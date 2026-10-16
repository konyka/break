#include <core/shader_io.h>
#include <core/log.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

static const char *shader_skip_space(const char *p, const char *end) {
    while (p < end && isspace((unsigned char)*p)) p++;
    return p;
}

static const char *shader_find(const char *src, const char *end, const char *needle) {
    usize length = strlen(needle);
    if (length == 0u) return src;
    while (src < end && (usize)(end - src) >= length) {
        if (memcmp(src, needle, length) == 0) return src;
        src++;
    }
    return NULL;
}

static usize shader_field_length(const char *field, usize capacity) {
    usize length = 0u;
    while (length < capacity && field[length] != '\0') length++;
    return length;
}

static bool shader_word_at(const char *base, const char *src, const char *end,
                           const char *word) {
    usize length = strlen(word);
    const char *after;
    if ((usize)(end - src) < length || memcmp(src, word, length) != 0)
        return false;
    after = src + length;
    return (src == base || !isalnum((unsigned char)src[-1])) &&
           (after == end || !isalnum((unsigned char)*after));
}

static const char *shader_find_word(const char *base, const char *src,
                                    const char *end,
                                    const char *word) {
    while (src < end) {
        if (shader_word_at(base, src, end, word)) return src;
        src++;
    }
    return NULL;
}

static const char *shader_char(const char *src, const char *end, char value) {
    while (src < end) {
        if (*src == value) return src;
        src++;
    }
    return NULL;
}

static int shader_binding_compare(const void *lhs, const void *rhs);

static const char *shader_identifier(const char *p, const char *end,
                                     char *out, usize cap) {
    usize n = 0;
    p = shader_skip_space(p, end);
    while (p < end && (isalnum((unsigned char)*p) || *p == '_')) {
        if (n + 1u < cap) out[n++] = *p;
        p++;
    }
    if (cap != 0u) out[n] = '\0';
    return p;
}

static u32 shader_layout_value(const char *layout, const char *end,
                               const char *key, u32 fallback) {
    const char *p = shader_find(layout, end, key);
    u64 value = 0u;
    bool has_digit = false;
    if (!p || p >= end) return fallback;
    p += strlen(key);
    p = shader_skip_space(p, end);
    if (p >= end || *p != '=') return fallback;
    p = shader_skip_space(p + 1, end);
    while (p < end && *p >= '0' && *p <= '9') {
        has_digit = true;
        value = value * 10u + (u64)(*p - '0');
        if (value > 0xffffffffu) return fallback;
        p++;
    }
    return !has_digit ? fallback : (u32)value;
}

static bool shader_layout_supported(const char *layout, const char *end) {
    const char *p = layout;
    static const char *const qualifiers[] = {
        "std140", "std430", "push_constant", "set", "binding",
        "location", "rgba8", "rgba16f", "rg16f", "r32f",
        "local_size_x", "local_size_y", "local_size_z"
    };
    while (p < end) {
        char word[32];
        usize length = 0u;
        while (p < end && !(isalpha((unsigned char)*p) || *p == '_')) p++;
        if (p == end) break;
        while (p < end && (isalnum((unsigned char)*p) || *p == '_')) {
            if (length + 1u < sizeof(word)) word[length++] = *p;
            p++;
        }
        word[length] = '\0';
        if (strcmp(word, "layout") == 0) continue;
        bool known = false;
        for (usize i = 0u; i < sizeof(qualifiers) / sizeof(qualifiers[0]); ++i) {
            if (strcmp(word, qualifiers[i]) == 0) {
                known = true;
                break;
            }
        }
        if (!known) return false;
    }
    if (shader_find_word(layout, layout, end, "location") != NULL) return false;
    if (shader_find_word(layout, layout, end, "binding") != NULL &&
        shader_layout_value(layout, end, "binding", UINT32_MAX) == UINT32_MAX) return false;
    if (shader_find_word(layout, layout, end, "set") != NULL &&
        shader_layout_value(layout, end, "set", UINT32_MAX) == UINT32_MAX) return false;
    return shader_find_word(layout, layout, end, "std140") != NULL ||
           shader_find_word(layout, layout, end, "std430") != NULL ||
           shader_find_word(layout, layout, end, "push_constant") != NULL ||
           shader_find_word(layout, layout, end, "binding") != NULL ||
           shader_find_word(layout, layout, end, "set") != NULL;
}

static bool shader_bindings_have_duplicate_slots(const ShaderIOBinding *bindings,
                                                 usize count) {
    for (usize i = 0u; i < count; ++i) {
        for (usize j = i + 1u; j < count; ++j) {
            if (bindings[i].kind != SHADER_IO_RESOURCE_PUSH_CONSTANT &&
                bindings[j].kind != SHADER_IO_RESOURCE_PUSH_CONSTANT &&
                bindings[i].set == bindings[j].set &&
                bindings[i].binding == bindings[j].binding)
                return true;
        }
    }
    return false;
}

static bool shader_type_supported(const char *type) {
    static const char *const types[] = {
        "sampler2D", "sampler2DArray", "samplerCube", "samplerBuffer",
        "image2D", "float", "int", "uint", "vec2", "vec3", "vec4",
        "mat2", "mat3", "mat4"
    };
    for (usize i = 0u; i < sizeof(types) / sizeof(types[0]); ++i)
        if (strcmp(type, types[i]) == 0) return true;
    return false;
}

u64 shader_reflect_bindings_hash(const ShaderIOBinding *bindings, usize count) {
    ShaderIOBinding *sorted;
    u64 hash = 1469598103934665603ull;
    usize size;
    if (!bindings && count != 0u) return 0u;
    if (count == 0u) return hash;
    if (count > (usize)-1 / sizeof(*bindings)) return 0u;
    size = count * sizeof(*bindings);
    sorted = malloc(size);
    if (!sorted) return 0u;
    memcpy(sorted, bindings, size);
    qsort(sorted, count, sizeof(*sorted), shader_binding_compare);
    for (usize i = 0u; i < count; ++i) {
        const ShaderIOBinding *binding = &sorted[i];
        const char *strings[] = { binding->name, binding->format };
        const u32 values[] = { (u32)binding->kind, (u32)binding->layout,
                               binding->set, binding->binding, binding->location };
        for (usize field = 0u; field < 2u; ++field) {
            usize capacity = field == 0u ? SHADER_IO_NAME_MAX : SHADER_IO_FORMAT_MAX;
            usize length = shader_field_length(strings[field], capacity);
            for (usize byte = 0u; byte < length; ++byte) {
                hash ^= (u8)strings[field][byte];
                hash *= 1099511628211ull;
            }
            hash ^= 0xffu;
            hash *= 1099511628211ull;
        }
        for (usize field = 0u; field < 5u; ++field) {
            u32 value = values[field];
            for (usize byte = 0u; byte < sizeof(value); ++byte) {
                hash ^= (u8)(value >> (byte * 8u));
                hash *= 1099511628211ull;
            }
        }
    }
    free(sorted);
    return hash;
}

static int shader_binding_compare(const void *lhs, const void *rhs) {
    const ShaderIOBinding *a = lhs;
    const ShaderIOBinding *b = rhs;
    int name_cmp;
    int format_cmp;
    if (a->set != b->set) return a->set < b->set ? -1 : 1;
    if (a->binding != b->binding) return a->binding < b->binding ? -1 : 1;
    if (a->kind != b->kind) return a->kind < b->kind ? -1 : 1;
    usize a_len = shader_field_length(a->name, SHADER_IO_NAME_MAX);
    usize b_len = shader_field_length(b->name, SHADER_IO_NAME_MAX);
    usize common = a_len < b_len ? a_len : b_len;
    name_cmp = memcmp(a->name, b->name, common);
    if (name_cmp == 0 && a_len != b_len) name_cmp = a_len < b_len ? -1 : 1;
    if (name_cmp != 0) return name_cmp;
    a_len = shader_field_length(a->format, SHADER_IO_FORMAT_MAX);
    b_len = shader_field_length(b->format, SHADER_IO_FORMAT_MAX);
    common = a_len < b_len ? a_len : b_len;
    format_cmp = memcmp(a->format, b->format, common);
    if (format_cmp == 0 && a_len != b_len) format_cmp = a_len < b_len ? -1 : 1;
    if (format_cmp != 0) return format_cmp;
    if (a->layout != b->layout) return a->layout < b->layout ? -1 : 1;
    if (a->location != b->location) return a->location < b->location ? -1 : 1;
    return 0;
}

static void shader_binding_add(ShaderIOBinding *out, usize capacity, usize *count,
                               const char *name, const char *format,
                               ShaderIOResourceKind kind, ShaderIOLayout layout,
                               u32 set, u32 binding) {
    ShaderIOBinding *record;
    usize index = *count;
    (*count)++;
    if (index >= capacity) return;
    record = &out[index];
    memset(record, 0, sizeof(*record));
    memcpy(record->name, name, shader_field_length(name, SHADER_IO_NAME_MAX));
    memcpy(record->format, format, shader_field_length(format, SHADER_IO_FORMAT_MAX));
    record->kind = kind;
    record->layout = layout;
    record->set = set;
    record->binding = binding;
}

usize shader_reflect_bindings(const char *src, usize len,
                              ShaderIOBinding *out, usize capacity) {
    const char *line = src;
    const char *end;
    usize count = 0;
    if (!src || (capacity != 0u && !out) || len > (usize)PTRDIFF_MAX) return 0u;
    if (capacity > (usize)-1 / sizeof(*out)) return 0u;
    end = src + len;
    while (line < end) {
        const char *line_end = memchr(line, '\n', (size_t)(end - line));
        const char *decl_end = line_end ? line_end : end;
        const char *layout_start = shader_find(line, decl_end, "layout(");
        const char *decl = line;
        char name[SHADER_IO_NAME_MAX];
        char format[SHADER_IO_FORMAT_MAX];
        ShaderIOResourceKind kind;
        ShaderIOLayout abi_layout = SHADER_IO_LAYOUT_DEFAULT;
        bool push_constant = false;
        u32 set = 0u;
        u32 binding = 0u;
        const char *first = shader_skip_space(line, decl_end);
        if (first >= decl_end || *first == '#' ||
            (first[0] == '/' && first + 1 < decl_end && first[1] == '/')) {
            line = line_end ? line_end + 1 : end;
            continue;
        }
        if (layout_start && layout_start < decl_end) {
            const char *layout_end = shader_char(layout_start, decl_end, ')');
            if (!layout_end || layout_end > decl_end) layout_end = decl_end;
            if (layout_end == decl_end || !shader_layout_supported(layout_start, layout_end)) {
                line = line_end ? line_end + 1 : end;
                continue;
            }
            set = shader_layout_value(layout_start, layout_end, "set", 0u);
            binding = shader_layout_value(layout_start, layout_end, "binding", 0u);
            if (shader_find_word(layout_start, layout_start, layout_end, "std140")) abi_layout = SHADER_IO_LAYOUT_STD140;
            else if (shader_find_word(layout_start, layout_start, layout_end, "std430")) abi_layout = SHADER_IO_LAYOUT_STD430;
            else if (shader_find_word(layout_start, layout_start, layout_end, "push_constant")) {
                abi_layout = SHADER_IO_LAYOUT_PUSH_CONSTANT;
                push_constant = true;
            }
            decl = layout_end < decl_end ? layout_end + 1 : decl_end;
        }
        decl = shader_skip_space(decl, decl_end);
        if (decl >= decl_end) {
            line = line_end ? line_end + 1 : end;
            continue;
        }
        if (push_constant) {
            const char *brace = memchr(line, '{', (size_t)(decl_end - line));
            const char *uniform = shader_find(line, decl_end, "uniform");
            if (uniform && uniform < decl_end && brace && brace < decl_end) {
                shader_identifier(uniform + 7, brace, name, sizeof(name));
                if (name[0] == '\0') {
                    line = line_end ? line_end + 1 : end;
                    continue;
                }
                shader_binding_add(out, capacity, &count, name, "push_constant",
                                   SHADER_IO_RESOURCE_PUSH_CONSTANT,
                                   SHADER_IO_LAYOUT_PUSH_CONSTANT, set, binding);
            }
        } else if (shader_find(decl, decl_end, " buffer ") || strncmp(decl, "buffer ", 7) == 0) {
            const char *buffer = shader_find(decl, decl_end, "buffer");
            const char *brace = memchr(decl, '{', (size_t)(decl_end - decl));
            if (buffer && brace && buffer < brace) {
                shader_identifier(buffer + 6, brace, name, sizeof(name));
                if (name[0] == '\0') {
                    line = line_end ? line_end + 1 : end;
                    continue;
                }
                shader_binding_add(out, capacity, &count, name, "buffer",
                                   SHADER_IO_RESOURCE_STORAGE, abi_layout,
                                   set, binding);
            }
        } else {
            const char *uniform = shader_find(decl, decl_end, "uniform");
            const char *sampler = uniform ? shader_find(uniform, decl_end, "sampler") : NULL;
            const char *image = uniform ? shader_find(uniform, decl_end, "image") : NULL;
            const char *brace = memchr(decl, '{', (size_t)(decl_end - decl));
            if (uniform && uniform < decl_end) {
                const char *type = shader_skip_space(uniform + 7, decl_end);
                const char *name_start;
                shader_identifier(type, decl_end, format, sizeof(format));
                if (!brace && !shader_type_supported(format)) {
                    line = line_end ? line_end + 1 : end;
                    continue;
                }
                name_start = type + strlen(format);
                if (brace && brace > uniform) name_start = uniform + 7;
                shader_identifier(name_start, decl_end, name, sizeof(name));
                if (name[0] == '\0') {
                    line = line_end ? line_end + 1 : end;
                    continue;
                }
                if (brace && brace > uniform) {
                    kind = SHADER_IO_RESOURCE_UNIFORM;
                    shader_identifier(name_start, brace, name, sizeof(name));
                } else if (image && image < decl_end) {
                    kind = SHADER_IO_RESOURCE_IMAGE;
                } else if (sampler && sampler < decl_end) {
                    kind = SHADER_IO_RESOURCE_SAMPLER;
                } else {
                    kind = SHADER_IO_RESOURCE_UNIFORM;
                }
                shader_binding_add(out, capacity, &count, name, format, kind,
                                   abi_layout, set, binding);
            }
        }
        line = line_end ? line_end + 1 : end;
    }
    if (count > capacity) return 0u;
    if (capacity > 1u && count > 1u)
        qsort(out, count, sizeof(*out), shader_binding_compare);
    if (shader_bindings_have_duplicate_slots(out, count)) return 0u;
    return count;
}

char *shader_read_file(const char *path, usize *out_len) {
    FILE *f = fopen(path, "rb");
    if (!f) return NULL;
    if (fseek(f, 0, SEEK_END) != 0) { fclose(f); return NULL; }
    long sz = ftell(f);
    if (sz < 0) { fclose(f); return NULL; }
    if ((u64)sz > (u64)SHADER_MAX_FILE_BYTES) {
        LOG_WARN("Shader read: %s too large (%ld bytes)", path, sz);
        fclose(f);
        return NULL;
    }
    if (fseek(f, 0, SEEK_SET) != 0) { fclose(f); return NULL; }
    char *buf = malloc((usize)sz + 1u);
    if (!buf) { fclose(f); return NULL; }
    if (fread(buf, 1, (usize)sz, f) != (usize)sz) {
        free(buf);
        fclose(f);
        return NULL;
    }
    buf[sz] = '\0';
    fclose(f);
    if (out_len) *out_len = (usize)sz;
    return buf;
}

char *shader_inject_define(const char *src, usize len, const char *name, usize *out_len) {
    if (!src || !name) return NULL;
    /* GLSL requires the #version directive to come before everything else, so
     * injecting after the first line (whatever it is) breaks any shader whose
     * #version is not on line 1. Scan for the #version line — the first
     * non-comment line — and insert after it; fall back to after line 1 when
     * the source declares no #version. */
    usize head = 0;
    usize pos = 0;
    while (pos < len) {
        const char *eol = memchr(src + pos, '\n', len - pos);
        usize line_end = eol ? (usize)(eol - src) : len;
        usize t = pos;
        while (t < line_end && (src[t] == ' ' || src[t] == '\t')) t++;
        if (line_end - t > 8u && memcmp(src + t, "#version", 8u) == 0 &&
            (src[t + 8u] == ' ' || src[t + 8u] == '\t')) {
            head = eol ? line_end + 1u : len;
            break;
        }
        if (!eol) break;
        pos = line_end + 1u;
    }
    if (head == 0) {
        const char *nl = memchr(src, '\n', len);
        head = nl ? (usize)(nl - src) + 1u : len;
    }
    /* If the insertion point does not follow a newline (e.g. a #version line
     * or a one-line source with no trailing newline), insert one or the
     * define fuses with the preceding line. */
    const char *lead = (head > 0 && src[head - 1] != '\n') ? "\n" : "";
    int def_raw = snprintf(NULL, 0, "%s#define %s 1\n", lead, name);
    if (def_raw < 0) return NULL;
    usize def_len = (usize)def_raw;
    char *out = malloc(len + def_len + 1u);
    if (!out) return NULL;
    memcpy(out, src, head);
    int written = snprintf(out + head, def_len + 1u, "%s#define %s 1\n", lead, name);
    if (written < 0) {
        free(out);
        return NULL;
    }
    usize total = head + (usize)written + (len - head);
    memcpy(out + head + (usize)written, src + head, len - head);
    out[total] = '\0';
    if (out_len) *out_len = total;
    return out;
}

const char *shader_variant_suffix(RHIShaderVariant v) {
    return v == RHI_SHADER_VARIANT_GLSL_VK ? "_vk" : "";
}

char *shader_variant_path(const char *base_path, RHIShaderVariant v,
                          char *out, usize cap) {
    if (!base_path || !out) return NULL;
    const char *dot = strrchr(base_path, '.');
    const char *suffix = shader_variant_suffix(v);
    usize stem = dot ? (usize)(dot - base_path) : strlen(base_path);
    usize need = stem + strlen(suffix) + strlen(dot ? dot : "") + 1u;
    if (need > cap) return NULL;
    memcpy(out, base_path, stem);
    strcpy(out + stem, suffix);
    if (dot) strcpy(out + stem + strlen(suffix), dot);
    return out;
}
