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
    "edit:hover { border-color: #5e6066; }\n"
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
    /* command palette popup */
    "#editor-palette { background-color: #2b2d30; }\n";

const char *break_editor_theme_css(void) {
    return k_css;
}

bool break_editor_theme_apply(struct my_window_t *win) {
    return win != NULL && my_window_set_css_style(win, k_css) == MY_RET_OK;
}
