/* Numeric equivalence check: git-HEAD golden_downsample vs rhi_oracle_downsample.
 * Throwaway evidence for plan E task 1 — not part of the build. */
#include <core/types.h>
#include <core/log.h>
#include <rhi/rhi.h>
#include "rhi_oracle.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* stubs so tests/rhi_oracle.c links standalone */
void log_write(LogLevel level, const char *file, int line, const char *fmt, ...) {
    (void)level; (void)file; (void)line; (void)fmt;
}
bool rhi_screenshot(RHIDevice *dev, u32 x, u32 y, u32 w, u32 h, u8 *pixels, usize pixel_bytes) {
    (void)dev; (void)x; (void)y; (void)w; (void)h; (void)pixels; (void)pixel_bytes;
    return false;
}

/* ---- original implementation, verbatim from git HEAD test_vulkan.c ---- */
#define GOLDEN_GW 20
#define GOLDEN_GH 15
static void golden_downsample(const u8 *rgba, u32 w, u32 h, u8 *grid /* GW*GH*3 */) {
    for (u32 gy = 0; gy < GOLDEN_GH; gy++) {
        for (u32 gx = 0; gx < GOLDEN_GW; gx++) {
            u32 x0 = gx * w / GOLDEN_GW, x1 = (gx + 1) * w / GOLDEN_GW;
            u32 y0 = gy * h / GOLDEN_GH, y1 = (gy + 1) * h / GOLDEN_GH;
            u64 r = 0, g = 0, b = 0, n = 0;
            for (u32 yy = y0; yy < y1; yy++) {
                for (u32 xx = x0; xx < x1; xx++) {
                    const u8 *p = &rgba[((usize)yy * w + xx) * 4u];
                    r += p[0]; g += p[1]; b += p[2]; n++;
                }
            }
            if (n == 0) n = 1;
            u8 *o = &grid[((usize)gy * GOLDEN_GW + gx) * 3u];
            o[0] = (u8)(r / n); o[1] = (u8)(g / n); o[2] = (u8)(b / n);
        }
    }
}

static u32 rng_state = 0x12345678u;
static u32 rng(void) {
    rng_state = rng_state * 1664525u + 1013904223u;
    return rng_state >> 8;
}

int main(void) {
    const u32 sizes[][2] = {{640,480},{800,600},{1280,720},{1920,1080},{20,15},{37,29}};
    int fails = 0;
    for (usize s = 0; s < sizeof(sizes)/sizeof(sizes[0]); s++) {
        u32 w = sizes[s][0], h = sizes[s][1];
        u8 *rgba = malloc((usize)w*h*4u);
        u8 g_old[RHI_ORACLE_GW*RHI_ORACLE_GH*3], g_new[RHI_ORACLE_GW*RHI_ORACLE_GH*3];
        for (int trial = 0; trial < 8; trial++) {
            for (usize i = 0; i < (usize)w*h*4u; i++) rgba[i] = (u8)rng();
            golden_downsample(rgba, w, h, g_old);
            rhi_oracle_downsample(rgba, w, h, g_new);
            if (memcmp(g_old, g_new, sizeof(g_old)) != 0) {
                printf("MISMATCH %ux%u trial %d\n", w, h, trial);
                fails++;
            }
        }
        free(rgba);
    }
    /* degenerate small frame: intended divergence (nearest-pixel fallback) */
    {
        u8 rgba[8*8*4];
        u8 g_old[RHI_ORACLE_GW*RHI_ORACLE_GH*3], g_new[RHI_ORACLE_GW*RHI_ORACLE_GH*3];
        for (usize i = 0; i < sizeof(rgba); i += 4u) {
            rgba[i]=200u; rgba[i+1u]=100u; rgba[i+2u]=50u; rgba[i+3u]=255u;
        }
        golden_downsample(rgba, 8u, 8u, g_old);
        rhi_oracle_downsample(rgba, 8u, 8u, g_new);
        printf("8x8 constant: old grid[3..5]=%u,%u,%u new grid[3..5]=%u,%u,%u (%s)\n",
               g_old[3],g_old[4],g_old[5], g_new[3],g_new[4],g_new[5],
               memcmp(g_old,g_new,sizeof(g_old))==0 ? "same" : "diverges-by-design");
    }
    printf(fails ? "EQUIV: FAIL (%d)\n" : "EQUIV: PASS (all realistic sizes byte-identical)\n", fails);
    return fails ? 1 : 0;
}
