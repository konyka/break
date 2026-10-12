#include "test_framework.h"

#include <renderer/sl_dlss.h>

#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#define SET_SL_DIR(v) SetEnvironmentVariableA("BREAK_SL_DIR", (v))
#else
#define SET_SL_DIR(v) 0
#endif

/* Headless contract: with the loader pointed at an empty directory the probe
 * must fail closed, classify the reason, stay idempotent, and shut down
 * safely. The real-runtime path is exercised by the Vulkan graphics suite. */

TEST(missing_runtime_fails_closed)
{
    SLDlssProbeResult result = SL_DLSS_SUPPORTED;
    RHINativeDevice native = {0};

    ASSERT_TRUE(SET_SL_DIR("Z:/definitely/missing/sl"));
    ASSERT_FALSE(sl_dlss_probe(NULL, &result));
    ASSERT_EQ(result, SL_DLSS_MISSING_RUNTIME);
    ASSERT_EQ(sl_dlss_api_status(), SL_DLSS_API_UNAVAILABLE);
    ASSERT_FALSE(sl_dlss_probe(&native, &result));
    ASSERT_EQ(result, SL_DLSS_MISSING_RUNTIME);
    ASSERT_TRUE(SET_SL_DIR(NULL));
    sl_dlss_shutdown();
    ASSERT_EQ(sl_dlss_api_status(), SL_DLSS_API_UNAVAILABLE);
}

TEST(null_result_pointer_is_safe)
{
    ASSERT_TRUE(SET_SL_DIR("Z:/definitely/missing/sl"));
    ASSERT_FALSE(sl_dlss_probe(NULL, NULL));
    ASSERT_TRUE(SET_SL_DIR(NULL));
    sl_dlss_shutdown();
}

TEST(failed_initialization_is_retryable)
{
    SLDlssProbeResult result = SL_DLSS_SUPPORTED;
    ASSERT_TRUE(SET_SL_DIR("Z:/definitely/missing/sl"));
    ASSERT_FALSE(sl_dlss_probe(NULL, &result));
    ASSERT_EQ(result, SL_DLSS_MISSING_RUNTIME);
    sl_dlss_shutdown();
    ASSERT_TRUE(SET_SL_DIR(NULL));
}

TEST(resource_tag_contract_rejects_non_vulkan_placeholders)
{
    RHITextureNativeInfo info = {0};
    SLDlssResourceTagDesc tag = {&info, SL_TAG_SCALING_INPUT_COLOR,
                                 SL_TAG_VALID_UNTIL_EVALUATE};
    ASSERT_FALSE(sl_dlss_resource_tag_desc_validate(&tag));
    info.type = RHI_NATIVE_HANDLE_VULKAN;
    info.image = (void *)(uintptr_t)1u;
    info.view = (void *)(uintptr_t)1u;
    info.width = 1u;
    info.height = 1u;
    ASSERT_TRUE(sl_dlss_resource_tag_desc_validate(&tag));
    tag.type = (SLDlssBufferType)99;
    ASSERT_FALSE(sl_dlss_resource_tag_desc_validate(&tag));
}

TEST(cpp_adapter_is_required_before_evaluation)
{
    RHITextureNativeInfo info = {0};
    SLDlssResourceTagDesc tag = {&info, SL_TAG_SCALING_INPUT_COLOR,
                                 SL_TAG_VALID_UNTIL_EVALUATE};
    info.type = RHI_NATIVE_HANDLE_VULKAN;
    info.image = (void *)(uintptr_t)1u;
    info.view = (void *)(uintptr_t)1u;
    info.width = 1u;
    info.height = 1u;
    sl_dlss_set_cpp_adapter(NULL);
    ASSERT_FALSE(sl_dlss_evaluate_tags(&tag, 1u, 1u, 1u));
}

TEST(cpp_adapter_is_required_before_evaluation)
{
    RHITextureNativeInfo info = {0};
    SLDlssResourceTagDesc tag = {&info, SL_TAG_DEPTH,
                                 SL_TAG_VALID_UNTIL_EVALUATE};
    info.type = RHI_NATIVE_HANDLE_VULKAN;
    info.image = (void *)(uintptr_t)1u;
    info.view = (void *)(uintptr_t)1u;
    info.width = 1u;
    info.height = 1u;
    sl_dlss_set_cpp_adapter(NULL);
    ASSERT_FALSE(sl_dlss_evaluate_tags(&tag, 1u, 1u, 1u));
}

TEST_MAIN_BEGIN()
    RUN_TEST(missing_runtime_fails_closed);
    RUN_TEST(null_result_pointer_is_safe);
    RUN_TEST(failed_initialization_is_retryable);
    RUN_TEST(resource_tag_contract_rejects_non_vulkan_placeholders);
    RUN_TEST(cpp_adapter_is_required_before_evaluation);
    RUN_TEST(cpp_adapter_is_required_before_evaluation);
TEST_MAIN_END()
