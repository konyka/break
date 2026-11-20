#include "test_framework.h"
#include <platform/platform.h>
#include <rhi/rhi.h>
#include <rhi/rhi_vk_screen_post.h>
#include <vulkan/vulkan.h>

static int post_attempts;
static int acquire_calls;
static int present_calls;
static int post_failure_limit = 2;

bool __real_vk_qnx_screen_post_present(VKQnxScreenPost *post, RHIDevice *dev);

bool __wrap_vk_qnx_screen_post_present(VKQnxScreenPost *post, RHIDevice *dev) {
  post_attempts++;
  if (post_attempts <= post_failure_limit) return false;
  return __real_vk_qnx_screen_post_present(post, dev);
}

VkResult __real_vkAcquireNextImageKHR(VkDevice device, VkSwapchainKHR swapchain,
                                      uint64_t timeout, VkSemaphore semaphore,
                                      VkFence fence, uint32_t *image_index);

VkResult __wrap_vkAcquireNextImageKHR(VkDevice device, VkSwapchainKHR swapchain,
                                      uint64_t timeout, VkSemaphore semaphore,
                                      VkFence fence, uint32_t *image_index) {
  acquire_calls++;
  return __real_vkAcquireNextImageKHR(device, swapchain, timeout, semaphore,
                                      fence, image_index);
}

VkResult __real_vkQueuePresentKHR(VkQueue queue, const VkPresentInfoKHR *info);
static VkResult forced_present_result = VK_SUCCESS;

VkResult __wrap_vkQueuePresentKHR(VkQueue queue, const VkPresentInfoKHR *info) {
  VkResult result = forced_present_result;
  present_calls++;
  forced_present_result = VK_SUCCESS;
  if (result != VK_SUCCESS) return result;
  return __real_vkQueuePresentKHR(queue, info);
}

TEST(screen_post_failure_preserves_vulkan_present_lifecycle) {
  const PlatformConfig config = {.width = 64, .height = 48,
                                 .title = "QNX Vulkan post failure recovery"};
  Platform *platform = platform_create(&config);
  RHIDevice *device = NULL;
  RHIResult results[3] = {RHI_RESULT_UNAVAILABLE, RHI_RESULT_UNAVAILABLE,
                          RHI_RESULT_UNAVAILABLE};
  u32 width = 0, height = 0;
  int completed = 0;
  int i;
  post_attempts = 0;
  acquire_calls = 0;
  present_calls = 0;
  ASSERT_NOT_NULL(platform);
  platform_get_drawable_size(platform, &width, &height);
  device = rhi_device_create(RHI_BACKEND_VULKAN,
                             platform_surface_native(platform),
                             platform_display_native(platform), width, height);
  ASSERT_NOT_NULL(device);
  rhi_set_vsync(device, false);
  for (i = 0; i < 3; ++i) {
    RHICmdBuffer *cmd = rhi_frame_begin(device);
    if (cmd == NULL) break;
    rhi_cmd_clear_color(cmd, 0.1f, 0.1f, 0.15f, 1.0f);
    rhi_frame_end(device);
    results[i] = rhi_present_ex(device);
    completed++;
  }
  rhi_device_destroy(device);
  platform_destroy(platform);
  ASSERT_EQ(completed, 3);
  ASSERT_EQ(results[0], RHI_RESULT_ERROR);
  ASSERT_EQ(results[1], RHI_RESULT_ERROR);
  ASSERT_EQ(results[2], RHI_RESULT_OK);
  ASSERT_EQ(post_attempts, 3);
  ASSERT_EQ(acquire_calls, 3);
  ASSERT_EQ(present_calls, 3);
}

TEST(screen_post_failure_result_survives_out_of_date_and_recovers) {
  const PlatformConfig config = {.width = 64, .height = 48,
                                 .title = "QNX Vulkan combined failure recovery"};
  Platform *platform = platform_create(&config);
  RHIDevice *device = NULL;
  RHIResult results[2] = {RHI_RESULT_UNAVAILABLE, RHI_RESULT_UNAVAILABLE};
  u32 width = 0, height = 0;
  int completed = 0;
  int i;
  post_failure_limit = 1;
  post_attempts = 0;
  acquire_calls = 0;
  present_calls = 0;
  forced_present_result = VK_ERROR_OUT_OF_DATE_KHR;
  ASSERT_NOT_NULL(platform);
  platform_get_drawable_size(platform, &width, &height);
  device = rhi_device_create(RHI_BACKEND_VULKAN,
                             platform_surface_native(platform),
                             platform_display_native(platform), width, height);
  ASSERT_NOT_NULL(device);
  rhi_set_vsync(device, false);
  for (i = 0; i < 2; ++i) {
    RHICmdBuffer *cmd = rhi_frame_begin(device);
    if (cmd == NULL) break;
    rhi_cmd_clear_color(cmd, 0.1f, 0.1f, 0.15f, 1.0f);
    rhi_frame_end(device);
    results[i] = rhi_present_ex(device);
    completed++;
  }
  rhi_device_destroy(device);
  platform_destroy(platform);
  ASSERT_EQ(completed, 2);
  ASSERT_EQ(results[0], RHI_RESULT_ERROR);
  ASSERT_EQ(results[1], RHI_RESULT_OK);
  ASSERT_EQ(post_attempts, 2);
  ASSERT_EQ(acquire_calls, 2);
  ASSERT_EQ(present_calls, 2);
}

TEST_MAIN_BEGIN()
  RUN_TEST(screen_post_failure_preserves_vulkan_present_lifecycle);
  RUN_TEST(screen_post_failure_result_survives_out_of_date_and_recovers);
TEST_MAIN_END()
