#pragma once

/* Editor side of the scripted input replay (BREAK_EDITOR_INPUT_SCRIPT builds
 * only): loads `--input-script <file>`, steps the player into the platform
 * InputState once per frame, and answers the script's move_to / expect /
 * screenshot from the live shell. */

#include <core/types.h>
#include <platform/platform.h>
#include <rhi/rhi.h>

#include "editor_panels.h"

typedef struct BreakEditorInputDriver BreakEditorInputDriver;

/* Removes "--input-script <file>" from argv. *out_path = NULL when absent.
 * false (with a message in err) for a missing file argument. */
bool break_editor_input_driver_take_cli(int *argc, char **argv,
                                        const char **out_path, char *err,
                                        usize err_cap);
/* NULL with a message in err when the file cannot be read or parsed. */
BreakEditorInputDriver *break_editor_input_driver_create(const char *path,
                                                         char *err,
                                                         usize err_cap);
void break_editor_input_driver_destroy(BreakEditorInputDriver *driver);
/* Call after platform_poll and before break_ui_pump. Returns false once the
 * script has finished (the editor should leave its loop). */
bool break_editor_input_driver_frame(BreakEditorInputDriver *driver,
                                     Platform *platform,
                                     BreakEditorShell *shell);
/* Call after rhi_frame_end and before rhi_present: performs a screenshot
 * the script queued this frame. */
void break_editor_input_driver_after_frame(BreakEditorInputDriver *driver,
                                           RHIDevice *device, u32 width,
                                           u32 height);
/* 0 when every step passed, 3 otherwise (printed per failure). */
int break_editor_input_driver_exit_code(const BreakEditorInputDriver *driver);
