#pragma once
#include <core/types.h>

#define FILEWATCH_MAX_PATH 256
#define FILEWATCH_MAX_ENTRIES 64

typedef struct {
    char  path[FILEWATCH_MAX_PATH];
    u32   last_modified;
    void (*callback)(const char *path, void *user);
    void *user;
} FileWatchEntry;

typedef struct {
    FileWatchEntry entries[FILEWATCH_MAX_ENTRIES];
    u32            count;
    i32            inotify_fd;
} FileWatcher;

void filewatch_init(FileWatcher *fw);
void filewatch_shutdown(FileWatcher *fw);
void filewatch_add(FileWatcher *fw, const char *path,
                   void (*callback)(const char *path, void *user), void *user);
void filewatch_poll(FileWatcher *fw);
