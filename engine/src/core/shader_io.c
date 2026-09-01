#include <core/shader_io.h>
#include <core/log.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
