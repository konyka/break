# Editor text clarity + CLion-style theme — design (2026-10-28)

## 1. Ghosted text (fixed first)

Measured: the toolbar text in a live editor screenshot went from 348 to 594 fully dark pixels between frame 3 and frame 70 with no input; GPU readback of one glyph through the same canvas was clean. Root cause: the Break RHI vgcanvas honoured the clip for rects and paths but not for glyph or texture quads. The retained UI repaints each damaged rect with the whole tree under a clip, so every partial repaint blended all text again on top of last frame's glyphs. Fixed in `my_vgcanvas_break_rhi.c` (glyph and texture quads are cut to the clip with UVs scaled), pinned by `test_myui_break_rhi_clip` (commit `67e42071`).

## 2. Look: JetBrains "New UI" dark (CLion 2024+)

Reference values (JetBrains Int UI dark palette; approximations from the public theme, no assets copied):

| Role | Colour |
|---|---|
| window / tool window background | `#2B2D30` |
| editor/content background (viewport surround, lists, consoles) | `#1E1F22` |
| panel separators / borders | `#393B40` (strong `#43454A`) |
| primary text | `#DFE1E5`; secondary text `#9DA0A8`; disabled `#6F737A` |
| default button | bg `#2B2D30`, border `#4E5157`, hover bg `#393B40`, pressed `#43454A` |
| primary (accent) button | bg `#3574F0`, hover `#4682FA`, pressed `#2E5FCC`, text white |
| input field | bg `#1E1F22`, border `#4E5157`, focused border `#3574F0` |
| list row | bg transparent on `#1E1F22`; hover `#2E436E` (selection tint); selected `#2E436E` |
| status bar | bg `#2B2D30`, text `#9DA0A8` |
| corner radius | buttons and inputs 4 px; panels 0 |
| font | UI 13 px (scaled by the platform DPI as today) |

## 3. Mechanism

- Editor owns a CSS sheet (`engine/apps/editor/editor_theme.{h,c}`, the sheet as a C string so no asset path is needed) applied with `my_window_set_css_style` right after the shell is built; no new styling engine. Selectors use widget types (`button`, `label`, `edit`, `list_view`, `text_area`, `window`) and the editor's existing widget names (`#editor-toolbar`, `#editor-status`, `#editor-console`, `#editor-outliner-panel`, ...), plus a `.primary` class for the accent "Add" button.
- myui gaps that block the look, fixed in myui with tests:
  1. `button` strokes a square 1 px rect around a rounded fill (visible corners) and ignores `border_width`: stroke a rounded rect of the same radius inset by half the line, with `border_width` (0 = no border).
  2. Plain containers (`my_widget_create` panels) paint nothing, so panel backgrounds cannot be themed: the base widget paints `bg_color` when a theme rule sets it (no rule = transparent, unchanged behaviour).
  3. `label` paints its background over the panel even when the theme gives it none; with (2), labels default to transparent (bg only when set).
- Language switch and font chain unchanged.

## 4. Testing

- myui unit tests (soft LCD canvas): rounded button border pixels stay inside the rounded shape (corner pixel = parent background), `border_width: 0` draws no border, container with `bg_color` paints it and without paints nothing, label without bg leaves the parent colour.
- `test_editor_shell`: the editor sheet parses with zero warnings in strict mode and the toolbar/status/console resolve the expected colours through `my_widget_style_get_color`.
- Live: `--input-script` screenshots on Vulkan and OpenGL; sample the regions against the palette.

## 4a. Selected outliner row

The outliner row bound to the selected entity carries style class `selected` (set in `editor_adapter_bind_row` and re-marked on a row click, which does not rebind), styled `#editor-outliner-row.selected` = selection tint `#2E436E`, white text. Pinned by `test_editor_shell` `outliner_highlights_the_selected_row`; live (Vulkan, `--input-script`) the clicked row samples `#2E436E` and the other `#1E1F22`.

## 4b. Focus ring and draw order

- myui edits paint the focused state from the hover slot (`my_edit.h`), so the sheet's `edit:hover` border is the accent `#3574F0` (focus ring). Pinned by `palette_paints_with_focused_edit_ring` (soft LCD).
- Live, Ctrl+P showed no palette: the Break RHI canvas flushed every solid (fills, text) and then every image, so the 3D viewport blit covered the palette painted after it. The canvas now records runs in issue order and replays them (`later_fill_covers_an_earlier_image`, red before on Vulkan and OpenGL).

## 4c. Light theme and switching (2026-10-29)

`editor_theme.c` holds a second sheet, JetBrains New UI light (window `#F7F8FA`, content `#FFFFFF`, text `#1F1F1F`, secondary `#6C707E`, borders `#D3D5DB`, selection `#D4E2FF`; accent `#3574F0` unchanged). `break_editor_shell_set_theme(shell, light)` or the palette commands `Theme: Light` / `Theme: Dark` (`主题：浅色` / `主题：深色`) apply it and repaint; self-painting widgets read `break_editor_theme_content_bg()`. Pinned by `theme_switches_between_dark_and_light`; live on Vulkan and OpenGL the top colours are `#FFFFFF`/`#F7F8FA`/`#D3D5DB` in light and return to `#1E1F22`/`#2B2D30`/`#393B40` with no light pixel left. Persisted since 2026-10-29 (see `editor_settings.h`).

## 5. Not delivered

Icons and gutters. Persisting theme/language/tabs: delivered 2026-10-29 (`apps/editor/editor_settings.h`). Tool-window tabs: delivered 2026-10-29 (`2026-10-29-editor-tool-window-tabs-design.md`). Fonts: **superseded 2026-10-29** — JetBrains Mono Regular 2.304 and Noto Sans SC are bundled at `engine/assets/fonts/` (OFL) and lead the font chain (see `docs/design/editor_i18n.md`).
