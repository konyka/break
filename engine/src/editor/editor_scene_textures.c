#include <editor/editor_scene_textures.h>

#include <editor/editor_scene.h>
#include <scene/scene_serial.h>

#include <string.h>

/* RESOURCES chunk entry (scene_serial.c emit_one_resource / load_resources_chunk):
 *   u64 guid, u32 type, u32 ref_index, u32 flags
 *   flags & 1: u32 u0,u1,u2; v3 only: u32 tex_slots[5]; f32 f[8 (v1) | 12]
 *   u32 path_len, path bytes (a reader keeps the first 63) */
#define RES_MIN_ENTRY 24u

typedef struct {
    const u8 *p;
    const u8 *end;
    u32 version;
} ResCursor;

typedef struct {
    u32 type, ref_index;
    u32 slots[5];
    char path[BREAK_EDITOR_SCENE_TEXTURE_PATH];
} ResEntry;

static bool cur_u32(ResCursor *c, u32 *out) {
    if ((usize)(c->end - c->p) < 4u) return false;
    memcpy(out, c->p, 4u);
    c->p += 4;
    return true;
}

static bool cur_skip(ResCursor *c, u64 n) {
    if ((u64)(c->end - c->p) < n) return false;
    c->p += n;
    return true;
}

static bool cur_entry(ResCursor *c, ResEntry *e) {
    u32 flags = 0, plen = 0, keep;
    memset(e, 0, sizeof(*e));
    for (u32 i = 0; i < 5u; i++) e->slots[i] = BREAK_EDITOR_SCENE_TEXTURE_NONE;
    if (!cur_skip(c, 8u) /* guid */ || !cur_u32(c, &e->type) ||
        !cur_u32(c, &e->ref_index) || !cur_u32(c, &flags)) {
        return false;
    }
    if (flags & ~1u) return false; /* the loader's SCENE_RESOURCE_FLAG_MASK */
    if (flags & 1u) {
        u32 fcount = c->version == BSCN_VERSION_V1 ? 8u : 12u;
        if (!cur_skip(c, 12u)) return false; /* u0..u2 */
        if (c->version == BSCN_VERSION) {
            for (u32 i = 0; i < 5u; i++) {
                if (!cur_u32(c, &e->slots[i])) return false;
            }
        }
        if (!cur_skip(c, (u64)fcount * 4u)) return false;
    }
    if (!cur_u32(c, &plen)) return false;
    keep = plen < BREAK_EDITOR_SCENE_TEXTURE_PATH ? plen
                                                  : BREAK_EDITOR_SCENE_TEXTURE_PATH - 1u;
    if ((u64)(c->end - c->p) < (u64)plen) return false;
    memcpy(e->path, c->p, keep);
    e->path[keep] = '\0';
    c->p += plen;
    return true;
}

/* Validates the whole chunk and returns the entry count; false when anything
 * is out of bounds, so the caller never sees partial data. */
static bool res_open(const u8 *bytes, u32 size, u32 version, ResCursor *c,
                     u32 *count) {
    u32 n = 0;
    ResCursor probe;
    ResEntry e;
    if (bytes == NULL || size < 4u) {
        return false;
    }
    if (version != BSCN_VERSION && version != BSCN_VERSION_V2 &&
        version != BSCN_VERSION_V1) {
        return false;
    }
    memcpy(&n, bytes, 4u);
    if ((u64)n * RES_MIN_ENTRY > (u64)(size - 4u)) return false;
    c->p = bytes + 4;
    c->end = bytes + size;
    c->version = version;
    probe = *c;
    for (u32 i = 0; i < n; i++) {
        if (!cur_entry(&probe, &e)) return false;
    }
    if (probe.p != probe.end) return false; /* the loader requires an exact fit */
    *count = n;
    return true;
}

u32 break_editor_scene_textures_parse_chunk(const u8 *bytes, u32 size,
                                            u32 version,
                                            BreakEditorSceneTexture *out,
                                            u32 cap,
                                            BreakEditorSceneMaterial *mats,
                                            u32 mat_cap, u32 *mat_total) {
    ResCursor c;
    ResEntry e;
    u32 n = 0, written = 0, materials = 0;
    if (mat_total) *mat_total = 0;
    if (!out || cap == 0u) return 0;
    if (!res_open(bytes, size, version, &c, &n)) return 0;

    /* pass 1: textures */
    {
        ResCursor it = c;
        for (u32 i = 0; i < n; i++) {
            (void)cur_entry(&it, &e); /* validated by res_open */
            if (e.type != BSCN_RES_TEXTURE || written >= cap) continue;
            out[written].ref_index = e.ref_index;
            memcpy(out[written].path, e.path, sizeof(out[written].path));
            out[written].used_by_materials = 0;
            written++;
        }
    }
    /* pass 2: materials (all of them count towards used_by_materials) */
    {
        ResCursor it = c;
        for (u32 i = 0; i < n; i++) {
            (void)cur_entry(&it, &e);
            if (e.type != BSCN_RES_MATERIAL) continue;
            if (mats && materials < mat_cap) {
                mats[materials].ref_index = e.ref_index;
                memcpy(mats[materials].slot_texture, e.slots, sizeof(e.slots));
            }
            for (u32 t = 0; t < written; t++) {
                for (u32 s = 0; s < 5u; s++) {
                    if (e.slots[s] != BREAK_EDITOR_SCENE_TEXTURE_NONE &&
                        e.slots[s] == out[t].ref_index) {
                        out[t].used_by_materials++;
                        break; /* once per material */
                    }
                }
            }
            materials++;
        }
    }
    if (mat_total) *mat_total = materials;
    return written;
}

u32 break_editor_scene_textures_parse(const BreakEditorDoc *doc,
                                      BreakEditorSceneTexture *out, u32 cap,
                                      BreakEditorSceneMaterial *mats,
                                      u32 mat_cap, u32 *mat_total) {
    const u8 *bytes = NULL;
    u32 size = 0, version = 0;
    if (mat_total) *mat_total = 0;
    if (!doc || !out || cap == 0u ||
        !break_editor_doc_kept_chunk(doc, BSCN_CHUNK_RESOURCES, &bytes, &size,
                                     &version)) {
        return 0;
    }
    return break_editor_scene_textures_parse_chunk(bytes, size, version, out,
                                                   cap, mats, mat_cap,
                                                   mat_total);
}

bool break_editor_scene_texture_path_ok(const char *path) {
    usize len, seg = 0;
    if (!path) return false;
    len = strlen(path);
    if (len == 0u || len >= BREAK_EDITOR_SCENE_TEXTURE_PATH) return false;
    for (usize i = 0; i <= len; i++) {
        unsigned char ch = (unsigned char)path[i];
        if (i == len || ch == '/') {
            /* segment path[i-seg .. i): not empty, not "." or ".." */
            if (seg == 0u) return false;
            if (seg == 1u && path[i - 1u] == '.') return false;
            if (seg == 2u && path[i - 1u] == '.' && path[i - 2u] == '.') return false;
            seg = 0;
            continue;
        }
        if (ch < 0x20u || ch > 0x7eu || ch == '\\' || ch == ':') return false;
        seg++;
    }
    return true;
}

static bool path_is_absolute(const char *p) {
    if (p[0] == '/' || p[0] == '\\') return true;
    return ((p[0] >= 'A' && p[0] <= 'Z') || (p[0] >= 'a' && p[0] <= 'z')) &&
           p[1] == ':' && (p[2] == '/' || p[2] == '\\');
}

bool break_editor_scene_texture_resolve(const char *scene_path, const char *uri,
                                        char *out, usize cap) {
    usize dir_len = 0, uri_len;
    if (!scene_path || !uri || !out || cap == 0u) return false;
    if (!break_editor_scene_texture_path_ok(uri)) return false;
    if (!path_is_absolute(scene_path)) return false;
    for (usize i = 0; scene_path[i] != '\0'; i++) {
        if (scene_path[i] == '/' || scene_path[i] == '\\') dir_len = i + 1u;
    }
    if (dir_len == 0u) return false;
    uri_len = strlen(uri);
    if (dir_len + uri_len + 1u > cap) return false;
    memcpy(out, scene_path, dir_len);
    memcpy(out + dir_len, uri, uri_len + 1u);
    return true;
}

bool break_editor_scene_texture_make_absolute(const char *path, const char *cwd,
                                              char *out, usize cap) {
    usize path_len, cwd_len;
    if (!path || !out || cap == 0u || path[0] == '\0') return false;
    if (path_is_absolute(path)) {
        path_len = strlen(path);
        if (path_len + 1u > cap) return false;
        memcpy(out, path, path_len + 1u);
        return true;
    }
    if (!cwd || cwd[0] == '\0' || !path_is_absolute(cwd)) return false;
    while (path[0] == '.' && (path[1] == '/' || path[1] == '\\')) {
        path += 2;
        while (path[0] == '/' || path[0] == '\\') path++;
    }
    if (path[0] == '\0') return false;
    path_len = strlen(path);
    cwd_len = strlen(cwd);
    while (cwd_len > 1u && (cwd[cwd_len - 1u] == '/' || cwd[cwd_len - 1u] == '\\')) {
        cwd_len--; /* "/cwd/" -> "/cwd"; a bare "/" keeps its slash */
    }
    if (cwd_len == 1u && (cwd[0] == '/' || cwd[0] == '\\')) {
        if (1u + path_len + 1u > cap) return false;
        out[0] = cwd[0];
        memcpy(out + 1, path, path_len + 1u);
        return true;
    }
    if (cwd_len + 1u + path_len + 1u > cap) return false;
    memcpy(out, cwd, cwd_len);
    out[cwd_len] = '/';
    memcpy(out + cwd_len + 1u, path, path_len + 1u);
    return true;
}
