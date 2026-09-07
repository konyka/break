/**
 * @file my_vgcanvas_vulkan.h
 * @brief Vulkan vgcanvas backend (M25b): shared CPU triangulation
 * (my_vggeometry) + swapchain/offscreen rendering.
 *
 * Windowed path (my_window_enable_gpu): the window asks the PAL port for
 * a VkSurfaceKHR (my_pal_window_vk_create_surface, void*-typed) and
 * hands it to my_vgcanvas_vulkan_create(); frames are presented via
 * my_vgcanvas_vulkan_present() (the window mounts it as its GL-adapter
 * swap_buffers). Offscreen path (tests): no surface, renders into a
 * private image, my_vgcanvas_vulkan_readback() copies it to host memory.
 *
 * Built only with MYUI_HAS_VULKAN; otherwise every entry point returns
 * NULL/MY_RET_NOT_SUPPORTED.
 * The backend reports the device-supported 1x/2x/4x sample levels. Target,
 * render-pass, pipeline, and swapchain changes are committed as one
 * candidate-resource transaction; a failed rebuild leaves the active target
 * and reported quality unchanged.
 */
#ifndef MY_VGCANVAS_VULKAN_H
#define MY_VGCANVAS_VULKAN_H

#include "myc/my_mem.h"
#include "myr/my_vgcanvas.h"

#ifndef MYUI_VULKAN_MAX_INSTANCE_EXTENSIONS
#define MYUI_VULKAN_MAX_INSTANCE_EXTENSIONS 8u
#endif
#ifndef MYUI_VULKAN_MAX_EXTENSION_NAME
#define MYUI_VULKAN_MAX_EXTENSION_NAME 256u
#endif

/**
 * @brief Peek at an already initialized shared VkInstance (as void*).
 * Returns NULL without initializing resources. Use the acquire API when
 * initialization and a temporary lifetime lease are required.
 */
void* my_vgcanvas_vulkan_instance(void);

/** @brief Acquire the shared instance for PAL surface creation. */
void* my_vgcanvas_vulkan_instance_acquire(void);

/** @brief Acquire the shared instance with a PAL-provided WSI extension set. */
void* my_vgcanvas_vulkan_instance_acquire_with_extensions(
    const char* const* extensions, uint32_t extension_count);

/** @brief Release a temporary instance-acquire lease. */
void my_vgcanvas_vulkan_instance_release(void);

/**
 * @brief Create the windowed backend on a PAL-created VkSurfaceKHR
 * (as void*; takes ownership — destroyed with the canvas or via
 * my_vgcanvas_vulkan_destroy_surface on failure). NULL on failure.
 */
my_vgcanvas_t* my_vgcanvas_vulkan_create(const my_allocator_t* allocator,
                                         void* vk_surface, int32_t width,
                                         int32_t height);

/** @brief Destroy a surface NOT consumed by a successful create. */
void my_vgcanvas_vulkan_destroy_surface(void* vk_surface);

/** @brief Create the surface-less offscreen backend (tests, M25b). */
my_vgcanvas_t* my_vgcanvas_vulkan_create_offscreen(
    const my_allocator_t* allocator, int32_t width, int32_t height);

/** @brief Notify a physical drawable resize (swapchain is rebuilt lazily).
 * The caller converts logical window dimensions before calling. */
my_ret_t my_vgcanvas_vulkan_resize(my_vgcanvas_t* vg, int32_t width,
                                   int32_t height);

/** @brief Submit the recorded frame and present it (windowed; the
 * GL-adapter swap_buffers equivalent). */
my_ret_t my_vgcanvas_vulkan_present(my_vgcanvas_t* vg);

/**
 * @brief Copy the current offscreen image into rgba (width*height*4
 * bytes, top-left origin, R/G/B/A order). Offscreen canvases only.
 */
my_ret_t my_vgcanvas_vulkan_readback(my_vgcanvas_t* vg, uint8_t* rgba,
                                     int32_t width, int32_t height);

#endif /* MY_VGCANVAS_VULKAN_H */
