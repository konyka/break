#include "test_framework.h"
#include "world_fake_rhi.h"
#include <renderer/world_presentation.h>

static MeshGpu gpu(u32 id) {
    MeshGpu result = {{id, id}, {id + 1000u, id + 1000u}};
    return result;
}

static MeshMaterial material(void) {
    MeshMaterial result;
    memset(&result, 0, sizeof(result));
    result.base_color = vec3(0.4f, 0.5f, 0.6f);
    result.roughness = 0.5f;
    result.albedo = (RHITexture){70u, 70u};
    result.sampler = (RHISampler){71u, 71u};
    return result;
}

static void snapshot_init(WorldFrameSnapshot *snapshot) {
    memset(snapshot, 0, sizeof(*snapshot));
    snapshot->frame_id = 3u;
    snapshot->view = mat4_identity();
    snapshot->projection = mat4_identity();
    snapshot->camera = vec3(0, 0, 5);
    snapshot->lighting.sun_dir = vec3(0, 0, 1);
    snapshot->lighting.sun_color = vec3(1, 1, 1);
    snapshot->lighting.ambient = vec3(0.1f, 0.1f, 0.1f);
    snapshot->lighting.fog = 0.2f;
    MeshDrawDesc draw = {4u, 36u, 6u};
    for (u32 i = 0; i < 2u; i++) {
        snapshot->draws[i].object_id = 10u + i * 20u;
        snapshot->draws[i].gpu = gpu(100u + i);
        snapshot->draws[i].draw = draw;
        snapshot->draws[i].material = material();
        snapshot->draws[i].stream = i == 1u;
    }
    snapshot->draw_count = 2u;
    snapshot->prototype_count = 1u;
    snapshot->prototypes[0].lod_count = 2u;
    snapshot->prototypes[0].material = material();
    for (u32 i = 0; i < 2u; i++) {
        snapshot->prototypes[0].gpu[i] = gpu(200u + i);
        snapshot->prototypes[0].draws[i] = draw;
    }
    snapshot->instance_count = 2u;
    snapshot->instances[0].model = mat4_translation(-1, 0, 0);
    snapshot->instances[1].model = mat4_translation(1, 0, 0);
    snapshot->batch_count = 1u;
    snapshot->batches[0].prototype = 0u;
    snapshot->batches[0].lod = 1u;
    snapshot->batches[0].first = 0u;
    snapshot->batches[0].count = 2u;
}

TEST(presenter_submits_stream_like_objects_and_instances_vegetation) {
    world_fake_reset(false);
    RHIDevice *dev = (RHIDevice *)1;
    RHICmdBuffer *cmd = (RHICmdBuffer *)1;
    WorldPresenter presenter;
    ASSERT_TRUE(world_presenter_create(dev, &presenter));
    static WorldFrameSnapshot snapshot;
    snapshot_init(&snapshot);
    WorldSubmitStats stats;
    memset(&stats, 0, sizeof(stats));
    ASSERT_EQ(world_presenter_submit(cmd, &presenter, &snapshot, &stats), WORLD_PRESENTATION_OK);
    ASSERT_EQ(stats.object_draws, 2u);
    ASSERT_EQ(stats.stream_draws, 1u);
    ASSERT_EQ(stats.instance_batches, 1u);
    ASSERT_EQ(stats.instance_count, 2u);
    ASSERT_EQ(g_world_fake.draw_count, 3u);
    ASSERT_EQ(g_world_fake.draws[0].pipeline.index, presenter.object_pipeline.pipeline.index);
    ASSERT_EQ(g_world_fake.draws[1].pipeline.index, presenter.object_pipeline.pipeline.index);
    ASSERT_EQ(g_world_fake.draws[2].pipeline.index, presenter.vegetation_pipeline.pipeline.index);
    ASSERT_EQ(g_world_fake.draws[2].vertex.index, snapshot.prototypes[0].gpu[1].vertex.index);
    ASSERT_EQ(g_world_fake.draws[2].instance_count, 2u);
    ASSERT_EQ(g_world_fake.draws[2].uniforms.instance_offset, 0);
    ASSERT_EQ(g_world_fake.update_count, 1u);
    ASSERT_EQ(g_world_fake.update_size, 2u * sizeof(Mat4));
    ASSERT_EQ(g_world_fake.texel_buffer.index, presenter.instances.index);
    ASSERT_EQ(memcmp(g_world_fake.instance_data, snapshot.instances, sizeof(Mat4) * 2u), 0);
    for (u32 i = 0; i < g_world_fake.draw_count; i++) ASSERT_NEQ(g_world_fake.draws[i].vertex.index, 20u);
    ASSERT_FLOAT_EQ(g_world_fake.draws[0].uniforms.base_color.e[2], 0.6f, 1e-6);
    ASSERT_FLOAT_EQ(g_world_fake.draws[0].uniforms.fog, 0.2f, 1e-6);

    world_presenter_destroy(dev, &presenter);
    ASSERT_FALSE(presenter.ready);
    ASSERT_EQ(g_world_fake.live_pipelines, 0u);
    ASSERT_EQ(g_world_fake.live_buffers, 0u);
    ASSERT_EQ(g_world_fake.live_textures, 0u);
    ASSERT_EQ(g_world_fake.live_samplers, 0u);
}

TEST(presenter_batch_offsets_and_invalid_snapshot_are_checked) {
    world_fake_reset(true);
    RHIDevice *dev = (RHIDevice *)1;
    RHICmdBuffer *cmd = (RHICmdBuffer *)1;
    WorldPresenter presenter;
    ASSERT_TRUE(world_presenter_create(dev, &presenter));
    static WorldFrameSnapshot snapshot;
    snapshot_init(&snapshot);
    snapshot.instance_count = 3u;
    snapshot.instances[2].model = mat4_translation(2, 0, 0);
    snapshot.batches[0].count = 2u;
    snapshot.batch_count = 2u;
    snapshot.batches[1].prototype = 0u;
    snapshot.batches[1].lod = 0u;
    snapshot.batches[1].first = 2u;
    snapshot.batches[1].count = 1u;
    WorldSubmitStats stats;
    ASSERT_EQ(world_presenter_submit(cmd, &presenter, &snapshot, &stats), WORLD_PRESENTATION_OK);
    ASSERT_EQ(g_world_fake.draws[3].uniforms.instance_offset, 2);
    ASSERT_EQ(stats.instance_count, 3u);

    u32 draws_before = g_world_fake.draw_count;
    snapshot.batches[1].first = 1u;
    ASSERT_EQ(world_presenter_submit(cmd, &presenter, &snapshot, &stats), WORLD_PRESENTATION_INVALID);
    ASSERT_EQ(g_world_fake.draw_count, draws_before);
    world_presenter_destroy(dev, &presenter);
}

TEST(presenter_creation_failure_cleans_partial_resources) {
    world_fake_reset(false);
    g_world_fake.pipeline_fail_on_call = 2u;
    WorldPresenter presenter;
    ASSERT_FALSE(world_presenter_create((RHIDevice *)1, &presenter));
    ASSERT_FALSE(presenter.ready);
    ASSERT_FALSE(rhi_handle_valid(presenter.object_pipeline.pipeline));
    ASSERT_EQ(g_world_fake.live_pipelines, 0u);
    ASSERT_EQ(g_world_fake.live_shaders, 0u);
    ASSERT_EQ(g_world_fake.live_buffers, 0u);
    ASSERT_EQ(g_world_fake.live_textures, 0u);
    ASSERT_EQ(g_world_fake.live_samplers, 0u);
}

TEST(presenter_accepts_exact_65536_byte_instance_upload) {
    world_fake_reset(false);
    RHIDevice *dev = (RHIDevice *)1;
    WorldPresenter presenter;
    ASSERT_TRUE(world_presenter_create(dev, &presenter));
    static WorldFrameSnapshot snapshot;
    snapshot_init(&snapshot);
    snapshot.instance_count = WORLD_PRESENT_MAX_INSTANCES;
    snapshot.batches[0].count = WORLD_PRESENT_MAX_INSTANCES;
    for (u32 i = 0; i < WORLD_PRESENT_MAX_INSTANCES; i++)
        snapshot.instances[i].model = mat4_translation((f32)i, 0, 0);
    WorldSubmitStats stats;
    ASSERT_EQ(world_presenter_submit((RHICmdBuffer *)1, &presenter, &snapshot, &stats),
              WORLD_PRESENTATION_OK);
    ASSERT_EQ(stats.instance_count, WORLD_PRESENT_MAX_INSTANCES);
    ASSERT_EQ(g_world_fake.update_count, 1u);
    ASSERT_EQ(g_world_fake.update_size, 65536u);
    ASSERT_EQ(g_world_fake.draws[2].instance_count, WORLD_PRESENT_MAX_INSTANCES);
    ASSERT_EQ(memcmp(g_world_fake.instance_data + 1023u * sizeof(Mat4),
                     &snapshot.instances[1023], sizeof(Mat4)), 0);
    world_presenter_destroy(dev, &presenter);
}

TEST(presenter_rejects_1025_instances_before_any_command) {
    world_fake_reset(true);
    RHIDevice *dev = (RHIDevice *)1;
    WorldPresenter presenter;
    ASSERT_TRUE(world_presenter_create(dev, &presenter));
    static WorldFrameSnapshot snapshot;
    snapshot_init(&snapshot);
    snapshot.instance_count = WORLD_PRESENT_MAX_INSTANCES + 1u;
    snapshot.batches[0].count = WORLD_PRESENT_MAX_INSTANCES + 1u;
    WorldSubmitStats stats;
    memset(&stats, 0xa5, sizeof(stats));
    WorldSubmitStats before = stats;
    ASSERT_EQ(world_presenter_submit((RHICmdBuffer *)1, &presenter, &snapshot, &stats),
              WORLD_PRESENTATION_OVERLOAD);
    ASSERT_EQ(memcmp(&stats, &before, sizeof(stats)), 0);
    ASSERT_EQ(g_world_fake.draw_count, 0u);
    ASSERT_EQ(g_world_fake.update_count, 0u);
    ASSERT_EQ(g_world_fake.update_size, 0u);
    world_presenter_destroy(dev, &presenter);
}

TEST_MAIN_BEGIN()
    RUN_TEST(presenter_submits_stream_like_objects_and_instances_vegetation);
    RUN_TEST(presenter_batch_offsets_and_invalid_snapshot_are_checked);
    RUN_TEST(presenter_creation_failure_cleans_partial_resources);
    RUN_TEST(presenter_accepts_exact_65536_byte_instance_upload);
    RUN_TEST(presenter_rejects_1025_instances_before_any_command);
TEST_MAIN_END()
