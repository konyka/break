#include <system/break_plugin.h>
#include <editor/editor_plugin_host.h>

#ifndef EDITOR_TEST_PLUGIN_NAME
#define EDITOR_TEST_PLUGIN_NAME "editor-test-plugin"
#endif
#ifndef EDITOR_TEST_PLUGIN_BUILD_ID
#define EDITOR_TEST_PLUGIN_BUILD_ID "editor-test-plugin"
#endif
#ifndef EDITOR_TEST_REGISTER_RESULT
#define EDITOR_TEST_REGISTER_RESULT 1
#endif

static bool fixture_command(void *user, BreakEditorDoc *doc)
{
    (void)user;
    return doc != NULL;
}

static bool fixture_register(void *user)
{
    const BreakEditorPluginApi *api = (const BreakEditorPluginApi *)user;
    if (!api || api->struct_size != sizeof(BreakEditorPluginApi) ||
        api->api_version != BREAK_EDITOR_PLUGIN_API_VERSION || !api->add_command) {
        return false;
    }
    if (api->add_command(api->host, "fixture.hello", "Fixture Hello", fixture_command, NULL) !=
        BREAK_EDITOR_PLUGIN_CMD_OK) {
        return false;
    }
    return EDITOR_TEST_REGISTER_RESULT != 0;
}

static const BreakPluginDescriptor descriptor = {
    sizeof(BreakPluginDescriptor),
    BREAK_PLUGIN_ABI_VERSION,
    EDITOR_TEST_PLUGIN_NAME,
    EDITOR_TEST_PLUGIN_BUILD_ID,
    fixture_register,
    NULL
};

#if defined(_WIN32)
__declspec(dllexport)
#endif
const BreakPluginDescriptor *break_plugin_entry(void)
{
    return &descriptor;
}
