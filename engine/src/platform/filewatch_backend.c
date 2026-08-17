#include <platform/filewatch_backend.h>
#include <string.h>

#define FILEWATCH_FSEVENT_RESCAN_FLAGS \
    (FILEWATCH_FSEVENT_FLAG_MUST_SCAN_SUBDIRS | \
     FILEWATCH_FSEVENT_FLAG_USER_DROPPED | \
     FILEWATCH_FSEVENT_FLAG_KERNEL_DROPPED | \
     FILEWATCH_FSEVENT_FLAG_ROOT_CHANGED | \
     FILEWATCH_FSEVENT_FLAG_MOUNT | \
     FILEWATCH_FSEVENT_FLAG_UNMOUNT)

#define FILEWATCH_FSEVENT_MODIFY_FLAGS \
    (FILEWATCH_FSEVENT_FLAG_ITEM_MODIFIED | \
     FILEWATCH_FSEVENT_FLAG_ITEM_INODE_META_MOD | \
     FILEWATCH_FSEVENT_FLAG_ITEM_FINDER_INFO_MOD | \
     FILEWATCH_FSEVENT_FLAG_ITEM_CHANGE_OWNER | \
     FILEWATCH_FSEVENT_FLAG_ITEM_XATTR_MOD | \
     FILEWATCH_FSEVENT_FLAG_ITEM_RENAMED)

FileWatchBackend filewatch_select_backend(u32 file_count, u32 dir_count,
                                           u32 max_depth) {
    if (max_depth >= FILEWATCH_FSEVENTS_MIN_DEPTH) {
        return FILEWATCH_BACKEND_FSEVENTS;
    }
    if (file_count >= FILEWATCH_FSEVENTS_MIN_FILES) {
        return FILEWATCH_BACKEND_FSEVENTS;
    }

    if (UINT32_MAX - file_count < dir_count) {
        return FILEWATCH_BACKEND_FSEVENTS;
    }

    u32 watch_count = file_count + dir_count;
    if (watch_count > FILEWATCH_FSEVENTS_MAX_KQUEUE_WATCHES) {
        return FILEWATCH_BACKEND_FSEVENTS;
    }
    return FILEWATCH_BACKEND_KQUEUE;
}

bool filewatch_map_fsevent_flags(u32 flags, FileWatchEventType *out_type,
                                 bool *out_needs_rescan) {
    if (!out_type || !out_needs_rescan) return false;

    *out_type = FW_EVENT_MODIFIED;
    *out_needs_rescan = (flags & FILEWATCH_FSEVENT_RESCAN_FLAGS) != 0u;

    if (flags & FILEWATCH_FSEVENT_FLAG_ITEM_CREATED) {
        *out_type = FW_EVENT_CREATED;
        return true;
    }
    if (flags & FILEWATCH_FSEVENT_FLAG_ITEM_REMOVED) {
        *out_type = FW_EVENT_DELETED;
        return true;
    }
    if (flags & FILEWATCH_FSEVENT_MODIFY_FLAGS) {
        *out_type = FW_EVENT_MODIFIED;
        return true;
    }
    if (*out_needs_rescan) return true;

    return false;
}

static bool fw_path_is_separator(char c) {
    return c == '/' || c == '\\';
}

static usize fw_path_trim_base_len(const char *path) {
    usize len = strlen(path);
    while (len > 1u && fw_path_is_separator(path[len - 1u])) {
        len--;
    }
    return len;
}

static bool fw_path_is_within(const char *base, usize base_len,
                              const char *path) {
    if (base_len == 0u) return true;
    if (memcmp(base, path, base_len) != 0) return false;
    if (path[base_len] == '\0') return true;
    return fw_path_is_separator(path[base_len]);
}

static bool fw_path_has_parent_segment(const char *path) {
    usize start = 0u;
    for (usize i = 0u;; i++) {
        if (path[i] != '\0' && !fw_path_is_separator(path[i])) continue;

        usize len = i - start;
        if (len == 2u && path[start] == '.' && path[start + 1u] == '.') {
            return true;
        }
        if (path[i] == '\0') break;
        start = i + 1u;
    }
    return false;
}

bool filewatch_normalize_event_path(char *out, usize out_cap,
                                    const char *base_path,
                                    const char *event_path) {
    if (!out || out_cap == 0u || !base_path || !event_path) return false;

    usize base_len = fw_path_trim_base_len(base_path);
    if (base_len >= out_cap) return false;

    if (event_path[0] == '\0' || strcmp(event_path, ".") == 0) {
        memcpy(out, base_path, base_len);
        out[base_len] = '\0';
        return true;
    }

    if (fw_path_has_parent_segment(event_path)) return false;

    if (event_path[0] == '/' || event_path[0] == '\\') {
        usize event_len = strlen(event_path);
        if (event_len >= out_cap) return false;

        bool root_base = base_len == 1u && fw_path_is_separator(base_path[0]);
        if (!root_base && !fw_path_is_within(base_path, base_len, event_path)) {
            return false;
        }

        memcpy(out, event_path, event_len + 1u);
        return true;
    }

    usize event_len = strlen(event_path);
    if (base_len == 1u && fw_path_is_separator(base_path[0])) {
        usize total_len = base_len + event_len;
        if (total_len >= out_cap) return false;

        out[0] = '/';
        memcpy(out + 1u, event_path, event_len + 1u);
        return true;
    }

    usize total_len = base_len + 1u + event_len;
    if (total_len >= out_cap) return false;

    memcpy(out, base_path, base_len);
    out[base_len] = '/';
    memcpy(out + base_len + 1u, event_path, event_len + 1u);
    return true;
}
