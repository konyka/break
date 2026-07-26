#include <core/shader_io.h>
#include <core/log.h>

#include <stdio.h>
#include <stdlib.h>

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
