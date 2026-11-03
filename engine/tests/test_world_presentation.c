#include "test_framework.h"
#include <renderer/world_presentation.h>

static MeshGpu test_gpu(u32 id) {
    MeshGpu gpu = {{id, id}, {id + 1000u, id + 1000u}};
    return gpu;
}

static MeshDrawDesc test_draw(void) {
    MeshDrawDesc desc = {4u, 36u, 6u};
    return desc;
}

static MeshMaterial test_material(void) {
    MeshMaterial material;
    memset(&material, 0, sizeof(material));
    material.base_color = vec3(1.0f, 0.8f, 0.6f);
    material.roughness = 0.5f;
    material.albedo = (RHITexture){50u, 50u};
    material.sampler = (RHISampler){51u, 51u};
    return material;
}

typedef struct SnapshotFixture {
    WorldObject objects[3];
    WorldVegetationPrototype prototypes[1];
    VegetationInstance instances[2];
    VegetationBuild vegetation;
    u32 outdoor[3];
    VisRoom rooms[1];
    VisQuery visibility;
    u8 levels[2];
    u32 tags[2];
    LodInstanceState lod_state;
    WorldPresentationInput input;
} SnapshotFixture;

static void fixture_init(SnapshotFixture *f) {
    memset(f, 0, sizeof(*f));
    for (u32 i = 0; i < 3u; i++) {
        f->objects[i].id = 10u + i * 10u;
        f->objects[i].gpu = test_gpu(100u + i);
        f->objects[i].draw = test_draw();
        f->objects[i].material = test_material();
        f->objects[i].stream = i == 2u;
    }
    f->outdoor[0] = 10u;
    f->outdoor[1] = 30u;
    f->outdoor[2] = 20u;
    f->visibility.rooms = f->rooms;
    f->visibility.room_count = 0u;
    f->visibility.outdoor_ids = f->outdoor;
    f->visibility.outdoor_count = 2u;
    f->visibility.camera_forward = vec3(0, 0, 1);

    f->prototypes[0].lod_count = 2u;
    f->prototypes[0].errors[0] = 0.0f;
    f->prototypes[0].errors[1] = 0.02f;
    f->prototypes[0].material = test_material();
    for (u32 i = 0; i < 2u; i++) {
        f->prototypes[0].gpu[i] = test_gpu(200u + i);
        f->prototypes[0].draws[i] = test_draw();
    }
    f->instances[0].position = vec3(0, 0, 1);
    f->instances[0].prototype = 0u;
    f->instances[1].position = vec3(100, 0, 0);
    f->instances[1].prototype = 0u;
    f->vegetation.instances = f->instances;
    f->vegetation.capacity = 2u;
    f->vegetation.count = 2u;
    f->lod_state.level = f->levels;
    f->lod_state.tag = f->tags;
    f->lod_state.capacity = 2u;

    f->input.frame_id = 7u;
    f->input.view = mat4_identity();
    f->input.projection = mat4_identity();
    f->input.camera = vec3(0, 0, 0);
    f->input.fov = 1.0f;
    f->input.screen_height = 100.0f;
    f->input.pixel_error = 1.0f;
    f->input.lighting.sun_dir = vec3(0, 1, 0);
    f->input.lighting.sun_color = vec3(1, 1, 1);
    f->input.lighting.ambient = vec3(0.1f, 0.1f, 0.1f);
    f->input.lighting.fog = 0.25f;
    f->input.objects = f->objects;
    f->input.object_count = 3u;
    f->input.visibility = &f->visibility;
    f->input.vegetation = &f->vegetation;
    f->input.prototypes = f->prototypes;
    f->input.prototype_count = 1u;
    f->input.lod_state = &f->lod_state;
}

TEST(snapshot_filters_visibility_and_selects_vegetation_lod) {
    SnapshotFixture f;
    fixture_init(&f);
    WorldFrameSnapshot out;
    memset(&out, 0, sizeof(out));
    ASSERT_EQ(world_presentation_snapshot(&f.input, &out), WORLD_PRESENTATION_OK);
    ASSERT_EQ(out.frame_id, 7u);
    ASSERT_EQ(out.draw_count, 2u);
    ASSERT_EQ(out.draws[0].object_id, 10u);
    ASSERT_EQ(out.draws[1].object_id, 30u);
    ASSERT_FALSE(out.draws[0].stream);
    ASSERT_TRUE(out.draws[1].stream);
    ASSERT_FLOAT_EQ(out.lighting.fog, 0.25f, 1e-6);
    ASSERT_EQ(out.instance_count, 2u);
    ASSERT_EQ(out.batch_count, 2u);
    ASSERT_EQ(out.batches[0].lod, 0u);
    ASSERT_EQ(out.batches[1].lod, 1u);
    ASSERT_EQ(out.batches[0].count, 1u);
    ASSERT_EQ(out.batches[1].count, 1u);
    u32 fine = out.batches[0].first;
    u32 coarse = out.batches[1].first;
    ASSERT_FLOAT_EQ(out.instances[fine].model.e[3][2], 1.0f, 1e-6);
    ASSERT_FLOAT_EQ(out.instances[coarse].model.e[3][0], 100.0f, 1e-6);
    ASSERT_EQ(f.levels[0], 0u);
    ASSERT_EQ(f.levels[1], 1u);
}

TEST(stream_tile_uses_the_same_migrated_mesh_path) {
    StreamTileData tile;
    memset(&tile, 0, sizeof(tile));
    tile.vertex_count = 4u;
    for (u32 i = 0; i < 4u; i++) {
        tile.verts[i].px = (i == 1u || i == 2u) ? 1.0f : -1.0f;
        tile.verts[i].py = (i >= 2u) ? 1.0f : -1.0f;
        tile.verts[i].nz = 1.0f;
        tile.verts[i].material = 9u;
    }
    MeshBuffer mesh;
    ASSERT_TRUE(world_presentation_stream_mesh(&tile, vec3(5, 6, 7), &mesh));
    ASSERT_EQ(mesh.count, 4u);
    ASSERT_EQ(mesh.index_count, 6u);
    ASSERT_FLOAT_EQ(mesh.verts[0].px, 4.0f, 1e-6);
    ASSERT_FLOAT_EQ(mesh.verts[0].py, 5.0f, 1e-6);
    ASSERT_FLOAT_EQ(mesh.verts[0].pz, 7.0f, 1e-6);
    ASSERT_EQ(mesh.verts[0].material, 9u);
    MeshDrawDesc desc;
    ASSERT_TRUE(mesh_buffer_draw_desc(&mesh, &desc));
    ASSERT_EQ(desc.stride, 36u);

    MeshBuffer before = mesh;
    tile.verts[0].px = NAN;
    ASSERT_FALSE(world_presentation_stream_mesh(&tile, vec3(5, 6, 7), &mesh));
    ASSERT_EQ(memcmp(&mesh, &before, sizeof(mesh)), 0);
}

TEST(snapshot_overflow_and_invalid_input_are_atomic) {
    SnapshotFixture f;
    fixture_init(&f);
    static WorldFrameSnapshot out;
    static WorldFrameSnapshot before;
    memset(&out, 0x5a, sizeof(out));
    before = out;
    f.input.object_count = WORLD_PRESENT_MAX_OBJECTS + 1u;
    ASSERT_EQ(world_presentation_snapshot(&f.input, &out), WORLD_PRESENTATION_OVERLOAD);
    ASSERT_EQ(memcmp(&out, &before, sizeof(out)), 0);

    fixture_init(&f);
    f.input.object_count = 3u;
    f.objects[0].material.roughness = NAN;
    f.levels[0] = 3u;
    f.tags[0] = 9u;
    ASSERT_EQ(world_presentation_snapshot(&f.input, &out), WORLD_PRESENTATION_INVALID);
    ASSERT_EQ(memcmp(&out, &before, sizeof(out)), 0);
    ASSERT_EQ(f.levels[0], 3u);
    ASSERT_EQ(f.tags[0], 9u);

    fixture_init(&f);
    static u32 too_many[WORLD_PRESENT_MAX_OBJECTS + 1u];
    for (u32 i = 0; i < WORLD_PRESENT_MAX_OBJECTS + 1u; i++) too_many[i] = 10u;
    f.visibility.outdoor_ids = too_many;
    f.visibility.outdoor_count = WORLD_PRESENT_MAX_OBJECTS + 1u;
    ASSERT_EQ(world_presentation_snapshot(&f.input, &out), WORLD_PRESENTATION_OVERLOAD);
    ASSERT_EQ(memcmp(&out, &before, sizeof(out)), 0);

    fixture_init(&f);
    f.visibility.rooms = NULL;
    f.visibility.room_count = 1u;
    ASSERT_EQ(world_presentation_snapshot(&f.input, &out), WORLD_PRESENTATION_INVALID);
    ASSERT_EQ(memcmp(&out, &before, sizeof(out)), 0);

    fixture_init(&f);
    f.visibility.outdoor_ids = NULL;
    f.visibility.outdoor_count = 1u;
    ASSERT_EQ(world_presentation_snapshot(&f.input, &out), WORLD_PRESENTATION_INVALID);
    ASSERT_EQ(memcmp(&out, &before, sizeof(out)), 0);

    fixture_init(&f);
    f.instances[1].prototype = 8u;
    ASSERT_EQ(world_presentation_snapshot(&f.input, &out), WORLD_PRESENTATION_INVALID);
    ASSERT_EQ(memcmp(&out, &before, sizeof(out)), 0);
    ASSERT_EQ(f.tags[0], 0u);
    ASSERT_EQ(f.tags[1], 0u);
}

TEST_MAIN_BEGIN()
    RUN_TEST(snapshot_filters_visibility_and_selects_vegetation_lod);
    RUN_TEST(stream_tile_uses_the_same_migrated_mesh_path);
    RUN_TEST(snapshot_overflow_and_invalid_input_are_atomic);
TEST_MAIN_END()
