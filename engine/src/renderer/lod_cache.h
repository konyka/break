#pragma once
#include <renderer/lod_gen.h>

#define LOD_CACHE_FORMAT_VERSION 1u
#define LOD_CACHE_HEADER_SIZE 80u

typedef struct {
    u64 first;
    u64 second;
} LodCacheKey;

typedef struct {
    u64 hits;
    u64 misses;
    u64 read_bytes;
    u64 write_bytes;
    f64 regenerate_ms;
    f64 io_ms;
    f64 saved_ms; /* stored miss-generation time minus hit-read time */
    bool io_failed;
} LodCacheStats;

typedef struct {
    const char *directory;
    LodCacheStats stats;
    bool writes_disabled;
} LodCache;

void lod_cache_init(LodCache *cache, const char *directory);
LodCacheKey lod_cache_key(const f32 *vertices, u32 vertex_count, u32 vertex_stride,
                          const u32 *indices, u32 index_count, u32 max_levels);
bool lod_cache_path(char *out, usize out_size, const char *directory, LodCacheKey key);

/* NULL/empty directory: direct lod_generate_levels, no file I/O or stats.
 * Otherwise load a validated hit or regenerate and atomically write the miss. */
void lod_cache_generate(LodCache *cache, const f32 *vertices, u32 vertex_count,
                        u32 vertex_stride, const u32 *indices, u32 index_count,
                        u32 max_levels, LodMeshLevels *out);
