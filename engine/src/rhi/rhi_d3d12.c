#if defined(_WIN32)
#define WIN32_LEAN_AND_MEAN
#define COBJMACROS
#include <windows.h>
#include <dxgi1_6.h>
#include <d3d12.h>

/* Route d3d12.dll to the side-by-side Agility SDK deployed next to the
 * executable (Task 1 lock: version 1.616.0 -> SDK version 616). */
__declspec(dllexport) const UINT D3D12SDKVersion = 616u;
__declspec(dllexport) const char *D3D12SDKPath = ".\\";
#endif

#include <rhi/rhi_d3d12.h>

#if defined(_WIN32)

#include <rhi/rhi.h>
#include <rhi/rhi_native_vulkan.h>
#include <rhi/rhi_backend_internal.h>
#include <core/log.h>
#include <core/shader_io.h>

#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define RHI_D3D12_FENCE_TIMEOUT_MS 20000u

/* The resource a view or binding of `bd` must point at right now. For an
 * UPLOAD-heap buffer that rhi_cmd_update_buffer / _fill_buffer wrote earlier
 * in this frame, that is the write's snapshot (rhi_d3d12_record_buffer_write):
 * the buffer itself already holds the frame's LAST write, so binding it
 * directly would give every earlier draw the last draw's data. Every binder
 * that reads a buffer -- vertex, index, CBV, SRV, texel -- goes through
 * here. */
static ID3D12Resource *rhi_d3d12_buffer_view_source(const RHI_D3D12Context *ctx,
                                                    const RHI_D3D12Buffer *bd) {
    if (!bd->device_local && bd->alias_resource != NULL &&
        bd->alias_frame == ctx->debug_frame)
        return bd->alias_resource;
    return bd->resource;
}

static void rhi_d3d12_release(IUnknown **object) {
    if (*object != NULL) {
        IUnknown_Release(*object);
        *object = NULL;
    }
}

static int rhi_d3d12_should_fail(const RHI_D3D12Context *context,
                                 RHI_D3D12CreateFailure stage) {
    return context->injected_failure == stage;
}

/* ---- Task 5: format mapping ----
 * Full RHIFormat coverage (rhi.h:143-151); RHI_FORMAT_UNDEFINED must never
 * reach here (descriptor validators reject it), so it maps to UNKNOWN and
 * callers treat UNKNOWN as a hard failure. */
static DXGI_FORMAT rhi_d3d12_format(RHIFormat format) {
    switch (format) {
    case RHI_FORMAT_R8G8B8A8_UNORM:      return DXGI_FORMAT_R8G8B8A8_UNORM;
    case RHI_FORMAT_B8G8R8A8_UNORM:      return DXGI_FORMAT_B8G8R8A8_UNORM;
    case RHI_FORMAT_R16G16B16A16_SFLOAT: return DXGI_FORMAT_R16G16B16A16_FLOAT;
    case RHI_FORMAT_R16G16_SFLOAT:       return DXGI_FORMAT_R16G16_FLOAT;
    case RHI_FORMAT_R32_FLOAT:           return DXGI_FORMAT_R32_FLOAT;
    case RHI_FORMAT_D32_FLOAT:           return DXGI_FORMAT_D32_FLOAT;
    default:                             return DXGI_FORMAT_UNKNOWN;
    }
}

/* Native-layout texel bytes (rhi.h:281-285): RGBA8/BGRA8 4B/px; RG16F 4B/px
 * f16 pairs; RGBA16F 8B/px f16 quads; R32F/D32F 4B/px f32. */
static UINT rhi_d3d12_format_bytes_per_pixel(RHIFormat format) {
    return format == RHI_FORMAT_R16G16B16A16_SFLOAT ? 8u : 4u;
}

/* ---- Task 5: descriptor allocator (free-list + fence retire) ---- */
HRESULT rhi_d3d12_descriptor_alloc_init(RHI_D3D12DescriptorAlloc *alloc,
                                        ID3D12DescriptorHeap *heap,
                                        UINT increment, UINT capacity) {
    UINT i;
    if (alloc == NULL || heap == NULL || capacity == 0u) return E_INVALIDARG;
    alloc->free_slots = (UINT *)malloc(capacity * sizeof(UINT));
    alloc->slot_fence = (UINT64 *)calloc(capacity, sizeof(UINT64));
    if (alloc->free_slots == NULL || alloc->slot_fence == NULL) {
        free(alloc->free_slots);
        free(alloc->slot_fence);
        alloc->free_slots = NULL;
        alloc->slot_fence = NULL;
        return E_OUTOFMEMORY;
    }
    for (i = 0u; i < capacity; ++i) alloc->free_slots[i] = i;
    alloc->heap = heap;
    alloc->increment = increment;
    alloc->capacity = capacity;
    alloc->free_count = capacity;
    return S_OK;
}

void rhi_d3d12_descriptor_alloc_destroy(RHI_D3D12DescriptorAlloc *alloc) {
    if (alloc == NULL) return;
    free(alloc->free_slots);
    free(alloc->slot_fence);
    alloc->free_slots = NULL;
    alloc->slot_fence = NULL;
    alloc->heap = NULL;
    alloc->increment = 0u;
    alloc->capacity = 0u;
    alloc->free_count = 0u;
}

UINT rhi_d3d12_descriptor_take(RHI_D3D12Context *ctx,
                               RHI_D3D12DescriptorAlloc *alloc) {
    UINT64 completed;
    UINT i;
    /* Scan the whole free stack (bottom = oldest retire) for a slot whose
     * retire fence has completed. A GPU-busy youngest entry must not mask
     * deeper completed slots (review fix: the old top-only check produced
     * false exhaustion under churn, most acute on the then 16-slot DSV heap).
     * Still fail-closed: returns UINT_MAX only when every free slot is
     * genuinely in flight. */
    completed = ID3D12Fence_GetCompletedValue(ctx->fence);
    for (i = 0u; i < alloc->free_count; ++i) {
        UINT slot = alloc->free_slots[i];
        if (alloc->slot_fence[slot] == 0u || completed >= alloc->slot_fence[slot]) {
            alloc->free_slots[i] = alloc->free_slots[alloc->free_count - 1u];
            alloc->free_count--;
            alloc->slot_fence[slot] = 0u;
            return slot;
        }
    }
    return UINT_MAX;
}

void rhi_d3d12_descriptor_give_back(RHI_D3D12DescriptorAlloc *alloc,
                                    UINT slot, UINT64 retire_fence) {
    alloc->slot_fence[slot] = retire_fence;
    alloc->free_slots[alloc->free_count++] = slot;
}

D3D12_CPU_DESCRIPTOR_HANDLE rhi_d3d12_descriptor_cpu(
    const RHI_D3D12DescriptorAlloc *alloc, UINT slot) {
    D3D12_CPU_DESCRIPTOR_HANDLE base;
    ID3D12DescriptorHeap_GetCPUDescriptorHandleForHeapStart(alloc->heap, &base);
    base.ptr += (SIZE_T)slot * (SIZE_T)alloc->increment;
    return base;
}

D3D12_GPU_DESCRIPTOR_HANDLE rhi_d3d12_descriptor_gpu(
    const RHI_D3D12DescriptorAlloc *alloc, UINT slot) {
    D3D12_GPU_DESCRIPTOR_HANDLE base;
    ID3D12DescriptorHeap_GetGPUDescriptorHandleForHeapStart(alloc->heap, &base);
    base.ptr += (UINT64)slot * (UINT64)alloc->increment;
    return base;
}

UINT64 rhi_d3d12_retire_fence(const RHI_D3D12Context *context) {
    return context->next_fence > 1u ? context->next_fence - 1u : 0u;
}

static void rhi_d3d12_cleanup_objects(RHI_D3D12Context *context) {
    size_t i;
    if (context == NULL) return;
    if (context->fence_event != NULL) {
        CloseHandle(context->fence_event);
        context->fence_event = NULL;
    }
    rhi_d3d12_release((IUnknown **)&context->fence);
    for (i = 0u; i < 2u; ++i) {
        UINT k;
        for (k = 0u; k < context->frame_staging_count[i]; ++k)
            rhi_d3d12_release((IUnknown **)&context->frame_staging[i][k]);
        free(context->frame_staging[i]);
        context->frame_staging[i] = NULL;
        context->frame_staging_count[i] = 0u;
        context->frame_staging_cap[i] = 0u;
    }
    rhi_d3d12_descriptor_alloc_destroy(&context->rtv_alloc);
    rhi_d3d12_descriptor_alloc_destroy(&context->dsv_alloc);
    rhi_d3d12_descriptor_alloc_destroy(&context->cbv_srv_uav_alloc);
    rhi_d3d12_descriptor_alloc_destroy(&context->sampler_alloc);
    rhi_d3d12_release((IUnknown **)&context->draw_indexed_signature);
    rhi_d3d12_release((IUnknown **)&context->draw_signature);
    rhi_d3d12_release((IUnknown **)&context->upload_list);
    rhi_d3d12_release((IUnknown **)&context->upload_allocator);
    rhi_d3d12_release((IUnknown **)&context->sampler_heap);
    rhi_d3d12_release((IUnknown **)&context->cbv_srv_uav_heap);
    rhi_d3d12_release((IUnknown **)&context->dsv_heap);
    rhi_d3d12_release((IUnknown **)&context->rtv_heap);
    for (i = 0u; i < 2u; ++i) {
        rhi_d3d12_release((IUnknown **)&context->command_lists[i]);
        rhi_d3d12_release((IUnknown **)&context->allocators[i]);
    }
    rhi_d3d12_release((IUnknown **)&context->copy_queue);
    rhi_d3d12_release((IUnknown **)&context->compute_queue);
    rhi_d3d12_release((IUnknown **)&context->direct_queue);
    rhi_d3d12_release((IUnknown **)&context->device);
    rhi_d3d12_release((IUnknown **)&context->adapter);
    rhi_d3d12_release((IUnknown **)&context->factory);
    context->frame_fence[0] = 0u;
    context->frame_fence[1] = 0u;
    context->frame_parity = 0u;
    context->acquire_in_flight = 0u;
    context->frame_started = 0u;
    context->frame_submitted = 0u;
    context->rtv_increment = 0u;
    context->dsv_increment = 0u;
    context->cbv_srv_uav_increment = 0u;
    context->sampler_increment = 0u;
    context->bound_rtv_count = 0u;
    context->bound_dsv_valid = 0u;
    context->bound_pipeline = NULL;
    context->bound_pipeline_compute = 0u;
    context->next_fence = 0u;
    context->completed_fence = 0u;
    context->descriptor_retire_fence = 0u;
    context->descriptor_live = 0u;
    context->device_lost = 0u;
    context->removed_reason = S_OK;
    context->dred_enabled = 0u;
}

/* Adapter enumeration with scoring: high-performance preference, software
 * adapters skipped, WARP only under an explicit env var so production never
 * silently degrades. Picks the hardware adapter with the most dedicated
 * VRAM that can actually create a FL12 device. */
static HRESULT rhi_d3d12_pick_adapter(IDXGIFactory6 *factory, IDXGIAdapter1 **out) {
    IDXGIAdapter1 *best = NULL;
    SIZE_T best_memory = 0;
    UINT index = 0u;
    if (getenv("ENGINE_D3D12_WARP") != NULL) {
        IDXGIAdapter *warp = NULL;
        HRESULT hr = IDXGIFactory4_EnumWarpAdapter(factory, &IID_IDXGIAdapter, (void **)&warp);
        if (SUCCEEDED(hr)) { *out = (IDXGIAdapter1 *)warp; return S_OK; }
        return hr;
    }
    for (;;) {
        IDXGIAdapter1 *candidate = NULL;
        DXGI_ADAPTER_DESC1 desc;
        HRESULT hr = IDXGIFactory6_EnumAdapterByGpuPreference(
            factory, index++, DXGI_GPU_PREFERENCE_HIGH_PERFORMANCE,
            &IID_IDXGIAdapter1, (void **)&candidate);
        if (hr == DXGI_ERROR_NOT_FOUND) break;
        if (FAILED(hr)) break;
        if (SUCCEEDED(IDXGIAdapter1_GetDesc1(candidate, &desc)) &&
            (desc.Flags & DXGI_ADAPTER_FLAG_SOFTWARE) == 0u &&
            SUCCEEDED(D3D12CreateDevice((IUnknown *)candidate, D3D_FEATURE_LEVEL_12_0,
                                        &IID_ID3D12Device, NULL)) &&
            (best == NULL || desc.DedicatedVideoMemory > best_memory)) {
            if (best != NULL) IDXGIAdapter1_Release(best);
            best = candidate; best_memory = desc.DedicatedVideoMemory; candidate = NULL;
        }
        if (candidate != NULL) IDXGIAdapter1_Release(candidate);
    }
    if (best == NULL) return DXGI_ERROR_NOT_FOUND;
    *out = best;
    return S_OK;
}

static HRESULT rhi_d3d12_select_adapter(RHI_D3D12Context *context) {
    /* Task 8: ENGINE_D3D12_DEBUG builds pair the debug layer (enabled in
     * rhi_d3d12_context_create before this runs) with the debug DXGI
     * factory; release builds keep flags=0 (zero debug overhead). */
#if defined(ENGINE_D3D12_DEBUG)
    const UINT factory_flags = DXGI_CREATE_FACTORY_DEBUG;
#else
    const UINT factory_flags = 0u;
#endif
    HRESULT hr = CreateDXGIFactory2(factory_flags, &IID_IDXGIFactory6,
                                    (void **)&context->factory);
    if (FAILED(hr)) return hr;
    return rhi_d3d12_pick_adapter(context->factory, &context->adapter);
}

/* DRED 1.x: force-enable auto breadcrumbs + page faults before device
 * creation so a later device removal has postmortem data to dump. */
static void rhi_d3d12_dred_enable(RHI_D3D12Context *context) {
    ID3D12DeviceRemovedExtendedDataSettings *settings = NULL;
    if (FAILED(D3D12GetDebugInterface(
            &IID_ID3D12DeviceRemovedExtendedDataSettings, (void **)&settings)))
        return;
    ID3D12DeviceRemovedExtendedDataSettings_SetAutoBreadcrumbsEnablement(
        settings, D3D12_DRED_ENABLEMENT_FORCED_ON);
    ID3D12DeviceRemovedExtendedDataSettings_SetPageFaultEnablement(
        settings, D3D12_DRED_ENABLEMENT_FORCED_ON);
    ID3D12DeviceRemovedExtendedDataSettings_Release(settings);
    context->dred_enabled = 1u;
}

static void rhi_d3d12_dred_dump(RHI_D3D12Context *ctx) {
    ID3D12DeviceRemovedExtendedData1 *dred = NULL;
    D3D12_DRED_AUTO_BREADCRUMBS_OUTPUT1 crumbs;
    D3D12_DRED_PAGE_FAULT_OUTPUT1 faults;
    if (!ctx->dred_enabled) return;
    if (FAILED(ID3D12Device_QueryInterface(ctx->device,
            &IID_ID3D12DeviceRemovedExtendedData1, (void **)&dred))) return;
    /* Page faults first: a descriptor pointing at freed or bogus memory faults,
     * and the faulting address names the resource. Breadcrumbs only say which
     * command list got that far, which is much weaker evidence. DRED page
     * faulting is already forced on in rhi_d3d12_dred_enable — it was enabled
     * but never read, so the half that identifies WHAT was wrong went unused. */
    ZeroMemory(&faults, sizeof(faults));
    if (SUCCEEDED(ID3D12DeviceRemovedExtendedData1_GetPageFaultAllocationOutput1(
            dred, &faults)) && faults.PageFaultVA != 0) {
        LOG_ERROR("DRED page fault at VA=%p",
                  (const void *)(ULONG_PTR)faults.PageFaultVA);
        /* Walking the existing-allocation chain names what the bad address
         * belongs to; a non-null recent-FREED chain instead means the address
         * was freed — the signature of a descriptor outliving its buffer. */
        {
            const D3D12_DRED_ALLOCATION_NODE1 *node =
                faults.pHeadExistingAllocationNode;
            for (u32 i = 0; node != NULL && i < 4u; ++i, node = node->pNext) {
                LOG_ERROR("DRED fault alloc[%u] type=%d name=%s", i,
                          (int)node->AllocationType,
                          node->ObjectNameA ? node->ObjectNameA : "(unnamed)");
            }
        }
        if (faults.pHeadRecentFreedAllocationNode != NULL)
            LOG_ERROR("DRED fault: the faulting address falls in a RECENTLY "
                      "FREED allocation");
    }
    if (SUCCEEDED(ID3D12DeviceRemovedExtendedData1_GetAutoBreadcrumbsOutput1(dred, &crumbs))) {
        const D3D12_AUTO_BREADCRUMB_NODE1 *node = crumbs.pHeadAutoBreadcrumbNode;
        while (node != NULL) {
            LOG_ERROR("DRED node: cmdlist=%S last_op=%u",
                      node->pCommandListDebugNameW ? node->pCommandListDebugNameW : L"(unnamed)",
                      (unsigned)(node->pLastBreadcrumbValue ? *node->pLastBreadcrumbValue : 0u));
            node = node->pNext;
        }
    }
    ID3D12DeviceRemovedExtendedData1_Release(dred);
}

static RHIResult rhi_d3d12_note_device_lost(RHI_D3D12Context *ctx) {
    if (!ctx->device_lost) {
        ctx->removed_reason = ID3D12Device_GetDeviceRemovedReason(ctx->device);
        LOG_ERROR("D3D12 device removed: 0x%08lx", (unsigned long)ctx->removed_reason);
        rhi_d3d12_dred_dump(ctx);
        ctx->device_lost = 1u;
    }
    return RHI_RESULT_DEVICE_LOST;
}

static RHIResult rhi_d3d12_wait_frame_slot(RHI_D3D12Context *ctx, UINT slot) {
    UINT64 target;
    HRESULT hr;
    if (ctx->device_lost) return RHI_RESULT_DEVICE_LOST;
    target = ctx->frame_fence[slot];
    if (target == 0u || ID3D12Fence_GetCompletedValue(ctx->fence) >= target)
        return RHI_RESULT_OK;
    hr = ID3D12Fence_SetEventOnCompletion(ctx->fence, target, ctx->fence_event);
    if (hr == DXGI_ERROR_DEVICE_REMOVED) return rhi_d3d12_note_device_lost(ctx);
    if (FAILED(hr)) return RHI_RESULT_SYNC_FAILED;
    if (WaitForSingleObject(ctx->fence_event, RHI_D3D12_FENCE_TIMEOUT_MS) != WAIT_OBJECT_0) {
        /* A fence unsignaled for 20 s mirrors the VK sticky-loss rule
         * (rhi.h:854-858): latch lost so callers wind down. */
        return rhi_d3d12_note_device_lost(ctx);
    }
    ctx->completed_fence = target;
    return RHI_RESULT_OK;
}

/* Present packets are queued AFTER the frame's submit signal, so the frame
 * slots alone do not cover them: a drain for resize/destroy must order
 * behind everything already enqueued (frames, uploads, presents), or back
 * buffers can be final-released while the GPU/compositor still references
 * them (debug-layer CORRUPTION: EXECUTION ERROR #921). Enqueue a fresh
 * signal and wait it. */
static RHIResult rhi_d3d12_drain_gpu(RHI_D3D12Context *ctx) {
    UINT64 value;
    HRESULT hr;
    if (ctx->device_lost) return RHI_RESULT_DEVICE_LOST;
    if (ctx->direct_queue == NULL || ctx->fence == NULL ||
        ctx->fence_event == NULL || ctx->next_fence == UINT64_MAX)
        return RHI_RESULT_OK;
    value = ctx->next_fence++;
    hr = ID3D12CommandQueue_Signal(ctx->direct_queue, ctx->fence, value);
    if (hr == DXGI_ERROR_DEVICE_REMOVED) return rhi_d3d12_note_device_lost(ctx);
    if (FAILED(hr)) return RHI_RESULT_SYNC_FAILED;
    hr = ID3D12Fence_SetEventOnCompletion(ctx->fence, value, ctx->fence_event);
    if (hr == DXGI_ERROR_DEVICE_REMOVED) return rhi_d3d12_note_device_lost(ctx);
    if (FAILED(hr)) return RHI_RESULT_SYNC_FAILED;
    if (WaitForSingleObject(ctx->fence_event, RHI_D3D12_FENCE_TIMEOUT_MS) != WAIT_OBJECT_0)
        return rhi_d3d12_note_device_lost(ctx);
    ctx->completed_fence = value;
    return RHI_RESULT_OK;
}

/* Task 7 consumes this via capabilities.feature_bits; the DXR probe itself
 * lives here so device creation already reports an honest feature set. */
static u32 rhi_d3d12_probe_feature_bits(const RHI_D3D12Context *ctx) {
    D3D12_FEATURE_DATA_D3D12_OPTIONS5 options5;
    ZeroMemory(&options5, sizeof(options5));
    if (SUCCEEDED(ID3D12Device_CheckFeatureSupport(
            ctx->device, D3D12_FEATURE_D3D12_OPTIONS5, &options5,
            (UINT)sizeof(options5))) &&
        options5.RaytracingTier != D3D12_RAYTRACING_TIER_NOT_SUPPORTED)
        return RHI_FEATURE_ACCELERATION_STRUCTURE;
    return 0u;
}

HRESULT rhi_d3d12_context_create(RHI_D3D12Context *context,
                                 RHI_D3D12CreateFailure injected_failure) {
    D3D12_COMMAND_QUEUE_DESC queue_desc;
    D3D12_DESCRIPTOR_HEAP_DESC heap_desc;
    HRESULT hr;
    UINT i;
    if (context == NULL) return E_INVALIDARG;
    ZeroMemory(context, sizeof(*context));
    context->injected_failure = injected_failure;
#if defined(ENGINE_D3D12_DEBUG)
    /* Task 8: debug layer + GPU-based validation, enabled before the DXGI
     * factory and the device are created (both latch debug state at
     * creation time). DRED is already forced on unconditionally by
     * rhi_d3d12_dred_enable below; debug configs add the layers on top.
     * The layers come from d3d12SDKLayers.dll (Agility redist deployed next
     * to the exe); without it D3D12GetDebugInterface fails and we log
     * instead of faking validation. */
    {
        ID3D12Debug1 *debug = NULL;
        if (SUCCEEDED(D3D12GetDebugInterface(&IID_ID3D12Debug1, (void **)&debug))) {
            ID3D12Debug1_EnableDebugLayer(debug);
            ID3D12Debug1_SetEnableGPUBasedValidation(debug, TRUE);
            ID3D12Debug1_Release(debug);
            LOG_INFO("D3D12: debug layer + GPU-based validation enabled "
                     "(ENGINE_D3D12_DEBUG)");
        } else {
            LOG_WARN("D3D12: ENGINE_D3D12_DEBUG is set but the debug layer is "
                     "unavailable (deploy d3d12SDKLayers.dll next to the exe)");
        }
    }
#endif
    if (rhi_d3d12_should_fail(context, RHI_D3D12_FAIL_ADAPTER)) {
        hr = E_FAIL;
        goto fail;
    }
    hr = rhi_d3d12_select_adapter(context);
    if (FAILED(hr)) goto fail;
    if (rhi_d3d12_should_fail(context, RHI_D3D12_FAIL_DEVICE)) {
        hr = E_FAIL;
        goto fail;
    }
    rhi_d3d12_dred_enable(context);
    hr = D3D12CreateDevice((IUnknown *)context->adapter, D3D_FEATURE_LEVEL_12_0,
                           &IID_ID3D12Device, (void **)&context->device);
    if (FAILED(hr)) {
        /* FL12 probe passed during scoring; a 12_0 failure here is
         * unexpected, but keep the 11_0 fallback for parity with the
         * original probe path. */
        hr = D3D12CreateDevice((IUnknown *)context->adapter, D3D_FEATURE_LEVEL_11_0,
                               &IID_ID3D12Device, (void **)&context->device);
    }
    if (FAILED(hr)) goto fail;
    ZeroMemory(&queue_desc, sizeof(queue_desc));
    queue_desc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;
    if (rhi_d3d12_should_fail(context, RHI_D3D12_FAIL_QUEUE)) {
        hr = E_FAIL;
        goto fail;
    }
    hr = ID3D12Device_CreateCommandQueue(context->device, &queue_desc,
                                         &IID_ID3D12CommandQueue,
                                         (void **)&context->direct_queue);
    if (FAILED(hr)) goto fail;
    queue_desc.Type = D3D12_COMMAND_LIST_TYPE_COMPUTE;
    hr = ID3D12Device_CreateCommandQueue(context->device, &queue_desc,
                                         &IID_ID3D12CommandQueue,
                                         (void **)&context->compute_queue);
    if (FAILED(hr)) goto fail;
    queue_desc.Type = D3D12_COMMAND_LIST_TYPE_COPY;
    hr = ID3D12Device_CreateCommandQueue(context->device, &queue_desc,
                                         &IID_ID3D12CommandQueue,
                                         (void **)&context->copy_queue);
    if (FAILED(hr)) goto fail;
    for (i = 0u; i < 2u; ++i) {
        if (rhi_d3d12_should_fail(context, RHI_D3D12_FAIL_ALLOCATOR)) {
            hr = E_FAIL;
            goto fail;
        }
        hr = ID3D12Device_CreateCommandAllocator(
            context->device, D3D12_COMMAND_LIST_TYPE_DIRECT,
            &IID_ID3D12CommandAllocator, (void **)&context->allocators[i]);
        if (FAILED(hr)) goto fail;
        if (rhi_d3d12_should_fail(context, RHI_D3D12_FAIL_COMMAND_LIST)) {
            hr = E_FAIL;
            goto fail;
        }
        hr = ID3D12Device_CreateCommandList(
            context->device, 0u, D3D12_COMMAND_LIST_TYPE_DIRECT,
            context->allocators[i], NULL, &IID_ID3D12GraphicsCommandList,
            (void **)&context->command_lists[i]);
        if (FAILED(hr)) goto fail;
        hr = ID3D12GraphicsCommandList_Close(context->command_lists[i]);
        if (FAILED(hr)) goto fail;
    }
    ZeroMemory(&heap_desc, sizeof(heap_desc));
    heap_desc.NumDescriptors = RHI_D3D12_RTV_CAPACITY;
    heap_desc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
    if (rhi_d3d12_should_fail(context, RHI_D3D12_FAIL_DESCRIPTOR)) {
        hr = E_FAIL;
        goto fail;
    }
    hr = ID3D12Device_CreateDescriptorHeap(context->device, &heap_desc,
                                           &IID_ID3D12DescriptorHeap,
                                           (void **)&context->rtv_heap);
    if (FAILED(hr)) goto fail;
    heap_desc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_DSV;
    heap_desc.NumDescriptors = RHI_D3D12_DSV_CAPACITY;
    hr = ID3D12Device_CreateDescriptorHeap(context->device, &heap_desc,
                                           &IID_ID3D12DescriptorHeap,
                                           (void **)&context->dsv_heap);
    if (FAILED(hr)) goto fail;
    heap_desc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
    heap_desc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;
    heap_desc.NumDescriptors = RHI_D3D12_CBV_SRV_UAV_CAPACITY;
    hr = ID3D12Device_CreateDescriptorHeap(context->device, &heap_desc,
                                           &IID_ID3D12DescriptorHeap,
                                           (void **)&context->cbv_srv_uav_heap);
    if (FAILED(hr)) goto fail;
    heap_desc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_SAMPLER;
    heap_desc.NumDescriptors = RHI_D3D12_SAMPLER_CAPACITY;
    hr = ID3D12Device_CreateDescriptorHeap(context->device, &heap_desc,
                                           &IID_ID3D12DescriptorHeap,
                                           (void **)&context->sampler_heap);
    if (FAILED(hr)) goto fail;
    context->rtv_increment = ID3D12Device_GetDescriptorHandleIncrementSize(
        context->device, D3D12_DESCRIPTOR_HEAP_TYPE_RTV);
    context->dsv_increment = ID3D12Device_GetDescriptorHandleIncrementSize(
        context->device, D3D12_DESCRIPTOR_HEAP_TYPE_DSV);
    context->cbv_srv_uav_increment = ID3D12Device_GetDescriptorHandleIncrementSize(
        context->device, D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);
    context->sampler_increment = ID3D12Device_GetDescriptorHandleIncrementSize(
        context->device, D3D12_DESCRIPTOR_HEAP_TYPE_SAMPLER);
    hr = rhi_d3d12_descriptor_alloc_init(&context->rtv_alloc,
        context->rtv_heap, context->rtv_increment, RHI_D3D12_RTV_CAPACITY);
    if (FAILED(hr)) goto fail;
    hr = rhi_d3d12_descriptor_alloc_init(&context->dsv_alloc,
        context->dsv_heap, context->dsv_increment, RHI_D3D12_DSV_CAPACITY);
    if (FAILED(hr)) goto fail;
    hr = rhi_d3d12_descriptor_alloc_init(&context->cbv_srv_uav_alloc,
        context->cbv_srv_uav_heap, context->cbv_srv_uav_increment,
        RHI_D3D12_CBV_SRV_UAV_CAPACITY);
    if (FAILED(hr)) goto fail;
    hr = rhi_d3d12_descriptor_alloc_init(&context->sampler_alloc,
        context->sampler_heap, context->sampler_increment,
        RHI_D3D12_SAMPLER_CAPACITY);
    if (FAILED(hr)) goto fail;
    /* One-shot upload/readback command pair (private allocator + list; the
     * staging contract is submit-and-wait, rhi.h:394-397 semantics). */
    hr = ID3D12Device_CreateCommandAllocator(
        context->device, D3D12_COMMAND_LIST_TYPE_DIRECT,
        &IID_ID3D12CommandAllocator, (void **)&context->upload_allocator);
    if (FAILED(hr)) goto fail;
    hr = ID3D12Device_CreateCommandList(
        context->device, 0u, D3D12_COMMAND_LIST_TYPE_DIRECT,
        context->upload_allocator, NULL, &IID_ID3D12GraphicsCommandList,
        (void **)&context->upload_list);
    if (FAILED(hr)) goto fail;
    hr = ID3D12GraphicsCommandList_Close(context->upload_list);
    if (FAILED(hr)) goto fail;
    /* ExecuteIndirect command signatures, prebuilt once. The indexed stride
     * is the shared ABI struct; the shared validator stays authoritative
     * (rhi.h:219-230) — refuse to create a signature the ABI rule rejects. */
    {
        D3D12_INDIRECT_ARGUMENT_DESC argument;
        D3D12_COMMAND_SIGNATURE_DESC signature_desc;
        ZeroMemory(&argument, sizeof(argument));
        argument.Type = D3D12_INDIRECT_ARGUMENT_TYPE_DRAW;
        ZeroMemory(&signature_desc, sizeof(signature_desc));
        signature_desc.ByteStride = (UINT)sizeof(D3D12_DRAW_ARGUMENTS);
        signature_desc.NumArgumentDescs = 1u;
        signature_desc.pArgumentDescs = &argument;
        hr = ID3D12Device_CreateCommandSignature(
            context->device, &signature_desc, NULL,
            &IID_ID3D12CommandSignature, (void **)&context->draw_signature);
        if (FAILED(hr)) goto fail;
        argument.Type = D3D12_INDIRECT_ARGUMENT_TYPE_DRAW_INDEXED;
        signature_desc.ByteStride = (UINT)sizeof(RHIIndexedIndirectCommand);
        if (!rhi_indirect_abi_valid((u32)signature_desc.ByteStride, 1u)) {
            hr = E_FAIL;
            goto fail;
        }
        hr = ID3D12Device_CreateCommandSignature(
            context->device, &signature_desc, NULL,
            &IID_ID3D12CommandSignature,
            (void **)&context->draw_indexed_signature);
        if (FAILED(hr)) goto fail;
    }
    if (rhi_d3d12_should_fail(context, RHI_D3D12_FAIL_FENCE)) {
        hr = E_FAIL;
        goto fail;
    }
    hr = ID3D12Device_CreateFence(context->device, 0u, D3D12_FENCE_FLAG_NONE,
                                  &IID_ID3D12Fence, (void **)&context->fence);
    if (FAILED(hr)) goto fail;
    if (rhi_d3d12_should_fail(context, RHI_D3D12_FAIL_EVENT)) {
        hr = E_FAIL;
        goto fail;
    }
    context->fence_event = CreateEventW(NULL, FALSE, FALSE, NULL);
    if (context->fence_event == NULL) {
        hr = HRESULT_FROM_WIN32(GetLastError());
        goto fail;
    }
    context->next_fence = 1u;
    return S_OK;
fail:
    rhi_d3d12_cleanup_objects(context);
    return hr;
}

void rhi_d3d12_context_destroy(RHI_D3D12Context *context) {
    if (context == NULL) return;
    rhi_d3d12_cleanup_objects(context);
    context->injected_failure = RHI_D3D12_FAIL_NONE;
}

HRESULT rhi_d3d12_context_retire(RHI_D3D12Context *context, UINT64 value) {
    if (context == NULL || context->fence == NULL ||
        value < context->completed_fence || value >= context->next_fence)
        return E_INVALIDARG;
    if (ID3D12Fence_GetCompletedValue(context->fence) < value) {
        HRESULT hr = ID3D12Fence_SetEventOnCompletion(context->fence, value,
                                                      context->fence_event);
        if (FAILED(hr)) return hr;
        if (WaitForSingleObject(context->fence_event, INFINITE) != WAIT_OBJECT_0)
            return HRESULT_FROM_WIN32(GetLastError());
    }
    context->completed_fence = value;
    return S_OK;
}

HRESULT rhi_d3d12_descriptor_acquire(RHI_D3D12Context *context) {
    if (context == NULL || context->cbv_srv_uav_heap == NULL) return E_FAIL;
    if (context->descriptor_live && context->completed_fence < context->descriptor_retire_fence)
        return HRESULT_FROM_WIN32(ERROR_BUSY);
    context->descriptor_live = 1u;
    context->descriptor_retire_fence = 0u;
    return S_OK;
}

HRESULT rhi_d3d12_descriptor_retire(RHI_D3D12Context *context) {
    if (context == NULL || context->fence == NULL || !context->descriptor_live)
        return E_INVALIDARG;
    if (context->next_fence == UINT64_MAX) return E_FAIL;
    context->descriptor_retire_fence = context->next_fence++;
    return ID3D12CommandQueue_Signal(context->direct_queue, context->fence,
                                     context->descriptor_retire_fence);
}

HRESULT rhi_d3d12_buffer_create(RHI_D3D12Context *context, UINT64 size,
                                RHI_D3D12Resource *out_resource) {
    D3D12_HEAP_PROPERTIES properties;
    D3D12_RESOURCE_DESC description;
    HRESULT hr;
    if (context == NULL || context->device == NULL || out_resource == NULL || size == 0u)
        return E_INVALIDARG;
    ZeroMemory(out_resource, sizeof(*out_resource));
    ZeroMemory(&properties, sizeof(properties));
    properties.Type = D3D12_HEAP_TYPE_DEFAULT;
    properties.CreationNodeMask = 1u;
    properties.VisibleNodeMask = 1u;
    ZeroMemory(&description, sizeof(description));
    description.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
    description.Width = size;
    description.Height = 1u;
    description.DepthOrArraySize = 1u;
    description.MipLevels = 1u;
    description.SampleDesc.Count = 1u;
    description.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;
    hr = ID3D12Device_CreateCommittedResource(
        context->device, &properties, D3D12_HEAP_FLAG_NONE, &description,
        D3D12_RESOURCE_STATE_COMMON, NULL, &IID_ID3D12Resource,
        (void **)&out_resource->resource);
    if (FAILED(hr)) ZeroMemory(out_resource, sizeof(*out_resource));
    else out_resource->state = D3D12_RESOURCE_STATE_COMMON;
    return hr;
}

void rhi_d3d12_resource_destroy(RHI_D3D12Resource *resource) {
    if (resource == NULL) return;
    rhi_d3d12_release((IUnknown **)&resource->resource);
    resource->state = D3D12_RESOURCE_STATE_COMMON;
    resource->retire_fence = 0u;
}

HRESULT rhi_d3d12_resource_transition(RHI_D3D12Context *context,
                                      ID3D12GraphicsCommandList *command_list,
                                      RHI_D3D12Resource *resource,
                                      D3D12_RESOURCE_STATES next_state) {
    D3D12_RESOURCE_BARRIER barrier;
    if (context == NULL || context->device == NULL || command_list == NULL ||
        resource == NULL || resource->resource == NULL) return E_INVALIDARG;
    if (resource->state == next_state) return S_OK;
    ZeroMemory(&barrier, sizeof(barrier));
    barrier.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
    barrier.Transition.pResource = resource->resource;
    barrier.Transition.Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;
    barrier.Transition.StateBefore = resource->state;
    barrier.Transition.StateAfter = next_state;
    ID3D12GraphicsCommandList_ResourceBarrier(command_list, 1u, &barrier);
    resource->state = next_state;
    return S_OK;
}

#if defined(ENGINE_D3D12_DEBUG)
/* R643: the debug layer writes its messages to OutputDebugString only, so a
 * console run never saw them -- "debug layer enabled" and a clean log meant
 * nothing. Drain the device's info queue into the engine log after every
 * submit. Only CORRUPTION / ERROR / WARNING are reported; INFO and MESSAGE
 * are the layer's own chatter, and so is [820] (a clear without an optimised
 * clear value: a speed hint, emitted on every clear of every FBO). The queue
 * is cleared after each drain so a message is reported once. */
static void rhi_d3d12_drain_info_queue(RHI_D3D12Context *ctx) {
    ID3D12InfoQueue *q = NULL;
    UINT64 n, i;
    if (ctx == NULL || ctx->device == NULL) return;
    if (FAILED(ID3D12Device_QueryInterface(ctx->device, &IID_ID3D12InfoQueue,
                                           (void **)&q)))
        return;
    n = ID3D12InfoQueue_GetNumStoredMessages(q);
    for (i = 0u; i < n; ++i) {
        SIZE_T len = 0u;
        D3D12_MESSAGE *msg;
        if (FAILED(ID3D12InfoQueue_GetMessage(q, i, NULL, &len)) || len == 0u)
            continue;
        msg = (D3D12_MESSAGE *)malloc(len);
        if (msg == NULL) break;
        if (SUCCEEDED(ID3D12InfoQueue_GetMessage(q, i, msg, &len)) &&
            msg->ID != D3D12_MESSAGE_ID_CLEARRENDERTARGETVIEW_MISMATCHINGCLEARVALUE) {
            if (msg->Severity == D3D12_MESSAGE_SEVERITY_CORRUPTION ||
                msg->Severity == D3D12_MESSAGE_SEVERITY_ERROR) {
                LOG_ERROR("D3D12 debug layer [%d]: %s", (int)msg->ID,
                          msg->pDescription);
                ctx->debug_layer_errors++;
            } else if (msg->Severity == D3D12_MESSAGE_SEVERITY_WARNING) {
                LOG_WARN("D3D12 debug layer [%d]: %s", (int)msg->ID,
                         msg->pDescription);
                ctx->debug_layer_warnings++;
            }
        }
        free(msg);
    }
    ID3D12InfoQueue_ClearStoredMessages(q);
    ID3D12InfoQueue_Release(q);
}
#else
static void rhi_d3d12_drain_info_queue(RHI_D3D12Context *ctx) { (void)ctx; }
#endif

int rhi_d3d12_debug_layer_counts(RHIDevice *dev, UINT64 *errors,
                                 UINT64 *warnings, UINT64 *rt_srv_aliases) {
    RHI_D3D12Context *ctx;
    if (dev == NULL || dev->backend_data == NULL) return 0;
    ctx = (RHI_D3D12Context *)dev->backend_data;
    rhi_d3d12_drain_info_queue(ctx);
    if (errors != NULL) *errors = ctx->debug_layer_errors;
    if (warnings != NULL) *warnings = ctx->debug_layer_warnings;
    if (rt_srv_aliases != NULL) *rt_srv_aliases = ctx->rt_srv_alias_count;
#if defined(ENGINE_D3D12_DEBUG)
    return 1;
#else
    return 0;
#endif
}

HRESULT rhi_d3d12_submit(RHI_D3D12Context *context, UINT allocator_index,
                         UINT64 *out_fence) {
    ID3D12CommandList *lists[1];
    HRESULT hr;
    UINT64 value;
    if (context == NULL || context->direct_queue == NULL || context->fence == NULL ||
        out_fence == NULL || allocator_index >= 2u) return E_INVALIDARG;
    hr = ID3D12GraphicsCommandList_Close(context->command_lists[allocator_index]);
    if (FAILED(hr)) return hr;
    lists[0] = (ID3D12CommandList *)context->command_lists[allocator_index];
    ID3D12CommandQueue_ExecuteCommandLists(context->direct_queue, 1u, lists);
    rhi_d3d12_drain_info_queue(context);
    value = context->next_fence++;
    hr = ID3D12CommandQueue_Signal(context->direct_queue, context->fence, value);
    if (FAILED(hr)) return hr;
    *out_fence = value;
    return S_OK;
}

/* ---- Task 5: one-shot staging submit ----
 * Upload/readback helpers record into the private upload list, submit on the
 * direct queue, and wait on the context fence (same fence the frame slots
 * pace against, so ordering vs in-flight frames is total). Must not be
 * called between rhi_frame_begin and rhi_frame_end — same contract as
 * rhi_build_blas_one_triangle (rhi.h:394-397). */
static RHIResult rhi_d3d12_wait_fence_value(RHI_D3D12Context *ctx, UINT64 value) {
    HRESULT hr;
    if (ctx->device_lost) return RHI_RESULT_DEVICE_LOST;
    if (ID3D12Fence_GetCompletedValue(ctx->fence) >= value) {
        if (ctx->completed_fence < value) ctx->completed_fence = value;
        return RHI_RESULT_OK;
    }
    hr = ID3D12Fence_SetEventOnCompletion(ctx->fence, value, ctx->fence_event);
    if (hr == DXGI_ERROR_DEVICE_REMOVED) return rhi_d3d12_note_device_lost(ctx);
    if (FAILED(hr)) return RHI_RESULT_SYNC_FAILED;
    if (WaitForSingleObject(ctx->fence_event, RHI_D3D12_FENCE_TIMEOUT_MS) != WAIT_OBJECT_0)
        return rhi_d3d12_note_device_lost(ctx);
    ctx->completed_fence = value;
    return RHI_RESULT_OK;
}

static HRESULT rhi_d3d12_oneshot_begin(RHI_D3D12Context *ctx) {
    HRESULT hr;
    if (ctx->device_lost) return DXGI_ERROR_DEVICE_REMOVED;
    hr = ID3D12CommandAllocator_Reset(ctx->upload_allocator);
    if (FAILED(hr)) return hr;
    return ID3D12GraphicsCommandList_Reset(ctx->upload_list,
                                           ctx->upload_allocator, NULL);
}

static RHIResult rhi_d3d12_oneshot_flush(RHI_D3D12Context *ctx) {
    ID3D12CommandList *lists[1];
    UINT64 value;
    HRESULT hr = ID3D12GraphicsCommandList_Close(ctx->upload_list);
    if (hr == DXGI_ERROR_DEVICE_REMOVED) return rhi_d3d12_note_device_lost(ctx);
    if (FAILED(hr)) return RHI_RESULT_ERROR;
    lists[0] = (ID3D12CommandList *)ctx->upload_list;
    ID3D12CommandQueue_ExecuteCommandLists(ctx->direct_queue, 1u, lists);
    rhi_d3d12_drain_info_queue(ctx);
    value = ctx->next_fence++;
    hr = ID3D12CommandQueue_Signal(ctx->direct_queue, ctx->fence, value);
    if (hr == DXGI_ERROR_DEVICE_REMOVED) return rhi_d3d12_note_device_lost(ctx);
    if (FAILED(hr)) return RHI_RESULT_SYNC_FAILED;
    return rhi_d3d12_wait_fence_value(ctx, value);
}

/* Committed staging buffer on an UPLOAD or READBACK heap (Task 5 decision
 * record: staging upload via CopyBufferRegion/CopyTextureRegion; readback
 * via a READBACK heap + Map/memcpy/Unmap). */
static ID3D12Resource *rhi_d3d12_staging_buffer(RHI_D3D12Context *ctx,
                                                D3D12_HEAP_TYPE heap_type,
                                                UINT64 size) {
    D3D12_HEAP_PROPERTIES properties;
    D3D12_RESOURCE_DESC description;
    ID3D12Resource *staging = NULL;
    HRESULT hr;
    ZeroMemory(&properties, sizeof(properties));
    properties.Type = heap_type;
    properties.CreationNodeMask = 1u;
    properties.VisibleNodeMask = 1u;
    ZeroMemory(&description, sizeof(description));
    description.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
    description.Width = size;
    description.Height = 1u;
    description.DepthOrArraySize = 1u;
    description.MipLevels = 1u;
    description.SampleDesc.Count = 1u;
    description.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;
    hr = ID3D12Device_CreateCommittedResource(
        ctx->device, &properties, D3D12_HEAP_FLAG_NONE, &description,
        heap_type == D3D12_HEAP_TYPE_READBACK ? D3D12_RESOURCE_STATE_COPY_DEST
                                              : D3D12_RESOURCE_STATE_GENERIC_READ,
        NULL, &IID_ID3D12Resource, (void **)&staging);
    /* A device that has already been removed answers every later call with
     * DXGI_ERROR_DEVICE_REMOVED. Without this the loss is discovered one or
     * two calls too late, by whichever unrelated API happens to fail next, and
     * the DRED breadcrumbs for the submit that actually killed it are gone
     * by then. */
    if (hr == DXGI_ERROR_DEVICE_REMOVED) (void)rhi_d3d12_note_device_lost(ctx);
    return SUCCEEDED(hr) ? staging : NULL;
}

/* Barrier helper for plain ID3D12Resource* (swapchain buffers and staging
 * flows that do not go through RHI_D3D12Resource). */
static void rhi_d3d12_transition(ID3D12GraphicsCommandList *list,
                                 ID3D12Resource *resource,
                                 D3D12_RESOURCE_STATES before,
                                 D3D12_RESOURCE_STATES after) {
    D3D12_RESOURCE_BARRIER barrier;
    if (before == after) return;
    ZeroMemory(&barrier, sizeof(barrier));
    barrier.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
    barrier.Transition.pResource = resource;
    barrier.Transition.Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;
    barrier.Transition.StateBefore = before;
    barrier.Transition.StateAfter = after;
    ID3D12GraphicsCommandList_ResourceBarrier(list, 1u, &barrier);
}

/* ---- swapchain (plan D Task 4) ----
 * Flip model, 3 back buffers (see RHI_D3D12_BACKBUFFER_COUNT in the header).
 * Decision record: present damage uses RHIPresentRect directly — it is a
 * top-left-origin {x,y,w,h} quad, the same convention DXGI_PRESENT_PARAMETERS
 * dirty rects use, so the GL/EGL bottom-left conversion
 * (rhi_present_damage_to_bottom_left) is NOT applied on this backend. */

/* Task 5: back-buffer RTVs live in rtv_alloc slots taken for the swapchain
 * lifetime (resize re-creates the views in the SAME slots; destroy gives
 * the slots back through the fence-retire path). */
static void rhi_d3d12_swapchain_create_rtvs(RHI_D3D12Context *context,
                                            RHI_D3D12Swapchain *sc) {
    UINT i;
    for (i = 0u; i < RHI_D3D12_BACKBUFFER_COUNT; ++i) {
        ID3D12Device_CreateRenderTargetView(
            context->device, sc->backbuffers[i], NULL,
            rhi_d3d12_descriptor_cpu(&context->rtv_alloc, sc->rtv_slots[i]));
    }
}

/* ALLOW_TEARING is only legal when the factory reports support; the flag is
 * created once and restated at ResizeBuffers, and only gates the vsync=0
 * present path (vsync=1 never sets DXGI_PRESENT_ALLOW_TEARING). */
static UINT rhi_d3d12_swapchain_flags(IDXGIFactory6 *factory) {
    IDXGIFactory5 *factory5 = NULL;
    BOOL allow = FALSE;
    if (SUCCEEDED(IDXGIFactory6_QueryInterface(
            factory, &IID_IDXGIFactory5, (void **)&factory5))) {
        (void)IDXGIFactory5_CheckFeatureSupport(
            factory5, DXGI_FEATURE_PRESENT_ALLOW_TEARING,
            &allow, (UINT)sizeof(allow));
        IDXGIFactory5_Release(factory5);
    }
    return allow ? (UINT)DXGI_SWAP_CHAIN_FLAG_ALLOW_TEARING : 0u;
}

/* Contract tests hand a sentinel HWND ((HWND)1) which DXGI refuses with
 * E_ACCESSDENIED; a device-owned hidden fallback window keeps the frame
 * lifecycle exercised against a real swapchain for those tests. The fallback
 * is EXPLICIT OPT-IN ONLY: it requires BREAK_D3D12_TEST_FALLBACK_HWND=1 in
 * the environment (same convention as ENGINE_D3D12_WARP above — env-gated
 * so production can never silently degrade). A non-NULL window_native that
 * is not a real window is otherwise an argument fault: fail closed with a
 * clear error instead of rendering to an invisible window. */
static HWND rhi_d3d12_fallback_window_create(UINT width, UINT height) {
    WNDCLASSW wc;
    ZeroMemory(&wc, sizeof(wc));
    wc.lpfnWndProc = DefWindowProcW;
    wc.hInstance = GetModuleHandleW(NULL);
    wc.lpszClassName = L"BreakRhiD3D12FallbackWindow";
    if (RegisterClassW(&wc) == 0 && GetLastError() != ERROR_CLASS_ALREADY_EXISTS)
        return NULL;
    return CreateWindowExW(0, wc.lpszClassName, L"rhi-d3d12-fallback",
                           WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
                           (int)width, (int)height, NULL, NULL,
                           GetModuleHandleW(NULL), NULL);
}

HRESULT rhi_d3d12_swapchain_create(RHI_D3D12Context *context,
                                   RHI_D3D12Swapchain *out, HWND hwnd,
                                   UINT width, UINT height) {
    DXGI_SWAP_CHAIN_DESC1 desc;
    IDXGISwapChain1 *sc1 = NULL;
    HRESULT hr;
    UINT i;
    HWND target = hwnd;
    if (context == NULL || out == NULL || hwnd == NULL || width == 0u || height == 0u)
        return E_INVALIDARG;
    ZeroMemory(out, sizeof(*out));
    for (i = 0u; i < RHI_D3D12_BACKBUFFER_COUNT; ++i)
        out->rtv_slots[i] = UINT_MAX; /* not-yet-taken marker for destroy */
    if (!IsWindow(target)) {
        const char *opt_in = getenv("BREAK_D3D12_TEST_FALLBACK_HWND");
        if (opt_in == NULL || strcmp(opt_in, "1") != 0) {
            LOG_ERROR("D3D12: window_native %p is not a real HWND; refusing "
                      "device creation (BREAK_D3D12_TEST_FALLBACK_HWND=1 opts "
                      "into the test-only hidden fallback window)",
                      (void *)hwnd);
            return E_INVALIDARG;
        }
        target = rhi_d3d12_fallback_window_create(width, height);
        if (target == NULL) return E_FAIL;
        out->owned_hwnd = target;
        LOG_WARN("D3D12: window_native is not a real HWND (%p); using a "
                 "device-owned hidden fallback window (opt-in)",
                 (void *)hwnd);
    }
    ZeroMemory(&desc, sizeof(desc));
    desc.Width = width;
    desc.Height = height;
    desc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
    desc.SampleDesc.Count = 1u;
    /* Flip-model back buffers are created by DXGI with COPY_SRC already,
     * so rhi_screenshot can CopyTextureRegion from the current one. */
    desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    desc.BufferCount = RHI_D3D12_BACKBUFFER_COUNT;
    desc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
    desc.Flags = rhi_d3d12_swapchain_flags(context->factory);
    hr = IDXGIFactory6_CreateSwapChainForHwnd(context->factory,
        (IUnknown *)context->direct_queue, target, &desc, NULL, NULL, &sc1);
    if (FAILED(hr)) {
        if (out->owned_hwnd != NULL) {
            DestroyWindow(out->owned_hwnd);
            out->owned_hwnd = NULL;
        }
        return hr;
    }
    hr = IDXGISwapChain1_QueryInterface(sc1, &IID_IDXGISwapChain4, (void **)&out->swapchain);
    IDXGISwapChain1_Release(sc1);
    if (FAILED(hr)) { rhi_d3d12_swapchain_destroy(context, out); return hr; }
    /* No Alt-Enter fullscreen flip surprises; the engine owns the window. */
    IDXGIFactory6_MakeWindowAssociation(context->factory, target, DXGI_MWA_NO_ALT_ENTER);
    out->hwnd = target; out->width = width; out->height = height;
    out->format = desc.Format; out->vsync = 1u; out->flags = desc.Flags;
    for (i = 0u; i < RHI_D3D12_BACKBUFFER_COUNT; ++i) {
        out->rtv_slots[i] = rhi_d3d12_descriptor_take(context, &context->rtv_alloc);
        if (out->rtv_slots[i] == UINT_MAX) {
            /* Partial take: destroy owns the give-back (it skips UINT_MAX
             * entries and resets each returned slot to UINT_MAX), so the
             * slots land in the free-list exactly once. */
            rhi_d3d12_swapchain_destroy(context, out);
            return E_OUTOFMEMORY;
        }
    }
    for (i = 0u; i < RHI_D3D12_BACKBUFFER_COUNT; ++i) {
        hr = IDXGISwapChain4_GetBuffer(out->swapchain, i,
                                       &IID_ID3D12Resource, (void **)&out->backbuffers[i]);
        if (FAILED(hr)) { rhi_d3d12_swapchain_destroy(context, out); return hr; }
    }
    rhi_d3d12_swapchain_create_rtvs(context, out);
    out->current_index = IDXGISwapChain3_GetCurrentBackBufferIndex(
        (IDXGISwapChain3 *)out->swapchain);
    return S_OK;
}

/* The caller (rhi_device_resize) guarantees a drain before this runs.
 * On failure the released back-buffer references are re-acquired so the old
 * swapchain keeps working; DXGI_ERROR_DEVICE_REMOVED is latched upstairs. */
HRESULT rhi_d3d12_swapchain_resize(RHI_D3D12Context *context,
                                   RHI_D3D12Swapchain *swapchain,
                                   UINT width, UINT height) {
    UINT i;
    HRESULT hr;
    if (context == NULL || swapchain == NULL || width == 0u || height == 0u)
        return E_INVALIDARG;
    for (i = 0u; i < RHI_D3D12_BACKBUFFER_COUNT; ++i)
        rhi_d3d12_release((IUnknown **)&swapchain->backbuffers[i]);
    hr = IDXGISwapChain4_ResizeBuffers(swapchain->swapchain,
        RHI_D3D12_BACKBUFFER_COUNT, width, height, swapchain->format,
        swapchain->flags);
    if (FAILED(hr)) {
        for (i = 0u; i < RHI_D3D12_BACKBUFFER_COUNT; ++i)
            (void)IDXGISwapChain4_GetBuffer(swapchain->swapchain, i,
                &IID_ID3D12Resource, (void **)&swapchain->backbuffers[i]);
        return hr;
    }
    swapchain->width = width; swapchain->height = height;
    swapchain->current_index = IDXGISwapChain3_GetCurrentBackBufferIndex(
        (IDXGISwapChain3 *)swapchain->swapchain);
    for (i = 0u; i < RHI_D3D12_BACKBUFFER_COUNT; ++i) {
        hr = IDXGISwapChain4_GetBuffer(swapchain->swapchain, i,
                                       &IID_ID3D12Resource, (void **)&swapchain->backbuffers[i]);
        if (FAILED(hr)) return hr;
    }
    rhi_d3d12_swapchain_create_rtvs(context, swapchain);
    return S_OK;
}

void rhi_d3d12_swapchain_destroy(RHI_D3D12Context *context,
                                 RHI_D3D12Swapchain *swapchain) {
    UINT i;
    if (swapchain == NULL) return;
    for (i = 0u; i < RHI_D3D12_BACKBUFFER_COUNT; ++i)
        rhi_d3d12_release((IUnknown **)&swapchain->backbuffers[i]);
    rhi_d3d12_release((IUnknown **)&swapchain->swapchain);
    if (context != NULL && context->rtv_alloc.free_slots != NULL) {
        for (i = 0u; i < RHI_D3D12_BACKBUFFER_COUNT; ++i) {
            if (swapchain->rtv_slots[i] != UINT_MAX) {
                rhi_d3d12_descriptor_give_back(&context->rtv_alloc,
                    swapchain->rtv_slots[i], rhi_d3d12_retire_fence(context));
                swapchain->rtv_slots[i] = UINT_MAX;
            }
        }
    }
    if (swapchain->owned_hwnd != NULL) {
        DestroyWindow(swapchain->owned_hwnd);
        swapchain->owned_hwnd = NULL;
    }
    swapchain->hwnd = NULL;
    swapchain->width = 0u;
    swapchain->height = 0u;
    swapchain->current_index = 0u;
    swapchain->vsync = 0u;
    swapchain->flags = 0u;
    swapchain->format = DXGI_FORMAT_UNKNOWN;
    (void)context;
}

static void rhi_d3d12_set_full_target_viewport(ID3D12GraphicsCommandList *list,
                                               u32 w, u32 h);
static void rhi_d3d12_backbuffer_barrier(RHI_D3D12Swapchain *sc,
                                         ID3D12GraphicsCommandList *list,
                                         D3D12_RESOURCE_STATES before,
                                         D3D12_RESOURCE_STATES after) {
    D3D12_RESOURCE_BARRIER barrier;
    ZeroMemory(&barrier, sizeof(barrier));
    barrier.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
    barrier.Transition.pResource = sc->backbuffers[sc->current_index];
    barrier.Transition.Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;
    barrier.Transition.StateBefore = before;
    barrier.Transition.StateAfter = after;
    ID3D12GraphicsCommandList_ResourceBarrier(list, 1u, &barrier);
}

static RHIResult rhi_d3d12_present(RHI_D3D12Context *ctx, RHI_D3D12Swapchain *sc,
                                   const RHIPresentRect *rects, UINT rect_count) {
    DXGI_PRESENT_PARAMETERS params;
    RECT dirty[RHI_MAX_PRESENT_DAMAGE_RECTS];
    HRESULT hr;
    UINT present_flags = 0u;
    UINT i;
    if (ctx->device_lost) return RHI_RESULT_DEVICE_LOST;
    if (!sc->vsync && (sc->flags & DXGI_SWAP_CHAIN_FLAG_ALLOW_TEARING) != 0u)
        present_flags |= DXGI_PRESENT_ALLOW_TEARING;
    /* This stack (inbox DXGI on the RTX 4060 Laptop driver) AVs inside
     * dxgi.dll when pPresentParameters is NULL, so a valid zeroed struct is
     * always passed; zeroed fields are the documented "no damage" form. */
    ZeroMemory(&params, sizeof(params));
    if (rects != NULL && rect_count > 0u &&
        rect_count <= RHI_MAX_PRESENT_DAMAGE_RECTS) {
        /* RHIPresentRect is top-left origin {x,y,w,h}; RECT is
         * {left,top,right,bottom} — same origin, but extents must be
         * converted to corner coordinates (no bottom-left flip here). */
        for (i = 0u; i < rect_count; ++i) {
            dirty[i].left = rects[i].x;
            dirty[i].top = rects[i].y;
            dirty[i].right = rects[i].x + (LONG)rects[i].w;
            dirty[i].bottom = rects[i].y + (LONG)rects[i].h;
        }
        params.DirtyRectsCount = rect_count;
        params.pDirtyRects = dirty;
    }
    hr = IDXGISwapChain1_Present1((IDXGISwapChain1 *)sc->swapchain,
                                  sc->vsync ? 1u : 0u, present_flags, &params);
    if (hr == DXGI_ERROR_INVALID_CALL && params.DirtyRectsCount != 0u) {
        /* FLIP_DISCARD rejects dirty-rect presents on this stack; damage is
         * an optimization, never correctness — retry full-surface. */
        ZeroMemory(&params, sizeof(params));
        hr = IDXGISwapChain1_Present1((IDXGISwapChain1 *)sc->swapchain,
                                      sc->vsync ? 1u : 0u, present_flags, &params);
    }
    if (hr == DXGI_ERROR_DEVICE_REMOVED || hr == DXGI_ERROR_DEVICE_RESET)
        return rhi_d3d12_note_device_lost(ctx);
    if (hr == DXGI_STATUS_OCCLUDED) return RHI_RESULT_BUSY;
    if (FAILED(hr)) return RHI_RESULT_ERROR;
    sc->current_index = IDXGISwapChain3_GetCurrentBackBufferIndex((IDXGISwapChain3 *)sc->swapchain);
    return RHI_RESULT_OK;
}

/* ---- engine_rhi_d3d12 device lifecycle (plan D Tasks 3+4) ----
 * Real device/queue/fence init (Task 3) plus flip-model swapchain and the
 * frame lifecycle state machine (Task 4, spec §4.3 mapping):
 *   acquire/begin -> wait frame slot + Reset allocator/list + RTV bind +
 *                    PRESENT->RENDER_TARGET barrier
 *   submit        -> RENDER_TARGET->PRESENT barrier + Close + Execute +
 *                    Signal + frame_fence[slot]  (the present-ward barrier is
 *                    recorded here because the command list closes at submit;
 *                    rhi_present_ex only calls Present1)
 *   present       -> Present1 (vsync/damage mapping in rhi_d3d12_present)
 *   resize        -> drain -> ResizeBuffers -> rebuild RTVs
 *   destroy       -> forced drain, then swapchain before context release.
 * The dispatcher-level _ex wrappers live in rhi.c (engine) and pass
 * RHI_BACKEND_D3D12 straight through to rhi_device_create here; create
 * failures are classified via rhi_backend_note_create_result (spec §4.2). */

/* ---- device lifecycle ---- */
/* 编译期单后端入口，与 GL/VK 后端同构：委托给下面的运行时入口。原先这里
 * fail-closed 返回 NULL，理由是「caps/shader_variant 契约未落地」；该契约
 * 现已落地（device/pipeline/shader/swapchain 契约测试与 WARP 运行时测试全
 * 绿），继续留桩只会让 engine_demo 在 device 创建阶段早失败。 */
RHIDevice *rhi_device_create_compiled(void *window_native,
                                      void *surface_native,
                                      void *display_native, u32 w, u32 h) {
    /* D3D12 交换链吃 HWND（rhi.h 的 window_native），不消费 surface 句柄。 */
    (void)surface_native;
    return rhi_device_create(RHI_BACKEND_D3D12, window_native, display_native, w,
                             h);
}
RHIDevice *rhi_device_create(RHIBackend backend, void *window_native,
                             void *display_native, u32 w, u32 h) {
    RHI_D3D12Context *ctx;
    RHIDevice *dev;
    HRESULT hr;
    (void)display_native;
    if (backend != RHI_BACKEND_D3D12 || window_native == NULL ||
        !rhi_drawable_dimensions_valid(w, h)) {
        rhi_backend_note_create_result(RHI_RESULT_INVALID_ARGUMENT);
        return NULL;
    }
    ctx = (RHI_D3D12Context *)calloc(1u, sizeof(*ctx));
    if (ctx == NULL) {
        rhi_backend_note_create_result(RHI_RESULT_ERROR);
        return NULL;
    }
    hr = rhi_d3d12_context_create(ctx, RHI_D3D12_FAIL_NONE);
    if (FAILED(hr)) {
        /* No hardware adapter -> UNAVAILABLE; anything else is a genuine
         * init failure -> ERROR (spec §4.2). Never fabricate success. */
        rhi_backend_note_create_result(hr == DXGI_ERROR_NOT_FOUND ?
                                       RHI_RESULT_UNAVAILABLE : RHI_RESULT_ERROR);
        free(ctx);
        return NULL;
    }
    hr = rhi_d3d12_swapchain_create(ctx, &ctx->swapchain,
                                    (HWND)window_native, w, h);
    if (FAILED(hr)) {
        LOG_ERROR("D3D12 swapchain creation failed: 0x%08lx",
                  (unsigned long)hr);
        /* A bogus non-NULL HWND is an argument fault (E_INVALIDARG from the
         * fallback gate); everything else is a genuine init failure. */
        rhi_backend_note_create_result(hr == E_INVALIDARG ?
                                       RHI_RESULT_INVALID_ARGUMENT :
                                       RHI_RESULT_ERROR);
        rhi_d3d12_context_destroy(ctx);
        free(ctx);
        return NULL;
    }
    ctx->swapchain_ready = 1u;
    dev = (RHIDevice *)calloc(1u, sizeof(*dev));
    if (dev == NULL) {
        rhi_d3d12_context_destroy(ctx);
        free(ctx);
        rhi_backend_note_create_result(RHI_RESULT_ERROR);
        return NULL;
    }
    rhi_init_freelist(dev);
    dev->backend_data = ctx;
    dev->width = w;
    dev->height = h;
    dev->status = RHI_DEVICE_STATUS_READY;
    dev->capabilities.backend = RHI_BACKEND_D3D12;
    dev->capabilities.color_sample_counts = rhi_sample_count_bit(1u);
    dev->capabilities.depth_sample_counts = rhi_sample_count_bit(1u);
    dev->capabilities.surface_sample_count = 1u;
    dev->capabilities.color_resolve_supported = true;
    dev->capabilities.scissor_supported = true;
    dev->capabilities.present_damage_supported = true;
    dev->capabilities.present_buffer_age_supported = true;
    dev->capabilities.feature_bits = rhi_d3d12_probe_feature_bits(ctx);
    /* R606: D3D12 is the sidecar backend — rhi_shader_create_path resolves the
     * hand-authored HLSL pair via rhi_d3d12_shader_sidecar_name. shader_variant
     * is deliberately left at its GLSL default: D3D12 has no GLSL, but claiming
     * the VK variant would send the renderer looking for *_vk files that do not
     * exist, and that is what caps.shader_sidecar_paths now answers instead.
     *
     * The temporal block rides register b1 because b0 is reserved for the
     * 32BIT_CONSTANTS root parameter (the push block); see
     * rhi_d3d12_root_sig_add_bindings and the blinn_phong_hlsl.vert header. */
    dev->capabilities.shader_sidecar_paths = true;
    dev->capabilities.temporal_ubo_binding = 1u;
    /* R637: indirect draw is complete on this backend -- ExecuteIndirect with
     * a count buffer, the storage binder (UAV + read-only SRV), recorded
     * buffer fills/updates, and the compact_draws_hlsl.comp sidecar.
     * first_instance is answered below from the device's shader model:
     * the sidecars read the base through SV_StartInstanceLocation, a
     * shader-model 6.8 vertex input (R658).
     *
     * R652: compute_supported is true. It only gates GPU culling
     * (gpucull_init); cull.comp and unified_cull.comp now have HLSL
     * sidecars, rhi_cmd_bind_texture_compute binds the Hi-Z SRV, and a GPU
     * copy into a host-visible staging buffer lands in its READBACK twin.
     * R653: hiz_supported is true -- hi_z_generate.comp and
     * occlusion_cull.comp have sidecars, and the per-mip SRV / storage-image
     * binders exist, so the unified cull reads a real Hi-Z pyramid. */
    dev->capabilities.compute_supported = true;
    dev->capabilities.hiz_supported = true;
    dev->capabilities.indirect_draw_supported = true;
    {
        D3D12_FEATURE_DATA_SHADER_MODEL sm;
        ZeroMemory(&sm, sizeof(sm));
        sm.HighestShaderModel = D3D_SHADER_MODEL_6_8;
        dev->capabilities.indirect_first_instance_supported =
            SUCCEEDED(ID3D12Device_CheckFeatureSupport(
                ctx->device, D3D12_FEATURE_SHADER_MODEL, &sm, (UINT)sizeof(sm))) &&
            sm.HighestShaderModel >= D3D_SHADER_MODEL_6_8;
    }
    g_current_device = dev;
    return dev;
}
void rhi_device_destroy(RHIDevice *dev) {
    RHI_D3D12Context *ctx;
    if (dev == NULL) return;
    ctx = (RHI_D3D12Context *)dev->backend_data;
    if (ctx != NULL) {
        /* Task 3 review handoff + spec §4.3: forced drain before release —
         * freeing queues/fences/back buffers while GPU work is in flight
         * races the teardown. The drain covers queued presents too
         * (rhi_d3d12_drain_gpu), not just frame submit fences; a
         * latched-lost device skips the waits (fences may never signal
         * post-TDR). */
        (void)rhi_d3d12_drain_gpu(ctx);
        /* The material binder's shared white fallback is an ordinary RHI
         * texture, so it is released here — after the drain that guarantees
         * no command list still references its SRV — and before the context
         * itself goes away. */
        if (rhi_handle_valid(ctx->white_fallback)) {
            rhi_texture_destroy(dev, ctx->white_fallback);
            ctx->white_fallback = RHI_HANDLE_NULL;
        }
        rhi_cubemap_depth_fbo_destroy(dev, &ctx->cube_fallback);
        if (rhi_handle_valid(ctx->black_cube)) {
            rhi_cubemap_destroy(dev, ctx->black_cube);
            ctx->black_cube = RHI_HANDLE_NULL;
        }
        if (ctx->swapchain_ready) {
            rhi_d3d12_swapchain_destroy(ctx, &ctx->swapchain);
            ctx->swapchain_ready = 0u;
        }
        rhi_d3d12_context_destroy(ctx);
        free(ctx);
        dev->backend_data = NULL;
    }
    if (g_current_device == dev) g_current_device = NULL;
    free(dev);
}
void rhi_device_resize(RHIDevice *dev, u32 w, u32 h) {
    RHI_D3D12Context *ctx;
    HRESULT hr;
    RHIResult wr;
    if (!rhi_drawable_dimensions_valid(w, h) ||
        !rhi_device_control_try_acquire(dev)) return;
    ctx = (RHI_D3D12Context *)dev->backend_data;
    if (ctx == NULL || !ctx->swapchain_ready) {
        rhi_device_set_lifecycle_result(dev, RHI_RESULT_UNAVAILABLE);
        rhi_device_control_release(dev);
        return;
    }
    if (ctx->device_lost) {
        rhi_device_set_lifecycle_result(dev, RHI_RESULT_DEVICE_LOST);
        rhi_device_control_release(dev);
        return;
    }
    /* spec §4.3: drain before touching swapchain buffers; the drain must
     * also cover queued presents (rhi_d3d12_drain_gpu), not just the frame
     * submit fences. */
    wr = rhi_d3d12_drain_gpu(ctx);
    if (wr != RHI_RESULT_OK) {
        rhi_device_set_lifecycle_result(dev, wr);
        rhi_device_control_release(dev);
        return;
    }
    hr = rhi_d3d12_swapchain_resize(ctx, &ctx->swapchain, w, h);
    if (FAILED(hr)) {
        if (hr == DXGI_ERROR_DEVICE_REMOVED || hr == DXGI_ERROR_DEVICE_RESET) {
            rhi_device_set_lifecycle_result(dev, rhi_d3d12_note_device_lost(ctx));
        } else {
            /* spec §4.2: the old swapchain is still live (buffers
             * re-acquired), so report OUT_OF_DATE for this call; later frame
             * calls keep working against the un-resized swapchain. */
            rhi_device_set_lifecycle_result(dev, RHI_RESULT_OUT_OF_DATE);
        }
    } else {
        rhi_device_set_lifecycle_result(dev, RHI_RESULT_OK);
        dev->width = w;
        dev->height = h;
    }
    rhi_device_control_release(dev);
}
static void rhi_d3d12_release_frame_staging(RHI_D3D12Context *ctx, UINT slot) {
    UINT k;
    for (k = 0u; k < ctx->frame_staging_count[slot]; ++k)
        rhi_d3d12_release((IUnknown **)&ctx->frame_staging[slot][k]);
    ctx->frame_staging_count[slot] = 0u;
}
/* R645: release a D3D12 object that a command list may still reference.
 * rhi_*_destroy used to Release at once; the UI canvas grows its vertex
 * buffers mid-frame (ensure_vbo destroys and recreates them while the frame
 * that drew with the old ones is recording or in flight), so the GPU read a
 * freed resource -- debug layer [921], and the demo intermittently hung or
 * crashed. GL keeps a deleted buffer alive until its last use and Vulkan's
 * destroy waits for the frames; here the object joins the frame-staging list
 * of the slot being recorded, which is released only after that slot's
 * fence has been waited on (rhi_frame_begin). Outside a frame the previous
 * submission may still run, so the object goes to the slot submitted last
 * (released when that slot is next acquired, after its fence). */
static void rhi_d3d12_release_deferred(RHI_D3D12Context *ctx, IUnknown **obj) {
    UINT slot;
    if (obj == NULL || *obj == NULL) return;
    if (ctx == NULL || ctx->device_lost) {
        rhi_d3d12_release(obj);
        return;
    }
    slot = ctx->frame_started ? (ctx->frame_parity & 1u)
                              : ((ctx->frame_parity + 1u) & 1u);
    if (ctx->frame_staging_count[slot] == ctx->frame_staging_cap[slot]) {
        UINT cap = ctx->frame_staging_cap[slot] ? ctx->frame_staging_cap[slot] * 2u : 16u;
        ID3D12Resource **grown = (ID3D12Resource **)realloc(
            ctx->frame_staging[slot], (size_t)cap * sizeof(*grown));
        if (grown == NULL) {
            /* Out of memory for the list: wait instead of racing the GPU. */
            (void)rhi_d3d12_drain_gpu(ctx);
            rhi_d3d12_release(obj);
            return;
        }
        ctx->frame_staging[slot] = grown;
        ctx->frame_staging_cap[slot] = cap;
    }
    ctx->frame_staging[slot][ctx->frame_staging_count[slot]++] =
        (ID3D12Resource *)*obj;
    *obj = NULL;
}

RHICmdBuffer *rhi_frame_begin(RHIDevice *dev) {
    RHI_D3D12Context *ctx;
    RHI_D3D12Swapchain *sc;
    D3D12_CPU_DESCRIPTOR_HANDLE rtv;
    RHIResult wr;
    HRESULT hr;
    UINT slot;
    if (dev == NULL) return NULL;
    ctx = (RHI_D3D12Context *)dev->backend_data;
    if (ctx == NULL || !ctx->swapchain_ready) {
        rhi_device_set_lifecycle_result(dev, RHI_RESULT_UNAVAILABLE);
        return NULL;
    }
    sc = &ctx->swapchain;
    /* spec §4.3: one in-flight acquire->submit pair max. */
    if (ctx->acquire_in_flight || !rhi_frame_owner_begin_backend(dev)) {
        rhi_device_set_lifecycle_result(dev, RHI_RESULT_BUSY);
        return NULL;
    }
    g_current_device = dev;
    dev->frame_partial_active = false;
    /* R629 diagnostic: bump before anything in this frame can bind a resource,
     * so every stamp written below belongs to the frame that reads it. */
    ctx->debug_frame++;
    if (ctx->device_lost) { /* sticky latch: quiet fail-fast, no spam */
        rhi_device_set_lifecycle_result(dev, RHI_RESULT_DEVICE_LOST);
        rhi_frame_owner_release(dev);
        return NULL;
    }
    slot = ctx->frame_parity & 1u;
    wr = rhi_d3d12_wait_frame_slot(ctx, slot);
    if (wr != RHI_RESULT_OK) {
        rhi_device_set_lifecycle_result(dev, wr);
        rhi_frame_owner_release(dev);
        return NULL;
    }
    rhi_d3d12_release_frame_staging(ctx, slot);
    sc->current_index = IDXGISwapChain3_GetCurrentBackBufferIndex(
        (IDXGISwapChain3 *)sc->swapchain);
    hr = ID3D12CommandAllocator_Reset(ctx->allocators[slot]);
    if (SUCCEEDED(hr))
        hr = ID3D12GraphicsCommandList_Reset(ctx->command_lists[slot],
                                             ctx->allocators[slot], NULL);
    if (FAILED(hr)) {
        rhi_device_set_lifecycle_result(dev,
            hr == DXGI_ERROR_DEVICE_REMOVED ?
            rhi_d3d12_note_device_lost(ctx) : RHI_RESULT_ERROR);
        rhi_frame_owner_release(dev);
        return NULL;
    }
    rhi_d3d12_backbuffer_barrier(sc, ctx->command_lists[slot],
                                 D3D12_RESOURCE_STATE_PRESENT,
                                 D3D12_RESOURCE_STATE_RENDER_TARGET);
    rtv = rhi_d3d12_descriptor_cpu(&ctx->rtv_alloc,
                                   sc->rtv_slots[sc->current_index]);
    ID3D12GraphicsCommandList_OMSetRenderTargets(ctx->command_lists[slot],
                                                 1u, &rtv, FALSE, NULL);
    rhi_d3d12_set_full_target_viewport(ctx->command_lists[slot],
                                       sc->width, sc->height);
    ctx->bound_rtvs[0] = rtv;
    ctx->bound_rtv_formats[0] = sc->format;
    ctx->bound_rtv_count = 1u;
    ctx->bound_dsv_valid = 0u;
    ctx->bound_pipeline = NULL;
    ctx->bound_pipeline_compute = 0u;
    memset(ctx->live_srv, 0, sizeof(ctx->live_srv));
    ctx->frame_started = 1u;
    ctx->frame_submitted = 0u;
    ctx->acquire_in_flight = 1u;
    rhi_device_set_lifecycle_result(dev, RHI_RESULT_OK);
    return (RHICmdBuffer *)ctx;
}
static void rhi_d3d12_retire_frame_srvs(RHI_D3D12Context *ctx, UINT64 fence) {
    UINT i;
    if (ctx == NULL) return;
    for (i = 0u; i < ctx->frame_srv_count; ++i)
        rhi_d3d12_descriptor_give_back(&ctx->cbv_srv_uav_alloc,
                                       ctx->frame_srv_slots[i], fence);
    ctx->frame_srv_count = 0u;
}

void rhi_frame_end(RHIDevice *dev) {
    RHI_D3D12Context *ctx;
    HRESULT hr;
    UINT slot;
    UINT64 fence = 0u;
    if (dev == NULL) return;
    if (!rhi_frame_owner_is_current(dev) || g_current_device != dev) return;
    ctx = (RHI_D3D12Context *)dev->backend_data;
    if (ctx == NULL || !ctx->frame_started) {
        rhi_device_set_lifecycle_result(dev, RHI_RESULT_UNAVAILABLE);
        return;
    }
    slot = ctx->frame_parity & 1u;
    /* The present-ward transition is recorded here: the command list closes
     * at submit, so rhi_present has no recording surface left. */
    rhi_d3d12_backbuffer_barrier(&ctx->swapchain, ctx->command_lists[slot],
                                 D3D12_RESOURCE_STATE_RENDER_TARGET,
                                 D3D12_RESOURCE_STATE_PRESENT);
    hr = rhi_d3d12_submit(ctx, slot, &fence);
    if (FAILED(hr)) {
        rhi_device_set_lifecycle_result(dev,
            hr == DXGI_ERROR_DEVICE_REMOVED ?
            rhi_d3d12_note_device_lost(ctx) : RHI_RESULT_ERROR);
        ctx->frame_started = 0u;
        ctx->acquire_in_flight = 0u;
        rhi_d3d12_retire_frame_srvs(ctx, 0u);
        rhi_frame_owner_release(dev);
        return;
    }
    ctx->frame_fence[slot] = fence;
    rhi_d3d12_retire_frame_srvs(ctx, fence);
    ctx->frame_parity ^= 1u;
    ctx->frame_started = 0u;
    ctx->frame_submitted = 1u;
    rhi_device_set_lifecycle_result(dev, RHI_RESULT_OK);
}
void rhi_present(RHIDevice *dev) {
    RHI_D3D12Context *ctx;
    const RHIPresentRect *rects = NULL;
    UINT rect_count = 0u;
    if (dev == NULL) return;
    if (!rhi_frame_owner_is_current(dev) || g_current_device != dev) return;
    ctx = (RHI_D3D12Context *)dev->backend_data;
    if (ctx == NULL) {
        rhi_device_set_lifecycle_result(dev, RHI_RESULT_UNAVAILABLE);
        return;
    }
    if (ctx->device_lost) {
        rhi_device_set_lifecycle_result(dev, RHI_RESULT_DEVICE_LOST);
        goto out_release;
    }
    if (!ctx->frame_submitted) {
        /* spec §4.3: present only after a successful submit. Refuse, abandon
         * the in-flight frame (close the recording list so its slot can be
         * re-acquired), and release the owner — VK parity. */
        (void)ID3D12GraphicsCommandList_Close(
            ctx->command_lists[ctx->frame_parity & 1u]);
        ctx->frame_started = 0u;
        ctx->acquire_in_flight = 0u;
        rhi_device_set_lifecycle_result(dev, RHI_RESULT_ERROR);
        goto out_release;
    }
    if (dev->frame_damage_requested && dev->frame_damage_count > 0u &&
        rhi_present_damage_validate(dev->frame_damage, dev->frame_damage_count,
                                    dev->width, dev->height)) {
        rects = dev->frame_damage;
        rect_count = dev->frame_damage_count;
    }
    rhi_device_set_lifecycle_result(
        dev, rhi_d3d12_present(ctx, &ctx->swapchain, rects, rect_count));
    ctx->frame_submitted = 0u;
    ctx->acquire_in_flight = 0u;
out_release:
    dev->frame_damage_requested = false;
    dev->frame_damage_count = 0u;
    dev->frame_current_damage_count = 0u;
    dev->frame_partial_active = false;
    rhi_frame_owner_release(dev);
}
void rhi_set_vsync(RHIDevice *dev, bool enabled) {
    RHI_D3D12Context *ctx =
        dev != NULL ? (RHI_D3D12Context *)dev->backend_data : NULL;
    if (ctx != NULL && ctx->swapchain_ready)
        ctx->swapchain.vsync = enabled ? 1u : 0u;
}
u32 rhi_frame_index(RHIDevice *dev) {
    RHI_D3D12Context *ctx =
        dev != NULL ? (RHI_D3D12Context *)dev->backend_data : NULL;
    return ctx != NULL ? (ctx->frame_parity & 1u) : 0u;
}
bool rhi_device_idle(RHIDevice *dev) {
    RHI_D3D12Context *ctx =
        dev != NULL ? (RHI_D3D12Context *)dev->backend_data : NULL;
    UINT slot;
    if (ctx == NULL || ctx->device_lost) return false;
    for (slot = 0u; slot < 2u; ++slot) {
        if (rhi_d3d12_wait_frame_slot(ctx, slot) != RHI_RESULT_OK)
            return false;
    }
    return !ctx->device_lost;
}
/* Sticky latch (spec §4.2, VK parity): once observed, device loss is
 * permanent and also latches dev->status so the _ex wrappers fail fast. */
bool rhi_device_lost(RHIDevice *dev) {
    RHI_D3D12Context *ctx =
        dev != NULL ? (RHI_D3D12Context *)dev->backend_data : NULL;
    if (ctx == NULL) return true;
    if (!ctx->device_lost && ctx->device != NULL &&
        ID3D12Device_GetDeviceRemovedReason(ctx->device) != S_OK)
        (void)rhi_d3d12_note_device_lost(ctx);
    if (ctx->device_lost) dev->status = RHI_DEVICE_STATUS_LOST;
    return ctx->device_lost != 0u;
}

/* ---- backend native interop (declared in rhi_native_vulkan.h) ---- */
bool rhi_backend_get_native_device(const RHIDevice *dev, RHINativeDevice *out) {
    RHI_D3D12Context *ctx;
    if (dev == NULL || out == NULL || dev->backend_data == NULL) return false;
    ctx = (RHI_D3D12Context *)dev->backend_data;
    out->type = RHI_NATIVE_HANDLE_D3D12;
    out->instance = ctx->factory;
    out->physical_device = ctx->adapter;
    out->device = ctx->device;
    out->graphics_queue = ctx->direct_queue;
    out->graphics_queue_family = 0u;
    out->feature_bits = dev->capabilities.feature_bits;
    return true;
}
bool rhi_backend_get_device_info(const RHIDevice *dev, RHIDeviceInfo *out) {
    RHI_D3D12Context *ctx;
    DXGI_ADAPTER_DESC1 desc;
    int len;
    if (dev == NULL || out == NULL || dev->backend_data == NULL) return false;
    ctx = (RHI_D3D12Context *)dev->backend_data;
    if (FAILED(IDXGIAdapter1_GetDesc1(ctx->adapter, &desc))) return false;
    /* Fail closed when the adapter name cannot be represented in UTF-8;
     * an empty device_name would break the contract asserted by
     * test_d3d12_device_contract. */
    len = WideCharToMultiByte(CP_UTF8, 0u, desc.Description, -1,
                              out->device_name, (int)sizeof(out->device_name),
                              NULL, NULL);
    if (len <= 0) return false;
    out->vendor_id = (u32)desc.VendorId;
    out->device_id = (u32)desc.DeviceId;
    return true;
}
bool rhi_backend_texture_get_native_info(const RHIDevice *dev,
                                         RHITexture texture,
                                         RHITextureNativeInfo *out) {
    (void)dev; (void)texture; (void)out; return false;
}
bool rhi_backend_cmd_buffer_get_native_info(const RHIDevice *dev,
                                            const RHICmdBuffer *cmd,
                                            RHICmdBufferNativeInfo *out) {
    (void)dev; (void)cmd; (void)out; return false;
}
/* ---- Task 7: DXR acceleration structures (fail-closed below tier 1.0) ----
 * AS storage is a committed buffer that never leaves
 * D3D12_RESOURCE_STATE_RAYTRACING_ACCELERATION_STRUCTURE, on a heap flagged
 * ALLOW_ONLY_RT_ACCELERATION_STRUCTURE_BUFFERS. Every DXR entry gates on
 * RHI_FEATURE_ACCELERATION_STRUCTURE (probed at device create from
 * D3D12_OPTIONS5.RaytracingTier) plus the ID3D12Device5 /
 * ID3D12GraphicsCommandList4 interfaces; anything missing fails closed
 * (invalid handle / false / 0). One-shot builds record into the upload
 * list and fence-wait, matching the rhi.h:394-397 contract. */
typedef struct RHI_D3D12AccelerationStructure {
    RHI_D3D12Resource storage; /* state stays RAYTRACING_ACCELERATION_STRUCTURE */
    UINT64 size;
    UINT type;                 /* RHIAccelerationStructureType */
} RHI_D3D12AccelerationStructure;

/* spec §4.4: the public TLAS instance record (rhi_tlas_instance_encode,
 * VK acceleration-structure instance ABI) is bit-identical to
 * D3D12_RAYTRACING_INSTANCE_DESC — row-major 3x4 transform at byte 0,
 * packed custom-index/mask at 48, packed SBT-offset/flags at 52, BLAS
 * device address at 56, 64 bytes total — and the flag values line up 1:1
 * (cull-disable/CCW/opaque/non-opaque = 1/2/4/8 in both APIs). The backend
 * therefore consumes the encoded record directly; these asserts pin the
 * layout contract so an SDK or ABI drift fails at compile time instead of
 * silently mistranslating instances. */
_Static_assert(sizeof(D3D12_RAYTRACING_INSTANCE_DESC) == RHI_TLAS_INSTANCE_SIZE,
               "TLAS instance record must stay 64 bytes (VK ABI)");
_Static_assert(offsetof(D3D12_RAYTRACING_INSTANCE_DESC, Transform) == 0u,
               "TLAS record transform offset");
_Static_assert(offsetof(D3D12_RAYTRACING_INSTANCE_DESC, AccelerationStructure) == 56u,
               "TLAS record BLAS address offset");
_Static_assert(D3D12_RAYTRACING_INSTANCE_FLAG_TRIANGLE_CULL_DISABLE == 0x1u &&
               D3D12_RAYTRACING_INSTANCE_FLAG_TRIANGLE_FRONT_COUNTERCLOCKWISE == 0x2u &&
               D3D12_RAYTRACING_INSTANCE_FLAG_FORCE_OPAQUE == 0x4u &&
               D3D12_RAYTRACING_INSTANCE_FLAG_FORCE_NON_OPAQUE == 0x8u,
               "TLAS record flag values must match the VK ABI");

static ID3D12GraphicsCommandList *rhi_d3d12_cmd_list(RHI_D3D12Context *ctx);

static UINT rhi_d3d12_dxr_supported(const RHIDevice *dev) {
    const RHI_D3D12Context *ctx;
    if (dev == NULL) return 0u;
    ctx = (const RHI_D3D12Context *)dev->backend_data;
    return ctx != NULL && !ctx->device_lost &&
           (dev->capabilities.feature_bits &
            RHI_FEATURE_ACCELERATION_STRUCTURE) != 0u;
}

static ID3D12Device5 *rhi_d3d12_device5(RHI_D3D12Context *ctx) {
    ID3D12Device5 *device5 = NULL;
    if (ctx == NULL || ctx->device == NULL) return NULL;
    if (FAILED(ID3D12Device_QueryInterface(ctx->device, &IID_ID3D12Device5,
                                           (void **)&device5)))
        return NULL;
    return device5;
}

static ID3D12GraphicsCommandList4 *rhi_d3d12_cmdlist4(
    ID3D12GraphicsCommandList *list) {
    ID3D12GraphicsCommandList4 *list4 = NULL;
    if (list == NULL) return NULL;
    if (FAILED(ID3D12GraphicsCommandList_QueryInterface(
            list, &IID_ID3D12GraphicsCommandList4, (void **)&list4)))
        return NULL;
    return list4;
}

/* AS storage: committed buffer, permanently in
 * D3D12_RESOURCE_STATE_RAYTRACING_ACCELERATION_STRUCTURE. Heap flags
 * stay NONE: heap-tier flags (the ALLOW_ONLY/DENY family) are illegal for
 * CreateCommittedResource (the runtime sets them automatically;
 * E_INVALIDARG otherwise), and the AS-only alias
 * D3D12_HEAP_FLAG_ALLOW_ONLY_RT_ACCELERATION_STRUCTURE_BUFFERS
 * postdates the pinned Agility 1.616 headers (Task 1 lock). */
static HRESULT rhi_d3d12_as_create_storage(RHI_D3D12Context *ctx, UINT64 size,
                                           RHI_D3D12Resource *out) {
    D3D12_HEAP_PROPERTIES heap;
    D3D12_RESOURCE_DESC desc;
    HRESULT hr;
    ZeroMemory(&heap, sizeof(heap));
    heap.Type = D3D12_HEAP_TYPE_DEFAULT;
    ZeroMemory(&desc, sizeof(desc));
    desc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
    desc.Width = size;
    desc.Height = 1u;
    desc.DepthOrArraySize = 1u;
    desc.MipLevels = 1u;
    desc.SampleDesc.Count = 1u;
    desc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;
    desc.Flags = D3D12_RESOURCE_FLAG_ALLOW_UNORDERED_ACCESS;
    hr = ID3D12Device_CreateCommittedResource(
        ctx->device, &heap, D3D12_HEAP_FLAG_NONE,
        &desc, D3D12_RESOURCE_STATE_RAYTRACING_ACCELERATION_STRUCTURE, NULL,
        &IID_ID3D12Resource, (void **)&out->resource);
    if (SUCCEEDED(hr)) out->state = D3D12_RESOURCE_STATE_RAYTRACING_ACCELERATION_STRUCTURE;
    return hr;
}

static D3D12_GPU_VIRTUAL_ADDRESS rhi_d3d12_buffer_gpuva(RHIDevice *dev,
        RHIBuffer buffer, UINT64 *out_size) {
    RHI_D3D12Buffer *bd;
    if (dev == NULL) return 0u;
    bd = (RHI_D3D12Buffer *)rhi_get_resource_typed(dev, buffer,
                                                   RHI_RES_BUFFER);
    if (bd == NULL || bd->resource == NULL) return 0u;
    if (out_size != NULL) *out_size = bd->size;
    return ID3D12Resource_GetGPUVirtualAddress(bd->resource);
}

/* One-triangle BLAS inputs. R32G32B32_FLOAT maps
 * RHI_VERTEX_FORMAT_R32G32B32_SFLOAT; the desc carries no index format, so
 * R32_UINT follows the VK implementation (rhi_vk.c VK_INDEX_TYPE_UINT32).
 * Addresses are unused by the prebuild query (deferred sizing passes 0). */
static void rhi_d3d12_blas_inputs(const RHIBLASOneTriangleDesc *desc,
        D3D12_GPU_VIRTUAL_ADDRESS vertex_address,
        D3D12_GPU_VIRTUAL_ADDRESS index_address,
        D3D12_RAYTRACING_GEOMETRY_DESC *out_geometry,
        D3D12_BUILD_RAYTRACING_ACCELERATION_STRUCTURE_INPUTS *out_inputs) {
    ZeroMemory(out_geometry, sizeof(*out_geometry));
    out_geometry->Type = D3D12_RAYTRACING_GEOMETRY_TYPE_TRIANGLES;
    out_geometry->Flags = D3D12_RAYTRACING_GEOMETRY_FLAG_OPAQUE;
    out_geometry->Triangles.VertexFormat = DXGI_FORMAT_R32G32B32_FLOAT;
    out_geometry->Triangles.VertexCount = desc->vertex_count;
    out_geometry->Triangles.VertexBuffer.StartAddress =
        vertex_address + (UINT64)desc->vertex_offset;
    out_geometry->Triangles.VertexBuffer.StrideInBytes = desc->vertex_stride;
    out_geometry->Triangles.IndexFormat = DXGI_FORMAT_R32_UINT;
    out_geometry->Triangles.IndexCount = desc->index_count;
    out_geometry->Triangles.IndexBuffer =
        index_address + (UINT64)desc->index_offset;
    ZeroMemory(out_inputs, sizeof(*out_inputs));
    out_inputs->Type = D3D12_RAYTRACING_ACCELERATION_STRUCTURE_TYPE_BOTTOM_LEVEL;
    out_inputs->Flags = D3D12_RAYTRACING_ACCELERATION_STRUCTURE_BUILD_FLAG_NONE;
    out_inputs->NumDescs = 1u;
    out_inputs->DescsLayout = D3D12_ELEMENTS_LAYOUT_ARRAY;
    out_inputs->pGeometryDescs = out_geometry;
}

static void rhi_d3d12_tlas_inputs(D3D12_GPU_VIRTUAL_ADDRESS instance_address,
        D3D12_BUILD_RAYTRACING_ACCELERATION_STRUCTURE_INPUTS *out_inputs) {
    ZeroMemory(out_inputs, sizeof(*out_inputs));
    out_inputs->Type = D3D12_RAYTRACING_ACCELERATION_STRUCTURE_TYPE_TOP_LEVEL;
    out_inputs->Flags = D3D12_RAYTRACING_ACCELERATION_STRUCTURE_BUILD_FLAG_NONE;
    out_inputs->NumDescs = 1u;
    out_inputs->DescsLayout = D3D12_ELEMENTS_LAYOUT_ARRAY;
    out_inputs->InstanceDescs = instance_address;
}

static bool rhi_d3d12_as_prebuild(ID3D12Device5 *device5,
        const D3D12_BUILD_RAYTRACING_ACCELERATION_STRUCTURE_INPUTS *inputs,
        RHIAccelerationStructureBuildSizes *out_sizes) {
    D3D12_RAYTRACING_ACCELERATION_STRUCTURE_PREBUILD_INFO info;
    if (device5 == NULL || inputs == NULL || out_sizes == NULL) return false;
    ZeroMemory(&info, sizeof(info));
    ID3D12Device5_GetRaytracingAccelerationStructurePrebuildInfo(
        device5, inputs, &info);
    out_sizes->acceleration_structure_size =
        (usize)info.ResultDataMaxSizeInBytes;
    out_sizes->build_scratch_size = (usize)info.ScratchDataSizeInBytes;
    return info.ResultDataMaxSizeInBytes != 0u &&
           info.ScratchDataSizeInBytes != 0u;
}

/* Record BuildRaytracingAccelerationStructure plus the UAV barrier that
 * orders the build (a UAV write) against later reads. */
static void rhi_d3d12_as_build_record(ID3D12GraphicsCommandList4 *list4,
        const D3D12_BUILD_RAYTRACING_ACCELERATION_STRUCTURE_INPUTS *inputs,
        D3D12_GPU_VIRTUAL_ADDRESS dest, D3D12_GPU_VIRTUAL_ADDRESS scratch,
        ID3D12Resource *dest_resource) {
    D3D12_BUILD_RAYTRACING_ACCELERATION_STRUCTURE_DESC build;
    D3D12_RESOURCE_BARRIER barrier;
    ZeroMemory(&build, sizeof(build));
    build.DestAccelerationStructureData = dest;
    build.Inputs = *inputs;
    build.ScratchAccelerationStructureData = scratch;
    ID3D12GraphicsCommandList4_BuildRaytracingAccelerationStructure(
        list4, &build, 0u, NULL);
    ZeroMemory(&barrier, sizeof(barrier));
    barrier.Type = D3D12_RESOURCE_BARRIER_TYPE_UAV;
    barrier.UAV.pResource = dest_resource;
    ID3D12GraphicsCommandList4_ResourceBarrier(list4, 1u, &barrier);
}

/* cmd == NULL selects the one-shot contract (rhi.h:394-397): record into
 * the upload list, submit on the direct queue, fence-wait; on return the
 * AS is usable and the inputs are safe to destroy. A live frame cmd
 * records into the current frame list instead. */
static bool rhi_d3d12_as_build_submit(RHI_D3D12Context *ctx,
        RHICmdBuffer *cmd,
        const D3D12_BUILD_RAYTRACING_ACCELERATION_STRUCTURE_INPUTS *inputs,
        D3D12_GPU_VIRTUAL_ADDRESS dest, D3D12_GPU_VIRTUAL_ADDRESS scratch,
        ID3D12Resource *dest_resource) {
    ID3D12GraphicsCommandList4 *list4;
    if (cmd == NULL) {
        if (FAILED(rhi_d3d12_oneshot_begin(ctx))) return false;
        list4 = rhi_d3d12_cmdlist4(ctx->upload_list);
        if (list4 == NULL) return false;
        rhi_d3d12_as_build_record(list4, inputs, dest, scratch, dest_resource);
        ID3D12GraphicsCommandList4_Release(list4);
        return rhi_d3d12_oneshot_flush(ctx) == RHI_RESULT_OK;
    }
    list4 = rhi_d3d12_cmdlist4(rhi_d3d12_cmd_list((RHI_D3D12Context *)cmd));
    if (list4 == NULL) return false;
    rhi_d3d12_as_build_record(list4, inputs, dest, scratch, dest_resource);
    ID3D12GraphicsCommandList4_Release(list4);
    return true;
}

bool rhi_backend_cmd_build_blas_one_triangle(
    RHICmdBuffer *cmd, RHIDevice *dev, RHIAccelerationStructure blas,
    const RHIBLASOneTriangleDesc *desc,
    RHIBuffer scratch_buffer, usize scratch_offset) {
    RHI_D3D12Context *ctx;
    RHI_D3D12AccelerationStructure *ad;
    ID3D12Device5 *device5;
    D3D12_RAYTRACING_GEOMETRY_DESC geometry;
    D3D12_BUILD_RAYTRACING_ACCELERATION_STRUCTURE_INPUTS inputs;
    RHIAccelerationStructureBuildSizes sizes;
    D3D12_GPU_VIRTUAL_ADDRESS vertex_address, index_address, scratch_address;
    UINT64 scratch_size = 0u;
    bool fits;
    if (dev == NULL || desc == NULL ||
        !rhi_blas_one_triangle_desc_validate(desc)) return false;
    if (!rhi_d3d12_dxr_supported(dev)) return false;
    ctx = (RHI_D3D12Context *)dev->backend_data;
    ad = (RHI_D3D12AccelerationStructure *)rhi_get_resource_typed(
        dev, blas, RHI_RES_ACCELERATION_STRUCTURE);
    if (ad == NULL || ad->type != RHI_ACCELERATION_STRUCTURE_BOTTOM_LEVEL)
        return false;
    vertex_address = rhi_d3d12_buffer_gpuva(dev, desc->vertex_buffer, NULL);
    index_address = rhi_d3d12_buffer_gpuva(dev, desc->index_buffer, NULL);
    scratch_address = rhi_d3d12_buffer_gpuva(dev, scratch_buffer, &scratch_size);
    if (vertex_address == 0u || index_address == 0u ||
        scratch_address == 0u || scratch_offset >= (usize)scratch_size ||
        (scratch_offset % D3D12_RAYTRACING_ACCELERATION_STRUCTURE_BYTE_ALIGNMENT) != 0u)
        return false;
    device5 = rhi_d3d12_device5(ctx);
    if (device5 == NULL) return false;
    rhi_d3d12_blas_inputs(desc, vertex_address, index_address,
                          &geometry, &inputs);
    fits = rhi_d3d12_as_prebuild(device5, &inputs, &sizes) &&
           sizes.acceleration_structure_size <= (usize)ad->size &&
           sizes.build_scratch_size <= (usize)scratch_size - scratch_offset;
    ID3D12Device5_Release(device5);
    if (!fits) return false;
    return rhi_d3d12_as_build_submit(ctx, cmd, &inputs,
        ID3D12Resource_GetGPUVirtualAddress(ad->storage.resource),
        scratch_address + (UINT64)scratch_offset, ad->storage.resource);
}

u64 rhi_backend_acceleration_structure_get_device_address(
    RHIDevice *dev, RHIAccelerationStructure structure) {
    RHI_D3D12AccelerationStructure *ad;
    if (!rhi_d3d12_dxr_supported(dev)) return 0u;
    ad = (RHI_D3D12AccelerationStructure *)rhi_get_resource_typed(
        dev, structure, RHI_RES_ACCELERATION_STRUCTURE);
    if (ad == NULL || ad->storage.resource == NULL) return 0u;
    return (u64)ID3D12Resource_GetGPUVirtualAddress(ad->storage.resource);
}

bool rhi_backend_tlas_one_instance_get_build_sizes(
    RHIDevice *dev, RHIBuffer instance_buffer,
    RHIAccelerationStructureBuildSizes *out_sizes) {
    RHI_D3D12Context *ctx;
    ID3D12Device5 *device5;
    D3D12_BUILD_RAYTRACING_ACCELERATION_STRUCTURE_INPUTS inputs;
    D3D12_GPU_VIRTUAL_ADDRESS instance_address;
    UINT64 instance_size = 0u;
    bool ok;
    if (out_sizes != NULL) memset(out_sizes, 0, sizeof(*out_sizes));
    if (dev == NULL || out_sizes == NULL) return false;
    if (!rhi_d3d12_dxr_supported(dev)) return false;
    ctx = (RHI_D3D12Context *)dev->backend_data;
    instance_address = rhi_d3d12_buffer_gpuva(dev, instance_buffer,
                                              &instance_size);
    if (instance_address == 0u || instance_size < RHI_TLAS_INSTANCE_SIZE ||
        (instance_address % D3D12_RAYTRACING_INSTANCE_DESCS_BYTE_ALIGNMENT) != 0u)
        return false;
    device5 = rhi_d3d12_device5(ctx);
    if (device5 == NULL) return false;
    rhi_d3d12_tlas_inputs(instance_address, &inputs);
    ok = rhi_d3d12_as_prebuild(device5, &inputs, out_sizes);
    ID3D12Device5_Release(device5);
    return ok;
}

bool rhi_backend_cmd_build_tlas_one_instance(
    RHICmdBuffer *cmd, RHIDevice *dev, RHIAccelerationStructure tlas,
    RHIBuffer instance_buffer, RHIBuffer scratch_buffer, usize scratch_offset) {
    RHI_D3D12Context *ctx;
    RHI_D3D12AccelerationStructure *ad;
    ID3D12Device5 *device5;
    D3D12_BUILD_RAYTRACING_ACCELERATION_STRUCTURE_INPUTS inputs;
    RHIAccelerationStructureBuildSizes sizes;
    D3D12_GPU_VIRTUAL_ADDRESS instance_address, scratch_address;
    UINT64 instance_size = 0u, scratch_size = 0u;
    bool fits;
    if (dev == NULL) return false;
    if (!rhi_d3d12_dxr_supported(dev)) return false;
    ctx = (RHI_D3D12Context *)dev->backend_data;
    ad = (RHI_D3D12AccelerationStructure *)rhi_get_resource_typed(
        dev, tlas, RHI_RES_ACCELERATION_STRUCTURE);
    if (ad == NULL || ad->type != RHI_ACCELERATION_STRUCTURE_TOP_LEVEL)
        return false;
    instance_address = rhi_d3d12_buffer_gpuva(dev, instance_buffer,
                                              &instance_size);
    scratch_address = rhi_d3d12_buffer_gpuva(dev, scratch_buffer, &scratch_size);
    if (instance_address == 0u || scratch_address == 0u ||
        instance_size < RHI_TLAS_INSTANCE_SIZE ||
        scratch_offset >= (usize)scratch_size ||
        (instance_address % D3D12_RAYTRACING_INSTANCE_DESCS_BYTE_ALIGNMENT) != 0u ||
        (scratch_offset % D3D12_RAYTRACING_ACCELERATION_STRUCTURE_BYTE_ALIGNMENT) != 0u)
        return false;
    device5 = rhi_d3d12_device5(ctx);
    if (device5 == NULL) return false;
    rhi_d3d12_tlas_inputs(instance_address, &inputs);
    fits = rhi_d3d12_as_prebuild(device5, &inputs, &sizes) &&
           sizes.acceleration_structure_size <= (usize)ad->size &&
           sizes.build_scratch_size <= (usize)scratch_size - scratch_offset;
    ID3D12Device5_Release(device5);
    if (!fits) return false;
    return rhi_d3d12_as_build_submit(ctx, cmd, &inputs,
        ID3D12Resource_GetGPUVirtualAddress(ad->storage.resource),
        scratch_address + (UINT64)scratch_offset, ad->storage.resource);
}

bool rhi_backend_acceleration_structure_get_vk_handle(
    RHIDevice *dev, RHIAccelerationStructure structure, void **out_handle) {
    /* The VK escape hatch is fail-closed on the D3D12 backend. */
    (void)dev; (void)structure; (void)out_handle; return false;
}
bool rhi_blas_one_triangle_get_build_sizes(
    RHIDevice *dev, const RHIBLASOneTriangleDesc *desc,
    RHIAccelerationStructureBuildSizes *out_sizes) {
    RHI_D3D12Context *ctx;
    ID3D12Device5 *device5;
    D3D12_RAYTRACING_GEOMETRY_DESC geometry;
    D3D12_BUILD_RAYTRACING_ACCELERATION_STRUCTURE_INPUTS inputs;
    D3D12_GPU_VIRTUAL_ADDRESS vertex_address, index_address;
    bool ok;
    if (out_sizes != NULL) memset(out_sizes, 0, sizeof(*out_sizes));
    if (dev == NULL || desc == NULL || out_sizes == NULL ||
        !rhi_blas_one_triangle_desc_validate(desc)) return false;
    if (!rhi_d3d12_dxr_supported(dev)) return false;
    ctx = (RHI_D3D12Context *)dev->backend_data;
    vertex_address = rhi_d3d12_buffer_gpuva(dev, desc->vertex_buffer, NULL);
    index_address = rhi_d3d12_buffer_gpuva(dev, desc->index_buffer, NULL);
    if (vertex_address == 0u || index_address == 0u) return false;
    device5 = rhi_d3d12_device5(ctx);
    if (device5 == NULL) return false;
    rhi_d3d12_blas_inputs(desc, vertex_address, index_address,
                          &geometry, &inputs);
    ok = rhi_d3d12_as_prebuild(device5, &inputs, out_sizes);
    ID3D12Device5_Release(device5);
    return ok;
}
RHIAccelerationStructure rhi_backend_acceleration_structure_create(
    RHIDevice *dev, const RHIAccelerationStructureDesc *desc) {
    RHI_D3D12Context *ctx;
    RHI_D3D12AccelerationStructure *ad;
    UINT64 size;
    u32 idx;
    if (desc == NULL ||
        (desc->type != RHI_ACCELERATION_STRUCTURE_BOTTOM_LEVEL &&
         desc->type != RHI_ACCELERATION_STRUCTURE_TOP_LEVEL))
        return RHI_HANDLE_NULL;
    if (!rhi_d3d12_dxr_supported(dev)) return RHI_HANDLE_NULL;
    ctx = (RHI_D3D12Context *)dev->backend_data;
    size = (UINT64)desc->storage_size;
    if (size == 0u) {
        /* Deferred sizing (rhi.c front door passes 0 through): take the
         * prebuild query's result size for the smallest buildable shape —
         * one-triangle BLAS / one-instance TLAS. */
        ID3D12Device5 *device5 = rhi_d3d12_device5(ctx);
        D3D12_BUILD_RAYTRACING_ACCELERATION_STRUCTURE_INPUTS inputs;
        RHIAccelerationStructureBuildSizes sizes;
        if (device5 == NULL) return RHI_HANDLE_NULL;
        if (desc->type == RHI_ACCELERATION_STRUCTURE_BOTTOM_LEVEL) {
            D3D12_RAYTRACING_GEOMETRY_DESC geometry;
            RHIBLASOneTriangleDesc one;
            ZeroMemory(&one, sizeof(one));
            one.vertex_count = 3u;
            one.vertex_stride = 12u;
            one.vertex_format = RHI_VERTEX_FORMAT_R32G32B32_SFLOAT;
            one.index_count = 3u;
            one.indexed = true;
            rhi_d3d12_blas_inputs(&one, 0u, 0u, &geometry, &inputs);
        } else {
            rhi_d3d12_tlas_inputs(0u, &inputs);
        }
        if (!rhi_d3d12_as_prebuild(device5, &inputs, &sizes)) {
            ID3D12Device5_Release(device5);
            return RHI_HANDLE_NULL;
        }
        ID3D12Device5_Release(device5);
        size = (UINT64)sizes.acceleration_structure_size;
    } else if (!rhi_acceleration_structure_desc_validate(desc)) {
        return RHI_HANDLE_NULL;
    }
    ad = (RHI_D3D12AccelerationStructure *)calloc(1u, sizeof(*ad));
    if (ad == NULL) return RHI_HANDLE_NULL;
    if (FAILED(rhi_d3d12_as_create_storage(ctx, size, &ad->storage))) {
        free(ad);
        return RHI_HANDLE_NULL;
    }
    ad->size = size;
    ad->type = (UINT)desc->type;
    idx = rhi_alloc_slot(dev);
    dev->slots[idx].ptr = ad;
    dev->slots[idx].type = RHI_RES_ACCELERATION_STRUCTURE;
    return rhi_make_handle(idx, dev->slots[idx].generation);
}
void rhi_backend_acceleration_structure_destroy(
    RHIDevice *dev, RHIAccelerationStructure structure) {
    RHI_D3D12AccelerationStructure *ad;
    if (dev == NULL) return;
    ad = (RHI_D3D12AccelerationStructure *)rhi_get_resource_typed(
        dev, structure, RHI_RES_ACCELERATION_STRUCTURE);
    if (ad == NULL) return;
    rhi_d3d12_release((IUnknown **)&ad->storage.resource);
    free(ad);
    rhi_free_slot(dev, structure);
}

u32 rhi_vk_validation_message_count(void) { return 0u; }
void rhi_vk_validation_message_count_reset(void) {}
bool rhi_vk_validation_gate_active(void) { return false; }
void rhi_vk_validation_set_enabled(bool enabled) { (void)enabled; }

/* ---- resource creation (Task 5) ----
 * Committed resources only (decision record: the RHI slot model is small —
 * 4096 slots — and there is no custom heap-reuse requirement; committed
 * resources let the driver place them and keep OS residency accounting
 * accurate. Placed resources wait for a real memory-pressure receipt.)
 * Buffer heap selection mirrors the VK policy: STORAGE/AS scratch and
 * initial-data mesh/storage buffers go DEVICE_LOCAL (DEFAULT heap +
 * staging upload); everything else is an UPLOAD-heap persistently
 * mappable buffer. */
static UINT rhi_d3d12_buffer_wants_device_local(const RHIBufferDesc *desc) {
    UINT mesh_only = (desc->usage & (RHI_BUFFER_USAGE_VERTEX | RHI_BUFFER_USAGE_INDEX)) != 0u &&
        (desc->usage & ~(RHI_BUFFER_USAGE_VERTEX | RHI_BUFFER_USAGE_INDEX)) == 0u;
    UINT gpu_storage = (desc->usage & RHI_BUFFER_USAGE_STORAGE) != 0u &&
        (desc->usage & (RHI_BUFFER_USAGE_UNIFORM | RHI_BUFFER_USAGE_VERTEX |
                        RHI_BUFFER_USAGE_INDEX)) == 0u;
    UINT as_input = (desc->usage & RHI_BUFFER_USAGE_AS_BUILD_INPUT) != 0u;
    UINT as_scratch = (desc->usage & RHI_BUFFER_USAGE_DEVICE_ADDRESS) != 0u &&
        (desc->usage & RHI_BUFFER_USAGE_STORAGE) != 0u &&
        (desc->usage & (RHI_BUFFER_USAGE_VERTEX | RHI_BUFFER_USAGE_INDEX |
                        RHI_BUFFER_USAGE_UNIFORM)) == 0u;
    return ((desc->initial_data != NULL) && (mesh_only || gpu_storage || as_input)) ||
           as_scratch;
}

static HRESULT rhi_d3d12_buffer_alloc(RHI_D3D12Context *ctx, UINT64 size,
                                      UINT device_local, UINT allow_uav,
                                      D3D12_RESOURCE_STATES initial_state,
                                      ID3D12Resource **out) {
    D3D12_HEAP_PROPERTIES properties;
    D3D12_RESOURCE_DESC description;
    HRESULT hr;
    ZeroMemory(&properties, sizeof(properties));
    properties.Type = device_local ? D3D12_HEAP_TYPE_DEFAULT : D3D12_HEAP_TYPE_UPLOAD;
    properties.CreationNodeMask = 1u;
    properties.VisibleNodeMask = 1u;
    ZeroMemory(&description, sizeof(description));
    description.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
    description.Width = size;
    description.Height = 1u;
    description.DepthOrArraySize = 1u;
    description.MipLevels = 1u;
    description.SampleDesc.Count = 1u;
    description.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;
    if (allow_uav) description.Flags |= D3D12_RESOURCE_FLAG_ALLOW_UNORDERED_ACCESS;
    hr = ID3D12Device_CreateCommittedResource(
        ctx->device, &properties, D3D12_HEAP_FLAG_NONE, &description,
        initial_state, NULL, &IID_ID3D12Resource, (void **)out);
    if (hr == DXGI_ERROR_DEVICE_REMOVED) (void)rhi_d3d12_note_device_lost(ctx);
    return hr;
}

/* One-shot staging upload into a DEFAULT-heap buffer range. */
static RHIResult rhi_d3d12_buffer_stage_upload(RHI_D3D12Context *ctx,
                                               RHI_D3D12Buffer *bd,
                                               UINT64 offset,
                                               const void *data, UINT64 size) {
    ID3D12Resource *staging;
    void *mapped = NULL;
    RHIResult rr;
    staging = rhi_d3d12_staging_buffer(ctx, D3D12_HEAP_TYPE_UPLOAD, size);
    if (staging == NULL) return RHI_RESULT_ERROR;
    if (FAILED(ID3D12Resource_Map(staging, 0u, NULL, &mapped))) {
        ID3D12Resource_Release(staging);
        return RHI_RESULT_ERROR;
    }
    memcpy(mapped, data, (size_t)size);
    ID3D12Resource_Unmap(staging, 0u, NULL);
    if (FAILED(rhi_d3d12_oneshot_begin(ctx))) {
        ID3D12Resource_Release(staging);
        return RHI_RESULT_ERROR;
    }
    rhi_d3d12_transition(ctx->upload_list, bd->resource, bd->state,
                         D3D12_RESOURCE_STATE_COPY_DEST);
    ID3D12GraphicsCommandList_CopyBufferRegion(ctx->upload_list, bd->resource,
                                               offset, staging, 0u, size);
    rhi_d3d12_transition(ctx->upload_list, bd->resource,
                         D3D12_RESOURCE_STATE_COPY_DEST, bd->state);
    rr = rhi_d3d12_oneshot_flush(ctx);
    ID3D12Resource_Release(staging);
    return rr;
}

RHIBuffer rhi_buffer_create(RHIDevice *dev, const RHIBufferDesc *desc) {
    RHI_D3D12Context *ctx;
    RHI_D3D12Buffer *bd;
    UINT64 alloc_size;
    u32 idx;
    UINT device_local;
    UINT allow_uav;
    D3D12_RESOURCE_STATES initial_state;
    if (dev == NULL || !rhi_buffer_desc_validate(desc)) return RHI_HANDLE_NULL;
    ctx = (RHI_D3D12Context *)dev->backend_data;
    if (ctx == NULL || ctx->device_lost) return RHI_HANDLE_NULL;
    device_local = rhi_d3d12_buffer_wants_device_local(desc);
    /* R636: ALLOW_UNORDERED_ACCESS is only legal on a DEFAULT-heap
     * resource. A STORAGE buffer without initial data lands on the UPLOAD
     * heap, and CreateCommittedResource refuses the flag there -- so the
     * buffer came back as an invalid handle and EVERY binding of it was
     * silently unbound. The skinned vertex shader then read a descriptor
     * that was never set and the GPU hung (DXGI_ERROR_DEVICE_HUNG). The
     * flag is dropped rather than failing the creation, and
     * rhi_cmd_bind_storage_buffer refuses to bind such a buffer as a UAV. */
    allow_uav = (desc->usage & RHI_BUFFER_USAGE_STORAGE) != 0u && device_local != 0u;
    if (!device_local) {
        /* UPLOAD heaps are persistently GENERIC_READ. */
        initial_state = D3D12_RESOURCE_STATE_GENERIC_READ;
    } else if (desc->initial_data != NULL) {
        /* R643: buffers are always created in COMMON whatever InitialState
         * says (debug layer [1328]); the upload copy promotes it. */
        initial_state = D3D12_RESOURCE_STATE_COMMON;
    } else {
        initial_state = allow_uav ? D3D12_RESOURCE_STATE_UNORDERED_ACCESS
                                  : D3D12_RESOURCE_STATE_COMMON;
    }
    bd = (RHI_D3D12Buffer *)calloc(1u, sizeof(*bd));
    if (bd == NULL) return RHI_HANDLE_NULL;
    /* R643: rhi_cmd_bind_uniform_buffer declares a CBV over the 256-rounded
     * size (D3D12 requires SizeInBytes % 256 == 0), so a buffer whose size is
     * not a multiple of 256 had a view running past the end of its
     * own resource -- debug layer [649], undefined reads of the tail. Any buffer
     * can be bound that way (usage flags are not checked there), so every
     * resource is allocated at the rounded size; bd->size stays the caller's
     * size, so every copy and readback still covers exactly the caller's
     * bytes. */
    alloc_size = ((UINT64)desc->size + 255u) & ~(UINT64)255u;
    if (FAILED(rhi_d3d12_buffer_alloc(ctx, alloc_size, device_local,
                                      allow_uav, initial_state,
                                      &bd->resource))) {
        free(bd);
        return RHI_HANDLE_NULL;
    }
    bd->size = (UINT64)desc->size;
    bd->usage = (UINT)desc->usage;
    bd->device_local = device_local;
    bd->allow_uav = allow_uav;
    if (device_local && desc->initial_data != NULL) {
        D3D12_RESOURCE_STATES final_state =
            allow_uav ? D3D12_RESOURCE_STATE_UNORDERED_ACCESS
                      : D3D12_RESOURCE_STATE_COMMON;
        /* Create-time upload: COPY_DEST -> final, in one submit. */
        ID3D12Resource *staging =
            rhi_d3d12_staging_buffer(ctx, D3D12_HEAP_TYPE_UPLOAD, bd->size);
        void *mapped = NULL;
        RHIResult rr = RHI_RESULT_ERROR;
        if (staging != NULL &&
            SUCCEEDED(ID3D12Resource_Map(staging, 0u, NULL, &mapped))) {
            memcpy(mapped, desc->initial_data, (size_t)bd->size);
            ID3D12Resource_Unmap(staging, 0u, NULL);
            if (SUCCEEDED(rhi_d3d12_oneshot_begin(ctx))) {
                ID3D12GraphicsCommandList_CopyBufferRegion(ctx->upload_list,
                    bd->resource, 0u, staging, 0u, bd->size);
                /* The copy implicitly promoted COMMON to COPY_DEST, so the
                 * barrier starts there. */
                rhi_d3d12_transition(ctx->upload_list, bd->resource,
                                     D3D12_RESOURCE_STATE_COPY_DEST,
                                     final_state);
                rr = rhi_d3d12_oneshot_flush(ctx);
            }
        }
        if (staging != NULL) ID3D12Resource_Release(staging);
        if (rr != RHI_RESULT_OK) {
            ID3D12Resource_Release(bd->resource);
            free(bd);
            return RHI_HANDLE_NULL;
        }
        bd->state = final_state;
    } else if (!device_local && desc->initial_data != NULL) {
        void *mapped = NULL;
        if (FAILED(ID3D12Resource_Map(bd->resource, 0u, NULL, &mapped))) {
            ID3D12Resource_Release(bd->resource);
            free(bd);
            return RHI_HANDLE_NULL;
        }
        memcpy(mapped, desc->initial_data, (size_t)bd->size);
        ID3D12Resource_Unmap(bd->resource, 0u, NULL);
        bd->state = D3D12_RESOURCE_STATE_GENERIC_READ;
    } else {
        bd->state = initial_state;
    }
    idx = rhi_alloc_slot(dev);
    dev->slots[idx].ptr = bd;
    dev->slots[idx].type = RHI_RES_BUFFER;
    return rhi_make_handle(idx, dev->slots[idx].generation);
}

void rhi_buffer_destroy(RHIDevice *dev, RHIBuffer buf) {
    RHI_D3D12Buffer *bd;
    if (dev == NULL) return;
    bd = (RHI_D3D12Buffer *)rhi_get_resource_typed(dev, buf, RHI_RES_BUFFER);
    if (bd == NULL) return;
    if (bd->mapped != NULL) {
        ID3D12Resource_Unmap(bd->readback != NULL ? bd->readback : bd->resource,
                             0u, NULL);
        bd->mapped = NULL;
    }
    rhi_d3d12_release_deferred((RHI_D3D12Context *)dev->backend_data,
                               (IUnknown **)&bd->resource);
    if (bd->readback != NULL)
        rhi_d3d12_release_deferred((RHI_D3D12Context *)dev->backend_data,
                                   (IUnknown **)&bd->readback);
    free(bd);
    rhi_free_slot(dev, buf);
}

/* ---- shaders (Task 6) ----
 * rhi_shader_create{,_compute} take the sidecar FILE NAME (len == 0): the
 * HLSL source is read from engine/shaders (RHI_D3D12_SHADER_SOURCE_DIR) for
 * text reflection and the uniform-marker table, and the precompiled DXIL
 * blob from the build tree (RHI_D3D12_SHADER_DXIL_DIR, produced by the
 * build-time dxc step in CMakeLists.txt). A missing/invalid DXIL — the
 * precompile was skipped or failed — refuses the shader: fail closed,
 * never a blob-less module (rhi_pipeline_create rejects blob-less shaders).
 * len != 0 keeps the legacy inline-source mode (source retained, blob
 * NULL), which stays fail-closed at pipeline creation. */
#ifndef RHI_D3D12_SHADER_SOURCE_DIR
#error "RHI_D3D12_SHADER_SOURCE_DIR must be set (engine/shaders)"
#endif
#ifndef RHI_D3D12_SHADER_DXIL_DIR
#error "RHI_D3D12_SHADER_DXIL_DIR must be set (build-tree shaders_d3d12)"
#endif

#define RHI_D3D12_MAX_UNIFORM_LOCS 16u

typedef struct RHI_D3D12UniformLoc {
    char name[SHADER_IO_NAME_MAX];
    UINT offset;                /* byte offset into the root constants */
} RHI_D3D12UniformLoc;

typedef struct RHI_D3D12Shader {
    char *source;
    usize source_len;
    UINT is_fragment;
    void *blob;         /* DXIL bytecode (Task 6) */
    usize blob_size;
} RHI_D3D12Shader;

typedef struct RHI_D3D12Pipeline {
    ID3D12PipelineState *pso;
    ID3D12RootSignature *root_sig;
    UINT is_compute;
    UINT push_param_index;      /* UINT_MAX = no constants param */
    UINT push_size;             /* declared root-constant bytes (clamped) */
    UINT vertex_stride;         /* effective input-layout stride */
    D3D12_PRIMITIVE_TOPOLOGY topology;
    UINT uniform_count;
    RHI_D3D12UniformLoc uniforms[RHI_D3D12_MAX_UNIFORM_LOCS];
    UINT image_root_params[RHI_D3D12_MAX_REGISTERS];
    UINT uniform_root_params[RHI_D3D12_MAX_REGISTERS];
    UINT storage_root_params[RHI_D3D12_MAX_REGISTERS];
    UINT storage_strides[RHI_D3D12_MAX_REGISTERS];
    UINT srv_buffer_strides[RHI_D3D12_MAX_REGISTERS];
    RHIPipelineDesc desc;
    /* R643: the PSO bakes its render-target formats, but callers only name a
     * colour format when it is not the RGBA8 default -- the bloom, tonemap,
     * sharpen, motion blur and SSS passes all draw into RGBA16F FBOs, and
     * the UI draws into the BGRA8 swapchain, through pipelines that never
     * said so. GL has no such state and VK builds per-format variants on
     * first use (vk_pipeline_for_fmt); this mirrors VK. rtv_formats is what
     * `pso` was built for (always with a D32 depth slot); variants are
     * created at draw time when the bound targets differ -- colour formats,
     * or no depth attachment at all -- from the DXIL copies kept here. */
    DXGI_FORMAT rtv_formats[RHI_MRT_MAX_ATTACHMENTS];
    UINT rtv_count;
    void *vs_blob, *ps_blob;
    usize vs_blob_size, ps_blob_size;
    struct {
        DXGI_FORMAT formats[RHI_MRT_MAX_ATTACHMENTS];
        UINT count;
        UINT no_dsv;
        ID3D12PipelineState *pso;
    } variants[6];
    UINT variant_count;
} RHI_D3D12Pipeline;

/* Bare file names only: no separators, drive letters, or traversal — the
 * shader directories are fixed by the build system. */
static int rhi_d3d12_shader_name_valid(const char *name) {
    const char *p;
    if (name == NULL || name[0] == '\0') return 0;
    for (p = name; *p != '\0'; ++p) {
        if (*p == '/' || *p == '\\' || *p == ':') return 0;
        if (*p == '.' && p[1] == '.') return 0;
    }
    return 1;
}

static int rhi_d3d12_shader_load(RHI_D3D12Shader *sd, const char *name) {
    char path[1024];
    usize dxil_len = 0u;
    (void)snprintf(path, sizeof(path), "%s/%s", RHI_D3D12_SHADER_SOURCE_DIR,
                   name);
    path[sizeof(path) - 1u] = '\0';
    sd->source = shader_read_file(path, &sd->source_len);
    if (sd->source == NULL) {
        LOG_WARN("D3D12: HLSL source %s not readable — refusing shader", path);
        return 0;
    }
    (void)snprintf(path, sizeof(path), "%s/%s.dxil", RHI_D3D12_SHADER_DXIL_DIR,
                   name);
    path[sizeof(path) - 1u] = '\0';
    sd->blob = shader_read_file(path, &dxil_len);
    sd->blob_size = dxil_len;
    if (sd->blob == NULL || dxil_len < 20u ||
        memcmp(sd->blob, "DXBC", 4u) != 0) {
        LOG_WARN("D3D12: precompiled DXIL for %s missing or invalid — "
                 "refusing shader (build-time dxc step must succeed first)",
                 name);
        free(sd->blob);
        free(sd->source);
        sd->blob = NULL;
        sd->source = NULL;
        sd->blob_size = 0u;
        sd->source_len = 0u;
        return 0;
    }
    return 1;
}

static RHIShader rhi_d3d12_shader_alloc(RHIDevice *dev, const char *source,
                                        usize len, UINT is_fragment) {
    RHI_D3D12Shader *sd;
    u32 idx;
    if (dev == NULL || source == NULL) return RHI_HANDLE_NULL;
    sd = (RHI_D3D12Shader *)calloc(1u, sizeof(*sd));
    if (sd == NULL) return RHI_HANDLE_NULL;
    if (len == 0u) {
        /* Filename mode: sidecar name -> HLSL source + precompiled DXIL. */
        if (!rhi_d3d12_shader_name_valid(source) ||
            !rhi_d3d12_shader_load(sd, source)) {
            free(sd);
            return RHI_HANDLE_NULL;
        }
    } else {
        /* Inline-source mode. This backend has no HLSL compiler in-process:
         * it loads precompiled DXIL by sidecar name (filename mode above,
         * which refuses loudly when the DXIL is absent). So an inline source
         * can only ever produce a shader with no blob, and returning a valid
         * handle for one hides the real cause two steps downstream -- every
         * call site saw "shader compile failed" as false, went on to
         * rhi_pipeline_create, and reported "pipeline creation failed" or
         * "bindings create failed", which names neither the backend nor the
         * missing sidecar. Refusing here is what turns ~25 misleading demo
         * warnings into one actionable line each. */
        LOG_WARN("D3D12: rhi_shader_create was given inline source, but this "
                 "backend never compiles HLSL in-process -- it only loads "
                 "precompiled DXIL by sidecar name. Use rhi_shader_create_path"
                 "(\"shaders/<name>.vert\") and add shaders/<name>_hlsl.vert "
                 "to the build.");
        free(sd);
        return RHI_HANDLE_NULL;
    }
    sd->is_fragment = is_fragment;
    idx = rhi_alloc_slot(dev);
    dev->slots[idx].ptr = sd;
    dev->slots[idx].type = RHI_RES_SHADER;
    return rhi_make_handle(idx, dev->slots[idx].generation);
}

RHIShader rhi_shader_create(RHIDevice *dev, const char *source, usize len,
                            bool is_fragment) {
    return rhi_d3d12_shader_alloc(dev, source, len, is_fragment ? 1u : 0u);
}
RHIShader rhi_shader_create_compute(RHIDevice *dev, const char *source,
                                    usize len) {
    return rhi_d3d12_shader_alloc(dev, source, len, 0u);
}

/* Sidecar name derivation for rhi_shader_create_path: drop the directory and
 * the extension, append "_hlsl" unless the base already carries it, then add
 * the stage suffix. See rhi_d3d12.h for the full contract and the decision
 * record on the idempotent suffix.
 *
 * The path's own stage extension is authoritative about intent: a path that
 * says ".frag" handed to the vertex path entry point is a caller bug, and
 * ignoring the extension would silently resolve the vertex sidecar and
 * render it — the one outcome harder to notice than a refusal. So the
 * mismatch is refused rather than papered over. An extension that names no
 * known stage (or no extension at all) carries no claim about the stage, and
 * the caller's stage argument stays authoritative there. */
static const char *rhi_d3d12_shader_stage_suffix(RHI_D3D12ShaderStage stage) {
    switch (stage) {
        case RHI_D3D12_SHADER_STAGE_VERTEX:   return ".vert";
        case RHI_D3D12_SHADER_STAGE_FRAGMENT: return ".frag";
        case RHI_D3D12_SHADER_STAGE_COMPUTE:  return ".comp";
        default: return NULL;
    }
}

static int rhi_d3d12_shader_stage_from_ext(const char *ext,
                                           RHI_D3D12ShaderStage *out) {
    if (strcmp(ext, ".vert") == 0) { *out = RHI_D3D12_SHADER_STAGE_VERTEX;   return 1; }
    if (strcmp(ext, ".frag") == 0) { *out = RHI_D3D12_SHADER_STAGE_FRAGMENT; return 1; }
    if (strcmp(ext, ".comp") == 0) { *out = RHI_D3D12_SHADER_STAGE_COMPUTE;  return 1; }
    return 0;
}

int rhi_d3d12_shader_sidecar_name(const char *path,
                                  RHI_D3D12ShaderStage stage, char *out,
                                  usize out_cap) {
    const char *base;
    const char *p;
    const char *ext = NULL;
    const char *suffix;
    usize base_len;
    usize needed;
    int already_suffixed;
    int written;
    /* Cleared up front so every refusal — including a NULL path or a zero
     * capacity — leaves the caller with a name it can trust is absent. */
    if (out != NULL && out_cap > 0u) out[0] = '\0';
    if (path == NULL || out == NULL || out_cap == 0u) return 0;

    suffix = rhi_d3d12_shader_stage_suffix(stage);
    if (suffix == NULL) {
        LOG_WARN("D3D12: shader stage %d is outside RHI_D3D12ShaderStage — no "
                 "sidecar suffix exists, refusing shader", (int)stage);
        return 0;
    }

    base = path;
    for (p = path; *p != '\0'; ++p)
        if (*p == '/' || *p == '\\') base = p + 1;
    for (p = base; *p != '\0'; ++p)
        if (*p == '.') ext = p;

    if (ext != NULL) {
        RHI_D3D12ShaderStage path_stage;
        if (rhi_d3d12_shader_stage_from_ext(ext, &path_stage) &&
            path_stage != stage) {
            LOG_WARN("D3D12: shader path %s names the %s stage but the %s "
                     "stage was requested — refusing shader rather than "
                     "resolving the wrong sidecar", path,
                     rhi_d3d12_shader_stage_suffix(path_stage), suffix);
            return 0;
        }
    }

    base_len = ext != NULL ? (usize)(ext - base) : strlen(base);
    if (base_len == 0u) {
        LOG_WARN("D3D12: shader path %s has no base name before its extension "
                 "— refusing shader", path);
        return 0;
    }
    /* Rejecting an over-long base here (rather than only via `needed` below)
     * also keeps the (int) precision cast in range. */
    if (base_len >= out_cap) {
        LOG_WARN("D3D12: shader path %s has a %u byte base name, over the %u "
                 "byte name budget — refusing shader", path,
                 (unsigned)base_len, (unsigned)out_cap);
        return 0;
    }
    already_suffixed = base_len >= 5u &&
                       memcmp(base + base_len - 5u, "_hlsl", 5u) == 0;
    /* Budget the whole name up front so the format below can never
     * truncate: a partial name left in `out` would resolve some other file,
     * which is exactly what the refusal exists to prevent. */
    needed = base_len + (already_suffixed ? 0u : 5u) + strlen(suffix) + 1u;
    if (needed > out_cap) {
        LOG_WARN("D3D12: sidecar name for %s needs %u bytes, over the %u byte "
                 "name budget — refusing shader", path, (unsigned)needed,
                 (unsigned)out_cap);
        return 0;
    }
    if (already_suffixed) {
        written = snprintf(out, out_cap, "%.*s%s", (int)base_len, base, suffix);
    } else {
        written = snprintf(out, out_cap, "%.*s_hlsl%s", (int)base_len, base, suffix);
    }
    if (written < 0 || (usize)written >= out_cap) {
        out[0] = '\0';
        LOG_WARN("D3D12: sidecar name for %s did not fit the %u byte name "
                 "budget — refusing shader", path, (unsigned)out_cap);
        return 0;
    }
    return 1;
}

RHIShader rhi_shader_create_path(RHIDevice *dev, const char *path,
                                 bool is_fragment) {
    char name[RHI_D3D12_SHADER_SIDECAR_NAME_CAPACITY];
    RHI_D3D12ShaderStage stage = is_fragment ? RHI_D3D12_SHADER_STAGE_FRAGMENT
                                            : RHI_D3D12_SHADER_STAGE_VERTEX;
    if (dev == NULL) return RHI_HANDLE_NULL;
    if (!rhi_d3d12_shader_sidecar_name(path, stage, name, (usize)sizeof(name)))
        return RHI_HANDLE_NULL;
    return rhi_shader_create(dev, name, 0u, is_fragment);
}

RHIShader rhi_shader_create_compute_path(RHIDevice *dev, const char *path) {
    char name[RHI_D3D12_SHADER_SIDECAR_NAME_CAPACITY];
    if (dev == NULL) return RHI_HANDLE_NULL;
    if (!rhi_d3d12_shader_sidecar_name(path, RHI_D3D12_SHADER_STAGE_COMPUTE,
                                       name, (usize)sizeof(name)))
        return RHI_HANDLE_NULL;
    return rhi_shader_create_compute(dev, name, 0u);
}

void rhi_shader_destroy(RHIDevice *dev, RHIShader shader) {
    RHI_D3D12Shader *sd;
    if (dev == NULL) return;
    sd = (RHI_D3D12Shader *)rhi_get_resource_typed(dev, shader, RHI_RES_SHADER);
    if (sd == NULL) return;
    free(sd->source);
    free(sd->blob);
    free(sd);
    rhi_free_slot(dev, shader);
}

/* ---- Task 6: line-oriented HLSL reflection for the hand-authored sidecars
 * ----
 * The shared shader_io parser speaks GLSL layout() syntax; the sidecars are
 * HLSL, so bindings come from this scanner. Recognized declarations (one
 * per line):
 *   ConstantBuffer<T> name : register(b0[, spaceN]) -> push-constant block.
 *       b0 is RESERVED for the 32BIT_CONSTANTS root param (Task 5 review
 *       handoff): a CBV at b0 would collide with the constants register and
 *       fail root-signature serialization.
 *   ConstantBuffer<T> name : register(bN)  (N > 0)   -> CBV table
 *   Texture2D name : register(tN)                    -> SRV + static sampler
 *       (sidecar convention: SamplerState sN pairs with Texture2D tN; the
 *       SamplerState line itself is skipped, the builder emits the static
 *       sampler for the SAMPLER-kind binding)
 *   StructuredBuffer<T> name : register(tN)          -> SRV
 *   RWStructuredBuffer<T> / RWByteAddressBuffer /
 *   RWTexture2D<T> name : register(uN)               -> UAV
 * Uniform-name side channel (rhi_pipeline_get_uniform_location):
 *   // rhi:uniform <name> <byte_offset>
 * Everything else is ignored; an unrecognized resource declaration simply
 * never reaches the root signature, which fails closed at PSO creation. */
static const char *rhi_d3d12_hlsl_find(const char *src, const char *end,
                                       const char *needle) {
    usize n = strlen(needle);
    while (src < end && (usize)(end - src) >= n) {
        if (memcmp(src, needle, n) == 0) return src;
        ++src;
    }
    return NULL;
}

static int rhi_d3d12_hlsl_ident_char(char c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') ||
           (c >= '0' && c <= '9') || c == '_';
}

static usize rhi_d3d12_reflect_hlsl(const char *src, usize len,
                                    ShaderIOBinding *out, usize capacity) {
    const char *line = src;
    const char *end = src + len;
    usize count = 0u;
    while (line < end) {
        const char *nl = memchr(line, '\n', (size_t)(end - line));
        const char *line_end = nl != NULL ? nl : end;
        const char *p = line;
        const char *reg;
        ShaderIOBinding *b;
        ShaderIOResourceKind kind;
        ShaderIOLayout layout = SHADER_IO_LAYOUT_DEFAULT;
        char klass;
        UINT regnum = 0u;
        int has_digit = 0;
        while (p < line_end && (*p == ' ' || *p == '\t' || *p == '\r')) ++p;
        if (p >= line_end || (p + 1 < line_end && p[0] == '/' && p[1] == '/')) {
            line = nl != NULL ? nl + 1 : end;
            continue;
        }
        reg = rhi_d3d12_hlsl_find(p, line_end, "register(");
        if (reg == NULL) {
            line = nl != NULL ? nl + 1 : end;
            continue;
        }
        reg += 9u;
        if (reg >= line_end) { line = nl != NULL ? nl + 1 : end; continue; }
        klass = *reg++;
        while (reg < line_end && *reg >= '0' && *reg <= '9') {
            regnum = regnum * 10u + (UINT)(*reg - '0');
            has_digit = 1;
            ++reg;
        }
        /* 's' (sampler) was missing here: every register(sN, ...) line was
         * dropped silently, so no SamplerState ever reached the root
         * signature. The sidecars only worked because Texture2D was
         * misclassified as SAMPLER and the static sampler it produced
         * happened to cover s0 as well. */
        if (!has_digit || (klass != 'b' && klass != 't' && klass != 'u' &&
                         klass != 's')) {
            line = nl != NULL ? nl + 1 : end;
            continue;
        }
        if (rhi_d3d12_hlsl_find(p, line_end, "RWStructuredBuffer") != NULL ||
            rhi_d3d12_hlsl_find(p, line_end, "RWByteAddressBuffer") != NULL ||
            rhi_d3d12_hlsl_find(p, line_end, "RWTexture") != NULL) {
            kind = SHADER_IO_RESOURCE_STORAGE;
        } else if (rhi_d3d12_hlsl_find(p, line_end, "ConstantBuffer") != NULL) {
            if (regnum == 0u) {
                kind = SHADER_IO_RESOURCE_PUSH_CONSTANT; /* b0 = root constants */
                layout = SHADER_IO_LAYOUT_PUSH_CONSTANT;
            } else {
                kind = SHADER_IO_RESOURCE_UNIFORM;
            }
        } else if (rhi_d3d12_hlsl_find(p, line_end, "SamplerState") != NULL) {
            kind = SHADER_IO_RESOURCE_SAMPLER; /* static sampler */
        } else if (rhi_d3d12_hlsl_find(p, line_end, "Texture") != NULL) {
            /* A Texture2D is an SRV resource, not a sampler. */
            kind = SHADER_IO_RESOURCE_IMAGE;   /* SRV range */
        } else if (rhi_d3d12_hlsl_find(p, line_end, "StructuredBuffer") != NULL ||
                   rhi_d3d12_hlsl_find(p, line_end, "ByteAddressBuffer") != NULL) {
            kind = SHADER_IO_RESOURCE_IMAGE;   /* read-only SRV */
        } else {
            line = nl != NULL ? nl + 1 : end; /* SamplerState & co: skipped */
            continue;
        }
        if (count >= capacity) {
            LOG_WARN("D3D12: HLSL reflection overflow (%u bindings max)",
                     (unsigned)capacity);
            return 0u; /* fail closed: a partial root signature is worse */
        }
        b = &out[count++];
        memset(b, 0, sizeof(*b));
        b->kind = kind;
        b->layout = layout;
        b->set = 0u;
        b->binding = regnum;
        /* A UAV descriptor has to match the shader's view of the buffer, so
         * the binder needs the element type. It rides in `format`: "raw" for
         * RWByteAddressBuffer, the template argument for RWStructuredBuffer,
         * empty for anything else (RWTexture*). */
        if (kind == SHADER_IO_RESOURCE_STORAGE ||
            (kind == SHADER_IO_RESOURCE_IMAGE && klass == 't' &&
             rhi_d3d12_hlsl_find(p, line_end, "Texture") == NULL)) {
            const char *sb = rhi_d3d12_hlsl_find(p, line_end, "StructuredBuffer<");
            if (rhi_d3d12_hlsl_find(p, line_end, "ByteAddressBuffer") != NULL) {
                memcpy(b->format, "raw", 4u);
            } else if (sb != NULL) {
                const char *t = sb + 17u;
                usize n = 0u;
                while (t < line_end && (*t == ' ' || *t == '\t')) ++t;
                while (t + n < line_end && rhi_d3d12_hlsl_ident_char(t[n]) &&
                       n + 1u < sizeof(b->format))
                    ++n;
                memcpy(b->format, t, n);
                b->format[n] = '\0';
            }
        }
        line = nl != NULL ? nl + 1 : end;
    }
    return count;
}

/* Parse `// rhi:uniform <name> <offset>` markers from one HLSL source into
 * the pipeline's name -> byte-offset table. Duplicate names keep the first
 * offset (VS/PS markers for the same block must agree). */
static void rhi_d3d12_uniform_markers(const char *src, usize len,
                                      RHI_D3D12UniformLoc *table,
                                      UINT *count) {
    const char *p = src;
    const char *end = src + len;
    while (p < end) {
        const char *mark = rhi_d3d12_hlsl_find(p, end, "rhi:uniform");
        char name[SHADER_IO_NAME_MAX];
        usize n = 0u;
        UINT offset = 0u;
        UINT i;
        int has_digit = 0;
        if (mark == NULL) return;
        p = mark + strlen("rhi:uniform");
        while (p < end && (*p == ' ' || *p == '\t')) ++p;
        while (p < end && rhi_d3d12_hlsl_ident_char(*p)) {
            if (n + 1u < sizeof(name)) name[n++] = *p;
            ++p;
        }
        name[n] = '\0';
        while (p < end && (*p == ' ' || *p == '\t')) ++p;
        while (p < end && *p >= '0' && *p <= '9') {
            offset = offset * 10u + (UINT)(*p - '0');
            has_digit = 1;
            ++p;
        }
        if (n == 0u || !has_digit) continue;
        for (i = 0u; i < *count; ++i)
            if (strcmp(table[i].name, name) == 0) break;
        if (i < *count) continue; /* first declaration wins */
        if (*count >= RHI_D3D12_MAX_UNIFORM_LOCS) {
            LOG_WARN("D3D12: uniform marker table full; %s not recorded", name);
            continue;
        }
        memcpy(table[*count].name, name, n + 1u);
        table[*count].offset = offset;
        (*count)++;
    }
}

/* R636: the HLSL constant-buffer packing rules, as dxc applies them to a
 * struct declared in a cbuffer: a matrix is one 16-byte column per column
 * of the type (float4x4 -> 64 bytes) on a 16-byte boundary, a float3 is 12
 * bytes but still 16-byte aligned, a float2 is 8 bytes on an 8-byte
 * boundary, and a scalar is 4 bytes.
 *
 * The `// rhi:uniform` markers publish byte offsets into that same block,
 * so a marker that disagrees with the struct it names is a silent bug: the
 * write lands on the wrong member and the shader reads a value nobody
 * wrote. motion_blur's u_mb_prev_vp said 32 where the layout says 80 --
 * inside the 64-byte u_mb_inv_proj -- and the depth-reconstruction branch
 * then read a matrix that was never written.
 *
 * The check is fail-closed: the pipeline is refused rather than built on
 * offsets nobody can vouch for. */
#define RHI_D3D12_MAX_CBUFFER_MEMBERS 32u

typedef struct {
    char name[SHADER_IO_NAME_MAX];
    UINT offset;
} RHI_D3D12CbufferMember;

/* Size and alignment of one cbuffer member type, or 0 when the type is not
 * one this checker understands (a struct member with a semantic, say, which
 * is not a cbuffer member at all). */
static int rhi_d3d12_hlsl_member_layout(const char *type, usize type_len,
                                         UINT *out_size, UINT *out_align) {
    static const struct { const char *name; UINT size; UINT align; } scalars[] = {
        { "float", 4u, 4u },  { "int", 4u, 4u },    { "uint", 4u, 4u },
        { "bool", 4u, 4u },   { "half", 4u, 4u },   { "float2", 8u, 8u },
        { "int2", 8u, 8u },   { "uint2", 8u, 8u },  { "float3", 12u, 16u },
        { "int3", 12u, 16u },{ "uint3", 12u, 16u },{ "float4", 16u, 16u },
        { "int4", 16u, 16u }, { "uint4", 16u, 16u },
    };
    usize i;
    for (i = 0u; i < sizeof(scalars) / sizeof(scalars[0]); ++i) {
        if (strlen(scalars[i].name) == type_len &&
            memcmp(scalars[i].name, type, type_len) == 0) {
            *out_size = scalars[i].size;
            *out_align = scalars[i].align;
            return 1;
        }
    }
    /* floatRxC: the cbuffer stores C columns of 16 bytes each. */
    if (type_len >= 8u && memcmp(type, "float", 5u) == 0 &&
        type[5] >= '2' && type[5] <= '4' && type[6] == 'x' &&
        type[7] >= '2' && type[7] <= '4' && type_len == 8u) {
        *out_size = (UINT)(type[7] - '0') * 16u;
        *out_align = 16u;
        return 1;
    }
    return 0;
}

/* Locate `struct <name> {` and hand back the body between the braces. */
static int rhi_d3d12_hlsl_struct_body(const char *src, usize len,
                                       const char *name, const char **out_body,
                                       usize *out_len) {
    const char *p = src;
    const char *end = src + len;
    char pattern[64];
    int written = snprintf(pattern, sizeof(pattern), "struct %s", name);
    if (written <= 0) return 0;
    while (p < end) {
        const char *hit = rhi_d3d12_hlsl_find(p, end, pattern);
        const char *brace;
        const char *scan;
        int depth = 0;
        if (hit == NULL) return 0;
        brace = hit + written;
        while (brace < end && *brace != '{') {
            if (*brace == ';') return 0;   /* a forward declaration */
            ++brace;
        }
        if (brace >= end) return 0;
        for (scan = brace; scan < end; ++scan) {
            if (*scan == '{') depth++;
            else if (*scan == '}') {
                depth--;
                if (depth == 0) {
                    *out_body = brace + 1;
                    *out_len = (usize)(scan - brace - 1);
                    return 1;
                }
            }
        }
        p = hit + written;
    }
    return 0;
}

/* The layout of the struct the push block is declared with: the markers
 * publish offsets into the b0 cbuffer, so that is the struct they have to
 * agree with. */
static int rhi_d3d12_hlsl_push_layout(const char *src, usize len,
                                       RHI_D3D12CbufferMember *out,
                                       usize capacity, usize *out_count) {
    const char *bind;
    const char *end = src + len;
    const char *body;
    usize body_len;
    char struct_name[SHADER_IO_NAME_MAX];
    usize n = 0u;
    *out_count = 0u;
    /* The markers publish offsets into the b0 cbuffer, so the struct they
     * have to agree with is the one bound at b0 -- not the first cbuffer in
     * the file, which is the b1 temporal block in the sidecars that have
     * one. */
    bind = src;
    struct_name[0] = '\0';
    while (bind < end) {
        const char *hit = rhi_d3d12_hlsl_find(bind, end, "ConstantBuffer<");
        const char *scan;
        usize name_len = 0u;
        if (hit == NULL) break;
        scan = hit + strlen("ConstantBuffer<");
        while (scan < end && *scan != '>' && name_len + 1u < sizeof(struct_name)) {
            if (rhi_d3d12_hlsl_ident_char(*scan))
                struct_name[name_len++] = *scan;
            else if (name_len > 0u) break;
            ++scan;
        }
        struct_name[name_len] = '\0';
        if (name_len == 0u) { bind = scan; continue; }
        /* Is this declaration the b0 one? */
        {
            const char *probe = scan;
            for (; probe < end && *probe != ';'; ++probe) {
                if (rhi_d3d12_hlsl_find(probe, end, "register(b0") == probe)
                    goto found;
                if (*probe == '\n') break;   /* the declaration ended */
            }
        }
        bind = hit + strlen("ConstantBuffer<");
    }
found:
    if (struct_name[0] == '\0') return 1;   /* no push block: nothing to check */
    if (!rhi_d3d12_hlsl_struct_body(src, len, struct_name, &body, &body_len))
        return 1;
    /* Members are `type name;` declarations; a member with a semantic
     * (`: SV_Position`) is not a cbuffer member and is skipped. The body is
     * copied with its comments blanked out first: a trailing `// 16` comment
     * sits AFTER the semicolon, so splitting the raw text on ';' would make
     * every declaration but the first start with the comment. */
    {
        char buf[2048];
        usize n_copy = body_len < sizeof(buf) - 1u ? body_len : sizeof(buf) - 1u;
        char *p;
        char *pend;
        char *semi;
        char *colon;
        char *d;
        char *type_start;
        char *type_end;
        char *name_start;
        char *name_end;
        char type[32];
        usize type_len;
        UINT size = 0u;
        UINT align_ = 0u;
        UINT offset = 0u;
        memcpy(buf, body, n_copy);
        buf[n_copy] = '\0';
        /* Blank the comments in the COPY: the source is const and a trailing
         * `// 16` comment sits AFTER the semicolon, so splitting the raw
         * text on ';' would make every declaration but the first start with
         * the comment. */
        p = buf;
        pend = buf + n_copy;
        while (p < pend) {
            if (p + 1 < pend && p[0] == '/' && p[1] == '/') {
                while (p < pend && *p != '\n') *p++ = ' ';
                continue;
            }
            if (p + 1 < pend && p[0] == '/' && p[1] == '*') {
                *p++ = ' ';
                *p++ = ' ';
                while (p + 1 < pend && !(p[0] == '*' && p[1] == '/')) {
                    if (*p != '\n') *p = ' ';
                    ++p;
                }
                if (p + 1 < pend) { *p = ' '; *(p + 1) = ' '; p += 2; }
                continue;
            }
            ++p;
        }
        p = buf;
        while (p < pend) {
            semi = (char *)memchr(p, ';', (size_t)(pend - p));
            if (semi == NULL) break;
            colon = (char *)memchr(p, ':', (size_t)(semi - p));
            if (colon != NULL) {   /* has a semantic: not a cbuffer member */
                p = semi + 1;
                continue;
            }
            d = p;
            while (d < semi && (*d == ' ' || *d == '\t' || *d == '\r' ||
                                *d == '\n')) ++d;
            type_start = d;
            while (d < semi && *d != ' ' && *d != '\t' && *d != '\r' &&
                   *d != '\n') ++d;
            type_end = d;
            while (d < semi && (*d == ' ' || *d == '\t' || *d == '\r' ||
                                *d == '\n')) ++d;
            name_start = d;
            while (d < semi && rhi_d3d12_hlsl_ident_char(*d)) ++d;
            name_end = d;
            type_len = (usize)(type_end - type_start);
            if (type_len == 0u || type_len >= sizeof(type)) {
                p = semi + 1;
                continue;
            }
            memcpy(type, type_start, type_len);
            type[type_len] = '\0';
            if (!rhi_d3d12_hlsl_member_layout(type, type_len, &size, &align_)) {
                p = semi + 1;
                continue;
            }
            offset = (offset + align_ - 1u) / align_ * align_;
            if (n < capacity) {
                usize name_size = (usize)(name_end - name_start);
                if (name_size > 0u && name_size < SHADER_IO_NAME_MAX) {
                    memcpy(out[n].name, name_start, name_size);
                    out[n].name[name_size] = '\0';
                    out[n].offset = offset;
                    n++;
                }
            }
            offset += size;
            p = semi + 1;
        }
    }
    *out_count = n;
    return 1;
}

/* Cross-check the markers against the push block's layout. Returns 0 when a
 * marker disagrees, so the caller can refuse the pipeline. */
static int rhi_d3d12_hlsl_markers_match_layout(const char *src, usize len) {
    RHI_D3D12UniformLoc markers[RHI_D3D12_MAX_UNIFORM_LOCS];
    RHI_D3D12CbufferMember members[RHI_D3D12_MAX_CBUFFER_MEMBERS];
    UINT marker_count = 0u;
    usize member_count = 0u;
    UINT i;
    int ok = 1;
    rhi_d3d12_uniform_markers(src, len, markers, &marker_count);
    if (marker_count == 0u) return 1;
    if (!rhi_d3d12_hlsl_push_layout(src, len, members,
                                    RHI_D3D12_MAX_CBUFFER_MEMBERS,
                                    &member_count))
        return 1;
    if (member_count == 0u) return 1;
    for (i = 0u; i < marker_count; ++i) {
        usize j;
        for (j = 0u; j < member_count; ++j) {
            if (strcmp(members[j].name, markers[i].name) != 0) continue;
            if (members[j].offset == markers[i].offset) break;
            LOG_ERROR("D3D12: uniform %s is published at byte %u but the "
                      "cbuffer layout puts it at %u -- the marker and the "
                      "struct disagree, so the write would land on the "
                      "wrong member. Refusing the shader.", markers[i].name,
                      (unsigned)markers[i].offset, (unsigned)members[j].offset);
            ok = 0;
            break;
        }
    }
    return ok;
}

/* Element size of a reflected RWStructuredBuffer<T> for the scalar and
 * vector types the compute sidecars use. 0 = raw view; UINT_MAX = no view
 * this backend can describe, which makes the binder refuse the bind. */
static UINT rhi_d3d12_storage_stride(const char *format) {
    static const struct { const char *name; UINT size; } k_types[] = {
        { "uint", 4u }, { "int", 4u }, { "float", 4u },
        { "uint2", 8u }, { "int2", 8u }, { "float2", 8u },
        { "uint3", 12u }, { "int3", 12u }, { "float3", 12u },
        { "uint4", 16u }, { "int4", 16u }, { "float4", 16u },
        { "float4x4", 64u },
    };
    usize i;
    if (strcmp(format, "raw") == 0) return 0u;
    for (i = 0u; i < sizeof(k_types) / sizeof(k_types[0]); ++i)
        if (strcmp(format, k_types[i].name) == 0) return k_types[i].size;
    return UINT_MAX;
}

static void rhi_d3d12_root_sig_note_storage(RHI_D3D12RootSigBuilder *b,
                                            const ShaderIOBinding *bind,
                                            UINT param) {
    if (bind->binding >= RHI_D3D12_MAX_REGISTERS) return;
    if (bind->kind == SHADER_IO_RESOURCE_STORAGE) {
        b->storage_root_params[bind->binding] = param;
        b->storage_strides[bind->binding] = rhi_d3d12_storage_stride(bind->format);
    } else if (bind->kind == SHADER_IO_RESOURCE_IMAGE && bind->format[0] != '\0') {
        /* A read-only buffer at register(tN): GLSL's `readonly buffer`. */
        b->srv_buffer_strides[bind->binding] = rhi_d3d12_storage_stride(bind->format);
    }
}

/* ---- root signature generation (Task 5) ---- */
/* One pass over reflected bindings: PUSH_CONSTANT folds into the constants
 * param the caller added first; UNIFORM -> CBV table; SAMPLER -> SRV table +
 * static sampler slot; STORAGE -> UAV table; IMAGE -> SRV table. Registers
 * follow the reflected binding (space 0). Returns 0 on overflow. */
static int rhi_d3d12_root_sig_add_bindings(RHI_D3D12RootSigBuilder *b,
                                           const ShaderIOBinding *bindings,
                                           usize count,
                                           D3D12_SHADER_VISIBILITY visibility) {
    usize i;
    for (i = 0u; i < count; ++i) {
        const ShaderIOBinding *bind = &bindings[i];
        D3D12_DESCRIPTOR_RANGE1 *range;
        D3D12_ROOT_PARAMETER1 *param;
        D3D12_DESCRIPTOR_RANGE_TYPE range_type;
        UINT base_register;
        switch (bind->kind) {
        case SHADER_IO_RESOURCE_UNIFORM:
            range_type = D3D12_DESCRIPTOR_RANGE_TYPE_CBV;
            break;
        case SHADER_IO_RESOURCE_STORAGE:
            range_type = D3D12_DESCRIPTOR_RANGE_TYPE_UAV;
            break;
        case SHADER_IO_RESOURCE_SAMPLER:
            /* A SamplerState resolves through a static sampler, not a
             * descriptor table; emitting both overlaps at register 0. */
            {
                D3D12_STATIC_SAMPLER_DESC *sampler;
                if (b->sampler_count >= 8u) return 0;
                sampler = &b->samplers[b->sampler_count++];
                ZeroMemory(sampler, sizeof(*sampler));
                sampler->Filter = D3D12_FILTER_MIN_MAG_MIP_LINEAR;
                sampler->AddressU = b->clamp_samplers ? D3D12_TEXTURE_ADDRESS_MODE_CLAMP
                                                      : D3D12_TEXTURE_ADDRESS_MODE_WRAP;
                sampler->AddressV = b->clamp_samplers ? D3D12_TEXTURE_ADDRESS_MODE_CLAMP
                                                      : D3D12_TEXTURE_ADDRESS_MODE_WRAP;
                sampler->AddressW = b->clamp_samplers ? D3D12_TEXTURE_ADDRESS_MODE_CLAMP
                                                      : D3D12_TEXTURE_ADDRESS_MODE_WRAP;
                sampler->MaxLOD = D3D12_FLOAT32_MAX;
                sampler->ShaderRegister = bind->binding;
                sampler->RegisterSpace = 0u;
                sampler->ShaderVisibility = visibility;
            }
            continue;
        case SHADER_IO_RESOURCE_IMAGE:
            range_type = D3D12_DESCRIPTOR_RANGE_TYPE_SRV;
            break;
        case SHADER_IO_RESOURCE_PUSH_CONSTANT:
        default:
            continue; /* folded into the 32BIT_CONSTANTS param */
        }
        base_register = bind->binding;
        {
            UINT reuse;
            for (reuse = 0u; reuse < b->param_count; ++reuse) {
                D3D12_ROOT_PARAMETER1 *rp = &b->params[reuse];
                const D3D12_DESCRIPTOR_RANGE1 *rr;
                if (rp->ParameterType !=
                    D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE) continue;
                if (rp->DescriptorTable.NumDescriptorRanges != 1u) continue;
                rr = rp->DescriptorTable.pDescriptorRanges;
                if (rr->RangeType != range_type) continue;
                if (rr->BaseShaderRegister != base_register) continue;
                if (rr->RegisterSpace != 0u) continue;
                if (rr->NumDescriptors != 1u) continue;
                /* R605: assign, never OR. In this SDK the
                 * D3D12_SHADER_VISIBILITY enumerators are sequential
                 * values (ALL 0, VERTEX 1, PIXEL 5), NOT bitmasks, so
                 * VERTEX | PIXEL evaluates to PIXEL and silently drops
                 * vertex visibility -- which is exactly the bug: the
                 * vertex shader would keep reading a table it cannot
                 * see, and the failure would be silent. */
                rp->ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL;
                if (bind->kind == SHADER_IO_RESOURCE_IMAGE && base_register < RHI_D3D12_MAX_REGISTERS)
                    b->image_root_params[base_register] = reuse;
                if (bind->kind == SHADER_IO_RESOURCE_UNIFORM && base_register < RHI_D3D12_MAX_REGISTERS)
                    b->uniform_root_params[base_register] = reuse;
                rhi_d3d12_root_sig_note_storage(b, bind, reuse);
                goto next_binding;
            }
        }
        if (b->param_count >= 23u || b->range_count >= 24u) return 0;
        range = &b->ranges[b->range_count++];
        ZeroMemory(range, sizeof(*range));
        range->RangeType = range_type;
        range->NumDescriptors = 1u;
        range->BaseShaderRegister = base_register;
        range->RegisterSpace = 0u;
        range->Flags = D3D12_DESCRIPTOR_RANGE_FLAG_NONE;
        range->OffsetInDescriptorsFromTableStart =
            D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;
        param = &b->params[b->param_count++];
        ZeroMemory(param, sizeof(*param));
        param->ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
        param->DescriptorTable.NumDescriptorRanges = 1u;
        param->DescriptorTable.pDescriptorRanges = range;
        param->ShaderVisibility = visibility;
        if (bind->kind == SHADER_IO_RESOURCE_IMAGE && bind->binding < RHI_D3D12_MAX_REGISTERS)
            b->image_root_params[bind->binding] = b->param_count - 1u;
        if (bind->kind == SHADER_IO_RESOURCE_UNIFORM && bind->binding < RHI_D3D12_MAX_REGISTERS)
            b->uniform_root_params[bind->binding] = b->param_count - 1u;
        rhi_d3d12_root_sig_note_storage(b, bind, b->param_count - 1u);
next_binding:
        ;
    }
    return 1;
}

static int rhi_d3d12_root_sig_from_bindings(RHI_D3D12RootSigBuilder *b,
                                            const ShaderIOBinding *bindings,
                                            usize count) {
    return rhi_d3d12_root_sig_add_bindings(b, bindings, count,
                                           D3D12_SHADER_VISIBILITY_ALL);
}

/* The 32BIT_CONSTANTS param goes in first (root param index 0) so both
 * graphics and compute push writes share one index. Graphics declares the
 * VK-parity 256B range, compute 128B (rhi.h R444 contract); the D3D12 root
 * signature budget is 64 DWORDs total, so the constants size is clamped
 * against the table cost — writes past the declared range are dropped by
 * the shared rhi_push_range_fits validation, never silently truncated
 * (same semantics as VK's R417 clamp). */
static ID3D12RootSignature *rhi_d3d12_root_signature_create(
        RHI_D3D12Context *ctx, RHI_D3D12RootSigBuilder *b, UINT is_compute,
        UINT *out_push_param_index, UINT *out_push_size) {
    D3D12_VERSIONED_ROOT_SIGNATURE_DESC desc;
    D3D12_ROOT_SIGNATURE_DESC1 *d1;
    D3D12_FEATURE_DATA_ROOT_SIGNATURE feature;
    ID3DBlob *serialized = NULL;
    ID3DBlob *error_blob = NULL;
    ID3D12RootSignature *root_sig = NULL;
    UINT table_params = b->param_count;
    UINT requested_dwords;
    UINT max_dwords;
    HRESULT hr;
    *out_push_param_index = UINT_MAX;
    *out_push_size = 0u;
    if (b->push_constant_size > 0u && b->param_count < 24u) {
        D3D12_ROOT_PARAMETER1 *param;
        UINT i;
        requested_dwords = b->push_constant_size / 4u;
        /* Descriptor tables cost 1 DWORD each; keep the total <= 64. */
        max_dwords = table_params >= 64u ? 0u : 64u - table_params;
        if (requested_dwords > max_dwords) requested_dwords = max_dwords;
        if (requested_dwords > 0u) {
            /* Shift table params up; constants take index 0. */
            for (i = b->param_count; i > 0u; --i)
                b->params[i] = b->params[i - 1u];
            param = &b->params[0];
            ZeroMemory(param, sizeof(*param));
            param->ParameterType = D3D12_ROOT_PARAMETER_TYPE_32BIT_CONSTANTS;
            param->Constants.ShaderRegister = 0u;
            param->Constants.RegisterSpace = 0u;
            param->Constants.Num32BitValues = requested_dwords;
            param->ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL;
            b->param_count++;
            *out_push_param_index = 0u;
            *out_push_size = requested_dwords * 4u;
        }
    }
    ZeroMemory(&feature, sizeof(feature));
    feature.HighestVersion = D3D_ROOT_SIGNATURE_VERSION_1_1;
    hr = ID3D12Device_CheckFeatureSupport(ctx->device,
        D3D12_FEATURE_ROOT_SIGNATURE, &feature, (UINT)sizeof(feature));
    /* The builder emits 1.1 shapes; fail closed rather than downcast to a
     * 1.0 layout (the range structs differ). 1.1 is universal on any
     * FL12-capable Win10 14393+ stack. */
    if (FAILED(hr) || feature.HighestVersion < D3D_ROOT_SIGNATURE_VERSION_1_1)
        return NULL;
    ZeroMemory(&desc, sizeof(desc));
    desc.Version = D3D_ROOT_SIGNATURE_VERSION_1_1;
    d1 = &desc.Desc_1_1;
    d1->NumParameters = b->param_count;
    d1->pParameters = b->params;
    d1->NumStaticSamplers = b->sampler_count;
    d1->pStaticSamplers = b->samplers;
    d1->Flags = is_compute ? D3D12_ROOT_SIGNATURE_FLAG_NONE
                           : D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT;
    hr = D3D12SerializeVersionedRootSignature(&desc, &serialized, &error_blob);
    if (FAILED(hr)) {
        if (error_blob != NULL) {
            LOG_ERROR("D3D12 root signature: %s",
                      (const char *)ID3D10Blob_GetBufferPointer(error_blob));
            ID3D10Blob_Release(error_blob);
        }
        return NULL;
    }
    if (error_blob != NULL) ID3D10Blob_Release(error_blob);
    hr = ID3D12Device_CreateRootSignature(
        ctx->device, 0u, ID3D10Blob_GetBufferPointer(serialized),
        ID3D10Blob_GetBufferSize(serialized), &IID_ID3D12RootSignature,
        (void **)&root_sig);
    ID3D10Blob_Release(serialized);
    if (FAILED(hr)) return NULL;
    return root_sig;
}

/* ---- PSO creation (RHIPipelineDesc -> D3D12 pipeline desc mapping) ---- */
static UINT rhi_d3d12_input_layout(const RHIPipelineDesc *desc,
                                   D3D12_INPUT_ELEMENT_DESC *elements,
                                   UINT *out_stride) {
    UINT stride = desc->vertex_stride;
    if (desc->no_vertex_input) {
        *out_stride = 0u;
        return 0u;
    }
    if (desc->font_vertex) {
        stride = 32u;
        elements[0] = (D3D12_INPUT_ELEMENT_DESC){ "POSITION", 0u, DXGI_FORMAT_R32G32_FLOAT, 0u, 0u, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0u };
        elements[1] = (D3D12_INPUT_ELEMENT_DESC){ "TEXCOORD", 0u, DXGI_FORMAT_R32G32_FLOAT, 0u, 8u, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0u };
        elements[2] = (D3D12_INPUT_ELEMENT_DESC){ "COLOR", 0u, DXGI_FORMAT_R32G32B32A32_FLOAT, 0u, 16u, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0u };
        *out_stride = stride;
        return 3u;
    }
    if (desc->skinned_vertex) {
        stride = 64u;
        elements[0] = (D3D12_INPUT_ELEMENT_DESC){ "POSITION", 0u, DXGI_FORMAT_R32G32B32_FLOAT, 0u, 0u, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0u };
        elements[1] = (D3D12_INPUT_ELEMENT_DESC){ "NORMAL", 0u, DXGI_FORMAT_R32G32B32_FLOAT, 0u, 12u, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0u };
        elements[2] = (D3D12_INPUT_ELEMENT_DESC){ "TEXCOORD", 0u, DXGI_FORMAT_R32G32_FLOAT, 0u, 24u, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0u };
        elements[3] = (D3D12_INPUT_ELEMENT_DESC){ "BLENDINDICES", 0u, DXGI_FORMAT_R32G32B32A32_UINT, 0u, 32u, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0u };
        elements[4] = (D3D12_INPUT_ELEMENT_DESC){ "BLENDWEIGHT", 0u, DXGI_FORMAT_R32G32B32A32_FLOAT, 0u, 48u, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0u };
        *out_stride = stride;
        return 5u;
    }
    if (desc->is_shadow_depth || stride == 12u) {
        /* Shadow-depth shaders consume position only; the binding stride
         * stays the mesh stride so the same VBOs bind unchanged. */
        if (stride == 0u) stride = 32u;
        elements[0] = (D3D12_INPUT_ELEMENT_DESC){ "POSITION", 0u, DXGI_FORMAT_R32G32B32_FLOAT, 0u, 0u, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0u };
        *out_stride = stride;
        return 1u;
    }
    if (stride == 0u) stride = 32u;
    elements[0] = (D3D12_INPUT_ELEMENT_DESC){ "POSITION", 0u, DXGI_FORMAT_R32G32B32_FLOAT, 0u, 0u, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0u };
    elements[1] = (D3D12_INPUT_ELEMENT_DESC){ "NORMAL", 0u, DXGI_FORMAT_R32G32B32_FLOAT, 0u, 12u, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0u };
    elements[2] = (D3D12_INPUT_ELEMENT_DESC){ "TEXCOORD", 0u, DXGI_FORMAT_R32G32_FLOAT, 0u, 24u, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0u };
    *out_stride = stride;
    return 3u;
}

static ID3D12PipelineState *rhi_d3d12_create_graphics_pso(
        RHI_D3D12Context *ctx, ID3D12RootSignature *root_sig,
        const D3D12_SHADER_BYTECODE *vs, const D3D12_SHADER_BYTECODE *ps,
        const RHIPipelineDesc *desc, UINT *out_stride,
        const DXGI_FORMAT *rtv_override, UINT rtv_override_count,
        UINT no_dsv) {
    D3D12_GRAPHICS_PIPELINE_STATE_DESC pso;
    D3D12_INPUT_ELEMENT_DESC elements[5];
    UINT rt_count;
    UINT i;
    ZeroMemory(&pso, sizeof(pso));
    pso.pRootSignature = root_sig;
    if (vs != NULL) pso.VS = *vs;
    if (ps != NULL) pso.PS = *ps;
    pso.InputLayout.NumElements = rhi_d3d12_input_layout(desc, elements, out_stride);
    pso.InputLayout.pInputElementDescs = elements;
    pso.RasterizerState.FillMode = desc->wireframe ? D3D12_FILL_MODE_WIREFRAME
                                                   : D3D12_FILL_MODE_SOLID;
    /* no_vertex_input also forces culling off, as on VK (cullMode NONE) and GL:
     * those pipelines are fullscreen triangles / generated geometry whose
     * winding the caller never chose, so a back-face cull can only ever drop
     * them. Without this the skybox and particle pipelines drew only because
     * their triangles happened to wind front-facing (R664). */
    pso.RasterizerState.CullMode =
        (desc->disable_culling || desc->no_vertex_input) ? D3D12_CULL_MODE_NONE
                                                          : D3D12_CULL_MODE_BACK;
    pso.RasterizerState.FrontCounterClockwise = FALSE;
    pso.RasterizerState.DepthClipEnable = TRUE;
    /* R445 parity with VK/GL: fullscreen blits (write-disable without
     * lequal compare) must not depth-test at all — the composite passes run
     * against a D32 attachment and LESS would discard the z=1.0 triangle. */
    pso.DepthStencilState.DepthEnable =
        (desc->depth_write_disable && !desc->depth_compare_lequal &&
         !desc->is_shadow_depth) ? FALSE : TRUE;
    pso.DepthStencilState.DepthFunc = desc->depth_compare_lequal
        ? D3D12_COMPARISON_FUNC_LESS_EQUAL : D3D12_COMPARISON_FUNC_LESS;
    pso.DepthStencilState.DepthWriteMask = desc->depth_write_disable
        ? D3D12_DEPTH_WRITE_MASK_ZERO : D3D12_DEPTH_WRITE_MASK_ALL;
    rt_count = desc->mrt_attachment_count > 1u ? desc->mrt_attachment_count : 1u;
    if (desc->is_shadow_depth) rt_count = 0u;
    if (rtv_override != NULL) rt_count = rtv_override_count;
    /* R650: per-target blend state only takes effect with
     * IndependentBlendEnable; without it D3D12 applies RenderTarget[0] to
     * every target, so alpha_blend_color_only blended the motion-vector RT1
     * as well (particles and water wrote a velocity mixed with the clear
     * value instead of their own). */
    pso.BlendState.IndependentBlendEnable =
        (desc->alpha_blend && desc->alpha_blend_color_only) ? TRUE : FALSE;
    for (i = 0u; i < 8u; ++i) {
        pso.BlendState.RenderTarget[i].RenderTargetWriteMask =
            D3D12_COLOR_WRITE_ENABLE_ALL;
        if (desc->alpha_blend &&
            (!desc->alpha_blend_color_only || i == 0u) && i < rt_count) {
            /* color_only keeps motion-vector MRT writes (RT1+) unblended. */
            pso.BlendState.RenderTarget[i].BlendEnable = TRUE;
            pso.BlendState.RenderTarget[i].SrcBlend = D3D12_BLEND_SRC_ALPHA;
            pso.BlendState.RenderTarget[i].DestBlend = D3D12_BLEND_INV_SRC_ALPHA;
            pso.BlendState.RenderTarget[i].BlendOp = D3D12_BLEND_OP_ADD;
            pso.BlendState.RenderTarget[i].SrcBlendAlpha = D3D12_BLEND_SRC_ALPHA;
            pso.BlendState.RenderTarget[i].DestBlendAlpha = D3D12_BLEND_INV_SRC_ALPHA;
            pso.BlendState.RenderTarget[i].BlendOpAlpha = D3D12_BLEND_OP_ADD;
        }
    }
    pso.NumRenderTargets = rt_count;
    if (rt_count > 0u) {
        for (i = 0u; i < rt_count; ++i) {
            RHIFormat f = desc->mrt_attachment_count > 1u
                ? desc->mrt_formats[i] : desc->color_format;
            pso.RTVFormats[i] = rtv_override != NULL ? rtv_override[i]
                                                     : rhi_d3d12_format(f);
            if (pso.RTVFormats[i] == DXGI_FORMAT_UNKNOWN) return NULL;
        }
    }
    /* R643: a pass with no depth attachment bound (the swapchain: frame
     * begin, FBO unbind) must use a PSO whose DSVFormat is UNKNOWN, with
     * depth testing off -- debug layer [615]. */
    pso.DSVFormat = no_dsv ? DXGI_FORMAT_UNKNOWN : DXGI_FORMAT_D32_FLOAT;
    if (no_dsv) {
        pso.DepthStencilState.DepthEnable = FALSE;
        pso.DepthStencilState.DepthWriteMask = D3D12_DEPTH_WRITE_MASK_ZERO;
    }
    pso.SampleDesc.Count = desc->sample_count == 0u ? 1u : desc->sample_count;
    pso.SampleMask = UINT_MAX;
    pso.PrimitiveTopologyType = desc->point_list
        ? D3D12_PRIMITIVE_TOPOLOGY_TYPE_POINT : D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
    {
        ID3D12PipelineState *result = NULL;
        HRESULT hr = ID3D12Device_CreateGraphicsPipelineState(
            ctx->device, &pso, &IID_ID3D12PipelineState, (void **)&result);
        return SUCCEEDED(hr) ? result : NULL;
    }
}

static ID3D12PipelineState *rhi_d3d12_create_compute_pso(
        RHI_D3D12Context *ctx, ID3D12RootSignature *root_sig,
        const D3D12_SHADER_BYTECODE *cs) {
    D3D12_COMPUTE_PIPELINE_STATE_DESC pso;
    ID3D12PipelineState *result = NULL;
    HRESULT hr;
    ZeroMemory(&pso, sizeof(pso));
    pso.pRootSignature = root_sig;
    pso.CS = *cs;
    hr = ID3D12Device_CreateComputePipelineState(
        ctx->device, &pso, &IID_ID3D12PipelineState, (void **)&result);
    return SUCCEEDED(hr) ? result : NULL;
}

RHIPipeline rhi_pipeline_create(RHIDevice *dev, const RHIPipelineDesc *desc) {
    RHI_D3D12Context *ctx;
    RHI_D3D12Pipeline *pd;
    RHI_D3D12RootSigBuilder builder;
    ShaderIOBinding bindings[32];   /* R654: deferred_light declares 19 */
    usize binding_count;
    D3D12_SHADER_BYTECODE vs_code;
    D3D12_SHADER_BYTECODE ps_code;
    u32 idx;
    if (dev == NULL || desc == NULL) return RHI_HANDLE_NULL;
    ctx = (RHI_D3D12Context *)dev->backend_data;
    if (ctx == NULL || ctx->device_lost) return RHI_HANDLE_NULL;
    if (desc->mrt_attachment_count > 1u &&
        !rhi_mrt_formats_valid(desc->mrt_formats, desc->mrt_attachment_count))
        return RHI_HANDLE_NULL;
    ZeroMemory(&builder, sizeof(builder));
    for (u32 i = 0u; i < RHI_D3D12_MAX_REGISTERS; ++i) {
        builder.image_root_params[i] = UINT_MAX;
        builder.uniform_root_params[i] = UINT_MAX;
        builder.storage_root_params[i] = UINT_MAX;
        builder.storage_strides[i] = UINT_MAX;
        builder.srv_buffer_strides[i] = UINT_MAX;
    }
    /* Push-constant contract: 128B compute / 256B graphics (VK parity); the
     * terrain/water/combined_* layout booleans select which HLSL root
     * constant block consumes these bytes (declared by Task 6's shaders);
     * they are retained in pd->desc for the uniform-location mapping. */
    builder.push_constant_size = desc->is_compute ? 128u : 256u;
    builder.clamp_samplers = (desc->is_compute || desc->no_vertex_input) ? 1u : 0u;
    ZeroMemory(&vs_code, sizeof(vs_code));
    ZeroMemory(&ps_code, sizeof(ps_code));
    if (desc->is_compute) {
        RHI_D3D12Shader *cs = (RHI_D3D12Shader *)rhi_get_resource_typed(
            dev, desc->frag, RHI_RES_SHADER); /* VK parity: CS rides .frag */
        if (cs == NULL || cs->blob == NULL) {
            LOG_WARN("D3D12: pipeline needs a compiled CS blob");
            return RHI_HANDLE_NULL;
        }
        binding_count = rhi_d3d12_reflect_hlsl(cs->source, cs->source_len,
                                               bindings, 32u);
        if (!rhi_d3d12_root_sig_from_bindings(&builder, bindings,
                                              binding_count))
            return RHI_HANDLE_NULL;
        pd = (RHI_D3D12Pipeline *)calloc(1u, sizeof(*pd));
        if (pd == NULL) return RHI_HANDLE_NULL;
        /* R636: same fail-closed marker/layout cross-check as the graphics
         * path. */
        if (!rhi_d3d12_hlsl_markers_match_layout(cs->source, cs->source_len)) {
            free(pd);
            return RHI_HANDLE_NULL;
        }
        rhi_d3d12_uniform_markers(cs->source, cs->source_len, pd->uniforms,
                                  &pd->uniform_count);
        pd->root_sig = rhi_d3d12_root_signature_create(ctx, &builder, 1u,
            &pd->push_param_index, &pd->push_size);
        if (pd->root_sig != NULL) {
            D3D12_SHADER_BYTECODE cs_code;
            cs_code.pShaderBytecode = cs->blob;
            cs_code.BytecodeLength = cs->blob_size;
            pd->pso = rhi_d3d12_create_compute_pso(ctx, pd->root_sig, &cs_code);
        }
        if (pd->pso == NULL) {
            rhi_d3d12_release((IUnknown **)&pd->root_sig);
            free(pd);
            return RHI_HANDLE_NULL;
        }
        pd->is_compute = 1u;
    } else {
        RHI_D3D12Shader *vs = (RHI_D3D12Shader *)rhi_get_resource_typed(
            dev, desc->vert, RHI_RES_SHADER);
        RHI_D3D12Shader *ps = (RHI_D3D12Shader *)rhi_get_resource_typed(
            dev, desc->frag, RHI_RES_SHADER);
        /* A shadow-depth pass legitimately has no pixel stage: the PSO is built
         * with zero render targets, so a pixel shader would have nothing to
         * write. GL and Metal both accept the null fragment handle here. */
        if (vs == NULL || vs->blob == NULL ||
            (!desc->is_shadow_depth && (ps == NULL || ps->blob == NULL))) {
            LOG_WARN("D3D12: pipeline needs compiled VS/PS blobs");
            return RHI_HANDLE_NULL;
        }
        binding_count = rhi_d3d12_reflect_hlsl(vs->source, vs->source_len,
                                               bindings, 32u);
        if (!rhi_d3d12_root_sig_add_bindings(&builder, bindings, binding_count,
                                             D3D12_SHADER_VISIBILITY_VERTEX))
            return RHI_HANDLE_NULL;
        if (ps != NULL) {
            binding_count = rhi_d3d12_reflect_hlsl(ps->source, ps->source_len,
                                                   bindings, 32u);
            if (!rhi_d3d12_root_sig_add_bindings(&builder, bindings,
                                                 binding_count,
                                                 D3D12_SHADER_VISIBILITY_PIXEL))
                return RHI_HANDLE_NULL;
        }
        vs_code.pShaderBytecode = vs->blob;
        vs_code.BytecodeLength = vs->blob_size;
        if (ps != NULL) {
            ps_code.pShaderBytecode = ps->blob;
            ps_code.BytecodeLength = ps->blob_size;
        }
        pd = (RHI_D3D12Pipeline *)calloc(1u, sizeof(*pd));
        if (pd == NULL) return RHI_HANDLE_NULL;
        /* R636: the published uniform offsets have to agree with the cbuffer
         * layout of the struct they name, or a write lands on the wrong
         * member and the shader reads a value nobody wrote. Fail closed: a
         * pipeline built on offsets nobody can vouch for is worse than no
         * pipeline. */
        if (!rhi_d3d12_hlsl_markers_match_layout(vs->source, vs->source_len) ||
            (ps != NULL &&
             !rhi_d3d12_hlsl_markers_match_layout(ps->source, ps->source_len))) {
            free(pd);
            return RHI_HANDLE_NULL;
        }
        rhi_d3d12_uniform_markers(vs->source, vs->source_len, pd->uniforms,
                                  &pd->uniform_count);
        if (ps != NULL)
            rhi_d3d12_uniform_markers(ps->source, ps->source_len, pd->uniforms,
                                      &pd->uniform_count);
        pd->root_sig = rhi_d3d12_root_signature_create(ctx, &builder, 0u,
            &pd->push_param_index, &pd->push_size);
        if (pd->root_sig != NULL)
            pd->pso = rhi_d3d12_create_graphics_pso(ctx, pd->root_sig,
                &vs_code, &ps_code, desc, &pd->vertex_stride, NULL, 0u, 0u);
        if (pd->pso == NULL) {
            rhi_d3d12_release((IUnknown **)&pd->root_sig);
            free(pd);
            return RHI_HANDLE_NULL;
        }
        if (!desc->is_shadow_depth) {
            UINT n = desc->mrt_attachment_count > 1u
                ? desc->mrt_attachment_count : 1u;
            for (UINT k = 0u; k < n; ++k)
                pd->rtv_formats[k] = rhi_d3d12_format(
                    desc->mrt_attachment_count > 1u ? desc->mrt_formats[k]
                                                    : desc->color_format);
            pd->rtv_count = n;
            pd->vs_blob = malloc(vs->blob_size);
            pd->ps_blob = ps != NULL ? malloc(ps->blob_size) : NULL;
            if (pd->vs_blob != NULL) {
                memcpy(pd->vs_blob, vs->blob, vs->blob_size);
                pd->vs_blob_size = vs->blob_size;
            }
            if (pd->ps_blob != NULL) {
                memcpy(pd->ps_blob, ps->blob, ps->blob_size);
                pd->ps_blob_size = ps->blob_size;
            }
        }
    }
    for (u32 i = 0u; i < RHI_D3D12_MAX_REGISTERS; ++i) {
        pd->image_root_params[i] = builder.image_root_params[i];
        pd->uniform_root_params[i] = builder.uniform_root_params[i];
        if (pd->image_root_params[i] != UINT_MAX &&
            pd->push_param_index != UINT_MAX)
            pd->image_root_params[i]++;
        if (pd->uniform_root_params[i] != UINT_MAX &&
            pd->push_param_index != UINT_MAX)
            pd->uniform_root_params[i]++;
        pd->storage_root_params[i] = builder.storage_root_params[i];
        pd->storage_strides[i] = builder.storage_strides[i];
        pd->srv_buffer_strides[i] = builder.srv_buffer_strides[i];
        if (pd->storage_root_params[i] != UINT_MAX &&
            pd->push_param_index != UINT_MAX)
            pd->storage_root_params[i]++;
    }
    pd->desc = *desc;
    pd->topology = desc->point_list ? D3D_PRIMITIVE_TOPOLOGY_POINTLIST
                                    : D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
    idx = rhi_alloc_slot(dev);
    dev->slots[idx].ptr = pd;
    dev->slots[idx].type = RHI_RES_PIPELINE;
    return rhi_make_handle(idx, dev->slots[idx].generation);
}
void rhi_pipeline_destroy(RHIDevice *dev, RHIPipeline pipe) {
    RHI_D3D12Pipeline *pd;
    if (dev == NULL) return;
    pd = (RHI_D3D12Pipeline *)rhi_get_resource_typed(dev, pipe, RHI_RES_PIPELINE);
    if (pd == NULL) return;
    {
        RHI_D3D12Context *dctx = (RHI_D3D12Context *)dev->backend_data;
        rhi_d3d12_release_deferred(dctx, (IUnknown **)&pd->pso);
        for (UINT k = 0u; k < pd->variant_count; ++k)
            rhi_d3d12_release_deferred(dctx, (IUnknown **)&pd->variants[k].pso);
        rhi_d3d12_release_deferred(dctx, (IUnknown **)&pd->root_sig);
    }
    free(pd->vs_blob);
    free(pd->ps_blob);
    free(pd);
    rhi_free_slot(dev, pipe);
}

/* ---- textures (Task 5) ----
 * Committed DEFAULT-heap textures; initial data uploads through an
 * UPLOAD-heap staging buffer + CopyTextureRegion (footprints from
 * GetCopyableFootprints, pitch aligned); readback goes through a
 * READBACK-heap buffer + Map/memcpy/Unmap. Byte semantics follow the
 * format's native layout (rhi.h:281-285). */
static D3D12_RESOURCE_STATES rhi_d3d12_texture_final_state(RHIFormat format) {
    return format == RHI_FORMAT_D32_FLOAT
        ? D3D12_RESOURCE_STATE_DEPTH_WRITE
        : (D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE |
           D3D12_RESOURCE_STATE_NON_PIXEL_SHADER_RESOURCE);
}

/* depth_samplable asks for the typeless alias pair: the resource is allocated
 * R32_TYPELESS so a D32_FLOAT depth-stencil view and an R32_FLOAT
 * shader resource view can both address the same bytes. Only the shadow atlas
 * needs it; every other depth target stays unsamplable D32_FLOAT, which is
 * exactly what it is today.
 * R441: array_size is the resource's slice count (D3D12's DepthOrArraySize);
 * 0 and 1 both mean an ordinary 2D texture and are the only values any
 * non-array caller passes. */
static RHITexture rhi_d3d12_texture_create_ex(RHIDevice *dev,
                                              const RHITextureDesc *desc,
                                              int depth_samplable,
                                              u32 array_size) {
    RHI_D3D12Context *ctx;
    RHI_D3D12Texture *td;
    D3D12_HEAP_PROPERTIES properties;
    D3D12_RESOURCE_DESC description;
    D3D12_RESOURCE_STATES initial_state;
    D3D12_CLEAR_VALUE clear_value;
    D3D12_CLEAR_VALUE *clear_ptr = NULL;
    DXGI_FORMAT dxgi_format;
    DXGI_FORMAT alloc_format;
    HRESULT hr;
    u32 idx;
    if (dev == NULL || !rhi_texture_desc_validate(desc)) return RHI_HANDLE_NULL;
    ctx = (RHI_D3D12Context *)dev->backend_data;
    if (ctx == NULL || ctx->device_lost) return RHI_HANDLE_NULL;
    dxgi_format = rhi_d3d12_format(desc->format);
    if (dxgi_format == DXGI_FORMAT_UNKNOWN) return RHI_HANDLE_NULL;
    if (depth_samplable && desc->format != RHI_FORMAT_D32_FLOAT)
        return RHI_HANDLE_NULL;
    alloc_format = (depth_samplable && desc->format == RHI_FORMAT_D32_FLOAT)
        ? DXGI_FORMAT_R32_TYPELESS : dxgi_format;
    ZeroMemory(&properties, sizeof(properties));
    properties.Type = D3D12_HEAP_TYPE_DEFAULT;
    properties.CreationNodeMask = 1u;
    properties.VisibleNodeMask = 1u;
    ZeroMemory(&description, sizeof(description));
    description.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D;
    description.Width = desc->width;
    description.Height = desc->height;
    description.DepthOrArraySize = (UINT)(array_size > 0u ? array_size : 1u);
    description.MipLevels = (UINT16)(desc->mip_levels == 0u ? 1u : desc->mip_levels);
    description.Format = alloc_format;
    description.SampleDesc.Count = 1u;
    /* R648: a texture with initial data is created in COMMON and moved to
     * COPY_DEST by an explicit barrier on the upload list, rather than being
     * created in COPY_DEST. Created in COPY_DEST, the first draw sampling
     * such a texture intermittently tripped GPU-based validation [1358]
     * ("Incompatible texture barrier layout ... LEGACY_COPY_DEST") on the
     * RTX driver even though the upload list's COPY_DEST -> shader-read
     * barrier had already executed and been waited on. WARP never showed it.
     * See docs/Implementation_Status.md R648 for the run counts. */
    initial_state = desc->data != NULL ? D3D12_RESOURCE_STATE_COMMON
                                       : rhi_d3d12_texture_final_state(desc->format);
    if (desc->format == RHI_FORMAT_D32_FLOAT) {
        description.Flags |= D3D12_RESOURCE_FLAG_ALLOW_DEPTH_STENCIL;
        ZeroMemory(&clear_value, sizeof(clear_value));
        /* The clear value names the depth-stencil aspect, which is D32_FLOAT
         * even when the resource itself was allocated typeless. */
        clear_value.Format = dxgi_format;
        clear_value.DepthStencil.Depth = 1.0f;
        clear_ptr = &clear_value;
    } else {
        description.Flags |= D3D12_RESOURCE_FLAG_ALLOW_RENDER_TARGET;
        /* R653: R32_FLOAT is the compute-written format (the Hi-Z pyramid,
         * written through rhi_cmd_bind_image_texture), so it may also back
         * a UAV. R654: so may RGBA16F -- the IBL BRDF LUT and cubemaps are
         * written by compute too. */
        if (desc->format == RHI_FORMAT_R32_FLOAT ||
            desc->format == RHI_FORMAT_R16G16B16A16_SFLOAT)
            description.Flags |= D3D12_RESOURCE_FLAG_ALLOW_UNORDERED_ACCESS;
    }
    td = (RHI_D3D12Texture *)calloc(1u, sizeof(*td));
    if (td == NULL) return RHI_HANDLE_NULL;
    hr = ID3D12Device_CreateCommittedResource(
        ctx->device, &properties, D3D12_HEAP_FLAG_NONE, &description,
        initial_state, clear_ptr, &IID_ID3D12Resource, (void **)&td->resource);
    if (FAILED(hr)) {
        free(td);
        return RHI_HANDLE_NULL;
    }
#if defined(ENGINE_D3D12_DEBUG)
    {
        static unsigned s_tex_serial;
        wchar_t wname[96];
        swprintf(wname, 96, L"tex#%u %ux%ux%u fmt%u data%d frame%llu",
                 ++s_tex_serial, (unsigned)desc->width, (unsigned)desc->height,
                 (unsigned)description.DepthOrArraySize, (unsigned)desc->format,
                 desc->data != NULL, (unsigned long long)ctx->debug_frame);
        ID3D12Object_SetName((ID3D12Object *)td->resource, wname);
    }
#endif
    td->dxgi_format = alloc_format;
    td->srv_format = depth_samplable ? DXGI_FORMAT_R32_FLOAT
                                     : DXGI_FORMAT_UNKNOWN;
    td->rhi_format = (UINT)desc->format;    td->width = desc->width;
    td->height = desc->height;
    td->mip_levels = description.MipLevels;
    td->array_size = description.DepthOrArraySize;
    td->state = initial_state;
    if (desc->data != NULL) {
        /* Tightly packed native-layout texels for mip 0. */
        UINT bpp = rhi_d3d12_format_bytes_per_pixel(desc->format);
        UINT64 row_bytes = (UINT64)desc->width * bpp;
        D3D12_PLACED_SUBRESOURCE_FOOTPRINT footprint;
        UINT num_rows;
        UINT64 row_size;
        UINT64 total_size;
        ID3D12Resource *staging;
        void *mapped = NULL;
        RHIResult rr = RHI_RESULT_ERROR;
        ID3D12Device_GetCopyableFootprints(ctx->device, &description, 0u, 1u,
            0u, &footprint, &num_rows, &row_size, &total_size);
        staging = rhi_d3d12_staging_buffer(ctx, D3D12_HEAP_TYPE_UPLOAD, total_size);
        if (staging != NULL &&
            SUCCEEDED(ID3D12Resource_Map(staging, 0u, NULL, &mapped))) {
            UINT r;
            const u8 *src = (const u8 *)desc->data;
            u8 *dst = (u8 *)mapped + footprint.Offset;
            for (r = 0u; r < num_rows; ++r)
                memcpy(dst + (UINT64)r * footprint.Footprint.RowPitch,
                       src + (UINT64)r * row_bytes, (size_t)row_bytes);
            ID3D12Resource_Unmap(staging, 0u, NULL);
            if (SUCCEEDED(rhi_d3d12_oneshot_begin(ctx))) {
                D3D12_TEXTURE_COPY_LOCATION dst_loc;
                D3D12_TEXTURE_COPY_LOCATION src_loc;
                ZeroMemory(&dst_loc, sizeof(dst_loc));
                dst_loc.pResource = td->resource;
                dst_loc.Type = D3D12_TEXTURE_COPY_TYPE_SUBRESOURCE_INDEX;
                dst_loc.SubresourceIndex = 0u;
                ZeroMemory(&src_loc, sizeof(src_loc));
                src_loc.pResource = staging;
                src_loc.Type = D3D12_TEXTURE_COPY_TYPE_PLACED_FOOTPRINT;
                src_loc.PlacedFootprint = footprint;
                rhi_d3d12_transition(ctx->upload_list, td->resource,
                    D3D12_RESOURCE_STATE_COMMON, D3D12_RESOURCE_STATE_COPY_DEST);
                ID3D12GraphicsCommandList_CopyTextureRegion(
                    ctx->upload_list, &dst_loc, 0u, 0u, 0u, &src_loc, NULL);
                rhi_d3d12_transition(ctx->upload_list, td->resource,
                    D3D12_RESOURCE_STATE_COPY_DEST,
                    rhi_d3d12_texture_final_state(desc->format));
                rr = rhi_d3d12_oneshot_flush(ctx);
            }
        }
        if (staging != NULL) ID3D12Resource_Release(staging);
        if (rr != RHI_RESULT_OK) {
            ID3D12Resource_Release(td->resource);
            free(td);
            return RHI_HANDLE_NULL;
        }
        td->state = rhi_d3d12_texture_final_state(desc->format);
    }
    idx = rhi_alloc_slot(dev);
    dev->slots[idx].ptr = td;
    dev->slots[idx].type = RHI_RES_TEXTURE;
    return rhi_make_handle(idx, dev->slots[idx].generation);
}
RHITexture rhi_texture_create(RHIDevice *dev, const RHITextureDesc *desc) {
    return rhi_d3d12_texture_create_ex(dev, desc, 0, 0u);
}
void rhi_texture_destroy(RHIDevice *dev, RHITexture tex) {
    RHI_D3D12Texture *td;
    if (dev == NULL) return;
    td = (RHI_D3D12Texture *)rhi_get_resource_typed(dev, tex, RHI_RES_TEXTURE);
    if (td == NULL) return;
    {
        RHI_D3D12Context *ctx = (RHI_D3D12Context *)dev->backend_data;
        UINT i;
        if (ctx != NULL)
            for (i = 0u; i < RHI_D3D12_MAX_REGISTERS; ++i)
                if (ctx->live_srv[i] == td) ctx->live_srv[i] = NULL;
    }
    rhi_d3d12_release_deferred((RHI_D3D12Context *)dev->backend_data,
                               (IUnknown **)&td->resource);
    free(td);
    rhi_free_slot(dev, tex);
}
/* R441: 2D texture array — one mip, RGBA8/BGRA8 only (material albedo
 * packing). The D3D12 shape is the ordinary TEXTURE2D resource description
 * with DepthOrArraySize = layers and no separate "array" resource dimension:
 * D3D12 spells GL_TEXTURE_2D_ARRAY / VkImageView 2D-array as slices of a
 * TEXTURE2D, and the SRV view dimension (not the resource) is what tells the
 * shader the slices are addressable. The validation mirror is the GL
 * backend's rhi_texture_array_create so a bad request is refused identically
 * on both. */
RHITexture rhi_texture_array_create(RHIDevice *dev, u32 width, u32 height,
                                    u32 layers, RHIFormat fmt) {
    RHITextureDesc td;
    if (dev == NULL || width == 0u || height == 0u || layers == 0u ||
        width > RHI_MAX_DRAWABLE_DIMENSION ||
        height > RHI_MAX_DRAWABLE_DIMENSION ||
        layers > RHI_MAX_TEXTURE_ARRAY_LAYERS) return RHI_HANDLE_NULL;
    if (fmt != RHI_FORMAT_R8G8B8A8_UNORM && fmt != RHI_FORMAT_B8G8R8A8_UNORM) {
        LOG_WARN("D3D12: texture array only supports 8-bit RGBA formats");
        return RHI_HANDLE_NULL;
    }
    memset(&td, 0, sizeof(td));
    td.width = width;
    td.height = height;
    td.format = fmt;
    td.mip_levels = 1u;
    td.data = NULL;
    return rhi_d3d12_texture_create_ex(dev, &td, 0, layers);
}
void rhi_texture_array_upload_layer(RHIDevice *dev, RHITexture tex, u32 layer,
                                    const void *rgba8, usize size) {
    RHI_D3D12Context *ctx;
    RHI_D3D12Texture *td;
    D3D12_RESOURCE_DESC description;
    D3D12_PLACED_SUBRESOURCE_FOOTPRINT footprint;
    UINT num_rows;
    UINT64 row_size;
    UINT64 total_size;
    UINT64 row_bytes;
    UINT bpp;
    UINT r;
    ID3D12Resource *staging;
    void *mapped = NULL;
    RHIResult rr = RHI_RESULT_ERROR;
    if (dev == NULL || rgba8 == NULL) return;
    ctx = (RHI_D3D12Context *)dev->backend_data;
    td = (RHI_D3D12Texture *)rhi_get_resource_typed(dev, tex, RHI_RES_TEXTURE);
    if (ctx == NULL || ctx->device_lost || td == NULL || td->resource == NULL)
        return;
    if (td->array_size <= 1u || layer >= td->array_size) return;
    bpp = rhi_d3d12_format_bytes_per_pixel((RHIFormat)td->rhi_format);
    if (bpp == 0u) return;
    row_bytes = (UINT64)td->width * bpp;
    /* Same host-OOB guard class as GL's copy (rhi.h:R441) — the copy reads
     * w*h*bpp bytes and must never run off the caller's buffer. */
    if (size < (usize)row_bytes * td->height) return;
    /* One slice is subresource `layer` of a mip-0 chain; the footprint the
     * copy needs is exactly what GetCopyableFootprints reports for that single
     * subresource, so the staging buffer is one slice, not the whole array. */
    ZeroMemory(&description, sizeof(description));
    description.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D;
    description.Width = td->width;
    description.Height = td->height;
    description.DepthOrArraySize = td->array_size;
    description.MipLevels = td->mip_levels;
    description.Format = td->dxgi_format;
    description.SampleDesc.Count = 1u;
    ID3D12Device_GetCopyableFootprints(ctx->device, &description, layer, 1u, 0u,
                                       &footprint, &num_rows, &row_size,
                                       &total_size);
    staging = rhi_d3d12_staging_buffer(ctx, D3D12_HEAP_TYPE_UPLOAD, total_size);
    if (staging != NULL &&
        SUCCEEDED(ID3D12Resource_Map(staging, 0u, NULL, &mapped))) {
        const u8 *src = (const u8 *)rgba8;
        u8 *dst = (u8 *)mapped + footprint.Offset;
        for (r = 0u; r < num_rows; ++r)
            memcpy(dst + (UINT64)r * footprint.Footprint.RowPitch,
                   src + (UINT64)r * row_bytes, (size_t)row_bytes);
        ID3D12Resource_Unmap(staging, 0u, NULL);
        if (SUCCEEDED(rhi_d3d12_oneshot_begin(ctx))) {
            D3D12_TEXTURE_COPY_LOCATION dst_loc;
            D3D12_TEXTURE_COPY_LOCATION src_loc;
            D3D12_RESOURCE_STATES after =
                rhi_d3d12_texture_final_state((RHIFormat)td->rhi_format);
            ZeroMemory(&dst_loc, sizeof(dst_loc));
            dst_loc.pResource = td->resource;
            dst_loc.Type = D3D12_TEXTURE_COPY_TYPE_SUBRESOURCE_INDEX;
            dst_loc.SubresourceIndex = layer;
            ZeroMemory(&src_loc, sizeof(src_loc));
            src_loc.pResource = staging;
            src_loc.Type = D3D12_TEXTURE_COPY_TYPE_PLACED_FOOTPRINT;
            src_loc.PlacedFootprint = footprint;
            /* The resource is already in its shader-read state (create
             * allocated it there and nothing has bound it yet at bake time),
             * so the slice copy has to walk it through COPY_DEST and back —
             * the same two transitions rhi_texture_create does. */
            rhi_d3d12_transition(ctx->upload_list, td->resource, td->state,
                                 D3D12_RESOURCE_STATE_COPY_DEST);
            ID3D12GraphicsCommandList_CopyTextureRegion(
                ctx->upload_list, &dst_loc, 0u, 0u, 0u, &src_loc, NULL);
            rhi_d3d12_transition(ctx->upload_list, td->resource,
                                 D3D12_RESOURCE_STATE_COPY_DEST, after);
            td->state = after;
            rr = rhi_d3d12_oneshot_flush(ctx);
        }
    }
    if (staging != NULL) ID3D12Resource_Release(staging);
    if (rr != RHI_RESULT_OK)
        LOG_WARN("D3D12: texture array layer %u upload failed", (unsigned)layer);
}
bool rhi_texture_get_size(RHIDevice *dev, RHITexture tex, u32 *out_w,
                          u32 *out_h) {
    RHI_D3D12Texture *td;
    if (dev == NULL || out_w == NULL || out_h == NULL) return false;
    td = (RHI_D3D12Texture *)rhi_get_resource_typed(dev, tex, RHI_RES_TEXTURE);
    if (td == NULL) return false;
    *out_w = td->width;
    *out_h = td->height;
    return true;
}
/* R654: one subresource (slice * mips + mip) to tightly packed rows. */
static bool rhi_d3d12_read_subresource(RHI_D3D12Context *ctx,
                                       RHI_D3D12Texture *td, UINT sub,
                                       u8 *dst) {
    D3D12_RESOURCE_DESC description;
    D3D12_PLACED_SUBRESOURCE_FOOTPRINT footprint;
    D3D12_TEXTURE_COPY_LOCATION src_loc, dst_loc;
    UINT num_rows, r;
    UINT64 row_size, total_size, row_bytes;
    ID3D12Resource *staging;
    void *mapped = NULL;
    D3D12_RANGE read_range;
    UINT mip = sub % td->mip_levels;
    UINT w = td->width >> mip, h = td->height >> mip;
    if (w == 0u) w = 1u;
    if (h == 0u) h = 1u;
    row_bytes = (UINT64)w * rhi_d3d12_format_bytes_per_pixel((RHIFormat)td->rhi_format);
    ID3D12Resource_GetDesc(td->resource, &description);
    ID3D12Device_GetCopyableFootprints(ctx->device, &description, sub, 1u, 0u,
        &footprint, &num_rows, &row_size, &total_size);
    staging = rhi_d3d12_staging_buffer(ctx, D3D12_HEAP_TYPE_READBACK, total_size);
    if (staging == NULL) return false;
    if (FAILED(rhi_d3d12_oneshot_begin(ctx))) {
        ID3D12Resource_Release(staging);
        return false;
    }
    rhi_d3d12_transition(ctx->upload_list, td->resource, td->state,
                         D3D12_RESOURCE_STATE_COPY_SOURCE);
    ZeroMemory(&src_loc, sizeof(src_loc));
    src_loc.pResource = td->resource;
    src_loc.Type = D3D12_TEXTURE_COPY_TYPE_SUBRESOURCE_INDEX;
    src_loc.SubresourceIndex = sub;
    ZeroMemory(&dst_loc, sizeof(dst_loc));
    dst_loc.pResource = staging;
    dst_loc.Type = D3D12_TEXTURE_COPY_TYPE_PLACED_FOOTPRINT;
    dst_loc.PlacedFootprint = footprint;
    ID3D12GraphicsCommandList_CopyTextureRegion(ctx->upload_list, &dst_loc,
                                                0u, 0u, 0u, &src_loc, NULL);
    rhi_d3d12_transition(ctx->upload_list, td->resource,
                         D3D12_RESOURCE_STATE_COPY_SOURCE, td->state);
    if (rhi_d3d12_oneshot_flush(ctx) != RHI_RESULT_OK) {
        ID3D12Resource_Release(staging);
        return false;
    }
    read_range.Begin = 0u;
    read_range.End = (SIZE_T)total_size;
    if (FAILED(ID3D12Resource_Map(staging, 0u, &read_range, &mapped))) {
        ID3D12Resource_Release(staging);
        return false;
    }
    for (r = 0u; r < num_rows; ++r)
        memcpy(dst + (UINT64)r * row_bytes,
               (const u8 *)mapped + footprint.Offset +
                   (UINT64)r * footprint.Footprint.RowPitch,
               (size_t)row_bytes);
    ID3D12Resource_Unmap(staging, 0u, NULL);
    ID3D12Resource_Release(staging);
    return true;
}
/* R654 test hook (not RHI API): read one face/mip of a colour cube, so the
 * WARP suite can check the IBL prefilter chain below mip 0. */
bool rhi_d3d12_cube_read_face(RHIDevice *dev, RHICubemap cm, u32 face,
                              u32 mip, void *dst) {
    RHI_D3D12Context *ctx;
    RHI_D3D12Texture *td;
    if (dev == NULL || dst == NULL || face >= 6u) return false;
    ctx = (RHI_D3D12Context *)dev->backend_data;
    if (ctx == NULL || ctx->device_lost) return false;
    td = (RHI_D3D12Texture *)rhi_get_resource_typed(dev, cm, RHI_RES_CUBEMAP);
    if (td == NULL || td->mip_split || mip >= td->mip_levels) return false;
    return rhi_d3d12_read_subresource(ctx, td, face * td->mip_levels + mip,
                                      (u8 *)dst);
}
bool rhi_texture_read_pixels(RHIDevice *dev, RHITexture tex, void *dst_rgba8,
                             usize size) {
    RHI_D3D12Context *ctx;
    RHI_D3D12Texture *td;
    D3D12_RESOURCE_DESC description;
    D3D12_PLACED_SUBRESOURCE_FOOTPRINT footprint;
    UINT bpp;
    UINT num_rows;
    UINT64 row_size;
    UINT64 total_size;
    UINT64 data_size;
    ID3D12Resource *staging;
    void *mapped = NULL;
    RHIResult rr;
    if (dev == NULL || dst_rgba8 == NULL) return false;
    ctx = (RHI_D3D12Context *)dev->backend_data;
    if (ctx == NULL || ctx->device_lost) return false;
    td = (RHI_D3D12Texture *)rhi_get_resource_typed(dev, tex, RHI_RES_TEXTURE);
    /* R654: a colour cube (RHI_RES_CUBEMAP) reads back all six faces at
     * mip 0, face-major, in native bytes (rhi.h R624). */
    if (td == NULL) {
        RHI_D3D12Texture *cube = (RHI_D3D12Texture *)rhi_get_resource_typed(
            dev, tex, RHI_RES_CUBEMAP);
        UINT64 face_bytes;
        u32 f;
        bool ok = true;
        if (cube == NULL || cube->mip_split) return false;
        face_bytes = (UINT64)cube->width * cube->height *
                     rhi_d3d12_format_bytes_per_pixel((RHIFormat)cube->rhi_format);
        if (size < (usize)(face_bytes * 6u)) return false;
        for (f = 0u; f < 6u && ok; ++f)
            ok = rhi_d3d12_read_subresource(ctx, cube, f * cube->mip_levels,
                                            (u8 *)dst_rgba8 + face_bytes * f);
        return ok;
    }
    if (td->mip_split) {
        LOG_WARN("D3D12: read_pixels on a texture with per-mip states pending");
        return false;
    }
    bpp = rhi_d3d12_format_bytes_per_pixel((RHIFormat)td->rhi_format);
    data_size = (UINT64)td->width * td->height * bpp;
    if (size < (usize)data_size) return false;
    ID3D12Resource_GetDesc(td->resource, &description);
    ID3D12Device_GetCopyableFootprints(ctx->device, &description, 0u, 1u, 0u,
        &footprint, &num_rows, &row_size, &total_size);
    staging = rhi_d3d12_staging_buffer(ctx, D3D12_HEAP_TYPE_READBACK, total_size);
    if (staging == NULL) return false;
    if (FAILED(rhi_d3d12_oneshot_begin(ctx))) {
        ID3D12Resource_Release(staging);
        return false;
    }
    rhi_d3d12_transition(ctx->upload_list, td->resource, td->state,
                         D3D12_RESOURCE_STATE_COPY_SOURCE);
    {
        D3D12_TEXTURE_COPY_LOCATION src_loc;
        D3D12_TEXTURE_COPY_LOCATION dst_loc;
        ZeroMemory(&src_loc, sizeof(src_loc));
        src_loc.pResource = td->resource;
        src_loc.Type = D3D12_TEXTURE_COPY_TYPE_SUBRESOURCE_INDEX;
        src_loc.SubresourceIndex = 0u;
        ZeroMemory(&dst_loc, sizeof(dst_loc));
        dst_loc.pResource = staging;
        dst_loc.Type = D3D12_TEXTURE_COPY_TYPE_PLACED_FOOTPRINT;
        dst_loc.PlacedFootprint = footprint;
        ID3D12GraphicsCommandList_CopyTextureRegion(ctx->upload_list,
            &dst_loc, 0u, 0u, 0u, &src_loc, NULL);
    }
    rhi_d3d12_transition(ctx->upload_list, td->resource,
                         D3D12_RESOURCE_STATE_COPY_SOURCE, td->state);
    rr = rhi_d3d12_oneshot_flush(ctx);
    if (rr != RHI_RESULT_OK) {
        ID3D12Resource_Release(staging);
        return false;
    }
    {
        D3D12_RANGE read_range;
        UINT r;
        const u8 *src;
        u8 *dst = (u8 *)dst_rgba8;
        UINT64 row_bytes = (UINT64)td->width * bpp;
        read_range.Begin = 0u;
        read_range.End = (SIZE_T)total_size;
        if (FAILED(ID3D12Resource_Map(staging, 0u, &read_range, &mapped))) {
            ID3D12Resource_Release(staging);
            return false;
        }
        src = (const u8 *)mapped + footprint.Offset;
        for (r = 0u; r < num_rows; ++r)
            memcpy(dst + (UINT64)r * row_bytes,
                   src + (UINT64)r * footprint.Footprint.RowPitch,
                   (size_t)row_bytes);
        ID3D12Resource_Unmap(staging, 0u, NULL);
    }
    ID3D12Resource_Release(staging);
    return true;
}
void rhi_texture_upload_mip(RHIDevice *dev, RHITexture tex, u32 mip_level,
                            u32 width, u32 height, const void *data,
                            usize size) {
    RHI_D3D12Context *ctx;
    RHI_D3D12Texture *td;
    D3D12_RESOURCE_DESC description;
    D3D12_PLACED_SUBRESOURCE_FOOTPRINT footprint;
    UINT bpp;
    UINT num_rows;
    UINT64 row_size;
    UINT64 total_size;
    UINT64 row_bytes;
    ID3D12Resource *staging;
    void *mapped = NULL;
    if (dev == NULL || data == NULL || size == 0u) return;
    ctx = (RHI_D3D12Context *)dev->backend_data;
    if (ctx == NULL || ctx->device_lost) return;
    td = (RHI_D3D12Texture *)rhi_get_resource_typed(dev, tex, RHI_RES_TEXTURE);
    if (td == NULL || mip_level >= td->mip_levels) return;
    bpp = rhi_d3d12_format_bytes_per_pixel((RHIFormat)td->rhi_format);
    row_bytes = (UINT64)width * bpp;
    if (size < (usize)(row_bytes * height)) return;
    ID3D12Resource_GetDesc(td->resource, &description);
    ID3D12Device_GetCopyableFootprints(ctx->device, &description, mip_level,
        1u, 0u, &footprint, &num_rows, &row_size, &total_size);
    staging = rhi_d3d12_staging_buffer(ctx, D3D12_HEAP_TYPE_UPLOAD, total_size);
    if (staging == NULL) return;
    if (FAILED(ID3D12Resource_Map(staging, 0u, NULL, &mapped))) {
        ID3D12Resource_Release(staging);
        return;
    }
    {
        UINT r;
        const u8 *src = (const u8 *)data;
        u8 *dst = (u8 *)mapped + footprint.Offset;
        for (r = 0u; r < num_rows; ++r)
            memcpy(dst + (UINT64)r * footprint.Footprint.RowPitch,
                   src + (UINT64)r * row_bytes, (size_t)row_bytes);
    }
    ID3D12Resource_Unmap(staging, 0u, NULL);
    if (SUCCEEDED(rhi_d3d12_oneshot_begin(ctx))) {
        D3D12_TEXTURE_COPY_LOCATION dst_loc;
        D3D12_TEXTURE_COPY_LOCATION src_loc;
        ZeroMemory(&dst_loc, sizeof(dst_loc));
        dst_loc.pResource = td->resource;
        dst_loc.Type = D3D12_TEXTURE_COPY_TYPE_SUBRESOURCE_INDEX;
        dst_loc.SubresourceIndex = mip_level;
        ZeroMemory(&src_loc, sizeof(src_loc));
        src_loc.pResource = staging;
        src_loc.Type = D3D12_TEXTURE_COPY_TYPE_PLACED_FOOTPRINT;
        src_loc.PlacedFootprint = footprint;
        rhi_d3d12_transition(ctx->upload_list, td->resource, td->state,
                             D3D12_RESOURCE_STATE_COPY_DEST);
        ID3D12GraphicsCommandList_CopyTextureRegion(ctx->upload_list,
            &dst_loc, 0u, 0u, 0u, &src_loc, NULL);
        rhi_d3d12_transition(ctx->upload_list, td->resource,
                             D3D12_RESOURCE_STATE_COPY_DEST, td->state);
        (void)rhi_d3d12_oneshot_flush(ctx);
    }
    ID3D12Resource_Release(staging);
}
RHISampler rhi_sampler_create(RHIDevice *dev, const RHISamplerDesc *desc) {
    RHI_D3D12Context *ctx;
    RHI_D3D12Sampler *smp;
    D3D12_SAMPLER_DESC sd;
    UINT slot;
    u32 idx;
    if (dev == NULL || desc == NULL) return RHI_HANDLE_NULL;
    ctx = (RHI_D3D12Context *)dev->backend_data;
    if (ctx == NULL || ctx->device_lost) return RHI_HANDLE_NULL;
    slot = rhi_d3d12_descriptor_take(ctx, &ctx->sampler_alloc);
    if (slot == UINT_MAX) return RHI_HANDLE_NULL;
    ZeroMemory(&sd, sizeof(sd));
    if (desc->min_filter == RHI_FILTER_NEAREST &&
        desc->mag_filter == RHI_FILTER_NEAREST)
        sd.Filter = D3D12_FILTER_MIN_MAG_MIP_POINT;
    else if (desc->min_filter == RHI_FILTER_LINEAR &&
             desc->mag_filter == RHI_FILTER_LINEAR)
        sd.Filter = D3D12_FILTER_MIN_MAG_MIP_LINEAR;
    else if (desc->min_filter == RHI_FILTER_LINEAR)
        sd.Filter = D3D12_FILTER_MIN_LINEAR_MAG_MIP_POINT;
    else
        sd.Filter = D3D12_FILTER_MIN_POINT_MAG_MIP_LINEAR;
    sd.AddressU = desc->wrap_u == RHI_WRAP_REPEAT ? D3D12_TEXTURE_ADDRESS_MODE_WRAP
                                                  : D3D12_TEXTURE_ADDRESS_MODE_CLAMP;
    sd.AddressV = desc->wrap_v == RHI_WRAP_REPEAT ? D3D12_TEXTURE_ADDRESS_MODE_WRAP
                                                  : D3D12_TEXTURE_ADDRESS_MODE_CLAMP;
    sd.AddressW = desc->wrap_w == RHI_WRAP_REPEAT ? D3D12_TEXTURE_ADDRESS_MODE_WRAP
                                                  : D3D12_TEXTURE_ADDRESS_MODE_CLAMP;
    sd.MaxLOD = D3D12_FLOAT32_MAX;
    ID3D12Device_CreateSampler(ctx->device, &sd,
        rhi_d3d12_descriptor_cpu(&ctx->sampler_alloc, slot));
    smp = (RHI_D3D12Sampler *)calloc(1u, sizeof(*smp));
    if (smp == NULL) {
        rhi_d3d12_descriptor_give_back(&ctx->sampler_alloc, slot, 0u);
        return RHI_HANDLE_NULL;
    }
    smp->slot = slot;
    idx = rhi_alloc_slot(dev);
    dev->slots[idx].ptr = smp;
    dev->slots[idx].type = RHI_RES_SAMPLER;
    return rhi_make_handle(idx, dev->slots[idx].generation);
}
void rhi_sampler_destroy(RHIDevice *dev, RHISampler sampler) {
    RHI_D3D12Context *ctx;
    RHI_D3D12Sampler *smp;
    if (dev == NULL) return;
    ctx = (RHI_D3D12Context *)dev->backend_data;
    smp = (RHI_D3D12Sampler *)rhi_get_resource_typed(dev, sampler, RHI_RES_SAMPLER);
    if (smp == NULL) return;
    if (ctx != NULL && ctx->sampler_alloc.free_slots != NULL)
        rhi_d3d12_descriptor_give_back(&ctx->sampler_alloc, smp->slot,
                                       rhi_d3d12_retire_fence(ctx));
    free(smp);
    rhi_free_slot(dev, sampler);
}

/* ---- command recording (Task 5: draw & dispatch family) ----
 * RHICmdBuffer on this backend is the context pointer (see rhi_frame_begin);
 * the recording list is the current frame slot's command list. State cmds
 * before a successful frame begin are dropped quietly (GL/VK parity). */
static ID3D12GraphicsCommandList *rhi_d3d12_cmd_list(RHI_D3D12Context *ctx) {
    if (ctx == NULL || !ctx->frame_started) return NULL;
    return ctx->command_lists[ctx->frame_parity & 1u];
}

/* Task 6: flush the legacy set_uniform_* staging buffer as root constants
 * before the next draw/dispatch (VK flush-at-draw parity, rhi.h:586-595).
 * Root-constant writes are 4-byte granular, so the dirty byte range widens
 * to DWORD alignment; every staged write was already validated against the
 * pipeline's declared (clamped) push range via rhi_push_helper_range_ok. */
/* R643: select the PSO whose render-target formats (and depth slot) match
 * what is bound now
 * (see RHI_D3D12Pipeline.rtv_formats). Called right before every draw. The
 * common case -- the pipeline was built for the bound formats -- is one
 * compare loop. A miss looks up / builds a variant; if the cache is full or
 * creation fails, the original PSO stays bound (the old behaviour). */
static void rhi_d3d12_match_rtv_formats(RHI_D3D12Context *ctx) {
    RHI_D3D12Pipeline *pd = (RHI_D3D12Pipeline *)ctx->bound_pipeline;
    ID3D12GraphicsCommandList *list = rhi_d3d12_cmd_list(ctx);
    ID3D12PipelineState *want = NULL;
    UINT i, k, n, no_dsv;
    if (pd == NULL || list == NULL || pd->is_compute || pd->rtv_count == 0u ||
        pd->vs_blob == NULL)
        return;
    n = ctx->bound_rtv_count;
    if (n == 0u) return;
    no_dsv = ctx->bound_dsv_valid ? 0u : 1u;
    if (n == pd->rtv_count && !no_dsv) {
        for (i = 0u; i < n; ++i)
            if (ctx->bound_rtv_formats[i] != pd->rtv_formats[i]) break;
        if (i == n) want = pd->pso;
    }
    for (k = 0u; want == NULL && k < pd->variant_count; ++k) {
        if (pd->variants[k].count != n || pd->variants[k].no_dsv != no_dsv)
            continue;
        for (i = 0u; i < n; ++i)
            if (pd->variants[k].formats[i] != ctx->bound_rtv_formats[i]) break;
        if (i == n) want = pd->variants[k].pso;
    }
    if (want == NULL && pd->variant_count < 6u) {
        D3D12_SHADER_BYTECODE vs, ps;
        UINT stride = 0u;
        vs.pShaderBytecode = pd->vs_blob;
        vs.BytecodeLength = pd->vs_blob_size;
        ps.pShaderBytecode = pd->ps_blob;
        ps.BytecodeLength = pd->ps_blob_size;
        want = rhi_d3d12_create_graphics_pso(ctx, pd->root_sig, &vs,
            pd->ps_blob != NULL ? &ps : NULL, &pd->desc, &stride,
            ctx->bound_rtv_formats, n, no_dsv);
        if (want != NULL) {
            k = pd->variant_count++;
            pd->variants[k].no_dsv = no_dsv;
            for (i = 0u; i < n; ++i)
                pd->variants[k].formats[i] = ctx->bound_rtv_formats[i];
            pd->variants[k].count = n;
            pd->variants[k].pso = want;
        }
    }
    if (want != NULL && want != ctx->bound_pso) {
        ID3D12GraphicsCommandList_SetPipelineState(list, want);
        ctx->bound_pso = want;
    }
}

static void rhi_d3d12_flush_uniform_staging(RHI_D3D12Context *ctx) {
    RHI_D3D12Pipeline *pd;
    ID3D12GraphicsCommandList *list;
    UINT lo;
    UINT hi;
    if (ctx == NULL || ctx->uniform_dirty_lo >= ctx->uniform_dirty_hi) return;
    pd = (RHI_D3D12Pipeline *)ctx->bound_pipeline;
    list = rhi_d3d12_cmd_list(ctx);
    if (pd == NULL || list == NULL || pd->push_param_index == UINT_MAX) {
        ctx->uniform_dirty_lo = 0u;
        ctx->uniform_dirty_hi = 0u;
        return;
    }
    lo = ctx->uniform_dirty_lo & ~3u;
    hi = (ctx->uniform_dirty_hi + 3u) & ~3u;
    if (hi > pd->push_size) hi = pd->push_size;
    ctx->uniform_dirty_lo = 0u;
    ctx->uniform_dirty_hi = 0u;
    if (hi <= lo) return;
    if (pd->is_compute)
        ID3D12GraphicsCommandList_SetComputeRoot32BitConstants(list,
            pd->push_param_index, (hi - lo) / 4u, ctx->uniform_staging + lo,
            lo / 4u);
    else
        ID3D12GraphicsCommandList_SetGraphicsRoot32BitConstants(list,
            pd->push_param_index, (hi - lo) / 4u, ctx->uniform_staging + lo,
            lo / 4u);
}

void rhi_cmd_begin_render_pass(RHICmdBuffer *cmd) {
    RHI_D3D12Context *ctx = (RHI_D3D12Context *)cmd;
    if (ctx == NULL || rhi_d3d12_cmd_list(ctx) == NULL) return;
    /* D3D12 records RTV/DSV binding directly; FBO bind already performed the
     * OMSetRenderTargets operation. Keep the explicit API stateful and
     * idempotent like VK, without opening a second native pass object. */
    if (!ctx->render_pass_active) ctx->render_pass_active = 1u;
}
void rhi_cmd_end_render_pass(RHICmdBuffer *cmd) {
    RHI_D3D12Context *ctx = (RHI_D3D12Context *)cmd;
    if (ctx == NULL) return;
    ctx->render_pass_active = 0u;
}
void rhi_cmd_bind_pipeline(RHICmdBuffer *cmd, RHIPipeline pipe) {
    RHI_D3D12Context *ctx = (RHI_D3D12Context *)cmd;
    ID3D12GraphicsCommandList *list;
    RHI_D3D12Pipeline *pd;
    ID3D12DescriptorHeap *heaps[2];
    if (ctx == NULL || g_current_device == NULL) return;
    list = rhi_d3d12_cmd_list(ctx);
    if (list == NULL) return;
    pd = (RHI_D3D12Pipeline *)rhi_get_resource_typed(g_current_device, pipe,
                                                     RHI_RES_PIPELINE);
    if (pd == NULL) return;
    /* Descriptor tables resolve against the shader-visible heaps; bind them
     * with every pipeline so a later table bind never sees a stale heap. */
    heaps[0] = ctx->cbv_srv_uav_heap;
    heaps[1] = ctx->sampler_heap;
    ID3D12GraphicsCommandList_SetDescriptorHeaps(list, 2u, heaps);
    ID3D12GraphicsCommandList_SetPipelineState(list, pd->pso);
    ctx->bound_pso = pd->pso;
    if (!pd->is_compute) memset(ctx->live_srv, 0, sizeof(ctx->live_srv));
    if (pd->is_compute) {
        ID3D12GraphicsCommandList_SetComputeRootSignature(list, pd->root_sig);
    } else {
        ID3D12GraphicsCommandList_SetGraphicsRootSignature(list, pd->root_sig);
        ID3D12GraphicsCommandList_IASetPrimitiveTopology(list, pd->topology);
        /* R643: a uniform buffer bound with rhi_cmd_bind_uniform_buffer stays
         * bound across pipeline changes on GL (global binding points) and on
         * Vulkan (compatible set layouts), and main.c relies on it: it binds
         * the forward temporal block once and rebinds only the pipeline after
         * other passes ran. D3D12 resets every root argument when the root
         * signature changes, so the next draw read an uninitialised b1
         * (GPU-based validation [935]). Re-apply this frame's CBVs to the
         * registers the new pipeline declares. */
        for (UINT r = 0u; r < RHI_D3D12_MAX_REGISTERS; ++r) {
            UINT param = pd->uniform_root_params[r];
            if (param == UINT_MAX || ctx->cbv_frame[r] != ctx->debug_frame)
                continue;
            ID3D12GraphicsCommandList_SetGraphicsRootDescriptorTable(
                list, param, ctx->cbv_gpu[r]);
        }
    }
    ctx->bound_pipeline = pd;
    ctx->bound_pipeline_compute = pd->is_compute;
}
void rhi_cmd_bind_vertex_buffer(RHICmdBuffer *cmd, RHIBuffer buf,
                                usize offset) {
    RHI_D3D12Context *ctx = (RHI_D3D12Context *)cmd;
    ID3D12GraphicsCommandList *list;
    RHI_D3D12Pipeline *pd;
    RHI_D3D12Buffer *bd;
    D3D12_VERTEX_BUFFER_VIEW view;
    if (ctx == NULL || g_current_device == NULL) return;
    list = rhi_d3d12_cmd_list(ctx);
    pd = (RHI_D3D12Pipeline *)ctx->bound_pipeline;
    if (list == NULL || pd == NULL || pd->is_compute || pd->vertex_stride == 0u)
        return;
    bd = (RHI_D3D12Buffer *)rhi_get_resource_typed(g_current_device, buf,
                                                   RHI_RES_BUFFER);
    if (bd == NULL || offset >= (usize)bd->size) return;
    view.BufferLocation = ID3D12Resource_GetGPUVirtualAddress(
                              rhi_d3d12_buffer_view_source(ctx, bd)) +
                          (UINT64)offset;
    view.SizeInBytes = (UINT)(bd->size - offset);
    view.StrideInBytes = pd->vertex_stride;
    ID3D12GraphicsCommandList_IASetVertexBuffers(list, 0u, 1u, &view);
}
void rhi_cmd_bind_index_buffer(RHICmdBuffer *cmd, RHIBuffer buf, usize offset,
                               bool is_u32) {
    RHI_D3D12Context *ctx = (RHI_D3D12Context *)cmd;
    ID3D12GraphicsCommandList *list;
    RHI_D3D12Buffer *bd;
    D3D12_INDEX_BUFFER_VIEW view;
    if (ctx == NULL || g_current_device == NULL) return;
    list = rhi_d3d12_cmd_list(ctx);
    if (list == NULL) return;
    bd = (RHI_D3D12Buffer *)rhi_get_resource_typed(g_current_device, buf,
                                                   RHI_RES_BUFFER);
    if (bd == NULL || offset >= (usize)bd->size) return;
    view.BufferLocation = ID3D12Resource_GetGPUVirtualAddress(
                              rhi_d3d12_buffer_view_source(ctx, bd)) +
                          (UINT64)offset;
    view.SizeInBytes = (UINT)(bd->size - offset);
    view.Format = is_u32 ? DXGI_FORMAT_R32_UINT : DXGI_FORMAT_R16_UINT;
    ID3D12GraphicsCommandList_IASetIndexBuffer(list, &view);
}
void rhi_cmd_set_viewport(RHICmdBuffer *cmd, f32 x, f32 y, f32 w, f32 h,
                          f32 min_depth, f32 max_depth) {
    RHI_D3D12Context *ctx = (RHI_D3D12Context *)cmd;
    ID3D12GraphicsCommandList *list = rhi_d3d12_cmd_list(ctx);
    D3D12_VIEWPORT vp;
    if (list == NULL) return;
    /* This is the RHI's "+Y up" viewport (R715: the UI canvas states its
     * orientation through it), the twin of VK's {x, y + h, w, -h}.
     *
     * The sign does NOT carry over from Vulkan. Vulkan's NDC y points down,
     * so VK needs a negative height to put NDC +Y at the top; D3D12's NDC y
     * already points up, so the positive-height viewport does that, and a
     * negative height is what turns +Y downward -- i.e. D3D12's negative
     * height is VK's POSITIVE one. This used to copy VK's sign and was
     * therefore identical to the frame/FBO default viewports
     * (rhi_d3d12_set_full_target_viewport, which match VK's positive
     * {0, 0, w, h}); R638 measured a quad covering NDC y > 0 landing in the
     * bottom half of the back buffer under both, and the demo's UI drawing
     * upside down at the bottom of the window. Covered by
     * swapchain_draws_put_ndc_up_at_the_top_of_the_screen. */
    vp.TopLeftX = x;
    vp.TopLeftY = y;
    vp.Width = w;
    vp.Height = h;
    vp.MinDepth = min_depth;
    vp.MaxDepth = max_depth;
    ID3D12GraphicsCommandList_RSSetViewports(list, 1u, &vp);
}
/* Full-target viewport + scissor. D3D12's implicit default is 1280x720, so
 * without this every draw is clipped to whatever sliver of the actual
 * target the default viewport happens to cover (clears are target-wide and
 * so look fine, which hides it). Uses the RHI's bottom-left convention -
 * TopLeftY = y + h, negative height - so NDC +Y lands on the top row. */
static void rhi_d3d12_set_full_target_viewport(ID3D12GraphicsCommandList *list,
                                               u32 w, u32 h) {
    D3D12_VIEWPORT vp;
    D3D12_RECT rect;
    if (list == NULL || w == 0u || h == 0u) return;
    vp.TopLeftX = 0.0f;
    vp.TopLeftY = (f32)h;
    vp.Width = (f32)w;
    vp.Height = -(f32)h;
    vp.MinDepth = 0.0f;
    vp.MaxDepth = 1.0f;
    ID3D12GraphicsCommandList_RSSetViewports(list, 1u, &vp);
    rect.left = 0;
    rect.top = 0;
    rect.right = (LONG)w;
    rect.bottom = (LONG)h;
    ID3D12GraphicsCommandList_RSSetScissorRects(list, 1u, &rect);
}
void rhi_cmd_set_scissor(RHICmdBuffer *cmd, i32 x, i32 y, u32 w, u32 h) {
    RHI_D3D12Context *ctx = (RHI_D3D12Context *)cmd;
    ID3D12GraphicsCommandList *list = rhi_d3d12_cmd_list(ctx);
    D3D12_RECT rect;
    if (list == NULL) return;
    rect.left = x;
    rect.top = y;
    rect.right = x + (LONG)w;
    rect.bottom = y + (LONG)h;
    ID3D12GraphicsCommandList_RSSetScissorRects(list, 1u, &rect);
}
void rhi_cmd_set_scissor_top_left(RHICmdBuffer *cmd, u32 x, u32 y, u32 w,
                                  u32 h) {
    rhi_cmd_set_scissor(cmd, (i32)x, (i32)y, w, h);
}
void rhi_cmd_set_shadow_viewport(RHICmdBuffer *cmd, u32 x, u32 y, u32 w,
                                 u32 h) {
    RHI_D3D12Context *ctx = (RHI_D3D12Context *)cmd;
    ID3D12GraphicsCommandList *list = rhi_d3d12_cmd_list(ctx);
    D3D12_VIEWPORT vp;
    if (list == NULL) return;
    /* Non-flipped: shadow depth passes use a top-left-origin viewport. */
    vp.TopLeftX = (f32)x;
    vp.TopLeftY = (f32)y;
    vp.Width = (f32)w;
    vp.Height = (f32)h;
    vp.MinDepth = 0.0f;
    vp.MaxDepth = 1.0f;
    ID3D12GraphicsCommandList_RSSetViewports(list, 1u, &vp);
    rhi_cmd_set_scissor(cmd, (i32)x, (i32)y, w, h);
}
void rhi_cmd_draw(RHICmdBuffer *cmd, u32 vertex_count, u32 instance_count) {
    ID3D12GraphicsCommandList *list =
        rhi_d3d12_cmd_list((RHI_D3D12Context *)cmd);
    if (list == NULL) return;
    rhi_d3d12_match_rtv_formats((RHI_D3D12Context *)cmd);
    rhi_d3d12_flush_uniform_staging((RHI_D3D12Context *)cmd);
    ID3D12GraphicsCommandList_DrawInstanced(list, vertex_count, instance_count,
                                            0u, 0u);
}
void rhi_cmd_draw_base(RHICmdBuffer *cmd, u32 vertex_count, u32 instance_count,
                       u32 first_vertex) {
    ID3D12GraphicsCommandList *list =
        rhi_d3d12_cmd_list((RHI_D3D12Context *)cmd);
    if (list == NULL) return;
    rhi_d3d12_match_rtv_formats((RHI_D3D12Context *)cmd);
    rhi_d3d12_flush_uniform_staging((RHI_D3D12Context *)cmd);
    ID3D12GraphicsCommandList_DrawInstanced(list, vertex_count, instance_count,
                                            first_vertex, 0u);
}
void rhi_cmd_draw_indexed(RHICmdBuffer *cmd, u32 index_count,
                          u32 instance_count) {
    ID3D12GraphicsCommandList *list =
        rhi_d3d12_cmd_list((RHI_D3D12Context *)cmd);
    if (list == NULL) return;
    rhi_d3d12_match_rtv_formats((RHI_D3D12Context *)cmd);
    rhi_d3d12_flush_uniform_staging((RHI_D3D12Context *)cmd);
    ID3D12GraphicsCommandList_DrawIndexedInstanced(list, index_count,
                                                   instance_count, 0u, 0, 0u);
}
void rhi_cmd_draw_indexed_base(RHICmdBuffer *cmd, u32 index_count,
                               u32 instance_count, u32 first_index,
                               i32 vertex_offset) {
    ID3D12GraphicsCommandList *list =
        rhi_d3d12_cmd_list((RHI_D3D12Context *)cmd);
    if (list == NULL) return;
    rhi_d3d12_match_rtv_formats((RHI_D3D12Context *)cmd);
    rhi_d3d12_flush_uniform_staging((RHI_D3D12Context *)cmd);
    ID3D12GraphicsCommandList_DrawIndexedInstanced(list, index_count,
        instance_count, first_index, vertex_offset, 0u);
}
UINT rhi_d3d12_indirect_args_valid(UINT indexed, UINT stride, UINT draw_count) {
    if (indexed)
        return rhi_indirect_abi_valid(stride, draw_count) &&
               stride == (UINT)sizeof(RHIIndexedIndirectCommand);
    return draw_count != 0u && stride == (UINT)sizeof(D3D12_DRAW_ARGUMENTS);
}

static void rhi_d3d12_execute_indirect(RHIDevice *dev, RHIBuffer cmd_buf,
                                       UINT64 offset, UINT draw_count,
                                       UINT stride, RHIBuffer count_buf,
                                       UINT64 count_offset, UINT max_draws,
                                       UINT indexed) {
    RHI_D3D12Context *ctx;
    ID3D12GraphicsCommandList *list;
    RHI_D3D12Buffer *args;
    RHI_D3D12Buffer *counter = NULL;
    if (dev == NULL) return;
    ctx = (RHI_D3D12Context *)dev->backend_data;
    if (ctx == NULL) return;
    /* The indexed ABI rule applies to indexed draws only; gating non-indexed
     * draws on it silently dead-ended every 16-byte-stride call. Rejections
     * are loud (fail closed, never a silent drop). */
    if (!rhi_d3d12_indirect_args_valid(indexed, stride, draw_count)) {
        LOG_WARN("D3D12: %s indirect args rejected (stride %u, count %u)",
                 indexed != 0u ? "indexed" : "non-indexed", stride, draw_count);
        return;
    }
    list = rhi_d3d12_cmd_list(ctx);
    if (list == NULL) return;
    rhi_d3d12_match_rtv_formats(ctx);
    rhi_d3d12_flush_uniform_staging(ctx);
    args = (RHI_D3D12Buffer *)rhi_get_resource_typed(dev, cmd_buf, RHI_RES_BUFFER);
    if (args == NULL) {
        LOG_WARN("D3D12: indirect draw with invalid argument buffer");
        return;
    }
    if (rhi_handle_valid(count_buf)) {
        counter = (RHI_D3D12Buffer *)rhi_get_resource_typed(dev, count_buf,
                                                            RHI_RES_BUFFER);
        if (counter == NULL) {
            LOG_WARN("D3D12: indirect draw with invalid count buffer");
            return;
        }
    }
    /* ExecuteIndirect requires the argument stride to equal the command
     * signature stride; the gate above already enforced exactly that.
     *
     * It also requires the argument buffer to be in INDIRECT_ARGUMENT state.
     * Nothing else put it there: rhi_buffer_create ends a create-time upload
     * in COMMON (or GENERIC_READ for an UPLOAD-heap buffer) and
     * rhi_buffer_update returns it to COMMON, so without this transition the
     * ExecuteIndirect reads a resource whose state never named the
     * indirection, which the API leaves undefined. The state is left as
     * INDIRECT_ARGUMENT: a later rhi_buffer_update transitions out of it
     * before writing, and back is cheap.
     *
     * Note this is a correctness fix, not a fix for the layer: with this
     * transition in place WARP still returns SV_InstanceID = 0 for a record
     * whose StartInstanceLocation is 1 or 2, while the same pipeline and
     * shader take it correctly from InstanceCount. See
     * blinn_phong_arr_sidecar_forwards_the_layer_into_pixels in
     * tests/test_d3d12_warp_runtime.c. */
    /* R650: a buffer the bound pipeline also reads as an SRV (the particle
     * DrawBuf: header for ExecuteIndirect, alive indices for the vertex
     * shader) keeps its shader-read bits -- read states combine, and
     * dropping them would leave that SRV reading a buffer in a state that
     * does not name it. */
    if (args->device_local &&
        (args->state & D3D12_RESOURCE_STATE_INDIRECT_ARGUMENT) == 0) {
        const D3D12_RESOURCE_STATES srv_bits =
            D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE |
            D3D12_RESOURCE_STATE_NON_PIXEL_SHADER_RESOURCE;
        D3D12_RESOURCE_STATES want = D3D12_RESOURCE_STATE_INDIRECT_ARGUMENT;
        if ((args->state & ~srv_bits) == 0 && (args->state & srv_bits) != 0)
            want |= args->state;
        rhi_d3d12_transition(list, args->resource, args->state, want);
        args->state = want;
    }
    /* The count buffer is read by ExecuteIndirect the same way and has the
     * same requirement. compact_draws writes it as a UAV right before this. */
    if (counter != NULL && counter->device_local &&
        counter->state != D3D12_RESOURCE_STATE_INDIRECT_ARGUMENT) {
        rhi_d3d12_transition(list, counter->resource, counter->state,
                             D3D12_RESOURCE_STATE_INDIRECT_ARGUMENT);
        counter->state = D3D12_RESOURCE_STATE_INDIRECT_ARGUMENT;
    }
    ID3D12GraphicsCommandList_ExecuteIndirect(list,
        indexed ? ctx->draw_indexed_signature : ctx->draw_signature,
        counter != NULL ? max_draws : draw_count,
        args->resource, offset,
        counter != NULL ? counter->resource : NULL, count_offset);
}
void rhi_cmd_draw_indirect(RHIDevice *dev, RHIBuffer cmd_buf, u32 offset,
                           u32 draw_count, u32 stride) {
    rhi_d3d12_execute_indirect(dev, cmd_buf, offset, draw_count, stride,
                               RHI_HANDLE_NULL, 0u, 0u, 0u);
}
void rhi_cmd_draw_indexed_indirect(RHIDevice *dev, RHIBuffer cmd_buf,
                                   u32 offset, u32 draw_count, u32 stride) {
    rhi_d3d12_execute_indirect(dev, cmd_buf, offset, draw_count, stride,
                               RHI_HANDLE_NULL, 0u, 0u, 1u);
}
void rhi_cmd_draw_indexed_indirect_count(RHIDevice *dev, RHIBuffer cmd_buf,
                                         u32 cmd_offset, RHIBuffer count_buf,
                                         u32 count_offset, u32 max_draws,
                                         u32 stride) {
    if (max_draws == 0u) return;
    rhi_d3d12_execute_indirect(dev, cmd_buf, cmd_offset, max_draws, stride,
                               count_buf, count_offset, max_draws, 1u);
}
void rhi_cmd_clear_color(RHICmdBuffer *cmd, f32 r, f32 g, f32 b, f32 a) {
    RHI_D3D12Context *ctx = (RHI_D3D12Context *)cmd;
    ID3D12GraphicsCommandList *list = rhi_d3d12_cmd_list(ctx);
    float color[4];
    UINT i;
    if (list == NULL) return;
    color[0] = r; color[1] = g; color[2] = b; color[3] = a;
    for (i = 0u; i < ctx->bound_rtv_count; ++i)
        ID3D12GraphicsCommandList_ClearRenderTargetView(list,
            ctx->bound_rtvs[i], color, 0u, NULL);
}
void rhi_cmd_clear_color_attachment(RHICmdBuffer *cmd, u32 attachment, f32 r,
                                    f32 g, f32 b, f32 a) {
    RHI_D3D12Context *ctx = (RHI_D3D12Context *)cmd;
    ID3D12GraphicsCommandList *list = rhi_d3d12_cmd_list(ctx);
    float color[4];
    if (list == NULL || attachment >= ctx->bound_rtv_count) return;
    color[0] = r; color[1] = g; color[2] = b; color[3] = a;
    ID3D12GraphicsCommandList_ClearRenderTargetView(list,
        ctx->bound_rtvs[attachment], color, 0u, NULL);
}
/* The format a shader resource view over this texture must declare. Every
 * colour texture and every ordinary D32_FLOAT depth target reports its own
 * format; only a shadow-atlas depth texture, allocated typeless so it can be
 * both the shadow pass's DSV and the lighting pass's SRV, reports the
 * R32_FLOAT alias instead of the unsamplable R32_TYPELESS it was
 * actually allocated with. */
/* R653/R654: per-subresource state tracking (see RHI_D3D12Texture.mip_state). */
static UINT rhi_d3d12_tex_subresource_count(const RHI_D3D12Texture *td) {
    UINT n = td->mip_levels * (td->array_size > 0u ? td->array_size : 1u);
    return n < 64u ? n : 64u;
}
static void rhi_d3d12_tex_sub_transition(ID3D12GraphicsCommandList *list,
                                         RHI_D3D12Texture *td, UINT sub,
                                         D3D12_RESOURCE_STATES want) {
    D3D12_RESOURCE_BARRIER barrier;
    UINT n = rhi_d3d12_tex_subresource_count(td);
    UINT m;
    if (sub >= n) return;
    if (!td->mip_split) {
        for (m = 0u; m < n; ++m) td->mip_state[m] = td->state;
        td->mip_split = 1u;
    }
    if (td->mip_state[sub] == want) return;
    ZeroMemory(&barrier, sizeof(barrier));
    barrier.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
    barrier.Transition.pResource = td->resource;
    barrier.Transition.Subresource = sub;
    barrier.Transition.StateBefore = td->mip_state[sub];
    barrier.Transition.StateAfter = want;
    ID3D12GraphicsCommandList_ResourceBarrier(list, 1u, &barrier);
    td->mip_state[sub] = want;
}
static void rhi_d3d12_tex_mip_transition(ID3D12GraphicsCommandList *list,
                                         RHI_D3D12Texture *td, UINT mip,
                                         D3D12_RESOURCE_STATES want) {
    if (mip >= td->mip_levels) return;
    rhi_d3d12_tex_sub_transition(list, td, mip, want);
}
static void rhi_d3d12_tex_unify(ID3D12GraphicsCommandList *list,
                                RHI_D3D12Texture *td,
                                D3D12_RESOURCE_STATES want) {
    UINT n = rhi_d3d12_tex_subresource_count(td);
    UINT m;
    if (!td->mip_split) return;
    for (m = 0u; m < n; ++m)
        rhi_d3d12_tex_sub_transition(list, td, m, want);
    td->mip_split = 0u;
    td->state = want;
}
static DXGI_FORMAT rhi_d3d12_srv_format(const RHI_D3D12Texture *td) {
    return td->srv_format != DXGI_FORMAT_UNKNOWN ? td->srv_format
                                                 : td->dxgi_format;
}
static void rhi_d3d12_bind_texture_td(RHICmdBuffer *cmd, RHI_D3D12Texture *td,
                                      u32 unit);
void rhi_cmd_bind_texture(RHICmdBuffer *cmd, RHITexture tex,
                          RHISampler sampler, u32 unit) {
    RHI_D3D12Texture *td;
    /* KNOWN LIMIT — the sampler argument is accepted and then discarded, on
     * every backend path that reaches this function, including the material
     * binders. Root-signature construction resolves every SamplerState
     * register to a D3D12_STATIC_SAMPLER_DESC (rhi_d3d12_root_sig_add_bindings)
     * hardcoded to MIN_MAG_MIP_LINEAR + MaxLOD FLT_MAX, and emits no root
     * parameter of type SAMPLER table, so there is nothing for a bind to
     * point at. GL applies the caller's sampler object per unit and so
     * honours filter, address mode and LOD selection; D3D12 currently
     * cannot. R662 picks the address mode per pipeline instead of per bind:
     * CLAMP for fullscreen (no_vertex_input) and compute pipelines -- every
     * sampler the post chain, deferred lighting, IBL and particle passes
     * create asks for CLAMP_TO_EDGE -- and WRAP for mesh pipelines, which
     * bind the engine's REPEAT material sampler.
     *
     * What that means concretely: a texture can be filtered LINEAR and
     * addressed WRAP or CLAMP by pipeline kind, and nothing else (NEAREST
     * requests come back bilinear). In particular there is no comparison
     * sampling — EnableComparison is never set and no D3D12_SAMPLER_DESC
     * reaches the shader.
     *
     * That is NOT what blocks the shadow pass. No production shader declares
     * a shadow sampler: the clustered forward shaders sample the point-shadow
     * cubes and the shadow atlas as a plain sampler and compare by hand on
     * the raw .r channel (blinn_phong_clustered.frag:70-71, the _vk twin
     * likewise), and the GL backend deliberately sets
     * GL_TEXTURE_COMPARE_MODE = GL_NONE for the same reason. A static LINEAR
     * sampler plus a plain SRV is exactly what that code needs. The shadow
     * atlas's real D3D12 constraint is the opposite one: D32_FLOAT cannot
     * back an SRV at all, so the atlas is allocated as the typeless
     * R32_TYPELESS and aliased to an R32_FLOAT SRV (see
     * rhi_d3d12_srv_format).
     *
     * The infrastructure for a real sampler table is half-present and
     * unused: the context already owns a shader-visible sampler heap
     * (sampler_heap / sampler_alloc) and rhi_sampler_create already writes a
     * real D3D12_SAMPLER_DESC honouring RHISamplerDesc's filters and address
     * modes into it (RHI_D3D12Sampler just holds the slot). What is missing
     * is (a) a root parameter carrying a SAMPLER descriptor range for the
     * pipeline's sampler registers, (b) a SetGraphicsRootDescriptorTable
     * alongside the SRV table here, and (c) a comparison flag on
     * RHISamplerDesc -> D3D12_SAMPLER_DESC. Deliberately not done in this
     * round: it is a root-signature change affecting every existing pipeline,
     * not a binder fix, and nothing in the current shader set needs it. */
    (void)sampler;
    if (g_current_device == NULL) return;
    td = (RHI_D3D12Texture *)rhi_get_resource_typed(g_current_device, tex,
                                                    RHI_RES_TEXTURE);
    if (td != NULL) rhi_d3d12_bind_texture_td(cmd, td, unit);
}
static void rhi_d3d12_bind_texture_td(RHICmdBuffer *cmd, RHI_D3D12Texture *td,
                                      u32 unit) {
    RHI_D3D12Context *ctx = (RHI_D3D12Context *)cmd;
    ID3D12GraphicsCommandList *list;
    RHI_D3D12Pipeline *pd;
    D3D12_SHADER_RESOURCE_VIEW_DESC srv;
    D3D12_GPU_DESCRIPTOR_HANDLE gpu;
    D3D12_RESOURCE_STATES read_state;
    UINT root_param;
    UINT slot;
    if (ctx == NULL || g_current_device == NULL || unit >= RHI_D3D12_MAX_REGISTERS) return;
    list = rhi_d3d12_cmd_list(ctx);
    pd = (RHI_D3D12Pipeline *)ctx->bound_pipeline;
    if (list == NULL || pd == NULL || td == NULL || td->resource == NULL)
        return;
    root_param = pd->image_root_params[unit];
    if (root_param == UINT_MAX) return;
    if (ctx->frame_srv_count >= RHI_D3D12_CBV_SRV_UAV_CAPACITY) return;
    slot = rhi_d3d12_descriptor_take(ctx, &ctx->cbv_srv_uav_alloc);
    if (slot == UINT_MAX) {
        LOG_WARN("D3D12: SRV descriptor heap exhausted");
        return;
    }
    ZeroMemory(&srv, sizeof(srv));
    srv.Format = rhi_d3d12_srv_format(td);
    /* R441: the view dimension is the ONLY thing that distinguishes a 2D-array
     * texture from a 2D one in D3D12 — both are a TEXTURE2D resource whose
     * slices are counted by DepthOrArraySize. A sampler2DArray declared in a
     * shader (blinn_phong_arr_hlsl.frag's Texture2DArray) needs a
     * TEXTURE2DARRAY descriptor spanning every slice; handing it the TEXTURE2D
     * view a 2D shader wants is a descriptor/shader dimension mismatch, not a
     * soft fallback. ArraySize is the whole array because the shader selects
     * the layer per draw (SV_InstanceID), not per descriptor. */
    if (td->is_cube) {
        /* R647: a point-shadow depth cube. The shader declares TextureCube
         * and selects the face by direction, so the view spans all six
         * slices as one cube. */
        srv.ViewDimension = D3D12_SRV_DIMENSION_TEXTURECUBE;
        srv.TextureCube.MostDetailedMip = 0u;
        srv.TextureCube.MipLevels = td->mip_levels;
        srv.TextureCube.ResourceMinLODClamp = 0.0f;
    } else if (td->array_size > 1u) {
        srv.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2DARRAY;
        srv.Texture2DArray.MostDetailedMip = 0u;
        srv.Texture2DArray.MipLevels = td->mip_levels;
        srv.Texture2DArray.FirstArraySlice = 0u;
        srv.Texture2DArray.ArraySize = td->array_size;
        srv.Texture2DArray.PlaneSlice = 0u;
    } else {
        srv.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;
        srv.Texture2D.MostDetailedMip = 0u;
        srv.Texture2D.MipLevels = td->mip_levels;
    }
    srv.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
    ID3D12Device_CreateShaderResourceView(ctx->device, td->resource, &srv,
        rhi_d3d12_descriptor_cpu(&ctx->cbv_srv_uav_alloc, slot));
    ctx->frame_srv_slots[ctx->frame_srv_count++] = slot;
    read_state = D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE |
                 D3D12_RESOURCE_STATE_NON_PIXEL_SHADER_RESOURCE;
    rhi_d3d12_tex_unify(list, td, read_state);
    if (td->state != read_state) {
        rhi_d3d12_transition(list, td->resource, td->state, read_state);
        td->state = read_state;
    }
    gpu = rhi_d3d12_descriptor_gpu(&ctx->cbv_srv_uav_alloc, slot);
    /* R629/R643 diagnostic: the texture is now live in this pipeline's
     * descriptor tables, so a render-target bind of it can be noticed. */
    if (!pd->is_compute) ctx->live_srv[unit] = td;
    if (pd->is_compute)
        ID3D12GraphicsCommandList_SetComputeRootDescriptorTable(list, root_param, gpu);
    else
        ID3D12GraphicsCommandList_SetGraphicsRootDescriptorTable(list, root_param, gpu);
}
void rhi_cmd_bind_shadow_texture(RHICmdBuffer *cmd, RHITexture shadow_tex,
                                 RHISampler sampler) {
    /* Material unit 1 is where the atlas belongs — the same slot the GL
     * backend binds it to. The sampler argument is discarded exactly as in
     * rhi_cmd_bind_texture: the production shaders compare the sampled .r by
     * hand rather than through a comparison sampler, so the static LINEAR
     * sampler the root signature already provides is what they expect. */
    rhi_cmd_bind_texture(cmd, shadow_tex, sampler, 1u);
}
void rhi_cmd_bind_uniform_buffer(RHICmdBuffer *cmd, RHIBuffer buf,
                                 u32 binding) {
    RHI_D3D12Context *ctx = (RHI_D3D12Context *)cmd;
    RHI_D3D12Pipeline *pd;
    RHI_D3D12Buffer *bd;
    ID3D12GraphicsCommandList *list;
    D3D12_CONSTANT_BUFFER_VIEW_DESC cbv;
    D3D12_GPU_DESCRIPTOR_HANDLE gpu;
    UINT param, slot;
    if (ctx == NULL || g_current_device == NULL || binding >= RHI_D3D12_MAX_REGISTERS) return;
    pd = (RHI_D3D12Pipeline *)ctx->bound_pipeline;
    list = rhi_d3d12_cmd_list(ctx);
    if (pd == NULL || list == NULL) return;
    param = pd->uniform_root_params[binding];
    if (param == UINT_MAX) return;
    bd = (RHI_D3D12Buffer *)rhi_get_resource_typed(g_current_device, buf,
                                                    RHI_RES_BUFFER);
    if (bd == NULL || bd->resource == NULL) return;
    if (ctx->frame_srv_count >= RHI_D3D12_CBV_SRV_UAV_CAPACITY) return;
    slot = rhi_d3d12_descriptor_take(ctx, &ctx->cbv_srv_uav_alloc);
    if (slot == UINT_MAX) return;
    ZeroMemory(&cbv, sizeof(cbv));
    cbv.BufferLocation = ID3D12Resource_GetGPUVirtualAddress(
        rhi_d3d12_buffer_view_source(ctx, bd));
    cbv.SizeInBytes = (UINT)((bd->size + 255u) & ~255u);
    ID3D12Device_CreateConstantBufferView(ctx->device, &cbv,
        rhi_d3d12_descriptor_cpu(&ctx->cbv_srv_uav_alloc, slot));
    gpu = rhi_d3d12_descriptor_gpu(&ctx->cbv_srv_uav_alloc, slot);
    if (pd->is_compute) {
        ID3D12GraphicsCommandList_SetComputeRootDescriptorTable(list, param, gpu);
    } else {
        ID3D12GraphicsCommandList_SetGraphicsRootDescriptorTable(list, param, gpu);
        ctx->cbv_gpu[binding] = gpu;
        ctx->cbv_frame[binding] = ctx->debug_frame;
    }
    /* R643: retire with the frame, like every other per-frame view. Giving
     * the slot back here with ctx->next_fence as its retire point was wrong
     * whenever a one-shot submit (a buffer or texture upload with initial
     * data) ran later in the same frame: the one-shot signals that very
     * value and waits for it, so the slot looked retired while the frame's
     * own list -- which still points at it -- had not even been submitted.
     * The next SRV bind then overwrote the descriptor under this CBV
     * (debug layer [1001]). */
    ctx->frame_srv_slots[ctx->frame_srv_count++] = slot;
}
/* Legacy per-uniform setters write the 256B push staging buffer; the dirty
 * range flushes as root constants before the next draw/dispatch (VK parity).
 * R552-B: validation is against the pipeline's declared push range, not the
 * staging size — out-of-range writes drop with a warning, never truncate. */
static void rhi_d3d12_stage_uniform(RHICmdBuffer *cmd, i32 location,
                                    const void *data, u32 size) {
    RHI_D3D12Context *ctx = (RHI_D3D12Context *)cmd;
    RHI_D3D12Pipeline *pd;
    if (ctx == NULL || data == NULL) return;
    pd = (RHI_D3D12Pipeline *)ctx->bound_pipeline;
    if (pd == NULL || pd->push_param_index == UINT_MAX) return;
    if (!rhi_push_helper_range_ok(location, size, pd->push_size)) {
        LOG_WARN("D3D12: set_uniform at %d+%u outside declared %u — write "
                 "dropped", location, size, pd->push_size);
        return;
    }
    memcpy(ctx->uniform_staging + location, data, size);
    if ((UINT)location < ctx->uniform_dirty_lo)
        ctx->uniform_dirty_lo = (UINT)location;
    if ((UINT)location + size > ctx->uniform_dirty_hi)
        ctx->uniform_dirty_hi = (UINT)location + size;
}
void rhi_cmd_set_uniform_mat4(RHICmdBuffer *cmd, i32 location, const f32 *m) {
    rhi_d3d12_stage_uniform(cmd, location, m, 64u);
}
void rhi_cmd_set_uniform_vec3(RHICmdBuffer *cmd, i32 location, f32 x, f32 y,
                              f32 z) {
    f32 v[3];
    v[0] = x; v[1] = y; v[2] = z;
    rhi_d3d12_stage_uniform(cmd, location, v, 12u);
}
void rhi_cmd_set_uniform_vec2(RHICmdBuffer *cmd, i32 location, f32 x, f32 y) {
    f32 v[2];
    v[0] = x; v[1] = y;
    rhi_d3d12_stage_uniform(cmd, location, v, 8u);
}
void rhi_cmd_set_uniform_vec4(RHICmdBuffer *cmd, i32 location, f32 x, f32 y,
                              f32 z, f32 w) {
    f32 v[4];
    v[0] = x; v[1] = y; v[2] = z; v[3] = w;
    rhi_d3d12_stage_uniform(cmd, location, v, 16u);
}
void rhi_cmd_set_uniform_f32(RHICmdBuffer *cmd, i32 location, f32 v) {
    rhi_d3d12_stage_uniform(cmd, location, &v, 4u);
}
void rhi_cmd_set_uniform_i32(RHICmdBuffer *cmd, i32 location, i32 v) {
    rhi_d3d12_stage_uniform(cmd, location, &v, 4u);
}
void rhi_cmd_push_constants(RHICmdBuffer *cmd, u32 offset, const void *data,
                            u32 size) {
    RHI_D3D12Context *ctx = (RHI_D3D12Context *)cmd;
    ID3D12GraphicsCommandList *list;
    RHI_D3D12Pipeline *pd;
    if (ctx == NULL || data == NULL) return;
    list = rhi_d3d12_cmd_list(ctx);
    pd = (RHI_D3D12Pipeline *)ctx->bound_pipeline;
    if (list == NULL || pd == NULL || pd->push_param_index == UINT_MAX) return;
    /* R444 parity: writes outside the declared (clamped) range are dropped
     * with a warning, never silently truncated at flush. D3D12 additionally
     * requires 4-byte-aligned offset/size for root constants. */
    if (((offset | size) & 3u) != 0u ||
        !rhi_push_range_fits(offset, size, pd->push_size)) {
        LOG_WARN("D3D12: push_constants offset %u+%u outside declared %u "
                 "(or unaligned) — write dropped", offset, size, pd->push_size);
        return;
    }
    if (pd->is_compute)
        ID3D12GraphicsCommandList_SetComputeRoot32BitConstants(list,
            pd->push_param_index, size / 4u, data, offset / 4u);
    else
        ID3D12GraphicsCommandList_SetGraphicsRoot32BitConstants(list,
            pd->push_param_index, size / 4u, data, offset / 4u);
}
void rhi_cmd_set_uniform_bytes(RHICmdBuffer *cmd, i32 location,
                               const void *data, u32 size) {
    if (location < 0) return;
    rhi_cmd_push_constants(cmd, (u32)location, data, size);
}
i32 rhi_pipeline_get_uniform_location(RHIDevice *dev, RHIPipeline pipe,
                                      const char *name) {
    RHI_D3D12Pipeline *pd;
    UINT i;
    if (dev == NULL || name == NULL) return -1;
    pd = (RHI_D3D12Pipeline *)rhi_get_resource_typed(dev, pipe, RHI_RES_PIPELINE);
    if (pd == NULL) return -1;
    /* Name -> byte offset into the root constants (VK push-constant
     * convention, spec §4.4); the table is built from the sidecar's
     * `// rhi:uniform <name> <offset>` markers at pipeline creation. */
    for (i = 0u; i < pd->uniform_count; ++i)
        if (strcmp(pd->uniforms[i].name, name) == 0)
            return (i32)pd->uniforms[i].offset;
    return -1;
}

/* Reflection-driven bindings: a snapshot view over the pipeline's sidecar
 * uniform table (name -> byte offset into the 32BIT_CONSTANTS root param),
 * the same authority rhi_pipeline_get_uniform_location reads. Returned as an
 * owned copy so a destroyed pipeline cannot leave dangling name pointers. */
struct RHIPipelineBindings {
    char names[RHI_D3D12_MAX_UNIFORM_LOCS][SHADER_IO_NAME_MAX];
    i32  slots[RHI_D3D12_MAX_UNIFORM_LOCS];
    u32  count;
};
RHIPipelineBindings *rhi_pipeline_bindings_create(RHIDevice *dev, RHIPipeline pipe) {
    RHI_D3D12Pipeline *pd;
    struct RHIPipelineBindings *b;
    if (dev == NULL || !rhi_handle_valid(pipe)) return NULL;
    pd = (RHI_D3D12Pipeline *)rhi_get_resource_typed(dev, pipe, RHI_RES_PIPELINE);
    if (pd == NULL) return NULL;
    b = (struct RHIPipelineBindings *)calloc(1u, sizeof(*b));
    if (b == NULL) return NULL;
    for (u32 i = 0u; i < pd->uniform_count && b->count < RHI_D3D12_MAX_UNIFORM_LOCS; ++i) {
        memcpy(b->names[b->count], pd->uniforms[i].name, sizeof(b->names[0]));
        b->names[b->count][sizeof(b->names[0]) - 1u] = '\0';
        b->slots[b->count] = (i32)pd->uniforms[i].offset;
        b->count++;
    }
    return b;
}
void rhi_pipeline_bindings_destroy(RHIDevice *dev, RHIPipelineBindings *bindings) {
    (void)dev;
    free(bindings);
}
i32 rhi_pipeline_bindings_resolve(const RHIPipelineBindings *b, const char *name) {
    if (b == NULL || name == NULL) return -1;
    for (u32 i = 0u; i < b->count; ++i)
        if (strcmp(b->names[i], name) == 0) return b->slots[i];
    return -1;
}

/* ---- shadow map / cubemap / FBO ---- */
/* Mirrors the GL backend's shadow_map_create. The one D3D12-specific step is the
 * allocation: a D32_FLOAT resource cannot back a shader resource view at all,
 * so the atlas is created through the depth_samplable path, which allocates the
 * canonical DXGI_FORMAT_R32_TYPELESS and aliases it two ways over the same
 * bytes — a D32_FLOAT depth-stencil view here, and the R32_FLOAT SRV that
 * rhi_cmd_bind_shadow_texture hands the lighting pass. */
RHIShadowMap rhi_shadow_map_create(RHIDevice *dev, u32 width, u32 height) {
    RHIShadowMap sm;
    RHI_D3D12Context *ctx;
    RHI_D3D12Texture *depth;
    RHI_D3D12ShadowAtlas *sd;
    RHITextureDesc tdesc;
    D3D12_DEPTH_STENCIL_VIEW_DESC dsv_desc;
    u32 idx;
    memset(&sm, 0, sizeof(sm));
    /* An atlas that publishes no target must never be bound: the R358 gate —
     * binding it would clear whatever depth was left bound before it. */
    if (dev == NULL || !rhi_drawable_dimensions_valid(width, height)) return sm;
    ctx = (RHI_D3D12Context *)dev->backend_data;
    if (ctx == NULL || ctx->device_lost) return sm;

    memset(&tdesc, 0, sizeof(tdesc));
    tdesc.width = width;
    tdesc.height = height;
    tdesc.format = RHI_FORMAT_D32_FLOAT;
    tdesc.mip_levels = 1u;
    tdesc.data = NULL;
    sm.depth_tex = rhi_d3d12_texture_create_ex(dev, &tdesc, 1, 0u);
    if (!rhi_handle_valid(sm.depth_tex)) return sm;
    depth = (RHI_D3D12Texture *)rhi_get_resource_typed(dev, sm.depth_tex,
                                                       RHI_RES_TEXTURE);
    if (depth == NULL) goto fail_tex;

    sd = (RHI_D3D12ShadowAtlas *)calloc(1u, sizeof(*sd));
    if (sd == NULL) goto fail_tex;
    sd->dsv_slot = rhi_d3d12_descriptor_take(ctx, &ctx->dsv_alloc);
    if (sd->dsv_slot == UINT_MAX) {
        free(sd);
        goto fail_tex;
    }
    /* The typeless resource is viewed as D32_FLOAT on the depth-stencil
     * aspect; the NULL-desc default would guess from the typeless format and
     * fail, so the alias is named explicitly. */
    ZeroMemory(&dsv_desc, sizeof(dsv_desc));
    dsv_desc.Format = DXGI_FORMAT_D32_FLOAT;
    dsv_desc.ViewDimension = D3D12_DSV_DIMENSION_TEXTURE2D;
    dsv_desc.Flags = D3D12_DSV_FLAG_NONE;
    ID3D12Device_CreateDepthStencilView(ctx->device, depth->resource, &dsv_desc,
        rhi_d3d12_descriptor_cpu(&ctx->dsv_alloc, sd->dsv_slot));
    sd->width = width;
    sd->height = height;
    idx = rhi_alloc_slot(dev);
    dev->slots[idx].ptr = sd;
    dev->slots[idx].type = RHI_RES_FRAMEBUFFER;
    sm.fbo = rhi_make_handle(idx, dev->slots[idx].generation);
    sm.width = width;
    sm.height = height;
    return sm;

fail_tex:
    rhi_texture_destroy(dev, sm.depth_tex);
    memset(&sm, 0, sizeof(sm));
    return sm;
}
void rhi_shadow_map_destroy(RHIDevice *dev, RHIShadowMap *sm) {
    RHI_D3D12Context *ctx;
    RHI_D3D12ShadowAtlas *sd;
    UINT64 retire;
    if (dev == NULL || sm == NULL) return;
    ctx = (RHI_D3D12Context *)dev->backend_data;
    if (rhi_handle_valid(sm->depth_tex)) rhi_texture_destroy(dev, sm->depth_tex);
    if (rhi_handle_valid(sm->fbo)) {
        sd = (RHI_D3D12ShadowAtlas *)rhi_get_resource_typed(dev, sm->fbo,
                                                            RHI_RES_FRAMEBUFFER);
        if (sd != NULL && ctx != NULL && sd->dsv_slot != UINT_MAX) {
            /* A command list may still hold this descriptor, so the slot goes
             * back through the fence-retire path, not straight to the
             * allocator — same rule the offscreen FBO teardown follows. */
            retire = rhi_d3d12_retire_fence(ctx);
            rhi_d3d12_descriptor_give_back(&ctx->dsv_alloc, sd->dsv_slot,
                                           retire);
        }
        free(sd);
        rhi_free_slot(dev, sm->fbo);
    }
    sm->fbo = RHI_HANDLE_NULL;
    sm->depth_tex = RHI_HANDLE_NULL;
}
void rhi_cmd_bind_shadow_map(RHICmdBuffer *cmd, RHIShadowMap *sm) {
    RHI_D3D12Context *ctx = (RHI_D3D12Context *)cmd;
    ID3D12GraphicsCommandList *list;
    RHI_D3D12ShadowAtlas *sd;
    RHI_D3D12Texture *depth;
    D3D12_CPU_DESCRIPTOR_HANDLE dsv;
    D3D12_VIEWPORT vp;
    D3D12_RECT sc;
    /* R358: never touch the depth attachment that is still bound when the
     * atlas is missing — that would clear the caller's frame. */
    if (ctx == NULL || g_current_device == NULL || sm == NULL) return;
    if (!rhi_handle_valid(sm->fbo)) return;
    sd = (RHI_D3D12ShadowAtlas *)rhi_get_resource_typed(g_current_device,
                                                        sm->fbo,
                                                        RHI_RES_FRAMEBUFFER);
    if (sd == NULL || sd->dsv_slot == UINT_MAX) return;
    depth = (RHI_D3D12Texture *)rhi_get_resource_typed(g_current_device,
                                                       sm->depth_tex,
                                                       RHI_RES_TEXTURE);
    if (depth == NULL || depth->resource == NULL) return;
    list = rhi_d3d12_cmd_list(ctx);
    if (list == NULL) return;
    if (depth->state != D3D12_RESOURCE_STATE_DEPTH_WRITE) {
        rhi_d3d12_transition(list, depth->resource, depth->state,
                             D3D12_RESOURCE_STATE_DEPTH_WRITE);
        depth->state = D3D12_RESOURCE_STATE_DEPTH_WRITE;
    }
    dsv = rhi_d3d12_descriptor_cpu(&ctx->dsv_alloc, sd->dsv_slot);
    /* Depth-only pass: the shadow-depth PSO already declares zero render
     * targets for is_shadow_depth (rhi_d3d12_create_graphics_pso), so zero
     * RTVs is what it expects. */
    ID3D12GraphicsCommandList_OMSetRenderTargets(list, 0u, NULL, TRUE, &dsv);
    ctx->bound_rtv_count = 0u;
    ctx->bound_dsv = dsv;
    ctx->bound_dsv_valid = 1u;
    /* Non-flipped, matching rhi_cmd_set_shadow_viewport — the shadow pass uses
     * a top-left-origin viewport, so it must NOT go through the Y-flipping
     * rhi_d3d12_set_full_target_viewport the colour passes use. */
    vp.TopLeftX = 0.0f; vp.TopLeftY = 0.0f;
    vp.Width = (f32)sd->width; vp.Height = (f32)sd->height;
    vp.MinDepth = 0.0f; vp.MaxDepth = 1.0f;
    ID3D12GraphicsCommandList_RSSetViewports(list, 1u, &vp);
    sc.left = 0; sc.top = 0;
    sc.right = (LONG)sd->width; sc.bottom = (LONG)sd->height;
    ID3D12GraphicsCommandList_RSSetScissorRects(list, 1u, &sc);
    /* R618 "bind == fresh": the whole atlas clears to 1.0 with the scissor
     * wide open. Per-cascade quadrants are applied afterwards by
     * rhi_cmd_set_shadow_viewport. */
    ID3D12GraphicsCommandList_ClearDepthStencilView(list, dsv,
        D3D12_CLEAR_FLAG_DEPTH, 1.0f, 0u, 0u, NULL);
}
void rhi_cmd_unbind_shadow_map(RHICmdBuffer *cmd, u32 screen_w, u32 screen_h) {
    RHI_D3D12Context *ctx = (RHI_D3D12Context *)cmd;
    ID3D12GraphicsCommandList *list;
    D3D12_CPU_DESCRIPTOR_HANDLE rtv;
    D3D12_VIEWPORT vp;
    D3D12_RECT sc;
    if (ctx == NULL || g_current_device == NULL || !ctx->swapchain_ready) return;
    list = rhi_d3d12_cmd_list(ctx);
    if (list == NULL) return;
    /* D3D12's "target 0" is the swapchain back buffer; the shadow depth buffer
     * is not part of it, which is the same shape as the GL bind-FBO-0
     * restore and the same shape as rhi_offscreen_fbo_unbind. */
    rtv = rhi_d3d12_descriptor_cpu(&ctx->rtv_alloc,
                                   ctx->swapchain.rtv_slots[ctx->swapchain.current_index]);
    ID3D12GraphicsCommandList_OMSetRenderTargets(list, 1u, &rtv, FALSE, NULL);
    ctx->bound_rtvs[0] = rtv;
    ctx->bound_rtv_formats[0] = ctx->swapchain.format;
    ctx->bound_rtv_count = 1u;
    ctx->bound_dsv_valid = 0u;
    vp.TopLeftX = 0.0f; vp.TopLeftY = 0.0f;
    vp.Width = (f32)screen_w; vp.Height = (f32)screen_h;
    vp.MinDepth = 0.0f; vp.MaxDepth = 1.0f;
    ID3D12GraphicsCommandList_RSSetViewports(list, 1u, &vp);
    sc.left = 0; sc.top = 0; sc.right = (LONG)screen_w; sc.bottom = (LONG)screen_h;
    ID3D12GraphicsCommandList_RSSetScissorRects(list, 1u, &sc);
}
void rhi_cmd_clear_depth(RHICmdBuffer *cmd) {
    RHI_D3D12Context *ctx = (RHI_D3D12Context *)cmd;
    ID3D12GraphicsCommandList *list = rhi_d3d12_cmd_list(ctx);
    if (list == NULL || !ctx->bound_dsv_valid) return;
    ID3D12GraphicsCommandList_ClearDepthStencilView(list, ctx->bound_dsv,
        D3D12_CLEAR_FLAG_DEPTH, 1.0f, 0u, 0u, NULL);
}
/* R654: colour cubemap (IBL env / irradiance / prefilter). An ordinary
 * RHI_D3D12Texture -- six slices, mip chain, is_cube -- that lives in a
 * RHI_RES_CUBEMAP slot, so RHICubemap handles never pass for 2D textures.
 * RGBA16F is created UAV-capable: the IBL bake writes every face/mip from
 * compute (rhi_cmd_bind_image_cubemap_face). Faces are uploaded at create
 * when given (mip 0, native bytes per rhi.h R625). */
static RHI_D3D12Texture *rhi_d3d12_cube_tex(RHIHandle handle) {
    if (g_current_device == NULL) return NULL;
    return (RHI_D3D12Texture *)rhi_get_resource_typed(g_current_device, handle,
                                                      RHI_RES_CUBEMAP);
}
RHICubemap rhi_cubemap_create(RHIDevice *dev, const RHICubemapDesc *desc) {
    RHI_D3D12Context *ctx;
    RHI_D3D12Texture *td;
    RHITextureDesc tdesc;
    RHITexture tex;
    RHIResourceSlot *slot;
    u32 f;
    if (dev == NULL || !rhi_cubemap_desc_validate(desc)) return RHI_HANDLE_NULL;
    ctx = (RHI_D3D12Context *)dev->backend_data;
    if (ctx == NULL || ctx->device_lost) return RHI_HANDLE_NULL;
    memset(&tdesc, 0, sizeof(tdesc));
    tdesc.width = desc->size;
    tdesc.height = desc->size;
    tdesc.format = desc->format == RHI_FORMAT_R16G16B16A16_SFLOAT
                       ? RHI_FORMAT_R16G16B16A16_SFLOAT : RHI_FORMAT_R8G8B8A8_UNORM;
    tdesc.mip_levels = desc->mip_levels == 0u ? 1u : desc->mip_levels;
    tex = rhi_d3d12_texture_create_ex(dev, &tdesc, 0, 6u);
    td = (RHI_D3D12Texture *)rhi_get_resource_typed(dev, tex, RHI_RES_TEXTURE);
    if (td == NULL) return RHI_HANDLE_NULL;
    td->is_cube = 1u;
    slot = &dev->slots[tex.index];
    slot->type = RHI_RES_CUBEMAP;
    for (f = 0u; f < 6u; ++f) {
        UINT bpp = rhi_d3d12_format_bytes_per_pixel(tdesc.format);
        UINT64 row_bytes = (UINT64)desc->size * bpp;
        D3D12_RESOURCE_DESC rd;
        D3D12_PLACED_SUBRESOURCE_FOOTPRINT fp;
        UINT rows;
        UINT64 rsz, total;
        ID3D12Resource *staging;
        void *mapped = NULL;
        UINT sub = f * td->mip_levels;
        if (desc->faces[f] == NULL) continue;
        ID3D12Resource_GetDesc(td->resource, &rd);
        ID3D12Device_GetCopyableFootprints(ctx->device, &rd, sub, 1u, 0u, &fp,
                                           &rows, &rsz, &total);
        staging = rhi_d3d12_staging_buffer(ctx, D3D12_HEAP_TYPE_UPLOAD, total);
        if (staging == NULL) continue;
        if (SUCCEEDED(ID3D12Resource_Map(staging, 0u, NULL, &mapped))) {
            UINT r;
            for (r = 0u; r < rows; ++r)
                memcpy((u8 *)mapped + fp.Offset + (UINT64)r * fp.Footprint.RowPitch,
                       (const u8 *)desc->faces[f] + (UINT64)r * row_bytes,
                       (size_t)row_bytes);
            ID3D12Resource_Unmap(staging, 0u, NULL);
            if (SUCCEEDED(rhi_d3d12_oneshot_begin(ctx))) {
                D3D12_TEXTURE_COPY_LOCATION dst_loc, src_loc;
                ZeroMemory(&dst_loc, sizeof(dst_loc));
                dst_loc.pResource = td->resource;
                dst_loc.Type = D3D12_TEXTURE_COPY_TYPE_SUBRESOURCE_INDEX;
                dst_loc.SubresourceIndex = sub;
                ZeroMemory(&src_loc, sizeof(src_loc));
                src_loc.pResource = staging;
                src_loc.Type = D3D12_TEXTURE_COPY_TYPE_PLACED_FOOTPRINT;
                src_loc.PlacedFootprint = fp;
                rhi_d3d12_transition(ctx->upload_list, td->resource, td->state,
                                     D3D12_RESOURCE_STATE_COPY_DEST);
                ID3D12GraphicsCommandList_CopyTextureRegion(ctx->upload_list,
                    &dst_loc, 0u, 0u, 0u, &src_loc, NULL);
                rhi_d3d12_transition(ctx->upload_list, td->resource,
                                     D3D12_RESOURCE_STATE_COPY_DEST, td->state);
                (void)rhi_d3d12_oneshot_flush(ctx);
            }
        }
        ID3D12Resource_Release(staging);
    }
    return tex;
}
void rhi_cubemap_destroy(RHIDevice *dev, RHICubemap cm) {
    RHI_D3D12Texture *td;
    if (dev == NULL) return;
    td = (RHI_D3D12Texture *)rhi_get_resource_typed(dev, cm, RHI_RES_CUBEMAP);
    if (td == NULL) return;
    rhi_d3d12_release_deferred((RHI_D3D12Context *)dev->backend_data,
                               (IUnknown **)&td->resource);
    free(td);
    rhi_free_slot(dev, cm);
}
/* All faces/mips back to the shader-read state, on the upload list (the
 * rhi.h contract: a device-idle one-time submit after the bake). */
void rhi_cubemap_transition_to_read(RHIDevice *dev, RHICubemap cm) {
    RHI_D3D12Context *ctx;
    RHI_D3D12Texture *td;
    const D3D12_RESOURCE_STATES read_state =
        D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE |
        D3D12_RESOURCE_STATE_NON_PIXEL_SHADER_RESOURCE;
    if (dev == NULL) return;
    ctx = (RHI_D3D12Context *)dev->backend_data;
    if (ctx == NULL || ctx->device_lost) return;
    td = (RHI_D3D12Texture *)rhi_get_resource_typed(dev, cm, RHI_RES_CUBEMAP);
    if (td == NULL) return;
    if (!td->mip_split && td->state == read_state) return;
    if (FAILED(rhi_d3d12_oneshot_begin(ctx))) return;
    if (td->mip_split) rhi_d3d12_tex_unify(ctx->upload_list, td, read_state);
    else rhi_d3d12_transition(ctx->upload_list, td->resource, td->state, read_state);
    if (rhi_d3d12_oneshot_flush(ctx) == RHI_RESULT_OK) {
        td->state = read_state;
        td->mip_split = 0u;
    }
}
void rhi_texture_transition_to_read(RHIDevice *dev, RHITexture tex) {
    RHI_D3D12Context *ctx;
    RHI_D3D12Texture *td;
    D3D12_RESOURCE_STATES read_state;
    if (dev == NULL) return;
    ctx = (RHI_D3D12Context *)dev->backend_data;
    if (ctx == NULL || ctx->device_lost) return;
    td = (RHI_D3D12Texture *)rhi_get_resource_typed(dev, tex, RHI_RES_TEXTURE);
    if (td == NULL) return;
    read_state = D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE |
                 D3D12_RESOURCE_STATE_NON_PIXEL_SHADER_RESOURCE;
    if (!td->mip_split && td->state == read_state) return;
    if (FAILED(rhi_d3d12_oneshot_begin(ctx))) return;
    if (td->mip_split) rhi_d3d12_tex_unify(ctx->upload_list, td, read_state);
    else rhi_d3d12_transition(ctx->upload_list, td->resource, td->state, read_state);
    if (rhi_d3d12_oneshot_flush(ctx) == RHI_RESULT_OK) {
        td->state = read_state;
        td->mip_split = 0u;
    }
}
/* R654: a colour cube's TEXTURECUBE SRV at register(t<unit>). The cube is
 * an RHI_D3D12Texture in an RHI_RES_CUBEMAP slot; rhi_d3d12_bind_texture_td
 * is the per-unit binder rhi_cmd_bind_texture wraps. */
static void rhi_d3d12_bind_texture_td(RHICmdBuffer *cmd, RHI_D3D12Texture *td,
                                      u32 unit);
void rhi_cmd_bind_cubemap(RHICmdBuffer *cmd, RHICubemap cm,
                          RHISampler sampler, u32 unit) {
    RHI_D3D12Texture *td = rhi_d3d12_cube_tex(cm);
    (void)sampler;
    if (td != NULL) rhi_d3d12_bind_texture_td(cmd, td, unit);
}
void rhi_cmd_set_depth_func_less_or_equal(RHICmdBuffer *cmd) { (void)cmd; }
void rhi_cmd_set_depth_func_less(RHICmdBuffer *cmd) { (void)cmd; }
void rhi_cmd_set_depth_mask(RHICmdBuffer *cmd, bool enabled) {
    (void)cmd; (void)enabled;
}
void rhi_cmd_set_cull_face(RHICmdBuffer *cmd, bool enabled) {
    (void)cmd; (void)enabled;
}

/* ---- buffers / texel (Task 5 host-side ops) ---- */
/* R614: texel buffers (units 5 and 6).
 *
 * This was a no-op stub, which made instanced.vert and skinned.vert
 * unwritable on D3D12 no matter how correct a sidecar was: both declare
 * layout(binding = 5) uniform samplerBuffer, and the GL backend's
 * rhi_cmd_bind_texel_buffers is what puts data there. Without it the shader
 * reads an unbound table.
 *
 * D3D12 has no texel buffer. The equivalent is a raw buffer SRV:
 * D3D12_SRV_DIMENSION_BUFFER, and the shader-side spelling is
 * StructuredBuffer<float4> at register tN -- which the HLSL reflection
 * already maps to an SRV range, so image_root_params[5] / [6] are populated
 * by the sidecar declaring it and nothing else has to change.
 *
 * Stride: GLSL's texelFetch(u_instances, i) indexes vec4 elements, and
 * instanced.vert reads the model matrix as eight separate fetches
 * (idx + 0 .. idx + 3, and + 4 .. + 7 for prev_model under FORWARD_MRT), so
 * the element is 16 bytes and NumElements is size/16. A StructuredBuffer
 * declared with any other element type would silently mis-index here, which
 * is why the divisor is fixed rather than taken from the shader: the engine
 * only ever uploads vec4 instance/joint rows.
 *
 * Read-only SRV, so no UAV descriptor is created. Buffers here are
 * UPLOAD-heap and CPU-mapped, so the transition is from COMMON to a combined
 * read state.
 */
/* R614: texel buffers (units 5 and 6).
 *
 * This was a no-op stub, which made instanced.vert and skinned.vert
 * unwritable on D3D12 no matter how correct a sidecar was: both declare
 * layout(binding = 5) uniform samplerBuffer, and the GL backend's
 * rhi_cmd_bind_texel_buffers is what puts data there. Without it the shader
 * reads an unbound table.
 *
 * D3D12 has no texel buffer. The equivalent is a raw buffer SRV:
 * D3D12_SRV_DIMENSION_BUFFER, and the shader-side spelling is
 * StructuredBuffer<float4> at register tN -- which the HLSL reflection
 * already maps to an SRV range, so image_root_params[5] / [6] are populated
 * by the sidecar declaring it and nothing else has to change.
 *
 * Stride: GLSL's texelFetch(u_instances, i) indexes vec4 elements, and
 * instanced.vert reads the model matrix as eight separate fetches
 * (idx + 0 .. idx + 3, and + 4 .. + 7 for prev_model under FORWARD_MRT), so
 * the element is 16 bytes and NumElements is size/16. A StructuredBuffer
 * declared with any other element type would silently mis-index here, which
 * is why the divisor is fixed rather than taken from the shader: the engine
 * only ever uploads vec4 instance/joint rows.
 *
 * Read-only SRV, so no UAV descriptor is created. Buffers here are
 * UPLOAD-heap and CPU-mapped, so the transition is from COMMON to a combined
 * read state.
 */
void rhi_cmd_bind_texel_buffers(RHICmdBuffer *cmd, RHIBuffer buf0,
                                RHIBuffer buf1) {
    RHI_D3D12Context *ctx = (RHI_D3D12Context *)cmd;
    ID3D12GraphicsCommandList *list;
    RHI_D3D12Pipeline *pd;
    RHIBuffer handles[2];
    u32 unit;
    if (ctx == NULL || g_current_device == NULL) return;
    handles[0] = buf0;
    handles[1] = buf1;
    for (unit = 5u; unit <= 6u; ++unit) {
        RHI_D3D12Buffer *bd;
        D3D12_SHADER_RESOURCE_VIEW_DESC srv;
        D3D12_RESOURCE_STATES read_state;
        D3D12_GPU_DESCRIPTOR_HANDLE gpu;
        UINT root_param;
        UINT slot;
        list = rhi_d3d12_cmd_list(ctx);
        pd = (RHI_D3D12Pipeline *)ctx->bound_pipeline;
        if (list == NULL || pd == NULL) return;
        /* An unset handle leaves the previous draw's descriptor in place, the
         * same contract every other binder here follows -- there is no unset
         * state in D3D12, which is why the material binder binds a white
         * fallback instead of clearing. */
        if (!rhi_handle_valid(handles[unit - 5u])) continue;
        bd = (RHI_D3D12Buffer *)rhi_get_resource_typed(g_current_device,
                                    handles[unit - 5u], RHI_RES_BUFFER);
        if (bd == NULL || bd->resource == NULL || bd->size < 16u) continue;
        root_param = pd->image_root_params[unit];
        if (root_param == UINT_MAX) continue;
        if (ctx->frame_srv_count >= RHI_D3D12_CBV_SRV_UAV_CAPACITY) return;
        slot = rhi_d3d12_descriptor_take(ctx, &ctx->cbv_srv_uav_alloc);
        if (slot == UINT_MAX) {
            LOG_WARN("D3D12: SRV descriptor heap exhausted");
            return;
        }
        ZeroMemory(&srv, sizeof(srv));
        srv.Format = DXGI_FORMAT_UNKNOWN;
        srv.ViewDimension = D3D12_SRV_DIMENSION_BUFFER;
        srv.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
        /* This SDK's D3D12_BUFFER_SRV carries FirstElement /
         * StructureByteStride / Flags rather than the older FirstBeforeUpdate
         * pair. StructureByteStride is what makes the shader's float4
         * indexing exact, so it is stated rather than left at 0. */
        srv.Buffer.FirstElement = 0u;
        srv.Buffer.NumElements = (UINT)(bd->size / 16u);
        srv.Buffer.StructureByteStride = 16u;
        srv.Buffer.Flags = D3D12_BUFFER_SRV_FLAG_NONE;
        /* An UPLOAD-heap buffer written with rhi_cmd_update_buffer earlier in
         * this frame is read through that write's snapshot (see
         * rhi_d3d12_record_buffer_write). main.c rewrites the instance buffer
         * once per mesh and binds it here before each draw; viewing the raw
         * resource would give every mesh the LAST mesh's rows, which is what
         * drew the large garbage triangles in the R638 demo. */
        ID3D12Device_CreateShaderResourceView(ctx->device,
            rhi_d3d12_buffer_view_source(ctx, bd), &srv, rhi_d3d12_descriptor_cpu(&ctx->cbv_srv_uav_alloc, slot));
        ctx->frame_srv_slots[ctx->frame_srv_count++] = slot;
        read_state = D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE |
                     D3D12_RESOURCE_STATE_NON_PIXEL_SHADER_RESOURCE;
        /* R636: an UPLOAD-heap buffer lives in GENERIC_READ for its whole
         * life and may not be transitioned; GENERIC_READ already implies
         * both shader-read states, so the barrier is not just illegal there
         * -- it is unnecessary. */
        if (bd->device_local && bd->state != read_state) {
            rhi_d3d12_transition(list, bd->resource, bd->state, read_state);
            bd->state = read_state;
        }
        gpu = rhi_d3d12_descriptor_gpu(&ctx->cbv_srv_uav_alloc, slot);
        if (pd->is_compute)
            ID3D12GraphicsCommandList_SetComputeRootDescriptorTable(list,
                                                                    root_param, gpu);
        else
            ID3D12GraphicsCommandList_SetGraphicsRootDescriptorTable(list,
                                                                    root_param, gpu);
    }
}
void rhi_buffer_update(RHIDevice *dev, RHIBuffer buf, const void *data,
                       usize size) {
    rhi_buffer_update_region(dev, buf, 0u, data, size);
}
void rhi_buffer_update_region(RHIDevice *dev, RHIBuffer buf, usize offset,
                              const void *data, usize size) {
    RHI_D3D12Context *ctx;
    RHI_D3D12Buffer *bd;
    if (dev == NULL || data == NULL || size == 0u) return;
    ctx = (RHI_D3D12Context *)dev->backend_data;
    if (ctx == NULL || ctx->device_lost) return;
    bd = (RHI_D3D12Buffer *)rhi_get_resource_typed(dev, buf, RHI_RES_BUFFER);
    if (bd == NULL || offset >= (usize)bd->size) return;
    if (size > (usize)bd->size - offset) size = (usize)bd->size - offset;
    if (!bd->device_local) {
        /* UPLOAD heap: host write through a transient Map. A host write is
         * immediate, so it supersedes any recorded-write snapshot this frame
         * made: later binds read the buffer itself again. */
        void *mapped = NULL;
        bd->alias_resource = NULL;
        if (FAILED(ID3D12Resource_Map(bd->resource, 0u, NULL, &mapped))) return;
        memcpy((u8 *)mapped + offset, data, size);
        ID3D12Resource_Unmap(bd->resource, 0u, NULL);
        return;
    }
    (void)rhi_d3d12_buffer_stage_upload(ctx, bd, (UINT64)offset, data,
                                        (UINT64)size);
}
bool rhi_buffer_read(RHIDevice *dev, RHIBuffer buf, void *dst, usize offset,
                     usize size) {
    RHI_D3D12Context *ctx;
    RHI_D3D12Buffer *bd;
    if (dev == NULL || dst == NULL || size == 0u) return false;
    ctx = (RHI_D3D12Context *)dev->backend_data;
    if (ctx == NULL || ctx->device_lost) return false;
    bd = (RHI_D3D12Buffer *)rhi_get_resource_typed(dev, buf, RHI_RES_BUFFER);
    if (bd == NULL || offset >= (usize)bd->size) return false;
    if (size > (usize)bd->size - offset) size = (usize)bd->size - offset;
    if (bd->mapped != NULL) {
        memcpy(dst, (const u8 *)bd->mapped + offset, size);
        return true;
    }
    if (!bd->device_local) {
        /* UPLOAD heaps are host-readable (write-combined; slow but legal).
         * R652: after a GPU copy into it, the READBACK twin holds the
         * bytes (see RHI_D3D12Buffer.readback). */
        ID3D12Resource *src = bd->readback != NULL ? bd->readback : bd->resource;
        D3D12_RANGE read_range;
        D3D12_RANGE none = { 0u, 0u };
        void *mapped = NULL;
        read_range.Begin = (SIZE_T)offset;
        read_range.End = (SIZE_T)(offset + size);
        if (FAILED(ID3D12Resource_Map(src, 0u, &read_range, &mapped)))
            return false;
        memcpy(dst, (const u8 *)mapped + offset, size);
        ID3D12Resource_Unmap(src, 0u, bd->readback != NULL ? &none : NULL);
        return true;
    }
    /* DEFAULT heap: READBACK staging + one-shot copy + Map/memcpy/Unmap. */
    {
        ID3D12Resource *staging =
            rhi_d3d12_staging_buffer(ctx, D3D12_HEAP_TYPE_READBACK, (UINT64)size);
        void *mapped = NULL;
        RHIResult rr;
        D3D12_RANGE read_range;
        bool ok = false;
        if (staging == NULL) return false;
        if (FAILED(rhi_d3d12_oneshot_begin(ctx))) {
            ID3D12Resource_Release(staging);
            return false;
        }
        rhi_d3d12_transition(ctx->upload_list, bd->resource, bd->state,
                             D3D12_RESOURCE_STATE_COPY_SOURCE);
        ID3D12GraphicsCommandList_CopyBufferRegion(ctx->upload_list, staging,
            0u, bd->resource, (UINT64)offset, (UINT64)size);
        rhi_d3d12_transition(ctx->upload_list, bd->resource,
                             D3D12_RESOURCE_STATE_COPY_SOURCE, bd->state);
        rr = rhi_d3d12_oneshot_flush(ctx);
        if (rr != RHI_RESULT_OK) {
            ID3D12Resource_Release(staging);
            return false;
        }
        read_range.Begin = 0u;
        read_range.End = (SIZE_T)size;
        if (SUCCEEDED(ID3D12Resource_Map(staging, 0u, &read_range, &mapped))) {
            memcpy(dst, mapped, size);
            ID3D12Resource_Unmap(staging, 0u, NULL);
            ok = true;
        }
        ID3D12Resource_Release(staging);
        return ok;
    }
}
/* C-BUF-3: a recorded buffer write is ordered against the draws/dispatches
 * recorded around it. Both entry points used to write through the host
 * (rhi_buffer_update_region), so every write in a frame landed before the
 * frame's list ran and the GPU saw only the last one -- harmless while
 * nothing read storage buffers on D3D12, wrong as soon as compact_draws runs
 * once per shadow cascade with fresh visibility.
 *
 * DEFAULT heap: the bytes go into a per-write UPLOAD staging buffer and are
 * copied by the frame's own command list, between barriers, so they take
 * effect exactly at their place in the list.
 *
 * UPLOAD heap: such a resource is permanently GENERIC_READ and can never be
 * a copy destination, so the in-list copy is impossible. The staging buffer
 * itself becomes the buffer's view source for the rest of the frame
 * (alias_resource): every later bind this frame reads that snapshot, earlier
 * binds keep the previous one. The bytes are also written through the host
 * so the buffer's own contents end up as the last write, which is what a
 * host read after the frame expects. */
static ID3D12Resource *rhi_d3d12_frame_staging(RHI_D3D12Context *ctx,
                                               const void *data, u32 fill,
                                               usize size) {
    UINT slot = ctx->frame_parity & 1u;
    ID3D12Resource *staging;
    void *mapped = NULL;
    if (ctx->frame_staging_count[slot] == ctx->frame_staging_cap[slot]) {
        UINT cap = ctx->frame_staging_cap[slot] ? ctx->frame_staging_cap[slot] * 2u : 16u;
        ID3D12Resource **grown = (ID3D12Resource **)realloc(
            ctx->frame_staging[slot], (size_t)cap * sizeof(*grown));
        if (grown == NULL) return NULL;
        ctx->frame_staging[slot] = grown;
        ctx->frame_staging_cap[slot] = cap;
    }
    staging = rhi_d3d12_staging_buffer(ctx, D3D12_HEAP_TYPE_UPLOAD, (UINT64)size);
    if (staging == NULL) return NULL;
    if (FAILED(ID3D12Resource_Map(staging, 0u, NULL, &mapped))) {
        ID3D12Resource_Release(staging);
        return NULL;
    }
    if (data != NULL) {
        memcpy(mapped, data, size);
    } else {
        usize i;
        for (i = 0u; i < size; i += 4u) memcpy((u8 *)mapped + i, &fill, 4u);
    }
    ID3D12Resource_Unmap(staging, 0u, NULL);
    ctx->frame_staging[slot][ctx->frame_staging_count[slot]++] = staging;
    return staging;
}

static void rhi_d3d12_record_buffer_write(RHICmdBuffer *cmd, RHIBuffer buf,
                                          usize offset, const void *data,
                                          u32 fill, usize size) {
    RHI_D3D12Context *ctx = (RHI_D3D12Context *)cmd;
    ID3D12GraphicsCommandList *list;
    RHI_D3D12Buffer *bd;
    ID3D12Resource *staging;
    if (ctx == NULL || g_current_device == NULL || size == 0u) return;
    list = rhi_d3d12_cmd_list(ctx);
    if (list == NULL) return;
    bd = (RHI_D3D12Buffer *)rhi_get_resource_typed(g_current_device, buf,
                                                    RHI_RES_BUFFER);
    if (bd == NULL || bd->resource == NULL || offset >= (usize)bd->size) return;
    if (size > (usize)bd->size - offset) size = (usize)bd->size - offset;
    if (!bd->device_local) {
        /* The snapshot has to be the whole buffer: a view over it replaces
         * the buffer for every element, not just the written range. It is
         * padded to 256 bytes because a CBV over it covers the 256-rounded
         * size, as rhi_cmd_bind_uniform_buffer declares for the original. */
        usize snap_size = ((usize)bd->size + 255u) & ~(usize)255u;
        u8 *whole = (u8 *)calloc(1u, snap_size);
        void *mapped = NULL;
        if (whole == NULL) return;
        if (FAILED(ID3D12Resource_Map(bd->resource, 0u, NULL, &mapped))) {
            free(whole);
            return;
        }
        if (bd->alias_resource != NULL && bd->alias_frame == ctx->debug_frame) {
            void *prev = NULL;
            if (SUCCEEDED(ID3D12Resource_Map(bd->alias_resource, 0u, NULL, &prev))) {
                memcpy(whole, prev, (size_t)bd->size);
                ID3D12Resource_Unmap(bd->alias_resource, 0u, NULL);
            } else {
                memcpy(whole, mapped, (size_t)bd->size);
            }
        } else {
            memcpy(whole, mapped, (size_t)bd->size);
        }
        if (data != NULL) {
            memcpy(whole + offset, data, size);
        } else {
            usize i;
            for (i = 0u; i < size; i += 4u) memcpy(whole + offset + i, &fill, 4u);
        }
        memcpy(mapped, whole, (size_t)bd->size);
        ID3D12Resource_Unmap(bd->resource, 0u, NULL);
        staging = rhi_d3d12_frame_staging(ctx, whole, 0u, snap_size);
        free(whole);
        if (staging == NULL) return;
        bd->alias_resource = staging;
        bd->alias_frame = ctx->debug_frame;
        return;
    }
    staging = rhi_d3d12_frame_staging(ctx, data, fill, size);
    if (staging == NULL) return;
    rhi_d3d12_transition(list, bd->resource, bd->state,
                         D3D12_RESOURCE_STATE_COPY_DEST);
    ID3D12GraphicsCommandList_CopyBufferRegion(list, bd->resource,
        (UINT64)offset, staging, 0u, (UINT64)size);
    rhi_d3d12_transition(list, bd->resource, D3D12_RESOURCE_STATE_COPY_DEST,
                         bd->state);
}
void rhi_cmd_fill_buffer(RHICmdBuffer *cmd, RHIBuffer buf, usize offset,
                         usize size, u32 value) {
    if (cmd == NULL || size == 0u || ((offset | size) & 3u) != 0u) return;
    rhi_d3d12_record_buffer_write(cmd, buf, offset, NULL, value, size);
}
void rhi_cmd_update_buffer(RHICmdBuffer *cmd, RHIBuffer buf, usize offset,
                           const void *data, usize size) {
    if (cmd == NULL || data == NULL || size == 0u) return;
    rhi_d3d12_record_buffer_write(cmd, buf, offset, data, 0u, size);
}

void *rhi_buffer_map(RHIDevice *dev, RHIBuffer buf) {
    RHI_D3D12Buffer *bd;
    void *mapped = NULL;
    if (dev == NULL) return NULL;
    bd = (RHI_D3D12Buffer *)rhi_get_resource_typed(dev, buf, RHI_RES_BUFFER);
    if (bd == NULL || bd->mapped != NULL) return NULL;
    if (bd->device_local) {
        LOG_WARN("D3D12: rhi_buffer_map on DEFAULT-heap buffer; use rhi_buffer_read");
        return NULL;
    }
    if (FAILED(ID3D12Resource_Map(bd->readback != NULL ? bd->readback : bd->resource,
                                  0u, NULL, &mapped)))
        return NULL;
    bd->mapped = mapped;
    return mapped;
}
void rhi_buffer_unmap(RHIDevice *dev, RHIBuffer buf) {
    RHI_D3D12Buffer *bd;
    if (dev == NULL) return;
    bd = (RHI_D3D12Buffer *)rhi_get_resource_typed(dev, buf, RHI_RES_BUFFER);
    if (bd == NULL || bd->mapped == NULL) return;
    {
        D3D12_RANGE none = { 0u, 0u };
        if (bd->readback != NULL)
            ID3D12Resource_Unmap(bd->readback, 0u, &none);
        else
            ID3D12Resource_Unmap(bd->resource, 0u, NULL);
    }
    bd->mapped = NULL;
}
void rhi_cmd_copy_buffer(RHICmdBuffer *cmd, RHIBuffer src, RHIBuffer dst,
                         usize size) {
    RHI_D3D12Context *ctx = (RHI_D3D12Context *)cmd;
    ID3D12GraphicsCommandList *list;
    RHI_D3D12Buffer *sbd;
    RHI_D3D12Buffer *dbd;
    if (ctx == NULL || g_current_device == NULL || size == 0u) return;
    list = rhi_d3d12_cmd_list(ctx);
    if (list == NULL) return;
    sbd = (RHI_D3D12Buffer *)rhi_get_resource_typed(g_current_device, src,
                                                    RHI_RES_BUFFER);
    dbd = (RHI_D3D12Buffer *)rhi_get_resource_typed(g_current_device, dst,
                                                    RHI_RES_BUFFER);
    if (sbd == NULL || dbd == NULL) return;
    if (size > (usize)sbd->size) size = (usize)sbd->size;
    if (size > (usize)dbd->size) size = (usize)dbd->size;
    if (!dbd->device_local) {
        /* R652: GPU -> host staging (gpucull's vis-flag readback). The
         * READBACK twin stays in COPY_DEST for its whole life. */
        if (!sbd->device_local) return;
        if (dbd->readback == NULL) {
            dbd->readback = rhi_d3d12_staging_buffer(ctx, D3D12_HEAP_TYPE_READBACK,
                                                     dbd->size);
            if (dbd->readback == NULL) return;
        }
        rhi_d3d12_transition(list, sbd->resource, sbd->state,
                             D3D12_RESOURCE_STATE_COPY_SOURCE);
        ID3D12GraphicsCommandList_CopyBufferRegion(list, dbd->readback, 0u,
                                                   sbd->resource, 0u, (UINT64)size);
        rhi_d3d12_transition(list, sbd->resource, D3D12_RESOURCE_STATE_COPY_SOURCE,
                             sbd->state);
        return;
    }
    rhi_d3d12_transition(list, sbd->resource, sbd->state,
                         D3D12_RESOURCE_STATE_COPY_SOURCE);
    rhi_d3d12_transition(list, dbd->resource, dbd->state,
                         D3D12_RESOURCE_STATE_COPY_DEST);
    ID3D12GraphicsCommandList_CopyBufferRegion(list, dbd->resource, 0u,
                                               sbd->resource, 0u, (UINT64)size);
    rhi_d3d12_transition(list, sbd->resource, D3D12_RESOURCE_STATE_COPY_SOURCE,
                         sbd->state);
    rhi_d3d12_transition(list, dbd->resource, D3D12_RESOURCE_STATE_COPY_DEST,
                         dbd->state);
}

/* ---- material texture binders ---- */
/* A GL texture unit that nothing bound still reads as the textureless
 * default, so the GL binder can leave a missing map alone. A D3D12 root
 * descriptor table has no such "unset" state: whatever the last draw left in
 * that descriptor slot is what the shader samples, so a missing material map
 * would read stale or never-written descriptor memory (measured on WARP:
 * black, with the shader itself still running). Every 2D material slot
 * therefore resolves through this shared 1x1 RGBA8 white texture, created on
 * first use and released with the context (rhi_device_destroy). White is the
 * neutral value for the maps that reach it (ao/occlusion 1.0, metallic-
 * roughness defaults), and it is the same fallback the engine's own scene
 * resources use for absent textures.
 *
 * SCOPE OF THE RULE, honestly: "never leaves a descriptor unwritten" holds on
 * the NORMAL path only. Three failure paths still skip the bind and leave the
 * table as it was — fallback creation failing (device lost, or the upload
 * path refusing), the descriptor allocator returning no slot, and the
 * per-frame SRV budget (RHI_D3D12_CBV_SRV_UAV_CAPACITY) being full. Each of
 * those is a loud, logged or fail-closed condition rather than a silent
 * correct-looking frame, but the guarantee is per-slot-and-best-effort, not
 * unconditional. Cube-typed slots do not even get this rule — see
 * rhi_d3d12_live_cube. */
static RHITexture rhi_d3d12_white_fallback(RHI_D3D12Context *ctx) {
    static const unsigned char white[4] = { 255u, 255u, 255u, 255u };
    RHITextureDesc desc;
    if (ctx == NULL || g_current_device == NULL) return RHI_HANDLE_NULL;
    if (rhi_handle_valid(ctx->white_fallback)) return ctx->white_fallback;
    memset(&desc, 0, sizeof(desc));
    desc.width = 1u;
    desc.height = 1u;
    desc.format = RHI_FORMAT_R8G8B8A8_UNORM;
    desc.mip_levels = 1u;
    desc.data = white;
    ctx->white_fallback = rhi_texture_create(g_current_device, &desc);
    return ctx->white_fallback;
}
/* A handle that names no live texture (null, stale, or not a texture) takes
 * the fallback, so a bound descriptor always describes something real. */
static RHITexture rhi_d3d12_material_slot(RHI_D3D12Context *ctx,
                                          RHITexture tex) {
    if (g_current_device != NULL && rhi_get_resource_typed(g_current_device,
            tex, RHI_RES_TEXTURE) != NULL) return tex;
    return rhi_d3d12_white_fallback(ctx);
}
/* Cube-typed slots — units 8/9 (irradiance, prefiltered radiance) and 10-13
 * (u_point_shadow_cubes[4]) — are sampled as CUBES, not 2D: see
 * engine/shaders/pbr_clustered.frag:56, blinn_phong_clustered.frag:22 and
 * deferred_light.frag:15, all of which declare
 * `layout(binding = 10) uniform samplerCube u_point_shadow_cubes[4]`. The
 * 2D white fallback is therefore WRONG for them: a TEXTURE2D descriptor on a
 * cube-sampled register is a descriptor/shader type mismatch, which is why
 * the engine's own bind path never gives these a 2D view
 * (engine/src/main.c:1109). They are skipped instead.
 *
 * "Live cube" is tested against the RHI_RES_CUBEMAP slot type — the type the
 * GL backend tags a point-shadow depth cube with in its
 * rhi_cubemap_depth_fbo_create — so a 2D texture handle can never pass this
 * gate by accident, and a cube handle can never be mistaken for a texture by
 * rhi_d3d12_material_slot (which requires RHI_RES_TEXTURE).
 * D3D12 creates no cubes today (rhi_cubemap_create and
 * rhi_cubemap_depth_fbo_create are stubs), so every one of these six slots
 * skips; the gate is what makes that omission deliberate and self-starting
 * rather than accidental when cube FBOs land. Note that even a live cube
 * still skips today, one step further in: rhi_cmd_bind_texture resolves
 * RHI_RES_TEXTURE and builds a TEXTURE2D SRV, so it declines a cube handle
 * rather than writing a wrong-dimension descriptor. Cube SRVs
 * (D3D12_SRV_DIMENSION_TEXTURECUBE + Cube2DArraySize) are part of the cube
 * work, not this binder. */
static int rhi_d3d12_live_cube(RHIHandle handle) {
    const RHI_D3D12Texture *td;
    if (g_current_device == NULL) return 0;
    if (rhi_get_resource_typed(g_current_device, handle, RHI_RES_CUBEMAP) != NULL)
        return 1;
    /* R647: a point-shadow depth cube is an RHI_RES_TEXTURE flagged is_cube
     * (rhi_cubemap_depth_fbo_create), which rhi_cmd_bind_texture views as a
     * TEXTURECUBE. A plain 2D texture still fails this gate. */
    td = (const RHI_D3D12Texture *)rhi_get_resource_typed(g_current_device,
                                                          handle, RHI_RES_TEXTURE);
    return td != NULL && td->is_cube;
}
/* R647: the cube twin of the white fallback, for the point-shadow cube
 * registers (t10-t13). A sidecar that declares them gets a descriptor on
 * every draw, and a depth of 1.0 is "nothing nearer than the far plane",
 * i.e. unshadowed — the same answer the old stubbed point_shadow_test gave.
 * The resource is cleared once, on the command list that first binds it,
 * before any read of it on that list. */
static RHITexture rhi_d3d12_cube_fallback(RHI_D3D12Context *ctx) {
    RHI_D3D12CubeDepthFBO *cd;
    RHI_D3D12Texture *td;
    ID3D12GraphicsCommandList *list;
    UINT f;
    if (ctx == NULL || g_current_device == NULL) return RHI_HANDLE_NULL;
    if (rhi_handle_valid(ctx->cube_fallback.depth_tex))
        return ctx->cube_fallback.depth_tex;
    list = rhi_d3d12_cmd_list(ctx);
    if (list == NULL) return RHI_HANDLE_NULL;
    ctx->cube_fallback = rhi_cubemap_depth_fbo_create(g_current_device, 1u);
    cd = (RHI_D3D12CubeDepthFBO *)rhi_get_resource_typed(g_current_device,
        ctx->cube_fallback.fb, RHI_RES_CUBEMAP_DEPTH_FBO);
    td = (RHI_D3D12Texture *)rhi_get_resource_typed(g_current_device,
        ctx->cube_fallback.depth_tex, RHI_RES_TEXTURE);
    if (cd == NULL || td == NULL) {
        rhi_cubemap_depth_fbo_destroy(g_current_device, &ctx->cube_fallback);
        return RHI_HANDLE_NULL;
    }
    if (td->state != D3D12_RESOURCE_STATE_DEPTH_WRITE) {
        rhi_d3d12_transition(list, td->resource, td->state,
                             D3D12_RESOURCE_STATE_DEPTH_WRITE);
        td->state = D3D12_RESOURCE_STATE_DEPTH_WRITE;
    }
    for (f = 0u; f < 6u; ++f)
        ID3D12GraphicsCommandList_ClearDepthStencilView(list,
            rhi_d3d12_descriptor_cpu(&ctx->dsv_alloc, cd->dsv_slots[f]),
            D3D12_CLEAR_FLAG_DEPTH, 1.0f, 0u, 0u, NULL);
    return ctx->cube_fallback.depth_tex;
}
/* R654: IBL cube fallback (t8 irradiance / t9 prefilter) -- a 1x1 RGBA16F
 * colour cube of zeros, i.e. "no environment light", the GLSL #else branch
 * of HAS_IBL. Created on first use and released with the context. */
static RHICubemap rhi_d3d12_black_cube(RHI_D3D12Context *ctx) {
    static const u16 zero[4] = { 0u, 0u, 0u, 0u };
    RHICubemapDesc d;
    u32 f;
    if (ctx == NULL || g_current_device == NULL) return RHI_HANDLE_NULL;
    if (rhi_handle_valid(ctx->black_cube)) return ctx->black_cube;
    memset(&d, 0, sizeof(d));
    d.size = 1u;
    d.format = RHI_FORMAT_R16G16B16A16_SFLOAT;
    d.mip_levels = 1u;
    for (f = 0u; f < 6u; ++f) d.faces[f] = zero;
    ctx->black_cube = rhi_cubemap_create(g_current_device, &d);
    return ctx->black_cube;
}
/* Point-shadow cube unit 10 + i: the caller's cube when it is live, else the
 * cleared fallback. */
static void rhi_d3d12_bind_point_shadow_cubes(RHICmdBuffer *cmd,
    RHI_D3D12Context *ctx, const RHITexture *cubes, u32 count,
    RHISampler sampler) {
    u32 i;
    if (cubes == NULL) count = 0u;
    if (count > 4u) count = 4u;
    for (i = 0u; i < 4u; ++i) {
        RHITexture t = (i < count && rhi_d3d12_live_cube(cubes[i]))
                           ? cubes[i] : rhi_d3d12_cube_fallback(ctx);
        if (rhi_handle_valid(t)) rhi_cmd_bind_texture(cmd, t, sampler, 10u + i);
    }
}
/* The binders only mean anything inside a started frame with a bound
 * pipeline, and creating the fallback uploads on the queue, so both guard
 * here rather than relying on rhi_cmd_bind_texture's per-call bail-outs. */
static int rhi_d3d12_material_bindable(RHI_D3D12Context *ctx) {
    if (ctx == NULL || g_current_device == NULL) return 0;
    return rhi_d3d12_cmd_list(ctx) != NULL && ctx->bound_pipeline != NULL;
}
/* Unit map mirrors the GL backend's rhi_cmd_bind_material_textures binder
 * exactly, so a D3D12 sidecar's register(tN) lines up with GL texture unit
 * N — the blinn_phong sidecar declares g_albedo : register(t0), which is why
 * albedo is unit 0. rhi_cmd_bind_texture returns without touching any table
 * for a register the bound pipeline does not declare, so a sidecar
 * declaring only t0 works here too.
 *
 * KNOWN SAMPLER LIMIT (inherited infrastructure, not introduced here):
 * `sampler` is accepted and forwarded but has no effect — see
 * rhi_cmd_bind_texture. Every D3D12 sampler register resolves to one
 * hardcoded static sampler, so the shadow map on unit 1 is sampled without
 * comparison filtering today. That blocks the D3D12 forward pass at the
 * shadow-map step, not at this binder. */
void rhi_cmd_bind_material_textures(RHICmdBuffer *cmd, RHITexture albedo,
    RHITexture mr, RHITexture normal, RHITexture emissive, RHITexture shadow,
    RHITexture ssao, RHISampler sampler) {
    RHI_D3D12Context *ctx = (RHI_D3D12Context *)cmd;
    if (!rhi_d3d12_material_bindable(ctx)) return;
    rhi_cmd_bind_texture(cmd, rhi_d3d12_material_slot(ctx, albedo), sampler, 0u);
    rhi_cmd_bind_texture(cmd, rhi_d3d12_material_slot(ctx, shadow), sampler, 1u);
    rhi_cmd_bind_texture(cmd, rhi_d3d12_material_slot(ctx, mr), sampler, 2u);
    rhi_cmd_bind_texture(cmd, rhi_d3d12_material_slot(ctx, normal), sampler, 3u);
    rhi_cmd_bind_texture(cmd, rhi_d3d12_material_slot(ctx, emissive), sampler, 4u);
    rhi_cmd_bind_texture(cmd, rhi_d3d12_material_slot(ctx, ssao), sampler, 5u);
}
/* Unit map mirrors the GL backend's rhi_cmd_bind_material_textures_ibl binder
 * exactly, including occlusion at 15, the point-shadow cubes at 10-13
 * (clamped to four), ssao at 14, and the IBL units 7-9. Same sampler caveat
 * as the non-IBL binder, and it bites hardest here: the point-shadow cubes
 * are samplerCube + manual .r compare on GL and want a comparison sampler
 * both for the cube and for the depth comparison. */
void rhi_cmd_bind_material_textures_ibl(RHICmdBuffer *cmd, RHITexture albedo,
    RHITexture mr, RHITexture normal, RHITexture emissive,
    RHITexture occlusion, RHITexture shadow, RHITexture ssao,
    RHISampler sampler, RHITexture brdf_lut, RHICubemap irradiance_map,
    RHICubemap prefilter_map, const RHITexture *point_shadow_cubes,
    u32 point_shadow_count) {
    RHI_D3D12Context *ctx = (RHI_D3D12Context *)cmd;
    if (!rhi_d3d12_material_bindable(ctx)) return;
    rhi_cmd_bind_texture(cmd, rhi_d3d12_material_slot(ctx, albedo), sampler, 0u);
    rhi_cmd_bind_texture(cmd, rhi_d3d12_material_slot(ctx, shadow), sampler, 1u);
    rhi_cmd_bind_texture(cmd, rhi_d3d12_material_slot(ctx, mr), sampler, 2u);
    rhi_cmd_bind_texture(cmd, rhi_d3d12_material_slot(ctx, normal), sampler, 3u);
    rhi_cmd_bind_texture(cmd, rhi_d3d12_material_slot(ctx, emissive), sampler, 4u);
    /* R583: occlusion at 15. */
    rhi_cmd_bind_texture(cmd, rhi_d3d12_material_slot(ctx, occlusion), sampler, 15u);
    /* Cube slots: a live cube, else the cube fallback — never a 2D
     * texture, which on a samplerCube register is a type mismatch (see
     * rhi_d3d12_live_cube). */
    rhi_d3d12_bind_point_shadow_cubes(cmd, ctx, point_shadow_cubes,
                                      point_shadow_count, sampler);
    /* R213-B: ssao at 14 — units 10-13 are u_point_shadow_cubes[4]. */
    rhi_cmd_bind_texture(cmd, rhi_d3d12_material_slot(ctx, ssao), sampler, 14u);
    rhi_cmd_bind_texture(cmd, rhi_d3d12_material_slot(ctx, brdf_lut), sampler, 7u);
    /* Units 8 and 9 are the IBL cubes. R655: a live cube, else the black
     * fallback -- a sidecar that declares t8/t9 (pbr_clustered_hlsl.frag)
     * must get a descriptor on every draw, and black adds no environment
     * light. rhi_cmd_bind_cubemap understands the colour cube; the old
     * rhi_cmd_bind_texture call could not build a cube view for it. */
    rhi_cmd_bind_cubemap(cmd, rhi_d3d12_cube_tex(irradiance_map) != NULL
                                  ? irradiance_map : rhi_d3d12_black_cube(ctx),
                         sampler, 8u);
    rhi_cmd_bind_cubemap(cmd, rhi_d3d12_cube_tex(prefilter_map) != NULL
                                  ? prefilter_map : rhi_d3d12_black_cube(ctx),
                         sampler, 9u);
}
void rhi_cmd_bind_deferred_gbuf_textures(RHICmdBuffer *cmd,
    RHITexture albedo_metallic, RHITexture roughness_ao, RHITexture normal,
    RHITexture depth, RHITexture emissive, RHITexture shadow, RHITexture ssao,
    RHISampler sampler, RHITexture brdf_lut, RHICubemap irradiance_map,
    RHICubemap prefilter_map, const RHITexture *point_shadow_cubes,
    u32 point_shadow_count, RHISampler cube_sampler) {
    /* R644: was a no-op stub. The GL backend's unit map, which is what
     * deferred_light_hlsl.frag declares: 0 albedo+metallic, 1 normal,
     * 2 roughness/AO, 3 depth, 4 shadow, 14 SSAO, 15 emissive. Units the
     * bound pipeline does not declare are skipped by rhi_cmd_bind_texture.
     * Shadow and SSAO fall back to white (lit, unoccluded) like the material
     * binder, because the sidecar always declares them and a D3D12 table has
     * no unbound state. R647: the point-shadow cubes go to 10-13 (a live
     * cube, else the 1.0 cube fallback). R654: the IBL inputs go to 7-9 --
     * the BRDF LUT (white fallback) and the irradiance / prefiltered cubes
     * (black fallback, so a missing environment adds no light). */
    RHI_D3D12Context *ctx = (RHI_D3D12Context *)cmd;
    if (!rhi_d3d12_material_bindable(ctx)) return;
    rhi_cmd_bind_texture(cmd, rhi_d3d12_material_slot(ctx, brdf_lut), sampler, 7u);
    rhi_cmd_bind_cubemap(cmd, rhi_d3d12_cube_tex(irradiance_map) != NULL
                                  ? irradiance_map : rhi_d3d12_black_cube(ctx),
                         sampler, 8u);
    rhi_cmd_bind_cubemap(cmd, rhi_d3d12_cube_tex(prefilter_map) != NULL
                                  ? prefilter_map : rhi_d3d12_black_cube(ctx),
                         sampler, 9u);
    rhi_d3d12_bind_point_shadow_cubes(cmd, ctx, point_shadow_cubes,
                                      point_shadow_count, cube_sampler);
    rhi_cmd_bind_texture(cmd, albedo_metallic, sampler, 0u);
    rhi_cmd_bind_texture(cmd, normal, sampler, 1u);
    rhi_cmd_bind_texture(cmd, roughness_ao, sampler, 2u);
    rhi_cmd_bind_texture(cmd, depth, sampler, 3u);
    rhi_cmd_bind_texture(cmd, rhi_d3d12_material_slot(ctx, shadow), sampler, 4u);
    rhi_cmd_bind_texture(cmd, rhi_d3d12_material_slot(ctx, ssao), sampler, 14u);
    rhi_cmd_bind_texture(cmd, emissive, sampler, 15u);
}
/* R620: was a no-op stub. Nine post passes route through it -- dof,
 * motion_blur, taa, ssr, ssgi, contact_shadow, lens_flare and both arms of
 * combined_post_process -- so on D3D12 every one of them would have built a
 * pipeline and then sampled unbound tables.
 *
 * The contract is the GL one, which is the simplest of the three backends:
 * textures[i] goes to unit i, at most six. That is exactly
 * rhi_cmd_bind_texture called once per unit, so this delegates instead of
 * duplicating the SRV path -- the per-unit binder already resolves
 * image_root_params[unit], skips a register the pipeline does not declare,
 * builds a 2D or 2D-array view from the texture, and transitions it to a
 * shader-read state. Invalid handles are skipped the same way GL's
 * gl_bind_tex_unit skips them. The sampler argument is accepted and dropped
 * exactly as in rhi_cmd_bind_texture; see the KNOWN LIMIT note there. */
void rhi_cmd_bind_textures_multi(RHICmdBuffer *cmd, RHITexture *textures,
                                 int count, RHISampler sampler) {
    int i;
    if (cmd == NULL || textures == NULL || count <= 0) return;
    for (i = 0; i < count && i < 6; ++i) {
        if (!rhi_handle_valid(textures[i])) continue;
        rhi_cmd_bind_texture(cmd, textures[i], sampler, (u32)i);
    }
}

/* ---- offscreen / MRT / depth-cube FBO ---- */
RHIOffscreenFBO rhi_offscreen_fbo_create_desc(RHIDevice *dev,
                                              const RHIOffscreenFBODesc *desc) {
    RHIOffscreenFBO out;
    RHI_D3D12Context *ctx;
    RHI_D3D12FBO *fd;
    RHI_D3D12Texture *color, *depth;
    RHITextureDesc tex_desc;
    UINT64 retire;
    u32 samples;
    UINT idx;
    if (dev == NULL || desc == NULL) { memset(&out, 0, sizeof(out)); return out; }
    memset(&out, 0, sizeof(out));
    if (!rhi_offscreen_fbo_desc_validate(&dev->capabilities, desc)) return out;
    ctx = (RHI_D3D12Context *)dev->backend_data;
    if (ctx == NULL) return out;
    samples = desc->sample_count == 0u ? 1u : desc->sample_count;
    /* MSAA needs a sample-count RTV plus a resolve target; not wired yet.
     * Fail closed rather than silently handing back a single-sample FBO. */
    if (samples > 1u) return out;

    memset(&tex_desc, 0, sizeof(tex_desc));
    tex_desc.width = desc->width;
    tex_desc.height = desc->height;
    tex_desc.mip_levels = 1u;
    tex_desc.format = desc->color_format;
    out.color_tex = rhi_texture_create(dev, &tex_desc);
    if (!rhi_handle_valid(out.color_tex)) return out;
    tex_desc.format = RHI_FORMAT_D32_FLOAT;
    /* R636: the depth attachment goes through the depth_samplable path, so
     * the resource is the canonical R32_TYPELESS and can be aliased both as
     * a D32_FLOAT depth-stencil view (here) and as an R32_FLOAT shader
     * resource view (by every post pass that samples the scene depth).
     * A plain D32_FLOAT resource cannot back an SRV at all: the SRV
     * creation failed, the descriptor stayed empty, and the shader read a
     * null descriptor -- which is how TAA and motion blur took the device
     * down on the first frame (0x887a0001 at present time). */
    out.depth_tex = rhi_d3d12_texture_create_ex(dev, &tex_desc, 1, 0u);
    if (!rhi_handle_valid(out.depth_tex)) {
        rhi_texture_destroy(dev, out.color_tex);
        memset(&out, 0, sizeof(out));
        return out;
    }
    color = (RHI_D3D12Texture *)rhi_get_resource_typed(dev, out.color_tex, RHI_RES_TEXTURE);
    depth = (RHI_D3D12Texture *)rhi_get_resource_typed(dev, out.depth_tex, RHI_RES_TEXTURE);
    fd = (RHI_D3D12FBO *)calloc(1u, sizeof(*fd));
    if (fd == NULL) goto fail;
    fd->rtv_slot = rhi_d3d12_descriptor_take(ctx, &ctx->rtv_alloc);
    fd->dsv_slot = rhi_d3d12_descriptor_take(ctx, &ctx->dsv_alloc);
    if (fd->rtv_slot == UINT_MAX || fd->dsv_slot == UINT_MAX) {
        LOG_WARN("D3D12: offscreen FBO refused -- %s descriptor heap exhausted",
                 fd->rtv_slot == UINT_MAX ? "RTV" : "DSV");
        retire = rhi_d3d12_retire_fence(ctx);
        if (fd->rtv_slot != UINT_MAX)
            rhi_d3d12_descriptor_give_back(&ctx->rtv_alloc, fd->rtv_slot, retire);
        if (fd->dsv_slot != UINT_MAX)
            rhi_d3d12_descriptor_give_back(&ctx->dsv_alloc, fd->dsv_slot, retire);
        free(fd);
        goto fail;
    }
    ID3D12Device_CreateRenderTargetView(ctx->device, color->resource, NULL,
        rhi_d3d12_descriptor_cpu(&ctx->rtv_alloc, fd->rtv_slot));
    {
        /* R636: the depth resource is R32_TYPELESS (see above), so the
         * depth-stencil view has to name the D32_FLOAT aspect explicitly --
         * a NULL-desc default would guess from the typeless format and
         * fail. */
        D3D12_DEPTH_STENCIL_VIEW_DESC dsv_desc;
        ZeroMemory(&dsv_desc, sizeof(dsv_desc));
        dsv_desc.Format = DXGI_FORMAT_D32_FLOAT;
        dsv_desc.ViewDimension = D3D12_DSV_DIMENSION_TEXTURE2D;
        dsv_desc.Flags = D3D12_DSV_FLAG_NONE;
        ID3D12Device_CreateDepthStencilView(ctx->device, depth->resource,
            &dsv_desc, rhi_d3d12_descriptor_cpu(&ctx->dsv_alloc, fd->dsv_slot));
    }
    /* R617/R619 portable contract: the bind clear color is caller-owned and
     * defaults to {0.05, 0.05, 0.1, 1.0}; depth always clears to 1.0. */
    fd->clear_color[0] = 0.05f; fd->clear_color[1] = 0.05f;
    fd->clear_color[2] = 0.1f;  fd->clear_color[3] = 1.0f;
    fd->width = desc->width;
    fd->height = desc->height;
    fd->sample_count = samples;
    idx = rhi_alloc_slot(dev);
    dev->slots[idx].ptr = fd;
    dev->slots[idx].type = RHI_RES_FRAMEBUFFER;
    out.fb = rhi_make_handle(idx, dev->slots[idx].generation);
    out.width = desc->width;
    out.height = desc->height;
    out.sample_count = samples;
    return out;
fail:
    rhi_texture_destroy(dev, out.color_tex);
    rhi_texture_destroy(dev, out.depth_tex);
    memset(&out, 0, sizeof(out));
    return out;
}
RHIOffscreenFBO rhi_offscreen_fbo_create(RHIDevice *dev, u32 width,
                                         u32 height) {
    return rhi_offscreen_fbo_create_fmt(dev, width, height,
                                        RHI_FORMAT_R8G8B8A8_UNORM);
}
RHIOffscreenFBO rhi_offscreen_fbo_create_fmt(RHIDevice *dev, u32 width,
                                             u32 height, RHIFormat color_fmt) {
    RHIOffscreenFBODesc desc;
    memset(&desc, 0, sizeof(desc));
    desc.width = width;
    desc.height = height;
    desc.color_format = color_fmt;
    desc.sample_count = 1u;
    return rhi_offscreen_fbo_create_desc(dev, &desc);
}
void rhi_offscreen_fbo_destroy(RHIDevice *dev, RHIOffscreenFBO *fbo) {
    RHI_D3D12Context *ctx;
    RHI_D3D12FBO *fd;
    UINT64 retire;
    if (dev == NULL || fbo == NULL) return;
    fd = (RHI_D3D12FBO *)rhi_get_resource_typed(dev, fbo->fb, RHI_RES_FRAMEBUFFER);
    if (fd == NULL) return;
    ctx = (RHI_D3D12Context *)dev->backend_data;
    if (ctx != NULL) {
        retire = rhi_d3d12_retire_fence(ctx);
        if (fd->rtv_slot != UINT_MAX)
            rhi_d3d12_descriptor_give_back(&ctx->rtv_alloc, fd->rtv_slot, retire);
        if (fd->dsv_slot != UINT_MAX)
            rhi_d3d12_descriptor_give_back(&ctx->dsv_alloc, fd->dsv_slot, retire);
    }
    free(fd);
    rhi_free_slot(dev, fbo->fb);
    if (rhi_handle_valid(fbo->color_tex)) rhi_texture_destroy(dev, fbo->color_tex);
    if (rhi_handle_valid(fbo->depth_tex)) rhi_texture_destroy(dev, fbo->depth_tex);
    memset(fbo, 0, sizeof(*fbo));
}
/* R629 diagnostic, narrowed in R643. A texture that is still bound as a
 * shader resource of the current pipeline when it becomes a render target is
 * read and written by the next draw -- undefined, and the shape that loses a
 * device. R629 warned whenever the texture had been read at any point in the
 * frame, which also fired on every legal ping-pong (bloom blur: read A ->
 * write B, read B -> write A; each bind barriers the resource): 33 warnings
 * per 12 demo frames, none of them a hazard, and the debug layer agreed. Now
 * only a live binding counts: ctx->live_srv[] holds the textures in the bound
 * pipeline's tables and is cleared when the root signature changes (which
 * drops every root argument). */
static void rhi_d3d12_warn_rt_srv_alias(RHI_D3D12Context *ctx,
                                         const RHI_D3D12Texture *tex,
                                         const char *role) {
    UINT i;
    if (ctx == NULL || tex == NULL) return;
    for (i = 0u; i < RHI_D3D12_MAX_REGISTERS; ++i) {
        if (ctx->live_srv[i] != tex) continue;
        LOG_WARN("D3D12: %ux%u texture is still bound as a shader resource "
                 "(unit %u) and is now being bound as %s -- the next draw "
                 "would read and write it", tex->width, tex->height, i, role);
        ctx->rt_srv_alias_count++;
        return;
    }
}

static void rhi_d3d12_fbo_bind_impl(RHICmdBuffer *cmd, RHIOffscreenFBO *fbo,
                                    bool load) {
    RHI_D3D12Context *ctx = (RHI_D3D12Context *)cmd;
    ID3D12GraphicsCommandList *list;
    RHI_D3D12FBO *fd;
    RHI_D3D12Texture *color, *depth;
    D3D12_CPU_DESCRIPTOR_HANDLE rtv, dsv;
    if (ctx == NULL || g_current_device == NULL || fbo == NULL) return;
    list = rhi_d3d12_cmd_list(ctx);
    if (list == NULL) return; /* no frame in flight: drop, GL/VK parity */
    fd = (RHI_D3D12FBO *)rhi_get_resource_typed(g_current_device, fbo->fb,
                                                RHI_RES_FRAMEBUFFER);
    if (fd == NULL) return;
    color = (RHI_D3D12Texture *)rhi_get_resource_typed(g_current_device, fbo->color_tex, RHI_RES_TEXTURE);
    depth = (RHI_D3D12Texture *)rhi_get_resource_typed(g_current_device, fbo->depth_tex, RHI_RES_TEXTURE);
    if (color == NULL || depth == NULL) return;
    /* Transitions declare the CPU-tracked state (td->state), the same rule
     * the texture upload / readback one-shots follow. */
    rhi_d3d12_warn_rt_srv_alias(ctx, color, "RENDER_TARGET");
    rhi_d3d12_transition(list, color->resource, color->state,
                         D3D12_RESOURCE_STATE_RENDER_TARGET);
    color->state = D3D12_RESOURCE_STATE_RENDER_TARGET;
    rhi_d3d12_warn_rt_srv_alias(ctx, depth, "DEPTH_WRITE");
    rhi_d3d12_transition(list, depth->resource, depth->state,
                         D3D12_RESOURCE_STATE_DEPTH_WRITE);
    depth->state = D3D12_RESOURCE_STATE_DEPTH_WRITE;
    rtv = rhi_d3d12_descriptor_cpu(&ctx->rtv_alloc, fd->rtv_slot);
    dsv = rhi_d3d12_descriptor_cpu(&ctx->dsv_alloc, fd->dsv_slot);
    ID3D12GraphicsCommandList_OMSetRenderTargets(list, 1u, &rtv, TRUE, &dsv);
    rhi_d3d12_set_full_target_viewport(list, fd->width, fd->height);
    ctx->bound_rtvs[0] = rtv;
    ctx->bound_rtv_formats[0] = color->dxgi_format;
    ctx->bound_rtv_count = 1u;
    ctx->bound_dsv = dsv;
    ctx->bound_dsv_valid = 1u;
    if (!load) {
        ID3D12GraphicsCommandList_ClearRenderTargetView(list, rtv, fd->clear_color, 0u, NULL);
        ID3D12GraphicsCommandList_ClearDepthStencilView(list, dsv,
            D3D12_CLEAR_FLAG_DEPTH, 1.0f, 0u, 0u, NULL);
    }
}
void rhi_offscreen_fbo_bind(RHICmdBuffer *cmd, RHIOffscreenFBO *fbo) {
    rhi_d3d12_fbo_bind_impl(cmd, fbo, false);
}
void rhi_offscreen_fbo_bind_load(RHICmdBuffer *cmd, RHIOffscreenFBO *fbo) {
    rhi_d3d12_fbo_bind_impl(cmd, fbo, true);
}
void rhi_offscreen_fbo_unbind(RHICmdBuffer *cmd, u32 screen_w, u32 screen_h) {
    RHI_D3D12Context *ctx = (RHI_D3D12Context *)cmd;
    ID3D12GraphicsCommandList *list;
    D3D12_CPU_DESCRIPTOR_HANDLE rtv;
    D3D12_VIEWPORT vp;
    D3D12_RECT sc;
    if (ctx == NULL || g_current_device == NULL || !ctx->swapchain_ready) return;
    list = rhi_d3d12_cmd_list(ctx);
    if (list == NULL) return;
    /* R230 parity: restore the swapchain target with a full-target
     * viewport/scissor, otherwise post-fx draws would keep targeting the
     * offscreen FBO that unbind just left bound. */
    rtv = rhi_d3d12_descriptor_cpu(&ctx->rtv_alloc,
                                   ctx->swapchain.rtv_slots[ctx->swapchain.current_index]);
    ID3D12GraphicsCommandList_OMSetRenderTargets(list, 1u, &rtv, FALSE, NULL);
    ctx->bound_rtvs[0] = rtv;
    ctx->bound_rtv_formats[0] = ctx->swapchain.format;
    ctx->bound_rtv_count = 1u;
    ctx->bound_dsv_valid = 0u;
    vp.TopLeftX = 0.0f; vp.TopLeftY = 0.0f;
    vp.Width = (f32)screen_w; vp.Height = (f32)screen_h;
    vp.MinDepth = 0.0f; vp.MaxDepth = 1.0f;
    ID3D12GraphicsCommandList_RSSetViewports(list, 1u, &vp);
    sc.left = 0; sc.top = 0; sc.right = (LONG)screen_w; sc.bottom = (LONG)screen_h;
    ID3D12GraphicsCommandList_RSSetScissorRects(list, 1u, &sc);
}
void rhi_offscreen_fbo_set_clear_color(RHIDevice *dev, RHIOffscreenFBO *fbo,
                                       f32 r, f32 g, f32 b, f32 a) {
    RHI_D3D12FBO *fd;
    if (dev == NULL || fbo == NULL) return;
    fd = (RHI_D3D12FBO *)rhi_get_resource_typed(dev, fbo->fb, RHI_RES_FRAMEBUFFER);
    if (fd == NULL) return;
    fd->clear_color[0] = r; fd->clear_color[1] = g;
    fd->clear_color[2] = b; fd->clear_color[3] = a;
}
static void rhi_d3d12_mrt_cleanup(RHIDevice *dev, RHIMRTFBO *fbo,
                                   RHI_D3D12MRTFBO *md) {
    RHI_D3D12Context *ctx;
    UINT64 retire;
    u32 i;
    if (dev == NULL || fbo == NULL || md == NULL) return;
    ctx = (RHI_D3D12Context *)dev->backend_data;
    if (ctx != NULL) {
        retire = rhi_d3d12_retire_fence(ctx);
        for (i = 0u; i < RHI_MRT_MAX_ATTACHMENTS; ++i) {
            if (md->rtv_slots[i] != UINT_MAX)
                rhi_d3d12_descriptor_give_back(&ctx->rtv_alloc,
                                               md->rtv_slots[i], retire);
        }
        if (md->dsv_slot != UINT_MAX)
            rhi_d3d12_descriptor_give_back(&ctx->dsv_alloc, md->dsv_slot,
                                           retire);
    }
    if (rhi_handle_valid(fbo->fb)) rhi_free_slot(dev, fbo->fb);
    for (i = 0u; i < RHI_MRT_MAX_ATTACHMENTS; ++i) {
        if (rhi_handle_valid(fbo->color_tex[i]))
            rhi_texture_destroy(dev, fbo->color_tex[i]);
    }
    if (rhi_handle_valid(fbo->depth_tex))
        rhi_texture_destroy(dev, fbo->depth_tex);
    free(md);
    memset(fbo, 0, sizeof(*fbo));
}

RHIMRTFBO rhi_mrt_fbo_create(RHIDevice *dev, u32 width, u32 height,
                             const RHIFormat *formats, u32 attachment_count) {
    RHIMRTFBO out;
    RHI_D3D12Context *ctx;
    RHI_D3D12MRTFBO *md;
    RHITextureDesc tex_desc;
    UINT idx;
    u32 i;
    memset(&out, 0, sizeof(out));
    if (dev == NULL || !rhi_mrt_desc_validate(width, height, formats,
                                               attachment_count))
        return out;
    ctx = (RHI_D3D12Context *)dev->backend_data;
    if (ctx == NULL) return out;
    /* Texture creation and final MRT registration each consume a resource
     * slot; preflight so rhi_alloc_slot cannot abort partway through setup. */
    if (dev->free_count < attachment_count + 2u) return out;
    md = (RHI_D3D12MRTFBO *)calloc(1u, sizeof(*md));
    if (md == NULL) return out;
    for (i = 0u; i < RHI_MRT_MAX_ATTACHMENTS; ++i) {
        md->rtv_slots[i] = UINT_MAX;
        md->clear_color[i][0] = 0.05f;
        md->clear_color[i][1] = 0.05f;
        md->clear_color[i][2] = 0.1f;
        md->clear_color[i][3] = 1.0f;
    }
    md->dsv_slot = UINT_MAX;
    md->width = width;
    md->height = height;
    md->attachment_count = attachment_count;
    md->sample_count = 1u;

    memset(&tex_desc, 0, sizeof(tex_desc));
    tex_desc.width = width;
    tex_desc.height = height;
    tex_desc.mip_levels = 1u;
    for (i = 0u; i < attachment_count; ++i) {
        tex_desc.format = formats[i];
        out.color_tex[i] = rhi_texture_create(dev, &tex_desc);
        if (!rhi_handle_valid(out.color_tex[i])) {
            rhi_d3d12_mrt_cleanup(dev, &out, md);
            return (RHIMRTFBO){0};
        }
    }
    tex_desc.format = RHI_FORMAT_D32_FLOAT;
    /* R636: same typeless-alias treatment as the plain FBO's depth
     * attachment -- the forward scene's depth is the one TAA, motion blur
     * and every other depth-reading post pass samples. */
    out.depth_tex = rhi_d3d12_texture_create_ex(dev, &tex_desc, 1, 0u);
    if (!rhi_handle_valid(out.depth_tex)) {
        rhi_d3d12_mrt_cleanup(dev, &out, md);
        return (RHIMRTFBO){0};
    }
    for (i = 0u; i < attachment_count; ++i) {
        md->rtv_slots[i] = rhi_d3d12_descriptor_take(ctx, &ctx->rtv_alloc);
        if (md->rtv_slots[i] == UINT_MAX) {
            rhi_d3d12_mrt_cleanup(dev, &out, md);
            return (RHIMRTFBO){0};
        }
    }
    md->dsv_slot = rhi_d3d12_descriptor_take(ctx, &ctx->dsv_alloc);
    if (md->dsv_slot == UINT_MAX) {
        rhi_d3d12_mrt_cleanup(dev, &out, md);
        return (RHIMRTFBO){0};
    }
    for (i = 0u; i < attachment_count; ++i) {
        RHI_D3D12Texture *color = (RHI_D3D12Texture *)
            rhi_get_resource_typed(dev, out.color_tex[i], RHI_RES_TEXTURE);
        if (color == NULL) {
            rhi_d3d12_mrt_cleanup(dev, &out, md);
            return (RHIMRTFBO){0};
        }
        ID3D12Device_CreateRenderTargetView(ctx->device, color->resource, NULL,
            rhi_d3d12_descriptor_cpu(&ctx->rtv_alloc, md->rtv_slots[i]));
    }
    {
        RHI_D3D12Texture *depth = (RHI_D3D12Texture *)
            rhi_get_resource_typed(dev, out.depth_tex, RHI_RES_TEXTURE);
        D3D12_DEPTH_STENCIL_VIEW_DESC dsv_desc;
        if (depth == NULL) {
            rhi_d3d12_mrt_cleanup(dev, &out, md);
            return (RHIMRTFBO){0};
        }
        /* R636: the depth resource is R32_TYPELESS, so the depth-stencil
         * view names the D32_FLOAT aspect explicitly. */
        ZeroMemory(&dsv_desc, sizeof(dsv_desc));
        dsv_desc.Format = DXGI_FORMAT_D32_FLOAT;
        dsv_desc.ViewDimension = D3D12_DSV_DIMENSION_TEXTURE2D;
        dsv_desc.Flags = D3D12_DSV_FLAG_NONE;
        ID3D12Device_CreateDepthStencilView(ctx->device, depth->resource,
            &dsv_desc, rhi_d3d12_descriptor_cpu(&ctx->dsv_alloc, md->dsv_slot));
    }
    if (dev->free_count == 0u) {
        rhi_d3d12_mrt_cleanup(dev, &out, md);
        return (RHIMRTFBO){0};
    }
    idx = rhi_alloc_slot(dev);
    if (idx >= RHI_MAX_RESOURCES) {
        rhi_d3d12_mrt_cleanup(dev, &out, md);
        return (RHIMRTFBO){0};
    }
    dev->slots[idx].ptr = md;
    dev->slots[idx].type = RHI_RES_MRT_FBO;
    out.fb = rhi_make_handle(idx, dev->slots[idx].generation);
    out.attachment_count = attachment_count;
    out.width = width;
    out.height = height;
    return out;
}
void rhi_mrt_fbo_destroy(RHIDevice *dev, RHIMRTFBO *fbo) {
    RHI_D3D12MRTFBO *md;
    if (dev == NULL || fbo == NULL) return;
    md = (RHI_D3D12MRTFBO *)rhi_get_resource_typed(dev, fbo->fb,
                                                   RHI_RES_MRT_FBO);
    if (md == NULL) {
        memset(fbo, 0, sizeof(*fbo));
        return;
    }
    rhi_d3d12_mrt_cleanup(dev, fbo, md);
}
static void rhi_d3d12_mrt_bind_impl(RHICmdBuffer *cmd, RHIMRTFBO *fbo,
                                     bool load) {
    RHI_D3D12Context *ctx = (RHI_D3D12Context *)cmd;
    ID3D12GraphicsCommandList *list;
    RHI_D3D12MRTFBO *md;
    RHI_D3D12Texture *colors[RHI_MRT_MAX_ATTACHMENTS];
    RHI_D3D12Texture *depth;
    D3D12_CPU_DESCRIPTOR_HANDLE rtvs[RHI_MRT_MAX_ATTACHMENTS];
    D3D12_CPU_DESCRIPTOR_HANDLE dsv;
    u32 i;

    if (ctx == NULL || g_current_device == NULL || fbo == NULL) return;
    list = rhi_d3d12_cmd_list(ctx);
    if (list == NULL) return;
    md = (RHI_D3D12MRTFBO *)rhi_get_resource_typed(g_current_device,
                                                    fbo->fb,
                                                    RHI_RES_MRT_FBO);
    if (md == NULL || md->attachment_count == 0u ||
        md->attachment_count > RHI_MRT_MAX_ATTACHMENTS ||
        fbo->attachment_count != md->attachment_count) return;

    for (i = 0u; i < md->attachment_count; ++i) {
        colors[i] = (RHI_D3D12Texture *)
            rhi_get_resource_typed(g_current_device, fbo->color_tex[i],
                                   RHI_RES_TEXTURE);
        if (colors[i] == NULL) return;
    }
    depth = (RHI_D3D12Texture *)rhi_get_resource_typed(
        g_current_device, fbo->depth_tex, RHI_RES_TEXTURE);
    if (depth == NULL) return;
    for (i = 0u; i < md->attachment_count; ++i) {
        rhi_d3d12_warn_rt_srv_alias(ctx, colors[i], "RENDER_TARGET");
        rhi_d3d12_transition(list, colors[i]->resource, colors[i]->state,
                             D3D12_RESOURCE_STATE_RENDER_TARGET);
        colors[i]->state = D3D12_RESOURCE_STATE_RENDER_TARGET;
        rtvs[i] = rhi_d3d12_descriptor_cpu(&ctx->rtv_alloc, md->rtv_slots[i]);
    }
    rhi_d3d12_warn_rt_srv_alias(ctx, depth, "DEPTH_WRITE");
    rhi_d3d12_transition(list, depth->resource, depth->state,
                         D3D12_RESOURCE_STATE_DEPTH_WRITE);
    depth->state = D3D12_RESOURCE_STATE_DEPTH_WRITE;
    dsv = rhi_d3d12_descriptor_cpu(&ctx->dsv_alloc, md->dsv_slot);

    ID3D12GraphicsCommandList_OMSetRenderTargets(list, md->attachment_count,
                                                 rtvs, FALSE, &dsv);
    rhi_d3d12_set_full_target_viewport(list, md->width, md->height);
    for (i = 0u; i < md->attachment_count; ++i) {
        ctx->bound_rtvs[i] = rtvs[i];
        ctx->bound_rtv_formats[i] = colors[i]->dxgi_format;
    }
    ctx->bound_rtv_count = md->attachment_count;
    ctx->bound_dsv = dsv;
    ctx->bound_dsv_valid = 1u;
    if (!load) {
        for (i = 0u; i < md->attachment_count; ++i)
            ID3D12GraphicsCommandList_ClearRenderTargetView(
                list, rtvs[i], md->clear_color[i], 0u, NULL);
        ID3D12GraphicsCommandList_ClearDepthStencilView(
            list, dsv, D3D12_CLEAR_FLAG_DEPTH, 1.0f, 0u, 0u, NULL);
    }
}
void rhi_mrt_fbo_bind(RHICmdBuffer *cmd, RHIMRTFBO *fbo) {
    rhi_d3d12_mrt_bind_impl(cmd, fbo, false);
}
void rhi_mrt_fbo_bind_load(RHICmdBuffer *cmd, RHIMRTFBO *fbo) {
    rhi_d3d12_mrt_bind_impl(cmd, fbo, true);
}
void rhi_mrt_fbo_unbind(RHICmdBuffer *cmd, u32 screen_w, u32 screen_h) {
    rhi_offscreen_fbo_unbind(cmd, screen_w, screen_h);
}
/* R647: point-light depth cube. One six-slice D32 resource allocated
 * typeless (R32_TYPELESS) so it has two views over the same bytes: a
 * D32_FLOAT DSV per face for the depth pass, and the R32_FLOAT TEXTURECUBE
 * SRV the lighting pass samples (is_cube, see rhi_cmd_bind_texture). Slice
 * N is face N in D3D12 TextureCube order +X,-X,+Y,-Y,+Z,-Z — the same order
 * rhi.h documents for the face index. */
RHICubemapDepthFBO rhi_cubemap_depth_fbo_create(RHIDevice *dev, u32 size) {
    RHICubemapDepthFBO out;
    RHI_D3D12Context *ctx;
    RHI_D3D12Texture *depth;
    RHI_D3D12CubeDepthFBO *cd;
    RHITextureDesc tdesc;
    D3D12_DEPTH_STENCIL_VIEW_DESC dsv_desc;
    u32 idx;
    u32 f;
    memset(&out, 0, sizeof(out));
    if (dev == NULL || !rhi_drawable_dimensions_valid(size, size)) return out;
    ctx = (RHI_D3D12Context *)dev->backend_data;
    if (ctx == NULL || ctx->device_lost) return out;
    memset(&tdesc, 0, sizeof(tdesc));
    tdesc.width = size;
    tdesc.height = size;
    tdesc.format = RHI_FORMAT_D32_FLOAT;
    tdesc.mip_levels = 1u;
    out.depth_tex = rhi_d3d12_texture_create_ex(dev, &tdesc, 1, 6u);
    if (!rhi_handle_valid(out.depth_tex)) return out;
    depth = (RHI_D3D12Texture *)rhi_get_resource_typed(dev, out.depth_tex,
                                                       RHI_RES_TEXTURE);
    cd = (RHI_D3D12CubeDepthFBO *)calloc(1u, sizeof(*cd));
    if (depth == NULL || cd == NULL) {
        free(cd);
        rhi_texture_destroy(dev, out.depth_tex);
        memset(&out, 0, sizeof(out));
        return out;
    }
    depth->is_cube = 1u;
    for (f = 0u; f < 6u; ++f) cd->dsv_slots[f] = UINT_MAX;
    for (f = 0u; f < 6u; ++f) {
        cd->dsv_slots[f] = rhi_d3d12_descriptor_take(ctx, &ctx->dsv_alloc);
        if (cd->dsv_slots[f] == UINT_MAX) {
            u32 k;
            for (k = 0u; k < f; ++k)
                rhi_d3d12_descriptor_give_back(&ctx->dsv_alloc,
                    cd->dsv_slots[k], rhi_d3d12_retire_fence(ctx));
            free(cd);
            rhi_texture_destroy(dev, out.depth_tex);
            memset(&out, 0, sizeof(out));
            return out;
        }
        ZeroMemory(&dsv_desc, sizeof(dsv_desc));
        dsv_desc.Format = DXGI_FORMAT_D32_FLOAT;
        dsv_desc.ViewDimension = D3D12_DSV_DIMENSION_TEXTURE2DARRAY;
        dsv_desc.Flags = D3D12_DSV_FLAG_NONE;
        dsv_desc.Texture2DArray.MipSlice = 0u;
        dsv_desc.Texture2DArray.FirstArraySlice = f;
        dsv_desc.Texture2DArray.ArraySize = 1u;
        ID3D12Device_CreateDepthStencilView(ctx->device, depth->resource,
            &dsv_desc, rhi_d3d12_descriptor_cpu(&ctx->dsv_alloc, cd->dsv_slots[f]));
    }
    cd->size = size;
    idx = rhi_alloc_slot(dev);
    dev->slots[idx].ptr = cd;
    dev->slots[idx].type = RHI_RES_CUBEMAP_DEPTH_FBO;
    out.fb = rhi_make_handle(idx, dev->slots[idx].generation);
    out.size = size;
    return out;
}
void rhi_cubemap_depth_fbo_destroy(RHIDevice *dev, RHICubemapDepthFBO *fbo) {
    RHI_D3D12Context *ctx;
    RHI_D3D12CubeDepthFBO *cd;
    u32 f;
    if (dev == NULL || fbo == NULL) return;
    ctx = (RHI_D3D12Context *)dev->backend_data;
    if (rhi_handle_valid(fbo->depth_tex)) rhi_texture_destroy(dev, fbo->depth_tex);
    cd = (RHI_D3D12CubeDepthFBO *)rhi_get_resource_typed(dev, fbo->fb,
                                                         RHI_RES_CUBEMAP_DEPTH_FBO);
    if (cd != NULL) {
        /* Same rule as the shadow atlas: a recorded list may still hold the
         * DSVs, so the slots go back through the fence-retire path. */
        if (ctx != NULL)
            for (f = 0u; f < 6u; ++f)
                if (cd->dsv_slots[f] != UINT_MAX)
                    rhi_d3d12_descriptor_give_back(&ctx->dsv_alloc,
                        cd->dsv_slots[f], rhi_d3d12_retire_fence(ctx));
        free(cd);
        rhi_free_slot(dev, fbo->fb);
    }
    fbo->fb = RHI_HANDLE_NULL;
    fbo->depth_tex = RHI_HANDLE_NULL;
    fbo->size = 0u;
}
/* rhi.h R618 contract: binding a face clears it to 1.0. The viewport is the
 * offscreen one (memory row 0 = NDC y -1), the same row order GL and Vulkan
 * give a cube face: cube addressing puts face-space t = 0 on row 0, and
 * point_shadow_compute_face_vp builds each face for exactly that order. */
void rhi_cubemap_depth_fbo_bind_face(RHICmdBuffer *cmd,
                                     RHICubemapDepthFBO *fbo, u32 face) {
    RHI_D3D12Context *ctx = (RHI_D3D12Context *)cmd;
    ID3D12GraphicsCommandList *list;
    RHI_D3D12CubeDepthFBO *cd;
    RHI_D3D12Texture *depth;
    D3D12_CPU_DESCRIPTOR_HANDLE dsv;
    if (ctx == NULL || g_current_device == NULL || fbo == NULL || face >= 6u)
        return;
    cd = (RHI_D3D12CubeDepthFBO *)rhi_get_resource_typed(g_current_device,
        fbo->fb, RHI_RES_CUBEMAP_DEPTH_FBO);
    depth = (RHI_D3D12Texture *)rhi_get_resource_typed(g_current_device,
        fbo->depth_tex, RHI_RES_TEXTURE);
    if (cd == NULL || depth == NULL || depth->resource == NULL ||
        cd->dsv_slots[face] == UINT_MAX) return;
    list = rhi_d3d12_cmd_list(ctx);
    if (list == NULL) return;
    rhi_d3d12_warn_rt_srv_alias(ctx, depth, "DEPTH_WRITE");
    if (depth->state != D3D12_RESOURCE_STATE_DEPTH_WRITE) {
        rhi_d3d12_transition(list, depth->resource, depth->state,
                             D3D12_RESOURCE_STATE_DEPTH_WRITE);
        depth->state = D3D12_RESOURCE_STATE_DEPTH_WRITE;
    }
    dsv = rhi_d3d12_descriptor_cpu(&ctx->dsv_alloc, cd->dsv_slots[face]);
    ID3D12GraphicsCommandList_OMSetRenderTargets(list, 0u, NULL, TRUE, &dsv);
    ctx->bound_rtv_count = 0u;
    ctx->bound_dsv = dsv;
    ctx->bound_dsv_valid = 1u;
    rhi_d3d12_set_full_target_viewport(list, cd->size, cd->size);
    ID3D12GraphicsCommandList_ClearDepthStencilView(list, dsv,
        D3D12_CLEAR_FLAG_DEPTH, 1.0f, 0u, 0u, NULL);
}
void rhi_cubemap_depth_fbo_unbind(RHICmdBuffer *cmd, u32 screen_w,
                                  u32 screen_h) {
    rhi_cmd_unbind_shadow_map(cmd, screen_w, screen_h);
}

/* ---- compute ---- */
void rhi_cmd_dispatch(RHICmdBuffer *cmd, u32 x, u32 y, u32 z) {
    ID3D12GraphicsCommandList *list =
        rhi_d3d12_cmd_list((RHI_D3D12Context *)cmd);
    if (list == NULL) return;
    rhi_d3d12_flush_uniform_staging((RHI_D3D12Context *)cmd);
    ID3D12GraphicsCommandList_Dispatch(list, x, y, z);
}
/* R-matrix probe: build one UAV view over `buf` so the caller can enumerate
 * which descriptor field shape this runtime accepts.
 *
 * variant:
 *   0  Format=R32_TYPELESS, Buffer.Flags left 0        (illegal: no RAW)
 *   1  Format=R32_TYPELESS + Buffer.Flags = RAW
 *   2  Format=DXGI_FORMAT_UNKNOWN, Buffer.Flags left 0  (structured)
 *   3  Format=DXGI_FORMAT_UNKNOWN + StructureByteStride 16
 *   4  fully zeroed descriptor
 *   5  pDesc = NULL (D3D12 infers everything from the resource)
 *   6  Format=R32_TYPELESS + RAW + counter resource
 *
 * Internal, not part of the RHI; exists for test_d3d12_uav_matrix. */
int rhi_d3d12_probe_create_uav(RHIDevice *dev, RHIBuffer buf, int variant) {
    RHI_D3D12Context *ctx;
    RHI_D3D12Buffer *bd;
    D3D12_UNORDERED_ACCESS_VIEW_DESC desc;
    D3D12_CPU_DESCRIPTOR_HANDLE cpu;
    D3D12_CPU_DESCRIPTOR_HANDLE heap_base;
    ID3D12Resource *counter = NULL;
    UINT64 heap_size;
    UINT slot;
    int rc = 0;
    if (dev == NULL || variant < 0 || variant > 6) return -1;
    ctx = (RHI_D3D12Context *)dev->backend_data;
    if (ctx == NULL || ctx->device == NULL) return -1;
    bd = (RHI_D3D12Buffer *)rhi_get_resource_typed(dev, buf, RHI_RES_BUFFER);
    if (bd == NULL || bd->resource == NULL) return -1;
    slot = rhi_d3d12_descriptor_take(ctx, &ctx->cbv_srv_uav_alloc);
    if (slot == UINT_MAX) return -1;
    cpu = rhi_d3d12_descriptor_cpu(&ctx->cbv_srv_uav_alloc, slot);
    /* The handle is computed, not read back, so nothing ever proved it lands
     * inside the heap this allocator owns. An out-of-range slot would write
     * past the heap end and the only symptom would be the device dying
     * somewhere unrelated. */
    ID3D12DescriptorHeap_GetCPUDescriptorHandleForHeapStart(
        ctx->cbv_srv_uav_alloc.heap, &heap_base);
    heap_size = (UINT64)ctx->cbv_srv_uav_alloc.capacity *
                (UINT64)ctx->cbv_srv_uav_alloc.increment;
    if ((UINT64)(cpu.ptr - heap_base.ptr) >= heap_size) {
        rc = -2;  /* handle outside the heap */
        goto done;
    }

    ZeroMemory(&desc, sizeof(desc));
    /* Variants 0..3 and 6 are complete buffer views. ViewDimension and
     * NumElements are mandatory: leaving either zeroed is an illegal
     * descriptor, which D3D12 reports by removing the device with
     * DXGI_ERROR_INVALID_CALL. Variants 4 and 5 keep that failure on purpose
     * as negative cells. */
    if (variant <= 3 || variant == 6) {
        desc.ViewDimension = D3D12_UAV_DIMENSION_BUFFER;
        desc.Buffer.NumElements = (UINT)(bd->size / 4u);
    }
    switch (variant) {
    case 0:
    case 6:
        desc.Format = DXGI_FORMAT_R32_TYPELESS;
        break;
    case 1:
        /* RAW is what distinguishes byte-address access from structured.
         * Without it a R32_TYPELESS view is read as a structured UAV with
         * StructureByteStride 0, which is not a legal descriptor. */
        desc.Format = DXGI_FORMAT_R32_TYPELESS;
        desc.Buffer.Flags = D3D12_BUFFER_UAV_FLAG_RAW;
        break;
    case 2:
        desc.Format = DXGI_FORMAT_UNKNOWN;
        break;
    case 3:
        desc.Format = DXGI_FORMAT_UNKNOWN;
        desc.Buffer.StructureByteStride = 16u;
        desc.Buffer.NumElements = (UINT)(bd->size / 16u);
        break;
    default:
        break;
    }
    if (variant == 6) counter = bd->resource;
    ID3D12Device_CreateUnorderedAccessView(ctx->device, bd->resource, counter,
                                           (variant == 5) ? NULL : &desc, cpu);
done:
    rhi_d3d12_descriptor_give_back(&ctx->cbv_srv_uav_alloc, slot,
                                   ctx->next_fence);
    return rc;
}
/* Read-only storage buffer -> buffer SRV at register(tN). Unlike a UAV this
 * works on an UPLOAD-heap buffer (GENERIC_READ already includes the shader
 * resource states), which is where host-updated inputs such as the per-frame
 * visibility flags live. A recorded write earlier in this frame
 * (alias_resource) is what the view reads. */
static void rhi_d3d12_bind_buffer_srv(RHI_D3D12Context *ctx,
                                      ID3D12GraphicsCommandList *list,
                                      RHI_D3D12Pipeline *pd,
                                      RHI_D3D12Buffer *bd, u32 binding) {
    D3D12_SHADER_RESOURCE_VIEW_DESC srv;
    D3D12_GPU_DESCRIPTOR_HANDLE gpu;
    ID3D12Resource *source = bd->resource;
    UINT stride = pd->srv_buffer_strides[binding];
    UINT slot;
    if (stride != 0u ? bd->size < stride : bd->size < 4u) return;
    source = rhi_d3d12_buffer_view_source(ctx, bd);
    if (ctx->frame_srv_count >= RHI_D3D12_CBV_SRV_UAV_CAPACITY) return;
    slot = rhi_d3d12_descriptor_take(ctx, &ctx->cbv_srv_uav_alloc);
    if (slot == UINT_MAX) {
        LOG_WARN("D3D12: SRV descriptor heap exhausted");
        return;
    }
    ZeroMemory(&srv, sizeof(srv));
    srv.ViewDimension = D3D12_SRV_DIMENSION_BUFFER;
    srv.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
    if (stride == 0u) {
        srv.Format = DXGI_FORMAT_R32_TYPELESS;
        srv.Buffer.Flags = D3D12_BUFFER_SRV_FLAG_RAW;
        srv.Buffer.NumElements = (UINT)(bd->size / 4u);
    } else {
        srv.Format = DXGI_FORMAT_UNKNOWN;
        srv.Buffer.StructureByteStride = stride;
        srv.Buffer.NumElements = (UINT)(bd->size / stride);
    }
    ID3D12Device_CreateShaderResourceView(ctx->device, source, &srv,
        rhi_d3d12_descriptor_cpu(&ctx->cbv_srv_uav_alloc, slot));
    ctx->frame_srv_slots[ctx->frame_srv_count++] = slot;
    if (bd->device_local) {
        D3D12_RESOURCE_STATES read_state =
            D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE |
            D3D12_RESOURCE_STATE_NON_PIXEL_SHADER_RESOURCE;
        if (bd->state != read_state) {
            rhi_d3d12_transition(list, bd->resource, bd->state, read_state);
            bd->state = read_state;
        }
    }
    gpu = rhi_d3d12_descriptor_gpu(&ctx->cbv_srv_uav_alloc, slot);
    if (pd->is_compute)
        ID3D12GraphicsCommandList_SetComputeRootDescriptorTable(list,
            pd->image_root_params[binding], gpu);
    else
        ID3D12GraphicsCommandList_SetGraphicsRootDescriptorTable(list,
            pd->image_root_params[binding], gpu);
}

/* Storage buffer -> UAV at register(uN) of the bound pipeline, or -- when
 * the pipeline declares no UAV there -- a buffer SRV at register(tN).
 *
 * The descriptor must be complete: ViewDimension BUFFER and a non-zero
 * NumElements are mandatory, and the shape has to match the shader's
 * declaration -- RWByteAddressBuffer wants R32_TYPELESS + RAW (4-byte
 * elements), RWStructuredBuffer<T> wants UNKNOWN + StructureByteStride.
 * Anything else is an illegal descriptor, and since
 * CreateUnorderedAccessView returns void the runtime reports it by removing
 * the device (DXGI_ERROR_INVALID_CALL). R611-R636 misread exactly that as a
 * platform fault; see R637 and test_d3d12_uav_matrix.
 *
 * Only DEFAULT-heap buffers carry ALLOW_UNORDERED_ACCESS. A STORAGE buffer
 * created without initial_data stays on the UPLOAD heap (it is the
 * CPU-readback convention the staging twins rely on), and binding one as a
 * UAV is refused here rather than handed to the runtime. */
void rhi_cmd_bind_storage_buffer(RHICmdBuffer *cmd, RHIBuffer buf,
                                 u32 binding) {
    RHI_D3D12Context *ctx = (RHI_D3D12Context *)cmd;
    RHI_D3D12Pipeline *pd;
    RHI_D3D12Buffer *bd;
    ID3D12GraphicsCommandList *list;
    D3D12_UNORDERED_ACCESS_VIEW_DESC uav;
    D3D12_GPU_DESCRIPTOR_HANDLE gpu;
    UINT param, stride, slot;
    if (ctx == NULL || g_current_device == NULL || binding >= RHI_D3D12_MAX_REGISTERS) return;
    pd = (RHI_D3D12Pipeline *)ctx->bound_pipeline;
    list = rhi_d3d12_cmd_list(ctx);
    if (pd == NULL || list == NULL) return;
    bd = (RHI_D3D12Buffer *)rhi_get_resource_typed(g_current_device, buf,
                                                    RHI_RES_BUFFER);
    if (bd == NULL || bd->resource == NULL) return;
    param = pd->storage_root_params[binding];
    if (param == UINT_MAX) {
        /* No UAV at uN: GLSL's `readonly buffer` at binding N is an SRV at
         * tN in the sidecar convention. */
        if (pd->image_root_params[binding] != UINT_MAX &&
            pd->srv_buffer_strides[binding] != UINT_MAX)
            rhi_d3d12_bind_buffer_srv(ctx, list, pd, bd, binding);
        return;
    }
    stride = pd->storage_strides[binding];
    if (stride == UINT_MAX) {
        LOG_WARN("D3D12: register(u%u) is not a buffer view this backend can "
                 "describe -- storage bind refused", (unsigned)binding);
        return;
    }
    if (!bd->allow_uav) {
        LOG_WARN("D3D12: storage bind at u%u refused -- buffer was not created "
                 "with UAV access (STORAGE buffers need initial_data to be "
                 "DEFAULT-heap)", (unsigned)binding);
        return;
    }
    if (stride != 0u ? bd->size < stride : bd->size < 4u) return;
    if (ctx->frame_srv_count >= RHI_D3D12_CBV_SRV_UAV_CAPACITY) return;
    slot = rhi_d3d12_descriptor_take(ctx, &ctx->cbv_srv_uav_alloc);
    if (slot == UINT_MAX) {
        LOG_WARN("D3D12: UAV descriptor heap exhausted");
        return;
    }
    ZeroMemory(&uav, sizeof(uav));
    uav.ViewDimension = D3D12_UAV_DIMENSION_BUFFER;
    uav.Buffer.FirstElement = 0u;
    if (stride == 0u) {
        uav.Format = DXGI_FORMAT_R32_TYPELESS;
        uav.Buffer.Flags = D3D12_BUFFER_UAV_FLAG_RAW;
        uav.Buffer.NumElements = (UINT)(bd->size / 4u);
    } else {
        uav.Format = DXGI_FORMAT_UNKNOWN;
        uav.Buffer.StructureByteStride = stride;
        uav.Buffer.NumElements = (UINT)(bd->size / stride);
    }
    ID3D12Device_CreateUnorderedAccessView(ctx->device, bd->resource, NULL,
        &uav, rhi_d3d12_descriptor_cpu(&ctx->cbv_srv_uav_alloc, slot));
    ctx->frame_srv_slots[ctx->frame_srv_count++] = slot;
    if (bd->state != D3D12_RESOURCE_STATE_UNORDERED_ACCESS) {
        rhi_d3d12_transition(list, bd->resource, bd->state,
                             D3D12_RESOURCE_STATE_UNORDERED_ACCESS);
        bd->state = D3D12_RESOURCE_STATE_UNORDERED_ACCESS;
    }
    gpu = rhi_d3d12_descriptor_gpu(&ctx->cbv_srv_uav_alloc, slot);
    if (pd->is_compute)
        ID3D12GraphicsCommandList_SetComputeRootDescriptorTable(list, param, gpu);
    else
        ID3D12GraphicsCommandList_SetGraphicsRootDescriptorTable(list, param, gpu);
}
void rhi_cmd_bind_acceleration_structure(RHICmdBuffer *cmd,
                                         RHIAccelerationStructure structure,
                                         u32 binding) {
    (void)cmd; (void)structure; (void)binding;
}
void rhi_cmd_memory_barrier(RHICmdBuffer *cmd) {
    ID3D12GraphicsCommandList *list =
        rhi_d3d12_cmd_list((RHI_D3D12Context *)cmd);
    D3D12_RESOURCE_BARRIER barrier;
    if (list == NULL) return;
    /* UAV barrier over all resources (NULL = every UAV on the list): orders
     * compute writes against later reads, matching the VK full barrier. */
    ZeroMemory(&barrier, sizeof(barrier));
    barrier.Type = D3D12_RESOURCE_BARRIER_TYPE_UAV;
    barrier.UAV.pResource = NULL;
    ID3D12GraphicsCommandList_ResourceBarrier(list, 1u, &barrier);
}
/* R653: storage image = a single-mip TEXTURE2D UAV at register(u<unit>),
 * with only that mip moved to UNORDERED_ACCESS. */
void rhi_cmd_bind_image_texture(RHICmdBuffer *cmd, RHITexture tex, u32 unit,
                                u32 mip_level, bool write_only) {
    RHI_D3D12Context *ctx = (RHI_D3D12Context *)cmd;
    ID3D12GraphicsCommandList *list;
    RHI_D3D12Pipeline *pd;
    RHI_D3D12Texture *td;
    D3D12_UNORDERED_ACCESS_VIEW_DESC uav;
    D3D12_GPU_DESCRIPTOR_HANDLE gpu;
    UINT param, slot;
    (void)write_only;
    if (ctx == NULL || g_current_device == NULL || unit >= RHI_D3D12_MAX_REGISTERS) return;
    list = rhi_d3d12_cmd_list(ctx);
    pd = (RHI_D3D12Pipeline *)ctx->bound_pipeline;
    td = (RHI_D3D12Texture *)rhi_get_resource_typed(g_current_device, tex,
                                                    RHI_RES_TEXTURE);
    if (list == NULL || pd == NULL || td == NULL || td->resource == NULL ||
        mip_level >= td->mip_levels) return;
    param = pd->storage_root_params[unit];
    if (param == UINT_MAX) return;
    if (td->rhi_format != (UINT)RHI_FORMAT_R32_FLOAT &&
        td->rhi_format != (UINT)RHI_FORMAT_R16G16B16A16_SFLOAT) {
        LOG_WARN("D3D12: storage image bind refused -- only R32_FLOAT and "
                 "RGBA16F textures are created UAV-capable");
        return;
    }
    if (ctx->frame_srv_count >= RHI_D3D12_CBV_SRV_UAV_CAPACITY) return;
    slot = rhi_d3d12_descriptor_take(ctx, &ctx->cbv_srv_uav_alloc);
    if (slot == UINT_MAX) return;
    ZeroMemory(&uav, sizeof(uav));
    uav.Format = td->dxgi_format;
    uav.ViewDimension = D3D12_UAV_DIMENSION_TEXTURE2D;
    uav.Texture2D.MipSlice = mip_level;
    ID3D12Device_CreateUnorderedAccessView(ctx->device, td->resource, NULL,
        &uav, rhi_d3d12_descriptor_cpu(&ctx->cbv_srv_uav_alloc, slot));
    ctx->frame_srv_slots[ctx->frame_srv_count++] = slot;
    rhi_d3d12_tex_mip_transition(list, td, mip_level,
                                 D3D12_RESOURCE_STATE_UNORDERED_ACCESS);
    gpu = rhi_d3d12_descriptor_gpu(&ctx->cbv_srv_uav_alloc, slot);
    if (pd->is_compute)
        ID3D12GraphicsCommandList_SetComputeRootDescriptorTable(list, param, gpu);
    else
        ID3D12GraphicsCommandList_SetGraphicsRootDescriptorTable(list, param, gpu);
}
/* R654: one face at one mip of a colour cube as a TEXTURE2DARRAY UAV with
 * ArraySize 1 (the shader declares RWTexture2D, which a single-slice array
 * UAV satisfies), and only that subresource moved to UNORDERED_ACCESS. */
void rhi_cmd_bind_image_cubemap_face(RHICmdBuffer *cmd, RHICubemap cm,
                                     u32 face, u32 mip, u32 unit,
                                     bool write_only) {
    RHI_D3D12Context *ctx = (RHI_D3D12Context *)cmd;
    ID3D12GraphicsCommandList *list;
    RHI_D3D12Pipeline *pd;
    RHI_D3D12Texture *td;
    D3D12_UNORDERED_ACCESS_VIEW_DESC uav;
    D3D12_GPU_DESCRIPTOR_HANDLE gpu;
    UINT param, slot;
    (void)write_only;
    if (ctx == NULL || g_current_device == NULL || unit >= RHI_D3D12_MAX_REGISTERS || face >= 6u) return;
    list = rhi_d3d12_cmd_list(ctx);
    pd = (RHI_D3D12Pipeline *)ctx->bound_pipeline;
    td = rhi_d3d12_cube_tex(cm);
    if (list == NULL || pd == NULL || td == NULL || td->resource == NULL ||
        mip >= td->mip_levels) return;
    param = pd->storage_root_params[unit];
    if (param == UINT_MAX) return;
    if (td->rhi_format != (UINT)RHI_FORMAT_R16G16B16A16_SFLOAT) {
        LOG_WARN("D3D12: cube face storage bind refused -- only RGBA16F cubes "
                 "are created UAV-capable");
        return;
    }
    if (ctx->frame_srv_count >= RHI_D3D12_CBV_SRV_UAV_CAPACITY) return;
    slot = rhi_d3d12_descriptor_take(ctx, &ctx->cbv_srv_uav_alloc);
    if (slot == UINT_MAX) return;
    ZeroMemory(&uav, sizeof(uav));
    uav.Format = td->dxgi_format;
    uav.ViewDimension = D3D12_UAV_DIMENSION_TEXTURE2DARRAY;
    uav.Texture2DArray.MipSlice = mip;
    uav.Texture2DArray.FirstArraySlice = face;
    uav.Texture2DArray.ArraySize = 1u;
    ID3D12Device_CreateUnorderedAccessView(ctx->device, td->resource, NULL,
        &uav, rhi_d3d12_descriptor_cpu(&ctx->cbv_srv_uav_alloc, slot));
    ctx->frame_srv_slots[ctx->frame_srv_count++] = slot;
    rhi_d3d12_tex_sub_transition(list, td, face * td->mip_levels + mip,
                                 D3D12_RESOURCE_STATE_UNORDERED_ACCESS);
    gpu = rhi_d3d12_descriptor_gpu(&ctx->cbv_srv_uav_alloc, slot);
    if (pd->is_compute)
        ID3D12GraphicsCommandList_SetComputeRootDescriptorTable(list, param, gpu);
    else
        ID3D12GraphicsCommandList_SetGraphicsRootDescriptorTable(list, param, gpu);
}
void rhi_cmd_bind_cubemap_sampler(RHICmdBuffer *cmd, RHICubemap cm,
                                  RHISampler sampler, u32 unit) {
    rhi_cmd_bind_cubemap(cmd, cm, sampler, unit);
}
/* R653: a single-mip TEXTURE2D SRV at register(t<unit>) (rhi.h C-TEX-2:
 * mip 0 of the view is `mip_level`), with only that mip moved to the
 * shader-read state -- the others may be UAVs of the same pass. */
void rhi_cmd_bind_texture_mip(RHICmdBuffer *cmd, RHITexture tex,
                              RHISampler sampler, u32 unit, u32 mip_level) {
    RHI_D3D12Context *ctx = (RHI_D3D12Context *)cmd;
    ID3D12GraphicsCommandList *list;
    RHI_D3D12Pipeline *pd;
    RHI_D3D12Texture *td;
    D3D12_SHADER_RESOURCE_VIEW_DESC srv;
    D3D12_GPU_DESCRIPTOR_HANDLE gpu;
    UINT param, slot;
    (void)sampler;
    if (ctx == NULL || g_current_device == NULL || unit >= RHI_D3D12_MAX_REGISTERS) return;
    list = rhi_d3d12_cmd_list(ctx);
    pd = (RHI_D3D12Pipeline *)ctx->bound_pipeline;
    td = (RHI_D3D12Texture *)rhi_get_resource_typed(g_current_device, tex,
                                                    RHI_RES_TEXTURE);
    if (list == NULL || pd == NULL || td == NULL || td->resource == NULL ||
        mip_level >= td->mip_levels || td->array_size > 1u || td->is_cube)
        return;
    param = pd->image_root_params[unit];
    if (param == UINT_MAX) return;
    if (ctx->frame_srv_count >= RHI_D3D12_CBV_SRV_UAV_CAPACITY) return;
    slot = rhi_d3d12_descriptor_take(ctx, &ctx->cbv_srv_uav_alloc);
    if (slot == UINT_MAX) return;
    ZeroMemory(&srv, sizeof(srv));
    srv.Format = rhi_d3d12_srv_format(td);
    srv.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;
    srv.Texture2D.MostDetailedMip = mip_level;
    srv.Texture2D.MipLevels = 1u;
    srv.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
    ID3D12Device_CreateShaderResourceView(ctx->device, td->resource, &srv,
        rhi_d3d12_descriptor_cpu(&ctx->cbv_srv_uav_alloc, slot));
    ctx->frame_srv_slots[ctx->frame_srv_count++] = slot;
    rhi_d3d12_tex_mip_transition(list, td, mip_level,
        D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE |
        D3D12_RESOURCE_STATE_NON_PIXEL_SHADER_RESOURCE);
    gpu = rhi_d3d12_descriptor_gpu(&ctx->cbv_srv_uav_alloc, slot);
    if (pd->is_compute)
        ID3D12GraphicsCommandList_SetComputeRootDescriptorTable(list, param, gpu);
    else
        ID3D12GraphicsCommandList_SetGraphicsRootDescriptorTable(list, param, gpu);
}
/* R652: the per-unit binder already resolves the bound pipeline's SRV table
 * for register(t<unit>) and sets it on the compute root when the pipeline is
 * a compute one, so a compute-stage sampled texture is that same bind. */
void rhi_cmd_bind_texture_compute(RHICmdBuffer *cmd, RHITexture tex,
                                  RHISampler sampler, u32 unit) {
    rhi_cmd_bind_texture(cmd, tex, sampler, unit);
}
void rhi_cmd_transition_depth_to_read(RHICmdBuffer *cmd,
                                      RHITexture depth_tex) {
    RHI_D3D12Context *ctx = (RHI_D3D12Context *)cmd;
    ID3D12GraphicsCommandList *list;
    RHI_D3D12Texture *td;
    D3D12_RESOURCE_STATES read_state;
    if (ctx == NULL || g_current_device == NULL) return;
    list = rhi_d3d12_cmd_list(ctx);
    if (list == NULL) return;
    td = (RHI_D3D12Texture *)rhi_get_resource_typed(g_current_device, depth_tex,
                                                    RHI_RES_TEXTURE);
    if (td == NULL || td->resource == NULL) return;
    read_state = D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE |
                 D3D12_RESOURCE_STATE_NON_PIXEL_SHADER_RESOURCE;
    if (td->state == read_state) return;
    rhi_d3d12_transition(list, td->resource, td->state, read_state);
    td->state = read_state;
}

/* ---- screenshot ---- */
/* Swapchain readback, mirroring the Vulkan path: a one-shot copy from the
 * acquired back buffer into a READBACK staging buffer, submitted and waited
 * on the same queue. Contract (rhi.h): the rect is top-left origin and rows
 * come back top-down. The swap chain is B8G8R8A8, so BGRA is swizzled to
 * RGBA on the way out — the same correction the VK BGRA path makes. */
bool rhi_screenshot(RHIDevice *dev, u32 x, u32 y, u32 w, u32 h, u8 *pixels,
                    usize pixel_bytes) {
    RHI_D3D12Context *ctx;
    RHI_D3D12Swapchain *sc;
    ID3D12Resource *backbuffer;
    ID3D12Resource *staging = NULL;
    D3D12_TEXTURE_COPY_LOCATION dst_loc;
    D3D12_TEXTURE_COPY_LOCATION src_loc;
    D3D12_PLACED_SUBRESOURCE_FOOTPRINT footprint;
    D3D12_BOX box;
    D3D12_RANGE read_range;
    UINT row_pitch;
    usize row_bytes;
    const u8 *src;
    u32 row_i;
    HRESULT hr = S_OK;

    if (dev == NULL || pixels == NULL) return false;
    ctx = (RHI_D3D12Context *)dev->backend_data;
    if (ctx == NULL || ctx->device_lost) return false;
    sc = &ctx->swapchain;
    if (!ctx->swapchain_ready || sc->swapchain == NULL) return false;
    if (!rhi_screenshot_region_validate(x, y, w, h, sc->width, sc->height,
                                        pixel_bytes)) {
        return false;
    }
    /* Legal only while a swapchain image is acquired: post-present the
     * compositor owns the back buffer (same rule and reason as the VK
     * backend). Refuse loudly rather than read an undefined image. */
    if (!ctx->frame_started && !ctx->frame_submitted) {
        LOG_ERROR("D3D12: rhi_screenshot outside an acquired frame is illegal "
                  "(back buffer not owned) — call between frame_begin and present");
        return false;
    }

    row_bytes = (usize)w * 4u;
    /* CopyTextureRegion requires the placed-footprint RowPitch to be a
     * multiple of D3D12_TEXTURE_DATA_PITCH_ALIGNMENT (256); a 4-px row is
     * 16 bytes, so the staging copy would be rejected outright. */
    row_pitch = ((UINT)row_bytes + D3D12_TEXTURE_DATA_PITCH_ALIGNMENT - 1u)
                / D3D12_TEXTURE_DATA_PITCH_ALIGNMENT
                * D3D12_TEXTURE_DATA_PITCH_ALIGNMENT;
    if (sc->current_index >= RHI_D3D12_BACKBUFFER_COUNT) return false;
    backbuffer = sc->backbuffers[sc->current_index];
    if (backbuffer == NULL) return false;

    /* Drain first: the copy must see this frame's rendering, and any
     * present packet queued after frame_end may still reference the image. */
    if (rhi_d3d12_drain_gpu(ctx) != RHI_RESULT_OK) {
        LOG_ERROR("D3D12: screenshot pre-copy GPU drain failed");
        return false;
    }

    staging = rhi_d3d12_staging_buffer(ctx, D3D12_HEAP_TYPE_READBACK,
                                      (UINT64)row_pitch * (UINT64)h);
    if (staging == NULL) {
        LOG_ERROR("D3D12: screenshot staging buffer alloc failed");
        return false;
    }

    /* Same reusable one-shot list the texture upload / read_pixels
     * paths use: the engine declares transitions from CPU-tracked
     * state rather than assuming an ambient value. */
    if (FAILED(rhi_d3d12_oneshot_begin(ctx))) {
        LOG_ERROR("D3D12: screenshot oneshot begin failed");
        goto cleanup;
    }

    ZeroMemory(&dst_loc, sizeof(dst_loc));
    dst_loc.pResource = staging;
    dst_loc.Type = D3D12_TEXTURE_COPY_TYPE_PLACED_FOOTPRINT;
    ZeroMemory(&footprint, sizeof(footprint));
    footprint.Offset = 0u;
    footprint.Footprint.Format = sc->format;
    footprint.Footprint.Width = w;
    footprint.Footprint.Height = h;
    footprint.Footprint.Depth = 1u;
    footprint.Footprint.RowPitch = row_pitch;
    dst_loc.PlacedFootprint = footprint;
    ZeroMemory(&src_loc, sizeof(src_loc));
    src_loc.pResource = backbuffer;
    src_loc.Type = D3D12_TEXTURE_COPY_TYPE_SUBRESOURCE_INDEX;
    src_loc.SubresourceIndex = 0u;

    /* pSrcBox must name the region explicitly: NULL would mean the whole
     * source subresource (the full 640x480), which cannot fit the 4x4
     * placed footprint and fails Close with E_INVALIDARG. */
    box.left = x; box.top = y; box.right = x + w; box.bottom = y + h;
    /* front/back select the depth slice; leaving them equal makes an
     * empty box and the copy silently does nothing. */
    box.front = 0; box.back = 1;
    rhi_d3d12_transition(ctx->upload_list, backbuffer, D3D12_RESOURCE_STATE_PRESENT,
                         D3D12_RESOURCE_STATE_COPY_SOURCE);
    /* agility-signature variant: pDst is a copy location (subresource
     * index is implied); DstX/Y/Z are offsets inside that footprint. */
    ID3D12GraphicsCommandList_CopyTextureRegion(ctx->upload_list, &dst_loc, 0u, 0u, 0u,
                                                &src_loc, &box);
    rhi_d3d12_transition(ctx->upload_list, backbuffer,
                         D3D12_RESOURCE_STATE_COPY_SOURCE,
                         D3D12_RESOURCE_STATE_PRESENT);
    /* flush closes, executes, signals and waits; the copy is queued
     * behind the frame submit on the same queue, so the staging
     * buffer is complete when we map it. */
    if (rhi_d3d12_oneshot_flush(ctx) != RHI_RESULT_OK) {
        hr = E_FAIL;
        goto cleanup;
    }
    /* Wait on the queue itself: the copy is the last thing enqueued, so a
     * fresh signal ordered behind it is a full drain for this readback. */
    if (rhi_d3d12_drain_gpu(ctx) != RHI_RESULT_OK) {
        hr = E_FAIL;  /* stale S_OK must not report a copy that never landed */
        goto cleanup;
    }

    ZeroMemory(&read_range, sizeof(read_range));
    hr = ID3D12Resource_Map(staging, 0u, &read_range, (void **)&src);
    if (FAILED(hr)) { LOG_ERROR("D3D12: screenshot map failed"); goto cleanup; }
    for (row_i = 0u; row_i < h; ++row_i) {
        const u8 *row = src + (usize)row_i * (usize)row_pitch;
        u8 *dst = pixels + (usize)row_i * row_bytes;
        usize i;
        for (i = 0u; i < row_bytes; i += 4u) {
            dst[i + 0u] = row[i + 2u]; /* R <- B */
            dst[i + 1u] = row[i + 1u]; /* G <- G */
            dst[i + 2u] = row[i + 0u]; /* B <- R */
            dst[i + 3u] = row[i + 3u]; /* A <- A */
        }
    }
    ID3D12Resource_Unmap(staging, 0u, NULL);

cleanup:
    if (!SUCCEEDED(hr))
        LOG_ERROR("D3D12: screenshot failed, hr=0x%08lx (x=%u y=%u w=%u h=%u backbuffer_index=%u)",
                  (unsigned long)hr, x, y, w, h, sc->current_index);
    rhi_d3d12_release((IUnknown **)&staging);
    return SUCCEEDED(hr);
}

/* ---- GPU timer ----
 * R663: a timestamp query heap with two queries per frame slot (begin, end),
 * resolved into a persistent READBACK buffer when the end timestamp is
 * written. The slot is the frame-parity slot being recorded, so a frame in
 * flight never overwrites the results of the one before it. Results are read
 * from the slot that was submitted LAST (parity ^ 1, both during and after a
 * frame) and only once its frame fence has completed, so elapsed_ms never
 * blocks: it returns the newest finished measurement, or 0 before the first
 * one lands. GL and Vulkan report one frame of latency in the same way; the
 * difference is that a finished value stays readable instead of dropping to 0
 * after one read, which is what the debug overlay and the trace export want
 * when they sample at different points of the frame. */
struct RHIGPUTimer {
    RHIDevice *owner;
    ID3D12QueryHeap *heap;
    ID3D12Resource *readback;       /* 2 slots x 2 x u64, kept in COPY_DEST */
    UINT64 frequency;               /* timestamp ticks per second */
    UINT cur_slot;                  /* slot begin() recorded into */
    UINT started;                   /* begin() seen, end() not yet */
    UINT recorded[2];               /* slot holds a resolved measurement */
    f64 last_ms;
};

RHIGPUTimer *rhi_gpu_timer_create(RHIDevice *dev) {
    RHI_D3D12Context *ctx;
    RHIGPUTimer *t;
    D3D12_QUERY_HEAP_DESC qd;
    if (dev == NULL) return NULL;
    ctx = (RHI_D3D12Context *)dev->backend_data;
    if (ctx == NULL || ctx->device_lost || ctx->direct_queue == NULL) return NULL;
    t = (RHIGPUTimer *)calloc(1u, sizeof(*t));
    if (t == NULL) return NULL;
    ZeroMemory(&qd, sizeof(qd));
    qd.Type = D3D12_QUERY_HEAP_TYPE_TIMESTAMP;
    qd.Count = 4u;
    if (FAILED(ID3D12Device_CreateQueryHeap(ctx->device, &qd, &IID_ID3D12QueryHeap,
                                            (void **)&t->heap)) ||
        FAILED(ID3D12CommandQueue_GetTimestampFrequency(ctx->direct_queue,
                                                        &t->frequency)) ||
        t->frequency == 0u) {
        LOG_WARN("D3D12: timestamp queries unavailable -- GPU timer disabled");
        rhi_d3d12_release((IUnknown **)&t->heap);
        free(t);
        return NULL;
    }
    t->readback = rhi_d3d12_staging_buffer(ctx, D3D12_HEAP_TYPE_READBACK,
                                           4u * sizeof(UINT64));
    if (t->readback == NULL) {
        rhi_d3d12_release((IUnknown **)&t->heap);
        free(t);
        return NULL;
    }
    t->owner = dev;
    return t;
}

void rhi_gpu_timer_destroy(RHIDevice *dev, RHIGPUTimer *t) {
    RHI_D3D12Context *ctx;
    if (t == NULL) return;
    ctx = dev != NULL ? (RHI_D3D12Context *)dev->backend_data : NULL;
    /* A command list in flight may still reference both objects. */
    rhi_d3d12_release_deferred(ctx, (IUnknown **)&t->readback);
    rhi_d3d12_release_deferred(ctx, (IUnknown **)&t->heap);
    free(t);
}

void rhi_gpu_timer_begin(RHIGPUTimer *t) {
    RHI_D3D12Context *ctx;
    ID3D12GraphicsCommandList *list;
    if (t == NULL || t->owner == NULL || g_current_device != t->owner) return;
    ctx = (RHI_D3D12Context *)t->owner->backend_data;
    list = rhi_d3d12_cmd_list(ctx);
    if (list == NULL) return;
    t->cur_slot = ctx->frame_parity & 1u;
    t->recorded[t->cur_slot] = 0u;
    ID3D12GraphicsCommandList_EndQuery(list, t->heap,
                                       D3D12_QUERY_TYPE_TIMESTAMP,
                                       t->cur_slot * 2u);
    t->started = 1u;
}

void rhi_gpu_timer_end(RHIGPUTimer *t) {
    RHI_D3D12Context *ctx;
    ID3D12GraphicsCommandList *list;
    if (t == NULL || t->owner == NULL || !t->started ||
        g_current_device != t->owner)
        return;
    ctx = (RHI_D3D12Context *)t->owner->backend_data;
    list = rhi_d3d12_cmd_list(ctx);
    /* begin() and end() must land in the same frame: the pair shares one
     * slot of the heap. */
    if (list == NULL || t->cur_slot != (ctx->frame_parity & 1u)) {
        t->started = 0u;
        return;
    }
    ID3D12GraphicsCommandList_EndQuery(list, t->heap,
                                       D3D12_QUERY_TYPE_TIMESTAMP,
                                       t->cur_slot * 2u + 1u);
    ID3D12GraphicsCommandList_ResolveQueryData(list, t->heap,
        D3D12_QUERY_TYPE_TIMESTAMP, t->cur_slot * 2u, 2u, t->readback,
        (UINT64)t->cur_slot * 2u * sizeof(UINT64));
    t->recorded[t->cur_slot] = 1u;
    t->started = 0u;
}

f64 rhi_gpu_timer_elapsed_ms(RHIGPUTimer *t) {
    RHI_D3D12Context *ctx;
    UINT slot;
    if (t == NULL || t->owner == NULL || g_current_device != t->owner)
        return 0.0;
    ctx = (RHI_D3D12Context *)t->owner->backend_data;
    if (ctx == NULL || ctx->device_lost || ctx->fence == NULL) return t->last_ms;
    /* The slot submitted last: while a frame records, the recording slot is
     * parity and the previous frame sits in the other one; after frame_end the
     * parity has flipped, so it is again the other one. */
    slot = (ctx->frame_parity + 1u) & 1u;
    if (!t->recorded[slot] || ctx->frame_fence[slot] == 0u ||
        ID3D12Fence_GetCompletedValue(ctx->fence) < ctx->frame_fence[slot])
        return t->last_ms;
    {
        D3D12_RANGE range;
        UINT64 *ticks = NULL;
        range.Begin = (SIZE_T)slot * 2u * sizeof(UINT64);
        range.End = range.Begin + 2u * sizeof(UINT64);
        if (SUCCEEDED(ID3D12Resource_Map(t->readback, 0u, &range, (void **)&ticks)) &&
            ticks != NULL) {
            UINT64 a = ticks[slot * 2u], z = ticks[slot * 2u + 1u];
            D3D12_RANGE none = { 0u, 0u };
            ID3D12Resource_Unmap(t->readback, 0u, &none);
            if (z >= a)
                t->last_ms = (f64)(z - a) * 1000.0 / (f64)t->frequency;
        }
    }
    return t->last_ms;
}

#endif
