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
#include "editor_viewport3d.h"

#include <core/profiler.h>
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
    /* Discriminating discriminant: the default theme overrides the window
     * bg to 0xF5F5F5FF (my_theme.c:1127-1128), consumed by the window's
     * on_paint (my_window.c:110-111); the normal-state button bg is
     * 0xE0E0E0FF (my_theme.c:1129-1130). A NEVER-painted dummy lcd stays
     * zero-filled, so all counts are 0 unless a frame was actually
     * rendered — comparing against the pre-theme rgb(32,32,32) fallback
     * would count 100% of the frame in BOTH cases.
     * Phase 2 Task 3 recalibration: the frame now contains the 3D viewport
     * panel (placeholder rgb(30,31,34), ~376x334 = ~125k px on the dummy
     * canvas where no FBO exists) under the open palette (420x300 = 126k
     * px), so the window bg legitimately covers only ~25-35% of the frame
     * (was >50% in the Phase 1 layout). The threshold keeps its
     * discriminating power (never-painted = 0) and the viewport placeholder
     * count is pinned directly. */
    for (y = 0u; y < 480u; y++) {
        for (x = 0u; x < 800u; x++) {
            const uint8_t *p = pixels + y * stride + x * 4u;
            if (p[0] == 245u && p[1] == 245u && p[2] == 245u) {
                bg_count++;
            } else if (p[0] == 224u && p[1] == 224u && p[2] == 224u) {
                button_count++;
            } else if ((p[0] == 30u && p[1] == 31u && p[2] == 34u) ||
                       (p[0] == 34u && p[1] == 31u && p[2] == 30u)) {
                /* placeholder rgb(30,31,34): the dummy lcd pixel format is
                 * BGRA8888 on some configs (my_vgcanvas_soft.c fill path),
                 * so accept either channel order (the gray theme probes
                 * above are order-agnostic, which is why they never cared) */
                viewport_count++;
            }
        }
    }
    printf("    (ppm smoke: %zu window-bg px, %zu button-bg px, %zu viewport "
           "placeholder px)\n",
           bg_count, button_count, viewport_count);
    /* window bg still paints broadly (the palette only covers part of it) */
    ASSERT_TRUE(bg_count > (800u * 480u) / 5u);
    /* ...and the toolbar/outliner-row buttons painted their bg */
    ASSERT_TRUE(button_count > 100u);
    /* ...and the viewport panel painted its placeholder (dummy path: no FBO) */
    ASSERT_TRUE(viewport_count > 100000u);
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

/* ---------------- Phase 3 Task 3: assets / lua / profiler panels -------- */

static bool write_text_file(const char *path, const char *text) {
    FILE *f = fopen(path, "wb");
    if (f == NULL) {
        return false;
    }
    fputs(text, f);
    return fclose(f) == 0;
}

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
    RUN_TEST(viewport_widget_present_and_laid_out);
    RUN_TEST(tool_keys_set_gizmo_mode_and_label);
    RUN_TEST(focus_key_moves_camera_target_to_selection);
    RUN_TEST(pointer_down_on_viewport_picks_entity);
    RUN_TEST(gizmo_drag_via_pointer_events_then_single_undo);
    RUN_TEST(mid_drag_ctrl_z_commits_then_undoes_the_drag);
    RUN_TEST(camera_orbit_pan_zoom_via_pointer_and_wheel);
    RUN_TEST(viewport_render_without_device_is_bounded_noop);
    RUN_TEST(model_matrix_known_answers);
    RUN_TEST(assets_panel_lists_fixture_root);
    RUN_TEST(assets_panel_navigation_updates_rows);
    RUN_TEST(assets_panel_bscn_activation_loads_doc_and_clears_undo);
    RUN_TEST(lua_panel_eval_routes_result_to_console_ring);
    RUN_TEST(lua_panel_spawn_updates_outliner_and_ctrl_z_reverts);
    RUN_TEST(lua_panel_history_up_down_recall);
    RUN_TEST(profiler_panel_populates_rows_after_pumped_frame);
    RUN_TEST(phase3_layout_assets_lua_profiler_panels_present);
TEST_MAIN_END()
