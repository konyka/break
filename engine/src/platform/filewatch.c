#include <platform/filewatch.h>
#include <core/log.h>
#include <string.h>
#include <sys/inotify.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>

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

    if (fw->inotify_fd >= 0) {
        inotify_add_watch(fw->inotify_fd, path, IN_MODIFY);
    }
}

void filewatch_poll(FileWatcher *fw) {
    if (fw->inotify_fd >= 0) {
        char buf[4096] __attribute__((aligned(__alignof__(struct inotify_event))));
        ssize_t len = read(fw->inotify_fd, buf, sizeof(buf));
        (void)len;
    }

    for (u32 i = 0; i < fw->count; i++) {
        FileWatchEntry *e = &fw->entries[i];
        u32 mt = file_mtime(e->path);
        if (mt != 0 && mt != e->last_modified) {
            e->last_modified = mt;
            if (e->callback) e->callback(e->path, e->user);
        }
    }
}
