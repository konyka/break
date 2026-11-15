#include "test_framework.h"

#include <editor/editor_plugin_manifest.h>

#include <stdio.h>
#include <string.h>
#if !defined(_WIN32)
#include <sys/stat.h>
#endif

#define HASH_A "00112233445566778899aabbccddeeff00112233445566778899AABBCCDDEEFF"

static BreakEditorPluginManifest g_manifest;

static BreakEditorPluginManifestStatus parse(const char *text, const char *base, u32 *line)
{
    return break_editor_plugin_manifest_parse(text, strlen(text), base, &g_manifest, line);
}

TEST(manifest_parses_entries_comments_and_crlf)
{
    const char *text =
        "# editor plugins\r\n"
        "\r\n"
        "  plugin tools-a " HASH_A " /opt/plugins/libtools_a.so\r\n"
        "plugin\ttools-b\t" HASH_A "\tplugins/my tools/libb.so  \n"
        "# trailing comment";
    u32 line = 99u;
    ASSERT_EQ(parse(text, "/home/u/project", &line), BREAK_EDITOR_PLUGIN_MANIFEST_OK);
    ASSERT_EQ(line, 0u);
    ASSERT_EQ(g_manifest.count, 2u);
    ASSERT_STR_EQ(g_manifest.entries[0].build_id, "tools-a");
    ASSERT_STR_EQ(g_manifest.entries[0].path, "/opt/plugins/libtools_a.so");
    ASSERT_EQ(g_manifest.entries[0].sha256[0], 0x00u);
    ASSERT_EQ(g_manifest.entries[0].sha256[1], 0x11u);
    ASSERT_EQ(g_manifest.entries[0].sha256[10], 0xaau);
    ASSERT_EQ(g_manifest.entries[0].sha256[15], 0xffu);
    ASSERT_EQ(g_manifest.entries[0].sha256[26], 0xaau);
    ASSERT_EQ(g_manifest.entries[0].sha256[31], 0xffu);
    ASSERT_STR_EQ(g_manifest.entries[1].build_id, "tools-b");
    ASSERT_STR_EQ(g_manifest.entries[1].path, "/home/u/project/plugins/my tools/libb.so");
}

TEST(manifest_path_joining)
{
    ASSERT_EQ(parse("plugin a " HASH_A " x.so", "/base/", NULL), BREAK_EDITOR_PLUGIN_MANIFEST_OK);
    ASSERT_STR_EQ(g_manifest.entries[0].path, "/base/x.so");
    ASSERT_EQ(parse("plugin a " HASH_A " plugins/x.so", NULL, NULL),
              BREAK_EDITOR_PLUGIN_MANIFEST_OK);
    ASSERT_STR_EQ(g_manifest.entries[0].path, "plugins/x.so");
    ASSERT_EQ(parse("plugin a " HASH_A " plugins/x.so", "", NULL),
              BREAK_EDITOR_PLUGIN_MANIFEST_OK);
    ASSERT_STR_EQ(g_manifest.entries[0].path, "plugins/x.so");
    ASSERT_EQ(parse("plugin a " HASH_A " C:\\p\\x.dll\n"
                    "plugin b " HASH_A " D:/p/x.dll\n"
                    "plugin c " HASH_A " \\\\server\\p\\x.dll",
                    "/base", NULL),
              BREAK_EDITOR_PLUGIN_MANIFEST_OK);
    ASSERT_EQ(g_manifest.count, 3u);
    ASSERT_STR_EQ(g_manifest.entries[0].path, "C:\\p\\x.dll");
    ASSERT_STR_EQ(g_manifest.entries[1].path, "D:/p/x.dll");
    ASSERT_STR_EQ(g_manifest.entries[2].path, "\\\\server\\p\\x.dll");
    ASSERT_EQ(parse("# only comments\n\n   \n", "/base", NULL), BREAK_EDITOR_PLUGIN_MANIFEST_OK);
    ASSERT_EQ(g_manifest.count, 0u);
}

static void expect_reject(const char *text, BreakEditorPluginManifestStatus want, u32 want_line)
{
    u32 line = 0u;
    ASSERT_EQ(parse("plugin seed " HASH_A " /seed.so", NULL, NULL),
              BREAK_EDITOR_PLUGIN_MANIFEST_OK);
    ASSERT_EQ(parse(text, "/base", &line), want);
    ASSERT_EQ(line, want_line);
    ASSERT_EQ(g_manifest.count, 0u);
}

TEST(manifest_rejects_bad_lines)
{
    char long_id[80];
    memset(long_id, 'i', 64u);
    long_id[64] = '\0';
    char text[256];

    expect_reject("load a " HASH_A " x.so", BREAK_EDITOR_PLUGIN_MANIFEST_SYNTAX, 1u);
    expect_reject("# ok\nplugin", BREAK_EDITOR_PLUGIN_MANIFEST_BAD_BUILD_ID, 2u);
    snprintf(text, sizeof text, "plugin %s " HASH_A " x.so", long_id);
    expect_reject(text, BREAK_EDITOR_PLUGIN_MANIFEST_BAD_BUILD_ID, 1u);
    expect_reject("plugin a\x7f " HASH_A " x.so", BREAK_EDITOR_PLUGIN_MANIFEST_BAD_BUILD_ID, 1u);
    expect_reject("plugin a\x01 " HASH_A " x.so", BREAK_EDITOR_PLUGIN_MANIFEST_BAD_BUILD_ID, 1u);
    expect_reject("plugin a~ " HASH_A " x.so\nplugin b\x80 " HASH_A " y.so",
                  BREAK_EDITOR_PLUGIN_MANIFEST_BAD_BUILD_ID, 2u);
    expect_reject("plugin a", BREAK_EDITOR_PLUGIN_MANIFEST_BAD_HASH, 1u);
    expect_reject("plugin a 0011 x.so", BREAK_EDITOR_PLUGIN_MANIFEST_BAD_HASH, 1u);
    expect_reject("plugin a " HASH_A "0 x.so", BREAK_EDITOR_PLUGIN_MANIFEST_BAD_HASH, 1u);
    expect_reject("plugin a g0112233445566778899aabbccddeeff00112233445566778899aabbccddeeff x.so",
                  BREAK_EDITOR_PLUGIN_MANIFEST_BAD_HASH, 1u);
    expect_reject("plugin a 0011223344556677889-aabbccddeeff00112233445566778899aabbccddeeff x.so",
                  BREAK_EDITOR_PLUGIN_MANIFEST_BAD_HASH, 1u);
    expect_reject("plugin a " HASH_A, BREAK_EDITOR_PLUGIN_MANIFEST_BAD_PATH, 1u);
    expect_reject("plugin a " HASH_A "   \r\n", BREAK_EDITOR_PLUGIN_MANIFEST_BAD_PATH, 1u);
    expect_reject("\nplugin a " HASH_A " x\x01.so", BREAK_EDITOR_PLUGIN_MANIFEST_BAD_PATH, 2u);
    expect_reject("plugin a " HASH_A " x\x7f.so", BREAK_EDITOR_PLUGIN_MANIFEST_BAD_PATH, 1u);
    expect_reject("plugin a " HASH_A " x~\x80.so\nplugin b " HASH_A " x\x1f.so",
                  BREAK_EDITOR_PLUGIN_MANIFEST_BAD_PATH, 2u);
    expect_reject("plugin a " HASH_A " /p/x.so\n"
                  "plugin b " HASH_A " /q/y.so\n"
                  "plugin c " HASH_A " /p/x.so\n",
                  BREAK_EDITOR_PLUGIN_MANIFEST_DUPLICATE, 3u);
}

TEST(manifest_rejects_nul_full_and_long_paths)
{
    static char text[8192];
    static char base[700];
    static char path[700];
    u32 line = 0u;
    const char nul[] = "plugin a " HASH_A " x.so\n# x\0y\n";
    ASSERT_EQ(break_editor_plugin_manifest_parse(nul, sizeof nul - 1u, NULL, &g_manifest, &line),
              BREAK_EDITOR_PLUGIN_MANIFEST_SYNTAX);
    ASSERT_EQ(line, 2u);
    ASSERT_EQ(g_manifest.count, 0u);

    usize used = 0u;
    for (u32 i = 0u; i < BREAK_EDITOR_PLUGIN_MANIFEST_MAX; ++i) {
        used += (usize)snprintf(text + used, sizeof text - used, "plugin p%u " HASH_A " /p%u.so\n",
                                i, i);
    }
    ASSERT_EQ(parse(text, NULL, &line), BREAK_EDITOR_PLUGIN_MANIFEST_OK);
    ASSERT_EQ(g_manifest.count, BREAK_EDITOR_PLUGIN_MANIFEST_MAX);
    snprintf(text + used, sizeof text - used, "plugin extra " HASH_A " /extra.so\n");
    ASSERT_EQ(parse(text, NULL, &line), BREAK_EDITOR_PLUGIN_MANIFEST_FULL);
    ASSERT_EQ(line, BREAK_EDITOR_PLUGIN_MANIFEST_MAX + 1u);
    ASSERT_EQ(g_manifest.count, 0u);

    memset(base, 'b', 600u);
    base[0] = '/';
    base[600] = '\0';
    memset(path, 'p', 600u);
    path[600] = '\0';
    snprintf(text, sizeof text, "plugin a " HASH_A " %s", path);
    ASSERT_EQ(parse(text, NULL, &line), BREAK_EDITOR_PLUGIN_MANIFEST_OK);
    ASSERT_EQ(parse(text, base, &line), BREAK_EDITOR_PLUGIN_MANIFEST_BAD_PATH);
    ASSERT_EQ(line, 1u);

    ASSERT_EQ(break_editor_plugin_manifest_parse(NULL, 0u, NULL, &g_manifest, &line),
              BREAK_EDITOR_PLUGIN_MANIFEST_INVALID);
    ASSERT_EQ(break_editor_plugin_manifest_parse("", 0u, NULL, NULL, &line),
              BREAK_EDITOR_PLUGIN_MANIFEST_INVALID);
}

typedef struct FakeLoader {
    BreakEditorPluginHost *host;
    u32 calls;
} FakeLoader;

static bool fake_cmd(void *user, BreakEditorDoc *doc)
{
    (void)user;
    (void)doc;
    return true;
}

/* Adds one command per entry, then succeeds only for build ids "ok*". */
static bool fake_load(void *user, const BreakEditorPluginManifestEntry *entry)
{
    FakeLoader *fake = (FakeLoader *)user;
    const BreakEditorPluginApi *api = break_editor_plugin_host_api(fake->host);
    char id[BREAK_EDITOR_PLUGIN_CMD_ID_CAPACITY + BREAK_EDITOR_PLUGIN_MANIFEST_BUILD_ID_CAPACITY];
    fake->calls++;
    snprintf(id, sizeof id, "fake.%s", entry->build_id);
    if (api->add_command(api->host, id, entry->build_id, fake_cmd, NULL) !=
        BREAK_EDITOR_PLUGIN_CMD_OK) {
        return false;
    }
    return strncmp(entry->build_id, "ok", 2u) == 0;
}

TEST(manifest_load_all_tracks_owners_and_drops_failed_commands)
{
    BreakEditorPluginCmds *cmds = break_editor_plugin_cmds_create(8u);
    BreakEditorPluginHost *host = break_editor_plugin_host_create(cmds);
    BreakEditorPluginManifestReport report;
    FakeLoader fake = {host, 0u};
    ASSERT_NOT_NULL(host);
    ASSERT_EQ(parse("plugin ok1 " HASH_A " /a.so\n"
                    "plugin bad " HASH_A " /b.so\n"
                    "plugin ok2 " HASH_A " /c.so\n",
                    NULL, NULL),
              BREAK_EDITOR_PLUGIN_MANIFEST_OK);

    ASSERT_TRUE(break_editor_plugin_manifest_load_all(&g_manifest, host, fake_load, &fake,
                                                      &report));
    ASSERT_EQ(fake.calls, 3u);
    ASSERT_EQ(report.loaded, 2u);
    ASSERT_EQ(report.failed, 1u);
    ASSERT_TRUE(report.owners[0] != 0u);
    ASSERT_EQ(report.owners[1], 0u);
    ASSERT_TRUE(report.owners[2] != 0u);
    ASSERT_NEQ(report.owners[0], report.owners[2]);
    ASSERT_EQ(break_editor_plugin_cmds_count(cmds), 2u);
    ASSERT_EQ(break_editor_plugin_cmds_find(cmds, "fake.ok1"), 0u);
    ASSERT_EQ(break_editor_plugin_cmds_find(cmds, "fake.ok2"), 1u);
    ASSERT_EQ(break_editor_plugin_cmds_find(cmds, "fake.bad"), BREAK_EDITOR_PLUGIN_CMD_NONE);
    ASSERT_EQ(break_editor_plugin_cmds_owner(cmds, 0u), report.owners[0]);
    ASSERT_EQ(break_editor_plugin_cmds_owner(cmds, 1u), report.owners[2]);
    ASSERT_EQ(break_editor_plugin_host_release(host, report.owners[2]), 1u);
    ASSERT_EQ(break_editor_plugin_cmds_count(cmds), 1u);

    /* A window left open by the caller: nothing loads, every entry fails. */
    fake.calls = 0u;
    ASSERT_TRUE(break_editor_plugin_host_begin_load(host) != 0u);
    ASSERT_TRUE(break_editor_plugin_manifest_load_all(&g_manifest, host, fake_load, &fake,
                                                      &report));
    ASSERT_EQ(fake.calls, 0u);
    ASSERT_EQ(report.loaded, 0u);
    ASSERT_EQ(report.failed, 3u);
    ASSERT_EQ(report.owners[0], 0u);
    ASSERT_TRUE(break_editor_plugin_host_end_load(host, false));

    ASSERT_FALSE(break_editor_plugin_manifest_load_all(NULL, host, fake_load, &fake, &report));
    ASSERT_FALSE(break_editor_plugin_manifest_load_all(&g_manifest, NULL, fake_load, &fake,
                                                       &report));
    ASSERT_FALSE(break_editor_plugin_manifest_load_all(&g_manifest, host, NULL, &fake, &report));
    ASSERT_FALSE(break_editor_plugin_manifest_load_all(&g_manifest, host, fake_load, &fake, NULL));

    break_editor_plugin_host_destroy(host);
    break_editor_plugin_cmds_destroy(cmds);
}

TEST(manifest_status_names)
{
    ASSERT_STR_EQ(break_editor_plugin_manifest_status_name(BREAK_EDITOR_PLUGIN_MANIFEST_OK), "ok");
    ASSERT_STR_EQ(break_editor_plugin_manifest_status_name(BREAK_EDITOR_PLUGIN_MANIFEST_INVALID),
                  "invalid");
    ASSERT_STR_EQ(break_editor_plugin_manifest_status_name(BREAK_EDITOR_PLUGIN_MANIFEST_SYNTAX),
                  "syntax");
    ASSERT_STR_EQ(
        break_editor_plugin_manifest_status_name(BREAK_EDITOR_PLUGIN_MANIFEST_BAD_BUILD_ID),
        "bad build id");
    ASSERT_STR_EQ(break_editor_plugin_manifest_status_name(BREAK_EDITOR_PLUGIN_MANIFEST_BAD_HASH),
                  "bad sha256");
    ASSERT_STR_EQ(break_editor_plugin_manifest_status_name(BREAK_EDITOR_PLUGIN_MANIFEST_BAD_PATH),
                  "bad path");
    ASSERT_STR_EQ(
        break_editor_plugin_manifest_status_name(BREAK_EDITOR_PLUGIN_MANIFEST_DUPLICATE),
        "duplicate path");
    ASSERT_STR_EQ(break_editor_plugin_manifest_status_name(BREAK_EDITOR_PLUGIN_MANIFEST_FULL),
                  "too many entries");
    ASSERT_STR_EQ(break_editor_plugin_manifest_status_name(BREAK_EDITOR_PLUGIN_MANIFEST_IO),
                  "cannot read file");
    ASSERT_STR_EQ(
        break_editor_plugin_manifest_status_name(BREAK_EDITOR_PLUGIN_MANIFEST_TOO_LARGE),
        "file too large");
    ASSERT_STR_EQ(break_editor_plugin_manifest_status_name(
                      (BreakEditorPluginManifestStatus)(BREAK_EDITOR_PLUGIN_MANIFEST_TOO_LARGE + 1)),
                  "unknown");
    ASSERT_STR_EQ(break_editor_plugin_manifest_status_name((BreakEditorPluginManifestStatus)-1),
                  "unknown");
}

static void write_text(const char *path, const char *text, usize size)
{
    FILE *f = fopen(path, "wb");
    ASSERT_NOT_NULL(f);
    ASSERT_EQ(fwrite(text, 1u, size, f), size);
    ASSERT_EQ(fclose(f), 0);
}

TEST(manifest_read_file_joins_to_the_manifest_directory)
{
    char path[640];
    char dir[640];
    char want[700];
    u32 line = 99u;
    const char *text = "plugin a " HASH_A " libs/a.so\nplugin b " HASH_A " /abs/b.so\n";
    test_tmp(path, sizeof path, "editor_plugin_manifest.txt");
    write_text(path, text, strlen(text));
    snprintf(dir, sizeof dir, "%s", path);
    char *slash = strrchr(dir, '/');
    ASSERT_NOT_NULL(slash);
    *slash = '\0';
    snprintf(want, sizeof want, "%s/libs/a.so", dir);

    ASSERT_EQ(break_editor_plugin_manifest_read_file(path, &g_manifest, &line),
              BREAK_EDITOR_PLUGIN_MANIFEST_OK);
    ASSERT_EQ(line, 0u);
    ASSERT_EQ(g_manifest.count, 2u);
    ASSERT_STR_EQ(g_manifest.entries[0].path, want);
    ASSERT_STR_EQ(g_manifest.entries[1].path, "/abs/b.so");

    const char *bad = "# ok\nplugin a " HASH_A " a.so\nplugin a nothex x.so\n";
    write_text(path, bad, strlen(bad));
    ASSERT_EQ(break_editor_plugin_manifest_read_file(path, &g_manifest, &line),
              BREAK_EDITOR_PLUGIN_MANIFEST_BAD_HASH);
    ASSERT_EQ(line, 3u);
    ASSERT_EQ(g_manifest.count, 0u);

    ASSERT_EQ(break_editor_plugin_manifest_read_file(path, &g_manifest, NULL),
              BREAK_EDITOR_PLUGIN_MANIFEST_BAD_HASH);
    ASSERT_EQ(remove(path), 0);
}

TEST(manifest_read_file_without_directory_keeps_relative_paths)
{
    char name[96];
    u32 line = 0u;
    const char *text = "plugin a " HASH_A " a.so\n";
    snprintf(name, sizeof name, "editor_plugin_manifest_%d.txt", (int)TEST_GETPID());
    write_text(name, text, strlen(text));
    ASSERT_EQ(break_editor_plugin_manifest_read_file(name, &g_manifest, &line),
              BREAK_EDITOR_PLUGIN_MANIFEST_OK);
    ASSERT_EQ(g_manifest.count, 1u);
    ASSERT_STR_EQ(g_manifest.entries[0].path, "a.so");
    ASSERT_EQ(remove(name), 0);
}

TEST(manifest_read_file_rejects_missing_large_and_null)
{
    static char big[BREAK_EDITOR_PLUGIN_MANIFEST_FILE_MAX + 1u];
    char path[640];
    u32 line = 7u;
    ASSERT_EQ(parse("plugin seed " HASH_A " /seed.so", NULL, NULL),
              BREAK_EDITOR_PLUGIN_MANIFEST_OK);
    test_tmp(path, sizeof path, "editor_plugin_manifest_missing.txt");
    (void)remove(path);
    ASSERT_EQ(break_editor_plugin_manifest_read_file(path, &g_manifest, &line),
              BREAK_EDITOR_PLUGIN_MANIFEST_IO);
    ASSERT_EQ(line, 0u);
    ASSERT_EQ(g_manifest.count, 0u);

    memset(big, '#', sizeof big);
    test_tmp(path, sizeof path, "editor_plugin_manifest_big.txt");
    write_text(path, big, BREAK_EDITOR_PLUGIN_MANIFEST_FILE_MAX);
    ASSERT_EQ(break_editor_plugin_manifest_read_file(path, &g_manifest, &line),
              BREAK_EDITOR_PLUGIN_MANIFEST_OK);
    ASSERT_EQ(g_manifest.count, 0u);
    ASSERT_EQ(parse("plugin seed " HASH_A " /seed.so", NULL, NULL),
              BREAK_EDITOR_PLUGIN_MANIFEST_OK);
    line = 7u;
    write_text(path, big, sizeof big);
    ASSERT_EQ(break_editor_plugin_manifest_read_file(path, &g_manifest, &line),
              BREAK_EDITOR_PLUGIN_MANIFEST_TOO_LARGE);
    ASSERT_EQ(line, 0u);
    ASSERT_EQ(g_manifest.count, 0u);
    ASSERT_EQ(remove(path), 0);

    /* A directory opens on POSIX but fails to read; Windows refuses to open it. */
    char dir[640];
    test_tmp(dir, sizeof dir, "editor_plugin_manifest_dir");
    ASSERT_EQ(TEST_MKDIR(dir), 0);
    line = 7u;
    ASSERT_EQ(break_editor_plugin_manifest_read_file(dir, &g_manifest, &line),
              BREAK_EDITOR_PLUGIN_MANIFEST_IO);
    ASSERT_EQ(line, 0u);
    ASSERT_EQ(TEST_RMDIR(dir), 0);

    ASSERT_EQ(break_editor_plugin_manifest_read_file(NULL, &g_manifest, &line),
              BREAK_EDITOR_PLUGIN_MANIFEST_INVALID);
    ASSERT_EQ(break_editor_plugin_manifest_read_file(path, NULL, &line),
              BREAK_EDITOR_PLUGIN_MANIFEST_INVALID);
}

TEST(manifest_take_cli)
{
    char a0[] = "editor", a1[] = "--plugin-manifest", a2[] = "/p/one.txt", a3[] = "scene.bscn",
         a4[] = "--plugin-manifest=/p/two.txt", a5[] = "--plugin-manifests", a6[] = "--lang";
    char *argv[] = {a0, a1, a2, a3, a4, a5, a6, NULL};
    int argc = 7;
    const char *path = (const char *)1;
    char err[96];
    ASSERT_TRUE(break_editor_plugin_manifest_take_cli(&argc, argv, &path, err, sizeof err));
    ASSERT_STR_EQ(path, "/p/two.txt");
    ASSERT_EQ(argc, 4);
    ASSERT_STR_EQ(argv[0], "editor");
    ASSERT_STR_EQ(argv[1], "scene.bscn");
    ASSERT_STR_EQ(argv[2], "--plugin-manifests");
    ASSERT_STR_EQ(argv[3], "--lang");
    ASSERT_TRUE(argv[4] == NULL);

    char b0[] = "editor", b1[] = "x";
    char *none[] = {b0, b1, NULL};
    int none_argc = 2;
    path = (const char *)1;
    ASSERT_TRUE(break_editor_plugin_manifest_take_cli(&none_argc, none, &path, NULL, 0u));
    ASSERT_TRUE(path == NULL);
    ASSERT_EQ(none_argc, 2);
    ASSERT_STR_EQ(none[1], "x");

    char c0[] = "editor", c1[] = "x", c2[] = "--plugin-manifest";
    char *missing[] = {c0, c1, c2, NULL};
    int missing_argc = 3;
    err[0] = '\0';
    ASSERT_FALSE(
        break_editor_plugin_manifest_take_cli(&missing_argc, missing, &path, err, sizeof err));
    ASSERT_EQ(missing_argc, 3);
    ASSERT_STR_EQ(missing[1], "x");
    ASSERT_TRUE(strstr(err, "--plugin-manifest needs a path") != NULL);

    char d0[] = "editor", d1[] = "--plugin-manifest=", d2[] = "y";
    char *empty[] = {d0, d1, d2, NULL};
    int empty_argc = 3;
    err[0] = '\0';
    ASSERT_FALSE(break_editor_plugin_manifest_take_cli(&empty_argc, empty, &path, err, sizeof err));
    ASSERT_EQ(empty_argc, 3);
    ASSERT_STR_EQ(empty[1], "--plugin-manifest=");
    ASSERT_TRUE(strstr(err, "--plugin-manifest needs a path") != NULL);

    char e0[] = "editor", e1[] = "--plugin-manifest", e2[] = "";
    char *blank[] = {e0, e1, e2, NULL};
    int blank_argc = 3;
    ASSERT_FALSE(break_editor_plugin_manifest_take_cli(&blank_argc, blank, &path, NULL, 0u));
    ASSERT_EQ(blank_argc, 3);

    /* The value after a bare option is a path even when it looks like one. */
    char f0[] = "editor", f1[] = "--plugin-manifest", f2[] = "--plugin-manifest=/x";
    char *odd[] = {f0, f1, f2, NULL};
    int odd_argc = 3;
    ASSERT_TRUE(break_editor_plugin_manifest_take_cli(&odd_argc, odd, &path, NULL, 0u));
    ASSERT_STR_EQ(path, "--plugin-manifest=/x");
    ASSERT_EQ(odd_argc, 1);

    ASSERT_FALSE(break_editor_plugin_manifest_take_cli(NULL, argv, &path, err, sizeof err));
    ASSERT_FALSE(break_editor_plugin_manifest_take_cli(&argc, NULL, &path, err, sizeof err));
    ASSERT_FALSE(break_editor_plugin_manifest_take_cli(&argc, argv, NULL, err, sizeof err));
    int zero = 0;
    ASSERT_FALSE(break_editor_plugin_manifest_take_cli(&zero, argv, &path, err, sizeof err));
}

TEST_MAIN_BEGIN()
    RUN_TEST(manifest_parses_entries_comments_and_crlf);
    RUN_TEST(manifest_path_joining);
    RUN_TEST(manifest_rejects_bad_lines);
    RUN_TEST(manifest_rejects_nul_full_and_long_paths);
    RUN_TEST(manifest_load_all_tracks_owners_and_drops_failed_commands);
    RUN_TEST(manifest_status_names);
    RUN_TEST(manifest_read_file_joins_to_the_manifest_directory);
    RUN_TEST(manifest_read_file_without_directory_keeps_relative_paths);
    RUN_TEST(manifest_read_file_rejects_missing_large_and_null);
    RUN_TEST(manifest_take_cli);
TEST_MAIN_END()
