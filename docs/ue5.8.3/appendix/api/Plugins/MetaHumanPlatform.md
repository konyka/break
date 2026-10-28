# Plugins / MetaHumanPlatform

- module root: `Plugins/MetaHuman/MetaHumanAnimator/Source/MetaHumanPlatform`
- headers: 3; symbols: 13
- symbol kinds: class=2, delegate=1, macro=2, member=2, prototype=6
- PrivateDependencyModuleNames: D3D12RHI, DX12, MeshTrackerInterface, MetaHumanCore, MetalRHI, RHI, VulkanRHI
- PublicDependencyModuleNames: Core

### `Plugins/MetaHuman/MetaHumanAnimator/Source/MetaHumanPlatform/Private/MetaHumanPlatformLog.h` (Private)


#### Free symbols / members of external scopes

- L7 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogMetaHumanPlatform, Log, All);`
- L7 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogMetaHumanPlatform, Log, All);`

### `Plugins/MetaHuman/MetaHumanAnimator/Source/MetaHumanPlatform/Public/MetaHumanMinSpec.h` (Public)


#### class `FMetaHumanMinSpec`  
`class FMetaHumanMinSpec`  
_L11-23_
- L15 _public prototype_ `static bool IsSupported();`
- L16 _public prototype_ `static FText GetMinSpec();`
- L17 _public prototype_ `static void Reset();`
- L21 _private member_ `static bool bIsInitialized;`
- L22 _private member_ `static bool bIsSupported;`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API METAHUMANPLATFORM_API`

### `Plugins/MetaHuman/MetaHumanAnimator/Source/MetaHumanPlatform/Public/MetaHumanPhysicalDeviceProvider.h` (Public)


#### class `FMetaHumanPhysicalDeviceProvider`  
`class FMetaHumanPhysicalDeviceProvider`  
_L9-14_
- L12 _public prototype_ `static bool GetLUIDs(FString& OutUEPhysicalDeviceLUID, TArray<FString>& OutAllPhysicalDeviceLUIDs);`
- L13 _public prototype_ `static int32 GetVRAMInMB();`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API METAHUMANPLATFORM_API`
