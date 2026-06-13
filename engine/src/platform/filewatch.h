#pragma once
#include <core/types.h>
#include <stdbool.h>

#define FILEWATCH_MAX_PATH 256
#define FILEWATCH_MAX_ENTRIES 64

typedef struct {
    char  path[FILEWATCH_MAX_PATH];
    u32   last_modified;
    void (*callback)(const char *path, void *user);
    void *user;
#ifndef ENGINE_PLATFORM_WINDOWS
    i32   inotify_wd;  /* inotify watch descriptor for this entry */
#endif
} FileWatchEntry;

typedef struct {
    FileWatchEntry entries[FILEWATCH_MAX_ENTRIES];
    u32            count;
#ifdef ENGINE_PLATFORM_WINDOWS
    void          *dir_handle;
#else
    i32            inotify_fd;
#endif
} FileWatcher;

void filewatch_init(FileWatcher *fw);
void filewatch_shutdown(FileWatcher *fw);
void filewatch_add(FileWatcher *fw, const char *path,
                   void (*callback)(const char *path, void *user), void *user);
void filewatch_poll(FileWatcher *fw);

/* ------------------------------------------------------------------
 * Extended directory-watch API with structured events
 * ------------------------------------------------------------------ */
typedef enum {
    FW_EVENT_MODIFIED,
    FW_EVENT_CREATED,
    FW_EVENT_DELETED
} FileWatchEventType;

typedef struct {
    char path[256];
    FileWatchEventType type;
} FileWatchEvent;

typedef struct FileWatch FileWatch;

/* Create a recursive directory watcher (watches dir and all subdirectories). */
FileWatch *filewatch_create_dir(const char *dir_path);

/* Poll a single structured event. Returns true if an event was retrieved. */
bool filewatch_poll_event(FileWatch *fw, FileWatchEvent *out_event);

/* Destroy a FileWatch created by filewatch_create_dir. */
void filewatch_destroy(FileWatch *fw);
