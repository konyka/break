/* BreakEditorAssets — implementation. Contract and bounds documented in
 * editor_assets.h. Pure CPU view model: the only OS interaction is
 * platform_list_dir; the editor document is not involved. All platform
 * specifics stay in platform_fs.c — this file carries no platform #ifdefs
 * ('/' separators byte-wise on every platform, same convention as
 * test_framework.h's test_tmp). */

#include <editor/editor_assets.h>

#include <editor/editor_test_hooks.h>
#include <platform/platform_fs.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct BreakEditorAssets {
    /* Normalized root (no trailing '/', except a bare "/" or drive root
     * "X:/") and the current relative directory ("" = root, segments
     * '/'-joined, only ever mutated by appending a validated single
     * segment or popping one — escaping the root is impossible). */
    char root[BREAK_EDITOR_ASSETS_PATH_CAPACITY];
    char rel[BREAK_EDITOR_ASSETS_PATH_CAPACITY];
    u32 depth;
    /* Cached one-level listing (unfiltered), dirs-first byte-wise sorted. */
    PlatformDirEntry *entries; /* [BREAK_EDITOR_ASSETS_MAX_ENTRIES] */
    u32 entry_count;
    bool truncated; /* directory held more than BREAK_EDITOR_ASSETS_MAX_ENTRIES */
    /* Filtered view: indices into entries[]. */
    u32 *visible; /* [BREAK_EDITOR_ASSETS_MAX_ENTRIES] */
    u32 visible_count;
    /* Parsed extension tokens; filter_count == 0 = filter off. */
    char filter[BREAK_EDITOR_ASSETS_FILTER_MAX_EXTS][BREAK_EDITOR_ASSETS_EXT_CAPACITY];
    u32 filter_count;
};

/* base + leaf joined with exactly one '/' separator; false when the result
 * (incl NUL) would not fit cap. */
static bool join_path(char *out, usize cap, const char *base, const char *leaf) {
    usize base_len = strlen(base);
    const char *sep = (base_len > 0 && base[base_len - 1] == '/') ? "" : "/";
    int n = snprintf(out, cap, "%s%s%s", base, sep, leaf);
    return n >= 0 && (usize)n < cap;
}

static int entry_cmp(const void *pa, const void *pb) {
    const PlatformDirEntry *a = (const PlatformDirEntry *)pa;
    const PlatformDirEntry *b = (const PlatformDirEntry *)pb;
    if (a->is_dir != b->is_dir) return a->is_dir ? -1 : 1;
    return strcmp(a->name, b->name);
}

static bool passes_filter(const BreakEditorAssets *a, const PlatformDirEntry *e) {
    if (e->is_dir) return true; /* directories always pass (navigation) */
    if (a->filter_count == 0) return true;
    /* Extension = bytes after the LAST '.'; a leading or trailing dot
     * means "no extension" (dotfiles, "note", "x." never match). */
    const char *dot = strrchr(e->name, '.');
    if (!dot || dot == e->name || dot[1] == '\0') return false;
    const char *ext = dot + 1;
    for (u32 i = 0; i < a->filter_count; i++) {
        if (strcmp(ext, a->filter[i]) == 0) return true;
    }
    return false;
}

static void recompute_visible(BreakEditorAssets *a) {
    a->visible_count = 0;
    for (u32 i = 0; i < a->entry_count; i++) {
        if (passes_filter(a, &a->entries[i])) {
            a->visible[a->visible_count++] = i;
        }
    }
}

/* Re-reads the current directory into the cache and re-sorts/re-filters.
 * Allocates nothing. On false the previous counts are left in place. */
static bool assets_refresh(BreakEditorAssets *a) {
    char dir[BREAK_EDITOR_ASSETS_PATH_CAPACITY];
    if (a->rel[0] == '\0') {
        usize root_len = strlen(a->root);
        memcpy(dir, a->root, root_len + 1); /* bounded at create */
    } else if (!join_path(dir, sizeof(dir), a->root, a->rel)) {
        return false;
    }
    u32 total = 0;
    if (!platform_list_dir(dir, a->entries, BREAK_EDITOR_ASSETS_MAX_ENTRIES, &total)) {
        return false;
    }
    a->entry_count =
        total < BREAK_EDITOR_ASSETS_MAX_ENTRIES ? total : BREAK_EDITOR_ASSETS_MAX_ENTRIES;
    a->truncated = total > BREAK_EDITOR_ASSETS_MAX_ENTRIES;
    /* Names within one directory level are unique, so the comparator is a
     * total order and the sort result deterministic. */
    qsort(a->entries, a->entry_count, sizeof(a->entries[0]), entry_cmp);
    recompute_visible(a);
    return true;
}

BreakEditorAssets *break_editor_assets_create(const char *root_path) {
    if (!root_path) return NULL;
    usize len = strlen(root_path);
    if (len == 0 || len + 1 > BREAK_EDITOR_ASSETS_PATH_CAPACITY) return NULL;
    char root[BREAK_EDITOR_ASSETS_PATH_CAPACITY];
    memcpy(root, root_path, len + 1);
    /* Strip trailing '/', but keep a bare "/" (and a drive root "X:/"). */
    while (len > 1 && root[len - 1] == '/' && root[len - 2] != ':') {
        root[--len] = '\0';
    }
    /* Root must exist and be a directory: a counting probe rejects missing
     * paths and regular files (opendir/FindFirstFile fail on both). A
     * symlinked root directory IS accepted here (the probe follows it) —
     * the no-follow policy governs listed ENTRIES, not the configured
     * root. */
    u32 probe = 0;
    if (!platform_list_dir(root, NULL, 0, &probe)) return NULL;

    /* Exactly 3 editor-owned allocations (pinned by the OOM sweep). */
    BreakEditorAssets *a = break_editor_test_calloc(sizeof(*a));
    if (!a) return NULL;
    a->entries =
        break_editor_test_calloc(sizeof(PlatformDirEntry) * BREAK_EDITOR_ASSETS_MAX_ENTRIES);
    if (!a->entries) {
        free(a);
        return NULL;
    }
    a->visible = break_editor_test_calloc(sizeof(u32) * BREAK_EDITOR_ASSETS_MAX_ENTRIES);
    if (!a->visible) {
        free(a->entries);
        free(a);
        return NULL;
    }
    memcpy(a->root, root, len + 1);
    if (!assets_refresh(a)) { /* tree vanished between probe and refresh */
        break_editor_assets_destroy(a);
        return NULL;
    }
    return a;
}

void break_editor_assets_destroy(BreakEditorAssets *assets) {
    if (!assets) return;
    free(assets->visible);
    free(assets->entries);
    free(assets);
}

bool break_editor_assets_enter(BreakEditorAssets *assets, const char *rel_subdir) {
    if (!assets || !rel_subdir || rel_subdir[0] == '\0') return false;
    if (strcmp(rel_subdir, "..") == 0) return break_editor_assets_up(assets);
    /* Single relative segment only: no absolute paths, no '/' anywhere. */
    if (rel_subdir[0] == '/' || strchr(rel_subdir, '/') != NULL) return false;
    if (strcmp(rel_subdir, ".") == 0) return false;
    usize name_len = strlen(rel_subdir);
    if (name_len >= BREAK_EDITOR_ASSETS_NAME_CAPACITY) return false;
    /* The target must be a directory in the current lstat-classified
     * listing — regular files and symlinks (is_dir == false) are never
     * enterable. */
    bool found = false;
    for (u32 i = 0; i < assets->entry_count; i++) {
        if (assets->entries[i].is_dir && strcmp(assets->entries[i].name, rel_subdir) == 0) {
            found = true;
            break;
        }
    }
    if (!found) return false;
    if (assets->depth >= BREAK_EDITOR_ASSETS_MAX_DEPTH) return false;

    char new_rel[BREAK_EDITOR_ASSETS_PATH_CAPACITY];
    if (assets->rel[0] == '\0') {
        memcpy(new_rel, rel_subdir, name_len + 1); /* 256 << 1024 */
    } else if (!join_path(new_rel, sizeof(new_rel), assets->rel, rel_subdir)) {
        return false;
    }
    /* The joined absolute directory path must stay within the path bound. */
    char dir[BREAK_EDITOR_ASSETS_PATH_CAPACITY];
    if (!join_path(dir, sizeof(dir), assets->root, new_rel)) return false;

    char old_rel[BREAK_EDITOR_ASSETS_PATH_CAPACITY];
    usize old_len = strlen(assets->rel);
    memcpy(old_rel, assets->rel, old_len + 1);
    u32 old_depth = assets->depth;

    memcpy(assets->rel, new_rel, strlen(new_rel) + 1);
    assets->depth++;
    if (!assets_refresh(assets)) {
        /* Directory vanished between listing and enter: revert. */
        memcpy(assets->rel, old_rel, old_len + 1);
        assets->depth = old_depth;
        if (!assets_refresh(assets)) {
            /* The old directory vanished too — stay coherent but empty. */
            assets->entry_count = 0;
            assets->visible_count = 0;
            assets->truncated = false;
        }
        return false;
    }
    return true;
}

bool break_editor_assets_up(BreakEditorAssets *assets) {
    if (!assets) return false;
    if (assets->depth == 0) return true; /* clamped at the root */
    char *slash = strrchr(assets->rel, '/');
    if (slash) {
        *slash = '\0';
    } else {
        assets->rel[0] = '\0';
    }
    assets->depth--;
    if (!assets_refresh(assets)) {
        /* Parent vanished (tree deleted under us): fall back to a coherent
         * empty root state. */
        assets->rel[0] = '\0';
        assets->depth = 0;
        assets->entry_count = 0;
        assets->visible_count = 0;
        assets->truncated = false;
        (void)assets_refresh(assets);
        return false;
    }
    return true;
}

usize break_editor_assets_count(const BreakEditorAssets *assets) {
    return assets ? assets->visible_count : 0;
}

bool break_editor_assets_entry_at(const BreakEditorAssets *assets, usize i,
                                  const char **out_name, bool *out_is_dir) {
    if (!assets || !out_name || !out_is_dir || i >= assets->visible_count) return false;
    const PlatformDirEntry *e = &assets->entries[assets->visible[i]];
    *out_name = e->name;
    *out_is_dir = e->is_dir;
    return true;
}

void break_editor_assets_set_filter(BreakEditorAssets *assets, const char *extensions_csv) {
    if (!assets) return;
    assets->filter_count = 0;
    if (extensions_csv && extensions_csv[0] != '\0') {
        const char *p = extensions_csv;
        while (*p && assets->filter_count < BREAK_EDITOR_ASSETS_FILTER_MAX_EXTS) {
            const char *comma = strchr(p, ',');
            usize len = comma ? (usize)(comma - p) : strlen(p);
            /* Empty segments skipped; over-long tokens dropped (bounded). */
            if (len > 0 && len < BREAK_EDITOR_ASSETS_EXT_CAPACITY) {
                memcpy(assets->filter[assets->filter_count], p, len);
                assets->filter[assets->filter_count][len] = '\0';
                assets->filter_count++;
            }
            if (!comma) break;
            p = comma + 1;
        }
    }
    recompute_visible(assets);
}

const char *break_editor_assets_current_rel(const BreakEditorAssets *assets) {
    return assets ? assets->rel : "";
}

bool break_editor_assets_abs_path(const BreakEditorAssets *assets, usize i,
                                  char *out, usize cap) {
    if (!assets || !out || cap == 0 || i >= assets->visible_count) return false;
    const char *name = assets->entries[assets->visible[i]].name;
    char dir[BREAK_EDITOR_ASSETS_PATH_CAPACITY];
    if (assets->rel[0] == '\0') {
        usize root_len = strlen(assets->root);
        memcpy(dir, assets->root, root_len + 1);
    } else if (!join_path(dir, sizeof(dir), assets->root, assets->rel)) {
        return false;
    }
    return join_path(out, cap, dir, name);
}
