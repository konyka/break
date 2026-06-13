#ifndef TEST_FRAMEWORK_H
#define TEST_FRAMEWORK_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

static int g_test_count = 0;
static int g_test_pass = 0;
static int g_test_fail = 0;

#define TEST(name) static void test_##name(void)

#define ASSERT_TRUE(x) do { \
    if (!(x)) { \
        printf("  FAIL: %s:%d: %s is false\n", __FILE__, __LINE__, #x); \
        g_test_fail++; \
        return; \
    } \
} while(0)

#define ASSERT_FALSE(x) do { \
    if ((x)) { \
        printf("  FAIL: %s:%d: %s is true\n", __FILE__, __LINE__, #x); \
        g_test_fail++; \
        return; \
    } \
} while(0)

#define ASSERT_EQ(a, b) do { \
    if ((a) != (b)) { \
        printf("  FAIL: %s:%d: %s != %s\n", __FILE__, __LINE__, #a, #b); \
        g_test_fail++; \
        return; \
    } \
} while(0)

#define ASSERT_NEQ(a, b) do { \
    if ((a) == (b)) { \
        printf("  FAIL: %s:%d: %s == %s\n", __FILE__, __LINE__, #a, #b); \
        g_test_fail++; \
        return; \
    } \
} while(0)

#define ASSERT_FLOAT_EQ(a, b, eps) do { \
    if (fabs((double)(a) - (double)(b)) > (double)(eps)) { \
        printf("  FAIL: %s:%d: %s != %s (diff=%g)\n", \
               __FILE__, __LINE__, #a, #b, \
               fabs((double)(a)-(double)(b))); \
        g_test_fail++; \
        return; \
    } \
} while(0)

#define ASSERT_STR_EQ(a, b) do { \
    if (strcmp((a), (b)) != 0) { \
        printf("  FAIL: %s:%d: \"%s\" != \"%s\"\n", __FILE__, __LINE__, (a), (b)); \
        g_test_fail++; \
        return; \
    } \
} while(0)

#define ASSERT_NOT_NULL(p) do { \
    if ((p) == NULL) { \
        printf("  FAIL: %s:%d: %s is NULL\n", __FILE__, __LINE__, #p); \
        g_test_fail++; \
        return; \
    } \
} while(0)

#define RUN_TEST(name) do { \
    int _fail_before = g_test_fail; \
    g_test_count++; \
    printf("  [%d] %s ... ", g_test_count, #name); \
    test_##name(); \
    if (g_test_fail == _fail_before) { \
        g_test_pass++; \
        printf("OK\n"); \
    } else { \
        /* FAIL already printed by ASSERT macro */ \
    } \
} while(0)

#define TEST_MAIN_BEGIN() int main(void) { \
    printf("=== Running Tests ===\n");

#define TEST_MAIN_END() \
    printf("\n=== Results: %d passed, %d failed, %d total ===\n", \
           g_test_pass, g_test_fail, g_test_count); \
    return g_test_fail > 0 ? 1 : 0; \
}

#endif /* TEST_FRAMEWORK_H */
