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
    const char *nl = memchr(src, '\n', len);
    usize head = nl ? (usize)(nl - src) + 1u : len;
    int def_raw = snprintf(NULL, 0, "#define %s 1\n", name);
    if (def_raw < 0) return NULL;
    usize def_len = (usize)def_raw;
    char *out = malloc(len + def_len + 1u);
    if (!out) return NULL;
    memcpy(out, src, head);
    int written = snprintf(out + head, def_len + 1u, "#define %s 1\n", name);
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
