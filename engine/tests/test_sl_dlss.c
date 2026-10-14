#include "test_framework.h"

#include <renderer/sl_dlss.h>
#include <rhi/rhi_native_vulkan.h>

/* The loader unit target is intentionally independent of the full RHI. */
bool rhi_cmd_buffer_get_native_info(const RHIDevice *dev,
                                    const RHICmdBuffer *cmd,
                                    RHICmdBufferNativeInfo *out) {
    if (out != NULL) memset(out, 0, sizeof(*out));
    if ((uintptr_t)dev != 1u || (uintptr_t)cmd != 1u || out == NULL)
        return false;
    out->type = RHI_NATIVE_HANDLE_VULKAN;
    out->command_buffer = (void *)(uintptr_t)1u;
    out->recording = true;
    return true;
}

#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#define SET_SL_DIR(v) SetEnvironmentVariableA("BREAK_SL_DIR", (v))
#else
#define SET_SL_DIR(v) 0
#endif

static int g_adapter_calls;
static int g_capture_calls;
static int g_restore_calls;

static bool test_capture_state(void *context, void *native_command_buffer) {
    (void)context;
    if (native_command_buffer == NULL) return false;
    g_capture_calls++;
    return true;
}

static bool test_restore_state(void *context, void *native_command_buffer) {
    (void)context;
    if (native_command_buffer == NULL) return false;
    g_restore_calls++;
    return true;
}

static bool test_adapter_callback(void *context,
                                  const SLDlssResourceTagDesc *tags,
                                  u32 tag_count, u32 output_width,
                                  u32 output_height,
                                  void *native_command_buffer) {
    (void)context;
    if (native_command_buffer == NULL) return false;
    if (tags == NULL || tag_count != 1u || output_width != 2u ||
        output_height != 2u)
        return false;
    g_adapter_calls++;
    return true;
}

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
    info.memory = (void *)(uintptr_t)1u;
    info.view = (void *)(uintptr_t)1u;
    info.native_format = 37u;
    info.width = 1u;
    info.height = 1u;
    info.mip_levels = 1u;
    info.array_layers = 1u;
    ASSERT_TRUE(sl_dlss_resource_tag_desc_validate(&tag));
    tag.type = (SLDlssBufferType)99;
    ASSERT_FALSE(sl_dlss_resource_tag_desc_validate(&tag));
}

TEST(cpp_adapter_is_required_before_evaluation)
{
    RHITextureNativeInfo info = {0};
    SLDlssResourceTagDesc tag = {&info, SL_TAG_DEPTH,
                                 SL_TAG_VALID_UNTIL_EVALUATE};
    info.type = RHI_NATIVE_HANDLE_VULKAN;
    info.image = (void *)(uintptr_t)1u;
    info.memory = (void *)(uintptr_t)1u;
    info.view = (void *)(uintptr_t)1u;
    info.native_format = 37u;
    info.width = 1u;
    info.height = 1u;
    info.mip_levels = 1u;
    info.array_layers = 1u;
    sl_dlss_set_cpp_adapter(NULL);
    ASSERT_FALSE(sl_dlss_evaluate_tags(&tag, 1u, 1u, 1u));
}

TEST(cpp_adapter_forwards_validated_tags)
{
    RHITextureNativeInfo info = {0};
    SLDlssResourceTagDesc tag = {&info, SL_TAG_DEPTH,
                                 SL_TAG_VALID_UNTIL_PRESENT};
    SLDlssCppAdapter adapter = {test_capture_state, test_adapter_callback,
                                test_restore_state, NULL};
    info.type = RHI_NATIVE_HANDLE_VULKAN;
    info.image = (void *)(uintptr_t)1u;
    info.memory = (void *)(uintptr_t)1u;
    info.view = (void *)(uintptr_t)1u;
    info.native_format = 37u;
    info.width = 2u;
    info.height = 2u;
    info.mip_levels = 1u;
    info.array_layers = 1u;
    g_adapter_calls = 0;
    g_capture_calls = 0;
    g_restore_calls = 0;
    ASSERT_TRUE(sl_dlss_set_cpp_adapter(&adapter));
    ASSERT_FALSE(sl_dlss_evaluate_tags(&tag, 1u, 2u, 2u));
    ASSERT_EQ(g_adapter_calls, 0);
    ASSERT_TRUE(sl_dlss_evaluate_tags_with_command_buffer(
        (const RHIDevice *)(uintptr_t)1u,
        (const RHICmdBuffer *)(uintptr_t)1u, &tag, 1u, 2u, 2u));
    ASSERT_EQ(g_adapter_calls, 1);
    ASSERT_EQ(g_capture_calls, 1);
    ASSERT_EQ(g_restore_calls, 1);
    info.view = NULL;
    ASSERT_FALSE(sl_dlss_evaluate_tags_with_command_buffer(
        (const RHIDevice *)(uintptr_t)1u,
        (const RHICmdBuffer *)(uintptr_t)1u, &tag, 1u, 2u, 2u));
    ASSERT_EQ(g_adapter_calls, 1);
    sl_dlss_set_cpp_adapter(NULL);
}

TEST(command_buffer_evaluation_requires_recording_native_handle)
{
    RHITextureNativeInfo info = {0};
    SLDlssResourceTagDesc tag = {&info, SL_TAG_DEPTH,
                                 SL_TAG_VALID_UNTIL_PRESENT};
    SLDlssCppAdapter adapter = {test_capture_state, test_adapter_callback,
                                test_restore_state, NULL};
    info.type = RHI_NATIVE_HANDLE_VULKAN;
    info.image = (void *)(uintptr_t)1u;
    info.memory = (void *)(uintptr_t)1u;
    info.view = (void *)(uintptr_t)1u;
    info.native_format = 37u;
    info.width = 1u;
    info.height = 1u;
    info.mip_levels = 1u;
    info.array_layers = 1u;
    ASSERT_TRUE(sl_dlss_set_cpp_adapter(&adapter));
    ASSERT_FALSE(sl_dlss_evaluate_tags_with_command_buffer(
        (const RHIDevice *)(uintptr_t)1u,
        (const RHICmdBuffer *)(uintptr_t)1u, &tag, 1u, 1u, 1u));
    sl_dlss_set_cpp_adapter(NULL);
}

TEST(command_buffer_evaluation_rejects_missing_rhi_context)
{
    RHITextureNativeInfo info = {0};
    SLDlssResourceTagDesc tag = {&info, SL_TAG_DEPTH,
                                 SL_TAG_VALID_UNTIL_PRESENT};
    SLDlssCppAdapter adapter = {test_capture_state, test_adapter_callback,
                                test_restore_state, NULL};
    info.type = RHI_NATIVE_HANDLE_VULKAN;
    info.image = (void *)(uintptr_t)1u;
    info.memory = (void *)(uintptr_t)1u;
    info.view = (void *)(uintptr_t)1u;
    info.native_format = 37u;
    info.width = 1u;
    info.height = 1u;
    info.mip_levels = 1u;
    info.array_layers = 1u;
    g_adapter_calls = 0;
    g_capture_calls = 0;
    g_restore_calls = 0;
    ASSERT_TRUE(sl_dlss_set_cpp_adapter(&adapter));
    ASSERT_FALSE(sl_dlss_evaluate_tags_with_command_buffer(
        NULL, NULL, &tag, 1u, 1u, 1u));
    ASSERT_EQ(g_adapter_calls, 0);
    ASSERT_EQ(g_capture_calls, 0);
    ASSERT_EQ(g_restore_calls, 0);
    ASSERT_FALSE(sl_dlss_evaluate_tags_with_command_buffer(
        (const RHIDevice *)(uintptr_t)1u, NULL, &tag, 1u, 1u, 1u));
    ASSERT_FALSE(sl_dlss_evaluate_tags_with_command_buffer(
        NULL, (const RHICmdBuffer *)(uintptr_t)1u, &tag, 1u, 1u, 1u));
    ASSERT_EQ(g_adapter_calls, 0);
    sl_dlss_set_cpp_adapter(NULL);
}

TEST(resource_tag_contract_rejects_incomplete_vulkan_metadata)
{
    RHITextureNativeInfo info = {0};
    SLDlssResourceTagDesc tag = {&info, SL_TAG_DEPTH,
                                 SL_TAG_VALID_UNTIL_PRESENT};
    info.type = RHI_NATIVE_HANDLE_VULKAN;
    info.image = (void *)(uintptr_t)1u;
    info.memory = (void *)(uintptr_t)1u;
    info.view = (void *)(uintptr_t)1u;
    info.width = 1u;
    info.height = 1u;
    info.mip_levels = 1u;
    info.array_layers = 1u;
    ASSERT_FALSE(sl_dlss_resource_tag_desc_validate(&tag));
    info.native_format = 37u;
    ASSERT_TRUE(sl_dlss_resource_tag_desc_validate(&tag));
    info.array_layers = 0u;
    ASSERT_FALSE(sl_dlss_resource_tag_desc_validate(&tag));
}

TEST_MAIN_BEGIN()
    RUN_TEST(missing_runtime_fails_closed);
    RUN_TEST(null_result_pointer_is_safe);
    RUN_TEST(failed_initialization_is_retryable);
    RUN_TEST(resource_tag_contract_rejects_non_vulkan_placeholders);
    RUN_TEST(cpp_adapter_is_required_before_evaluation);
    RUN_TEST(cpp_adapter_forwards_validated_tags);
    RUN_TEST(resource_tag_contract_rejects_incomplete_vulkan_metadata);
    RUN_TEST(command_buffer_evaluation_requires_recording_native_handle);
    RUN_TEST(command_buffer_evaluation_rejects_missing_rhi_context);
TEST_MAIN_END()
