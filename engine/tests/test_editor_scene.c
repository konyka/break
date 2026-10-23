/* Stage 4 scene editor Phase 1 Task 2: BreakEditorDoc scene save/load tests.
 *
 * Covers the brief checkboxes: BSCN + sidecar round-trip (names, generations,
 * component bytes), missing/corrupt/oversize sidecar fallback to generated
 * `entity_<index>_<generation>` names + warning, dirty semantics (cleared on
 * save; load result depends on whether any fallback name was used), bounded
 * rejection (4 MiB sidecar cap, >127-byte sidecar names, >64 MiB BSCN via
 * scene_serial's own cap, over-cap paths), OOM injection on the sidecar read
 * buffer, no-partial-save tmp+rename behavior, and "load clears the undo
 * stack / failed load keeps it". */

#include "test_framework.h"

#include <editor/editor_doc.h>
#include <editor/editor_cmd.h>
#include <editor/editor_scene.h>
#include <editor/editor_test_hooks.h>

#include <ecs/ecs.h>
#include <scene/scene_serial.h>

#include <stdio.h>
#include <string.h>

/* Test-local transform component (Task 3 owns the real registry). The doc's
 * World has no components registered by default; the shell/test registers
 * through the borrowed World* (shell-only escape hatch). */
typedef struct {
    f32 pos[3];
    f32 rot[3];
    f32 scale[3];
} TestTransform; /* 36 bytes */

#define TEST_COMP_TRANSFORM 42u

static Entity to_ecs(BreakEditorEntityId id) {
    Entity e;
    e.index = id.index;
    e.generation = id.generation;
    return e;
}

static World *doc_world(BreakEditorDoc *doc) {
    return (World *)break_editor_doc_world(doc);
}

static BreakEditorDoc *make_doc_with_transform(void) {
    BreakEditorDoc *doc = break_editor_doc_create();
    if (!doc) return NULL;
    world_register_component(doc_world(doc), TEST_COMP_TRANSFORM,
                             (u32)sizeof(TestTransform));
    return doc;
}

static bool put_transform(BreakEditorDoc *doc, BreakEditorEntityId id,
                          f32 base) {
    TestTransform *t =
        world_add_component(doc_world(doc), to_ecs(id), TEST_COMP_TRANSFORM);
    if (!t) return false;
    for (u32 i = 0; i < 3; i++) {
        t->pos[i] = base + (f32)i;
        t->rot[i] = base + 10.0f + (f32)i;
        t->scale[i] = base + 20.0f + (f32)i;
    }
    return true;
}

static bool transform_equals(BreakEditorDoc *doc, BreakEditorEntityId id,
                             f32 base) {
    const TestTransform *t =
        world_get_component(doc_world(doc), to_ecs(id), TEST_COMP_TRANSFORM);
    if (!t) return false;
    for (u32 i = 0; i < 3; i++) {
        if (t->pos[i] != base + (f32)i) return false;
        if (t->rot[i] != base + 10.0f + (f32)i) return false;
        if (t->scale[i] != base + 20.0f + (f32)i) return false;
    }
    return true;
}

static bool file_exists(const char *path) {
    FILE *fp = fopen(path, "rb");
    if (!fp) return false;
    fclose(fp);
    return true;
}

static bool write_text_file(const char *path, const char *text) {
    FILE *fp = fopen(path, "wb");
    if (!fp) return false;
    usize n = strlen(text);
    bool ok = fwrite(text, 1, n, fp) == n;
    if (fclose(fp) != 0) ok = false;
    return ok;
}

static void sidecar_path_of(const char *bscn, char *out, usize cap) {
    snprintf(out, cap, "%s%s", bscn, BREAK_EDITOR_SIDECAR_SUFFIX);
}

TEST(save_load_round_trip_names_generations_components) {
    char path[512];
    test_tmp(path, sizeof(path), "editor_scene_rt.bscn");
    char sidecar[600];
    sidecar_path_of(path, sidecar, sizeof(sidecar));

    BreakEditorDoc *doc = make_doc_with_transform();
    ASSERT_NOT_NULL(doc);
    BreakEditorEntityId a = break_editor_doc_add_entity(doc, "alpha");
    BreakEditorEntityId b = break_editor_doc_add_entity(doc, "beta");
    BreakEditorEntityId c = break_editor_doc_add_entity(doc, "gamma");
    ASSERT_TRUE(break_editor_entity_id_valid(a));
    ASSERT_TRUE(break_editor_entity_id_valid(b));
    ASSERT_TRUE(break_editor_entity_id_valid(c));
    ASSERT_TRUE(put_transform(doc, a, 1.0f));
    ASSERT_TRUE(put_transform(doc, b, 2.0f));
    /* c intentionally has no transform: sparse components round-trip too. */

    ASSERT_TRUE(break_editor_doc_save(doc, path));
    /* Save clears dirty, does NOT clear the undo stack (save is not a
     * mutation). */
    ASSERT_FALSE(break_editor_doc_is_dirty(doc));
    ASSERT_TRUE(file_exists(path));
    ASSERT_TRUE(file_exists(sidecar));
    ASSERT_TRUE(scene_probe_binary(path));
    /* tmp+rename: no staging files left behind. */
    char tmp[640];
    snprintf(tmp, sizeof(tmp), "%s.tmp", path);
    ASSERT_FALSE(file_exists(tmp));
    snprintf(tmp, sizeof(tmp), "%s.tmp", sidecar);
    ASSERT_FALSE(file_exists(tmp));

    break_editor_doc_destroy(doc);

    BreakEditorDoc *doc2 = make_doc_with_transform();
    ASSERT_NOT_NULL(doc2);
    ASSERT_TRUE(break_editor_doc_load(doc2, path));
    ASSERT_EQ(break_editor_doc_entity_count(doc2), 3u);
    /* No holes in the saved doc => ids round-trip exactly. */
    BreakEditorEntityId id;
    const char *name = NULL;
    ASSERT_TRUE(break_editor_doc_entity_at(doc2, 0, &id, &name));
    ASSERT_TRUE(break_editor_entity_id_eq(id, a));
    ASSERT_STR_EQ(name, "alpha");
    ASSERT_TRUE(break_editor_doc_entity_at(doc2, 1, &id, &name));
    ASSERT_TRUE(break_editor_entity_id_eq(id, b));
    ASSERT_STR_EQ(name, "beta");
    ASSERT_TRUE(break_editor_doc_entity_at(doc2, 2, &id, &name));
    ASSERT_TRUE(break_editor_entity_id_eq(id, c));
    ASSERT_STR_EQ(name, "gamma");
    /* Component payloads byte-equal. */
    ASSERT_TRUE(transform_equals(doc2, a, 1.0f));
    ASSERT_TRUE(transform_equals(doc2, b, 2.0f));
    ASSERT_TRUE(world_get_component(doc_world(doc2), to_ecs(c),
                                    TEST_COMP_TRANSFORM) == NULL);
    /* Full sidecar match => loaded state == on-disk state => clean. */
    ASSERT_FALSE(break_editor_doc_is_dirty(doc2));

    break_editor_doc_destroy(doc2);
    remove(path);
    remove(sidecar);
}

TEST(round_trip_with_destroyed_hole_compacts_indices_but_keeps_names) {
    /* Documented compaction: BSCN stores entities densely (ascending order,
     * no index field), so loading re-creates dense indices 1..n and only
     * generations survive per entity. The sidecar's {index,generation} key
     * is the dense (post-load) id, so names follow entities through the
     * compaction. */
    char path[512];
    test_tmp(path, sizeof(path), "editor_scene_hole.bscn");
    char sidecar[600];
    sidecar_path_of(path, sidecar, sizeof(sidecar));

    BreakEditorDoc *doc = make_doc_with_transform();
    ASSERT_NOT_NULL(doc);
    BreakEditorEntityId a = break_editor_doc_add_entity(doc, "alpha");
    BreakEditorEntityId b = break_editor_doc_add_entity(doc, "beta");
    BreakEditorEntityId c = break_editor_doc_add_entity(doc, "gamma");
    ASSERT_TRUE(put_transform(doc, a, 1.0f));
    ASSERT_TRUE(put_transform(doc, c, 3.0f));
    ASSERT_TRUE(break_editor_doc_remove_entity(doc, b)); /* hole at index 2 */
    u32 gen_c = c.generation;

    ASSERT_TRUE(break_editor_doc_save(doc, path));
    break_editor_doc_destroy(doc);

    BreakEditorDoc *doc2 = make_doc_with_transform();
    ASSERT_NOT_NULL(doc2);
    ASSERT_TRUE(break_editor_doc_load(doc2, path));
    ASSERT_EQ(break_editor_doc_entity_count(doc2), 2u);
    BreakEditorEntityId id;
    const char *name = NULL;
    /* alpha stays {1,1}; gamma's generation survives but its index compacts
     * from 3 to 2. */
    ASSERT_TRUE(break_editor_doc_entity_at(doc2, 0, &id, &name));
    ASSERT_EQ(id.index, 1u);
    ASSERT_EQ(id.generation, 1u);
    ASSERT_STR_EQ(name, "alpha");
    ASSERT_TRUE(break_editor_doc_entity_at(doc2, 1, &id, &name));
    ASSERT_EQ(id.index, 2u);
    ASSERT_EQ(id.generation, gen_c);
    ASSERT_STR_EQ(name, "gamma");
    /* Component bytes follow the same entity. */
    ASSERT_TRUE(transform_equals(doc2, id, 3.0f));
    ASSERT_FALSE(break_editor_doc_is_dirty(doc2));

    break_editor_doc_destroy(doc2);
    remove(path);
    remove(sidecar);
}

TEST(load_missing_sidecar_generates_names) {
    char path[512];
    test_tmp(path, sizeof(path), "editor_scene_nosc.bscn");
    char sidecar[600];
    sidecar_path_of(path, sidecar, sizeof(sidecar));

    BreakEditorDoc *doc = break_editor_doc_create();
    ASSERT_NOT_NULL(doc);
    BreakEditorEntityId a = break_editor_doc_add_entity(doc, "alpha");
    BreakEditorEntityId b = break_editor_doc_add_entity(doc, "beta");
    ASSERT_TRUE(break_editor_doc_save(doc, path));
    break_editor_doc_destroy(doc);
    ASSERT_EQ(remove(sidecar), 0);

    BreakEditorDoc *doc2 = break_editor_doc_create();
    ASSERT_NOT_NULL(doc2);
    ASSERT_TRUE(break_editor_doc_load(doc2, path));
    ASSERT_EQ(break_editor_doc_entity_count(doc2), 2u);
    char expect[64];
    const char *name = NULL;
    BreakEditorEntityId id;
    snprintf(expect, sizeof(expect), "entity_%u_%u", a.index, a.generation);
    ASSERT_TRUE(break_editor_doc_entity_at(doc2, 0, &id, &name));
    ASSERT_STR_EQ(name, expect);
    snprintf(expect, sizeof(expect), "entity_%u_%u", b.index, b.generation);
    ASSERT_TRUE(break_editor_doc_entity_at(doc2, 1, &id, &name));
    ASSERT_STR_EQ(name, expect);
    /* Fallback names are not on disk => doc differs from disk => dirty. */
    ASSERT_TRUE(break_editor_doc_is_dirty(doc2));

    break_editor_doc_destroy(doc2);
    remove(path);
}

TEST(load_corrupt_sidecar_falls_back_but_load_succeeds) {
    char path[512];
    test_tmp(path, sizeof(path), "editor_scene_corrupt.bscn");
    char sidecar[600];
    sidecar_path_of(path, sidecar, sizeof(sidecar));

    BreakEditorDoc *doc = break_editor_doc_create();
    ASSERT_NOT_NULL(doc);
    ASSERT_TRUE(break_editor_entity_id_valid(
        break_editor_doc_add_entity(doc, "alpha")));
    ASSERT_TRUE(break_editor_doc_save(doc, path));
    break_editor_doc_destroy(doc);

    ASSERT_TRUE(write_text_file(sidecar, "this is not json {{{"));

    BreakEditorDoc *doc2 = break_editor_doc_create();
    ASSERT_NOT_NULL(doc2);
    ASSERT_TRUE(break_editor_doc_load(doc2, path)); /* load still succeeds */
    ASSERT_EQ(break_editor_doc_entity_count(doc2), 1u);
    BreakEditorEntityId id;
    const char *name = NULL;
    ASSERT_TRUE(break_editor_doc_entity_at(doc2, 0, &id, &name));
    ASSERT_STR_EQ(name, "entity_1_1");
    ASSERT_TRUE(break_editor_doc_is_dirty(doc2));

    break_editor_doc_destroy(doc2);
    remove(path);
    remove(sidecar);
}

TEST(load_sidecar_oversize_name_skips_only_that_entry) {
    char path[512];
    test_tmp(path, sizeof(path), "editor_scene_big_name.bscn");
    char sidecar[600];
    sidecar_path_of(path, sidecar, sizeof(sidecar));

    BreakEditorDoc *doc = break_editor_doc_create();
    ASSERT_NOT_NULL(doc);
    break_editor_doc_add_entity(doc, "alpha");
    break_editor_doc_add_entity(doc, "beta");
    break_editor_doc_add_entity(doc, "gamma");
    ASSERT_TRUE(break_editor_doc_save(doc, path));
    break_editor_doc_destroy(doc);

    /* Hand-craft a sidecar: entry 1 carries a 200-byte name (> 127-byte cap)
     * => bounded-rejected (skipped), later entries still apply. */
    char big[1024];
    int n = snprintf(big, sizeof(big),
                     "{\"version\":1,\"entities\":[{\"index\":1,\"generation\":1,"
                     "\"name\":\"");
    ASSERT_TRUE(n > 0);
    memset(big + n, 'a', 200);
    n += 200;
    snprintf(big + n, sizeof(big) - (usize)n,
             "\"},{\"index\":2,\"generation\":1,\"name\":\"two\"},"
             "{\"index\":3,\"generation\":1,\"name\":\"three\"}]}");
    ASSERT_TRUE(write_text_file(sidecar, big));

    BreakEditorDoc *doc2 = break_editor_doc_create();
    ASSERT_NOT_NULL(doc2);
    ASSERT_TRUE(break_editor_doc_load(doc2, path));
    ASSERT_EQ(break_editor_doc_entity_count(doc2), 3u);
    BreakEditorEntityId id;
    const char *name = NULL;
    ASSERT_TRUE(break_editor_doc_entity_at(doc2, 0, &id, &name));
    ASSERT_STR_EQ(name, "entity_1_1"); /* skipped => generated */
    ASSERT_TRUE(break_editor_doc_entity_at(doc2, 1, &id, &name));
    ASSERT_STR_EQ(name, "two");
    ASSERT_TRUE(break_editor_doc_entity_at(doc2, 2, &id, &name));
    ASSERT_STR_EQ(name, "three");
    ASSERT_TRUE(break_editor_doc_is_dirty(doc2)); /* a fallback was used */

    break_editor_doc_destroy(doc2);
    remove(path);
    remove(sidecar);
}

TEST(load_oversize_sidecar_file_falls_back) {
    char path[512];
    test_tmp(path, sizeof(path), "editor_scene_bigsc.bscn");
    char sidecar[600];
    sidecar_path_of(path, sidecar, sizeof(sidecar));

    BreakEditorDoc *doc = break_editor_doc_create();
    ASSERT_NOT_NULL(doc);
    break_editor_doc_add_entity(doc, "alpha");
    ASSERT_TRUE(break_editor_doc_save(doc, path));
    break_editor_doc_destroy(doc);

    /* 4 MiB + 1 sidecar: rejected by the editor's own bounded read. */
    FILE *fp = fopen(sidecar, "wb");
    ASSERT_NOT_NULL(fp);
    ASSERT_EQ(fseek(fp, (long)BREAK_EDITOR_SIDECAR_MAX_BYTES, SEEK_SET), 0);
    ASSERT_EQ(fputc(0, fp), 0);
    ASSERT_EQ(fclose(fp), 0);

    BreakEditorDoc *doc2 = break_editor_doc_create();
    ASSERT_NOT_NULL(doc2);
    ASSERT_TRUE(break_editor_doc_load(doc2, path));
    ASSERT_EQ(break_editor_doc_entity_count(doc2), 1u);
    BreakEditorEntityId id;
    const char *name = NULL;
    ASSERT_TRUE(break_editor_doc_entity_at(doc2, 0, &id, &name));
    ASSERT_STR_EQ(name, "entity_1_1");
    ASSERT_TRUE(break_editor_doc_is_dirty(doc2));

    break_editor_doc_destroy(doc2);
    remove(path);
    remove(sidecar);
}

TEST(load_replaces_previous_contents) {
    char path[512];
    test_tmp(path, sizeof(path), "editor_scene_replace.bscn");
    char sidecar[600];
    sidecar_path_of(path, sidecar, sizeof(sidecar));

    BreakEditorDoc *src = break_editor_doc_create();
    ASSERT_NOT_NULL(src);
    break_editor_doc_add_entity(src, "one");
    break_editor_doc_add_entity(src, "two");
    ASSERT_TRUE(break_editor_doc_save(src, path));
    break_editor_doc_destroy(src);

    BreakEditorDoc *doc = break_editor_doc_create();
    ASSERT_NOT_NULL(doc);
    for (int i = 0; i < 5; i++) break_editor_doc_add_entity(doc, "old");
    ASSERT_EQ(break_editor_doc_entity_count(doc), 5u);

    ASSERT_TRUE(break_editor_doc_load(doc, path));
    ASSERT_EQ(break_editor_doc_entity_count(doc), 2u);
    const char *name = NULL;
    BreakEditorEntityId id;
    ASSERT_TRUE(break_editor_doc_entity_at(doc, 0, &id, &name));
    ASSERT_STR_EQ(name, "one");
    ASSERT_TRUE(break_editor_doc_entity_at(doc, 1, &id, &name));
    ASSERT_STR_EQ(name, "two");
    /* Full sidecar match: loaded doc is clean even though it was dirty. */
    ASSERT_FALSE(break_editor_doc_is_dirty(doc));

    break_editor_doc_destroy(doc);
    remove(path);
    remove(sidecar);
}

TEST(failed_load_leaves_doc_unchanged) {
    char path[512];
    test_tmp(path, sizeof(path), "editor_scene_missing.bscn"); /* never created */

    BreakEditorDoc *doc = break_editor_doc_create();
    ASSERT_NOT_NULL(doc);
    break_editor_doc_add_entity(doc, "alpha");
    break_editor_doc_add_entity(doc, "beta");
    ASSERT_TRUE(break_editor_doc_is_dirty(doc));

    ASSERT_FALSE(break_editor_doc_load(doc, path));
    ASSERT_EQ(break_editor_doc_entity_count(doc), 2u);
    ASSERT_TRUE(break_editor_doc_is_dirty(doc));
    const char *name = NULL;
    BreakEditorEntityId id;
    ASSERT_TRUE(break_editor_doc_entity_at(doc, 0, &id, &name));
    ASSERT_STR_EQ(name, "alpha");
    /* Undo history untouched by the failed load. */
    ASSERT_TRUE(break_editor_undo(doc));
    ASSERT_EQ(break_editor_doc_entity_count(doc), 1u);

    /* A present-but-invalid BSCN also fails without mutation. */
    ASSERT_TRUE(write_text_file(path, "BSCN but not really a scene"));
    ASSERT_FALSE(scene_probe_binary(path));
    ASSERT_FALSE(break_editor_doc_load(doc, path));
    ASSERT_EQ(break_editor_doc_entity_count(doc), 1u);

    break_editor_doc_destroy(doc);
    remove(path);
}

TEST(load_clears_undo_stack_save_does_not) {
    char path[512];
    test_tmp(path, sizeof(path), "editor_scene_undo.bscn");
    char sidecar[600];
    sidecar_path_of(path, sidecar, sizeof(sidecar));

    BreakEditorDoc *doc = break_editor_doc_create();
    ASSERT_NOT_NULL(doc);
    break_editor_doc_add_entity(doc, "alpha");
    break_editor_doc_add_entity(doc, "beta");
    BreakEditorCmdStack *stack = break_editor_doc_stack(doc);
    ASSERT_NOT_NULL(stack);
    ASSERT_EQ(break_editor_cmd_stack_undo_count(stack), 2u);

    ASSERT_TRUE(break_editor_doc_save(doc, path));
    /* Save is not a mutation: history survives it. */
    ASSERT_EQ(break_editor_cmd_stack_undo_count(stack), 2u);

    ASSERT_TRUE(break_editor_doc_load(doc, path));
    /* Documented semantics: a successful load clears the undo/redo history
     * (the commands reference the pre-load world, which no longer exists). */
    ASSERT_EQ(break_editor_cmd_stack_size(stack), 0u);
    ASSERT_EQ(break_editor_cmd_stack_undo_count(stack), 0u);
    ASSERT_EQ(break_editor_cmd_stack_redo_count(stack), 0u);
    ASSERT_FALSE(break_editor_undo(doc));
    ASSERT_FALSE(break_editor_redo(doc));

    break_editor_doc_destroy(doc);
    remove(path);
    remove(sidecar);
}

TEST(oversize_bscn_rejected_by_scene_serial_cap) {
    char path[512];
    test_tmp(path, sizeof(path), "editor_scene_huge.bscn");

    /* 64 MiB + 1 sparse file with a plausible magic: scene_serial's own
     * BSCN_MAX_FILE_BYTES gate (verify, don't re-implement). */
    FILE *fp = fopen(path, "wb");
    ASSERT_NOT_NULL(fp);
    u32 magic = BSCN_MAGIC;
    ASSERT_EQ(fwrite(&magic, 1, sizeof(magic), fp), sizeof(magic));
    ASSERT_EQ(fseek(fp, (long)BSCN_MAX_FILE_BYTES, SEEK_SET), 0);
    ASSERT_EQ(fputc(0, fp), 0);
    ASSERT_EQ(fclose(fp), 0);

    ASSERT_FALSE(scene_probe_binary(path));

    BreakEditorDoc *doc = break_editor_doc_create();
    ASSERT_NOT_NULL(doc);
    break_editor_doc_add_entity(doc, "alpha");
    ASSERT_FALSE(break_editor_doc_load(doc, path));
    ASSERT_EQ(break_editor_doc_entity_count(doc), 1u);
    ASSERT_TRUE(break_editor_doc_is_dirty(doc));

    break_editor_doc_destroy(doc);
    remove(path);
}

TEST(save_to_unwritable_path_fails_bounded) {
    char path[512];
    test_tmp(path, sizeof(path), "editor_scene_nowrite/x.bscn");
    /* The parent directory never exists => tmp-file fopen fails. */
    char sidecar[600];
    sidecar_path_of(path, sidecar, sizeof(sidecar));
    char tmp[640];

    BreakEditorDoc *doc = break_editor_doc_create();
    ASSERT_NOT_NULL(doc);
    break_editor_doc_add_entity(doc, "alpha");
    ASSERT_TRUE(break_editor_doc_is_dirty(doc));

    ASSERT_FALSE(break_editor_doc_save(doc, path));
    ASSERT_TRUE(break_editor_doc_is_dirty(doc)); /* unchanged on failure */
    ASSERT_FALSE(file_exists(path));
    ASSERT_FALSE(file_exists(sidecar));
    snprintf(tmp, sizeof(tmp), "%s.tmp", path);
    ASSERT_FALSE(file_exists(tmp));
    snprintf(tmp, sizeof(tmp), "%s.tmp", sidecar);
    ASSERT_FALSE(file_exists(tmp));

    break_editor_doc_destroy(doc);
}

TEST(save_sidecar_over_cap_fails_bounded) {
    /* Worst-case sidecar growth: names of 127 '"' characters escape to 254
     * bytes each; ~300 bytes/entry crosses the 4 MiB sidecar cap near 14.1k
     * entities, so 16000 must fail bounded. The save writes the sidecar
     * BEFORE the BSCN, so a cap failure leaves neither file behind. */
    char path[512];
    test_tmp(path, sizeof(path), "editor_scene_cap.bscn");
    char sidecar[600];
    sidecar_path_of(path, sidecar, sizeof(sidecar));

    char long_name[BREAK_EDITOR_NAME_CAPACITY];
    memset(long_name, '"', BREAK_EDITOR_NAME_CAPACITY - 1u);
    long_name[BREAK_EDITOR_NAME_CAPACITY - 1u] = '\0';

    BreakEditorDoc *doc = break_editor_doc_create();
    ASSERT_NOT_NULL(doc);
    for (u32 i = 0; i < 16000; i++) {
        ASSERT_TRUE(break_editor_entity_id_valid(
            break_editor_doc_add_entity(doc, long_name)));
    }
    ASSERT_TRUE(break_editor_doc_is_dirty(doc));

    ASSERT_FALSE(break_editor_doc_save(doc, path));
    ASSERT_TRUE(break_editor_doc_is_dirty(doc)); /* failure keeps dirty */
    ASSERT_FALSE(file_exists(path));
    ASSERT_FALSE(file_exists(sidecar));

    break_editor_doc_destroy(doc);
}

TEST(oom_injection_on_sidecar_read_buffer) {
    char path[512];
    test_tmp(path, sizeof(path), "editor_scene_oom.bscn");
    char sidecar[600];
    sidecar_path_of(path, sidecar, sizeof(sidecar));

    BreakEditorDoc *doc = break_editor_doc_create();
    ASSERT_NOT_NULL(doc);
    break_editor_doc_add_entity(doc, "alpha");

    /* Save performs NO editor-owned allocation (streaming stdio): it
     * succeeds even with a zero budget. */
    break_editor_test_set_alloc_budget(0);
    bool save_ok = break_editor_doc_save(doc, path);
    break_editor_test_set_alloc_budget(BREAK_EDITOR_TEST_ALLOC_DISABLED);
    ASSERT_TRUE(save_ok);
    break_editor_doc_destroy(doc);

    /* The load path's only editor-owned allocation is the sidecar read
     * buffer; its failure degrades to the same bounded fallback as a
     * missing/corrupt sidecar (load still succeeds). */
    BreakEditorDoc *doc2 = break_editor_doc_create();
    ASSERT_NOT_NULL(doc2);
    break_editor_test_set_alloc_budget(0);
    bool load_ok = break_editor_doc_load(doc2, path);
    break_editor_test_set_alloc_budget(BREAK_EDITOR_TEST_ALLOC_DISABLED);
    ASSERT_TRUE(load_ok);
    ASSERT_EQ(break_editor_doc_entity_count(doc2), 1u);
    BreakEditorEntityId id;
    const char *name = NULL;
    ASSERT_TRUE(break_editor_doc_entity_at(doc2, 0, &id, &name));
    ASSERT_STR_EQ(name, "entity_1_1");
    ASSERT_TRUE(break_editor_doc_is_dirty(doc2));

    break_editor_doc_destroy(doc2);
    remove(path);
    remove(sidecar);
}

TEST(null_and_bad_args_fail_bounded) {
    char path[512];
    test_tmp(path, sizeof(path), "editor_scene_args.bscn");

    BreakEditorDoc *doc = break_editor_doc_create();
    ASSERT_NOT_NULL(doc);
    break_editor_doc_add_entity(doc, "alpha");

    ASSERT_FALSE(break_editor_doc_save(NULL, path));
    ASSERT_FALSE(break_editor_doc_save(doc, NULL));
    ASSERT_FALSE(break_editor_doc_load(NULL, path));
    ASSERT_FALSE(break_editor_doc_load(doc, NULL));

    /* Over-cap path (> BREAK_EDITOR_SCENE_PATH_CAPACITY with suffixes):
     * bounded false, doc unchanged. */
    char long_path[2100];
    memset(long_path, 'a', sizeof(long_path) - 1u);
    long_path[sizeof(long_path) - 1u] = '\0';
    ASSERT_FALSE(break_editor_doc_save(doc, long_path));
    ASSERT_FALSE(break_editor_doc_load(doc, long_path));
    ASSERT_EQ(break_editor_doc_entity_count(doc), 1u);
    ASSERT_TRUE(break_editor_doc_is_dirty(doc));

    break_editor_doc_destroy(doc);
}

TEST(empty_doc_round_trip) {
    char path[512];
    test_tmp(path, sizeof(path), "editor_scene_empty.bscn");
    char sidecar[600];
    sidecar_path_of(path, sidecar, sizeof(sidecar));

    BreakEditorDoc *doc = break_editor_doc_create();
    ASSERT_NOT_NULL(doc);
    ASSERT_TRUE(break_editor_doc_save(doc, path)); /* never dirty: still fine */
    break_editor_doc_destroy(doc);

    BreakEditorDoc *doc2 = break_editor_doc_create();
    ASSERT_NOT_NULL(doc2);
    for (int i = 0; i < 3; i++) break_editor_doc_add_entity(doc2, "x");
    ASSERT_TRUE(break_editor_doc_load(doc2, path));
    ASSERT_EQ(break_editor_doc_entity_count(doc2), 0u);
    ASSERT_FALSE(break_editor_doc_is_dirty(doc2));
    ASSERT_FALSE(break_editor_undo(doc2)); /* stack cleared */

    break_editor_doc_destroy(doc2);
    remove(path);
    remove(sidecar);
}

TEST_MAIN_BEGIN()
    RUN_TEST(save_load_round_trip_names_generations_components);
    RUN_TEST(round_trip_with_destroyed_hole_compacts_indices_but_keeps_names);
    RUN_TEST(load_missing_sidecar_generates_names);
    RUN_TEST(load_corrupt_sidecar_falls_back_but_load_succeeds);
    RUN_TEST(load_sidecar_oversize_name_skips_only_that_entry);
    RUN_TEST(load_oversize_sidecar_file_falls_back);
    RUN_TEST(load_replaces_previous_contents);
    RUN_TEST(failed_load_leaves_doc_unchanged);
    RUN_TEST(load_clears_undo_stack_save_does_not);
    RUN_TEST(oversize_bscn_rejected_by_scene_serial_cap);
    RUN_TEST(save_to_unwritable_path_fails_bounded);
    RUN_TEST(save_sidecar_over_cap_fails_bounded);
    RUN_TEST(oom_injection_on_sidecar_read_buffer);
    RUN_TEST(null_and_bad_args_fail_bounded);
    RUN_TEST(empty_doc_round_trip);
TEST_MAIN_END()
