#include "test_framework.h"
#include <platform/filewatch_backend.h>

TEST(small_tree_prefers_kqueue)
{
    ASSERT_EQ(filewatch_select_backend(10u, 3u, 2u),
              FILEWATCH_BACKEND_KQUEUE);
}

TEST(watch_limit_edge_prefers_kqueue)
{
    ASSERT_EQ(filewatch_select_backend(200u, 56u, 1u),
              FILEWATCH_BACKEND_KQUEUE);
}

TEST(watch_limit_overflow_prefers_fsevents)
{
    ASSERT_EQ(filewatch_select_backend(200u, 57u, 1u),
              FILEWATCH_BACKEND_FSEVENTS);
}

TEST(file_count_threshold_prefers_fsevents)
{
    ASSERT_EQ(filewatch_select_backend(512u, 0u, 1u),
              FILEWATCH_BACKEND_FSEVENTS);
}

TEST(depth_threshold_prefers_fsevents)
{
    ASSERT_EQ(filewatch_select_backend(1u, 1u, 8u),
              FILEWATCH_BACKEND_FSEVENTS);
}

TEST(depth_below_threshold_prefers_kqueue)
{
    ASSERT_EQ(filewatch_select_backend(1u, 1u, 7u),
              FILEWATCH_BACKEND_KQUEUE);
}

TEST(overflowing_counts_prefer_fsevents)
{
    ASSERT_EQ(filewatch_select_backend(UINT32_MAX, UINT32_MAX, 0u),
              FILEWATCH_BACKEND_FSEVENTS);
}

TEST(fsevent_must_scan_subdirs_requires_rescan)
{
    FileWatchEventType type = FW_EVENT_MODIFIED;
    bool rescan = false;
    ASSERT_TRUE(filewatch_map_fsevent_flags(
        FILEWATCH_FSEVENT_FLAG_MUST_SCAN_SUBDIRS, &type, &rescan));
    ASSERT_TRUE(rescan);
    ASSERT_EQ(type, FW_EVENT_MODIFIED);
}

TEST(fsevent_dropped_events_require_rescan)
{
    FileWatchEventType type = FW_EVENT_MODIFIED;
    bool rescan = false;
    ASSERT_TRUE(filewatch_map_fsevent_flags(
        FILEWATCH_FSEVENT_FLAG_USER_DROPPED |
        FILEWATCH_FSEVENT_FLAG_KERNEL_DROPPED, &type, &rescan));
    ASSERT_TRUE(rescan);
    ASSERT_EQ(type, FW_EVENT_MODIFIED);
}

TEST(fsevent_root_changed_requires_rescan)
{
    FileWatchEventType type = FW_EVENT_MODIFIED;
    bool rescan = false;
    ASSERT_TRUE(filewatch_map_fsevent_flags(
        FILEWATCH_FSEVENT_FLAG_ROOT_CHANGED, &type, &rescan));
    ASSERT_TRUE(rescan);
    ASSERT_EQ(type, FW_EVENT_MODIFIED);
}

TEST(fsevent_created_maps_to_created)
{
    FileWatchEventType type = FW_EVENT_MODIFIED;
    bool rescan = true;
    ASSERT_TRUE(filewatch_map_fsevent_flags(
        FILEWATCH_FSEVENT_FLAG_ITEM_CREATED, &type, &rescan));
    ASSERT_FALSE(rescan);
    ASSERT_EQ(type, FW_EVENT_CREATED);
}

TEST(fsevent_removed_maps_to_deleted)
{
    FileWatchEventType type = FW_EVENT_MODIFIED;
    bool rescan = true;
    ASSERT_TRUE(filewatch_map_fsevent_flags(
        FILEWATCH_FSEVENT_FLAG_ITEM_REMOVED, &type, &rescan));
    ASSERT_FALSE(rescan);
    ASSERT_EQ(type, FW_EVENT_DELETED);
}

TEST(fsevent_modified_maps_to_modified)
{
    FileWatchEventType type = FW_EVENT_MODIFIED;
    bool rescan = true;
    ASSERT_TRUE(filewatch_map_fsevent_flags(
        FILEWATCH_FSEVENT_FLAG_ITEM_MODIFIED |
        FILEWATCH_FSEVENT_FLAG_ITEM_INODE_META_MOD, &type, &rescan));
    ASSERT_FALSE(rescan);
    ASSERT_EQ(type, FW_EVENT_MODIFIED);
}

TEST(fsevent_item_event_with_scan_flag_keeps_rescan)
{
    FileWatchEventType type = FW_EVENT_MODIFIED;
    bool rescan = false;
    ASSERT_TRUE(filewatch_map_fsevent_flags(
        FILEWATCH_FSEVENT_FLAG_ITEM_CREATED |
        FILEWATCH_FSEVENT_FLAG_MUST_SCAN_SUBDIRS, &type, &rescan));
    ASSERT_TRUE(rescan);
    ASSERT_EQ(type, FW_EVENT_CREATED);
}

TEST(fsevent_history_only_flags_do_not_emit_event)
{
    FileWatchEventType type = FW_EVENT_MODIFIED;
    bool rescan = false;
    ASSERT_FALSE(filewatch_map_fsevent_flags(
        FILEWATCH_FSEVENT_FLAG_HISTORY_DONE |
        FILEWATCH_FSEVENT_FLAG_EVENT_IDS_WRAPPED, &type, &rescan));
    ASSERT_FALSE(rescan);
}

TEST(normalize_empty_event_path_returns_base)
{
    char out[FILEWATCH_MAX_PATH];
    ASSERT_TRUE(filewatch_normalize_event_path(out, sizeof(out),
                                               "/tmp/watch", ""));
    ASSERT_STR_EQ(out, "/tmp/watch");
}

TEST(normalize_dot_event_path_returns_base)
{
    char out[FILEWATCH_MAX_PATH];
    ASSERT_TRUE(filewatch_normalize_event_path(out, sizeof(out),
                                               "/tmp/watch/", "."));
    ASSERT_STR_EQ(out, "/tmp/watch");
}

TEST(normalize_relative_event_path_joins_base)
{
    char out[FILEWATCH_MAX_PATH];
    ASSERT_TRUE(filewatch_normalize_event_path(out, sizeof(out),
                                               "/tmp/watch", "src/main.c"));
    ASSERT_STR_EQ(out, "/tmp/watch/src/main.c");
}

TEST(normalize_relative_event_path_handles_base_slash)
{
    char out[FILEWATCH_MAX_PATH];
    ASSERT_TRUE(filewatch_normalize_event_path(out, sizeof(out),
                                               "/tmp/watch/", "src/main.c"));
    ASSERT_STR_EQ(out, "/tmp/watch/src/main.c");
}

TEST(normalize_absolute_event_path_inside_base_is_copied)
{
    char out[FILEWATCH_MAX_PATH];
    ASSERT_TRUE(filewatch_normalize_event_path(out, sizeof(out),
                                               "/tmp/watch", "/tmp/watch/src/main.c"));
    ASSERT_STR_EQ(out, "/tmp/watch/src/main.c");
}

TEST(normalize_absolute_event_path_equal_base_is_copied)
{
    char out[FILEWATCH_MAX_PATH];
    ASSERT_TRUE(filewatch_normalize_event_path(out, sizeof(out),
                                               "/tmp/watch", "/tmp/watch"));
    ASSERT_STR_EQ(out, "/tmp/watch");
}

TEST(normalize_absolute_event_path_outside_base_is_rejected)
{
    char out[FILEWATCH_MAX_PATH];
    ASSERT_FALSE(filewatch_normalize_event_path(out, sizeof(out),
                                                "/tmp/watch", "/tmp/other/file.c"));
}

TEST(normalize_root_base_joins_without_double_slash)
{
    char out[FILEWATCH_MAX_PATH];
    ASSERT_TRUE(filewatch_normalize_event_path(out, sizeof(out),
                                               "/", "tmp/watch.c"));
    ASSERT_STR_EQ(out, "/tmp/watch.c");
}

TEST(normalize_root_base_accepts_absolute_child)
{
    char out[FILEWATCH_MAX_PATH];
    ASSERT_TRUE(filewatch_normalize_event_path(out, sizeof(out),
                                               "/", "/tmp/watch.c"));
    ASSERT_STR_EQ(out, "/tmp/watch.c");
}

TEST(normalize_parent_traversal_is_rejected)
{
    char out[FILEWATCH_MAX_PATH];
    ASSERT_FALSE(filewatch_normalize_event_path(out, sizeof(out),
                                                "/tmp/watch", "../other/file.c"));
}

TEST(normalize_oversized_path_is_rejected)
{
    char out[FILEWATCH_MAX_PATH];
    char event_path[512];
    memset(event_path, 'a', sizeof(event_path) - 1);
    event_path[sizeof(event_path) - 1] = '\0';
    ASSERT_FALSE(filewatch_normalize_event_path(out, sizeof(out),
                                                "/tmp/watch", event_path));
}

TEST_MAIN_BEGIN()
    RUN_TEST(small_tree_prefers_kqueue);
    RUN_TEST(watch_limit_edge_prefers_kqueue);
    RUN_TEST(watch_limit_overflow_prefers_fsevents);
    RUN_TEST(file_count_threshold_prefers_fsevents);
    RUN_TEST(depth_threshold_prefers_fsevents);
    RUN_TEST(depth_below_threshold_prefers_kqueue);
    RUN_TEST(overflowing_counts_prefer_fsevents);
    RUN_TEST(fsevent_must_scan_subdirs_requires_rescan);
    RUN_TEST(fsevent_dropped_events_require_rescan);
    RUN_TEST(fsevent_root_changed_requires_rescan);
    RUN_TEST(fsevent_created_maps_to_created);
    RUN_TEST(fsevent_removed_maps_to_deleted);
    RUN_TEST(fsevent_modified_maps_to_modified);
    RUN_TEST(fsevent_item_event_with_scan_flag_keeps_rescan);
    RUN_TEST(fsevent_history_only_flags_do_not_emit_event);
    RUN_TEST(normalize_empty_event_path_returns_base);
    RUN_TEST(normalize_dot_event_path_returns_base);
    RUN_TEST(normalize_relative_event_path_joins_base);
    RUN_TEST(normalize_relative_event_path_handles_base_slash);
    RUN_TEST(normalize_absolute_event_path_inside_base_is_copied);
    RUN_TEST(normalize_absolute_event_path_equal_base_is_copied);
    RUN_TEST(normalize_absolute_event_path_outside_base_is_rejected);
    RUN_TEST(normalize_root_base_joins_without_double_slash);
    RUN_TEST(normalize_root_base_accepts_absolute_child);
    RUN_TEST(normalize_parent_traversal_is_rejected);
    RUN_TEST(normalize_oversized_path_is_rejected);
TEST_MAIN_END()
