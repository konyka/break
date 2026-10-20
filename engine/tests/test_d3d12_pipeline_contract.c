#include <rhi/rhi.h>
#include "test_framework.h"
#if defined(_WIN32)
#include <rhi/rhi_d3d12.h>
#include <rhi/rhi_backend_internal.h>
#endif
/* GPU resource roundtrip; main skips 77 when no adapter. */
static RHIDevice *g_dev;

TEST(buffer_write_read_roundtrip) {
    const u32 payload[4] = { 11u, 22u, 33u, 44u };
    u32 readback[4] = { 0u, 0u, 0u, 0u };
    RHIBufferDesc bdesc;
    memset(&bdesc, 0, sizeof(bdesc));
    bdesc.usage = RHI_BUFFER_USAGE_STORAGE | RHI_BUFFER_USAGE_DEVICE_ADDRESS;
    bdesc.size = sizeof(payload);
    bdesc.initial_data = payload;
    RHIBuffer buf = rhi_buffer_create(g_dev, &bdesc);
    ASSERT_TRUE(rhi_handle_valid(buf));
    ASSERT_TRUE(rhi_buffer_read(g_dev, buf, readback, 0, sizeof(readback)));
    ASSERT_TRUE(memcmp(readback, payload, sizeof(payload)) == 0);
    rhi_buffer_destroy(g_dev, buf);
}

TEST(command_buffer_fill_and_update_roundtrip) {
    u32 readback[4] = { 0u, 0u, 0u, 0u };
    const u32 update[2] = { 0x11223344u, 0x55667788u };
    RHIBufferDesc desc;
    RHIBuffer buf;
    RHICmdBuffer *cmd;
    memset(&desc, 0, sizeof(desc));
    desc.usage = RHI_BUFFER_USAGE_STORAGE | RHI_BUFFER_USAGE_DEVICE_ADDRESS;
    desc.size = sizeof(readback);
    buf = rhi_buffer_create(g_dev, &desc);
    ASSERT_TRUE(rhi_handle_valid(buf));
    cmd = rhi_frame_begin(g_dev);
    ASSERT_TRUE(cmd != NULL);
    rhi_cmd_fill_buffer(cmd, buf, 0u, sizeof(readback), 0xA5A5A5A5u);
    rhi_cmd_update_buffer(cmd, buf, 0u, update, sizeof(update));
    ASSERT_EQ(rhi_frame_end_ex(g_dev), RHI_RESULT_OK);
    ASSERT_EQ(rhi_present_ex(g_dev), RHI_RESULT_OK);
    ASSERT_TRUE(rhi_buffer_read(g_dev, buf, readback, 0u, sizeof(readback)));
    ASSERT_EQ(readback[0], update[0]);
    ASSERT_EQ(readback[1], update[1]);
    ASSERT_EQ(readback[2], 0xA5A5A5A5u);
    ASSERT_EQ(readback[3], 0xA5A5A5A5u);
    rhi_buffer_destroy(g_dev, buf);
}

TEST(texture_create_readback_roundtrip) {
    /* RGBA8 4B/px byte contract (rhi.h:501). */
    static const u8 texels[16] = {
        255,0,0,255, 0,255,0,255, 0,0,255,255, 255,255,255,255 };
    u8 out[16];
    RHITextureDesc tdesc;
    memset(&tdesc, 0, sizeof(tdesc));
    memset(out, 0, sizeof(out));
    tdesc.width = 2u; tdesc.height = 2u;
    tdesc.format = RHI_FORMAT_R8G8B8A8_UNORM; tdesc.mip_levels = 1u;
    tdesc.data = texels;
    RHITexture tex = rhi_texture_create(g_dev, &tdesc);
    ASSERT_TRUE(rhi_handle_valid(tex));
    ASSERT_TRUE(rhi_texture_read_pixels(g_dev, tex, out, sizeof(out)));
    ASSERT_TRUE(memcmp(out, texels, sizeof(out)) == 0);
    rhi_texture_destroy(g_dev, tex);
}

TEST(indirect_abi_rule_shared) {
    /* The shared validator stays authoritative (rhi.h:227-230). */
    ASSERT_TRUE(rhi_indirect_abi_valid((u32)sizeof(RHIIndexedIndirectCommand), 1u));
    ASSERT_FALSE(rhi_indirect_abi_valid(8u, 0u));
}

#if defined(_WIN32)
/* Review fix 1 regression: a partial RTV-slot take failure during swapchain
 * creation must return the taken slots to the free-list exactly once (the
 * old code gave them back manually AND via rhi_d3d12_swapchain_destroy,
 * doubling entries and aliasing later takers). */
TEST(swapchain_rtv_take_failure_returns_slots_once) {
    RHI_D3D12Context *ctx = (RHI_D3D12Context *)g_dev->backend_data;
    RHI_D3D12DescriptorAlloc *alloc = &ctx->rtv_alloc;
    UINT taken[RHI_D3D12_RTV_CAPACITY];
    UINT count = 0u;
    UINT i;
    UINT j;
    RHI_D3D12Swapchain sc2;
    HRESULT hr;
    /* Hermetic opt-in (CTest also injects this via ENVIRONMENT). */
    _putenv("BREAK_D3D12_TEST_FALLBACK_HWND=1");
    /* Leave exactly 2 free slots: a 3-back-buffer swapchain must fail on
     * the third take, after slots 0 and 1 were taken. */
    while (alloc->free_count > 2u) {
        UINT slot = rhi_d3d12_descriptor_take(ctx, alloc);
        ASSERT_TRUE(slot != UINT_MAX);
        taken[count++] = slot;
    }
    hr = rhi_d3d12_swapchain_create(ctx, &sc2, (HWND)(void *)1, 8u, 8u);
    ASSERT_TRUE(FAILED(hr));
    /* Exactly the 2 pre-failure free slots remain: no double give-back. */
    ASSERT_EQ(alloc->free_count, 2u);
    while (count > 0u)
        rhi_d3d12_descriptor_give_back(alloc, taken[--count], 0u);
    /* The live swapchain keeps its 3 slots; everything else is back. */
    ASSERT_EQ(alloc->free_count, alloc->capacity - RHI_D3D12_BACKBUFFER_COUNT);
    for (i = 0u; i < alloc->free_count; ++i)
        for (j = i + 1u; j < alloc->free_count; ++j)
            ASSERT_TRUE(alloc->free_slots[i] != alloc->free_slots[j]);
}

/* Review fix 2 regression: the indexed ABI rule must not gate non-indexed
 * indirect draws; 16-byte D3D12_DRAW_ARGUMENTS strides are valid there. */
TEST(indirect_stride_gate_per_topology) {
    ASSERT_TRUE(rhi_d3d12_indirect_args_valid(0u, 16u, 1u));
    ASSERT_FALSE(rhi_d3d12_indirect_args_valid(0u, 20u, 1u));
    ASSERT_FALSE(rhi_d3d12_indirect_args_valid(0u, 16u, 0u));
    ASSERT_FALSE(rhi_d3d12_indirect_args_valid(0u, 8u, 1u));
    ASSERT_TRUE(rhi_d3d12_indirect_args_valid(1u, 20u, 1u));
    ASSERT_FALSE(rhi_d3d12_indirect_args_valid(1u, 24u, 1u));
    ASSERT_FALSE(rhi_d3d12_indirect_args_valid(1u, 8u, 0u));
}

/* Review fix 3 regression: a GPU-busy youngest free slot must not mask
 * deeper completed slots (the old top-only check falsely exhausted the
 * heap). Uses the DSV allocator, idle in this test. */
TEST(descriptor_take_scans_past_busy_top) {
    RHI_D3D12Context *ctx = (RHI_D3D12Context *)g_dev->backend_data;
    RHI_D3D12DescriptorAlloc *alloc = &ctx->dsv_alloc;
    UINT held[RHI_D3D12_DSV_CAPACITY];
    UINT count = 0u;
    UINT a;
    UINT b;
    UINT c;
    /* Drain the allocator so the free-stack contents are fully known. */
    while (alloc->free_count > 0u) {
        UINT slot = rhi_d3d12_descriptor_take(ctx, alloc);
        ASSERT_TRUE(slot != UINT_MAX);
        held[count++] = slot;
    }
    c = held[--count];
    b = held[--count];
    a = held[--count];
    /* Free stack = [c(completed), b(busy), a(busy)] bottom-to-top: the busy
     * youngest entry must not mask the completed c underneath. */
    rhi_d3d12_descriptor_give_back(alloc, c, 0u);
    rhi_d3d12_descriptor_give_back(alloc, b, ~(UINT64)0u);
    rhi_d3d12_descriptor_give_back(alloc, a, ~(UINT64)0u);
    ASSERT_EQ(rhi_d3d12_descriptor_take(ctx, alloc), c);
    /* Everything left is genuinely in flight: fail closed. */
    ASSERT_EQ(rhi_d3d12_descriptor_take(ctx, alloc), UINT_MAX);
    /* a and b were never taken (the fail-closed take left them on the free
     * stack): clear their retire fences in place. Only the actually-held c
     * is handed back — giving a/b back again would duplicate stack entries
     * and push free_count past capacity (heap overflow). */
    alloc->slot_fence[a] = 0u;
    alloc->slot_fence[b] = 0u;
    rhi_d3d12_descriptor_give_back(alloc, c, 0u);
    while (count > 0u)
        rhi_d3d12_descriptor_give_back(alloc, held[--count], 0u);
    ASSERT_EQ(alloc->free_count, alloc->capacity);
}
#endif

int main(void) {
#if defined(_WIN32)
    RHIResult r = RHI_RESULT_OK;
    g_dev = rhi_device_create_ex(RHI_BACKEND_D3D12, (void *)1, NULL, 64, 64, &r);
    if (g_dev == NULL) return 77;
    printf("=== Running Tests ===\n");
    RUN_TEST(buffer_write_read_roundtrip);
    RUN_TEST(command_buffer_fill_and_update_roundtrip);
    RUN_TEST(texture_create_readback_roundtrip);
    RUN_TEST(indirect_abi_rule_shared);
    RUN_TEST(swapchain_rtv_take_failure_returns_slots_once);
    RUN_TEST(indirect_stride_gate_per_topology);
    RUN_TEST(descriptor_take_scans_past_busy_top);
    if (rhi_device_drain_ex(g_dev) != RHI_RESULT_OK) g_test_fail++;
    rhi_device_destroy(g_dev);
    printf("\n=== Results: %d passed, %d failed, %d total ===\n",
           g_test_pass, g_test_fail, g_test_count);
    return g_test_fail > 0 ? 1 : 0;
#else
    return 77;
#endif
}
