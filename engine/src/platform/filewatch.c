#include <platform/filewatch.h>
#include <core/log.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define FW_MAX_WATCHES 256
#define FW_EVENT_QUEUE_SIZE 32
#define FW_NOTIFY_BUF_SIZE 4096

#ifdef ENGINE_PLATFORM_WINDOWS
#include <windows.h>

struct FileWatch {
    HANDLE     dir_handle;
    OVERLAPPED overlapped;
    BYTE       buffer[FW_NOTIFY_BUF_SIZE];
    char       base_path[256];
    FileWatchEvent events[FW_EVENT_QUEUE_SIZE];
    u32        event_head;
    u32        event_tail;
    bool       watching;
};

static u32 file_mtime(const char *path) {
    WIN32_FILE_ATTRIBUTE_DATA data;
    if (!GetFileAttributesExA(path, GetFileExInfoStandard, &data)) return 0;
    /* Convert FILETIME to unix-epoch seconds for comparison */
    ULARGE_INTEGER ull;
    ull.LowPart  = data.ftLastWriteTime.dwLowDateTime;
    ull.HighPart = data.ftLastWriteTime.dwHighDateTime;
    return (u32)((ull.QuadPart - 116444736000000000ULL) / 10000000ULL);
}

/* ------------------------------------------------------------------
 * Legacy single-file watcher (FileWatcher) — directory change notification
 * ------------------------------------------------------------------ */
void filewatch_init(FileWatcher *fw) {
    memset(fw, 0, sizeof(*fw));
    fw->dir_handle = INVALID_HANDLE_VALUE;
}

void filewatch_shutdown(FileWatcher *fw) {
    if (fw->dir_handle != INVALID_HANDLE_VALUE) {
        FindCloseChangeNotification((HANDLE)fw->dir_handle);
        fw->dir_handle = INVALID_HANDLE_VALUE;
    }
}

void filewatch_add(FileWatcher *fw, const char *path,
                   void (*callback)(const char *path, void *user), void *user) {
    if (fw->count >= FILEWATCH_MAX_ENTRIES) return;
    FileWatchEntry *e = &fw->entries[fw->count++];
    strncpy(e->path, path, FILEWATCH_MAX_PATH - 1);
    e->path[FILEWATCH_MAX_PATH - 1] = '\0';
    e->callback = callback;
    e->user = user;
    e->last_modified = file_mtime(path);

    /* Set up directory change notification for the first entry */
    if (fw->dir_handle == INVALID_HANDLE_VALUE) {
        /* Extract directory from path */
        char dir[FILEWATCH_MAX_PATH];
        strncpy(dir, path, FILEWATCH_MAX_PATH - 1);
        dir[FILEWATCH_MAX_PATH - 1] = '\0';
        char *last_sep = strrchr(dir, '\\');
        if (!last_sep) last_sep = strrchr(dir, '/');
        if (last_sep) {
            *last_sep = '\0';
        } else {
            dir[0] = '.';
            dir[1] = '\0';
        }
        HANDLE h = FindFirstChangeNotificationA(dir, FALSE,
                                                 FILE_NOTIFY_CHANGE_LAST_WRITE);
        if (h != INVALID_HANDLE_VALUE) {
            fw->dir_handle = (void *)h;
        }
    }
}

void filewatch_poll(FileWatcher *fw) {
    /* Check if directory notification was triggered (non-blocking) */
    if (fw->dir_handle != INVALID_HANDLE_VALUE) {
        DWORD result = WaitForSingleObject((HANDLE)fw->dir_handle, 0);
        if (result == WAIT_OBJECT_0) {
            FindNextChangeNotification((HANDLE)fw->dir_handle);
        }
    }

    /* Poll all watched files for mtime changes */
    for (u32 i = 0; i < fw->count; i++) {
        FileWatchEntry *e = &fw->entries[i];
        u32 mt = file_mtime(e->path);
        if (mt != 0 && mt != e->last_modified) {
            e->last_modified = mt;
            if (e->callback) e->callback(e->path, e->user);
        }
    }
}

/* ------------------------------------------------------------------
 * Extended FileWatch API (Windows ReadDirectoryChangesW)
 * ------------------------------------------------------------------ */

#define FW_NOTIFY_FILTER \
    (FILE_NOTIFY_CHANGE_FILE_NAME | \
     FILE_NOTIFY_CHANGE_DIR_NAME  | \
     FILE_NOTIFY_CHANGE_LAST_WRITE | \
     FILE_NOTIFY_CHANGE_CREATION)

static bool fw_start_watch(FileWatch *fw) {
    return ReadDirectoryChangesW(fw->dir_handle,
                                 fw->buffer,
                                 sizeof(fw->buffer),
                                 TRUE, /* recursive */
                                 FW_NOTIFY_FILTER,
                                 NULL,
                                 &fw->overlapped,
                                 NULL) ? true : false;
}

FileWatch *filewatch_create_dir(const char *dir_path) {
    if (!dir_path) return NULL;

    FileWatch *fw = (FileWatch *)calloc(1, sizeof(FileWatch));
    if (!fw) return NULL;

    strncpy(fw->base_path, dir_path, sizeof(fw->base_path) - 1);
    fw->base_path[sizeof(fw->base_path) - 1] = '\0';

    fw->dir_handle = CreateFileA(
        dir_path,
        FILE_LIST_DIRECTORY,
        FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE,
        NULL,
        OPEN_EXISTING,
        FILE_FLAG_BACKUP_SEMANTICS | FILE_FLAG_OVERLAPPED,
        NULL);

    if (fw->dir_handle == INVALID_HANDLE_VALUE) {
        LOG_WARN("filewatch: CreateFile failed for %s", dir_path);
        free(fw);
        return NULL;
    }

    fw->overlapped.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
    if (!fw->overlapped.hEvent) {
        CloseHandle(fw->dir_handle);
        free(fw);
        return NULL;
    }

    if (!fw_start_watch(fw)) {
        LOG_WARN("filewatch: ReadDirectoryChangesW failed for %s", dir_path);
        CloseHandle(fw->overlapped.hEvent);
        CloseHandle(fw->dir_handle);
        free(fw);
        return NULL;
    }

    fw->watching = true;
    return fw;
}

static void fw_enqueue_event(FileWatch *fw, const FileWatchEvent *ev) {
    u32 next = (fw->event_head + 1) % FW_EVENT_QUEUE_SIZE;
    if (next == fw->event_tail) return; /* full, drop */
    fw->events[fw->event_head] = *ev;
    fw->event_head = next;
}

bool filewatch_poll_event(FileWatch *fw, FileWatchEvent *out_event) {
    if (!fw || !out_event) return false;

    /* Drain queue first */
    if (fw->event_head != fw->event_tail) {
        *out_event = fw->events[fw->event_tail];
        fw->event_tail = (fw->event_tail + 1) % FW_EVENT_QUEUE_SIZE;
        return true;
    }

    if (!fw->watching) return false;

    /* Non-blocking check on overlapped completion */
    DWORD bytes_returned = 0;
    if (!GetOverlappedResult(fw->dir_handle, &fw->overlapped, &bytes_returned, FALSE)) {
        /* Not yet complete (ERROR_IO_INCOMPLETE) or other error */
        return false;
    }
    if (bytes_returned == 0) {
        /* Buffer overflow — restart watch */
        ResetEvent(fw->overlapped.hEvent);
        fw_start_watch(fw);
        return false;
    }

    /* Parse FILE_NOTIFY_INFORMATION records */
    FILE_NOTIFY_INFORMATION *fni = (FILE_NOTIFY_INFORMATION *)fw->buffer;
    for (;;) {
        FileWatchEvent ev;
        memset(&ev, 0, sizeof(ev));

        /* Convert wide filename to UTF-8 */
        char filename[FILEWATCH_MAX_PATH];
        int wlen = (int)(fni->FileNameLength / sizeof(WCHAR));
        int written = WideCharToMultiByte(CP_UTF8, 0,
                                          fni->FileName, wlen,
                                          filename, (int)sizeof(filename) - 1,
                                          NULL, NULL);
        if (written < 0) written = 0;
        if (written >= (int)sizeof(filename)) written = (int)sizeof(filename) - 1;
        filename[written] = '\0';

        /* Build full path safely (avoid format-truncation warnings) */
        char tmp[FILEWATCH_MAX_PATH * 2 + 4];
        int n = snprintf(tmp, sizeof(tmp), "%s\\%s", fw->base_path, filename);
        if (n < 0) n = 0;
        size_t copy = (size_t)n;
        if (copy >= sizeof(ev.path)) copy = sizeof(ev.path) - 1;
        memcpy(ev.path, tmp, copy);
        ev.path[copy] = '\0';

        switch (fni->Action) {
        case FILE_ACTION_MODIFIED:         ev.type = FW_EVENT_MODIFIED; break;
        case FILE_ACTION_ADDED:            ev.type = FW_EVENT_CREATED;  break;
        case FILE_ACTION_REMOVED:          ev.type = FW_EVENT_DELETED;  break;
        case FILE_ACTION_RENAMED_NEW_NAME: ev.type = FW_EVENT_CREATED;  break;
        case FILE_ACTION_RENAMED_OLD_NAME: ev.type = FW_EVENT_DELETED;  break;
        default:                           ev.type = FW_EVENT_MODIFIED; break;
        }

        fw_enqueue_event(fw, &ev);

        if (fni->NextEntryOffset == 0) break;
        fni = (FILE_NOTIFY_INFORMATION *)((BYTE *)fni + fni->NextEntryOffset);
    }

    /* Re-arm watch */
    ResetEvent(fw->overlapped.hEvent);
    fw_start_watch(fw);

    /* Return first queued event */
    if (fw->event_head != fw->event_tail) {
        *out_event = fw->events[fw->event_tail];
        fw->event_tail = (fw->event_tail + 1) % FW_EVENT_QUEUE_SIZE;
        return true;
    }
    return false;
}

void filewatch_destroy(FileWatch *fw) {
    if (!fw) return;
    if (fw->dir_handle != INVALID_HANDLE_VALUE && fw->dir_handle != NULL) {
        CancelIo(fw->dir_handle);
        CloseHandle(fw->dir_handle);
    }
    if (fw->overlapped.hEvent) {
        CloseHandle(fw->overlapped.hEvent);
    }
    free(fw);
}

#else /* Linux / POSIX */
#include <sys/inotify.h>
#include <sys/stat.h>
#include <unistd.h>

struct FileWatch {
    int   inotify_fd;
    int   watch_fds[FW_MAX_WATCHES];
    char  watch_paths[FW_MAX_WATCHES][256];
    u32   watch_count;
    char  base_path[256];
    FileWatchEvent events[FW_EVENT_QUEUE_SIZE];
    u32   event_head;
    u32   event_tail;
};

void filewatch_init(FileWatcher *fw) {
    memset(fw, 0, sizeof(*fw));
    fw->inotify_fd = inotify_init1(IN_NONBLOCK);
    if (fw->inotify_fd < 0) {
        LOG_WARN("filewatch: inotify_init failed");
    }
}

void filewatch_shutdown(FileWatcher *fw) {
    if (fw->inotify_fd >= 0) close(fw->inotify_fd);
    fw->inotify_fd = -1;
}

static u32 file_mtime(const char *path) {
    struct stat st;
    if (stat(path, &st) != 0) return 0;
    return (u32)st.st_mtime;
}

void filewatch_add(FileWatcher *fw, const char *path,
                   void (*callback)(const char *path, void *user), void *user) {
    if (fw->count >= FILEWATCH_MAX_ENTRIES) return;
    FileWatchEntry *e = &fw->entries[fw->count++];
    strncpy(e->path, path, FILEWATCH_MAX_PATH - 1);
    e->path[FILEWATCH_MAX_PATH - 1] = '\0';
    e->callback = callback;
    e->user = user;
    e->last_modified = file_mtime(path);
    e->inotify_wd = -1;

    if (fw->inotify_fd >= 0) {
        int wd = inotify_add_watch(fw->inotify_fd, path, IN_MODIFY);
        if (wd >= 0) e->inotify_wd = wd;
    }
}

void filewatch_poll(FileWatcher *fw) {
    /* Parse inotify events to build dirty set, only stat modified files */
    bool dirty[FILEWATCH_MAX_ENTRIES];
    bool inotify_ok = false;

    if (fw->inotify_fd >= 0) {
        char buf[4096] ENGINE_ALIGN(__alignof__(struct inotify_event));
        ssize_t len = read(fw->inotify_fd, buf, sizeof(buf));
        if (len > 0) {
            memset(dirty, 0, sizeof(dirty));
            inotify_ok = true;
            const char *ptr = buf;
            while (ptr < buf + len) {
                const struct inotify_event *ev = (const struct inotify_event *)ptr;
                /* Mark the entry matching this wd as dirty */
                for (u32 i = 0; i < fw->count; i++) {
                    if (fw->entries[i].inotify_wd == ev->wd) {
                        dirty[i] = true;
                        break;
                    }
                }
                ptr += sizeof(struct inotify_event) + ev->len;
            }
        }
    }

    for (u32 i = 0; i < fw->count; i++) {
        /* If inotify read succeeded, skip entries not in dirty set */
        if (inotify_ok && !dirty[i]) continue;

        FileWatchEntry *e = &fw->entries[i];
        u32 mt = file_mtime(e->path);
        if (mt != 0 && mt != e->last_modified) {
            e->last_modified = mt;
            if (e->callback) e->callback(e->path, e->user);
        }
    }
}

/* ------------------------------------------------------------------
 * Extended FileWatch API (Linux/inotify recursive implementation)
 * ------------------------------------------------------------------ */
#include <dirent.h>

static void fw_add_dir_recursive(FileWatch *fw, const char *path) {
    if (fw->watch_count >= FW_MAX_WATCHES) return;
    int wd = inotify_add_watch(fw->inotify_fd, path,
        IN_MODIFY | IN_CREATE | IN_DELETE | IN_MOVED_TO);
    if (wd >= 0) {
        fw->watch_fds[fw->watch_count] = wd;
        strncpy(fw->watch_paths[fw->watch_count], path, 255);
        fw->watch_paths[fw->watch_count][255] = '\0';
        fw->watch_count++;
    } else {
        LOG_WARN("filewatch: inotify_add_watch failed for %s", path);
    }

    DIR *dir = opendir(path);
    if (!dir) return;
    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_name[0] == '.') continue;
        /* Use a generously-sized buffer to avoid format-truncation warnings
         * (path may itself approach 256 bytes; d_name up to NAME_MAX=255). */
        char sub[FILEWATCH_MAX_PATH * 2 + 4];
        int n = snprintf(sub, sizeof(sub), "%s/%s", path, entry->d_name);
        if (n < 0 || (size_t)n >= sizeof(sub)) continue;
        struct stat st;
        if (stat(sub, &st) == 0 && S_ISDIR(st.st_mode)) {
            fw_add_dir_recursive(fw, sub);
        }
    }
    closedir(dir);
}

FileWatch *filewatch_create_dir(const char *dir_path) {
    if (!dir_path) return NULL;
    FileWatch *fw = (FileWatch *)calloc(1, sizeof(FileWatch));
    if (!fw) return NULL;
    fw->inotify_fd = inotify_init1(IN_NONBLOCK);
    if (fw->inotify_fd < 0) {
        LOG_WARN("filewatch: inotify_init failed");
        free(fw);
        return NULL;
    }
    strncpy(fw->base_path, dir_path, sizeof(fw->base_path) - 1);
    fw_add_dir_recursive(fw, dir_path);
    return fw;
}

bool filewatch_poll_event(FileWatch *fw, FileWatchEvent *out_event) {
    if (!fw || !out_event) return false;

    /* Drain queue first */
    if (fw->event_head != fw->event_tail) {
        *out_event = fw->events[fw->event_tail];
        fw->event_tail = (fw->event_tail + 1) % FW_EVENT_QUEUE_SIZE;
        return true;
    }

    if (fw->inotify_fd < 0) return false;

    char buf[4096] ENGINE_ALIGN(__alignof__(struct inotify_event));
    ssize_t len = read(fw->inotify_fd, buf, sizeof(buf));
    if (len <= 0) return false;

    for (char *ptr = buf; ptr < buf + len; ) {
        struct inotify_event *event = (struct inotify_event *)ptr;

        const char *dir_path = "";
        for (u32 i = 0; i < fw->watch_count; i++) {
            if (fw->watch_fds[i] == event->wd) {
                dir_path = fw->watch_paths[i];
                break;
            }
        }

        FileWatchEvent ev;
        memset(&ev, 0, sizeof(ev));
        /* Format into an oversized temp buffer first, then bounded-copy into
         * ev.path to avoid GCC -Wformat-truncation when dir_path + name may
         * exceed sizeof(ev.path). */
        if (event->len > 0) {
            char tmp[FILEWATCH_MAX_PATH * 2 + 4];
            int n = snprintf(tmp, sizeof(tmp), "%s/%s", dir_path, event->name);
            if (n < 0) n = 0;
            size_t copy = (size_t)n;
            if (copy >= sizeof(ev.path)) copy = sizeof(ev.path) - 1;
            memcpy(ev.path, tmp, copy);
            ev.path[copy] = '\0';
        } else {
            size_t dl = strlen(dir_path);
            if (dl >= sizeof(ev.path)) dl = sizeof(ev.path) - 1;
            memcpy(ev.path, dir_path, dl);
            ev.path[dl] = '\0';
        }

        bool keep = true;
        if (event->mask & IN_MODIFY)        ev.type = FW_EVENT_MODIFIED;
        else if (event->mask & IN_CREATE)   ev.type = FW_EVENT_CREATED;
        else if (event->mask & IN_DELETE)   ev.type = FW_EVENT_DELETED;
        else if (event->mask & IN_MOVED_TO) ev.type = FW_EVENT_CREATED;
        else keep = false;

        /* Auto-watch newly created subdirectories */
        if ((event->mask & IN_CREATE) && (event->mask & IN_ISDIR)) {
            fw_add_dir_recursive(fw, ev.path);
        }

        if (keep) {
            u32 next = (fw->event_head + 1) % FW_EVENT_QUEUE_SIZE;
            if (next != fw->event_tail) {
                fw->events[fw->event_head] = ev;
                fw->event_head = next;
            }
        }

        ptr += sizeof(struct inotify_event) + event->len;
    }

    if (fw->event_head != fw->event_tail) {
        *out_event = fw->events[fw->event_tail];
        fw->event_tail = (fw->event_tail + 1) % FW_EVENT_QUEUE_SIZE;
        return true;
    }
    return false;
}

void filewatch_destroy(FileWatch *fw) {
    if (!fw) return;
    if (fw->inotify_fd >= 0) {
        for (u32 i = 0; i < fw->watch_count; i++) {
            inotify_rm_watch(fw->inotify_fd, fw->watch_fds[i]);
        }
        close(fw->inotify_fd);
    }
    free(fw);
}

#endif
