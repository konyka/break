/* R419: the engine pins _POSIX_C_SOURCE=199309L, which hides lstat() on glibc
 * (needed below for symlink-safe directory recursion). _DEFAULT_SOURCE
 * restores it; inert on other platforms. Must precede all system includes. */
#define _DEFAULT_SOURCE

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
    if (!fw || !path || strlen(path) >= FILEWATCH_MAX_PATH) return;
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

#elif defined(ENGINE_PLATFORM_MACOS) || defined(__APPLE__)
#include <sys/event.h>
#include <sys/stat.h>
#include <dirent.h>
#include <fcntl.h>
#include <time.h>
#include <unistd.h>

#define FW_KQ_MAX_EVENTS 64

static u32 kq_file_mtime(const char *path) {
    struct stat st;
    if (stat(path, &st) != 0) return 0;
    return (u32)st.st_mtime;
}

static bool kq_register_vnode(int kq, int fd, uintptr_t ident) {
    struct kevent ev;
    EV_SET(&ev, (uintptr_t)fd, EVFILT_VNODE, EV_ADD | EV_ENABLE | EV_CLEAR,
           NOTE_WRITE | NOTE_DELETE | NOTE_RENAME | NOTE_ATTRIB, 0,
           (void *)ident);
    return kevent(kq, &ev, 1, NULL, 0, NULL) == 0;
}

/* ------------------------------------------------------------------
 * Legacy single-file watcher (FileWatcher)
 * ------------------------------------------------------------------ */
void filewatch_init(FileWatcher *fw) {
    memset(fw, 0, sizeof(*fw));
    fw->kqueue_fd = kqueue();
    if (fw->kqueue_fd < 0) {
        LOG_WARN("filewatch: kqueue init failed");
    }
}

void filewatch_shutdown(FileWatcher *fw) {
    if (!fw) return;
    if (fw->kqueue_fd >= 0) {
        for (u32 i = 0; i < fw->count; i++) {
            if (fw->entries[i].watch_fd >= 0) close(fw->entries[i].watch_fd);
            fw->entries[i].watch_fd = -1;
        }
        close(fw->kqueue_fd);
        fw->kqueue_fd = -1;
    }
}

void filewatch_add(FileWatcher *fw, const char *path,
                   void (*callback)(const char *path, void *user), void *user) {
    if (!fw || !path || strlen(path) >= FILEWATCH_MAX_PATH) return;
    if (fw->count >= FILEWATCH_MAX_ENTRIES) return;

    u32 idx = fw->count;
    FileWatchEntry *e = &fw->entries[idx];
    strncpy(e->path, path, FILEWATCH_MAX_PATH - 1);
    e->path[FILEWATCH_MAX_PATH - 1] = '\0';
    e->callback = callback;
    e->user = user;
    e->watch_fd = -1;
    e->last_modified = kq_file_mtime(path);

    if (fw->kqueue_fd >= 0) {
        int fd = open(path, O_RDONLY | O_NONBLOCK);
        if (fd >= 0) {
            if (kq_register_vnode(fw->kqueue_fd, fd, (uintptr_t)idx)) {
                e->watch_fd = fd;
            } else {
                close(fd);
            }
        }
    }
    fw->count++;
}

void filewatch_poll(FileWatcher *fw) {
    if (!fw) return;

    bool dirty[FILEWATCH_MAX_ENTRIES];
    bool kq_ok = false;
    memset(dirty, 0, sizeof(dirty));

    if (fw->kqueue_fd >= 0) {
        struct kevent events[FW_KQ_MAX_EVENTS];
        struct timespec ts = { 0, 0 };
        int n = kevent(fw->kqueue_fd, NULL, 0, events, FW_KQ_MAX_EVENTS, &ts);
        if (n > 0) {
            kq_ok = true;
            for (int i = 0; i < n; i++) {
                u32 idx = (u32)(uintptr_t)events[i].udata;
                if (idx < fw->count) dirty[idx] = true;
            }
        }
    }

    for (u32 i = 0; i < fw->count; i++) {
        if (kq_ok && !dirty[i]) continue;
        FileWatchEntry *e = &fw->entries[i];
        u32 mt = kq_file_mtime(e->path);
        if (mt != 0 && mt != e->last_modified) {
            e->last_modified = mt;
            if (e->callback) e->callback(e->path, e->user);
        }
    }
}

/* ------------------------------------------------------------------
 * Extended FileWatch API (macOS / BSD kqueue)
 * ------------------------------------------------------------------ */
typedef struct {
    char path[256];
    u32  mtime;
} KqWatchSnapshot;

struct FileWatch {
    int             kqueue_fd;
    int             watch_fds[FW_MAX_WATCHES];
    char            watch_paths[FW_MAX_WATCHES][256];
    u32             watch_mtimes[FW_MAX_WATCHES];
    bool            watch_is_dir[FW_MAX_WATCHES];
    u32             watch_count;
    char            base_path[256];
    FileWatchEvent  events[FW_EVENT_QUEUE_SIZE];
    u32             event_head;
    u32             event_tail;
};

static void kq_fw_enqueue(FileWatch *fw, const char *path, FileWatchEventType type) {
    if (!fw || !path || strlen(path) >= sizeof(fw->events[0].path)) return;
    u32 next = (fw->event_head + 1) % FW_EVENT_QUEUE_SIZE;
    if (next == fw->event_tail) return;
    FileWatchEvent ev;
    memset(&ev, 0, sizeof(ev));
    snprintf(ev.path, sizeof(ev.path), "%s", path);
    ev.type = type;
    fw->events[fw->event_head] = ev;
    fw->event_head = next;
}

static bool kq_fw_register(FileWatch *fw, const char *path, bool is_dir, u32 mtime) {
    if (!fw || !path || strlen(path) >= sizeof(fw->watch_paths[0])) return false;
    if (fw->watch_count >= FW_MAX_WATCHES) return false;

    int fd = open(path, O_RDONLY | O_NONBLOCK);
    if (fd < 0) return false;

    u32 idx = fw->watch_count;
    if (!kq_register_vnode(fw->kqueue_fd, fd, (uintptr_t)idx)) {
        close(fd);
        return false;
    }

    fw->watch_fds[idx] = fd;
    strncpy(fw->watch_paths[idx], path, sizeof(fw->watch_paths[idx]) - 1);
    fw->watch_paths[idx][sizeof(fw->watch_paths[idx]) - 1] = '\0';
    fw->watch_mtimes[idx] = mtime;
    fw->watch_is_dir[idx] = is_dir;
    fw->watch_count++;
    return true;
}

static void kq_fw_reset(FileWatch *fw) {
    if (!fw) return;
    for (u32 i = 0; i < fw->watch_count; i++) {
        if (fw->watch_fds[i] >= 0) close(fw->watch_fds[i]);
        fw->watch_fds[i] = -1;
        fw->watch_paths[i][0] = '\0';
        fw->watch_mtimes[i] = 0;
        fw->watch_is_dir[i] = false;
    }
    fw->watch_count = 0;
}

static void kq_fw_scan_dir(FileWatch *fw, const char *path, u32 depth) {
    if (!fw || !path || depth >= 32u || fw->watch_count >= FW_MAX_WATCHES) return;

    DIR *dir = opendir(path);
    if (!dir) return;

    struct stat st;
    if (lstat(path, &st) == 0) {
        kq_fw_register(fw, path, true, (u32)st.st_mtime);
    }

    struct dirent *ent;
    while ((ent = readdir(dir)) != NULL && fw->watch_count < FW_MAX_WATCHES) {
        if (strcmp(ent->d_name, ".") == 0 || strcmp(ent->d_name, "..") == 0) continue;

        char child[512];
        int n = snprintf(child, sizeof(child), "%s/%s", path, ent->d_name);
        if (n < 0 || (usize)n >= sizeof(child)) continue;

        struct stat cst;
        if (lstat(child, &cst) != 0) continue;
        if (S_ISDIR(cst.st_mode)) {
            if (depth + 1u < 32u) kq_fw_scan_dir(fw, child, depth + 1u);
        } else if (S_ISREG(cst.st_mode)) {
            kq_fw_register(fw, child, false, (u32)cst.st_mtime);
        }
    }
    closedir(dir);
}

static bool kq_fw_snapshot_find(const KqWatchSnapshot *snap, u32 count,
                                const char *path, u32 *out_idx) {
    if (!snap || !path || !out_idx) return false;
    for (u32 i = 0; i < count; i++) {
        if (strcmp(snap[i].path, path) == 0) {
            *out_idx = i;
            return true;
        }
    }
    return false;
}

static bool kq_fw_watch_find(const FileWatch *fw, const char *path, u32 *out_idx) {
    if (!fw || !path || !out_idx) return false;
    for (u32 i = 0; i < fw->watch_count; i++) {
        if (strcmp(fw->watch_paths[i], path) == 0) {
            *out_idx = i;
            return true;
        }
    }
    return false;
}

static void kq_fw_rescan(FileWatch *fw) {
    if (!fw || !fw->base_path[0]) return;

    KqWatchSnapshot old[FW_MAX_WATCHES];
    u32 old_count = fw->watch_count;
    if (old_count > FW_MAX_WATCHES) old_count = FW_MAX_WATCHES;
    for (u32 i = 0; i < old_count; i++) {
        strncpy(old[i].path, fw->watch_paths[i], sizeof(old[i].path) - 1);
        old[i].path[sizeof(old[i].path) - 1] = '\0';
        old[i].mtime = fw->watch_mtimes[i];
    }

    kq_fw_reset(fw);
    kq_fw_scan_dir(fw, fw->base_path, 0);

    for (u32 i = 0; i < fw->watch_count; i++) {
        u32 old_idx = 0;
        if (!kq_fw_snapshot_find(old, old_count, fw->watch_paths[i], &old_idx)) {
            kq_fw_enqueue(fw, fw->watch_paths[i], FW_EVENT_CREATED);
        } else if (fw->watch_mtimes[i] != old[old_idx].mtime) {
            kq_fw_enqueue(fw, fw->watch_paths[i], FW_EVENT_MODIFIED);
        }
    }

    for (u32 i = 0; i < old_count; i++) {
        u32 new_idx = 0;
        if (!kq_fw_watch_find(fw, old[i].path, &new_idx)) {
            kq_fw_enqueue(fw, old[i].path, FW_EVENT_DELETED);
        }
    }
}

FileWatch *filewatch_create_dir(const char *dir_path) {
    if (!dir_path || strlen(dir_path) >= FILEWATCH_MAX_PATH) return NULL;

    FileWatch *fw = (FileWatch *)calloc(1, sizeof(FileWatch));
    if (!fw) return NULL;

    strncpy(fw->base_path, dir_path, sizeof(fw->base_path) - 1);
    fw->base_path[sizeof(fw->base_path) - 1] = '\0';
    fw->kqueue_fd = kqueue();
    if (fw->kqueue_fd < 0) {
        free(fw);
        return NULL;
    }

    kq_fw_scan_dir(fw, dir_path, 0);
    return fw;
}

bool filewatch_poll_event(FileWatch *fw, FileWatchEvent *out_event) {
    if (!fw || !out_event) return false;

    if (fw->event_head != fw->event_tail) {
        *out_event = fw->events[fw->event_tail];
        fw->event_tail = (fw->event_tail + 1) % FW_EVENT_QUEUE_SIZE;
        return true;
    }

    if (fw->kqueue_fd >= 0) {
        struct kevent events[FW_KQ_MAX_EVENTS];
        struct timespec ts = { 0, 0 };
        int n = kevent(fw->kqueue_fd, NULL, 0, events, FW_KQ_MAX_EVENTS, &ts);
        bool rescan = false;

        for (int i = 0; i < n; i++) {
            if (events[i].flags & EV_ERROR) continue;
            u32 idx = (u32)(uintptr_t)events[i].udata;
            if (idx >= fw->watch_count) continue;

            if (events[i].fflags & (NOTE_DELETE | NOTE_RENAME)) {
                rescan = true;
                continue;
            }
            if (fw->watch_is_dir[idx]) {
                rescan = true;
                continue;
            }

            const char *path = fw->watch_paths[idx];
            u32 mt = kq_file_mtime(path);
            if (mt == 0) {
                rescan = true;
            } else if (mt != fw->watch_mtimes[idx]) {
                fw->watch_mtimes[idx] = mt;
                kq_fw_enqueue(fw, path, FW_EVENT_MODIFIED);
            }
        }

        if (rescan) kq_fw_rescan(fw);
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
    if (fw->kqueue_fd >= 0) {
        kq_fw_reset(fw);
        close(fw->kqueue_fd);
    }
    free(fw);
}

#elif defined(ENGINE_PLATFORM_LINUX)
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
    if (!fw || !path || strlen(path) >= FILEWATCH_MAX_PATH) return;
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
                /* R419: IN_Q_OVERFLOW (wd == -1) means the kernel dropped
                 * events — the dirty set is incomplete, so fall back to
                 * stat-ing every watched file this cycle. */
                if (ev->mask & IN_Q_OVERFLOW) {
                    inotify_ok = false;
                    break;
                }
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

static void fw_add_dir_recursive(FileWatch *fw, const char *path, u32 depth) {
    /* R419: cap recursion depth — a symlink to an ancestor directory would
     * otherwise recurse forever (stack overflow). */
    if (depth >= 32) return;
    /* R432: skip the add when this path is already watched — a subdir created
     * after its parent's inotify_add_watch but before recursion reached it is
     * re-added when its queued IN_CREATE fires; inotify_add_watch returns the
     * SAME wd, which was then stored in two slots, and IN_IGNORED retires only
     * the first match, leaving a stale slot that aliases events to the old
     * path when the kernel reuses the wd. Recursion below still runs so any
     * not-yet-watched children are picked up. */
    bool already_watched = false;
    for (u32 i = 0; i < fw->watch_count; i++) {
        if (fw->watch_fds[i] != -1 && strcmp(fw->watch_paths[i], path) == 0) {
            already_watched = true;
            break;
        }
    }
    /* R427: reclaim a slot retired by IN_IGNORED (watch_fds[i] == -1) before
     * appending — watch_count only ever grew, so sustained dir churn exhausted
     * FW_MAX_WATCHES and new dirs were silently never watched. */
    u32 slot = fw->watch_count;
    if (!already_watched) {
        for (u32 i = 0; i < fw->watch_count; i++) {
            if (fw->watch_fds[i] == -1) { slot = i; break; }
        }
    }
    if (!already_watched && slot < FW_MAX_WATCHES) {
        int wd = inotify_add_watch(fw->inotify_fd, path,
            IN_MODIFY | IN_CREATE | IN_DELETE | IN_MOVED_TO);
        if (wd >= 0) {
            fw->watch_fds[slot] = wd;
            strncpy(fw->watch_paths[slot], path, 255);
            fw->watch_paths[slot][255] = '\0';
            if (slot == fw->watch_count) fw->watch_count++;
        } else {
            LOG_WARN("filewatch: inotify_add_watch failed for %s", path);
        }
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
        /* R419: lstat (not stat) and skip symlinks — stat() follows links, so
         * a symlink to an ancestor dir caused unbounded recursion. */
        if (lstat(sub, &st) == 0 && S_ISDIR(st.st_mode) && !S_ISLNK(st.st_mode)) {
            fw_add_dir_recursive(fw, sub, depth + 1);
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
    fw->base_path[sizeof(fw->base_path) - 1] = '\0';
    fw_add_dir_recursive(fw, dir_path, 0);
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

        /* R423: IN_Q_OVERFLOW (wd == -1) matches no watch and was silently
         * dropped, losing every queued event. Surface it as a MODIFIED event
         * on the watched root so the caller knows its event stream is
         * incomplete and can rescan. */
        if (event->mask & IN_Q_OVERFLOW) {
            LOG_WARN("filewatch: inotify queue overflow for %s — events lost, rescan advised",
                     fw->base_path);
            FileWatchEvent ov;
            memset(&ov, 0, sizeof(ov));
            snprintf(ov.path, sizeof(ov.path), "%s", fw->base_path);
            ov.type = FW_EVENT_MODIFIED;
            u32 next = (fw->event_head + 1) % FW_EVENT_QUEUE_SIZE;
            if (next != fw->event_tail) {
                fw->events[fw->event_head] = ov;
                fw->event_head = next;
            }
            ptr += sizeof(struct inotify_event) + event->len;
            continue;
        }

        /* R423: IN_IGNORED means the kernel removed this watch (dir deleted /
         * unmounted). Retire the entry — a later inotify_add_watch may reuse
         * the same wd and a stale entry would alias events to this path. */
        if (event->mask & IN_IGNORED) {
            for (u32 i = 0; i < fw->watch_count; i++) {
                if (fw->watch_fds[i] == event->wd) {
                    fw->watch_fds[i] = -1;
                    fw->watch_paths[i][0] = '\0';
                    break;
                }
            }
            ptr += sizeof(struct inotify_event) + event->len;
            continue;
        }

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
         * exceed sizeof(ev.path). R423: track whether the copy truncated. */
        bool path_truncated = false;
        if (event->len > 0) {
            char tmp[FILEWATCH_MAX_PATH * 2 + 4];
            int n = snprintf(tmp, sizeof(tmp), "%s/%s", dir_path, event->name);
            if (n < 0) n = 0;
            size_t copy = (size_t)n;
            if (copy >= sizeof(ev.path)) {
                copy = sizeof(ev.path) - 1;
                path_truncated = true;
            }
            memcpy(ev.path, tmp, copy);
            ev.path[copy] = '\0';
        } else {
            size_t dl = strlen(dir_path);
            if (dl >= sizeof(ev.path)) {
                dl = sizeof(ev.path) - 1;
                path_truncated = true;
            }
            memcpy(ev.path, dir_path, dl);
            ev.path[dl] = '\0';
        }

        bool keep = true;
        if (event->mask & IN_MODIFY)        ev.type = FW_EVENT_MODIFIED;
        else if (event->mask & IN_CREATE)   ev.type = FW_EVENT_CREATED;
        else if (event->mask & IN_DELETE)   ev.type = FW_EVENT_DELETED;
        else if (event->mask & IN_MOVED_TO) ev.type = FW_EVENT_CREATED;
        else keep = false;

        /* Auto-watch newly created subdirectories. R423: skip when the path
         * was truncated — the capped path can point at the wrong directory. */
        if ((event->mask & IN_CREATE) && (event->mask & IN_ISDIR)) {
            if (!path_truncated) {
                fw_add_dir_recursive(fw, ev.path, 0);
            } else {
                LOG_WARN("filewatch: not auto-watching truncated path (>255 bytes)");
            }
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

#else /* portable fallback (macOS and other POSIX without inotify) */
#include <sys/stat.h>

struct FileWatch {
    char            base_path[256];
    u32             last_mtime;
    FileWatchEvent  events[FW_EVENT_QUEUE_SIZE];
    u32             event_head;
    u32             event_tail;
};

static u32 file_mtime(const char *path) {
    struct stat st;
    if (stat(path, &st) != 0) return 0;
    return (u32)st.st_mtime;
}

static void filewatch_fallback_enqueue(FileWatch *fw, const FileWatchEvent *ev) {
    u32 next = (fw->event_head + 1) % FW_EVENT_QUEUE_SIZE;
    if (next == fw->event_tail) return;
    fw->events[fw->event_head] = *ev;
    fw->event_head = next;
}

void filewatch_init(FileWatcher *fw) {
    memset(fw, 0, sizeof(*fw));
}

void filewatch_shutdown(FileWatcher *fw) {
    (void)fw;
}

void filewatch_add(FileWatcher *fw, const char *path,
                   void (*callback)(const char *path, void *user), void *user) {
    if (!fw || !path || strlen(path) >= FILEWATCH_MAX_PATH) return;
    if (fw->count >= FILEWATCH_MAX_ENTRIES) return;
    FileWatchEntry *e = &fw->entries[fw->count++];
    strncpy(e->path, path, FILEWATCH_MAX_PATH - 1);
    e->path[FILEWATCH_MAX_PATH - 1] = '\0';
    e->callback = callback;
    e->user = user;
    e->last_modified = file_mtime(path);
}

void filewatch_poll(FileWatcher *fw) {
    if (!fw) return;
    for (u32 i = 0; i < fw->count; i++) {
        FileWatchEntry *e = &fw->entries[i];
        u32 mt = file_mtime(e->path);
        if (mt != 0 && mt != e->last_modified) {
            e->last_modified = mt;
            if (e->callback) e->callback(e->path, e->user);
        }
    }
}

FileWatch *filewatch_create_dir(const char *dir_path) {
    if (!dir_path) return NULL;
    FileWatch *fw = (FileWatch *)calloc(1, sizeof(FileWatch));
    if (!fw) return NULL;
    strncpy(fw->base_path, dir_path, sizeof(fw->base_path) - 1);
    fw->base_path[sizeof(fw->base_path) - 1] = '\0';
    fw->last_mtime = file_mtime(dir_path);
    return fw;
}

bool filewatch_poll_event(FileWatch *fw, FileWatchEvent *out_event) {
    if (!fw || !out_event) return false;

    if (fw->event_head != fw->event_tail) {
        *out_event = fw->events[fw->event_tail];
        fw->event_tail = (fw->event_tail + 1) % FW_EVENT_QUEUE_SIZE;
        return true;
    }

    u32 mt = file_mtime(fw->base_path);
    if (mt != 0 && mt != fw->last_mtime) {
        fw->last_mtime = mt;
        FileWatchEvent ev;
        memset(&ev, 0, sizeof(ev));
        snprintf(ev.path, sizeof(ev.path), "%s", fw->base_path);
        ev.type = FW_EVENT_MODIFIED;
        filewatch_fallback_enqueue(fw, &ev);
    }

    if (fw->event_head != fw->event_tail) {
        *out_event = fw->events[fw->event_tail];
        fw->event_tail = (fw->event_tail + 1) % FW_EVENT_QUEUE_SIZE;
        return true;
    }
    return false;
}

void filewatch_destroy(FileWatch *fw) {
    free(fw);
}

#endif
