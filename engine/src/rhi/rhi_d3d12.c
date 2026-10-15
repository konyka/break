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

#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#define RHI_D3D12_FENCE_TIMEOUT_MS 20000u

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

static void rhi_d3d12_cleanup_objects(RHI_D3D12Context *context) {
    size_t i;
    if (context == NULL) return;
    if (context->fence_event != NULL) {
        CloseHandle(context->fence_event);
        context->fence_event = NULL;
    }
    rhi_d3d12_release((IUnknown **)&context->fence);
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
    /* CreateDXGIFactory2 with flags=0; the debug flag is Task 8's knob. */
    HRESULT hr = CreateDXGIFactory2(0u, &IID_IDXGIFactory6,
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
    if (!ctx->dred_enabled) return;
    if (FAILED(ID3D12Device_QueryInterface(ctx->device,
            &IID_ID3D12DeviceRemovedExtendedData1, (void **)&dred))) return;
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
    heap_desc.NumDescriptors = RHI_D3D12_BACKBUFFER_COUNT;
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
    hr = ID3D12Device_CreateDescriptorHeap(context->device, &heap_desc,
                                           &IID_ID3D12DescriptorHeap,
                                           (void **)&context->dsv_heap);
    if (FAILED(hr)) goto fail;
    heap_desc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
    heap_desc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;
    heap_desc.NumDescriptors = 16u;
    hr = ID3D12Device_CreateDescriptorHeap(context->device, &heap_desc,
                                           &IID_ID3D12DescriptorHeap,
                                           (void **)&context->cbv_srv_uav_heap);
    if (FAILED(hr)) goto fail;
    context->rtv_increment = ID3D12Device_GetDescriptorHandleIncrementSize(
        context->device, D3D12_DESCRIPTOR_HEAP_TYPE_RTV);
    context->dsv_increment = ID3D12Device_GetDescriptorHandleIncrementSize(
        context->device, D3D12_DESCRIPTOR_HEAP_TYPE_DSV);
    context->cbv_srv_uav_increment = ID3D12Device_GetDescriptorHandleIncrementSize(
        context->device, D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);
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
    value = context->next_fence++;
    hr = ID3D12CommandQueue_Signal(context->direct_queue, context->fence, value);
    if (FAILED(hr)) return hr;
    *out_fence = value;
    return S_OK;
}

/* ---- swapchain (plan D Task 4) ----
 * Flip model, 3 back buffers (see RHI_D3D12_BACKBUFFER_COUNT in the header).
 * Decision record: present damage uses RHIPresentRect directly — it is a
 * top-left-origin {x,y,w,h} quad, the same convention DXGI_PRESENT_PARAMETERS
 * dirty rects use, so the GL/EGL bottom-left conversion
 * (rhi_present_damage_to_bottom_left) is NOT applied on this backend. */

static void rhi_d3d12_swapchain_create_rtvs(RHI_D3D12Context *context,
                                            RHI_D3D12Swapchain *sc) {
    D3D12_CPU_DESCRIPTOR_HANDLE base;
    UINT i;
    ID3D12DescriptorHeap_GetCPUDescriptorHandleForHeapStart(
        context->rtv_heap, &base);
    for (i = 0u; i < RHI_D3D12_BACKBUFFER_COUNT; ++i) {
        D3D12_CPU_DESCRIPTOR_HANDLE handle = base;
        handle.ptr += (SIZE_T)i * (SIZE_T)context->rtv_increment;
        ID3D12Device_CreateRenderTargetView(context->device,
                                            sc->backbuffers[i], NULL, handle);
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
    g_current_device = dev;
    return dev;
}
void rhi_device_destroy(RHIDevice *dev) {
    RHI_D3D12Context *ctx;
    UINT slot;
    if (dev == NULL) return;
    ctx = (RHI_D3D12Context *)dev->backend_data;
    if (ctx != NULL) {
        /* Task 3 review handoff + spec §4.3: forced drain before release —
         * freeing queues/fences/back buffers while GPU work is in flight
         * races the teardown. A latched-lost device skips the waits (fences
         * may never signal post-TDR). */
        if (!ctx->device_lost) {
            for (slot = 0u; slot < 2u; ++slot)
                (void)rhi_d3d12_wait_frame_slot(ctx, slot);
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
    UINT slot;
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
    /* spec §4.3: drain before touching swapchain buffers. */
    for (slot = 0u; slot < 2u; ++slot) {
        RHIResult wr = rhi_d3d12_wait_frame_slot(ctx, slot);
        if (wr != RHI_RESULT_OK) {
            rhi_device_set_lifecycle_result(dev, wr);
            rhi_device_control_release(dev);
            return;
        }
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
    ID3D12DescriptorHeap_GetCPUDescriptorHandleForHeapStart(ctx->rtv_heap, &rtv);
    rtv.ptr += (SIZE_T)sc->current_index * (SIZE_T)ctx->rtv_increment;
    ID3D12GraphicsCommandList_OMSetRenderTargets(ctx->command_lists[slot],
                                                 1u, &rtv, FALSE, NULL);
    ctx->frame_started = 1u;
    ctx->frame_submitted = 0u;
    ctx->acquire_in_flight = 1u;
    rhi_device_set_lifecycle_result(dev, RHI_RESULT_OK);
    return (RHICmdBuffer *)ctx;
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
        rhi_frame_owner_release(dev);
        return;
    }
    ctx->frame_fence[slot] = fence;
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
bool rhi_backend_cmd_build_blas_one_triangle(
    RHICmdBuffer *cmd, RHIDevice *dev, RHIAccelerationStructure blas,
    const RHIBLASOneTriangleDesc *desc,
    RHIBuffer scratch_buffer, usize scratch_offset) {
    (void)cmd; (void)dev; (void)blas; (void)desc;
    (void)scratch_buffer; (void)scratch_offset;
    return false;
}
u64 rhi_backend_acceleration_structure_get_device_address(
    RHIDevice *dev, RHIAccelerationStructure structure) {
    (void)dev; (void)structure; return 0u;
}
bool rhi_backend_tlas_one_instance_get_build_sizes(
    RHIDevice *dev, RHIBuffer instance_buffer,
    RHIAccelerationStructureBuildSizes *out_sizes) {
    (void)dev; (void)instance_buffer; (void)out_sizes; return false;
}
bool rhi_backend_cmd_build_tlas_one_instance(
    RHICmdBuffer *cmd, RHIDevice *dev, RHIAccelerationStructure tlas,
    RHIBuffer instance_buffer, RHIBuffer scratch_buffer, usize scratch_offset) {
    (void)cmd; (void)dev; (void)tlas; (void)instance_buffer;
    (void)scratch_buffer; (void)scratch_offset;
    return false;
}
bool rhi_backend_acceleration_structure_get_vk_handle(
    RHIDevice *dev, RHIAccelerationStructure structure, void **out_handle) {
    (void)dev; (void)structure; (void)out_handle; return false;
}
bool rhi_blas_one_triangle_get_build_sizes(
    RHIDevice *dev, const RHIBLASOneTriangleDesc *desc,
    RHIAccelerationStructureBuildSizes *out_sizes) {
    (void)dev; (void)desc; (void)out_sizes; return false;
}
RHIAccelerationStructure rhi_backend_acceleration_structure_create(
    RHIDevice *dev, const RHIAccelerationStructureDesc *desc) {
    (void)dev; (void)desc; return RHI_HANDLE_NULL;
}
void rhi_backend_acceleration_structure_destroy(
    RHIDevice *dev, RHIAccelerationStructure structure) {
    (void)dev; (void)structure;
}

u32 rhi_vk_validation_message_count(void) { return 0u; }
void rhi_vk_validation_message_count_reset(void) {}
bool rhi_vk_validation_gate_active(void) { return false; }
void rhi_vk_validation_set_enabled(bool enabled) { (void)enabled; }

/* ---- resource creation ---- */
RHIBuffer rhi_buffer_create(RHIDevice *dev, const RHIBufferDesc *desc) {
    (void)dev; (void)desc; return RHI_HANDLE_NULL;
}
void rhi_buffer_destroy(RHIDevice *dev, RHIBuffer buf) { (void)dev; (void)buf; }
RHIShader rhi_shader_create(RHIDevice *dev, const char *source, usize len,
                            bool is_fragment) {
    (void)dev; (void)source; (void)len; (void)is_fragment;
    return RHI_HANDLE_NULL;
}
RHIShader rhi_shader_create_compute(RHIDevice *dev, const char *source,
                                    usize len) {
    (void)dev; (void)source; (void)len; return RHI_HANDLE_NULL;
}
void rhi_shader_destroy(RHIDevice *dev, RHIShader shader) {
    (void)dev; (void)shader;
}
RHIPipeline rhi_pipeline_create(RHIDevice *dev, const RHIPipelineDesc *desc) {
    (void)dev; (void)desc; return RHI_HANDLE_NULL;
}
void rhi_pipeline_destroy(RHIDevice *dev, RHIPipeline pipe) {
    (void)dev; (void)pipe;
}
RHITexture rhi_texture_create(RHIDevice *dev, const RHITextureDesc *desc) {
    (void)dev; (void)desc; return RHI_HANDLE_NULL;
}
void rhi_texture_destroy(RHIDevice *dev, RHITexture tex) {
    (void)dev; (void)tex;
}
RHITexture rhi_texture_array_create(RHIDevice *dev, u32 width, u32 height,
                                    u32 layers, RHIFormat fmt) {
    (void)dev; (void)width; (void)height; (void)layers; (void)fmt;
    return RHI_HANDLE_NULL;
}
void rhi_texture_array_upload_layer(RHIDevice *dev, RHITexture tex, u32 layer,
                                    const void *rgba8, usize size) {
    (void)dev; (void)tex; (void)layer; (void)rgba8; (void)size;
}
bool rhi_texture_get_size(RHIDevice *dev, RHITexture tex, u32 *out_w,
                          u32 *out_h) {
    (void)dev; (void)tex; (void)out_w; (void)out_h; return false;
}
bool rhi_texture_read_pixels(RHIDevice *dev, RHITexture tex, void *dst_rgba8,
                             usize size) {
    (void)dev; (void)tex; (void)dst_rgba8; (void)size; return false;
}
void rhi_texture_upload_mip(RHIDevice *dev, RHITexture tex, u32 mip_level,
                            u32 width, u32 height, const void *data,
                            usize size) {
    (void)dev; (void)tex; (void)mip_level; (void)width; (void)height;
    (void)data; (void)size;
}
RHISampler rhi_sampler_create(RHIDevice *dev, const RHISamplerDesc *desc) {
    (void)dev; (void)desc; return RHI_HANDLE_NULL;
}
void rhi_sampler_destroy(RHIDevice *dev, RHISampler sampler) {
    (void)dev; (void)sampler;
}

/* ---- command recording ---- */
void rhi_cmd_begin_render_pass(RHICmdBuffer *cmd) { (void)cmd; }
void rhi_cmd_end_render_pass(RHICmdBuffer *cmd) { (void)cmd; }
void rhi_cmd_bind_pipeline(RHICmdBuffer *cmd, RHIPipeline pipe) {
    (void)cmd; (void)pipe;
}
void rhi_cmd_bind_vertex_buffer(RHICmdBuffer *cmd, RHIBuffer buf,
                                usize offset) {
    (void)cmd; (void)buf; (void)offset;
}
void rhi_cmd_bind_index_buffer(RHICmdBuffer *cmd, RHIBuffer buf, usize offset,
                               bool is_u32) {
    (void)cmd; (void)buf; (void)offset; (void)is_u32;
}
void rhi_cmd_set_viewport(RHICmdBuffer *cmd, f32 x, f32 y, f32 w, f32 h,
                          f32 min_depth, f32 max_depth) {
    (void)cmd; (void)x; (void)y; (void)w; (void)h; (void)min_depth;
    (void)max_depth;
}
void rhi_cmd_set_scissor(RHICmdBuffer *cmd, i32 x, i32 y, u32 w, u32 h) {
    (void)cmd; (void)x; (void)y; (void)w; (void)h;
}
void rhi_cmd_set_scissor_top_left(RHICmdBuffer *cmd, u32 x, u32 y, u32 w,
                                  u32 h) {
    (void)cmd; (void)x; (void)y; (void)w; (void)h;
}
void rhi_cmd_set_shadow_viewport(RHICmdBuffer *cmd, u32 x, u32 y, u32 w,
                                 u32 h) {
    (void)cmd; (void)x; (void)y; (void)w; (void)h;
}
void rhi_cmd_draw(RHICmdBuffer *cmd, u32 vertex_count, u32 instance_count) {
    (void)cmd; (void)vertex_count; (void)instance_count;
}
void rhi_cmd_draw_base(RHICmdBuffer *cmd, u32 vertex_count, u32 instance_count,
                       u32 first_vertex) {
    (void)cmd; (void)vertex_count; (void)instance_count; (void)first_vertex;
}
void rhi_cmd_draw_indexed(RHICmdBuffer *cmd, u32 index_count,
                          u32 instance_count) {
    (void)cmd; (void)index_count; (void)instance_count;
}
void rhi_cmd_draw_indexed_base(RHICmdBuffer *cmd, u32 index_count,
                               u32 instance_count, u32 first_index,
                               i32 vertex_offset) {
    (void)cmd; (void)index_count; (void)instance_count; (void)first_index;
    (void)vertex_offset;
}
void rhi_cmd_draw_indirect(RHIDevice *dev, RHIBuffer cmd_buf, u32 offset,
                           u32 draw_count, u32 stride) {
    (void)dev; (void)cmd_buf; (void)offset; (void)draw_count; (void)stride;
}
void rhi_cmd_draw_indexed_indirect(RHIDevice *dev, RHIBuffer cmd_buf,
                                   u32 offset, u32 draw_count, u32 stride) {
    (void)dev; (void)cmd_buf; (void)offset; (void)draw_count; (void)stride;
}
void rhi_cmd_draw_indexed_indirect_count(RHIDevice *dev, RHIBuffer cmd_buf,
                                         u32 cmd_offset, RHIBuffer count_buf,
                                         u32 count_offset, u32 max_draws,
                                         u32 stride) {
    (void)dev; (void)cmd_buf; (void)cmd_offset; (void)count_buf;
    (void)count_offset; (void)max_draws; (void)stride;
}
void rhi_cmd_clear_color(RHICmdBuffer *cmd, f32 r, f32 g, f32 b, f32 a) {
    (void)cmd; (void)r; (void)g; (void)b; (void)a;
}
void rhi_cmd_clear_color_attachment(RHICmdBuffer *cmd, u32 attachment, f32 r,
                                    f32 g, f32 b, f32 a) {
    (void)cmd; (void)attachment; (void)r; (void)g; (void)b; (void)a;
}
void rhi_cmd_bind_texture(RHICmdBuffer *cmd, RHITexture tex,
                          RHISampler sampler, u32 unit) {
    (void)cmd; (void)tex; (void)sampler; (void)unit;
}
void rhi_cmd_bind_shadow_texture(RHICmdBuffer *cmd, RHITexture shadow_tex,
                                 RHISampler sampler) {
    (void)cmd; (void)shadow_tex; (void)sampler;
}
void rhi_cmd_bind_uniform_buffer(RHICmdBuffer *cmd, RHIBuffer buf,
                                 u32 binding) {
    (void)cmd; (void)buf; (void)binding;
}
void rhi_cmd_set_uniform_mat4(RHICmdBuffer *cmd, i32 location, const f32 *m) {
    (void)cmd; (void)location; (void)m;
}
void rhi_cmd_set_uniform_vec3(RHICmdBuffer *cmd, i32 location, f32 x, f32 y,
                              f32 z) {
    (void)cmd; (void)location; (void)x; (void)y; (void)z;
}
void rhi_cmd_set_uniform_vec2(RHICmdBuffer *cmd, i32 location, f32 x, f32 y) {
    (void)cmd; (void)location; (void)x; (void)y;
}
void rhi_cmd_set_uniform_vec4(RHICmdBuffer *cmd, i32 location, f32 x, f32 y,
                              f32 z, f32 w) {
    (void)cmd; (void)location; (void)x; (void)y; (void)z; (void)w;
}
void rhi_cmd_set_uniform_f32(RHICmdBuffer *cmd, i32 location, f32 v) {
    (void)cmd; (void)location; (void)v;
}
void rhi_cmd_set_uniform_i32(RHICmdBuffer *cmd, i32 location, i32 v) {
    (void)cmd; (void)location; (void)v;
}
void rhi_cmd_push_constants(RHICmdBuffer *cmd, u32 offset, const void *data,
                            u32 size) {
    (void)cmd; (void)offset; (void)data; (void)size;
}
void rhi_cmd_set_uniform_bytes(RHICmdBuffer *cmd, i32 location,
                               const void *data, u32 size) {
    (void)cmd; (void)location; (void)data; (void)size;
}
i32 rhi_pipeline_get_uniform_location(RHIDevice *dev, RHIPipeline pipe,
                                      const char *name) {
    (void)dev; (void)pipe; (void)name; return -1;
}

/* ---- shadow map / cubemap / FBO ---- */
RHIShadowMap rhi_shadow_map_create(RHIDevice *dev, u32 width, u32 height) {
    RHIShadowMap out;
    (void)dev; (void)width; (void)height;
    memset(&out, 0, sizeof(out));
    return out;
}
void rhi_shadow_map_destroy(RHIDevice *dev, RHIShadowMap *sm) {
    (void)dev; (void)sm;
}
void rhi_cmd_bind_shadow_map(RHICmdBuffer *cmd, RHIShadowMap *sm) {
    (void)cmd; (void)sm;
}
void rhi_cmd_unbind_shadow_map(RHICmdBuffer *cmd, u32 screen_w, u32 screen_h) {
    (void)cmd; (void)screen_w; (void)screen_h;
}
void rhi_cmd_clear_depth(RHICmdBuffer *cmd) { (void)cmd; }
RHICubemap rhi_cubemap_create(RHIDevice *dev, const RHICubemapDesc *desc) {
    (void)dev; (void)desc; return RHI_HANDLE_NULL;
}
void rhi_cubemap_destroy(RHIDevice *dev, RHICubemap cm) {
    (void)dev; (void)cm;
}
void rhi_cubemap_transition_to_read(RHIDevice *dev, RHICubemap cm) {
    (void)dev; (void)cm;
}
void rhi_texture_transition_to_read(RHIDevice *dev, RHITexture tex) {
    (void)dev; (void)tex;
}
void rhi_cmd_bind_cubemap(RHICmdBuffer *cmd, RHICubemap cm,
                          RHISampler sampler, u32 unit) {
    (void)cmd; (void)cm; (void)sampler; (void)unit;
}
void rhi_cmd_set_depth_func_less_or_equal(RHICmdBuffer *cmd) { (void)cmd; }
void rhi_cmd_set_depth_func_less(RHICmdBuffer *cmd) { (void)cmd; }
void rhi_cmd_set_depth_mask(RHICmdBuffer *cmd, bool enabled) {
    (void)cmd; (void)enabled;
}
void rhi_cmd_set_cull_face(RHICmdBuffer *cmd, bool enabled) {
    (void)cmd; (void)enabled;
}

/* ---- buffers / texel ---- */
void rhi_cmd_bind_texel_buffers(RHICmdBuffer *cmd, RHIBuffer buf0,
                                RHIBuffer buf1) {
    (void)cmd; (void)buf0; (void)buf1;
}
void rhi_buffer_update(RHIDevice *dev, RHIBuffer buf, const void *data,
                       usize size) {
    (void)dev; (void)buf; (void)data; (void)size;
}
void rhi_buffer_update_region(RHIDevice *dev, RHIBuffer buf, usize offset,
                              const void *data, usize size) {
    (void)dev; (void)buf; (void)offset; (void)data; (void)size;
}
bool rhi_buffer_read(RHIDevice *dev, RHIBuffer buf, void *dst, usize offset,
                     usize size) {
    (void)dev; (void)buf; (void)dst; (void)offset; (void)size; return false;
}
void rhi_cmd_fill_buffer(RHICmdBuffer *cmd, RHIBuffer buf, usize offset,
                         usize size, u32 value) {
    (void)cmd; (void)buf; (void)offset; (void)size; (void)value;
}
void rhi_cmd_update_buffer(RHICmdBuffer *cmd, RHIBuffer buf, usize offset,
                           const void *data, usize size) {
    (void)cmd; (void)buf; (void)offset; (void)data; (void)size;
}
void *rhi_buffer_map(RHIDevice *dev, RHIBuffer buf) {
    (void)dev; (void)buf; return NULL;
}
void rhi_buffer_unmap(RHIDevice *dev, RHIBuffer buf) { (void)dev; (void)buf; }
void rhi_cmd_copy_buffer(RHICmdBuffer *cmd, RHIBuffer src, RHIBuffer dst,
                         usize size) {
    (void)cmd; (void)src; (void)dst; (void)size;
}

/* ---- material texture binders ---- */
void rhi_cmd_bind_material_textures(RHICmdBuffer *cmd, RHITexture albedo,
    RHITexture mr, RHITexture normal, RHITexture emissive, RHITexture shadow,
    RHITexture ssao, RHISampler sampler) {
    (void)cmd; (void)albedo; (void)mr; (void)normal; (void)emissive;
    (void)shadow; (void)ssao; (void)sampler;
}
void rhi_cmd_bind_material_textures_ibl(RHICmdBuffer *cmd, RHITexture albedo,
    RHITexture mr, RHITexture normal, RHITexture emissive,
    RHITexture occlusion, RHITexture shadow, RHITexture ssao,
    RHISampler sampler, RHITexture brdf_lut, RHICubemap irradiance_map,
    RHICubemap prefilter_map, const RHITexture *point_shadow_cubes,
    u32 point_shadow_count) {
    (void)cmd; (void)albedo; (void)mr; (void)normal; (void)emissive;
    (void)occlusion; (void)shadow; (void)ssao; (void)sampler; (void)brdf_lut;
    (void)irradiance_map; (void)prefilter_map; (void)point_shadow_cubes;
    (void)point_shadow_count;
}
void rhi_cmd_bind_deferred_gbuf_textures(RHICmdBuffer *cmd,
    RHITexture albedo_metallic, RHITexture roughness_ao, RHITexture normal,
    RHITexture depth, RHITexture emissive, RHITexture shadow, RHITexture ssao,
    RHISampler sampler, RHITexture brdf_lut, RHICubemap irradiance_map,
    RHICubemap prefilter_map, const RHITexture *point_shadow_cubes,
    u32 point_shadow_count, RHISampler cube_sampler) {
    (void)cmd; (void)albedo_metallic; (void)roughness_ao; (void)normal;
    (void)depth; (void)emissive; (void)shadow; (void)ssao; (void)sampler;
    (void)brdf_lut; (void)irradiance_map; (void)prefilter_map;
    (void)point_shadow_cubes;
    (void)point_shadow_count; (void)cube_sampler;
}
void rhi_cmd_bind_textures_multi(RHICmdBuffer *cmd, RHITexture *textures,
                                 int count, RHISampler sampler) {
    (void)cmd; (void)textures; (void)count; (void)sampler;
}

/* ---- offscreen / MRT / depth-cube FBO ---- */
RHIOffscreenFBO rhi_offscreen_fbo_create(RHIDevice *dev, u32 width,
                                         u32 height) {
    RHIOffscreenFBO out;
    (void)dev; (void)width; (void)height;
    memset(&out, 0, sizeof(out));
    return out;
}
RHIOffscreenFBO rhi_offscreen_fbo_create_fmt(RHIDevice *dev, u32 width,
                                             u32 height, RHIFormat color_fmt) {
    RHIOffscreenFBO out;
    (void)dev; (void)width; (void)height; (void)color_fmt;
    memset(&out, 0, sizeof(out));
    return out;
}
RHIOffscreenFBO rhi_offscreen_fbo_create_desc(RHIDevice *dev,
                                              const RHIOffscreenFBODesc *desc) {
    RHIOffscreenFBO out;
    (void)dev; (void)desc;
    memset(&out, 0, sizeof(out));
    return out;
}
void rhi_offscreen_fbo_destroy(RHIDevice *dev, RHIOffscreenFBO *fbo) {
    (void)dev; (void)fbo;
}
void rhi_offscreen_fbo_bind(RHICmdBuffer *cmd, RHIOffscreenFBO *fbo) {
    (void)cmd; (void)fbo;
}
void rhi_offscreen_fbo_bind_load(RHICmdBuffer *cmd, RHIOffscreenFBO *fbo) {
    (void)cmd; (void)fbo;
}
void rhi_offscreen_fbo_unbind(RHICmdBuffer *cmd, u32 screen_w, u32 screen_h) {
    (void)cmd; (void)screen_w; (void)screen_h;
}
void rhi_offscreen_fbo_set_clear_color(RHIDevice *dev, RHIOffscreenFBO *fbo,
                                       f32 r, f32 g, f32 b, f32 a) {
    (void)dev; (void)fbo; (void)r; (void)g; (void)b; (void)a;
}
RHIMRTFBO rhi_mrt_fbo_create(RHIDevice *dev, u32 width, u32 height,
                             const RHIFormat *formats, u32 attachment_count) {
    RHIMRTFBO out;
    (void)dev; (void)width; (void)height; (void)formats;
    (void)attachment_count;
    memset(&out, 0, sizeof(out));
    return out;
}
void rhi_mrt_fbo_destroy(RHIDevice *dev, RHIMRTFBO *fbo) {
    (void)dev; (void)fbo;
}
void rhi_mrt_fbo_bind(RHICmdBuffer *cmd, RHIMRTFBO *fbo) {
    (void)cmd; (void)fbo;
}
void rhi_mrt_fbo_bind_load(RHICmdBuffer *cmd, RHIMRTFBO *fbo) {
    (void)cmd; (void)fbo;
}
void rhi_mrt_fbo_unbind(RHICmdBuffer *cmd, u32 screen_w, u32 screen_h) {
    (void)cmd; (void)screen_w; (void)screen_h;
}
RHICubemapDepthFBO rhi_cubemap_depth_fbo_create(RHIDevice *dev, u32 size) {
    RHICubemapDepthFBO out;
    (void)dev; (void)size;
    memset(&out, 0, sizeof(out));
    return out;
}
void rhi_cubemap_depth_fbo_destroy(RHIDevice *dev, RHICubemapDepthFBO *fbo) {
    (void)dev; (void)fbo;
}
void rhi_cubemap_depth_fbo_bind_face(RHICmdBuffer *cmd,
                                     RHICubemapDepthFBO *fbo, u32 face) {
    (void)cmd; (void)fbo; (void)face;
}
void rhi_cubemap_depth_fbo_unbind(RHICmdBuffer *cmd, u32 screen_w,
                                  u32 screen_h) {
    (void)cmd; (void)screen_w; (void)screen_h;
}

/* ---- compute ---- */
void rhi_cmd_dispatch(RHICmdBuffer *cmd, u32 x, u32 y, u32 z) {
    (void)cmd; (void)x; (void)y; (void)z;
}
void rhi_cmd_bind_storage_buffer(RHICmdBuffer *cmd, RHIBuffer buf,
                                 u32 binding) {
    (void)cmd; (void)buf; (void)binding;
}
void rhi_cmd_bind_acceleration_structure(RHICmdBuffer *cmd,
                                         RHIAccelerationStructure structure,
                                         u32 binding) {
    (void)cmd; (void)structure; (void)binding;
}
void rhi_cmd_memory_barrier(RHICmdBuffer *cmd) { (void)cmd; }
void rhi_cmd_bind_image_texture(RHICmdBuffer *cmd, RHITexture tex, u32 unit,
                                u32 mip_level, bool write_only) {
    (void)cmd; (void)tex; (void)unit; (void)mip_level; (void)write_only;
}
void rhi_cmd_bind_image_cubemap_face(RHICmdBuffer *cmd, RHICubemap cm,
                                     u32 face, u32 mip, u32 unit,
                                     bool write_only) {
    (void)cmd; (void)cm; (void)face; (void)mip; (void)unit; (void)write_only;
}
void rhi_cmd_bind_cubemap_sampler(RHICmdBuffer *cmd, RHICubemap cm,
                                  RHISampler sampler, u32 unit) {
    (void)cmd; (void)cm; (void)sampler; (void)unit;
}
void rhi_cmd_bind_texture_mip(RHICmdBuffer *cmd, RHITexture tex,
                              RHISampler sampler, u32 unit, u32 mip_level) {
    (void)cmd; (void)tex; (void)sampler; (void)unit; (void)mip_level;
}
void rhi_cmd_bind_texture_compute(RHICmdBuffer *cmd, RHITexture tex,
                                  RHISampler sampler, u32 unit) {
    (void)cmd; (void)tex; (void)sampler; (void)unit;
}
void rhi_cmd_transition_depth_to_read(RHICmdBuffer *cmd,
                                      RHITexture depth_tex) {
    (void)cmd; (void)depth_tex;
}

/* ---- screenshot ---- */
bool rhi_screenshot(RHIDevice *dev, u32 x, u32 y, u32 w, u32 h, u8 *pixels,
                    usize pixel_bytes) {
    (void)dev; (void)x; (void)y; (void)w; (void)h; (void)pixels;
    (void)pixel_bytes;
    return false;
}

/* ---- GPU timer ---- */
RHIGPUTimer *rhi_gpu_timer_create(RHIDevice *dev) { (void)dev; return NULL; }
void rhi_gpu_timer_destroy(RHIDevice *dev, RHIGPUTimer *t) {
    (void)dev; (void)t;
}
void rhi_gpu_timer_begin(RHIGPUTimer *t) { (void)t; }
void rhi_gpu_timer_end(RHIGPUTimer *t) { (void)t; }
f64 rhi_gpu_timer_elapsed_ms(RHIGPUTimer *t) { (void)t; return 0.0; }

#endif
