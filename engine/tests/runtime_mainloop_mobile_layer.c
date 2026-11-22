/* test_runtime_mainloop_platform builds the display-free mobile window layer
 * on every host; only this file sees the iOS selector, so the clock and the
 * profiler keep the host platform's implementation. */
#ifndef ENGINE_PLATFORM_IOS
#define ENGINE_PLATFORM_IOS 1
#endif
#include "../src/platform/window_mobile.c"
