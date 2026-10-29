#pragma once
/* Editor UI font discovery (design: docs/design/editor_i18n.md §Fonts).
 *
 * The editor used to name two Debian-layout font files; on other systems
 * neither existed and myui fell back to its built-in 8x8 ASCII bitmap font,
 * so every non-ASCII character rendered as the same placeholder block.
 *
 * break_editor_font_candidates builds an ordered, existing-files-only font
 * chain for the requested UI language: fontconfig matches first (when the
 * build has fontconfig), then a table of well-known install locations for
 * Fedora/RHEL, Debian/Ubuntu, Arch, openSUSE, Windows and macOS. myui routes
 * each codepoint to the first face that has it, so order decides which face
 * draws shared glyphs (Latin, punctuation). The bundled CLion face
 * (JetBrains Mono Regular) always leads the chain, for every language; the
 * system faces follow (zh-CN puts a CJK face before the other Latin faces,
 * other languages the reverse), so Chinese still falls through to CJK.
 * Duplicates are dropped; paths that do not fit the caller's storage are
 * skipped, never truncated. */

#include <core/types.h>

#include <editor/editor_i18n.h>

#include "myr/my_font.h"

#define BREAK_EDITOR_FONT_MAX_CANDIDATES 6u
#define BREAK_EDITOR_FONT_PATH_MAX 512u

typedef struct {
    my_font_source_t sources[BREAK_EDITOR_FONT_MAX_CANDIDATES];
    char paths[BREAK_EDITOR_FONT_MAX_CANDIDATES][BREAK_EDITOR_FONT_PATH_MAX];
    usize count;
    bool has_cjk; /* at least one candidate is a CJK face */
} BreakEditorFontChain;

/* Bundled CLion UI face: JetBrains Mono Regular (OFL, see
 * engine/assets/fonts/OFL.txt). Candidate locations, in order:
 * $BREAK_ASSET_DIR/assets/fonts/..., the executable's own directory, its
 * parent + "engine/" (repo build tree), the cwd, and the cwd + "engine/".
 * Returns true and writes the path when candidate `index` exists (the file
 * itself may still be absent — chain_add checks). */
#define BREAK_EDITOR_BUNDLED_FONT_PATHS 5u
bool break_editor_bundled_font_path(usize index, char *out, usize cap);

/* Same candidate locations for the bundled Chinese face, Noto Sans SC
 * (engine/assets/fonts/NotoSansSC-VF.ttf + NotoSansSC-OFL.txt) — the family
 * the CLion Chinese language pack uses. Added right after JetBrains Mono in
 * every language, so Chinese renders without any host CJK font. */
bool break_editor_bundled_cjk_font_path(usize index, char *out, usize cap);

/* `root` prefixes every built-in table path (NULL or "" = the real file
 * system); tests point it at a temporary tree. `use_fontconfig` lets tests
 * exercise the table alone. Returns the candidate count (0 = nothing found;
 * the caller should warn that the bitmap fallback will be used). */
usize break_editor_font_candidates(BreakEditorLang lang, const char *root,
                                   bool use_fontconfig,
                                   BreakEditorFontChain *out);

/* Removes every "--lang <tag>" / "--lang=<tag>" from argv in place (so the
 * remaining arguments keep their existing meaning) and parses the last one.
 * Returns false and writes a bounded message to `err` when a --lang has no
 * value or an unsupported tag; *argc is then unchanged. When no --lang is
 * given, *out_lang is set from break_editor_i18n_lang_from_env(). */
bool break_editor_cli_take_lang(int *argc, char **argv,
                                BreakEditorLang *out_lang, char *err,
                                usize err_cap);
