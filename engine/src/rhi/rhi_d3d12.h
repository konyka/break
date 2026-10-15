#ifndef RHI_D3D12_NATIVE_H
#define RHI_D3D12_NATIVE_H

#if defined(_WIN32)

#define WIN32_LEAN_AND_MEAN
#define COBJMACROS
#include <windows.h>
#include <dxgi1_6.h>
#include <d3d12.h>

typedef enum RHI_D3D12CreateFailure {
    RHI_D3D12_FAIL_NONE = 0,
    RHI_D3D12_FAIL_ADAPTER,
    RHI_D3D12_FAIL_DEVICE,
    RHI_D3D12_FAIL_QUEUE,
    RHI_D3D12_FAIL_ALLOCATOR,
    RHI_D3D12_FAIL_COMMAND_LIST,
    RHI_D3D12_FAIL_DESCRIPTOR,
    RHI_D3D12_FAIL_FENCE,
    RHI_D3D12_FAIL_EVENT,
} RHI_D3D12CreateFailure;

typedef struct RHI_D3D12Context {
    IDXGIFactory6 *factory;
    IDXGIAdapter1 *adapter;
    ID3D12Device *device;
    ID3D12CommandQueue *direct_queue;   /* renamed from `queue` */
    ID3D12CommandQueue *compute_queue;
    ID3D12CommandQueue *copy_queue;
    ID3D12CommandAllocator *allocators[2];
    ID3D12GraphicsCommandList *command_lists[2];
    ID3D12DescriptorHeap *rtv_heap;
    ID3D12DescriptorHeap *dsv_heap;
    ID3D12DescriptorHeap *cbv_srv_uav_heap;
    ID3D12Fence *fence;
    HANDLE fence_event;
    UINT64 frame_fence[2];              /* last submitted fence per slot */
    UINT frame_parity;                  /* rhi_frame_index slot source */
    UINT acquire_in_flight;             /* spec §4.3: one in-flight pair max */
    UINT rtv_increment;
    UINT dsv_increment;
    UINT cbv_srv_uav_increment;
    UINT64 next_fence;
    UINT64 completed_fence;
    UINT64 descriptor_retire_fence;
    UINT descriptor_live;
    UINT device_lost;                   /* sticky latch */
    HRESULT removed_reason;
    UINT dred_enabled;
    RHI_D3D12CreateFailure injected_failure;
} RHI_D3D12Context;

typedef struct RHI_D3D12Resource {
    ID3D12Resource *resource;
    D3D12_RESOURCE_STATES state;
    UINT64 retire_fence;
} RHI_D3D12Resource;

HRESULT rhi_d3d12_context_create(RHI_D3D12Context *context,
                                 RHI_D3D12CreateFailure injected_failure);
void rhi_d3d12_context_destroy(RHI_D3D12Context *context);
HRESULT rhi_d3d12_context_retire(RHI_D3D12Context *context, UINT64 value);
HRESULT rhi_d3d12_descriptor_acquire(RHI_D3D12Context *context);
HRESULT rhi_d3d12_descriptor_retire(RHI_D3D12Context *context);
HRESULT rhi_d3d12_buffer_create(RHI_D3D12Context *context, UINT64 size,
                                RHI_D3D12Resource *out_resource);
void rhi_d3d12_resource_destroy(RHI_D3D12Resource *resource);
HRESULT rhi_d3d12_resource_transition(RHI_D3D12Context *context,
                                      ID3D12GraphicsCommandList *command_list,
                                      RHI_D3D12Resource *resource,
                                      D3D12_RESOURCE_STATES next_state);
HRESULT rhi_d3d12_submit(RHI_D3D12Context *context, UINT allocator_index,
                         UINT64 *out_fence);

#endif

#endif
