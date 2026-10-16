/* Golden-image readback oracle, extracted verbatim-behavior from test_vulkan.c
 * (golden_downsample / golden_write_ppm / golden_compare_ppm /
 * golden_compare_buffer). The presented frame is read back via rhi_screenshot,
 * box-downsampled to a tiny grid (robust against single-pixel driver noise) and
 * compared against a committed reference PPM with a mean-absolute-error
 * tolerance. Set the env var GOLDEN_UPDATE=1 to regenerate the reference. */
#include "rhi_oracle.h"
#include <core/log.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
#include <direct.h>
#define oracle_mkdir(p) _mkdir(p)
#else
#include <sys/stat.h>
#define oracle_mkdir(p) mkdir(p, 0755)
#endif

void rhi_oracle_downsample(const u8 *rgba, u32 w, u32 h, u8 *grid) {
    for (u32 gy = 0; gy < RHI_ORACLE_GH; gy++) {
        for (u32 gx = 0; gx < RHI_ORACLE_GW; gx++) {
            u32 x0 = gx * w / RHI_ORACLE_GW, x1 = (gx + 1) * w / RHI_ORACLE_GW;
            u32 y0 = gy * h / RHI_ORACLE_GH, y1 = (gy + 1) * h / RHI_ORACLE_GH;
            u64 r = 0, g = 0, b = 0, n = 0;
            for (u32 yy = y0; yy < y1; yy++) {
                for (u32 xx = x0; xx < x1; xx++) {
                    const u8 *p = &rgba[((usize)yy * w + xx) * 4u];
                    r += p[0]; g += p[1]; b += p[2]; n++;
                }
            }
            if (n == 0) {
                /* Degenerate box (only when w < GW or h < GH; real presented
                 * frames are always >= the grid, so every box is non-empty and
                 * this path never changes golden behavior): fall back to the
                 * nearest source pixel instead of emitting black. */
                u32 cx = x0 < w ? x0 : w - 1;
                u32 cy = y0 < h ? y0 : h - 1;
                const u8 *p = &rgba[((usize)cy * w + cx) * 4u];
                r = p[0]; g = p[1]; b = p[2]; n = 1;
            }
            u8 *o = &grid[((usize)gy * RHI_ORACLE_GW + gx) * 3u];
            o[0] = (u8)(r / n); o[1] = (u8)(g / n); o[2] = (u8)(b / n);
        }
    }
}

bool rhi_oracle_write_ppm(const char *path, const u8 *grid) {
    oracle_mkdir("tests");
    oracle_mkdir("tests/golden");
    FILE *f = fopen(path, "wb");
    if (!f) return false;
    fprintf(f, "P6\n%d %d\n255\n", (int)RHI_ORACLE_GW, (int)RHI_ORACLE_GH);
    usize gbytes = (usize)RHI_ORACLE_GW * RHI_ORACLE_GH * 3;
    bool ok = fwrite(grid, 1, gbytes, f) == gbytes;
    fclose(f);
    if (!ok) return false;
    return true;
}

int rhi_oracle_compare_ppm(const char *path, const u8 *grid, RHIOracleResult *out) {
    FILE *f = fopen(path, "rb");
    if (!f) return -1;
    int gw = 0, gh = 0, mx = 0;
    if (fscanf(f, "P6 %d %d %d", &gw, &gh, &mx) != 3 ||
        gw != (int)RHI_ORACLE_GW || gh != (int)RHI_ORACLE_GH) {
        fclose(f); return 1;
    }
    fgetc(f); /* consume the single whitespace after maxval */
    u8 ref[RHI_ORACLE_GW * RHI_ORACLE_GH * 3];
    usize rd = fread(ref, 1, sizeof(ref), f);
    fclose(f);
    if (rd != sizeof(ref)) return 1;
    f64 sum = 0; u32 maxd = 0;
    for (usize i = 0; i < sizeof(ref); i++) {
        int d = (int)grid[i] - (int)ref[i];
        if (d < 0) d = -d;
        sum += (f64)d;
        if ((u32)d > maxd) maxd = (u32)d;
    }
    if (out) {
        out->mae = sum / (f64)sizeof(ref);
        out->maxd = maxd;
    }
    return 0;
}

/* `reject_blank`: fail when the captured grid is a single flat color —
 * a blank reference/compare is layout-insensitive and silently useless
 * (R438: the camera golden was blank for exactly this reason). */
bool rhi_oracle_compare_frame(const u8 *shot_rgba, u32 w, u32 h,
                              const char *path, bool reject_blank) {
    bool golden_pass = false;
    u8 grid[RHI_ORACLE_GW * RHI_ORACLE_GH * 3];
    rhi_oracle_downsample(shot_rgba, w, h, grid);

    if (reject_blank) {
        bool varied = false;
        for (usize i = 3; i < sizeof(grid) && !varied; i += 3)
            if (grid[i] != grid[0] || grid[i+1] != grid[1] || grid[i+2] != grid[2])
                varied = true;
        if (!varied) {
            LOG_ERROR("GOLDEN: %s captured a single flat color — blank image "
                      "cannot detect layout regressions", path);
            return false;
        }
    }

    bool update = (getenv("GOLDEN_UPDATE") != NULL);
    RHIOracleResult res = {0.0, 0u};
    int cmp = update ? -1 : rhi_oracle_compare_ppm(path, grid, &res);
    if (cmp == -1) {
        if (rhi_oracle_write_ppm(path, grid)) {
            LOG_WARN("GOLDEN: wrote reference %s (%dx%d) — rerun to compare",
                     path, (int)RHI_ORACLE_GW, (int)RHI_ORACLE_GH);
            golden_pass = true;
        } else {
            LOG_ERROR("GOLDEN: failed to write reference %s", path);
        }
    } else if (cmp == 0) {
        golden_pass = (res.mae <= RHI_ORACLE_MAE_MAX && res.maxd <= RHI_ORACLE_MAXD_MAX);
        LOG_INFO("GOLDEN: %s MAE=%.2f max=%u (tol MAE<=8.0 max<=56) -> %s",
                 path, res.mae, res.maxd, golden_pass ? "OK" : "DRIFT");
    } else {
        LOG_ERROR("GOLDEN: format/size mismatch in %s", path);
    }
    return golden_pass;
}

bool rhi_oracle_capture_presented(RHIDevice *dev, u32 w, u32 h, u8 *out_rgba) {
    if (!dev || !out_rgba || w == 0u || h == 0u) return false;
    return rhi_screenshot(dev, 0, 0, w, h, out_rgba, (usize)w * h * 4u);
}
