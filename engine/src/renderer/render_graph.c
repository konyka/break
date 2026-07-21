/* ============================================================================
 *  render_graph.c — Declarative render-pass graph with automatic resource
 *                   management, dead-pass culling and lifetime aliasing.
 *
 *  Pure CPU-side scheduler.  All GPU resources are routed through the RHI
 *  abstraction (rhi_texture_create / rhi_buffer_create / *_destroy).  No
 *  direct GL / Vulkan calls.
 *
 *  Memory model: a single malloc for the RenderGraph itself; everything else
 *  lives in fixed-size arrays.
 * ==========================================================================*/

#include "render_graph.h"
#include "../core/log.h"

#include <stdlib.h>
#include <string.h>

/* ---------------------------------------------------------------------------
 *  Small helpers
 * -------------------------------------------------------------------------*/

static void rg_copy_name(char *dst, const char *src)
{
    if (!src) {
        dst[0] = '\0';
        return;
    }
    /* sizeof field is 64; truncate safely. memchr+memcpy is faster than
     * byte-by-byte loop (bulk scan + bulk copy). */
    const char *end = (const char *)memchr(src, '\0', 63);
    size_t len = end ? (size_t)(end - src) : 63;
    memcpy(dst, src, len);
    dst[len] = '\0';
}

static bool rg_resource_index_valid(const RenderGraph *rg, RGResource h)
{
    return rg != NULL && h != RG_INVALID_RESOURCE && h < rg->resource_count;
}

/* Whether a usage represents a finalised "external" output.  Such writes
   anchor the dead-pass culling pass: any pass producing one of these is
   considered "live" and is the seed of the back-traversal. */
static bool rg_is_output_usage(RGResourceUsage u)
{
    return u == RG_USAGE_PRESENT;
}

/* ---------------------------------------------------------------------------
 *  Lifetime
 * -------------------------------------------------------------------------*/

RenderGraph *rg_create(void)
{
    RenderGraph *rg = (RenderGraph *)calloc(1, sizeof(RenderGraph));
    if (!rg) {
        LOG_ERROR("rg_create: out of memory");
        return NULL;
    }
    rg->compiled = false;
    rg->device = NULL;
    return rg;
}

void rg_set_device(RenderGraph *rg, RHIDevice *dev)
{
    if (!rg) return;
    rg->device = dev;
}

void rg_destroy(RenderGraph *rg)
{
    if (!rg) return;

    /* Destroy any textures the graph still owns, both live resources and
       free-list entries. */
    if (rg->device) {
        for (u32 i = 0; i < rg->resource_count; i++) {
            RGResourceInfo *info = &rg->resources[i];
            if (info->allocated && !info->is_imported && !info->is_buffer &&
                rhi_handle_valid(info->physical_texture)) {
                rhi_texture_destroy(rg->device, info->physical_texture);
            }
        }
        for (u32 i = 0; i < rg->pool_count; i++) {
            if (rhi_handle_valid(rg->texture_pool[i].tex)) {
                rhi_texture_destroy(rg->device, rg->texture_pool[i].tex);
            }
        }
    }

    free(rg);
}

void rg_reset(RenderGraph *rg)
{
    if (!rg) return;

    /* Return all RG-owned textures to the pool so the next frame can alias
       them rather than reallocate. */
    for (u32 i = 0; i < rg->resource_count; i++) {
        RGResourceInfo *info = &rg->resources[i];
        if (info->allocated && !info->is_imported && !info->is_buffer &&
            rhi_handle_valid(info->physical_texture)) {
            /* R308 (CORRECTNESS): a texture claimed from the pool this frame is
             * ALREADY a pool entry — rg_pool_claim leaves the entry in place and
             * only flips in_use, it does not remove it. Re-adding it here would
             * create a second entry holding the same RHITexture handle, and then:
             *   (1) a later frame's rg_pool_claim can hand that one physical
             *       texture to two DISTINCT RG resources → they alias and clobber
             *       each other's contents;
             *   (2) rg_destroy walks the whole pool and rhi_texture_destroy()s the
             *       shared handle once per duplicate → double free;
             *   (3) the pool grows by one dup per frame until it overflows
             *       RG_MAX_RESOURCES and starts destroying live textures.
             * Only pool a texture that isn't already there; the trailing loop
             * below resets in_use so the existing entry is reusable next frame. */
            bool already_pooled = false;
            for (u32 j = 0; j < rg->pool_count; j++) {
                if (rg->texture_pool[j].tex.index == info->physical_texture.index &&
                    rg->texture_pool[j].tex.generation == info->physical_texture.generation) {
                    already_pooled = true;
                    break;
                }
            }
            if (already_pooled) continue;
            if (rg->pool_count < RG_MAX_RESOURCES) {
                RGTexturePoolEntry *e = &rg->texture_pool[rg->pool_count++];
                e->tex        = info->physical_texture;
                e->width      = info->tex_desc.width;
                e->height     = info->tex_desc.height;
                e->format     = info->tex_desc.format;
                e->mip_levels = info->tex_desc.mip_levels;
                e->in_use     = false;
            } else {
                /* Pool full — destroy directly. */
                if (rg->device) rhi_texture_destroy(rg->device, info->physical_texture);
            }
        }
    }

    rg->pass_count      = 0;
    rg->resource_count  = 0;
    rg->execution_count = 0;
    rg->culled_count    = 0;
    rg->compiled        = false;

    /* Mark every pool entry as available again. */
    for (u32 i = 0; i < rg->pool_count; i++) {
        rg->texture_pool[i].in_use = false;
    }
}

/* ---------------------------------------------------------------------------
 *  Pass declaration
 * -------------------------------------------------------------------------*/

RGPass *rg_add_pass(RenderGraph *rg, const char *name, RGPassType type)
{
    if (!rg) return NULL;
    if (rg->pass_count >= RG_MAX_PASSES) {
        LOG_ERROR("rg_add_pass: pass limit (%u) reached", RG_MAX_PASSES);
        return NULL;
    }

    RGPass *p = &rg->passes[rg->pass_count];
    memset(p, 0, sizeof(*p));
    rg_copy_name(p->name, name);
    p->type            = type;
    p->owner           = rg;
    p->index           = rg->pass_count;
    p->execution_order = 0xFFFFFFFFu;
    p->culled          = false;

    rg->pass_count++;
    rg->compiled = false;
    return p;
}

void rg_pass_read(RGPass *pass, RGResource res, RGResourceUsage usage)
{
    if (!pass || !pass->owner) return;
    if (!rg_resource_index_valid(pass->owner, res)) {
        LOG_WARN("rg_pass_read: invalid resource handle %u", res);
        return;
    }
    if (pass->read_count >= RG_MAX_PASS_DEPS) {
        LOG_ERROR("rg_pass_read: read slot exhausted on pass '%s'", pass->name);
        return;
    }

    RGPassAccess *a = &pass->reads[pass->read_count++];
    a->resource = res;
    a->usage    = usage;
    a->is_write = false;

    RGResourceInfo *info = &pass->owner->resources[res];
    info->ref_count++;
    info->last_read_pass = pass->index;
    pass->owner->compiled = false;
}

RGResource rg_pass_write(RGPass *pass, RGResource res, RGResourceUsage usage)
{
    if (!pass || !pass->owner) return RG_INVALID_RESOURCE;
    if (!rg_resource_index_valid(pass->owner, res)) {
        LOG_WARN("rg_pass_write: invalid resource handle %u", res);
        return RG_INVALID_RESOURCE;
    }
    if (pass->write_count >= RG_MAX_PASS_DEPS) {
        LOG_ERROR("rg_pass_write: write slot exhausted on pass '%s'", pass->name);
        return RG_INVALID_RESOURCE;
    }

    RGPassAccess *a = &pass->writes[pass->write_count++];
    a->resource = res;
    a->usage    = usage;
    a->is_write = true;

    RGResourceInfo *info = &pass->owner->resources[res];
    info->ref_count++;
    if (info->first_write_pass == RG_INVALID_RESOURCE) {
        info->first_write_pass = pass->index;
    }
    pass->owner->compiled = false;
    return res;
}

void rg_pass_set_execute(RGPass *pass,
                         void (*fn)(void *ctx, RGPass *pass),
                         void *ctx)
{
    if (!pass) return;
    pass->execute = fn;
    pass->ctx     = ctx;
}

/* ---------------------------------------------------------------------------
 *  Resource declaration
 * -------------------------------------------------------------------------*/

static RGResourceInfo *rg_alloc_resource(RenderGraph *rg, RGResource *out_handle)
{
    if (rg->resource_count >= RG_MAX_RESOURCES) {
        LOG_ERROR("rg_alloc_resource: resource limit (%u) reached",
                  RG_MAX_RESOURCES);
        if (out_handle) *out_handle = RG_INVALID_RESOURCE;
        return NULL;
    }
    RGResource h = rg->resource_count++;
    RGResourceInfo *info = &rg->resources[h];
    memset(info, 0, sizeof(*info));
    info->first_write_pass = RG_INVALID_RESOURCE;
    info->last_read_pass   = RG_INVALID_RESOURCE;
    info->physical_texture = RHI_HANDLE_NULL;
    info->physical_buffer  = RHI_HANDLE_NULL;
    if (out_handle) *out_handle = h;
    return info;
}

RGResource rg_create_texture(RenderGraph *rg, const char *name,
                             const RGTextureDesc *desc)
{
    if (!rg || !desc) return RG_INVALID_RESOURCE;
    RGResource h;
    RGResourceInfo *info = rg_alloc_resource(rg, &h);
    if (!info) return RG_INVALID_RESOURCE;

    rg_copy_name(info->name, name);
    info->is_imported = false;
    info->is_buffer   = false;
    info->tex_desc    = *desc;
    /* The caller may pass desc->name; ensure the persisted name in the desc
       still points to something stable: we copy the canonical name in. */
    info->tex_desc.name = info->name;

    rg->compiled = false;
    return h;
}

RGResource rg_create_buffer(RenderGraph *rg, const char *name,
                            const RGBufferDesc *desc)
{
    if (!rg || !desc) return RG_INVALID_RESOURCE;
    RGResource h;
    RGResourceInfo *info = rg_alloc_resource(rg, &h);
    if (!info) return RG_INVALID_RESOURCE;

    rg_copy_name(info->name, name);
    info->is_imported   = false;
    info->is_buffer     = true;
    info->buf_desc      = *desc;
    info->buf_desc.name = info->name;

    rg->compiled = false;
    return h;
}

RGResource rg_import_texture(RenderGraph *rg, const char *name,
                             RHITexture external)
{
    if (!rg) return RG_INVALID_RESOURCE;
    RGResource h;
    RGResourceInfo *info = rg_alloc_resource(rg, &h);
    if (!info) return RG_INVALID_RESOURCE;

    rg_copy_name(info->name, name);
    info->is_imported      = true;
    info->is_buffer        = false;
    info->physical_texture = external;
    info->tex_desc.name    = info->name;
    rg->compiled = false;
    return h;
}

RGResource rg_import_buffer(RenderGraph *rg, const char *name,
                            RHIBuffer external)
{
    if (!rg) return RG_INVALID_RESOURCE;
    RGResource h;
    RGResourceInfo *info = rg_alloc_resource(rg, &h);
    if (!info) return RG_INVALID_RESOURCE;

    rg_copy_name(info->name, name);
    info->is_imported     = true;
    info->is_buffer       = true;
    info->physical_buffer = external;
    info->buf_desc.name   = info->name;
    rg->compiled = false;
    return h;
}

/* ---------------------------------------------------------------------------
 *  Compile: dependency derivation, dead-pass culling, topological sort,
 *           physical resource allocation, cycle detection.
 * -------------------------------------------------------------------------*/

/* Helper: derive the dependency list of a single pass (passes that write any
   resource this pass reads). */
static void rg_derive_dependencies(RenderGraph *rg, u32 p)
{
    RGPass *pass = &rg->passes[p];
    pass->dep_count = 0;

    for (u32 r = 0; r < pass->read_count; r++) {
        RGResource res = pass->reads[r].resource;
        if (!rg_resource_index_valid(rg, res)) continue;

        RGResourceInfo *info = &rg->resources[res];
        if (info->first_write_pass == RG_INVALID_RESOURCE) continue;
        if (info->first_write_pass == p) continue;

        /* Dedup against existing deps. */
        bool already = false;
        for (u32 d = 0; d < pass->dep_count; d++) {
            if (pass->dependencies[d] == info->first_write_pass) {
                already = true;
                break;
            }
        }
        if (already) continue;

        if (pass->dep_count >= RG_MAX_PASS_DEPS) {
            LOG_WARN("rg_compile: dependency slot exhausted on pass '%s'",
                     pass->name);
            break;
        }
        pass->dependencies[pass->dep_count++] = info->first_write_pass;
    }
}

/* Helper: dead-code elimination.  A pass is "live" if any of its writes lands
   on either an imported resource (assumed observable by the host) or carries
   a PRESENT usage.  From the live seed set we walk dependencies backwards
   and mark every reachable pass as live too. */
static void rg_cull_dead_passes(RenderGraph *rg)
{
    /* Initial: everything culled. */
    for (u32 p = 0; p < rg->pass_count; p++) {
        rg->passes[p].culled = true;
    }

    /* Mark seeds. */
    u32 stack[RG_MAX_PASSES];
    u32 sp = 0;

    for (u32 p = 0; p < rg->pass_count; p++) {
        RGPass *pass = &rg->passes[p];
        bool live = false;
        for (u32 w = 0; w < pass->write_count && !live; w++) {
            RGResource r = pass->writes[w].resource;
            if (!rg_resource_index_valid(rg, r)) continue;
            const RGResourceInfo *info = &rg->resources[r];
            if (info->is_imported)                live = true;
            else if (rg_is_output_usage(pass->writes[w].usage)) live = true;
        }
        if (live) {
            pass->culled = false;
            stack[sp++]  = p;
        }
    }

    /* Walk backwards over dependency edges. */
    while (sp > 0) {
        u32 p = stack[--sp];
        const RGPass *pass = &rg->passes[p];
        for (u32 d = 0; d < pass->dep_count; d++) {
            u32 dep = pass->dependencies[d];
            if (dep < rg->pass_count && rg->passes[dep].culled) {
                rg->passes[dep].culled = false;
                stack[sp++] = dep;
            }
        }
    }

    /* Count culled passes for stats. */
    rg->culled_count = 0;
    for (u32 p = 0; p < rg->pass_count; p++) {
        if (rg->passes[p].culled) rg->culled_count++;
    }
}

/* Helper: Kahn's algorithm topological sort over the live sub-graph.
 * Uses a reverse adjacency list (dependents) for O(V+E) instead of O(V^2). */
static bool rg_topo_sort(RenderGraph *rg)
{
    u32 in_degree[RG_MAX_PASSES];
    memset(in_degree, 0, sizeof(in_degree));

    /* Build reverse adjacency list: rdeps[p] = passes that depend on p.
     *
     * R328 (CORRECTNESS): the second dimension must be RG_MAX_PASSES, not
     * RG_MAX_PASS_DEPS. `dependencies[]` is bounded by RG_MAX_PASS_DEPS because
     * a pass depends on at most one producer per resource it reads (<=16 reads).
     * But the REVERSE relation is unbounded by that: a single producer (e.g. a
     * depth prepass or gbuffer written once) can be read by every other live
     * pass, so it may have up to pass_count-1 (<= RG_MAX_PASSES-1) dependents.
     * The old [RG_MAX_PASS_DEPS] array + `rdeps_count[dep] < RG_MAX_PASS_DEPS`
     * guard silently DROPPED reverse edges past the 16th dependent while still
     * counting them in in_degree[p]. Those dropped dependents' in_degree was
     * then never decremented when the producer was scheduled, so it never
     * reached 0, they were never enqueued, execution_count < live_total, and
     * rg_compile spuriously reported a "cyclic dependency" and refused to run a
     * perfectly acyclic graph. Size the fan-out array to RG_MAX_PASSES so every
     * reverse edge is recorded (rdeps_count[dep] <= pass_count-1 < RG_MAX_PASSES,
     * so the guard is now purely defensive). */
    u32 rdeps[RG_MAX_PASSES][RG_MAX_PASSES];
    u32 rdeps_count[RG_MAX_PASSES];
    memset(rdeps_count, 0, sizeof(rdeps_count));

    for (u32 p = 0; p < rg->pass_count; p++) {
        if (rg->passes[p].culled) continue;
        for (u32 d = 0; d < rg->passes[p].dep_count; d++) {
            u32 dep = rg->passes[p].dependencies[d];
            if (dep < rg->pass_count && !rg->passes[dep].culled) {
                in_degree[p]++;
                if (rdeps_count[dep] < RG_MAX_PASSES) {
                    rdeps[dep][rdeps_count[dep]++] = p;
                }
            }
        }
    }

    /* Seed queue with all live passes that have no live dependencies. */
    u32 queue[RG_MAX_PASSES];
    u32 front = 0, back = 0;
    for (u32 p = 0; p < rg->pass_count; p++) {
        if (rg->passes[p].culled) continue;
        if (in_degree[p] == 0) queue[back++] = p;
    }

    rg->execution_count = 0;
    while (front < back) {
        u32 p = queue[front++];
        rg->execution_order[rg->execution_count] = p;
        rg->passes[p].execution_order = rg->execution_count;
        rg->execution_count++;

        /* Decrement successors using reverse adjacency list — O(deps)
         * instead of scanning all V passes. */
        for (u32 s = 0; s < rdeps_count[p]; s++) {
            u32 q = rdeps[p][s];
            if (in_degree[q] > 0 && --in_degree[q] == 0) {
                queue[back++] = q;
            }
        }
    }

    /* Cycle check: every live pass must end up scheduled. */
    u32 live_total = rg->pass_count - rg->culled_count;
    if (rg->execution_count != live_total) {
        LOG_ERROR("rg_compile: cyclic dependency detected (%u/%u scheduled)",
                  rg->execution_count, live_total);
        return false;
    }
    return true;
}

/* Helper: try to claim a pooled texture matching the requested description.
   The pool is a simple lifetime-aliasing free-list; once claimed, the entry
   is removed so subsequent allocations cannot alias it. */
static bool rg_pool_claim(RenderGraph *rg, const RGTextureDesc *desc,
                          RHITexture *out)
{
    for (u32 i = 0; i < rg->pool_count; i++) {
        RGTexturePoolEntry *e = &rg->texture_pool[i];
        if (e->in_use) continue;
        if (e->width != desc->width)         continue;
        if (e->height != desc->height)       continue;
        if (e->format != desc->format)       continue;
        if (e->mip_levels != desc->mip_levels) continue;
        if (!rhi_handle_valid(e->tex))       continue;

        *out      = e->tex;
        e->in_use = true;
        return true;
    }
    return false;
}

/* Helper: physical resource allocation for non-imported resources that are
   actually referenced by at least one live pass. */
static void rg_allocate_resources(RenderGraph *rg)
{
    for (u32 r = 0; r < rg->resource_count; r++) {
        RGResourceInfo *info = &rg->resources[r];
        if (info->is_imported)    continue;
        if (info->ref_count == 0) continue;
        if (info->allocated)      continue;

        if (info->is_buffer) {
            if (!rg->device) {
                LOG_WARN("rg_compile: no device set; skipping buffer '%s'",
                         info->name);
                continue;
            }
            RHIBufferDesc bd;
            memset(&bd, 0, sizeof(bd));
            bd.size  = info->buf_desc.size;
            bd.usage = (RHIBufferUsage)(RHI_BUFFER_USAGE_STORAGE);
            bd.initial_data = NULL;
            info->physical_buffer = rhi_buffer_create(rg->device, &bd);
            info->allocated = rhi_handle_valid(info->physical_buffer);
        } else {
            /* Try pool reuse first. */
            RHITexture chosen = RHI_HANDLE_NULL;
            if (rg_pool_claim(rg, &info->tex_desc, &chosen)) {
                info->physical_texture = chosen;
                info->allocated = true;
                continue;
            }
            if (!rg->device) {
                LOG_WARN("rg_compile: no device set; skipping texture '%s'",
                         info->name);
                continue;
            }
            RHITextureDesc td;
            memset(&td, 0, sizeof(td));
            td.width      = info->tex_desc.width;
            td.height     = info->tex_desc.height;
            td.format     = (RHIFormat)info->tex_desc.format;
            td.mip_levels = info->tex_desc.mip_levels ? info->tex_desc.mip_levels : 1;
            td.data       = NULL;
            info->physical_texture = rhi_texture_create(rg->device, &td);
            info->allocated = rhi_handle_valid(info->physical_texture);
        }
    }
}

bool rg_compile(RenderGraph *rg)
{
    if (!rg) return false;
    if (rg->pass_count == 0) {
        rg->execution_count = 0;
        rg->culled_count    = 0;
        rg->compiled        = true;
        return true;
    }

    /* 1. Dependency derivation per pass (must precede culling). */
    for (u32 p = 0; p < rg->pass_count; p++) {
        rg_derive_dependencies(rg, p);
    }

    /* 2. Dead pass culling. */
    rg_cull_dead_passes(rg);

    /* 3. Topological sort (Kahn). */
    if (!rg_topo_sort(rg)) {
        rg->compiled = false;
        return false;
    }

    /* 4. Physical resource allocation (with pool aliasing). */
    rg_allocate_resources(rg);

    rg->compiled = true;
    return true;
}

/* ---------------------------------------------------------------------------
 *  Execution
 * -------------------------------------------------------------------------*/

void rg_execute(RenderGraph *rg)
{
    if (!rg) return;
    if (!rg->compiled) {
        LOG_ERROR("rg_execute: render graph not compiled");
        return;
    }

    for (u32 i = 0; i < rg->execution_count; i++) {
        u32 pass_idx = rg->execution_order[i];
        if (pass_idx >= rg->pass_count) continue;
        RGPass *pass = &rg->passes[pass_idx];
        if (pass->culled) continue;

        /* NOTE: barrier / layout-transition insertion is intentionally left
           to the user execute callback (or to an RHI-specific layer above):
           the abstract RHI does not expose granular pipeline barriers
           beyond rhi_cmd_memory_barrier, which is most relevant for compute
           write-after-read scenarios. */

        if (pass->execute) {
            pass->execute(pass->ctx, pass);
        }
    }
}

/* ---------------------------------------------------------------------------
 *  Resource lookup
 * -------------------------------------------------------------------------*/

RHITexture rg_get_texture(RenderGraph *rg, RGResource handle)
{
    if (!rg_resource_index_valid(rg, handle)) return RHI_HANDLE_NULL;
    const RGResourceInfo *info = &rg->resources[handle];
    if (info->is_buffer) return RHI_HANDLE_NULL;
    return info->physical_texture;
}

RHIBuffer rg_get_buffer(RenderGraph *rg, RGResource handle)
{
    if (!rg_resource_index_valid(rg, handle)) return RHI_HANDLE_NULL;
    const RGResourceInfo *info = &rg->resources[handle];
    if (!info->is_buffer) return RHI_HANDLE_NULL;
    return info->physical_buffer;
}

/* ---------------------------------------------------------------------------
 *  Stats
 * -------------------------------------------------------------------------*/

u32 rg_pass_count(RenderGraph *rg)        { return rg ? rg->pass_count : 0; }
u32 rg_resource_count(RenderGraph *rg)    { return rg ? rg->resource_count : 0; }
u32 rg_culled_pass_count(RenderGraph *rg) { return rg ? rg->culled_count : 0; }
