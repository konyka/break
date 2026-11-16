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

static const BreakEditorPluginApi *fixture_api;

static void copy_text(const char *text, char *out, usize cap)
{
    usize i = 0u;
    while (i + 1u < cap && text[i] != '\0') {
        out[i] = text[i];
        i++;
    }
    out[i] = '\0';
}

/* the text follows the editor language read through lang_tag */
static bool fixture_section(void *user, const BreakEditorDoc *doc, BreakEditorEntityId entity,
                            char *out, usize cap)
{
    const char *tag = fixture_api ? fixture_api->lang_tag(fixture_api->host) : "";
    (void)user;
    (void)doc;
    (void)entity;
    if (cap > 0u) {
        copy_text(tag[0] == 'z' ? "\xe5\xa4\xb9\xe5\x85\xb7\xe5\x8c\xba\xe5\x9d\x97"
                                : "fixture section",
                  out, cap);
    }
    return true;
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
    if (!api->set_command_label || !api->lang_tag ||
        api->set_command_label(api->host, "fixture.hello", "zh-CN",
                               "\xe5\xa4\xb9\xe5\x85\xb7\xe9\x97\xae\xe5\x80\x99") !=
            BREAK_EDITOR_PLUGIN_CMD_OK) {
        return false;
    }
    fixture_api = api;
    /* a host without a section registry refuses the section and its title;
     * that is not a registration failure */
    (void)api->add_section(api->host, "fixture.section", "Fixture Section", fixture_section, NULL);
    (void)api->set_section_title(api->host, "fixture.section", "zh-CN",
                                 "\xe5\xa4\xb9\xe5\x85\xb7\xe5\x88\x86\xe5\x8c\xba");
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
