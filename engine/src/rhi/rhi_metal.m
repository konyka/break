/* Native Metal RHI backend. Single Objective-C TU exporting the same rhi_*
 * symbols as rhi_vk.c / rhi_gl.c. Manual reference counting (-fno-objc-arc):
 * Obj-C handles live in C structs (backend_data / slot table), matching the
 * window_cocoa.m precedent.
 *
 * Task 3 state: device create/destroy, capabilities and device info are
 * implemented (plus the format-mapping layer in rhi/rhi_metal_format.h).
 * Task 4 state: the sticky device-lost latch is wired — every commit goes
 * through metal_commit (addCompletedHandler status check), and idle/destroy
 * drain through a bounded (20 s) MTLSharedEvent wait because
 * waitUntilCompleted has no timeout and hangs forever on a wedged GPU.
 * Task 5 state: the frame family is wired — drawable acquire with a bounded
 * nextDrawable retry, two-slot MTLSharedEvent pacing, present folded into
 * frame_end (present-before-commit is a Metal hard constraint), resize as
 * dev-dimension bookkeeping, and clear-only render passes. Teardown quiesces
 * pending completion handlers before free(mb) (Task 4 review handoff).
 * Task 7 state: the resource family is wired — buffers (shared storage for
 * UNIFORM/initial-data, private + blit staging for pure-GPU usages),
 * textures/arrays/cubemaps (private storage, staging uploads, blit readback
 * through a shared buffer with the R587-R602/R624 byte contracts), and
 * samplers. All one-shot submits wait bounded through drain_event
 * (metal_commit_wait), never a bare waitUntilCompleted.
 * Task 8 state: the pipeline/FBO family is wired — RHIPipelineDesc field
 * mapping onto MTLRenderPipelineDescriptor (vertex layout table ported from
 * rhi_vk.c vk_build_graphics_pipeline, R445 depth rule, blend/cull/
 * wireframe/point_list, color_format + MRT attachment formats), the
 * R616/R617 offscreen+MRT bind/bind_load contract via loadAction
 * Clear/Load, R618 shadow + cubemap-depth face clears, and R619
 * caller-owned FBO clear colors. Shaders ride the interim MSL-source path
 * (newLibraryWithSource:, entry convention vs_main/fs_main/cs_main) until
 * Task 10 lands the manifest loader.
 * Task 9 state: compute (MTLComputePipelineState + dispatch on a lazily
 * opened compute encoder; storage/image binds; memoryBarrierWithScope:),
 * blit-family cmd ops (fill/update/copy via a transient blit encoder),
 * rhi_screenshot (bounded drain + blit from the drawable, which is now
 * retained until present; the layer is switched to framebufferOnly=NO at
 * device create so readback is legal), indirect draws (native
 * indirectBuffer: loops; the _count variant is fail-closed — no Metal
 * equivalent), and the GPU timer (MTLCounterSampleBuffer timestamps with a
 * supportsCounterSampling: gate and a warn-once degraded mode).
 * Every other entry point logs and fails closed until its family is filled
 * in by the later plan-C tasks. */
#import <Metal/Metal.h>
#import <QuartzCore/CAMetalLayer.h>

#include <rhi/rhi.h>
#include <rhi/rhi_backend_internal.h>
#include <rhi/rhi_metal_format.h>
#include <rhi/rhi_native_vulkan.h>
#include <core/log.h>
#include <core/shader_io.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <mach/mach_time.h>   /* gpu timer tick -> ns conversion */

struct RHICmdBuffer;

typedef struct {
    id<MTLDevice> device;
    id<MTLCommandQueue> queue;
    CAMetalLayer *layer;          /* not owned; owned by the platform layer */
    id<MTLLibrary> library;       /* offline-compiled shader library (Task 10) */
    id<MTLSharedEvent> frame_event; /* frame pacing signals (frame_counter values) */
    id<MTLSharedEvent> drain_event; /* Task 4 bounded drain (drain_counter values) */
    u64 frame_counter;            /* frames presented; slot = counter % 2 */
    u64 drain_counter;            /* MTLSharedEvent values for bounded drain waits */
    id<CAMetalDrawable> drawable; /* current acquired drawable, nil between frames */
    struct RHICmdBuffer *frame_cmd; /* cached per-frame recording state */
    _Atomic u32 pending_handlers; /* commits whose completion handler has not run */
    id<MTLDepthStencilState> depth_states[5]; /* Task 8 cache: [lequal?2:0]|[write_off?1:0], [4]=Always+write off (R445) */
    id<MTLTexture> screen_depth;  /* drawable-sized D32 for the screen pass */
    u32 screen_depth_w, screen_depth_h;
    /* Task 12: device-address (gpuResourceID) -> MetalAS payload registry
     * for the TLAS instance conversion's linear lookup. */
    struct MetalAS **as_registry;
    u32 as_count;
    u32 as_cap;
    bool frame_started;           /* acquire done, submit not yet */
    bool frame_submitted;         /* submit done, present not yet */
    _Atomic bool device_lost_latch; /* sticky; mirrors rhi_vk.c device-lost semantics */
    bool suspended;               /* iOS host-driven pause: acquire returns BUSY */
    RHIFormat swapchain_format;   /* from the layer's pixelFormat */
    u32 max_push_bytes;           /* 256 staging, mirrors VK push staging */
} MetalBackend;

#define RHI_METAL_MAX_PUSH_BYTES 256u
/* spvBufferSizeConstants table cap (one uint byte size per runtime-array
 * SSBO; the widest engine shader today uses a single entry). */
#define RHI_METAL_BSC_MAX 4u

/* Pin the platform-free C11 ordinals to the real MTLPixelFormat values.
 * This TU is the only place Metal headers are visible, so a header drift or
 * an ordinal collision breaks the macOS compile here, never silently. */
static MTLPixelFormat rhi_metal_pixel_format(RHIMetalFormat f) {
    switch (f) {
        case RHI_METAL_FORMAT_RGBA8_UNORM:   return MTLPixelFormatRGBA8Unorm;
        case RHI_METAL_FORMAT_BGRA8_UNORM:   return MTLPixelFormatBGRA8Unorm;
        case RHI_METAL_FORMAT_RGBA16_FLOAT:  return MTLPixelFormatRGBA16Float;
        case RHI_METAL_FORMAT_RG16_FLOAT:    return MTLPixelFormatRG16Float;
        case RHI_METAL_FORMAT_R32_FLOAT:     return MTLPixelFormatR32Float;
        case RHI_METAL_FORMAT_DEPTH32_FLOAT: return MTLPixelFormatDepth32Float;
        default:
            LOG_ERROR("rhi_metal: unmapped RHIMetalFormat %d", (int)f);
            return MTLPixelFormatInvalid;
    }
}

/* Reverse direction for swapchain_format: window_cocoa.m sets the layer's
 * pixelFormat (BGRA8Unorm) before the RHI device exists, so create derives
 * the RHI format from the layer instead of imposing one. */
static RHIFormat rhi_metal_rhi_format_from_pixel_format(MTLPixelFormat f) {
    switch (f) {
        case MTLPixelFormatRGBA8Unorm:   return RHI_FORMAT_R8G8B8A8_UNORM;
        case MTLPixelFormatBGRA8Unorm:   return RHI_FORMAT_B8G8R8A8_UNORM;
        case MTLPixelFormatRGBA16Float:  return RHI_FORMAT_R16G16B16A16_SFLOAT;
        case MTLPixelFormatRG16Float:    return RHI_FORMAT_R16G16_SFLOAT;
        case MTLPixelFormatR32Float:     return RHI_FORMAT_R32_FLOAT;
        case MTLPixelFormatDepth32Float: return RHI_FORMAT_D32_FLOAT;
        default:                         return RHI_FORMAT_UNDEFINED;
    }
}

_Static_assert((NSUInteger)MTLPixelFormatInvalid == (NSUInteger)RHI_METAL_FORMAT_INVALID,
               "RHI_METAL_FORMAT_INVALID must equal MTLPixelFormatInvalid");
_Static_assert(MTLPixelFormatRGBA8Unorm != MTLPixelFormatBGRA8Unorm, "overlap");
_Static_assert(MTLPixelFormatRGBA8Unorm != MTLPixelFormatRGBA16Float, "overlap");
_Static_assert(MTLPixelFormatRGBA8Unorm != MTLPixelFormatRG16Float, "overlap");
_Static_assert(MTLPixelFormatRGBA8Unorm != MTLPixelFormatR32Float, "overlap");
_Static_assert(MTLPixelFormatRGBA8Unorm != MTLPixelFormatDepth32Float, "overlap");
_Static_assert(MTLPixelFormatBGRA8Unorm != MTLPixelFormatRGBA16Float, "overlap");
_Static_assert(MTLPixelFormatBGRA8Unorm != MTLPixelFormatRG16Float, "overlap");
_Static_assert(MTLPixelFormatBGRA8Unorm != MTLPixelFormatR32Float, "overlap");
_Static_assert(MTLPixelFormatBGRA8Unorm != MTLPixelFormatDepth32Float, "overlap");
_Static_assert(MTLPixelFormatRGBA16Float != MTLPixelFormatRG16Float, "overlap");
_Static_assert(MTLPixelFormatRGBA16Float != MTLPixelFormatR32Float, "overlap");
_Static_assert(MTLPixelFormatRGBA16Float != MTLPixelFormatDepth32Float, "overlap");
_Static_assert(MTLPixelFormatRG16Float != MTLPixelFormatR32Float, "overlap");
_Static_assert(MTLPixelFormatRG16Float != MTLPixelFormatDepth32Float, "overlap");
_Static_assert(MTLPixelFormatR32Float != MTLPixelFormatDepth32Float, "overlap");

/* ---- Task 4: device-lost detection ----
 * Metal has no public device-lost notification API, so loss is observed at
 * (1) every commit's addCompletedHandler status check and (2) the bounded
 * drain wait below. Once latched, all blocking waits fail fast so callers
 * wind down (VK R578 / rhi.h:854-858 parity; sticky per spec §4.2). */
#define RHI_METAL_DRAIN_TIMEOUT_MS 20000ull   /* aligns the VK 20 s rule */

static void metal_note_device_lost(RHIDevice *dev, MetalBackend *mb, const char *where) {
    /* The latch is written from completion-handler callbacks on arbitrary
     * queues and read on API threads; atomic exchange, log the first only. */
    if (!atomic_exchange_explicit(&mb->device_lost_latch, true,
                                  memory_order_acq_rel)) {
        LOG_ERROR("rhi_metal: device lost (%s) — latched; blocking waits now fail fast",
                  where);
    }
    dev->status = RHI_DEVICE_STATUS_LOST;
    rhi_device_set_lifecycle_result(dev, RHI_RESULT_DEVICE_LOST);
}

/* Latch on MTLCommandBufferStatusError. MTLCommandBufferErrorDeviceRemoved
 * only surfaces on macOS 13+ (and is macOS-only in the SDK); older releases
 * and iOS report a generic error code — both latch (fail-closed). */
static void metal_check_cmd_error(RHIDevice *dev, MetalBackend *mb,
                                  id<MTLCommandBuffer> cmd, const char *where) {
    if (cmd.status != MTLCommandBufferStatusError) return;
    NSError *err = cmd.error;
    long code = err != nil ? (long)err.code : -1L;
    (void)code;
#if TARGET_OS_OSX
    if (code == (long)MTLCommandBufferErrorDeviceRemoved) {
        LOG_ERROR("rhi_metal: command buffer at %s failed with "
                  "MTLCommandBufferErrorDeviceRemoved", where);
    } else {
        LOG_ERROR("rhi_metal: command buffer at %s failed (error code %ld)",
                  where, code);
    }
#endif
    metal_note_device_lost(dev, mb, where);
}

/* Single commit funnel: every submitted command buffer carries a
 * completedHandler so an asynchronously-reported GPU fault latches the
 * device lost. Fail-fast when already latched. The handler captures dev/mb
 * raw, so pending_handlers tracks handlers in flight and destroy quiesces
 * them before free(mb) (Task 4 review handoff: a late handler firing after
 * teardown is a UAF). */
static RHIResult metal_commit(RHIDevice *dev, id<MTLCommandBuffer> cmd) {
    MetalBackend *mb = (MetalBackend *)dev->backend_data;
    if (mb->device_lost_latch) return RHI_RESULT_DEVICE_LOST;
    atomic_fetch_add_explicit(&mb->pending_handlers, 1u, memory_order_acq_rel);
    [cmd addCompletedHandler:^(id<MTLCommandBuffer> finished) {
        @autoreleasepool {
            metal_check_cmd_error(dev, mb, finished, "completion");
        }
        atomic_fetch_sub_explicit(&mb->pending_handlers, 1u, memory_order_acq_rel);
    }];
    [cmd commit];
    return RHI_RESULT_OK;
}

/* Bounded wait until every committed buffer's completion handler has run.
 * Handlers fire only when their buffer completes, so after a successful
 * drain this only waits out handler-queue dispatch latency; on a wedged GPU
 * the buffers never complete and the handlers never fire, so a timeout here
 * cannot strand a live handler either (teardown stays bounded). */
static void metal_quiesce_handlers(MetalBackend *mb) {
    u64 waited_ms = 0u;
    while (atomic_load_explicit(&mb->pending_handlers, memory_order_acquire) != 0u) {
        if (waited_ms >= RHI_METAL_DRAIN_TIMEOUT_MS) {
            LOG_ERROR("rhi_metal: %u completion handlers still pending at teardown",
                      (unsigned)atomic_load_explicit(&mb->pending_handlers,
                                                     memory_order_acquire));
            return;
        }
        /* 1ms backoff: nanosleep stays C11-friendly in this Obj-C TU. */
        { struct timespec ts = { 0, 1000000L }; nanosleep(&ts, NULL); }
        waited_ms += 1u;
    }
}

/* Bounded queue drain. waitUntilCompleted has no timeout and hangs forever
 * on a wedged GPU (Task 3 review handoff), so the wait goes through a
 * MTLSharedEvent with a 20 s bound — the VK fence-unsignaled rule
 * (rhi.h:854-858), matching rhi_d3d12_drain_gpu's 20 s fence timeout. On
 * timeout the device is latched lost and the first report is SYNC_FAILED;
 * the wrapper upgrades to DEVICE_LOST on subsequent calls via the latch.
 * The drain signals drain_event with drain_counter values, deliberately
 * separate from frame_event/frame_counter (Task 5 pacing): one event's
 * signaledValue is monotonic, so sharing it would let drain signals satisfy
 * frame waits early. */
static RHIResult metal_drain(RHIDevice *dev, MetalBackend *mb) {
    if (mb->device_lost_latch) return RHI_RESULT_DEVICE_LOST;
    if (mb->queue == nil) return RHI_RESULT_OK;
    if (mb->drain_event == nil) {
        mb->drain_event = [mb->device newSharedEvent];
        if (mb->drain_event == nil) {
            LOG_ERROR("rhi_metal: newSharedEvent failed");
            return RHI_RESULT_SYNC_FAILED;
        }
    }
    id<MTLCommandBuffer> drain = [mb->queue commandBuffer];
    if (drain == nil) {
        LOG_ERROR("rhi_metal: drain command buffer allocation failed");
        return RHI_RESULT_SYNC_FAILED;
    }
    u64 value = ++mb->drain_counter;
    [drain encodeSignalEvent:mb->drain_event value:value];
    RHIResult commit_result = metal_commit(dev, drain);
    if (commit_result != RHI_RESULT_OK) return commit_result;
    if (![mb->drain_event waitUntilSignaledValue:value
                                     timeoutMS:RHI_METAL_DRAIN_TIMEOUT_MS]) {
        LOG_ERROR("rhi_metal: shared event unsignaled after %llu ms — "
                  "treating device as lost",
                  (unsigned long long)RHI_METAL_DRAIN_TIMEOUT_MS);
        metal_note_device_lost(dev, mb, "shared-event timeout");
        return RHI_RESULT_SYNC_FAILED;
    }
    metal_check_cmd_error(dev, mb, drain, "drain");
    if (mb->device_lost_latch) return RHI_RESULT_DEVICE_LOST;
    /* The buffer already completed (event signaled), so this returns at
     * once; it also quiesces the completion handler before teardown can
     * free the backend the handler captures. */
    [drain waitUntilCompleted];
    return RHI_RESULT_OK;
}

/* Current render-pass target (review fix C1): rhi_cmd_clear_color inside a
 * pass reopens a Clear pass on the SAME target (VK vkCmdClearAttachments
 * in-place parity) instead of hijacking to the screen pass. */
/* frame_begin auto-opens the screen pass (Task 13, VK parity); the helper
 * lives with the pass family below. */
static void metal_open_screen_pass(RHICmdBuffer *cmd, u32 w, u32 h,
                                   bool depth_load);
/* VK suspend/resume parity (Task 13 review round): resumes a pass
 * suspended by a compute/blit interlude with loadAction=Load. */
static void metal_resume_render_pass_if_needed(RHICmdBuffer *cmd);
struct MetalPipeline;
static void metal_apply_render_pipeline(RHICmdBuffer *cmd,
                                        struct MetalPipeline *pp,
                                        RHIPipeline pipe);

#define METAL_REPLAY_SLOTS 32u

enum {
    METAL_PASS_NONE = 0,
    METAL_PASS_SCREEN,
    METAL_PASS_OFFSCREEN,
    METAL_PASS_MRT,
    METAL_PASS_SHADOW,
    METAL_PASS_CUBE_DEPTH,
};

struct RHICmdBuffer {
    MetalBackend *backend;
    id<MTLCommandBuffer> cmd;
    id<MTLRenderCommandEncoder> render_encoder;
    id<MTLComputeCommandEncoder> compute_encoder;
    id<MTLBlitCommandEncoder> blit_encoder;
    u8 push_staging[RHI_METAL_MAX_PUSH_BYTES];
    RHIPipeline bound_pipeline;
    f32 clear_color[4];           /* pending/next clear color (MTLClearColor) */
    bool clear_pending;           /* next render pass opens with LoadActionClear */
    bool render_pass_open;
    bool push_dirty;              /* staging holds bytes not yet flushed */
    bool push_staged;             /* staging written at least once this frame */
    RHIBuffer bound_ubo;          /* deferred UBO bind (VK bound_ubo parity) */
    u32 bound_ubo_binding;
    /* Recorded compute storage-buffer binds (handles, generation-checked at
     * replay). Encoder state does not survive pass switches (I2 rule), so
     * dispatch replays these. */
    RHIBuffer bound_storage[25];
    u32 bound_storage_mask;
    /* Graphics-bind-point storage records, kept apart from the compute ones
     * above (VK keeps separate COMPUTE/GRAPHICS descriptor bind points). A
     * shared table replayed compute binds 0/1 (cluster cull light buffers)
     * into vertex buffer(0) of the next storage-using draw, clobbering the
     * mesh VBO. */
    RHIBuffer bound_gfx_storage[25];
    u32 bound_gfx_storage_mask;
    /* Recorded texel-buffer binds (textures 16/17). Same I2 rule: a blit
     * interlude (rhi_cmd_update_buffer between instanced draws) drops them,
     * while VK descriptor sets survive — replayed at every draw. */
    RHIBuffer bound_texel[2];
    /* Suspended render pass (VK suspend/resume parity): a compute or blit
     * interlude records the open target here; the next graphics call
     * resumes it with loadAction=Load (metal_resume_render_pass_if_needed). */
    u8 suspended_kind;            /* METAL_PASS_* or METAL_PASS_NONE */
    RHIHandle suspended_target;
    u32 suspended_w, suspended_h, suspended_face;
    /* Graphics pipeline bound when the pass was suspended. VK pipeline binds
     * are command-buffer state and survive a compute/blit interlude
     * (deferred G-Buffer: per-material factor update_buffer between draws
     * with no rebind), so the resume re-applies it. */
    RHIPipeline suspended_pipeline;
    /* Encoder-bound resources recorded as they are bound (retained). Metal
     * drops fragment textures/samplers and the vertex buffer with the
     * encoder, while VK keeps them as command-buffer state across the
     * compute/blit interlude (deferred G-Buffer: the per-material factor
     * update_buffer sits between bind_material and the vertex bind), so the
     * resume replays them. Cleared whenever a fresh pass opens. */
    id<MTLTexture> frag_tex[METAL_REPLAY_SLOTS];
    id<MTLSamplerState> frag_smp[METAL_REPLAY_SLOTS];
    id<MTLBuffer> vtx_buf;
    NSUInteger vtx_off;
    bool resuming;
    u8 pass_kind;                 /* METAL_PASS_* while render_pass_open */
    RHIHandle pass_target;        /* fb handle of the bound target */
    MTLPixelFormat pass_color_format; /* color0 of the open pass (Invalid if none) */
    u32 pass_w, pass_h;
    u32 pass_face;                /* cubemap depth face */
    RHIBuffer index_buffer;       /* recorded; applied at (indexed) draw time */
    usize index_offset;
    bool index_u32;
    /* Task 9 gpu timer: stage-boundary counter sampling is render-encoder-
     * only on Apple GPUs, so begin/end called between passes pend here and
     * land on the next pass open in the same frame. */
    RHIGPUTimer *pending_timers[8];
    u32 pending_indices[8];
    u32 pending_count;
};

/* Encoder lifecycle rule (docs/rhi_metal_notes.md): at most one encoder is
 * open per command buffer at a time; switching target or encoder type ends
 * the current one first. The recorded work stays in the command buffer.
 * Closing a pass drops ALL encoder state (render pipeline, depth state,
 * viewport), so the bound-pipeline bookkeeping is invalidated here —
 * callers must re-bind after any pass switch (VK unbind_shadow_map's
 * current_pipeline = NULL parity; review fix I1: a stale handle replayed
 * into a fresh encoder draws without a render pipeline state and trips
 * Metal validation). */
static void metal_replay_clear(RHICmdBuffer *cmd) {
    u32 i;
    for (i = 0u; i < METAL_REPLAY_SLOTS; ++i) {
        [cmd->frag_tex[i] release];
        cmd->frag_tex[i] = nil;
        [cmd->frag_smp[i] release];
        cmd->frag_smp[i] = nil;
    }
    [cmd->vtx_buf release];
    cmd->vtx_buf = nil;
    cmd->vtx_off = 0u;
}

static void metal_set_frag_texture(RHICmdBuffer *cmd, id<MTLTexture> tex,
                                   NSUInteger index) {
    [cmd->render_encoder setFragmentTexture:tex atIndex:index];
    if (index < METAL_REPLAY_SLOTS) {
        [tex retain];
        [cmd->frag_tex[index] release];
        cmd->frag_tex[index] = tex;
    }
}

static void metal_set_frag_sampler(RHICmdBuffer *cmd, id<MTLSamplerState> smp,
                                   NSUInteger index) {
    [cmd->render_encoder setFragmentSamplerState:smp atIndex:index];
    if (index < METAL_REPLAY_SLOTS) {
        [smp retain];
        [cmd->frag_smp[index] release];
        cmd->frag_smp[index] = smp;
    }
}

static void metal_replay_encoder_state(RHICmdBuffer *cmd) {
    u32 i;
    for (i = 0u; i < METAL_REPLAY_SLOTS; ++i) {
        if (cmd->frag_tex[i] != nil)
            [cmd->render_encoder setFragmentTexture:cmd->frag_tex[i]
                                            atIndex:(NSUInteger)i];
        if (cmd->frag_smp[i] != nil)
            [cmd->render_encoder setFragmentSamplerState:cmd->frag_smp[i]
                                                 atIndex:(NSUInteger)i];
    }
    if (cmd->vtx_buf != nil)
        [cmd->render_encoder setVertexBuffer:cmd->vtx_buf
                                      offset:cmd->vtx_off
                                     atIndex:0u];
}

static void metal_end_render_encoder(RHICmdBuffer *cmd) {
    if (cmd->render_encoder != nil) {
        [cmd->render_encoder endEncoding];
        [cmd->render_encoder release];
        cmd->render_encoder = nil;
    }
    cmd->render_pass_open = false;
    cmd->pass_kind = METAL_PASS_NONE;
    cmd->pass_target = RHI_HANDLE_NULL;
    cmd->bound_pipeline = RHI_HANDLE_NULL;
    /* setBytes/setBuffer are ENCODER state (unlike VK's command-buffer
     * state): closing the encoder drops them, so anything staged/bound this
     * frame must be replayed at the next draw (review fixes I1/I2). The
     * staging bytes live on the cmd — replay is a zero-copy setBytes. The
     * recorded UBO/storage binds are replayed unconditionally at flush. */
    if (cmd->push_staged) cmd->push_dirty = true;
}

/* Task 9: the compute encoder obeys the same one-encoder rule. */
static void metal_end_compute_encoder(RHICmdBuffer *cmd) {
    if (cmd->compute_encoder != nil) {
        [cmd->compute_encoder endEncoding];
        [cmd->compute_encoder release];
        cmd->compute_encoder = nil;
    }
    cmd->bound_pipeline = RHI_HANDLE_NULL;
    if (cmd->push_staged) cmd->push_dirty = true;
}

static void metal_end_encoders(RHICmdBuffer *cmd) {
    metal_end_render_encoder(cmd);
    metal_end_compute_encoder(cmd);
}

RHIDevice *rhi_device_create(RHIBackend backend, void *window_native,
                              void *display_native, u32 w, u32 h);

RHIDevice *rhi_device_create_compiled(void *window_native,
                                      void *surface_native,
                                      void *display_native, u32 w, u32 h) {
    /* Cocoa exposes the CAMetalLayer through both native handles.  Keep the
     * compiled-backend entry point aligned with the explicit Metal selector
     * so consumers cannot accidentally fall through to the MoltenVK path. */
    (void)surface_native;
    return rhi_device_create(RHI_BACKEND_METAL, window_native,
                              display_native, w, h);
}

RHIDevice *rhi_device_create(RHIBackend backend, void *window_native, void *display_native, u32 w, u32 h) {
    (void)display_native;
    if (backend != RHI_BACKEND_METAL || window_native == NULL ||
        !rhi_drawable_dimensions_valid(w, h)) {
        rhi_backend_note_create_result(RHI_RESULT_INVALID_ARGUMENT);
        return NULL;
    }
    CAMetalLayer *layer = (CAMetalLayer *)window_native;
    id<MTLDevice> device = MTLCreateSystemDefaultDevice();
    if (device == nil) {
        /* Runtime fallback: the selector already fails closed on non-Metal
         * platforms, so nil here means a genuine init failure -> ERROR via
         * the wrapper's pre-seeded g_backend_create_result. Never fabricate
         * a device. */
        LOG_ERROR("rhi_metal: MTLCreateSystemDefaultDevice returned nil");
        return NULL;
    }
    id<MTLCommandQueue> queue = [device newCommandQueue];
    if (queue == nil) {
        LOG_ERROR("rhi_metal: newCommandQueue failed");
        [device release];
        return NULL;
    }
    RHIFormat swapchain_format = rhi_metal_rhi_format_from_pixel_format(layer.pixelFormat);
    if (swapchain_format == RHI_FORMAT_UNDEFINED ||
        rhi_metal_pixel_format(rhi_metal_format_from_rhi(swapchain_format)) !=
            layer.pixelFormat) {
        /* The layer's pixel format is outside the RHI format set (or the
         * mapping layer disagrees with itself) — fail closed. */
        LOG_ERROR("rhi_metal: unsupported swapchain pixel format %lu",
                  (unsigned long)layer.pixelFormat);
        [queue release];
        [device release];
        return NULL;
    }
    u32 color_counts = 0u, depth_counts = 0u;
    {
        static const NSUInteger sample_probes[4] = { 1u, 2u, 4u, 8u };
        for (u32 i = 0u; i < 4u; ++i) {
            if ([device supportsTextureSampleCount:sample_probes[i]]) {
                color_counts |= rhi_sample_count_bit((u32)sample_probes[i]);
                depth_counts |= rhi_sample_count_bit((u32)sample_probes[i]);
            }
        }
    }
    if ((color_counts & rhi_sample_count_bit(1u)) == 0u ||
        (depth_counts & rhi_sample_count_bit(1u)) == 0u) {
        /* Metal guarantees 1x everywhere; a device reporting otherwise is
         * broken — fail closed instead of fabricating capability bits. */
        LOG_ERROR("rhi_metal: device does not support 1x sampling");
        [queue release];
        [device release];
        return NULL;
    }
    MetalBackend *mb = (MetalBackend *)calloc(1u, sizeof(*mb));
    RHIDevice *dev = (RHIDevice *)calloc(1u, sizeof(*dev));
    if (mb == NULL || dev == NULL) {
        free(mb);
        free(dev);
        [queue release];
        [device release];
        return NULL;
    }
    layer.device = device;
    /* framebufferOnly=YES (the default) forbids blit readback of drawable
     * textures, which rhi_screenshot (rhi.h:815-826) requires between
     * acquire and present. VK/D3D12 swapchains carry TRANSFER_SRC/COPY_SRC
     * by contract; Metal must opt out here. */
    layer.framebufferOnly = NO;
    mb->device = device;
    mb->queue = queue;
    mb->layer = layer;               /* not owned */
    /* Task 10: the offline-compiled shader library lives beside the
     * executable (engine_link_rhi_backend copies it per consumer). A missing
     * metallib degrades to per-shader embedded-MSL compilation at shader
     * create (LOG_WARN path), never to silence. */
    @autoreleasepool {
        NSString *exe = [[NSBundle mainBundle] executablePath];
        NSString *dir = [exe stringByDeletingLastPathComponent];
        NSString *lib_path =
            [dir stringByAppendingPathComponent:@"engine.metallib"];
        NSError *err = nil;
        /* newLibraryWithFile: returns +1 (new* rule); deprecated since
         * macOS 13 in favor of the URL form. */
        mb->library = [device
            newLibraryWithURL:[NSURL fileURLWithPath:lib_path]
                        error:&err];
        if (mb->library == nil) {
            LOG_WARN("rhi_metal: engine.metallib unavailable (%s) — embedded "
                     "MSL fallback active",
                     err != nil ? [[err localizedDescription] UTF8String]
                                : "not beside the executable");
        }
    }
    mb->swapchain_format = swapchain_format;
    mb->max_push_bytes = RHI_METAL_MAX_PUSH_BYTES;
    rhi_init_freelist(dev);
    dev->backend_data = mb;
    dev->width = w;
    dev->height = h;
    dev->capabilities.backend = RHI_BACKEND_METAL;
    /* Metal consumes the Vulkan-layout GLSL corpus after the offline
     * SPIR-V/MSL conversion.  Keep renderer source selection in sync with
     * the manifest hashes generated at build time. */
    dev->capabilities.shader_variant = (u32)RHI_SHADER_VARIANT_GLSL_VK;
    /* R606: Metal has no sidecars either — rhi_shader_create_path returns the
     * GLSL file. blinn_phong_vk.vert declares ForwardTemporal at binding 0. */
    dev->capabilities.shader_sidecar_paths = false;
    dev->capabilities.temporal_ubo_binding = 0u;
    dev->capabilities.color_sample_counts = color_counts;
    dev->capabilities.depth_sample_counts = depth_counts;
    /* CAMetalLayer drawables cannot be multisampled; MSAA is only possible
     * via an offscreen resolve (storeActionMultisampleResolve), so the
     * surface itself reports 1x. */
    dev->capabilities.surface_sample_count = 1u;
    dev->capabilities.color_resolve_supported = true;
    /* fail-closed: custom depth resolve is out of scope for this plan. */
    dev->capabilities.depth_resolve_supported = false;
    dev->capabilities.scissor_supported = true;      /* setScissorRect: */
    /* drawable contents are not preserved and CAMetalLayer has no damage or
     * buffer-age mechanism. */
    dev->capabilities.present_target_preserved = false;
    dev->capabilities.present_damage_supported = false;
    dev->capabilities.present_buffer_age_supported = false;
    if ([device respondsToSelector:@selector(supportsRaytracing)] &&
        device.supportsRaytracing) {
        dev->capabilities.feature_bits =
            RHI_FEATURE_ACCELERATION_STRUCTURE | RHI_FEATURE_RAY_QUERY;
    }
    /* RHI_FEATURE_RAY_TRACING_PIPELINE is never set: Metal's
     * intersection-function model has no raygen-pipeline equivalent
     * (fail-closed). */
    dev->status = RHI_DEVICE_STATUS_READY;
    g_current_device = dev;
    return dev;
}

void rhi_device_destroy(RHIDevice *dev) {
    if (dev == NULL) return;
    MetalBackend *mb = (MetalBackend *)dev->backend_data;
    if (mb != NULL) {
        /* §4.3: destroy drains first — via the implementation-internal idle
         * (bounded frame-signal wait + Task 4 bounded queue drain). A wedged
         * GPU must not hang teardown: on timeout the device is latched lost
         * and teardown proceeds. */
        (void)rhi_device_idle(dev);
        /* Task 4 review handoff: frame commits reuse metal_commit, whose
         * completion handlers capture dev/mb raw; free(mb) while a handler
         * is pending is a UAF. Quiesce them (bounded) before releasing. */
        metal_quiesce_handlers(mb);
        @autoreleasepool {
            if (mb->drawable != nil) {   /* nil between frames; retained at acquire */
                [mb->drawable release];
                mb->drawable = nil;
            }
            if (mb->frame_cmd != NULL) {
                metal_end_encoders(mb->frame_cmd);
                [mb->frame_cmd->cmd release];   /* nil between frames; no-op then */
                metal_replay_clear(mb->frame_cmd);
                free(mb->frame_cmd);
                mb->frame_cmd = NULL;
            }
            [mb->library release];       /* nil when the metallib is missing (embedded fallback) */
            [mb->frame_event release];   /* created lazily by rhi_frame_begin */
            [mb->drain_event release];   /* created lazily by metal_drain */
            for (u32 i = 0u; i < 5u; ++i) [mb->depth_states[i] release];
            [mb->screen_depth release];
            free(mb->as_registry);
            [mb->queue release];
            [mb->device release];
        }
        free(mb);
        dev->backend_data = NULL;
    }
    if (g_current_device == dev) g_current_device = NULL;
    free(dev);
}

void rhi_device_resize(RHIDevice *dev, u32 w, u32 h) {
    MetalBackend *mb = dev != NULL ? (MetalBackend *)dev->backend_data : NULL;
    if (mb == NULL) {
        if (dev != NULL) rhi_device_set_lifecycle_result(dev, RHI_RESULT_UNAVAILABLE);
        return;
    }
    /* Only the RHI-side dimensions are updated; layer.drawableSize is owned
     * by the window layer (window_cocoa.m cocoa_update_drawable_size). The
     * next acquire adopts the layer's actual size — the "swapchain auto
     * rebuild" semantic needs no explicit teardown here. */
    dev->width = w;
    dev->height = h;
}

/* nextDrawable with a bounded retry: a nil drawable means the layer's
 * drawable pool is exhausted (all in flight), so back off 1 ms and retry up
 * to a 1 s deadline. nil past the deadline maps to OUT_OF_DATE (fail-fast);
 * a latched device maps to DEVICE_LOST. Returns a retained drawable. */
static id<CAMetalDrawable> metal_acquire_drawable(MetalBackend *mtl, RHIDevice *dev) {
    const u64 deadline_ms = 1000u;
    u64 waited_ms = 0u;
    for (;;) {
        @autoreleasepool {
            id<CAMetalDrawable> d = [mtl->layer nextDrawable];
            if (d != nil) return [d retain];
        }
        if (mtl->device_lost_latch) {
            rhi_device_set_lifecycle_result(dev, RHI_RESULT_DEVICE_LOST);
            return nil;
        }
        if (waited_ms >= deadline_ms) {
            rhi_device_set_lifecycle_result(dev, RHI_RESULT_OUT_OF_DATE);
            return nil;
        }
        /* 1ms backoff: usleep via nanosleep to stay C11-friendly in Obj-C TU. */
        struct timespec ts = { 0, 1000000L };
        nanosleep(&ts, NULL);
        waited_ms += 1u;
    }
}

static bool metal_ensure_frame_event(RHIDevice *dev, MetalBackend *mb) {
    if (mb->frame_event != nil) return true;
    mb->frame_event = [mb->device newSharedEvent];
    if (mb->frame_event == nil) {
        LOG_ERROR("rhi_metal: newSharedEvent failed");
        rhi_device_set_lifecycle_result(dev, RHI_RESULT_SYNC_FAILED);
        return false;
    }
    return true;
}

RHICmdBuffer *rhi_frame_begin(RHIDevice *dev) {
    if (dev == NULL) return NULL;
    MetalBackend *mb = (MetalBackend *)dev->backend_data;
    if (mb == NULL) {
        rhi_device_set_lifecycle_result(dev, RHI_RESULT_UNAVAILABLE);
        return NULL;
    }
    /* spec §4.3: one in-flight acquire->submit pair max. */
    if (mb->frame_started || !rhi_frame_owner_begin_backend(dev)) {
        rhi_device_set_lifecycle_result(dev, RHI_RESULT_BUSY);
        return NULL;
    }
    g_current_device = dev;
    dev->frame_partial_active = false;
    if (mb->device_lost_latch) { /* sticky latch: quiet fail-fast, no spam */
        rhi_device_set_lifecycle_result(dev, RHI_RESULT_DEVICE_LOST);
        rhi_frame_owner_release(dev);
        return NULL;
    }
    if (mb->suspended) {   /* iOS host-driven pause; known boundary: no production setter exists — hosts self-discipline (no frame API calls while backgrounded), only the ENGINE_RHI_TEST hook rhi_test_metal_set_suspended arms this */
        rhi_device_set_lifecycle_result(dev, RHI_RESULT_BUSY);
        rhi_frame_owner_release(dev);
        return NULL;
    }
    if (mb->layer == nil) {
        rhi_device_set_lifecycle_result(dev, RHI_RESULT_SURFACE_LOST);
        rhi_frame_owner_release(dev);
        return NULL;
    }
    /* commandBuffer and friends are autoreleased; the C caller may have no
     * pool in place (rhi_frame_begin is a plain C entry point), so scope one
     * here. The drawable and cmd buffer are retained and survive the drain. */
    @autoreleasepool {
    if (!metal_ensure_frame_event(dev, mb)) {
        rhi_frame_owner_release(dev);
        return NULL;
    }
    /* Two-slot pacing: the slot being acquired was last used by frame
     * frame_counter-2; wait for its completion signal (bounded, 20 s —
     * same VK fence rule as metal_drain). wait_value 0 is trivially
     * satisfied (initial signaledValue is 0), so the first reuse after
     * frame 0 does not block; CAMetalLayer's own drawable backpressure
     * covers that window (pinned by test_rhi_metal_format_mapping). */
    if (mb->frame_counter >= 2u &&
        ![mb->frame_event waitUntilSignaledValue:
              rhi_metal_slot_wait_value(mb->frame_counter)
                                       timeoutMS:RHI_METAL_DRAIN_TIMEOUT_MS]) {
        LOG_ERROR("rhi_metal: frame pacing event unsignaled after %llu ms",
                  (unsigned long long)RHI_METAL_DRAIN_TIMEOUT_MS);
        metal_note_device_lost(dev, mb, "frame pacing timeout");
        /* First report is SYNC_FAILED; the latch upgrades later calls. */
        rhi_device_set_lifecycle_result(dev, RHI_RESULT_SYNC_FAILED);
        rhi_frame_owner_release(dev);
        return NULL;
    }
    mb->drawable = metal_acquire_drawable(mb, dev);   /* sets lifecycle on failure */
    if (mb->drawable == nil) {
        rhi_frame_owner_release(dev);
        return NULL;
    }
    if (mb->drawable.texture == nil) {
        [mb->drawable release];
        mb->drawable = nil;
        rhi_device_set_lifecycle_result(dev, RHI_RESULT_SURFACE_LOST);
        rhi_frame_owner_release(dev);
        return NULL;
    }
    /* Drawable-size adoption: the window layer owns drawableSize
     * (windowDidResize -> cocoa_update_drawable_size), so a stale dev
     * dimension picks up the layer's actual size here instead of any
     * explicit swapchain rebuild. An invalid (e.g. minimized 0x0) layer
     * size is not adopted; the acquire retry above already bounded it. */
    {
        CGSize layer_size = mb->layer.drawableSize;
        u32 lw = (u32)(layer_size.width + 0.5);
        u32 lh = (u32)(layer_size.height + 0.5);
        if (rhi_drawable_dimensions_valid(lw, lh) &&
            (lw != dev->width || lh != dev->height)) {
            dev->width = lw;
            dev->height = lh;
        }
    }
    id<MTLCommandBuffer> mtl_cmd = [mb->queue commandBuffer];
    if (mtl_cmd == nil) {
        LOG_ERROR("rhi_metal: command buffer allocation failed");
        [mb->drawable release];
        mb->drawable = nil;
        rhi_device_set_lifecycle_result(dev, RHI_RESULT_ERROR);
        rhi_frame_owner_release(dev);
        return NULL;
    }
    if (mb->frame_cmd == NULL) {
        mb->frame_cmd = (RHICmdBuffer *)calloc(1u, sizeof(*mb->frame_cmd));
        if (mb->frame_cmd == NULL) {
            [mb->drawable release];
            mb->drawable = nil;
            rhi_device_set_lifecycle_result(dev, RHI_RESULT_ERROR);
            rhi_frame_owner_release(dev);
            return NULL;
        }
        mb->frame_cmd->backend = mb;
    }
    RHICmdBuffer *cmd = mb->frame_cmd;
    /* An abandoned in-flight encoder (an init path that opened compute/blit
     * work without a frame_end) must be ENDED, not just dropped — nil-ing a
     * live encoder leaves Metal reporting "already encoding" on the next
     * encoder creation on the reused frame cmd (found in Task 13 IBL rebake). */
    metal_end_encoders(cmd);
    cmd->cmd = [mtl_cmd retain];   /* autoreleased by the queue; we hold it to frame_end */
    cmd->render_encoder = nil;
    cmd->compute_encoder = nil;
    cmd->render_pass_open = false;
    cmd->pass_kind = METAL_PASS_NONE;
    cmd->pass_target = RHI_HANDLE_NULL;
    cmd->bound_pipeline = RHI_HANDLE_NULL;
    cmd->index_buffer = RHI_HANDLE_NULL;
    cmd->pending_count = 0;   /* gpu timer samples never cross frames */
    cmd->push_dirty = false;
    cmd->push_staged = false;
    cmd->bound_ubo = RHI_HANDLE_NULL;
    cmd->bound_ubo_binding = 0u;
    cmd->bound_storage_mask = 0u;
    cmd->bound_gfx_storage_mask = 0u;
    cmd->bound_texel[0] = RHI_HANDLE_NULL;
    cmd->bound_texel[1] = RHI_HANDLE_NULL;
    cmd->suspended_kind = METAL_PASS_NONE;
    cmd->suspended_target = RHI_HANDLE_NULL;
    cmd->suspended_w = cmd->suspended_h = cmd->suspended_face = 0u;
    cmd->suspended_pipeline = RHI_HANDLE_NULL;
    cmd->resuming = false;
    metal_replay_clear(cmd);
    /* A fresh drawable's contents are undefined, so the first pass of every
     * frame clears (default opaque black; rhi_cmd_clear_color overrides). */
    cmd->clear_color[0] = 0.0f;
    cmd->clear_color[1] = 0.0f;
    cmd->clear_color[2] = 0.0f;
    cmd->clear_color[3] = 1.0f;
    cmd->clear_pending = true;
    mb->frame_started = true;
    mb->frame_submitted = false;
    /* VK parity (rhi_vk.c frame_begin opens the swapchain pass inline):
     * the engine never calls begin_render_pass explicitly — main.c and myui
     * draw to the screen straight after acquire, so the screen pass must be
     * open here (clear with cmd->clear_color; C1 same-target reopen covers
     * a later rhi_cmd_clear_color). */
    metal_open_screen_pass(cmd, dev->width, dev->height, false);
    rhi_device_set_lifecycle_result(dev, RHI_RESULT_OK);
    return cmd;
    }   /* @autoreleasepool */
}

void rhi_frame_end(RHIDevice *dev) {
    if (dev == NULL) return;
    if (!rhi_frame_owner_is_current(dev) || g_current_device != dev) return;
    @autoreleasepool {
    MetalBackend *mb = (MetalBackend *)dev->backend_data;
    if (mb == NULL || !mb->frame_started) {
        rhi_device_set_lifecycle_result(dev, RHI_RESULT_UNAVAILABLE);
        return;
    }
    RHICmdBuffer *cmd = mb->frame_cmd;
    if (cmd != NULL) metal_end_encoders(cmd);
    id<MTLCommandBuffer> mtl_cmd = cmd != NULL ? cmd->cmd : nil;
    RHIResult result = RHI_RESULT_OK;
    if (mtl_cmd == nil || mb->drawable == nil || mb->frame_event == nil) {
        /* Unreachable on the healthy path (frame_started implies all three);
         * fail closed instead of committing a present-less buffer. */
        LOG_ERROR("rhi_metal: frame_end without a live command buffer/drawable");
        result = RHI_RESULT_ERROR;
    } else {
        /* presentDrawable must be attached before commit (Metal hard
         * constraint), so the Metal backend folds present semantics into
         * frame_end; rhi_present is bookkeeping only. */
        [mtl_cmd presentDrawable:mb->drawable];
        [mtl_cmd encodeSignalEvent:mb->frame_event value:mb->frame_counter];
        result = metal_commit(dev, mtl_cmd);
    }
    /* The drawable stays retained until rhi_present: rhi_screenshot between
     * frame_end and present reads it (rhi.h:815-826 / R577), and Metal keeps
     * it alive for the scheduled present regardless. */
    if (cmd != NULL) {
        [cmd->cmd release];       /* our retain; the queue keeps it alive */
        cmd->cmd = nil;
    }
    mb->frame_started = false;
    mb->frame_submitted = (result == RHI_RESULT_OK);
    rhi_device_set_lifecycle_result(dev, result);
    /* The frame owner stays held until rhi_present (D3D12 parity). */
    }   /* @autoreleasepool */
}

void rhi_present(RHIDevice *dev) {
    if (dev == NULL) return;
    if (!rhi_frame_owner_is_current(dev) || g_current_device != dev) return;
    MetalBackend *mb = (MetalBackend *)dev->backend_data;
    if (mb == NULL) {
        rhi_device_set_lifecycle_result(dev, RHI_RESULT_UNAVAILABLE);
        return;
    }
    if (mb->device_lost_latch) {
        rhi_device_set_lifecycle_result(dev, RHI_RESULT_DEVICE_LOST);
        goto out_release;
    }
    if (!mb->frame_submitted) {
        /* spec §4.3: present only after a successful submit. */
        rhi_device_set_lifecycle_result(dev, RHI_RESULT_ERROR);
        goto out_release;
    }
    /* presentDrawable was attached pre-commit in rhi_frame_end (Metal hard
     * constraint); present is bookkeeping only — advance the pacing counter
     * and clear the damage state. */
    mb->frame_counter++;
    mb->frame_submitted = false;
    rhi_device_set_lifecycle_result(dev, RHI_RESULT_OK);
out_release:
    /* The frame's drawable is released at present (retained since acquire so
     * a pre-present rhi_screenshot can read it). Runs on every path —
     * present is mandatory after frame_end (the owner stays held). */
    if (mb->drawable != nil) {
        [mb->drawable release];
        mb->drawable = nil;
    }
    dev->frame_damage_requested = false;
    dev->frame_damage_count = 0u;
    dev->frame_current_damage_count = 0u;
    dev->frame_partial_active = false;
    rhi_frame_owner_release(dev);
}

void rhi_set_vsync(RHIDevice *dev, bool enabled) {
    MetalBackend *mb = dev != NULL ? (MetalBackend *)dev->backend_data : NULL;
    if (mb == NULL || mb->layer == nil) return;
#if TARGET_OS_OSX
    /* displaySyncEnabled is macOS 10.13+; guard for older SDKs/hosts. */
    if ([mb->layer respondsToSelector:@selector(setDisplaySyncEnabled:)])
        mb->layer.displaySyncEnabled = enabled ? YES : NO;
#else
    /* iOS has no displaySyncEnabled; present is always display-synced. */
    (void)enabled;
#endif
}

u32 rhi_frame_index(RHIDevice *dev) {
    MetalBackend *mb = dev != NULL ? (MetalBackend *)dev->backend_data : NULL;
    return mb != NULL ? rhi_metal_frame_slot(mb->frame_counter) : 0u;
}

bool rhi_device_idle(RHIDevice *dev) {
    MetalBackend *mb = dev != NULL ? (MetalBackend *)dev->backend_data : NULL;
    if (mb == NULL) return false;
    /* Latched loss (or an injected LOST status): fail fast instead of
     * blocking on a dead device; the wrapper maps this to DEVICE_LOST. */
    if (mb->device_lost_latch || dev->status == RHI_DEVICE_STATUS_LOST)
        return false;
    /* §4.3 drain row: wait for the last submitted frame's signal
     * (0 frames -> immediate success). Bounded 20 s; a timeout latches the
     * device lost and the wrapper reports SYNC_FAILED first. */
    if (mb->frame_counter >= 1u && mb->frame_event != nil &&
        ![mb->frame_event waitUntilSignaledValue:mb->frame_counter - 1u
                                      timeoutMS:RHI_METAL_DRAIN_TIMEOUT_MS]) {
        LOG_ERROR("rhi_metal: last frame unsignaled after %llu ms",
                  (unsigned long long)RHI_METAL_DRAIN_TIMEOUT_MS);
        metal_note_device_lost(dev, mb, "frame drain timeout");
        return false;
    }
    /* Diagnostic probe parity with VK (rhi_vk.c rhi_device_idle): the
     * Task 4 queue-wide bounded drain stays — it covers non-frame commits
     * and the degenerate frame-0 signal (value 0 == initial signaledValue),
     * and makes an asynchronously-reported loss observable at the probe
     * site. Bounded — never hangs on a wedged GPU. */
    bool idle_ok;
    @autoreleasepool {
        idle_ok = metal_drain(dev, mb) == RHI_RESULT_OK;
    }
    return idle_ok;
}

bool rhi_device_lost(RHIDevice *dev) {
    if (dev == NULL) return false;
    MetalBackend *mb = (MetalBackend *)dev->backend_data;
    /* dev->status covers the ENGINE_RHI_TEST injection path; the latch
     * covers Metal-observed loss. Either is sticky (spec §4.2). */
    if (dev->status == RHI_DEVICE_STATUS_LOST) return true;
    if (mb != NULL && mb->device_lost_latch) {
        /* Sync the wrapper-visible status so the _ex wrappers fail fast
         * (rhi_d3d12.c rhi_device_lost parity). */
        dev->status = RHI_DEVICE_STATUS_LOST;
        return true;
    }
    return false;
}

bool rhi_backend_get_native_device(const RHIDevice *dev, RHINativeDevice *out) {
    LOG_ERROR("rhi_metal: rhi_backend_get_native_device not implemented");
    (void)dev;
    (void)out;
    return false;
}

bool rhi_backend_get_device_info(const RHIDevice *dev, RHIDeviceInfo *out) {
    if (dev == NULL || out == NULL) return false;
    MetalBackend *mb = (MetalBackend *)dev->backend_data;
    if (mb == NULL || mb->device == nil) return false;
    /* backend/feature_bits are pre-filled by the rhi_device_get_info wrapper
     * from dev->capabilities; this fills the hardware identity. */
    @autoreleasepool {
        const char *name = [mb->device.name UTF8String];
        if (name != NULL) {
            snprintf(out->device_name, sizeof(out->device_name), "%s", name);
        }
    }
    out->vendor_id = [mb->device supportsFamily:MTLGPUFamilyApple1] ? 0x106Bu : 0u;
    out->device_id = 0u;
    out->api_version = (3u << 22);   /* Metal 3 baseline (macOS 14 / Xcode 15) */
    out->driver_version = 0u;
    return true;
}

bool rhi_backend_texture_get_native_info( const RHIDevice *dev, RHITexture texture, RHITextureNativeInfo *out) {
    LOG_ERROR("rhi_metal: rhi_backend_texture_get_native_info not implemented");
    (void)dev;
    (void)texture;
    (void)out;
    return false;
}

bool rhi_backend_cmd_buffer_get_native_info( const RHIDevice *dev, const RHICmdBuffer *cmd, RHICmdBufferNativeInfo *out) {
    LOG_ERROR("rhi_metal: rhi_backend_cmd_buffer_get_native_info not implemented");
    (void)dev;
    (void)cmd;
    (void)out;
    return false;
}

u32 rhi_vk_validation_message_count(void) {
    LOG_ERROR("rhi_metal: rhi_vk_validation_message_count not implemented");
    return 0u;
}

void rhi_vk_validation_message_count_reset(void) {
    LOG_ERROR("rhi_metal: rhi_vk_validation_message_count_reset not implemented");
}

bool rhi_vk_validation_gate_active(void) {
    LOG_ERROR("rhi_metal: rhi_vk_validation_gate_active not implemented");
    return false;
}

void rhi_vk_validation_set_enabled(bool enabled) {
    LOG_ERROR("rhi_metal: rhi_vk_validation_set_enabled not implemented");
    (void)enabled;
}

/* ---- Task 7: resource family ----
 * Obj-C objects live in slot-table payloads whose lifetimes are managed by
 * rhi_alloc_slot/rhi_free_slot; destroy releases the MTL object, frees the
 * payload, and frees the slot. In-flight safety: Metal command buffers
 * retain every resource encoded into them, so a release can never dangle
 * the GPU — destroy additionally drains (bounded, Task 4 rule) when commits
 * are still in flight, matching the D3D12 retire-fence semantics. */
typedef struct {
    id<MTLBuffer> buffer;
    id<MTLTexture> texel_view;  /* cached RGBA32F view for RHI_BUFFER_USAGE_TEXEL */
    usize size;
    RHIBufferUsage usage;
    bool shared_mode;   /* MTLResourceStorageModeShared (host-visible) */
} MetalBuffer;

typedef struct {
    id<MTLTexture> texture;
    RHIFormat format;
    u32 width;
    u32 height;
    u32 mip_levels;
    u32 layers;         /* 1 = 2D, 6 = cube, N = 2D array */
    bool is_cube;
} MetalTexture;

typedef struct {
    id<MTLSamplerState> sampler;
} MetalSampler;

/* Storage-mode rule (Task 7 brief): shared when the host ever touches the
 * bytes (initial_data != NULL or UNIFORM usage), private only for pure-GPU
 * usages (STORAGE/INDIRECT/AS_BUILD_INPUT/DEVICE_ADDRESS) with no initial
 * data — the committed/placed decision analogue of rhi_d3d12.c.
 * iOS texel views use private storage and staged uploads instead: Simulator
 * rejects a linear texture backed by a shared buffer. */
#ifdef ENGINE_RHI_TEST
static bool rhi_test_private_texel;
#endif
static bool metal_buffer_wants_private(const RHIBufferDesc *desc) {
    const RHIBufferUsage gpu_only = (RHIBufferUsage)(
        RHI_BUFFER_USAGE_STORAGE | RHI_BUFFER_USAGE_INDIRECT |
        RHI_BUFFER_USAGE_AS_BUILD_INPUT | RHI_BUFFER_USAGE_DEVICE_ADDRESS);
    const RHIBufferUsage host_side = (RHIBufferUsage)(
        RHI_BUFFER_USAGE_VERTEX | RHI_BUFFER_USAGE_INDEX |
        RHI_BUFFER_USAGE_UNIFORM | RHI_BUFFER_USAGE_TEXEL);
    if ((desc->usage & RHI_BUFFER_USAGE_TEXEL) != 0) {
#if TARGET_OS_IOS
        return true;
#elif defined(ENGINE_RHI_TEST)
        if (rhi_test_private_texel) return true;
#endif
    }
    if (desc->initial_data != NULL) return false;
    return (desc->usage & gpu_only) != 0 && (desc->usage & host_side) == 0;
}

/* Bounded one-shot submit for the resource family (staging uploads and
 * readbacks). waitUntilCompleted has no timeout and hangs forever on a
 * wedged GPU (Task 3 handoff), so the wait goes through drain_event like
 * metal_drain; on timeout the device is latched lost. The trailing
 * waitUntilCompleted returns at once (the event already signaled) and
 * quiesces the completion handler before the caller's autoreleasepool
 * drains the staging buffer. */
static RHIResult metal_commit_wait(RHIDevice *dev, MetalBackend *mb,
                                   id<MTLCommandBuffer> cmd) {
    u64 value;
    RHIResult result;
    if (mb->device_lost_latch) return RHI_RESULT_DEVICE_LOST;
    if (mb->drain_event == nil) {
        mb->drain_event = [mb->device newSharedEvent];
        if (mb->drain_event == nil) {
            LOG_ERROR("rhi_metal: newSharedEvent failed");
            return RHI_RESULT_SYNC_FAILED;
        }
    }
    value = ++mb->drain_counter;
    [cmd encodeSignalEvent:mb->drain_event value:value];
    result = metal_commit(dev, cmd);
    if (result != RHI_RESULT_OK) return result;
    if (![mb->drain_event waitUntilSignaledValue:value
                                     timeoutMS:RHI_METAL_DRAIN_TIMEOUT_MS]) {
        LOG_ERROR("rhi_metal: resource submit unsignaled after %llu ms",
                  (unsigned long long)RHI_METAL_DRAIN_TIMEOUT_MS);
        metal_note_device_lost(dev, mb, "resource submit timeout");
        return RHI_RESULT_SYNC_FAILED;
    }
    metal_check_cmd_error(dev, mb, cmd, "resource submit");
    if (mb->device_lost_latch) return RHI_RESULT_DEVICE_LOST;
    [cmd waitUntilCompleted];
    return RHI_RESULT_OK;
}

static bool metal_buffer_upload_initial(RHIDevice *dev, MetalBackend *mb,
                                        id<MTLBuffer> buffer, const void *data,
                                        usize size, bool shared_mode) {
    if (data == NULL) return true;
    if (shared_mode) {
        memcpy(buffer.contents, data, size);
        return true;
    }
    @autoreleasepool {
        id<MTLBuffer> staging = [mb->device newBufferWithBytes:data
                                                       length:(NSUInteger)size
                                                      options:MTLResourceStorageModeShared];
        if (staging == nil) {
            LOG_ERROR("rhi_metal: initial buffer staging allocation failed");
            return false;
        }
        id<MTLCommandBuffer> cmd = [mb->queue commandBuffer];
        if (cmd == nil) {
            LOG_ERROR("rhi_metal: initial buffer upload command buffer failed");
            return false;
        }
        id<MTLBlitCommandEncoder> blit = [cmd blitCommandEncoder];
        if (blit == nil) {
            LOG_ERROR("rhi_metal: initial buffer upload encoder failed");
            return false;
        }
        [blit copyFromBuffer:staging sourceOffset:0u
                    toBuffer:buffer destinationOffset:0u size:(NSUInteger)size];
        [blit endEncoding];
        return metal_commit_wait(dev, mb, cmd) == RHI_RESULT_OK;
    }
}

/* Destroy-time in-flight safety (Task 5 retire parity): drain (bounded)
 * only when commits are actually in flight. */
static void metal_retire_drain(RHIDevice *dev, MetalBackend *mb) {
    if (atomic_load_explicit(&mb->pending_handlers, memory_order_acquire) != 0u)
        (void)metal_drain(dev, mb);
}

static u32 metal_texture_bpp(RHIFormat f) {
    return rhi_metal_format_bytes_per_pixel(rhi_metal_format_from_rhi(f));
}

/* Texture usage bits. Color formats get the one-step triple (read +
 * render-target + shader-write) so no later consumer hits a
 * usage-deficient texture. Depth/stencil formats must NOT request
 * MTLTextureUsageShaderWrite — Metal does not support shader writes to
 * depth/stencil pixel formats (Texture Descriptor Validation may reject
 * the combination; observed permissive on M2/Metal 4, kept restrictive
 * here for older hosts and Metal validation runs). */
static MTLTextureUsage metal_texture_usage_for(RHIFormat f) {
    if (f == RHI_FORMAT_D32_FLOAT)
        return MTLTextureUsageShaderRead | MTLTextureUsageRenderTarget;
    return MTLTextureUsageShaderRead | MTLTextureUsageRenderTarget |
           MTLTextureUsageShaderWrite;
}

/* Upload one tightly-packed 2D region (native-format bytes, R593) into
 * (mip, slice) of a private texture via a shared staging buffer + blit —
 * the VK staging-upload analogue (rhi_vk.c vk_texture_sync_submit). */
static bool metal_texture_upload_region(RHIDevice *dev, MetalBackend *mb,
                                        MetalTexture *td, u32 mip, u32 slice,
                                        u32 w, u32 h, const void *data,
                                        usize data_size) {
    u32 bpp = metal_texture_bpp(td->format);
    usize row_bytes;
    bool ok = false;
    if (bpp == 0u || w == 0u || h == 0u) return false;
    row_bytes = (usize)w * bpp;
    if (data == NULL || data_size < row_bytes * (usize)h) {
        LOG_ERROR("rhi_metal: texture upload size %llu too small for %ux%u (bpp %u)",
                  (unsigned long long)data_size, (unsigned)w, (unsigned)h,
                  (unsigned)bpp);
        return false;
    }
    @autoreleasepool {
        id<MTLBuffer> staging =
            [mb->device newBufferWithBytes:data
                                   length:(NSUInteger)(row_bytes * (usize)h)
                                  options:MTLResourceStorageModeShared];
        id<MTLCommandBuffer> cmd;
        id<MTLBlitCommandEncoder> blit;
        if (staging == nil) {
            LOG_ERROR("rhi_metal: upload staging allocation failed");
            return false;
        }
        cmd = [mb->queue commandBuffer];
        if (cmd == nil) {
            LOG_ERROR("rhi_metal: upload command buffer allocation failed");
            return false;
        }
        blit = [cmd blitCommandEncoder];
        [blit copyFromBuffer:staging
                sourceOffset:0u
           sourceBytesPerRow:(NSUInteger)row_bytes
         sourceBytesPerImage:(NSUInteger)(row_bytes * (usize)h)
                  sourceSize:MTLSizeMake((NSUInteger)w, (NSUInteger)h, 1u)
                   toTexture:td->texture
            destinationSlice:(NSUInteger)slice
            destinationLevel:(NSUInteger)mip
           destinationOrigin:MTLOriginMake(0.0, 0.0, 0.0)];
        [blit endEncoding];
        ok = metal_commit_wait(dev, mb, cmd) == RHI_RESULT_OK;
    }
    return ok;
}

/* ---- Task 12: acceleration structures ----
 * MTLAccelerationStructure mapping with fail-closed gates. Availability is
 * the Task 3 capability bit (supportsRaytracing at device create) AND
 * macOS 13+ (the triangle-descriptor vertexFormat and gpuResourceID are
 * 13+); either missing -> every entry point fails closed (NULL / false /
 * no-op + log), and the *_ex wrappers surface RHI_RESULT_UNSUPPORTED
 * through the existing capability contract. RHI_FEATURE_RAY_TRACING_PIPELINE
 * is never set (Task 3: Metal's intersection-function model has no
 * raygen-pipeline equivalent); ray query rides
 * setAccelerationStructure:atBufferIndex: on the compute path. */

/* Forward: the Task 7 payload type this family consumes. */

static bool metal_rt_available(const RHIDevice *dev) {
    if ((dev->capabilities.feature_bits &
         RHI_FEATURE_ACCELERATION_STRUCTURE) == 0u) return false;
#if defined(__MAC_OS_X_VERSION_MAX_ALLOWED) && \
    __MAC_OS_X_VERSION_MAX_ALLOWED >= 130000
    if (@available(macOS 13.0, *)) return true;
#endif
    /* SDK without macOS 13 API markers cannot build the 13+ entry points
     * this family needs — fail closed (review fix M2: never a
     * misleading "available" fallback). */
    return false;
}

typedef struct MetalAS {
    id<MTLAccelerationStructure> structure;   /* +1 owned (newAccelerationStructureWithSize:) */
} MetalAS;

static bool metal_as_registry_add(MetalBackend *mb, MetalAS *ad) {
    if (mb->as_count == mb->as_cap) {
        u32 ncap = mb->as_cap == 0u ? 8u : mb->as_cap * 2u;
        MetalAS **nr =
            (MetalAS **)realloc(mb->as_registry, ncap * sizeof(*nr));
        if (nr == NULL) return false;
        mb->as_registry = nr;
        mb->as_cap = ncap;
    }
    mb->as_registry[mb->as_count++] = ad;
    return true;
}

static void metal_as_registry_remove(MetalBackend *mb, MetalAS *ad) {
    u32 i;
    for (i = 0u; i < mb->as_count; ++i) {
        if (mb->as_registry[i] == ad) {
            mb->as_registry[i] = mb->as_registry[mb->as_count - 1u];
            mb->as_count--;
            return;
        }
    }
}

RHIAccelerationStructure rhi_backend_acceleration_structure_create( RHIDevice *dev, const RHIAccelerationStructureDesc *desc) {
    MetalBackend *mb;
    MetalAS *ad;
    u32 slot;
    if (dev == NULL || desc == NULL || !metal_rt_available(dev))
        return RHI_HANDLE_NULL;
    mb = (MetalBackend *)dev->backend_data;
    if (mb == NULL || mb->device_lost_latch) return RHI_HANDLE_NULL;
    if (desc->storage_size == 0u) {
        /* The engine flow always sizes via the prebuild query; a zero size
         * has no Metal meaning — fail closed instead of a zero-byte AS. */
        LOG_ERROR("rhi_metal: AS create with storage_size 0 (query build sizes first)");
        return RHI_HANDLE_NULL;
    }
    ad = (MetalAS *)calloc(1u, sizeof(*ad));
    if (ad == NULL) return RHI_HANDLE_NULL;
    if (!metal_as_registry_add(mb, ad)) {
        free(ad);
        return RHI_HANDLE_NULL;
    }
    @autoreleasepool {
        /* newAccelerationStructureWithSize: returns +1 (new* rule). */
        ad->structure = [mb->device
            newAccelerationStructureWithSize:(NSUInteger)desc->storage_size];
    }
    if (ad->structure == nil) {
        LOG_ERROR("rhi_metal: newAccelerationStructureWithSize failed (%llu bytes)",
                  (unsigned long long)desc->storage_size);
        metal_as_registry_remove(mb, ad);
        free(ad);
        return RHI_HANDLE_NULL;
    }
    slot = rhi_alloc_slot(dev);
    dev->slots[slot].ptr = ad;
    dev->slots[slot].type = RHI_RES_ACCELERATION_STRUCTURE;
    return rhi_make_handle(slot, dev->slots[slot].generation);
}

void rhi_backend_acceleration_structure_destroy( RHIDevice *dev, RHIAccelerationStructure structure) {
    MetalBackend *mb;
    MetalAS *ad;
    if (dev == NULL) return;
    mb = (MetalBackend *)dev->backend_data;
    ad = (MetalAS *)rhi_get_resource_typed(dev, structure,
                                           RHI_RES_ACCELERATION_STRUCTURE);
    if (ad == NULL) return;
    if (mb != NULL) {
        metal_retire_drain(dev, mb);
        metal_as_registry_remove(mb, ad);
    }
    [ad->structure release];
    free(ad);
    rhi_free_slot(dev, structure);
}

u64 rhi_backend_acceleration_structure_get_device_address( RHIDevice *dev, RHIAccelerationStructure structure) {
    MetalAS *ad;
    if (dev == NULL) return 0u;
    ad = (MetalAS *)rhi_get_resource_typed(dev, structure,
                                           RHI_RES_ACCELERATION_STRUCTURE);
    if (ad == NULL) return 0u;
    /* Metal 4 made MTLResourceID an opaque struct (no u64 conversion), so
     * the "device address" exposed to the VK-ABI instance records is a
     * synthetic value: the payload pointer. It is unique, nonzero, stable
     * for the payload's life, and round-trips through the registry lookup
     * in metal_as_convert_tlas_record — the only consumer. */
    return (u64)(uintptr_t)ad;
}

bool rhi_backend_acceleration_structure_get_vk_handle( RHIDevice *dev, RHIAccelerationStructure structure, void **out_handle) {
    /* Not Vulkan: there is no VkAccelerationStructureKHR to expose. */
    if (out_handle != NULL) *out_handle = NULL;
    (void)dev;
    (void)structure;
    return false;
}

/* Shared triangle-geometry descriptor (vertex/index buffers ride the RHI
 * buffers' MTLBuffer directly — no copy). Autoreleased. */
static MTLAccelerationStructureTriangleGeometryDescriptor *
metal_as_triangle_desc(const RHIBLASOneTriangleDesc *desc,
                       MetalBuffer *vb, MetalBuffer *ib) {
    MTLAccelerationStructureTriangleGeometryDescriptor *tri =
        [MTLAccelerationStructureTriangleGeometryDescriptor descriptor];
    tri.vertexBuffer = vb->buffer;
    tri.vertexBufferOffset = (NSUInteger)desc->vertex_offset;
    tri.vertexStride = (NSUInteger)desc->vertex_stride;
    tri.vertexFormat = MTLAttributeFormatFloat3;   /* R32G32B32_SFLOAT */
    tri.indexBuffer = ib->buffer;
    tri.indexBufferOffset = (NSUInteger)desc->index_offset;
    tri.indexType = MTLIndexTypeUInt32;
    tri.triangleCount = 1u;
    return tri;
}

bool rhi_blas_one_triangle_get_build_sizes( RHIDevice *dev, const RHIBLASOneTriangleDesc *desc, RHIAccelerationStructureBuildSizes *out_sizes) {
    MetalBackend *mb;
    MetalBuffer *vb, *ib;
    if (out_sizes != NULL) memset(out_sizes, 0, sizeof(*out_sizes));
    if (dev == NULL || out_sizes == NULL || !metal_rt_available(dev) ||
        !rhi_blas_one_triangle_desc_validate(desc)) {
        return false;
    }
    mb = (MetalBackend *)dev->backend_data;
    if (mb == NULL || mb->device_lost_latch) return false;
    vb = (MetalBuffer *)rhi_get_resource_typed(dev, desc->vertex_buffer,
                                               RHI_RES_BUFFER);
    ib = (MetalBuffer *)rhi_get_resource_typed(dev, desc->index_buffer,
                                               RHI_RES_BUFFER);
    if (vb == NULL || ib == NULL) return false;
    @autoreleasepool {
        MTLAccelerationStructureTriangleGeometryDescriptor *tri =
            metal_as_triangle_desc(desc, vb, ib);
        MTLPrimitiveAccelerationStructureDescriptor *pd =
            [MTLPrimitiveAccelerationStructureDescriptor descriptor];
        MTLAccelerationStructureSizes sizes;
        pd.geometryDescriptors = @[ tri ];
        sizes = [mb->device accelerationStructureSizesWithDescriptor:pd];
        out_sizes->acceleration_structure_size =
            (usize)sizes.accelerationStructureSize;
        out_sizes->build_scratch_size = (usize)sizes.buildScratchBufferSize;
    }
    return out_sizes->acceleration_structure_size != 0u &&
           out_sizes->build_scratch_size != 0u;
}

bool rhi_backend_cmd_build_blas_one_triangle( RHICmdBuffer *cmd, RHIDevice *dev, RHIAccelerationStructure blas, const RHIBLASOneTriangleDesc *desc, RHIBuffer scratch_buffer, usize scratch_offset) {
    MetalBackend *mb;
    MetalAS *ad;
    MetalBuffer *scratch, *vb, *ib;
    bool ok = false;
    if (dev == NULL || !metal_rt_available(dev) ||
        !rhi_blas_one_triangle_desc_validate(desc)) {
        return false;
    }
    mb = (MetalBackend *)dev->backend_data;
    /* VK parity: one-shot build outside a frame (cmd must be NULL). */
    if (mb == NULL || cmd != NULL || mb->frame_started) return false;
    ad = (MetalAS *)rhi_get_resource_typed(dev, blas,
                                           RHI_RES_ACCELERATION_STRUCTURE);
    scratch = (MetalBuffer *)rhi_get_resource_typed(dev, scratch_buffer,
                                                    RHI_RES_BUFFER);
    vb = (MetalBuffer *)rhi_get_resource_typed(dev, desc->vertex_buffer,
                                               RHI_RES_BUFFER);
    ib = (MetalBuffer *)rhi_get_resource_typed(dev, desc->index_buffer,
                                               RHI_RES_BUFFER);
    if (ad == NULL || scratch == NULL || vb == NULL || ib == NULL)
        return false;
    @autoreleasepool {
        MTLAccelerationStructureTriangleGeometryDescriptor *tri =
            metal_as_triangle_desc(desc, vb, ib);
        MTLPrimitiveAccelerationStructureDescriptor *pd =
            [MTLPrimitiveAccelerationStructureDescriptor descriptor];
        id<MTLCommandBuffer> cb;
        id<MTLAccelerationStructureCommandEncoder> enc;
        pd.geometryDescriptors = @[ tri ];
        cb = [mb->queue commandBuffer];
        if (cb == nil) {
            LOG_ERROR("rhi_metal: BLAS build command buffer failed");
            return false;
        }
        /* accelerationStructureCommandEncoder is autoreleased. */
        enc = [cb accelerationStructureCommandEncoder];
        if (enc == nil) {
            LOG_ERROR("rhi_metal: AS command encoder failed");
            return false;
        }
        [enc buildAccelerationStructure:ad->structure
                             descriptor:pd
                          scratchBuffer:scratch->buffer
                    scratchBufferOffset:(NSUInteger)scratch_offset];
        [enc endEncoding];
        ok = metal_commit_wait(dev, mb, cb) == RHI_RESULT_OK;
    }
    return ok;
}

/* Read `size` bytes at `offset` of a MetalBuffer (shared -> direct copy;
 * private -> blit staging via rhi_buffer_read). `handle` is only needed for
 * the readback path. */
static bool metal_as_buffer_read(RHIDevice *dev, RHIBuffer handle,
                                 MetalBuffer *bb, usize offset, void *dst,
                                 usize size) {
    if (offset > bb->size || size > bb->size - offset) return false;
    if (bb->shared_mode) {
        memcpy(dst, (const u8 *)bb->buffer.contents + offset, (size_t)size);
        return true;
    }
    return rhi_buffer_read(dev, handle, dst, offset, size);
}

/* VK-ABI 64B instance record -> MTLAccelerationStructureUserIDInstanceDescriptor
 * (+ the BLAS object for instancedAccelerationStructures).
 * Unpack: bytes 0-47 transform row-major 3x4 (transposed into MTL's
 * column-major 4x3), bytes 48-51 packed0 = custom_index low24 | mask<<24,
 * bytes 52-55 packed1 = sbt_offset low24 | flags<<24, bytes 56-63 u64 BLAS
 * device address (registry linear lookup; unknown address -> fail closed). */
static bool metal_as_convert_tlas_record(RHIDevice *dev, const u8 *rec,
                                         MTLAccelerationStructureUserIDInstanceDescriptor *out,
                                         id<MTLAccelerationStructure> *out_blas) {
    MetalBackend *mb = (MetalBackend *)dev->backend_data;
    f32 transform[12];
    u32 packed0, packed1, flags;
    u64 blas_addr;
    u32 i;
    static bool warned_flags;
    memcpy(transform, rec, sizeof(transform));
    memcpy(&packed0, rec + 48, sizeof(packed0));
    memcpy(&packed1, rec + 52, sizeof(packed1));
    memcpy(&blas_addr, rec + 56, sizeof(blas_addr));
    for (i = 0u; i < mb->as_count; ++i) {
        MetalAS *ad = mb->as_registry[i];
        /* The record's "BLAS device address" is the synthetic payload
         * pointer minted by get_device_address. */
        if ((u64)(uintptr_t)ad == blas_addr) {
            /* VK row-major 3x4 -> MTLPackedFloat4x3 (four float3 columns):
             * column j = (t[j], t[j+4], t[j+8]). */
            out->transformationMatrix.columns[0] =
                MTLPackedFloat3Make(transform[0], transform[4], transform[8]);
            out->transformationMatrix.columns[1] =
                MTLPackedFloat3Make(transform[1], transform[5], transform[9]);
            out->transformationMatrix.columns[2] =
                MTLPackedFloat3Make(transform[2], transform[6], transform[10]);
            out->transformationMatrix.columns[3] =
                MTLPackedFloat3Make(transform[3], transform[7], transform[11]);
            out->options = 0u;
            out->mask = (packed0 >> 24) & 0xFFu;
            out->intersectionFunctionTableOffset = packed1 & 0x00FFFFFFu;
            out->accelerationStructureIndex = 0u;   /* single-instance array */
            out->userID = packed0 & 0x00FFFFFFu;
            flags = (packed1 >> 24) & 0xFFu;
            if (flags != 0u && !warned_flags) {
                LOG_WARN("rhi_metal: TLAS instance flags %#x not mapped in v1",
                         (unsigned)flags);
                warned_flags = true;
            }
            *out_blas = ad->structure;
            return true;
        }
    }
    LOG_ERROR("rhi_metal: TLAS instance references unknown BLAS address 0x%llx",
              (unsigned long long)blas_addr);
    return false;
}

/* Shared TLAS descriptor for the one-instance path: converts record 0 of
 * the caller's VK-ABI instance buffer into a staging buffer holding one
 * MTLAccelerationStructureUserIDInstanceDescriptor. The staging buffer is
 * +1 (newBufferWithBytes:) — the CALLER releases it after the sizes query /
 * build wait. Returns nil on failure (logged). */
static MTLInstanceAccelerationStructureDescriptor *
metal_as_tlas_desc(RHIDevice *dev, RHIBuffer instance_buffer,
                   id<MTLBuffer> *out_staging) {
    MetalBackend *mb = (MetalBackend *)dev->backend_data;
    MetalBuffer *inst;
    MTLInstanceAccelerationStructureDescriptor *idesc;
    u8 rec[RHI_TLAS_INSTANCE_SIZE];
    MTLAccelerationStructureUserIDInstanceDescriptor conv;
    id<MTLAccelerationStructure> blas = nil;
    *out_staging = nil;
    inst = (MetalBuffer *)rhi_get_resource_typed(dev, instance_buffer,
                                                 RHI_RES_BUFFER);
    if (inst == NULL || inst->size < RHI_TLAS_INSTANCE_SIZE) return nil;
    memset(&conv, 0, sizeof(conv));
    if (!metal_as_buffer_read(dev, instance_buffer, inst, 0u, rec,
                              sizeof(rec)) ||
        !metal_as_convert_tlas_record(dev, rec, &conv, &blas)) {
        return nil;
    }
    *out_staging =
        [mb->device newBufferWithBytes:&conv
                                length:sizeof(conv)
                               options:MTLResourceStorageModeShared];
    if (*out_staging == nil) {
        LOG_ERROR("rhi_metal: TLAS instance staging allocation failed");
        return nil;
    }
    idesc = [MTLInstanceAccelerationStructureDescriptor descriptor];
    idesc.instanceDescriptorBuffer = *out_staging;
    idesc.instanceDescriptorBufferOffset = 0u;
    idesc.instanceCount = 1u;
    idesc.instanceDescriptorType =
        MTLAccelerationStructureInstanceDescriptorTypeUserID;
    idesc.instancedAccelerationStructures = @[ blas ];
    return idesc;
}

bool rhi_backend_tlas_one_instance_get_build_sizes( RHIDevice *dev, RHIBuffer instance_buffer, RHIAccelerationStructureBuildSizes *out_sizes) {
    MetalBackend *mb;
    if (out_sizes != NULL) memset(out_sizes, 0, sizeof(*out_sizes));
    if (dev == NULL || out_sizes == NULL || !metal_rt_available(dev))
        return false;
    mb = (MetalBackend *)dev->backend_data;
    if (mb == NULL || mb->device_lost_latch) return false;
    @autoreleasepool {
        id<MTLBuffer> staging = nil;
        MTLInstanceAccelerationStructureDescriptor *idesc;
        MTLAccelerationStructureSizes sizes;
        idesc = metal_as_tlas_desc(dev, instance_buffer, &staging);
        if (idesc == nil) return false;
        sizes = [mb->device accelerationStructureSizesWithDescriptor:idesc];
        out_sizes->acceleration_structure_size =
            (usize)sizes.accelerationStructureSize;
        out_sizes->build_scratch_size = (usize)sizes.buildScratchBufferSize;
        [staging release];
    }
    return out_sizes->acceleration_structure_size != 0u &&
           out_sizes->build_scratch_size != 0u;
}

bool rhi_backend_cmd_build_tlas_one_instance( RHICmdBuffer *cmd, RHIDevice *dev, RHIAccelerationStructure tlas, RHIBuffer instance_buffer, RHIBuffer scratch_buffer, usize scratch_offset) {
    MetalBackend *mb;
    MetalAS *ad;
    MetalBuffer *scratch;
    bool ok = false;
    if (dev == NULL || !metal_rt_available(dev)) return false;
    mb = (MetalBackend *)dev->backend_data;
    /* VK parity: one-shot build outside a frame (cmd must be NULL). */
    if (mb == NULL || cmd != NULL || mb->frame_started) return false;
    ad = (MetalAS *)rhi_get_resource_typed(dev, tlas,
                                           RHI_RES_ACCELERATION_STRUCTURE);
    scratch = (MetalBuffer *)rhi_get_resource_typed(dev, scratch_buffer,
                                                    RHI_RES_BUFFER);
    if (ad == NULL || scratch == NULL) return false;
    @autoreleasepool {
        id<MTLBuffer> staging = nil;
        MTLInstanceAccelerationStructureDescriptor *idesc;
        id<MTLCommandBuffer> cb;
        id<MTLAccelerationStructureCommandEncoder> enc;
        idesc = metal_as_tlas_desc(dev, instance_buffer, &staging);
        if (idesc == nil) return false;
        cb = [mb->queue commandBuffer];
        if (cb == nil) {
            LOG_ERROR("rhi_metal: TLAS build command buffer failed");
            [staging release];
            return false;
        }
        enc = [cb accelerationStructureCommandEncoder];
        if (enc == nil) {
            LOG_ERROR("rhi_metal: AS command encoder failed");
            [staging release];
            return false;
        }
        [enc buildAccelerationStructure:ad->structure
                             descriptor:idesc
                          scratchBuffer:scratch->buffer
                    scratchBufferOffset:(NSUInteger)scratch_offset];
        [enc endEncoding];
        ok = metal_commit_wait(dev, mb, cb) == RHI_RESULT_OK;
        [staging release];
    }
    return ok;
}

RHIBuffer rhi_buffer_create(RHIDevice *dev, const RHIBufferDesc *desc) {
    MetalBackend *mb;
    MetalBuffer *bb;
    bool private_mode;
    usize allocation_size;
    usize texel_count = 0u, texel_rows = 0u;
    u32 idx;
    if (dev == NULL || !rhi_buffer_desc_validate(desc)) return RHI_HANDLE_NULL;
    mb = (MetalBackend *)dev->backend_data;
    if (mb == NULL || mb->device_lost_latch) return RHI_HANDLE_NULL;
    private_mode = metal_buffer_wants_private(desc);
    allocation_size = desc->size;
    if ((desc->usage & RHI_BUFFER_USAGE_TEXEL) != 0) {
        if (desc->size > (usize)-1 - 15u) return RHI_HANDLE_NULL;
        texel_count = (desc->size + 15u) / 16u;
        texel_rows = (texel_count + 4095u) / 4096u;
        if (texel_rows > (usize)-1 / (4096u * 16u))
            return RHI_HANDLE_NULL;
        /* The MSL samplerBuffer conversion addresses a fixed 4096-wide 2D
         * texture. Pad the physical allocation to complete rows; bb->size
         * remains the caller's logical byte count. */
        allocation_size = texel_rows * 4096u * 16u;
    }
    bb = (MetalBuffer *)calloc(1u, sizeof(*bb));
    if (bb == NULL) return RHI_HANDLE_NULL;
    bb->size = desc->size;
    bb->usage = desc->usage;
    bb->shared_mode = !private_mode;
    /* Factory methods are autoreleased; retain to survive the pool drain. */
    @autoreleasepool {
        MTLResourceOptions opts = private_mode
            ? MTLResourceStorageModePrivate : MTLResourceStorageModeShared;
        bb->buffer = [[mb->device newBufferWithLength:(NSUInteger)allocation_size
                                              options:opts] retain];
        if (bb->buffer != nil &&
            !metal_buffer_upload_initial(dev, mb, bb->buffer, desc->initial_data,
                                         desc->size, bb->shared_mode)) {
            [bb->buffer release];
            bb->buffer = nil;
        }
        if (bb->buffer != nil && texel_count != 0u) {
            MTLTextureDescriptor *td = [MTLTextureDescriptor
                texture2DDescriptorWithPixelFormat:MTLPixelFormatRGBA32Float
                width:(NSUInteger)(texel_count < 4096u ? texel_count : 4096u)
                height:(NSUInteger)texel_rows mipmapped:NO];
            td.usage = MTLTextureUsageShaderRead;
            td.storageMode = bb->buffer.storageMode;
            bb->texel_view = [bb->buffer newTextureWithDescriptor:td
                offset:0u bytesPerRow:(NSUInteger)(4096u * 16u)];
        }
    }
    if (bb->buffer == nil || (texel_count != 0u && bb->texel_view == nil)) {
        LOG_ERROR("rhi_metal: buffer/texel allocation failed (%llu bytes)",
                  (unsigned long long)desc->size);
        [bb->texel_view release];
        [bb->buffer release];
        free(bb);
        return RHI_HANDLE_NULL;
    }
    idx = rhi_alloc_slot(dev);
    dev->slots[idx].ptr = bb;
    dev->slots[idx].type = RHI_RES_BUFFER;
    return rhi_make_handle(idx, dev->slots[idx].generation);
}

void rhi_buffer_destroy(RHIDevice *dev, RHIBuffer buf) {
    MetalBackend *mb;
    MetalBuffer *bb;
    if (dev == NULL) return;
    mb = (MetalBackend *)dev->backend_data;
    bb = (MetalBuffer *)rhi_get_resource_typed(dev, buf, RHI_RES_BUFFER);
    if (bb == NULL) return;
    if (mb != NULL) metal_retire_drain(dev, mb);
    [bb->texel_view release];
    [bb->buffer release];
    free(bb);
    rhi_free_slot(dev, buf);
}

/* ---- Task 8/10: shader + pipeline family ----
 * Production path (Task 10): the renderer hands rhi_shader_create the GLSL
 * source text; the backend hashes it (rhi_metal_fnv1a64) and resolves the
 * offline-converted MSL function from the build-time manifest —
 * engine.metallib when it loaded at device create, else the manifest's
 * embedded MSL text compiled per shader (LOG_WARN). A hash miss fails
 * closed (LOG_ERROR + null handle): no runtime GLSL/MSL guessing in
 * production. The ENGINE_RHI_TEST hook below keeps the Task 8/9 contract
 * tests' inline-MSL sources working (same precedent as
 * rhi_test_metal_set_suspended). */
typedef struct {
    id<MTLLibrary> library;   /* retained: the function must not outlive it */
    id<MTLFunction> function;
    bool is_fragment;
    /* spirv-cross emits `constant uint* spvBufferSizeConstants
     * [[buffer(25)]]` for runtime-array SSBOs (`.length()`), one uint BYTE
     * SIZE per such SSBO (the MSL divides by the element stride itself).
     * bsc_buffer_index[i] is the metal buffer argument index whose bound
     * buffer's byte size feeds entry i; parsed from the MSL text at shader
     * create (metal_parse_buffer_size_constants). */
    u8 bsc_count;
    u8 bsc_buffer_index[RHI_METAL_BSC_MAX];
} MetalShader;

#define RHI_METAL_BSC_ARG_INDEX 25u

/* Maps `constant uint& _61BufferSize = spvBufferSizeConstants[i];` aliases
 * back to the entry signature's `... _61 [[buffer(N)]] ...` declaration.
 * Text-local and fail-quiet (a shader without the pattern gets count 0);
 * an unmappable alias is a loud no-op so validation still catches it. */
static void metal_parse_buffer_size_constants(MetalShader *sd,
                                              const char *msl) {
    const char *p = msl;
    sd->bsc_count = 0u;
    if (msl == NULL) return;
    while ((p = strstr(p, " = spvBufferSizeConstants[")) != NULL) {
        static const char k_marker[] = " = spvBufferSizeConstants[";
        const char *alias_end = p;
        const char *alias_begin;
        const char *sig;
        char alias[96];
        char needle[128];
        usize alias_len;
        u32 table_index;
        u32 arg_index;
        p += sizeof(k_marker) - 1u;
        table_index = (u32)atoi(p);
        alias_begin = alias_end;
        while (alias_begin > msl && alias_begin[-1] != ' ' &&
               alias_begin[-1] != '\t' && alias_begin[-1] != '\n' &&
               alias_begin[-1] != '&')
            --alias_begin;
        alias_len = (usize)(alias_end - alias_begin);
        if (alias_len == 0u || alias_len >= sizeof(alias)) continue;
        memcpy(alias, alias_begin, alias_len);
        alias[alias_len] = '\0';
        /* spirv-cross names the alias <var>BufferSize; the signature
         * declares `<type>& <var> [[buffer(N)]]`. */
        if (alias_len > 10u && strcmp(alias + alias_len - 10u, "BufferSize") == 0)
            alias[alias_len - 10u] = '\0';
        snprintf(needle, sizeof(needle), "%s [[buffer(", alias);
        sig = strstr(msl, needle);
        if (sig == NULL) {
            LOG_ERROR("rhi_metal: spvBufferSizeConstants alias '%s' has no "
                      "buffer() declaration", alias);
            continue;
        }
        arg_index = (u32)atoi(sig + strlen(needle));
        if (table_index >= RHI_METAL_BSC_MAX) {
            LOG_ERROR("rhi_metal: spvBufferSizeConstants[%u] exceeds table "
                      "cap %u", (unsigned)table_index,
                      (unsigned)RHI_METAL_BSC_MAX);
            continue;
        }
        if (arg_index > 24u) {
            LOG_ERROR("rhi_metal: buffer-size constant source index %u out of "
                      "range", (unsigned)arg_index);
            continue;
        }
        sd->bsc_buffer_index[table_index] = (u8)arg_index;
        if (table_index + 1u > sd->bsc_count)
            sd->bsc_count = (u8)(table_index + 1u);
    }
}

/* MSL-source compile (test seam + embedded-MSL fallback). */
static RHIShader metal_shader_create_source(RHIDevice *dev, const char *source,
                                            usize len, const char *entry,
                                            bool is_fragment) {
    MetalBackend *mb;
    MetalShader *sd;
    u32 idx;
    if (dev == NULL || source == NULL || len == 0u || entry == NULL)
        return RHI_HANDLE_NULL;
    mb = (MetalBackend *)dev->backend_data;
    if (mb == NULL || mb->device_lost_latch) return RHI_HANDLE_NULL;
    sd = (MetalShader *)calloc(1u, sizeof(*sd));
    if (sd == NULL) return RHI_HANDLE_NULL;
    @autoreleasepool {
        NSString *src = [[NSString alloc] initWithBytes:source
                                                 length:(NSUInteger)len
                                               encoding:NSUTF8StringEncoding];
        NSError *err = nil;
        id<MTLLibrary> lib;
        id<MTLFunction> fn;
        if (src == nil) {
            LOG_ERROR("rhi_metal: shader source is not valid UTF-8");
            free(sd);
            return RHI_HANDLE_NULL;
        }
        lib = [mb->device newLibraryWithSource:src options:nil error:&err];
        [src release];
        if (lib == nil) {
            LOG_ERROR("rhi_metal: MSL compile failed: %s",
                      err != nil ? [[err localizedDescription] UTF8String]
                                 : "(no error info)");
            free(sd);
            return RHI_HANDLE_NULL;
        }
        fn = [lib newFunctionWithName:[NSString stringWithUTF8String:entry]];
        if (fn == nil) {
            LOG_ERROR("rhi_metal: MSL entry point '%s' not found", entry);
            [lib release];
            free(sd);
            return RHI_HANDLE_NULL;
        }
        /* new* methods return +1 under MRC — hold directly, no extra retain. */
        sd->library = lib;
        sd->function = fn;
    }
    {
        /* The caller's source is length-delimited, not necessarily
         * NUL-terminated — parse a private copy. */
        char *copy = (char *)malloc(len + 1u);
        if (copy != NULL) {
            memcpy(copy, source, len);
            copy[len] = '\0';
            metal_parse_buffer_size_constants(sd, copy);
            free(copy);
        }
    }
    sd->is_fragment = is_fragment;
    idx = rhi_alloc_slot(dev);
    dev->slots[idx].ptr = sd;
    dev->slots[idx].type = RHI_RES_SHADER;
    return rhi_make_handle(idx, dev->slots[idx].generation);
}

/* Manifest path: hash the incoming GLSL text and resolve the offline MSL
 * function. Returns RHI_HANDLE_NULL on a miss (fail closed). */
static RHIShader metal_shader_manifest_create(RHIDevice *dev,
                                              const char *source, usize len,
                                              bool is_fragment) {
    MetalBackend *mb;
    MetalShader *sd;
    u64 hash;
    usize i;
    u32 slot;
    if (dev == NULL || source == NULL || len == 0u) return RHI_HANDLE_NULL;
    mb = (MetalBackend *)dev->backend_data;
    if (mb == NULL || mb->device_lost_latch) return RHI_HANDLE_NULL;
    hash = rhi_metal_fnv1a64(source, len);
    for (i = 0u; i < rhi_metal_shader_manifest_count; ++i) {
        if (rhi_metal_shader_manifest[i].source_hash == hash) break;
    }
    if (i == rhi_metal_shader_manifest_count) {
        LOG_ERROR("rhi_metal: shader source hash 0x%016llx not in the offline "
                  "manifest — fail closed (no runtime GLSL compile)",
                  (unsigned long long)hash);
        return RHI_HANDLE_NULL;
    }
    sd = (MetalShader *)calloc(1u, sizeof(*sd));
    if (sd == NULL) return RHI_HANDLE_NULL;
    @autoreleasepool {
        const char *entry = rhi_metal_shader_manifest[i].msl_function;
        id<MTLFunction> fn = nil;
        if (mb->library != nil) {
            /* newFunctionWithName: returns +1 (new* rule). */
            fn = [mb->library
                newFunctionWithName:[NSString stringWithUTF8String:entry]];
            if (fn != nil) {
                sd->library = [mb->library retain];
                sd->function = fn;
            }
        } else {
#ifndef RHI_METAL_SHADER_NO_EMBEDDED_MSL
            /* metallib missing: compile this shader's embedded MSL text. */
            static bool warned_embedded = false;
            if (!warned_embedded) {
                LOG_WARN("rhi_metal: compiling embedded MSL (metallib missing)");
                warned_embedded = true;
            }
            /* Reuse the source-compile machinery against the embedded text. */
            {
                RHIShader tmp = metal_shader_create_source(
                    dev, rhi_metal_shader_msl[i],
                    (usize)strlen(rhi_metal_shader_msl[i]), entry, is_fragment);
                if (rhi_handle_valid(tmp)) {
                    MetalShader *inner = (MetalShader *)rhi_get_resource_typed(
                        dev, tmp, RHI_RES_SHADER);
                    /* Move the payload out of the temp slot. */
                    sd->library = inner->library;
                    sd->function = inner->function;
                    free(inner);
                    rhi_free_slot(dev, tmp);
                }
            }
#else
            LOG_ERROR("rhi_metal: engine.metallib missing and embedded MSL "
                      "compiled out (RHI_METAL_SHADER_NO_EMBEDDED_MSL)");
#endif
        }
        if (sd->function == nil) {
            LOG_ERROR("rhi_metal: manifest entry '%s' did not resolve", entry);
            free(sd);
            return RHI_HANDLE_NULL;
        }
    }
#ifndef RHI_METAL_SHADER_NO_EMBEDDED_MSL
    /* The embedded MSL text is the same bytes the metallib was compiled
     * from, so the buffer-size-constant layout parses identically either
     * way. (NO_EMBEDDED builds have no text to parse: bsc_count stays 0.) */
    metal_parse_buffer_size_constants(sd, rhi_metal_shader_msl[i]);
#endif
    sd->is_fragment = is_fragment;
    slot = rhi_alloc_slot(dev);
    dev->slots[slot].ptr = sd;
    dev->slots[slot].type = RHI_RES_SHADER;
    return rhi_make_handle(slot, dev->slots[slot].generation);
}

RHIShader rhi_shader_create(RHIDevice *dev, const char *source, usize len, bool is_fragment) {
    return metal_shader_manifest_create(dev, source, len, is_fragment);
}

RHIShader rhi_shader_create_compute(RHIDevice *dev, const char *source, usize len) {
    return metal_shader_manifest_create(dev, source, len, false);
}

/* Path-based siblings. Metal resolves a shader by hashing its GLSL text
 * against the offline manifest (metal_shader_manifest_create), so it needs
 * the text, not the name — read the file and delegate exactly as the text
 * entry point does. An unreadable file is refused (RHI_HANDLE_NULL), the
 * same fail-closed outcome the manifest lookup gives on a hash miss. */
RHIShader rhi_shader_create_path(RHIDevice *dev, const char *path, bool is_fragment) {
    usize len = 0u;
    char *source;
    RHIShader sh;
    if (dev == NULL || path == NULL) return RHI_HANDLE_NULL;
    source = shader_read_file(path, &len);
    if (source == NULL) return RHI_HANDLE_NULL;
    sh = rhi_shader_create(dev, source, len, is_fragment);
    free(source);
    return sh;
}

RHIShader rhi_shader_create_compute_path(RHIDevice *dev, const char *path) {
    usize len = 0u;
    char *source;
    RHIShader sh;
    if (dev == NULL || path == NULL) return RHI_HANDLE_NULL;
    source = shader_read_file(path, &len);
    if (source == NULL) return RHI_HANDLE_NULL;
    sh = rhi_shader_create_compute(dev, source, len);
    free(source);
    return sh;
}

void rhi_shader_destroy(RHIDevice *dev, RHIShader shader) {
    MetalBackend *mb;
    MetalShader *sd;
    if (dev == NULL) return;
    mb = (MetalBackend *)dev->backend_data;
    sd = (MetalShader *)rhi_get_resource_typed(dev, shader, RHI_RES_SHADER);
    if (sd == NULL) return;
    if (mb != NULL) metal_retire_drain(dev, mb);
    [sd->function release];
    [sd->library release];
    free(sd);
    rhi_free_slot(dev, shader);
}

/* Vertex layout convention table, ported field-by-field from the VK
 * backend (rhi_vk.c vk_build_graphics_pipeline) so the same VBO bytes feed
 * both backends unchanged. Returns the resolved stride and the descriptor
 * (nil when the desc declares no vertex input). Caller releases *out_vd. */
static u32 metal_vertex_descriptor_for(const RHIPipelineDesc *desc,
                                       MTLVertexDescriptor **out_vd) {
    MTLVertexDescriptor *vd;
    u32 stride = desc->vertex_stride;
    *out_vd = nil;
    if (desc->no_vertex_input) return 0u;
    vd = [MTLVertexDescriptor vertexDescriptor];   /* autoreleased */
    vd.layouts[0].stepFunction = MTLVertexStepFunctionPerVertex;
    vd.layouts[0].stepRate = 1u;
    if (desc->font_vertex) {
        stride = 32u;
        vd.attributes[0].format = MTLVertexFormatFloat2;
        vd.attributes[0].offset = 0u;
        vd.attributes[1].format = MTLVertexFormatFloat2;
        vd.attributes[1].offset = 2u * sizeof(f32);
        vd.attributes[2].format = MTLVertexFormatFloat4;
        vd.attributes[2].offset = 4u * sizeof(f32);
    } else if (desc->skinned_vertex) {
        stride = 64u;
        vd.attributes[0].format = MTLVertexFormatFloat3;
        vd.attributes[0].offset = 0u;
        vd.attributes[1].format = MTLVertexFormatFloat3;
        vd.attributes[1].offset = 3u * sizeof(f32);
        vd.attributes[2].format = MTLVertexFormatFloat2;
        vd.attributes[2].offset = 6u * sizeof(f32);
        vd.attributes[3].format = MTLVertexFormatUInt4;
        vd.attributes[3].offset = 8u * sizeof(f32);
        vd.attributes[4].format = MTLVertexFormatFloat4;
        vd.attributes[4].offset = 8u * sizeof(f32) + 4u * sizeof(u32);
    } else if (desc->is_shadow_depth) {
        /* R440 parity: shadow-depth vertex shaders consume location 0 only;
         * the binding stride stays the mesh stride. */
        stride = stride > 0u ? stride : 32u;
        vd.attributes[0].format = MTLVertexFormatFloat3;
        vd.attributes[0].offset = 0u;
    } else if (stride == 12u) {
        vd.attributes[0].format = MTLVertexFormatFloat3;
        vd.attributes[0].offset = 0u;
    } else {
        stride = stride > 0u ? stride : 32u;
        vd.attributes[0].format = MTLVertexFormatFloat3;
        vd.attributes[0].offset = 0u;
        vd.attributes[1].format = MTLVertexFormatFloat3;
        vd.attributes[1].offset = 3u * sizeof(f32);
        vd.attributes[2].format = MTLVertexFormatFloat2;
        vd.attributes[2].offset = 6u * sizeof(f32);
    }
    {
        /* Walk the declared attributes to bind them all to buffer 0. */
        u32 attr_count = desc->font_vertex ? 3u
            : desc->skinned_vertex ? 5u
            : (desc->is_shadow_depth || stride == 12u) ? 1u : 3u;
        u32 i;
        for (i = 0u; i < attr_count; ++i) vd.attributes[i].bufferIndex = 0u;
    }
    vd.layouts[0].stride = (NSUInteger)stride;
    *out_vd = vd;
    return stride;
}

/* Depth-stencil state cache (backend-owned; pipelines hold weak refs — all
 * pipelines are destroyed before the device releases the cache). R445
 * ("no depth test") is a real MTLCompareFunctionAlways + write-off state,
 * NOT a nil state: the depth-stencil state is sticky encoder state, so a
 * nil payload would leave a previous pipeline's state in force on a reused
 * encoder (review fix C2). */
static id<MTLDepthStencilState> metal_depth_state(MetalBackend *mb,
                                                  bool lequal,
                                                  bool write_disable) {
    u32 idx = (lequal ? 2u : 0u) | (write_disable ? 1u : 0u);
    if (mb->depth_states[idx] != nil) return mb->depth_states[idx];
    @autoreleasepool {
        MTLDepthStencilDescriptor *d = [[MTLDepthStencilDescriptor alloc] init];
        d.depthCompareFunction = lequal ? MTLCompareFunctionLessEqual
                                        : MTLCompareFunctionLess;
        d.depthWriteEnabled = write_disable ? NO : YES;
        mb->depth_states[idx] =
            [mb->device newDepthStencilStateWithDescriptor:d];   /* +1, cache-owned */
        [d release];
    }
    if (mb->depth_states[idx] == nil)
        LOG_ERROR("rhi_metal: newDepthStencilStateWithDescriptor failed");
    return mb->depth_states[idx];
}

/* R445 state: depth test fully off (Always + no write). */
static id<MTLDepthStencilState> metal_depth_state_always_off(MetalBackend *mb) {
    if (mb->depth_states[4] != nil) return mb->depth_states[4];
    @autoreleasepool {
        MTLDepthStencilDescriptor *d = [[MTLDepthStencilDescriptor alloc] init];
        d.depthCompareFunction = MTLCompareFunctionAlways;
        d.depthWriteEnabled = NO;
        mb->depth_states[4] =
            [mb->device newDepthStencilStateWithDescriptor:d];   /* +1, cache-owned */
        [d release];
    }
    if (mb->depth_states[4] == nil)
        LOG_ERROR("rhi_metal: newDepthStencilStateWithDescriptor failed");
    return mb->depth_states[4];
}

typedef struct MetalPipeline {
    id<MTLRenderPipelineState> pipeline;   /* graphics; nil when is_compute */
    id<MTLComputePipelineState> compute;   /* Task 9; nil unless is_compute */
    id<MTLDepthStencilState> depth_state; /* always non-nil for graphics;
                                           * R445 maps to the Always+write-off
                                           * cached state */
    RHIPipelineDesc desc;      /* retained copy, shader handles nulled (VK
                                * build_desc parity; the push-block layout
                                * flags are consumed by Task 11's binder) */
    u32 vertex_stride;         /* resolved; 0 when no_vertex_input */
    bool is_compute;
    bool point_list;           /* R168-C: draw uses MTLPrimitiveTypePoint */
    bool mrt_pipeline;         /* binds only into its MRT-format passes */
    /* Rasterizer state is encoder state in Metal (unlike VK's PSO), so the
     * desc's cull/fill choices are recorded here and applied at bind. */
    bool cull_none;            /* no_vertex_input || disable_culling */
    bool wireframe;            /* setTriangleFillMode: Lines */
    /* Task 15: bind-time color0 pixelFormat variants. The engine's postfx
     * pipelines historically leave desc->color_format at 0 (BGRA8) and rely
     * on driver leniency when bound into R16G16B16A16_SFLOAT FBO passes
     * (VK build: color_format 0 resolves to the swap format — UB by the
     * render-pass compatibility rules, tolerated everywhere). Metal
     * validation refuses, so the backend rebuilds the state with the
     * pass's actual color0 format (small cache; single-attachment only —
     * MRT formats are declared explicitly and stay strict). */
    MTLRenderPipelineDescriptor *proto;  /* nil for MRT/depth-only/compute */
    MTLPixelFormat declared_color_fmt;
    struct {
        MTLPixelFormat fmt;
        id<MTLRenderPipelineState> state;
    } variants[4];
    u32 variant_count;
    /* Copied from the source shader(s) at create (compute: desc->frag;
     * graphics: desc->vert) — see MetalShader. */
    u8 bsc_count;
    u8 bsc_buffer_index[RHI_METAL_BSC_MAX];
} MetalPipeline;

RHIPipeline rhi_pipeline_create(RHIDevice *dev, const RHIPipelineDesc *desc) {
    MetalBackend *mb;
    MetalShader *vs;
    MetalShader *fs = NULL;
    MetalPipeline *pp;
    u32 idx;
    u32 samples;
    u32 color_count;
    bool ok = false;
    if (dev == NULL || desc == NULL) return RHI_HANDLE_NULL;
    mb = (MetalBackend *)dev->backend_data;
    if (mb == NULL || mb->device_lost_latch) return RHI_HANDLE_NULL;
    if (desc->is_compute) {
        /* Task 9: VK convention — the compute shader rides desc->frag. */
        MetalShader *cs = (MetalShader *)rhi_get_resource_typed(
            dev, desc->frag, RHI_RES_SHADER);
        MetalPipeline *cp;
        if (cs == NULL) return RHI_HANDLE_NULL;
        cp = (MetalPipeline *)calloc(1u, sizeof(*cp));
        if (cp == NULL) return RHI_HANDLE_NULL;
        @autoreleasepool {
            NSError *err = nil;
            /* newComputePipelineStateWithFunction: returns +1 (new* rule). */
            cp->compute = [mb->device
                newComputePipelineStateWithFunction:cs->function error:&err];
            if (cp->compute == nil) {
                LOG_ERROR("rhi_metal: newComputePipelineState failed: %s",
                          err != nil ? [[err localizedDescription] UTF8String]
                                     : "(no error info)");
                free(cp);
                return RHI_HANDLE_NULL;
            }
        }
        cp->desc = *desc;
        cp->desc.vert = RHI_HANDLE_NULL;
        cp->desc.frag = RHI_HANDLE_NULL;
        cp->is_compute = true;
        cp->bsc_count = cs->bsc_count;
        memcpy(cp->bsc_buffer_index, cs->bsc_buffer_index,
               sizeof(cp->bsc_buffer_index));
        {
            u32 cidx = rhi_alloc_slot(dev);
            dev->slots[cidx].ptr = cp;
            dev->slots[cidx].type = RHI_RES_PIPELINE;
            return rhi_make_handle(cidx, dev->slots[cidx].generation);
        }
    }
    vs = (MetalShader *)rhi_get_resource_typed(dev, desc->vert, RHI_RES_SHADER);
    if (vs == NULL) return RHI_HANDLE_NULL;
    if (rhi_handle_valid(desc->frag)) {
        fs = (MetalShader *)rhi_get_resource_typed(dev, desc->frag,
                                                   RHI_RES_SHADER);
        if (fs == NULL) return RHI_HANDLE_NULL;
    }
    if (!desc->is_shadow_depth && fs == NULL) return RHI_HANDLE_NULL;
    if (desc->mrt_attachment_count > 1u &&
        !rhi_mrt_formats_valid(desc->mrt_formats, desc->mrt_attachment_count)) {
        return RHI_HANDLE_NULL;
    }
    samples = desc->sample_count == 0u ? 1u : desc->sample_count;
    if (rhi_sample_count_bit(samples) == 0u ||
        (dev->capabilities.color_sample_counts &
         rhi_sample_count_bit(samples)) == 0u) {
        LOG_ERROR("rhi_metal: unsupported pipeline sample count %u",
                  (unsigned)samples);
        return RHI_HANDLE_NULL;
    }
    color_count = desc->is_shadow_depth ? 0u
        : desc->mrt_attachment_count > 1u ? desc->mrt_attachment_count : 1u;
    pp = (MetalPipeline *)calloc(1u, sizeof(*pp));
    if (pp == NULL) return RHI_HANDLE_NULL;
    @autoreleasepool {
        MTLRenderPipelineDescriptor *pd =
            [[MTLRenderPipelineDescriptor alloc] init];   /* +1 */
        MTLVertexDescriptor *vd = nil;
        NSError *err = nil;
        u32 i;
        pd.vertexFunction = vs->function;
        pd.fragmentFunction = fs != NULL ? fs->function : nil;
        pp->vertex_stride = metal_vertex_descriptor_for(desc, &vd);
        if (vd != nil) pd.vertexDescriptor = vd;
        for (i = 0u; i < color_count; ++i) {
            MTLRenderPipelineColorAttachmentDescriptor *att =
                pd.colorAttachments[i];
            RHIFormat fmt = desc->mrt_attachment_count > 1u
                ? desc->mrt_formats[i]
                : desc->color_format;
            RHIMetalFormat mf;
            /* The unset default (RHI_FORMAT_R8G8B8A8_UNORM == 0) selects the
             * swapchain format (rhi.h contract; vk_desc_base_color_fmt
             * parity). */
            if (desc->mrt_attachment_count <= 1u &&
                fmt == RHI_FORMAT_R8G8B8A8_UNORM) {
                fmt = mb->swapchain_format;
            }
            if (!rhi_format_is_color(fmt)) {
                /* Fail closed: depth/undefined formats never become a color
                 * attachment (MRT formats are pre-screened by
                 * rhi_mrt_formats_valid). */
                LOG_ERROR("rhi_metal: pipeline color format %d is not a color format",
                          (int)fmt);
                [pd release];
                free(pp);
                return RHI_HANDLE_NULL;
            }
            mf = rhi_metal_format_from_rhi(fmt);
            if (mf == RHI_METAL_FORMAT_INVALID) {
                LOG_ERROR("rhi_metal: pipeline color format %d has no Metal mapping",
                          (int)fmt);
                [pd release];
                free(pp);
                return RHI_HANDLE_NULL;
            }
            att.pixelFormat = rhi_metal_pixel_format(mf);
            att.blendingEnabled = desc->alpha_blend ? YES : NO;
            if (desc->alpha_blend) {
                att.sourceRGBBlendFactor = MTLBlendFactorSourceAlpha;
                att.destinationRGBBlendFactor = MTLBlendFactorOneMinusSourceAlpha;
                att.rgbBlendOperation = MTLBlendOperationAdd;
                att.sourceAlphaBlendFactor = MTLBlendFactorSourceAlpha;
                att.destinationAlphaBlendFactor = MTLBlendFactorOneMinusSourceAlpha;
                att.alphaBlendOperation = MTLBlendOperationAdd;
            }
            /* alpha_blend_color_only: motion-vector RT1 stays unblended while
             * RT0 alpha-blends (Metal has independent blend unconditionally,
             * no feature gate needed unlike VK's feat_independent_blend). */
            if (desc->alpha_blend_color_only && i == 1u && color_count > 1u)
                att.blendingEnabled = NO;
        }
        /* Every RHI render pass carries a D32 depth attachment (swapchain
         * pass included — metal_open_screen_pass), so the pipeline declares
         * it unconditionally; R445 "no depth test" is a nil depth-stencil
         * STATE, not an absent attachment format. */
        pd.depthAttachmentPixelFormat = MTLPixelFormatDepth32Float;
        pd.rasterSampleCount = (NSUInteger)samples;
        /* newRenderPipelineStateWithDescriptor: returns +1 (new* rule). */
        pp->pipeline = [mb->device newRenderPipelineStateWithDescriptor:pd
                                                                 error:&err];
        if (pp->pipeline == nil) {
            LOG_ERROR("rhi_metal: newRenderPipelineState failed: %s",
                      err != nil ? [[err localizedDescription] UTF8String]
                                 : "(no error info)");
            [pd release];
            free(pp);
            return RHI_HANDLE_NULL;
        }
        if (color_count == 1u) {
            pp->proto = [pd copy];   /* +1; bind-time variant template */
            pp->declared_color_fmt = pd.colorAttachments[0].pixelFormat;
        }
        [pd release];
        ok = true;
    }
    if (!ok) {   /* defensive; all failure paths above return early */
        free(pp);
        return RHI_HANDLE_NULL;
    }
    /* R445: write_disable without lequal => depth test fully off, expressed
     * as the cached Always+write-off state (bind sets it unconditionally —
     * a skipped set would leave a previous pipeline's state in force). */
    if (desc->depth_write_disable && !desc->depth_compare_lequal) {
        pp->depth_state = metal_depth_state_always_off(mb);
    } else {
        pp->depth_state = metal_depth_state(mb, desc->depth_compare_lequal,
                                            desc->depth_write_disable);
    }
    if (pp->depth_state == nil) {
        [pp->pipeline release];
        free(pp);
        return RHI_HANDLE_NULL;
    }
    pp->desc = *desc;
    pp->desc.vert = RHI_HANDLE_NULL;
    pp->desc.frag = RHI_HANDLE_NULL;
    pp->point_list = desc->point_list;
    pp->mrt_pipeline = desc->mrt_attachment_count > 1u;
    pp->cull_none = desc->no_vertex_input || desc->disable_culling;
    pp->wireframe = desc->wireframe;
    pp->bsc_count = vs->bsc_count;
    memcpy(pp->bsc_buffer_index, vs->bsc_buffer_index,
           sizeof(pp->bsc_buffer_index));
    idx = rhi_alloc_slot(dev);
    dev->slots[idx].ptr = pp;
    dev->slots[idx].type = RHI_RES_PIPELINE;
    return rhi_make_handle(idx, dev->slots[idx].generation);
}

void rhi_pipeline_destroy(RHIDevice *dev, RHIPipeline pipe) {
    MetalBackend *mb;
    MetalPipeline *pp;
    if (dev == NULL) return;
    mb = (MetalBackend *)dev->backend_data;
    pp = (MetalPipeline *)rhi_get_resource_typed(dev, pipe, RHI_RES_PIPELINE);
    if (pp == NULL) return;
    if (mb != NULL) metal_retire_drain(dev, mb);
    [pp->pipeline release];
    [pp->compute release];
    [pp->proto release];
    {
        u32 vi;
        for (vi = 0u; vi < pp->variant_count; ++vi)
            [pp->variants[vi].state release];
    }
    free(pp);
    rhi_free_slot(dev, pipe);
}

RHITexture rhi_texture_create(RHIDevice *dev, const RHITextureDesc *desc) {
    MetalBackend *mb;
    MetalTexture *td;
    RHIMetalFormat mf;
    u32 mips;
    u32 idx;
    if (dev == NULL || !rhi_texture_desc_validate(desc)) return RHI_HANDLE_NULL;
    mb = (MetalBackend *)dev->backend_data;
    if (mb == NULL || mb->device_lost_latch) return RHI_HANDLE_NULL;
    mf = rhi_metal_format_from_rhi(desc->format);
    if (mf == RHI_METAL_FORMAT_INVALID) {
        /* Double-guard behind the shared validator: fail closed. */
        LOG_ERROR("rhi_metal: texture format %d has no Metal mapping",
                  (int)desc->format);
        return RHI_HANDLE_NULL;
    }
    mips = desc->mip_levels == 0u ? 1u : desc->mip_levels;
    td = (MetalTexture *)calloc(1u, sizeof(*td));
    if (td == NULL) return RHI_HANDLE_NULL;
    @autoreleasepool {
        MTLTextureDescriptor *d = [MTLTextureDescriptor
            texture2DDescriptorWithPixelFormat:rhi_metal_pixel_format(mf)
                                         width:(NSUInteger)desc->width
                                        height:(NSUInteger)desc->height
                                     mipmapped:(mips > 1u)];
        d.mipmapLevelCount = (NSUInteger)mips;
        d.usage = metal_texture_usage_for(desc->format);
        d.storageMode = MTLStorageModePrivate;   /* uploads: blit staging */
        td->texture = [[mb->device newTextureWithDescriptor:d] retain];
    }
    if (td->texture == nil) {
        LOG_ERROR("rhi_metal: texture allocation failed (%ux%u fmt %d)",
                  (unsigned)desc->width, (unsigned)desc->height,
                  (int)desc->format);
        free(td);
        return RHI_HANDLE_NULL;
    }
    td->format = desc->format;
    td->width = desc->width;
    td->height = desc->height;
    td->mip_levels = mips;
    td->layers = 1u;
    td->is_cube = false;
    if (desc->data != NULL) {
        /* R593: mip 0 texels in the format's native layout, tightly packed. */
        usize bytes = (usize)desc->width * desc->height *
                      metal_texture_bpp(desc->format);
        if (!metal_texture_upload_region(dev, mb, td, 0u, 0u, desc->width,
                                         desc->height, desc->data, bytes)) {
            [td->texture release];
            free(td);
            return RHI_HANDLE_NULL;
        }
    }
    idx = rhi_alloc_slot(dev);
    dev->slots[idx].ptr = td;
    dev->slots[idx].type = RHI_RES_TEXTURE;
    return rhi_make_handle(idx, dev->slots[idx].generation);
}

void rhi_texture_destroy(RHIDevice *dev, RHITexture tex) {
    MetalBackend *mb;
    MetalTexture *td;
    if (dev == NULL) return;
    mb = (MetalBackend *)dev->backend_data;
    td = (MetalTexture *)rhi_get_resource_typed(dev, tex, RHI_RES_TEXTURE);
    if (td == NULL) return;
    if (mb != NULL) metal_retire_drain(dev, mb);
    [td->texture release];
    free(td);
    rhi_free_slot(dev, tex);
}

RHITexture rhi_texture_array_create(RHIDevice *dev, u32 width, u32 height, u32 layers, RHIFormat fmt) {
    MetalBackend *mb;
    MetalTexture *td;
    RHIMetalFormat mf;
    u32 idx;
    if (dev == NULL || width == 0u || height == 0u || layers == 0u ||
        width > RHI_MAX_DRAWABLE_DIMENSION ||
        height > RHI_MAX_DRAWABLE_DIMENSION ||
        layers > RHI_MAX_TEXTURE_ARRAY_LAYERS) {
        return RHI_HANDLE_NULL;
    }
    mb = (MetalBackend *)dev->backend_data;
    if (mb == NULL || mb->device_lost_latch) return RHI_HANDLE_NULL;
    /* R441: 8-bit RGBA formats only (VK parity). */
    if (fmt != RHI_FORMAT_R8G8B8A8_UNORM && fmt != RHI_FORMAT_B8G8R8A8_UNORM) {
        LOG_ERROR("rhi_metal: texture array only supports RGBA8/BGRA8");
        return RHI_HANDLE_NULL;
    }
    mf = rhi_metal_format_from_rhi(fmt);   /* guaranteed valid by the check above */
    td = (MetalTexture *)calloc(1u, sizeof(*td));
    if (td == NULL) return RHI_HANDLE_NULL;
    @autoreleasepool {
        MTLTextureDescriptor *d = [MTLTextureDescriptor
            texture2DDescriptorWithPixelFormat:rhi_metal_pixel_format(mf)
                                         width:(NSUInteger)width
                                        height:(NSUInteger)height
                                     mipmapped:NO];
        d.textureType = MTLTextureType2DArray;
        d.arrayLength = (NSUInteger)layers;
        d.usage = MTLTextureUsageShaderRead | MTLTextureUsageShaderWrite;
        d.storageMode = MTLStorageModePrivate;
        td->texture = [[mb->device newTextureWithDescriptor:d] retain];
    }
    if (td->texture == nil) {
        LOG_ERROR("rhi_metal: texture array allocation failed (%ux%u x%u)",
                  (unsigned)width, (unsigned)height, (unsigned)layers);
        free(td);
        return RHI_HANDLE_NULL;
    }
    td->format = fmt;
    td->width = width;
    td->height = height;
    td->mip_levels = 1u;
    td->layers = layers;
    td->is_cube = false;
    idx = rhi_alloc_slot(dev);
    dev->slots[idx].ptr = td;
    dev->slots[idx].type = RHI_RES_TEXTURE;
    return rhi_make_handle(idx, dev->slots[idx].generation);
}

void rhi_texture_array_upload_layer(RHIDevice *dev, RHITexture tex, u32 layer, const void *rgba8, usize size) {
    MetalBackend *mb;
    MetalTexture *td;
    if (dev == NULL) return;
    mb = (MetalBackend *)dev->backend_data;
    if (mb == NULL || mb->device_lost_latch) return;
    td = (MetalTexture *)rhi_get_resource_typed(dev, tex, RHI_RES_TEXTURE);
    if (td == NULL || td->layers <= 1u || rgba8 == NULL) return;
    /* R441 host-OOB guard class (R417 parity): the copy reads w*h*4 bytes. */
    if (layer >= td->layers) return;
    if (size < (usize)td->width * td->height * 4u) return;
    (void)metal_texture_upload_region(dev, mb, td, 0u, layer, td->width,
                                      td->height, rgba8, size);
}

bool rhi_texture_get_size(RHIDevice *dev, RHITexture tex, u32 *out_w, u32 *out_h) {
    MetalTexture *td;
    if (dev == NULL || out_w == NULL || out_h == NULL) return false;
    td = (MetalTexture *)rhi_get_resource_typed(dev, tex, RHI_RES_TEXTURE);
    if (td == NULL) {
        /* R631: cubemap handles report the face extent (GL/VK parity). */
        td = (MetalTexture *)rhi_get_resource_typed(dev, tex, RHI_RES_CUBEMAP);
        if (td == NULL) return false;
    }
    *out_w = td->width;
    *out_h = td->height;
    return true;
}

bool rhi_texture_read_pixels(RHIDevice *dev, RHITexture tex, void *dst_rgba8, usize size) {
    MetalBackend *mb;
    MetalTexture *td;
    u32 bpp;
    u32 slices;
    usize face_bytes;
    usize stride;
    bool ok = false;
    if (dev == NULL || dst_rgba8 == NULL) return false;
    mb = (MetalBackend *)dev->backend_data;
    if (mb == NULL || mb->device_lost_latch) return false;
    td = (MetalTexture *)rhi_get_resource_typed(dev, tex, RHI_RES_TEXTURE);
    if (td == NULL) {
        /* R624: color cubemap readback — six faces face-major (+X,-X,+Y,
         * -Y,+Z,-Z = Metal cube slice order), mip 0, native bytes per
         * format (R587-R602). */
        td = (MetalTexture *)rhi_get_resource_typed(dev, tex, RHI_RES_CUBEMAP);
        if (td == NULL) return false;
    }
    bpp = metal_texture_bpp(td->format);
    if (bpp == 0u) return false;
    slices = td->is_cube ? 6u : 1u;
    face_bytes = (usize)td->width * td->height * bpp;
    if (size < face_bytes * slices) return false;   /* host-OOB guard */
    /* 256-aligned per-slice staging offsets satisfy the macOS blit
     * destinationOffset alignment for every format/slice count. */
    stride = (face_bytes + 255u) & ~(usize)255u;
    @autoreleasepool {
        id<MTLBuffer> staging =
            [mb->device newBufferWithLength:(NSUInteger)(stride * slices)
                                    options:MTLResourceStorageModeShared];
        id<MTLCommandBuffer> cmd;
        id<MTLBlitCommandEncoder> blit;
        u32 s;
        if (staging == nil) {
            LOG_ERROR("rhi_metal: readback staging allocation failed");
            return false;
        }
        cmd = [mb->queue commandBuffer];
        if (cmd == nil) {
            LOG_ERROR("rhi_metal: readback command buffer allocation failed");
            return false;
        }
        blit = [cmd blitCommandEncoder];
        for (s = 0u; s < slices; ++s) {
            [blit copyFromTexture:td->texture
                      sourceSlice:(NSUInteger)s
                      sourceLevel:0u
                     sourceOrigin:MTLOriginMake(0.0, 0.0, 0.0)
                       sourceSize:MTLSizeMake((NSUInteger)td->width,
                                              (NSUInteger)td->height, 1u)
                         toBuffer:staging
                destinationOffset:(NSUInteger)(stride * s)
           destinationBytesPerRow:(NSUInteger)((usize)td->width * bpp)
          destinationBytesPerImage:(NSUInteger)face_bytes];
        }
        [blit endEncoding];
        if (metal_commit_wait(dev, mb, cmd) != RHI_RESULT_OK) return false;
        {
            const u8 *src = (const u8 *)staging.contents;
            u8 *dst = (u8 *)dst_rgba8;
            for (s = 0u; s < slices; ++s)
                memcpy(dst + face_bytes * s, src + stride * s,
                       (size_t)face_bytes);
        }
        ok = true;
    }
    return ok;
}

void rhi_texture_upload_mip(RHIDevice *dev, RHITexture tex, u32 mip_level, u32 width, u32 height, const void *data, usize size) {
    MetalBackend *mb;
    MetalTexture *td;
    u32 mip_w;
    u32 mip_h;
    u32 bpp;
    if (dev == NULL || data == NULL || size == 0u) return;
    mb = (MetalBackend *)dev->backend_data;
    if (mb == NULL || mb->device_lost_latch) return;
    td = (MetalTexture *)rhi_get_resource_typed(dev, tex, RHI_RES_TEXTURE);
    if (td == NULL || mip_level >= td->mip_levels) return;
    /* R417 parity with VK: the dims must match the actual mip extent and
     * size must cover w*h*bpp bytes (RGBA8 mip streaming is 4B/px). */
    mip_w = td->width >> mip_level;
    if (mip_w == 0u) mip_w = 1u;
    mip_h = td->height >> mip_level;
    if (mip_h == 0u) mip_h = 1u;
    if (width != mip_w || height != mip_h) return;
    bpp = metal_texture_bpp(td->format);
    if (bpp == 0u || size < (usize)width * height * bpp) return;
    (void)metal_texture_upload_region(dev, mb, td, mip_level, 0u, width,
                                      height, data, size);
}

RHISampler rhi_sampler_create(RHIDevice *dev, const RHISamplerDesc *desc) {
    MetalBackend *mb;
    MetalSampler *smp;
    u32 idx;
    if (dev == NULL || desc == NULL) return RHI_HANDLE_NULL;
    mb = (MetalBackend *)dev->backend_data;
    if (mb == NULL || mb->device_lost_latch) return RHI_HANDLE_NULL;
    /* Enum-range fail-closed: garbage filter/wrap values never reach Metal. */
    if (desc->min_filter > RHI_FILTER_LINEAR ||
        desc->mag_filter > RHI_FILTER_LINEAR ||
        desc->wrap_u > RHI_WRAP_CLAMP_TO_EDGE ||
        desc->wrap_v > RHI_WRAP_CLAMP_TO_EDGE ||
        desc->wrap_w > RHI_WRAP_CLAMP_TO_EDGE) {
        LOG_ERROR("rhi_metal: sampler desc out of range");
        return RHI_HANDLE_NULL;
    }
    smp = (MetalSampler *)calloc(1u, sizeof(*smp));
    if (smp == NULL) return RHI_HANDLE_NULL;
    @autoreleasepool {
        MTLSamplerDescriptor *sd = [MTLSamplerDescriptor new];   /* +1, released below */
        sd.minFilter = desc->min_filter == RHI_FILTER_LINEAR
            ? MTLSamplerMinMagFilterLinear : MTLSamplerMinMagFilterNearest;
        sd.magFilter = desc->mag_filter == RHI_FILTER_LINEAR
            ? MTLSamplerMinMagFilterLinear : MTLSamplerMinMagFilterNearest;
        sd.mipFilter = desc->min_filter == RHI_FILTER_LINEAR
            ? MTLSamplerMipFilterLinear : MTLSamplerMipFilterNearest;
        sd.sAddressMode = desc->wrap_u == RHI_WRAP_REPEAT
            ? MTLSamplerAddressModeRepeat : MTLSamplerAddressModeClampToEdge;
        sd.tAddressMode = desc->wrap_v == RHI_WRAP_REPEAT
            ? MTLSamplerAddressModeRepeat : MTLSamplerAddressModeClampToEdge;
        sd.rAddressMode = desc->wrap_w == RHI_WRAP_REPEAT
            ? MTLSamplerAddressModeRepeat : MTLSamplerAddressModeClampToEdge;
        smp->sampler = [[mb->device newSamplerStateWithDescriptor:sd] retain];
        [sd release];
    }
    if (smp->sampler == nil) {
        LOG_ERROR("rhi_metal: newSamplerStateWithDescriptor failed");
        free(smp);
        return RHI_HANDLE_NULL;
    }
    idx = rhi_alloc_slot(dev);
    dev->slots[idx].ptr = smp;
    dev->slots[idx].type = RHI_RES_SAMPLER;
    return rhi_make_handle(idx, dev->slots[idx].generation);
}

void rhi_sampler_destroy(RHIDevice *dev, RHISampler sampler) {
    MetalBackend *mb;
    MetalSampler *smp;
    if (dev == NULL) return;
    mb = (MetalBackend *)dev->backend_data;
    smp = (MetalSampler *)rhi_get_resource_typed(dev, sampler, RHI_RES_SAMPLER);
    if (smp == NULL) return;
    if (mb != NULL) metal_retire_drain(dev, mb);
    [smp->sampler release];
    free(smp);
    rhi_free_slot(dev, sampler);
}

/* Lazily (re)create the drawable-sized D32 screen depth texture. Every RHI
 * render pass carries a D32 depth attachment (VK swapchain-pass parity),
 * and Task 8 pipelines declare depthAttachmentPixelFormat=D32Float — a
 * color-only screen pass would fail Metal validation on the first draw. */
static bool metal_ensure_screen_depth(RHIDevice *dev, MetalBackend *mb) {
    if (mb->screen_depth != nil && mb->screen_depth_w == dev->width &&
        mb->screen_depth_h == dev->height) return true;
    @autoreleasepool {
        MTLTextureDescriptor *d = [MTLTextureDescriptor
            texture2DDescriptorWithPixelFormat:MTLPixelFormatDepth32Float
                                         width:(NSUInteger)dev->width
                                        height:(NSUInteger)dev->height
                                     mipmapped:NO];
        d.usage = metal_texture_usage_for(RHI_FORMAT_D32_FLOAT);
        d.storageMode = MTLStorageModePrivate;
        /* An in-flight frame's encoder retains the old texture, so dropping
         * our reference here cannot dangle the GPU. newTextureWithDescriptor:
         * returns +1 (new* rule) — hold directly. */
        id<MTLTexture> tex = [mb->device newTextureWithDescriptor:d];
        if (tex == nil) {
            LOG_ERROR("rhi_metal: screen depth allocation failed (%ux%u)",
                      (unsigned)dev->width, (unsigned)dev->height);
            return false;
        }
        [mb->screen_depth release];
        mb->screen_depth = tex;
        mb->screen_depth_w = dev->width;
        mb->screen_depth_h = dev->height;
    }
    return true;
}

/* End any open encoder, open `pass`, and pin viewport+scissor to the full
 * target extent (VK bind-parity: every bind sets a non-flipped full-size
 * viewport/scissor). The pass descriptor is consumed synchronously. */
/* Task 9: pending gpu-timer samples land on the freshly opened encoder.
 * Defined with the timer family (needs the complete RHIGPUTimer). */
static void metal_drain_pending_timer_samples(RHICmdBuffer *cmd);

static void metal_open_render_pass(RHICmdBuffer *cmd,
                                   MTLRenderPassDescriptor *pass,
                                   u32 w, u32 h) {
    metal_end_encoders(cmd);   /* one-encoder rule: compute closes too */
    cmd->suspended_kind = METAL_PASS_NONE;   /* a fresh pass replaces any suspension */
    if (!cmd->resuming) metal_replay_clear(cmd);
    cmd->render_encoder =
        [[cmd->cmd renderCommandEncoderWithDescriptor:pass] retain];
    if (cmd->render_encoder == nil) {
        LOG_ERROR("rhi_metal: renderCommandEncoderWithDescriptor failed");
        return;
    }
    cmd->render_pass_open = true;
    cmd->pass_color_format = pass.colorAttachments[0].texture != nil
        ? pass.colorAttachments[0].texture.pixelFormat
        : MTLPixelFormatInvalid;
    {
        MTLViewport vp = { 0.0, 0.0, (double)w, (double)h, 0.0, 1.0 };
        MTLScissorRect sc = { 0u, 0u, w, h };
        [cmd->render_encoder setViewport:vp];
        [cmd->render_encoder setScissorRect:sc];
    }
    metal_drain_pending_timer_samples(cmd);
}

/* Offscreen/MRT targets follow the VK/GL/D3D12 memory convention: NDC y=-1
 * lands in texture row 0, so every post pass that samples with
 * uv = ndc * 0.5 + 0.5 reads the image the right way up. Metal's default
 * viewport stores NDC y=+1 in row 0, so offscreen passes use the flipped
 * (negative-height) viewport; the drawable keeps the default. */
static void metal_set_offscreen_viewport(RHICmdBuffer *cmd, u32 w, u32 h) {
    MTLViewport vp = { 0.0, (double)h, (double)w, -(double)h, 0.0, 1.0 };
    [cmd->render_encoder setViewport:vp];
}

/* Screen (drawable) pass. clear_pending decides color Load vs Clear with
 * cmd->clear_color; depth clears to 1.0 unless depth_load (the
 * clear_color reopen path preserves depth — VK vkCmdClearAttachments
 * clears color only). Call inside an autorelease pool. */
static void metal_open_screen_pass(RHICmdBuffer *cmd, u32 w, u32 h,
                                   bool depth_load) {
    MetalBackend *mb = cmd->backend;
    RHIDevice *dev = g_current_device;
    MTLRenderPassDescriptor *pass;
    if (!metal_ensure_screen_depth(dev, mb)) return;
    pass = [MTLRenderPassDescriptor renderPassDescriptor];
    pass.colorAttachments[0].texture = mb->drawable.texture;
    pass.colorAttachments[0].storeAction = MTLStoreActionStore;
    if (cmd->clear_pending) {
        pass.colorAttachments[0].loadAction = MTLLoadActionClear;
        pass.colorAttachments[0].clearColor =
            MTLClearColorMake((double)cmd->clear_color[0],
                              (double)cmd->clear_color[1],
                              (double)cmd->clear_color[2],
                              (double)cmd->clear_color[3]);
        cmd->clear_pending = false;
    } else {
        pass.colorAttachments[0].loadAction = MTLLoadActionLoad;
    }
    pass.depthAttachment.texture = mb->screen_depth;
    pass.depthAttachment.loadAction =
        depth_load ? MTLLoadActionLoad : MTLLoadActionClear;
    pass.depthAttachment.clearDepth = 1.0;
    pass.depthAttachment.storeAction = MTLStoreActionStore;
    metal_open_render_pass(cmd, pass, w, h);
    if (cmd->render_pass_open) {
        cmd->pass_kind = METAL_PASS_SCREEN;
        cmd->pass_w = w;
        cmd->pass_h = h;
    }
}

void rhi_cmd_begin_render_pass(RHICmdBuffer *cmd) {
    if (cmd == NULL || cmd->backend == NULL) return;
    MetalBackend *mb = cmd->backend;
    /* VK parity (rhi_vk.c:6166): already-open is a silent no-op — since
     * Task 13 frame_begin auto-opens the screen pass, explicit
     * begin_render_pass callers just continue on the open pass. */
    if (cmd->render_pass_open) return;
    if (cmd->cmd == nil || mb->drawable == nil) {
        /* Fail closed: no frame in flight (or no drawable) — nothing to
         * encode into. */
        LOG_ERROR("rhi_metal: begin_render_pass outside a live frame");
        return;
    }
    /* Descriptor/encoder factory methods are autoreleased; scope a pool for
     * C callers. The encoder itself is retained and survives the drain. */
    @autoreleasepool {
        metal_open_screen_pass(cmd, g_current_device->width,
                               g_current_device->height, false);
    }
}

void rhi_cmd_end_render_pass(RHICmdBuffer *cmd) {
    if (cmd == NULL) return;
    metal_end_render_encoder(cmd);
}

/* Task 9: lazily open the frame's compute encoder (one-encoder rule: an
 * open render pass closes first — and is recorded as suspended so the next
 * graphics call resumes it, VK vk_suspend_pass_for_compute parity). */
static id<MTLComputeCommandEncoder> metal_ensure_compute_encoder(RHICmdBuffer *cmd) {
    if (cmd->compute_encoder != nil) return cmd->compute_encoder;
    if (cmd->cmd == nil) {
        LOG_ERROR("rhi_metal: compute encoder requested outside a live frame");
        return nil;
    }
    if (cmd->render_pass_open && cmd->suspended_kind == METAL_PASS_NONE) {
        cmd->suspended_kind = cmd->pass_kind;
        cmd->suspended_target = cmd->pass_target;
        cmd->suspended_w = cmd->pass_w;
        cmd->suspended_h = cmd->pass_h;
        cmd->suspended_face = cmd->pass_face;
        cmd->suspended_pipeline = cmd->bound_pipeline;
    }
    metal_end_render_encoder(cmd);
    /* computeCommandEncoder is autoreleased; retain to the frame end. */
    cmd->compute_encoder = [[cmd->cmd computeCommandEncoder] retain];
    if (cmd->compute_encoder == nil)
        LOG_ERROR("rhi_metal: computeCommandEncoder failed");
    return cmd->compute_encoder;
}

/* Returns the render pipeline state matching the open pass's color0
 * format, building and caching a variant from pp->proto when the engine
 * pipeline was declared against a different format (see MetalPipeline). */
static id<MTLRenderPipelineState> metal_pipeline_state_for_pass(
    MetalPipeline *pp, MetalBackend *mb, MTLPixelFormat pass_fmt) {
    u32 vi;
    MTLRenderPipelineDescriptor *vd;
    id<MTLRenderPipelineState> st;
    NSError *err = nil;
    if (pp->proto == nil || pass_fmt == MTLPixelFormatInvalid ||
        pass_fmt == pp->declared_color_fmt)
        return pp->pipeline;
    for (vi = 0u; vi < pp->variant_count; ++vi) {
        if (pp->variants[vi].fmt == pass_fmt)
            return pp->variants[vi].state;
    }
    if (pp->variant_count >= 4u) {
        LOG_ERROR("rhi_metal: pixelFormat variant cache full (declared %lu, pass %lu)",
                  (unsigned long)pp->declared_color_fmt, (unsigned long)pass_fmt);
        return pp->pipeline;
    }
    vd = [pp->proto copy];   /* +1, released below */
    vd.colorAttachments[0].pixelFormat = pass_fmt;
    /* newRenderPipelineStateWithDescriptor: returns +1 (new* rule). */
    st = [mb->device newRenderPipelineStateWithDescriptor:vd error:&err];
    [vd release];
    if (st == nil) {
        LOG_ERROR("rhi_metal: pixelFormat variant build failed: %s",
                  err != nil ? [[err localizedDescription] UTF8String]
                             : "(no error info)");
        return pp->pipeline;
    }
    pp->variants[pp->variant_count].fmt = pass_fmt;
    pp->variants[pp->variant_count].state = st;
    pp->variant_count++;
    return st;
}

void rhi_cmd_bind_pipeline(RHICmdBuffer *cmd, RHIPipeline pipe) {
    MetalPipeline *pp;
    if (cmd == NULL || cmd->backend == NULL) return;
    pp = (MetalPipeline *)rhi_get_resource_typed(g_current_device, pipe,
                                                 RHI_RES_PIPELINE);
    if (pp == NULL) return;
    if (pp->is_compute) {
        id<MTLComputeCommandEncoder> enc = metal_ensure_compute_encoder(cmd);
        if (enc == nil) return;
        [enc setComputePipelineState:pp->compute];
        cmd->bound_pipeline = pipe;
        return;
    }
    metal_resume_render_pass_if_needed(cmd);
    if (!cmd->render_pass_open || cmd->render_encoder == nil) {
        LOG_ERROR("rhi_metal: bind_pipeline without an open render pass (suspended=%d)",
                  (int)cmd->suspended_kind);
        return;
    }
    metal_apply_render_pipeline(cmd, pp, pipe);
}

static void metal_apply_render_pipeline(RHICmdBuffer *cmd, MetalPipeline *pp,
                                        RHIPipeline pipe) {
    [cmd->render_encoder setRenderPipelineState:
        metal_pipeline_state_for_pass(pp, cmd->backend, cmd->pass_color_format)];
    /* Unconditional: the depth-stencil state is sticky encoder state, so
     * skipping the set for a depth-off pipeline would leave a stale state
     * in force (review fix C2). pp->depth_state is always non-nil. */
    [cmd->render_encoder setDepthStencilState:pp->depth_state];
    /* Metal rasterizer state lives on the encoder, not the PSO (VK PSO
     * parity): winding is always Clockwise (VK frontFace parity). */
    [cmd->render_encoder setFrontFacingWinding:MTLWindingClockwise];
    [cmd->render_encoder setCullMode:pp->cull_none ? MTLCullModeNone
                                                   : MTLCullModeBack];
    [cmd->render_encoder setTriangleFillMode:pp->wireframe
        ? MTLTriangleFillModeLines : MTLTriangleFillModeFill];
    cmd->bound_pipeline = pipe;
}

void rhi_cmd_bind_vertex_buffer(RHICmdBuffer *cmd, RHIBuffer buf, usize offset) {
    MetalBuffer *bb;
    if (cmd == NULL) return;
    metal_resume_render_pass_if_needed(cmd);
    if (cmd->render_encoder == nil) return;
    bb = (MetalBuffer *)rhi_get_resource_typed(g_current_device, buf,
                                               RHI_RES_BUFFER);
    if (bb == NULL) return;
    /* The Task 8 vertex-layout table binds every attribute to
     * layouts[0].bufferIndex 0 (VK single-binding parity). */
    [cmd->render_encoder setVertexBuffer:bb->buffer
                                  offset:(NSUInteger)offset
                                 atIndex:0u];
    [bb->buffer retain];
    [cmd->vtx_buf release];
    cmd->vtx_buf = bb->buffer;
    cmd->vtx_off = (NSUInteger)offset;
}

void rhi_cmd_bind_index_buffer(RHICmdBuffer *cmd, RHIBuffer buf, usize offset, bool is_u32) {
    MetalBuffer *bb;
    if (cmd == NULL || cmd->backend == NULL) return;
    bb = (MetalBuffer *)rhi_get_resource_typed(g_current_device, buf,
                                               RHI_RES_BUFFER);
    if (bb == NULL) return;
    /* Recorded, not encoded: Metal applies the index buffer at draw time. */
    cmd->index_buffer = buf;
    cmd->index_offset = offset;
    cmd->index_u32 = is_u32;
}

void rhi_cmd_set_viewport(RHICmdBuffer *cmd, f32 x, f32 y, f32 w, f32 h, f32 min_depth, f32 max_depth) {
    if (cmd == NULL || cmd->render_encoder == nil) return;
    /* The RHI's +Y-up viewport follows the target's own convention, like
     * rhi_vk.c: offscreen/MRT targets keep NDC y=-1 in memory row 0 (the
     * flipped viewport metal_set_offscreen_viewport installs at bind), the
     * drawable and the depth-only shadow targets keep Metal's default. */
    MTLViewport vp = { (double)x, (double)y, (double)w, (double)h,
                       (double)min_depth, (double)max_depth };
    if (cmd->pass_kind == METAL_PASS_OFFSCREEN ||
        cmd->pass_kind == METAL_PASS_MRT) {
        vp.originY = (double)y + (double)h;
        vp.height = -(double)h;
    }
    [cmd->render_encoder setViewport:vp];
}

void rhi_cmd_set_scissor(RHICmdBuffer *cmd, i32 x, i32 y, u32 w, u32 h) {
    if (cmd == NULL || cmd->render_encoder == nil) return;
    /* Metal scissor is unsigned and clipped to the render target; negative
     * origins clamp (VK allows signed offsets). */
    MTLScissorRect sc = {
        (NSUInteger)(x < 0 ? 0 : x),
        (NSUInteger)(y < 0 ? 0 : y),
        (NSUInteger)w,
        (NSUInteger)h
    };
    [cmd->render_encoder setScissorRect:sc];
}

void rhi_cmd_set_scissor_top_left(RHICmdBuffer *cmd, u32 x, u32 y, u32 w, u32 h) {
    if (cmd == NULL || cmd->render_encoder == nil) return;
    /* Top-left origin, matching Metal's scissor convention directly. */
    MTLScissorRect sc = { (NSUInteger)x, (NSUInteger)y,
                          (NSUInteger)w, (NSUInteger)h };
    [cmd->render_encoder setScissorRect:sc];
}

void rhi_cmd_set_shadow_viewport(RHICmdBuffer *cmd, u32 x, u32 y, u32 w, u32 h) {
    if (cmd == NULL || cmd->backend == NULL) return;
    metal_resume_render_pass_if_needed(cmd);
    if (cmd->render_encoder == nil) return;
    /* Shadow atlas quadrants use top-left pixel coordinates and the full
     * 0..1 depth range; each cascade must not overwrite its neighbours. */
    rhi_cmd_set_viewport(cmd, (f32)x, (f32)y, (f32)w, (f32)h, 0.0f, 1.0f);
    rhi_cmd_set_scissor_top_left(cmd, x, y, w, h);
}

/* Shared draw guards: open render pass + bound graphics pipeline; returns
 * the payload (NULL after logging on failure). */
static void metal_flush_push(RHICmdBuffer *cmd, const MetalPipeline *pp);
static void metal_flush_texel(RHICmdBuffer *cmd, const MetalPipeline *pp);
static void metal_apply_texel_views(RHICmdBuffer *cmd, const MetalBuffer *b0,
                                    const MetalBuffer *b1);

static MetalPipeline *metal_draw_ready(RHICmdBuffer *cmd, const char *what) {
    MetalPipeline *pp;
    metal_resume_render_pass_if_needed(cmd);
    if (cmd == NULL || cmd->render_encoder == nil || !cmd->render_pass_open) {
        LOG_ERROR("rhi_metal: %s without an open render pass", what);
        return NULL;
    }
    pp = (MetalPipeline *)rhi_get_resource_typed(g_current_device,
                                                 cmd->bound_pipeline,
                                                 RHI_RES_PIPELINE);
    if (pp == NULL || pp->is_compute) {
        LOG_ERROR("rhi_metal: %s without a bound graphics pipeline", what);
        return NULL;
    }
    return pp;
}

static MTLPrimitiveType metal_pipeline_prim(const MetalPipeline *pp) {
    return pp->point_list ? MTLPrimitiveTypePoint : MTLPrimitiveTypeTriangle;
}

void rhi_cmd_draw(RHICmdBuffer *cmd, u32 vertex_count, u32 instance_count) {
    MetalPipeline *pp;
    if (vertex_count == 0u || instance_count == 0u) return;   /* VK no-op parity */
    pp = metal_draw_ready(cmd, "draw");
    if (pp == NULL) return;
    metal_flush_push(cmd, pp);
    [cmd->render_encoder drawPrimitives:metal_pipeline_prim(pp)
                            vertexStart:0u
                            vertexCount:(NSUInteger)vertex_count
                          instanceCount:(NSUInteger)instance_count];
}

void rhi_cmd_draw_base(RHICmdBuffer *cmd, u32 vertex_count, u32 instance_count, u32 first_vertex) {
    MetalPipeline *pp;
    if (vertex_count == 0u || instance_count == 0u) return;
    pp = metal_draw_ready(cmd, "draw_base");
    if (pp == NULL) return;
    metal_flush_push(cmd, pp);
    [cmd->render_encoder drawPrimitives:metal_pipeline_prim(pp)
                            vertexStart:(NSUInteger)first_vertex
                            vertexCount:(NSUInteger)vertex_count
                          instanceCount:(NSUInteger)instance_count];
}

void rhi_cmd_draw_indexed(RHICmdBuffer *cmd, u32 index_count, u32 instance_count) {
    MetalPipeline *pp;
    MetalBuffer *ib;
    if (index_count == 0u || instance_count == 0u) return;
    pp = metal_draw_ready(cmd, "draw_indexed");
    if (pp == NULL) return;
    ib = (MetalBuffer *)rhi_get_resource_typed(g_current_device,
                                               cmd->index_buffer,
                                               RHI_RES_BUFFER);
    if (ib == NULL) {
        LOG_ERROR("rhi_metal: draw_indexed without a bound index buffer");
        return;
    }
    metal_flush_push(cmd, pp);
    [cmd->render_encoder drawIndexedPrimitives:metal_pipeline_prim(pp)
                                    indexCount:(NSUInteger)index_count
                                     indexType:(cmd->index_u32 ? MTLIndexTypeUInt32
                                                               : MTLIndexTypeUInt16)
                                   indexBuffer:ib->buffer
                             indexBufferOffset:(NSUInteger)cmd->index_offset
                                 instanceCount:(NSUInteger)instance_count];
}

void rhi_cmd_draw_indexed_instanced_base(RHICmdBuffer *cmd, u32 index_count, u32 instance_count, u32 first_index, i32 vertex_offset, u32 first_instance) {
    /* vkCmdDrawIndexed parity: firstIndex becomes a byte offset past the
     * bound index-buffer offset; vertexOffset/firstInstance map to Metal's
     * baseVertex/baseInstance. */
    MetalPipeline *pp;
    MetalBuffer *ib;
    if (index_count == 0u || instance_count == 0u) return;
    pp = metal_draw_ready(cmd, "draw_indexed_base");
    if (pp == NULL) return;
    ib = (MetalBuffer *)rhi_get_resource_typed(g_current_device,
                                               cmd->index_buffer,
                                               RHI_RES_BUFFER);
    if (ib == NULL) {
        LOG_ERROR("rhi_metal: draw_indexed_base without a bound index buffer");
        return;
    }
    metal_flush_push(cmd, pp);
    [cmd->render_encoder drawIndexedPrimitives:metal_pipeline_prim(pp)
                                    indexCount:(NSUInteger)index_count
                                     indexType:(cmd->index_u32 ? MTLIndexTypeUInt32
                                                               : MTLIndexTypeUInt16)
                                   indexBuffer:ib->buffer
                             indexBufferOffset:(NSUInteger)cmd->index_offset +
                                               (NSUInteger)first_index *
                                                   (cmd->index_u32 ? 4u : 2u)
                                 instanceCount:(NSUInteger)instance_count
                                    baseVertex:(NSInteger)vertex_offset
                                  baseInstance:(NSUInteger)first_instance];
}

void rhi_cmd_draw_indexed_base(RHICmdBuffer *cmd, u32 index_count, u32 instance_count, u32 first_index, i32 vertex_offset) {
    rhi_cmd_draw_indexed_instanced_base(cmd, index_count, instance_count,
                                        first_index, vertex_offset, 0u);
}

/* Indirect arg ABIs are layout-identical between VK and Metal:
 * non-indexed {vertexCount, instanceCount, vertexStart, baseInstance} = 16B;
 * indexed {indexCount, instanceCount, firstIndex, vertexOffset(i32),
 * firstInstance} = 20B. Metal has no multi-draw indirect with a count
 * bound, so draw_count>1 loops single-command indirect draws. */
_Static_assert(sizeof(MTLDrawPrimitivesIndirectArguments) == 16u,
               "draw indirect arg ABI drift");
_Static_assert(sizeof(MTLDrawIndexedPrimitivesIndirectArguments) == 20u,
               "indexed indirect arg ABI drift");
_Static_assert(sizeof(RHIIndexedIndirectCommand) == 20u,
               "RHI indexed indirect ABI must match the Metal record");
void rhi_cmd_draw_indirect(RHIDevice *dev, RHIBuffer cmd_buf, u32 offset, u32 draw_count, u32 stride) {
    MetalBackend *mb;
    RHICmdBuffer *cmd;
    MetalPipeline *pp;
    MetalBuffer *ab;
    u32 i;
    if (dev == NULL) return;
    mb = (MetalBackend *)dev->backend_data;
    if (mb == NULL) return;
    cmd = mb->frame_cmd;
    if (draw_count == 0u || stride < 16u || (stride % 4u) != 0u ||
        (offset & 3u) != 0u) {
        LOG_ERROR("rhi_metal: draw_indirect bad args (count %u stride %u offset %u)",
                  (unsigned)draw_count, (unsigned)stride, (unsigned)offset);
        return;
    }
    ab = (MetalBuffer *)rhi_get_resource_typed(dev, cmd_buf, RHI_RES_BUFFER);
    pp = cmd != NULL ? metal_draw_ready(cmd, "draw_indirect") : NULL;
    if (ab == NULL || pp == NULL) return;
    if ((usize)offset + (usize)(draw_count - 1u) * stride + 16u > ab->size) {
        LOG_ERROR("rhi_metal: draw_indirect range overruns the arg buffer");
        return;
    }
    metal_flush_push(cmd, pp);
    for (i = 0u; i < draw_count; ++i) {
        [cmd->render_encoder drawPrimitives:metal_pipeline_prim(pp)
                             indirectBuffer:ab->buffer
                       indirectBufferOffset:(NSUInteger)(offset + i * stride)];
    }
}

void rhi_cmd_draw_indexed_indirect(RHIDevice *dev, RHIBuffer cmd_buf, u32 offset, u32 draw_count, u32 stride) {
    MetalBackend *mb;
    RHICmdBuffer *cmd;
    MetalPipeline *pp;
    MetalBuffer *ab;
    MetalBuffer *ib;
    u32 i;
    if (dev == NULL) return;
    mb = (MetalBackend *)dev->backend_data;
    if (mb == NULL) return;
    cmd = mb->frame_cmd;
    if (draw_count == 0u || stride < 20u || (stride % 4u) != 0u ||
        (offset & 3u) != 0u) {
        LOG_ERROR("rhi_metal: draw_indexed_indirect bad args (count %u stride %u offset %u)",
                  (unsigned)draw_count, (unsigned)stride, (unsigned)offset);
        return;
    }
    ab = (MetalBuffer *)rhi_get_resource_typed(dev, cmd_buf, RHI_RES_BUFFER);
    pp = cmd != NULL ? metal_draw_ready(cmd, "draw_indexed_indirect") : NULL;
    ib = cmd != NULL
        ? (MetalBuffer *)rhi_get_resource_typed(dev, cmd->index_buffer,
                                                RHI_RES_BUFFER)
        : NULL;
    if (ab == NULL || pp == NULL || ib == NULL) {
        if (ib == NULL)
            LOG_ERROR("rhi_metal: draw_indexed_indirect without an index buffer");
        return;
    }
    if ((usize)offset + (usize)(draw_count - 1u) * stride + 20u > ab->size) {
        LOG_ERROR("rhi_metal: draw_indexed_indirect range overruns the arg buffer");
        return;
    }
    metal_flush_push(cmd, pp);
    for (i = 0u; i < draw_count; ++i) {
        [cmd->render_encoder
            drawIndexedPrimitives:metal_pipeline_prim(pp)
                        indexType:(cmd->index_u32 ? MTLIndexTypeUInt32
                                                  : MTLIndexTypeUInt16)
                      indexBuffer:ib->buffer
                indexBufferOffset:(NSUInteger)cmd->index_offset
                   indirectBuffer:ab->buffer
             indirectBufferOffset:(NSUInteger)(offset + i * stride)];
    }
}

void rhi_cmd_draw_indexed_indirect_count(RHIDevice *dev, RHIBuffer cmd_buf, u32 cmd_offset, RHIBuffer count_buf, u32 count_offset, u32 max_draws, u32 stride) {
    /* Fail closed: Metal has no draw-indirect-with-count equivalent
     * (MTLIndirectCommandBuffer is a separate encoding model, out of plan
     * scope). Recorded in docs/rhi_metal_d3d12_feature_matrix.md. */
    LOG_ERROR("rhi_metal: rhi_cmd_draw_indexed_indirect_count has no Metal equivalent");
    (void)dev;
    (void)cmd_buf;
    (void)cmd_offset;
    (void)count_buf;
    (void)count_offset;
    (void)max_draws;
    (void)stride;
}

/* In-pass clear_color reopen helpers (review fix C1), defined with their
 * payload types in the FBO/MRT/shadow sections below. */
static void metal_offscreen_clear_reopen(RHICmdBuffer *cmd, RHIHandle fb,
                                         u32 w, u32 h, const f32 *rgba);
static void metal_mrt_clear_reopen(RHICmdBuffer *cmd, RHIHandle fb,
                                   u32 w, u32 h, const f32 *rgba);
static void metal_mrt_attachment_clear_reopen(RHICmdBuffer *cmd, RHIHandle fb,
                                   u32 w, u32 h, u32 attachment, const f32 *rgba);
static void metal_offscreen_depth_clear_reopen(RHICmdBuffer *cmd, RHIHandle fb,
                                               u32 w, u32 h);
static void metal_mrt_depth_clear_reopen(RHICmdBuffer *cmd, RHIHandle fb,
                                         u32 w, u32 h);
static void metal_depth_target_clear_reopen(RHICmdBuffer *cmd, u8 kind,
                                            RHIHandle fb, u32 w, u32 h,
                                            u32 face);

void rhi_cmd_clear_color(RHICmdBuffer *cmd, f32 r, f32 g, f32 b, f32 a) {
    u8 kind;
    RHIHandle target;
    u32 w, h, face;
    if (cmd == NULL) return;
    cmd->clear_color[0] = r;
    cmd->clear_color[1] = g;
    cmd->clear_color[2] = b;
    cmd->clear_color[3] = a;
    if (!cmd->render_pass_open) {
        /* Outside a pass: the next begin_render_pass opens with
         * loadAction=Clear and this color. */
        cmd->clear_pending = true;
        return;
    }
    /* Inside a pass (review fix C1): Metal clears are render-pass load
     * actions, so flush the current encoder (its recorded work stays in the
     * command buffer) and reopen a Clear pass on the SAME target — VK's
     * vkCmdClearAttachments clears the current target in place
     * (rhi_vk.c:7063-7081); the engine's only in-pass sequence is bind ->
     * clear_color immediately (main.c:6506-6507), where a reopen with Clear
     * is equivalent. Depth is preserved (Load), matching VK clearing color
     * attachment 0 only. */
    kind = cmd->pass_kind;
    target = cmd->pass_target;
    w = cmd->pass_w;
    h = cmd->pass_h;
    face = cmd->pass_face;
    metal_end_render_encoder(cmd);
    @autoreleasepool {
        switch (kind) {
        case METAL_PASS_SCREEN:
            cmd->clear_pending = true;
            metal_open_screen_pass(cmd, w, h, true /* depth Load */);
            break;
        case METAL_PASS_OFFSCREEN:
            metal_offscreen_clear_reopen(cmd, target, w, h, cmd->clear_color);
            break;
        case METAL_PASS_MRT:
            metal_mrt_clear_reopen(cmd, target, w, h, cmd->clear_color);
            break;
        case METAL_PASS_SHADOW:
        case METAL_PASS_CUBE_DEPTH:
            /* Depth-only target: a color clear does not apply (VK would be
             * an invalid attachment index); reopen the depth clear. */
            metal_depth_target_clear_reopen(cmd, kind, target, w, h, face);
            break;
        default:
            /* No recorded target (unreachable on healthy paths): fail closed
             * onto the screen pass so later draws still have a target. */
            LOG_ERROR("rhi_metal: clear_color in a pass of unknown target");
            cmd->clear_pending = true;
            if (cmd->cmd != nil && cmd->backend != NULL &&
                cmd->backend->drawable != nil) {
                metal_open_screen_pass(cmd, w, h, false);
            }
            break;
        }
    }
}

void rhi_cmd_clear_color_attachment(RHICmdBuffer *cmd, u32 attachment, f32 r, f32 g, f32 b, f32 a) {
    f32 rgba[4];
    RHIHandle target;
    u32 w, h;
    if (cmd == NULL || cmd->backend == NULL || attachment >= RHI_MRT_MAX_ATTACHMENTS)
        return;
    if (attachment == 0u) {
        rhi_cmd_clear_color(cmd, r, g, b, a);
        return;
    }
    metal_resume_render_pass_if_needed(cmd);
    if (!cmd->render_pass_open || cmd->pass_kind != METAL_PASS_MRT) return;
    target = cmd->pass_target;
    w = cmd->pass_w;
    h = cmd->pass_h;
    rgba[0] = r; rgba[1] = g; rgba[2] = b; rgba[3] = a;
    metal_end_render_encoder(cmd);
    metal_mrt_attachment_clear_reopen(cmd, target, w, h, attachment, rgba);
}

void rhi_cmd_bind_texture(RHICmdBuffer *cmd, RHITexture tex, RHISampler sampler, u32 unit) {
    MetalTexture *td;
    MetalSampler *sd;
    if (cmd == NULL) return;
    metal_resume_render_pass_if_needed(cmd);
    if (cmd->render_encoder == nil) return;
    td = (MetalTexture *)rhi_get_resource_typed(g_current_device, tex,
                                                RHI_RES_TEXTURE);
    sd = (MetalSampler *)rhi_get_resource_typed(g_current_device, sampler,
                                                RHI_RES_SAMPLER);
    if (td == NULL || sd == NULL) return;
    /* Graphics material set = set 0; combined samplers flatten to
     * texture(unit)+sampler(unit) (Task 10 contract). */
    metal_set_frag_texture(cmd, td->texture, (NSUInteger)unit);
    metal_set_frag_sampler(cmd, sd->sampler, (NSUInteger)unit);
}

void rhi_cmd_bind_shadow_texture(RHICmdBuffer *cmd, RHITexture shadow_tex, RHISampler sampler) {
    LOG_ERROR("rhi_metal: rhi_cmd_bind_shadow_texture not implemented");
    (void)cmd;
    (void)shadow_tex;
    (void)sampler;
}

void rhi_cmd_bind_uniform_buffer(RHICmdBuffer *cmd, RHIBuffer buf, u32 binding) {
    if (cmd == NULL || cmd->backend == NULL) return;
    /* VK parity (rhi_vk.c:8064-8074 records vk->bound_ubo only): defer the
     * actual set*Buffer to draw/dispatch time — encoder state does not
     * survive pass switches (blit interlude / clear_color reopen), so an
     * immediate write could be lost (review fix I2). The replay index is
     * computed at flush from the bound pipeline (metal_flush_push). VK
     * descriptor sets additionally stay bound across pipelines with
     * compatible layouts, so the flush re-applies the recorded UBO at EVERY
     * draw/dispatch (computed from THAT pipeline's ubo_set) rather than
     * only when a dirty flag survived — a first draw with a different
     * ubo_set must not consume the bind (terrain crash, Task 15). */
    if (rhi_get_resource_typed(g_current_device, buf, RHI_RES_BUFFER) == NULL)
        return;
    cmd->bound_ubo = buf;
    cmd->bound_ubo_binding = binding;
}

/* ---- Task 11: push-constant staging ----
 * 256B per-cmd staging (RHI_METAL_MAX_PUSH_BYTES; VK's 128B compute range
 * is preserved). Writes validate against the bound pipeline's range and
 * drop with LOG_WARN on overflow (rhi.h:573-580); the flush happens at
 * draw/dispatch via set*Bytes:atIndex:29 (the Task 10 reserved push slot). */
static u32 metal_push_range_for(const MetalPipeline *pp) {
    return pp->is_compute ? 128u : RHI_METAL_MAX_PUSH_BYTES;
}

/* Replays the deferred UBO bind (I2). Index formula (VK pipeline-layout
 * position parity, rhi_vk.c pipeline create): graphics ubo_set =
 * (uses_textures + uses_texel_buffer + uses_storage), compute = 3; MSL
 * index = set*8+binding (Task 10 flattening contract). */
static void metal_flush_ubo(RHICmdBuffer *cmd, const MetalPipeline *pp) {
    MetalBuffer *bb;
    u32 set, index;
    if (!rhi_handle_valid(cmd->bound_ubo)) return;
    bb = (MetalBuffer *)rhi_get_resource_typed(g_current_device,
                                               cmd->bound_ubo,
                                               RHI_RES_BUFFER);
    if (bb == NULL) return;
    if (pp->is_compute) {
        set = 3u;
        index = set * 8u + cmd->bound_ubo_binding;
        if (cmd->compute_encoder != nil) {
            [cmd->compute_encoder setBuffer:bb->buffer
                                     offset:0u
                                    atIndex:(NSUInteger)index];
        }
    } else if (cmd->render_encoder != nil) {
        set = (pp->desc.uses_textures ? 1u : 0u) +
              (pp->desc.uses_texel_buffer ? 1u : 0u) +
              (pp->desc.uses_storage ? 1u : 0u);
        index = set * 8u + cmd->bound_ubo_binding;
        /* The flattened index is stage-agnostic; bind both stages so the
         * UBO resolves wherever the shader declares it (VK
         * single-descriptor-set parity). */
        [cmd->render_encoder setVertexBuffer:bb->buffer
                                      offset:0u
                                     atIndex:(NSUInteger)index];
        [cmd->render_encoder setFragmentBuffer:bb->buffer
                                        offset:0u
                                       atIndex:(NSUInteger)index];
    }
}

/* Replays recorded storage binds lost to pass switches (I2 rule) and feeds
 * the spvBufferSizeConstants table at buffer(25) from the bound buffers'
 * byte sizes. Graphics replays both stages because the clustered, instanced,
 * skinned and particle variants declare storage in different stages.
 * Fail-closed: a missing or stale binding logs and returns false so the
 * caller can skip the draw or dispatch. */
static bool metal_flush_storage_and_bsc(RHICmdBuffer *cmd,
                                        const MetalPipeline *pp) {
    u32 sizes[RHI_METAL_BSC_MAX];
    u32 i;
    bool need_bsc = pp->bsc_count > 0u;
    const RHIBuffer *table = pp->is_compute ? cmd->bound_storage
                                            : cmd->bound_gfx_storage;
    const u32 mask = pp->is_compute ? cmd->bound_storage_mask
                                    : cmd->bound_gfx_storage_mask;
    if (pp->is_compute) {
        u32 idx;
        if (cmd->compute_encoder == nil) return true;
        for (idx = 0u; idx < 25u; ++idx) {
            MetalBuffer *bb;
            if ((mask & (1u << idx)) == 0u) continue;
            bb = (MetalBuffer *)rhi_get_resource_typed(
                g_current_device, table[idx], RHI_RES_BUFFER);
            if (bb == NULL) continue;
            [cmd->compute_encoder setBuffer:bb->buffer
                                     offset:0u
                                    atIndex:(NSUInteger)idx];
        }
    } else if ((need_bsc || pp->desc.uses_storage) && cmd->render_encoder != nil) {
        /* Replay only this pipeline's own storage set (set*8 .. set*8+7,
         * the rhi_cmd_bind_storage_buffer flattening). Records from another
         * layout (particles bind set 0 -> indices 0/1) would otherwise land
         * on vertex buffer(0) of a textured storage pipeline and replace
         * its mesh VBO — VK's per-layout descriptor sets never alias so. */
        u32 idx;
        u32 base = ((pp->desc.uses_textures ? 1u : 0u) +
                    (pp->desc.uses_texel_buffer ? 1u : 0u)) * 8u;
        u32 end = base + 8u < 25u ? base + 8u : 25u;
        for (idx = base; idx < end; ++idx) {
            MetalBuffer *bb;
            if ((mask & (1u << idx)) == 0u) continue;
            bb = (MetalBuffer *)rhi_get_resource_typed(
                g_current_device, table[idx], RHI_RES_BUFFER);
            if (bb == NULL) continue;
            [cmd->render_encoder setVertexBuffer:bb->buffer
                                          offset:0u
                                         atIndex:(NSUInteger)idx];
            [cmd->render_encoder setFragmentBuffer:bb->buffer
                                            offset:0u
                                           atIndex:(NSUInteger)idx];
        }
    }
    if (!need_bsc) return true;
    for (i = 0u; i < pp->bsc_count; ++i) {
        u32 idx = pp->bsc_buffer_index[i];
        MetalBuffer *bb;
        if ((mask & (1u << idx)) == 0u) {
            LOG_ERROR("rhi_metal: buffer-size constant %u needs a storage "
                      "buffer at index %u — none bound (fail-closed)",
                      (unsigned)i, idx);
            return false;
        }
        bb = (MetalBuffer *)rhi_get_resource_typed(
            g_current_device, table[idx], RHI_RES_BUFFER);
        if (bb == NULL) {
            LOG_ERROR("rhi_metal: buffer-size constant %u: stale storage "
                      "buffer at index %u", (unsigned)i, idx);
            return false;
        }
        if (bb->size > 0xFFFFFFFFull) {
            LOG_ERROR("rhi_metal: buffer-size constant %u: buffer exceeds "
                      "uint32 byte size", (unsigned)i);
            return false;
        }
        sizes[i] = (u32)bb->size;
    }
    if (pp->is_compute) {
        if (cmd->compute_encoder == nil) return false;
        [cmd->compute_encoder setBytes:sizes
                                length:pp->bsc_count * sizeof(u32)
                               atIndex:RHI_METAL_BSC_ARG_INDEX];
    } else {
        if (cmd->render_encoder == nil) return false;
        [cmd->render_encoder setVertexBytes:sizes
                                     length:pp->bsc_count * sizeof(u32)
                                    atIndex:RHI_METAL_BSC_ARG_INDEX];
    }
    return true;
}

static void metal_flush_push(RHICmdBuffer *cmd, const MetalPipeline *pp) {
    if (cmd->push_dirty) {
        if (pp->is_compute) {
            if (cmd->compute_encoder != nil) {
                [cmd->compute_encoder setBytes:cmd->push_staging
                                        length:128u
                                       atIndex:29u];
            }
        } else if (cmd->render_encoder != nil) {
            [cmd->render_encoder setVertexBytes:cmd->push_staging
                                         length:RHI_METAL_MAX_PUSH_BYTES
                                        atIndex:29u];
            [cmd->render_encoder setFragmentBytes:cmd->push_staging
                                           length:RHI_METAL_MAX_PUSH_BYTES
                                          atIndex:29u];
        }
        cmd->push_dirty = false;
    }
    metal_flush_ubo(cmd, pp);
    if (!pp->is_compute) metal_flush_texel(cmd, pp);
    (void)metal_flush_storage_and_bsc(cmd, pp);
}

/* Stage a small uniform write (set_uniform_* helpers): negative locations
 * drop silently (unknown name at the call site), range overflow drops with
 * LOG_WARN — the VK VK_PUSH_HELPER_CHECK semantics. */
static void metal_push_stage(RHICmdBuffer *cmd, i32 location,
                             const void *data, u32 size) {
    MetalPipeline *pp;
    u32 range;
    if (cmd == NULL || cmd->backend == NULL || data == NULL || location < 0)
        return;
    pp = (MetalPipeline *)rhi_get_resource_typed(g_current_device,
                                                 cmd->bound_pipeline,
                                                 RHI_RES_PIPELINE);
    if (pp == NULL) return;
    range = metal_push_range_for(pp);
    if (!rhi_push_helper_range_ok(location, size, range)) {
        LOG_WARN("rhi_metal: set_uniform offset %d+%u exceeds push range %u — dropped",
                 location, (unsigned)size, (unsigned)range);
        return;
    }
    memcpy(cmd->push_staging + location, data, (size_t)size);
    cmd->push_dirty = true;
    cmd->push_staged = true;
}

void rhi_cmd_set_uniform_mat4(RHICmdBuffer *cmd, i32 location, const f32 *m) {
    metal_push_stage(cmd, location, m, 64u);
}

void rhi_cmd_set_uniform_vec3(RHICmdBuffer *cmd, i32 location, f32 x, f32 y, f32 z) {
    f32 v[3];
    v[0] = x; v[1] = y; v[2] = z;
    metal_push_stage(cmd, location, v, 12u);
}

void rhi_cmd_set_uniform_vec2(RHICmdBuffer *cmd, i32 location, f32 x, f32 y) {
    f32 v[2];
    v[0] = x; v[1] = y;
    metal_push_stage(cmd, location, v, 8u);
}

void rhi_cmd_set_uniform_vec4(RHICmdBuffer *cmd, i32 location, f32 x, f32 y, f32 z, f32 w) {
    f32 v[4];
    v[0] = x; v[1] = y; v[2] = z; v[3] = w;
    metal_push_stage(cmd, location, v, 16u);
}

void rhi_cmd_set_uniform_f32(RHICmdBuffer *cmd, i32 location, f32 v) {
    metal_push_stage(cmd, location, &v, 4u);
}

void rhi_cmd_set_uniform_i32(RHICmdBuffer *cmd, i32 location, i32 v) {
    metal_push_stage(cmd, location, &v, 4u);
}

/* R444: Push-constant upload, semantics aligned with vkCmdPushConstants
 * (offset, size): validated against the bound pipeline's declared range;
 * out-of-range writes drop with a warning instead of truncating at flush. */
void rhi_cmd_push_constants(RHICmdBuffer *cmd, u32 offset, const void *data, u32 size) {
    MetalPipeline *pp;
    u32 range;
    if (cmd == NULL || cmd->backend == NULL || data == NULL || size == 0u)
        return;
    pp = (MetalPipeline *)rhi_get_resource_typed(g_current_device,
                                                 cmd->bound_pipeline,
                                                 RHI_RES_PIPELINE);
    if (pp == NULL) return;
    range = metal_push_range_for(pp);
    if (!rhi_push_range_fits(offset, size, range)) {
        LOG_WARN("rhi_metal: push constants [%u, +%u) exceed declared range %u — dropped",
                 (unsigned)offset, (unsigned)size, (unsigned)range);
        return;
    }
    memcpy(cmd->push_staging + offset, data, (size_t)size);
    cmd->push_dirty = true;
    cmd->push_staged = true;
}

/* R179/R444: deprecated alias of rhi_cmd_push_constants (location == byte offset). */
void rhi_cmd_set_uniform_bytes(RHICmdBuffer *cmd, i32 location, const void *data, u32 size) {
    if (location < 0) return;
    rhi_cmd_push_constants(cmd, (u32)location, data, size);
}

/* ---- Task 11: VK-identical push-constant byte offsets ----
 * This cascade is a mechanical, line-by-line port of rhi_vk.c
 * rhi_pipeline_get_uniform_location's table body (pd->X flags mapped to the
 * retained RHIPipelineDesc fields). The two backends MUST return identical
 * offsets for identical descs — the test_rhi_push_offset_dump golden block
 * (VK backend) is diffed byte-empty against the Metal results in
 * test_rhi_metal_resources. Any edit to the VK tables requires the same
 * edit here plus a golden regen. */
static i32 metal_uniform_location(const RHIPipelineDesc *desc, const char *name) {
    /* R591 rule (vk pipeline create): the clustered-skinned variant rides
     * the clustered uniform table, not the G-Buffer table. */
    bool skinned_gbuffer = desc->skinned_vertex && desc->uses_texel_buffer &&
                           !desc->is_instanced && !desc->uses_storage;
    /* R560: skinned G-Buffer vertex stage — same 256B push block as
     * gbuffer_vk.vert: u_model@0 u_view@64 u_proj@128 u_prev_mvp@192.
     * Handled before the clustered classification so u_proj does not resolve
     * to -1 (a texel-buffer pipeline would otherwise be taken as clustered). */
    if (skinned_gbuffer) {
        if (strcmp(name, "u_model") == 0)      return 0;
        if (strcmp(name, "u_view") == 0)       return 64;
        if (strcmp(name, "u_proj") == 0)       return 128;
        if (strcmp(name, "u_prev_mvp") == 0)   return 192;
        return -1;
    }

    bool clustered = desc->uses_texel_buffer && !desc->is_instanced;
    bool non_clustered_tbo = desc->uses_texel_buffer && desc->is_instanced;

    /* Terrain: model is identity (dropped). Push block (<=256B):
     *   u_view@0 u_proj@64 u_light_vp@128
     *   u_light_dir@192 u_shadow_bias@204  (packed vec4)
     *   u_light_color@208 u_water_y@220    (packed vec4)
     *   u_ambient@224 u_time@236           (packed vec4)
     *   u_camera_pos@240                   (vec4) */
    if (desc->terrain_layout) {
        if (strcmp(name, "u_view") == 0)        return 0;
        if (strcmp(name, "u_proj") == 0)        return 64;
        if (strcmp(name, "u_light_vp") == 0)    return 128;
        if (strcmp(name, "u_light_dir") == 0)   return 192;
        if (strcmp(name, "u_shadow_bias") == 0) return 204;
        if (strcmp(name, "u_light_color") == 0) return 208;
        if (strcmp(name, "u_water_y") == 0)     return 220;
        if (strcmp(name, "u_ambient") == 0)     return 224;
        if (strcmp(name, "u_time") == 0)        return 236;
        if (strcmp(name, "u_camera_pos") == 0)  return 240;
        return -1; /* u_model, u_albedo (sampler) not push constants */
    }
    /* Water: no model. Push block (<=256B):
     *   u_view@0 u_proj@64 u_light_vp@128
     *   u_camera_pos@192 u_time@204    (packed vec4)
     *   u_water_color@208 u_shadow_bias@220 (packed vec4)
     *   u_water_y@224                  (vec4) */
    if (desc->water_layout) {
        if (strcmp(name, "u_view") == 0)         return 0;
        if (strcmp(name, "u_proj") == 0)         return 64;
        if (strcmp(name, "u_light_vp") == 0)     return 128;
        if (strcmp(name, "u_camera_pos") == 0)   return 192;
        if (strcmp(name, "u_time") == 0)         return 204;
        if (strcmp(name, "u_water_color") == 0)  return 208;
        if (strcmp(name, "u_shadow_bias") == 0)  return 220;
        if (strcmp(name, "u_water_y") == 0)      return 224;
        return -1;
    }
    /* R202-B: shadow depth pipelines (CSM depth_only + point_shadow_depth). */
    if (desc->is_shadow_depth) {
        if (strcmp(name, "u_model") == 0)      return 0;
        if (strcmp(name, "u_light_vp") == 0)   return 64;  /* CSM */
        if (strcmp(name, "u_mvp") == 0)        return 64;  /* point light */
        if (strcmp(name, "u_light_pos") == 0)  return 128;
        if (strcmp(name, "u_far_plane") == 0)  return 144;
        return -1;
    }
    /* Combined TAA+FXAA (combined_taa_fxaa_vk.frag). Push block (<=256B):
     *   u_taa_curr_vp@0 u_taa_prev_vp@64 u_taa_inv_proj@128
     *   u_screen_w@192 u_screen_h@196 u_taa_blend@200
     *   u_taa_first_frame@204 u_fxaa_threshold@208 u_taa_use_velocity@212 */
    if (desc->combined_aa_layout) {
        if (strcmp(name, "u_taa_curr_vp") == 0)     return 0;
        if (strcmp(name, "u_taa_prev_vp") == 0)     return 64;
        if (strcmp(name, "u_taa_inv_proj") == 0)    return 128;
        if (strcmp(name, "u_screen_w") == 0)        return 192;
        if (strcmp(name, "u_screen_h") == 0)        return 196;
        if (strcmp(name, "u_taa_blend") == 0)       return 200;
        if (strcmp(name, "u_taa_first_frame") == 0) return 204;
        if (strcmp(name, "u_fxaa_threshold") == 0)  return 208;
        if (strcmp(name, "u_taa_use_velocity") == 0) return 212;
        return -1; /* samplers (curr/hist/depth/velocity) are not push constants */
    }
    /* Combined tonemap+colorgrade+cinematic (combined_color_vk.frag):
     *   u_tm_exposure@0 u_tm_gamma@4 u_tm_mode@8
     *   u_cg_saturation@12 u_cg_contrast@16 u_cg_brightness@20
     *   u_cg_temperature@24 u_cg_tint@28
     *   u_cine_aberration@32 u_cine_vignette@36 u_cine_grain@40 u_cine_time@44
     *   u_screen_w@48 u_screen_h@52 */
    if (desc->combined_color_layout) {
        if (strcmp(name, "u_tm_exposure") == 0)    return 0;
        if (strcmp(name, "u_tm_gamma") == 0)       return 4;
        if (strcmp(name, "u_tm_mode") == 0)        return 8;
        if (strcmp(name, "u_cg_saturation") == 0)  return 12;
        if (strcmp(name, "u_cg_contrast") == 0)    return 16;
        if (strcmp(name, "u_cg_brightness") == 0)  return 20;
        if (strcmp(name, "u_cg_temperature") == 0) return 24;
        if (strcmp(name, "u_cg_tint") == 0)        return 28;
        if (strcmp(name, "u_cine_aberration") == 0) return 32;
        if (strcmp(name, "u_cine_vignette") == 0)  return 36;
        if (strcmp(name, "u_cine_grain") == 0)     return 40;
        if (strcmp(name, "u_cine_time") == 0)      return 44;
        if (strcmp(name, "u_screen_w") == 0)       return 48;
        if (strcmp(name, "u_screen_h") == 0)       return 52;
        return -1;
    }

    if (non_clustered_tbo) {
        if (strcmp(name, "u_view") == 0)        return 0;
        if (strcmp(name, "u_proj") == 0)        return 64;
        if (strcmp(name, "u_light_dir") == 0)   return 128;
        if (strcmp(name, "u_light_color") == 0) return 144;
        if (strcmp(name, "u_ambient") == 0)     return 160;
        if (strcmp(name, "u_camera_pos") == 0)  return 176;
        return -1;
    }
    if (desc->is_compute) {
        if (strcmp(name, "push.dt") == 0)           return 0;
        if (strcmp(name, "push.view") == 0)         return 0;
        if (strcmp(name, "push.proj") == 0)         return 64;
        /* IBL compute shaders (irradiance & prefilter share push layout):
         *   u_roughness@0  u_face@4  u_face_size/u_mip_size@8 */
        if (strcmp(name, "u_roughness") == 0)       return 0;
        if (strcmp(name, "u_face") == 0)            return 4;
        if (strcmp(name, "u_face_size") == 0)       return 8;
        if (strcmp(name, "u_mip_size") == 0)        return 8;
        /* sky_to_cube.comp: shares u_face@4 / u_face_size@8 above, plus the
         * sun vectors at aligned offsets 16 and 32. */
        if (strcmp(name, "u_sun_dir") == 0)         return 16;
        if (strcmp(name, "u_sun_color") == 0)       return 32;
        /* cluster_cull.comp: mat4 vp@0, vec4 params0@64, vec4 params1@80. */
        if (strcmp(name, "u_cc_vp") == 0)           return 0;
        if (strcmp(name, "u_cc_params0") == 0)      return 64;
        if (strcmp(name, "u_cc_params1") == 0)      return 80;
        /* GPU culling (cull.comp / unified_cull.comp): mat4 vp@0, uint count@64 */
        if (strcmp(name, "u_cull_vp") == 0)         return 0;
        if (strcmp(name, "u_cull_count") == 0)      return 64;
        if (strcmp(name, "u_cull_hi_z_width") == 0)  return 68;
        if (strcmp(name, "u_cull_hi_z_height") == 0) return 72;
        if (strcmp(name, "u_cull_use_hi_z") == 0)    return 76;
        if (strcmp(name, "u_cull_write_draws") == 0) return 80;
        /* Occlusion culling (occlusion_cull.comp): mat4 view_proj@0, uint object_count@64, float hi_z_width@68, float hi_z_height@72 */
        if (strcmp(name, "pc_view_proj") == 0)       return 0;
        if (strcmp(name, "pc_object_count") == 0)    return 64;
        if (strcmp(name, "pc_hi_z_width") == 0)      return 68;
        if (strcmp(name, "pc_hi_z_height") == 0)     return 72;
        /* Hi-Z generation (hi_z_generate.comp): vec2 output_size@0 */
        if (strcmp(name, "pc_output_size") == 0)     return 0;
        /* Draw compaction (compact_draws.comp): uint total_draws@0 */
        if (strcmp(name, "total_draws") == 0)       return 0;
        return -1;
    }
    /* The clustered instanced/skinned variants (R590/R591) also carry a
     * storage set for their vertex SSBO, but their push block is the
     * clustered one below; only particle-style storage pipelines take this
     * short table. */
    if (desc->uses_storage && !clustered) {
        if (strcmp(name, "push.view") == 0)         return 0;
        if (strcmp(name, "push.proj") == 0)         return 64;
        return -1;
    }
    /* R203-A: gbuffer_vk.vert packs prev@192; camera_velocity_vk packs prev@128.
     * An unconditional 192 made the late return 128 dead and broke forward_velocity. */
    if (strcmp(name, "u_prev_mvp") == 0)
        return 192;
    if (strcmp(name, "u_prev_vp") == 0)
        return (desc->no_vertex_input) ? 128 : 192;
    if (strcmp(name, "u_model") == 0)       return 0;
    if (strcmp(name, "u_view") == 0)        return 64;
    /* The clustered fragment shader drops the unused u_proj slot and reuses the
     * freed 64 bytes for camera/ambient/fog/shadow params (see clustered map). */
    if (strcmp(name, "u_proj") == 0)        return clustered ? -1 : 128;
    /* R203-B: generic u_light_vp@64 aliased u_view. Real users are covered by
     * terrain/water/is_shadow_depth layouts above — do not map here. */
    if (strcmp(name, "u_vol_inv_proj") == 0)     return 0;
    if (strcmp(name, "u_vol_view") == 0)         return 64;
    if (strcmp(name, "u_vol_ldx") == 0)          return 128;
    if (strcmp(name, "u_vol_ldy") == 0)          return 132;
    if (strcmp(name, "u_vol_ldz") == 0)          return 136;
    if (strcmp(name, "u_vol_lcx") == 0)          return 140;
    if (strcmp(name, "u_vol_lcy") == 0)          return 144;
    if (strcmp(name, "u_vol_lcz") == 0)          return 148;
    if (strcmp(name, "u_vol_density") == 0)      return 152;
    if (strcmp(name, "u_vol_fog_r") == 0)        return 156;
    if (strcmp(name, "u_vol_fog_g") == 0)        return 160;
    if (strcmp(name, "u_vol_fog_b") == 0)        return 164;
    if (strcmp(name, "u_vol_sw") == 0)           return 168;
    if (strcmp(name, "u_vol_sh") == 0)           return 172;
    if (strcmp(name, "u_vol_inv_view") == 0)    return 176; /* R224-B */
    if (strcmp(name, "u_lf_light_x") == 0)          return 0;
    if (strcmp(name, "u_lf_light_y") == 0)          return 4;
    if (strcmp(name, "u_lf_intensity") == 0)        return 8;
    if (strcmp(name, "u_lf_sw") == 0)               return 12;
    if (strcmp(name, "u_lf_sh") == 0)               return 16;
    if (strcmp(name, "u_lf_lc_r") == 0)             return 20;
    if (strcmp(name, "u_lf_lc_g") == 0)             return 24;
    if (strcmp(name, "u_lf_lc_b") == 0)             return 28;
    if (strcmp(name, "u_sun_dir") == 0)              return 128;
    if (strcmp(name, "u_sun_color") == 0)            return 144;
    if (strcmp(name, "u_ssgi_inv_proj") == 0)       return 0;
    if (strcmp(name, "u_ssgi_proj") == 0)           return 64;
    if (strcmp(name, "u_ssgi_radius") == 0)         return 128;
    if (strcmp(name, "u_ssgi_intensity") == 0)      return 132;
    if (strcmp(name, "u_ssgi_sw") == 0)             return 136;
    if (strcmp(name, "u_ssgi_sh") == 0)             return 140;
    if (strcmp(name, "u_fxaa_sw") == 0)            return 0;
    if (strcmp(name, "u_fxaa_sh") == 0)            return 4;
    /* R204-B: standalone tonemap_vk.frag layout (combined_color uses early map).
     * Old mega-tonemap offsets (aberration@8 etc.) conflicted with screen_w/mode. */
    if (strcmp(name, "u_tm_exposure") == 0)       return 0;
    if (strcmp(name, "u_tm_gamma") == 0)           return 4;
    if (strcmp(name, "u_tm_screen_w") == 0)         return 8;
    if (strcmp(name, "u_tm_screen_h") == 0)         return 12;
    if (strcmp(name, "u_cine_aberration") == 0)    return 0;
    if (strcmp(name, "u_cine_vignette") == 0)    return 4;
    if (strcmp(name, "u_cine_grain") == 0)       return 8;
    if (strcmp(name, "u_cine_time") == 0)        return 12;
    if (strcmp(name, "u_cine_sw") == 0)          return 16;
    if (strcmp(name, "u_cine_sh") == 0)          return 20;
    if (strcmp(name, "u_dof_focus") == 0)       return 0;
    if (strcmp(name, "u_dof_range") == 0)       return 4;
    if (strcmp(name, "u_dof_near") == 0)        return 8;
    if (strcmp(name, "u_dof_far") == 0)         return 12;
    if (strcmp(name, "u_dof_sw") == 0)          return 16;
    if (strcmp(name, "u_dof_sh") == 0)          return 20;
    if (strcmp(name, "u_ssr_proj") == 0)        return 0;
    if (strcmp(name, "u_ssr_inv_proj") == 0)    return 64;
    if (strcmp(name, "u_ssr_view") == 0)        return 128;
    if (strcmp(name, "u_ssr_sw") == 0)          return 192;
    if (strcmp(name, "u_ssr_sh") == 0)          return 196;
    if (strcmp(name, "u_ssr_max_steps") == 0)   return 200;
    if (strcmp(name, "u_ssr_stride") == 0)      return 204;
    if (strcmp(name, "u_ssr_thickness") == 0)   return 208;
    if (strcmp(name, "u_taa_curr_vp") == 0)     return 0;
    if (strcmp(name, "u_taa_prev_vp") == 0)     return 64;
    if (strcmp(name, "u_taa_inv_proj") == 0)    return 128;
    if (strcmp(name, "u_taa_sw") == 0)          return 192;
    if (strcmp(name, "u_taa_sh") == 0)          return 196;
    if (strcmp(name, "u_taa_blend") == 0)       return 200;
    if (strcmp(name, "u_taa_first_frame") == 0) return 204;
    if (strcmp(name, "u_taa_use_velocity") == 0) return 208;
    if (strcmp(name, "u_ssao_proj") == 0)       return 0;
    if (strcmp(name, "u_ssao_inv_proj") == 0)   return 64;
    if (strcmp(name, "u_ssao_sw") == 0)         return 128;
    if (strcmp(name, "u_ssao_sh") == 0)         return 132;
    if (strcmp(name, "u_ssao_radius") == 0)     return 136;
    if (strcmp(name, "u_ssao_bias") == 0)       return 140;
    /* Debug visualization overlay (debug_viz_vk.frag). */
    if (strcmp(name, "u_dv_mode") == 0)         return 0;
    if (strcmp(name, "u_dv_near") == 0)         return 4;
    if (strcmp(name, "u_dv_far") == 0)          return 8;
    if (strcmp(name, "u_dv_split0") == 0)       return 12;
    if (strcmp(name, "u_dv_split1") == 0)       return 16;
    if (strcmp(name, "u_dv_split2") == 0)       return 20;
    if (strcmp(name, "u_dv_split3") == 0)       return 24;
    /* Lens effects (lens_effects_vk.frag): chromatic aberration + vignette + grain. */
    if (strcmp(name, "u_ca_strength") == 0)        return 0;
    if (strcmp(name, "u_vignette_strength") == 0)  return 4;
    if (strcmp(name, "u_vignette_softness") == 0)  return 8;
    if (strcmp(name, "u_grain_strength") == 0)     return 12;
    /* Sharpen (sharpen_vk.frag): CAS-style strength + screen size. */
    if (strcmp(name, "u_sharp_strength") == 0)     return 0;
    if (strcmp(name, "u_sharp_sw") == 0)           return 4;
    if (strcmp(name, "u_sharp_sh") == 0)           return 8;
    /* Upscale TSR (upscale_vk.frag). R197-A: locations were missing — all loc_*
     * returned -1 so push constants never reached the shader. */
    if (strcmp(name, "u_ups_rw") == 0)             return 0;
    if (strcmp(name, "u_ups_rh") == 0)             return 4;
    if (strcmp(name, "u_ups_dw") == 0)             return 8;
    if (strcmp(name, "u_ups_dh") == 0)             return 12;
    if (strcmp(name, "u_ups_sharp") == 0)          return 16;
    if (strcmp(name, "u_ups_copy_only") == 0)      return 20;
    if (strcmp(name, "u_ups_first_frame") == 0)    return 24;
    if (strcmp(name, "u_ups_inv_proj") == 0)       return 32;
    if (strcmp(name, "u_ups_prev_vp") == 0)        return 96;
    /* R198-A: luminance_vk.frag auto-exposure — missing map froze adaptation. */
    if (strcmp(name, "u_lum_w") == 0)              return 0;
    if (strcmp(name, "u_lum_h") == 0)              return 4;
    if (strcmp(name, "u_lum_speed") == 0)          return 8;
    if (strcmp(name, "u_lum_dt") == 0)             return 12;
    /* R198-B: god_rays_vk.frag — missing map zeroed sun/intensity. */
    if (strcmp(name, "u_gr_sun_x") == 0)           return 0;
    if (strcmp(name, "u_gr_sun_y") == 0)           return 4;
    if (strcmp(name, "u_gr_intensity") == 0)       return 8;
    if (strcmp(name, "u_gr_decay") == 0)           return 12;
    if (strcmp(name, "u_gr_sw") == 0)              return 16;
    if (strcmp(name, "u_gr_sh") == 0)              return 20;
    /* R199-A: motion_blur_vk.frag — missing map zeroed strength/proj. */
    if (strcmp(name, "u_mb_strength") == 0)        return 0;
    if (strcmp(name, "u_mb_sw") == 0)              return 4;
    if (strcmp(name, "u_mb_sh") == 0)              return 8;
    if (strcmp(name, "u_mb_inv_proj") == 0)        return 12;
    if (strcmp(name, "u_mb_prev_vp") == 0)         return 76;
    if (strcmp(name, "u_mb_use_velocity") == 0)    return 140;
    /* R199-B: contact_shadow_vk.frag — missing map zeroed light/proj. */
    if (strcmp(name, "u_cs_light_x") == 0)         return 0;
    if (strcmp(name, "u_cs_light_y") == 0)         return 4;
    if (strcmp(name, "u_cs_light_z") == 0)         return 8;
    if (strcmp(name, "u_cs_inv_proj") == 0)        return 12;
    if (strcmp(name, "u_cs_sw") == 0)              return 76;
    if (strcmp(name, "u_cs_sh") == 0)              return 80;
    /* R200-A: color_grade_vk.frag standalone — combined_color_layout uses different offsets. */
    if (strcmp(name, "u_cg_saturation") == 0)      return 0;
    if (strcmp(name, "u_cg_contrast") == 0)        return 4;
    if (strcmp(name, "u_cg_brightness") == 0)      return 8;
    if (strcmp(name, "u_cg_temperature") == 0)     return 12;
    if (strcmp(name, "u_cg_tint") == 0)            return 16;
    /* R200-B: bloom extract/blur/composite — missing map killed bloom + SSGI blur. */
    if (strcmp(name, "u_threshold") == 0)          return 0;
    if (strcmp(name, "u_direction") == 0)          return 0; /* vec2 */
    if (strcmp(name, "u_bloom_strength") == 0)     return 0;
    /* R201-A: sss_vk / sss_vertical_vk — missing map → sw/sh=0 divide-by-zero. */
    if (strcmp(name, "u_sss_strength") == 0)       return 0;
    if (strcmp(name, "u_sss_sw") == 0)             return 4;
    if (strcmp(name, "u_sss_sh") == 0)             return 8;
    if (strcmp(name, "u_sss_max_dist") == 0)       return 12;
    if (strcmp(name, "u_sssv_strength") == 0)      return 0;
    if (strcmp(name, "u_sssv_sw") == 0)            return 4;
    if (strcmp(name, "u_sssv_sh") == 0)            return 8;
    if (strcmp(name, "u_sssv_max_dist") == 0)      return 12;
    /* R201-B: fxaa_vk.frag standalone threshold (combined_aa uses offset 208). */
    if (strcmp(name, "u_fxaa_threshold") == 0)     return 8;
    /* Standalone tonemap_vk.frag mode (combined_color uses offset 8). */
    if (strcmp(name, "u_tm_mode") == 0)            return 16;
    if (strcmp(name, "u_view") == 0)        return 64;
    if (strcmp(name, "u_proj") == 0)        return 128;
    if (clustered) {
        /* Layout matches pbr_clustered_vk.frag's push block (u_proj removed). */
        /* R579-E: the model-matrix write must resolve or draws render with
         * stale push garbage (the R579-B/C/E "zero fragments" final root
         * cause). R586: the vert now declares only u_model@0/u_view@64 at
         * these same offsets and reads proj from the aux UBO — the
         * contradictory u_proj@128 vert layout is retired. */
        if (strcmp(name, "u_model") == 0)      return 0;
        if (strcmp(name, "u_camera_pos") == 0)  return 128;
        if (strcmp(name, "u_fog_near") == 0)    return 140;
        if (strcmp(name, "u_ambient") == 0)     return 144;
        if (strcmp(name, "u_fog_far") == 0)     return 156;
        if (strcmp(name, "u_screen_w") == 0)    return 160;
        if (strcmp(name, "u_screen_h") == 0)    return 164;
        if (strcmp(name, "u_near") == 0)        return 168;
        if (strcmp(name, "u_far") == 0)         return 172;
        if (strcmp(name, "u_point_count") == 0) return 176;
        if (strcmp(name, "u_dir_count") == 0)   return 180;
        if (strcmp(name, "u_shadow_bias") == 0) return 184;
        if (strcmp(name, "u_fog_color") == 0)   return 192;
        if (strcmp(name, "u_underwater") == 0)  return 204;
        if (strcmp(name, "u_point_shadow_far_planes") == 0) return 208;
        if (strcmp(name, "u_pom_enabled") == 0) return 224;
        if (strcmp(name, "u_occlusion_strength") == 0) return 228; /* R598 */
        if (strcmp(name, "u_mr_factor") == 0)  return 232; /* R579 */
        if (strcmp(name, "u_emissive_factor") == 0) return 240; /* R586 */
    } else if (desc->no_vertex_input && desc->uses_texel_buffer && !desc->is_compute) {
        /* deferred_light_vk: clustered lighting + IBL full-screen pass. */
        if (strcmp(name, "u_inv_vp") == 0)       return 0;
        if (strcmp(name, "u_view") == 0)         return 64;
        if (strcmp(name, "u_camera_pos") == 0)   return 128;
        if (strcmp(name, "u_screen_w") == 0)      return 144;
        if (strcmp(name, "u_screen_h") == 0)      return 148;
        if (strcmp(name, "u_near") == 0)          return 160;
        if (strcmp(name, "u_far") == 0)           return 164;
        if (strcmp(name, "u_shadow_bias") == 0)   return 168;
        if (strcmp(name, "u_point_count") == 0)   return 176;
        if (strcmp(name, "u_dir_count") == 0)     return 180;
        /* vec4 member — std430 aligns 16 (SPIR-V Offset 192; the pre-R588
         * float[4] sat at 184). Mirrors the rhi_vk.c table fix. */
        if (strcmp(name, "u_point_shadow_far_planes") == 0) return 192;
    } else if (desc->no_vertex_input && !desc->uses_texel_buffer && !desc->is_compute) {
        /* Other full-screen post passes (tonemap, fxaa, etc.). */
        if (strcmp(name, "u_inv_vp") == 0)     return 0;
        if (strcmp(name, "u_camera_pos") == 0) return 64;
        if (strcmp(name, "u_screen_w") == 0)    return 80;
        if (strcmp(name, "u_screen_h") == 0)    return 84;
        /* R445: the skybox is also a no_vertex_input fullscreen pipeline and
         * lands in this branch — its push block (skybox_vk.vert/.frag) is
         * u_inv_proj@0 u_view@64 u_sun_dir@128 u_sun_color@144. u_inv_proj
         * resolved below (shared return 0); without these, u_view/sun stayed
         * at -1 and the VK sky sampled uninitialized push-constant garbage
         * (static, sun-preset-immune haze). */
        if (strcmp(name, "u_view") == 0)       return 64;
        if (strcmp(name, "u_sun_dir") == 0)    return 128;
        if (strcmp(name, "u_sun_color") == 0)  return 144;
    } else {
        if (strcmp(name, "u_light_dir") == 0)   return 192;
        if (strcmp(name, "u_light_color") == 0) return 208;
        if (strcmp(name, "u_ambient") == 0)     return 224;
        if (strcmp(name, "u_camera_pos") == 0)  return 240;
    }
    if (strcmp(name, "u_albedo") == 0)      return -1;
    if (strcmp(name, "u_inv_proj") == 0)    return 0;
    if (strcmp(name, "u_curr_vp") == 0)     return 64;
    /* editor_color_vk.vert/.frag (position-only vec3, 12-byte stride):
     * mat4 u_mvp@0, vec4 u_color@64. The shadow-depth u_mvp@64 case
     * returned earlier; the stride gate keeps every other desc on the VK
     * golden table. */
    if (desc->vertex_stride == 12u) {
        if (strcmp(name, "u_mvp") == 0)     return 0;
        if (strcmp(name, "u_color") == 0)   return 64;
    }
    return -1;
}

i32 rhi_pipeline_get_uniform_location(RHIDevice *dev, RHIPipeline pipe, const char *name) {
    MetalPipeline *pp;
    if (dev == NULL || name == NULL) return -1;
    pp = (MetalPipeline *)rhi_get_resource_typed(dev, pipe, RHI_RES_PIPELINE);
    if (pp == NULL) {
        /* Divergence note (review M1): VK falls through to its generic
         * tables when the handle does not resolve (pd==NULL returns table
         * offsets); Metal fails closed with -1. Callers passing an invalid
         * pipeline are already broken either way — behavior intentionally
         * unchanged. */
        return -1;
    }
    return metal_uniform_location(&pp->desc, name);
}

/* Owned pipeline-layout snapshot: both bindings APIs resolve through the same
 * VK-aligned offset table, and the copy keeps the names independent of the
 * pipeline's lifetime. */
struct RHIPipelineBindings {
    RHIPipelineDesc desc;
};

RHIPipelineBindings *rhi_pipeline_bindings_create(RHIDevice *dev, RHIPipeline pipe) {
    MetalPipeline *pp;
    RHIPipelineBindings *b;
    if (dev == NULL) return NULL;
    pp = (MetalPipeline *)rhi_get_resource_typed(dev, pipe, RHI_RES_PIPELINE);
    if (pp == NULL) return NULL;
    b = (RHIPipelineBindings *)calloc(1u, sizeof(*b));
    if (b != NULL) b->desc = pp->desc;
    return b;
}

void rhi_pipeline_bindings_destroy(RHIDevice *dev, RHIPipelineBindings *b) {
    (void)dev;
    free(b);
}

i32 rhi_pipeline_bindings_resolve(const RHIPipelineBindings *b, const char *name) {
    if (b == NULL || name == NULL) return -1;
    return metal_uniform_location(&b->desc, name);
}

/* ---- Task 8: render-target payloads and FBO family ----
 * Metal has no framebuffer object: the FBO structs group texture handles
 * and a small backend payload (clear color / MSAA textures); bind builds a
 * MTLRenderPassDescriptor on the spot (loadAction carries the R616-R619
 * clear/preserve contract — the VK loadOp form, not GL's explicit clear). */

/* Private-storage render-target texture (no initial data, no host upload
 * path). cube => MTLTextureTypeCube; samples > 1 => 2DMultisample
 * (render-target-only usage: the single-sample resolve target is the
 * readable texture). */
static MetalTexture *metal_render_target_tex_alloc(MetalBackend *mb,
                                                   u32 w, u32 h,
                                                   RHIFormat fmt,
                                                   bool cube, u32 samples) {
    MetalTexture *td = (MetalTexture *)calloc(1u, sizeof(*td));
    RHIMetalFormat mf;
    if (td == NULL) return NULL;
    mf = rhi_metal_format_from_rhi(fmt);
    if (mf == RHI_METAL_FORMAT_INVALID) {
        free(td);
        return NULL;
    }
    @autoreleasepool {
        MTLTextureDescriptor *d;
        if (cube) {
            d = [MTLTextureDescriptor
                textureCubeDescriptorWithPixelFormat:rhi_metal_pixel_format(mf)
                                                size:(NSUInteger)w
                                           mipmapped:NO];
        } else {
            d = [MTLTextureDescriptor
                texture2DDescriptorWithPixelFormat:rhi_metal_pixel_format(mf)
                                             width:(NSUInteger)w
                                            height:(NSUInteger)h
                                         mipmapped:NO];
        }
        if (samples > 1u) {
            d.textureType = MTLTextureType2DMultisample;
            d.sampleCount = (NSUInteger)samples;
            d.usage = MTLTextureUsageRenderTarget;
        } else {
            d.usage = metal_texture_usage_for(fmt);
        }
        d.storageMode = MTLStorageModePrivate;
        /* newTextureWithDescriptor: returns +1 (new* rule) — hold directly. */
        td->texture = [mb->device newTextureWithDescriptor:d];
    }
    if (td->texture == nil) {
        LOG_ERROR("rhi_metal: render-target texture allocation failed (%ux%u fmt %d)",
                  (unsigned)w, (unsigned)h, (int)fmt);
        free(td);
        return NULL;
    }
    td->format = fmt;
    td->width = w;
    td->height = h;
    td->mip_levels = 1u;
    td->layers = cube ? 6u : 1u;
    td->is_cube = cube;
    return td;
}

/* Slot-wrap an FBO-owned texture payload. */
static RHITexture metal_fbo_texture_slot(RHIDevice *dev, MetalTexture *td,
                                         u32 slot_type) {
    u32 idx = rhi_alloc_slot(dev);
    dev->slots[idx].ptr = td;
    dev->slots[idx].type = slot_type;
    return rhi_make_handle(idx, dev->slots[idx].generation);
}

/* Release the payload + slot behind an FBO-owned texture handle. */
static void metal_fbo_texture_slot_free(RHIDevice *dev, RHITexture tex,
                                        u32 slot_type) {
    MetalTexture *td;
    if (!rhi_handle_valid(tex)) return;
    td = (MetalTexture *)rhi_get_resource_typed(dev, tex, slot_type);
    if (td != NULL) {
        [td->texture release];
        free(td);
    }
    rhi_free_slot(dev, tex);
}

static bool metal_cmd_in_frame(const RHICmdBuffer *cmd, const char *what) {
    if (cmd == NULL || cmd->backend == NULL || cmd->cmd == nil) {
        LOG_ERROR("rhi_metal: %s outside a live frame", what);
        return false;
    }
    return true;
}

/* Unbind shared tail: end the target pass and reopen the screen pass so the
 * caller's next draws land on the drawable (VK unbind parity: the swapchain
 * pass restarts with loadOp=CLEAR — here with cmd->clear_color, which
 * rhi_cmd_clear_color owns; depth always re-clears to 1.0). Outside a live
 * frame only the encoder close happens. */
static void metal_screen_unbind(RHICmdBuffer *cmd, u32 screen_w, u32 screen_h) {
    MetalBackend *mb;
    if (cmd == NULL || cmd->backend == NULL) return;
    mb = cmd->backend;
    metal_end_render_encoder(cmd);
    if (cmd->cmd == nil || mb->drawable == nil) return;
    cmd->clear_pending = true;   /* VK unbind always re-clears the screen */
    @autoreleasepool {
        metal_open_screen_pass(cmd, screen_w, screen_h, false);
    }
}

typedef struct {
    RHITexture depth_tex;   /* reopen path (in-pass clear_color, C1) */
} MetalShadowData;

RHIShadowMap rhi_shadow_map_create(RHIDevice *dev, u32 width, u32 height) {
    RHIShadowMap sm = {0};
    MetalBackend *mb;
    MetalTexture *depth;
    MetalShadowData *sd;
    u32 idx;
    if (dev == NULL || !rhi_drawable_dimensions_valid(width, height))
        return sm;
    mb = (MetalBackend *)dev->backend_data;
    if (mb == NULL || mb->device_lost_latch) return sm;
    depth = metal_render_target_tex_alloc(mb, width, height,
                                          RHI_FORMAT_D32_FLOAT, false, 1u);
    sd = (MetalShadowData *)calloc(1u, sizeof(*sd));
    if (depth == NULL || sd == NULL) {
        if (depth != NULL) { [depth->texture release]; free(depth); }
        free(sd);
        return sm;
    }
    sm.depth_tex = metal_fbo_texture_slot(dev, depth, RHI_RES_TEXTURE);
    sm.width = width;
    sm.height = height;
    sd->depth_tex = sm.depth_tex;
    idx = rhi_alloc_slot(dev);
    dev->slots[idx].ptr = sd;
    dev->slots[idx].type = RHI_RES_FRAMEBUFFER;
    sm.fbo = rhi_make_handle(idx, dev->slots[idx].generation);
    return sm;
}

void rhi_shadow_map_destroy(RHIDevice *dev, RHIShadowMap *sm) {
    MetalBackend *mb;
    MetalShadowData *sd;
    if (dev == NULL || sm == NULL) return;
    mb = (MetalBackend *)dev->backend_data;
    sd = (MetalShadowData *)rhi_get_resource_typed(dev, sm->fbo,
                                                   RHI_RES_FRAMEBUFFER);
    if (sd == NULL) return;
    if (mb != NULL) metal_retire_drain(dev, mb);
    free(sd);
    rhi_free_slot(dev, sm->fbo);
    metal_fbo_texture_slot_free(dev, sm->depth_tex, RHI_RES_TEXTURE);
    memset(sm, 0, sizeof(*sm));
}

/* Depth-only pass (R618: every bind clears depth to 1.0; no load twin).
 * load=true opens the RESUME variant (loadAction=Load — VK suspend/resume
 * parity for compute/blit interludes). */
static void metal_depth_only_pass_ex(RHICmdBuffer *cmd, id<MTLTexture> depth_tex,
                                     NSUInteger slice, u32 w, u32 h, bool load) {
    @autoreleasepool {
        MTLRenderPassDescriptor *pass =
            [MTLRenderPassDescriptor renderPassDescriptor];
        pass.depthAttachment.texture = depth_tex;
        pass.depthAttachment.slice = slice;
        pass.depthAttachment.loadAction =
            load ? MTLLoadActionLoad : MTLLoadActionClear;
        pass.depthAttachment.clearDepth = 1.0;
        pass.depthAttachment.storeAction = MTLStoreActionStore;
        metal_open_render_pass(cmd, pass, w, h);
    }
}

static void metal_depth_only_pass(RHICmdBuffer *cmd, id<MTLTexture> depth_tex,
                                  NSUInteger slice, u32 w, u32 h) {
    metal_depth_only_pass_ex(cmd, depth_tex, slice, w, h, false);
}

void rhi_cmd_bind_shadow_map(RHICmdBuffer *cmd, RHIShadowMap *sm) {
    MetalTexture *depth;
    if (!metal_cmd_in_frame(cmd, "bind_shadow_map") || sm == NULL) return;
    depth = (MetalTexture *)rhi_get_resource_typed(g_current_device,
                                                   sm->depth_tex,
                                                   RHI_RES_TEXTURE);
    if (depth == NULL) {
        /* Never silent: a failed bind leaves the caller drawing into a
         * never-opened pass (found via Task 13 consumer smoke). */
        LOG_ERROR("rhi_metal: bind_shadow_map: depth_tex does not resolve");
        return;
    }
    metal_depth_only_pass(cmd, depth->texture, 0u, sm->width, sm->height);
    if (cmd->render_pass_open) {
        cmd->pass_kind = METAL_PASS_SHADOW;
        cmd->pass_target = sm->fbo;
        cmd->pass_w = sm->width;
        cmd->pass_h = sm->height;
    } else {
    }
}

void rhi_cmd_unbind_shadow_map(RHICmdBuffer *cmd, u32 screen_w, u32 screen_h) {
    metal_screen_unbind(cmd, screen_w, screen_h);
}

void rhi_cmd_clear_depth(RHICmdBuffer *cmd) {
    u8 kind;
    RHIHandle target;
    u32 w, h, face;
    if (cmd == NULL || cmd->backend == NULL) return;
    metal_resume_render_pass_if_needed(cmd);
    if (!cmd->render_pass_open) return;
    kind = cmd->pass_kind;
    target = cmd->pass_target;
    w = cmd->pass_w;
    h = cmd->pass_h;
    face = cmd->pass_face;
    metal_end_render_encoder(cmd);
    switch (kind) {
    case METAL_PASS_SCREEN:
        metal_open_screen_pass(cmd, w, h, false /* depth Clear, color Load */);
        break;
    case METAL_PASS_OFFSCREEN:
        metal_offscreen_depth_clear_reopen(cmd, target, w, h);
        break;
    case METAL_PASS_MRT:
        metal_mrt_depth_clear_reopen(cmd, target, w, h);
        break;
    case METAL_PASS_SHADOW:
    case METAL_PASS_CUBE_DEPTH:
        metal_depth_target_clear_reopen(cmd, kind, target, w, h, face);
        break;
    default:
        break;
    }
}

RHICubemap rhi_cubemap_create(RHIDevice *dev, const RHICubemapDesc *desc) {
    MetalBackend *mb;
    MetalTexture *cd;
    RHIMetalFormat mf;
    u32 mips;
    u32 idx;
    u32 bpp;
    usize face_bytes;
    u32 f;
    if (dev == NULL || !rhi_cubemap_desc_validate(desc)) return RHI_HANDLE_NULL;
    mb = (MetalBackend *)dev->backend_data;
    if (mb == NULL || mb->device_lost_latch) return RHI_HANDLE_NULL;
    mf = rhi_metal_format_from_rhi(desc->format);
    if (mf == RHI_METAL_FORMAT_INVALID) {
        LOG_ERROR("rhi_metal: cubemap format %d has no Metal mapping",
                  (int)desc->format);
        return RHI_HANDLE_NULL;
    }
    mips = desc->mip_levels == 0u ? 1u : desc->mip_levels;
    bpp = metal_texture_bpp(desc->format);
    face_bytes = (usize)desc->size * desc->size * bpp;
    cd = (MetalTexture *)calloc(1u, sizeof(*cd));
    if (cd == NULL) return RHI_HANDLE_NULL;
    @autoreleasepool {
        MTLTextureDescriptor *d = [MTLTextureDescriptor
            textureCubeDescriptorWithPixelFormat:rhi_metal_pixel_format(mf)
                                            size:(NSUInteger)desc->size
                                       mipmapped:(mips > 1u)];
        d.mipmapLevelCount = (NSUInteger)mips;
        /* Cubemap formats are color-only per rhi_cubemap_desc_validate, but
         * route through the same helper so the depth restriction cannot be
         * bypassed by a future desc change. */
        d.usage = metal_texture_usage_for(desc->format);
        d.storageMode = MTLStorageModePrivate;
        cd->texture = [[mb->device newTextureWithDescriptor:d] retain];
    }
    if (cd->texture == nil) {
        LOG_ERROR("rhi_metal: cubemap allocation failed (size %u fmt %d)",
                  (unsigned)desc->size, (int)desc->format);
        free(cd);
        return RHI_HANDLE_NULL;
    }
    cd->format = desc->format;
    cd->width = desc->size;
    cd->height = desc->size;
    cd->mip_levels = mips;
    cd->layers = 6u;
    cd->is_cube = true;
    /* R624/R625: mip 0 per face in native bytes; Metal cube slices are in
     * the same +X,-X,+Y,-Y,+Z,-Z order as the face-major contract, so the
     * upload is a straight per-slice blit. */
    for (f = 0u; f < 6u; ++f) {
        if (desc->faces[f] == NULL) continue;
        if (!metal_texture_upload_region(dev, mb, cd, 0u, f, desc->size,
                                         desc->size, desc->faces[f],
                                         face_bytes)) {
            [cd->texture release];
            free(cd);
            return RHI_HANDLE_NULL;
        }
    }
    idx = rhi_alloc_slot(dev);
    dev->slots[idx].ptr = cd;
    dev->slots[idx].type = RHI_RES_CUBEMAP;
    return rhi_make_handle(idx, dev->slots[idx].generation);
}

void rhi_cubemap_destroy(RHIDevice *dev, RHICubemap cm) {
    MetalBackend *mb;
    MetalTexture *cd;
    if (dev == NULL) return;
    mb = (MetalBackend *)dev->backend_data;
    cd = (MetalTexture *)rhi_get_resource_typed(dev, cm, RHI_RES_CUBEMAP);
    if (cd == NULL) return;
    if (mb != NULL) metal_retire_drain(dev, mb);
    [cd->texture release];
    free(cd);
    rhi_free_slot(dev, cm);
}

void rhi_cubemap_transition_to_read(RHIDevice *dev, RHICubemap cm) {
    /* Metal has no layout transitions; hazard tracking makes a
     * storage-written texture readable without an explicit barrier. */
    (void)dev;
    (void)cm;
}

void rhi_texture_transition_to_read(RHIDevice *dev, RHITexture tex) {
    /* No-op, same rationale as rhi_cubemap_transition_to_read. */
    (void)dev;
    (void)tex;
}

void rhi_cmd_bind_cubemap(RHICmdBuffer *cmd, RHICubemap cm, RHISampler sampler, u32 unit) {
    MetalTexture *cd;
    MetalSampler *sd;
    if (cmd == NULL || cmd->backend == NULL) return;
    metal_resume_render_pass_if_needed(cmd);
    if (cmd->render_encoder == nil) return;
    cd = (MetalTexture *)rhi_get_resource_typed(g_current_device, cm,
                                                RHI_RES_CUBEMAP);
    sd = (MetalSampler *)rhi_get_resource_typed(g_current_device, sampler,
                                                RHI_RES_SAMPLER);
    if (cd == NULL || sd == NULL) return;
    metal_set_frag_texture(cmd, cd->texture, (NSUInteger)unit);
    metal_set_frag_sampler(cmd, sd->sampler, (NSUInteger)unit);
}

/* These calls are pipeline-state declarations on Metal too: skybox already
 * selects LEQUAL + no depth write + no culling in its RHIPipelineDesc. */
void rhi_cmd_set_depth_func_less_or_equal(RHICmdBuffer *cmd) {
    (void)cmd;
}

void rhi_cmd_set_depth_func_less(RHICmdBuffer *cmd) {
    (void)cmd;
}

void rhi_cmd_set_depth_mask(RHICmdBuffer *cmd, bool enabled) {
    (void)cmd;
    (void)enabled;
}

void rhi_cmd_set_cull_face(RHICmdBuffer *cmd, bool enabled) {
    (void)cmd;
    (void)enabled;
}

void rhi_cmd_bind_texel_buffers(RHICmdBuffer *cmd, RHIBuffer buf0, RHIBuffer buf1) {
    MetalBuffer *b0, *b1;
    if (cmd == NULL || cmd->backend == NULL) return;
    metal_resume_render_pass_if_needed(cmd);
    if (cmd->render_encoder == nil) return;
    b0 = (MetalBuffer *)rhi_get_resource_typed(g_current_device, buf0,
                                               RHI_RES_BUFFER);
    b1 = (MetalBuffer *)rhi_get_resource_typed(g_current_device, buf1,
                                               RHI_RES_BUFFER);
    if (b0 == NULL || b0->texel_view == nil) return;
    if (b1 == NULL || b1->texel_view == nil) {
        b1 = b0;
        buf1 = buf0;
    }
    cmd->bound_texel[0] = buf0;
    cmd->bound_texel[1] = buf1;
    metal_apply_texel_views(cmd, b0, b1);
}

static void metal_flush_texel(RHICmdBuffer *cmd, const MetalPipeline *pp) {
    MetalBuffer *b0, *b1;
    if (!pp->desc.uses_texel_buffer || cmd->render_encoder == nil) return;
    b0 = (MetalBuffer *)rhi_get_resource_typed(g_current_device,
                                               cmd->bound_texel[0],
                                               RHI_RES_BUFFER);
    b1 = (MetalBuffer *)rhi_get_resource_typed(g_current_device,
                                               cmd->bound_texel[1],
                                               RHI_RES_BUFFER);
    if (b0 == NULL || b0->texel_view == nil) return;
    if (b1 == NULL || b1->texel_view == nil) b1 = b0;
    metal_apply_texel_views(cmd, b0, b1);
}

static void metal_apply_texel_views(RHICmdBuffer *cmd, const MetalBuffer *b0,
                                    const MetalBuffer *b1) {
    /* samplerBuffer flattening: set*16+binding. The shaders use both stages
     * depending on the instanced/skinned/clustered variant. */
    [cmd->render_encoder setVertexTexture:b0->texel_view atIndex:16u];
    [cmd->render_encoder setVertexTexture:b1->texel_view atIndex:17u];
    [cmd->render_encoder setFragmentTexture:b0->texel_view atIndex:16u];
    [cmd->render_encoder setFragmentTexture:b1->texel_view atIndex:17u];
}

void rhi_buffer_update(RHIDevice *dev, RHIBuffer buf, const void *data, usize size) {
    rhi_buffer_update_region(dev, buf, 0u, data, size);
}

void rhi_buffer_update_region(RHIDevice *dev, RHIBuffer buf, usize offset, const void *data, usize size) {
    MetalBackend *mb;
    MetalBuffer *bb;
    if (dev == NULL || data == NULL || size == 0u) return;
    mb = (MetalBackend *)dev->backend_data;
    if (mb == NULL || mb->device_lost_latch) return;
    bb = (MetalBuffer *)rhi_get_resource_typed(dev, buf, RHI_RES_BUFFER);
    if (bb == NULL || offset >= bb->size) return;
    if (size > bb->size - offset) size = bb->size - offset;
    if (bb->shared_mode) {
        /* Shared storage is coherent and persistently mapped: direct copy. */
        memcpy((u8 *)bb->buffer.contents + offset, data, (size_t)size);
        return;
    }
    /* Private storage: blit staging through a transient shared buffer,
     * VK staging-upload parity (rhi_vk.c:8909-8975 semantics), with the
     * bounded submit wait. */
    @autoreleasepool {
        id<MTLBuffer> staging =
            [mb->device newBufferWithBytes:data
                                   length:(NSUInteger)size
                                  options:MTLResourceStorageModeShared];
        id<MTLCommandBuffer> cmd;
        id<MTLBlitCommandEncoder> blit;
        if (staging == nil) {
            LOG_ERROR("rhi_metal: buffer update staging allocation failed");
            return;
        }
        cmd = [mb->queue commandBuffer];
        if (cmd == nil) {
            LOG_ERROR("rhi_metal: buffer update command buffer failed");
            return;
        }
        blit = [cmd blitCommandEncoder];
        [blit copyFromBuffer:staging
                sourceOffset:0u
                    toBuffer:bb->buffer
           destinationOffset:(NSUInteger)offset
                        size:(NSUInteger)size];
        [blit endEncoding];
        (void)metal_commit_wait(dev, mb, cmd);
    }
}

bool rhi_buffer_read(RHIDevice *dev, RHIBuffer buf, void *dst, usize offset, usize size) {
    MetalBackend *mb;
    MetalBuffer *bb;
    if (dev == NULL || dst == NULL || size == 0u) return false;
    mb = (MetalBackend *)dev->backend_data;
    if (mb == NULL || mb->device_lost_latch) return false;
    bb = (MetalBuffer *)rhi_get_resource_typed(dev, buf, RHI_RES_BUFFER);
    if (bb == NULL || offset >= bb->size) return false;
    if (size > bb->size - offset) size = bb->size - offset;
    if (bb->shared_mode) {
        memcpy(dst, (const u8 *)bb->buffer.contents + offset, (size_t)size);
        return true;
    }
    /* Private storage: blit back to a shared staging buffer, bounded wait,
     * then host copy. */
    @autoreleasepool {
        id<MTLBuffer> staging =
            [mb->device newBufferWithLength:(NSUInteger)size
                                    options:MTLResourceStorageModeShared];
        id<MTLCommandBuffer> cmd;
        id<MTLBlitCommandEncoder> blit;
        if (staging == nil) {
            LOG_ERROR("rhi_metal: buffer readback staging allocation failed");
            return false;
        }
        cmd = [mb->queue commandBuffer];
        if (cmd == nil) {
            LOG_ERROR("rhi_metal: buffer readback command buffer failed");
            return false;
        }
        blit = [cmd blitCommandEncoder];
        [blit copyFromBuffer:bb->buffer
                sourceOffset:(NSUInteger)offset
                    toBuffer:staging
           destinationOffset:0u
                        size:(NSUInteger)size];
        [blit endEncoding];
        if (metal_commit_wait(dev, mb, cmd) != RHI_RESULT_OK) return false;
        memcpy(dst, staging.contents, (size_t)size);
        return true;
    }
}

/* Task 9 blit interlude: close the current encoder (one-encoder rule;
 * callers re-bind their target afterwards — VK's suspend/resume equivalent
 * is a later-bind with Load), open a transient blit encoder on the frame's
 * command buffer. Returns nil outside a live frame. */
static id<MTLBlitCommandEncoder> metal_blit_interlude(RHICmdBuffer *cmd,
                                                      const char *what) {
    if (!metal_cmd_in_frame(cmd, what)) return nil;
    if (cmd->render_pass_open && cmd->suspended_kind == METAL_PASS_NONE) {
        cmd->suspended_kind = cmd->pass_kind;
        cmd->suspended_target = cmd->pass_target;
        cmd->suspended_w = cmd->pass_w;
        cmd->suspended_h = cmd->pass_h;
        cmd->suspended_face = cmd->pass_face;
        cmd->suspended_pipeline = cmd->bound_pipeline;
    }
    metal_end_encoders(cmd);
    return [cmd->cmd blitCommandEncoder];   /* autoreleased; ends in place */
}

void rhi_cmd_fill_buffer(RHICmdBuffer *cmd, RHIBuffer buf, usize offset, usize size, u32 value) {
    MetalBuffer *bb;
    id<MTLBlitCommandEncoder> blit;
    if (cmd == NULL || cmd->backend == NULL || size == 0u) return;
    bb = (MetalBuffer *)rhi_get_resource_typed(g_current_device, buf,
                                               RHI_RES_BUFFER);
    if (bb == NULL || offset >= bb->size) return;
    if (size > bb->size - offset) size = bb->size - offset;   /* R425 clamp */
    if (size == 0u) return;
    /* VK parity (vkCmdFillBuffer): the pattern is a u32 word and offset/size
     * are 4-byte aligned. Metal's fillBuffer takes a BYTE pattern, so only
     * byte-uniform words are expressible (all engine callers use 0). */
    if (((offset | size) & 3u) != 0u) {
        LOG_ERROR("rhi_metal: fill_buffer requires 4-byte aligned offset/size");
        return;
    }
    if ((value >> 8 & 0xFFu) != (value & 0xFFu) ||
        (value >> 16 & 0xFFu) != (value & 0xFFu) ||
        (value >> 24) != (value & 0xFFu)) {
        LOG_ERROR("rhi_metal: fill_buffer pattern 0x%08X is not byte-uniform",
                  (unsigned)value);
        return;
    }
    blit = metal_blit_interlude(cmd, "fill_buffer");
    if (blit == nil) return;
    [blit fillBuffer:bb->buffer
               range:NSMakeRange((NSUInteger)offset, (NSUInteger)size)
               value:(u8)(value & 0xFFu)];
    [blit endEncoding];
}

void rhi_cmd_update_buffer(RHICmdBuffer *cmd, RHIBuffer buf, usize offset, const void *data, usize size) {
    MetalBackend *mb;
    MetalBuffer *bb;
    id<MTLBlitCommandEncoder> blit;
    if (cmd == NULL || cmd->backend == NULL || data == NULL || size == 0u)
        return;
    mb = cmd->backend;
    bb = (MetalBuffer *)rhi_get_resource_typed(g_current_device, buf,
                                               RHI_RES_BUFFER);
    if (bb == NULL || offset >= bb->size) return;
    if (size > bb->size - offset) size = bb->size - offset;   /* R425 clamp */
    if (size == 0u) return;
    /* VK parity (vkCmdUpdateBuffer limits): 4-byte align, <= 65536. */
    if (size > 65536u || ((offset | size) & 3u) != 0u) {
        LOG_ERROR("rhi_metal: update_buffer requires 4-byte align and size<=65536");
        return;
    }
    blit = metal_blit_interlude(cmd, "update_buffer");
    if (blit == nil) return;
    @autoreleasepool {
        /* Transient shared staging; the command buffer retains it until
         * execution. newBufferWithBytes: returns +1 (new* rule). */
        id<MTLBuffer> staging =
            [mb->device newBufferWithBytes:data
                                    length:(NSUInteger)size
                                   options:MTLResourceStorageModeShared];
        if (staging == nil) {
            LOG_ERROR("rhi_metal: update_buffer staging allocation failed");
            return;
        }
        [blit copyFromBuffer:staging
                sourceOffset:0u
                    toBuffer:bb->buffer
           destinationOffset:(NSUInteger)offset
                        size:(NSUInteger)size];
        [blit endEncoding];
        [staging release];
    }
}

void *rhi_buffer_map(RHIDevice *dev, RHIBuffer buf) {
    MetalBuffer *bb;
    if (dev == NULL) return NULL;
    bb = (MetalBuffer *)rhi_get_resource_typed(dev, buf, RHI_RES_BUFFER);
    if (bb == NULL) return NULL;
    if (!bb->shared_mode) {
        /* Fail-closed (VK R186 parity): private storage has no host
         * mapping — use rhi_buffer_read. */
        LOG_ERROR("rhi_metal: rhi_buffer_map on private buffer; use rhi_buffer_read");
        return NULL;
    }
    return bb->buffer.contents;
}

void rhi_buffer_unmap(RHIDevice *dev, RHIBuffer buf) {
    /* Shared storage is persistently mapped; nothing to do. */
    (void)dev;
    (void)buf;
}

void rhi_cmd_copy_buffer(RHICmdBuffer *cmd, RHIBuffer src, RHIBuffer dst, usize size) {
    MetalBuffer *sb;
    MetalBuffer *db;
    id<MTLBlitCommandEncoder> blit;
    if (cmd == NULL || cmd->backend == NULL || size == 0u) return;
    sb = (MetalBuffer *)rhi_get_resource_typed(g_current_device, src,
                                               RHI_RES_BUFFER);
    db = (MetalBuffer *)rhi_get_resource_typed(g_current_device, dst,
                                               RHI_RES_BUFFER);
    if (sb == NULL || db == NULL) return;
    /* R425: clamp against both buffer sizes. */
    if (size > sb->size) size = sb->size;
    if (size > db->size) size = db->size;
    if (size == 0u) return;
    blit = metal_blit_interlude(cmd, "copy_buffer");
    if (blit == nil) return;
    [blit copyFromBuffer:sb->buffer
            sourceOffset:0u
                toBuffer:db->buffer
       destinationOffset:0u
                    size:(NSUInteger)size];
    [blit endEncoding];
}

void rhi_cmd_bind_material_textures(RHICmdBuffer *cmd, RHITexture albedo, RHITexture mr, RHITexture normal, RHITexture emissive, RHITexture shadow, RHITexture ssao, RHISampler sampler) {
    MetalTexture *td_alb;
    MetalTexture *td_mr;
    MetalTexture *td_nrm;
    MetalTexture *td_em;
    MetalTexture *td_shadow;
    MetalTexture *td_ssao;
    MetalSampler *sd;
    id<MTLTexture> views[9];
    u32 i;
    if (cmd == NULL) return;
    metal_resume_render_pass_if_needed(cmd);
    if (cmd->render_encoder == nil) return;
    td_alb = (MetalTexture *)rhi_get_resource_typed(g_current_device, albedo,
                                                    RHI_RES_TEXTURE);
    sd = (MetalSampler *)rhi_get_resource_typed(g_current_device, sampler,
                                                RHI_RES_SAMPLER);
    if (td_alb == NULL || sd == NULL) return;
    td_mr = (MetalTexture *)rhi_get_resource_typed(g_current_device, mr,
                                                   RHI_RES_TEXTURE);
    td_nrm = (MetalTexture *)rhi_get_resource_typed(g_current_device, normal,
                                                    RHI_RES_TEXTURE);
    td_em = (MetalTexture *)rhi_get_resource_typed(g_current_device, emissive,
                                                   RHI_RES_TEXTURE);
    td_shadow = (MetalTexture *)rhi_get_resource_typed(g_current_device, shadow,
                                                       RHI_RES_TEXTURE);
    td_ssao = (MetalTexture *)rhi_get_resource_typed(g_current_device, ssao,
                                                     RHI_RES_TEXTURE);
    /* VK slot contract (rhi_vk.c:7651-7666): 0=albedo, 1=shadow (explicit;
     * Metal has no legacy global shadow view to fall back to), 2=mr,
     * 3=normal, 4=emissive, 5=ssao, 6-8=IBL slots (albedo fallback);
     * missing slots bind albedo so the flattened texture(unit) indices the
     * Task 10 contract generates stay populated. Combined-sampler parity:
     * one sampler state across all nine. */
    views[0] = td_alb->texture;
    views[1] = td_shadow != NULL ? td_shadow->texture : td_alb->texture;
    views[2] = td_mr != NULL ? td_mr->texture : td_alb->texture;
    views[3] = td_nrm != NULL ? td_nrm->texture : td_alb->texture;
    views[4] = td_em != NULL ? td_em->texture : td_alb->texture;
    views[5] = td_ssao != NULL ? td_ssao->texture : td_alb->texture;
    views[6] = td_alb->texture;
    views[7] = td_alb->texture;
    views[8] = td_alb->texture;
    for (i = 0u; i < 9u; ++i) {
        metal_set_frag_texture(cmd, views[i], (NSUInteger)i);
        metal_set_frag_sampler(cmd, sd->sampler, (NSUInteger)i);
    }
}

void rhi_cmd_bind_material_textures_ibl(RHICmdBuffer *cmd, RHITexture albedo, RHITexture mr, RHITexture normal, RHITexture emissive, RHITexture occlusion, RHITexture shadow, RHITexture ssao, RHISampler sampler, RHITexture brdf_lut, RHICubemap irradiance_map, RHICubemap prefilter_map, const RHITexture *point_shadow_cubes, u32 point_shadow_count) {
    RHITexture handles[7];
    id<MTLTexture> views[7];
    MetalTexture *td_alb, *td_occ;
    MetalTexture *cd_irr, *cd_pref, *cube_fallback = NULL;
    MetalTexture *points[4] = { NULL, NULL, NULL, NULL };
    MetalSampler *sd;
    u32 i;
    if (cmd == NULL || cmd->backend == NULL) return;
    metal_resume_render_pass_if_needed(cmd);
    if (cmd->render_encoder == nil) return;
    td_alb = (MetalTexture *)rhi_get_resource_typed(g_current_device, albedo,
                                                    RHI_RES_TEXTURE);
    sd = (MetalSampler *)rhi_get_resource_typed(g_current_device, sampler,
                                                RHI_RES_SAMPLER);
    if (td_alb == NULL || sd == NULL) return;
    handles[0] = albedo;
    handles[1] = shadow;
    handles[2] = mr;
    handles[3] = normal;
    handles[4] = emissive;
    handles[5] = ssao;
    handles[6] = brdf_lut;
    for (i = 0u; i < 7u; ++i) {
        MetalTexture *td = (MetalTexture *)rhi_get_resource_typed(
            g_current_device, handles[i], RHI_RES_TEXTURE);
        views[i] = td != NULL ? td->texture : td_alb->texture;
    }
    td_occ = (MetalTexture *)rhi_get_resource_typed(g_current_device, occlusion,
                                                    RHI_RES_TEXTURE);
    cd_irr = (MetalTexture *)rhi_get_resource_typed(g_current_device,
        irradiance_map, RHI_RES_CUBEMAP);
    cd_pref = (MetalTexture *)rhi_get_resource_typed(g_current_device,
        prefilter_map, RHI_RES_CUBEMAP);
    if (cd_irr != NULL) cube_fallback = cd_irr;
    else if (cd_pref != NULL) cube_fallback = cd_pref;
    if (point_shadow_count > 4u) point_shadow_count = 4u;
    for (i = 0u; i < point_shadow_count && point_shadow_cubes != NULL; ++i) {
        points[i] = (MetalTexture *)rhi_get_resource_typed(g_current_device,
            point_shadow_cubes[i], RHI_RES_CUBEMAP);
        if (cube_fallback == NULL && points[i] != NULL) cube_fallback = points[i];
    }
    for (i = 0u; i < 7u; ++i)
        metal_set_frag_texture(cmd, views[i], (NSUInteger)i);
    /* Cube slots must never receive a 2D albedo fallback. If no real cube is
     * available, leave the optional slot unbound rather than violating the
     * shader's texturecube argument type. */
    if (cd_irr != NULL || cube_fallback != NULL)
        metal_set_frag_texture(cmd, (cd_irr != NULL ? cd_irr : cube_fallback)->texture, 7u);
    if (cd_pref != NULL || cube_fallback != NULL)
        metal_set_frag_texture(cmd, (cd_pref != NULL ? cd_pref : cube_fallback)->texture, 8u);
    metal_set_frag_texture(cmd, (td_occ != NULL ? td_occ : td_alb)->texture, 9u);
    for (i = 0u; i < 4u; ++i) {
        MetalTexture *cd = points[i] != NULL ? points[i] : cube_fallback;
        if (cd != NULL)
            metal_set_frag_texture(cmd, cd->texture, (NSUInteger)(10u + i));
    }
    for (i = 0u; i < 14u; ++i)
        metal_set_frag_sampler(cmd, sd->sampler, (NSUInteger)i);
}

void rhi_cmd_bind_deferred_gbuf_textures(RHICmdBuffer *cmd, RHITexture albedo_metallic, RHITexture roughness_ao, RHITexture normal, RHITexture depth, RHITexture emissive, RHITexture shadow, RHITexture ssao, RHISampler sampler, RHITexture brdf_lut, RHICubemap irradiance_map, RHICubemap prefilter_map, const RHITexture *point_shadow_cubes, u32 point_shadow_count, RHISampler cube_sampler) {
    /* VK slot parity (rhi_vk.c rhi_cmd_bind_deferred_gbuf_textures, set 0):
     * 0 albedo_metallic, 1 shadow, 2 roughness_ao, 3 normal, 4 depth,
     * 5 ssao, 6 brdf_lut, 7 irradiance, 8 prefilter, 9 emissive,
     * 10..13 point-shadow cubes; every slot samples with `sampler`
     * (cube_sampler is GL-only). Missing 2D slots fall back to albedo. */
    RHITexture handles[10];
    id<MTLTexture> views[10];
    MetalTexture *td_alb;
    MetalTexture *cd_irr, *cd_pref, *cube_fallback = NULL;
    MetalTexture *points[4] = { NULL, NULL, NULL, NULL };
    MetalSampler *sd;
    u32 i;
    (void)cube_sampler;
    if (cmd == NULL || cmd->backend == NULL) return;
    metal_resume_render_pass_if_needed(cmd);
    if (cmd->render_encoder == nil) return;
    td_alb = (MetalTexture *)rhi_get_resource_typed(g_current_device,
                                                    albedo_metallic,
                                                    RHI_RES_TEXTURE);
    sd = (MetalSampler *)rhi_get_resource_typed(g_current_device, sampler,
                                                RHI_RES_SAMPLER);
    if (td_alb == NULL || sd == NULL) return;
    handles[0] = albedo_metallic;
    handles[1] = shadow;
    handles[2] = roughness_ao;
    handles[3] = normal;
    handles[4] = depth;
    handles[5] = ssao;
    handles[6] = brdf_lut;
    handles[7] = RHI_HANDLE_NULL;
    handles[8] = RHI_HANDLE_NULL;
    handles[9] = emissive;
    for (i = 0u; i < 10u; ++i) {
        MetalTexture *td = (MetalTexture *)rhi_get_resource_typed(
            g_current_device, handles[i], RHI_RES_TEXTURE);
        views[i] = td != NULL ? td->texture : td_alb->texture;
    }
    cd_irr = (MetalTexture *)rhi_get_resource_typed(g_current_device,
        irradiance_map, RHI_RES_CUBEMAP);
    cd_pref = (MetalTexture *)rhi_get_resource_typed(g_current_device,
        prefilter_map, RHI_RES_CUBEMAP);
    if (cd_irr != NULL) cube_fallback = cd_irr;
    else if (cd_pref != NULL) cube_fallback = cd_pref;
    if (point_shadow_count > 4u) point_shadow_count = 4u;
    for (i = 0u; i < point_shadow_count && point_shadow_cubes != NULL; ++i) {
        points[i] = (MetalTexture *)rhi_get_resource_typed(g_current_device,
            point_shadow_cubes[i], RHI_RES_CUBEMAP);
        if (cube_fallback == NULL && points[i] != NULL) cube_fallback = points[i];
    }
    for (i = 0u; i < 10u; ++i) {
        if (i == 7u || i == 8u) continue;
        metal_set_frag_texture(cmd, views[i], (NSUInteger)i);
    }
    /* Cube slots never receive a 2D fallback (texturecube argument type). */
    if (cd_irr != NULL || cube_fallback != NULL)
        metal_set_frag_texture(cmd, (cd_irr != NULL ? cd_irr : cube_fallback)->texture, 7u);
    if (cd_pref != NULL || cube_fallback != NULL)
        metal_set_frag_texture(cmd, (cd_pref != NULL ? cd_pref : cube_fallback)->texture, 8u);
    for (i = 0u; i < 4u; ++i) {
        MetalTexture *cd = points[i] != NULL ? points[i] : cube_fallback;
        if (cd != NULL)
            metal_set_frag_texture(cmd, cd->texture, (NSUInteger)(10u + i));
    }
    for (i = 0u; i < 14u; ++i)
        metal_set_frag_sampler(cmd, sd->sampler, (NSUInteger)i);
}

void rhi_cmd_bind_textures_multi(RHICmdBuffer *cmd, RHITexture *textures, int count, RHISampler sampler) {
    MetalSampler *sd;
    int i;
    /* VK contract (rhi_vk.c:7976+): textures[0..count-1] land on consecutive
     * bindings 0..count-1 with ONE combined sampler (postfx passes: TAA x4,
     * ssr/dof/lens_flare/contact_shadow x2, motion_blur x3). A null texture
     * leaves its slot unbound (VK binds NULL_HANDLE; sampling it is the
     * caller's bug and Metal validation says so loudly). */
    if (cmd == NULL || textures == NULL || count <= 0 || count > 6)
        return;
    metal_resume_render_pass_if_needed(cmd);
    if (cmd->render_encoder == nil) return;
    sd = (MetalSampler *)rhi_get_resource_typed(g_current_device, sampler,
                                                RHI_RES_SAMPLER);
    if (sd == NULL) return;
    for (i = 0; i < count; ++i) {
        MetalTexture *td = (MetalTexture *)rhi_get_resource_typed(
            g_current_device, textures[i], RHI_RES_TEXTURE);
        if (td == NULL) continue;
        metal_set_frag_texture(cmd, td->texture, (NSUInteger)i);
        metal_set_frag_sampler(cmd, sd->sampler, (NSUInteger)i);
    }
}

typedef struct {
    f32 clear_color[4];       /* R619 caller-owned bind clear (attachment 0) */
    u32 sample_count;
    RHIFormat color_format;
    RHITexture color_tex;     /* wrapped single-sample textures (reopen path) */
    RHITexture depth_tex;
    /* MSAA machinery (brief Produces): multisample color/depth attachments
     * resolving into the wrapped single-sample textures via
     * storeAction=MultisampleResolve. Currently unreachable through the
     * public API: the shared rhi_offscreen_fbo_desc_validate rejects
     * sample_count>1 because depth_resolve_supported==false (Task 3
     * fail-closed) — same gate shape as VK's vk_offscreen_fbo_create. */
    MetalTexture *msaa_color;   /* nil unless sample_count > 1 */
    MetalTexture *msaa_depth;
} MetalFBOData;

static RHIOffscreenFBO metal_offscreen_fbo_create(RHIDevice *dev, u32 width,
                                                  u32 height,
                                                  RHIFormat color_fmt,
                                                  u32 requested_samples) {
    RHIOffscreenFBO fbo = {0};
    MetalBackend *mb;
    MetalFBOData *fd;
    MetalTexture *color;
    MetalTexture *depth;
    u32 samples = requested_samples == 0u ? 1u : requested_samples;
    u32 idx;
    if (dev == NULL || !rhi_drawable_dimensions_valid(width, height) ||
        !rhi_format_is_color(color_fmt) ||
        rhi_sample_count_bit(samples) == 0u) {
        return fbo;
    }
    mb = (MetalBackend *)dev->backend_data;
    if (mb == NULL || mb->device_lost_latch) return fbo;
    if ((dev->capabilities.color_sample_counts &
         rhi_sample_count_bit(samples)) == 0u ||
        (dev->capabilities.depth_sample_counts &
         rhi_sample_count_bit(samples)) == 0u) {
        return fbo;
    }
    /* VK parity gate: MSAA needs both resolve paths. Metal reports
     * depth_resolve_supported=false (Task 3), so this fails closed today. */
    if (samples > 1u && (!dev->capabilities.color_resolve_supported ||
                         !dev->capabilities.depth_resolve_supported)) {
        return fbo;
    }
    color = metal_render_target_tex_alloc(mb, width, height, color_fmt,
                                          false, 1u);
    depth = metal_render_target_tex_alloc(mb, width, height,
                                          RHI_FORMAT_D32_FLOAT, false, 1u);
    fd = (MetalFBOData *)calloc(1u, sizeof(*fd));
    if (color == NULL || depth == NULL || fd == NULL) {
        if (color != NULL) { [color->texture release]; free(color); }
        if (depth != NULL) { [depth->texture release]; free(depth); }
        free(fd);
        return fbo;
    }
    fd->sample_count = samples;
    fd->color_format = color_fmt;
    /* R617 portable-contract default; R619 lets the caller replace it. */
    fd->clear_color[0] = 0.05f;
    fd->clear_color[1] = 0.05f;
    fd->clear_color[2] = 0.1f;
    fd->clear_color[3] = 1.0f;
    if (samples > 1u) {
        fd->msaa_color = metal_render_target_tex_alloc(mb, width, height,
                                                       color_fmt, false,
                                                       samples);
        fd->msaa_depth = metal_render_target_tex_alloc(mb, width, height,
                                                       RHI_FORMAT_D32_FLOAT,
                                                       false, samples);
        if (fd->msaa_color == NULL || fd->msaa_depth == NULL) {
            if (fd->msaa_color != NULL) {
                [fd->msaa_color->texture release];
                free(fd->msaa_color);
            }
            if (fd->msaa_depth != NULL) {
                [fd->msaa_depth->texture release];
                free(fd->msaa_depth);
            }
            [color->texture release];
            free(color);
            [depth->texture release];
            free(depth);
            free(fd);
            return fbo;
        }
    }
    fbo.color_tex = metal_fbo_texture_slot(dev, color, RHI_RES_TEXTURE);
    fbo.depth_tex = metal_fbo_texture_slot(dev, depth, RHI_RES_TEXTURE);
    fbo.width = width;
    fbo.height = height;
    fbo.sample_count = samples;
    fd->color_tex = fbo.color_tex;
    fd->depth_tex = fbo.depth_tex;
    idx = rhi_alloc_slot(dev);
    dev->slots[idx].ptr = fd;
    dev->slots[idx].type = RHI_RES_FRAMEBUFFER;
    fbo.fb = rhi_make_handle(idx, dev->slots[idx].generation);
    return fbo;
}

RHIOffscreenFBO rhi_offscreen_fbo_create(RHIDevice *dev, u32 width, u32 height) {
    return metal_offscreen_fbo_create(dev, width, height,
                                      RHI_FORMAT_B8G8R8A8_UNORM, 1u);
}

RHIOffscreenFBO rhi_offscreen_fbo_create_fmt(RHIDevice *dev, u32 width, u32 height, RHIFormat color_fmt) {
    return metal_offscreen_fbo_create(dev, width, height, color_fmt, 1u);
}

RHIOffscreenFBO rhi_offscreen_fbo_create_desc(RHIDevice *dev, const RHIOffscreenFBODesc *desc) {
    RHIOffscreenFBO fbo = {0};
    if (dev == NULL ||
        !rhi_offscreen_fbo_desc_validate(&dev->capabilities, desc)) {
        return fbo;
    }
    return metal_offscreen_fbo_create(dev, desc->width, desc->height,
                                      desc->color_format, desc->sample_count);
}

void rhi_offscreen_fbo_destroy(RHIDevice *dev, RHIOffscreenFBO *fbo) {
    MetalBackend *mb;
    MetalFBOData *fd;
    if (dev == NULL || fbo == NULL) return;
    mb = (MetalBackend *)dev->backend_data;
    fd = (MetalFBOData *)rhi_get_resource_typed(dev, fbo->fb,
                                                RHI_RES_FRAMEBUFFER);
    if (fd == NULL) return;
    if (mb != NULL) metal_retire_drain(dev, mb);
    if (fd->msaa_color != NULL) {
        [fd->msaa_color->texture release];
        free(fd->msaa_color);
    }
    if (fd->msaa_depth != NULL) {
        [fd->msaa_depth->texture release];
        free(fd->msaa_depth);
    }
    free(fd);
    rhi_free_slot(dev, fbo->fb);
    metal_fbo_texture_slot_free(dev, fbo->color_tex, RHI_RES_TEXTURE);
    metal_fbo_texture_slot_free(dev, fbo->depth_tex, RHI_RES_TEXTURE);
    memset(fbo, 0, sizeof(*fbo));
}

/* Shared offscreen-FBO pass builder. color_load: Load vs Clear with
 * clear_rgba; depth_load: preserve depth (the in-pass clear_color reopen —
 * VK vkCmdClearAttachments clears color attachment 0 only) vs Clear 1.0
 * (R617 bind). */
static void metal_offscreen_pass_open(RHICmdBuffer *cmd, MetalFBOData *fd,
                                      MetalTexture *color, MetalTexture *depth,
                                      RHIHandle fb, u32 w, u32 h,
                                      bool color_load, const f32 *clear_rgba,
                                      bool depth_load) {
    @autoreleasepool {
        const bool msaa = fd->sample_count > 1u;
        MTLRenderPassDescriptor *pass =
            [MTLRenderPassDescriptor renderPassDescriptor];
        pass.colorAttachments[0].texture =
            msaa ? fd->msaa_color->texture : color->texture;
        pass.colorAttachments[0].storeAction =
            msaa ? MTLStoreActionMultisampleResolve : MTLStoreActionStore;
        if (msaa) pass.colorAttachments[0].resolveTexture = color->texture;
        pass.depthAttachment.texture =
            msaa ? fd->msaa_depth->texture : depth->texture;
        pass.depthAttachment.storeAction =
            msaa ? MTLStoreActionMultisampleResolve : MTLStoreActionStore;
        if (msaa) pass.depthAttachment.resolveTexture = depth->texture;
        if (color_load) {
            pass.colorAttachments[0].loadAction = MTLLoadActionLoad;
        } else {
            pass.colorAttachments[0].loadAction = MTLLoadActionClear;
            pass.colorAttachments[0].clearColor =
                MTLClearColorMake((double)clear_rgba[0],
                                  (double)clear_rgba[1],
                                  (double)clear_rgba[2],
                                  (double)clear_rgba[3]);
        }
        if (depth_load) {
            pass.depthAttachment.loadAction = MTLLoadActionLoad;
        } else {
            pass.depthAttachment.loadAction = MTLLoadActionClear;
            pass.depthAttachment.clearDepth = 1.0;
        }
        metal_open_render_pass(cmd, pass, w, h);
    }
    if (cmd->render_pass_open) {
        metal_set_offscreen_viewport(cmd, w, h);
        cmd->pass_kind = METAL_PASS_OFFSCREEN;
        cmd->pass_target = fb;
        cmd->pass_w = w;
        cmd->pass_h = h;
    }
}

/* R617: bind == fresh target. color clears to the per-FBO clear color
 * (R619), depth to 1.0; bind_load == resume (loadAction=Load, no clears). */
static void metal_offscreen_fbo_bind_impl(RHICmdBuffer *cmd,
                                          RHIOffscreenFBO *fbo, bool load) {
    MetalFBOData *fd;
    MetalTexture *color;
    MetalTexture *depth;
    if (!metal_cmd_in_frame(cmd, load ? "offscreen_fbo_bind_load"
                                      : "offscreen_fbo_bind") ||
        fbo == NULL) {
        return;
    }
    fd = (MetalFBOData *)rhi_get_resource_typed(g_current_device, fbo->fb,
                                                RHI_RES_FRAMEBUFFER);
    color = (MetalTexture *)rhi_get_resource_typed(g_current_device,
                                                   fbo->color_tex,
                                                   RHI_RES_TEXTURE);
    depth = (MetalTexture *)rhi_get_resource_typed(g_current_device,
                                                   fbo->depth_tex,
                                                   RHI_RES_TEXTURE);
    if (fd == NULL || color == NULL || depth == NULL) return;
    metal_offscreen_pass_open(cmd, fd, color, depth, fbo->fb, fbo->width,
                              fbo->height, load, fd->clear_color, load);
}

/* C1: in-pass clear_color reopen on the same offscreen target — attachment
 * 0 Clear with the CALLER's color (overrides the R619 per-FBO color for
 * this pass), depth preserved. */
static void metal_offscreen_clear_reopen(RHICmdBuffer *cmd, RHIHandle fb,
                                         u32 w, u32 h, const f32 *rgba) {
    MetalFBOData *fd = (MetalFBOData *)rhi_get_resource_typed(
        g_current_device, fb, RHI_RES_FRAMEBUFFER);
    MetalTexture *color;
    MetalTexture *depth;
    if (fd == NULL) {
        LOG_ERROR("rhi_metal: clear_color reopen on a stale offscreen FBO");
        return;
    }
    color = (MetalTexture *)rhi_get_resource_typed(g_current_device,
                                                   fd->color_tex,
                                                   RHI_RES_TEXTURE);
    depth = (MetalTexture *)rhi_get_resource_typed(g_current_device,
                                                   fd->depth_tex,
                                                   RHI_RES_TEXTURE);
    if (color == NULL || depth == NULL) return;
    metal_offscreen_pass_open(cmd, fd, color, depth, fb, w, h,
                              false, rgba, true);
}

static void metal_offscreen_depth_clear_reopen(RHICmdBuffer *cmd, RHIHandle fb,
                                               u32 w, u32 h) {
    MetalFBOData *fd = (MetalFBOData *)rhi_get_resource_typed(
        g_current_device, fb, RHI_RES_FRAMEBUFFER);
    MetalTexture *color;
    MetalTexture *depth;
    if (fd == NULL) return;
    color = (MetalTexture *)rhi_get_resource_typed(g_current_device,
        fd->color_tex, RHI_RES_TEXTURE);
    depth = (MetalTexture *)rhi_get_resource_typed(g_current_device,
        fd->depth_tex, RHI_RES_TEXTURE);
    if (color == NULL || depth == NULL) return;
    metal_offscreen_pass_open(cmd, fd, color, depth, fb, w, h,
                              true /* color Load */, NULL, false /* depth Clear */);
}

void rhi_offscreen_fbo_bind(RHICmdBuffer *cmd, RHIOffscreenFBO *fbo) {
    metal_offscreen_fbo_bind_impl(cmd, fbo, false);
}

void rhi_offscreen_fbo_bind_load(RHICmdBuffer *cmd, RHIOffscreenFBO *fbo) {
    metal_offscreen_fbo_bind_impl(cmd, fbo, true);
}

void rhi_offscreen_fbo_unbind(RHICmdBuffer *cmd, u32 screen_w, u32 screen_h) {
    metal_screen_unbind(cmd, screen_w, screen_h);
}

/* R619: caller-owned clear color — stored per-FBO, used by the next bind. */
void rhi_offscreen_fbo_set_clear_color(RHIDevice *dev, RHIOffscreenFBO *fbo, f32 r, f32 g, f32 b, f32 a) {
    MetalFBOData *fd;
    if (dev == NULL || fbo == NULL || !rhi_handle_valid(fbo->fb)) return;
    fd = (MetalFBOData *)rhi_get_resource_typed(dev, fbo->fb,
                                                RHI_RES_FRAMEBUFFER);
    if (fd == NULL) return;
    fd->clear_color[0] = r;
    fd->clear_color[1] = g;
    fd->clear_color[2] = b;
    fd->clear_color[3] = a;
}

typedef struct {
    u32 attachment_count;
    RHIFormat formats[RHI_MRT_MAX_ATTACHMENTS];
    RHITexture color_tex[RHI_MRT_MAX_ATTACHMENTS];   /* reopen path */
    RHITexture depth_tex;
} MetalMRTFBOData;

RHIMRTFBO rhi_mrt_fbo_create(RHIDevice *dev, u32 width, u32 height, const RHIFormat *formats, u32 attachment_count) {
    RHIMRTFBO fbo = {0};
    MetalBackend *mb;
    MetalMRTFBOData *md;
    u32 i;
    u32 idx;
    if (dev == NULL ||
        !rhi_mrt_desc_validate(width, height, formats, attachment_count)) {
        return fbo;
    }
    mb = (MetalBackend *)dev->backend_data;
    if (mb == NULL || mb->device_lost_latch) return fbo;
    md = (MetalMRTFBOData *)calloc(1u, sizeof(*md));
    if (md == NULL) return fbo;
    md->attachment_count = attachment_count;
    for (i = 0u; i < attachment_count; ++i) {
        MetalTexture *ct = metal_render_target_tex_alloc(mb, width, height,
                                                         formats[i], false,
                                                         1u);
        if (ct == NULL) {
            while (i-- > 0u)
                metal_fbo_texture_slot_free(dev, fbo.color_tex[i],
                                            RHI_RES_TEXTURE);
            free(md);
            return fbo;
        }
        md->formats[i] = formats[i];
        fbo.color_tex[i] = metal_fbo_texture_slot(dev, ct, RHI_RES_TEXTURE);
        md->color_tex[i] = fbo.color_tex[i];
    }
    {
        MetalTexture *depth = metal_render_target_tex_alloc(
            mb, width, height, RHI_FORMAT_D32_FLOAT, false, 1u);
        if (depth == NULL) {
            for (i = 0u; i < attachment_count; ++i)
                metal_fbo_texture_slot_free(dev, fbo.color_tex[i],
                                            RHI_RES_TEXTURE);
            free(md);
            return fbo;
        }
        fbo.depth_tex = metal_fbo_texture_slot(dev, depth, RHI_RES_TEXTURE);
        md->depth_tex = fbo.depth_tex;
    }
    fbo.attachment_count = attachment_count;
    fbo.width = width;
    fbo.height = height;
    idx = rhi_alloc_slot(dev);
    dev->slots[idx].ptr = md;
    dev->slots[idx].type = RHI_RES_MRT_FBO;
    fbo.fb = rhi_make_handle(idx, dev->slots[idx].generation);
    return fbo;
}

void rhi_mrt_fbo_destroy(RHIDevice *dev, RHIMRTFBO *fbo) {
    MetalBackend *mb;
    MetalMRTFBOData *md;
    u32 i;
    if (dev == NULL || fbo == NULL) return;
    mb = (MetalBackend *)dev->backend_data;
    md = (MetalMRTFBOData *)rhi_get_resource_typed(dev, fbo->fb,
                                                   RHI_RES_MRT_FBO);
    if (md == NULL) {
        memset(fbo, 0, sizeof(*fbo));
        return;
    }
    if (mb != NULL) metal_retire_drain(dev, mb);
    for (i = 0u; i < md->attachment_count; ++i)
        metal_fbo_texture_slot_free(dev, fbo->color_tex[i], RHI_RES_TEXTURE);
    metal_fbo_texture_slot_free(dev, fbo->depth_tex, RHI_RES_TEXTURE);
    free(md);
    rhi_free_slot(dev, fbo->fb);
    memset(fbo, 0, sizeof(*fbo));
}

/* Shared MRT pass builder. The low byte selects 0 = clear every attachment,
 * 1 = load every attachment, 2+N = clear only attachment N with clear_rgba.
 * Bit 0x100 independently requests a depth clear; mode 0 always clears depth. */
static void metal_mrt_pass_open(RHICmdBuffer *cmd, MetalMRTFBOData *md,
                                RHIHandle fb, u32 w, u32 h, u32 mode,
                                const f32 *clear_rgba) {
    const u32 color_mode = mode & 0xffu;
    const bool depth_clear = color_mode == 0u || (mode & 0x100u) != 0u;
    @autoreleasepool {
        MTLRenderPassDescriptor *pass =
            [MTLRenderPassDescriptor renderPassDescriptor];
        u32 i;
        for (i = 0u; i < md->attachment_count; ++i) {
            MetalTexture *ct = (MetalTexture *)rhi_get_resource_typed(
                g_current_device, md->color_tex[i], RHI_RES_TEXTURE);
            if (ct == NULL) return;
            pass.colorAttachments[i].texture = ct->texture;
            pass.colorAttachments[i].storeAction = MTLStoreActionStore;
            if (color_mode == 0u ||
                (color_mode >= 2u && i == color_mode - 2u)) {
                pass.colorAttachments[i].loadAction = MTLLoadActionClear;
                pass.colorAttachments[i].clearColor =
                    (color_mode >= 2u)
                        ? MTLClearColorMake((double)clear_rgba[0],
                                            (double)clear_rgba[1],
                                            (double)clear_rgba[2],
                                            (double)clear_rgba[3])
                        : MTLClearColorMake(0.0, 0.0, 0.0, 0.0);
            } else {
                pass.colorAttachments[i].loadAction = MTLLoadActionLoad;
            }
        }
        {
            MetalTexture *depth = (MetalTexture *)rhi_get_resource_typed(
                g_current_device, md->depth_tex, RHI_RES_TEXTURE);
            if (depth == NULL) return;
            pass.depthAttachment.texture = depth->texture;
        }
        pass.depthAttachment.storeAction = MTLStoreActionStore;
        pass.depthAttachment.loadAction =
            depth_clear ? MTLLoadActionClear : MTLLoadActionLoad;
        pass.depthAttachment.clearDepth = 1.0;
        metal_open_render_pass(cmd, pass, w, h);
    }
    if (cmd->render_pass_open) {
        metal_set_offscreen_viewport(cmd, w, h);
        cmd->pass_kind = METAL_PASS_MRT;
        cmd->pass_target = fb;
        cmd->pass_w = w;
        cmd->pass_h = h;
    }
}

/* R616: bind clears every color attachment to (0,0,0,0) and depth to 1.0;
 * bind_load preserves all attachments. */
static void metal_mrt_fbo_bind_impl(RHICmdBuffer *cmd, RHIMRTFBO *fbo,
                                    bool load) {
    MetalMRTFBOData *md;
    if (!metal_cmd_in_frame(cmd, load ? "mrt_fbo_bind_load" : "mrt_fbo_bind") ||
        fbo == NULL) {
        return;
    }
    md = (MetalMRTFBOData *)rhi_get_resource_typed(g_current_device, fbo->fb,
                                                   RHI_RES_MRT_FBO);
    if (md == NULL) return;
    metal_mrt_pass_open(cmd, md, fbo->fb, fbo->width, fbo->height,
                        load ? 1u : 0u, NULL);
}

/* C1: in-pass clear_color reopen on the same MRT target. */
static void metal_mrt_clear_reopen(RHICmdBuffer *cmd, RHIHandle fb,
                                   u32 w, u32 h, const f32 *rgba) {
    MetalMRTFBOData *md = (MetalMRTFBOData *)rhi_get_resource_typed(
        g_current_device, fb, RHI_RES_MRT_FBO);
    if (md == NULL) {
        LOG_ERROR("rhi_metal: clear_color reopen on a stale MRT FBO");
        return;
    }
    metal_mrt_pass_open(cmd, md, fb, w, h, 2u, rgba);
}

static void metal_mrt_attachment_clear_reopen(RHICmdBuffer *cmd, RHIHandle fb,
                                   u32 w, u32 h, u32 attachment, const f32 *rgba) {
    MetalMRTFBOData *md = (MetalMRTFBOData *)rhi_get_resource_typed(
        g_current_device, fb, RHI_RES_MRT_FBO);
    if (md == NULL || attachment >= md->attachment_count) {
        LOG_ERROR("rhi_metal: clear attachment %u on an invalid MRT target",
                  attachment);
        return;
    }
    metal_mrt_pass_open(cmd, md, fb, w, h, 2u + attachment, rgba);
}

static void metal_mrt_depth_clear_reopen(RHICmdBuffer *cmd, RHIHandle fb,
                                         u32 w, u32 h) {
    MetalMRTFBOData *md = (MetalMRTFBOData *)rhi_get_resource_typed(
        g_current_device, fb, RHI_RES_MRT_FBO);
    if (md == NULL) return;
    metal_mrt_pass_open(cmd, md, fb, w, h, 1u | 0x100u, NULL);
}

void rhi_mrt_fbo_bind(RHICmdBuffer *cmd, RHIMRTFBO *fbo) {
    metal_mrt_fbo_bind_impl(cmd, fbo, false);
}

void rhi_mrt_fbo_bind_load(RHICmdBuffer *cmd, RHIMRTFBO *fbo) {
    metal_mrt_fbo_bind_impl(cmd, fbo, true);
}

void rhi_mrt_fbo_unbind(RHICmdBuffer *cmd, u32 screen_w, u32 screen_h) {
    metal_screen_unbind(cmd, screen_w, screen_h);
}

typedef struct {
    u32 size;
    RHITexture depth_tex;   /* reopen path (in-pass clear_color, C1) */
} MetalCubemapDepthFBOData;

RHICubemapDepthFBO rhi_cubemap_depth_fbo_create(RHIDevice *dev, u32 size) {
    RHICubemapDepthFBO fbo = {0};
    MetalBackend *mb;
    MetalTexture *depth;
    MetalCubemapDepthFBOData *cd;
    u32 idx;
    if (dev == NULL || size == 0u || size > RHI_MAX_DRAWABLE_DIMENSION)
        return fbo;
    mb = (MetalBackend *)dev->backend_data;
    if (mb == NULL || mb->device_lost_latch) return fbo;
    /* The depth cube is slot-typed RHI_RES_CUBEMAP so the R624 face-major
     * readback path (six D32 faces) works on it unchanged. */
    depth = metal_render_target_tex_alloc(mb, size, size,
                                          RHI_FORMAT_D32_FLOAT, true, 1u);
    cd = (MetalCubemapDepthFBOData *)calloc(1u, sizeof(*cd));
    if (depth == NULL || cd == NULL) {
        if (depth != NULL) { [depth->texture release]; free(depth); }
        free(cd);
        return fbo;
    }
    cd->size = size;
    fbo.depth_tex = metal_fbo_texture_slot(dev, depth, RHI_RES_CUBEMAP);
    cd->depth_tex = fbo.depth_tex;
    fbo.size = size;
    idx = rhi_alloc_slot(dev);
    dev->slots[idx].ptr = cd;
    dev->slots[idx].type = RHI_RES_CUBEMAP_DEPTH_FBO;
    fbo.fb = rhi_make_handle(idx, dev->slots[idx].generation);
    return fbo;
}

void rhi_cubemap_depth_fbo_destroy(RHIDevice *dev, RHICubemapDepthFBO *fbo) {
    MetalBackend *mb;
    MetalCubemapDepthFBOData *cd;
    if (dev == NULL || fbo == NULL) return;
    mb = (MetalBackend *)dev->backend_data;
    cd = (MetalCubemapDepthFBOData *)rhi_get_resource_typed(
        dev, fbo->fb, RHI_RES_CUBEMAP_DEPTH_FBO);
    if (cd == NULL) return;
    if (mb != NULL) metal_retire_drain(dev, mb);
    free(cd);
    rhi_free_slot(dev, fbo->fb);
    metal_fbo_texture_slot_free(dev, fbo->depth_tex, RHI_RES_CUBEMAP);
    memset(fbo, 0, sizeof(*fbo));
}

/* R618: every face bind CLEARS that face's depth to 1.0 (no load twin). */
void rhi_cubemap_depth_fbo_bind_face(RHICmdBuffer *cmd, RHICubemapDepthFBO *fbo, u32 face) {
    MetalCubemapDepthFBOData *cd;
    MetalTexture *depth;
    if (!metal_cmd_in_frame(cmd, "cubemap_depth_fbo_bind_face") ||
        fbo == NULL || face >= 6u) {
        return;
    }
    cd = (MetalCubemapDepthFBOData *)rhi_get_resource_typed(
        g_current_device, fbo->fb, RHI_RES_CUBEMAP_DEPTH_FBO);
    depth = (MetalTexture *)rhi_get_resource_typed(g_current_device,
                                                   fbo->depth_tex,
                                                   RHI_RES_CUBEMAP);
    if (cd == NULL || depth == NULL) {
        LOG_ERROR("rhi_metal: cubemap_depth_fbo_bind_face: target does not resolve");
        return;
    }
    metal_depth_only_pass(cmd, depth->texture, (NSUInteger)face, fbo->size,
                          fbo->size);
    if (cmd->render_pass_open) {
        cmd->pass_kind = METAL_PASS_CUBE_DEPTH;
        cmd->pass_target = fbo->fb;
        cmd->pass_w = fbo->size;
        cmd->pass_h = fbo->size;
        cmd->pass_face = face;
    }
}

void rhi_cubemap_depth_fbo_unbind(RHICmdBuffer *cmd, u32 screen_w, u32 screen_h) {
    metal_screen_unbind(cmd, screen_w, screen_h);
}

/* VK vk_resume_pass_if_needed parity: a compute/blit interlude suspends the
 * open render target (metal_ensure_compute_encoder / metal_blit_interlude);
 * the next graphics call resumes it with loadAction=Load — color and depth
 * content preserved. The suspension record is consumed (or dropped when the
 * target no longer resolves). */
static void metal_resume_render_pass_if_needed(RHICmdBuffer *cmd) {
    u8 kind;
    RHIHandle target;
    RHIPipeline pipe;
    MetalPipeline *pp;
    u32 w, h, face;
    if (cmd == NULL) return;
    if (cmd->render_pass_open ||
        cmd->suspended_kind == METAL_PASS_NONE) {
        return;
    }
    if (cmd->cmd == nil) {
        cmd->suspended_kind = METAL_PASS_NONE;
        return;
    }
    kind = cmd->suspended_kind;
    target = cmd->suspended_target;
    w = cmd->suspended_w;
    h = cmd->suspended_h;
    face = cmd->suspended_face;
    pipe = cmd->suspended_pipeline;
    cmd->suspended_kind = METAL_PASS_NONE;
    cmd->suspended_pipeline = RHI_HANDLE_NULL;
    cmd->resuming = true;
    switch (kind) {
    case METAL_PASS_SCREEN:
        @autoreleasepool {
            metal_open_screen_pass(cmd, w, h, true /* depth Load */);
        }
        break;
    case METAL_PASS_OFFSCREEN: {
        MetalFBOData *fd = (MetalFBOData *)rhi_get_resource_typed(
            g_current_device, target, RHI_RES_FRAMEBUFFER);
        MetalTexture *color;
        MetalTexture *depth;
        if (fd == NULL) break;
        color = (MetalTexture *)rhi_get_resource_typed(
            g_current_device, fd->color_tex, RHI_RES_TEXTURE);
        depth = (MetalTexture *)rhi_get_resource_typed(
            g_current_device, fd->depth_tex, RHI_RES_TEXTURE);
        if (color == NULL || depth == NULL) break;
        metal_offscreen_pass_open(cmd, fd, color, depth, target, w, h,
                                  true /* color Load */, fd->clear_color,
                                  true /* depth Load */);
        break;
    }
    case METAL_PASS_MRT: {
        MetalMRTFBOData *md = (MetalMRTFBOData *)rhi_get_resource_typed(
            g_current_device, target, RHI_RES_MRT_FBO);
        if (md == NULL) break;
        metal_mrt_pass_open(cmd, md, target, w, h, 1u /* bind_load */, NULL);
        break;
    }
    case METAL_PASS_SHADOW: {
        MetalShadowData *sd = (MetalShadowData *)rhi_get_resource_typed(
            g_current_device, target, RHI_RES_FRAMEBUFFER);
        MetalTexture *depth;
        if (sd == NULL) {
            LOG_ERROR("rhi_metal: resume shadow: payload resolve failed (gen %u idx %u)",
                      (unsigned)target.generation, (unsigned)target.index);
            break;
        }
        depth = (MetalTexture *)rhi_get_resource_typed(
            g_current_device, sd->depth_tex, RHI_RES_TEXTURE);
        if (depth == NULL) {
            LOG_ERROR("rhi_metal: resume shadow: depth resolve failed");
            break;
        }
        metal_depth_only_pass_ex(cmd, depth->texture, 0u, w, h,
                                 true /* resume: Load */);
        if (cmd->render_pass_open) {
            cmd->pass_kind = METAL_PASS_SHADOW;
            cmd->pass_target = target;
            cmd->pass_w = w;
            cmd->pass_h = h;
        }
        break;
    }
    case METAL_PASS_CUBE_DEPTH: {
        MetalCubemapDepthFBOData *cd =
            (MetalCubemapDepthFBOData *)rhi_get_resource_typed(
                g_current_device, target, RHI_RES_CUBEMAP_DEPTH_FBO);
        MetalTexture *depth;
        if (cd == NULL) break;
        depth = (MetalTexture *)rhi_get_resource_typed(
            g_current_device, cd->depth_tex, RHI_RES_CUBEMAP);
        if (depth == NULL) break;
        metal_depth_only_pass_ex(cmd, depth->texture, (NSUInteger)face, w, h,
                                 true /* resume: Load */);
        if (cmd->render_pass_open) {
            cmd->pass_kind = METAL_PASS_CUBE_DEPTH;
            cmd->pass_target = target;
            cmd->pass_w = w;
            cmd->pass_h = h;
            cmd->pass_face = face;
        }
        break;
    }
    default:
        break;
    }
    cmd->resuming = false;
    if (!cmd->render_pass_open || cmd->render_encoder == nil) return;
    metal_replay_encoder_state(cmd);
    pp = (MetalPipeline *)rhi_get_resource_typed(g_current_device, pipe,
                                                 RHI_RES_PIPELINE);
    if (pp != NULL && !pp->is_compute) metal_apply_render_pipeline(cmd, pp, pipe);
}

/* C1: in-pass clear_color on a depth-only target — a color clear does not
 * apply (VK would index a nonexistent color attachment), so reopen the
 * depth clear (R618 bind == fresh parity). */
static void metal_depth_target_clear_reopen(RHICmdBuffer *cmd, u8 kind,
                                            RHIHandle fb, u32 w, u32 h,
                                            u32 face) {
    MetalTexture *depth = NULL;
    NSUInteger slice = 0u;
    if (kind == METAL_PASS_SHADOW) {
        MetalShadowData *sd = (MetalShadowData *)rhi_get_resource_typed(
            g_current_device, fb, RHI_RES_FRAMEBUFFER);
        if (sd != NULL)
            depth = (MetalTexture *)rhi_get_resource_typed(
                g_current_device, sd->depth_tex, RHI_RES_TEXTURE);
    } else {
        MetalCubemapDepthFBOData *cd =
            (MetalCubemapDepthFBOData *)rhi_get_resource_typed(
                g_current_device, fb, RHI_RES_CUBEMAP_DEPTH_FBO);
        if (cd != NULL)
            depth = (MetalTexture *)rhi_get_resource_typed(
                g_current_device, cd->depth_tex, RHI_RES_CUBEMAP);
        slice = (NSUInteger)face;
    }
    if (depth == NULL) {
        LOG_ERROR("rhi_metal: clear_color reopen on a stale depth target");
        return;
    }
    metal_depth_only_pass(cmd, depth->texture, slice, w, h);
    if (cmd->render_pass_open) {
        cmd->pass_kind = kind;
        cmd->pass_target = fb;
        cmd->pass_w = w;
        cmd->pass_h = h;
        cmd->pass_face = face;
    }
}

void rhi_cmd_dispatch(RHICmdBuffer *cmd, u32 x, u32 y, u32 z) {
    MetalPipeline *pp;
    id<MTLComputeCommandEncoder> enc;
    NSUInteger max_tg, tg;
    if (cmd == NULL || cmd->backend == NULL) return;
    if (x == 0u || y == 0u || z == 0u) return;
    pp = (MetalPipeline *)rhi_get_resource_typed(g_current_device,
                                                 cmd->bound_pipeline,
                                                 RHI_RES_PIPELINE);
    if (pp == NULL || !pp->is_compute) {
        LOG_ERROR("rhi_metal: dispatch without a bound compute pipeline");
        return;
    }
    enc = metal_ensure_compute_encoder(cmd);
    if (enc == nil) return;
    /* Brief rule: threadgroup = min(pipeline maxTotal, the 64 (8x8)
     * convention). Dispatch counts are in GROUPS (VK parity), so callers
     * divide by the group size themselves. */
    max_tg = pp->compute.maxTotalThreadsPerThreadgroup;
    tg = max_tg < 64u ? max_tg : 64u;
    metal_flush_push(cmd, pp);
    if (!metal_flush_storage_and_bsc(cmd, pp)) {
        LOG_ERROR("rhi_metal: dispatch skipped (buffer-size constants unmet)");
        return;
    }
    [enc dispatchThreadgroups:MTLSizeMake((NSUInteger)x, (NSUInteger)y,
                                          (NSUInteger)z)
        threadsPerThreadgroup:MTLSizeMake(tg, 1u, 1u)];
}

void rhi_cmd_bind_storage_buffer(RHICmdBuffer *cmd, RHIBuffer buf, u32 binding) {
    MetalBuffer *bb;
    MetalPipeline *pp;
    u32 index = binding;
    if (cmd == NULL || cmd->backend == NULL) return;
    bb = (MetalBuffer *)rhi_get_resource_typed(g_current_device, buf,
                                               RHI_RES_BUFFER);
    if (bb == NULL) return;
    if (binding >= 25u) {
        LOG_ERROR("rhi_metal: storage binding %u collides with reserved "
                  "argument slots (25=bsc, 28=AS, 29=push)",
                  (unsigned)binding);
        return;
    }
    pp = (MetalPipeline *)rhi_get_resource_typed(g_current_device,
        cmd->bound_pipeline, RHI_RES_PIPELINE);
    if (pp != NULL && !pp->is_compute) {
        /* `binding` is within the shader's storage set, not an MSL argument
         * index. Textures and texel buffers occupy the preceding sets. */
        u32 set = (pp->desc.uses_textures ? 1u : 0u) +
                  (pp->desc.uses_texel_buffer ? 1u : 0u);
        index = set * 8u + binding;
    }
    if (index >= 25u) {
        LOG_ERROR("rhi_metal: flattened storage index %u is reserved", index);
        return;
    }
    if (pp != NULL && !pp->is_compute) {
        cmd->bound_gfx_storage[index] = buf;
        cmd->bound_gfx_storage_mask |= 1u << index;
        if (cmd->render_encoder == nil) return;
        [cmd->render_encoder setVertexBuffer:bb->buffer offset:0u
                                     atIndex:(NSUInteger)index];
        [cmd->render_encoder setFragmentBuffer:bb->buffer offset:0u
                                       atIndex:(NSUInteger)index];
        return;
    }
    cmd->bound_storage[index] = buf;
    cmd->bound_storage_mask |= 1u << index;
    id<MTLComputeCommandEncoder> enc = metal_ensure_compute_encoder(cmd);
    if (enc == nil) return;
    [enc setBuffer:bb->buffer offset:0u atIndex:(NSUInteger)index];
}

void rhi_cmd_bind_acceleration_structure( RHICmdBuffer *cmd, RHIAccelerationStructure structure, u32 binding) {
    MetalAS *ad;
    id<MTLComputeCommandEncoder> enc;
    if (cmd == NULL || cmd->backend == NULL) return;
    ad = (MetalAS *)rhi_get_resource_typed(g_current_device, structure,
                                           RHI_RES_ACCELERATION_STRUCTURE);
    if (ad == NULL) {
        LOG_ERROR("rhi_metal: bind_acceleration_structure on an invalid handle");
        return;
    }
    /* M4 index allocation (docs/rhi_metal_notes.md): index 28 is the
     * ray-query acceleration-structure slot — clear of the flattened
     * resources (0..24), spvBufferSizeConstants (25) and push constants
     * (29). The RHI binding argument is 0 in the
     * engine's only call pattern; anything else is rejected loudly. */
    if (binding != 0u) {
        LOG_ERROR("rhi_metal: bind_acceleration_structure binding %u unsupported (v1)",
                  (unsigned)binding);
        return;
    }
    enc = metal_ensure_compute_encoder(cmd);
    if (enc == nil) return;
    if (![enc respondsToSelector:@selector(setAccelerationStructure:atBufferIndex:)]) {
        LOG_ERROR("rhi_metal: setAccelerationStructure unavailable on this host");
        return;
    }
    [enc setAccelerationStructure:ad->structure atBufferIndex:28u];
}

void rhi_cmd_memory_barrier(RHICmdBuffer *cmd) {
    if (cmd == NULL) return;
    /* Metal auto-tracks hazards across encoder boundaries; the explicit
     * barrier only matters between dispatches on ONE compute encoder
     * (VK's in-command-buffer pipeline barrier analogue). */
    if (cmd->compute_encoder != nil) {
        [cmd->compute_encoder
            memoryBarrierWithScope:MTLBarrierScopeBuffers |
                                   MTLBarrierScopeTextures];
    } else if (cmd->render_encoder != nil) {
        /* Review note M5: a barrier requested mid-render-pass is silently
         * dropped (Metal tracks render-pass hazards itself) — say so once. */
        static bool warned_render_barrier = false;
        if (!warned_render_barrier) {
            LOG_WARN("rhi_metal: memory_barrier inside a render pass is a no-op");
            warned_render_barrier = true;
        }
    }
}

void rhi_cmd_bind_image_texture(RHICmdBuffer *cmd, RHITexture tex, u32 unit, u32 mip_level, bool write_only) {
    MetalTexture *td;
    id<MTLComputeCommandEncoder> enc;
    id<MTLTexture> view;
    (void)write_only;   /* Metal has no per-binding access mode; usage covers it */
    if (cmd == NULL || cmd->backend == NULL) return;
    td = (MetalTexture *)rhi_get_resource_typed(g_current_device, tex,
                                                RHI_RES_TEXTURE);
    if (td == NULL || mip_level >= td->mip_levels) return;
    enc = metal_ensure_compute_encoder(cmd);
    if (enc == nil) return;
    view = td->texture;
    if (mip_level > 0u) {
        /* newTextureViewWithPixelFormat: returns +1 (new* rule). */
        view = [td->texture
            newTextureViewWithPixelFormat:td->texture.pixelFormat
                              textureType:MTLTextureType2D
                                   levels:NSMakeRange((NSUInteger)mip_level, 1u)
                                   slices:NSMakeRange(0u, 1u)];
        if (view == nil) {
            LOG_ERROR("rhi_metal: mip %u texture view failed",
                      (unsigned)mip_level);
            return;
        }
    }
    [enc setTexture:view atIndex:(NSUInteger)unit];
    if (view != td->texture) [view release];
}

void rhi_cmd_bind_image_cubemap_face(RHICmdBuffer *cmd, RHICubemap cm, u32 face, u32 mip, u32 unit, bool write_only) {
    MetalTexture *cd;
    id<MTLComputeCommandEncoder> enc;
    id<MTLTexture> view;
    (void)write_only;
    if (cmd == NULL || cmd->backend == NULL || face >= 6u) return;
    cd = (MetalTexture *)rhi_get_resource_typed(g_current_device, cm,
                                                RHI_RES_CUBEMAP);
    if (cd == NULL || mip >= cd->mip_levels) return;
    enc = metal_ensure_compute_encoder(cmd);
    if (enc == nil) return;
    /* A single cube face binds as a 2D view of slice `face`, level `mip`.
     * newTextureViewWithPixelFormat: returns +1 (new* rule). */
    view = [cd->texture
        newTextureViewWithPixelFormat:cd->texture.pixelFormat
                          textureType:MTLTextureType2D
                               levels:NSMakeRange((NSUInteger)mip, 1u)
                               slices:NSMakeRange((NSUInteger)face, 1u)];
    if (view == nil) {
        LOG_ERROR("rhi_metal: cube face %u view failed", (unsigned)face);
        return;
    }
    [enc setTexture:view atIndex:(NSUInteger)unit];
    [view release];
}

/* Compute sampler_mip set binding (IBL capture / Hi-Z paths). VK compute
 * layout parity: sampler_mip is set 2, and `unit` is the binding within it;
 * the Task 10 flattening maps combined samplers to set*4+binding, so the
 * MSL texture/sampler index = 2*4+unit = 8+unit (u_env_map (2,1) -> 9,
 * pinned by Metal validation). */
static void metal_compute_bind_tex_smp(RHICmdBuffer *cmd, id<MTLTexture> tex,
                                       id<MTLSamplerState> smp, u32 unit) {
    id<MTLComputeCommandEncoder> enc = metal_ensure_compute_encoder(cmd);
    u32 index;
    if (enc == nil) return;
    index = 8u + unit;
    if (tex != nil) [enc setTexture:tex atIndex:(NSUInteger)index];
    if (smp != nil) [enc setSamplerState:smp atIndex:(NSUInteger)index];
}

void rhi_cmd_bind_cubemap_sampler(RHICmdBuffer *cmd, RHICubemap cm, RHISampler sampler, u32 unit) {
    MetalTexture *cd;
    MetalSampler *sd;
    if (cmd == NULL || cmd->backend == NULL) return;
    cd = (MetalTexture *)rhi_get_resource_typed(g_current_device, cm,
                                                RHI_RES_CUBEMAP);
    sd = (MetalSampler *)rhi_get_resource_typed(g_current_device, sampler,
                                                RHI_RES_SAMPLER);
    if (cd == NULL || sd == NULL) return;
    metal_compute_bind_tex_smp(cmd, cd->texture, sd->sampler, unit);
}

/* Bind a full 2D texture (mip 0) + sampler for a compute pipeline's
 * sampler_mip set (same index contract as bind_cubemap_sampler). */
void rhi_cmd_bind_texture_compute(RHICmdBuffer *cmd, RHITexture tex, RHISampler sampler, u32 unit) {
    MetalTexture *td;
    MetalSampler *sd;
    if (cmd == NULL || cmd->backend == NULL) return;
    td = (MetalTexture *)rhi_get_resource_typed(g_current_device, tex,
                                                RHI_RES_TEXTURE);
    sd = (MetalSampler *)rhi_get_resource_typed(g_current_device, sampler,
                                                RHI_RES_SAMPLER);
    if (td == NULL || sd == NULL) return;
    metal_compute_bind_tex_smp(cmd, td->texture, sd->sampler, unit);
}

void rhi_cmd_bind_texture_mip(RHICmdBuffer *cmd, RHITexture tex, RHISampler sampler, u32 unit, u32 mip_level) {
    MetalTexture *td;
    MetalSampler *sd;
    id<MTLComputeCommandEncoder> enc;
    id<MTLTexture> view;
    u32 index;
    if (cmd == NULL || cmd->backend == NULL) return;
    td = (MetalTexture *)rhi_get_resource_typed(g_current_device, tex,
                                                RHI_RES_TEXTURE);
    sd = (MetalSampler *)rhi_get_resource_typed(g_current_device, sampler,
                                                RHI_RES_SAMPLER);
    if (td == NULL || sd == NULL || mip_level >= td->mip_levels) return;
    view = td->texture;
    if (mip_level > 0u) {
        /* newTextureViewWithPixelFormat: returns +1 (new* rule). */
        view = [td->texture
            newTextureViewWithPixelFormat:td->texture.pixelFormat
                              textureType:MTLTextureType2D
                                   levels:NSMakeRange((NSUInteger)mip_level, 1u)
                                   slices:NSMakeRange(0u, 1u)];
        if (view == nil) {
            LOG_ERROR("rhi_metal: mip %u texture view failed",
                      (unsigned)mip_level);
            return;
        }
    }
    enc = metal_ensure_compute_encoder(cmd);
    if (enc == nil) {
        if (view != td->texture) [view release];
        return;
    }
    index = 8u + unit;   /* see metal_compute_bind_tex_smp */
    [enc setTexture:view atIndex:(NSUInteger)index];
    [enc setSamplerState:sd->sampler atIndex:(NSUInteger)index];
    if (view != td->texture) [view release];
}

void rhi_cmd_transition_depth_to_read(RHICmdBuffer *cmd, RHITexture depth_tex) {
    /* Metal depth targets are created with ShaderRead usage and have no
     * VK-style layout transition; the following pass change ends the writer. */
    (void)cmd;
    (void)depth_tex;
}

bool rhi_screenshot(RHIDevice *dev, u32 x, u32 y, u32 w, u32 h, u8 *pixels, usize pixel_bytes) {
    MetalBackend *mb;
    bool ok = false;
    if (dev == NULL || pixels == NULL) return false;
    mb = (MetalBackend *)dev->backend_data;
    if (mb == NULL || mb->device_lost_latch) return false;
    /* R577 parity: legal only between acquire and present. The drawable is
     * retained from frame_begin to present, so a post-frame_end /
     * pre-present call (the engine's capture point, main.c) still has it. */
    if ((!mb->frame_started && !mb->frame_submitted) || mb->drawable == nil) {
        LOG_ERROR("rhi_metal: rhi_screenshot outside an acquired frame is "
                  "illegal (no drawable) — call between frame_begin and present");
        return false;
    }
    if (!rhi_screenshot_region_validate(x, y, w, h, dev->width, dev->height,
                                        pixel_bytes)) {
        return false;
    }
    /* Bounded drain (never a bare waitUntilCompleted — Task 4 rule).
     * Rendering recorded into the still-uncommitted in-flight frame is not
     * visible, same as VK's device-wide wait. */
    if (metal_drain(dev, mb) != RHI_RESULT_OK) return false;
    @autoreleasepool {
        const usize row_bytes = (usize)w * 4u;
        /* newBufferWithLength: returns +1 (new* rule) — released on every
         * pool exit below (review fix I1). */
        id<MTLBuffer> staging =
            [mb->device newBufferWithLength:(NSUInteger)(row_bytes * h)
                                    options:MTLResourceStorageModeShared];
        id<MTLCommandBuffer> cmd;
        id<MTLBlitCommandEncoder> blit;
        if (staging == nil) {
            LOG_ERROR("rhi_metal: screenshot staging allocation failed");
            return false;
        }
        cmd = [mb->queue commandBuffer];
        if (cmd == nil) {
            LOG_ERROR("rhi_metal: screenshot command buffer failed");
            [staging release];
            return false;
        }
        blit = [cmd blitCommandEncoder];
        /* Native byte order (BGRA8 swapchain -> B,G,R,A), same as VK's raw
         * vkCmdCopyImageToBuffer of its BGRA image. */
        [blit copyFromTexture:mb->drawable.texture
                  sourceSlice:0u
                  sourceLevel:0u
                 sourceOrigin:MTLOriginMake((NSUInteger)x, (NSUInteger)y, 0u)
                   sourceSize:MTLSizeMake((NSUInteger)w, (NSUInteger)h, 1u)
                     toBuffer:staging
            destinationOffset:0u
       destinationBytesPerRow:(NSUInteger)row_bytes
     destinationBytesPerImage:(NSUInteger)(row_bytes * h)];
        [blit endEncoding];
        if (metal_commit_wait(dev, mb, cmd) != RHI_RESULT_OK) {
            [staging release];
            return false;
        }
        /* Row-order contract (rhi.h): top-left origin, rows top-down on
         * every backend. Metal blit rows are already top-down. */
        memcpy(pixels, staging.contents, (usize)row_bytes * h);
        [staging release];
        ok = true;
    }
    return ok;
}

/* ---- Task 9: GPU timer (MTLCounterSampleBuffer timestamps) ----
 * Apple GPUs (observed G14/M2) support only
 * MTLCounterSamplingPointAtStageBoundary — sampling is legal on RENDER
 * encoders only (compute/blit assert at runtime). begin/end called while
 * no render pass is open pend on the cmd buffer and land at the next pass
 * open of the same frame (metal_drain_pending_timer_samples). */
struct RHIGPUTimer {
    RHIDevice *owner;
    id<MTLCounterSampleBuffer> csb;   /* two timestamp samples; nil if unsupported */
    u64 pending_frame_value;          /* frame_event value that completes the samples */
    u32 sampled_mask;                 /* bit0/bit1: index 0/1 actually recorded */
    bool supported;
    bool result_ready;
    bool warned;                      /* warn-once degraded mode */
};

static void metal_gpu_timer_sample(RHIGPUTimer *t, NSUInteger index);

/* Drains pended begin/end samples onto the just-opened render encoder
 * (called from metal_open_render_pass). */
static void metal_drain_pending_timer_samples(RHICmdBuffer *cmd) {
    u32 i;
    if (cmd == NULL || cmd->render_encoder == nil) return;
    for (i = 0u; i < cmd->pending_count; ++i) {
        RHIGPUTimer *t = cmd->pending_timers[i];
        MetalBackend *mb;
        if (t == NULL || t->csb == nil) continue;
        [cmd->render_encoder sampleCountersInBuffer:t->csb
                                      atSampleIndex:(NSUInteger)cmd->pending_indices[i]
                                        withBarrier:YES];
        t->sampled_mask |= 1u << cmd->pending_indices[i];
        /* The sample lands in the CURRENT frame — retarget the completion
         * gate so a sample pended across a frame boundary cannot be read
         * early from stale counter data. */
        mb = g_current_device != NULL
            ? (MetalBackend *)g_current_device->backend_data : NULL;
        if (mb != NULL) t->pending_frame_value = mb->frame_counter;
    }
    cmd->pending_count = 0u;
}

RHIGPUTimer *rhi_gpu_timer_create(RHIDevice *dev) {
    MetalBackend *mb;
    RHIGPUTimer *t;
    if (dev == NULL) return NULL;
    mb = (MetalBackend *)dev->backend_data;
    if (mb == NULL) return NULL;
    t = (RHIGPUTimer *)calloc(1u, sizeof(*t));
    if (t == NULL) return NULL;
    t->owner = dev;
    /* macOS 10.15+; not every device/family supports stage-boundary
     * timestamp sampling — degrade to a warn-once zero timer instead of
     * failing device creation paths.
     *
     * Metal 4 runtime caveat (observed on this plan's M2 host, macOS 26 /
     * SDK 26.5): supportsCounterSampling:AtStageBoundary returns YES on
     * Apple-family GPUs, but sampleCountersInBuffer: on ANY encoder type
     * (render/compute/blit) aborts the process with "not supported on this
     * device" — an uncatchable hard assert, not an NSException (probed with
     * @try/@catch). There is no safe runtime probe, so the Metal 4 runtime
     * (macOS 26+) is statically gated to the degraded path on every GPU
     * family. The Metal 4 replacement (MTL4CounterHeap) is out of this
     * plan's scope. */
    {
        /* Review fix I3: the failure mode is an uncatchable abort, so gate
         * conservatively on the runtime alone — every GPU family on the
         * Metal 4 runtime (macOS 26+) takes the degraded path. The SDK macro
         * only guards compile-time symbol availability. */
        bool metal4_runtime = false;
#if defined(__MAC_OS_X_VERSION_MAX_ALLOWED) && __MAC_OS_X_VERSION_MAX_ALLOWED >= 260000
        if (@available(macOS 26.0, *)) {
            metal4_runtime = true;
        }
#endif
        if (metal4_runtime ||
            ![mb->device supportsCounterSampling:MTLCounterSamplingPointAtStageBoundary]) {
            t->supported = false;
            return t;
        }
    }
    t->supported = true;
    @autoreleasepool {
        NSArray<id<MTLCounterSet>> *sets = mb->device.counterSets;
        id<MTLCounterSet> timestamps = nil;
        MTLCounterSampleBufferDescriptor *d;
        NSError *err = nil;
        for (id<MTLCounterSet> set in sets) {
            if ([set.name isEqualToString:MTLCommonCounterSetTimestamp]) {
                timestamps = set;
                break;
            }
        }
        if (timestamps == nil) {
            LOG_WARN("rhi_metal: timestamp counter set missing; gpu timer degraded");
            t->supported = false;
            return t;
        }
        d = [[MTLCounterSampleBufferDescriptor alloc] init];
        /* Newer SDKs (26+) expose a single counterSet (the counterSets
         * array property is gone). One timestamp set is all we sample. */
        d.counterSet = timestamps;
        d.sampleCount = 2u;
        d.storageMode = MTLStorageModeShared;
        /* newCounterSampleBufferWithDescriptor: returns +1 (new* rule). */
        t->csb = [mb->device newCounterSampleBufferWithDescriptor:d
                                                            error:&err];
        [d release];
        if (t->csb == nil) {
            LOG_WARN("rhi_metal: counter sample buffer failed (%s); timer degraded",
                     err != nil ? [[err localizedDescription] UTF8String]
                                : "(no error info)");
            t->supported = false;
        }
    }
    return t;
}

void rhi_gpu_timer_destroy(RHIDevice *dev, RHIGPUTimer *t) {
    if (t == NULL) return;
    if (dev != NULL && dev == t->owner) {
        MetalBackend *mb = (MetalBackend *)dev->backend_data;
        if (mb != NULL) {
            /* Review fix I2: sweep pended samples pointing at this timer —
             * the pending list holds raw pointers and the drain at the next
             * pass open would otherwise dereference freed memory. */
            RHICmdBuffer *cmd = mb->frame_cmd;
            if (cmd != NULL) {
                u32 i = 0u;
                while (i < cmd->pending_count) {
                    if (cmd->pending_timers[i] == t) {
                        cmd->pending_count--;
                        memmove(&cmd->pending_timers[i],
                                &cmd->pending_timers[i + 1u],
                                (cmd->pending_count - i) *
                                    sizeof(cmd->pending_timers[0]));
                        memmove(&cmd->pending_indices[i],
                                &cmd->pending_indices[i + 1u],
                                (cmd->pending_count - i) *
                                    sizeof(cmd->pending_indices[0]));
                    } else {
                        ++i;
                    }
                }
            }
            metal_retire_drain(dev, mb);
        }
    }
    [t->csb release];
    free(t);
}

/* Sample into the open render encoder; otherwise pend on the cmd buffer
 * (applied at the next pass open this frame — stage-boundary sampling is
 * render-encoder-only on Apple GPUs; compute/blit encoders assert).
 * Degraded timers (csb == nil) still pend: the drain skips them, and the
 * destroy sweep (review fix I2) is exercised uniformly on every host. */
static void metal_gpu_timer_sample(RHIGPUTimer *t, NSUInteger index) {
    MetalBackend *mb;
    RHICmdBuffer *cmd;
    if (g_current_device != t->owner) return;
    mb = (MetalBackend *)t->owner->backend_data;
    cmd = mb != NULL ? mb->frame_cmd : NULL;
    if (cmd == NULL || cmd->cmd == nil) {
        LOG_ERROR("rhi_metal: gpu timer sample outside a live frame");
        return;
    }
    if (t->csb != nil && cmd->render_encoder != nil) {
        [cmd->render_encoder sampleCountersInBuffer:t->csb
                                      atSampleIndex:index
                                        withBarrier:YES];
        t->sampled_mask |= 1u << index;
        return;
    }
    if (cmd->pending_count < 8u) {
        cmd->pending_timers[cmd->pending_count] = t;
        cmd->pending_indices[cmd->pending_count] = (u32)index;
        cmd->pending_count++;
    } else {
        LOG_WARN("rhi_metal: gpu timer pending-sample list full; sample dropped");
    }
}

void rhi_gpu_timer_begin(RHIGPUTimer *t) {
    if (t == NULL) return;
    t->sampled_mask = 0u;
    t->result_ready = false;
    metal_gpu_timer_sample(t, 0u);
}

void rhi_gpu_timer_end(RHIGPUTimer *t) {
    MetalBackend *mb;
    if (t == NULL) return;
    metal_gpu_timer_sample(t, 1u);
    if (!t->supported || g_current_device != t->owner) return;
    mb = (MetalBackend *)t->owner->backend_data;
    if (mb == NULL) return;
    /* The samples complete when the recording frame's signal lands. */
    t->pending_frame_value = mb->frame_counter;
    t->result_ready = true;
}

f64 rhi_gpu_timer_elapsed_ms(RHIGPUTimer *t) {
    MetalBackend *mb;
    u64 ts[2] = { 0u, 0u };
    NSData *data;
    mach_timebase_info_data_t tb;
    if (t == NULL) return 0.0;
    if (!t->supported || t->csb == nil) {
        if (!t->warned) {
            LOG_WARN("rhi_metal: gpu timer unsupported on this device; elapsed_ms is 0");
            t->warned = true;
        }
        return 0.0;
    }
    /* Both samples must have actually landed (a begin/end pended past
     * frame_end leaves the mask incomplete). */
    if (!t->result_ready || t->sampled_mask != 3u || g_current_device != t->owner)
        return 0.0;
    mb = (MetalBackend *)t->owner->backend_data;
    if (mb == NULL) return 0.0;
    /* Poll availability (VK R430 parity: never wait on a not-yet-completed
     * frame's samples). */
    if (mb->frame_event == nil ||
        mb->frame_event.signaledValue < t->pending_frame_value) {
        return 0.0;
    }
    @autoreleasepool {
        /* resolveCounterRange: returns an AUTORELEASED NSData — dereference
         * strictly inside the pool (review fix C1: the previous code used
         * data.bytes after the pool drained = UAF). */
        data = [t->csb resolveCounterRange:NSMakeRange(0u, 2u)];
        if (data == nil || data.length < sizeof(ts)) return 0.0;
        memcpy(ts, data.bytes, sizeof(ts));
    }
    if (ts[1] < ts[0]) return 0.0;
    /* Counter timestamps are mach absolute time ticks. */
    (void)mach_timebase_info(&tb);
    if (tb.denom == 0u) return 0.0;
    return (f64)(ts[1] - ts[0]) * (f64)tb.numer / (f64)tb.denom / 1.0e6;
}

/* ---- ENGINE_RHI_TEST hooks ---- */
#ifdef ENGINE_RHI_TEST
/* Task 6: arms the suspended-acquire BUSY defense for
 * test_rhi_metal_frame_lifecycle. Private export (no public header);
 * production iOS hosts self-discipline — they make no frame API calls while
 * backgrounded — so there is intentionally no production setter. */
void rhi_test_metal_set_suspended(RHIDevice *dev, bool suspended) {
    MetalBackend *mb = dev != NULL ? (MetalBackend *)dev->backend_data : NULL;
    if (mb != NULL) mb->suspended = suspended;
}

void rhi_test_metal_set_private_texel(bool enabled) {
    rhi_test_private_texel = enabled;
}

/* Task 10: the production shader path is manifest-only (fail closed on a
 * hash miss); the Task 8/9 contract tests drive pipelines with inline MSL
 * sources, which compile through this hook (the pre-Task-10 interim path).
 * Entry-point convention stays vs_main / fs_main / cs_main. */
RHIShader rhi_test_metal_shader_create_source(RHIDevice *dev,
                                              const char *source, usize len,
                                              const char *entry,
                                              bool is_fragment) {
    return metal_shader_create_source(dev, source, len, entry, is_fragment);
}

/* Task 12 review (M1): exposes the VK-ABI -> MTL TLAS record conversion
 * for component-level assertions (identity transforms are
 * transpose-invisible). Copies the converted 68-byte descriptor out. */
bool rhi_test_metal_convert_tlas_record(RHIDevice *dev, const u8 *rec,
                                        u8 *out68) {
    MTLAccelerationStructureUserIDInstanceDescriptor conv;
    id<MTLAccelerationStructure> blas = nil;
    _Static_assert(sizeof(conv) == 68u, "UserID instance descriptor layout");
    if (dev == NULL || rec == NULL || out68 == NULL) return false;
    memset(&conv, 0, sizeof(conv));
    if (!metal_as_convert_tlas_record(dev, rec, &conv, &blas)) return false;
    memcpy(out68, &conv, sizeof(conv));
    return true;
}
#endif
