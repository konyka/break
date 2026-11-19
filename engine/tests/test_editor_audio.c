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
#if !defined(_WIN32)
#include <sys/stat.h> /* mkdir behind TEST_MKDIR */
#endif

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
    ASSERT_EQ(audio_edit_fade_i16(expected, 4u, 1u, 16000u, 1000.0, 1000.0), AUDIO_OK);
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

static void write_u16_le(FILE *file, u16 value) {
    const u8 bytes[] = {(u8)value, (u8)(value >> 8u)};
    fwrite(bytes, 1u, 2u, file);
}

static void write_u32_le(FILE *file, u32 value) {
    const u8 bytes[] = {(u8)value, (u8)(value >> 8u), (u8)(value >> 16u),
                        (u8)(value >> 24u)};
    fwrite(bytes, 1u, 4u, file);
}

TEST(wav_import_attaches_and_failures_are_atomic)
{
    char path[512];
    test_tmp(path, sizeof(path), "editor_audio_import");
    const i16 imported[] = {1234, -2345};
    FILE *file = fopen(path, "wb");
    ASSERT_NOT_NULL(file);
    const u32 data_bytes = 4u;
    fwrite("RIFF", 1u, 4u, file);
    write_u32_le(file, 36u + data_bytes);
    fwrite("WAVEfmt ", 1u, 8u, file);
    write_u32_le(file, 16u);
    write_u16_le(file, 1u);
    write_u16_le(file, 1u);
    write_u32_le(file, 16000u);
    write_u32_le(file, 32000u);
    write_u16_le(file, 2u);
    write_u16_le(file, 16u);
    fwrite("data", 1u, 4u, file);
    write_u32_le(file, data_bytes);
    for (u32 i = 0; i < 2u; ++i) write_u16_le(file, (u16)imported[i]);
    ASSERT_EQ(fclose(file), 0);

    for (u64 budget = 0u; budget < 4u; ++budget) {
        BreakEditorDoc *doc = break_editor_doc_create();
        ASSERT_NOT_NULL(doc);
        break_editor_test_set_alloc_budget(budget);
        ASSERT_TRUE(!break_editor_doc_audio_attach_wav(doc, path));
        break_editor_test_set_alloc_budget(BREAK_EDITOR_TEST_ALLOC_DISABLED);
        ASSERT_TRUE(!break_editor_doc_audio_attached(doc));
        ASSERT_EQ(break_editor_cmd_stack_revision(break_editor_doc_stack(doc)), 0u);
        ASSERT_TRUE(!break_editor_doc_is_dirty(doc));
        break_editor_doc_destroy(doc);
    }
    BreakEditorDoc *doc = break_editor_doc_create();
    ASSERT_NOT_NULL(doc);
    break_editor_test_set_alloc_budget(4u);
    ASSERT_TRUE(break_editor_doc_audio_attach_wav(doc, path));
    break_editor_test_set_alloc_budget(BREAK_EDITOR_TEST_ALLOC_DISABLED);
    ASSERT_EQ(break_editor_doc_audio_sample_rate(doc), 16000u);
    ASSERT_EQ(break_editor_doc_audio_channels(doc), 1u);
    assert_samples(doc, imported, 2u);
    ASSERT_TRUE(break_editor_doc_audio_trim(doc, 0u, 1u));
    ASSERT_TRUE(break_editor_undo(doc));
    assert_samples(doc, imported, 2u);
    const u64 revision = break_editor_cmd_stack_revision(break_editor_doc_stack(doc));
    ASSERT_TRUE(break_editor_doc_is_dirty(doc));
    ASSERT_TRUE(!break_editor_doc_audio_attach_wav(doc, path));
    assert_samples(doc, imported, 2u);
    ASSERT_EQ(break_editor_cmd_stack_revision(break_editor_doc_stack(doc)), revision);
    ASSERT_TRUE(break_editor_doc_is_dirty(doc));
    break_editor_doc_destroy(doc);

    doc = break_editor_doc_create();
    ASSERT_NOT_NULL(doc);
    ASSERT_TRUE(!break_editor_doc_audio_attach_wav(doc, NULL));
    ASSERT_TRUE(!break_editor_doc_audio_attach_wav(doc, "missing-editor-audio.wav"));
    file = fopen(path, "wb");
    ASSERT_NOT_NULL(file);
    fwrite("not a wave", 1u, 10u, file);
    ASSERT_EQ(fclose(file), 0);
    ASSERT_TRUE(!break_editor_doc_audio_attach_wav(doc, path));
    ASSERT_TRUE(!break_editor_doc_audio_attached(doc));
    ASSERT_EQ(break_editor_cmd_stack_revision(break_editor_doc_stack(doc)), 0u);
    ASSERT_TRUE(!break_editor_doc_is_dirty(doc));
    break_editor_doc_destroy(doc);
    remove(path);
}

static bool file_exists(const char *path) {
    FILE *file = fopen(path, "rb");
    if (!file) return false;
    fclose(file);
    return true;
}

TEST(wav_export_round_trips_and_failures_leave_nothing)
{
    char path[512], tmp[600];
    test_tmp(path, sizeof(path), "editor_audio_export.wav");
    snprintf(tmp, sizeof(tmp), "%s.tmp", path);
    remove(path);
    remove(tmp);

    BreakEditorDoc *doc = break_editor_doc_create();
    ASSERT_NOT_NULL(doc);
    ASSERT_TRUE(!break_editor_doc_audio_save_wav(doc, path));
    ASSERT_TRUE(!file_exists(path));
    const i16 stereo[8] = {1, -1, 300, -300, 32767, -32768, 7, 8};
    ASSERT_TRUE(break_editor_doc_audio_attach(doc, 44100u, 2u, stereo, 4u));
    ASSERT_TRUE(break_editor_doc_audio_cut(doc, 1u, 2u));
    const u64 revision = break_editor_cmd_stack_revision(break_editor_doc_stack(doc));
    const bool dirty = break_editor_doc_is_dirty(doc);
    ASSERT_TRUE(!break_editor_doc_audio_save_wav(NULL, path));
    ASSERT_TRUE(!break_editor_doc_audio_save_wav(doc, NULL));
    ASSERT_TRUE(!break_editor_doc_audio_save_wav(doc, ""));
    char missing_dir[600];
    snprintf(missing_dir, sizeof(missing_dir), "%s.no-such-dir/out.wav", path);
    ASSERT_TRUE(!break_editor_doc_audio_save_wav(doc, missing_dir));

    /* the rename fails when path is a directory: the temporary is removed */
    char dir_path[600], dir_tmp[700];
    snprintf(dir_path, sizeof(dir_path), "%s.dir", path);
    snprintf(dir_tmp, sizeof(dir_tmp), "%s.tmp", dir_path);
    remove(dir_tmp);
    TEST_MKDIR(dir_path);
    ASSERT_TRUE(!break_editor_doc_audio_save_wav(doc, dir_path));
    ASSERT_TRUE(!file_exists(dir_tmp));
    TEST_RMDIR(dir_path);

    /* allocation failure: no file and no temporary left behind */
    break_editor_test_set_alloc_budget(0u);
    ASSERT_TRUE(!break_editor_doc_audio_save_wav(doc, path));
    break_editor_test_set_alloc_budget(BREAK_EDITOR_TEST_ALLOC_DISABLED);
    ASSERT_TRUE(!file_exists(path));
    ASSERT_TRUE(!file_exists(tmp));

    ASSERT_TRUE(break_editor_doc_audio_save_wav(doc, path));
    ASSERT_TRUE(!file_exists(tmp));
    ASSERT_EQ(break_editor_cmd_stack_revision(break_editor_doc_stack(doc)), revision);
    ASSERT_EQ(break_editor_doc_is_dirty(doc), dirty);

    BreakEditorDoc *copy = break_editor_doc_create();
    ASSERT_NOT_NULL(copy);
    ASSERT_TRUE(break_editor_doc_audio_attach_wav(copy, path));
    ASSERT_EQ(break_editor_doc_audio_sample_rate(copy), 44100u);
    ASSERT_EQ(break_editor_doc_audio_channels(copy), 2u);
    const i16 expected[6] = {1, -1, 32767, -32768, 7, 8};
    ASSERT_EQ(break_editor_doc_audio_frames(copy), 3u);
    ASSERT_EQ(memcmp(break_editor_doc_audio_samples(copy), expected, sizeof(expected)), 0);
    break_editor_doc_destroy(copy);

    /* a second save replaces the file whole */
    ASSERT_TRUE(break_editor_doc_audio_trim(doc, 0u, 1u));
    ASSERT_TRUE(break_editor_doc_audio_save_wav(doc, path));
    copy = break_editor_doc_create();
    ASSERT_NOT_NULL(copy);
    ASSERT_TRUE(break_editor_doc_audio_attach_wav(copy, path));
    ASSERT_EQ(break_editor_doc_audio_frames(copy), 1u);
    break_editor_doc_destroy(copy);
    break_editor_doc_destroy(doc);
    remove(path);
}

TEST(wav_export_handles_mono_a_stale_temporary_and_long_paths)
{
    char path[512], tmp[600];
    test_tmp(path, sizeof(path), "editor_audio_export_mono.wav");
    snprintf(tmp, sizeof(tmp), "%s.tmp", path);
    remove(path);
    /* a temporary left by an earlier crash is replaced, not appended to */
    FILE *stale = fopen(tmp, "wb");
    ASSERT_NOT_NULL(stale);
    fwrite("stale stale stale stale stale stale stale stale", 1u, 47u, stale);
    ASSERT_EQ(fclose(stale), 0);

    BreakEditorDoc *doc = break_editor_doc_create();
    ASSERT_NOT_NULL(doc);
    ASSERT_TRUE(break_editor_doc_audio_attach(doc, 8000u, 1u, kSamples, 8u));
    ASSERT_TRUE(break_editor_doc_audio_save_wav(doc, path));
    ASSERT_TRUE(!file_exists(tmp));
    BreakEditorDoc *copy = break_editor_doc_create();
    ASSERT_NOT_NULL(copy);
    ASSERT_TRUE(break_editor_doc_audio_attach_wav(copy, path));
    ASSERT_EQ(break_editor_doc_audio_sample_rate(copy), 8000u);
    ASSERT_EQ(break_editor_doc_audio_channels(copy), 1u);
    assert_samples(copy, kSamples, 8u);
    break_editor_doc_destroy(copy);

    /* "<path>.tmp" must fit BREAK_EDITOR_SCENE_PATH_CAPACITY: nothing is created */
    char long_path[BREAK_EDITOR_SCENE_PATH_CAPACITY];
    memset(long_path, 'a', sizeof(long_path) - 1u);
    long_path[sizeof(long_path) - 1u] = '\0';
    ASSERT_TRUE(!break_editor_doc_audio_save_wav(doc, long_path));
    break_editor_doc_destroy(doc);
    remove(path);
}

static void assert_columns(const i16 *min, const i16 *max, const i16 *emin,
                           const i16 *emax, u32 columns) {
    ASSERT_EQ(memcmp(min, emin, sizeof(i16) * columns), 0);
    ASSERT_EQ(memcmp(max, emax, sizeof(i16) * columns), 0);
}

TEST(waveform_reports_min_max_per_column)
{
    i16 min[16], max[16];
    BreakEditorDoc *doc = break_editor_doc_create();
    ASSERT_NOT_NULL(doc);
    ASSERT_TRUE(!break_editor_doc_audio_waveform(doc, 4u, min, max));
    ASSERT_TRUE(break_editor_doc_audio_attach(doc, 16000u, 1u, kSamples, 8u));
    /* 8 frames / 3 columns: [0,2) [2,5) [5,8) */
    ASSERT_TRUE(break_editor_doc_audio_waveform(doc, 3u, min, max));
    {
        const i16 emin[] = {0, 200, 500}, emax[] = {100, 400, 700};
        assert_columns(min, max, emin, emax, 3u);
    }
    ASSERT_TRUE(break_editor_doc_audio_waveform(doc, 8u, min, max));
    assert_columns(min, max, kSamples, kSamples, 8u);
    /* 16 columns over 8 frames: column c shows frame c/2 */
    ASSERT_TRUE(break_editor_doc_audio_waveform(doc, 16u, min, max));
    for (u32 c = 0u; c < 16u; ++c) {
        ASSERT_EQ(min[c], kSamples[c / 2u]);
        ASSERT_EQ(max[c], kSamples[c / 2u]);
    }
    ASSERT_TRUE(break_editor_doc_audio_waveform(doc, 1u, min, max));
    ASSERT_EQ(min[0], 0);
    ASSERT_EQ(max[0], 700);
    break_editor_doc_destroy(doc);

    /* stereo: both channels count; frames {(-5,9) (3,-7) (1,2) (-20,4)} */
    const i16 stereo[] = {-5, 9, 3, -7, 1, 2, -20, 4};
    doc = break_editor_doc_create();
    ASSERT_NOT_NULL(doc);
    ASSERT_TRUE(break_editor_doc_audio_attach(doc, 48000u, 2u, stereo, 4u));
    ASSERT_TRUE(break_editor_doc_audio_waveform(doc, 2u, min, max));
    {
        const i16 emin[] = {-7, -20}, emax[] = {9, 4};
        assert_columns(min, max, emin, emax, 2u);
    }
    break_editor_doc_destroy(doc);
}

TEST(waveform_rejects_invalid_arguments_without_writing)
{
    i16 min[4] = {11, 11, 11, 11}, max[4] = {22, 22, 22, 22};
    static i16 big_min[BREAK_EDITOR_AUDIO_WAVEFORM_MAX_COLUMNS + 1u];
    static i16 big_max[BREAK_EDITOR_AUDIO_WAVEFORM_MAX_COLUMNS + 1u];
    BreakEditorDoc *doc = break_editor_doc_create();
    ASSERT_NOT_NULL(doc);
    ASSERT_TRUE(!break_editor_doc_audio_waveform(NULL, 4u, min, max));
    ASSERT_TRUE(break_editor_doc_audio_attach(doc, 16000u, 1u, kSamples, 8u));
    ASSERT_TRUE(!break_editor_doc_audio_waveform(doc, 0u, min, max));
    ASSERT_TRUE(!break_editor_doc_audio_waveform(doc, 4u, NULL, max));
    ASSERT_TRUE(!break_editor_doc_audio_waveform(doc, 4u, min, NULL));
    ASSERT_TRUE(!break_editor_doc_audio_waveform(
        doc, BREAK_EDITOR_AUDIO_WAVEFORM_MAX_COLUMNS + 1u, big_min, big_max));
    ASSERT_TRUE(break_editor_doc_audio_waveform(
        doc, BREAK_EDITOR_AUDIO_WAVEFORM_MAX_COLUMNS, big_min, big_max));
    ASSERT_EQ(big_max[BREAK_EDITOR_AUDIO_WAVEFORM_MAX_COLUMNS - 1u], 700);
    /* trimmed to zero frames */
    ASSERT_TRUE(break_editor_doc_audio_cut(doc, 0u, 8u));
    ASSERT_EQ(break_editor_doc_audio_frames(doc), 0u);
    ASSERT_TRUE(!break_editor_doc_audio_waveform(doc, 4u, min, max));
    for (u32 i = 0u; i < 4u; ++i) {
        ASSERT_EQ(min[i], 11);
        ASSERT_EQ(max[i], 22);
    }
    break_editor_doc_destroy(doc);
}

TEST(audio_revision_tracks_every_attachment_change)
{
    BreakEditorDoc *doc = break_editor_doc_create();
    ASSERT_NOT_NULL(doc);
    ASSERT_EQ(break_editor_doc_audio_revision(NULL), 0u);
    u64 last = break_editor_doc_audio_revision(doc);
#define EXPECT_CHANGED()                                          \
    do {                                                          \
        const u64 now_ = break_editor_doc_audio_revision(doc);    \
        ASSERT_TRUE(now_ != last);                                \
        last = now_;                                              \
    } while (0)
#define EXPECT_SAME() ASSERT_EQ(break_editor_doc_audio_revision(doc), last)
    ASSERT_TRUE(break_editor_doc_audio_attach(doc, 16000u, 1u, kSamples, 8u));
    EXPECT_CHANGED();
    ASSERT_TRUE(!break_editor_doc_audio_trim(doc, 6u, 2u));
    EXPECT_SAME();
    ASSERT_TRUE(break_editor_doc_audio_trim(doc, 1u, 7u));
    EXPECT_CHANGED();
    ASSERT_TRUE(break_editor_doc_audio_fade(doc, 0.1, 0.1));
    EXPECT_CHANGED();
    ASSERT_TRUE(break_editor_undo(doc));
    EXPECT_CHANGED();
    ASSERT_TRUE(break_editor_redo(doc));
    EXPECT_CHANGED();
    char path[512];
    test_tmp(path, sizeof(path), "editor_audio_revision.wav");
    ASSERT_TRUE(break_editor_doc_audio_save_wav(doc, path));
    EXPECT_SAME();
    ASSERT_TRUE(break_editor_doc_reset(doc));
    EXPECT_CHANGED();
    /* a fresh attachment never repeats an earlier revision */
    ASSERT_TRUE(break_editor_doc_audio_attach_wav(doc, path));
    EXPECT_CHANGED();
    ASSERT_TRUE(last > 2u);
#undef EXPECT_CHANGED
#undef EXPECT_SAME
    remove(path);
    break_editor_doc_destroy(doc);
}

TEST(fade_and_normalize_ranges_change_only_the_range)
{
    static i16 ramp[2u * 400u];
    i16 expected[2u * 400u];
    BreakEditorDoc *doc = break_editor_doc_create();
    ASSERT_NOT_NULL(doc);
    for (u32 i = 0u; i < 800u; ++i) ramp[i] = (i16)((i % 2u) ? -(i16)(i * 10u) : (i16)(i * 10u));
    ASSERT_TRUE(break_editor_doc_audio_attach(doc, 8000u, 2u, ramp, 400u));
    BreakEditorCmdStack *stack = break_editor_doc_stack(doc);
    /* fade [100, 300): 5 ms = 40 frames at each end of the range */
    memcpy(expected, ramp, sizeof(ramp));
    ASSERT_EQ(audio_edit_fade_i16(expected + 2u * 100u, 200u, 2u, 8000u, 5.0, 5.0), AUDIO_OK);
    ASSERT_TRUE(break_editor_doc_audio_fade_range(doc, 100u, 300u, 5.0, 5.0));
    ASSERT_EQ(memcmp(break_editor_doc_audio_samples(doc), expected, sizeof(expected)), 0);
    ASSERT_EQ(break_editor_cmd_stack_undo_count(stack), 1u);
    ASSERT_TRUE(break_editor_undo(doc));
    ASSERT_EQ(memcmp(break_editor_doc_audio_samples(doc), ramp, sizeof(ramp)), 0);
    ASSERT_TRUE(break_editor_redo(doc));
    ASSERT_EQ(memcmp(break_editor_doc_audio_samples(doc), expected, sizeof(expected)), 0);
    ASSERT_TRUE(break_editor_undo(doc));
    /* normalize [50, 60): the peak is measured inside the range */
    memcpy(expected, ramp, sizeof(ramp));
    ASSERT_EQ(audio_edit_normalize_i16(expected + 2u * 50u, 10u, 2u, -1.0), AUDIO_OK);
    ASSERT_TRUE(break_editor_doc_audio_normalize_range(doc, 50u, 60u, -1.0));
    ASSERT_EQ(memcmp(break_editor_doc_audio_samples(doc), expected, sizeof(expected)), 0);
    ASSERT_TRUE(break_editor_doc_audio_samples(doc)[2u * 59u] > 25000);
    ASSERT_EQ(break_editor_doc_audio_samples(doc)[2u * 60u], ramp[2u * 60u]);
    ASSERT_TRUE(break_editor_undo(doc));
    ASSERT_EQ(memcmp(break_editor_doc_audio_samples(doc), ramp, sizeof(ramp)), 0);
    /* invalid: nothing changes, no history entry */
    const u32 undo = break_editor_cmd_stack_undo_count(stack);
    ASSERT_TRUE(!break_editor_doc_audio_fade_range(doc, 10u, 10u, 5.0, 5.0));
    ASSERT_TRUE(!break_editor_doc_audio_fade_range(doc, 20u, 10u, 5.0, 5.0));
    ASSERT_TRUE(!break_editor_doc_audio_fade_range(doc, 10u, 401u, 5.0, 5.0));
    ASSERT_TRUE(!break_editor_doc_audio_fade_range(doc, 10u, 20u, -1.0, 5.0));
    ASSERT_TRUE(!break_editor_doc_audio_normalize_range(doc, 10u, 20u, 1.0));
    ASSERT_TRUE(!break_editor_doc_audio_normalize_range(doc, 400u, 400u, -1.0));
    ASSERT_TRUE(!break_editor_doc_audio_normalize_range(NULL, 0u, 1u, -1.0));
    ASSERT_EQ(break_editor_cmd_stack_undo_count(stack), undo);
    ASSERT_EQ(memcmp(break_editor_doc_audio_samples(doc), ramp, sizeof(ramp)), 0);
    /* digital silence: normalize reports success and changes nothing, like
     * the whole-clip call, so it still records one undoable command */
    {
        BreakEditorDoc *quiet = break_editor_doc_create();
        static const i16 zeros[4] = {0, 0, 0, 0};
        ASSERT_NOT_NULL(quiet);
        ASSERT_TRUE(break_editor_doc_audio_attach(quiet, 8000u, 1u, zeros, 4u));
        ASSERT_TRUE(break_editor_doc_audio_normalize_range(quiet, 0u, 4u, -1.0));
        ASSERT_EQ(memcmp(break_editor_doc_audio_samples(quiet), zeros, sizeof(zeros)), 0);
        ASSERT_EQ(break_editor_cmd_stack_undo_count(break_editor_doc_stack(quiet)), 1u);
        break_editor_doc_destroy(quiet);
    }
    /* a range shorter than the fade length still fades inside it */
    memcpy(expected, ramp, sizeof(ramp));
    ASSERT_EQ(audio_edit_fade_i16(expected + 2u * 10u, 3u, 2u, 8000u, 100.0, 100.0), AUDIO_OK);
    ASSERT_TRUE(break_editor_doc_audio_fade_range(doc, 10u, 13u, 100.0, 100.0));
    ASSERT_EQ(memcmp(break_editor_doc_audio_samples(doc), expected, sizeof(expected)), 0);
    ASSERT_EQ(break_editor_doc_audio_samples(doc)[2u * 13u], ramp[2u * 13u]);
    ASSERT_TRUE(break_editor_undo(doc));
    /* the whole clip as a range equals the whole-clip call */
    memcpy(expected, ramp, sizeof(ramp));
    ASSERT_EQ(audio_edit_normalize_i16(expected, 400u, 2u, -6.0), AUDIO_OK);
    ASSERT_TRUE(break_editor_doc_audio_normalize_range(doc, 0u, 400u, -6.0));
    ASSERT_EQ(memcmp(break_editor_doc_audio_samples(doc), expected, sizeof(expected)), 0);
    break_editor_doc_destroy(doc);
}

TEST(waveform_range_matches_a_manual_min_max)
{
    static i16 ramp[500u];
    i16 min[64], max[64], wmin[64], wmax[64];
    BreakEditorDoc *doc = break_editor_doc_create();
    ASSERT_NOT_NULL(doc);
    for (u32 i = 0u; i < 500u; ++i) ramp[i] = (i16)((i % 7u) * 1000u) - 3000;
    ASSERT_TRUE(break_editor_doc_audio_attach(doc, 8000u, 1u, ramp, 500u));
    /* the full range equals the whole-clip function */
    ASSERT_TRUE(break_editor_doc_audio_waveform(doc, 17u, wmin, wmax));
    ASSERT_TRUE(break_editor_doc_audio_waveform_range(doc, 0u, 500u, 17u, min, max));
    ASSERT_EQ(memcmp(min, wmin, sizeof(i16) * 17u), 0);
    ASSERT_EQ(memcmp(max, wmax, sizeof(i16) * 17u), 0);
    /* a sub-range: column c covers [100 + c*200/8, 100 + (c+1)*200/8) */
    ASSERT_TRUE(break_editor_doc_audio_waveform_range(doc, 100u, 300u, 8u, min, max));
    for (u32 c = 0u; c < 8u; ++c) {
        const u32 first = 100u + c * 200u / 8u;
        const u32 last = 100u + (c + 1u) * 200u / 8u;
        i16 lo = ramp[first], hi = ramp[first];
        for (u32 f = first; f < last; ++f) {
            if (ramp[f] < lo) lo = ramp[f];
            if (ramp[f] > hi) hi = ramp[f];
        }
        ASSERT_EQ(min[c], lo);
        ASSERT_EQ(max[c], hi);
    }
    /* more columns than frames: one frame each */
    ASSERT_TRUE(break_editor_doc_audio_waveform_range(doc, 10u, 14u, 8u, min, max));
    for (u32 c = 0u; c < 8u; ++c) ASSERT_EQ(min[c], ramp[10u + c / 2u]);
    /* a narrow column still covers the whole frame, both channels */
    {
        static i16 stereo[40u];
        for (u32 i = 0u; i < 20u; ++i) {
            stereo[i * 2u] = 1000;
            stereo[i * 2u + 1u] = -2000;
        }
        break_editor_doc_reset(doc);
        ASSERT_TRUE(break_editor_doc_audio_attach(doc, 8000u, 2u, stereo, 20u));
        ASSERT_TRUE(break_editor_doc_audio_waveform_range(doc, 4u, 8u, 8u, min, max));
        for (u32 c = 0u; c < 8u; ++c) {
            ASSERT_EQ(min[c], -2000);
            ASSERT_EQ(max[c], 1000);
        }
        break_editor_doc_reset(doc);
        ASSERT_TRUE(break_editor_doc_audio_attach(doc, 8000u, 1u, ramp, 500u));
    }
    /* invalid ranges write nothing */
    min[0] = 42;
    ASSERT_TRUE(!break_editor_doc_audio_waveform_range(doc, 10u, 10u, 4u, min, max));
    ASSERT_TRUE(!break_editor_doc_audio_waveform_range(doc, 20u, 10u, 4u, min, max));
    ASSERT_TRUE(!break_editor_doc_audio_waveform_range(doc, 0u, 501u, 4u, min, max));
    ASSERT_TRUE(!break_editor_doc_audio_waveform_range(doc, 0u, 10u, 0u, min, max));
    ASSERT_TRUE(!break_editor_doc_audio_waveform_range(NULL, 0u, 10u, 4u, min, max));
    ASSERT_EQ(min[0], 42);
    break_editor_doc_destroy(doc);
}

/* Per-channel waveform (design 2026-11-19-editor-audio-channels). */
TEST(waveform_channel_reports_one_channel_at_a_time)
{
    static i16 stereo[200u];
    i16 min[16], max[16];
    BreakEditorDoc *doc = break_editor_doc_create();
    ASSERT_NOT_NULL(doc);
    /* left silent, right a loud ramp */
    for (u32 i = 0u; i < 100u; ++i) {
        stereo[i * 2u] = 0;
        stereo[i * 2u + 1u] = (i16)(i * 300u);
    }
    ASSERT_TRUE(break_editor_doc_audio_attach(doc, 8000u, 2u, stereo, 100u));
    /* channel 0 is silent throughout */
    ASSERT_TRUE(break_editor_doc_audio_waveform_channel(doc, 0u, 0u, 100u, 4u, min, max));
    for (u32 c = 0u; c < 4u; ++c) {
        ASSERT_EQ(min[c], 0);
        ASSERT_EQ(max[c], 0);
    }
    /* channel 1 rises with the ramp */
    ASSERT_TRUE(break_editor_doc_audio_waveform_channel(doc, 1u, 0u, 100u, 4u, min, max));
    for (u32 c = 0u; c < 4u; ++c) {
        ASSERT_EQ(min[c], (i16)(c * 25u * 300u));
        ASSERT_EQ(max[c], (i16)((c * 25u + 24u) * 300u));
    }
    /* a sub-range of one channel */
    ASSERT_TRUE(break_editor_doc_audio_waveform_channel(doc, 1u, 50u, 60u, 2u, min, max));
    ASSERT_EQ(min[0], (i16)(50u * 300u));
    ASSERT_EQ(max[1], (i16)(59u * 300u));
    /* the merged function still reports the union of both channels */
    ASSERT_TRUE(break_editor_doc_audio_waveform_range(doc, 0u, 100u, 4u, min, max));
    for (u32 c = 0u; c < 4u; ++c) {
        ASSERT_EQ(min[c], 0); /* the silent left channel */
        ASSERT_EQ(max[c], (i16)((c * 25u + 24u) * 300u));
    }
    /* an out-of-range channel writes nothing */
    min[0] = 42;
    ASSERT_TRUE(!break_editor_doc_audio_waveform_channel(doc, 2u, 0u, 100u, 4u, min, max));
    ASSERT_TRUE(!break_editor_doc_audio_waveform_channel(doc, 0u, 0u, 101u, 4u, min, max));
    ASSERT_TRUE(!break_editor_doc_audio_waveform_channel(doc, 0u, 0u, 100u, 0u, min, max));
    ASSERT_TRUE(!break_editor_doc_audio_waveform_channel(NULL, 0u, 0u, 100u, 4u, min, max));
    ASSERT_EQ(min[0], 42);
    /* a mono clip has channel 0 only */
    break_editor_doc_reset(doc);
    ASSERT_TRUE(break_editor_doc_audio_attach(doc, 8000u, 1u, stereo, 100u));
    ASSERT_TRUE(break_editor_doc_audio_waveform_channel(doc, 0u, 0u, 100u, 4u, min, max));
    ASSERT_TRUE(!break_editor_doc_audio_waveform_channel(doc, 1u, 0u, 100u, 4u, min, max));
    break_editor_doc_destroy(doc);
}

/* Peak and RMS (design 2026-11-19-editor-audio-db). */
TEST(peak_range_reports_peak_and_rms)
{
    static i16 pcm[400u];
    double peak = -1.0, rms = -1.0;
    BreakEditorDoc *doc = break_editor_doc_create();
    ASSERT_NOT_NULL(doc);
    /* a full-scale square wave: peak and RMS are both the amplitude */
    for (u32 i = 0u; i < 400u; ++i) pcm[i] = (i16)(i % 2u == 0u ? 32767 : -32767);
    ASSERT_TRUE(break_editor_doc_audio_attach(doc, 8000u, 1u, pcm, 400u));
    ASSERT_TRUE(break_editor_doc_audio_peak_range(doc, 0u, 400u, &peak, &rms));
    ASSERT_TRUE(peak > 32766.0 && peak < 32768.0);
    ASSERT_TRUE(rms > 32766.0 && rms < 32768.0);
    /* half the amplitude: both halve */
    break_editor_doc_reset(doc);
    for (u32 i = 0u; i < 400u; ++i) pcm[i] = (i16)(i % 2u == 0u ? 16384 : -16384);
    ASSERT_TRUE(break_editor_doc_audio_attach(doc, 8000u, 1u, pcm, 400u));
    ASSERT_TRUE(break_editor_doc_audio_peak_range(doc, 0u, 400u, &peak, &rms));
    ASSERT_TRUE(peak > 16383.0 && peak < 16385.0);
    ASSERT_TRUE(rms > 16383.0 && rms < 16385.0);
    /* RMS is below the peak for anything but a square wave, and the peak
     * is not the first sample: 399 quiet frames then one loud one */
    break_editor_doc_reset(doc);
    for (u32 i = 0u; i < 400u; ++i) pcm[i] = (i16)(i == 399u ? 30000 : 300);
    ASSERT_TRUE(break_editor_doc_audio_attach(doc, 8000u, 1u, pcm, 400u));
    ASSERT_TRUE(break_editor_doc_audio_peak_range(doc, 0u, 400u, &peak, &rms));
    ASSERT_TRUE(peak > 29999.0 && peak < 30001.0);
    /* sqrt((399*300^2 + 30000^2)/400) is about 1543 */
    ASSERT_TRUE(rms > 1500.0 && rms < 1590.0);
    ASSERT_TRUE(rms < peak / 10.0);
    /* a sub-range sees only its own samples */
    break_editor_doc_reset(doc);
    for (u32 i = 0u; i < 400u; ++i) pcm[i] = (i16)(i < 200u ? 20000 : 100);
    ASSERT_TRUE(break_editor_doc_audio_attach(doc, 8000u, 1u, pcm, 400u));
    ASSERT_TRUE(break_editor_doc_audio_peak_range(doc, 200u, 400u, &peak, &rms));
    ASSERT_TRUE(peak > 99.0 && peak < 101.0);
    ASSERT_TRUE(rms > 99.0 && rms < 101.0);
    ASSERT_TRUE(break_editor_doc_audio_peak_range(doc, 0u, 200u, &peak, &rms));
    ASSERT_TRUE(peak > 19999.0 && peak < 20001.0);
    /* a silent clip is 0, not an error */
    break_editor_doc_reset(doc);
    memset(pcm, 0, sizeof(pcm));
    ASSERT_TRUE(break_editor_doc_audio_attach(doc, 8000u, 1u, pcm, 400u));
    ASSERT_TRUE(break_editor_doc_audio_peak_range(doc, 0u, 400u, &peak, &rms));
    ASSERT_EQ((int)peak, 0);
    ASSERT_EQ((int)rms, 0);
    /* invalid ranges write nothing */
    peak = rms = -1.0;
    ASSERT_TRUE(!break_editor_doc_audio_peak_range(doc, 10u, 10u, &peak, &rms));
    ASSERT_TRUE(!break_editor_doc_audio_peak_range(doc, 0u, 401u, &peak, &rms));
    ASSERT_TRUE(!break_editor_doc_audio_peak_range(NULL, 0u, 10u, &peak, &rms));
    ASSERT_EQ((int)peak, -1);
    ASSERT_EQ((int)rms, -1);
    break_editor_doc_destroy(doc);
}

/* True peak (design 2026-11-20-editor-audio-true-peak). */
TEST(true_peak_range_sees_intersample_peaks)
{
    static i16 pcm[400u];
    double peak = -1.0, rms = -1.0, tp = -1.0;
    BreakEditorDoc *doc = break_editor_doc_create();
    ASSERT_NOT_NULL(doc);
    /* a sine whose crests fall between samples: 4 samples per cycle with a
     * quarter-sample offset, so no sample lands on the crest */
    for (u32 i = 0u; i < 400u; ++i) {
        const double phase = 2.0 * 3.14159265358979 * ((double)i / 4.0 + 0.125);
        pcm[i] = (i16)(sin(phase) * 20000.0);
    }
    ASSERT_TRUE(break_editor_doc_audio_attach(doc, 8000u, 1u, pcm, 400u));
    ASSERT_TRUE(break_editor_doc_audio_peak_range(doc, 0u, 400u, &peak, &rms));
    ASSERT_TRUE(break_editor_doc_audio_true_peak_range(doc, 0u, 400u, &tp));
    /* the reconstruction reaches above every stored sample */
    ASSERT_TRUE(tp > peak);
    /* the samples sit at +-45 degrees of the sine, so they read 20000 *
     * sin(45) = 14142 while the crest between them is the full 20000: the
     * reconstruction must recover about sqrt(2) of the sample peak */
    ASSERT_TRUE(tp > peak * 1.38 && tp < peak * 1.48);
    ASSERT_TRUE(tp > 19500.0 && tp < 20600.0);
    /* a square wave's true peak is at least its sample peak (phase 0 is
     * the identity, so it can never report less) */
    break_editor_doc_reset(doc);
    for (u32 i = 0u; i < 400u; ++i) pcm[i] = (i16)(i % 2u == 0u ? 32767 : -32767);
    ASSERT_TRUE(break_editor_doc_audio_attach(doc, 8000u, 1u, pcm, 400u));
    ASSERT_TRUE(break_editor_doc_audio_peak_range(doc, 0u, 400u, &peak, &rms));
    ASSERT_TRUE(break_editor_doc_audio_true_peak_range(doc, 0u, 400u, &tp));
    ASSERT_TRUE(tp >= peak - 1.0);
    /* a silent clip is 0 */
    break_editor_doc_reset(doc);
    memset(pcm, 0, sizeof(pcm));
    ASSERT_TRUE(break_editor_doc_audio_attach(doc, 8000u, 1u, pcm, 400u));
    ASSERT_TRUE(break_editor_doc_audio_true_peak_range(doc, 0u, 400u, &tp));
    ASSERT_EQ((int)tp, 0);
    /* a sub-range sees only its own samples, and a range at either end of
     * the clip does not read past it */
    break_editor_doc_reset(doc);
    for (u32 i = 0u; i < 400u; ++i) pcm[i] = (i16)(i < 200u ? 20000 : 100);
    ASSERT_TRUE(break_editor_doc_audio_attach(doc, 8000u, 1u, pcm, 400u));
    /* the quiet half: the kernel reaches 16 samples back, so the loud half
     * bleeds into the first few output samples of this range */
    ASSERT_TRUE(break_editor_doc_audio_true_peak_range(doc, 216u, 400u, &tp));
    ASSERT_TRUE(tp > 90.0 && tp < 2000.0);
    ASSERT_TRUE(break_editor_doc_audio_true_peak_range(doc, 0u, 1u, &tp));
    ASSERT_TRUE(tp > 0.0);
    ASSERT_TRUE(break_editor_doc_audio_true_peak_range(doc, 399u, 400u, &tp));
    ASSERT_TRUE(tp > 0.0);
    /* stereo: both channels are measured, and the peak is a magnitude.
     * Channel 0 is quiet; channel 1 is loud and starts negative, so a
     * measurement that skipped later channels or dropped the absolute
     * value would read far too low. */
    break_editor_doc_reset(doc);
    for (u32 i = 0u; i < 200u; ++i) {
        pcm[i * 2u] = 100;
        pcm[i * 2u + 1u] = (i16)(i % 2u == 0u ? -25000 : 25000);
    }
    ASSERT_TRUE(break_editor_doc_audio_attach(doc, 8000u, 2u, pcm, 200u));
    ASSERT_TRUE(break_editor_doc_audio_true_peak_range(doc, 0u, 200u, &tp));
    ASSERT_TRUE(tp > 24000.0);
    /* a one-channel clip of the same quiet level reads far lower, which is
     * what makes the loud second channel's contribution observable */
    {
        static i16 quiet[200u];
        double quiet_tp = 0.0;
        for (u32 i = 0u; i < 200u; ++i) quiet[i] = 100;
        break_editor_doc_reset(doc);
        ASSERT_TRUE(break_editor_doc_audio_attach(doc, 8000u, 1u, quiet, 200u));
        ASSERT_TRUE(break_editor_doc_audio_true_peak_range(doc, 0u, 200u, &quiet_tp));
        ASSERT_TRUE(quiet_tp < 200.0);
        break_editor_doc_reset(doc);
        ASSERT_TRUE(break_editor_doc_audio_attach(doc, 8000u, 2u, pcm, 200u));
    }
    /* an all-negative clip still reports its magnitude: the measurement is
     * |signal|, not the signal's maximum */
    {
        static i16 negative[200u];
        for (u32 i = 0u; i < 200u; ++i) negative[i] = -18000;
        break_editor_doc_reset(doc);
        ASSERT_TRUE(break_editor_doc_audio_attach(doc, 8000u, 1u, negative, 200u));
        ASSERT_TRUE(break_editor_doc_audio_true_peak_range(doc, 0u, 200u, &tp));
        /* above the 18000 magnitude, not below it: the clip's edges are a
         * step against the zero outside, and the sinc reconstruction rings
         * past the level there (a real recording has no such step) */
        ASSERT_TRUE(tp > 17000.0 && tp < 23000.0);
        break_editor_doc_reset(doc);
        ASSERT_TRUE(break_editor_doc_audio_attach(doc, 8000u, 2u, pcm, 200u));
    }
    /* invalid ranges write nothing */
    tp = -1.0;
    ASSERT_TRUE(!break_editor_doc_audio_true_peak_range(doc, 10u, 10u, &tp));
    ASSERT_TRUE(!break_editor_doc_audio_true_peak_range(doc, 0u, 201u, &tp));
    ASSERT_TRUE(!break_editor_doc_audio_true_peak_range(NULL, 0u, 10u, &tp));
    ASSERT_TRUE(!break_editor_doc_audio_true_peak_range(doc, 0u, 10u, NULL));
    ASSERT_EQ((int)tp, -1);
    break_editor_doc_destroy(doc);
}

TEST_MAIN_BEGIN()
    RUN_TEST(true_peak_range_sees_intersample_peaks);
    RUN_TEST(peak_range_reports_peak_and_rms);
    RUN_TEST(waveform_channel_reports_one_channel_at_a_time);
    RUN_TEST(waveform_range_matches_a_manual_min_max);
    RUN_TEST(fade_and_normalize_ranges_change_only_the_range);
    RUN_TEST(waveform_reports_min_max_per_column);
    RUN_TEST(waveform_rejects_invalid_arguments_without_writing);
    RUN_TEST(audio_revision_tracks_every_attachment_change);
    RUN_TEST(attach_validation_and_reset_or_load_detach);
    RUN_TEST(trim_and_cut_are_byte_exact_undoable_commands);
    RUN_TEST(fade_normalize_and_mix_use_real_primitives);
    RUN_TEST(origin_conflicts_and_drop_oldest_include_audio);
    RUN_TEST(invalid_and_oom_failures_are_atomic);
    RUN_TEST(wav_import_attaches_and_failures_are_atomic);
    RUN_TEST(wav_export_round_trips_and_failures_leave_nothing);
    RUN_TEST(wav_export_handles_mono_a_stale_temporary_and_long_paths);
TEST_MAIN_END()
