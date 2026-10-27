# Editor fonts and languages

Status: delivered 2026-10-27, branch `sdd/editor-i18n`. Design `docs/superpowers/specs/2026-10-27-editor-i18n-design.md`, plan `docs/superpowers/plans/2026-10-27-editor-i18n.md`.

## 1. What was wrong

All editor text looked garbled. The editor named two Debian-only font files (`/usr/share/fonts/opentype/noto/NotoSansCJK-Regular.ttc`, `/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf`). On other systems (this host is Fedora) neither exists, and `break_ui_init_with_fonts` silently fell back to myui's built-in 8x8 bitmap font: ASCII 32..126 only, scaled up to 16 px. ASCII drew as coarse blocks and every other character (Chinese, `—`, `…`) as the same placeholder. Nothing was logged. A live process confirmed `ui->font->vtable == s_bitmap_vtable`; after the fix it is `s_chain_vtable`.

Separately, ~30 comment lines in `engine/src/rhi/rhi.h` had `—`/`→` saved as UTF-8 that had been read as GBK. They are restored from the clean lines in git history.

## 2. Fonts

`engine/apps/editor/editor_fonts.{h,c}`, `break_editor_font_candidates(lang, root, use_fontconfig, &chain)`:

1. fontconfig best match for the script (`zh-cn` for CJK, `en` for Latin), kept only if the match really covers that language. fontconfig is optional: CMake links it when `pkg-config fontconfig` is found (Linux).
2. Otherwise the first existing file from a table of known install locations: Fedora/RHEL (`google-noto-sans-cjk-vf-fonts`, `google-droid-sans-fonts`, `dejavu-sans-fonts`, `liberation-sans-fonts`), Debian/Ubuntu (`opentype/noto`, `truetype/dejavu`, `truetype/liberation`, `truetype/wqy`), Arch (`noto-cjk`, `TTF`), openSUSE, Windows (`segoeui`, `msyh`, `simsun`) and macOS (`Helvetica`, `PingFang`, `STHeiti`).

One face per script, at most six candidates, duplicates dropped, paths that do not fit are skipped rather than truncated. myui routes each codepoint to the first face that has it, so order matters: zh-CN puts the CJK face first (Chinese punctuation and Latin inside Chinese text use it), other languages put the Latin face first.

If nothing is found the editor prints `no UI font found ...`; if no CJK face is found it prints `no CJK font found; Chinese text will not render`. `break_ui_init_with_fonts` now logs a warning whenever it uses the bitmap fallback. Install Noto Sans CJK to get both scripts.

## 3. Languages

`engine/src/editor/editor_i18n.{h,c}` + `editor_i18n_tables.c` (in `break_editor`):

- Keys are the `BreakEditorTr` enum; `break_editor_tr(key)` returns the current language's text, falling back to en-US and then `"?"`. Never NULL.
- Languages: `en-US`, `zh-CN`.
- Startup language: `--lang <tag>` (or `--lang=<tag>`), else the first parseable of `BREAK_LANG`, `LC_ALL`, `LC_MESSAGES`, `LANG`, else en-US. Tags accept BCP 47 and POSIX forms (`zh-CN`, `zh_CN.UTF-8`, `zh`, `en_US.utf8`, `C`, `POSIX`). An unsupported `--lang` exits with code 2.
- Runtime switch: command palette (`Ctrl+P`) entries `Language: English` and `Language: 中文 (Chinese)` (in Chinese: `语言：English（英文）`, `语言：中文`), or `break_editor_shell_set_language(shell, lang)`. The toolbar, panel titles, tool label, status bar, inspector, palette rows and filter, and the render-debugger reload row change at once. The palette filters by the current language's command names.
- Translated: all editor chrome and editor console messages, including scene and shader hot-reload messages.
- Not translated: entity and component names (document data), file paths, Lua console echo/output (`lua| ...`), engine `LOG_*` output, remote protocol text. Console lines already written keep the language they were written in; the switch itself is logged in the new language.
- The current language is one process-wide value used only on the editor UI thread.

### Adding a language

1. Add a value before `BREAK_EDITOR_LANG_COUNT` in `editor_i18n.h`, a tag and native name in `editor_i18n.c`, and a row in `editor_i18n_tables.c`.
2. Teach `break_editor_i18n_parse_lang` its language subtag.
3. Add a palette command if it should be selectable at runtime.
4. `test_editor_i18n` then fails until every key is filled, valid UTF-8, different from en-US, and uses the same printf conversions in the same order as en-US.
5. Add the script's fonts to the table in `editor_fonts.c` if they are not Latin or CJK.

## 4. Tests and evidence

- `test_editor_i18n` (7): table coverage, UTF-8 validity, translation check, format-conversion parity, language switch bounds, tags/names, tag parsing, environment priority. Mutations (an untranslated key, a `%s`→`%u` change in zh-CN) each fail it.
- `test_editor_fonts` (6): Fedora and Debian layouts simulated under a temporary root (order by language), Latin-only system reports no CJK, empty/over-long roots, real-system candidates exist and are unique, `--lang` argv stripping.
- `test_editor_shell` (+3; 80 Snowflake OFF, 105 ON): shell created in Chinese, runtime switch through the palette in both directions, inspector rebuilt in the new language, bounded API.
- `test_source_encoding` (CTest script): scans engine sources, shaders and docs for GBK-misreading markers; fails on the old `rhi.h`, passes now.
- Live (Fedora, Xwayland X11, NVK Vulkan and Mesa OpenGL, `editor --lang zh-CN` and `--lang en-US`): gdb confirms the vector font chain (`s_chain_vtable`, not the 8×8 bitmap) for both languages. Screenshots before and after a runtime switch (`break_editor_shell_set_language` injected with gdb at the shell tick; XTEST input does not reach the window under Xwayland) differ in every text panel; the same language on the two backends differs less than two languages on one backend in the menu row (474/806 vs 1205/1287 text-mask pixels). No OCR was run, so the glyph shapes were not read back automatically. Script and images: `.superpowers/sdd/2026-10-27-editor-i18n/live/` (ignored by git).

Not verified: Windows/macOS font paths at run time, systems without fontconfig, right-to-left or complex-shaping scripts (not supported).
