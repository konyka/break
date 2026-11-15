#include <editor/editor_plugin_manifest.h>

#include <string.h>

typedef struct ManifestCursor {
    const char *p;
    const char *end;
} ManifestCursor;

static bool manifest_blank(char c)
{
    return c == ' ' || c == '\t';
}

static void manifest_skip_blanks(ManifestCursor *c)
{
    while (c->p < c->end && manifest_blank(*c->p)) {
        c->p++;
    }
}

static usize manifest_token(ManifestCursor *c, const char **out)
{
    *out = c->p;
    while (c->p < c->end && !manifest_blank(*c->p)) {
        c->p++;
    }
    return (usize)(c->p - *out);
}

static int manifest_hex(char c)
{
    if (c >= '0' && c <= '9') return c - '0';
    if (c >= 'a' && c <= 'f') return c - 'a' + 10;
    if (c >= 'A' && c <= 'F') return c - 'A' + 10;
    return -1;
}

static bool manifest_absolute(const char *path, usize length)
{
    if (length >= 1u && (path[0] == '/' || path[0] == '\\')) return true;
    return length >= 2u && path[1] == ':' &&
           ((path[0] >= 'A' && path[0] <= 'Z') || (path[0] >= 'a' && path[0] <= 'z'));
}

static BreakEditorPluginManifestStatus manifest_parse_entry(ManifestCursor *c,
                                                            const char *base_dir,
                                                            BreakEditorPluginManifestEntry *entry)
{
    const char *token = NULL;
    usize length = manifest_token(c, &token);
    if (length != 6u || memcmp(token, "plugin", 6u) != 0) {
        return BREAK_EDITOR_PLUGIN_MANIFEST_SYNTAX;
    }

    manifest_skip_blanks(c);
    length = manifest_token(c, &token);
    if (length == 0u || length >= BREAK_EDITOR_PLUGIN_MANIFEST_BUILD_ID_CAPACITY) {
        return BREAK_EDITOR_PLUGIN_MANIFEST_BAD_BUILD_ID;
    }
    for (usize i = 0u; i < length; ++i) {
        u8 byte = (u8)token[i];
        if (byte < 0x21u || byte > 0x7eu) return BREAK_EDITOR_PLUGIN_MANIFEST_BAD_BUILD_ID;
    }
    memcpy(entry->build_id, token, length);
    entry->build_id[length] = '\0';

    manifest_skip_blanks(c);
    length = manifest_token(c, &token);
    if (length != 64u) return BREAK_EDITOR_PLUGIN_MANIFEST_BAD_HASH;
    for (usize i = 0u; i < 32u; ++i) {
        int hi = manifest_hex(token[2u * i]);
        int lo = manifest_hex(token[2u * i + 1u]);
        if (hi < 0 || lo < 0) return BREAK_EDITOR_PLUGIN_MANIFEST_BAD_HASH;
        entry->sha256[i] = (u8)((hi << 4) | lo);
    }

    manifest_skip_blanks(c);
    const char *path = c->p;
    const char *path_end = c->end;
    while (path_end > path && manifest_blank(path_end[-1])) {
        path_end--;
    }
    length = (usize)(path_end - path);
    if (length == 0u) return BREAK_EDITOR_PLUGIN_MANIFEST_BAD_PATH;
    for (usize i = 0u; i < length; ++i) {
        u8 byte = (u8)path[i];
        if (byte < 0x20u || byte == 0x7fu) return BREAK_EDITOR_PLUGIN_MANIFEST_BAD_PATH;
    }
    usize base_length = 0u;
    bool separator = false;
    if (base_dir && base_dir[0] != '\0' && !manifest_absolute(path, length)) {
        base_length = strlen(base_dir);
        char last = base_dir[base_length - 1u];
        separator = last != '/' && last != '\\';
    }
    usize total = base_length + (separator ? 1u : 0u) + length;
    if (total >= BREAK_EDITOR_PLUGIN_MANIFEST_PATH_CAPACITY) {
        return BREAK_EDITOR_PLUGIN_MANIFEST_BAD_PATH;
    }
    memcpy(entry->path, base_dir ? base_dir : "", base_length);
    if (separator) entry->path[base_length] = '/';
    memcpy(entry->path + base_length + (separator ? 1u : 0u), path, length);
    entry->path[total] = '\0';
    return BREAK_EDITOR_PLUGIN_MANIFEST_OK;
}

BreakEditorPluginManifestStatus break_editor_plugin_manifest_parse(
    const char *text, usize size, const char *base_dir, BreakEditorPluginManifest *out,
    u32 *error_line)
{
    if (error_line) *error_line = 0u;
    if (!text || !out) return BREAK_EDITOR_PLUGIN_MANIFEST_INVALID;
    out->count = 0u;

    const char *p = text;
    const char *end = text + size;
    u32 line = 0u;
    while (p < end) {
        const char *line_end = memchr(p, '\n', (usize)(end - p));
        const char *next = line_end ? line_end + 1 : end;
        if (!line_end) line_end = end;
        line++;
        BreakEditorPluginManifestStatus status = BREAK_EDITOR_PLUGIN_MANIFEST_OK;
        if (memchr(p, '\0', (usize)(line_end - p))) {
            status = BREAK_EDITOR_PLUGIN_MANIFEST_SYNTAX;
        } else {
            ManifestCursor c = {p, line_end};
            if (c.end > c.p && c.end[-1] == '\r') c.end--;
            manifest_skip_blanks(&c);
            if (c.p < c.end && *c.p != '#') {
                if (out->count == BREAK_EDITOR_PLUGIN_MANIFEST_MAX) {
                    status = BREAK_EDITOR_PLUGIN_MANIFEST_FULL;
                } else {
                    BreakEditorPluginManifestEntry *entry = &out->entries[out->count];
                    status = manifest_parse_entry(&c, base_dir, entry);
                    for (u32 i = 0u; status == BREAK_EDITOR_PLUGIN_MANIFEST_OK && i < out->count;
                         ++i) {
                        if (strcmp(out->entries[i].path, entry->path) == 0) {
                            status = BREAK_EDITOR_PLUGIN_MANIFEST_DUPLICATE;
                        }
                    }
                    if (status == BREAK_EDITOR_PLUGIN_MANIFEST_OK) out->count++;
                }
            }
        }
        if (status != BREAK_EDITOR_PLUGIN_MANIFEST_OK) {
            out->count = 0u;
            if (error_line) *error_line = line;
            return status;
        }
        p = next;
    }
    return BREAK_EDITOR_PLUGIN_MANIFEST_OK;
}

bool break_editor_plugin_manifest_load_all(const BreakEditorPluginManifest *manifest,
                                           BreakEditorPluginHost *host,
                                           BreakEditorPluginManifestLoadFn load_fn, void *user,
                                           BreakEditorPluginManifestReport *report)
{
    if (!manifest || !host || !load_fn || !report) return false;
    memset(report, 0, sizeof(*report));
    u32 count = manifest->count < BREAK_EDITOR_PLUGIN_MANIFEST_MAX
                    ? manifest->count
                    : BREAK_EDITOR_PLUGIN_MANIFEST_MAX;
    for (u32 i = 0u; i < count; ++i) {
        u32 owner = break_editor_plugin_host_begin_load(host);
        if (owner == 0u) {
            report->failed++;
            continue;
        }
        bool loaded = load_fn(user, &manifest->entries[i]);
        (void)break_editor_plugin_host_end_load(host, loaded);
        if (loaded) {
            report->owners[i] = owner;
            report->loaded++;
        } else {
            report->failed++;
        }
    }
    return true;
}
