#include <vulkan/vulkan.h>
#include <rhi/rhi_backend_internal.h>
#include <rhi/rhi_native_vulkan.h>
#include <rhi/rhi_vk_probe.h>
#include <rhi/rhi_result_map.h>
#include <platform/platform_vk_surface.h>
#if defined(ENGINE_PLATFORM_ANDROID) && defined(ENGINE_ANDROID_NATIVE_WINDOW)
/* vk_shutdown keeps the ANativeWindow_release half of the reference pair
 * (the acquire moved into platform_vk_surface.c); this header declares it. */
#include <android/native_window.h>
#endif
#include <shaderc/shaderc.h>
#include <core/log.h>
#include <core/shader_io.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <stdatomic.h>

_Static_assert(VK_ERROR_DEVICE_LOST == -4, "vk result constant drift");
_Static_assert(VK_ERROR_OUT_OF_DATE_KHR == -1000001004, "vk result constant drift");
_Static_assert(VK_ERROR_SURFACE_LOST_KHR == -1000000000, "vk result constant drift");

/* Probe-header constant pinning: any drift between rhi_vk_probe.h and the
 * Vulkan/RHI enums fails here at compile time instead of on a GPU. */
_Static_assert(VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU == (int)VK_PROBE_DEVICE_TYPE_DISCRETE, "vk probe constant drift");
_Static_assert(VK_PHYSICAL_DEVICE_TYPE_INTEGRATED_GPU == (int)VK_PROBE_DEVICE_TYPE_INTEGRATED, "vk probe constant drift");
_Static_assert(VK_PHYSICAL_DEVICE_TYPE_VIRTUAL_GPU == (int)VK_PROBE_DEVICE_TYPE_VIRTUAL, "vk probe constant drift");
_Static_assert(VK_PHYSICAL_DEVICE_TYPE_CPU == (int)VK_PROBE_DEVICE_TYPE_CPU, "vk probe constant drift");
_Static_assert(VK_PHYSICAL_DEVICE_TYPE_OTHER == (int)VK_PROBE_DEVICE_TYPE_OTHER, "vk probe constant drift");
_Static_assert(VK_QUEUE_GRAPHICS_BIT == (int)VK_PROBE_QUEUE_GRAPHICS_BIT, "vk probe constant drift");
_Static_assert(VK_PRESENT_MODE_IMMEDIATE_KHR == (int)VK_PROBE_PRESENT_MODE_IMMEDIATE, "vk probe constant drift");
_Static_assert(VK_PRESENT_MODE_MAILBOX_KHR == (int)VK_PROBE_PRESENT_MODE_MAILBOX, "vk probe constant drift");
_Static_assert(VK_PRESENT_MODE_FIFO_KHR == (int)VK_PROBE_PRESENT_MODE_FIFO, "vk probe constant drift");
_Static_assert(VK_PRESENT_MODE_FIFO_RELAXED_KHR == (int)VK_PROBE_PRESENT_MODE_FIFO_RELAXED, "vk probe constant drift");
_Static_assert(VK_FORMAT_B8G8R8A8_SRGB == (int)VK_PROBE_FORMAT_B8G8R8A8_SRGB, "vk probe constant drift");
_Static_assert(VK_FORMAT_R8G8B8A8_SRGB == (int)VK_PROBE_FORMAT_R8G8B8A8_SRGB, "vk probe constant drift");
_Static_assert(VK_FORMAT_B8G8R8A8_UNORM == (int)VK_PROBE_FORMAT_B8G8R8A8_UNORM, "vk probe constant drift");
_Static_assert(VK_FORMAT_UNDEFINED == (int)VK_PROBE_FORMAT_UNDEFINED, "vk probe constant drift");
_Static_assert(VK_COLOR_SPACE_SRGB_NONLINEAR_KHR == (int)VK_PROBE_COLORSPACE_SRGB_NONLINEAR, "vk probe constant drift");
_Static_assert(RHI_FEATURE_RAY_TRACING_PIPELINE == VK_PROBE_FEATURE_RAY_TRACING_PIPELINE, "vk probe constant drift");
_Static_assert(RHI_FEATURE_RAY_QUERY == VK_PROBE_FEATURE_RAY_QUERY, "vk probe constant drift");
_Static_assert(RHI_FEATURE_ACCELERATION_STRUCTURE == VK_PROBE_FEATURE_ACCELERATION_STRUCTURE, "vk probe constant drift");

#define VK_MAX_FRAMES 2
#define VK_MAX_UNIFORMS 64

/* R438: in-process Vulkan validation message accounting (R437 follow-up).
 * The debug messenger callback counts severity>=warning messages so the
 * integration suite can hard-gate on zero; messages are still mirrored to
 * stderr to keep the previous layer-default observability. */
static _Atomic u32 g_validation_msg_count = 0;
static bool        g_validation_gate_active = false;

/* R550-E: explicit gate control replacing the R439 NDEBUG guard (whose
 * Release behavior left the test_vulkan VALIDATION GATE permanently
 * skipped). Activation rules, evaluated once at instance creation:
 *  - Debug builds (!NDEBUG): enabled, as before;
 *  - any build compiled with ENGINE_VK_VALIDATION: enabled;
 *  - otherwise: enabled only when the embedder calls
 *    rhi_vk_validation_set_enabled(true) before rhi init (test_vulkan does
 *    this; engine_demo does not, so Release demos keep zero messenger
 *    overhead).
 * The callback and counters stay compiled in every configuration so the
 * public API always links; the messenger is only registered when enabled. */
static int g_validation_enable_override = -1; /* -1: follow build default */

static bool vk_validation_enabled(void) {
    if (g_validation_enable_override >= 0) return g_validation_enable_override != 0;
#if defined(ENGINE_VK_VALIDATION) || !defined(NDEBUG)
    return true;
#else
    return false;
#endif
}

static VKAPI_ATTR VkBool32 VKAPI_CALL
vk_debug_utils_callback(VkDebugUtilsMessageSeverityFlagBitsEXT severity,
                        VkDebugUtilsMessageTypeFlagsEXT type,
                        const VkDebugUtilsMessengerCallbackDataEXT *data,
                        void *user_data) {
    (void)type; (void)user_data;
    if (severity >= VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT) {
        atomic_fetch_add_explicit(&g_validation_msg_count, 1u, memory_order_relaxed);
        fprintf(stderr, "VK VALIDATION: %s\n",
                (data && data->pMessage) ? data->pMessage : "(null)");
    }
    return VK_FALSE;
}

u32 rhi_vk_validation_message_count(void) {
    return atomic_load_explicit(&g_validation_msg_count, memory_order_relaxed);
}
void rhi_vk_validation_message_count_reset(void) {
    atomic_store_explicit(&g_validation_msg_count, 0u, memory_order_relaxed);
}
bool rhi_vk_validation_gate_active(void) {
    return g_validation_gate_active;
}
void rhi_vk_validation_set_enabled(bool enabled) {
    g_validation_enable_override = enabled ? 1 : 0;
}

/* ---- Internal types ---- */

typedef struct {
    VkShaderModule module;
    /* Owned copy of the compiled SPIR-V, so a pipeline can recreate its shader
     * modules when it needs a render-pass-format variant (the original shader
     * handle is usually destroyed right after pipeline creation). */
    u32   *spirv;
    usize  spirv_size;  /* bytes */
    /* Plan E Task 5: std430 push-constant reflection cached at create time —
     * the source does not have to outlive the shader. A 256B block of 4B
     * scalars bounds the member count at 64. */
    ShaderIOPushMember push_members[64];
    u32    push_member_count;
    bool   push_reflect_failed; /* source has a push block but reflection returned 0 */
} VKShaderData;

/* Plan E Task 5: merged vert+frag member tables fit in twice the per-shader cap. */
#define VK_PUSH_MERGE_MAX 128u

#define VK_INVALID_SET 0xFFu
#define VK_MAX_MIP_VIEWS 16u

typedef struct {
    VkPipelineLayout layout;
    VkPipeline        pipeline;
    u32               vertex_stride;
    bool              no_vertex_input;
    u32               push_range_count;
    VkPushConstantRange push_ranges[8];
    /* R417: clamped graphics push-constant range size from layout creation
     * (min(256, maxPushConstantsSize)); the flush clamps dirty ranges to it. */
    u32               push_range_size;
    u32               uniform_offsets[VK_MAX_UNIFORMS];
    u32               uniform_sizes[VK_MAX_UNIFORMS];
    u32               uniform_count;
    /* Plan E Task 5: merged vert/frag push-member reflection — the offset
     * authority for rhi_pipeline_get_uniform_location and the source table
     * rhi_pipeline_bindings_create materializes. */
    ShaderIOPushMember push_members[VK_PUSH_MERGE_MAX];
    u32               push_member_count;
    bool              push_reflect_failed;
    bool              uses_texel_buffer;
    bool              is_instanced;
    bool              is_compute;
    bool              uses_storage;
    /* R560: a skinned G-Buffer pipeline carries the ordinary
     * model/view/proj/prev-MVP block even though it uses a texel buffer for
     * joint poses. Without this flag `rhi_pipeline_get_uniform_location`
     * classifies it as clustered (uses_texel_buffer && !is_instanced) and
     * reports u_proj=-1, so the Vulkan skinned draw samples stale push data.
     * Must be checked before the clustered/non_clustered classification. */
    bool              skinned_gbuffer_layout;
    bool              terrain_layout;
    bool              water_layout;
    bool              combined_aa_layout;
    bool              combined_color_layout;
    bool              mrt_pipeline;
    /* Set indices for the auxiliary descriptor sets that the
     * generic command-stream binding helpers (image_texture,
     * texture_mip, uniform_buffer) target.  VK_INVALID_SET means
     * the pipeline layout does not declare that auxiliary set. */
    u8                storage_image_set;
    u8                sampler_mip_set;
    u8                ubo_set;
    /* R590: graphics storage-buffer set index (storage_vtx_layout) — the
     * graphics branch of rhi_cmd_bind_storage_buffer used to hardcode 0,
     * which only holds for texture-less pipelines (particles). A pipeline
     * combining textures/texel/storage (clustered-instanced) places the
     * storage set later; VK_INVALID_SET = no storage set. */
    u8                storage_set;
    u8                ray_query_set;
    /* Render-pass-format variant support (graphics only). A pipeline must be
     * render-pass-compatible with whatever FBO it is drawn into; since the same
     * logical pipeline (e.g. a post-fx blit) can be bound across targets of
     * different color formats, we lazily build per-format variants at bind time.
     * base_color_fmt is the format the base `pipeline` was created for;
     * VK_FORMAT_UNDEFINED marks depth-only/compute/MRT pipelines that are never
     * variant-ed. The SPIR-V copies + desc snapshot let us rebuild variants. */
    VkFormat          base_color_fmt;
    VkSampleCountFlagBits base_sample_count;
    /* R440: MRT pipelines (desc->mrt_attachment_count > 1) are built against
     * this per-pipeline render pass (formats match rhi_mrt_fbo_create's pass,
     * so the two are render-pass-compatible); VK_NULL_HANDLE otherwise. */
    VkRenderPass      mrt_render_pass;
    VkFormat          variant_fmt[8];
    VkSampleCountFlagBits variant_samples[8];
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
    u8            *map_shadow;  /* C-BUF-4: host shadow while a DEVICE_LOCAL buffer is mapped */
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
    /* R441: >1 for 2D texture arrays (material-indirect path); the view is
     * VK_IMAGE_VIEW_TYPE_2D_ARRAY covering all layers, mip_layout[0] tracks
     * the whole-array layout (layer-granular transitions are not tracked). */
    u32            layers;
} VKTextureData;

/* Forward declaration — full definition in the Cubemap section below. */
struct VKCubemapData {
    VkImage        image;
    VkDeviceMemory memory;
    VkImageView    view;
    VkFormat       format;
    u32            size;        /* face width == face height (R624) */
    u32            mip_levels;
    /* Lazily created per-face, per-mip storage views for compute write. */
    VkImageView    face_views[6][VK_MAX_MIP_VIEWS];
};
typedef struct VKCubemapData VKCubemapData;

/* RHI_RES_FRAMEBUFFER slots carry one of two payload types (shadow map /
 * offscreen FBO); a tag at offset 0 lets rhi_device_destroy tell them apart
 * without the public handle structs. */
#define VK_SHADOW_DATA_MAGIC 0x53484D50u
#define VK_FBO_DATA_MAGIC    0x4F46424Fu

typedef struct {
    u32            magic; /* VK_SHADOW_DATA_MAGIC */
    VkImage        depth_image;
    VkDeviceMemory depth_memory;
    VkImageView    depth_view;
    VkFramebuffer  framebuffer;
    VkRenderPass   render_pass;
    VkRenderPass   render_pass_load;  /* LOAD-op twin for compute suspend/resume */
} VKShadowData;

typedef struct {
    u32            magic; /* VK_FBO_DATA_MAGIC */
    VkImage        color_image;
    VkDeviceMemory color_memory;
    VkImageView    color_view;
    VkImage        msaa_color_image;
    VkDeviceMemory msaa_color_memory;
    VkImageView    msaa_color_view;
    VkImage        depth_image;
    VkDeviceMemory depth_memory;
    VkImageView    depth_view;
    VkImage        msaa_depth_image;
    VkDeviceMemory msaa_depth_memory;
    VkImageView    msaa_depth_view;
    VkFramebuffer  framebuffer;
    VkRenderPass   render_pass;
    VkRenderPass   render_pass_load;  /* LOAD-op twin for compute suspend/resume */
    VkFormat       color_fmt;         /* for render-pass-compatible pipeline variants */
    VkSampleCountFlagBits samples;
    f32            clear_color[4];    /* R619: caller-owned bind clear (create installs the default) */
} VKFBOData;

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
    VkAccelerationStructureKHR handle;
    VkBuffer storage_buffer;
    VkDeviceMemory storage_memory;
    VkDeviceSize storage_size;
} VKAccelerationStructureData;

static PFN_vkGetAccelerationStructureBuildSizesKHR g_vk_get_as_build_sizes;
static PFN_vkGetBufferDeviceAddress g_vk_get_buffer_device_address;
static PFN_vkCmdBuildAccelerationStructuresKHR g_vk_cmd_build_as;
static PFN_vkBuildAccelerationStructuresKHR g_vk_build_as_host;
static bool g_vk_host_as_supported;
static PFN_vkGetAccelerationStructureDeviceAddressKHR g_vk_get_as_address;

typedef struct {
    VkInstance       instance;
    VkDebugUtilsMessengerEXT debug_messenger; /* R438: VK_NULL_HANDLE unless debug build w/ ext */
    VkPhysicalDevice         physical;
    VkPhysicalDeviceProperties device_props;
    bool             feat_fill_mode_non_solid; /* wireframe (polygonMode=LINE) usable */
    bool             feat_independent_blend;   /* per-MRT-attachment blend state usable */
    bool             feat_draw_indirect_count;  /* vkCmdDraw*IndirectCount usable */
    bool             feat_multi_draw_indirect;  /* drawCount>1 in one indirect call */
    bool             feat_ray_tracing_pipeline;
    bool             feat_ray_query;
    bool             feat_acceleration_structure;
    bool             feat_partially_bound;      /* descriptorBindingPartiallyBound usable */
    bool             feat_uab_sampled_image;    /* descriptorBindingSampledImageUpdateAfterBind usable */
    bool             validation_layer_present;  /* R635: VK_LAYER_KHRONOS_validation loaded */
    bool             feat_depth_stencil_resolve;
    bool             has_device_fault; /* R576: VK_EXT_device_fault enabled */
    bool             device_lost;      /* R578: latched VK_ERROR_DEVICE_LOST — all
                                        * blocking waits fail fast once set (a
                                        * WDDM TDR reset can leave fences
                                        * permanently unsignaled, so unbounded
                                        * waits would hang the process). */
    VkResolveModeFlagBits depth_resolve_mode;
    VkDevice                 device;
    VkQueue          graphics_queue;
    VkQueue          present_queue;
    u32              graphics_family;
    u32              present_family;

    VkSurfaceKHR            surface;
    VkSwapchainKHR          swapchain;
    VkFormat                swap_format;
    bool                    swap_bgra; /* R430: screenshot swizzles BGRA->RGBA only when set */
    VkExtent2D              swap_extent;
    VkImage                *swap_images;
    VkImageView            *swap_views;
    VkFramebuffer          *framebuffers;
    u32                     swap_count;
    u32                     swap_view_count;
    u32                     framebuffer_count;
    u32                     render_semaphore_count;

    VkRenderPass  render_pass;
    VkImage       depth_image;
    VkDeviceMemory depth_memory;
    VkImageView   depth_view;

    VkCommandPool   cmd_pool;
    VkCommandBuffer cmd_buffers[VK_MAX_FRAMES];
    u32             cmd_buffer_count;

    VkSemaphore image_semaphores[VK_MAX_FRAMES];
    VkSemaphore *render_semaphores;
    VkFence     fences[VK_MAX_FRAMES];
    u32         current_frame;
    u32         image_index;
    bool        frame_started;
    bool        frame_submitted;

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
    VkDescriptorSetLayout    ray_query_layout;

#if defined(ENGINE_PLATFORM_ANDROID)
    struct ANativeWindow *native_window;
#endif

    VkPipeline current_pipeline;
    VKPipelineData *current_pipeline_data;
    RHIBuffer       bound_ubo;
    u32             bound_ubo_binding;
    VKPipelineData *ubo_bound_pipeline_data;
    /* Storage-buffer binds accumulate into ONE descriptor set per pipeline bind:
     * a compute shader (e.g. compact_draws.comp) reads bindings 0..3 from the
     * same set 0, so each rhi_cmd_bind_storage_buffer must write into the shared
     * set rather than allocate+bind a fresh single-binding set (which clobbers
     * the previously bound one, leaving bindings 0..2 unwritten -> 08114). */
    VkDescriptorSet storage_set;
    bool            storage_set_valid;
    /* R436: Storage-image binds accumulate into ONE descriptor set per
     * pipeline bind, mirroring storage_set above. Previously every
     * rhi_cmd_bind_image_texture allocated+bound a fresh single-binding set,
     * clobbering the previous one — so at most ONE image unit was valid per
     * dispatch (hit as VUID-vkCmdDispatch-None-08114 when the segmented Hi-Z
     * chain bound 4 mip images). Single-bind call sites are unaffected. */
    VkDescriptorSet image_set;
    bool            image_set_valid;
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
    VkSampleCountFlagBits active_sample_count;
    /* R94-2: viewport/scissor cache -- skip redundant vkCmdSetViewport/Scissor */
    f32           cached_vp_x, cached_vp_y, cached_vp_w, cached_vp_h;
    f32           cached_vp_min_d, cached_vp_max_d;
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
    VkSampleCountFlagBits pipe_rp_samples[8];
    u32          pipe_rp_count;

    shaderc_compiler_t shaderc_compiler;
    bool vsync;
} VKBackend;

static bool vk_blas_buffer_address(VKBackend *vk, RHIDevice *dev,
                                   RHIBuffer buffer, usize offset,
                                   VkDeviceAddress *out_address) {
    VKBufferData *data;
    VkBufferDeviceAddressInfo info = {0};
    if (vk == NULL || dev == NULL || out_address == NULL) return false;
    data = (VKBufferData *)rhi_get_resource_typed(dev, buffer, RHI_RES_BUFFER);
    if (data == NULL || g_vk_get_buffer_device_address == NULL) return false;
    info.sType = VK_STRUCTURE_TYPE_BUFFER_DEVICE_ADDRESS_INFO;
    info.buffer = data->buffer;
    *out_address = g_vk_get_buffer_device_address(vk->device, &info) + offset;
    return *out_address != 0;
}

static void vk_rebind_uniform_buffers(VKBackend *vk);

/* ---- Helpers ---- */

/* R175: One in-flight mip upload — reclaim on next upload / device shutdown
 * so async_loader_tick does not stall the main thread on every level. */
typedef struct {
    VKBackend      *owner_backend;
    VkFence         fence;
    VkBuffer        staging;
    VkDeviceMemory  staging_mem;
    VkCommandBuffer cb;
    VkCommandPool   pool;
    bool            pending;
} VKMipUploadPending;
static VKMipUploadPending g_mip_upload_pending;

/* R578: latch DEVICE_LOST the first time it is observed; every blocking
 * wait consults the latch and fails fast instead of blocking forever on a
 * post-TDR device (WDDM resets can leave fences permanently unsignaled). */
static void vk_note_result(VKBackend *vk, VkResult r) {
    if (r == VK_ERROR_DEVICE_LOST && !vk->device_lost) {
        vk->device_lost = true;
        LOG_ERROR("VK: device lost — latched; blocking waits now fail fast (R578)");
    }
}

static RHIResult vk_lifecycle_result(VkResult result) {
    return rhi_vk_result_to_lifecycle((i32)result);
}

/* R578: bounded fence wait. Healthy frames signal within milliseconds; the
 * 10 s bound plus a single retry tolerates extreme load, and a second
 * timeout means the GPU is gone (TDR detection itself takes 2-8 s), so the
 * device is latched lost rather than risk an unbounded hang. */
static VkResult vk_wait_fence(VKBackend *vk, VkFence fence) {
    if (vk->device_lost) return VK_ERROR_DEVICE_LOST;
    const u64 bound_ns = 10ull * 1000ull * 1000ull * 1000ull;
    VkResult r = vkWaitForFences(vk->device, 1, &fence, VK_TRUE, bound_ns);
    if (r == VK_TIMEOUT)
        r = vkWaitForFences(vk->device, 1, &fence, VK_TRUE, bound_ns);
    if (r == VK_TIMEOUT) {
        LOG_ERROR("VK: fence unsignaled after 20 s — treating device as lost (R578)");
        vk->device_lost = true;
        return VK_ERROR_DEVICE_LOST;
    }
    vk_note_result(vk, r);
    return r;
}

static void vk_mip_upload_reclaim(VKBackend *vk) {
    if (!g_mip_upload_pending.pending || !vk) return;
    if (g_mip_upload_pending.owner_backend != NULL &&
        g_mip_upload_pending.owner_backend != vk) {
        return;
    }
    if (g_mip_upload_pending.fence) {
        if (vk_wait_fence(vk, g_mip_upload_pending.fence) != VK_SUCCESS)
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

static bool vk_mip_upload_owned_by_other(VKBackend *vk) {
    return g_mip_upload_pending.pending &&
           g_mip_upload_pending.owner_backend != NULL &&
           g_mip_upload_pending.owner_backend != vk;
}

static VKBackend *vk_backend(RHIDevice *dev) {
    return (VKBackend *)dev->backend_data;
}

static VKBackend *vk_cmd_backend(RHICmdBuffer *cmd) {
    extern _Thread_local RHIDevice *g_current_device;
    VKBackend *vk;
    if (cmd == NULL || g_current_device == NULL) return NULL;
    vk = vk_backend(g_current_device);
    return vk != NULL && vk->frame_started && (void *)cmd == (void *)vk
               ? vk
               : NULL;
}

static bool vk_device_extension_present(VkPhysicalDevice physical,
                                        const char *extension_name) {
    u32 count = 0u;
    VkExtensionProperties *extensions;
    bool found = false;

    if (vkEnumerateDeviceExtensionProperties(physical, NULL, &count, NULL) != VK_SUCCESS ||
        count == 0u) {
        return false;
    }
    extensions = calloc(count, sizeof(*extensions));
    if (extensions == NULL) return false;
    if (vkEnumerateDeviceExtensionProperties(physical, NULL, &count, extensions) == VK_SUCCESS) {
        for (u32 i = 0u; i < count; ++i) {
            if (strcmp(extensions[i].extensionName, extension_name) == 0) {
                found = true;
                break;
            }
        }
    }
    free(extensions);
    return found;
}

bool rhi_backend_get_native_device(const RHIDevice *dev, RHINativeDevice *out) {
    const VKBackend *vk;
    if (dev == NULL || out == NULL) return false;
    vk = (const VKBackend *)dev->backend_data;
    if (vk == NULL || vk->instance == VK_NULL_HANDLE ||
        vk->physical == VK_NULL_HANDLE || vk->device == VK_NULL_HANDLE ||
        vk->graphics_queue == VK_NULL_HANDLE) {
        memset(out, 0, sizeof(*out));
        return false;
    }
    out->type = RHI_NATIVE_HANDLE_VULKAN;
    out->instance = (void *)(uintptr_t)vk->instance;
    out->physical_device = (void *)(uintptr_t)vk->physical;
    out->device = (void *)(uintptr_t)vk->device;
    out->graphics_queue = (void *)(uintptr_t)vk->graphics_queue;
    out->graphics_queue_family = vk->graphics_family;
    out->feature_bits = dev->capabilities.feature_bits;
    return true;
}

#ifdef ENGINE_RHI_TEST
static _Thread_local RHIDevice *g_vk_test_cache_owner;

void rhi_test_gl_cache_sync(RHIDevice *dev) {
    g_vk_test_cache_owner = dev;
}

RHIDevice *rhi_test_gl_cache_owner(void) {
    return g_vk_test_cache_owner;
}
#endif

static void vk_wait_frames(VKBackend *vk) {
    /* R578: sequential bounded waits — never block forever on a dead device. */
    for (u32 i = 0; i < VK_MAX_FRAMES; i++) {
        /* R588: never wait on the fence of the frame that is currently being
         * RECORDED — rhi_frame_begin reset it and it will not be submitted
         * until rhi_frame_end, so the wait can never succeed: it burns the
         * full 20 s bound and then falsely latches the device lost. Mid-frame
         * callers (one-off staging upload/download, deferred destroys) only
         * need prior in-flight frames drained; the recording frame's commands
         * execute after any immediately-submitted work by queue order. */
        if (vk->frame_started && i == vk->current_frame)
            continue;
        if (vk_wait_fence(vk, vk->fences[i]) != VK_SUCCESS) {
            LOG_WARN("VK: vkWaitForFences failed in wait_frames");
            return;
        }
    }
}

/* R576: device-fault forensics — after a DEVICE_LOST, report the driver's
 * fault description and faulting address ranges (VK_EXT_device_fault). */
static void vk_dump_device_fault(VKBackend *vk, const char *site) {
    /* R578: driver fault queries can BLOCK FOREVER on a post-TDR device
     * (observed: vkGetDeviceProcAddr hangs after WDDM reset, which also
     * explains why R576's dump never produced output on faulting runs). */
    if (vk->device_lost) return;
    if (!vk->has_device_fault) return;
    PFN_vkGetDeviceFaultInfoEXT get_fault =
        (PFN_vkGetDeviceFaultInfoEXT)vkGetDeviceProcAddr(vk->device, "vkGetDeviceFaultInfoEXT");
    if (!get_fault) return;
    VkDeviceFaultCountsEXT counts;
    memset(&counts, 0, sizeof(counts));
    counts.sType = VK_STRUCTURE_TYPE_DEVICE_FAULT_COUNTS_EXT;
    VkResult r0 = get_fault(vk->device, &counts, NULL);
    if (r0 != VK_SUCCESS) {
        LOG_ERROR("VK: device fault query at %s failed (%d)", site, (int)r0);
        return;
    }
    VkDeviceFaultAddressInfoEXT *addrs =
        calloc(counts.addressInfoCount ? counts.addressInfoCount : 1u, sizeof(*addrs));
    VkDeviceFaultVendorInfoEXT *vendors =
        calloc(counts.vendorInfoCount ? counts.vendorInfoCount : 1u, sizeof(*vendors));
    if (!addrs || !vendors) { free(addrs); free(vendors); return; }
    VkDeviceFaultInfoEXT fi;
    memset(&fi, 0, sizeof(fi));
    fi.sType = VK_STRUCTURE_TYPE_DEVICE_FAULT_INFO_EXT;
    fi.pAddressInfos = addrs;
    fi.pVendorInfos = vendors;
    if (get_fault(vk->device, &counts, &fi) == VK_SUCCESS) {
        LOG_ERROR("VK: device fault at %s: %s (address infos %u, vendor infos %u)",
                  site, fi.description, (unsigned)counts.addressInfoCount,
                  (unsigned)counts.vendorInfoCount);
        for (u32 i = 0; i < counts.addressInfoCount; i++) {
            LOG_ERROR("VK:   fault address 0x%llx precision %u bytes",
                      (unsigned long long)addrs[i].reportedAddress,
                      (unsigned)addrs[i].addressPrecision);
        }
    }
    free(addrs);
    free(vendors);
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

static bool g_vk_test_alloc_failure = false;
void rhi_vk_set_alloc_failure_for_test(bool enable) {
    g_vk_test_alloc_failure = enable;
}

static VkResult vk_allocate_memory(VKBackend *vk, VkMemoryAllocateInfo *info,
                                   VkDeviceMemory *out_memory) {
    if (g_vk_test_alloc_failure) return VK_ERROR_OUT_OF_HOST_MEMORY;
    if (!vk || !info || !out_memory || info->memoryTypeIndex == UINT32_MAX)
        return VK_ERROR_INITIALIZATION_FAILED;
    return vkAllocateMemory(vk->device, info, NULL, out_memory);
}

static bool vk_instance_extension_available(const char *name) {
    u32 count = 0u;
    if (!name || vkEnumerateInstanceExtensionProperties(NULL, &count, NULL) != VK_SUCCESS)
        return false;
    VkExtensionProperties *props = calloc(count ? count : 1u, sizeof(*props));
    if (!props) return false;
    if (vkEnumerateInstanceExtensionProperties(NULL, &count, props) != VK_SUCCESS) {
        free(props);
        return false;
    }
    bool found = false;
    for (u32 i = 0; i < count; i++) {
        if (strcmp(props[i].extensionName, name) == 0) {
            found = true;
            break;
        }
    }
    free(props);
    return found;
}

static bool vk_device_extension_available(VkPhysicalDevice physical,
                                          const char *name) {
    u32 count = 0u;
    if (physical == VK_NULL_HANDLE || !name ||
        vkEnumerateDeviceExtensionProperties(physical, NULL, &count, NULL) != VK_SUCCESS)
        return false;
    VkExtensionProperties *props = calloc(count ? count : 1u, sizeof(*props));
    if (!props) return false;
    if (vkEnumerateDeviceExtensionProperties(physical, NULL, &count, props) != VK_SUCCESS) {
        free(props);
        return false;
    }
    bool found = false;
    for (u32 i = 0; i < count; i++) {
        if (strcmp(props[i].extensionName, name) == 0) {
            found = true;
            break;
        }
    }
    free(props);
    return found;
}

/* Suitability is checked before selecting a device so a broken or compute-
 * only adapter cannot win selection and fail later during device creation. */
static bool vk_physical_device_suitable(VkPhysicalDevice physical,
                                        VkSurfaceKHR surface) {
    if (physical == VK_NULL_HANDLE || surface == VK_NULL_HANDLE ||
        !vk_device_extension_available(physical, VK_KHR_SWAPCHAIN_EXTENSION_NAME))
        return false;

    VkSurfaceCapabilitiesKHR caps;
    if (vkGetPhysicalDeviceSurfaceCapabilitiesKHR(physical, surface, &caps) != VK_SUCCESS)
        return false;

    u32 format_count = 0u;
    if (vkGetPhysicalDeviceSurfaceFormatsKHR(physical, surface, &format_count, NULL) != VK_SUCCESS ||
        format_count == 0u)
        return false;
    u32 mode_count = 0u;
    if (vkGetPhysicalDeviceSurfacePresentModesKHR(physical, surface, &mode_count, NULL) != VK_SUCCESS ||
        mode_count == 0u)
        return false;

    u32 queue_count = 0u;
    vkGetPhysicalDeviceQueueFamilyProperties(physical, &queue_count, NULL);
    if (queue_count == 0u)
        return false;
    VkQueueFamilyProperties *queues = calloc(queue_count, sizeof(*queues));
    if (!queues)
        return false;
    vkGetPhysicalDeviceQueueFamilyProperties(physical, &queue_count, queues);

    bool has_graphics = false;
    bool has_present = false;
    for (u32 q = 0u; q < queue_count; q++) {
        if (queues[q].queueCount > 0u &&
            (queues[q].queueFlags & VK_QUEUE_GRAPHICS_BIT) != 0)
            has_graphics = true;
        VkBool32 can_present = VK_FALSE;
        if (vkGetPhysicalDeviceSurfaceSupportKHR(physical, q, surface,
                                                  &can_present) != VK_SUCCESS) {
            free(queues);
            return false;
        }
        if (queues[q].queueCount > 0u && can_present)
            has_present = true;
    }
    free(queues);
    return has_graphics && has_present;
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
                           VkFramebuffer fb, u32 w, u32 h, VkFormat color_fmt,
                           VkSampleCountFlagBits samples) {
    vk->resume_render_pass = resume_rp;
    vk->resume_framebuffer = fb;
    vk->resume_extent.width = w;
    vk->resume_extent.height = h;
    vk->pass_suspended = false;
    vk->active_color_fmt = color_fmt;
    vk->active_sample_count = samples;
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

/* R635: SyncVal-clean external subpass dependency masks. The historical
 * masks (srcAccess=0, srcStage=COLOR_ATTACHMENT_OUTPUT only) left pass-begin
 * layout transitions and loadOp clears unsynchronized with the PREVIOUS
 * pass's attachment writes and fragment/compute/transfer reads — 20 SyncVal
 * hazards (WAW depth clear, RAW color/depth load) on every back-to-back
 * pass pair, latent on every driver. src side therefore covers every way the
 * attachments were last touched; dst side covers loadOp read + write + depth
 * test. Render-pass compatibility compares dependencyCount only (R440), so
 * widening the masks changes no compatibility class. */
static void vk_external_dep_color_depth(VkSubpassDependency *dep) {
    dep->srcSubpass = VK_SUBPASS_EXTERNAL;
    dep->dstSubpass = 0;
    dep->srcStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT
                      | VK_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT
                      | VK_PIPELINE_STAGE_LATE_FRAGMENT_TESTS_BIT
                      | VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT
                      | VK_PIPELINE_STAGE_COMPUTE_SHADER_BIT
                      | VK_PIPELINE_STAGE_TRANSFER_BIT;
    dep->srcAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT
                       | VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT
                       | VK_ACCESS_SHADER_READ_BIT
                       | VK_ACCESS_TRANSFER_WRITE_BIT;
    dep->dstStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT
                      | VK_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT
                      | VK_PIPELINE_STAGE_LATE_FRAGMENT_TESTS_BIT;
    dep->dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_READ_BIT
                       | VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT
                       | VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_READ_BIT
                       | VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT;
}

/* Depth-only variant (shadow map / point-shadow cube passes): prior use is
 * depth sampling (fragment) or a previous depth render of the same map. */
static void vk_external_dep_depth_only(VkSubpassDependency *dep) {
    dep->srcSubpass = VK_SUBPASS_EXTERNAL;
    dep->dstSubpass = 0;
    dep->srcStageMask = VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT
                      | VK_PIPELINE_STAGE_LATE_FRAGMENT_TESTS_BIT
                      | VK_PIPELINE_STAGE_TRANSFER_BIT;
    dep->srcAccessMask = VK_ACCESS_SHADER_READ_BIT
                       | VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT
                       | VK_ACCESS_TRANSFER_WRITE_BIT;
    dep->dstStageMask = VK_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT
                      | VK_PIPELINE_STAGE_LATE_FRAGMENT_TESTS_BIT;
    dep->dstAccessMask = VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_READ_BIT
                       | VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT;
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
    if (vkQueueSubmit(vk->graphics_queue, 1, &si, VK_NULL_HANDLE) != VK_SUCCESS) {
        LOG_FATAL("VK: vkQueueSubmit failed in init_image_layout");
        vk_dump_device_fault(vk, "init_image_layout");
    }
    if (vkQueueWaitIdle(vk->graphics_queue) != VK_SUCCESS) {
        LOG_FATAL("VK: vkQueueWaitIdle failed in init_image_layout");
        vk_dump_device_fault(vk, "init_image_layout");
    }
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

static bool vk_create_swapchain(VKBackend *vk, u32 w, u32 h) {
    VkSurfaceCapabilitiesKHR caps;
    VkResult caps_res = vkGetPhysicalDeviceSurfaceCapabilitiesKHR(vk->physical, vk->surface, &caps);
    int caps_ok = (caps_res == VK_SUCCESS);
    if (!caps_ok) {
        /* R575: some drivers fail ONLY this query (observed: AMD iGPU driver
         * 2.0.310 returning VK_ERROR_UNKNOWN while formats/present-modes
         * queries succeed). Fall back to safe defaults so the device stays
         * usable: requested extent, identity transform, double buffering. */
        LOG_WARN("VK: surface caps query failed (%d) — using fallback caps "
                 "(requested extent, identity transform, double buffer)",
                 (int)caps_res);
        memset(&caps, 0, sizeof(caps));
        caps.currentExtent.width = UINT32_MAX; /* take the clamp path below */
        caps.minImageExtent.width = 1;  caps.minImageExtent.height = 1;
        caps.maxImageExtent.width = 16384; caps.maxImageExtent.height = 16384;
        caps.minImageCount = 1;
        caps.currentTransform = VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR;
    }

    /* R430: validate the preferred format against the surface — the old
     * hardcoded B8G8R8A8_SRGB made vkCreateSwapchainKHR fail on surfaces
     * without it, and init carried on with a NULL swapchain. */
    VkColorSpaceKHR swap_colorspace = VK_COLOR_SPACE_SRGB_NONLINEAR_KHR;
    {
        u32 fmt_count = 0;
        if (vkGetPhysicalDeviceSurfaceFormatsKHR(vk->physical, vk->surface,
                                                 &fmt_count, NULL) != VK_SUCCESS) {
            LOG_FATAL("VK: surface format query failed");
            return false;
        }
        if (fmt_count == 0u) {
            LOG_FATAL("VK: surface reports no formats");
            return false;
        }
        VkSurfaceFormatKHR *formats = calloc(fmt_count, sizeof(VkSurfaceFormatKHR));
        if (!formats) { LOG_FATAL("VK: OOM surface formats"); return false; }
        if (vkGetPhysicalDeviceSurfaceFormatsKHR(vk->physical, vk->surface,
                                                 &fmt_count, formats) != VK_SUCCESS) {
            LOG_FATAL("VK: surface format list query failed");
            free(formats);
            return false;
        }
        VkProbeSurfaceFormat *probe_formats = calloc(fmt_count, sizeof(*probe_formats));
        if (!probe_formats) { LOG_FATAL("VK: OOM surface format probe"); free(formats); return false; }
        for (u32 i = 0; i < fmt_count; i++) {
            probe_formats[i].format = (u32)formats[i].format;
            probe_formats[i].color_space = (u32)formats[i].colorSpace;
        }
        VkProbeSurfaceFormat picked = { 0u, 0u };
        bool format_ok = vk_probe_choose_surface_format(probe_formats, fmt_count, &picked);
        free(probe_formats);
        free(formats);
        if (!format_ok) {
            LOG_FATAL("VK: surface reports no formats");
            return false;
        }
        if (picked.format != (u32)VK_FORMAT_B8G8R8A8_SRGB) {
            LOG_WARN("VK: B8G8R8A8_SRGB unsupported, falling back to surface format %d", (int)picked.format);
        }
        vk->swap_format = (VkFormat)picked.format;
        swap_colorspace = (VkColorSpaceKHR)picked.color_space;
        /* Screenshot readback swizzles BGRA->RGBA; RGBA-order formats need none. */
        vk->swap_bgra = (vk->swap_format == VK_FORMAT_B8G8R8A8_SRGB || vk->swap_format == VK_FORMAT_B8G8R8A8_UNORM);
    }

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
    u32 queue_families[2] = { vk->graphics_family, vk->present_family };
    sci.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
    sci.surface = vk->surface;
    sci.minImageCount = img_count;
    sci.imageFormat = vk->swap_format;
    sci.imageColorSpace = swap_colorspace; /* R430: matches the chosen format */
    sci.imageExtent = extent;
    sci.imageArrayLayers = 1;
    /* R430: TRANSFER_SRC — rhi_screenshot vkCmdCopyImageToBuffer reads a
     * swapchain image (VUID-00126). */
    sci.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT | VK_IMAGE_USAGE_TRANSFER_SRC_BIT;
    {
        if (vk->graphics_family != vk->present_family) {
            sci.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
            sci.queueFamilyIndexCount = 2u;
            sci.pQueueFamilyIndices = queue_families;
        } else {
            sci.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
        }
    }
    sci.preTransform = caps.currentTransform;
    sci.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
    VkPresentModeKHR present_mode = VK_PRESENT_MODE_FIFO_KHR;
    {
        u32 mode_count = 0;
        if (vkGetPhysicalDeviceSurfacePresentModesKHR(vk->physical, vk->surface,
                                                      &mode_count, NULL) != VK_SUCCESS) {
            LOG_FATAL("VK: present mode query failed");
            return false;
        }
        if (mode_count == 0u) {
            LOG_FATAL("VK: surface reports no present modes");
            return false;
        }
        VkPresentModeKHR *modes = calloc(mode_count, sizeof(VkPresentModeKHR));
        if (!modes) { LOG_FATAL("VK: OOM present modes"); return false; }
        if (vkGetPhysicalDeviceSurfacePresentModesKHR(vk->physical, vk->surface,
                                                      &mode_count, modes) != VK_SUCCESS) {
            LOG_FATAL("VK: present mode list query failed");
            free(modes);
            return false;
        }
        /* Prefer mailbox for interactive camera input while vsync is enabled:
         * it replaces stale queued frames without tearing. When vsync is off,
         * prefer immediate for the lowest input-to-photon latency. The full
         * fallback ordering lives in rhi_vk_probe.h. */
        u32 *probe_modes = calloc(mode_count, sizeof(*probe_modes));
        if (!probe_modes) { LOG_FATAL("VK: OOM present mode probe"); free(modes); return false; }
        for (u32 i = 0; i < mode_count; i++)
            probe_modes[i] = (u32)modes[i];
        present_mode = (VkPresentModeKHR)vk_probe_choose_present_mode(probe_modes, mode_count, vk->vsync);
        free(probe_modes);
        free(modes);
    }
    sci.presentMode = present_mode;
    LOG_INFO("VK: swapchain present mode=%s images=%u vsync=%s",
             present_mode == VK_PRESENT_MODE_MAILBOX_KHR ? "MAILBOX" :
             present_mode == VK_PRESENT_MODE_IMMEDIATE_KHR ? "IMMEDIATE" :
             "FIFO",
             img_count, vk->vsync ? "on" : "off");
    sci.clipped = VK_TRUE;
    sci.oldSwapchain = VK_NULL_HANDLE;

    VkResult res = vkCreateSwapchainKHR(vk->device, &sci, NULL, &vk->swapchain);
    if (res != VK_SUCCESS) {
        /* R430: propagate — init must not continue with a NULL swapchain. */
        LOG_FATAL("Failed to create swapchain: %d", res);
        return false;
    }

    if (vkGetSwapchainImagesKHR(vk->device, vk->swapchain, &vk->swap_count, NULL) != VK_SUCCESS) {
        LOG_FATAL("VK: vkGetSwapchainImagesKHR count query failed");
        return false;
    }
    if (vk->swap_count == 0u) {
        LOG_FATAL("VK: swapchain returned no images");
        vkDestroySwapchainKHR(vk->device, vk->swapchain, NULL);
        vk->swapchain = VK_NULL_HANDLE;
        return false;
    }
    vk->swap_images = calloc(vk->swap_count, sizeof(VkImage));
    if (!vk->swap_images) { LOG_FATAL("VK: OOM swap images"); return false; }
    vk->swap_views = calloc(vk->swap_count, sizeof(VkImageView));
    if (!vk->swap_views) { LOG_FATAL("VK: OOM swap views"); return false; }
    if (vkGetSwapchainImagesKHR(vk->device, vk->swapchain, &vk->swap_count, vk->swap_images) != VK_SUCCESS) {
        LOG_FATAL("VK: vkGetSwapchainImagesKHR image query failed");
        free(vk->swap_images);
        vk->swap_images = NULL;
        vk->swap_count = 0u;
        return false;
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
            vk->swap_view_count = i;
            return false;
        }
        vk->swap_view_count = i + 1u;
    }

    vk->render_semaphores = calloc(vk->swap_count, sizeof(VkSemaphore));
    if (!vk->render_semaphores) { LOG_FATAL("VK: OOM render semaphores"); return false; }
    for (u32 i = 0; i < vk->swap_count; i++) {
        VkSemaphoreCreateInfo sci2 = {0};
        sci2.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;
        if (vkCreateSemaphore(vk->device, &sci2, NULL, &vk->render_semaphores[i]) != VK_SUCCESS) {
            LOG_FATAL("VK: failed to create render semaphore %u", i);
            vk->render_semaphore_count = i;
            return false;
        }
        vk->render_semaphore_count = i + 1u;
    }
    return true;
}

static bool vk_create_depth(VKBackend *vk) {
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
        return false;
    }

    VkMemoryRequirements mem_req;
    vkGetImageMemoryRequirements(vk->device, vk->depth_image, &mem_req);

    VkMemoryAllocateInfo ai = {0};
    ai.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
    ai.allocationSize = mem_req.size;
    ai.memoryTypeIndex = vk_find_memory(vk, mem_req.memoryTypeBits,
                                         VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);
    if (ai.memoryTypeIndex == UINT32_MAX) {
        LOG_FATAL("VK: no device-local memory type for depth image");
        return false;
    }
    if (vk_allocate_memory(vk, &ai, &vk->depth_memory) != VK_SUCCESS) {
        LOG_FATAL("VK: failed to allocate depth memory");
        return false;
    }
    if (vkBindImageMemory(vk->device, vk->depth_image, vk->depth_memory, 0) != VK_SUCCESS) {
        LOG_FATAL("VK: failed to bind depth image memory");
        return false;
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
        return false;
    }
    return true;
}

static bool vk_create_framebuffers(VKBackend *vk) {
    /* R149: Guard against NULL swap_views — vk_create_swapchain may have failed
     * (e.g., vkCreateSwapchainKHR error, OOM on swap_images/swap_views), leaving
     * swap_count at a stale non-zero value while swap_views is NULL.
     * Without this check, vk->swap_views[i] dereferences NULL. */
    if (!vk->swap_views || vk->swap_count == 0 ||
        vk->depth_view == VK_NULL_HANDLE || vk->render_pass == VK_NULL_HANDLE)
        return false;
    vk->framebuffers = calloc(vk->swap_count, sizeof(VkFramebuffer));
    if (!vk->framebuffers) { LOG_FATAL("VK: OOM framebuffers"); return false; }
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
            vk->framebuffer_count = i;
            return false;
        }
        vk->framebuffer_count = i + 1u;
    }
    return true;
}

static bool vk_create_render_pass(VKBackend *vk) {
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
    vk_external_dep_color_depth(&dep);

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
        return false;
    }
    if (vk->render_pass_load != VK_NULL_HANDLE) {
        vkDestroyRenderPass(vk->device, vk->render_pass_load, NULL);
    }
    vk->render_pass_load = vk_make_resume_render_pass(vk, &ci);
    if (vk->render_pass_load == VK_NULL_HANDLE) {
        vkDestroyRenderPass(vk->device, vk->render_pass, NULL);
        vk->render_pass = VK_NULL_HANDLE;
        return false;
    }
    return true;
}

static void vk_cleanup_swapchain(VKBackend *vk) {
    if (vk->framebuffers) {
        for (u32 i = 0; i < vk->framebuffer_count; i++)
            if (vk->framebuffers[i] != VK_NULL_HANDLE)
                vkDestroyFramebuffer(vk->device, vk->framebuffers[i], NULL);
        free(vk->framebuffers);
        vk->framebuffers = NULL;
    }
    vk->framebuffer_count = 0u;
    if (vk->depth_view) { vkDestroyImageView(vk->device, vk->depth_view, NULL); vk->depth_view = VK_NULL_HANDLE; }
    if (vk->depth_image) { vkDestroyImage(vk->device, vk->depth_image, NULL); vk->depth_image = VK_NULL_HANDLE; }
    if (vk->depth_memory) { vkFreeMemory(vk->device, vk->depth_memory, NULL); vk->depth_memory = VK_NULL_HANDLE; }
    if (vk->swap_views) {
        for (u32 i = 0; i < vk->swap_view_count; i++)
            if (vk->swap_views[i] != VK_NULL_HANDLE)
                vkDestroyImageView(vk->device, vk->swap_views[i], NULL);
        free(vk->swap_views);
        vk->swap_views = NULL;
    }
    vk->swap_view_count = 0u;
    if (vk->swap_images) { free(vk->swap_images); vk->swap_images = NULL; }
    if (vk->render_semaphores) {
        for (u32 i = 0; i < vk->render_semaphore_count; i++)
            if (vk->render_semaphores[i] != VK_NULL_HANDLE)
                vkDestroySemaphore(vk->device, vk->render_semaphores[i], NULL);
        free(vk->render_semaphores);
        vk->render_semaphores = NULL;
    }
    vk->render_semaphore_count = 0u;
    vk->swap_count = 0u;
    if (vk->swapchain) { vkDestroySwapchainKHR(vk->device, vk->swapchain, NULL); vk->swapchain = VK_NULL_HANDLE; }
}

static RHIResult vk_recreate_swapchain(VKBackend *vk, u32 w, u32 h) {
    VkResult idle_result = vkDeviceWaitIdle(vk->device);
    if (idle_result != VK_SUCCESS) {
        LOG_WARN("VK: vkDeviceWaitIdle failed in recreate_swapchain");
        return vk_lifecycle_result(idle_result);
    }
    vk_cleanup_swapchain(vk);
    if (vk->render_pass_load != VK_NULL_HANDLE) {
        vkDestroyRenderPass(vk->device, vk->render_pass_load, NULL);
        vk->render_pass_load = VK_NULL_HANDLE;
    }
    if (vk->render_pass != VK_NULL_HANDLE) {
        vkDestroyRenderPass(vk->device, vk->render_pass, NULL);
        vk->render_pass = VK_NULL_HANDLE;
    }
    if (!vk_create_swapchain(vk, w, h)) {
        /* R430: cannot recover mid-run; do not continue with NULL swapchain. */
        LOG_ERROR("VK: swapchain recreation failed");
        vk_cleanup_swapchain(vk);
        return RHI_RESULT_UNAVAILABLE;
    }
    if (!vk_create_render_pass(vk) || !vk_create_depth(vk) ||
        !vk_create_framebuffers(vk)) {
        LOG_ERROR("VK: swapchain attachment recreation failed");
        vk_cleanup_swapchain(vk);
        if (vk->render_pass_load != VK_NULL_HANDLE) {
            vkDestroyRenderPass(vk->device, vk->render_pass_load, NULL);
            vk->render_pass_load = VK_NULL_HANDLE;
        }
        if (vk->render_pass != VK_NULL_HANDLE) {
            vkDestroyRenderPass(vk->device, vk->render_pass, NULL);
            vk->render_pass = VK_NULL_HANDLE;
        }
        return RHI_RESULT_UNAVAILABLE;
    }
    return RHI_RESULT_OK;
}

/* ---- Init/Shutdown ---- */

static void vk_shutdown(RHIDevice *dev);

static void vk_init_cleanup(RHIDevice *dev, VKBackend *vk) {
    if (!vk) return;
    if (dev) dev->backend_data = vk;
    vk_shutdown(dev);
}

static bool vk_init(RHIDevice *dev, void *window_native, void *display_native, u32 w, u32 h) {
    VKBackend *vk = calloc(1, sizeof(VKBackend));
    if (!vk) return false;
    dev->backend_data = vk;

    /* R430: swap_format is chosen from the surface's supported formats in
     * vk_create_swapchain (after surface + physical device exist). */

    VkApplicationInfo app = {0};
    app.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    app.pApplicationName = "PureCEngine";
    app.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
    app.pEngineName = "PureCEngine";
    app.engineVersion = VK_MAKE_VERSION(1, 0, 0);
    app.apiVersion = VK_API_VERSION_1_2;

    const char *layers[] = { "VK_LAYER_KHRONOS_validation" };
    const bool validation_on = vk_validation_enabled();
    const char *extensions[8];
    u32 ext_count = platform_vk_required_instance_extensions(
        NULL, extensions, (u32)(sizeof(extensions) / sizeof(extensions[0])));
    for (u32 i = 0; i < ext_count; i++) {
        if (!vk_instance_extension_available(extensions[i])) {
            LOG_FATAL("VK: required instance extension unavailable: %s", extensions[i]);
            vk_init_cleanup(dev, vk);
            return false;
        }
    }
    if (validation_on) {
        /* R438: enable VK_EXT_debug_utils when present so validation messages
         * can be counted in-process (test gate). Absence only disables the
         * gate. */
        u32 avail_count = 0;
        vkEnumerateInstanceExtensionProperties(NULL, &avail_count, NULL);
        VkExtensionProperties *avail = calloc(avail_count, sizeof(*avail));
        if (avail) {
            vkEnumerateInstanceExtensionProperties(NULL, &avail_count, avail);
            for (u32 i = 0; i < avail_count; i++) {
                if (strcmp(avail[i].extensionName, VK_EXT_DEBUG_UTILS_EXTENSION_NAME) == 0) {
                    extensions[ext_count++] = VK_EXT_DEBUG_UTILS_EXTENSION_NAME;
                    break;
                }
            }
            free(avail);
        }
    }

    /* R635: opt-in synchronization validation (BREAK_VK_SYNC_VALIDATION=1).
     * SyncVal catches WAR/RAW hazards between recorded commands — the class
     * behind the flaky gbuffer-factor failure (R633) — that the default core
     * checks cannot see. Off by default: it costs performance and its extra
     * scrutiny belongs to deliberate hardening runs, not every debug init. */
    VkValidationFeatureEnableEXT sync_enables[1];
    VkValidationFeaturesEXT validation_features = {0};
    const char *sync_env = getenv("BREAK_VK_SYNC_VALIDATION");
    const bool sync_validation_on = validation_on && sync_env && sync_env[0] == '1';
    if (sync_validation_on) {
        /* VK_EXT_validation_features is provided BY the validation layer, so
         * it never appears in the NULL (global) enumeration — query the
         * layer's own extension list (enabling a layer makes its instance
         * extensions enable-able). */
        u32 avail_count = 0;
        vkEnumerateInstanceExtensionProperties("VK_LAYER_KHRONOS_validation", &avail_count, NULL);
        VkExtensionProperties *avail = calloc(avail_count ? avail_count : 1u, sizeof(*avail));
        bool has_vf = false;
        if (avail) {
            vkEnumerateInstanceExtensionProperties("VK_LAYER_KHRONOS_validation", &avail_count, avail);
            for (u32 i = 0; i < avail_count; i++) {
                if (strcmp(avail[i].extensionName, VK_EXT_VALIDATION_FEATURES_EXTENSION_NAME) == 0) {
                    has_vf = true;
                    break;
                }
            }
            free(avail);
        }
        if (has_vf && ext_count < sizeof(extensions) / sizeof(extensions[0])) {
            extensions[ext_count++] = VK_EXT_VALIDATION_FEATURES_EXTENSION_NAME;
            sync_enables[0] = VK_VALIDATION_FEATURE_ENABLE_SYNCHRONIZATION_VALIDATION_EXT;
            validation_features.sType = VK_STRUCTURE_TYPE_VALIDATION_FEATURES_EXT;
            validation_features.enabledValidationFeatureCount = 1;
            validation_features.pEnabledValidationFeatures = sync_enables;
            LOG_INFO("VK: synchronization validation enabled (BREAK_VK_SYNC_VALIDATION=1)");
        } else {
            LOG_WARN("VK: BREAK_VK_SYNC_VALIDATION=1 but VK_EXT_validation_features "
                     "unavailable — sync validation off");
        }
    }

    VkInstanceCreateInfo ici = {0};
    ici.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    ici.pApplicationInfo = &app;
    ici.enabledExtensionCount = ext_count;
    ici.ppEnabledExtensionNames = extensions;
    if (validation_features.sType != 0)
        ici.pNext = &validation_features;
    ici.flags |= platform_vk_instance_create_flags(NULL);
    if (validation_on) {
        u32 layer_count = 0;
        vkEnumerateInstanceLayerProperties(&layer_count, NULL);
        VkLayerProperties *props = calloc(layer_count, sizeof(VkLayerProperties));
        if (!props) { LOG_FATAL("VK: OOM layer properties"); vk_init_cleanup(dev, vk); return false; }
        vkEnumerateInstanceLayerProperties(&layer_count, props);
        bool found = false;
        for (u32 i = 0; i < layer_count; i++) {
            if (strcmp(props[i].layerName, "VK_LAYER_KHRONOS_validation") == 0) { found = true; break; }
        }
        free(props);
        if (found) {
            ici.enabledLayerCount = 1;
            ici.ppEnabledLayerNames = layers;
            vk->validation_layer_present = true;
        } else {
            /* R635: without the layer the messenger counts nothing and the
             * test_vulkan VALIDATION GATE was vacuously green (macOS SDK
             * layer manifests are not on the loader search path by default).
             * Fail loudly so a missing layer is never mistaken for a pass. */
            LOG_WARN("VK: VK_LAYER_KHRONOS_validation not present — validation gate will count nothing");
        }
    }

    if (vkCreateInstance(&ici, NULL, &vk->instance) != VK_SUCCESS) {
        LOG_FATAL("Vulkan: failed to create instance");
        vk_init_cleanup(dev, vk);
        return false;
    }

    if (validation_on) {
        /* R438: register a debug messenger so validation messages are counted
         * in-process (test gate). Failure (missing layer/ext) degrades to no
         * gate with a warning — init must still succeed. */
        PFN_vkCreateDebugUtilsMessengerEXT create_dbg =
            (PFN_vkCreateDebugUtilsMessengerEXT)vkGetInstanceProcAddr(
                vk->instance, "vkCreateDebugUtilsMessengerEXT");
        if (create_dbg) {
            VkDebugUtilsMessengerCreateInfoEXT dci = {0};
            dci.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
            dci.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT |
                                  VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
            dci.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT |
                              VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT |
                              VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
            dci.pfnUserCallback = vk_debug_utils_callback;
            if (create_dbg(vk->instance, &dci, NULL, &vk->debug_messenger) == VK_SUCCESS) {
                /* R635: the gate is only meaningful with the layer attached —
                 * a bare debug_utils messenger receives no messages and used
                 * to print a vacuous "0 validation messages ✓". */
                g_validation_gate_active = vk->validation_layer_present;
            } else {
                vk->debug_messenger = VK_NULL_HANDLE;
                LOG_WARN("VK: debug messenger creation failed — validation gate disabled");
            }
        } else {
            LOG_WARN("VK: vkCreateDebugUtilsMessengerEXT unavailable — validation gate disabled");
        }
    }

    {
        /* vkGetInstanceProcAddr 是函数指针，API 参数是 void * —— 用 memcpy
         * 桥接（-Wpedantic 不允许直接强转）。 */
        PFN_vkGetInstanceProcAddr gpa_fn = vkGetInstanceProcAddr;
        void *gpa;
        u64 surface_bits = 0u;
        u64 surface_result;
        memcpy(&gpa, &gpa_fn, sizeof(gpa));
        surface_result = platform_vk_create_surface_handles(
            window_native, display_native, (void *)vk->instance, gpa,
            &surface_bits);
        if (surface_result != PLATFORM_VK_SURFACE_OK) {
            LOG_ERROR("Failed to create Vulkan surface via PAL (error %llu)",
                      (unsigned long long)surface_result);
            vk_init_cleanup(dev, vk);
            return false;
        }
        vk->surface = (VkSurfaceKHR)surface_bits;
#if defined(ENGINE_PLATFORM_ANDROID)
        /* The PAL acquired this window inside platform_vk_create_surface_handles
         * (success path only, with its own rollback on failure). Assign only on
         * success so every vk_init failure path leaves the field NULL and
         * vk_shutdown's guard skips the release — acquire/release stay paired. */
        vk->native_window = (struct ANativeWindow *)window_native;
#endif
    }

    u32 gpu_count = 0;
    if (vkEnumeratePhysicalDevices(vk->instance, &gpu_count, NULL) != VK_SUCCESS) {
        LOG_FATAL("VK: physical device enumeration failed");
        vk_init_cleanup(dev, vk);
        return false;
    }
    if (gpu_count == 0) { LOG_FATAL("Vulkan: no GPUs"); vk_init_cleanup(dev, vk); return false; }
    VkPhysicalDevice *gpus = calloc(gpu_count, sizeof(VkPhysicalDevice));
    if (!gpus) { LOG_FATAL("VK: OOM GPU list"); vk_init_cleanup(dev, vk); return false; }
    if (vkEnumeratePhysicalDevices(vk->instance, &gpu_count, gpus) != VK_SUCCESS) {
        LOG_FATAL("VK: physical device enumeration failed");
        free(gpus);
        vk_init_cleanup(dev, vk);
        return false;
    }
    /* R574/R576 (ROBUSTNESS): select only a GPU with a usable surface,
     * graphics/present queues, and VK_KHR_swapchain. On hybrid-graphics
     * laptops an iGPU driver can fail the caps query while another adapter
     * remains usable; never select a candidate that will fail later. */
    vk->physical = VK_NULL_HANDLE;
    /* R575/R576 (ENV OVERRIDE): a requested GPU is still subject to the same
     * suitability checks. Invalid or unsuitable pins fail explicitly rather
     * than silently selecting a different adapter. */
    {
        const char *env_idx = getenv("RE_VK_DEVICE_INDEX");
        if (env_idx && env_idx[0]) {
            char *end = NULL;
            errno = 0;
            unsigned long parsed = strtoul(env_idx, &end, 10);
            if (errno == ERANGE || end == env_idx || *end != '\0' ||
                parsed > UINT32_MAX || parsed >= gpu_count) {
                LOG_FATAL("VK: invalid RE_VK_DEVICE_INDEX: %s", env_idx);
                free(gpus);
                vk_init_cleanup(dev, vk);
                return false;
            }
            if (!vk_physical_device_suitable(gpus[parsed], vk->surface)) {
                LOG_FATAL("VK: requested GPU is not suitable: %lu", parsed);
                free(gpus);
                vk_init_cleanup(dev, vk);
                return false;
            }
            vk->physical = gpus[parsed];
        }
    }
    if (vk->physical == VK_NULL_HANDLE) {
        /* Adapter scoring lives in rhi_vk_probe.h (discrete > integrated >
         * virtual > software > other; api_version then index tie-break).
         * Suitability (R574/R576) is precomputed per candidate so an adapter
         * that would fail later never wins the score. */
        VkProbeAdapterInfo *probes = calloc(gpu_count, sizeof(*probes));
        if (!probes) { LOG_FATAL("VK: OOM adapter probe list"); free(gpus); vk_init_cleanup(dev, vk); return false; }
        for (u32 i = 0; i < gpu_count; i++) {
            VkPhysicalDeviceProperties props = {0};
            vkGetPhysicalDeviceProperties(gpus[i], &props);
            probes[i].device_type = (u32)props.deviceType;
            probes[i].api_version = props.apiVersion;
            probes[i].suitable = vk_physical_device_suitable(gpus[i], vk->surface);
        }
        i32 picked = vk_probe_select_adapter(probes, gpu_count);
        free(probes);
        if (picked >= 0)
            vk->physical = gpus[picked];
    }
    if (vk->physical == VK_NULL_HANDLE) {
        LOG_FATAL("VK: no suitable Vulkan GPU found");
        free(gpus);
        vk_init_cleanup(dev, vk);
        return false;
    }
    free(gpus);
    vkGetPhysicalDeviceProperties(vk->physical, &vk->device_props);
    VkPhysicalDeviceProperties2 device_props2 = {0};
    device_props2.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PROPERTIES_2;
    VkPhysicalDeviceDepthStencilResolveProperties depth_resolve_props = {0};
    depth_resolve_props.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_DEPTH_STENCIL_RESOLVE_PROPERTIES;
    device_props2.pNext = &depth_resolve_props;
    vkGetPhysicalDeviceProperties2(vk->physical, &device_props2);
    vk->feat_depth_stencil_resolve =
        depth_resolve_props.supportedDepthResolveModes != 0;
    if (depth_resolve_props.supportedDepthResolveModes & VK_RESOLVE_MODE_SAMPLE_ZERO_BIT)
        vk->depth_resolve_mode = VK_RESOLVE_MODE_SAMPLE_ZERO_BIT;
    else if (depth_resolve_props.supportedDepthResolveModes & VK_RESOLVE_MODE_AVERAGE_BIT)
        vk->depth_resolve_mode = VK_RESOLVE_MODE_AVERAGE_BIT;
    else if (depth_resolve_props.supportedDepthResolveModes & VK_RESOLVE_MODE_MIN_BIT)
        vk->depth_resolve_mode = VK_RESOLVE_MODE_MIN_BIT;
    else if (depth_resolve_props.supportedDepthResolveModes & VK_RESOLVE_MODE_MAX_BIT)
        vk->depth_resolve_mode = VK_RESOLVE_MODE_MAX_BIT;
    dev->capabilities.backend = RHI_BACKEND_VULKAN;
    dev->capabilities.scissor_supported = true;
    dev->capabilities.present_target_preserved = false;
    dev->capabilities.present_damage_supported = false;
    dev->capabilities.present_buffer_age_supported = false;
    dev->capabilities.color_sample_counts = rhi_sample_count_bit(1u);
    dev->capabilities.depth_sample_counts = rhi_sample_count_bit(1u);
    for (u32 samples = 2u; samples <= 64u; samples <<= 1u) {
        VkSampleCountFlagBits flag = (VkSampleCountFlagBits)samples;
        if ((vk->device_props.limits.framebufferColorSampleCounts & flag) != 0) {
            dev->capabilities.color_sample_counts |=
                rhi_sample_count_bit(samples);
        }
        if ((vk->device_props.limits.framebufferDepthSampleCounts & flag) != 0)
            dev->capabilities.depth_sample_counts |= rhi_sample_count_bit(samples);
    }
    dev->capabilities.surface_sample_count = 1u;
    dev->capabilities.color_resolve_supported =
        (dev->capabilities.color_sample_counts & ~rhi_sample_count_bit(1u)) != 0u;
    dev->capabilities.depth_resolve_supported = vk->feat_depth_stencil_resolve;
    /* Record extension availability first. Capability bits are published only
     * after the matching device features have been enabled successfully. */
    vk->feat_ray_tracing_pipeline =
        vk_device_extension_present(vk->physical, VK_KHR_ACCELERATION_STRUCTURE_EXTENSION_NAME) &&
        vk_device_extension_present(vk->physical, VK_KHR_RAY_TRACING_PIPELINE_EXTENSION_NAME);
    vk->feat_ray_query =
        vk_device_extension_present(vk->physical, VK_KHR_RAY_QUERY_EXTENSION_NAME);
    /* 迁移期只探测不消费：dynamic rendering / synchronization2。 */
    dev->capabilities.dynamic_rendering_supported =
        VK_API_VERSION_MAJOR(vk->device_props.apiVersion) > 1u ||
        (VK_API_VERSION_MAJOR(vk->device_props.apiVersion) == 1u &&
         VK_API_VERSION_MINOR(vk->device_props.apiVersion) >= 3u) ||
        vk_device_extension_present(vk->physical, VK_KHR_DYNAMIC_RENDERING_EXTENSION_NAME);
    dev->capabilities.synchronization2_supported =
        VK_API_VERSION_MAJOR(vk->device_props.apiVersion) > 1u ||
        (VK_API_VERSION_MAJOR(vk->device_props.apiVersion) == 1u &&
         VK_API_VERSION_MINOR(vk->device_props.apiVersion) >= 3u) ||
        vk_device_extension_present(vk->physical, VK_KHR_SYNCHRONIZATION_2_EXTENSION_NAME);
    dev->capabilities.feature_bits = 0u;
    /* 计划 E capability contract（test_vulkan tv_test_capability_contract 消费）。 */
    dev->capabilities.push_constants_supported = true;
    dev->capabilities.max_push_constant_size =
        (u32)vk->device_props.limits.maxPushConstantsSize;
    if (dev->capabilities.max_push_constant_size < 128u) {
        /* 下限钳制告警：Vulkan 规范保证 >=128；低于下限按不支持处理，不伪装。 */
        LOG_WARN("VK: maxPushConstantsSize %u below the 128-byte floor",
                 dev->capabilities.max_push_constant_size);
        dev->capabilities.max_push_constant_size = 0u;
        dev->capabilities.push_constants_supported = false;
    }
    dev->capabilities.hiz_supported = true;
    dev->capabilities.compute_supported = true;
    dev->capabilities.indirect_draw_supported = true;
    dev->capabilities.shader_variant = (u32)RHI_SHADER_VARIANT_GLSL_VK;
    LOG_INFO("Vulkan GPU: %s (push constants: %u bytes, UBO alignment: %lu)",
             vk->device_props.deviceName,
             vk->device_props.limits.maxPushConstantsSize,
             (unsigned long)vk->device_props.limits.minUniformBufferOffsetAlignment);

    u32 queue_count = 0;
    vkGetPhysicalDeviceQueueFamilyProperties(vk->physical, &queue_count, NULL);
    VkQueueFamilyProperties *queues = calloc(queue_count, sizeof(VkQueueFamilyProperties));
    if (!queues) { LOG_FATAL("VK: OOM queue list"); vk_init_cleanup(dev, vk); return false; }
    vkGetPhysicalDeviceQueueFamilyProperties(vk->physical, &queue_count, queues);
    u32 *family_flags = calloc(queue_count, sizeof(*family_flags));
    bool *family_present = calloc(queue_count, sizeof(*family_present));
    if (!family_flags || !family_present) {
        LOG_FATAL("VK: OOM queue probe arrays");
        free(family_flags);
        free(family_present);
        free(queues);
        vk_init_cleanup(dev, vk);
        return false;
    }
    for (u32 i = 0; i < queue_count; i++) {
        family_flags[i] = (u32)queues[i].queueFlags;
        VkBool32 present = VK_FALSE;
        if (vkGetPhysicalDeviceSurfaceSupportKHR(vk->physical, i, vk->surface,
                                                  &present) != VK_SUCCESS) {
            free(family_flags);
            free(family_present);
            free(queues);
            LOG_FATAL("Vulkan: surface support query failed");
            vk_init_cleanup(dev, vk);
            return false;
        }
        family_present[i] = present == VK_TRUE;
    }
    free(queues);
    /* Combined graphics+present family first (EXCLUSIVE swapchain sharing);
     * selection rules live in rhi_vk_probe.h. */
    if (!vk_probe_choose_queue_families(family_flags, family_present, queue_count,
                                        &vk->graphics_family, &vk->present_family)) {
        free(family_flags);
        free(family_present);
        LOG_FATAL("Vulkan: no suitable queue family");
        vk_init_cleanup(dev, vk);
        return false;
    }
    free(family_flags);
    free(family_present);

    f32 queue_priority = 1.0f;
    VkDeviceQueueCreateInfo queue_infos[2] = {0};
    u32 queue_info_count = 1u;
    queue_infos[0].sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
    queue_infos[0].queueFamilyIndex = vk->graphics_family;
    queue_infos[0].queueCount = 1;
    queue_infos[0].pQueuePriorities = &queue_priority;
    if (vk->present_family != vk->graphics_family) {
        queue_info_count = 2u;
        queue_infos[1] = queue_infos[0];
        queue_infos[1].queueFamilyIndex = vk->present_family;
    }

    /* Enable only features we actually use and that the device supports.
     * drawIndirectCount is a Vulkan 1.2 feature queried via the feature2 chain;
     * the GPU-driven indirect pipeline calls vkCmdDrawIndexedIndirectCount. */
    VkPhysicalDeviceVulkan11Features supported_vk11 = {0};
    supported_vk11.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_1_FEATURES;
    VkPhysicalDeviceVulkan12Features supported_vk12 = {0};
    supported_vk12.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_2_FEATURES;
    VkPhysicalDeviceAccelerationStructureFeaturesKHR supported_accel = {0};
    supported_accel.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_ACCELERATION_STRUCTURE_FEATURES_KHR;
    VkPhysicalDeviceRayTracingPipelineFeaturesKHR supported_rt_pipeline = {0};
    supported_rt_pipeline.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_RAY_TRACING_PIPELINE_FEATURES_KHR;
    VkPhysicalDeviceRayQueryFeaturesKHR supported_ray_query = {0};
    supported_ray_query.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_RAY_QUERY_FEATURES_KHR;
    supported_vk11.pNext = &supported_vk12;
    supported_vk12.pNext = &supported_accel;
    supported_accel.pNext = &supported_rt_pipeline;
    supported_rt_pipeline.pNext = &supported_ray_query;
    VkPhysicalDeviceFeatures2 supported_features2 = {0};
    supported_features2.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FEATURES_2;
    supported_features2.pNext = &supported_vk11;
    vkGetPhysicalDeviceFeatures2(vk->physical, &supported_features2);
    dev->capabilities.feature_bits = 0u;

    VkPhysicalDeviceFeatures enabled_features = {0};
    if (supported_features2.features.fillModeNonSolid) {
        enabled_features.fillModeNonSolid = VK_TRUE; /* wireframe debug pipelines */
        vk->feat_fill_mode_non_solid = true;
    }
    if (supported_features2.features.independentBlend) {
        enabled_features.independentBlend = VK_TRUE;
        vk->feat_independent_blend = true;
    }
    /* R169: Allow VS/GS/TS to write PointSize (particle POINT_LIST sprites). */
    if (supported_features2.features.shaderTessellationAndGeometryPointSize) {
        enabled_features.shaderTessellationAndGeometryPointSize = VK_TRUE;
    }
    /* R635: multiDrawIndirect is required for vkCmdDraw*Indirect with
     * drawCount>1 — previously relied on driver leniency (validation error on
     * every indirect batch; strict drivers may ignore the extra draws). When
     * absent the indirect entry points fall back to per-draw loops. */
    if (supported_features2.features.multiDrawIndirect) {
        enabled_features.multiDrawIndirect = VK_TRUE;
        vk->feat_multi_draw_indirect = true;
    }

    VkPhysicalDeviceVulkan12Features enabled_vk12 = {0};
    enabled_vk12.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_2_FEATURES;
    if (supported_vk12.drawIndirectCount) {
        enabled_vk12.drawIndirectCount = VK_TRUE;
        vk->feat_draw_indirect_count = true;
    }
    /* R441: gl_BaseInstance(ARB) in the material-array forward shaders declares
     * the SPIR-V DrawParameters capability — needs the 1.1 feature enabled.
     * If the driver lacks it, shader-module creation fails and the array
     * pipeline stays invalid, auto-disabling the path (R437 fallback). */
    VkPhysicalDeviceVulkan11Features enabled_vk11 = {0};
    enabled_vk11.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_1_FEATURES;
    enabled_vk11.pNext = &enabled_vk12;
    if (supported_vk11.shaderDrawParameters) {
        enabled_vk11.shaderDrawParameters = VK_TRUE;
    }
    /* Partially-bound descriptors let one shared material layout serve both the
     * forward shaders (binding 5 = single u_ssao) and deferred_light_vk.frag
     * (binding 5 = u_point_shadow_cubes[4]); each shader only needs the array
     * elements it actually samples to be valid. */
    if (supported_vk12.descriptorBindingPartiallyBound) {
        enabled_vk12.descriptorBindingPartiallyBound = VK_TRUE;
        vk->feat_partially_bound = true;
    }
    /* R635: UPDATE_AFTER_BIND on the two shadow-cube array bindings moves them
     * out of the (possibly tiny — spec minimum 16, MoltenVK exactly 16)
     * maxPerStageDescriptorSamplers budget into the update-after-bind budget
     * (1024 on MoltenVK); the material layout is otherwise non-conformant on
     * any driver reporting the spec-minimum sampler limit. */
    if (supported_vk12.descriptorBindingSampledImageUpdateAfterBind) {
        enabled_vk12.descriptorBindingSampledImageUpdateAfterBind = VK_TRUE;
        vk->feat_uab_sampled_image = true;
    }

    const char *dev_extensions[8];
    u32 dev_extension_count = 0u;
    if (!vk_device_extension_available(vk->physical, VK_KHR_SWAPCHAIN_EXTENSION_NAME)) {
        LOG_FATAL("VK: required device extension unavailable: %s",
                  VK_KHR_SWAPCHAIN_EXTENSION_NAME);
        vk_init_cleanup(dev, vk);
        return false;
    }
    dev_extensions[dev_extension_count++] = VK_KHR_SWAPCHAIN_EXTENSION_NAME;
    bool as_extensions = supported_vk12.bufferDeviceAddress &&
        supported_accel.accelerationStructure &&
        vk_device_extension_available(
        vk->physical, VK_KHR_ACCELERATION_STRUCTURE_EXTENSION_NAME) &&
        vk_device_extension_available(vk->physical,
                                      VK_KHR_DEFERRED_HOST_OPERATIONS_EXTENSION_NAME);
    if (as_extensions) {
        enabled_vk12.bufferDeviceAddress = VK_TRUE;
        dev_extensions[dev_extension_count++] = VK_KHR_DEFERRED_HOST_OPERATIONS_EXTENSION_NAME;
        dev_extensions[dev_extension_count++] = VK_KHR_ACCELERATION_STRUCTURE_EXTENSION_NAME;
    }
    bool rt_pipeline_extensions = vk->feat_ray_tracing_pipeline && as_extensions &&
        vk_device_extension_available(vk->physical,
                                      VK_KHR_PIPELINE_LIBRARY_EXTENSION_NAME);
    if (rt_pipeline_extensions) {
        dev_extensions[dev_extension_count++] = VK_KHR_PIPELINE_LIBRARY_EXTENSION_NAME;
        dev_extensions[dev_extension_count++] = VK_KHR_RAY_TRACING_PIPELINE_EXTENSION_NAME;
    }
    if (vk->feat_ray_query && as_extensions)
        dev_extensions[dev_extension_count++] = VK_KHR_RAY_QUERY_EXTENSION_NAME;
#if defined(ENGINE_PLATFORM_MACOS) || defined(ENGINE_PLATFORM_IOS)
    /* Mandatory on MoltenVK: a portability driver must have its subset
     * extension enabled whenever the device advertises it. */
    if (vk_device_extension_available(vk->physical, "VK_KHR_portability_subset"))
        dev_extensions[dev_extension_count++] = "VK_KHR_portability_subset";
    else {
        LOG_FATAL("VK: required device extension unavailable: VK_KHR_portability_subset");
        vk_init_cleanup(dev, vk);
        return false;
    }
#endif
    /* R576: enable VK_EXT_device_fault when offered (vendor fault forensics —
     * after a DEVICE_LOST, vkGetDeviceFaultInfoEXT reports the faulting
     * pipeline-stage/address info; see vk_dump_device_fault). */
    {
        u32 avail = 0;
        vk->has_device_fault = false;
        vk->device_lost = false; /* R578 */
        if (vkEnumerateDeviceExtensionProperties(vk->physical, NULL, &avail, NULL) != VK_SUCCESS) {
            LOG_WARN("VK: optional device extension query failed");
            avail = 0u;
        }
        VkExtensionProperties *props = calloc(avail ? avail : 1u, sizeof(*props));
        if (props) {
            if (vkEnumerateDeviceExtensionProperties(vk->physical, NULL, &avail, props) != VK_SUCCESS) {
                free(props);
                props = NULL;
                avail = 0u;
            }
        }
        if (props) {
            for (u32 i = 0; i < avail; i++) {
                if (strcmp(props[i].extensionName, VK_EXT_DEVICE_FAULT_EXTENSION_NAME) == 0) {
                    dev_extensions[dev_extension_count++] = VK_EXT_DEVICE_FAULT_EXTENSION_NAME;
                    vk->has_device_fault = true;
                    break;
                }
            }
            free(props);
        }
    }
    VkPhysicalDeviceAccelerationStructureFeaturesKHR enabled_accel = {0};
    VkPhysicalDeviceRayTracingPipelineFeaturesKHR enabled_rt_pipeline = {0};
    VkPhysicalDeviceRayQueryFeaturesKHR enabled_ray_query = {0};
    bool enable_rt_pipeline = rt_pipeline_extensions &&
                              supported_accel.accelerationStructure &&
                              supported_rt_pipeline.rayTracingPipeline;
    bool enable_ray_query = as_extensions && vk->feat_ray_query &&
                            supported_accel.accelerationStructure &&
                            supported_ray_query.rayQuery;
    enabled_accel.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_ACCELERATION_STRUCTURE_FEATURES_KHR;
    enabled_rt_pipeline.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_RAY_TRACING_PIPELINE_FEATURES_KHR;
    enabled_ray_query.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_RAY_QUERY_FEATURES_KHR;
    if (as_extensions) {
        enabled_accel.accelerationStructure = VK_TRUE;
        /* Enable host-side AS build commands when supported — without this,
         * vkBuildAccelerationStructuresKHR is a spec violation that silently
         * falls back to device builds or crashes drivers (observed: AMD). */
        enabled_accel.accelerationStructureHostCommands =
            supported_accel.accelerationStructureHostCommands ? VK_TRUE : VK_FALSE;
        enabled_accel.pNext = &enabled_rt_pipeline;
        enabled_rt_pipeline.rayTracingPipeline = enable_rt_pipeline ? VK_TRUE : VK_FALSE;
        enabled_rt_pipeline.pNext = enable_ray_query ? &enabled_ray_query : NULL;
        enabled_ray_query.rayQuery = enable_ray_query ? VK_TRUE : VK_FALSE;
        enabled_vk12.pNext = &enabled_accel;
    }

    VkDeviceCreateInfo dci = {0};
    dci.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
    dci.pNext = &enabled_vk11; /* R441: 1.1 chain head (-> 1.2 features) */
    dci.queueCreateInfoCount = queue_info_count;
    dci.pQueueCreateInfos = queue_infos;
    dci.enabledExtensionCount = dev_extension_count;
    dci.ppEnabledExtensionNames = dev_extensions;
    dci.pEnabledFeatures = &enabled_features;

    if (vkCreateDevice(vk->physical, &dci, NULL, &vk->device) != VK_SUCCESS) {
        LOG_FATAL("Vulkan: failed to create device");
        vk_init_cleanup(dev, vk);
        return false;
    }

    if (enable_rt_pipeline) {
        dev->capabilities.feature_bits |= RHI_FEATURE_RAY_TRACING_PIPELINE;
    }
    if (enable_ray_query) {
        dev->capabilities.feature_bits |= RHI_FEATURE_RAY_QUERY;
    }
    vk->feat_acceleration_structure = as_extensions &&
        supported_accel.accelerationStructure &&
        enabled_accel.accelerationStructure == VK_TRUE;
    if (vk->feat_acceleration_structure) {
        dev->capabilities.feature_bits |= RHI_FEATURE_ACCELERATION_STRUCTURE;
    }

    vkGetDeviceQueue(vk->device, vk->graphics_family, 0, &vk->graphics_queue);
    vkGetDeviceQueue(vk->device, vk->present_family, 0, &vk->present_queue);
    g_vk_get_buffer_device_address =
        (PFN_vkGetBufferDeviceAddress)vkGetDeviceProcAddr(
            vk->device, "vkGetBufferDeviceAddress");
    g_vk_get_as_build_sizes =
        (PFN_vkGetAccelerationStructureBuildSizesKHR)vkGetDeviceProcAddr(
            vk->device, "vkGetAccelerationStructureBuildSizesKHR");
    g_vk_cmd_build_as = (PFN_vkCmdBuildAccelerationStructuresKHR)
        vkGetDeviceProcAddr(vk->device, "vkCmdBuildAccelerationStructuresKHR");
    g_vk_build_as_host = (PFN_vkBuildAccelerationStructuresKHR)
        vkGetDeviceProcAddr(vk->device, "vkBuildAccelerationStructuresKHR");
    g_vk_get_as_address = (PFN_vkGetAccelerationStructureDeviceAddressKHR)
        vkGetDeviceProcAddr(vk->device, "vkGetAccelerationStructureDeviceAddressKHR");
    /* Host-side AS builds require accelerationStructureHostCommands; calling
     * vkBuildAccelerationStructuresKHR without it is a spec violation that
     * crashes some drivers (observed: AMD Windows integrated GPU). */
    {
        VkPhysicalDeviceAccelerationStructureFeaturesKHR as_features;
        VkPhysicalDeviceFeatures2 features2;
        memset(&as_features, 0, sizeof(as_features));
        as_features.sType =
            VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_ACCELERATION_STRUCTURE_FEATURES_KHR;
        memset(&features2, 0, sizeof(features2));
        features2.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FEATURES_2;
        features2.pNext = &as_features;
        vkGetPhysicalDeviceFeatures2(vk->physical, &features2);
        g_vk_host_as_supported =
            as_features.accelerationStructureHostCommands == VK_TRUE;
        LOG_INFO("VK: AS host commands %s (accelerationStructure=%d)",
                 g_vk_host_as_supported ? "supported" : "NOT supported",
                 (int)as_features.accelerationStructure);
    }

    if (!vk_create_swapchain(vk, w, h)) {
        /* R430: fail init instead of running with a NULL swapchain. */
        vk_init_cleanup(dev, vk);
        return false;
    }
    if (!vk_create_render_pass(vk) || !vk_create_depth(vk) ||
        !vk_create_framebuffers(vk)) {
        LOG_FATAL("VK: failed to create swapchain attachments");
        vk_init_cleanup(dev, vk);
        return false;
    }

    VkCommandPoolCreateInfo cpci = {0};
    cpci.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
    cpci.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
    cpci.queueFamilyIndex = vk->graphics_family;
    if (vkCreateCommandPool(vk->device, &cpci, NULL, &vk->cmd_pool) != VK_SUCCESS) {
        LOG_FATAL("VK: failed to create command pool");
        vk_init_cleanup(dev, vk); return false;
    }

    VkCommandBufferAllocateInfo cbai = {0};
    cbai.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    cbai.commandPool = vk->cmd_pool;
    cbai.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
    cbai.commandBufferCount = VK_MAX_FRAMES;
    if (vkAllocateCommandBuffers(vk->device, &cbai, vk->cmd_buffers) != VK_SUCCESS) {
        LOG_FATAL("VK: failed to allocate command buffers");
        vk_init_cleanup(dev, vk); return false;
    }
    vk->cmd_buffer_count = VK_MAX_FRAMES;

    vk->uniform_ring_size = 4 * 1024 * 1024;
    for (u32 i = 0; i < VK_MAX_FRAMES; i++) {
        VkBufferCreateInfo bci = {0};
        bci.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
        bci.size = vk->uniform_ring_size;
        bci.usage = VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT;
        bci.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
        if (vkCreateBuffer(vk->device, &bci, NULL, &vk->uniform_ring[i].buffer) != VK_SUCCESS) {
            LOG_FATAL("VK: failed to create uniform buffer %u", i);
            vk_init_cleanup(dev, vk); return false;
        }

        VkMemoryRequirements mem_req;
        vkGetBufferMemoryRequirements(vk->device, vk->uniform_ring[i].buffer, &mem_req);

        VkMemoryAllocateInfo mai = {0};
        mai.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
        mai.allocationSize = mem_req.size;
        mai.memoryTypeIndex = vk_find_memory(vk, mem_req.memoryTypeBits,
            VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);
        if (vk_allocate_memory(vk, &mai, &vk->uniform_ring[i].memory) != VK_SUCCESS) {
            LOG_FATAL("VK: failed to allocate uniform memory %u", i);
            vk_init_cleanup(dev, vk); return false;
        }
        if (vkBindBufferMemory(vk->device, vk->uniform_ring[i].buffer, vk->uniform_ring[i].memory, 0) != VK_SUCCESS) {
            LOG_FATAL("VK: failed to bind uniform buffer %u", i);
            vk_init_cleanup(dev, vk); return false;
        }
        if (vkMapMemory(vk->device, vk->uniform_ring[i].memory, 0, vk->uniform_ring_size, 0, (void **)&vk->uniform_mapped[i]) != VK_SUCCESS) {
            LOG_FATAL("VK: failed to map uniform memory %u", i);
            vk_init_cleanup(dev, vk); return false;
        }
        vk->uniform_offset[i] = 0;
    }

    {
        VkDescriptorSetLayoutBinding binds[RHI_MAX_TEXTURE_UNITS];
        memset(binds, 0, sizeof(binds));
        for (u32 i = 0; i < RHI_MAX_TEXTURE_UNITS; i++) {
            binds[i].binding = i;
            binds[i].descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
            binds[i].descriptorCount = 1;
            binds[i].stageFlags = VK_SHADER_STAGE_FRAGMENT_BIT;
        }
        /* Binding 5 doubles as the forward shaders' single u_ssao and the
         * deferred lighting shader's u_point_shadow_cubes[4]. Forward point-light
         * shadows use binding 10 so SSAO at binding 5 stays valid. Layout array
         * keeps every generic texture unit addressable. */
        VkDescriptorBindingFlags bind_flags[RHI_MAX_TEXTURE_UNITS] = {0};
        VkDescriptorSetLayoutBindingFlagsCreateInfo flags_ci = {0};
        flags_ci.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_BINDING_FLAGS_CREATE_INFO;
        flags_ci.bindingCount = RHI_MAX_TEXTURE_UNITS;
        flags_ci.pBindingFlags = bind_flags;
        if (vk->feat_partially_bound) {
            binds[5].descriptorCount = 4;
            bind_flags[5] = VK_DESCRIPTOR_BINDING_PARTIALLY_BOUND_BIT;
            binds[10].descriptorCount = 4;
            bind_flags[10] = VK_DESCRIPTOR_BINDING_PARTIALLY_BOUND_BIT;
        } else {
            binds[10].descriptorCount = 1;
        }
        /* R635: the two shadow-cube arrays push the per-stage sampler total to
         * 22, past the spec-minimum maxPerStageDescriptorSamplers of 16 (the
         * exact MoltenVK figure — the layout was non-conformant everywhere,
         * desktop drivers just report higher limits). UPDATE_AFTER_BIND moves
         * the arrays into the maxPerStageDescriptorUpdateAfterBindSamplers
         * budget (1024 on MoltenVK); the 14 remaining single bindings stay at
         * 14 <= 16. Update timing is relaxed (superset), never tightened. */
        bool uab_arrays = vk->feat_uab_sampled_image && vk->feat_partially_bound;
        if (uab_arrays) {
            bind_flags[5]  |= VK_DESCRIPTOR_BINDING_UPDATE_AFTER_BIND_BIT;
            bind_flags[10] |= VK_DESCRIPTOR_BINDING_UPDATE_AFTER_BIND_BIT;
        }

        VkDescriptorSetLayoutCreateInfo dli = {0};
        dli.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
        dli.bindingCount = RHI_MAX_TEXTURE_UNITS;
        dli.pBindings = binds;
        if (uab_arrays)
            dli.flags = VK_DESCRIPTOR_SET_LAYOUT_CREATE_UPDATE_AFTER_BIND_POOL_BIT;
        if (vk->feat_partially_bound) dli.pNext = &flags_ci;
        if (vkCreateDescriptorSetLayout(vk->device, &dli, NULL, &vk->desc_layout) != VK_SUCCESS) {
            LOG_FATAL("VK: failed to create desc layout");
            vk_init_cleanup(dev, vk); return false;
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
            vk_init_cleanup(dev, vk); return false;
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
            vk_init_cleanup(dev, vk); return false;
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
            vk_init_cleanup(dev, vk); return false;
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
            vk_init_cleanup(dev, vk); return false;
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
            vk_init_cleanup(dev, vk); return false;
        }
    }

    /* Dedicated ray-query set: binding 0 is TLAS, binding 1 is a storage
     * image. It is appended only when acceleration-structure support is
     * enabled; unsupported devices must never see the AS descriptor type. */
    if (as_extensions) {
        VkDescriptorSetLayoutBinding rqb[2] = {0};
        VkDescriptorSetLayoutCreateInfo rqli = {0};
        rqb[0].binding = 0u;
        rqb[0].descriptorType = VK_DESCRIPTOR_TYPE_ACCELERATION_STRUCTURE_KHR;
        rqb[0].descriptorCount = 1u;
        rqb[0].stageFlags = VK_SHADER_STAGE_COMPUTE_BIT;
        rqb[1].binding = 1u;
        rqb[1].descriptorType = VK_DESCRIPTOR_TYPE_STORAGE_IMAGE;
        rqb[1].descriptorCount = 1u;
        rqb[1].stageFlags = VK_SHADER_STAGE_COMPUTE_BIT;
        rqli.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
        rqli.bindingCount = 2u;
        rqli.pBindings = rqb;
        if (vkCreateDescriptorSetLayout(vk->device, &rqli, NULL,
                                        &vk->ray_query_layout) != VK_SUCCESS) {
            LOG_FATAL("VK: failed to create ray query layout");
            vk_init_cleanup(dev, vk);
            return false;
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
            vk_init_cleanup(dev, vk); return false;
        }
    }

    {
        VkDescriptorPoolSize pool_sizes[6] = {0};
        u32 pool_size_count = 5u;
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
        if (as_extensions) {
            pool_sizes[5].type = VK_DESCRIPTOR_TYPE_ACCELERATION_STRUCTURE_KHR;
            pool_sizes[5].descriptorCount = 256;
            pool_size_count = 6u;
        }

        VkDescriptorPoolCreateInfo dpi = {0};
        dpi.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
        dpi.flags = VK_DESCRIPTOR_POOL_CREATE_FREE_DESCRIPTOR_SET_BIT;
        /* R635: allocating sets whose layout carries UPDATE_AFTER_BIND
         * (material texture layout, shadow-cube arrays) requires the pool
         * flag; harmless for the legacy path. */
        if (vk->feat_uab_sampled_image && vk->feat_partially_bound)
            dpi.flags |= VK_DESCRIPTOR_POOL_CREATE_UPDATE_AFTER_BIND_BIT;
        dpi.maxSets = 4096;
        dpi.poolSizeCount = pool_size_count;
        dpi.pPoolSizes = pool_sizes;
        for (u32 i = 0; i < VK_MAX_FRAMES; i++) {
            if (vkCreateDescriptorPool(vk->device, &dpi, NULL, &vk->desc_pools[i]) != VK_SUCCESS) {
                LOG_FATAL("VK: failed to create descriptor pool %u", i);
                vk_init_cleanup(dev, vk); return false;
            }
        }
    }

    for (u32 i = 0; i < VK_MAX_FRAMES; i++) {
        VkSemaphoreCreateInfo sci2 = {0};
        sci2.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;
        if (vkCreateSemaphore(vk->device, &sci2, NULL, &vk->image_semaphores[i]) != VK_SUCCESS) {
            LOG_FATAL("VK: failed to create image semaphore %u", i);
            vk_init_cleanup(dev, vk); return false;
        }
        VkFenceCreateInfo fci = {0};
        fci.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
        fci.flags = VK_FENCE_CREATE_SIGNALED_BIT;
        if (vkCreateFence(vk->device, &fci, NULL, &vk->fences[i]) != VK_SUCCESS) {
            LOG_FATAL("VK: failed to create fence %u", i);
            vk_init_cleanup(dev, vk); return false;
        }
    }

    dev->backend_data = vk;
    dev->width = w;
    dev->height = h;

    vk->shaderc_compiler = shaderc_compiler_initialize();
    if (!vk->shaderc_compiler) {
        LOG_FATAL("Vulkan: shaderc_compiler_initialize failed");
        /* R425: treat as init failure — returning true with a NULL compiler
         * makes the first rhi_shader_create crash in shaderc_compile_into_spv. */
        dev->backend_data = NULL;
        vk_init_cleanup(dev, vk);
        return false;
    }

    LOG_INFO("Vulkan initialized");
    return true;
}

bool rhi_device_idle(RHIDevice *dev) {
    VKBackend *vk = dev ? vk_backend(dev) : NULL;
    if (!vk || vk->device == VK_NULL_HANDLE) return false;
    /* Diagnostic probe: DEVICE_LOST from an earlier faulting submission is
     * reported asynchronously and otherwise only surfaces at the next
     * fence wait, often far from the faulting test. A full idle wait makes
     * the loss observable at the probe site (test_vulkan bisection). */
    VkResult r = vkDeviceWaitIdle(vk->device);
    vk_note_result(vk, r); /* R578 */
    if (r != VK_SUCCESS) {
        LOG_ERROR("rhi_device_idle: vkDeviceWaitIdle = %d", (int)r);
        return false;
    }
    return true;
}

bool rhi_device_lost(RHIDevice *dev) {
    VKBackend *vk = dev ? vk_backend(dev) : NULL;
    return vk ? vk->device_lost : false; /* R578 */
}

static void vk_shutdown(RHIDevice *dev) {
    VKBackend *vk = vk_backend(dev);
    if (!vk) return;
    if (vk->device != VK_NULL_HANDLE && vkDeviceWaitIdle(vk->device) != VK_SUCCESS)
        LOG_WARN("VK: vkDeviceWaitIdle failed in shutdown");
    /* R175: Device idle — free deferred mip-upload resources without waiting. */
    if (vk->device != VK_NULL_HANDLE && !vk_mip_upload_owned_by_other(vk))
        vk_mip_upload_reclaim(vk);

#if defined(ENGINE_PLATFORM_ANDROID)
    if (vk->native_window) {
        ANativeWindow_release(vk->native_window);
        vk->native_window = NULL;
    }
#endif

    if (vk->shaderc_compiler) {
        shaderc_compiler_release(vk->shaderc_compiler);
        vk->shaderc_compiler = NULL;
    }

    if (vk->device != VK_NULL_HANDLE) {
        for (u32 i = 0; i < VK_MAX_FRAMES; i++) {
            if (vk->image_semaphores[i]) vkDestroySemaphore(vk->device, vk->image_semaphores[i], NULL);
            if (vk->fences[i]) vkDestroyFence(vk->device, vk->fences[i], NULL);
            if (vk->uniform_mapped[i] && vk->uniform_ring[i].memory)
                vkUnmapMemory(vk->device, vk->uniform_ring[i].memory);
            if (vk->uniform_ring[i].buffer) vkDestroyBuffer(vk->device, vk->uniform_ring[i].buffer, NULL);
            if (vk->uniform_ring[i].memory) vkFreeMemory(vk->device, vk->uniform_ring[i].memory, NULL);
        }

        if (vk->cmd_pool != VK_NULL_HANDLE) {
            if (vk->cmd_buffer_count)
                vkFreeCommandBuffers(vk->device, vk->cmd_pool, vk->cmd_buffer_count, vk->cmd_buffers);
            vkDestroyCommandPool(vk->device, vk->cmd_pool, NULL);
        }
        for (u32 i = 0; i < VK_MAX_FRAMES; i++)
            if (vk->desc_pools[i]) vkDestroyDescriptorPool(vk->device, vk->desc_pools[i], NULL);
        if (vk->desc_layout) vkDestroyDescriptorSetLayout(vk->device, vk->desc_layout, NULL);
        if (vk->texel_layout) vkDestroyDescriptorSetLayout(vk->device, vk->texel_layout, NULL);
        if (vk->storage_layout) vkDestroyDescriptorSetLayout(vk->device, vk->storage_layout, NULL);
        if (vk->storage_vtx_layout) vkDestroyDescriptorSetLayout(vk->device, vk->storage_vtx_layout, NULL);
        if (vk->storage_image_layout) vkDestroyDescriptorSetLayout(vk->device, vk->storage_image_layout, NULL);
        if (vk->ray_query_layout) vkDestroyDescriptorSetLayout(vk->device, vk->ray_query_layout, NULL);
        if (vk->sampler_mip_layout) vkDestroyDescriptorSetLayout(vk->device, vk->sampler_mip_layout, NULL);
        if (vk->ubo_layout) vkDestroyDescriptorSetLayout(vk->device, vk->ubo_layout, NULL);
        vk_cleanup_swapchain(vk);
        if (vk->render_pass) vkDestroyRenderPass(vk->device, vk->render_pass, NULL);
        if (vk->render_pass_load) vkDestroyRenderPass(vk->device, vk->render_pass_load, NULL);
        for (u32 i = 0; i < vk->pipe_rp_count; i++) {
            if (vk->pipe_rp_cache[i]) vkDestroyRenderPass(vk->device, vk->pipe_rp_cache[i], NULL);
        }
        vkDestroyDevice(vk->device, NULL);
        vk->device = VK_NULL_HANDLE;
    }
    /* R438: symmetric cleanup of the validation-gate debug messenger (only
     * ever non-NULL when the gate was enabled at init). */
    if (vk->debug_messenger && vk->instance != VK_NULL_HANDLE) {
        PFN_vkDestroyDebugUtilsMessengerEXT destroy_dbg =
            (PFN_vkDestroyDebugUtilsMessengerEXT)vkGetInstanceProcAddr(
                vk->instance, "vkDestroyDebugUtilsMessengerEXT");
        if (destroy_dbg) destroy_dbg(vk->instance, vk->debug_messenger, NULL);
        vk->debug_messenger = VK_NULL_HANDLE;
    }
    if (vk->surface && vk->instance) vkDestroySurfaceKHR(vk->instance, vk->surface, NULL);
    if (vk->instance) vkDestroyInstance(vk->instance, NULL);
    g_validation_gate_active = false;
    free(vk);
    dev->backend_data = NULL;
}

/* ---- RHI Implementation (overrides GL versions via conditional compilation) ---- */

static VkFormat vk_format_from_rhi(RHIFormat fmt) {
    switch (fmt) {
    case RHI_FORMAT_R8G8B8A8_UNORM: return VK_FORMAT_R8G8B8A8_UNORM;
    case RHI_FORMAT_B8G8R8A8_UNORM: return VK_FORMAT_B8G8R8A8_UNORM;
    case RHI_FORMAT_R16G16B16A16_SFLOAT: return VK_FORMAT_R16G16B16A16_SFLOAT;
    case RHI_FORMAT_R16G16_SFLOAT: return VK_FORMAT_R16G16_SFLOAT;
    case RHI_FORMAT_R32_FLOAT:      return VK_FORMAT_R32_SFLOAT;
    case RHI_FORMAT_D32_FLOAT:      return VK_FORMAT_D32_SFLOAT;
    default: return VK_FORMAT_R8G8B8A8_UNORM;
    }
}

/* R417: bytes-per-pixel for staging-size computation (texture create assumed
 * 4 bpp, halving the staging buffer for R16G16B16A16_SFLOAT → GPU OOB read). */
static u32 rhi_format_bpp(RHIFormat fmt) {
    switch (fmt) {
    case RHI_FORMAT_R16G16B16A16_SFLOAT: return 8;
    case RHI_FORMAT_R16G16_SFLOAT: return 4;
    default:                             return 4;
    }
}

/* 计划 E Task 2：编译期单后端入口——VK 实现转发到自身后端。
 * 双句柄约定（rhi.h）：VK 消费 surface_native（Wayland 上为 wl_surface*）。 */
RHIDevice *rhi_device_create_compiled(void *window_native, void *surface_native,
                                      void *display_native, u32 w, u32 h) {
    (void)window_native;
    return rhi_device_create(RHI_BACKEND_VULKAN, surface_native,
                             display_native, w, h);
}

RHIDevice *rhi_device_create(RHIBackend backend, void *window_native, void *display_native, u32 w, u32 h) {
    if (backend != RHI_BACKEND_VULKAN || !rhi_drawable_dimensions_valid(w, h)) {
        return NULL;
    }
#ifdef ENGINE_PLATFORM_WINDOWS
    if (window_native == NULL || display_native == NULL) return NULL;
#elif defined(ENGINE_PLATFORM_MACOS) || defined(ENGINE_PLATFORM_IOS)
    if (window_native == NULL) return NULL;
#elif defined(ENGINE_PLATFORM_ANDROID)
    if (window_native == NULL) return NULL;
#else
    if (window_native == NULL || display_native == NULL) return NULL;
#endif
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
    if (!rhi_frame_owner_begin_destroy(dev)) return;
    VKBackend *vk = vk_backend(dev);
    if (!vk) {
        if (g_current_device == dev) g_current_device = NULL;
        free(dev);
        return;
    }
    if (vkDeviceWaitIdle(vk->device) != VK_SUCCESS)
        LOG_WARN("VK: vkDeviceWaitIdle failed in device_destroy");

    /* The queue is idle, but each per-frame command buffer still RETAINS its
     * recorded resource bindings until reset, and this validation layer only
     * clears the pending state after an explicit fence wait (queue-idle alone
     * is insufficient). The NVIDIA layer (unlike AMD/Mesa) then rejects
     * destroying pipeline/buffer objects those command buffers still
     * reference, so wait each frame fence and reset every command buffer
     * before the slot-cleanup loop below frees those objects. Fences are
     * created signaled, and the device is already idle, so each wait returns
     * immediately. */
    for (u32 i = 0; i < vk->cmd_buffer_count && i < VK_MAX_FRAMES; i++) {
        if (vk->fences[i] != VK_NULL_HANDLE &&
            vkWaitForFences(vk->device, 1u, &vk->fences[i], VK_TRUE,
                            UINT64_MAX) != VK_SUCCESS) {
            LOG_WARN("VK: fence wait failed in device_destroy (frame %u)", i);
        }
        if (vk->cmd_buffers[i] != VK_NULL_HANDLE)
            vkResetCommandBuffer(vk->cmd_buffers[i], 0);
    }

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
                /* R440: per-pipeline MRT render pass — vk_pipeline_data_free
                 * destroys it; this hand-rolled case must too. */
                if (pd->mrt_render_pass) vkDestroyRenderPass(vk->device, pd->mrt_render_pass, NULL);
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
        case RHI_RES_CUBEMAP: {
            /* Mirrors the tail of rhi_cubemap_destroy (device already idle). */
            VKCubemapData *cd = (VKCubemapData *)dev->slots[i].ptr;
            if (cd) {
                for (u32 f = 0; f < 6; f++) {
                    for (u32 m = 0; m < VK_MAX_MIP_VIEWS; m++) {
                        if (cd->face_views[f][m])
                            vkDestroyImageView(vk->device, cd->face_views[f][m], NULL);
                    }
                }
                vkDestroyImageView(vk->device, cd->view, NULL);
                vkDestroyImage(vk->device, cd->image, NULL);
                vkFreeMemory(vk->device, cd->memory, NULL);
                free(cd);
            }
            break;
        }
        case RHI_RES_FRAMEBUFFER: {
            /* Two payload types share this slot type, tagged at create:
             * VKShadowData (shadow map) / VKFBOData (offscreen FBO). Their
             * color/depth image+view+memory are aliased into sibling
             * RHI_RES_TEXTURE slots and released by the TEXTURE case;
             * destroy here only what no texture slot owns (mirrors the tails
             * of rhi_shadow_map_destroy / vk_offscreen_fbo_release, minus the
             * aliased objects and the device-idle wait done once up front). */
            const u32 *magic = (const u32 *)dev->slots[i].ptr;
            if (magic && *magic == VK_SHADOW_DATA_MAGIC) {
                VKShadowData *sd = (VKShadowData *)dev->slots[i].ptr;
                if (vk->shadow_render_pass == sd->render_pass)
                    vk->shadow_render_pass = VK_NULL_HANDLE;
                if (sd->framebuffer) vkDestroyFramebuffer(vk->device, sd->framebuffer, NULL);
                if (sd->render_pass) vkDestroyRenderPass(vk->device, sd->render_pass, NULL);
                if (sd->render_pass_load) vkDestroyRenderPass(vk->device, sd->render_pass_load, NULL);
                free(sd);
            } else if (magic && *magic == VK_FBO_DATA_MAGIC) {
                VKFBOData *fd = (VKFBOData *)dev->slots[i].ptr;
                if (fd->framebuffer) vkDestroyFramebuffer(vk->device, fd->framebuffer, NULL);
                if (fd->render_pass) vkDestroyRenderPass(vk->device, fd->render_pass, NULL);
                if (fd->render_pass_load) vkDestroyRenderPass(vk->device, fd->render_pass_load, NULL);
                if (fd->msaa_color_view) vkDestroyImageView(vk->device, fd->msaa_color_view, NULL);
                if (fd->msaa_color_image) vkDestroyImage(vk->device, fd->msaa_color_image, NULL);
                if (fd->msaa_color_memory) vkFreeMemory(vk->device, fd->msaa_color_memory, NULL);
                if (fd->msaa_depth_view) vkDestroyImageView(vk->device, fd->msaa_depth_view, NULL);
                if (fd->msaa_depth_image) vkDestroyImage(vk->device, fd->msaa_depth_image, NULL);
                if (fd->msaa_depth_memory) vkFreeMemory(vk->device, fd->msaa_depth_memory, NULL);
                free(fd);
            } else {
                free(dev->slots[i].ptr);
            }
            break;
        }
        case RHI_RES_MRT_FBO: {
            /* Attachment + depth image/view/memory are aliased into sibling
             * RHI_RES_TEXTURE slots (released by the TEXTURE case);
             * destroy only the framebuffer, both render passes and the struct
             * (mirrors rhi_mrt_fbo_destroy, minus the aliased objects). */
            VKMRTFBOData *md = (VKMRTFBOData *)dev->slots[i].ptr;
            if (md) {
                if (md->framebuffer) vkDestroyFramebuffer(vk->device, md->framebuffer, NULL);
                if (md->render_pass) vkDestroyRenderPass(vk->device, md->render_pass, NULL);
                if (md->render_pass_load) vkDestroyRenderPass(vk->device, md->render_pass_load, NULL);
                free(md);
            }
            break;
        }
        case RHI_RES_CUBEMAP_DEPTH_FBO: {
            /* The depth image/view/memory are aliased into the sibling
             * RHI_RES_TEXTURE slot (released by the TEXTURE case);
             * destroy the per-face views/framebuffers, both render passes and
             * the struct (mirrors rhi_cubemap_depth_fbo_destroy). */
            VKCubemapDepthFBOData *cd = (VKCubemapDepthFBOData *)dev->slots[i].ptr;
            if (cd) {
                for (u32 face = 0; face < 6; face++) {
                    if (cd->face_fbos[face]) vkDestroyFramebuffer(vk->device, cd->face_fbos[face], NULL);
                    if (cd->face_views[face]) vkDestroyImageView(vk->device, cd->face_views[face], NULL);
                }
                if (cd->render_pass) vkDestroyRenderPass(vk->device, cd->render_pass, NULL);
                if (cd->render_pass_load) vkDestroyRenderPass(vk->device, cd->render_pass_load, NULL);
                free(cd);
            }
            break;
        }
        case RHI_RES_ACCELERATION_STRUCTURE: {
            VKAccelerationStructureData *ad =
                (VKAccelerationStructureData *)dev->slots[i].ptr;
            if (ad) {
                PFN_vkDestroyAccelerationStructureKHR destroy_as =
                    (PFN_vkDestroyAccelerationStructureKHR)vkGetDeviceProcAddr(
                        vk->device, "vkDestroyAccelerationStructureKHR");
                if (destroy_as && ad->handle != VK_NULL_HANDLE)
                    destroy_as(vk->device, ad->handle, NULL);
                if (ad->storage_buffer != VK_NULL_HANDLE)
                    vkDestroyBuffer(vk->device, ad->storage_buffer, NULL);
                if (ad->storage_memory != VK_NULL_HANDLE)
                    vkFreeMemory(vk->device, ad->storage_memory, NULL);
                free(ad);
            }
            break;
        }
        default:
            free(dev->slots[i].ptr);
            break;
        }
    }

    vk_shutdown(dev);
    if (g_current_device == dev) g_current_device = NULL;
    rhi_frame_owner_release(dev);
    free(dev);
}

void rhi_device_resize(RHIDevice *dev, u32 w, u32 h) {
    if (!rhi_drawable_dimensions_valid(w, h) ||
        !rhi_device_control_try_acquire(dev)) return;
    VKBackend *vk = vk_backend(dev);
    if (!vk) {
        rhi_device_control_release(dev);
        return;
    }
    rhi_device_set_lifecycle_result(dev, vk_recreate_swapchain(vk, w, h));
    if (dev->lifecycle_result == RHI_RESULT_OK) {
        dev->width = w;
        dev->height = h;
    }
    rhi_device_control_release(dev);
}

RHICmdBuffer *rhi_frame_begin(RHIDevice *dev) {
    if (dev == NULL) return NULL;
    VKBackend *vk = vk_backend(dev);
    if (!vk) {
        rhi_device_set_lifecycle_result(dev, RHI_RESULT_UNAVAILABLE);
        return NULL;
    }
    if (!rhi_frame_owner_begin_backend(dev)) return NULL;
    g_current_device = dev;
    dev->frame_partial_active = false;
    vk->frame_submitted = false;

    /* R175: Ensure this device's deferred mip upload finished before sampling. */
    vk_mip_upload_reclaim(vk);

    if (vk->device_lost) { /* R578: latched loss — quiet fail-fast, no spam */
        rhi_device_set_lifecycle_result(dev, RHI_RESULT_DEVICE_LOST);
        vk->frame_started = false;
        rhi_frame_owner_release(dev);
        return NULL;
    }
    VkResult fence_res = vk_wait_fence(vk, vk->fences[vk->current_frame]);
    if (fence_res != VK_SUCCESS) {
        rhi_device_set_lifecycle_result(dev, vk_lifecycle_result(fence_res));
        LOG_FATAL("VK: vkWaitForFences failed in frame_begin (res=%d)", (int)fence_res);
        vk_dump_device_fault(vk, "frame_begin");
        vk->frame_started = false;
        rhi_frame_owner_release(dev);
        return NULL;
    }
    VkResult reset_fence_res = vkResetFences(vk->device, 1, &vk->fences[vk->current_frame]);
    if (reset_fence_res != VK_SUCCESS) {
        rhi_device_set_lifecycle_result(dev, vk_lifecycle_result(reset_fence_res));
        LOG_FATAL("VK: vkResetFences failed in frame_begin");
        vk->frame_started = false;
        rhi_frame_owner_release(dev);
        return NULL;
    }
    VkResult reset_pool_res = vkResetDescriptorPool(vk->device, vk->desc_pools[vk->current_frame], 0);
    if (reset_pool_res != VK_SUCCESS) {
        rhi_device_set_lifecycle_result(dev, vk_lifecycle_result(reset_pool_res));
        LOG_FATAL("VK: vkResetDescriptorPool failed in frame_begin");
        vk->frame_started = false;
        rhi_frame_owner_release(dev);
        return NULL;
    }

    VkResult res = vkAcquireNextImageKHR(vk->device, vk->swapchain, UINT64_MAX,
        vk->image_semaphores[vk->current_frame], VK_NULL_HANDLE, &vk->image_index);
    if (res == VK_ERROR_OUT_OF_DATE_KHR) {
        RHIResult recreate_result = vk_recreate_swapchain(vk, dev->width, dev->height);
        if (recreate_result != RHI_RESULT_OK) {
            rhi_device_set_lifecycle_result(dev, recreate_result);
            vk->frame_started = false;
            rhi_frame_owner_release(dev);
            return NULL;
        }
        res = vkAcquireNextImageKHR(vk->device, vk->swapchain, UINT64_MAX,
            vk->image_semaphores[vk->current_frame], VK_NULL_HANDLE, &vk->image_index);
        if (res != VK_SUCCESS && res != VK_SUBOPTIMAL_KHR) {
            rhi_device_set_lifecycle_result(dev, vk_lifecycle_result(res));
            vk->frame_started = false;
            rhi_frame_owner_release(dev);
            return NULL;
        }
    } else if (res != VK_SUCCESS && res != VK_SUBOPTIMAL_KHR) {
        /* R148: Handle VK_ERROR_DEVICE_LOST / VK_ERROR_SURFACE_LOST_KHR / etc.
         * Without this, a non-OUT_OF_DATE error falls through and proceeds to
         * record commands with a stale image_index, potentially using an invalid
         * framebuffer and causing a cascade of GPU errors. */
        LOG_ERROR("VK: vkAcquireNextImageKHR failed (res=%d)", (int)res);
        rhi_device_set_lifecycle_result(dev, vk_lifecycle_result(res));
        vk->frame_started = false;
        rhi_frame_owner_release(dev);
        return NULL;
    }
    /* VK_SUBOPTIMAL_KHR is a success — swapchain rebuild deferred to rhi_present */

    /* R150: Guard against NULL framebuffers — vk_create_framebuffers may have failed
     * (e.g., OOM on calloc, vkCreateFramebuffer error) even though the swapchain
     * itself is valid and vkAcquireNextImageKHR succeeded. Without this check,
     * vk->framebuffers[vk->image_index] dereferences NULL. */
    if (!vk->framebuffers) {
        LOG_ERROR("VK: framebuffers not available in frame_begin");
        rhi_device_set_lifecycle_result(dev, RHI_RESULT_UNAVAILABLE);
        vk->frame_started = false;
        rhi_frame_owner_release(dev);
        return NULL;
    }

    VkResult reset_cmd_res = vkResetCommandBuffer(vk->cmd_buffers[vk->current_frame], 0);
    if (reset_cmd_res != VK_SUCCESS) {
        rhi_device_set_lifecycle_result(dev, vk_lifecycle_result(reset_cmd_res));
        LOG_FATAL("VK: vkResetCommandBuffer failed in frame_begin");
        vk->frame_started = false;
        rhi_frame_owner_release(dev);
        return NULL;
    }
    vk->current_pipeline = VK_NULL_HANDLE; /* R89-1: reset pipeline cache for new command buffer */
    vk->vp_valid = false; vk->sc_valid = false;  /* R94-2: reset viewport/scissor cache */
    vk->push_dirty = false; vk->push_dirty_min = 256; vk->push_dirty_max = 0;  /* R96-1: clean state — each set_uniform marks its own range. Avoids pushing 256 bytes to compute pipelines that only declare 128-byte push constant ranges. */

    VkCommandBufferBeginInfo bi = {0};
    bi.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
    bi.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;
    VkResult begin_res = vkBeginCommandBuffer(vk->cmd_buffers[vk->current_frame], &bi);
    if (begin_res != VK_SUCCESS) {
        rhi_device_set_lifecycle_result(dev, vk_lifecycle_result(begin_res));
        LOG_FATAL("VK: vkBeginCommandBuffer failed in frame_begin");
        vk->frame_started = false;
        rhi_frame_owner_release(dev);
        return NULL;
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
                   vk->swap_extent.width, vk->swap_extent.height, vk->swap_format,
                   VK_SAMPLE_COUNT_1_BIT);

    VkViewport vp = {0, 0, (f32)vk->swap_extent.width, (f32)vk->swap_extent.height, 0.0f, 1.0f};
    vkCmdSetViewport(vk->cmd_buffers[vk->current_frame], 0, 1, &vp);
    VkRect2D sc = {{0, 0}, vk->swap_extent};
    vkCmdSetScissor(vk->cmd_buffers[vk->current_frame], 0, 1, &sc);

    vk->frame_started = true;
    vk->current_pipeline = VK_NULL_HANDLE;
    vk->current_pipeline_data = NULL;  /* R106-1: reset stale pointer — desc pool was just reset, so storage_set is dangling */
    vk->bound_ubo = RHI_HANDLE_NULL;
    vk->ubo_bound_pipeline_data = NULL;
    vk->storage_set_valid = false;     /* R106-1: force re-alloc on next bind_storage_buffer */
    vk->image_set_valid = false;       /* R436: same for the storage-image set */
    vk->vp_valid = false; vk->sc_valid = false;  /* R94-2: reset for swapchain pass */
    vk->depth_lequal = false;

    vk->uniform_offset[vk->current_frame] = 0;

    return (RHICmdBuffer *)vk;
}

bool rhi_screenshot(RHIDevice *dev, u32 x, u32 y, u32 w, u32 h,
                    u8 *pixels, usize pixel_bytes) {
    if (!dev || !pixels) return false;
    VKBackend *vk = vk_backend(dev);
    if (!vk) return false;
    /* R577 (CORRECTNESS): the readback transitions vk->swap_images[image_index],
     * which is only legal while that image is acquired — i.e. from
     * rhi_frame_begin until rhi_present. Post-present calls touch an image
     * the presentation engine owns again (spec violation; drivers tolerate it
     * to varying degrees — the cross-GPU hybrid path does not). Refuse loudly
     * so callers move the capture inside the frame (frame_begin..present). */
    if (!vk->frame_started && !vk->frame_submitted) {
        LOG_ERROR("VK: rhi_screenshot outside an acquired frame is illegal "
                  "(image not acquired) — call between frame_begin and present");
        return false;
    }

    if (!rhi_screenshot_region_validate(x, y, w, h, vk->swap_extent.width,
                                        vk->swap_extent.height, pixel_bytes)) {
        return false;
    }

    /* Wait for all frames to complete before reading back. */
    if (vkDeviceWaitIdle(vk->device) != VK_SUCCESS) {
        LOG_WARN("VK: vkDeviceWaitIdle failed in screenshot");
        return false;
    }

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
        return false;
    }

    VkMemoryRequirements mem_req;
    vkGetBufferMemoryRequirements(vk->device, staging_buf, &mem_req);

    VkMemoryAllocateInfo alloc = {0};
    alloc.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
    alloc.allocationSize = mem_req.size;
    alloc.memoryTypeIndex = vk_find_memory(vk, mem_req.memoryTypeBits,
                                            VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);

    VkDeviceMemory staging_mem;
    if (vk_allocate_memory(vk, &alloc, &staging_mem) != VK_SUCCESS) {
        LOG_WARN("screenshot: failed to allocate staging memory");
        vkDestroyBuffer(vk->device, staging_buf, NULL);
        return false;
    }
    if (vkBindBufferMemory(vk->device, staging_buf, staging_mem, 0) != VK_SUCCESS) {
        LOG_WARN("screenshot: failed to bind staging buffer memory");
        vkFreeMemory(vk->device, staging_mem, NULL);
        vkDestroyBuffer(vk->device, staging_buf, NULL);
        return false;
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
        return false;
    }

    VkCommandBufferBeginInfo begin = {0};
    begin.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
    begin.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;
    if (vkBeginCommandBuffer(cmd, &begin) != VK_SUCCESS) {
        LOG_FATAL("VK: failed to begin screenshot command buffer");
        vkFreeCommandBuffers(vk->device, vk->cmd_pool, 1, &cmd);
        vkDestroyBuffer(vk->device, staging_buf, NULL);
        vkFreeMemory(vk->device, staging_mem, NULL);
        return false;
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
        return false;
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
        return false;
    }
    if (vkQueueWaitIdle(vk->graphics_queue) != VK_SUCCESS) {
        LOG_WARN("VK: vkQueueWaitIdle failed in screenshot");
        vkFreeCommandBuffers(vk->device, vk->cmd_pool, 1, &cmd);
        vkDestroyBuffer(vk->device, staging_buf, NULL);
        vkFreeMemory(vk->device, staging_mem, NULL);
        return false;
    }

    vkFreeCommandBuffers(vk->device, vk->cmd_pool, 1, &cmd);

    /* Map buffer and copy RGBA to pixels (VK swapchain is BGRA, convert to RGBA). */
    void *mapped;
    if (vkMapMemory(vk->device, staging_mem, 0, buf_size, 0, &mapped) != VK_SUCCESS) {
        LOG_FATAL("VK: vkMapMemory failed in screenshot");
        vkDestroyBuffer(vk->device, staging_buf, NULL);
        vkFreeMemory(vk->device, staging_mem, NULL);
        return false;
    }
    const u8 *src = (const u8 *)mapped;
    /* R421: iterate in usize — the old 32-bit w*h overflowed for large
     * rects while buf_size was computed in 64-bit. */
    const usize pixel_count = (usize)w * (usize)h;
    /* R430: swap_format is now validated against the surface and may fall
     * back to an RGBA-order format — only swizzle for BGRA-order. */
    if (vk->swap_bgra) {
        for (usize i = 0; i < pixel_count; ++i) {
            pixels[i * 4u + 0u] = src[i * 4u + 2u]; /* R <- B */
            pixels[i * 4u + 1u] = src[i * 4u + 1u]; /* G <- G */
            pixels[i * 4u + 2u] = src[i * 4u + 0u]; /* B <- R */
            pixels[i * 4u + 3u] = src[i * 4u + 3u]; /* A <- A */
        }
    } else {
        memcpy(pixels, src, pixel_count * 4u);
    }
    vkUnmapMemory(vk->device, staging_mem);

    vkFreeMemory(vk->device, staging_mem, NULL);
    vkDestroyBuffer(vk->device, staging_buf, NULL);
    return true;
}

struct RHIGPUTimer {
    VkQueryPool query_pool;
    VkDevice    vkdev;
    RHIDevice  *owner;
    f64         timestamp_period;
    bool        result_ready;
};

RHIGPUTimer *rhi_gpu_timer_create(RHIDevice *dev) {
    if (dev == NULL) return NULL;
    VKBackend *vk = vk_backend(dev);
    if (vk == NULL) return NULL;
    RHIGPUTimer *t = calloc(1, sizeof(RHIGPUTimer));
    if (!t) return NULL;
    t->vkdev = vk->device;
    t->owner = dev;
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
    if (!t) return;
    if (dev != NULL && dev == t->owner && g_current_device == dev &&
        t->query_pool != VK_NULL_HANDLE)
        vkDestroyQueryPool(t->vkdev, t->query_pool, NULL);
    free(t);
}

void rhi_gpu_timer_begin(RHIGPUTimer *t) {
    if (!t) return;
    VKBackend *vk = (g_current_device == t->owner) ?
        vk_backend(g_current_device) : NULL;
    if (!vk) return;
    /* vkCmdResetQueryPool is forbidden inside a render pass. */
    vk_suspend_pass_for_compute(vk);
    vkCmdResetQueryPool(vk->cmd_buffers[vk->current_frame], t->query_pool, 0, 2);
    vkCmdWriteTimestamp(vk->cmd_buffers[vk->current_frame],
        VK_PIPELINE_STAGE_BOTTOM_OF_PIPE_BIT, t->query_pool, 0);
}

void rhi_gpu_timer_end(RHIGPUTimer *t) {
    if (!t) return;
    VKBackend *vk = (g_current_device == t->owner) ?
        vk_backend(g_current_device) : NULL;
    if (!vk) return;
    vkCmdWriteTimestamp(vk->cmd_buffers[vk->current_frame],
        VK_PIPELINE_STAGE_BOTTOM_OF_PIPE_BIT, t->query_pool, 1);
    t->result_ready = true;
}

f64 rhi_gpu_timer_elapsed_ms(RHIGPUTimer *t) {
    if (!t || !t->result_ready || g_current_device != t->owner) return 0.0;
    /* R430: drop VK_QUERY_RESULT_WAIT_BIT — the draw-bench path queries
     * timestamps recorded into the current, not-yet-submitted command
     * buffer, so waiting never completes (deadlock under BREAK_DRAW_BENCH=1).
     * Poll availability instead and report 0 until both timestamps land;
     * the previous-frame path still gets real values. */
    u64 results[4] = {0};
    VkResult r = vkGetQueryPoolResults(t->vkdev, t->query_pool, 0, 2,
        sizeof(results), results, 2 * sizeof(u64),
        VK_QUERY_RESULT_64_BIT | VK_QUERY_RESULT_WITH_AVAILABILITY_BIT);
    if (r != VK_SUCCESS) return 0.0;
    if (results[1] == 0 || results[3] == 0) return 0.0; /* not ready yet */
    t->result_ready = false;
    return (f64)(results[2] - results[0]) * t->timestamp_period / 1e6;
}


void rhi_frame_end(RHIDevice *dev) {
    if (dev == NULL) return;
    if (!rhi_frame_owner_is_current(dev) || g_current_device != dev) return;
    VKBackend *vk = vk_backend(dev);
    if (!vk) {
        rhi_device_set_lifecycle_result(dev, RHI_RESULT_UNAVAILABLE);
        return;
    }
    if (!vk->frame_started) {
        rhi_device_set_lifecycle_result(dev, RHI_RESULT_UNAVAILABLE);
        return;
    }

    /* If a compute dispatch left a pass suspended with no following draw,
     * resume it so it ends with the correct finalLayout transition. */
    vk_resume_pass_if_needed(vk);
    if (vk->render_pass_active) {
        vkCmdEndRenderPass(vk->cmd_buffers[vk->current_frame]);
        vk->render_pass_active = false;
    }
    VkResult end_res = vkEndCommandBuffer(vk->cmd_buffers[vk->current_frame]);
    if (end_res != VK_SUCCESS) {
        rhi_device_set_lifecycle_result(dev,
                                        end_res == VK_ERROR_DEVICE_LOST ?
                                        RHI_RESULT_DEVICE_LOST :
                                        RHI_RESULT_SYNC_FAILED);
        LOG_FATAL("VK: vkEndCommandBuffer failed in frame_end");
        vk->frame_started = false;
        rhi_frame_owner_release(dev);
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

    VkResult submit_res = vkQueueSubmit(vk->graphics_queue, 1, &si, vk->fences[vk->current_frame]);
    vk_note_result(vk, submit_res); /* R578 */
    if (submit_res != VK_SUCCESS) {
        rhi_device_set_lifecycle_result(dev,
                                        submit_res == VK_ERROR_DEVICE_LOST ?
                                        RHI_RESULT_DEVICE_LOST :
                                        RHI_RESULT_SYNC_FAILED);
        LOG_FATAL("VK: vkQueueSubmit failed in frame_end (res=%d)", (int)submit_res);
        vk_dump_device_fault(vk, "frame_end");
        vk->frame_started = false;
        vk->frame_submitted = false;
        rhi_frame_owner_release(dev);
        return;
    }
    rhi_device_set_lifecycle_result(dev, RHI_RESULT_OK);
    vk->frame_started = false;
    vk->frame_submitted = true;
}

void rhi_present(RHIDevice *dev) {
    if (dev == NULL) return;
    if (!rhi_frame_owner_is_current(dev) || g_current_device != dev) return;
    VKBackend *vk = vk_backend(dev);
    if (!vk) {
        rhi_device_set_lifecycle_result(dev, RHI_RESULT_UNAVAILABLE);
        return;
    }
    if (vk->device_lost) { /* R578: acquire/present can block on a dead device */
        rhi_device_set_lifecycle_result(dev, RHI_RESULT_DEVICE_LOST);
        dev->frame_damage_requested = false;
        dev->frame_damage_count = 0u;
        dev->frame_current_damage_count = 0u;
        dev->frame_partial_active = false;
        rhi_frame_owner_release(dev);
        return;
    }
    if (!vk->frame_submitted) {
        rhi_device_set_lifecycle_result(dev, RHI_RESULT_UNAVAILABLE);
        dev->frame_damage_requested = false;
        dev->frame_damage_count = 0u;
        dev->frame_current_damage_count = 0u;
        dev->frame_partial_active = false;
        rhi_frame_owner_release(dev);
        return;
    }

    VkPresentInfoKHR pi = {0};
    pi.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
    pi.waitSemaphoreCount = 1;
    pi.pWaitSemaphores = &vk->render_semaphores[vk->image_index];
    pi.swapchainCount = 1;
    pi.pSwapchains = &vk->swapchain;
    pi.pImageIndices = &vk->image_index;

    VkResult res = vkQueuePresentKHR(vk->present_queue, &pi);
    if (res == VK_ERROR_DEVICE_LOST) {
        rhi_device_set_lifecycle_result(dev, RHI_RESULT_DEVICE_LOST);
    } else if (res == VK_ERROR_OUT_OF_DATE_KHR || res == VK_SUBOPTIMAL_KHR) {
        rhi_device_set_lifecycle_result(dev, RHI_RESULT_OUT_OF_DATE);
    } else if (res != VK_SUCCESS) {
        rhi_device_set_lifecycle_result(dev, RHI_RESULT_ERROR);
    } else {
        rhi_device_set_lifecycle_result(dev, RHI_RESULT_OK);
    }
    if (res == VK_ERROR_OUT_OF_DATE_KHR || res == VK_SUBOPTIMAL_KHR) {
        RHIResult recreate_result = vk_recreate_swapchain(vk, dev->width, dev->height);
        if (recreate_result != RHI_RESULT_OK)
            rhi_device_set_lifecycle_result(dev, recreate_result);
    }

    vk->current_frame = (vk->current_frame + 1) % VK_MAX_FRAMES;
    vk->frame_submitted = false;
    dev->frame_damage_requested = false;
    dev->frame_damage_count = 0u;
    dev->frame_current_damage_count = 0u;
    dev->frame_partial_active = false;
    rhi_frame_owner_release(dev);
}

void rhi_cmd_set_scissor_top_left(RHICmdBuffer *cmd, u32 x, u32 y, u32 w,
                                  u32 h) {
    rhi_cmd_set_scissor(cmd, (i32)x, (i32)y, w, h);
}

u32 rhi_frame_index(RHIDevice *dev) {
    if (dev == NULL) return 0u;
    VKBackend *vk = vk_backend(dev);
    if (!vk) return 0u;
    return vk->current_frame;
}

void rhi_set_vsync(RHIDevice *dev, bool enabled) {
    if (!rhi_device_control_try_acquire(dev)) return;
    VKBackend *vk = vk_backend(dev);
    if (!vk) {
        rhi_device_control_release(dev);
        return;
    }
    vk->vsync = enabled;
    vk_recreate_swapchain(vk, dev->width, dev->height);
    rhi_device_control_release(dev);
}

/* Plan E Task 5 — bounded substring search for source that need not be
 * NUL-terminated. */
static bool vk_source_contains(const char *src, usize len, const char *needle) {
    usize n = strlen(needle);
    if (!src || len < n) return false;
    for (usize i = 0u; i + n <= len; i++)
        if (memcmp(src + i, needle, n) == 0) return true;
    return false;
}

/* Cache the std430 push-constant reflection of a freshly compiled shader. The
 * reflector fails closed (0 members) on macro/non-literal array sizes or
 * unsupported members — flag that so RHIPipelineBindings fails closed with a
 * warning instead of fabricating offsets; the legacy table below keeps
 * serving rhi_pipeline_get_uniform_location for such shaders. */
static void vk_reflect_push_cache(VKShaderData *sd, const char *source, usize len) {
    usize n = shader_reflect_push_constants(source, len, sd->push_members,
                                            sizeof(sd->push_members) /
                                            sizeof(sd->push_members[0]));
    if (n > 0u) {
        sd->push_member_count = (u32)n;
        return;
    }
    if (vk_source_contains(source, len, "push_constant")) {
        sd->push_reflect_failed = true;
        LOG_WARN("VK: push-constant reflection failed closed (macro/non-literal "
                 "array size or unsupported member) — bindings resolve will "
                 "return -1; the legacy uniform table keeps serving this shader");
    }
}

RHIShader rhi_shader_create(RHIDevice *dev, const char *source, usize len, bool is_fragment) {
    if (dev == NULL || source == NULL || len == 0u) return RHI_HANDLE_NULL;
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
    vk_reflect_push_cache(sd, source, len);
    dev->slots[idx].ptr = sd;
    dev->slots[idx].type = RHI_RES_SHADER;
    return rhi_make_handle(idx, dev->slots[idx].generation);
}

void rhi_shader_destroy(RHIDevice *dev, RHIShader shader) {
    if (dev == NULL) return;
    VKBackend *vk = vk_backend(dev);
    VKShaderData *sd = (VKShaderData *)rhi_get_resource_typed(dev, shader, RHI_RES_SHADER);
    if (!sd) return;
    vkDestroyShaderModule(vk->device, sd->module, NULL);
    free(sd->spirv);
    free(sd);
    rhi_free_slot(dev, shader);
}

RHIShader rhi_shader_create_compute(RHIDevice *dev, const char *source, usize len) {
    if (dev == NULL || source == NULL || len == 0u) return RHI_HANDLE_NULL;
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
    vk_reflect_push_cache(sd, source, len);
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
        if (vk->pipe_rp_formats[i] == vkfmt &&
            vk->pipe_rp_samples[i] == VK_SAMPLE_COUNT_1_BIT)
            return vk->pipe_rp_cache[i];
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
    VkAttachmentReference color_ref = {0, VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL};
    VkAttachmentReference depth_ref = {1, VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL};
    VkSubpassDependency dep = {0};
    vk_external_dep_color_depth(&dep);
    atts[1].format = VK_FORMAT_D32_SFLOAT;
    atts[1].samples = VK_SAMPLE_COUNT_1_BIT;
    atts[1].loadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
    atts[1].storeOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
    atts[1].stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
    atts[1].stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
    atts[1].initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
    atts[1].finalLayout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;
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
        /* R425: propagate failure instead of falling back to the swapchain
         * render pass — a pipeline built against it is render-pass
         * incompatible with the target FBO and misrenders. */
        LOG_WARN("VK: vk_pipeline_render_pass_fmt: vkCreateRenderPass failed");
        return VK_NULL_HANDLE;
    }
    vk->pipe_rp_formats[vk->pipe_rp_count] = vkfmt;
    vk->pipe_rp_samples[vk->pipe_rp_count] = VK_SAMPLE_COUNT_1_BIT;
    vk->pipe_rp_cache[vk->pipe_rp_count] = rp;
    vk->pipe_rp_count++;
    return rp;
}

static VkRenderPass vk_pipeline_render_pass_fmt_samples(VKBackend *vk, VkFormat vkfmt,
                                                         VkSampleCountFlagBits samples) {
    if (samples == VK_SAMPLE_COUNT_1_BIT)
        return vk_pipeline_render_pass_fmt(vk, vkfmt);
    if (!vk || !vk->feat_depth_stencil_resolve) return VK_NULL_HANDLE;
    for (u32 i = 0; i < vk->pipe_rp_count; i++) {
        if (vk->pipe_rp_formats[i] == vkfmt && vk->pipe_rp_samples[i] == samples)
            return vk->pipe_rp_cache[i];
    }
    if (vk->pipe_rp_count >= 8) return VK_NULL_HANDLE;

    VkAttachmentDescription2 atts[4] = {0};
    for (u32 i = 0; i < 4u; i++) atts[i].sType = VK_STRUCTURE_TYPE_ATTACHMENT_DESCRIPTION_2;
    atts[0].format = vkfmt;
    atts[0].samples = samples;
    atts[0].loadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
    atts[0].storeOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
    atts[0].stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
    atts[0].stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
    atts[0].initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
    atts[0].finalLayout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
    atts[1] = atts[0];
    atts[1].format = vkfmt;
    atts[1].samples = VK_SAMPLE_COUNT_1_BIT;
    atts[1].finalLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
    atts[2] = atts[0];
    atts[2].format = VK_FORMAT_D32_SFLOAT;
    atts[2].finalLayout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;
    atts[3] = atts[2];
    atts[3].samples = VK_SAMPLE_COUNT_1_BIT;
    atts[3].finalLayout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_READ_ONLY_OPTIMAL;

    VkAttachmentReference2 color_ref = {0};
    color_ref.sType = VK_STRUCTURE_TYPE_ATTACHMENT_REFERENCE_2;
    color_ref.attachment = 0;
    color_ref.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
    VkAttachmentReference2 resolve_ref = color_ref;
    resolve_ref.attachment = 1;
    VkAttachmentReference2 depth_ref = {0};
    depth_ref.sType = VK_STRUCTURE_TYPE_ATTACHMENT_REFERENCE_2;
    depth_ref.attachment = 2;
    depth_ref.layout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;
    VkAttachmentReference2 depth_resolve_ref = depth_ref;
    depth_resolve_ref.attachment = 3;

    VkSubpassDescriptionDepthStencilResolve ds_resolve = {0};
    ds_resolve.sType = VK_STRUCTURE_TYPE_SUBPASS_DESCRIPTION_DEPTH_STENCIL_RESOLVE;
    ds_resolve.depthResolveMode = vk->depth_resolve_mode;
    ds_resolve.stencilResolveMode = VK_RESOLVE_MODE_NONE;
    ds_resolve.pDepthStencilResolveAttachment = &depth_resolve_ref;
    VkSubpassDescription2 subpass = {0};
    subpass.sType = VK_STRUCTURE_TYPE_SUBPASS_DESCRIPTION_2;
    subpass.pNext = &ds_resolve;
    subpass.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
    subpass.colorAttachmentCount = 1;
    subpass.pColorAttachments = &color_ref;
    subpass.pResolveAttachments = &resolve_ref;
    subpass.pDepthStencilAttachment = &depth_ref;

    VkSubpassDependency2 dependency = {0};
    dependency.sType = VK_STRUCTURE_TYPE_SUBPASS_DEPENDENCY_2;
    VkSubpassDependency dep_masks = {0};
    vk_external_dep_color_depth(&dep_masks);
    dependency.srcSubpass = dep_masks.srcSubpass;
    dependency.dstSubpass = dep_masks.dstSubpass;
    dependency.srcStageMask = dep_masks.srcStageMask;
    dependency.srcAccessMask = dep_masks.srcAccessMask;
    dependency.dstStageMask = dep_masks.dstStageMask;
    dependency.dstAccessMask = dep_masks.dstAccessMask;
    VkRenderPassCreateInfo2 create_info = {0};
    create_info.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO_2;
    create_info.attachmentCount = 4;
    create_info.pAttachments = atts;
    create_info.subpassCount = 1;
    create_info.pSubpasses = &subpass;
    create_info.dependencyCount = 1;
    create_info.pDependencies = &dependency;
    VkRenderPass render_pass = VK_NULL_HANDLE;
    if (vkCreateRenderPass2(vk->device, &create_info, NULL, &render_pass) != VK_SUCCESS)
        return VK_NULL_HANDLE;
    vk->pipe_rp_formats[vk->pipe_rp_count] = vkfmt;
    vk->pipe_rp_samples[vk->pipe_rp_count] = samples;
    vk->pipe_rp_cache[vk->pipe_rp_count++] = render_pass;
    return render_pass;
}

static VkRenderPass vk_create_msaa_resume_pass(VKBackend *vk, VkFormat color_format,
                                                VkSampleCountFlagBits samples) {
    VkAttachmentDescription2 atts[4] = {0};
    for (u32 i = 0; i < 4u; i++) atts[i].sType = VK_STRUCTURE_TYPE_ATTACHMENT_DESCRIPTION_2;
    atts[0].format = color_format;
    atts[0].samples = samples;
    atts[0].loadOp = VK_ATTACHMENT_LOAD_OP_LOAD;
    atts[0].storeOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
    atts[0].initialLayout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
    atts[0].finalLayout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
    atts[1] = atts[0];
    atts[1].samples = VK_SAMPLE_COUNT_1_BIT;
    atts[1].storeOp = VK_ATTACHMENT_STORE_OP_STORE;
    atts[1].initialLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
    atts[1].finalLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
    atts[2] = atts[0];
    atts[2].format = VK_FORMAT_D32_SFLOAT;
    atts[2].initialLayout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;
    atts[2].finalLayout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;
    atts[3] = atts[2];
    atts[3].samples = VK_SAMPLE_COUNT_1_BIT;
    atts[3].storeOp = VK_ATTACHMENT_STORE_OP_STORE;
    atts[3].initialLayout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_READ_ONLY_OPTIMAL;
    atts[3].finalLayout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_READ_ONLY_OPTIMAL;

    VkAttachmentReference2 color = {VK_STRUCTURE_TYPE_ATTACHMENT_REFERENCE_2, NULL, 0,
                                    VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL, 0};
    VkAttachmentReference2 color_resolve = color;
    color_resolve.attachment = 1;
    VkAttachmentReference2 depth = color;
    depth.attachment = 2;
    depth.layout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;
    VkAttachmentReference2 depth_resolve = depth;
    depth_resolve.attachment = 3;
    VkSubpassDescriptionDepthStencilResolve ds_resolve = {0};
    ds_resolve.sType = VK_STRUCTURE_TYPE_SUBPASS_DESCRIPTION_DEPTH_STENCIL_RESOLVE;
    ds_resolve.depthResolveMode = vk->depth_resolve_mode;
    ds_resolve.stencilResolveMode = VK_RESOLVE_MODE_NONE;
    ds_resolve.pDepthStencilResolveAttachment = &depth_resolve;
    VkSubpassDescription2 subpass = {0};
    subpass.sType = VK_STRUCTURE_TYPE_SUBPASS_DESCRIPTION_2;
    subpass.pNext = &ds_resolve;
    subpass.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
    subpass.colorAttachmentCount = 1;
    subpass.pColorAttachments = &color;
    subpass.pResolveAttachments = &color_resolve;
    subpass.pDepthStencilAttachment = &depth;
    VkRenderPassCreateInfo2 info = {0};
    info.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO_2;
    info.attachmentCount = 4;
    info.pAttachments = atts;
    info.subpassCount = 1;
    info.pSubpasses = &subpass;
    VkSubpassDependency2 dependency = {0};
    dependency.sType = VK_STRUCTURE_TYPE_SUBPASS_DEPENDENCY_2;
    VkSubpassDependency dep_masks = {0};
    vk_external_dep_color_depth(&dep_masks);
    dependency.srcSubpass = dep_masks.srcSubpass;
    dependency.dstSubpass = dep_masks.dstSubpass;
    dependency.srcStageMask = dep_masks.srcStageMask;
    dependency.srcAccessMask = dep_masks.srcAccessMask;
    dependency.dstStageMask = dep_masks.dstStageMask;
    dependency.dstAccessMask = dep_masks.dstAccessMask;
    info.dependencyCount = 1;
    info.pDependencies = &dependency;
    VkRenderPass pass = VK_NULL_HANDLE;
    if (vkCreateRenderPass2(vk->device, &info, NULL, &pass) != VK_SUCCESS)
        LOG_WARN("VK: failed to create MSAA resume render pass");
    return pass;
}

static VkSampleCountFlagBits vk_sample_count(u32 count) {
    switch (count) {
        case 2u: return VK_SAMPLE_COUNT_2_BIT;
        case 4u: return VK_SAMPLE_COUNT_4_BIT;
        case 8u: return VK_SAMPLE_COUNT_8_BIT;
        case 16u: return VK_SAMPLE_COUNT_16_BIT;
        case 32u: return VK_SAMPLE_COUNT_32_BIT;
        case 64u: return VK_SAMPLE_COUNT_64_BIT;
        default: return VK_SAMPLE_COUNT_1_BIT;
    }
}

static bool vk_create_attachment_image(VKBackend *vk, VkFormat format,
                                       u32 width, u32 height,
                                       VkSampleCountFlagBits samples,
                                       VkImageUsageFlags usage,
                                       VkImageAspectFlags aspect,
                                       VkImage *out_image,
                                       VkDeviceMemory *out_memory,
                                       VkImageView *out_view) {
    VkImageCreateInfo image_info = {0};
    image_info.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
    image_info.imageType = VK_IMAGE_TYPE_2D;
    image_info.format = format;
    image_info.extent = (VkExtent3D){width, height, 1};
    image_info.mipLevels = 1;
    image_info.arrayLayers = 1;
    image_info.samples = samples;
    image_info.tiling = VK_IMAGE_TILING_OPTIMAL;
    image_info.usage = usage;
    image_info.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
    image_info.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
    if (vkCreateImage(vk->device, &image_info, NULL, out_image) != VK_SUCCESS)
        return false;

    VkMemoryRequirements requirements;
    vkGetImageMemoryRequirements(vk->device, *out_image, &requirements);
    VkMemoryAllocateInfo alloc_info = {0};
    alloc_info.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
    alloc_info.allocationSize = requirements.size;
    alloc_info.memoryTypeIndex = vk_find_memory(vk, requirements.memoryTypeBits,
                                                VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);
    if (alloc_info.memoryTypeIndex == UINT32_MAX ||
        vk_allocate_memory(vk, &alloc_info, out_memory) != VK_SUCCESS) {
        vkDestroyImage(vk->device, *out_image, NULL);
        *out_image = VK_NULL_HANDLE;
        return false;
    }
    if (vkBindImageMemory(vk->device, *out_image, *out_memory, 0) != VK_SUCCESS) {
        vkFreeMemory(vk->device, *out_memory, NULL);
        vkDestroyImage(vk->device, *out_image, NULL);
        *out_memory = VK_NULL_HANDLE;
        *out_image = VK_NULL_HANDLE;
        return false;
    }

    VkImageViewCreateInfo view_info = {0};
    view_info.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
    view_info.image = *out_image;
    view_info.viewType = VK_IMAGE_VIEW_TYPE_2D;
    view_info.format = format;
    view_info.subresourceRange.aspectMask = aspect;
    view_info.subresourceRange.levelCount = 1;
    view_info.subresourceRange.layerCount = 1;
    if (vkCreateImageView(vk->device, &view_info, NULL, out_view) != VK_SUCCESS) {
        vkFreeMemory(vk->device, *out_memory, NULL);
        vkDestroyImage(vk->device, *out_image, NULL);
        *out_memory = VK_NULL_HANDLE;
        *out_image = VK_NULL_HANDLE;
        return false;
    }
    return true;
}

static bool vk_sample_count_supported(const VKBackend *vk, u32 count) {
    if (!vk || rhi_sample_count_bit(count) == 0u) return false;
    VkSampleCountFlagBits samples = (VkSampleCountFlagBits)count;
    return (vk->device_props.limits.framebufferColorSampleCounts & samples) != 0 &&
           (vk->device_props.limits.framebufferDepthSampleCounts & samples) != 0;
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

/* R440: build a render pass for an MRT pipeline's base pipeline, with the same
 * color attachment formats (+ D32F depth, 1 sample) as the pass
 * rhi_mrt_fbo_create builds for the G-buffer FBO. Per the render-pass
 * compatibility rules (formats + sample counts), a pipeline created against
 * this pass may be bound inside the FBO's pass. The caller owns the returned
 * pass (destroyed with the pipeline). */
static VkRenderPass vk_mrt_pipeline_render_pass(VKBackend *vk, const RHIFormat *formats,
                                                u32 attachment_count) {
    if (!formats || attachment_count < 2 || attachment_count > RHI_MRT_MAX_ATTACHMENTS)
        return VK_NULL_HANDLE;

    VkAttachmentDescription atts[RHI_MRT_MAX_ATTACHMENTS + 1];
    VkAttachmentReference color_refs[RHI_MRT_MAX_ATTACHMENTS];
    memset(atts, 0, sizeof(atts));
    for (u32 i = 0; i < attachment_count; i++) {
        atts[i].format = vk_format_from_rhi(formats[i]);
        atts[i].samples = VK_SAMPLE_COUNT_1_BIT;
        atts[i].loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
        atts[i].storeOp = VK_ATTACHMENT_STORE_OP_STORE;
        atts[i].stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
        atts[i].stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
        atts[i].initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
        atts[i].finalLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
        color_refs[i].attachment = i;
        color_refs[i].layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
    }
    atts[attachment_count].format = VK_FORMAT_D32_SFLOAT;
    atts[attachment_count].samples = VK_SAMPLE_COUNT_1_BIT;
    atts[attachment_count].loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
    atts[attachment_count].storeOp = VK_ATTACHMENT_STORE_OP_STORE;
    atts[attachment_count].stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
    atts[attachment_count].stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
    atts[attachment_count].initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
    atts[attachment_count].finalLayout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_READ_ONLY_OPTIMAL;
    VkAttachmentReference depth_ref = { attachment_count,
                                        VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL };

    VkSubpassDescription sp = {0};
    sp.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
    sp.colorAttachmentCount = attachment_count;
    sp.pColorAttachments = color_refs;
    sp.pDepthStencilAttachment = &depth_ref;

    /* R442: must match rhi_mrt_fbo_create's pass exactly — render-pass
     * compatibility (VUID-vkCmdDrawIndexedIndirectCount-renderPass-02684)
     * compares dependencyCount; the FBO pass has 1, this had 0, so the R440
     * MRT pipeline was never actually compatible with the G-buffer pass. */
    VkSubpassDependency dep = {0};
    vk_external_dep_color_depth(&dep);

    VkRenderPassCreateInfo ci = {0};
    ci.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
    ci.attachmentCount = attachment_count + 1;
    ci.pAttachments = atts;
    ci.subpassCount = 1;
    ci.pSubpasses = &sp;
    ci.dependencyCount = 1;
    ci.pDependencies = &dep;

    VkRenderPass rp = VK_NULL_HANDLE;
    if (vkCreateRenderPass(vk->device, &ci, NULL, &rp) != VK_SUCCESS) {
        LOG_WARN("VK: vk_mrt_pipeline_render_pass: vkCreateRenderPass failed");
        return VK_NULL_HANDLE;
    }
    return rp;
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
    /* R425: a NULL render pass means vk_pipeline_render_pass_fmt failed;
     * report failure instead of building an incompatible pipeline. */
    if (rp == VK_NULL_HANDLE) return VK_NULL_HANDLE;
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
    } else if (desc->is_shadow_depth) {
        /* R440: shadow-depth vertex shaders (depth_only.vert,
         * point_shadow_depth_vk.vert) consume only location 0. Declaring the
         * full pos+normal+uv layout tripped validation performance warnings
         * ("vertex attribute not consumed"); declare position only. The
         * binding stride stays the mesh stride (default 32) — the same VBOs
         * are bound as before, only the attribute list shrinks. */
        stride = stride > 0 ? stride : 32;
        binding = vk_binding(stride);
        attrs[0] = vk_attr(0, 0, VK_FORMAT_R32G32B32_SFLOAT);
        vertex_input.vertexBindingDescriptionCount = 1;
        vertex_input.pVertexBindingDescriptions = &binding;
        vertex_input.vertexAttributeDescriptionCount = 1;
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
    msaa.rasterizationSamples = vk_sample_count(desc->sample_count);

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
    /* R440: an MRT pipeline's subpass has mrt_attachment_count color
     * attachments — the blend state must cover all of them (same per-attachment
     * state replicated). */
    VkPipelineColorBlendAttachmentState blend_atts[RHI_MRT_MAX_ATTACHMENTS];
    u32 blend_count = (desc->mrt_attachment_count > 1)
                    ? desc->mrt_attachment_count : 1;
    if (blend_count > RHI_MRT_MAX_ATTACHMENTS) blend_count = RHI_MRT_MAX_ATTACHMENTS;
    for (u32 i = 0; i < blend_count; i++) blend_atts[i] = blend_att;
    /* Separate RT0 alpha blending from RT1 velocity writes requires the
     * independentBlend feature.  Devices without it retain the legal,
     * shared blend state rather than creating an invalid pipeline. */
    if (desc->alpha_blend_color_only && vk->feat_independent_blend && blend_count > 1u)
        blend_atts[1].blendEnable = VK_FALSE;
    blend.attachmentCount = blend_count;
    blend.pAttachments = blend_atts;

    VkPipelineDepthStencilStateCreateInfo depth = {0};
    depth.sType = VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO;
    /* R445: fullscreen blit pipelines (depth_write_disable without
     * depth_compare_lequal) must not depth-test at all. The composite/postfx
     * render passes DO carry a D32 attachment (unlike assumed when this was
     * written), so the z=1.0 fullscreen triangle was tested against the
     * cleared 1.0 depth and LESS discarded every fragment — the entire
     * composite chain (tonemap/inspector/UI-underlay) never reached the
     * swapchain, leaving the pass clear color + UI text only. The scene
     * itself rendered fine (verified by direct scene-FBO readback), which is
     * why golden tests missed it. Mirrors the GL backend's R445 rule. */
    depth.depthTestEnable =
        (desc->depth_write_disable && !desc->depth_compare_lequal) ? VK_FALSE : VK_TRUE;
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
static VkPipeline vk_pipeline_for_fmt(VKBackend *vk, VKPipelineData *pd, VkFormat vkfmt,
                                      VkSampleCountFlagBits samples) {
    if (pd->is_compute || pd->base_color_fmt == VK_FORMAT_UNDEFINED) return pd->pipeline;
    if ((vkfmt == VK_FORMAT_UNDEFINED || vkfmt == pd->base_color_fmt) &&
        samples == pd->base_sample_count) return pd->pipeline;
    for (u32 i = 0; i < pd->variant_count; i++) {
        if (pd->variant_fmt[i] == vkfmt && pd->variant_samples[i] == samples)
            return pd->variant_pipe[i];
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

    RHIPipelineDesc variant_desc = pd->build_desc;
    variant_desc.sample_count = samples == VK_SAMPLE_COUNT_1_BIT ? 1u : (u32)samples;
    VkRenderPass rp = (samples == VK_SAMPLE_COUNT_1_BIT)
        ? vk_pipeline_render_pass_fmt(vk, vkfmt)
        : vk_pipeline_render_pass_fmt_samples(vk, vkfmt, samples);
    VkPipeline var = vk_build_graphics_pipeline(vk, &variant_desc, pd->layout,
                                                vs_mod, fs_mod, rp, NULL);
    vkDestroyShaderModule(vk->device, vs_mod, NULL);
    vkDestroyShaderModule(vk->device, fs_mod, NULL);
    if (var == VK_NULL_HANDLE) return pd->pipeline;

    pd->variant_fmt[pd->variant_count] = vkfmt;
    pd->variant_samples[pd->variant_count] = samples;
    pd->variant_pipe[pd->variant_count] = var;
    pd->variant_count++;
    return var;
}

/* Plan E Task 5: merge a stage's reflected push members into the pipeline's
 * table. Vert and frag declare the SAME push block, so duplicates keep the
 * first (vert) entry; a shader that failed closed contributes nothing — its
 * names stay on the legacy table and bindings resolve -1. Overflow beyond
 * VK_PUSH_MERGE_MAX drops late members the same fail-closed way. */
static void vk_pipeline_merge_push(VKPipelineData *pd, const VKShaderData *sd) {
    if (!sd) return;
    if (sd->push_reflect_failed) pd->push_reflect_failed = true;
    for (u32 i = 0u; i < sd->push_member_count; ++i) {
        const ShaderIOPushMember *m = &sd->push_members[i];
        bool dup = false;
        for (u32 j = 0u; j < pd->push_member_count; ++j) {
            if (strcmp(pd->push_members[j].name, m->name) == 0) { dup = true; break; }
        }
        if (dup) continue;
        if (pd->push_member_count >= VK_PUSH_MERGE_MAX) return;
        pd->push_members[pd->push_member_count++] = *m;
    }
}

RHIPipeline rhi_pipeline_create(RHIDevice *dev, const RHIPipelineDesc *desc) {
    if (!dev || !desc) return RHI_HANDLE_NULL;
    VKBackend *vk = vk_backend(dev);

    u32 requested_samples = desc->sample_count == 0u ? 1u : desc->sample_count;
    if (!desc->is_compute && requested_samples > 1u &&
        (desc->is_shadow_depth || desc->mrt_attachment_count > 1u)) {
        LOG_WARN("VK: multisample shadow/MRT pipelines are not supported");
        return RHI_HANDLE_NULL;
    }
    if (!desc->is_compute && requested_samples > 1u &&
        !rhi_offscreen_fbo_desc_validate(&dev->capabilities, &(RHIOffscreenFBODesc){
            .width = 1u,
            .height = 1u,
            .color_format = desc->color_format == RHI_FORMAT_UNDEFINED
                ? RHI_FORMAT_B8G8R8A8_UNORM : desc->color_format,
            .sample_count = requested_samples })) {
        LOG_WARN("VK: unsupported graphics pipeline sample count %u", requested_samples);
        return RHI_HANDLE_NULL;
    }

    if (desc->is_compute) {
        VKShaderData *cs_data = (VKShaderData *)rhi_get_resource_typed(dev, desc->frag, RHI_RES_SHADER);
        if (!cs_data) return RHI_HANDLE_NULL;

        VkPipelineShaderStageCreateInfo stage = {0};
        stage.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
        stage.stage = VK_SHADER_STAGE_COMPUTE_BIT;
        stage.module = cs_data->module;
        stage.pName = "main";

        VkDescriptorSetLayout set_layouts[5];
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
         u32 ray_query_set = VK_INVALID_SET;
         if (vk->ray_query_layout != VK_NULL_HANDLE) {
             ray_query_set = set_count;
             set_layouts[set_count++] = vk->ray_query_layout;
         }

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
        pd->ray_query_set = (u8)ray_query_set;
        vk_pipeline_merge_push(pd, cs_data);
        dev->slots[idx].ptr = pd;
        dev->slots[idx].type = RHI_RES_PIPELINE;
        return rhi_make_handle(idx, dev->slots[idx].generation);
    }

    VKShaderData *vs_data = (VKShaderData *)rhi_get_resource_typed(dev, desc->vert, RHI_RES_SHADER);
    VKShaderData *fs_data = (VKShaderData *)rhi_get_resource_typed(dev, desc->frag, RHI_RES_SHADER);
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
    u32 graphics_storage_set = VK_INVALID_SET;
    if (desc->uses_storage) {
        graphics_storage_set = set_count; /* R590: record the real index */
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

    /* R440: MRT pipelines (G-buffer) build their base pipeline against a pass
     * compatible with the MRT FBO's pass, not the single-attachment swapchain
     * pass — the fragment shader's outputs 1..N then have real attachments. */
    VkRenderPass mrt_rp = VK_NULL_HANDLE;
    VkRenderPass base_rp;
    if (desc->is_shadow_depth) {
        base_rp = vk->shadow_render_pass;
    } else if (desc->mrt_attachment_count > 1) {
        mrt_rp = vk_mrt_pipeline_render_pass(vk, desc->mrt_formats,
                                             desc->mrt_attachment_count);
        base_rp = mrt_rp;
    } else {
        VkSampleCountFlagBits pipeline_samples = vk_sample_count(desc->sample_count);
        base_rp = pipeline_samples == VK_SAMPLE_COUNT_1_BIT
            ? vk_pipeline_render_pass(vk, desc->color_format)
            : vk_pipeline_render_pass_fmt_samples(vk, vk_desc_base_color_fmt(vk, desc),
                                                  pipeline_samples);
    }
    u32 stride = 0;
    VkPipeline pipeline = vk_build_graphics_pipeline(vk, desc, layout, vs_data->module,
                                                     fs_data->module, base_rp, &stride);
    if (pipeline == VK_NULL_HANDLE) {
        if (mrt_rp) vkDestroyRenderPass(vk->device, mrt_rp, NULL);
        vkDestroyPipelineLayout(vk->device, layout, NULL);
        return RHI_HANDLE_NULL;
    }

    VKPipelineData *pd = calloc(1, sizeof(VKPipelineData));
    if (!pd) { vkDestroyPipeline(vk->device, pipeline, NULL); if (mrt_rp) vkDestroyRenderPass(vk->device, mrt_rp, NULL); vkDestroyPipelineLayout(vk->device, layout, NULL); return RHI_HANDLE_NULL; }
    u32 idx = rhi_alloc_slot(dev);
    pd->layout = layout;
    pd->pipeline = pipeline;
    pd->base_sample_count = vk_sample_count(desc->sample_count);
    pd->vertex_stride = stride;
    pd->push_range_size = push_range.size; /* R417: clamped at layout creation */
    pd->no_vertex_input = desc->no_vertex_input;
    pd->uses_texel_buffer = desc->uses_texel_buffer;
    pd->is_instanced = desc->is_instanced;
    pd->uses_storage = desc->uses_storage;
    /* R591: && !uses_storage — a skinned_vertex pipeline WITH a storage set
     * is the clustered-skinned variant (joint matrices ride the vertex SSBO
     * there); it must fall through to the clustered uniform table
     * (uses_texel_buffer && !is_instanced), not the G-Buffer table. The
     * existing skinned forward/G-Buffer pipelines never set uses_storage. */
    pd->skinned_gbuffer_layout =
        desc->skinned_vertex && desc->uses_texel_buffer && !desc->is_instanced &&
        !desc->uses_storage;
    pd->terrain_layout = desc->terrain_layout;
    pd->water_layout = desc->water_layout;
    pd->combined_aa_layout = desc->combined_aa_layout;
    pd->combined_color_layout = desc->combined_color_layout;
    pd->mrt_pipeline = desc->mrt_attachment_count > 1u;
    pd->storage_image_set = (u8)VK_INVALID_SET;
    pd->sampler_mip_set = (u8)VK_INVALID_SET;
    pd->ubo_set = (u8)graphics_ubo_set;
    pd->storage_set = (u8)graphics_storage_set; /* R590 */
    vk_pipeline_merge_push(pd, vs_data);
    vk_pipeline_merge_push(pd, fs_data);
    /* Variant support: depth-only shadow pipelines never need color variants
     * (marked UNDEFINED); color pipelines retain their SPIR-V + desc so a
     * render-pass-format variant can be built lazily at bind time. */
    pd->build_desc = *desc;
    pd->build_desc.vert = RHI_HANDLE_NULL;
    pd->build_desc.frag = RHI_HANDLE_NULL;
    pd->mrt_render_pass = mrt_rp;
    /* R440: MRT pipelines bind only inside their (compatible) MRT pass — never
     * build single-color-format variants for them. */
    if (desc->is_shadow_depth || desc->mrt_attachment_count > 1) {
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
    if (pd->mrt_render_pass) vkDestroyRenderPass(vk->device, pd->mrt_render_pass, NULL); /* R440 */
    vkDestroyPipelineLayout(vk->device, pd->layout, NULL);
    free(pd->vs_spirv);
    free(pd->fs_spirv);
    free(pd);
}

void rhi_pipeline_destroy(RHIDevice *dev, RHIPipeline pipe) {
    if (dev == NULL) return;
    VKBackend *vk = vk_backend(dev);
    VKPipelineData *pd = (VKPipelineData *)rhi_get_resource_typed(dev, pipe, RHI_RES_PIPELINE);
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
        vk_allocate_memory(vk, &smi, &staging_mem) != VK_SUCCESS) {
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
    if (vk->device_lost) return false; /* R578: fail fast on a dead device */
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
        vk_allocate_memory(vk, &smi, &staging_mem) != VK_SUCCESS) {
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
    VkResult sr = vkQueueSubmit(vk->graphics_queue, 1, &si, VK_NULL_HANDLE);
    vk_note_result(vk, sr); /* R578 */
    if (sr != VK_SUCCESS) {
        vkFreeCommandBuffers(vk->device, vk->cmd_pool, 1, &tmp_cb);
        vkFreeMemory(vk->device, staging_mem, NULL);
        vkDestroyBuffer(vk->device, staging, NULL);
        return false;
    }
    VkResult wr = vkQueueWaitIdle(vk->graphics_queue);
    vk_note_result(vk, wr); /* R578 */
    if (wr != VK_SUCCESS)
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
    if (dev == NULL || !rhi_buffer_desc_validate(desc)) return RHI_HANDLE_NULL;
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
    if (desc->usage & RHI_BUFFER_USAGE_AS_BUILD_INPUT)
        ci.usage |= VK_BUFFER_USAGE_ACCELERATION_STRUCTURE_BUILD_INPUT_READ_ONLY_BIT_KHR;
    if (desc->usage & RHI_BUFFER_USAGE_DEVICE_ADDRESS)
        ci.usage |= VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT;
    if (is_texel)                                     ci.usage |= VK_BUFFER_USAGE_UNIFORM_TEXEL_BUFFER_BIT;
    /* rhi_cmd_update_buffer records vkCmdUpdateBuffer for temporal UBOs and
     * GPU light texel buffers; Vulkan requires every such target to include
     * TRANSFER_DST usage. */
    if (desc->usage & (RHI_BUFFER_USAGE_UNIFORM | RHI_BUFFER_USAGE_TEXEL))
        ci.usage |= VK_BUFFER_USAGE_TRANSFER_DST_BIT;

    /* R181/R184: DEVICE_LOCAL when initial_data is provided for:
     *  - static VERTEX/INDEX meshes
     *  - GPU-only STORAGE (±INDIRECT, ±TEXEL) buffers (e.g. particle SSBOs,
     *    light_grid TEXEL|STORAGE). UNIFORM and dynamic VERTEX/INDEX stay HV.
     * R192-B: TEXEL no longer excludes gpu_storage (grid is CS-write/FS-read).
     * RT: AS build inputs also go DEVICE_LOCAL via staging upload — drivers
     * are inconsistent reading HOST_VISIBLE device-address buffers during
     * vkCmdBuildAccelerationStructuresKHR (observed: AMD RADV/Windows builds
     * an empty BLAS from HV inputs; trace returns miss). */
    bool mesh_only = (desc->usage & (RHI_BUFFER_USAGE_VERTEX | RHI_BUFFER_USAGE_INDEX)) != 0
        && (desc->usage & ~(RHI_BUFFER_USAGE_VERTEX | RHI_BUFFER_USAGE_INDEX)) == 0;
    bool gpu_storage = (desc->usage & RHI_BUFFER_USAGE_STORAGE) != 0
        && (desc->usage & (RHI_BUFFER_USAGE_UNIFORM
                           | RHI_BUFFER_USAGE_VERTEX | RHI_BUFFER_USAGE_INDEX)) == 0;
    bool as_input = (desc->usage & RHI_BUFFER_USAGE_AS_BUILD_INPUT) != 0;
    /* AS scratch: STORAGE|DEVICE_ADDRESS with no V/I/U and no initial data.
     * The GPU writes to scratch during device-side AS builds — HOST_VISIBLE
     * scratch has been observed to corrupt driver state on NVIDIA WDDM
     * (DEVICE_LOST after a "successful" build). Force DEVICE_LOCAL. */
    bool as_scratch = (desc->usage & RHI_BUFFER_USAGE_DEVICE_ADDRESS) != 0 &&
                      (desc->usage & RHI_BUFFER_USAGE_STORAGE) != 0 &&
                      (desc->usage & (RHI_BUFFER_USAGE_VERTEX |
                                      RHI_BUFFER_USAGE_INDEX |
                                      RHI_BUFFER_USAGE_UNIFORM)) == 0;
    bool device_local = (desc->initial_data != NULL &&
                         (mesh_only || gpu_storage || as_input)) || as_scratch;
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
    VkMemoryAllocateFlagsInfo address_flags = {0};
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

    if ((desc->usage & RHI_BUFFER_USAGE_DEVICE_ADDRESS) != 0u) {
        address_flags.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO;
        address_flags.flags = VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT;
        ai.pNext = &address_flags;
    }

    VkDeviceMemory mem;
    if (vk_allocate_memory(vk, &ai, &mem) != VK_SUCCESS) {
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
    if (dev == NULL) return;
    VKBackend *vk = vk_backend(dev);
    VKBufferData *bd = (VKBufferData *)rhi_get_resource_typed(dev, buf, RHI_RES_BUFFER);
    if (!bd) return;
    vk_wait_frames(vk);
    if (bd->mapped) vkUnmapMemory(vk->device, bd->memory);
    free(bd->map_shadow); /* C-BUF-4: abandoned mid-map shadow */
    if (bd->texel_view != VK_NULL_HANDLE) vkDestroyBufferView(vk->device, bd->texel_view, NULL);
    vkDestroyBuffer(vk->device, bd->buffer, NULL);
    vkFreeMemory(vk->device, bd->memory, NULL);
    free(bd);
    rhi_free_slot(dev, buf);
}

RHIAccelerationStructure rhi_backend_acceleration_structure_create(
    RHIDevice *dev, const RHIAccelerationStructureDesc *desc) {
    VKBackend *vk;
    VKAccelerationStructureData *ad;
    VkBufferCreateInfo buffer_info = {0};
    VkMemoryRequirements memory_requirements;
    VkMemoryAllocateInfo allocate_info = {0};
    VkAccelerationStructureCreateInfoKHR as_info = {0};
    PFN_vkCreateAccelerationStructureKHR create_as;
    VkAccelerationStructureTypeKHR as_type;
    u32 slot;

    if (dev == NULL || desc == NULL ||
        (dev->capabilities.feature_bits & RHI_FEATURE_ACCELERATION_STRUCTURE) == 0u) {
        return RHI_HANDLE_NULL;
    }
    vk = vk_backend(dev);
    if (vk == NULL || !rhi_acceleration_structure_desc_validate(desc)) {
        return RHI_HANDLE_NULL;
    }
    create_as = (PFN_vkCreateAccelerationStructureKHR)vkGetDeviceProcAddr(
        vk->device, "vkCreateAccelerationStructureKHR");
    if (create_as == NULL) return RHI_HANDLE_NULL;

    buffer_info.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
    buffer_info.size = (VkDeviceSize)desc->storage_size;
    buffer_info.usage = VK_BUFFER_USAGE_ACCELERATION_STRUCTURE_STORAGE_BIT_KHR |
                        VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT;
    buffer_info.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
    VkBuffer storage_buffer = VK_NULL_HANDLE;
    if (vkCreateBuffer(vk->device, &buffer_info, NULL, &storage_buffer) != VK_SUCCESS)
        return RHI_HANDLE_NULL;

    vkGetBufferMemoryRequirements(vk->device, storage_buffer, &memory_requirements);
    allocate_info.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
    allocate_info.allocationSize = memory_requirements.size;
    {
        VkMemoryAllocateFlagsInfo as_address_flags = {0};
        as_address_flags.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO;
        as_address_flags.flags = VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT;
        allocate_info.pNext = &as_address_flags;
    }
    allocate_info.memoryTypeIndex = vk_find_memory(
        vk, memory_requirements.memoryTypeBits, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);
    VkDeviceMemory storage_memory = VK_NULL_HANDLE;
    if (allocate_info.memoryTypeIndex == UINT32_MAX ||
        vk_allocate_memory(vk, &allocate_info, &storage_memory) != VK_SUCCESS) {
        vkDestroyBuffer(vk->device, storage_buffer, NULL);
        return RHI_HANDLE_NULL;
    }
    if (vkBindBufferMemory(vk->device, storage_buffer, storage_memory, 0) != VK_SUCCESS) {
        vkFreeMemory(vk->device, storage_memory, NULL);
        vkDestroyBuffer(vk->device, storage_buffer, NULL);
        return RHI_HANDLE_NULL;
    }

    as_type = desc->type == RHI_ACCELERATION_STRUCTURE_TOP_LEVEL
        ? VK_ACCELERATION_STRUCTURE_TYPE_TOP_LEVEL_KHR
        : VK_ACCELERATION_STRUCTURE_TYPE_BOTTOM_LEVEL_KHR;
    as_info.sType = VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_CREATE_INFO_KHR;
    as_info.buffer = storage_buffer;
    as_info.size = (VkDeviceSize)desc->storage_size;
    as_info.type = as_type;
    VkAccelerationStructureKHR handle = VK_NULL_HANDLE;
    if (create_as(vk->device, &as_info, NULL, &handle) != VK_SUCCESS) {
        vkFreeMemory(vk->device, storage_memory, NULL);
        vkDestroyBuffer(vk->device, storage_buffer, NULL);
        return RHI_HANDLE_NULL;
    }

    ad = calloc(1, sizeof(*ad));
    if (ad == NULL) {
        PFN_vkDestroyAccelerationStructureKHR destroy_as =
            (PFN_vkDestroyAccelerationStructureKHR)vkGetDeviceProcAddr(
                vk->device, "vkDestroyAccelerationStructureKHR");
        if (destroy_as) destroy_as(vk->device, handle, NULL);
        vkFreeMemory(vk->device, storage_memory, NULL);
        vkDestroyBuffer(vk->device, storage_buffer, NULL);
        return RHI_HANDLE_NULL;
    }
    slot = rhi_alloc_slot(dev);
    ad->handle = handle;
    ad->storage_buffer = storage_buffer;
    ad->storage_memory = storage_memory;
    ad->storage_size = desc->storage_size;
    dev->slots[slot].ptr = ad;
    dev->slots[slot].type = RHI_RES_ACCELERATION_STRUCTURE;
    return rhi_make_handle(slot, dev->slots[slot].generation);
}

void rhi_backend_acceleration_structure_destroy(
    RHIDevice *dev, RHIAccelerationStructure structure) {
    VKBackend *vk;
    VKAccelerationStructureData *ad;
    PFN_vkDestroyAccelerationStructureKHR destroy_as;
    if (dev == NULL) return;
    vk = vk_backend(dev);
    ad = (VKAccelerationStructureData *)rhi_get_resource_typed(
        dev, structure, RHI_RES_ACCELERATION_STRUCTURE);
    if (vk == NULL || ad == NULL) return;
    vk_wait_frames(vk);
    destroy_as = (PFN_vkDestroyAccelerationStructureKHR)vkGetDeviceProcAddr(
        vk->device, "vkDestroyAccelerationStructureKHR");
    if (destroy_as && ad->handle != VK_NULL_HANDLE)
        destroy_as(vk->device, ad->handle, NULL);
    vkDestroyBuffer(vk->device, ad->storage_buffer, NULL);
    vkFreeMemory(vk->device, ad->storage_memory, NULL);
    free(ad);
    rhi_free_slot(dev, structure);
}

bool rhi_blas_one_triangle_get_build_sizes(
    RHIDevice *dev, const RHIBLASOneTriangleDesc *desc,
    RHIAccelerationStructureBuildSizes *out_sizes) {
    VKBackend *vk;
    VkDeviceAddress vertex_address;
    VkDeviceAddress index_address;
    VkAccelerationStructureGeometryTrianglesDataKHR triangles = {0};
    VkAccelerationStructureGeometryKHR geometry = {0};
    VkAccelerationStructureBuildGeometryInfoKHR build = {0};
    VkAccelerationStructureBuildSizesInfoKHR sizes = {0};
    u32 primitive_count = 1u;

    if (out_sizes != NULL) memset(out_sizes, 0, sizeof(*out_sizes));
    if (dev == NULL || out_sizes == NULL ||
        (dev->capabilities.feature_bits & RHI_FEATURE_ACCELERATION_STRUCTURE) == 0u ||
        !rhi_blas_one_triangle_desc_validate(desc)) return false;
    vk = vk_backend(dev);
    if (vk == NULL || g_vk_get_as_build_sizes == NULL ||
        !vk_blas_buffer_address(vk, dev, desc->vertex_buffer,
                                desc->vertex_offset, &vertex_address) ||
        !vk_blas_buffer_address(vk, dev, desc->index_buffer,
                                desc->index_offset, &index_address)) return false;

    triangles.sType = VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_GEOMETRY_TRIANGLES_DATA_KHR;
    triangles.vertexFormat = VK_FORMAT_R32G32B32_SFLOAT;
    triangles.vertexData.deviceAddress = vertex_address;
    triangles.vertexStride = desc->vertex_stride;
    triangles.maxVertex = desc->vertex_count - 1u;
    triangles.indexType = VK_INDEX_TYPE_UINT32;
    triangles.indexData.deviceAddress = index_address;
    geometry.sType = VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_GEOMETRY_KHR;
    geometry.geometryType = VK_GEOMETRY_TYPE_TRIANGLES_KHR;
    geometry.geometry.triangles = triangles;
    geometry.flags = VK_GEOMETRY_OPAQUE_BIT_KHR;
    build.sType = VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_BUILD_GEOMETRY_INFO_KHR;
    build.type = VK_ACCELERATION_STRUCTURE_TYPE_BOTTOM_LEVEL_KHR;
    build.flags = VK_BUILD_ACCELERATION_STRUCTURE_PREFER_FAST_TRACE_BIT_KHR;
    build.geometryCount = 1u;
    build.pGeometries = &geometry;
    sizes.sType = VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_BUILD_SIZES_INFO_KHR;
    g_vk_get_as_build_sizes(vk->device, VK_ACCELERATION_STRUCTURE_BUILD_TYPE_DEVICE_KHR,
                            &build, &primitive_count, &sizes);
    out_sizes->acceleration_structure_size = (usize)sizes.accelerationStructureSize;
    out_sizes->build_scratch_size = (usize)sizes.buildScratchSize;
    return out_sizes->acceleration_structure_size != 0u &&
           out_sizes->build_scratch_size != 0u;
}

bool rhi_backend_cmd_build_blas_one_triangle(
    RHICmdBuffer *cmd, RHIDevice *dev, RHIAccelerationStructure blas,
    const RHIBLASOneTriangleDesc *desc, RHIBuffer scratch_buffer,
    usize scratch_offset) {
    VKBackend *vk;
    VKAccelerationStructureData *as_data;
    VKBufferData *scratch;
    VkDeviceAddress vertex_address, index_address, scratch_address;
    VkAccelerationStructureGeometryTrianglesDataKHR triangles = {0};
    VkAccelerationStructureGeometryKHR geometry = {0};
    VkAccelerationStructureBuildGeometryInfoKHR build = {0};
    VkAccelerationStructureBuildRangeInfoKHR range = {0};
    const VkAccelerationStructureBuildRangeInfoKHR *ranges[1] = {&range};

    if (dev == NULL || g_vk_build_as_host == NULL ||
        (dev->capabilities.feature_bits & RHI_FEATURE_ACCELERATION_STRUCTURE) == 0u ||
        !rhi_blas_one_triangle_desc_validate(desc)) return false;
    vk = vk_backend(dev);
    if (vk == NULL || vk->frame_started || cmd != NULL) return false;
    as_data = (VKAccelerationStructureData *)rhi_get_resource_typed(
        dev, blas, RHI_RES_ACCELERATION_STRUCTURE);
    scratch = (VKBufferData *)rhi_get_resource_typed(
        dev, scratch_buffer, RHI_RES_BUFFER);
    if (as_data == NULL || scratch == NULL ||
        !vk_blas_buffer_address(vk, dev, desc->vertex_buffer,
                                desc->vertex_offset, &vertex_address) ||
        !vk_blas_buffer_address(vk, dev, desc->index_buffer,
                                desc->index_offset, &index_address) ||
        !vk_blas_buffer_address(vk, dev, scratch_buffer,
                                scratch_offset, &scratch_address)) return false;

    triangles.sType = VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_GEOMETRY_TRIANGLES_DATA_KHR;
    triangles.vertexFormat = VK_FORMAT_R32G32B32_SFLOAT;
    triangles.vertexData.deviceAddress = vertex_address;
    triangles.vertexStride = desc->vertex_stride;
    triangles.maxVertex = desc->vertex_count - 1u;
    triangles.indexType = VK_INDEX_TYPE_UINT32;
    triangles.indexData.deviceAddress = index_address;
    geometry.sType = VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_GEOMETRY_KHR;
    geometry.geometryType = VK_GEOMETRY_TYPE_TRIANGLES_KHR;
    geometry.geometry.triangles = triangles;
    geometry.flags = VK_GEOMETRY_OPAQUE_BIT_KHR;
    build.sType = VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_BUILD_GEOMETRY_INFO_KHR;
    build.type = VK_ACCELERATION_STRUCTURE_TYPE_BOTTOM_LEVEL_KHR;
    build.flags = VK_BUILD_ACCELERATION_STRUCTURE_PREFER_FAST_TRACE_BIT_KHR;
    build.mode = VK_BUILD_ACCELERATION_STRUCTURE_MODE_BUILD_KHR;
    build.dstAccelerationStructure = as_data->handle;
    build.geometryCount = 1u;
    build.pGeometries = &geometry;
    build.scratchData.deviceAddress = scratch_address;
    range.primitiveCount = 1u;
    if (g_vk_build_as_host != NULL && g_vk_host_as_supported) {
        VkResult build_result = g_vk_build_as_host(
            vk->device, VK_NULL_HANDLE, 1u, &build, ranges);
        if (build_result == VK_SUCCESS) {
            LOG_INFO("RT BLAS built via host path");
            return true;
        }
        LOG_WARN("RT BLAS host build result=%d, falling back to device", (int)build_result);
    }
    /* Device-side fallback: one-shot submit. Keep PREFER_FAST_TRACE —
     * some drivers (NVIDIA WDDM) may produce invalid AS without it.
     * Use a dedicated command pool to avoid any interaction with the
     * engine's per-frame command buffers. */
    if (g_vk_cmd_build_as != NULL) {
        VkCommandPool as_pool = VK_NULL_HANDLE;
        VkCommandPoolCreateInfo pool_ci = {0};
        VkCommandBufferAllocateInfo alloc_info = {0};
        VkCommandBufferBeginInfo begin_info = {0};
        VkSubmitInfo submit = {0};
        VkCommandBuffer one_shot;
        pool_ci.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
        pool_ci.queueFamilyIndex = vk->graphics_family;
        if (vkCreateCommandPool(vk->device, &pool_ci, NULL, &as_pool) != VK_SUCCESS)
            return false;
        alloc_info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
        alloc_info.commandPool = as_pool;
        alloc_info.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
        alloc_info.commandBufferCount = 1u;
        if (vkAllocateCommandBuffers(vk->device, &alloc_info, &one_shot) != VK_SUCCESS) {
            vkDestroyCommandPool(vk->device, as_pool, NULL);
            return false;
        }
        begin_info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
        begin_info.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;
        if (vkBeginCommandBuffer(one_shot, &begin_info) != VK_SUCCESS) {
            vkFreeCommandBuffers(vk->device, as_pool, 1u, &one_shot);
            vkDestroyCommandPool(vk->device, as_pool, NULL);
            return false;
        }
        g_vk_cmd_build_as(one_shot, 1u, &build, ranges);
        if (vkEndCommandBuffer(one_shot) != VK_SUCCESS) {
            vkFreeCommandBuffers(vk->device, as_pool, 1u, &one_shot);
            vkDestroyCommandPool(vk->device, as_pool, NULL);
            return false;
        }
        submit.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
        submit.commandBufferCount = 1u;
        submit.pCommandBuffers = &one_shot;
        if (vkQueueSubmit(vk->graphics_queue, 1u, &submit, VK_NULL_HANDLE) != VK_SUCCESS ||
            vkQueueWaitIdle(vk->graphics_queue) != VK_SUCCESS) {
            vkFreeCommandBuffers(vk->device, as_pool, 1u, &one_shot);
            vkDestroyCommandPool(vk->device, as_pool, NULL);
            return false;
        }
        vkFreeCommandBuffers(vk->device, as_pool, 1u, &one_shot);
        vkDestroyCommandPool(vk->device, as_pool, NULL);
        LOG_INFO("RT BLAS built via device fallback path");
        return true;
    }
    LOG_WARN("RT BLAS build unavailable (no host or device path)");
    return false;
}

u64 rhi_backend_acceleration_structure_get_device_address(
    RHIDevice *dev, RHIAccelerationStructure structure) {
    VKBackend *vk;
    VKAccelerationStructureData *as_data;
    VkAccelerationStructureDeviceAddressInfoKHR info = {0};
    if (dev == NULL || g_vk_get_as_address == NULL) return 0u;
    vk = vk_backend(dev);
    as_data = (VKAccelerationStructureData *)rhi_get_resource_typed(
        dev, structure, RHI_RES_ACCELERATION_STRUCTURE);
    if (vk == NULL || as_data == NULL || as_data->handle == VK_NULL_HANDLE)
        return 0u;
    info.sType = VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_DEVICE_ADDRESS_INFO_KHR;
    info.accelerationStructure = as_data->handle;
    return (u64)g_vk_get_as_address(vk->device, &info);
}

bool rhi_backend_acceleration_structure_get_vk_handle(
    RHIDevice *dev, RHIAccelerationStructure structure, void **out_handle) {
    VKAccelerationStructureData *as_data;
    if (dev == NULL || out_handle == NULL) return false;
    as_data = (VKAccelerationStructureData *)rhi_get_resource_typed(
        dev, structure, RHI_RES_ACCELERATION_STRUCTURE);
    if (as_data == NULL || as_data->handle == VK_NULL_HANDLE) {
        *out_handle = NULL;
        return false;
    }
    *out_handle = (void *)(uintptr_t)as_data->handle;
    return true;
}

bool rhi_backend_tlas_one_instance_get_build_sizes(
    RHIDevice *dev, RHIBuffer instance_buffer,
    RHIAccelerationStructureBuildSizes *out_sizes) {
    VKBackend *vk;
    VKBufferData *instance_data;
    VkDeviceAddress instance_address;
    VkAccelerationStructureGeometryKHR geometry = {0};
    VkAccelerationStructureBuildGeometryInfoKHR build = {0};
    VkAccelerationStructureBuildSizesInfoKHR sizes = {0};
    u32 primitive_count = 1u;

    if (dev == NULL || g_vk_get_as_build_sizes == NULL ||
        (dev->capabilities.feature_bits & RHI_FEATURE_ACCELERATION_STRUCTURE) == 0u)
        return false;
    vk = vk_backend(dev);
    instance_data = (VKBufferData *)rhi_get_resource_typed(
        dev, instance_buffer, RHI_RES_BUFFER);
    if (vk == NULL || instance_data == NULL ||
        instance_data->size < RHI_TLAS_INSTANCE_SIZE ||
        !vk_blas_buffer_address(vk, dev, instance_buffer, 0u,
                                &instance_address)) return false;

    geometry.sType = VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_GEOMETRY_KHR;
    geometry.geometryType = VK_GEOMETRY_TYPE_INSTANCES_KHR;
    geometry.geometry.instances.sType =
        VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_GEOMETRY_INSTANCES_DATA_KHR;
    geometry.geometry.instances.arrayOfPointers = VK_FALSE;
    geometry.geometry.instances.data.deviceAddress = instance_address;
    build.sType = VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_BUILD_GEOMETRY_INFO_KHR;
    build.type = VK_ACCELERATION_STRUCTURE_TYPE_TOP_LEVEL_KHR;
    build.flags = VK_BUILD_ACCELERATION_STRUCTURE_PREFER_FAST_TRACE_BIT_KHR;
    build.geometryCount = 1u;
    build.pGeometries = &geometry;
    sizes.sType = VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_BUILD_SIZES_INFO_KHR;
    g_vk_get_as_build_sizes(vk->device, VK_ACCELERATION_STRUCTURE_BUILD_TYPE_DEVICE_KHR,
                            &build, &primitive_count, &sizes);
    out_sizes->acceleration_structure_size = (usize)sizes.accelerationStructureSize;
    out_sizes->build_scratch_size = (usize)sizes.buildScratchSize;
    return out_sizes->acceleration_structure_size != 0u &&
           out_sizes->build_scratch_size != 0u;
}

bool rhi_backend_cmd_build_tlas_one_instance(
    RHICmdBuffer *cmd, RHIDevice *dev, RHIAccelerationStructure tlas,
    RHIBuffer instance_buffer, RHIBuffer scratch_buffer,
    usize scratch_offset) {
    VKBackend *vk;
    VKAccelerationStructureData *as_data;
    VKBufferData *instance_data;
    VkDeviceAddress instance_address, scratch_address;
    VkAccelerationStructureGeometryKHR geometry = {0};
    VkAccelerationStructureBuildGeometryInfoKHR build = {0};
    VkAccelerationStructureBuildRangeInfoKHR range = {0};
    const VkAccelerationStructureBuildRangeInfoKHR *ranges[1] = {&range};

    if (cmd == NULL && dev == NULL) return false;
    if (dev == NULL || g_vk_build_as_host == NULL ||
        (dev->capabilities.feature_bits & RHI_FEATURE_ACCELERATION_STRUCTURE) == 0u)
        return false;
    vk = vk_backend(dev);
    if (vk == NULL || vk->frame_started || cmd != NULL) return false;
    as_data = (VKAccelerationStructureData *)rhi_get_resource_typed(
        dev, tlas, RHI_RES_ACCELERATION_STRUCTURE);
    instance_data = (VKBufferData *)rhi_get_resource_typed(
        dev, instance_buffer, RHI_RES_BUFFER);
    if (as_data == NULL || instance_data == NULL ||
        instance_data->size < RHI_TLAS_INSTANCE_SIZE ||
        !vk_blas_buffer_address(vk, dev, instance_buffer, 0u,
                                &instance_address) ||
        !vk_blas_buffer_address(vk, dev, scratch_buffer,
                                scratch_offset, &scratch_address)) return false;

    geometry.sType = VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_GEOMETRY_KHR;
    geometry.geometryType = VK_GEOMETRY_TYPE_INSTANCES_KHR;
    geometry.geometry.instances.sType =
        VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_GEOMETRY_INSTANCES_DATA_KHR;
    geometry.geometry.instances.arrayOfPointers = VK_FALSE;
    geometry.geometry.instances.data.deviceAddress = instance_address;
    build.sType = VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_BUILD_GEOMETRY_INFO_KHR;
    build.type = VK_ACCELERATION_STRUCTURE_TYPE_TOP_LEVEL_KHR;
    build.flags = VK_BUILD_ACCELERATION_STRUCTURE_PREFER_FAST_TRACE_BIT_KHR;
    build.mode = VK_BUILD_ACCELERATION_STRUCTURE_MODE_BUILD_KHR;
    build.dstAccelerationStructure = as_data->handle;
    build.geometryCount = 1u;
    build.pGeometries = &geometry;
    build.scratchData.deviceAddress = scratch_address;
    range.primitiveCount = 1u;
    if (g_vk_build_as_host != NULL && g_vk_host_as_supported) {
        VkResult build_result = g_vk_build_as_host(
            vk->device, VK_NULL_HANDLE, 1u, &build, ranges);
        if (build_result == VK_SUCCESS) {
            LOG_INFO("RT TLAS built via host path");
            return true;
        }
        LOG_WARN("RT TLAS host build result=%d, falling back to device", (int)build_result);
    }
    if (g_vk_cmd_build_as != NULL) {
        VkCommandPool as_pool = VK_NULL_HANDLE;
        VkCommandPoolCreateInfo pool_ci = {0};
        VkCommandBufferAllocateInfo alloc_info = {0};
        VkCommandBufferBeginInfo begin_info = {0};
        VkSubmitInfo submit = {0};
        VkCommandBuffer one_shot;
        pool_ci.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
        pool_ci.queueFamilyIndex = vk->graphics_family;
        if (vkCreateCommandPool(vk->device, &pool_ci, NULL, &as_pool) != VK_SUCCESS)
            return false;
        alloc_info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
        alloc_info.commandPool = as_pool;
        alloc_info.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
        alloc_info.commandBufferCount = 1u;
        if (vkAllocateCommandBuffers(vk->device, &alloc_info, &one_shot) != VK_SUCCESS) {
            vkDestroyCommandPool(vk->device, as_pool, NULL);
            return false;
        }
        begin_info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
        begin_info.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;
        if (vkBeginCommandBuffer(one_shot, &begin_info) != VK_SUCCESS) {
            vkFreeCommandBuffers(vk->device, as_pool, 1u, &one_shot);
            vkDestroyCommandPool(vk->device, as_pool, NULL);
            return false;
        }
        g_vk_cmd_build_as(one_shot, 1u, &build, ranges);
        if (vkEndCommandBuffer(one_shot) != VK_SUCCESS) {
            vkFreeCommandBuffers(vk->device, as_pool, 1u, &one_shot);
            vkDestroyCommandPool(vk->device, as_pool, NULL);
            return false;
        }
        submit.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
        submit.commandBufferCount = 1u;
        submit.pCommandBuffers = &one_shot;
        if (vkQueueSubmit(vk->graphics_queue, 1u, &submit, VK_NULL_HANDLE) != VK_SUCCESS ||
            vkQueueWaitIdle(vk->graphics_queue) != VK_SUCCESS) {
            vkFreeCommandBuffers(vk->device, as_pool, 1u, &one_shot);
            vkDestroyCommandPool(vk->device, as_pool, NULL);
            return false;
        }
        vkFreeCommandBuffers(vk->device, as_pool, 1u, &one_shot);
        vkDestroyCommandPool(vk->device, as_pool, NULL);
        LOG_INFO("RT TLAS built via device fallback path");
        return true;
    }
    LOG_WARN("RT TLAS build unavailable (no host or device path)");
    return false;
}

RHITexture rhi_texture_create(RHIDevice *dev, const RHITextureDesc *desc) {
    if (dev == NULL || !rhi_texture_desc_validate(desc)) return RHI_HANDLE_NULL;
    VKBackend *vk = vk_backend(dev);
    VkFormat fmt = vk_format_from_rhi(desc->format);
    bool is_depth = (desc->format == RHI_FORMAT_D32_FLOAT);
    /* Depth textures must use the DEPTH aspect (view + barriers); COLOR is
     * invalid for D32 and trips VUID-VkImageViewCreateInfo-image-01762. */
    VkImageAspectFlags aspect = is_depth ? VK_IMAGE_ASPECT_DEPTH_BIT
                                         : VK_IMAGE_ASPECT_COLOR_BIT;

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
     * exposed through a STORAGE_IMAGE descriptor.
     * R552-A: +TRANSFER_SRC so color textures can be read back via
     * rhi_texture_read_pixels (same class of fix as R442/R550-E; the
     * bake-time material texture-array build in the demo reads back
     * albedo/MR textures and tripped
     * VUID-vkCmdCopyImageToBuffer-srcImage-00186 /
     * VUID-VkImageMemoryBarrier-oldLayout-01212 without it). */
    if (is_depth) {
        /* Depth textures are rendered into (shadow/atlas paths).
         * R602: +TRANSFER_SRC so D32 can be read back via
         * rhi_texture_read_pixels (native f32 depth semantics — same class
         * as the R552-A color-side fix). */
        ci.usage |= VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT |
                    VK_IMAGE_USAGE_TRANSFER_SRC_BIT;
    } else {
        ci.usage |= VK_IMAGE_USAGE_STORAGE_BIT | VK_IMAGE_USAGE_TRANSFER_SRC_BIT;
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
    if (vk_allocate_memory(vk, &ai, &mem) != VK_SUCCESS) {
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
    vci.subresourceRange.aspectMask = aspect;
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
        /* R417: bpp from desc->format + 64-bit math — the old 32-bit w*h*4
         * wrapped past 4GB and under-allocated 2x for 8-bpp formats. */
        VkDeviceSize data_size = (VkDeviceSize)desc->width * desc->height
                               * rhi_format_bpp(desc->format);

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
        if (vk_allocate_memory(vk, &smi, &staging_mem) != VK_SUCCESS) {
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
        barrier.subresourceRange.aspectMask = aspect;
        /* R430: transition the full mip chain — the view spans ci.mipLevels
         * and mips 1+ would otherwise stay UNDEFINED. */
        barrier.subresourceRange.levelCount = ci.mipLevels;
        barrier.subresourceRange.layerCount = 1;
        barrier.srcAccessMask = 0;
        barrier.dstAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
        vkCmdPipelineBarrier(tmp_cb, VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT,
            VK_PIPELINE_STAGE_TRANSFER_BIT, 0, 0, NULL, 0, NULL, 1, &barrier);

        VkBufferImageCopy region = {0};
        region.bufferOffset = 0;
        region.bufferRowLength = 0;
        region.bufferImageHeight = 0;
        region.imageSubresource.aspectMask = aspect;
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
        barrier2.subresourceRange.aspectMask = aspect;
        barrier2.subresourceRange.levelCount = ci.mipLevels; /* R430: full chain */
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
        if (vk_wait_fence(vk, upload_fence) != VK_SUCCESS)
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
        barrier.subresourceRange.aspectMask = aspect;
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
        if (vk_wait_fence(vk, layout_fence) != VK_SUCCESS) {
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
    if (dev == NULL) return;
    VKBackend *vk = vk_backend(dev);
    VKTextureData *td = (VKTextureData *)rhi_get_resource_typed(dev, tex, RHI_RES_TEXTURE);
    if (!td || !data || size == 0) return;
    if (mip_level >= td->mip_levels) return;

    /* R417: reject uploads whose dims don't match the actual mip extent or
     * whose size can't cover w*h*4 bytes (RGBA8 streaming, matching the GL
     * backend) — otherwise the copy extent can exceed the staging buffer. */
    u32 mip_w = td->width >> mip_level;  if (mip_w == 0) mip_w = 1;
    u32 mip_h = td->height >> mip_level; if (mip_h == 0) mip_h = 1;
    if (width != mip_w || height != mip_h) return;
    if (size < (usize)width * height * 4u) return;

    /* R175: Reclaim previous fire-and-forget upload before allocating a new one. */
    if (vk_mip_upload_owned_by_other(vk)) {
        LOG_WARN("VK: mip upload slot is owned by another device");
        return;
    }
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
    if (vk_allocate_memory(vk, &smi, &staging_mem) != VK_SUCCESS) {
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
    g_mip_upload_pending.owner_backend = vk;
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

/* R441: record callback for vk_texture_sync_submit — pre barrier into
 * mid_layout, optional buffer<->image copy, post barrier back to old_layout
 * (copies only; barrier-only transitions end in mid_layout). */
typedef struct {
    VkImage       image;
    VkBuffer      staging;
    u32           width, height;
    u32           base_layer, layer_count;
    VkImageLayout old_layout, mid_layout;
    bool          copy;
    /* R602: aspect for the barrier + copy subresource — COLOR for every
     * pre-existing caller (texture-array paths), DEPTH when reading back a
     * D32 texture (pre-R602 the hardcoded COLOR aspect tripped
     * VUID-09601/09105 on depth images). */
    VkImageAspectFlags aspect;
} VKArrayTransferCtx;

static void vk_array_transfer_record(VkCommandBuffer cb, void *p) {
    VKArrayTransferCtx *c = (VKArrayTransferCtx *)p;
    bool to_image = (c->mid_layout == VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL);

    VkImageMemoryBarrier pre = {0};
    pre.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
    pre.oldLayout = c->old_layout;
    pre.newLayout = c->mid_layout;
    pre.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
    pre.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
    pre.image = c->image;
    pre.subresourceRange.aspectMask = c->aspect;
    pre.subresourceRange.levelCount = 1;
    pre.subresourceRange.baseArrayLayer = c->base_layer;
    pre.subresourceRange.layerCount = c->layer_count;
    pre.srcAccessMask = (c->old_layout == VK_IMAGE_LAYOUT_UNDEFINED) ? 0
                      : VK_ACCESS_SHADER_READ_BIT;
    pre.dstAccessMask = to_image ? VK_ACCESS_TRANSFER_WRITE_BIT
                                 : VK_ACCESS_TRANSFER_READ_BIT;
    VkPipelineStageFlags src_stage = (c->old_layout == VK_IMAGE_LAYOUT_UNDEFINED)
        ? VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT : VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT;
    if (!c->copy) {
        /* Barrier-only (create-time layout transition). */
        pre.dstAccessMask = VK_ACCESS_SHADER_READ_BIT;
        vkCmdPipelineBarrier(cb, src_stage, VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT,
                             0, 0, NULL, 0, NULL, 1, &pre);
        return;
    }
    vkCmdPipelineBarrier(cb, src_stage, VK_PIPELINE_STAGE_TRANSFER_BIT,
                         0, 0, NULL, 0, NULL, 1, &pre);

    VkBufferImageCopy region = {0};
    region.imageSubresource.aspectMask = c->aspect;
    region.imageSubresource.mipLevel = 0;
    region.imageSubresource.baseArrayLayer = c->base_layer;
    region.imageSubresource.layerCount = c->layer_count;
    region.imageExtent = (VkExtent3D){c->width, c->height, 1};
    if (to_image) {
        vkCmdCopyBufferToImage(cb, c->staging, c->image, c->mid_layout, 1, &region);
    } else {
        vkCmdCopyImageToBuffer(cb, c->image, c->mid_layout, c->staging, 1, &region);
    }

    VkImageMemoryBarrier post = pre;
    post.oldLayout = c->mid_layout;
    post.newLayout = c->old_layout;
    post.srcAccessMask = pre.dstAccessMask;
    post.dstAccessMask = VK_ACCESS_SHADER_READ_BIT;
    vkCmdPipelineBarrier(cb, VK_PIPELINE_STAGE_TRANSFER_BIT,
                         VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT,
                         0, 0, NULL, 0, NULL, 1, &post);
}

/* R441: one-shot synchronous staging submit (bake-time texture-array paths).
 * Returns false on any failure; on success the GPU work has completed. */
static bool vk_texture_sync_submit(VKBackend *vk, VkBuffer staging,
                                   VkDeviceMemory staging_mem,
                                   void (*record)(VkCommandBuffer, void *), void *record_ctx) {
    VkCommandBufferAllocateInfo cbai = {0};
    cbai.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    cbai.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
    cbai.commandPool = vk->cmd_pool;
    cbai.commandBufferCount = 1;
    VkCommandBuffer cb;
    if (vkAllocateCommandBuffers(vk->device, &cbai, &cb) != VK_SUCCESS) return false;
    VkCommandBufferBeginInfo cbi = {0};
    cbi.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
    cbi.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;
    if (vkBeginCommandBuffer(cb, &cbi) != VK_SUCCESS) {
        vkFreeCommandBuffers(vk->device, vk->cmd_pool, 1, &cb);
        return false;
    }
    record(cb, record_ctx);
    if (vkEndCommandBuffer(cb) != VK_SUCCESS) {
        vkFreeCommandBuffers(vk->device, vk->cmd_pool, 1, &cb);
        return false;
    }
    VkFence fence;
    VkFenceCreateInfo fci = {0};
    fci.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
    if (vkCreateFence(vk->device, &fci, NULL, &fence) != VK_SUCCESS) {
        vkFreeCommandBuffers(vk->device, vk->cmd_pool, 1, &cb);
        return false;
    }
    VkSubmitInfo si = {0};
    si.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
    si.commandBufferCount = 1;
    si.pCommandBuffers = &cb;
    bool ok = vkQueueSubmit(vk->graphics_queue, 1, &si, fence) == VK_SUCCESS &&
              vk_wait_fence(vk, fence) == VK_SUCCESS;
    vkDestroyFence(vk->device, fence, NULL);
    vkFreeCommandBuffers(vk->device, vk->cmd_pool, 1, &cb);
    if (staging) vkDestroyBuffer(vk->device, staging, NULL);
    if (staging_mem) vkFreeMemory(vk->device, staging_mem, NULL);
    return ok;
}

/* Host-visible staging buffer + memcpy of `size` bytes from `src` (NULL src
 * leaves it mapped-out/unwritten). */
static bool vk_texture_staging_alloc(VKBackend *vk, VkDeviceSize size, const void *src,
                                     VkBuffer *out_buf, VkDeviceMemory *out_mem) {
    VkBufferCreateInfo bci = {0};
    bci.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
    bci.size = size;
    bci.usage = VK_BUFFER_USAGE_TRANSFER_SRC_BIT | VK_BUFFER_USAGE_TRANSFER_DST_BIT;
    bci.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
    if (vkCreateBuffer(vk->device, &bci, NULL, out_buf) != VK_SUCCESS) return false;
    VkMemoryRequirements smr;
    vkGetBufferMemoryRequirements(vk->device, *out_buf, &smr);
    VkMemoryAllocateInfo smi = {0};
    smi.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
    smi.allocationSize = smr.size;
    smi.memoryTypeIndex = vk_find_memory(vk, smr.memoryTypeBits,
        VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);
    if (vk_allocate_memory(vk, &smi, out_mem) != VK_SUCCESS) {
        vkDestroyBuffer(vk->device, *out_buf, NULL);
        return false;
    }
    if (vkBindBufferMemory(vk->device, *out_buf, *out_mem, 0) != VK_SUCCESS) {
        vkFreeMemory(vk->device, *out_mem, NULL);
        vkDestroyBuffer(vk->device, *out_buf, NULL);
        return false;
    }
    if (src) {
        void *mapped;
        if (vkMapMemory(vk->device, *out_mem, 0, size, 0, &mapped) != VK_SUCCESS) {
            vkFreeMemory(vk->device, *out_mem, NULL);
            vkDestroyBuffer(vk->device, *out_buf, NULL);
            return false;
        }
        memcpy(mapped, src, (size_t)size);
        vkUnmapMemory(vk->device, *out_mem);
    }
    return true;
}

/* R441: 2D texture array — all layers start in SHADER_READ_ONLY (zero
 * content), per-layer uploads transition individual layers. */
RHITexture rhi_texture_array_create(RHIDevice *dev, u32 width, u32 height,
                                    u32 layers, RHIFormat fmt) {
    if (dev == NULL) return RHI_HANDLE_NULL;
    VKBackend *vk = vk_backend(dev);
    if (!vk || width == 0 || height == 0 || layers == 0 ||
        width > RHI_MAX_DRAWABLE_DIMENSION ||
        height > RHI_MAX_DRAWABLE_DIMENSION ||
        layers > RHI_MAX_TEXTURE_ARRAY_LAYERS) return RHI_HANDLE_NULL;
    if (fmt != RHI_FORMAT_R8G8B8A8_UNORM && fmt != RHI_FORMAT_B8G8R8A8_UNORM) {
        LOG_WARN("VK: texture array only supports 8-bit RGBA formats");
        return RHI_HANDLE_NULL;
    }
    VkFormat vkfmt = vk_format_from_rhi(fmt);

    VkImageCreateInfo ci = {0};
    ci.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
    ci.imageType = VK_IMAGE_TYPE_2D;
    ci.format = vkfmt;
    ci.extent = (VkExtent3D){width, height, 1};
    ci.mipLevels = 1;
    ci.arrayLayers = layers;
    ci.samples = VK_SAMPLE_COUNT_1_BIT;
    ci.tiling = VK_IMAGE_TILING_OPTIMAL;
    ci.usage = VK_IMAGE_USAGE_SAMPLED_BIT | VK_IMAGE_USAGE_TRANSFER_DST_BIT |
               VK_IMAGE_USAGE_TRANSFER_SRC_BIT;
    ci.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
    ci.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;

    VkImage image;
    if (vkCreateImage(vk->device, &ci, NULL, &image) != VK_SUCCESS) {
        LOG_WARN("VK: failed to create texture array image");
        return RHI_HANDLE_NULL;
    }
    VkMemoryRequirements mem_req;
    vkGetImageMemoryRequirements(vk->device, image, &mem_req);
    VkMemoryAllocateInfo ai = {0};
    ai.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
    ai.allocationSize = mem_req.size;
    ai.memoryTypeIndex = vk_find_memory(vk, mem_req.memoryTypeBits, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);
    VkDeviceMemory mem;
    if (vk_allocate_memory(vk, &ai, &mem) != VK_SUCCESS ||
        vkBindImageMemory(vk->device, image, mem, 0) != VK_SUCCESS) {
        LOG_WARN("VK: failed to allocate/bind texture array memory");
        vkDestroyImage(vk->device, image, NULL);
        return RHI_HANDLE_NULL;
    }

    VkImageViewCreateInfo vci = {0};
    vci.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
    vci.image = image;
    vci.viewType = VK_IMAGE_VIEW_TYPE_2D_ARRAY;
    vci.format = vkfmt;
    vci.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
    vci.subresourceRange.levelCount = 1;
    vci.subresourceRange.layerCount = layers;
    VkImageView view;
    if (vkCreateImageView(vk->device, &vci, NULL, &view) != VK_SUCCESS) {
        LOG_WARN("VK: failed to create texture array view");
        vkFreeMemory(vk->device, mem, NULL);
        vkDestroyImage(vk->device, image, NULL);
        return RHI_HANDLE_NULL;
    }

    VKTextureData *td = calloc(1, sizeof(VKTextureData));
    if (!td) {
        vkDestroyImageView(vk->device, view, NULL);
        vkFreeMemory(vk->device, mem, NULL);
        vkDestroyImage(vk->device, image, NULL);
        return RHI_HANDLE_NULL;
    }
    td->image = image;
    td->view = view;
    td->memory = mem;
    td->width = width;
    td->height = height;
    td->format = vkfmt;
    td->mip_levels = 1;
    td->layers = layers;

    /* All layers UNDEFINED -> SHADER_READ_ONLY (upload_layer transitions the
     * single layer it writes through TRANSFER_DST and back). */
    VKArrayTransferCtx ctx = {0};
    ctx.image = image;
    ctx.width = width;
    ctx.height = height;
    ctx.base_layer = 0;
    ctx.layer_count = layers;
    ctx.old_layout = VK_IMAGE_LAYOUT_UNDEFINED;
    ctx.mid_layout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
    ctx.copy = false;
    ctx.aspect = VK_IMAGE_ASPECT_COLOR_BIT;
    if (!vk_texture_sync_submit(vk, VK_NULL_HANDLE, VK_NULL_HANDLE,
                                vk_array_transfer_record, &ctx)) {
        LOG_WARN("VK: texture array layout transition failed");
        vkDestroyImageView(vk->device, view, NULL);
        vkFreeMemory(vk->device, mem, NULL);
        vkDestroyImage(vk->device, image, NULL);
        free(td);
        return RHI_HANDLE_NULL;
    }
    td->mip_layout[0] = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;

    u32 idx = rhi_alloc_slot(dev);
    dev->slots[idx].ptr = td;
    dev->slots[idx].type = RHI_RES_TEXTURE;
    return rhi_make_handle(idx, dev->slots[idx].generation);
}

void rhi_texture_array_upload_layer(RHIDevice *dev, RHITexture tex,
                                    u32 layer, const void *rgba8, usize size) {
    VKBackend *vk = vk_backend(dev);
    VKTextureData *td = (VKTextureData *)rhi_get_resource_typed(dev, tex, RHI_RES_TEXTURE);
    if (!vk || !td || td->layers == 0 || !rgba8) return;
    if (layer >= td->layers) return;
    /* R441: same host-OOB guard class as R417 — the copy reads w*h*4 bytes. */
    VkDeviceSize data_size = (VkDeviceSize)td->width * td->height * 4u;
    if (size < (usize)data_size) return;

    VkBuffer staging;
    VkDeviceMemory staging_mem;
    if (!vk_texture_staging_alloc(vk, data_size, rgba8, &staging, &staging_mem)) {
        LOG_WARN("VK: texture array layer staging alloc failed");
        return;
    }

    VKArrayTransferCtx ctx = {0};
    ctx.image = td->image;
    ctx.staging = staging;
    ctx.width = td->width;
    ctx.height = td->height;
    ctx.base_layer = layer;
    ctx.layer_count = 1;
    ctx.old_layout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
    ctx.mid_layout = VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL;
    ctx.copy = true;
    ctx.aspect = VK_IMAGE_ASPECT_COLOR_BIT;
    if (!vk_texture_sync_submit(vk, staging, staging_mem,
                                vk_array_transfer_record, &ctx)) {
        LOG_WARN("VK: texture array layer upload failed");
    }
}

bool rhi_texture_get_size(RHIDevice *dev, RHITexture tex, u32 *out_w, u32 *out_h) {
    VKTextureData *td = (VKTextureData *)rhi_get_resource_typed(dev, tex, RHI_RES_TEXTURE);
    if (!td) {
        /* R631: cubemap handles report the face extent (GL parity; VK depth
         * cubes are TEXTURE-registered and already worked). */
        VKCubemapData *cd = (VKCubemapData *)rhi_get_resource_typed(dev, tex, RHI_RES_CUBEMAP);
        if (!cd || !out_w || !out_h) return false;
        *out_w = cd->size;
        *out_h = cd->size;
        return true;
    }
    if (!out_w || !out_h) return false;
    *out_w = td->width;
    *out_h = td->height;
    return true;
}

bool rhi_texture_read_pixels(RHIDevice *dev, RHITexture tex, void *dst_rgba8, usize size) {
    VKBackend *vk = vk_backend(dev);
    VKTextureData *td = (VKTextureData *)rhi_get_resource_typed(dev, tex, RHI_RES_TEXTURE);
    if (!vk || !dst_rgba8) return false;
    if (!td) {
        /* R624: COLOR cubemap readback — six faces face-major (+X..-Z),
         * mip 0, native bytes per format (RGBA8 4B/px; RGBA16F 8B/px f16).
         * Defined while the cube is in shader-read state (create and
         * rhi_cubemap_transition_to_read both end there); face contents are
         * undefined until written (create upload or compute). The copy
         * restores SHADER_READ_ONLY, so readback is non-destructive. */
        VKCubemapData *cd = (VKCubemapData *)rhi_get_resource_typed(dev, tex, RHI_RES_CUBEMAP);
        if (!cd) return false;
        u32 bpp = (cd->format == VK_FORMAT_R16G16B16A16_SFLOAT) ? 8u : 4u;
        VkDeviceSize data_size = (VkDeviceSize)cd->size * cd->size * bpp * 6u;
        if (size < (usize)data_size) return false;
        if (vkDeviceWaitIdle(vk->device) != VK_SUCCESS)
            LOG_WARN("VK: vkDeviceWaitIdle failed in cubemap readback");
        VkBuffer staging;
        VkDeviceMemory staging_mem;
        if (!vk_texture_staging_alloc(vk, data_size, NULL, &staging, &staging_mem)) {
            LOG_WARN("VK: cubemap readback staging alloc failed");
            return false;
        }
        VKArrayTransferCtx ctx = {0};
        ctx.image = cd->image;
        ctx.staging = staging;
        ctx.width = cd->size;
        ctx.height = cd->size;
        ctx.base_layer = 0;
        ctx.layer_count = 6;
        ctx.old_layout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
        ctx.mid_layout = VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL;
        ctx.copy = true;
        ctx.aspect = VK_IMAGE_ASPECT_COLOR_BIT;
        if (!vk_texture_sync_submit(vk, VK_NULL_HANDLE, VK_NULL_HANDLE,
                                    vk_array_transfer_record, &ctx)) {
            LOG_WARN("VK: cubemap readback submit failed");
            vkDestroyBuffer(vk->device, staging, NULL);
            vkFreeMemory(vk->device, staging_mem, NULL);
            return false;
        }
        void *mapped;
        if (vkMapMemory(vk->device, staging_mem, 0, data_size, 0, &mapped) != VK_SUCCESS)
            return false;
        memcpy(dst_rgba8, mapped, (size_t)data_size);
        vkUnmapMemory(vk->device, staging_mem);
        vkDestroyBuffer(vk->device, staging, NULL);
        vkFreeMemory(vk->device, staging_mem, NULL);
        return true;
    }
    /* R610: a point-shadow depth cube (fbo_depth wrapper with layers==6)
     * reads back all six faces face-major (+X..-Z layer order); every other
     * array texture keeps the R441 no-readback rule. */
    bool fbo_depth = (td->mip_levels == 0 &&
                      td->format == VK_FORMAT_D32_SFLOAT);
    u32 layer_count = (fbo_depth && td->layers == 6u) ? 6u : 1u;
    if (td->layers > 1u && layer_count == 1u) return false;
    /* R445: bytes-per-pixel must follow the image format — the old hard-coded
     * 4B/px read back only half of an RGBA16F texel stream (and the copy
     * itself overflowed the w*h*4 staging buffer with w*h*8 bytes). */
    u32 bpp = (td->format == VK_FORMAT_R16G16B16A16_SFLOAT) ? 8u : 4u;
    VkDeviceSize data_size = (VkDeviceSize)td->width * td->height * bpp * layer_count;
    if (size < (usize)data_size) return false;

    /* Bake-time sync readback — in-flight frames must not race the barrier. */
    if (vkDeviceWaitIdle(vk->device) != VK_SUCCESS)
        LOG_WARN("VK: vkDeviceWaitIdle failed in texture readback");

    VkBuffer staging;
    VkDeviceMemory staging_mem;
    if (!vk_texture_staging_alloc(vk, data_size, NULL, &staging, &staging_mem)) {
        LOG_WARN("VK: texture readback staging alloc failed");
        return false;
    }

    /* R603: the offscreen-FBO depth wrapper (mip_levels == 0 by design — see
     * vk_offscreen_fbo_create) tracks its layout in cur_layout, owned by
     * rhi_cmd_transition_depth_to_read / the FBO bind paths. Everything else
     * (standalone textures, MRT/offscreen color wrappers — their mip_levels
     * may also be 0 but they are COLOR formats) keeps the mip_layout[0]
     * derivation with the SHADER_READ_ONLY fallback. A virgin depth wrapper
     * (never rendered) keeps UNDEFINED: the copy then yields undefined
     * contents, the honest semantic for reading before any render.
     * R610: the cube variant shares this path — all rendered faces sit in
     * DEPTH_STENCIL_READ_ONLY (tracked via cur_layout by bind_face); faces
     * never rendered keep UNDEFINED contents under a whole-image barrier,
     * so readback is defined once every face has been rendered at least
     * once (the gate's six-face clear). */
    VkImageLayout old_layout = fbo_depth ? td->cur_layout : td->mip_layout[0];
    if (old_layout == VK_IMAGE_LAYOUT_UNDEFINED && !fbo_depth)
        old_layout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;

    VKArrayTransferCtx ctx = {0};
    ctx.image = td->image;
    ctx.staging = staging;
    ctx.width = td->width;
    ctx.height = td->height;
    ctx.base_layer = 0;
    ctx.layer_count = layer_count;
    ctx.old_layout = old_layout;
    ctx.mid_layout = VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL;
    ctx.copy = true;
    /* R602: D32 readback copies the DEPTH aspect (pre-R602 the hardcoded
     * COLOR aspect + missing TRANSFER_SRC usage made depth readback
     * spec-noncompliant; the value only survived by driver leniency). */
    ctx.aspect = (td->format == VK_FORMAT_D32_SFLOAT)
               ? VK_IMAGE_ASPECT_DEPTH_BIT : VK_IMAGE_ASPECT_COLOR_BIT;
    /* NULL staging args: the caller still needs the mapped memory afterwards,
     * so sync_submit must not free it here. */
    if (!vk_texture_sync_submit(vk, VK_NULL_HANDLE, VK_NULL_HANDLE,
                                vk_array_transfer_record, &ctx)) {
        LOG_WARN("VK: texture readback submit failed");
        vkDestroyBuffer(vk->device, staging, NULL);
        vkFreeMemory(vk->device, staging_mem, NULL);
        return false;
    }

    void *mapped;
    if (vkMapMemory(vk->device, staging_mem, 0, data_size, 0, &mapped) != VK_SUCCESS)
        return false;
    memcpy(dst_rgba8, mapped, (size_t)data_size);
    vkUnmapMemory(vk->device, staging_mem);
    vkDestroyBuffer(vk->device, staging, NULL);
    vkFreeMemory(vk->device, staging_mem, NULL);
    return true;
}

void rhi_texture_destroy(RHIDevice *dev, RHITexture tex) {
    if (dev == NULL) return;
    VKBackend *vk = vk_backend(dev);
    VKTextureData *td = (VKTextureData *)rhi_get_resource_typed(dev, tex, RHI_RES_TEXTURE);
    if (!td) return;
    /* The material-texture fallback caches this view
     * (rhi_cmd_bind_shadow_texture) — drop the cache before destroying it. */
    if (vk->shadow_tex_view == td->view) vk->shadow_tex_view = VK_NULL_HANDLE;
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
    if (dev == NULL || desc == NULL) return RHI_HANDLE_NULL;
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
    if (dev == NULL) return;
    VKBackend *vk = vk_backend(dev);
    VKSamplerData *sd = (VKSamplerData *)rhi_get_resource_typed(dev, sampler, RHI_RES_SAMPLER);
    if (!sd) return;
    vkDestroySampler(vk->device, sd->sampler, NULL);
    free(sd);
    rhi_free_slot(dev, sampler);
}

/* ---- Command recording ---- */

void rhi_cmd_begin_render_pass(RHICmdBuffer *cmd) {
    (void)cmd;
    VKBackend *vk = vk_cmd_backend(cmd);
    if (!vk) return;
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
                   vk->swap_extent.width, vk->swap_extent.height, vk->swap_format,
                   VK_SAMPLE_COUNT_1_BIT);

    VkViewport vp = {0, 0, (f32)vk->swap_extent.width, (f32)vk->swap_extent.height, 0.0f, 1.0f};
    vkCmdSetViewport(vk->cmd_buffers[vk->current_frame], 0, 1, &vp);
    VkRect2D sc = {{0, 0}, vk->swap_extent};
    vkCmdSetScissor(vk->cmd_buffers[vk->current_frame], 0, 1, &sc);
    vk->vp_valid = false; vk->sc_valid = false;  /* R95-1: invalidate cache (render pass begin uses non-flipped viewport, different from rhi_cmd_set_viewport's flipped viewport) */
    vk->current_pipeline = VK_NULL_HANDLE;
}

void rhi_cmd_end_render_pass(RHICmdBuffer *cmd) {
    (void)cmd;
    VKBackend *vk = vk_cmd_backend(cmd);
    if (!vk) return;
    if (vk->render_pass_active) {
        vkCmdEndRenderPass(vk->cmd_buffers[vk->current_frame]);
        vk->render_pass_active = false;
    }
    /* A pass suspended for compute is already ended; drop the resume request. */
    vk->pass_suspended = false;
}

void rhi_cmd_bind_pipeline(RHICmdBuffer *cmd, RHIPipeline pipe) {
    (void)cmd;
    VKBackend *vk = vk_cmd_backend(cmd);
    if (!vk) return;
    VKPipelineData *pd = (VKPipelineData *)rhi_get_resource_typed(g_current_device, pipe, RHI_RES_PIPELINE);
    if (!pd) return;
    VkPipelineBindPoint bind_point = pd->is_compute ?
        VK_PIPELINE_BIND_POINT_COMPUTE : VK_PIPELINE_BIND_POINT_GRAPHICS;
    /* Pick (or lazily build) a pipeline compatible with the active render pass's
     * color format, so the same logical pipeline can be drawn into FBOs of
     * different formats without breaking render-pass compatibility. */
    VkPipeline bound = pd->is_compute ? pd->pipeline
        : vk_pipeline_for_fmt(vk, pd, vk->active_color_fmt, vk->active_sample_count);
    /* R89-1: Skip redundant vkCmdBindPipeline when pipeline unchanged. */
    if (bound != vk->current_pipeline) {
        vkCmdBindPipeline(vk->cmd_buffers[vk->current_frame], bind_point, bound);
        vk->current_pipeline = bound;
    }
    vk->current_pipeline_data = pd;
    if (pd->mrt_pipeline && rhi_handle_valid(vk->bound_ubo) &&
        vk->ubo_bound_pipeline_data != pd)
        vk_rebind_uniform_buffers(vk);
    /* Start a fresh storage-buffer descriptor set for this pipeline binding. */
    vk->storage_set_valid = false;
    /* R436: same for the storage-image descriptor set. */
    vk->image_set_valid = false;
}

void rhi_cmd_bind_vertex_buffer(RHICmdBuffer *cmd, RHIBuffer buf, usize offset) {
    (void)cmd;
    VKBackend *vk = vk_cmd_backend(cmd);
    if (!vk) return;
    VKBufferData *bd = (VKBufferData *)rhi_get_resource_typed(g_current_device, buf, RHI_RES_BUFFER);
    if (!bd) return;
    VkDeviceSize off = (VkDeviceSize)offset;
    vkCmdBindVertexBuffers(vk->cmd_buffers[vk->current_frame], 0, 1, &bd->buffer, &off);
}

void rhi_cmd_bind_index_buffer(RHICmdBuffer *cmd, RHIBuffer buf, usize offset, bool is_u32) {
    (void)cmd;
    VKBackend *vk = vk_cmd_backend(cmd);
    if (!vk) return;
    VKBufferData *bd = (VKBufferData *)rhi_get_resource_typed(g_current_device, buf, RHI_RES_BUFFER);
    if (!bd) return;
    /* R224-A: Honor recorded index width (was hard-coded UINT32). */
    VkIndexType itype = is_u32 ? VK_INDEX_TYPE_UINT32 : VK_INDEX_TYPE_UINT16;
    vkCmdBindIndexBuffer(vk->cmd_buffers[vk->current_frame], bd->buffer, (VkDeviceSize)offset, itype);
}

void rhi_cmd_set_viewport(RHICmdBuffer *cmd, f32 x, f32 y, f32 w, f32 h,
                          f32 min_depth, f32 max_depth) {
    (void)cmd;
    VKBackend *vk = vk_cmd_backend(cmd);
    if (!vk) return;
    if (vk->vp_valid && vk->cached_vp_x == x && vk->cached_vp_y == y &&
        vk->cached_vp_w == w && vk->cached_vp_h == h &&
        vk->cached_vp_min_d == min_depth && vk->cached_vp_max_d == max_depth)
        return;  /* R94-2: cache hit */
    /* R225-A: Honor recorded depth range (was hard-coded 0..1). */
    VkViewport vp = {x, y + h, w, -h, min_depth, max_depth};
    vkCmdSetViewport(vk->cmd_buffers[vk->current_frame], 0, 1, &vp);
    vk->cached_vp_x = x; vk->cached_vp_y = y; vk->cached_vp_w = w; vk->cached_vp_h = h;
    vk->cached_vp_min_d = min_depth; vk->cached_vp_max_d = max_depth;
    vk->vp_valid = true;
}

void rhi_cmd_set_scissor(RHICmdBuffer *cmd, i32 x, i32 y, u32 w, u32 h) {
    (void)cmd;
    VKBackend *vk = vk_cmd_backend(cmd);
    if (!vk) return;
    if (vk->sc_valid && vk->cached_sc_x == x && vk->cached_sc_y == y &&
        vk->cached_sc_w == w && vk->cached_sc_h == h) return;  /* R94-2: cache hit */
    VkRect2D sc = {{x, y}, {w, h}};
    vkCmdSetScissor(vk->cmd_buffers[vk->current_frame], 0, 1, &sc);
    vk->cached_sc_x = x; vk->cached_sc_y = y; vk->cached_sc_w = w; vk->cached_sc_h = h;
    vk->sc_valid = true;
}

void rhi_cmd_set_shadow_viewport(RHICmdBuffer *cmd, u32 x, u32 y, u32 w, u32 h) {
    (void)cmd;
    VKBackend *vk = vk_cmd_backend(cmd);
    if (!vk) return;
    /* Non-flipped: shadow depth passes use a top-left-origin viewport (see
     * rhi_cmd_bind_shadow_map), so cascade quadrants must match that. */
    if (!vk->vp_valid || vk->cached_vp_x != (f32)x || vk->cached_vp_y != (f32)y ||
        vk->cached_vp_w != (f32)w || vk->cached_vp_h != (f32)h ||
        vk->cached_vp_min_d != 0.0f || vk->cached_vp_max_d != 1.0f) {  /* R94-2 / R225-A */
        VkViewport vp = {(f32)x, (f32)y, (f32)w, (f32)h, 0.0f, 1.0f};
        vkCmdSetViewport(vk->cmd_buffers[vk->current_frame], 0, 1, &vp);
        vk->cached_vp_x = (f32)x; vk->cached_vp_y = (f32)y; vk->cached_vp_w = (f32)w; vk->cached_vp_h = (f32)h;
        vk->cached_vp_min_d = 0.0f; vk->cached_vp_max_d = 1.0f;
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
    rhi_cmd_draw_base(cmd, vertex_count, instance_count, 0u);
}

void rhi_cmd_draw_base(RHICmdBuffer *cmd, u32 vertex_count, u32 instance_count,
                       u32 first_vertex) {
    (void)cmd;
    VKBackend *vk = vk_cmd_backend(cmd);
    if (!vk) return;
    vk_resume_pass_if_needed(vk);
    vk_flush_push_constants(vk);  /* R94-3: batch push constants */
    vkCmdDraw(vk->cmd_buffers[vk->current_frame], vertex_count, instance_count,
              first_vertex, 0);
}

void rhi_cmd_draw_indexed(RHICmdBuffer *cmd, u32 index_count, u32 instance_count) {
    rhi_cmd_draw_indexed_base(cmd, index_count, instance_count, 0u, 0);
}

void rhi_cmd_draw_indexed_base(RHICmdBuffer *cmd, u32 index_count, u32 instance_count,
                               u32 first_index, i32 vertex_offset) {
    (void)cmd;
    VKBackend *vk = vk_cmd_backend(cmd);
    if (!vk) return;
    vk_resume_pass_if_needed(vk);
    vk_flush_push_constants(vk);  /* R94-3: batch push constants */
    vkCmdDrawIndexed(vk->cmd_buffers[vk->current_frame], index_count, instance_count,
                     first_index, vertex_offset, 0);
}

void rhi_cmd_draw_indirect(RHIDevice *dev, RHIBuffer cmd_buf, u32 offset,
                           u32 draw_count, u32 stride) {
    if (!dev || g_current_device != dev) return;
    VKBackend *vk = vk_backend(dev);
    if (!vk || !vk->frame_started) return;
    VKBufferData *bd = (VKBufferData *)rhi_get_resource_typed(dev, cmd_buf, RHI_RES_BUFFER);
    if (!bd) return;
    vk_resume_pass_if_needed(vk);
    vk_flush_push_constants(vk);
    if (vk->feat_multi_draw_indirect || draw_count <= 1u) {
        vkCmdDrawIndirect(vk->cmd_buffers[vk->current_frame],
                          bd->buffer, (VkDeviceSize)offset,
                          draw_count, stride);
    } else {
        /* R635: multiDrawIndirect absent — drawCount must be 0/1, loop. */
        for (u32 i = 0; i < draw_count; i++) {
            vkCmdDrawIndirect(vk->cmd_buffers[vk->current_frame],
                              bd->buffer, (VkDeviceSize)(offset + (usize)i * stride),
                              1u, stride);
        }
    }
}

void rhi_cmd_draw_indexed_indirect(RHIDevice *dev, RHIBuffer cmd_buf, u32 offset,
                                   u32 draw_count, u32 stride) {
    if (!dev || g_current_device != dev) return;
    VKBackend *vk = vk_backend(dev);
    if (!vk || !vk->frame_started) return;
    VKBufferData *bd = (VKBufferData *)rhi_get_resource_typed(dev, cmd_buf, RHI_RES_BUFFER);
    if (!bd) return;
    vk_resume_pass_if_needed(vk);
    vk_flush_push_constants(vk);  /* R94-3: batch push constants */
    if (vk->feat_multi_draw_indirect || draw_count <= 1u) {
        vkCmdDrawIndexedIndirect(vk->cmd_buffers[vk->current_frame],
                                 bd->buffer, (VkDeviceSize)offset,
                                 draw_count, stride);
    } else {
        /* R635: multiDrawIndirect absent — drawCount must be 0/1, loop. */
        for (u32 i = 0; i < draw_count; i++) {
            vkCmdDrawIndexedIndirect(vk->cmd_buffers[vk->current_frame],
                                     bd->buffer, (VkDeviceSize)(offset + (usize)i * stride),
                                     1u, stride);
        }
    }
}

void rhi_cmd_draw_indexed_indirect_count(RHIDevice *dev, RHIBuffer cmd_buf, u32 cmd_offset,
                                         RHIBuffer count_buf, u32 count_offset,
                                         u32 max_draws, u32 stride) {
    if (!dev || g_current_device != dev) return;
    VKBackend *vk = vk_backend(dev);
    if (!vk || !vk->frame_started) return;
    VKBufferData *cmd_bd   = (VKBufferData *)rhi_get_resource_typed(dev, cmd_buf, RHI_RES_BUFFER);
    VKBufferData *count_bd = (VKBufferData *)rhi_get_resource_typed(dev, count_buf, RHI_RES_BUFFER);
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
        /* Fallback when drawIndirectCount is unavailable: issue max_draws.
         * Callers (indirect_draw R234-B / gpucull R171) zero visible slots
         * before compact so surplus commands are no-ops (indexCount=0). */
        if (vk->feat_multi_draw_indirect || max_draws <= 1u) {
            vkCmdDrawIndexedIndirect(vk->cmd_buffers[vk->current_frame],
                                     cmd_bd->buffer, (VkDeviceSize)cmd_offset,
                                     max_draws, stride);
        } else {
            /* R635: multiDrawIndirect absent — drawCount must be 0/1, loop. */
            for (u32 i = 0; i < max_draws; i++) {
                vkCmdDrawIndexedIndirect(vk->cmd_buffers[vk->current_frame],
                                         cmd_bd->buffer,
                                         (VkDeviceSize)(cmd_offset + (usize)i * stride),
                                         1u, stride);
            }
        }
    }
}

void rhi_cmd_dispatch(RHICmdBuffer *cmd, u32 x, u32 y, u32 z) {
    (void)cmd;
    VKBackend *vk = vk_cmd_backend(cmd);
    if (!vk) return;
    /* Vulkan forbids vkCmdDispatch inside a render pass. Suspend the active
     * pass (its attachments are STOREd); the next draw/clear resumes it. */
    vk_suspend_pass_for_compute(vk);
    vk_flush_push_constants(vk);  /* R94-3: batch push constants */
    vkCmdDispatch(vk->cmd_buffers[vk->current_frame], x, y, z);
}

void rhi_cmd_bind_storage_buffer(RHICmdBuffer *cmd, RHIBuffer buf, u32 binding) {
    (void)cmd;
    VKBackend *vk = vk_cmd_backend(cmd);
    if (!vk) return;
    if (!vk->current_pipeline_data) return;
    VKPipelineData *cpd = vk->current_pipeline_data;
    VKBufferData *bd = (VKBufferData *)rhi_get_resource_typed(g_current_device, buf, RHI_RES_BUFFER);
    if (!bd) return;

    VkDescriptorSetLayout layout_to_use = cpd->is_compute ?
        vk->storage_layout : vk->storage_vtx_layout;

    /* Accumulate all of this pipeline's storage-buffer binds into one set so
     * a shader reading bindings 0..7 sees every buffer (allocated lazily on the
     * first bind after rhi_cmd_bind_pipeline). */
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
    /* C-BUF-3 fix: re-bind the set on EVERY storage bind. R90-1 used to skip
     * the re-bind after the first one and rely on the host having updated
     * the already-bound set — but the spec lets drivers consume descriptor
     * contents at vkCmdBindDescriptorSets host-execution time ("may be
     * consumed during host execution of the command, or during shader
     * execution... or in between"), so a later-binding write can be invisible
     * to the dispatch. Observed on the local NVIDIA driver: the second
     * rhi_cmd_bind_storage_buffer's buffer was never written by the shader
     * (C-BUF-3 phase). Re-binding snapshots the accumulated set contents at
     * a point after every update recorded so far, which is correct on both
     * consumption models. */
    VkPipelineBindPoint bp = cpd->is_compute ?
        VK_PIPELINE_BIND_POINT_COMPUTE : VK_PIPELINE_BIND_POINT_GRAPHICS;
    /* R590: graphics pipelines place the storage set at their OWN index
     * (textures/texel shift it past 0); compute keeps the historical 0
     * (compute layouts wire storage first). */
    u32 first_set = cpd->is_compute ? 0u :
        (cpd->storage_set != (u8)VK_INVALID_SET ? (u32)cpd->storage_set : 0u);
    vkCmdBindDescriptorSets(vk->cmd_buffers[vk->current_frame],
        bp, cpd->layout,
        first_set, 1, &ds, 0, NULL);
}

bool rhi_backend_cmd_buffer_get_native_info(
    const RHIDevice *dev, const RHICmdBuffer *cmd,
    RHICmdBufferNativeInfo *out) {
    const VKBackend *vk;
    if (dev == NULL || cmd == NULL || out == NULL) return false;
    memset(out, 0, sizeof(*out));
    vk = (const VKBackend *)dev->backend_data;
    if (vk == NULL || !vk->frame_started ||
        cmd != (const RHICmdBuffer *)vk ||
        vk->cmd_buffers[vk->current_frame] == VK_NULL_HANDLE)
        return false;
    out->type = RHI_NATIVE_HANDLE_VULKAN;
    out->command_buffer = (void *)(uintptr_t)vk->cmd_buffers[vk->current_frame];
    out->recording = true;
    return true;
}

static RHIFormat rhi_format_from_vk(VkFormat fmt) {
    switch (fmt) {
    case VK_FORMAT_R8G8B8A8_UNORM: return RHI_FORMAT_R8G8B8A8_UNORM;
    case VK_FORMAT_B8G8R8A8_UNORM: return RHI_FORMAT_B8G8R8A8_UNORM;
    case VK_FORMAT_R16G16B16A16_SFLOAT: return RHI_FORMAT_R16G16B16A16_SFLOAT;
    case VK_FORMAT_R16G16_SFLOAT: return RHI_FORMAT_R16G16_SFLOAT;
    case VK_FORMAT_R32_SFLOAT: return RHI_FORMAT_R32_FLOAT;
    case VK_FORMAT_D32_SFLOAT: return RHI_FORMAT_D32_FLOAT;
    default: return RHI_FORMAT_UNDEFINED;
    }
}

bool rhi_backend_get_device_info(const RHIDevice *dev, RHIDeviceInfo *out) {
    const VKBackend *vk;
    if (dev == NULL || out == NULL) return false;
    vk = (const VKBackend *)dev->backend_data;
    if (vk == NULL) return false;
    out->backend = RHI_BACKEND_VULKAN;
    strncpy(out->device_name, vk->device_props.deviceName,
            sizeof(out->device_name) - 1u);
    out->vendor_id = vk->device_props.vendorID;
    out->device_id = vk->device_props.deviceID;
    out->api_version = vk->device_props.apiVersion;
    out->driver_version = vk->device_props.driverVersion;
    out->feature_bits = dev->capabilities.feature_bits;
    return true;
}

bool rhi_backend_texture_get_native_info(
    const RHIDevice *dev, RHITexture texture, RHITextureNativeInfo *out) {
    const VKTextureData *td;
    if (dev == NULL || out == NULL) return false;
    td = (const VKTextureData *)rhi_get_resource_typed(
        (RHIDevice *)dev, texture, RHI_RES_TEXTURE);
    if (td == NULL || td->image == VK_NULL_HANDLE || td->view == VK_NULL_HANDLE)
        return false;
    out->type = RHI_NATIVE_HANDLE_VULKAN;
    out->image = (void *)(uintptr_t)td->image;
    out->memory = (void *)(uintptr_t)td->memory;
    out->view = (void *)(uintptr_t)td->view;
    out->image_layout = (u32)td->cur_layout;
    out->format = rhi_format_from_vk(td->format);
    out->native_format = (u32)td->format;
    out->width = td->width;
    out->height = td->height;
    out->mip_levels = td->mip_levels;
    out->array_layers = td->layers == 0u ? 1u : td->layers;
    return true;
}

void rhi_cmd_bind_acceleration_structure(
    RHICmdBuffer *cmd, RHIAccelerationStructure structure, u32 binding) {
    VKBackend *vk;
    VKPipelineData *cpd;
    VKAccelerationStructureData *as_data;
    VkWriteDescriptorSetAccelerationStructureKHR as_write = {0};
    VkWriteDescriptorSet write = {0};
    VkAccelerationStructureKHR handle;
    VkDescriptorSetLayout layout;
    VkDescriptorSet set;
    VkDescriptorSetAllocateInfo allocate = {0};

    if (cmd == NULL || binding >= 4u) return;
    vk = vk_cmd_backend(cmd);
    if (vk == NULL || vk->current_pipeline_data == NULL) return;
    cpd = vk->current_pipeline_data;
    if (!cpd->is_compute) return;
    as_data = (VKAccelerationStructureData *)rhi_get_resource_typed(
        g_current_device, structure, RHI_RES_ACCELERATION_STRUCTURE);
    if (as_data == NULL) return;

    /* Allocate a small dedicated set so ray-query shaders do not depend on the
     * legacy storage-buffer/image set layout. The compute pipeline must expose
     * an acceleration-structure binding at this set's binding index. */
    layout = vk->ray_query_layout;
    if (layout == VK_NULL_HANDLE) return;
    allocate.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
    allocate.descriptorPool = vk->desc_pools[vk->current_frame];
    allocate.descriptorSetCount = 1u;
    allocate.pSetLayouts = &layout;
    if (vkAllocateDescriptorSets(vk->device, &allocate, &set) != VK_SUCCESS)
        return;
    handle = as_data->handle;
    as_write.sType =
        VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET_ACCELERATION_STRUCTURE_KHR;
    as_write.accelerationStructureCount = 1u;
    as_write.pAccelerationStructures = &handle;
    write.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
    write.dstSet = set;
    write.dstBinding = binding;
    write.descriptorCount = 1u;
    write.descriptorType = VK_DESCRIPTOR_TYPE_ACCELERATION_STRUCTURE_KHR;
    write.pNext = &as_write;
    vkUpdateDescriptorSets(vk->device, 1u, &write, 0u, NULL);
    vkCmdBindDescriptorSets(vk->cmd_buffers[vk->current_frame],
                            VK_PIPELINE_BIND_POINT_COMPUTE, cpd->layout,
                            cpd->ray_query_set, 1u, &set, 0u, NULL);
}

void rhi_cmd_memory_barrier(RHICmdBuffer *cmd) {
    (void)cmd;
    VKBackend *vk = vk_cmd_backend(cmd);
    if (!vk) return;
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
    VKBackend *vk = vk_cmd_backend(cmd);
    if (!vk || unit >= 4u) return;
    VKTextureData *td = (VKTextureData *)rhi_get_resource_typed(g_current_device, tex, RHI_RES_TEXTURE);
    if (!td || td->image == VK_NULL_HANDLE || mip_level >= td->mip_levels ||
        mip_level >= VK_MAX_MIP_VIEWS) return;
    VKPipelineData *cpd = vk->current_pipeline_data;
    if (!cpd || cpd->storage_image_set == (u8)VK_INVALID_SET) return;
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

    /* R436: Accumulate all of this pipeline's storage-image binds into ONE
     * set (mirrors the storage-buffer R90-1 pattern) so a shader using image
     * units 0..3 sees every bound mip. The set is bound once per pipeline;
     * updating an as-yet-unused set before the dispatch consumes it is valid. */
    VkDescriptorSetLayout layout = vk->storage_image_layout;
    bool need_bind = !vk->image_set_valid;
    if (!vk->image_set_valid) {
        VkDescriptorSetAllocateInfo dsai = {0};
        dsai.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
        dsai.descriptorPool = vk->desc_pools[vk->current_frame];
        dsai.descriptorSetCount = 1;
        dsai.pSetLayouts = &layout;
        if (vkAllocateDescriptorSets(vk->device, &dsai, &vk->image_set) != VK_SUCCESS)
            return;
        vk->image_set_valid = true;
    }
    VkDescriptorSet ds = vk->image_set;

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
    if (need_bind) {
        VkPipelineBindPoint bp = cpd->is_compute ?
            VK_PIPELINE_BIND_POINT_COMPUTE : VK_PIPELINE_BIND_POINT_GRAPHICS;
        vkCmdBindDescriptorSets(vk->cmd_buffers[vk->current_frame],
            bp, cpd->layout,
            cpd->storage_image_set, 1, &ds, 0, NULL);
    }
}

void rhi_cmd_bind_image_cubemap_face(RHICmdBuffer *cmd, RHICubemap cm, u32 face, u32 mip, u32 unit, bool write_only) {
    (void)cmd;
    VKBackend *vk = vk_cmd_backend(cmd);
    if (!vk || unit >= 4u) return;
    VKCubemapData *cd = (VKCubemapData *)rhi_get_resource_typed(g_current_device, cm, RHI_RES_CUBEMAP);
    if (!cd || face >= 6u) return;
    if (mip >= cd->mip_levels || mip >= VK_MAX_MIP_VIEWS) return;
    VKPipelineData *cpd = vk->current_pipeline_data;
    if (!cpd || cpd->storage_image_set == (u8)VK_INVALID_SET) return;
    vk_suspend_pass_for_compute(vk);

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
    VKBackend *vk = vk_cmd_backend(cmd);
    if (!vk || unit >= 4u) return;
    VKCubemapData *cd = (VKCubemapData *)rhi_get_resource_typed(g_current_device, cm, RHI_RES_CUBEMAP);
    VKSamplerData *sd = (VKSamplerData *)rhi_get_resource_typed(g_current_device, sampler, RHI_RES_SAMPLER);
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
    VKBackend *vk = vk_cmd_backend(cmd);
    if (!vk || unit >= 4u) return;
    VKTextureData *td = (VKTextureData *)rhi_get_resource_typed(g_current_device, tex, RHI_RES_TEXTURE);
    if (!td || td->image == VK_NULL_HANDLE || mip_level >= td->mip_levels ||
        mip_level >= VK_MAX_MIP_VIEWS) return;
    VKPipelineData *cpd = vk->current_pipeline_data;
    if (!cpd || cpd->sampler_mip_set == (u8)VK_INVALID_SET) return;
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
    VKSamplerData *sd = (VKSamplerData *)rhi_get_resource_typed(g_current_device, sampler, RHI_RES_SAMPLER);
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
    VKBackend *vk = vk_cmd_backend(cmd);
    if (!vk || unit >= 4u) return;
    VKTextureData *td = (VKTextureData *)rhi_get_resource_typed(g_current_device, tex, RHI_RES_TEXTURE);
    if (!td || td->image == VK_NULL_HANDLE) return;
    VKPipelineData *cpd = vk->current_pipeline_data;
    if (!cpd || cpd->sampler_mip_set == (u8)VK_INVALID_SET) return;
    VKSamplerData *sd = (VKSamplerData *)rhi_get_resource_typed(g_current_device, sampler, RHI_RES_SAMPLER);
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
    VKBackend *vk = vk_cmd_backend(cmd);
    if (!vk) return;
    VKTextureData *td = (VKTextureData *)rhi_get_resource_typed(g_current_device, depth_tex, RHI_RES_TEXTURE);
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
    VKBackend *vk = vk_cmd_backend(cmd);
    if (!vk) return;
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

void rhi_cmd_clear_color_attachment(RHICmdBuffer *cmd, u32 attachment,
                                    f32 r, f32 g, f32 b, f32 a) {
    (void)cmd;
    VKBackend *vk = vk_cmd_backend(cmd);
    if (!vk) return;
    if (!vk || attachment >= RHI_MRT_MAX_ATTACHMENTS) return;
    vk_resume_pass_if_needed(vk);
    VkClearAttachment att = {0};
    att.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
    att.colorAttachment = attachment;
    att.clearValue.color.float32[0] = r;
    att.clearValue.color.float32[1] = g;
    att.clearValue.color.float32[2] = b;
    att.clearValue.color.float32[3] = a;
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
    /* R417: graphics uses the clamped size stored at creation — the layout
     * range is min(256, maxPushConstantsSize), so a hard-coded 256 is invalid
     * on 128-byte-limit devices. */
    u32 max_pc = vk->current_pipeline_data->is_compute ? 128
                 : vk->current_pipeline_data->push_range_size;
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

/* R552-B: Bounds rule for the legacy set_uniform_* helpers below. Validates
 * the byte offset against the pipeline's declared push range (compute 128B /
 * graphics clamped push_range_size) instead of the hard 256 staging size —
 * writes into [declared_range, 256) were silently truncated at flush. A
 * negative location (absent uniform) stays silent, matching GL semantics. */
#define VK_PUSH_HELPER_CHECK(vk, location, size) do { \
    VKPipelineData *pd_ = (vk)->current_pipeline_data; \
    if (!pd_) return; \
    u32 range_ = pd_->is_compute ? 128u : pd_->push_range_size; \
    if (!rhi_push_helper_range_ok((location), (size), range_)) { \
        if ((location) >= 0) \
            LOG_WARN("VK: set_uniform offset %d+%u exceeds declared push range %u — write dropped", \
                     (location), (u32)(size), range_); \
        return; \
    } \
} while(0)

/* Push constants map to rhi_cmd_set_uniform_*. Location is used as byte offset. */
void rhi_cmd_set_uniform_mat4(RHICmdBuffer *cmd, i32 location, const f32 *m) {
    (void)cmd;
    if (m == NULL) return;
    VKBackend *vk = vk_cmd_backend(cmd);
    if (!vk) return;
    VK_PUSH_HELPER_CHECK(vk, location, 64u);
    memcpy(vk->push_staging + location, m, 64);  /* R94-3: stage, flush at draw */
    VK_PUSH_MARK(vk, location, 64);
    vk->push_dirty = true;
}

void rhi_cmd_set_uniform_vec3(RHICmdBuffer *cmd, i32 location, f32 x, f32 y, f32 z) {
    (void)cmd;
    VKBackend *vk = vk_cmd_backend(cmd);
    if (!vk) return;
    VK_PUSH_HELPER_CHECK(vk, location, 12u);
    f32 v[3] = {x, y, z};
    memcpy(vk->push_staging + location, v, 12);  /* R94-3: stage, flush at draw */
    VK_PUSH_MARK(vk, location, 12);
    vk->push_dirty = true;
}

void rhi_cmd_set_uniform_vec2(RHICmdBuffer *cmd, i32 location, f32 x, f32 y) {
    (void)cmd;
    VKBackend *vk = vk_cmd_backend(cmd);
    if (!vk) return;
    VK_PUSH_HELPER_CHECK(vk, location, 8u);
    f32 v[2] = {x, y};
    memcpy(vk->push_staging + location, v, 8);  /* R94-3: stage, flush at draw */
    VK_PUSH_MARK(vk, location, 8);
    vk->push_dirty = true;
}

void rhi_cmd_set_uniform_vec4(RHICmdBuffer *cmd, i32 location, f32 x, f32 y, f32 z, f32 w) {
    (void)cmd;
    VKBackend *vk = vk_cmd_backend(cmd);
    if (!vk) return;
    VK_PUSH_HELPER_CHECK(vk, location, 16u);
    f32 v[4] = {x, y, z, w};
    memcpy(vk->push_staging + location, v, 16);  /* R94-3: stage, flush at draw */
    VK_PUSH_MARK(vk, location, 16);
    vk->push_dirty = true;
}

void rhi_cmd_set_uniform_f32(RHICmdBuffer *cmd, i32 location, f32 v) {
    (void)cmd;
    VKBackend *vk = vk_cmd_backend(cmd);
    if (!vk) return;
    VK_PUSH_HELPER_CHECK(vk, location, 4u);
    memcpy(vk->push_staging + location, &v, 4);  /* R94-3: stage, flush at draw */
    VK_PUSH_MARK(vk, location, 4);
    vk->push_dirty = true;
}

/* R444: Push-constant upload with vkCmdPushConstants(offset, size) semantics.
 * Validates against the pipeline's declared push range (was: hard 256, which
 * silently truncated writes into [push_range_size, 256) at flush). */
void rhi_cmd_push_constants(RHICmdBuffer *cmd, u32 offset, const void *data, u32 size) {
    (void)cmd;
    if (!data || size == 0u) return;
    VKBackend *vk = vk_cmd_backend(cmd);
    if (!vk) return;
    VKPipelineData *pd = vk->current_pipeline_data;
    if (!pd) return;
    u32 range = pd->is_compute ? 128u : pd->push_range_size;
    if (!rhi_push_range_fits(offset, size, range)) {
        LOG_WARN("VK: push constants [%u, +%u) exceed declared range %u — write dropped",
                 offset, size, range);
        return;
    }
    memcpy(vk->push_staging + offset, data, size);
    VK_PUSH_MARK(vk, offset, size);
    vk->push_dirty = true;
}

/* R179/R444: Deprecated alias of rhi_cmd_push_constants (location == byte offset). */
void rhi_cmd_set_uniform_bytes(RHICmdBuffer *cmd, i32 location, const void *data, u32 size) {
    if (location < 0) return;
    rhi_cmd_push_constants(cmd, (u32)location, data, size);
}

void rhi_cmd_set_uniform_i32(RHICmdBuffer *cmd, i32 location, i32 v) {
    (void)cmd;
    VKBackend *vk = vk_cmd_backend(cmd);
    if (!vk) return;
    VK_PUSH_HELPER_CHECK(vk, location, 4u);
    memcpy(vk->push_staging + location, &v, 4);  /* R94-3: stage, flush at draw */
    VK_PUSH_MARK(vk, location, 4);
    vk->push_dirty = true;
}

/* ---- Plan E Task 5: RHIPipelineBindings (reflection-driven) ---- */

typedef struct {
    char name[SHADER_IO_NAME_MAX];
    i32  slot; /* std430 push byte offset == legacy API's location */
} VKBindingEntry;

struct RHIPipelineBindings {
    VKBindingEntry entries[VK_PUSH_MERGE_MAX];
    u32  count;
    bool reflect_failed;
};

/* Plan E Task 5 Stage C-2: alias rows for query names the shaders do not
 * declare as push members. The legacy chain answered these from its
 * classification tables; reflection only carries true member names, so the
 * alias resolves to the aliased member's reflected slot plus a swizzle
 * delta. A row fires only when the pipeline declares the member AND no
 * member row already carries the alias name (real members win — e.g.
 * u_shadow_bias is a member of pbr_clustered_vk.frag but the
 * u_clip_params.y alias on deferred_light_vk.frag). Provenance:
 *   - u_prev_vp (Stage C-1): legacy generic tail mapped it onto the gbuffer
 *     family's u_prev_mvp slot (192); camera_velocity_vk.frag declares it
 *     as a real member (128) so the member row wins there.
 *   - deferred rows (Stage C-2 batch 4): deferred_light_vk.frag packs
 *     screen params into u_screen_params.xy and clip params into
 *     u_clip_params.xyz; the legacy no_vertex_input+texel branch served
 *     144/148/160/164/168, exactly member slot + delta. */
typedef struct {
    const char *alias;
    const char *member;
    u32         delta; /* byte offset of the aliased channel inside the member */
} VKPushAliasRow;

static const VKPushAliasRow vk_push_alias_rows[] = {
    { "u_prev_vp",     "u_prev_mvp",      0u },
    { "u_screen_w",    "u_screen_params", 0u },
    { "u_screen_h",    "u_screen_params", 4u },
    { "u_near",        "u_clip_params",   0u },
    { "u_far",         "u_clip_params",   4u },
    { "u_shadow_bias", "u_clip_params",   8u },
    /* Stage C-2 batch 5 (particles): block-instance names "push.<member>"
     * against particle_update.comp's dt and particle.vert's view/proj push
     * blocks — the legacy is_compute/uses_storage branches served
     * push.dt@0, push.view@0, push.proj@64. GL declares plain loose
     * uniforms (u_view/u_proj/u_dt), so the alias names resolve -1 there
     * exactly like the legacy glGetUniformLocation did. */
    { "push.dt",   "dt",   0u },
    { "push.view", "view", 0u },
    { "push.proj", "proj", 64u },
    /* Stage C-2 batch 6 (terrain): terrain_vk packs light dir+bias into
     * u_light_dir_bias, color+water_y into u_light_color_watery, ambient+
     * time into u_ambient_time. The vert carries a real u_camera_pos member
     * so the member row wins there; the frag's member is u_cam_pos (alias
     * row below). Legacy terrain_layout branch served
     * 192/204/208/220/224/236(/240 via the vert member). */
    { "u_light_dir",   "u_light_dir_bias",      0u },
    { "u_shadow_bias", "u_light_dir_bias",     12u },
    { "u_light_color", "u_light_color_watery",  0u },
    { "u_water_y",     "u_light_color_watery", 12u },
    { "u_ambient",     "u_ambient_time",        0u },
    { "u_time",        "u_ambient_time",       12u },
    { "u_camera_pos",  "u_cam_pos",             0u },
    /* Stage C-2 batch 6 (water): water_vk packs camera pos+time into
     * u_camera_time and color+bias into u_color_bias; water_y rides the
     * u_watery vec4. Legacy water_layout branch served 192/204/208/220/224. */
    { "u_camera_pos",  "u_camera_time",   0u },
    { "u_time",        "u_camera_time",  12u },
    { "u_water_color", "u_color_bias",    0u },
    { "u_shadow_bias", "u_color_bias",   12u },
    { "u_water_y",     "u_watery",        0u },
    /* Stage C-2 batch 6 (table-deletion survival): gpucull.c and
     * occlusion_cull.c keep querying the legacy is_compute names until
     * batches 7-8 migrate them. The compute shaders' members carry those
     * offsets exactly (cross-checked by test_shader_io's
     * vk_compute_push_tables_match_reflection gate: cull.comp vp@0/
     * obj_count@64, unified_cull.comp +68/+72/+76/+80, occlusion_cull.comp
     * view_proj@0/object_count@64/hi_z@68/72, hi_z_generate output_size@0). */
    { "u_cull_vp",          "vp",           0u },
    { "u_cull_count",       "obj_count",    0u },
    { "u_cull_hi_z_width",  "hi_z_width",   0u },
    { "u_cull_hi_z_height", "hi_z_height",  0u },
    { "u_cull_use_hi_z",    "use_hi_z",     0u },
    { "u_cull_write_draws", "write_draws",  0u },
    { "pc_view_proj",       "view_proj",    0u },
    { "pc_object_count",    "object_count", 0u },
    { "pc_hi_z_width",      "hi_z_width",   0u },
    { "pc_hi_z_height",     "hi_z_height",  0u },
    { "pc_output_size",     "output_size",  0u },
};

static u32 vk_push_alias_row_count(void) {
    return (u32)(sizeof(vk_push_alias_rows) / sizeof(vk_push_alias_rows[0]));
}

static i32 vk_push_alias_offset(const VKPipelineData *pd, const char *name) {
    if (!pd) return -1;
    for (u32 r = 0u; r < vk_push_alias_row_count(); ++r) {
        const VKPushAliasRow *row = &vk_push_alias_rows[r];
        if (strcmp(name, row->alias) != 0) continue;
        i32 slot = -1;
        bool alias_is_member = false;
        for (u32 i = 0u; i < pd->push_member_count; ++i) {
            if (strcmp(pd->push_members[i].name, row->member) == 0)
                slot = (i32)pd->push_members[i].offset;
            else if (strcmp(pd->push_members[i].name, name) == 0)
                alias_is_member = true;
        }
        if (slot >= 0 && !alias_is_member) return slot + (i32)row->delta;
    }
    return -1;
}

RHIPipelineBindings *rhi_pipeline_bindings_create(RHIDevice *dev, RHIPipeline pipe) {
    if (dev == NULL || !rhi_handle_valid(pipe)) return NULL;
    VKPipelineData *pd = (VKPipelineData *)rhi_get_resource_typed(dev, pipe, RHI_RES_PIPELINE);
    if (!pd) return NULL;
    RHIPipelineBindings *b = calloc(1, sizeof(*b));
    if (!b) return NULL;
    for (u32 i = 0u; i < pd->push_member_count && b->count < VK_PUSH_MERGE_MAX; ++i) {
        VKBindingEntry *e = &b->entries[b->count++];
        memcpy(e->name, pd->push_members[i].name, sizeof(e->name));
        e->name[sizeof(e->name) - 1u] = '\0';
        e->slot = (i32)pd->push_members[i].offset;
    }
    /* Alias rows only when no member row exists (see vk_push_alias_rows).
     * Keeps resolve byte-identical to the legacy chain for every caller
     * that still queries the legacy alias name, proven by the parity phase
     * + golden signature. */
    for (u32 r = 0u; r < vk_push_alias_row_count(); ++r) {
        const VKPushAliasRow *row = &vk_push_alias_rows[r];
        bool present = false;
        for (u32 i = 0u; i < b->count; ++i)
            if (strcmp(b->entries[i].name, row->alias) == 0) { present = true; break; }
        if (present || b->count >= VK_PUSH_MERGE_MAX) continue;
        i32 slot = vk_push_alias_offset(pd, row->alias);
        if (slot < 0) continue;
        VKBindingEntry *e = &b->entries[b->count++];
        memcpy(e->name, row->alias, strlen(row->alias) + 1u);
        e->name[sizeof(e->name) - 1u] = '\0';
        e->slot = slot;
    }
    b->reflect_failed = pd->push_reflect_failed;
    if (b->reflect_failed)
        LOG_WARN("VK: RHIPipelineBindings reflection failed closed — resolve "
                 "returns -1 for every name (no fabricated offsets)");
    return b;
}

void rhi_pipeline_bindings_destroy(RHIDevice *dev, RHIPipelineBindings *b) {
    (void)dev;
    free(b);
}

i32 rhi_pipeline_bindings_resolve(const RHIPipelineBindings *b, const char *name) {
    if (!b || !name) return -1;
    for (u32 i = 0u; i < b->count; ++i)
        if (strcmp(b->entries[i].name, name) == 0) return b->entries[i].slot;
    return -1;
}

i32 rhi_pipeline_get_uniform_location(RHIDevice *dev, RHIPipeline pipe, const char *name) {
    if (dev == NULL || name == NULL) return -1;
    VKPipelineData *pd = (VKPipelineData *)rhi_get_resource_typed(dev, pipe, RHI_RES_PIPELINE);

    /* Plan E Task 5: the merged push-member reflection (cached at shader
     * create) is the offset authority. Stage C-2 batch 6 deleted the
     * hand-written push-offset classification tables that used to follow
     * this loop: test_shader_io's vk_push_tables_match_reflection +
     * vk_compute_push_tables_match_reflection gates cross-checked
     * reflection against those tables (graphics + compute) before the
     * deletion, and their embedded expected-value tables stay as the
     * pinned historical record reflection must keep matching. Names the
     * shaders do not declare as members resolve through the shared alias
     * rows (block-instance aliases like "push.dt", packed vec4 swizzle
     * aliases -- see vk_push_alias_rows), which also keep the still-legacy
     * batch 7-9 callers (gpucull / occlusion_cull compute names) on their
     * exact legacy offsets; everything else returns -1. Render-pass/layout
     * classification itself is untouched -- it lives in
     * rhi_pipeline_create (the *_layout flags and push-range build), not
     * here. */
    if (pd) {
        for (u32 i = 0u; i < pd->push_member_count; ++i) {
            if (strcmp(name, pd->push_members[i].name) == 0)
                return (i32)pd->push_members[i].offset;
        }
    }
    return vk_push_alias_offset(pd, name);
}

void rhi_cmd_bind_material_textures(RHICmdBuffer *cmd,
    RHITexture albedo, RHITexture mr, RHITexture normal, RHITexture emissive,
    RHITexture shadow, RHITexture ssao, RHISampler sampler) {
    (void)cmd;
    VKBackend *vk = vk_cmd_backend(cmd);
    if (!vk) return;
    if (!vk->current_pipeline_data) return;

    VKTextureData *td_alb = (VKTextureData *)rhi_get_resource_typed(g_current_device, albedo, RHI_RES_TEXTURE);
    VKTextureData *td_mr  = (VKTextureData *)rhi_get_resource_typed(g_current_device, mr, RHI_RES_TEXTURE);
    VKTextureData *td_nrm = (VKTextureData *)rhi_get_resource_typed(g_current_device, normal, RHI_RES_TEXTURE);
    VKTextureData *td_em  = (VKTextureData *)rhi_get_resource_typed(g_current_device, emissive, RHI_RES_TEXTURE);
    VKTextureData *td_ssao = (VKTextureData *)rhi_get_resource_typed(g_current_device, ssao, RHI_RES_TEXTURE);
    VKTextureData *td_shadow = (VKTextureData *)rhi_get_resource_typed(g_current_device, shadow, RHI_RES_TEXTURE);
    VKSamplerData *sd     = (VKSamplerData *)rhi_get_resource_typed(g_current_device, sampler, RHI_RES_SAMPLER);
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
    RHITexture occlusion, RHITexture shadow, RHITexture ssao, RHISampler sampler,
    RHITexture brdf_lut, RHICubemap irradiance_map, RHICubemap prefilter_map,
    const RHITexture *point_shadow_cubes, u32 point_shadow_count) {
    (void)cmd;
    VKBackend *vk = vk_cmd_backend(cmd);
    if (!vk) return;
    if (!vk->current_pipeline_data) return;

    VKTextureData *td_alb = (VKTextureData *)rhi_get_resource_typed(g_current_device, albedo, RHI_RES_TEXTURE);
    VKTextureData *td_mr  = (VKTextureData *)rhi_get_resource_typed(g_current_device, mr, RHI_RES_TEXTURE);
    VKTextureData *td_nrm = (VKTextureData *)rhi_get_resource_typed(g_current_device, normal, RHI_RES_TEXTURE);
    VKTextureData *td_em  = (VKTextureData *)rhi_get_resource_typed(g_current_device, emissive, RHI_RES_TEXTURE);
    VKTextureData *td_occ = (VKTextureData *)rhi_get_resource_typed(g_current_device, occlusion, RHI_RES_TEXTURE); /* R583 */
    VKTextureData *td_ssao = (VKTextureData *)rhi_get_resource_typed(g_current_device, ssao, RHI_RES_TEXTURE);
    VKTextureData *td_shadow = (VKTextureData *)rhi_get_resource_typed(g_current_device, shadow, RHI_RES_TEXTURE);
    VKTextureData *td_brdf = (VKTextureData *)rhi_get_resource_typed(g_current_device, brdf_lut, RHI_RES_TEXTURE);
    VKCubemapData *cd_irr  = (VKCubemapData *)rhi_get_resource_typed(
        g_current_device, irradiance_map, RHI_RES_CUBEMAP);
    VKCubemapData *cd_pref = (VKCubemapData *)rhi_get_resource_typed(
        g_current_device, prefilter_map, RHI_RES_CUBEMAP);
    VKSamplerData *sd     = (VKSamplerData *)rhi_get_resource_typed(g_current_device, sampler, RHI_RES_SAMPLER);
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
            VKTextureData *td = (VKTextureData *)rhi_get_resource_typed(g_current_device, point_shadow_cubes[i], RHI_RES_TEXTURE);
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
            VKTextureData *td = (VKTextureData *)rhi_get_resource_typed(g_current_device, point_shadow_cubes[i], RHI_RES_TEXTURE);
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
    /* R583: occlusion at binding 9 — the shared layout's only unwritten slot
     * (the deferred LIGHTING pass uses binding 9 for its emissive target,
     * but that pass binds its own descriptor set). */
    img_infos[9].sampler = sd->sampler;
    img_infos[9].imageView = td_occ ? td_occ->view : alb_view;
    img_infos[9].imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;

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

    /* Bindings 6-9: brdf_lut, irradiance, prefilter, occlusion (R583) */
    writes[2].sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
    writes[2].dstSet = ds;
    writes[2].dstBinding = 6;
    writes[2].descriptorCount = 4;
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

/* R582: one-shot set-0 binder for the deferred lighting pass (see rhi.h for
 * the binding map). Mirrors the ibl helper's batching/fallback conventions:
 * invalid handles fall back to the albedo view so descriptors stay valid. */
void rhi_cmd_bind_deferred_gbuf_textures(RHICmdBuffer *cmd,
    RHITexture albedo_metallic, RHITexture roughness_ao, RHITexture normal,
    RHITexture depth, RHITexture emissive, RHITexture shadow, RHITexture ssao,
    RHISampler sampler, RHITexture brdf_lut, RHICubemap irradiance_map,
    RHICubemap prefilter_map, const RHITexture *point_shadow_cubes,
    u32 point_shadow_count, RHISampler cube_sampler) {
    (void)cmd;
    (void)cube_sampler; /* GL-only: linear filter for point-shadow cubes;
                         * VK binds everything with `sampler` (legacy behavior). */
    VKBackend *vk = vk_cmd_backend(cmd);
    if (!vk || !vk->current_pipeline_data) return;

    VKTextureData *td_am  = (VKTextureData *)rhi_get_resource_typed(g_current_device, albedo_metallic, RHI_RES_TEXTURE);
    VKTextureData *td_rao = (VKTextureData *)rhi_get_resource_typed(g_current_device, roughness_ao, RHI_RES_TEXTURE);
    VKTextureData *td_nrm = (VKTextureData *)rhi_get_resource_typed(g_current_device, normal, RHI_RES_TEXTURE);
    VKTextureData *td_dep = (VKTextureData *)rhi_get_resource_typed(g_current_device, depth, RHI_RES_TEXTURE);
    VKTextureData *td_em  = (VKTextureData *)rhi_get_resource_typed(g_current_device, emissive, RHI_RES_TEXTURE);
    VKTextureData *td_sh  = (VKTextureData *)rhi_get_resource_typed(g_current_device, shadow, RHI_RES_TEXTURE);
    VKTextureData *td_ss  = (VKTextureData *)rhi_get_resource_typed(g_current_device, ssao, RHI_RES_TEXTURE);
    VKTextureData *td_br  = (VKTextureData *)rhi_get_resource_typed(g_current_device, brdf_lut, RHI_RES_TEXTURE);
    VKCubemapData *cd_irr  = (VKCubemapData *)rhi_get_resource_typed(g_current_device, irradiance_map, RHI_RES_CUBEMAP);
    VKCubemapData *cd_pref = (VKCubemapData *)rhi_get_resource_typed(g_current_device, prefilter_map, RHI_RES_CUBEMAP);
    VKSamplerData *sd = (VKSamplerData *)rhi_get_resource_typed(g_current_device, sampler, RHI_RES_SAMPLER);
    if (!sd) return;

    VkDescriptorSetAllocateInfo dsai = {0};
    dsai.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
    dsai.descriptorPool = vk->desc_pools[vk->current_frame];
    dsai.descriptorSetCount = 1;
    dsai.pSetLayouts = &vk->desc_layout;
    VkDescriptorSet ds;
    if (vkAllocateDescriptorSets(vk->device, &dsai, &ds) != VK_SUCCESS) return;

    VkImageView alb_view = td_am ? td_am->view : VK_NULL_HANDLE;
    VkDescriptorImageInfo img[11];
    memset(img, 0, sizeof(img));
    const VkImageView views[11] = {
        td_am  ? td_am->view  : alb_view, /* 0 albedo_metallic */
        td_sh  ? td_sh->view  : alb_view, /* 1 shadow          */
        td_rao ? td_rao->view : alb_view, /* 2 roughness_ao    */
        td_nrm ? td_nrm->view : alb_view, /* 3 normal          */
        td_dep ? td_dep->view : alb_view, /* 4 depth           */
        td_ss  ? td_ss->view  : alb_view, /* 5 ssao            */
        td_br  ? td_br->view  : alb_view, /* 6 brdf_lut        */
        cd_irr  ? cd_irr->view  : alb_view, /* 7 irradiance    */
        cd_pref ? cd_pref->view : alb_view, /* 8 prefilter     */
        td_em  ? td_em->view  : alb_view, /* 9 emissive (R582) */
        alb_view,                         /* 10 (cubes below)  */
    };
    for (u32 i = 0; i < 11u; i++) {
        img[i].sampler = sd->sampler;
        img[i].imageView = views[i];
        img[i].imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
    }

    /* Point-shadow cubes at binding 10 (count 4 under PARTIALLY_BOUND). */
    u32 pt_n = point_shadow_cubes ? point_shadow_count : 0u;
    if (pt_n > 4u) pt_n = 4u;
    u32 pt_write_n = vk->feat_partially_bound ? 4u : 1u;
    VkDescriptorImageInfo cube_infos[4];
    memset(cube_infos, 0, sizeof(cube_infos));
    for (u32 i = 0; i < 4u; i++) {
        VkImageView v = alb_view;
        if (i < pt_n) {
            VKTextureData *td = (VKTextureData *)rhi_get_resource_typed(g_current_device, point_shadow_cubes[i], RHI_RES_TEXTURE);
            if (td && td->view != VK_NULL_HANDLE) v = td->view;
        }
        cube_infos[i].sampler = sd->sampler;
        cube_infos[i].imageView = v;
        cube_infos[i].imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
    }

    /* Write splitting mirrors the ibl helper: a single VkWriteDescriptorSet
     * may not span bindings whose VkDescriptorBindingFlags differ — binding 5
     * carries PARTIALLY_BOUND (when the feature is on) while 0-4 do not. */
    VkWriteDescriptorSet writes[4];
    memset(writes, 0, sizeof(writes));
    /* Bindings 0-4: albedo_metallic, shadow, roughness_ao, normal, depth */
    writes[0].sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
    writes[0].dstSet = ds;
    writes[0].dstBinding = 0;
    writes[0].descriptorCount = 5;
    writes[0].descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
    writes[0].pImageInfo = &img[0];
    /* Binding 5: ssao */
    writes[1].sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
    writes[1].dstSet = ds;
    writes[1].dstBinding = 5;
    writes[1].descriptorCount = 1;
    writes[1].descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
    writes[1].pImageInfo = &img[5];
    /* Bindings 6-9: brdf_lut, irradiance, prefilter, emissive */
    writes[2].sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
    writes[2].dstSet = ds;
    writes[2].dstBinding = 6;
    writes[2].descriptorCount = 4;
    writes[2].descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
    writes[2].pImageInfo = &img[6];
    /* Binding 10: point_shadow_cubes */
    writes[3].sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
    writes[3].dstSet = ds;
    writes[3].dstBinding = 10;
    writes[3].descriptorCount = pt_write_n;
    writes[3].descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
    writes[3].pImageInfo = cube_infos;

    vkUpdateDescriptorSets(vk->device, 4, writes, 0, NULL);
    vkCmdBindDescriptorSets(vk->cmd_buffers[vk->current_frame],
        VK_PIPELINE_BIND_POINT_GRAPHICS, vk->current_pipeline_data->layout,
        0, 1, &ds, 0, NULL);
}

void rhi_cmd_bind_textures_multi(RHICmdBuffer *cmd,
    RHITexture *textures, int count, RHISampler sampler) {
    (void)cmd;
    VKBackend *vk = vk_cmd_backend(cmd);
    if (!vk) return;
    if (!vk->current_pipeline_data || !textures || count <= 0 || count > 6) return;

    VKSamplerData *sd = (VKSamplerData *)rhi_get_resource_typed(g_current_device, sampler, RHI_RES_SAMPLER);
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
        VKTextureData *td = (VKTextureData *)rhi_get_resource_typed(g_current_device, textures[i], RHI_RES_TEXTURE);
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
    (void)cmd;
    VKBackend *vk = vk_cmd_backend(cmd);
    if (!vk || unit >= RHI_MAX_TEXTURE_UNITS || !vk->current_pipeline_data) return;
    VKTextureData *td = (VKTextureData *)rhi_get_resource_typed(
        g_current_device, tex, RHI_RES_TEXTURE);
    VKSamplerData *sd = (VKSamplerData *)rhi_get_resource_typed(
        g_current_device, sampler, RHI_RES_SAMPLER);
    if (!td || td->view == VK_NULL_HANDLE || !sd) return;

    VkDescriptorSetAllocateInfo dsai = {0};
    dsai.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
    dsai.descriptorPool = vk->desc_pools[vk->current_frame];
    dsai.descriptorSetCount = 1;
    dsai.pSetLayouts = &vk->desc_layout;
    VkDescriptorSet ds;
    if (vkAllocateDescriptorSets(vk->device, &dsai, &ds) != VK_SUCCESS) return;

    VkDescriptorImageInfo image_info = {0};
    image_info.sampler = sd->sampler;
    image_info.imageView = td->view;
    image_info.imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
    VkWriteDescriptorSet write = {0};
    write.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
    write.dstSet = ds;
    write.dstBinding = unit;
    write.descriptorCount = 1;
    write.descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
    write.pImageInfo = &image_info;
    vkUpdateDescriptorSets(vk->device, 1, &write, 0, NULL);
    vkCmdBindDescriptorSets(vk->cmd_buffers[vk->current_frame],
        VK_PIPELINE_BIND_POINT_GRAPHICS, vk->current_pipeline_data->layout,
        0, 1, &ds, 0, NULL);
}

void rhi_cmd_bind_shadow_texture(RHICmdBuffer *cmd, RHITexture shadow_tex, RHISampler sampler) {
    (void)cmd; (void)sampler;
    VKBackend *vk = vk_cmd_backend(cmd);
    if (!vk) return;
    VKTextureData *td = (VKTextureData *)rhi_get_resource_typed(g_current_device, shadow_tex, RHI_RES_TEXTURE);
    vk->shadow_tex_view = td ? td->view : VK_NULL_HANDLE;
}

void rhi_cmd_bind_uniform_buffer(RHICmdBuffer *cmd, RHIBuffer buf, u32 binding) {
    (void)cmd;
    VKBackend *vk = vk_cmd_backend(cmd);
    if (!vk) return;
    VKPipelineData *cpd = vk->current_pipeline_data;
    if (!cpd || cpd->ubo_set == (u8)VK_INVALID_SET) return;

    VKBufferData *bd = (VKBufferData *)rhi_get_resource_typed(g_current_device, buf, RHI_RES_BUFFER);
    if (!bd || bd->buffer == VK_NULL_HANDLE) return;
    vk->bound_ubo = buf;
    vk->bound_ubo_binding = binding;

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
    vk->ubo_bound_pipeline_data = cpd;
}

static void vk_rebind_uniform_buffers(VKBackend *vk) {
    if (!vk || !rhi_handle_valid(vk->bound_ubo)) return;
    rhi_cmd_bind_uniform_buffer((RHICmdBuffer *)vk, vk->bound_ubo, vk->bound_ubo_binding);
}

/* ---- Shadow map ---- */

RHIShadowMap rhi_shadow_map_create(RHIDevice *dev, u32 width, u32 height) {
    if (dev == NULL || !rhi_drawable_dimensions_valid(width, height)) {
        return (RHIShadowMap){0};
    }
    VKBackend *vk = vk_backend(dev);
    RHIShadowMap sm = {0};
    sm.width = width;
    sm.height = height;

    VKShadowData *sd = calloc(1, sizeof(VKShadowData));
    if (!sd) return sm;
    sd->magic = VK_SHADOW_DATA_MAGIC;

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
    /* R609: TRANSFER_SRC lets rhi_texture_read_pixels copy the shadow depth
     * out (same permission-only class as R602/R603/R608). */
    ci.usage = VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT | VK_IMAGE_USAGE_SAMPLED_BIT |
               VK_IMAGE_USAGE_TRANSFER_SRC_BIT;
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
    if (vk_allocate_memory(vk, &ai, &sd->depth_memory) != VK_SUCCESS) {
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
    vk_external_dep_depth_only(&dep);

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
    if (!td) {
        /* R358: GPU objects already live in sd — tear down before returning null. */
        LOG_WARN("VK: shadow texture slot alloc failed");
        if (sd->render_pass_load) vkDestroyRenderPass(vk->device, sd->render_pass_load, NULL);
        if (vk->shadow_render_pass == sd->render_pass)
            vk->shadow_render_pass = VK_NULL_HANDLE;
        vkDestroyFramebuffer(vk->device, sd->framebuffer, NULL);
        vkDestroyRenderPass(vk->device, sd->render_pass, NULL);
        vkDestroyImageView(vk->device, sd->depth_view, NULL);
        vkFreeMemory(vk->device, sd->depth_memory, NULL);
        vkDestroyImage(vk->device, sd->depth_image, NULL);
        free(sd);
        return sm;
    }
    u32 tidx = rhi_alloc_slot(dev);
    td->image = sd->depth_image;
    td->view = sd->depth_view;
    td->memory = sd->depth_memory;
    td->width = width;
    td->height = height;
    /* R609: format keys the R602 aspect split and the R603 fbo_depth
     * readback discriminator (mip_levels stays 0 — layout is tracked via
     * cur_layout, set by rhi_cmd_bind_shadow_map). */
    td->format = VK_FORMAT_D32_SFLOAT;
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
    VKShadowData *sd = rhi_get_resource_typed(dev, sm->fbo, RHI_RES_FRAMEBUFFER);
    if (!sd) return;
    if (vkDeviceWaitIdle(vk->device) != VK_SUCCESS)
        LOG_WARN("VK: vkDeviceWaitIdle failed in shadow_map_destroy");
    /* Drop the cached fallback shadow view before it dangles (it aliases
     * sd->depth_view, destroyed just below). */
    if (vk->shadow_tex_view == sd->depth_view) vk->shadow_tex_view = VK_NULL_HANDLE;
    vkDestroyFramebuffer(vk->device, sd->framebuffer, NULL);
    /* R430: clear the cached default shadow pass like the create-failure
     * path does — it aliases sd->render_pass destroyed just below. */
    if (vk->shadow_render_pass == sd->render_pass)
        vk->shadow_render_pass = VK_NULL_HANDLE;
    vkDestroyRenderPass(vk->device, sd->render_pass, NULL);
    if (sd->render_pass_load) vkDestroyRenderPass(vk->device, sd->render_pass_load, NULL);
    vkDestroyImageView(vk->device, sd->depth_view, NULL);
    vkDestroyImage(vk->device, sd->depth_image, NULL);
    vkFreeMemory(vk->device, sd->depth_memory, NULL);
    free(sd);
    /* R425: free the VKTextureData behind the depth_tex slot (calloc'd at
     * create) — the old code freed only the slot, leaking the struct. */
    if (rhi_handle_valid(sm->depth_tex)) {
        VKTextureData *td = (VKTextureData *)rhi_get_resource_typed(
            dev, sm->depth_tex, RHI_RES_TEXTURE);
        if (td) free(td);
        if (dev->slots[sm->depth_tex.index].ptr == td)
            dev->slots[sm->depth_tex.index].ptr = NULL;
    }
    rhi_free_slot(dev, sm->fbo);
    rhi_free_slot(dev, sm->depth_tex);
    sm->fbo = RHI_HANDLE_NULL;
    sm->depth_tex = RHI_HANDLE_NULL;
}

void rhi_cmd_bind_shadow_map(RHICmdBuffer *cmd, RHIShadowMap *sm) {
    (void)cmd;
    if (!sm) return;
    VKBackend *vk = vk_cmd_backend(cmd);
    if (!vk) return;
    VKShadowData *sd = rhi_get_resource_typed(g_current_device, sm->fbo, RHI_RES_FRAMEBUFFER);
    if (!sd) return;

    /* R609: the shadow pass ends with depth in SHADER_READ_ONLY_OPTIMAL (the
     * finalLayout set at create). Track it on the wrapper so readback's R603
     * fbo_depth path gets a correct oldLayout (same fix class as R258's MRT
     * bind tracking). */
    VKTextureData *sdt = (VKTextureData *)rhi_get_resource_typed(
        g_current_device, sm->depth_tex, RHI_RES_TEXTURE);
    if (sdt) sdt->cur_layout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;

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
    vk_record_pass(vk, sd->render_pass_load, sd->framebuffer, sm->width, sm->height,
                   VK_FORMAT_UNDEFINED, VK_SAMPLE_COUNT_1_BIT);

    VkViewport vp = {0, 0, (f32)sm->width, (f32)sm->height, 0, 1};
    vkCmdSetViewport(vk->cmd_buffers[vk->current_frame], 0, 1, &vp);
    VkRect2D sc = {{0, 0}, {sm->width, sm->height}};
    vkCmdSetScissor(vk->cmd_buffers[vk->current_frame], 0, 1, &sc);
    vk->vp_valid = false; vk->sc_valid = false;  /* R95-2: invalidate cache */
}

void rhi_cmd_unbind_shadow_map(RHICmdBuffer *cmd, u32 screen_w, u32 screen_h) {
    (void)cmd;
    VKBackend *vk = vk_cmd_backend(cmd);
    if (!vk) return;

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
                   screen_w, screen_h, vk->swap_format, VK_SAMPLE_COUNT_1_BIT);

    VkViewport vp = {0, 0, (f32)screen_w, (f32)screen_h, 0, 1};
    vkCmdSetViewport(vk->cmd_buffers[vk->current_frame], 0, 1, &vp);
    VkRect2D sc = {{0, 0}, {screen_w, screen_h}};
    vkCmdSetScissor(vk->cmd_buffers[vk->current_frame], 0, 1, &sc);
    vk->vp_valid = false; vk->sc_valid = false;  /* R95-2: invalidate cache */
    vk->current_pipeline = VK_NULL_HANDLE;
}

void rhi_cmd_clear_depth(RHICmdBuffer *cmd) {
    (void)cmd;
    VKBackend *vk = vk_cmd_backend(cmd);
    if (!vk) return;
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
    if (dev == NULL || !rhi_cubemap_desc_validate(desc)) return RHI_HANDLE_NULL;
    VKBackend *vk = vk_backend(dev);

    VKCubemapData *cd = calloc(1, sizeof(VKCubemapData));
    if (!cd) return RHI_HANDLE_NULL;

    VkFormat fmt = vk_format_from_rhi(desc->format);
    u32 mips = desc->mip_levels ? desc->mip_levels : 1u;
    if (mips > VK_MAX_MIP_VIEWS) return RHI_HANDLE_NULL;
    cd->format = fmt;
    cd->mip_levels = mips;
    cd->size = desc->size;

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
    ci.usage = VK_IMAGE_USAGE_SAMPLED_BIT | VK_IMAGE_USAGE_TRANSFER_DST_BIT |
               VK_IMAGE_USAGE_STORAGE_BIT | VK_IMAGE_USAGE_TRANSFER_SRC_BIT;
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
    if (vk_allocate_memory(vk, &ai, &cd->memory) != VK_SUCCESS) {
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
        if (vk_wait_fence(vk, fence) != VK_SUCCESS) {
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

    /* R586: upload CPU-provided faces — previously the faces[] payload was
     * silently dropped, so a faces-provided cubemap sampled UNDEFINED content
     * on VK (only compute-generated IBL cubemaps had real content; tests that
     * expected black "worked" by accident). A cubemap is a 6-layer array:
     * reuse the texture-array transfer machinery per face. Mirrors the GL
     * contract: mip 0 only.
     * R625: RGBA16F faces join — the source is native f16 bytes (8B/px), the
     * exact byte contract the R624 readback returns (pre-R625 f16 faces were
     * skipped here, silently dropped just like the pre-R586 RGBA8 case). */
    {
        const VkDeviceSize face_bytes =
            (VkDeviceSize)desc->size * desc->size *
            (desc->format == RHI_FORMAT_R16G16B16A16_SFLOAT ? 8u : 4u);
        for (u32 i = 0; i < 6u; i++) {
            if (!desc->faces[i]) continue;
            VkBuffer staging;
            VkDeviceMemory staging_mem;
            if (!vk_texture_staging_alloc(vk, face_bytes, desc->faces[i],
                                          &staging, &staging_mem)) {
                LOG_WARN("VK: cubemap face %u staging alloc failed", i);
                continue;
            }
            VKArrayTransferCtx ctx = {0};
            ctx.image = cd->image;
            ctx.staging = staging;
            ctx.width = desc->size;
            ctx.height = desc->size;
            ctx.base_layer = i;
            ctx.layer_count = 1;
            ctx.old_layout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
            ctx.mid_layout = VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL;
            ctx.copy = true;
            ctx.aspect = VK_IMAGE_ASPECT_COLOR_BIT;
            if (!vk_texture_sync_submit(vk, staging, staging_mem,
                                        vk_array_transfer_record, &ctx))
                LOG_WARN("VK: cubemap face %u upload failed", i);
        }
    }

    u32 idx = rhi_alloc_slot(dev);
    dev->slots[idx].ptr = cd;
    dev->slots[idx].type = RHI_RES_CUBEMAP;
    return rhi_make_handle(idx, dev->slots[idx].generation);
}

void rhi_cubemap_destroy(RHIDevice *dev, RHICubemap cm) {
    if (!dev || !rhi_handle_valid(cm)) return;
    VKBackend *vk = vk_backend(dev);
    VKCubemapData *cd = rhi_get_resource_typed(dev, cm, RHI_RES_CUBEMAP);
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
    VKCubemapData *cd = (VKCubemapData *)rhi_get_resource_typed(dev, cm, RHI_RES_CUBEMAP);
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
    if (vk_wait_fence(vk, fence) != VK_SUCCESS)
        LOG_WARN("VK: vkWaitForFences failed for cubemap transition");
    vkDestroyFence(vk->device, fence, NULL);
    vkFreeCommandBuffers(vk->device, vk->cmd_pool, 1, &tmp_cb);
}

void rhi_texture_transition_to_read(RHIDevice *dev, RHITexture tex) {
    if (!dev || !rhi_handle_valid(tex)) return;
    VKBackend *vk = vk_backend(dev);
    VKTextureData *td = (VKTextureData *)rhi_get_resource_typed(dev, tex, RHI_RES_TEXTURE);
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
    if (vk_wait_fence(vk, fence) != VK_SUCCESS)
        LOG_WARN("VK: vkWaitForFences failed for texture transition");
    vkDestroyFence(vk->device, fence, NULL);
    vkFreeCommandBuffers(vk->device, vk->cmd_pool, 1, &tmp_cb);

    if (td->cur_layout) td->cur_layout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
}

void rhi_cmd_bind_cubemap(RHICmdBuffer *cmd, RHICubemap cm, RHISampler sampler, u32 unit) {
    (void)cmd;
    VKBackend *vk = vk_cmd_backend(cmd);
    if (!vk || unit >= RHI_MAX_TEXTURE_UNITS) return;
    VKCubemapData *cd = (VKCubemapData *)rhi_get_resource_typed(g_current_device, cm, RHI_RES_CUBEMAP);
    VKSamplerData *sd = (VKSamplerData *)rhi_get_resource_typed(g_current_device, sampler, RHI_RES_SAMPLER);
    if (!cd || !sd || !vk->current_pipeline_data) return;

    VkDescriptorSetAllocateInfo dsai = {0};
    dsai.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
    dsai.descriptorPool = vk->desc_pools[vk->current_frame];
    dsai.descriptorSetCount = 1;
    dsai.pSetLayouts = &vk->desc_layout;

    VkDescriptorSet ds;
    if (vkAllocateDescriptorSets(vk->device, &dsai, &ds) != VK_SUCCESS) return;

    VkDescriptorImageInfo image_info = {0};
    image_info.sampler = sd->sampler;
    image_info.imageView = cd->view;
    image_info.imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;

    VkWriteDescriptorSet write = {0};
    write.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
    write.dstSet = ds;
    write.dstBinding = unit;
    write.descriptorCount = 1;
    write.descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
    write.pImageInfo = &image_info;
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
void rhi_cmd_set_depth_func_less_or_equal(RHICmdBuffer *cmd) {
    (void)vk_cmd_backend(cmd);
}
void rhi_cmd_set_depth_func_less(RHICmdBuffer *cmd) {
    (void)vk_cmd_backend(cmd);
}

/* R80-2: Vulkan no-ops — depth mask and cull face are handled by pipeline state. */
void rhi_cmd_set_depth_mask(RHICmdBuffer *cmd, bool enabled) {
    (void)enabled;
    (void)vk_cmd_backend(cmd);
}
void rhi_cmd_set_cull_face(RHICmdBuffer *cmd, bool enabled) {
    (void)enabled;
    (void)vk_cmd_backend(cmd);
}

void rhi_buffer_update(RHIDevice *dev, RHIBuffer buf, const void *data, usize size) {
    if (dev == NULL) return;
    VKBackend *vk = vk_backend(dev);
    VKBufferData *bd = (VKBufferData *)rhi_get_resource_typed(dev, buf, RHI_RES_BUFFER);
    if (!bd || !data || size == 0u) return;
    /* R417: clamp to buffer size on all paths — the persistent-mapped memcpy
     * below was unclamped (OOB write past the mapped allocation). */
    if (size > bd->size) size = bd->size;
    if (bd->mapped) {
        memcpy(bd->mapped, data, size);
    } else if (bd->device_local) {
        /* R181: rare updates to static DEVICE_LOCAL meshes (e.g. terrain flatten). */
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
    if (dev == NULL) return;
    VKBackend *vk = vk_backend(dev);
    VKBufferData *bd = (VKBufferData *)rhi_get_resource_typed(dev, buf, RHI_RES_BUFFER);
    if (!bd || !data || size == 0u) return;
    if (offset >= bd->size) return;
    if (size > bd->size - offset) size = bd->size - offset;
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
    if (dev == NULL) return NULL;
    VKBackend *vk = vk_backend(dev);
    if (vk->device_lost) return NULL; /* R578: vkMapMemory can block on a dead device */
    VKBufferData *bd = (VKBufferData *)rhi_get_resource_typed(dev, buf, RHI_RES_BUFFER);
    if (!bd) return NULL;
    if (bd->mapped) return bd->mapped;
    /* C-BUF-4: DEVICE_LOCAL maps through a host shadow — downloaded on map,
     * uploaded back on unmap — so map writes are device/read-visible after
     * unmap on BOTH backends (GL maps are ordinary writable buffer maps).
     * Previously this refused with NULL, diverging from GL. */
    if (bd->device_local) {
        if (bd->map_shadow) return bd->map_shadow; /* nested map */
        bd->map_shadow = malloc(bd->size);
        if (!bd->map_shadow) return NULL;
        if (!vk_buffer_staging_download(vk, bd->buffer, 0, bd->map_shadow, bd->size)) {
            free(bd->map_shadow);
            bd->map_shadow = NULL;
            LOG_WARN("VK: staging download failed in buffer_map");
            return NULL;
        }
        return bd->map_shadow;
    }
    void *mapped = NULL;
    if (vkMapMemory(vk->device, bd->memory, 0, VK_WHOLE_SIZE, 0, &mapped) != VK_SUCCESS) {
        LOG_WARN("VK: vkMapMemory failed in buffer_map");
        return NULL;
    }
    return mapped;
}

void rhi_buffer_unmap(RHIDevice *dev, RHIBuffer buf) {
    if (dev == NULL) return;
    VKBackend *vk = vk_backend(dev);
    VKBufferData *bd = (VKBufferData *)rhi_get_resource_typed(dev, buf, RHI_RES_BUFFER);
    if (!bd) return;
    if (bd->mapped) return; /* persistent mapping */
    /* C-BUF-4: publish the shadow's writes back to the DEVICE_LOCAL buffer. */
    if (bd->device_local) {
        if (bd->map_shadow) {
            if (!vk_buffer_staging_upload(vk, bd->buffer, 0, bd->map_shadow, bd->size))
                LOG_WARN("VK: staging upload failed in buffer_unmap");
            free(bd->map_shadow);
            bd->map_shadow = NULL;
        }
        return;
    }
    vkUnmapMemory(vk->device, bd->memory);
}

bool rhi_buffer_read(RHIDevice *dev, RHIBuffer buf, void *dst, usize offset, usize size) {
    if (dev == NULL) return false;
    VKBackend *vk = vk_backend(dev);
    VKBufferData *bd = (VKBufferData *)rhi_get_resource_typed(dev, buf, RHI_RES_BUFFER);
    if (!bd || !dst || size == 0u) return false;
    if (offset >= bd->size) return false;
    if (size > bd->size - offset) size = bd->size - offset;
    if (bd->mapped) {
        memcpy(dst, bd->mapped + offset, size);
        return true;
    }
    if (bd->device_local)
        return vk_buffer_staging_download(vk, bd->buffer, offset, dst, size);
    if (vk->device_lost) return false; /* R578: vkMapMemory can block on a dead device */
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
    VKBackend *vk = vk_cmd_backend(cmd);
    if (!vk) return;
    VKBufferData *bd = (VKBufferData *)rhi_get_resource_typed(g_current_device, buf, RHI_RES_BUFFER);
    if (!bd) return;
    if (offset >= bd->size) return;
    if (size > bd->size - offset) size = bd->size - offset;
    if (size == 0u) return;
    vk_suspend_pass_for_compute(vk);
    VkCommandBuffer cb = vk->cmd_buffers[vk->current_frame];

    /* vkCmdUpdateBuffer is limited to 65536 bytes and requires 4-byte align. */
    if (size > 65536u || ((offset | size) & 3u) != 0u) {
        LOG_WARN("VK: rhi_cmd_update_buffer requires 4-byte align and size<=65536");
        return;
    }

    /* WAR: a previous draw/dispatch may still be reading this buffer (the
     * per-draw UBO rebind pattern updates one buffer twice in a frame). The
     * post-update barrier below only orders the transfer write against LATER
     * shader reads; without this pre barrier the write can land before an
     * earlier draw's reads finish — observed as flaky identical pixels on
     * MoltenVK (deferred gbuffer factor test). */
    VkBufferMemoryBarrier pre_update = {0};
    pre_update.sType = VK_STRUCTURE_TYPE_BUFFER_MEMORY_BARRIER;
    pre_update.srcAccessMask = VK_ACCESS_SHADER_READ_BIT
                             | VK_ACCESS_INDIRECT_COMMAND_READ_BIT
                             | VK_ACCESS_VERTEX_ATTRIBUTE_READ_BIT;
    pre_update.dstAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
    pre_update.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
    pre_update.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
    pre_update.buffer = bd->buffer;
    pre_update.offset = offset;
    pre_update.size = size;
    vkCmdPipelineBarrier(cb,
        VK_PIPELINE_STAGE_VERTEX_INPUT_BIT | VK_PIPELINE_STAGE_VERTEX_SHADER_BIT
            | VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT | VK_PIPELINE_STAGE_COMPUTE_SHADER_BIT
            | VK_PIPELINE_STAGE_DRAW_INDIRECT_BIT,
        VK_PIPELINE_STAGE_TRANSFER_BIT,
        0, 0, NULL, 1, &pre_update, 0, NULL);

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
    VKBackend *vk = vk_cmd_backend(cmd);
    if (!vk) return;
    VKBufferData *src_bd = (VKBufferData *)rhi_get_resource_typed(g_current_device, src, RHI_RES_BUFFER);
    VKBufferData *dst_bd = (VKBufferData *)rhi_get_resource_typed(g_current_device, dst, RHI_RES_BUFFER);
    if (!src_bd || !dst_bd) return;
    /* R425: clamp against both buffer sizes like rhi_cmd_update_buffer —
     * an oversized copy would read/write past the smaller buffer. */
    if (size > src_bd->size) size = src_bd->size;
    if (size > dst_bd->size) size = dst_bd->size;
    if (size == 0u) return;
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
                               | VK_ACCESS_TRANSFER_WRITE_BIT | VK_ACCESS_TRANSFER_READ_BIT
                               | VK_ACCESS_INDIRECT_COMMAND_READ_BIT
                               | VK_ACCESS_VERTEX_ATTRIBUTE_READ_BIT;
    barriers[1].dstAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
    barriers[1].srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
    barriers[1].dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
    barriers[1].buffer = dst_bd->buffer;
    barriers[1].offset = 0;
    barriers[1].size = size;
    vkCmdPipelineBarrier(cb,
        VK_PIPELINE_STAGE_COMPUTE_SHADER_BIT | VK_PIPELINE_STAGE_TRANSFER_BIT
            | VK_PIPELINE_STAGE_HOST_BIT | VK_PIPELINE_STAGE_VERTEX_INPUT_BIT
            | VK_PIPELINE_STAGE_VERTEX_SHADER_BIT | VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT
            | VK_PIPELINE_STAGE_DRAW_INDIRECT_BIT,
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
    VKBackend *vk = vk_cmd_backend(cmd);
    if (!vk) return;
    VKBufferData *bd = (VKBufferData *)rhi_get_resource_typed(g_current_device, buf, RHI_RES_BUFFER);
    if (!bd) return;
    /* R425: clamp offset+size against the buffer like rhi_cmd_update_buffer. */
    if (offset >= bd->size) return;
    if (size > bd->size - offset) size = bd->size - offset;
    if (size == 0u) return;
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
                              | VK_ACCESS_INDIRECT_COMMAND_READ_BIT | VK_ACCESS_SHADER_READ_BIT
                              | VK_ACCESS_VERTEX_ATTRIBUTE_READ_BIT;
    to_transfer.dstAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
    to_transfer.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
    to_transfer.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
    to_transfer.buffer = bd->buffer;
    to_transfer.offset = offset;
    to_transfer.size = size;
    vkCmdPipelineBarrier(cb,
        VK_PIPELINE_STAGE_COMPUTE_SHADER_BIT | VK_PIPELINE_STAGE_TRANSFER_BIT
            | VK_PIPELINE_STAGE_DRAW_INDIRECT_BIT | VK_PIPELINE_STAGE_VERTEX_INPUT_BIT
            | VK_PIPELINE_STAGE_VERTEX_SHADER_BIT | VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT,
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
    VKBackend *vk = vk_cmd_backend(cmd);
    if (!vk) return;
    if (!vk->current_pipeline_data) return;

    VKBufferData *bd0 = (VKBufferData *)rhi_get_resource_typed(g_current_device, buf0, RHI_RES_BUFFER);
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
        bd1 = (VKBufferData *)rhi_get_resource_typed(g_current_device, buf1, RHI_RES_BUFFER);
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

static void vk_offscreen_fbo_release(VKBackend *vk, VKFBOData *fd) {
    if (!vk || !fd) return;
    if (fd->framebuffer) vkDestroyFramebuffer(vk->device, fd->framebuffer, NULL);
    if (fd->render_pass) vkDestroyRenderPass(vk->device, fd->render_pass, NULL);
    if (fd->render_pass_load) vkDestroyRenderPass(vk->device, fd->render_pass_load, NULL);
    if (fd->color_view) vkDestroyImageView(vk->device, fd->color_view, NULL);
    if (fd->color_image) vkDestroyImage(vk->device, fd->color_image, NULL);
    if (fd->color_memory) vkFreeMemory(vk->device, fd->color_memory, NULL);
    if (fd->msaa_color_view) vkDestroyImageView(vk->device, fd->msaa_color_view, NULL);
    if (fd->msaa_color_image) vkDestroyImage(vk->device, fd->msaa_color_image, NULL);
    if (fd->msaa_color_memory) vkFreeMemory(vk->device, fd->msaa_color_memory, NULL);
    if (fd->depth_view) vkDestroyImageView(vk->device, fd->depth_view, NULL);
    if (fd->depth_image) vkDestroyImage(vk->device, fd->depth_image, NULL);
    if (fd->depth_memory) vkFreeMemory(vk->device, fd->depth_memory, NULL);
    if (fd->msaa_depth_view) vkDestroyImageView(vk->device, fd->msaa_depth_view, NULL);
    if (fd->msaa_depth_image) vkDestroyImage(vk->device, fd->msaa_depth_image, NULL);
    if (fd->msaa_depth_memory) vkFreeMemory(vk->device, fd->msaa_depth_memory, NULL);
    free(fd);
}

static RHIOffscreenFBO vk_offscreen_fbo_create(RHIDevice *dev, u32 width, u32 height,
                                               RHIFormat color_fmt, u32 requested_samples) {
    RHIOffscreenFBO fbo = {0};
    fbo.width = width;
    fbo.height = height;
    u32 sample_count = requested_samples == 0u ? 1u : requested_samples;
    if (!dev || rhi_sample_count_bit(sample_count) == 0u)
        return fbo;
    VKBackend *vk = vk_backend(dev);
    VkSampleCountFlagBits samples = vk_sample_count(sample_count);
    if (!vk || !vk_sample_count_supported(vk, sample_count) ||
        (sample_count > 1u && (!vk->feat_depth_stencil_resolve ||
                               !dev->capabilities.color_resolve_supported)))
        return fbo;
    fbo.sample_count = sample_count;

    VkFormat vk_color_fmt = vk_format_from_rhi(color_fmt);

    VKFBOData *fd = calloc(1, sizeof(VKFBOData));
    if (!fd) return fbo;
    fd->magic = VK_FBO_DATA_MAGIC;
    fd->color_fmt = vk_color_fmt;
    /* R619: the R617 portable-contract default; caller may replace it via
     * rhi_offscreen_fbo_set_clear_color. */
    fd->clear_color[0] = 0.05f; fd->clear_color[1] = 0.05f;
    fd->clear_color[2] = 0.1f;  fd->clear_color[3] = 1.0f;
    VkAttachmentDescription attachments[4] = {0};

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
    /* R550-E: +TRANSFER_SRC so the color target can be read back via
     * rhi_texture_read_pixels (same class of fix as R442 for the MRT
     * helper; the combined-color output readback in test_vulkan tripped
     * VUID-vkCmdCopyImageToBuffer-srcImage-00186 /
     * VUID-VkImageMemoryBarrier-oldLayout-01212 without it). */
    ci.usage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT | VK_IMAGE_USAGE_SAMPLED_BIT |
               VK_IMAGE_USAGE_TRANSFER_SRC_BIT;
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
    if (vk_allocate_memory(vk, &ai, &fd->color_memory) != VK_SUCCESS) {
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
    /* R603: +TRANSFER_SRC so the wrapped depth texture (fbo.depth_tex) can
     * be read back via rhi_texture_read_pixels — native f32 depth semantics
     * for FBO attachment depth, completing the readback family (R602 did
     * standalone D32 textures). Permissive flag; rendering is unaffected. */
    ci.usage = VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT |
               VK_IMAGE_USAGE_SAMPLED_BIT | VK_IMAGE_USAGE_TRANSFER_SRC_BIT;
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
    if (vk_allocate_memory(vk, &ai, &fd->depth_memory) != VK_SUCCESS) {
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

    fd->samples = samples;
    if (samples != VK_SAMPLE_COUNT_1_BIT) {
        if (!vk_create_attachment_image(vk, vk_color_fmt, width, height, samples,
                VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT,
                VK_IMAGE_ASPECT_COLOR_BIT, &fd->msaa_color_image,
                &fd->msaa_color_memory, &fd->msaa_color_view) ||
            !vk_create_attachment_image(vk, VK_FORMAT_D32_SFLOAT, width, height, samples,
                VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT,
                VK_IMAGE_ASPECT_DEPTH_BIT, &fd->msaa_depth_image,
                &fd->msaa_depth_memory, &fd->msaa_depth_view)) {
            vk_offscreen_fbo_release(vk, fd);
            return fbo;
        }
    }

    attachments[0].format = vk_color_fmt;
    attachments[0].samples = samples;
    attachments[0].loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
    attachments[0].storeOp = VK_ATTACHMENT_STORE_OP_STORE;
    attachments[0].stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
    attachments[0].stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
    attachments[0].initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
    attachments[0].finalLayout = samples == VK_SAMPLE_COUNT_1_BIT
        ? VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL
        : VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
    attachments[1].format = vk_color_fmt;
    attachments[1].samples = VK_SAMPLE_COUNT_1_BIT;
    attachments[1].loadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
    attachments[1].storeOp = VK_ATTACHMENT_STORE_OP_STORE;
    attachments[1].stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
    attachments[1].stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
    attachments[1].initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
    attachments[1].finalLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
    attachments[2].format = VK_FORMAT_D32_SFLOAT;
    attachments[2].samples = samples;
    attachments[2].loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
    /* STORE so depth survives a render-pass suspend (compute dispatch). */
    attachments[2].storeOp = VK_ATTACHMENT_STORE_OP_STORE;
    attachments[2].stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
    attachments[2].stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
    attachments[2].initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
    attachments[2].finalLayout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;
    attachments[3].format = VK_FORMAT_D32_SFLOAT;
    attachments[3].samples = VK_SAMPLE_COUNT_1_BIT;
    attachments[3].loadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
    attachments[3].storeOp = VK_ATTACHMENT_STORE_OP_STORE;
    attachments[3].stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
    attachments[3].stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
    attachments[3].initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
    attachments[3].finalLayout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_READ_ONLY_OPTIMAL;

    if (samples == VK_SAMPLE_COUNT_1_BIT) {
        attachments[1].format = VK_FORMAT_D32_SFLOAT;
        attachments[1].samples = VK_SAMPLE_COUNT_1_BIT;
        attachments[1].loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
        attachments[1].storeOp = VK_ATTACHMENT_STORE_OP_STORE;
        attachments[1].stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
        attachments[1].stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
        attachments[1].initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
        attachments[1].finalLayout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;
    }

    VkSubpassDependency dep = {0};
    vk_external_dep_color_depth(&dep);

    VkSubpassDescription sp = {0};
    sp.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
    sp.colorAttachmentCount = 1;
    VkAttachmentReference color_ref = {0, VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL};
    VkAttachmentReference depth_ref = {1, VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL};
    sp.pColorAttachments = &color_ref;
    sp.pDepthStencilAttachment = &depth_ref;

    VkRenderPassCreateInfo rpci = {0};
    rpci.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
    rpci.attachmentCount = 2;
    rpci.pAttachments = attachments;
    rpci.subpassCount = 1;
    rpci.pSubpasses = &sp;
    rpci.dependencyCount = 1;
    rpci.pDependencies = &dep;
    if (samples != VK_SAMPLE_COUNT_1_BIT) {
        VkAttachmentReference2 color_ref2 = {0};
        color_ref2.sType = VK_STRUCTURE_TYPE_ATTACHMENT_REFERENCE_2;
        color_ref2.attachment = 0;
        color_ref2.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
        VkAttachmentReference2 resolve_ref2 = color_ref2;
        resolve_ref2.attachment = 1;
        VkAttachmentReference2 depth_ref2 = color_ref2;
        depth_ref2.attachment = 2;
        depth_ref2.layout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;
        VkAttachmentReference2 depth_resolve_ref2 = depth_ref2;
        depth_resolve_ref2.attachment = 3;
        VkSubpassDescriptionDepthStencilResolve ds_resolve = {0};
        ds_resolve.sType = VK_STRUCTURE_TYPE_SUBPASS_DESCRIPTION_DEPTH_STENCIL_RESOLVE;
        ds_resolve.depthResolveMode = vk->depth_resolve_mode;
        ds_resolve.stencilResolveMode = VK_RESOLVE_MODE_NONE;
        ds_resolve.pDepthStencilResolveAttachment = &depth_resolve_ref2;
        VkSubpassDescription2 sp2 = {0};
        sp2.sType = VK_STRUCTURE_TYPE_SUBPASS_DESCRIPTION_2;
        sp2.pNext = &ds_resolve;
        sp2.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
        sp2.colorAttachmentCount = 1;
        sp2.pColorAttachments = &color_ref2;
        sp2.pResolveAttachments = &resolve_ref2;
        sp2.pDepthStencilAttachment = &depth_ref2;
        VkSubpassDependency2 dep2 = {0};
        dep2.sType = VK_STRUCTURE_TYPE_SUBPASS_DEPENDENCY_2;
        dep2.srcSubpass = dep.srcSubpass;
        dep2.dstSubpass = dep.dstSubpass;
        dep2.srcStageMask = dep.srcStageMask;
        dep2.srcAccessMask = dep.srcAccessMask;
        dep2.dstStageMask = dep.dstStageMask;
        dep2.dstAccessMask = dep.dstAccessMask;
        VkAttachmentDescription2 atts2[4] = {0};
        for (u32 i = 0; i < 4u; i++) {
            atts2[i].sType = VK_STRUCTURE_TYPE_ATTACHMENT_DESCRIPTION_2;
            atts2[i].format = attachments[i].format;
            atts2[i].samples = attachments[i].samples;
            atts2[i].loadOp = attachments[i].loadOp;
            atts2[i].storeOp = attachments[i].storeOp;
            atts2[i].stencilLoadOp = attachments[i].stencilLoadOp;
            atts2[i].stencilStoreOp = attachments[i].stencilStoreOp;
            atts2[i].initialLayout = attachments[i].initialLayout;
            atts2[i].finalLayout = attachments[i].finalLayout;
        }
        VkRenderPassCreateInfo2 rpci2 = {0};
        rpci2.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO_2;
        rpci2.attachmentCount = 4;
        rpci2.pAttachments = atts2;
        rpci2.subpassCount = 1;
        rpci2.pSubpasses = &sp2;
        rpci2.dependencyCount = 1;
        rpci2.pDependencies = &dep2;
        if (vkCreateRenderPass2(vk->device, &rpci2, NULL, &fd->render_pass) != VK_SUCCESS)
            goto fbo_create_fail;
    } else if (vkCreateRenderPass(vk->device, &rpci, NULL, &fd->render_pass) != VK_SUCCESS) {
fbo_create_fail:
        LOG_FATAL("VK: failed to create MRT render pass");
        vk_offscreen_fbo_release(vk, fd);
        return fbo;
    }
    if (samples == VK_SAMPLE_COUNT_1_BIT) {
        fd->render_pass_load = vk_make_resume_render_pass(vk, &rpci);
    } else {
        fd->render_pass_load = vk_create_msaa_resume_pass(vk, vk_color_fmt, samples);
        if (!fd->render_pass_load) {
            vk_offscreen_fbo_release(vk, fd);
            return fbo;
        }
    }

    VkImageView views[] = {samples == VK_SAMPLE_COUNT_1_BIT ? fd->color_view : fd->msaa_color_view,
                           samples == VK_SAMPLE_COUNT_1_BIT ? fd->depth_view : fd->color_view,
                           fd->msaa_depth_view, fd->depth_view};
    VkFramebufferCreateInfo fbci = {0};
    fbci.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
    fbci.renderPass = fd->render_pass;
    fbci.attachmentCount = samples == VK_SAMPLE_COUNT_1_BIT ? 2u : 4u;
    fbci.pAttachments = views;
    fbci.width = width;
    fbci.height = height;
    fbci.layers = 1;
    if (vkCreateFramebuffer(vk->device, &fbci, NULL, &fd->framebuffer) != VK_SUCCESS) {
        LOG_FATAL("VK: failed to create MRT framebuffer");
        vk_offscreen_fbo_release(vk, fd);
        return fbo;
    }

    VKTextureData *td = calloc(1, sizeof(VKTextureData));
    if (!td) {
        /* R359: GPU FBO already live in fd — tear down before returning null. */
        LOG_WARN("VK: offscreen color texture slot alloc failed");
        vk_offscreen_fbo_release(vk, fd);
        return (RHIOffscreenFBO){0};
    }
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
    if (!dd) {
        LOG_WARN("VK: offscreen depth texture slot alloc failed");
        /* Destroy the color slot first, then release the complete candidate. */
        fd->color_view = VK_NULL_HANDLE;
        fd->color_image = VK_NULL_HANDLE;
        fd->color_memory = VK_NULL_HANDLE;
        rhi_texture_destroy(dev, fbo.color_tex);
        vk_offscreen_fbo_release(vk, fd);
        return (RHIOffscreenFBO){0};
    }
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

RHIOffscreenFBO rhi_offscreen_fbo_create_desc(RHIDevice *dev, const RHIOffscreenFBODesc *desc) {
    RHIOffscreenFBO fbo = {0};
    if (!dev || !rhi_offscreen_fbo_desc_validate(&dev->capabilities, desc)) return fbo;
    if (desc->sample_count > 1u &&
        (!dev->capabilities.color_resolve_supported ||
         !dev->capabilities.depth_resolve_supported)) return fbo;
    return vk_offscreen_fbo_create(dev, desc->width, desc->height,
                                   desc->color_format, desc->sample_count);
}

RHIOffscreenFBO rhi_offscreen_fbo_create_fmt(RHIDevice *dev, u32 width, u32 height,
                                             RHIFormat color_fmt) {
    return vk_offscreen_fbo_create(dev, width, height, color_fmt, 1u);
}

RHIOffscreenFBO rhi_offscreen_fbo_create(RHIDevice *dev, u32 width, u32 height) {
    return rhi_offscreen_fbo_create_fmt(dev, width, height, RHI_FORMAT_B8G8R8A8_UNORM);
}

void rhi_offscreen_fbo_destroy(RHIDevice *dev, RHIOffscreenFBO *fbo) {
    if (!dev || !fbo) return;
    VKBackend *vk = vk_backend(dev);
    VKFBOData *fd = rhi_get_resource_typed(dev, fbo->fb, RHI_RES_FRAMEBUFFER);
    if (!fd) return;
    if (vkDeviceWaitIdle(vk->device) != VK_SUCCESS)
        LOG_WARN("VK: vkDeviceWaitIdle failed in offscreen_fbo_destroy");
    vk_offscreen_fbo_release(vk, fd);
    /* R425: free the VKTextureData structs behind the color/depth texture
     * slots (calloc'd at create) — the old code freed only the slots,
     * leaking 2 structs per destroy (resize recreates all post FBOs). */
    if (rhi_handle_valid(fbo->color_tex)) {
        VKTextureData *td = (VKTextureData *)rhi_get_resource_typed(
            dev, fbo->color_tex, RHI_RES_TEXTURE);
        if (td) free(td);
        if (dev->slots[fbo->color_tex.index].ptr == td)
            dev->slots[fbo->color_tex.index].ptr = NULL;
    }
    if (rhi_handle_valid(fbo->depth_tex)) {
        VKTextureData *dd = (VKTextureData *)rhi_get_resource_typed(
            dev, fbo->depth_tex, RHI_RES_TEXTURE);
        if (dd) free(dd);
        if (dev->slots[fbo->depth_tex.index].ptr == dd)
            dev->slots[fbo->depth_tex.index].ptr = NULL;
    }
    rhi_free_slot(dev, fbo->fb);
    rhi_free_slot(dev, fbo->color_tex);
    rhi_free_slot(dev, fbo->depth_tex);
    memset(fbo, 0, sizeof(*fbo));
}

void rhi_offscreen_fbo_bind(RHICmdBuffer *cmd, RHIOffscreenFBO *fbo) {
    (void)cmd;
    if (!fbo) return;
    VKBackend *vk = vk_cmd_backend(cmd);
    if (!vk) return;
    VKFBOData *fd = rhi_get_resource_typed(g_current_device, fbo->fb, RHI_RES_FRAMEBUFFER);
    if (!fd) return;

    /* This pass clears + writes the depth attachment and ends with it in
     * DEPTH_STENCIL_ATTACHMENT_OPTIMAL (the render pass finalLayout).  Track
     * that so a later rhi_cmd_transition_depth_to_read re-makes it readable
     * (post-fx like tonemap/cinematic re-bind the scene FBO then god rays /
     * debug viz sample its depth).
     * R611: under MSAA the wrapper wraps the single-sample RESOLVE TARGET,
     * not the multisampled attachment — that image ends the pass in
     * DEPTH_STENCIL_READ_ONLY_OPTIMAL (the resolve attachment finalLayout),
     * which is also what rhi_texture_read_pixels' R603 fbo_depth path needs
     * as oldLayout. */
    VKTextureData *dtd = (VKTextureData *)rhi_get_resource_typed(
        g_current_device, fbo->depth_tex, RHI_RES_TEXTURE);
    if (dtd) dtd->cur_layout = (fd->samples != VK_SAMPLE_COUNT_1_BIT)
        ? VK_IMAGE_LAYOUT_DEPTH_STENCIL_READ_ONLY_OPTIMAL
        : VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;

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
    VkClearValue clears[4];
    memset(clears, 0, sizeof(clears));
    /* R619: caller-owned bind clear color (stored per-FBO; the R617
     * portable-contract default is installed at create). Depth stays 1.0. */
    clears[0].color.float32[0] = fd->clear_color[0];
    clears[0].color.float32[1] = fd->clear_color[1];
    clears[0].color.float32[2] = fd->clear_color[2];
    clears[0].color.float32[3] = fd->clear_color[3];
    clears[fd->samples == VK_SAMPLE_COUNT_1_BIT ? 1u : 2u].depthStencil.depth = 1.0f;
    rpi.clearValueCount = fd->samples == VK_SAMPLE_COUNT_1_BIT ? 2u : 4u;
    rpi.pClearValues = clears;
    vkCmdBeginRenderPass(vk->cmd_buffers[vk->current_frame], &rpi,
        VK_SUBPASS_CONTENTS_INLINE);
    vk->render_pass_active = true;
    vk_record_pass(vk, fd->render_pass_load, fd->framebuffer, fbo->width, fbo->height,
                   fd->color_fmt, fd->samples);

    VkViewport vp = {0, 0, (f32)fbo->width, (f32)fbo->height, 0, 1};
    vkCmdSetViewport(vk->cmd_buffers[vk->current_frame], 0, 1, &vp);
    VkRect2D sc = {{0, 0}, {fbo->width, fbo->height}};
    vkCmdSetScissor(vk->cmd_buffers[vk->current_frame], 0, 1, &sc);
    vk->vp_valid = false; vk->sc_valid = false;  /* R95-2: invalidate cache */
}

void rhi_offscreen_fbo_bind_load(RHICmdBuffer *cmd, RHIOffscreenFBO *fbo) {
    (void)cmd;
    if (!fbo) return;
    VKBackend *vk = vk_cmd_backend(cmd);
    if (!vk) return;
    VKFBOData *fd = rhi_get_resource_typed(g_current_device, fbo->fb, RHI_RES_FRAMEBUFFER);
    if (!fd || !fd->render_pass_load) {
        /* Fallback if LOAD twin missing. */
        rhi_offscreen_fbo_bind(cmd, fbo);
        return;
    }

    /* Depth may be SHADER_READ_ONLY after transition_depth_to_read; LOAD twin
     * expects DEPTH_STENCIL_ATTACHMENT (finalLayout of the clear pass). */
    VKTextureData *dtd = (VKTextureData *)rhi_get_resource_typed(
        g_current_device, fbo->depth_tex, RHI_RES_TEXTURE);
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
    vk_record_pass(vk, fd->render_pass_load, fd->framebuffer, fbo->width, fbo->height,
                   fd->color_fmt, fd->samples);

    VkViewport vp = {0, 0, (f32)fbo->width, (f32)fbo->height, 0, 1};
    vkCmdSetViewport(vk->cmd_buffers[vk->current_frame], 0, 1, &vp);
    VkRect2D sc = {{0, 0}, {fbo->width, fbo->height}};
    vkCmdSetScissor(vk->cmd_buffers[vk->current_frame], 0, 1, &sc);
    vk->vp_valid = false; vk->sc_valid = false;
}

/* R619: caller-owned clear color — stored per-FBO, used by the next bind. */
void rhi_offscreen_fbo_set_clear_color(RHIDevice *dev, RHIOffscreenFBO *fbo,
                                       f32 r, f32 g, f32 b, f32 a) {
    if (!dev || !fbo || !rhi_handle_valid(fbo->fb)) return;
    VKFBOData *fd = rhi_get_resource_typed(dev, fbo->fb, RHI_RES_FRAMEBUFFER);
    if (!fd) return;
    fd->clear_color[0] = r; fd->clear_color[1] = g;
    fd->clear_color[2] = b; fd->clear_color[3] = a;
}

void rhi_offscreen_fbo_unbind(RHICmdBuffer *cmd, u32 screen_w, u32 screen_h) {
    (void)cmd;
    VKBackend *vk = vk_cmd_backend(cmd);
    if (!vk) return;

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
                   screen_w, screen_h, vk->swap_format, VK_SAMPLE_COUNT_1_BIT);

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
    /* R442: +TRANSFER_SRC so the G-buffer attachments can be read back via
     * rhi_texture_read_pixels (TEST 12 pixel gate). */
    ci.usage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT | VK_IMAGE_USAGE_SAMPLED_BIT |
               VK_IMAGE_USAGE_TRANSFER_SRC_BIT;
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
    if (vk_allocate_memory(vk, &ai, out_mem) != VK_SUCCESS) {
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
    if (dev == NULL || !rhi_mrt_desc_validate(width, height, formats,
                                               attachment_count)) return fbo;
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
        /* R608: TRANSFER_SRC lets rhi_texture_read_pixels copy the MRT depth
         * attachment out (same permission-only class as R602/R603). */
        ci.usage = VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT | VK_IMAGE_USAGE_SAMPLED_BIT |
                   VK_IMAGE_USAGE_TRANSFER_SRC_BIT;
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
        if (vk_allocate_memory(vk, &ai, &md->depth_memory) != VK_SUCCESS) {
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
    vk_external_dep_color_depth(&dep);

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
        if (!td) {
            /* R360: never publish fb with missing color/depth handles. */
            LOG_WARN("VK: MRT color slot alloc failed (%u/%u)", i, attachment_count);
            rhi_mrt_fbo_destroy(dev, &fbo);
            return (RHIMRTFBO){0};
        }
        u32 cidx = rhi_alloc_slot(dev);
        td->image = md->color_images[i];
        td->view = md->color_views[i];
        td->memory = md->color_memories[i];
        td->width = width;
        td->height = height;
        /* R584: keep the attachment format on the wrapper — without it
         * rhi_texture_read_pixels falls back to 4B/px and its staging
         * buffer overflows on SFLOAT MRT attachments (GPU fault; the same
         * bug class R445 fixed for standalone textures). */
        td->format = vk_format_from_rhi(formats[i]);
        dev->slots[cidx].ptr  = td;
        dev->slots[cidx].type = RHI_RES_TEXTURE;
        fbo.color_tex[i] = rhi_make_handle(cidx, dev->slots[cidx].generation);
    }

    /* Register depth as a texture handle. */
    {
        VKTextureData *dd = calloc(1, sizeof(VKTextureData));
        if (!dd) {
            LOG_WARN("VK: MRT depth slot alloc failed");
            rhi_mrt_fbo_destroy(dev, &fbo);
            return (RHIMRTFBO){0};
        }
        u32 didx = rhi_alloc_slot(dev);
        dd->image = md->depth_image;
        dd->view = md->depth_view;
        dd->memory = md->depth_memory;
        dd->width = width;
        dd->height = height;
        /* R608: the depth wrapper never got its format (R584 fixed the color
         * attachments only) — the R602 aspect split and the R603 fbo_depth
         * readback discriminator both key on it. mip_levels stays 0: layout
         * is tracked via cur_layout (rhi_mrt_fbo_bind, R258). */
        dd->format = VK_FORMAT_D32_SFLOAT;
        dev->slots[didx].ptr  = dd;
        dev->slots[didx].type = RHI_RES_TEXTURE;
        fbo.depth_tex = rhi_make_handle(didx, dev->slots[didx].generation);
    }

    return fbo;
}

void rhi_mrt_fbo_destroy(RHIDevice *dev, RHIMRTFBO *fbo) {
    if (!dev || !fbo) return;
    VKBackend *vk = vk_backend(dev);
    VKMRTFBOData *md = (VKMRTFBOData *)rhi_get_resource_typed(dev, fbo->fb, RHI_RES_MRT_FBO);
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
            VKTextureData *td = (VKTextureData *)rhi_get_resource_typed(
                dev, fbo->color_tex[i], RHI_RES_TEXTURE);
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
        VKTextureData *dd = (VKTextureData *)rhi_get_resource_typed(
            dev, fbo->depth_tex, RHI_RES_TEXTURE);
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
    VKBackend *vk = vk_cmd_backend(cmd);
    if (!vk) return;
    VKMRTFBOData *md = (VKMRTFBOData *)rhi_get_resource_typed(
        g_current_device, fbo->fb, RHI_RES_MRT_FBO);
    if (!md) return;

    /* R258 (CORRECTNESS): this MRT (G-buffer) render pass ends with the depth
     * attachment in DEPTH_STENCIL_READ_ONLY_OPTIMAL (its finalLayout, set at
     * create). Track that on the depth texture handle so a later
     * rhi_cmd_transition_depth_to_read issues a barrier with the correct
     * oldLayout and actually re-runs each frame. Without this the depth's
     * cur_layout stayed UNDEFINED (calloc): the first transition used
     * oldLayout=DEPTH_STENCIL_ATTACHMENT_OPTIMAL (mismatching the real
     * READ_ONLY layout), and from frame 2 the idempotent SHADER_READ_ONLY
     * early-return skipped the barrier entirely — leaving the deferred Hi-Z
     * compute to sample gbuf_depth with a stale layout AND no depth-write
     * (LATE_FRAGMENT_TESTS) → compute-read dependency (occlusion flicker /
     * validation errors). Mirrors rhi_offscreen_fbo_bind, which tracks its own
     * ATTACHMENT_OPTIMAL finalLayout. GL is unaffected (transition is a no-op). */
    VKTextureData *dtd = (VKTextureData *)rhi_get_resource_typed(
        g_current_device, fbo->depth_tex, RHI_RES_TEXTURE);
    if (dtd) dtd->cur_layout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_READ_ONLY_OPTIMAL;

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
    vk_record_pass(vk, md->render_pass_load, md->framebuffer, fbo->width, fbo->height,
                   VK_FORMAT_UNDEFINED, VK_SAMPLE_COUNT_1_BIT);

    VkViewport vp = {0, 0, (f32)fbo->width, (f32)fbo->height, 0, 1};
    vkCmdSetViewport(vk->cmd_buffers[vk->current_frame], 0, 1, &vp);
    VkRect2D sc = {{0, 0}, {fbo->width, fbo->height}};
    vkCmdSetScissor(vk->cmd_buffers[vk->current_frame], 0, 1, &sc);
    vk->vp_valid = false; vk->sc_valid = false;  /* R95-2: invalidate cache */
}

void rhi_mrt_fbo_bind_load(RHICmdBuffer *cmd, RHIMRTFBO *fbo) {
    (void)cmd;
    if (!fbo) return;
    VKBackend *vk = vk_cmd_backend(cmd);
    if (!vk) return;
    VKMRTFBOData *md = (VKMRTFBOData *)rhi_get_resource_typed(g_current_device, fbo->fb, RHI_RES_MRT_FBO);
    if (!md || !md->render_pass_load) {
        rhi_mrt_fbo_bind(cmd, fbo);
        return;
    }

    if (vk->render_pass_active) {
        vkCmdEndRenderPass(vk->cmd_buffers[vk->current_frame]);
        vk->render_pass_active = false;
    }

    VkRenderPassBeginInfo rpi = {0};
    rpi.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
    rpi.renderPass = md->render_pass_load;
    rpi.framebuffer = md->framebuffer;
    rpi.renderArea.extent.width = fbo->width;
    rpi.renderArea.extent.height = fbo->height;
    vkCmdBeginRenderPass(vk->cmd_buffers[vk->current_frame], &rpi,
                         VK_SUBPASS_CONTENTS_INLINE);
    vk->render_pass_active = true;
    vk_record_pass(vk, md->render_pass_load, md->framebuffer,
                   fbo->width, fbo->height, VK_FORMAT_UNDEFINED,
                   VK_SAMPLE_COUNT_1_BIT);

    VkViewport vp = {0, 0, (f32)fbo->width, (f32)fbo->height, 0, 1};
    vkCmdSetViewport(vk->cmd_buffers[vk->current_frame], 0, 1, &vp);
    VkRect2D sc = {{0, 0}, {fbo->width, fbo->height}};
    vkCmdSetScissor(vk->cmd_buffers[vk->current_frame], 0, 1, &sc);
    vk->vp_valid = false;
    vk->sc_valid = false;
}

void rhi_mrt_fbo_unbind(RHICmdBuffer *cmd, u32 screen_w, u32 screen_h) {
    rhi_offscreen_fbo_unbind(cmd, screen_w, screen_h);
}

/* ======================================================================== */
/* Depth cubemap FBO (point-light shadow maps) -- VK backend                */
/* ======================================================================== */

RHICubemapDepthFBO rhi_cubemap_depth_fbo_create(RHIDevice *dev, u32 size) {
    if (dev == NULL || size == 0u || size > RHI_MAX_DRAWABLE_DIMENSION) {
        return (RHICubemapDepthFBO){0};
    }
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
    /* R610: TRANSFER_SRC lets rhi_texture_read_pixels copy the cubemap depth
     * out (same permission-only class as R602/R603/R608/R609). */
    ci.usage = VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT | VK_IMAGE_USAGE_SAMPLED_BIT |
               VK_IMAGE_USAGE_TRANSFER_SRC_BIT;
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
    if (vk_allocate_memory(vk, &ai, &cd->depth_memory) != VK_SUCCESS) {
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
    vk_external_dep_depth_only(&dep);

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
    if (!td) {
        /* R359: face FBOs/views + depth image already live — tear down. */
        LOG_WARN("VK: cubemap depth texture slot alloc failed");
        for (u32 j = 0; j < 6; j++) {
            if (cd->face_fbos[j]) vkDestroyFramebuffer(vk->device, cd->face_fbos[j], NULL);
            if (cd->face_views[j]) vkDestroyImageView(vk->device, cd->face_views[j], NULL);
        }
        if (cd->render_pass_load) vkDestroyRenderPass(vk->device, cd->render_pass_load, NULL);
        if (cd->render_pass) vkDestroyRenderPass(vk->device, cd->render_pass, NULL);
        if (cd->depth_view) vkDestroyImageView(vk->device, cd->depth_view, NULL);
        if (cd->depth_memory) vkFreeMemory(vk->device, cd->depth_memory, NULL);
        if (cd->depth_image) vkDestroyImage(vk->device, cd->depth_image, NULL);
        free(cd);
        return (RHICubemapDepthFBO){0};
    }
    u32 tidx = rhi_alloc_slot(dev);
    td->image = cd->depth_image;
    td->view = cd->depth_view;
    td->memory = cd->depth_memory;
    td->width = size;
    td->height = size;
    /* R610: format keys the R602 aspect split and the R603 fbo_depth
     * readback discriminator; layers=6 marks the point-shadow cube so the
     * readback copies all six faces (mip_levels stays 0 — layout is tracked
     * via cur_layout, set by rhi_cubemap_depth_fbo_bind_face). */
    td->format = VK_FORMAT_D32_SFLOAT;
    td->layers = 6u;
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
    VKCubemapDepthFBOData *cd = (VKCubemapDepthFBOData *)rhi_get_resource_typed(
        dev, fbo->fb, RHI_RES_CUBEMAP_DEPTH_FBO);
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
        VKTextureData *td = (VKTextureData *)rhi_get_resource_typed(
            dev, fbo->depth_tex, RHI_RES_TEXTURE);
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
    VKBackend *vk = vk_cmd_backend(cmd);
    if (!vk) return;
    VKCubemapDepthFBOData *cd = (VKCubemapDepthFBOData *)rhi_get_resource_typed(
        g_current_device, fbo->fb, RHI_RES_CUBEMAP_DEPTH_FBO);
    if (!cd) return;

    /* R610: every face pass ends with its layer in DEPTH_STENCIL_READ_ONLY
     * (the finalLayout set at create). Track it on the wrapper so readback's
     * R603 fbo_depth path gets a correct oldLayout (R258/R609 fix class;
     * layers share one tracked layout — passes leave all rendered faces in
     * the same state). */
    VKTextureData *ctd = (VKTextureData *)rhi_get_resource_typed(
        g_current_device, fbo->depth_tex, RHI_RES_TEXTURE);
    if (ctd) ctd->cur_layout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_READ_ONLY_OPTIMAL;

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
                   fbo->size, fbo->size, VK_FORMAT_UNDEFINED, VK_SAMPLE_COUNT_1_BIT);

    VkViewport vp = {0, 0, (f32)fbo->size, (f32)fbo->size, 0, 1};
    vkCmdSetViewport(vk->cmd_buffers[vk->current_frame], 0, 1, &vp);
    VkRect2D sc = {{0, 0}, {fbo->size, fbo->size}};
    vkCmdSetScissor(vk->cmd_buffers[vk->current_frame], 0, 1, &sc);
    vk->vp_valid = false; vk->sc_valid = false;  /* R95-2: invalidate cache */
}

void rhi_cubemap_depth_fbo_unbind(RHICmdBuffer *cmd, u32 screen_w, u32 screen_h) {
    rhi_offscreen_fbo_unbind(cmd, screen_w, screen_h);
}
