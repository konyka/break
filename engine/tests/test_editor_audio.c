/* Editor PCM attachments: lifecycle, exact snapshot undo/redo, origin
 * conflicts, bounded history and allocation-failure atomicity. */
#include "test_framework.h"

#include <audio/audio_edit.h>
#include <editor/editor_audio.h>
#include <editor/editor_cmd.h>
#include <editor/editor_scene.h>
#include <editor/editor_test_hooks.h>

#include <math.h>
#include <stdio.h>
#include <string.h>

static const i16 kSamples[8] = {0, 100, 200, 300, 400, 500, 600, 700};

static void assert_samples(BreakEditorDoc *doc, const i16 *expected, u32 frames) {
    ASSERT_EQ(break_editor_doc_audio_frames(doc), frames);
    ASSERT_EQ(memcmp(break_editor_doc_audio_samples(doc), expected, sizeof(i16) * frames), 0);
}

TEST(attach_validation_and_reset_or_load_detach)
{
    BreakEditorDoc *doc = break_editor_doc_create();
    ASSERT_NOT_NULL(doc);
    ASSERT_TRUE(!break_editor_doc_audio_attached(doc));
    ASSERT_EQ(break_editor_doc_audio_frames(doc), 0u);
    ASSERT_EQ(break_editor_doc_audio_sample_rate(doc), 0u);
    ASSERT_EQ(break_editor_doc_audio_channels(doc), 0u);
    ASSERT_TRUE(break_editor_doc_audio_samples(doc) == NULL);
    ASSERT_TRUE(!break_editor_doc_audio_attach(NULL, 16000u, 1u, kSamples, 8u));
    ASSERT_TRUE(!break_editor_doc_audio_attach(doc, 0u, 1u, kSamples, 8u));
    ASSERT_TRUE(!break_editor_doc_audio_attach(doc, 16000u, 3u, kSamples, 8u));
    ASSERT_TRUE(!break_editor_doc_audio_attach(doc, 16000u, 1u, NULL, 1u));
    ASSERT_TRUE(!break_editor_doc_audio_attach(doc, 16000u, 1u, kSamples, 65537u));
    ASSERT_TRUE(break_editor_doc_audio_attach(doc, 16000u, 1u, kSamples, 8u));
    ASSERT_TRUE(break_editor_doc_audio_attached(doc));
    ASSERT_EQ(break_editor_doc_audio_sample_rate(doc), 16000u);
    ASSERT_EQ(break_editor_doc_audio_channels(doc), 1u);
    ASSERT_TRUE(break_editor_doc_is_dirty(doc));
    assert_samples(doc, kSamples, 8u);
    ASSERT_TRUE(!break_editor_doc_audio_attach(doc, 16000u, 1u, kSamples, 8u));
    assert_samples(doc, kSamples, 8u);
    ASSERT_TRUE(break_editor_doc_reset(doc));
    ASSERT_TRUE(!break_editor_doc_audio_attached(doc));
    ASSERT_TRUE(!break_editor_doc_is_dirty(doc));

    ASSERT_TRUE(break_editor_doc_audio_attach(doc, 16000u, 1u, kSamples, 8u));
    char path[512], sidecar[600];
    test_tmp(path, sizeof(path), "editor_audio");
    snprintf(sidecar, sizeof(sidecar), "%s.editor.json", path);
    remove(path);
    remove(sidecar);
    ASSERT_TRUE(break_editor_doc_save(doc, path));
    ASSERT_TRUE(break_editor_doc_load(doc, path));
    ASSERT_TRUE(!break_editor_doc_audio_attached(doc));
    remove(path);
    remove(sidecar);
    break_editor_doc_destroy(doc);
}

TEST(trim_and_cut_are_byte_exact_undoable_commands)
{
    BreakEditorDoc *doc = break_editor_doc_create();
    ASSERT_NOT_NULL(doc);
    ASSERT_TRUE(break_editor_doc_audio_attach(doc, 16000u, 1u, kSamples, 8u));
    const i16 trimmed[] = {200, 300, 400, 500};
    ASSERT_TRUE(break_editor_doc_audio_trim(doc, 2u, 6u));
    assert_samples(doc, trimmed, 4u);
    ASSERT_EQ(break_editor_cmd_stack_undo_count(break_editor_doc_stack(doc)), 1u);
    ASSERT_TRUE(break_editor_undo(doc));
    assert_samples(doc, kSamples, 8u);
    ASSERT_TRUE(break_editor_redo(doc));
    assert_samples(doc, trimmed, 4u);
    const i16 cut[] = {200, 500};
    ASSERT_TRUE(break_editor_doc_audio_cut(doc, 1u, 3u));
    assert_samples(doc, cut, 2u);
    ASSERT_TRUE(break_editor_undo(doc));
    assert_samples(doc, trimmed, 4u);
    ASSERT_TRUE(break_editor_redo(doc));
    assert_samples(doc, cut, 2u);
    ASSERT_TRUE(break_editor_undo(doc));
    ASSERT_TRUE(break_editor_undo(doc));
    assert_samples(doc, kSamples, 8u);
    ASSERT_TRUE(break_editor_redo(doc));
    ASSERT_TRUE(break_editor_redo(doc));
    assert_samples(doc, cut, 2u);
    break_editor_doc_destroy(doc);
}

TEST(fade_normalize_and_mix_use_real_primitives)
{
    const i16 initial[] = {-1000, 500, 1000, -2000};
    i16 expected[4];
    BreakEditorDoc *doc = break_editor_doc_create();
    ASSERT_NOT_NULL(doc);
    ASSERT_TRUE(break_editor_doc_audio_attach(doc, 16000u, 1u, initial, 4u));
    memcpy(expected, initial, sizeof(initial));
    ASSERT_EQ(audio_edit_fade_i16(expected, 4u, 1u, 16000.0, 1000.0, 1000.0), AUDIO_OK);
    ASSERT_TRUE(break_editor_doc_audio_fade(doc, 1000.0, 1000.0));
    assert_samples(doc, expected, 4u);
    ASSERT_TRUE(break_editor_undo(doc));
    assert_samples(doc, initial, 4u);

    memcpy(expected, initial, sizeof(initial));
    ASSERT_EQ(audio_edit_normalize_i16(expected, 4u, 1u, -6.0), AUDIO_OK);
    ASSERT_TRUE(break_editor_doc_audio_normalize(doc, -6.0));
    assert_samples(doc, expected, 4u);
    ASSERT_TRUE(break_editor_undo(doc));
    ASSERT_TRUE(break_editor_doc_audio_normalize(doc, -12.0));
    ASSERT_TRUE(!break_editor_redo(doc));

    i16 mixed[4], normalized[4];
    memcpy(mixed, break_editor_doc_audio_samples(doc), sizeof(mixed));
    memcpy(normalized, mixed, sizeof(normalized));
    const i16 source[] = {1000, -1000};
    ASSERT_EQ(audio_edit_mix_i16(mixed, 4u, source, 2u, 1u, 0.5), AUDIO_OK);
    ASSERT_TRUE(break_editor_doc_audio_mix(doc, source, 2u, 0.5));
    assert_samples(doc, mixed, 4u);
    ASSERT_TRUE(break_editor_undo(doc));
    assert_samples(doc, normalized, 4u);
    ASSERT_TRUE(break_editor_redo(doc));
    assert_samples(doc, mixed, 4u);
    ASSERT_TRUE(break_editor_doc_is_dirty(doc));
    break_editor_doc_destroy(doc);
}

TEST(origin_conflicts_and_drop_oldest_include_audio)
{
    BreakEditorDoc *doc = break_editor_doc_create();
    ASSERT_NOT_NULL(doc);
    ASSERT_TRUE(break_editor_doc_audio_attach(doc, 16000u, 1u, kSamples, 8u));
    break_editor_doc_set_origin(doc, 1u);
    ASSERT_TRUE(break_editor_doc_audio_trim(doc, 0u, 7u));
    break_editor_doc_set_origin(doc, 2u);
    ASSERT_TRUE(break_editor_entity_id_valid(break_editor_doc_add_entity(doc, "other")));
    ASSERT_EQ(break_editor_undo_origin(doc, 1u), BREAK_EDITOR_ORIGIN_BLOCKED);
    ASSERT_EQ(break_editor_undo_origin(doc, 2u), BREAK_EDITOR_ORIGIN_APPLIED);
    ASSERT_EQ(break_editor_undo_origin(doc, 1u), BREAK_EDITOR_ORIGIN_BLOCKED);
    assert_samples(doc, kSamples, 7u);
    break_editor_doc_destroy(doc);

    doc = break_editor_doc_create();
    ASSERT_NOT_NULL(doc);
    ASSERT_TRUE(break_editor_doc_audio_attach(doc, 16000u, 1u, kSamples, 8u));
    break_editor_doc_set_origin(doc, 7u);
    const i16 expected[] = {100, 200, 300};
    ASSERT_TRUE(break_editor_doc_audio_trim(doc, 1u, 4u));
    ASSERT_EQ(break_editor_undo_origin(doc, 7u), BREAK_EDITOR_ORIGIN_APPLIED);
    assert_samples(doc, kSamples, 8u);
    ASSERT_EQ(break_editor_redo_origin(doc, 7u), BREAK_EDITOR_ORIGIN_APPLIED);
    assert_samples(doc, expected, 3u);
    break_editor_doc_destroy(doc);

    doc = break_editor_doc_create();
    ASSERT_NOT_NULL(doc);
    ASSERT_TRUE(break_editor_doc_audio_attach(doc, 16000u, 1u, kSamples, 1u));
    for (u32 i = 0; i < 257u; ++i) {
        ASSERT_TRUE(break_editor_doc_audio_normalize(doc, -12.0));
    }
    BreakEditorCmdStack *stack = break_editor_doc_stack(doc);
    ASSERT_EQ(break_editor_cmd_stack_size(stack), 256u);
    ASSERT_TRUE(break_editor_cmd_stack_dropped_oldest(stack));
    break_editor_doc_destroy(doc);
}

TEST(invalid_and_oom_failures_are_atomic)
{
    BreakEditorDoc *doc = break_editor_doc_create();
    ASSERT_NOT_NULL(doc);
    ASSERT_TRUE(!break_editor_doc_audio_trim(doc, 0u, 1u));
    ASSERT_TRUE(break_editor_doc_audio_attach(doc, 16000u, 1u, kSamples, 8u));
    BreakEditorCmdStack *stack = break_editor_doc_stack(doc);
    const u64 revision = break_editor_cmd_stack_revision(stack);
    ASSERT_TRUE(!break_editor_doc_audio_trim(doc, 4u, 2u));
    ASSERT_TRUE(!break_editor_doc_audio_cut(doc, 0u, 9u));
    ASSERT_TRUE(!break_editor_doc_audio_fade(doc, NAN, 0.0));
    ASSERT_TRUE(!break_editor_doc_audio_normalize(doc, NAN));
    ASSERT_TRUE(!break_editor_doc_audio_mix(doc, kSamples, 8u, NAN));
    assert_samples(doc, kSamples, 8u);
    ASSERT_EQ(break_editor_cmd_stack_revision(stack), revision);
    break_editor_test_set_alloc_budget(1u);
    ASSERT_TRUE(!break_editor_doc_audio_trim(doc, 4u, 2u));
    const u64 remaining = atomic_load(&g_break_editor_test_alloc_budget);
    break_editor_test_set_alloc_budget(BREAK_EDITOR_TEST_ALLOC_DISABLED);
    ASSERT_EQ(remaining, 1u);
    break_editor_doc_destroy(doc);

    for (u64 budget = 0u; budget < 2u; ++budget) {
        doc = break_editor_doc_create();
        ASSERT_NOT_NULL(doc);
        break_editor_test_set_alloc_budget(budget);
        ASSERT_TRUE(!break_editor_doc_audio_attach(doc, 16000u, 1u, kSamples, 8u));
        break_editor_test_set_alloc_budget(BREAK_EDITOR_TEST_ALLOC_DISABLED);
        ASSERT_TRUE(!break_editor_doc_audio_attached(doc));
        break_editor_doc_destroy(doc);
    }
    doc = break_editor_doc_create();
    ASSERT_NOT_NULL(doc);
    break_editor_test_set_alloc_budget(2u);
    ASSERT_TRUE(break_editor_doc_audio_attach(doc, 16000u, 1u, kSamples, 8u));
    break_editor_test_set_alloc_budget(BREAK_EDITOR_TEST_ALLOC_DISABLED);
    stack = break_editor_doc_stack(doc);
    for (u64 budget = 0u; budget < 3u; ++budget) {
        const u64 before = break_editor_cmd_stack_revision(stack);
        break_editor_test_set_alloc_budget(budget);
        ASSERT_TRUE(!break_editor_doc_audio_trim(doc, 1u, 4u));
        break_editor_test_set_alloc_budget(BREAK_EDITOR_TEST_ALLOC_DISABLED);
        assert_samples(doc, kSamples, 8u);
        ASSERT_EQ(break_editor_cmd_stack_revision(stack), before);
    }
    ASSERT_TRUE(break_editor_doc_audio_trim(doc, 1u, 4u));
    break_editor_doc_destroy(doc);
}

TEST_MAIN_BEGIN()
    RUN_TEST(attach_validation_and_reset_or_load_detach);
    RUN_TEST(trim_and_cut_are_byte_exact_undoable_commands);
    RUN_TEST(fade_normalize_and_mix_use_real_primitives);
    RUN_TEST(origin_conflicts_and_drop_oldest_include_audio);
    RUN_TEST(invalid_and_oom_failures_are_atomic);
TEST_MAIN_END()
