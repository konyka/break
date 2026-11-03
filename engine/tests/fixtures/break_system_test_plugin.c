#include <system/break_plugin.h>
#include "break_system_test_plugin.h"

#ifndef BREAK_TEST_PLUGIN_NAME
#define BREAK_TEST_PLUGIN_NAME "system-test"
#endif
#ifndef BREAK_TEST_PLUGIN_BUILD_ID
#define BREAK_TEST_PLUGIN_BUILD_ID "system-test-build"
#endif
#ifndef BREAK_TEST_PLUGIN_EVENT
#define BREAK_TEST_PLUGIN_EVENT 1
#endif
#ifndef BREAK_TEST_PLUGIN_ABI
#define BREAK_TEST_PLUGIN_ABI BREAK_PLUGIN_ABI_VERSION
#endif
#ifndef BREAK_TEST_REGISTER_RESULT
#define BREAK_TEST_REGISTER_RESULT 1
#endif
#ifndef BREAK_TEST_NO_ENTRY
#define BREAK_TEST_NO_ENTRY 0
#endif

#if !BREAK_TEST_NO_ENTRY
static bool test_register(void *user) {
    BreakSystemTestPluginLog *log = (BreakSystemTestPluginLog *)user;
    if (!log || log->count >= 16u) return false;
    log->events[log->count++] = BREAK_TEST_PLUGIN_EVENT;
    return BREAK_TEST_REGISTER_RESULT != 0;
}

static void test_unregister(void *user) {
    BreakSystemTestPluginLog *log = (BreakSystemTestPluginLog *)user;
    if (log && log->count < 16u) log->events[log->count++] = -BREAK_TEST_PLUGIN_EVENT;
}

static const BreakPluginDescriptor descriptor = {
    sizeof(BreakPluginDescriptor),
    BREAK_TEST_PLUGIN_ABI,
    BREAK_TEST_PLUGIN_NAME,
    BREAK_TEST_PLUGIN_BUILD_ID,
    test_register,
    test_unregister
};

#if defined(_WIN32)
__declspec(dllexport)
#endif
const BreakPluginDescriptor *break_plugin_entry(void) {
    return &descriptor;
}
#endif
