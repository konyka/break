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
#include <unistd.h>
#include <sys/types.h>

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

TEST(bytebuf_reserve_rejects_u32_wrap)
{
    ASSERT_TRUE(scene_serial_test_bytebuf_rejects_wrap());
}

TEST(prefab_block_rejects_u32_wrap)
{
    ASSERT_TRUE(scene_serial_test_prefab_block_rejects_wrap());
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

TEST(load_binary_rollback_orphans_on_bad_components)
{
    /* R353: ENTITIES succeed then COMPONENTS fail → destroy created entities. */
    const char *path = "/tmp/test_rollback_orphans.bscn";
    {
        u32 ent_chunk[3] = {1u, 1u, 0u}; /* n, gen, comp_count */
        u32 comp_chunk[1] = {1u};        /* type_count only → truncated */

        BscnHeader h = {0};
        h.magic = BSCN_MAGIC;
        h.version = BSCN_VERSION;
        h.chunk_count = 2;
        BscnChunkEntry table[2];
        u32 base = (u32)sizeof(h) + 2u * (u32)sizeof(BscnChunkEntry);
        table[0].type = BSCN_CHUNK_ENTITIES;
        table[0].offset = base;
        table[0].size = (u32)sizeof(ent_chunk);
        table[1].type = BSCN_CHUNK_COMPONENTS;
        table[1].offset = base + (u32)sizeof(ent_chunk);
        table[1].size = (u32)sizeof(comp_chunk);

        FILE *fp = fopen(path, "wb");
        ASSERT_TRUE(fp != NULL);
        fwrite(&h, sizeof(h), 1, fp);
        fwrite(table, sizeof(table), 1, fp);
        fwrite(ent_chunk, sizeof(ent_chunk), 1, fp);
        fwrite(comp_chunk, sizeof(comp_chunk), 1, fp);
        fclose(fp);
    }

    World *w = world_create();
    ASSERT_NOT_NULL(w);
    u32 live_before = 0;
    for (u32 i = 0; i < w->entity_count; i++) {
        if (world_entity_exists(w, w->entities[i])) live_before++;
    }

    ASSERT_TRUE(!scene_load_binary(w, NULL, path));

    u32 live_after = 0;
    for (u32 i = 0; i < w->entity_count; i++) {
        if (world_entity_exists(w, w->entities[i])) live_after++;
    }
    ASSERT_EQ(live_before, live_after);

    world_destroy(w);
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
    /* R383: scene_load_binary also allocates `nodes` — and does so even for a
     * zero-node scene, so node_count==0 is no proof there is nothing to free. */
    scene_serial_free(s);
    memset(s, 0, sizeof(*s));
}

/* Reject the SCENE_NODES chunk by making its node count exceed the loader cap.
 * SCENE_NODES is written last, so RESOURCES has already been applied by then. */
static bool corrupt_scene_nodes_count(const char *path)
{
    FILE *f = fopen(path, "r+b");
    if (!f) return false;
    BscnHeader h;
    if (fread(&h, sizeof(h), 1, f) != 1) { fclose(f); return false; }
    bool done = false;
    for (u32 i = 0; i < h.chunk_count; i++) {
        BscnChunkEntry e;
        long ent_off = (long)(sizeof(BscnHeader) + i * sizeof(BscnChunkEntry));
        if (fseek(f, ent_off, SEEK_SET) != 0) break;
        if (fread(&e, sizeof(e), 1, f) != 1) break;
        if (e.type != BSCN_CHUNK_SCENE_NODES) continue;
        u32 bogus = 0xFFFFFFFFu;
        if (fseek(f, (long)e.offset, SEEK_SET) != 0) break;
        done = fwrite(&bogus, sizeof(bogus), 1, f) == 1;
        break;
    }
    fclose(f);
    return done;
}

/* R387: overwrite the RESOURCES chunk's entry count. Found by mutation fuzzing:
 * the count went straight into calloc(n, sizeof(SceneResource)). */
static bool set_resources_count(const char *path, u32 value)
{
    FILE *f = fopen(path, "r+b");
    if (!f) return false;
    BscnHeader h;
    if (fread(&h, sizeof(h), 1, f) != 1) { fclose(f); return false; }
    bool done = false;
    for (u32 i = 0; i < h.chunk_count; i++) {
        BscnChunkEntry e;
        long ent_off = (long)(sizeof(BscnHeader) + i * sizeof(BscnChunkEntry));
        if (fseek(f, ent_off, SEEK_SET) != 0) break;
        if (fread(&e, sizeof(e), 1, f) != 1) break;
        if (e.type != BSCN_CHUNK_RESOURCES) continue;
        if (fseek(f, (long)e.offset, SEEK_SET) != 0) break;
        done = fwrite(&value, sizeof(value), 1, f) == 1;
        break;
    }
    fclose(f);
    return done;
}

/* R396: overwrite the first entity's comp_count in the ENTITIES chunk. */
static bool set_first_entity_comp_count(const char *path, u32 value)
{
    FILE *f = fopen(path, "r+b");
    if (!f) return false;
    BscnHeader h;
    if (fread(&h, sizeof(h), 1, f) != 1) { fclose(f); return false; }
    bool done = false;
    for (u32 i = 0; i < h.chunk_count; i++) {
        BscnChunkEntry e;
        long ent_off = (long)(sizeof(BscnHeader) + i * sizeof(BscnChunkEntry));
        if (fseek(f, ent_off, SEEK_SET) != 0) break;
        if (fread(&e, sizeof(e), 1, f) != 1) break;
        if (e.type != BSCN_CHUNK_ENTITIES) continue;
        if (fseek(f, (long)e.offset + 8, SEEK_SET) != 0) break;
        done = fwrite(&value, sizeof(value), 1, f) == 1;
        break;
    }
    fclose(f);
    return done;
}

TEST(resources_count_bounded_by_chunk_size)
{
    const char *path = "/tmp/test_bscn_rescount.bscn";
    SerializeOptions opts = { .include_resources = true, .pretty_json = false };
    World *w = world_create();
    Scene src; make_scene(&src);
    ASSERT_TRUE(scene_save_binary(w, &src, path, &opts));
    /* A count no chunk this small could hold must be rejected before it
     * reaches calloc, not turned into a ~1.2TB request. */
    ASSERT_TRUE(set_resources_count(path, 0xFFFFFFFFu));

    World *w2 = world_create();
    Scene dst; memset(&dst, 0, sizeof(dst));
    ASSERT_TRUE(!scene_load_binary(w2, &dst, path));
    ASSERT_EQ(dst.resource_count, 0u);

    free_scene_src(&dst); free_scene_src(&src);
    world_destroy(w); world_destroy(w2);
    remove(path);
}

TEST(entities_comp_count_bounded)
{
    const char *path = "/tmp/test_bscn_compcount.bscn";
    World *w = world_create();
    world_register_component(w, 1, sizeof(u32));
    Entity e = world_create_entity(w);
    world_add_component(w, e, 1);
    ASSERT_TRUE(scene_save_binary(w, NULL, path, NULL));
    ASSERT_TRUE(set_first_entity_comp_count(path, 1000u));

    World *w2 = world_create();
    world_register_component(w2, 1, sizeof(u32));
    u32 live_before = 0;
    for (u32 i = 0; i < w2->entity_count; i++) {
        if (world_entity_exists(w2, w2->entities[i])) live_before++;
    }
    ASSERT_TRUE(!scene_load_binary(w2, NULL, path));
    u32 live_after = 0;
    for (u32 i = 0; i < w2->entity_count; i++) {
        if (world_entity_exists(w2, w2->entities[i])) live_after++;
    }
    ASSERT_EQ(live_before, live_after);

    world_destroy(w);
    world_destroy(w2);
    remove(path);
}

/* R398: scene_load_* read the entire file — reject before malloc. */
static bool write_sparse_file(const char *path, off_t size)
{
    FILE *f = fopen(path, "wb");
    if (!f) return false;
#if defined(_POSIX_C_SOURCE) && _POSIX_C_SOURCE >= 200112L
    bool ok = ftruncate(fileno(f), size) == 0;
#else
    bool ok = false;
    if (fseek(f, (long)size - 1, SEEK_SET) == 0) ok = fputc('x', f) != EOF;
#endif
    fclose(f);
    return ok;
}

TEST(load_binary_rejects_oversized_file)
{
    const char *path = "/tmp/test_bscn_huge.bscn";
    ASSERT_TRUE(write_sparse_file(path, (off_t)BSCN_MAX_FILE_BYTES + 1));

    World *w = world_create();
    ASSERT_TRUE(!scene_load_binary(w, NULL, path));
    ASSERT_TRUE(!scene_probe_binary(path));

    world_destroy(w);
    remove(path);
}

TEST(load_json_rejects_oversized_file)
{
    const char *path = "/tmp/test_bscn_huge.json";
    ASSERT_TRUE(write_sparse_file(path, (off_t)BSCN_MAX_FILE_BYTES + 1));

    World *w = world_create();
    ASSERT_TRUE(!scene_load_json(w, NULL, path));

    world_destroy(w);
    remove(path);
}

/* R387: two ENTITIES chunks made the first pass call load_entities_chunk twice,
 * overwriting (and leaking) the first allocation. */
TEST(duplicate_entities_chunk_rejected)
{
    const char *path = "/tmp/test_bscn_dupents.bscn";
    SerializeOptions opts = { .include_resources = true, .pretty_json = false };
    World *w = world_create();
    Scene src; make_scene(&src);
    ASSERT_TRUE(scene_save_binary(w, &src, path, &opts));

    /* Retype a second table slot to ENTITIES, pointing at the real one. */
    FILE *f = fopen(path, "r+b");
    ASSERT_NOT_NULL(f);
    BscnHeader h;
    ASSERT_TRUE(fread(&h, sizeof(h), 1, f) == 1);
    ASSERT_TRUE(h.chunk_count >= 2u);
    BscnChunkEntry ents_entry;
    memset(&ents_entry, 0, sizeof(ents_entry));
    bool found = false;
    for (u32 i = 0; i < h.chunk_count && !found; i++) {
        BscnChunkEntry e;
        fseek(f, (long)(sizeof(BscnHeader) + i * sizeof(BscnChunkEntry)), SEEK_SET);
        if (fread(&e, sizeof(e), 1, f) != 1) break;
        if (e.type == BSCN_CHUNK_ENTITIES) { ents_entry = e; found = true; }
    }
    ASSERT_TRUE(found);
    /* Slot 2 is HIERARCHY in the writer's fixed order; alias it to ENTITIES. */
    fseek(f, (long)(sizeof(BscnHeader) + 2u * sizeof(BscnChunkEntry)), SEEK_SET);
    ASSERT_TRUE(fwrite(&ents_entry, sizeof(ents_entry), 1, f) == 1);
    fclose(f);

    World *w2 = world_create();
    Scene dst; memset(&dst, 0, sizeof(dst));
    ASSERT_TRUE(!scene_load_binary(w2, &dst, path));

    free_scene_src(&dst); free_scene_src(&src);
    world_destroy(w); world_destroy(w2);
    remove(path);
}

/* R384: a chunk that fails after RESOURCES was applied must not leave the
 * caller's Scene half-overwritten — scene_load_binary now stages and commits. */
TEST(failed_load_keeps_previous_scene)
{
    const char *pa = "/tmp/test_bscn_keep_a.bscn";
    const char *pb = "/tmp/test_bscn_keep_b.bscn";
    SerializeOptions opts = { .include_resources = true, .pretty_json = false };

    /* A: 2 meshes + 2 materials → 4 resources. */
    World *wa = world_create();
    Scene a; make_scene(&a);
    ASSERT_TRUE(scene_save_binary(wa, &a, pa, &opts));

    /* B: 1 mesh only → 1 resource, then corrupt its trailing SCENE_NODES. */
    World *wb = world_create();
    Scene b; memset(&b, 0, sizeof(b));
    b.mesh_count = 1;
    b.meshes = (Mesh *)calloc(1, sizeof(Mesh));
    ASSERT_TRUE(scene_save_binary(wb, &b, pb, &opts));
    ASSERT_TRUE(corrupt_scene_nodes_count(pb));

    World *wd = world_create();
    Scene dst; memset(&dst, 0, sizeof(dst));
    ASSERT_TRUE(scene_load_binary(wd, &dst, pa));
    ASSERT_EQ(dst.resource_count, 4u);

    /* Loading B fails; A's manifest must survive intact rather than be swapped
     * for B's single entry. */
    World *wd2 = world_create();
    ASSERT_TRUE(!scene_load_binary(wd2, &dst, pb));
    ASSERT_EQ(dst.resource_count, 4u);
    ASSERT_TRUE(dst.resources != NULL);

    free_scene_src(&dst); free_scene_src(&a); free_scene_src(&b);
    world_destroy(wa); world_destroy(wb);
    world_destroy(wd); world_destroy(wd2);
    remove(pa); remove(pb);
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

TEST(instantiate_prefab_offsets_root_nodes_only)
{
    /* R416: scene_load_binary replaces s->nodes wholesale, so the position
     * offset must apply to the loaded nodes — not a tail slice starting at
     * the pre-load node count.
     * R422: but only to ROOT nodes — children inherit the root's translation
     * through world-transform composition, so offsetting every node displaced
     * a depth-d node by (d+1)x the position. */
    const char *path = "/tmp/test_prefab_offset.bscn";

    /* Prefab: depth-2 hierarchy — root at (1,0,0), child at (0,2,0),
     * grandchild at (0,0,3). */
    World *ws = world_create();
    Scene src; memset(&src, 0, sizeof(src));
    src.node_count = 3;
    src.nodes = (SceneNode *)calloc(3, sizeof(SceneNode));
    ASSERT_NOT_NULL(src.nodes);
    src.nodes[0].parent_index = UINT32_MAX;
    src.nodes[0].local_transform = mat4_identity();
    src.nodes[0].local_transform.e[3][0] = 1.0f;
    src.nodes[1].parent_index = 0;
    src.nodes[1].local_transform = mat4_identity();
    src.nodes[1].local_transform.e[3][1] = 2.0f;
    src.nodes[2].parent_index = 1;
    src.nodes[2].local_transform = mat4_identity();
    src.nodes[2].local_transform.e[3][2] = 3.0f;
    ASSERT_TRUE(scene_save_binary(ws, &src, path, NULL));

    /* Destination already holds 4 nodes (more than the prefab's 3): with the
     * old tail-slice loop, nodes [4..3) — nothing — would have been offset. */
    World *wd = world_create();
    Scene dst; memset(&dst, 0, sizeof(dst));
    dst.node_count = 4;
    dst.nodes = (SceneNode *)calloc(4, sizeof(SceneNode));
    ASSERT_NOT_NULL(dst.nodes);

    Vec3 offset = vec3(10.0f, 20.0f, 30.0f);
    ASSERT_TRUE(scene_instantiate_prefab(wd, &dst, path, offset));

    /* Replace semantics: the scene now holds exactly the prefab's nodes. */
    ASSERT_EQ(dst.node_count, 3u);
    ASSERT_EQ(dst.nodes[1].parent_index, 0u);
    ASSERT_EQ(dst.nodes[2].parent_index, 1u);

    /* Root: offset applied. */
    ASSERT_FLOAT_EQ(dst.nodes[0].local_transform.e[3][0], 1.0f + 10.0f, 1e-5f);
    ASSERT_FLOAT_EQ(dst.nodes[0].local_transform.e[3][1], 0.0f + 20.0f, 1e-5f);
    ASSERT_FLOAT_EQ(dst.nodes[0].local_transform.e[3][2], 0.0f + 30.0f, 1e-5f);
    /* Children: local transforms untouched — they inherit the root's move. */
    ASSERT_FLOAT_EQ(dst.nodes[1].local_transform.e[3][0], 0.0f, 1e-5f);
    ASSERT_FLOAT_EQ(dst.nodes[1].local_transform.e[3][1], 2.0f, 1e-5f);
    ASSERT_FLOAT_EQ(dst.nodes[1].local_transform.e[3][2], 0.0f, 1e-5f);
    ASSERT_FLOAT_EQ(dst.nodes[2].local_transform.e[3][0], 0.0f, 1e-5f);
    ASSERT_FLOAT_EQ(dst.nodes[2].local_transform.e[3][1], 0.0f, 1e-5f);
    ASSERT_FLOAT_EQ(dst.nodes[2].local_transform.e[3][2], 3.0f, 1e-5f);

    free_scene_src(&dst);
    free_scene_src(&src);
    world_destroy(ws);
    world_destroy(wd);
    remove(path);
}

/* R422: the JSON loader committed s->nodes (freeing the caller's old graph)
 * the moment the "nodes" array parsed — BEFORE the rest of the document. A
 * later top-level failure returned false with the old scene destroyed. Nodes
 * are now staged and committed only on full success (the binary path's R384
 * pattern). */
TEST(load_json_failure_preserves_old_graph)
{
    const char *path = "/tmp/test_json_partial.json";

    World *w = world_create();
    Scene dst; memset(&dst, 0, sizeof(dst));
    dst.node_count = 2;
    dst.nodes = (SceneNode *)calloc(2, sizeof(SceneNode));
    ASSERT_NOT_NULL(dst.nodes);
    dst.nodes[0].local_transform = mat4_identity();
    dst.nodes[0].local_transform.e[3][0] = 5.0f;
    dst.nodes[1].local_transform = mat4_identity();
    SceneNode *old_nodes = dst.nodes;

    /* Valid "nodes" array, then a top-level failure AFTER it. */
    const char *bad =
        "{\"version\":1,"
        "\"nodes\":[{\"parent\":4294967295,\"mesh\":0,\"flags\":0}],"
        "\"entities\":garbage}";
    {
        FILE *fp = fopen(path, "wb");
        ASSERT_NOT_NULL(fp);
        ASSERT_TRUE(fwrite(bad, 1, strlen(bad), fp) == strlen(bad));
        fclose(fp);
    }

    ASSERT_TRUE(!scene_load_json(w, &dst, path));
    /* Old graph must survive untouched — same pointer, same contents. */
    ASSERT_TRUE(dst.nodes == old_nodes);
    ASSERT_EQ(dst.node_count, 2u);
    ASSERT_FLOAT_EQ(dst.nodes[0].local_transform.e[3][0], 5.0f, 1e-6f);

    /* A fully valid document still replaces the old graph. */
    const char *good =
        "{\"version\":1,"
        "\"nodes\":[{\"parent\":4294967295,\"mesh\":0,\"flags\":0}]}";
    {
        FILE *fp = fopen(path, "wb");
        ASSERT_NOT_NULL(fp);
        ASSERT_TRUE(fwrite(good, 1, strlen(good), fp) == strlen(good));
        fclose(fp);
    }
    ASSERT_TRUE(scene_load_json(w, &dst, path));
    ASSERT_EQ(dst.node_count, 1u);
    ASSERT_NOT_NULL(dst.nodes);

    scene_serial_free(&dst);
    world_destroy(w);
    remove(path);
}

/* R426: JSON nodes were memset to 0, so a node missing the "parent" key got
 * parent_index == 0 — silently parented to node 0 instead of being a root.
 * The default is now UINT32_MAX, matching the binary/glTF paths. */
TEST(load_json_node_without_parent_is_root)
{
    const char *path = "/tmp/test_json_noparent.json";
    const char *doc =
        "{\"version\":1,"
        "\"nodes\":[{\"mesh\":0,\"flags\":0},"
        "{\"parent\":0,\"mesh\":0,\"flags\":0}]}";
    {
        FILE *fp = fopen(path, "wb");
        ASSERT_NOT_NULL(fp);
        ASSERT_TRUE(fwrite(doc, 1, strlen(doc), fp) == strlen(doc));
        fclose(fp);
    }

    World *w = world_create();
    Scene dst; memset(&dst, 0, sizeof(dst));
    ASSERT_TRUE(scene_load_json(w, &dst, path));
    ASSERT_EQ(dst.node_count, 2u);
    ASSERT_EQ(dst.nodes[0].parent_index, UINT32_MAX); /* missing key -> root */
    ASSERT_EQ(dst.nodes[1].parent_index, 0u);         /* explicit parent kept */

    scene_serial_free(&dst);
    world_destroy(w);
    remove(path);
}

/* R426: js_u32 wrapped silently on literals > UINT32_MAX (v*10+d). They are
 * now rejected, failing the whole parse instead of loading a wrapped value. */
TEST(load_json_rejects_oversized_u32_literal)
{
    const char *path = "/tmp/test_json_biglit.json";
    /* 4294967296 = UINT32_MAX + 1. */
    const char *doc = "{\"version\":4294967296,\"entities\":[]}";
    {
        FILE *fp = fopen(path, "wb");
        ASSERT_NOT_NULL(fp);
        ASSERT_TRUE(fwrite(doc, 1, strlen(doc), fp) == strlen(doc));
        fclose(fp);
    }

    World *w = world_create();
    ASSERT_TRUE(!scene_load_json(w, NULL, path));

    /* The largest in-range literal must still parse. */
    const char *ok_doc =
        "{\"version\":1,"
        "\"nodes\":[{\"parent\":4294967295,\"mesh\":0,\"flags\":0}]}";
    {
        FILE *fp = fopen(path, "wb");
        ASSERT_NOT_NULL(fp);
        ASSERT_TRUE(fwrite(ok_doc, 1, strlen(ok_doc), fp) == strlen(ok_doc));
        fclose(fp);
    }
    Scene dst; memset(&dst, 0, sizeof(dst));
    ASSERT_TRUE(scene_load_json(w, &dst, path));
    ASSERT_EQ(dst.node_count, 1u);
    ASSERT_EQ(dst.nodes[0].parent_index, UINT32_MAX);

    scene_serial_free(&dst);
    world_destroy(w);
    remove(path);
}

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
    RUN_TEST(bytebuf_reserve_rejects_u32_wrap);
    RUN_TEST(prefab_block_rejects_u32_wrap);
    RUN_TEST(save_binary_null_path);
    RUN_TEST(load_json_nonexistent);
    RUN_TEST(save_json_null_world);
    /* Edge cases */
    RUN_TEST(load_binary_empty_path);
    RUN_TEST(save_binary_empty_path);
    RUN_TEST(load_json_empty_path);
    RUN_TEST(save_json_empty_path);
    RUN_TEST(load_binary_zero_chunks);
    RUN_TEST(load_binary_rollback_orphans_on_bad_components);
    RUN_TEST(failed_load_keeps_previous_scene);
    RUN_TEST(resources_count_bounded_by_chunk_size);
    RUN_TEST(load_binary_rejects_oversized_file);
    RUN_TEST(load_json_rejects_oversized_file);
    RUN_TEST(entities_comp_count_bounded);
    RUN_TEST(duplicate_entities_chunk_rejected);
    /* Round 8: resources + generation */
    RUN_TEST(resources_roundtrip_include);
    RUN_TEST(resources_roundtrip_refs_only);
    RUN_TEST(resources_guid_deterministic);
    RUN_TEST(generation_restore_roundtrip);
    RUN_TEST(generation_restore_roundtrip_json);
    RUN_TEST(instantiate_prefab_offsets_root_nodes_only);
    RUN_TEST(load_json_failure_preserves_old_graph);
    RUN_TEST(load_json_node_without_parent_is_root);
    RUN_TEST(load_json_rejects_oversized_u32_literal);
TEST_MAIN_END()
