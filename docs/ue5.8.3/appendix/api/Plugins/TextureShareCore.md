# Plugins / TextureShareCore

- module root: `Plugins/VirtualProduction/TextureShare/Source/TextureShareCore`
- headers: 61; symbols: 1148
- symbol kinds: class=28, delegate=20, enum=18, enumerator=101, function=289, macro=6, member=235, namespace=7, prototype=381, struct=53, typedef=6, variable=4
- PrivateDependencyModuleNames: VulkanRHI
- PrivateIncludePathModuleNames: VulkanRHI
- PublicDependencyModuleNames: Core

### `Plugins/VirtualProduction/TextureShare/Source/TextureShareCore/Private/Containers/TextureShareCoreContainers.h` (Private)


#### struct `FTextureShareCoreObjectData`  
`struct FTextureShareCoreObjectData : public ITextureShareSerialize`  
_L12-28_
- inherits: `ITextureShareSerialize`
- desc: TextureShareCore object data container The structure is serializable (binary compatible) and reflected on the SDK side (UE types will be replaced with simplified copies from the SDK).
- L16 _public member_ `FTextureShareCoreObjectDesc Desc;` — Object information
- L19 _public member_ `FTextureShareCoreData Data;` — Setup frame data on game thread before rendering call
- L22 _public prototype_ `virtual ~FTextureShareCoreObjectData() = default;`
- L24 _public function_ `virtual ITextureShareSerializeStream& Serialize(ITextureShareSerializeStream& Stream) override`

#### struct `FTextureShareCoreObjectProxyData`  
`struct FTextureShareCoreObjectProxyData : public ITextureShareSerialize`  
_L34-50_
- inherits: `ITextureShareSerialize`
- desc: TextureShareCore object proxy data container The structure is serializable (binary compatible) and reflected on the SDK side (UE types will be replaced with simplified copies from the SDK).
- L38 _public member_ `FTextureShareCoreObjectDesc Desc;` — Object ID
- L41 _public member_ `FTextureShareCoreProxyData ProxyData;` — Setup frame data on game thread before rendering call
- L44 _public prototype_ `virtual ~FTextureShareCoreObjectProxyData() = default;`
- L46 _public function_ `virtual ITextureShareSerializeStream& Serialize(ITextureShareSerializeStream & Stream) override`

### `Plugins/VirtualProduction/TextureShare/Source/TextureShareCore/Private/Containers/TextureShareCoreContainers_CustomData.h` (Private)


#### struct `FTextureShareCoreCustomData`  
`struct FTextureShareCoreCustomData : public ITextureShareSerialize`  
_L10-57_
- inherits: `ITextureShareSerialize`
- desc: Custom data pair: Key + Value The structure is serializable (binary compatible) and reflected on the SDK side (UE types will be replaced with simplified copies from the SDK).
- L14 _public member_ `FString Key;` — Custom data key
- L17 _public member_ `FString Value;` — Custom data value
- L20 _public prototype_ `virtual ~FTextureShareCoreCustomData() = default;`
- L22 _public function_ `virtual ITextureShareSerializeStream& Serialize(ITextureShareSerializeStream & Stream) override`
- L28 _public prototype_ `FTextureShareCoreCustomData() = default;`
- L30 _public function_ `FTextureShareCoreCustomData(const wchar_t* InKey, const wchar_t* InValue) : Key(InKey), Value(InValue)`
- L34 _public function_ `FTextureShareCoreCustomData(const FString& InKey, const FString& InValue) : Key(InKey), Value(InValue)`
- L38 _public function_ `bool EqualsFunc(const wchar_t* InKey) const`
- L43 _public function_ `bool EqualsFunc(const FString& InKey) const`
- L48 _public function_ `bool EqualsFunc(const FTextureShareCoreCustomData& InParameter) const`
- L53 _public function_ `bool operator==(const FTextureShareCoreCustomData& InParameter) const`

### `Plugins/VirtualProduction/TextureShare/Source/TextureShareCore/Private/Containers/TextureShareCoreContainers_Data.h` (Private)


#### struct `FTextureShareCoreData`  
`struct FTextureShareCoreData : public ITextureShareSerialize`  
_L14-52_
- inherits: `ITextureShareSerialize`
- desc: Game data of the TextureShareCore object The structure is serializable (binary compatible) and reflected on the SDK side (UE types will be replaced with simplified copies from the SDK).
- L18 _public member_ `FTextureShareCoreFrameMarker FrameMarker;` — Current frame marker
- L21 _public member_ `TArraySerializable<FTextureShareCoreViewDesc> SupportedViews;` — Supported views of this object
- L24 _public member_ `TArraySerializable<FTextureShareCoreResourceRequest> ResourceRequests;` — Resource requests from this object to remote processes
- L27 _public member_ `TArraySerializable<FTextureShareCoreManualProjection> ManualProjections;` — Manual projection requests from this object to remote processes
- L30 _public member_ `TArraySerializable<FTextureShareCoreManualProjectionSource> ManualProjectionsSources;` — Sources of used manual projections in local process
- L33 _public member_ `TArraySerializable<FTextureShareCoreCustomData> CustomData;` — Custom abstract data of this object
- L36 _public prototype_ `virtual ~FTextureShareCoreData() = default;`
- L38 _public function_ `virtual ITextureShareSerializeStream& Serialize(ITextureShareSerializeStream & Stream) override`
- L44 _public function_ `void ResetData()`

### `Plugins/VirtualProduction/TextureShare/Source/TextureShareCore/Private/Containers/TextureShareCoreContainers_DeviceD3D11.h` (Private)
_(no declarations extracted)_

### `Plugins/VirtualProduction/TextureShare/Source/TextureShareCore/Private/Containers/TextureShareCoreContainers_DeviceD3D12.h` (Private)
_(no declarations extracted)_

### `Plugins/VirtualProduction/TextureShare/Source/TextureShareCore/Private/Containers/TextureShareCoreContainers_DeviceVulkan.h` (Private)


#### struct `FTextureShareDeviceVulkanContext`  
`struct FTextureShareDeviceVulkanContext : public ITextureShareSerialize`  
_L16-59_
- inherits: `ITextureShareSerialize`
- desc: Vulkan device context The structure is serializable (binary compatible) and reflected on the SDK side (UE types will be replaced with simplified copies from the SDK).
- L19 _public prototype_ `FTextureShareDeviceVulkanContext() = default;`
- L20 _public function_ `FTextureShareDeviceVulkanContext(VkInstance InInstance, VkPhysicalDevice InPhysicalDevice, VkDevice InDevice)`
- L27 _public function_ `bool IsValid() const`
- L32 _public function_ `VkInstance GetInstance() const`
- L37 _public function_ `VkPhysicalDevice GetPhysicalDevice() const`
- L42 _public function_ `VkDevice GetDevice() const`
- L48 _public prototype_ `virtual ~FTextureShareDeviceVulkanContext() = default;`
- L50 _public function_ `virtual ITextureShareSerializeStream& Serialize(ITextureShareSerializeStream & Stream) override`
- L56 _private member_ `Windows::HANDLE Instance = nullptr;`
- L57 _private member_ `Windows::HANDLE PhysicalDevice = nullptr;`
- L58 _private member_ `Windows::HANDLE Device = nullptr;`

#### struct `FTextureShareDeviceVulkanResource`  
`struct FTextureShareDeviceVulkanResource : public ITextureShareSerialize`  
_L65-113_
- inherits: `ITextureShareSerialize`
- desc: Vulkan resource context The structure is serializable (binary compatible) and reflected on the SDK side (UE types will be replaced with simplified copies from the SDK).
- L68 _public prototype_ `FTextureShareDeviceVulkanResource() = default;`
- L70 _public function_ `FTextureShareDeviceVulkanResource(VkDeviceMemory InAllocationHandle, const uint64 InAllocationOffset = 0)`
- L76 _public function_ `void operator==(const FTextureShareDeviceVulkanResource& In)`
- L82 _public function_ `bool IsValid() const`
- L87 _public function_ `void* GetNativeResourcePtr() const`
- L92 _public function_ `VkDeviceMemory GetAllocationHandle() const`
- L97 _public function_ `uint64 GetAllocationOffset() const`
- L103 _public prototype_ `virtual ~FTextureShareDeviceVulkanResource() = default;`
- L105 _public function_ `virtual ITextureShareSerializeStream& Serialize(ITextureShareSerializeStream & Stream) override`
- L111 _private member_ `Windows::HANDLE AllocationHandle = nullptr;`
- L112 _private member_ `uint64 AllocationOffset = 0;`

#### Free symbols / members of external scopes

- L6 _typedef_ `typedef struct VkInstance_T* VkInstance;`
- L7 _typedef_ `typedef struct VkPhysicalDevice_T* VkPhysicalDevice;`
- L8 _typedef_ `typedef struct VkDevice_T* VkDevice;`
- L9 _typedef_ `typedef struct VkDeviceMemory_T* VkDeviceMemory;`
- L10 _typedef_ `typedef struct VkImage_T* VkImage;`

### `Plugins/VirtualProduction/TextureShare/Source/TextureShareCore/Private/Containers/TextureShareCoreContainers_FrameMarker.h` (Private)


#### struct `FTextureShareCoreFrameMarker`  
`struct FTextureShareCoreFrameMarker : public ITextureShareSerialize`  
_L10-31_
- inherits: `ITextureShareSerialize`
- desc: Frame marker. Sync purpose The structure is serializable (binary compatible) and reflected on the SDK side (UE types will be replaced with simplified copies from the SDK).
- L13 _public member_ `uint32 CustomFrameIndex1 = 0;`
- L14 _public member_ `uint64 CustomFrameIndex2 = 0;`
- L17 _public prototype_ `virtual ~FTextureShareCoreFrameMarker() = default;`
- L19 _public function_ `virtual ITextureShareSerializeStream& Serialize(ITextureShareSerializeStream & Stream) override`
- L25 _public function_ `void NextFrame()`

#### struct `FTextureShareCoreObjectFrameMarker`  
`struct FTextureShareCoreObjectFrameMarker : public ITextureShareSerialize`  
_L37-75_
- inherits: `ITextureShareSerialize`
- desc: Frame marker paired with Object descriptor. Sync purpose The structure is serializable (binary compatible) and reflected on the SDK side (UE types will be replaced with simplified copies from the SDK).
- L41 _public member_ `FTextureShareCoreObjectDesc ObjectDesc;` — Projection data source process Object ID
- L44 _public member_ `FTextureShareCoreFrameMarker FrameMarker;` — Projection data source process frame marker
- L47 _public prototype_ `virtual ~FTextureShareCoreObjectFrameMarker() = default;`
- L49 _public function_ `virtual ITextureShareSerializeStream& Serialize(ITextureShareSerializeStream & Stream) override`
- L55 _public prototype_ `FTextureShareCoreObjectFrameMarker() = default;`
- L57 _public function_ `FTextureShareCoreObjectFrameMarker(const FTextureShareCoreObjectDesc& InObjectDesc, const FTextureShareCoreFrameMarker& InFrameMarker) : ObjectDesc(InObjectDesc), FrameMarker(InFrameMarker)`
- L61 _public function_ `bool EqualsFunc(const FTextureShareCoreObjectDesc& InObjectDesc) const`
- L66 _public function_ `bool EqualsFunc(const FTextureShareCoreObjectFrameMarker& InObjectFrameMarker) const`
- L71 _public function_ `bool operator==(const FTextureShareCoreObjectFrameMarker& InObjectFrameMarker) const`

### `Plugins/VirtualProduction/TextureShare/Source/TextureShareCore/Private/Containers/TextureShareCoreContainers_ManualProjection.h` (Private)


#### struct `FTextureShareCoreManualProjection`  
`struct FTextureShareCoreManualProjection : public ITextureShareSerialize`  
_L12-66_
- inherits: `ITextureShareSerialize`
- desc: Manual projection settings for specified view The structure is serializable (binary compatible) and reflected on the SDK side (UE types will be replaced with simplified copies from the SDK).
- L16 _public member_ `FTextureShareCoreViewDesc ViewDesc;` — Apply manual projection for this view
- L18 _public member_ `ETextureShareCoreSceneViewManualProjectionType ProjectionType = ETextureShareCoreSceneViewManualProjectionType::FrustumAngles;`
- L20 _public member_ `ETextureShareViewRotationDataType ViewRotationType = ETextureShareViewRotationDataType::Original;`
- L21 _public member_ `ETextureShareViewLocationDataType ViewLocationType = ETextureShareViewLocationDataType::Original;`
- L24 _public member_ `FMatrix ProjectionMatrix = FMatrix::Identity;` — Projection matrix
- L27 _public member_ `FRotator ViewRotation = FRotator::ZeroRotator;` — View rotation
- L30 _public member_ `FVector ViewLocation = FVector::ZeroVector;` — View location
- L39 _public member_ `} FrustumAngles;`
- L42 _public prototype_ `virtual ~FTextureShareCoreManualProjection() = default;`
- L44 _public function_ `virtual ITextureShareSerializeStream& Serialize(ITextureShareSerializeStream & Stream) override`
- L52 _public function_ `bool EqualsFunc(const FString& InViewId) const`
- L57 _public function_ `bool EqualsFunc(const FTextureShareCoreViewDesc& InViewDesc) const`
- L62 _public function_ `bool EqualsFunc(const FTextureShareCoreManualProjection& InManualProjection) const`

#### struct `FTextureShareCoreManualProjection::FFrustumAngles`  
`struct FFrustumAngles`  
_L33-39_
- desc: Frustum angles
- L35 _public member_ `float Left = -30.f;`
- L36 _public member_ `float Right = 30.f;`
- L37 _public member_ `float Top = 30.f;`
- L38 _public member_ `float Bottom = -30.f;`

#### struct `FTextureShareCoreManualProjectionSource`  
`struct FTextureShareCoreManualProjectionSource : public ITextureShareSerialize`  
_L73-111_
- inherits: `ITextureShareSerialize`
- desc: Manual projection source info When using a manual projection from a remote process, store the description of the remote object with a frame marker The structure is serializable (binary compatible) and reflected on the SDK side (UE types will be replaced with simplified copies from the SDK).
- L77 _public member_ `FTextureShareCoreViewDesc ViewDesc;` — View desc type of this resource (support stereo)
- L80 _public member_ `FTextureShareCoreObjectFrameMarker ObjectFrameMarker;` — remote process object and framemarker info
- L83 _public prototype_ `virtual ~FTextureShareCoreManualProjectionSource() = default;`
- L85 _public function_ `virtual ITextureShareSerializeStream& Serialize(ITextureShareSerializeStream & Stream) override`
- L91 _public prototype_ `FTextureShareCoreManualProjectionSource() = default;`
- L93 _public function_ `FTextureShareCoreManualProjectionSource(const FTextureShareCoreViewDesc& InViewDesc, const FTextureShareCoreObjectFrameMarker& InObjectFrameMarker) : ViewDesc(InViewDesc), ObjectFrameMarker(InObjectFrameMarker)`
- L97 _public function_ `bool EqualsFunc(const FTextureShareCoreViewDesc& InViewDesc) const`
- L102 _public function_ `bool EqualsFunc(const FTextureShareCoreManualProjectionSource& InManualProjectionSource) const`
- L107 _public function_ `bool operator==(const FTextureShareCoreManualProjectionSource& InManualProjectionSource) const`

### `Plugins/VirtualProduction/TextureShare/Source/TextureShareCore/Private/Containers/TextureShareCoreContainers_ObjectDesc.h` (Private)


#### struct `FTextureShareCoreObjectProcessDesc`  
`struct FTextureShareCoreObjectProcessDesc : public ITextureShareSerialize`  
_L11-33_
- inherits: `ITextureShareSerialize`
- desc: Process descriptor The structure is serializable (binary compatible) and reflected on the SDK side (UE types will be replaced with simplified copies from the SDK).
- L15 _public member_ `FString ProcessId;` — Process name (user-defined)
- L18 _public member_ `FGuid ProcessGuid;` — Unique process guid
- L21 _public member_ `ETextureShareProcessType ProcessType = ETextureShareProcessType::Undefined;` — The local process type
- L24 _public member_ `ETextureShareDeviceType DeviceType = ETextureShareDeviceType::Undefined;` — Local process device type
- L27 _public prototype_ `virtual ~FTextureShareCoreObjectProcessDesc() = default;`
- L29 _public function_ `virtual ITextureShareSerializeStream& Serialize(ITextureShareSerializeStream & Stream) override`

#### struct `FTextureShareCoreObjectSyncState`  
`struct FTextureShareCoreObjectSyncState : public ITextureShareSerialize`  
_L39-54_
- inherits: `ITextureShareSerialize`
- desc: Object sync logic state The structure is serializable (binary compatible) and reflected on the SDK side (UE types will be replaced with simplified copies from the SDK).
- L42 _public member_ `ETextureShareSyncStep Step = ETextureShareSyncStep::Undefined;`
- L43 _public member_ `ETextureShareSyncState State = ETextureShareSyncState::Undefined;`
- L45 _public member_ `ETextureShareSyncStep NextStep = ETextureShareSyncStep::Undefined;`
- L46 _public member_ `ETextureShareSyncStep PrevStep = ETextureShareSyncStep::Undefined;`
- L49 _public prototype_ `virtual ~FTextureShareCoreObjectSyncState() = default;`
- L50 _public function_ `virtual ITextureShareSerializeStream& Serialize(ITextureShareSerializeStream& Stream) override`

#### struct `FTextureShareCoreObjectSync`  
`struct FTextureShareCoreObjectSync : public ITextureShareSerialize`  
_L60-111_
- inherits: `ITextureShareSerialize`
- desc: Object sync info The structure is serializable (binary compatible) and reflected on the SDK side (UE types will be replaced with simplified copies from the SDK).
- L64 _public member_ `FTextureShareCoreObjectSyncState SyncState;` — Object sync logic state
- L68 _public member_ `uint64 SyncStepSettings = 0;` — Bit-storage for sync steps used by this process 64 bits. Max steps=64
- L71 _public member_ `uint64 LastAccessTime = 0;` — Last access time from this object
- L74 _public prototype_ `virtual ~FTextureShareCoreObjectSync() = default;`
- L75 _public function_ `virtual ITextureShareSerializeStream& Serialize(ITextureShareSerializeStream& Stream) override`
- L81 _public function_ `bool IsStepEnabled(const ETextureShareSyncStep InStep) const`
- L98 _public function_ `void SetSyncStepSettings(const FTextureShareCoreSyncSettings& InSyncSettings)`

#### struct `FTextureShareCoreObjectDesc`  
`struct FTextureShareCoreObjectDesc : public ITextureShareSerialize`  
_L117-157_
- inherits: `ITextureShareSerialize`
- desc: Object unique description The structure is serializable (binary compatible) and reflected on the SDK side (UE types will be replaced with simplified copies from the SDK).
- L121 _public member_ `FString ShareName;` — Texture share name (TS objects with the same ShareName are trying to connect)
- L124 _public member_ `FGuid ObjectGuid;` — Unique object guid. Generated unique for a local process
- L127 _public member_ `FTextureShareCoreObjectSync Sync;` — Object Sync info
- L130 _public member_ `FTextureShareCoreObjectProcessDesc ProcessDesc;` — Local process description
- L133 _public prototype_ `virtual ~FTextureShareCoreObjectDesc() = default;`
- L135 _public function_ `virtual ITextureShareSerializeStream& Serialize(ITextureShareSerializeStream & Stream) override`
- L141 _public prototype_ `FTextureShareCoreObjectDesc() = default;`
- L143 _public function_ `bool EqualsFunc(const FGuid& InObjectGuid) const`
- L148 _public function_ `bool EqualsFunc(const FTextureShareCoreObjectDesc& InObjectDesc) const`
- L153 _public function_ `bool operator==(const FTextureShareCoreObjectDesc& InObjectDesc) const`

### `Plugins/VirtualProduction/TextureShare/Source/TextureShareCore/Private/Containers/TextureShareCoreContainers_ProxyData.h` (Private)


#### struct `FTextureShareCoreProxyData`  
`struct FTextureShareCoreProxyData : public ITextureShareSerialize`  
_L12-48_
- inherits: `ITextureShareSerialize`
- desc: Proxy data of the TextureShareCore object The structure is serializable (binary compatible) and reflected on the SDK side (UE types will be replaced with simplified copies from the SDK).
- L18 _public member_ `FTextureShareCoreFrameMarker FrameMarker;` — Frame markers on local process (Copied from game thread value) Must be copied from the game thread object data immediately after BeginFrameSync_RenderThread. **Currently, only the UE process side makes changes to this property.**
- L23 _public member_ `TArraySerializable<FTextureShareCoreObjectFrameMarker> RemoteFrameMarkers;` — Frame markers of all connected objects from game thread Must be copied from the game thread object data immediately after BeginFrameSync_RenderThread. **Currently, only the UE process side makes changes to this property.**
- L27 _public member_ `TArraySerializable<FTextureShareCoreSceneViewData> SceneData;` — Scene data (viewports, matrices, etc) **Currently, only the UE process side makes changes to this property.**
- L31 _public member_ `TArraySerializable<FTextureShareCoreResourceHandle> ResourceHandles;` — Descriptors for shared resources. Change only from the owner of the resource. **Currently, only the UE process side makes changes to this property.**
- L34 _public prototype_ `virtual ~FTextureShareCoreProxyData() = default;`
- L36 _public function_ `virtual ITextureShareSerializeStream& Serialize(ITextureShareSerializeStream & Stream) override`
- L42 _public function_ `void ResetProxyData()`

### `Plugins/VirtualProduction/TextureShare/Source/TextureShareCore/Private/Containers/TextureShareCoreContainers_ResourceDesc.h` (Private)


#### struct `FTextureShareCoreResourceDesc`  
`struct FTextureShareCoreResourceDesc : public ITextureShareSerialize`  
_L10-86_
- inherits: `ITextureShareSerialize`
- desc: Resource descriptor The structure is serializable (binary compatible) and reflected on the SDK side (UE types will be replaced with simplified copies from the SDK).
- L14 _public member_ `FString ResourceName;` — Resource name
- L17 _public member_ `FTextureShareCoreViewDesc ViewDesc;` — Resource owner
- L20 _public member_ `ETextureShareTextureOp OperationType = ETextureShareTextureOp::Read;` — Texture operation type (read or write)
- L23 _public member_ `ETextureShareSyncStep SyncStep = ETextureShareSyncStep::Undefined;` — resource sync order for logic (default value '-1'unordered)
- L26 _public member_ `ETextureShareResourceType ResourceType = ETextureShareResourceType::Default;` — Resource type
- L29 _public prototype_ `virtual ~FTextureShareCoreResourceDesc() = default;`
- L31 _public function_ `virtual ITextureShareSerializeStream& Serialize(ITextureShareSerializeStream & Stream) override`
- L37 _public function_ `FTextureShareCoreResourceDesc(const FString& InResourceName, const FTextureShareCoreViewDesc& InViewDesc, const ETextureShareTextureOp InOperationType, const ETextureShareSyncStep InSyncStep, const ETextureShareResourceType& InResourceType) : ResourceName(InResourceName), ViewDesc(InViewDesc), OperationType(InOperationType), SyncStep(InSyncStep), ResourceType(InResourceType)`
- L41 _public function_ `FTextureShareCoreResourceDesc(const FString& InResourceName, const FTextureShareCoreViewDesc& InViewDesc, const ETextureShareTextureOp InOperationType, const ETextureShareSyncStep InSyncStep) : ResourceName(InResourceName), ViewDesc(InViewDesc), OperationType(InOperationType), SyncStep(InSyncStep)`
- L45 _public function_ `FTextureShareCoreResourceDesc(const FString& InResourceName, const FTextureShareCoreViewDesc& InViewDesc, const ETextureShareTextureOp InOperationType) : ResourceName(InResourceName), ViewDesc(InViewDesc), OperationType(InOperationType)`
- L49 _public function_ `FTextureShareCoreResourceDesc(const FString& InResourceName, const ETextureShareTextureOp InOperationType, const ETextureShareSyncStep InSyncStep) : ResourceName(InResourceName), OperationType(InOperationType), SyncStep(InSyncStep)`
- L53 _public function_ `FTextureShareCoreResourceDesc(const FString& InResourceName, const ETextureShareTextureOp InOperationType) : ResourceName(InResourceName), OperationType(InOperationType)`
- L57 _public function_ `FTextureShareCoreResourceDesc(const FString& InResourceName) : ResourceName(InResourceName)`
- L61 _public prototype_ `FTextureShareCoreResourceDesc() = default;`
- L64 _public function_ `bool EqualsFunc(const FTextureShareCoreViewDesc& InViewDesc) const`
- L69 _public function_ `bool EqualsFunc(const FTextureShareCoreResourceDesc& InResourceDesc) const`
- L79 _public function_ `bool operator==(const FTextureShareCoreResourceDesc& InResourceDesc) const`

### `Plugins/VirtualProduction/TextureShare/Source/TextureShareCore/Private/Containers/TextureShareCoreContainers_ResourceHandle.h` (Private)


#### struct `FTextureShareCoreResourceHandle`  
`struct FTextureShareCoreResourceHandle : public ITextureShareSerialize`  
_L10-58_
- inherits: `ITextureShareSerialize`
- desc: Resource handle data (Shared resource handlers and other data) The structure is serializable (binary compatible) and reflected on the SDK side (UE types will be replaced with simplified copies from the SDK).
- L14 _public member_ `FTextureShareCoreResourceDesc ResourceDesc;` — Resource info
- L17 _public member_ `Windows::HANDLE NTHandle = nullptr;` — GPU-GPU share purpose (this resource use NT handle)
- L20 _public member_ `Windows::HANDLE SharedHandle = nullptr;` — GPU-GPU share purpose (not NT handle)
- L23 _public member_ `FGuid SharedHandleGuid;` — Unique handle name
- L26 _public member_ `uint32 GPUIndex = 0;` — Resource Owner GPU Index
- L29 _public prototype_ `virtual ~FTextureShareCoreResourceHandle() = default;`
- L31 _public function_ `virtual ITextureShareSerializeStream& Serialize(ITextureShareSerializeStream & Stream) override`
- L37 _public function_ `bool HandleEquals(const FTextureShareCoreResourceHandle& In) const`
- L44 _public function_ `bool EqualsFunc(const FTextureShareCoreResourceDesc& InResourceDesc) const`
- L49 _public function_ `bool EqualsFunc(const FTextureShareCoreViewDesc& InViewDesc) const`
- L54 _public function_ `bool operator==(const FTextureShareCoreResourceHandle& In) const`

### `Plugins/VirtualProduction/TextureShare/Source/TextureShareCore/Private/Containers/TextureShareCoreContainers_ResourceRequest.h` (Private)


#### struct `FTextureShareCoreResourceRequest`  
`struct FTextureShareCoreResourceRequest : public ITextureShareSerialize`  
_L11-107_
- inherits: `ITextureShareSerialize`
- desc: Resource request data When no size and/or format is specified, values from another process or values from local resources are used. The structure is serializable (binary compatible) and reflected on the SDK side (UE types will be replaced with simplified copies from the SDK).
- L15 _public member_ `FTextureShareCoreResourceDesc ResourceDesc;` — Resource info
- L20 _public member_ `int32 GPUIndex = -1;` — MGPU support. When a texture is rendered on a GPU other than the destination, it must be transferred between GPUs. The transfer is performed on the UE side in the TextureShare module.
- L25 _public member_ `EPixelFormat PixelFormat = EPixelFormat::PF_Unknown;` — Required texture format The UE process only uses the "EPixelFormat" value. Otherwise, find the best of "EPixelFormat" associated with "DXGI_FORMAT".
- L26 _public member_ `DXGI_FORMAT Format = DXGI_FORMAT_UNKNOWN;`
- L29 _public member_ `FIntPoint Size = FIntPoint::ZeroValue;` — Required texture size (or zero if the original value is acceptable)
- L32 _public member_ `float Gamma = -1;` — Required texture gamma (or negative value if the original value is acceptable)
- L35 _public member_ `uint32 NumMips = 0;` — Experimental: nummips feature
- L38 _public prototype_ `virtual ~FTextureShareCoreResourceRequest() = default;`
- L40 _public function_ `virtual ITextureShareSerializeStream& Serialize(ITextureShareSerializeStream & Stream) override`
- L46 _public prototype_ `FTextureShareCoreResourceRequest() = default;`
- L48 _public function_ `FTextureShareCoreResourceRequest(const FTextureShareCoreResourceDesc& InResourceDesc, const float InGamma = -1.f) : ResourceDesc(InResourceDesc) , Gamma(InGamma)`
- L53 _public function_ `FTextureShareCoreResourceRequest(const FTextureShareCoreResourceDesc& InResourceDesc, const FIntPoint& InSize, const float InGamma = -1.f) : ResourceDesc(InResourceDesc) , Size(InSize) , Gamma(InGamma)`
- L59 _public function_ `FTextureShareCoreResourceRequest(const FTextureShareCoreResourceDesc& InResourceDesc, const DXGI_FORMAT InFormat, const float InGamma = -1.f) : ResourceDesc(InResourceDesc) , Format(InFormat) , Gamma(InGamma)`
- L65 _public function_ `FTextureShareCoreResourceRequest(const FTextureShareCoreResourceDesc& InResourceDesc, const FIntPoint& InSize, const DXGI_FORMAT InFormat, const float InGamma = -1.f) : ResourceDesc(InResourceDesc) , Format(InFormat) , Size(InSize) , Gamma(InGamma)`
- L72 _public function_ `FTextureShareCoreResourceRequest(const FTextureShareCoreResourceDesc& InResourceDesc, const EPixelFormat InPixelFormat, const float InGamma = -1.f) : ResourceDesc(InResourceDesc) , PixelFormat(InPixelFormat) , Gamma(InGamma)`
- L78 _public function_ `FTextureShareCoreResourceRequest(const FTextureShareCoreResourceDesc& InResourceDesc, const FIntPoint& InSize, const EPixelFormat InPixelFormat, const float InGamma = -1.f) : ResourceDesc(InResourceDesc) , PixelFormat(InPixelFormat) , Size(InSize) , Gamma(InGamma)`
- L88 _public function_ `void SetPixelFormat(uint32 InPixelFormat)`
- L93 _public function_ `bool EqualsFunc(const FTextureShareCoreResourceDesc& InResourceDesc) const`
- L98 _public function_ `bool EqualsFunc(const FTextureShareCoreViewDesc& InViewDesc) const`
- L103 _public function_ `bool operator==(const FTextureShareCoreResourceRequest& InResourceRequest) const`

### `Plugins/VirtualProduction/TextureShare/Source/TextureShareCore/Private/Containers/TextureShareCoreContainers_SceneData.h` (Private)


#### struct `FTextureShareCoreSceneViewMatrices`  
`struct FTextureShareCoreSceneViewMatrices : public ITextureShareSerialize`  
_L10-52_
- inherits: `ITextureShareSerialize`
- desc: Scene data: View matrices The structure is serializable (binary compatible) and reflected on the SDK side (UE types will be replaced with simplified copies from the SDK).
- L14 _public member_ `FMatrix ProjectionMatrix;` — ViewToClip : UE projection matrix projects such that clip space Z=1 is the near plane, and Z=0 is the infinite far plane.
- L17 _public member_ `FMatrix ProjectionNoAAMatrix;` — ViewToClipNoAA : UE projection matrix projects such that clip space Z=1 is the near plane, and Z=0 is the infinite far plane. Don't apply any AA jitter
- L20 _public member_ `FMatrix ViewMatrix;` — WorldToView..
- L23 _public member_ `FMatrix ViewProjectionMatrix;` — Scene data: View matrices The structure is serializable (binary compatible) and reflected on the SDK side (UE types will be replaced with simplified copies from the SDK). struct FTextureShareCoreSceneViewMatrices : public ITextureShareSerialize { ViewToClip : UE projection matrix projects such that clip space Z=1 is the near plane, and Z=0 is the infinite far plane. FMatrix ProjectionMatrix; ViewToClipNoAA : UE projection matrix projects such that clip space Z=1 is the near plane, and Z=0 is the infinite far plane. Don't apply any AA jitter FMatrix ProjectionNoAAMatrix; WorldToView.. FMatrix ViewMatrix; WorldToClip : UE projection matrix projects such that clip space Z=1 is the near plane, and Z=0 is the infinite far plane.
- L26 _public member_ `FMatrix TranslatedViewProjectionMatrix;` — The view-projection transform, starting from world-space points translated by -ViewOrigin.
- L29 _public member_ `FVector PreViewTranslation;` — The translation to apply to the world before TranslatedViewProjectionMatrix. Usually it is -ViewOrigin but with rereflections this can differ
- L32 _public member_ `FVector ViewOrigin;` — To support ortho and other modes this is redundant, in world space
- L35 _public member_ `FVector2D ProjectionScale;` — Scale applied by the projection matrix in X and Y.
- L38 _public member_ `FVector2D TemporalAAProjectionJitter;` — TemporalAA jitter offset currently stored in the projection matrix
- L41 _public member_ `float ScreenScale = 1.f;` — Scale factor to use when computing the size of a sphere in pixels.
- L44 _public prototype_ `virtual ~FTextureShareCoreSceneViewMatrices() = default;`
- L46 _public function_ `virtual ITextureShareSerializeStream& Serialize(ITextureShareSerializeStream & Stream) override`

#### struct `FTextureShareCoreSceneView`  
`struct FTextureShareCoreSceneView : public ITextureShareSerialize`  
_L58-96_
- inherits: `ITextureShareSerialize`
- desc: Scene data: View The structure is serializable (binary compatible) and reflected on the SDK side (UE types will be replaced with simplified copies from the SDK).
- L61 _public member_ `FTextureShareCoreSceneViewMatrices ViewMatrices;`
- L64 _public member_ `FIntRect UnscaledViewRect;` — Final position of the view in the final render target (in pixels), potentially constrained by an aspect ratio requirement (black bars)
- L67 _public member_ `FIntRect UnconstrainedViewRect;` — Raw view size (in pixels), used for screen space calculations
- L70 _public member_ `FVector ViewLocation;` — Variables used to determine the view matrix
- L71 _public member_ `FRotator ViewRotation;`
- L72 _public member_ `FQuat BaseHmdOrientation;`
- L73 _public member_ `FVector BaseHmdLocation;`
- L74 _public member_ `float WorldToMetersScale = 1.f;`
- L77 _public member_ `int32 StereoViewIndex;` — For stereoscopic rendering, unique index identifying the view across view families
- L80 _public member_ `int32 PrimaryViewIndex;` — For stereoscopic rendering, view family index of the primary view associated with this view
- L83 _public member_ `float FOV;` — Actual field of view and that desired by the camera originally
- L84 _public member_ `float DesiredFOV;`
- L87 _public prototype_ `virtual ~FTextureShareCoreSceneView() = default;`
- L89 _public function_ `virtual ITextureShareSerializeStream& Serialize(ITextureShareSerializeStream & Stream) override`

#### struct `FTextureShareCoreSceneGameTime`  
`struct FTextureShareCoreSceneGameTime : public ITextureShareSerialize`  
_L102-119_
- inherits: `ITextureShareSerialize`
- desc: Scene data: GameTime The structure is serializable (binary compatible) and reflected on the SDK side (UE types will be replaced with simplified copies from the SDK).
- L105 _public member_ `float RealTimeSeconds;`
- L106 _public member_ `float WorldTimeSeconds;`
- L108 _public member_ `float DeltaRealTimeSeconds;`
- L109 _public member_ `float DeltaWorldTimeSeconds;`
- L112 _public prototype_ `virtual ~FTextureShareCoreSceneGameTime() = default;`
- L114 _public function_ `virtual ITextureShareSerializeStream& Serialize(ITextureShareSerializeStream & Stream) override`

#### struct `FTextureShareCoreSceneViewFamily`  
`struct FTextureShareCoreSceneViewFamily : public ITextureShareSerialize`  
_L125-150_
- inherits: `ITextureShareSerialize`
- desc: Scene data: ViewFamily The structure is serializable (binary compatible) and reflected on the SDK side (UE types will be replaced with simplified copies from the SDK).
- L129 _public member_ `FTextureShareCoreSceneGameTime GameTime;` — The current time
- L132 _public member_ `uint32 FrameNumber = 0;` — Copy from main thread GFrameNumber to be accessible on render thread side. UINT_MAX before CreateSceneRenderer() or BeginRenderingViewFamily() was called
- L135 _public member_ `bool bIsHDR = false;` — When enabled, the post processing will output in HDR space
- L138 _public member_ `float GammaCorrection = 1.f;` — Gamma correction used when rendering this family. Default is 1.0
- L141 _public member_ `float SecondaryViewFraction = 1.f;` — Secondary view fraction to support High DPI monitor
- L144 _public prototype_ `virtual ~FTextureShareCoreSceneViewFamily() = default;`
- L146 _public function_ `virtual ITextureShareSerializeStream& Serialize(ITextureShareSerializeStream & Stream) override`

#### struct `FTextureShareCoreSceneViewData`  
`struct FTextureShareCoreSceneViewData : public ITextureShareSerialize`  
_L156-202_
- inherits: `ITextureShareSerialize`
- desc: Scene data The structure is serializable (binary compatible) and reflected on the SDK side (UE types will be replaced with simplified copies from the SDK).
- L160 _public member_ `FTextureShareCoreViewDesc ViewDesc;` — Eye type of this resource (support stereo)
- L163 _public member_ `FTextureShareCoreSceneView View;` — Scene view data
- L166 _public member_ `FTextureShareCoreSceneViewFamily ViewFamily;` — Scene ViewFamily data
- L169 _public prototype_ `virtual ~FTextureShareCoreSceneViewData() = default;`
- L171 _public function_ `virtual ITextureShareSerializeStream& Serialize(ITextureShareSerializeStream & Stream) override`
- L177 _public prototype_ `FTextureShareCoreSceneViewData() = default;`
- L179 _public function_ `FTextureShareCoreSceneViewData(const FString& InViewId, const ETextureShareEyeType InEyeType = ETextureShareEyeType::Default) : ViewDesc(InViewId, InEyeType)`
- L183 _public function_ `FTextureShareCoreSceneViewData(const FTextureShareCoreViewDesc& InViewDesc) : ViewDesc(InViewDesc)`
- L188 _public function_ `bool EqualsFunc(const FTextureShareCoreSceneViewData& InViewData) const`
- L193 _public function_ `bool EqualsFunc(const FTextureShareCoreViewDesc& InViewDesc) const`
- L198 _public function_ `bool operator==(const FTextureShareCoreSceneViewData& InSceneViewData) const`

### `Plugins/VirtualProduction/TextureShare/Source/TextureShareCore/Private/Containers/TextureShareCoreContainers_SyncSettings.h` (Private)


#### enum `ETextureShareCoreFrameConnectionsState`  
`enum class ETextureShareCoreFrameConnectionsState : uint8`  
_L9-14_
- desc: Connection state
- L11 _public enumerator_ `SkipFrame = 0`
- L12 _public enumerator_ `Wait`
- L13 _public enumerator_ `Accept`

#### struct `FTextureShareCoreFrameConnectionsSettings`  
`struct FTextureShareCoreFrameConnectionsSettings : public ITextureShareSerialize`  
_L20-66_
- inherits: `ITextureShareSerialize`
- desc: SyncSettings: Connection - Wait until the required number of processes are connected at new frame The structure is serializable (binary compatible) and reflected on the SDK side (UE types will be replaced with simplified copies from the SDK).
- L24 _public member_ `int32 MinValue = 0;` — Required number of processes. The TS frame will only start when this number is reached.
- L27 _public member_ `TArraySerializable<FString> AllowedProcessNames;` — Connect only to processes with names from this list
- L30 _public member_ `TArraySerializable<FString> BannedProcessNames;` — Ignore processes with names from this list
- L33 _public prototype_ `virtual ~FTextureShareCoreFrameConnectionsSettings() = default;`
- L35 _public function_ `virtual ITextureShareSerializeStream& Serialize(ITextureShareSerializeStream& Stream) override`
- L40 _public function_ `bool operator==(const FTextureShareCoreFrameConnectionsSettings& In) const`
- L48 _public function_ `ETextureShareCoreFrameConnectionsState GetConnectionsState(const int32 InReadyToConnectObjectsCount, const int32 InFrameConnectionsCount) const`

#### struct `FTextureShareCoreFrameSyncSettings`  
`struct FTextureShareCoreFrameSyncSettings : public ITextureShareSerialize`  
_L72-92_
- inherits: `ITextureShareSerialize`
- desc: SyncSettings: define all sync steps for this object The structure is serializable (binary compatible) and reflected on the SDK side (UE types will be replaced with simplified copies from the SDK).
- L77 _public member_ `TArraySerializable<ETextureShareSyncStep> Steps;` — Used sync steps by this process (handled by logic above) Order of values: grow
- L80 _public prototype_ `virtual ~FTextureShareCoreFrameSyncSettings() = default;`
- L82 _public function_ `virtual ITextureShareSerializeStream& Serialize(ITextureShareSerializeStream& Stream) override`
- L88 _public function_ `bool EqualsFunc(const FTextureShareCoreFrameSyncSettings& In) const`

#### struct `FTextureShareCoreTimeOutSettings`  
`struct FTextureShareCoreTimeOutSettings : public ITextureShareSerialize`  
_L98-146_
- inherits: `ITextureShareSerialize`
- desc: SyncSettings: TimeOut values The structure is serializable (binary compatible) and reflected on the SDK side (UE types will be replaced with simplified copies from the SDK).
- L102 _public member_ `uint32 MemoryMutexTimeout = 1000;` — Memory mutex timeout in miliseconds
- L106 _public member_ `uint32 FrameBeginTimeOut = 0;` — Timeout for frame begin (process 0 - infinite
- L110 _public member_ `uint32 FrameSyncTimeOut = 1000;` — Max frame sync time, until this frame lost. 0 - infinite
- L113 _public member_ `uint32 FrameBeginTimeOutSplit = 100;` — Split time for timeouts. prevent freeze
- L114 _public member_ `uint32 FrameSyncTimeOutSplit = 100;`
- L120 _public member_ `int32 ProcessLostStatusTimeOut = 2000;` — now sync logic threat object as lost, if last access time expired. If the process is alive, it is re-created on-demant and re-connected '-1' - disable this option This value is unique per process.
- L123 _public member_ `int32 ThreadMutexTimeout = 1500;` — Multithreaded mutex timeout used in FTextureShareCoreObject::LockThread Mutex()
- L126 _public prototype_ `virtual ~FTextureShareCoreTimeOutSettings() = default;`
- L128 _public function_ `virtual ITextureShareSerializeStream& Serialize(ITextureShareSerializeStream & Stream) override`
- L136 _public function_ `bool operator==(const FTextureShareCoreTimeOutSettings& In) const`

#### struct `FTextureShareCoreSyncSettings`  
`struct FTextureShareCoreSyncSettings : public ITextureShareSerialize`  
_L152-179_
- inherits: `ITextureShareSerialize`
- desc: SyncSettings for TextureShareCore object The structure is serializable (binary compatible) and reflected on the SDK side (UE types will be replaced with simplified copies from the SDK).
- L157 _public member_ `FTextureShareCoreFrameConnectionsSettings FrameConnectionSettings;` — At the beginning of each frame, the local process waits for the required number of processes. If it is not reached within the specified time, then this frame will not start.
- L160 _public member_ `FTextureShareCoreTimeOutSettings TimeoutSettings;` — Timeout settings for internal IPC sync logic
- L163 _public member_ `FTextureShareCoreFrameSyncSettings FrameSyncSettings;` — Frame sync logic settings
- L166 _public prototype_ `virtual ~FTextureShareCoreSyncSettings() = default;`
- L168 _public function_ `virtual ITextureShareSerializeStream& Serialize(ITextureShareSerializeStream & Stream) override`
- L173 _public function_ `bool operator==(const FTextureShareCoreSyncSettings& In) const`

### `Plugins/VirtualProduction/TextureShare/Source/TextureShareCore/Private/Containers/TextureShareCoreContainers_ViewDesc.h` (Private)


#### struct `FTextureShareCoreViewDesc`  
`struct FTextureShareCoreViewDesc : public ITextureShareSerialize`  
_L11-64_
- inherits: `ITextureShareSerialize`
- desc: View descriptor (Name + EyeType) The structure is serializable (binary compatible) and reflected on the SDK side (UE types will be replaced with simplified copies from the SDK).
- L15 _public member_ `FString SrcId;` — Source view name (Debug log purpose)
- L18 _public member_ `FString Id = UE::TextureShareCoreStrings::DefaultViewId;` — View name
- L21 _public member_ `ETextureShareEyeType EyeType = ETextureShareEyeType::Default;` — Eye type of this view (support stereo)
- L24 _public prototype_ `virtual ~FTextureShareCoreViewDesc() = default;`
- L26 _public function_ `virtual ITextureShareSerializeStream& Serialize(ITextureShareSerializeStream & Stream) override`
- L32 _public prototype_ `FTextureShareCoreViewDesc() = default;`
- L34 _public function_ `FTextureShareCoreViewDesc(const FTextureShareCoreViewDesc & In) : SrcId(In.SrcId), Id(In.Id), EyeType(In.EyeType)`
- L38 _public function_ `FTextureShareCoreViewDesc(const FString& InSrcViewId, const FString& InViewId, const ETextureShareEyeType InEyeType = ETextureShareEyeType::Default) : SrcId(InSrcViewId), Id(InViewId), EyeType(InEyeType)`
- L42 _public function_ `FTextureShareCoreViewDesc(const FString & InViewId, const ETextureShareEyeType InEyeType = ETextureShareEyeType::Default) : Id(InViewId), EyeType(InEyeType)`
- L46 _public function_ `FTextureShareCoreViewDesc(const ETextureShareEyeType InEyeType) : EyeType(InEyeType)`
- L50 _public function_ `bool EqualsFunc(const FString& InViewId) const`
- L55 _public function_ `bool EqualsFunc(const FTextureShareCoreViewDesc & InViewDesc) const`
- L60 _public function_ `bool operator==(const FTextureShareCoreViewDesc& InViewDesc) const`

### `Plugins/VirtualProduction/TextureShare/Source/TextureShareCore/Private/Containers/TextureShareCoreEnums.h` (Private)


#### enum `ETextureShareDeviceType`  
`enum class ETextureShareDeviceType : uint8`  
_L12-20_
- desc: Render Device interface type
- L14 _public enumerator_ `Undefined = 0`
- L16 _public enumerator_ `D3D11`
- L17 _public enumerator_ `D3D12`
- L19 _public enumerator_ `Vulkan`

#### enum `ETextureShareProcessType`  
`enum class ETextureShareProcessType : uint8`  
_L26-49_
- desc: TextureShare Process type. This type means how processes are visible to each other.
- L29 _public enumerator_ `Undefined = 0` — Undefined process. Ignored by everyone.
- L33 _public enumerator_ `SDK` — External SDK default process type. Possible connections: [UE], [UE2UE]
- L44 _public enumerator_ `UE` — Note: Processes with type [UE] should not be visible to each other. The reason is that multiple instances of Unreal (i.e. nDisplay nodes) start connecting to each other on the same PC if the TextureShare plugin is used. This is because any TextureShare object tries to attach to any suitable remote process. Also, the "invisible" TS object is created by default on startup and starts that sync fight anyway. Therefore, for the UE+UE connection, we use a new process type [UE2UE].
- L48 _public enumerator_ `UE2UE` — Unreal Engine special process type. Possible connections: [SDK], [UE2UE]

#### enum `ETextureShareThreadMutex`  
`enum class ETextureShareThreadMutex : uint8`  
_L55-68_
- desc: Multithread mutex index Using this enum, you can access multi-threaded mutexes.
- L57 _public enumerator_ `GameThread = 0`
- L58 _public enumerator_ `RenderingThread`
- L60 _public enumerator_ `InternalLock`
- L61 _public enumerator_ `InternalObjectDescMT`
- L62 _public enumerator_ `InternalFrameConnectionsMT`
- L63 _public enumerator_ `InternalSyncSettingsMT`
- L65 _public enumerator_ `COUNT`
- L67 _public enumerator_ `MAX_LOG = InternalLock` — All mutexes after this dont produce log

#### enum `ETextureShareTextureOp`  
`enum class ETextureShareTextureOp : uint8`  
_L73-83_
- desc: Texture operation
- L76 _public enumerator_ `Undefined = 0` — Operation not defined (useful to find any type of operation)
- L79 _public enumerator_ `Write` — Send texture to remote process
- L82 _public enumerator_ `Read` — Receive texture

#### enum `ETextureShareEyeType`  
`enum class ETextureShareEyeType : uint8`  
_L88-96_
- desc: View eye type
- L91 _public enumerator_ `Default = 0` — Monoscopic
- L94 _public enumerator_ `StereoLeft` — Stereoscopic rendering
- L95 _public enumerator_ `StereoRight`

#### enum `ETextureShareFrameSyncTemplate`  
`enum class ETextureShareFrameSyncTemplate : uint8`  
_L101-115_
- desc: Sync steps template type
- L104 _public enumerator_ `Default = 0` — Sync logic for BP object
- L107 _public enumerator_ `SDK` — Minimalistic sync logic for SDK object
- L110 _public enumerator_ `DisplayCluster` — Sync logic for DC object
- L113 _public enumerator_ `DisplayClusterCrossNode` — Sync logic between DC nodes

#### enum `ETextureShareResourceType`  
`enum class ETextureShareResourceType: uint8`  
_L120-124_
- desc: Resource type
- L122 _public enumerator_ `Default = 0`
- L123 _public enumerator_ `CrossAdapter`

#### enum `ETextureShareSyncStep`  
`enum class ETextureShareSyncStep : uint8`  
_L129-181_
- desc: Sync steps values
- L131 _public enumerator_ `Undefined = 0`
- L133 _public enumerator_ `InterprocessConnection`
- L139 _public enumerator_ `FrameBegin`
- L141 _public enumerator_ `FramePreSetupBegin`
- L142 _public enumerator_ `FramePreSetupEnd`
- L144 _public enumerator_ `FrameSetupBegin`
- L145 _public enumerator_ `FrameSetupEnd`
- L147 _public enumerator_ `FramePostSetupBegin`
- L148 _public enumerator_ `FramePostSetupEnd`
- L150 _public enumerator_ `FrameFlush`
- L152 _public enumerator_ `FrameEnd`
- L158 _public enumerator_ `FrameProxyBegin`
- L160 _public enumerator_ `FrameSceneFinalColorBegin`
- L161 _public enumerator_ `FrameSceneFinalColorEnd`
- L163 _public enumerator_ `FrameProxyPreRenderBegin`
- L164 _public enumerator_ `FrameProxyPreRenderEnd`
- L166 _public enumerator_ `FrameProxyRenderBegin`
- L167 _public enumerator_ `FrameProxyRenderEnd`
- L169 _public enumerator_ `FrameProxyPostWarpBegin`
- L170 _public enumerator_ `FrameProxyPostWarpEnd`
- L172 _public enumerator_ `FrameProxyPostRenderBegin`
- L173 _public enumerator_ `FrameProxyPostRenderEnd`
- L175 _public enumerator_ `FrameProxyBackBufferReadyToPresentBegin`
- L176 _public enumerator_ `FrameProxyBackBufferReadyToPresentEnd`
- L178 _public enumerator_ `FrameProxyFlush`
- L180 _public enumerator_ `FrameProxyEnd`

#### enum `ETextureShareSyncPass`  
`enum class ETextureShareSyncPass : uint8`  
_L186-193_
- desc: Object sync barrier pass
- L188 _public enumerator_ `Undefined = 0`
- L190 _public enumerator_ `Enter`
- L191 _public enumerator_ `Exit`
- L192 _public enumerator_ `Complete`

#### enum `ETextureShareSyncState`  
`enum class ETextureShareSyncState : uint8`  
_L198-209_
- desc: Object sync barrier state
- L200 _public enumerator_ `Undefined = 0`
- L202 _public enumerator_ `Enter`
- L203 _public enumerator_ `EnterCompleted`
- L205 _public enumerator_ `Exit`
- L206 _public enumerator_ `ExitCompleted`
- L208 _public enumerator_ `Completed`

#### enum `ETextureShareCoreSceneViewManualProjectionType`  
`enum class ETextureShareCoreSceneViewManualProjectionType : uint8`  
_L214-218_
- desc: Projection matrix source type
- L216 _public enumerator_ `FrustumAngles = 0`
- L217 _public enumerator_ `Matrix`

#### enum `ETextureShareViewRotationDataType`  
`enum class ETextureShareViewRotationDataType : uint8`  
_L224-234_
- desc: Rotator operation type How to change the projection view rotator value
- L227 _public enumerator_ `Original = 0` — Use original value
- L230 _public enumerator_ `Relative` — Add value from manual projection
- L233 _public enumerator_ `Absolute` — Use value from manual projection

#### enum `ETextureShareViewLocationDataType`  
`enum class ETextureShareViewLocationDataType : uint8`  
_L240-259_
- desc: Location operation type How to change the projection view location value
- L243 _public enumerator_ `Original = 0` — Use original value
- L246 _public enumerator_ `Relative` — Add value from manual projection
- L249 _public enumerator_ `Absolute` — Use value from manual projection
- L252 _public enumerator_ `Original_NoViewOffset` — Use original value, but without stereo view offset
- L255 _public enumerator_ `Relative_NoViewOffset` — Add value from manual projection, but without stereo view offset
- L258 _public enumerator_ `Absolute_NoViewOffset` — Use value from manual projection, but without stereo view offset

### `Plugins/VirtualProduction/TextureShare/Source/TextureShareCore/Private/Core/ResourcesCache/D3D11/TextureShareCoreD3D11ResourcesCache.h` (Private)


#### class `FTextureShareCoreD3D11ResourcesCache`  
`class FTextureShareCoreD3D11ResourcesCache : public ITextureShareCoreD3D11ResourcesCache , public FTextureShareCoreResourcesCache`  
_L13-30_
- inherits: `ITextureShareCoreD3D11ResourcesCache,FTextureShareCoreResourcesCache`
- desc: D3D11 renderer resources cache container
- L18 _public function_ `FTextureShareCoreD3D11ResourcesCache(const TSharedPtr<FTextureShareCoreSecurityAttributes>& InSecurityAttributes) : SecurityAttributes(InSecurityAttributes)`
- L21 _public prototype_ `virtual ~FTextureShareCoreD3D11ResourcesCache() = default;`
- L24 _public prototype_ `virtual bool CreateSharedResource(const FTextureShareCoreObjectDesc& InObjectDesc, ID3D11Device* InD3D11Device, ID3D11Texture2D* InResourceD3D11, const FTextureShareCoreResourceDesc& InResourceDesc, FTextureShareCoreResourceHandle& OutResourceHandle) override;`
- L25 _public prototype_ `virtual ID3D11Texture2D* OpenSharedResource(const FTextureShareCoreObjectDesc& InObjectDesc, ID3D11Device* InD3D11Device, const FTextureShareCoreResourceHandle& InResourceHandle) override;`
- L26 _public prototype_ `virtual bool RemoveSharedResource(const FTextureShareCoreObjectDesc& InObjectDesc, ID3D11Texture2D* InResourceD3D11) override;`
- L29 _private member_ `TSharedPtr<FTextureShareCoreSecurityAttributes> SecurityAttributes;`

### `Plugins/VirtualProduction/TextureShare/Source/TextureShareCore/Private/Core/ResourcesCache/D3D11/TextureShareCoreD3D11ResourcesCacheItem.h` (Private)


#### class `FTextureShareCoreD3D11ResourcesCacheItem`  
`class FTextureShareCoreD3D11ResourcesCacheItem : public FTextureShareCoreResourcesCacheItem`  
_L10-33_
- inherits: `FTextureShareCoreResourcesCacheItem`
- desc: D3D11 renderer resource container
- L15 _public prototype_ `FTextureShareCoreD3D11ResourcesCacheItem(ID3D11Texture2D* InResourceD3D11, const FTextureShareCoreResourceDesc& InResourceDesc, const void* InSecurityAttributes);` — Create shared resource
- L18 _public prototype_ `FTextureShareCoreD3D11ResourcesCacheItem(ID3D11Device* InD3D11Device, const FTextureShareCoreResourceHandle& InResourceHandle);` — Open shared resource
- L20 _public prototype_ `virtual ~FTextureShareCoreD3D11ResourcesCacheItem();`
- L22 _public function_ `virtual void* GetNativeResource() const override`
- L29 _public member_ `bool bNeedReleaseD3D11Resource = false;` — Opened from Handle resources released
- L32 _public member_ `ID3D11Texture2D* D3D11Resource = nullptr;` — Saved resource ptr

### `Plugins/VirtualProduction/TextureShare/Source/TextureShareCore/Private/Core/ResourcesCache/D3D12/TextureShareCoreD3D12ResourcesCache.h` (Private)


#### class `FTextureShareCoreD3D12ResourcesCache`  
`class FTextureShareCoreD3D12ResourcesCache : public ITextureShareCoreD3D12ResourcesCache , public FTextureShareCoreResourcesCache`  
_L13-31_
- inherits: `ITextureShareCoreD3D12ResourcesCache,FTextureShareCoreResourcesCache`
- desc: D3D12 renderer resources cache container
- L18 _public function_ `FTextureShareCoreD3D12ResourcesCache(const TSharedPtr<FTextureShareCoreSecurityAttributes>& InSecurityAttributes) : SecurityAttributes(InSecurityAttributes)`
- L21 _public prototype_ `virtual ~FTextureShareCoreD3D12ResourcesCache() = default;`
- L24 _public prototype_ `virtual ID3D12Resource* CreateCrossAdapterResource(const FTextureShareCoreObjectDesc& InObjectDesc, ID3D12Device* InD3D12Device, const int32 InWidth, const int32 InHeight, const DXGI_FORMAT InFormat, const FTextureShareCoreResourceDesc& InResourceDesc, FTextureShareCoreResourceHandle& OutResourceHandle) override;`
- L26 _public prototype_ `virtual bool CreateSharedResource(const FTextureShareCoreObjectDesc& InObjectDesc, ID3D12Device* InD3D12Device, ID3D12Resource* InResourceD3D12, const uint32 InResourceGPUIndex, const FTextureShareCoreResourceDesc& InResourceDesc, FTextureShareCoreResourceHandle& OutResourceHandle) override;`
- L27 _public prototype_ `virtual ID3D12Resource* OpenSharedResource(const FTextureShareCoreObjectDesc& InObjectDesc, ID3D12Device* InD3D12Device, const FTextureShareCoreResourceHandle& InResourceHandle) override;`
- L28 _public prototype_ `virtual bool RemoveSharedResource(const FTextureShareCoreObjectDesc& InObjectDesc, ID3D12Resource* InResourceD3D12) override;`
- L30 _private member_ `TSharedPtr<FTextureShareCoreSecurityAttributes> SecurityAttributes;`

### `Plugins/VirtualProduction/TextureShare/Source/TextureShareCore/Private/Core/ResourcesCache/D3D12/TextureShareCoreD3D12ResourcesCacheItem.h` (Private)


#### class `FTextureShareCoreD3D12ResourcesCacheItem`  
`class FTextureShareCoreD3D12ResourcesCacheItem : public FTextureShareCoreResourcesCacheItem`  
_L10-50_
- inherits: `FTextureShareCoreResourcesCacheItem`
- desc: D3D12 renderer resource container
- L15 _public function_ `FTextureShareCoreD3D12ResourcesCacheItem(ID3D12Device* InD3D12Device, ID3D12Resource* InResourceD3D12, const FTextureShareCoreResourceDesc& InResourceDesc, const void* InSecurityAttributes)` — Create shared resource
- L21 _public function_ `FTextureShareCoreD3D12ResourcesCacheItem(ID3D12Device* InD3D12Device, const int32 InWidth, const int32 InHeight, const DXGI_FORMAT InFormat, const FTextureShareCoreResourceDesc& InResourceDesc, const void* InSecurityAttributes)` — Create cross-adapter shared resource
- L27 _public function_ `FTextureShareCoreD3D12ResourcesCacheItem(ID3D12Device* InD3D12Device, const FTextureShareCoreResourceHandle& InResourceHandle)` — Open shared resource
- L32 _public prototype_ `virtual ~FTextureShareCoreD3D12ResourcesCacheItem();`
- L34 _public function_ `virtual void* GetNativeResource() const override`
- L40 _private prototype_ `void ImplCreateSharedResource(ID3D12Device* InD3D12Device, ID3D12Resource* InResourceD3D12, const FTextureShareCoreResourceDesc& InResourceDesc, const void* InSecurityAttributes);`
- L41 _private prototype_ `void ImplCreateSharedCrossAdapterResource(ID3D12Device* InD3D12Device, const int32 InWidth, const int32 InHeight, const DXGI_FORMAT InFormat, const FTextureShareCoreResourceDesc& InResourceDesc, const void* InSecurityAttributes);`
- L42 _private prototype_ `void ImplOpenSharedResource(ID3D12Device* InD3D12Device, const FTextureShareCoreResourceHandle& InResourceHandle);`
- L46 _public member_ `bool bNeedReleaseD3D12Resource = false;` — Opened from Handle resources released
- L49 _public member_ `ID3D12Resource* D3D12Resource = nullptr;` — Saved resource ptr

### `Plugins/VirtualProduction/TextureShare/Source/TextureShareCore/Private/Core/ResourcesCache/TextureShareCoreResourcesCache.h` (Private)


#### class `FTextureShareCoreResourcesCache`  
`class FTextureShareCoreResourcesCache`  
_L10-39_
- desc: Render resource cache base
- L13 _public prototype_ `virtual ~FTextureShareCoreResourcesCache() = default;`
- L16 _public prototype_ `bool RemoveObjectCachedResources(const FTextureShareCoreObjectDesc& InObjectDesc);`
- L19 _public prototype_ `void RemoveUnusedResources(const uint32 InMilisecondsTimeOut);` — Release all resources last used more than specified timeout value
- L35 _protected prototype_ `FObjectCachedResources& GetObjectCachedResources(const FTextureShareCoreObjectDesc& InObjectDesc);`
- L38 _private member_ `TMap<FGuid, FObjectCachedResources> Objects;`

#### struct `FTextureShareCoreResourcesCache::FObjectCachedResources`  
`struct FObjectCachedResources`  
_L22-32_
- L24 _public prototype_ `FTextureShareCoreResourcesCacheItem* Find(const FTextureShareCoreResourceHandle& InResourceHandle);`
- L25 _public prototype_ `FTextureShareCoreResourcesCacheItem* FindByNativeResourcePtr(const void* InNativeResourcePtr);`
- L26 _public prototype_ `FTextureShareCoreResourcesCacheItem* FindByResourceDesc(const FTextureShareCoreResourceDesc& InResourceDesc);`
- L28 _public prototype_ `bool RemoveByNativeResourcePtr(const void* InNativeResourcePtr);`
- L31 _public member_ `TArray<TSharedPtr<FTextureShareCoreResourcesCacheItem>> Resources;`

### `Plugins/VirtualProduction/TextureShare/Source/TextureShareCore/Private/Core/ResourcesCache/TextureShareCoreResourcesCacheItem.h` (Private)


#### class `FTextureShareCoreResourcesCacheItem`  
`class FTextureShareCoreResourcesCacheItem`  
_L10-60_
- desc: Render resource cache item base
- L13 _public function_ `FTextureShareCoreResourcesCacheItem()`
- L18 _public function_ `virtual ~FTextureShareCoreResourcesCacheItem()`
- L23 _public function_ `virtual void* GetNativeResource() const`
- L29 _public function_ `const FTextureShareCoreResourceHandle& GetHandle() const`
- L34 _public function_ `void SetResourceHandleGPUIndex(const uint32 InGPUIndex)`
- L39 _public function_ `bool HandleEquals(const FTextureShareCoreResourceHandle& InResourceHandle) const`
- L44 _public prototype_ `void UpdateLastAccessTime();`
- L46 _public prototype_ `bool IsResourceUnused(const uint32 InMilisecondsTimeOut) const;`
- L49 _private prototype_ `void ReleaseHandle();`
- L53 _protected member_ `FTextureShareCoreResourceHandle Handle;` — Shared resource handles info
- L56 _protected member_ `uint64 LastAccessTime = 0;` — garbage collector for unused resources
- L59 _protected member_ `bool bNeedReleaseNTHandle = false;` — Close handles in destructor

### `Plugins/VirtualProduction/TextureShare/Source/TextureShareCore/Private/Core/ResourcesCache/Vulkan/TextureShareCoreVulkanResourcesCache.h` (Private)


#### class `FTextureShareCoreVulkanResourcesCache`  
`class FTextureShareCoreVulkanResourcesCache : public ITextureShareCoreVulkanResourcesCache , public FTextureShareCoreResourcesCache`  
_L12-29_
- inherits: `ITextureShareCoreVulkanResourcesCache,FTextureShareCoreResourcesCache`
- desc: Vulkan renderer resources cache container
- L17 _public function_ `FTextureShareCoreVulkanResourcesCache(const TSharedPtr<FTextureShareCoreSecurityAttributes>& InSecurityAttributes) : SecurityAttributes(InSecurityAttributes)`
- L20 _public prototype_ `virtual ~FTextureShareCoreVulkanResourcesCache() = default;`
- L23 _public prototype_ `virtual bool CreateSharedResource(const FTextureShareCoreObjectDesc& InObjectDesc, const FTextureShareDeviceVulkanContext& InDeviceVulkanContext, const FTextureShareDeviceVulkanResource& InVulkanResource, const FTextureShareCoreResourceDesc& InResourceDesc, FTextureShareCoreResourceHandle& OutResourceHandle) override;`
- L24 _public prototype_ `virtual FTextureShareDeviceVulkanResource OpenSharedResource(const FTextureShareCoreObjectDesc& InObjectDesc, const FTextureShareDeviceVulkanContext& InDeviceVulkanContext, const FTextureShareCoreResourceHandle& InResourceHandle) override;`
- L25 _public prototype_ `virtual bool RemoveSharedResource(const FTextureShareCoreObjectDesc& InObjectDesc, const FTextureShareDeviceVulkanContext& InDeviceVulkanContext, const FTextureShareDeviceVulkanResource& InVulkanResource) override;`
- L28 _private member_ `TSharedPtr<FTextureShareCoreSecurityAttributes> SecurityAttributes;`

### `Plugins/VirtualProduction/TextureShare/Source/TextureShareCore/Private/Core/ResourcesCache/Vulkan/TextureShareCoreVulkanResourcesCacheItem.h` (Private)


#### class `FTextureShareCoreVulkanResourcesCacheItem`  
`class FTextureShareCoreVulkanResourcesCacheItem : public FTextureShareCoreResourcesCacheItem`  
_L10-33_
- inherits: `FTextureShareCoreResourcesCacheItem`
- desc: Vulkan renderer resource container
- L15 _public prototype_ `FTextureShareCoreVulkanResourcesCacheItem(const FTextureShareDeviceVulkanContext& InDeviceVulkanContext, const FTextureShareDeviceVulkanResource& InVulkanResource, const FTextureShareCoreResourceDesc& InResourceDesc, const void* InSecurityAttributes);` — Create shared resource
- L18 _public prototype_ `FTextureShareCoreVulkanResourcesCacheItem(const FTextureShareDeviceVulkanContext& InDeviceVulkanContext, const FTextureShareCoreResourceHandle& InResourceHandle);` — Open shared resource
- L20 _public prototype_ `virtual ~FTextureShareCoreVulkanResourcesCacheItem();`
- L22 _public function_ `virtual void* GetNativeResource() const override`
- L28 _public member_ `const FTextureShareDeviceVulkanContext DeviceVulkanContext;`
- L31 _public member_ `bool bNeedReleaseVulkanResource = false;` — Opened from Handle resources released
- L32 _public member_ `FTextureShareDeviceVulkanResource VulkanResource;`

### `Plugins/VirtualProduction/TextureShare/Source/TextureShareCore/Private/Core/Serialize/ITextureShareCoreSerializeStream.h` (Private)


#### class `ITextureShareCoreSerializeStream`  
`class ITextureShareCoreSerializeStream : public ITextureShareSerializeStream`  
_L11-139_
- inherits: `ITextureShareSerializeStream`
- desc: Support UE core types serialization
- L15 _public prototype_ `virtual ~ITextureShareCoreSerializeStream() = default;`
- L18 _public function_ `virtual ITextureShareSerializeStream& operator<<(ITextureShareSerialize& InOutData) override` — Serialize any serializable objects
- L25 _public function_ `virtual ITextureShareSerializeStream& operator<<(int8& In) override` — Serialize atomic types:
- L26 _public function_ `virtual ITextureShareSerializeStream& operator<<(int16& In) override`
- L27 _public function_ `virtual ITextureShareSerializeStream& operator<<(int32& In) override`
- L28 _public function_ `virtual ITextureShareSerializeStream& operator<<(int64& In) override`
- L30 _public function_ `virtual ITextureShareSerializeStream& operator<<(uint8& In) override`
- L31 _public function_ `virtual ITextureShareSerializeStream& operator<<(uint16& In) override`
- L32 _public function_ `virtual ITextureShareSerializeStream& operator<<(uint32& In) override`
- L33 _public function_ `virtual ITextureShareSerializeStream& operator<<(uint64& In) override`
- L35 _public function_ `virtual ITextureShareSerializeStream& operator<<(float& In) override`
- L36 _public function_ `virtual ITextureShareSerializeStream& operator<<(double& In) override`
- L37 _public function_ `virtual ITextureShareSerializeStream& operator<<(bool& In) override`
- L41 _public function_ `virtual ITextureShareSerializeStream& operator<<(ETextureShareFrameSyncTemplate& In) override` — Serialize TextureShare enums:
- L42 _public function_ `virtual ITextureShareSerializeStream& operator<<(ETextureShareSyncPass& In) override`
- L43 _public function_ `virtual ITextureShareSerializeStream& operator<<(ETextureShareSyncState& In) override`
- L45 _public function_ `virtual ITextureShareSerializeStream& operator<<(ETextureShareSyncStep& In) override`
- L46 _public function_ `virtual ITextureShareSerializeStream& operator<<(ETextureShareResourceType& In) override`
- L48 _public function_ `virtual ITextureShareSerializeStream& operator<<(ETextureShareTextureOp& In) override`
- L49 _public function_ `virtual ITextureShareSerializeStream& operator<<(ETextureShareEyeType& In) override`
- L50 _public function_ `virtual ITextureShareSerializeStream& operator<<(ETextureShareProcessType& In) override`
- L51 _public function_ `virtual ITextureShareSerializeStream& operator<<(ETextureShareDeviceType& In) override`
- L53 _public function_ `virtual ITextureShareSerializeStream& operator<<(ETextureShareCoreSceneViewManualProjectionType& In) override`
- L54 _public function_ `virtual ITextureShareSerializeStream& operator<<(ETextureShareViewRotationDataType& In) override`
- L55 _public function_ `virtual ITextureShareSerializeStream& operator<<(ETextureShareViewLocationDataType& In) override`
- L59 _public function_ `virtual ITextureShareSerializeStream& operator<<(EPixelFormat& In) override` — Serialize other enums
- L60 _public function_ `virtual ITextureShareSerializeStream& operator<<(DXGI_FORMAT& In) override`
- L64 _public function_ `virtual ITextureShareSerializeStream& operator<<(FString& InOutData) override` — Serialize UECore types:
- L91 _public function_ `virtual ITextureShareSerializeStream& operator<<(FVector& InOutData) override`
- L96 _public function_ `virtual ITextureShareSerializeStream& operator<<(FVector2D& InOutData) override`
- L101 _public function_ `virtual ITextureShareSerializeStream& operator<<(FRotator& InOutData) override`
- L106 _public function_ `virtual ITextureShareSerializeStream& operator<<(FQuat& InOutData) override`
- L111 _public function_ `virtual ITextureShareSerializeStream& operator<<(FMatrix& InOutData) override`
- L120 _public function_ `virtual ITextureShareSerializeStream& operator<<(FIntRect& InOutData) override`
- L125 _public function_ `virtual ITextureShareSerializeStream& operator<<(FIntPoint& InOutData) override`
- L130 _public function_ `virtual ITextureShareSerializeStream& operator<<(FGuid& InOutData) override`
- L135 _public function_ `virtual ITextureShareSerializeStream& operator<<(Windows::HANDLE& InOutData) override`

### `Plugins/VirtualProduction/TextureShare/Source/TextureShareCore/Private/Core/TextureShareCore.h` (Private)


#### class `FTextureShareCore`  
`class FTextureShareCore : public ITextureShareCoreAPI`  
_L20-98_
- inherits: `ITextureShareCoreAPI`
- desc: TextureShareCore API implementation
- L24 _public prototype_ `FTextureShareCore();`
- L25 _public prototype_ `virtual ~FTextureShareCore();`
- L28 _public prototype_ `bool BeginSession();`
- L29 _public prototype_ `void EndSession();`
- L33 _public prototype_ `virtual TSharedPtr<class ITextureShareCoreObject, ESPMode::ThreadSafe> GetOrCreateCoreObject(const FString& ShareName, const ETextureShareProcessType InProcessType = ETextureShareProcessType::Undefined) override;`
- L34 _public prototype_ `virtual bool IsCoreObjectExist(const FString& ShareName) const override;`
- L35 _public prototype_ `virtual bool RemoveCoreObject(const FString& ShareName) override;`
- L37 _public prototype_ `virtual TSharedPtr<class ITextureShareCoreD3D11ResourcesCache, ESPMode::ThreadSafe> GetD3D11ResourcesCache() override;`
- L38 _public prototype_ `virtual TSharedPtr<class ITextureShareCoreD3D12ResourcesCache, ESPMode::ThreadSafe> GetD3D12ResourcesCache() override;`
- L39 _public prototype_ `virtual TSharedPtr<class ITextureShareCoreVulkanResourcesCache, ESPMode::ThreadSafe> GetVulkanResourcesCache() override;`
- L41 _public prototype_ `virtual void RemoveUnusedResources(const uint32 InMilisecondsTimeOut) override;`
- L43 _public prototype_ `virtual bool GetInterprocessObjects(const FString& InShareName, TArraySerializable<FTextureShareCoreObjectDesc>& OutInterprocessObjects) const override;`
- L45 _public prototype_ `virtual const FTextureShareCoreObjectProcessDesc& GetProcessDesc() const override;`
- L47 _public prototype_ `virtual void SetProcessName(const FString& InProcessId) override;`
- L48 _public prototype_ `virtual bool SetProcessDeviceType(const ETextureShareDeviceType InDeviceType) override;`
- L50 _public function_ `virtual ITextureShareCoreCallbacks& GetCallbacks() override`
- L56 _public prototype_ `bool RemoveCachedResources(const FTextureShareCoreObjectDesc& ObjectDesc);`
- L59 _public prototype_ `bool IsActive() const;`
- L60 _public prototype_ `bool IsSessionActive() const;`
- L63 _public prototype_ `struct FTextureShareCoreInterprocessMemory* GetInterprocessMemory() const;`
- L65 _public prototype_ `bool LockInterprocessMemory(const uint32 MaxMillisecondsToWait) const;`
- L66 _public prototype_ `void UnlockInterprocessMemory() const;`
- L68 _public prototype_ `TSharedPtr<FEvent, ESPMode::ThreadSafe> CreateInterprocessEvent(const FGuid& InEventGuid);`
- L69 _public prototype_ `TSharedPtr<FEvent, ESPMode::ThreadSafe> OpenInterprocessEvent(const FGuid& InEventGuid);`
- L72 _private prototype_ `bool InitializeInterprocessMemory();`
- L73 _private prototype_ `void ReleaseInterprocessMemory();`
- L77 _private member_ `static constexpr auto InterprocessMemoryName = TEXT("{DA` — Interprocess shared memory uses predefined names
- L78 _private member_ `static constexpr auto InterprocessMemoryMutexName = TEXT("Tex`
- L80 _private member_ `bool bIsSessionActive = false;`
- L82 _private member_ `TSharedPtr<FTextureShareCoreInterprocessMemoryRegion, ESPMode::ThreadSafe> InterprocessMemoryRegion;`
- L83 _private member_ `TSharedPtr<FTextureShareCoreInterprocessMutex, ESPMode::ThreadSafe> InterprocessMemoryMutex;`
- L85 _private member_ `TSharedPtr<FTextureShareCoreD3D11ResourcesCache, ESPMode::ThreadSafe> D3D11ResourcesCache;`
- L86 _private member_ `TSharedPtr<FTextureShareCoreD3D12ResourcesCache, ESPMode::ThreadSafe> D3D12ResourcesCache;`
- L87 _private member_ `TSharedPtr<FTextureShareCoreVulkanResourcesCache, ESPMode::ThreadSafe> VulkanResourcesCache;`
- L89 _private member_ `TSharedPtr<FTextureShareCoreSecurityAttributes> SecurityAttributes;`
- L92 _private member_ `FTextureShareCoreObjectProcessDesc ProcessDesc;` — Local process description
- L95 _private member_ `TMap<FString, TSharedPtr<FTextureShareCoreObject, ESPMode::ThreadSafe>> Objects;` — TS Objects
- L97 _private member_ `FTextureShareCoreCallbacks Callbacks;`

### `Plugins/VirtualProduction/TextureShare/Source/TextureShareCore/Private/Core/TextureShareCoreCallbacks.h` (Private)


#### class `FTextureShareCoreCallbacks`  
`class FTextureShareCoreCallbacks : public ITextureShareCoreCallbacks`  
_L10-67_
- inherits: `ITextureShareCoreCallbacks`
- desc: TextureShareCore callbacks API implementation
- L14 _public prototype_ `virtual ~FTextureShareCoreCallbacks() = default;`
- L17 _public function_ `virtual FTextureShareCoreBeginSessionEvent& OnTextureShareCoreBeginSession() override`
- L22 _public function_ `virtual FTextureShareCoreEndSessionEvent& OnTextureShareCoreEndSession() override`
- L27 _public function_ `virtual FTextureShareCoreBeginFrameSyncEvent& OnTextureShareCoreBeginFrameSync() override`
- L32 _public function_ `virtual FTextureShareCoreEndFrameSyncEvent& OnTextureShareCoreEndFrameSync() override`
- L37 _public function_ `virtual FTextureShareCoreFrameSyncEvent& OnTextureShareCoreFrameSync() override`
- L42 _public function_ `virtual FTextureShareCoreBeginFrameSyncEvent_RenderThread& OnTextureShareCoreBeginFrameSync_RenderThread() override`
- L47 _public function_ `virtual FTextureShareCoreEndFrameSyncEvent_RenderThread& OnTextureShareCoreEndFrameSync_RenderThread() override`
- L52 _public function_ `virtual FTextureShareCoreFrameSyncEvent_RenderThread& OnTextureShareCoreFrameSync_RenderThread() override`
- L58 _private member_ `FTextureShareCoreBeginSessionEvent TextureShareCoreBeginSessionEvent;`
- L59 _private member_ `FTextureShareCoreEndSessionEvent TextureShareCoreEndSessionEvent;`
- L60 _private member_ `FTextureShareCoreBeginFrameSyncEvent TextureShareCoreBeginFrameSyncEvent;`
- L61 _private member_ `FTextureShareCoreEndFrameSyncEvent TextureShareCoreEndFrameSyncEvent;`
- L62 _private member_ `FTextureShareCoreFrameSyncEvent TextureShareCoreFrameSyncEvent;`
- L64 _private member_ `FTextureShareCoreBeginFrameSyncEvent_RenderThread TextureShareCoreBeginFrameSyncEvent_RenderThread;`
- L65 _private member_ `FTextureShareCoreEndFrameSyncEvent_RenderThread TextureShareCoreEndFrameSyncEvent_RenderThread;`
- L66 _private member_ `FTextureShareCoreFrameSyncEvent_RenderThread TextureShareCoreFrameSyncEvent_RenderThread;`

### `Plugins/VirtualProduction/TextureShare/Source/TextureShareCore/Private/Core/TextureShareCoreHelpers.h` (Private)


#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace TextureShareCore` (scope `UE`)
- L15 _function_ `static constexpr auto GetTEXT(const ETextureShareDeviceType In)` (scope `UE::TextureShareCore`) — Debug log purpose
- L29 _function_ `static constexpr auto GetTEXT(const ETextureShareFrameSyncTemplate In)` (scope `UE::TextureShareCore`)
- L43 _function_ `static constexpr auto GetTEXT(const ETextureShareThreadMutex In)` (scope `UE::TextureShareCore`)
- L61 _function_ `static constexpr auto GetTEXT(const ETextureShareTextureOp In)` (scope `UE::TextureShareCore`)
- L74 _function_ `static constexpr auto GetTEXT(const ETextureShareEyeType InEyeType)` (scope `UE::TextureShareCore`)
- L88 _function_ `static constexpr auto GetTEXT(const ETextureShareSyncStep In)` (scope `UE::TextureShareCore`)
- L146 _function_ `static constexpr auto GetTEXT(const ETextureShareSyncPass In)` (scope `UE::TextureShareCore`)
- L160 _function_ `static constexpr auto GetTEXT(const ETextureShareSyncState In)` (scope `UE::TextureShareCore`)
- L179 _function_ `static FString ToString(const FTextureShareCoreObjectSyncState& InObjectSyncState)` (scope `UE::TextureShareCore`)
- L184 _function_ `static FString ToString(const FTextureShareCoreObjectDesc& InObject)` (scope `UE::TextureShareCore`)
- L189 _function_ `static FString ToString(const TArraySerializable<FTextureShareCoreObjectDesc>& InObjects)` (scope `UE::TextureShareCore`)
- L205 _function_ `static FString ToString(const FTextureShareCoreViewDesc& InViewDesc)` (scope `UE::TextureShareCore`)
- L210 _function_ `static FString ToString(const FTextureShareCoreResourceDesc& InResourceDesc)` (scope `UE::TextureShareCore`)
- L219 _function_ `static FString ToString(const FTextureShareCoreResourceRequest& InResourceRequest)` (scope `UE::TextureShareCore`)

### `Plugins/VirtualProduction/TextureShare/Source/TextureShareCore/Private/Core/TextureShareCoreSecurityAttributes.h` (Private)


#### enum `ETextureShareSecurityAttributesType`  
`enum class ETextureShareSecurityAttributesType : uint8`  
_L8-14_
- L10 _public enumerator_ `Resource = 0`
- L11 _public enumerator_ `Event`
- L13 _public enumerator_ `COUNT`

#### class `FTextureShareCoreSecurityAttributes`  
`class FTextureShareCoreSecurityAttributes`  
_L19-30_
- desc: Windows security descriptors for IPC
- L22 _public prototype_ `FTextureShareCoreSecurityAttributes();`
- L23 _public prototype_ `~FTextureShareCoreSecurityAttributes();`
- L26 _public prototype_ `const void* GetSecurityAttributes(const ETextureShareSecurityAttributesType InType) const;`
- L29 _private member_ `TUniquePtr<FWindowsSecurityAttributesHelper> SecurityAttributes[(uint8)ETextureShareSecurityAttributesType::COUNT];`

### `Plugins/VirtualProduction/TextureShare/Source/TextureShareCore/Private/Core/TextureShareCoreTime.h` (Private)


#### struct `FTextureShareCoreTime`  
`struct FTextureShareCoreTime`  
_L10-34_
- desc: Internal time API for TextureShare (SDK compiled without UE engine)
- L12 _public prototype_ `static void InitTiming();`
- L14 _public function_ `static uint64 Cycles64()`
- L21 _public function_ `static uint32 Cycles64ToMiliseconds(const uint64 InCycles64)`
- L26 _public function_ `static uint64 MilisecondsToCycles64(const uint32 InMiliseconds)`
- L32 _private member_ `static uint64 InitCycles64;`
- L33 _private member_ `static uint64 Cycle64PerSecond;`

### `Plugins/VirtualProduction/TextureShare/Source/TextureShareCore/Private/IPC/Containers/TextureShareCoreInterprocessContainers.h` (Private)


#### struct `FTextureShareCoreTimestump`  
`struct FTextureShareCoreTimestump`  
_L14-40_
- desc: Timestump container This structure fits the criteria of being POD ("Plain Old Data") for binary compatibility with direct memory access.
- L16 _public member_ `uint64 Time;`
- L19 _public function_ `void Empty()`
- L24 _public function_ `bool IsEmpty() const`
- L30 _public function_ `void Update()` — UPdate time value do current time
- L36 _public function_ `uint32 GetElapsedMilisecond() const` — return miliseconds from last update

#### struct `FTextureShareCoreGuid`  
`struct FTextureShareCoreGuid`  
_L46-89_
- desc: FGuid components container This structure fits the criteria of being POD ("Plain Old Data") for binary compatibility with direct memory access.
- L48 _public member_ `uint32 A;`
- L49 _public member_ `uint32 B;`
- L50 _public member_ `uint32 C;`
- L51 _public member_ `uint32 D;`
- L54 _public function_ `bool Equals(const FTextureShareCoreGuid& In) const`
- L59 _public function_ `void Empty()`
- L64 _public function_ `bool IsEmpty() const`
- L69 _public function_ `FGuid ToGuid() const`
- L74 _public function_ `void Initialize(const FGuid& InGuid)`
- L82 _public function_ `static FTextureShareCoreGuid Create(const FGuid& InGuid)`

#### struct `FTextureShareCoreSMD5Hash`  
`struct FTextureShareCoreSMD5Hash`  
_L95-132_
- desc: String MD5 hash container This structure fits the criteria of being POD ("Plain Old Data") for binary compatibility with direct memory access.
- L99 _public member_ `static constexpr auto MD5DigestLen = 16;` — MD5 digest is 16 bytes
- L102 _public member_ `uint8 MD5Digest[MD5DigestLen];` — MD5 hash value
- L105 _public function_ `bool Equals(const FTextureShareCoreSMD5Hash& In) const`
- L110 _public function_ `bool IsEnabled() const`
- L115 _public function_ `void Empty()`
- L120 _public prototype_ `void Initialize(const FString& InText);`
- L122 _public function_ `static FTextureShareCoreSMD5Hash Create(const FString& InString)`
- L131 _public member_ `static FTextureShareCoreSMD5Hash EmptyValue;`

#### struct `FTextureShareCoreSMD5HashList`  
`struct FTextureShareCoreSMD5HashList`  
_L138-185_
- desc: Simple constant array of MD5 string hashes This structure fits the criteria of being POD ("Plain Old Data") for binary compatibility with direct memory access.
- L142 _public member_ `static constexpr auto MaxStringsCnt = 16;` — Max count of elements in array This array is currently used as the holder of the sync settings process names.
- L145 _public member_ `FTextureShareCoreSMD5Hash List[MaxStringsCnt];` — MD5 hash values
- L148 _public function_ `void Empty()`
- L153 _public function_ `bool IsEmpty() const`
- L158 _public function_ `int32 Find(const FTextureShareCoreSMD5Hash& InHash) const`
- L176 _public prototype_ `void Initialize(const TArraySerializable<FString>& InStringList);`
- L178 _public function_ `static FTextureShareCoreSMD5HashList Create(const TArraySerializable<FString>& InStringList)`

#### struct `FTextureShareCoreStringHash`  
`struct FTextureShareCoreStringHash`  
_L191-234_
- desc: Unique MD5 hash produced from string This structure fits the criteria of being POD ("Plain Old Data") for binary compatibility with direct memory access.
- L195 _public member_ `static constexpr auto MaxStringLength = 128;` — Maximum string len This string is currently used as the holder of process names and textureshare objects.
- L198 _public member_ `wchar_t String[MaxStringLength];` — String value
- L201 _public member_ `FTextureShareCoreSMD5Hash Hash;` — MD5 hash of the string before
- L204 _public function_ `bool Equals(const FTextureShareCoreStringHash& In) const`
- L209 _public function_ `bool Equals(const FTextureShareCoreSMD5Hash& InHash) const`
- L214 _public function_ `FString ToString() const`
- L219 _public function_ `void Empty()`
- L226 _public prototype_ `void Initialize(const FString& InText);`
- L228 _public function_ `static FTextureShareCoreStringHash Create(const FString& InText)`

### `Plugins/VirtualProduction/TextureShare/Source/TextureShareCore/Private/IPC/Containers/TextureShareCoreInterprocessEnums.h` (Private)


#### enum `ETextureShareCoreInterprocessObjectDataType`  
`enum class ETextureShareCoreInterprocessObjectDataType : uint8`  
_L10-18_
- desc: Type of serialized data in memory area
- L13 _public enumerator_ `Undefined = 0` — Mem block not defined
- L16 _public enumerator_ `Frame` — data blocks by types
- L17 _public enumerator_ `FrameProxy`

#### enum `ETextureShareCoreInterprocessObjectFrameSyncState`  
`enum class ETextureShareCoreInterprocessObjectFrameSyncState: uint8`  
_L23-35_
- desc: Object synchronization state (internal use only)
- L25 _public enumerator_ `Undefined = 0`
- L26 _public enumerator_ `FrameSyncLost`
- L28 _public enumerator_ `NewFrame`
- L29 _public enumerator_ `FrameConnected`
- L30 _public enumerator_ `FrameBegin`
- L31 _public enumerator_ `FrameEnd`
- L33 _public enumerator_ `FrameProxyBegin`
- L34 _public enumerator_ `FrameProxyEnd`

#### enum `ETextureShareInterprocessObjectSyncBarrierState`  
`enum class ETextureShareInterprocessObjectSyncBarrierState : uint8`  
_L40-58_
- desc: Object barrier synchronization state (internal use only)
- L42 _public enumerator_ `Undefined = 0`
- L45 _public enumerator_ `UnusedSyncStep` — this process does not use this barrier
- L48 _public enumerator_ `WaitConnection` — Special logic for connection, because at this monent processes reconnected
- L49 _public enumerator_ `AcceptConnection`
- L51 _public enumerator_ `Wait`
- L52 _public enumerator_ `Accept`
- L54 _public enumerator_ `ObjectLost`
- L55 _public enumerator_ `FrameSyncLost`
- L57 _public enumerator_ `InvalidLogic`

### `Plugins/VirtualProduction/TextureShare/Source/TextureShareCore/Private/IPC/Containers/TextureShareCoreInterprocessMemory.h` (Private)


#### struct `FTextureShareCoreInterprocessMemory`  
`struct FTextureShareCoreInterprocessMemory`  
_L12-50_
- desc: This structure represents the entire block of shared memory. This structure fits the criteria of being POD ("Plain Old Data") for binary compatibility with direct memory access.
- L15 _public member_ `static constexpr auto MaxNumberOfInterprocessObject = 256;` — Maximum number of TextureShare IPC objects at the same time
- L18 _public member_ `FTextureShareCoreInterprocessObject Objects[MaxNumberOfInterprocessObject];` — TextureShare IPC objects containers
- L22 _public prototype_ `const FTextureShareCoreInterprocessObject* FindObject(const FTextureShareCoreObjectDesc& InObjectDesc) const;` — Find all not empty objects
- L23 _public prototype_ `FTextureShareCoreInterprocessObject* FindObject(const FTextureShareCoreObjectDesc& InObjectDesc);`
- L25 _public prototype_ `FTextureShareCoreInterprocessObject* FindEmptyObject();`
- L27 _public prototype_ `void ReleaseDirtyObjects(const FTextureShareCoreObjectDesc& InObjectDesc);`
- L30 _public prototype_ `bool IsUsedSyncBarrierPass(const TArraySerializable<FTextureShareCoreObjectDesc>& ObjectsDesc, const ETextureShareSyncStep InSyncStep);`
- L31 _public prototype_ `int32 FindConnectableObjects(TArraySerializable<FTextureShareCoreObjectDesc>& OutConnectableObjects, const FTextureShareCoreInterprocessObject& InObject) const;`
- L33 _public prototype_ `ETextureShareInterprocessObjectSyncBarrierState GetBarrierState(const FTextureShareCoreInterprocessObject& InObject, const TArraySerializable<FTextureShareCoreObjectDesc>& InFrameConnections) const;`
- L35 _public prototype_ `void UpdateFrameConnections(TArraySerializable<FTextureShareCoreObjectDesc>& InOutFrameConnections) const;`
- L38 _public prototype_ `int32 FindInterprocessObjects(TArraySerializable<FTextureShareCoreObjectDesc>& OutInterprocessObjects) const;`
- L41 _public prototype_ `int32 FindInterprocessObjects(TArraySerializable<FTextureShareCoreObjectDesc>& OutInterprocessObjects, const FTextureShareCoreSMD5Hash& InHash) const;` — Return all IPC objects with same name
- L43 _public function_ `int32 FindInterprocessObjects(TArraySerializable<FTextureShareCoreObjectDesc>& OutInterprocessObjects, const FString& InShareName) const`
- L49 _public prototype_ `int32 FindObjectEventListeners(TArray<const FTextureShareCoreInterprocessObject*>& OutObjects, const FTextureShareCoreObjectDesc& InObjectDesc) const;` — return remote IPC who may listen this object

### `Plugins/VirtualProduction/TextureShare/Source/TextureShareCore/Private/IPC/Containers/TextureShareCoreInterprocessObject.h` (Private)


#### struct `FTextureShareCoreInterprocessObject`  
`struct FTextureShareCoreInterprocessObject`  
_L12-60_
- desc: This structure represents the data of a TextureShare object in shared memory. This structure fits the criteria of being POD ("Plain Old Data") for binary compatibility with direct memory access.
- L15 _public member_ `FTextureShareCoreInterprocessObjectDesc Desc;` — Object ID data
- L18 _public member_ `FTextureShareCoreInterprocessObjectSync Sync;` — Object sync info
- L21 _public member_ `FTextureShareCoreInterprocessObjectData Data;` — Object data for IPC exchanges
- L24 _public function_ `bool IsEnabled() const`
- L29 _public function_ `bool GetDesc(FTextureShareCoreObjectDesc& OutDesc) const`
- L34 _public function_ `void InitializeInterprocessObject(const FTextureShareCoreObjectDesc& InObjectDesc, const FTextureShareCoreSyncSettings& InSyncSettings)`
- L46 _public function_ `void Release()`
- L53 _public function_ `void UpdateInterprocessObject(const FTextureShareCoreObjectDesc& InObjectDesc, const FTextureShareCoreSyncSettings& InSyncSettings)`

### `Plugins/VirtualProduction/TextureShare/Source/TextureShareCore/Private/IPC/Containers/TextureShareCoreInterprocessObjectContainers.h` (Private)


#### struct `FTextureShareCoreObjectDataRef`  
`struct FTextureShareCoreObjectDataRef : public ITextureShareSerialize`  
_L11-32_
- inherits: `ITextureShareSerialize`
- desc: Data wrapper for serializer
- L15 _public member_ `FTextureShareCoreObjectDesc ObjectDesc;` — Object ID
- L18 _public member_ `FTextureShareCoreData& Data;` — Setup frame data on game thread before rendering call
- L21 _public prototype_ `virtual ~FTextureShareCoreObjectDataRef() = default;`
- L23 _public function_ `virtual ITextureShareSerializeStream& Serialize(ITextureShareSerializeStream & Stream) override`
- L29 _public function_ `FTextureShareCoreObjectDataRef(const FTextureShareCoreObjectDesc& InObjectDesc, FTextureShareCoreData& InData) : ObjectDesc(InObjectDesc), Data(InData)`

#### struct `FTextureShareCoreObjectProxyDataRef`  
`struct FTextureShareCoreObjectProxyDataRef : public ITextureShareSerialize`  
_L37-58_
- inherits: `ITextureShareSerialize`
- desc: Data wrapper for serializer
- L41 _public member_ `FTextureShareCoreObjectDesc ObjectDesc;` — Object ID
- L44 _public member_ `FTextureShareCoreProxyData& ProxyData;` — Setup frame data on game thread before rendering call
- L47 _public prototype_ `virtual ~FTextureShareCoreObjectProxyDataRef() = default;`
- L49 _public function_ `virtual ITextureShareSerializeStream& Serialize(ITextureShareSerializeStream & Stream) override`
- L55 _public function_ `FTextureShareCoreObjectProxyDataRef(const FTextureShareCoreObjectDesc& InObjectDesc, FTextureShareCoreProxyData& InProxyData) : ObjectDesc(InObjectDesc), ProxyData(InProxyData)`

### `Plugins/VirtualProduction/TextureShare/Source/TextureShareCore/Private/IPC/Containers/TextureShareCoreInterprocessObjectData.h` (Private)


#### struct `FTextureShareCoreInterprocessObjectDataHeader`  
`struct FTextureShareCoreInterprocessObjectDataHeader`  
_L10-24_
- desc: IPC object Data Header: define data size, type and access time This structure fits the criteria of being POD ("Plain Old Data") for binary compatibility with direct memory access.
- L13 _public member_ `ETextureShareCoreInterprocessObjectDataType Type;` — Type of serialized data in memory area
- L16 _public member_ `uint32 Size;` — Size of serialized data in memory area
- L19 _public member_ `FTextureShareCoreTimestump LastWriteTime;` — Time when serialized data was last written to memory
- L22 _public prototype_ `void Initialize();`
- L23 _public prototype_ `void Release();`

#### struct `FTextureShareCoreInterprocessObjectDataMemory`  
`struct FTextureShareCoreInterprocessObjectDataMemory`  
_L30-45_
- desc: IPC object Data Container: raw memory bytes for serializer This structure fits the criteria of being POD ("Plain Old Data") for binary compatibility with direct memory access.
- L33 _public member_ `static auto constexpr MaxInterprocessObjectDataSize = (32 * 1024);` — Maximum size of serialized data
- L36 _public member_ `uint8 Data[MaxInterprocessObjectDataSize];` — Memory area for serialized data
- L40 _public function_ `void Initialize()` — The 'Data' is references from the 'DataHeader', no cleanup required
- L43 _public function_ `void Release()`

#### struct `FTextureShareCoreInterprocessObjectData`  
`struct FTextureShareCoreInterprocessObjectData`  
_L51-85_
- desc: TS object memory container for serializer This structure fits the criteria of being POD ("Plain Old Data") for binary compatibility with direct memory access.
- L54 _public member_ `FTextureShareCoreInterprocessObjectDataHeader DataHeader;` — Serialized data description
- L57 _public member_ `FTextureShareCoreInterprocessObjectDataMemory DataMemory;` — Serialized data container
- L60 _public function_ `bool IsEnabled(const ETextureShareCoreInterprocessObjectDataType InDataType) const`
- L65 _public function_ `void Initialize()`
- L71 _public function_ `void Release()`
- L79 _public prototype_ `bool Write(struct FTextureShareCoreObjectDataRef& InObjectData);` — Serialize
- L80 _public prototype_ `bool Write(struct FTextureShareCoreObjectProxyDataRef& InObjectProxyData);`
- L83 _public prototype_ `bool Read(struct FTextureShareCoreObjectData& OutObjectData) const;` — De-Serialize
- L84 _public prototype_ `bool Read(struct FTextureShareCoreObjectProxyData& OutObjectProxyData) const;`

### `Plugins/VirtualProduction/TextureShare/Source/TextureShareCore/Private/IPC/Containers/TextureShareCoreInterprocessObjectDesc.h` (Private)


#### struct `FTextureShareCoreInterprocessObjectDesc`  
`struct FTextureShareCoreInterprocessObjectDesc`  
_L10-129_
- desc: IPC object descriptor This structure fits the criteria of being POD ("Plain Old Data") for binary compatibility with direct memory access.
- L13 _public member_ `FTextureShareCoreGuid ObjectGuid;` — Unique process guid. Generated unique for a local process
- L17 _public member_ `FTextureShareCoreStringHash ShareName;` — MD5 hash of the object name. Generated from a ShareName using the MD5 hash function. Paired objects use identical hash values
- L20 _public member_ `FTextureShareCoreStringHash ProcessName;` — MD5 hash of the process name. Generated from a ProcessName using the MD5 hash function.
- L23 _public member_ `FTextureShareCoreGuid ProcessGuid;` — Unique process guid
- L26 _public member_ `ETextureShareProcessType ProcessType;` — The local process type
- L29 _public function_ `bool IsEnabled() const`
- L34 _public function_ `bool Equals(const FTextureShareCoreGuid& InObjectGuid) const`
- L39 _public function_ `bool Equals(const FTextureShareCoreObjectDesc& InObjectDesc) const`
- L44 _public function_ `bool IsShareNameEquals(const FString& InShareName) const`
- L49 _public function_ `bool IsShareNameEquals(const FTextureShareCoreStringHash& InShareNameHash) const`
- L54 _public function_ `bool IsShareNameEquals(const FTextureShareCoreSMD5Hash& InHash) const`
- L59 _public function_ `bool IsConnectable(const FTextureShareCoreInterprocessObjectDesc& In) const`
- L64 _public function_ `bool IsConnectable(const FTextureShareCoreSMD5Hash& InHash, const ETextureShareProcessType InProcessType) const`
- L126 _public prototype_ `void Initialize(const FTextureShareCoreObjectDesc& InCoreObjectDesc);`
- L127 _public prototype_ `void Release();`
- L128 _public prototype_ `bool GetDesc(FTextureShareCoreObjectDesc& OutDesc) const;`

### `Plugins/VirtualProduction/TextureShare/Source/TextureShareCore/Private/IPC/Containers/TextureShareCoreInterprocessObjectSync.h` (Private)


#### struct `FTextureShareCoreInterprocessObjectSync`  
`struct FTextureShareCoreInterprocessObjectSync`  
_L13-143_
- desc: IPC object data: Sync This structure fits the criteria of being POD ("Plain Old Data") for binary compatibility with direct memory access.
- L16 _public member_ `FTextureShareCoreInterprocessObjectSyncState SyncState;` — interprocess sync logic
- L19 _public member_ `FTextureShareCoreInterprocessObjectSyncSettings SyncSettings;` — Sync settings
- L22 _public member_ `FTextureShareCoreTimestump LastAccessTime;` — Last access time from this object
- L25 _public member_ `bool bProcessStuck;` — This flag set after any frame begin timeout\connect for all unused processes
- L28 _public prototype_ `void Release();`
- L29 _public prototype_ `bool GetDesc(FTextureShareCoreObjectDesc& OutDesc) const;`
- L37 _public function_ `void UpdateLastAccessTime()` — Touch the time avery time when process get own data
- L45 _public function_ `bool IsEnabled() const`
- L59 _public function_ `ETextureShareInterprocessObjectSyncBarrierState GetBarrierState(const FTextureShareCoreInterprocessObjectSync& InObjectSync) const`
- L89 _public function_ `void MarkProcessStuck()`
- L96 _public function_ `bool BeginSyncBarrier(const ETextureShareSyncStep InSyncStep, const ETextureShareSyncPass InSyncPass, const ETextureShareSyncStep InNextSyncStep)`
- L102 _public function_ `bool AcceptSyncBarrier(const ETextureShareSyncStep InSyncStep, const ETextureShareSyncPass InSyncPass)`
- L108 _public function_ `bool IsBarrierCompleted(const ETextureShareSyncStep InSyncStep, const ETextureShareSyncPass InSyncPass) const`
- L128 _public function_ `void ResetSync()`
- L134 _public function_ `const FTextureShareCoreInterprocessObjectSyncState& GetSyncState() const`
- L139 _public function_ `const FTextureShareCoreInterprocessObjectSyncSettings& GetSyncSettings() const`

### `Plugins/VirtualProduction/TextureShare/Source/TextureShareCore/Private/IPC/Containers/TextureShareCoreInterprocessObjectSyncSettings.h` (Private)


#### struct `FTextureShareCoreInterprocessObjectSyncSettings`  
`struct FTextureShareCoreInterprocessObjectSyncSettings`  
_L12-99_
- desc: IPC object data: SyncSettings This structure fits the criteria of being POD ("Plain Old Data") for binary compatibility with direct memory access.
- L15 _public member_ `FTextureShareCoreSMD5HashList AllowedProcessNames;` — Synchronization settings for allowed/forbidden process names
- L16 _public member_ `FTextureShareCoreSMD5HashList BannedProcessNames;`
- L20 _public member_ `uint64 Data;` — Bit-storage for sync steps used by this process 64 bits. Max steps=64
- L23 _public member_ `int32 ProcessLostStatusTimeOut;` — process status loss timeout for local process
- L26 _public prototype_ `void UpdateInterprocessObjectSyncSettings(const struct FTextureShareCoreObjectDesc& InObjectDesc, const struct FTextureShareCoreSyncSettings& InSyncSettings);`
- L27 _public prototype_ `void Release();`
- L30 _public function_ `bool IsStepEnabled(const ETextureShareSyncStep InStep) const`
- L47 _public function_ `bool IsProcessLost(const uint32 InElapsedMilisecond) const`
- L64 _public function_ `bool IsShouldBeConnected(const FTextureShareCoreStringHash& LocalProcessName, const FTextureShareCoreStringHash& RemoteProcessName, const FTextureShareCoreInterprocessObjectSyncSettings& RemoteProcessSyncSettings) const` — The rules accepted in both directions
- L70 _public function_ `uint64 GetData() const`
- L76 _protected function_ `bool IsProcessNameShouldBeConnected(const FTextureShareCoreSMD5Hash& InProcessName) const`

### `Plugins/VirtualProduction/TextureShare/Source/TextureShareCore/Private/IPC/Containers/TextureShareCoreInterprocessObjectSyncState.h` (Private)


#### struct `FTextureShareCoreInterprocessObjectSyncState`  
`struct FTextureShareCoreInterprocessObjectSyncState`  
_L11-58_
- desc: IPC object data: SyncState This structure fits the criteria of being POD ("Plain Old Data") for binary compatibility with direct memory access.
- L14 _public member_ `ETextureShareSyncStep Step;` — Barrier sync step
- L17 _public member_ `ETextureShareSyncState State;` — Barrier sync state
- L20 _public member_ `ETextureShareSyncStep NextStep;` — Next sync step
- L23 _public member_ `ETextureShareSyncStep PrevStep;` — Prev sync step
- L27 _public prototype_ `bool BeginSyncBarrier(const ETextureShareSyncStep InSyncStep, const ETextureShareSyncPass InSyncPass, const ETextureShareSyncStep InNextSyncStep);` — Enter barrier
- L30 _public prototype_ `bool AcceptSyncBarrier(const ETextureShareSyncStep InSyncStep, const ETextureShareSyncPass InSyncPass);` — Accept barrier (Called agter BeginSyncBarrier)
- L33 _public prototype_ `void ResetSync();` — Whe error or sync is lost
- L36 _public prototype_ `ETextureShareInterprocessObjectSyncBarrierState GetBarrierState(const FTextureShareCoreInterprocessObjectSyncState& InSync) const;` — Return barrier state
- L39 _public prototype_ `void Read(FTextureShareCoreObjectSyncState& OutSyncState) const;` — Export barrier state from compressed POD to UE struct
- L42 _public prototype_ `void Initialize();`
- L43 _public prototype_ `void Release();`
- L46 _private prototype_ `bool HandleLogicBroken();`
- L48 _private prototype_ `ETextureShareInterprocessObjectSyncBarrierState GetConnectionBarrierState(const FTextureShareCoreInterprocessObjectSyncState& InSync) const;`
- L49 _private prototype_ `ETextureShareInterprocessObjectSyncBarrierState GetConnectionBarrierState_Enter(const FTextureShareCoreInterprocessObjectSyncState& InSync) const;`
- L50 _private prototype_ `ETextureShareInterprocessObjectSyncBarrierState GetConnectionBarrierState_EnterCompleted(const FTextureShareCoreInterprocessObjectSyncState& InSync) const;`
- L52 _private prototype_ `ETextureShareInterprocessObjectSyncBarrierState GetBarrierState_Enter(const FTextureShareCoreInterprocessObjectSyncState& InSync) const;`
- L53 _private prototype_ `ETextureShareInterprocessObjectSyncBarrierState GetBarrierState_EnterCompleted(const FTextureShareCoreInterprocessObjectSyncState& InSync) const;`
- L54 _private prototype_ `ETextureShareInterprocessObjectSyncBarrierState GetBarrierState_Exit(const FTextureShareCoreInterprocessObjectSyncState& InSync) const;`
- L55 _private prototype_ `ETextureShareInterprocessObjectSyncBarrierState GetBarrierState_ExitCompleted(const FTextureShareCoreInterprocessObjectSyncState& InSync) const;`
- L57 _private prototype_ `ETextureShareInterprocessObjectSyncBarrierState HandleBarrierStateResult(const FTextureShareCoreInterprocessObjectSyncState& InSync, const ETextureShareInterprocessObjectSyncBarrierState InBarrierState) const;`

### `Plugins/VirtualProduction/TextureShare/Source/TextureShareCore/Private/IPC/TextureShareCoreInterprocessEvent.h` (Private)


#### class `FTextureShareCoreInterprocessEventWin`  
`class FTextureShareCoreInterprocessEventWin : public FEvent`  
_L10-53_
- inherits: `FEvent`
- desc: IPC events (Windows)
- L14 _public function_ `FTextureShareCoreInterprocessEventWin(Windows::HANDLE InEvent) : Event(InEvent)`
- L18 _public function_ `virtual ~FTextureShareCoreInterprocessEventWin()`
- L24 _public function_ `virtual bool Create(bool bIsManualReset = false) override` — FEvent
- L29 _public prototype_ `virtual void Trigger() override;`
- L30 _public prototype_ `virtual void Reset() override;`
- L31 _public prototype_ `virtual bool Wait(uint32 MaxMillisecondsToWait, const bool bIgnoreThreadIdleStats = false) override;`
- L32 _public function_ `virtual bool IsManualReset() override`
- L38 _public function_ `Windows::HANDLE GetEventHandle() const`
- L44 _protected prototype_ `void ReleaseEvent();`
- L47 _public prototype_ `static TSharedPtr<FEvent, ESPMode::ThreadSafe> CreateInterprocessEvent(const FGuid& InEventGuid, const void* InSecurityAttributes);`
- L48 _public prototype_ `static TSharedPtr<FEvent, ESPMode::ThreadSafe> OpenInterprocessEvent(const FGuid& InEventGuid, const void* InSecurityAttributes);`
- L52 _private member_ `Windows::HANDLE Event;` — Holds the handle to the event.

### `Plugins/VirtualProduction/TextureShare/Source/TextureShareCore/Private/IPC/TextureShareCoreInterprocessHelpers.h` (Private)


#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace TextureShareCore` (scope `UE`)
- L11 _function_ `static constexpr auto GetTEXT(const ETextureShareInterprocessObjectSyncBarrierState InBarrierState)` (scope `UE::TextureShareCore`)
- L33 _function_ `static constexpr auto GetTEXT(const ETextureShareCoreInterprocessObjectFrameSyncState InSyncState)` (scope `UE::TextureShareCore`)
- L54 _function_ `static FString ToString(const FTextureShareCoreInterprocessObjectSyncState& InObjectSyncState)` (scope `UE::TextureShareCore`)
- L59 _function_ `static FString ToString(const FTextureShareCoreInterprocessObject& InObject)` (scope `UE::TextureShareCore`)
- L64 _function_ `static FString ToString(const TArray<FTextureShareCoreInterprocessObject*>& InObjects)` (scope `UE::TextureShareCore`)

### `Plugins/VirtualProduction/TextureShare/Source/TextureShareCore/Private/IPC/TextureShareCoreInterprocessMemoryRegion.h` (Private)


#### class `FTextureShareCoreInterprocessMemoryRegion`  
`class FTextureShareCoreInterprocessMemoryRegion`  
_L9-29_
- desc: IPC Shared Memory
- L12 _public prototype_ `FTextureShareCoreInterprocessMemoryRegion(const FString& InSharedMemoryRegionName);`
- L13 _public prototype_ `~FTextureShareCoreInterprocessMemoryRegion();`
- L16 _public prototype_ `bool Initialize();` — Initialize shared memory resources
- L18 _public prototype_ `struct FTextureShareCoreInterprocessMemory* GetInterprocessMemory() const;`
- L21 _private prototype_ `bool CleanupInterprocessObjects() const;`
- L22 _private prototype_ `void ReleaseInterprocessObjects();`
- L25 _public member_ `const FString SharedMemoryRegionName;`
- L28 _private member_ `void* PlatformMemoryRegion = nullptr;`

### `Plugins/VirtualProduction/TextureShare/Source/TextureShareCore/Private/IPC/TextureShareCoreInterprocessMutex.h` (Private)


#### class `FTextureShareCoreInterprocessMutex`  
`class FTextureShareCoreInterprocessMutex`  
_L12-63_
- desc: The mutex class implementation. This class can be used in both cases, for processes and threads.
- L15 _public function_ `FTextureShareCoreInterprocessMutex()`
- L18 _public prototype_ `~FTextureShareCoreInterprocessMutex();`
- L23 _public function_ `bool InitializeInterprocessMutex(const FString& InMutexId)` — Create a interprocess platform mutex object in the global namespace @param InMutexId - the name of the interprocess mutex
- L29 _public function_ `bool Initialize()` — Create a multithread platform mutex object in the local namespace.
- L42 _public prototype_ `bool LockMutex(const uint32 InMaxMillisecondsToWait);` — Tries to acquire and exclusive access for a specified amount of nanoseconds (also known as TryWait()). @param InMaxMillisecondsToWait - milliseconds to wait for @return false if was not able to lock within given time
- L45 _public prototype_ `void UnlockMutex();` — Relinquishes an exclusive access (also known as Release())
- L48 _public function_ `bool IsValid() const` — Is the platform mutex exist.
- L55 _private prototype_ `bool InitializeInterprocessMutex(bool bGlobalNameSpace, const FString& InMutexId);` — Implementation of mutex opening/creation.
- L58 _private prototype_ `void ReleaseInterprocessMutex();` — Implementation of mutex releasing.
- L62 _private member_ `FGenericPlatformProcess::FSemaphore* PlatformMutex = nullptr;` — the reference to the platform mutex

### `Plugins/VirtualProduction/TextureShare/Source/TextureShareCore/Private/IPC/TextureShareCoreInterprocessSerializer.h` (Private)


#### class `FTextureShareCoreSerializeStreamRead`  
`class FTextureShareCoreSerializeStreamRead : public ITextureShareCoreSerializeStream`  
_L13-38_
- inherits: `ITextureShareCoreSerializeStream`
- desc: Simple memory serializer - Read
- L17 _public function_ `FTextureShareCoreSerializeStreamRead(const FTextureShareCoreInterprocessObjectData& InSrcObject) : SrcObject(InSrcObject)`
- L21 _public function_ `virtual bool IsWriteStream() const`
- L27 _protected function_ `virtual FTextureShareCoreSerializeStreamRead& SerializeData(void* InDataPtr, const uint32_t InDataSize) override`
- L33 _private prototype_ `FTextureShareCoreSerializeStreamRead& ReadDataFromStream(void* InDataPtr, const uint32_t InDataSize);`
- L36 _private member_ `const FTextureShareCoreInterprocessObjectData& SrcObject;`
- L37 _private member_ `uint32_t CurrentPos = 0;`

#### class `FTextureShareCoreSerializeStreamWrite`  
`class FTextureShareCoreSerializeStreamWrite : public ITextureShareCoreSerializeStream`  
_L43-73_
- inherits: `ITextureShareCoreSerializeStream`
- desc: Simple memory serializer - Write
- L47 _public function_ `FTextureShareCoreSerializeStreamWrite(FTextureShareCoreInterprocessObjectData& InDstObject) : DstObject(InDstObject)`
- L51 _public function_ `virtual bool IsWriteStream() const`
- L57 _protected function_ `virtual FTextureShareCoreSerializeStreamWrite& SerializeData(void* InDataPtr, const uint32_t InDataSize) override`
- L62 _protected function_ `virtual FTextureShareCoreSerializeStreamWrite& SerializeData(const void* InDataPtr, const uint32_t InDataSize) override`
- L68 _protected prototype_ `FTextureShareCoreSerializeStreamWrite& WriteDataToStream(const void* InDataPtr, const uint32_t InDataSize);`
- L71 _private member_ `FTextureShareCoreInterprocessObjectData& DstObject;`
- L72 _private member_ `uint32_t CurrentPos = 0;`

### `Plugins/VirtualProduction/TextureShare/Source/TextureShareCore/Private/ITextureShareCoreAPI.h` (Private)


#### class `ITextureShareCoreAPI`  
`class ITextureShareCoreAPI`  
_L16-109_
- desc: TextureShareCore API
- L19 _public prototype_ `virtual ~ITextureShareCoreAPI() = default;`
- L25 _public prototype_ `virtual TSharedPtr<ITextureShareCoreD3D11ResourcesCache, ESPMode::ThreadSafe> GetD3D11ResourcesCache() = 0;` — Returns D3D11 TextureShare resources cache interface
- L30 _public prototype_ `virtual TSharedPtr<ITextureShareCoreD3D12ResourcesCache, ESPMode::ThreadSafe> GetD3D12ResourcesCache() = 0;` — Returns D3D12 TextureShare resources cache interface
- L35 _public prototype_ `virtual TSharedPtr<ITextureShareCoreVulkanResourcesCache, ESPMode::ThreadSafe> GetVulkanResourcesCache() = 0;` — Returns Vulkan TextureShare resources cache interface
- L45 _public prototype_ `virtual TSharedPtr<class ITextureShareCoreObject, ESPMode::ThreadSafe> GetOrCreateCoreObject(const FString& ShareName, const ETextureShareProcessType ProcessType = ETextureShareProcessType::Undefined) = 0;` — Get or create new TextureShareCore object @param ShareName - Unique share name. Objects with the same name will try to connect @return - Ptr to TextureShareCore object
- L54 _public prototype_ `virtual bool IsCoreObjectExist(const FString& ShareName) const = 0;` — The test for the TextureShareCore object with the specified name exists. @param ShareName - Unique share name @return - true, if object with the specified name still exists.
- L63 _public prototype_ `virtual bool RemoveCoreObject(const FString& ShareName) = 0;` — Remove TextureShareCore object @param ShareName - Unique share name @return True if the object with this name removed
- L74 _public prototype_ `virtual bool GetInterprocessObjects(const FString& InShareName, TArraySerializable<FTextureShareCoreObjectDesc>& OutInterprocessObjects) const = 0;` — Returns a list of handles to interprocess TextureShare objects with the specified name. @param InShareName            - (optional) name of the TextureShare object @param OutInterprocessObjects - Output array with handles to TextureShare objects @return true, if success
- L79 _public prototype_ `virtual const struct FTextureShareCoreObjectProcessDesc& GetProcessDesc() const = 0;` — Returns detailed information about the local process
- L86 _public prototype_ `virtual void SetProcessName(const FString& InProcessId) = 0;` — Assign a unique name to the local process. The changes only affect newly created TextureShare objects. @param InProcessId - Custom local process name
- L93 _public prototype_ `virtual bool SetProcessDeviceType(const ETextureShareDeviceType InDeviceType) = 0;` — Assign a device type to the local process. The changes only affect newly created TextureShare objects. @param InDeviceType - render device type
- L100 _public prototype_ `virtual void RemoveUnusedResources(const uint32 InMilisecondsTimeOut) = 0;` — Release all resources last used more than specified timeout value @param InMilisecondsTimeout- Timeout to remove resource
- L108 _public prototype_ `virtual ITextureShareCoreCallbacks& GetCallbacks() = 0;` — Access to the TextureShareCore callbacks API @return Callbacks API

### `Plugins/VirtualProduction/TextureShare/Source/TextureShareCore/Private/ITextureShareCoreCallbacks.h` (Private)


#### class `ITextureShareCoreCallbacks`  
`class ITextureShareCoreCallbacks`  
_L13-54_
- desc: TextureShareCore callbacks API
- L16 _public prototype_ `static ITextureShareCoreCallbacks& Get();`
- L18 _public prototype_ `virtual ~ITextureShareCoreCallbacks() = default;`
- L22 _public prototype_ `DECLARE_EVENT_OneParam(ITextureShareCoreCallbacks, FTextureShareCoreBeginSessionEvent, ITextureShareCoreObject&);` — Called on session start
- L23 _public prototype_ `virtual FTextureShareCoreBeginSessionEvent& OnTextureShareCoreBeginSession() = 0;`
- L26 _public prototype_ `DECLARE_EVENT_OneParam(ITextureShareCoreCallbacks, FTextureShareCoreEndSessionEvent, ITextureShareCoreObject&);` — Called on session end
- L27 _public prototype_ `virtual FTextureShareCoreEndSessionEvent& OnTextureShareCoreEndSession() = 0;`
- L31 _public prototype_ `DECLARE_EVENT_OneParam(ITextureShareCoreCallbacks, FTextureShareCoreBeginFrameSyncEvent, ITextureShareCoreObject&);` — Called on begin frame sync
- L32 _public prototype_ `virtual FTextureShareCoreBeginFrameSyncEvent& OnTextureShareCoreBeginFrameSync() = 0;`
- L35 _public prototype_ `DECLARE_EVENT_OneParam(ITextureShareCoreCallbacks, FTextureShareCoreEndFrameSyncEvent, ITextureShareCoreObject&);` — Called on end frame sync
- L36 _public prototype_ `virtual FTextureShareCoreEndFrameSyncEvent& OnTextureShareCoreEndFrameSync() = 0;`
- L39 _public prototype_ `DECLARE_EVENT_TwoParams(ITextureShareCoreCallbacks, FTextureShareCoreFrameSyncEvent, ITextureShareCoreObject&, const ETextureShareSyncStep);` — Called on frame sync
- L40 _public prototype_ `virtual FTextureShareCoreFrameSyncEvent& OnTextureShareCoreFrameSync() = 0;`
- L44 _public prototype_ `DECLARE_EVENT_OneParam(ITextureShareCoreCallbacks, FTextureShareCoreBeginFrameSyncEvent_RenderThread, ITextureShareCoreObject&);` — Called on begin frame sync on render thread
- L45 _public prototype_ `virtual FTextureShareCoreBeginFrameSyncEvent_RenderThread& OnTextureShareCoreBeginFrameSync_RenderThread() = 0;`
- L48 _public prototype_ `DECLARE_EVENT_OneParam(ITextureShareCoreCallbacks, FTextureShareCoreEndFrameSyncEvent_RenderThread, ITextureShareCoreObject&);` — Called on end frame sync on render thread
- L49 _public prototype_ `virtual FTextureShareCoreEndFrameSyncEvent_RenderThread& OnTextureShareCoreEndFrameSync_RenderThread() = 0;`
- L52 _public prototype_ `DECLARE_EVENT_TwoParams(ITextureShareCoreCallbacks, FTextureShareCoreFrameSyncEvent_RenderThread, ITextureShareCoreObject&, const ETextureShareSyncStep);` — Called on frame sync on render thread
- L53 _public prototype_ `virtual FTextureShareCoreFrameSyncEvent_RenderThread& OnTextureShareCoreFrameSync_RenderThread() = 0;`

#### Free symbols / members of external scopes

- L22 _delegate_ `DECLARE_EVENT_OneParam(ITextureShareCoreCallbacks, FTextureShareCoreBeginSessionEvent, ITextureShareCoreObject&);` — Called on session start
- L26 _delegate_ `DECLARE_EVENT_OneParam(ITextureShareCoreCallbacks, FTextureShareCoreEndSessionEvent, ITextureShareCoreObject&);` — Called on session end
- L31 _delegate_ `DECLARE_EVENT_OneParam(ITextureShareCoreCallbacks, FTextureShareCoreBeginFrameSyncEvent, ITextureShareCoreObject&);` — Called on begin frame sync
- L35 _delegate_ `DECLARE_EVENT_OneParam(ITextureShareCoreCallbacks, FTextureShareCoreEndFrameSyncEvent, ITextureShareCoreObject&);` — Called on end frame sync
- L39 _delegate_ `DECLARE_EVENT_TwoParams(ITextureShareCoreCallbacks, FTextureShareCoreFrameSyncEvent, ITextureShareCoreObject&, const ETextureShareSyncStep);` — Called on frame sync
- L44 _delegate_ `DECLARE_EVENT_OneParam(ITextureShareCoreCallbacks, FTextureShareCoreBeginFrameSyncEvent_RenderThread, ITextureShareCoreObject&);` — Called on begin frame sync on render thread
- L48 _delegate_ `DECLARE_EVENT_OneParam(ITextureShareCoreCallbacks, FTextureShareCoreEndFrameSyncEvent_RenderThread, ITextureShareCoreObject&);` — Called on end frame sync on render thread
- L52 _delegate_ `DECLARE_EVENT_TwoParams(ITextureShareCoreCallbacks, FTextureShareCoreFrameSyncEvent_RenderThread, ITextureShareCoreObject&, const ETextureShareSyncStep);` — Called on frame sync on render thread

### `Plugins/VirtualProduction/TextureShare/Source/TextureShareCore/Private/ITextureShareCoreD3D11ResourcesCache.h` (Private)


#### class `ITextureShareCoreD3D11ResourcesCache`  
`class ITextureShareCoreD3D11ResourcesCache`  
_L15-54_
- desc: API for Shared Resources on the D3D11 renderer
- L18 _public prototype_ `virtual ~ITextureShareCoreD3D11ResourcesCache() = default;`
- L32 _public prototype_ `virtual bool CreateSharedResource(const FTextureShareCoreObjectDesc& InObjectDesc, ID3D11Device* InD3D11Device, ID3D11Texture2D* InResourceD3D11, const FTextureShareCoreResourceDesc& InResourceDesc, FTextureShareCoreResourceHandle& OutResourceHandle) = 0;` — Create a handle to a share from a D3D11 resource @param InObjectDesc      - A handle to a TextureShare object. This object is the owner of the resource @param InD3D11Device     - D3D11 device interface @param InResourceD3D11   - D3D11 resource interface @param InResourceDesc    - Resource information for TS core (Eye, type of operation, sync pass, etc) @param OutResourceHandle - Output resource handle @return true if success
- L43 _public prototype_ `virtual ID3D11Texture2D* OpenSharedResource(const FTextureShareCoreObjectDesc& InObjectDesc, ID3D11Device* InD3D11Device, const FTextureShareCoreResourceHandle& InResourceHandle) = 0;` — Open shared resource from the handle, and return D3D11 resource @param InObjectDesc     - A handle to a TextureShare object. This object is the owner of the resource @param InD3D11Device    - D3D11 device interface @param InResourceHandle - Shared resource handle @return sharedPtr to D3D11 resource
- L53 _public prototype_ `virtual bool RemoveSharedResource(const FTextureShareCoreObjectDesc& InObjectDesc, ID3D11Texture2D* InResourceD3D11) = 0;` — Remove cached shared handle from D3D11 resource @param InObjectDesc    - A handle to a TextureShare object. This object is the owner of the resource @param InResourceD3D11 - texture resource interface @return true if success

### `Plugins/VirtualProduction/TextureShare/Source/TextureShareCore/Private/ITextureShareCoreD3D12ResourcesCache.h` (Private)


#### class `ITextureShareCoreD3D12ResourcesCache`  
`class ITextureShareCoreD3D12ResourcesCache`  
_L15-69_
- desc: API for Shared Resources on the D3D12 renderer
- L18 _public prototype_ `virtual ~ITextureShareCoreD3D12ResourcesCache() = default;`
- L34 _public prototype_ `virtual ID3D12Resource* CreateCrossAdapterResource(const FTextureShareCoreObjectDesc& InObjectDesc, ID3D12Device* InD3D12Device, const int32 InWidth, const int32 InHeight, const DXGI_FORMAT InFormat, const FTextureShareCoreResourceDesc& InResourceDesc, FTextureShareCoreResourceHandle& OutResourceHandle) = 0;` — Create a D3D12 cross-adapter resource @param InObjectDesc      - A handle to a TextureShare object. This object is the owner of the resource @param InD3D12Device     - D3D12 device interface @param InWidth           - resource size X @param InHeight          - resource size Y @param InFormat          - resource format @param InResourceDesc    - Resource information for TS core (Eye, type of operation, sync pass, etc) @param OutResourceHandle - Output resource handle @return nullptr if failed
- L47 _public prototype_ `virtual bool CreateSharedResource(const FTextureShareCoreObjectDesc& InObjectDesc, ID3D12Device* InD3D12Device, ID3D12Resource* InResourceD3D12, const uint32 InResourceGPUIndex, const FTextureShareCoreResourceDesc& InResourceDesc, FTextureShareCoreResourceHandle& OutResourceHandle) = 0;` — Create a handle to a share from a D3D12 resource @param InObjectDesc      - A handle to a TextureShare object. This object is the owner of the resource @param InD3D12Device     - D3D12 device interface @param InResourceD3D12   - D3D12 resource interface @param InResourceDesc    - Resource information for TS core (Eye, type of operation, sync pass, etc) @param OutResourceHandle - Output resource handle @return true if success
- L58 _public prototype_ `virtual ID3D12Resource* OpenSharedResource(const FTextureShareCoreObjectDesc& InObjectDesc, ID3D12Device* InD3D12Device, const FTextureShareCoreResourceHandle& InResourceHandle) = 0;` — Open shared resource from the handle, and return D3D12 resource @param InObjectDesc     - A handle to a TextureShare object. This object is the owner of the resource @param InD3D12Device    - D3D12 device interface @param InResourceHandle - Shared resource handle @return sharedPtr to D3D12 resource
- L68 _public prototype_ `virtual bool RemoveSharedResource(const FTextureShareCoreObjectDesc& InObjectDesc, ID3D12Resource* InResourceD3D12) = 0;` — Remove cached shared handle from D3D12 resource @param InObjectDesc    - A handle to a TextureShare object. This object is the owner of the resource @param InResourceD3D12 - texture resource interface @return true if success

### `Plugins/VirtualProduction/TextureShare/Source/TextureShareCore/Private/ITextureShareCoreObject.h` (Private)


#### class `ITextureShareCoreObject`  
`class ITextureShareCoreObject`  
_L10-269_
- desc: TextureShareCore object API
- L13 _public prototype_ `virtual ~ITextureShareCoreObject() = default;`
- L21 _public prototype_ `virtual const FString& GetName() const = 0;` — Return the name of the TextureShare.
- L26 _public prototype_ `virtual FTextureShareCoreObjectDesc GetObjectDesc() const = 0;` — Returns detailed information about the TextureShare object.
- L31 _public prototype_ `virtual FTextureShareCoreObjectDesc GetObjectDesc_RenderThread() const = 0;` — Returns detailed information about the TextureShare proxy object.
- L36 _public prototype_ `virtual bool IsActive() const = 0;` — Returns true if the TextureShare object is ready to be used.
- L41 _public prototype_ `virtual bool IsActive_RenderThread() const = 0;` — Returns true if the TextureShare proxy object is ready to be used.
- L46 _public prototype_ `virtual bool IsFrameSyncActive() const = 0;` — Returns true if the TextureShareCore object has started a session and processes are connected for this frame.
- L51 _public prototype_ `virtual bool IsFrameSyncActive_RenderThread() const = 0;` — Returns true if the TextureShareCore proxy object has started a session and processes are connected for this frame.
- L56 _public prototype_ `virtual bool IsBeginFrameSyncActive() const = 0;` — Returns true if the BeginFrameSync() function can be called at this moment
- L61 _public prototype_ `virtual bool IsBeginFrameSyncActive_RenderThread() const = 0;` — Returns true if the BeginFrameSync_RenderThread() function can be called at this moment
- L74 _public prototype_ `virtual bool SetProcessId(const FString& InProcessId) = 0;` — Change the process name for this TextureShare object. If the object is synced now, then the changes are deferred and executed in the next frame. @param InProcessId - New process name @return true, if success
- L81 _public prototype_ `virtual bool SetDeviceType(const ETextureShareDeviceType InDeviceType) = 0;` — Assign a device type for this TextureShare object. @param InDeviceType - render device type
- L91 _public prototype_ `virtual bool SetSyncSettings(const FTextureShareCoreSyncSettings& InSyncSettings) = 0;` — Change the sync settings for this TextureShare object. If the object is synced now, then the changes are deferred and executed in the next frame. @param InSyncSetting - New sync settings @return true, if success
- L96 _public prototype_ `virtual FTextureShareCoreSyncSettings GetSyncSettings() const = 0;` — Return the sync settings of the TextureShare.
- L106 _public prototype_ `virtual FTextureShareCoreFrameSyncSettings GetFrameSyncSettings(const ETextureShareFrameSyncTemplate InType) const = 0;` — Get TextureShare default sync settings by template type The settings of this template are not related to the current settings of the object @param InType - Sync settings template type @return structure with sync logic settings
- L117 _public prototype_ `virtual bool FindSkippedSyncStep(const ETextureShareSyncStep InSyncStep, ETextureShareSyncStep& OutSkippedSyncStep) = 0;` — Find skipped frame sync step for object @param InSyncStep           - Sync step value @param bIsRenderThreadFrame - TS has two sync steps groups: for the game thread and for the rendering thread. @param OutSkippedSyncStep   - Skipped sync step value @return true, if skipped sync step found
- L128 _public prototype_ `virtual bool FindSkippedSyncStep_RenderThread(const ETextureShareSyncStep InSyncStep, ETextureShareSyncStep& OutSkippedSyncStep) = 0;` — Find skipped frame sync step for proxy object @param InSyncStep           - Sync step value @param bIsRenderThreadFrame - TS has two sync steps groups: for the game thread and for the rendering thread. @param OutSkippedSyncStep   - Skipped sync step value @return true, if skipped sync step found
- L140 _public prototype_ `virtual bool BeginSession() = 0;` — Start a TextureShare session for the specified device @param InDeviceType     - Shared resources render device type @return True if the success
- L147 _public prototype_ `virtual bool EndSession() = 0;` — End the TextureShare session and the resources in use are also removed. @return True if the success
- L152 _public prototype_ `virtual bool IsSessionActive() const = 0;` — Returns true if the session is currently valid
- L166 _public prototype_ `virtual bool LockThreadMutex(const ETextureShareThreadMutex InThreadMutex, bool bForceLockNoWait = false) const = 0;` — Support for multi-threaded implementation. The mutex of the specified type will be locked (and created for the first time) @param InThreadMutex - Mutex type @param bForceLockNoWait - lock without waiting for unlock @return True if the success
- L176 _public prototype_ `virtual bool UnlockThreadMutex(const ETextureShareThreadMutex InThreadMutex) const = 0;` — Support for multi-threaded implementation. The mutex of the specified type will be unlocked @param InThreadMutex - Mutex type @return True if the success
- L186 _public prototype_ `virtual bool BeginFrameSync() = 0;` — Begin sync logic in range FrameBegin..FrameEnd The list of connected processes for the current frame will also be updated. Returns true if the frame is connected to other processes that match the synchronization settings.
- L197 _public prototype_ `virtual bool FrameSync(const ETextureShareSyncStep InSyncStep) = 0;` — Synchronize connected processes that support this sync step Data from remote processes will be read at the time the barrier is synchronized. Missed sync steps from the sync settings will also be called. @param InSyncStep - Sync step value @return True if the success
- L203 _public prototype_ `virtual bool EndFrameSync() = 0;` — Finalize sync logic in range FrameBegin..FrameEnd Missed sync steps from the sync settings will also be called.
- L208 _public prototype_ `virtual bool BeginFrameSync_RenderThread() = 0;` — Begin sync logic in range FrameProxyBegin..FrameProxyEnd
- L219 _public prototype_ `virtual bool FrameSync_RenderThread(const ETextureShareSyncStep InSyncStep) = 0;` — Synchronize connected processes that support this sync step ProxyData from remote processes will be read at the time the barrier is synchronized. Missed sync steps from the sync settings will also be called. @param InSyncStep - Sync step value @return True if the success
- L225 _public prototype_ `virtual bool EndFrameSync_RenderThread() = 0;` — Finalize sync logic in range FrameProxyBegin..FrameProxyEnd Missed sync steps from the sync settings will also be called.
- L234 _public prototype_ `virtual TArraySerializable<FTextureShareCoreObjectDesc> GetConnectedInterprocessObjects() const = 0;` — Returns a list of handles to the interprocess TextureShare objects that are currently connected to this object. @param OutInterprocessObjects - Output array with handles to TextureShare objects @return true, if success
- L243 _public prototype_ `virtual FTextureShareCoreData& GetData() = 0;` — Reference to Data. Object data for the current frame in the GameThread.
- L249 _public prototype_ `virtual FTextureShareCoreProxyData& GetProxyData_RenderThread() = 0;` — Reference to ProxyData. Object proxy data for the current frame in the RenderThread.
- L254 _public prototype_ `virtual TArraySerializable<FTextureShareCoreObjectData> GetReceivedData() const = 0;` — Received Data from connected process objects
- L259 _public prototype_ `virtual TArraySerializable<FTextureShareCoreObjectProxyData> GetReceivedProxyData_RenderThread() const= 0;` — Received ProxyData from connected process objects
- L268 _public prototype_ `virtual bool RemoveObject() = 0;` — Remove TextureShareCore object call ITextureShareCoreAPI::Remove()

### `Plugins/VirtualProduction/TextureShare/Source/TextureShareCore/Private/ITextureShareCoreVulkanResourcesCache.h` (Private)


#### class `ITextureShareCoreVulkanResourcesCache`  
`class ITextureShareCoreVulkanResourcesCache`  
_L15-55_
- desc: API for Shared Resources on the Vulkan renderer
- L18 _public prototype_ `virtual ~ITextureShareCoreVulkanResourcesCache() = default;`
- L32 _public prototype_ `virtual bool CreateSharedResource(const FTextureShareCoreObjectDesc& InObjectDesc, const FTextureShareDeviceVulkanContext& InDeviceVulkanContext, const FTextureShareDeviceVulkanResource& InVulkanResource, const FTextureShareCoreResourceDesc& InResourceDesc, FTextureShareCoreResourceHandle& OutResourceHandle) = 0;` — Create a handle to a share from a Vulkan resource @param InObjectDesc          - A handle to a TextureShare object. This object is the owner of the resource @param InDeviceVulkanContext - Vulkan device context @param InVulkanResource      - Vulkan resource context @param InResourceDesc        - Resource information for TS core (Eye, type of operation, sync pass, etc) @param OutResourceHandle     - Output resource handle @return true if success
- L43 _public prototype_ `virtual FTextureShareDeviceVulkanResource OpenSharedResource(const FTextureShareCoreObjectDesc& InObjectDesc, const FTextureShareDeviceVulkanContext& InDeviceVulkanContext, const FTextureShareCoreResourceHandle& InResourceHandle) = 0;` — Open shared resource from the handle, and return Vulkan resource @param InObjectDesc          - A handle to a TextureShare object. This object is the owner of the resource @param InDeviceVulkanContext - Vulkan device context @param InResourceHandle      - Shared resource handle @return sharedPtr to Vulkan resource memory handle
- L54 _public prototype_ `virtual bool RemoveSharedResource(const FTextureShareCoreObjectDesc& InObjectDesc, const FTextureShareDeviceVulkanContext& InDeviceVulkanContext, const FTextureShareDeviceVulkanResource& InVulkanResource) = 0;` — Remove cached shared handle from Vulkan resource @param InObjectDesc          - A handle to a TextureShare object. This object is the owner of the resource @param InDeviceVulkanContext - Vulkan device context @param InVulkanResource      - Vulkan resource context @return true if success

### `Plugins/VirtualProduction/TextureShare/Source/TextureShareCore/Private/Misc/TextureShareCoreStrings.h` (Private)


#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace TextureShareCoreStrings` (scope `UE`)
- L15 _variable_ `static constexpr auto DefaultShareName = TEXT("Def` (scope `UE::TextureShareCoreStrings`)
- L17 _variable_ `static constexpr auto DefaultViewId = TEXT("Def` (scope `UE::TextureShareCoreStrings`)
- L19 _namespace_ `namespace DefaultProcessName` (scope `UE::TextureShareCoreStrings`)
- L23 _variable_ `static constexpr auto SDK = TEXT(TEXTURESHARE_PROJECT_NAME);` (scope `UE::TextureShareCoreStrings::DefaultProcessName`) — Use TextureShare project name as process name
- L27 _variable_ `static constexpr auto UE = TEXT("Unr` (scope `UE::TextureShareCoreStrings::DefaultProcessName`)

### `Plugins/VirtualProduction/TextureShare/Source/TextureShareCore/Private/Module/TextureShareCoreLog.h` (Private)


#### Free symbols / members of external scopes

- L9 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogTextureShareCore, Warning, Warning);`
- L9 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogTextureShareCore, Warning, Warning);`
- L10 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogTextureShareCoreD3D, Warning, Warning);`
- L10 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogTextureShareCoreD3D, Warning, Warning);`
- L11 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogTextureShareCoreWindows, Warning, Warning);`
- L11 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogTextureShareCoreWindows, Warning, Warning);`
- L12 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogTextureShareCoreObject, Warning, Warning);`
- L12 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogTextureShareCoreObject, Warning, Warning);`
- L13 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogTextureShareCoreObjectSync, Warning, Warning);`
- L13 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogTextureShareCoreObjectSync, Warning, Warning);`
- L14 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogTextureShareCoreProxyObjectSync, Warning, Warning);`
- L14 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogTextureShareCoreProxyObjectSync, Warning, Warning);`
- L16 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogTextureShareCore, Log, All);`
- L16 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogTextureShareCore, Log, All);`
- L17 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogTextureShareCoreD3D, Log, All);`
- L17 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogTextureShareCoreD3D, Log, All);`
- L18 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogTextureShareCoreWindows, Log, All);`
- L18 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogTextureShareCoreWindows, Log, All);`
- L19 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogTextureShareCoreObject, Log, All);`
- L19 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogTextureShareCoreObject, Log, All);`
- L20 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogTextureShareCoreObjectSync, Log, All);`
- L20 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogTextureShareCoreObjectSync, Log, All);`
- L21 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogTextureShareCoreProxyObjectSync, Log, All);`
- L21 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogTextureShareCoreProxyObjectSync, Log, All);`

### `Plugins/VirtualProduction/TextureShare/Source/TextureShareCore/Private/Module/TextureShareCoreLogDefines.h` (Private)


#### struct `FTextureShareCoreLogHelpers`  
`struct FTextureShareCoreLogHelpers`  
_L22-25_
- desc: Enable extra log in VS output window
- L24 _public prototype_ `static void WriteLine(const FString& In);`

#### Free symbols / members of external scopes

- L27 _macro_ `#define UE_LOG(CategoryName, Verbosity, Format, ...)\`
- L30 _macro_ `#define UE_TS_LOG(CategoryName, Verbosity, Format, ...)\`
- L36 _macro_ `#define UE_TS_BARRIER_LOG(CategoryName, Verbosity, Format, ...)\`
- L41 _macro_ `#define UE_TS_BARRIER_LOG(CategoryName, Verbosity, Format, ...)` — Disable extra log
- L46 _macro_ `#define UE_LOG(CategoryName, Verbosity, Format, ...)` — Disable all log
- L47 _macro_ `#define UE_TS_LOG(CategoryName, Verbosity, Format, ...)`

### `Plugins/VirtualProduction/TextureShare/Source/TextureShareCore/Private/Module/TextureShareCoreModule.h` (Private)


#### class `FTextureShareCoreModule`  
`class FTextureShareCoreModule : public ITextureShareCore`  
_L10-35_
- inherits: `ITextureShareCore`
- desc: TextureShareCore module implementation
- L14 _public function_ `virtual ~FTextureShareCoreModule()`
- L19 _public prototype_ `virtual void StartupModule() override;`
- L20 _public prototype_ `virtual void ShutdownModule() override;`
- L28 _public prototype_ `virtual ITextureShareCoreAPI& GetTextureShareCoreAPI() override;` — Returns Core API Interface Put headers in an Internal folder. This limits visibility to other engine modules, and allows implementations to be changed in hotfixes.
- L31 _protected prototype_ `void ShutdownModuleImpl();`
- L34 _private member_ `TUniquePtr<FTextureShareCore> TextureShareCoreAPI;`

### `Plugins/VirtualProduction/TextureShare/Source/TextureShareCore/Private/Object/TextureShareCoreObject.h` (Private)


#### class `FTextureShareCoreObject`  
`class FTextureShareCoreObject : public ITextureShareCoreObject`  
_L14-223_
- inherits: `ITextureShareCoreObject`
- desc: TextureShareCore object api implementation
- L18 _public prototype_ `FTextureShareCoreObject(FTextureShareCore& InOwner, const FString& InTextureShareName, const ETextureShareProcessType InProcessType);`
- L19 _public prototype_ `virtual ~FTextureShareCoreObject();`
- L24 _public prototype_ `virtual const FString& GetName() const override;`
- L26 _public prototype_ `virtual FTextureShareCoreObjectDesc GetObjectDesc() const override;`
- L27 _public prototype_ `virtual FTextureShareCoreObjectDesc GetObjectDesc_RenderThread() const override;`
- L29 _public prototype_ `virtual bool IsActive() const override;`
- L30 _public prototype_ `virtual bool IsActive_RenderThread() const override;`
- L32 _public prototype_ `virtual bool IsFrameSyncActive() const override;`
- L33 _public prototype_ `virtual bool IsFrameSyncActive_RenderThread() const override;`
- L35 _public prototype_ `virtual bool IsBeginFrameSyncActive() const override;`
- L36 _public prototype_ `virtual bool IsBeginFrameSyncActive_RenderThread() const override;`
- L39 _protected prototype_ `const FTextureShareCoreObjectDesc GetObjectDesc_AnyThread() const;`
- L43 _private member_ `FTextureShareCoreObjectDesc ObjectDescMT;` — (MultiThread access data)
- L48 _public prototype_ `virtual bool SetProcessId(const FString& InProcessId) override;`
- L49 _public prototype_ `virtual bool SetDeviceType(const ETextureShareDeviceType InDeviceType) override;`
- L51 _public prototype_ `virtual bool SetSyncSettings(const FTextureShareCoreSyncSettings& InSyncSettings) override;`
- L52 _public prototype_ `virtual FTextureShareCoreSyncSettings GetSyncSettings() const override;`
- L54 _public prototype_ `virtual FTextureShareCoreFrameSyncSettings GetFrameSyncSettings(const ETextureShareFrameSyncTemplate InType) const override;`
- L59 _private member_ `FTextureShareCoreSyncSettings SyncSettingsMT;` — This settings used for a frame (MultiThread access data)
- L62 _protected prototype_ `void AddNewSyncStep(const ETextureShareSyncStep InSyncStep);`
- L63 _protected prototype_ `void UpdateInterprocessObject();`
- L66 _protected prototype_ `const FTextureShareCoreTimeOutSettings& GetTimeOutSettings() const;` — Special exception for timeout settings: they do not use arrays and are thread-safe.
- L71 _public prototype_ `virtual bool BeginSession() override;`
- L72 _public prototype_ `virtual bool EndSession() override;`
- L73 _public prototype_ `virtual bool IsSessionActive() const override;`
- L76 _private member_ `bool bSessionActive = false;`
- L81 _public prototype_ `virtual bool LockThreadMutex(const ETextureShareThreadMutex InThreadMutex, bool bForceLockNoWait = false) const override;`
- L82 _public prototype_ `virtual bool UnlockThreadMutex(const ETextureShareThreadMutex InThreadMutex) const override;`
- L85 _protected prototype_ `TSharedPtr<FTextureShareCoreInterprocessMutex, ESPMode::ThreadSafe> GetThreadMutex(const ETextureShareThreadMutex InThreadMutex) const;`
- L87 _protected prototype_ `void InitializeThreadMutexes();`
- L88 _protected prototype_ `void ReleaseThreadMutexes();`
- L91 _private member_ `TArray<TSharedPtr<FTextureShareCoreInterprocessMutex, ESPMode::ThreadSafe>> ThreadMutexes;`
- L96 _public prototype_ `virtual bool BeginFrameSync() override;`
- L97 _public prototype_ `virtual bool FrameSync(const ETextureShareSyncStep InSyncStep) override;`
- L98 _public prototype_ `virtual bool EndFrameSync() override;`
- L100 _public prototype_ `virtual bool BeginFrameSync_RenderThread() override;`
- L101 _public prototype_ `virtual bool FrameSync_RenderThread(const ETextureShareSyncStep InSyncStep) override;`
- L102 _public prototype_ `virtual bool EndFrameSync_RenderThread() override;`
- L104 _public prototype_ `virtual bool FindSkippedSyncStep(const ETextureShareSyncStep InSyncStep, ETextureShareSyncStep& OutSkippedSyncStep) override;`
- L105 _public prototype_ `virtual bool FindSkippedSyncStep_RenderThread(const ETextureShareSyncStep InSyncStep, ETextureShareSyncStep& OutSkippedSyncStep) override;`
- L107 _public prototype_ `virtual TArraySerializable<FTextureShareCoreObjectDesc> GetConnectedInterprocessObjects() const override;`
- L110 _protected prototype_ `bool FindSkippedSyncStepImpl(const ETextureShareSyncStep InSyncStep, bool bIsProxyFrame, ETextureShareSyncStep& OutSkippedSyncStep);`
- L111 _protected prototype_ `void ReleaseSyncData();`
- L117 _private member_ `TArraySerializable<FTextureShareCoreObjectDesc> FrameConnectionsMT;` — When the frame starts, a list of processes connected to the frame is created. New processes connected later inside this framelock will be ignored. (MultiThread access data)
- L120 _private member_ `bool bIsFrameConnectionTimeoutReached = false;` — Prevend double check for begion connection timeout
- L122 _private member_ `ETextureShareCoreInterprocessObjectFrameSyncState FrameSyncState = ETextureShareCoreInterprocessObjectFrameSyncState::Undefined;`
- L123 _private member_ `ETextureShareSyncStep CurrentSyncStep = ETextureShareSyncStep::Undefined;`
- L126 _private member_ `TSharedPtr<FEvent, ESPMode::ThreadSafe> NotificationEvent;` — Local process notification event
- L129 _private member_ `TMap<FGuid, TSharedPtr<FEvent, ESPMode::ThreadSafe>> CachedNotificationEvents;` — Opened events for remote processes
- L132 _protected prototype_ `bool TryFrameProcessesConnection(FTextureShareCoreInterprocessMemory& InterprocessMemory, FTextureShareCoreInterprocessObject& LocalObject);`
- L133 _protected prototype_ `bool ConnectFrameProcesses();`
- L134 _protected prototype_ `bool DisconnectFrameProcesses();`
- L137 _protected prototype_ `const TArraySerializable<FTextureShareCoreObjectDesc> GetFrameConnections() const;` — Return FrameConnectionsMT.
- L140 _protected prototype_ `bool IsEmptyFrameConnections() const;` — Return true is FrameConnectionsMT is empty.
- L143 _protected prototype_ `void ResetFrameConnections();` — Reset FrameConnectionsMT array.
- L146 _protected prototype_ `void SetFrameConnections(const TArraySerializable<FTextureShareCoreObjectDesc>& InNewFrameConnections);` — Set FrameConnectionsMT array.
- L149 _protected prototype_ `void UpdateFrameConnections(FTextureShareCoreInterprocessMemory& InterprocessMemory);` — Update frame connections data from the IPC memory.
- L152 _protected prototype_ `int32 FindFrameConnections(FTextureShareCoreInterprocessMemory& InterprocessMemory, FTextureShareCoreInterprocessObject& LocalObject);` — Search for a frame connections.
- L154 _protected prototype_ `bool DoFrameSync(const ETextureShareSyncStep InSyncStep);`
- L155 _protected prototype_ `bool DoFrameSync_RenderThread(const ETextureShareSyncStep InSyncStep);`
- L158 _protected prototype_ `bool BeginSyncBarrier(FTextureShareCoreInterprocessMemory& InterprocessMemory, FTextureShareCoreInterprocessObject& LocalObject, const ETextureShareSyncStep InSyncStep, const ETextureShareSyncPass InSyncPass);` — Barrier
- L159 _protected prototype_ `bool AcceptSyncBarrier(FTextureShareCoreInterprocessMemory& InterprocessMemory, FTextureShareCoreInterprocessObject& LocalObject, const ETextureShareSyncStep InSyncStep, const ETextureShareSyncPass InSyncPass);`
- L161 _protected prototype_ `bool PrepareSyncBarrierPass(const ETextureShareSyncStep InSyncStep);`
- L162 _protected prototype_ `bool PrepareSyncBarrierPass_RenderThread(const ETextureShareSyncStep InSyncStep);`
- L164 _protected prototype_ `bool TryEnterSyncBarrier(const ETextureShareSyncStep InSyncStep) const;`
- L165 _protected prototype_ `bool TryFrameProcessesBarrier(FTextureShareCoreInterprocessMemory& InterprocessMemory, FTextureShareCoreInterprocessObject& LocalObject, const ETextureShareSyncStep InSyncStep, const ETextureShareSyncPass InSyncPass);`
- L168 _protected prototype_ `bool SyncBarrierPass(const ETextureShareSyncStep InSyncStep, const ETextureShareSyncPass InSyncPass);` — Wait until all connected processes entered to desired sync step
- L169 _protected prototype_ `bool SyncBarrierPass_RenderThread(const ETextureShareSyncStep InSyncStep, const ETextureShareSyncPass InSyncPass);`
- L171 _protected prototype_ `bool SyncBarrierPassImpl(FTextureShareCoreInterprocessMemory& InterprocessMemory, FTextureShareCoreInterprocessObject& LocalObject, const ETextureShareSyncStep InSyncStep, const ETextureShareSyncPass InSyncPass);`
- L173 _protected prototype_ `void SetCurrentSyncStep(const ETextureShareSyncStep InSyncStep);`
- L174 _protected prototype_ `void SetFrameSyncState(const ETextureShareCoreInterprocessObjectFrameSyncState InFrameSyncState);`
- L176 _protected prototype_ `ETextureShareSyncStep FindNextSyncStep(const ETextureShareSyncStep InSyncStep) const;`
- L178 _protected prototype_ `void UpdateLastAccessTime() const;`
- L180 _protected prototype_ `bool TryWaitFrameProcesses(const uint32 InRemainMaxMillisecondsToWait);`
- L181 _protected prototype_ `void SendNotificationEvents(const bool bInterprocessMemoryLockRequired);`
- L183 _protected prototype_ `void HandleResetSync(FTextureShareCoreInterprocessMemory& InterprocessMemory, FTextureShareCoreInterprocessObject& LocalObject);`
- L184 _protected prototype_ `void HandleFrameLost(FTextureShareCoreInterprocessMemory& InterprocessMemory, FTextureShareCoreInterprocessObject& LocalObject);`
- L185 _protected prototype_ `void HandleFrameSkip(FTextureShareCoreInterprocessMemory& InterprocessMemory, FTextureShareCoreInterprocessObject& LocalObject);`
- L190 _public prototype_ `virtual FTextureShareCoreData& GetData() override;`
- L191 _public prototype_ `virtual FTextureShareCoreProxyData& GetProxyData_RenderThread() override;`
- L193 _public prototype_ `virtual TArraySerializable<FTextureShareCoreObjectData> GetReceivedData() const override;`
- L194 _public prototype_ `virtual TArraySerializable<FTextureShareCoreObjectProxyData> GetReceivedProxyData_RenderThread() const override;`
- L197 _protected prototype_ `void ReleaseData();`
- L201 _private member_ `FTextureShareCoreData Data;` — Local process data
- L202 _private member_ `FTextureShareCoreProxyData ProxyData;`
- L205 _private member_ `TArraySerializable<FTextureShareCoreObjectData> ReceivedObjectsData;` — Local copy of transfered resources and data
- L206 _private member_ `TArraySerializable<FTextureShareCoreObjectProxyData> ReceivedObjectsProxyData;`
- L211 _public prototype_ `virtual bool RemoveObject() override;`
- L215 _protected prototype_ `bool SendFrameData();` — Data
- L216 _protected prototype_ `bool ReceiveFrameData();`
- L218 _protected prototype_ `bool SendFrameProxyData_RenderThread();`
- L219 _protected prototype_ `bool ReceiveFrameProxyData_RenderThread();`
- L222 _private member_ `FTextureShareCore& Owner;`

### `Plugins/VirtualProduction/TextureShare/Source/TextureShareCore/Private/Object/TextureShareCoreObjectContainers.h` (Private)


#### struct `FTextureShareCoreObjectTimeout`  
`struct FTextureShareCoreObjectTimeout`  
_L10-64_
- desc: Timer for synchronization
- L12 _public function_ `FTextureShareCoreObjectTimeout(const uint32 InMaxMillisecondsToWait, const uint32 InMaxRemainMillisecondsToWait) : InitCycles64(FTextureShareCoreTime::Cycles64()) , MaxCycles64ToWait(FTextureShareCoreTime::MilisecondsToCycles64(InMaxMillisecondsToWait)) , MaxMillisecondsToWait(InMaxMillisecondsToWait) , MaxRemainMillisecondsToWait(InMaxRemainMillisecondsToWait)`
- L19 _public function_ `uint64 GetLastCycles64() const`
- L24 _public function_ `bool IsTimeOut() const`
- L35 _public function_ `uint32 GetRemainMaxMillisecondsToWait() const`
- L60 _private member_ `const uint64 InitCycles64;`
- L61 _private member_ `const uint64 MaxCycles64ToWait;`
- L62 _private member_ `const uint32 MaxMillisecondsToWait;`
- L63 _private member_ `const uint32 MaxRemainMillisecondsToWait;`

### `Plugins/VirtualProduction/TextureShare/Source/TextureShareCore/Private/Serialize/ITextureShareSerialize.h` (Private)


#### struct `ITextureShareSerialize`  
`struct ITextureShareSerialize`  
_L24-28_
- desc: Serialize structures data to exchange between processes
- L26 _public prototype_ `virtual ~ITextureShareSerialize() = default;`
- L27 _public prototype_ `virtual ITextureShareSerializeStream& Serialize(ITextureShareSerializeStream& Stream) = 0;`

#### class `ITextureShareSerializeStream`  
`class ITextureShareSerializeStream`  
_L33-105_
- desc: Interface for binary serialization
- L36 _public prototype_ `virtual ~ITextureShareSerializeStream() = default;`
- L40 _public prototype_ `virtual ITextureShareSerializeStream& operator<<(ITextureShareSerialize& InOutData) = 0;` — Serialize any serializable objects
- L44 _public prototype_ `virtual ITextureShareSerializeStream& operator<<(int8& In) = 0;` — Serialize atomic types:
- L45 _public prototype_ `virtual ITextureShareSerializeStream& operator<<(int16& In) = 0;`
- L46 _public prototype_ `virtual ITextureShareSerializeStream& operator<<(int32& In) = 0;`
- L47 _public prototype_ `virtual ITextureShareSerializeStream& operator<<(int64& In) = 0;`
- L49 _public prototype_ `virtual ITextureShareSerializeStream& operator<<(uint8& In) = 0;`
- L50 _public prototype_ `virtual ITextureShareSerializeStream& operator<<(uint16& In) = 0;`
- L51 _public prototype_ `virtual ITextureShareSerializeStream& operator<<(uint32& In) = 0;`
- L52 _public prototype_ `virtual ITextureShareSerializeStream& operator<<(uint64& In) = 0;`
- L54 _public prototype_ `virtual ITextureShareSerializeStream& operator<<(float& In) = 0;`
- L55 _public prototype_ `virtual ITextureShareSerializeStream& operator<<(double& In) = 0;`
- L56 _public prototype_ `virtual ITextureShareSerializeStream& operator<<(bool& In) = 0;`
- L60 _public prototype_ `virtual ITextureShareSerializeStream& operator<<(ETextureShareFrameSyncTemplate& In) = 0;` — Serialize TextureShare enums:
- L61 _public prototype_ `virtual ITextureShareSerializeStream& operator<<(ETextureShareSyncPass& In) = 0;`
- L62 _public prototype_ `virtual ITextureShareSerializeStream& operator<<(ETextureShareSyncState& In) = 0;`
- L64 _public prototype_ `virtual ITextureShareSerializeStream& operator<<(ETextureShareSyncStep& In) = 0;`
- L65 _public prototype_ `virtual ITextureShareSerializeStream& operator<<(ETextureShareResourceType& In) = 0;`
- L67 _public prototype_ `virtual ITextureShareSerializeStream& operator<<(ETextureShareTextureOp& In) = 0;`
- L68 _public prototype_ `virtual ITextureShareSerializeStream& operator<<(ETextureShareEyeType& In) = 0;`
- L69 _public prototype_ `virtual ITextureShareSerializeStream& operator<<(ETextureShareProcessType& In) = 0;`
- L70 _public prototype_ `virtual ITextureShareSerializeStream& operator<<(ETextureShareDeviceType& In) = 0;`
- L72 _public prototype_ `virtual ITextureShareSerializeStream& operator<<(ETextureShareCoreSceneViewManualProjectionType& In) = 0;`
- L73 _public prototype_ `virtual ITextureShareSerializeStream& operator<<(ETextureShareViewRotationDataType& In) = 0;`
- L74 _public prototype_ `virtual ITextureShareSerializeStream& operator<<(ETextureShareViewLocationDataType& In) = 0;`
- L78 _public prototype_ `virtual ITextureShareSerializeStream& operator<<(EPixelFormat& In) = 0;` — Serialize other enums
- L79 _public prototype_ `virtual ITextureShareSerializeStream& operator<<(DXGI_FORMAT& In) = 0;`
- L83 _public prototype_ `virtual ITextureShareSerializeStream& operator<<(FString& InOutData) = 0;` — Serialize UECore types:
- L84 _public prototype_ `virtual ITextureShareSerializeStream& operator<<(FVector& InOutData) = 0;`
- L85 _public prototype_ `virtual ITextureShareSerializeStream& operator<<(FVector2D& InOutData) = 0;`
- L86 _public prototype_ `virtual ITextureShareSerializeStream& operator<<(FRotator& InOutData) = 0;`
- L87 _public prototype_ `virtual ITextureShareSerializeStream& operator<<(FQuat& InOutData) = 0;`
- L88 _public prototype_ `virtual ITextureShareSerializeStream& operator<<(FMatrix& InOutData) = 0;`
- L89 _public prototype_ `virtual ITextureShareSerializeStream& operator<<(FIntRect& InOutData) = 0;`
- L90 _public prototype_ `virtual ITextureShareSerializeStream& operator<<(FIntPoint& InOutData) = 0;`
- L91 _public prototype_ `virtual ITextureShareSerializeStream& operator<<(FGuid& InOutData) = 0;`
- L92 _public prototype_ `virtual ITextureShareSerializeStream& operator<<(Windows::HANDLE& InOutData) = 0;`
- L95 _public prototype_ `virtual bool IsWriteStream() const = 0;`
- L96 _public function_ `virtual ITextureShareSerializeStream& SerializeData(void*, const uint32_t)`
- L101 _public function_ `virtual ITextureShareSerializeStream& SerializeData(const void*, const uint32_t)`

### `Plugins/VirtualProduction/TextureShare/Source/TextureShareCore/Private/Serialize/TextureShareCoreSerialize.h` (Private)


#### struct `TTextureShareCoreRemoveReference`  
`template <typename T> struct TTextureShareCoreRemoveReference`  
_L9-9_
- desc: TTextureShareCoreRemoveReference<type> will remove any references from a type.
- L9 _public typedef_ `template <typename T> struct TTextureShareCoreRemoveReference { typedef T Type; };` — TTextureShareCoreRemoveReference<type> will remove any references from a type.

#### struct `TTextureShareCoreRemoveReference`  
`template <typename T> struct TTextureShareCoreRemoveReference`  
_L10-10_
- desc: TTextureShareCoreRemoveReference<type> will remove any references from a type.
- L9 _public typedef_ `template <typename T> struct TTextureShareCoreRemoveReference { typedef T Type; };` — TTextureShareCoreRemoveReference<type> will remove any references from a type.

#### struct `TTextureShareCoreRemoveReference`  
`template <typename T> struct TTextureShareCoreRemoveReference`  
_L11-11_
- desc: TTextureShareCoreRemoveReference<type> will remove any references from a type.
- L9 _public typedef_ `template <typename T> struct TTextureShareCoreRemoveReference { typedef T Type; };` — TTextureShareCoreRemoveReference<type> will remove any references from a type.

#### class `TArraySerializable`  
`template<typename T> class TArraySerializable : public ITextureShareSerialize , public TArray<T>`  
_L44-233_
- inherits: `ITextureShareSerialize,TArray<T>`
- desc: Serializable array template for TextureShare
- L49 _public function_ `virtual ITextureShareSerializeStream& Serialize(ITextureShareSerializeStream& Stream) override`
- L69 _public function_ `void AppendSorted(const TArray<T>& InArrayValues)` — Append array values ordered. Value must support compare ops
- L78 _public function_ `void AddSorted(const T InValue)` — Add value ordered. Value must support compare ops
- L94 _public function_ `bool EqualsFunc(const TArray<T>& InArrayValues) const` — Returns true if two array values are equal
- L119 _public function_ `template <typename Predicate> T* FindByPredicate(Predicate Pred)` — Finds an element which matches a predicate functor. @param Pred The functor to apply to each element. true, or nullptr if none is found. @see FilterByPredicate, ContainsByPredicate
- L134 _public function_ `template <typename Predicate> const T* FindByPredicate(Predicate Pred) const`
- L155 _public function_ `template <typename Predicate> int32 IndexOfByPredicate(Predicate Pred) const` — Finds an item by predicate. @param Pred The predicate to match. @returns Index to the first matching element, or INDEX_NONE if none is found.
- L170 _public function_ `template<typename SubT> const T* FindByEqualsFunc(const SubT& InValue) const`
- L178 _public function_ `template<typename SubT> T* FindByEqualsFunc(const SubT& InValue)`
- L186 _public function_ `template<typename SubT> bool GetValuesByEqualsFunc(const SubT& InValue, TArray<T>& OutValues) const`
- L200 _public function_ `bool EmplaceValue(const T& InValue, const bool bOverrideExist = false)`
- L219 _public function_ `bool AppendValues(const TArraySerializable<T>& In, const bool bOverrideExist = false)`

#### Free symbols / members of external scopes

- L18 _function_ `template <typename T> inline T&& TextureShareCoreForward(typename TTextureShareCoreRemoveReference<T>::Type& Obj)` — Forward will cast a reference to an rvalue reference. This is UE's equivalent of std::forward.
- L24 _function_ `template <typename T> inline T&& TextureShareCoreForward(typename TTextureShareCoreRemoveReference<T>::Type&& Obj)`
- L34 _function_ `template <typename FuncType, typename... ArgTypes> inline auto TextureShareCoreInvoke(FuncType&& Func, ArgTypes&&... Args) -> decltype(TextureShareCoreForward<FuncType>(Func)(TextureShareCoreForward<ArgTypes>(Args)...))` — Invokes a callable with a set of arguments.  Allows the following: Copied from file "Templates\Invoke.h" for SDK
- L172 _function_ `return FindByPredicate([InValue](const T& DataIt) { return DataIt.EqualsFunc(InValue); });` (scope `TArraySerializable::FindByEqualsFunc`)
- L202 _function_ `if (T* ExistValue = FindByPredicate([InValue](const T& DataIt) { return DataIt.EqualsFunc(InValue); }))` (scope `TArraySerializable::EmplaceValue`)

### `Plugins/VirtualProduction/TextureShare/Source/TextureShareCore/Public/ITextureShareCore.h` (Public)


#### class `ITextureShareCore`  
`class ITextureShareCore : public IModuleInterface`  
_L11-45_
- inherits: `IModuleInterface`
- desc: Low level API for UE and SDK
- L14 _private member_ `static constexpr auto ModuleName = TEXT("Tex`
- L23 _public function_ `static inline ITextureShareCore& Get()` — Singleton-like access to this module's interface.  This is just for convenience! Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already. @return Returns singleton object, loading the module on demand if needed
- L33 _public function_ `static inline bool IsAvailable()` — Checks to see if this module is loaded and ready.  It is only valid to call Get() if IsAvailable() returns true. @return True if the module is loaded and ready to use
- L44 _public prototype_ `virtual class ITextureShareCoreAPI& GetTextureShareCoreAPI() = 0;` — Returns Core API Interface Put headers in an Internal folder. This limits visibility to other engine modules, and allows implementations to be changed in hotfixes.
