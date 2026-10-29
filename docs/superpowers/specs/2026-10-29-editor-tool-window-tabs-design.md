# Editor tool-window tabs — design (2026-10-29)

## Goal

CLion groups tool windows behind tab strips instead of tiling every panel. The editor tiles five diagnostics/console panels into two small areas (bottom row: console + Lua side by side; right column: profiler h:30% + a h:20% row split between network and render), so each one is cramped. Put each area behind a tab strip so the active panel gets the whole area.

## Layout

- Bottom area (`editor-bottom`, h:96 → h:160): tab strip `editor-bottom-tabs` (h:26) with `Console` / `Lua`, then the active page fills the rest. Pages: `editor-console` (text area), `editor-lua-panel`.
- Right diagnostics area (`editor-diag-row`, keeps the name; moves from h:20% to h:45% of the right column and absorbs the profiler's 30%): tab strip `editor-diag-tabs` with `Profiler` / `Network` / `Render`; pages `editor-profiler-panel`, `editor-network-panel`, `editor-render-panel`. The inspector stays above with h:1f.

Inactive pages are hidden (`visible = false`), not destroyed: panels keep ticking and their weak list pointers stay valid, so the existing panel modules and their 4 Hz refresh/teardown contracts are unchanged. Each panel build already sets its own layout params; the shell overrides them to `w:100% h:1f` after the build.

## Tabs

A tab is a myui button named `editor-tab` with class `active` on the selected one (theme: active = content background + 2 px accent underline approximated by an accent bottom border colour; inactive = window background, secondary text). Clicking a tab shows its page and hides the others. Labels are translated (`Console`/`控制台`, `Lua`, `Profiler`/`性能分析`, `Network`/`网络`, `Render`/`渲染`) and retranslated on language switch.

API (shell): `break_editor_shell_select_tab(shell, area, index)` and `break_editor_shell_active_tab(shell, area)` with `area` 0 = bottom, 1 = diagnostics; out-of-range is rejected. Defaults: Console, Profiler.

## Testing

- Shell tests: both strips exist with the right tab count and labels; only the active page is visible; clicking (real pointer dispatch) a tab switches page and the `active` class; the active page fills the area under the strip; language switch retranslates tab labels; existing layout tests updated to the new placement (network/render are pages of `editor-diag-row`, profiler too).
- Live: input-script clicks each tab on Vulkan and OpenGL; screenshots show the page content change.

## Not covered

Drag-to-reorder, detaching tool windows, collapsing an area, persisting the active tab.
