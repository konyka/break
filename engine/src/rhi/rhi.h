#pragma once
#include <core/types.h>
#include <platform/platform_wsi.h>

/* ---- Handle: index + generation for safe resource reference ---- */
typedef struct { u32 index; u32 generation; } RHIHandle;

#define RHI_MAX_PRESENT_DAMAGE_RECTS 16u
#define RHI_MAX_SCREENSHOT_BYTES (64u * 1024u * 1024u)
#define RHI_MAX_DRAWABLE_DIMENSION 16384u
#define RHI_MAX_MIP_LEVELS 16u
#define RHI_MAX_TEXTURE_ARRAY_LAYERS 2048u
#define RHI_MAX_TEXTURE_UNITS 16u

typedef struct {
    i32 x;
    i32 y;
    u32 w;
    u32 h;
} RHIPresentRect;

/* ---- Strongly-typed handle aliases ---- */
typedef RHIHandle RHIBuffer;
typedef RHIHandle RHIShader;
typedef RHIHandle RHIPipeline;
typedef RHIHandle RHITexture;
typedef RHIHandle RHIFramebuffer;
typedef RHIHandle RHIRenderPass;
typedef RHIHandle RHIAccelerationStructure;

#define RHI_HANDLE_NULL ((RHIHandle){0, 0})
#define rhi_handle_valid(h) ((h).generation != 0)

/* ---- Enums ---- */
typedef enum {
    RHI_BACKEND_OPENGL,
    RHI_BACKEND_VULKAN,
    /* Plan C: native Metal backend (engine_rhi_metal) on Apple platforms.
     * Device family landed in Task 3 (create/caps/info), sticky device-lost
     * latch in Task 4. */
    RHI_BACKEND_METAL,
    /* Plan D: selectable on WIN32 via engine_rhi_d3d12; real device
     * creation landed in Task 3 (adapter scoring, queues, fence pacing,
     * sticky device-lost latch, DRED). */
    RHI_BACKEND_D3D12,
} RHIBackend;

typedef enum {
    RHI_ACCELERATION_STRUCTURE_BOTTOM_LEVEL,
    RHI_ACCELERATION_STRUCTURE_TOP_LEVEL,
} RHIAccelerationStructureType;

typedef struct {
    RHIAccelerationStructureType type;
    /* storage_size=0 = 后端延迟定尺寸（backend 内部决定） */
    usize storage_size;
} RHIAccelerationStructureDesc;

typedef struct {
    RHIBuffer vertex_buffer;
    usize vertex_offset;
    u32 vertex_count;
    u32 vertex_stride;
    u32 vertex_format;
    RHIBuffer index_buffer;
    usize index_offset;
    u32 index_count;
    bool indexed;
} RHIBLASOneTriangleDesc;

#define RHI_VERTEX_FORMAT_R32G32B32_SFLOAT 1u

typedef struct {
    usize acceleration_structure_size;
    usize build_scratch_size;
} RHIAccelerationStructureBuildSizes;

/* Serialized TLAS instance record (64 bytes, array-of-structs layout,
 * compatible with the Vulkan acceleration-structure instance ABI):
 * transform row-major 3x4, packed custom index/mask,
 * packed SBT offset/flags, then the BLAS device address. */
#define RHI_TLAS_INSTANCE_SIZE 64u
typedef struct {
    f32 transform[12];
    u32 instance_custom_index;
    u8  instance_mask;
    u32 sbt_record_offset;
    u32 instance_flags;
} RHITLASInstanceDesc;

typedef enum {
    RHI_NATIVE_HANDLE_NONE = 0,
    RHI_NATIVE_HANDLE_VULKAN = 1,
    RHI_NATIVE_HANDLE_METAL = 2,
    RHI_NATIVE_HANDLE_D3D12 = 3,
} RHINativeHandleType;

typedef enum {
    RHI_FEATURE_RAY_TRACING_PIPELINE = 1u << 0,
    RHI_FEATURE_RAY_QUERY = 1u << 1,
    RHI_FEATURE_ACCELERATION_STRUCTURE = 1u << 2,
} RHIFeatureBits;

/* 计划 E：后端 shader 源变体（RHICapabilities.shader_variant 的取值域）。 */
typedef enum {
    RHI_SHADER_VARIANT_GLSL    = 0, /* desktop GL 源（无后缀） */
    RHI_SHADER_VARIANT_GLSL_VK = 1, /* Vulkan 布局 GLSL（*_vk 后缀，push-constant 块） */
} RHIShaderVariant;

/* Capability bit for a power-of-two color sample count. */
static inline u32 rhi_sample_count_bit(u32 count) {
    u32 bit = 0u;
    if (count == 0u || (count & (count - 1u)) != 0u) return 0u;
    while (count > 1u) {
        count >>= 1u;
        bit++;
    }
    return 1u << bit;
}

typedef struct {
    RHIBackend backend;
    u32        color_sample_counts;
    u32        depth_sample_counts;
    u32        surface_sample_count;
    bool       color_resolve_supported;
    bool       depth_resolve_supported;
    bool       scissor_supported;
    bool       present_target_preserved;
    bool       present_damage_supported;
    bool       present_buffer_age_supported;
    u32        feature_bits;
    /* 迁移期新增（源码兼容追加，无 struct_size——调用方按完整结构编译）：
     * VK_KHR_dynamic_rendering / VK_KHR_synchronization2（或 API>=1.3 核心）
     * 的探测结果；只探测不消费，消费接入在后续计划。 */
    bool       dynamic_rendering_supported;
    bool       synchronization2_supported;
    /* 计划 E 新增（headless 契约：test_rhi_capabilities） */
    bool       push_constants_supported; /* VK=true，GL=false */
    u32        max_push_constant_size;   /* 字节；不支持为 0；VK=设备 limit（>=128） */
    bool       hiz_supported;            /* Hi-Z occlusion 金字塔路径 */
    bool       compute_supported;        /* rhi_cmd_dispatch 路径 */
    bool       indirect_draw_supported;  /* rhi_cmd_draw_*_indirect 族 */
    u32        shader_variant;           /* RHIShaderVariant */
} RHICapabilities;

#define RHI_DEVICE_NAME_MAX 256u
typedef struct {
    RHIBackend backend;
    char device_name[RHI_DEVICE_NAME_MAX];
    u32 vendor_id;
    u32 device_id;
    u32 api_version;
    u32 driver_version;
    u32 feature_bits;
} RHIDeviceInfo;

typedef enum {
    RHI_FORMAT_R8G8B8A8_UNORM,
    RHI_FORMAT_B8G8R8A8_UNORM,
    RHI_FORMAT_R16G16B16A16_SFLOAT,
    RHI_FORMAT_R16G16_SFLOAT,
    RHI_FORMAT_R32_FLOAT,
    RHI_FORMAT_D32_FLOAT,
    RHI_FORMAT_UNDEFINED,
} RHIFormat;

typedef enum {
    RHI_BUFFER_USAGE_VERTEX   = 1 << 0,
    RHI_BUFFER_USAGE_INDEX    = 1 << 1,
    RHI_BUFFER_USAGE_UNIFORM  = 1 << 2,
    RHI_BUFFER_USAGE_TEXEL    = 1 << 3,
    RHI_BUFFER_USAGE_STORAGE  = 1 << 4,
    RHI_BUFFER_USAGE_INDIRECT = 1 << 5,
    RHI_BUFFER_USAGE_AS_BUILD_INPUT = 1 << 6,
    RHI_BUFFER_USAGE_DEVICE_ADDRESS = 1 << 7,
} RHIBufferUsage;

typedef enum {
    RHI_FILTER_NEAREST,
    RHI_FILTER_LINEAR,
} RHIFilter;

typedef enum {
    RHI_WRAP_REPEAT,
    RHI_WRAP_CLAMP_TO_EDGE,
} RHIWrapMode;

/* ---- Descriptors ---- */
/* R440: moved above RHIPipelineDesc so the desc can carry per-pipeline MRT
 * attachment formats (still bounds RHIMRTFBO below).
 * R582: 4 -> 5 for the deferred G-Buffer's emissive target (RT4). All MRT
 * code paths are macro/count-driven, so existing <=4-attachment users are
 * unaffected. */
#define RHI_MRT_MAX_ATTACHMENTS 5

typedef enum {
    RHI_SHADER_RESOURCE_SAMPLER,
    RHI_SHADER_RESOURCE_UNIFORM,
    RHI_SHADER_RESOURCE_STORAGE,
    RHI_SHADER_RESOURCE_PUSH_CONSTANT,
    RHI_SHADER_RESOURCE_IMAGE,
} RHIShaderResourceKind;

static inline bool rhi_shader_resource_kind_is_buffer(RHIShaderResourceKind kind) {
    return kind == RHI_SHADER_RESOURCE_UNIFORM || kind == RHI_SHADER_RESOURCE_STORAGE;
}

static inline bool rhi_shader_resource_kind_is_push(RHIShaderResourceKind kind) {
    return kind == RHI_SHADER_RESOURCE_PUSH_CONSTANT;
}

static inline bool rhi_format_is_color(RHIFormat format) {
    return format == RHI_FORMAT_R8G8B8A8_UNORM || format == RHI_FORMAT_B8G8R8A8_UNORM ||
           format == RHI_FORMAT_R16G16B16A16_SFLOAT || format == RHI_FORMAT_R16G16_SFLOAT ||
           format == RHI_FORMAT_R32_FLOAT;
}

static inline bool rhi_mrt_formats_valid(const RHIFormat *formats, u32 count) {
    if (formats == NULL || count == 0u || count > RHI_MRT_MAX_ATTACHMENTS) return false;
    for (u32 i = 0u; i < count; ++i)
        if (!rhi_format_is_color(formats[i])) return false;
    return true;
}

typedef struct {
    u32 index_count;
    u32 instance_count;
    u32 first_index;
    i32 vertex_offset;
    u32 first_instance;
} RHIIndexedIndirectCommand;

static inline bool rhi_indirect_abi_valid(u32 stride, u32 draw_count) {
    return stride >= (u32)sizeof(RHIIndexedIndirectCommand) &&
           (stride % 4u) == 0u && draw_count != 0u;
}

typedef struct {
    RHIBufferUsage usage;
    usize          size;
    const void    *initial_data;
} RHIBufferDesc;

typedef struct {
    RHIShader vert;
    RHIShader frag;
    u32 vertex_stride;
    bool no_vertex_input;
    bool uses_textures;
    bool depth_compare_lequal;
    bool depth_write_disable;
    bool disable_culling;
    bool uses_texel_buffer;
    bool alpha_blend;
    /* Keep motion-vector MRT writes unblended while RT0 uses alpha blending.
     * This avoids accumulating transparent velocities across layers. */
    bool alpha_blend_color_only;
    bool font_vertex;
    bool is_instanced;
    bool skinned_vertex;
    bool is_compute;
    bool uses_storage;
    bool is_shadow_depth;
    bool wireframe;
    bool point_list;             /* R168-C: POINT_LIST topology (particles) */
    /* 计划 E Task 6：pipeline 声明其 push 块布局契约；后端据此建立绑定
     * （VK 真实消费：rhi_vk.c vk_push_alias_rows 的打包别名行服务于这些
     * 布局家族；GL 忽略——按 uniform 名直接反射，无布局概念）。
     * 5c-2a 删除 rhi_vk.c 手写布局表后这些字段暂无运行时读者（原读者
     * 即被删的表）；其成文的真实消费是 test_shader_io.c
     * vk_push_tables_match_reflection 尾段的「字段 → shader → 反射布局」
     * 三方闭环断言；默认 false 由 test_rhi_capabilities.c
     * pipeline_desc_contract_fields_have_defined_defaults 钉死。 */
    bool terrain_layout;         /* terrain_vk.vert/.frag 的 push 布局契约 */
    bool water_layout;           /* water_vk.vert/.frag 的 push 布局契约 */
    bool combined_aa_layout;     /* combined_taa_fxaa_vk.frag 的 push 布局契约 */
    bool combined_color_layout;  /* combined_color_vk.frag 的 push 布局契约 */
    /* Color attachment format of the render target this pipeline draws into.
     * 契约：pipeline 声明其绘制目标的颜色格式，后端据此保证
     * render-pass 兼容——pipeline 必须对着与所绑 FBO 颜色格式一致的
     * pass 构建（VK 真实消费；GL 忽略——帧缓冲格式由 FBO 绑定决定，
     * 无 render-pass 兼容约束）。The default value
     * (RHI_FORMAT_R8G8B8A8_UNORM == 0) selects the swapchain pass; set
     * RHI_FORMAT_R16G16B16A16_SFLOAT for the HDR scene FBO. 默认值契约由
     * test_rhi_capabilities.c pipeline_desc_contract_fields_have_defined_defaults
     * 钉死。 */
    RHIFormat color_format;
    /* Graphics attachment sample count. Zero means the legacy 1x target. */
    u32       sample_count;
    /* R440: MRT (G-buffer) target description. 契约：当
     * mrt_attachment_count > 1 时 pipeline 声明其绘制进一个带这些颜色
     * 附件格式（+ D32F depth）的多附件渲染目标，与 rhi_mrt_fbo_create
     * 对同格式构建的 pass render-pass 兼容——shader 写出的每个 fragment
     * 输出都有真实附件（VK 真实消费：据此选 render pass；GL 忽略）。
     * 默认 0/空由 test_rhi_capabilities.c
     * pipeline_desc_contract_fields_have_defined_defaults +
     * rhi_mrt_formats_valid 既有校验钉死。 */
    u32       mrt_attachment_count;
    RHIFormat mrt_formats[RHI_MRT_MAX_ATTACHMENTS];
} RHIPipelineDesc;

typedef struct {
    u32         width;
    u32         height;
    RHIFormat   format;
    u32         mip_levels;
    /* R593: initial texel bytes in the format's NATIVE layout on both
     * backends (RGBA8閳?B/px; RG16F閳?B/px f16 pairs; RGBA16F閳?B/px f16
     * quads; R32F/D32F閳?B/px f32). NULL leaves the texture undefined. */
    const void *data;
} RHITextureDesc;

typedef struct {
    u32       width;
    u32       height;
    RHIFormat color_format;
    u32       sample_count;
} RHIOffscreenFBODesc;

/* Returns true only when the descriptor can be created without silently
 * falling back to a different sample count. */

typedef struct {
    RHIFilter  min_filter;
    RHIFilter  mag_filter;
    RHIWrapMode wrap_u;
    RHIWrapMode wrap_v;
    RHIWrapMode wrap_w;
} RHISamplerDesc;

typedef RHIHandle RHISampler;

typedef RHIHandle RHICubemap;

/* ---- Command Buffer (opaque) ---- */
typedef struct RHICmdBuffer RHICmdBuffer;

/* ---- Device (opaque) ---- */
typedef struct RHIDevice RHIDevice;

typedef enum {
    RHI_DEVICE_STATUS_UNKNOWN = 0,
    RHI_DEVICE_STATUS_READY,
    RHI_DEVICE_STATUS_LOST,
} RHIDeviceStatus;

/* Outcome of a lifecycle operation.  Existing pointer/bool/void entrypoints
 * remain source-compatible; the *_ex entrypoints expose the reason instead of
 * collapsing every failure to NULL, false, or no-op. */
typedef enum {
    RHI_RESULT_OK = 0,
    RHI_RESULT_ERROR = -1,
    RHI_RESULT_INVALID_ARGUMENT = -2,
    RHI_RESULT_UNAVAILABLE = -3,
    RHI_RESULT_UNSUPPORTED = -4,
    RHI_RESULT_BUSY = -5,
    RHI_RESULT_OUT_OF_DATE = -6,
    RHI_RESULT_SURFACE_LOST = -7,
    RHI_RESULT_DEVICE_LOST = -8,
    RHI_RESULT_SYNC_FAILED = -9,
} RHIResult;

/* ---- Device API ---- */
/* `w` and `h` are physical drawable pixels, never logical UI points. */
RHIDevice *rhi_device_create(RHIBackend backend, void *window_native, void *display_native, u32 w, u32 h);
RHIDevice *rhi_device_create_ex(RHIBackend backend, void *window_native,
                                void *display_native, u32 w, u32 h,
                                RHIResult *out_result);
/* 编译期单后端的设备创建入口(Post-计划 A:enum 参数退役为内部细节)。
 * 双句柄:各编译后端按自身消费类型选取——VK 取 surface_native(Wayland
 * 上为 wl_surface*),GL 取 window_native(Wayland 上为 wl_egl_window*);
 * Metal 取 window_native(Cocoa 两 getter 同值);其余平台两 getter 返回
 * 相同句柄。 */
RHIDevice *rhi_device_create_compiled(void *window_native, void *surface_native,
                                      void *display_native, u32 w, u32 h);
void       rhi_device_destroy(RHIDevice *dev);
RHIResult  rhi_device_destroy_ex(RHIDevice *dev);
/* 把平台层 WSI 状态对象挂到设备（非拥有指针，Platform 拥有存储）。
 * 挂上后 rhi_device_destroy_ex 在 WSI DESTROYING 状态返回 RHI_RESULT_BUSY
 * 并拒绝销毁；wsi == NULL 解除挂载。 */
void       rhi_device_attach_wsi(RHIDevice *dev, PlatformWsiSurface *wsi);
bool       rhi_device_get_capabilities(const RHIDevice *dev, RHICapabilities *out);
RHIDeviceStatus rhi_device_get_status(const RHIDevice *dev);
/* Read-only diagnostics: resource slots in use and slot capacity, taken from
 * the core free list (never touches the backend). Either out pointer may be
 * NULL. False on a NULL device. */
bool       rhi_device_resource_usage(const RHIDevice *dev, u32 *out_used,
                                     u32 *out_capacity);
bool       rhi_device_get_info(const RHIDevice *dev, RHIDeviceInfo *out);
bool       rhi_backend_get_device_info(const RHIDevice *dev, RHIDeviceInfo *out);
bool       rhi_backend_cmd_build_blas_one_triangle(
               RHICmdBuffer *cmd, RHIDevice *dev,
               RHIAccelerationStructure blas,
               const RHIBLASOneTriangleDesc *desc,
               RHIBuffer scratch_buffer, usize scratch_offset);
u64        rhi_backend_acceleration_structure_get_device_address(
               RHIDevice *dev, RHIAccelerationStructure structure);
bool       rhi_backend_tlas_one_instance_get_build_sizes(
               RHIDevice *dev, RHIBuffer instance_buffer,
               RHIAccelerationStructureBuildSizes *out_sizes);
bool       rhi_backend_cmd_build_tlas_one_instance(
               RHICmdBuffer *cmd, RHIDevice *dev,
               RHIAccelerationStructure tlas, RHIBuffer instance_buffer,
               RHIBuffer scratch_buffer, usize scratch_offset);
/* One-shot build submission (like texture staging): records into a private
 * command buffer, submits, and waits for the queue to idle. Must not be called
 * between rhi_frame_begin and rhi_frame_end. On return the acceleration
 * structure is safe to use and all inputs are safe to destroy. */
bool       rhi_build_blas_one_triangle(
               RHIDevice *dev, RHIAccelerationStructure blas,
               const RHIBLASOneTriangleDesc *desc,
               RHIBuffer scratch_buffer, usize scratch_offset);
/* TLAS one-instance path: encode the instance record, query TLAS sizes, and
 * record the build. The instance buffer must be STORAGE|DEVICE_ADDRESS and at
 * least RHI_TLAS_INSTANCE_SIZE bytes. */
bool       rhi_tlas_instance_encode(
               void *dst, usize dst_size,
               u64 blas_device_address,
               const RHITLASInstanceDesc *desc);
u64        rhi_acceleration_structure_get_device_address(
               RHIDevice *dev, RHIAccelerationStructure structure);
bool       rhi_tlas_one_instance_get_build_sizes(
               RHIDevice *dev, RHIBuffer instance_buffer,
               RHIAccelerationStructureBuildSizes *out_sizes);
bool       rhi_build_tlas_one_instance(
               RHIDevice *dev, RHIAccelerationStructure tlas,
               RHIBuffer instance_buffer, RHIBuffer scratch_buffer,
               usize scratch_offset);
bool       rhi_acceleration_structure_desc_validate(
               const RHIAccelerationStructureDesc *desc);
bool       rhi_blas_one_triangle_desc_validate(
               const RHIBLASOneTriangleDesc *desc);
bool       rhi_blas_one_triangle_get_build_sizes(
               RHIDevice *dev, const RHIBLASOneTriangleDesc *desc,
               RHIAccelerationStructureBuildSizes *out_sizes);
RHIAccelerationStructure rhi_acceleration_structure_create(
               RHIDevice *dev, const RHIAccelerationStructureDesc *desc);
void       rhi_acceleration_structure_destroy(
               RHIDevice *dev, RHIAccelerationStructure structure);
RHIAccelerationStructure rhi_backend_acceleration_structure_create(
               RHIDevice *dev, const RHIAccelerationStructureDesc *desc);
void       rhi_backend_acceleration_structure_destroy(
               RHIDevice *dev, RHIAccelerationStructure structure);
bool       rhi_present_damage_validate(const RHIPresentRect *rects, u32 count,
                                       u32 width, u32 height);
/* Convert top-left drawable damage to the bottom-left convention used by
 * EGL/GLX damage-present extensions. This is allocation-free and supports
 * in-place conversion when the input and output buffers alias. */
bool       rhi_present_damage_to_bottom_left(const RHIPresentRect *rects,
                                             u32 count, u32 width, u32 height,
                                             RHIPresentRect *out, u32 capacity);
/* Validate a bounded RGBA8 screenshot region and destination storage. */
bool       rhi_screenshot_region_validate(u32 x, u32 y, u32 w, u32 h,
                                          u32 width, u32 height,
                                          usize dst_bytes);
/* Resize the default framebuffer/swapchain in physical drawable pixels. */
void       rhi_device_resize(RHIDevice *dev, u32 w, u32 h);
RHIResult  rhi_device_resize_ex(RHIDevice *dev, u32 w, u32 h);

/* ---- Frame lifecycle ---- */
RHICmdBuffer *rhi_frame_begin(RHIDevice *dev);
RHICmdBuffer *rhi_frame_begin_ex(RHIDevice *dev, RHIResult *out_result);
RHICmdBuffer *rhi_frame_acquire_ex(RHIDevice *dev, RHIResult *out_result);
RHICmdBuffer *rhi_frame_begin_damage(RHIDevice *dev,
                                     const RHIPresentRect *rects, u32 count,
                                     bool *out_partial);
void          rhi_frame_end(RHIDevice *dev);
RHIResult     rhi_frame_end_ex(RHIDevice *dev);
RHIResult     rhi_frame_submit_ex(RHIDevice *dev);
void          rhi_present(RHIDevice *dev);
RHIResult     rhi_present_ex(RHIDevice *dev);
bool          rhi_frame_get_damage(const RHIDevice *dev,
                                   RHIPresentRect *rects, u32 capacity,
                                   u32 *out_count);
void          rhi_set_vsync(RHIDevice *dev, bool enabled);
/* R172: In-flight frame slot index (Vulkan 0..1 after fence wait; GL always 0). */
u32           rhi_frame_index(RHIDevice *dev);

/* ---- Resource creation ---- */
/* Pure descriptor validation shared by every backend. */
bool        rhi_buffer_desc_validate(const RHIBufferDesc *desc);
bool        rhi_texture_desc_validate(const RHITextureDesc *desc);
RHIBuffer   rhi_buffer_create(RHIDevice *dev, const RHIBufferDesc *desc);
void        rhi_buffer_destroy(RHIDevice *dev, RHIBuffer buf);
RHIShader   rhi_shader_create(RHIDevice *dev, const char *source, usize len, bool is_fragment);
void        rhi_shader_destroy(RHIDevice *dev, RHIShader shader);
RHIPipeline rhi_pipeline_create(RHIDevice *dev, const RHIPipelineDesc *desc);
void        rhi_pipeline_destroy(RHIDevice *dev, RHIPipeline pipe);
/* Plan E C-TEX-1: the 7-enum RHIFormat matrix is closed. The 6 real formats
 * round-trip native bytes through .data upload + rhi_texture_read_pixels
 * (byte table at the readback entry below; RGBA8 is 4B/px R,G,B,A order);
 * RHI_FORMAT_UNDEFINED is REJECTED here on both backends (shared
 * rhi_texture_desc_validate) — it never silently falls back to another
 * format. Pinned by the texture format-matrix oracle (test_vulkan). */
RHITexture  rhi_texture_create(RHIDevice *dev, const RHITextureDesc *desc);
void        rhi_texture_destroy(RHIDevice *dev, RHITexture tex);
/* R441: 2D texture array (single mip, RGBA8/BGRA8) for the material-indirect
 * single-execute forward path 閳?the only dual-backend bindless substitute
 * (GL here has no ARB_bindless_texture; VK needs zero new features). The
 * shared sampler descriptor layout accepts a 2D_ARRAY view for
 * sampler2DArray without any layout change. */
RHITexture  rhi_texture_array_create(RHIDevice *dev, u32 width, u32 height,
                                     u32 layers, RHIFormat fmt);
/* Upload one full layer (RGBA8, size >= w*h*4 of the array extent). */
void        rhi_texture_array_upload_layer(RHIDevice *dev, RHITexture tex,
                                           u32 layer, const void *rgba8, usize size);
/* R441: size query + synchronous readback of mip 0 閳?used once at bake time
 * to pack material albedos into a texture array (staging on VK, glGetTexImage
 * on GL; not a per-frame API). R631: the size query also accepts cubemap
 * handles (color cubes, and depth cubes on GL where they register as
 * RHI_RES_CUBEMAP) 閳?it reports the face extent; this completes the
 * size-query half of the R610/R624 cube readback contract. Byte semantics
 * follow the texture format on BOTH backends (R587/R593/R601/R602): RGBA8 閳?4B/px RGBA; BGRA8 閳?4B/px BGRA
 * order; RG16F 閳?4B/px f16 pairs; RGBA16F 閳?8B/px f16 quads; R32F 閳?4B/px
 * f32; D32 閳?4B/px f32 depth (R602: the last undefined format joined 閳?every
 * RHIFormat now has defined readback semantics). R608/R609/R610 extended the
 * same D32 semantics to FBO ATTACHMENT depths (offscreen/MRT/shadow-map);
 * R610 also defines the point-shadow depth CUBE: readback yields all six
 * faces face-major (+X,-X,+Y,-Y,+Z,-Z layer order), 4B f32 per texel, so the
 * caller buffer is w*h*4*6. VK: defined once every face has been rendered at
 * least once (unrendered faces keep undefined contents 閳?their layout was
 * never transitioned out of UNDEFINED).
 * R624 defines the COLOR cubemap (rhi_cubemap_create): pass the RHICubemap
 * handle here 閳?readback yields all six faces face-major mip 0 in the
 * format's native bytes (RGBA8 4B/px RGBA; RGBA16F 8B/px f16 quads), so the
 * caller buffer is size*size*bpp*6. VK: defined while the cube is in
 * shader-read state (create and rhi_cubemap_transition_to_read both end
 * there; the copy restores SHADER_READ_ONLY 閳?non-destructive), face
 * contents undefined until written. RGBA16F cube faces upload natively at
 * create (R625: f16 bytes, GL_HALF_FLOAT on GL / 8B staging on VK 閳?
 * pre-R625 they were silently dropped on BOTH backends).
 * Plan E C-TEX-1: this byte table is the readback half of the closed
 * 7-format matrix — every real format round-trips its native bytes on both
 * backends for exact-representable values (RGBA8 included, 4B/px R,G,B,A
 * order); RHI_FORMAT_UNDEFINED has no readback semantics because
 * rhi_texture_create rejects it. */
bool        rhi_texture_get_size(RHIDevice *dev, RHITexture tex, u32 *out_w, u32 *out_h);
bool        rhi_texture_read_pixels(RHIDevice *dev, RHITexture tex, void *dst_rgba8, usize size);
/* Upload RGBA8 pixel data into a single mip level of an existing texture.
 * Used by the mipmap streaming system to push individual levels to the GPU.
 * Plan E C-TEX-2: the uploaded bytes ARE the texels a shader samples after
 * rhi_cmd_bind_texture_mip(tex, ..., level) — the bound single-mip view
 * makes textureLod(..., 0.0) read exactly this level's content on both
 * backends (VK: per-mip VkImageView; GL: single-mip glTextureView). The
 * level extent must equal width>>level / height>>level (floored at 1) and
 * size must cover w*h*4, or the upload is dropped (R417). Pinned by the
 * mip upload oracle (test_vulkan): upload -> bind_texture_mip -> compute
 * sample == uploaded bytes (+-1 UNORM round trip). */
void        rhi_texture_upload_mip(RHIDevice *dev, RHITexture tex, u32 mip_level,
                                   u32 width, u32 height, const void *data, usize size);
/* Plan E C-TEX-3: sampler filter/wrap behavior is identical across
 * backends — NEAREST magnification selects the nearest texel (no blend),
 * CLAMP_TO_EDGE freezes the edge texel for UVs outside [0,1], REPEAT wraps
 * them (edge-extrapolated UVs resolve to different texels per mode). GL
 * maps the min filter to a MIPMAP enum (R194-A) so textureLod honors the
 * requested level. Pinned by the sampler contract oracle (test_vulkan). */
RHISampler  rhi_sampler_create(RHIDevice *dev, const RHISamplerDesc *desc);
void        rhi_sampler_destroy(RHIDevice *dev, RHISampler sampler);

/* ---- Command recording ---- */
void rhi_cmd_begin_render_pass(RHICmdBuffer *cmd);
void rhi_cmd_end_render_pass(RHICmdBuffer *cmd);
void rhi_cmd_bind_pipeline(RHICmdBuffer *cmd, RHIPipeline pipe);
void rhi_cmd_bind_vertex_buffer(RHICmdBuffer *cmd, RHIBuffer buf, usize offset);
/* is_u32=true 閳?UINT32 indices; false 閳?UINT16 (R224-A). */
void rhi_cmd_bind_index_buffer(RHICmdBuffer *cmd, RHIBuffer buf, usize offset, bool is_u32);
/* min_depth/max_depth: Vulkan viewport depth range / GL glDepthRange (R225-A). */
void rhi_cmd_set_viewport(RHICmdBuffer *cmd, f32 x, f32 y, f32 w, f32 h,
                          f32 min_depth, f32 max_depth);
void rhi_cmd_set_scissor(RHICmdBuffer *cmd, i32 x, i32 y, u32 w, u32 h);
void rhi_cmd_set_scissor_top_left(RHICmdBuffer *cmd, u32 x, u32 y, u32 w, u32 h);
/* Set a non-Y-flipped viewport + matching scissor, matching the depth/shadow
 * render-pass convention (top-left origin on VK, native on GL). Used to render
 * cascaded-shadow quadrants into a single shadow-atlas texture. */
void rhi_cmd_set_shadow_viewport(RHICmdBuffer *cmd, u32 x, u32 y, u32 w, u32 h);
void rhi_cmd_draw(RHICmdBuffer *cmd, u32 vertex_count, u32 instance_count);
/* Non-indexed draw with a vertex-buffer-relative first vertex. */
void rhi_cmd_draw_base(RHICmdBuffer *cmd, u32 vertex_count, u32 instance_count,
                       u32 first_vertex);
void rhi_cmd_draw_indexed(RHICmdBuffer *cmd, u32 index_count, u32 instance_count);
/* Like draw_indexed, with base index and vertex offset (mega-buffer / cmd replay). */
void rhi_cmd_draw_indexed_base(RHICmdBuffer *cmd, u32 index_count, u32 instance_count,
                               u32 first_index, i32 vertex_offset);
/* ---- Indirect drawing (GPU-driven pipeline) ---- */
/* Non-indexed DrawIndirect (VkDrawIndirectCommand / DrawArraysIndirect). */
void rhi_cmd_draw_indirect(RHIDevice *dev, RHIBuffer cmd_buf, u32 offset,
                           u32 draw_count, u32 stride);
void rhi_cmd_draw_indexed_indirect(RHIDevice *dev, RHIBuffer cmd_buf, u32 offset,
                                   u32 draw_count, u32 stride);
void rhi_cmd_draw_indexed_indirect_count(RHIDevice *dev, RHIBuffer cmd_buf, u32 cmd_offset,
                                         RHIBuffer count_buf, u32 count_offset,
                                         u32 max_draws, u32 stride);
void rhi_cmd_clear_color(RHICmdBuffer *cmd, f32 r, f32 g, f32 b, f32 a);
void rhi_cmd_clear_color_attachment(RHICmdBuffer *cmd, u32 attachment, f32 r, f32 g, f32 b, f32 a);
void rhi_cmd_bind_texture(RHICmdBuffer *cmd, RHITexture tex, RHISampler sampler, u32 unit);
void rhi_cmd_bind_shadow_texture(RHICmdBuffer *cmd, RHITexture shadow_tex, RHISampler sampler);
void rhi_cmd_bind_uniform_buffer(RHICmdBuffer *cmd, RHIBuffer buf, u32 binding);
void rhi_cmd_set_uniform_mat4(RHICmdBuffer *cmd, i32 location, const f32 *m);
void rhi_cmd_set_uniform_vec3(RHICmdBuffer *cmd, i32 location, f32 x, f32 y, f32 z);
void rhi_cmd_set_uniform_vec2(RHICmdBuffer *cmd, i32 location, f32 x, f32 y);
void rhi_cmd_set_uniform_vec4(RHICmdBuffer *cmd, i32 location, f32 x, f32 y, f32 z, f32 w);
void rhi_cmd_set_uniform_f32(RHICmdBuffer *cmd, i32 location, f32 v);
void rhi_cmd_set_uniform_i32(RHICmdBuffer *cmd, i32 location, i32 v);
/* R444: Push-constant upload, semantics aligned with
 * push-constant range semantics (offset, size): [offset, offset+size) must fit inside the
 * bound pipeline's declared push range (compute 128B / graphics clamped
 * range); an out-of-range write is dropped with a warning instead of being
 * silently truncated at flush. GL has no push-constant equivalent, so this is
 * a documented no-op there 閳?use the per-uniform setters above for
 * GL-visible state. */
void rhi_cmd_push_constants(RHICmdBuffer *cmd, u32 offset, const void *data, u32 size);
/* R444: Shared bounds rule for the contract above, kept pure so it is
 * unit-testable headless and reused by backend validation. */
static inline bool rhi_push_range_fits(u32 offset, u32 size, u32 range_size) {
    return size > 0u && offset <= range_size && size <= range_size - offset;
}
/* R552-B: Bounds rule for the legacy set_uniform_* helpers on VK, where
 * `location` is a byte offset into the push-constant block. The check is
 * against the pipeline's declared push range, not the 256B staging buffer 閳?
 * writes into [declared_range, 256) used to be silently truncated at flush. */
static inline bool rhi_push_helper_range_ok(i32 location, u32 size, u32 range_size) {
    return location >= 0 && rhi_push_range_fits((u32)location, size, range_size);
}
/* R179/R444: Deprecated alias of rhi_cmd_push_constants (location == byte
 * offset). Kept for compatibility; new code should call rhi_cmd_push_constants. */
void rhi_cmd_set_uniform_bytes(RHICmdBuffer *cmd, i32 location, const void *data, u32 size);
/* DEPRECATED（计划 E）：新代码用 rhi_pipeline_bindings_create/resolve。
 * 保留至全部调用点迁移完成（Task 8 grep gate 清零），删除时机另行决定（OpenGL 长期保留，不再随其退役）。 */
i32  rhi_pipeline_get_uniform_location(RHIDevice *dev, RHIPipeline pipe, const char *name);

/* ---- Plan E Task 5: reflection-driven pipeline bindings ---- */
typedef struct RHIPipelineBindings RHIPipelineBindings; /* 不透明 */
/* 每管线一次：后端在 shader/pipeline create 时已缓存反射结果，这里物化为
 * name->slot 表。slot 语义 = 后端绑定槽（VK push 字节偏移 / GL location /
 * 未来 Metal|D3D12 绑定索引），值由 reflection 推导、全后端同源。
 * VK 名字来自 std430 push 反射；反射 fail-closed（宏/非字面量数组长度等）
 * 时 resolve 返回 -1（create 时 LOG_WARN），不伪造槽位。 */
RHIPipelineBindings *rhi_pipeline_bindings_create(RHIDevice *dev, RHIPipeline pipe);
void  rhi_pipeline_bindings_destroy(RHIDevice *dev, RHIPipelineBindings *b);
/* 成员不存在返回 -1（与旧 API 一致）。 */
i32   rhi_pipeline_bindings_resolve(const RHIPipelineBindings *b, const char *name);

/* ---- Framebuffer (depth-only for shadow pass) ---- */
typedef struct {
    RHIFramebuffer fbo;
    RHITexture     depth_tex;
    u32            width;
    u32            height;
} RHIShadowMap;

RHIShadowMap rhi_shadow_map_create(RHIDevice *dev, u32 width, u32 height);
void         rhi_shadow_map_destroy(RHIDevice *dev, RHIShadowMap *sm);
/* R618 contract: binding a shadow map CLEARS its depth to 1.0 on both
 * backends (GL: explicit glClear under a forced depth mask; VK: the render
 * pass depth loadOp with clear value 1.0). There is no load/preserve twin 閳?
 * every bind starts the atlas fresh. This is the same "bind == fresh" half
 * of the R616/R617 MRT/offscreen semantic pair, audited consistent here and
 * pinned by the graphics roundtrip gate's shadow bind-clear phase. */
void         rhi_cmd_bind_shadow_map(RHICmdBuffer *cmd, RHIShadowMap *sm);
void         rhi_cmd_unbind_shadow_map(RHICmdBuffer *cmd, u32 screen_w, u32 screen_h);
void rhi_cmd_clear_depth(RHICmdBuffer *cmd);

/* ---- Cubemap ---- */
typedef struct {
    u32         size;
    /* mip 0 per face. RGBA8: 4B/px bytes. RGBA16F (R625): native f16 quads
     * (8B/px) 閳?the exact byte contract rhi_texture_read_pixels returns for
     * the cube (R624), so upload and readback round-trip byte-exactly. */
    const void *faces[6];
    /* Optional. 0 (RHI_FORMAT_R8G8B8A8_UNORM) keeps the legacy RGBA8 behavior.
     * Set RHI_FORMAT_R16G16B16A16_SFLOAT for HDR env/IBL cubemaps. */
    RHIFormat   format;
    /* Optional. 0 or 1 == single mip. >1 allocates a mip chain (e.g. IBL
     * prefilter).  When >1 and faces[] are provided, only mip 0 is uploaded. */
    u32         mip_levels;
} RHICubemapDesc;

RHICubemap rhi_cubemap_create(RHIDevice *dev, const RHICubemapDesc *desc);
bool       rhi_cubemap_desc_validate(const RHICubemapDesc *desc);
void       rhi_cubemap_destroy(RHIDevice *dev, RHICubemap cm);
/* Transition all faces/mips of a cubemap that was written via compute storage
 * (GENERAL layout) back to a shader-readable layout for sampling.  Performs a
 * device-idle one-time submit; call once after IBL generation completes. */
void       rhi_cubemap_transition_to_read(RHIDevice *dev, RHICubemap cm);

/* Transition a 2D texture written via compute storage (GENERAL layout) back to
 * a shader-readable layout for sampling.  Device-idle one-time submit. */
void       rhi_texture_transition_to_read(RHIDevice *dev, RHITexture tex);
void rhi_cmd_bind_cubemap(RHICmdBuffer *cmd, RHICubemap cm, RHISampler sampler, u32 unit);

/* ---- Depth state ---- */
void rhi_cmd_set_depth_func_less_or_equal(RHICmdBuffer *cmd);
void rhi_cmd_set_depth_func_less(RHICmdBuffer *cmd);
void rhi_cmd_set_depth_mask(RHICmdBuffer *cmd, bool enabled);
void rhi_cmd_set_cull_face(RHICmdBuffer *cmd, bool enabled);

/* ---- Texel buffer ---- */
void rhi_cmd_bind_texel_buffers(RHICmdBuffer *cmd, RHIBuffer buf0, RHIBuffer buf1);
/* Plan E C-BUF contracts (normative; pinned by test_vulkan's BUFFER STAGING
 * CONTRACT and CMD UPDATE BUFFER ORDERING phases on both backends):
 *   C-BUF-1  A buffer created with initial_data reads those bytes back
 *            byte-exactly via rhi_buffer_read — HOST_VISIBLE and
 *            DEVICE_LOCAL(+staging) have the same semantics.
 *   C-BUF-2  rhi_buffer_update_region writes only [offset, offset+size);
 *            every other byte keeps its prior content. offset/size need NO
 *            caller alignment (backends absorb any non-coherent-atom
 *            alignment internally) and are bounds-checked — out-of-range
 *            regions are clamped/rejected, never UB.
 *   C-BUF-3  rhi_cmd_update_buffer is ordered against every LATER dispatch/
 *            draw recorded in the SAME command buffer (R183): the shader
 *            reads the updated bytes.
 *   C-BUF-4  Writes through the pointer returned by rhi_buffer_map become
 *            visible to the device and to rhi_buffer_read after
 *            rhi_buffer_unmap. Maps are read/write; unwritten bytes keep
 *            their content (no invalidate). DEVICE_LOCAL buffers map through
 *            a staging shadow (download on map, upload on unmap). */
void rhi_buffer_update(RHIDevice *dev, RHIBuffer buf, const void *data, usize size);
void rhi_buffer_update_region(RHIDevice *dev, RHIBuffer buf, usize offset, const void *data, usize size);
/* R186: Host readback 閳?works for HOST_VISIBLE and DEVICE_LOCAL (staging). C-BUF-1/2. */
bool rhi_buffer_read(RHIDevice *dev, RHIBuffer buf, void *dst, usize offset, usize size);
/* R171: Recorded GPU clear (recorded GPU buffer fill / glClearBufferSubData). Host
 * memcpy updates are NOT ordered between dispatches in the same Vulkan CB. */
void rhi_cmd_fill_buffer(RHICmdBuffer *cmd, RHIBuffer buf, usize offset, usize size, u32 value);
/* R183: Record a host閳墱PU buffer write into the command buffer (ordered vs
 * later dispatches — C-BUF-3). Prefer over rhi_buffer_update when the same buffer is
 * rewritten multiple times in one CB (e.g. CSM cascade visibility). */
void rhi_cmd_update_buffer(RHICmdBuffer *cmd, RHIBuffer buf, usize offset,
                           const void *data, usize size);

/* ---- Material textures (binds albedo/mr/normal/emissive + shadow in one descriptor set) ---- */
void rhi_cmd_bind_material_textures(RHICmdBuffer *cmd,
    RHITexture albedo, RHITexture mr, RHITexture normal, RHITexture emissive,
    RHITexture shadow, RHITexture ssao, RHISampler sampler);

/* Material + IBL textures: binds material (0-4) + occlusion (R583) + shadow
 * (1) + ssao (14) + brdf_lut/irradiance/prefilter (7-9) + point_shadow_cubes
 * (10-13). R583 occlusion slot: GL unit 15 / VK set 0 binding 9 閳?the only
 * slots free in the G-Buffer pass on each backend (GL 5/6 are vertex-stage
 * texel-buffer units: joints/instances/light data; VK 5 is the ssao/pt-shadow
 * array). They coincide with the deferred LIGHTING pass's emissive slots 閳?
 * a different pass with its own descriptor set, so no conflict. Callers
 * resolve the white 1x1 fallback (no occlusion texture = 1.0 per glTF)
 * before calling. */
void rhi_cmd_bind_material_textures_ibl(RHICmdBuffer *cmd,
    RHITexture albedo, RHITexture mr, RHITexture normal, RHITexture emissive,
    RHITexture occlusion, RHITexture shadow, RHITexture ssao, RHISampler sampler,
    RHITexture brdf_lut, RHICubemap irradiance_map, RHICubemap prefilter_map,
    const RHITexture *point_shadow_cubes, u32 point_shadow_count);

/* R582: one-shot texture bind for the deferred lighting pass. The deferred
 * lighting binding maps have diverged from the forward material layout
 * (G-Buffer targets + shadow + SSAO + IBL + point-shadow cubes + the R582
 * emissive target), so they get a dedicated binder instead of riding
 * forward-arg slots.
 *   VK set 0: 0=albedo_metallic 1=shadow 2=roughness_ao 3=normal 4=depth
 *             5=ssao 6=brdf 7=irradiance 8=prefilter 9=emissive 10-13=cubes
 *   GL units: 0=albedo_metallic 1=normal 2=roughness_ao 3=depth 4=shadow
 *             7=brdf 8=irradiance 9=prefilter 10-13=cubes 14=ssao 15=emissive
 * Handles that are invalid fall back to the albedo view (VK) / skip (GL,
 * matching the existing per-unit bind behavior). */
void rhi_cmd_bind_deferred_gbuf_textures(RHICmdBuffer *cmd,
    RHITexture albedo_metallic, RHITexture roughness_ao, RHITexture normal,
    RHITexture depth, RHITexture emissive, RHITexture shadow, RHITexture ssao,
    RHISampler sampler, RHITexture brdf_lut, RHICubemap irradiance_map,
    RHICubemap prefilter_map, const RHITexture *point_shadow_cubes,
    u32 point_shadow_count, RHISampler cube_sampler);

void rhi_cmd_bind_textures_multi(RHICmdBuffer *cmd,
    RHITexture *textures, int count, RHISampler sampler);

/* ---- Offscreen framebuffer (color + depth) ---- */
typedef struct {
    RHIFramebuffer fb;
    RHITexture     color_tex;
    RHITexture     depth_tex;
    u32            width;
    u32            height;
    u32            sample_count;
} RHIOffscreenFBO;

RHIOffscreenFBO rhi_offscreen_fbo_create(RHIDevice *dev, u32 width, u32 height);
RHIOffscreenFBO rhi_offscreen_fbo_create_fmt(RHIDevice *dev, u32 width, u32 height, RHIFormat color_fmt);
RHIOffscreenFBO rhi_offscreen_fbo_create_desc(RHIDevice *dev, const RHIOffscreenFBODesc *desc);
bool            rhi_offscreen_fbo_desc_validate(const RHICapabilities *caps,
                                                const RHIOffscreenFBODesc *desc);
void            rhi_offscreen_fbo_destroy(RHIDevice *dev, RHIOffscreenFBO *fbo);
/* R617: the bind pair's contract is unified on both backends 閳?
 * bind = fresh target: clears color to {0.05, 0.05, 0.1, 1.0} and depth to
 * 1.0 (VK has always done it via the render-pass loadOp 閳?those exact
 * values are the portable contract; GL joins with explicit clears as of
 * R617 閳?before that GL preserved, which made GL's bind indistinguishable
 * from bind_load).
 * bind_load = resume: preserves all attachment content (R196-A: tonemap/
 * cinematic reuse scene_fbo; a CLEAR bind would wipe depth needed by god
 * rays/upscale). */
void            rhi_offscreen_fbo_bind(RHICmdBuffer *cmd, RHIOffscreenFBO *fbo);
void            rhi_offscreen_fbo_bind_load(RHICmdBuffer *cmd, RHIOffscreenFBO *fbo);
void            rhi_offscreen_fbo_unbind(RHICmdBuffer *cmd, u32 screen_w, u32 screen_h);
/* R619: caller-owned bind clear color. Replaces the RHI-baked default
 * {0.05, 0.05, 0.1, 1.0} for THIS FBO's bind clear (both backends; MSAA
 * variants share the path). Depth clear stays 1.0 and bind_load never
 * clears 閳?only the bind color value is caller-owned. The default is
 * installed at create, so existing callers see zero behavior change. */
void            rhi_offscreen_fbo_set_clear_color(RHIDevice *dev,
                                                  RHIOffscreenFBO *fbo,
                                                  f32 r, f32 g, f32 b, f32 a);

/* ---- MRT (Multiple Render Targets) framebuffer ---- */

typedef struct {
    RHIFramebuffer fb;
    RHITexture     color_tex[RHI_MRT_MAX_ATTACHMENTS];
    RHITexture     depth_tex;
    u32            attachment_count;
    u32            width;
    u32            height;
} RHIMRTFBO;

RHIMRTFBO rhi_mrt_fbo_create(RHIDevice *dev, u32 width, u32 height,
                              const RHIFormat *formats, u32 attachment_count);
bool      rhi_mrt_desc_validate(u32 width, u32 height,
                                const RHIFormat *formats, u32 attachment_count);
void      rhi_mrt_fbo_destroy(RHIDevice *dev, RHIMRTFBO *fbo);
/* R616: the bind pair's contract is unified on both backends 閳?
 * bind = fresh target: clears every color attachment to (0,0,0,0) and depth
 * to 1.0 (VK has always done it via the render-pass loadOp; GL joins with
 * explicit clears as of R616 閳?before that GL preserved, which made GL's
 * bind indistinguishable from bind_load).
 * bind_load = resume: preserves all attachment content. */
void      rhi_mrt_fbo_bind(RHICmdBuffer *cmd, RHIMRTFBO *fbo);
void      rhi_mrt_fbo_bind_load(RHICmdBuffer *cmd, RHIMRTFBO *fbo);
void      rhi_mrt_fbo_unbind(RHICmdBuffer *cmd, u32 screen_w, u32 screen_h);

/* ---- Depth cubemap FBO (point-light shadow maps) ---- */
typedef struct {
    RHIFramebuffer fb;
    RHITexture     depth_tex;   /* cubemap depth texture */
    u32            size;        /* face width == face height */
} RHICubemapDepthFBO;

RHICubemapDepthFBO rhi_cubemap_depth_fbo_create(RHIDevice *dev, u32 size);
void               rhi_cubemap_depth_fbo_destroy(RHIDevice *dev, RHICubemapDepthFBO *fbo);
/* Bind a single cubemap face for rendering (face 0..5 = +X,-X,+Y,-Y,+Z,-Z).
 * R618 contract: binding a face CLEARS that face's depth to 1.0 on both
 * backends (GL: glClear after the face re-attachment; VK: per-face render
 * pass depth loadOp). No load/preserve twin 閳?every face bind starts fresh,
 * matching rhi_cmd_bind_shadow_map. */
void               rhi_cubemap_depth_fbo_bind_face(RHICmdBuffer *cmd, RHICubemapDepthFBO *fbo, u32 face);
void               rhi_cubemap_depth_fbo_unbind(RHICmdBuffer *cmd, u32 screen_w, u32 screen_h);

/* ---- Compute shader ---- */
RHIShader   rhi_shader_create_compute(RHIDevice *dev, const char *source, usize len);
void        rhi_cmd_dispatch(RHICmdBuffer *cmd, u32 x, u32 y, u32 z);
void        rhi_cmd_bind_storage_buffer(RHICmdBuffer *cmd, RHIBuffer buf, u32 binding);
/* Bind one acceleration structure to a compute pipeline's dedicated ray-query
 * descriptor binding. The binding must be declared by the pipeline contract;
 * unsupported backends fail closed. */
void        rhi_cmd_bind_acceleration_structure(
                RHICmdBuffer *cmd, RHIAccelerationStructure structure,
                u32 binding);
void rhi_cmd_memory_barrier(RHICmdBuffer *cmd);
void rhi_cmd_bind_image_texture(RHICmdBuffer *cmd, RHITexture tex, u32 unit, u32 mip_level, bool write_only);
/* Bind a cubemap face's mip level as a storage image for compute write
 * (face 0..5 = +X,-X,+Y,-Y,+Z,-Z). mip 0 is the base level. */
void rhi_cmd_bind_image_cubemap_face(RHICmdBuffer *cmd, RHICubemap cm, u32 face, u32 mip, u32 unit, bool write_only);
/* Bind a cubemap as a sampler for compute read (binding 1 in sampler_mip set). */
void rhi_cmd_bind_cubemap_sampler(RHICmdBuffer *cmd, RHICubemap cm, RHISampler sampler, u32 unit);
void rhi_cmd_bind_texture_mip(RHICmdBuffer *cmd, RHITexture tex, RHISampler sampler, u32 unit, u32 mip_level);
/* Bind a full 2D texture (mip 0) as a sampler for a *compute* pipeline's
 * sampler set. Unlike rhi_cmd_bind_texture (which targets the graphics
 * material set), this targets the compute sampler_mip set and assumes the
 * texture is already in a shader-read layout (no transition barrier). */
void rhi_cmd_bind_texture_compute(RHICmdBuffer *cmd, RHITexture tex, RHISampler sampler, u32 unit);
void rhi_cmd_transition_depth_to_read(RHICmdBuffer *cmd, RHITexture depth_tex);
/* C-BUF-4: read/write mapping. Writes through the pointer are visible to the
 * device and to rhi_buffer_read after rhi_buffer_unmap; unwritten bytes keep
 * their content (no invalidate). DEVICE_LOCAL buffers map through a staging
 * shadow (VK). */
void*       rhi_buffer_map(RHIDevice *dev, RHIBuffer buf);
void        rhi_buffer_unmap(RHIDevice *dev, RHIBuffer buf);
void        rhi_cmd_copy_buffer(RHICmdBuffer *cmd, RHIBuffer src, RHIBuffer dst, usize size);
/* Reads back the framebuffer into `pixels` as RGBA8. The region must be
 * inside the drawable and `pixel_bytes` must be at least w*h*4. The call
 * waits for completion on Vulkan and returns false without touching pixels
 * when validation or backend readback fails.
 * R577: must be called while a swapchain image is acquired 閳?between
 * rhi_frame_begin and rhi_present (in-frame or post-frame_end pre-present).
 * Post-present calls are a Vulkan spec violation (the image is owned by the
 * presentation engine again) and are refused (false + error log). The readback
 * carries the previously presented frame's pixels: rendering recorded into the
 * in-flight frame is not visible to it.
 * Row order: the rect (x, y) is top-left origin and rows are returned
 * top-down on every backend. Vulkan gets this from the swapchain copy path;
 * GL reverses glReadPixels' bottom-up rows to match. Callers must not flip
 * again — a BMP writer that wants bottom-up rows does its own flip. */
bool        rhi_screenshot(RHIDevice *dev, u32 x, u32 y, u32 w, u32 h,
                           u8 *pixels, usize pixel_bytes);

/* Diagnostic probe: waits for full device idle and reports whether the
 * device is still alive. DEVICE_LOST from a faulting earlier submission
 * is reported asynchronously and normally only surfaces at a much later
 * fence wait; test harnesses probe between test groups to attribute the
 * loss to the faulting submission window. GL maps to glFinish()+error
 * check (no equivalent loss concept). Returns false only on a lost/failed
 * device or null arguments. */
bool rhi_device_idle(RHIDevice *dev);
RHIResult rhi_device_idle_ex(RHIDevice *dev);
RHIResult rhi_device_drain_ex(RHIDevice *dev);

/* R578: sticky device-lost latch. Vulkan: set on the first observed
 * VK_ERROR_DEVICE_LOST (or a fence unsignaled for 20 s); all blocking
 * waits then fail fast so callers wind down instead of hanging on a
 * post-TDR device (WDDM resets can leave fences permanently unsignaled).
 * GL: no asynchronous loss concept yet 閳?currently always false. */
bool rhi_device_lost(RHIDevice *dev);

#ifdef ENGINE_RHI_TEST
void rhi_test_set_lifecycle_result(RHIDevice *dev, RHIResult result);
void rhi_test_set_device_status(RHIDevice *dev, RHIDeviceStatus status);
#endif

typedef struct RHIGPUTimer RHIGPUTimer;
RHIGPUTimer *rhi_gpu_timer_create(RHIDevice *dev);
void         rhi_gpu_timer_destroy(RHIDevice *dev, RHIGPUTimer *t);
void         rhi_gpu_timer_begin(RHIGPUTimer *t);
void         rhi_gpu_timer_end(RHIGPUTimer *t);
f64          rhi_gpu_timer_elapsed_ms(RHIGPUTimer *t);

/* 测试专用分配故障注入（恒编译、默认关闭；与 VK 后端的 validation 故障注入
 * 同先例——符号只由 VK 后端定义，调用点必须 #ifdef ENGINE_VULKAN）。开启后
 * vk_allocate_memory 不调用 vkAllocateMemory，直接返回
 * VK_ERROR_OUT_OF_HOST_MEMORY。 */
void rhi_vk_set_alloc_failure_for_test(bool enable);
