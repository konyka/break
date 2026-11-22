#pragma once

#include <runtime/runtime_mainloop.h>

/* Reads one frame's BreakRuntimeMainLoopFacts from a Platform: drawable
 * size, content scale and WSI state, plus the close request the caller got
 * from platform_poll (PLATFORM_EVENT_QUIT). Kept out of runtime_core so the
 * runtime library never depends on the platform layer; link it next to the
 * platform backend. Main loop thread only. False for NULL arguments. */
typedef struct Platform Platform;

bool break_runtime_mainloop_platform_facts(Platform *platform, u64 frame, bool close_requested,
                                           BreakRuntimeMainLoopFacts *out_facts);
