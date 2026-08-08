#include <asset/hotreload.h>
#include <core/log.h>
#include <stb_image.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <core/shader_io.h>

/* Dev-only texture reload: reject absurd dimensions before stbi_load allocates. */
#define HOTRELOAD_MAX_TEX_DIM 8192u

static RHIPipeline hotreload_compile_pipeline(RHIDevice *dev,
                                               const char *vert_path,
                                               const char *frag_path) {
    usize vs_len = 0, fs_len = 0;
    char *vs_src = shader_read_file(vert_path, &vs_len);
    char *fs_src = shader_read_file(frag_path, &fs_len);
    if (!vs_src || !fs_src) {
        free(vs_src);
        free(fs_src);
        return RHI_HANDLE_NULL;
    }

    RHIShader vs = rhi_shader_create(dev, vs_src, vs_len, false);
    RHIShader fs = rhi_shader_create(dev, fs_src, fs_len, true);
    free(vs_src);
    free(fs_src);

    if (!rhi_handle_valid(vs) || !rhi_handle_valid(fs)) {
        LOG_WARN("Hot reload: shader compile failed");
        if (rhi_handle_valid(vs)) rhi_shader_destroy(dev, vs);
        if (rhi_handle_valid(fs)) rhi_shader_destroy(dev, fs);
        return RHI_HANDLE_NULL;
    }

    RHIPipelineDesc pdesc = {.vert = vs, .frag = fs, .uses_textures = true};
    RHIPipeline pipe = rhi_pipeline_create(dev, &pdesc);
    rhi_shader_destroy(dev, vs);
    rhi_shader_destroy(dev, fs);
    return pipe;
}

static void hotreload_shader_callback(const char *path, void *user) {
    HotReloadPipeline *hr = (HotReloadPipeline *)user;
    LOG_INFO("Hot reload: %s changed, recompiling pipeline", path);
    RHIPipeline new_pipe = hotreload_compile_pipeline(hr->device, hr->vert_path, hr->frag_path);
    if (rhi_handle_valid(new_pipe)) {
        if (rhi_handle_valid(hr->pipeline)) rhi_pipeline_destroy(hr->device, hr->pipeline);
        hr->pipeline = new_pipe;
        LOG_INFO("Hot reload: pipeline recompiled successfully");
    } else {
        LOG_WARN("Hot reload: recompile failed, keeping old pipeline");
    }
}

bool hotreload_pipeline_init(HotReloadPipeline *hr, RHIDevice *dev,
                              const char *vert_path, const char *frag_path,
                              RHIPipelineDesc *out_desc) {
    (void)out_desc;
    /* R111-2: Zero the struct first so strncpy-truncated paths are guaranteed
     * null-terminated.  hotreload_texture_init already does this. */
    memset(hr, 0, sizeof(*hr));
    hr->device = dev;
    hr->pipeline = RHI_HANDLE_NULL;
    hr->ready = false;
    strncpy(hr->vert_path, vert_path, sizeof(hr->vert_path) - 1);
    hr->vert_path[sizeof(hr->vert_path) - 1] = '\0';
    strncpy(hr->frag_path, frag_path, sizeof(hr->frag_path) - 1);
    hr->frag_path[sizeof(hr->frag_path) - 1] = '\0';

    hr->pipeline = hotreload_compile_pipeline(dev, vert_path, frag_path);
    if (!rhi_handle_valid(hr->pipeline)) return false;

    filewatch_init(&hr->watcher);
    filewatch_add(&hr->watcher, vert_path, hotreload_shader_callback, hr);
    filewatch_add(&hr->watcher, frag_path, hotreload_shader_callback, hr);

    hr->ready = true;
    return true;
}

void hotreload_pipeline_shutdown(HotReloadPipeline *hr) {
    /* R431 (CORRECTNESS): mirror the R311 poll guard. main.c calls shutdown
     * unconditionally even when init failed (initial shader compile error) —
     * in that case *hr is all-zero, so watcher.inotify_fd == 0 passes
     * filewatch_shutdown's `fd >= 0` check and close(0) CLOSES STDIN. */
    if (!hr || !hr->ready) return;
    filewatch_shutdown(&hr->watcher);
    if (rhi_handle_valid(hr->pipeline)) rhi_pipeline_destroy(hr->device, hr->pipeline);
    hr->ready = false;
}

void hotreload_pipeline_poll(HotReloadPipeline *hr) {
    /* R311 (CORRECTNESS): mirror hotreload_texture_poll's guard. If
     * hotreload_pipeline_init FAILED (e.g. the initial shader compile errored —
     * the exact case hot-reload exists to iterate on), it returns false BEFORE
     * calling filewatch_init, leaving *hr at its memset(0) state: ready=false
     * and watcher.inotify_fd==0. main.c ignores the init return and still polls
     * every frame (see main.c hotreload_pipeline_poll call), so without this
     * guard filewatch_poll would take its `inotify_fd >= 0` branch (0 passes!)
     * and read(0, ...) — i.e. a BLOCKING read on stdin every frame, hanging the
     * render loop on a TTY (or silently consuming piped stdin otherwise). Only
     * poll once init succeeded and the watcher is actually initialized. */
    if (!hr || !hr->ready) return;
    filewatch_poll(&hr->watcher);
}

static bool hotreload_reload_texture(HotReloadTexture *hr) {
    if (!hr || !hr->device || !hr->target) return false;

    int w = 0, h = 0, ch = 0;
    if (!stbi_info(hr->path, &w, &h, &ch)) {
        LOG_WARN("Hot reload texture: cannot read info for %s", hr->path);
        return false;
    }
    if (w <= 0 || h <= 0 ||
        (u32)w > HOTRELOAD_MAX_TEX_DIM || (u32)h > HOTRELOAD_MAX_TEX_DIM) {
        LOG_WARN("Hot reload texture: dimensions out of range %dx%d for %s", w, h, hr->path);
        return false;
    }
    u8 *data = stbi_load(hr->path, &w, &h, &ch, 4);
    /* R431 (TOCTOU): the file can be swapped between stbi_info and stbi_load,
     * so the decoded w/h are NOT the validated ones — re-check the dimension
     * cap here before rhi_texture_create sizes its allocation from them. */
    if (!data || w <= 0 || h <= 0 ||
        (u32)w > HOTRELOAD_MAX_TEX_DIM || (u32)h > HOTRELOAD_MAX_TEX_DIM) {
        if (data) stbi_image_free(data);
        LOG_WARN("Hot reload texture: failed to decode %s", hr->path);
        return false;
    }

    RHITexture old = *hr->target;
    RHITextureDesc desc = {
        .width      = (u32)w,
        .height     = (u32)h,
        .format     = RHI_FORMAT_R8G8B8A8_UNORM,
        .mip_levels = 1,
        .data       = data,
    };
    RHITexture neu = rhi_texture_create(hr->device, &desc);
    stbi_image_free(data);

    if (!rhi_handle_valid(neu)) {
        LOG_WARN("Hot reload texture: GPU upload failed for %s", hr->path);
        return false;
    }

    if (rhi_handle_valid(old)) rhi_texture_destroy(hr->device, old);
    *hr->target = neu;
    LOG_INFO("Hot reload texture: reloaded %s (%dx%d)", hr->path, w, h);

    if (hr->on_reloaded) hr->on_reloaded(hr->on_reloaded_user);
    return true;
}

static void hotreload_texture_callback(const char *path, void *user) {
    HotReloadTexture *hr = (HotReloadTexture *)user;
    (void)path;
    hotreload_reload_texture(hr);
}

bool hotreload_texture_init(HotReloadTexture *hr, RHIDevice *dev,
                              const char *path, RHITexture *target) {
    if (!hr || !dev || !path || !target) return false;
    if (strlen(path) >= sizeof(hr->path)) return false;
    memset(hr, 0, sizeof(*hr));
    hr->device = dev;
    hr->target = target;
    strncpy(hr->path, path, sizeof(hr->path) - 1);
    hr->path[sizeof(hr->path) - 1] = '\0';

    filewatch_init(&hr->watcher);
    filewatch_add(&hr->watcher, hr->path, hotreload_texture_callback, hr);
    hr->ready = true;
    return true;
}

void hotreload_texture_set_callback(HotReloadTexture *hr,
                                      void (*on_reloaded)(void *user), void *user) {
    if (!hr) return;
    hr->on_reloaded = on_reloaded;
    hr->on_reloaded_user = user;
}

void hotreload_texture_poll(HotReloadTexture *hr) {
    if (!hr || !hr->ready) return;
    filewatch_poll(&hr->watcher);
}

void hotreload_texture_shutdown(HotReloadTexture *hr) {
    if (!hr) return;
    filewatch_shutdown(&hr->watcher);
    hr->ready = false;
}
