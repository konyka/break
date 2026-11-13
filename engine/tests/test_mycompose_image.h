/* C harness for test_mycompose_gpu.cpp: Platform, explicit RHI device,
 * BreakUI, the myui Compose adapter and screenshot inspection. The engine
 * platform/myui headers use C11 atomics and are C-only, so the C++ test
 * reaches them through this narrow C interface. */
#ifndef TEST_MYCOMPOSE_IMAGE_H
#define TEST_MYCOMPOSE_IMAGE_H

#include <stddef.h>
#include <stdint.h>

#include <myui/mycompose/my_compose_runtime.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct ComposeGpu ComposeGpu;

typedef struct ComposeGpuDevice {
    int backend;              /* RHIBackend reported by the device */
    char name[256];
    uint32_t vendor_id;
    uint32_t device_id;
    uint32_t api_version;
    uint32_t driver_version;
    int device_type;          /* RHIDeviceType */
    const char *device_type_name;
} ComposeGpuDevice;

typedef struct ComposeGpuFonts {
    int mono_loaded;          /* JetBrainsMono alone loads and draws 'A' */
    int cjk_loaded;           /* NotoSansSC alone loads and draws U+5927 */
    int chain_uses_cjk;       /* the BreakUI chain draws U+5927 like NotoSansSC */
    int32_t mono_w, mono_h, cjk_w, cjk_h;
} ComposeGpuFonts;

typedef struct ComposeGpuInject {
    int move;
    float x, y;               /* logical window coordinates */
    int key;                  /* InputState key slot, -1 = none */
    int press;
} ComposeGpuInject;

typedef struct ComposeGpuRect {
    int32_t x, y, w, h;       /* logical window coordinates */
} ComposeGpuRect;

typedef struct ComposeGpuRegion {
    uint32_t total;
    uint32_t match;           /* within tolerance of the expected colour */
    uint32_t dark;            /* r,g,b < 96: text ink */
    uint64_t signature;       /* hash of dark pixel positions */
} ComposeGpuRegion;

typedef struct ComposeGpuCounters {
    uint32_t frames, rendered, skipped, shots, presents;
    uint32_t synthetic_pointer_edges, synthetic_key_edges;
    uint32_t direct_text_commits, queue_text_events;
    uint32_t drawable_w, drawable_h, logical_w, logical_h;
    uint64_t compose_allocs;  /* inside my_compose_myui_pump */
    uint64_t myui_allocs;     /* inside break_ui_pump and break_ui_render */
} ComposeGpuCounters;

/* Allocation counter owned by the test TU (0 growth when not wrapped). */
uint64_t compose_gpu_alloc_count(void);
int compose_gpu_alloc_counting(void);

/* 0 = ready, 77 = no display/device, 1 = failure (incl. missing fonts). */
int compose_gpu_open(ComposeGpu **out, int vulkan, const char *mono_font,
    const char *cjk_font, ComposeGpuDevice *device, ComposeGpuFonts *fonts);
int compose_gpu_bind(ComposeGpu *gpu, MyComposeStore *store, MyComposeView view,
    void *view_context);
/* One production frame; returns 0 on success. `want_shot` takes a
 * screenshot when a frame is rendered (see counters/shot_taken). */
int compose_gpu_frame(ComposeGpu *gpu, const ComposeGpuInject *inject,
    const char *direct_commit, int want_shot, int *shot_taken);
/* `idle` frames, then frames until a screenshot is taken. */
int compose_gpu_settle(ComposeGpu *gpu, unsigned idle);
int compose_gpu_click(ComposeGpu *gpu, MyComposeNodeHandle node);
int compose_gpu_tap_key(ComposeGpu *gpu, int key);
int compose_gpu_rect(ComposeGpu *gpu, MyComposeNodeHandle node, ComposeGpuRect *out);
const void *compose_gpu_widget(ComposeGpu *gpu, MyComposeNodeHandle node);
int compose_gpu_text(ComposeGpu *gpu, MyComposeNodeHandle node, char *out, size_t cap);
int compose_gpu_focused(ComposeGpu *gpu, MyComposeNodeHandle node);
ComposeGpuRegion compose_gpu_inspect(ComposeGpu *gpu, ComposeGpuRect rect,
    uint32_t rgba, int tolerance);
int compose_gpu_write_ppm(ComposeGpu *gpu, const char *path);
void compose_gpu_counters(ComposeGpu *gpu, ComposeGpuCounters *out);
uint32_t compose_gpu_vk_validation_messages(void);
void compose_gpu_close(ComposeGpu *gpu);

#ifdef __cplusplus
}
#endif

#endif
