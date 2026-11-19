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

TEST_MAIN_BEGIN()
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
