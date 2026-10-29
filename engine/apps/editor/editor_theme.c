/* Editor look: JetBrains New UI dark — see editor_theme.h. */

#include "editor_theme.h"

#include "myui/my_window.h"

/* Selectors use the widget types myui paints (button, label, edit,
 * list_view, text_area, window) and the editor's widget names. Plain
 * containers paint bg_color only when a rule sets it, labels are
 * transparent unless themed, buttons draw a rounded border of
 * border-width (myui 2026-10-28). */
static const char k_css[] =
    /* base */
    "window { background-color: #2b2d30; color: #dfe1e5; }\n"
    /* the base theme gives labels a light bg; editor labels sit on their
     * panel colour */
    "label { background-color: transparent; color: #dfe1e5;"
    " font-size: 13px; }\n"
    /* tool window chrome: toolbar and status bar on the window colour,
     * separated from the content by the panel border colour */
    "#editor-root { background-color: #393b40; }\n"
    "#editor-toolbar { background-color: #2b2d30; }\n"
    "#editor-status { background-color: #2b2d30; color: #9da0a8;"
    " font-size: 12px; }\n"
    "#editor-tool-label { color: #9da0a8; font-size: 12px; }\n"
    /* tool windows (outliner, assets, inspector, diagnostics) */
    "#editor-outliner-panel, #editor-right-panel, #editor-bottom,"
    " #editor-assets-panel, #editor-assets-preview-panel, #editor-inspector,"
    " #editor-diag-row { background-color: #2b2d30; }\n"
    "#editor-outliner-label, #editor-assets-path,"
    " #editor-assets-preview-label, #editor-inspector-name-label {"
    " color: #9da0a8; font-size: 12px; }\n"
    /* content surfaces */
    "list_view { background-color: #1e1f22; }\n"
    "text_area { background-color: #1e1f22; border-color: #1e1f22;"
    " color: #dfe1e5; }\n"
    "edit { background-color: #1e1f22; border-color: #4e5157;"
    " color: #dfe1e5; }\n"
    /* myui edits paint their focused state from the hover slot (my_edit.h),
     * so this is the focus ring: accent border */
    "edit:hover { border-color: #3574f0; }\n"
    /* buttons: flat dark default, 4 px corners, 1 px border */
    "button { background-color: #2b2d30; border-color: #4e5157;"
    " border-width: 1px; border-radius: 4px; color: #dfe1e5;"
    " font-size: 13px; }\n"
    "button:hover { background-color: #393b40; border-color: #5e6066; }\n"
    "button:pressed { background-color: #43454a; }\n"
    "button:disabled { background-color: #2b2d30; border-color: #393b40;"
    " color: #6f737a; }\n"
    /* primary action (toolbar Add): accent blue */
    "#editor-add-button { background-color: #3574f0; border-color: #3574f0;"
    " color: #ffffff; }\n"
    "#editor-add-button:hover { background-color: #4682fa;"
    " border-color: #4682fa; }\n"
    "#editor-add-button:pressed { background-color: #2e5fcc;"
    " border-color: #2e5fcc; }\n"
    /* list rows: borderless, selection tint on hover */
    "#editor-outliner-row, #editor-assets-row, #editor-palette-row {"
    " background-color: #1e1f22; border-width: 0px; border-radius: 0px;"
    " color: #dfe1e5; }\n"
    "#editor-outliner-row:hover, #editor-assets-row:hover,"
    " #editor-palette-row:hover { background-color: #2e436e; }\n"
    "#editor-outliner-row:pressed, #editor-assets-row:pressed,"
    " #editor-palette-row:pressed { background-color: #2e436e; }\n"
    /* the selected entity's outliner row (class set by editor_panels.c) */
    "#editor-outliner-row.selected, #editor-outliner-row.selected:hover,"
    " #editor-palette-row.selected, #editor-palette-row.selected:hover {"
    " background-color: #2e436e; color: #ffffff; }\n"
    /* command palette popup */
    "#editor-palette { background-color: #2b2d30; }\n"
    /* tool-window tab strips: flat tabs on the window colour, the active
     * one on the content colour with accent text */
    "#editor-bottom-tabs, #editor-diag-tabs { background-color: #2b2d30; }\n"
    "#editor-tab { background-color: #2b2d30; border-width: 0px;"
    " border-radius: 0px; color: #9da0a8; font-size: 12px; }\n"
    "#editor-tab:hover { background-color: #393b40; color: #dfe1e5; }\n"
    "#editor-tab.active, #editor-tab.active:hover {"
    " background-color: #1e1f22; color: #dfe1e5; }\n";

static const char k_css_light[] =
    /* base */
    "window { background-color: #f7f8fa; color: #1f1f1f; }\n"
    /* the base theme gives labels a light bg; editor labels sit on their
     * panel colour */
    "label { background-color: transparent; color: #1f1f1f;"
    " font-size: 13px; }\n"
    /* tool window chrome: toolbar and status bar on the window colour,
     * separated from the content by the panel border colour */
    "#editor-root { background-color: #d3d5db; }\n"
    "#editor-toolbar { background-color: #f7f8fa; }\n"
    "#editor-status { background-color: #f7f8fa; color: #6c707e;"
    " font-size: 12px; }\n"
    "#editor-tool-label { color: #6c707e; font-size: 12px; }\n"
    /* tool windows (outliner, assets, inspector, diagnostics) */
    "#editor-outliner-panel, #editor-right-panel, #editor-bottom,"
    " #editor-assets-panel, #editor-assets-preview-panel, #editor-inspector,"
    " #editor-diag-row { background-color: #f7f8fa; }\n"
    "#editor-outliner-label, #editor-assets-path,"
    " #editor-assets-preview-label, #editor-inspector-name-label {"
    " color: #6c707e; font-size: 12px; }\n"
    /* content surfaces */
    "list_view { background-color: #ffffff; }\n"
    "text_area { background-color: #ffffff; border-color: #ffffff;"
    " color: #1f1f1f; }\n"
    "edit { background-color: #ffffff; border-color: #d3d5db;"
    " color: #1f1f1f; }\n"
    /* myui edits paint their focused state from the hover slot (my_edit.h),
     * so this is the focus ring: accent border */
    "edit:hover { border-color: #3574f0; }\n"
    /* buttons: flat dark default, 4 px corners, 1 px border */
    "button { background-color: #f7f8fa; border-color: #d3d5db;"
    " border-width: 1px; border-radius: 4px; color: #1f1f1f;"
    " font-size: 13px; }\n"
    "button:hover { background-color: #d3d5db; border-color: #c3c6cc; }\n"
    "button:pressed { background-color: #dfe1e5; }\n"
    "button:disabled { background-color: #f7f8fa; border-color: #d3d5db;"
    " color: #a8acb4; }\n"
    /* primary action (toolbar Add): accent blue */
    "#editor-add-button { background-color: #3574f0; border-color: #3574f0;"
    " color: #ffffff; }\n"
    "#editor-add-button:hover { background-color: #4682fa;"
    " border-color: #4682fa; }\n"
    "#editor-add-button:pressed { background-color: #2e5fcc;"
    " border-color: #2e5fcc; }\n"
    /* list rows: borderless, selection tint on hover */
    "#editor-outliner-row, #editor-assets-row, #editor-palette-row {"
    " background-color: #ffffff; border-width: 0px; border-radius: 0px;"
    " color: #1f1f1f; }\n"
    "#editor-outliner-row:hover, #editor-assets-row:hover,"
    " #editor-palette-row:hover { background-color: #d4e2ff; }\n"
    "#editor-outliner-row:pressed, #editor-assets-row:pressed,"
    " #editor-palette-row:pressed { background-color: #d4e2ff; }\n"
    /* the selected entity's outliner row (class set by editor_panels.c) */
    "#editor-outliner-row.selected, #editor-outliner-row.selected:hover,"
    " #editor-palette-row.selected, #editor-palette-row.selected:hover {"
    " background-color: #d4e2ff; color: #1f1f1f; }\n"
    /* command palette popup */
    "#editor-palette { background-color: #f7f8fa; }\n"
    "#editor-bottom-tabs, #editor-diag-tabs { background-color: #f7f8fa; }\n"
    "#editor-tab { background-color: #f7f8fa; border-width: 0px;"
    " border-radius: 0px; color: #6c707e; font-size: 12px; }\n"
    "#editor-tab:hover { background-color: #dfe1e5; color: #1f1f1f; }\n"
    "#editor-tab.active, #editor-tab.active:hover {"
    " background-color: #ffffff; color: #1f1f1f; }\n";


static bool g_light = false;

const char *break_editor_theme_css(void) {
    return k_css;
}

bool break_editor_theme_apply(struct my_window_t *win) {
    return break_editor_theme_apply_mode(win, false);
}

bool break_editor_theme_apply_mode(struct my_window_t *win, bool light) {
    if (win == NULL) {
        return false;
    }
    if (my_window_set_css_style(win, light ? k_css_light : k_css) != MY_RET_OK) {
        return false; /* keep the previous sheet AND the previous mode */
    }
    g_light = light;
    return true;
}

bool break_editor_theme_is_light(void) {
    return g_light;
}

uint32_t break_editor_theme_content_bg(void) {
    return g_light ? BREAK_EDITOR_THEME_LIGHT_BG_CONTENT
                   : BREAK_EDITOR_THEME_BG_CONTENT;
}
