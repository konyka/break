#pragma once

/* Scripted input replay for live editor validation (design
 * docs/superpowers/specs/2026-10-28-editor-input-script-design.md).
 *
 * The player writes into the platform InputState before break_ui_pump reads
 * it, so every step after that is the production input path. One command
 * advances per frame; "wait N" holds for N frames. Pure apart from the
 * InputState writes and the caller callbacks; test/dev builds only
 * (BREAK_EDITOR_INPUT_SCRIPT). */

#include <core/types.h>
#include <platform/input.h>

#define BREAK_EDITOR_INPUT_SCRIPT_MAX_COMMANDS 512u
#define BREAK_EDITOR_INPUT_SCRIPT_MAX_LINE 256u
#define BREAK_EDITOR_INPUT_SCRIPT_MAX_ARG 128u

typedef struct BreakEditorInputScript BreakEditorInputScript;

typedef struct {
    /* move_to: window-logical position of a named widget's point at
     * fraction (fx, fy); false = not found (the step fails). */
    bool (*locate)(void *user, const char *name, f32 fx, f32 fy, f32 *out_x,
                   f32 *out_y);
    /* expect: the text after "expect "; false = the expectation failed */
    bool (*expect)(void *user, const char *what);
    /* screenshot: the file argument */
    void (*screenshot)(void *user, const char *file);
    void *user;
} BreakEditorInputScriptHooks;

/* Parses `text` (len bytes). NULL on error with "line N: reason" in err. */
BreakEditorInputScript *break_editor_input_script_parse(const char *text,
                                                        usize len, char *err,
                                                        usize err_cap);
void break_editor_input_script_destroy(BreakEditorInputScript *script);
usize break_editor_input_script_command_count(
    const BreakEditorInputScript *script);

/* One frame: applies the current command to `input` (mouse coordinates are
 * multiplied by `input_scale`, the platform's logical->input factor) and
 * advances. Returns false once the script has finished (after quit or the
 * last command). */
bool break_editor_input_script_step(BreakEditorInputScript *script,
                                    InputState *input, f32 input_scale,
                                    const BreakEditorInputScriptHooks *hooks);
/* Failed steps so far (expect false, move_to not found). */
u32 break_editor_input_script_failures(const BreakEditorInputScript *script);
/* Line of the first failure (0 = none). */
u32 break_editor_input_script_first_failure_line(
    const BreakEditorInputScript *script);
bool break_editor_input_script_quit_requested(
    const BreakEditorInputScript *script);
