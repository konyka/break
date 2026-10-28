/* Headless tests for the Stage 4 scene editor Phase 1 shell (Task 4):
 * panel wiring, shortcut routing, command palette, selection, and a PPM
 * pixel smoke — all on the dummy PAL via break_editor_shell_create_for_test
 * (no RHI). Widget callbacks are exercised through the real emitters
 * ("click"/"activate") so a UI bypass of the command stack would fail the
 * undo pins. */
#include "test_framework.h"

#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <time.h>
#if defined(_WIN32)
#include <sys/utime.h>
#define utime _utime
#define utimbuf _utimbuf
#else
#include <utime.h>
#endif

#include "editor_hot_reload.h"
#include "editor_image_preview.h"
#include "editor_theme.h"
#include <editor/editor_i18n.h>
#include "editor_panels.h"
#include "editor_shader_reload.h"
#include "editor_shader_source.h"
#include "editor_viewport3d.h"
#include "rhi_editor_fake.h"

#include <stdatomic.h>
#include <stdint.h>
#include <stb_image_write.h>
#define BREAK_RUNTIME_TESTING 1
#include <runtime/runtime_test_hooks.h>
#undef BREAK_RUNTIME_TESTING

#include <core/profiler.h>
#include <platform/time.h>
#include <editor/editor_cmd.h>
#include <editor/editor_components.h>
#include <editor/editor_gizmo.h>
#include <editor/editor_scene.h>
#include <editor/editor_viewport.h>

#include "myc/my_emitter.h"
#include "mypal/my_event.h"
#include "mypal/my_pal.h"
#include "myr/my_lcd_mem.h"
#include "myui/my_event_dispatch.h"
#include "myui/my_widget.h"
#include "myui/my_window.h"
#include "myui/widgets/my_button.h"
#include "myui/widgets/my_label.h"
#include "myui/widgets/my_edit.h"

static void emit_click(my_widget_t *w) {
    ASSERT_NOT_NULL(w);
    ASSERT_EQ(my_emitter_emit(w->emitter, "click", NULL), MY_RET_OK);
}

static void emit_activate(my_widget_t *edit) {
    ASSERT_NOT_NULL(edit);
    ASSERT_EQ(my_emitter_emit(edit->emitter, "activate",
                              (void *)my_edit_get_text(edit)),
              MY_RET_OK);
}

static my_widget_t *find(BreakEditorShell *shell, const char *name) {
    return my_widget_find_descendant(break_editor_shell_root(shell), name);
}

static void shell_paint(BreakEditorShell *shell) {
    my_window_t *win = break_editor_shell_window(shell);
    ASSERT_NOT_NULL(win);
    my_widget_invalidate((my_widget_t *)win, NULL);
    my_window_paint(win);
}

static bool file_exists(const char *path) {
    FILE *f = fopen(path, "rb");
    if (f == NULL) {
        return false;
    }
    fclose(f);
    return true;
}

/* Start of the last line in the console's joined text (each line, including
 * the final one, is '\n'-terminated by shell_log). */
static const char *last_console_line(const char *console) {
    const char *last = console;
    const char *p;
    for (p = console; *p != '\0'; p++) {
        if (*p == '\n' && p[1] != '\0') {
            last = p + 1;
        }
    }
    return last;
}

TEST(shell_create_and_destroy)
{
    BreakEditorShell *shell = break_editor_shell_create_for_test();
    ASSERT_NOT_NULL(shell);
    ASSERT_NOT_NULL(break_editor_shell_doc(shell));
    ASSERT_NOT_NULL(break_editor_shell_root(shell));
    ASSERT_NOT_NULL(break_editor_shell_window(shell));
    ASSERT_EQ(break_editor_shell_outliner_count(shell), 0u);
    ASSERT_STR_EQ(break_editor_shell_tool_text(shell), "Tool: Select");
    ASSERT_FALSE(break_editor_shell_palette_is_open(shell));
    break_editor_shell_destroy(shell);
    break_editor_shell_destroy(NULL); /* NULL no-op */
}

TEST(add_entity_via_panel_button_increments_outliner)
{
    BreakEditorShell *shell = break_editor_shell_create_for_test();
    BreakEditorDoc *doc;
    BreakEditorEntityId id;
    const char *name = NULL;
    ASSERT_NOT_NULL(shell);
    ASSERT_EQ(break_editor_shell_outliner_count(shell), 0u);
    emit_click(find(shell, "editor-add-button"));
    ASSERT_EQ(break_editor_shell_outliner_count(shell), 1u);
    doc = break_editor_shell_doc(shell);
    ASSERT_TRUE(break_editor_doc_entity_at(doc, 0, &id, &name));
    ASSERT_TRUE(strstr(name, "entity_") == name);
    ASSERT_TRUE(break_editor_doc_is_dirty(doc));
    break_editor_shell_destroy(shell);
}

TEST(add_entity_via_palette_and_ctrl_z_removes_row)
{
    BreakEditorShell *shell = break_editor_shell_create_for_test();
    ASSERT_NOT_NULL(shell);
    ASSERT_TRUE(break_editor_shell_dispatch_key(shell, 'p', MY_KEYMOD_CTRL));
    ASSERT_TRUE(break_editor_shell_palette_is_open(shell));
    ASSERT_TRUE(break_editor_shell_palette_set_filter(shell, "add"));
    ASSERT_EQ(break_editor_shell_palette_count(shell), 1u);
    ASSERT_TRUE(break_editor_shell_dispatch_key(shell, MY_KEY_RETURN, 0u));
    ASSERT_FALSE(break_editor_shell_palette_is_open(shell));
    ASSERT_EQ(break_editor_shell_outliner_count(shell), 1u);
    /* Ctrl+Z removes the row; Ctrl+Y restores it. */
    ASSERT_TRUE(break_editor_shell_dispatch_key(shell, 'z', MY_KEYMOD_CTRL));
    ASSERT_EQ(break_editor_shell_outliner_count(shell), 0u);
    ASSERT_TRUE(break_editor_shell_dispatch_key(shell, 'y', MY_KEYMOD_CTRL));
    ASSERT_EQ(break_editor_shell_outliner_count(shell), 1u);
    break_editor_shell_destroy(shell);
}

TEST(remove_selected_via_panel_button)
{
    BreakEditorShell *shell = break_editor_shell_create_for_test();
    ASSERT_NOT_NULL(shell);
    emit_click(find(shell, "editor-add-button"));
    emit_click(find(shell, "editor-add-button"));
    ASSERT_EQ(break_editor_shell_outliner_count(shell), 2u);
    ASSERT_TRUE(break_editor_shell_select_index(shell, 1));
    emit_click(find(shell, "editor-remove-button"));
    ASSERT_EQ(break_editor_shell_outliner_count(shell), 1u);
    /* Selection tracked the removed entity: it must be cleared. */
    ASSERT_FALSE(break_editor_entity_id_valid(
        break_editor_shell_selected(shell)));
    /* Undo restores the removed entity (Task 1 remove command revert). */
    ASSERT_TRUE(break_editor_shell_dispatch_key(shell, 'z', MY_KEYMOD_CTRL));
    ASSERT_EQ(break_editor_shell_outliner_count(shell), 2u);
    break_editor_shell_destroy(shell);
}

TEST(remove_selected_console_line_names_removed_entity)
{
    BreakEditorShell *shell = break_editor_shell_create_for_test();
    BreakEditorDoc *doc;
    BreakEditorEntityId id;
    const char *name = NULL;
    const char *last;
    char saved_name[BREAK_EDITOR_NAME_CAPACITY];
    char expected[BREAK_EDITOR_NAME_CAPACITY + 32u];
    ASSERT_NOT_NULL(shell);
    emit_click(find(shell, "editor-add-button"));
    ASSERT_TRUE(break_editor_shell_select_index(shell, 0));
    doc = break_editor_shell_doc(shell);
    ASSERT_TRUE(break_editor_doc_entity_at(doc, 0, &id, &name));
    snprintf(saved_name, sizeof(saved_name), "%s", name);
    emit_click(find(shell, "editor-remove-button"));
    ASSERT_EQ(break_editor_shell_outliner_count(shell), 0u);
    /* Regression pin: shell_do_remove_selected must copy the borrowed
     * entity_at name BEFORE break_editor_doc_remove_entity clears the slot
     * (slot_clear zeroes name[0], editor_doc.c) — the console's latest line
     * names the removed entity, never "remove entity ''". */
    last = last_console_line(break_editor_shell_console_text(shell));
    snprintf(expected, sizeof(expected), "remove entity '%s'", saved_name);
    ASSERT_TRUE(strstr(last, expected) == last);
    break_editor_shell_destroy(shell);
}

TEST(rename_via_name_edit_then_undo_reverts_displayed_name)
{
    BreakEditorShell *shell = break_editor_shell_create_for_test();
    BreakEditorDoc *doc;
    BreakEditorEntityId id;
    const char *name = NULL;
    my_widget_t *edit;
    char old_name[BREAK_EDITOR_NAME_CAPACITY];
    ASSERT_NOT_NULL(shell);
    emit_click(find(shell, "editor-add-button"));
    ASSERT_TRUE(break_editor_shell_select_index(shell, 0));
    doc = break_editor_shell_doc(shell);
    ASSERT_TRUE(break_editor_doc_entity_at(doc, 0, &id, &name));
    snprintf(old_name, sizeof(old_name), "%s", name);
    edit = find(shell, "editor-name-edit");
    ASSERT_NOT_NULL(edit);
    ASSERT_STR_EQ(my_edit_get_text(edit), old_name);
    ASSERT_EQ(my_edit_set_text(edit, "hero"), MY_RET_OK);
    emit_activate(edit);
    ASSERT_TRUE(break_editor_doc_entity_at(doc, 0, &id, &name));
    ASSERT_STR_EQ(name, "hero");
    /* The inspector displays the committed name... */
    ASSERT_STR_EQ(break_editor_shell_name_edit_text(shell), "hero");
    /* ...and undo reverts both the doc name and the displayed name —
     * proof the edit routed through the command stack, not world_*. */
    ASSERT_TRUE(break_editor_shell_dispatch_key(shell, 'z', MY_KEYMOD_CTRL));
    ASSERT_TRUE(break_editor_doc_entity_at(doc, 0, &id, &name));
    ASSERT_STR_EQ(name, old_name);
    ASSERT_STR_EQ(break_editor_shell_name_edit_text(shell), old_name);
    /* Redo re-applies the rename. */
    ASSERT_TRUE(break_editor_shell_dispatch_key(shell, 'y', MY_KEYMOD_CTRL));
    ASSERT_TRUE(break_editor_doc_entity_at(doc, 0, &id, &name));
    ASSERT_STR_EQ(name, "hero");
    ASSERT_STR_EQ(break_editor_shell_name_edit_text(shell), "hero");
    break_editor_shell_destroy(shell);
}

TEST(tool_keys_update_tool_label)
{
    BreakEditorShell *shell = break_editor_shell_create_for_test();
    ASSERT_NOT_NULL(shell);
    ASSERT_TRUE(break_editor_shell_dispatch_key(shell, 'w', 0u));
    ASSERT_STR_EQ(break_editor_shell_tool_text(shell), "Tool: Translate");
    ASSERT_TRUE(break_editor_shell_dispatch_key(shell, 'e', 0u));
    ASSERT_STR_EQ(break_editor_shell_tool_text(shell), "Tool: Rotate");
    ASSERT_TRUE(break_editor_shell_dispatch_key(shell, 'r', 0u));
    ASSERT_STR_EQ(break_editor_shell_tool_text(shell), "Tool: Scale");
    ASSERT_TRUE(break_editor_shell_dispatch_key(shell, 'q', 0u));
    ASSERT_STR_EQ(break_editor_shell_tool_text(shell), "Tool: Select");
    /* SHIFT ignored for letter tools; ALT blocks the shortcut. */
    ASSERT_TRUE(break_editor_shell_dispatch_key(shell, 'W', MY_KEYMOD_SHIFT));
    ASSERT_STR_EQ(break_editor_shell_tool_text(shell), "Tool: Translate");
    ASSERT_FALSE(break_editor_shell_dispatch_key(shell, 'q', MY_KEYMOD_ALT));
    ASSERT_STR_EQ(break_editor_shell_tool_text(shell), "Tool: Translate");
    /* Unbound keys are not consumed. */
    ASSERT_FALSE(break_editor_shell_dispatch_key(shell, 'x', 0u));
    break_editor_shell_destroy(shell);
}

TEST(focus_key_records_intent_note)
{
    BreakEditorShell *shell = break_editor_shell_create_for_test();
    ASSERT_NOT_NULL(shell);
    emit_click(find(shell, "editor-add-button"));
    ASSERT_TRUE(break_editor_shell_select_index(shell, 0));
    ASSERT_TRUE(break_editor_shell_dispatch_key(shell, 'f', 0u));
    ASSERT_TRUE(strstr(break_editor_shell_status_text(shell), "focus") !=
                NULL);
    ASSERT_TRUE(strstr(break_editor_shell_console_text(shell), "focus") !=
                NULL);
    break_editor_shell_destroy(shell);
}

TEST(palette_opens_filters_and_escape_closes)
{
    BreakEditorShell *shell = break_editor_shell_create_for_test();
    ASSERT_NOT_NULL(shell);
    ASSERT_TRUE(break_editor_shell_dispatch_key(shell, 'p', MY_KEYMOD_CTRL));
    ASSERT_TRUE(break_editor_shell_palette_is_open(shell));
    ASSERT_EQ(break_editor_shell_palette_count(shell), 12u);
    ASSERT_TRUE(break_editor_shell_palette_set_filter(shell, "tool"));
    ASSERT_EQ(break_editor_shell_palette_count(shell), 4u);
    ASSERT_TRUE(break_editor_shell_palette_set_filter(shell, "save"));
    ASSERT_EQ(break_editor_shell_palette_count(shell), 1u);
    ASSERT_TRUE(break_editor_shell_palette_set_filter(shell, "zzz-no-match"));
    ASSERT_EQ(break_editor_shell_palette_count(shell), 0u);
    ASSERT_TRUE(break_editor_shell_dispatch_key(shell, MY_KEY_ESCAPE, 0u));
    ASSERT_FALSE(break_editor_shell_palette_is_open(shell));
    /* Ctrl+P toggles open again. */
    ASSERT_TRUE(break_editor_shell_dispatch_key(shell, 'p', MY_KEYMOD_CTRL));
    ASSERT_TRUE(break_editor_shell_palette_is_open(shell));
    ASSERT_TRUE(break_editor_shell_dispatch_key(shell, 'p', MY_KEYMOD_CTRL));
    ASSERT_FALSE(break_editor_shell_palette_is_open(shell));
    break_editor_shell_destroy(shell);
}

TEST(palette_executes_tool_command_on_activate)
{
    BreakEditorShell *shell = break_editor_shell_create_for_test();
    my_widget_t *edit;
    ASSERT_NOT_NULL(shell);
    ASSERT_TRUE(break_editor_shell_dispatch_key(shell, 'p', MY_KEYMOD_CTRL));
    ASSERT_TRUE(break_editor_shell_palette_set_filter(shell, "rotate"));
    edit = find(shell, "editor-palette-edit");
    ASSERT_NOT_NULL(edit);
    emit_activate(edit);
    ASSERT_STR_EQ(break_editor_shell_tool_text(shell), "Tool: Rotate");
    ASSERT_FALSE(break_editor_shell_palette_is_open(shell));
    break_editor_shell_destroy(shell);
}

TEST(ctrl_s_saves_to_configured_path)
{
    BreakEditorShell *shell = break_editor_shell_create_for_test();
    BreakEditorDoc *doc;
    char dir[512];
    char path[600];
    char sidecar[700];
    ASSERT_NOT_NULL(shell);
    test_tmp(dir, sizeof(dir), "editor_shell_save");
    TEST_MKDIR(dir);
    snprintf(path, sizeof(path), "%s/scene.bscn", dir);
    snprintf(sidecar, sizeof(sidecar), "%s" BREAK_EDITOR_SIDECAR_SUFFIX, path);
    /* No path configured: Ctrl+S is a bounded no-op (consumed, no file). */
    ASSERT_TRUE(break_editor_shell_dispatch_key(shell, 's', MY_KEYMOD_CTRL));
    ASSERT_FALSE(file_exists(path));
    ASSERT_TRUE(break_editor_shell_set_scene_path(shell, path));
    emit_click(find(shell, "editor-add-button"));
    doc = break_editor_shell_doc(shell);
    ASSERT_TRUE(break_editor_doc_is_dirty(doc));
    ASSERT_TRUE(break_editor_shell_dispatch_key(shell, 's', MY_KEYMOD_CTRL));
    ASSERT_TRUE(file_exists(path));
    ASSERT_TRUE(file_exists(sidecar));
    ASSERT_FALSE(break_editor_doc_is_dirty(doc));
    ASSERT_TRUE(strstr(break_editor_shell_status_text(shell), "saved") !=
                NULL);
    remove(path);
    remove(sidecar);
    TEST_RMDIR(dir);
    break_editor_shell_destroy(shell);
}

TEST(outliner_row_click_selects)
{
    BreakEditorShell *shell = break_editor_shell_create_for_test();
    BreakEditorDoc *doc;
    BreakEditorEntityId first;
    my_widget_t *row;
    ASSERT_NOT_NULL(shell);
    emit_click(find(shell, "editor-add-button"));
    emit_click(find(shell, "editor-add-button"));
    shell_paint(shell); /* realize the virtualized rows */
    row = find(shell, "editor-outliner-row");
    ASSERT_NOT_NULL(row);
    emit_click(row);
    doc = break_editor_shell_doc(shell);
    {
        const char *first_name = NULL;
        ASSERT_TRUE(break_editor_doc_entity_at(doc, 0, &first, &first_name));
        ASSERT_TRUE(break_editor_entity_id_eq(
            break_editor_shell_selected(shell), first));
        /* The inspector mirrors the selection: name edit shows row 0's name. */
        ASSERT_STR_EQ(break_editor_shell_name_edit_text(shell), first_name);
    }
    break_editor_shell_destroy(shell);
}

TEST(rename_then_undo_reverts_outliner_row_text)
{
    BreakEditorShell *shell = break_editor_shell_create_for_test();
    my_widget_t *row;
    my_widget_t *edit;
    const char *row_text;
    char original[BREAK_EDITOR_NAME_CAPACITY];
    ASSERT_NOT_NULL(shell);
    emit_click(find(shell, "editor-add-button"));
    shell_paint(shell); /* realize the virtualized rows */
    row = find(shell, "editor-outliner-row");
    ASSERT_NOT_NULL(row);
    row_text = ((const my_button_t *)row)->text;
    ASSERT_NOT_NULL(row_text);
    /* the row binds the doc's display name, never the "<stale>" fallback
     * (fix-round pin: entity_at rejects NULL out_id, and bind_row must not
     * pass one) */
    ASSERT_TRUE(strcmp(row_text, "<stale>") != 0);
    ASSERT_TRUE(strstr(row_text, "entity_") == row_text);
    snprintf(original, sizeof(original), "%s", row_text);
    /* rename through the shell UI (name edit "activate"), then undo — the
     * OUTLINER ROW's displayed name must follow both ways because rows
     * rebind from the doc on refresh */
    ASSERT_TRUE(break_editor_shell_select_index(shell, 0));
    edit = find(shell, "editor-name-edit");
    ASSERT_NOT_NULL(edit);
    ASSERT_EQ(my_edit_set_text(edit, "hero"), MY_RET_OK);
    emit_activate(edit);
    row = find(shell, "editor-outliner-row");
    ASSERT_NOT_NULL(row);
    ASSERT_STR_EQ(((const my_button_t *)row)->text, "hero");
    ASSERT_TRUE(break_editor_shell_dispatch_key(shell, 'z', MY_KEYMOD_CTRL));
    row = find(shell, "editor-outliner-row");
    ASSERT_NOT_NULL(row);
    ASSERT_STR_EQ(((const my_button_t *)row)->text, original);
    /* redo re-applies the displayed rename */
    ASSERT_TRUE(break_editor_shell_dispatch_key(shell, 'y', MY_KEYMOD_CTRL));
    row = find(shell, "editor-outliner-row");
    ASSERT_NOT_NULL(row);
    ASSERT_STR_EQ(((const my_button_t *)row)->text, "hero");
    break_editor_shell_destroy(shell);
}

TEST(inspector_field_edit_routes_through_command_stack)
{
    BreakEditorShell *shell = break_editor_shell_create_for_test();
    BreakEditorDoc *doc;
    BreakEditorEntityId id;
    my_widget_t *add_btn;
    my_widget_t *field;
    f32 value = 0.0f;
    char field_name[64];
    const char *unused_name = NULL;
    ASSERT_NOT_NULL(shell);
    emit_click(find(shell, "editor-add-button"));
    ASSERT_TRUE(break_editor_shell_select_index(shell, 0));
    doc = break_editor_shell_doc(shell);
    ASSERT_TRUE(break_editor_doc_entity_at(doc, 0, &id, &unused_name));
    ASSERT_FALSE(break_editor_doc_has_component(
        doc, id, BREAK_EDITOR_COMPONENT_TRANSFORM));
    add_btn = find(shell, "editor-component-add-64");
    ASSERT_NOT_NULL(add_btn);
    emit_click(add_btn);
    ASSERT_TRUE(break_editor_doc_has_component(doc, id,
                                               BREAK_EDITOR_COMPONENT_TRANSFORM));
    snprintf(field_name, sizeof(field_name), "editor-field-%u-%u",
             BREAK_EDITOR_COMPONENT_TRANSFORM, 0u);
    field = find(shell, field_name);
    ASSERT_NOT_NULL(field);
    ASSERT_EQ(my_edit_set_text(field, "1.5"), MY_RET_OK);
    emit_activate(field);
    ASSERT_TRUE(break_editor_doc_get_field_f32(
        doc, id, BREAK_EDITOR_COMPONENT_TRANSFORM, 0u, &value));
    ASSERT_FLOAT_EQ(value, 1.5f, 1e-6f);
    /* Undo restores the previous 4 bytes and the displayed text. */
    ASSERT_TRUE(break_editor_shell_dispatch_key(shell, 'z', MY_KEYMOD_CTRL));
    ASSERT_TRUE(break_editor_doc_get_field_f32(
        doc, id, BREAK_EDITOR_COMPONENT_TRANSFORM, 0u, &value));
    ASSERT_FLOAT_EQ(value, 0.0f, 1e-6f);
    ASSERT_STR_EQ(my_edit_get_text(find(shell, field_name)), "0");
    /* Garbage input is bounded-rejected and the doc is unchanged. */
    field = find(shell, field_name);
    ASSERT_EQ(my_edit_set_text(field, "not-a-number"), MY_RET_OK);
    emit_activate(field);
    ASSERT_TRUE(break_editor_doc_get_field_f32(
        doc, id, BREAK_EDITOR_COMPONENT_TRANSFORM, 0u, &value));
    ASSERT_FLOAT_EQ(value, 0.0f, 1e-6f);
    /* Undo of the component add removes it again. */
    ASSERT_TRUE(break_editor_shell_dispatch_key(shell, 'z', MY_KEYMOD_CTRL));
    ASSERT_FALSE(break_editor_doc_has_component(
        doc, id, BREAK_EDITOR_COMPONENT_TRANSFORM));
    break_editor_shell_destroy(shell);
}

TEST(console_ring_is_bounded_at_64_entries)
{
    BreakEditorShell *shell = break_editor_shell_create_for_test();
    const char *text;
    usize lines = 0u;
    int i;
    ASSERT_NOT_NULL(shell);
    for (i = 0; i < 70; i++) {
        emit_click(find(shell, "editor-add-button"));
    }
    ASSERT_EQ(break_editor_shell_outliner_count(shell), 70u);
    text = break_editor_shell_console_text(shell);
    ASSERT_NOT_NULL(text);
    for (i = 0; text[i] != '\0'; i++) {
        if (text[i] == '\n') {
            lines++;
        }
    }
    ASSERT_EQ(lines, 64u);
    break_editor_shell_destroy(shell);
}

TEST(ppm_smoke_paints_expected_theme_colors)
{
    BreakEditorShell *shell = break_editor_shell_create_for_test();
    my_window_t *win;
    my_lcd_t *lcd;
    const uint8_t *pixels;
    uint32_t stride;
    size_t bg_count = 0u;
    size_t button_count = 0u;
    size_t viewport_count = 0u;
    uint32_t x, y;
    ASSERT_NOT_NULL(shell);
    emit_click(find(shell, "editor-add-button"));
    ASSERT_TRUE(break_editor_shell_dispatch_key(shell, 'p', MY_KEYMOD_CTRL));
    shell_paint(shell);
    win = break_editor_shell_window(shell);
    lcd = my_pal_window_get_lcd(win->pal_window);
    ASSERT_NOT_NULL(lcd);
    pixels = my_lcd_mem_get_buffer(lcd);
    stride = my_lcd_mem_get_stride(lcd);
    ASSERT_NOT_NULL(pixels);
    /* Discriminating discriminant (recalibrated 2026-10-28 for the editor
     * sheet, editor_theme.c): tool-window surfaces paint the window colour
     * #2B2D30, content surfaces (lists, console) #1E1F22, and the viewport
     * panel its placeholder rgb(30,31,34). A never-painted dummy lcd stays
     * zero-filled, so every count is 0 unless a frame was rendered; the
     * three colours are distinct, so each count is pinned on its own. The
     * lcd is BGRA8888 on some configs: accept either channel order. */
    for (y = 0u; y < 480u; y++) {
        for (x = 0u; x < 800u; x++) {
            const uint8_t *p = pixels + y * stride + x * 4u;
            if ((p[0] == 0x2bu && p[1] == 0x2du && p[2] == 0x30u) ||
                (p[0] == 0x30u && p[1] == 0x2du && p[2] == 0x2bu)) {
                bg_count++;
            } else if ((p[0] == 0x1eu && p[1] == 0x1fu && p[2] == 0x22u) ||
                       (p[0] == 0x22u && p[1] == 0x1fu && p[2] == 0x1eu)) {
                /* content colour: lists, console, outliner rows and the
                 * viewport placeholder (the same #1E1F22) */
                button_count++;
            }
        }
    }
    printf("    (ppm smoke: %zu tool-window px, %zu content px, %zu viewport "
           "placeholder px)\n",
           bg_count, button_count, viewport_count);
    /* tool windows paint broadly (the palette only covers part of them) */
    ASSERT_TRUE(bg_count > (800u * 480u) / 10u);
    /* ...and the lists, console and viewport placeholder (dummy path: no
     * FBO, ~125k px) painted the content colour */
    ASSERT_TRUE(button_count > 150000u);
    /* the viewport panel itself is the placeholder colour at its centre */
    {
        my_widget_t *vpw = find(shell, "editor-viewport");
        int32_t gx = 0, gy = 0;
        const uint8_t *p;
        ASSERT_NOT_NULL(vpw);
        my_widget_local_to_global(vpw, &gx, &gy);
        gx += vpw->rect.w / 2;
        gy += vpw->rect.h - 4; /* below the open palette */
        p = pixels + (uint32_t)gy * stride + (uint32_t)gx * 4u;
        viewport_count = (p[1] == 31u && (p[0] == 30u || p[0] == 34u)) ? 1u : 0u;
        ASSERT_EQ(viewport_count, 1u);
    }
    break_editor_shell_destroy(shell);
}

/* ---------------- Phase 2 Task 3: viewport panel + wiring ---------------- */

/* Projects a world point through the shell camera's PUBLIC view/proj into
 * the viewport widget's local pixel space (top-left origin, the same
 * unprojection convention break_editor_viewport_screen_ray inverts). */
static bool project_to_viewport(BreakEditorShell *shell,
                                const my_widget_t *vp, const f32 wp[3],
                                f32 out_local[2]) {
    const BreakEditorCamera *cam = break_editor_shell_camera(shell);
    f32 v[16], p[16];
    f32 vx, vy, vz, vw;
    f32 cx, cy, cw;
    f32 ndc_x, ndc_y;
    if (cam == NULL || vp == NULL || vp->rect.w <= 0 || vp->rect.h <= 0) {
        return false;
    }
    break_editor_camera_view(cam, v);
    break_editor_camera_proj(cam, (f32)vp->rect.w / (f32)vp->rect.h, p);
    /* Mat4 is column-major e[col][row]; flat index = col*4 + row. */
    vx = v[0] * wp[0] + v[4] * wp[1] + v[8] * wp[2] + v[12];
    vy = v[1] * wp[0] + v[5] * wp[1] + v[9] * wp[2] + v[13];
    vz = v[2] * wp[0] + v[6] * wp[1] + v[10] * wp[2] + v[14];
    vw = v[3] * wp[0] + v[7] * wp[1] + v[11] * wp[2] + v[15];
    cx = p[0] * vx + p[4] * vy + p[8] * vz + p[12] * vw;
    cy = p[1] * vx + p[5] * vy + p[9] * vz + p[13] * vw;
    cw = p[3] * vx + p[7] * vy + p[11] * vz + p[15] * vw;
    if (cw < 1e-6f) {
        return false; /* behind the camera */
    }
    ndc_x = cx / cw;
    ndc_y = cy / cw;
    out_local[0] = (ndc_x + 1.0f) * 0.5f * (f32)vp->rect.w;
    out_local[1] = (1.0f - ndc_y) * 0.5f * (f32)vp->rect.h;
    return true;
}

/* Dispatches one pointer event at a viewport-LOCAL logical pixel position
 * through the real window dispatcher (hit-test + grab semantics included). */
static void viewport_pointer(BreakEditorShell *shell, my_event_type_t type,
                             f32 local_x, f32 local_y, u8 button, u8 mods,
                             int delta) {
    my_widget_t *vp = break_editor_shell_viewport_widget(shell);
    my_window_t *win = break_editor_shell_window(shell);
    my_event_t ev = my_event_init(type);
    int32_t gx = (int32_t)(local_x + 0.5f);
    int32_t gy = (int32_t)(local_y + 0.5f);
    ASSERT_NOT_NULL(vp);
    ASSERT_NOT_NULL(win);
    my_widget_local_to_global(vp, &gx, &gy);
    ev.u.pointer.x = gx;
    ev.u.pointer.y = gy;
    ev.u.pointer.button = button;
    ev.u.pointer.modifiers = mods;
    ev.u.pointer.delta = delta;
    (void)my_event_dispatch(&win->dispatcher, &ev);
}

/* Adds one entity with an EditorTransform at pos via the real panel buttons
 * (command-stack path) and selects it; the caller reads the id back with
 * break_editor_shell_selected(). */
static void add_transformed_entity(BreakEditorShell *shell, f32 px, f32 py,
                                   f32 pz) {
    my_widget_t *field;
    char val[32];
    emit_click(find(shell, "editor-add-button"));
    ASSERT_TRUE(break_editor_shell_select_index(shell, 0u));
    emit_click(find(shell, "editor-component-add-64"));
    ASSERT_TRUE(break_editor_entity_id_valid(break_editor_shell_selected(shell)));
    /* pos.x/y/z are fields 0..2 of the transform component */
    snprintf(val, sizeof(val), "%.9g", (double)px);
    field = find(shell, "editor-field-64-0");
    ASSERT_NOT_NULL(field);
    ASSERT_EQ(my_edit_set_text(field, val), MY_RET_OK);
    emit_activate(field);
    snprintf(val, sizeof(val), "%.9g", (double)py);
    field = find(shell, "editor-field-64-1");
    ASSERT_NOT_NULL(field);
    ASSERT_EQ(my_edit_set_text(field, val), MY_RET_OK);
    emit_activate(field);
    snprintf(val, sizeof(val), "%.9g", (double)pz);
    field = find(shell, "editor-field-64-2");
    ASSERT_NOT_NULL(field);
    ASSERT_EQ(my_edit_set_text(field, val), MY_RET_OK);
    emit_activate(field);
}

TEST(viewport_widget_present_and_laid_out)
{
    BreakEditorShell *shell = break_editor_shell_create_for_test();
    my_widget_t *vp;
    my_widget_t *outliner;
    my_widget_t *inspector;
    my_widget_t *right_panel;
    ASSERT_NOT_NULL(shell);
    vp = break_editor_shell_viewport_widget(shell);
    ASSERT_NOT_NULL(vp);
    ASSERT_TRUE(find(shell, "editor-viewport") == vp);
    shell_paint(shell);
    outliner = find(shell, "editor-outliner-panel");
    inspector = find(shell, "editor-inspector");
    /* Phase 3 Task 3: the inspector is nested in the right column container
     * (inspector over profiler), so the same-parent-space x comparison runs
     * against editor-right-panel (widget->rect is in PARENT coordinates) */
    right_panel = find(shell, "editor-right-panel");
    ASSERT_NOT_NULL(outliner);
    ASSERT_NOT_NULL(inspector);
    ASSERT_NOT_NULL(right_panel);
    /* middle row: outliner 25% | viewport 1f | right column 28% */
    ASSERT_TRUE(vp->rect.w > 0 && vp->rect.h > 0);
    ASSERT_TRUE(vp->rect.x >= outliner->rect.x + outliner->rect.w - 1);
    ASSERT_TRUE(right_panel->rect.x >= vp->rect.x + vp->rect.w - 1);
    ASSERT_TRUE(inspector->rect.w > 0 && inspector->rect.h > 0);
    ASSERT_EQ(vp->rect.h, outliner->rect.h);
    break_editor_shell_destroy(shell);
}

TEST(tool_keys_set_gizmo_mode_and_label)
{
    BreakEditorShell *shell = break_editor_shell_create_for_test();
    ASSERT_NOT_NULL(shell);
    ASSERT_EQ(break_editor_shell_gizmo_mode(shell), BREAK_EDITOR_GIZMO_NONE);
    ASSERT_TRUE(break_editor_shell_dispatch_key(shell, 'w', 0u));
    ASSERT_EQ(break_editor_shell_gizmo_mode(shell),
              BREAK_EDITOR_GIZMO_TRANSLATE);
    ASSERT_STR_EQ(break_editor_shell_tool_text(shell), "Tool: Translate");
    ASSERT_TRUE(break_editor_shell_dispatch_key(shell, 'e', 0u));
    ASSERT_EQ(break_editor_shell_gizmo_mode(shell), BREAK_EDITOR_GIZMO_ROTATE);
    ASSERT_STR_EQ(break_editor_shell_tool_text(shell), "Tool: Rotate");
    ASSERT_TRUE(break_editor_shell_dispatch_key(shell, 'r', 0u));
    ASSERT_EQ(break_editor_shell_gizmo_mode(shell), BREAK_EDITOR_GIZMO_SCALE);
    ASSERT_STR_EQ(break_editor_shell_tool_text(shell), "Tool: Scale");
    ASSERT_TRUE(break_editor_shell_dispatch_key(shell, 'q', 0u));
    ASSERT_EQ(break_editor_shell_gizmo_mode(shell), BREAK_EDITOR_GIZMO_NONE);
    ASSERT_STR_EQ(break_editor_shell_tool_text(shell), "Tool: Select");
    break_editor_shell_destroy(shell);
}

TEST(focus_key_moves_camera_target_to_selection)
{
    BreakEditorShell *shell = break_editor_shell_create_for_test();
    const BreakEditorCamera *cam;
    ASSERT_NOT_NULL(shell);
    add_transformed_entity(shell, 5.0f, 2.0f, -3.0f);
    cam = break_editor_shell_camera(shell);
    ASSERT_NOT_NULL(cam);
    ASSERT_FLOAT_EQ(cam->target[0], 0.0f, 1e-6f);
    ASSERT_TRUE(break_editor_shell_dispatch_key(shell, 'f', 0u));
    cam = break_editor_shell_camera(shell);
    ASSERT_FLOAT_EQ(cam->target[0], 5.0f, 1e-4f);
    ASSERT_FLOAT_EQ(cam->target[1], 2.0f, 1e-4f);
    ASSERT_FLOAT_EQ(cam->target[2], -3.0f, 1e-4f);
    /* focus fits a sane distance (Task 1 contract: clamped, positive) */
    ASSERT_TRUE(cam->distance > 0.04f && cam->distance < 10000.0f);
    ASSERT_TRUE(strstr(break_editor_shell_status_text(shell), "focus") !=
                NULL);
    break_editor_shell_destroy(shell);
}

TEST(pointer_down_on_viewport_picks_entity)
{
    BreakEditorShell *shell = break_editor_shell_create_for_test();
    BreakEditorEntityId id;
    my_widget_t *vp;
    f32 local[2];
    f32 origin[3] = {0.0f, 0.0f, 0.0f};
    ASSERT_NOT_NULL(shell);
    add_transformed_entity(shell, 0.0f, 0.0f, 0.0f);
    id = break_editor_shell_selected(shell);
    shell_paint(shell);
    vp = break_editor_shell_viewport_widget(shell);
    ASSERT_NOT_NULL(vp);
    ASSERT_TRUE(project_to_viewport(shell, vp, origin, local));
    /* left press where the proxy projects: pick selects the entity */
    viewport_pointer(shell, MY_EVENT_POINTER_DOWN, local[0], local[1], 1u,
                     0u, 0);
    ASSERT_TRUE(break_editor_entity_id_eq(break_editor_shell_selected(shell),
                                          id));
    /* left press far off the proxy (top-left corner area): selection clears */
    viewport_pointer(shell, MY_EVENT_POINTER_UP, local[0], local[1], 1u, 0u,
                     0);
    viewport_pointer(shell, MY_EVENT_POINTER_DOWN, 4.0f, 4.0f, 1u, 0u, 0);
    ASSERT_FALSE(break_editor_entity_id_valid(
        break_editor_shell_selected(shell)));
    break_editor_shell_destroy(shell);
}

TEST(gizmo_drag_via_pointer_events_then_single_undo)
{
    BreakEditorShell *shell = break_editor_shell_create_for_test();
    BreakEditorDoc *doc;
    BreakEditorEntityId id;
    my_widget_t *vp;
    BreakEditorGizmoHandle handles[4];
    usize n;
    f32 local[2];
    f32 center[3];
    f32 value = 0.0f;
    f32 dragged = 0.0f;
    ASSERT_NOT_NULL(shell);
    add_transformed_entity(shell, 0.0f, 0.0f, 0.0f);
    id = break_editor_shell_selected(shell);
    doc = break_editor_shell_doc(shell);
    shell_paint(shell);
    vp = break_editor_shell_viewport_widget(shell);
    ASSERT_NOT_NULL(vp);
    /* W = translate mode; selection attached the gizmo */
    ASSERT_TRUE(break_editor_shell_dispatch_key(shell, 'w', 0u));
    n = break_editor_gizmo_handles(break_editor_shell_gizmo(shell), handles,
                                   4u);
    ASSERT_EQ(n, 4u);
    /* X handle center in world space */
    center[0] = 0.5f * (handles[0].aabb_min[0] + handles[0].aabb_max[0]);
    center[1] = 0.5f * (handles[0].aabb_min[1] + handles[0].aabb_max[1]);
    center[2] = 0.5f * (handles[0].aabb_min[2] + handles[0].aabb_max[2]);
    ASSERT_EQ(handles[0].part, BREAK_EDITOR_GIZMO_PART_X);
    ASSERT_TRUE(project_to_viewport(shell, vp, center, local));
    viewport_pointer(shell, MY_EVENT_POINTER_DOWN, local[0], local[1], 1u,
                     0u, 0);
    viewport_pointer(shell, MY_EVENT_POINTER_MOVE, local[0] + 40.0f, local[1],
                     0u, 0u, 0);
    viewport_pointer(shell, MY_EVENT_POINTER_UP, local[0] + 40.0f, local[1],
                     1u, 0u, 0);
    ASSERT_TRUE(break_editor_doc_get_field_f32(
        doc, id, BREAK_EDITOR_COMPONENT_TRANSFORM, 0u, &value));
    ASSERT_TRUE(value > 0.01f); /* dragged right along +X */
    dragged = value;
    /* ONE undo reverts the whole drag (single command contract) */
    ASSERT_TRUE(break_editor_shell_dispatch_key(shell, 'z', MY_KEYMOD_CTRL));
    ASSERT_TRUE(break_editor_doc_get_field_f32(
        doc, id, BREAK_EDITOR_COMPONENT_TRANSFORM, 0u, &value));
    ASSERT_FLOAT_EQ(value, 0.0f, 1e-6f);
    /* redo re-applies the drag result */
    ASSERT_TRUE(break_editor_shell_dispatch_key(shell, 'y', MY_KEYMOD_CTRL));
    ASSERT_TRUE(break_editor_doc_get_field_f32(
        doc, id, BREAK_EDITOR_COMPONENT_TRANSFORM, 0u, &value));
    ASSERT_FLOAT_EQ(value, dragged, 1e-5f);
    break_editor_shell_destroy(shell);
}

TEST(mid_drag_ctrl_z_commits_then_undoes_the_drag)
{
    BreakEditorShell *shell = break_editor_shell_create_for_test();
    BreakEditorDoc *doc;
    BreakEditorEntityId id;
    my_widget_t *vp;
    BreakEditorGizmoHandle handles[4];
    f32 local[2];
    f32 center[3];
    f32 value = 0.0f;
    ASSERT_NOT_NULL(shell);
    add_transformed_entity(shell, 0.0f, 0.0f, 0.0f);
    id = break_editor_shell_selected(shell);
    doc = break_editor_shell_doc(shell);
    shell_paint(shell);
    vp = break_editor_shell_viewport_widget(shell);
    ASSERT_NOT_NULL(vp);
    ASSERT_TRUE(break_editor_shell_dispatch_key(shell, 'w', 0u));
    ASSERT_EQ(break_editor_gizmo_handles(break_editor_shell_gizmo(shell),
                                         handles, 4u),
              4u);
    center[0] = 0.5f * (handles[0].aabb_min[0] + handles[0].aabb_max[0]);
    center[1] = 0.5f * (handles[0].aabb_min[1] + handles[0].aabb_max[1]);
    center[2] = 0.5f * (handles[0].aabb_min[2] + handles[0].aabb_max[2]);
    ASSERT_TRUE(project_to_viewport(shell, vp, center, local));
    viewport_pointer(shell, MY_EVENT_POINTER_DOWN, local[0], local[1], 1u,
                     0u, 0);
    viewport_pointer(shell, MY_EVENT_POINTER_MOVE, local[0] + 40.0f, local[1],
                     0u, 0u, 0);
    ASSERT_TRUE(break_editor_doc_get_field_f32(
        doc, id, BREAK_EDITOR_COMPONENT_TRANSFORM, 0u, &value));
    ASSERT_TRUE(value > 0.01f); /* mid-drag: live write happened */
    /* External undo mid-drag: the drag is ended+committed FIRST, then the
     * undo reverts exactly that committed drag (documented policy). */
    ASSERT_TRUE(break_editor_shell_dispatch_key(shell, 'z', MY_KEYMOD_CTRL));
    ASSERT_TRUE(break_editor_doc_get_field_f32(
        doc, id, BREAK_EDITOR_COMPONENT_TRANSFORM, 0u, &value));
    ASSERT_FLOAT_EQ(value, 0.0f, 1e-6f);
    /* the drag is closed: further moves write nothing, the up is a no-op */
    viewport_pointer(shell, MY_EVENT_POINTER_MOVE, local[0] + 80.0f, local[1],
                     0u, 0u, 0);
    viewport_pointer(shell, MY_EVENT_POINTER_UP, local[0] + 80.0f, local[1],
                     1u, 0u, 0);
    ASSERT_TRUE(break_editor_doc_get_field_f32(
        doc, id, BREAK_EDITOR_COMPONENT_TRANSFORM, 0u, &value));
    ASSERT_FLOAT_EQ(value, 0.0f, 1e-6f);
    break_editor_shell_destroy(shell);
}

TEST(camera_orbit_pan_zoom_via_pointer_and_wheel)
{
    BreakEditorShell *shell = break_editor_shell_create_for_test();
    const BreakEditorCamera *cam;
    f32 yaw0, dist0;
    f32 target0[3];
    ASSERT_NOT_NULL(shell);
    shell_paint(shell);
    cam = break_editor_shell_camera(shell);
    ASSERT_NOT_NULL(cam);
    yaw0 = cam->yaw;
    dist0 = cam->distance;
    target0[0] = cam->target[0];
    target0[1] = cam->target[1];
    target0[2] = cam->target[2];
    /* right-drag orbits */
    viewport_pointer(shell, MY_EVENT_POINTER_DOWN, 100.0f, 100.0f, 3u, 0u, 0);
    viewport_pointer(shell, MY_EVENT_POINTER_MOVE, 160.0f, 100.0f, 0u, 0u, 0);
    viewport_pointer(shell, MY_EVENT_POINTER_UP, 160.0f, 100.0f, 3u, 0u, 0);
    ASSERT_TRUE(cam->yaw != yaw0);
    /* shift+left-drag pans */
    viewport_pointer(shell, MY_EVENT_POINTER_DOWN, 100.0f, 100.0f, 1u,
                     MY_KEYMOD_SHIFT, 0);
    viewport_pointer(shell, MY_EVENT_POINTER_MOVE, 100.0f, 140.0f, 0u,
                     MY_KEYMOD_SHIFT, 0);
    viewport_pointer(shell, MY_EVENT_POINTER_UP, 100.0f, 140.0f, 1u,
                     MY_KEYMOD_SHIFT, 0);
    ASSERT_TRUE(cam->target[0] != target0[0] || cam->target[1] != target0[1] ||
                cam->target[2] != target0[2]);
    /* wheel zooms */
    viewport_pointer(shell, MY_EVENT_POINTER_WHEEL, 100.0f, 100.0f, 0u, 0u,
                     3);
    ASSERT_TRUE(cam->distance < dist0); /* positive delta zooms in */
    /* camera moves are view state: nothing undoable was recorded */
    {
        char last[128];
        last[0] = '\0';
        (void)break_editor_cmd_stack_describe_last(
            break_editor_doc_stack(break_editor_shell_doc(shell)), last);
        ASSERT_STR_EQ(last, "");
    }
    break_editor_shell_destroy(shell);
}

TEST(viewport_render_without_device_is_bounded_noop)
{
    BreakEditorShell *shell = break_editor_shell_create_for_test();
    ASSERT_NOT_NULL(shell);
    /* dummy-PAL path: no RHI device — the render entry must be a guarded
     * no-op (and the per-frame tick must be safe too). */
    break_editor_shell_tick(shell);
    break_editor_shell_render_viewport(shell, NULL, NULL, 800, 480, 800, 480);
    break_editor_shell_tick(NULL);
    break_editor_shell_render_viewport(NULL, NULL, NULL, 0, 0, 0, 0);
    break_editor_shell_destroy(shell);
}

/* Render debugger (docs/design/editor_render_debugger.md §2): the viewport
 * records CPU-side stats for its last render call — never a GPU readback.
 * Headless: a tiny panel and a device whose init fails (the test RHI stubs
 * report no capabilities) each land on a distinct skip reason. */
TEST(viewport_last_stats_report_skip_reasons_headless)
{
    BreakEditorShell *shell = break_editor_shell_create_for_test();
    BreakEditorViewport3D *vp;
    BreakEditorViewport3DStats st;
    static int fake_device, fake_cmd;
    ASSERT_NOT_NULL(shell);
    vp = break_editor_shell_viewport3d(shell);
    ASSERT_NOT_NULL(vp);

    ASSERT_TRUE(break_editor_viewport3d_last_stats(vp, &st));
    ASSERT_EQ(st.init_state, BREAK_EDITOR_VIEWPORT3D_INIT_NOT_ATTEMPTED);
    ASSERT_EQ(st.draws, 0u);
    ASSERT_STR_EQ(break_editor_viewport3d_skip_name(st.skipped), "not-rendered");

    break_editor_viewport3d_render(vp, break_editor_shell_doc(shell),
                                   &fake_device, &fake_cmd, 8, 8);
    ASSERT_TRUE(break_editor_viewport3d_last_stats(vp, &st));
    ASSERT_STR_EQ(break_editor_viewport3d_skip_name(st.skipped), "panel-too-small");

    break_editor_viewport3d_render(vp, break_editor_shell_doc(shell),
                                   &fake_device, &fake_cmd, 200, 120);
    ASSERT_TRUE(break_editor_viewport3d_last_stats(vp, &st));
    ASSERT_EQ(st.init_state, BREAK_EDITOR_VIEWPORT3D_INIT_FAILED);
    ASSERT_STR_EQ(break_editor_viewport3d_skip_name(st.skipped), "init-failed");
    ASSERT_EQ(st.draws, 0u);
    ASSERT_EQ(st.proxies, 0u);
    ASSERT_EQ(st.gizmo_handles, 0u);

    ASSERT_FALSE(break_editor_viewport3d_last_stats(NULL, &st));
    ASSERT_FALSE(break_editor_viewport3d_last_stats(vp, NULL));
    ASSERT_NOT_NULL(break_editor_viewport3d_skip_name(-1));
    break_editor_shell_destroy(shell);
}

TEST(viewport_shell_wrapper_records_no_device)
{
    BreakEditorShell *shell = break_editor_shell_create_for_test();
    BreakEditorViewport3DStats st;
    ASSERT_NOT_NULL(shell);
    break_editor_shell_render_viewport(shell, NULL, NULL, 800, 480, 800, 480);
    ASSERT_TRUE(break_editor_viewport3d_last_stats(
        break_editor_shell_viewport3d(shell), &st));
    ASSERT_STR_EQ(break_editor_viewport3d_skip_name(st.skipped), "no-device");
    break_editor_shell_destroy(shell);
}

TEST(model_matrix_known_answers)
{
    f32 m[16];
    /* pos (1,2,3), yaw 90 deg about Y, scale 2: local +X -> world -Z
     * (R_y(90): x' = z, z' = -x), scaled, then translated. */
    break_editor_viewport3d_model_matrix(
        (const f32[]){1.0f, 2.0f, 3.0f}, (const f32[]){0.0f, 90.0f, 0.0f},
        (const f32[]){2.0f, 2.0f, 2.0f}, m);
    {
        /* M * (1,0,0,1) column-vector: row i = m[i] + m[4+i]*0 + ... */
        f32 px = m[0] * 1.0f + m[12];
        f32 py = m[1] * 1.0f + m[13];
        f32 pz = m[2] * 1.0f + m[14];
        ASSERT_FLOAT_EQ(px, 1.0f, 1e-4f);
        ASSERT_FLOAT_EQ(py, 2.0f, 1e-4f);
        ASSERT_FLOAT_EQ(pz, 1.0f, 1e-4f); /* -2 + 3 */
    }
    /* composition order pin: M = R_y * R_x * R_z — (0,1,0) through
     * pitch 90 then yaw 90 lands on +X, not +Z. */
    break_editor_viewport3d_model_matrix(
        (const f32[]){0.0f, 0.0f, 0.0f}, (const f32[]){90.0f, 90.0f, 0.0f},
        (const f32[]){1.0f, 1.0f, 1.0f}, m);
    {
        f32 px = m[4];
        f32 py = m[5];
        f32 pz = m[6];
        ASSERT_FLOAT_EQ(px, 1.0f, 1e-4f);
        ASSERT_FLOAT_EQ(py, 0.0f, 1e-4f);
        ASSERT_FLOAT_EQ(pz, 0.0f, 1e-4f);
    }
    /* degrees, not radians: rot.x = 90 must be a quarter turn */
    break_editor_viewport3d_model_matrix(
        (const f32[]){0.0f, 0.0f, 0.0f}, (const f32[]){90.0f, 0.0f, 0.0f},
        (const f32[]){1.0f, 1.0f, 1.0f}, m);
    {
        /* R_x(90): (0,1,0) -> (0,0,1) */
        ASSERT_FLOAT_EQ(m[5], 0.0f, 1e-4f);
        ASSERT_FLOAT_EQ(m[6], 1.0f, 1e-4f);
    }
}

static bool write_text_file(const char *path, const char *text) {
    FILE *f = fopen(path, "wb");
    if (f == NULL) {
        return false;
    }
    fputs(text, f);
    return fclose(f) == 0;
}

/* ---------------- shader source resolution ---------------- */

#if !defined(_WIN32)
extern int setenv(const char *name, const char *value, int overwrite);
extern int unsetenv(const char *name);
#endif

typedef struct {
    char *value;
} EditorShaderEnv;

static bool shader_env_save(EditorShaderEnv *env) {
    const char *value = getenv("BREAK_SHADER_DIR");
    size_t size;
    env->value = NULL;
    if (value == NULL) {
        return true;
    }
    size = strlen(value) + 1u;
    env->value = (char *)malloc(size);
    if (env->value != NULL) {
        memcpy(env->value, value, size);
    }
    return env->value != NULL;
}

static bool shader_env_set(const char *value) {
#if defined(_WIN32)
    return _putenv_s("BREAK_SHADER_DIR", value) == 0;
#else
    return setenv("BREAK_SHADER_DIR", value, 1) == 0;
#endif
}

static void shader_env_restore(EditorShaderEnv *env) {
    if (env->value != NULL) {
        (void)shader_env_set(env->value);
        free(env->value);
    } else {
#if defined(_WIN32)
        (void)_putenv_s("BREAK_SHADER_DIR", "");
#else
        (void)unsetenv("BREAK_SHADER_DIR");
#endif
    }
    env->value = NULL;
}

static void assert_shader_read(const BreakEditorShaderSource *source,
                               BreakEditorShaderStage stage,
                               const char *expected_path,
                               const char *expected_data) {
    BreakEditorShaderBytes bytes;
    memset(&bytes, 0, sizeof(bytes));
    ASSERT_TRUE(break_editor_shader_source_read(source, stage, &bytes));
    ASSERT_STR_EQ(bytes.path, expected_path);
    ASSERT_EQ(bytes.size, strlen(expected_data));
    ASSERT_STR_EQ(bytes.data, expected_data);
    ASSERT_EQ(bytes.data[bytes.size], '\0');
    break_editor_shader_source_destroy_bytes(&bytes);
    ASSERT_TRUE(bytes.data == NULL && bytes.size == 0u);
    ASSERT_EQ(bytes.path[0], '\0');
}

static void shader_source_variants_body(void) {
    BreakEditorShaderSource source;
    char root[512], shaders[600];
    char vert[700], frag[700], vert_vk[700], frag_vk[700];
    test_tmp(root, sizeof(root), "editor_shader_source_variants");
    snprintf(shaders, sizeof(shaders), "%s/shaders", root);
    snprintf(vert, sizeof(vert), "%s/editor_color.vert", shaders);
    snprintf(frag, sizeof(frag), "%s/editor_color.frag", shaders);
    snprintf(vert_vk, sizeof(vert_vk), "%s/editor_color_vk.vert", shaders);
    snprintf(frag_vk, sizeof(frag_vk), "%s/editor_color_vk.frag", shaders);
    ASSERT_EQ(TEST_MKDIR(root), 0);
    ASSERT_EQ(TEST_MKDIR(shaders), 0);
    ASSERT_TRUE(write_text_file(vert, "REV=1 vertex\n"));
    ASSERT_TRUE(write_text_file(frag, "REV=1 fragment\n"));
    ASSERT_TRUE(write_text_file(vert_vk, "REV=1 vertex vk\n"));
    ASSERT_TRUE(write_text_file(frag_vk, "REV=1 fragment vk\n"));
    ASSERT_TRUE(shader_env_set(root));

    ASSERT_TRUE(break_editor_shader_source_configure(
        &source, RHI_SHADER_VARIANT_GLSL));
    ASSERT_EQ(source.root_count, 5u);
    ASSERT_EQ(source.skipped_roots, 0u);
    ASSERT_STR_EQ(source.roots[0], root);
    ASSERT_STR_EQ(source.roots[1], ".");
    ASSERT_STR_EQ(source.roots[2], "engine");
    ASSERT_STR_EQ(source.roots[3], "../engine");
    ASSERT_STR_EQ(source.roots[4], "../../engine");
    ASSERT_STR_EQ(break_editor_shader_source_path(
        &source, BREAK_EDITOR_SHADER_VERTEX), "shaders/editor_color.vert");
    ASSERT_STR_EQ(break_editor_shader_source_path(
        &source, BREAK_EDITOR_SHADER_FRAGMENT), "shaders/editor_color.frag");
    assert_shader_read(&source, BREAK_EDITOR_SHADER_VERTEX, vert,
                       "REV=1 vertex\n");
    assert_shader_read(&source, BREAK_EDITOR_SHADER_FRAGMENT, frag,
                       "REV=1 fragment\n");

    ASSERT_TRUE(break_editor_shader_source_configure(
        &source, RHI_SHADER_VARIANT_GLSL_VK));
    ASSERT_STR_EQ(break_editor_shader_source_path(
        &source, BREAK_EDITOR_SHADER_VERTEX), "shaders/editor_color_vk.vert");
    ASSERT_STR_EQ(break_editor_shader_source_path(
        &source, BREAK_EDITOR_SHADER_FRAGMENT), "shaders/editor_color_vk.frag");
    assert_shader_read(&source, BREAK_EDITOR_SHADER_VERTEX, vert_vk,
                       "REV=1 vertex vk\n");
    assert_shader_read(&source, BREAK_EDITOR_SHADER_FRAGMENT, frag_vk,
                       "REV=1 fragment vk\n");

    remove(vert);
    remove(frag);
    remove(vert_vk);
    remove(frag_vk);
    TEST_RMDIR(shaders);
    TEST_RMDIR(root);
}

TEST(shader_source_resolves_variant_paths_bytes_and_cleanup)
{
    EditorShaderEnv env;
    ASSERT_TRUE(shader_env_save(&env));
    shader_source_variants_body();
    shader_env_restore(&env);
}

static void shader_source_empty_fallback_body(void) {
    static const char fallback_data[] = "REV=2 fallback vertex\n";
    BreakEditorShaderSource source;
    BreakEditorShaderBytes bytes;
    char root[512], shaders[600], vert[700];
    char fallback_root[512], fallback_shaders[600], fallback_vert[700];
    size_t fallback_len;
    test_tmp(root, sizeof(root), "editor_shader_source_fallback");
    test_tmp(fallback_root, sizeof(fallback_root),
             "editor_shader_source_fallback_low");
    snprintf(shaders, sizeof(shaders), "%s/shaders", root);
    snprintf(vert, sizeof(vert), "%s/editor_color.vert", shaders);
    snprintf(fallback_shaders, sizeof(fallback_shaders), "%s/shaders",
             fallback_root);
    snprintf(fallback_vert, sizeof(fallback_vert), "%s/editor_color.vert",
             fallback_shaders);
    ASSERT_EQ(TEST_MKDIR(root), 0);
    ASSERT_EQ(TEST_MKDIR(shaders), 0);
    ASSERT_EQ(TEST_MKDIR(fallback_root), 0);
    ASSERT_EQ(TEST_MKDIR(fallback_shaders), 0);
    ASSERT_TRUE(write_text_file(vert, ""));
    ASSERT_TRUE(write_text_file(fallback_vert, fallback_data));
    ASSERT_TRUE(shader_env_set(root));
    ASSERT_TRUE(break_editor_shader_source_configure(
        &source, RHI_SHADER_VARIANT_GLSL));
    fallback_len = strlen(fallback_root);
    ASSERT_TRUE(fallback_len < sizeof(source.roots[1]));
    source.root_count = 2u;
    memcpy(source.roots[1], fallback_root, fallback_len + 1u);

    memset(&bytes, 0, sizeof(bytes));
    ASSERT_TRUE(break_editor_shader_source_read(
        &source, BREAK_EDITOR_SHADER_VERTEX, &bytes));
    ASSERT_STR_EQ(bytes.path, vert);
    ASSERT_EQ(bytes.size, 0u);
    ASSERT_NOT_NULL(bytes.data);
    ASSERT_EQ(bytes.data[0], '\0');
    break_editor_shader_source_destroy_bytes(&bytes);

    ASSERT_EQ(remove(vert), 0);
    memset(&bytes, 0, sizeof(bytes));
    ASSERT_TRUE(break_editor_shader_source_read(
        &source, BREAK_EDITOR_SHADER_VERTEX, &bytes));
    ASSERT_STR_EQ(bytes.path, fallback_vert);
    ASSERT_TRUE(strcmp(bytes.path, vert) != 0);
    ASSERT_TRUE(file_exists(bytes.path));
    ASSERT_EQ(bytes.size, strlen(fallback_data));
    ASSERT_STR_EQ(bytes.data, fallback_data);
    break_editor_shader_source_destroy_bytes(&bytes);
    remove(fallback_vert);
    TEST_RMDIR(fallback_shaders);
    TEST_RMDIR(fallback_root);
    TEST_RMDIR(shaders);
    TEST_RMDIR(root);
}

TEST(shader_source_empty_file_succeeds_and_missing_root_falls_back)
{
    EditorShaderEnv env;
    ASSERT_TRUE(shader_env_save(&env));
    shader_source_empty_fallback_body();
    shader_env_restore(&env);
}

static void shader_source_all_missing_body(void) {
    BreakEditorShaderSource source;
    BreakEditorShaderBytes bytes;
    char root[512];
    test_tmp(root, sizeof(root), "editor_shader_source_missing");
    ASSERT_EQ(TEST_MKDIR(root), 0);
    ASSERT_TRUE(shader_env_set(root));
    ASSERT_TRUE(break_editor_shader_source_configure(
        &source, RHI_SHADER_VARIANT_GLSL));
    snprintf(source.logical[BREAK_EDITOR_SHADER_VERTEX],
             sizeof(source.logical[BREAK_EDITOR_SHADER_VERTEX]),
             "shaders/break_editor_absent_%d.vert", (int)TEST_GETPID());
    memset(&bytes, 0, sizeof(bytes));
    ASSERT_FALSE(break_editor_shader_source_read(
        &source, BREAK_EDITOR_SHADER_VERTEX, &bytes));
    ASSERT_TRUE(bytes.data == NULL);
    ASSERT_EQ(bytes.size, 0u);
    ASSERT_EQ(bytes.path[0], '\0');
    break_editor_shader_source_destroy_bytes(&bytes);
    ASSERT_TRUE(bytes.data == NULL && bytes.size == 0u);
    TEST_RMDIR(root);
}

TEST(shader_source_all_missing_returns_no_partial_bytes)
{
    EditorShaderEnv env;
    ASSERT_TRUE(shader_env_save(&env));
    shader_source_all_missing_body();
    shader_env_restore(&env);
}

static void shader_source_overlong_root_body(void) {
    BreakEditorShaderSource source;
    char root[VFS_MAX_PATH + 32u];
    memset(root, 'x', VFS_MAX_PATH);
    root[VFS_MAX_PATH] = '\0';
    ASSERT_TRUE(shader_env_set(root));
    ASSERT_TRUE(break_editor_shader_source_configure(
        &source, RHI_SHADER_VARIANT_GLSL));
    ASSERT_EQ(source.root_count, 4u);
    ASSERT_EQ(source.skipped_roots, 1u);
    ASSERT_STR_EQ(source.roots[0], ".");
    ASSERT_STR_EQ(source.roots[1], "engine");
    ASSERT_STR_EQ(source.roots[2], "../engine");
    ASSERT_STR_EQ(source.roots[3], "../../engine");
}

TEST(shader_source_overlong_root_is_skipped_not_truncated)
{
    EditorShaderEnv env;
    ASSERT_TRUE(shader_env_save(&env));
    shader_source_overlong_root_body();
    shader_env_restore(&env);
}

/* ---------------- transactional viewport shader candidates ---------------- */

static bool viewport_gpu_state_equal(const BreakEditorViewport3DGpuState *a,
                                     const BreakEditorViewport3DGpuState *b) {
    return a->pipeline.index == b->pipeline.index &&
           a->pipeline.generation == b->pipeline.generation &&
           a->bindings == b->bindings && a->loc_mvp == b->loc_mvp &&
           a->loc_color == b->loc_color && a->vbo.index == b->vbo.index &&
           a->vbo.generation == b->vbo.generation;
}

static bool editor_fake_stats_equal(const EditorRhiFakeStats *a,
                                    const EditorRhiFakeStats *b) {
    return a->pipeline_creates == b->pipeline_creates &&
           a->pipeline_destroys == b->pipeline_destroys &&
           a->binding_destroys == b->binding_destroys &&
           a->buffer_creates == b->buffer_creates &&
           a->live_shaders == b->live_shaders &&
           a->live_pipelines == b->live_pipelines &&
           a->live_bindings == b->live_bindings &&
           a->live_buffers == b->live_buffers;
}

static void viewport_shader_candidate_body(void) {
    static const char good_frag[] = "fragment";
    static const struct {
        const char *vert, *frag;
        u32 pipeline_creates, pipeline_destroys, binding_destroys;
    } failures[] = {
        {"REV=2 COMPILE_FAIL", "fragment", 0u, 0u, 0u},
        {"REV=2 vertex", "REV=2 COMPILE_FAIL", 0u, 0u, 0u},
        {"REV=2 LINK_FAIL", "fragment", 0u, 0u, 0u},
        {"REV=2 BINDINGS_FAIL", "fragment", 1u, 1u, 0u},
        {"REV=2 NO_MVP", "fragment", 1u, 1u, 1u},
        {"REV=2 NO_COLOR", "fragment", 1u, 1u, 1u}
    };
    BreakEditorViewport3D *vp;
    BreakEditorViewport3DGpuState before, after;
    BreakEditorViewport3DStats viewport_stats;
    EditorRhiFakeStats before_stats, after_stats;
    char root[512], shaders[600], vert_path[700], frag_path[700];
    int device = 0, other_device = 0;
    usize i;
    test_tmp(root, sizeof(root), "editor_shader_candidate");
    snprintf(shaders, sizeof(shaders), "%s/shaders", root);
    snprintf(vert_path, sizeof(vert_path), "%s/editor_color.vert", shaders);
    snprintf(frag_path, sizeof(frag_path), "%s/editor_color.frag", shaders);
    ASSERT_EQ(TEST_MKDIR(root), 0);
    ASSERT_EQ(TEST_MKDIR(shaders), 0);
    ASSERT_TRUE(write_text_file(vert_path, "REV=1 vertex\n"));
    ASSERT_TRUE(write_text_file(frag_path, "fragment\n"));
    ASSERT_TRUE(shader_env_set(root));
    vp = break_editor_viewport3d_create();
    ASSERT_NOT_NULL(vp);
    ASSERT_TRUE(break_editor_viewport3d_prepare(vp, &device));
    break_editor_viewport3d_gpu_state_for_test(vp, &before);
    ASSERT_EQ(editor_rhi_fake_pipeline_revision(before.pipeline), 1u);
    ASSERT_TRUE(rhi_handle_valid(before.vbo));
    ASSERT_NOT_NULL(before.bindings);
    ASSERT_TRUE(before.loc_mvp >= 0 && before.loc_color >= 0);
    editor_rhi_fake_stats(&before_stats);
    ASSERT_EQ(before_stats.live_shaders, 0u);
    ASSERT_EQ(before_stats.live_pipelines, 1u);
    ASSERT_EQ(before_stats.live_bindings, 1u);
    ASSERT_EQ(before_stats.live_buffers, 1u);
    ASSERT_EQ(before_stats.buffer_creates, 1u);

    for (i = 0u; i < sizeof(failures) / sizeof(failures[0]); i++) {
        break_editor_viewport3d_gpu_state_for_test(vp, &before);
        editor_rhi_fake_stats(&before_stats);
        ASSERT_FALSE(break_editor_viewport3d_reload_shader_source(
            vp, failures[i].vert, strlen(failures[i].vert),
            failures[i].frag, strlen(failures[i].frag)));
        break_editor_viewport3d_gpu_state_for_test(vp, &after);
        ASSERT_TRUE(viewport_gpu_state_equal(&before, &after));
        ASSERT_EQ(editor_rhi_fake_pipeline_revision(after.pipeline), 1u);
        ASSERT_TRUE(break_editor_viewport3d_last_stats(vp, &viewport_stats));
        ASSERT_EQ(viewport_stats.init_state, BREAK_EDITOR_VIEWPORT3D_INIT_READY);
        editor_rhi_fake_stats(&after_stats);
        ASSERT_EQ(after_stats.live_shaders, 0u);
        ASSERT_EQ(after_stats.live_pipelines, before_stats.live_pipelines);
        ASSERT_EQ(after_stats.live_bindings, before_stats.live_bindings);
        ASSERT_EQ(after_stats.live_buffers, before_stats.live_buffers);
        ASSERT_EQ(after_stats.pipeline_creates,
                  before_stats.pipeline_creates + failures[i].pipeline_creates);
        ASSERT_EQ(after_stats.pipeline_destroys,
                  before_stats.pipeline_destroys + failures[i].pipeline_destroys);
        ASSERT_EQ(after_stats.binding_destroys,
                  before_stats.binding_destroys + failures[i].binding_destroys);
        ASSERT_EQ(after_stats.buffer_creates, before_stats.buffer_creates);
    }

    {
        static const char prefix[] = "REV=2 vertex";
        static const char suffix[] = "REV=9 COMPILE_FAIL";
        char source[64];
        size_t prefix_len = sizeof(prefix) - 1u;
        memset(source, 'x', sizeof(source));
        memcpy(source, prefix, prefix_len);
        memcpy(source + prefix_len, suffix, sizeof(suffix) - 1u);
        ASSERT_TRUE(break_editor_viewport3d_reload_shader_source(
            vp, source, prefix_len, good_frag, sizeof(good_frag) - 1u));
        break_editor_viewport3d_gpu_state_for_test(vp, &after);
        ASSERT_EQ(editor_rhi_fake_pipeline_revision(after.pipeline), 2u);
        editor_rhi_fake_stats(&after_stats);
        ASSERT_EQ(after_stats.live_shaders, 0u);
    }

    break_editor_viewport3d_gpu_state_for_test(vp, &before);
    editor_rhi_fake_stats(&before_stats);
    ASSERT_TRUE(break_editor_viewport3d_reload_shader_source(
        vp, "REV=2 vertex", strlen("REV=2 vertex"),
        good_frag, sizeof(good_frag) - 1u));
    break_editor_viewport3d_gpu_state_for_test(vp, &after);
    ASSERT_EQ(editor_rhi_fake_pipeline_revision(after.pipeline), 2u);
    ASSERT_TRUE(after.pipeline.index != before.pipeline.index ||
                after.pipeline.generation != before.pipeline.generation);
    ASSERT_EQ(after.vbo.index, before.vbo.index);
    ASSERT_EQ(after.vbo.generation, before.vbo.generation);
    editor_rhi_fake_stats(&after_stats);
    ASSERT_EQ(after_stats.live_shaders, 0u);
    ASSERT_EQ(after_stats.live_pipelines, before_stats.live_pipelines);
    ASSERT_EQ(after_stats.live_bindings, before_stats.live_bindings);
    ASSERT_EQ(after_stats.live_buffers, before_stats.live_buffers);
    ASSERT_EQ(after_stats.pipeline_creates, before_stats.pipeline_creates + 1u);
    ASSERT_EQ(after_stats.pipeline_destroys,
              before_stats.pipeline_destroys + 1u);
    ASSERT_EQ(after_stats.binding_destroys, before_stats.binding_destroys + 1u);
    ASSERT_EQ(after_stats.buffer_creates, before_stats.buffer_creates);

    ASSERT_TRUE(break_editor_viewport3d_reload_shader_source(
        vp, "REV=3 vertex", strlen("REV=3 vertex"),
        "REV=2 fragment", strlen("REV=2 fragment")));
    break_editor_viewport3d_gpu_state_for_test(vp, &after);
    ASSERT_EQ(editor_rhi_fake_pipeline_revision(after.pipeline), 3u);
    ASSERT_EQ(editor_rhi_fake_pipeline_stage_revision(after.pipeline, false), 3u);
    ASSERT_EQ(editor_rhi_fake_pipeline_stage_revision(after.pipeline, true), 2u);

    before = after;
    ASSERT_FALSE(break_editor_viewport3d_prepare(vp, &other_device));
    break_editor_viewport3d_gpu_state_for_test(vp, &after);
    ASSERT_TRUE(viewport_gpu_state_equal(&before, &after));
    break_editor_viewport3d_destroy(vp);
    editor_rhi_fake_stats(&after_stats);
    ASSERT_EQ(after_stats.live_shaders, 0u);
    ASSERT_EQ(after_stats.live_pipelines, 0u);
    ASSERT_EQ(after_stats.live_bindings, 0u);
    ASSERT_EQ(after_stats.live_buffers, 0u);
    remove(vert_path);
    remove(frag_path);
    TEST_RMDIR(shaders);
    TEST_RMDIR(root);
}

TEST(viewport_shader_candidate_failures_preserve_live_state)
{
    EditorShaderEnv env;
    ASSERT_TRUE(shader_env_save(&env));
    editor_rhi_fake_reset();
    editor_rhi_fake_set_enabled(true);
    viewport_shader_candidate_body();
    editor_rhi_fake_set_enabled(false);
    editor_rhi_fake_reset();
    shader_env_restore(&env);
}

static void viewport_shader_initial_recovery_body(void) {
    static const char good_frag[] = "fragment";
    BreakEditorViewport3D *vp;
    BreakEditorViewport3DGpuState state;
    BreakEditorViewport3DStats viewport_stats;
    EditorRhiFakeStats before_stats, after_stats;
    char root[512], shaders[600], vert_path[700], frag_path[700];
    int device = 0;
    test_tmp(root, sizeof(root), "editor_shader_initial_recovery");
    snprintf(shaders, sizeof(shaders), "%s/shaders", root);
    snprintf(vert_path, sizeof(vert_path), "%s/editor_color.vert", shaders);
    snprintf(frag_path, sizeof(frag_path), "%s/editor_color.frag", shaders);
    ASSERT_EQ(TEST_MKDIR(root), 0);
    ASSERT_EQ(TEST_MKDIR(shaders), 0);
    ASSERT_TRUE(write_text_file(vert_path, "COMPILE_FAIL"));
    ASSERT_TRUE(write_text_file(frag_path, "fragment\n"));
    ASSERT_TRUE(shader_env_set(root));
    vp = break_editor_viewport3d_create();
    ASSERT_NOT_NULL(vp);
    ASSERT_FALSE(break_editor_viewport3d_prepare(NULL, &device));
    ASSERT_FALSE(break_editor_viewport3d_prepare(vp, NULL));
    ASSERT_FALSE(break_editor_viewport3d_prepare(vp, &device));
    ASSERT_TRUE(break_editor_viewport3d_last_stats(vp, &viewport_stats));
    ASSERT_EQ(viewport_stats.init_state, BREAK_EDITOR_VIEWPORT3D_INIT_FAILED);
    break_editor_viewport3d_gpu_state_for_test(vp, &state);
    ASSERT_FALSE(rhi_handle_valid(state.pipeline));
    ASSERT_TRUE(state.bindings == NULL);
    ASSERT_FALSE(rhi_handle_valid(state.vbo));
    editor_rhi_fake_stats(&before_stats);
    ASSERT_EQ(before_stats.live_shaders, 0u);
    ASSERT_EQ(before_stats.live_pipelines, 0u);
    ASSERT_EQ(before_stats.live_bindings, 0u);
    ASSERT_EQ(before_stats.live_buffers, 0u);

    ASSERT_FALSE(break_editor_viewport3d_prepare(vp, &device));
    editor_rhi_fake_stats(&after_stats);
    ASSERT_TRUE(editor_fake_stats_equal(&before_stats, &after_stats));
    ASSERT_TRUE(break_editor_viewport3d_reload_shader_source(
        vp, "REV=3 vertex", strlen("REV=3 vertex"),
        good_frag, sizeof(good_frag) - 1u));
    break_editor_viewport3d_gpu_state_for_test(vp, &state);
    ASSERT_EQ(editor_rhi_fake_pipeline_revision(state.pipeline), 3u);
    ASSERT_TRUE(rhi_handle_valid(state.vbo));
    ASSERT_NOT_NULL(state.bindings);
    ASSERT_TRUE(state.loc_mvp >= 0 && state.loc_color >= 0);
    ASSERT_TRUE(break_editor_viewport3d_last_stats(vp, &viewport_stats));
    ASSERT_EQ(viewport_stats.init_state, BREAK_EDITOR_VIEWPORT3D_INIT_READY);
    editor_rhi_fake_stats(&before_stats);
    ASSERT_EQ(before_stats.pipeline_creates, 1u);
    ASSERT_EQ(before_stats.buffer_creates, 1u);
    ASSERT_EQ(before_stats.live_shaders, 0u);
    ASSERT_EQ(before_stats.live_pipelines, 1u);
    ASSERT_EQ(before_stats.live_bindings, 1u);
    ASSERT_EQ(before_stats.live_buffers, 1u);

    ASSERT_TRUE(break_editor_viewport3d_prepare(vp, &device));
    editor_rhi_fake_stats(&after_stats);
    ASSERT_TRUE(editor_fake_stats_equal(&before_stats, &after_stats));
    break_editor_viewport3d_destroy(vp);
    editor_rhi_fake_stats(&after_stats);
    ASSERT_EQ(after_stats.live_shaders, 0u);
    ASSERT_EQ(after_stats.live_pipelines, 0u);
    ASSERT_EQ(after_stats.live_bindings, 0u);
    ASSERT_EQ(after_stats.live_buffers, 0u);
    remove(vert_path);
    remove(frag_path);
    TEST_RMDIR(shaders);
    TEST_RMDIR(root);
}

TEST(viewport_shader_initial_failure_recovers_through_explicit_reload)
{
    EditorShaderEnv env;
    ASSERT_TRUE(shader_env_save(&env));
    editor_rhi_fake_reset();
    editor_rhi_fake_set_enabled(true);
    viewport_shader_initial_recovery_body();
    editor_rhi_fake_set_enabled(false);
    editor_rhi_fake_reset();
    shader_env_restore(&env);
}

/* ---------------- Phase 3 Task 3: assets / lua / profiler panels -------- */

/* Saves a scratch doc with `n` entities to `path` (BSCN + sidecar) so the
 * assets panel has a loadable .bscn fixture. */
static void save_fixture_scene(const char *path, u32 n) {
    BreakEditorDoc *doc = break_editor_doc_create();
    u32 i;
    ASSERT_NOT_NULL(doc);
    for (i = 0u; i < n; i++) {
        ASSERT_TRUE(break_editor_entity_id_valid(
            break_editor_doc_add_entity(doc, NULL)));
    }
    ASSERT_TRUE(break_editor_doc_save(doc, path));
    break_editor_doc_destroy(doc);
}

/* Iterates the realized (painted) rows of a list_view and returns the first
 * row whose button text equals `text` (rows are direct children of the
 * list — my_list_view.c my_widget_add_child(self, row)). */
static void img_shell_write(void *context, void *data, int size) {
    if (size > 0) {
        (void)fwrite(data, 1u, (size_t)size, (FILE *)context);
    }
}

static my_widget_t *list_row_by_text(my_widget_t *list, const char *text) {
    usize i, n;
    if (list == NULL || text == NULL) {
        return NULL;
    }
    n = my_widget_child_count(list);
    for (i = 0u; i < n; i++) {
        my_widget_t *row = my_widget_get_child(list, i);
        const char *t;
        if (row == NULL) {
            continue;
        }
        t = ((const my_button_t *)row)->text;
        if (t != NULL && strcmp(t, text) == 0) {
            return row;
        }
    }
    return NULL;
}

/* Emits a raw key_down on a widget's emitter (the path the myui dispatcher
 * takes for keys the widget itself did not consume — my_edit returns
 * MY_RET_FAIL for Up/Down, so they reach the panel's "key_down" handler). */
static void emit_key_down(my_widget_t *w, u32 key) {
    my_event_t ev = my_event_init(MY_EVENT_KEY_DOWN);
    ASSERT_NOT_NULL(w);
    ev.u.key.key = key;
    ev.u.key.modifiers = 0u;
    ASSERT_EQ(my_emitter_emit(w->emitter, "key_down", &ev), MY_RET_OK);
}

TEST(assets_panel_lists_fixture_root)
{
    BreakEditorShell *shell = break_editor_shell_create_for_test();
    char dir[512];
    char sub[600];
    char f1[700];
    char f2[700];
    my_widget_t *list;
    ASSERT_NOT_NULL(shell);
    test_tmp(dir, sizeof(dir), "editor_shell_assets_list");
    TEST_MKDIR(dir);
    snprintf(sub, sizeof(sub), "%s/sub", dir);
    TEST_MKDIR(sub);
    snprintf(f1, sizeof(f1), "%s/a.txt", dir);
    snprintf(f2, sizeof(f2), "%s/b.txt", dir);
    ASSERT_TRUE(write_text_file(f1, "a"));
    ASSERT_TRUE(write_text_file(f2, "b"));
    ASSERT_TRUE(break_editor_shell_set_assets_root(shell, dir));
    /* rows: the always-present ".." + sub/ + a.txt + b.txt (the model sorts
     * directories first, then byte-wise) */
    ASSERT_EQ(break_editor_shell_assets_row_count(shell), 4u);
    ASSERT_TRUE(strstr(break_editor_shell_assets_path_text(shell), "assets:") !=
                NULL);
    shell_paint(shell);
    list = find(shell, "editor-assets-list");
    ASSERT_NOT_NULL(list);
    ASSERT_NOT_NULL(list_row_by_text(list, ".."));
    ASSERT_NOT_NULL(list_row_by_text(list, "sub/"));
    ASSERT_NOT_NULL(list_row_by_text(list, "a.txt"));
    ASSERT_NOT_NULL(list_row_by_text(list, "b.txt"));
    break_editor_shell_destroy(shell);
    remove(f1);
    remove(f2);
    TEST_RMDIR(sub);
    TEST_RMDIR(dir);
}

/* Image rows open the preview (texture hot reload, 2026-10-28); .bscn rows
 * still load scenes and other files still log "not loadable". */
TEST(assets_panel_image_row_opens_the_preview)
{
    BreakEditorShell *shell = break_editor_shell_create_for_test();
    char dir[512];
    char png[700];
    char txt[700];
    my_widget_t *list;
    my_widget_t *row;
    BreakEditorImagePreviewStats st;
    int i;
    ASSERT_NOT_NULL(shell);
    test_tmp(dir, sizeof(dir), "editor_shell_assets_image");
    TEST_MKDIR(dir);
    snprintf(png, sizeof(png), "%s/pic.png", dir);
    snprintf(txt, sizeof(txt), "%s/note.txt", dir);
    {
        static u8 px[6 * 4 * 4];
        FILE *f;
        memset(px, 0x7f, sizeof(px));
        f = fopen(png, "wb");
        ASSERT_NOT_NULL(f);
        ASSERT_TRUE(stbi_write_png_to_func(img_shell_write, f, 6, 4, 4, px, 24) != 0);
        fclose(f);
    }
    ASSERT_TRUE(write_text_file(txt, "n"));
    ASSERT_TRUE(break_editor_shell_set_assets_root(shell, dir));
    shell_paint(shell);
    ASSERT_NOT_NULL(find(shell, "editor-assets-preview"));
    ASSERT_TRUE(break_editor_shell_image_preview_stats(shell, &st));
    ASSERT_FALSE(st.has_image);
    list = find(shell, "editor-assets-list");
    ASSERT_NOT_NULL(list);
    row = list_row_by_text(list, "pic.png");
    ASSERT_NOT_NULL(row);
    emit_click(row);
    for (i = 0; i < 3000; i++) {
        ASSERT_TRUE(break_editor_shell_image_preview_stats(shell, &st));
        if (st.reloads == 1u) break;
        break_editor_shell_tick(shell);
        time_sleep_us(2000u);
    }
    ASSERT_EQ(st.reloads, 1u);
    ASSERT_EQ(st.width, 6u);
    ASSERT_EQ(st.height, 4u);
    /* a non-image, non-scene file leaves the preview alone */
    row = list_row_by_text(list, "note.txt");
    ASSERT_NOT_NULL(row);
    emit_click(row);
    break_editor_shell_tick(shell);
    ASSERT_TRUE(break_editor_shell_image_preview_stats(shell, &st));
    ASSERT_TRUE(st.has_image);
    ASSERT_EQ(st.width, 6u);
    break_editor_shell_destroy(shell);
    remove(png);
    remove(txt);
    TEST_RMDIR(dir);
}

/* The editor applies its JetBrains New UI dark sheet at shell create
 * (editor_theme.c): widgets resolve the palette through the real cascade. */
TEST(shell_applies_the_new_ui_dark_theme)
{
    BreakEditorShell *shell = break_editor_shell_create_for_test();
    my_widget_t *w;
    ASSERT_NOT_NULL(shell);
    w = find(shell, "editor-toolbar");
    ASSERT_NOT_NULL(w);
    ASSERT_EQ(my_widget_style_get_color(w, MY_STATE_NORMAL, "bg_color", 0u),
              BREAK_EDITOR_THEME_BG_WINDOW);
    w = find(shell, "editor-remove-button");
    ASSERT_NOT_NULL(w);
    ASSERT_EQ(my_widget_style_get_color(w, MY_STATE_NORMAL, "bg_color", 0u),
              BREAK_EDITOR_THEME_BG_WINDOW);
    ASSERT_EQ(my_widget_style_get_color(w, MY_STATE_HOVER, "bg_color", 0u),
              BREAK_EDITOR_THEME_HOVER);
    ASSERT_EQ(my_widget_style_get_color(w, MY_STATE_NORMAL, "fg_color", 0u),
              BREAK_EDITOR_THEME_TEXT);
    ASSERT_EQ(my_widget_style_get_int(w, MY_STATE_NORMAL, "round_radius", -1), 4);
    w = find(shell, "editor-add-button");
    ASSERT_NOT_NULL(w);
    ASSERT_EQ(my_widget_style_get_color(w, MY_STATE_NORMAL, "bg_color", 0u),
              BREAK_EDITOR_THEME_ACCENT);
    w = find(shell, "editor-outliner");
    ASSERT_NOT_NULL(w);
    ASSERT_EQ(my_widget_style_get_color(w, MY_STATE_NORMAL, "bg_color", 0u),
              BREAK_EDITOR_THEME_BG_CONTENT);
    w = find(shell, "editor-console");
    ASSERT_NOT_NULL(w);
    ASSERT_EQ(my_widget_style_get_color(w, MY_STATE_NORMAL, "bg_color", 0u),
              BREAK_EDITOR_THEME_BG_CONTENT);
    w = find(shell, "editor-status");
    ASSERT_NOT_NULL(w);
    ASSERT_EQ(my_widget_style_get_color(w, MY_STATE_NORMAL, "fg_color", 0u),
              BREAK_EDITOR_THEME_TEXT_SECONDARY);
    /* labels sit on their panel: no light base-theme bg */
    w = find(shell, "editor-outliner-label");
    ASSERT_NOT_NULL(w);
    ASSERT_EQ(my_widget_style_get_color(w, MY_STATE_NORMAL, "bg_color", 1u) &
                  0xFFu,
              0u);
    /* the sheet survives a language switch (panels are retranslated, not
     * rebuilt) */
    ASSERT_TRUE(break_editor_shell_set_language(shell, BREAK_EDITOR_LANG_ZH_CN));
    w = find(shell, "editor-add-button");
    ASSERT_EQ(my_widget_style_get_color(w, MY_STATE_NORMAL, "bg_color", 0u),
              BREAK_EDITOR_THEME_ACCENT);
    ASSERT_TRUE(break_editor_shell_set_language(shell, BREAK_EDITOR_LANG_EN_US));
    break_editor_shell_destroy(shell);
}

/* The outliner row of the selected entity carries the "selected" class and
 * resolves the selection tint; other rows keep the content background.
 * Covers both selection paths: a row click (select_index, no list refresh)
 * and add/remove (refresh_all rebinds rows). */
static usize outliner_selected_rows(my_widget_t *list, my_widget_t **out) {
    usize i, n = my_widget_child_count(list), hits = 0u;
    for (i = 0u; i < n; i++) {
        my_widget_t *row = my_widget_get_child(list, i);
        const char *cls = my_widget_get_style_class(row);
        if (cls != NULL && strcmp(cls, "selected") == 0) {
            if (out != NULL) *out = row;
            hits++;
        }
    }
    return hits;
}

TEST(outliner_highlights_the_selected_row)
{
    BreakEditorShell *shell = break_editor_shell_create_for_test();
    my_widget_t *list;
    my_widget_t *row = NULL;
    my_widget_t *other;
    BreakEditorEntityId id;
    const char *name = NULL;
    char first[BREAK_EDITOR_NAME_CAPACITY];
    ASSERT_NOT_NULL(shell);
    emit_click(find(shell, "editor-add-button"));
    emit_click(find(shell, "editor-add-button"));
    shell_paint(shell);
    list = find(shell, "editor-outliner");
    ASSERT_NOT_NULL(list);
    ASSERT_TRUE(break_editor_doc_entity_at(break_editor_shell_doc(shell), 0u,
                                           &id, &name));
    snprintf(first, sizeof(first), "%s", name);
    /* add selects the new entity (index 1): exactly one highlighted row */
    ASSERT_EQ(outliner_selected_rows(list, &row), 1u);
    ASSERT_EQ(my_widget_style_get_color(row, MY_STATE_NORMAL, "bg_color", 0u),
              BREAK_EDITOR_THEME_SELECTION);
    other = list_row_by_text(list, first);
    ASSERT_NOT_NULL(other);
    ASSERT_TRUE(other != row);
    ASSERT_EQ(my_widget_style_get_color(other, MY_STATE_NORMAL, "bg_color", 0u),
              BREAK_EDITOR_THEME_BG_CONTENT);
    /* clicking the first row moves the highlight */
    emit_click(other);
    ASSERT_EQ(outliner_selected_rows(list, &row), 1u);
    ASSERT_TRUE(row == other);
    /* removing the selection clears every highlight */
    emit_click(find(shell, "editor-remove-button"));
    shell_paint(shell);
    ASSERT_EQ(outliner_selected_rows(list, NULL), 0u);
    break_editor_shell_destroy(shell);
}

TEST(assets_panel_navigation_updates_rows)
{
    BreakEditorShell *shell = break_editor_shell_create_for_test();
    char dir[512];
    char sub[600];
    char f1[700];
    char f2[700];
    my_widget_t *list;
    my_widget_t *row;
    ASSERT_NOT_NULL(shell);
    test_tmp(dir, sizeof(dir), "editor_shell_assets_nav");
    TEST_MKDIR(dir);
    snprintf(sub, sizeof(sub), "%s/sub", dir);
    TEST_MKDIR(sub);
    snprintf(f1, sizeof(f1), "%s/a.txt", dir);
    snprintf(f2, sizeof(f2), "%s/inner.txt", sub);
    ASSERT_TRUE(write_text_file(f1, "a"));
    ASSERT_TRUE(write_text_file(f2, "i"));
    ASSERT_TRUE(break_editor_shell_set_assets_root(shell, dir));
    shell_paint(shell);
    list = find(shell, "editor-assets-list");
    ASSERT_NOT_NULL(list);
    ASSERT_EQ(break_editor_shell_assets_row_count(shell), 3u);
    /* enter the subdirectory: rows rebind from the model's new snapshot */
    row = list_row_by_text(list, "sub/");
    ASSERT_NOT_NULL(row);
    emit_click(row);
    ASSERT_EQ(break_editor_shell_assets_row_count(shell), 2u);
    ASSERT_TRUE(strstr(break_editor_shell_assets_path_text(shell), "sub") !=
                NULL);
    shell_paint(shell);
    ASSERT_NOT_NULL(list_row_by_text(list, "inner.txt"));
    /* ".." row on top navigates back, clamped at the root */
    row = list_row_by_text(list, "..");
    ASSERT_NOT_NULL(row);
    emit_click(row);
    ASSERT_EQ(break_editor_shell_assets_row_count(shell), 3u);
    shell_paint(shell);
    ASSERT_NOT_NULL(list_row_by_text(list, "sub/"));
    /* at the root, ".." is a clamped no-op */
    row = list_row_by_text(list, "..");
    ASSERT_NOT_NULL(row);
    emit_click(row);
    ASSERT_EQ(break_editor_shell_assets_row_count(shell), 3u);
    break_editor_shell_destroy(shell);
    remove(f1);
    remove(f2);
    TEST_RMDIR(sub);
    TEST_RMDIR(dir);
}

TEST(assets_panel_bscn_activation_loads_doc_and_clears_undo)
{
    BreakEditorShell *shell = break_editor_shell_create_for_test();
    BreakEditorDoc *doc;
    char dir[512];
    char scene[600];
    char sidecar[700];
    my_widget_t *list;
    my_widget_t *row;
    ASSERT_NOT_NULL(shell);
    test_tmp(dir, sizeof(dir), "editor_shell_assets_load");
    TEST_MKDIR(dir);
    snprintf(scene, sizeof(scene), "%s/scene.bscn", dir);
    snprintf(sidecar, sizeof(sidecar), "%s" BREAK_EDITOR_SIDECAR_SUFFIX,
             scene);
    save_fixture_scene(scene, 2u);
    doc = break_editor_shell_doc(shell);
    ASSERT_EQ(break_editor_doc_entity_count(doc), 0u);
    ASSERT_TRUE(break_editor_shell_set_assets_root(shell, dir));
    shell_paint(shell);
    list = find(shell, "editor-assets-list");
    ASSERT_NOT_NULL(list);
    row = list_row_by_text(list, "scene.bscn");
    ASSERT_NOT_NULL(row);
    emit_click(row);
    /* confirm-free load (Phase 2 documents the world swap + undo clear) */
    ASSERT_EQ(break_editor_doc_entity_count(doc), 2u);
    ASSERT_EQ(break_editor_shell_outliner_count(shell), 2u);
    ASSERT_TRUE(strstr(break_editor_shell_console_text(shell), "load") != NULL);
    /* the load cleared the command stack: Ctrl+Z cannot resurrect the
     * pre-load (empty) document */
    ASSERT_TRUE(break_editor_shell_dispatch_key(shell, 'z', MY_KEYMOD_CTRL));
    ASSERT_EQ(break_editor_doc_entity_count(doc), 2u);
    break_editor_shell_destroy(shell);
    remove(scene);
    remove(sidecar);
    TEST_RMDIR(dir);
}

TEST(lua_panel_eval_routes_result_to_console_ring)
{
    BreakEditorShell *shell = break_editor_shell_create_for_test();
    my_widget_t *edit;
    ASSERT_NOT_NULL(shell);
    edit = find(shell, "editor-lua-edit");
    ASSERT_NOT_NULL(edit);
    ASSERT_EQ(my_edit_set_text(edit, "return 1+2"), MY_RET_OK);
    emit_activate(edit);
    /* Task 2 core output lands in the SHARED console ring with the lua|
     * prefix */
    ASSERT_TRUE(strstr(break_editor_shell_console_text(shell), "lua| 3") !=
                NULL);
    ASSERT_EQ(break_editor_shell_lua_history_count(shell), 1u);
    /* the input field is cleared for the next line */
    ASSERT_STR_EQ(my_edit_get_text(edit), "");
    break_editor_shell_destroy(shell);
}

TEST(lua_panel_spawn_updates_outliner_and_ctrl_z_reverts)
{
    BreakEditorShell *shell = break_editor_shell_create_for_test();
    my_widget_t *edit;
    ASSERT_NOT_NULL(shell);
    edit = find(shell, "editor-lua-edit");
    ASSERT_NOT_NULL(edit);
    ASSERT_EQ(my_edit_set_text(edit, "brk.ecs.spawn()"), MY_RET_OK);
    emit_activate(edit);
    /* the console core drains its ECS batch into undoable doc commands; the
     * outliner refresh after eval picks the new entity up */
    ASSERT_EQ(break_editor_shell_outliner_count(shell), 1u);
    ASSERT_TRUE(break_editor_shell_dispatch_key(shell, 'z', MY_KEYMOD_CTRL));
    ASSERT_EQ(break_editor_shell_outliner_count(shell), 0u);
    break_editor_shell_destroy(shell);
}

TEST(lua_panel_history_up_down_recall)
{
    BreakEditorShell *shell = break_editor_shell_create_for_test();
    my_widget_t *edit;
    ASSERT_NOT_NULL(shell);
    edit = find(shell, "editor-lua-edit");
    ASSERT_NOT_NULL(edit);
    ASSERT_EQ(my_edit_set_text(edit, "return 1"), MY_RET_OK);
    emit_activate(edit);
    ASSERT_EQ(my_edit_set_text(edit, "return 2"), MY_RET_OK);
    emit_activate(edit);
    ASSERT_EQ(break_editor_shell_lua_history_count(shell), 2u);
    /* Up walks newest->oldest; Down walks back; past the newest the
     * in-progress (stashed) line is restored */
    emit_key_down(edit, MY_KEY_UP);
    ASSERT_STR_EQ(my_edit_get_text(edit), "return 2");
    emit_key_down(edit, MY_KEY_UP);
    ASSERT_STR_EQ(my_edit_get_text(edit), "return 1");
    emit_key_down(edit, MY_KEY_DOWN);
    ASSERT_STR_EQ(my_edit_get_text(edit), "return 2");
    emit_key_down(edit, MY_KEY_DOWN);
    ASSERT_STR_EQ(my_edit_get_text(edit), "");
    /* Up past the oldest is a clamped no-op */
    emit_key_down(edit, MY_KEY_UP);
    emit_key_down(edit, MY_KEY_UP);
    emit_key_down(edit, MY_KEY_UP);
    ASSERT_STR_EQ(my_edit_get_text(edit), "return 1");
    break_editor_shell_destroy(shell);
}

TEST(profiler_panel_populates_rows_after_pumped_frame)
{
    BreakEditorShell *shell = break_editor_shell_create_for_test();
    u32 frames_before;
    ASSERT_NOT_NULL(shell);
    /* pump one frame with a marker region in THIS process */
    profiler_set_enabled(true);
    profiler_begin_frame();
    profiler_push("p33_marker_region");
    profiler_pop();
    profiler_end_frame();
    frames_before = g_profiler.frame_count;
    ASSERT_TRUE(frames_before >= 1u);
    /* the first tick after create always refreshes (4 Hz throttle onwards);
     * the panel is a pure view: profiler state is byte-identical across the
     * refresh */
    break_editor_shell_tick(shell);
    ASSERT_EQ(g_profiler.frame_count, frames_before);
    ASSERT_TRUE(break_editor_shell_profiler_row_count(shell) >= 1u);
    ASSERT_NOT_NULL(break_editor_shell_profiler_row_text(shell, 0u));
    ASSERT_TRUE(strstr(break_editor_shell_profiler_row_text(shell, 0u),
                       "p33_marker_region") != NULL);
    ASSERT_TRUE(strstr(break_editor_shell_profiler_row_text(shell, 0u), "ms") !=
                NULL);
    profiler_set_enabled(false);
    break_editor_shell_destroy(shell);
}

TEST(phase3_layout_assets_lua_profiler_panels_present)
{
    BreakEditorShell *shell = break_editor_shell_create_for_test();
    my_widget_t *bottom;
    my_widget_t *console;
    my_widget_t *lua_panel;
    my_widget_t *outliner_panel;
    my_widget_t *assets_panel;
    my_widget_t *inspector;
    my_widget_t *profiler_panel;
    ASSERT_NOT_NULL(shell);
    shell_paint(shell);
    /* widget presence */
    ASSERT_NOT_NULL(find(shell, "editor-assets-list"));
    ASSERT_NOT_NULL(find(shell, "editor-assets-path"));
    ASSERT_NOT_NULL(find(shell, "editor-lua-edit"));
    ASSERT_NOT_NULL(find(shell, "editor-profiler-list"));
    /* bottom row = two columns: console ring left, lua panel right (~40%) */
    bottom = find(shell, "editor-bottom");
    console = find(shell, "editor-console");
    lua_panel = find(shell, "editor-lua-panel");
    ASSERT_NOT_NULL(bottom);
    ASSERT_NOT_NULL(console);
    ASSERT_NOT_NULL(lua_panel);
    ASSERT_TRUE(console->rect.x < lua_panel->rect.x);
    ASSERT_TRUE(lua_panel->rect.x >= console->rect.x + console->rect.w - 1);
    ASSERT_TRUE(lua_panel->rect.w * 10 >= bottom->rect.w * 3);  /* >= 30% */
    ASSERT_TRUE(lua_panel->rect.w * 10 <= bottom->rect.w * 5);  /* <= 50% */
    /* assets panel under the outliner; profiler panel under the inspector */
    outliner_panel = find(shell, "editor-outliner-panel");
    assets_panel = find(shell, "editor-assets-panel");
    inspector = find(shell, "editor-inspector");
    profiler_panel = find(shell, "editor-profiler-panel");
    ASSERT_NOT_NULL(outliner_panel);
    ASSERT_NOT_NULL(assets_panel);
    ASSERT_NOT_NULL(inspector);
    ASSERT_NOT_NULL(profiler_panel);
    ASSERT_TRUE(assets_panel->rect.y > outliner_panel->rect.y);
    ASSERT_TRUE(assets_panel->rect.h * 10 >= outliner_panel->rect.h * 3);
    ASSERT_TRUE(assets_panel->rect.h * 10 <= outliner_panel->rect.h * 5);
    ASSERT_TRUE(profiler_panel->rect.y > inspector->rect.y);
    ASSERT_TRUE(profiler_panel->rect.h * 10 >= inspector->rect.h * 3);
    ASSERT_TRUE(profiler_panel->rect.h * 10 <= inspector->rect.h * 7);
    break_editor_shell_destroy(shell);
}

/* ---------------- Phase 4 Task 3: network diagnostics panel -------------
 * Pure view over the borrowed remote (editor_panel_network.c). The panel
 * clock is injectable (break_editor_shell_set_network_clock_for_test) so
 * the <= 4 Hz throttle is pinned deterministically, without sleeps. */

static u64 g_net_clock_us = 0u;

static u64 net_test_clock(void *user) {
    (void)user;
    return g_net_clock_us;
}

#ifdef BREAK_EDITOR_REMOTE_TESTS
typedef struct {
    u32 count;
    char rows[16][96];
} NetRowsSnapshot;

static void net_rows_capture(BreakEditorShell *shell, NetRowsSnapshot *out) {
    u32 i;
    memset(out, 0, sizeof(*out));
    out->count = break_editor_shell_network_row_count(shell);
    for (i = 0u; i < out->count && i < 16u; i++) {
        const char *t = break_editor_shell_network_row_text(shell, i);
        (void)snprintf(out->rows[i], sizeof(out->rows[i]), "%s",
                       t != NULL ? t : "<null>");
    }
}

static bool net_rows_equal(const NetRowsSnapshot *a, const NetRowsSnapshot *b) {
    u32 i;
    if (a->count != b->count) {
        return false;
    }
    for (i = 0u; i < a->count && i < 16u; i++) {
        if (strcmp(a->rows[i], b->rows[i]) != 0) {
            return false;
        }
    }
    return true;
}
#endif /* BREAK_EDITOR_REMOTE_TESTS */

TEST(network_panel_remote_off_row)
{
    BreakEditorShell *shell = break_editor_shell_create_for_test();
    ASSERT_NOT_NULL(shell);
    ASSERT_TRUE(break_editor_shell_remote(shell) == NULL);
    break_editor_shell_tick(shell);
    /* remote == NULL: exactly one bounded "remote: off" row */
    ASSERT_EQ(break_editor_shell_network_row_count(shell), 1u);
    ASSERT_STR_EQ(break_editor_shell_network_row_text(shell, 0u), "remote: off");
    ASSERT_TRUE(break_editor_shell_network_row_text(shell, 1u) == NULL);
    ASSERT_TRUE(strlen(break_editor_shell_network_row_text(shell, 0u)) < 96u);
    /* NULL-safe accessors */
    ASSERT_EQ(break_editor_shell_network_row_count(NULL), 0u);
    ASSERT_TRUE(break_editor_shell_network_row_text(NULL, 0u) == NULL);
    break_editor_shell_set_network_clock_for_test(NULL, net_test_clock, NULL);
    break_editor_shell_destroy(shell);
}

TEST(network_panel_layout_in_diagnostics_column_under_profiler)
{
    BreakEditorShell *shell = break_editor_shell_create_for_test();
    my_widget_t *profiler_panel;
    my_widget_t *network_panel;
    my_widget_t *right_panel;
    ASSERT_NOT_NULL(shell);
    break_editor_shell_tick(shell);
    shell_paint(shell);
    ASSERT_NOT_NULL(find(shell, "editor-network-list"));
    ASSERT_NOT_NULL(find(shell, "editor-network-label"));
    profiler_panel = find(shell, "editor-profiler-panel");
    network_panel = find(shell, "editor-network-panel");
    right_panel = find(shell, "editor-right-panel");
    ASSERT_NOT_NULL(profiler_panel);
    ASSERT_NOT_NULL(network_panel);
    ASSERT_NOT_NULL(right_panel);
    /* diagnostics area: same right column as the profiler, directly below
     * it (documented placement: inspector h:1f / profiler h:30% / network
     * h:20%) */
    /* network sits in the shared diagnostics row (with the render debugger)
     * directly under the profiler; the row keeps the documented h:20% */
    {
        my_widget_t *diag = find(shell, "editor-diag-row");
        ASSERT_NOT_NULL(diag);
        ASSERT_TRUE(diag->parent == right_panel);
        ASSERT_TRUE(network_panel->parent == diag);
        ASSERT_TRUE(profiler_panel->parent == right_panel);
        ASSERT_TRUE(diag->rect.y >= profiler_panel->rect.y + profiler_panel->rect.h);
        ASSERT_TRUE(diag->rect.h * 10 >= right_panel->rect.h * 1);
        ASSERT_TRUE(diag->rect.h * 10 <= right_panel->rect.h * 3);
        ASSERT_EQ(network_panel->rect.h, diag->rect.h);
        ASSERT_TRUE(network_panel->rect.w > 0);
    }
    break_editor_shell_destroy(shell);
}

/* Strips C comments so prose that names a forbidden call does not trip the
 * scan (code tokens only). */
static void net_strip_comments(char *s) {
    char *r = s, *w = s;
    while (*r != '\0') {
        if (r[0] == '/' && r[1] == '*') {
            r += 2;
            while (*r != '\0' && !(r[0] == '*' && r[1] == '/')) {
                r++;
            }
            if (*r != '\0') {
                r += 2;
            }
            *w++ = ' ';
        } else if (r[0] == '/' && r[1] == '/') {
            while (*r != '\0' && *r != '\n') {
                r++;
            }
        } else {
            *w++ = *r++;
        }
    }
    *w = '\0';
}

#define NET_PANEL_STR2(x) #x
#define NET_PANEL_STR(x) NET_PANEL_STR2(x)

TEST(network_panel_source_never_calls_send_close_transition)
{
    /* source-scan pin (the house test_rhi_metal_* source-read precedent):
     * the panel TU reaches the network ONLY through the read-only
     * editor_remote.h accessors — no transport/session headers, no send,
     * close, transition, or lifecycle calls. */
    static char src[65536];
    static const char *const k_forbidden[] = {
        "break_net_reactor_send",          "break_net_reactor_stop",
        "break_net_reactor_step",          "break_net_reactor_poll_event",
        "break_session_manager_close",     "break_session_manager_transition",
        "break_session_manager_bind",      "break_session_manager_begin_auth",
        "break_session_manager_auth_succeeded",
        "break_session_manager_apply_event",
        "break_session_manager_apply_adapter_event",
        "break_session_manager_poll",      "break_session_manager_destroy",
        "break_editor_remote_tick",        "break_editor_remote_start",
        "break_editor_remote_destroy",     "break_editor_remote_set_psk",
        "break_editor_remote_manager_for_test",
        "break_editor_shell_set_remote",   "network/break_net",
        "network/break_session",           "snow/",
        "close(",                          "send(",
        "break_editor_doc_",               "break_editor_undo",
        "break_editor_redo"};
    FILE *f = fopen(NET_PANEL_STR(BREAK_EDITOR_NETWORK_PANEL_SOURCE), "rb");
    size_t n, i;
    ASSERT_NOT_NULL(f);
    n = fread(src, 1u, sizeof(src) - 1u, f);
    fclose(f);
    ASSERT_TRUE(n > 0u && n < sizeof(src) - 1u);
    src[n] = '\0';
    net_strip_comments(src);
    /* positive control: the scan sees real code */
    ASSERT_TRUE(strstr(src, "editor_panel_network_tick") != NULL);
    ASSERT_TRUE(strstr(src, "break_editor_remote_session_stats") != NULL);
    for (i = 0u; i < sizeof(k_forbidden) / sizeof(k_forbidden[0]); i++) {
        if (strstr(src, k_forbidden[i]) != NULL) {
            printf("  FAIL: %s:%d: panel source contains forbidden token "
                   "\"%s\"\n",
                   __FILE__, __LINE__, k_forbidden[i]);
            g_test_fail++;
            return;
        }
    }
}

/* ---------------- render debugger panel (docs/design/editor_render_debugger.md) ---------------- */

static u64 g_render_clock_us = 0u;
static u64 render_test_clock(void *user) {
    (void)user;
    return g_render_clock_us;
}

/* Fake read-only source: what the panel would get from the RHI. */
static int g_render_fake_lost;
static u32 g_render_fake_used = 17u;
static bool render_fake_info(const void *dev, RHIDeviceInfo *out) {
    (void)dev;
    memset(out, 0, sizeof(*out));
    out->backend = RHI_BACKEND_VULKAN;
    snprintf(out->device_name, sizeof(out->device_name), "%s",
             "Fake GPU 9000 with a deliberately very long marketing name that must be truncated safely");
    out->vendor_id = 0x10deu;
    out->device_id = 0x2489u;
    out->api_version = 4206592u; /* 1.3.0 */
    out->driver_version = 12345u;
    return true;
}
static bool render_fake_caps(const void *dev, RHICapabilities *out) {
    (void)dev;
    memset(out, 0, sizeof(*out));
    out->backend = RHI_BACKEND_VULKAN;
    out->shader_variant = (u32)RHI_SHADER_VARIANT_GLSL_VK;
    out->compute_supported = true;
    out->indirect_draw_supported = true;
    out->push_constants_supported = true;
    out->max_push_constant_size = 256u;
    out->color_sample_counts = 0x5u;
    return true;
}
static RHIDeviceStatus render_fake_status(const void *dev) {
    (void)dev;
    return g_render_fake_lost ? RHI_DEVICE_STATUS_LOST : RHI_DEVICE_STATUS_READY;
}
static u32 render_fake_frame(const void *dev) { (void)dev; return 42u; }
static bool render_fake_usage(const void *dev, u32 *used, u32 *cap) {
    (void)dev;
    *used = g_render_fake_used;
    *cap = 4096u;
    return true;
}
static const char *render_fake_backend(void) { return "vulkan"; }
static const char *render_fake_reason(void) { return "platform-default"; }

static const BreakEditorRenderSource k_render_fake_source = {
    render_fake_info, render_fake_caps, render_fake_status, render_fake_frame,
    render_fake_usage, render_fake_backend, render_fake_reason};

static int g_render_fake_device;

static bool render_row_has(BreakEditorShell *shell, const char *needle) {
    u32 i, n = break_editor_shell_render_row_count(shell);
    for (i = 0u; i < n; i++) {
        const char *t = break_editor_shell_render_row_text(shell, i);
        if (t != NULL && strstr(t, needle) != NULL) return true;
    }
    return false;
}

TEST(render_panel_no_device_row)
{
    BreakEditorShell *shell = break_editor_shell_create_for_test();
    ASSERT_NOT_NULL(shell);
    break_editor_shell_tick(shell);
    ASSERT_EQ(break_editor_shell_render_row_count(shell), 1u);
    ASSERT_STR_EQ(break_editor_shell_render_row_text(shell, 0u), "render: no device");
    ASSERT_TRUE(break_editor_shell_render_row_text(shell, 1u) == NULL);
    ASSERT_EQ(break_editor_shell_render_row_count(NULL), 0u);
    ASSERT_TRUE(break_editor_shell_render_row_text(NULL, 0u) == NULL);
    break_editor_shell_set_render_device(NULL, NULL); /* NULL shell: no-op */
    break_editor_shell_destroy(shell);
}

TEST(render_panel_diag_attach_failure_does_not_leave_dangling_lists)
{
    BreakEditorShell *shell;
    break_editor_shell_fail_diag_attach_for_test();
    shell = break_editor_shell_create_for_test();
    ASSERT_NOT_NULL(shell);
    /* Both panels are forced to refresh on their first tick. The failed row
     * attach must leave their weak list pointers NULL, never dangling. */
    break_editor_shell_tick(shell);
    ASSERT_TRUE(find(shell, "editor-diag-row") == NULL);
    ASSERT_EQ(break_editor_shell_network_row_count(shell), 1u);
    ASSERT_STR_EQ(break_editor_shell_network_row_text(shell, 0u), "remote: off");
    ASSERT_EQ(break_editor_shell_render_row_count(shell), 1u);
    ASSERT_STR_EQ(break_editor_shell_render_row_text(shell, 0u), "render: no device");
    break_editor_shell_destroy(shell);
}

TEST(render_panel_layout_beside_network_in_diagnostics_row)
{
    BreakEditorShell *shell = break_editor_shell_create_for_test();
    my_widget_t *network_panel, *render_panel, *right_panel;
    ASSERT_NOT_NULL(shell);
    break_editor_shell_tick(shell);
    shell_paint(shell);
    ASSERT_NOT_NULL(find(shell, "editor-render-list"));
    ASSERT_NOT_NULL(find(shell, "editor-render-label"));
    network_panel = find(shell, "editor-network-panel");
    render_panel = find(shell, "editor-render-panel");
    right_panel = find(shell, "editor-right-panel");
    ASSERT_NOT_NULL(network_panel);
    ASSERT_NOT_NULL(render_panel);
    /* same diagnostics row as the network panel, to its right */
    ASSERT_NOT_NULL(right_panel);
    ASSERT_TRUE(render_panel->parent == network_panel->parent);
    ASSERT_EQ(render_panel->rect.y, network_panel->rect.y);
    ASSERT_EQ(render_panel->rect.h, network_panel->rect.h);
    ASSERT_TRUE(render_panel->rect.x >= network_panel->rect.x + network_panel->rect.w);
    ASSERT_TRUE(render_panel->rect.w > 0);
    break_editor_shell_destroy(shell);
}

TEST(render_panel_rows_from_device_source_and_viewport_stats)
{
    BreakEditorShell *shell = break_editor_shell_create_for_test();
    u32 i, n;
    ASSERT_NOT_NULL(shell);
    g_render_clock_us = UINT64_C(1000000);
    g_render_fake_lost = 0;
    g_render_fake_used = 17u;
    break_editor_shell_set_render_clock_for_test(shell, render_test_clock, NULL);
    break_editor_shell_set_render_source_for_test(shell, &k_render_fake_source);
    break_editor_shell_set_render_device(shell, (RHIDevice *)&g_render_fake_device);
    break_editor_shell_tick(shell);
    n = break_editor_shell_render_row_count(shell);
    ASSERT_EQ(n, 9u);
    for (i = 0u; i < n; i++) {
        const char *t = break_editor_shell_render_row_text(shell, i);
        ASSERT_NOT_NULL(t);
        ASSERT_TRUE(strlen(t) < 96u);
    }
    ASSERT_TRUE(render_row_has(shell, "backend: vulkan (platform-default) status=ready frame=42"));
    ASSERT_TRUE(render_row_has(shell, "gpu: Fake GPU 9000"));
    ASSERT_TRUE(render_row_has(shell, "vendor=0x10de device=0x2489 api=1.3.0"));
    ASSERT_TRUE(render_row_has(shell, "caps: shader=glsl_vk compute=1 indirect=1 push=256"));
    ASSERT_TRUE(render_row_has(shell, "msaa=0x5"));
    ASSERT_TRUE(render_row_has(shell, "resources: 17/4096 slots"));
    ASSERT_TRUE(render_row_has(shell, "viewport: failed"));
    ASSERT_TRUE(render_row_has(shell, "skipped=not-rendered"));
    ASSERT_STR_EQ(break_editor_shell_render_row_text(shell, 8u),
                  "shader reload: unavailable");
    /* detach: back to the single no-device row on the next tick */
    break_editor_shell_set_render_device(shell, NULL);
    break_editor_shell_tick(shell);
    ASSERT_EQ(break_editor_shell_render_row_count(shell), 1u);
    break_editor_shell_destroy(shell);
}

TEST(render_panel_throttle_4hz_and_device_lost)
{
    BreakEditorShell *shell = break_editor_shell_create_for_test();
    ASSERT_NOT_NULL(shell);
    g_render_clock_us = UINT64_C(2000000);
    g_render_fake_lost = 0;
    g_render_fake_used = 17u;
    break_editor_shell_set_render_clock_for_test(shell, render_test_clock, NULL);
    break_editor_shell_set_render_source_for_test(shell, &k_render_fake_source);
    break_editor_shell_set_render_device(shell, (RHIDevice *)&g_render_fake_device);
    break_editor_shell_tick(shell); /* attach forces a refresh */
    ASSERT_TRUE(render_row_has(shell, "resources: 17/4096"));
    /* sources change inside the window: rows held */
    g_render_fake_used = 99u;
    g_render_fake_lost = 1;
    g_render_clock_us += UINT64_C(249999);
    break_editor_shell_tick(shell);
    ASSERT_TRUE(render_row_has(shell, "resources: 17/4096"));
    ASSERT_TRUE(render_row_has(shell, "status=ready"));
    /* exactly 250,000 us later: live values, including the lost device */
    g_render_clock_us += UINT64_C(1);
    break_editor_shell_tick(shell);
    ASSERT_TRUE(render_row_has(shell, "resources: 99/4096"));
    ASSERT_TRUE(render_row_has(shell, "status=lost"));
    break_editor_shell_destroy(shell);
}

#define RENDER_PANEL_STR2(x) #x
#define RENDER_PANEL_STR(x) RENDER_PANEL_STR2(x)

TEST(render_panel_source_is_read_only)
{
    /* source-scan pin: the panel reaches the renderer only through the
     * read-only queries; it never creates, destroys, binds, records,
     * submits or presents anything. */
    static char src[65536];
    static const char *const forbidden[] = {
        "_create(", "_destroy(", "rhi_cmd_", "rhi_frame_begin", "rhi_frame_end",
        "rhi_present", "rhi_device_resize", "rhi_set_vsync", "rhi_buffer_",
        "rhi_texture_", "rhi_pipeline_", "rhi_screenshot", "rhi_device_idle",
        "rhi_offscreen_fbo_", "rhi_device_attach_wsi", "rhi_rollout_set_",
        "rhi_device_control_", "rhi_frame_submit", "rhi_frame_acquire",
        "rhi_set_", "rhi_shader_", "rhi_cubemap_", "rhi_framebuffer_",
        "break_editor_viewport3d_request_shader_reload(",
        "break_editor_viewport3d_tick(", "break_editor_shader_reload_"};
    FILE *f = fopen(RENDER_PANEL_STR(BREAK_EDITOR_RENDER_PANEL_SOURCE), "rb");
    size_t n, i;
    char *body;
    ASSERT_NOT_NULL(f);
    n = fread(src, 1u, sizeof(src) - 1u, f);
    fclose(f);
    src[n] = '\0';
    /* scan only the read-only region (between the BEGIN/END markers); the
     * panel's own widget lifecycle below END is allowed to create/destroy */
    body = strstr(src, "RENDER_PANEL_READONLY_BEGIN");
    ASSERT_NOT_NULL(body);
    {
        char *end = strstr(body, "RENDER_PANEL_READONLY_END");
        ASSERT_NOT_NULL(end);
        *end = '\0';
    }
    net_strip_comments(body);
    for (i = 0u; i < sizeof(forbidden) / sizeof(forbidden[0]); i++) {
        if (strstr(body, forbidden[i]) != NULL)
            printf("    forbidden token in render panel: %s\n", forbidden[i]);
        ASSERT_TRUE(strstr(body, forbidden[i]) == NULL);
    }
}


/* ---------------- Phase 4 Task 1: remote session host (plaintext seam) ----
 * Compiled only when the build has BREAK_ENABLE_SNOWFLAKE=ON (CMake gates
 * the break_net link and defines BREAK_EDITOR_REMOTE_TESTS); with snowflake
 * OFF this suite is byte-identical to the Phase 3 one. */

#ifdef BREAK_EDITOR_REMOTE_TESTS

#include "editor_remote.h"

#include <editor/editor_protocol.h>
#include <network/break_net_adapter.h>
#include <network/break_net_envelope.h>
#include <network/break_session.h>

#include <snow/network_buffer.h>
#include <snow/openssl.h>
#ifdef BREAK_ENABLE_CRYPTO
#include <crypto/break_crypto.h>
#endif

#include <arpa/inet.h>
#include <errno.h>
#include <stdlib.h>
#include <fcntl.h>
#include <poll.h>
#include <sys/socket.h>
#include <time.h>
#include <unistd.h>

/* Test isolation: every remote a test creates is tracked, and
 * RUN_REMOTE_TEST destroys any a failed test left behind (an early ASSERT
 * return skips the test's own destroy). A leaked remote keeps its sessions
 * non-NEW, which pins the process-global session auth domain and would
 * cascade into the TLS tests' break_session_set_auth installs. */
#define REMOTE_TRACK_MAX 8u
static BreakEditorRemote *g_remote_live[REMOTE_TRACK_MAX];

static BreakEditorRemote *remote_tracked_create(
    BreakEditorShell *shell, const BreakEditorRemoteConfig *cfg) {
    BreakEditorRemote *r = break_editor_remote_create(shell, cfg);
    u32 i;
    for (i = 0u; r != NULL && i < REMOTE_TRACK_MAX; i++) {
        if (g_remote_live[i] == NULL) {
            g_remote_live[i] = r;
            break;
        }
    }
    return r;
}

static void remote_tracked_destroy(BreakEditorRemote *r) {
    u32 i;
    for (i = 0u; r != NULL && i < REMOTE_TRACK_MAX; i++) {
        if (g_remote_live[i] == r) {
            g_remote_live[i] = NULL;
        }
    }
    break_editor_remote_destroy(r);
}

static void remote_reap_leaked(void) {
    u32 i;
    for (i = 0u; i < REMOTE_TRACK_MAX; i++) {
        if (g_remote_live[i] != NULL) {
            BreakEditorRemote *r = g_remote_live[i];
            g_remote_live[i] = NULL;
            printf("  (reaped a remote leaked by a failed test)\n");
            break_editor_remote_destroy(r);
        }
    }
}

#define break_editor_remote_create(shell, cfg) remote_tracked_create(shell, cfg)
#define break_editor_remote_destroy(r) remote_tracked_destroy(r)
#define RUN_REMOTE_TEST(name) do { \
    RUN_TEST(name); \
    remote_reap_leaked(); \
} while (0)

static u64 remote_monotonic_us(void) {
    struct timespec now;
    clock_gettime(CLOCK_MONOTONIC, &now);
    return (u64)now.tv_sec * UINT64_C(1000000) +
           (u64)now.tv_nsec / UINT64_C(1000);
}

/* get16/put16/put32: canonical little-endian lanes (the wire rule — no
 * structs on the wire). */
static u16 rd16(const void *p) {
    const u8 *b = (const u8 *)p;
    return (u16)((u16)b[0] | ((u16)b[1] << 8u));
}
static void wr16(u8 *p, u16 v) { p[0] = (u8)v; p[1] = (u8)(v >> 8u); }
static void wr32(u8 *p, u32 v) {
    p[0] = (u8)v; p[1] = (u8)(v >> 8u); p[2] = (u8)(v >> 16u);
    p[3] = (u8)(v >> 24u);
}

typedef struct {
    int fd;                  /* -1 = closed */
    BreakEditorRemote *remote;
    BreakEditorShell *shell;
    u32 next_seq;            /* per-connection monotonically increasing */
    bool saw_eof;
} RemoteClient;

/* One pump cycle: tick the shell — its per-frame wiring drives the
 * attached remote's poll_adapter (the per-frame wiring pin) — then poll the
 * client socket with a real kernel deadline so the test sleeps instead of
 * spinning. */
static void remote_client_pump(RemoteClient *c, int poll_ms) {
    struct pollfd pfd;
    break_editor_shell_tick(c->shell);
    if (c->fd >= 0) {
        pfd.fd = c->fd;
        pfd.events = POLLIN;
        pfd.revents = 0;
        (void)poll(&pfd, 1, poll_ms);
    } else if (poll_ms > 0) {
        struct timespec ts = {0, (long)poll_ms * 1000000L};
        nanosleep(&ts, NULL);
    }
}

static void remote_client_close(RemoteClient *c) {
    if (c->fd >= 0) {
        close(c->fd);
        c->fd = -1;
    }
}

static void remote_client_connect(RemoteClient *c, BreakEditorShell *shell,
                                  BreakEditorRemote *remote) {
    struct sockaddr_in address;
    u64 deadline;
    memset(c, 0, sizeof(*c));
    c->fd = -1;
    c->shell = shell;
    c->remote = remote;
    c->next_seq = 1u;
    c->fd = socket(AF_INET, SOCK_STREAM, 0);
    ASSERT_TRUE(c->fd >= 0);
    memset(&address, 0, sizeof(address));
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
    address.sin_port = htons(break_editor_remote_port(remote));
    ASSERT_EQ(connect(c->fd, (const struct sockaddr *)&address,
                      sizeof(address)),
              0);
    /* wait until the host tracks the connection */
    deadline = remote_monotonic_us() + UINT64_C(3000000);
    while (remote_monotonic_us() < deadline) {
        if (break_editor_remote_connection_count(remote) >= 1u) {
            break;
        }
        remote_client_pump(c, 5);
    }
    ASSERT_TRUE(break_editor_remote_connection_count(remote) >= 1u);
    /* let the plaintext-seam auto-auth complete before the first request
     * leaves: remote_table_sync transitions NEW → AUTHENTICATED on the tick
     * after the OPENED event is adopted, and a request arriving while the
     * session is still NEW gets dropped without a response. */
    {
        u64 auth_deadline = remote_monotonic_us() + UINT64_C(3000000);
        uint64_t keys[4];
        uint32_t states[4];
        uint32_t n = 0u;
        while (remote_monotonic_us() < auth_deadline) {
            n = break_editor_remote_connections_snapshot(remote, keys, states, 4u);
            if (n >= 1u && states[0] == 2u /* BREAK_SESSION_AUTHENTICATED */) {
                break;
            }
            remote_client_pump(c, 5);
        }
        ASSERT_TRUE(n >= 1u);
        ASSERT_EQ(states[0], 2u);
    }
}

/* Encodes + sends one request envelope (payload may be NULL with size 0).
 * Well-formed messages only — payloads above the 4096 B protocol bound or
 * unregistered ids are rejected by the client-side codec, so negative
 * tests use remote_client_send_raw below. */
static void remote_client_send(RemoteClient *c, u16 id, const u8 *payload,
                               size_t payload_size) {
    BreakNetEnvelope env;
    u8 wire[BREAK_NET_ENVELOPE_HEADER_SIZE + BREAK_EDITOR_PROTO_MAX_PAYLOAD];
    size_t wire_size = 0u;
    size_t off = 0u;
    ASSERT_TRUE(payload_size <= BREAK_EDITOR_PROTO_MAX_PAYLOAD);
    memset(&env, 0, sizeof(env));
    env.protocol_version = BREAK_EDITOR_PROTO_VERSION;
    env.message_id = id;
    env.sequence = c->next_seq++;
    env.payload = payload;
    env.payload_size = payload_size;
    ASSERT_EQ(break_net_envelope_encode(&env, wire, sizeof(wire), &wire_size),
              BREAK_NET_ENVELOPE_OK);
    /* Deliver before returning: the request must reach the server before
     * the following remote_client_recv starts pumping for the response,
     * otherwise the deadline could pass with the frame still local. */
    while (off < wire_size) {
        ssize_t n = write(c->fd, wire + off, wire_size - off);
        ASSERT_TRUE(n > 0);
        off += (size_t)n;
        remote_client_pump(c, 0);
    }
}

/* Hand-crafts one envelope WITHOUT the codec (unknown ids / oversized
 * payloads the codec refuses to encode — the fail-closed negative tests). */
static void remote_client_send_raw(RemoteClient *c, u16 id,
                                   const u8 *payload, size_t payload_size) {
    u8 frame[BREAK_NET_ENVELOPE_HEADER_SIZE + 5000];
    size_t off = 0u;
    ASSERT_TRUE(payload_size <= 5000u);
    ASSERT_TRUE(payload_size == 0u || payload != NULL);
    wr32(frame, BREAK_NET_ENVELOPE_MAGIC);
    wr16(frame + 4u, BREAK_EDITOR_PROTO_VERSION);
    wr16(frame + 6u, id);
    wr16(frame + 8u, 0u);
    wr32(frame + 10u, c->next_seq++);
    wr32(frame + 14u, (u32)payload_size);
    if (payload_size != 0u) {
        memcpy(frame + BREAK_NET_ENVELOPE_HEADER_SIZE, payload, payload_size);
    }
    off = 0u;
    while (off < BREAK_NET_ENVELOPE_HEADER_SIZE + payload_size) {
        ssize_t n = write(c->fd, frame + off,
                          BREAK_NET_ENVELOPE_HEADER_SIZE + payload_size - off);
        if (n <= 0) {
            break; /* the server may close mid-write (fail closed) */
        }
        off += (size_t)n;
    }
}

/* Reads exactly one response envelope, pumping the host between reads.
 * Returns the payload size; the envelope is decoded into *out_env with
 * out_env->payload pointing into the static buffer. Returns SIZE_MAX on a
 * read failure (the callers assert against their expected size, which never
 * equals SIZE_MAX). */
static size_t remote_client_recv(RemoteClient *c, BreakNetEnvelope *out_env) {
    static u8 buf[BREAK_NET_ENVELOPE_HEADER_SIZE +
                  BREAK_EDITOR_PROTO_MAX_PAYLOAD];
    size_t have = 0u;
    size_t need;
    u32 payload_size;
    u64 deadline = remote_monotonic_us() + UINT64_C(3000000);
    while (have < BREAK_NET_ENVELOPE_HEADER_SIZE &&
           remote_monotonic_us() < deadline) {
        struct pollfd pfd = {c->fd, POLLIN, 0};
        remote_client_pump(c, 0);
        if (poll(&pfd, 1, 10) > 0) {
            ssize_t n = read(c->fd, buf + have, sizeof(buf) - have);
            if (n <= 0) {
                break;
            }
            have += (size_t)n;
        }
    }
    if (have < BREAK_NET_ENVELOPE_HEADER_SIZE) {
        return SIZE_MAX;
    }
    payload_size = (u32)buf[14] | ((u32)buf[15] << 8u) | ((u32)buf[16] << 16u) |
                   ((u32)buf[17] << 24u);
    need = BREAK_NET_ENVELOPE_HEADER_SIZE + (size_t)payload_size;
    if (need > sizeof(buf)) {
        return SIZE_MAX;
    }
    while (have < need && remote_monotonic_us() < deadline) {
        struct pollfd pfd = {c->fd, POLLIN, 0};
        remote_client_pump(c, 0);
        if (poll(&pfd, 1, 10) > 0) {
            ssize_t n = read(c->fd, buf + have, sizeof(buf) - have);
            if (n <= 0) {
                break;
            }
            have += (size_t)n;
        }
    }
    if (have != need ||
        break_net_envelope_decode(buf, have, out_env) != BREAK_NET_ENVELOPE_OK) {
        return SIZE_MAX;
    }
    return out_env->payload_size;
}

static void remote_client_wait_eof(RemoteClient *c) {
    u64 deadline = remote_monotonic_us() + UINT64_C(3000000);
    u8 sink[64];
    while (remote_monotonic_us() < deadline) {
        struct pollfd pfd = {c->fd, POLLIN, 0};
        int ready;
        remote_client_pump(c, 0);
        ready = poll(&pfd, 1, 10);
        if (ready > 0 && (pfd.revents & (POLLIN | POLLHUP | POLLERR)) != 0) {
            ssize_t n = read(c->fd, sink, sizeof(sink));
            if (n == 0) {
                c->saw_eof = true;
                return;
            }
        }
    }
}

/* Waits until the host drops the connection from its table. */
static void remote_wait_connection_count(BreakEditorRemote *remote,
                                         BreakEditorShell *shell, u32 want) {
    u64 deadline = remote_monotonic_us() + UINT64_C(3000000);
    while (remote_monotonic_us() < deadline) {
        if (break_editor_remote_connection_count(remote) == want) {
            return;
        }
        break_editor_shell_tick(shell);
        {
            struct timespec ts = {0, 1000000L};
            nanosleep(&ts, NULL);
        }
    }
}

static BreakEditorRemote *remote_start_default(BreakEditorShell *shell) {
    BreakEditorRemoteConfig cfg;
    BreakEditorRemote *remote;
    memset(&cfg, 0, sizeof(cfg));
    cfg.bind_host = "127.0.0.1";
    cfg.bind_port = 0u;
    cfg.max_connections = 8u;
    remote = break_editor_remote_create(shell, &cfg);
    if (remote == NULL) {
        printf("  FAIL: %s:%d: remote create returned NULL\n", __FILE__,
               __LINE__);
        g_test_fail++;
        return NULL;
    }
    if (!break_editor_remote_start(remote)) {
        printf("  FAIL: %s:%d: remote start failed\n", __FILE__, __LINE__);
        g_test_fail++;
        break_editor_remote_destroy(remote);
        return NULL;
    }
    if (break_editor_remote_port(remote) == 0u) {
        printf("  FAIL: %s:%d: remote port is 0 after start\n", __FILE__,
               __LINE__);
        g_test_fail++;
        break_editor_remote_destroy(remote);
        return NULL;
    }
    /* the shell tick drives the remote once per frame (borrowed — the test
     * destroys the remote before the shell) */
    break_editor_shell_set_remote(shell, remote);
    return remote;
}

TEST(remote_protocol_ids_live_in_default_registry)
{
    /* The envelope codec only consults the default registry, so every editor
     * id must be registered there with the 4096 B payload limit and v1. */
    const struct {
        u16 id;
    } ids[] = {{BREAK_EDITOR_MSG_DESCRIBE}, {BREAK_EDITOR_MSG_LIST},
               {BREAK_EDITOR_MSG_SPAWN},    {BREAK_EDITOR_MSG_REMOVE},
               {BREAK_EDITOR_MSG_RENAME},   {BREAK_EDITOR_MSG_SET_FIELD},
               {BREAK_EDITOR_MSG_UNDO},     {BREAK_EDITOR_MSG_REDO},
               {BREAK_EDITOR_MSG_EVAL},     {BREAK_EDITOR_MSG_RESULT}};
    const BreakNetMessageRegistry *registry = break_net_message_registry_default();
    usize i;
    for (i = 0u; i < sizeof(ids) / sizeof(ids[0]); i++) {
        const BreakNetMessageDefinition *def =
            break_net_message_registry_lookup(registry, ids[i].id);
        ASSERT_NOT_NULL(def);
        ASSERT_EQ(def->minimum_version, 1u);
        ASSERT_EQ(def->maximum_version, 1u);
        ASSERT_EQ(def->payload_limit, (size_t)BREAK_EDITOR_PROTO_MAX_PAYLOAD);
    }
    /* 4..19 free space is claimed, not beyond */
    ASSERT_TRUE(break_net_message_registry_lookup(registry, 20u) == NULL);
}

TEST(remote_describe_returns_version_entity_count_dirty)
{
    BreakEditorShell *shell = break_editor_shell_create_for_test();
    BreakEditorRemote *remote;
    RemoteClient c;
    BreakNetEnvelope rsp;
    BreakEditorDoc *doc;
    ASSERT_NOT_NULL(shell);
    remote = remote_start_default(shell);
    ASSERT_NOT_NULL(remote);
    remote_client_connect(&c, shell, remote);
    doc = break_editor_shell_doc(shell);
    remote_client_send(&c, BREAK_EDITOR_MSG_DESCRIBE, NULL, 0u);
    ASSERT_EQ(remote_client_recv(&c, &rsp), 7u);
    ASSERT_EQ(rsp.message_id, BREAK_EDITOR_MSG_DESCRIBE);
    ASSERT_EQ(rd16(((const u8 *)rsp.payload)), BREAK_EDITOR_PROTO_VERSION);
    ASSERT_EQ((u32)((const u8 *)rsp.payload)[2] | ((u32)((const u8 *)rsp.payload)[3] << 8u) |
                  ((u32)((const u8 *)rsp.payload)[4] << 16u) | ((u32)((const u8 *)rsp.payload)[5] << 24u),
              (u32)break_editor_doc_entity_count(doc));
    ASSERT_EQ(((const u8 *)rsp.payload)[6], 0u); /* clean doc */
    /* a spawn flips the dirty flag reported by the next DESCRIBE
     * (name_len 0 = generated name) */
    remote_client_send(&c, BREAK_EDITOR_MSG_SPAWN, (const u8[]){0u, 0u}, 2u);
    ASSERT_EQ(remote_client_recv(&c, &rsp), 8u);
    ASSERT_EQ(rsp.message_id, BREAK_EDITOR_MSG_SPAWN);
    remote_client_send(&c, BREAK_EDITOR_MSG_DESCRIBE, NULL, 0u);
    ASSERT_EQ(remote_client_recv(&c, &rsp), 7u);
    ASSERT_EQ(((const u8 *)rsp.payload)[6], 1u);
    remote_client_close(&c);
    break_editor_remote_destroy(remote);
    break_editor_shell_destroy(shell);
}

TEST(remote_spawn_list_rename_remove_roundtrip_and_ctrl_z_pin)
{
    BreakEditorShell *shell = break_editor_shell_create_for_test();
    BreakEditorRemote *remote;
    RemoteClient c;
    BreakNetEnvelope rsp;
    BreakEditorDoc *doc;
    u32 index, generation;
    ASSERT_NOT_NULL(shell);
    remote = remote_start_default(shell);
    ASSERT_NOT_NULL(remote);
    remote_client_connect(&c, shell, remote);
    doc = break_editor_shell_doc(shell);

    /* SPAWN "hero" → entity id {index, generation} */
    {
        u8 req[2 + 4];
        wr16(req, 4u);
        memcpy(req + 2u, "hero", 4u);
        remote_client_send(&c, BREAK_EDITOR_MSG_SPAWN, req, 6u);
    }
    ASSERT_EQ(remote_client_recv(&c, &rsp), 8u);
    ASSERT_EQ(rsp.message_id, BREAK_EDITOR_MSG_SPAWN);
    index = (u32)((const u8 *)rsp.payload)[0] | ((u32)((const u8 *)rsp.payload)[1] << 8u) |
            ((u32)((const u8 *)rsp.payload)[2] << 16u) | ((u32)((const u8 *)rsp.payload)[3] << 24u);
    generation = (u32)((const u8 *)rsp.payload)[4] | ((u32)((const u8 *)rsp.payload)[5] << 8u) |
                 ((u32)((const u8 *)rsp.payload)[6] << 16u) | ((u32)((const u8 *)rsp.payload)[7] << 24u);
    ASSERT_EQ(break_editor_doc_entity_count(doc), 1u);

    /* LIST → one row {id, "hero"} */
    remote_client_send(&c, BREAK_EDITOR_MSG_LIST, NULL, 0u);
    ASSERT_EQ(remote_client_recv(&c, &rsp), 2u + 8u + 2u + 4u);
    ASSERT_EQ(rsp.message_id, BREAK_EDITOR_MSG_LIST);
    ASSERT_EQ(rd16(((const u8 *)rsp.payload)), 1u);
    ASSERT_EQ(rd16(((const u8 *)rsp.payload) + 10u), 4u);
    ASSERT_TRUE(memcmp(((const u8 *)rsp.payload) + 12u, "hero", 4u) == 0);

    /* RENAME id → "villain" */
    {
        u8 req[17];
        wr32(req, index);
        wr32(req + 4u, generation);
        wr16(req + 8u, 7u);
        memcpy(req + 10u, "villain", 7u);
        remote_client_send(&c, BREAK_EDITOR_MSG_RENAME, req, 17u);
    }
    ASSERT_EQ(remote_client_recv(&c, &rsp), 1u);
    ASSERT_EQ(rsp.message_id, BREAK_EDITOR_MSG_RENAME);
    ASSERT_EQ(((const u8 *)rsp.payload)[0], 1u);
    {
        BreakEditorEntityId id = {index, generation};
        const char *name = NULL;
        BreakEditorEntityId got;
        ASSERT_TRUE(break_editor_doc_entity_at(doc, 0u, &got, &name));
        ASSERT_STR_EQ(name, "villain");
        ASSERT_TRUE(break_editor_entity_id_eq(got, id));
    }

    /* REMOVE id → removed=1, doc empty */
    {
        u8 req[8];
        wr32(req, index);
        wr32(req + 4u, generation);
        remote_client_send(&c, BREAK_EDITOR_MSG_REMOVE, req, 8u);
    }
    ASSERT_EQ(remote_client_recv(&c, &rsp), 1u);
    ASSERT_EQ(((const u8 *)rsp.payload)[0], 1u);
    ASSERT_EQ(break_editor_doc_entity_count(doc), 0u);

    /* Ctrl+Z on the shell undoes the REMOTE remove, then the rename, then
     * the spawn — the command-stack 1:1 mapping pin. */
    ASSERT_TRUE(break_editor_shell_dispatch_key(shell, 'z', MY_KEYMOD_CTRL));
    ASSERT_EQ(break_editor_doc_entity_count(doc), 1u);
    ASSERT_TRUE(break_editor_shell_dispatch_key(shell, 'z', MY_KEYMOD_CTRL));
    {
        const char *name = NULL;
        BreakEditorEntityId got;
        ASSERT_TRUE(break_editor_doc_entity_at(doc, 0u, &got, &name));
        ASSERT_STR_EQ(name, "hero");
    }
    ASSERT_TRUE(break_editor_shell_dispatch_key(shell, 'z', MY_KEYMOD_CTRL));
    ASSERT_EQ(break_editor_doc_entity_count(doc), 0u);
    remote_client_close(&c);
    break_editor_remote_destroy(remote);
    break_editor_shell_destroy(shell);
}

TEST(remote_spawn_then_remote_undo_redo)
{
    BreakEditorShell *shell = break_editor_shell_create_for_test();
    BreakEditorRemote *remote;
    RemoteClient c;
    BreakNetEnvelope rsp;
    BreakEditorDoc *doc;
    ASSERT_NOT_NULL(shell);
    remote = remote_start_default(shell);
    ASSERT_NOT_NULL(remote);
    remote_client_connect(&c, shell, remote);
    doc = break_editor_shell_doc(shell);
    remote_client_send(&c, BREAK_EDITOR_MSG_SPAWN, (const u8[]){0u, 0u}, 2u);
    ASSERT_EQ(remote_client_recv(&c, &rsp), 8u);
    ASSERT_EQ(break_editor_doc_entity_count(doc), 1u);
    /* UNDO applied=1 reverts the remote spawn (Ctrl+Z equivalence pin) */
    remote_client_send(&c, BREAK_EDITOR_MSG_UNDO, NULL, 0u);
    ASSERT_EQ(remote_client_recv(&c, &rsp), 1u);
    ASSERT_EQ(rsp.message_id, BREAK_EDITOR_MSG_UNDO);
    ASSERT_EQ(((const u8 *)rsp.payload)[0], 1u);
    ASSERT_EQ(break_editor_doc_entity_count(doc), 0u);
    /* REDO re-applies it */
    remote_client_send(&c, BREAK_EDITOR_MSG_REDO, NULL, 0u);
    ASSERT_EQ(remote_client_recv(&c, &rsp), 1u);
    ASSERT_EQ(((const u8 *)rsp.payload)[0], 1u);
    ASSERT_EQ(break_editor_doc_entity_count(doc), 1u);
    /* UNDO on an empty undo side reports applied=0 (bounded, not an error) */
    remote_client_send(&c, BREAK_EDITOR_MSG_UNDO, NULL, 0u);
    ASSERT_EQ(remote_client_recv(&c, &rsp), 1u);
    ASSERT_EQ(((const u8 *)rsp.payload)[0], 1u);
    ASSERT_EQ(break_editor_doc_entity_count(doc), 0u);
    remote_client_send(&c, BREAK_EDITOR_MSG_UNDO, NULL, 0u);
    ASSERT_EQ(remote_client_recv(&c, &rsp), 1u);
    ASSERT_EQ(((const u8 *)rsp.payload)[0], 0u);
    remote_client_close(&c);
    break_editor_remote_destroy(remote);
    break_editor_shell_destroy(shell);
}

TEST(remote_set_field_maps_component_and_field_names)
{
    BreakEditorShell *shell = break_editor_shell_create_for_test();
    BreakEditorRemote *remote;
    RemoteClient c;
    BreakNetEnvelope rsp;
    BreakEditorDoc *doc;
    u32 index, generation;
    f32 value = 0.0f;
    BreakEditorEntityId id;
    ASSERT_NOT_NULL(shell);
    remote = remote_start_default(shell);
    ASSERT_NOT_NULL(remote);
    remote_client_connect(&c, shell, remote);
    doc = break_editor_shell_doc(shell);
    remote_client_send(&c, BREAK_EDITOR_MSG_SPAWN, (const u8[]){0u, 0u}, 2u);
    ASSERT_EQ(remote_client_recv(&c, &rsp), 8u);
    index = (u32)((const u8 *)rsp.payload)[0] | ((u32)((const u8 *)rsp.payload)[1] << 8u) |
            ((u32)((const u8 *)rsp.payload)[2] << 16u) | ((u32)((const u8 *)rsp.payload)[3] << 24u);
    generation = (u32)((const u8 *)rsp.payload)[4] | ((u32)((const u8 *)rsp.payload)[5] << 8u) |
                 ((u32)((const u8 *)rsp.payload)[6] << 16u) | ((u32)((const u8 *)rsp.payload)[7] << 24u);
    id.index = index;
    id.generation = generation;

    /* SET_FIELD without the component → RESULT status=failed (never a
     * half-applied record: no implicit component add on the wire path) */
    ASSERT_FALSE(break_editor_doc_has_component(doc, id,
                                                BREAK_EDITOR_COMPONENT_TRANSFORM));
    {
        u8 req[8 + 2 + 9 + 2 + 5 + 4];
        size_t n = 0u;
        f32 v = 1.5f;
        wr32(req + n, index); n += 4u;
        wr32(req + n, generation); n += 4u;
        wr16(req + n, 9u); n += 2u;
        memcpy(req + n, "Transform", 9u); n += 9u;
        wr16(req + n, 5u); n += 2u;
        memcpy(req + n, "pos.x", 5u); n += 5u;
        memcpy(req + n, &v, 4u); n += 4u;
        remote_client_send(&c, BREAK_EDITOR_MSG_SET_FIELD, req, n);
    }
    ASSERT_EQ(remote_client_recv(&c, &rsp), 1u);
    ASSERT_EQ(rsp.message_id, BREAK_EDITOR_MSG_SET_FIELD);
    ASSERT_EQ(((const u8 *)rsp.payload)[0], 0u); /* ok=0: bounded failure */
    ASSERT_FALSE(break_editor_doc_has_component(doc, id,
                                                BREAK_EDITOR_COMPONENT_TRANSFORM));

    /* Add the component through the shell UI (the undoable path), then the
     * remote SET_FIELD succeeds and Ctrl+Z reverts it. */
    ASSERT_TRUE(break_editor_shell_select_index(shell, 0u));
    emit_click(find(shell, "editor-component-add-64"));
    ASSERT_TRUE(break_editor_doc_has_component(doc, id,
                                               BREAK_EDITOR_COMPONENT_TRANSFORM));
    {
        u8 req[8 + 2 + 9 + 2 + 5 + 4];
        size_t n = 0u;
        f32 v = 1.5f;
        wr32(req + n, index); n += 4u;
        wr32(req + n, generation); n += 4u;
        wr16(req + n, 9u); n += 2u;
        memcpy(req + n, "Transform", 9u); n += 9u;
        wr16(req + n, 5u); n += 2u;
        memcpy(req + n, "pos.x", 5u); n += 5u;
        memcpy(req + n, &v, 4u); n += 4u;
        remote_client_send(&c, BREAK_EDITOR_MSG_SET_FIELD, req, n);
    }
    ASSERT_EQ(remote_client_recv(&c, &rsp), 1u);
    ASSERT_EQ(rsp.message_id, BREAK_EDITOR_MSG_SET_FIELD);
    ASSERT_EQ(((const u8 *)rsp.payload)[0], 1u);
    ASSERT_TRUE(break_editor_doc_get_field_f32(
        doc, id, BREAK_EDITOR_COMPONENT_TRANSFORM, 0u, &value));
    ASSERT_FLOAT_EQ(value, 1.5f, 1e-6f);
    ASSERT_TRUE(break_editor_shell_dispatch_key(shell, 'z', MY_KEYMOD_CTRL));
    ASSERT_TRUE(break_editor_doc_get_field_f32(
        doc, id, BREAK_EDITOR_COMPONENT_TRANSFORM, 0u, &value));
    ASSERT_FLOAT_EQ(value, 0.0f, 1e-6f);

    /* unknown component name → RESULT invalid */
    {
        u8 req[8 + 2 + 3 + 2 + 5 + 4];
        size_t n = 0u;
        f32 v = 1.0f;
        wr32(req + n, index); n += 4u;
        wr32(req + n, generation); n += 4u;
        wr16(req + n, 3u); n += 2u;
        memcpy(req + n, "Foo", 3u); n += 3u;
        wr16(req + n, 5u); n += 2u;
        memcpy(req + n, "pos.x", 5u); n += 5u;
        memcpy(req + n, &v, 4u); n += 4u;
        remote_client_send(&c, BREAK_EDITOR_MSG_SET_FIELD, req, n);
    }
    ASSERT_EQ(remote_client_recv(&c, &rsp), 1u);
    ASSERT_EQ(rsp.message_id, BREAK_EDITOR_MSG_RESULT);
    ASSERT_EQ(((const u8 *)rsp.payload)[0], BREAK_EDITOR_PROTO_STATUS_INVALID);
    remote_client_close(&c);
    break_editor_remote_destroy(remote);
    break_editor_shell_destroy(shell);
}

TEST(remote_eval_runs_on_shell_thread_and_returns_console_tail)
{
    BreakEditorShell *shell = break_editor_shell_create_for_test();
    BreakEditorRemote *remote;
    RemoteClient c;
    BreakNetEnvelope rsp;
    u16 line_count;
    ASSERT_NOT_NULL(shell);
    remote = remote_start_default(shell);
    ASSERT_NOT_NULL(remote);
    remote_client_connect(&c, shell, remote);
    {
        u8 req[2 + 10];
        wr16(req, 10u);
        memcpy(req + 2u, "return 1+2", 10u);
        remote_client_send(&c, BREAK_EDITOR_MSG_EVAL, req, 12u);
    }
    {
        size_t size = remote_client_recv(&c, &rsp);
        const u8 *p;
        size_t off;
        u16 i;
        bool found = false;
        ASSERT_EQ(rsp.message_id, BREAK_EDITOR_MSG_EVAL);
        ASSERT_TRUE(size >= 4u);
        ASSERT_EQ(((const u8 *)rsp.payload)[0], 1u); /* ok */
        line_count = rd16(((const u8 *)rsp.payload) + 1u);
        ASSERT_TRUE(line_count >= 1u);
        p = ((const u8 *)rsp.payload) + 3u;
        off = 0u;
        for (i = 0u; i < line_count; i++) {
            u16 len = rd16(p + off);
            off += 2u;
            ASSERT_TRUE(off + len <= size - 3u);
            if (len == 6u && memcmp(p + off, "lua| 3", 6u) == 0) {
                found = true;
            }
            off += len;
        }
        ASSERT_TRUE(found);
    }
    /* the shell's own console ring carries the same line (shared ring) */
    ASSERT_TRUE(strstr(break_editor_shell_console_text(shell), "lua| 3") !=
                NULL);
    /* a failing eval returns ok=0 with bounded "lua| error:" lines and
     * ZERO partial record application (the console contract: a failed chunk
     * discards its records). */
    {
        u8 req[2 + 16];
        wr16(req, 16u);
        memcpy(req + 2u, "error('boom', 0)", 16u);
        remote_client_send(&c, BREAK_EDITOR_MSG_EVAL, req, 18u);
    }
    {
        size_t size = remote_client_recv(&c, &rsp);
        const u8 *pl;
        bool has_error_line = false;
        ASSERT_TRUE(size >= 3u);
        pl = (const u8 *)rsp.payload;
        ASSERT_EQ(pl[0], 0u);
        {
            u16 lines = rd16(pl + 1u);
            size_t off = 3u;
            u16 i;
            ASSERT_TRUE(lines >= 1u);
            for (i = 0u; i < lines; i++) {
                u16 len = rd16(pl + off);
                off += 2u;
                if (len >= 11u && memcmp(pl + off, "lua| error:", 11u) == 0) {
                    has_error_line = true;
                }
                off += len;
            }
        }
        ASSERT_TRUE(has_error_line);
        ASSERT_EQ(break_editor_doc_entity_count(break_editor_shell_doc(shell)),
                  0u);
    }
    remote_client_close(&c);
    break_editor_remote_destroy(remote);
    break_editor_shell_destroy(shell);
}

TEST(remote_eval_at_4096_boundary_and_len_mismatch_closes)
{
    BreakEditorShell *shell = break_editor_shell_create_for_test();
    BreakEditorRemote *remote;
    RemoteClient c;
    BreakNetEnvelope rsp;
    static u8 req[2 + 4094];
    ASSERT_NOT_NULL(shell);
    remote = remote_start_default(shell);
    ASSERT_NOT_NULL(remote);
    remote_client_connect(&c, shell, remote);
    /* the largest payload the registry limit admits: 4096 B total = 2 B
     * length + 4094 B text. The console core's own 4096 B input bound
     * accepts it: the eval runs and reports its outcome as bounded lines
     * (ok=1 — a bare 'xxxx' chunk is an expression whose value is
     * unrepresentable, an error LINE, not a failed eval), connection up. */
    wr16(req, 4094u);
    memset(req + 2u, 'x', 4094u);
    remote_client_send_raw(&c, BREAK_EDITOR_MSG_EVAL, req, sizeof(req));
    {
        size_t size = remote_client_recv(&c, &rsp);
        ASSERT_TRUE(size >= 3u);
        ASSERT_EQ(rsp.message_id, BREAK_EDITOR_MSG_EVAL);
        ASSERT_EQ(((const u8 *)rsp.payload)[0], 1u);
        ASSERT_EQ(break_editor_remote_connection_count(remote), 1u);
    }
    /* text_len > shipped bytes (4097 declared, 4094 sent — exact-parse
     * mismatch) is a protocol error: fail closed — the handler returns
     * false, the session manager closes the connection, and the table drops
     * it. The client-side close below delivers the CLOSE event that
     * finalizes the drop (the fail-closed path produces NO response — the
     * authoritative observable is the connection-table count). */
    wr16(req, 4097u);
    remote_client_send_raw(&c, BREAK_EDITOR_MSG_EVAL, req, sizeof(req));
    remote_client_close(&c);
    remote_wait_connection_count(remote, shell, 0u);
    ASSERT_EQ(break_editor_remote_connection_count(remote), 0u);
    /* a fresh connection still works (the remote never wedged) */
    remote_client_connect(&c, shell, remote);
    remote_client_send(&c, BREAK_EDITOR_MSG_DESCRIBE, NULL, 0u);
    ASSERT_EQ(remote_client_recv(&c, &rsp), 7u);
    ASSERT_EQ(rsp.message_id, BREAK_EDITOR_MSG_DESCRIBE);
    remote_client_close(&c);
    break_editor_remote_destroy(remote);
    break_editor_shell_destroy(shell);
}

TEST(remote_unknown_id_and_malformed_close_connection)
{
    BreakEditorShell *shell = break_editor_shell_create_for_test();
    BreakEditorRemote *remote;
    RemoteClient c;
    BreakNetEnvelope rsp;
    ASSERT_NOT_NULL(shell);
    remote = remote_start_default(shell);
    ASSERT_NOT_NULL(remote);
    remote_client_connect(&c, shell, remote);

    /* unknown id (77, unregistered): hand-crafted frame (the client-side
     * codec refuses to encode unregistered ids) — the server's frame parser
     * rejects it: fail closed, zero doc effect, connection closes. */
    remote_client_send_raw(&c, 77u, NULL, 0u);
    remote_client_wait_eof(&c);
    ASSERT_TRUE(c.saw_eof);
    remote_wait_connection_count(remote, shell, 0u);
    ASSERT_EQ(break_editor_remote_connection_count(remote), 0u);
    ASSERT_EQ(break_editor_doc_entity_count(break_editor_shell_doc(shell)),
              0u);

    /* malformed payload (REMOVE declares 8-byte entity id, ships 3): the
     * handler's exact-layout check fails closed (no response; the
     * connection-table drop is the authoritative observable — the
     * client-side close delivers the final CLOSE event). */
    remote_client_close(&c);
    remote_client_connect(&c, shell, remote);
    remote_client_send(&c, BREAK_EDITOR_MSG_REMOVE,
                       (const u8[]){1u, 2u, 3u}, 3u);
    /* the handler fails closed and the server closes the transport: the
     * client reads EOF without any response bytes */
    c.saw_eof = false;
    remote_client_wait_eof(&c);
    ASSERT_TRUE(c.saw_eof);
    remote_client_close(&c);
    remote_wait_connection_count(remote, shell, 0u);
    ASSERT_EQ(break_editor_remote_connection_count(remote), 0u);

    /* oversize payload (5000 B > the 4096 B registry limit): hand-crafted
     * frame — the server's frame parser rejects it against the registry
     * payload_limit, fail closed. */
    remote_client_close(&c);
    remote_client_connect(&c, shell, remote);
    {
        static u8 payload5000[5000];
        memset(payload5000, 0xa5u, sizeof(payload5000));
        remote_client_send_raw(&c, BREAK_EDITOR_MSG_DESCRIBE, payload5000,
                               sizeof(payload5000));
        remote_client_wait_eof(&c);
        ASSERT_TRUE(c.saw_eof);
    }
    /* remote still running; a fresh connection works */
    remote_client_close(&c);
    remote_client_connect(&c, shell, remote);
    remote_client_send(&c, BREAK_EDITOR_MSG_DESCRIBE, NULL, 0u);
    ASSERT_EQ(remote_client_recv(&c, &rsp), 7u);
    remote_client_close(&c);
    break_editor_remote_destroy(remote);
    break_editor_shell_destroy(shell);
}

TEST(remote_disabled_leaves_shell_untouched)
{
    BreakEditorShell *shell = break_editor_shell_create_for_test();
    char status_snapshot[256];
    char console_snapshot[1024];
    ASSERT_NOT_NULL(shell);
    /* never created, never started: ticks and shortcuts behave exactly as
     * today (byte-identical status/console text across ticks) */
    snprintf(status_snapshot, sizeof(status_snapshot), "%s",
             break_editor_shell_status_text(shell));
    snprintf(console_snapshot, sizeof(console_snapshot), "%s",
             break_editor_shell_console_text(shell));
    break_editor_shell_tick(shell);
    break_editor_shell_tick(shell);
    ASSERT_STR_EQ(break_editor_shell_status_text(shell), status_snapshot);
    ASSERT_STR_EQ(break_editor_shell_console_text(shell), console_snapshot);
    ASSERT_TRUE(break_editor_shell_dispatch_key(shell, 'w', 0u));
    ASSERT_STR_EQ(break_editor_shell_tool_text(shell), "Tool: Translate");
    /* created but never started: still untouched */
    {
        BreakEditorRemoteConfig cfg;
        BreakEditorRemote *remote;
        memset(&cfg, 0, sizeof(cfg));
        cfg.bind_host = "127.0.0.1";
        cfg.max_connections = 4u;
        remote = break_editor_remote_create(shell, &cfg);
        ASSERT_NOT_NULL(remote);
        ASSERT_FALSE(break_editor_remote_is_running(remote));
        break_editor_shell_tick(shell);
        ASSERT_STR_EQ(break_editor_shell_tool_text(shell), "Tool: Translate");
        break_editor_remote_destroy(remote);
    }
    break_editor_shell_destroy(shell);
}

TEST(remote_tick_wiring_polls_adapter_every_frame)
{
    BreakEditorShell *shell = break_editor_shell_create_for_test();
    BreakEditorRemote *remote;
    RemoteClient c;
    u64 t0, t1;
    ASSERT_NOT_NULL(shell);
    remote = remote_start_default(shell);
    ASSERT_NOT_NULL(remote);
    /* detached: the shell tick leaves the remote alone (default OFF
     * discipline — the host wires it via break_editor_shell_set_remote) */
    break_editor_shell_set_remote(shell, NULL);
    ASSERT_TRUE(break_editor_shell_remote(shell) == NULL);
    t0 = break_editor_remote_poll_count(remote);
    break_editor_shell_tick(shell);
    t1 = break_editor_remote_poll_count(remote);
    ASSERT_EQ(t1, t0);
    /* attached: exactly one poll_adapter cycle per shell tick */
    break_editor_shell_set_remote(shell, remote);
    ASSERT_TRUE(break_editor_shell_remote(shell) == remote);
    break_editor_shell_tick(shell);
    t1 = break_editor_remote_poll_count(remote);
    ASSERT_TRUE(t1 > t0);
    t0 = t1;
    break_editor_shell_tick(shell);
    break_editor_shell_tick(shell);
    t1 = break_editor_remote_poll_count(remote);
    ASSERT_TRUE(t1 >= t0 + 2u);
    /* while a client is connected, each tick keeps polling */
    remote_client_connect(&c, shell, remote);
    t0 = break_editor_remote_poll_count(remote);
    break_editor_shell_tick(shell);
    t1 = break_editor_remote_poll_count(remote);
    ASSERT_TRUE(t1 > t0);
    remote_client_close(&c);
    break_editor_remote_destroy(remote);
    break_editor_shell_destroy(shell);
}

TEST(remote_config_validation_and_snapshot)
{
    BreakEditorShell *shell = break_editor_shell_create_for_test();
    BreakEditorRemoteConfig cfg;
    BreakEditorRemote *remote;
    RemoteClient c;
    u64 keys[8];
    u32 states[8];
    u32 rows;
    ASSERT_NOT_NULL(shell);
    memset(&cfg, 0, sizeof(cfg));
    cfg.bind_host = "127.0.0.1";
    cfg.max_connections = 33u; /* over the ≤ 32 cap */
    ASSERT_TRUE(break_editor_remote_create(shell, &cfg) == NULL);
    cfg.max_connections = 0u;  /* 0 = default cap */
    remote = break_editor_remote_create(shell, &cfg);
    ASSERT_NOT_NULL(remote);
    /* TLS without cert/key fails closed at start */
    {
        BreakEditorRemoteConfig tls_cfg;
        BreakEditorRemote *tls_remote;
        memset(&tls_cfg, 0, sizeof(tls_cfg));
        tls_cfg.bind_host = "127.0.0.1";
        tls_cfg.max_connections = 4u;
        tls_cfg.use_tls = true;
        tls_remote = break_editor_remote_create(shell, &tls_cfg);
        ASSERT_NOT_NULL(tls_remote);
        ASSERT_FALSE(break_editor_remote_start(tls_remote));
        ASSERT_FALSE(break_editor_remote_is_running(tls_remote));
        break_editor_remote_destroy(tls_remote);
    }
    ASSERT_TRUE(break_editor_remote_start(remote));
    ASSERT_EQ(break_editor_remote_admission_denied(remote), 0u);
    /* attach the remote to the shell's per-frame tick (the host wiring —
     * remote_start_default does this for the other tests) */
    break_editor_shell_set_remote(shell, remote);
    remote_client_connect(&c, shell, remote);
    rows = break_editor_remote_connections_snapshot(remote, keys, states, 8u);
    ASSERT_EQ(rows, 1u);
    ASSERT_NEQ(keys[0], 0u);
    ASSERT_EQ(states[0], (u32)BREAK_SESSION_AUTHENTICATED);
    ASSERT_EQ(break_editor_remote_session_id(remote, keys[0]), 1u);
    remote_client_close(&c);
    remote_wait_connection_count(remote, shell, 0u);
    ASSERT_EQ(break_editor_remote_connection_count(remote), 0u);
    break_editor_remote_destroy(remote);
    break_editor_shell_destroy(shell);
}

TEST(remote_null_and_bounded_calls_are_safe)
{
    break_editor_remote_destroy(NULL);
    break_editor_remote_tick(NULL);
    ASSERT_FALSE(break_editor_remote_is_running(NULL));
    ASSERT_EQ(break_editor_remote_port(NULL), 0u);
    ASSERT_EQ(break_editor_remote_admission_denied(NULL), 0u);
    ASSERT_EQ(break_editor_remote_connection_count(NULL), 0u);
    ASSERT_EQ(break_editor_remote_connections_snapshot(NULL, NULL, NULL, 0u),
              0u);
    ASSERT_EQ(break_editor_remote_poll_count(NULL), 0u);
    ASSERT_EQ(break_editor_remote_session_id(NULL, 1u), 0u);
    ASSERT_TRUE(break_editor_remote_create(NULL, NULL) == NULL);
    ASSERT_FALSE(break_editor_remote_set_psk(NULL, NULL, NULL));
}

/* ---------------- Phase 4 Task 3: network panel over a live remote ------- */

static const char *net_state_name(u32 state) {
    switch (state) {
    case BREAK_SESSION_NEW: return "NEW";
    case BREAK_SESSION_AUTHENTICATING: return "AUTHENTICATING";
    case BREAK_SESSION_AUTHENTICATED: return "AUTHENTICATED";
    case BREAK_SESSION_CLOSING: return "CLOSING";
    case BREAK_SESSION_CLOSED: return "CLOSED";
    default: return "UNKNOWN";
    }
}

/* Expected rows, built from the AUTHORITATIVE sources (manager apply stats
 * + reactor/remote accessors), independent of the panel's own reads. */
static void net_expected_rows(BreakEditorRemote *remote,
                              NetRowsSnapshot *out) {
    BreakSessionApplyStats st;
    u64 keys[32];
    u32 states[32];
    u32 n, i;
    memset(out, 0, sizeof(*out));
    memset(&st, 0, sizeof(st));
    break_session_manager_apply_stats(
        (const BreakSessionManager *)break_editor_remote_manager_for_test(
            remote),
        &st);
    (void)snprintf(out->rows[0], 96u,
                   "reactor: running=%u tls=%u outbound=%llu denied=%llu",
                   break_editor_remote_is_running(remote) ? 1u : 0u,
                   break_editor_remote_is_tls(remote) ? 1u : 0u,
                   (unsigned long long)break_editor_remote_outbound_count(
                       remote),
                   (unsigned long long)break_editor_remote_admission_denied(
                       remote));
    (void)snprintf(out->rows[1], 96u,
                   "session: applied=%llu unknown=%llu stale=%llu",
                   (unsigned long long)st.applied,
                   (unsigned long long)st.unknown,
                   (unsigned long long)st.stale);
    (void)snprintf(out->rows[2], 96u,
                   "session: invalid=%llu phase_rejected=%llu",
                   (unsigned long long)st.invalid,
                   (unsigned long long)st.phase_rejected);
    (void)snprintf(out->rows[3], 96u,
                   "session: duplicate=%llu handler_failed=%llu",
                   (unsigned long long)st.duplicate,
                   (unsigned long long)st.handler_failed);
    (void)snprintf(out->rows[4], 96u, "connections: %u",
                   break_editor_remote_connection_count(remote));
    n = break_editor_remote_connections_snapshot(remote, keys, states, 32u);
    for (i = 0u; i < n && i < 11u; i++) {
        (void)snprintf(out->rows[5u + i], 96u, "conn: key=%llu state=%s",
                       (unsigned long long)keys[i], net_state_name(states[i]));
    }
    out->count = 5u + i;
}

TEST(network_panel_rows_match_session_stats_and_reactor_accessors)
{
    BreakEditorShell *shell = break_editor_shell_create_for_test();
    BreakEditorRemote *remote;
    RemoteClient c;
    BreakNetEnvelope rsp;
    BreakSessionApplyStats st;
    NetRowsSnapshot got, want;
    u32 i;
    ASSERT_NOT_NULL(shell);
    g_net_clock_us = UINT64_C(1000000);
    break_editor_shell_set_network_clock_for_test(shell, net_test_clock, NULL);
    remote = remote_start_default(shell);
    ASSERT_NOT_NULL(remote);
    remote_client_connect(&c, shell, remote);
    remote_client_send(&c, BREAK_EDITOR_MSG_DESCRIBE, NULL, 0u);
    ASSERT_EQ(remote_client_recv(&c, &rsp), 7u);
    remote_client_send(&c, BREAK_EDITOR_MSG_SPAWN, (const u8[]){0u, 0u}, 2u);
    ASSERT_EQ(remote_client_recv(&c, &rsp), 8u);
    /* commands really went through the manager (non-trivial counters) */
    memset(&st, 0, sizeof(st));
    break_session_manager_apply_stats(
        (const BreakSessionManager *)break_editor_remote_manager_for_test(
            remote),
        &st);
    ASSERT_TRUE(st.applied >= 2u);
    /* past the throttle window: the panel-only tick re-snapshots (no
     * remote tick runs, so the sources are stable for the comparison) */
    g_net_clock_us += UINT64_C(250000);
    break_editor_shell_network_tick_for_test(shell);
    net_rows_capture(shell, &got);
    net_expected_rows(remote, &want);
    ASSERT_EQ(got.count, want.count);
    ASSERT_EQ(got.count, 6u); /* reactor + 3 session + header + 1 conn */
    for (i = 0u; i < got.count; i++) {
        ASSERT_STR_EQ(got.rows[i], want.rows[i]);
        ASSERT_TRUE(strlen(got.rows[i]) < 96u);
    }
    ASSERT_TRUE(strstr(got.rows[0], "running=1 tls=0") != NULL);
    ASSERT_TRUE(strstr(got.rows[5], "state=AUTHENTICATED") != NULL);
    ASSERT_TRUE(break_editor_shell_network_row_text(shell, got.count) == NULL);
    remote_client_close(&c);
    remote_wait_connection_count(remote, shell, 0u);
    /* destroy detaches the shell borrow AND the panel's: the next refresh
     * renders "remote: off" (no dangling read — ASan lane) */
    break_editor_remote_destroy(remote);
    g_net_clock_us += UINT64_C(250000);
    break_editor_shell_tick(shell);
    ASSERT_EQ(break_editor_shell_network_row_count(shell), 1u);
    ASSERT_STR_EQ(break_editor_shell_network_row_text(shell, 0u), "remote: off");
    break_editor_shell_destroy(shell);
}

TEST(network_panel_shell_destroyed_before_attached_remote)
{
    /* reverse teardown: the host destroys the shell while the remote (and
     * a live session) is still attached. The shell severs the remote's
     * back-pointer, so the later remote tick/destroy never touch the freed
     * shell, its network panel, or its doc (ASan lane pins zero reports). */
    BreakEditorShell *shell = break_editor_shell_create_for_test();
    BreakEditorRemote *remote;
    RemoteClient c;
    BreakNetEnvelope rsp;
    ASSERT_NOT_NULL(shell);
    g_net_clock_us = UINT64_C(2000000);
    break_editor_shell_set_network_clock_for_test(shell, net_test_clock, NULL);
    remote = remote_start_default(shell);
    ASSERT_NOT_NULL(remote);
    remote_client_connect(&c, shell, remote);
    remote_client_send(&c, BREAK_EDITOR_MSG_DESCRIBE, NULL, 0u);
    ASSERT_EQ(remote_client_recv(&c, &rsp), 7u);
    g_net_clock_us += UINT64_C(250000);
    break_editor_shell_tick(shell);
    ASSERT_TRUE(break_editor_shell_network_row_count(shell) >= 6u);
    break_editor_shell_destroy(shell);
    /* the orphaned remote is stopped and inert (no handler can reach the
     * freed doc; the tick is a no-op) */
    ASSERT_FALSE(break_editor_remote_is_running(remote));
    break_editor_remote_tick(remote);
    ASSERT_EQ(break_editor_remote_connection_count(remote), 1u);
    remote_client_close(&c);
    break_editor_remote_destroy(remote);
}

TEST(network_panel_rows_bounded_with_more_than_11_connections)
{
    /* 13 live connections: 5 fixed rows + 11 connection rows = 16 (the
     * storage cap); the header row still carries the full count */
    BreakEditorShell *shell = break_editor_shell_create_for_test();
    BreakEditorRemoteConfig cfg;
    BreakEditorRemote *remote;
    RemoteClient c[13];
    u32 i, n;
    ASSERT_NOT_NULL(shell);
    g_net_clock_us = UINT64_C(3000000);
    break_editor_shell_set_network_clock_for_test(shell, net_test_clock, NULL);
    memset(&cfg, 0, sizeof(cfg));
    cfg.bind_host = "127.0.0.1";
    cfg.max_connections = 16u;
    remote = break_editor_remote_create(shell, &cfg);
    ASSERT_NOT_NULL(remote);
    ASSERT_TRUE(break_editor_remote_start(remote));
    break_editor_shell_set_remote(shell, remote);
    for (i = 0u; i < 13u; i++) {
        c[i].fd = -1;
    }
    for (i = 0u; i < 13u; i++) {
        /* remote_client_connect only waits for count >= 1: adopt each
         * connection before the next connect so the accept backlog drains */
        remote_client_connect(&c[i], shell, remote);
        remote_wait_connection_count(remote, shell, i + 1u);
    }
    n = break_editor_remote_connection_count(remote);
    g_net_clock_us += UINT64_C(250000);
    break_editor_shell_network_tick_for_test(shell);
    for (i = 0u; i < 13u; i++) {
        remote_client_close(&c[i]);
    }
    ASSERT_EQ(n, 13u);
    ASSERT_EQ(break_editor_shell_network_row_count(shell), 16u);
    ASSERT_STR_EQ(break_editor_shell_network_row_text(shell, 4u),
                  "connections: 13");
    for (i = 5u; i < 16u; i++) {
        const char *t = break_editor_shell_network_row_text(shell, i);
        ASSERT_NOT_NULL(t);
        ASSERT_TRUE(strncmp(t, "conn: key=", 10u) == 0);
        ASSERT_TRUE(strlen(t) < 96u);
    }
    ASSERT_TRUE(break_editor_shell_network_row_text(shell, 16u) == NULL);
    break_editor_remote_destroy(remote);
    break_editor_shell_destroy(shell);
}

TEST(network_panel_throttle_4hz_row_storage_unchanged_within_250ms)
{
    BreakEditorShell *shell = break_editor_shell_create_for_test();
    BreakEditorRemote *remote;
    RemoteClient c;
    BreakNetEnvelope rsp;
    NetRowsSnapshot first, held, want, after;
    ASSERT_NOT_NULL(shell);
    g_net_clock_us = UINT64_C(5000000);
    break_editor_shell_set_network_clock_for_test(shell, net_test_clock, NULL);
    remote = remote_start_default(shell);
    ASSERT_NOT_NULL(remote);
    /* attach forces a re-snapshot on the next tick (the clock is frozen,
     * so this is the ONLY refresh until it advances) */
    remote_client_connect(&c, shell, remote);
    net_rows_capture(shell, &first);
    ASSERT_TRUE(first.count >= 5u);
    /* many ticks inside the window, while the sources DO change */
    g_net_clock_us += UINT64_C(100000);
    remote_client_send(&c, BREAK_EDITOR_MSG_DESCRIBE, NULL, 0u);
    ASSERT_EQ(remote_client_recv(&c, &rsp), 7u);
    g_net_clock_us += UINT64_C(149999); /* 249,999 us since the refresh */
    break_editor_shell_tick(shell);
    break_editor_shell_tick(shell);
    net_rows_capture(shell, &held);
    ASSERT_TRUE(net_rows_equal(&first, &held));
    net_expected_rows(remote, &want);
    ASSERT_FALSE(net_rows_equal(&want, &held)); /* stats moved underneath */
    /* exactly 250,000 us: refreshes to the live values */
    g_net_clock_us += UINT64_C(1);
    break_editor_shell_network_tick_for_test(shell);
    net_rows_capture(shell, &after);
    net_expected_rows(remote, &want);
    ASSERT_TRUE(net_rows_equal(&want, &after));
    ASSERT_FALSE(net_rows_equal(&first, &after));
    remote_client_close(&c);
    break_editor_remote_destroy(remote);
    break_editor_shell_destroy(shell);
}

TEST(network_panel_refresh_never_mutates_remote_state)
{
    BreakEditorShell *shell = break_editor_shell_create_for_test();
    BreakEditorRemote *remote;
    RemoteClient c;
    BreakNetEnvelope rsp;
    BreakSessionApplyStats st0, st1;
    const BreakSessionManager *mgr;
    u64 keys0[8], keys1[8];
    u32 states0[8], states1[8];
    u32 n0, n1, i;
    u64 polls0, denied0, outbound0;
    usize entities0;
    static char console0[8192];
    ASSERT_NOT_NULL(shell);
    g_net_clock_us = UINT64_C(9000000);
    break_editor_shell_set_network_clock_for_test(shell, net_test_clock, NULL);
    remote = remote_start_default(shell);
    ASSERT_NOT_NULL(remote);
    remote_client_connect(&c, shell, remote);
    remote_client_send(&c, BREAK_EDITOR_MSG_DESCRIBE, NULL, 0u);
    ASSERT_EQ(remote_client_recv(&c, &rsp), 7u);
    mgr = (const BreakSessionManager *)break_editor_remote_manager_for_test(
        remote);
    memset(&st0, 0, sizeof(st0));
    break_session_manager_apply_stats(mgr, &st0);
    n0 = break_editor_remote_connections_snapshot(remote, keys0, states0, 8u);
    polls0 = break_editor_remote_poll_count(remote);
    denied0 = break_editor_remote_admission_denied(remote);
    outbound0 = (u64)break_editor_remote_outbound_count(remote);
    entities0 = break_editor_doc_entity_count(break_editor_shell_doc(shell));
    (void)snprintf(console0, sizeof(console0), "%s",
                   break_editor_shell_console_text(shell));
    /* 8 panel-only refreshes (each past the window) */
    for (i = 0u; i < 8u; i++) {
        g_net_clock_us += UINT64_C(250000);
        break_editor_shell_network_tick_for_test(shell);
    }
    ASSERT_TRUE(break_editor_shell_network_row_count(shell) >= 6u);
    memset(&st1, 0, sizeof(st1));
    break_session_manager_apply_stats(mgr, &st1);
    ASSERT_EQ(memcmp(&st0, &st1, sizeof(st0)), 0);
    n1 = break_editor_remote_connections_snapshot(remote, keys1, states1, 8u);
    ASSERT_EQ(n1, n0);
    for (i = 0u; i < n0; i++) {
        ASSERT_EQ(keys1[i], keys0[i]);
        ASSERT_EQ(states1[i], states0[i]);
    }
    ASSERT_EQ(break_editor_remote_poll_count(remote), polls0);
    ASSERT_EQ(break_editor_remote_admission_denied(remote), denied0);
    ASSERT_EQ((u64)break_editor_remote_outbound_count(remote), outbound0);
    ASSERT_EQ(break_editor_doc_entity_count(break_editor_shell_doc(shell)),
              entities0);
    ASSERT_STR_EQ(break_editor_shell_console_text(shell), console0);
    ASSERT_TRUE(break_editor_remote_is_running(remote));
    /* the connection is still usable afterwards (no close was issued) */
    remote_client_send(&c, BREAK_EDITOR_MSG_DESCRIBE, NULL, 0u);
    ASSERT_EQ(remote_client_recv(&c, &rsp), 7u);
    remote_client_close(&c);
    break_editor_remote_destroy(remote);
    break_editor_shell_destroy(shell);
}

/* ---------------- Phase 4 Task 2: --remote CLI (default OFF) ------------- */

static bool remote_cli(int argc, const char **argv, BreakEditorRemoteCli *cli) {
    char err[160];
    err[0] = '\0';
    return break_editor_remote_cli_parse(argc, (char **)argv, cli, err,
                                         sizeof(err));
}

TEST(remote_cli_default_off_and_fail_closed_flags)
{
    static const char k_hex64[] =
        "000102030405060708090a0b0c0d0e0f101112131415161718191a1b1c1d1e1f";
    BreakEditorRemoteCli cli;
    BreakEditorRemoteConfig cfg;
    char err[160];
    u32 i;
    {
        const char *argv[] = {"editor"};
        ASSERT_TRUE(remote_cli(1, argv, &cli));
        ASSERT_FALSE(cli.enabled); /* no flag: no remote, no listener */
        ASSERT_TRUE(cli.scene_path == NULL);
    }
    {
        const char *argv[] = {"editor", "scene.bscn"};
        ASSERT_TRUE(remote_cli(2, argv, &cli));
        ASSERT_FALSE(cli.enabled);
        ASSERT_STR_EQ(cli.scene_path, "scene.bscn");
    }
    {
        /* --remote requires TLS cert/key AND a PSK: fail closed */
        const char *argv[] = {"editor", "--remote"};
        err[0] = '\0';
        ASSERT_FALSE(break_editor_remote_cli_parse(2, (char **)argv, &cli, err,
                                                   sizeof(err)));
        ASSERT_TRUE(err[0] != '\0');
    }
    {
        const char *argv[] = {"editor", "--remote", "--remote-cert", "c.pem",
                              "--remote-key", "k.pem"};
        ASSERT_FALSE(remote_cli(6, argv, &cli));
    }
    {
        const char *argv[] = {"editor", "--remote", "--remote-psk-hex", k_hex64};
        ASSERT_FALSE(remote_cli(4, argv, &cli)); /* no cert/key */
    }
    {
        /* remote options without --remote are rejected (no silent no-op) */
        const char *argv[] = {"editor", "--remote-port", "5000"};
        ASSERT_FALSE(remote_cli(3, argv, &cli));
    }
    {
        const char *argv[] = {"editor", "--remote", "--remote-port", "70000",
                              "--remote-cert", "c.pem", "--remote-key", "k.pem",
                              "--remote-psk-hex", k_hex64};
        ASSERT_FALSE(remote_cli(10, argv, &cli));
    }
    {
        const char *argv[] = {"editor", "--remote", "--remote-cert", "c.pem",
                              "--remote-key", "k.pem", "--remote-psk-hex",
                              "0011"};
        ASSERT_FALSE(remote_cli(8, argv, &cli)); /* short PSK */
    }
    {
        const char *argv[] = {"editor", "--remote", "--remote-cert", "c.pem",
                              "--remote-key", "k.pem", "--remote-psk-hex",
                              k_hex64, "--remote-key-id-hex", "zz00000000000000"};
        ASSERT_FALSE(remote_cli(10, argv, &cli)); /* non-hex key id */
    }
    {
        const char *argv[] = {"editor", "--remote", "--remote-bogus"};
        ASSERT_FALSE(remote_cli(3, argv, &cli));
    }
    {
        /* an inline "=value" is never echoed: it may be the PSK */
        char argbuf[96];
        const char *argv[] = {"editor", "--remote", argbuf};
        snprintf(argbuf, sizeof(argbuf), "--remote-psk-hex=%s", k_hex64);
        err[0] = '\0';
        ASSERT_FALSE(break_editor_remote_cli_parse(3, (char **)argv, &cli, err,
                                                   sizeof(err)));
        ASSERT_TRUE(strstr(err, "--remote-psk-hex") != NULL);
        ASSERT_TRUE(strstr(err, "0001020304") == NULL);
    }
    {
        const char *argv[] = {"editor", "--remote", "--remote-cert"};
        ASSERT_FALSE(remote_cli(3, argv, &cli)); /* missing value */
    }
    {
        const char *argv[] = {"editor",          "--remote",
                              "--remote-port",   "5000",
                              "--remote-cert",   "c.pem",
                              "--remote-key",    "k.pem",
                              "--remote-ca",     "ca.pem",
                              "--remote-psk-hex", k_hex64,
                              "--remote-key-id-hex", "6564697430303031",
                              "my.bscn"};
        ASSERT_TRUE(remote_cli(15, argv, &cli));
        ASSERT_TRUE(cli.enabled);
        ASSERT_EQ(cli.port, 5000u);
        ASSERT_STR_EQ(cli.cert_file, "c.pem");
        ASSERT_STR_EQ(cli.key_file, "k.pem");
        ASSERT_STR_EQ(cli.ca_file, "ca.pem");
        ASSERT_STR_EQ(cli.scene_path, "my.bscn");
        ASSERT_TRUE(cli.has_psk);
        for (i = 0u; i < 32u; i++) {
            ASSERT_EQ(cli.psk[i], (u8)i);
        }
        ASSERT_TRUE(memcmp(cli.key_id, "edit0001", 8u) == 0);
        break_editor_remote_cli_to_config(&cli, &cfg);
        ASSERT_STR_EQ(cfg.bind_host, "127.0.0.1"); /* loopback-first */
        ASSERT_EQ(cfg.bind_port, 5000u);
        ASSERT_TRUE(cfg.use_tls); /* TLS is required for --remote */
        ASSERT_STR_EQ(cfg.tls_cert_file, "c.pem");
        ASSERT_EQ(cfg.rate_global_per_sec,
                  BREAK_EDITOR_REMOTE_DEFAULT_RATE_PER_SEC);
        ASSERT_EQ(cfg.rate_global_burst, BREAK_EDITOR_REMOTE_DEFAULT_RATE_BURST);
        ASSERT_EQ(cfg.rate_per_ip_per_minute,
                  BREAK_EDITOR_REMOTE_DEFAULT_RATE_PER_IP_PER_MIN);
        ASSERT_TRUE(cfg.rate_global_per_sec != 0u &&
                    cfg.rate_global_burst != 0u &&
                    cfg.rate_per_ip_per_minute != 0u);
        /* --remote always evicts peers that never authenticate */
        ASSERT_EQ(cfg.auth_timeout_ms, BREAK_EDITOR_REMOTE_DEFAULT_AUTH_TIMEOUT_MS);
        ASSERT_TRUE(cfg.auth_timeout_ms != 0u);
        break_editor_remote_cli_wipe(&cli);
        ASSERT_FALSE(cli.has_psk);
        for (i = 0u; i < 32u; i++) {
            ASSERT_EQ(cli.psk[i], 0u);
        }
        break_editor_remote_cli_wipe(NULL);
    }
    {
        /* default port + all-zero key id when not given; dev PSK file of
         * exactly 32 raw bytes */
        static const char *k_psk_path = "editor_remote_cli_test.psk";
        FILE *f = fopen(k_psk_path, "wb");
        u8 raw[33];
        ASSERT_NOT_NULL(f);
        for (i = 0u; i < 33u; i++) {
            raw[i] = (u8)(0xa0u + i);
        }
        ASSERT_EQ(fwrite(raw, 1u, 32u, f), 32u);
        fclose(f);
        {
            const char *argv[] = {"editor", "--remote", "--remote-cert", "c.pem",
                                  "--remote-key", "k.pem", "--remote-psk-file",
                                  k_psk_path};
            ASSERT_TRUE(remote_cli(8, argv, &cli));
            ASSERT_EQ(cli.port, BREAK_EDITOR_REMOTE_DEFAULT_PORT);
            ASSERT_TRUE(memcmp(cli.psk, raw, 32u) == 0);
            for (i = 0u; i < 8u; i++) {
                ASSERT_EQ(cli.key_id[i], 0u);
            }
            ASSERT_TRUE(cli.ca_file == NULL);
        }
        f = fopen(k_psk_path, "wb");
        ASSERT_NOT_NULL(f);
        ASSERT_EQ(fwrite(raw, 1u, 33u, f), 33u); /* wrong size: rejected */
        fclose(f);
        {
            const char *argv[] = {"editor", "--remote", "--remote-cert", "c.pem",
                                  "--remote-key", "k.pem", "--remote-psk-file",
                                  k_psk_path};
            ASSERT_FALSE(remote_cli(8, argv, &cli));
        }
        remove(k_psk_path);
        {
            const char *argv[] = {"editor", "--remote", "--remote-cert", "c.pem",
                                  "--remote-key", "k.pem", "--remote-psk-file",
                                  k_psk_path};
            ASSERT_FALSE(remote_cli(8, argv, &cli)); /* missing file */
        }
    }
}

#ifdef BREAK_ENABLE_CRYPTO

/* ---------------- Phase 4 Task 2: TLS + CHALLENGE/AUTH-v2 ----------------
 * In-test TLS client (raw socket + client-role snow_ssl_t, the
 * test_break_net_tls.c idiom). The host reactor is STEP-mode, so every wait
 * loop ticks the shell (the server only progresses on the shell thread).
 * Fixture PEMs are the pinned Snowflake self-signed test certs (test-only). */

#ifndef BREAK_TEST_SSL_FIXTURE_DIR
#error "BREAK_TEST_SSL_FIXTURE_DIR must be defined by the build system"
#endif
#define EDITOR_TLS_STR2(x) #x
#define EDITOR_TLS_STR(x) EDITOR_TLS_STR2(x)

static const u8 k_tls_psk[32] = {
    0x10u, 0x21u, 0x32u, 0x43u, 0x54u, 0x65u, 0x76u, 0x87u,
    0x98u, 0xa9u, 0xbau, 0xcbu, 0xdcu, 0xedu, 0xfeu, 0x0fu,
    0x11u, 0x22u, 0x33u, 0x44u, 0x55u, 0x66u, 0x77u, 0x88u,
    0x99u, 0xaau, 0xbbu, 0xccu, 0xddu, 0xeeu, 0xffu, 0x01u};
static const u8 k_tls_key_id[8] = {'e', 'd', 'i', 't', '0', '0', '0', '1'};

static void tls_fixture_path(char *out, size_t cap, const char *name) {
    snprintf(out, cap, "%s/%s", EDITOR_TLS_STR(BREAK_TEST_SSL_FIXTURE_DIR),
             name);
}

typedef struct {
    int fd;
    snow_ssl_ctx_t *ctx;
    snow_ssl_t *ssl;
    snow_network_buffer_t *plain;
    BreakEditorShell *shell;
    u32 next_seq;
    u8 server_nonce[16];
} TlsRemoteClient;

static void tls_client_pump(TlsRemoteClient *c, int poll_ms) {
    struct pollfd pfd = {c->fd, POLLIN, 0};
    break_editor_shell_tick(c->shell);
    (void)poll(&pfd, 1, poll_ms);
}

static bool tls_client_flush(TlsRemoteClient *c, snow_network_buffer_t *out) {
    size_t size = snow_network_buffer_length(out);
    size_t copied = 0u, off = 0u;
    u8 *flat;
    if (size == 0u) {
        return true;
    }
    flat = (u8 *)malloc(size);
    if (flat == NULL ||
        snow_network_buffer_copy_to(out, flat, size, &copied) != SNOW_OK ||
        copied != size) {
        free(flat);
        return false;
    }
    snow_network_buffer_clear(out);
    while (off < size) {
        ssize_t n = write(c->fd, flat + off, size - off);
        if (n <= 0) {
            free(flat);
            return false;
        }
        off += (size_t)n;
    }
    free(flat);
    return true;
}

/* One deadline-bounded read burst: 1 = bytes consumed, 0 = nothing yet,
 * -1 = peer closed / TLS error. */
static int tls_client_read_burst(TlsRemoteClient *c, snow_network_buffer_t *out,
                                 bool handshake) {
    u8 buf[4096];
    struct pollfd pfd = {c->fd, POLLIN, 0};
    ssize_t got;
    break_editor_shell_tick(c->shell);
    if (poll(&pfd, 1, 5) <= 0) {
        return 0;
    }
    got = read(c->fd, buf, sizeof(buf));
    if (got <= 0) {
        return -1;
    }
    if (handshake) {
        return snow_ssl_do_handshake(c->ssl, out, buf, (size_t)got) == 0 ? 1
                                                                         : -1;
    }
    return snow_ssl_read(c->ssl, buf, (size_t)got, c->plain) == 0 ? 1 : -1;
}

static bool tls_client_send_wire(TlsRemoteClient *c, const u8 *wire,
                                 size_t size) {
    snow_network_buffer_t *out = NULL;
    bool ok;
    if (snow_network_buffer_create(&out) != SNOW_OK) {
        return false;
    }
    ok = snow_ssl_write(c->ssl, (const char *)wire, size, out) == 0 &&
         tls_client_flush(c, out);
    snow_network_buffer_destroy(out);
    return ok;
}

static bool tls_client_send(TlsRemoteClient *c, u16 id, u16 version,
                            const u8 *payload, size_t size) {
    BreakNetEnvelope env;
    u8 wire[BREAK_NET_ENVELOPE_HEADER_SIZE + BREAK_EDITOR_PROTO_MAX_PAYLOAD];
    size_t wire_size = 0u;
    memset(&env, 0, sizeof(env));
    env.protocol_version = version;
    env.message_id = id;
    env.sequence = c->next_seq++;
    env.payload = payload;
    env.payload_size = size;
    if (break_net_envelope_encode(&env, wire, sizeof(wire), &wire_size) !=
        BREAK_NET_ENVELOPE_OK) {
        return false;
    }
    return tls_client_send_wire(c, wire, wire_size);
}

/* Reads one decrypted envelope; payload copied into the static buffer. */
static bool tls_client_recv(TlsRemoteClient *c, BreakNetEnvelope *out_env) {
    static u8 frame[BREAK_NET_ENVELOPE_HEADER_SIZE +
                    BREAK_EDITOR_PROTO_MAX_PAYLOAD];
    u64 deadline = remote_monotonic_us() + UINT64_C(5000000);
    while (remote_monotonic_us() < deadline) {
        size_t have = snow_network_buffer_length(c->plain);
        if (have >= BREAK_NET_ENVELOPE_HEADER_SIZE) {
            size_t n = 0u, need;
            u32 payload_size;
            if (snow_network_buffer_get_header(c->plain,
                                               BREAK_NET_ENVELOPE_HEADER_SIZE,
                                               frame, sizeof(frame), &n) !=
                SNOW_OK) {
                return false;
            }
            payload_size = (u32)frame[14] | ((u32)frame[15] << 8u) |
                           ((u32)frame[16] << 16u) | ((u32)frame[17] << 24u);
            need = BREAK_NET_ENVELOPE_HEADER_SIZE + (size_t)payload_size;
            if (need > sizeof(frame)) {
                return false;
            }
            if (have >= need) {
                if (snow_network_buffer_get_header(c->plain, need, frame,
                                                   sizeof(frame), &n) !=
                        SNOW_OK ||
                    n != need ||
                    snow_network_buffer_move_header(c->plain, need) !=
                        SNOW_OK) {
                    return false;
                }
                return break_net_envelope_decode(frame, need, out_env) ==
                       BREAK_NET_ENVELOPE_OK;
            }
        }
        if (tls_client_read_burst(c, NULL, false) < 0) {
            return false;
        }
    }
    return false;
}

/* TCP connect + TLS handshake + CHALLENGE receive (server nonce captured). */
static bool tls_client_open(TlsRemoteClient *c, BreakEditorShell *shell,
                            BreakEditorRemote *remote) {
    struct sockaddr_in address;
    snow_ssl_ctx_opts_t opts;
    snow_network_buffer_t *out = NULL;
    BreakNetEnvelope challenge;
    u64 deadline;
    bool ok = false;
    memset(c, 0, sizeof(*c));
    c->shell = shell;
    c->next_seq = 1u;
    c->fd = socket(AF_INET, SOCK_STREAM, 0);
    if (c->fd < 0) {
        return false;
    }
    memset(&address, 0, sizeof(address));
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
    address.sin_port = htons(break_editor_remote_port(remote));
    if (connect(c->fd, (const struct sockaddr *)&address, sizeof(address)) !=
        0) {
        return false;
    }
    memset(&opts, 0, sizeof(opts));
    c->ctx = snow_ssl_ctx_new(&opts, NULL);
    c->ssl = c->ctx != NULL ? snow_ssl_new(c->ctx) : NULL;
    if (c->ssl == NULL || snow_ssl_init(c->ssl, false) != SNOW_OK ||
        snow_network_buffer_create(&c->plain) != SNOW_OK ||
        snow_network_buffer_create(&out) != SNOW_OK) {
        goto done;
    }
    if (snow_ssl_do_handshake(c->ssl, out, NULL, 0u) != 0 ||
        !tls_client_flush(c, out)) {
        goto done;
    }
    deadline = remote_monotonic_us() + UINT64_C(5000000);
    while (!snow_ssl_is_handshaked(c->ssl) &&
           remote_monotonic_us() < deadline) {
        if (tls_client_read_burst(c, out, true) < 0 ||
            !tls_client_flush(c, out)) {
            goto done;
        }
    }
    if (!snow_ssl_is_handshaked(c->ssl) || !tls_client_recv(c, &challenge) ||
        challenge.message_id != BREAK_NET_MESSAGE_ID_CHALLENGE ||
        challenge.protocol_version != 1u || challenge.payload_size != 16u) {
        goto done;
    }
    memcpy(c->server_nonce, challenge.payload, 16u);
    ok = true;
done:
    snow_network_buffer_destroy(out);
    return ok;
}

/* Pumps until the server closes the stream (EOF / reset / TLS error) or
 * 5 s pass. Any decrypted bytes stay in c->plain for the caller to check. */
static bool tls_client_wait_eof(TlsRemoteClient *c) {
    u64 deadline = remote_monotonic_us() + UINT64_C(5000000);
    while (remote_monotonic_us() < deadline) {
        if (tls_client_read_burst(c, NULL, false) < 0) {
            return true;
        }
    }
    return false;
}

static void tls_client_close(TlsRemoteClient *c) {
    snow_network_buffer_destroy(c->plain);
    snow_ssl_free(c->ssl);
    snow_ssl_ctx_free(c->ctx);
    if (c->fd >= 0) {
        close(c->fd);
    }
    memset(c, 0, sizeof(*c));
    c->fd = -1;
}

/* AUTH v2: key_id[8] || client_nonce[16] || HMAC-SHA256(psk, "BRKAUTH2" ||
 * server_nonce || client_nonce). */
static bool tls_client_send_auth(TlsRemoteClient *c, const u8 key_id[8],
                                 const u8 psk[32], bool tamper) {
    u8 payload[56];
    u8 context[40];
    u32 i;
    memcpy(payload, key_id, 8u);
    for (i = 0u; i < 16u; i++) {
        payload[8u + i] = (u8)(0x5au + i);
    }
    memcpy(context, "BRKAUTH2", 8u);
    memcpy(context + 8u, c->server_nonce, 16u);
    memcpy(context + 24u, payload + 8u, 16u);
    if (!break_crypto_hmac_sha256(psk, 32u, context, sizeof(context),
                                  payload + 24u)) {
        return false;
    }
    if (tamper) {
        payload[24u] ^= 0x80u;
    }
    return tls_client_send(c, BREAK_NET_MESSAGE_ID_AUTH, 2u, payload,
                           sizeof(payload));
}

static bool tls_wait_first_state(BreakEditorRemote *remote,
                                 BreakEditorShell *shell, u32 want) {
    u64 deadline = remote_monotonic_us() + UINT64_C(5000000);
    while (remote_monotonic_us() < deadline) {
        u64 keys[4];
        u32 states[4];
        if (break_editor_remote_connections_snapshot(remote, keys, states, 4u) >=
                1u &&
            states[0] == want) {
            return true;
        }
        break_editor_shell_tick(shell);
        {
            struct timespec ts = {0, 1000000L};
            nanosleep(&ts, NULL);
        }
    }
    return false;
}

static BreakEditorRemoteConfig tls_remote_config(char *cert, char *key,
                                                 size_t cap) {
    BreakEditorRemoteConfig cfg;
    tls_fixture_path(cert, cap, "snow_test_cert.pem");
    tls_fixture_path(key, cap, "snow_test_key.pem");
    memset(&cfg, 0, sizeof(cfg));
    cfg.bind_host = "127.0.0.1";
    cfg.bind_port = 0u;
    cfg.max_connections = 8u;
    cfg.use_tls = true;
    cfg.tls_cert_file = cert;
    cfg.tls_key_file = key;
    return cfg;
}

static BreakEditorRemote *tls_remote_start_timeout(BreakEditorShell *shell,
                                                   u32 auth_timeout_ms) {
    char cert[512], key[512];
    BreakEditorRemoteConfig cfg = tls_remote_config(cert, key, sizeof(cert));
    cfg.auth_timeout_ms = auth_timeout_ms;
    BreakEditorRemote *remote = break_editor_remote_create(shell, &cfg);
    if (remote == NULL || !break_editor_remote_set_psk(remote, k_tls_key_id,
                                                       k_tls_psk) ||
        !break_editor_remote_start(remote)) {
        printf("  FAIL: %s:%d: TLS remote start failed\n", __FILE__, __LINE__);
        g_test_fail++;
        break_editor_remote_destroy(remote);
        return NULL;
    }
    break_editor_shell_set_remote(shell, remote);
    return remote;
}

static BreakEditorRemote *tls_remote_start(BreakEditorShell *shell) {
    return tls_remote_start_timeout(shell, 0u);
}

TEST(remote_tls_auth_v2_client_describe_and_spawn)
{
    BreakEditorShell *shell = break_editor_shell_create_for_test();
    BreakEditorRemote *remote;
    TlsRemoteClient c;
    BreakNetEnvelope rsp;
    BreakEditorDoc *doc;
    ASSERT_NOT_NULL(shell);
    doc = break_editor_shell_doc(shell);
    remote = tls_remote_start(shell);
    ASSERT_NOT_NULL(remote);
    ASSERT_TRUE(tls_client_open(&c, shell, remote));
    /* TLS mode never auto-authenticates: the session waits in NEW */
    ASSERT_TRUE(tls_wait_first_state(remote, shell, (u32)BREAK_SESSION_NEW));
    ASSERT_TRUE(tls_client_send_auth(&c, k_tls_key_id, k_tls_psk, false));
    ASSERT_TRUE(
        tls_wait_first_state(remote, shell, (u32)BREAK_SESSION_AUTHENTICATED));
    ASSERT_TRUE(tls_client_send(&c, BREAK_EDITOR_MSG_DESCRIBE,
                                BREAK_EDITOR_PROTO_VERSION, NULL, 0u));
    ASSERT_TRUE(tls_client_recv(&c, &rsp));
    ASSERT_EQ(rsp.message_id, BREAK_EDITOR_MSG_DESCRIBE);
    ASSERT_EQ(rsp.payload_size, 7u);
    ASSERT_EQ(rd16(rsp.payload), BREAK_EDITOR_PROTO_VERSION);
    {
        u8 req[2 + 4];
        wr16(req, 4u);
        memcpy(req + 2u, "hero", 4u);
        ASSERT_TRUE(tls_client_send(&c, BREAK_EDITOR_MSG_SPAWN,
                                    BREAK_EDITOR_PROTO_VERSION, req,
                                    sizeof(req)));
    }
    ASSERT_TRUE(tls_client_recv(&c, &rsp));
    ASSERT_EQ(rsp.message_id, BREAK_EDITOR_MSG_SPAWN);
    ASSERT_EQ(rsp.payload_size, 8u);
    ASSERT_EQ(break_editor_doc_entity_count(doc), 1u);
    /* the remote spawn stays undoable from the local shell */
    ASSERT_TRUE(break_editor_shell_dispatch_key(shell, 'z', MY_KEYMOD_CTRL));
    ASSERT_EQ(break_editor_doc_entity_count(doc), 0u);
    tls_client_close(&c);
    remote_wait_connection_count(remote, shell, 0u);
    ASSERT_EQ(break_editor_remote_connection_count(remote), 0u);
    break_editor_remote_destroy(remote);
    break_editor_shell_destroy(shell);
}

static u32 rd32le(const u8 *p) {
    return (u32)p[0] | ((u32)p[1] << 8u) | ((u32)p[2] << 16u) |
           ((u32)p[3] << 24u);
}

/* Phase 4 closeout end-to-end: one scripted client over TLS + AUTH-v2 runs
 * connect -> auth -> describe -> spawn -> remote undo -> disconnect and
 * prints an "E2E|" transcript line per step (captured into
 * docs/design/editor_remote.md). */
TEST(remote_tls_e2e_connect_auth_describe_spawn_undo_disconnect)
{
    BreakEditorShell *shell = break_editor_shell_create_for_test();
    BreakEditorRemote *remote;
    TlsRemoteClient c;
    BreakNetEnvelope rsp;
    BreakEditorDoc *doc;
    const u8 *pl;
    ASSERT_NOT_NULL(shell);
    doc = break_editor_shell_doc(shell);
    remote = tls_remote_start(shell);
    ASSERT_NOT_NULL(remote);
    printf("  E2E| listen 127.0.0.1:<ephemeral> tls=%d\n",
           break_editor_remote_is_tls(remote) ? 1 : 0);
    ASSERT_TRUE(tls_client_open(&c, shell, remote));
    printf("  E2E| connect: TLS handshake ok; <- CHALLENGE id=%u v1 16B "
           "server_nonce\n", (unsigned)BREAK_NET_MESSAGE_ID_CHALLENGE);
    ASSERT_TRUE(tls_wait_first_state(remote, shell, (u32)BREAK_SESSION_NEW));
    printf("  E2E| session state=%s\n",
           break_editor_remote_state_name((u32)BREAK_SESSION_NEW));
    ASSERT_TRUE(tls_client_send_auth(&c, k_tls_key_id, k_tls_psk, false));
    ASSERT_TRUE(
        tls_wait_first_state(remote, shell, (u32)BREAK_SESSION_AUTHENTICATED));
    printf("  E2E| -> AUTH id=%u v2 56B (key_id||client_nonce||hmac) ; "
           "session state=%s\n", (unsigned)BREAK_NET_MESSAGE_ID_AUTH,
           break_editor_remote_state_name((u32)BREAK_SESSION_AUTHENTICATED));
    ASSERT_TRUE(tls_client_send(&c, BREAK_EDITOR_MSG_DESCRIBE,
                                BREAK_EDITOR_PROTO_VERSION, NULL, 0u));
    ASSERT_TRUE(tls_client_recv(&c, &rsp));
    ASSERT_EQ(rsp.message_id, BREAK_EDITOR_MSG_DESCRIBE);
    ASSERT_EQ(rsp.payload_size, 7u);
    pl = (const u8 *)rsp.payload;
    ASSERT_EQ(rd16(pl), BREAK_EDITOR_PROTO_VERSION);
    ASSERT_EQ(rd32le(pl + 2u), 0u);
    printf("  E2E| -> DESCRIBE id=%u 0B ; <- DESCRIBE id=%u %uB version=%u "
           "entity_count=%u dirty=%u\n", (unsigned)BREAK_EDITOR_MSG_DESCRIBE,
           (unsigned)rsp.message_id, (unsigned)rsp.payload_size,
           (unsigned)rd16(pl), (unsigned)rd32le(pl + 2u), (unsigned)pl[6]);
    {
        u8 req[2 + 4];
        wr16(req, 4u);
        memcpy(req + 2u, "hero", 4u);
        ASSERT_TRUE(tls_client_send(&c, BREAK_EDITOR_MSG_SPAWN,
                                    BREAK_EDITOR_PROTO_VERSION, req,
                                    sizeof(req)));
        ASSERT_TRUE(tls_client_recv(&c, &rsp));
        ASSERT_EQ(rsp.message_id, BREAK_EDITOR_MSG_SPAWN);
        ASSERT_EQ(rsp.payload_size, 8u);
        ASSERT_EQ(break_editor_doc_entity_count(doc), 1u);
        pl = (const u8 *)rsp.payload;
        printf("  E2E| -> SPAWN id=%u 6B name=\"hero\" ; <- SPAWN id=%u %uB "
               "entity={index=%u,generation=%u} ; doc entity_count=%u\n",
               (unsigned)BREAK_EDITOR_MSG_SPAWN, (unsigned)rsp.message_id,
               (unsigned)rsp.payload_size, (unsigned)rd32le(pl),
               (unsigned)rd32le(pl + 4u),
               (unsigned)break_editor_doc_entity_count(doc));
    }
    ASSERT_TRUE(tls_client_send(&c, BREAK_EDITOR_MSG_UNDO,
                                BREAK_EDITOR_PROTO_VERSION, NULL, 0u));
    ASSERT_TRUE(tls_client_recv(&c, &rsp));
    ASSERT_EQ(rsp.message_id, BREAK_EDITOR_MSG_UNDO);
    ASSERT_EQ(rsp.payload_size, 1u);
    pl = (const u8 *)rsp.payload;
    ASSERT_EQ(pl[0], 1u);
    ASSERT_EQ(break_editor_doc_entity_count(doc), 0u);
    printf("  E2E| -> UNDO id=%u 0B ; <- UNDO id=%u %uB applied=%u ; doc "
           "entity_count=%u\n", (unsigned)BREAK_EDITOR_MSG_UNDO,
           (unsigned)rsp.message_id, (unsigned)rsp.payload_size,
           (unsigned)pl[0], (unsigned)break_editor_doc_entity_count(doc));
    tls_client_close(&c);
    remote_wait_connection_count(remote, shell, 0u);
    ASSERT_EQ(break_editor_remote_connection_count(remote), 0u);
    printf("  E2E| disconnect: client closed ; remote connection_count=%u "
           "admission_denied=%llu\n",
           (unsigned)break_editor_remote_connection_count(remote),
           (unsigned long long)break_editor_remote_admission_denied(remote));
    break_editor_remote_destroy(remote);
    break_editor_shell_destroy(shell);
}

/* mode 0 = no AUTH (command straight after the handshake), 1 = tampered
 * tag, 2 = unknown key id, 3 = AUTH v1 while v2 auth is configured. */
static void tls_unauthenticated_case(int mode) {
    static const u8 k_unknown_id[8] = {'n', 'o', 's', 'u', 'c', 'h', 'k', 'y'};
    BreakEditorShell *shell = break_editor_shell_create_for_test();
    BreakEditorRemote *remote;
    TlsRemoteClient c;
    BreakSessionApplyStats before, after;
    BreakSessionManager *manager;
    u8 spawn_req[2] = {0u, 0u};
    ASSERT_NOT_NULL(shell);
    remote = tls_remote_start(shell);
    ASSERT_NOT_NULL(remote);
    manager = (BreakSessionManager *)break_editor_remote_manager_for_test(remote);
    ASSERT_TRUE(tls_client_open(&c, shell, remote));
    ASSERT_TRUE(tls_wait_first_state(remote, shell, (u32)BREAK_SESSION_NEW));
    if (mode == 1) {
        ASSERT_TRUE(tls_client_send_auth(&c, k_tls_key_id, k_tls_psk, true));
    } else if (mode == 2) {
        ASSERT_TRUE(tls_client_send_auth(&c, k_unknown_id, k_tls_psk, false));
    } else if (mode == 3) {
        ASSERT_TRUE(tls_client_send(&c, BREAK_NET_MESSAGE_ID_AUTH, 1u,
                                    (const u8 *)"plain", 5u));
    }
    /* the first editor command: refused, session closed (fail closed) */
    ASSERT_TRUE(tls_client_send(&c, BREAK_EDITOR_MSG_SPAWN,
                                BREAK_EDITOR_PROTO_VERSION, spawn_req,
                                sizeof(spawn_req)));
    remote_wait_connection_count(remote, shell, 0u);
    ASSERT_EQ(break_editor_remote_connection_count(remote), 0u);
    ASSERT_EQ(break_editor_doc_entity_count(break_editor_shell_doc(shell)), 0u);
    /* the server now closes the transport too: the client reads EOF and
     * never receives a response byte; the session saw no applied command */
    break_session_manager_apply_stats(manager, &before);
    ASSERT_TRUE(tls_client_wait_eof(&c));
    ASSERT_EQ(snow_network_buffer_length(c.plain), 0u);
    break_session_manager_apply_stats(manager, &after);
    ASSERT_EQ(after.applied, before.applied);
    ASSERT_EQ(break_editor_doc_entity_count(break_editor_shell_doc(shell)), 0u);
    ASSERT_TRUE(break_editor_remote_server_closes(remote) >= 1u);
    tls_client_close(&c);
    break_editor_remote_destroy(remote);
    break_editor_shell_destroy(shell);
}

TEST(remote_tls_unauthenticated_clients_closed_zero_doc_effect)
{
    int mode;
    for (mode = 0; mode < 4; mode++) {
        int fail_before = g_test_fail;
        tls_unauthenticated_case(mode);
        if (g_test_fail != fail_before) {
            printf("  (unauthenticated mode %d)\n", mode);
            return;
        }
    }
}

TEST(remote_tls_auth_deadline_closes_idle_unauthenticated_client)
{
    BreakEditorShell *shell = break_editor_shell_create_for_test();
    BreakEditorRemote *remote;
    TlsRemoteClient c;
    u64 started;
    ASSERT_NOT_NULL(shell);
    remote = tls_remote_start_timeout(shell, 300u);
    ASSERT_NOT_NULL(remote);
    /* taken before connecting: the host starts its deadline clock when it
     * first sees the connection, which is later, so the gap is >= 300 ms */
    started = remote_monotonic_us();
    ASSERT_TRUE(tls_client_open(&c, shell, remote));
    ASSERT_TRUE(tls_wait_first_state(remote, shell, (u32)BREAK_SESSION_NEW));
    /* the client completes TLS but never sends AUTH: evicted by deadline */
    ASSERT_TRUE(tls_client_wait_eof(&c));
    ASSERT_TRUE(remote_monotonic_us() - started >= UINT64_C(300000));
    ASSERT_EQ(snow_network_buffer_length(c.plain), 0u);
    remote_wait_connection_count(remote, shell, 0u);
    ASSERT_EQ(break_editor_remote_connection_count(remote), 0u);
    ASSERT_EQ(break_editor_remote_auth_timeouts(remote), 1u);
    ASSERT_EQ(break_editor_doc_entity_count(break_editor_shell_doc(shell)), 0u);
    tls_client_close(&c);
    break_editor_remote_destroy(remote);
    break_editor_shell_destroy(shell);
}

TEST(remote_tls_auth_deadline_spares_authenticated_client)
{
    BreakEditorShell *shell = break_editor_shell_create_for_test();
    BreakEditorRemote *remote;
    TlsRemoteClient c;
    BreakNetEnvelope rsp;
    u64 until;
    ASSERT_NOT_NULL(shell);
    remote = tls_remote_start_timeout(shell, 300u);
    ASSERT_NOT_NULL(remote);
    ASSERT_TRUE(tls_client_open(&c, shell, remote));
    ASSERT_TRUE(tls_wait_first_state(remote, shell, (u32)BREAK_SESSION_NEW));
    ASSERT_TRUE(tls_client_send_auth(&c, k_tls_key_id, k_tls_psk, false));
    ASSERT_TRUE(
        tls_wait_first_state(remote, shell, (u32)BREAK_SESSION_AUTHENTICATED));
    /* well past the deadline the session is still served */
    until = remote_monotonic_us() + UINT64_C(700000);
    while (remote_monotonic_us() < until) {
        tls_client_pump(&c, 5);
    }
    ASSERT_EQ(break_editor_remote_connection_count(remote), 1u);
    ASSERT_TRUE(tls_client_send(&c, BREAK_EDITOR_MSG_DESCRIBE,
                                BREAK_EDITOR_PROTO_VERSION, NULL, 0u));
    ASSERT_TRUE(tls_client_recv(&c, &rsp));
    ASSERT_EQ(rsp.message_id, BREAK_EDITOR_MSG_DESCRIBE);
    ASSERT_EQ(break_editor_remote_auth_timeouts(remote), 0u);
    tls_client_close(&c);
    break_editor_remote_destroy(remote);
    break_editor_shell_destroy(shell);
}

TEST(remote_tls_start_fails_closed_on_missing_certs_or_auth)
{
    BreakEditorShell *shell = break_editor_shell_create_for_test();
    char cert[512], key[512], missing[512];
    BreakEditorRemoteConfig cfg;
    BreakEditorRemote *remote;
    ASSERT_NOT_NULL(shell);
    tls_fixture_path(missing, sizeof(missing), "no_such_cert.pem");
    /* TLS + PSK but unreadable cert file */
    cfg = tls_remote_config(cert, key, sizeof(cert));
    cfg.tls_cert_file = missing;
    remote = break_editor_remote_create(shell, &cfg);
    ASSERT_NOT_NULL(remote);
    ASSERT_TRUE(break_editor_remote_set_psk(remote, k_tls_key_id, k_tls_psk));
    ASSERT_FALSE(break_editor_remote_start(remote));
    ASSERT_FALSE(break_editor_remote_is_running(remote));
    break_editor_remote_destroy(remote);
    /* TLS + PSK but no key file */
    cfg = tls_remote_config(cert, key, sizeof(cert));
    cfg.tls_key_file = NULL;
    remote = break_editor_remote_create(shell, &cfg);
    ASSERT_NOT_NULL(remote);
    ASSERT_TRUE(break_editor_remote_set_psk(remote, k_tls_key_id, k_tls_psk));
    ASSERT_FALSE(break_editor_remote_start(remote));
    break_editor_remote_destroy(remote);
    /* valid TLS certs but no auth configured: no unauthenticated TLS path */
    cfg = tls_remote_config(cert, key, sizeof(cert));
    remote = break_editor_remote_create(shell, &cfg);
    ASSERT_NOT_NULL(remote);
    ASSERT_FALSE(break_editor_remote_start(remote));
    ASSERT_FALSE(break_editor_remote_is_running(remote));
    /* the PSK seam is configure-before-start only */
    ASSERT_FALSE(break_editor_remote_set_psk(remote, NULL, k_tls_psk));
    ASSERT_FALSE(break_editor_remote_set_psk(remote, k_tls_key_id, NULL));
    break_editor_remote_destroy(remote);
    /* a started remote refuses a late PSK change; destroy clears the
     * process-global session auth (a plaintext remote afterwards
     * auto-authenticates again — pinned by the Task 1 suite order too) */
    remote = tls_remote_start(shell);
    ASSERT_NOT_NULL(remote);
    ASSERT_FALSE(break_editor_remote_set_psk(remote, k_tls_key_id, k_tls_psk));
    break_editor_remote_destroy(remote);
    ASSERT_TRUE(break_session_set_auth(NULL, NULL));
    {
        RemoteClient pc;
        BreakNetEnvelope rsp;
        BreakEditorRemote *plain = remote_start_default(shell);
        ASSERT_NOT_NULL(plain);
        remote_client_connect(&pc, shell, plain);
        remote_client_send(&pc, BREAK_EDITOR_MSG_DESCRIBE, NULL, 0u);
        ASSERT_EQ(remote_client_recv(&pc, &rsp), 7u);
        remote_client_close(&pc);
        break_editor_remote_destroy(plain);
    }
    break_editor_shell_destroy(shell);
}

TEST(remote_tls_rate_limit_denials_observable)
{
    BreakEditorShell *shell = break_editor_shell_create_for_test();
    char cert[512], key[512];
    BreakEditorRemoteConfig cfg;
    BreakEditorRemote *remote;
    struct sockaddr_in address;
    int fds[2] = {-1, -1};
    u64 deadline;
    int i;
    ASSERT_NOT_NULL(shell);
    cfg = tls_remote_config(cert, key, sizeof(cert));
    cfg.rate_per_ip_per_minute = 1u;
    remote = break_editor_remote_create(shell, &cfg);
    ASSERT_NOT_NULL(remote);
    ASSERT_TRUE(break_editor_remote_set_psk(remote, k_tls_key_id, k_tls_psk));
    ASSERT_TRUE(break_editor_remote_start(remote));
    break_editor_shell_set_remote(shell, remote);
    ASSERT_EQ(break_editor_remote_admission_denied(remote), 0u);
    memset(&address, 0, sizeof(address));
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
    address.sin_port = htons(break_editor_remote_port(remote));
    for (i = 0; i < 2; i++) {
        fds[i] = socket(AF_INET, SOCK_STREAM, 0);
        ASSERT_TRUE(fds[i] >= 0);
        ASSERT_EQ(connect(fds[i], (const struct sockaddr *)&address,
                          sizeof(address)),
                  0);
    }
    deadline = remote_monotonic_us() + UINT64_C(5000000);
    while (remote_monotonic_us() < deadline &&
           (break_editor_remote_admission_denied(remote) < 1u ||
            break_editor_remote_connection_count(remote) < 1u)) {
        break_editor_shell_tick(shell);
        {
            struct timespec ts = {0, 1000000L};
            nanosleep(&ts, NULL);
        }
    }
    /* per-IP 1/min: the first connect is admitted, the second denied */
    ASSERT_EQ(break_editor_remote_admission_denied(remote), 1u);
    ASSERT_EQ(break_editor_remote_connection_count(remote), 1u);
    close(fds[0]);
    close(fds[1]);
    remote_wait_connection_count(remote, shell, 0u);
    break_editor_remote_destroy(remote);
    break_editor_shell_destroy(shell);
}

#endif /* BREAK_ENABLE_CRYPTO */

#endif /* BREAK_EDITOR_REMOTE_TESTS */


/* ---------------- editor asset hot reload ---------------- */

/* The legacy single-file watcher compares mtimes at one-second resolution,
 * so every simulated external edit forces a distinct future mtime instead of
 * relying on wall-clock gaps. */
static void hr_bump_mtime(const char *path) {
    static long bump = 100;
    struct stat st;
    struct utimbuf times;
    bump += 10;
    ASSERT_EQ(stat(path, &st), 0);
    times.actime = st.st_atime;
    times.modtime = time(NULL) + bump;
    ASSERT_EQ(utime(path, &times), 0);
}

static void hr_write_text(const char *path, const char *text) {
    FILE *f = fopen(path, "wb");
    ASSERT_NOT_NULL(f);
    fputs(text, f);
    fclose(f);
}

/* Simulates an external tool replacing the scene with `n` entities. */
static void hr_external_scene(const char *path, u32 n) {
    save_fixture_scene(path, n);
    hr_bump_mtime(path);
}

#define HR_WAIT(shell_, cond_)                                              \
    do {                                                                    \
        int hr_i_;                                                          \
        for (hr_i_ = 0; hr_i_ < 3000 && !(cond_); hr_i_++) {                \
            break_editor_shell_tick(shell_);                                \
            time_sleep_us(2000u);                                           \
        }                                                                   \
    } while (0)

static void hr_settle(BreakEditorShell *shell, int ticks) {
    int i;
    for (i = 0; i < ticks; i++) {
        break_editor_shell_tick(shell);
        time_sleep_us(2000u);
    }
}

/* ---------------- viewport shader reload ---------------- */

typedef struct ShaderReloadLogCapture {
    u32 calls;
    char last[160];
} ShaderReloadLogCapture;

static void shader_reload_capture_log(void *user, const char *line) {
    ShaderReloadLogCapture *capture = (ShaderReloadLogCapture *)user;
    if (capture == NULL || line == NULL) {
        return;
    }
    capture->calls++;
    snprintf(capture->last, sizeof(capture->last), "%s", line);
}

typedef struct ShaderReloadFixture {
    BreakEditorShell *shell;
    BreakEditorViewport3D *vp;
    int device;
    char root[512];
    char shaders[600];
    char vert[700];
    char frag[700];
    ShaderReloadLogCapture log;
} ShaderReloadFixture;

static void shader_reload_fixture_close(ShaderReloadFixture *fx) {
    if (fx->shell != NULL) {
        break_editor_shell_set_render_device(fx->shell, NULL);
        break_editor_shell_destroy(fx->shell);
        fx->shell = NULL;
        fx->vp = NULL;
    }
    remove(fx->vert);
    remove(fx->frag);
    if (fx->shaders[0] != '\0') {
        TEST_RMDIR(fx->shaders);
    }
    if (fx->root[0] != '\0') {
        TEST_RMDIR(fx->root);
    }
}

static void shader_reload_fixture_open(ShaderReloadFixture *fx,
                                       const char *name,
                                       const char *initial_vert,
                                       const char *initial_frag) {
    memset(fx, 0, sizeof(*fx));
    test_tmp(fx->root, sizeof(fx->root), name);
    snprintf(fx->shaders, sizeof(fx->shaders), "%s/shaders", fx->root);
    snprintf(fx->vert, sizeof(fx->vert), "%s/editor_color.vert", fx->shaders);
    snprintf(fx->frag, sizeof(fx->frag), "%s/editor_color.frag", fx->shaders);
    ASSERT_EQ(TEST_MKDIR(fx->root), 0);
    ASSERT_EQ(TEST_MKDIR(fx->shaders), 0);
    hr_write_text(fx->vert, initial_vert);
    hr_write_text(fx->frag, initial_frag);
    ASSERT_TRUE(shader_env_set(fx->root));
    fx->shell = break_editor_shell_create_for_test();
    ASSERT_NOT_NULL(fx->shell);
    fx->vp = break_editor_shell_viewport3d(fx->shell);
    ASSERT_NOT_NULL(fx->vp);
    break_editor_shell_set_render_device(fx->shell,
                                         (RHIDevice *)&fx->device);
}

static BreakEditorShaderReloadStats shader_reload_stats(
    const ShaderReloadFixture *fx) {
    BreakEditorShaderReloadStats stats;
    memset(&stats, 0, sizeof(stats));
    (void)break_editor_viewport3d_shader_reload_stats(fx->vp, &stats);
    return stats;
}

static u32 shader_reload_revision(const ShaderReloadFixture *fx) {
    BreakEditorViewport3DGpuState state;
    break_editor_viewport3d_gpu_state_for_test(fx->vp, &state);
    return editor_rhi_fake_pipeline_revision(state.pipeline);
}

static void shader_reload_assert_stage_revisions(
    const ShaderReloadFixture *fx, u32 vertex, u32 fragment) {
    BreakEditorViewport3DGpuState state;
    u32 got_vertex, got_fragment;
    break_editor_viewport3d_gpu_state_for_test(fx->vp, &state);
    got_vertex = editor_rhi_fake_pipeline_stage_revision(state.pipeline, false);
    got_fragment = editor_rhi_fake_pipeline_stage_revision(state.pipeline, true);
    ASSERT_EQ(got_vertex, vertex);
    ASSERT_EQ(got_fragment, fragment);
}

static void shader_reload_write_pair(ShaderReloadFixture *fx, u32 revision,
                                     const char *marker, bool bump) {
    char vert[128], frag[128];
    snprintf(vert, sizeof(vert), "REV=%u vertex%s\n", revision, marker);
    snprintf(frag, sizeof(frag), "REV=%u fragment%s\n", revision, marker);
    hr_write_text(fx->vert, vert);
    hr_write_text(fx->frag, frag);
    if (bump) {
        hr_bump_mtime(fx->vert);
        hr_bump_mtime(fx->frag);
    }
}

static void shader_reload_manual_shortcut_body(ShaderReloadFixture *fx) {
    BreakEditorShaderReloadStats stats;
    EditorRhiFakeStats before, after;
    shader_reload_fixture_open(fx, "editor_shader_reload_manual",
                               "REV=1 vertex\n", "REV=1 fragment\n");
    ASSERT_NOT_NULL(fx->shell);
    ASSERT_TRUE(shader_reload_stats(fx).watching);
    ASSERT_EQ(shader_reload_revision(fx), 1u);
    shader_reload_write_pair(fx, 5u, "", false);

    ASSERT_TRUE(break_editor_shell_dispatch_key(fx->shell, 'r',
                                                 MY_KEYMOD_SHIFT));
    ASSERT_STR_EQ(break_editor_shell_tool_text(fx->shell), "Tool: Scale");
    ASSERT_TRUE(break_editor_shell_dispatch_key(fx->shell, 'r',
                                                 MY_KEYMOD_NONE));
    ASSERT_STR_EQ(break_editor_shell_tool_text(fx->shell), "Tool: Scale");
    stats = shader_reload_stats(fx);
    ASSERT_EQ(stats.attempts, 0u);
    ASSERT_FALSE(stats.busy);

    editor_rhi_fake_stats(&before);
    ASSERT_TRUE(break_editor_shell_dispatch_key(
        fx->shell, 'r', MY_KEYMOD_CTRL | MY_KEYMOD_SHIFT));
    stats = shader_reload_stats(fx);
    ASSERT_TRUE(stats.busy);
    ASSERT_EQ(stats.attempts, 0u);
    editor_rhi_fake_stats(&after);
    ASSERT_TRUE(editor_fake_stats_equal(&before, &after));
    ASSERT_EQ(shader_reload_revision(fx), 1u);

    HR_WAIT(fx->shell, shader_reload_stats(fx).reloads == 1u);
    stats = shader_reload_stats(fx);
    ASSERT_EQ(stats.attempts, 1u);
    ASSERT_EQ(stats.reloads, 1u);
    ASSERT_EQ(stats.failed, 0u);
    ASSERT_FALSE(stats.busy);
    ASSERT_EQ(stats.last_result, BREAK_EDITOR_SHADER_RELOAD_APPLIED);
    ASSERT_EQ(shader_reload_revision(fx), 5u);
    ASSERT_STR_EQ(last_console_line(break_editor_shell_console_text(fx->shell)),
                  "shader reload: applied shader pair\n");
}

TEST(shader_reload_ctrl_shift_r_queues_without_sync_rhi)
{
    EditorShaderEnv env;
    ShaderReloadFixture fx;
    ASSERT_TRUE(shader_env_save(&env));
    editor_rhi_fake_reset();
    editor_rhi_fake_set_enabled(true);
    memset(&fx, 0, sizeof(fx));
    shader_reload_manual_shortcut_body(&fx);
    break_runtime_test_reload_set_gates(0u, 0u);
    shader_reload_fixture_close(&fx);
    editor_rhi_fake_set_enabled(false);
    editor_rhi_fake_reset();
    shader_env_restore(&env);
}

static void shader_reload_watcher_body(ShaderReloadFixture *fx) {
    BreakEditorShaderReloadStats stats;
    BreakEditorViewport3DStats render_stats;
    BreakEditorViewport3DGpuState before_bad, after_bad;
    EditorRhiFakeStats fake_before_bad, fake_after_bad;
    int cmd = 0;
    shader_reload_fixture_open(fx, "editor_shader_reload_watcher",
                               "REV=1 vertex\n", "REV=1 fragment\n");
    ASSERT_NOT_NULL(fx->shell);
    break_editor_viewport3d_set_shader_reload_logger(
        fx->vp, shader_reload_capture_log, &fx->log);
    break_editor_viewport3d_render(
        fx->vp, break_editor_shell_doc(fx->shell), &fx->device, &cmd, 800, 480);
    ASSERT_TRUE(break_editor_viewport3d_last_stats(fx->vp, &render_stats));
    ASSERT_EQ(render_stats.skipped, BREAK_EDITOR_VIEWPORT3D_SKIP_NONE);
    ASSERT_EQ(render_stats.fbo_w, 800u);
    ASSERT_EQ(render_stats.fbo_h, 480u);
    ASSERT_EQ(shader_reload_revision(fx), 1u);
    shader_reload_assert_stage_revisions(fx, 1u, 1u);
    stats = shader_reload_stats(fx);
    ASSERT_TRUE(stats.watching);
    ASSERT_FALSE(stats.busy);
    ASSERT_EQ(stats.attempts, 0u);

    shader_reload_write_pair(fx, 2u, "", true);
    HR_WAIT(fx->shell, shader_reload_stats(fx).reloads == 1u);
    stats = shader_reload_stats(fx);
    ASSERT_EQ(stats.reloads, 1u);
    ASSERT_EQ(stats.attempts, 1u);
    ASSERT_EQ(stats.failed, 0u);
    ASSERT_TRUE(stats.events >= 1u);
    ASSERT_EQ(stats.last_result, BREAK_EDITOR_SHADER_RELOAD_APPLIED);
    ASSERT_EQ(shader_reload_revision(fx), 2u);
    shader_reload_assert_stage_revisions(fx, 2u, 2u);
    ASSERT_TRUE(fx->log.calls >= 1u);
    {
        EditorRhiFakeStats fake;
        editor_rhi_fake_stats(&fake);
        ASSERT_EQ(fake.pipeline_destroys, 1u);
        ASSERT_EQ(fake.binding_destroys, 1u);
        ASSERT_EQ(fake.buffer_creates, 1u);
    }

    break_editor_viewport3d_gpu_state_for_test(fx->vp, &before_bad);
    editor_rhi_fake_stats(&fake_before_bad);
    shader_reload_write_pair(fx, 3u, " COMPILE_FAIL", true);
    HR_WAIT(fx->shell, shader_reload_stats(fx).failed == 1u);
    stats = shader_reload_stats(fx);
    ASSERT_EQ(stats.failed, 1u);
    ASSERT_EQ(stats.reloads, 1u);
    ASSERT_EQ(stats.last_result, BREAK_EDITOR_SHADER_RELOAD_FAILED_KEEP_OLD);
    break_editor_viewport3d_gpu_state_for_test(fx->vp, &after_bad);
    editor_rhi_fake_stats(&fake_after_bad);
    ASSERT_TRUE(viewport_gpu_state_equal(&before_bad, &after_bad));
    ASSERT_EQ(shader_reload_revision(fx), 2u);
    shader_reload_assert_stage_revisions(fx, 2u, 2u);
    ASSERT_TRUE(editor_fake_stats_equal(&fake_before_bad, &fake_after_bad));

    shader_reload_write_pair(fx, 4u, "", true);
    HR_WAIT(fx->shell, shader_reload_stats(fx).reloads == 2u);
    stats = shader_reload_stats(fx);
    ASSERT_EQ(stats.reloads, 2u);
    ASSERT_EQ(stats.failed, 1u);
    ASSERT_EQ(stats.attempts, 3u);
    ASSERT_EQ(shader_reload_revision(fx), 4u);
    shader_reload_assert_stage_revisions(fx, 4u, 4u);
    editor_rhi_fake_stats(&fake_after_bad);
    ASSERT_EQ(fake_after_bad.pipeline_destroys,
              fake_before_bad.pipeline_destroys + 1u);
    ASSERT_EQ(fake_after_bad.binding_destroys,
              fake_before_bad.binding_destroys + 1u);
    ASSERT_EQ(fake_after_bad.buffer_creates, 1u);

    break_editor_shell_set_render_device(fx->shell,
                                         (RHIDevice *)&fx->device);
    break_editor_shell_tick(fx->shell);
    ASSERT_EQ(break_editor_shell_render_row_count(fx->shell), 9u);
    ASSERT_STR_EQ(break_editor_shell_render_row_text(fx->shell, 8u),
                  "shader reload: watching busy=0 applied=2 failed=1");
}

TEST(shader_reload_watcher_applies_pair_keeps_old_and_recovers)
{
    EditorShaderEnv env;
    ShaderReloadFixture fx;
    ASSERT_TRUE(shader_env_save(&env));
    editor_rhi_fake_reset();
    editor_rhi_fake_set_enabled(true);
    memset(&fx, 0, sizeof(fx));
    shader_reload_watcher_body(&fx);
    break_runtime_test_reload_set_gates(0u, 0u);
    shader_reload_fixture_close(&fx);
    editor_rhi_fake_set_enabled(false);
    editor_rhi_fake_reset();
    shader_env_restore(&env);
}

static void shader_reload_initial_recovery_body(ShaderReloadFixture *fx) {
    BreakEditorShaderReloadStats stats;
    EditorRhiFakeStats fake;
    shader_reload_fixture_open(fx, "editor_shader_reload_initial",
                               "REV=1 COMPILE_FAIL\n", "REV=1 fragment\n");
    ASSERT_NOT_NULL(fx->shell);
    ASSERT_EQ(shader_reload_revision(fx), 0u);
    stats = shader_reload_stats(fx);
    ASSERT_TRUE(stats.watching);
    ASSERT_EQ(stats.attempts, 0u);
    hr_settle(fx->shell, 20);
    ASSERT_EQ(shader_reload_stats(fx).attempts, 0u);
    editor_rhi_fake_stats(&fake);
    ASSERT_EQ(fake.pipeline_creates, 0u);
    ASSERT_EQ(fake.buffer_creates, 0u);

    shader_reload_write_pair(fx, 2u, "", true);
    HR_WAIT(fx->shell, shader_reload_stats(fx).reloads == 1u);
    stats = shader_reload_stats(fx);
    ASSERT_EQ(stats.attempts, 1u);
    ASSERT_EQ(stats.reloads, 1u);
    ASSERT_EQ(stats.failed, 0u);
    ASSERT_EQ(shader_reload_revision(fx), 2u);
    editor_rhi_fake_stats(&fake);
    ASSERT_EQ(fake.pipeline_creates, 1u);
    ASSERT_EQ(fake.buffer_creates, 1u);
    ASSERT_EQ(fake.live_pipelines, 1u);
    ASSERT_EQ(fake.live_bindings, 1u);
    ASSERT_EQ(fake.live_buffers, 1u);
}

TEST(shader_reload_initial_failure_recovers_without_implicit_retry)
{
    EditorShaderEnv env;
    ShaderReloadFixture fx;
    ASSERT_TRUE(shader_env_save(&env));
    editor_rhi_fake_reset();
    editor_rhi_fake_set_enabled(true);
    memset(&fx, 0, sizeof(fx));
    shader_reload_initial_recovery_body(&fx);
    break_runtime_test_reload_set_gates(0u, 0u);
    shader_reload_fixture_close(&fx);
    editor_rhi_fake_set_enabled(false);
    editor_rhi_fake_reset();
    shader_env_restore(&env);
}

static void shader_reload_trailing_body(ShaderReloadFixture *fx) {
    BreakEditorShaderReloadStats stats;
    EditorRhiFakeStats fake;
    u64 popped;
    shader_reload_fixture_open(fx, "editor_shader_reload_trailing",
                               "REV=1 vertex\n", "REV=1 fragment\n");
    ASSERT_NOT_NULL(fx->shell);
    break_editor_viewport3d_set_shader_reload_logger(
        fx->vp, shader_reload_capture_log, &fx->log);
    editor_rhi_fake_stats(&fake);
    ASSERT_EQ(fake.pipeline_creates, 1u);
    popped = atomic_load_explicit(&g_break_runtime_test_reload_popped,
                                  memory_order_acquire);
    break_runtime_test_reload_set_gates(0u, 1u);
    shader_reload_write_pair(fx, 2u, "", false);
    ASSERT_TRUE(break_editor_viewport3d_request_shader_reload(fx->vp));
    break_editor_shell_tick(fx->shell);
    HR_WAIT(fx->shell,
            atomic_load_explicit(&g_break_runtime_test_reload_popped,
                                 memory_order_acquire) > popped);
    stats = shader_reload_stats(fx);
    ASSERT_TRUE(stats.busy);
    ASSERT_EQ(stats.attempts, 1u);
    editor_rhi_fake_stats(&fake);
    ASSERT_EQ(fake.pipeline_creates, 1u);
    ASSERT_EQ(fx->log.calls, 0u);

    shader_reload_write_pair(fx, 3u, "", false);
    ASSERT_TRUE(break_editor_viewport3d_request_shader_reload(fx->vp));
    break_editor_shell_tick(fx->shell);
    editor_rhi_fake_stats(&fake);
    ASSERT_EQ(fake.pipeline_creates, 1u);
    break_runtime_test_reload_set_gates(0u, 0u);
    HR_WAIT(fx->shell, shader_reload_stats(fx).reloads == 2u);
    stats = shader_reload_stats(fx);
    ASSERT_EQ(stats.reloads, 2u);
    ASSERT_TRUE(stats.attempts >= 2u);
    ASSERT_FALSE(stats.busy);
    ASSERT_EQ(shader_reload_revision(fx), 3u);
    shader_reload_assert_stage_revisions(fx, 3u, 3u);
    editor_rhi_fake_stats(&fake);
    ASSERT_EQ(fake.buffer_creates, 1u);
}

TEST(shader_reload_worker_stages_off_rhi_and_trailing_uses_latest)
{
    EditorShaderEnv env;
    ShaderReloadFixture fx;
    ASSERT_TRUE(shader_env_save(&env));
    editor_rhi_fake_reset();
    editor_rhi_fake_set_enabled(true);
    memset(&fx, 0, sizeof(fx));
    shader_reload_trailing_body(&fx);
    break_runtime_test_reload_set_gates(0u, 0u);
    shader_reload_fixture_close(&fx);
    editor_rhi_fake_set_enabled(false);
    editor_rhi_fake_reset();
    shader_env_restore(&env);
}

typedef struct ShaderDirectFixture {
    ShaderReloadFixture base;
    BreakEditorShaderSource source;
    BreakEditorShaderReload *reload;
    bool reload_in_viewport;
} ShaderDirectFixture;

static bool shader_direct_apply(void *user, const void *vert, usize vert_size,
                                const void *frag, usize frag_size) {
    ShaderDirectFixture *fx = (ShaderDirectFixture *)user;
    return break_editor_viewport3d_reload_shader_source(
        fx->base.vp, vert, vert_size, frag, frag_size);
}

static void shader_direct_open_pair(ShaderDirectFixture *fx, const char *name,
                                    const char *initial_vert,
                                    const char *initial_frag) {
    size_t root_len;
    memset(fx, 0, sizeof(*fx));
    shader_reload_fixture_open(&fx->base, name, initial_vert, initial_frag);
    ASSERT_NOT_NULL(fx->base.shell);
    ASSERT_TRUE(break_editor_shader_source_configure(
        &fx->source, RHI_SHADER_VARIANT_GLSL));
    root_len = strlen(fx->base.root);
    ASSERT_TRUE(root_len < sizeof(fx->source.roots[0]));
    fx->source.root_count = 1u;
    memcpy(fx->source.roots[0], fx->base.root, root_len + 1u);
    fx->reload = break_editor_shader_reload_create(
        &fx->source, shader_direct_apply, fx);
    ASSERT_NOT_NULL(fx->reload);
}

static void shader_direct_open(ShaderDirectFixture *fx, const char *name) {
    shader_direct_open_pair(fx, name, "REV=1 vertex\n", "REV=1 fragment\n");
}

static void shader_direct_close(ShaderDirectFixture *fx) {
    if (fx->reload != NULL) {
        break_editor_shader_reload_set_shutdown_timeout_for_test(fx->reload,
                                                                 2000u);
        if (!fx->reload_in_viewport) {
            break_editor_shader_reload_destroy(fx->reload);
        }
        fx->reload = NULL;
    }
    shader_reload_fixture_close(&fx->base);
}

static BreakEditorShaderReloadStats shader_direct_stats(
    const ShaderDirectFixture *fx) {
    BreakEditorShaderReloadStats stats;
    memset(&stats, 0, sizeof(stats));
    (void)break_editor_shader_reload_stats(fx->reload, &stats);
    return stats;
}

#define SHADER_DIRECT_WAIT(fx_, cond_)                                       \
    do {                                                                     \
        int shader_i_;                                                       \
        for (shader_i_ = 0; shader_i_ < 3000 && !(cond_); shader_i_++) {     \
            break_editor_shader_reload_tick((fx_)->reload);                  \
            time_sleep_us(2000u);                                            \
        }                                                                    \
    } while (0)

typedef struct ShaderPromotionFixture {
    ShaderDirectFixture direct;
    char root[512];
    char shaders[600];
    char vert[700];
    char frag[700];
} ShaderPromotionFixture;

static void shader_promotion_open(ShaderPromotionFixture *fx) {
    size_t high_len, low_len;
    memset(fx, 0, sizeof(*fx));
    shader_direct_open_pair(&fx->direct, "editor_shader_reload_two_root_low",
                            "REV=1 vertex\n", "REV=2 fragment\n");
    ASSERT_NOT_NULL(fx->direct.base.shell);
    test_tmp(fx->root, sizeof(fx->root), "editor_shader_reload_two_root_high");
    snprintf(fx->shaders, sizeof(fx->shaders), "%s/shaders", fx->root);
    snprintf(fx->vert, sizeof(fx->vert), "%s/editor_color.vert", fx->shaders);
    snprintf(fx->frag, sizeof(fx->frag), "%s/editor_color.frag", fx->shaders);
    ASSERT_EQ(TEST_MKDIR(fx->root), 0);
    ASSERT_EQ(TEST_MKDIR(fx->shaders), 0);
    break_editor_shader_reload_destroy(fx->direct.reload);
    fx->direct.reload = NULL;
    high_len = strlen(fx->root);
    low_len = strlen(fx->direct.base.root);
    ASSERT_TRUE(high_len < sizeof(fx->direct.source.roots[0]));
    ASSERT_TRUE(low_len < sizeof(fx->direct.source.roots[1]));
    fx->direct.source.root_count = 2u;
    memcpy(fx->direct.source.roots[0], fx->root, high_len + 1u);
    memcpy(fx->direct.source.roots[1], fx->direct.base.root, low_len + 1u);
    fx->direct.reload = break_editor_shader_reload_create(
        &fx->direct.source, shader_direct_apply, &fx->direct);
    ASSERT_NOT_NULL(fx->direct.reload);
}

static void shader_promotion_close(ShaderPromotionFixture *fx) {
    shader_direct_close(&fx->direct);
    remove(fx->vert);
    remove(fx->frag);
    if (fx->shaders[0] != '\0') {
        TEST_RMDIR(fx->shaders);
    }
    if (fx->root[0] != '\0') {
        TEST_RMDIR(fx->root);
    }
}

static void shader_reload_two_root_body(ShaderPromotionFixture *fx) {
    BreakEditorShaderReloadStats stats;
    shader_promotion_open(fx);
    ASSERT_NOT_NULL(fx->direct.reload);
    stats = shader_direct_stats(&fx->direct);
    ASSERT_TRUE(stats.watching);
    ASSERT_EQ(stats.attempts, 0u);
    ASSERT_EQ(shader_reload_revision(&fx->direct.base), 1u);

    shader_reload_assert_stage_revisions(&fx->direct.base, 1u, 2u);

    /* the higher-priority pair appears: the watcher promotes both stages */
    hr_write_text(fx->vert, "REV=4 vertex\n");
    hr_write_text(fx->frag, "REV=3 fragment\n");
    hr_bump_mtime(fx->vert);
    hr_bump_mtime(fx->frag);
    SHADER_DIRECT_WAIT(&fx->direct,
                       shader_direct_stats(&fx->direct).reloads >= 1u &&
                           !shader_direct_stats(&fx->direct).busy);
    stats = shader_direct_stats(&fx->direct);
    ASSERT_TRUE(stats.events >= 1u);
    ASSERT_EQ(stats.failed, 0u);
    ASSERT_FALSE(stats.busy);
    shader_reload_assert_stage_revisions(&fx->direct.base, 4u, 3u);

    /* deleting it alone (no manual request) falls back to the lower root */
    {
        u64 events_before = stats.events;
        u64 reloads_before = stats.reloads;
        ASSERT_EQ(remove(fx->vert), 0);
        ASSERT_EQ(remove(fx->frag), 0);
        SHADER_DIRECT_WAIT(&fx->direct,
                           shader_direct_stats(&fx->direct).reloads >
                                   reloads_before &&
                               !shader_direct_stats(&fx->direct).busy);
        stats = shader_direct_stats(&fx->direct);
        ASSERT_TRUE(stats.events > events_before);
        ASSERT_EQ(stats.failed, 0u);
        ASSERT_FALSE(stats.busy);
        shader_reload_assert_stage_revisions(&fx->direct.base, 1u, 2u);
    }
}

TEST(shader_reload_two_root_watch_promotes_and_delete_falls_back)
{
    EditorShaderEnv env;
    ShaderPromotionFixture fx;
    ASSERT_TRUE(shader_env_save(&env));
    editor_rhi_fake_reset();
    editor_rhi_fake_set_enabled(true);
    memset(&fx, 0, sizeof(fx));
    shader_reload_two_root_body(&fx);
    break_runtime_test_reload_set_gates(0u, 0u);
    shader_promotion_close(&fx);
    editor_rhi_fake_set_enabled(false);
    editor_rhi_fake_reset();
    shader_env_restore(&env);
}

static void shader_reload_one_sided_body(ShaderDirectFixture *fx) {
    BreakEditorViewport3DGpuState before, after;
    EditorRhiFakeStats fake;
    shader_direct_open(fx, "editor_shader_reload_one_sided");
    ASSERT_NOT_NULL(fx->reload);
    break_editor_viewport3d_gpu_state_for_test(fx->base.vp, &before);
    ASSERT_EQ(remove(fx->base.frag), 0);
    ASSERT_TRUE(break_editor_shader_reload_request(fx->reload));
    SHADER_DIRECT_WAIT(fx, shader_direct_stats(fx).failed == 1u);
    ASSERT_EQ(shader_direct_stats(fx).attempts, 1u);
    ASSERT_EQ(shader_direct_stats(fx).failed, 1u);
    break_editor_viewport3d_gpu_state_for_test(fx->base.vp, &after);
    ASSERT_TRUE(viewport_gpu_state_equal(&before, &after));
    editor_rhi_fake_stats(&fake);
    ASSERT_EQ(fake.pipeline_creates, 1u);

    /* the delete above is itself a watcher event (opt-in missing notify), so
     * an automatic attempt may also run; pin the outcome, not the count */
    shader_reload_write_pair(&fx->base, 2u, "", false);
    ASSERT_TRUE(break_editor_shader_reload_request(fx->reload));
    SHADER_DIRECT_WAIT(fx, shader_direct_stats(fx).reloads >= 1u &&
                               !shader_direct_stats(fx).busy);
    ASSERT_TRUE(shader_direct_stats(fx).attempts >= 2u);
    ASSERT_TRUE(shader_direct_stats(fx).reloads >= 1u);
    ASSERT_EQ(shader_direct_stats(fx).last_result,
              BREAK_EDITOR_SHADER_RELOAD_APPLIED);
    shader_reload_assert_stage_revisions(&fx->base, 2u, 2u);
}

TEST(shader_reload_one_sided_failure_preserves_pipeline)
{
    EditorShaderEnv env;
    ShaderDirectFixture fx;
    ASSERT_TRUE(shader_env_save(&env));
    editor_rhi_fake_reset();
    editor_rhi_fake_set_enabled(true);
    memset(&fx, 0, sizeof(fx));
    shader_reload_one_sided_body(&fx);
    break_runtime_test_reload_set_gates(0u, 0u);
    shader_direct_close(&fx);
    editor_rhi_fake_set_enabled(false);
    editor_rhi_fake_reset();
    shader_env_restore(&env);
}

static void shader_reload_second_admission_body(ShaderDirectFixture *fx) {
    char fragment_path[96];
    u32 i;
    shader_direct_open(fx, "editor_shader_reload_second_admission");
    ASSERT_NOT_NULL(fx->reload);
    memcpy(fragment_path, fx->source.logical[BREAK_EDITOR_SHADER_FRAGMENT],
           sizeof(fragment_path));
    fx->source.logical[BREAK_EDITOR_SHADER_FRAGMENT][0] = '\0';
    for (i = 1u; i <= 8u; i++) {
        BreakEditorShaderReloadStats stats;
        u32 settle;
        ASSERT_TRUE(break_editor_shader_reload_request(fx->reload));
        break_editor_shader_reload_tick(fx->reload);
        SHADER_DIRECT_WAIT(fx, shader_direct_stats(fx).failed == i);
        stats = shader_direct_stats(fx);
        ASSERT_EQ(stats.attempts, i);
        ASSERT_EQ(stats.failed, i);
        ASSERT_FALSE(stats.busy);
        for (settle = 0u; settle < 4u; settle++) {
            break_editor_shader_reload_tick(fx->reload);
            time_sleep_us(2000u);
        }
        stats = shader_direct_stats(fx);
        ASSERT_EQ(stats.attempts, i);
        ASSERT_EQ(stats.failed, i);
        ASSERT_FALSE(stats.busy);
    }
    memcpy(fx->source.logical[BREAK_EDITOR_SHADER_FRAGMENT], fragment_path,
           sizeof(fragment_path));
    ASSERT_TRUE(break_editor_shader_reload_request(fx->reload));
    SHADER_DIRECT_WAIT(fx, shader_direct_stats(fx).reloads == 1u);
    {
        /* ASSERT_EQ prints only the expression; keep the counters in the log
         * so a CI-only failure of this case can be diagnosed. */
        BreakEditorShaderReloadStats final_stats = shader_direct_stats(fx);
        if (final_stats.attempts != 9u || final_stats.failed != 8u) {
            printf("  second_admission final: attempts=%llu reloads=%llu failed=%llu busy=%d last_result=%d events=%llu\n",
                   (unsigned long long)final_stats.attempts,
                   (unsigned long long)final_stats.reloads,
                   (unsigned long long)final_stats.failed,
                   (int)final_stats.busy, (int)final_stats.last_result,
                   (unsigned long long)final_stats.events);
        }
    }
    ASSERT_EQ(shader_direct_stats(fx).attempts, 9u);
    ASSERT_EQ(shader_direct_stats(fx).failed, 8u);
    ASSERT_EQ(shader_reload_revision(&fx->base), 1u);
}

/* Deterministic form of the CI-only failure of the case below. An attempt
 * whose fragment admission fails cancels the vertex request; if the worker
 * already published that request's commit command, the command stays in the
 * bounded owner queue (capacity 4) until the owner pump reclaims it. The pump
 * used to run only while an attempt was active, so dead commands from
 * back-to-back failed attempts were never reclaimed and the next valid reload
 * was rejected as a commit overload. The seam lets the worker reach the
 * commit publish between the two admissions (what a preempted owner thread
 * does on a loaded CI runner). */
static void shader_dead_commit_let_worker_run(void *user) {
    (void)user;
    time_sleep_us(30000u);
}

static void shader_reload_dead_commit_body(ShaderDirectFixture *fx) {
    char fragment_path[96];
    u32 i;
    shader_direct_open(fx, "editor_shader_reload_dead_commit");
    ASSERT_NOT_NULL(fx->reload);
    memcpy(fragment_path, fx->source.logical[BREAK_EDITOR_SHADER_FRAGMENT],
           sizeof(fragment_path));
    fx->source.logical[BREAK_EDITOR_SHADER_FRAGMENT][0] = '\0';
    break_editor_shader_reload_set_between_requests_for_test(
        fx->reload, shader_dead_commit_let_worker_run, NULL);
    for (i = 1u; i <= 6u; i++) {
        ASSERT_TRUE(break_editor_shader_reload_request(fx->reload));
        break_editor_shader_reload_tick(fx->reload); /* fails at once */
        ASSERT_EQ(shader_direct_stats(fx).failed, i);
        ASSERT_FALSE(shader_direct_stats(fx).busy);
    }
    break_editor_shader_reload_set_between_requests_for_test(fx->reload, NULL,
                                                             NULL);
    memcpy(fx->source.logical[BREAK_EDITOR_SHADER_FRAGMENT], fragment_path,
           sizeof(fragment_path));
    ASSERT_TRUE(break_editor_shader_reload_request(fx->reload));
    SHADER_DIRECT_WAIT(fx, !shader_direct_stats(fx).busy &&
                               shader_direct_stats(fx).attempts == 7u);
    ASSERT_EQ(shader_direct_stats(fx).reloads, 1u);
    ASSERT_EQ(shader_direct_stats(fx).failed, 6u);
    ASSERT_EQ(shader_reload_revision(&fx->base), 1u);
}

TEST(shader_reload_dead_commit_commands_do_not_block_next_reload)
{
    EditorShaderEnv env;
    ShaderDirectFixture fx;
    ASSERT_TRUE(shader_env_save(&env));
    editor_rhi_fake_reset();
    editor_rhi_fake_set_enabled(true);
    memset(&fx, 0, sizeof(fx));
    shader_reload_dead_commit_body(&fx);
    break_runtime_test_reload_set_gates(0u, 0u);
    shader_direct_close(&fx);
    editor_rhi_fake_set_enabled(false);
    editor_rhi_fake_reset();
    shader_env_restore(&env);
}

TEST(shader_reload_second_request_admission_failure_recovers)
{
    EditorShaderEnv env;
    ShaderDirectFixture fx;
    ASSERT_TRUE(shader_env_save(&env));
    editor_rhi_fake_reset();
    editor_rhi_fake_set_enabled(true);
    memset(&fx, 0, sizeof(fx));
    shader_reload_second_admission_body(&fx);
    break_runtime_test_reload_set_gates(0u, 0u);
    shader_direct_close(&fx);
    editor_rhi_fake_set_enabled(false);
    editor_rhi_fake_reset();
    shader_env_restore(&env);
}

static void shader_direct_recreate_without_watch(ShaderDirectFixture *fx) {
    ASSERT_NOT_NULL(fx->reload);
    memset(fx->source.roots[0], 'x', 240u);
    fx->source.roots[0][240] = '\0';
    break_editor_shader_reload_destroy(fx->reload);
    fx->reload = break_editor_shader_reload_create(
        &fx->source, shader_direct_apply, fx);
    ASSERT_NOT_NULL(fx->reload);
}

static void shader_reload_watch_unavailable_body(ShaderDirectFixture *fx) {
    BreakEditorShaderReloadStats stats;
    EditorRhiFakeStats fake;
    shader_direct_open(fx, "editor_shader_reload_no_watch");
    shader_direct_recreate_without_watch(fx);
    stats = shader_direct_stats(fx);
    ASSERT_FALSE(stats.watching);
    ASSERT_EQ(stats.last_result, BREAK_EDITOR_SHADER_RELOAD_UNAVAILABLE);
    ASSERT_TRUE(break_editor_shader_reload_request(fx->reload));
    SHADER_DIRECT_WAIT(fx, shader_direct_stats(fx).failed == 1u);
    stats = shader_direct_stats(fx);
    ASSERT_EQ(stats.attempts, 1u);
    ASSERT_EQ(stats.failed, 1u);
    ASSERT_FALSE(stats.busy);
    editor_rhi_fake_stats(&fake);
    ASSERT_EQ(fake.pipeline_creates, 1u);
    ASSERT_EQ(shader_reload_revision(&fx->base), 1u);
}

TEST(shader_reload_manual_request_survives_watch_unavailable)
{
    EditorShaderEnv env;
    ShaderDirectFixture fx;
    ASSERT_TRUE(shader_env_save(&env));
    editor_rhi_fake_reset();
    editor_rhi_fake_set_enabled(true);
    memset(&fx, 0, sizeof(fx));
    shader_reload_watch_unavailable_body(&fx);
    break_runtime_test_reload_set_gates(0u, 0u);
    shader_direct_close(&fx);
    editor_rhi_fake_set_enabled(false);
    editor_rhi_fake_reset();
    shader_env_restore(&env);
}

static void shader_reload_manual_only_diagnostic_body(ShaderDirectFixture *fx) {
    BreakEditorShaderReloadStats stats;
    u64 popped;
    shader_direct_open(fx, "editor_shader_reload_manual_only_panel");
    shader_direct_recreate_without_watch(fx);
    stats = shader_direct_stats(fx);
    ASSERT_FALSE(stats.watching);
    ASSERT_EQ(stats.attempts, 0u);
    ASSERT_TRUE(break_editor_viewport3d_replace_shader_reload_for_test(
        fx->base.vp, fx->reload));
    fx->reload_in_viewport = true;
    g_render_clock_us = UINT64_C(3000000);
    break_editor_shell_set_render_clock_for_test(fx->base.shell,
                                                  render_test_clock, NULL);
    break_editor_shell_tick(fx->base.shell);
    ASSERT_STR_EQ(break_editor_shell_render_row_text(fx->base.shell, 8u),
                  "shader reload: manual-only busy=0 applied=0 failed=0");

    popped = atomic_load_explicit(&g_break_runtime_test_reload_popped,
                                  memory_order_acquire);
    break_runtime_test_reload_set_gates(0u, 1u);
    ASSERT_TRUE(break_editor_viewport3d_request_shader_reload(fx->base.vp));
    break_editor_shell_tick(fx->base.shell);
    HR_WAIT(fx->base.shell,
            atomic_load_explicit(&g_break_runtime_test_reload_popped,
                                 memory_order_acquire) > popped);
    stats = shader_direct_stats(fx);
    ASSERT_FALSE(stats.watching);
    ASSERT_TRUE(stats.busy);
    ASSERT_EQ(stats.attempts, 1u);
    g_render_clock_us += UINT64_C(250000);
    break_editor_shell_tick(fx->base.shell);
    ASSERT_STR_EQ(break_editor_shell_render_row_text(fx->base.shell, 8u),
                  "shader reload: manual-only busy=1 applied=0 failed=0");

    break_runtime_test_reload_set_gates(0u, 0u);
    HR_WAIT(fx->base.shell, shader_direct_stats(fx).failed == 1u);
    stats = shader_direct_stats(fx);
    ASSERT_FALSE(stats.watching);
    ASSERT_FALSE(stats.busy);
    ASSERT_EQ(stats.attempts, 1u);
    ASSERT_EQ(stats.reloads, 0u);
    ASSERT_EQ(stats.failed, 1u);
    g_render_clock_us += UINT64_C(250000);
    break_editor_shell_tick(fx->base.shell);
    ASSERT_STR_EQ(break_editor_shell_render_row_text(fx->base.shell, 8u),
                  "shader reload: manual-only busy=0 applied=0 failed=1");
}

TEST(shader_reload_manual_only_diagnostic_keeps_busy_and_counts)
{
    EditorShaderEnv env;
    ShaderDirectFixture fx;
    ASSERT_TRUE(shader_env_save(&env));
    editor_rhi_fake_reset();
    editor_rhi_fake_set_enabled(true);
    memset(&fx, 0, sizeof(fx));
    shader_reload_manual_only_diagnostic_body(&fx);
    break_runtime_test_reload_set_gates(0u, 0u);
    shader_direct_close(&fx);
    editor_rhi_fake_set_enabled(false);
    editor_rhi_fake_reset();
    shader_env_restore(&env);
}

static void shader_reload_claim_teardown_body(ShaderReloadFixture *fx) {
    EditorRhiFakeStats fake;
    shader_reload_fixture_open(fx, "editor_shader_reload_claim_stop",
                               "REV=1 vertex\n", "REV=1 fragment\n");
    ASSERT_NOT_NULL(fx->shell);
    break_runtime_test_reload_set_gates(1u, 0u);
    ASSERT_TRUE(break_editor_viewport3d_request_shader_reload(fx->vp));
    break_editor_shell_tick(fx->shell);
    ASSERT_TRUE(shader_reload_stats(fx).busy);
    ASSERT_EQ(shader_reload_stats(fx).attempts, 1u);
    shader_reload_fixture_close(fx);
    editor_rhi_fake_stats(&fake);
    ASSERT_EQ(fake.live_shaders, 0u);
    ASSERT_EQ(fake.live_pipelines, 0u);
    ASSERT_EQ(fake.live_bindings, 0u);
    ASSERT_EQ(fake.live_buffers, 0u);
}

TEST(shader_reload_inflight_claim_teardown_is_bounded)
{
    EditorShaderEnv env;
    ShaderReloadFixture fx;
    ASSERT_TRUE(shader_env_save(&env));
    editor_rhi_fake_reset();
    editor_rhi_fake_set_enabled(true);
    memset(&fx, 0, sizeof(fx));
    shader_reload_claim_teardown_body(&fx);
    break_runtime_test_reload_set_gates(0u, 0u);
    shader_reload_fixture_close(&fx);
    editor_rhi_fake_set_enabled(false);
    editor_rhi_fake_reset();
    shader_env_restore(&env);
}

static void shader_reload_shutdown_retry_body(ShaderDirectFixture *fx) {
    u64 popped;
    shader_direct_open(fx, "editor_shader_reload_stop_retry");
    ASSERT_NOT_NULL(fx->reload);
    popped = atomic_load_explicit(&g_break_runtime_test_reload_popped,
                                  memory_order_acquire);
    break_runtime_test_reload_set_gates(0u, 1u);
    ASSERT_TRUE(break_editor_shader_reload_request(fx->reload));
    break_editor_shader_reload_tick(fx->reload);
    SHADER_DIRECT_WAIT(fx,
        atomic_load_explicit(&g_break_runtime_test_reload_popped,
                             memory_order_acquire) > popped);
    break_editor_shader_reload_set_shutdown_timeout_for_test(fx->reload, 0u);
    ASSERT_FALSE(break_editor_shader_reload_shutdown(fx->reload));
    break_runtime_test_reload_set_gates(0u, 0u);
    break_editor_shader_reload_set_shutdown_timeout_for_test(fx->reload,
                                                             2000u);
    ASSERT_TRUE(break_editor_shader_reload_shutdown(fx->reload));
    break_editor_shader_reload_destroy(fx->reload);
    fx->reload = NULL;
    ASSERT_EQ(shader_reload_revision(&fx->base), 1u);
}

TEST(shader_reload_shutdown_timeout_can_retry)
{
    EditorShaderEnv env;
    ShaderDirectFixture fx;
    ASSERT_TRUE(shader_env_save(&env));
    editor_rhi_fake_reset();
    editor_rhi_fake_set_enabled(true);
    memset(&fx, 0, sizeof(fx));
    shader_reload_shutdown_retry_body(&fx);
    break_runtime_test_reload_set_gates(0u, 0u);
    shader_direct_close(&fx);
    editor_rhi_fake_set_enabled(false);
    editor_rhi_fake_reset();
    shader_env_restore(&env);
}

static void shader_reload_shell_timeout_retry_body(ShaderReloadFixture *fx) {
    BreakEditorShell *shell;
    BreakEditorViewport3D *vp;
    BreakEditorDoc *doc;
    BreakEditorShaderReloadStats stats;
    EditorRhiFakeStats fake;
    u64 popped;
    shader_reload_fixture_open(fx, "editor_shader_reload_shell_stop_retry",
                               "REV=1 vertex\n", "REV=1 fragment\n");
    ASSERT_NOT_NULL(fx->shell);
    shell = fx->shell;
    vp = fx->vp;
    doc = break_editor_shell_doc(shell);
    popped = atomic_load_explicit(&g_break_runtime_test_reload_popped,
                                  memory_order_acquire);
    break_runtime_test_reload_set_gates(0u, 1u);
    ASSERT_TRUE(break_editor_viewport3d_request_shader_reload(vp));
    break_editor_shell_tick(shell);
    HR_WAIT(shell,
            atomic_load_explicit(&g_break_runtime_test_reload_popped,
                                 memory_order_acquire) > popped);
    break_editor_viewport3d_set_shader_reload_shutdown_timeout_for_test(vp, 0u);
    break_editor_shell_set_render_device(shell, NULL);

    ASSERT_FALSE(break_editor_viewport3d_destroy(vp));
    ASSERT_TRUE(break_editor_shell_viewport3d(shell) == vp);
    ASSERT_FALSE(break_editor_shell_destroy(shell));
    ASSERT_TRUE(fx->shell == shell);
    ASSERT_TRUE(fx->vp == vp);
    ASSERT_TRUE(break_editor_shell_viewport3d(shell) == vp);
    ASSERT_TRUE(break_editor_shell_doc(shell) == doc);
    ASSERT_EQ(shader_reload_revision(fx), 1u);
    editor_rhi_fake_stats(&fake);
    ASSERT_EQ(fake.live_pipelines, 1u);
    ASSERT_EQ(fake.live_bindings, 1u);
    ASSERT_EQ(fake.live_buffers, 1u);
    stats = shader_reload_stats(fx);
    ASSERT_EQ(stats.last_result, BREAK_EDITOR_SHADER_RELOAD_UNAVAILABLE);
    ASSERT_FALSE(stats.busy);
    ASSERT_FALSE(break_editor_viewport3d_request_shader_reload(vp));
    break_editor_shell_set_render_device(shell, (RHIDevice *)&fx->device);
    break_editor_shell_tick(shell);
    ASSERT_STR_EQ(break_editor_shell_render_row_text(shell, 8u),
                  "shader reload: shutdown-pending busy=0 applied=0 failed=0");
    break_editor_shell_set_render_device(shell, NULL);
    memset(&fx->log, 0, sizeof(fx->log));
    break_editor_viewport3d_set_shader_reload_logger(
        vp, shader_reload_capture_log, &fx->log);
    ASSERT_TRUE(fx->log.calls == 0u ||
                strstr(fx->log.last, "manual reload remains available") == NULL);
    break_editor_shell_tick(shell);

    break_runtime_test_reload_set_gates(0u, 0u);
    break_editor_viewport3d_set_shader_reload_shutdown_timeout_for_test(
        vp, 2000u);
    ASSERT_TRUE(break_editor_shell_destroy(shell));
    fx->shell = NULL;
    fx->vp = NULL;
    editor_rhi_fake_stats(&fake);
    ASSERT_EQ(fake.live_shaders, 0u);
    ASSERT_EQ(fake.live_pipelines, 0u);
    ASSERT_EQ(fake.live_bindings, 0u);
    ASSERT_EQ(fake.live_buffers, 0u);
}

TEST(shader_reload_viewport_and_shell_shutdown_retry_same_owner)
{
    EditorShaderEnv env;
    ShaderReloadFixture fx;
    ASSERT_TRUE(shader_env_save(&env));
    editor_rhi_fake_reset();
    editor_rhi_fake_set_enabled(true);
    memset(&fx, 0, sizeof(fx));
    shader_reload_shell_timeout_retry_body(&fx);
    break_runtime_test_reload_set_gates(0u, 0u);
    if (fx.vp != NULL) {
        break_editor_viewport3d_set_shader_reload_shutdown_timeout_for_test(
            fx.vp, 2000u);
    }
    shader_reload_fixture_close(&fx);
    editor_rhi_fake_set_enabled(false);
    editor_rhi_fake_reset();
    shader_env_restore(&env);
}

TEST(shader_reload_shortcut_without_owner_is_bounded)
{
    BreakEditorShell *shell = break_editor_shell_create_for_test();
    BreakEditorViewport3D *vp;
    BreakEditorShaderReloadStats stats;
    ASSERT_NOT_NULL(shell);
    vp = break_editor_shell_viewport3d(shell);
    ASSERT_NOT_NULL(vp);
    ASSERT_TRUE(break_editor_viewport3d_shader_reload_stats(vp, &stats));
    ASSERT_EQ(stats.last_result, BREAK_EDITOR_SHADER_RELOAD_UNAVAILABLE);
    ASSERT_EQ(stats.attempts, 0u);
    ASSERT_FALSE(stats.busy);

    ASSERT_TRUE(break_editor_shell_dispatch_key(
        shell, 'r', MY_KEYMOD_CTRL | MY_KEYMOD_SHIFT));
    ASSERT_STR_EQ(last_console_line(break_editor_shell_console_text(shell)),
                  "shader reload: unavailable\n");
    ASSERT_STR_EQ(break_editor_shell_tool_text(shell), "Tool: Select");
    break_editor_shell_tick(shell);
    ASSERT_TRUE(break_editor_viewport3d_shader_reload_stats(vp, &stats));
    ASSERT_EQ(stats.attempts, 0u);
    ASSERT_EQ(stats.reloads, 0u);
    ASSERT_EQ(stats.failed, 0u);
    ASSERT_FALSE(stats.busy);
    ASSERT_FALSE(break_editor_shell_dispatch_key(
        NULL, 'r', MY_KEYMOD_CTRL | MY_KEYMOD_SHIFT));
    break_editor_shell_destroy(shell);
}

TEST(shader_reload_unavailable_stats_and_null_calls)
{
    BreakEditorViewport3D *vp = break_editor_viewport3d_create();
    BreakEditorShaderReloadStats stats;
    ASSERT_NOT_NULL(vp);
    ASSERT_TRUE(break_editor_viewport3d_shader_reload_stats(vp, &stats));
    ASSERT_FALSE(stats.watching);
    ASSERT_FALSE(stats.busy);
    ASSERT_EQ(stats.last_result, BREAK_EDITOR_SHADER_RELOAD_UNAVAILABLE);
    ASSERT_EQ(stats.attempts, 0u);
    ASSERT_FALSE(break_editor_viewport3d_request_shader_reload(vp));
    break_editor_viewport3d_tick(vp);
    break_editor_viewport3d_set_shader_reload_logger(vp, NULL, NULL);
    break_editor_viewport3d_tick(NULL);
    ASSERT_FALSE(break_editor_viewport3d_request_shader_reload(NULL));
    ASSERT_FALSE(break_editor_viewport3d_shader_reload_stats(NULL, &stats));
    ASSERT_FALSE(break_editor_viewport3d_shader_reload_stats(vp, NULL));
    break_editor_viewport3d_destroy(vp);
}

typedef struct HrFixture {
    BreakEditorShell *shell;
    BreakEditorHotReload *hr;
    BreakEditorDoc *doc;
    char dir[512];
    char scene[600];
    char sidecar[700];
} HrFixture;

static BreakEditorHotReloadStats hr_stats(const HrFixture *fx) {
    BreakEditorHotReloadStats st;
    memset(&st, 0, sizeof(st));
    (void)break_editor_hot_reload_stats(fx->hr, &st);
    return st;
}

/* Opens a shell with a hot-reload host watching <dir>/scene.bscn. When
 * `file_entities` > 0 the scene file exists first and is loaded into the
 * document (clean), so the watcher baseline matches the document. */
static void hr_open(HrFixture *fx, const char *name, u32 file_entities) {
    memset(fx, 0, sizeof(*fx));
    test_tmp(fx->dir, sizeof(fx->dir), name);
    TEST_MKDIR(fx->dir);
    snprintf(fx->scene, sizeof(fx->scene), "%s/scene.bscn", fx->dir);
    snprintf(fx->sidecar, sizeof(fx->sidecar), "%s" BREAK_EDITOR_SIDECAR_SUFFIX,
             fx->scene);
    fx->shell = break_editor_shell_create_for_test();
    ASSERT_NOT_NULL(fx->shell);
    fx->doc = break_editor_shell_doc(fx->shell);
    if (file_entities > 0u) {
        save_fixture_scene(fx->scene, file_entities);
        ASSERT_TRUE(break_editor_doc_load(fx->doc, fx->scene));
        break_editor_shell_refresh(fx->shell);
        ASSERT_FALSE(break_editor_doc_is_dirty(fx->doc));
    }
    fx->hr = break_editor_hot_reload_create(fx->shell);
    ASSERT_NOT_NULL(fx->hr);
    break_editor_shell_set_hot_reload(fx->shell, fx->hr);
    ASSERT_TRUE(break_editor_shell_set_scene_path(fx->shell, fx->scene));
}

static void hr_close(HrFixture *fx) {
    break_editor_shell_set_hot_reload(fx->shell, NULL);
    break_editor_hot_reload_destroy(fx->hr);
    break_editor_shell_destroy(fx->shell);
    remove(fx->scene);
    remove(fx->sidecar);
    TEST_RMDIR(fx->dir);
}

TEST(hot_reload_valid_external_edit_replaces_document)
{
    HrFixture fx;
    BreakEditorHotReloadStats st;
    hr_open(&fx, "editor_hr_valid", 1u);
    st = hr_stats(&fx);
    ASSERT_TRUE(st.watching);
    ASSERT_EQ(break_editor_doc_entity_count(fx.doc), 1u);

    hr_external_scene(fx.scene, 3u);
    HR_WAIT(fx.shell, break_editor_doc_entity_count(fx.doc) == 3u);

    ASSERT_EQ(break_editor_doc_entity_count(fx.doc), 3u);
    ASSERT_EQ(break_editor_shell_outliner_count(fx.shell), 3u);
    st = hr_stats(&fx);
    ASSERT_EQ(st.reloads, 1u);
    ASSERT_EQ(st.failed, 0u);
    ASSERT_TRUE(strstr(break_editor_shell_console_text(fx.shell),
                       "hot reload") != NULL);
    hr_close(&fx);
}

TEST(hot_reload_creation_of_missing_scene_loads_it)
{
    HrFixture fx;
    hr_open(&fx, "editor_hr_create", 0u);
    ASSERT_TRUE(hr_stats(&fx).watching);
    ASSERT_EQ(break_editor_doc_entity_count(fx.doc), 0u);

    hr_external_scene(fx.scene, 2u);
    HR_WAIT(fx.shell, break_editor_doc_entity_count(fx.doc) == 2u);
    ASSERT_EQ(break_editor_doc_entity_count(fx.doc), 2u);
    ASSERT_EQ(hr_stats(&fx).reloads, 1u);
    hr_close(&fx);
}

TEST(hot_reload_invalid_external_edit_keeps_document_and_undo)
{
    HrFixture fx;
    BreakEditorHotReloadStats st;
    hr_open(&fx, "editor_hr_invalid", 2u);
    /* one undoable edit, saved so the document is clean again */
    emit_click(find(fx.shell, "editor-add-button"));
    ASSERT_EQ(break_editor_doc_entity_count(fx.doc), 3u);
    ASSERT_TRUE(break_editor_shell_dispatch_key(fx.shell, 's', MY_KEYMOD_CTRL));
    ASSERT_FALSE(break_editor_doc_is_dirty(fx.doc));
    ASSERT_EQ(break_editor_cmd_stack_undo_count(break_editor_doc_stack(fx.doc)),
              1u);

    hr_write_text(fx.scene, "this is not a scene");
    hr_bump_mtime(fx.scene);
    HR_WAIT(fx.shell, hr_stats(&fx).failed == 1u);

    st = hr_stats(&fx);
    ASSERT_EQ(st.failed, 1u);
    ASSERT_EQ(st.reloads, 0u);
    ASSERT_EQ(break_editor_doc_entity_count(fx.doc), 3u);
    ASSERT_EQ(break_editor_cmd_stack_undo_count(break_editor_doc_stack(fx.doc)),
              1u);
    ASSERT_TRUE(strstr(break_editor_shell_console_text(fx.shell),
                       "keeping current") != NULL);
    hr_close(&fx);
}

TEST(hot_reload_dirty_document_is_not_overwritten)
{
    HrFixture fx;
    BreakEditorHotReloadStats st;
    hr_open(&fx, "editor_hr_dirty", 2u);
    emit_click(find(fx.shell, "editor-add-button"));
    ASSERT_TRUE(break_editor_doc_is_dirty(fx.doc));
    ASSERT_EQ(break_editor_doc_entity_count(fx.doc), 3u);

    hr_external_scene(fx.scene, 5u);
    HR_WAIT(fx.shell, hr_stats(&fx).skipped_dirty == 1u);

    st = hr_stats(&fx);
    ASSERT_EQ(st.skipped_dirty, 1u);
    ASSERT_EQ(st.reloads, 0u);
    ASSERT_EQ(break_editor_doc_entity_count(fx.doc), 3u);
    ASSERT_TRUE(break_editor_doc_is_dirty(fx.doc));
    ASSERT_TRUE(strstr(break_editor_shell_console_text(fx.shell), "skipped") !=
                NULL);
    hr_close(&fx);
}

TEST(hot_reload_own_save_does_not_reload_or_erase_undo)
{
    HrFixture fx;
    BreakEditorHotReloadStats st;
    hr_open(&fx, "editor_hr_ownsave", 0u);
    emit_click(find(fx.shell, "editor-add-button"));
    ASSERT_TRUE(break_editor_shell_dispatch_key(fx.shell, 's', MY_KEYMOD_CTRL));
    ASSERT_TRUE(file_exists(fx.scene));
    hr_settle(fx.shell, 40);
    ASSERT_EQ(hr_stats(&fx).reloads, 0u);

    /* worst case: the filesystem reports a new mtime for the saved file; the
     * content hash proves it is our own bytes, so nothing is reloaded */
    hr_bump_mtime(fx.scene);
    HR_WAIT(fx.shell, hr_stats(&fx).skipped_same == 1u);
    st = hr_stats(&fx);
    ASSERT_EQ(st.skipped_same, 1u);
    ASSERT_EQ(st.reloads, 0u);
    ASSERT_EQ(break_editor_cmd_stack_undo_count(break_editor_doc_stack(fx.doc)),
              1u);
    ASSERT_EQ(break_editor_doc_entity_count(fx.doc), 1u);
    hr_close(&fx);
}

TEST(hot_reload_external_edit_after_local_save_still_reloads)
{
    HrFixture fx;
    hr_open(&fx, "editor_hr_after_save", 0u);
    /* the save replaces the file by rename, which retires the inotify watch;
     * the watcher must keep seeing later external edits */
    emit_click(find(fx.shell, "editor-add-button"));
    ASSERT_TRUE(break_editor_shell_dispatch_key(fx.shell, 's', MY_KEYMOD_CTRL));
    hr_settle(fx.shell, 20);
    ASSERT_EQ(hr_stats(&fx).reloads, 0u);

    hr_external_scene(fx.scene, 4u);
    HR_WAIT(fx.shell, break_editor_doc_entity_count(fx.doc) == 4u);
    ASSERT_EQ(break_editor_doc_entity_count(fx.doc), 4u);
    ASSERT_EQ(hr_stats(&fx).reloads, 1u);

    hr_external_scene(fx.scene, 2u);
    HR_WAIT(fx.shell, break_editor_doc_entity_count(fx.doc) == 2u);
    ASSERT_EQ(break_editor_doc_entity_count(fx.doc), 2u);
    ASSERT_EQ(hr_stats(&fx).reloads, 2u);
    hr_close(&fx);
}

TEST(hot_reload_scene_without_sidecar_keeps_following_external_edits)
{
    HrFixture fx;
    hr_open(&fx, "editor_hr_nosidecar", 0u);

    /* an external tool writes only the .bscn: the load generates names and
     * the document equals the file, so it must stay clean enough to follow
     * the next external edit */
    save_fixture_scene(fx.scene, 2u);
    remove(fx.sidecar);
    hr_bump_mtime(fx.scene);
    HR_WAIT(fx.shell, break_editor_doc_entity_count(fx.doc) == 2u);
    ASSERT_EQ(break_editor_doc_entity_count(fx.doc), 2u);
    /* names were generated (dirty flag), but there is no user history */
    ASSERT_EQ(break_editor_cmd_stack_size(break_editor_doc_stack(fx.doc)), 0u);

    save_fixture_scene(fx.scene, 5u);
    remove(fx.sidecar);
    hr_bump_mtime(fx.scene);
    HR_WAIT(fx.shell, break_editor_doc_entity_count(fx.doc) == 5u);
    ASSERT_EQ(break_editor_doc_entity_count(fx.doc), 5u);
    ASSERT_EQ(hr_stats(&fx).reloads, 2u);
    ASSERT_EQ(hr_stats(&fx).skipped_dirty, 0u);
    hr_close(&fx);
}

TEST(hot_reload_request_in_flight_during_save_is_dropped_as_stale)
{
    HrFixture fx;
    BreakEditorHotReloadStats st;
    hr_open(&fx, "editor_hr_stale", 2u);

    hr_external_scene(fx.scene, 4u);
    break_editor_shell_tick(fx.shell); /* detects the change, issues the request */
    ASSERT_EQ(hr_stats(&fx).requests, 1u);

    /* the user saves before the staged bytes are committed */
    emit_click(find(fx.shell, "editor-add-button"));
    ASSERT_TRUE(break_editor_shell_dispatch_key(fx.shell, 's', MY_KEYMOD_CTRL));

    HR_WAIT(fx.shell, hr_stats(&fx).skipped_stale == 1u);
    hr_settle(fx.shell, 20);
    st = hr_stats(&fx);
    ASSERT_EQ(st.skipped_stale, 1u);
    ASSERT_EQ(st.reloads, 0u);
    ASSERT_EQ(break_editor_doc_entity_count(fx.doc), 3u);
    ASSERT_FALSE(break_editor_doc_is_dirty(fx.doc));
    hr_close(&fx);
}

TEST(hot_reload_scene_switch_via_asset_browser_rewatches)
{
    BreakEditorShell *shell = break_editor_shell_create_for_test();
    BreakEditorHotReload *hr;
    BreakEditorDoc *doc;
    BreakEditorHotReloadStats st;
    char dir_a[512], dir_b[512], scene_a[600], scene_b[600];
    char side_a[700], side_b[700];
    my_widget_t *list;
    ASSERT_NOT_NULL(shell);
    test_tmp(dir_a, sizeof(dir_a), "editor_hr_switch_a");
    test_tmp(dir_b, sizeof(dir_b), "editor_hr_switch_b");
    TEST_MKDIR(dir_a);
    TEST_MKDIR(dir_b);
    snprintf(scene_a, sizeof(scene_a), "%s/a.bscn", dir_a);
    snprintf(scene_b, sizeof(scene_b), "%s/b.bscn", dir_b);
    snprintf(side_a, sizeof(side_a), "%s" BREAK_EDITOR_SIDECAR_SUFFIX, scene_a);
    snprintf(side_b, sizeof(side_b), "%s" BREAK_EDITOR_SIDECAR_SUFFIX, scene_b);
    save_fixture_scene(scene_a, 1u);
    save_fixture_scene(scene_b, 2u);
    doc = break_editor_shell_doc(shell);
    hr = break_editor_hot_reload_create(shell);
    ASSERT_NOT_NULL(hr);
    break_editor_shell_set_hot_reload(shell, hr);

    ASSERT_TRUE(break_editor_shell_set_assets_root(shell, dir_a));
    shell_paint(shell);
    list = find(shell, "editor-assets-list");
    ASSERT_NOT_NULL(list);
    emit_click(list_row_by_text(list, "a.bscn"));
    ASSERT_EQ(break_editor_doc_entity_count(doc), 1u);
    ASSERT_STR_EQ(break_editor_shell_scene_path(shell), scene_a);

    ASSERT_TRUE(break_editor_shell_set_assets_root(shell, dir_b));
    shell_paint(shell);
    list = find(shell, "editor-assets-list");
    ASSERT_NOT_NULL(list);
    emit_click(list_row_by_text(list, "b.bscn"));
    ASSERT_EQ(break_editor_doc_entity_count(doc), 2u);
    ASSERT_STR_EQ(break_editor_shell_scene_path(shell), scene_b);
    ASSERT_TRUE(break_editor_hot_reload_stats(hr, &st));
    ASSERT_TRUE(st.watching);

    /* the previous scene is no longer watched */
    hr_external_scene(scene_a, 6u);
    hr_settle(shell, 60);
    ASSERT_EQ(break_editor_doc_entity_count(doc), 2u);

    /* the new one is */
    hr_external_scene(scene_b, 4u);
    HR_WAIT(shell, break_editor_doc_entity_count(doc) == 4u);
    ASSERT_EQ(break_editor_doc_entity_count(doc), 4u);

    break_editor_shell_set_hot_reload(shell, NULL);
    break_editor_hot_reload_destroy(hr);
    break_editor_shell_destroy(shell);
    remove(scene_a);
    remove(side_a);
    remove(scene_b);
    remove(side_b);
    TEST_RMDIR(dir_a);
    TEST_RMDIR(dir_b);
}

static u64 g_assets_clock_us;
static u64 assets_clock(void *user) {
    (void)user;
    return g_assets_clock_us;
}

TEST(assets_panel_live_refresh_shows_external_create_and_delete)
{
    BreakEditorShell *shell = break_editor_shell_create_for_test();
    BreakEditorDoc *doc;
    char dir[512], f_a[600], f_b[600];
    my_widget_t *list;
    ASSERT_NOT_NULL(shell);
    test_tmp(dir, sizeof(dir), "editor_shell_assets_live");
    TEST_MKDIR(dir);
    snprintf(f_a, sizeof(f_a), "%s/a.txt", dir);
    snprintf(f_b, sizeof(f_b), "%s/b.txt", dir);
    hr_write_text(f_a, "a");
    doc = break_editor_shell_doc(shell);
    emit_click(find(shell, "editor-add-button"));
    ASSERT_TRUE(break_editor_doc_is_dirty(doc));

    g_assets_clock_us = 1000000u;
    break_editor_shell_set_assets_clock_for_test(shell, assets_clock, NULL);
    ASSERT_TRUE(break_editor_shell_set_assets_root(shell, dir));
    shell_paint(shell);
    ASSERT_EQ(break_editor_shell_assets_row_count(shell), 2u); /* ".." + a.txt */

    hr_write_text(f_b, "b");
    /* within the throttle interval nothing is re-listed */
    break_editor_shell_tick(shell);
    g_assets_clock_us += 500000u;
    break_editor_shell_tick(shell);
    ASSERT_EQ(break_editor_shell_assets_row_count(shell), 2u);

    g_assets_clock_us += 600000u; /* 1.1 s since the root was set */
    break_editor_shell_tick(shell);
    shell_paint(shell);
    ASSERT_EQ(break_editor_shell_assets_row_count(shell), 3u);
    list = find(shell, "editor-assets-list");
    ASSERT_NOT_NULL(list);
    ASSERT_NOT_NULL(list_row_by_text(list, "b.txt"));

    remove(f_a);
    g_assets_clock_us += 1100000u;
    break_editor_shell_tick(shell);
    shell_paint(shell);
    ASSERT_EQ(break_editor_shell_assets_row_count(shell), 2u);

    /* a directory-only change never touches the document */
    ASSERT_EQ(break_editor_doc_entity_count(doc), 1u);
    ASSERT_TRUE(break_editor_doc_is_dirty(doc));

    break_editor_shell_destroy(shell);
    remove(f_b);
    TEST_RMDIR(dir);
}

TEST(assets_panel_live_refresh_survives_vanished_directory)
{
    BreakEditorShell *shell = break_editor_shell_create_for_test();
    char dir[512], sub[600], keep[600];
    my_widget_t *list;
    ASSERT_NOT_NULL(shell);
    test_tmp(dir, sizeof(dir), "editor_shell_assets_gone");
    TEST_MKDIR(dir);
    snprintf(sub, sizeof(sub), "%s/sub", dir);
    snprintf(keep, sizeof(keep), "%s/keep.txt", dir);
    TEST_MKDIR(sub);
    hr_write_text(keep, "k");

    g_assets_clock_us = 5000000u;
    break_editor_shell_set_assets_clock_for_test(shell, assets_clock, NULL);
    ASSERT_TRUE(break_editor_shell_set_assets_root(shell, dir));
    shell_paint(shell);
    list = find(shell, "editor-assets-list");
    ASSERT_NOT_NULL(list);
    emit_click(list_row_by_text(list, "sub/"));
    ASSERT_TRUE(strstr(break_editor_shell_assets_path_text(shell), "/sub") !=
                NULL);

    break_editor_shell_tick(shell); /* the first tick only starts the interval */
    TEST_RMDIR(sub);
    g_assets_clock_us += 1100000u;
    break_editor_shell_tick(shell);
    shell_paint(shell);
    ASSERT_STR_EQ(break_editor_shell_assets_path_text(shell), "assets: /");
    ASSERT_EQ(break_editor_shell_assets_row_count(shell), 2u);

    break_editor_shell_destroy(shell);
    remove(keep);
    TEST_RMDIR(dir);
}

TEST(hot_reload_overlong_scene_path_disables_watch_without_truncating)
{
    BreakEditorShell *shell = break_editor_shell_create_for_test();
    BreakEditorHotReload *hr;
    BreakEditorHotReloadStats st;
    char path[400];
    usize used;
    ASSERT_NOT_NULL(shell);
    hr = break_editor_hot_reload_create(shell);
    ASSERT_NOT_NULL(hr);
    break_editor_shell_set_hot_reload(shell, hr);

    used = (usize)snprintf(path, sizeof(path), "/tmp/");
    memset(path + used, 'a', 300u);
    path[used + 300u] = '\0';
    strcat(path, ".bscn");
    /* the save target is still accepted (it has its own, larger bound) */
    ASSERT_TRUE(break_editor_shell_set_scene_path(shell, path));
    ASSERT_STR_EQ(break_editor_shell_scene_path(shell), path);
    ASSERT_TRUE(break_editor_hot_reload_stats(hr, &st));
    ASSERT_FALSE(st.watching);
    ASSERT_TRUE(strstr(break_editor_shell_console_text(shell),
                       "hot reload disabled") != NULL);

    break_editor_shell_set_hot_reload(shell, NULL);
    break_editor_hot_reload_destroy(hr);
    break_editor_shell_destroy(shell);
}

TEST(hot_reload_teardown_in_either_order_is_safe)
{
    char dir[512];
    char scene[600];
    char sidecar[700];
    BreakEditorShell *shell;
    BreakEditorHotReload *hr;
    test_tmp(dir, sizeof(dir), "editor_hr_teardown");
    TEST_MKDIR(dir);
    snprintf(scene, sizeof(scene), "%s/scene.bscn", dir);
    snprintf(sidecar, sizeof(sidecar), "%s" BREAK_EDITOR_SIDECAR_SUFFIX, scene);

    /* host destroys the hot-reload object while it is still attached */
    shell = break_editor_shell_create_for_test();
    ASSERT_NOT_NULL(shell);
    hr = break_editor_hot_reload_create(shell);
    ASSERT_NOT_NULL(hr);
    break_editor_shell_set_hot_reload(shell, hr);
    ASSERT_TRUE(break_editor_shell_set_scene_path(shell, scene));
    break_editor_hot_reload_destroy(hr);
    ASSERT_TRUE(break_editor_shell_hot_reload(shell) == NULL);
    break_editor_shell_tick(shell);
    break_editor_shell_destroy(shell);

    /* host destroys the shell first, then the orphaned hot-reload object */
    shell = break_editor_shell_create_for_test();
    ASSERT_NOT_NULL(shell);
    hr = break_editor_hot_reload_create(shell);
    ASSERT_NOT_NULL(hr);
    break_editor_shell_set_hot_reload(shell, hr);
    ASSERT_TRUE(break_editor_shell_set_scene_path(shell, scene));
    break_editor_shell_destroy(shell);
    break_editor_hot_reload_tick(hr);
    break_editor_hot_reload_destroy(hr);

    remove(scene);
    remove(sidecar);
    TEST_RMDIR(dir);
}

/* ---------------- i18n ---------------- */

static const char *label_text(BreakEditorShell *shell, const char *name) {
    my_widget_t *w = find(shell, name);
    return w != NULL ? ((const my_label_t *)w)->text : NULL;
}

static const char *button_text(BreakEditorShell *shell, const char *name) {
    my_widget_t *w = find(shell, name);
    return w != NULL ? ((const my_button_t *)w)->text : NULL;
}

/* a shell created while zh-CN is current shows Chinese chrome */
TEST(i18n_shell_created_in_chinese_shows_chinese_text)
{
    BreakEditorShell *shell;
    ASSERT_TRUE(break_editor_i18n_set_lang(BREAK_EDITOR_LANG_ZH_CN));
    shell = break_editor_shell_create_for_test();
    ASSERT_NOT_NULL(shell);
    ASSERT_STR_EQ(break_editor_shell_tool_text(shell), "工具：选择");
    ASSERT_STR_EQ(button_text(shell, "editor-add-button"), "添加");
    ASSERT_STR_EQ(button_text(shell, "editor-remove-button"), "删除");
    ASSERT_STR_EQ(label_text(shell, "editor-outliner-label"), "大纲");
    ASSERT_STR_EQ(label_text(shell, "editor-profiler-label"),
                  "性能分析（前 16 项，4 Hz）");
    ASSERT_STR_EQ(last_console_line(break_editor_shell_console_text(shell)),
                  "编辑器已就绪\n");
    ASSERT_TRUE(strstr(break_editor_shell_status_text(shell), "实体=") != NULL);
    break_editor_shell_destroy(shell);
    ASSERT_TRUE(break_editor_i18n_set_lang(BREAK_EDITOR_LANG_EN_US));
}

/* runtime switch through the palette: chrome follows immediately, earlier
 * console lines keep their language */
TEST(i18n_palette_switches_language_at_runtime)
{
    BreakEditorShell *shell;
    ASSERT_TRUE(break_editor_i18n_set_lang(BREAK_EDITOR_LANG_EN_US));
    shell = break_editor_shell_create_for_test();
    ASSERT_NOT_NULL(shell);
    ASSERT_TRUE(break_editor_shell_dispatch_key(shell, 'e', 0u));
    ASSERT_STR_EQ(break_editor_shell_tool_text(shell), "Tool: Rotate");

    ASSERT_TRUE(break_editor_shell_dispatch_key(shell, 'p', MY_KEYMOD_CTRL));
    ASSERT_TRUE(break_editor_shell_palette_set_filter(shell, "Language"));
    ASSERT_EQ(break_editor_shell_palette_count(shell), 2u);
    ASSERT_TRUE(break_editor_shell_palette_set_filter(shell, "Chinese"));
    ASSERT_EQ(break_editor_shell_palette_count(shell), 1u);
    ASSERT_TRUE(break_editor_shell_dispatch_key(shell, MY_KEY_RETURN, 0u));

    ASSERT_EQ(break_editor_i18n_lang(), BREAK_EDITOR_LANG_ZH_CN);
    ASSERT_STR_EQ(break_editor_shell_tool_text(shell), "工具：旋转");
    ASSERT_STR_EQ(button_text(shell, "editor-add-button"), "添加");
    ASSERT_STR_EQ(label_text(shell, "editor-outliner-label"), "大纲");
    ASSERT_STR_EQ(label_text(shell, "editor-render-label"), "渲染（4 Hz）");
    ASSERT_STR_EQ(label_text(shell, "editor-network-label"), "网络（4 Hz）");
    ASSERT_STR_EQ(label_text(shell, "editor-lua-label"), "Lua 控制台");
    ASSERT_TRUE(strncmp(label_text(shell, "editor-assets-path"), "资源：", 9u) == 0);
    ASSERT_TRUE(strstr(break_editor_shell_status_text(shell), "实体=") != NULL);
    /* the line announcing the switch is already in the new language; the
     * ready line written earlier stays English */
    ASSERT_STR_EQ(last_console_line(break_editor_shell_console_text(shell)),
                  "语言：中文\n");
    ASSERT_TRUE(strstr(break_editor_shell_console_text(shell),
                       "editor shell ready") != NULL);

    /* palette now lists and filters Chinese command names */
    ASSERT_TRUE(break_editor_shell_dispatch_key(shell, 'p', MY_KEYMOD_CTRL));
    ASSERT_EQ(break_editor_shell_palette_count(shell), 12u);
    ASSERT_TRUE(break_editor_shell_palette_set_filter(shell, "保存"));
    ASSERT_EQ(break_editor_shell_palette_count(shell), 1u);
    ASSERT_TRUE(break_editor_shell_palette_set_filter(shell, "English"));
    ASSERT_EQ(break_editor_shell_palette_count(shell), 1u);
    ASSERT_TRUE(break_editor_shell_dispatch_key(shell, MY_KEY_RETURN, 0u));
    ASSERT_EQ(break_editor_i18n_lang(), BREAK_EDITOR_LANG_EN_US);
    ASSERT_STR_EQ(break_editor_shell_tool_text(shell), "Tool: Rotate");
    ASSERT_STR_EQ(button_text(shell, "editor-remove-button"), "Remove");
    ASSERT_STR_EQ(label_text(shell, "editor-outliner-label"), "Outliner");
    break_editor_shell_destroy(shell);
}

TEST(i18n_set_language_api_is_bounded)
{
    BreakEditorShell *shell = break_editor_shell_create_for_test();
    ASSERT_NOT_NULL(shell);
    ASSERT_FALSE(break_editor_shell_set_language(shell, BREAK_EDITOR_LANG_COUNT));
    ASSERT_EQ(break_editor_i18n_lang(), BREAK_EDITOR_LANG_EN_US);
    ASSERT_FALSE(break_editor_shell_set_language(NULL, BREAK_EDITOR_LANG_ZH_CN));
    ASSERT_TRUE(break_editor_shell_set_language(shell, BREAK_EDITOR_LANG_ZH_CN));
    /* the inspector is rebuilt in the new language on selection change */
    emit_click(find(shell, "editor-add-button"));
    ASSERT_TRUE(break_editor_shell_select_index(shell, 0u));
    ASSERT_STR_EQ(label_text(shell, "editor-inspector-name-label"), "名称");
    ASSERT_TRUE(break_editor_shell_set_language(shell, BREAK_EDITOR_LANG_EN_US));
    ASSERT_STR_EQ(label_text(shell, "editor-inspector-name-label"), "Name");
    break_editor_shell_destroy(shell);
}

/* ---------------- asset-browser image preview + texture hot reload ------- */

typedef struct {
    char root[512];
    char a[700];
    char b[700];
    BreakEditorImagePreview *preview;
    char log[8][160];
    u32 log_count;
} ImagePreviewFixture;

static void img_mem_write(void *context, void *data, int size) {
    FILE *f = (FILE *)context;
    if (size > 0) {
        (void)fwrite(data, 1u, (size_t)size, f);
    }
}

/* Writes a w x h PNG whose pixels are all (shade, 0, 0, 255). */
static void img_write_png(const char *path, int w, int h, u8 shade) {
    static u8 px[64 * 64 * 4];
    FILE *f;
    int i;
    ASSERT_TRUE(w > 0 && h > 0 && w <= 64 && h <= 64);
    for (i = 0; i < w * h; i++) {
        px[i * 4 + 0] = shade;
        px[i * 4 + 1] = 0u;
        px[i * 4 + 2] = 0u;
        px[i * 4 + 3] = 255u;
    }
    f = fopen(path, "wb");
    ASSERT_NOT_NULL(f);
    ASSERT_TRUE(stbi_write_png_to_func(img_mem_write, f, w, h, 4, px, w * 4) != 0);
    fclose(f);
    hr_bump_mtime(path);
}

static void img_log(void *user, const char *line) {
    ImagePreviewFixture *fx = (ImagePreviewFixture *)user;
    if (fx->log_count < 8u) {
        snprintf(fx->log[fx->log_count], sizeof(fx->log[0]), "%s", line);
    }
    fx->log_count++;
}

static void img_fixture_open(ImagePreviewFixture *fx, const char *name) {
    memset(fx, 0, sizeof(*fx));
    test_tmp(fx->root, sizeof(fx->root), name);
    ASSERT_EQ(TEST_MKDIR(fx->root), 0);
    snprintf(fx->a, sizeof(fx->a), "%s/a.png", fx->root);
    snprintf(fx->b, sizeof(fx->b), "%s/b.png", fx->root);
    fx->preview = break_editor_image_preview_create();
    ASSERT_NOT_NULL(fx->preview);
    break_editor_image_preview_set_logger(fx->preview, img_log, fx);
}

static void img_fixture_close(ImagePreviewFixture *fx) {
    if (fx->preview != NULL) {
        break_editor_image_preview_set_shutdown_timeout_for_test(fx->preview,
                                                                 2000u);
        break_editor_image_preview_destroy(fx->preview);
        fx->preview = NULL;
    }
    remove(fx->a);
    remove(fx->b);
    TEST_RMDIR(fx->root);
}

static BreakEditorImagePreviewStats img_stats(const ImagePreviewFixture *fx) {
    BreakEditorImagePreviewStats s;
    memset(&s, 0, sizeof(s));
    (void)break_editor_image_preview_stats(fx->preview, &s);
    return s;
}

#define IMG_WAIT(fx_, cond_)                                                 \
    do {                                                                     \
        int img_i_;                                                          \
        for (img_i_ = 0; img_i_ < 3000 && !(cond_); img_i_++) {              \
            break_editor_image_preview_tick((fx_)->preview);                 \
            time_sleep_us(2000u);                                            \
        }                                                                    \
    } while (0)

static RHIDevice *img_fake_device(void) {
    /* the fake RHI ignores the device pointer; any non-NULL value selects
     * the "has a device" path */
    return (RHIDevice *)(uintptr_t)0x1;
}

static void image_preview_load_reload_body(ImagePreviewFixture *fx) {
    BreakEditorImagePreviewStats s;
    EditorRhiFakeStats fake;
    RHITexture first;
    img_fixture_open(fx, "editor_image_preview_reload");
    break_editor_image_preview_set_device(fx->preview, img_fake_device());
    img_write_png(fx->a, 8, 4, 100u);
    ASSERT_TRUE(break_editor_image_preview_set_path(fx->preview, fx->a));
    ASSERT_TRUE(strcmp(break_editor_image_preview_path(fx->preview), fx->a) == 0);
    IMG_WAIT(fx, img_stats(fx).reloads == 1u);
    s = img_stats(fx);
    ASSERT_EQ(s.reloads, 1u);
    ASSERT_TRUE(s.has_image);
    ASSERT_EQ(s.width, 8u);
    ASSERT_EQ(s.height, 4u);
    ASSERT_TRUE(s.watching);
    ASSERT_EQ(s.last_result, BREAK_EDITOR_IMAGE_PREVIEW_APPLIED);
    editor_rhi_fake_stats(&fake);
    ASSERT_EQ(fake.texture_creates, 1u);
    ASSERT_EQ(fake.last_texture_w, 8u);
    first = break_editor_image_preview_texture(fx->preview);
    ASSERT_TRUE(editor_rhi_fake_texture_live(first));

    /* external rewrite with a new size: watcher-driven reload */
    img_write_png(fx->a, 16, 2, 200u);
    IMG_WAIT(fx, img_stats(fx).reloads == 2u);
    s = img_stats(fx);
    ASSERT_EQ(s.reloads, 2u);
    ASSERT_EQ(s.width, 16u);
    ASSERT_EQ(s.height, 2u);
    ASSERT_TRUE(s.events >= 1u);
    editor_rhi_fake_stats(&fake);
    ASSERT_EQ(fake.texture_creates, 2u);
    ASSERT_EQ(fake.texture_destroys, 1u);
    ASSERT_EQ(fake.live_textures, 1u);
    ASSERT_FALSE(editor_rhi_fake_texture_live(first));
    ASSERT_TRUE(fx->log_count >= 2u);
}

TEST(image_preview_loads_and_hot_reloads_texture)
{
    ImagePreviewFixture fx;
    editor_rhi_fake_reset();
    editor_rhi_fake_set_enabled(true);
    image_preview_load_reload_body(&fx);
    img_fixture_close(&fx);
    {
        EditorRhiFakeStats fake;
        editor_rhi_fake_stats(&fake);
        ASSERT_EQ(fake.live_textures, 0u); /* destroy released it */
    }
    editor_rhi_fake_set_enabled(false);
    editor_rhi_fake_reset();
}

static void image_preview_failure_keeps_old_body(ImagePreviewFixture *fx) {
    BreakEditorImagePreviewStats s;
    EditorRhiFakeStats fake;
    RHITexture kept;
    img_fixture_open(fx, "editor_image_preview_keep_old");
    break_editor_image_preview_set_device(fx->preview, img_fake_device());
    img_write_png(fx->a, 4, 4, 50u);
    ASSERT_TRUE(break_editor_image_preview_set_path(fx->preview, fx->a));
    IMG_WAIT(fx, img_stats(fx).reloads == 1u);
    kept = break_editor_image_preview_texture(fx->preview);
    ASSERT_TRUE(editor_rhi_fake_texture_live(kept));

    /* garbage: probe fails on the worker */
    hr_write_text(fx->a, "not an image at all");
    hr_bump_mtime(fx->a);
    IMG_WAIT(fx, img_stats(fx).failed == 1u && !img_stats(fx).busy);
    s = img_stats(fx);
    ASSERT_EQ(s.failed, 1u);
    ASSERT_EQ(s.reloads, 1u);
    ASSERT_EQ(s.width, 4u);
    ASSERT_EQ(s.last_result, BREAK_EDITOR_IMAGE_PREVIEW_FAILED_KEEP_OLD);
    ASSERT_TRUE(rhi_handle_valid(break_editor_image_preview_texture(fx->preview)));
    ASSERT_TRUE(editor_rhi_fake_texture_live(kept));

    /* a valid image whose GPU create fails also keeps the old texture */
    editor_rhi_fake_fail_texture_creates(1u);
    img_write_png(fx->a, 6, 6, 90u);
    IMG_WAIT(fx, img_stats(fx).failed == 2u && !img_stats(fx).busy);
    s = img_stats(fx);
    ASSERT_EQ(s.failed, 2u);
    ASSERT_EQ(s.width, 4u);
    ASSERT_TRUE(editor_rhi_fake_texture_live(kept));
    editor_rhi_fake_stats(&fake);
    ASSERT_EQ(fake.texture_destroys, 0u);

    /* recovery */
    ASSERT_TRUE(break_editor_image_preview_request(fx->preview));
    IMG_WAIT(fx, img_stats(fx).reloads == 2u);
    ASSERT_EQ(img_stats(fx).width, 6u);
    ASSERT_FALSE(editor_rhi_fake_texture_live(kept));
}

TEST(image_preview_failed_reload_keeps_current_texture)
{
    ImagePreviewFixture fx;
    editor_rhi_fake_reset();
    editor_rhi_fake_set_enabled(true);
    image_preview_failure_keeps_old_body(&fx);
    img_fixture_close(&fx);
    editor_rhi_fake_set_enabled(false);
    editor_rhi_fake_reset();
}

static void image_preview_switch_body(ImagePreviewFixture *fx) {
    BreakEditorImagePreviewStats s;
    EditorRhiFakeStats fake;
    u64 popped;
    img_fixture_open(fx, "editor_image_preview_switch");
    break_editor_image_preview_set_device(fx->preview, img_fake_device());
    img_write_png(fx->a, 3, 3, 10u);
    img_write_png(fx->b, 5, 7, 20u);
    /* hold the worker on a's request, then switch to b: a's late result
     * must not become the preview */
    popped = atomic_load_explicit(&g_break_runtime_test_reload_popped,
                                  memory_order_acquire);
    break_runtime_test_reload_set_gates(0u, 1u);
    ASSERT_TRUE(break_editor_image_preview_set_path(fx->preview, fx->a));
    IMG_WAIT(fx, atomic_load_explicit(&g_break_runtime_test_reload_popped,
                                      memory_order_acquire) > popped);
    ASSERT_TRUE(img_stats(fx).busy);
    ASSERT_TRUE(break_editor_image_preview_set_path(fx->preview, fx->b));
    break_runtime_test_reload_set_gates(0u, 0u);
    IMG_WAIT(fx, img_stats(fx).reloads == 1u && !img_stats(fx).busy);
    s = img_stats(fx);
    ASSERT_EQ(s.reloads, 1u);
    ASSERT_EQ(s.width, 5u);
    ASSERT_EQ(s.height, 7u);
    editor_rhi_fake_stats(&fake);
    ASSERT_EQ(fake.texture_creates, 1u);
    ASSERT_EQ(fake.last_texture_w, 5u);
    ASSERT_TRUE(strcmp(break_editor_image_preview_path(fx->preview), fx->b) == 0);

    /* only b is watched now: editing a does nothing */
    img_write_png(fx->a, 9, 9, 30u);
    {
        int i;
        for (i = 0; i < 300; i++) {
            break_editor_image_preview_tick(fx->preview);
            time_sleep_us(2000u);
        }
    }
    ASSERT_EQ(img_stats(fx).reloads, 1u);
    ASSERT_EQ(img_stats(fx).width, 5u);
}

TEST(image_preview_switching_files_drops_the_old_request)
{
    ImagePreviewFixture fx;
    editor_rhi_fake_reset();
    editor_rhi_fake_set_enabled(true);
    image_preview_switch_body(&fx);
    break_runtime_test_reload_set_gates(0u, 0u);
    img_fixture_close(&fx);
    editor_rhi_fake_set_enabled(false);
    editor_rhi_fake_reset();
}

static void image_preview_headless_and_bounds_body(ImagePreviewFixture *fx) {
    BreakEditorImagePreviewStats s;
    EditorRhiFakeStats fake;
    char long_path[BREAK_EDITOR_IMAGE_PREVIEW_PATH_CAPACITY + 16u];
    img_fixture_open(fx, "editor_image_preview_headless");
    s = img_stats(fx);
    ASSERT_FALSE(s.has_image);
    ASSERT_EQ(s.last_result, BREAK_EDITOR_IMAGE_PREVIEW_EMPTY);
    ASSERT_FALSE(break_editor_image_preview_request(fx->preview));
    ASSERT_FALSE(break_editor_image_preview_set_path(fx->preview, NULL));
    ASSERT_FALSE(break_editor_image_preview_set_path(fx->preview, ""));
    ASSERT_FALSE(break_editor_image_preview_set_path(fx->preview, "noslash.png"));
    memset(long_path, 'x', sizeof(long_path) - 1u);
    long_path[0] = '/';
    long_path[sizeof(long_path) - 1u] = '\0';
    ASSERT_FALSE(break_editor_image_preview_set_path(fx->preview, long_path));
    ASSERT_TRUE(break_editor_image_preview_path(fx->preview)[0] == '\0');

    /* no device: decodes and reports, creates no texture */
    img_write_png(fx->a, 2, 3, 70u);
    ASSERT_TRUE(break_editor_image_preview_set_path(fx->preview, fx->a));
    IMG_WAIT(fx, img_stats(fx).reloads == 1u);
    s = img_stats(fx);
    ASSERT_TRUE(s.has_image);
    ASSERT_EQ(s.width, 2u);
    ASSERT_EQ(s.height, 3u);
    ASSERT_FALSE(rhi_handle_valid(break_editor_image_preview_texture(fx->preview)));
    editor_rhi_fake_stats(&fake);
    ASSERT_EQ(fake.texture_creates, 0u);

    /* attaching a device uploads the current image once */
    break_editor_image_preview_set_device(fx->preview, img_fake_device());
    break_editor_image_preview_tick(fx->preview);
    editor_rhi_fake_stats(&fake);
    ASSERT_EQ(fake.texture_creates, 1u);
    ASSERT_TRUE(rhi_handle_valid(break_editor_image_preview_texture(fx->preview)));
    /* detaching destroys it */
    break_editor_image_preview_set_device(fx->preview, NULL);
    editor_rhi_fake_stats(&fake);
    ASSERT_EQ(fake.live_textures, 0u);
    ASSERT_TRUE(img_stats(fx).has_image);

    /* bounded shutdown with a held worker: false, then retry succeeds */
    break_runtime_test_reload_set_gates(0u, 1u);
    ASSERT_TRUE(break_editor_image_preview_request(fx->preview));
    {
        u64 popped = atomic_load_explicit(&g_break_runtime_test_reload_popped,
                                          memory_order_acquire);
        IMG_WAIT(fx, atomic_load_explicit(&g_break_runtime_test_reload_popped,
                                          memory_order_acquire) > popped);
    }
    break_editor_image_preview_set_shutdown_timeout_for_test(fx->preview, 50u);
    ASSERT_FALSE(break_editor_image_preview_shutdown(fx->preview));
    ASSERT_EQ(img_stats(fx).last_result, BREAK_EDITOR_IMAGE_PREVIEW_UNAVAILABLE);
    ASSERT_FALSE(break_editor_image_preview_set_path(fx->preview, fx->b));
    break_runtime_test_reload_set_gates(0u, 0u);
    break_editor_image_preview_set_shutdown_timeout_for_test(fx->preview, 2000u);
    ASSERT_TRUE(break_editor_image_preview_shutdown(fx->preview));
}

TEST(image_preview_headless_device_switch_and_bounded_shutdown)
{
    ImagePreviewFixture fx;
    editor_rhi_fake_reset();
    editor_rhi_fake_set_enabled(true);
    image_preview_headless_and_bounds_body(&fx);
    break_runtime_test_reload_set_gates(0u, 0u);
    img_fixture_close(&fx);
    editor_rhi_fake_set_enabled(false);
    editor_rhi_fake_reset();
}

TEST_MAIN_BEGIN()
    RUN_TEST(shell_create_and_destroy);
    RUN_TEST(i18n_shell_created_in_chinese_shows_chinese_text);
    RUN_TEST(i18n_palette_switches_language_at_runtime);
    RUN_TEST(i18n_set_language_api_is_bounded);
    RUN_TEST(add_entity_via_panel_button_increments_outliner);
    RUN_TEST(add_entity_via_palette_and_ctrl_z_removes_row);
    RUN_TEST(remove_selected_via_panel_button);
    RUN_TEST(remove_selected_console_line_names_removed_entity);
    RUN_TEST(rename_via_name_edit_then_undo_reverts_displayed_name);
    RUN_TEST(tool_keys_update_tool_label);
    RUN_TEST(focus_key_records_intent_note);
    RUN_TEST(palette_opens_filters_and_escape_closes);
    RUN_TEST(palette_executes_tool_command_on_activate);
    RUN_TEST(ctrl_s_saves_to_configured_path);
    RUN_TEST(outliner_row_click_selects);
    RUN_TEST(rename_then_undo_reverts_outliner_row_text);
    RUN_TEST(inspector_field_edit_routes_through_command_stack);
    RUN_TEST(console_ring_is_bounded_at_64_entries);
    RUN_TEST(ppm_smoke_paints_expected_theme_colors);
    RUN_TEST(viewport_widget_present_and_laid_out);
    RUN_TEST(tool_keys_set_gizmo_mode_and_label);
    RUN_TEST(focus_key_moves_camera_target_to_selection);
    RUN_TEST(pointer_down_on_viewport_picks_entity);
    RUN_TEST(gizmo_drag_via_pointer_events_then_single_undo);
    RUN_TEST(mid_drag_ctrl_z_commits_then_undoes_the_drag);
    RUN_TEST(camera_orbit_pan_zoom_via_pointer_and_wheel);
    RUN_TEST(viewport_render_without_device_is_bounded_noop);
    RUN_TEST(viewport_shell_wrapper_records_no_device);
    RUN_TEST(model_matrix_known_answers);
    RUN_TEST(viewport_last_stats_report_skip_reasons_headless);
    RUN_TEST(shader_source_resolves_variant_paths_bytes_and_cleanup);
    RUN_TEST(shader_source_empty_file_succeeds_and_missing_root_falls_back);
    RUN_TEST(shader_source_all_missing_returns_no_partial_bytes);
    RUN_TEST(shader_source_overlong_root_is_skipped_not_truncated);
    RUN_TEST(viewport_shader_candidate_failures_preserve_live_state);
    RUN_TEST(viewport_shader_initial_failure_recovers_through_explicit_reload);
    RUN_TEST(assets_panel_lists_fixture_root);
    RUN_TEST(shell_applies_the_new_ui_dark_theme);
    RUN_TEST(outliner_highlights_the_selected_row);
    RUN_TEST(assets_panel_navigation_updates_rows);
    RUN_TEST(assets_panel_image_row_opens_the_preview);
    RUN_TEST(assets_panel_bscn_activation_loads_doc_and_clears_undo);
    RUN_TEST(lua_panel_eval_routes_result_to_console_ring);
    RUN_TEST(lua_panel_spawn_updates_outliner_and_ctrl_z_reverts);
    RUN_TEST(lua_panel_history_up_down_recall);
    RUN_TEST(profiler_panel_populates_rows_after_pumped_frame);
    RUN_TEST(phase3_layout_assets_lua_profiler_panels_present);
    RUN_TEST(network_panel_remote_off_row);
    RUN_TEST(network_panel_layout_in_diagnostics_column_under_profiler);
    RUN_TEST(network_panel_source_never_calls_send_close_transition);
    RUN_TEST(render_panel_no_device_row);
    RUN_TEST(render_panel_diag_attach_failure_does_not_leave_dangling_lists);
    RUN_TEST(render_panel_layout_beside_network_in_diagnostics_row);
    RUN_TEST(render_panel_rows_from_device_source_and_viewport_stats);
    RUN_TEST(render_panel_throttle_4hz_and_device_lost);
    RUN_TEST(render_panel_source_is_read_only);
    RUN_TEST(shader_reload_ctrl_shift_r_queues_without_sync_rhi);
    RUN_TEST(shader_reload_watcher_applies_pair_keeps_old_and_recovers);
    RUN_TEST(shader_reload_initial_failure_recovers_without_implicit_retry);
    RUN_TEST(shader_reload_worker_stages_off_rhi_and_trailing_uses_latest);
    RUN_TEST(shader_reload_two_root_watch_promotes_and_delete_falls_back);
    RUN_TEST(shader_reload_one_sided_failure_preserves_pipeline);
    RUN_TEST(shader_reload_dead_commit_commands_do_not_block_next_reload);
    RUN_TEST(image_preview_loads_and_hot_reloads_texture);
    RUN_TEST(image_preview_failed_reload_keeps_current_texture);
    RUN_TEST(image_preview_switching_files_drops_the_old_request);
    RUN_TEST(image_preview_headless_device_switch_and_bounded_shutdown);
    RUN_TEST(shader_reload_second_request_admission_failure_recovers);
    RUN_TEST(shader_reload_manual_request_survives_watch_unavailable);
    RUN_TEST(shader_reload_manual_only_diagnostic_keeps_busy_and_counts);
    RUN_TEST(shader_reload_inflight_claim_teardown_is_bounded);
    RUN_TEST(shader_reload_shutdown_timeout_can_retry);
    RUN_TEST(shader_reload_viewport_and_shell_shutdown_retry_same_owner);
    RUN_TEST(shader_reload_shortcut_without_owner_is_bounded);
    RUN_TEST(shader_reload_unavailable_stats_and_null_calls);
    RUN_TEST(hot_reload_valid_external_edit_replaces_document);
    RUN_TEST(hot_reload_creation_of_missing_scene_loads_it);
    RUN_TEST(hot_reload_invalid_external_edit_keeps_document_and_undo);
    RUN_TEST(hot_reload_dirty_document_is_not_overwritten);
    RUN_TEST(hot_reload_own_save_does_not_reload_or_erase_undo);
    RUN_TEST(hot_reload_external_edit_after_local_save_still_reloads);
    RUN_TEST(hot_reload_scene_without_sidecar_keeps_following_external_edits);
    RUN_TEST(hot_reload_request_in_flight_during_save_is_dropped_as_stale);
    RUN_TEST(hot_reload_scene_switch_via_asset_browser_rewatches);
    RUN_TEST(assets_panel_live_refresh_shows_external_create_and_delete);
    RUN_TEST(assets_panel_live_refresh_survives_vanished_directory);
    RUN_TEST(hot_reload_overlong_scene_path_disables_watch_without_truncating);
    RUN_TEST(hot_reload_teardown_in_either_order_is_safe);
#ifdef BREAK_EDITOR_REMOTE_TESTS
    RUN_REMOTE_TEST(remote_protocol_ids_live_in_default_registry);
    RUN_REMOTE_TEST(remote_describe_returns_version_entity_count_dirty);
    RUN_REMOTE_TEST(remote_spawn_list_rename_remove_roundtrip_and_ctrl_z_pin);
    RUN_REMOTE_TEST(remote_spawn_then_remote_undo_redo);
    RUN_REMOTE_TEST(remote_set_field_maps_component_and_field_names);
    RUN_REMOTE_TEST(remote_eval_runs_on_shell_thread_and_returns_console_tail);
    RUN_REMOTE_TEST(remote_eval_at_4096_boundary_and_len_mismatch_closes);
    RUN_REMOTE_TEST(remote_unknown_id_and_malformed_close_connection);
    RUN_REMOTE_TEST(remote_disabled_leaves_shell_untouched);
    RUN_REMOTE_TEST(remote_tick_wiring_polls_adapter_every_frame);
    RUN_REMOTE_TEST(remote_config_validation_and_snapshot);
    RUN_REMOTE_TEST(remote_null_and_bounded_calls_are_safe);
    RUN_REMOTE_TEST(remote_cli_default_off_and_fail_closed_flags);
    RUN_REMOTE_TEST(network_panel_rows_match_session_stats_and_reactor_accessors);
    RUN_REMOTE_TEST(network_panel_shell_destroyed_before_attached_remote);
    RUN_REMOTE_TEST(network_panel_rows_bounded_with_more_than_11_connections);
    RUN_REMOTE_TEST(network_panel_throttle_4hz_row_storage_unchanged_within_250ms);
    RUN_REMOTE_TEST(network_panel_refresh_never_mutates_remote_state);
#ifdef BREAK_ENABLE_CRYPTO
    RUN_REMOTE_TEST(remote_tls_auth_v2_client_describe_and_spawn);
    RUN_REMOTE_TEST(remote_tls_e2e_connect_auth_describe_spawn_undo_disconnect);
    RUN_REMOTE_TEST(remote_tls_unauthenticated_clients_closed_zero_doc_effect);
    RUN_REMOTE_TEST(remote_tls_auth_deadline_closes_idle_unauthenticated_client);
    RUN_REMOTE_TEST(remote_tls_auth_deadline_spares_authenticated_client);
    RUN_REMOTE_TEST(remote_tls_start_fails_closed_on_missing_certs_or_auth);
    RUN_REMOTE_TEST(remote_tls_rate_limit_denials_observable);
#endif
#endif
TEST_MAIN_END()
