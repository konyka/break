#if defined(_WIN32)
#define WIN32_LEAN_AND_MEAN
#define COBJMACROS
#include <windows.h>
#include <dxgi1_6.h>
#include <d3d12.h>
#endif

#include <rhi/rhi_d3d12.h>

#if defined(_WIN32)

#include <stddef.h>
#include <stdint.h>

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
    rhi_d3d12_release((IUnknown **)&context->queue);
    rhi_d3d12_release((IUnknown **)&context->device);
    rhi_d3d12_release((IUnknown **)&context->adapter);
    context->rtv_increment = 0u;
    context->dsv_increment = 0u;
    context->cbv_srv_uav_increment = 0u;
    context->next_fence = 0u;
    context->completed_fence = 0u;
    context->descriptor_retire_fence = 0u;
    context->descriptor_live = 0u;
}

static HRESULT rhi_d3d12_select_adapter(RHI_D3D12Context *context) {
    IDXGIFactory6 *factory = NULL;
    IDXGIAdapter1 *candidate = NULL;
    DXGI_ADAPTER_DESC1 description;
    HRESULT hr;
    UINT index = 0u;

    hr = CreateDXGIFactory1(&IID_IDXGIFactory6, (void **)&factory);
    if (FAILED(hr)) return hr;
    for (;;) {
        hr = IDXGIFactory6_EnumAdapterByGpuPreference(
            factory, index++, DXGI_GPU_PREFERENCE_HIGH_PERFORMANCE,
            &IID_IDXGIAdapter1, (void **)&candidate);
        if (hr == DXGI_ERROR_NOT_FOUND) break;
        if (FAILED(hr)) break;
        hr = IDXGIAdapter1_GetDesc1(candidate, &description);
        if (SUCCEEDED(hr) && (description.Flags & DXGI_ADAPTER_FLAG_SOFTWARE) == 0u) {
            hr = D3D12CreateDevice((IUnknown *)candidate, D3D_FEATURE_LEVEL_11_0,
                                   &IID_ID3D12Device, NULL);
            if (SUCCEEDED(hr)) {
                context->adapter = candidate;
                candidate = NULL;
                break;
            }
        }
        rhi_d3d12_release((IUnknown **)&candidate);
    }
    rhi_d3d12_release((IUnknown **)&candidate);
    rhi_d3d12_release((IUnknown **)&factory);
    return context->adapter != NULL ? S_OK : (FAILED(hr) ? hr : DXGI_ERROR_NOT_FOUND);
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
    hr = D3D12CreateDevice((IUnknown *)context->adapter, D3D_FEATURE_LEVEL_11_0,
                           &IID_ID3D12Device, (void **)&context->device);
    if (FAILED(hr)) goto fail;
    ZeroMemory(&queue_desc, sizeof(queue_desc));
    queue_desc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;
    if (rhi_d3d12_should_fail(context, RHI_D3D12_FAIL_QUEUE)) {
        hr = E_FAIL;
        goto fail;
    }
    hr = ID3D12Device_CreateCommandQueue(context->device, &queue_desc,
                                         &IID_ID3D12CommandQueue,
                                         (void **)&context->queue);
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
    heap_desc.NumDescriptors = 2u;
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
    return ID3D12CommandQueue_Signal(context->queue, context->fence,
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
    if (context == NULL || context->queue == NULL || context->fence == NULL ||
        out_fence == NULL || allocator_index >= 2u) return E_INVALIDARG;
    hr = ID3D12GraphicsCommandList_Close(context->command_lists[allocator_index]);
    if (FAILED(hr)) return hr;
    lists[0] = (ID3D12CommandList *)context->command_lists[allocator_index];
    ID3D12CommandQueue_ExecuteCommandLists(context->queue, 1u, lists);
    value = context->next_fence++;
    hr = ID3D12CommandQueue_Signal(context->queue, context->fence, value);
    if (FAILED(hr)) return hr;
    *out_fence = value;
    return S_OK;
}

#endif
