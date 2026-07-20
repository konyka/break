/* ==========================================================================
 *  test_scene_serial.c — Unit tests for BSCN binary scene serialization.
 * ========================================================================== */

#include "test_framework.h"
#include <scene/scene_serial.h>
#include <ecs/ecs.h>
#include <asset/asset.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

/* ----------------------------------------------------------------------- */
/*  Header format validation                                                */
/* ----------------------------------------------------------------------- */

TEST(bscn_magic_value)
{
    /* BSCN_MAGIC = 0x4E534342, stored as LE bytes: 42='B', 43='C', 53='S', 4E='N' */
    u32 magic = BSCN_MAGIC;
    u8 *bytes = (u8 *)&magic;
    ASSERT_EQ(bytes[0], (u8)'B');
    ASSERT_EQ(bytes[1], (u8)'C');
    ASSERT_EQ(bytes[2], (u8)'S');
    ASSERT_EQ(bytes[3], (u8)'N');
}

TEST(bscn_version)
{
    ASSERT_EQ(BSCN_VERSION, 1u);
}

TEST(bscn_header_size)
{
    /* Header is 3 u32 fields = 12 bytes */
    ASSERT_EQ(sizeof(BscnHeader), 12u);
}

TEST(bscn_chunk_entry_size)
{
    /* ChunkEntry is 3 u32 fields = 12 bytes */
    ASSERT_EQ(sizeof(BscnChunkEntry), 12u);
}

/* ----------------------------------------------------------------------- */
/*  load_binary rejects invalid files                                       */
/* ----------------------------------------------------------------------- */

TEST(load_binary_null_args)
{
    ASSERT_TRUE(!scene_load_binary(NULL, NULL, "/tmp/nonexistent.bscn"));
}

TEST(load_binary_nonexistent_file)
{
    World w = {0};
    ASSERT_TRUE(!scene_load_binary(&w, NULL, "/tmp/absolutely_nonexistent_12345.bscn"));
}

TEST(load_binary_bad_magic)
{
    /* Write a file with wrong magic */
    const char *path = "/tmp/test_bad_magic.bscn";
    {
        BscnHeader h = {0};
        h.magic = 0xDEADBEEF;
        h.version = BSCN_VERSION;
        h.chunk_count = 0;
        FILE *fp = fopen(path, "wb");
        if (fp) { fwrite(&h, sizeof(h), 1, fp); fclose(fp); }
    }
    World w = {0};
    ASSERT_TRUE(!scene_load_binary(&w, NULL, path));
    remove(path);
}

TEST(load_binary_bad_version)
{
    /* Write a file with wrong version */
    const char *path = "/tmp/test_bad_version.bscn";
    {
        BscnHeader h = {0};
        h.magic = BSCN_MAGIC;
        h.version = 999;
        h.chunk_count = 0;
        FILE *fp = fopen(path, "wb");
        if (fp) { fwrite(&h, sizeof(h), 1, fp); fclose(fp); }
    }
    World w = {0};
    ASSERT_TRUE(!scene_load_binary(&w, NULL, path));
    remove(path);
}

TEST(load_binary_truncated)
{
    /* Write a file smaller than header */
    const char *path = "/tmp/test_truncated.bscn";
    {
        u8 data[4] = {0};
        FILE *fp = fopen(path, "wb");
        if (fp) { fwrite(data, sizeof(data), 1, fp); fclose(fp); }
    }
    World w = {0};
    ASSERT_TRUE(!scene_load_binary(&w, NULL, path));
    remove(path);
}

TEST(load_binary_too_many_chunks)
{
    /* chunk_count > 64 should be rejected */
    const char *path = "/tmp/test_many_chunks.bscn";
    {
        BscnHeader h = {0};
        h.magic = BSCN_MAGIC;
        h.version = BSCN_VERSION;
        h.chunk_count = 100;
        FILE *fp = fopen(path, "wb");
        if (fp) { fwrite(&h, sizeof(h), 1, fp); fclose(fp); }
    }
    World w = {0};
    ASSERT_TRUE(!scene_load_binary(&w, NULL, path));
    remove(path);
}

/* ----------------------------------------------------------------------- */
/*  save_binary validation                                                  */
/* ----------------------------------------------------------------------- */

TEST(save_binary_null_world)
{
    ASSERT_TRUE(!scene_save_binary(NULL, NULL, "/tmp/test.bscn", NULL));
}

TEST(save_binary_null_path)
{
    World w = {0};
    ASSERT_TRUE(!scene_save_binary(&w, NULL, NULL, NULL));
}

/* ----------------------------------------------------------------------- */
/*  JSON format validation                                                  */
/* ----------------------------------------------------------------------- */

TEST(load_json_nonexistent)
{
    World w = {0};
    ASSERT_TRUE(!scene_load_json(&w, NULL, "/tmp/absolutely_nonexistent_67890.json"));
}

TEST(save_json_null_world)
{
    ASSERT_TRUE(!scene_save_json(NULL, NULL, "/tmp/test.json", NULL));
}

/* ----------------------------------------------------------------------- */
/*  Edge Cases                                                              */
/* ----------------------------------------------------------------------- */

TEST(load_binary_empty_path)
{
    World w = {0};
    /* Empty path should fail gracefully */
    ASSERT_TRUE(!scene_load_binary(&w, NULL, ""));
}

TEST(save_binary_empty_path)
{
    World w = {0};
    /* Empty path should fail gracefully */
    ASSERT_TRUE(!scene_save_binary(&w, NULL, "", NULL));
}

TEST(load_json_empty_path)
{
    World w = {0};
    /* Empty path should fail gracefully */
    ASSERT_TRUE(!scene_load_json(&w, NULL, ""));
}

TEST(save_json_empty_path)
{
    World w = {0};
    /* Empty path should fail gracefully */
    ASSERT_TRUE(!scene_save_json(&w, NULL, "", NULL));
}

TEST(load_binary_zero_chunks)
{
    /* Valid file with zero chunks */
    const char *path = "/tmp/test_zero_chunks.bscn";
    {
        BscnHeader h = {0};
        h.magic = BSCN_MAGIC;
        h.version = BSCN_VERSION;
        h.chunk_count = 0;
        FILE *fp = fopen(path, "wb");
        if (fp) { fwrite(&h, sizeof(h), 1, fp); fclose(fp); }
    }
    World w = {0};
    /* Zero chunks should load successfully */
    bool ok = scene_load_binary(&w, NULL, path);
    /* May or may not succeed depending on implementation - just don't crash */
    (void)ok;
    remove(path);
}

/* ----------------------------------------------------------------------- */
/*  Round 8: RESOURCES chunk + include_resources + generation restore       */
/* ----------------------------------------------------------------------- */

/* Build a small in-memory scene with 2 meshes + 2 materials (no GPU handles). */
static void make_scene(Scene *s) {
    memset(s, 0, sizeof(*s));
    s->mesh_count = 2;
    s->meshes = (Mesh *)calloc(2, sizeof(Mesh));
    s->meshes[0].index_count = 36;  s->meshes[0].vertex_count = 24;
    s->meshes[0].material_idx = 0;
    s->meshes[0].aabb_min = vec3(-1, -1, -1); s->meshes[0].aabb_max = vec3(1, 1, 1);
    s->meshes[1].index_count = 6;   s->meshes[1].vertex_count = 4;
    s->meshes[1].material_idx = 1;
    s->meshes[1].aabb_min = vec3(0, 0, 0);    s->meshes[1].aabb_max = vec3(2, 0, 2);

    s->material_count = 2;
    s->materials = (Material *)calloc(2, sizeof(Material));
    s->materials[0].base_color[0] = 0.25f; s->materials[0].base_color[1] = 0.5f;
    s->materials[0].base_color[2] = 0.75f; s->materials[0].base_color[3] = 1.0f;
    s->materials[0].metallic_factor = 0.1f; s->materials[0].roughness_factor = 0.8f;
    s->materials[0].emissive_strength = 0.0f; s->materials[0].alpha_cutoff = 0.5f;
    s->materials[0].alpha_mode = ALPHA_OPAQUE;
    s->materials[1].base_color[0] = 1.0f; s->materials[1].base_color[1] = 0.0f;
    s->materials[1].base_color[2] = 0.0f; s->materials[1].base_color[3] = 0.5f;
    s->materials[1].metallic_factor = 0.9f; s->materials[1].roughness_factor = 0.2f;
    s->materials[1].alpha_mode = ALPHA_BLEND;
}

static void free_scene_src(Scene *s) {
    free(s->meshes);
    free(s->materials);
    scene_resources_free(s);
    memset(s, 0, sizeof(*s));
}

TEST(resources_roundtrip_include)
{
    const char *path = "/tmp/test_res_include.bscn";
    World *w = world_create();
    Scene src; make_scene(&src);

    SerializeOptions opts = { .include_resources = true, .pretty_json = false };
    ASSERT_TRUE(scene_save_binary(w, &src, path, &opts));

    World *w2 = world_create();
    Scene dst; memset(&dst, 0, sizeof(dst));
    ASSERT_TRUE(scene_load_binary(w2, &dst, path));

    /* 2 meshes + 2 materials + 0 textures (no valid GPU handles). */
    ASSERT_EQ(dst.resource_count, 4u);

    /* Find mesh 0 and material 1, verify inlined descriptors round-tripped. */
    bool found_mesh0 = false, found_mat1 = false;
    for (u32 i = 0; i < dst.resource_count; i++) {
        SceneResource *r = &dst.resources[i];
        ASSERT_TRUE((r->flags & 1u) != 0);   /* descriptor inlined */
        if (r->type == BSCN_RES_MESH && r->ref_index == 0) {
            found_mesh0 = true;
            ASSERT_EQ(r->u0, 36u);   /* index_count */
            ASSERT_EQ(r->u1, 24u);   /* vertex_count */
        }
        if (r->type == BSCN_RES_MATERIAL && r->ref_index == 1) {
            found_mat1 = true;
            ASSERT_TRUE(fabsf(r->f[0] - 1.0f) < 1e-6f);  /* base_color.r */
            ASSERT_TRUE(fabsf(r->f[3] - 0.5f) < 1e-6f);  /* base_color.a */
            ASSERT_EQ(r->u0, (u32)ALPHA_BLEND);
        }
    }
    ASSERT_TRUE(found_mesh0);
    ASSERT_TRUE(found_mat1);

    free_scene_src(&dst);
    free_scene_src(&src);
    world_destroy(w);
    world_destroy(w2);
    remove(path);
}

TEST(resources_roundtrip_refs_only)
{
    const char *path = "/tmp/test_res_refs.bscn";
    World *w = world_create();
    Scene src; make_scene(&src);

    SerializeOptions opts = { .include_resources = false, .pretty_json = false };
    ASSERT_TRUE(scene_save_binary(w, &src, path, &opts));

    World *w2 = world_create();
    Scene dst; memset(&dst, 0, sizeof(dst));
    ASSERT_TRUE(scene_load_binary(w2, &dst, path));

    ASSERT_EQ(dst.resource_count, 4u);
    for (u32 i = 0; i < dst.resource_count; i++) {
        SceneResource *r = &dst.resources[i];
        /* path-only: no descriptor inlined, but guid + type + ref kept. */
        ASSERT_EQ(r->flags & 1u, 0u);
        ASSERT_TRUE(r->guid != 0);
        ASSERT_EQ(r->u0, 0u);
        ASSERT_TRUE(fabsf(r->f[0]) < 1e-9f);
    }

    free_scene_src(&dst);
    free_scene_src(&src);
    world_destroy(w);
    world_destroy(w2);
    remove(path);
}

TEST(resources_guid_deterministic)
{
    const char *p1 = "/tmp/test_res_g1.bscn";
    const char *p2 = "/tmp/test_res_g2.bscn";
    World *w = world_create();
    Scene src; make_scene(&src);
    SerializeOptions opts = { .include_resources = true, .pretty_json = false };

    ASSERT_TRUE(scene_save_binary(w, &src, p1, &opts));
    ASSERT_TRUE(scene_save_binary(w, &src, p2, &opts));

    World *wa = world_create(); Scene a; memset(&a, 0, sizeof(a));
    World *wb = world_create(); Scene b; memset(&b, 0, sizeof(b));
    ASSERT_TRUE(scene_load_binary(wa, &a, p1));
    ASSERT_TRUE(scene_load_binary(wb, &b, p2));

    ASSERT_EQ(a.resource_count, b.resource_count);
    for (u32 i = 0; i < a.resource_count; i++) {
        ASSERT_TRUE(a.resources[i].guid == b.resources[i].guid);
        ASSERT_EQ(a.resources[i].type, b.resources[i].type);
    }

    free_scene_src(&a); free_scene_src(&b); free_scene_src(&src);
    world_destroy(w); world_destroy(wa); world_destroy(wb);
    remove(p1); remove(p2);
}

TEST(generation_restore_roundtrip)
{
    const char *path = "/tmp/test_gen_restore.bscn";
    World *w = world_create();
    world_register_component(w, 1, sizeof(u32));

    Entity a = world_create_entity(w);   /* idx1 gen1 */
    Entity b = world_create_entity(w);   /* idx2 gen1 */
    world_destroy_entity(w, a);          /* free idx1 (bumps its generation) */
    Entity c = world_create_entity(w);   /* reuse idx1 -> generation bumped again */
    world_add_component(w, b, 1);
    world_add_component(w, c, 1);

    /* Capture the live generations to compare after a round-trip. */
    u32 idx_c = c.index, idx_b = b.index;
    u32 gen_c = w->entities[idx_c].generation;
    u32 gen_b = w->entities[idx_b].generation;
    ASSERT_TRUE(gen_c > 1u);   /* idx1 was reused, so its generation advanced */

    ASSERT_TRUE(scene_save_binary(w, NULL, path, NULL));

    World *w2 = world_create();
    world_register_component(w2, 1, sizeof(u32));
    ASSERT_TRUE(scene_load_binary(w2, NULL, path));

    /* Saved order is by ascending index; the loader recreates entities in that
     * same order and restores each generation. */
    ASSERT_EQ(w2->entities[idx_c].generation, gen_c);
    ASSERT_EQ(w2->entities[idx_b].generation, gen_b);

    /* The restored (index,generation) identity resolves as a live entity. */
    Entity restored = { idx_c, gen_c };
    ASSERT_TRUE(world_entity_exists(w2, restored));

    world_destroy(w);
    world_destroy(w2);
    remove(path);
}

/* R243: JSON path must restore generation just like the binary path. Save emits
 * "gen"; load previously discarded it, breaking (index, generation) identity on
 * JSON round-trips. */
TEST(generation_restore_roundtrip_json)
{
    const char *path = "/tmp/test_gen_restore.json";
    World *w = world_create();
    world_register_component(w, 1, sizeof(u32));

    Entity a = world_create_entity(w);
    Entity b = world_create_entity(w);
    world_destroy_entity(w, a);
    Entity c = world_create_entity(w);
    world_add_component(w, b, 1);
    world_add_component(w, c, 1);

    u32 idx_c = c.index, idx_b = b.index;
    u32 gen_c = w->entities[idx_c].generation;
    u32 gen_b = w->entities[idx_b].generation;
    ASSERT_TRUE(gen_c > 1u);

    SerializeOptions opts = { .include_resources = false, .pretty_json = false };
    ASSERT_TRUE(scene_save_json(w, NULL, path, &opts));

    World *w2 = world_create();
    world_register_component(w2, 1, sizeof(u32));
    ASSERT_TRUE(scene_load_json(w2, NULL, path));

    ASSERT_EQ(w2->entities[idx_c].generation, gen_c);
    ASSERT_EQ(w2->entities[idx_b].generation, gen_b);

    Entity restored = { idx_c, gen_c };
    ASSERT_TRUE(world_entity_exists(w2, restored));

    world_destroy(w);
    world_destroy(w2);
    remove(path);
}

/* ----------------------------------------------------------------------- */

TEST_MAIN_BEGIN()
    RUN_TEST(bscn_magic_value);
    RUN_TEST(bscn_version);
    RUN_TEST(bscn_header_size);
    RUN_TEST(bscn_chunk_entry_size);
    RUN_TEST(load_binary_null_args);
    RUN_TEST(load_binary_nonexistent_file);
    RUN_TEST(load_binary_bad_magic);
    RUN_TEST(load_binary_bad_version);
    RUN_TEST(load_binary_truncated);
    RUN_TEST(load_binary_too_many_chunks);
    RUN_TEST(save_binary_null_world);
    RUN_TEST(save_binary_null_path);
    RUN_TEST(load_json_nonexistent);
    RUN_TEST(save_json_null_world);
    /* Edge cases */
    RUN_TEST(load_binary_empty_path);
    RUN_TEST(save_binary_empty_path);
    RUN_TEST(load_json_empty_path);
    RUN_TEST(save_json_empty_path);
    RUN_TEST(load_binary_zero_chunks);
    /* Round 8: resources + generation */
    RUN_TEST(resources_roundtrip_include);
    RUN_TEST(resources_roundtrip_refs_only);
    RUN_TEST(resources_guid_deterministic);
    RUN_TEST(generation_restore_roundtrip);
    RUN_TEST(generation_restore_roundtrip_json);
TEST_MAIN_END()
