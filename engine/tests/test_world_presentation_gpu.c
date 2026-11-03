#include <platform/platform.h>
#include <renderer/world_presentation.h>
#include <rhi/rhi_native_vulkan.h>
#include <X11/Xlib.h>
#include <stdio.h>
#include <string.h>

#define SHOT_W 128u
#define SHOT_H 128u
#define SHOT_BYTES (SHOT_W * SHOT_H * 4u)

#ifndef WORLD_GPU_BACKEND
#define WORLD_GPU_BACKEND RHI_BACKEND_VULKAN
#endif

static void fill_quad(MeshStageVertex verts[4], f32 cx, f32 cy, f32 half) {
    memset(verts, 0, 4u * sizeof(MeshStageVertex));
    const f32 x[4] = {cx - half, cx + half, cx + half, cx - half};
    const f32 y[4] = {cy - half, cy - half, cy + half, cy + half};
    for (u32 i = 0; i < 4u; i++) {
        verts[i].px = x[i];
        verts[i].py = y[i];
        verts[i].ny = 1.0f;
    }
}

static bool upload_quad(RHIDevice *dev, f32 cx, f32 cy, f32 half,
                        MeshGpu *gpu, MeshDrawDesc *draw) {
    MeshStageVertex legacy[4];
    MeshBuffer mesh;
    fill_quad(legacy, cx, cy, half);
    return mesh_buffer_from_legacy(&mesh, legacy, 4u, NULL) &&
           mesh_buffer_draw_desc(&mesh, draw) && mesh_gpu_upload(dev, &mesh, gpu);
}

static RHITexture make_texture(RHIDevice *dev, u8 r, u8 g, u8 b) {
    u8 rgba[4] = {r, g, b, 255u};
    RHITextureDesc desc = {1u, 1u, RHI_FORMAT_R8G8B8A8_UNORM, 1u, rgba};
    return rhi_texture_create(dev, &desc);
}

static RHITexture make_uv_texture(RHIDevice *dev) {
    u8 rgba[8] = {255u, 0, 0, 255u, 255u, 0, 255u, 255u};
    RHITextureDesc desc = {2u, 1u, RHI_FORMAT_R8G8B8A8_UNORM, 1u, rgba};
    return rhi_texture_create(dev, &desc);
}

static MeshMaterial make_material(RHITexture texture, RHISampler sampler) {
    MeshMaterial material;
    memset(&material, 0, sizeof(material));
    material.base_color = vec3(1, 1, 1);
    material.roughness = 0.5f;
    material.albedo = texture;
    material.sampler = sampler;
    return material;
}

static bool render_snapshot(RHIDevice *dev, WorldPresenter *presenter,
                            const WorldFrameSnapshot *snapshot, u8 shot[SHOT_BYTES],
                            WorldSubmitStats *last_stats) {
    for (u32 frame = 0; frame < 3u; frame++) {
        RHICmdBuffer *cmd = rhi_frame_begin(dev);
        if (!cmd) return false;
        rhi_cmd_begin_render_pass(cmd);
        rhi_cmd_clear_color(cmd, 0, 0, 0, 1);
        WorldSubmitStats stats;
        if (world_presenter_submit(cmd, presenter, snapshot, &stats) != WORLD_PRESENTATION_OK)
            return false;
        rhi_cmd_end_render_pass(cmd);
        rhi_frame_end(dev);
        if (frame == 2u && !rhi_screenshot(dev, 0, 0, SHOT_W, SHOT_H, shot, SHOT_BYTES))
            return false;
        rhi_present(dev);
        if (last_stats) *last_stats = stats;
    }
    return true;
}

typedef struct PixelStats {
    u32 red;
    u32 green;
    u32 blue;
    u32 magenta;
    u32 yellow;
    u64 luminance;
} PixelStats;

static PixelStats inspect_pixels(const u8 shot[SHOT_BYTES]) {
    PixelStats stats = {0};
    for (u32 i = 0; i < SHOT_W * SHOT_H; i++) {
        u32 r = shot[i * 4u];
        u32 g = shot[i * 4u + 1u];
        u32 b = shot[i * 4u + 2u];
        if (r > 120u && g < 100u && b < 100u) stats.red++;
        if (g > 120u && r < 100u && b < 100u) stats.green++;
        if (b > 120u && r < 100u && g < 100u) stats.blue++;
        if (r > 120u && g < 100u && b > 120u) stats.magenta++;
        if (r > 150u && g > 150u && b < 80u) stats.yellow++;
        stats.luminance += r + g + b;
    }
    return stats;
}

static bool write_ppm(const char *path, const u8 shot[SHOT_BYTES]) {
    FILE *out = fopen(path, "wb");
    if (!out) return false;
    fprintf(out, "P6\n%u %u\n255\n", SHOT_W, SHOT_H);
    for (u32 i = 0; i < SHOT_W * SHOT_H; i++)
        fwrite(shot + i * 4u, 1, 3, out);
    return fclose(out) == 0;
}

int main(void) {
    const bool vulkan = WORLD_GPU_BACKEND == RHI_BACKEND_VULKAN;
    const char *backend_name = vulkan ? "vulkan" : "opengl";
    Display *display = XOpenDisplay(NULL);
    if (!display) {
        printf("SKIP: no reachable X11 display\n");
        return 77;
    }
    XCloseDisplay(display);
    const PlatformConfig config = {.width = SHOT_W, .height = SHOT_H, .title = "world presentation"};
    Platform *platform = platform_create(&config);
    if (!platform) {
        printf("SKIP: platform window was not created\n");
        return 77;
    }
    u32 width = 0, height = 0;
    platform_get_drawable_size(platform, &width, &height);
    void *window = vulkan ? platform_surface_native(platform) : platform_window_native(platform);
    RHIDevice *dev = rhi_device_create(WORLD_GPU_BACKEND, window,
                                       platform_display_native(platform), width, height);
    if (!dev) {
        platform_destroy(platform);
        printf("SKIP: %s device was not created\n", backend_name);
        return 77;
    }
    rhi_device_attach_wsi(dev, platform_wsi_surface(platform));
    rhi_set_vsync(dev, false);
    if (width != SHOT_W || height != SHOT_H) {
        printf("FAIL: drawable is %ux%u, expected %ux%u\n", width, height, SHOT_W, SHOT_H);
        rhi_device_destroy(dev);
        platform_destroy(platform);
        return 1;
    }

    int result = 1;
    WorldPresenter presenter;
    memset(&presenter, 0, sizeof(presenter));
    MeshGpu static_gpu = {0}, hidden_gpu = {0}, stream_gpu = {0}, vegetation_gpu = {0};
    RHITexture textures[4] = {{0}};
    WorldObject objects[3];
    WorldVegetationPrototype prototype;
    VegetationInstance instances[2];
    memset(objects, 0, sizeof(objects));
    memset(&prototype, 0, sizeof(prototype));
    memset(instances, 0, sizeof(instances));
    if (!world_presenter_create(dev, &presenter)) {
        printf("FAIL: presenter creation/shader compilation failed\n");
        goto cleanup;
    }
    MeshDrawDesc static_draw, hidden_draw, stream_draw, vegetation_draw;
    if (!upload_quad(dev, -0.5f, -0.5f, 0.15f, &static_gpu, &static_draw) ||
        !upload_quad(dev, 0.0f, 0.0f, 1.0f, &hidden_gpu, &hidden_draw) ||
        !upload_quad(dev, 0.0f, 0.0f, 0.15f, &vegetation_gpu, &vegetation_draw)) {
        printf("FAIL: object mesh upload failed\n");
        goto cleanup;
    }
    StreamTileData tile;
    memset(&tile, 0, sizeof(tile));
    tile.vertex_count = 4u;
    fill_quad(tile.verts, 0.0f, 0.0f, 0.15f);
    MeshBuffer stream_mesh;
    if (!world_presentation_stream_mesh(&tile, vec3(0.5f, -0.5f, 0), &stream_mesh) ||
        !mesh_buffer_draw_desc(&stream_mesh, &stream_draw) ||
        !mesh_gpu_upload(dev, &stream_mesh, &stream_gpu)) {
        printf("FAIL: V1 stream mesh upload failed\n");
        goto cleanup;
    }
    textures[0] = make_uv_texture(dev);
    textures[1] = make_texture(dev, 0, 255, 0);
    textures[2] = make_texture(dev, 0, 0, 255);
    textures[3] = make_texture(dev, 255, 255, 0);
    for (u32 i = 0; i < 4u; i++) {
        if (!rhi_handle_valid(textures[i])) {
            printf("FAIL: material texture creation failed\n");
            goto cleanup;
        }
    }
    objects[0].id = 10u;
    objects[0].gpu = static_gpu;
    objects[0].draw = static_draw;
    objects[0].material = make_material(textures[0], presenter.sampler);
    objects[1].id = 20u;
    objects[1].gpu = hidden_gpu;
    objects[1].draw = hidden_draw;
    objects[1].material = make_material(textures[3], presenter.sampler);
    objects[2].id = 30u;
    objects[2].gpu = stream_gpu;
    objects[2].draw = stream_draw;
    objects[2].material = make_material(textures[1], presenter.sampler);
    objects[2].stream = true;

    u32 visible_ids[2] = {10u, 30u};
    VisRoom room;
    memset(&room, 0, sizeof(room));
    VisQuery visibility;
    memset(&visibility, 0, sizeof(visibility));
    visibility.rooms = &room;
    visibility.room_count = 0u;
    visibility.outdoor_ids = visible_ids;
    visibility.outdoor_count = 2u;
    visibility.camera_forward = vec3(0, 0, 1);

    prototype.lod_count = 2u;
    prototype.errors[0] = 0.0f;
    prototype.errors[1] = 0.02f;
    prototype.gpu[0] = vegetation_gpu;
    prototype.gpu[1] = vegetation_gpu;
    prototype.draws[0] = vegetation_draw;
    prototype.draws[1] = vegetation_draw;
    prototype.material = make_material(textures[2], presenter.sampler);
    u8 density[2] = {1u, 1u};
    f32 heights[2] = {0.5f, 0.5f};
    VegetationDesc vegetation_desc = {density, 2u, 1u, 1.0f, 1u};
    VegetationBuild vegetation = {instances, 2u, 0u, 0u};
    if (!vegetation_build(&vegetation_desc, heights, 1.0f, &vegetation)) {
        printf("FAIL: CPU vegetation layout failed\n");
        goto cleanup;
    }
    for (u32 i = 0; i < vegetation.count; i++) {
        instances[i].position.e[0] -= 1.0f;
        instances[i].position.e[2] -= 0.5f;
    }
    u8 lod_levels[2] = {0};
    u32 lod_tags[2] = {0};
    LodInstanceState lod_state = {lod_levels, lod_tags, 2u};

    WorldPresentationInput input;
    memset(&input, 0, sizeof(input));
    input.frame_id = 1u;
    input.view = mat4_identity();
    input.projection = mat4_identity();
    input.camera = vec3(0, 0, 5);
    input.fov = 1.0f;
    input.screen_height = SHOT_H;
    input.pixel_error = 1.0f;
    input.objects = objects;
    input.object_count = 3u;
    input.visibility = &visibility;
    input.vegetation = &vegetation;
    input.prototypes = &prototype;
    input.prototype_count = 1u;
    input.lod_state = &lod_state;
    static WorldFrameSnapshot day;
    static WorldFrameSnapshot night;
    time_of_day_eval(5.0f, 10.0f, &input.lighting);
    if (world_presentation_snapshot(&input, &day) != WORLD_PRESENTATION_OK) {
        printf("FAIL: day snapshot failed\n");
        goto cleanup;
    }
    input.frame_id = 2u;
    time_of_day_eval(0.0f, 10.0f, &input.lighting);
    if (world_presentation_snapshot(&input, &night) != WORLD_PRESENTATION_OK) {
        printf("FAIL: night snapshot failed\n");
        goto cleanup;
    }

    static u8 day_shot[SHOT_BYTES];
    static u8 night_shot[SHOT_BYTES];
    WorldSubmitStats submit_stats;
    if (!render_snapshot(dev, &presenter, &day, day_shot, &submit_stats) ||
        !render_snapshot(dev, &presenter, &night, night_shot, NULL)) {
        printf("FAIL: frame submission or screenshot failed\n");
        goto cleanup;
    }
    PixelStats day_stats = inspect_pixels(day_shot);
    PixelStats night_stats = inspect_pixels(night_shot);
    char day_path[128], night_path[128];
    snprintf(day_path, sizeof(day_path), "world_presentation_%s_day.ppm", backend_name);
    snprintf(night_path, sizeof(night_path), "world_presentation_%s_night.ppm", backend_name);
    bool saved = write_ppm(day_path, day_shot) && write_ppm(night_path, night_shot);
    printf("WORLD PIXELS backend=%s red=%u green=%u blue=%u magenta=%u yellow=%u day_luma=%llu night_luma=%llu\n",
           backend_name, day_stats.red, day_stats.green, day_stats.blue, day_stats.magenta,
           day_stats.yellow, (unsigned long long)day_stats.luminance,
           (unsigned long long)night_stats.luminance);
    printf("WORLD EVIDENCE day=%s night=%s saved=%d\n", day_path, night_path, saved ? 1 : 0);
    if (!saved || submit_stats.object_draws != 2u || submit_stats.stream_draws != 1u ||
        submit_stats.instance_count != 2u || submit_stats.instance_batches != 1u ||
        day_stats.red < 50u || day_stats.green < 50u || day_stats.blue < 50u ||
        day_stats.magenta < 50u || day_stats.yellow != 0u ||
        night_stats.luminance * 4u >= day_stats.luminance) {
        printf("FAIL: world pixel or submission contract was not met\n");
        goto cleanup;
    }
#ifdef ENGINE_VULKAN
    if (vulkan) {
        u32 validation_messages = rhi_vk_validation_message_count();
        printf("WORLD VULKAN validation_messages=%u\n", validation_messages);
        if (validation_messages != 0u) goto cleanup;
    }
#endif
    result = 0;

cleanup:
    rhi_device_idle(dev);
    mesh_gpu_destroy(dev, &vegetation_gpu);
    mesh_gpu_destroy(dev, &stream_gpu);
    mesh_gpu_destroy(dev, &hidden_gpu);
    mesh_gpu_destroy(dev, &static_gpu);
    for (u32 i = 0; i < 4u; i++)
        if (rhi_handle_valid(textures[i])) rhi_texture_destroy(dev, textures[i]);
    world_presenter_destroy(dev, &presenter);
    rhi_device_destroy(dev);
    platform_destroy(platform);
    return result;
}
