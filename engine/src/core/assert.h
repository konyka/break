#pragma once
#include <core/types.h>

/* ---- Compile-time assert ---- */
/* C11 _Static_assert is a keyword; provide a convenience macro */
#define STATIC_ASSERT(cond, msg) _Static_assert(cond, msg)

/* ---- Runtime assert ---- */
/* engine_assert prints a message and aborts.
   Controlled by ENGINE_ASSERTS_ENABLED:
     - Always enabled in debug builds (NDEBUG not defined)
     - Can be forced on/off with ENGINE_ASSERTS_ENABLE/DISABLE
*/
#if !defined(ENGINE_ASSERTS_DISABLE) && (defined(DEBUG) || !defined(NDEBUG))
    #define ENGINE_ASSERTS_ENABLED 1
#else
    #undef ENGINE_ASSERTS_ENABLED
#endif

#ifdef ENGINE_ASSERTS_ENABLED
    #define engine_assert(cond, msg)                                           \
        do {                                                                   \
            if (!(cond)) {                                                     \
                engine_assert_fail(#cond, __FILE__, __LINE__, __func__, msg);  \
            }                                                                  \
        } while (0)
#else
    #define engine_assert(cond, msg) ((void)0)
#endif

[[noreturn]] void engine_assert_fail(const char *cond, const char *file,
                                     int line, const char *func,
                                     const char *msg);
