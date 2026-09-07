#include "test_framework.h"

#include "platform/platform.h"

TEST(valid_configuration_is_accepted)
{
    const PlatformConfig config = {640, 480, "Break"};

    ASSERT_TRUE(platform_config_valid(&config));
}

TEST(null_configuration_is_rejected)
{
    ASSERT_FALSE(platform_config_valid(NULL));
}

TEST(configuration_requires_title)
{
    const PlatformConfig config = {640, 480, NULL};
    const PlatformConfig empty_title = {640, 480, ""};

    ASSERT_FALSE(platform_config_valid(&config));
    ASSERT_FALSE(platform_config_valid(&empty_title));
}

TEST(configuration_rejects_malformed_utf8_titles)
{
    const PlatformConfig truncated = {640, 480, "\xE4\xB8"};
    const PlatformConfig truncated_two_byte = {640, 480, "\xC2"};
    const PlatformConfig truncated_three_byte = {640, 480, "\xE0\xA0"};
    const PlatformConfig truncated_four_byte = {640, 480, "\xF0\x90\x80"};
    const PlatformConfig invalid_continuation = {640, 480, "\xE2\x28\xA1"};
    const PlatformConfig invalid_lead_only = {640, 480, "\x80"};
    const PlatformConfig truncated_three_byte_only = {640, 480, "\xE0"};
    const PlatformConfig truncated_four_byte_only = {640, 480, "\xF0"};
    const PlatformConfig invalid_lead = {640, 480, "\x80X"};
    const PlatformConfig invalid_two_byte_lead = {640, 480, "\xC0\x80"};
    const PlatformConfig invalid_four_byte_lead = {640, 480, "\xF5\x80\x80\x80"};
    const PlatformConfig overlong = {640, 480, "\xC0\x80"};
    const PlatformConfig surrogate = {640, 480, "\xED\xA0\x80"};
    const PlatformConfig out_of_range = {640, 480, "\xF4\x90\x80\x80"};

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
    const PlatformConfig config = {640, 480, "\xF4\x8F\xBF\xBF"};

    ASSERT_TRUE(platform_config_valid(&config));
}

TEST(configuration_requires_nonzero_dimensions)
{
    const PlatformConfig zero_width = {0, 480, "Break"};
    const PlatformConfig zero_height = {640, 0, "Break"};

    ASSERT_FALSE(platform_config_valid(&zero_width));
    ASSERT_FALSE(platform_config_valid(&zero_height));
}

TEST(configuration_accepts_maximum_native_safe_dimensions)
{
    const PlatformConfig config = {
        PLATFORM_MAX_WINDOW_DIMENSION,
        PLATFORM_MAX_WINDOW_DIMENSION,
        "Break"
    };

    ASSERT_TRUE(platform_config_valid(&config));
}

TEST(configuration_rejects_dimensions_above_native_safe_limit)
{
    const PlatformConfig width_too_large = {
        PLATFORM_MAX_WINDOW_DIMENSION + 1u, 480, "Break"
    };
    const PlatformConfig height_too_large = {
        640, PLATFORM_MAX_WINDOW_DIMENSION + 1u, "Break"
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
TEST_MAIN_END()
