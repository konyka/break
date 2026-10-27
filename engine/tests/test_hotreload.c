#include "test_framework.h"
#include <asset/hotreload.h>
#include <core/shader_io.h>
#include <stdio.h>
#include <string.h>
#if !defined(ENGINE_PLATFORM_WINDOWS)
#include <fcntl.h>
#include <sys/stat.h>
#include <time.h>
#include <unistd.h>
#include <utime.h>
#endif

static RHIShader  s_shader  = {1, 1};
static RHIPipeline s_pipe   = {1, 1};
static RHITexture s_tex     = {1, 1};

RHIShader rhi_shader_create(RHIDevice *dev, const char *src, usize len, bool is_frag) {
    (void)dev; (void)src; (void)len; (void)is_frag;
    return s_shader;
}
void rhi_shader_destroy(RHIDevice *dev, RHIShader sh) { (void)dev; (void)sh; }
RHIPipeline rhi_pipeline_create(RHIDevice *dev, const RHIPipelineDesc *desc) {
    (void)dev; (void)desc;
    return s_pipe;
}
void rhi_pipeline_destroy(RHIDevice *dev, RHIPipeline p) { (void)dev; (void)p; }
RHITexture rhi_texture_create(RHIDevice *dev, const RHITextureDesc *desc) {
    (void)dev; (void)desc;
    return s_tex;
}
void rhi_texture_destroy(RHIDevice *dev, RHITexture t) { (void)dev; (void)t; }

static bool write_file(const char *path, long size, char fill) {
    FILE *f = fopen(path, "wb");
    if (!f) return false;
    for (long i = 0; i < size; i++) fputc(fill, f);
    fclose(f);
    return true;
}

/* R393: read_file had no size cap — multi-GB shader path could malloc before compile. */
TEST(hotreload_rejects_oversized_shader)
{
    /* R444: per-pid paths — parallel ctest trees raced on the fixed names. */
    char TMP_VERT[64], TMP_FRAG[64];
    test_tmp(TMP_VERT, sizeof TMP_VERT, "test_hotreload.vert");
    test_tmp(TMP_FRAG, sizeof TMP_FRAG, "test_hotreload.frag");

    ASSERT_TRUE(write_file(TMP_VERT, (long)SHADER_MAX_FILE_BYTES + 1, 'x'));
    ASSERT_TRUE(write_file(TMP_FRAG, 16, '#'));

    HotReloadPipeline hr;
    ASSERT_TRUE(!hotreload_pipeline_init(&hr, NULL, TMP_VERT, TMP_FRAG, NULL));
    remove(TMP_VERT);
    remove(TMP_FRAG);
}

/* R471: texture reload persists its source identity in path[256]; accepting
 * a longer input would watch and reload the truncated, unrelated pathname. */
TEST(hotreload_texture_rejects_path_truncation)
{
    HotReloadTexture hr = {0};
    RHITexture target = s_tex;
    char path[257];
    memset(path, 'x', sizeof(path) - 1u);
    path[sizeof(path) - 1u] = '\0';

    ASSERT_TRUE(!hotreload_texture_init(&hr, (RHIDevice *)(usize)1, path, &target));
    ASSERT_FALSE(hr.ready);
}

/* R487: a failed texture init leaves the watcher zeroed; shutdown must not
 * treat that zero as an inotify descriptor and close the caller's stdin. */
TEST(hotreload_texture_failed_init_keeps_stdin)
{
#if defined(ENGINE_PLATFORM_WINDOWS)
    /* Linux filewatchers use an integer descriptor; Windows uses handles. */
#else
    int saved_stdin = dup(STDIN_FILENO);
    ASSERT_TRUE(saved_stdin >= 0);
    int probe = open("/dev/null", O_RDONLY);
    ASSERT_TRUE(probe >= 0);
    ASSERT_EQ(dup2(probe, STDIN_FILENO), STDIN_FILENO);
    close(probe);

    HotReloadTexture hr = {0};
    hotreload_texture_shutdown(&hr);
    ASSERT_TRUE(fcntl(STDIN_FILENO, F_GETFD) >= 0);

    ASSERT_EQ(dup2(saved_stdin, STDIN_FILENO), STDIN_FILENO);
    close(saved_stdin);
#endif
}

/* R472: callbacks recompile from the paths persisted in HotReloadPipeline.
 * A successful initial compile must not leave them as truncated identities. */
TEST(hotreload_pipeline_rejects_path_truncation)
{
#if defined(ENGINE_PLATFORM_WINDOWS)
    /* Win32 CRT cannot create a 256-character basename reliably on all
     * configured temp roots; the path-field guard is covered by the texture
     * and filewatch tests below. */
    return;
#else
    char vert[257], frag[257];
    char tmp[256];
    test_tmp(tmp, sizeof tmp, "hr_long");
    for (char *c = tmp; *c; c++) if (*c == '\\') *c = '/';
    ASSERT_EQ(TEST_MKDIR(tmp), 0);
    usize t = strlen(tmp);
    ASSERT_TRUE(t > 0 && t < 256);
    memcpy(vert, tmp, t);
    vert[t++] = '/';
    memset(vert + t, 'v', sizeof(vert) - t - 1u);
    vert[256] = '\0';
    t = strlen(tmp);
    memcpy(frag, tmp, t);
    frag[t++] = '/';
    memset(frag + t, 'f', sizeof(frag) - t - 1u);
    frag[256] = '\0';
    ASSERT_EQ(strlen(vert), sizeof(vert) - 1u);
    ASSERT_EQ(strlen(frag), sizeof(frag) - 1u);
    ASSERT_TRUE(write_file(vert, 16, '#'));
    ASSERT_TRUE(write_file(frag, 16, '#'));

    HotReloadPipeline hr = {0};
    bool initialized = hotreload_pipeline_init(&hr, (RHIDevice *)(usize)1,
                                               vert, frag, NULL);
    if (initialized) hotreload_pipeline_shutdown(&hr);
    ASSERT_FALSE(initialized);
    ASSERT_FALSE(hr.ready);
    remove(vert);
    remove(frag);
    ASSERT_EQ(TEST_RMDIR(tmp), 0);
#endif
}

/* R473: FileWatcher polls the persisted entry path, so it must not retain a
 * truncated source path as a live entry. */
TEST(filewatch_rejects_path_truncation)
{
    FileWatcher watcher;
    char path[FILEWATCH_MAX_PATH + 1u];
    memset(path, 'x', sizeof(path) - 1u);
    path[sizeof(path) - 1u] = '\0';

    filewatch_init(&watcher);
    filewatch_add(&watcher, path, NULL, NULL);
    ASSERT_EQ(watcher.count, 0u);
    filewatch_shutdown(&watcher);
}

static int s_fw_calls[2];
static void fw_count_cb(const char *path, void *user) {
    (void)path;
    (*(int *)user)++;
}

#if !defined(ENGINE_PLATFORM_WINDOWS)
static void fw_set_mtime(const char *path, long offset) {
    struct stat st;
    struct utimbuf t;
    ASSERT_EQ(stat(path, &st), 0);
    t.actime = st.st_atime;
    t.modtime = time(NULL) + offset;
    ASSERT_EQ(utime(path, &t), 0);
}
#endif

/* filewatch_add keeps its historical rule (deletion is silent);
 * filewatch_add_with_missing additionally reports existing -> missing once,
 * and both report the file reappearing. */
TEST(filewatch_delete_notify_is_opt_in)
{
#if defined(ENGINE_PLATFORM_WINDOWS)
    /* mtime forcing needs utime(); Windows keeps the shared rule untested. */
    return;
#else
    char legacy[64], opt_in[64];
    FileWatcher w;
    test_tmp(legacy, sizeof legacy, "fw_legacy.txt");
    test_tmp(opt_in, sizeof opt_in, "fw_optin.txt");
    ASSERT_TRUE(write_file(legacy, 4, 'a'));
    ASSERT_TRUE(write_file(opt_in, 4, 'b'));
    fw_set_mtime(legacy, 100);
    fw_set_mtime(opt_in, 100);
    s_fw_calls[0] = s_fw_calls[1] = 0;

    filewatch_init(&w);
    filewatch_add(&w, legacy, fw_count_cb, &s_fw_calls[0]);
    filewatch_add_with_missing(&w, opt_in, fw_count_cb, &s_fw_calls[1]);
    ASSERT_EQ(w.count, 2u);
    ASSERT_FALSE(w.entries[0].notify_missing);
    ASSERT_TRUE(w.entries[1].notify_missing);

    ASSERT_EQ(remove(legacy), 0);
    ASSERT_EQ(remove(opt_in), 0);
    filewatch_poll(&w);
    filewatch_poll(&w); /* already missing: no repeat */
    ASSERT_EQ(s_fw_calls[0], 0);
    ASSERT_EQ(s_fw_calls[1], 1);

    ASSERT_TRUE(write_file(legacy, 4, 'c'));
    ASSERT_TRUE(write_file(opt_in, 4, 'd'));
    fw_set_mtime(legacy, 200);
    fw_set_mtime(opt_in, 200);
    filewatch_poll(&w);
    ASSERT_EQ(s_fw_calls[0], 1);
    ASSERT_EQ(s_fw_calls[1], 2);

    /* bounded: NULL watcher and over-long paths are rejected */
    filewatch_add_with_missing(NULL, opt_in, fw_count_cb, NULL);
    {
        char longp[FILEWATCH_MAX_PATH + 1u];
        memset(longp, 'x', sizeof(longp) - 1u);
        longp[sizeof(longp) - 1u] = '\0';
        filewatch_add_with_missing(&w, longp, fw_count_cb, NULL);
        ASSERT_EQ(w.count, 2u);
    }
    filewatch_shutdown(&w);
    remove(legacy);
    remove(opt_in);
#endif
}

TEST_MAIN_BEGIN()
    RUN_TEST(filewatch_delete_notify_is_opt_in);
    RUN_TEST(hotreload_rejects_oversized_shader);
    RUN_TEST(hotreload_texture_rejects_path_truncation);
    RUN_TEST(hotreload_texture_failed_init_keeps_stdin);
    RUN_TEST(hotreload_pipeline_rejects_path_truncation);
    RUN_TEST(filewatch_rejects_path_truncation);
TEST_MAIN_END()
