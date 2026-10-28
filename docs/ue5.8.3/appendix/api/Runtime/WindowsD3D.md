# Runtime / WindowsD3D

- module root: `Source/Runtime/Windows/WindowsD3D`
- headers: 4; symbols: 20
- symbol kinds: class=1, macro=3, member=4, prototype=11, struct=1
- PublicDependencyModuleNames: Core

### `Source/Runtime/Windows/WindowsD3D/Internal/Windows/D3DIntelExtensions.h` (Internal)


#### Free symbols / members of external scopes

- L6 _macro_ `#define INTEL_EXTENSIONS 0`
- L11 _macro_ `#define INTC_IGDEXT_D3D12 1`
- L18 _prototype_ `INTCExtensionAppInfo1 GetIntelApplicationInfo();`
- L19 _prototype_ `void EnableIntelAppDiscovery(uint32 DeviceId);`

### `Source/Runtime/Windows/WindowsD3D/Internal/Windows/WindowsD3D.h` (Internal)


#### struct `FWindowsGPUInfo`  
`struct FWindowsGPUInfo`  
_L12-18_
- L14 _public member_ `uint32 VendorId = 0;`
- L15 _public member_ `uint32 DeviceId = 0;`
- L16 _public member_ `uint64 DedicatedVideoMemory = 0;`
- L17 _public member_ `FString AdapterName;`

#### class `FWindowsD3D`  
`class FWindowsD3D`  
_L20-33_
- L23 _public prototype_ `static FWindowsGPUInfo GetExpectedGPUInfo();`
- L24 _public prototype_ `static FWindowsGPUInfo GetGPUInfoByDedicatedMemory();`
- L25 _public prototype_ `static uint64 ChooseD3D11Adapter(uint64 DesiredAdapterLuid);`
- L26 _public prototype_ `static uint64 ChooseD3D12Adapter(uint64 DesiredAdapterLuid);`
- L28 _public prototype_ `static ID3D11Device* FindCachedD3D11AdapterDevice(uint64 AdapterLuid, int32& FeatureLevel);`
- L29 _public prototype_ `static void CacheD3D11AdapterDevice(uint64 AdapterLuid, TRefCountPtr<ID3D11Device>&& Device, int32 FeatureLevel);`
- L30 _public prototype_ `static ID3D12Device* FindCachedD3D12AdapterDevice(uint64 AdapterLuid);`
- L31 _public prototype_ `static void CacheD3D12AdapterDevice(uint64 AdapterLuid, TRefCountPtr<ID3D12Device>&& Device);`
- L32 _public prototype_ `static void ReleaseCachedAdapterDevices();`

### `Source/Runtime/Windows/WindowsD3D/Public/Windows/D3D11ThirdParty.h` (Public)
_(no declarations extracted)_

### `Source/Runtime/Windows/WindowsD3D/Public/Windows/WindowsD3D12ThirdParty.h` (Public)


#### Free symbols / members of external scopes

- L10 _macro_ `#define INITGUID`
