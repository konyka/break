#pragma once

#include <core/types.h>

#if defined(__GNUC__) || defined(__clang__)
#define PLATFORM_WSI_INLINE static inline __attribute__((unused))
#else
#define PLATFORM_WSI_INLINE static inline
#endif

typedef enum PlatformWsiState {
    PLATFORM_WSI_UNAVAILABLE = 0,
    PLATFORM_WSI_CREATED,
    PLATFORM_WSI_RESIZED,
    PLATFORM_WSI_LOST,
    PLATFORM_WSI_SUSPENDED,
    PLATFORM_WSI_DESTROYING,
} PlatformWsiState;

typedef enum PlatformWsiResult {
    PLATFORM_WSI_OK = 0,
    PLATFORM_WSI_INVALID_TRANSITION = -1,
    PLATFORM_WSI_UNAVAILABLE_RESULT = -2,
    PLATFORM_WSI_INVALID_ARGUMENT = -3,
    PLATFORM_WSI_UNSUPPORTED = -4,
} PlatformWsiResult;

typedef enum PlatformWsiQueueType {
    PLATFORM_WSI_QUEUE_DIRECT = 0,
    PLATFORM_WSI_QUEUE_COPY,
    PLATFORM_WSI_QUEUE_COMPUTE,
} PlatformWsiQueueType;

typedef enum PlatformWsiSwapchainState {
    PLATFORM_WSI_SWAPCHAIN_UNINITIALIZED = 0,
    PLATFORM_WSI_SWAPCHAIN_READY,
    PLATFORM_WSI_SWAPCHAIN_RENDERING,
    PLATFORM_WSI_SWAPCHAIN_PRESENT,
    PLATFORM_WSI_SWAPCHAIN_RETIRED,
} PlatformWsiSwapchainState;

typedef struct PlatformWsiBackBuffer {
    u64 generation;
    u32 index;
    bool retired;
} PlatformWsiBackBuffer;

typedef struct PlatformWsiSwapchain {
    PlatformWsiSwapchainState state;
    PlatformWsiQueueType queue_type;
    bool flip_discard;
    bool tearing_supported;
    bool tearing_enabled;
    u64 generation;
    u32 buffer_count;
    u32 logical_width;
    u32 logical_height;
    u32 drawable_width;
    u32 drawable_height;
    PlatformWsiBackBuffer current_buffer;
} PlatformWsiSwapchain;

typedef enum PlatformWsiBackend {
    PLATFORM_WSI_BACKEND_X11 = 0,
    PLATFORM_WSI_BACKEND_WAYLAND,
    PLATFORM_WSI_BACKEND_WIN32,
    PLATFORM_WSI_BACKEND_COCOA,
    PLATFORM_WSI_BACKEND_ANDROID,
    PLATFORM_WSI_BACKEND_IOS,
    PLATFORM_WSI_BACKEND_QNX,
} PlatformWsiBackend;

#if defined(SIMULATE_WAYLAND)
#define PLATFORM_WSI_COMPILE_BACKEND PLATFORM_WSI_BACKEND_WAYLAND
#elif defined(SIMULATE_WIN32)
#define PLATFORM_WSI_COMPILE_BACKEND PLATFORM_WSI_BACKEND_WIN32
#elif defined(SIMULATE_COCOA)
#define PLATFORM_WSI_COMPILE_BACKEND PLATFORM_WSI_BACKEND_COCOA
#elif defined(SIMULATE_ANDROID)
#define PLATFORM_WSI_COMPILE_BACKEND PLATFORM_WSI_BACKEND_ANDROID
#elif defined(SIMULATE_IOS)
#define PLATFORM_WSI_COMPILE_BACKEND PLATFORM_WSI_BACKEND_IOS
#elif defined(SIMULATE_QNX) || \
    (defined(ENGINE_PLATFORM_QNX) && defined(ENGINE_QNX_SCREEN))
#define PLATFORM_WSI_COMPILE_BACKEND PLATFORM_WSI_BACKEND_QNX
#else
#define PLATFORM_WSI_COMPILE_BACKEND PLATFORM_WSI_BACKEND_X11
#endif

typedef struct PlatformWsiSurface {
    PlatformWsiState state;
    PlatformWsiBackend backend;
    u32 logical_width;
    u32 logical_height;
    u32 drawable_width;
    u32 drawable_height;
} PlatformWsiSurface;

PLATFORM_WSI_INLINE bool platform_wsi_sizes_valid(u32 logical_width,
                                                  u32 logical_height,
                                                  u32 drawable_width,
                                                  u32 drawable_height)
{
    return logical_width > 0u && logical_height > 0u && drawable_width > 0u &&
           drawable_height > 0u;
}

PLATFORM_WSI_INLINE PlatformWsiResult platform_wsi_swapchain_init(
    PlatformWsiSwapchain *swapchain, PlatformWsiQueueType queue_type,
    bool flip_discard, bool tearing_supported, bool tearing_enabled,
    u32 buffer_count, u32 logical_width, u32 logical_height,
    u32 drawable_width, u32 drawable_height)
{
    if (swapchain == NULL) return PLATFORM_WSI_INVALID_ARGUMENT;
    swapchain->state = PLATFORM_WSI_SWAPCHAIN_UNINITIALIZED;
    swapchain->queue_type = queue_type;
    swapchain->flip_discard = flip_discard;
    swapchain->tearing_supported = tearing_supported;
    swapchain->tearing_enabled = tearing_enabled;
    swapchain->generation = 0u;
    swapchain->buffer_count = 0u;
    swapchain->logical_width = 0u;
    swapchain->logical_height = 0u;
    swapchain->drawable_width = 0u;
    swapchain->drawable_height = 0u;
    swapchain->current_buffer.generation = 0u;
    swapchain->current_buffer.index = 0u;
    swapchain->current_buffer.retired = true;
    if (queue_type != PLATFORM_WSI_QUEUE_DIRECT || !flip_discard ||
        buffer_count < 2u || !platform_wsi_sizes_valid(
            logical_width, logical_height, drawable_width, drawable_height)) {
        return PLATFORM_WSI_INVALID_ARGUMENT;
    }
    if (tearing_enabled && !tearing_supported)
        return PLATFORM_WSI_UNSUPPORTED;
    swapchain->state = PLATFORM_WSI_SWAPCHAIN_READY;
    swapchain->generation = 1u;
    swapchain->buffer_count = buffer_count;
    swapchain->logical_width = logical_width;
    swapchain->logical_height = logical_height;
    swapchain->drawable_width = drawable_width;
    swapchain->drawable_height = drawable_height;
    swapchain->current_buffer.generation = swapchain->generation;
    swapchain->current_buffer.retired = false;
    return PLATFORM_WSI_OK;
}

PLATFORM_WSI_INLINE PlatformWsiResult platform_wsi_swapchain_begin_frame(
    PlatformWsiSwapchain *swapchain, PlatformWsiBackBuffer *out_buffer)
{
    if (swapchain == NULL || out_buffer == NULL)
        return PLATFORM_WSI_INVALID_ARGUMENT;
    if (swapchain->state != PLATFORM_WSI_SWAPCHAIN_READY)
        return PLATFORM_WSI_INVALID_TRANSITION;
    if (swapchain->current_buffer.retired ||
        swapchain->current_buffer.generation != swapchain->generation)
        return PLATFORM_WSI_INVALID_TRANSITION;
    swapchain->state = PLATFORM_WSI_SWAPCHAIN_RENDERING;
    *out_buffer = swapchain->current_buffer;
    return PLATFORM_WSI_OK;
}

PLATFORM_WSI_INLINE PlatformWsiResult platform_wsi_swapchain_present(
    PlatformWsiSwapchain *swapchain, const PlatformWsiBackBuffer *buffer)
{
    if (swapchain == NULL || buffer == NULL)
        return PLATFORM_WSI_INVALID_ARGUMENT;
    if (swapchain->state != PLATFORM_WSI_SWAPCHAIN_RENDERING)
        return PLATFORM_WSI_INVALID_TRANSITION;
    if (buffer->retired || buffer->generation != swapchain->generation ||
        buffer->index != swapchain->current_buffer.index)
        return PLATFORM_WSI_INVALID_ARGUMENT;
    swapchain->state = PLATFORM_WSI_SWAPCHAIN_PRESENT;
    return PLATFORM_WSI_OK;
}

PLATFORM_WSI_INLINE PlatformWsiResult platform_wsi_swapchain_ready(
    PlatformWsiSwapchain *swapchain)
{
    if (swapchain == NULL) return PLATFORM_WSI_INVALID_ARGUMENT;
    if (swapchain->state != PLATFORM_WSI_SWAPCHAIN_PRESENT)
        return PLATFORM_WSI_INVALID_TRANSITION;
    swapchain->state = PLATFORM_WSI_SWAPCHAIN_READY;
    return PLATFORM_WSI_OK;
}

PLATFORM_WSI_INLINE PlatformWsiResult platform_wsi_swapchain_resize(
    PlatformWsiSwapchain *swapchain, u32 logical_width, u32 logical_height,
    u32 drawable_width, u32 drawable_height)
{
    if (swapchain == NULL) return PLATFORM_WSI_INVALID_ARGUMENT;
    if (swapchain->state != PLATFORM_WSI_SWAPCHAIN_READY)
        return PLATFORM_WSI_INVALID_TRANSITION;
    if (!platform_wsi_sizes_valid(logical_width, logical_height, drawable_width,
                                  drawable_height))
        return PLATFORM_WSI_INVALID_ARGUMENT;
    swapchain->current_buffer.retired = true;
    swapchain->state = PLATFORM_WSI_SWAPCHAIN_RETIRED;
    swapchain->logical_width = logical_width;
    swapchain->logical_height = logical_height;
    swapchain->drawable_width = drawable_width;
    swapchain->drawable_height = drawable_height;
    swapchain->generation++;
    swapchain->current_buffer.generation = swapchain->generation;
    swapchain->current_buffer.index = 0u;
    swapchain->current_buffer.retired = false;
    swapchain->state = PLATFORM_WSI_SWAPCHAIN_READY;
    return PLATFORM_WSI_OK;
}

PLATFORM_WSI_INLINE PlatformWsiResult platform_wsi_surface_init(
    PlatformWsiSurface *surface, bool available, u32 logical_width,
    u32 logical_height, u32 drawable_width, u32 drawable_height)
{
    if (surface == NULL) return PLATFORM_WSI_INVALID_ARGUMENT;
    surface->backend = PLATFORM_WSI_COMPILE_BACKEND;
    surface->logical_width = 0u;
    surface->logical_height = 0u;
    surface->drawable_width = 0u;
    surface->drawable_height = 0u;
    if (!available) {
        surface->state = PLATFORM_WSI_UNAVAILABLE;
        return PLATFORM_WSI_UNAVAILABLE_RESULT;
    }
    if (!platform_wsi_sizes_valid(logical_width, logical_height, drawable_width,
                                  drawable_height)) {
        surface->state = PLATFORM_WSI_UNAVAILABLE;
        return PLATFORM_WSI_INVALID_ARGUMENT;
    }
    surface->state = PLATFORM_WSI_CREATED;
    surface->logical_width = logical_width;
    surface->logical_height = logical_height;
    surface->drawable_width = drawable_width;
    surface->drawable_height = drawable_height;
    return PLATFORM_WSI_OK;
}

PLATFORM_WSI_INLINE PlatformWsiResult platform_wsi_surface_resize(
    PlatformWsiSurface *surface, u32 logical_width, u32 logical_height,
    u32 drawable_width, u32 drawable_height)
{
    if (surface == NULL) return PLATFORM_WSI_INVALID_ARGUMENT;
    if (surface->state == PLATFORM_WSI_UNAVAILABLE)
        return PLATFORM_WSI_UNAVAILABLE_RESULT;
    if (surface->state != PLATFORM_WSI_CREATED &&
        surface->state != PLATFORM_WSI_RESIZED)
        return PLATFORM_WSI_INVALID_TRANSITION;
    if (!platform_wsi_sizes_valid(logical_width, logical_height, drawable_width,
                                  drawable_height))
        return PLATFORM_WSI_INVALID_ARGUMENT;
    surface->state = PLATFORM_WSI_RESIZED;
    surface->logical_width = logical_width;
    surface->logical_height = logical_height;
    surface->drawable_width = drawable_width;
    surface->drawable_height = drawable_height;
    return PLATFORM_WSI_OK;
}

PLATFORM_WSI_INLINE PlatformWsiResult platform_wsi_surface_suspend(
    PlatformWsiSurface *surface)
{
    if (surface == NULL) return PLATFORM_WSI_INVALID_ARGUMENT;
    if (surface->state == PLATFORM_WSI_UNAVAILABLE)
        return PLATFORM_WSI_UNAVAILABLE_RESULT;
    if (surface->state != PLATFORM_WSI_CREATED &&
        surface->state != PLATFORM_WSI_RESIZED)
        return PLATFORM_WSI_INVALID_TRANSITION;
    surface->state = PLATFORM_WSI_SUSPENDED;
    return PLATFORM_WSI_OK;
}

PLATFORM_WSI_INLINE PlatformWsiResult platform_wsi_surface_resume(
    PlatformWsiSurface *surface)
{
    if (surface == NULL) return PLATFORM_WSI_INVALID_ARGUMENT;
    if (surface->state == PLATFORM_WSI_UNAVAILABLE)
        return PLATFORM_WSI_UNAVAILABLE_RESULT;
    if (surface->state != PLATFORM_WSI_SUSPENDED)
        return PLATFORM_WSI_INVALID_TRANSITION;
    surface->state = PLATFORM_WSI_CREATED;
    return PLATFORM_WSI_OK;
}

PLATFORM_WSI_INLINE PlatformWsiResult platform_wsi_surface_lose(
    PlatformWsiSurface *surface)
{
    if (surface == NULL) return PLATFORM_WSI_INVALID_ARGUMENT;
    if (surface->state == PLATFORM_WSI_UNAVAILABLE)
        return PLATFORM_WSI_UNAVAILABLE_RESULT;
    if (surface->state != PLATFORM_WSI_CREATED &&
        surface->state != PLATFORM_WSI_RESIZED)
        return PLATFORM_WSI_INVALID_TRANSITION;
    surface->state = PLATFORM_WSI_LOST;
    return PLATFORM_WSI_OK;
}

PLATFORM_WSI_INLINE PlatformWsiResult platform_wsi_surface_destroy(
    PlatformWsiSurface *surface)
{
    if (surface == NULL) return PLATFORM_WSI_INVALID_ARGUMENT;
    if (surface->state == PLATFORM_WSI_DESTROYING)
        return PLATFORM_WSI_INVALID_TRANSITION;
    surface->state = PLATFORM_WSI_DESTROYING;
    return PLATFORM_WSI_OK;
}

/* 帧是否允许进入 RHI：仅 CREATED/RESIZED。SUSPENDED/LOST/DESTROYING/UNAVAILABLE
 * 一律拒绝——应用层据此跳过渲染，而不是让后端在死 surface 上空转。 */
PLATFORM_WSI_INLINE bool platform_wsi_frame_allowed(const PlatformWsiSurface *surface)
{
    return surface != NULL &&
           (surface->state == PLATFORM_WSI_CREATED ||
            surface->state == PLATFORM_WSI_RESIZED);
}

/* RHI 销毁门控：进入 DESTROYING 后拒绝销毁。销毁顺序契约：
 * rhi_device_destroy_ex 必须先于 platform_destroy（后者把状态推入
 * DESTROYING）。 */
PLATFORM_WSI_INLINE bool platform_wsi_rhi_teardown_allowed(const PlatformWsiSurface *surface)
{
    return surface != NULL && surface->state != PLATFORM_WSI_DESTROYING;
}

#undef PLATFORM_WSI_INLINE
