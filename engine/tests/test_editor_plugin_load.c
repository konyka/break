#include "test_framework.h"

#include <crypto/break_crypto.h>
#include <editor/editor_cmd.h>
#include <editor/editor_components.h>
#include <editor/editor_doc.h>
#include <editor/editor_plugin_host.h>
#include <editor/editor_plugin_loader.h>
#include <editor/editor_plugin_manifest.h>
#include <system/break_plugin.h>

#include <stdio.h>
#include <string.h>

#define FIXTURE_COMPONENT_ID 100u
#define FIXTURE_ZH_PANEL_TITLE "\xe5\xa4\xb9\xe5\x85\xb7\xe9\x9d\xa2\xe6\x9d\xbf"
#define FIXTURE_ZH_HELLO "\xe5\xa4\xb9\xe5\x85\xb7\xe9\x97\xae\xe5\x80\x99"
#define FIXTURE_ZH_SECTION_TITLE "\xe5\xa4\xb9\xe5\x85\xb7\xe5\x88\x86\xe5\x8c\xba"
#define FIXTURE_ZH_SECTION_TEXT "\xe5\xa4\xb9\xe5\x85\xb7\xe5\x8c\xba\xe5\x9d\x97"

static bool hash_file(const char *path, u8 out[32])
{
    FILE *file = fopen(path, "rb");
    BreakCryptoSha256Ctx *ctx = NULL;
    u8 buffer[4096];
    bool ok = true;
    if (!file) {
        return false;
    }
    ctx = break_crypto_sha256_ctx_create();
    if (!ctx) {
        fclose(file);
        return false;
    }
    for (;;) {
        usize count = fread(buffer, 1u, sizeof(buffer), file);
        if (count && !break_crypto_sha256_update(ctx, buffer, count)) {
            ok = false;
        }
        if (!ok || count < sizeof(buffer)) {
            break;
        }
    }
    if (ferror(file) || !break_crypto_sha256_final(ctx, out)) {
        ok = false;
    }
    break_crypto_sha256_ctx_destroy(ctx);
    if (fclose(file) != 0) {
        ok = false;
    }
    return ok;
}

/* A real plugin library registers a command through the editor API; the
 * command runs from the registry with a doc; release + unload removes it. */
TEST(real_plugin_adds_and_removes_a_command)
{
    u8 digest[32];
    BreakPluginHandle handle;
    BreakEditorPluginCmds *cmds = break_editor_plugin_cmds_create(8u);
    BreakEditorPluginHost *host = break_editor_plugin_host_create(cmds);
    BreakEditorDoc *doc = break_editor_doc_create();
    ASSERT_NOT_NULL(cmds);
    ASSERT_NOT_NULL(host);
    ASSERT_NOT_NULL(doc);
    BreakPluginManager *manager =
        break_plugin_create(4u, (void *)break_editor_plugin_host_api(host));
    ASSERT_NOT_NULL(manager);
    ASSERT_TRUE(hash_file(EDITOR_TEST_PLUGIN_PATH, digest));

    u32 owner = break_editor_plugin_host_begin_load(host);
    ASSERT_TRUE(owner != 0u);
    BreakPluginStatus status = break_plugin_load(manager, EDITOR_TEST_PLUGIN_PATH,
                                                 "editor-test-plugin", digest, &handle);
    ASSERT_TRUE(break_editor_plugin_host_end_load(host, status == BREAK_PLUGIN_OK));
    ASSERT_EQ(status, BREAK_PLUGIN_OK);
    ASSERT_EQ(break_editor_plugin_cmds_count(cmds), 1u);
    u32 index = break_editor_plugin_cmds_find(cmds, "fixture.hello");
    ASSERT_EQ(index, 0u);
    ASSERT_STR_EQ(break_editor_plugin_cmds_label(cmds, index), "Fixture Hello");
    /* the plugin registered its zh-CN label through set_command_label */
    ASSERT_STR_EQ(break_editor_plugin_cmds_label_lang(cmds, index, BREAK_EDITOR_LANG_ZH_CN),
                  FIXTURE_ZH_HELLO);
    ASSERT_STR_EQ(break_editor_plugin_cmds_label_lang(cmds, index, BREAK_EDITOR_LANG_EN_US),
                  "Fixture Hello");
    ASSERT_EQ(break_editor_plugin_cmds_owner(cmds, index), owner);
    ASSERT_TRUE(break_editor_plugin_cmds_execute(cmds, index, doc));
    ASSERT_FALSE(break_editor_plugin_cmds_execute(cmds, index, NULL));

    ASSERT_EQ(break_editor_plugin_host_release(host, owner), 1u);
    ASSERT_EQ(break_plugin_unload(manager, handle), BREAK_PLUGIN_OK);
    ASSERT_EQ(break_editor_plugin_cmds_count(cmds), 0u);
    ASSERT_EQ(break_plugin_destroy(manager), BREAK_PLUGIN_OK);
    break_editor_plugin_host_destroy(host);
    break_editor_plugin_cmds_destroy(cmds);
    break_editor_doc_destroy(doc);
}

/* A plugin that adds a command and then fails registration is not loaded,
 * and its command does not stay in the registry. */
TEST(failed_registration_leaves_no_command)
{
    u8 digest[32];
    BreakPluginHandle handle;
    BreakEditorPluginCmds *cmds = break_editor_plugin_cmds_create(8u);
    BreakEditorPluginHost *host = break_editor_plugin_host_create(cmds);
    ASSERT_NOT_NULL(cmds);
    ASSERT_NOT_NULL(host);
    BreakPluginManager *manager =
        break_plugin_create(4u, (void *)break_editor_plugin_host_api(host));
    ASSERT_NOT_NULL(manager);
    ASSERT_TRUE(hash_file(EDITOR_TEST_PLUGIN_FAIL_PATH, digest));

    ASSERT_TRUE(break_editor_plugin_host_begin_load(host) != 0u);
    BreakPluginStatus status = break_plugin_load(manager, EDITOR_TEST_PLUGIN_FAIL_PATH,
                                                 "editor-test-plugin-fail", digest, &handle);
    ASSERT_TRUE(break_editor_plugin_host_end_load(host, status == BREAK_PLUGIN_OK));
    ASSERT_EQ(status, BREAK_PLUGIN_FAILED);
    ASSERT_EQ(break_editor_plugin_cmds_count(cmds), 0u);
    ASSERT_EQ(break_plugin_destroy(manager), BREAK_PLUGIN_OK);
    break_editor_plugin_host_destroy(host);
    break_editor_plugin_cmds_destroy(cmds);
}

typedef struct ManifestLoader {
    BreakPluginManager *manager;
    BreakPluginHandle handles[BREAK_EDITOR_PLUGIN_MANIFEST_MAX];
    u32 calls;
} ManifestLoader;

static bool manifest_load_plugin(void *user, const BreakEditorPluginManifestEntry *entry)
{
    ManifestLoader *loader = (ManifestLoader *)user;
    BreakPluginHandle handle;
    if (break_plugin_load(loader->manager, entry->path, entry->build_id, entry->sha256,
                          &handle) != BREAK_PLUGIN_OK) {
        loader->calls++;
        return false;
    }
    loader->handles[loader->calls++] = handle;
    return true;
}

static void hex_digest(const u8 digest[32], char out[65])
{
    static const char digits[] = "0123456789abcdef";
    for (u32 i = 0u; i < 32u; ++i) {
        out[2u * i] = digits[digest[i] >> 4];
        out[2u * i + 1u] = digits[digest[i] & 15u];
    }
    out[64] = '\0';
}

/* A manifest of real libraries: the good plugin loads and keeps its
 * command; the plugin whose registration fails and an entry with a wrong
 * hash both fail and leave no command behind. */
TEST(manifest_loads_real_plugins_and_skips_failures)
{
    u8 good[32];
    u8 fail[32];
    char good_hex[65];
    char fail_hex[65];
    char wrong_hex[65];
    static char text[4096];
    static BreakEditorPluginManifest manifest;
    BreakEditorPluginManifestReport report;
    ManifestLoader loader;
    BreakEditorPluginCmds *cmds = break_editor_plugin_cmds_create(8u);
    BreakEditorPluginHost *host = break_editor_plugin_host_create(cmds);
    ASSERT_NOT_NULL(host);
    ASSERT_TRUE(hash_file(EDITOR_TEST_PLUGIN_PATH, good));
    ASSERT_TRUE(hash_file(EDITOR_TEST_PLUGIN_FAIL_PATH, fail));
    hex_digest(good, good_hex);
    hex_digest(fail, fail_hex);
    good[0] ^= 0xffu;
    hex_digest(good, wrong_hex);
    snprintf(text, sizeof text,
             "# startup plugins\n"
             "plugin editor-test-plugin-fail %s %s\n"
             "plugin editor-test-plugin %s %s\n",
             fail_hex, EDITOR_TEST_PLUGIN_FAIL_PATH, good_hex, EDITOR_TEST_PLUGIN_PATH);
    ASSERT_EQ(break_editor_plugin_manifest_parse(text, strlen(text), NULL, &manifest, NULL),
              BREAK_EDITOR_PLUGIN_MANIFEST_OK);
    ASSERT_EQ(manifest.count, 2u);

    memset(&loader, 0, sizeof loader);
    loader.manager = break_plugin_create(4u, (void *)break_editor_plugin_host_api(host));
    ASSERT_NOT_NULL(loader.manager);
    ASSERT_TRUE(break_editor_plugin_manifest_load_all(&manifest, host, manifest_load_plugin,
                                                      &loader, &report));
    ASSERT_EQ(loader.calls, 2u);
    ASSERT_EQ(report.loaded, 1u);
    ASSERT_EQ(report.failed, 1u);
    ASSERT_EQ(report.owners[0], 0u);
    ASSERT_TRUE(report.owners[1] != 0u);
    ASSERT_EQ(break_editor_plugin_cmds_count(cmds), 1u);
    ASSERT_EQ(break_editor_plugin_cmds_find(cmds, "fixture.hello"), 0u);
    ASSERT_EQ(break_editor_plugin_cmds_owner(cmds, 0u), report.owners[1]);

    ASSERT_EQ(break_editor_plugin_host_release(host, report.owners[1]), 1u);
    ASSERT_EQ(break_plugin_unload(loader.manager, loader.handles[1]), BREAK_PLUGIN_OK);
    ASSERT_EQ(break_editor_plugin_cmds_count(cmds), 0u);

    /* The same library with a wrong hash is refused before it runs. */
    snprintf(text, sizeof text, "plugin editor-test-plugin %s %s\n", wrong_hex,
             EDITOR_TEST_PLUGIN_PATH);
    ASSERT_EQ(break_editor_plugin_manifest_parse(text, strlen(text), NULL, &manifest, NULL),
              BREAK_EDITOR_PLUGIN_MANIFEST_OK);
    memset(loader.handles, 0, sizeof loader.handles);
    loader.calls = 0u;
    ASSERT_TRUE(break_editor_plugin_manifest_load_all(&manifest, host, manifest_load_plugin,
                                                      &loader, &report));
    ASSERT_EQ(report.loaded, 0u);
    ASSERT_EQ(report.failed, 1u);
    ASSERT_EQ(break_editor_plugin_cmds_count(cmds), 0u);

    ASSERT_EQ(break_plugin_destroy(loader.manager), BREAK_PLUGIN_OK);
    break_editor_plugin_host_destroy(host);
    break_editor_plugin_cmds_destroy(cmds);
}


#if defined(__linux__)
/* True when a mapping whose name contains `path` is in this process.
 * break_plugin opens a sealed memfd copy, so a loaded plugin shows up as
 * VERIFIED_PLUGIN_MAPPING, not under its file path. */
#define VERIFIED_PLUGIN_MAPPING "memfd:break-verified-plugin"
static bool library_mapped(const char *path)
{
    char line[2048];
    bool found = false;
    FILE *maps = fopen("/proc/self/maps", "r");
    if (!maps) return false;
    while (!found && fgets(line, sizeof line, maps)) {
        found = strstr(line, path) != NULL;
    }
    fclose(maps);
    return found;
}
#endif

/* The loader owns the manager: the good plugin stays loaded with its
 * command, the failing one leaves nothing, and destroy unloads everything. */
TEST(loader_loads_a_manifest_and_unloads_on_destroy)
{
    u8 good[32];
    u8 fail[32];
    char good_hex[65];
    char fail_hex[65];
    char wrong_hex[65];
    static char text[4096];
    static BreakEditorPluginManifest manifest;
    BreakEditorPluginManifestReport report;
    BreakEditorPluginCmds *cmds = break_editor_plugin_cmds_create(8u);
    BreakEditorPluginHost *host = break_editor_plugin_host_create(cmds);
    ASSERT_NOT_NULL(host);
    ASSERT_TRUE(hash_file(EDITOR_TEST_PLUGIN_PATH, good));
    ASSERT_TRUE(hash_file(EDITOR_TEST_PLUGIN_FAIL_PATH, fail));
    hex_digest(good, good_hex);
    hex_digest(fail, fail_hex);
    snprintf(text, sizeof text,
             "plugin editor-test-plugin-fail %s %s\n"
             "plugin editor-test-plugin %s %s\n",
             fail_hex, EDITOR_TEST_PLUGIN_FAIL_PATH, good_hex, EDITOR_TEST_PLUGIN_PATH);
    ASSERT_EQ(break_editor_plugin_manifest_parse(text, strlen(text), NULL, &manifest, NULL),
              BREAK_EDITOR_PLUGIN_MANIFEST_OK);

    BreakEditorPluginSections *sections = break_editor_plugin_sections_create(4u);
    ASSERT_NOT_NULL(sections);
    break_editor_plugin_host_set_sections(host, sections);
    BreakEditorDoc *doc = break_editor_doc_create();
    ASSERT_NOT_NULL(doc);
    break_editor_plugin_host_set_doc(host, doc);
    BreakEditorPluginPanels *panels = break_editor_plugin_panels_create(4u);
    ASSERT_NOT_NULL(panels);
    break_editor_plugin_host_set_panels(host, panels);
    BreakEditorPluginLoader *loader = break_editor_plugin_loader_create(host);
    ASSERT_NOT_NULL(loader);
    ASSERT_EQ(break_editor_plugin_loader_count(loader), 0u);
    ASSERT_TRUE(break_editor_plugin_loader_load_manifest(loader, &manifest, &report));
    ASSERT_EQ(report.loaded, 1u);
    ASSERT_EQ(report.failed, 1u);
    ASSERT_EQ(report.owners[0], 0u);
    ASSERT_TRUE(report.owners[1] != 0u);
    ASSERT_EQ(break_editor_plugin_loader_count(loader), 1u);
    ASSERT_EQ(break_editor_plugin_cmds_count(cmds), 1u);
    ASSERT_EQ(break_editor_plugin_cmds_owner(cmds, 0u), report.owners[1]);
#if defined(__linux__)
    ASSERT_TRUE(library_mapped(VERIFIED_PLUGIN_MAPPING));
#endif
    /* the real plugin also adds an inspector section under the same owner;
     * the failing plugin's section was dropped with its load window */
    ASSERT_EQ(break_editor_plugin_sections_count(sections), 1u);
    ASSERT_STR_EQ(break_editor_plugin_sections_id(sections, 0u), "fixture.section");
    ASSERT_EQ(break_editor_plugin_sections_owner(sections, 0u), report.owners[1]);
    /* the good plugin's component type is in the doc; the failing plugin
     * registered the same type in its window and it was dropped, which is
     * why the good plugin (loaded second) could register it */
    ASSERT_EQ(break_editor_doc_component_count(doc), 3u);
    {
        BreakEditorComponentInfo info;
        ASSERT_TRUE(break_editor_doc_component_info(doc, 2u, &info));
        ASSERT_EQ(info.component_id, FIXTURE_COMPONENT_ID);
        ASSERT_STR_EQ(info.display_name, "FixtureStats");
        ASSERT_EQ(info.field_count, 2u);
    }
    /* the plugin's panel, with its zh-CN title; its text is produced by
     * plugin code on every render */
    ASSERT_EQ(break_editor_plugin_panels_count(panels), 1u);
    ASSERT_STR_EQ(break_editor_plugin_panels_id(panels, 0u), "fixture.panel");
    ASSERT_EQ(break_editor_plugin_panels_owner(panels, 0u), report.owners[1]);
    ASSERT_STR_EQ(break_editor_plugin_panels_title(panels, 0u, BREAK_EDITOR_LANG_ZH_CN),
                  FIXTURE_ZH_PANEL_TITLE);
    {
        char panel_text[64];
        ASSERT_TRUE(break_editor_plugin_panels_render(panels, 0u, doc, panel_text,
                                                      sizeof panel_text));
        ASSERT_STR_EQ(panel_text, "renders: 1");
        ASSERT_TRUE(break_editor_plugin_panels_render(panels, 0u, doc, panel_text,
                                                      sizeof panel_text));
        ASSERT_STR_EQ(panel_text, "renders: 2");
    }
    BreakEditorEntityId unit = break_editor_doc_add_entity(doc, "unit");
    ASSERT_TRUE(break_editor_doc_add_component(doc, unit, FIXTURE_COMPONENT_ID));
    {
        f32 level = 0.0f;
        bool active = false;
        ASSERT_TRUE(break_editor_doc_get_field_f32(doc, unit, FIXTURE_COMPONENT_ID, 0u, &level));
        ASSERT_TRUE(level == 2.5f);
        ASSERT_TRUE(break_editor_doc_get_field_bool(doc, unit, FIXTURE_COMPONENT_ID, 1u,
                                                    &active));
        ASSERT_TRUE(active);
    }
    ASSERT_STR_EQ(break_editor_plugin_sections_title_lang(sections, 0u, BREAK_EDITOR_LANG_ZH_CN),
                  FIXTURE_ZH_SECTION_TITLE);
    ASSERT_STR_EQ(break_editor_plugin_sections_title_lang(sections, 0u, BREAK_EDITOR_LANG_EN_US),
                  "Fixture Section");
    {
        /* the section text follows the editor language via api->lang_tag;
         * not named `text`, which would hide the manifest buffer (MSVC C4456) */
        char section_text[64];
        ASSERT_TRUE(break_editor_i18n_set_lang(BREAK_EDITOR_LANG_EN_US));
        ASSERT_TRUE(break_editor_plugin_sections_describe(sections, 0u, NULL,
                                                          BREAK_EDITOR_ENTITY_NULL,
                                                          section_text, sizeof section_text));
        ASSERT_STR_EQ(section_text, "fixture section");
        ASSERT_TRUE(break_editor_i18n_set_lang(BREAK_EDITOR_LANG_ZH_CN));
        ASSERT_TRUE(break_editor_plugin_sections_describe(sections, 0u, NULL,
                                                          BREAK_EDITOR_ENTITY_NULL,
                                                          section_text, sizeof section_text));
        ASSERT_STR_EQ(section_text, FIXTURE_ZH_SECTION_TEXT);
        ASSERT_TRUE(break_editor_i18n_set_lang(BREAK_EDITOR_LANG_EN_US));
    }

    /* A second manifest adds to the same loader; a wrong hash loads nothing. */
    good[0] ^= 0xffu;
    hex_digest(good, wrong_hex);
    snprintf(text, sizeof text, "plugin editor-test-plugin %s %s\n", wrong_hex,
             EDITOR_TEST_PLUGIN_PATH);
    ASSERT_EQ(break_editor_plugin_manifest_parse(text, strlen(text), NULL, &manifest, NULL),
              BREAK_EDITOR_PLUGIN_MANIFEST_OK);
    ASSERT_TRUE(break_editor_plugin_loader_load_manifest(loader, &manifest, &report));
    ASSERT_EQ(report.loaded, 0u);
    ASSERT_EQ(report.failed, 1u);
    ASSERT_EQ(break_editor_plugin_loader_count(loader), 1u);
    ASSERT_EQ(break_editor_plugin_cmds_count(cmds), 1u);

    break_editor_plugin_loader_destroy(loader);
    ASSERT_EQ(break_editor_plugin_cmds_count(cmds), 0u);
#if defined(__linux__)
    /* destroy unloads the library, not only its commands */
    ASSERT_FALSE(library_mapped(VERIFIED_PLUGIN_MAPPING));
#endif
    ASSERT_EQ(break_editor_plugin_sections_count(sections), 0u);
    ASSERT_EQ(break_editor_plugin_panels_count(panels), 0u);
    break_editor_plugin_panels_destroy(panels);
    /* the type and its default bytes were copied: after the library is
     * unmapped the type still edits, undoes and adds with its defaults */
    ASSERT_EQ(break_editor_doc_component_count(doc), 3u);
    ASSERT_TRUE(break_editor_doc_set_field_f32(doc, unit, FIXTURE_COMPONENT_ID, 0u, 6.0f));
    ASSERT_TRUE(break_editor_undo(doc));
    {
        BreakEditorEntityId other = break_editor_doc_add_entity(doc, "other");
        f32 level = 0.0f;
        ASSERT_TRUE(break_editor_doc_add_component(doc, other, FIXTURE_COMPONENT_ID));
        ASSERT_TRUE(break_editor_doc_get_field_f32(doc, other, FIXTURE_COMPONENT_ID, 0u, &level));
        ASSERT_TRUE(level == 2.5f);
    }
    break_editor_doc_destroy(doc);
    break_editor_plugin_sections_destroy(sections);
    break_editor_plugin_host_destroy(host);
    break_editor_plugin_cmds_destroy(cmds);
}

TEST(loader_rejects_null_arguments)
{
    static BreakEditorPluginManifest manifest;
    BreakEditorPluginManifestReport report;
    BreakEditorPluginCmds *cmds = break_editor_plugin_cmds_create(4u);
    BreakEditorPluginHost *host = break_editor_plugin_host_create(cmds);
    ASSERT_TRUE(break_editor_plugin_loader_create(NULL) == NULL);
    BreakEditorPluginLoader *loader = break_editor_plugin_loader_create(host);
    ASSERT_NOT_NULL(loader);
    memset(&manifest, 0, sizeof manifest);
    ASSERT_FALSE(break_editor_plugin_loader_load_manifest(NULL, &manifest, &report));
    ASSERT_FALSE(break_editor_plugin_loader_load_manifest(loader, NULL, &report));
    ASSERT_FALSE(break_editor_plugin_loader_load_manifest(loader, &manifest, NULL));
    ASSERT_TRUE(break_editor_plugin_loader_load_manifest(loader, &manifest, &report));
    ASSERT_EQ(report.loaded, 0u);
    ASSERT_EQ(report.failed, 0u);
    ASSERT_EQ(break_editor_plugin_loader_count(NULL), 0u);
    break_editor_plugin_loader_destroy(NULL);
    break_editor_plugin_loader_destroy(loader);
    break_editor_plugin_host_destroy(host);
    break_editor_plugin_cmds_destroy(cmds);
}

TEST_MAIN_BEGIN()
    RUN_TEST(real_plugin_adds_and_removes_a_command);
    RUN_TEST(failed_registration_leaves_no_command);
    RUN_TEST(manifest_loads_real_plugins_and_skips_failures);
    RUN_TEST(loader_loads_a_manifest_and_unloads_on_destroy);
    RUN_TEST(loader_rejects_null_arguments);
TEST_MAIN_END()
