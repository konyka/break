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
/* R707a: extra_key bytes (e.g. skinning poses) also enter the hash; with
 * extra_key_size 0 the key equals lod_cache_key. */
LodCacheKey lod_cache_key_ex(const f32 *vertices, u32 vertex_count, u32 vertex_stride,
                             const u32 *indices, u32 index_count, u32 max_levels,
                             const void *extra_key, usize extra_key_size);
bool lod_cache_path(char *out, usize out_size, const char *directory, LodCacheKey key);

/* NULL/empty directory: direct lod_generate_levels, no file I/O or stats.
 * Otherwise load a validated hit or regenerate and atomically write the miss. */
void lod_cache_generate(LodCache *cache, const f32 *vertices, u32 vertex_count,
                        u32 vertex_stride, const u32 *indices, u32 index_count,
                        u32 max_levels, LodMeshLevels *out);

/* R707a: same cache with a caller generator (called on a miss, on invalid
 * input and with no cache directory; out is zeroed first). The key is
 * lod_cache_key_ex(..., extra_key, extra_key_size), so callers must put every
 * generator input beyond vertices/indices/stride/max_levels into extra_key.
 * Hits are validated as in lod_cache_generate (counts, stop ratio, indices
 * < vertex_count); the file format is unchanged. */
typedef void (*LodCacheGenerateFn)(void *user, LodMeshLevels *out);
void lod_cache_generate_ex(LodCache *cache, const f32 *vertices, u32 vertex_count,
                           u32 vertex_stride, const u32 *indices, u32 index_count,
                           u32 max_levels, const void *extra_key, usize extra_key_size,
                           LodCacheGenerateFn generate, void *user, LodMeshLevels *out);
