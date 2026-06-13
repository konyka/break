#include <asset/hotreload.h>
#include <core/log.h>
#include <stb_image.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static char *read_file(const char *path, usize *out_len) {
    FILE *f = fopen(path, "rb");
    if (!f) return NULL;
    fseek(f, 0, SEEK_END);
    long sz = ftell(f);
    if (sz < 0) { fclose(f); return NULL; }
    fseek(f, 0, SEEK_SET);
    char *buf = malloc((usize)sz + 1);
    if (!buf) { fclose(f); return NULL; }
    usize rd = fread(buf, 1, (usize)sz, f);
    buf[rd] = '\0';
    fclose(f);
    if (out_len) *out_len = rd;
    return buf;
}

static RHIPipeline hotreload_compile_pipeline(RHIDevice *dev,
                                               const char *vert_path,
                                               const char *frag_path) {
    usize vs_len = 0, fs_len = 0;
    char *vs_src = read_file(vert_path, &vs_len);
    char *fs_src = read_file(frag_path, &fs_len);
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
    hr->device = dev;
    hr->pipeline = RHI_HANDLE_NULL;
    hr->ready = false;
    strncpy(hr->vert_path, vert_path, sizeof(hr->vert_path) - 1);
    strncpy(hr->frag_path, frag_path, sizeof(hr->frag_path) - 1);

    hr->pipeline = hotreload_compile_pipeline(dev, vert_path, frag_path);
    if (!rhi_handle_valid(hr->pipeline)) return false;

    filewatch_init(&hr->watcher);
    filewatch_add(&hr->watcher, vert_path, hotreload_shader_callback, hr);
    filewatch_add(&hr->watcher, frag_path, hotreload_shader_callback, hr);

    hr->ready = true;
    return true;
}

void hotreload_pipeline_shutdown(HotReloadPipeline *hr) {
    filewatch_shutdown(&hr->watcher);
    if (rhi_handle_valid(hr->pipeline)) rhi_pipeline_destroy(hr->device, hr->pipeline);
    hr->ready = false;
}

void hotreload_pipeline_poll(HotReloadPipeline *hr) {
    filewatch_poll(&hr->watcher);
}

static bool hotreload_reload_texture(HotReloadTexture *hr) {
    if (!hr || !hr->device || !hr->target) return false;

    int w = 0, h = 0, ch = 0;
    u8 *data = stbi_load(hr->path, &w, &h, &ch, 4);
    if (!data || w <= 0 || h <= 0) {
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
    memset(hr, 0, sizeof(*hr));
    hr->device = dev;
    hr->target = target;
    strncpy(hr->path, path, sizeof(hr->path) - 1);

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
