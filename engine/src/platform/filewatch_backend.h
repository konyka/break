#pragma once
#include <core/types.h>
#include <platform/filewatch.h>

typedef enum {
    FILEWATCH_BACKEND_KQUEUE = 0,
    FILEWATCH_BACKEND_FSEVENTS = 1
} FileWatchBackend;

/* Choose the macOS directory-watch backend from bounded tree statistics.
 * FSEvents is preferred for large/deep trees; kqueue is preferred when exact
 * per-file events matter and the watch set is small enough. */
#define FILEWATCH_FSEVENTS_MIN_FILES 512u
#define FILEWATCH_FSEVENTS_MIN_DEPTH 8u
#define FILEWATCH_FSEVENTS_MAX_KQUEUE_WATCHES 256u

FileWatchBackend filewatch_select_backend(u32 file_count, u32 dir_count,
                                           u32 max_depth);

/* FSEvents flag values are platform constants. Keep the decision logic here
 * so the backend selection and callback mapping remain unit-testable on
 * every host platform. */
#define FILEWATCH_FSEVENT_FLAG_MUST_SCAN_SUBDIRS  0x00000001u
#define FILEWATCH_FSEVENT_FLAG_USER_DROPPED       0x00000002u
#define FILEWATCH_FSEVENT_FLAG_KERNEL_DROPPED     0x00000004u
#define FILEWATCH_FSEVENT_FLAG_EVENT_IDS_WRAPPED  0x00000008u
#define FILEWATCH_FSEVENT_FLAG_HISTORY_DONE       0x00000010u
#define FILEWATCH_FSEVENT_FLAG_ROOT_CHANGED       0x00000020u
#define FILEWATCH_FSEVENT_FLAG_MOUNT              0x00000040u
#define FILEWATCH_FSEVENT_FLAG_UNMOUNT            0x00000080u
#define FILEWATCH_FSEVENT_FLAG_ITEM_CREATED       0x00000100u
#define FILEWATCH_FSEVENT_FLAG_ITEM_REMOVED       0x00000200u
#define FILEWATCH_FSEVENT_FLAG_ITEM_INODE_META_MOD 0x00000400u
#define FILEWATCH_FSEVENT_FLAG_ITEM_RENAMED       0x00000800u
#define FILEWATCH_FSEVENT_FLAG_ITEM_MODIFIED      0x00001000u
#define FILEWATCH_FSEVENT_FLAG_ITEM_FINDER_INFO_MOD 0x00002000u
#define FILEWATCH_FSEVENT_FLAG_ITEM_CHANGE_OWNER  0x00004000u
#define FILEWATCH_FSEVENT_FLAG_ITEM_XATTR_MOD     0x00008000u
#define FILEWATCH_FSEVENT_FLAG_ITEM_IS_FILE       0x00010000u
#define FILEWATCH_FSEVENT_FLAG_ITEM_IS_DIR        0x00020000u
#define FILEWATCH_FSEVENT_FLAG_ITEM_IS_SYMLINK    0x00040000u

bool filewatch_map_fsevent_flags(u32 flags, FileWatchEventType *out_type,
                                 bool *out_needs_rescan);

/* Normalize an FSEvents callback path into the watched tree. Relative paths
 * are joined onto base_path, absolute paths are accepted only when they stay
 * inside base_path, and "." or "" resolves to base_path itself. */
bool filewatch_normalize_event_path(char *out, usize out_cap,
                                    const char *base_path,
                                    const char *event_path);
