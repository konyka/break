/* Cross-backend rendering comparison pin: OpenGL is retained as the reference
 * backend, so its committed golden must stay consistent with the Vulkan one.
 *
 * Both backends now produce the same image, so the grids are compared as-is:
 *  - rhi_screenshot returns top-down rows on every backend and NDC +Y is the
 *    top of the presented image on every backend (R639 flipped the Vulkan
 *    swapchain viewport to match GL).
 *  - Vulkan prefers a UNORM swapchain (R646), so neither backend sRGB-encodes
 *    on write.
 * A golden that is vertically mirrored or sRGB-encoded relative to the other
 * fails this check: regenerate it with GOLDEN_UPDATE=1 from that backend.
 * Pure CPU: reads the four 20x15 PPM grids, no GPU, no backend library. */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define GW 20
#define GH 15
#define GRID_BYTES (GW * GH * 3)
#define PARITY_MAE_MAX 2.0
#define PARITY_MAXD_MAX 12

static int read_ppm(const char *path, unsigned char *out) {
    FILE *f = fopen(path, "rb");
    int w = 0, h = 0, maxv = 0;
    int ok;
    if (f == NULL) {
        fprintf(stderr, "FAIL: cannot open %s\n", path);
        return 0;
    }
    ok = fscanf(f, "P6 %d %d %d", &w, &h, &maxv) == 3 && w == GW && h == GH &&
         maxv == 255 && fgetc(f) != EOF &&
         fread(out, 1, GRID_BYTES, f) == (size_t)GRID_BYTES;
    fclose(f);
    if (!ok) fprintf(stderr, "FAIL: %s is not a %dx%d P6 grid\n", path, GW, GH);
    return ok;
}

static int check_pair(const char *dir, const char *vk_name, const char *gl_name) {
    char vk_path[512], gl_path[512];
    unsigned char vk[GRID_BYTES], gl[GRID_BYTES];
    double sum = 0.0, mae;
    int maxd = 0, i;
    snprintf(vk_path, sizeof(vk_path), "%s/%s", dir, vk_name);
    snprintf(gl_path, sizeof(gl_path), "%s/%s", dir, gl_name);
    if (!read_ppm(vk_path, vk) || !read_ppm(gl_path, gl)) return 0;
    for (i = 0; i < GRID_BYTES; i++) {
        int d = abs((int)vk[i] - (int)gl[i]);
        sum += d;
        if (d > maxd) maxd = d;
    }
    mae = sum / GRID_BYTES;
    printf("  %s vs %s: MAE=%.2f max=%d (tol MAE<=%.1f max<=%d)\n", vk_name,
           gl_name, mae, maxd, PARITY_MAE_MAX, PARITY_MAXD_MAX);
    if (mae > PARITY_MAE_MAX || maxd > PARITY_MAXD_MAX) {
        fprintf(stderr, "FAIL: GL golden no longer matches the Vulkan golden "
                        "(stale, flipped or sRGB-encoded reference?)\n");
        return 0;
    }
    return 1;
}

int main(int argc, char **argv) {
    int ok = 1;
    if (argc != 2) {
        fprintf(stderr, "usage: test_rhi_golden_parity <golden_dir>\n");
        return 2;
    }
    ok &= check_pair(argv[1], "test_vulkan_vk.ppm", "test_vulkan_gl.ppm");
    ok &= check_pair(argv[1], "test_vulkan_vk_cam.ppm", "test_vulkan_gl_cam.ppm");
    printf(ok ? "test_rhi_golden_parity: OK\n" : "test_rhi_golden_parity: FAILED\n");
    return ok ? 0 : 1;
}
