#include "test_framework.h"

#include "platform/platform.h"

TEST(valid_configuration_is_accepted)
{
    const PlatformConfig config = {.width = 640, .height = 480, .title = "Break"};

    ASSERT_TRUE(platform_config_valid(&config));
    ASSERT_EQ(config.native_window, NULL);
    ASSERT_EQ(config.native_display, NULL);
}

TEST(null_configuration_is_rejected)
{
    ASSERT_FALSE(platform_config_valid(NULL));
}

TEST(configuration_requires_title)
{
    const PlatformConfig config = {.width = 640, .height = 480, .title = NULL};
    const PlatformConfig empty_title = {.width = 640, .height = 480, .title = ""};

    ASSERT_FALSE(platform_config_valid(&config));
    ASSERT_FALSE(platform_config_valid(&empty_title));
}

TEST(configuration_rejects_malformed_utf8_titles)
{
    const PlatformConfig truncated = {.width = 640, .height = 480, .title = "\xE4\xB8"};
    const PlatformConfig truncated_two_byte = {.width = 640, .height = 480, .title = "\xC2"};
    const PlatformConfig truncated_three_byte = {.width = 640, .height = 480, .title = "\xE0\xA0"};
    const PlatformConfig truncated_four_byte = {.width = 640, .height = 480, .title = "\xF0\x90\x80"};
    const PlatformConfig invalid_continuation = {.width = 640, .height = 480, .title = "\xE2\x28\xA1"};
    const PlatformConfig invalid_lead_only = {.width = 640, .height = 480, .title = "\x80"};
    const PlatformConfig truncated_three_byte_only = {.width = 640, .height = 480, .title = "\xE0"};
    const PlatformConfig truncated_four_byte_only = {.width = 640, .height = 480, .title = "\xF0"};
    const PlatformConfig invalid_lead = {.width = 640, .height = 480, .title = "\x80X"};
    const PlatformConfig invalid_two_byte_lead = {.width = 640, .height = 480, .title = "\xC0\x80"};
    const PlatformConfig invalid_four_byte_lead = {.width = 640, .height = 480, .title = "\xF5\x80\x80\x80"};
    const PlatformConfig overlong = {.width = 640, .height = 480, .title = "\xC0\x80"};
    const PlatformConfig surrogate = {.width = 640, .height = 480, .title = "\xED\xA0\x80"};
    const PlatformConfig out_of_range = {.width = 640, .height = 480, .title = "\xF4\x90\x80\x80"};

    ASSERT_FALSE(platform_config_valid(&truncated));
    ASSERT_FALSE(platform_config_valid(&truncated_two_byte));
    ASSERT_FALSE(platform_config_valid(&truncated_three_byte));
    ASSERT_FALSE(platform_config_valid(&truncated_four_byte));
    ASSERT_FALSE(platform_config_valid(&invalid_continuation));
    ASSERT_FALSE(platform_config_valid(&invalid_lead_only));
    ASSERT_FALSE(platform_config_valid(&truncated_three_byte_only));
    ASSERT_FALSE(platform_config_valid(&truncated_four_byte_only));
    ASSERT_FALSE(platform_config_valid(&invalid_lead));
    ASSERT_FALSE(platform_config_valid(&invalid_two_byte_lead));
    ASSERT_FALSE(platform_config_valid(&invalid_four_byte_lead));
    ASSERT_FALSE(platform_config_valid(&overlong));
    ASSERT_FALSE(platform_config_valid(&surrogate));
    ASSERT_FALSE(platform_config_valid(&out_of_range));
}

TEST(configuration_accepts_maximum_unicode_scalar_title)
{
    const PlatformConfig config = {.width = 640, .height = 480, .title = "\xF4\x8F\xBF\xBF"};

    ASSERT_TRUE(platform_config_valid(&config));
}

TEST(configuration_requires_nonzero_dimensions)
{
    const PlatformConfig zero_width = {.width = 0, .height = 480, .title = "Break"};
    const PlatformConfig zero_height = {.width = 640, .height = 0, .title = "Break"};

    ASSERT_FALSE(platform_config_valid(&zero_width));
    ASSERT_FALSE(platform_config_valid(&zero_height));
}

TEST(configuration_accepts_maximum_native_safe_dimensions)
{
    const PlatformConfig config = {
        PLATFORM_MAX_WINDOW_DIMENSION,
        PLATFORM_MAX_WINDOW_DIMENSION,
        .title = "Break"
    };

    ASSERT_TRUE(platform_config_valid(&config));
}

TEST(configuration_rejects_dimensions_above_native_safe_limit)
{
    const PlatformConfig width_too_large = {
        .width = PLATFORM_MAX_WINDOW_DIMENSION + 1u, .height = 480, .title = "Break"
    };
    const PlatformConfig height_too_large = {
        .width = 640, .height = PLATFORM_MAX_WINDOW_DIMENSION + 1u, .title = "Break"
    };

    ASSERT_FALSE(platform_config_valid(&width_too_large));
    ASSERT_FALSE(platform_config_valid(&height_too_large));
}

TEST(configuration_enforces_title_byte_budget)
{
    char accepted_title[PLATFORM_MAX_WINDOW_TITLE_BYTES];
    char rejected_title[PLATFORM_MAX_WINDOW_TITLE_BYTES + 1u];
    PlatformConfig accepted;
    PlatformConfig rejected;

    memset(accepted_title, 'a', PLATFORM_MAX_WINDOW_TITLE_BYTES - 1u);
    accepted_title[PLATFORM_MAX_WINDOW_TITLE_BYTES - 1u] = '\0';
    accepted.width = 640;
    accepted.height = 480;
    accepted.title = accepted_title;

    memset(rejected_title, 'a', PLATFORM_MAX_WINDOW_TITLE_BYTES);
    rejected_title[PLATFORM_MAX_WINDOW_TITLE_BYTES] = '\0';
    rejected.width = 640;
    rejected.height = 480;
    rejected.title = rejected_title;

    ASSERT_TRUE(platform_config_valid(&accepted));
    ASSERT_FALSE(platform_config_valid(&rejected));
}

TEST(configuration_accepts_opaque_native_handles)
{
    int window;
    int display;
    const PlatformConfig config = {
        640, 480, "Break", &window, &display
    };

    ASSERT_TRUE(platform_config_valid(&config));
    ASSERT_EQ(config.native_window, &window);
    ASSERT_EQ(config.native_display, &display);
}

TEST_MAIN_BEGIN()
    RUN_TEST(valid_configuration_is_accepted);
    RUN_TEST(null_configuration_is_rejected);
    RUN_TEST(configuration_requires_title);
    RUN_TEST(configuration_rejects_malformed_utf8_titles);
    RUN_TEST(configuration_accepts_maximum_unicode_scalar_title);
    RUN_TEST(configuration_requires_nonzero_dimensions);
    RUN_TEST(configuration_accepts_maximum_native_safe_dimensions);
    RUN_TEST(configuration_rejects_dimensions_above_native_safe_limit);
    RUN_TEST(configuration_enforces_title_byte_budget);
    RUN_TEST(configuration_accepts_opaque_native_handles);
TEST_MAIN_END()
