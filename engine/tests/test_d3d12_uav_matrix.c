#include <rhi/rhi.h>
#include "test_framework.h"

/* UAV parameter matrix.
 *
 * ID3D12Device_CreateUnorderedAccessView returns void; an illegal descriptor
 * is reported by removing the device with DXGI_ERROR_INVALID_CALL. A dead
 * device cannot be shared between trials, so every cell builds its own device
 * and "killed" is decided by whether an unrelated allocation still succeeds
 * afterwards.
 *
 * Each cell varies one field of the view descriptor. Legal shapes must
 * survive; the deliberately illegal ones (zeroed desc, pDesc=NULL) show what
 * a bad descriptor looks like.
 */

/* Internal to the D3D12 backend; lives in rhi_d3d12.c. format_kind:
 * 0 = R32_TYPELESS (raw), 1 = DXGI_FORMAT_UNKNOWN + StructureByteStride 16
 * (structured, via the DESC1 entry point), 2 = R32_FLOAT (typed). */
extern int rhi_d3d12_probe_create_uav(RHIDevice *dev, RHIBuffer buf,
                                      int format_kind);

static const char *const k_uav_format_name[] = {
    "R32_TYPELESS flags=0",
    "R32_TYPELESS +RAW",
    "UNKNOWN flags=0",
    "UNKNOWN stride16",
    "zeroed desc",
    "pDesc=NULL",
    "R32_TYPELESS+RAW+cnt"
};

typedef struct {
    int format;       /* index into k_uav_format_name */
    u32 size;         /* buffer bytes */
    int uav_flag;     /* drive RHI_BUFFER_USAGE_STORAGE */
    int create_view;  /* 0 = control, never build the view */
} UavCell;

static int uav_cell_survives(const UavCell *cell, char *detail, usize cap) {
    static const unsigned char seed[16] = { 1,2,3,4, 5,6,7,8, 9,10,11,12,
                                            13,14,15,16 };
    RHIResult r = RHI_RESULT_OK;
    RHIDevice *dev;
    RHITextureDesc td;
    RHITexture probe;
    int alive;

    dev = rhi_device_create_ex(RHI_BACKEND_D3D12, (void *)1, NULL, 64, 64, &r);
    if (dev == NULL) {
        snprintf(detail, cap, "device create failed");
        return 0;
    }
    memset(&td, 0, sizeof(td));
    td.width = 2u; td.height = 2u;
    td.format = RHI_FORMAT_R8G8B8A8_UNORM; td.mip_levels = 1u;
    td.data = seed;

    /* Baseline before the cell's view: a healthy device must pass this, so a
     * cell that fails after it is attributable to the view and not to the
     * device coming up broken. */
    probe = rhi_texture_create(dev, &td);
    if (!rhi_handle_valid(probe)) {
        snprintf(detail, cap, "baseline texture create failed");
        rhi_device_destroy(dev);
        return 0;
    }
    rhi_texture_destroy(dev, probe);

    if (cell->create_view) {
        static const unsigned char bseed[256] = { 0 };
        RHIBufferDesc bd;
        RHIBuffer buf;
        memset(&bd, 0, sizeof(bd));
        bd.size = cell->size;
        bd.usage = cell->uav_flag ? RHI_BUFFER_USAGE_STORAGE
                                  : RHI_BUFFER_USAGE_UNIFORM;
        /* initial_data is load-bearing here, not cosmetic: without it the
         * buffer is not device-local, so it lands on the UPLOAD heap, and a
         * UPLOAD heap buffer cannot carry ALLOW_UNORDERED_ACCESS --
         * CreateCommittedResource fails and the cell never reaches the view.
         * Supplying it is what makes this a matrix over view shapes instead of
         * a matrix over buffer placement. */
        bd.initial_data = bseed;
        buf = rhi_buffer_create(dev, &bd);
        if (!rhi_handle_valid(buf)) {
            snprintf(detail, cap, "buffer create failed (placement)");
            rhi_device_destroy(dev);
            return 0;
        }
        (void)rhi_d3d12_probe_create_uav(dev, buf, cell->format);
        snprintf(detail, cap, "view built");
        rhi_buffer_destroy(dev, buf);
    } else {
        snprintf(detail, cap, "control (no view)");
    }

    /* The verdict: an allocation unrelated to anything above still works, and
     * its contents still come back. Checking the bytes too, because "allocates
     * fine but renders garbage" is the other half of what a bad descriptor
     * looks like. */
    probe = rhi_texture_create(dev, &td);
    alive = rhi_handle_valid(probe);
    if (!alive) {
        snprintf(detail, cap, "KILLED: post-view texture create failed");
    } else {
        unsigned char px[16];
        memset(px, 0, sizeof(px));
        if (!rhi_texture_read_pixels(dev, probe, px, sizeof(px)))
            snprintf(detail, cap, "readback FAILED");
        else if (px[0] != seed[0])
            snprintf(detail, cap, "readback wrong (p0=%d want %d)",
                     (int)px[0], (int)seed[0]);
        else
            snprintf(detail, cap, "ok");
        /* D3D12 hands back the existing device for an adapter while any
         * reference to it lives, so a leaked texture here would make the next
         * cell inherit this cell's device, removed or not. */
        rhi_texture_destroy(dev, probe);
    }
    rhi_device_destroy(dev);
    return alive;
}

TEST(uav_view_parameter_matrix) {
    UavCell cells[9];
    int alive_cells[9];
    int i;
    int survivors = 0;
    memset(cells, 0, sizeof(cells));
    /* Field-level sweep: variant 0 is the shape the binder uses today and
     * variants 1..6 each move exactly one field away from it. Two controls
     * (no view at all) bracket the run so a device that came up broken shows
     * up as a control failure instead of being read as a field-level result. */
    cells[0].format = 0; cells[0].size = 256u; cells[0].uav_flag = 1; cells[0].create_view = 1;
    cells[1].format = 1; cells[1].size = 256u; cells[1].uav_flag = 1; cells[1].create_view = 1;
    cells[2].format = 2; cells[2].size = 256u; cells[2].uav_flag = 1; cells[2].create_view = 1;
    cells[3].format = 3; cells[3].size = 256u; cells[3].uav_flag = 1; cells[3].create_view = 1;
    cells[4].format = 4; cells[4].size = 256u; cells[4].uav_flag = 1; cells[4].create_view = 1;
    cells[5].format = 5; cells[5].size = 256u; cells[5].uav_flag = 1; cells[5].create_view = 1;
    cells[6].format = 6; cells[6].size = 256u; cells[6].uav_flag = 1; cells[6].create_view = 1;
    cells[7].format = 0; cells[7].size = 256u; cells[7].uav_flag = 1; cells[7].create_view = 0;
    cells[8].format = 1; cells[8].size = 256u; cells[8].uav_flag = 1; cells[8].create_view = 0;

    for (i = 0; i < (int)(sizeof(cells) / sizeof(cells[0])); ++i) {
        char detail[72];
        int ok = uav_cell_survives(&cells[i], detail, sizeof(detail));
        printf("  uav-matrix[%d] fmt=%-18s size=%-4u storage=%d view=%d -> %-6s (%s)\n",
               i, k_uav_format_name[cells[i].format], (unsigned)cells[i].size,
               cells[i].uav_flag, cells[i].create_view,
               ok ? "ALIVE" : "KILLED", detail);
        alive_cells[i] = ok;
        if (ok) ++survivors;
        fflush(stdout);
    }
    printf("  uav-matrix: %d/%d cells survived\n", survivors,
           (int)(sizeof(cells) / sizeof(cells[0])));
    /* Legal views must survive on any conforming runtime: raw (1), structured
     * with a stride (3), and the no-view controls (7, 8). The others are
     * illegal descriptors and are expected to die with
     * DXGI_ERROR_INVALID_CALL: R32_TYPELESS without RAW (0), structured with
     * stride 0 (2), zeroed (4), pDesc=NULL, which a buffer cannot satisfy (5),
     * and a counter on a raw view, since counters need a structured view (6).
     *
     * An earlier version of the probe left ViewDimension and NumElements
     * zeroed, so every view cell died on both WARP and the RTX 4060. That was
     * misread for several rounds as a platform fault. */
    ASSERT_TRUE(alive_cells[1]);
    ASSERT_TRUE(alive_cells[3]);
    ASSERT_TRUE(alive_cells[7]);
    ASSERT_TRUE(alive_cells[8]);
}

int main(void) {
#if defined(_WIN32)
    printf("=== Running Tests ===\n");
    RUN_TEST(uav_view_parameter_matrix);
    printf("\n=== Results: %d passed, %d failed, %d total ===\n",
           g_test_pass, g_test_fail, g_test_count);
    return g_test_fail > 0 ? 1 : 0;
#else
    return 77;
#endif
}
