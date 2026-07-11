#ifdef ENGINE_PLATFORM_WINDOWS
    #define VK_USE_PLATFORM_WIN32_KHR
    #include <windows.h>
#elif defined(ENGINE_PLATFORM_MACOS)
    #define VK_USE_PLATFORM_METAL_EXT
#elif defined(ENGINE_PLATFORM_WAYLAND)
    #define VK_USE_PLATFORM_WAYLAND_KHR
    #include <wayland-client.h>
#else
    #define VK_USE_PLATFORM_XLIB_KHR
#endif
#include <vulkan/vulkan.h>
#if !defined(ENGINE_PLATFORM_WINDOWS) && !defined(ENGINE_PLATFORM_WAYLAND) && !defined(ENGINE_PLATFORM_MACOS)
#include <X11/Xlib.h>
#endif
#include <shaderc/shaderc.h>
#include <core/log.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define VK_MAX_FRAMES 2
#define VK_MAX_UNIFORMS 64

/* ---- Internal types ---- */

typedef struct {
    VkShaderModule module;
    /* Owned copy of the compiled SPIR-V, so a pipeline can recreate its shader
     * modules when it needs a render-pass-format variant (the original shader
     * handle is usually destroyed right after pipeline creation). */
    u32   *spirv;
    usize  spirv_size;  /* bytes */
} VKShaderData;

#define VK_INVALID_SET 0xFFu
#define VK_MAX_MIP_VIEWS 16u

typedef struct {
    VkPipelineLayout layout;
    VkPipeline        pipeline;
    u32               vertex_stride;
    bool              no_vertex_input;
    u32               push_range_count;
    VkPushConstantRange push_ranges[8];
    u32               uniform_offsets[VK_MAX_UNIFORMS];
    u32               uniform_sizes[VK_MAX_UNIFORMS];
    u32               uniform_count;
    bool              uses_texel_buffer;
    bool              is_instanced;
    bool              is_compute;
    bool              uses_storage;
    bool              terrain_layout;
    bool              water_layout;
    bool              combined_aa_layout;
    bool              combined_color_layout;
    /* Set indices for the auxiliary descriptor sets that the
     * generic command-stream binding helpers (image_texture,
     * texture_mip, uniform_buffer) target.  VK_INVALID_SET means
     * the pipeline layout does not declare that auxiliary set. */
    u8                storage_image_set;
    u8                sampler_mip_set;
    u8                ubo_set;
    /* Render-pass-format variant support (graphics only). A pipeline must be
     * render-pass-compatible with whatever FBO it is drawn into; since the same
     * logical pipeline (e.g. a post-fx blit) can be bound across targets of
     * different color formats, we lazily build per-format variants at bind time.
     * base_color_fmt is the format the base `pipeline` was created for;
     * VK_FORMAT_UNDEFINED marks depth-only/compute/MRT pipelines that are never
     * variant-ed. The SPIR-V copies + desc snapshot let us rebuild variants. */
    VkFormat          base_color_fmt;
    VkFormat          variant_fmt[8];
    VkPipeline        variant_pipe[8];
    u32               variant_count;
    u32              *vs_spirv;  usize vs_spirv_size;
    u32              *fs_spirv;  usize fs_spirv_size;
    RHIPipelineDesc   build_desc;
} VKPipelineData;

typedef struct {
    VkBuffer       buffer;
    VkDeviceMemory memory;
    VkBufferView   texel_view;
    usize          size;
    bool           is_texel;
    u8            *mapped;
    bool           device_local; /* R181: no persistent map; updates via staging */
} VKBufferData;

typedef struct {
    VkImage        image;
    VkImageView    view;
    VkDeviceMemory memory;
    u32            width;
    u32            height;
    VkFormat       format;
    u32            mip_levels;
    /* Lazily created per-mip image views.  Slot m is created the
     * first time mip level m is bound through rhi_cmd_bind_image_texture
     * or rhi_cmd_bind_texture_mip.  Both the storage-image and the
     * combined-image-sampler descriptor types use the same
     * single-mip view, since the underlying VkImage was created with
     * both SAMPLED and STORAGE usage bits when applicable. */
    VkImageView    mip_views[VK_MAX_MIP_VIEWS];
    /* R172: Per-mip layout tracking for Hi-Z ping-pong (UNDEFINED=0 unknown). */
    VkImageLayout  mip_layout[VK_MAX_MIP_VIEWS];
    /* Tracked layout for depth targets that ping-pong between being a depth
     * attachment and a sampled texture (scene depth read by post-fx).  0 ==
     * VK_IMAGE_LAYOUT_UNDEFINED means "unknown / not yet tracked". */
    VkImageLayout  cur_layout;
} VKTextureData;

/* Forward declaration — full definition in the Cubemap section below. */
struct VKCubemapData {
    VkImage        image;
    VkDeviceMemory memory;
    VkImageView    view;
    VkFormat       format;
    u32            mip_levels;
    /* Lazily created per-face, per-mip storage views for compute write. */
    VkImageView    face_views[6][VK_MAX_MIP_VIEWS];
};
typedef struct VKCubemapData VKCubemapData;

typedef struct {
    VkSampler sampler;
} VKSamplerData;

typedef struct {
    VkFramebuffer fbo;
} VKFramebufferData;

typedef struct {
    VkDeviceMemory memory;
    VkBuffer       buffer;
} VKUniformRing;

typedef struct {
    VkInstance       instance;
    VkPhysicalDevice         physical;
    VkPhysicalDeviceProperties device_props;
    bool             feat_fill_mode_non_solid; /* wireframe (polygonMode=LINE) usable */
    bool             feat_draw_indirect_count;  /* vkCmdDraw*IndirectCount usable */
    bool             feat_partially_bound;      /* descriptorBindingPartiallyBound usable */
    VkDevice                 device;
    VkQueue          graphics_queue;
    VkQueue          present_queue;
    u32              graphics_family;
    u32              present_family;

    VkSurfaceKHR            surface;
    VkSwapchainKHR          swapchain;
    VkFormat                swap_format;
    VkExtent2D              swap_extent;
    VkImage                *swap_images;
    VkImageView            *swap_views;
    VkFramebuffer          *framebuffers;
    u32                     swap_count;

    VkRenderPass  render_pass;
    VkImage       depth_image;
    VkDeviceMemory depth_memory;
    VkImageView   depth_view;

    VkCommandPool   cmd_pool;
    VkCommandBuffer cmd_buffers[VK_MAX_FRAMES];

    VkSemaphore image_semaphores[VK_MAX_FRAMES];
    VkSemaphore *render_semaphores;
    VkFence     fences[VK_MAX_FRAMES];
    u32         current_frame;
    u32         image_index;
    bool        frame_started;

    VKUniformRing uniform_ring[VK_MAX_FRAMES];
    u8           *uniform_mapped[VK_MAX_FRAMES];
    usize         uniform_ring_size;
    usize         uniform_offset[VK_MAX_FRAMES];

    VkDescriptorPool        desc_pools[VK_MAX_FRAMES];
    VkDescriptorSetLayout    desc_layout;
    VkDescriptorSetLayout    texel_layout;
    VkDescriptorSetLayout    storage_layout;
    VkDescriptorSetLayout    storage_vtx_layout;
    /* Auxiliary layouts wired into compute / graphics pipeline
     * layouts to satisfy the generic command-buffer binding API. */
    VkDescriptorSetLayout    storage_image_layout;
    VkDescriptorSetLayout    sampler_mip_layout;
    VkDescriptorSetLayout    ubo_layout;

#ifdef ENGINE_PLATFORM_WINDOWS
    HINSTANCE hinstance;
    HWND      hwnd;
#elif defined(ENGINE_PLATFORM_MACOS)
    void *metal_layer;   /* CAMetalLayer* from the Cocoa window */
#elif defined(ENGINE_PLATFORM_WAYLAND)
    struct wl_display *wl_display;
    struct wl_surface *wl_surface;
#else
    Display *display;
    Window   window;
#endif

    VkPipeline current_pipeline;
    VKPipelineData *current_pipeline_data;
    /* Storage-buffer binds accumulate into ONE descriptor set per pipeline bind:
     * a compute shader (e.g. compact_draws.comp) reads bindings 0..3 from the
     * same set 0, so each rhi_cmd_bind_storage_buffer must write into the shared
     * set rather than allocate+bind a fresh single-binding set (which clobbers
     * the previously bound one, leaving bindings 0..2 unwritten -> 08114). */
    VkDescriptorSet storage_set;
    bool            storage_set_valid;
    bool       depth_lequal;
    bool       render_pass_active;
    /* Render-pass suspend/resume: Vulkan forbids vkCmdDispatch/barriers inside
     * a render pass, but the GPU-driven cull/compaction compute is issued
     * mid-frame. rhi_cmd_dispatch suspends the active pass (ends it, attachments
     * are STOREd); the next draw/clear resumes it via a LOAD-op twin so prior
     * pass contents survive. The resume_* fields capture the pass to restore. */
    bool          pass_suspended;
    VkRenderPass  resume_render_pass;   /* LOAD-op twin of the active pass */
    VkFramebuffer resume_framebuffer;
    VkExtent2D    resume_extent;
    /* Color format of the currently-bound render pass, so rhi_cmd_bind_pipeline
     * can pick (or build) a render-pass-compatible pipeline variant.
     * VK_FORMAT_UNDEFINED means "do not variant" (depth-only/MRT passes). */
    VkFormat      active_color_fmt;
    /* R94-2: viewport/scissor cache -- skip redundant vkCmdSetViewport/Scissor */
    f32           cached_vp_x, cached_vp_y, cached_vp_w, cached_vp_h;
    i32           cached_sc_x, cached_sc_y;
    u32           cached_sc_w, cached_sc_h;
    bool          vp_valid, sc_valid;
    /* R94-3: push constant staging -- batch vkCmdPushConstants into one call */
    u8            push_staging[256];
    u32           push_dirty_min;
    u32           push_dirty_max;
    bool          push_dirty;
    VkRenderPass shadow_render_pass;
    VkRenderPass render_pass_load;      /* LOAD-op twin of the swapchain pass */
    VkImageView shadow_tex_view;
    /* Template render passes for pipeline creation, keyed by color VkFormat, so
     * a pipeline is render-pass-compatible with the offscreen FBO it draws into
     * (matching color format + D32 depth + identical subpass layout). The
     * swapchain pass is used for the default (swapchain) target. */
    VkFormat     pipe_rp_formats[8];
    VkRenderPass pipe_rp_cache[8];
    u32          pipe_rp_count;

    shaderc_compiler_t shaderc_compiler;
    bool vsync;
} VKBackend;

/* ---- Helpers ---- */

/* R175: One in-flight mip upload — reclaim on next upload / device shutdown
 * so async_loader_tick does not stall the main thread on every level. */
typedef struct {
    VkFence         fence;
    VkBuffer        staging;
    VkDeviceMemory  staging_mem;
    VkCommandBuffer cb;
    VkCommandPool   pool;
    bool            pending;
} VKMipUploadPending;
static VKMipUploadPending g_mip_upload_pending;

static void vk_mip_upload_reclaim(VKBackend *vk) {
    if (!g_mip_upload_pending.pending || !vk) return;
    if (g_mip_upload_pending.fence) {
        if (vkWaitForFences(vk->device, 1, &g_mip_upload_pending.fence, VK_TRUE, UINT64_MAX) != VK_SUCCESS)
            LOG_WARN("VK: vkWaitForFences failed reclaiming mip upload");
        vkDestroyFence(vk->device, g_mip_upload_pending.fence, NULL);
    }
    if (g_mip_upload_pending.cb)
        vkFreeCommandBuffers(vk->device, g_mip_upload_pending.pool, 1, &g_mip_upload_pending.cb);
    if (g_mip_upload_pending.staging)
        vkDestroyBuffer(vk->device, g_mip_upload_pending.staging, NULL);
    if (g_mip_upload_pending.staging_mem)
        vkFreeMemory(vk->device, g_mip_upload_pending.staging_mem, NULL);
    memset(&g_mip_upload_pending, 0, sizeof(g_mip_upload_pending));
}

static VKBackend *vk_backend(RHIDevice *dev) {
    return (VKBackend *)dev->backend_data;
}

static void vk_wait_frames(VKBackend *vk) {
    if (vkWaitForFences(vk->device, VK_MAX_FRAMES, vk->fences, VK_TRUE, UINT64_MAX) != VK_SUCCESS)
        LOG_WARN("VK: vkWaitForFences failed in wait_frames");
}

static u32 vk_find_memory(VKBackend *vk, u32 type_filter, VkMemoryPropertyFlags props) {
    VkPhysicalDeviceMemoryProperties mem_props;
    vkGetPhysicalDeviceMemoryProperties(vk->physical, &mem_props);
    for (u32 i = 0; i < mem_props.memoryTypeCount; i++) {
        if ((type_filter & (1u << i)) && (mem_props.memoryTypes[i].propertyFlags & props) == props)
            return i;
    }
    return UINT32_MAX;
}

/* Build a LOAD-op "resume" twin of a CLEAR render pass: same subpasses and
 * dependencies, but every attachment loads its existing contents and starts in
 * the layout it ended the suspended pass in (its finalLayout). Used to resume a
 * render pass that rhi_cmd_dispatch suspended so compute could run. The source
 * render pass MUST keep storeOp=STORE on any attachment that must survive. */
static VkRenderPass vk_make_resume_render_pass(VKBackend *vk,
                                               const VkRenderPassCreateInfo *clear_ci) {
    VkAttachmentDescription atts[RHI_MRT_MAX_ATTACHMENTS + 2];
    u32 n = clear_ci->attachmentCount;
    if (n > RHI_MRT_MAX_ATTACHMENTS + 2) return VK_NULL_HANDLE;
    for (u32 i = 0; i < n; i++) {
        atts[i] = clear_ci->pAttachments[i];
        atts[i].loadOp = VK_ATTACHMENT_LOAD_OP_LOAD;
        atts[i].initialLayout = atts[i].finalLayout;
    }
    VkRenderPassCreateInfo ci = *clear_ci;
    ci.pAttachments = atts;
    VkRenderPass rp = VK_NULL_HANDLE;
    if (vkCreateRenderPass(vk->device, &ci, NULL, &rp) != VK_SUCCESS)
        LOG_WARN("VK: vkCreateRenderPass failed in make_resume_render_pass");
    return rp;
}

/* Record the currently-active render pass so a later dispatch can suspend and
 * the next draw can resume it. Call right after vkCmdBeginRenderPass. */
static void vk_record_pass(VKBackend *vk, VkRenderPass resume_rp,
                           VkFramebuffer fb, u32 w, u32 h, VkFormat color_fmt) {
    vk->resume_render_pass = resume_rp;
    vk->resume_framebuffer = fb;
    vk->resume_extent.width = w;
    vk->resume_extent.height = h;
    vk->pass_suspended = false;
    vk->active_color_fmt = color_fmt;
}

/* Resume a render pass previously suspended by rhi_cmd_dispatch. No clears: the
 * LOAD-op twin preserves attachment contents. Dynamic viewport/scissor set
 * before the suspend persist across the boundary, so they are not re-set. */
static void vk_resume_pass_if_needed(VKBackend *vk) {
    if (!vk->pass_suspended) return;
    vk->pass_suspended = false;
    if (vk->resume_render_pass == VK_NULL_HANDLE) return;
    VkRenderPassBeginInfo rpi = {0};
    rpi.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
    rpi.renderPass = vk->resume_render_pass;
    rpi.framebuffer = vk->resume_framebuffer;
    rpi.renderArea.extent = vk->resume_extent;
    rpi.clearValueCount = 0;
    rpi.pClearValues = NULL;
    vkCmdBeginRenderPass(vk->cmd_buffers[vk->current_frame], &rpi, VK_SUBPASS_CONTENTS_INLINE);
    vk->render_pass_active = true;
}

/* Suspend the active render pass so a compute dispatch / image-layout barrier
 * (forbidden inside a render pass) can run. The next draw/clear resumes it via
 * vk_resume_pass_if_needed. No-op when no pass is active. */
static void vk_suspend_pass_for_compute(VKBackend *vk) {
    if (vk->render_pass_active) {
        vkCmdEndRenderPass(vk->cmd_buffers[vk->current_frame]);
        vk->render_pass_active = false;
        vk->pass_suspended = true;
    }
}

/* One-time-submit transition of a freshly created color image (all mips/layers)
 * from UNDEFINED to the given layout. Offscreen/MRT targets may be sampled by a
 * composite/post pass before their producing pass has ever rendered into them
 * (e.g. when an optional effect is disabled or its shader failed to build);
 * giving them a defined sampling layout up front avoids
 * VUID-vkCmdDraw-None-09600 (sampling an UNDEFINED image). */
static void vk_init_image_layout(VKBackend *vk, VkImage image, VkImageLayout layout) {
    if (image == VK_NULL_HANDLE) return;
    VkCommandBufferAllocateInfo cbai = {0};
    cbai.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    cbai.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
    cbai.commandPool = vk->cmd_pool;
    cbai.commandBufferCount = 1;
    VkCommandBuffer cb;
    if (vkAllocateCommandBuffers(vk->device, &cbai, &cb) != VK_SUCCESS) return;
    VkCommandBufferBeginInfo bi = {0};
    bi.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
    bi.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;
    if (vkBeginCommandBuffer(cb, &bi) != VK_SUCCESS) {
        LOG_FATAL("VK: failed to begin command buffer");
        vkFreeCommandBuffers(vk->device, vk->cmd_pool, 1, &cb);
        return;
    }

    VkImageMemoryBarrier b = {0};
    b.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
    b.oldLayout = VK_IMAGE_LAYOUT_UNDEFINED;
    b.newLayout = layout;
    b.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
    b.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
    b.image = image;
    b.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
    b.subresourceRange.levelCount = VK_REMAINING_MIP_LEVELS;
    b.subresourceRange.layerCount = VK_REMAINING_ARRAY_LAYERS;
    b.srcAccessMask = 0;
    b.dstAccessMask = VK_ACCESS_SHADER_READ_BIT;
    vkCmdPipelineBarrier(cb, VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT,
        VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT, 0, 0, NULL, 0, NULL, 1, &b);

    if (vkEndCommandBuffer(cb) != VK_SUCCESS) {
        LOG_FATAL("VK: failed to end command buffer");
        vkFreeCommandBuffers(vk->device, vk->cmd_pool, 1, &cb);
        return;
    }
    VkSubmitInfo si = {0};
    si.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
    si.commandBufferCount = 1;
    si.pCommandBuffers = &cb;
    if (vkQueueSubmit(vk->graphics_queue, 1, &si, VK_NULL_HANDLE) != VK_SUCCESS)
        LOG_FATAL("VK: vkQueueSubmit failed in init_image_layout");
    if (vkQueueWaitIdle(vk->graphics_queue) != VK_SUCCESS)
        LOG_FATAL("VK: vkQueueWaitIdle failed in init_image_layout");
    vkFreeCommandBuffers(vk->device, vk->cmd_pool, 1, &cb);
}


static VkShaderModule vk_compile_glsl(VKBackend *vk, const char *source, usize len, bool is_fragment,
                                      u32 **out_spirv, usize *out_spirv_size) {
    if (out_spirv) *out_spirv = NULL;
    if (out_spirv_size) *out_spirv_size = 0;

    shaderc_compile_options_t opts = shaderc_compile_options_initialize();
    shaderc_compile_options_set_target_env(opts, shaderc_target_env_vulkan, shaderc_env_version_vulkan_1_2);
    shaderc_compile_options_set_target_spirv(opts, shaderc_spirv_version_1_5);

    shaderc_shader_kind kind = is_fragment ? shaderc_fragment_shader : shaderc_vertex_shader;
    shaderc_compilation_result_t result = shaderc_compile_into_spv(
        vk->shaderc_compiler, source, len, kind, "shader.glsl", "main", opts);

    shaderc_compilation_status status = shaderc_result_get_compilation_status(result);
    if (status != shaderc_compilation_status_success) {
        LOG_FATAL("Vulkan shader compile error: %s", shaderc_result_get_error_message(result));
        shaderc_result_release(result);
        shaderc_compile_options_release(opts);
        return VK_NULL_HANDLE;
    }

    usize spv_size = shaderc_result_get_length(result);
    const u32 *spv_data = (const u32 *)shaderc_result_get_bytes(result);

    VkShaderModuleCreateInfo ci = {0};
    ci.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
    ci.codeSize = spv_size;
    ci.pCode = spv_data;

    VkShaderModule module;
    VkResult res = vkCreateShaderModule(vk->device, &ci, NULL, &module);

    /* Hand back an owned SPIR-V copy for later pipeline-variant rebuilds. */
    if (res == VK_SUCCESS && out_spirv && spv_size > 0) {
        u32 *copy = malloc(spv_size);
        if (copy) {
            memcpy(copy, spv_data, spv_size);
            *out_spirv = copy;
            if (out_spirv_size) *out_spirv_size = spv_size;
        }
    }

    shaderc_result_release(result);
    shaderc_compile_options_release(opts);

    if (res != VK_SUCCESS) {
        LOG_FATAL("Failed to create shader module");
        return VK_NULL_HANDLE;
    }
    return module;
}

/* ---- Swapchain ---- */

static void vk_create_swapchain(VKBackend *vk, u32 w, u32 h) {
    VkSurfaceCapabilitiesKHR caps;
    vkGetPhysicalDeviceSurfaceCapabilitiesKHR(vk->physical, vk->surface, &caps);

    VkExtent2D extent;
    if (caps.currentExtent.width != UINT32_MAX) {
        extent = caps.currentExtent;
    } else {
        extent.width = w < caps.minImageExtent.width ? caps.minImageExtent.width : (w > caps.maxImageExtent.width ? caps.maxImageExtent.width : w);
        extent.height = h < caps.minImageExtent.height ? caps.minImageExtent.height : (h > caps.maxImageExtent.height ? caps.maxImageExtent.height : h);
    }
    vk->swap_extent = extent;

    u32 img_count = caps.minImageCount + 1;
    if (caps.maxImageCount > 0 && img_count > caps.maxImageCount) img_count = caps.maxImageCount;

    VkSwapchainCreateInfoKHR sci = {0};
    sci.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
    sci.surface = vk->surface;
    sci.minImageCount = img_count;
    sci.imageFormat = vk->swap_format;
    sci.imageColorSpace = VK_COLOR_SPACE_SRGB_NONLINEAR_KHR;
    sci.imageExtent = extent;
    sci.imageArrayLayers = 1;
    sci.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
    sci.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
    sci.preTransform = caps.currentTransform;
    sci.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
    VkPresentModeKHR present_mode = VK_PRESENT_MODE_FIFO_KHR;
    {
        u32 mode_count = 0;
        vkGetPhysicalDeviceSurfacePresentModesKHR(vk->physical, vk->surface, &mode_count, NULL);
        VkPresentModeKHR *modes = calloc(mode_count, sizeof(VkPresentModeKHR));
        if (!modes) { LOG_FATAL("VK: OOM present modes"); return; }
        vkGetPhysicalDeviceSurfacePresentModesKHR(vk->physical, vk->surface, &mode_count, modes);
        if (!vk->vsync) {
            for (u32 i = 0; i < mode_count; i++) {
                if (modes[i] == VK_PRESENT_MODE_IMMEDIATE_KHR) {
                    present_mode = VK_PRESENT_MODE_IMMEDIATE_KHR;
                    break;
                }
            }
        }
        free(modes);
    }
    sci.presentMode = present_mode;
    sci.clipped = VK_TRUE;
    sci.oldSwapchain = VK_NULL_HANDLE;

    VkResult res = vkCreateSwapchainKHR(vk->device, &sci, NULL, &vk->swapchain);
    if (res != VK_SUCCESS) {
        LOG_FATAL("Failed to create swapchain: %d", res);
        return;
    }

    if (vkGetSwapchainImagesKHR(vk->device, vk->swapchain, &vk->swap_count, NULL) != VK_SUCCESS) {
        LOG_FATAL("VK: vkGetSwapchainImagesKHR count query failed");
        return;
    }
    vk->swap_images = calloc(vk->swap_count, sizeof(VkImage));
    if (!vk->swap_images) { LOG_FATAL("VK: OOM swap images"); return; }
    vk->swap_views = calloc(vk->swap_count, sizeof(VkImageView));
    if (!vk->swap_views) { LOG_FATAL("VK: OOM swap views"); return; }
    if (vkGetSwapchainImagesKHR(vk->device, vk->swapchain, &vk->swap_count, vk->swap_images) != VK_SUCCESS) {
        LOG_FATAL("VK: vkGetSwapchainImagesKHR image query failed");
        free(vk->swap_images);
        return;
    }

    for (u32 i = 0; i < vk->swap_count; i++) {
        VkImageViewCreateInfo vci = {0};
        vci.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
        vci.image = vk->swap_images[i];
        vci.viewType = VK_IMAGE_VIEW_TYPE_2D;
        vci.format = vk->swap_format;
        vci.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
        vci.subresourceRange.levelCount = 1;
        vci.subresourceRange.layerCount = 1;
        if (vkCreateImageView(vk->device, &vci, NULL, &vk->swap_views[i]) != VK_SUCCESS) {
            LOG_FATAL("VK: failed to create swapchain image view %u", i);
            return;
        }
    }

    vk->render_semaphores = calloc(vk->swap_count, sizeof(VkSemaphore));
    if (!vk->render_semaphores) { LOG_FATAL("VK: OOM render semaphores"); return; }
    for (u32 i = 0; i < vk->swap_count; i++) {
        VkSemaphoreCreateInfo sci2 = {0};
        sci2.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;
        if (vkCreateSemaphore(vk->device, &sci2, NULL, &vk->render_semaphores[i]) != VK_SUCCESS) {
            LOG_FATAL("VK: failed to create render semaphore %u", i);
            return;
        }
    }
}

static void vk_create_depth(VKBackend *vk) {
    VkImageCreateInfo ci = {0};
    ci.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
    ci.imageType = VK_IMAGE_TYPE_2D;
    ci.format = VK_FORMAT_D32_SFLOAT;
    ci.extent.width = vk->swap_extent.width;
    ci.extent.height = vk->swap_extent.height;
    ci.extent.depth = 1;
    ci.mipLevels = 1;
    ci.arrayLayers = 1;
    ci.samples = VK_SAMPLE_COUNT_1_BIT;
    ci.tiling = VK_IMAGE_TILING_OPTIMAL;
    ci.usage = VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT;
    ci.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
    ci.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;

    if (vkCreateImage(vk->device, &ci, NULL, &vk->depth_image) != VK_SUCCESS) {
        LOG_FATAL("VK: failed to create depth image");
        return;
    }

    VkMemoryRequirements mem_req;
    vkGetImageMemoryRequirements(vk->device, vk->depth_image, &mem_req);

    VkMemoryAllocateInfo ai = {0};
    ai.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
    ai.allocationSize = mem_req.size;
    ai.memoryTypeIndex = vk_find_memory(vk, mem_req.memoryTypeBits,
                                         VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);
    if (vkAllocateMemory(vk->device, &ai, NULL, &vk->depth_memory) != VK_SUCCESS) {
        LOG_FATAL("VK: failed to allocate depth memory");
        return;
    }
    if (vkBindImageMemory(vk->device, vk->depth_image, vk->depth_memory, 0) != VK_SUCCESS) {
        LOG_FATAL("VK: failed to bind depth image memory");
        return;
    }

    VkImageViewCreateInfo vci = {0};
    vci.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
    vci.image = vk->depth_image;
    vci.viewType = VK_IMAGE_VIEW_TYPE_2D;
    vci.format = VK_FORMAT_D32_SFLOAT;
    vci.subresourceRange.aspectMask = VK_IMAGE_ASPECT_DEPTH_BIT;
    vci.subresourceRange.levelCount = 1;
    vci.subresourceRange.layerCount = 1;
    if (vkCreateImageView(vk->device, &vci, NULL, &vk->depth_view) != VK_SUCCESS) {
        LOG_FATAL("VK: failed to create depth image view");
        return;
    }
}

static void vk_create_framebuffers(VKBackend *vk) {
    /* R149: Guard against NULL swap_views — vk_create_swapchain may have failed
     * (e.g., vkCreateSwapchainKHR error, OOM on swap_images/swap_views), leaving
     * swap_count at a stale non-zero value while swap_views is NULL.
     * Without this check, vk->swap_views[i] dereferences NULL. */
    if (!vk->swap_views || vk->swap_count == 0) return;
    vk->framebuffers = calloc(vk->swap_count, sizeof(VkFramebuffer));
    if (!vk->framebuffers) { LOG_FATAL("VK: OOM framebuffers"); return; }
    for (u32 i = 0; i < vk->swap_count; i++) {
        VkImageView attachments[2] = { vk->swap_views[i], vk->depth_view };
        VkFramebufferCreateInfo ci = {0};
        ci.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
        ci.renderPass = vk->render_pass;
        ci.attachmentCount = 2;
        ci.pAttachments = attachments;
        ci.width = vk->swap_extent.width;
        ci.height = vk->swap_extent.height;
        ci.layers = 1;
        if (vkCreateFramebuffer(vk->device, &ci, NULL, &vk->framebuffers[i]) != VK_SUCCESS) {
            LOG_FATAL("VK: failed to create framebuffer %u", i);
            return;
        }
    }
}

static void vk_create_render_pass(VKBackend *vk) {
    VkAttachmentDescription attachments[2] = {0};

    attachments[0].format = vk->swap_format;
    attachments[0].samples = VK_SAMPLE_COUNT_1_BIT;
    attachments[0].loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
    attachments[0].storeOp = VK_ATTACHMENT_STORE_OP_STORE;
    attachments[0].stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
    attachments[0].stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
    attachments[0].initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
    attachments[0].finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;

    attachments[1].format = VK_FORMAT_D32_SFLOAT;
    attachments[1].samples = VK_SAMPLE_COUNT_1_BIT;
    attachments[1].loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
    /* STORE so depth survives a render-pass suspend (compute dispatch). */
    attachments[1].storeOp = VK_ATTACHMENT_STORE_OP_STORE;
    attachments[1].stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
    attachments[1].stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
    attachments[1].initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
    attachments[1].finalLayout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;

    VkAttachmentReference color_ref = {0, VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL};
    VkAttachmentReference depth_ref = {1, VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL};

    VkSubpassDescription subpass = {0};
    subpass.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
    subpass.colorAttachmentCount = 1;
    subpass.pColorAttachments = &color_ref;
    subpass.pDepthStencilAttachment = &depth_ref;

    VkSubpassDependency dep = {0};
    dep.srcSubpass = VK_SUBPASS_EXTERNAL;
    dep.dstSubpass = 0;
    dep.srcStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
    dep.srcAccessMask = 0;
    dep.dstStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
    dep.dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;

    VkRenderPassCreateInfo ci = {0};
    ci.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
    ci.attachmentCount = 2;
    ci.pAttachments = attachments;
    ci.subpassCount = 1;
    ci.pSubpasses = &subpass;
    ci.dependencyCount = 1;
    ci.pDependencies = &dep;

    if (vkCreateRenderPass(vk->device, &ci, NULL, &vk->render_pass) != VK_SUCCESS) {
        LOG_FATAL("VK: failed to create render pass");
        return;
    }
    if (vk->render_pass_load != VK_NULL_HANDLE) {
        vkDestroyRenderPass(vk->device, vk->render_pass_load, NULL);
    }
    vk->render_pass_load = vk_make_resume_render_pass(vk, &ci);
}

static void vk_cleanup_swapchain(VKBackend *vk) {
    if (vk->framebuffers) {
        for (u32 i = 0; i < vk->swap_count; i++)
            vkDestroyFramebuffer(vk->device, vk->framebuffers[i], NULL);
        free(vk->framebuffers);
        vk->framebuffers = NULL;
    }
    if (vk->depth_view) { vkDestroyImageView(vk->device, vk->depth_view, NULL); vk->depth_view = VK_NULL_HANDLE; }
    if (vk->depth_image) { vkDestroyImage(vk->device, vk->depth_image, NULL); vk->depth_image = VK_NULL_HANDLE; }
    if (vk->depth_memory) { vkFreeMemory(vk->device, vk->depth_memory, NULL); vk->depth_memory = VK_NULL_HANDLE; }
    if (vk->swap_views) {
        for (u32 i = 0; i < vk->swap_count; i++) vkDestroyImageView(vk->device, vk->swap_views[i], NULL);
        free(vk->swap_views);
        vk->swap_views = NULL;
    }
    if (vk->swap_images) { free(vk->swap_images); vk->swap_images = NULL; }
    if (vk->render_semaphores) {
        for (u32 i = 0; i < vk->swap_count; i++) vkDestroySemaphore(vk->device, vk->render_semaphores[i], NULL);
        free(vk->render_semaphores);
        vk->render_semaphores = NULL;
    }
    if (vk->swapchain) { vkDestroySwapchainKHR(vk->device, vk->swapchain, NULL); vk->swapchain = VK_NULL_HANDLE; }
}

static void vk_recreate_swapchain(VKBackend *vk, u32 w, u32 h) {
    if (vkDeviceWaitIdle(vk->device) != VK_SUCCESS)
        LOG_WARN("VK: vkDeviceWaitIdle failed in recreate_swapchain");
    vk_cleanup_swapchain(vk);
    vk_create_swapchain(vk, w, h);
    vk_create_depth(vk);
    vk_create_framebuffers(vk);
}

/* ---- Init/Shutdown ---- */

static bool vk_init(RHIDevice *dev, void *window_native, void *display_native, u32 w, u32 h) {
    VKBackend *vk = calloc(1, sizeof(VKBackend));
    if (!vk) return false;

#ifdef ENGINE_PLATFORM_WINDOWS
    vk->hinstance = (HINSTANCE)display_native;
    vk->hwnd = (HWND)window_native;
#elif defined(ENGINE_PLATFORM_MACOS)
    (void)display_native;
    vk->metal_layer = window_native;   /* CAMetalLayer* */
#elif defined(ENGINE_PLATFORM_WAYLAND)
    vk->wl_display = (struct wl_display *)display_native;
    vk->wl_surface = (struct wl_surface *)window_native;
#else
    vk->display = (Display *)display_native;
    vk->window = (Window)(uintptr_t)window_native;
#endif
    vk->swap_format = VK_FORMAT_B8G8R8A8_SRGB;

    VkApplicationInfo app = {0};
    app.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    app.pApplicationName = "PureCEngine";
    app.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
    app.pEngineName = "PureCEngine";
    app.engineVersion = VK_MAKE_VERSION(1, 0, 0);
    app.apiVersion = VK_API_VERSION_1_2;

#ifndef NDEBUG
    const char *layers[] = { "VK_LAYER_KHRONOS_validation" };
#endif
    const char *extensions[] = {
        VK_KHR_SURFACE_EXTENSION_NAME,
#ifdef ENGINE_PLATFORM_WINDOWS
        VK_KHR_WIN32_SURFACE_EXTENSION_NAME,
#elif defined(ENGINE_PLATFORM_MACOS)
        VK_EXT_METAL_SURFACE_EXTENSION_NAME,
        VK_KHR_PORTABILITY_ENUMERATION_EXTENSION_NAME,
        VK_KHR_GET_PHYSICAL_DEVICE_PROPERTIES_2_EXTENSION_NAME,
#elif defined(ENGINE_PLATFORM_WAYLAND)
        VK_KHR_WAYLAND_SURFACE_EXTENSION_NAME,
#else
        VK_KHR_XLIB_SURFACE_EXTENSION_NAME,
#endif
    };

    VkInstanceCreateInfo ici = {0};
    ici.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    ici.pApplicationInfo = &app;
    ici.enabledExtensionCount = (u32)(sizeof(extensions) / sizeof(extensions[0]));
    ici.ppEnabledExtensionNames = extensions;
#ifdef ENGINE_PLATFORM_MACOS
    /* MoltenVK is a portability driver — must opt in to enumeration. */
    ici.flags |= VK_INSTANCE_CREATE_ENUMERATE_PORTABILITY_BIT_KHR;
#endif
#ifdef NDEBUG
    ici.enabledLayerCount = 0;
#else
    {
        u32 layer_count = 0;
        vkEnumerateInstanceLayerProperties(&layer_count, NULL);
        VkLayerProperties *props = calloc(layer_count, sizeof(VkLayerProperties));
        if (!props) { LOG_FATAL("VK: OOM layer properties"); free(vk); return false; }
        vkEnumerateInstanceLayerProperties(&layer_count, props);
        bool found = false;
        for (u32 i = 0; i < layer_count; i++) {
            if (strcmp(props[i].layerName, "VK_LAYER_KHRONOS_validation") == 0) { found = true; break; }
        }
        free(props);
        if (found) {
            ici.enabledLayerCount = 1;
            ici.ppEnabledLayerNames = layers;
        }
    }
#endif

    if (vkCreateInstance(&ici, NULL, &vk->instance) != VK_SUCCESS) {
        LOG_FATAL("Vulkan: failed to create instance");
        free(vk);
        return false;
    }

#ifdef ENGINE_PLATFORM_WINDOWS
    VkWin32SurfaceCreateInfoKHR sci = {0};
    sci.sType = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR;
    sci.hinstance = vk->hinstance;
    sci.hwnd = vk->hwnd;
    if (vkCreateWin32SurfaceKHR(vk->instance, &sci, NULL, &vk->surface) != VK_SUCCESS) {
        LOG_ERROR("Failed to create Win32 Vulkan surface");
        free(vk);
        return false;
    }
#elif defined(ENGINE_PLATFORM_MACOS)
    VkMetalSurfaceCreateInfoEXT sci = {0};
    sci.sType = VK_STRUCTURE_TYPE_METAL_SURFACE_CREATE_INFO_EXT;
    sci.pLayer = vk->metal_layer;   /* CAMetalLayer* supplied by the Cocoa window */
    {
        PFN_vkCreateMetalSurfaceEXT create_metal =
            (PFN_vkCreateMetalSurfaceEXT)vkGetInstanceProcAddr(
                vk->instance, "vkCreateMetalSurfaceEXT");
        if (!create_metal ||
            create_metal(vk->instance, &sci, NULL, &vk->surface) != VK_SUCCESS) {
            LOG_ERROR("Failed to create Metal (MoltenVK) Vulkan surface");
            free(vk);
            return false;
        }
    }
#elif defined(ENGINE_PLATFORM_WAYLAND)
    VkWaylandSurfaceCreateInfoKHR sci = {0};
    sci.sType = VK_STRUCTURE_TYPE_WAYLAND_SURFACE_CREATE_INFO_KHR;
    sci.display = vk->wl_display;
    sci.surface = vk->wl_surface;
    if (vkCreateWaylandSurfaceKHR(vk->instance, &sci, NULL, &vk->surface) != VK_SUCCESS) {
        LOG_ERROR("Failed to create Wayland Vulkan surface");
        free(vk);
        return false;
    }
#else
    VkXlibSurfaceCreateInfoKHR sci = {0};
    sci.sType = VK_STRUCTURE_TYPE_XLIB_SURFACE_CREATE_INFO_KHR;
    sci.dpy = vk->display;
    sci.window = vk->window;
    if (vkCreateXlibSurfaceKHR(vk->instance, &sci, NULL, &vk->surface) != VK_SUCCESS) {
        LOG_ERROR("Failed to create Xlib Vulkan surface");
        free(vk);
        return false;
    }
#endif

    u32 gpu_count = 0;
    vkEnumeratePhysicalDevices(vk->instance, &gpu_count, NULL);
    if (gpu_count == 0) { LOG_FATAL("Vulkan: no GPUs"); free(vk); return false; }
    VkPhysicalDevice *gpus = calloc(gpu_count, sizeof(VkPhysicalDevice));
    if (!gpus) { LOG_FATAL("VK: OOM GPU list"); free(vk); return false; }
    vkEnumeratePhysicalDevices(vk->instance, &gpu_count, gpus);
    vk->physical = gpus[0];
    free(gpus);
    vkGetPhysicalDeviceProperties(vk->physical, &vk->device_props);
    LOG_INFO("Vulkan GPU: %s (push constants: %u bytes, UBO alignment: %lu)",
             vk->device_props.deviceName,
             vk->device_props.limits.maxPushConstantsSize,
             (unsigned long)vk->device_props.limits.minUniformBufferOffsetAlignment);

    u32 queue_count = 0;
    vkGetPhysicalDeviceQueueFamilyProperties(vk->physical, &queue_count, NULL);
    VkQueueFamilyProperties *queues = calloc(queue_count, sizeof(VkQueueFamilyProperties));
    if (!queues) { LOG_FATAL("VK: OOM queue list"); free(vk); return false; }
    vkGetPhysicalDeviceQueueFamilyProperties(vk->physical, &queue_count, queues);
    vk->graphics_family = UINT32_MAX;
    vk->present_family = UINT32_MAX;
    for (u32 i = 0; i < queue_count; i++) {
        if (queues[i].queueFlags & VK_QUEUE_GRAPHICS_BIT && vk->graphics_family == UINT32_MAX)
            vk->graphics_family = i;
        VkBool32 present = VK_FALSE;
        vkGetPhysicalDeviceSurfaceSupportKHR(vk->physical, i, vk->surface, &present);
        if (present && vk->present_family == UINT32_MAX)
            vk->present_family = i;
    }
    free(queues);
    if (vk->graphics_family == UINT32_MAX || vk->present_family == UINT32_MAX) {
        LOG_FATAL("Vulkan: no suitable queue family");
        free(vk);
        return false;
    }

    f32 queue_priority = 1.0f;
    VkDeviceQueueCreateInfo qci = {0};
    qci.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
    qci.queueFamilyIndex = vk->graphics_family;
    qci.queueCount = 1;
    qci.pQueuePriorities = &queue_priority;

    /* Enable only features we actually use and that the device supports.
     * drawIndirectCount is a Vulkan 1.2 feature queried via the feature2 chain;
     * the GPU-driven indirect pipeline calls vkCmdDrawIndexedIndirectCount. */
    VkPhysicalDeviceVulkan12Features supported_vk12 = {0};
    supported_vk12.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_2_FEATURES;
    VkPhysicalDeviceFeatures2 supported_features2 = {0};
    supported_features2.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FEATURES_2;
    supported_features2.pNext = &supported_vk12;
    vkGetPhysicalDeviceFeatures2(vk->physical, &supported_features2);

    VkPhysicalDeviceFeatures enabled_features = {0};
    if (supported_features2.features.fillModeNonSolid) {
        enabled_features.fillModeNonSolid = VK_TRUE; /* wireframe debug pipelines */
        vk->feat_fill_mode_non_solid = true;
    }
    /* R169: Allow VS/GS/TS to write PointSize (particle POINT_LIST sprites). */
    if (supported_features2.features.shaderTessellationAndGeometryPointSize) {
        enabled_features.shaderTessellationAndGeometryPointSize = VK_TRUE;
    }

    VkPhysicalDeviceVulkan12Features enabled_vk12 = {0};
    enabled_vk12.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_2_FEATURES;
    if (supported_vk12.drawIndirectCount) {
        enabled_vk12.drawIndirectCount = VK_TRUE;
        vk->feat_draw_indirect_count = true;
    }
    /* Partially-bound descriptors let one shared material layout serve both the
     * forward shaders (binding 5 = single u_ssao) and deferred_light_vk.frag
     * (binding 5 = u_point_shadow_cubes[4]); each shader only needs the array
     * elements it actually samples to be valid. */
    if (supported_vk12.descriptorBindingPartiallyBound) {
        enabled_vk12.descriptorBindingPartiallyBound = VK_TRUE;
        vk->feat_partially_bound = true;
    }

    const char *dev_extensions[] = {
        VK_KHR_SWAPCHAIN_EXTENSION_NAME,
#ifdef ENGINE_PLATFORM_MACOS
        /* Mandatory on MoltenVK: a portability driver must have its subset
         * extension enabled whenever the device advertises it. */
        "VK_KHR_portability_subset",
#endif
    };
    VkDeviceCreateInfo dci = {0};
    dci.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
    dci.pNext = &enabled_vk12;
    dci.queueCreateInfoCount = 1;
    dci.pQueueCreateInfos = &qci;
    dci.enabledExtensionCount = (u32)(sizeof(dev_extensions) / sizeof(dev_extensions[0]));
    dci.ppEnabledExtensionNames = dev_extensions;
    dci.pEnabledFeatures = &enabled_features;

    if (vkCreateDevice(vk->physical, &dci, NULL, &vk->device) != VK_SUCCESS) {
        LOG_FATAL("Vulkan: failed to create device");
        free(vk);
        return false;
    }

    vkGetDeviceQueue(vk->device, vk->graphics_family, 0, &vk->graphics_queue);
    vkGetDeviceQueue(vk->device, vk->present_family, 0, &vk->present_queue);

    vk_create_swapchain(vk, w, h);
    vk_create_render_pass(vk);
    vk_create_depth(vk);
    vk_create_framebuffers(vk);

    VkCommandPoolCreateInfo cpci = {0};
    cpci.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
    cpci.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
    cpci.queueFamilyIndex = vk->graphics_family;
    if (vkCreateCommandPool(vk->device, &cpci, NULL, &vk->cmd_pool) != VK_SUCCESS) {
        LOG_FATAL("VK: failed to create command pool");
        free(vk); return false;
    }

    VkCommandBufferAllocateInfo cbai = {0};
    cbai.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    cbai.commandPool = vk->cmd_pool;
    cbai.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
    cbai.commandBufferCount = VK_MAX_FRAMES;
    if (vkAllocateCommandBuffers(vk->device, &cbai, vk->cmd_buffers) != VK_SUCCESS) {
        LOG_FATAL("VK: failed to allocate command buffers");
        free(vk); return false;
    }

    vk->uniform_ring_size = 4 * 1024 * 1024;
    for (u32 i = 0; i < VK_MAX_FRAMES; i++) {
        VkBufferCreateInfo bci = {0};
        bci.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
        bci.size = vk->uniform_ring_size;
        bci.usage = VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT;
        bci.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
        if (vkCreateBuffer(vk->device, &bci, NULL, &vk->uniform_ring[i].buffer) != VK_SUCCESS) {
            LOG_FATAL("VK: failed to create uniform buffer %u", i);
            free(vk); return false;
        }

        VkMemoryRequirements mem_req;
        vkGetBufferMemoryRequirements(vk->device, vk->uniform_ring[i].buffer, &mem_req);

        VkMemoryAllocateInfo mai = {0};
        mai.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
        mai.allocationSize = mem_req.size;
        mai.memoryTypeIndex = vk_find_memory(vk, mem_req.memoryTypeBits,
            VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);
        if (vkAllocateMemory(vk->device, &mai, NULL, &vk->uniform_ring[i].memory) != VK_SUCCESS) {
            LOG_FATAL("VK: failed to allocate uniform memory %u", i);
            free(vk); return false;
        }
        if (vkBindBufferMemory(vk->device, vk->uniform_ring[i].buffer, vk->uniform_ring[i].memory, 0) != VK_SUCCESS) {
            LOG_FATAL("VK: failed to bind uniform buffer %u", i);
            free(vk); return false;
        }
        if (vkMapMemory(vk->device, vk->uniform_ring[i].memory, 0, vk->uniform_ring_size, 0, (void **)&vk->uniform_mapped[i]) != VK_SUCCESS) {
            LOG_FATAL("VK: failed to map uniform memory %u", i);
            free(vk); return false;
        }
        vk->uniform_offset[i] = 0;
    }

    {
        VkDescriptorSetLayoutBinding binds[10];
        memset(binds, 0, sizeof(binds));
        for (int i = 0; i < 6; i++) {
            binds[i].binding = i;
            binds[i].descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
            binds[i].descriptorCount = 1;
            binds[i].stageFlags = VK_SHADER_STAGE_FRAGMENT_BIT;
        }
        /* IBL textures (bindings 6-8): brdf_lut, irradiance_map, prefilter_map */
        for (int i = 6; i < 9; i++) {
            binds[i].binding = i;
            binds[i].descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
            binds[i].descriptorCount = 1;
            binds[i].stageFlags = VK_SHADER_STAGE_FRAGMENT_BIT;
        }

        /* Binding 5 doubles as the forward shaders' single u_ssao and the
         * deferred lighting shader's u_point_shadow_cubes[4]. Forward point-light
         * shadows use binding 10 so SSAO at binding 5 stays valid. Layout array
         * has 10 entries: bindings 0-8 plus binding 10 at index 9. */
        VkDescriptorBindingFlags bind_flags[10] = {0};
        VkDescriptorSetLayoutBindingFlagsCreateInfo flags_ci = {0};
        flags_ci.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_BINDING_FLAGS_CREATE_INFO;
        flags_ci.bindingCount = 10;
        flags_ci.pBindingFlags = bind_flags;
        binds[9].binding = 10;
        binds[9].descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
        binds[9].stageFlags = VK_SHADER_STAGE_FRAGMENT_BIT;
        if (vk->feat_partially_bound) {
            binds[5].descriptorCount = 4;
            bind_flags[5] = VK_DESCRIPTOR_BINDING_PARTIALLY_BOUND_BIT;
            binds[9].descriptorCount = 4;
            bind_flags[9] = VK_DESCRIPTOR_BINDING_PARTIALLY_BOUND_BIT;
        } else {
            binds[9].descriptorCount = 1;
        }

        VkDescriptorSetLayoutCreateInfo dli = {0};
        dli.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
        dli.bindingCount = 10;
        dli.pBindings = binds;
        if (vk->feat_partially_bound) dli.pNext = &flags_ci;
        if (vkCreateDescriptorSetLayout(vk->device, &dli, NULL, &vk->desc_layout) != VK_SUCCESS) {
            LOG_FATAL("VK: failed to create desc layout");
            free(vk); return false;
        }
    }

    {
        VkDescriptorSetLayoutBinding texel_binds[2] = {0};
        texel_binds[0].binding = 0;
        texel_binds[0].descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_TEXEL_BUFFER;
        texel_binds[0].descriptorCount = 1;
        texel_binds[0].stageFlags = VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_FRAGMENT_BIT;
        texel_binds[1].binding = 1;
        texel_binds[1].descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_TEXEL_BUFFER;
        texel_binds[1].descriptorCount = 1;
        texel_binds[1].stageFlags = VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_FRAGMENT_BIT;

        VkDescriptorSetLayoutCreateInfo tli = {0};
        tli.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
        tli.bindingCount = 2;
        tli.pBindings = texel_binds;
        if (vkCreateDescriptorSetLayout(vk->device, &tli, NULL, &vk->texel_layout) != VK_SUCCESS) {
            LOG_FATAL("VK: failed to create texel layout");
            free(vk); return false;
        }
    }

    {
        VkDescriptorSetLayoutBinding storage_binds[8];
        memset(storage_binds, 0, sizeof(storage_binds));
        for (int i = 0; i < 8; i++) {
            storage_binds[i].binding = (u32)i;
            storage_binds[i].descriptorType = VK_DESCRIPTOR_TYPE_STORAGE_BUFFER;
            storage_binds[i].descriptorCount = 1;
            storage_binds[i].stageFlags = VK_SHADER_STAGE_COMPUTE_BIT;
        }

        VkDescriptorSetLayoutCreateInfo sli = {0};
        sli.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
        sli.bindingCount = 8;
        sli.pBindings = storage_binds;
        if (vkCreateDescriptorSetLayout(vk->device, &sli, NULL, &vk->storage_layout) != VK_SUCCESS) {
            LOG_FATAL("VK: failed to create storage layout");
            free(vk); return false;
        }
    }

    {
        VkDescriptorSetLayoutBinding svb[4];
        memset(svb, 0, sizeof(svb));
        for (int i = 0; i < 4; i++) {
            svb[i].binding = i;
            svb[i].descriptorType = VK_DESCRIPTOR_TYPE_STORAGE_BUFFER;
            svb[i].descriptorCount = 1;
            svb[i].stageFlags = VK_SHADER_STAGE_COMPUTE_BIT | VK_SHADER_STAGE_VERTEX_BIT;
        }
        VkDescriptorSetLayoutCreateInfo svli = {0};
        svli.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
        svli.bindingCount = 4;
        svli.pBindings = svb;
        if (vkCreateDescriptorSetLayout(vk->device, &svli, NULL, &vk->storage_vtx_layout) != VK_SUCCESS) {
            LOG_FATAL("VK: failed to create storage vtx layout");
            free(vk); return false;
        }
    }

    /* Auxiliary layouts: storage image / sampled mip / UBO.  Each
     * declares 4 generic bindings indexed by the public binding/unit
     * argument so the shader can opt in to whichever slot it needs. */
    {
        VkDescriptorSetLayoutBinding sib[4];
        memset(sib, 0, sizeof(sib));
        for (int i = 0; i < 4; i++) {
            sib[i].binding = (u32)i;
            sib[i].descriptorType = VK_DESCRIPTOR_TYPE_STORAGE_IMAGE;
            sib[i].descriptorCount = 1;
            sib[i].stageFlags = VK_SHADER_STAGE_COMPUTE_BIT |
                                VK_SHADER_STAGE_FRAGMENT_BIT;
        }
        VkDescriptorSetLayoutCreateInfo sili = {0};
        sili.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
        sili.bindingCount = 4;
        sili.pBindings = sib;
        if (vkCreateDescriptorSetLayout(vk->device, &sili, NULL, &vk->storage_image_layout) != VK_SUCCESS) {
            LOG_FATAL("VK: failed to create storage image layout");
            free(vk); return false;
        }
    }

    {
        VkDescriptorSetLayoutBinding smb[4];
        memset(smb, 0, sizeof(smb));
        for (int i = 0; i < 4; i++) {
            smb[i].binding = (u32)i;
            smb[i].descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
            smb[i].descriptorCount = 1;
            smb[i].stageFlags = VK_SHADER_STAGE_COMPUTE_BIT |
                                VK_SHADER_STAGE_FRAGMENT_BIT;
        }
        VkDescriptorSetLayoutCreateInfo smli = {0};
        smli.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
        smli.bindingCount = 4;
        smli.pBindings = smb;
        if (vkCreateDescriptorSetLayout(vk->device, &smli, NULL, &vk->sampler_mip_layout) != VK_SUCCESS) {
            LOG_FATAL("VK: failed to create sampler mip layout");
            free(vk); return false;
        }
    }

    {
        VkDescriptorSetLayoutBinding ub[4];
        memset(ub, 0, sizeof(ub));
        for (int i = 0; i < 4; i++) {
            ub[i].binding = (u32)i;
            ub[i].descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
            ub[i].descriptorCount = 1;
            ub[i].stageFlags = VK_SHADER_STAGE_VERTEX_BIT |
                               VK_SHADER_STAGE_FRAGMENT_BIT |
                               VK_SHADER_STAGE_COMPUTE_BIT;
        }
        VkDescriptorSetLayoutCreateInfo uli = {0};
        uli.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
        uli.bindingCount = 4;
        uli.pBindings = ub;
        if (vkCreateDescriptorSetLayout(vk->device, &uli, NULL, &vk->ubo_layout) != VK_SUCCESS) {
            LOG_FATAL("VK: failed to create UBO layout");
            free(vk); return false;
        }
    }

    {
        VkDescriptorPoolSize pool_sizes[5] = {0};
        pool_sizes[0].type = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
        pool_sizes[0].descriptorCount = 1024;
        pool_sizes[1].type = VK_DESCRIPTOR_TYPE_UNIFORM_TEXEL_BUFFER;
        pool_sizes[1].descriptorCount = 1024;
        pool_sizes[2].type = VK_DESCRIPTOR_TYPE_STORAGE_BUFFER;
        pool_sizes[2].descriptorCount = 256;
        pool_sizes[3].type = VK_DESCRIPTOR_TYPE_STORAGE_IMAGE;
        pool_sizes[3].descriptorCount = 256;
        pool_sizes[4].type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
        pool_sizes[4].descriptorCount = 256;

        VkDescriptorPoolCreateInfo dpi = {0};
        dpi.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
        dpi.flags = VK_DESCRIPTOR_POOL_CREATE_FREE_DESCRIPTOR_SET_BIT;
        dpi.maxSets = 4096;
        dpi.poolSizeCount = 5;
        dpi.pPoolSizes = pool_sizes;
        for (u32 i = 0; i < VK_MAX_FRAMES; i++) {
            if (vkCreateDescriptorPool(vk->device, &dpi, NULL, &vk->desc_pools[i]) != VK_SUCCESS) {
                LOG_FATAL("VK: failed to create descriptor pool %u", i);
                free(vk); return false;
            }
        }
    }

    for (u32 i = 0; i < VK_MAX_FRAMES; i++) {
        VkSemaphoreCreateInfo sci2 = {0};
        sci2.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;
        if (vkCreateSemaphore(vk->device, &sci2, NULL, &vk->image_semaphores[i]) != VK_SUCCESS) {
            LOG_FATAL("VK: failed to create image semaphore %u", i);
            free(vk); return false;
        }
        VkFenceCreateInfo fci = {0};
        fci.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
        fci.flags = VK_FENCE_CREATE_SIGNALED_BIT;
        if (vkCreateFence(vk->device, &fci, NULL, &vk->fences[i]) != VK_SUCCESS) {
            LOG_FATAL("VK: failed to create fence %u", i);
            free(vk); return false;
        }
    }

    dev->backend_data = vk;
    dev->width = w;
    dev->height = h;

    vk->shaderc_compiler = shaderc_compiler_initialize();
    if (!vk->shaderc_compiler) {
        LOG_FATAL("Vulkan: shaderc_compiler_initialize failed");
    }

    LOG_INFO("Vulkan initialized");
    return true;
}

static void vk_shutdown(RHIDevice *dev) {
    VKBackend *vk = vk_backend(dev);
    if (!vk) return;
    if (vkDeviceWaitIdle(vk->device) != VK_SUCCESS)
        LOG_WARN("VK: vkDeviceWaitIdle failed in shutdown");
    /* R175: Device idle — free deferred mip-upload resources without waiting. */
    if (g_mip_upload_pending.pending) {
        if (g_mip_upload_pending.fence)
            vkDestroyFence(vk->device, g_mip_upload_pending.fence, NULL);
        if (g_mip_upload_pending.cb)
            vkFreeCommandBuffers(vk->device, g_mip_upload_pending.pool, 1, &g_mip_upload_pending.cb);
        if (g_mip_upload_pending.staging)
            vkDestroyBuffer(vk->device, g_mip_upload_pending.staging, NULL);
        if (g_mip_upload_pending.staging_mem)
            vkFreeMemory(vk->device, g_mip_upload_pending.staging_mem, NULL);
        memset(&g_mip_upload_pending, 0, sizeof(g_mip_upload_pending));
    }

    if (vk->shaderc_compiler) {
        shaderc_compiler_release(vk->shaderc_compiler);
        vk->shaderc_compiler = NULL;
    }

    for (u32 i = 0; i < VK_MAX_FRAMES; i++) {
        vkDestroySemaphore(vk->device, vk->image_semaphores[i], NULL);
        vkDestroyFence(vk->device, vk->fences[i], NULL);
        vkUnmapMemory(vk->device, vk->uniform_ring[i].memory);
        vkDestroyBuffer(vk->device, vk->uniform_ring[i].buffer, NULL);
        vkFreeMemory(vk->device, vk->uniform_ring[i].memory, NULL);
    }

    vkFreeCommandBuffers(vk->device, vk->cmd_pool, VK_MAX_FRAMES, vk->cmd_buffers);
    vkDestroyCommandPool(vk->device, vk->cmd_pool, NULL);
    for (u32 i = 0; i < VK_MAX_FRAMES; i++)
        vkDestroyDescriptorPool(vk->device, vk->desc_pools[i], NULL);
    vkDestroyDescriptorSetLayout(vk->device, vk->desc_layout, NULL);
    vkDestroyDescriptorSetLayout(vk->device, vk->texel_layout, NULL);
    vkDestroyDescriptorSetLayout(vk->device, vk->storage_layout, NULL);
    vkDestroyDescriptorSetLayout(vk->device, vk->storage_vtx_layout, NULL);
    vkDestroyDescriptorSetLayout(vk->device, vk->storage_image_layout, NULL);
    vkDestroyDescriptorSetLayout(vk->device, vk->sampler_mip_layout, NULL);
    vkDestroyDescriptorSetLayout(vk->device, vk->ubo_layout, NULL);
    vk_cleanup_swapchain(vk);
    if (vk->render_pass) vkDestroyRenderPass(vk->device, vk->render_pass, NULL);
    if (vk->render_pass_load) vkDestroyRenderPass(vk->device, vk->render_pass_load, NULL);
    for (u32 i = 0; i < vk->pipe_rp_count; i++) {
        vkDestroyRenderPass(vk->device, vk->pipe_rp_cache[i], NULL);
    }
    vkDestroyDevice(vk->device, NULL);
    vkDestroySurfaceKHR(vk->instance, vk->surface, NULL);
    vkDestroyInstance(vk->instance, NULL);
    free(vk);
    dev->backend_data = NULL;
}

/* ---- RHI Implementation (overrides GL versions via conditional compilation) ---- */

static VkFormat vk_format_from_rhi(RHIFormat fmt) {
    switch (fmt) {
    case RHI_FORMAT_R8G8B8A8_UNORM: return VK_FORMAT_R8G8B8A8_UNORM;
    case RHI_FORMAT_B8G8R8A8_UNORM: return VK_FORMAT_B8G8R8A8_UNORM;
    case RHI_FORMAT_R16G16B16A16_SFLOAT: return VK_FORMAT_R16G16B16A16_SFLOAT;
    case RHI_FORMAT_R32_FLOAT:      return VK_FORMAT_R32_SFLOAT;
    case RHI_FORMAT_D32_FLOAT:      return VK_FORMAT_D32_SFLOAT;
    default: return VK_FORMAT_R8G8B8A8_UNORM;
    }
}

RHIDevice *rhi_device_create(RHIBackend backend, void *window_native, void *display_native, u32 w, u32 h) {
    (void)backend;
    RHIDevice *dev = calloc(1, sizeof(RHIDevice));
    if (!dev) return NULL;
    rhi_init_freelist(dev);
    if (!vk_init(dev, window_native, display_native, w, h)) {
        free(dev);
        return NULL;
    }
    g_current_device = dev;
    return dev;
}

void rhi_device_destroy(RHIDevice *dev) {
    if (!dev) return;
    VKBackend *vk = vk_backend(dev);
    if (vkDeviceWaitIdle(vk->device) != VK_SUCCESS)
        LOG_WARN("VK: vkDeviceWaitIdle failed in device_destroy");

    for (u32 i = 0; i < RHI_MAX_RESOURCES; i++) {
        if (!dev->slots[i].alive) continue;
        switch (dev->slots[i].type) {
        case RHI_RES_SHADER: {
            VKShaderData *sd = (VKShaderData *)dev->slots[i].ptr;
            if (sd) { vkDestroyShaderModule(vk->device, sd->module, NULL); free(sd->spirv); free(sd); }
            break;
        }
        case RHI_RES_PIPELINE: {
            VKPipelineData *pd = (VKPipelineData *)dev->slots[i].ptr;
            if (pd) {
                vkDestroyPipeline(vk->device, pd->pipeline, NULL);
                for (u32 v = 0; v < pd->variant_count; v++) {
                    vkDestroyPipeline(vk->device, pd->variant_pipe[v], NULL);
                }
                vkDestroyPipelineLayout(vk->device, pd->layout, NULL);
                free(pd->vs_spirv);
                free(pd->fs_spirv);
                free(pd);
            }
            break;
        }
        case RHI_RES_BUFFER: {
            VKBufferData *bd = (VKBufferData *)dev->slots[i].ptr;
            if (bd) { vkDestroyBuffer(vk->device, bd->buffer, NULL); vkFreeMemory(vk->device, bd->memory, NULL); free(bd); }
            break;
        }
        case RHI_RES_TEXTURE: {
            VKTextureData *td = (VKTextureData *)dev->slots[i].ptr;
            if (td) {
                for (u32 m = 0; m < VK_MAX_MIP_VIEWS; m++) {
                    if (td->mip_views[m] != VK_NULL_HANDLE)
                        vkDestroyImageView(vk->device, td->mip_views[m], NULL);
                }
                vkDestroyImageView(vk->device, td->view, NULL);
                vkDestroyImage(vk->device, td->image, NULL);
                vkFreeMemory(vk->device, td->memory, NULL);
                free(td);
            }
            break;
        }
        case RHI_RES_SAMPLER: {
            VKSamplerData *sd = (VKSamplerData *)dev->slots[i].ptr;
            if (sd) { vkDestroySampler(vk->device, sd->sampler, NULL); free(sd); }
            break;
        }
        case RHI_RES_MRT_FBO: {
            /* freed explicitly via rhi_mrt_fbo_destroy; device-destroy skips */
            break;
        }
        case RHI_RES_CUBEMAP_DEPTH_FBO: {
            /* freed explicitly via rhi_cubemap_depth_fbo_destroy */
            break;
        }
        default:
            free(dev->slots[i].ptr);
            break;
        }
    }

    vk_shutdown(dev);
    if (g_current_device == dev) g_current_device = NULL;
    free(dev);
}

void rhi_device_resize(RHIDevice *dev, u32 w, u32 h) {
    VKBackend *vk = vk_backend(dev);
    vk_recreate_swapchain(vk, w, h);
    dev->width = w;
    dev->height = h;
}

RHICmdBuffer *rhi_frame_begin(RHIDevice *dev) {
    VKBackend *vk = vk_backend(dev);
    g_current_device = dev;

    /* R175: Ensure deferred mip uploads finished before this frame samples them. */
    vk_mip_upload_reclaim(vk);

    if (vkWaitForFences(vk->device, 1, &vk->fences[vk->current_frame], VK_TRUE, UINT64_MAX) != VK_SUCCESS) {
        LOG_FATAL("VK: vkWaitForFences failed in frame_begin");
        vk->frame_started = false;
        return (RHICmdBuffer *)vk;
    }
    if (vkResetFences(vk->device, 1, &vk->fences[vk->current_frame]) != VK_SUCCESS) {
        LOG_FATAL("VK: vkResetFences failed in frame_begin");
        vk->frame_started = false;
        return (RHICmdBuffer *)vk;
    }
    if (vkResetDescriptorPool(vk->device, vk->desc_pools[vk->current_frame], 0) != VK_SUCCESS) {
        LOG_FATAL("VK: vkResetDescriptorPool failed in frame_begin");
        vk->frame_started = false;
        return (RHICmdBuffer *)vk;
    }

    VkResult res = vkAcquireNextImageKHR(vk->device, vk->swapchain, UINT64_MAX,
        vk->image_semaphores[vk->current_frame], VK_NULL_HANDLE, &vk->image_index);
    if (res == VK_ERROR_OUT_OF_DATE_KHR) {
        vk_recreate_swapchain(vk, dev->width, dev->height);
        res = vkAcquireNextImageKHR(vk->device, vk->swapchain, UINT64_MAX,
            vk->image_semaphores[vk->current_frame], VK_NULL_HANDLE, &vk->image_index);
        if (res != VK_SUCCESS && res != VK_SUBOPTIMAL_KHR) {
            vk->frame_started = false;
            return (RHICmdBuffer *)vk;
        }
    } else if (res != VK_SUCCESS && res != VK_SUBOPTIMAL_KHR) {
        /* R148: Handle VK_ERROR_DEVICE_LOST / VK_ERROR_SURFACE_LOST_KHR / etc.
         * Without this, a non-OUT_OF_DATE error falls through and proceeds to
         * record commands with a stale image_index, potentially using an invalid
         * framebuffer and causing a cascade of GPU errors. */
        LOG_ERROR("VK: vkAcquireNextImageKHR failed (res=%d)", (int)res);
        vk->frame_started = false;
        return (RHICmdBuffer *)vk;
    }
    /* VK_SUBOPTIMAL_KHR is a success — swapchain rebuild deferred to rhi_present */

    /* R150: Guard against NULL framebuffers — vk_create_framebuffers may have failed
     * (e.g., OOM on calloc, vkCreateFramebuffer error) even though the swapchain
     * itself is valid and vkAcquireNextImageKHR succeeded. Without this check,
     * vk->framebuffers[vk->image_index] dereferences NULL. */
    if (!vk->framebuffers) {
        LOG_ERROR("VK: framebuffers not available in frame_begin");
        vk->frame_started = false;
        return (RHICmdBuffer *)vk;
    }

    if (vkResetCommandBuffer(vk->cmd_buffers[vk->current_frame], 0) != VK_SUCCESS) {
        LOG_FATAL("VK: vkResetCommandBuffer failed in frame_begin");
        vk->frame_started = false;
        return (RHICmdBuffer *)vk;
    }
    vk->current_pipeline = VK_NULL_HANDLE; /* R89-1: reset pipeline cache for new command buffer */
    vk->vp_valid = false; vk->sc_valid = false;  /* R94-2: reset viewport/scissor cache */
    vk->push_dirty = false; vk->push_dirty_min = 256; vk->push_dirty_max = 0;  /* R96-1: clean state — each set_uniform marks its own range. Avoids pushing 256 bytes to compute pipelines that only declare 128-byte push constant ranges. */

    VkCommandBufferBeginInfo bi = {0};
    bi.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
    bi.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;
    if (vkBeginCommandBuffer(vk->cmd_buffers[vk->current_frame], &bi) != VK_SUCCESS) {
        LOG_FATAL("VK: vkBeginCommandBuffer failed in frame_begin");
        vk->frame_started = false;
        return (RHICmdBuffer *)vk;
    }

    VkRenderPassBeginInfo rpi = {0};
    rpi.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
    rpi.renderPass = vk->render_pass;
    rpi.framebuffer = vk->framebuffers[vk->image_index];
    rpi.renderArea.offset = (VkOffset2D){0, 0};
    rpi.renderArea.extent = vk->swap_extent;

    VkClearValue clears[2] = {0};
    clears[0].color = (VkClearColorValue){{0.2f, 0.25f, 0.35f, 1.0f}};
    clears[1].depthStencil = (VkClearDepthStencilValue){1.0f, 0};
    rpi.clearValueCount = 2;
    rpi.pClearValues = clears;

    vkCmdBeginRenderPass(vk->cmd_buffers[vk->current_frame], &rpi, VK_SUBPASS_CONTENTS_INLINE);
    vk->render_pass_active = true;
    vk_record_pass(vk, vk->render_pass_load, vk->framebuffers[vk->image_index],
                   vk->swap_extent.width, vk->swap_extent.height, vk->swap_format);

    VkViewport vp = {0, 0, (f32)vk->swap_extent.width, (f32)vk->swap_extent.height, 0.0f, 1.0f};
    vkCmdSetViewport(vk->cmd_buffers[vk->current_frame], 0, 1, &vp);
    VkRect2D sc = {{0, 0}, vk->swap_extent};
    vkCmdSetScissor(vk->cmd_buffers[vk->current_frame], 0, 1, &sc);

    vk->frame_started = true;
    vk->current_pipeline = VK_NULL_HANDLE;
    vk->current_pipeline_data = NULL;  /* R106-1: reset stale pointer — desc pool was just reset, so storage_set is dangling */
    vk->storage_set_valid = false;     /* R106-1: force re-alloc on next bind_storage_buffer */
    vk->vp_valid = false; vk->sc_valid = false;  /* R94-2: reset for swapchain pass */
    vk->depth_lequal = false;

    vk->uniform_offset[vk->current_frame] = 0;

    return (RHICmdBuffer *)vk;
}

void rhi_screenshot(RHIDevice *dev, u32 x, u32 y, u32 w, u32 h, u8 *pixels) {
    if (!dev || !pixels) return;
    VKBackend *vk = vk_backend(dev);
    if (!vk) return;

    /* Wait for all frames to complete before reading back. */
    if (vkDeviceWaitIdle(vk->device) != VK_SUCCESS)
        LOG_WARN("VK: vkDeviceWaitIdle failed in screenshot");

    /* Create a host-visible staging buffer. */
    VkDeviceSize buf_size = (VkDeviceSize)w * h * 4u;
    VkBufferCreateInfo buf_ci = {0};
    buf_ci.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
    buf_ci.size  = buf_size;
    buf_ci.usage = VK_BUFFER_USAGE_TRANSFER_DST_BIT;
    buf_ci.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

    VkBuffer staging_buf;
    if (vkCreateBuffer(vk->device, &buf_ci, NULL, &staging_buf) != VK_SUCCESS) {
        LOG_WARN("screenshot: failed to create staging buffer");
        return;
    }

    VkMemoryRequirements mem_req;
    vkGetBufferMemoryRequirements(vk->device, staging_buf, &mem_req);

    VkMemoryAllocateInfo alloc = {0};
    alloc.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
    alloc.allocationSize = mem_req.size;
    alloc.memoryTypeIndex = vk_find_memory(vk, mem_req.memoryTypeBits,
                                            VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);

    VkDeviceMemory staging_mem;
    if (vkAllocateMemory(vk->device, &alloc, NULL, &staging_mem) != VK_SUCCESS) {
        LOG_WARN("screenshot: failed to allocate staging memory");
        vkDestroyBuffer(vk->device, staging_buf, NULL);
        return;
    }
    if (vkBindBufferMemory(vk->device, staging_buf, staging_mem, 0) != VK_SUCCESS) {
        LOG_WARN("screenshot: failed to bind staging buffer memory");
        vkFreeMemory(vk->device, staging_mem, NULL);
        vkDestroyBuffer(vk->device, staging_buf, NULL);
        return;
    }

    /* Allocate a one-shot command buffer for the copy. */
    VkCommandBufferAllocateInfo cmd_ai = {0};
    cmd_ai.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    cmd_ai.commandPool = vk->cmd_pool;
    cmd_ai.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
    cmd_ai.commandBufferCount = 1;

    VkCommandBuffer cmd;
    if (vkAllocateCommandBuffers(vk->device, &cmd_ai, &cmd) != VK_SUCCESS) {
        LOG_FATAL("VK: failed to allocate screenshot command buffer");
        vkDestroyBuffer(vk->device, staging_buf, NULL);
        vkFreeMemory(vk->device, staging_mem, NULL);
        return;
    }

    VkCommandBufferBeginInfo begin = {0};
    begin.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
    begin.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;
    if (vkBeginCommandBuffer(cmd, &begin) != VK_SUCCESS) {
        LOG_FATAL("VK: failed to begin screenshot command buffer");
        vkFreeCommandBuffers(vk->device, vk->cmd_pool, 1, &cmd);
        vkDestroyBuffer(vk->device, staging_buf, NULL);
        vkFreeMemory(vk->device, staging_mem, NULL);
        return;
    }

    /* Transition swapchain image to TRANSFER_SRC_OPTIMAL. */
    VkImage src_image = vk->swap_images[vk->image_index];
    VkImageMemoryBarrier barrier = {0};
    barrier.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
    barrier.srcAccessMask = VK_ACCESS_MEMORY_READ_BIT;
    barrier.dstAccessMask = VK_ACCESS_TRANSFER_READ_BIT;
    barrier.oldLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;
    barrier.newLayout = VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL;
    barrier.image = src_image;
    barrier.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
    barrier.subresourceRange.levelCount = 1;
    barrier.subresourceRange.layerCount = 1;
    vkCmdPipelineBarrier(cmd,
                         VK_PIPELINE_STAGE_TRANSFER_BIT, VK_PIPELINE_STAGE_TRANSFER_BIT,
                         0, 0, NULL, 0, NULL, 1, &barrier);

    /* Copy region from (x, y) to buffer. */
    VkBufferImageCopy region = {0};
    region.imageSubresource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
    region.imageSubresource.layerCount = 1;
    region.imageOffset.x = (int32_t)x;
    region.imageOffset.y = (int32_t)y;
    region.imageExtent.width  = w;
    region.imageExtent.height = h;
    region.imageExtent.depth  = 1;
    vkCmdCopyImageToBuffer(cmd, src_image, VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL,
                           staging_buf, 1, &region);

    /* Restore swapchain image layout. */
    barrier.srcAccessMask = VK_ACCESS_TRANSFER_READ_BIT;
    barrier.dstAccessMask = VK_ACCESS_MEMORY_READ_BIT;
    barrier.oldLayout = VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL;
    barrier.newLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;
    vkCmdPipelineBarrier(cmd,
                         VK_PIPELINE_STAGE_TRANSFER_BIT, VK_PIPELINE_STAGE_TRANSFER_BIT,
                         0, 0, NULL, 0, NULL, 1, &barrier);

    if (vkEndCommandBuffer(cmd) != VK_SUCCESS) {
        LOG_FATAL("VK: failed to end screenshot command buffer");
        vkFreeCommandBuffers(vk->device, vk->cmd_pool, 1, &cmd);
        vkDestroyBuffer(vk->device, staging_buf, NULL);
        vkFreeMemory(vk->device, staging_mem, NULL);
        return;
    }

    /* Submit and wait. */
    VkSubmitInfo submit = {0};
    submit.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
    submit.commandBufferCount = 1;
    submit.pCommandBuffers = &cmd;
    if (vkQueueSubmit(vk->graphics_queue, 1, &submit, VK_NULL_HANDLE) != VK_SUCCESS) {
        LOG_FATAL("VK: failed to submit screenshot command buffer");
        vkFreeCommandBuffers(vk->device, vk->cmd_pool, 1, &cmd);
        vkDestroyBuffer(vk->device, staging_buf, NULL);
        vkFreeMemory(vk->device, staging_mem, NULL);
        return;
    }
    if (vkQueueWaitIdle(vk->graphics_queue) != VK_SUCCESS)
        LOG_WARN("VK: vkQueueWaitIdle failed in screenshot");

    vkFreeCommandBuffers(vk->device, vk->cmd_pool, 1, &cmd);

    /* Map buffer and copy RGBA to pixels (VK swapchain is BGRA, convert to RGBA). */
    void *mapped;
    if (vkMapMemory(vk->device, staging_mem, 0, buf_size, 0, &mapped) != VK_SUCCESS) {
        LOG_FATAL("VK: vkMapMemory failed in screenshot");
        vkDestroyBuffer(vk->device, staging_buf, NULL);
        vkFreeMemory(vk->device, staging_mem, NULL);
        return;
    }
    const u8 *src = (const u8 *)mapped;
    for (u32 i = 0; i < w * h; ++i) {
        pixels[i * 4u + 0u] = src[i * 4u + 2u]; /* R <- B */
        pixels[i * 4u + 1u] = src[i * 4u + 1u]; /* G <- G */
        pixels[i * 4u + 2u] = src[i * 4u + 0u]; /* B <- R */
        pixels[i * 4u + 3u] = src[i * 4u + 3u]; /* A <- A */
    }
    vkUnmapMemory(vk->device, staging_mem);

    vkFreeMemory(vk->device, staging_mem, NULL);
    vkDestroyBuffer(vk->device, staging_buf, NULL);
}

struct RHIGPUTimer {
    VkQueryPool query_pool;
    VkDevice    vkdev;
    f64         timestamp_period;
    bool        result_ready;
};

RHIGPUTimer *rhi_gpu_timer_create(RHIDevice *dev) {
    VKBackend *vk = vk_backend(dev);
    RHIGPUTimer *t = calloc(1, sizeof(RHIGPUTimer));
    if (!t) return NULL;
    t->vkdev = vk->device;
    t->timestamp_period = (f64)vk->device_props.limits.timestampPeriod;
    VkQueryPoolCreateInfo ci = {0};
    ci.sType = VK_STRUCTURE_TYPE_QUERY_POOL_CREATE_INFO;
    ci.queryType = VK_QUERY_TYPE_TIMESTAMP;
    ci.queryCount = 2;
    if (vkCreateQueryPool(vk->device, &ci, NULL, &t->query_pool) != VK_SUCCESS) {
        LOG_WARN("VK: vkCreateQueryPool failed");
        free(t);
        return NULL;
    }
    return t;
}

void rhi_gpu_timer_destroy(RHIDevice *dev, RHIGPUTimer *t) {
    (void)dev;
    if (!t) return;
    if (t->query_pool != VK_NULL_HANDLE) vkDestroyQueryPool(t->vkdev, t->query_pool, NULL);
    free(t);
}

void rhi_gpu_timer_begin(RHIGPUTimer *t) {
    if (!t) return;
    VKBackend *vk = vk_backend(g_current_device);
    /* vkCmdResetQueryPool is forbidden inside a render pass. */
    vk_suspend_pass_for_compute(vk);
    vkCmdResetQueryPool(vk->cmd_buffers[vk->current_frame], t->query_pool, 0, 2);
    vkCmdWriteTimestamp(vk->cmd_buffers[vk->current_frame],
        VK_PIPELINE_STAGE_BOTTOM_OF_PIPE_BIT, t->query_pool, 0);
}

void rhi_gpu_timer_end(RHIGPUTimer *t) {
    if (!t) return;
    VKBackend *vk = vk_backend(g_current_device);
    vkCmdWriteTimestamp(vk->cmd_buffers[vk->current_frame],
        VK_PIPELINE_STAGE_BOTTOM_OF_PIPE_BIT, t->query_pool, 1);
    t->result_ready = true;
}

f64 rhi_gpu_timer_elapsed_ms(RHIGPUTimer *t) {
    if (!t || !t->result_ready) return 0.0;
    u64 results[2] = {0};
    VkResult r = vkGetQueryPoolResults(t->vkdev, t->query_pool, 0, 2,
        sizeof(results), results, sizeof(u64),
        VK_QUERY_RESULT_64_BIT | VK_QUERY_RESULT_WAIT_BIT);
    t->result_ready = false;
    if (r != VK_SUCCESS) return 0.0;
    return (f64)(results[1] - results[0]) * t->timestamp_period / 1e6;
}


void rhi_frame_end(RHIDevice *dev) {
    VKBackend *vk = vk_backend(dev);
    if (!vk->frame_started) return;

    /* If a compute dispatch left a pass suspended with no following draw,
     * resume it so it ends with the correct finalLayout transition. */
    vk_resume_pass_if_needed(vk);
    if (vk->render_pass_active) {
        vkCmdEndRenderPass(vk->cmd_buffers[vk->current_frame]);
        vk->render_pass_active = false;
    }
    if (vkEndCommandBuffer(vk->cmd_buffers[vk->current_frame]) != VK_SUCCESS) {
        LOG_FATAL("VK: vkEndCommandBuffer failed in frame_end");
        vk->frame_started = false;
        return;
    }

    VkSubmitInfo si = {0};
    si.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;

    VkPipelineStageFlags wait_stage = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
    si.waitSemaphoreCount = 1;
    si.pWaitSemaphores = &vk->image_semaphores[vk->current_frame];
    si.pWaitDstStageMask = &wait_stage;
    si.commandBufferCount = 1;
    si.pCommandBuffers = &vk->cmd_buffers[vk->current_frame];
    si.signalSemaphoreCount = 1;
    si.pSignalSemaphores = &vk->render_semaphores[vk->image_index];

    if (vkQueueSubmit(vk->graphics_queue, 1, &si, vk->fences[vk->current_frame]) != VK_SUCCESS) {
        LOG_FATAL("VK: vkQueueSubmit failed in frame_end");
        vk->frame_started = false;
        return;
    }
    vk->frame_started = false;
}

void rhi_present(RHIDevice *dev) {
    VKBackend *vk = vk_backend(dev);

    VkPresentInfoKHR pi = {0};
    pi.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
    pi.waitSemaphoreCount = 1;
    pi.pWaitSemaphores = &vk->render_semaphores[vk->image_index];
    pi.swapchainCount = 1;
    pi.pSwapchains = &vk->swapchain;
    pi.pImageIndices = &vk->image_index;

    VkResult res = vkQueuePresentKHR(vk->present_queue, &pi);
    if (res == VK_ERROR_OUT_OF_DATE_KHR || res == VK_SUBOPTIMAL_KHR) {
        vk_recreate_swapchain(vk, dev->width, dev->height);
    }

    vk->current_frame = (vk->current_frame + 1) % VK_MAX_FRAMES;
}

u32 rhi_frame_index(RHIDevice *dev) {
    VKBackend *vk = vk_backend(dev);
    return vk->current_frame;
}

void rhi_set_vsync(RHIDevice *dev, bool enabled) {
    VKBackend *vk = vk_backend(dev);
    vk->vsync = enabled;
    vk_recreate_swapchain(vk, dev->width, dev->height);
}

RHIShader rhi_shader_create(RHIDevice *dev, const char *source, usize len, bool is_fragment) {
    VKBackend *vk = vk_backend(dev);
    u32 *spirv = NULL; usize spirv_size = 0;
    VkShaderModule mod = vk_compile_glsl(vk, source, len, is_fragment, &spirv, &spirv_size);
    if (mod == VK_NULL_HANDLE) { free(spirv); return RHI_HANDLE_NULL; }

    VKShaderData *sd = calloc(1, sizeof(VKShaderData));
    if (!sd) { vkDestroyShaderModule(vk->device, mod, NULL); free(spirv); return RHI_HANDLE_NULL; }
    u32 idx = rhi_alloc_slot(dev);
    sd->module = mod;
    sd->spirv = spirv;
    sd->spirv_size = spirv_size;
    dev->slots[idx].ptr = sd;
    dev->slots[idx].type = RHI_RES_SHADER;
    return rhi_make_handle(idx, dev->slots[idx].generation);
}

void rhi_shader_destroy(RHIDevice *dev, RHIShader shader) {
    VKBackend *vk = vk_backend(dev);
    VKShaderData *sd = (VKShaderData *)rhi_get_resource(dev, shader);
    if (!sd) return;
    vkDestroyShaderModule(vk->device, sd->module, NULL);
    free(sd->spirv);
    free(sd);
    rhi_free_slot(dev, shader);
}

RHIShader rhi_shader_create_compute(RHIDevice *dev, const char *source, usize len) {
    VKBackend *vk = vk_backend(dev);
    shaderc_compile_options_t opts = shaderc_compile_options_initialize();
    shaderc_compile_options_set_target_env(opts, shaderc_target_env_vulkan, shaderc_env_version_vulkan_1_2);
    shaderc_compile_options_set_target_spirv(opts, shaderc_spirv_version_1_5);
    shaderc_compilation_result_t result = shaderc_compile_into_spv(
        vk->shaderc_compiler, source, len, shaderc_compute_shader, "compute.glsl", "main", opts);
    shaderc_compilation_status status = shaderc_result_get_compilation_status(result);
    if (status != shaderc_compilation_status_success) {
        LOG_FATAL("Vulkan compute shader compile error: %s", shaderc_result_get_error_message(result));
        shaderc_result_release(result);
        shaderc_compile_options_release(opts);
        return RHI_HANDLE_NULL;
    }
    usize spv_size = shaderc_result_get_length(result);
    const u32 *spv_data = (const u32 *)shaderc_result_get_bytes(result);
    VkShaderModuleCreateInfo ci = {0};
    ci.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
    ci.codeSize = spv_size;
    ci.pCode = spv_data;
    VkShaderModule mod;
    if (vkCreateShaderModule(vk->device, &ci, NULL, &mod) != VK_SUCCESS) {
        shaderc_result_release(result);
        shaderc_compile_options_release(opts);
        return RHI_HANDLE_NULL;
    }
    shaderc_result_release(result);
    shaderc_compile_options_release(opts);
    VKShaderData *sd = calloc(1, sizeof(VKShaderData));
    if (!sd) { vkDestroyShaderModule(vk->device, mod, NULL); return RHI_HANDLE_NULL; }
    u32 idx = rhi_alloc_slot(dev);
    sd->module = mod;
    dev->slots[idx].ptr = sd;
    dev->slots[idx].type = RHI_RES_SHADER;
    return rhi_make_handle(idx, dev->slots[idx].generation);
}

static VkVertexInputBindingDescription vk_binding(u32 stride) {
    VkVertexInputBindingDescription d = {0};
    d.binding = 0;
    d.stride = stride;
    d.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;
    return d;
}

static VkVertexInputAttributeDescription vk_attr(u32 location, u32 offset, VkFormat fmt) {
    VkVertexInputAttributeDescription d = {0};
    d.location = location;
    d.binding = 0;
    d.format = fmt;
    d.offset = offset;
    return d;
}

/* Return a render pass suitable for creating a graphics pipeline that targets a
 * color attachment of VkFormat `vkfmt`. The swapchain format maps to the
 * swapchain pass. Other formats get a cached template pass
 * [color(vkfmt), depth(D32_SFLOAT)] structurally identical to the offscreen FBO
 * pass, so a pipeline created here is render-pass-compatible with that FBO. */
static VkRenderPass vk_pipeline_render_pass_fmt(VKBackend *vk, VkFormat vkfmt) {
    if (vkfmt == vk->swap_format) return vk->render_pass; /* default/swapchain */
    for (u32 i = 0; i < vk->pipe_rp_count; i++) {
        if (vk->pipe_rp_formats[i] == vkfmt) return vk->pipe_rp_cache[i];
    }
    if (vk->pipe_rp_count >= 8) return vk->render_pass; /* cache full (won't happen) */

    /* This pass is used ONLY for pipeline creation, never for rendering.
     * Render-pass compatibility ignores load/store ops and layouts, so use
     * DONT_CARE (valid with initialLayout=UNDEFINED). Only formats, sample
     * counts and the subpass attachment references must match the real FBO. */
    VkAttachmentDescription atts[2] = {0};
    atts[0].format = vkfmt;
    atts[0].samples = VK_SAMPLE_COUNT_1_BIT;
    atts[0].loadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
    atts[0].storeOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
    atts[0].stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
    atts[0].stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
    atts[0].initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
    atts[0].finalLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
    atts[1].format = VK_FORMAT_D32_SFLOAT;
    atts[1].samples = VK_SAMPLE_COUNT_1_BIT;
    atts[1].loadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
    atts[1].storeOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
    atts[1].stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
    atts[1].stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
    atts[1].initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
    atts[1].finalLayout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;

    VkAttachmentReference color_ref = {0, VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL};
    VkAttachmentReference depth_ref = {1, VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL};
    VkSubpassDescription sp = {0};
    sp.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
    sp.colorAttachmentCount = 1;
    sp.pColorAttachments = &color_ref;
    sp.pDepthStencilAttachment = &depth_ref;

    /* Must match the offscreen FBO render pass dependency exactly: the
     * validation layer treats a differing dependencyCount as a render-pass
     * incompatibility (VUID-vkCmdDraw-renderPass-02684), so a pipeline whose
     * template pass omits this dependency would be flagged when drawn into the
     * real FBO pass even though formats/subpasses match. */
    VkSubpassDependency dep = {0};
    dep.srcSubpass = VK_SUBPASS_EXTERNAL;
    dep.dstSubpass = 0;
    dep.srcStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
    dep.srcAccessMask = 0;
    dep.dstStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
    dep.dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;

    VkRenderPassCreateInfo ci = {0};
    ci.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
    ci.attachmentCount = 2;
    ci.pAttachments = atts;
    ci.subpassCount = 1;
    ci.pSubpasses = &sp;
    ci.dependencyCount = 1;
    ci.pDependencies = &dep;

    VkRenderPass rp = VK_NULL_HANDLE;
    if (vkCreateRenderPass(vk->device, &ci, NULL, &rp) != VK_SUCCESS) {
        return vk->render_pass;
    }
    vk->pipe_rp_formats[vk->pipe_rp_count] = vkfmt;
    vk->pipe_rp_cache[vk->pipe_rp_count] = rp;
    vk->pipe_rp_count++;
    return rp;
}

/* Resolve a desc color_format hint to the VkFormat the pipeline's base render
 * pass uses. The unset default (RHI_FORMAT_R8G8B8A8_UNORM == 0) means
 * "swapchain". */
static VkFormat vk_desc_base_color_fmt(VKBackend *vk, const RHIPipelineDesc *desc) {
    if (desc->color_format == RHI_FORMAT_R8G8B8A8_UNORM) return vk->swap_format;
    return vk_format_from_rhi(desc->color_format);
}

static VkRenderPass vk_pipeline_render_pass(VKBackend *vk, RHIFormat fmt) {
    return vk_pipeline_render_pass_fmt(vk, (fmt == RHI_FORMAT_R8G8B8A8_UNORM)
                                          ? vk->swap_format : vk_format_from_rhi(fmt));
}

/* Build a graphics VkPipeline from `desc` against render pass `rp`, using the
 * supplied (already-created, render-pass-independent) pipeline layout and shader
 * modules. Factored out of rhi_pipeline_create so the base pipeline and any
 * per-render-pass-format variants share identical state. Returns VK_NULL_HANDLE
 * on failure; writes the resolved vertex stride to *out_stride. */
static VkPipeline vk_build_graphics_pipeline(VKBackend *vk, const RHIPipelineDesc *desc,
                                             VkPipelineLayout layout, VkShaderModule vs_mod,
                                             VkShaderModule fs_mod, VkRenderPass rp,
                                             u32 *out_stride) {
    VkPipelineShaderStageCreateInfo stages[2] = {0};
    stages[0].sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
    stages[0].stage = VK_SHADER_STAGE_VERTEX_BIT;
    stages[0].module = vs_mod;
    stages[0].pName = "main";
    stages[1].sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
    stages[1].stage = VK_SHADER_STAGE_FRAGMENT_BIT;
    stages[1].module = fs_mod;
    stages[1].pName = "main";

    VkPipelineVertexInputStateCreateInfo vertex_input = {0};
    vertex_input.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;

    VkVertexInputBindingDescription binding;
    VkVertexInputAttributeDescription attrs[5];
    u32 stride = desc->vertex_stride;

    if (desc->no_vertex_input) {
        stride = 0;
    } else if (desc->font_vertex) {
        stride = 32;
        binding = vk_binding(32);
        attrs[0] = vk_attr(0, 0, VK_FORMAT_R32G32_SFLOAT);
        attrs[1] = vk_attr(1, 2 * sizeof(f32), VK_FORMAT_R32G32_SFLOAT);
        attrs[2] = vk_attr(2, 4 * sizeof(f32), VK_FORMAT_R32G32B32A32_SFLOAT);
        vertex_input.vertexBindingDescriptionCount = 1;
        vertex_input.pVertexBindingDescriptions = &binding;
        vertex_input.vertexAttributeDescriptionCount = 3;
        vertex_input.pVertexAttributeDescriptions = attrs;
    } else if (desc->skinned_vertex) {
        stride = 64;
        binding = vk_binding(64);
        attrs[0] = vk_attr(0, 0, VK_FORMAT_R32G32B32_SFLOAT);
        attrs[1] = vk_attr(1, 3 * sizeof(f32), VK_FORMAT_R32G32B32_SFLOAT);
        attrs[2] = vk_attr(2, 6 * sizeof(f32), VK_FORMAT_R32G32_SFLOAT);
        attrs[3] = vk_attr(3, 8 * sizeof(f32), VK_FORMAT_R32G32B32A32_UINT);
        attrs[4] = vk_attr(4, 8 * sizeof(f32) + 4 * sizeof(u32), VK_FORMAT_R32G32B32A32_SFLOAT);
        vertex_input.vertexBindingDescriptionCount = 1;
        vertex_input.pVertexBindingDescriptions = &binding;
        vertex_input.vertexAttributeDescriptionCount = 5;
        vertex_input.pVertexAttributeDescriptions = attrs;
    } else if (stride == 12) {
        binding = vk_binding(12);
        attrs[0] = vk_attr(0, 0, VK_FORMAT_R32G32B32_SFLOAT);
        vertex_input.vertexBindingDescriptionCount = 1;
        vertex_input.pVertexBindingDescriptions = &binding;
        vertex_input.vertexAttributeDescriptionCount = 1;
        vertex_input.pVertexAttributeDescriptions = attrs;
    } else {
        stride = stride > 0 ? stride : 32;
        binding = vk_binding(stride);
        attrs[0] = vk_attr(0, 0, VK_FORMAT_R32G32B32_SFLOAT);
        attrs[1] = vk_attr(1, 3 * sizeof(f32), VK_FORMAT_R32G32B32_SFLOAT);
        attrs[2] = vk_attr(2, 6 * sizeof(f32), VK_FORMAT_R32G32_SFLOAT);
        vertex_input.vertexBindingDescriptionCount = 1;
        vertex_input.pVertexBindingDescriptions = &binding;
        vertex_input.vertexAttributeDescriptionCount = 3;
        vertex_input.pVertexAttributeDescriptions = attrs;
    }

    VkPipelineInputAssemblyStateCreateInfo assembly = {0};
    assembly.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
    /* R168-C: POINT_LIST for particle point sprites; default TRIANGLE_LIST. */
    assembly.topology = desc->point_list ? VK_PRIMITIVE_TOPOLOGY_POINT_LIST
                                         : VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
    assembly.primitiveRestartEnable = VK_FALSE;

    VkPipelineViewportStateCreateInfo viewport = {0};
    viewport.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
    viewport.viewportCount = 1;
    viewport.scissorCount = 1;

    VkPipelineRasterizationStateCreateInfo raster = {0};
    raster.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
    raster.depthClampEnable = VK_FALSE;
    raster.rasterizerDiscardEnable = VK_FALSE;
    raster.polygonMode = (desc->wireframe && vk->feat_fill_mode_non_solid)
                       ? VK_POLYGON_MODE_LINE : VK_POLYGON_MODE_FILL;
    raster.lineWidth = 1.0f;
    raster.cullMode = (desc->no_vertex_input || desc->disable_culling) ? VK_CULL_MODE_NONE : VK_CULL_MODE_BACK_BIT;
    raster.frontFace = VK_FRONT_FACE_CLOCKWISE;
    raster.depthBiasEnable = VK_FALSE;

    VkPipelineMultisampleStateCreateInfo msaa = {0};
    msaa.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
    msaa.sampleShadingEnable = VK_FALSE;
    msaa.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;

    VkPipelineColorBlendAttachmentState blend_att = {0};
    blend_att.colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT |
                               VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;
    if (desc->alpha_blend) {
        blend_att.blendEnable = VK_TRUE;
        blend_att.srcColorBlendFactor = VK_BLEND_FACTOR_SRC_ALPHA;
        blend_att.dstColorBlendFactor = VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA;
        blend_att.colorBlendOp = VK_BLEND_OP_ADD;
        blend_att.srcAlphaBlendFactor = VK_BLEND_FACTOR_SRC_ALPHA;
        blend_att.dstAlphaBlendFactor = VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA;
        blend_att.alphaBlendOp = VK_BLEND_OP_ADD;
    } else {
        blend_att.blendEnable = VK_FALSE;
    }

    VkPipelineColorBlendStateCreateInfo blend = {0};
    blend.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
    blend.logicOpEnable = VK_FALSE;
    blend.attachmentCount = 1;
    blend.pAttachments = &blend_att;

    VkPipelineDepthStencilStateCreateInfo depth = {0};
    depth.sType = VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO;
    depth.depthTestEnable = VK_TRUE;
    depth.depthWriteEnable = desc->depth_write_disable ? VK_FALSE : VK_TRUE;
    depth.depthCompareOp = desc->depth_compare_lequal ? VK_COMPARE_OP_LESS_OR_EQUAL : VK_COMPARE_OP_LESS;
    depth.depthBoundsTestEnable = VK_FALSE;
    depth.stencilTestEnable = VK_FALSE;

    VkDynamicState dynamic_states[] = {
        VK_DYNAMIC_STATE_VIEWPORT,
        VK_DYNAMIC_STATE_SCISSOR,
    };
    VkPipelineDynamicStateCreateInfo dynamic = {0};
    dynamic.sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
    dynamic.dynamicStateCount = 2;
    dynamic.pDynamicStates = dynamic_states;

    VkGraphicsPipelineCreateInfo pci = {0};
    pci.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
    pci.stageCount = 2;
    pci.pStages = stages;
    pci.pVertexInputState = &vertex_input;
    pci.pInputAssemblyState = &assembly;
    pci.pViewportState = &viewport;
    pci.pRasterizationState = &raster;
    pci.pMultisampleState = &msaa;
    pci.pDepthStencilState = &depth;
    pci.pColorBlendState = &blend;
    pci.pDynamicState = &dynamic;
    pci.layout = layout;
    pci.renderPass = rp;
    pci.subpass = 0;

    VkPipeline pipeline = VK_NULL_HANDLE;
    VkResult res = vkCreateGraphicsPipelines(vk->device, VK_NULL_HANDLE, 1, &pci, NULL, &pipeline);
    if (out_stride) *out_stride = stride;
    if (res != VK_SUCCESS) {
        LOG_FATAL("Vulkan: failed to create pipeline: %d", res);
        return VK_NULL_HANDLE;
    }
    return pipeline;
}

/* Return a pipeline compatible with a render pass of color format `vkfmt`,
 * building (and caching) a variant on demand. Falls back to the base pipeline if
 * the format is the base format, not variant-able, or a rebuild fails. */
static VkPipeline vk_pipeline_for_fmt(VKBackend *vk, VKPipelineData *pd, VkFormat vkfmt) {
    if (pd->is_compute || pd->base_color_fmt == VK_FORMAT_UNDEFINED) return pd->pipeline;
    if (vkfmt == VK_FORMAT_UNDEFINED || vkfmt == pd->base_color_fmt) return pd->pipeline;
    for (u32 i = 0; i < pd->variant_count; i++) {
        if (pd->variant_fmt[i] == vkfmt) return pd->variant_pipe[i];
    }
    if (pd->variant_count >= 8 || !pd->vs_spirv || !pd->fs_spirv) return pd->pipeline;

    /* Recreate transient shader modules from the retained SPIR-V. */
    VkShaderModuleCreateInfo smci = {0};
    smci.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
    smci.codeSize = pd->vs_spirv_size; smci.pCode = pd->vs_spirv;
    VkShaderModule vs_mod = VK_NULL_HANDLE;
    if (vkCreateShaderModule(vk->device, &smci, NULL, &vs_mod) != VK_SUCCESS) return pd->pipeline;
    smci.codeSize = pd->fs_spirv_size; smci.pCode = pd->fs_spirv;
    VkShaderModule fs_mod = VK_NULL_HANDLE;
    if (vkCreateShaderModule(vk->device, &smci, NULL, &fs_mod) != VK_SUCCESS) {
        vkDestroyShaderModule(vk->device, vs_mod, NULL);
        return pd->pipeline;
    }

    VkRenderPass rp = vk_pipeline_render_pass_fmt(vk, vkfmt);
    VkPipeline var = vk_build_graphics_pipeline(vk, &pd->build_desc, pd->layout, vs_mod, fs_mod, rp, NULL);
    vkDestroyShaderModule(vk->device, vs_mod, NULL);
    vkDestroyShaderModule(vk->device, fs_mod, NULL);
    if (var == VK_NULL_HANDLE) return pd->pipeline;

    pd->variant_fmt[pd->variant_count] = vkfmt;
    pd->variant_pipe[pd->variant_count] = var;
    pd->variant_count++;
    return var;
}

RHIPipeline rhi_pipeline_create(RHIDevice *dev, const RHIPipelineDesc *desc) {
    VKBackend *vk = vk_backend(dev);

    if (desc->is_compute) {
        VKShaderData *cs_data = (VKShaderData *)rhi_get_resource(dev, desc->frag);
        if (!cs_data) return RHI_HANDLE_NULL;

        VkPipelineShaderStageCreateInfo stage = {0};
        stage.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
        stage.stage = VK_SHADER_STAGE_COMPUTE_BIT;
        stage.module = cs_data->module;
        stage.pName = "main";

        VkDescriptorSetLayout set_layouts[4];
        u32 set_count = 0;
        u32 storage_image_set = VK_INVALID_SET;
        u32 sampler_mip_set = VK_INVALID_SET;
        u32 ubo_set = VK_INVALID_SET;
        /* Compute pipelines always wire all four auxiliary sets so that
         * rhi_cmd_bind_storage_buffer / image_texture / texture_mip /
         * uniform_buffer can target them generically.  Empty sets cost
         * nothing if the shader never references them. */
        set_layouts[set_count++] = vk->storage_layout;
        storage_image_set = set_count;
        set_layouts[set_count++] = vk->storage_image_layout;
        sampler_mip_set = set_count;
        set_layouts[set_count++] = vk->sampler_mip_layout;
        ubo_set = set_count;
        set_layouts[set_count++] = vk->ubo_layout;

        VkPushConstantRange push_range = {0};
        push_range.stageFlags = VK_SHADER_STAGE_COMPUTE_BIT;
        push_range.offset = 0;
        push_range.size = 128;

        VkPipelineLayoutCreateInfo lci = {0};
        lci.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
        lci.setLayoutCount = set_count;
        lci.pSetLayouts = set_layouts;
        lci.pushConstantRangeCount = 1;
        lci.pPushConstantRanges = &push_range;

        VkPipelineLayout layout;
        if (vkCreatePipelineLayout(vk->device, &lci, NULL, &layout) != VK_SUCCESS) {
            LOG_FATAL("VK: failed to create compute pipeline layout");
            return RHI_HANDLE_NULL;
        }

        VkComputePipelineCreateInfo cpci = {0};
        cpci.sType = VK_STRUCTURE_TYPE_COMPUTE_PIPELINE_CREATE_INFO;
        cpci.stage = stage;
        cpci.layout = layout;

        VkPipeline pipeline;
        VkResult res = vkCreateComputePipelines(vk->device, VK_NULL_HANDLE, 1, &cpci, NULL, &pipeline);
        if (res != VK_SUCCESS) {
            LOG_FATAL("Vulkan: failed to create compute pipeline: %d", res);
            vkDestroyPipelineLayout(vk->device, layout, NULL);
            return RHI_HANDLE_NULL;
        }

        VKPipelineData *pd = calloc(1, sizeof(VKPipelineData));
        if (!pd) { vkDestroyPipeline(vk->device, pipeline, NULL); vkDestroyPipelineLayout(vk->device, layout, NULL); return RHI_HANDLE_NULL; }
        u32 idx = rhi_alloc_slot(dev);
        pd->layout = layout;
        pd->pipeline = pipeline;
        pd->no_vertex_input = true;
        pd->uses_texel_buffer = false;
        pd->is_compute = true;
        pd->storage_image_set = (u8)storage_image_set;
        pd->sampler_mip_set = (u8)sampler_mip_set;
        pd->ubo_set = (u8)ubo_set;
        dev->slots[idx].ptr = pd;
        dev->slots[idx].type = RHI_RES_PIPELINE;
        return rhi_make_handle(idx, dev->slots[idx].generation);
    }

    VKShaderData *vs_data = (VKShaderData *)rhi_get_resource(dev, desc->vert);
    VKShaderData *fs_data = (VKShaderData *)rhi_get_resource(dev, desc->frag);
    if (!vs_data || !fs_data) return RHI_HANDLE_NULL;

    /* The pipeline layout is render-pass-independent and shared by the base
     * pipeline and all its render-pass-format variants. */
    VkPushConstantRange push_range = {0};
    push_range.stageFlags = VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_FRAGMENT_BIT;
    push_range.offset = 0;
    push_range.size = 256;
    if (push_range.size > vk->device_props.limits.maxPushConstantsSize) {
        LOG_ERROR("Push constant range %u exceeds device max %u",
                  push_range.size, vk->device_props.limits.maxPushConstantsSize);
        push_range.size = vk->device_props.limits.maxPushConstantsSize;
    }

    VkPipelineLayoutCreateInfo lci = {0};
    lci.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
    VkDescriptorSetLayout set_layouts[4];
    u32 set_count = 0;
    if (desc->uses_textures) {
        set_layouts[set_count++] = vk->desc_layout;
    }
    if (desc->uses_texel_buffer) {
        set_layouts[set_count++] = vk->texel_layout;
    }
    if (desc->uses_storage) {
        set_layouts[set_count++] = vk->storage_vtx_layout;
    }
    /* Append the auxiliary UBO set so rhi_cmd_bind_uniform_buffer can
     * always target a graphics pipeline regardless of whether earlier
     * sets were declared. */
    u32 graphics_ubo_set = set_count;
    set_layouts[set_count++] = vk->ubo_layout;
    lci.setLayoutCount = set_count;
    lci.pSetLayouts = set_layouts;
    lci.pushConstantRangeCount = 1;
    lci.pPushConstantRanges = &push_range;

    VkPipelineLayout layout;
    if (vkCreatePipelineLayout(vk->device, &lci, NULL, &layout) != VK_SUCCESS) {
        LOG_FATAL("VK: failed to create graphics pipeline layout");
        return RHI_HANDLE_NULL;
    }

    VkRenderPass base_rp = desc->is_shadow_depth ? vk->shadow_render_pass
                         : vk_pipeline_render_pass(vk, desc->color_format);
    u32 stride = 0;
    VkPipeline pipeline = vk_build_graphics_pipeline(vk, desc, layout, vs_data->module,
                                                     fs_data->module, base_rp, &stride);
    if (pipeline == VK_NULL_HANDLE) {
        vkDestroyPipelineLayout(vk->device, layout, NULL);
        return RHI_HANDLE_NULL;
    }

    VKPipelineData *pd = calloc(1, sizeof(VKPipelineData));
    if (!pd) { vkDestroyPipeline(vk->device, pipeline, NULL); vkDestroyPipelineLayout(vk->device, layout, NULL); return RHI_HANDLE_NULL; }
    u32 idx = rhi_alloc_slot(dev);
    pd->layout = layout;
    pd->pipeline = pipeline;
    pd->vertex_stride = stride;
    pd->no_vertex_input = desc->no_vertex_input;
    pd->uses_texel_buffer = desc->uses_texel_buffer;
    pd->is_instanced = desc->is_instanced;
    pd->uses_storage = desc->uses_storage;
    pd->terrain_layout = desc->terrain_layout;
    pd->water_layout = desc->water_layout;
    pd->combined_aa_layout = desc->combined_aa_layout;
    pd->combined_color_layout = desc->combined_color_layout;
    pd->storage_image_set = (u8)VK_INVALID_SET;
    pd->sampler_mip_set = (u8)VK_INVALID_SET;
    pd->ubo_set = (u8)graphics_ubo_set;
    /* Variant support: depth-only shadow pipelines never need color variants
     * (marked UNDEFINED); color pipelines retain their SPIR-V + desc so a
     * render-pass-format variant can be built lazily at bind time. */
    pd->build_desc = *desc;
    pd->build_desc.vert = RHI_HANDLE_NULL;
    pd->build_desc.frag = RHI_HANDLE_NULL;
    if (desc->is_shadow_depth) {
        pd->base_color_fmt = VK_FORMAT_UNDEFINED;
    } else {
        pd->base_color_fmt = vk_desc_base_color_fmt(vk, desc);
        if (vs_data->spirv && fs_data->spirv) {
            pd->vs_spirv = malloc(vs_data->spirv_size);
            pd->fs_spirv = malloc(fs_data->spirv_size);
            if (pd->vs_spirv && pd->fs_spirv) {
                memcpy(pd->vs_spirv, vs_data->spirv, vs_data->spirv_size);
                memcpy(pd->fs_spirv, fs_data->spirv, fs_data->spirv_size);
                pd->vs_spirv_size = vs_data->spirv_size;
                pd->fs_spirv_size = fs_data->spirv_size;
            } else {
                free(pd->vs_spirv); free(pd->fs_spirv);
                pd->vs_spirv = pd->fs_spirv = NULL;
            }
        }
    }
    dev->slots[idx].ptr = pd;
    dev->slots[idx].type = RHI_RES_PIPELINE;
    return rhi_make_handle(idx, dev->slots[idx].generation);
}

/* Destroy a pipeline's GPU objects (base + variants + layout) and free its
 * retained SPIR-V. Does not touch the resource slot. */
static void vk_pipeline_data_free(VKBackend *vk, VKPipelineData *pd) {
    if (!pd) return;
    vkDestroyPipeline(vk->device, pd->pipeline, NULL);
    for (u32 i = 0; i < pd->variant_count; i++) {
        vkDestroyPipeline(vk->device, pd->variant_pipe[i], NULL);
    }
    vkDestroyPipelineLayout(vk->device, pd->layout, NULL);
    free(pd->vs_spirv);
    free(pd->fs_spirv);
    free(pd);
}

void rhi_pipeline_destroy(RHIDevice *dev, RHIPipeline pipe) {
    VKBackend *vk = vk_backend(dev);
    VKPipelineData *pd = (VKPipelineData *)rhi_get_resource(dev, pipe);
    if (!pd) return;
    vk_wait_frames(vk);
    vk_pipeline_data_free(vk, pd);
    rhi_free_slot(dev, pipe);
}

/* R181: One-shot host→DEVICE_LOCAL buffer copy (create / rare update). */
static bool vk_buffer_staging_upload(VKBackend *vk, VkBuffer dst, usize dst_offset,
                                     const void *data, usize size) {
    if (!data || size == 0u) return true;
    VkBuffer staging;
    VkDeviceMemory staging_mem;
    VkBufferCreateInfo bci = {0};
    bci.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
    bci.size = size;
    bci.usage = VK_BUFFER_USAGE_TRANSFER_SRC_BIT;
    bci.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
    if (vkCreateBuffer(vk->device, &bci, NULL, &staging) != VK_SUCCESS) return false;

    VkMemoryRequirements smr;
    vkGetBufferMemoryRequirements(vk->device, staging, &smr);
    VkMemoryAllocateInfo smi = {0};
    smi.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
    smi.allocationSize = smr.size;
    smi.memoryTypeIndex = vk_find_memory(vk, smr.memoryTypeBits,
        VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);
    if (smi.memoryTypeIndex == UINT32_MAX ||
        vkAllocateMemory(vk->device, &smi, NULL, &staging_mem) != VK_SUCCESS) {
        vkDestroyBuffer(vk->device, staging, NULL);
        return false;
    }
    if (vkBindBufferMemory(vk->device, staging, staging_mem, 0) != VK_SUCCESS) {
        vkFreeMemory(vk->device, staging_mem, NULL);
        vkDestroyBuffer(vk->device, staging, NULL);
        return false;
    }
    void *mapped = NULL;
    if (vkMapMemory(vk->device, staging_mem, 0, size, 0, &mapped) != VK_SUCCESS) {
        vkFreeMemory(vk->device, staging_mem, NULL);
        vkDestroyBuffer(vk->device, staging, NULL);
        return false;
    }
    memcpy(mapped, data, size);
    vkUnmapMemory(vk->device, staging_mem);

    vk_wait_frames(vk);
    VkCommandBufferAllocateInfo cbai = {0};
    cbai.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    cbai.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
    cbai.commandPool = vk->cmd_pool;
    cbai.commandBufferCount = 1;
    VkCommandBuffer tmp_cb;
    if (vkAllocateCommandBuffers(vk->device, &cbai, &tmp_cb) != VK_SUCCESS) {
        vkFreeMemory(vk->device, staging_mem, NULL);
        vkDestroyBuffer(vk->device, staging, NULL);
        return false;
    }
    VkCommandBufferBeginInfo cbi = {0};
    cbi.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
    cbi.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;
    if (vkBeginCommandBuffer(tmp_cb, &cbi) != VK_SUCCESS) {
        vkFreeCommandBuffers(vk->device, vk->cmd_pool, 1, &tmp_cb);
        vkFreeMemory(vk->device, staging_mem, NULL);
        vkDestroyBuffer(vk->device, staging, NULL);
        return false;
    }
    VkBufferCopy region = {0};
    region.srcOffset = 0;
    region.dstOffset = dst_offset;
    region.size = size;
    vkCmdCopyBuffer(tmp_cb, staging, dst, 1, &region);
    if (vkEndCommandBuffer(tmp_cb) != VK_SUCCESS) {
        vkFreeCommandBuffers(vk->device, vk->cmd_pool, 1, &tmp_cb);
        vkFreeMemory(vk->device, staging_mem, NULL);
        vkDestroyBuffer(vk->device, staging, NULL);
        return false;
    }
    VkSubmitInfo si = {0};
    si.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
    si.commandBufferCount = 1;
    si.pCommandBuffers = &tmp_cb;
    if (vkQueueSubmit(vk->graphics_queue, 1, &si, VK_NULL_HANDLE) != VK_SUCCESS) {
        vkFreeCommandBuffers(vk->device, vk->cmd_pool, 1, &tmp_cb);
        vkFreeMemory(vk->device, staging_mem, NULL);
        vkDestroyBuffer(vk->device, staging, NULL);
        return false;
    }
    if (vkQueueWaitIdle(vk->graphics_queue) != VK_SUCCESS)
        LOG_WARN("VK: queue wait failed after buffer staging upload");
    vkFreeCommandBuffers(vk->device, vk->cmd_pool, 1, &tmp_cb);
    vkDestroyBuffer(vk->device, staging, NULL);
    vkFreeMemory(vk->device, staging_mem, NULL);
    return true;
}

/* R186: One-shot DEVICE_LOCAL→host download (mega mesh bake / rare readback). */
static bool vk_buffer_staging_download(VKBackend *vk, VkBuffer src, usize src_offset,
                                       void *dst, usize size) {
    if (!dst || size == 0u) return true;
    VkBuffer staging;
    VkDeviceMemory staging_mem;
    VkBufferCreateInfo bci = {0};
    bci.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
    bci.size = size;
    bci.usage = VK_BUFFER_USAGE_TRANSFER_DST_BIT;
    bci.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
    if (vkCreateBuffer(vk->device, &bci, NULL, &staging) != VK_SUCCESS) return false;

    VkMemoryRequirements smr;
    vkGetBufferMemoryRequirements(vk->device, staging, &smr);
    VkMemoryAllocateInfo smi = {0};
    smi.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
    smi.allocationSize = smr.size;
    smi.memoryTypeIndex = vk_find_memory(vk, smr.memoryTypeBits,
        VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);
    if (smi.memoryTypeIndex == UINT32_MAX ||
        vkAllocateMemory(vk->device, &smi, NULL, &staging_mem) != VK_SUCCESS) {
        vkDestroyBuffer(vk->device, staging, NULL);
        return false;
    }
    if (vkBindBufferMemory(vk->device, staging, staging_mem, 0) != VK_SUCCESS) {
        vkFreeMemory(vk->device, staging_mem, NULL);
        vkDestroyBuffer(vk->device, staging, NULL);
        return false;
    }

    vk_wait_frames(vk);
    VkCommandBufferAllocateInfo cbai = {0};
    cbai.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    cbai.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
    cbai.commandPool = vk->cmd_pool;
    cbai.commandBufferCount = 1;
    VkCommandBuffer tmp_cb;
    if (vkAllocateCommandBuffers(vk->device, &cbai, &tmp_cb) != VK_SUCCESS) {
        vkFreeMemory(vk->device, staging_mem, NULL);
        vkDestroyBuffer(vk->device, staging, NULL);
        return false;
    }
    VkCommandBufferBeginInfo cbi = {0};
    cbi.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
    cbi.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;
    if (vkBeginCommandBuffer(tmp_cb, &cbi) != VK_SUCCESS) {
        vkFreeCommandBuffers(vk->device, vk->cmd_pool, 1, &tmp_cb);
        vkFreeMemory(vk->device, staging_mem, NULL);
        vkDestroyBuffer(vk->device, staging, NULL);
        return false;
    }
    VkBufferCopy region = {0};
    region.srcOffset = src_offset;
    region.dstOffset = 0;
    region.size = size;
    vkCmdCopyBuffer(tmp_cb, src, staging, 1, &region);
    if (vkEndCommandBuffer(tmp_cb) != VK_SUCCESS) {
        vkFreeCommandBuffers(vk->device, vk->cmd_pool, 1, &tmp_cb);
        vkFreeMemory(vk->device, staging_mem, NULL);
        vkDestroyBuffer(vk->device, staging, NULL);
        return false;
    }
    VkSubmitInfo si = {0};
    si.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
    si.commandBufferCount = 1;
    si.pCommandBuffers = &tmp_cb;
    if (vkQueueSubmit(vk->graphics_queue, 1, &si, VK_NULL_HANDLE) != VK_SUCCESS) {
        vkFreeCommandBuffers(vk->device, vk->cmd_pool, 1, &tmp_cb);
        vkFreeMemory(vk->device, staging_mem, NULL);
        vkDestroyBuffer(vk->device, staging, NULL);
        return false;
    }
    if (vkQueueWaitIdle(vk->graphics_queue) != VK_SUCCESS)
        LOG_WARN("VK: queue wait failed after buffer staging download");
    vkFreeCommandBuffers(vk->device, vk->cmd_pool, 1, &tmp_cb);

    void *mapped = NULL;
    if (vkMapMemory(vk->device, staging_mem, 0, size, 0, &mapped) != VK_SUCCESS) {
        vkFreeMemory(vk->device, staging_mem, NULL);
        vkDestroyBuffer(vk->device, staging, NULL);
        return false;
    }
    memcpy(dst, mapped, size);
    vkUnmapMemory(vk->device, staging_mem);
    vkDestroyBuffer(vk->device, staging, NULL);
    vkFreeMemory(vk->device, staging_mem, NULL);
    return true;
}

RHIBuffer rhi_buffer_create(RHIDevice *dev, const RHIBufferDesc *desc) {
    VKBackend *vk = vk_backend(dev);

    VkBufferCreateInfo ci = {0};
    ci.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
    ci.size = desc->size;
    ci.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

    bool is_texel = (desc->usage & RHI_BUFFER_USAGE_TEXEL) != 0;
    if (desc->usage & RHI_BUFFER_USAGE_VERTEX)      ci.usage |= VK_BUFFER_USAGE_VERTEX_BUFFER_BIT;
    if (desc->usage & RHI_BUFFER_USAGE_INDEX)        ci.usage |= VK_BUFFER_USAGE_INDEX_BUFFER_BIT;
    if (desc->usage & RHI_BUFFER_USAGE_UNIFORM)      ci.usage |= VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT;
    if (desc->usage & RHI_BUFFER_USAGE_STORAGE) {    ci.usage |= VK_BUFFER_USAGE_STORAGE_BUFFER_BIT; ci.usage |= VK_BUFFER_USAGE_TRANSFER_SRC_BIT | VK_BUFFER_USAGE_TRANSFER_DST_BIT; /* R87-1: enable GPU-side copy */ }
    if (desc->usage & RHI_BUFFER_USAGE_INDIRECT)     ci.usage |= VK_BUFFER_USAGE_INDIRECT_BUFFER_BIT;
    if (is_texel)                                     ci.usage |= VK_BUFFER_USAGE_UNIFORM_TEXEL_BUFFER_BIT;

    /* R181/R184: DEVICE_LOCAL when initial_data is provided for:
     *  - static VERTEX/INDEX meshes
     *  - GPU-only STORAGE (±INDIRECT, ±TEXEL) buffers (e.g. particle SSBOs,
     *    light_grid TEXEL|STORAGE). UNIFORM and dynamic VERTEX/INDEX stay HV.
     * R192-B: TEXEL no longer excludes gpu_storage (grid is CS-write/FS-read). */
    bool mesh_only = (desc->usage & (RHI_BUFFER_USAGE_VERTEX | RHI_BUFFER_USAGE_INDEX)) != 0
        && (desc->usage & ~(RHI_BUFFER_USAGE_VERTEX | RHI_BUFFER_USAGE_INDEX)) == 0;
    bool gpu_storage = (desc->usage & RHI_BUFFER_USAGE_STORAGE) != 0
        && (desc->usage & (RHI_BUFFER_USAGE_UNIFORM
                           | RHI_BUFFER_USAGE_VERTEX | RHI_BUFFER_USAGE_INDEX)) == 0;
    bool device_local = desc->initial_data != NULL && (mesh_only || gpu_storage);
    if (device_local)
        ci.usage |= VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_TRANSFER_SRC_BIT; /* R186: SRC for readback */

    VkBuffer buf;
    if (vkCreateBuffer(vk->device, &ci, NULL, &buf) != VK_SUCCESS) {
        LOG_FATAL("VK: failed to create buffer");
        return RHI_HANDLE_NULL;
    }

    VkMemoryRequirements mem_req;
    vkGetBufferMemoryRequirements(vk->device, buf, &mem_req);

    VkMemoryAllocateInfo ai = {0};
    ai.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
    ai.allocationSize = mem_req.size;

    VkMemoryPropertyFlags props = device_local
        ? VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT
        : (VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);
    ai.memoryTypeIndex = vk_find_memory(vk, mem_req.memoryTypeBits, props);
    if (ai.memoryTypeIndex == UINT32_MAX && device_local) {
        /* Fallback if DEVICE_LOCAL unsupported for this usage mask. */
        device_local = false;
        props = VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT;
        ai.memoryTypeIndex = vk_find_memory(vk, mem_req.memoryTypeBits, props);
    }

    VkDeviceMemory mem;
    if (vkAllocateMemory(vk->device, &ai, NULL, &mem) != VK_SUCCESS) {
        LOG_FATAL("VK: failed to allocate buffer memory");
        vkDestroyBuffer(vk->device, buf, NULL);
        return RHI_HANDLE_NULL;
    }
    if (vkBindBufferMemory(vk->device, buf, mem, 0) != VK_SUCCESS) {
        LOG_FATAL("VK: failed to bind buffer memory");
        vkFreeMemory(vk->device, mem, NULL);
        vkDestroyBuffer(vk->device, buf, NULL);
        return RHI_HANDLE_NULL;
    }

    VkBufferView texel_view = VK_NULL_HANDLE;
    if (is_texel) {
        VkBufferViewCreateInfo bvci = {0};
        bvci.sType = VK_STRUCTURE_TYPE_BUFFER_VIEW_CREATE_INFO;
        bvci.buffer = buf;
        bvci.format = VK_FORMAT_R32G32B32A32_SFLOAT;
        bvci.range = desc->size;
        if (vkCreateBufferView(vk->device, &bvci, NULL, &texel_view) != VK_SUCCESS) {
            LOG_WARN("VK: vkCreateBufferView failed for texel buffer");
            texel_view = VK_NULL_HANDLE;
        }
    }

    VKBufferData *bd = calloc(1, sizeof(VKBufferData));
    if (!bd) { if (texel_view) vkDestroyBufferView(vk->device, texel_view, NULL); vkDestroyBuffer(vk->device, buf, NULL); vkFreeMemory(vk->device, mem, NULL); return RHI_HANDLE_NULL; }
    u32 idx = rhi_alloc_slot(dev);
    bd->buffer = buf;
    bd->memory = mem;
    bd->size = desc->size;
    bd->texel_view = texel_view;
    bd->is_texel = is_texel;
    bd->device_local = device_local;
    if (!device_local) {
        /* Persistent mapping: HOST_VISIBLE | HOST_COHERENT memory stays mapped
         * for the buffer's lifetime. Eliminates vkMapMemory/vkUnmapMemory overhead
         * in rhi_buffer_update (called multiple times per frame). */
        if (vkMapMemory(vk->device, mem, 0, desc->size, 0, (void **)&bd->mapped) != VK_SUCCESS) {
            LOG_WARN("VK: vkMapMemory failed for persistent mapping in buffer_create");
            bd->mapped = NULL;
        }
        if (desc->initial_data && bd->mapped) {
            memcpy(bd->mapped, desc->initial_data, desc->size);
        }
    } else if (desc->initial_data) {
        if (!vk_buffer_staging_upload(vk, buf, 0, desc->initial_data, desc->size)) {
            LOG_WARN("VK: DEVICE_LOCAL buffer staging upload failed");
        }
    }
    dev->slots[idx].ptr = bd;
    dev->slots[idx].type = RHI_RES_BUFFER;
    return rhi_make_handle(idx, dev->slots[idx].generation);
}

void rhi_buffer_destroy(RHIDevice *dev, RHIBuffer buf) {
    VKBackend *vk = vk_backend(dev);
    VKBufferData *bd = (VKBufferData *)rhi_get_resource(dev, buf);
    if (!bd) return;
    vk_wait_frames(vk);
    if (bd->mapped) vkUnmapMemory(vk->device, bd->memory);
    if (bd->texel_view != VK_NULL_HANDLE) vkDestroyBufferView(vk->device, bd->texel_view, NULL);
    vkDestroyBuffer(vk->device, bd->buffer, NULL);
    vkFreeMemory(vk->device, bd->memory, NULL);
    free(bd);
    rhi_free_slot(dev, buf);
}

RHITexture rhi_texture_create(RHIDevice *dev, const RHITextureDesc *desc) {
    VKBackend *vk = vk_backend(dev);
    VkFormat fmt = vk_format_from_rhi(desc->format);
    bool is_depth = (desc->format == RHI_FORMAT_D32_FLOAT);

    VkImageCreateInfo ci = {0};
    ci.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
    ci.imageType = VK_IMAGE_TYPE_2D;
    ci.format = fmt;
    ci.extent.width = desc->width;
    ci.extent.height = desc->height;
    ci.extent.depth = 1;
    ci.mipLevels = desc->mip_levels > 0 ? desc->mip_levels : 1;
    ci.arrayLayers = 1;
    ci.samples = VK_SAMPLE_COUNT_1_BIT;
    ci.tiling = VK_IMAGE_TILING_OPTIMAL;
    ci.usage = VK_IMAGE_USAGE_SAMPLED_BIT | VK_IMAGE_USAGE_TRANSFER_DST_BIT;
    /* Non-depth color formats may be bound as a storage image (e.g.
     * Hi-Z mip generation writes via imageStore).  Add STORAGE usage
     * unconditionally for color textures so any mip can later be
     * exposed through a STORAGE_IMAGE descriptor. */
    if (!is_depth) {
        ci.usage |= VK_IMAGE_USAGE_STORAGE_BIT;
    }
    ci.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
    ci.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;

    VkImage image;
    if (vkCreateImage(vk->device, &ci, NULL, &image) != VK_SUCCESS) {
        LOG_FATAL("VK: failed to create texture image");
        return RHI_HANDLE_NULL;
    }

    VkMemoryRequirements mem_req;
    vkGetImageMemoryRequirements(vk->device, image, &mem_req);

    VkMemoryAllocateInfo ai = {0};
    ai.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
    ai.allocationSize = mem_req.size;
    ai.memoryTypeIndex = vk_find_memory(vk, mem_req.memoryTypeBits, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);
    VkDeviceMemory mem;
    if (vkAllocateMemory(vk->device, &ai, NULL, &mem) != VK_SUCCESS) {
        LOG_FATAL("VK: failed to allocate texture memory");
        vkDestroyImage(vk->device, image, NULL);
        return RHI_HANDLE_NULL;
    }
    if (vkBindImageMemory(vk->device, image, mem, 0) != VK_SUCCESS) {
        LOG_FATAL("VK: failed to bind texture image memory");
        vkFreeMemory(vk->device, mem, NULL);
        vkDestroyImage(vk->device, image, NULL);
        return RHI_HANDLE_NULL;
    }

    VkImageViewCreateInfo vci = {0};
    vci.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
    vci.image = image;
    vci.viewType = VK_IMAGE_VIEW_TYPE_2D;
    vci.format = fmt;
    vci.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
    /* R171: Expose full mip chain for sampling (Hi-Z textureLod / textureQueryLevels).
     * Per-mip storage image binds create their own single-level views. */
    vci.subresourceRange.levelCount = ci.mipLevels;
    vci.subresourceRange.layerCount = 1;
    VkImageView view;
    if (vkCreateImageView(vk->device, &vci, NULL, &view) != VK_SUCCESS) {
        LOG_FATAL("VK: failed to create texture image view");
        vkFreeMemory(vk->device, mem, NULL);
        vkDestroyImage(vk->device, image, NULL);
        return RHI_HANDLE_NULL;
    }

    if (desc->data) {
        VkBuffer staging;
        VkDeviceMemory staging_mem;
        VkDeviceSize data_size = desc->width * desc->height * 4;

        VkBufferCreateInfo bci = {0};
        bci.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
        bci.size = data_size;
        bci.usage = VK_BUFFER_USAGE_TRANSFER_SRC_BIT;
        bci.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
        if (vkCreateBuffer(vk->device, &bci, NULL, &staging) != VK_SUCCESS) {
            LOG_FATAL("VK: failed to create staging buffer");
            vkDestroyImageView(vk->device, view, NULL);
            vkDestroyImage(vk->device, image, NULL);
            vkFreeMemory(vk->device, mem, NULL);
            return RHI_HANDLE_NULL;
        }

        VkMemoryRequirements smr;
        vkGetBufferMemoryRequirements(vk->device, staging, &smr);
        VkMemoryAllocateInfo smi = {0};
        smi.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
        smi.allocationSize = smr.size;
        smi.memoryTypeIndex = vk_find_memory(vk, smr.memoryTypeBits,
            VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);
        if (vkAllocateMemory(vk->device, &smi, NULL, &staging_mem) != VK_SUCCESS) {
            LOG_FATAL("VK: failed to allocate staging memory");
            vkDestroyBuffer(vk->device, staging, NULL);
            vkDestroyImageView(vk->device, view, NULL);
            vkDestroyImage(vk->device, image, NULL);
            vkFreeMemory(vk->device, mem, NULL);
            return RHI_HANDLE_NULL;
        }
        if (vkBindBufferMemory(vk->device, staging, staging_mem, 0) != VK_SUCCESS) {
            LOG_FATAL("VK: failed to bind staging buffer");
            vkFreeMemory(vk->device, staging_mem, NULL);
            vkDestroyBuffer(vk->device, staging, NULL);
            vkDestroyImageView(vk->device, view, NULL);
            vkDestroyImage(vk->device, image, NULL);
            vkFreeMemory(vk->device, mem, NULL);
            return RHI_HANDLE_NULL;
        }

        void *mapped;
        if (vkMapMemory(vk->device, staging_mem, 0, data_size, 0, &mapped) != VK_SUCCESS) {
            LOG_FATAL("VK: failed to map staging memory");
            vkFreeMemory(vk->device, staging_mem, NULL);
            vkDestroyBuffer(vk->device, staging, NULL);
            vkDestroyImageView(vk->device, view, NULL);
            vkDestroyImage(vk->device, image, NULL);
            vkFreeMemory(vk->device, mem, NULL);
            return RHI_HANDLE_NULL;
        }
        memcpy(mapped, desc->data, data_size);
        vkUnmapMemory(vk->device, staging_mem);

        VkCommandBufferAllocateInfo cbai = {0};
        cbai.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
        cbai.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
        cbai.commandPool = vk->cmd_pool;
        cbai.commandBufferCount = 1;
        VkCommandBuffer tmp_cb;
        if (vkAllocateCommandBuffers(vk->device, &cbai, &tmp_cb) != VK_SUCCESS) {
            LOG_FATAL("VK: failed to allocate texture staging command buffer");
            vkDestroyBuffer(vk->device, staging, NULL);
            vkFreeMemory(vk->device, staging_mem, NULL);
            vkDestroyImageView(vk->device, view, NULL);
            vkDestroyImage(vk->device, image, NULL);
            vkFreeMemory(vk->device, mem, NULL);
            return RHI_HANDLE_NULL;
        }
        VkCommandBufferBeginInfo cbi = {0};
        cbi.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
        cbi.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;
        if (vkBeginCommandBuffer(tmp_cb, &cbi) != VK_SUCCESS) {
            LOG_FATAL("VK: failed to begin texture staging command buffer");
            vkFreeCommandBuffers(vk->device, vk->cmd_pool, 1, &tmp_cb);
            vkDestroyBuffer(vk->device, staging, NULL);
            vkFreeMemory(vk->device, staging_mem, NULL);
            vkDestroyImageView(vk->device, view, NULL);
            vkDestroyImage(vk->device, image, NULL);
            vkFreeMemory(vk->device, mem, NULL);
            return RHI_HANDLE_NULL;
        }

        VkImageMemoryBarrier barrier = {0};
        barrier.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
        barrier.oldLayout = VK_IMAGE_LAYOUT_UNDEFINED;
        barrier.newLayout = VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL;
        barrier.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
        barrier.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
        barrier.image = image;
        barrier.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
        barrier.subresourceRange.levelCount = 1;
        barrier.subresourceRange.layerCount = 1;
        barrier.srcAccessMask = 0;
        barrier.dstAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
        vkCmdPipelineBarrier(tmp_cb, VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT,
            VK_PIPELINE_STAGE_TRANSFER_BIT, 0, 0, NULL, 0, NULL, 1, &barrier);

        VkBufferImageCopy region = {0};
        region.bufferOffset = 0;
        region.bufferRowLength = 0;
        region.bufferImageHeight = 0;
        region.imageSubresource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
        region.imageSubresource.mipLevel = 0;
        region.imageSubresource.baseArrayLayer = 0;
        region.imageSubresource.layerCount = 1;
        region.imageExtent = (VkExtent3D){desc->width, desc->height, 1};
        vkCmdCopyBufferToImage(tmp_cb, staging, image, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, 1, &region);

        VkImageMemoryBarrier barrier2 = {0};
        barrier2.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
        barrier2.oldLayout = VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL;
        barrier2.newLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
        barrier2.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
        barrier2.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
        barrier2.image = image;
        barrier2.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
        barrier2.subresourceRange.levelCount = 1;
        barrier2.subresourceRange.layerCount = 1;
        barrier2.srcAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
        barrier2.dstAccessMask = VK_ACCESS_SHADER_READ_BIT;
        vkCmdPipelineBarrier(tmp_cb, VK_PIPELINE_STAGE_TRANSFER_BIT,
            VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT, 0, 0, NULL, 0, NULL, 1, &barrier2);

        if (vkEndCommandBuffer(tmp_cb) != VK_SUCCESS) {
            LOG_FATAL("VK: failed to end texture staging command buffer");
            vkFreeCommandBuffers(vk->device, vk->cmd_pool, 1, &tmp_cb);
            vkDestroyBuffer(vk->device, staging, NULL);
            vkFreeMemory(vk->device, staging_mem, NULL);
            vkDestroyImageView(vk->device, view, NULL);
            vkDestroyImage(vk->device, image, NULL);
            vkFreeMemory(vk->device, mem, NULL);
            return RHI_HANDLE_NULL;
        }

        VkFence upload_fence;
        VkFenceCreateInfo fci = {0};
        fci.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
        if (vkCreateFence(vk->device, &fci, NULL, &upload_fence) != VK_SUCCESS) {
            LOG_FATAL("VK: failed to create texture upload fence");
            vkFreeCommandBuffers(vk->device, vk->cmd_pool, 1, &tmp_cb);
            vkDestroyBuffer(vk->device, staging, NULL);
            vkFreeMemory(vk->device, staging_mem, NULL);
            vkDestroyImageView(vk->device, view, NULL);
            vkDestroyImage(vk->device, image, NULL);
            vkFreeMemory(vk->device, mem, NULL);
            return RHI_HANDLE_NULL;
        }

        VkSubmitInfo si = {0};
        si.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
        si.commandBufferCount = 1;
        si.pCommandBuffers = &tmp_cb;
        if (vkQueueSubmit(vk->graphics_queue, 1, &si, upload_fence) != VK_SUCCESS) {
            LOG_FATAL("VK: failed to submit texture staging commands");
            vkDestroyFence(vk->device, upload_fence, NULL);
            vkFreeCommandBuffers(vk->device, vk->cmd_pool, 1, &tmp_cb);
            vkDestroyBuffer(vk->device, staging, NULL);
            vkFreeMemory(vk->device, staging_mem, NULL);
            vkDestroyImageView(vk->device, view, NULL);
            vkDestroyImage(vk->device, image, NULL);
            vkFreeMemory(vk->device, mem, NULL);
            return RHI_HANDLE_NULL;
        }
        if (vkWaitForFences(vk->device, 1, &upload_fence, VK_TRUE, UINT64_MAX) != VK_SUCCESS)
            LOG_WARN("VK: vkWaitForFences failed for texture staging");

        vkDestroyFence(vk->device, upload_fence, NULL);
        vkFreeCommandBuffers(vk->device, vk->cmd_pool, 1, &tmp_cb);
        vkDestroyBuffer(vk->device, staging, NULL);
        vkFreeMemory(vk->device, staging_mem, NULL);
    } else {
        VkCommandBufferAllocateInfo cbai = {0};
        cbai.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
        cbai.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
        cbai.commandPool = vk->cmd_pool;
        cbai.commandBufferCount = 1;
        VkCommandBuffer tmp_cb;
        if (vkAllocateCommandBuffers(vk->device, &cbai, &tmp_cb) != VK_SUCCESS) {
            LOG_FATAL("VK: failed to allocate texture layout command buffer");
            vkDestroyImageView(vk->device, view, NULL);
            vkDestroyImage(vk->device, image, NULL);
            vkFreeMemory(vk->device, mem, NULL);
            return RHI_HANDLE_NULL;
        }
        VkCommandBufferBeginInfo cbi = {0};
        cbi.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
        cbi.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;
        if (vkBeginCommandBuffer(tmp_cb, &cbi) != VK_SUCCESS) {
            LOG_FATAL("VK: failed to begin texture layout command buffer");
            vkFreeCommandBuffers(vk->device, vk->cmd_pool, 1, &tmp_cb);
            vkDestroyImageView(vk->device, view, NULL);
            vkDestroyImage(vk->device, image, NULL);
            vkFreeMemory(vk->device, mem, NULL);
            return RHI_HANDLE_NULL;
        }

        VkImageMemoryBarrier barrier = {0};
        barrier.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
        barrier.oldLayout = VK_IMAGE_LAYOUT_UNDEFINED;
        barrier.newLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
        barrier.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
        barrier.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
        barrier.image = image;
        barrier.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
        barrier.subresourceRange.levelCount = ci.mipLevels;
        barrier.subresourceRange.layerCount = 1;
        barrier.srcAccessMask = 0;
        barrier.dstAccessMask = VK_ACCESS_SHADER_READ_BIT;
        vkCmdPipelineBarrier(tmp_cb, VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT,
            VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT, 0, 0, NULL, 0, NULL, 1, &barrier);
        if (vkEndCommandBuffer(tmp_cb) != VK_SUCCESS) {
            LOG_FATAL("VK: failed to end texture layout command buffer");
            vkFreeCommandBuffers(vk->device, vk->cmd_pool, 1, &tmp_cb);
            vkDestroyImageView(vk->device, view, NULL);
            vkDestroyImage(vk->device, image, NULL);
            vkFreeMemory(vk->device, mem, NULL);
            return RHI_HANDLE_NULL;
        }

        VkFence layout_fence;
        VkFenceCreateInfo fci2 = {0};
        fci2.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
        if (vkCreateFence(vk->device, &fci2, NULL, &layout_fence) != VK_SUCCESS) {
            LOG_FATAL("VK: failed to create texture layout fence");
            vkFreeCommandBuffers(vk->device, vk->cmd_pool, 1, &tmp_cb);
            vkDestroyImageView(vk->device, view, NULL);
            vkDestroyImage(vk->device, image, NULL);
            vkFreeMemory(vk->device, mem, NULL);
            return RHI_HANDLE_NULL;
        }

        VkSubmitInfo si = {0};
        si.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
        si.commandBufferCount = 1;
        si.pCommandBuffers = &tmp_cb;
        if (vkQueueSubmit(vk->graphics_queue, 1, &si, layout_fence) != VK_SUCCESS) {
            LOG_FATAL("VK: failed to submit texture layout commands");
            vkDestroyFence(vk->device, layout_fence, NULL);
            vkFreeCommandBuffers(vk->device, vk->cmd_pool, 1, &tmp_cb);
            vkDestroyImageView(vk->device, view, NULL);
            vkDestroyImage(vk->device, image, NULL);
            vkFreeMemory(vk->device, mem, NULL);
            return RHI_HANDLE_NULL;
        }
        if (vkWaitForFences(vk->device, 1, &layout_fence, VK_TRUE, UINT64_MAX) != VK_SUCCESS) {
            LOG_FATAL("VK: vkWaitForFences failed for texture layout");
            vkDestroyFence(vk->device, layout_fence, NULL);
            vkFreeCommandBuffers(vk->device, vk->cmd_pool, 1, &tmp_cb);
            vkDestroyImageView(vk->device, view, NULL);
            vkDestroyImage(vk->device, image, NULL);
            vkFreeMemory(vk->device, mem, NULL);
            return RHI_HANDLE_NULL;
        }

        vkDestroyFence(vk->device, layout_fence, NULL);
        vkFreeCommandBuffers(vk->device, vk->cmd_pool, 1, &tmp_cb);
    }

    VKTextureData *td = calloc(1, sizeof(VKTextureData));
    if (!td) { vkDestroyImageView(vk->device, view, NULL); vkDestroyImage(vk->device, image, NULL); vkFreeMemory(vk->device, mem, NULL); return RHI_HANDLE_NULL; }
    u32 idx = rhi_alloc_slot(dev);
    td->image = image;
    td->view = view;
    td->memory = mem;
    td->width = desc->width;
    td->height = desc->height;
    td->format = fmt;
    td->mip_levels = ci.mipLevels;
    /* R174: data path only uploads/transitions mip 0; higher mips stay UNDEFINED.
     * No-data path transitions the full chain to SHADER_READ_ONLY. */
    if (desc->data) {
        if (td->mip_levels > 0u)
            td->mip_layout[0] = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
    } else {
        for (u32 m = 0; m < td->mip_levels && m < VK_MAX_MIP_VIEWS; m++) {
            td->mip_layout[m] = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
        }
    }
    dev->slots[idx].ptr = td;
    dev->slots[idx].type = RHI_RES_TEXTURE;
    return rhi_make_handle(idx, dev->slots[idx].generation);
}

void rhi_texture_upload_mip(RHIDevice *dev, RHITexture tex, u32 mip_level,
                            u32 width, u32 height, const void *data, usize size) {
    VKBackend *vk = vk_backend(dev);
    VKTextureData *td = (VKTextureData *)rhi_get_resource(dev, tex);
    if (!td || !data || size == 0) return;
    if (mip_level >= td->mip_levels) return;

    /* R175: Reclaim previous fire-and-forget upload before allocating a new one. */
    vk_mip_upload_reclaim(vk);

    /* Host-visible staging buffer holding the mip's pixels. */
    VkDeviceSize data_size = (VkDeviceSize)size;
    VkBuffer staging;
    VkBufferCreateInfo bci = {0};
    bci.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
    bci.size = data_size;
    bci.usage = VK_BUFFER_USAGE_TRANSFER_SRC_BIT;
    bci.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
    if (vkCreateBuffer(vk->device, &bci, NULL, &staging) != VK_SUCCESS) return;

    VkMemoryRequirements smr;
    vkGetBufferMemoryRequirements(vk->device, staging, &smr);
    VkMemoryAllocateInfo smi = {0};
    smi.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
    smi.allocationSize = smr.size;
    smi.memoryTypeIndex = vk_find_memory(vk, smr.memoryTypeBits,
        VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);
    VkDeviceMemory staging_mem;
    if (vkAllocateMemory(vk->device, &smi, NULL, &staging_mem) != VK_SUCCESS) {
        vkDestroyBuffer(vk->device, staging, NULL);
        return;
    }
    if (vkBindBufferMemory(vk->device, staging, staging_mem, 0) != VK_SUCCESS) {
        LOG_FATAL("VK: failed to bind mip staging buffer memory");
        vkFreeMemory(vk->device, staging_mem, NULL);
        vkDestroyBuffer(vk->device, staging, NULL);
        return;
    }

    void *mapped;
    if (vkMapMemory(vk->device, staging_mem, 0, data_size, 0, &mapped) != VK_SUCCESS) {
        LOG_FATAL("VK: failed to map mip staging memory");
        vkFreeMemory(vk->device, staging_mem, NULL);
        vkDestroyBuffer(vk->device, staging, NULL);
        return;
    }
    memcpy(mapped, data, (size_t)data_size);
    vkUnmapMemory(vk->device, staging_mem);

    VkCommandBufferAllocateInfo cbai = {0};
    cbai.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    cbai.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
    cbai.commandPool = vk->cmd_pool;
    cbai.commandBufferCount = 1;
    VkCommandBuffer cb;
    if (vkAllocateCommandBuffers(vk->device, &cbai, &cb) != VK_SUCCESS) {
        LOG_FATAL("VK: failed to allocate mip upload command buffer");
        vkDestroyBuffer(vk->device, staging, NULL);
        vkFreeMemory(vk->device, staging_mem, NULL);
        return;
    }
    VkCommandBufferBeginInfo cbi = {0};
    cbi.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
    cbi.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;
    if (vkBeginCommandBuffer(cb, &cbi) != VK_SUCCESS) {
        LOG_FATAL("VK: failed to begin mip upload command buffer");
        vkFreeCommandBuffers(vk->device, vk->cmd_pool, 1, &cb);
        vkDestroyBuffer(vk->device, staging, NULL);
        vkFreeMemory(vk->device, staging_mem, NULL);
        return;
    }

    /* R175: Use tracked mip_layout — data-create path leaves higher mips UNDEFINED. */
    VkImageLayout old_layout = (mip_level < VK_MAX_MIP_VIEWS)
        ? td->mip_layout[mip_level] : VK_IMAGE_LAYOUT_UNDEFINED;
    VkImageMemoryBarrier to_dst = {0};
    to_dst.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
    to_dst.oldLayout = old_layout;
    to_dst.newLayout = VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL;
    to_dst.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
    to_dst.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
    to_dst.image = td->image;
    to_dst.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
    to_dst.subresourceRange.baseMipLevel = mip_level;
    to_dst.subresourceRange.levelCount = 1;
    to_dst.subresourceRange.layerCount = 1;
    to_dst.srcAccessMask = (old_layout == VK_IMAGE_LAYOUT_UNDEFINED) ? 0
                         : VK_ACCESS_SHADER_READ_BIT;
    to_dst.dstAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
    VkPipelineStageFlags src_stage = (old_layout == VK_IMAGE_LAYOUT_UNDEFINED)
        ? VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT : VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT;
    vkCmdPipelineBarrier(cb, src_stage,
        VK_PIPELINE_STAGE_TRANSFER_BIT, 0, 0, NULL, 0, NULL, 1, &to_dst);

    VkBufferImageCopy region = {0};
    region.imageSubresource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
    region.imageSubresource.mipLevel = mip_level;
    region.imageSubresource.layerCount = 1;
    region.imageExtent = (VkExtent3D){width, height, 1};
    vkCmdCopyBufferToImage(cb, staging, td->image,
        VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, 1, &region);

    VkImageMemoryBarrier to_read = to_dst;
    to_read.oldLayout = VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL;
    to_read.newLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
    to_read.srcAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
    to_read.dstAccessMask = VK_ACCESS_SHADER_READ_BIT;
    vkCmdPipelineBarrier(cb, VK_PIPELINE_STAGE_TRANSFER_BIT,
        VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT, 0, 0, NULL, 0, NULL, 1, &to_read);

    if (vkEndCommandBuffer(cb) != VK_SUCCESS) {
        LOG_FATAL("VK: failed to end mip upload command buffer");
        vkFreeCommandBuffers(vk->device, vk->cmd_pool, 1, &cb);
        vkDestroyBuffer(vk->device, staging, NULL);
        vkFreeMemory(vk->device, staging_mem, NULL);
        return;
    }

    VkFence fence;
    VkFenceCreateInfo fci = {0};
    fci.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
    if (vkCreateFence(vk->device, &fci, NULL, &fence) != VK_SUCCESS) {
        LOG_FATAL("VK: failed to create mip upload fence");
        vkFreeCommandBuffers(vk->device, vk->cmd_pool, 1, &cb);
        vkDestroyBuffer(vk->device, staging, NULL);
        vkFreeMemory(vk->device, staging_mem, NULL);
        return;
    }
    VkSubmitInfo si = {0};
    si.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
    si.commandBufferCount = 1;
    si.pCommandBuffers = &cb;
    if (vkQueueSubmit(vk->graphics_queue, 1, &si, fence) != VK_SUCCESS) {
        LOG_FATAL("VK: failed to submit mip upload commands");
        vkDestroyFence(vk->device, fence, NULL);
        vkFreeCommandBuffers(vk->device, vk->cmd_pool, 1, &cb);
        vkDestroyBuffer(vk->device, staging, NULL);
        vkFreeMemory(vk->device, staging_mem, NULL);
        return;
    }
    /* R175: Do not stall the main thread — reclaim on next upload / shutdown. */
    g_mip_upload_pending.fence = fence;
    g_mip_upload_pending.staging = staging;
    g_mip_upload_pending.staging_mem = staging_mem;
    g_mip_upload_pending.cb = cb;
    g_mip_upload_pending.pool = vk->cmd_pool;
    g_mip_upload_pending.pending = true;
    /* R173: Upload ends in SHADER_READ_ONLY_OPTIMAL for this mip.
     * Layout is updated now; GPU may still be transitioning — safe because
     * subsequent uses either wait via reclaim or go through frame fences. */
    if (mip_level < VK_MAX_MIP_VIEWS)
        td->mip_layout[mip_level] = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
}

void rhi_texture_destroy(RHIDevice *dev, RHITexture tex) {
    VKBackend *vk = vk_backend(dev);
    VKTextureData *td = (VKTextureData *)rhi_get_resource(dev, tex);
    if (!td) return;
    /* R176: Pending mip upload may still reference this image — reclaim first. */
    vk_mip_upload_reclaim(vk);
    vk_wait_frames(vk);
    for (u32 m = 0; m < VK_MAX_MIP_VIEWS; m++) {
        if (td->mip_views[m] != VK_NULL_HANDLE) {
            vkDestroyImageView(vk->device, td->mip_views[m], NULL);
            td->mip_views[m] = VK_NULL_HANDLE;
        }
    }
    vkDestroyImageView(vk->device, td->view, NULL);
    vkDestroyImage(vk->device, td->image, NULL);
    vkFreeMemory(vk->device, td->memory, NULL);
    free(td);
    rhi_free_slot(dev, tex);
}

static VkFilter vk_filter(RHIFilter f) {
    return f == RHI_FILTER_LINEAR ? VK_FILTER_LINEAR : VK_FILTER_NEAREST;
}

static VkSamplerAddressMode vk_wrap(RHIWrapMode w) {
    return w == RHI_WRAP_CLAMP_TO_EDGE ? VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE : VK_SAMPLER_ADDRESS_MODE_REPEAT;
}

RHISampler rhi_sampler_create(RHIDevice *dev, const RHISamplerDesc *desc) {
    VKBackend *vk = vk_backend(dev);

    VkSamplerCreateInfo ci = {0};
    ci.sType = VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO;
    ci.magFilter = vk_filter(desc->mag_filter);
    ci.minFilter = vk_filter(desc->min_filter);
    ci.addressModeU = vk_wrap(desc->wrap_u);
    ci.addressModeV = vk_wrap(desc->wrap_v);
    ci.addressModeW = vk_wrap(desc->wrap_w);
    ci.anisotropyEnable = VK_FALSE;
    ci.maxAnisotropy = 1.0f;
    ci.borderColor = VK_BORDER_COLOR_INT_OPAQUE_BLACK;
    ci.unnormalizedCoordinates = VK_FALSE;
    ci.compareEnable = VK_FALSE;
    /* R194-B: match min_filter — Hi-Z NEAREST must not lerp across mips. */
    ci.mipmapMode = (desc->min_filter == RHI_FILTER_LINEAR)
        ? VK_SAMPLER_MIPMAP_MODE_LINEAR
        : VK_SAMPLER_MIPMAP_MODE_NEAREST;
    ci.mipLodBias = 0.0f;
    ci.minLod = 0.0f;
    /* R193-A: maxLod=0 clamped every textureLod/implicit LOD to mip0 — broke
     * IBL prefilter and Hi-Z pyramid sampling. Match GL default (~1000). */
    ci.maxLod = VK_LOD_CLAMP_NONE;

    VkSampler sampler;
    if (vkCreateSampler(vk->device, &ci, NULL, &sampler) != VK_SUCCESS) {
        LOG_FATAL("VK: failed to create sampler");
        return RHI_HANDLE_NULL;
    }

    VKSamplerData *sd = calloc(1, sizeof(VKSamplerData));
    if (!sd) { vkDestroySampler(vk->device, sampler, NULL); return RHI_HANDLE_NULL; }
    u32 idx = rhi_alloc_slot(dev);
    sd->sampler = sampler;
    dev->slots[idx].ptr = sd;
    dev->slots[idx].type = RHI_RES_SAMPLER;
    return rhi_make_handle(idx, dev->slots[idx].generation);
}

void rhi_sampler_destroy(RHIDevice *dev, RHISampler sampler) {
    VKBackend *vk = vk_backend(dev);
    VKSamplerData *sd = (VKSamplerData *)rhi_get_resource(dev, sampler);
    if (!sd) return;
    vkDestroySampler(vk->device, sd->sampler, NULL);
    free(sd);
    rhi_free_slot(dev, sampler);
}

/* ---- Command recording ---- */

void rhi_cmd_begin_render_pass(RHICmdBuffer *cmd) {
    (void)cmd;
    VKBackend *vk = vk_backend(g_current_device);
    if (vk->render_pass_active) return;
    if (!vk->framebuffers) return;  /* R150: guard against NULL framebuffers */

    VkRenderPassBeginInfo rpi = {0};
    rpi.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
    rpi.renderPass = vk->render_pass;
    rpi.framebuffer = vk->framebuffers[vk->image_index];
    rpi.renderArea.offset = (VkOffset2D){0, 0};
    rpi.renderArea.extent = vk->swap_extent;

    VkClearValue clears[2] = {0};
    rpi.clearValueCount = 2;
    rpi.pClearValues = clears;

    vkCmdBeginRenderPass(vk->cmd_buffers[vk->current_frame], &rpi, VK_SUBPASS_CONTENTS_INLINE);
    vk->render_pass_active = true;
    vk_record_pass(vk, vk->render_pass_load, vk->framebuffers[vk->image_index],
                   vk->swap_extent.width, vk->swap_extent.height, vk->swap_format);

    VkViewport vp = {0, 0, (f32)vk->swap_extent.width, (f32)vk->swap_extent.height, 0.0f, 1.0f};
    vkCmdSetViewport(vk->cmd_buffers[vk->current_frame], 0, 1, &vp);
    VkRect2D sc = {{0, 0}, vk->swap_extent};
    vkCmdSetScissor(vk->cmd_buffers[vk->current_frame], 0, 1, &sc);
    vk->vp_valid = false; vk->sc_valid = false;  /* R95-1: invalidate cache (render pass begin uses non-flipped viewport, different from rhi_cmd_set_viewport's flipped viewport) */
    vk->current_pipeline = VK_NULL_HANDLE;
}

void rhi_cmd_end_render_pass(RHICmdBuffer *cmd) {
    (void)cmd;
    VKBackend *vk = vk_backend(g_current_device);
    if (vk->render_pass_active) {
        vkCmdEndRenderPass(vk->cmd_buffers[vk->current_frame]);
        vk->render_pass_active = false;
    }
    /* A pass suspended for compute is already ended; drop the resume request. */
    vk->pass_suspended = false;
}

void rhi_cmd_bind_pipeline(RHICmdBuffer *cmd, RHIPipeline pipe) {
    (void)cmd;
    VKBackend *vk = vk_backend(g_current_device);
    VKPipelineData *pd = (VKPipelineData *)rhi_get_resource(g_current_device, pipe);
    if (!pd) return;
    VkPipelineBindPoint bind_point = pd->is_compute ?
        VK_PIPELINE_BIND_POINT_COMPUTE : VK_PIPELINE_BIND_POINT_GRAPHICS;
    /* Pick (or lazily build) a pipeline compatible with the active render pass's
     * color format, so the same logical pipeline can be drawn into FBOs of
     * different formats without breaking render-pass compatibility. */
    VkPipeline bound = pd->is_compute ? pd->pipeline
                     : vk_pipeline_for_fmt(vk, pd, vk->active_color_fmt);
    /* R89-1: Skip redundant vkCmdBindPipeline when pipeline unchanged. */
    if (bound != vk->current_pipeline) {
        vkCmdBindPipeline(vk->cmd_buffers[vk->current_frame], bind_point, bound);
        vk->current_pipeline = bound;
    }
    vk->current_pipeline_data = pd;
    /* Start a fresh storage-buffer descriptor set for this pipeline binding. */
    vk->storage_set_valid = false;
}

void rhi_cmd_bind_vertex_buffer(RHICmdBuffer *cmd, RHIBuffer buf, usize offset) {
    (void)cmd;
    VKBackend *vk = vk_backend(g_current_device);
    VKBufferData *bd = (VKBufferData *)rhi_get_resource(g_current_device, buf);
    if (!bd) return;
    VkDeviceSize off = (VkDeviceSize)offset;
    vkCmdBindVertexBuffers(vk->cmd_buffers[vk->current_frame], 0, 1, &bd->buffer, &off);
}

void rhi_cmd_bind_index_buffer(RHICmdBuffer *cmd, RHIBuffer buf, usize offset) {
    (void)cmd;
    VKBackend *vk = vk_backend(g_current_device);
    VKBufferData *bd = (VKBufferData *)rhi_get_resource(g_current_device, buf);
    if (!bd) return;
    vkCmdBindIndexBuffer(vk->cmd_buffers[vk->current_frame], bd->buffer, (VkDeviceSize)offset, VK_INDEX_TYPE_UINT32);
}

void rhi_cmd_set_viewport(RHICmdBuffer *cmd, f32 x, f32 y, f32 w, f32 h) {
    (void)cmd;
    VKBackend *vk = vk_backend(g_current_device);
    if (vk->vp_valid && vk->cached_vp_x == x && vk->cached_vp_y == y &&
        vk->cached_vp_w == w && vk->cached_vp_h == h) return;  /* R94-2: cache hit */
    VkViewport vp = {x, y + h, w, -h, 0.0f, 1.0f};
    vkCmdSetViewport(vk->cmd_buffers[vk->current_frame], 0, 1, &vp);
    vk->cached_vp_x = x; vk->cached_vp_y = y; vk->cached_vp_w = w; vk->cached_vp_h = h;
    vk->vp_valid = true;
}

void rhi_cmd_set_scissor(RHICmdBuffer *cmd, i32 x, i32 y, u32 w, u32 h) {
    (void)cmd;
    VKBackend *vk = vk_backend(g_current_device);
    if (vk->sc_valid && vk->cached_sc_x == x && vk->cached_sc_y == y &&
        vk->cached_sc_w == w && vk->cached_sc_h == h) return;  /* R94-2: cache hit */
    VkRect2D sc = {{x, y}, {w, h}};
    vkCmdSetScissor(vk->cmd_buffers[vk->current_frame], 0, 1, &sc);
    vk->cached_sc_x = x; vk->cached_sc_y = y; vk->cached_sc_w = w; vk->cached_sc_h = h;
    vk->sc_valid = true;
}

void rhi_cmd_set_shadow_viewport(RHICmdBuffer *cmd, u32 x, u32 y, u32 w, u32 h) {
    (void)cmd;
    VKBackend *vk = vk_backend(g_current_device);
    /* Non-flipped: shadow depth passes use a top-left-origin viewport (see
     * rhi_cmd_bind_shadow_map), so cascade quadrants must match that. */
    if (!vk->vp_valid || vk->cached_vp_x != (f32)x || vk->cached_vp_y != (f32)y ||
        vk->cached_vp_w != (f32)w || vk->cached_vp_h != (f32)h) {  /* R94-2: cache */
        VkViewport vp = {(f32)x, (f32)y, (f32)w, (f32)h, 0.0f, 1.0f};
        vkCmdSetViewport(vk->cmd_buffers[vk->current_frame], 0, 1, &vp);
        vk->cached_vp_x = (f32)x; vk->cached_vp_y = (f32)y; vk->cached_vp_w = (f32)w; vk->cached_vp_h = (f32)h;
        vk->vp_valid = true;
    }
    if (!vk->sc_valid || vk->cached_sc_x != (i32)x || vk->cached_sc_y != (i32)y ||
        vk->cached_sc_w != w || vk->cached_sc_h != h) {
        VkRect2D sc = {{(i32)x, (i32)y}, {w, h}};
        vkCmdSetScissor(vk->cmd_buffers[vk->current_frame], 0, 1, &sc);
        vk->cached_sc_x = (i32)x; vk->cached_sc_y = (i32)y; vk->cached_sc_w = w; vk->cached_sc_h = h;
        vk->sc_valid = true;
    }
}

/* R94-3: Forward declaration — vk_flush_push_constants is defined below
 * (before rhi_cmd_set_uniform_*) but called from draw/dispatch functions. */
static void vk_flush_push_constants(VKBackend *vk);

void rhi_cmd_draw(RHICmdBuffer *cmd, u32 vertex_count, u32 instance_count) {
    (void)cmd;
    VKBackend *vk = vk_backend(g_current_device);
    vk_resume_pass_if_needed(vk);
    vk_flush_push_constants(vk);  /* R94-3: batch push constants */
    vkCmdDraw(vk->cmd_buffers[vk->current_frame], vertex_count, instance_count, 0, 0);
}

void rhi_cmd_draw_indexed(RHICmdBuffer *cmd, u32 index_count, u32 instance_count) {
    (void)cmd;
    VKBackend *vk = vk_backend(g_current_device);
    vk_resume_pass_if_needed(vk);
    vk_flush_push_constants(vk);  /* R94-3: batch push constants */
    vkCmdDrawIndexed(vk->cmd_buffers[vk->current_frame], index_count, instance_count, 0, 0, 0);
}

void rhi_cmd_draw_indirect(RHIDevice *dev, RHIBuffer cmd_buf, u32 offset,
                           u32 draw_count, u32 stride) {
    VKBackend *vk = vk_backend(dev);
    VKBufferData *bd = (VKBufferData *)rhi_get_resource(dev, cmd_buf);
    if (!bd) return;
    vk_resume_pass_if_needed(vk);
    vk_flush_push_constants(vk);
    vkCmdDrawIndirect(vk->cmd_buffers[vk->current_frame],
                      bd->buffer, (VkDeviceSize)offset,
                      draw_count, stride);
}

void rhi_cmd_draw_indexed_indirect(RHIDevice *dev, RHIBuffer cmd_buf, u32 offset,
                                   u32 draw_count, u32 stride) {
    VKBackend *vk = vk_backend(dev);
    VKBufferData *bd = (VKBufferData *)rhi_get_resource(dev, cmd_buf);
    if (!bd) return;
    vk_resume_pass_if_needed(vk);
    vk_flush_push_constants(vk);  /* R94-3: batch push constants */
    vkCmdDrawIndexedIndirect(vk->cmd_buffers[vk->current_frame],
                             bd->buffer, (VkDeviceSize)offset,
                             draw_count, stride);
}

void rhi_cmd_draw_indexed_indirect_count(RHIDevice *dev, RHIBuffer cmd_buf, u32 cmd_offset,
                                         RHIBuffer count_buf, u32 count_offset,
                                         u32 max_draws, u32 stride) {
    VKBackend *vk = vk_backend(dev);
    VKBufferData *cmd_bd   = (VKBufferData *)rhi_get_resource(dev, cmd_buf);
    VKBufferData *count_bd = (VKBufferData *)rhi_get_resource(dev, count_buf);
    if (!cmd_bd || !count_bd) return;
    vk_resume_pass_if_needed(vk);
    vk_flush_push_constants(vk);  /* R94-3: batch push constants */
    if (vk->feat_draw_indirect_count) {
        /* Vulkan 1.2 core API; requires the drawIndirectCount feature. */
        vkCmdDrawIndexedIndirectCount(vk->cmd_buffers[vk->current_frame],
                                      cmd_bd->buffer, (VkDeviceSize)cmd_offset,
                                      count_bd->buffer, (VkDeviceSize)count_offset,
                                      max_draws, stride);
    } else {
        /* Fallback: the GPU count is unavailable, so issue max_draws draws.
         * Compacted slots beyond the live count keep instanceCount=0 (cleared
         * by the compaction pass), making the surplus draws no-ops. */
        vkCmdDrawIndexedIndirect(vk->cmd_buffers[vk->current_frame],
                                 cmd_bd->buffer, (VkDeviceSize)cmd_offset,
                                 max_draws, stride);
    }
}

void rhi_cmd_dispatch(RHICmdBuffer *cmd, u32 x, u32 y, u32 z) {
    (void)cmd;
    VKBackend *vk = vk_backend(g_current_device);
    /* Vulkan forbids vkCmdDispatch inside a render pass. Suspend the active
     * pass (its attachments are STOREd); the next draw/clear resumes it. */
    vk_suspend_pass_for_compute(vk);
    vk_flush_push_constants(vk);  /* R94-3: batch push constants */
    vkCmdDispatch(vk->cmd_buffers[vk->current_frame], x, y, z);
}

void rhi_cmd_bind_storage_buffer(RHICmdBuffer *cmd, RHIBuffer buf, u32 binding) {
    (void)cmd;
    VKBackend *vk = vk_backend(g_current_device);
    if (!vk->current_pipeline_data) return;
    VKPipelineData *cpd = vk->current_pipeline_data;
    VKBufferData *bd = (VKBufferData *)rhi_get_resource(g_current_device, buf);
    if (!bd) return;

    VkDescriptorSetLayout layout_to_use = cpd->is_compute ?
        vk->storage_layout : vk->storage_vtx_layout;

    /* Accumulate all of this pipeline's storage-buffer binds into one set so
     * a shader reading bindings 0..7 sees every buffer (allocated lazily on the
     * first bind after rhi_cmd_bind_pipeline). Updating an as-yet-unused set
     * before the dispatch/draw consumes it is valid. */
    bool need_bind = !vk->storage_set_valid;  /* R90-1: only bind once per pipeline */
    if (!vk->storage_set_valid) {
        VkDescriptorSetAllocateInfo dsai = {0};
        dsai.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
        dsai.descriptorPool = vk->desc_pools[vk->current_frame];
        dsai.descriptorSetCount = 1;
        dsai.pSetLayouts = &layout_to_use;
        if (vkAllocateDescriptorSets(vk->device, &dsai, &vk->storage_set) != VK_SUCCESS)
            return;
        vk->storage_set_valid = true;
    }
    VkDescriptorSet ds = vk->storage_set;

    VkDescriptorBufferInfo buf_info = {0};
    buf_info.buffer = bd->buffer;
    buf_info.offset = 0;
    buf_info.range = VK_WHOLE_SIZE;

    VkWriteDescriptorSet write = {0};
    write.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
    write.dstSet = ds;
    write.dstBinding = binding;
    write.descriptorCount = 1;
    write.descriptorType = VK_DESCRIPTOR_TYPE_STORAGE_BUFFER;
    write.pBufferInfo = &buf_info;

    vkUpdateDescriptorSets(vk->device, 1, &write, 0, NULL);
    /* R90-1: Skip redundant vkCmdBindDescriptorSets — the set is already bound
     * from the first storage-buffer bind after pipeline bind. Subsequent
     * vkUpdateDescriptorSets calls are visible to the GPU without re-binding. */
    if (need_bind) {
        VkPipelineBindPoint bp = cpd->is_compute ?
            VK_PIPELINE_BIND_POINT_COMPUTE : VK_PIPELINE_BIND_POINT_GRAPHICS;
        vkCmdBindDescriptorSets(vk->cmd_buffers[vk->current_frame],
            bp, cpd->layout,
            0, 1, &ds, 0, NULL);
    }
}

void rhi_cmd_memory_barrier(RHICmdBuffer *cmd) {
    (void)cmd;
    VKBackend *vk = vk_backend(g_current_device);
    vk_suspend_pass_for_compute(vk);
    VkMemoryBarrier barrier = {0};
    barrier.sType = VK_STRUCTURE_TYPE_MEMORY_BARRIER;
    barrier.srcAccessMask = VK_ACCESS_SHADER_WRITE_BIT;
    /* Cover uniform-texel reads in the fragment stage too: GPU light binning
     * writes the cluster grid as a storage buffer in compute, then the PBR
     * fragment shader samples it as a uniform texel buffer.
     * R168-B: Also cover indirect command reads (particle/gpucull draw_indirect). */
    barrier.dstAccessMask = VK_ACCESS_SHADER_READ_BIT | VK_ACCESS_UNIFORM_READ_BIT
                          | VK_ACCESS_HOST_READ_BIT | VK_ACCESS_INDIRECT_COMMAND_READ_BIT
                          | VK_ACCESS_TRANSFER_READ_BIT;
    vkCmdPipelineBarrier(vk->cmd_buffers[vk->current_frame],
        VK_PIPELINE_STAGE_COMPUTE_SHADER_BIT,
        VK_PIPELINE_STAGE_COMPUTE_SHADER_BIT | VK_PIPELINE_STAGE_VERTEX_SHADER_BIT
            | VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT | VK_PIPELINE_STAGE_HOST_BIT
            | VK_PIPELINE_STAGE_DRAW_INDIRECT_BIT | VK_PIPELINE_STAGE_TRANSFER_BIT,
        0, 1, &barrier, 0, NULL, 0, NULL);
}

void rhi_cmd_bind_image_texture(RHICmdBuffer *cmd, RHITexture tex, u32 unit, u32 mip_level, bool write_only) {
    (void)cmd;
    VKBackend *vk = vk_backend(g_current_device);
    VKTextureData *td = (VKTextureData *)rhi_get_resource(g_current_device, tex);
    if (!td || td->image == VK_NULL_HANDLE) return;
    vk_suspend_pass_for_compute(vk);

    /* Transition the requested mip to VK_IMAGE_LAYOUT_GENERAL so it can
     * be written by a compute shader via imageStore.
     * R172: Use tracked per-mip oldLayout (UNDEFINED only on first use). */
    VkImageLayout old_layout = (mip_level < VK_MAX_MIP_VIEWS)
        ? td->mip_layout[mip_level] : VK_IMAGE_LAYOUT_UNDEFINED;
    if (old_layout == VK_IMAGE_LAYOUT_UNDEFINED && !write_only)
        old_layout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;

    VkImageMemoryBarrier barrier = {0};
    barrier.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
    barrier.image = td->image;
    barrier.oldLayout = old_layout;
    barrier.newLayout = VK_IMAGE_LAYOUT_GENERAL;
    barrier.srcAccessMask = (old_layout == VK_IMAGE_LAYOUT_UNDEFINED) ? 0
        : (VK_ACCESS_SHADER_READ_BIT | VK_ACCESS_SHADER_WRITE_BIT);
    barrier.dstAccessMask = write_only
        ? VK_ACCESS_SHADER_WRITE_BIT
        : (VK_ACCESS_SHADER_READ_BIT | VK_ACCESS_SHADER_WRITE_BIT);
    barrier.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
    barrier.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
    barrier.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
    barrier.subresourceRange.baseMipLevel = mip_level;
    barrier.subresourceRange.levelCount = 1;
    barrier.subresourceRange.baseArrayLayer = 0;
    barrier.subresourceRange.layerCount = 1;
    vkCmdPipelineBarrier(vk->cmd_buffers[vk->current_frame],
        VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT | VK_PIPELINE_STAGE_COMPUTE_SHADER_BIT,
        VK_PIPELINE_STAGE_COMPUTE_SHADER_BIT,
        0, 0, NULL, 0, NULL, 1, &barrier);
    if (mip_level < VK_MAX_MIP_VIEWS)
        td->mip_layout[mip_level] = VK_IMAGE_LAYOUT_GENERAL;

    /* Bind a STORAGE_IMAGE descriptor referencing a per-mip image
     * view (cached on the texture).  This requires the currently bound
     * pipeline to declare a storage_image_layout set, which is true for
     * every compute pipeline created through this backend. */
    VKPipelineData *cpd = vk->current_pipeline_data;
    if (!cpd || cpd->storage_image_set == (u8)VK_INVALID_SET) return;
    if (mip_level >= VK_MAX_MIP_VIEWS) return;

    if (td->mip_views[mip_level] == VK_NULL_HANDLE) {
        VkImageViewCreateInfo vci = {0};
        vci.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
        vci.image = td->image;
        vci.viewType = VK_IMAGE_VIEW_TYPE_2D;
        vci.format = td->format;
        vci.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
        vci.subresourceRange.baseMipLevel = mip_level;
        vci.subresourceRange.levelCount = 1;
        vci.subresourceRange.baseArrayLayer = 0;
        vci.subresourceRange.layerCount = 1;
        if (vkCreateImageView(vk->device, &vci, NULL, &td->mip_views[mip_level]) != VK_SUCCESS)
            return;
    }

    VkDescriptorSetLayout layout = vk->storage_image_layout;
    VkDescriptorSetAllocateInfo dsai = {0};
    dsai.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
    dsai.descriptorPool = vk->desc_pools[vk->current_frame];
    dsai.descriptorSetCount = 1;
    dsai.pSetLayouts = &layout;

    VkDescriptorSet ds;
    if (vkAllocateDescriptorSets(vk->device, &dsai, &ds) != VK_SUCCESS) return;

    VkDescriptorImageInfo img_info = {0};
    img_info.sampler = VK_NULL_HANDLE;
    img_info.imageView = td->mip_views[mip_level];
    img_info.imageLayout = VK_IMAGE_LAYOUT_GENERAL;

    u32 binding = (unit < 4) ? unit : 0;
    VkWriteDescriptorSet write = {0};
    write.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
    write.dstSet = ds;
    write.dstBinding = binding;
    write.descriptorCount = 1;
    write.descriptorType = VK_DESCRIPTOR_TYPE_STORAGE_IMAGE;
    write.pImageInfo = &img_info;

    vkUpdateDescriptorSets(vk->device, 1, &write, 0, NULL);
    VkPipelineBindPoint bp = cpd->is_compute ?
        VK_PIPELINE_BIND_POINT_COMPUTE : VK_PIPELINE_BIND_POINT_GRAPHICS;
    vkCmdBindDescriptorSets(vk->cmd_buffers[vk->current_frame],
        bp, cpd->layout,
        cpd->storage_image_set, 1, &ds, 0, NULL);
}

void rhi_cmd_bind_image_cubemap_face(RHICmdBuffer *cmd, RHICubemap cm, u32 face, u32 mip, u32 unit, bool write_only) {
    (void)cmd;
    VKBackend *vk = vk_backend(g_current_device);
    VKCubemapData *cd = (VKCubemapData *)rhi_get_resource(g_current_device, cm);
    if (!cd || face >= 6u) return;
    if (mip >= cd->mip_levels || mip >= VK_MAX_MIP_VIEWS) return;
    vk_suspend_pass_for_compute(vk);

    VKPipelineData *cpd = vk->current_pipeline_data;
    if (!cpd || cpd->storage_image_set == (u8)VK_INVALID_SET) return;

    /* Transition the target face+mip to GENERAL layout for compute write. */
    VkImageMemoryBarrier barrier = {0};
    barrier.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
    barrier.image = cd->image;
    barrier.oldLayout = write_only ? VK_IMAGE_LAYOUT_UNDEFINED : VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
    barrier.newLayout = VK_IMAGE_LAYOUT_GENERAL;
    barrier.srcAccessMask = write_only ? 0 : VK_ACCESS_SHADER_READ_BIT;
    barrier.dstAccessMask = write_only ? VK_ACCESS_SHADER_WRITE_BIT
                                        : (VK_ACCESS_SHADER_READ_BIT | VK_ACCESS_SHADER_WRITE_BIT);
    barrier.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
    barrier.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
    barrier.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
    barrier.subresourceRange.baseMipLevel = mip;
    barrier.subresourceRange.levelCount = 1;
    barrier.subresourceRange.baseArrayLayer = face;
    barrier.subresourceRange.layerCount = 1;
    vkCmdPipelineBarrier(vk->cmd_buffers[vk->current_frame],
        VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT | VK_PIPELINE_STAGE_COMPUTE_SHADER_BIT,
        VK_PIPELINE_STAGE_COMPUTE_SHADER_BIT,
        0, 0, NULL, 0, NULL, 1, &barrier);

    /* Lazily create per-face, per-mip storage image view. */
    if (cd->face_views[face][mip] == VK_NULL_HANDLE) {
        VkImageViewCreateInfo vci = {0};
        vci.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
        vci.image = cd->image;
        vci.viewType = VK_IMAGE_VIEW_TYPE_2D;
        vci.format = cd->format;
        vci.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
        vci.subresourceRange.baseMipLevel = mip;
        vci.subresourceRange.levelCount = 1;
        vci.subresourceRange.baseArrayLayer = face;
        vci.subresourceRange.layerCount = 1;
        if (vkCreateImageView(vk->device, &vci, NULL, &cd->face_views[face][mip]) != VK_SUCCESS)
            return;
    }

    VkDescriptorSetLayout layout = vk->storage_image_layout;
    VkDescriptorSetAllocateInfo dsai = {0};
    dsai.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
    dsai.descriptorPool = vk->desc_pools[vk->current_frame];
    dsai.descriptorSetCount = 1;
    dsai.pSetLayouts = &layout;

    VkDescriptorSet ds;
    if (vkAllocateDescriptorSets(vk->device, &dsai, &ds) != VK_SUCCESS) return;

    VkDescriptorImageInfo img_info = {0};
    img_info.sampler = VK_NULL_HANDLE;
    img_info.imageView = cd->face_views[face][mip];
    img_info.imageLayout = VK_IMAGE_LAYOUT_GENERAL;

    u32 binding = (unit < 4) ? unit : 0;
    VkWriteDescriptorSet write = {0};
    write.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
    write.dstSet = ds;
    write.dstBinding = binding;
    write.descriptorCount = 1;
    write.descriptorType = VK_DESCRIPTOR_TYPE_STORAGE_IMAGE;
    write.pImageInfo = &img_info;

    vkUpdateDescriptorSets(vk->device, 1, &write, 0, NULL);
    VkPipelineBindPoint bp = cpd->is_compute ?
        VK_PIPELINE_BIND_POINT_COMPUTE : VK_PIPELINE_BIND_POINT_GRAPHICS;
    vkCmdBindDescriptorSets(vk->cmd_buffers[vk->current_frame],
        bp, cpd->layout,
        cpd->storage_image_set, 1, &ds, 0, NULL);
}

void rhi_cmd_bind_cubemap_sampler(RHICmdBuffer *cmd, RHICubemap cm, RHISampler sampler, u32 unit) {
    (void)cmd;
    VKBackend *vk = vk_backend(g_current_device);
    VKCubemapData *cd = (VKCubemapData *)rhi_get_resource(g_current_device, cm);
    VKSamplerData *sd = (VKSamplerData *)rhi_get_resource(g_current_device, sampler);
    if (!cd || !sd || !vk->current_pipeline_data) return;

    VKPipelineData *cpd = vk->current_pipeline_data;
    if (cpd->sampler_mip_set == (u8)VK_INVALID_SET) return;

    VkDescriptorSetLayout layout = vk->sampler_mip_layout;
    VkDescriptorSetAllocateInfo dsai = {0};
    dsai.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
    dsai.descriptorPool = vk->desc_pools[vk->current_frame];
    dsai.descriptorSetCount = 1;
    dsai.pSetLayouts = &layout;

    VkDescriptorSet ds;
    if (vkAllocateDescriptorSets(vk->device, &dsai, &ds) != VK_SUCCESS) return;

    VkDescriptorImageInfo img_info = {0};
    img_info.sampler = sd->sampler;
    img_info.imageView = cd->view;
    img_info.imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;

    u32 binding = (unit < 4) ? unit : 0;
    VkWriteDescriptorSet write = {0};
    write.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
    write.dstSet = ds;
    write.dstBinding = binding;
    write.descriptorCount = 1;
    write.descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
    write.pImageInfo = &img_info;

    vkUpdateDescriptorSets(vk->device, 1, &write, 0, NULL);
    VkPipelineBindPoint bp = cpd->is_compute ?
        VK_PIPELINE_BIND_POINT_COMPUTE : VK_PIPELINE_BIND_POINT_GRAPHICS;
    vkCmdBindDescriptorSets(vk->cmd_buffers[vk->current_frame],
        bp, cpd->layout,
        cpd->sampler_mip_set, 1, &ds, 0, NULL);
}

void rhi_cmd_bind_texture_mip(RHICmdBuffer *cmd, RHITexture tex, RHISampler sampler, u32 unit, u32 mip_level) {
    (void)cmd;
    VKBackend *vk = vk_backend(g_current_device);
    VKTextureData *td = (VKTextureData *)rhi_get_resource(g_current_device, tex);
    if (!td || td->image == VK_NULL_HANDLE) return;
    vk_suspend_pass_for_compute(vk);

    /* Ensure the source mip is in SHADER_READ_ONLY_OPTIMAL layout before
     * a sampler reads it. R172: honor tracked mip_layout. */
    VkImageLayout old_layout = (mip_level < VK_MAX_MIP_VIEWS)
        ? td->mip_layout[mip_level] : VK_IMAGE_LAYOUT_GENERAL;
    if (old_layout != VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL) {
        VkImageMemoryBarrier barrier = {0};
        barrier.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
        barrier.image = td->image;
        barrier.oldLayout = (old_layout == VK_IMAGE_LAYOUT_UNDEFINED)
            ? VK_IMAGE_LAYOUT_GENERAL : old_layout;
        barrier.newLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
        barrier.srcAccessMask = VK_ACCESS_SHADER_WRITE_BIT | VK_ACCESS_SHADER_READ_BIT;
        barrier.dstAccessMask = VK_ACCESS_SHADER_READ_BIT;
        barrier.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
        barrier.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
        barrier.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
        barrier.subresourceRange.baseMipLevel = mip_level;
        barrier.subresourceRange.levelCount = 1;
        barrier.subresourceRange.baseArrayLayer = 0;
        barrier.subresourceRange.layerCount = 1;
        vkCmdPipelineBarrier(vk->cmd_buffers[vk->current_frame],
            VK_PIPELINE_STAGE_COMPUTE_SHADER_BIT,
            VK_PIPELINE_STAGE_COMPUTE_SHADER_BIT | VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT,
            0, 0, NULL, 0, NULL, 1, &barrier);
        if (mip_level < VK_MAX_MIP_VIEWS)
            td->mip_layout[mip_level] = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
    }

    /* Bind a COMBINED_IMAGE_SAMPLER referencing a per-mip image view. */
    VKPipelineData *cpd = vk->current_pipeline_data;
    if (!cpd || cpd->sampler_mip_set == (u8)VK_INVALID_SET) return;
    if (mip_level >= VK_MAX_MIP_VIEWS) return;

    VKSamplerData *sd = (VKSamplerData *)rhi_get_resource(g_current_device, sampler);
    if (!sd) return;

    if (td->mip_views[mip_level] == VK_NULL_HANDLE) {
        VkImageViewCreateInfo vci = {0};
        vci.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
        vci.image = td->image;
        vci.viewType = VK_IMAGE_VIEW_TYPE_2D;
        vci.format = td->format;
        vci.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
        vci.subresourceRange.baseMipLevel = mip_level;
        vci.subresourceRange.levelCount = 1;
        vci.subresourceRange.baseArrayLayer = 0;
        vci.subresourceRange.layerCount = 1;
        if (vkCreateImageView(vk->device, &vci, NULL, &td->mip_views[mip_level]) != VK_SUCCESS)
            return;
    }

    VkDescriptorSetLayout layout = vk->sampler_mip_layout;
    VkDescriptorSetAllocateInfo dsai = {0};
    dsai.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
    dsai.descriptorPool = vk->desc_pools[vk->current_frame];
    dsai.descriptorSetCount = 1;
    dsai.pSetLayouts = &layout;

    VkDescriptorSet ds;
    if (vkAllocateDescriptorSets(vk->device, &dsai, &ds) != VK_SUCCESS) return;

    VkDescriptorImageInfo img_info = {0};
    img_info.sampler = sd->sampler;
    img_info.imageView = td->mip_views[mip_level];
    img_info.imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;

    u32 binding = (unit < 4) ? unit : 0;
    VkWriteDescriptorSet write = {0};
    write.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
    write.dstSet = ds;
    write.dstBinding = binding;
    write.descriptorCount = 1;
    write.descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
    write.pImageInfo = &img_info;

    vkUpdateDescriptorSets(vk->device, 1, &write, 0, NULL);
    VkPipelineBindPoint bp = cpd->is_compute ?
        VK_PIPELINE_BIND_POINT_COMPUTE : VK_PIPELINE_BIND_POINT_GRAPHICS;
    vkCmdBindDescriptorSets(vk->cmd_buffers[vk->current_frame],
        bp, cpd->layout,
        cpd->sampler_mip_set, 1, &ds, 0, NULL);
}

void rhi_cmd_bind_texture_compute(RHICmdBuffer *cmd, RHITexture tex, RHISampler sampler, u32 unit) {
    (void)cmd;
    VKBackend *vk = vk_backend(g_current_device);
    VKTextureData *td = (VKTextureData *)rhi_get_resource(g_current_device, tex);
    if (!td || td->image == VK_NULL_HANDLE) return;
    VKPipelineData *cpd = vk->current_pipeline_data;
    if (!cpd || cpd->sampler_mip_set == (u8)VK_INVALID_SET) return;
    VKSamplerData *sd = (VKSamplerData *)rhi_get_resource(g_current_device, sampler);
    if (!sd) return;

    /* R179: Full-view sampling requires every mip in READ_ONLY — Hi-Z writes
     * leave mips GENERAL until explicitly transitioned. */
    vk_suspend_pass_for_compute(vk);
    for (u32 m = 0; m < td->mip_levels && m < VK_MAX_MIP_VIEWS; m++) {
        VkImageLayout old_layout = td->mip_layout[m];
        if (old_layout == VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL) continue;
        if (old_layout == VK_IMAGE_LAYOUT_UNDEFINED)
            old_layout = VK_IMAGE_LAYOUT_GENERAL;
        VkImageMemoryBarrier barrier = {0};
        barrier.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
        barrier.image = td->image;
        barrier.oldLayout = old_layout;
        barrier.newLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
        barrier.srcAccessMask = VK_ACCESS_SHADER_WRITE_BIT | VK_ACCESS_SHADER_READ_BIT;
        barrier.dstAccessMask = VK_ACCESS_SHADER_READ_BIT;
        barrier.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
        barrier.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
        barrier.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
        barrier.subresourceRange.baseMipLevel = m;
        barrier.subresourceRange.levelCount = 1;
        barrier.subresourceRange.layerCount = 1;
        vkCmdPipelineBarrier(vk->cmd_buffers[vk->current_frame],
            VK_PIPELINE_STAGE_COMPUTE_SHADER_BIT | VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT,
            VK_PIPELINE_STAGE_COMPUTE_SHADER_BIT,
            0, 0, NULL, 0, NULL, 1, &barrier);
        td->mip_layout[m] = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
    }

    VkDescriptorSetLayout layout = vk->sampler_mip_layout;
    VkDescriptorSetAllocateInfo dsai = {0};
    dsai.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
    dsai.descriptorPool = vk->desc_pools[vk->current_frame];
    dsai.descriptorSetCount = 1;
    dsai.pSetLayouts = &layout;

    VkDescriptorSet ds;
    if (vkAllocateDescriptorSets(vk->device, &dsai, &ds) != VK_SUCCESS) return;

    VkDescriptorImageInfo img_info = {0};
    img_info.sampler = sd->sampler;
    img_info.imageView = td->view;
    img_info.imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;

    u32 binding = (unit < 4) ? unit : 0;
    VkWriteDescriptorSet write = {0};
    write.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
    write.dstSet = ds;
    write.dstBinding = binding;
    write.descriptorCount = 1;
    write.descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
    write.pImageInfo = &img_info;

    vkUpdateDescriptorSets(vk->device, 1, &write, 0, NULL);
    VkPipelineBindPoint bp = cpd->is_compute ?
        VK_PIPELINE_BIND_POINT_COMPUTE : VK_PIPELINE_BIND_POINT_GRAPHICS;
    vkCmdBindDescriptorSets(vk->cmd_buffers[vk->current_frame],
        bp, cpd->layout,
        cpd->sampler_mip_set, 1, &ds, 0, NULL);
}

void rhi_cmd_transition_depth_to_read(RHICmdBuffer *cmd, RHITexture depth_tex) {
    (void)cmd;
    VKBackend *vk = vk_backend(g_current_device);
    VKTextureData *td = (VKTextureData *)rhi_get_resource(g_current_device, depth_tex);
    if (!td) return;
    /* Idempotent: if the depth is already shader-readable, nothing to do.  This
     * lets callers re-issue the transition after a post-fx pass (tonemap /
     * cinematic) re-bound the owning FBO and reverted the depth to the attachment
     * layout, without tripping an oldLayout mismatch when it was never reverted. */
    if (td->cur_layout == VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL) return;
    /* The depth being read is the active pass's depth attachment; end the pass
     * (its attachments are STOREd) before transitioning + sampling it. */
    vk_suspend_pass_for_compute(vk);

    VkImageLayout old_layout = (td->cur_layout == VK_IMAGE_LAYOUT_UNDEFINED)
        ? VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL : td->cur_layout;
    VkImageMemoryBarrier barrier = {0};
    barrier.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
    barrier.image = td->image;
    barrier.oldLayout = old_layout;
    barrier.newLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
    barrier.srcAccessMask = VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT;
    barrier.dstAccessMask = VK_ACCESS_SHADER_READ_BIT;
    barrier.subresourceRange.aspectMask = VK_IMAGE_ASPECT_DEPTH_BIT;
    barrier.subresourceRange.levelCount = 1;
    barrier.subresourceRange.layerCount = 1;
    /* R180: Hi-Z compute samples depth immediately after this transition;
     * FRAGMENT-only dst left compute unsynchronized. */
    vkCmdPipelineBarrier(vk->cmd_buffers[vk->current_frame],
        VK_PIPELINE_STAGE_LATE_FRAGMENT_TESTS_BIT,
        VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT | VK_PIPELINE_STAGE_COMPUTE_SHADER_BIT,
        0, 0, NULL, 0, NULL, 1, &barrier);
    td->cur_layout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
}

void rhi_cmd_clear_color(RHICmdBuffer *cmd, f32 r, f32 g, f32 b, f32 a) {
    (void)cmd;
    VKBackend *vk = vk_backend(g_current_device);
    vk_resume_pass_if_needed(vk);
    VkClearAttachment att = {0};
    att.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
    att.clearValue.color.float32[0] = r;
    att.clearValue.color.float32[1] = g;
    att.clearValue.color.float32[2] = b;
    att.clearValue.color.float32[3] = a;
    /* Clear rect must stay within the *current* render area (which may be an
     * offscreen/half-res FBO), not the swapchain. resume_extent tracks the
     * active pass's extent (set at every begin-render-pass site). */
    VkExtent2D area = (vk->resume_extent.width && vk->resume_extent.height)
                    ? vk->resume_extent : vk->swap_extent;
    VkClearRect rect = {{{0, 0}, area}, 0, 1};
    vkCmdClearAttachments(vk->cmd_buffers[vk->current_frame], 1, &att, 1, &rect);
}

/* R94-3: Flush pending push constants to the command buffer. Called before
 * every draw/dispatch to batch multiple rhi_cmd_set_uniform_* calls into
 * a single vkCmdPushConstants. */
static void vk_flush_push_constants(VKBackend *vk) {
    if (!vk->push_dirty || !vk->current_pipeline_data) return;
    /* R96-1: Clamp dirty range to the pipeline's push constant range.
     * Compute pipelines declare 128 bytes; graphics declare 256. */
    u32 max_pc = vk->current_pipeline_data->is_compute ? 128 : 256;
    if (vk->push_dirty_max > max_pc) vk->push_dirty_max = max_pc;
    if (vk->push_dirty_min >= vk->push_dirty_max) { vk->push_dirty = false; return; }
    VkShaderStageFlags stages = VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_FRAGMENT_BIT;
    if (vk->current_pipeline_data->is_compute) stages = VK_SHADER_STAGE_COMPUTE_BIT;
    vkCmdPushConstants(vk->cmd_buffers[vk->current_frame], vk->current_pipeline_data->layout,
        stages, vk->push_dirty_min, vk->push_dirty_max - vk->push_dirty_min,
        vk->push_staging + vk->push_dirty_min);
    vk->push_dirty = false;
    vk->push_dirty_min = 256;
    vk->push_dirty_max = 0;
}

#define VK_PUSH_MARK(vk, offset, size) do { \
    if ((u32)(offset) < (vk)->push_dirty_min) (vk)->push_dirty_min = (u32)(offset); \
    if ((u32)(offset) + (u32)(size) > (vk)->push_dirty_max) (vk)->push_dirty_max = (u32)(offset) + (u32)(size); \
} while(0)

/* Push constants map to rhi_cmd_set_uniform_*. Location is used as byte offset. */
void rhi_cmd_set_uniform_mat4(RHICmdBuffer *cmd, i32 location, const f32 *m) {
    (void)cmd;
    VKBackend *vk = vk_backend(g_current_device);
    if (!vk->current_pipeline_data) return;
    if (location < 0 || (u32)location + 64 > 256) return;  /* R146: bounds check push_staging[256] */
    memcpy(vk->push_staging + location, m, 64);  /* R94-3: stage, flush at draw */
    VK_PUSH_MARK(vk, location, 64);
    vk->push_dirty = true;
}

void rhi_cmd_set_uniform_vec3(RHICmdBuffer *cmd, i32 location, f32 x, f32 y, f32 z) {
    (void)cmd;
    VKBackend *vk = vk_backend(g_current_device);
    if (!vk->current_pipeline_data) return;
    if (location < 0 || (u32)location + 12 > 256) return;  /* R146: bounds check push_staging[256] */
    f32 v[3] = {x, y, z};
    memcpy(vk->push_staging + location, v, 12);  /* R94-3: stage, flush at draw */
    VK_PUSH_MARK(vk, location, 12);
    vk->push_dirty = true;
}

void rhi_cmd_set_uniform_vec2(RHICmdBuffer *cmd, i32 location, f32 x, f32 y) {
    (void)cmd;
    VKBackend *vk = vk_backend(g_current_device);
    if (!vk->current_pipeline_data) return;
    if (location < 0 || (u32)location + 8 > 256) return;  /* R146: bounds check push_staging[256] */
    f32 v[2] = {x, y};
    memcpy(vk->push_staging + location, v, 8);  /* R94-3: stage, flush at draw */
    VK_PUSH_MARK(vk, location, 8);
    vk->push_dirty = true;
}

void rhi_cmd_set_uniform_vec4(RHICmdBuffer *cmd, i32 location, f32 x, f32 y, f32 z, f32 w) {
    (void)cmd;
    VKBackend *vk = vk_backend(g_current_device);
    if (!vk->current_pipeline_data) return;
    if (location < 0 || (u32)location + 16 > 256) return;  /* R146: bounds check push_staging[256] */
    f32 v[4] = {x, y, z, w};
    memcpy(vk->push_staging + location, v, 16);  /* R94-3: stage, flush at draw */
    VK_PUSH_MARK(vk, location, 16);
    vk->push_dirty = true;
}

void rhi_cmd_set_uniform_f32(RHICmdBuffer *cmd, i32 location, f32 v) {
    (void)cmd;
    VKBackend *vk = vk_backend(g_current_device);
    if (!vk->current_pipeline_data) return;
    if (location < 0 || (u32)location + 4 > 256) return;  /* R146: bounds check push_staging[256] */
    memcpy(vk->push_staging + location, &v, 4);  /* R94-3: stage, flush at draw */
    VK_PUSH_MARK(vk, location, 4);
    vk->push_dirty = true;
}

/* R179: Upload an arbitrary push-constant range in one mark (avoids mat4 64B truncation). */
void rhi_cmd_set_uniform_bytes(RHICmdBuffer *cmd, i32 location, const void *data, u32 size) {
    (void)cmd;
    if (!data || size == 0u) return;
    VKBackend *vk = vk_backend(g_current_device);
    if (!vk->current_pipeline_data) return;
    if (location < 0 || (u32)location + size > 256u) return;
    memcpy(vk->push_staging + location, data, size);
    VK_PUSH_MARK(vk, location, size);
    vk->push_dirty = true;
}

void rhi_cmd_set_uniform_i32(RHICmdBuffer *cmd, i32 location, i32 v) {
    (void)cmd;
    VKBackend *vk = vk_backend(g_current_device);
    if (!vk->current_pipeline_data) return;
    if (location < 0 || (u32)location + 4 > 256) return;  /* R146: bounds check push_staging[256] */
    memcpy(vk->push_staging + location, &v, 4);  /* R94-3: stage, flush at draw */
    VK_PUSH_MARK(vk, location, 4);
    vk->push_dirty = true;
}

i32 rhi_pipeline_get_uniform_location(RHIDevice *dev, RHIPipeline pipe, const char *name) {
    (void)dev;
    VKPipelineData *pd = (VKPipelineData *)rhi_get_resource(dev, pipe);
    bool clustered = pd && pd->uses_texel_buffer && !pd->is_instanced;
    bool non_clustered_tbo = pd && pd->uses_texel_buffer && pd->is_instanced;

    /* Terrain: model is identity (dropped). Push block (<=256B):
     *   u_view@0 u_proj@64 u_light_vp@128
     *   u_light_dir@192 u_shadow_bias@204  (packed vec4)
     *   u_light_color@208 u_water_y@220    (packed vec4)
     *   u_ambient@224 u_time@236           (packed vec4)
     *   u_camera_pos@240                   (vec4) */
    if (pd && pd->terrain_layout) {
        if (strcmp(name, "u_view") == 0)        return 0;
        if (strcmp(name, "u_proj") == 0)        return 64;
        if (strcmp(name, "u_light_vp") == 0)    return 128;
        if (strcmp(name, "u_light_dir") == 0)   return 192;
        if (strcmp(name, "u_shadow_bias") == 0) return 204;
        if (strcmp(name, "u_light_color") == 0) return 208;
        if (strcmp(name, "u_water_y") == 0)     return 220;
        if (strcmp(name, "u_ambient") == 0)     return 224;
        if (strcmp(name, "u_time") == 0)        return 236;
        if (strcmp(name, "u_camera_pos") == 0)  return 240;
        return -1; /* u_model, u_albedo (sampler) not push constants */
    }
    /* Water: no model. Push block (<=256B):
     *   u_view@0 u_proj@64 u_light_vp@128
     *   u_camera_pos@192 u_time@204    (packed vec4)
     *   u_water_color@208 u_shadow_bias@220 (packed vec4)
     *   u_water_y@224                  (vec4) */
    if (pd && pd->water_layout) {
        if (strcmp(name, "u_view") == 0)         return 0;
        if (strcmp(name, "u_proj") == 0)         return 64;
        if (strcmp(name, "u_light_vp") == 0)     return 128;
        if (strcmp(name, "u_camera_pos") == 0)   return 192;
        if (strcmp(name, "u_time") == 0)         return 204;
        if (strcmp(name, "u_water_color") == 0)  return 208;
        if (strcmp(name, "u_shadow_bias") == 0)  return 220;
        if (strcmp(name, "u_water_y") == 0)      return 224;
        return -1;
    }
    /* Combined TAA+FXAA (combined_taa_fxaa_vk.frag). Push block (<=256B):
     *   u_taa_curr_vp@0 u_taa_prev_vp@64 u_taa_inv_proj@128
     *   u_screen_w@192 u_screen_h@196 u_taa_blend@200
     *   u_taa_first_frame@204 u_fxaa_threshold@208 u_taa_use_velocity@212 */
    if (pd && pd->combined_aa_layout) {
        if (strcmp(name, "u_taa_curr_vp") == 0)     return 0;
        if (strcmp(name, "u_taa_prev_vp") == 0)     return 64;
        if (strcmp(name, "u_taa_inv_proj") == 0)    return 128;
        if (strcmp(name, "u_screen_w") == 0)        return 192;
        if (strcmp(name, "u_screen_h") == 0)        return 196;
        if (strcmp(name, "u_taa_blend") == 0)       return 200;
        if (strcmp(name, "u_taa_first_frame") == 0) return 204;
        if (strcmp(name, "u_fxaa_threshold") == 0)  return 208;
        if (strcmp(name, "u_taa_use_velocity") == 0) return 212;
        return -1; /* samplers (curr/hist/depth/velocity) are not push constants */
    }
    /* Combined tonemap+colorgrade+cinematic (combined_color_vk.frag):
     *   u_tm_exposure@0 u_tm_gamma@4 u_tm_mode@8
     *   u_cg_saturation@12 u_cg_contrast@16 u_cg_brightness@20
     *   u_cg_temperature@24 u_cg_tint@28
     *   u_cine_aberration@32 u_cine_vignette@36 u_cine_grain@40 u_cine_time@44
     *   u_screen_w@48 u_screen_h@52 */
    if (pd && pd->combined_color_layout) {
        if (strcmp(name, "u_tm_exposure") == 0)    return 0;
        if (strcmp(name, "u_tm_gamma") == 0)       return 4;
        if (strcmp(name, "u_tm_mode") == 0)        return 8;
        if (strcmp(name, "u_cg_saturation") == 0)  return 12;
        if (strcmp(name, "u_cg_contrast") == 0)    return 16;
        if (strcmp(name, "u_cg_brightness") == 0)  return 20;
        if (strcmp(name, "u_cg_temperature") == 0) return 24;
        if (strcmp(name, "u_cg_tint") == 0)        return 28;
        if (strcmp(name, "u_cine_aberration") == 0) return 32;
        if (strcmp(name, "u_cine_vignette") == 0)  return 36;
        if (strcmp(name, "u_cine_grain") == 0)     return 40;
        if (strcmp(name, "u_cine_time") == 0)      return 44;
        if (strcmp(name, "u_screen_w") == 0)       return 48;
        if (strcmp(name, "u_screen_h") == 0)       return 52;
        return -1;
    }

    if (non_clustered_tbo) {
        if (strcmp(name, "u_view") == 0)        return 0;
        if (strcmp(name, "u_proj") == 0)        return 64;
        if (strcmp(name, "u_light_dir") == 0)   return 128;
        if (strcmp(name, "u_light_color") == 0) return 144;
        if (strcmp(name, "u_ambient") == 0)     return 160;
        if (strcmp(name, "u_camera_pos") == 0)  return 176;
        return -1;
    }
    if (pd && pd->is_compute) {
        if (strcmp(name, "push.dt") == 0)           return 0;
        if (strcmp(name, "push.view") == 0)         return 0;
        if (strcmp(name, "push.proj") == 0)         return 64;
        /* IBL compute shaders (irradiance & prefilter share push layout):
         *   u_roughness@0  u_face@4  u_face_size/u_mip_size@8 */
        if (strcmp(name, "u_roughness") == 0)       return 0;
        if (strcmp(name, "u_face") == 0)            return 4;
        if (strcmp(name, "u_face_size") == 0)       return 8;
        if (strcmp(name, "u_mip_size") == 0)        return 8;
        /* sky_to_cube.comp: shares u_face@4 / u_face_size@8 above, plus the
         * sun vectors at aligned offsets 16 and 32. */
        if (strcmp(name, "u_sun_dir") == 0)         return 16;
        if (strcmp(name, "u_sun_color") == 0)       return 32;
        /* cluster_cull.comp: mat4 vp@0, vec4 params0@64, vec4 params1@80. */
        if (strcmp(name, "u_cc_vp") == 0)           return 0;
        if (strcmp(name, "u_cc_params0") == 0)      return 64;
        if (strcmp(name, "u_cc_params1") == 0)      return 80;
        /* GPU culling (cull.comp / unified_cull.comp): mat4 vp@0, uint count@64 */
        if (strcmp(name, "u_cull_vp") == 0)         return 0;
        if (strcmp(name, "u_cull_count") == 0)      return 64;
        if (strcmp(name, "u_cull_hi_z_width") == 0)  return 68;
        if (strcmp(name, "u_cull_hi_z_height") == 0) return 72;
        if (strcmp(name, "u_cull_use_hi_z") == 0)    return 76;
        if (strcmp(name, "u_cull_write_draws") == 0) return 80;
        /* Occlusion culling (occlusion_cull.comp): mat4 view_proj@0, uint object_count@64, float hi_z_width@68, float hi_z_height@72 */
        if (strcmp(name, "pc_view_proj") == 0)       return 0;
        if (strcmp(name, "pc_object_count") == 0)    return 64;
        if (strcmp(name, "pc_hi_z_width") == 0)      return 68;
        if (strcmp(name, "pc_hi_z_height") == 0)     return 72;
        /* Hi-Z generation (hi_z_generate.comp): vec2 output_size@0 */
        if (strcmp(name, "pc_output_size") == 0)     return 0;
        /* Draw compaction (compact_draws.comp): uint total_draws@0 */
        if (strcmp(name, "total_draws") == 0)       return 0;
        return -1;
    }
    if (pd && pd->uses_storage) {
        if (strcmp(name, "push.view") == 0)         return 0;
        if (strcmp(name, "push.proj") == 0)         return 64;
        return -1;
    }
    if (strcmp(name, "u_prev_vp") == 0)       return 192;
    if (strcmp(name, "u_model") == 0)       return 0;
    if (strcmp(name, "u_view") == 0)        return 64;
    /* The clustered fragment shader drops the unused u_proj slot and reuses the
     * freed 64 bytes for camera/ambient/fog/shadow params (see clustered map). */
    if (strcmp(name, "u_proj") == 0)        return clustered ? -1 : 128;
    if (strcmp(name, "u_light_vp") == 0)    return 64;
    if (strcmp(name, "u_vol_inv_proj") == 0)     return 0;
    if (strcmp(name, "u_vol_view") == 0)         return 64;
    if (strcmp(name, "u_vol_ldx") == 0)          return 128;
    if (strcmp(name, "u_vol_ldy") == 0)          return 132;
    if (strcmp(name, "u_vol_ldz") == 0)          return 136;
    if (strcmp(name, "u_vol_lcx") == 0)          return 140;
    if (strcmp(name, "u_vol_lcy") == 0)          return 144;
    if (strcmp(name, "u_vol_lcz") == 0)          return 148;
    if (strcmp(name, "u_vol_density") == 0)      return 152;
    if (strcmp(name, "u_vol_fog_r") == 0)        return 156;
    if (strcmp(name, "u_vol_fog_g") == 0)        return 160;
    if (strcmp(name, "u_vol_fog_b") == 0)        return 164;
    if (strcmp(name, "u_vol_sw") == 0)           return 168;
    if (strcmp(name, "u_vol_sh") == 0)           return 172;
    if (strcmp(name, "u_lf_light_x") == 0)          return 0;
    if (strcmp(name, "u_lf_light_y") == 0)          return 4;
    if (strcmp(name, "u_lf_intensity") == 0)        return 8;
    if (strcmp(name, "u_lf_sw") == 0)               return 12;
    if (strcmp(name, "u_lf_sh") == 0)               return 16;
    if (strcmp(name, "u_lf_lc_r") == 0)             return 20;
    if (strcmp(name, "u_lf_lc_g") == 0)             return 24;
    if (strcmp(name, "u_lf_lc_b") == 0)             return 28;
    if (strcmp(name, "u_sun_dir") == 0)              return 128;
    if (strcmp(name, "u_sun_color") == 0)            return 144;
    if (strcmp(name, "u_ssgi_inv_proj") == 0)       return 0;
    if (strcmp(name, "u_ssgi_proj") == 0)           return 64;
    if (strcmp(name, "u_ssgi_radius") == 0)         return 128;
    if (strcmp(name, "u_ssgi_intensity") == 0)      return 132;
    if (strcmp(name, "u_ssgi_sw") == 0)             return 136;
    if (strcmp(name, "u_ssgi_sh") == 0)             return 140;
    if (strcmp(name, "u_fxaa_sw") == 0)            return 0;
    if (strcmp(name, "u_fxaa_sh") == 0)            return 4;
    if (strcmp(name, "u_tm_exposure") == 0)       return 0;
    if (strcmp(name, "u_tm_gamma") == 0)           return 4;
    if (strcmp(name, "u_tm_aberration") == 0)      return 8;
    if (strcmp(name, "u_tm_vignette") == 0)        return 12;
    if (strcmp(name, "u_tm_grain") == 0)            return 16;
    if (strcmp(name, "u_tm_time") == 0)             return 20;
    if (strcmp(name, "u_tm_screen_w") == 0)         return 24;
    if (strcmp(name, "u_tm_screen_h") == 0)         return 28;
    if (strcmp(name, "u_tm_saturation") == 0)       return 32;
    if (strcmp(name, "u_tm_contrast") == 0)         return 36;
    if (strcmp(name, "u_tm_brightness") == 0)       return 40;
    if (strcmp(name, "u_tm_temperature") == 0)      return 44;
    if (strcmp(name, "u_tm_tint") == 0)             return 48;
    if (strcmp(name, "u_cine_aberration") == 0)    return 0;
    if (strcmp(name, "u_cine_vignette") == 0)    return 4;
    if (strcmp(name, "u_cine_grain") == 0)       return 8;
    if (strcmp(name, "u_cine_time") == 0)        return 12;
    if (strcmp(name, "u_cine_sw") == 0)          return 16;
    if (strcmp(name, "u_cine_sh") == 0)          return 20;
    if (strcmp(name, "u_dof_focus") == 0)       return 0;
    if (strcmp(name, "u_dof_range") == 0)       return 4;
    if (strcmp(name, "u_dof_near") == 0)        return 8;
    if (strcmp(name, "u_dof_far") == 0)         return 12;
    if (strcmp(name, "u_dof_sw") == 0)          return 16;
    if (strcmp(name, "u_dof_sh") == 0)          return 20;
    if (strcmp(name, "u_ssr_proj") == 0)        return 0;
    if (strcmp(name, "u_ssr_inv_proj") == 0)    return 64;
    if (strcmp(name, "u_ssr_view") == 0)        return 128;
    if (strcmp(name, "u_ssr_sw") == 0)          return 192;
    if (strcmp(name, "u_ssr_sh") == 0)          return 196;
    if (strcmp(name, "u_ssr_max_steps") == 0)   return 200;
    if (strcmp(name, "u_ssr_stride") == 0)      return 204;
    if (strcmp(name, "u_ssr_thickness") == 0)   return 208;
    if (strcmp(name, "u_taa_curr_vp") == 0)     return 0;
    if (strcmp(name, "u_taa_prev_vp") == 0)     return 64;
    if (strcmp(name, "u_taa_inv_proj") == 0)    return 128;
    if (strcmp(name, "u_taa_sw") == 0)          return 192;
    if (strcmp(name, "u_taa_sh") == 0)          return 196;
    if (strcmp(name, "u_taa_blend") == 0)       return 200;
    if (strcmp(name, "u_taa_first_frame") == 0) return 204;
    if (strcmp(name, "u_taa_use_velocity") == 0) return 208;
    if (strcmp(name, "u_ssao_proj") == 0)       return 0;
    if (strcmp(name, "u_ssao_inv_proj") == 0)   return 64;
    if (strcmp(name, "u_ssao_sw") == 0)         return 128;
    if (strcmp(name, "u_ssao_sh") == 0)         return 132;
    if (strcmp(name, "u_ssao_radius") == 0)     return 136;
    if (strcmp(name, "u_ssao_bias") == 0)       return 140;
    /* Debug visualization overlay (debug_viz_vk.frag). */
    if (strcmp(name, "u_dv_mode") == 0)         return 0;
    if (strcmp(name, "u_dv_near") == 0)         return 4;
    if (strcmp(name, "u_dv_far") == 0)          return 8;
    if (strcmp(name, "u_dv_split0") == 0)       return 12;
    if (strcmp(name, "u_dv_split1") == 0)       return 16;
    if (strcmp(name, "u_dv_split2") == 0)       return 20;
    if (strcmp(name, "u_dv_split3") == 0)       return 24;
    /* Lens effects (lens_effects_vk.frag): chromatic aberration + vignette + grain. */
    if (strcmp(name, "u_ca_strength") == 0)        return 0;
    if (strcmp(name, "u_vignette_strength") == 0)  return 4;
    if (strcmp(name, "u_vignette_softness") == 0)  return 8;
    if (strcmp(name, "u_grain_strength") == 0)     return 12;
    /* Sharpen (sharpen_vk.frag): CAS-style strength + screen size. */
    if (strcmp(name, "u_sharp_strength") == 0)     return 0;
    if (strcmp(name, "u_sharp_sw") == 0)           return 4;
    if (strcmp(name, "u_sharp_sh") == 0)           return 8;
    /* Upscale TSR (upscale_vk.frag). R197-A: locations were missing — all loc_*
     * returned -1 so push constants never reached the shader. */
    if (strcmp(name, "u_ups_rw") == 0)             return 0;
    if (strcmp(name, "u_ups_rh") == 0)             return 4;
    if (strcmp(name, "u_ups_dw") == 0)             return 8;
    if (strcmp(name, "u_ups_dh") == 0)             return 12;
    if (strcmp(name, "u_ups_sharp") == 0)          return 16;
    if (strcmp(name, "u_ups_copy_only") == 0)      return 20;
    if (strcmp(name, "u_ups_inv_proj") == 0)       return 32;
    if (strcmp(name, "u_ups_prev_vp") == 0)        return 96;
    if (strcmp(name, "u_view") == 0)        return 64;
    if (strcmp(name, "u_proj") == 0)        return 128;
    if (clustered) {
        /* Layout matches pbr_clustered_vk.frag's push block (u_proj removed). */
        if (strcmp(name, "u_camera_pos") == 0)  return 128;
        if (strcmp(name, "u_fog_near") == 0)    return 140;
        if (strcmp(name, "u_ambient") == 0)     return 144;
        if (strcmp(name, "u_fog_far") == 0)     return 156;
        if (strcmp(name, "u_screen_w") == 0)    return 160;
        if (strcmp(name, "u_screen_h") == 0)    return 164;
        if (strcmp(name, "u_near") == 0)        return 168;
        if (strcmp(name, "u_far") == 0)         return 172;
        if (strcmp(name, "u_point_count") == 0) return 176;
        if (strcmp(name, "u_dir_count") == 0)   return 180;
        if (strcmp(name, "u_shadow_bias") == 0) return 184;
        if (strcmp(name, "u_fog_color") == 0)   return 192;
        if (strcmp(name, "u_underwater") == 0)  return 204;
        if (strcmp(name, "u_point_shadow_far_planes") == 0) return 208;
        if (strcmp(name, "u_pom_enabled") == 0) return 224;
    } else if (pd && pd->no_vertex_input && pd->uses_texel_buffer && !pd->is_compute) {
        /* deferred_light_vk: clustered lighting + IBL full-screen pass. */
        if (strcmp(name, "u_inv_vp") == 0)       return 0;
        if (strcmp(name, "u_view") == 0)         return 64;
        if (strcmp(name, "u_camera_pos") == 0)   return 128;
        if (strcmp(name, "u_screen_w") == 0)      return 144;
        if (strcmp(name, "u_screen_h") == 0)      return 148;
        if (strcmp(name, "u_near") == 0)          return 160;
        if (strcmp(name, "u_far") == 0)           return 164;
        if (strcmp(name, "u_shadow_bias") == 0)   return 168;
        if (strcmp(name, "u_point_count") == 0)   return 176;
        if (strcmp(name, "u_dir_count") == 0)     return 180;
        if (strcmp(name, "u_point_shadow_far_planes") == 0) return 184;
    } else if (pd && pd->no_vertex_input && !pd->uses_texel_buffer && !pd->is_compute) {
        /* Other full-screen post passes (tonemap, fxaa, etc.). */
        if (strcmp(name, "u_inv_vp") == 0)     return 0;
        if (strcmp(name, "u_camera_pos") == 0) return 64;
        if (strcmp(name, "u_screen_w") == 0)    return 80;
        if (strcmp(name, "u_screen_h") == 0)    return 84;
    } else {
        if (strcmp(name, "u_light_dir") == 0)   return 192;
        if (strcmp(name, "u_light_color") == 0) return 208;
        if (strcmp(name, "u_ambient") == 0)     return 224;
        if (strcmp(name, "u_camera_pos") == 0)  return 240;
    }
    if (strcmp(name, "u_albedo") == 0)      return -1;
    if (strcmp(name, "u_inv_proj") == 0)    return 0;
    if (strcmp(name, "u_curr_vp") == 0)     return 64;
    if (strcmp(name, "u_prev_vp") == 0)     return 128;
    return -1;
}

void rhi_cmd_bind_material_textures(RHICmdBuffer *cmd,
    RHITexture albedo, RHITexture mr, RHITexture normal, RHITexture emissive,
    RHITexture shadow, RHITexture ssao, RHISampler sampler) {
    (void)cmd;
    VKBackend *vk = vk_backend(g_current_device);
    if (!vk->current_pipeline_data) return;

    VKTextureData *td_alb = (VKTextureData *)rhi_get_resource(g_current_device, albedo);
    VKTextureData *td_mr  = (VKTextureData *)rhi_get_resource(g_current_device, mr);
    VKTextureData *td_nrm = (VKTextureData *)rhi_get_resource(g_current_device, normal);
    VKTextureData *td_em  = (VKTextureData *)rhi_get_resource(g_current_device, emissive);
    VKTextureData *td_ssao = (VKTextureData *)rhi_get_resource(g_current_device, ssao);
    VKTextureData *td_shadow = (VKTextureData *)rhi_get_resource(g_current_device, shadow);
    VKSamplerData *sd     = (VKSamplerData *)rhi_get_resource(g_current_device, sampler);
    if (!sd) return;

    VkDescriptorSetAllocateInfo dsai = {0};
    dsai.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
    dsai.descriptorPool = vk->desc_pools[vk->current_frame];
    dsai.descriptorSetCount = 1;
    dsai.pSetLayouts = &vk->desc_layout;

    VkDescriptorSet ds;
    if (vkAllocateDescriptorSets(vk->device, &dsai, &ds) != VK_SUCCESS) return;

    VkImageView alb_view = td_alb ? td_alb->view : VK_NULL_HANDLE;
    /* Prefer the explicitly-passed shadow texture (e.g. CSM atlas); fall back to
     * the legacy global binding, then albedo to keep the descriptor complete. */
    VkImageView shadow_view = td_shadow ? td_shadow->view
                            : (vk->shadow_tex_view ? vk->shadow_tex_view : alb_view);
    VkImageView views[9];
    views[0] = alb_view;
    views[1] = shadow_view;
    views[2] = td_mr  ? td_mr->view  : alb_view;
    views[3] = td_nrm ? td_nrm->view : alb_view;
    views[4] = td_em  ? td_em->view  : alb_view;
    views[5] = td_ssao ? td_ssao->view : alb_view;
    /* IBL slots (6-8): use fallback alb_view when no IBL textures bound */
    views[6] = alb_view;
    views[7] = alb_view;
    views[8] = alb_view;

    VkDescriptorImageInfo img_infos[9];
    memset(img_infos, 0, sizeof(img_infos));

    /* R99-1: Split into 3 writes — binding 5 has descriptorCount=4 when
     * feat_partially_bound, so a single descriptorCount=9 write would fill
     * binding 5's array elements 1-3 instead of bindings 6-8. */
    for (int i = 0; i < 9; i++) {
        img_infos[i].sampler = sd->sampler;
        img_infos[i].imageView = views[i];
        img_infos[i].imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
    }

    VkWriteDescriptorSet writes[3];
    memset(writes, 0, sizeof(writes));
    /* Bindings 0-4: albedo, shadow, mr, normal, emissive */
    writes[0].sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
    writes[0].dstSet = ds;
    writes[0].dstBinding = 0;
    writes[0].descriptorCount = 5;
    writes[0].descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
    writes[0].pImageInfo = &img_infos[0];
    /* Binding 5: ssao (element 0 only; array size is 4 when partially bound) */
    writes[1].sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
    writes[1].dstSet = ds;
    writes[1].dstBinding = 5;
    writes[1].descriptorCount = 1;
    writes[1].descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
    writes[1].pImageInfo = &img_infos[5];
    /* Bindings 6-8: brdf_lut, irradiance, prefilter */
    writes[2].sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
    writes[2].dstSet = ds;
    writes[2].dstBinding = 6;
    writes[2].descriptorCount = 3;
    writes[2].descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
    writes[2].pImageInfo = &img_infos[6];

    vkUpdateDescriptorSets(vk->device, 3, writes, 0, NULL);
    vkCmdBindDescriptorSets(vk->cmd_buffers[vk->current_frame],
        VK_PIPELINE_BIND_POINT_GRAPHICS, vk->current_pipeline_data->layout,
        0, 1, &ds, 0, NULL);
}

void rhi_cmd_bind_material_textures_ibl(RHICmdBuffer *cmd,
    RHITexture albedo, RHITexture mr, RHITexture normal, RHITexture emissive,
    RHITexture shadow, RHITexture ssao, RHISampler sampler,
    RHITexture brdf_lut, RHICubemap irradiance_map, RHICubemap prefilter_map,
    const RHITexture *point_shadow_cubes, u32 point_shadow_count) {
    (void)cmd;
    VKBackend *vk = vk_backend(g_current_device);
    if (!vk->current_pipeline_data) return;

    VKTextureData *td_alb = (VKTextureData *)rhi_get_resource(g_current_device, albedo);
    VKTextureData *td_mr  = (VKTextureData *)rhi_get_resource(g_current_device, mr);
    VKTextureData *td_nrm = (VKTextureData *)rhi_get_resource(g_current_device, normal);
    VKTextureData *td_em  = (VKTextureData *)rhi_get_resource(g_current_device, emissive);
    VKTextureData *td_ssao = (VKTextureData *)rhi_get_resource(g_current_device, ssao);
    VKTextureData *td_shadow = (VKTextureData *)rhi_get_resource(g_current_device, shadow);
    VKTextureData *td_brdf = (VKTextureData *)rhi_get_resource(g_current_device, brdf_lut);
    VKCubemapData *cd_irr  = (VKCubemapData *)rhi_get_resource(g_current_device, irradiance_map);
    VKCubemapData *cd_pref = (VKCubemapData *)rhi_get_resource(g_current_device, prefilter_map);
    VKSamplerData *sd     = (VKSamplerData *)rhi_get_resource(g_current_device, sampler);
    if (!sd) return;

    VkDescriptorSetAllocateInfo dsai = {0};
    dsai.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
    dsai.descriptorPool = vk->desc_pools[vk->current_frame];
    dsai.descriptorSetCount = 1;
    dsai.pSetLayouts = &vk->desc_layout;

    VkDescriptorSet ds;
    if (vkAllocateDescriptorSets(vk->device, &dsai, &ds) != VK_SUCCESS) return;

    VkImageView alb_view = td_alb ? td_alb->view : VK_NULL_HANDLE;
    VkImageView shadow_view = td_shadow ? td_shadow->view
                            : (vk->shadow_tex_view ? vk->shadow_tex_view : alb_view);

    bool use_pt_shadow = point_shadow_cubes && point_shadow_count > 0u;
    u32 pt_n = use_pt_shadow ? point_shadow_count : 0u;
    if (pt_n > 4u) pt_n = 4u;
    /* Forward draws bind SSAO at unit 5; deferred lighting reuses binding 5 for
     * cubemaps (ssao handle is null). Forward point shadows use binding 10. */
    bool pt_shadow_at_bind5 = use_pt_shadow && !rhi_handle_valid(ssao);

    VkDescriptorImageInfo bind5_infos[4];
    memset(bind5_infos, 0, sizeof(bind5_infos));
    for (u32 i = 0u; i < 4u; i++) {
        VkImageView v = alb_view;
        if (pt_shadow_at_bind5 && i < pt_n) {
            VKTextureData *td = (VKTextureData *)rhi_get_resource(g_current_device, point_shadow_cubes[i]);
            if (td && td->view != VK_NULL_HANDLE) v = td->view;
        } else if (!pt_shadow_at_bind5 && i == 0u) {
            v = td_ssao ? td_ssao->view : alb_view;
        }
        bind5_infos[i].sampler = sd->sampler;
        bind5_infos[i].imageView = v;
        bind5_infos[i].imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
    }

    VkDescriptorImageInfo bind10_infos[4];
    memset(bind10_infos, 0, sizeof(bind10_infos));
    for (u32 i = 0u; i < 4u; i++) {
        VkImageView v = alb_view;
        if (use_pt_shadow && !pt_shadow_at_bind5 && i < pt_n) {
            VKTextureData *td = (VKTextureData *)rhi_get_resource(g_current_device, point_shadow_cubes[i]);
            if (td && td->view != VK_NULL_HANDLE) v = td->view;
        }
        bind10_infos[i].sampler = sd->sampler;
        bind10_infos[i].imageView = v;
        bind10_infos[i].imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
    }

    VkDescriptorImageInfo img_infos[10];
    memset(img_infos, 0, sizeof(img_infos));

    img_infos[0].sampler = sd->sampler;
    img_infos[0].imageView = alb_view;
    img_infos[0].imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
    img_infos[1].sampler = sd->sampler;
    img_infos[1].imageView = shadow_view;
    img_infos[1].imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
    img_infos[2].sampler = sd->sampler;
    img_infos[2].imageView = td_mr ? td_mr->view : alb_view;
    img_infos[2].imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
    img_infos[3].sampler = sd->sampler;
    img_infos[3].imageView = td_nrm ? td_nrm->view : alb_view;
    img_infos[3].imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
    img_infos[4].sampler = sd->sampler;
    img_infos[4].imageView = td_em ? td_em->view : alb_view;
    img_infos[4].imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
    img_infos[6].sampler = sd->sampler;
    img_infos[6].imageView = td_brdf ? td_brdf->view : alb_view;
    img_infos[6].imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
    img_infos[7].sampler = sd->sampler;
    img_infos[7].imageView = cd_irr ? cd_irr->view : alb_view;
    img_infos[7].imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
    img_infos[8].sampler = sd->sampler;
    img_infos[8].imageView = cd_pref ? cd_pref->view : alb_view;
    img_infos[8].imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;

    /* R97-3: Batch descriptor writes — 4 consecutive-group writes instead of 10
     * individual writes. Bindings 0-4, 5, 6-8, 10 are grouped by consecutiveness. */
    u32 pt_shadow_n = vk->feat_partially_bound ? 4 : 1;
    VkWriteDescriptorSet writes[4];
    memset(writes, 0, sizeof(writes));

    /* Bindings 0-4: albedo, shadow, mr, normal, emissive */
    writes[0].sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
    writes[0].dstSet = ds;
    writes[0].dstBinding = 0;
    writes[0].descriptorCount = 5;
    writes[0].descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
    writes[0].pImageInfo = &img_infos[0];

    /* Binding 5: ssao or point_shadow_cubes[4] */
    writes[1].sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
    writes[1].dstSet = ds;
    writes[1].dstBinding = 5;
    writes[1].descriptorCount = pt_shadow_n;
    writes[1].descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
    writes[1].pImageInfo = bind5_infos;

    /* Bindings 6-8: brdf_lut, irradiance, prefilter */
    writes[2].sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
    writes[2].dstSet = ds;
    writes[2].dstBinding = 6;
    writes[2].descriptorCount = 3;
    writes[2].descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
    writes[2].pImageInfo = &img_infos[6];

    /* Binding 10: point_shadow_cubes[4] (forward path) */
    writes[3].sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
    writes[3].dstSet = ds;
    writes[3].dstBinding = 10;
    writes[3].descriptorCount = pt_shadow_n;
    writes[3].descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
    writes[3].pImageInfo = bind10_infos;

    vkUpdateDescriptorSets(vk->device, 4, writes, 0, NULL);
    vkCmdBindDescriptorSets(vk->cmd_buffers[vk->current_frame],
        VK_PIPELINE_BIND_POINT_GRAPHICS, vk->current_pipeline_data->layout,
        0, 1, &ds, 0, NULL);
}

void rhi_cmd_bind_textures_multi(RHICmdBuffer *cmd,
    RHITexture *textures, int count, RHISampler sampler) {
    (void)cmd;
    VKBackend *vk = vk_backend(g_current_device);
    if (!vk->current_pipeline_data || count <= 0 || count > 6) return;

    VKSamplerData *sd = (VKSamplerData *)rhi_get_resource(g_current_device, sampler);
    if (!sd) return;

    VkDescriptorSetAllocateInfo dsai = {0};
    dsai.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
    dsai.descriptorPool = vk->desc_pools[vk->current_frame];
    dsai.descriptorSetCount = 1;
    dsai.pSetLayouts = &vk->desc_layout;

    VkDescriptorSet ds;
    if (vkAllocateDescriptorSets(vk->device, &dsai, &ds) != VK_SUCCESS) return;

    VkDescriptorImageInfo img_infos[6];
    memset(img_infos, 0, sizeof(img_infos));

    /* R97-4: Single vkUpdateDescriptorSets write with descriptorCount=count
     * for consecutive bindings 0..count-1, instead of count separate writes. */
    for (int i = 0; i < count; i++) {
        VKTextureData *td = (VKTextureData *)rhi_get_resource(g_current_device, textures[i]);
        img_infos[i].sampler = sd->sampler;
        img_infos[i].imageView = td ? td->view : VK_NULL_HANDLE;
        img_infos[i].imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
    }

    VkWriteDescriptorSet write = {0};
    write.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
    write.dstSet = ds;
    write.dstBinding = 0;
    write.descriptorCount = (u32)count;
    write.descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
    write.pImageInfo = img_infos;

    vkUpdateDescriptorSets(vk->device, 1, &write, 0, NULL);
    vkCmdBindDescriptorSets(vk->cmd_buffers[vk->current_frame],
        VK_PIPELINE_BIND_POINT_GRAPHICS, vk->current_pipeline_data->layout,
        0, 1, &ds, 0, NULL);
}

void rhi_cmd_bind_texture(RHICmdBuffer *cmd, RHITexture tex, RHISampler sampler, u32 unit) {
    rhi_cmd_bind_material_textures(cmd, tex, tex, tex, tex, tex, tex, sampler);
    (void)unit;
}

void rhi_cmd_bind_shadow_texture(RHICmdBuffer *cmd, RHITexture shadow_tex, RHISampler sampler) {
    (void)cmd; (void)sampler;
    VKBackend *vk = vk_backend(g_current_device);
    VKTextureData *td = (VKTextureData *)rhi_get_resource(g_current_device, shadow_tex);
    vk->shadow_tex_view = td ? td->view : VK_NULL_HANDLE;
}

void rhi_cmd_bind_uniform_buffer(RHICmdBuffer *cmd, RHIBuffer buf, u32 binding) {
    (void)cmd;
    VKBackend *vk = vk_backend(g_current_device);
    VKPipelineData *cpd = vk->current_pipeline_data;
    if (!cpd || cpd->ubo_set == (u8)VK_INVALID_SET) return;

    VKBufferData *bd = (VKBufferData *)rhi_get_resource(g_current_device, buf);
    if (!bd || bd->buffer == VK_NULL_HANDLE) return;

    VkDescriptorSetLayout layout = vk->ubo_layout;
    VkDescriptorSetAllocateInfo dsai = {0};
    dsai.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
    dsai.descriptorPool = vk->desc_pools[vk->current_frame];
    dsai.descriptorSetCount = 1;
    dsai.pSetLayouts = &layout;

    VkDescriptorSet ds;
    if (vkAllocateDescriptorSets(vk->device, &dsai, &ds) != VK_SUCCESS) return;

    VkDescriptorBufferInfo buf_info = {0};
    buf_info.buffer = bd->buffer;
    buf_info.offset = 0;
    buf_info.range = VK_WHOLE_SIZE;

    u32 dst_binding = (binding < 4) ? binding : 0;
    VkWriteDescriptorSet write = {0};
    write.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
    write.dstSet = ds;
    write.dstBinding = dst_binding;
    write.descriptorCount = 1;
    write.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
    write.pBufferInfo = &buf_info;

    vkUpdateDescriptorSets(vk->device, 1, &write, 0, NULL);
    VkPipelineBindPoint bp = cpd->is_compute ?
        VK_PIPELINE_BIND_POINT_COMPUTE : VK_PIPELINE_BIND_POINT_GRAPHICS;
    vkCmdBindDescriptorSets(vk->cmd_buffers[vk->current_frame],
        bp, cpd->layout,
        cpd->ubo_set, 1, &ds, 0, NULL);
}

/* ---- Shadow map ---- */

typedef struct {
    VkImage        depth_image;
    VkDeviceMemory depth_memory;
    VkImageView    depth_view;
    VkFramebuffer  framebuffer;
    VkRenderPass   render_pass;
    VkRenderPass   render_pass_load;  /* LOAD-op twin for compute suspend/resume */
} VKShadowData;

RHIShadowMap rhi_shadow_map_create(RHIDevice *dev, u32 width, u32 height) {
    VKBackend *vk = vk_backend(dev);
    RHIShadowMap sm = {0};
    sm.width = width;
    sm.height = height;

    VKShadowData *sd = calloc(1, sizeof(VKShadowData));
    if (!sd) return sm;

    VkImageCreateInfo ci = {0};
    ci.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
    ci.imageType = VK_IMAGE_TYPE_2D;
    ci.format = VK_FORMAT_D32_SFLOAT;
    ci.extent.width = width;
    ci.extent.height = height;
    ci.extent.depth = 1;
    ci.mipLevels = 1;
    ci.arrayLayers = 1;
    ci.samples = VK_SAMPLE_COUNT_1_BIT;
    ci.tiling = VK_IMAGE_TILING_OPTIMAL;
    ci.usage = VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT | VK_IMAGE_USAGE_SAMPLED_BIT;
    ci.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
    ci.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
    if (vkCreateImage(vk->device, &ci, NULL, &sd->depth_image) != VK_SUCCESS) {
        LOG_FATAL("VK: failed to create shadow image");
        free(sd);
        return sm;
    }

    VkMemoryRequirements mr;
    vkGetImageMemoryRequirements(vk->device, sd->depth_image, &mr);
    VkMemoryAllocateInfo ai = {0};
    ai.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
    ai.allocationSize = mr.size;
    ai.memoryTypeIndex = vk_find_memory(vk, mr.memoryTypeBits, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);
    if (vkAllocateMemory(vk->device, &ai, NULL, &sd->depth_memory) != VK_SUCCESS) {
        LOG_FATAL("VK: failed to allocate shadow memory");
        vkDestroyImage(vk->device, sd->depth_image, NULL);
        free(sd);
        return sm;
    }
    if (vkBindImageMemory(vk->device, sd->depth_image, sd->depth_memory, 0) != VK_SUCCESS) {
        LOG_FATAL("VK: failed to bind shadow image memory");
        vkFreeMemory(vk->device, sd->depth_memory, NULL);
        vkDestroyImage(vk->device, sd->depth_image, NULL);
        free(sd);
        return sm;
    }

    VkImageViewCreateInfo ivci = {0};
    ivci.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
    ivci.image = sd->depth_image;
    ivci.viewType = VK_IMAGE_VIEW_TYPE_2D;
    ivci.format = VK_FORMAT_D32_SFLOAT;
    ivci.subresourceRange.aspectMask = VK_IMAGE_ASPECT_DEPTH_BIT;
    ivci.subresourceRange.levelCount = 1;
    ivci.subresourceRange.layerCount = 1;
    if (vkCreateImageView(vk->device, &ivci, NULL, &sd->depth_view) != VK_SUCCESS) {
        LOG_FATAL("VK: failed to create shadow image view");
        vkFreeMemory(vk->device, sd->depth_memory, NULL);
        vkDestroyImage(vk->device, sd->depth_image, NULL);
        free(sd);
        return sm;
    }

    VkAttachmentDescription depth_att = {0};
    depth_att.format = VK_FORMAT_D32_SFLOAT;
    depth_att.samples = VK_SAMPLE_COUNT_1_BIT;
    depth_att.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
    depth_att.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
    depth_att.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
    depth_att.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
    depth_att.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
    depth_att.finalLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;

    VkAttachmentReference depth_ref = {0, VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL};
    VkSubpassDescription sp = {0};
    sp.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
    sp.pDepthStencilAttachment = &depth_ref;

    VkSubpassDependency dep = {0};
    dep.srcSubpass = VK_SUBPASS_EXTERNAL;
    dep.dstSubpass = 0;
    dep.srcStageMask = VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT;
    dep.dstStageMask = VK_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT;
    dep.dstAccessMask = VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT;

    VkRenderPassCreateInfo rpci = {0};
    rpci.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
    rpci.attachmentCount = 1;
    rpci.pAttachments = &depth_att;
    rpci.subpassCount = 1;
    rpci.pSubpasses = &sp;
    rpci.dependencyCount = 1;
    rpci.pDependencies = &dep;
    if (vkCreateRenderPass(vk->device, &rpci, NULL, &sd->render_pass) != VK_SUCCESS) {
        LOG_FATAL("VK: failed to create shadow render pass");
        vkDestroyImageView(vk->device, sd->depth_view, NULL);
        vkFreeMemory(vk->device, sd->depth_memory, NULL);
        vkDestroyImage(vk->device, sd->depth_image, NULL);
        free(sd);
        return sm;
    }
    sd->render_pass_load = vk_make_resume_render_pass(vk, &rpci);

    VkFramebufferCreateInfo fbci = {0};
    fbci.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
    fbci.renderPass = sd->render_pass;
    fbci.attachmentCount = 1;
    fbci.pAttachments = &sd->depth_view;
    fbci.width = width;
    fbci.height = height;
    fbci.layers = 1;
    if (vkCreateFramebuffer(vk->device, &fbci, NULL, &sd->framebuffer) != VK_SUCCESS) {
        LOG_FATAL("VK: failed to create shadow framebuffer");
        if (sd->render_pass_load) vkDestroyRenderPass(vk->device, sd->render_pass_load, NULL);
        vkDestroyRenderPass(vk->device, sd->render_pass, NULL);
        vkDestroyImageView(vk->device, sd->depth_view, NULL);
        vkFreeMemory(vk->device, sd->depth_memory, NULL);
        vkDestroyImage(vk->device, sd->depth_image, NULL);
        free(sd);
        return sm;
    }

    if (vk->shadow_render_pass == VK_NULL_HANDLE) {
        vk->shadow_render_pass = sd->render_pass;
    }

    VKTextureData *td = calloc(1, sizeof(VKTextureData));
    if (!td) return sm;
    u32 tidx = rhi_alloc_slot(dev);
    td->image = sd->depth_image;
    td->view = sd->depth_view;
    td->memory = sd->depth_memory;
    td->width = width;
    td->height = height;
    dev->slots[tidx].ptr = td;
    dev->slots[tidx].type = RHI_RES_TEXTURE;
    sm.depth_tex = rhi_make_handle(tidx, dev->slots[tidx].generation);

    u32 fidx = rhi_alloc_slot(dev);
    dev->slots[fidx].ptr = sd;
    dev->slots[fidx].type = RHI_RES_FRAMEBUFFER;
    sm.fbo = rhi_make_handle(fidx, dev->slots[fidx].generation);

    return sm;
}

void rhi_shadow_map_destroy(RHIDevice *dev, RHIShadowMap *sm) {
    if (!dev || !sm) return;
    VKBackend *vk = vk_backend(dev);
    VKShadowData *sd = rhi_get_resource(dev, sm->fbo);
    if (!sd) return;
    if (vkDeviceWaitIdle(vk->device) != VK_SUCCESS)
        LOG_WARN("VK: vkDeviceWaitIdle failed in shadow_map_destroy");
    vkDestroyFramebuffer(vk->device, sd->framebuffer, NULL);
    vkDestroyRenderPass(vk->device, sd->render_pass, NULL);
    if (sd->render_pass_load) vkDestroyRenderPass(vk->device, sd->render_pass_load, NULL);
    vkDestroyImageView(vk->device, sd->depth_view, NULL);
    vkDestroyImage(vk->device, sd->depth_image, NULL);
    vkFreeMemory(vk->device, sd->depth_memory, NULL);
    free(sd);
    rhi_free_slot(dev, sm->fbo);
    rhi_free_slot(dev, sm->depth_tex);
    sm->fbo = RHI_HANDLE_NULL;
    sm->depth_tex = RHI_HANDLE_NULL;
}

void rhi_cmd_bind_shadow_map(RHICmdBuffer *cmd, RHIShadowMap *sm) {
    (void)cmd;
    if (!sm) return;
    VKBackend *vk = vk_backend(g_current_device);
    VKShadowData *sd = rhi_get_resource(g_current_device, sm->fbo);
    if (!sd) return;

    if (vk->render_pass_active) {
        vkCmdEndRenderPass(vk->cmd_buffers[vk->current_frame]);
        vk->render_pass_active = false; /* R181: match offscreen_fbo_bind */
    }
    vk->pass_suspended = false;

    VkRenderPassBeginInfo rpi = {0};
    rpi.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
    rpi.renderPass = sd->render_pass;
    rpi.framebuffer = sd->framebuffer;
    rpi.renderArea.extent.width = sm->width;
    rpi.renderArea.extent.height = sm->height;
    VkClearValue clear;
    memset(&clear, 0, sizeof(clear));
    clear.depthStencil.depth = 1.0f;
    rpi.clearValueCount = 1;
    rpi.pClearValues = &clear;
    vkCmdBeginRenderPass(vk->cmd_buffers[vk->current_frame], &rpi, VK_SUBPASS_CONTENTS_INLINE);
    vk->render_pass_active = true;
    vk_record_pass(vk, sd->render_pass_load, sd->framebuffer, sm->width, sm->height, VK_FORMAT_UNDEFINED);

    VkViewport vp = {0, 0, (f32)sm->width, (f32)sm->height, 0, 1};
    vkCmdSetViewport(vk->cmd_buffers[vk->current_frame], 0, 1, &vp);
    VkRect2D sc = {{0, 0}, {sm->width, sm->height}};
    vkCmdSetScissor(vk->cmd_buffers[vk->current_frame], 0, 1, &sc);
    vk->vp_valid = false; vk->sc_valid = false;  /* R95-2: invalidate cache */
}

void rhi_cmd_unbind_shadow_map(RHICmdBuffer *cmd, u32 screen_w, u32 screen_h) {
    (void)cmd;
    VKBackend *vk = vk_backend(g_current_device);

    if (vk->render_pass_active) {
        vkCmdEndRenderPass(vk->cmd_buffers[vk->current_frame]);
        vk->render_pass_active = false; /* R181: close state before early-return */
    }
    vk->pass_suspended = false;
    if (!vk->framebuffers) return;  /* R150: guard against NULL framebuffers */

    VkRenderPassBeginInfo rpi = {0};
    rpi.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
    rpi.renderPass = vk->render_pass;
    rpi.framebuffer = vk->framebuffers[vk->image_index];
    rpi.renderArea.extent.width = screen_w;
    rpi.renderArea.extent.height = screen_h;
    VkClearValue clears[2];
    memset(clears, 0, sizeof(clears));
    clears[0].color.float32[0] = 0.2f;
    clears[0].color.float32[1] = 0.25f;
    clears[0].color.float32[2] = 0.35f;
    clears[0].color.float32[3] = 1.0f;
    clears[1].depthStencil.depth = 1.0f;
    rpi.clearValueCount = 2;
    rpi.pClearValues = clears;
    vkCmdBeginRenderPass(vk->cmd_buffers[vk->current_frame], &rpi, VK_SUBPASS_CONTENTS_INLINE);
    vk->render_pass_active = true;
    vk_record_pass(vk, vk->render_pass_load, vk->framebuffers[vk->image_index],
                   screen_w, screen_h, vk->swap_format);

    VkViewport vp = {0, 0, (f32)screen_w, (f32)screen_h, 0, 1};
    vkCmdSetViewport(vk->cmd_buffers[vk->current_frame], 0, 1, &vp);
    VkRect2D sc = {{0, 0}, {screen_w, screen_h}};
    vkCmdSetScissor(vk->cmd_buffers[vk->current_frame], 0, 1, &sc);
    vk->vp_valid = false; vk->sc_valid = false;  /* R95-2: invalidate cache */
    vk->current_pipeline = VK_NULL_HANDLE;
}

void rhi_cmd_clear_depth(RHICmdBuffer *cmd) {
    (void)cmd;
    VKBackend *vk = vk_backend(g_current_device);
    vk_resume_pass_if_needed(vk);
    VkClearAttachment att = {0};
    att.aspectMask = VK_IMAGE_ASPECT_DEPTH_BIT;
    att.clearValue.depthStencil.depth = 1.0f;
    VkExtent2D area = (vk->resume_extent.width && vk->resume_extent.height)
                    ? vk->resume_extent : vk->swap_extent;
    VkClearRect rect = {{{0, 0}, area}, 0, 1};
    vkCmdClearAttachments(vk->cmd_buffers[vk->current_frame], 1, &att, 1, &rect);
}

/* ---- Cubemap ---- */

RHICubemap rhi_cubemap_create(RHIDevice *dev, const RHICubemapDesc *desc) {
    VKBackend *vk = vk_backend(dev);

    VKCubemapData *cd = calloc(1, sizeof(VKCubemapData));
    if (!cd) return RHI_HANDLE_NULL;

    VkFormat fmt = vk_format_from_rhi(desc->format);
    u32 mips = desc->mip_levels ? desc->mip_levels : 1u;
    if (mips > VK_MAX_MIP_VIEWS) mips = VK_MAX_MIP_VIEWS;
    cd->format = fmt;
    cd->mip_levels = mips;

    VkImageCreateInfo ci = {0};
    ci.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
    ci.imageType = VK_IMAGE_TYPE_2D;
    ci.format = fmt;
    ci.extent.width = desc->size;
    ci.extent.height = desc->size;
    ci.extent.depth = 1;
    ci.mipLevels = mips;
    ci.arrayLayers = 6;
    ci.samples = VK_SAMPLE_COUNT_1_BIT;
    ci.tiling = VK_IMAGE_TILING_OPTIMAL;
    ci.usage = VK_IMAGE_USAGE_SAMPLED_BIT | VK_IMAGE_USAGE_TRANSFER_DST_BIT | VK_IMAGE_USAGE_STORAGE_BIT;
    ci.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
    ci.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
    ci.flags = VK_IMAGE_CREATE_CUBE_COMPATIBLE_BIT;
    if (vkCreateImage(vk->device, &ci, NULL, &cd->image) != VK_SUCCESS) {
        LOG_FATAL("VK: failed to create cubemap image");
        free(cd);
        return RHI_HANDLE_NULL;
    }

    VkMemoryRequirements mr;
    vkGetImageMemoryRequirements(vk->device, cd->image, &mr);
    VkMemoryAllocateInfo ai = {0};
    ai.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
    ai.allocationSize = mr.size;
    ai.memoryTypeIndex = vk_find_memory(vk, mr.memoryTypeBits, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);
    if (vkAllocateMemory(vk->device, &ai, NULL, &cd->memory) != VK_SUCCESS) {
        LOG_FATAL("VK: failed to allocate cubemap memory");
        vkDestroyImage(vk->device, cd->image, NULL);
        free(cd);
        return RHI_HANDLE_NULL;
    }
    if (vkBindImageMemory(vk->device, cd->image, cd->memory, 0) != VK_SUCCESS) {
        LOG_FATAL("VK: failed to bind cubemap image memory");
        vkFreeMemory(vk->device, cd->memory, NULL);
        vkDestroyImage(vk->device, cd->image, NULL);
        free(cd);
        return RHI_HANDLE_NULL;
    }

    VkImageViewCreateInfo ivci = {0};
    ivci.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
    ivci.image = cd->image;
    ivci.viewType = VK_IMAGE_VIEW_TYPE_CUBE;
    ivci.format = fmt;
    ivci.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
    ivci.subresourceRange.levelCount = mips;
    ivci.subresourceRange.layerCount = 6;
    if (vkCreateImageView(vk->device, &ivci, NULL, &cd->view) != VK_SUCCESS) {
        LOG_FATAL("VK: failed to create cubemap image view");
        vkFreeMemory(vk->device, cd->memory, NULL);
        vkDestroyImage(vk->device, cd->image, NULL);
        free(cd);
        return RHI_HANDLE_NULL;
    }

    /* Transition all 6 faces UNDEFINED -> SHADER_READ on a one-time-submit
     * command buffer. Cubemaps are created during init (before any frame's
     * vkBeginCommandBuffer), so the frame command buffer must NOT be used here. */
    {
        VkCommandBufferAllocateInfo cbai = {0};
        cbai.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
        cbai.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
        cbai.commandPool = vk->cmd_pool;
        cbai.commandBufferCount = 1;
        VkCommandBuffer tmp_cb;
        if (vkAllocateCommandBuffers(vk->device, &cbai, &tmp_cb) != VK_SUCCESS) {
            LOG_FATAL("VK: failed to allocate cubemap layout command buffer");
            vkDestroyImageView(vk->device, cd->view, NULL);
            vkDestroyImage(vk->device, cd->image, NULL);
            vkFreeMemory(vk->device, cd->memory, NULL);
            free(cd);
            return RHI_HANDLE_NULL;
        }
        VkCommandBufferBeginInfo cbi = {0};
        cbi.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
        cbi.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;
        if (vkBeginCommandBuffer(tmp_cb, &cbi) != VK_SUCCESS) {
            LOG_FATAL("VK: failed to begin cubemap layout command buffer");
            vkFreeCommandBuffers(vk->device, vk->cmd_pool, 1, &tmp_cb);
            vkDestroyImageView(vk->device, cd->view, NULL);
            vkDestroyImage(vk->device, cd->image, NULL);
            vkFreeMemory(vk->device, cd->memory, NULL);
            free(cd);
            return RHI_HANDLE_NULL;
        }

        VkImageMemoryBarrier barrier = {0};
        barrier.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
        barrier.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
        barrier.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
        barrier.image = cd->image;
        barrier.oldLayout = VK_IMAGE_LAYOUT_UNDEFINED;
        barrier.newLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
        barrier.srcAccessMask = 0;
        barrier.dstAccessMask = VK_ACCESS_SHADER_READ_BIT;
        barrier.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
        barrier.subresourceRange.levelCount = mips;
        barrier.subresourceRange.layerCount = 6;
        vkCmdPipelineBarrier(tmp_cb, VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT,
            VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT, 0, 0, NULL, 0, NULL, 1, &barrier);

        if (vkEndCommandBuffer(tmp_cb) != VK_SUCCESS) {
            LOG_FATAL("VK: failed to end cubemap layout command buffer");
            vkFreeCommandBuffers(vk->device, vk->cmd_pool, 1, &tmp_cb);
            vkDestroyImageView(vk->device, cd->view, NULL);
            vkDestroyImage(vk->device, cd->image, NULL);
            vkFreeMemory(vk->device, cd->memory, NULL);
            free(cd);
            return RHI_HANDLE_NULL;
        }

        VkFence fence;
        VkFenceCreateInfo fci = {0};
        fci.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
        if (vkCreateFence(vk->device, &fci, NULL, &fence) != VK_SUCCESS) {
            LOG_FATAL("VK: failed to create cubemap layout fence");
            vkFreeCommandBuffers(vk->device, vk->cmd_pool, 1, &tmp_cb);
            vkDestroyImageView(vk->device, cd->view, NULL);
            vkDestroyImage(vk->device, cd->image, NULL);
            vkFreeMemory(vk->device, cd->memory, NULL);
            free(cd);
            return RHI_HANDLE_NULL;
        }
        VkSubmitInfo si = {0};
        si.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
        si.commandBufferCount = 1;
        si.pCommandBuffers = &tmp_cb;
        if (vkQueueSubmit(vk->graphics_queue, 1, &si, fence) != VK_SUCCESS) {
            LOG_FATAL("VK: failed to submit cubemap layout commands");
            vkDestroyFence(vk->device, fence, NULL);
            vkFreeCommandBuffers(vk->device, vk->cmd_pool, 1, &tmp_cb);
            vkDestroyImageView(vk->device, cd->view, NULL);
            vkDestroyImage(vk->device, cd->image, NULL);
            vkFreeMemory(vk->device, cd->memory, NULL);
            free(cd);
            return RHI_HANDLE_NULL;
        }
        if (vkWaitForFences(vk->device, 1, &fence, VK_TRUE, UINT64_MAX) != VK_SUCCESS) {
            LOG_FATAL("VK: vkWaitForFences failed for cubemap layout");
            vkDestroyFence(vk->device, fence, NULL);
            vkFreeCommandBuffers(vk->device, vk->cmd_pool, 1, &tmp_cb);
            vkDestroyImageView(vk->device, cd->view, NULL);
            vkDestroyImage(vk->device, cd->image, NULL);
            vkFreeMemory(vk->device, cd->memory, NULL);
            free(cd);
            return RHI_HANDLE_NULL;
        }
        vkDestroyFence(vk->device, fence, NULL);
        vkFreeCommandBuffers(vk->device, vk->cmd_pool, 1, &tmp_cb);
    }

    u32 idx = rhi_alloc_slot(dev);
    dev->slots[idx].ptr = cd;
    dev->slots[idx].type = RHI_RES_CUBEMAP;
    return rhi_make_handle(idx, dev->slots[idx].generation);
}

void rhi_cubemap_destroy(RHIDevice *dev, RHICubemap cm) {
    if (!dev || !rhi_handle_valid(cm)) return;
    VKBackend *vk = vk_backend(dev);
    VKCubemapData *cd = rhi_get_resource(dev, cm);
    if (!cd) return;
    if (vkDeviceWaitIdle(vk->device) != VK_SUCCESS)
        LOG_WARN("VK: vkDeviceWaitIdle failed in cubemap_destroy");
    for (u32 i = 0; i < 6; i++) {
        for (u32 m = 0; m < VK_MAX_MIP_VIEWS; m++) {
            if (cd->face_views[i][m]) vkDestroyImageView(vk->device, cd->face_views[i][m], NULL);
        }
    }
    vkDestroyImageView(vk->device, cd->view, NULL);
    vkDestroyImage(vk->device, cd->image, NULL);
    vkFreeMemory(vk->device, cd->memory, NULL);
    free(cd);
    rhi_free_slot(dev, cm);
}

void rhi_cubemap_transition_to_read(RHIDevice *dev, RHICubemap cm) {
    if (!dev || !rhi_handle_valid(cm)) return;
    VKBackend *vk = vk_backend(dev);
    VKCubemapData *cd = (VKCubemapData *)rhi_get_resource(dev, cm);
    if (!cd) return;

    /* Prior compute writes ran in earlier queue submissions; make sure they
     * finished before re-transitioning, then barrier GENERAL -> SHADER_READ. */
    if (vkDeviceWaitIdle(vk->device) != VK_SUCCESS)
        LOG_WARN("VK: vkDeviceWaitIdle failed in cubemap_transition_to_read");

    VkCommandBufferAllocateInfo cbai = {0};
    cbai.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    cbai.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
    cbai.commandPool = vk->cmd_pool;
    cbai.commandBufferCount = 1;
    VkCommandBuffer tmp_cb;
    if (vkAllocateCommandBuffers(vk->device, &cbai, &tmp_cb) != VK_SUCCESS) {
        LOG_WARN("VK: failed to allocate cubemap transition command buffer");
        return;
    }
    VkCommandBufferBeginInfo cbi = {0};
    cbi.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
    cbi.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;
    if (vkBeginCommandBuffer(tmp_cb, &cbi) != VK_SUCCESS) {
        LOG_WARN("VK: failed to begin cubemap transition command buffer");
        vkFreeCommandBuffers(vk->device, vk->cmd_pool, 1, &tmp_cb);
        return;
    }

    VkImageMemoryBarrier barrier = {0};
    barrier.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
    barrier.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
    barrier.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
    barrier.image = cd->image;
    barrier.oldLayout = VK_IMAGE_LAYOUT_GENERAL;
    barrier.newLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
    barrier.srcAccessMask = VK_ACCESS_SHADER_WRITE_BIT;
    barrier.dstAccessMask = VK_ACCESS_SHADER_READ_BIT;
    barrier.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
    barrier.subresourceRange.levelCount = cd->mip_levels;
    barrier.subresourceRange.layerCount = 6;
    vkCmdPipelineBarrier(tmp_cb, VK_PIPELINE_STAGE_COMPUTE_SHADER_BIT,
        VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT, 0, 0, NULL, 0, NULL, 1, &barrier);

    if (vkEndCommandBuffer(tmp_cb) != VK_SUCCESS) {
        LOG_WARN("VK: failed to end cubemap transition command buffer");
        vkFreeCommandBuffers(vk->device, vk->cmd_pool, 1, &tmp_cb);
        return;
    }

    VkFence fence;
    VkFenceCreateInfo fci = {0};
    fci.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
    if (vkCreateFence(vk->device, &fci, NULL, &fence) != VK_SUCCESS) {
        LOG_WARN("VK: failed to create cubemap transition fence");
        vkFreeCommandBuffers(vk->device, vk->cmd_pool, 1, &tmp_cb);
        return;
    }
    VkSubmitInfo si = {0};
    si.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
    si.commandBufferCount = 1;
    si.pCommandBuffers = &tmp_cb;
    if (vkQueueSubmit(vk->graphics_queue, 1, &si, fence) != VK_SUCCESS) {
        LOG_WARN("VK: failed to submit cubemap transition commands");
        vkDestroyFence(vk->device, fence, NULL);
        vkFreeCommandBuffers(vk->device, vk->cmd_pool, 1, &tmp_cb);
        return;
    }
    if (vkWaitForFences(vk->device, 1, &fence, VK_TRUE, UINT64_MAX) != VK_SUCCESS)
        LOG_WARN("VK: vkWaitForFences failed for cubemap transition");
    vkDestroyFence(vk->device, fence, NULL);
    vkFreeCommandBuffers(vk->device, vk->cmd_pool, 1, &tmp_cb);
}

void rhi_texture_transition_to_read(RHIDevice *dev, RHITexture tex) {
    if (!dev || !rhi_handle_valid(tex)) return;
    VKBackend *vk = vk_backend(dev);
    VKTextureData *td = (VKTextureData *)rhi_get_resource(dev, tex);
    if (!td || td->image == VK_NULL_HANDLE) return;

    if (vkDeviceWaitIdle(vk->device) != VK_SUCCESS)
        LOG_WARN("VK: vkDeviceWaitIdle failed in texture_transition_to_read");

    VkCommandBufferAllocateInfo cbai = {0};
    cbai.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    cbai.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
    cbai.commandPool = vk->cmd_pool;
    cbai.commandBufferCount = 1;
    VkCommandBuffer tmp_cb;
    if (vkAllocateCommandBuffers(vk->device, &cbai, &tmp_cb) != VK_SUCCESS) {
        LOG_WARN("VK: failed to allocate texture transition command buffer");
        return;
    }
    VkCommandBufferBeginInfo cbi = {0};
    cbi.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
    cbi.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;
    if (vkBeginCommandBuffer(tmp_cb, &cbi) != VK_SUCCESS) {
        LOG_WARN("VK: failed to begin texture transition command buffer");
        vkFreeCommandBuffers(vk->device, vk->cmd_pool, 1, &tmp_cb);
        return;
    }

    VkImageMemoryBarrier barrier = {0};
    barrier.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
    barrier.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
    barrier.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
    barrier.image = td->image;
    barrier.oldLayout = VK_IMAGE_LAYOUT_GENERAL;
    barrier.newLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
    barrier.srcAccessMask = VK_ACCESS_SHADER_WRITE_BIT;
    barrier.dstAccessMask = VK_ACCESS_SHADER_READ_BIT;
    barrier.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
    barrier.subresourceRange.levelCount = VK_REMAINING_MIP_LEVELS;
    barrier.subresourceRange.layerCount = VK_REMAINING_ARRAY_LAYERS;
    vkCmdPipelineBarrier(tmp_cb, VK_PIPELINE_STAGE_COMPUTE_SHADER_BIT,
        VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT, 0, 0, NULL, 0, NULL, 1, &barrier);

    if (vkEndCommandBuffer(tmp_cb) != VK_SUCCESS) {
        LOG_WARN("VK: failed to end texture transition command buffer");
        vkFreeCommandBuffers(vk->device, vk->cmd_pool, 1, &tmp_cb);
        return;
    }

    VkFence fence;
    VkFenceCreateInfo fci = {0};
    fci.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
    if (vkCreateFence(vk->device, &fci, NULL, &fence) != VK_SUCCESS) {
        LOG_WARN("VK: failed to create texture transition fence");
        vkFreeCommandBuffers(vk->device, vk->cmd_pool, 1, &tmp_cb);
        return;
    }
    VkSubmitInfo si = {0};
    si.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
    si.commandBufferCount = 1;
    si.pCommandBuffers = &tmp_cb;
    if (vkQueueSubmit(vk->graphics_queue, 1, &si, fence) != VK_SUCCESS) {
        LOG_WARN("VK: failed to submit texture transition commands");
        vkDestroyFence(vk->device, fence, NULL);
        vkFreeCommandBuffers(vk->device, vk->cmd_pool, 1, &tmp_cb);
        return;
    }
    if (vkWaitForFences(vk->device, 1, &fence, VK_TRUE, UINT64_MAX) != VK_SUCCESS)
        LOG_WARN("VK: vkWaitForFences failed for texture transition");
    vkDestroyFence(vk->device, fence, NULL);
    vkFreeCommandBuffers(vk->device, vk->cmd_pool, 1, &tmp_cb);

    if (td->cur_layout) td->cur_layout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
}

void rhi_cmd_bind_cubemap(RHICmdBuffer *cmd, RHICubemap cm, RHISampler sampler, u32 unit) {
    (void)cmd; (void)unit;
    VKBackend *vk = vk_backend(g_current_device);
    VKCubemapData *cd = (VKCubemapData *)rhi_get_resource(g_current_device, cm);
    VKSamplerData *sd = (VKSamplerData *)rhi_get_resource(g_current_device, sampler);
    if (!cd || !sd || !vk->current_pipeline_data) return;

    VkDescriptorSetAllocateInfo dsai = {0};
    dsai.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
    dsai.descriptorPool = vk->desc_pools[vk->current_frame];
    dsai.descriptorSetCount = 1;
    dsai.pSetLayouts = &vk->desc_layout;

    VkDescriptorSet ds;
    if (vkAllocateDescriptorSets(vk->device, &dsai, &ds) != VK_SUCCESS) return;

    /* R98-1: Single write with descriptorCount=2 for consecutive bindings 0-1.
     * Both bindings use the same cubemap view (was 2 separate identical writes). */
    VkDescriptorImageInfo img_infos[2];
    memset(img_infos, 0, sizeof(img_infos));
    img_infos[0].sampler = sd->sampler;
    img_infos[0].imageView = cd->view;
    img_infos[0].imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
    img_infos[1] = img_infos[0];

    VkWriteDescriptorSet write = {0};
    write.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
    write.dstSet = ds;
    write.dstBinding = 0;
    write.descriptorCount = 2;
    write.descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
    write.pImageInfo = img_infos;
    vkUpdateDescriptorSets(vk->device, 1, &write, 0, NULL);

    vkCmdBindDescriptorSets(vk->cmd_buffers[vk->current_frame],
        VK_PIPELINE_BIND_POINT_GRAPHICS, vk->current_pipeline_data->layout,
        0, 1, &ds, 0, NULL);
}

/* ---- Depth state ---- */

/* R81-1: Vulkan no-ops — depth compare op is a static pipeline state
 * (depth.depthCompareOp set at pipeline creation). VK_DYNAMIC_STATE_DEPTH_COMPARE_OP
 * is NOT enabled, so calling vkCmdSetDepthCompareOp would be a validation error.
 * skybox_render is the sole caller; the skybox pipeline descriptor sets
 * depth_compare_lequal=true which maps to VK_COMPARE_OP_LESS_OR_EQUAL. */
void rhi_cmd_set_depth_func_less_or_equal(RHICmdBuffer *cmd) { (void)cmd; }
void rhi_cmd_set_depth_func_less(RHICmdBuffer *cmd) { (void)cmd; }

/* R80-2: Vulkan no-ops — depth mask and cull face are handled by pipeline state. */
void rhi_cmd_set_depth_mask(RHICmdBuffer *cmd, bool enabled) { (void)cmd; (void)enabled; }
void rhi_cmd_set_cull_face(RHICmdBuffer *cmd, bool enabled) { (void)cmd; (void)enabled; }

void rhi_buffer_update(RHIDevice *dev, RHIBuffer buf, const void *data, usize size) {
    VKBackend *vk = vk_backend(dev);
    VKBufferData *bd = (VKBufferData *)rhi_get_resource(dev, buf);
    if (!bd || !data || size == 0u) return;
    if (bd->mapped) {
        memcpy(bd->mapped, data, size);
    } else if (bd->device_local) {
        /* R181: rare updates to static DEVICE_LOCAL meshes (e.g. terrain flatten). */
        if (size > bd->size) size = bd->size;
        if (!vk_buffer_staging_upload(vk, bd->buffer, 0, data, size))
            LOG_WARN("VK: rhi_buffer_update staging failed");
    } else {
        void *mapped;
        /* R113-2: Guard against vkMapMemory failure — without this check
         * 'mapped' is undefined and memcpy would crash. */
        if (vkMapMemory(vk->device, bd->memory, 0, size, 0, &mapped) != VK_SUCCESS)
            return;
        memcpy(mapped, data, size);
        vkUnmapMemory(vk->device, bd->memory);
    }
}

void rhi_buffer_update_region(RHIDevice *dev, RHIBuffer buf, usize offset, const void *data, usize size) {
    VKBackend *vk = vk_backend(dev);
    VKBufferData *bd = (VKBufferData *)rhi_get_resource(dev, buf);
    if (!bd || !data || size == 0u) return;
    if (offset >= bd->size) return;
    if (offset + size > bd->size) size = bd->size - offset;
    if (bd->mapped) {
        memcpy(bd->mapped + offset, data, size);
    } else if (bd->device_local) {
        if (!vk_buffer_staging_upload(vk, bd->buffer, offset, data, size))
            LOG_WARN("VK: rhi_buffer_update_region staging failed");
    } else {
        void *mapped;
        /* R113-2: Guard against vkMapMemory failure — same fix as rhi_buffer_update. */
        if (vkMapMemory(vk->device, bd->memory, offset, size, 0, &mapped) != VK_SUCCESS)
            return;
        memcpy(mapped, data, size);
        vkUnmapMemory(vk->device, bd->memory);
    }
}

void* rhi_buffer_map(RHIDevice *dev, RHIBuffer buf) {
    VKBackend *vk = vk_backend(dev);
    VKBufferData *bd = (VKBufferData *)rhi_get_resource(dev, buf);
    if (!bd) return NULL;
    if (bd->mapped) return bd->mapped;
    /* R186: DEVICE_LOCAL cannot be persistently mapped — use rhi_buffer_read. */
    if (bd->device_local) {
        LOG_WARN("VK: rhi_buffer_map on DEVICE_LOCAL buffer; use rhi_buffer_read");
        return NULL;
    }
    void *mapped = NULL;
    if (vkMapMemory(vk->device, bd->memory, 0, VK_WHOLE_SIZE, 0, &mapped) != VK_SUCCESS) {
        LOG_WARN("VK: vkMapMemory failed in buffer_map");
        return NULL;
    }
    return mapped;
}

void rhi_buffer_unmap(RHIDevice *dev, RHIBuffer buf) {
    VKBackend *vk = vk_backend(dev);
    VKBufferData *bd = (VKBufferData *)rhi_get_resource(dev, buf);
    if (!bd) return;
    if (bd->mapped || bd->device_local) return; /* persistent / no map */
    vkUnmapMemory(vk->device, bd->memory);
}

bool rhi_buffer_read(RHIDevice *dev, RHIBuffer buf, void *dst, usize offset, usize size) {
    VKBackend *vk = vk_backend(dev);
    VKBufferData *bd = (VKBufferData *)rhi_get_resource(dev, buf);
    if (!bd || !dst || size == 0u) return false;
    if (offset >= bd->size) return false;
    if (offset + size > bd->size) size = bd->size - offset;
    if (bd->mapped) {
        memcpy(dst, bd->mapped + offset, size);
        return true;
    }
    if (bd->device_local)
        return vk_buffer_staging_download(vk, bd->buffer, offset, dst, size);
    void *mapped = NULL;
    if (vkMapMemory(vk->device, bd->memory, offset, size, 0, &mapped) != VK_SUCCESS)
        return false;
    memcpy(dst, mapped, size);
    vkUnmapMemory(vk->device, bd->memory);
    return true;
}

/* R183: Record host data into the CB so later dispatches see ordered writes
 * (unlike rhi_buffer_update which memcpy's mapped memory immediately). */
void rhi_cmd_update_buffer(RHICmdBuffer *cmd, RHIBuffer buf, usize offset,
                           const void *data, usize size) {
    (void)cmd;
    if (!data || size == 0u) return;
    VKBackend *vk = vk_backend(g_current_device);
    VKBufferData *bd = (VKBufferData *)rhi_get_resource(g_current_device, buf);
    if (!bd) return;
    if (offset + size > bd->size) {
        if (offset >= bd->size) return;
        size = bd->size - offset;
    }
    vk_suspend_pass_for_compute(vk);
    VkCommandBuffer cb = vk->cmd_buffers[vk->current_frame];

    /* vkCmdUpdateBuffer is limited to 65536 bytes and requires 4-byte align. */
    if (size > 65536u || ((offset | size) & 3u) != 0u) {
        LOG_WARN("VK: rhi_cmd_update_buffer requires 4-byte align and size<=65536");
        return;
    }
    vkCmdUpdateBuffer(cb, bd->buffer, (VkDeviceSize)offset, (VkDeviceSize)size, data);

    VkBufferMemoryBarrier to_shader = {0};
    to_shader.sType = VK_STRUCTURE_TYPE_BUFFER_MEMORY_BARRIER;
    to_shader.srcAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
    to_shader.dstAccessMask = VK_ACCESS_SHADER_READ_BIT | VK_ACCESS_SHADER_WRITE_BIT
                            | VK_ACCESS_INDIRECT_COMMAND_READ_BIT;
    to_shader.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
    to_shader.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
    to_shader.buffer = bd->buffer;
    to_shader.offset = offset;
    to_shader.size = size;
    vkCmdPipelineBarrier(cb,
        VK_PIPELINE_STAGE_TRANSFER_BIT,
        VK_PIPELINE_STAGE_COMPUTE_SHADER_BIT | VK_PIPELINE_STAGE_DRAW_INDIRECT_BIT
            | VK_PIPELINE_STAGE_VERTEX_SHADER_BIT | VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT,
        0, 0, NULL, 1, &to_shader, 0, NULL);
}

/* R87-1: GPU-side buffer copy via vkCmdCopyBuffer (non-blocking). */
void rhi_cmd_copy_buffer(RHICmdBuffer *cmd, RHIBuffer src, RHIBuffer dst, usize size) {
    (void)cmd;
    if (size == 0u) return;
    VKBackend *vk = vk_backend(g_current_device);
    VKBufferData *src_bd = (VKBufferData *)rhi_get_resource(g_current_device, src);
    VKBufferData *dst_bd = (VKBufferData *)rhi_get_resource(g_current_device, dst);
    if (!src_bd || !dst_bd) return;
    /* R177: Copy is invalid inside a render pass; also barrier compute→transfer
     * so callers cannot forget (vis-flags / occlusion staging paths). */
    vk_suspend_pass_for_compute(vk);
    VkCommandBuffer cb = vk->cmd_buffers[vk->current_frame];

    VkBufferMemoryBarrier barriers[2];
    memset(barriers, 0, sizeof(barriers));
    barriers[0].sType = VK_STRUCTURE_TYPE_BUFFER_MEMORY_BARRIER;
    barriers[0].srcAccessMask = VK_ACCESS_SHADER_WRITE_BIT | VK_ACCESS_TRANSFER_WRITE_BIT;
    barriers[0].dstAccessMask = VK_ACCESS_TRANSFER_READ_BIT;
    barriers[0].srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
    barriers[0].dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
    barriers[0].buffer = src_bd->buffer;
    barriers[0].offset = 0;
    barriers[0].size = size;
    barriers[1].sType = VK_STRUCTURE_TYPE_BUFFER_MEMORY_BARRIER;
    barriers[1].srcAccessMask = VK_ACCESS_HOST_READ_BIT | VK_ACCESS_SHADER_READ_BIT
                               | VK_ACCESS_TRANSFER_WRITE_BIT | VK_ACCESS_TRANSFER_READ_BIT;
    barriers[1].dstAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
    barriers[1].srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
    barriers[1].dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
    barriers[1].buffer = dst_bd->buffer;
    barriers[1].offset = 0;
    barriers[1].size = size;
    vkCmdPipelineBarrier(cb,
        VK_PIPELINE_STAGE_COMPUTE_SHADER_BIT | VK_PIPELINE_STAGE_TRANSFER_BIT
            | VK_PIPELINE_STAGE_HOST_BIT,
        VK_PIPELINE_STAGE_TRANSFER_BIT,
        0, 0, NULL, 2, barriers, 0, NULL);

    VkBufferCopy region = { .srcOffset = 0, .dstOffset = 0, .size = size };
    vkCmdCopyBuffer(cb, src_bd->buffer, dst_bd->buffer, 1, &region);

    VkBufferMemoryBarrier to_host = {0};
    to_host.sType = VK_STRUCTURE_TYPE_BUFFER_MEMORY_BARRIER;
    to_host.srcAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
    to_host.dstAccessMask = VK_ACCESS_HOST_READ_BIT | VK_ACCESS_SHADER_READ_BIT
                          | VK_ACCESS_TRANSFER_READ_BIT;
    to_host.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
    to_host.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
    to_host.buffer = dst_bd->buffer;
    to_host.offset = 0;
    to_host.size = size;
    vkCmdPipelineBarrier(cb,
        VK_PIPELINE_STAGE_TRANSFER_BIT,
        VK_PIPELINE_STAGE_HOST_BIT | VK_PIPELINE_STAGE_COMPUTE_SHADER_BIT
            | VK_PIPELINE_STAGE_TRANSFER_BIT,
        0, 0, NULL, 1, &to_host, 0, NULL);
}

/* R171: Recorded fill so resets are ordered between dispatches in the same CB. */
void rhi_cmd_fill_buffer(RHICmdBuffer *cmd, RHIBuffer buf, usize offset, usize size, u32 value) {
    (void)cmd;
    if (size == 0u) return;
    VKBackend *vk = vk_backend(g_current_device);
    VKBufferData *bd = (VKBufferData *)rhi_get_resource(g_current_device, buf);
    if (!bd) return;
    /* vkCmdFillBuffer requires 4-byte alignment. */
    if ((offset & 3u) || (size & 3u)) {
        LOG_WARN("VK: rhi_cmd_fill_buffer requires 4-byte aligned offset/size");
        return;
    }
    vk_suspend_pass_for_compute(vk);
    VkCommandBuffer cb = vk->cmd_buffers[vk->current_frame];

    VkBufferMemoryBarrier to_transfer = {0};
    to_transfer.sType = VK_STRUCTURE_TYPE_BUFFER_MEMORY_BARRIER;
    /* R185: Also wait prior DRAW_INDIRECT / shader reads — CSM/point-shadow
     * reuse the same count/draws buffer across cascades in one CB. */
    to_transfer.srcAccessMask = VK_ACCESS_SHADER_WRITE_BIT | VK_ACCESS_TRANSFER_WRITE_BIT
                              | VK_ACCESS_INDIRECT_COMMAND_READ_BIT | VK_ACCESS_SHADER_READ_BIT;
    to_transfer.dstAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
    to_transfer.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
    to_transfer.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
    to_transfer.buffer = bd->buffer;
    to_transfer.offset = offset;
    to_transfer.size = size;
    vkCmdPipelineBarrier(cb,
        VK_PIPELINE_STAGE_COMPUTE_SHADER_BIT | VK_PIPELINE_STAGE_TRANSFER_BIT
            | VK_PIPELINE_STAGE_DRAW_INDIRECT_BIT,
        VK_PIPELINE_STAGE_TRANSFER_BIT,
        0, 0, NULL, 1, &to_transfer, 0, NULL);

    vkCmdFillBuffer(cb, bd->buffer, (VkDeviceSize)offset, (VkDeviceSize)size, value);

    VkBufferMemoryBarrier to_shader = {0};
    to_shader.sType = VK_STRUCTURE_TYPE_BUFFER_MEMORY_BARRIER;
    to_shader.srcAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
    to_shader.dstAccessMask = VK_ACCESS_SHADER_READ_BIT | VK_ACCESS_SHADER_WRITE_BIT
                            | VK_ACCESS_INDIRECT_COMMAND_READ_BIT;
    to_shader.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
    to_shader.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
    to_shader.buffer = bd->buffer;
    to_shader.offset = offset;
    to_shader.size = size;
    vkCmdPipelineBarrier(cb,
        VK_PIPELINE_STAGE_TRANSFER_BIT,
        VK_PIPELINE_STAGE_COMPUTE_SHADER_BIT | VK_PIPELINE_STAGE_DRAW_INDIRECT_BIT,
        0, 0, NULL, 1, &to_shader, 0, NULL);
}

void rhi_cmd_bind_texel_buffers(RHICmdBuffer *cmd, RHIBuffer buf0, RHIBuffer buf1) {
    (void)cmd;
    VKBackend *vk = vk_backend(g_current_device);
    if (!vk->current_pipeline_data) return;

    VKBufferData *bd0 = (VKBufferData *)rhi_get_resource(g_current_device, buf0);
    if (!bd0 || bd0->texel_view == VK_NULL_HANDLE) return;

    VkDescriptorSet desc_set;
    VkDescriptorSetAllocateInfo dsai = {0};
    dsai.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
    dsai.descriptorPool = vk->desc_pools[vk->current_frame];
    dsai.descriptorSetCount = 1;
    dsai.pSetLayouts = &vk->texel_layout;
    VkResult res = vkAllocateDescriptorSets(vk->device, &dsai, &desc_set);
    if (res != VK_SUCCESS) {
        LOG_ERROR("Failed to allocate texel descriptor set: %d", res);
        return;
    }

    VkWriteDescriptorSet writes[2] = {0};
    u32 write_count = 0;
    writes[write_count].sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
    writes[write_count].dstSet = desc_set;
    writes[write_count].dstBinding = 0;
    writes[write_count].descriptorCount = 1;
    writes[write_count].descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_TEXEL_BUFFER;
    writes[write_count].pTexelBufferView = &bd0->texel_view;
    write_count++;

    VKBufferData *bd1 = NULL;
    if (rhi_handle_valid(buf1)) {
        bd1 = (VKBufferData *)rhi_get_resource(g_current_device, buf1);
    }
    if (bd1 && bd1->texel_view != VK_NULL_HANDLE) {
        writes[write_count].sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
        writes[write_count].dstSet = desc_set;
        writes[write_count].dstBinding = 1;
        writes[write_count].descriptorCount = 1;
        writes[write_count].descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_TEXEL_BUFFER;
        writes[write_count].pTexelBufferView = &bd1->texel_view;
        write_count++;
    }

    vkUpdateDescriptorSets(vk->device, write_count, writes, 0, NULL);

    vkCmdBindDescriptorSets(vk->cmd_buffers[vk->current_frame],
        VK_PIPELINE_BIND_POINT_GRAPHICS, vk->current_pipeline_data->layout,
        1, 1, &desc_set, 0, NULL);
}

/* ---- Offscreen FBO ---- */

typedef struct {
    VkImage        color_image;
    VkDeviceMemory color_memory;
    VkImageView    color_view;
    VkImage        depth_image;
    VkDeviceMemory depth_memory;
    VkImageView    depth_view;
    VkFramebuffer  framebuffer;
    VkRenderPass   render_pass;
    VkRenderPass   render_pass_load;  /* LOAD-op twin for compute suspend/resume */
    VkFormat       color_fmt;         /* for render-pass-compatible pipeline variants */
} VKFBOData;

RHIOffscreenFBO rhi_offscreen_fbo_create_fmt(RHIDevice *dev, u32 width, u32 height, RHIFormat color_fmt) {
    VKBackend *vk = vk_backend(dev);
    RHIOffscreenFBO fbo = {0};
    fbo.width = width;
    fbo.height = height;

    VkFormat vk_color_fmt = vk_format_from_rhi(color_fmt);

    VKFBOData *fd = calloc(1, sizeof(VKFBOData));
    if (!fd) return fbo;
    fd->color_fmt = vk_color_fmt;

    VkImageCreateInfo ci = {0};
    ci.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
    ci.imageType = VK_IMAGE_TYPE_2D;
    ci.format = vk_color_fmt;
    ci.extent.width = width;
    ci.extent.height = height;
    ci.extent.depth = 1;
    ci.mipLevels = 1;
    ci.arrayLayers = 1;
    ci.samples = VK_SAMPLE_COUNT_1_BIT;
    ci.tiling = VK_IMAGE_TILING_OPTIMAL;
    ci.usage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT | VK_IMAGE_USAGE_SAMPLED_BIT;
    ci.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
    ci.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
    if (vkCreateImage(vk->device, &ci, NULL, &fd->color_image) != VK_SUCCESS) {
        LOG_FATAL("VK: failed to create MRT color image");
        free(fd);
        return fbo;
    }

    VkMemoryRequirements mr;
    vkGetImageMemoryRequirements(vk->device, fd->color_image, &mr);
    VkMemoryAllocateInfo ai = {0};
    ai.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
    ai.allocationSize = mr.size;
    ai.memoryTypeIndex = vk_find_memory(vk, mr.memoryTypeBits,
        VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);
    if (vkAllocateMemory(vk->device, &ai, NULL, &fd->color_memory) != VK_SUCCESS) {
        LOG_FATAL("VK: failed to allocate MRT color memory");
        vkDestroyImage(vk->device, fd->color_image, NULL);
        free(fd);
        return fbo;
    }
    if (vkBindImageMemory(vk->device, fd->color_image, fd->color_memory, 0) != VK_SUCCESS) {
        LOG_FATAL("VK: failed to bind MRT color image memory");
        vkFreeMemory(vk->device, fd->color_memory, NULL);
        vkDestroyImage(vk->device, fd->color_image, NULL);
        free(fd);
        return fbo;
    }

    VkImageViewCreateInfo ivci = {0};
    ivci.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
    ivci.image = fd->color_image;
    ivci.viewType = VK_IMAGE_VIEW_TYPE_2D;
    ivci.format = vk_color_fmt;
    ivci.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
    ivci.subresourceRange.levelCount = 1;
    ivci.subresourceRange.layerCount = 1;
    if (vkCreateImageView(vk->device, &ivci, NULL, &fd->color_view) != VK_SUCCESS) {
        LOG_FATAL("VK: failed to create MRT color image view");
        vkFreeMemory(vk->device, fd->color_memory, NULL);
        vkDestroyImage(vk->device, fd->color_image, NULL);
        free(fd);
        return fbo;
    }

    /* Defined sampling layout for the case this target is sampled before it is
     * ever rendered into (avoids VUID-vkCmdDraw-None-09600). */
    vk_init_image_layout(vk, fd->color_image, VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL);

    ci.format = VK_FORMAT_D32_SFLOAT;
    ci.usage = VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT | VK_IMAGE_USAGE_SAMPLED_BIT;
    if (vkCreateImage(vk->device, &ci, NULL, &fd->depth_image) != VK_SUCCESS) {
        LOG_FATAL("VK: failed to create MRT depth image");
        vkDestroyImageView(vk->device, fd->color_view, NULL);
        vkFreeMemory(vk->device, fd->color_memory, NULL);
        vkDestroyImage(vk->device, fd->color_image, NULL);
        free(fd);
        return fbo;
    }
    vkGetImageMemoryRequirements(vk->device, fd->depth_image, &mr);
    ai.allocationSize = mr.size;
    ai.memoryTypeIndex = vk_find_memory(vk, mr.memoryTypeBits,
        VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);
    if (vkAllocateMemory(vk->device, &ai, NULL, &fd->depth_memory) != VK_SUCCESS) {
        LOG_FATAL("VK: failed to allocate MRT depth memory");
        vkDestroyImage(vk->device, fd->depth_image, NULL);
        vkDestroyImageView(vk->device, fd->color_view, NULL);
        vkFreeMemory(vk->device, fd->color_memory, NULL);
        vkDestroyImage(vk->device, fd->color_image, NULL);
        free(fd);
        return fbo;
    }
    if (vkBindImageMemory(vk->device, fd->depth_image, fd->depth_memory, 0) != VK_SUCCESS) {
        LOG_FATAL("VK: failed to bind MRT depth image memory");
        vkFreeMemory(vk->device, fd->depth_memory, NULL);
        vkDestroyImage(vk->device, fd->depth_image, NULL);
        vkDestroyImageView(vk->device, fd->color_view, NULL);
        vkFreeMemory(vk->device, fd->color_memory, NULL);
        vkDestroyImage(vk->device, fd->color_image, NULL);
        free(fd);
        return fbo;
    }

    ivci.image = fd->depth_image;
    ivci.format = VK_FORMAT_D32_SFLOAT;
    ivci.subresourceRange.aspectMask = VK_IMAGE_ASPECT_DEPTH_BIT;
    if (vkCreateImageView(vk->device, &ivci, NULL, &fd->depth_view) != VK_SUCCESS) {
        LOG_FATAL("VK: failed to create MRT depth image view");
        vkFreeMemory(vk->device, fd->depth_memory, NULL);
        vkDestroyImage(vk->device, fd->depth_image, NULL);
        vkDestroyImageView(vk->device, fd->color_view, NULL);
        vkFreeMemory(vk->device, fd->color_memory, NULL);
        vkDestroyImage(vk->device, fd->color_image, NULL);
        free(fd);
        return fbo;
    }

    VkAttachmentDescription attachments[2] = {0};
    attachments[0].format = vk_color_fmt;
    attachments[0].samples = VK_SAMPLE_COUNT_1_BIT;
    attachments[0].loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
    attachments[0].storeOp = VK_ATTACHMENT_STORE_OP_STORE;
    attachments[0].stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
    attachments[0].stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
    attachments[0].initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
    attachments[0].finalLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
    attachments[1].format = VK_FORMAT_D32_SFLOAT;
    attachments[1].samples = VK_SAMPLE_COUNT_1_BIT;
    attachments[1].loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
    /* STORE so depth survives a render-pass suspend (compute dispatch). */
    attachments[1].storeOp = VK_ATTACHMENT_STORE_OP_STORE;
    attachments[1].stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
    attachments[1].stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
    attachments[1].initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
    attachments[1].finalLayout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;

    VkAttachmentReference color_ref = {0, VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL};
    VkAttachmentReference depth_ref = {1, VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL};
    VkSubpassDescription sp = {0};
    sp.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
    sp.colorAttachmentCount = 1;
    sp.pColorAttachments = &color_ref;
    sp.pDepthStencilAttachment = &depth_ref;

    VkSubpassDependency dep = {0};
    dep.srcSubpass = VK_SUBPASS_EXTERNAL;
    dep.dstSubpass = 0;
    dep.srcStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
    dep.srcAccessMask = 0;
    dep.dstStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
    dep.dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;

    VkRenderPassCreateInfo rpci = {0};
    rpci.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
    rpci.attachmentCount = 2;
    rpci.pAttachments = attachments;
    rpci.subpassCount = 1;
    rpci.pSubpasses = &sp;
    rpci.dependencyCount = 1;
    rpci.pDependencies = &dep;
    if (vkCreateRenderPass(vk->device, &rpci, NULL, &fd->render_pass) != VK_SUCCESS) {
        LOG_FATAL("VK: failed to create MRT render pass");
        vkDestroyImageView(vk->device, fd->depth_view, NULL);
        vkFreeMemory(vk->device, fd->depth_memory, NULL);
        vkDestroyImage(vk->device, fd->depth_image, NULL);
        vkDestroyImageView(vk->device, fd->color_view, NULL);
        vkFreeMemory(vk->device, fd->color_memory, NULL);
        vkDestroyImage(vk->device, fd->color_image, NULL);
        free(fd);
        return fbo;
    }
    fd->render_pass_load = vk_make_resume_render_pass(vk, &rpci);

    VkImageView views[] = {fd->color_view, fd->depth_view};
    VkFramebufferCreateInfo fbci = {0};
    fbci.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
    fbci.renderPass = fd->render_pass;
    fbci.attachmentCount = 2;
    fbci.pAttachments = views;
    fbci.width = width;
    fbci.height = height;
    fbci.layers = 1;
    if (vkCreateFramebuffer(vk->device, &fbci, NULL, &fd->framebuffer) != VK_SUCCESS) {
        LOG_FATAL("VK: failed to create MRT framebuffer");
        if (fd->render_pass_load) vkDestroyRenderPass(vk->device, fd->render_pass_load, NULL);
        vkDestroyRenderPass(vk->device, fd->render_pass, NULL);
        vkDestroyImageView(vk->device, fd->depth_view, NULL);
        vkFreeMemory(vk->device, fd->depth_memory, NULL);
        vkDestroyImage(vk->device, fd->depth_image, NULL);
        vkDestroyImageView(vk->device, fd->color_view, NULL);
        vkFreeMemory(vk->device, fd->color_memory, NULL);
        vkDestroyImage(vk->device, fd->color_image, NULL);
        free(fd);
        return fbo;
    }

    VKTextureData *td = calloc(1, sizeof(VKTextureData));
    if (!td) return fbo;
    u32 idx = rhi_alloc_slot(dev);
    td->image = fd->color_image;
    td->view = fd->color_view;
    td->memory = fd->color_memory;
    td->width = width;
    td->height = height;
    td->format = vk_color_fmt;
    td->mip_levels = 1u; /* R180: bind_texture_compute layout loop */
    td->mip_layout[0] = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
    td->cur_layout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
    dev->slots[idx].ptr = td;
    dev->slots[idx].type = RHI_RES_TEXTURE;
    fbo.color_tex = rhi_make_handle(idx, dev->slots[idx].generation);

    VKTextureData *dd = calloc(1, sizeof(VKTextureData));
    if (!dd) return fbo;
    u32 didx = rhi_alloc_slot(dev);
    dd->image = fd->depth_image;
    dd->view = fd->depth_view;
    dd->memory = fd->depth_memory;
    dd->width = width;
    dd->height = height;
    /* mip_levels stays 0: bind_texture_compute uses COLOR aspect; depth
     * layout is owned by rhi_cmd_transition_depth_to_read (cur_layout). */
    dd->format = VK_FORMAT_D32_SFLOAT;
    dd->cur_layout = VK_IMAGE_LAYOUT_UNDEFINED;
    dev->slots[didx].ptr = dd;
    dev->slots[didx].type = RHI_RES_TEXTURE;
    fbo.depth_tex = rhi_make_handle(didx, dev->slots[didx].generation);

    u32 fidx = rhi_alloc_slot(dev);
    dev->slots[fidx].ptr = fd;
    dev->slots[fidx].type = RHI_RES_FRAMEBUFFER;
    fbo.fb = rhi_make_handle(fidx, dev->slots[fidx].generation);

    return fbo;
}

RHIOffscreenFBO rhi_offscreen_fbo_create(RHIDevice *dev, u32 width, u32 height) {
    return rhi_offscreen_fbo_create_fmt(dev, width, height, RHI_FORMAT_B8G8R8A8_UNORM);
}

void rhi_offscreen_fbo_destroy(RHIDevice *dev, RHIOffscreenFBO *fbo) {
    if (!dev || !fbo) return;
    VKBackend *vk = vk_backend(dev);
    VKFBOData *fd = rhi_get_resource(dev, fbo->fb);
    if (!fd) return;
    if (vkDeviceWaitIdle(vk->device) != VK_SUCCESS)
        LOG_WARN("VK: vkDeviceWaitIdle failed in offscreen_fbo_destroy");
    vkDestroyFramebuffer(vk->device, fd->framebuffer, NULL);
    vkDestroyRenderPass(vk->device, fd->render_pass, NULL);
    if (fd->render_pass_load) vkDestroyRenderPass(vk->device, fd->render_pass_load, NULL);
    vkDestroyImageView(vk->device, fd->color_view, NULL);
    vkDestroyImage(vk->device, fd->color_image, NULL);
    vkFreeMemory(vk->device, fd->color_memory, NULL);
    vkDestroyImageView(vk->device, fd->depth_view, NULL);
    vkDestroyImage(vk->device, fd->depth_image, NULL);
    vkFreeMemory(vk->device, fd->depth_memory, NULL);
    free(fd);
    rhi_free_slot(dev, fbo->fb);
    rhi_free_slot(dev, fbo->color_tex);
    rhi_free_slot(dev, fbo->depth_tex);
    memset(fbo, 0, sizeof(*fbo));
}

void rhi_offscreen_fbo_bind(RHICmdBuffer *cmd, RHIOffscreenFBO *fbo) {
    (void)cmd;
    if (!fbo) return;
    VKBackend *vk = vk_backend(g_current_device);
    VKFBOData *fd = rhi_get_resource(g_current_device, fbo->fb);
    if (!fd) return;

    /* This pass clears + writes the depth attachment and ends with it in
     * DEPTH_STENCIL_ATTACHMENT_OPTIMAL (the render pass finalLayout).  Track
     * that so a later rhi_cmd_transition_depth_to_read re-makes it readable
     * (post-fx like tonemap/cinematic re-bind the scene FBO then god rays /
     * debug viz sample its depth). */
    VKTextureData *dtd = (VKTextureData *)rhi_get_resource(g_current_device, fbo->depth_tex);
    if (dtd) dtd->cur_layout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;

    if (vk->render_pass_active) {
        vkCmdEndRenderPass(vk->cmd_buffers[vk->current_frame]);
        vk->render_pass_active = false;
    }

    VkRenderPassBeginInfo rpi = {0};
    rpi.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
    rpi.renderPass = fd->render_pass;
    rpi.framebuffer = fd->framebuffer;
    rpi.renderArea.extent.width = fbo->width;
    rpi.renderArea.extent.height = fbo->height;
    VkClearValue clears[2];
    memset(clears, 0, sizeof(clears));
    clears[0].color.float32[0] = 0.05f;
    clears[0].color.float32[1] = 0.05f;
    clears[0].color.float32[2] = 0.1f;
    clears[0].color.float32[3] = 1.0f;
    clears[1].depthStencil.depth = 1.0f;
    rpi.clearValueCount = 2;
    rpi.pClearValues = clears;
    vkCmdBeginRenderPass(vk->cmd_buffers[vk->current_frame], &rpi,
        VK_SUBPASS_CONTENTS_INLINE);
    vk->render_pass_active = true;
    vk_record_pass(vk, fd->render_pass_load, fd->framebuffer, fbo->width, fbo->height, fd->color_fmt);

    VkViewport vp = {0, 0, (f32)fbo->width, (f32)fbo->height, 0, 1};
    vkCmdSetViewport(vk->cmd_buffers[vk->current_frame], 0, 1, &vp);
    VkRect2D sc = {{0, 0}, {fbo->width, fbo->height}};
    vkCmdSetScissor(vk->cmd_buffers[vk->current_frame], 0, 1, &sc);
    vk->vp_valid = false; vk->sc_valid = false;  /* R95-2: invalidate cache */
}

void rhi_offscreen_fbo_bind_load(RHICmdBuffer *cmd, RHIOffscreenFBO *fbo) {
    (void)cmd;
    if (!fbo) return;
    VKBackend *vk = vk_backend(g_current_device);
    VKFBOData *fd = rhi_get_resource(g_current_device, fbo->fb);
    if (!fd || !fd->render_pass_load) {
        /* Fallback if LOAD twin missing. */
        rhi_offscreen_fbo_bind(cmd, fbo);
        return;
    }

    /* Depth may be SHADER_READ_ONLY after transition_depth_to_read; LOAD twin
     * expects DEPTH_STENCIL_ATTACHMENT (finalLayout of the clear pass). */
    VKTextureData *dtd = (VKTextureData *)rhi_get_resource(g_current_device, fbo->depth_tex);
    if (dtd && dtd->cur_layout == VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL) {
        vk_suspend_pass_for_compute(vk);
        VkImageMemoryBarrier barrier = {0};
        barrier.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
        barrier.image = dtd->image;
        barrier.oldLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
        barrier.newLayout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;
        barrier.srcAccessMask = VK_ACCESS_SHADER_READ_BIT;
        barrier.dstAccessMask = VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_READ_BIT
                              | VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT;
        barrier.subresourceRange.aspectMask = VK_IMAGE_ASPECT_DEPTH_BIT;
        barrier.subresourceRange.levelCount = 1;
        barrier.subresourceRange.layerCount = 1;
        vkCmdPipelineBarrier(vk->cmd_buffers[vk->current_frame],
            VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT | VK_PIPELINE_STAGE_COMPUTE_SHADER_BIT,
            VK_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT | VK_PIPELINE_STAGE_LATE_FRAGMENT_TESTS_BIT,
            0, 0, NULL, 0, NULL, 1, &barrier);
        dtd->cur_layout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;
    } else if (dtd) {
        dtd->cur_layout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;
    }

    if (vk->render_pass_active) {
        vkCmdEndRenderPass(vk->cmd_buffers[vk->current_frame]);
        vk->render_pass_active = false;
    }

    VkRenderPassBeginInfo rpi = {0};
    rpi.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
    rpi.renderPass = fd->render_pass_load;
    rpi.framebuffer = fd->framebuffer;
    rpi.renderArea.extent.width = fbo->width;
    rpi.renderArea.extent.height = fbo->height;
    rpi.clearValueCount = 0;
    rpi.pClearValues = NULL;
    vkCmdBeginRenderPass(vk->cmd_buffers[vk->current_frame], &rpi,
        VK_SUBPASS_CONTENTS_INLINE);
    vk->render_pass_active = true;
    vk_record_pass(vk, fd->render_pass_load, fd->framebuffer, fbo->width, fbo->height, fd->color_fmt);

    VkViewport vp = {0, 0, (f32)fbo->width, (f32)fbo->height, 0, 1};
    vkCmdSetViewport(vk->cmd_buffers[vk->current_frame], 0, 1, &vp);
    VkRect2D sc = {{0, 0}, {fbo->width, fbo->height}};
    vkCmdSetScissor(vk->cmd_buffers[vk->current_frame], 0, 1, &sc);
    vk->vp_valid = false; vk->sc_valid = false;
}

void rhi_offscreen_fbo_unbind(RHICmdBuffer *cmd, u32 screen_w, u32 screen_h) {
    (void)cmd;
    VKBackend *vk = vk_backend(g_current_device);

    if (vk->render_pass_active) {
        vkCmdEndRenderPass(vk->cmd_buffers[vk->current_frame]);
        vk->render_pass_active = false;
    }
    if (!vk->framebuffers) return;  /* R150: guard against NULL framebuffers */

    VkRenderPassBeginInfo rpi = {0};
    rpi.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
    rpi.renderPass = vk->render_pass;
    rpi.framebuffer = vk->framebuffers[vk->image_index];
    rpi.renderArea.extent.width = screen_w;
    rpi.renderArea.extent.height = screen_h;
    VkClearValue clears[2];
    memset(clears, 0, sizeof(clears));
    clears[0].color.float32[0] = 0.2f;
    clears[0].color.float32[1] = 0.25f;
    clears[0].color.float32[2] = 0.35f;
    clears[0].color.float32[3] = 1.0f;
    clears[1].depthStencil.depth = 1.0f;
    rpi.clearValueCount = 2;
    rpi.pClearValues = clears;
    vkCmdBeginRenderPass(vk->cmd_buffers[vk->current_frame], &rpi,
        VK_SUBPASS_CONTENTS_INLINE);
    vk->render_pass_active = true;
    vk_record_pass(vk, vk->render_pass_load, vk->framebuffers[vk->image_index],
                   screen_w, screen_h, vk->swap_format);

    VkViewport vp = {0, 0, (f32)screen_w, (f32)screen_h, 0, 1};
    vkCmdSetViewport(vk->cmd_buffers[vk->current_frame], 0, 1, &vp);
    VkRect2D sc = {{0, 0}, {screen_w, screen_h}};
    vkCmdSetScissor(vk->cmd_buffers[vk->current_frame], 0, 1, &sc);
    vk->vp_valid = false; vk->sc_valid = false;  /* R95-2: invalidate cache */
    vk->current_pipeline = VK_NULL_HANDLE;
}

/* ======================================================================== */
/* MRT (Multiple Render Targets) framebuffer -- VK backend                  */
/* ======================================================================== */

typedef struct {
    VkImage        color_images[RHI_MRT_MAX_ATTACHMENTS];
    VkDeviceMemory color_memories[RHI_MRT_MAX_ATTACHMENTS];
    VkImageView    color_views[RHI_MRT_MAX_ATTACHMENTS];
    VkImage        depth_image;
    VkDeviceMemory depth_memory;
    VkImageView    depth_view;
    VkFramebuffer  framebuffer;
    VkRenderPass   render_pass;
    VkRenderPass   render_pass_load;  /* LOAD-op twin for compute suspend/resume */
    u32            attachment_count;
} VKMRTFBOData;

typedef struct {
    VkImage        depth_image;     /* cubemap: 6 layers */
    VkDeviceMemory depth_memory;
    VkImageView    depth_view;      /* cubemap view (all 6 layers) */
    VkImageView    face_views[6];   /* per-face 2D views */
    VkFramebuffer  face_fbos[6];   /* per-face framebuffers */
    VkRenderPass   render_pass;
    VkRenderPass   render_pass_load; /* LOAD-op twin for compute suspend/resume */
    u32            size;
} VKCubemapDepthFBOData;

/* Helper: create a 2D VkImage + memory + view for MRT color attachments. */
static void vk_create_mrt_color_image(VKBackend *vk, VkFormat fmt,
                                       u32 w, u32 h,
                                       VkImage *out_img,
                                       VkDeviceMemory *out_mem,
                                       VkImageView *out_view) {
    VkImageCreateInfo ci = {0};
    ci.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
    ci.imageType = VK_IMAGE_TYPE_2D;
    ci.format = fmt;
    ci.extent.width = w;
    ci.extent.height = h;
    ci.extent.depth = 1;
    ci.mipLevels = 1;
    ci.arrayLayers = 1;
    ci.samples = VK_SAMPLE_COUNT_1_BIT;
    ci.tiling = VK_IMAGE_TILING_OPTIMAL;
    ci.usage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT | VK_IMAGE_USAGE_SAMPLED_BIT;
    ci.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
    ci.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
    if (vkCreateImage(vk->device, &ci, NULL, out_img) != VK_SUCCESS) {
        LOG_FATAL("VK: failed to create MRT color image (helper)");
        return;
    }

    VkMemoryRequirements mr;
    vkGetImageMemoryRequirements(vk->device, *out_img, &mr);
    VkMemoryAllocateInfo ai = {0};
    ai.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
    ai.allocationSize = mr.size;
    ai.memoryTypeIndex = vk_find_memory(vk, mr.memoryTypeBits,
        VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);
    if (vkAllocateMemory(vk->device, &ai, NULL, out_mem) != VK_SUCCESS) {
        LOG_FATAL("VK: failed to allocate MRT color memory (helper)");
        vkDestroyImage(vk->device, *out_img, NULL);
        return;
    }
    if (vkBindImageMemory(vk->device, *out_img, *out_mem, 0) != VK_SUCCESS) {
        LOG_FATAL("VK: failed to bind MRT color image memory (helper)");
        vkFreeMemory(vk->device, *out_mem, NULL);
        vkDestroyImage(vk->device, *out_img, NULL);
        return;
    }

    VkImageViewCreateInfo ivci = {0};
    ivci.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
    ivci.image = *out_img;
    ivci.viewType = VK_IMAGE_VIEW_TYPE_2D;
    ivci.format = fmt;
    ivci.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
    ivci.subresourceRange.levelCount = 1;
    ivci.subresourceRange.layerCount = 1;
    if (vkCreateImageView(vk->device, &ivci, NULL, out_view) != VK_SUCCESS) {
        LOG_FATAL("VK: failed to create MRT color image view (helper)");
        vkFreeMemory(vk->device, *out_mem, NULL);
        vkDestroyImage(vk->device, *out_img, NULL);
        return;
    }

    /* Defined sampling layout in case this G-buffer target is sampled before its
     * pass renders into it (avoids VUID-vkCmdDraw-None-09600). */
    vk_init_image_layout(vk, *out_img, VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL);
}

RHIMRTFBO rhi_mrt_fbo_create(RHIDevice *dev, u32 width, u32 height,
                              const RHIFormat *formats, u32 attachment_count) {
    RHIMRTFBO fbo = {0};
    if (attachment_count == 0u || attachment_count > RHI_MRT_MAX_ATTACHMENTS) return fbo;
    fbo.attachment_count = attachment_count;
    fbo.width  = width;
    fbo.height = height;

    VKBackend *vk = vk_backend(dev);
    VKMRTFBOData *md = calloc(1, sizeof(VKMRTFBOData));
    if (!md) return fbo;
    md->attachment_count = attachment_count;

    /* Create color attachments. */
    VkAttachmentDescription att_descs[RHI_MRT_MAX_ATTACHMENTS + 1]; /* +1 for depth */
    VkAttachmentReference color_refs[RHI_MRT_MAX_ATTACHMENTS];
    memset(att_descs, 0, sizeof(att_descs));

    for (u32 i = 0; i < attachment_count; i++) {
        VkFormat vk_fmt = vk_format_from_rhi(formats[i]);
        vk_create_mrt_color_image(vk, vk_fmt, width, height,
                                   &md->color_images[i],
                                   &md->color_memories[i],
                                   &md->color_views[i]);
        color_refs[i].attachment = i;
        color_refs[i].layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

        att_descs[i].format = vk_fmt;
        att_descs[i].samples = VK_SAMPLE_COUNT_1_BIT;
        att_descs[i].loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
        att_descs[i].storeOp = VK_ATTACHMENT_STORE_OP_STORE;
        att_descs[i].stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
        att_descs[i].stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
        att_descs[i].initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
        att_descs[i].finalLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
    }

    /* Shared depth attachment. */
    {
        VkImageCreateInfo ci = {0};
        ci.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
        ci.imageType = VK_IMAGE_TYPE_2D;
        ci.format = VK_FORMAT_D32_SFLOAT;
        ci.extent.width = width;
        ci.extent.height = height;
        ci.extent.depth = 1;
        ci.mipLevels = 1;
        ci.arrayLayers = 1;
        ci.samples = VK_SAMPLE_COUNT_1_BIT;
        ci.tiling = VK_IMAGE_TILING_OPTIMAL;
        ci.usage = VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT | VK_IMAGE_USAGE_SAMPLED_BIT;
        ci.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
        ci.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
        if (vkCreateImage(vk->device, &ci, NULL, &md->depth_image) != VK_SUCCESS) {
            LOG_FATAL("VK: failed to create MRT depth image");
            for (u32 i = 0; i < attachment_count; i++) {
                vkDestroyImageView(vk->device, md->color_views[i], NULL);
                vkDestroyImage(vk->device, md->color_images[i], NULL);
                vkFreeMemory(vk->device, md->color_memories[i], NULL);
            }
            free(md);
            return fbo;
        }

        VkMemoryRequirements mr;
        vkGetImageMemoryRequirements(vk->device, md->depth_image, &mr);
        VkMemoryAllocateInfo ai = {0};
        ai.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
        ai.allocationSize = mr.size;
        ai.memoryTypeIndex = vk_find_memory(vk, mr.memoryTypeBits,
            VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);
        if (vkAllocateMemory(vk->device, &ai, NULL, &md->depth_memory) != VK_SUCCESS) {
            LOG_FATAL("VK: failed to allocate MRT depth memory");
            vkDestroyImage(vk->device, md->depth_image, NULL);
            for (u32 i = 0; i < attachment_count; i++) {
                vkDestroyImageView(vk->device, md->color_views[i], NULL);
                vkDestroyImage(vk->device, md->color_images[i], NULL);
                vkFreeMemory(vk->device, md->color_memories[i], NULL);
            }
            free(md);
            return fbo;
        }
        if (vkBindImageMemory(vk->device, md->depth_image, md->depth_memory, 0) != VK_SUCCESS) {
            LOG_FATAL("VK: failed to bind MRT depth image memory");
            vkFreeMemory(vk->device, md->depth_memory, NULL);
            vkDestroyImage(vk->device, md->depth_image, NULL);
            for (u32 i = 0; i < attachment_count; i++) {
                vkDestroyImageView(vk->device, md->color_views[i], NULL);
                vkDestroyImage(vk->device, md->color_images[i], NULL);
                vkFreeMemory(vk->device, md->color_memories[i], NULL);
            }
            free(md);
            return fbo;
        }

        VkImageViewCreateInfo ivci = {0};
        ivci.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
        ivci.image = md->depth_image;
        ivci.viewType = VK_IMAGE_VIEW_TYPE_2D;
        ivci.format = VK_FORMAT_D32_SFLOAT;
        ivci.subresourceRange.aspectMask = VK_IMAGE_ASPECT_DEPTH_BIT;
        ivci.subresourceRange.levelCount = 1;
        ivci.subresourceRange.layerCount = 1;
        if (vkCreateImageView(vk->device, &ivci, NULL, &md->depth_view) != VK_SUCCESS) {
            LOG_FATAL("VK: failed to create MRT depth image view");
            vkFreeMemory(vk->device, md->depth_memory, NULL);
            vkDestroyImage(vk->device, md->depth_image, NULL);
            for (u32 i = 0; i < attachment_count; i++) {
                vkDestroyImageView(vk->device, md->color_views[i], NULL);
                vkDestroyImage(vk->device, md->color_images[i], NULL);
                vkFreeMemory(vk->device, md->color_memories[i], NULL);
            }
            free(md);
            return fbo;
        }
    }

    u32 depth_idx = attachment_count;
    att_descs[depth_idx].format = VK_FORMAT_D32_SFLOAT;
    att_descs[depth_idx].samples = VK_SAMPLE_COUNT_1_BIT;
    att_descs[depth_idx].loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
    att_descs[depth_idx].storeOp = VK_ATTACHMENT_STORE_OP_STORE;
    att_descs[depth_idx].stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
    att_descs[depth_idx].stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
    att_descs[depth_idx].initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
    att_descs[depth_idx].finalLayout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_READ_ONLY_OPTIMAL;

    VkAttachmentReference depth_ref = {depth_idx, VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL};

    VkSubpassDescription sp = {0};
    sp.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
    sp.colorAttachmentCount = attachment_count;
    sp.pColorAttachments = color_refs;
    sp.pDepthStencilAttachment = &depth_ref;

    VkSubpassDependency dep = {0};
    dep.srcSubpass = VK_SUBPASS_EXTERNAL;
    dep.dstSubpass = 0;
    dep.srcStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT |
                       VK_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT;
    dep.dstStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT |
                       VK_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT;
    dep.dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT |
                        VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT;

    VkRenderPassCreateInfo rpci = {0};
    rpci.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
    rpci.attachmentCount = attachment_count + 1;
    rpci.pAttachments = att_descs;
    rpci.subpassCount = 1;
    rpci.pSubpasses = &sp;
    rpci.dependencyCount = 1;
    rpci.pDependencies = &dep;
    if (vkCreateRenderPass(vk->device, &rpci, NULL, &md->render_pass) != VK_SUCCESS) {
        LOG_FATAL("VK: failed to create MRT render pass");
        vkDestroyImageView(vk->device, md->depth_view, NULL);
        vkFreeMemory(vk->device, md->depth_memory, NULL);
        vkDestroyImage(vk->device, md->depth_image, NULL);
        for (u32 i = 0; i < attachment_count; i++) {
            vkDestroyImageView(vk->device, md->color_views[i], NULL);
            vkDestroyImage(vk->device, md->color_images[i], NULL);
            vkFreeMemory(vk->device, md->color_memories[i], NULL);
        }
        free(md);
        return fbo;
    }
    md->render_pass_load = vk_make_resume_render_pass(vk, &rpci);

    /* Create framebuffer. */
    VkImageView all_views[RHI_MRT_MAX_ATTACHMENTS + 1];
    for (u32 i = 0; i < attachment_count; i++) all_views[i] = md->color_views[i];
    all_views[attachment_count] = md->depth_view;

    VkFramebufferCreateInfo fbci = {0};
    fbci.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
    fbci.renderPass = md->render_pass;
    fbci.attachmentCount = attachment_count + 1;
    fbci.pAttachments = all_views;
    fbci.width = width;
    fbci.height = height;
    fbci.layers = 1;
    if (vkCreateFramebuffer(vk->device, &fbci, NULL, &md->framebuffer) != VK_SUCCESS) {
        LOG_FATAL("VK: failed to create MRT framebuffer");
        if (md->render_pass_load) vkDestroyRenderPass(vk->device, md->render_pass_load, NULL);
        vkDestroyRenderPass(vk->device, md->render_pass, NULL);
        vkDestroyImageView(vk->device, md->depth_view, NULL);
        vkFreeMemory(vk->device, md->depth_memory, NULL);
        vkDestroyImage(vk->device, md->depth_image, NULL);
        for (u32 i = 0; i < attachment_count; i++) {
            vkDestroyImageView(vk->device, md->color_views[i], NULL);
            vkDestroyImage(vk->device, md->color_images[i], NULL);
            vkFreeMemory(vk->device, md->color_memories[i], NULL);
        }
        free(md);
        return fbo;
    }

    /* Register FBO handle. */
    u32 fidx = rhi_alloc_slot(dev);
    dev->slots[fidx].ptr  = md;
    dev->slots[fidx].type = RHI_RES_MRT_FBO;
    fbo.fb = rhi_make_handle(fidx, dev->slots[fidx].generation);

    /* Register each color texture as a separate texture handle. */
    for (u32 i = 0; i < attachment_count; i++) {
        VKTextureData *td = calloc(1, sizeof(VKTextureData));
        if (!td) return fbo;
        u32 cidx = rhi_alloc_slot(dev);
        td->image = md->color_images[i];
        td->view = md->color_views[i];
        td->memory = md->color_memories[i];
        td->width = width;
        td->height = height;
        dev->slots[cidx].ptr  = td;
        dev->slots[cidx].type = RHI_RES_TEXTURE;
        fbo.color_tex[i] = rhi_make_handle(cidx, dev->slots[cidx].generation);
    }

    /* Register depth as a texture handle. */
    {
        VKTextureData *dd = calloc(1, sizeof(VKTextureData));
        if (!dd) return fbo;
        u32 didx = rhi_alloc_slot(dev);
        dd->image = md->depth_image;
        dd->view = md->depth_view;
        dd->memory = md->depth_memory;
        dd->width = width;
        dd->height = height;
        dev->slots[didx].ptr  = dd;
        dev->slots[didx].type = RHI_RES_TEXTURE;
        fbo.depth_tex = rhi_make_handle(didx, dev->slots[didx].generation);
    }

    return fbo;
}

void rhi_mrt_fbo_destroy(RHIDevice *dev, RHIMRTFBO *fbo) {
    if (!dev || !fbo) return;
    VKBackend *vk = vk_backend(dev);
    VKMRTFBOData *md = (VKMRTFBOData *)rhi_get_resource(dev, fbo->fb);
    if (!md) { memset(fbo, 0, sizeof(*fbo)); return; }
    if (vkDeviceWaitIdle(vk->device) != VK_SUCCESS)
        LOG_WARN("VK: vkDeviceWaitIdle failed in mrt_fbo_destroy");

    vkDestroyFramebuffer(vk->device, md->framebuffer, NULL);
    vkDestroyRenderPass(vk->device, md->render_pass, NULL);
    if (md->render_pass_load) vkDestroyRenderPass(vk->device, md->render_pass_load, NULL);
    for (u32 i = 0; i < md->attachment_count; i++) {
        vkDestroyImageView(vk->device, md->color_views[i], NULL);
        vkDestroyImage(vk->device, md->color_images[i], NULL);
        vkFreeMemory(vk->device, md->color_memories[i], NULL);
        /* Null the shared texture slot so device-destroy skips double-free. */
        if (rhi_handle_valid(fbo->color_tex[i])) {
            VKTextureData *td = (VKTextureData *)rhi_get_resource(dev, fbo->color_tex[i]);
            if (td) free(td);
            if (dev->slots[fbo->color_tex[i].index].ptr == td)
                dev->slots[fbo->color_tex[i].index].ptr = NULL;
            rhi_free_slot(dev, fbo->color_tex[i]);
        }
    }
    vkDestroyImageView(vk->device, md->depth_view, NULL);
    vkDestroyImage(vk->device, md->depth_image, NULL);
    vkFreeMemory(vk->device, md->depth_memory, NULL);
    if (rhi_handle_valid(fbo->depth_tex)) {
        VKTextureData *dd = (VKTextureData *)rhi_get_resource(dev, fbo->depth_tex);
        if (dd) free(dd);
        if (dev->slots[fbo->depth_tex.index].ptr == dd)
            dev->slots[fbo->depth_tex.index].ptr = NULL;
        rhi_free_slot(dev, fbo->depth_tex);
    }
    free(md);
    rhi_free_slot(dev, fbo->fb);
    memset(fbo, 0, sizeof(*fbo));
}

void rhi_mrt_fbo_bind(RHICmdBuffer *cmd, RHIMRTFBO *fbo) {
    (void)cmd;
    if (!fbo) return;
    VKBackend *vk = vk_backend(g_current_device);
    VKMRTFBOData *md = (VKMRTFBOData *)rhi_get_resource(g_current_device, fbo->fb);
    if (!md) return;

    if (vk->render_pass_active) {
        vkCmdEndRenderPass(vk->cmd_buffers[vk->current_frame]);
        vk->render_pass_active = false;
    }

    VkRenderPassBeginInfo rpi = {0};
    rpi.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
    rpi.renderPass = md->render_pass;
    rpi.framebuffer = md->framebuffer;
    rpi.renderArea.extent.width = fbo->width;
    rpi.renderArea.extent.height = fbo->height;

    VkClearValue clears[RHI_MRT_MAX_ATTACHMENTS + 1];
    memset(clears, 0, sizeof(clears));
    for (u32 i = 0; i < md->attachment_count; i++) {
        clears[i].color.float32[0] = 0.0f;
        clears[i].color.float32[1] = 0.0f;
        clears[i].color.float32[2] = 0.0f;
        clears[i].color.float32[3] = 0.0f;
    }
    clears[md->attachment_count].depthStencil.depth = 1.0f;
    rpi.clearValueCount = md->attachment_count + 1;
    rpi.pClearValues = clears;

    vkCmdBeginRenderPass(vk->cmd_buffers[vk->current_frame], &rpi,
        VK_SUBPASS_CONTENTS_INLINE);
    vk->render_pass_active = true;
    vk_record_pass(vk, md->render_pass_load, md->framebuffer, fbo->width, fbo->height, VK_FORMAT_UNDEFINED);

    VkViewport vp = {0, 0, (f32)fbo->width, (f32)fbo->height, 0, 1};
    vkCmdSetViewport(vk->cmd_buffers[vk->current_frame], 0, 1, &vp);
    VkRect2D sc = {{0, 0}, {fbo->width, fbo->height}};
    vkCmdSetScissor(vk->cmd_buffers[vk->current_frame], 0, 1, &sc);
    vk->vp_valid = false; vk->sc_valid = false;  /* R95-2: invalidate cache */
}

void rhi_mrt_fbo_unbind(RHICmdBuffer *cmd, u32 screen_w, u32 screen_h) {
    rhi_offscreen_fbo_unbind(cmd, screen_w, screen_h);
}

/* ======================================================================== */
/* Depth cubemap FBO (point-light shadow maps) -- VK backend                */
/* ======================================================================== */

RHICubemapDepthFBO rhi_cubemap_depth_fbo_create(RHIDevice *dev, u32 size) {
    RHICubemapDepthFBO fbo = {0};
    fbo.size = size;

    VKBackend *vk = vk_backend(dev);
    VKCubemapDepthFBOData *cd = calloc(1, sizeof(VKCubemapDepthFBOData));
    if (!cd) return fbo;
    cd->size = size;

    /* Create depth cubemap image (6 layers). */
    VkImageCreateInfo ci = {0};
    ci.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
    ci.flags = VK_IMAGE_CREATE_CUBE_COMPATIBLE_BIT;
    ci.imageType = VK_IMAGE_TYPE_2D;
    ci.format = VK_FORMAT_D32_SFLOAT;
    ci.extent.width = size;
    ci.extent.height = size;
    ci.extent.depth = 1;
    ci.mipLevels = 1;
    ci.arrayLayers = 6;
    ci.samples = VK_SAMPLE_COUNT_1_BIT;
    ci.tiling = VK_IMAGE_TILING_OPTIMAL;
    ci.usage = VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT | VK_IMAGE_USAGE_SAMPLED_BIT;
    ci.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
    ci.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
    if (vkCreateImage(vk->device, &ci, NULL, &cd->depth_image) != VK_SUCCESS) {
        LOG_FATAL("VK: failed to create cubemap depth image");
        free(cd);
        return fbo;
    }

    VkMemoryRequirements mr;
    vkGetImageMemoryRequirements(vk->device, cd->depth_image, &mr);
    VkMemoryAllocateInfo ai = {0};
    ai.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
    ai.allocationSize = mr.size;
    ai.memoryTypeIndex = vk_find_memory(vk, mr.memoryTypeBits,
        VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);
    if (vkAllocateMemory(vk->device, &ai, NULL, &cd->depth_memory) != VK_SUCCESS) {
        LOG_FATAL("VK: failed to allocate cubemap depth memory");
        vkDestroyImage(vk->device, cd->depth_image, NULL);
        free(cd);
        return fbo;
    }
    if (vkBindImageMemory(vk->device, cd->depth_image, cd->depth_memory, 0) != VK_SUCCESS) {
        LOG_FATAL("VK: failed to bind cubemap depth image memory");
        vkFreeMemory(vk->device, cd->depth_memory, NULL);
        vkDestroyImage(vk->device, cd->depth_image, NULL);
        free(cd);
        return fbo;
    }

    /* Full cubemap view (all 6 layers). */
    VkImageViewCreateInfo ivci = {0};
    ivci.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
    ivci.image = cd->depth_image;
    ivci.viewType = VK_IMAGE_VIEW_TYPE_CUBE;
    ivci.format = VK_FORMAT_D32_SFLOAT;
    ivci.subresourceRange.aspectMask = VK_IMAGE_ASPECT_DEPTH_BIT;
    ivci.subresourceRange.levelCount = 1;
    ivci.subresourceRange.layerCount = 6;
    if (vkCreateImageView(vk->device, &ivci, NULL, &cd->depth_view) != VK_SUCCESS) {
        LOG_FATAL("VK: failed to create cubemap depth image view");
        vkFreeMemory(vk->device, cd->depth_memory, NULL);
        vkDestroyImage(vk->device, cd->depth_image, NULL);
        free(cd);
        return fbo;
    }

    /* Per-face 2D views and framebuffers. */
    VkAttachmentDescription att = {0};
    att.format = VK_FORMAT_D32_SFLOAT;
    att.samples = VK_SAMPLE_COUNT_1_BIT;
    att.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
    att.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
    att.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
    att.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
    att.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
    att.finalLayout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_READ_ONLY_OPTIMAL;

    VkAttachmentReference depth_ref = {0, VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL};
    VkSubpassDescription sp = {0};
    sp.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
    sp.pDepthStencilAttachment = &depth_ref;

    /* Match vk->shadow_render_pass exactly (same depth-only attachment + this
     * dependency): the is_shadow_depth pipeline is created against that pass and
     * reused here, so render-pass compatibility (VUID-...-renderPass-02684)
     * requires identical subpass dependencies. src=FRAGMENT_SHADER also matches
     * the real hazard: the prior frame samples this cube depth before we
     * overwrite it. */
    VkSubpassDependency dep = {0};
    dep.srcSubpass = VK_SUBPASS_EXTERNAL;
    dep.dstSubpass = 0;
    dep.srcStageMask = VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT;
    dep.dstStageMask = VK_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT;
    dep.dstAccessMask = VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT;

    VkRenderPassCreateInfo rpci = {0};
    rpci.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
    rpci.attachmentCount = 1;
    rpci.pAttachments = &att;
    rpci.subpassCount = 1;
    rpci.pSubpasses = &sp;
    rpci.dependencyCount = 1;
    rpci.pDependencies = &dep;
    if (vkCreateRenderPass(vk->device, &rpci, NULL, &cd->render_pass) != VK_SUCCESS) {
        LOG_FATAL("VK: failed to create cubemap depth render pass");
        vkDestroyImageView(vk->device, cd->depth_view, NULL);
        vkFreeMemory(vk->device, cd->depth_memory, NULL);
        vkDestroyImage(vk->device, cd->depth_image, NULL);
        free(cd);
        return fbo;
    }
    /* LOAD-op twin so the GPU-driven indirect cull/compaction (a compute
     * dispatch issued mid-pass) can suspend and resume this depth pass. */
    cd->render_pass_load = vk_make_resume_render_pass(vk, &rpci);

    for (u32 face = 0; face < 6; face++) {
        VkImageViewCreateInfo fvci = {0};
        fvci.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
        fvci.image = cd->depth_image;
        fvci.viewType = VK_IMAGE_VIEW_TYPE_2D;
        fvci.format = VK_FORMAT_D32_SFLOAT;
        fvci.subresourceRange.aspectMask = VK_IMAGE_ASPECT_DEPTH_BIT;
        fvci.subresourceRange.levelCount = 1;
        fvci.subresourceRange.baseArrayLayer = face;
        fvci.subresourceRange.layerCount = 1;
        if (vkCreateImageView(vk->device, &fvci, NULL, &cd->face_views[face]) != VK_SUCCESS) {
            LOG_FATAL("VK: failed to create cubemap depth face view %u", face);
            for (u32 j = 0; j < face; j++) {
                vkDestroyFramebuffer(vk->device, cd->face_fbos[j], NULL);
                vkDestroyImageView(vk->device, cd->face_views[j], NULL);
            }
            if (cd->render_pass_load) vkDestroyRenderPass(vk->device, cd->render_pass_load, NULL);
            vkDestroyRenderPass(vk->device, cd->render_pass, NULL);
            vkDestroyImageView(vk->device, cd->depth_view, NULL);
            vkFreeMemory(vk->device, cd->depth_memory, NULL);
            vkDestroyImage(vk->device, cd->depth_image, NULL);
            free(cd);
            return fbo;
        }

        VkFramebufferCreateInfo fbci = {0};
        fbci.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
        fbci.renderPass = cd->render_pass;
        fbci.attachmentCount = 1;
        fbci.pAttachments = &cd->face_views[face];
        fbci.width = size;
        fbci.height = size;
        fbci.layers = 1;
        if (vkCreateFramebuffer(vk->device, &fbci, NULL, &cd->face_fbos[face]) != VK_SUCCESS) {
            LOG_FATAL("VK: failed to create cubemap depth face framebuffer %u", face);
            vkDestroyImageView(vk->device, cd->face_views[face], NULL);
            for (u32 j = 0; j < face; j++) {
                vkDestroyFramebuffer(vk->device, cd->face_fbos[j], NULL);
                vkDestroyImageView(vk->device, cd->face_views[j], NULL);
            }
            if (cd->render_pass_load) vkDestroyRenderPass(vk->device, cd->render_pass_load, NULL);
            vkDestroyRenderPass(vk->device, cd->render_pass, NULL);
            vkDestroyImageView(vk->device, cd->depth_view, NULL);
            vkFreeMemory(vk->device, cd->depth_memory, NULL);
            vkDestroyImage(vk->device, cd->depth_image, NULL);
            free(cd);
            return fbo;
        }
    }

    /* Register depth texture handle (cubemap). */
    VKTextureData *td = calloc(1, sizeof(VKTextureData));
    if (!td) return fbo;
    u32 tidx = rhi_alloc_slot(dev);
    td->image = cd->depth_image;
    td->view = cd->depth_view;
    td->memory = cd->depth_memory;
    td->width = size;
    td->height = size;
    dev->slots[tidx].ptr  = td;
    dev->slots[tidx].type = RHI_RES_TEXTURE;
    fbo.depth_tex = rhi_make_handle(tidx, dev->slots[tidx].generation);

    /* Register FBO handle. */
    u32 fidx = rhi_alloc_slot(dev);
    dev->slots[fidx].ptr  = cd;
    dev->slots[fidx].type = RHI_RES_CUBEMAP_DEPTH_FBO;
    fbo.fb = rhi_make_handle(fidx, dev->slots[fidx].generation);

    return fbo;
}

void rhi_cubemap_depth_fbo_destroy(RHIDevice *dev, RHICubemapDepthFBO *fbo) {
    if (!dev || !fbo) return;
    VKBackend *vk = vk_backend(dev);
    VKCubemapDepthFBOData *cd = (VKCubemapDepthFBOData *)rhi_get_resource(dev, fbo->fb);
    if (!cd) { memset(fbo, 0, sizeof(*fbo)); return; }
    if (vkDeviceWaitIdle(vk->device) != VK_SUCCESS)
        LOG_WARN("VK: vkDeviceWaitIdle failed in cubemap_depth_fbo_destroy");

    for (u32 face = 0; face < 6; face++) {
        vkDestroyFramebuffer(vk->device, cd->face_fbos[face], NULL);
        vkDestroyImageView(vk->device, cd->face_views[face], NULL);
    }
    vkDestroyRenderPass(vk->device, cd->render_pass, NULL);
    if (cd->render_pass_load)
        vkDestroyRenderPass(vk->device, cd->render_pass_load, NULL);
    vkDestroyImageView(vk->device, cd->depth_view, NULL);
    vkDestroyImage(vk->device, cd->depth_image, NULL);
    vkFreeMemory(vk->device, cd->depth_memory, NULL);

    /* Free the registered texture slot. */
    if (rhi_handle_valid(fbo->depth_tex)) {
        VKTextureData *td = (VKTextureData *)rhi_get_resource(dev, fbo->depth_tex);
        if (td) free(td);
        if (dev->slots[fbo->depth_tex.index].ptr == td)
            dev->slots[fbo->depth_tex.index].ptr = NULL;
        rhi_free_slot(dev, fbo->depth_tex);
    }
    free(cd);
    rhi_free_slot(dev, fbo->fb);
    memset(fbo, 0, sizeof(*fbo));
}

void rhi_cubemap_depth_fbo_bind_face(RHICmdBuffer *cmd, RHICubemapDepthFBO *fbo, u32 face) {
    (void)cmd;
    if (!fbo || face >= 6u) return;
    VKBackend *vk = vk_backend(g_current_device);
    VKCubemapDepthFBOData *cd = (VKCubemapDepthFBOData *)rhi_get_resource(g_current_device, fbo->fb);
    if (!cd) return;

    if (vk->render_pass_active) {
        vkCmdEndRenderPass(vk->cmd_buffers[vk->current_frame]);
        vk->render_pass_active = false;
    }

    VkRenderPassBeginInfo rpi = {0};
    rpi.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
    rpi.renderPass = cd->render_pass;
    rpi.framebuffer = cd->face_fbos[face];
    rpi.renderArea.extent.width = fbo->size;
    rpi.renderArea.extent.height = fbo->size;
    VkClearValue clear;
    memset(&clear, 0, sizeof(clear));
    clear.depthStencil.depth = 1.0f;
    rpi.clearValueCount = 1;
    rpi.pClearValues = &clear;

    vkCmdBeginRenderPass(vk->cmd_buffers[vk->current_frame], &rpi,
        VK_SUBPASS_CONTENTS_INLINE);
    vk->render_pass_active = true;
    /* The GPU-driven indirect path dispatches the cull/compaction compute inside
     * this depth pass; record the LOAD twin + this face's framebuffer so the
     * subsequent indirect draw can resume the pass instead of drawing outside it. */
    vk_record_pass(vk, cd->render_pass_load, cd->face_fbos[face],
                   fbo->size, fbo->size, VK_FORMAT_UNDEFINED);

    VkViewport vp = {0, 0, (f32)fbo->size, (f32)fbo->size, 0, 1};
    vkCmdSetViewport(vk->cmd_buffers[vk->current_frame], 0, 1, &vp);
    VkRect2D sc = {{0, 0}, {fbo->size, fbo->size}};
    vkCmdSetScissor(vk->cmd_buffers[vk->current_frame], 0, 1, &sc);
    vk->vp_valid = false; vk->sc_valid = false;  /* R95-2: invalidate cache */
}

void rhi_cubemap_depth_fbo_unbind(RHICmdBuffer *cmd, u32 screen_w, u32 screen_h) {
    rhi_offscreen_fbo_unbind(cmd, screen_w, screen_h);
}
