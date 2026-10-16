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
