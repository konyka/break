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
 * Every other entry point logs and fails closed until its family is filled
 * in by the later plan-C tasks. */
#import <Metal/Metal.h>
#import <QuartzCore/CAMetalLayer.h>

#include <rhi/rhi.h>
#include <rhi/rhi_backend_internal.h>
#include <rhi/rhi_metal_format.h>
#include <rhi/rhi_native_vulkan.h>
#include <core/log.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

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
    bool frame_started;           /* acquire done, submit not yet */
    bool frame_submitted;         /* submit done, present not yet */
    bool device_lost_latch;       /* sticky; mirrors rhi_vk.c device-lost semantics */
    bool suspended;               /* iOS host-driven pause: acquire returns BUSY */
    RHIFormat swapchain_format;   /* from the layer's pixelFormat */
    u32 max_push_bytes;           /* 256 staging, mirrors VK push staging */
} MetalBackend;

#define RHI_METAL_MAX_PUSH_BYTES 256u

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
    if (!mb->device_lost_latch) {
        mb->device_lost_latch = true;
        LOG_ERROR("rhi_metal: device lost (%s) — latched; blocking waits now fail fast",
                  where);
    }
    dev->status = RHI_DEVICE_STATUS_LOST;
    rhi_device_set_lifecycle_result(dev, RHI_RESULT_DEVICE_LOST);
}

/* Latch on MTLCommandBufferStatusError. MTLCommandBufferErrorDeviceRemoved
 * only surfaces on macOS 13+; older releases report a generic error code —
 * both latch (fail-closed). */
static void metal_check_cmd_error(RHIDevice *dev, MetalBackend *mb,
                                  id<MTLCommandBuffer> cmd, const char *where) {
    if (cmd.status != MTLCommandBufferStatusError) return;
    NSError *err = cmd.error;
    long code = err != nil ? (long)err.code : -1L;
    if (code == (long)MTLCommandBufferErrorDeviceRemoved) {
        LOG_ERROR("rhi_metal: command buffer at %s failed with "
                  "MTLCommandBufferErrorDeviceRemoved", where);
    } else {
        LOG_ERROR("rhi_metal: command buffer at %s failed (error code %ld)",
                  where, code);
    }
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
};

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
    mb->device = device;
    mb->queue = queue;
    mb->layer = layer;               /* not owned */
    mb->swapchain_format = swapchain_format;
    mb->max_push_bytes = RHI_METAL_MAX_PUSH_BYTES;
    rhi_init_freelist(dev);
    dev->backend_data = mb;
    dev->width = w;
    dev->height = h;
    dev->capabilities.backend = RHI_BACKEND_METAL;
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
                if (mb->frame_cmd->render_encoder != nil) {
                    [mb->frame_cmd->render_encoder endEncoding];
                    [mb->frame_cmd->render_encoder release];
                    mb->frame_cmd->render_encoder = nil;
                }
                [mb->frame_cmd->cmd release];   /* nil between frames; no-op then */
                free(mb->frame_cmd);
                mb->frame_cmd = NULL;
            }
            [mb->library release];       /* nil until Task 10; releasing nil is a no-op */
            [mb->frame_event release];   /* created lazily by rhi_frame_begin */
            [mb->drain_event release];   /* created lazily by metal_drain */
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
    if (mb->suspended) {   /* iOS host-driven pause (Task 14 wires the setter) */
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
    cmd->cmd = [mtl_cmd retain];   /* autoreleased by the queue; we hold it to frame_end */
    cmd->render_encoder = nil;
    cmd->render_pass_open = false;
    /* A fresh drawable's contents are undefined, so the first pass of every
     * frame clears (default opaque black; rhi_cmd_clear_color overrides). */
    cmd->clear_color[0] = 0.0f;
    cmd->clear_color[1] = 0.0f;
    cmd->clear_color[2] = 0.0f;
    cmd->clear_color[3] = 1.0f;
    cmd->clear_pending = true;
    mb->frame_started = true;
    mb->frame_submitted = false;
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
    if (cmd != NULL && cmd->render_encoder != nil) {
        [cmd->render_encoder endEncoding];
        [cmd->render_encoder release];
        cmd->render_encoder = nil;
        cmd->render_pass_open = false;
    }
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
    if (mb->drawable != nil) {
        [mb->drawable release];   /* Metal retains it for the scheduled present */
        mb->drawable = nil;
    }
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
    dev->frame_damage_requested = false;
    dev->frame_damage_count = 0u;
    dev->frame_current_damage_count = 0u;
    dev->frame_partial_active = false;
    rhi_frame_owner_release(dev);
}

void rhi_set_vsync(RHIDevice *dev, bool enabled) {
    MetalBackend *mb = dev != NULL ? (MetalBackend *)dev->backend_data : NULL;
    if (mb == NULL || mb->layer == nil) return;
    /* displaySyncEnabled is macOS 10.13+; guard for older SDKs/hosts. */
    if ([mb->layer respondsToSelector:@selector(setDisplaySyncEnabled:)])
        mb->layer.displaySyncEnabled = enabled ? YES : NO;
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

bool rhi_backend_cmd_build_blas_one_triangle( RHICmdBuffer *cmd, RHIDevice *dev, RHIAccelerationStructure blas, const RHIBLASOneTriangleDesc *desc, RHIBuffer scratch_buffer, usize scratch_offset) {
    LOG_ERROR("rhi_metal: rhi_backend_cmd_build_blas_one_triangle not implemented");
    (void)cmd;
    (void)dev;
    (void)blas;
    (void)desc;
    (void)scratch_buffer;
    (void)scratch_offset;
    return false;
}

u64 rhi_backend_acceleration_structure_get_device_address( RHIDevice *dev, RHIAccelerationStructure structure) {
    LOG_ERROR("rhi_metal: rhi_backend_acceleration_structure_get_device_address not implemented");
    (void)dev;
    (void)structure;
    return 0u;
}

bool rhi_backend_tlas_one_instance_get_build_sizes( RHIDevice *dev, RHIBuffer instance_buffer, RHIAccelerationStructureBuildSizes *out_sizes) {
    LOG_ERROR("rhi_metal: rhi_backend_tlas_one_instance_get_build_sizes not implemented");
    (void)dev;
    (void)instance_buffer;
    (void)out_sizes;
    return false;
}

bool rhi_backend_cmd_build_tlas_one_instance( RHICmdBuffer *cmd, RHIDevice *dev, RHIAccelerationStructure tlas, RHIBuffer instance_buffer, RHIBuffer scratch_buffer, usize scratch_offset) {
    LOG_ERROR("rhi_metal: rhi_backend_cmd_build_tlas_one_instance not implemented");
    (void)cmd;
    (void)dev;
    (void)tlas;
    (void)instance_buffer;
    (void)scratch_buffer;
    (void)scratch_offset;
    return false;
}

bool rhi_backend_acceleration_structure_get_vk_handle( RHIDevice *dev, RHIAccelerationStructure structure, void **out_handle) {
    LOG_ERROR("rhi_metal: rhi_backend_acceleration_structure_get_vk_handle not implemented");
    (void)dev;
    (void)structure;
    (void)out_handle;
    return false;
}

bool rhi_blas_one_triangle_get_build_sizes( RHIDevice *dev, const RHIBLASOneTriangleDesc *desc, RHIAccelerationStructureBuildSizes *out_sizes) {
    LOG_ERROR("rhi_metal: rhi_blas_one_triangle_get_build_sizes not implemented");
    (void)dev;
    (void)desc;
    (void)out_sizes;
    return false;
}

RHIAccelerationStructure rhi_backend_acceleration_structure_create( RHIDevice *dev, const RHIAccelerationStructureDesc *desc) {
    LOG_ERROR("rhi_metal: rhi_backend_acceleration_structure_create not implemented");
    (void)dev;
    (void)desc;
    return RHI_HANDLE_NULL;
}

void rhi_backend_acceleration_structure_destroy( RHIDevice *dev, RHIAccelerationStructure structure) {
    LOG_ERROR("rhi_metal: rhi_backend_acceleration_structure_destroy not implemented");
    (void)dev;
    (void)structure;
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

RHIBuffer rhi_buffer_create(RHIDevice *dev, const RHIBufferDesc *desc) {
    LOG_ERROR("rhi_metal: rhi_buffer_create not implemented");
    (void)dev;
    (void)desc;
    return RHI_HANDLE_NULL;
}

void rhi_buffer_destroy(RHIDevice *dev, RHIBuffer buf) {
    LOG_ERROR("rhi_metal: rhi_buffer_destroy not implemented");
    (void)dev;
    (void)buf;
}

RHIShader rhi_shader_create(RHIDevice *dev, const char *source, usize len, bool is_fragment) {
    LOG_ERROR("rhi_metal: rhi_shader_create not implemented");
    (void)dev;
    (void)source;
    (void)len;
    (void)is_fragment;
    return RHI_HANDLE_NULL;
}

RHIShader rhi_shader_create_compute(RHIDevice *dev, const char *source, usize len) {
    LOG_ERROR("rhi_metal: rhi_shader_create_compute not implemented");
    (void)dev;
    (void)source;
    (void)len;
    return RHI_HANDLE_NULL;
}

void rhi_shader_destroy(RHIDevice *dev, RHIShader shader) {
    LOG_ERROR("rhi_metal: rhi_shader_destroy not implemented");
    (void)dev;
    (void)shader;
}

RHIPipeline rhi_pipeline_create(RHIDevice *dev, const RHIPipelineDesc *desc) {
    LOG_ERROR("rhi_metal: rhi_pipeline_create not implemented");
    (void)dev;
    (void)desc;
    return RHI_HANDLE_NULL;
}

void rhi_pipeline_destroy(RHIDevice *dev, RHIPipeline pipe) {
    LOG_ERROR("rhi_metal: rhi_pipeline_destroy not implemented");
    (void)dev;
    (void)pipe;
}

RHITexture rhi_texture_create(RHIDevice *dev, const RHITextureDesc *desc) {
    LOG_ERROR("rhi_metal: rhi_texture_create not implemented");
    (void)dev;
    (void)desc;
    return RHI_HANDLE_NULL;
}

void rhi_texture_destroy(RHIDevice *dev, RHITexture tex) {
    LOG_ERROR("rhi_metal: rhi_texture_destroy not implemented");
    (void)dev;
    (void)tex;
}

RHITexture rhi_texture_array_create(RHIDevice *dev, u32 width, u32 height, u32 layers, RHIFormat fmt) {
    LOG_ERROR("rhi_metal: rhi_texture_array_create not implemented");
    (void)dev;
    (void)width;
    (void)height;
    (void)layers;
    (void)fmt;
    return RHI_HANDLE_NULL;
}

void rhi_texture_array_upload_layer(RHIDevice *dev, RHITexture tex, u32 layer, const void *rgba8, usize size) {
    LOG_ERROR("rhi_metal: rhi_texture_array_upload_layer not implemented");
    (void)dev;
    (void)tex;
    (void)layer;
    (void)rgba8;
    (void)size;
}

bool rhi_texture_get_size(RHIDevice *dev, RHITexture tex, u32 *out_w, u32 *out_h) {
    LOG_ERROR("rhi_metal: rhi_texture_get_size not implemented");
    (void)dev;
    (void)tex;
    (void)out_w;
    (void)out_h;
    return false;
}

bool rhi_texture_read_pixels(RHIDevice *dev, RHITexture tex, void *dst_rgba8, usize size) {
    LOG_ERROR("rhi_metal: rhi_texture_read_pixels not implemented");
    (void)dev;
    (void)tex;
    (void)dst_rgba8;
    (void)size;
    return false;
}

void rhi_texture_upload_mip(RHIDevice *dev, RHITexture tex, u32 mip_level, u32 width, u32 height, const void *data, usize size) {
    LOG_ERROR("rhi_metal: rhi_texture_upload_mip not implemented");
    (void)dev;
    (void)tex;
    (void)mip_level;
    (void)width;
    (void)height;
    (void)data;
    (void)size;
}

RHISampler rhi_sampler_create(RHIDevice *dev, const RHISamplerDesc *desc) {
    LOG_ERROR("rhi_metal: rhi_sampler_create not implemented");
    (void)dev;
    (void)desc;
    return RHI_HANDLE_NULL;
}

void rhi_sampler_destroy(RHIDevice *dev, RHISampler sampler) {
    LOG_ERROR("rhi_metal: rhi_sampler_destroy not implemented");
    (void)dev;
    (void)sampler;
}

void rhi_cmd_begin_render_pass(RHICmdBuffer *cmd) {
    if (cmd == NULL || cmd->backend == NULL) return;
    MetalBackend *mb = cmd->backend;
    if (cmd->render_pass_open) {
        LOG_ERROR("rhi_metal: render pass already open");
        return;
    }
    if (cmd->cmd == nil || mb->drawable == nil) {
        /* Fail closed: no frame in flight (or no drawable) — nothing to
         * encode into. */
        LOG_ERROR("rhi_metal: begin_render_pass outside a live frame");
        return;
    }
    /* Descriptor/encoder factory methods are autoreleased; scope a pool for
     * C callers. The encoder itself is retained and survives the drain. */
    @autoreleasepool {
    MTLRenderPassDescriptor *pass = [MTLRenderPassDescriptor renderPassDescriptor];
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
    cmd->render_encoder =
        [[cmd->cmd renderCommandEncoderWithDescriptor:pass] retain];
    if (cmd->render_encoder == nil) {
        LOG_ERROR("rhi_metal: renderCommandEncoderWithDescriptor failed");
        return;
    }
    cmd->render_pass_open = true;
    }   /* @autoreleasepool */
}

void rhi_cmd_end_render_pass(RHICmdBuffer *cmd) {
    if (cmd == NULL || !cmd->render_pass_open) return;
    [cmd->render_encoder endEncoding];
    [cmd->render_encoder release];
    cmd->render_encoder = nil;
    cmd->render_pass_open = false;
}

void rhi_cmd_bind_pipeline(RHICmdBuffer *cmd, RHIPipeline pipe) {
    LOG_ERROR("rhi_metal: rhi_cmd_bind_pipeline not implemented");
    (void)cmd;
    (void)pipe;
}

void rhi_cmd_bind_vertex_buffer(RHICmdBuffer *cmd, RHIBuffer buf, usize offset) {
    LOG_ERROR("rhi_metal: rhi_cmd_bind_vertex_buffer not implemented");
    (void)cmd;
    (void)buf;
    (void)offset;
}

void rhi_cmd_bind_index_buffer(RHICmdBuffer *cmd, RHIBuffer buf, usize offset, bool is_u32) {
    LOG_ERROR("rhi_metal: rhi_cmd_bind_index_buffer not implemented");
    (void)cmd;
    (void)buf;
    (void)offset;
    (void)is_u32;
}

void rhi_cmd_set_viewport(RHICmdBuffer *cmd, f32 x, f32 y, f32 w, f32 h, f32 min_depth, f32 max_depth) {
    LOG_ERROR("rhi_metal: rhi_cmd_set_viewport not implemented");
    (void)cmd;
    (void)x;
    (void)y;
    (void)w;
    (void)h;
    (void)min_depth;
    (void)max_depth;
}

void rhi_cmd_set_scissor(RHICmdBuffer *cmd, i32 x, i32 y, u32 w, u32 h) {
    LOG_ERROR("rhi_metal: rhi_cmd_set_scissor not implemented");
    (void)cmd;
    (void)x;
    (void)y;
    (void)w;
    (void)h;
}

void rhi_cmd_set_scissor_top_left(RHICmdBuffer *cmd, u32 x, u32 y, u32 w, u32 h) {
    LOG_ERROR("rhi_metal: rhi_cmd_set_scissor_top_left not implemented");
    (void)cmd;
    (void)x;
    (void)y;
    (void)w;
    (void)h;
}

void rhi_cmd_set_shadow_viewport(RHICmdBuffer *cmd, u32 x, u32 y, u32 w, u32 h) {
    LOG_ERROR("rhi_metal: rhi_cmd_set_shadow_viewport not implemented");
    (void)cmd;
    (void)x;
    (void)y;
    (void)w;
    (void)h;
}

void rhi_cmd_draw(RHICmdBuffer *cmd, u32 vertex_count, u32 instance_count) {
    LOG_ERROR("rhi_metal: rhi_cmd_draw not implemented");
    (void)cmd;
    (void)vertex_count;
    (void)instance_count;
}

void rhi_cmd_draw_base(RHICmdBuffer *cmd, u32 vertex_count, u32 instance_count, u32 first_vertex) {
    LOG_ERROR("rhi_metal: rhi_cmd_draw_base not implemented");
    (void)cmd;
    (void)vertex_count;
    (void)instance_count;
    (void)first_vertex;
}

void rhi_cmd_draw_indexed(RHICmdBuffer *cmd, u32 index_count, u32 instance_count) {
    LOG_ERROR("rhi_metal: rhi_cmd_draw_indexed not implemented");
    (void)cmd;
    (void)index_count;
    (void)instance_count;
}

void rhi_cmd_draw_indexed_base(RHICmdBuffer *cmd, u32 index_count, u32 instance_count, u32 first_index, i32 vertex_offset) {
    LOG_ERROR("rhi_metal: rhi_cmd_draw_indexed_base not implemented");
    (void)cmd;
    (void)index_count;
    (void)instance_count;
    (void)first_index;
    (void)vertex_offset;
}

void rhi_cmd_draw_indirect(RHIDevice *dev, RHIBuffer cmd_buf, u32 offset, u32 draw_count, u32 stride) {
    LOG_ERROR("rhi_metal: rhi_cmd_draw_indirect not implemented");
    (void)dev;
    (void)cmd_buf;
    (void)offset;
    (void)draw_count;
    (void)stride;
}

void rhi_cmd_draw_indexed_indirect(RHIDevice *dev, RHIBuffer cmd_buf, u32 offset, u32 draw_count, u32 stride) {
    LOG_ERROR("rhi_metal: rhi_cmd_draw_indexed_indirect not implemented");
    (void)dev;
    (void)cmd_buf;
    (void)offset;
    (void)draw_count;
    (void)stride;
}

void rhi_cmd_draw_indexed_indirect_count(RHIDevice *dev, RHIBuffer cmd_buf, u32 cmd_offset, RHIBuffer count_buf, u32 count_offset, u32 max_draws, u32 stride) {
    LOG_ERROR("rhi_metal: rhi_cmd_draw_indexed_indirect_count not implemented");
    (void)dev;
    (void)cmd_buf;
    (void)cmd_offset;
    (void)count_buf;
    (void)count_offset;
    (void)max_draws;
    (void)stride;
}

void rhi_cmd_clear_color(RHICmdBuffer *cmd, f32 r, f32 g, f32 b, f32 a) {
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
    /* Inside a pass: Metal clears are render-pass load actions, so flush the
     * current encoder (its recorded work stays in the command buffer) and
     * reopen with loadAction=Clear + the new color. */
    [cmd->render_encoder endEncoding];
    [cmd->render_encoder release];
    cmd->render_encoder = nil;
    cmd->render_pass_open = false;
    cmd->clear_pending = true;
    rhi_cmd_begin_render_pass(cmd);
}

void rhi_cmd_clear_color_attachment(RHICmdBuffer *cmd, u32 attachment, f32 r, f32 g, f32 b, f32 a) {
    LOG_ERROR("rhi_metal: rhi_cmd_clear_color_attachment not implemented");
    (void)cmd;
    (void)attachment;
    (void)r;
    (void)g;
    (void)b;
    (void)a;
}

void rhi_cmd_bind_texture(RHICmdBuffer *cmd, RHITexture tex, RHISampler sampler, u32 unit) {
    LOG_ERROR("rhi_metal: rhi_cmd_bind_texture not implemented");
    (void)cmd;
    (void)tex;
    (void)sampler;
    (void)unit;
}

void rhi_cmd_bind_shadow_texture(RHICmdBuffer *cmd, RHITexture shadow_tex, RHISampler sampler) {
    LOG_ERROR("rhi_metal: rhi_cmd_bind_shadow_texture not implemented");
    (void)cmd;
    (void)shadow_tex;
    (void)sampler;
}

void rhi_cmd_bind_uniform_buffer(RHICmdBuffer *cmd, RHIBuffer buf, u32 binding) {
    LOG_ERROR("rhi_metal: rhi_cmd_bind_uniform_buffer not implemented");
    (void)cmd;
    (void)buf;
    (void)binding;
}

void rhi_cmd_set_uniform_mat4(RHICmdBuffer *cmd, i32 location, const f32 *m) {
    LOG_ERROR("rhi_metal: rhi_cmd_set_uniform_mat4 not implemented");
    (void)cmd;
    (void)location;
    (void)m;
}

void rhi_cmd_set_uniform_vec3(RHICmdBuffer *cmd, i32 location, f32 x, f32 y, f32 z) {
    LOG_ERROR("rhi_metal: rhi_cmd_set_uniform_vec3 not implemented");
    (void)cmd;
    (void)location;
    (void)x;
    (void)y;
    (void)z;
}

void rhi_cmd_set_uniform_vec2(RHICmdBuffer *cmd, i32 location, f32 x, f32 y) {
    LOG_ERROR("rhi_metal: rhi_cmd_set_uniform_vec2 not implemented");
    (void)cmd;
    (void)location;
    (void)x;
    (void)y;
}

void rhi_cmd_set_uniform_vec4(RHICmdBuffer *cmd, i32 location, f32 x, f32 y, f32 z, f32 w) {
    LOG_ERROR("rhi_metal: rhi_cmd_set_uniform_vec4 not implemented");
    (void)cmd;
    (void)location;
    (void)x;
    (void)y;
    (void)z;
    (void)w;
}

void rhi_cmd_set_uniform_f32(RHICmdBuffer *cmd, i32 location, f32 v) {
    LOG_ERROR("rhi_metal: rhi_cmd_set_uniform_f32 not implemented");
    (void)cmd;
    (void)location;
    (void)v;
}

void rhi_cmd_set_uniform_i32(RHICmdBuffer *cmd, i32 location, i32 v) {
    LOG_ERROR("rhi_metal: rhi_cmd_set_uniform_i32 not implemented");
    (void)cmd;
    (void)location;
    (void)v;
}

void rhi_cmd_push_constants(RHICmdBuffer *cmd, u32 offset, const void *data, u32 size) {
    LOG_ERROR("rhi_metal: rhi_cmd_push_constants not implemented");
    (void)cmd;
    (void)offset;
    (void)data;
    (void)size;
}

void rhi_cmd_set_uniform_bytes(RHICmdBuffer *cmd, i32 location, const void *data, u32 size) {
    LOG_ERROR("rhi_metal: rhi_cmd_set_uniform_bytes not implemented");
    (void)cmd;
    (void)location;
    (void)data;
    (void)size;
}

i32 rhi_pipeline_get_uniform_location(RHIDevice *dev, RHIPipeline pipe, const char *name) {
    LOG_ERROR("rhi_metal: rhi_pipeline_get_uniform_location not implemented");
    (void)dev;
    (void)pipe;
    (void)name;
    return -1;
}

RHIShadowMap rhi_shadow_map_create(RHIDevice *dev, u32 width, u32 height) {
    LOG_ERROR("rhi_metal: rhi_shadow_map_create not implemented");
    (void)dev;
    (void)width;
    (void)height;
    return (RHIShadowMap){0};
}

void rhi_shadow_map_destroy(RHIDevice *dev, RHIShadowMap *sm) {
    LOG_ERROR("rhi_metal: rhi_shadow_map_destroy not implemented");
    (void)dev;
    (void)sm;
}

void rhi_cmd_bind_shadow_map(RHICmdBuffer *cmd, RHIShadowMap *sm) {
    LOG_ERROR("rhi_metal: rhi_cmd_bind_shadow_map not implemented");
    (void)cmd;
    (void)sm;
}

void rhi_cmd_unbind_shadow_map(RHICmdBuffer *cmd, u32 screen_w, u32 screen_h) {
    LOG_ERROR("rhi_metal: rhi_cmd_unbind_shadow_map not implemented");
    (void)cmd;
    (void)screen_w;
    (void)screen_h;
}

void rhi_cmd_clear_depth(RHICmdBuffer *cmd) {
    LOG_ERROR("rhi_metal: rhi_cmd_clear_depth not implemented");
    (void)cmd;
}

RHICubemap rhi_cubemap_create(RHIDevice *dev, const RHICubemapDesc *desc) {
    LOG_ERROR("rhi_metal: rhi_cubemap_create not implemented");
    (void)dev;
    (void)desc;
    return RHI_HANDLE_NULL;
}

void rhi_cubemap_destroy(RHIDevice *dev, RHICubemap cm) {
    LOG_ERROR("rhi_metal: rhi_cubemap_destroy not implemented");
    (void)dev;
    (void)cm;
}

void rhi_cubemap_transition_to_read(RHIDevice *dev, RHICubemap cm) {
    LOG_ERROR("rhi_metal: rhi_cubemap_transition_to_read not implemented");
    (void)dev;
    (void)cm;
}

void rhi_texture_transition_to_read(RHIDevice *dev, RHITexture tex) {
    LOG_ERROR("rhi_metal: rhi_texture_transition_to_read not implemented");
    (void)dev;
    (void)tex;
}

void rhi_cmd_bind_cubemap(RHICmdBuffer *cmd, RHICubemap cm, RHISampler sampler, u32 unit) {
    LOG_ERROR("rhi_metal: rhi_cmd_bind_cubemap not implemented");
    (void)cmd;
    (void)cm;
    (void)sampler;
    (void)unit;
}

void rhi_cmd_set_depth_func_less_or_equal(RHICmdBuffer *cmd) {
    LOG_ERROR("rhi_metal: rhi_cmd_set_depth_func_less_or_equal not implemented");
    (void)cmd;
}

void rhi_cmd_set_depth_func_less(RHICmdBuffer *cmd) {
    LOG_ERROR("rhi_metal: rhi_cmd_set_depth_func_less not implemented");
    (void)cmd;
}

void rhi_cmd_set_depth_mask(RHICmdBuffer *cmd, bool enabled) {
    LOG_ERROR("rhi_metal: rhi_cmd_set_depth_mask not implemented");
    (void)cmd;
    (void)enabled;
}

void rhi_cmd_set_cull_face(RHICmdBuffer *cmd, bool enabled) {
    LOG_ERROR("rhi_metal: rhi_cmd_set_cull_face not implemented");
    (void)cmd;
    (void)enabled;
}

void rhi_cmd_bind_texel_buffers(RHICmdBuffer *cmd, RHIBuffer buf0, RHIBuffer buf1) {
    LOG_ERROR("rhi_metal: rhi_cmd_bind_texel_buffers not implemented");
    (void)cmd;
    (void)buf0;
    (void)buf1;
}

void rhi_buffer_update(RHIDevice *dev, RHIBuffer buf, const void *data, usize size) {
    LOG_ERROR("rhi_metal: rhi_buffer_update not implemented");
    (void)dev;
    (void)buf;
    (void)data;
    (void)size;
}

void rhi_buffer_update_region(RHIDevice *dev, RHIBuffer buf, usize offset, const void *data, usize size) {
    LOG_ERROR("rhi_metal: rhi_buffer_update_region not implemented");
    (void)dev;
    (void)buf;
    (void)offset;
    (void)data;
    (void)size;
}

bool rhi_buffer_read(RHIDevice *dev, RHIBuffer buf, void *dst, usize offset, usize size) {
    LOG_ERROR("rhi_metal: rhi_buffer_read not implemented");
    (void)dev;
    (void)buf;
    (void)dst;
    (void)offset;
    (void)size;
    return false;
}

void rhi_cmd_fill_buffer(RHICmdBuffer *cmd, RHIBuffer buf, usize offset, usize size, u32 value) {
    LOG_ERROR("rhi_metal: rhi_cmd_fill_buffer not implemented");
    (void)cmd;
    (void)buf;
    (void)offset;
    (void)size;
    (void)value;
}

void rhi_cmd_update_buffer(RHICmdBuffer *cmd, RHIBuffer buf, usize offset, const void *data, usize size) {
    LOG_ERROR("rhi_metal: rhi_cmd_update_buffer not implemented");
    (void)cmd;
    (void)buf;
    (void)offset;
    (void)data;
    (void)size;
}

void *rhi_buffer_map(RHIDevice *dev, RHIBuffer buf) {
    LOG_ERROR("rhi_metal: rhi_buffer_map not implemented");
    (void)dev;
    (void)buf;
    return NULL;
}

void rhi_buffer_unmap(RHIDevice *dev, RHIBuffer buf) {
    LOG_ERROR("rhi_metal: rhi_buffer_unmap not implemented");
    (void)dev;
    (void)buf;
}

void rhi_cmd_copy_buffer(RHICmdBuffer *cmd, RHIBuffer src, RHIBuffer dst, usize size) {
    LOG_ERROR("rhi_metal: rhi_cmd_copy_buffer not implemented");
    (void)cmd;
    (void)src;
    (void)dst;
    (void)size;
}

void rhi_cmd_bind_material_textures(RHICmdBuffer *cmd, RHITexture albedo, RHITexture mr, RHITexture normal, RHITexture emissive, RHITexture shadow, RHITexture ssao, RHISampler sampler) {
    LOG_ERROR("rhi_metal: rhi_cmd_bind_material_textures not implemented");
    (void)cmd;
    (void)albedo;
    (void)mr;
    (void)normal;
    (void)emissive;
    (void)shadow;
    (void)ssao;
    (void)sampler;
}

void rhi_cmd_bind_material_textures_ibl(RHICmdBuffer *cmd, RHITexture albedo, RHITexture mr, RHITexture normal, RHITexture emissive, RHITexture occlusion, RHITexture shadow, RHITexture ssao, RHISampler sampler, RHITexture brdf_lut, RHICubemap irradiance_map, RHICubemap prefilter_map, const RHITexture *point_shadow_cubes, u32 point_shadow_count) {
    LOG_ERROR("rhi_metal: rhi_cmd_bind_material_textures_ibl not implemented");
    (void)cmd;
    (void)albedo;
    (void)mr;
    (void)normal;
    (void)emissive;
    (void)occlusion;
    (void)shadow;
    (void)ssao;
    (void)sampler;
    (void)brdf_lut;
    (void)irradiance_map;
    (void)prefilter_map;
    (void)point_shadow_cubes;
    (void)point_shadow_count;
}

void rhi_cmd_bind_deferred_gbuf_textures(RHICmdBuffer *cmd, RHITexture albedo_metallic, RHITexture roughness_ao, RHITexture normal, RHITexture depth, RHITexture emissive, RHITexture shadow, RHITexture ssao, RHISampler sampler, RHITexture brdf_lut, RHICubemap irradiance_map, RHICubemap prefilter_map, const RHITexture *point_shadow_cubes, u32 point_shadow_count, RHISampler cube_sampler) {
    LOG_ERROR("rhi_metal: rhi_cmd_bind_deferred_gbuf_textures not implemented");
    (void)cmd;
    (void)albedo_metallic;
    (void)roughness_ao;
    (void)normal;
    (void)depth;
    (void)emissive;
    (void)shadow;
    (void)ssao;
    (void)sampler;
    (void)brdf_lut;
    (void)irradiance_map;
    (void)prefilter_map;
    (void)point_shadow_cubes;
    (void)point_shadow_count;
    (void)cube_sampler;
}

void rhi_cmd_bind_textures_multi(RHICmdBuffer *cmd, RHITexture *textures, int count, RHISampler sampler) {
    LOG_ERROR("rhi_metal: rhi_cmd_bind_textures_multi not implemented");
    (void)cmd;
    (void)textures;
    (void)count;
    (void)sampler;
}

RHIOffscreenFBO rhi_offscreen_fbo_create(RHIDevice *dev, u32 width, u32 height) {
    LOG_ERROR("rhi_metal: rhi_offscreen_fbo_create not implemented");
    (void)dev;
    (void)width;
    (void)height;
    return (RHIOffscreenFBO){0};
}

RHIOffscreenFBO rhi_offscreen_fbo_create_fmt(RHIDevice *dev, u32 width, u32 height, RHIFormat color_fmt) {
    LOG_ERROR("rhi_metal: rhi_offscreen_fbo_create_fmt not implemented");
    (void)dev;
    (void)width;
    (void)height;
    (void)color_fmt;
    return (RHIOffscreenFBO){0};
}

RHIOffscreenFBO rhi_offscreen_fbo_create_desc(RHIDevice *dev, const RHIOffscreenFBODesc *desc) {
    LOG_ERROR("rhi_metal: rhi_offscreen_fbo_create_desc not implemented");
    (void)dev;
    (void)desc;
    return (RHIOffscreenFBO){0};
}

void rhi_offscreen_fbo_destroy(RHIDevice *dev, RHIOffscreenFBO *fbo) {
    LOG_ERROR("rhi_metal: rhi_offscreen_fbo_destroy not implemented");
    (void)dev;
    (void)fbo;
}

void rhi_offscreen_fbo_bind(RHICmdBuffer *cmd, RHIOffscreenFBO *fbo) {
    LOG_ERROR("rhi_metal: rhi_offscreen_fbo_bind not implemented");
    (void)cmd;
    (void)fbo;
}

void rhi_offscreen_fbo_bind_load(RHICmdBuffer *cmd, RHIOffscreenFBO *fbo) {
    LOG_ERROR("rhi_metal: rhi_offscreen_fbo_bind_load not implemented");
    (void)cmd;
    (void)fbo;
}

void rhi_offscreen_fbo_unbind(RHICmdBuffer *cmd, u32 screen_w, u32 screen_h) {
    LOG_ERROR("rhi_metal: rhi_offscreen_fbo_unbind not implemented");
    (void)cmd;
    (void)screen_w;
    (void)screen_h;
}

void rhi_offscreen_fbo_set_clear_color(RHIDevice *dev, RHIOffscreenFBO *fbo, f32 r, f32 g, f32 b, f32 a) {
    LOG_ERROR("rhi_metal: rhi_offscreen_fbo_set_clear_color not implemented");
    (void)dev;
    (void)fbo;
    (void)r;
    (void)g;
    (void)b;
    (void)a;
}

RHIMRTFBO rhi_mrt_fbo_create(RHIDevice *dev, u32 width, u32 height, const RHIFormat *formats, u32 attachment_count) {
    LOG_ERROR("rhi_metal: rhi_mrt_fbo_create not implemented");
    (void)dev;
    (void)width;
    (void)height;
    (void)formats;
    (void)attachment_count;
    return (RHIMRTFBO){0};
}

void rhi_mrt_fbo_destroy(RHIDevice *dev, RHIMRTFBO *fbo) {
    LOG_ERROR("rhi_metal: rhi_mrt_fbo_destroy not implemented");
    (void)dev;
    (void)fbo;
}

void rhi_mrt_fbo_bind(RHICmdBuffer *cmd, RHIMRTFBO *fbo) {
    LOG_ERROR("rhi_metal: rhi_mrt_fbo_bind not implemented");
    (void)cmd;
    (void)fbo;
}

void rhi_mrt_fbo_bind_load(RHICmdBuffer *cmd, RHIMRTFBO *fbo) {
    LOG_ERROR("rhi_metal: rhi_mrt_fbo_bind_load not implemented");
    (void)cmd;
    (void)fbo;
}

void rhi_mrt_fbo_unbind(RHICmdBuffer *cmd, u32 screen_w, u32 screen_h) {
    LOG_ERROR("rhi_metal: rhi_mrt_fbo_unbind not implemented");
    (void)cmd;
    (void)screen_w;
    (void)screen_h;
}

RHICubemapDepthFBO rhi_cubemap_depth_fbo_create(RHIDevice *dev, u32 size) {
    LOG_ERROR("rhi_metal: rhi_cubemap_depth_fbo_create not implemented");
    (void)dev;
    (void)size;
    return (RHICubemapDepthFBO){0};
}

void rhi_cubemap_depth_fbo_destroy(RHIDevice *dev, RHICubemapDepthFBO *fbo) {
    LOG_ERROR("rhi_metal: rhi_cubemap_depth_fbo_destroy not implemented");
    (void)dev;
    (void)fbo;
}

void rhi_cubemap_depth_fbo_bind_face(RHICmdBuffer *cmd, RHICubemapDepthFBO *fbo, u32 face) {
    LOG_ERROR("rhi_metal: rhi_cubemap_depth_fbo_bind_face not implemented");
    (void)cmd;
    (void)fbo;
    (void)face;
}

void rhi_cubemap_depth_fbo_unbind(RHICmdBuffer *cmd, u32 screen_w, u32 screen_h) {
    LOG_ERROR("rhi_metal: rhi_cubemap_depth_fbo_unbind not implemented");
    (void)cmd;
    (void)screen_w;
    (void)screen_h;
}

void rhi_cmd_dispatch(RHICmdBuffer *cmd, u32 x, u32 y, u32 z) {
    LOG_ERROR("rhi_metal: rhi_cmd_dispatch not implemented");
    (void)cmd;
    (void)x;
    (void)y;
    (void)z;
}

void rhi_cmd_bind_storage_buffer(RHICmdBuffer *cmd, RHIBuffer buf, u32 binding) {
    LOG_ERROR("rhi_metal: rhi_cmd_bind_storage_buffer not implemented");
    (void)cmd;
    (void)buf;
    (void)binding;
}

void rhi_cmd_bind_acceleration_structure( RHICmdBuffer *cmd, RHIAccelerationStructure structure, u32 binding) {
    LOG_ERROR("rhi_metal: rhi_cmd_bind_acceleration_structure not implemented");
    (void)cmd;
    (void)structure;
    (void)binding;
}

void rhi_cmd_memory_barrier(RHICmdBuffer *cmd) {
    LOG_ERROR("rhi_metal: rhi_cmd_memory_barrier not implemented");
    (void)cmd;
}

void rhi_cmd_bind_image_texture(RHICmdBuffer *cmd, RHITexture tex, u32 unit, u32 mip_level, bool write_only) {
    LOG_ERROR("rhi_metal: rhi_cmd_bind_image_texture not implemented");
    (void)cmd;
    (void)tex;
    (void)unit;
    (void)mip_level;
    (void)write_only;
}

void rhi_cmd_bind_image_cubemap_face(RHICmdBuffer *cmd, RHICubemap cm, u32 face, u32 mip, u32 unit, bool write_only) {
    LOG_ERROR("rhi_metal: rhi_cmd_bind_image_cubemap_face not implemented");
    (void)cmd;
    (void)cm;
    (void)face;
    (void)mip;
    (void)unit;
    (void)write_only;
}

void rhi_cmd_bind_cubemap_sampler(RHICmdBuffer *cmd, RHICubemap cm, RHISampler sampler, u32 unit) {
    LOG_ERROR("rhi_metal: rhi_cmd_bind_cubemap_sampler not implemented");
    (void)cmd;
    (void)cm;
    (void)sampler;
    (void)unit;
}

void rhi_cmd_bind_texture_mip(RHICmdBuffer *cmd, RHITexture tex, RHISampler sampler, u32 unit, u32 mip_level) {
    LOG_ERROR("rhi_metal: rhi_cmd_bind_texture_mip not implemented");
    (void)cmd;
    (void)tex;
    (void)sampler;
    (void)unit;
    (void)mip_level;
}

void rhi_cmd_bind_texture_compute(RHICmdBuffer *cmd, RHITexture tex, RHISampler sampler, u32 unit) {
    LOG_ERROR("rhi_metal: rhi_cmd_bind_texture_compute not implemented");
    (void)cmd;
    (void)tex;
    (void)sampler;
    (void)unit;
}

void rhi_cmd_transition_depth_to_read(RHICmdBuffer *cmd, RHITexture depth_tex) {
    LOG_ERROR("rhi_metal: rhi_cmd_transition_depth_to_read not implemented");
    (void)cmd;
    (void)depth_tex;
}

bool rhi_screenshot(RHIDevice *dev, u32 x, u32 y, u32 w, u32 h, u8 *pixels, usize pixel_bytes) {
    LOG_ERROR("rhi_metal: rhi_screenshot not implemented");
    (void)dev;
    (void)x;
    (void)y;
    (void)w;
    (void)h;
    (void)pixels;
    (void)pixel_bytes;
    return false;
}

RHIGPUTimer *rhi_gpu_timer_create(RHIDevice *dev) {
    LOG_ERROR("rhi_metal: rhi_gpu_timer_create not implemented");
    (void)dev;
    return NULL;
}

void rhi_gpu_timer_destroy(RHIDevice *dev, RHIGPUTimer *t) {
    LOG_ERROR("rhi_metal: rhi_gpu_timer_destroy not implemented");
    (void)dev;
    (void)t;
}

void rhi_gpu_timer_begin(RHIGPUTimer *t) {
    LOG_ERROR("rhi_metal: rhi_gpu_timer_begin not implemented");
    (void)t;
}

void rhi_gpu_timer_end(RHIGPUTimer *t) {
    LOG_ERROR("rhi_metal: rhi_gpu_timer_end not implemented");
    (void)t;
}

f64 rhi_gpu_timer_elapsed_ms(RHIGPUTimer *t) {
    LOG_ERROR("rhi_metal: rhi_gpu_timer_elapsed_ms not implemented");
    (void)t;
    return 0.0;
}
