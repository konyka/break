#include "test_framework.h"
#include "platform/platform_wsi.h"

static void assert_sizes(const PlatformWsiSurface *surface, u32 logical_w,
                         u32 logical_h, u32 drawable_w, u32 drawable_h)
{
    ASSERT_EQ(surface->logical_width, logical_w);
    ASSERT_EQ(surface->logical_height, logical_h);
    ASSERT_EQ(surface->drawable_width, drawable_w);
    ASSERT_EQ(surface->drawable_height, drawable_h);
}

TEST(wsi_lifecycle_accepts_legal_surface_transitions)
{
    PlatformWsiSurface surface;

    ASSERT_EQ(platform_wsi_surface_init(&surface, true, 320u, 180u, 640u, 360u),
              PLATFORM_WSI_OK);
    ASSERT_EQ(surface.state, PLATFORM_WSI_CREATED);
    assert_sizes(&surface, 320u, 180u, 640u, 360u);
    ASSERT_EQ(platform_wsi_surface_resize(&surface, 400u, 225u, 800u, 450u),
              PLATFORM_WSI_OK);
    ASSERT_EQ(surface.state, PLATFORM_WSI_RESIZED);
    assert_sizes(&surface, 400u, 225u, 800u, 450u);
    ASSERT_EQ(platform_wsi_surface_suspend(&surface), PLATFORM_WSI_OK);
    ASSERT_EQ(surface.state, PLATFORM_WSI_SUSPENDED);
    ASSERT_EQ(platform_wsi_surface_resume(&surface), PLATFORM_WSI_OK);
    ASSERT_EQ(surface.state, PLATFORM_WSI_CREATED);
    ASSERT_EQ(platform_wsi_surface_lose(&surface), PLATFORM_WSI_OK);
    ASSERT_EQ(surface.state, PLATFORM_WSI_LOST);
    ASSERT_EQ(platform_wsi_surface_destroy(&surface), PLATFORM_WSI_OK);
    ASSERT_EQ(surface.state, PLATFORM_WSI_DESTROYING);
}

TEST(wsi_lifecycle_rejects_unavailable_and_invalid_transitions)
{
    PlatformWsiSurface surface;

    ASSERT_EQ(platform_wsi_surface_init(&surface, false, 320u, 180u, 640u, 360u),
              PLATFORM_WSI_UNAVAILABLE_RESULT);
    ASSERT_EQ(surface.state, PLATFORM_WSI_UNAVAILABLE);
    ASSERT_EQ(platform_wsi_surface_resize(&surface, 1u, 1u, 1u, 1u),
              PLATFORM_WSI_UNAVAILABLE_RESULT);
    ASSERT_EQ(platform_wsi_surface_resume(&surface), PLATFORM_WSI_UNAVAILABLE_RESULT);

    ASSERT_EQ(platform_wsi_surface_init(&surface, true, 320u, 180u, 640u, 360u),
              PLATFORM_WSI_OK);
    ASSERT_EQ(platform_wsi_surface_resume(&surface), PLATFORM_WSI_INVALID_TRANSITION);
    ASSERT_EQ(platform_wsi_surface_destroy(&surface), PLATFORM_WSI_OK);
    ASSERT_EQ(platform_wsi_surface_destroy(&surface), PLATFORM_WSI_INVALID_TRANSITION);
    ASSERT_EQ(platform_wsi_surface_resize(&surface, 1u, 1u, 1u, 1u),
              PLATFORM_WSI_INVALID_TRANSITION);
}

TEST(wsi_lifecycle_compiles_for_named_backend)
{
    PlatformWsiSurface surface;
    ASSERT_EQ(platform_wsi_surface_init(&surface, true, 1u, 1u, 1u, 1u),
              PLATFORM_WSI_OK);
    ASSERT_EQ(surface.backend, PLATFORM_WSI_COMPILE_BACKEND);
#if defined(SIMULATE_QNX)
    ASSERT_EQ(surface.backend, PLATFORM_WSI_BACKEND_QNX);
#endif
}

TEST(win32_wsi_contract_requires_direct_flip_discard_and_tearing_support)
{
    PlatformWsiSwapchain swapchain;

    ASSERT_EQ(platform_wsi_swapchain_init(
                  &swapchain, PLATFORM_WSI_QUEUE_COPY, true, true, false,
                  2u, 320u, 180u, 640u, 360u),
              PLATFORM_WSI_INVALID_ARGUMENT);
    ASSERT_EQ(platform_wsi_swapchain_init(
                  &swapchain, PLATFORM_WSI_QUEUE_DIRECT, true, false, true,
                  2u, 320u, 180u, 640u, 360u),
              PLATFORM_WSI_UNSUPPORTED);
    ASSERT_EQ(platform_wsi_swapchain_init(
                  &swapchain, PLATFORM_WSI_QUEUE_DIRECT, true, false, false,
                  2u, 320u, 180u, 640u, 360u),
              PLATFORM_WSI_OK);
}

TEST(win32_wsi_contract_orders_present_and_retires_resized_buffers)
{
    PlatformWsiSwapchain swapchain;
    PlatformWsiBackBuffer old_buffer;
    PlatformWsiBackBuffer new_buffer;

    ASSERT_EQ(platform_wsi_swapchain_init(
                  &swapchain, PLATFORM_WSI_QUEUE_DIRECT, true, true, true,
                  3u, 320u, 180u, 640u, 360u),
              PLATFORM_WSI_OK);
    ASSERT_EQ(platform_wsi_swapchain_present(&swapchain, NULL),
              PLATFORM_WSI_INVALID_ARGUMENT);
    ASSERT_EQ(platform_wsi_swapchain_begin_frame(&swapchain, &old_buffer),
              PLATFORM_WSI_OK);
    ASSERT_EQ(platform_wsi_swapchain_ready(&swapchain),
              PLATFORM_WSI_INVALID_TRANSITION);
    ASSERT_EQ(platform_wsi_swapchain_resize(&swapchain, 400u, 225u, 800u, 450u),
              PLATFORM_WSI_INVALID_TRANSITION);
    ASSERT_EQ(platform_wsi_swapchain_present(&swapchain, &old_buffer),
              PLATFORM_WSI_OK);
    ASSERT_EQ(platform_wsi_swapchain_ready(&swapchain), PLATFORM_WSI_OK);
    ASSERT_EQ(platform_wsi_swapchain_resize(&swapchain, 400u, 225u, 800u, 450u),
              PLATFORM_WSI_OK);
    ASSERT_TRUE(old_buffer.retired ||
                old_buffer.generation != swapchain.generation);
    ASSERT_EQ(platform_wsi_swapchain_begin_frame(&swapchain, &new_buffer),
              PLATFORM_WSI_OK);
    ASSERT_EQ(new_buffer.generation, swapchain.generation);
    ASSERT_EQ(platform_wsi_swapchain_present(&swapchain, &old_buffer),
              PLATFORM_WSI_INVALID_ARGUMENT);
    ASSERT_EQ(platform_wsi_swapchain_present(&swapchain, &new_buffer),
              PLATFORM_WSI_OK);
    ASSERT_EQ(swapchain.logical_width, 400u);
    ASSERT_EQ(swapchain.logical_height, 225u);
    ASSERT_EQ(swapchain.drawable_width, 800u);
    ASSERT_EQ(swapchain.drawable_height, 450u);
}

TEST(wsi_frame_allowed_only_when_created_or_resized)
{
    PlatformWsiSurface surface;
    ASSERT_EQ(platform_wsi_surface_init(&surface, true, 100u, 100u, 100u, 100u),
              PLATFORM_WSI_OK);
    ASSERT_TRUE(platform_wsi_frame_allowed(&surface));
    ASSERT_EQ(platform_wsi_surface_resize(&surface, 200u, 200u, 200u, 200u),
              PLATFORM_WSI_OK);
    ASSERT_TRUE(platform_wsi_frame_allowed(&surface));
    ASSERT_EQ(platform_wsi_surface_suspend(&surface), PLATFORM_WSI_OK);
    ASSERT_FALSE(platform_wsi_frame_allowed(&surface));
    ASSERT_EQ(platform_wsi_surface_resume(&surface), PLATFORM_WSI_OK);
    ASSERT_TRUE(platform_wsi_frame_allowed(&surface));
    ASSERT_EQ(platform_wsi_surface_lose(&surface), PLATFORM_WSI_OK);
    ASSERT_FALSE(platform_wsi_frame_allowed(&surface));
    ASSERT_FALSE(platform_wsi_frame_allowed(NULL));
}

TEST(wsi_teardown_rejected_while_destroying)
{
    PlatformWsiSurface surface;
    ASSERT_EQ(platform_wsi_surface_init(&surface, true, 100u, 100u, 100u, 100u),
              PLATFORM_WSI_OK);
    ASSERT_TRUE(platform_wsi_rhi_teardown_allowed(&surface));
    ASSERT_EQ(platform_wsi_surface_destroy(&surface), PLATFORM_WSI_OK);
    ASSERT_FALSE(platform_wsi_rhi_teardown_allowed(&surface));
    ASSERT_FALSE(platform_wsi_rhi_teardown_allowed(NULL));
}

TEST_MAIN_BEGIN()
    RUN_TEST(wsi_lifecycle_accepts_legal_surface_transitions);
    RUN_TEST(wsi_lifecycle_rejects_unavailable_and_invalid_transitions);
    RUN_TEST(wsi_lifecycle_compiles_for_named_backend);
    RUN_TEST(win32_wsi_contract_requires_direct_flip_discard_and_tearing_support);
    RUN_TEST(win32_wsi_contract_orders_present_and_retires_resized_buffers);
    RUN_TEST(wsi_frame_allowed_only_when_created_or_resized);
    RUN_TEST(wsi_teardown_rejected_while_destroying);
TEST_MAIN_END()
