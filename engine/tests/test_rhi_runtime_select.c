/* Runtime backend chain selection (docs/design/rhi_runtime_backend.md §4-§5).
 * Pure: fake backends, fake env, captured RHIEVT lines; no GPU. */
#include "rhi/rhi_runtime.h"
#include "rhi/rhi_rollout.h"
#include "core/log.h"

#include <stdarg.h>
#include <stdio.h>
#include <string.h>

static unsigned checks, failures;
#define CHECK(c) check((c), #c, __LINE__)
static void check(int c, const char *e, int line) {
    checks++;
    if (!c) { fprintf(stderr, "FAIL line %d: %s\n", line, e); failures++; }
}

/* ---- captured log lines ---- */
static char logbuf[4096];
void log_write(LogLevel level, const char *file, int line, const char *fmt, ...) {
    char tmp[512];
    va_list ap;
    (void)level; (void)file; (void)line;
    va_start(ap, fmt);
    vsnprintf(tmp, sizeof(tmp), fmt, ap);
    va_end(ap);
    if (strlen(logbuf) + strlen(tmp) + 2 < sizeof(logbuf)) {
        strcat(logbuf, tmp);
        strcat(logbuf, "\n");
    }
}

/* ---- fake env ---- */
static const char *env_backend, *env_no_fallback, *env_fail_vulkan;
static const char *fake_getenv(const char *name) {
    if (strcmp(name, "BREAK_RHI_BACKEND") == 0) return env_backend;
    if (strcmp(name, "BREAK_RHI_NO_FALLBACK") == 0) return env_no_fallback;
    if (strcmp(name, "BREAK_RHI_FAIL_VULKAN") == 0) return env_fail_vulkan;
    return NULL;
}

/* ---- fake backends ---- */
static int dev_vk, dev_gl;
static int vk_ok, gl_ok;
static unsigned vk_calls, gl_calls;
static void *vk_got_window, *gl_got_window;
static RHIApi api_vk, api_gl;
static int window_h, surface_h, display_h;

static RHIDevice *fake_vk_create(void *w, void *d, u32 width, u32 height) {
    (void)d; (void)width; (void)height;
    vk_calls++; vk_got_window = w;
    return vk_ok ? (RHIDevice *)&dev_vk : NULL;
}
static RHIDevice *fake_gl_create(void *w, void *d, u32 width, u32 height) {
    (void)d; (void)width; (void)height;
    gl_calls++; gl_got_window = w;
    return gl_ok ? (RHIDevice *)&dev_gl : NULL;
}
static u32 vk_frame_index(RHIDevice *dev) { (void)dev; return 100u; }
static u32 gl_frame_index(RHIDevice *dev) { (void)dev; return 200u; }

static const RHIRuntimeBackendDesc k_backends[] = {
    { RHI_BACKEND_VULKAN, "vulkan", &api_vk, fake_vk_create, true },
    { RHI_BACKEND_OPENGL, "opengl", &api_gl, fake_gl_create, false },
};
static const RHIRuntimeConfig k_cfg = { k_backends, 2u, fake_getenv };

static void reset(int vk, int gl) {
    rhi_runtime_reset_for_test();
    vk_ok = vk; gl_ok = gl;
    vk_calls = gl_calls = 0u;
    vk_got_window = gl_got_window = NULL;
    env_backend = env_no_fallback = env_fail_vulkan = NULL;
    logbuf[0] = '\0';
}

static RHIDevice *chain(void) {
    return rhi_runtime_create_chain(&k_cfg, &window_h, &surface_h, &display_h,
                                    640u, 480u);
}

static const char *find(const char *needle) { return strstr(logbuf, needle); }

int main(void) {
    RHIDevice *dev;
    api_vk.rhi_frame_index = vk_frame_index;
    api_gl.rhi_frame_index = gl_frame_index;

    /* 1. nothing created yet */
    reset(1, 1);
    CHECK(strcmp(rhi_runtime_active_backend(), "none") == 0);
    CHECK(rhi_frame_index(NULL) == 0u); /* stub table */

    /* 2. default chain: vulkan wins, GL never touched, VK gets surface */
    reset(1, 1);
    dev = chain();
    CHECK(dev == (RHIDevice *)&dev_vk);
    CHECK(vk_calls == 1u && gl_calls == 0u);
    CHECK(vk_got_window == &surface_h);
    CHECK(strcmp(rhi_runtime_active_backend(), "vulkan") == 0);
    CHECK(rhi_frame_index(dev) == 100u); /* forwarders now hit the VK table */
    CHECK(strcmp(rhi_rollout_compiled_backend(), "vulkan") == 0);
    CHECK(strcmp(rhi_rollout_compiled_reason(), "platform-default") == 0);
    CHECK(find("\"event\":\"backend_selected\",\"backend\":\"vulkan\"") != NULL);
    CHECK(find("\"event\":\"fallback\"") == NULL);

    /* 3. vulkan create fails -> opengl on window_native, fallback logged */
    reset(0, 1);
    dev = chain();
    CHECK(dev == (RHIDevice *)&dev_gl);
    CHECK(vk_calls == 1u && gl_calls == 1u);
    CHECK(gl_got_window == &window_h);
    CHECK(strcmp(rhi_runtime_active_backend(), "opengl") == 0);
    CHECK(rhi_frame_index(dev) == 200u);
    {
        const char *fb = find("\"event\":\"fallback\",\"backend\":\"vulkan\"");
        const char *sel = find("\"event\":\"backend_selected\",\"backend\":\"opengl\"");
        CHECK(fb != NULL && sel != NULL && fb < sel); /* order: fallback first */
        CHECK(find("\"reason\":\"config-fallback\"") != NULL);
    }
    /* later RHIEVT lines (device_lost, ...) must name the backend in use */
    CHECK(strcmp(rhi_rollout_compiled_backend(), "opengl") == 0);
    CHECK(strcmp(rhi_rollout_compiled_reason(), "config-fallback") == 0);
    CHECK(strcmp(rhi_runtime_selection_reason(), "config-fallback") == 0);

    /* 4. every entry fails -> NULL, stays "none", stub table still safe */
    reset(0, 0);
    dev = chain();
    CHECK(dev == NULL);
    CHECK(vk_calls == 1u && gl_calls == 1u);
    CHECK(strcmp(rhi_runtime_active_backend(), "none") == 0);
    CHECK(rhi_frame_index(NULL) == 0u);
    CHECK(find("backend_selected") == NULL);

    /* 5. BREAK_RHI_BACKEND=opengl restricts the chain (vulkan not tried) */
    reset(1, 1);
    env_backend = "opengl";
    dev = chain();
    CHECK(dev == (RHIDevice *)&dev_gl);
    CHECK(vk_calls == 0u && gl_calls == 1u);
    CHECK(find("\"backend\":\"opengl\",\"reason\":\"explicit-env\"") != NULL);
    CHECK(strcmp(rhi_rollout_compiled_reason(), "explicit-env") == 0);

    /* 6. BREAK_RHI_BACKEND=vulkan + vulkan failure -> no silent GL */
    reset(0, 1);
    env_backend = "vulkan";
    dev = chain();
    CHECK(dev == NULL);
    CHECK(gl_calls == 0u);

    /* 7. unknown env value: warn, then default chain */
    reset(1, 1);
    env_backend = "glide";
    dev = chain();
    CHECK(dev == (RHIDevice *)&dev_vk);
    CHECK(find("BREAK_RHI_BACKEND") != NULL && find("glide") != NULL);

    /* 8. BREAK_RHI_NO_FALLBACK=1 keeps only the primary */
    reset(0, 1);
    env_no_fallback = "1";
    dev = chain();
    CHECK(dev == NULL);
    CHECK(vk_calls == 1u && gl_calls == 0u);

    /* 9. BREAK_RHI_FAIL_VULKAN=1: vulkan factory never called, GL wins */
    reset(1, 1);
    env_fail_vulkan = "1";
    dev = chain();
    CHECK(dev == (RHIDevice *)&dev_gl);
    CHECK(vk_calls == 0u && gl_calls == 1u);
    CHECK(find("\"event\":\"fallback\",\"backend\":\"vulkan\"") != NULL);

    /* 10. explicit create: exact backend, no fallback, unknown fails */
    reset(0, 1);
    dev = rhi_runtime_create_explicit(&k_cfg, RHI_BACKEND_VULKAN, &surface_h,
                                      &display_h, 640u, 480u);
    CHECK(dev == NULL && gl_calls == 0u);
    CHECK(strcmp(rhi_runtime_active_backend(), "none") == 0);
    dev = rhi_runtime_create_explicit(&k_cfg, RHI_BACKEND_OPENGL, &window_h,
                                      &display_h, 640u, 480u);
    CHECK(dev == (RHIDevice *)&dev_gl);
    CHECK(strcmp(rhi_runtime_active_backend(), "opengl") == 0);
    reset(1, 1);
    dev = rhi_runtime_create_explicit(&k_cfg, RHI_BACKEND_D3D12, &window_h,
                                      &display_h, 640u, 480u);
    CHECK(dev == NULL && vk_calls == 0u && gl_calls == 0u);

    /* 11. invalid config is rejected, not dereferenced */
    reset(1, 1);
    CHECK(rhi_runtime_create_chain(NULL, &window_h, &surface_h, &display_h,
                                   640u, 480u) == NULL);

    rhi_runtime_reset_for_test();
    if (failures != 0u) {
        fprintf(stderr, "%u of %u checks failed\n", failures, checks);
        return 1;
    }
    printf("OK: %u runtime selection checks\n", checks);
    return 0;
}
