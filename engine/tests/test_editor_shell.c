/* Headless tests for the Stage 4 scene editor Phase 1 shell (Task 4):
 * panel wiring, shortcut routing, command palette, selection, and a PPM
 * pixel smoke — all on the dummy PAL via break_editor_shell_create_for_test
 * (no RHI). Widget callbacks are exercised through the real emitters
 * ("click"/"activate") so a UI bypass of the command stack would fail the
 * undo pins. */
#include "test_framework.h"

#include <stdio.h>
#include <string.h>
#if defined(_WIN32)
#else
#include <sys/stat.h>
#endif

#include "editor_panels.h"

#include <editor/editor_cmd.h>
#include <editor/editor_components.h>
#include <editor/editor_scene.h>

#include "myc/my_emitter.h"
#include "mypal/my_event.h"
#include "mypal/my_pal.h"
#include "myr/my_lcd_mem.h"
#include "myui/my_widget.h"
#include "myui/my_window.h"
#include "myui/widgets/my_button.h"
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
    ASSERT_EQ(break_editor_shell_palette_count(shell), 10u);
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
    /* Discriminating discriminant: the default theme overrides the window
     * bg to 0xF5F5F5FF (my_theme.c:1127-1128), consumed by the window's
     * on_paint (my_window.c:110-111); the normal-state button bg is
     * 0xE0E0E0FF (my_theme.c:1129-1130). A NEVER-painted dummy lcd stays
     * zero-filled, so both counts are 0 unless a frame was actually
     * rendered — comparing against the pre-theme rgb(32,32,32) fallback
     * would count 100% of the frame in BOTH cases. */
    for (y = 0u; y < 480u; y++) {
        for (x = 0u; x < 800u; x++) {
            const uint8_t *p = pixels + y * stride + x * 4u;
            if (p[0] == 245u && p[1] == 245u && p[2] == 245u) {
                bg_count++;
            } else if (p[0] == 224u && p[1] == 224u && p[2] == 224u) {
                button_count++;
            }
        }
    }
    /* most of the 800x480 frame is window bg... */
    /* most of the 800x480 frame is window bg... */
    printf("    (ppm smoke: %zu window-bg px, %zu button-bg px)\n", bg_count,
           button_count);
    ASSERT_TRUE(bg_count > (800u * 480u) / 2u);
    /* ...and the toolbar/outliner-row buttons painted their bg */
    ASSERT_TRUE(button_count > 100u);
    break_editor_shell_destroy(shell);
}

TEST_MAIN_BEGIN()
    RUN_TEST(shell_create_and_destroy);
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
TEST_MAIN_END()
