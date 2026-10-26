#include "test_framework.h"
#include <platform/platform_vk_surface.h>
#include "../src/platform/platform_vk_surface_vkabi.h"

static char test_instance;
static char test_context;
static char test_window;
static int test_available;
static i32 test_result;
static u32 test_get_proc_calls;
static u32 test_create_calls;
static void *test_seen_instance;
static const void *test_seen_allocator;
static PVkScreenSurfaceCreateInfo test_seen_info;

static i32 test_create_surface(void *instance, const void *create_info,
                               const void *allocator, u64 *out_surface)
{
    test_create_calls++;
    test_seen_instance = instance;
    test_seen_allocator = allocator;
    memcpy(&test_seen_info, create_info, sizeof(test_seen_info));
    *out_surface = (u64)0x123456789abcdef0ULL;
    return test_result;
}

static void *test_get_proc_addr(void *instance, const char *name)
{
    PVkCreateSurfaceFn create = test_create_surface;
    void *entry = NULL;
    test_get_proc_calls++;
    if (instance != &test_instance ||
        strcmp(name, "vkCreateScreenSurfaceQNX") != 0 || !test_available) {
        return NULL;
    }
    memcpy(&entry, &create, sizeof(entry));
    return entry;
}

static void *test_get_proc_address(void)
{
    PVkGetProcAddrFn get_proc = test_get_proc_addr;
    void *address = NULL;
    memcpy(&address, &get_proc, sizeof(address));
    return address;
}

void *platform_display_native(Platform *p)
{
    return p != NULL ? &test_context : NULL;
}

void *platform_surface_native(Platform *p)
{
    return p != NULL ? &test_window : NULL;
}

static void test_reset(void)
{
    test_available = 1;
    test_result = 0;
    test_get_proc_calls = 0u;
    test_create_calls = 0u;
    test_seen_instance = NULL;
    test_seen_allocator = NULL;
    memset(&test_seen_info, 0, sizeof(test_seen_info));
}

TEST(qnx_required_extensions)
{
    const char *extensions[2] = { NULL, NULL };
    const char *small[1] = { (const char *)&test_instance };
    ASSERT_EQ(platform_vk_required_instance_extensions(NULL, NULL, 0u), 2u);
    ASSERT_EQ(platform_vk_required_instance_extensions(NULL, small, 1u), 2u);
    ASSERT_EQ(small[0], (const char *)&test_instance);
    ASSERT_EQ(platform_vk_required_instance_extensions(NULL, extensions, 2u), 2u);
    ASSERT_STR_EQ(extensions[0], "VK_KHR_surface");
    ASSERT_STR_EQ(extensions[1], "VK_QNX_screen_surface");
    ASSERT_EQ(platform_vk_instance_create_flags(NULL), 0u);
}

TEST(qnx_invalid_arguments_and_native_handles)
{
    u64 surface = 99u;
    void *get_proc = test_get_proc_address();
    test_reset();
    ASSERT_EQ(platform_vk_create_surface(NULL, &test_instance, get_proc, &surface),
              PLATFORM_VK_SURFACE_ERROR_INVALID_ARGUMENT);
    ASSERT_EQ(surface, 99u);
    ASSERT_EQ(platform_vk_create_surface_handles(&test_window, &test_context,
                                                 NULL, get_proc, &surface),
              PLATFORM_VK_SURFACE_ERROR_INVALID_ARGUMENT);
    ASSERT_EQ(platform_vk_create_surface_handles(&test_window, &test_context,
                                                 &test_instance, NULL, &surface),
              PLATFORM_VK_SURFACE_ERROR_INVALID_ARGUMENT);
    ASSERT_EQ(platform_vk_create_surface_handles(&test_window, &test_context,
                                                 &test_instance, get_proc, NULL),
              PLATFORM_VK_SURFACE_ERROR_INVALID_ARGUMENT);
    ASSERT_EQ(surface, 99u);
    ASSERT_EQ(platform_vk_create_surface_handles(NULL, &test_context,
                                                 &test_instance, get_proc, &surface),
              PLATFORM_VK_SURFACE_ERROR_UNAVAILABLE);
    ASSERT_EQ(surface, 0u);
    surface = 99u;
    ASSERT_EQ(platform_vk_create_surface_handles(&test_window, NULL,
                                                 &test_instance, get_proc, &surface),
              PLATFORM_VK_SURFACE_ERROR_UNAVAILABLE);
    ASSERT_EQ(surface, 0u);
    ASSERT_EQ(test_get_proc_calls, 0u);
    ASSERT_EQ(test_create_calls, 0u);
}

TEST(qnx_missing_create_entrypoint)
{
    u64 surface = 99u;
    test_reset();
    test_available = 0;
    ASSERT_EQ(platform_vk_create_surface_handles(&test_window, &test_context,
                                                 &test_instance,
                                                 test_get_proc_address(), &surface),
              PLATFORM_VK_SURFACE_ERROR_PROC_MISSING);
    ASSERT_EQ(surface, 0u);
    ASSERT_EQ(test_get_proc_calls, 1u);
    ASSERT_EQ(test_create_calls, 0u);
}

TEST(qnx_create_surface_success)
{
    Platform *platform = (Platform *)&test_instance;
    u64 surface = 0u;
    test_reset();
    ASSERT_EQ(platform_vk_create_surface(platform, &test_instance,
                                         test_get_proc_address(), &surface),
              PLATFORM_VK_SURFACE_OK);
    ASSERT_EQ(surface, (u64)0x123456789abcdef0ULL);
    ASSERT_EQ(test_get_proc_calls, 1u);
    ASSERT_EQ(test_create_calls, 1u);
    ASSERT_EQ(test_seen_instance, &test_instance);
    ASSERT_EQ(test_seen_allocator, NULL);
    ASSERT_EQ(test_seen_info.sType, PVK_STYPE_SCREEN_SURFACE_CREATE_INFO_QNX);
    ASSERT_EQ(test_seen_info.pNext, NULL);
    ASSERT_EQ(test_seen_info.flags, 0u);
    ASSERT_EQ(test_seen_info.context, &test_context);
    ASSERT_EQ(test_seen_info.window, &test_window);
}

TEST(qnx_create_surface_failure)
{
    u64 surface = 99u;
    test_reset();
    test_result = -9;
    ASSERT_EQ(platform_vk_create_surface_handles(&test_window, &test_context,
                                                 &test_instance,
                                                 test_get_proc_address(), &surface),
              PLATFORM_VK_SURFACE_ERROR_CREATE_FAILED);
    ASSERT_EQ(surface, 0u);
    ASSERT_EQ(test_create_calls, 1u);
    ASSERT_EQ(test_seen_info.context, &test_context);
    ASSERT_EQ(test_seen_info.window, &test_window);
}

TEST_MAIN_BEGIN()
    RUN_TEST(qnx_required_extensions);
    RUN_TEST(qnx_invalid_arguments_and_native_handles);
    RUN_TEST(qnx_missing_create_entrypoint);
    RUN_TEST(qnx_create_surface_success);
    RUN_TEST(qnx_create_surface_failure);
TEST_MAIN_END()
