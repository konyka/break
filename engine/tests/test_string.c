/* ==========================================================================
 *  test_string.c — Unit tests for the core string slice module.
 * ========================================================================== */

#include "test_framework.h"
#include <core/string.h>
#include <string.h>

/* ----------------------------------------------------------------------- */

TEST(str_from_c_basic)
{
    Str s = str_from_c("hello");
    ASSERT_EQ(s.len, (usize)5);
    ASSERT_TRUE(memcmp(s.data, "hello", 5) == 0);
}

TEST(str_from_c_empty)
{
    Str s = str_from_c("");
    ASSERT_EQ(s.len, (usize)0);
}

TEST(str_macro)
{
    Str s = STR("world");
    ASSERT_EQ(s.len, (usize)5);
    ASSERT_TRUE(str_eq_c(s, "world"));
}

TEST(str_eq_same)
{
    Str a = STR("test");
    Str b = STR("test");
    ASSERT_TRUE(str_eq(a, b));
}

TEST(str_eq_different)
{
    Str a = STR("abc");
    Str b = STR("xyz");
    ASSERT_TRUE(!str_eq(a, b));
}

TEST(str_eq_different_len)
{
    Str a = STR("ab");
    Str b = STR("abc");
    ASSERT_TRUE(!str_eq(a, b));
}

TEST(str_eq_c_match)
{
    Str s = STR("hello");
    ASSERT_TRUE(str_eq_c(s, "hello"));
}

TEST(str_eq_c_mismatch)
{
    Str s = STR("hello");
    ASSERT_TRUE(!str_eq_c(s, "world"));
}

TEST(str_slice_basic)
{
    Str s = STR("Hello, World!");
    Str sub = str_slice(s, 7, 12);
    ASSERT_EQ(sub.len, (usize)5);
    ASSERT_TRUE(str_eq_c(sub, "World"));
}

TEST(str_slice_full)
{
    Str s = STR("abc");
    Str sub = str_slice(s, 0, 3);
    ASSERT_TRUE(str_eq(sub, s));
}

TEST(str_slice_clamp)
{
    Str s = STR("abc");
    Str sub = str_slice(s, 0, 100);  /* end > len, should clamp */
    ASSERT_EQ(sub.len, (usize)3);
}

TEST(str_slice_empty)
{
    Str s = STR("abc");
    Str sub = str_slice(s, 2, 1);  /* start > end, should be empty */
    ASSERT_EQ(sub.len, (usize)0);
}

TEST(str_find_char_found)
{
    Str s = STR("hello world");
    i32 idx = str_find_char(s, 'w');
    ASSERT_EQ(idx, 6);
}

TEST(str_find_char_not_found)
{
    Str s = STR("hello");
    i32 idx = str_find_char(s, 'z');
    ASSERT_EQ(idx, -1);
}

TEST(str_find_char_first)
{
    Str s = STR("abcabc");
    i32 idx = str_find_char(s, 'a');
    ASSERT_EQ(idx, 0);
}

TEST(str_hash_deterministic)
{
    Str s = STR("test_key");
    u64 h1 = str_hash(s);
    u64 h2 = str_hash(s);
    ASSERT_TRUE(h1 == h2);
    ASSERT_TRUE(h1 != 0);
}

TEST(str_hash_different)
{
    Str a = STR("key_a");
    Str b = STR("key_b");
    ASSERT_TRUE(str_hash(a) != str_hash(b));
}

TEST(str_copy_basic)
{
    Str s = STR("hello");
    char buf[32] = {0};
    Str copied = str_copy(s, buf, sizeof(buf));
    ASSERT_EQ(copied.len, (usize)5);
    ASSERT_TRUE(str_eq_c(copied, "hello"));
    ASSERT_EQ(buf[5], '\0');
}

TEST(str_copy_truncate)
{
    Str s = STR("hello world");
    char buf[6] = {0};
    Str copied = str_copy(s, buf, sizeof(buf));
    ASSERT_EQ(copied.len, (usize)5);  /* buf_size - 1 = 5 */
    ASSERT_EQ(buf[5], '\0');
}

/* ----------------------------------------------------------------------- */
/*  Edge Cases                                                              */
/* ----------------------------------------------------------------------- */

TEST(str_hash_empty)
{
    Str s = STR("");
    u64 h = str_hash(s);
    /* Hash of empty string is implementation-defined, just verify no crash */
    (void)h;
    ASSERT_TRUE(true);
}

TEST(str_slice_start_beyond_len)
{
    Str s = STR("abc");
    Str sub = str_slice(s, 100, 200);  /* start > len */
    ASSERT_EQ(sub.len, (usize)0);
}

TEST(str_find_char_empty_string)
{
    Str s = STR("");
    i32 idx = str_find_char(s, 'a');
    ASSERT_EQ(idx, -1);
}

TEST(str_copy_zero_buffer)
{
    Str s = STR("hello");
    char buf[1] = {0};
    Str copied = str_copy(s, buf, 0);
    /* Zero-size buffer - implementation-defined, just verify no crash */
    (void)copied;
    ASSERT_TRUE(true);
}

/* ----------------------------------------------------------------------- */

TEST_MAIN_BEGIN()
    RUN_TEST(str_from_c_basic);
    RUN_TEST(str_from_c_empty);
    RUN_TEST(str_macro);
    RUN_TEST(str_eq_same);
    RUN_TEST(str_eq_different);
    RUN_TEST(str_eq_different_len);
    RUN_TEST(str_eq_c_match);
    RUN_TEST(str_eq_c_mismatch);
    RUN_TEST(str_slice_basic);
    RUN_TEST(str_slice_full);
    RUN_TEST(str_slice_clamp);
    RUN_TEST(str_slice_empty);
    RUN_TEST(str_find_char_found);
    RUN_TEST(str_find_char_not_found);
    RUN_TEST(str_find_char_first);
    RUN_TEST(str_hash_deterministic);
    RUN_TEST(str_hash_different);
    RUN_TEST(str_copy_basic);
    RUN_TEST(str_copy_truncate);
    /* Edge cases */
    RUN_TEST(str_hash_empty);
    RUN_TEST(str_slice_start_beyond_len);
    RUN_TEST(str_find_char_empty_string);
    RUN_TEST(str_copy_zero_buffer);
TEST_MAIN_END()
