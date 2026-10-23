/* ==========================================================================
 *  test_break_version.c — Product version/build identity contract tests.
 * ========================================================================== */

#include "test_framework.h"
#include <core/break_version.h>
#include <string.h>

/* Expected "MAJOR.MINOR.PATCH" triple derived from the public macros. */
static void expected_triple(char *buf, size_t cap)
{
    snprintf(buf, cap, "%d.%d.%d",
             BREAK_VERSION_MAJOR, BREAK_VERSION_MINOR, BREAK_VERSION_PATCH);
}

TEST(version_macros_are_0_1_0)
{
    ASSERT_EQ(BREAK_VERSION_MAJOR, 0);
    ASSERT_EQ(BREAK_VERSION_MINOR, 1);
    ASSERT_EQ(BREAK_VERSION_PATCH, 0);
}

TEST(version_string_non_null)
{
    ASSERT_NOT_NULL(break_version_string());
}

TEST(version_string_has_triple_prefix)
{
    char triple[32];
    const char *s = break_version_string();
    expected_triple(triple, sizeof(triple));
    ASSERT_STR_EQ(triple, "0.1.0");
    ASSERT_TRUE(strncmp(s, triple, strlen(triple)) == 0);
}

TEST(version_string_shape)
{
    /* Parse-check the contract shape: ^0\.1\.0(\+.+)?$ */
    char triple[32];
    const char *s = break_version_string();
    const char *rest;
    expected_triple(triple, sizeof(triple));
    ASSERT_TRUE(strncmp(s, triple, strlen(triple)) == 0);
    rest = s + strlen(triple);
    if (rest[0] != '\0') {
        ASSERT_EQ(rest[0], '+');
        ASSERT_TRUE(strlen(rest) >= 2); /* '+' alone is not a valid suffix */
    }
    ASSERT_TRUE(strlen(s) < 64); /* bounded identity string */
}

TEST(version_string_build_id_suffix_when_injected)
{
#ifdef BREAK_BUILD_ID
    /* CMake injects the short git hash (fallback "unknown"); the suffix must
     * be present, non-empty, and byte-identical to the injected value. */
    const char *s = break_version_string();
    const char *plus = strchr(s, '+');
    ASSERT_NOT_NULL(plus);
    ASSERT_TRUE(strlen(BREAK_BUILD_ID) > 0);
    ASSERT_STR_EQ(plus + 1, BREAK_BUILD_ID);
#else
    /* Without injection the plain triple is returned, no '+' suffix. */
    ASSERT_TRUE(strchr(break_version_string(), '+') == NULL);
#endif
}

TEST(version_string_repeated_calls_same_pointer)
{
    const char *a = break_version_string();
    const char *b = break_version_string();
    ASSERT_TRUE(a == b);
}

TEST(version_string_contents_stable)
{
    char copy[64];
    const char *s = break_version_string();
    ASSERT_TRUE(strlen(s) < sizeof(copy));
    strcpy(copy, s);
    ASSERT_STR_EQ(break_version_string(), copy);
}

TEST_MAIN_BEGIN()
    RUN_TEST(version_macros_are_0_1_0);
    RUN_TEST(version_string_non_null);
    RUN_TEST(version_string_has_triple_prefix);
    RUN_TEST(version_string_shape);
    RUN_TEST(version_string_build_id_suffix_when_injected);
    RUN_TEST(version_string_repeated_calls_same_pointer);
    RUN_TEST(version_string_contents_stable);
TEST_MAIN_END()
