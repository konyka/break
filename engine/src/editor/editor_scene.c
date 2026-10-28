/* BreakEditorDoc scene persistence — see editor_scene.h for the full
 * contract (two-file save, REPLACE load via staging-world swap, index
 * compaction, sidecar fallback rules, dirty/undo semantics, tmp+rename). */

#include <editor/editor_scene.h>

#include <editor/editor_internal.h>
#include <editor/editor_test_hooks.h>

#include <core/log.h>
#include <scene/scene_serial.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ---------------------------------------------------------------- */
/* Paths                                                            */
/* ---------------------------------------------------------------- */

/* Builds the sidecar path and both tmp paths. Bounded: every result must
 * fit BREAK_EDITOR_SCENE_PATH_CAPACITY bytes including the NUL. */
static bool scene_paths(const char *path, char *bscn_tmp, char *sidecar,
                        char *sidecar_tmp) {
    if (!path) return false;
    int n = snprintf(sidecar, BREAK_EDITOR_SCENE_PATH_CAPACITY, "%s%s", path,
                     BREAK_EDITOR_SIDECAR_SUFFIX);
    if (n < 0 || (usize)n >= BREAK_EDITOR_SCENE_PATH_CAPACITY) return false;
    n = snprintf(bscn_tmp, BREAK_EDITOR_SCENE_PATH_CAPACITY, "%s.tmp", path);
    if (n < 0 || (usize)n >= BREAK_EDITOR_SCENE_PATH_CAPACITY) return false;
    n = snprintf(sidecar_tmp, BREAK_EDITOR_SCENE_PATH_CAPACITY, "%s.tmp",
                 sidecar);
    if (n < 0 || (usize)n >= BREAK_EDITOR_SCENE_PATH_CAPACITY) return false;
    return true;
}

/* Bounded sidecar path for the load path (only file it touches). */
static bool sidecar_path(const char *path, char *out) {
    if (!path) return false;
    int n = snprintf(out, BREAK_EDITOR_SCENE_PATH_CAPACITY, "%s%s", path,
                     BREAK_EDITOR_SIDECAR_SUFFIX);
    return n >= 0 && (usize)n < BREAK_EDITOR_SCENE_PATH_CAPACITY;
}

/* rename(2) replaces atomically on POSIX; Windows rename() fails when the
 * destination exists, so remove it first (best-effort, non-atomic —
 * documented in the header). */
static bool rename_replace(const char *tmp, const char *dst) {
#if defined(_WIN32)
    remove(dst);
#endif
    return rename(tmp, dst) == 0;
}

/* ---------------------------------------------------------------- */
/* Sidecar write                                                    */
/* ---------------------------------------------------------------- */

static bool write_all(FILE *fp, const char *s, usize n, u64 *written) {
    if (n && fwrite(s, 1, n, fp) != n) return false;
    *written += n; /* bounded inputs: total provably <= 4 MiB + entry */
    return true;
}

/* '"' and '\' get a backslash escape, bytes < 0x20 become \u00XX, all other
 * bytes (including UTF-8 continuation bytes) pass through. name is a
 * NUL-terminated 128-byte-bounded buffer (slot storage); the escaped output
 * is at most 127*6 = 762 bytes + NUL. Returns the escaped length. */
static usize escape_name(const char name[BREAK_EDITOR_NAME_CAPACITY],
                         char *out) {
    static const char hex[] = "0123456789abcdef";
    usize o = 0;
    for (usize i = 0; i < BREAK_EDITOR_NAME_CAPACITY && name[i]; i++) {
        u8 c = (u8)name[i];
        if (c == '"' || c == '\\') {
            out[o++] = '\\';
            out[o++] = (char)c;
        } else if (c < 0x20u) {
            out[o++] = '\\';
            out[o++] = 'u';
            out[o++] = '0';
            out[o++] = '0';
            out[o++] = hex[c >> 4];
            out[o++] = hex[c & 0xFu];
        } else {
            out[o++] = (char)c;
        }
    }
    out[o] = '\0';
    return o;
}

/* Streams the sidecar; fails bounded (false, tmp removed by caller) when the
 * exact byte count would exceed BREAK_EDITOR_SIDECAR_MAX_BYTES. Never
 * allocates. Entries are written in ascending world-index order; the "index"
 * field is the dense 1-based rank among live entities, which is exactly the
 * index the entity will have after a load (index compaction, see header). */
static bool sidecar_write(BreakEditorDoc *doc, const char *path) {
    FILE *fp = fopen(path, "wb");
    if (!fp) return false;
    u64 written = 0;
    bool ok = write_all(fp, "{\"version\":1,\"entities\":[",
                        sizeof("{\"version\":1,\"entities\":[") - 1u, &written);
    bool first = true;
    u32 rank = 0;
    for (u32 i = 1; i < ECS_MAX_ENTITIES && ok; i++) {
        u32 gen = doc->slots[i].generation;
        if (!gen) continue;
        /* Defensive: emit exactly the entities the BSCN will carry. The doc
         * invariant already makes slots == live entities; if that ever
         * desyncs, skipping here keeps sidecar and BSCN consistent (the
         * missing names just fall back to generated on load). */
        Entity e;
        e.index = i;
        e.generation = gen;
        if (!world_entity_exists(doc->world, e)) continue;
        rank++;

        char esc[BREAK_EDITOR_NAME_CAPACITY * 6u + 1u];
        usize elen = escape_name(doc->slots[i].name, esc);
        /* `,{"index":4294967295,"generation":4294967295,"name":"` is 54
         * bytes worst case — 64 is provably sufficient. */
        char fixed[64];
        int flen = snprintf(fixed, sizeof(fixed),
                            "%s{\"index\":%u,\"generation\":%u,\"name\":\"",
                            first ? "" : ",", rank, gen);
        if (flen <= 0 || (usize)flen >= sizeof(fixed)) {
            ok = false;
            break;
        }
        u64 entry_bytes = (u64)flen + (u64)elen + 2u /* quote + brace */;
        if (written + entry_bytes + 2u /* "]}" footer */ >
            (u64)BREAK_EDITOR_SIDECAR_MAX_BYTES) {
            LOG_WARN("editor: sidecar would exceed the %u-byte cap; save "
                     "aborted before touching '%s'",
                     (unsigned)BREAK_EDITOR_SIDECAR_MAX_BYTES, path);
            ok = false;
            break;
        }
        ok = write_all(fp, fixed, (usize)flen, &written) &&
             write_all(fp, esc, elen, &written) &&
             write_all(fp, "\"}", 2, &written);
        first = false;
    }
    if (ok) ok = write_all(fp, "]}", 2, &written);
    if (ferror(fp)) ok = false;
    if (fclose(fp) != 0) ok = false;
    return ok;
}

/* ---------------------------------------------------------------- */
/* Sidecar read (cursor parser over a capped in-memory buffer)      */
/* ---------------------------------------------------------------- */

typedef struct {
    const char *p;
    const char *end;
} SidecarCursor;

static void sc_skip_ws(SidecarCursor *c) {
    while (c->p < c->end &&
           (*c->p == ' ' || *c->p == '\t' || *c->p == '\n' || *c->p == '\r')) {
        c->p++;
    }
}

/* Consumes `ch` (after optional whitespace) only when present. */
static bool sc_expect(SidecarCursor *c, char ch) {
    sc_skip_ws(c);
    if (c->p >= c->end || *c->p != ch) return false;
    c->p++;
    return true;
}

/* Consumes a literal token (after optional whitespace) only when present. */
static bool sc_consume(SidecarCursor *c, const char *lit) {
    sc_skip_ws(c);
    usize n = strlen(lit);
    if ((usize)(c->end - c->p) < n || memcmp(c->p, lit, n) != 0) return false;
    c->p += n;
    return true;
}

static bool sc_u32(SidecarCursor *c, u32 *out) {
    sc_skip_ws(c);
    if (c->p >= c->end || *c->p < '0' || *c->p > '9') return false;
    u64 v = 0;
    while (c->p < c->end && *c->p >= '0' && *c->p <= '9') {
        v = v * 10u + (u32)(*c->p - '0');
        if (v > UINT32_MAX) return false; /* file-controlled overflow */
        c->p++;
    }
    *out = (u32)v;
    return true;
}

static bool sc_hex4(SidecarCursor *c, u32 *out) {
    if (c->end - c->p < 4) return false;
    u32 v = 0;
    for (int i = 0; i < 4; i++) {
        char h = c->p[i];
        u32 d;
        if (h >= '0' && h <= '9') d = (u32)(h - '0');
        else if (h >= 'a' && h <= 'f') d = (u32)(h - 'a') + 10u;
        else if (h >= 'A' && h <= 'F') d = (u32)(h - 'A') + 10u;
        else return false;
        v = v * 16u + d;
    }
    c->p += 4;
    *out = v;
    return true;
}

/* Parses one JSON string into out (always fully consumed when the closing
 * quote exists). Returns false on STRUCTURAL corruption (unterminated
 * string) — the caller stops parsing. A syntactically complete but unusable
 * string (over-cap after unescape, empty, unknown escape, \u value > 0xFF,
 * raw control byte) sets *usable=false so the caller skips just this
 * entry. */
static bool sc_string(SidecarCursor *c, char out[BREAK_EDITOR_NAME_CAPACITY],
                      bool *usable) {
    memset(out, 0, BREAK_EDITOR_NAME_CAPACITY);
    *usable = false;
    sc_skip_ws(c);
    if (c->p >= c->end || *c->p != '"') return false;
    c->p++;
    usize len = 0;
    bool bad = false;
    for (;;) {
        if (c->p >= c->end) return false; /* unterminated: structural */
        u8 ch = (u8)*c->p;
        if (ch == '"') {
            c->p++;
            break;
        }
        u8 v;
        if (ch == '\\') {
            c->p++;
            if (c->p >= c->end) return false;
            char e = *c->p;
            switch (e) {
            case '"': v = '"'; c->p++; break;
            case '\\': v = '\\'; c->p++; break;
            case '/': v = '/'; c->p++; break;
            case 'b': v = '\b'; c->p++; break;
            case 'f': v = '\f'; c->p++; break;
            case 'n': v = '\n'; c->p++; break;
            case 'r': v = '\r'; c->p++; break;
            case 't': v = '\t'; c->p++; break;
            case 'u': {
                c->p++;
                u32 val = 0;
                if (!sc_hex4(c, &val) || val > 0xFFu) {
                    /* Consumed what we could; resync by continuing the
                     * scan to the closing quote. */
                    bad = true;
                    continue;
                }
                v = (u8)val;
                break;
            }
            default:
                /* Unknown escape: drop the backslash, keep scanning. */
                bad = true;
                c->p++;
                continue;
            }
        } else if (ch < 0x20u) {
            bad = true; /* raw control byte: invalid JSON string content */
            c->p++;
            continue;
        } else {
            v = ch;
            c->p++;
        }
        if (len + 1u >= BREAK_EDITOR_NAME_CAPACITY) {
            bad = true; /* over-cap: reject the entry, keep consuming */
        } else if (!bad) {
            out[len++] = (char)v;
        }
    }
    /* Empty names are treated as absent: the writer never emits one. */
    *usable = !bad && len > 0;
    return true;
}

/* Applies sidecar names to the (already swapped) doc world. Returns true
 * when ANY fallback/skip occurred — the caller then marks the doc dirty,
 * because the in-memory names differ from what a re-save would write. Never
 * fails the load: every problem degrades to generated-name fallback. */
static bool sidecar_apply(BreakEditorDoc *doc, const char *sidecar_path) {
    FILE *fp = fopen(sidecar_path, "rb");
    if (!fp) {
        LOG_WARN("editor: sidecar '%s' unreadable; generated entity names",
                 sidecar_path);
        return true;
    }
    long sz = -1;
    if (fseek(fp, 0, SEEK_END) != 0 || (sz = ftell(fp)) < 0 ||
        fseek(fp, 0, SEEK_SET) != 0) {
        fclose(fp);
        LOG_WARN("editor: sidecar '%s' not measurable; generated names",
                 sidecar_path);
        return true;
    }
    if ((u64)sz > (u64)BREAK_EDITOR_SIDECAR_MAX_BYTES) {
        fclose(fp);
        LOG_WARN("editor: sidecar '%s' over the %u-byte cap; generated names",
                 sidecar_path, (unsigned)BREAK_EDITOR_SIDECAR_MAX_BYTES);
        return true;
    }
    /* The one editor-owned allocation of the load path (OOM-injectable). */
    char *buf = break_editor_test_calloc((usize)sz + 1u);
    if (!buf) {
        fclose(fp);
        LOG_WARN("editor: sidecar read buffer allocation failed; generated "
                 "names");
        return true;
    }
    bool read_ok = fread(buf, 1, (usize)sz, fp) == (usize)sz;
    fclose(fp);
    if (!read_ok) {
        free(buf);
        LOG_WARN("editor: sidecar '%s' truncated read; generated names",
                 sidecar_path);
        return true;
    }
    /* buf[sz] is NUL from calloc, so every scan also stops at the NUL. */

    SidecarCursor c = { buf, buf + sz };
    bool problem = false;

    u32 version = 0;
    if (!sc_expect(&c, '{') || !sc_consume(&c, "\"version\"") ||
        !sc_expect(&c, ':') || !sc_u32(&c, &version) || version != 1u ||
        !sc_expect(&c, ',') || !sc_consume(&c, "\"entities\"") ||
        !sc_expect(&c, ':') || !sc_expect(&c, '[')) {
        LOG_WARN("editor: sidecar '%s' is not a version-1 name document; "
                 "generated names", sidecar_path);
        free(buf);
        return true;
    }

    if (!sc_expect(&c, ']')) {
        for (;;) {
            u32 index = 0, gen = 0;
            char name[BREAK_EDITOR_NAME_CAPACITY];
            bool usable = false;
            bool entry_ok =
                sc_expect(&c, '{') &&
                sc_consume(&c, "\"index\"") && sc_expect(&c, ':') &&
                sc_u32(&c, &index) &&
                sc_expect(&c, ',') &&
                sc_consume(&c, "\"generation\"") && sc_expect(&c, ':') &&
                sc_u32(&c, &gen) && sc_expect(&c, ',') &&
                sc_consume(&c, "\"name\"") && sc_expect(&c, ':') &&
                sc_string(&c, name, &usable) && sc_expect(&c, '}');
            if (!entry_ok) {
                /* Structural corruption: keep the names already applied,
                 * fall back for the rest. */
                LOG_WARN("editor: sidecar '%s' corrupt at byte %ld; "
                         "remaining entities get generated names",
                         sidecar_path, (long)(c.p - buf));
                problem = true;
                break;
            }
            if (!usable) {
                LOG_WARN("editor: sidecar entry for index %u rejected "
                         "(name cap %u bytes or invalid escape); generated "
                         "name used", index,
                         BREAK_EDITOR_NAME_CAPACITY - 1u);
                problem = true;
            } else if (index == 0 || index >= ECS_MAX_ENTITIES || gen == 0) {
                LOG_WARN("editor: sidecar entry {%u,%u} out of range; "
                         "skipped", index, gen);
                problem = true;
            } else if (doc->slots[index].generation != 0) {
                LOG_WARN("editor: duplicate sidecar entry for index %u; "
                         "keeping the first", index);
                problem = true;
            } else {
                Entity e;
                e.index = index;
                e.generation = gen;
                if (world_entity_exists(doc->world, e)) {
                    break_editor_doc_slot_set(doc, index, gen, name);
                }
                /* else: stale entry naming an entity the BSCN does not
                 * have — ignored, not a fallback trigger (the loaded doc
                 * matches a fresh save of this content). */
            }
            sc_skip_ws(&c);
            if (c.p < c.end && *c.p == ',') {
                c.p++;
                continue;
            }
            if (c.p < c.end && *c.p == ']') {
                c.p++;
                break;
            }
            LOG_WARN("editor: sidecar '%s' corrupt at byte %ld; remaining "
                     "entities get generated names", sidecar_path,
                     (long)(c.p - buf));
            problem = true;
            break;
        }
    }

    if (!sc_expect(&c, '}')) {
        LOG_WARN("editor: sidecar '%s' missing closing brace; entries "
                 "already applied kept", sidecar_path);
        problem = true;
    }
    sc_skip_ws(&c);
    if (c.p != c.end) {
        LOG_WARN("editor: sidecar '%s' has trailing garbage; ignored",
                 sidecar_path);
        problem = true;
    }
    free(buf);
    return problem;
}

/* ---------------------------------------------------------------- */
/* Public API                                                       */
/* ---------------------------------------------------------------- */

bool break_editor_doc_save(BreakEditorDoc *doc, const char *path) {
    if (!doc || !path) return false;
    char bscn_tmp[BREAK_EDITOR_SCENE_PATH_CAPACITY];
    char sidecar[BREAK_EDITOR_SCENE_PATH_CAPACITY];
    char sidecar_tmp[BREAK_EDITOR_SCENE_PATH_CAPACITY];
    if (!scene_paths(path, bscn_tmp, sidecar, sidecar_tmp)) return false;

    /* Sidecar first: a sidecar failure (cap, I/O) leaves neither file
     * behind. The BSCN is committed before the sidecar (see header). */
    if (!sidecar_write(doc, sidecar_tmp)) {
        remove(sidecar_tmp);
        return false;
    }
    /* NULL Scene: verified tolerated by every emit_* chunk (header). The
     * 64 MiB cap is scene_serial's own gate on both write and read. */
    if (!scene_save_binary(doc->world, NULL, bscn_tmp, NULL)) {
        remove(sidecar_tmp);
        remove(bscn_tmp);
        return false;
    }
    if (!rename_replace(bscn_tmp, path)) {
        remove(sidecar_tmp);
        remove(bscn_tmp);
        return false;
    }
    if (!rename_replace(sidecar_tmp, sidecar)) {
        LOG_WARN("editor: sidecar commit failed for '%s'; the BSCN is saved "
                 "but names were lost", sidecar);
        remove(sidecar_tmp);
        return false; /* dirty stays set: the pair on disk is incomplete */
    }
    break_editor_doc_clear_dirty(doc);
    return true;
}

static bool doc_load_staged(BreakEditorDoc *doc, const char *path,
                            const void *data, usize size) {
    if (!doc || !path || !data || size == 0u) return false;
    char sidecar[BREAK_EDITOR_SCENE_PATH_CAPACITY];
    if (!sidecar_path(path, sidecar)) return false;

    /* All-or-nothing staging: scene_load_binary does not clear the target
     * world (it appends), so REPLACE semantics require a fresh world, swapped
     * in only after the whole file parses. A fresh world also makes the
     * loaded indices dense 1..n (index compaction, see header), which is
     * what the sidecar's "index" field keys on. */
    World *staging = world_create();
    if (!staging) return false;
    /* Carry the doc's component registrations across the swap so payloads
     * parse (scene_serial skips ids with no/size-mismatched registration). */
    for (u32 t = 0; t < ECS_MAX_COMPONENTS; t++) {
        u32 sz = doc->world->component_sizes[t];
        if (sz) world_register_component(staging, t, sz);
    }
    /* NULL Scene: parse-and-discard (scene_serial.c:1596-1598). */
    if (!scene_load_binary_memory(staging, NULL, data, size)) {
        world_destroy(staging);
        return false; /* doc fully unchanged: entities, names, stack, dirty */
    }

    /* Commit: swap worlds, reset names, clear the undo history (the recorded
     * commands reference the pre-load world, which no longer exists). */
    world_destroy(doc->world);
    doc->world = staging;
    memset(doc->slots, 0, sizeof(BreakEditorNameSlot) * ECS_MAX_ENTITIES);
    doc->named_count = 0;
    break_editor_cmd_stack_clear(doc->stack);

    bool used_fallback = sidecar_apply(doc, sidecar);

    /* Every live entity without a sidecar name gets the generated fallback.
     * slots/named_count stay exact because slot_set maintains them. */
    for (u32 i = 1; i < staging->entity_count; i++) {
        Entity e = staging->entities[i];
        if (!world_entity_exists(staging, e)) continue;
        if (doc->slots[i].generation != 0) continue;
        char name[BREAK_EDITOR_NAME_CAPACITY];
        memset(name, 0, sizeof(name));
        snprintf(name, sizeof(name), "entity_%u_%u", i, e.generation);
        break_editor_doc_slot_set(doc, i, e.generation, name);
        used_fallback = true;
    }

    /* Dirty iff any generated-name fallback was used (header contract). */
    doc->dirty = used_fallback;
    return true;
}


bool break_editor_doc_load_bytes(BreakEditorDoc *doc, const char *path,
                                  const void *data, usize size) {
    return doc_load_staged(doc, path, data, size);
}

bool break_editor_doc_load(BreakEditorDoc *doc, const char *path) {
    if (!doc || !path) return false;
    FILE *fp = fopen(path, "rb");
    if (!fp) return false;
    if (fseek(fp, 0, SEEK_END) != 0) { fclose(fp); return false; }
    long fsz = ftell(fp);
    if (fseek(fp, 0, SEEK_SET) != 0 || fsz <= 0 ||
        (u64)fsz > (u64)BSCN_MAX_FILE_BYTES) {
        fclose(fp);
        return false;
    }
    u8 *buf = (u8 *)malloc((usize)fsz);
    if (!buf) { fclose(fp); return false; }
    bool read_ok = fread(buf, 1, (usize)fsz, fp) == (usize)fsz;
    fclose(fp);
    if (!read_ok) { free(buf); return false; }
    bool ok = doc_load_staged(doc, path, buf, (usize)fsz);
    free(buf);
    return ok;
}
