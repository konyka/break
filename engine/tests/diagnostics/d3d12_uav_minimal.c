/* Minimal, self-contained D3D12 UAV probe.
 *
 * NOT part of the test suite. It is deliberately standalone: it includes no
 * engine header and links against nothing but d3d12/dxgi/dxguid, so its result
 * is attributable to the platform rather than to anything in this repository.
 * It is kept as a diagnostic, not wired into CMake; test_d3d12_uav_matrix
 * covers the same view shapes through the engine.
 *
 * Build (clang, from this directory):
 *   clang -x c -std=c11 -O1 -Wno-nonportable-include-path -DCOBJMACROS \
 *         -D_WIN32_WINNT=0x0601 d3d12_uav_minimal.c -o d3d12_uav_minimal.exe \
 *         -ld3d12 -ldxgi -ldxguid \
 *         -I"<sdk>/um" -I"<sdk>/shared" -I"<sdk>/ucrt"
 * Run with no argument for the hardware adapter, or "w" for WARP.
 *
 * WHAT IT ESTABLISHED (2026-10-20, this host, RTX 4060 Laptop GPU and WARP):
 *   With a complete descriptor (as below) — RESULT: UAV view created, device
 *   HEALTHY on both adapters. Structured (UNKNOWN + stride 16) and typed
 *   (R32_FLOAT) buffer views are healthy too.
 *
 *   The 2026-10-19 version of this file left ViewDimension and NumElements
 *   zeroed and reported DEVICE LOST on both adapters. That was the probe's own
 *   bug: removal reason 0x887A0001 is DXGI_ERROR_INVALID_CALL, i.e. the runtime
 *   rejecting the descriptor, not a platform fault. Setting only one of the two
 *   fields still dies; both are required. pDesc = NULL also dies, because a
 *   buffer has no format for D3D12 to infer a view from.
 *
 * Mirrors only what rhi_d3d12.c does for a storage-buffer bind:
 *   - DXGI factory, pick the hardware adapter (or WARP with "w")
 *   - D3D12CreateDevice at FL11_0
 *   - a shader-visible CBV_SRV_UAV descriptor heap
 *   - CreateCommittedResource, DEFAULT heap, 256 bytes, ALLOW_UNORDERED_ACCESS
 *   - CreateUnorderedAccessView into that heap
 *   - then ask the device to do one more unrelated allocation
 *
 * Note CreateUnorderedAccessView returns void: a bad descriptor surfaces only
 * as the device being removed on the next call.
 */
#include <windows.h>
#include <dxgi1_6.h>
#include <d3d12.h>
#include <stdio.h>

static ID3D12Device *g_dev;

static const char *hr_name(HRESULT hr) {
    if (hr == DXGI_ERROR_DEVICE_REMOVED) return "DXGI_ERROR_DEVICE_REMOVED";
    if (hr == DXGI_ERROR_DEVICE_HUNG)   return "DXGI_ERROR_DEVICE_HUNG";
    if (hr == DXGI_ERROR_DEVICE_RESET)  return "DXGI_ERROR_DEVICE_RESET";
    if (hr == E_INVALIDARG)             return "E_INVALIDARG";
    if (hr == E_FAIL)                   return "E_FAIL";
    if (SUCCEEDED(hr))                  return "S_OK";
    return "other";
}

static int make_device(int use_warp) {
    IDXGIFactory6 *factory = NULL;
    IDXGIAdapter1 *chosen = NULL;
    IDXGIAdapter *warp = NULL;
    HRESULT hr = CreateDXGIFactory2(0, &IID_IDXGIFactory6, (void **)&factory);
    if (FAILED(hr)) { printf("  factory failed 0x%08lx\n", (unsigned long)hr); return -1; }
    if (use_warp) {
        hr = IDXGIFactory4_EnumWarpAdapter(factory, &IID_IDXGIAdapter, (void **)&warp);
        factory->lpVtbl->Release(factory);
        if (FAILED(hr)) { printf("  EnumWarpAdapter failed 0x%08lx\n",
                                 (unsigned long)hr); return -1; }
        hr = D3D12CreateDevice((IUnknown *)warp, D3D_FEATURE_LEVEL_11_0,
                               &IID_ID3D12Device, (void **)&g_dev);
        IDXGIAdapter_Release(warp);
        if (FAILED(hr)) { printf("  CreateDevice(WARP) failed 0x%08lx\n",
                                 (unsigned long)hr); return -1; }
        printf("  adapter: WARP\n");
        return 0;
    }
    for (;;) {
        IDXGIAdapter1 *cand = NULL;
        hr = IDXGIFactory6_EnumAdapterByGpuPreference(factory, 0,
                DXGI_GPU_PREFERENCE_HIGH_PERFORMANCE, &IID_IDXGIAdapter1,
                (void **)&cand);
        if (hr == DXGI_ERROR_NOT_FOUND || !cand) break;
        if (!chosen) chosen = cand; else IDXGIAdapter1_Release(cand);
        break;
    }
    factory->lpVtbl->Release(factory);
    if (!chosen) { printf("  no hardware adapter\n"); return -1; }
    {
        DXGI_ADAPTER_DESC1 d;
        if (SUCCEEDED(IDXGIAdapter1_GetDesc1(chosen, &d)))
            printf("  adapter: %ls\n", d.Description);
    }
    hr = D3D12CreateDevice((IUnknown *)chosen, D3D_FEATURE_LEVEL_11_0,
                           &IID_ID3D12Device, (void **)&g_dev);
    IDXGIAdapter1_Release(chosen);
    if (FAILED(hr)) { printf("  CreateDevice failed 0x%08lx\n", (unsigned long)hr); return -1; }
    return 0;
}

int main(int argc, char **argv) {
    int use_warp = (argc > 1 && argv[1][0] == 'w');
    ID3D12DescriptorHeap *heap = NULL;
    D3D12_HEAP_PROPERTIES hp;
    D3D12_RESOURCE_DESC rd;
    D3D12_CLEAR_VALUE cv;
    ID3D12Resource *buf = NULL;
    D3D12_UNORDERED_ACCESS_VIEW_DESC uav;
    D3D12_CPU_DESCRIPTOR_HANDLE cpu;
    ID3D12Resource *probe = NULL;
    D3D12_RESOURCE_DESC pd;
    HRESULT hr;

    printf("=== minimal D3D12 UAV probe (%s) ===\n", use_warp ? "WARP" : "hardware");
    if (make_device(use_warp) != 0) { printf("RESULT: device create FAILED\n"); return 1; }

    ZeroMemory(&hp, sizeof(hp));
    hp.Type = D3D12_HEAP_TYPE_DEFAULT;
    hp.CreationNodeMask = 1u; hp.VisibleNodeMask = 1u;
    ZeroMemory(&pd, sizeof(pd));
    pd.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
    pd.Width = 256u; pd.Height = 1u; pd.DepthOrArraySize = 1u;
    pd.MipLevels = 1u; pd.SampleDesc.Count = 1u;
    pd.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;
    hr = ID3D12Device_CreateCommittedResource(g_dev, &hp, D3D12_HEAP_FLAG_NONE,
        &pd, D3D12_RESOURCE_STATE_COPY_DEST, NULL, &IID_ID3D12Resource,
        (void **)&probe);
    printf("  unrelated resource create: %s\n", hr_name(hr));
    if (FAILED(hr)) { printf("RESULT: device already broken before UAV\n"); return 1; }
    ID3D12Resource_Release(probe);

    {
        D3D12_DESCRIPTOR_HEAP_DESC dh;
        ZeroMemory(&dh, sizeof(dh));
        dh.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
        dh.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;
        dh.NumDescriptors = 16;
        hr = ID3D12Device_CreateDescriptorHeap(g_dev, &dh,
            &IID_ID3D12DescriptorHeap, (void **)&heap);
    }
    if (FAILED(hr)) { printf("  descriptor heap failed %s\n", hr_name(hr)); return 1; }

    ZeroMemory(&rd, sizeof(rd));
    rd.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
    rd.Width = 256u; rd.Height = 1u; rd.DepthOrArraySize = 1u;
    rd.MipLevels = 1u; rd.SampleDesc.Count = 1u;
    rd.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;
    rd.Flags = D3D12_RESOURCE_FLAG_ALLOW_UNORDERED_ACCESS;
    (void)cv;
    hr = ID3D12Device_CreateCommittedResource(g_dev, &hp, D3D12_HEAP_FLAG_NONE, &rd,
        D3D12_RESOURCE_STATE_UNORDERED_ACCESS, NULL, &IID_ID3D12Resource,
        (void **)&buf);
    printf("  UAV buffer create:        %s\n", hr_name(hr));
    if (FAILED(hr)) { printf("RESULT: UAV buffer creation itself failed\n"); return 1; }

    ID3D12DescriptorHeap_GetCPUDescriptorHandleForHeapStart(heap, &cpu);
    ZeroMemory(&uav, sizeof(uav));
    uav.Format = DXGI_FORMAT_R32_TYPELESS;
    uav.ViewDimension = D3D12_UAV_DIMENSION_BUFFER;
    uav.Buffer.NumElements = 256u / 4u;
    uav.Buffer.Flags = D3D12_BUFFER_UAV_FLAG_RAW;
    /* Returns void: an illegal descriptor is reported by removing the device
     * with DXGI_ERROR_INVALID_CALL instead. Leaving ViewDimension zeroed
     * (D3D12_UAV_DIMENSION_UNKNOWN) or NumElements at 0 does exactly that. */
    ID3D12Device_CreateUnorderedAccessView(g_dev, buf, NULL, &uav, cpu);
    printf("  CreateUnorderedAccessView: returned (void)\n");

    ZeroMemory(&pd, sizeof(pd));
    pd.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
    pd.Width = 256u; pd.Height = 1u; pd.DepthOrArraySize = 1u;
    pd.MipLevels = 1u; pd.SampleDesc.Count = 1u;
    pd.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;
    hr = ID3D12Device_CreateCommittedResource(g_dev, &hp, D3D12_HEAP_FLAG_NONE, &pd,
        D3D12_RESOURCE_STATE_COPY_DEST, NULL, &IID_ID3D12Resource, (void **)&probe);
    printf("  post-view allocation:     %s\n", hr_name(hr));
    printf("  GetDeviceRemovedReason:   0x%08lx\n",
           (unsigned long)ID3D12Device_GetDeviceRemovedReason(g_dev));
    if (FAILED(hr))
        printf("RESULT: DEVICE LOST by CreateUnorderedAccessView\n");
    else
        printf("RESULT: UAV view created, device HEALTHY\n");
    if (probe) ID3D12Resource_Release(probe);
    if (buf) ID3D12Resource_Release(buf);
    if (heap) ID3D12DescriptorHeap_Release(heap);
    if (g_dev) ID3D12Device_Release(g_dev);
    return FAILED(hr) ? 1 : 0;
}
