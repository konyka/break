/* ==========================================================================
 *  break_version.c — Product version/build identity (see break_version.h).
 * ========================================================================== */

#include <core/break_version.h>

#define BREAK_STR_(x) #x
#define BREAK_STR(x) BREAK_STR_(x)

#define BREAK_VERSION_TRIPLE \
    BREAK_STR(BREAK_VERSION_MAJOR) "." BREAK_STR(BREAK_VERSION_MINOR) "." \
    BREAK_STR(BREAK_VERSION_PATCH)

#if defined(BREAK_BUILD_ID)
/* BREAK_BUILD_ID must be a non-empty string literal; CMake injects the short
 * git hash with an "unknown" fallback, so an empty value never reaches here
 * from the supported build path. */
#define BREAK_VERSION_STRING BREAK_VERSION_TRIPLE "+" BREAK_BUILD_ID
#else
#define BREAK_VERSION_STRING BREAK_VERSION_TRIPLE
#endif

const char *break_version_string(void)
{
    /* String literal: static storage duration, never NULL, same pointer on
     * every call. */
    return BREAK_VERSION_STRING;
}
