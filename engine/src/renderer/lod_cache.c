#include "lod_cache.h"
#include <math.h>
#include <stdatomic.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <process.h>
#define lod_cache_pid() _getpid()
#else
#include <unistd.h>
#define lod_cache_pid() getpid()
#endif

#define LOD_CACHE_MESHOPT_VERSION 1030u
#define LOD_CACHE_MAX_FILE (1024u * 1024u * 1024u)

static const u8 k_magic[8] = { 'L', 'O', 'D', 'C', 'A', 'C', 'H', 'E' };
static atomic_uint g_temp_counter;

static f64 cache_now_ms(void) {
    struct timespec ts;
    if (timespec_get(&ts, TIME_UTC) != TIME_UTC) return 0.0;
    return (f64)ts.tv_sec * 1000.0 + (f64)ts.tv_nsec / 1e6;
}

static void put32(u8 *p, u32 v) {
    p[0] = (u8)v; p[1] = (u8)(v >> 8); p[2] = (u8)(v >> 16); p[3] = (u8)(v >> 24);
}

static void put64(u8 *p, u64 v) {
    for (u32 i = 0; i < 8u; i++) p[i] = (u8)(v >> (i * 8u));
}

static u32 get32(const u8 *p) {
    return (u32)p[0] | ((u32)p[1] << 8) | ((u32)p[2] << 16) | ((u32)p[3] << 24);
}

static u64 get64(const u8 *p) {
    u64 v = 0u;
    for (u32 i = 0; i < 8u; i++) v |= (u64)p[i] << (i * 8u);
    return v;
}

static u32 float_bits(f32 v) {
    u32 u;
    memcpy(&u, &v, sizeof(u));
    return u;
}

static f32 bits_float(u32 u) {
    f32 v;
    memcpy(&v, &u, sizeof(v));
    return v;
}

static void hash_bytes(LodCacheKey *key, const void *data, usize size) {
    const u8 *p = (const u8 *)data;
    u64 a = key->first, b = key->second;
    for (usize i = 0; i < size; i++) {
        a ^= p[i];
        a *= 1099511628211ull;
        b += (u64)p[i] + 0x9e3779b97f4a7c15ull;
        b ^= b << 13; b ^= b >> 7; b ^= b << 17;
        b *= 0xbf58476d1ce4e5b9ull;
    }
    key->first = a;
    key->second = b;
}

static void hash32(LodCacheKey *key, u32 v) {
    u8 p[4];
    put32(p, v);
    hash_bytes(key, p, sizeof(p));
}

void lod_cache_init(LodCache *cache, const char *directory) {
    if (!cache) return;
    memset(cache, 0, sizeof(*cache));
    cache->directory = directory;
}

LodCacheKey lod_cache_key(const f32 *vertices, u32 vertex_count, u32 vertex_stride,
                          const u32 *indices, u32 index_count, u32 max_levels) {
    LodCacheKey key = { 1469598103934665603ull, 0x6a09e667f3bcc909ull };
    hash32(&key, LOD_CACHE_FORMAT_VERSION);
    hash32(&key, LOD_CACHE_MESHOPT_VERSION);
    hash32(&key, vertex_count);
    hash32(&key, index_count);
    hash32(&key, vertex_stride);
    hash32(&key, max_levels);
    hash32(&key, LOD_GEN_MIN_TRIANGLES);
    hash32(&key, float_bits(LOD_GEN_STOP_RATIO));
    if (vertices && vertex_stride && (usize)vertex_count <= (usize)-1 / vertex_stride)
        hash_bytes(&key, vertices, (usize)vertex_count * vertex_stride);
    if (indices && (usize)index_count <= (usize)-1 / sizeof(u32))
        hash_bytes(&key, indices, (usize)index_count * sizeof(u32));
    key.first ^= key.first >> 33;
    key.first *= 0xff51afd7ed558ccdull;
    key.first ^= key.first >> 33;
    key.second ^= key.second >> 29;
    key.second *= 0x94d049bb133111ebull;
    key.second ^= key.second >> 31;
    return key;
}

bool lod_cache_path(char *out, usize out_size, const char *directory, LodCacheKey key) {
    if (!out || out_size == 0u || !directory || !directory[0]) return false;
    usize n = strlen(directory);
    const char *sep = (n && directory[n - 1u] != '/' && directory[n - 1u] != '\\') ? "/" : "";
    int w = snprintf(out, out_size, "%s%slod_%016llx%016llx.bin", directory, sep,
                     (unsigned long long)key.first, (unsigned long long)key.second);
    return w > 0 && (usize)w < out_size;
}

static bool input_valid(const f32 *vertices, u32 vertex_count, u32 vertex_stride,
                        const u32 *indices, u32 index_count, u32 max_levels) {
    if (!vertices || !indices || vertex_count == 0u || index_count == 0u) return false;
    if (vertex_stride < 32u || (vertex_stride & 3u) != 0u || index_count % 3u != 0u) return false;
    if (max_levels == 0u || max_levels > LOD_GEN_MAX_LEVELS) return false;
    for (u32 i = 0; i < index_count; i++)
        if (indices[i] >= vertex_count) return false;
    return true;
}

static u8 *read_whole(const char *path, usize expected_max, usize *out_size) {
    FILE *f = fopen(path, "rb");
    if (!f) return NULL;
    if (fseek(f, 0, SEEK_END) != 0) { fclose(f); return NULL; }
    long end = ftell(f);
    if (end < 0 || (u64)end > LOD_CACHE_MAX_FILE || (usize)end > expected_max) {
        fclose(f);
        return NULL;
    }
    if (fseek(f, 0, SEEK_SET) != 0) { fclose(f); return NULL; }
    usize size = (usize)end;
    u8 *data = (u8 *)malloc(size ? size : 1u);
    if (!data) { fclose(f); return NULL; }
    bool ok = fread(data, 1, size, f) == size && !ferror(f);
    fclose(f);
    if (!ok) { free(data); return NULL; }
    *out_size = size;
    return data;
}

static bool decode(const u8 *data, usize size, LodCacheKey key,
                   u32 vertex_count, u32 source_index_count, u32 vertex_stride,
                   u32 max_levels, LodMeshLevels *out, f64 *stored_generation_ms) {
    if (!data || size < LOD_CACHE_HEADER_SIZE + 8u) return false;
    if (memcmp(data, k_magic, sizeof(k_magic)) != 0) return false;
    if (get32(data + 8u) != LOD_CACHE_FORMAT_VERSION ||
        get32(data + 12u) != LOD_CACHE_HEADER_SIZE ||
        get64(data + 16u) != key.first || get64(data + 24u) != key.second ||
        get32(data + 32u) != vertex_count || get32(data + 36u) != source_index_count ||
        get32(data + 40u) != vertex_stride || get32(data + 44u) != max_levels ||
        get32(data + 48u) != LOD_GEN_MIN_TRIANGLES ||
        get32(data + 52u) != float_bits(LOD_GEN_STOP_RATIO) ||
        get32(data + 56u) != LOD_CACHE_MESHOPT_VERSION)
        return false;
    if (stored_generation_ms) *stored_generation_ms = (f64)get32(data + 68u) / 1000.0;
    u32 level_count = get32(data + 60u);
    if (level_count == 0u || level_count > max_levels || level_count > LOD_GEN_MAX_LEVELS)
        return false;
    if (size < LOD_CACHE_HEADER_SIZE + (usize)level_count * 8u) return false;
    f32 scale = bits_float(get32(data + 64u));
    if (!isfinite(scale) || scale < 0.0f) return false;
    u64 index_bytes = get64(data + 72u);
    u64 sum_bytes = 0u;
    f32 previous_error = 0.0f;
    u32 previous_count = source_index_count;
    for (u32 l = 0; l < level_count; l++) {
        const u8 *meta = data + LOD_CACHE_HEADER_SIZE + (usize)l * 8u;
        u32 count = get32(meta);
        f32 error = bits_float(get32(meta + 4u));
        if (!isfinite(error) || error < previous_error) return false;
        if (l == 0u) {
            if (count != source_index_count || float_bits(error) != 0u) return false;
        } else {
            if (count == 0u || count % 3u != 0u || count > previous_count ||
                (f32)count > (f32)previous_count * LOD_GEN_STOP_RATIO)
                return false;
            if (count > UINT32_MAX / sizeof(u32)) return false;
            sum_bytes += (u64)count * sizeof(u32);
        }
        previous_error = error;
        previous_count = count;
    }
    if (sum_bytes != index_bytes) return false;
    usize metadata = LOD_CACHE_HEADER_SIZE + (usize)level_count * 8u;
    if (index_bytes > (u64)((usize)-1 - metadata)) return false;
    usize expected = metadata + (usize)index_bytes;
    if (expected != size) return false;

    usize offset = LOD_CACHE_HEADER_SIZE + (usize)level_count * 8u;
    for (u32 l = 1; l < level_count; l++) {
        u32 count = get32(data + LOD_CACHE_HEADER_SIZE + (usize)l * 8u);
        for (u32 i = 0; i < count; i++) {
            if (get32(data + offset + (usize)i * 4u) >= vertex_count) return false;
        }
        offset += (usize)count * 4u;
    }

    LodMeshLevels result;
    memset(&result, 0, sizeof(result));
    result.level_count = level_count;
    result.scale = scale;
    offset = LOD_CACHE_HEADER_SIZE + (usize)level_count * 8u;
    for (u32 l = 0; l < level_count; l++) {
        const u8 *meta = data + LOD_CACHE_HEADER_SIZE + (usize)l * 8u;
        u32 count = get32(meta);
        result.index_count[l] = count;
        result.rel_error[l] = bits_float(get32(meta + 4u));
        if (l > 0u) {
            result.indices[l] = (u32 *)malloc((usize)count * sizeof(u32));
            if (!result.indices[l]) {
                lod_mesh_levels_free(&result);
                return false;
            }
            for (u32 i = 0; i < count; i++)
                result.indices[l][i] = get32(data + offset + (usize)i * 4u);
            offset += (usize)count * 4u;
        }
    }
    *out = result;
    return true;
}

static bool encode(const LodMeshLevels *levels, LodCacheKey key,
                   u32 vertex_count, u32 source_index_count, u32 vertex_stride,
                   u32 max_levels, f64 generation_ms, u8 **out_data, usize *out_size) {
    if (!levels || levels->level_count == 0u || levels->level_count > max_levels ||
        levels->level_count > LOD_GEN_MAX_LEVELS) return false;
    u64 bytes = 0u;
    for (u32 l = 1; l < levels->level_count; l++) {
        u32 count = levels->index_count[l];
        if (!levels->indices[l] || count == 0u || count % 3u != 0u ||
            count > UINT32_MAX / sizeof(u32)) return false;
        bytes += (u64)count * sizeof(u32);
    }
    usize metadata = LOD_CACHE_HEADER_SIZE + (usize)levels->level_count * 8u;
    if (bytes > (u64)((usize)-1 - metadata)) return false;
    usize size = metadata + (usize)bytes;
    if (size > LOD_CACHE_MAX_FILE) return false;
    u8 *data = (u8 *)malloc(size);
    if (!data) return false;
    memset(data, 0, size);
    memcpy(data, k_magic, sizeof(k_magic));
    put32(data + 8u, LOD_CACHE_FORMAT_VERSION);
    put32(data + 12u, LOD_CACHE_HEADER_SIZE);
    put64(data + 16u, key.first); put64(data + 24u, key.second);
    put32(data + 32u, vertex_count); put32(data + 36u, source_index_count);
    put32(data + 40u, vertex_stride); put32(data + 44u, max_levels);
    put32(data + 48u, LOD_GEN_MIN_TRIANGLES);
    put32(data + 52u, float_bits(LOD_GEN_STOP_RATIO));
    put32(data + 56u, LOD_CACHE_MESHOPT_VERSION);
    put32(data + 60u, levels->level_count);
    put32(data + 64u, float_bits(levels->scale));
    f64 generation_us = generation_ms > 0.0 ? generation_ms * 1000.0 : 0.0;
    put32(data + 68u, generation_us >= (f64)UINT32_MAX ? UINT32_MAX : (u32)generation_us);
    put64(data + 72u, bytes);
    usize offset = LOD_CACHE_HEADER_SIZE + (usize)levels->level_count * 8u;
    for (u32 l = 0; l < levels->level_count; l++) {
        u8 *meta = data + LOD_CACHE_HEADER_SIZE + (usize)l * 8u;
        u32 count = levels->index_count[l];
        put32(meta, count); put32(meta + 4u, float_bits(levels->rel_error[l]));
        if (l > 0u) {
            for (u32 i = 0; i < count; i++) put32(data + offset + (usize)i * 4u, levels->indices[l][i]);
            offset += (usize)count * 4u;
        }
    }
    *out_data = data;
    *out_size = size;
    return true;
}

static bool atomic_write(const char *path, const u8 *data, usize size) {
    char temp[1088];
    u32 id = atomic_fetch_add(&g_temp_counter, 1u);
    int n = snprintf(temp, sizeof(temp), "%s.tmp.%d.%u", path, lod_cache_pid(), id);
    if (n <= 0 || (usize)n >= sizeof(temp)) return false;
    FILE *f = fopen(temp, "wb");
    if (!f) return false;
    bool ok = fwrite(data, 1, size, f) == size && fflush(f) == 0;
    if (fclose(f) != 0) ok = false;
    if (ok) {
#ifdef _WIN32
        ok = MoveFileExA(temp, path, MOVEFILE_REPLACE_EXISTING | MOVEFILE_WRITE_THROUGH) != 0;
#else
        ok = rename(temp, path) == 0;
#endif
    }
    if (!ok) remove(temp);
    return ok;
}

void lod_cache_generate(LodCache *cache, const f32 *vertices, u32 vertex_count,
                        u32 vertex_stride, const u32 *indices, u32 index_count,
                        u32 max_levels, LodMeshLevels *out) {
    if (!out) return;
    memset(out, 0, sizeof(*out));
    if (!cache || !cache->directory || !cache->directory[0] ||
        !input_valid(vertices, vertex_count, vertex_stride, indices, index_count, max_levels)) {
        lod_generate_levels(vertices, vertex_count, vertex_stride, indices, index_count, max_levels, out);
        return;
    }

    LodCacheKey key = lod_cache_key(vertices, vertex_count, vertex_stride, indices, index_count, max_levels);
    char path[1024];
    if (!lod_cache_path(path, sizeof(path), cache->directory, key)) {
        lod_generate_levels(vertices, vertex_count, vertex_stride, indices, index_count, max_levels, out);
        return;
    }
    u64 max_file = LOD_CACHE_HEADER_SIZE + 3u * 8u + (u64)index_count * 2u * sizeof(u32);
    usize expected_max = max_file > (u64)LOD_CACHE_MAX_FILE ? (usize)LOD_CACHE_MAX_FILE : (usize)max_file;
    f64 io0 = cache_now_ms();
    usize size = 0;
    u8 *data = read_whole(path, expected_max, &size);
    bool hit = false;
    f64 stored_generation_ms = 0.0;
    if (data) {
        hit = decode(data, size, key, vertex_count, index_count, vertex_stride, max_levels,
                     out, &stored_generation_ms);
        cache->stats.read_bytes += size;
        free(data);
    }
    f64 hit_io_ms = cache_now_ms() - io0;
    cache->stats.io_ms += hit_io_ms;
    if (hit) {
        cache->stats.hits++;
        cache->stats.saved_ms += stored_generation_ms - hit_io_ms;
        return;
    }

    cache->stats.misses++;
    f64 gen0 = cache_now_ms();
    lod_generate_levels(vertices, vertex_count, vertex_stride, indices, index_count, max_levels, out);
    f64 generation_ms = cache_now_ms() - gen0;
    cache->stats.regenerate_ms += generation_ms;
    if (cache->writes_disabled) return;
    u8 *encoded = NULL;
    usize encoded_size = 0;
    if (!encode(out, key, vertex_count, index_count, vertex_stride, max_levels,
                generation_ms, &encoded, &encoded_size)) return;
    f64 write0 = cache_now_ms();
    bool ok = atomic_write(path, encoded, encoded_size);
    cache->stats.io_ms += cache_now_ms() - write0;
    if (ok) {
        cache->stats.write_bytes += encoded_size;
    } else {
        cache->stats.io_failed = true;
        cache->writes_disabled = true;
    }
    free(encoded);
}
