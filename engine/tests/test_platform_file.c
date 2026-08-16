#include "test_framework.h"
#include <platform/file.h>
#include <stdio.h>
#include <stdlib.h>

TEST(mkdir_creates_directory) {
    char path[256];
    test_tmp(path, sizeof(path), "mkdir");
    ASSERT_FALSE(platform_file_exists(path));
    ASSERT_TRUE(platform_mkdir(path));
    ASSERT_TRUE(platform_file_exists(path));
    ASSERT_TRUE(platform_file_is_directory(path));
    ASSERT_FALSE(platform_file_is_regular(path));
}

TEST(file_size_matches_written_bytes) {
    char dir[256], path[512];
    test_tmp(dir, sizeof(dir), "size");
    platform_mkdir(dir);
    snprintf(path, sizeof(path), "%s/test.bin", dir);
    const char data[] = "hello platform";
    FILE *f = fopen(path, "wb");
    ASSERT_NOT_NULL(f);
    fwrite(data, 1, sizeof(data) - 1, f);
    fclose(f);
    u64 sz = 0;
    ASSERT_TRUE(platform_file_size(path, &sz));
    ASSERT_EQ(sz, (u64)(sizeof(data) - 1));
}

TEST(file_mtime_nonzero_after_write) {
    char dir[256], path[512];
    test_tmp(dir, sizeof(dir), "mtime");
    platform_mkdir(dir);
    snprintf(path, sizeof(path), "%s/a.txt", dir);
    FILE *f = fopen(path, "wb");
    ASSERT_NOT_NULL(f);
    fwrite("x", 1, 1, f);
    fclose(f);
    u64 mt = platform_file_mtime(path);
    ASSERT_NEQ(mt, 0u);
}

static struct {
    int file_count;
    int dir_count;
    char seen_subfile;
} g_visitor_state;

static void test_visitor(const char *rel_path, const char *abs_path,
                         bool is_directory, void *user) {
    (void)abs_path;
    (void)user;
    if (is_directory) {
        g_visitor_state.dir_count++;
    } else {
        g_visitor_state.file_count++;
        if (strcmp(rel_path, "sub/inner.txt") == 0)
            g_visitor_state.seen_subfile = 1;
    }
}

TEST(dir_foreach_visits_nested_entries) {
    char dir[256], sub[512], file[1024];
    test_tmp(dir, sizeof(dir), "foreach");
    platform_mkdir(dir);
    snprintf(sub, sizeof(sub), "%s/sub", dir);
    platform_mkdir(sub);
    snprintf(file, sizeof(file), "%s/inner.txt", sub);
    FILE *f = fopen(file, "wb");
    ASSERT_NOT_NULL(f);
    fwrite("x", 1, 1, f);
    fclose(f);
    char top[512];
    snprintf(top, sizeof(top), "%s/top.txt", dir);
    f = fopen(top, "wb");
    ASSERT_NOT_NULL(f);
    fwrite("y", 1, 1, f);
    fclose(f);

    memset(&g_visitor_state, 0, sizeof(g_visitor_state));
    ASSERT_TRUE(platform_dir_foreach(dir, "", test_visitor, NULL));
    ASSERT_EQ(g_visitor_state.file_count, 2);
    ASSERT_EQ(g_visitor_state.dir_count, 1);
    ASSERT_EQ(g_visitor_state.seen_subfile, 1);
}

TEST_MAIN_BEGIN()
    RUN_TEST(mkdir_creates_directory);
    RUN_TEST(file_size_matches_written_bytes);
    RUN_TEST(file_mtime_nonzero_after_write);
    RUN_TEST(dir_foreach_visits_nested_entries);
TEST_MAIN_END()
