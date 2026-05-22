#include <renderer/gpucull.h>
#include <core/log.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static char *gc_read_file(const char *path, usize *out_len) {
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

bool gpucull_init(GPUCullSystem *gc, RHIDevice *dev) {
    memset(gc, 0, sizeof(*gc));
    gc->device = dev;

    usize cs_len = 0;
    char *cs_src = gc_read_file("shaders/cull.comp", &cs_len);
    if (!cs_src) {
        LOG_WARN("GPUCull: compute shader not found");
        return false;
    }

    RHIShader cs = rhi_shader_create(dev, cs_src, cs_len, true);
    free(cs_src);
    if (!rhi_handle_valid(cs)) {
        LOG_WARN("GPUCull: shader compile failed");
        return false;
    }

    RHIPipelineDesc pdesc = {0};
    pdesc.frag = cs;
    pdesc.is_compute = true;
    gc->cull_pipe = rhi_pipeline_create(dev, &pdesc);
    rhi_shader_destroy(dev, cs);

    if (!rhi_handle_valid(gc->cull_pipe)) {
        LOG_WARN("GPUCull: pipeline creation failed");
        return false;
    }

    RHIBufferDesc obj_desc = {
        .size = GPUCULL_MAX_OBJECTS * sizeof(f32) * 4,
        .usage = RHI_BUFFER_USAGE_STORAGE,
    };
    gc->object_ssbo = rhi_buffer_create(dev, &obj_desc);

    RHIBufferDesc vis_desc = {
        .size = GPUCULL_MAX_OBJECTS * sizeof(u32),
        .usage = RHI_BUFFER_USAGE_STORAGE,
    };
    gc->visible_ssbo = rhi_buffer_create(dev, &vis_desc);

    RHIBufferDesc count_desc = {
        .size = sizeof(u32),
        .usage = RHI_BUFFER_USAGE_STORAGE,
    };
    gc->count_buf = rhi_buffer_create(dev, &count_desc);

    gc->ready = true;
    LOG_INFO("GPUCull: initialized (max %u objects)", GPUCULL_MAX_OBJECTS);
    return true;
}

void gpucull_shutdown(GPUCullSystem *gc) {
    if (!gc->device) return;
    if (rhi_handle_valid(gc->count_buf)) rhi_buffer_destroy(gc->device, gc->count_buf);
    if (rhi_handle_valid(gc->visible_ssbo)) rhi_buffer_destroy(gc->device, gc->visible_ssbo);
    if (rhi_handle_valid(gc->object_ssbo)) rhi_buffer_destroy(gc->device, gc->object_ssbo);
    if (rhi_handle_valid(gc->cull_pipe)) rhi_pipeline_destroy(gc->device, gc->cull_pipe);
    gc->ready = false;
}

void gpucull_update_objects(GPUCullSystem *gc, const f32 *positions, const f32 *radii, u32 count) {
    if (!gc->ready || count == 0) return;
    gc->object_count = count > GPUCULL_MAX_OBJECTS ? GPUCULL_MAX_OBJECTS : count;

    f32 *data = malloc(gc->object_count * 4 * sizeof(f32));
    for (u32 i = 0; i < gc->object_count; i++) {
        data[i * 4 + 0] = positions[i * 3 + 0];
        data[i * 4 + 1] = positions[i * 3 + 1];
        data[i * 4 + 2] = positions[i * 3 + 2];
        data[i * 4 + 3] = radii[i];
    }
    rhi_buffer_update(gc->device, gc->object_ssbo, data, gc->object_count * 4 * sizeof(f32));
    free(data);
}

void gpucull_dispatch(GPUCullSystem *gc, RHICmdBuffer *cmd, const f32 *vp) {
    if (!gc->ready || gc->object_count == 0) return;

    u32 zero = 0;
    rhi_buffer_update(gc->device, gc->count_buf, &zero, sizeof(u32));

    rhi_cmd_bind_pipeline(cmd, gc->cull_pipe);
    rhi_cmd_bind_storage_buffer(cmd, gc->object_ssbo, 0);
    rhi_cmd_bind_storage_buffer(cmd, gc->visible_ssbo, 1);
    rhi_cmd_bind_storage_buffer(cmd, gc->count_buf, 2);

    i32 loc = rhi_pipeline_get_uniform_location(gc->device, gc->cull_pipe, "push.vp");
    if (loc >= 0) rhi_cmd_set_uniform_mat4(cmd, loc, vp);

    u32 groups = (gc->object_count + 63) / 64;
    rhi_cmd_dispatch(cmd, groups, 1, 1);
    rhi_cmd_memory_barrier(cmd);
}

void gpucull_get_results(GPUCullSystem *gc, u32 *out_visible_count) {
    if (!gc->ready || !out_visible_count) return;
    *out_visible_count = gc->object_count;
}
