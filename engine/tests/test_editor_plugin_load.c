#include "test_framework.h"

#include <crypto/break_crypto.h>
#include <editor/editor_doc.h>
#include <editor/editor_plugin_host.h>
#include <system/break_plugin.h>

#include <stdio.h>

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

TEST_MAIN_BEGIN()
    RUN_TEST(real_plugin_adds_and_removes_a_command);
    RUN_TEST(failed_registration_leaves_no_command);
TEST_MAIN_END()
