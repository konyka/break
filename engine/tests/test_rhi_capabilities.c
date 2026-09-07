#include "test_framework.h"

#include <stdatomic.h>

#include "core/platform_thread.h"
#include "rhi/rhi.h"
#include "rhi/rhi_present_history.h"

extern RHIDevice *rhi_test_device_create(void);
extern void rhi_test_device_destroy(RHIDevice *dev);
extern RHIHandle rhi_test_resource_create(RHIDevice *dev);
extern void rhi_test_resource_destroy(RHIDevice *dev, RHIHandle handle);
extern void *rhi_get_resource(RHIDevice *dev, RHIHandle handle);
extern bool rhi_test_cmd_matches_device(RHIDevice *dev, RHICmdBuffer *cmd,
                                         void *backend);
extern void rhi_test_set_current_device(RHIDevice *dev);
extern void rhi_test_set_backend(RHIDevice *dev, void *backend);
extern void rhi_test_set_dimensions(RHIDevice *dev, u32 width, u32 height);
extern void rhi_test_gl_cache_sync(RHIDevice *dev);
extern RHIDevice *rhi_test_gl_cache_owner(void);
extern bool rhi_test_frame_owner_try_acquire(RHIDevice *dev);
extern bool rhi_test_frame_owner_is_current(const RHIDevice *dev);
extern void rhi_test_frame_owner_release(RHIDevice *dev);
extern bool rhi_test_frame_owner_begin_destroy(RHIDevice *dev);
extern bool rhi_test_device_control_try_acquire(RHIDevice *dev);
extern void rhi_test_device_control_release(RHIDevice *dev);

typedef struct rhi_thread_isolation_context_t {
    RHIDevice *device;
    RHICmdBuffer *command;
    void *backend;
    atomic_bool matched;
} rhi_thread_isolation_context_t;

typedef struct rhi_frame_owner_context_t {
    RHIDevice *device;
    atomic_bool acquired;
} rhi_frame_owner_context_t;

typedef struct rhi_frame_damage_context_t {
    RHIDevice *device;
    RHIPresentRect rect;
    atomic_bool began;
} rhi_frame_damage_context_t;

static PLATFORM_THREAD_RET rhi_thread_must_not_inherit_current_device(
    PLATFORM_THREAD_ARG argument) {
    rhi_thread_isolation_context_t *context =
        (rhi_thread_isolation_context_t *)argument;
    atomic_store_explicit(
        &context->matched,
        rhi_test_cmd_matches_device(context->device, context->command,
                                    context->backend),
        memory_order_release);
#if defined(PLATFORM_THREAD_WIN32)
    return 0;
#else
    return NULL;
#endif
}

static PLATFORM_THREAD_RET rhi_thread_must_not_acquire_frame_owner(
    PLATFORM_THREAD_ARG argument) {
    rhi_frame_owner_context_t *context =
        (rhi_frame_owner_context_t *)argument;
    rhi_test_frame_owner_release(context->device);
    atomic_store_explicit(&context->acquired,
                          rhi_test_frame_owner_try_acquire(context->device),
                          memory_order_release);
    if (atomic_load_explicit(&context->acquired, memory_order_acquire)) {
        rhi_test_frame_owner_release(context->device);
    }
#if defined(PLATFORM_THREAD_WIN32)
    return 0;
#else
    return NULL;
#endif
}

static PLATFORM_THREAD_RET rhi_thread_must_not_begin_damage(
    PLATFORM_THREAD_ARG argument) {
    rhi_frame_damage_context_t *context =
        (rhi_frame_damage_context_t *)argument;
    atomic_store_explicit(
        &context->began,
        rhi_frame_begin_damage(context->device, &context->rect, 1u, NULL) !=
            NULL,
        memory_order_release);
#if defined(PLATFORM_THREAD_WIN32)
    return 0;
#else
    return NULL;
#endif
}

TEST(resource_handles_are_scoped_to_their_device)
{
    RHIDevice *first = rhi_test_device_create();
    RHIDevice *second = rhi_test_device_create();
    RHIHandle first_handle;
    RHIHandle second_handle;
    RHIHandle reused_handle;

    ASSERT_NEQ(first, NULL);
    ASSERT_NEQ(second, NULL);
    first_handle = rhi_test_resource_create(first);
    second_handle = rhi_test_resource_create(second);
    ASSERT_TRUE(rhi_handle_valid(first_handle));
    ASSERT_TRUE(rhi_handle_valid(second_handle));
    ASSERT_EQ(second_handle.index, first_handle.index);
    ASSERT_NEQ(rhi_get_resource(first, first_handle), NULL);
    ASSERT_EQ(rhi_get_resource(second, first_handle), NULL);

    rhi_test_resource_destroy(first, first_handle);
    ASSERT_EQ(rhi_get_resource(first, first_handle), NULL);
    reused_handle = rhi_test_resource_create(first);
    ASSERT_TRUE(rhi_handle_valid(reused_handle));
    ASSERT_EQ(reused_handle.index, first_handle.index);
    ASSERT_NEQ(reused_handle.generation, first_handle.generation);
    ASSERT_EQ(rhi_get_resource(first, reused_handle),
              (void *)first);

    rhi_test_resource_destroy(first, reused_handle);
    rhi_test_resource_destroy(second, second_handle);
    rhi_test_device_destroy(first);
    rhi_test_device_destroy(second);
}

TEST(command_handles_are_scoped_to_their_device)
{
    RHIDevice *first = rhi_test_device_create();
    RHIDevice *second = rhi_test_device_create();
    int backend_token = 0;
    RHICmdBuffer *cmd = (RHICmdBuffer *)&backend_token;

    ASSERT_NEQ(first, NULL);
    ASSERT_NEQ(second, NULL);
    rhi_test_set_backend(first, &backend_token);
    rhi_test_set_current_device(first);
    ASSERT_TRUE(rhi_test_cmd_matches_device(first, cmd, &backend_token));
    ASSERT_FALSE(rhi_test_cmd_matches_device(second, cmd, &backend_token));
    rhi_test_set_current_device(second);
    ASSERT_FALSE(rhi_test_cmd_matches_device(first, cmd, &backend_token));
    rhi_test_set_current_device(NULL);
    rhi_test_device_destroy(first);
    rhi_test_device_destroy(second);
}

TEST(current_device_state_is_thread_local)
{
    RHIDevice *device = rhi_test_device_create();
    int backend_token = 0;
    rhi_thread_isolation_context_t context;
    PlatformThread thread;

    ASSERT_NEQ(device, NULL);
    rhi_test_set_backend(device, &backend_token);
    rhi_test_set_current_device(device);
    context.device = device;
    context.command = (RHICmdBuffer *)&backend_token;
    context.backend = &backend_token;
    atomic_init(&context.matched, true);
    ASSERT_TRUE(platform_thread_create(
        &thread, rhi_thread_must_not_inherit_current_device, &context));
    platform_thread_join(thread);
    ASSERT_FALSE(atomic_load_explicit(&context.matched, memory_order_acquire));
    rhi_test_set_current_device(NULL);
    rhi_test_device_destroy(device);
}

TEST(gl_state_cache_is_invalidated_when_device_changes)
{
    RHIDevice *first = rhi_test_device_create();
    RHIDevice *second = rhi_test_device_create();

    ASSERT_NEQ(first, NULL);
    ASSERT_NEQ(second, NULL);
    rhi_test_gl_cache_sync(first);
    ASSERT_EQ(rhi_test_gl_cache_owner(), first);
    rhi_test_gl_cache_sync(second);
    ASSERT_EQ(rhi_test_gl_cache_owner(), second);
    rhi_test_gl_cache_sync(NULL);
    ASSERT_EQ(rhi_test_gl_cache_owner(), NULL);
    rhi_test_device_destroy(first);
    rhi_test_device_destroy(second);
}

TEST(frame_owner_rejects_cross_thread_reentry)
{
    RHIDevice *device = rhi_test_device_create();
    rhi_frame_owner_context_t context;
    PlatformThread thread;

    ASSERT_NEQ(device, NULL);
    ASSERT_TRUE(rhi_test_frame_owner_try_acquire(device));
    ASSERT_TRUE(rhi_test_frame_owner_is_current(device));
    context.device = device;
    atomic_init(&context.acquired, true);
    ASSERT_TRUE(platform_thread_create(
        &thread, rhi_thread_must_not_acquire_frame_owner, &context));
    platform_thread_join(thread);
    ASSERT_FALSE(atomic_load_explicit(&context.acquired, memory_order_acquire));
    rhi_test_frame_owner_release(device);
    ASSERT_FALSE(rhi_test_frame_owner_is_current(device));
    atomic_store_explicit(&context.acquired, false, memory_order_release);
    ASSERT_TRUE(platform_thread_create(
        &thread, rhi_thread_must_not_acquire_frame_owner, &context));
    platform_thread_join(thread);
    ASSERT_TRUE(atomic_load_explicit(&context.acquired, memory_order_acquire));
    rhi_test_device_destroy(device);
}

TEST(frame_owner_allows_one_active_device_per_thread)
{
    RHIDevice *first = rhi_test_device_create();
    RHIDevice *second = rhi_test_device_create();

    ASSERT_NEQ(first, NULL);
    ASSERT_NEQ(second, NULL);
    ASSERT_TRUE(rhi_test_frame_owner_try_acquire(first));
    ASSERT_TRUE(rhi_test_frame_owner_is_current(first));
    ASSERT_FALSE(rhi_test_frame_owner_try_acquire(second));
    ASSERT_FALSE(rhi_test_frame_owner_is_current(second));
    rhi_test_frame_owner_release(first);
    ASSERT_TRUE(rhi_test_frame_owner_try_acquire(second));
    rhi_test_frame_owner_release(second);
    rhi_test_device_destroy(first);
    rhi_test_device_destroy(second);
}

TEST(frame_begin_damage_does_not_publish_when_owner_is_busy)
{
    RHIDevice *device = rhi_test_device_create();
    RHIPresentRect rect = {1, 2, 10u, 10u};
    RHIPresentRect output = {0};
    u32 output_count = 99u;
    rhi_frame_damage_context_t context;
    PlatformThread thread;

    ASSERT_NEQ(device, NULL);
    rhi_test_set_dimensions(device, 100u, 100u);
    ASSERT_TRUE(rhi_test_frame_owner_try_acquire(device));
    context.device = device;
    context.rect = rect;
    atomic_init(&context.began, true);
    ASSERT_TRUE(platform_thread_create(
        &thread, rhi_thread_must_not_begin_damage, &context));
    platform_thread_join(thread);
    ASSERT_FALSE(atomic_load_explicit(&context.began, memory_order_acquire));
    ASSERT_EQ(rhi_frame_begin_damage(device, &rect, 1u, NULL), NULL);
    ASSERT_TRUE(rhi_frame_get_damage(device, &output, 1u, &output_count));
    ASSERT_EQ(output_count, 0u);
    rhi_test_frame_owner_release(device);
    rhi_test_device_destroy(device);
}

TEST(frame_owner_blocks_device_destroy_until_frame_release)
{
    RHIDevice *device = rhi_test_device_create();

    ASSERT_NEQ(device, NULL);
    ASSERT_TRUE(rhi_test_frame_owner_try_acquire(device));
    ASSERT_FALSE(rhi_test_frame_owner_begin_destroy(device));
    rhi_test_frame_owner_release(device);
    ASSERT_TRUE(rhi_test_frame_owner_begin_destroy(device));
    rhi_test_device_destroy(device);
}

TEST(frame_owner_blocks_device_controls)
{
    RHIDevice *device = rhi_test_device_create();

    ASSERT_NEQ(device, NULL);
    ASSERT_TRUE(rhi_test_device_control_try_acquire(device));
    ASSERT_FALSE(rhi_test_frame_owner_try_acquire(device));
    rhi_test_device_control_release(device);
    ASSERT_TRUE(rhi_test_device_control_try_acquire(device));
    rhi_test_device_control_release(device);
    ASSERT_TRUE(rhi_test_frame_owner_try_acquire(device));
    ASSERT_FALSE(rhi_test_device_control_try_acquire(device));
    rhi_test_frame_owner_release(device);
    ASSERT_TRUE(rhi_test_device_control_try_acquire(device));
    rhi_test_device_control_release(device);
    rhi_test_device_destroy(device);
}

TEST(sample_count_bits_are_portable_and_bounded)
{
    ASSERT_EQ(rhi_sample_count_bit(0u), 0u);
    ASSERT_EQ(rhi_sample_count_bit(3u), 0u);
    ASSERT_EQ(rhi_sample_count_bit(1u), 1u);
    ASSERT_EQ(rhi_sample_count_bit(2u), 2u);
    ASSERT_EQ(rhi_sample_count_bit(4u), 4u);
    ASSERT_EQ(rhi_sample_count_bit(64u), 64u);
}

TEST(capability_query_rejects_invalid_arguments)
{
    RHICapabilities caps;
    ASSERT_FALSE(rhi_device_get_capabilities(NULL, NULL));
    ASSERT_FALSE(rhi_device_get_capabilities(NULL, &caps));
}

TEST(frame_lifecycle_rejects_null_device)
{
    ASSERT_EQ(rhi_frame_begin(NULL), NULL);
    rhi_frame_end(NULL);
    rhi_present(NULL);
    ASSERT_EQ(rhi_frame_index(NULL), 0u);
}

TEST(device_controls_reject_null_device)
{
    rhi_device_resize(NULL, 640u, 480u);
    rhi_set_vsync(NULL, true);
    ASSERT_EQ(rhi_pipeline_get_uniform_location(NULL, RHI_HANDLE_NULL, NULL), -1);
    ASSERT_EQ(rhi_pipeline_get_uniform_location(NULL, RHI_HANDLE_NULL, "u_model"), -1);
    ASSERT_EQ(rhi_gpu_timer_create(NULL), NULL);
}

TEST(device_resize_rejects_zero_dimensions)
{
    rhi_device_resize(NULL, 0u, 480u);
    rhi_device_resize(NULL, 640u, 0u);
}

TEST(command_entrypoints_are_safe_without_current_device)
{
    RHIOffscreenFBO offscreen = {0};
    RHIMRTFBO mrt = {0};

    rhi_cmd_begin_render_pass(NULL);
    rhi_cmd_end_render_pass(NULL);
    rhi_cmd_bind_pipeline(NULL, RHI_HANDLE_NULL);
    rhi_cmd_bind_vertex_buffer(NULL, RHI_HANDLE_NULL, 0u);
    rhi_cmd_bind_index_buffer(NULL, RHI_HANDLE_NULL, 0u, true);
    rhi_cmd_set_viewport(NULL, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f);
    rhi_cmd_set_scissor(NULL, 0, 0, 1u, 1u);
    rhi_cmd_set_scissor_top_left(NULL, 0u, 0u, 1u, 1u);
    rhi_cmd_set_shadow_viewport(NULL, 0u, 0u, 1u, 1u);
    rhi_cmd_draw(NULL, 1u, 1u);
    rhi_cmd_draw_base(NULL, 1u, 1u, 0u);
    rhi_cmd_draw_indexed(NULL, 1u, 1u);
    rhi_cmd_draw_indexed_base(NULL, 1u, 1u, 0u, 0);
    rhi_cmd_draw_indirect(NULL, RHI_HANDLE_NULL, 0u, 1u, 0u);
    rhi_cmd_draw_indexed_indirect(NULL, RHI_HANDLE_NULL, 0u, 1u, 0u);
    rhi_cmd_draw_indexed_indirect_count(NULL, RHI_HANDLE_NULL, 0u,
                                        RHI_HANDLE_NULL, 0u, 1u, 0u);
    rhi_cmd_clear_color(NULL, 0.0f, 0.0f, 0.0f, 1.0f);
    rhi_cmd_clear_color_attachment(NULL, 0u, 0.0f, 0.0f, 0.0f, 1.0f);
    rhi_cmd_bind_texture(NULL, RHI_HANDLE_NULL, RHI_HANDLE_NULL, 0u);
    rhi_cmd_bind_texture(NULL, RHI_HANDLE_NULL, RHI_HANDLE_NULL,
                         RHI_MAX_TEXTURE_UNITS);
    rhi_cmd_bind_shadow_texture(NULL, RHI_HANDLE_NULL, RHI_HANDLE_NULL);
    rhi_cmd_bind_cubemap(NULL, RHI_HANDLE_NULL, RHI_HANDLE_NULL, 0u);
    rhi_cmd_bind_cubemap(NULL, RHI_HANDLE_NULL, RHI_HANDLE_NULL,
                         RHI_MAX_TEXTURE_UNITS);
    rhi_cmd_bind_cubemap_sampler(NULL, RHI_HANDLE_NULL, RHI_HANDLE_NULL, 0u);
    rhi_cmd_bind_textures_multi(NULL, NULL, 1, RHI_HANDLE_NULL);
    rhi_cmd_bind_textures_multi(NULL, NULL, 0, RHI_HANDLE_NULL);
    rhi_cmd_bind_uniform_buffer(NULL, RHI_HANDLE_NULL, 0u);
    rhi_cmd_set_uniform_mat4(NULL, 0, NULL);
    rhi_cmd_set_uniform_bytes(NULL, 0, NULL, 1u);
    rhi_cmd_set_depth_func_less_or_equal(NULL);
    rhi_cmd_set_depth_func_less(NULL);
    rhi_cmd_set_depth_mask(NULL, true);
    rhi_cmd_set_cull_face(NULL, true);
    rhi_cmd_bind_shadow_map(NULL, NULL);
    rhi_cmd_unbind_shadow_map(NULL, 1u, 1u);
    rhi_cmd_clear_depth(NULL);
    rhi_cmd_dispatch(NULL, 1u, 1u, 1u);
    rhi_cmd_bind_storage_buffer(NULL, RHI_HANDLE_NULL, 0u);
    rhi_cmd_memory_barrier(NULL);
    rhi_cmd_bind_image_texture(NULL, RHI_HANDLE_NULL, 0u, 0u, true);
    rhi_cmd_bind_image_cubemap_face(NULL, RHI_HANDLE_NULL, 0u, 0u, 0u, true);
    rhi_cmd_bind_texture_mip(NULL, RHI_HANDLE_NULL, RHI_HANDLE_NULL, 0u, 0u);
    rhi_cmd_bind_texture_compute(NULL, RHI_HANDLE_NULL, RHI_HANDLE_NULL, 0u);
    rhi_cmd_transition_depth_to_read(NULL, RHI_HANDLE_NULL);
    rhi_cubemap_transition_to_read(NULL, RHI_HANDLE_NULL);
    rhi_texture_transition_to_read(NULL, RHI_HANDLE_NULL);
    rhi_offscreen_fbo_bind(NULL, &offscreen);
    rhi_offscreen_fbo_bind_load(NULL, &offscreen);
    rhi_offscreen_fbo_unbind(NULL, 1u, 1u);
    rhi_mrt_fbo_bind(NULL, &mrt);
    rhi_mrt_fbo_bind_load(NULL, &mrt);
    rhi_mrt_fbo_unbind(NULL, 1u, 1u);
}

TEST(device_creation_rejects_invalid_backend_dimensions_and_handles)
{
    ASSERT_EQ(rhi_device_create((RHIBackend)99, NULL, NULL, 640u, 480u), NULL);
    ASSERT_EQ(rhi_device_create(RHI_BACKEND_OPENGL, NULL, NULL, 0u, 480u), NULL);
    ASSERT_EQ(rhi_device_create(RHI_BACKEND_OPENGL, NULL, NULL,
                                RHI_MAX_DRAWABLE_DIMENSION + 1u, 480u), NULL);
    ASSERT_EQ(rhi_device_create(RHI_BACKEND_OPENGL, NULL, NULL, 640u, 480u), NULL);
}

TEST(resource_api_rejects_null_and_malformed_inputs)
{
    RHIBufferDesc buffer_desc = {0};
    RHITextureDesc texture_desc = {0};
    RHIPipelineDesc pipeline_desc = {0};
    RHISamplerDesc sampler_desc = {0};

    ASSERT_FALSE(rhi_handle_valid(rhi_buffer_create(NULL, NULL)));
    ASSERT_FALSE(rhi_handle_valid(rhi_buffer_create(NULL, &buffer_desc)));
    ASSERT_FALSE(rhi_handle_valid(rhi_shader_create(NULL, NULL, 0u, false)));
    ASSERT_FALSE(rhi_handle_valid(rhi_shader_create_compute(NULL, NULL, 0u)));
    ASSERT_FALSE(rhi_handle_valid(rhi_pipeline_create(NULL, NULL)));
    ASSERT_FALSE(rhi_handle_valid(rhi_pipeline_create(NULL, &pipeline_desc)));
    ASSERT_FALSE(rhi_handle_valid(rhi_texture_create(NULL, NULL)));
    ASSERT_FALSE(rhi_handle_valid(rhi_texture_create(NULL, &texture_desc)));
    ASSERT_FALSE(rhi_handle_valid(rhi_sampler_create(NULL, NULL)));
    ASSERT_FALSE(rhi_handle_valid(rhi_sampler_create(NULL, &sampler_desc)));
    ASSERT_FALSE(rhi_handle_valid(rhi_texture_array_create(NULL, 0u, 1u, 1u,
                                                           RHI_FORMAT_R8G8B8A8_UNORM)));

    rhi_buffer_destroy(NULL, RHI_HANDLE_NULL);
    rhi_shader_destroy(NULL, RHI_HANDLE_NULL);
    rhi_pipeline_destroy(NULL, RHI_HANDLE_NULL);
    rhi_texture_destroy(NULL, RHI_HANDLE_NULL);
    rhi_sampler_destroy(NULL, RHI_HANDLE_NULL);
}

TEST(resource_descriptors_reject_zero_and_unsupported_values)
{
    RHIBufferDesc buffer_desc = {
        .usage = RHI_BUFFER_USAGE_VERTEX,
        .size = 0u,
        .initial_data = NULL,
    };
    RHITextureDesc texture_desc = {
        .width = 0u,
        .height = 1u,
        .format = RHI_FORMAT_R8G8B8A8_UNORM,
        .mip_levels = 1u,
        .data = NULL,
    };

    ASSERT_FALSE(rhi_handle_valid(rhi_buffer_create(NULL, &buffer_desc)));
    buffer_desc.size = 1u;
    buffer_desc.usage = 0;
    ASSERT_FALSE(rhi_handle_valid(rhi_buffer_create(NULL, &buffer_desc)));
    ASSERT_FALSE(rhi_handle_valid(rhi_texture_create(NULL, &texture_desc)));
    texture_desc.width = 1u;
    texture_desc.format = RHI_FORMAT_UNDEFINED;
    ASSERT_FALSE(rhi_handle_valid(rhi_texture_create(NULL, &texture_desc)));
}

TEST(resource_descriptor_validation_is_bounded)
{
    RHIBufferDesc buffer_desc = {
        .usage = RHI_BUFFER_USAGE_VERTEX,
        .size = 1u,
        .initial_data = NULL,
    };
    RHITextureDesc texture_desc = {
        .width = 16384u,
        .height = 16384u,
        .format = RHI_FORMAT_R8G8B8A8_UNORM,
        .mip_levels = 15u,
        .data = NULL,
    };

    ASSERT_TRUE(rhi_buffer_desc_validate(&buffer_desc));
    buffer_desc.usage = (RHIBufferUsage)(RHI_BUFFER_USAGE_VERTEX | (1u << 15));
    ASSERT_FALSE(rhi_buffer_desc_validate(&buffer_desc));
    ASSERT_TRUE(rhi_texture_desc_validate(&texture_desc));
    texture_desc.mip_levels = 16u;
    ASSERT_FALSE(rhi_texture_desc_validate(&texture_desc));
    texture_desc.mip_levels = 1u;
    texture_desc.width = RHI_MAX_DRAWABLE_DIMENSION + 1u;
    ASSERT_FALSE(rhi_texture_desc_validate(&texture_desc));
}

TEST(secondary_resource_creation_rejects_invalid_inputs)
{
    RHICubemapDesc cubemap = {0};

    ASSERT_FALSE(rhi_handle_valid(rhi_cubemap_create(NULL, NULL)));
    ASSERT_FALSE(rhi_handle_valid(rhi_cubemap_create(NULL, &cubemap)));
    ASSERT_EQ(rhi_shadow_map_create(NULL, 1u, 1u).fbo.generation, 0u);
    ASSERT_EQ(rhi_shadow_map_create(NULL, 0u, 1u).fbo.generation, 0u);
    ASSERT_EQ(rhi_cubemap_depth_fbo_create(NULL, 1u).fb.generation, 0u);
    ASSERT_EQ(rhi_cubemap_depth_fbo_create(NULL, 0u).fb.generation, 0u);

    cubemap.size = 16384u;
    cubemap.format = RHI_FORMAT_R8G8B8A8_UNORM;
    cubemap.mip_levels = 15u;
    ASSERT_TRUE(rhi_cubemap_desc_validate(&cubemap));
    cubemap.mip_levels = 16u;
    ASSERT_FALSE(rhi_cubemap_desc_validate(&cubemap));
}

TEST(framebuffer_descriptors_reject_invalid_inputs)
{
    const RHIFormat formats[2] = {
        RHI_FORMAT_R8G8B8A8_UNORM,
        RHI_FORMAT_R16G16_SFLOAT,
    };

    ASSERT_FALSE(rhi_mrt_desc_validate(0u, 1u, formats, 1u));
    ASSERT_FALSE(rhi_mrt_desc_validate(1u, 1u, NULL, 1u));
    ASSERT_FALSE(rhi_mrt_desc_validate(1u, 1u, formats,
                                       RHI_MRT_MAX_ATTACHMENTS + 1u));
    ASSERT_TRUE(rhi_mrt_desc_validate(1u, 1u, formats, 2u));
    ASSERT_FALSE(rhi_mrt_desc_validate(RHI_MAX_DRAWABLE_DIMENSION + 1u,
                                       1u, formats, 1u));
    {
        RHIFormat invalid = RHI_FORMAT_D32_FLOAT;
        ASSERT_FALSE(rhi_mrt_desc_validate(1u, 1u, &invalid, 1u));
    }
}

TEST(offscreen_descriptor_requires_safe_supported_values)
{
    RHICapabilities caps = {0};
    caps.color_sample_counts = rhi_sample_count_bit(1u) |
                               rhi_sample_count_bit(2u) |
                               rhi_sample_count_bit(4u);
    caps.depth_sample_counts = rhi_sample_count_bit(1u) |
                               rhi_sample_count_bit(2u) |
                               rhi_sample_count_bit(4u);
    caps.color_resolve_supported = true;
    caps.depth_resolve_supported = true;

    RHIOffscreenFBODesc desc = {64u, 64u, RHI_FORMAT_R8G8B8A8_UNORM, 2u};
    ASSERT_TRUE(rhi_offscreen_fbo_desc_validate(&caps, &desc));
    desc.width = 0u;
    ASSERT_FALSE(rhi_offscreen_fbo_desc_validate(&caps, &desc));
    desc.width = 64u;
    desc.sample_count = 3u;
    ASSERT_FALSE(rhi_offscreen_fbo_desc_validate(&caps, &desc));
    desc.sample_count = 4u;
    caps.depth_resolve_supported = false;
    ASSERT_FALSE(rhi_offscreen_fbo_desc_validate(&caps, &desc));
    caps.depth_resolve_supported = true;
    caps.depth_sample_counts = rhi_sample_count_bit(1u) | rhi_sample_count_bit(2u);
    ASSERT_FALSE(rhi_offscreen_fbo_desc_validate(&caps, &desc));
}

TEST(offscreen_descriptor_defaults_to_single_sample)
{
    RHICapabilities caps = {0};
    caps.color_sample_counts = rhi_sample_count_bit(1u);
    caps.depth_sample_counts = rhi_sample_count_bit(1u);
    RHIOffscreenFBODesc desc = {1u, 1u, RHI_FORMAT_R8G8B8A8_UNORM, 0u};
    ASSERT_TRUE(rhi_offscreen_fbo_desc_validate(&caps, &desc));
    ASSERT_EQ(desc.sample_count, 0u);
}

TEST(present_damage_rects_require_bounded_nonempty_regions)
{
    RHIPresentRect rect = {0, 0, 10u, 10u};

    ASSERT_TRUE(rhi_present_damage_validate(&rect, 1u, 100u, 100u));
    ASSERT_TRUE(rhi_present_damage_validate(NULL, 0u, 100u, 100u));
    ASSERT_FALSE(rhi_present_damage_validate(NULL, 1u, 100u, 100u));
    ASSERT_FALSE(rhi_present_damage_validate(&rect, 1u, 0u, 100u));
    ASSERT_TRUE(rhi_present_damage_validate(&rect, 1u, 100u, 100u));

    rect.x = -1;
    ASSERT_FALSE(rhi_present_damage_validate(&rect, 1u, 100u, 100u));
    rect.x = 95;
    rect.w = 10u;
    ASSERT_FALSE(rhi_present_damage_validate(&rect, 1u, 100u, 100u));
    rect.x = 0;
    rect.w = 0u;
    ASSERT_FALSE(rhi_present_damage_validate(&rect, 1u, 100u, 100u));
}

TEST(present_damage_rects_have_a_fixed_upper_bound)
{
    RHIPresentRect rects[RHI_MAX_PRESENT_DAMAGE_RECTS + 1u] = {{0, 0, 1u, 1u}};
    u32 i;

    for (i = 0u; i < RHI_MAX_PRESENT_DAMAGE_RECTS + 1u; ++i) {
        rects[i] = (RHIPresentRect){(i32)(i % 10u), (i32)(i / 10u), 1u, 1u};
    }

    ASSERT_TRUE(rhi_present_damage_validate(rects, RHI_MAX_PRESENT_DAMAGE_RECTS,
                                             100u, 100u));
    ASSERT_FALSE(rhi_present_damage_validate(rects,
                                              RHI_MAX_PRESENT_DAMAGE_RECTS + 1u,
                                              100u, 100u));
}

TEST(screenshot_region_requires_bounded_rgba8_storage)
{
    ASSERT_TRUE(rhi_screenshot_region_validate(2u, 3u, 4u, 5u,
                                                16u, 16u, 80u));
    ASSERT_TRUE(rhi_screenshot_region_validate(2u, 3u, 4u, 5u,
                                                16u, 16u, 81u));
    ASSERT_FALSE(rhi_screenshot_region_validate(2u, 3u, 4u, 5u,
                                                 16u, 16u, 79u));
    ASSERT_FALSE(rhi_screenshot_region_validate(16u, 0u, 1u, 1u,
                                                 16u, 16u, 4u));
    ASSERT_FALSE(rhi_screenshot_region_validate(0u, 0u, 0u, 1u,
                                                 16u, 16u, 0u));
    ASSERT_FALSE(rhi_screenshot_region_validate(0u, 15u, 2u, 2u,
                                                 16u, 16u, 16u));
    ASSERT_FALSE(rhi_screenshot_region_validate(0u, 0u, 8192u, 8192u,
                                                 8192u, 8192u,
                                                 (usize)RHI_MAX_SCREENSHOT_BYTES));
}

TEST(screenshot_region_rejects_size_overflow)
{
    ASSERT_FALSE(rhi_screenshot_region_validate(UINT32_MAX, UINT32_MAX,
                                                 UINT32_MAX, UINT32_MAX,
                                                 UINT32_MAX, UINT32_MAX,
                                                 SIZE_MAX));
}

TEST(present_damage_converts_top_left_to_bottom_left)
{
    RHIPresentRect input[2] = {{10, 20, 30u, 40u}, {0, 0, 5u, 6u}};
    RHIPresentRect output[2] = {{0}};

    ASSERT_TRUE(rhi_present_damage_to_bottom_left(input, 2u, 100u, 100u,
                                                  output, 2u));
    ASSERT_EQ(output[0].x, 10);
    ASSERT_EQ(output[0].y, 40);
    ASSERT_EQ(output[0].w, 30u);
    ASSERT_EQ(output[0].h, 40u);
    ASSERT_EQ(output[1].y, 94);
}

TEST(present_damage_conversion_supports_in_place_and_rejects_bad_capacity)
{
    RHIPresentRect damage = {2, 3, 4u, 5u};

    ASSERT_TRUE(rhi_present_damage_to_bottom_left(&damage, 1u, 20u, 20u,
                                                  &damage, 1u));
    ASSERT_EQ(damage.y, 12);
    ASSERT_FALSE(rhi_present_damage_to_bottom_left(&damage, 1u, 20u, 20u,
                                                   NULL, 0u));
    ASSERT_FALSE(rhi_present_damage_to_bottom_left(
        &(RHIPresentRect){19, 0, 2u, 1u}, 1u, 20u, 20u, &damage, 1u));
}

TEST(present_history_forces_full_on_first_image_use)
{
    RHIPresentHistory history;
    RHIPresentRect current = {10, 20, 30u, 40u};
    RHIPresentRect output[RHI_MAX_PRESENT_DAMAGE_RECTS];
    u32 output_count = 0u;
    bool full = false;

    ASSERT_TRUE(rhi_present_history_init(&history, 2u, 100u, 100u));
    ASSERT_TRUE(rhi_present_history_prepare(&history, 0u, &current, 1u,
                                             output, RHI_MAX_PRESENT_DAMAGE_RECTS,
                                             &output_count, &full));
    ASSERT_TRUE(full);
    ASSERT_EQ(output_count, 1u);
    ASSERT_EQ(output[0].w, 100u);
    ASSERT_EQ(output[0].h, 100u);
}

TEST(present_history_merges_damage_since_image_was_used)
{
    RHIPresentHistory history;
    RHIPresentRect first = {0, 0, 10u, 10u};
    RHIPresentRect second = {80, 80, 10u, 10u};
    RHIPresentRect current = {40, 40, 10u, 10u};
    RHIPresentRect output[RHI_MAX_PRESENT_DAMAGE_RECTS];
    u32 output_count = 0u;
    bool full = false;

    ASSERT_TRUE(rhi_present_history_init(&history, 2u, 100u, 100u));
    ASSERT_TRUE(rhi_present_history_commit(&history, 0u, &first, 1u));
    ASSERT_TRUE(rhi_present_history_prepare(&history, 1u, &second, 1u,
                                             output, RHI_MAX_PRESENT_DAMAGE_RECTS,
                                             &output_count, &full));
    ASSERT_TRUE(full);
    ASSERT_TRUE(rhi_present_history_commit(&history, 1u, &second, 1u));
    ASSERT_TRUE(rhi_present_history_prepare(&history, 0u, &current, 1u,
                                             output, RHI_MAX_PRESENT_DAMAGE_RECTS,
                                             &output_count, &full));
    ASSERT_FALSE(full);
    ASSERT_EQ(output_count, 2u);
    ASSERT_EQ(output[0].x, 80);
    ASSERT_EQ(output[1].x, 40);
}

TEST(present_history_reset_invalidates_every_swapchain_image)
{
    RHIPresentHistory history;
    RHIPresentRect damage = {1, 2, 3u, 4u};
    RHIPresentRect output[RHI_MAX_PRESENT_DAMAGE_RECTS];
    u32 output_count = 0u;
    bool full = false;

    ASSERT_TRUE(rhi_present_history_init(&history, 2u, 20u, 20u));
    ASSERT_TRUE(rhi_present_history_commit(&history, 0u, &damage, 1u));
    ASSERT_TRUE(rhi_present_history_reset(&history));
    ASSERT_TRUE(rhi_present_history_prepare(&history, 0u, &damage, 1u,
                                             output, RHI_MAX_PRESENT_DAMAGE_RECTS,
                                             &output_count, &full));
    ASSERT_TRUE(full);
    ASSERT_TRUE(rhi_present_history_prepare(&history, 1u, &damage, 1u,
                                             output, RHI_MAX_PRESENT_DAMAGE_RECTS,
                                             &output_count, &full));
    ASSERT_TRUE(full);
}

TEST(present_history_aborts_to_safe_full_frame)
{
    RHIPresentHistory history;
    RHIPresentRect damage = {1, 2, 3u, 4u};
    RHIPresentRect output[RHI_MAX_PRESENT_DAMAGE_RECTS];
    u32 output_count = 0u;
    bool full = false;

    ASSERT_TRUE(rhi_present_history_init(&history, 1u, 20u, 20u));
    ASSERT_TRUE(rhi_present_history_commit(&history, 0u, &damage, 1u));
    rhi_present_history_abort(&history);
    ASSERT_TRUE(rhi_present_history_prepare(&history, 0u, &damage, 1u,
                                             output, RHI_MAX_PRESENT_DAMAGE_RECTS,
                                             &output_count, &full));
    ASSERT_TRUE(full);
}

TEST(present_history_rejects_invalid_damage_without_state_change)
{
    RHIPresentHistory history;
    RHIPresentRect valid = {1, 2, 3u, 4u};
    RHIPresentRect invalid = {-1, 2, 3u, 4u};

    ASSERT_TRUE(rhi_present_history_init(&history, 1u, 20u, 20u));
    ASSERT_TRUE(rhi_present_history_commit(&history, 0u, &valid, 1u));
    ASSERT_FALSE(rhi_present_history_commit(&history, 0u, &invalid, 1u));
    ASSERT_EQ(rhi_present_history_generation(&history), 1u);
    ASSERT_TRUE(rhi_present_history_image_generation(&history, 0u) == 1u);
}

TEST(present_history_overflow_invalidates_other_images)
{
    RHIPresentHistory history;
    RHIPresentRect damage = {1, 2, 3u, 4u};
    RHIPresentRect output[RHI_MAX_PRESENT_DAMAGE_RECTS];
    u32 output_count = 0u;
    bool full = false;
    u32 i;

    ASSERT_TRUE(rhi_present_history_init(&history, 2u, 20u, 20u));
    ASSERT_TRUE(rhi_present_history_commit(&history, 0u, &damage, 1u));
    for (i = 1u; i < RHI_PRESENT_HISTORY_CAPACITY; ++i) {
        ASSERT_TRUE(rhi_present_history_commit(&history, 1u, &damage, 1u));
    }
    ASSERT_TRUE(rhi_present_history_prepare(&history, 0u, &damage, 1u,
                                             output, RHI_MAX_PRESENT_DAMAGE_RECTS,
                                             &output_count, &full));
    ASSERT_TRUE(full);
    ASSERT_EQ(rhi_present_history_generation(&history),
              RHI_PRESENT_HISTORY_CAPACITY);
    ASSERT_TRUE(rhi_present_history_commit(&history, 0u, &damage, 1u));
    ASSERT_TRUE(rhi_present_history_prepare(&history, 1u, &damage, 1u,
                                             output, RHI_MAX_PRESENT_DAMAGE_RECTS,
                                             &output_count, &full));
    ASSERT_TRUE(full);
}

TEST(present_damage_history_requires_full_for_unknown_age)
{
    RHIPresentDamageHistory history;
    RHIPresentRect current = {2, 3, 4u, 5u};
    RHIPresentRect output[RHI_MAX_PRESENT_DAMAGE_RECTS];
    u32 output_count = 0u;
    bool full = false;

    ASSERT_TRUE(rhi_present_damage_history_init(&history, 100u, 80u));
    ASSERT_TRUE(rhi_present_damage_history_prepare_age(
        &history, 0u, &current, 1u, output, RHI_MAX_PRESENT_DAMAGE_RECTS,
        &output_count, &full));
    ASSERT_TRUE(full);
    ASSERT_EQ(output_count, 1u);
    ASSERT_EQ(output[0].w, 100u);
    ASSERT_EQ(output[0].h, 80u);
}

TEST(present_damage_history_requires_history_for_age_one)
{
    RHIPresentDamageHistory history;
    RHIPresentRect current = {2, 3, 4u, 5u};
    RHIPresentRect output[RHI_MAX_PRESENT_DAMAGE_RECTS];
    u32 output_count = 0u;
    bool full = false;

    ASSERT_TRUE(rhi_present_damage_history_init(&history, 100u, 80u));
    ASSERT_TRUE(rhi_present_damage_history_prepare_age(
        &history, 1u, &current, 1u, output, RHI_MAX_PRESENT_DAMAGE_RECTS,
        &output_count, &full));
    ASSERT_TRUE(full);
    ASSERT_EQ(output_count, 1u);
}

TEST(present_damage_history_merges_age_without_reusing_old_damage)
{
    RHIPresentDamageHistory history;
    RHIPresentRect first = {1, 2, 3u, 4u};
    RHIPresentRect second = {20, 21, 5u, 6u};
    RHIPresentRect current = {40, 41, 7u, 8u};
    RHIPresentRect output[RHI_MAX_PRESENT_DAMAGE_RECTS];
    u32 output_count = 0u;
    bool full = false;

    ASSERT_TRUE(rhi_present_damage_history_init(&history, 100u, 100u));
    ASSERT_TRUE(rhi_present_damage_history_commit(&history, &first, 1u));
    ASSERT_TRUE(rhi_present_damage_history_commit(&history, &second, 1u));
    ASSERT_TRUE(rhi_present_damage_history_prepare_age(
        &history, 2u, &current, 1u, output, RHI_MAX_PRESENT_DAMAGE_RECTS,
        &output_count, &full));
    ASSERT_FALSE(full);
    ASSERT_EQ(output_count, 2u);
    ASSERT_EQ(output[0].x, 20);
    ASSERT_EQ(output[1].x, 40);
}

TEST(present_damage_history_rejects_age_gap_and_preserves_state)
{
    RHIPresentDamageHistory history;
    RHIPresentRect damage = {1, 2, 3u, 4u};
    RHIPresentRect output[RHI_MAX_PRESENT_DAMAGE_RECTS];
    u32 output_count = 0u;
    bool full = false;

    ASSERT_TRUE(rhi_present_damage_history_init(&history, 20u, 20u));
    ASSERT_TRUE(rhi_present_damage_history_commit(&history, &damage, 1u));
    ASSERT_FALSE(rhi_present_damage_history_prepare_age(
        &history, 0u, &(RHIPresentRect){-1, 0, 1u, 1u}, 1u, output,
        RHI_MAX_PRESENT_DAMAGE_RECTS, &output_count, &full));
    ASSERT_TRUE(rhi_present_damage_history_prepare_age(
        &history, 3u, &damage, 1u, output, RHI_MAX_PRESENT_DAMAGE_RECTS,
        &output_count, &full));
    ASSERT_TRUE(full);
    ASSERT_EQ(history.entry_count, 1u);
}

TEST(present_damage_history_overflow_forces_full)
{
    RHIPresentDamageHistory history;
    RHIPresentRect damage = {0, 0, 1u, 1u};
    RHIPresentRect output[RHI_MAX_PRESENT_DAMAGE_RECTS];
    u32 output_count = 0u;
    bool full = false;
    u32 i;

    ASSERT_TRUE(rhi_present_damage_history_init(&history, 20u, 20u));
    for (i = 0u; i < RHI_PRESENT_DAMAGE_HISTORY_CAPACITY; ++i) {
        ASSERT_TRUE(rhi_present_damage_history_commit(&history, &damage, 1u));
    }
    ASSERT_TRUE(rhi_present_damage_history_prepare_age(
        &history, RHI_PRESENT_DAMAGE_HISTORY_CAPACITY + 1u, &damage, 1u,
        output, RHI_MAX_PRESENT_DAMAGE_RECTS, &output_count, &full));
    ASSERT_TRUE(full);
    ASSERT_EQ(output_count, 1u);
}

TEST_MAIN_BEGIN()
    RUN_TEST(resource_handles_are_scoped_to_their_device);
    RUN_TEST(command_handles_are_scoped_to_their_device);
    RUN_TEST(current_device_state_is_thread_local);
    RUN_TEST(gl_state_cache_is_invalidated_when_device_changes);
    RUN_TEST(frame_owner_rejects_cross_thread_reentry);
    RUN_TEST(frame_owner_allows_one_active_device_per_thread);
    RUN_TEST(frame_begin_damage_does_not_publish_when_owner_is_busy);
    RUN_TEST(frame_owner_blocks_device_destroy_until_frame_release);
    RUN_TEST(frame_owner_blocks_device_controls);
    RUN_TEST(sample_count_bits_are_portable_and_bounded);
    RUN_TEST(capability_query_rejects_invalid_arguments);
    RUN_TEST(frame_lifecycle_rejects_null_device);
    RUN_TEST(device_controls_reject_null_device);
    RUN_TEST(device_resize_rejects_zero_dimensions);
    RUN_TEST(command_entrypoints_are_safe_without_current_device);
    RUN_TEST(device_creation_rejects_invalid_backend_dimensions_and_handles);
    RUN_TEST(resource_api_rejects_null_and_malformed_inputs);
    RUN_TEST(resource_descriptors_reject_zero_and_unsupported_values);
    RUN_TEST(resource_descriptor_validation_is_bounded);
    RUN_TEST(secondary_resource_creation_rejects_invalid_inputs);
    RUN_TEST(framebuffer_descriptors_reject_invalid_inputs);
    RUN_TEST(offscreen_descriptor_requires_safe_supported_values);
    RUN_TEST(offscreen_descriptor_defaults_to_single_sample);
    RUN_TEST(present_damage_rects_require_bounded_nonempty_regions);
    RUN_TEST(present_damage_rects_have_a_fixed_upper_bound);
    RUN_TEST(screenshot_region_requires_bounded_rgba8_storage);
    RUN_TEST(screenshot_region_rejects_size_overflow);
    RUN_TEST(present_damage_converts_top_left_to_bottom_left);
    RUN_TEST(present_damage_conversion_supports_in_place_and_rejects_bad_capacity);
    RUN_TEST(present_history_forces_full_on_first_image_use);
    RUN_TEST(present_history_merges_damage_since_image_was_used);
    RUN_TEST(present_history_reset_invalidates_every_swapchain_image);
    RUN_TEST(present_history_aborts_to_safe_full_frame);
    RUN_TEST(present_history_rejects_invalid_damage_without_state_change);
    RUN_TEST(present_history_overflow_invalidates_other_images);
    RUN_TEST(present_damage_history_requires_full_for_unknown_age);
    RUN_TEST(present_damage_history_requires_history_for_age_one);
    RUN_TEST(present_damage_history_merges_age_without_reusing_old_damage);
    RUN_TEST(present_damage_history_rejects_age_gap_and_preserves_state);
    RUN_TEST(present_damage_history_overflow_forces_full);
TEST_MAIN_END()
