/* Cross-backend rendering comparison pin: OpenGL is retained as the reference
 * backend, so its committed golden must stay consistent with the Vulkan one.
 *
 * Two known, deliberate differences are modelled instead of tolerated:
 *  - Vulkan presents through an sRGB swapchain (encoded on write); the GL
 *    default framebuffer is written raw. So VK ~= srgb_encode(GL).
 *  - rhi_screenshot returns top-down rows on both backends (rhi.h contract),
 *    but test_vulkan renders with the non-flipped viewport: Vulkan maps NDC +Y
 *    to the bottom row, GL to the top row. The stored grids are therefore
 *    vertical mirrors of each other. So VK ~= srgb_encode(vflip(GL)).
 * A GL golden generated before the top-down screenshot contract (commit
 * ac15c54a) is NOT mirrored and fails this check: regenerate it with
 * GOLDEN_UPDATE=1 from a GL build.
 * Pure CPU: reads the four 20x15 PPM grids, no GPU, no backend library. */
#include <math.h>
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

static unsigned char srgb_encode(unsigned char c) {
    double x = (double)c / 255.0;
    double y = x <= 0.0031308 ? 12.92 * x : 1.055 * pow(x, 1.0 / 2.4) - 0.055;
    return (unsigned char)(y * 255.0 + 0.5);
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
        int row = i / (GW * 3), col = i % (GW * 3);
        int mirrored = (GH - 1 - row) * (GW * 3) + col;
        int d = abs((int)vk[i] - (int)srgb_encode(gl[mirrored]));
        sum += d;
        if (d > maxd) maxd = d;
    }
    mae = sum / GRID_BYTES;
    printf("  %s vs srgb(vflip(%s)): MAE=%.2f max=%d (tol MAE<=%.1f max<=%d)\n", vk_name,
           gl_name, mae, maxd, PARITY_MAE_MAX, PARITY_MAXD_MAX);
    if (mae > PARITY_MAE_MAX || maxd > PARITY_MAXD_MAX) {
        fprintf(stderr, "FAIL: GL golden no longer matches the Vulkan golden "
                        "(stale or flipped reference?)\n");
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
