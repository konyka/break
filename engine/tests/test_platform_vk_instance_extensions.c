/* Instance extension resolution: required extensions must be present, the
 * loader-only portability enumeration extension is dropped (with its create
 * flag) when the executable talks to MoltenVK directly. Pure logic; no
 * Vulkan runtime is needed. */
#include "test_framework.h"
#include <platform/platform_vk_surface.h>
#include <string.h>

#define PORTABILITY_BIT 0x1u

typedef struct {
    const char *have[8];
    u32 count;
} Avail;

static bool avail(const char *name, void *user) {
    const Avail *a = (const Avail *)user;
    for (u32 i = 0; i < a->count; i++)
        if (strcmp(a->have[i], name) == 0) return true;
    return false;
}

TEST(only_portability_enumeration_is_optional) {
    ASSERT_TRUE(platform_vk_instance_extension_optional("VK_KHR_portability_enumeration"));
    ASSERT_FALSE(platform_vk_instance_extension_optional("VK_KHR_surface"));
    ASSERT_FALSE(platform_vk_instance_extension_optional("VK_EXT_metal_surface"));
    ASSERT_FALSE(platform_vk_instance_extension_optional("VK_KHR_get_physical_device_properties2"));
    ASSERT_FALSE(platform_vk_instance_extension_optional(NULL));
}

TEST(all_present_keeps_everything) {
    const char *names[] = {"VK_KHR_surface", "VK_EXT_metal_surface", "VK_KHR_portability_enumeration",
                           "VK_KHR_get_physical_device_properties2"};
    Avail a = {{"VK_KHR_surface", "VK_EXT_metal_surface", "VK_KHR_portability_enumeration",
                "VK_KHR_get_physical_device_properties2"}, 4u};
    u32 count = 4u, flags = PORTABILITY_BIT;
    const char *missing = "unset";
    ASSERT_TRUE(platform_vk_resolve_instance_extensions(names, &count, &flags, avail, &a, &missing));
    ASSERT_EQ(count, 4u);
    ASSERT_EQ(flags, PORTABILITY_BIT);
    ASSERT_TRUE(missing == NULL);
    ASSERT_STR_EQ(names[2], "VK_KHR_portability_enumeration");
}

/* MoltenVK linked directly: no loader, so no portability enumeration. */
TEST(direct_moltenvk_drops_portability_enumeration_and_its_flag) {
    const char *names[] = {"VK_KHR_surface", "VK_EXT_metal_surface", "VK_KHR_portability_enumeration",
                           "VK_KHR_get_physical_device_properties2"};
    Avail a = {{"VK_KHR_surface", "VK_EXT_metal_surface", "VK_KHR_get_physical_device_properties2"}, 3u};
    u32 count = 4u, flags = PORTABILITY_BIT | 0x8u;
    const char *missing = "unset";
    ASSERT_TRUE(platform_vk_resolve_instance_extensions(names, &count, &flags, avail, &a, &missing));
    ASSERT_EQ(count, 3u);
    ASSERT_EQ(flags, 0x8u);
    ASSERT_TRUE(missing == NULL);
    ASSERT_STR_EQ(names[0], "VK_KHR_surface");
    ASSERT_STR_EQ(names[1], "VK_EXT_metal_surface");
    ASSERT_STR_EQ(names[2], "VK_KHR_get_physical_device_properties2");
}

TEST(a_missing_required_extension_fails_and_names_it) {
    const char *names[] = {"VK_KHR_surface", "VK_EXT_metal_surface", "VK_KHR_portability_enumeration"};
    Avail a = {{"VK_KHR_surface", "VK_KHR_portability_enumeration"}, 2u};
    u32 count = 3u, flags = PORTABILITY_BIT;
    const char *missing = NULL;
    ASSERT_FALSE(platform_vk_resolve_instance_extensions(names, &count, &flags, avail, &a, &missing));
    ASSERT_STR_EQ(missing, "VK_EXT_metal_surface");
    /* a required one missing after an optional one was dropped */
    {
        const char *n2[] = {"VK_KHR_portability_enumeration", "VK_KHR_surface"};
        Avail none = {{"x"}, 1u};
        u32 c2 = 2u, f2 = PORTABILITY_BIT;
        ASSERT_FALSE(platform_vk_resolve_instance_extensions(n2, &c2, &f2, avail, &none, &missing));
        ASSERT_STR_EQ(missing, "VK_KHR_surface");
    }
}

TEST(bad_arguments_are_refused) {
    const char *names[] = {"VK_KHR_surface"};
    Avail a = {{"VK_KHR_surface"}, 1u};
    u32 count = 1u, flags = 0u;
    ASSERT_FALSE(platform_vk_resolve_instance_extensions(NULL, &count, &flags, avail, &a, NULL));
    ASSERT_FALSE(platform_vk_resolve_instance_extensions(names, NULL, &flags, avail, &a, NULL));
    ASSERT_FALSE(platform_vk_resolve_instance_extensions(names, &count, NULL, avail, &a, NULL));
    ASSERT_FALSE(platform_vk_resolve_instance_extensions(names, &count, &flags, NULL, &a, NULL));
    ASSERT_TRUE(platform_vk_resolve_instance_extensions(names, &count, &flags, avail, &a, NULL));
    count = 0u;
    ASSERT_TRUE(platform_vk_resolve_instance_extensions(names, &count, &flags, avail, &a, NULL));
    ASSERT_EQ(count, 0u);
}

TEST_MAIN_BEGIN()
    RUN_TEST(only_portability_enumeration_is_optional);
    RUN_TEST(all_present_keeps_everything);
    RUN_TEST(direct_moltenvk_drops_portability_enumeration_and_its_flag);
    RUN_TEST(a_missing_required_extension_fails_and_names_it);
    RUN_TEST(bad_arguments_are_refused);
TEST_MAIN_END()
