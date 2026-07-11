#include "mipmap_stream.h"
#include <core/log.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

/* Per-request context so the completion callback knows where the bytes go.
 * Allocated from an internal pool to avoid per-request malloc.
 * R167-D: request_id lets the callback reject stale completions after invalidate. */
typedef struct {
    MipmapStreamManager *mgr;
    u32 tex;
    u32 level;
    u64 request_id;
} MipLoadReq;

/* ========================================================================
 * Internal helpers
 * ======================================================================== */

/* Pool-based allocation for MipLoadReq: avoids malloc in hot path.
 * Slot stride must match sizeof(MipLoadReq) (24 bytes on 64-bit). Falls back
 * to malloc when the pool is exhausted. */
#define MIPMAP_REQ_SLOT_STRIDE 24
_Static_assert(sizeof(MipLoadReq) <= MIPMAP_REQ_SLOT_STRIDE,
               "MipLoadReq exceeds pool slot stride");

static MipLoadReq *mip_alloc_req(MipmapStreamManager *mgr) {
    if (mgr->req_pool_next < MIPMAP_STREAM_REQ_POOL_SIZE) {
        MipLoadReq *r = (MipLoadReq *)(mgr->req_pool + mgr->req_pool_next * MIPMAP_REQ_SLOT_STRIDE);
        mgr->req_pool_next++;
        return r;
    }
    return (MipLoadReq *)malloc(sizeof(MipLoadReq));
}

static void mip_free_req(MipLoadReq *req) {
    /* Pool-allocated entries are never individually freed; only malloc'd
     * fallbacks need freeing. Pool slots are reclaimed at shutdown. */
    if (!req) return;
    const u8 *pool_start = req->mgr ? req->mgr->req_pool : NULL;
    if (pool_start) {
        const u8 *p = (const u8 *)req;
        if (p >= pool_start &&
            p < pool_start + MIPMAP_STREAM_REQ_POOL_SIZE * MIPMAP_REQ_SLOT_STRIDE) {
            return; /* pool entry — no free needed */
        }
    }
    free(req);
}

/* Compute byte size of a single mipmap level.
 * R167-E: Return 0 on overflow instead of clamping to UINT32_MAX (which
 * corrupted level_offset accumulation). Caller must reject registration. */
static u32 mipmap_level_size(u32 width, u32 height, u32 level, u32 bpp) {
    u32 w = width >> level;
    u32 h = height >> level;
    if (w < 1) w = 1;
    if (h < 1) h = 1;
    usize bytes = (usize)w * (usize)h * (usize)bpp;
    return bytes > UINT32_MAX ? 0u : (u32)bytes;
}

/* Compute desired mipmap level from screen coverage using integer exponent
 * extraction instead of log2f. Each mip level halves resolution in both
 * dimensions, so level = floor(0.5 * log2(1/coverage)).
 *
 * For IEEE 754 floats, log2(x) ≈ exponent_bits - 127.
 * 1/coverage inverts: log2(1/c) = -log2(c) = -(exp_c - 127) = 127 - exp_c.
 * level = (127 - exp_c) >> 1. */
static u32 coverage_to_level(f32 coverage, u32 mip_count, u32 width, u32 height) {
    (void)width; (void)height;
    if (mip_count == 0) return 0;
    if (coverage >= 1.0f) return 0;
    if (coverage <= 0.0f) return mip_count - 1;

    /* Extract biased exponent from IEEE 754 float */
    u32 bits;
    memcpy(&bits, &coverage, sizeof(u32));
    i32 exp_bits = (i32)((bits >> 23) & 0xFF);  /* biased exponent */
    /* level ≈ floor(0.5 * (127 - exp_bits)) */
    i32 level = (127 - exp_bits) >> 1;
    if (level < 0) level = 0;
    if ((u32)level >= mip_count) level = (i32)(mip_count - 1);
    return (u32)level;
}

/* Recompute the finest resident level after a state change. */
static void mipmap_recompute_resident(StreamedTexture *tex) {
    tex->resident_level = tex->mip_count;
    for (u32 l = 0; l < tex->mip_count; l++) {
        if (tex->level_state[l] == MIPMAP_LEVEL_RESIDENT) {
            tex->resident_level = l;
            break;
        }
    }
}

/* Async completion callback. Runs on the main thread via async_loader_tick.
 * Ownership of `data` is transferred to us, so we either keep it (resident
 * cache) or free it. This is also where the real GPU upload is triggered.
 * Cancelled requests invoke this with data=NULL (R167-D async_loader_cancel). */
static void mipmap_load_callback(void *user_data, void *data, u32 size) {
    MipLoadReq *req = (MipLoadReq *)user_data;
    if (!req) { if (data) free(data); return; }

    MipmapStreamManager *mgr = req->mgr;
    u32 t = req->tex;
    u32 l = req->level;
    u64 req_id = req->request_id;
    mip_free_req(req);

    if (!mgr || t >= mgr->texture_count) { if (data) free(data); return; }
    StreamedTexture *tex = &mgr->textures[t];
    if (l >= tex->mip_count) { if (data) free(data); return; }

    /* R167-D: Reject stale completions after invalidate/re-request. */
    if (req_id == 0 || tex->level_request_id[l] != req_id ||
        tex->level_state[l] != MIPMAP_LEVEL_LOADING) {
        if (data) free(data);
        return;
    }

    /* Load failure / cancel: release the byte reservation made at request time. */
    if (!data || size == 0) {
        tex->level_state[l] = MIPMAP_LEVEL_UNLOADED;
        tex->level_request_id[l] = 0;
        if (mgr->total_resident_bytes >= tex->level_size[l])
            mgr->total_resident_bytes -= tex->level_size[l];
        return;
    }

    /* Take ownership of the loaded bytes as the resident cache copy. */
    if (tex->level_data[l]) free(tex->level_data[l]);
    tex->level_data[l] = data;
    tex->level_state[l] = MIPMAP_LEVEL_RESIDENT;
    tex->level_request_id[l] = 0;
    if (l < tex->resident_level) tex->resident_level = l;
    mgr->cache_hits++;

    /* Real GPU upload of this level. */
    if (mgr->upload_fn) {
        u32 w = tex->width >> l; if (w < 1) w = 1;
        u32 h = tex->height >> l; if (h < 1) h = 1;
        mgr->upload_fn(mgr->upload_ctx, (i32)t, l, w, h, data, size);
        mgr->uploads++;
    }
}

/* ========================================================================
 * Public API
 * ======================================================================== */

bool mipmap_stream_init(MipmapStreamManager *mgr, usize memory_budget) {
    if (!mgr) return false;
    memset(mgr, 0, sizeof(*mgr));
    mgr->memory_budget = memory_budget > 0 ? memory_budget : (64 * 1024 * 1024); /* 64MB default */
    mgr->ready = true;
    LOG_INFO("MipmapStream: initialized (budget=%zu MB)", mgr->memory_budget / (1024 * 1024));
    return true;
}

void mipmap_stream_shutdown(MipmapStreamManager *mgr) {
    if (!mgr || !mgr->ready) return;

    /* R172: Cancel in-flight loads so callbacks free MipLoadReq before async dies. */
    for (u32 t = 0; t < mgr->texture_count; t++) {
        StreamedTexture *tex = &mgr->textures[t];
        if (!tex->active) continue;
        for (u32 l = 0; l < tex->mip_count; l++) {
            if (tex->level_state[l] == MIPMAP_LEVEL_LOADING && tex->level_request_id[l] != 0) {
                async_loader_cancel(tex->level_request_id[l]);
                tex->level_request_id[l] = 0;
                tex->level_state[l] = MIPMAP_LEVEL_UNLOADED;
            }
        }
    }
    async_loader_tick();

    /* Free all resident level data */
    for (u32 t = 0; t < mgr->texture_count; t++) {
        StreamedTexture *tex = &mgr->textures[t];
        if (!tex->active) continue;
        for (u32 l = 0; l < tex->mip_count; l++) {
            if (tex->level_data[l]) {
                free(tex->level_data[l]);
                tex->level_data[l] = NULL;
            }
        }
    }

    LOG_INFO("MipmapStream: shutdown (loads=%u evictions=%u hits=%u)",
             mgr->load_requests, mgr->evictions, mgr->cache_hits);
    mgr->ready = false;
}

i32 mipmap_stream_register(MipmapStreamManager *mgr, const char *path,
                            u32 width, u32 height, u32 mip_count,
                            u32 bytes_per_pixel) {
    if (!mgr || !mgr->ready || !path) return -1;
    if (mgr->texture_count >= MIPMAP_STREAM_MAX_TEXTURES) return -1;
    /* R170: Reject zero dims/mips/bpp before allocating a slot (mip_count-1 underflow). */
    if (width == 0u || height == 0u || mip_count == 0u || bytes_per_pixel == 0u) return -1;
    if (mip_count > MIPMAP_STREAM_MAX_LEVELS) mip_count = MIPMAP_STREAM_MAX_LEVELS;

    i32 idx = (i32)mgr->texture_count++;
    StreamedTexture *tex = &mgr->textures[idx];

    memset(tex, 0, sizeof(*tex));
    strncpy(tex->path, path, sizeof(tex->path) - 1);
    tex->path[sizeof(tex->path) - 1] = '\0';
    tex->width = width;
    tex->height = height;
    tex->mip_count = mip_count;
    tex->bytes_per_pixel = bytes_per_pixel;
    tex->active = true;
    tex->desired_level = mip_count - 1; /* start with smallest */
    tex->resident_level = mip_count;    /* nothing loaded yet */

    /* Compute offsets for each mipmap level in the file */
    /* R145: Use usize for offset accumulation to prevent u32 overflow */
    usize offset = 0;
    for (u32 l = 0; l < mip_count; l++) {
        u32 sz = mipmap_level_size(width, height, l, bytes_per_pixel);
        /* R167-E: Reject textures whose level size overflows u32 — clamping
         * would corrupt subsequent level_offset values. */
        if (sz == 0) {
            LOG_ERROR("MipmapStream: level %u size overflow for '%s' (%ux%u bpp=%u)",
                      l, path, width, height, bytes_per_pixel);
            mgr->texture_count--;
            return -1;
        }
        tex->level_offset[l] = (u64)offset;
        tex->level_size[l] = sz;
        tex->level_state[l] = MIPMAP_LEVEL_UNLOADED;
        offset += sz;
    }

    LOG_DEBUG("MipmapStream: registered '%s' (%ux%u, %u mips, %u bpp)",
              path, width, height, mip_count, bytes_per_pixel);
    return idx;
}

void mipmap_stream_update_visibility(MipmapStreamManager *mgr, i32 tex_idx,
                                      f32 screen_coverage, u64 frame_number) {
    if (!mgr || !mgr->ready || tex_idx < 0 || (u32)tex_idx >= mgr->texture_count) return;
    StreamedTexture *tex = &mgr->textures[tex_idx];
    if (!tex->active) return;

    tex->screen_coverage = screen_coverage;
    tex->desired_level = coverage_to_level(screen_coverage, tex->mip_count,
                                           tex->width, tex->height);
    if (screen_coverage > 0.0f) {
        tex->last_visible_frame = frame_number;
    }
}

void mipmap_stream_update(MipmapStreamManager *mgr) {
    if (!mgr || !mgr->ready) return;

    /* Note: residency transitions happen in mipmap_load_callback, which the
     * host drives via async_loader_tick(). This function only issues new load
     * requests and evicts the resident cache under memory pressure. */

    /* Phase 1: Request desired levels that aren't resident or loading. */
    for (u32 t = 0; t < mgr->texture_count; t++) {
        StreamedTexture *tex = &mgr->textures[t];
        if (!tex->active) continue;

        u32 desired = tex->desired_level;
        if (desired >= tex->mip_count) desired = tex->mip_count - 1;

        if (tex->level_state[desired] == MIPMAP_LEVEL_UNLOADED) {
            u32 needed = tex->level_size[desired];
            /* R171: If over budget, evict this texture's finer resident levels
             * first so desired mip can load (previously skipped forever). */
            if (mgr->total_resident_bytes + needed > mgr->memory_budget) {
                for (u32 l = 0; l < desired && l < tex->mip_count; l++) {
                    if (tex->level_state[l] != MIPMAP_LEVEL_RESIDENT) continue;
                    if (tex->level_data[l]) {
                        free(tex->level_data[l]);
                        tex->level_data[l] = NULL;
                    }
                    tex->level_state[l] = MIPMAP_LEVEL_UNLOADED;
                    if (mgr->total_resident_bytes >= tex->level_size[l])
                        mgr->total_resident_bytes -= tex->level_size[l];
                    mgr->evictions++;
                }
                mipmap_recompute_resident(tex);
            }
            if (mgr->total_resident_bytes + needed > mgr->memory_budget) {
                continue;
            }

            MipLoadReq *ctx = mip_alloc_req(mgr);
            if (!ctx) continue;
            ctx->mgr = mgr;
            ctx->tex = t;
            ctx->level = desired;
            ctx->request_id = 0;

            u64 req_id = async_loader_request_range_priority(
                tex->path,
                tex->level_offset[desired],
                tex->level_size[desired],
                mipmap_load_callback,
                ctx,
                (i32)ASYNC_PRIORITY_MIP((i32)desired)
            );

            if (req_id > 0) {
                ctx->request_id = req_id;
                tex->level_state[desired] = MIPMAP_LEVEL_LOADING;
                tex->level_request_id[desired] = req_id;
                mgr->load_requests++;
                mgr->total_resident_bytes += needed; /* reserve until resident */
            } else {
                mip_free_req(ctx);
            }
        }
    }

    /* Phase 2: Evict resident levels finer than desired when over budget. */
    if (mgr->total_resident_bytes > mgr->memory_budget) {
        for (u32 t = 0; t < mgr->texture_count; t++) {
            if (mgr->total_resident_bytes <= mgr->memory_budget) break;

            StreamedTexture *tex = &mgr->textures[t];
            if (!tex->active) continue;

            for (u32 l = 0; l < tex->desired_level && l < tex->mip_count; l++) {
                if (tex->level_state[l] == MIPMAP_LEVEL_RESIDENT) {
                    if (tex->level_data[l]) {
                        free(tex->level_data[l]);
                        tex->level_data[l] = NULL;
                    }
                    tex->level_state[l] = MIPMAP_LEVEL_UNLOADED;
                    if (mgr->total_resident_bytes >= tex->level_size[l])
                        mgr->total_resident_bytes -= tex->level_size[l];
                    mgr->evictions++;
                }
            }
            mipmap_recompute_resident(tex);
        }
    }
}

void *mipmap_stream_get_level(MipmapStreamManager *mgr, i32 tex_idx, u32 level) {
    if (!mgr || !mgr->ready || tex_idx < 0 || (u32)tex_idx >= mgr->texture_count) return NULL;
    StreamedTexture *tex = &mgr->textures[tex_idx];
    if (!tex->active || level >= tex->mip_count) return NULL;
    if (tex->level_state[level] != MIPMAP_LEVEL_RESIDENT) return NULL;
    return tex->level_data[level];
}

bool mipmap_stream_force_level(MipmapStreamManager *mgr, i32 tex_idx, u32 level) {
    if (!mgr || !mgr->ready || tex_idx < 0 || (u32)tex_idx >= mgr->texture_count) return false;
    StreamedTexture *tex = &mgr->textures[tex_idx];
    if (!tex->active || level >= tex->mip_count) return false;

    /* Already resident */
    if (tex->level_state[level] == MIPMAP_LEVEL_RESIDENT) return true;

    /* Issue the load if it isn't already in flight. */
    if (tex->level_state[level] == MIPMAP_LEVEL_UNLOADED) {
        u32 needed = tex->level_size[level];
        /* R172: Evict finer levels then respect budget (same as update path). */
        if (mgr->total_resident_bytes + needed > mgr->memory_budget) {
            for (u32 l = 0; l < level && l < tex->mip_count; l++) {
                if (tex->level_state[l] != MIPMAP_LEVEL_RESIDENT) continue;
                if (tex->level_data[l]) {
                    free(tex->level_data[l]);
                    tex->level_data[l] = NULL;
                }
                tex->level_state[l] = MIPMAP_LEVEL_UNLOADED;
                if (mgr->total_resident_bytes >= tex->level_size[l])
                    mgr->total_resident_bytes -= tex->level_size[l];
                mgr->evictions++;
            }
            mipmap_recompute_resident(tex);
        }
        if (mgr->total_resident_bytes + needed > mgr->memory_budget) {
            return false;
        }

        MipLoadReq *ctx = mip_alloc_req(mgr);
        if (!ctx) return false;
        ctx->mgr = mgr;
        ctx->tex = (u32)tex_idx;
        ctx->level = level;
        ctx->request_id = 0;

        u64 req_id = async_loader_request_range_priority(
            tex->path,
            tex->level_offset[level],
            tex->level_size[level],
            mipmap_load_callback,
            ctx,
            (i32)ASYNC_PRIORITY_MIP((i32)level)
        );
        if (req_id == 0) { mip_free_req(ctx); return false; }

        ctx->request_id = req_id;
        tex->level_state[level] = MIPMAP_LEVEL_LOADING;
        tex->level_request_id[level] = req_id;
        mgr->load_requests++;
        mgr->total_resident_bytes += needed; /* reserve */
    }

    /* Block until the completion callback marks the level resident. We pump
     * async_loader_tick() ourselves since residency is delivered there. */
    u32 timeout = 1000000;
    while (timeout > 0) {
        async_loader_tick();
        if (tex->level_state[level] == MIPMAP_LEVEL_RESIDENT) return true;
        if (tex->level_state[level] == MIPMAP_LEVEL_UNLOADED) return false; /* failed */
        timeout--;
    }
    return false;
}

void mipmap_stream_set_upload(MipmapStreamManager *mgr, MipmapUploadFn fn, void *ctx) {
    if (!mgr) return;
    mgr->upload_fn = fn;
    mgr->upload_ctx = ctx;
}

u32 mipmap_stream_resident_level(MipmapStreamManager *mgr, i32 tex_idx) {
    if (!mgr || tex_idx < 0 || (u32)tex_idx >= mgr->texture_count) return 0;
    return mgr->textures[tex_idx].resident_level;
}

u32 mipmap_stream_load_requests(MipmapStreamManager *mgr) {
    return mgr ? mgr->load_requests : 0;
}

u32 mipmap_stream_evictions(MipmapStreamManager *mgr) {
    return mgr ? mgr->evictions : 0;
}

u32 mipmap_stream_uploads(MipmapStreamManager *mgr) {
    return mgr ? mgr->uploads : 0;
}

usize mipmap_stream_resident_bytes(MipmapStreamManager *mgr) {
    return mgr ? mgr->total_resident_bytes : 0;
}

void mipmap_stream_invalidate(MipmapStreamManager *mgr, i32 tex_idx) {
    if (!mgr || !mgr->ready || tex_idx < 0 || (u32)tex_idx >= mgr->texture_count) return;
    StreamedTexture *tex = &mgr->textures[tex_idx];
    if (!tex->active) return;

    for (u32 l = 0; l < tex->mip_count; l++) {
        u64 inflight = 0;
        if (tex->level_state[l] == MIPMAP_LEVEL_LOADING && tex->level_request_id[l] != 0) {
            /* Mark stale BEFORE cancel so the cancel callback (NULL data) does
             * not double-subtract the budget reservation. */
            inflight = tex->level_request_id[l];
            if (mgr->total_resident_bytes >= tex->level_size[l])
                mgr->total_resident_bytes -= tex->level_size[l];
            tex->level_state[l] = MIPMAP_LEVEL_UNLOADED;
            tex->level_request_id[l] = 0;
            async_loader_cancel(inflight);
        } else if (tex->level_state[l] == MIPMAP_LEVEL_RESIDENT) {
            if (mgr->total_resident_bytes >= tex->level_size[l])
                mgr->total_resident_bytes -= tex->level_size[l];
        }
        if (tex->level_data[l]) {
            free(tex->level_data[l]);
            tex->level_data[l] = NULL;
        }
        tex->level_state[l] = MIPMAP_LEVEL_UNLOADED;
        tex->level_request_id[l] = 0;
    }
    tex->resident_level = tex->mip_count;
    LOG_INFO("MipmapStream: invalidated '%s'", tex->path);
}
