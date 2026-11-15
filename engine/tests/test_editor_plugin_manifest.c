#include "test_framework.h"

#include <editor/editor_plugin_manifest.h>

#include <stdio.h>
#include <string.h>

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

TEST_MAIN_BEGIN()
    RUN_TEST(manifest_parses_entries_comments_and_crlf);
    RUN_TEST(manifest_path_joining);
    RUN_TEST(manifest_rejects_bad_lines);
    RUN_TEST(manifest_rejects_nul_full_and_long_paths);
    RUN_TEST(manifest_load_all_tracks_owners_and_drops_failed_commands);
TEST_MAIN_END()
