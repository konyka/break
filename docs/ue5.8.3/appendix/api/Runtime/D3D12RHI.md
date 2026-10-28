# Runtime / D3D12RHI

- module root: `Source/Runtime/D3D12RHI`
- headers: 61; symbols: 4514
- symbol kinds: class=131, delegate=103, enum=48, enumerator=210, externvar=15, function=986, macro=119, member=1287, namespace=30, prototype=1280, struct=190, typedef=84, union=6, variable=25
- PrivateDependencyModuleNames: HeadMountedDisplay
- PublicDependencyModuleNames: WinPixEventRuntime, WindowsD3D

### `Source/Runtime/D3D12RHI/Internal/D3D12RayTracingResources.h` (Internal)


#### struct `FD3D12HitGroupSystemParameters`  
`struct FD3D12HitGroupSystemParameters`  
_L18-34_
- desc: Built-in local root parameters that are always bound to all hit shaders Contains union for bindless and non-bindless index/vertex buffer data to make the code handling the hit group parameters easier to use (otherwise all cached hit parameter code has to be done twice and stored twice making everything more complicated) Ideally the non bindless code path should be removed 'soon' - this constant buffer size for FD3D12HitGroupSystemParameters in Bindless is 8 bytes bigger than needed
- L20 _public member_ `FHitGroupSystemRootConstants RootConstants;`

#### union `FD3D12HitGroupSystemParameters::(anonymous)`  
``  
_L22-33_

#### struct `FD3D12HitGroupSystemParameters::__anon159d6b08010a::(anonymous)`  
``  
_L24-27_

#### struct `FD3D12HitGroupSystemParameters::__anon159d6b08010a::(anonymous)`  
``  
_L29-32_

#### struct `FD3D12RayTracingOfflineBvhHeader`  
`struct FD3D12RayTracingOfflineBvhHeader`  
_L36-40_
- L38 _public member_ `uint32 Size = 0;`
- L39 _public member_ `uint32 SerializedSize = 0;`

#### Free symbols / members of external scopes

- L12 _typedef_ `using FD3D12_GPU_VIRTUAL_ADDRESS = uint64;`
- L25 _member_ `uint32 BindlessHitGroupSystemIndexBuffer;` (scope `FD3D12HitGroupSystemParameters::__anon159d6b08010a::__anon159d6b080208`)
- L26 _member_ `uint32 BindlessHitGroupSystemVertexBuffer;` (scope `FD3D12HitGroupSystemParameters::__anon159d6b08010a::__anon159d6b080208`)
- L30 _member_ `FD3D12_GPU_VIRTUAL_ADDRESS IndexBuffer;` (scope `FD3D12HitGroupSystemParameters::__anon159d6b08010a::__anon159d6b080308`)
- L31 _member_ `FD3D12_GPU_VIRTUAL_ADDRESS VertexBuffer;` (scope `FD3D12HitGroupSystemParameters::__anon159d6b08010a::__anon159d6b080308`)

### `Source/Runtime/D3D12RHI/Internal/D3D12ShaderUtils.h` (Internal)


#### Free symbols / members of external scopes

- L18 _prototype_ `bool BuildComputeShaderRootSignature( const TConstArrayView<uint8>& ShaderCode, D3D12_RESOURCE_BINDING_TIER ResourceBindingTier, TRefCountPtr<ID3DBlob>& OutRootSigBlob, int32& OutNativeBytecodeOffset);` — Build a serialized root signature for a compute shader from its UE shader blob. Uses the same root signature construction logic as RHICreateComputeShader. @param ShaderCode            Full UE shader blob (SRT + native bytecode + optional data) @param ResourceBindingTier   Resource binding tier to use for the root signature layout @param OutRootSigBlob        Receives the serialized root signature blob @param OutNativeBytecodeOffset  Receives the offset to native DXBC/DXIL bytecode within ShaderCode @return true on success
- L35 _prototype_ `bool BuildGraphicsShaderRootSignature( const TConstArrayView<TConstArrayView<uint8>> ShaderBlobs, D3D12_RESOURCE_BINDING_TIER ResourceBindingTier, TRefCountPtr<ID3DBlob>& OutRootSigBlob);` — Build a serialized root signature for a graphics PSO from multiple UE shader blobs. Merges FShaderCodePackedResourceCounts across all active shader stages to produce a single root signature that covers the union of resources required by all stages. @param ShaderBlobs           Array of full UE shader blobs, one per active stage (SRT + native bytecode + optional data). Null/empty entries are skipped. @param ResourceBindingTier   Resource binding tier to use for the root signature layout @param OutRootSigBlob        Receives the serialized root signature blob @return true on success

### `Source/Runtime/D3D12RHI/Private/D3D12Access.h` (Private)


#### enum `ED3D12Access`  
`enum class ED3D12Access : D3D12AccessUnderlyingType`  
_L14-56_
- L16 _public enumerator_ `Unknown = static_cast<D3D12AccessUnderlyingType>(ERHIAccess::Unknown)`
- L17 _public enumerator_ `CPURead = static_cast<D3D12AccessUnderlyingType>(ERHIAccess::CPURead)`
- L18 _public enumerator_ `Present = static_cast<D3D12AccessUnderlyingType>(ERHIAccess::Present)`
- L19 _public enumerator_ `IndirectArgs = static_cast<D3D12AccessUnderlyingType>(ERHIAccess::IndirectArgs)`
- L20 _public enumerator_ `VertexOrIndexBuffer = static_cast<D3D12AccessUnderlyingType>(ERHIAccess::VertexOrIndexBuffer)`
- L21 _public enumerator_ `SRVCompute = static_cast<D3D12AccessUnderlyingType>(ERHIAccess::SRVCompute)`
- L22 _public enumerator_ `SRVGraphicsPixel = static_cast<D3D12AccessUnderlyingType>(ERHIAccess::SRVGraphicsPixel)`
- L23 _public enumerator_ `SRVGraphicsNonPixel = static_cast<D3D12AccessUnderlyingType>(ERHIAccess::SRVGraphicsNonPixel)`
- L24 _public enumerator_ `CopySrc = static_cast<D3D12AccessUnderlyingType>(ERHIAccess::CopySrc)`
- L25 _public enumerator_ `ResolveSrc = static_cast<D3D12AccessUnderlyingType>(ERHIAccess::ResolveSrc)`
- L26 _public enumerator_ `DSVRead = static_cast<D3D12AccessUnderlyingType>(ERHIAccess::DSVRead)`
- L27 _public enumerator_ `UAVCompute = static_cast<D3D12AccessUnderlyingType>(ERHIAccess::UAVCompute)`
- L28 _public enumerator_ `UAVGraphics = static_cast<D3D12AccessUnderlyingType>(ERHIAccess::UAVGraphics)`
- L29 _public enumerator_ `RTV = static_cast<D3D12AccessUnderlyingType>(ERHIAccess::RTV)`
- L30 _public enumerator_ `CopyDest = static_cast<D3D12AccessUnderlyingType>(ERHIAccess::CopyDest)`
- L31 _public enumerator_ `ResolveDst = static_cast<D3D12AccessUnderlyingType>(ERHIAccess::ResolveDst)`
- L32 _public enumerator_ `DSVWrite = static_cast<D3D12AccessUnderlyingType>(ERHIAccess::DSVWrite)`
- L33 _public enumerator_ `BVHRead = static_cast<D3D12AccessUnderlyingType>(ERHIAccess::BVHRead)`
- L34 _public enumerator_ `BVHWrite = static_cast<D3D12AccessUnderlyingType>(ERHIAccess::BVHWrite)`
- L35 _public enumerator_ `Discard = static_cast<D3D12AccessUnderlyingType>(ERHIAccess::Discard)`
- L36 _public enumerator_ `ShadingRateSource = static_cast<D3D12AccessUnderlyingType>(ERHIAccess::ShadingRateSource)`
- L37 _public enumerator_ `RHIAccessLast = ShadingRateSource`
- L40 _public enumerator_ `Common = RHIAccessLast << 1` — D3D12 specific extensions
- L41 _public enumerator_ `GenericRead = RHIAccessLast << 2`
- L42 _public enumerator_ `Last = GenericRead`
- L44 _public enumerator_ `Mask = (Last << 1) - 1`
- L46 _public enumerator_ `SRVGraphics = static_cast<D3D12AccessUnderlyingType>(ERHIAccess::SRVGraphics)`
- L47 _public enumerator_ `SRVMask = static_cast<D3D12AccessUnderlyingType>(ERHIAccess::SRVMask)`
- L48 _public enumerator_ `UAVMask = static_cast<D3D12AccessUnderlyingType>(ERHIAccess::UAVMask)`
- L49 _public enumerator_ `ReadOnlyExclusiveMask = (static_cast<D3D12AccessUnderlyingType>(ERHIAccess::ReadOnlyExclusiveMask) | GenericRead) & ~BVHRead`
- L50 _public enumerator_ `ReadOnlyExclusiveComputeMask = static_cast<D3D12AccessUnderlyingType>(ERHIAccess::ReadOnlyExclusiveComputeMask) | GenericRead`
- L51 _public enumerator_ `ReadOnlyMask = static_cast<D3D12AccessUnderlyingType>(ERHIAccess::ReadOnlyMask)`
- L52 _public enumerator_ `ReadableMask = static_cast<D3D12AccessUnderlyingType>(ERHIAccess::ReadableMask) | BVHRead`
- L53 _public enumerator_ `WriteOnlyExclusiveMask = static_cast<D3D12AccessUnderlyingType>(ERHIAccess::WriteOnlyExclusiveMask)`
- L54 _public enumerator_ `WriteOnlyMask = static_cast<D3D12AccessUnderlyingType>(ERHIAccess::WriteOnlyMask)`
- L55 _public enumerator_ `WritableMask = static_cast<D3D12AccessUnderlyingType>(ERHIAccess::WritableMask)`

#### Free symbols / members of external scopes

- L12 _typedef_ `using D3D12AccessUnderlyingType = std::underlying_type_t<ERHIAccess>;`
- L62 _prototype_ `ENUM_CLASS_FLAGS(ED3D12Access);`
- L64 _function_ `constexpr ED3D12Access ConvertToD3D12Access(ERHIAccess InRHIAccess)`
- L69 _function_ `constexpr bool IsInvalidAccess(ED3D12Access InD3D12Access)`
- L78 _function_ `constexpr bool IsValidAccess(ED3D12Access InD3D12Access)`

### `Source/Runtime/D3D12RHI/Private/D3D12Adapter.h` (Private)


#### struct `FD3D12DeviceBasicInfo`  
`struct FD3D12DeviceBasicInfo`  
_L46-60_
- L48 _public member_ `D3D_FEATURE_LEVEL MaxFeatureLevel;`
- L49 _public member_ `D3D_SHADER_MODEL MaxShaderModel;`
- L50 _public member_ `D3D12_RESOURCE_BINDING_TIER ResourceBindingTier;`
- L51 _public member_ `D3D12_RESOURCE_HEAP_TIER ResourceHeapTier;`
- L52 _public member_ `uint32 NumDeviceNodes;`
- L53 _public member_ `bool bSupportsWaveOps;`
- L54 _public member_ `bool bSupportsAtomic64;`
- L55 _public member_ `bool bTileBasedRenderer;`
- L56 _public member_ `bool bUMA;`
- L57 _public member_ `bool bCacheCoherentUMA;`
- L58 _public member_ `bool bSupportsGPUUploadHeaps;`
- L59 _public member_ `ERHIFeatureLevel::Type MaxRHIFeatureLevel;`

#### struct `FD3D12AdapterDesc`  
`struct FD3D12AdapterDesc`  
_L62-115_
- L64 _public prototype_ `FD3D12AdapterDesc();`
- L65 _public prototype_ `FD3D12AdapterDesc(const DXGI_ADAPTER_DESC& InDesc, int32 InAdapterIndex, const FD3D12DeviceBasicInfo& DeviceInfo);`
- L67 _public prototype_ `bool IsValid() const;`
- L70 _public prototype_ `static HRESULT EnumAdapters(int32 AdapterIndex, DXGI_GPU_PREFERENCE GpuPreference, IDXGIFactory2* DxgiFactory2, IDXGIFactory6* DxgiFactory6, IDXGIAdapter** TempAdapter);`
- L71 _public prototype_ `HRESULT EnumAdapters(IDXGIFactory2* DxgiFactory2, IDXGIFactory6* DxgiFactory6, IDXGIAdapter** TempAdapter) const;`
- L74 _public member_ `DXGI_ADAPTER_DESC Desc{};`
- L77 _public member_ `int32 AdapterIndex = -1;` — -1 if not supported or FindAdapter() wasn't called. Ideally we would store a pointer to IDXGIAdapter but it's unlikely the adpaters change during engine init.
- L80 _public member_ `D3D_FEATURE_LEVEL MaxSupportedFeatureLevel = (D3D_FEATURE_LEVEL)0;` — The maximum D3D12 feature level supported. 0 if not supported or FindAdapter() wasn't called
- L83 _public member_ `D3D_SHADER_MODEL MaxSupportedShaderModel = (D3D_SHADER_MODEL)0;` — The maximum Shader Model supported. 0 if not supported or FindAdpater() wasn't called
- L85 _public member_ `D3D12_RESOURCE_BINDING_TIER ResourceBindingTier = D3D12_RESOURCE_BINDING_TIER_1;`
- L87 _public member_ `D3D12_RESOURCE_HEAP_TIER ResourceHeapTier = D3D12_RESOURCE_HEAP_TIER_1;`
- L89 _public member_ `ERHIFeatureLevel::Type MaxRHIFeatureLevel = ERHIFeatureLevel::Num;`
- L92 _public member_ `uint32 NumDeviceNodes = 1;` — Number of device nodes (read: GPUs)
- L95 _public member_ `bool bTileBasedRenderer = false;` — Whether the GPU is tile-based.
- L98 _public member_ `bool bUMA = false;` — Whether the GPU has unified memory. This can be used to identify integrated GPU as well.
- L101 _public member_ `bool bCacheCoherentUMA = false;` — Whether the UMA device has cache coherency between the GPU and CPU.
- L104 _public member_ `bool bSupportsGPUUploadHeaps = false;` — Whether the device supports GPU Upload Heaps
- L107 _public member_ `bool bSupportsWaveOps = false;` — Whether SM6.0 wave ops are supported
- L110 _public member_ `bool bSupportsAtomic64 = false;` — Whether SM6.6 atomic64 wave ops are supported
- L113 _public member_ `DXGI_GPU_PREFERENCE GpuPreference = DXGI_GPU_PREFERENCE_UNSPECIFIED;`

#### struct `FD3D12MemoryInfo`  
`struct FD3D12MemoryInfo`  
_L117-131_
- L119 _public member_ `DXGI_QUERY_VIDEO_MEMORY_INFO LocalMemoryInfo{};`
- L120 _public member_ `DXGI_QUERY_VIDEO_MEMORY_INFO NonLocalMemoryInfo{};`
- L122 _public member_ `uint32 UpdateFrameNumber = ~uint32(0);`
- L124 _public member_ `uint64 AvailableLocalMemory = 0;`
- L125 _public member_ `uint64 DemotedLocalMemory = 0;`
- L127 _public function_ `bool IsOverBudget() const`

#### class `FTransientUniformBufferAllocator`  
`class FTransientUniformBufferAllocator : public FD3D12FastConstantAllocator, public TThreadSingleton<FTransientUniformBufferAllocator>`  
_L133-142_
- inherits: `FD3D12FastConstantAllocator,TThreadSingleton<FTransientUniformBufferAllocator>`
- L136 _public function_ `FTransientUniformBufferAllocator(FD3D12Adapter* InAdapter, FD3D12Device* Parent, FRHIGPUMask VisibiltyMask) : FD3D12FastConstantAllocator(Parent, VisibiltyMask), Adapter(InAdapter)`
- L137 _public prototype_ `~FTransientUniformBufferAllocator();`
- L139 _public prototype_ `void Cleanup();`
- L141 _private member_ `FD3D12Adapter* Adapter = nullptr;`

#### class `FD3D12Adapter`  
`class FD3D12Adapter : public FNoncopyable`  
_L147-697_
- inherits: `FNoncopyable`
- desc: Represents a set of linked D3D12 device nodes (LDA i.e 1 or more identical GPUs). In most cases there will be only 1 node, however if the system supports SLI/Crossfire and the app enables it an Adapter will have 2 or more nodes. This class will own anything that can be shared across LDA including: System Pool Memory,.Pipeline State Objects, Root Signatures etc.
- L151 _public prototype_ `FD3D12Adapter(FD3D12AdapterDesc& DescIn);`
- L152 _public prototype_ `virtual ~FD3D12Adapter();`
- L154 _public prototype_ `void CleanupResources();`
- L156 _public prototype_ `void InitializeDevices();`
- L157 _public prototype_ `void InitializeExplicitDescriptorHeap();`
- L158 _public prototype_ `void InitializeRayTracing();`
- L161 _public function_ `FORCEINLINE const uint32 GetAdapterIndex() const` — Getters
- L162 _public function_ `FORCEINLINE const D3D_FEATURE_LEVEL GetFeatureLevel() const`
- L163 _public function_ `FORCEINLINE D3D_SHADER_MODEL GetHighestShaderModel() const`
- L165 _public function_ `FORCEINLINE ID3D12Device* GetD3DDevice() const`
- L167 _public function_ `FORCEINLINE ID3D12Device1* GetD3DDevice1() const`
- L170 _public function_ `FORCEINLINE ID3D12Device2* GetD3DDevice2() const`
- L173 _public function_ `FORCEINLINE ID3D12Device3* GetD3DDevice3() const`
- L176 _public function_ `FORCEINLINE ID3D12Device4* GetD3DDevice4() const`
- L179 _public function_ `FORCEINLINE ID3D12Device5* GetD3DDevice5()`
- L182 _public function_ `FORCEINLINE ID3D12Device6* GetD3DDevice6()`
- L185 _public function_ `FORCEINLINE ID3D12Device7* GetD3DDevice7()`
- L188 _public function_ `FORCEINLINE ID3D12Device8* GetD3DDevice8()`
- L191 _public function_ `FORCEINLINE ID3D12Device9* GetD3DDevice9()`
- L194 _public function_ `FORCEINLINE ID3D12Device10* GetD3DDevice10()`
- L197 _public function_ `FORCEINLINE ID3D12Device11* GetD3DDevice11()`
- L200 _public function_ `FORCEINLINE ID3D12Device12* GetD3DDevice12()`
- L203 _public function_ `FORCEINLINE IDXGIFactory2* GetDXGIFactory2() const`
- L205 _public function_ `FORCEINLINE IDXGIFactory3* GetDXGIFactory3() const`
- L208 _public function_ `FORCEINLINE IDXGIFactory4* GetDXGIFactory4() const`
- L211 _public function_ `FORCEINLINE IDXGIFactory5* GetDXGIFactory5() const`
- L214 _public function_ `FORCEINLINE IDXGIFactory6* GetDXGIFactory6() const`
- L217 _public function_ `FORCEINLINE IDXGIFactory7* GetDXGIFactory7() const`
- L220 _public function_ `FORCEINLINE const bool IsDebugDevice() const`
- L222 _public function_ `FORCEINLINE const D3D12_RESOURCE_HEAP_TIER GetResourceHeapTier () const`
- L223 _public function_ `FORCEINLINE const D3D12_RESOURCE_BINDING_TIER GetResourceBindingTier () const`
- L224 _public function_ `FORCEINLINE const D3D_ROOT_SIGNATURE_VERSION GetRootSignatureVersion () const`
- L226 _public function_ `FORCEINLINE const bool IsDepthBoundsTestSupported() const`
- L227 _public function_ `FORCEINLINE const bool IsHeapNotZeroedSupported () const`
- L228 _public function_ `FORCEINLINE const bool IsHeapCreateNotResidentSupported() const`
- L230 _public function_ `FORCEINLINE const bool AreCopyQueueTimestampQueriesSupported() const`
- L232 _public function_ `FORCEINLINE const DXGI_ADAPTER_DESC& GetD3DAdapterDesc() const`
- L233 _public function_ `FORCEINLINE IDXGIAdapter* GetAdapter()`
- L235 _public function_ `FORCEINLINE const FD3D12AdapterDesc& GetDesc() const`
- L237 _public function_ `FORCEINLINE TArray<FD3D12Viewport*>& GetViewports()`
- L239 _public function_ `FORCEINLINE int32 GetMaxDescriptorsForHeapType(ERHIDescriptorHeapType InHeapType)`
- L241 _public function_ `FORCEINLINE ID3D12CommandSignature* GetDrawIndirectCommandSignature ()`
- L242 _public function_ `FORCEINLINE ID3D12CommandSignature* GetDrawIndexedIndirectCommandSignature ()`
- L243 _public function_ `FORCEINLINE ID3D12CommandSignature* GetDispatchIndirectGraphicsCommandSignature()`
- L244 _public function_ `FORCEINLINE ID3D12CommandSignature* GetDispatchIndirectComputeCommandSignature ()`
- L246 _public function_ `FORCEINLINE ID3D12CommandSignature* GetDispatchIndirectMeshCommandSignature()`
- L248 _public function_ `FORCEINLINE ID3D12CommandSignature* GetDispatchRaysIndirectCommandSignature()`
- L250 _public function_ `FORCEINLINE FD3D12PipelineStateCache& GetPSOCache()`
- L252 _public prototype_ `const FD3D12RootSignature* GetRootSignature(const FBoundShaderStateInput& BoundShaderState);`
- L253 _public prototype_ `const FD3D12RootSignature* GetRootSignature(const class FD3D12ComputeShader* Shader);`
- L254 _public prototype_ `const FD3D12RootSignature* GetRootSignature(ERHIShaderBundleMode ShaderBundleMode, bool bBindless);`
- L256 _public prototype_ `const FD3D12RootSignature* GetRootSignature(const class FD3D12WorkGraphShader* Shader);`
- L257 _public prototype_ `const FD3D12RootSignature* GetGlobalWorkGraphRootSignature(const FRHIShaderBindingLayout& ShaderBindingLayout);`
- L258 _public prototype_ `const FD3D12RootSignature* GetWorkGraphGraphicsRootSignature(const FBoundShaderStateInput& BoundShaderState);`
- L260 _public prototype_ `const FD3D12RootSignature* GetLocalRootSignature(const class FD3D12RayTracingShader* Shader);`
- L261 _public prototype_ `const FD3D12RootSignature* GetGlobalRayTracingRootSignature(const FRHIShaderBindingLayout& ShaderBindingLayout);`
- L263 _public function_ `FORCEINLINE FD3D12RootSignatureManager* GetRootSignatureManager()`
- L268 _public function_ `FORCEINLINE FD3D12ManualFence& GetFrameFence()`
- L270 _public function_ `FORCEINLINE FD3D12Device* GetDevice(uint32 GPUIndex) const`
- L276 _public function_ `TConstArrayView<FD3D12Device*> GetDevices() const`
- L281 _public function_ `FORCEINLINE uint32 GetVRSTileSize() const`
- L283 _public prototype_ `void CreateDXGIFactory(bool bWithDebug);`
- L284 _public prototype_ `static void CreateDXGIFactory(TRefCountPtr<IDXGIFactory2>& DxgiFactory2, bool bWithDebug);`
- L285 _public prototype_ `void InitDXGIFactoryVariants(IDXGIFactory2* InDxgiFactory2);`
- L286 _public prototype_ `HRESULT EnumAdapters(IDXGIAdapter** TempAdapter) const;`
- L288 _public function_ `FORCEINLINE FD3D12UploadHeapAllocator& GetUploadHeapAllocator(uint32 GPUIndex)`
- L293 _public function_ `FORCEINLINE uint32 GetDebugFlags() const`
- L295 _public prototype_ `void EndFrame();`
- L298 _public function_ `HRESULT CreateCommittedResource(const FD3D12ResourceDesc& InDesc, FRHIGPUMask CreationNode, const D3D12_HEAP_PROPERTIES& HeapProps, ED3D12Access InInitialD3D12Access, const D3D12_CLEAR_VALUE* ClearValue, FD3D12Resource** ppOutResource, const TCHAR* Name, bool bVerifyHResult = true)` — Resource Creation
- L320 _public prototype_ `HRESULT CreateCommittedResource(const FD3D12ResourceDesc& Desc, FRHIGPUMask CreationNode, const D3D12_HEAP_PROPERTIES& HeapProps, ED3D12Access InInitialD3D12Access, ED3D12ResourceStateMode InResourceStateMode, ED3D12Access InDefaultD3D12Access, const D3D12_CLEAR_VALUE* ClearValue, FD3D12Resource** ppOutResource, const TCHAR* Name, bool bVerifyHResult = true);`
- L331 _public function_ `HRESULT CreateCommittedResourceRaw( const D3D12_HEAP_PROPERTIES& InHeapProps, D3D12_HEAP_FLAGS InHeapFlags, const FD3D12ResourceDesc& InDesc, ED3D12Access InInitialD3D12Access, const D3D12_CLEAR_VALUE* InClearValue, TRefCountPtr<ID3D12Resource>& OutResource)`
- L349 _public function_ `HRESULT CreatePlacedResource(const FD3D12ResourceDesc& InDesc, FD3D12Heap* BackingHeap, uint64 HeapOffset, ED3D12Access InInitialD3D12Access, const D3D12_CLEAR_VALUE* ClearValue, FD3D12Resource** ppOutResource, const TCHAR* Name, bool bVerifyHResult = true)`
- L371 _public prototype_ `HRESULT CreatePlacedResource(const FD3D12ResourceDesc& Desc, FD3D12Heap* BackingHeap, uint64 HeapOffset, ED3D12Access InInitialD3D12Access, ED3D12ResourceStateMode InResourceStateMode, ED3D12Access InDefaultD3D12Access, const D3D12_CLEAR_VALUE* ClearValue, FD3D12Resource** ppOutResource, const TCHAR* Name, bool bVerifyHResult = true);`
- L382 _public prototype_ `HRESULT CreateReservedResource(const FD3D12ResourceDesc& Desc, FRHIGPUMask CreationNode, ED3D12Access InInitialD3D12Access, ED3D12ResourceStateMode InResourceStateMode, ED3D12Access InDefaultD3D12Access, const D3D12_CLEAR_VALUE* ClearValue, FD3D12Resource** ppOutResource, const TCHAR* Name, bool bVerifyHResult = true);`
- L392 _public prototype_ `HRESULT CreateBuffer(D3D12_HEAP_TYPE HeapType, FRHIGPUMask CreationNode, FRHIGPUMask VisibleNodes, uint64 HeapSize, FD3D12Resource** ppOutResource, const TCHAR* Name, D3D12_RESOURCE_FLAGS Flags = D3D12_RESOURCE_FLAG_NONE);`
- L400 _public prototype_ `HRESULT CreateBuffer(D3D12_HEAP_TYPE HeapType, FRHIGPUMask CreationNode, FRHIGPUMask VisibleNodes, ED3D12Access InInitialD3D12Access, ED3D12ResourceStateMode InResourceStateMode, ED3D12Access InDefaultD3D12Access, uint64 HeapSize, FD3D12Resource** ppOutResource, const TCHAR* Name, D3D12_RESOURCE_FLAGS Flags = D3D12_RESOURCE_FLAG_NONE);`
- L411 _public prototype_ `HRESULT CreateBuffer(const D3D12_HEAP_PROPERTIES& HeapProps, FRHIGPUMask CreationNode, ED3D12Access InInitialD3D12Access, ED3D12ResourceStateMode InResourceStateMode, ED3D12Access InDefaultD3D12Access, uint64 HeapSize, FD3D12Resource** ppOutResource, const TCHAR* Name, D3D12_RESOURCE_FLAGS Flags = D3D12_RESOURCE_FLAG_NONE);`
- L421 _public prototype_ `FD3D12Buffer* CreateRHIBuffer( const D3D12_RESOURCE_DESC& Desc, uint32 Alignment, const FRHIBufferCreateDesc& CreateDesc, ED3D12ResourceStateMode InResourceStateMode, ED3D12Access InCreateD3D12Access, bool bKeepUnlocked = false, ID3D12ResourceAllocator* ResourceAllocator = nullptr );`
- L432 _public prototype_ `void CreateUAVAliasResourceDesc(const FD3D12ResourceLocation& Location);`
- L436 _public function_ `template <typename ObjectType, typename CreationCoreFunction> inline ObjectType* CreateLinkedObject(FRHIGPUMask GPUMask, const CreationCoreFunction& pfnCreationCore)`
- L445 _public function_ `inline FD3D12CommandContextRedirector& GetDefaultContextRedirector()`
- L447 _public prototype_ `FD3D12TransientHeapCache& GetOrCreateTransientHeapCache();`
- L449 _public prototype_ `FD3D12FastConstantAllocator& GetTransientUniformBufferAllocator();`
- L450 _public prototype_ `void ReleaseTransientUniformBufferAllocator(FTransientUniformBufferAllocator* InAllocator);`
- L452 _public prototype_ `void BlockUntilIdle();`
- L454 _public prototype_ `const FRHIMemoryStats& CollectMemoryStats();`
- L455 _public function_ `FORCEINLINE const FRHIMemoryStats& GetMemoryStats() const`
- L456 _public function_ `FORCEINLINE uint64 GetMemoryStatsUpdateFrame() const`
- L458 _public function_ `bool IsTrackingAllAllocations() const`
- L459 _public prototype_ `void TrackAllocationData(FD3D12ResourceLocation* InAllocation, uint64 InAllocationSize, bool bCollectCallstack);`
- L460 _public prototype_ `void ReleaseTrackedAllocationData(FD3D12ResourceLocation* InAllocation, bool bDefragFree);`
- L461 _public prototype_ `void TrackHeapAllocation(FD3D12Heap* InHeap);`
- L462 _public prototype_ `void ReleaseTrackedHeap(FD3D12Heap* InHeap);`
- L463 _public prototype_ `void DumpTrackedAllocationData(FOutputDevice& OutputDevice, bool bResidentOnly, bool bWithCallstack);`
- L470 _public prototype_ `void FindResourcesNearGPUAddress(D3D12_GPU_VIRTUAL_ADDRESS InGPUVirtualAddress, uint64 InRange, TArray<FAllocatedResourceResult>& OutResources);`
- L471 _public prototype_ `void FindHeapsContainingGPUAddress(D3D12_GPU_VIRTUAL_ADDRESS InGPUVirtualAddress, TArray<FD3D12Heap*>& OutHeaps);`
- L485 _public prototype_ `void FindReleasedAllocationData(D3D12_GPU_VIRTUAL_ADDRESS InGPUVirtualAddress, TArray<FReleasedAllocationData>& OutAllocationData);`
- L498 _public prototype_ `void SetResidencyPriority(ID3D12Pageable* Pageable, D3D12_RESIDENCY_PRIORITY HeapPriority, uint32 GPUIndex, TOptional<uint64> ResourceSize = {});` — Controls the heuristics used by Windows Video Memory Manager to demote resources from GPU physical memory when it is overcommitted or fragmented. The D3D12 RHI performs access tracking and manual residency management, however it is still possible to overcommit under some conditions on low-VRAM GPUs. Render targets, depth buffers and UAVs are assigned high residency priority by default. To differentiate between high priority resources, the size is packed into low 16 bits of the priority value (in units of 10MB). If ResourceSize parameter is specified, the final priority value will be packed in a mannner consistent with the default priority assignment. Current priority value is stored in the Pageable private data. The size bits will be preserved if priority changes but the size is not provided in subsequent calls to this function. See https://learn.microsoft.com/en-us/windows/win32/direct3d12/residency.
- L502 _public function_ `FD3D12BindlessDescriptorAllocator& GetBindlessDescriptorAllocator()`
- L505 _public prototype_ `void CreateTransition( FRHITransition* Transition, const FRHITransitionCreateInfo& CreateInfo);`
- L508 _public prototype_ `void ReleaseTransition(FRHITransition* Transition);`
- L511 _public prototype_ `static TUniquePtr<FD3D12BarriersFactory::BarriersForContextType> CreateBarriersForContext();`
- L515 _protected prototype_ `virtual void CreateRootDevice(bool bWithDebug);`
- L517 _protected prototype_ `void CreateD3DInfoQueue();`
- L519 _protected prototype_ `virtual void AllocateBuffer(FD3D12Device* Device, const D3D12_RESOURCE_DESC& Desc, uint32 Size, EBufferUsageFlags InUsage, ED3D12ResourceStateMode InResourceStateMode, ED3D12Access InCreatED3D12Access, uint32 Alignment, FD3D12Buffer* Buffer, FD3D12ResourceLocation& ResourceLocation, ID3D12ResourceAllocator* ResourceAllocator, const TCHAR* InDebugName, const FName& OwnerName);`
- L532 _protected member_ `static ED3D12BarrierImplementationType PreferredBarrierImplType;`
- L533 _protected member_ `static TUniquePtr<const FD3D12BarriersFactory::BarriersForAdapterType> Barriers;`
- L536 _protected prototype_ `virtual void CreateCommandSignatures();` — Creates default root and execute indirect signatures
- L539 _protected member_ `TRefCountPtr<ID3D12Device> RootDevice;` — LDA setups have one ID3D12Device
- L541 _protected member_ `TRefCountPtr<ID3D12Device1> RootDevice1;`
- L544 _protected member_ `TRefCountPtr<ID3D12Device2> RootDevice2;`
- L547 _protected member_ `TRefCountPtr<ID3D12Device3> RootDevice3;`
- L550 _protected member_ `TRefCountPtr<ID3D12Device4> RootDevice4;`
- L553 _protected member_ `TRefCountPtr<ID3D12Device5> RootDevice5;`
- L556 _protected member_ `TRefCountPtr<ID3D12Device6> RootDevice6;`
- L559 _protected member_ `TRefCountPtr<ID3D12Device7> RootDevice7;`
- L562 _protected member_ `TRefCountPtr<ID3D12Device8> RootDevice8;`
- L565 _protected member_ `TRefCountPtr<ID3D12Device9> RootDevice9;`
- L568 _protected member_ `TRefCountPtr<ID3D12Device10> RootDevice10;`
- L571 _protected member_ `TRefCountPtr<ID3D12Device11> RootDevice11;`
- L574 _protected member_ `TRefCountPtr<ID3D12Device12> RootDevice12;`
- L577 _protected member_ `TRefCountPtr<IDXGIFactory2> DxgiFactory2;`
- L579 _protected member_ `TRefCountPtr<IDXGIFactory3> DxgiFactory3;`
- L582 _protected member_ `TRefCountPtr<IDXGIFactory4> DxgiFactory4;`
- L585 _protected member_ `TRefCountPtr<IDXGIFactory5> DxgiFactory5;`
- L588 _protected member_ `TRefCountPtr<IDXGIFactory6> DxgiFactory6;`
- L591 _protected member_ `TRefCountPtr<IDXGIFactory7> DxgiFactory7;`
- L595 _protected member_ `HMODULE DxgiDebugDllHandle{};`
- L596 _protected member_ `TRefCountPtr<IDXGIDebug> DXGIDebug;`
- L597 _protected member_ `HANDLE ExceptionHandlerHandle = INVALID_HANDLE_VALUE;`
- L600 _protected member_ `D3D_ROOT_SIGNATURE_VERSION RootSignatureVersion;`
- L601 _protected member_ `bool bDepthBoundsTestSupported = false;`
- L602 _protected member_ `bool bCopyQueueTimestampQueriesSupported = false;`
- L603 _protected member_ `bool bHeapNotZeroedSupported = false;`
- L604 _protected member_ `bool bHeapCreateNotResidentSupported = false;`
- L606 _protected member_ `int32 MaxNonSamplerDescriptors = 0;`
- L607 _protected member_ `int32 MaxSamplerDescriptors = 0;`
- L609 _protected member_ `uint32 VRSTileSize = 0;`
- L612 _protected member_ `bool bDebugDevice = false;` — Running with debug device
- L614 _protected member_ `FD3D12AdapterDesc Desc;`
- L616 _protected member_ `TRefCountPtr<IDXGIAdapter> DxgiAdapter;`
- L618 _protected member_ `FD3D12RootSignatureManager RootSignatureManager;`
- L620 _protected member_ `FD3D12PipelineStateCache PipelineStateCache;`
- L622 _protected member_ `TRefCountPtr<ID3D12CommandSignature> DrawIndirectCommandSignature;`
- L623 _protected member_ `TRefCountPtr<ID3D12CommandSignature> DrawIndexedIndirectCommandSignature;`
- L624 _protected member_ `TRefCountPtr<ID3D12CommandSignature> DispatchIndirectGraphicsCommandSignature;`
- L625 _protected member_ `TRefCountPtr<ID3D12CommandSignature> DispatchIndirectComputeCommandSignature;`
- L627 _protected member_ `TRefCountPtr<ID3D12CommandSignature> DispatchIndirectMeshCommandSignature;`
- L629 _protected member_ `TRefCountPtr<ID3D12CommandSignature> DispatchRaysIndirectCommandSignature;`
- L631 _protected member_ `FD3D12UploadHeapAllocator* UploadHeapAllocator[MAX_NUM_GPUS];`
- L634 _protected member_ `TArray<FD3D12Viewport*> Viewports;` — A list of all viewport RHIs that have been created.
- L637 _protected member_ `TUniquePtr<FD3D12ManualFence> FrameFence;` — A Fence whose value increases every frame
- L639 _protected member_ `FD3D12CommandContextRedirector DefaultContextRedirector;`
- L641 _protected member_ `bool bTrackAllAllocation = false;`
- L655 _protected member_ `TMap<FD3D12ResourceLocation*, FTrackedAllocationData> TrackedAllocationData;` — Tracked resource information.
- L656 _protected member_ `TArray<FD3D12Heap*> TrackedHeaps;`
- L657 _protected member_ `TArray<FReleasedAllocationData> ReleasedAllocationData;`
- L658 _protected member_ `FCriticalSection TrackedAllocationDataCS;`
- L660 _protected member_ `FRHIMemoryStats MemoryStats;`
- L661 _protected member_ `uint64 MemoryStatsUpdateFrame;`
- L663 _protected member_ `TArray<FTransientUniformBufferAllocator*> TransientUniformBufferAllocators;`
- L664 _protected member_ `FCriticalSection TransientUniformBufferAllocatorsCS;`
- L666 _protected member_ `TUniquePtr<IRHITransientMemoryCache> TransientMemoryCache;`
- L669 _protected member_ `TStaticArray<FD3D12Device*, MAX_NUM_GPUS> Devices;` — Each of these devices represents a physical GPU 'Node'
- L671 _protected member_ `uint32 DebugFlags = 0;`
- L674 _protected member_ `FD3D12RootSignature StaticGraphicsRootSignature;`
- L675 _protected member_ `FD3D12RootSignature StaticGraphicsWithConstantsRootSignature;`
- L676 _protected member_ `FD3D12RootSignature StaticComputeRootSignature;`
- L677 _protected member_ `FD3D12RootSignature StaticComputeWithConstantsRootSignature;`
- L680 _protected member_ `FD3D12RootSignature StaticBindlessGraphicsRootSignature;`
- L681 _protected member_ `FD3D12RootSignature StaticBindlessGraphicsWithConstantsRootSignature;`
- L682 _protected member_ `FD3D12RootSignature StaticBindlessComputeRootSignature;`
- L683 _protected member_ `FD3D12RootSignature StaticBindlessComputeWithConstantsRootSignature;`
- L686 _protected member_ `FD3D12RootSignature StaticRayTracingGlobalRootSignature;`
- L687 _protected member_ `FD3D12RootSignature StaticRayTracingLocalRootSignature;`
- L691 _protected member_ `FD3D12BindlessDescriptorAllocator BindlessDescriptorAllocator;`
- L696 _private prototype_ `void TraceMemoryAllocation(FD3D12Resource* Resource);` — Insight memory trace helper

#### struct `FD3D12Adapter::FAllocatedResourceResult`  
`struct FAllocatedResourceResult`  
_L465-469_
- L467 _public member_ `FD3D12ResourceLocation* Allocation = nullptr;`
- L468 _public member_ `uint64 Distance = 0;`

#### struct `FD3D12Adapter::FReleasedAllocationData`  
`struct FReleasedAllocationData`  
_L473-484_
- L475 _public member_ `D3D12_GPU_VIRTUAL_ADDRESS GPUVirtualAddress = 0;`
- L476 _public member_ `uint64 AllocationSize = 0;`
- L477 _public member_ `FName ResourceName;`
- L478 _public member_ `D3D12_RESOURCE_DESC ResourceDesc = {};`
- L479 _public member_ `uint64 ReleasedFrameID = 0;`
- L480 _public member_ `bool bDefragFree = false;`
- L481 _public member_ `bool bBackBuffer = false;`
- L482 _public member_ `bool bTransient = false;`
- L483 _public member_ `bool bHeap = false;`

#### struct `FD3D12Adapter::FTrackedAllocationData`  
`struct FTrackedAllocationData`  
_L644-652_
- desc: Information about an allocated resource.
- L646 _public member_ `static const int32 MaxStackDepth = 30;`
- L648 _public member_ `FD3D12ResourceLocation* ResourceAllocation;`
- L649 _public member_ `uint64 AllocationSize;`
- L650 _public member_ `uint32 StackDepth;`
- L651 _public member_ `uint64 Stack[MaxStackDepth];`

#### Free symbols / members of external scopes

- L440 _function_ `GPUMask, [this](uint32 GPUIndex)` (scope `FD3D12Adapter::CreateLinkedObject`)

### `Source/Runtime/D3D12RHI/Private/D3D12Allocation.h` (Private)


#### class `FD3D12ResourceAllocator`  
`class FD3D12ResourceAllocator : public FD3D12DeviceChild, public FD3D12MultiNodeGPUObject`  
_L27-60_
- inherits: `FD3D12DeviceChild,FD3D12MultiNodeGPUObject`
- L31 _public prototype_ `FD3D12ResourceAllocator(FD3D12Device* ParentDevice, FRHIGPUMask VisibleNodes, const FD3D12ResourceInitConfig& InInitConfig, const FString& Name, uint32 MaxSizeForPooling);`
- L36 _public prototype_ `~FD3D12ResourceAllocator();`
- L38 _public function_ `const FD3D12ResourceInitConfig& GetInitConfig() const`
- L39 _public function_ `const uint32 GetMaximumAllocationSizeForPooling() const`
- L43 _protected member_ `const FD3D12ResourceInitConfig InitConfig;`
- L44 _protected member_ `const FString DebugName;`
- L45 _protected member_ `bool Initialized;`
- L49 _protected member_ `const uint32 MaximumAllocationSizeForPooling;` — Any allocation larger than this just gets straight up allocated (i.e. not pooled). These large allocations should be infrequent so the CPU overhead should be minimal
- L51 _protected member_ `FCriticalSection CS;`
- L54 _protected member_ `uint32 SpaceAlignedUsed;`
- L55 _protected member_ `uint32 SpaceActualUsed;`
- L56 _protected member_ `uint32 NumBlocksInDeferredDeletionQueue;`
- L57 _protected member_ `uint32 PeakUsage;`
- L58 _protected member_ `uint32 FailedAllocationSpace;`

#### class `FD3D12BuddyAllocator`  
`class FD3D12BuddyAllocator : public FD3D12ResourceAllocator`  
_L85-188_
- inherits: `FD3D12ResourceAllocator`
- L89 _public prototype_ `FD3D12BuddyAllocator(FD3D12Device* ParentDevice, FRHIGPUMask VisibleNodes, const FD3D12ResourceInitConfig& InInitConfig, const FString& Name, EResourceAllocationStrategy InAllocationStrategy, uint32 MaxSizeForPooling, uint32 InMaxBlockSize, uint32 InMinBlockSize, HeapId InTraceParentHeapId);`
- L99 _public prototype_ `bool TryAllocate(uint32 SizeInBytes, uint32 Alignment, FD3D12ResourceLocation& ResourceLocation);`
- L101 _public prototype_ `void Deallocate(FD3D12ResourceLocation& ResourceLocation);`
- L103 _public prototype_ `void Initialize();`
- L105 _public prototype_ `void Destroy();`
- L107 _public prototype_ `void CleanUpAllocations();`
- L109 _public prototype_ `void DumpAllocatorStats(class FOutputDevice& Ar);`
- L110 _public prototype_ `void UpdateMemoryStats(uint32& IOMemoryAllocated, uint32& IOMemoryUsed, uint32& IOMemoryFree, uint32& IOAlignmentWaste, uint32& IOAllocatedPageCount, uint32& IOFullPageCount);`
- L112 _public prototype_ `void ReleaseAllResources();`
- L114 _public prototype_ `void Reset();`
- L116 _public function_ `inline bool IsEmpty()`
- L120 _public function_ `inline uint64 GetLastUsedFrameFence() const`
- L122 _public function_ `inline uint32 GetTotalSizeUsed() const`
- L123 _public function_ `inline uint64 GetAllocationOffsetInBytes(const FD3D12BuddyAllocatorPrivateData& AllocatorPrivateData) const`
- L125 _public function_ `inline FD3D12Heap* GetBackingHeap()`
- L127 _public function_ `inline bool IsOwner(FD3D12ResourceLocation& ResourceLocation)`
- L134 _protected member_ `const uint32 MaxBlockSize;`
- L135 _protected member_ `const uint32 MinBlockSize;`
- L136 _protected member_ `const EResourceAllocationStrategy AllocationStrategy;`
- L138 _protected member_ `TRefCountPtr<FD3D12Resource> BackingResource;`
- L139 _protected member_ `TRefCountPtr<FD3D12Heap> BackingHeap;`
- L153 _private member_ `TArray<RetiredBlock> DeferredDeletionQueue;`
- L154 _private member_ `TArray<TSet<uint32>> FreeBlocks;`
- L155 _private member_ `uint64 LastUsedFrameFence;`
- L156 _private member_ `uint32 MaxOrder;`
- L157 _private member_ `uint32 TotalSizeUsed;`
- L158 _private member_ `HeapId TraceHeapId;`
- L160 _private member_ `bool HeapFullMessageDisplayed;`
- L162 _private function_ `inline uint32 SizeToUnitSize(uint32 size) const`
- L167 _private function_ `inline uint32 UnitSizeToOrder(uint32 size) const`
- L174 _private function_ `inline uint32 GetBuddyOffset(const uint32 &offset, const uint32 &size)`
- L179 _private function_ `uint32 OrderToUnitSize(uint32 order) const`
- L180 _private prototype_ `uint32 AllocateBlock(uint32 order);`
- L181 _private prototype_ `void DeallocateBlock(uint32 offset, uint32 order);`
- L183 _private prototype_ `bool CanAllocate(uint32 size, uint32 alignment);`
- L185 _private prototype_ `void DeallocateInternal(RetiredBlock& Block);`
- L187 _private prototype_ `void Allocate(uint32 SizeInBytes, uint32 Alignment, FD3D12ResourceLocation& ResourceLocation);`

#### struct `FD3D12BuddyAllocator::RetiredBlock`  
`struct RetiredBlock`  
_L142-151_
- L144 _public member_ `FD3D12Resource* PlacedResource;`
- L145 _public member_ `uint64 FrameFence;`
- L146 _public member_ `FD3D12BuddyAllocatorPrivateData Data;`
- L149 _public member_ `uint32 AllocationSize;` — Actual size only used for tracking memory stats

#### class `FD3D12MultiBuddyAllocator`  
`class FD3D12MultiBuddyAllocator : public FD3D12ResourceAllocator`  
_L197-251_
- inherits: `FD3D12ResourceAllocator`
- L201 _public prototype_ `FD3D12MultiBuddyAllocator(FD3D12Device* ParentDevice, FRHIGPUMask VisibleNodes, const FD3D12ResourceInitConfig& InInitConfig, const FString& Name, EResourceAllocationStrategy InAllocationStrategy, uint32 InMaxAllocationSize, uint32 InDefaultPoolSize, uint32 InMinBlockSize, HeapId InTraceParentHeapId, ERHIPoolAllocationStrategy InPoolAllocationStrategy, uint16 InOverFlowPoolsCount);`
- L212 _public prototype_ `~FD3D12MultiBuddyAllocator();`
- L214 _public function_ `const EResourceAllocationStrategy GetAllocationStrategy() const`
- L216 _public prototype_ `bool TryAllocate(uint32 SizeInBytes, uint32 Alignment, FD3D12ResourceLocation& ResourceLocation);`
- L218 _public prototype_ `void Deallocate(FD3D12ResourceLocation& ResourceLocation);`
- L220 _public prototype_ `void Initialize();`
- L222 _public prototype_ `void Destroy();`
- L224 _public prototype_ `void CleanUpAllocations(uint64 InFrameLag);`
- L226 _public prototype_ `void DumpAllocatorStats(class FOutputDevice& Ar);`
- L227 _public prototype_ `void UpdateMemoryStats(uint32& IOMemoryAllocated, uint32& IOMemoryUsed, uint32& IOMemoryFree, uint32& IOAlignmentWaste, uint32& IOAllocatedPageCount, uint32& IOFullPageCount);`
- L229 _public prototype_ `void ReleaseAllResources();`
- L231 _public prototype_ `void Reset();`
- L234 _protected prototype_ `FD3D12BuddyAllocator* CreateNewAllocator(uint32 InMinSizeInBytes);`
- L235 _protected prototype_ `void NewAllocatorAsyncAllocate();`
- L238 _protected member_ `const EResourceAllocationStrategy AllocationStrategy;`
- L239 _protected member_ `const uint32 MinBlockSize;`
- L240 _protected member_ `const uint32 DefaultPoolSize;`
- L242 _protected member_ `TArray<FD3D12BuddyAllocator*> Allocators;`
- L245 _private member_ `HeapId TraceHeapId;`
- L247 _private member_ `TArray<FD3D12BuddyAllocator*> OverFlowAllocators;`
- L248 _private member_ `ERHIPoolAllocationStrategy PoolAllocationStrategy = ERHIPoolAllocationStrategy::Immediate;`
- L249 _private member_ `ERHIPoolAllocationStatus PoolAllocationStatus = ERHIPoolAllocationStatus::Idle;`
- L250 _private member_ `int16 OverFlowPoolsCount = 1;`

#### class `FD3D12UploadHeapAllocator`  
`class FD3D12UploadHeapAllocator : public FD3D12AdapterChild, public FD3D12DeviceChild, public FD3D12MultiNodeGPUObject`  
_L258-284_
- inherits: `FD3D12AdapterChild,FD3D12DeviceChild,FD3D12MultiNodeGPUObject`
- desc: This is designed for allocation of scratch memory such as temporary staging buffers or shadow buffers for dynamic resources.
- L262 _public prototype_ `FD3D12UploadHeapAllocator(FD3D12Adapter* InParent, FD3D12Device* InParentDevice, const FString& InName);`
- L264 _public prototype_ `void Init();`
- L265 _public prototype_ `void Destroy();`
- L268 _public prototype_ `void* AllocUploadResource(uint32 InSize, uint32 InAlignment, FD3D12ResourceLocation& ResourceLocation);` — Allocates <size> bytes from the end of an available resource heap.
- L269 _public prototype_ `void* AllocFastConstantAllocationPage(uint32 InSize, uint32 InAlignment, FD3D12ResourceLocation& ResourceLocation);`
- L271 _public prototype_ `void CleanUpAllocations(uint64 InFrameLag);`
- L272 _public prototype_ `void UpdateMemoryStats();`
- L275 _private member_ `HeapId TraceHeapId;`
- L277 _private member_ `FD3D12MultiBuddyAllocator SmallBlockAllocator;` — Buddy allocator used for all 'small' allocation - fast but aligns to power of 2
- L279 _private member_ `FCriticalSection BigBlockCS;` — Pool allocator for all bigger allocations - less fast but less alignment waste
- L280 _private member_ `FD3D12PoolAllocator BigBlockAllocator;`
- L283 _private member_ `FD3D12MultiBuddyAllocator FastConstantPageAllocator;` — Separate buddy allocator used for the fast constant allocator pages which get always freed within the same frame by default (different allocator to avoid fragmentation with the other pools - always the same size allocations)

#### class `FD3D12DefaultBufferPool`  
`class FD3D12DefaultBufferPool : public FD3D12DeviceChild, public FD3D12MultiNodeGPUObject`  
_L289-313_
- inherits: `FD3D12DeviceChild,FD3D12MultiNodeGPUObject`
- L292 _public prototype_ `FD3D12DefaultBufferPool(FD3D12Device* InParent, FD3D12MultiBuddyAllocator* InAllocator);`
- L293 _public function_ `~FD3D12DefaultBufferPool()`
- L295 _public prototype_ `bool SupportsAllocation(D3D12_HEAP_TYPE InHeapType, D3D12_RESOURCE_FLAGS InResourceFlags, EBufferUsageFlags InBufferUsage, ED3D12ResourceStateMode InResourceStateMode, uint32 Alignment) const;`
- L296 _public prototype_ `void AllocDefaultResource( D3D12_HEAP_TYPE InHeapType, const D3D12_RESOURCE_DESC& InDesc, EBufferUsageFlags InBufferUsage, ED3D12ResourceStateMode InResourceStateMode, ED3D12Access InCreateD3D12Access, uint32 InAlignment, const TCHAR* InName, FD3D12ResourceLocation& ResourceLocation);`
- L305 _public prototype_ `void CleanUpAllocations(uint64 InFrameLag);`
- L306 _public prototype_ `void UpdateMemoryStats(uint32& IOMemoryAllocated, uint32& IOMemoryUsed, uint32& IOMemoryFree, uint32& IOMemoryEndFree, uint32& IOAlignmentWaste, uint32& IOAllocatedPageCount, uint32& IOFullPageCount);`
- L308 _public prototype_ `static FD3D12ResourceInitConfig GetResourceAllocatorInitConfig(D3D12_HEAP_TYPE InHeapType, D3D12_RESOURCE_FLAGS InResourceFlags, EBufferUsageFlags InBufferUsage);`
- L309 _public prototype_ `static EResourceAllocationStrategy GetResourceAllocationStrategy(D3D12_RESOURCE_FLAGS InResourceFlags, ED3D12ResourceStateMode InResourceStateMode, uint32 Alignment);`
- L312 _private member_ `FD3D12MultiBuddyAllocator* Allocator;`

#### class `FD3D12DefaultBufferAllocator`  
`class FD3D12DefaultBufferAllocator : public FD3D12DeviceChild, public FD3D12MultiNodeGPUObject`  
_L323-354_
- inherits: `FD3D12DeviceChild,FD3D12MultiNodeGPUObject`
- desc: FD3D12DefaultBufferAllocator
- L326 _public prototype_ `FD3D12DefaultBufferAllocator(FD3D12Device* InParent, FRHIGPUMask VisibleNodes);`
- L329 _public prototype_ `void AllocDefaultResource( D3D12_HEAP_TYPE InHeapType, const D3D12_RESOURCE_DESC& pDesc, EBufferUsageFlags InBufferUsage, ED3D12ResourceStateMode InResourceStateMode, ED3D12Access InCreateD3D12Access, FD3D12ResourceLocation& ResourceLocation, uint32 Alignment, const TCHAR* Name);` — Grab a buffer from the available buffers or create a new buffer if none are available
- L339 _public prototype_ `void FreeDefaultBufferPools();`
- L340 _public prototype_ `void BeginFrame(FD3D12ContextArray const& Contexts);`
- L341 _public prototype_ `void CleanupFreeBlocks(uint64 InFrameLag);`
- L342 _public prototype_ `void UpdateMemoryStats();`
- L344 _public prototype_ `static bool IsPlacedResource(D3D12_RESOURCE_FLAGS InResourceFlags, ED3D12ResourceStateMode InResourceStateMode, uint32 Alignment);`
- L345 _public prototype_ `static ED3D12Access GetDefaultInitialD3D12Access(D3D12_HEAP_TYPE InHeapType, EBufferUsageFlags InBufferFlags, ED3D12ResourceStateMode InResourceStateMode);`
- L349 _private prototype_ `FD3D12BufferPool* CreateBufferPool(D3D12_HEAP_TYPE InHeapType, D3D12_RESOURCE_FLAGS InResourceFlags, EBufferUsageFlags InBufferUsage, ED3D12ResourceStateMode InResourceStateMode, uint32 Alignment);`
- L351 _private member_ `TArray<FD3D12BufferPool*> DefaultBufferPools;`
- L352 _private member_ `FCriticalSection CS;`
- L353 _private member_ `HeapId TraceHeapId;`

#### struct `FD3D12FastAllocatorPage`  
`struct FD3D12FastAllocatorPage`  
_L360-389_
- L362 _public function_ `FD3D12FastAllocatorPage() : PageSize(0) , NextFastAllocOffset(0) , FastAllocData(nullptr) , FrameFence(0)`
- L368 _public function_ `FD3D12FastAllocatorPage(uint32 Size) : PageSize(Size) , NextFastAllocOffset(0) , FastAllocData(nullptr) , FrameFence(0)`
- L374 _public prototype_ `~FD3D12FastAllocatorPage();`
- L376 _public function_ `void Reset()`
- L382 _public prototype_ `void UpdateFence();`
- L384 _public member_ `const uint32 PageSize;`
- L385 _public member_ `TRefCountPtr<FD3D12Resource> FastAllocBuffer;`
- L386 _public member_ `uint32 NextFastAllocOffset;`
- L387 _public member_ `void* FastAllocData;`
- L388 _public member_ `uint64 FrameFence;`

#### class `FD3D12FastAllocatorPagePool`  
`class FD3D12FastAllocatorPagePool : public FD3D12DeviceChild, public FD3D12MultiNodeGPUObject`  
_L391-415_
- inherits: `FD3D12DeviceChild,FD3D12MultiNodeGPUObject`
- L394 _public prototype_ `FD3D12FastAllocatorPagePool(FD3D12Device* Parent, FRHIGPUMask VisibiltyMask, D3D12_HEAP_TYPE InHeapType, uint32 Size);`
- L396 _public prototype_ `FD3D12FastAllocatorPagePool(FD3D12Device* Parent, FRHIGPUMask VisibiltyMask, const D3D12_HEAP_PROPERTIES& InHeapProperties, uint32 Size);`
- L398 _public prototype_ `FD3D12FastAllocatorPage* RequestFastAllocatorPage();`
- L399 _public prototype_ `void ReturnFastAllocatorPage(FD3D12FastAllocatorPage* Page);`
- L400 _public prototype_ `void CleanupPages(uint64 FrameLag);`
- L402 _public function_ `inline uint32 GetPageSize() const`
- L404 _public function_ `inline D3D12_HEAP_TYPE GetHeapType() const`
- L405 _public function_ `inline bool IsCPUWritable() const`
- L407 _public prototype_ `void Destroy();`
- L411 _protected member_ `const uint32 PageSize;`
- L412 _protected member_ `const D3D12_HEAP_PROPERTIES HeapProperties;`
- L414 _protected member_ `TArray<FD3D12FastAllocatorPage*> Pool;`

#### class `FD3D12FastAllocator`  
`class FD3D12FastAllocator : public FD3D12DeviceChild, public FD3D12MultiNodeGPUObject`  
_L417-434_
- inherits: `FD3D12DeviceChild,FD3D12MultiNodeGPUObject`
- L420 _public prototype_ `FD3D12FastAllocator(FD3D12Device* Parent, FRHIGPUMask VisibiltyMask, D3D12_HEAP_TYPE InHeapType, uint32 PageSize);`
- L421 _public prototype_ `FD3D12FastAllocator(FD3D12Device* Parent, FRHIGPUMask VisibiltyMask, const D3D12_HEAP_PROPERTIES& InHeapProperties, uint32 PageSize);`
- L423 _public prototype_ `void* Allocate(uint32 Size, uint32 Alignment, class FD3D12ResourceLocation* ResourceLocation);`
- L424 _public prototype_ `void Destroy();`
- L426 _public prototype_ `void CleanupPages(uint64 FrameLag);`
- L429 _protected member_ `FD3D12FastAllocatorPagePool PagePool;`
- L431 _protected member_ `FD3D12FastAllocatorPage* CurrentAllocatorPage;`
- L433 _protected member_ `FCriticalSection CS;`

#### class `FD3D12FastConstantAllocator`  
`class FD3D12FastConstantAllocator : public FD3D12DeviceChild, public FD3D12MultiNodeGPUObject`  
_L436-449_
- inherits: `FD3D12DeviceChild,FD3D12MultiNodeGPUObject`
- L439 _public prototype_ `FD3D12FastConstantAllocator(FD3D12Device* Parent, FRHIGPUMask VisibiltyMask);`
- L441 _public prototype_ `void* Allocate(uint32 Bytes, class FD3D12ResourceLocation& OutLocation, FD3D12ConstantBufferView* OutCBView);`
- L442 _public function_ `void ClearResource()`
- L445 _private member_ `FD3D12ResourceLocation UnderlyingResource;`
- L447 _private member_ `uint32 Offset;`
- L448 _private member_ `uint32 PageSize;`

#### class `FD3D12TextureAllocatorPool`  
`class FD3D12TextureAllocatorPool : public FD3D12DeviceChild, public FD3D12MultiNodeGPUObject`  
_L456-488_
- inherits: `FD3D12DeviceChild,FD3D12MultiNodeGPUObject`
- L459 _public prototype_ `FD3D12TextureAllocatorPool(FD3D12Device* Device, FRHIGPUMask VisibilityNode);`
- L461 _public prototype_ `HRESULT AllocateTexture( FD3D12ResourceDesc Desc, const D3D12_CLEAR_VALUE* ClearValue, EPixelFormat UEFormat, FD3D12ResourceLocation& TextureLocation, ED3D12Access InInitialD3D12Access, ED3D12Access InDefaultD3D12Access, const TCHAR* Name);`
- L470 _public prototype_ `void BeginFrame(FD3D12ContextArray const& Contexts);`
- L471 _public prototype_ `void CleanUpAllocations();`
- L472 _public prototype_ `void Destroy();`
- L473 _public prototype_ `bool GetMemoryStats(uint64& OutTotalAllocated, uint64& OutTotalUnused) const;`
- L486 _private member_ `FD3D12PoolAllocator* PoolAllocators[(int)EPoolType::Count];`
- L487 _private member_ `HeapId TraceHeapId;`
- L520 _public function_ `void BeginFrame(FD3D12ContextArray const& Contexts)`
- L521 _public function_ `void CleanUpAllocations()`
- L523 _public function_ `void Destroy()`
- L524 _public function_ `bool GetMemoryStats(uint64& OutTotalAllocated, uint64& OutTotalUnused) const`
- L528 _private member_ `FD3D12TextureAllocator ReadOnlyTexturePool;`

#### enum `FD3D12TextureAllocatorPool::EPoolType`  
`enum class EPoolType`  
_L477-484_
- L479 _public enumerator_ `ReadOnly4K`
- L480 _public enumerator_ `ReadOnly`
- L481 _public enumerator_ `RenderTarget`
- L482 _public enumerator_ `UAV`
- L483 _public enumerator_ `Count`

#### class `FD3D12TextureAllocator`  
`class FD3D12TextureAllocator : public FD3D12MultiBuddyAllocator`  
_L490-504_
- inherits: `FD3D12MultiBuddyAllocator`
- L493 _public prototype_ `FD3D12TextureAllocator(FD3D12Device* Device, FRHIGPUMask VisibleNodes, const FString& Name, uint32 HeapSize, D3D12_HEAP_FLAGS Flags, HeapId InTraceParentHeapId);`
- L495 _public prototype_ `~FD3D12TextureAllocator();`
- L497 _public prototype_ `HRESULT AllocateTexture( FD3D12ResourceDesc Desc, const D3D12_CLEAR_VALUE* ClearValue, FD3D12ResourceLocation& TextureLocation, ED3D12Access InInitialD3D12Access, ED3D12Access InDefaultD3D12Access, const TCHAR* Name);`

#### class `FD3D12TextureAllocatorPool`  
`class FD3D12TextureAllocatorPool : public FD3D12DeviceChild, public FD3D12MultiNodeGPUObject`  
_L506-529_
- inherits: `FD3D12DeviceChild,FD3D12MultiNodeGPUObject`
- L459 _public prototype_ `FD3D12TextureAllocatorPool(FD3D12Device* Device, FRHIGPUMask VisibilityNode);`
- L461 _public prototype_ `HRESULT AllocateTexture( FD3D12ResourceDesc Desc, const D3D12_CLEAR_VALUE* ClearValue, EPixelFormat UEFormat, FD3D12ResourceLocation& TextureLocation, ED3D12Access InInitialD3D12Access, ED3D12Access InDefaultD3D12Access, const TCHAR* Name);`
- L470 _public prototype_ `void BeginFrame(FD3D12ContextArray const& Contexts);`
- L471 _public prototype_ `void CleanUpAllocations();`
- L472 _public prototype_ `void Destroy();`
- L473 _public prototype_ `bool GetMemoryStats(uint64& OutTotalAllocated, uint64& OutTotalUnused) const;`
- L486 _private member_ `FD3D12PoolAllocator* PoolAllocators[(int)EPoolType::Count];`
- L487 _private member_ `HeapId TraceHeapId;`
- L520 _public function_ `void BeginFrame(FD3D12ContextArray const& Contexts)`
- L521 _public function_ `void CleanUpAllocations()`
- L523 _public function_ `void Destroy()`
- L524 _public function_ `bool GetMemoryStats(uint64& OutTotalAllocated, uint64& OutTotalUnused) const`
- L528 _private member_ `FD3D12TextureAllocator ReadOnlyTexturePool;`

#### Free symbols / members of external scopes

- L23 _macro_ `#define D3D12RHI_TRACK_DETAILED_STATS (PLATFORM_WINDOWS && !(UE_BUILD_TEST || UE_BUILD_SHIPPING))`
- L25 _variable_ `const uint32 kD3D12ManualSubAllocationAlignment = 256;`
- L73 _macro_ `#define MIN_PLACED_RESOURCE_SIZE (64 * 1024)` — Unfortunately the api restricts the minimum size of a placed buffer resource to 64k
- L74 _macro_ `#define D3D_BUFFER_ALIGNMENT (64 * 1024)`
- L77 _macro_ `#define INCREASE_ALLOC_COUNTER(A, B) (A = A + B);`
- L78 _macro_ `#define DECREASE_ALLOC_COUNTER(A, B) (A = A - B);`
- L80 _macro_ `#define INCREASE_ALLOC_COUNTER(A, B)`
- L81 _macro_ `#define DECREASE_ALLOC_COUNTER(A, B)`
- L316 _typedef_ `typedef FD3D12PoolAllocator FD3D12BufferPool;`
- L318 _typedef_ `typedef FD3D12DefaultBufferPool FD3D12BufferPool;`

### `Source/Runtime/D3D12RHI/Private/D3D12AmdExtensions.h` (Private)
_(no declarations extracted)_

### `Source/Runtime/D3D12RHI/Private/D3D12BarriersFactory.h` (Private)


#### enum `ED3D12BarrierImplementationType`  
`enum class ED3D12BarrierImplementationType`  
_L11-16_
- L13 _public enumerator_ `Legacy`
- L14 _public enumerator_ `Enhanced`
- L15 _public enumerator_ `Invalid`

#### struct `TD3D12BarriersFactoryEntry`  
`struct TD3D12BarriersFactoryEntry`  
_L41-46_
- L43 _public member_ `static constexpr ED3D12BarrierImplementationType ImplType = InImplType;`
- L44 _public typedef_ `using AdapterImplType = TAdapterImpl;`
- L45 _public typedef_ `using ContextImplType = TContextImpl;`

#### struct `TD3D12BarriersFactoryEntry`  
`template <> struct TD3D12BarriersFactoryEntry<ED3D12BarrierImplementationType::Invalid, nullptr_t, nullptr_t>`  
_L52-52_
- desc: Don't define any of the *ImplTypes in this case since it's a terminator only and meaningless as a factory entry. If we try to use the ImplTypes, something has gone wrong anyway.
- L43 _public member_ `static constexpr ED3D12BarrierImplementationType ImplType = InImplType;`
- L44 _public typedef_ `using AdapterImplType = TAdapterImpl;`
- L45 _public typedef_ `using ContextImplType = TContextImpl;`

#### struct `TIsInstanceOfD3D12BarriersFactoryTemplate`  
`template<typename, template<auto, typename...> typename = TD3D12BarriersFactoryEntry> struct TIsInstanceOfD3D12BarriersFactoryTemplate : std::false_type`  
_L77-77_
- inherits: `std::false_type`
- desc: Check if a type is an instance of TD3D12BarriersFactoryEntry This is done by having a baseline struct template that accepts any type followed by a template-template type which we default to TD3D12BarriersFactoryEntry. This baseline produces a struct that inherits from std::false_type and is what all types that don't follow the pattern of TTemplate<auto, typename...> will match. Template types that do follow the pattern of TTemplate<auto, typename...> will match the specialization. That's good, but also means it would match anytime that takes that pattern of template parameters and specifically only want TD3D12BarriersFactoryEntry. To further refine the result, we then conditionally switch on if putting the template-template type back together with its parameters produces the same type as gluing those same parameters together with TD3D12BarriersFactoryEntry. Whether the resulting struct inherits from std::true_type or std::false_type depends on the result of that equality and ultimately answers the question of if the provided type is an instance of TD3D12BarriersFactoryEntry.

#### struct `TIsInstanceOfD3D12BarriersFactoryTemplate`  
`template<template<auto, typename...> typename TTemplate, auto InImplType, typename... TParams> struct TIsInstanceOfD3D12BarriersFactoryTemplate<TTemplate<InImplType, TParams...>, TTemplate> : std::conditional_t< std::is_same_v< TTemplate<InImplType, TParams...>, TD3D12BarriersFactoryEntry<InImplType, TParams...> >, std::true_type, std::false_type >`  
_L80-88_
- inherits: `std::conditional_t<std::is_same_v<TTemplate<InImplType,TParams...>,TD3D12BarriersFactoryEntry<InImplType,TParams...>>,std::true_type,std::false_type>`

#### class `TD3D12BarriersFactory`  
`template <CD3D12BarriersFactoryEntry... TFactoryEntries> class TD3D12BarriersFactory`  
_L129-274_
- L136 _private member_ `static constexpr uint32 MinimumFactoryEntries = 2u;` — 2 accounts for 1 entry + terminator
- L140 _public typedef_ `template <CD3D12BarriersForAdapterImpl TAdapterImpl, CD3D12BarriersForContextImpl TContextImpl> using BarrierImpl = TTuple<TAdapterImpl, TContextImpl>;`
- L142 _public typedef_ `using BarriersForAdapterType = std::conditional_t< (sizeof...(TFactoryEntries) > MinimumFactoryEntries), ID3D12BarriersForAdapter, typename TGetFirstTypeInPack<TFactoryEntries...>::Type::AdapterImplType>;`
- L148 _public typedef_ `using BarriersForContextType = std::conditional_t< (sizeof...(TFactoryEntries) > MinimumFactoryEntries), ID3D12BarriersForContext, typename TGetFirstTypeInPack<TFactoryEntries...>::Type::ContextImplType>;`
- L155 _public function_ `static BarriersForAdapterType* CreateBarriersForAdapter( ED3D12BarrierImplementationType PreferredType)`
- L162 _public function_ `static BarriersForContextType* CreateBarriersForContext( ED3D12BarrierImplementationType PreferredType)`
- L189 _private function_ `static CreateBarriersInternalReturnType<InComponentType>::Type* CreateBarriersInternal( ED3D12BarrierImplementationType PreferredType)`
- L232 _private function_ `template <typename T, typename TFirst, typename... TRest> static consteval bool CheckThatLastTypeInPackIs()`
- L245 _private function_ `template <CD3D12BarriersFactoryEntry TFirst, CD3D12BarriersFactoryEntry... TRest> static consteval bool CheckThatNoImplTypeAppearsMoreThanOnce( TStaticArray<bool, static_cast<uint32>(ED3D12BarrierImplementationType::Invalid)> SeenTypes = {})`

#### struct `TD3D12BarriersFactory::TGetFirstTypeInPack`  
`template <typename TFirst, typename...> struct TGetFirstTypeInPack`  
_L133-133_
- L133 _public typedef_ `template <typename TFirst, typename...> struct TGetFirstTypeInPack { using Type = TFirst; };`

#### enum `TD3D12BarriersFactory::EComponentType`  
`enum class EComponentType`  
_L169-173_
- L171 _public enumerator_ `Adapter`
- L172 _public enumerator_ `Context`

#### struct `TD3D12BarriersFactory::CreateBarriersInternalReturnType`  
`template <EComponentType InCompType> struct CreateBarriersInternalReturnType`  
_L178-178_
- desc: If another component type is added, add a new specialization to use the same CreateBarriersInternal function for it
- L178 _public typedef_ `template <EComponentType InCompType> struct CreateBarriersInternalReturnType { using Type = nullptr_t; };` — If another component type is added, add a new specialization to use the same CreateBarriersInternal function for it
- L180 _public typedef_ `template<> struct CreateBarriersInternalReturnType<EComponentType::Adapter> { using Type = BarriersForAdapterType; };`
- L182 _public typedef_ `template<> struct CreateBarriersInternalReturnType<EComponentType::Context> { using Type = BarriersForContextType; };`

#### struct `TD3D12BarriersFactory::CreateBarriersInternalReturnType`  
`template<> struct CreateBarriersInternalReturnType<EComponentType::Adapter>`  
_L180-180_
- L178 _public typedef_ `template <EComponentType InCompType> struct CreateBarriersInternalReturnType { using Type = nullptr_t; };` — If another component type is added, add a new specialization to use the same CreateBarriersInternal function for it
- L180 _public typedef_ `template<> struct CreateBarriersInternalReturnType<EComponentType::Adapter> { using Type = BarriersForAdapterType; };`
- L182 _public typedef_ `template<> struct CreateBarriersInternalReturnType<EComponentType::Context> { using Type = BarriersForContextType; };`

#### struct `TD3D12BarriersFactory::CreateBarriersInternalReturnType`  
`template<> struct CreateBarriersInternalReturnType<EComponentType::Context>`  
_L182-182_
- L178 _public typedef_ `template <EComponentType InCompType> struct CreateBarriersInternalReturnType { using Type = nullptr_t; };` — If another component type is added, add a new specialization to use the same CreateBarriersInternal function for it
- L180 _public typedef_ `template<> struct CreateBarriersInternalReturnType<EComponentType::Adapter> { using Type = BarriersForAdapterType; };`
- L182 _public typedef_ `template<> struct CreateBarriersInternalReturnType<EComponentType::Context> { using Type = BarriersForContextType; };`

#### Free symbols / members of external scopes

- L55 _typedef_ `using FNullD3D12BarriersFactoryEntry = TD3D12BarriersFactoryEntry<ED3D12BarrierImplementationType::Invalid, nullptr_t, nullptr_t>;` — Used for ending the list of TFactoryEntries in the template parameters for TD3D12BarriersFactory

### `Source/Runtime/D3D12RHI/Private/D3D12BindlessDescriptors.h` (Private)


#### class `FD3D12BindlessDescriptorAllocator`  
`class FD3D12BindlessDescriptorAllocator : public FD3D12AdapterChild`  
_L34-78_
- inherits: `FD3D12AdapterChild`
- desc: Manager for configuration settings and shared descriptor allocators, stored on the adapter.
- L37 _public prototype_ `FD3D12BindlessDescriptorAllocator() = delete;`
- L38 _public prototype_ `FD3D12BindlessDescriptorAllocator(FD3D12Adapter* InParent);`
- L40 _public prototype_ `void Init();`
- L42 _public function_ `ERHIBindlessConfiguration GetConfiguration() const`
- L44 _public function_ `bool AreResourcesBindless() const`
- L45 _public function_ `bool AreSamplersBindless() const`
- L48 _public prototype_ `FRHIDescriptorHandle AllocateDescriptor(ERHIDescriptorType DescriptorType);` — Bindless descriptor allocators are stored in the adapter, so descriptor handles can be allocated once and shared for multi-GPU objects
- L49 _public prototype_ `TOptional<FRHIDescriptorAllocation> AllocateDescriptors(ERHIDescriptorTypeMask DescriptorTypeMask, uint32 DescriptorCount);`
- L51 _public prototype_ `void FreeDescriptor(FRHIDescriptorHandle Handle);`
- L52 _public prototype_ `void FreeDescriptors(FRHIDescriptorAllocation Allocation, ERHIDescriptorTypeMask TypeMask);`
- L54 _public function_ `FCriticalSection& GetResourceHeapsCS()`
- L56 _public function_ `uint32 GetResourceCapacity() const`
- L57 _public function_ `uint32 GetSamplerCapacity() const`
- L59 _public function_ `bool GetResourceAllocatedRange(FRHIDescriptorAllocatorRange& OutAllocatedRange) const`
- L62 _public function_ `FRHIHeapDescriptorAllocator* GetResourceAllocator()`
- L67 _private prototype_ `TOptional<FRHIDescriptorAllocation> ResizeGrowAndAllocate(uint32 NumAllocations);`
- L70 _private member_ `ERHIBindlessConfiguration BindlessConfiguration{};`
- L72 _private member_ `uint32 MaxResourceHeapSize = 0;`
- L73 _private member_ `uint32 MaxSamplerHeapSize = 0;`
- L75 _private member_ `FCriticalSection ResourceHeapsCS;`
- L76 _private member_ `FRHIHeapDescriptorAllocator* ResourceAllocator = nullptr;`
- L77 _private member_ `FRHIHeapDescriptorAllocator* SamplerAllocator = nullptr;`

#### class `FD3D12BindlessSamplerManager`  
`class FD3D12BindlessSamplerManager : public FD3D12DeviceChild`  
_L81-112_
- inherits: `FD3D12DeviceChild`
- desc: Manager specifically for bindless sampler descriptors.
- L84 _public prototype_ `FD3D12BindlessSamplerManager() = delete;`
- L85 _public prototype_ `FD3D12BindlessSamplerManager(FD3D12Device* InDevice, FD3D12BindlessDescriptorAllocator& InAllocator);`
- L87 _public prototype_ `void CleanupResources();`
- L89 _public prototype_ `void InitializeDescriptor(FRHIDescriptorHandle DstHandle, const FD3D12SamplerState* SamplerState);`
- L91 _public prototype_ `void OpenCommandList(FD3D12CommandContext& Context);`
- L92 _public prototype_ `void CloseCommandList(FD3D12CommandContext& Context);`
- L94 _public prototype_ `FD3D12DescriptorHeap* GetExplicitHeapForContext(FD3D12CommandContext& Context) const;`
- L96 _public function_ `FD3D12DescriptorHeap* GetHeap() const`
- L97 _public function_ `ERHIBindlessConfiguration GetConfiguration() const`
- L99 _public function_ `constexpr ERHIDescriptorTypeMask GetTypeMask() const`
- L104 _public function_ `constexpr bool HandlesAllocation(ERHIDescriptorType InType) const`
- L110 _private member_ `FD3D12DescriptorHeapPtr GpuHeap;`
- L111 _private member_ `ERHIBindlessConfiguration Configuration;`

#### struct `FD3D12ContextBindlessState`  
`struct FD3D12ContextBindlessState`  
_L117-132_
- desc: Helper container for all context related bindless state.
- L119 _public member_ `FD3D12DescriptorHeapPtr CurrentGpuHeap;`
- L120 _public member_ `bool bRefreshHeap = false;`
- L122 _public prototype_ `FD3D12ContextBindlessState() = default;`
- L123 _public function_ `~FD3D12ContextBindlessState()`
- L128 _public function_ `void RefreshDescriptorHeap()`

#### class `FMovingWindowMax`  
`template <typename T, int32 ArraySize> class FMovingWindowMax`  
_L136-176_
- desc: Simple helper class to compute moving max in given amount of values.
- L139 _public function_ `FMovingWindowMax() : RemoveNextIdx(0) , NumValuesUsed(0)`
- L146 _public function_ `void PushValue(T Value)`
- L160 _public function_ `T GetMax() const`
- L171 _private member_ `TStaticArray<T, ArraySize> ValuesArray;`
- L174 _private member_ `int32 RemoveNextIdx;` — The array Index of the next item to remove when the moving window is full
- L175 _private member_ `int32 NumValuesUsed;`

#### class `FD3D12BindlessResourceManager`  
`class FD3D12BindlessResourceManager : public FD3D12DeviceChild`  
_L179-253_
- inherits: `FD3D12DeviceChild`
- desc: Manager specifically for bindless resource descriptors. Has to handle renames on command lists.
- L182 _public prototype_ `FD3D12BindlessResourceManager() = delete;`
- L183 _public prototype_ `FD3D12BindlessResourceManager(FD3D12Device* InDevice, FD3D12BindlessDescriptorAllocator& InAllocator);`
- L185 _public prototype_ `void CleanupResources();`
- L187 _public prototype_ `void GarbageCollect();`
- L188 _public prototype_ `void Recycle(FD3D12DescriptorHeap* DescriptorHeap);`
- L190 _public prototype_ `void InitializeDescriptor(FRHIDescriptorHandle DstHandle, const FD3D12View* View);`
- L191 _public prototype_ `void UpdateDescriptor(FD3D12ContextArray const& Contexts, FRHIDescriptorHandle DstHandle, const FD3D12View* View);`
- L193 _public prototype_ `void FlushPendingDescriptorUpdates(FD3D12CommandContext& Context);`
- L195 _public prototype_ `void OpenCommandList(FD3D12CommandContext& Context);`
- L196 _public prototype_ `void CloseCommandList(FD3D12CommandContext& Context);`
- L197 _public prototype_ `void FinalizeContext(FD3D12CommandContext& Context);`
- L199 _public prototype_ `FD3D12DescriptorHeap* GetHeap(ERHIPipeline Pipeline) const;`
- L200 _public prototype_ `FD3D12DescriptorHeap* GetExplicitHeapForContext(FD3D12CommandContext& Context);`
- L202 _public function_ `ERHIBindlessConfiguration GetConfiguration() const`
- L205 _public prototype_ `void GrowCPUHeap(uint32 OriginalNumDescriptors, uint32 NewNumDescriptors);` — Called from FD3D12Adapter::AllocateBindlessResourceHandle
- L207 _public function_ `constexpr ERHIDescriptorTypeMask GetTypeMask() const`
- L212 _public function_ `constexpr bool HandlesAllocation(ERHIDescriptorType InType) const`
- L218 _private prototype_ `void CopyCpuHeap(FD3D12DescriptorHeap* DestinationHeap);`
- L219 _private prototype_ `void AssignHeapToState(FD3D12ContextBindlessState& State);`
- L220 _private prototype_ `void FinalizeHeapOnState(FD3D12ContextBindlessState& State);`
- L222 _private prototype_ `void CheckRequestNewActiveGPUHeap();`
- L223 _private prototype_ `int AddActiveGPUHeap();`
- L224 _private prototype_ `void ReleaseGPUHeaps();`
- L225 _private prototype_ `void UpdateInUseGPUHeaps(bool bInUse);`
- L228 _private member_ `FCriticalSection& HeapsCS;` — Critical section shared across devices
- L229 _private member_ `FD3D12DescriptorHeapPtr CpuHeap;`
- L230 _private member_ `const ERHIBindlessConfiguration Configuration;`
- L232 _private member_ `uint64 GarbageCollectCycle = 0;`
- L233 _private member_ `uint64 LastUsedExplicitHeapCycle = 0;`
- L235 _private member_ `bool bRequestNewActiveGpuHeap = false;`
- L236 _private member_ `bool bCPUHeapResized = false;`
- L238 _private member_ `uint32 InUseGPUHeaps = 0;`
- L239 _private member_ `uint32 MaxInUseGPUHeaps = 0;`
- L240 _private member_ `FMovingWindowMax<uint32, 100> MovingWindowMaxInUseGPUHeaps;`
- L250 _private member_ `int32 ActiveGpuHeapIndex = -1;`
- L251 _private member_ `TArray<FGpuHeapData> ActiveGpuHeaps;`
- L252 _private member_ `TArray<FGpuHeapData> PooledGpuHeaps;`

#### struct `FD3D12BindlessResourceManager::FGpuHeapData`  
`struct FGpuHeapData`  
_L242-248_
- L244 _public member_ `FD3D12DescriptorHeapPtr GpuHeap;`
- L245 _public member_ `TArray<FD3D12DescriptorIndex> UpdatedIndices;`
- L246 _public member_ `bool bInUse = true;`
- L247 _public member_ `uint64 LastUsedGarbageCollectCycle = 0;`

#### struct `FD3D12DescriptorHeapPair`  
`struct FD3D12DescriptorHeapPair`  
_L257-261_
- L259 _public member_ `FD3D12DescriptorHeap* SamplerHeap;`
- L260 _public member_ `FD3D12DescriptorHeap* ResourceHeap;`

#### class `FD3D12BindlessDescriptorManager`  
`class FD3D12BindlessDescriptorManager : public FD3D12DeviceChild`  
_L264-324_
- inherits: `FD3D12DeviceChild`
- desc: Manager for descriptors used in bindless rendering.
- L267 _public prototype_ `FD3D12BindlessDescriptorManager(FD3D12Device* InDevice, FD3D12BindlessDescriptorAllocator& InAllocator);`
- L268 _public prototype_ `~FD3D12BindlessDescriptorManager();`
- L270 _public prototype_ `void Init();`
- L271 _public prototype_ `void CleanupResources();`
- L273 _public function_ `FD3D12BindlessDescriptorAllocator& GetAllocator()`
- L278 _public function_ `FD3D12BindlessResourceManager* GetResourceManager() const`
- L283 _public function_ `FD3D12BindlessSamplerManager* GetSamplerManager() const`
- L288 _public function_ `ERHIBindlessConfiguration GetConfiguration() const`
- L293 _public prototype_ `void ImmediateFree(FRHIDescriptorHandle InHandle);`
- L294 _public prototype_ `void DeferredFreeFromDestructor(FRHIDescriptorHandle InHandle);`
- L296 _public prototype_ `void GarbageCollect();`
- L297 _public prototype_ `void Recycle(FD3D12DescriptorHeap* DescriptorHeap);`
- L299 _public prototype_ `void InitializeDescriptor(FRHIDescriptorHandle DstHandle, const FD3D12SamplerState* SamplerState);`
- L300 _public prototype_ `void InitializeDescriptor(FRHIDescriptorHandle DstHandle, const FD3D12View* View);`
- L301 _public prototype_ `void UpdateDescriptor(FD3D12ContextArray const& Contexts, FRHIDescriptorHandle DstHandle, const FD3D12View* SourceView);`
- L303 _public prototype_ `void FinalizeContext(FD3D12CommandContext& Context);`
- L305 _public prototype_ `void OpenCommandList(FD3D12CommandContext& Context);`
- L306 _public prototype_ `void CloseCommandList(FD3D12CommandContext& Context);`
- L308 _public prototype_ `void FlushPendingDescriptorUpdates(FD3D12CommandContext& Context);`
- L309 _public prototype_ `void SetHeapsForRayTracing(FD3D12CommandContext& Context);`
- L311 _public prototype_ `FD3D12DescriptorHeapPair GetExplicitHeapsForContext(FD3D12CommandContext& Context, ERHIBindlessConfiguration InConfiguration);`
- L314 _public prototype_ `TRHIPipelineArray<FD3D12DescriptorHeapPtr> AllocateResourceHeapsForAllPipelines(int32 InSize);`
- L318 _private member_ `FD3D12BindlessDescriptorAllocator& Allocator;`
- L320 _private member_ `TUniquePtr<FD3D12BindlessResourceManager> ResourceManager;`
- L321 _private member_ `TUniquePtr<FD3D12BindlessSamplerManager> SamplerManager;`
- L323 _private member_ `ERHIBindlessConfiguration Configuration{};`

#### Free symbols / members of external scopes

- L26 _namespace_ `namespace UE`
- L26 _namespace_ `namespace D3D12BindlessDescriptors` (scope `UE`)
- L28 _prototype_ `FD3D12DescriptorHeap* CreateCpuHeap(FD3D12Device* InDevice, ERHIDescriptorHeapType InType, uint32 InNewNumDescriptorsPerHeap);` (scope `UE::D3D12BindlessDescriptors`)
- L29 _prototype_ `FD3D12DescriptorHeap* CreateGpuHeap(FD3D12Device* InDevice, ERHIDescriptorHeapType InType, uint32 InNewNumDescriptorsPerHeap);` (scope `UE::D3D12BindlessDescriptors`)
- L30 _prototype_ `void DeferredFreeHeap(FD3D12Device* InDevice, FD3D12DescriptorHeap* InHeap);` (scope `UE::D3D12BindlessDescriptors`)

### `Source/Runtime/D3D12RHI/Private/D3D12CommandContext.h` (Private)


#### struct `FD3D12DeferredDeleteObject`  
`struct FD3D12DeferredDeleteObject`  
_L48-189_
- L66 _public member_ `} Type;`
- L116 _public function_ `explicit FD3D12DeferredDeleteObject(FD3D12Resource* RHIObject) : Type(EType::RHIObject) , RHIObject(RHIObject)`
- L121 _public function_ `explicit FD3D12DeferredDeleteObject(FD3D12Heap* InHeap) : Type(EType::Heap) , Heap(InHeap)`
- L126 _public function_ `explicit FD3D12DeferredDeleteObject(FD3D12DescriptorHeap* InDescriptorHeap, EType Type) : Type(Type) , DescriptorHeap(InDescriptorHeap)`
- L137 _public function_ `explicit FD3D12DeferredDeleteObject(ID3D12Object* D3DObject) : Type(EType::D3DObject) , D3DObject(D3DObject)`
- L143 _public function_ `explicit FD3D12DeferredDeleteObject(FRHIDescriptorAllocation Allocation, ERHIDescriptorTypeMask TypeMask, FD3D12Device* Device) : Type(EType::DescriptorAllocation) , DescriptorAllocation({ Allocation, TypeMask, Device })`
- L148 _public function_ `explicit FD3D12DeferredDeleteObject(FRHIDescriptorHandle Handle, FD3D12Device* Device) : Type(EType::BindlessDescriptor) , BindlessDescriptor({ Handle, Device })`
- L154 _public function_ `explicit FD3D12DeferredDeleteObject(void* Ptr, EType Type) : Type(Type) , CPUAllocation(Ptr)`
- L161 _public function_ `explicit FD3D12DeferredDeleteObject(FD3D12OnlineDescriptorBlock* Block, FD3D12OnlineDescriptorManager* Manager) : Type(EType::DescriptorBlock) , DescriptorBlock({ Block, Manager })`
- L166 _public function_ `explicit FD3D12DeferredDeleteObject(FPlatformMemory::FPlatformVirtualMemoryBlock& VirtualBlock, ETextureCreateFlags Flags, uint64 CommittedTextureSize, void* RawMemory) : Type(EType::VirtualAllocation) , VirtualAllocDescriptor({ VirtualBlock, Flags, CommittedTextureSize, RawMemory })`
- L171 _public function_ `explicit FD3D12DeferredDeleteObject(TUniqueFunction<void()>&& Func) : Type(EType::Func) , Func(new TUniqueFunction<void()>(MoveTemp(Func)))`
- L176 _public function_ `explicit FD3D12DeferredDeleteObject(FD3D12Texture* InTexture, TUniquePtr<FD3D12LockedResource>&& InLockedResource, uint32 InSubresource) : Type(EType::TextureStagingBuffer)`

#### enum `FD3D12DeferredDeleteObject::EType`  
`enum class EType`  
_L50-66_
- L52 _public enumerator_ `RHIObject`
- L53 _public enumerator_ `D3DObject`
- L54 _public enumerator_ `Heap`
- L55 _public enumerator_ `DescriptorHeap`
- L57 _public enumerator_ `DescriptorAllocation`
- L58 _public enumerator_ `BindlessDescriptor`
- L59 _public enumerator_ `BindlessDescriptorHeap`
- L61 _public enumerator_ `CPUAllocation`
- L62 _public enumerator_ `DescriptorBlock`
- L63 _public enumerator_ `VirtualAllocation`
- L64 _public enumerator_ `Func`
- L65 _public enumerator_ `TextureStagingBuffer`

#### union `FD3D12DeferredDeleteObject::(anonymous)`  
``  
_L69-114_

#### struct `FD3D12DeferredDeleteObject::__anon4ceecebb010a::(anonymous)`  
``  
_L79-83_

#### struct `FD3D12DeferredDeleteObject::__anon4ceecebb010a::(anonymous)`  
``  
_L86-89_

#### struct `FD3D12DeferredDeleteObject::__anon4ceecebb010a::(anonymous)`  
``  
_L95-98_

#### struct `FD3D12DeferredDeleteObject::__anon4ceecebb010a::(anonymous)`  
``  
_L101-106_

#### struct `FD3D12DeferredDeleteObject::__anon4ceecebb010a::(anonymous)`  
``  
_L109-113_

#### enum `ED3D12Units`  
`enum class ED3D12Units`  
_L191-195_
- L193 _public enumerator_ `Raw`
- L194 _public enumerator_ `Microseconds`

#### enum `ED3D12FlushFlags`  
`enum class ED3D12FlushFlags`  
_L197-206_
- L199 _public enumerator_ `None = 0`
- L202 _public enumerator_ `WaitForSubmission = 1` — Block the calling thread until the submission thread has dispatched all work.
- L205 _public enumerator_ `WaitForCompletion = 2` — Both the calling thread until the GPU has signaled completion of all dispatched work.

#### class `FD3D12ContextCommon`  
`class FD3D12ContextCommon`  
_L213-457_
- desc: Base class that manages the recording of FD3D12FinalizedCommands instances. Manages the logic for creating and recycling command lists and allocators.
- L218 _protected prototype_ `FD3D12ContextCommon(FD3D12Device* Device, ED3D12QueueType QueueType, bool bIsDefaultContext);`
- L221 _public prototype_ `virtual ~FD3D12ContextCommon() = default;`
- L224 _protected prototype_ `virtual void OpenCommandList();`
- L225 _protected prototype_ `virtual void CloseCommandList();`
- L234 _public function_ `virtual void ClearState(EClearStateMode ClearStateMode = EClearStateMode::All)`
- L235 _public function_ `virtual void ConditionalClearShaderResource(FD3D12ResourceLocation* Resource, EShaderParameterTypeMask ShaderParameterTypeMask)`
- L239 _public prototype_ `void SignalSyncPoint(FD3D12SyncPoint* SyncPoint);` — Inserts a command to signal the specified sync point
- L242 _public prototype_ `void WaitSyncPoint(FD3D12SyncPoint* SyncPoint);` — Inserts a command that blocks the GPU queue until the specified sync point is signaled.
- L245 _public prototype_ `void SignalManualFence(ID3D12Fence* Fence, uint64 Value);` — Inserts a command that signals the specified D3D12 fence object.
- L248 _public prototype_ `void WaitManualFence(ID3D12Fence* Fence, uint64 Value, const TSharedPtr<std::atomic<bool>>& bHasSignalled);` — Inserts a command that waits the specified D3D12 fence object.
- L252 _public prototype_ `FD3D12QueryLocation InsertTimestamp(ED3D12Units Units, uint64* Target);` — Inserts a timestamp query command. "Target" specifies the optional location the result will be written to by the interrupt handler thread.
- L255 _public prototype_ `FD3D12QueryLocation AllocateQuery(ED3D12QueryType Type, void* Target);` — Allocates a query of the specified type, returning its location.
- L260 _public prototype_ `void SetReservedBufferCommitSize(FD3D12Buffer* Buffer, uint64 CommitSizeInBytes);` — Resizes physical memory allocation for a buffer. Allocates new backing heaps as necessary. Causes the command list to be split, as reserved resource update operations are performed on the D3D12 queue. The actual work is deferred via FD3D12Payload.
- L264 _public prototype_ `virtual void Finalize(TArray<FD3D12Payload*>& OutPayloads);` — Complete recording of the current command list set, and appends the resulting payloads to the given array. Resets the context so new commands can be recorded.
- L267 _public member_ `FD3D12Device* const Device;` — The owner device of this context
- L270 _public member_ `ED3D12QueueType const QueueType;` — The type of command lists this context records.
- L271 _public function_ `bool IsAsyncComputeContext() const`
- L272 _public prototype_ `ERHIPipeline GetRHIPipeline() const;`
- L275 _public member_ `bool const bIsDefaultContext;` — True for the immediate context (@todo remove this)
- L276 _public function_ `bool IsDefaultContext() const`
- L278 _public function_ `bool IsOpen() const`
- L279 _public function_ `bool IsPendingCommands() const`
- L281 _public function_ `FD3D12SyncPoint* GetContextSyncPoint()`
- L298 _public member_ `} BatchedSyncPoints;`
- L300 _public prototype_ `void BindDiagnosticBuffer(FD3D12RootSignature const* RootSignature, ED3D12PipelineType PipelineType);`
- L302 _public function_ `FD3D12QueryAllocator& GetTimestampQueries()`
- L309 _private member_ `FD3D12QueryAllocator TimestampQueries;` — Allocators to manage query heaps
- L310 _private member_ `FD3D12QueryAllocator OcclusionQueries;`
- L311 _private member_ `FD3D12QueryAllocator PipelineStatsQueries;`
- L315 _private member_ `FD3D12CommandList* CommandList = nullptr;` — The active D3D12 command list where recorded D3D commands are directed. This is swapped when command lists are split (e.g. when signalling a fence).
- L319 _private member_ `FD3D12CommandAllocator* CommandAllocator = nullptr;` — The command allocator used to open command lists within this context. The allocator is reused for each new command list until the context is finalized.
- L323 _private member_ `TArray<FD3D12Payload*> Payloads;` — The array of recorded payloads the submission thread will process. These are returned when the context is finalized.
- L326 _private member_ `FD3D12SyncPointRef ContextSyncPoint;` — A sync point signaled when all payloads in this context have completed.
- L329 _public function_ `void BeginRecursiveCommand()`
- L335 _public function_ `FD3D12CommandList& GetCommandList()` — Returns the current command list (or creates a new one if the command list was not open).
- L344 _protected prototype_ `void WriteMarker(D3D12_GPU_VIRTUAL_ADDRESS Address, uint32 Value, EMarkerType Type);`
- L352 _protected member_ `} CurrentPhase = EPhase::Wait;`
- L354 _protected function_ `FD3D12Payload* GetPayload(EPhase Phase)`
- L365 _protected prototype_ `void NewPayload();`
- L367 _protected member_ `uint32 ActiveQueries = 0;`
- L369 _protected member_ `const TUniquePtr<FD3D12BarriersFactory::BarriersForContextType> Barriers;`
- L373 _public function_ `void OpenIfNotAlready()` — Open the command list if it's not already open.
- L382 _public prototype_ `void SetPresent(FD3D12PresentArgs& PresentArgs);` — Set the Present Params in the context for the Submission Thread to call the native Present
- L385 _public prototype_ `void FlushCommands(ED3D12FlushFlags FlushFlags = ED3D12FlushFlags::None);` — Flushes any pending commands in this context to the GPU.
- L389 _public prototype_ `void ConditionalSplitCommandList();` — Closes the current command list if the number of enqueued commands exceeds the threshold defined by the "D3D12.MaxCommandsPerCommandList" cvar.
- L391 _public function_ `auto BaseCommandList ()`
- L392 _public function_ `auto CopyCommandList ()`
- L393 _public function_ `auto GraphicsCommandList ()`
- L395 _public function_ `auto GraphicsCommandList1 ()`
- L398 _public function_ `auto GraphicsCommandList2 ()`
- L401 _public function_ `auto GraphicsCommandList3 ()`
- L404 _public function_ `auto GraphicsCommandList4 ()`
- L407 _public function_ `auto GraphicsCommandList5 ()`
- L410 _public function_ `auto GraphicsCommandList6 ()`
- L413 _public function_ `auto GraphicsCommandList7 ()`
- L416 _public function_ `auto GraphicsCommandList8 ()`
- L419 _public function_ `auto GraphicsCommandList9 ()`
- L422 _public function_ `auto GraphicsCommandList10()`
- L426 _public function_ `auto DebugCommandList ()`
- L429 _public function_ `auto RayTracingCommandList()`
- L432 _public function_ `auto AftermathHandle ()`
- L435 _public function_ `void BeginQuery(FD3D12QueryLocation const& Location)`
- L436 _public function_ `void EndQuery (FD3D12QueryLocation const& Location)`
- L439 _public function_ `void UpdateResidency(const FD3D12Resource* Resource)`
- L445 _public prototype_ `void AddGlobalBarrier( ED3D12Access InD3D12AccessBefore, ED3D12Access InD3D12AccessAfter);` — Resource transition / barrier functions. These get batched and recorded into the command list when FlushResourceBarriers() is called.
- L449 _public prototype_ `void AddBarrier( const FD3D12Resource* pResource, ED3D12Access InD3D12AccessBefore, ED3D12Access InD3D12AccessAfter, uint32 Subresource);`
- L456 _public prototype_ `void FlushResourceBarriers();` — Flushes the batched resource barriers to the current command list

#### enum `FD3D12ContextCommon::EClearStateMode`  
`enum class EClearStateMode`  
_L228-232_
- L230 _public enumerator_ `TransientOnly`
- L231 _public enumerator_ `All`

#### struct `FD3D12ContextCommon::(anonymous)`  
``  
_L295-298_

#### enum `FD3D12ContextCommon::EMarkerType`  
`enum class EMarkerType`  
_L343-343_
- L343 _public enumerator_ `enum class EMarkerType { In, Out }; void WriteMarker(D3D12_GPU_VIRTUAL_ADDRESS Address, uint32 Value, EMarkerType Type); enum class EPhase { Wait, UpdateReservedResources, Execute,`
- L343 _public enumerator_ `enum class EMarkerType { In, Out }; void WriteMarker(D3D12_GPU_VIRTUAL_ADDRESS Address, uint32 Value, EMarkerType Type); enum class EPhase { Wait, UpdateReservedResources, Execute,`

#### enum `FD3D12ContextCommon::EPhase`  
`enum class EPhase`  
_L346-352_
- L348 _public enumerator_ `Wait`
- L349 _public enumerator_ `UpdateReservedResources`
- L350 _public enumerator_ `Execute`
- L351 _public enumerator_ `Signal`

#### class `FD3D12ContextCopy`  
`class FD3D12ContextCopy final : public FD3D12ContextCommon`  
_L463-469_
- inherits: `FD3D12ContextCommon`
- desc: Context for the copy queue. Doesn't implement an RHI interface since the copy queue is not directly exposed to the renderer.
- L466 _public function_ `FD3D12ContextCopy(FD3D12Device* Device) : FD3D12ContextCommon(Device, ED3D12QueueType::Copy, false)`

#### class `FD3D12CopyScope`  
`class FD3D12CopyScope final`  
_L475-492_
- desc: Helper for recording and submitting copy queue work. Used for buffer / texture data upload etc.
- L478 _private member_ `FD3D12Device* const Device;`
- L479 _private member_ `FD3D12SyncPointRef SyncPoint;`
- L482 _private member_ `mutable bool bSyncPointRetrieved = false;`
- L486 _public member_ `FD3D12ContextCopy& Context;`
- L488 _public prototype_ `FD3D12SyncPoint* GetSyncPoint() const;`
- L490 _public prototype_ `FD3D12CopyScope(FD3D12Device* Device, ED3D12SyncPointType SyncPointType, FD3D12SyncPointRef const& WaitSyncPoint = {});`
- L491 _public prototype_ `~FD3D12CopyScope();`

#### class `FD3D12CommandContextBase`  
`class FD3D12CommandContextBase : public IRHICommandContext, public FD3D12AdapterChild`  
_L496-525_
- inherits: `IRHICommandContext,FD3D12AdapterChild`
- desc: Base class used to define commands that are not device specific, or that broadcast to all devices. @todo mgpu - try to remove this class
- L499 _public prototype_ `FD3D12CommandContextBase(FD3D12Adapter* InParent, FRHIGPUMask InGPUMask);`
- L501 _public function_ `FRHIGPUMask GetGPUMask() const`
- L502 _public function_ `FRHIGPUMask GetPhysicalGPUMask() const`
- L504 _public function_ `virtual void RHISetAsyncComputeBudget(EAsyncComputeBudget Budget)`
- L506 _public function_ `virtual class FD3D12CommandContextRedirector* AsRedirector()`
- L508 _public function_ `static FD3D12CommandContextBase& Get(FRHICommandListBase& RHICmdList)`
- L513 _public function_ `static FD3D12CommandContextBase* Get(IRHIComputeContext* RHIContext)`
- L518 _public prototype_ `virtual FD3D12CommandContext* GetSingleDeviceContext(uint32 InGPUIndex) = 0;`
- L523 _protected member_ `FRHIGPUMask GPUMask;`
- L524 _protected member_ `FRHIGPUMask PhysicalGPUMask;`

#### class `FD3D12CommandContext`  
`class FD3D12CommandContext : public FD3D12ContextCommon, public FD3D12CommandContextBase, public FD3D12DeviceChild`  
_L528-888_
- inherits: `FD3D12ContextCommon,FD3D12CommandContextBase,FD3D12DeviceChild`
- desc: RHI Context type used for graphics and async compute command lists.
- L531 _public prototype_ `FD3D12CommandContext(class FD3D12Device* InParent, ED3D12QueueType QueueType, bool InIsDefaultContext);`
- L532 _public prototype_ `virtual ~FD3D12CommandContext();`
- L534 _public function_ `static FD3D12CommandContext& Get(FRHICommandListBase& RHICmdList, uint32 GPUIndex)`
- L544 _public prototype_ `virtual void OpenCommandList() override;`
- L545 _public prototype_ `virtual void CloseCommandList() override final;`
- L547 _public function_ `virtual ERHIPipeline GetPipeline() const override`
- L554 _public prototype_ `virtual void ClearState(EClearStateMode ClearStateMode = EClearStateMode::All) override final;`
- L555 _public prototype_ `virtual void ConditionalClearShaderResource(FD3D12ResourceLocation* Resource, EShaderParameterTypeMask ShaderParameterTypeMask) override final;`
- L556 _public prototype_ `void ClearShaderResources(FD3D12UnorderedAccessView* UAV, EShaderParameterTypeMask ShaderParameterTypeMask);`
- L557 _public prototype_ `void ClearShaderResources(FD3D12BaseShaderResource* Resource, EShaderParameterTypeMask ShaderParameterTypeMask);`
- L558 _public prototype_ `void ClearAllShaderResources();`
- L560 _public function_ `void FlushProfilerStats()`
- L570 _public member_ `FD3D12FastConstantAllocator ConstantsAllocator;`
- L573 _public member_ `TArray<uint32> GPUEventStack;` — Current GPU event stack
- L575 _public member_ `FD3D12StateCache StateCache;`
- L578 _public member_ `FD3D12UniformBuffer* BoundUniformBuffers[SF_NumStandardFrequencies][MAX_CBS] = {};` — Track the currently bound uniform buffers.
- L581 _public member_ `uint16 DirtyUniformBuffers[SF_NumStandardFrequencies] = {};` — Bit array to track which uniform buffers have changed since the last draw call.
- L584 _public member_ `FRenderQueryRHIRef OuterOcclusionQuery;` — Handle for the dummy outer occlusion query we optionally insert for performance reasons
- L585 _public member_ `bool bOuterOcclusionQuerySubmitted = false;`
- L588 _public member_ `bool bDiscardSharedGraphicsConstants = false;` — When a new graphics PSO is set, we discard all old constants set for the previous shader.
- L591 _public member_ `bool bDiscardSharedComputeConstants = false;` — When a new compute PSO is set, we discard all old constants set for the previous shader.
- L596 _public member_ `D3D12_SHADING_RATE_COMBINER VRSCombiners[D3D12_RS_SET_SHADING_RATE_COMBINER_COUNT] = { D3D12_SHADING_RATE_COMBINER_PASSTHROUGH, D3D12_SHADING_RATE_COMBINER_PASSTHROUGH };`
- L597 _public member_ `D3D12_SHADING_RATE VRSShadingRate = D3D12_SHADING_RATE_1X1;`
- L601 _public member_ `FD3D12ConstantBuffer StageConstantBuffers[SF_NumStandardFrequencies];` — Constant buffers for Set*ShaderParameter calls.
- L604 _public member_ `bool bNeedFlushTextureCache = false;`
- L605 _public function_ `void InvalidateTextureCache()`
- L606 _public function_ `inline void FlushTextureCacheIfNeeded()`
- L615 _public function_ `virtual void FlushTextureCache()`
- L620 _public member_ `Experimental::TRobinHoodHashSet<uint64> RayTracingShaderTables;` — Used to deduplicate work done by the shader table on this context.
- L624 _public prototype_ `void CommitNonComputeShaderConstants();` — needs to be called before each draw call
- L627 _public prototype_ `void CommitComputeShaderConstants();` — needs to be called before each dispatch call
- L629 _public prototype_ `template <class ShaderType> void SetResourcesFromTables(const ShaderType* RESTRICT);`
- L631 _public prototype_ `void SetSRVParameter(EShaderFrequency Frequency, uint32 SRVIndex, FD3D12ShaderResourceView* SRV);`
- L632 _public prototype_ `void SetUAVParameter(EShaderFrequency Frequency, uint32 UAVIndex, FD3D12UnorderedAccessView* UAV);`
- L634 _public prototype_ `void CommitGraphicsResourceTables();`
- L635 _public prototype_ `void CommitComputeResourceTables();`
- L638 _public prototype_ `template<typename TPixelShader> void ResolveTextureUsingShader( FD3D12Texture* SourceTexture, FD3D12Texture* DestTexture, FD3D12RenderTargetView* DestSurfaceRTV, FD3D12DepthStencilView* DestSurfaceDSV, const D3D12_RESOURCE_DESC& ResolveTargetDesc, const FResolveRect& SourceRect, const FResolveRect& DestRect, typename TPixelShader::FParameter PixelShaderParameter );`
- L649 _public prototype_ `virtual void SetDepthBounds(float MinDepth, float MaxDepth);`
- L650 _public prototype_ `virtual void SetShadingRate(EVRSShadingRate ShadingRate, FD3D12Resource* ShadingRateImage, const TStaticArray<EVRSRateCombiner, ED3D12VRSCombinerStages::Num>& Combiners);`
- L652 _public function_ `virtual void SetAsyncComputeBudgetInternal(EAsyncComputeBudget Budget)`
- L654 _public prototype_ `virtual void RHIBeginTransitions(TArrayView<const FRHITransition*> Transitions) final override;`
- L655 _public prototype_ `virtual void RHIEndTransitions(TArrayView<const FRHITransition*> Transitions) final override;`
- L658 _public prototype_ `virtual void RHISetComputePipelineState(FRHIComputePipelineState* ComputePipelineState) final override;` — IRHIComputeContext interface
- L659 _public prototype_ `virtual void RHIDispatchComputeShader(uint32 ThreadGroupCountX, uint32 ThreadGroupCountY, uint32 ThreadGroupCountZ) final override;`
- L660 _public prototype_ `virtual void RHIDispatchIndirectComputeShader(FRHIBuffer* ArgumentBuffer, uint32 ArgumentOffset) final override;`
- L661 _public prototype_ `virtual void RHISetStaticUniformBuffers(const FUniformBufferStaticBindings& InUniformBuffers) final override;`
- L662 _public prototype_ `virtual void RHISetStaticUniformBuffer(FUniformBufferStaticSlot Slot, FRHIUniformBuffer* Buffer) final override;`
- L663 _public prototype_ `virtual void RHISetShaderParameters(FRHIComputeShader* Shader, TConstArrayView<uint8> InParametersData, TConstArrayView<FRHIShaderParameter> InParameters, TConstArrayView<FRHIShaderParameterResource> InResourceParameters, TConstArrayView<FRHIShaderParameterResource> InBindlessParameters) final override;`
- L664 _public prototype_ `virtual void RHISetShaderUnbinds(FRHIComputeShader* Shader, TConstArrayView<FRHIShaderParameterUnbind> InUnbinds) final override;`
- L665 _public prototype_ `virtual void RHISetShaderUnbinds(FRHIGraphicsShader* Shader, TConstArrayView<FRHIShaderParameterUnbind> InUnbinds) final override;`
- L667 _public prototype_ `virtual void RHIBeginBreadcrumbGPU(FRHIBreadcrumbNode* Breadcrumb) final override;`
- L668 _public prototype_ `virtual void RHIEndBreadcrumbGPU (FRHIBreadcrumbNode* Breadcrumb) final override;`
- L672 _public prototype_ `virtual void RHISetMultipleViewports(uint32 Count, const FViewportBounds* Data) final override;` — IRHICommandContext interface
- L673 _public prototype_ `virtual void RHIClearUAVFloat(FRHIUnorderedAccessView* UnorderedAccessViewRHI, const FVector4f& Values) final override;`
- L674 _public prototype_ `virtual void RHIClearUAVUint(FRHIUnorderedAccessView* UnorderedAccessViewRHI, const FUintVector4& Values) final override;`
- L675 _public prototype_ `virtual void RHICopyTexture(FRHITexture* SourceTexture, FRHITexture* DestTexture, const FRHICopyTextureInfo& CopyInfo) final override;`
- L676 _public prototype_ `virtual void RHICopyBufferRegion(FRHIBuffer* DestBuffer, uint64 DstOffset, FRHIBuffer* SourceBuffer, uint64 SrcOffset, uint64 NumBytes) final override;`
- L677 _public prototype_ `virtual void RHICopyToStagingBuffer(FRHIBuffer* SourceBuffer, FRHIStagingBuffer* DestinationStagingBuffer, uint32 Offset, uint32 NumBytes) final override;`
- L678 _public prototype_ `virtual void RHIBeginRenderQuery(FRHIRenderQuery* RenderQuery) final override;`
- L679 _public prototype_ `virtual void RHIEndRenderQuery(FRHIRenderQuery* RenderQuery) final override;`
- L680 _public prototype_ `virtual void RHISetStreamSource(uint32 StreamIndex, FRHIBuffer* VertexBuffer, uint32 Offset) final override;`
- L681 _public prototype_ `virtual void RHISetViewport(float MinX, float MinY, float MinZ, float MaxX, float MaxY, float MaxZ) final override;`
- L682 _public prototype_ `virtual void RHISetStereoViewport(float LeftMinX, float RightMinX, float LeftMinY, float RightMinY, float MinZ, float LeftMaxX, float RightMaxX, float LeftMaxY, float RightMaxY, float MaxZ) override;`
- L683 _public prototype_ `virtual void RHISetScissorRect(bool bEnable, uint32 MinX, uint32 MinY, uint32 MaxX, uint32 MaxY) final override;`
- L684 _public prototype_ `virtual void RHISetGraphicsPipelineState(FRHIGraphicsPipelineState* GraphicsPipelineState, uint32 StencilRef, bool bApplyAdditionalState) final override;`
- L685 _public prototype_ `virtual void RHISetShaderParameters(FRHIGraphicsShader* Shader, TConstArrayView<uint8> InParametersData, TConstArrayView<FRHIShaderParameter> InParameters, TConstArrayView<FRHIShaderParameterResource> InResourceParameters, TConstArrayView<FRHIShaderParameterResource> InBindlessParameters) final override;`
- L686 _public prototype_ `virtual void RHISetStencilRef(uint32 StencilRef) final override;`
- L687 _public prototype_ `virtual void RHISetBlendFactor(const FLinearColor& BlendFactor) final override;`
- L689 _public prototype_ `void SetRenderTargets(uint32 NumSimultaneousRenderTargets, const FRHIRenderTargetView* NewRenderTargets, const FRHIDepthRenderTargetView* NewDepthStencilTarget);`
- L690 _public prototype_ `void SetRenderTargetsAndClear(const FRHISetRenderTargetsInfo& RenderTargetsInfo);`
- L692 _public prototype_ `virtual void RHISetShaderRootConstants( const FUint32Vector4& Constants) override;`
- L695 _public prototype_ `virtual void RHIDispatchComputeShaderBundle( FRHIShaderBundle* ShaderBundle, FRHIBuffer* RecordArgBuffer, TConstArrayView<FRHIShaderParameterResource> SharedBindlessParameters, TConstArrayView<FRHIShaderBundleComputeDispatch> Dispatches, ERHIShaderBundleMethod Method) override;`
- L702 _public prototype_ `virtual void RHIDispatchGraphicsShaderBundle( FRHIShaderBundle* ShaderBundle, FRHIBuffer* RecordArgBuffer, const FRHIShaderBundleGraphicsState& BundleState, TConstArrayView<FRHIShaderParameterResource> SharedBindlessParameters, TConstArrayView<FRHIShaderBundleGraphicsDispatch> Dispatches, ERHIShaderBundleMethod Method) override;`
- L710 _public prototype_ `virtual void RHIDrawPrimitive(uint32 BaseVertexIndex, uint32 NumPrimitives, uint32 NumInstances) final override;`
- L711 _public prototype_ `virtual void RHIDrawPrimitiveIndirect(FRHIBuffer* ArgumentBuffer, uint32 ArgumentOffset) final override;`
- L712 _public prototype_ `virtual void RHIDrawIndexedPrimitive(FRHIBuffer* IndexBuffer, int32 BaseVertexIndex, uint32 FirstInstance, uint32 NumVertices, uint32 StartIndex, uint32 NumPrimitives, uint32 NumInstances) final override;`
- L713 _public prototype_ `virtual void RHIDrawIndexedPrimitiveIndirect(FRHIBuffer* IndexBuffer, FRHIBuffer* ArgumentBuffer, uint32 ArgumentOffset) final override;`
- L714 _public prototype_ `virtual void RHIMultiDrawIndexedPrimitiveIndirect(FRHIBuffer* IndexBuffer, FRHIBuffer* ArgumentBuffer, uint32 ArgumentOffset, FRHIBuffer* CountBuffer, uint32 CountBufferOffset, uint32 MaxDrawArguments) final override;`
- L716 _public prototype_ `virtual void RHIDispatchMeshShader(uint32 ThreadGroupCountX, uint32 ThreadGroupCountY, uint32 ThreadGroupCountZ) final override;`
- L717 _public prototype_ `virtual void RHIDispatchIndirectMeshShader(FRHIBuffer* ArgumentBuffer, uint32 ArgumentOffset) final override;`
- L719 _public prototype_ `virtual void RHISetDepthBounds(float MinDepth, float MaxDepth) final override;`
- L720 _public prototype_ `virtual void RHISetShadingRate(EVRSShadingRate ShadingRate, EVRSRateCombiner Combiner) final override;`
- L722 _public prototype_ `virtual void RHIClearMRTImpl(bool* bClearColorArray, int32 NumClearColors, const FLinearColor* ColorArray, bool bClearDepth, float Depth, bool bClearStencil, uint32 Stencil);`
- L724 _public function_ `virtual void RHIBeginRenderPass(const FRHIRenderPassInfo& InInfo, const TCHAR* InName)`
- L733 _public function_ `virtual void RHIEndRenderPass()`
- L747 _public prototype_ `void ResolveTexture(UE::RHICore::FResolveTextureInfo Info);`
- L750 _public prototype_ `virtual void RHIBindAccelerationStructureMemory(FRHIRayTracingScene* Scene, FRHIBuffer* Buffer, uint32 BufferOffset) final override;`
- L751 _public prototype_ `virtual void BuildAccelerationStructuresInternal(TConstArrayView<D3D12_BUILD_RAYTRACING_ACCELERATION_STRUCTURE_DESC> BuildDesc);`
- L753 _public prototype_ `virtual void BuildAccelerationStructuresInternalEx(const TArrayView<NVAPI_D3D12_BUILD_RAYTRACING_ACCELERATION_STRUCTURE_DESC_EX> ParamsArray);`
- L757 _public prototype_ `static void UnregisterAccelerationStructuresInternalMGPU(TConstArrayView<FRayTracingGeometryBuildParams> Params, FRHIGPUMask GPUMask);` — Should be called before RHIBuildAccelerationStructures when multiple GPU support is present (for example, from FD3D12CommandContextRedirector::RHIBuildAccelerationStructures)
- L759 _public prototype_ `virtual void RHIExecuteMultiIndirectClusterOperation(const FRayTracingClusterOperationParams& Params) final override;`
- L760 _public prototype_ `virtual void RHIBuildAccelerationStructures(TConstArrayView<FRayTracingGeometryBuildParams> Params, const FRHIBufferRange& ScratchBufferRange) final override;`
- L761 _public prototype_ `virtual void RHIBuildAccelerationStructures(TConstArrayView<FRayTracingSceneBuildParams> Params) final override;`
- L762 _public prototype_ `virtual void RHICommitShaderBindingTable(FRHIShaderBindingTable* SBT, FRHIBuffer* InlineBindingDataBuffer) final override;`
- L764 _public prototype_ `virtual void RHIRayTraceDispatch(FRHIRayTracingPipelineState* RayTracingPipelineState, FRHIRayTracingShader* RayGenShader, FRHIShaderBindingTable* InSBT, const FRayTracingShaderBindings& GlobalResourceBindings, uint32 Width, uint32 Height) final override;`
- L767 _public prototype_ `virtual void RHIRayTraceDispatchIndirect(FRHIRayTracingPipelineState* RayTracingPipelineState, FRHIRayTracingShader* RayGenShader, FRHIShaderBindingTable* InSBT, const FRayTracingShaderBindings& GlobalResourceBindings, FRHIBuffer* ArgumentBuffer, uint32 ArgumentOffset) final override;`
- L771 _public prototype_ `virtual void RHISetBindingsOnShaderBindingTable( FRHIShaderBindingTable* InSBT, FRHIRayTracingPipelineState* Pipeline, uint32 NumBindings, const FRayTracingLocalShaderBindings* Bindings, ERayTracingBindingType BindingType) final override;`
- L777 _public function_ `template<typename TRHIType, typename TReturnType = typename TD3D12ResourceTraits<TRHIType>::TConcreteType> static FORCEINLINE TReturnType* ResourceCast(TRHIType* Resource)`
- L783 _public function_ `template<typename TRHIType, typename TReturnType = typename TD3D12ResourceTraits<TRHIType>::TConcreteType> static FORCEINLINE_DEBUGGABLE TReturnType* ResourceCast(TRHIType* Resource, uint32 GPUIndex)`
- L790 _public function_ `template<typename ObjectType, typename RHIType> static FORCEINLINE_DEBUGGABLE ObjectType* RetrieveObject(RHIType* RHIObject, uint32 GPUIndex)`
- L796 _public function_ `template<typename ObjectType, typename RHIType> FORCEINLINE_DEBUGGABLE ObjectType* RetrieveObject(RHIType* RHIObject)`
- L801 _public function_ `static inline FD3D12Texture* RetrieveTexture(FRHITexture* Texture, uint32 GPUIndex)`
- L807 _public function_ `FORCEINLINE_DEBUGGABLE FD3D12Texture* RetrieveTexture(FRHITexture* Texture)`
- L812 _public function_ `FORCEINLINE_DEBUGGABLE const FD3D12Texture* RetrieveTexture(const FRHITexture* Texture)`
- L817 _public prototype_ `uint32 GetFrameFenceCounter() const;`
- L819 _public function_ `uint32 GetGPUIndex() const`
- L821 _public function_ `virtual void RHISetGPUMask(FRHIGPUMask InGPUMask) final override`
- L828 _public function_ `inline const TArray<FRHIUniformBuffer*>& GetStaticUniformBuffers() const`
- L833 _public prototype_ `void FlushPendingDescriptorUpdates();`
- L835 _public prototype_ `void SetExplicitDescriptorCache(FD3D12ExplicitDescriptorCache& ExplicitDescriptorCache);`
- L836 _public prototype_ `void UnsetExplicitDescriptorCache();`
- L838 _public prototype_ `virtual void Finalize(TArray<FD3D12Payload*>& OutPayloads) override;`
- L841 _public prototype_ `FD3D12DescriptorHeap* GetBindlessResourcesHeap();`
- L842 _public function_ `FD3D12ContextBindlessState& GetBindlessState()`
- L845 _public function_ `const FRHIShaderBindingLayout& GetShaderBindingLayout() const`
- L851 _public prototype_ `FORCENOINLINE void CopyBufferRegionChecked( ID3D12Resource* DestResource, const FName& DestName, uint64 DestOffset, ID3D12Resource* SourceResource, const FName& SourceName, uint64 SourceOffset, uint32 ByteCount );`
- L857 _public prototype_ `FORCENOINLINE void CopyTextureRegionChecked( const D3D12_TEXTURE_COPY_LOCATION* DestCopyLocation, int DestX, int DestY, int DestZ, EPixelFormat DestPixelFormat, const D3D12_TEXTURE_COPY_LOCATION* SourceCopyLocation, const D3D12_BOX* SourceBox, EPixelFormat SourcePixelFormat, const FName& DestName, const FName& SourceName );`
- L865 _protected function_ `FD3D12CommandContext* GetSingleDeviceContext(uint32 InGPUIndex) final override`
- L871 _private prototype_ `void SetupDispatch(uint32 ThreadGroupCountX, uint32 ThreadGroupCountY, uint32 ThreadGroupCountZ);`
- L872 _private prototype_ `void SetupDraw(FRHIBuffer* IndexBufferRHI, uint32 NumPrimitives = 0, uint32 NumVertices = 0);`
- L873 _private prototype_ `void SetupDispatchDraw(uint32 ThreadGroupCountX, uint32 ThreadGroupCountY, uint32 ThreadGroupCountZ);`
- L874 _private prototype_ `FD3D12ResourceLocation& SetupIndirectArgument(FRHIBuffer* ArgumentBufferRHI, D3D12_RESOURCE_STATES ExtraStates = static_cast<D3D12_RESOURCE_STATES>(0));`
- L875 _private prototype_ `void PostGpuEvent();`
- L877 _private prototype_ `static void ClearUAV(TRHICommandList_RecursiveHazardous<FD3D12CommandContext>& RHICmdList, FD3D12UnorderedAccessView_RHI* UAV, const void* ClearValues, bool bFloat);`
- L879 _private prototype_ `void DispatchWorkGraphShaderBundle(FRHIShaderBundle* ShaderBundle, FRHIBuffer* RecordArgBuffer, TConstArrayView<FRHIShaderParameterResource> SharedBindlessParameters, TConstArrayView<FRHIShaderBundleComputeDispatch> Dispatches);`
- L880 _private prototype_ `void DispatchWorkGraphShaderBundle(FRHIShaderBundle* ShaderBundle, FRHIBuffer* RecordArgBuffer, const FRHIShaderBundleGraphicsState& BundleState, TConstArrayView<FRHIShaderParameterResource> SharedBindlessParameters, TConstArrayView<FRHIShaderBundleGraphicsDispatch> Dispatches);`
- L882 _private member_ `TArray<FRHIUniformBuffer*> StaticUniformBuffers;`
- L883 _private member_ `const FRHIShaderBindingLayout* ShaderBindinglayout = nullptr;`
- L886 _private member_ `FD3D12ContextBindlessState BindlessState;`

#### class `FD3D12CommandContextRedirector`  
`class FD3D12CommandContextRedirector final : public FD3D12CommandContextBase`  
_L892-1192_
- inherits: `FD3D12CommandContextBase`
- desc: Version of command context to handle multi-GPU.  Because IRHICommandContext is pure virtual we can return the normal FD3D12CommandContext when not using mGPU, thus there is no additional overhead for the common case i.e. 1 GPU.
- L896 _public member_ `ED3D12QueueType const QueueType;` — The type of command lists this context records.
- L897 _public member_ `bool const bIsDefaultContext;`
- L899 _public prototype_ `FD3D12CommandContextRedirector(class FD3D12Adapter* InParent, ED3D12QueueType QueueType, bool InIsDefaultContext);`
- L901 _public function_ `virtual FD3D12CommandContextRedirector* AsRedirector() override`
- L906 _public function_ `FORCEINLINE virtual void RHISetComputePipelineState(FRHIComputePipelineState* ComputePipelineState) final override`
- L910 _public function_ `FORCEINLINE virtual void RHIDispatchComputeShader(uint32 ThreadGroupCountX, uint32 ThreadGroupCountY, uint32 ThreadGroupCountZ) final override`
- L914 _public function_ `FORCEINLINE virtual void RHIDispatchIndirectComputeShader(FRHIBuffer* ArgumentBuffer, uint32 ArgumentOffset) final override`
- L919 _public function_ `FORCEINLINE virtual void RHIBeginTransitions(TArrayView<const FRHITransition*> Transitions) final override`
- L923 _public function_ `FORCEINLINE virtual void RHIEndTransitions(TArrayView<const FRHITransition*> Transitions) final override`
- L929 _public prototype_ `virtual void RHITransferResources(TConstArrayView<FTransferResourceParams> Params) final override;`
- L930 _public prototype_ `virtual void RHITransferResourceSignal(TConstArrayView<FTransferResourceFenceData*> FenceDatas, FRHIGPUMask SrcGPUMask) final override;`
- L931 _public prototype_ `virtual void RHITransferResourceWait(TConstArrayView<FTransferResourceFenceData*> FenceDatas) final override;`
- L934 _public prototype_ `virtual void RHICrossGPUTransfer(TConstArrayView<FTransferResourceParams> Params, TConstArrayView<FCrossGPUTransferFence*> PreTransfer, TConstArrayView<FCrossGPUTransferFence*> PostTransfer) final override;` — New and improved cross GPU transfer API
- L935 _public prototype_ `virtual void RHICrossGPUTransferSignal(TConstArrayView<FTransferResourceParams> Params, TConstArrayView<FCrossGPUTransferFence*> PreTransfer) final override;`
- L936 _public prototype_ `virtual void RHICrossGPUTransferWait(TConstArrayView<FCrossGPUTransferFence*> PostTransfer) final override;`
- L939 _public function_ `FORCEINLINE virtual void RHICopyToStagingBuffer(FRHIBuffer* SourceBuffer, FRHIStagingBuffer* DestinationStagingBuffer, uint32 Offset, uint32 NumBytes) final override`
- L943 _public function_ `FORCEINLINE virtual void RHISetShaderParameters(FRHIComputeShader* Shader, TConstArrayView<uint8> InParametersData, TConstArrayView<FRHIShaderParameter> InParameters, TConstArrayView<FRHIShaderParameterResource> InResourceParameters, TConstArrayView<FRHIShaderParameterResource> InBindlessParameters) final override`
- L947 _public function_ `FORCEINLINE virtual void RHISetShaderUnbinds(FRHIComputeShader* Shader, TConstArrayView<FRHIShaderParameterUnbind> InUnbinds) final override`
- L953 _public function_ `FORCEINLINE virtual void RHIBeginBreadcrumbGPU(FRHIBreadcrumbNode* Breadcrumb) final override`
- L961 _public function_ `FORCEINLINE virtual void RHIEndBreadcrumbGPU(FRHIBreadcrumbNode* Breadcrumb) final override`
- L972 _public function_ `FORCEINLINE virtual void RHISetMultipleViewports(uint32 Count, const FViewportBounds* Data) final override` — IRHICommandContext interface
- L976 _public function_ `FORCEINLINE virtual void RHIClearUAVFloat(FRHIUnorderedAccessView* UnorderedAccessViewRHI, const FVector4f& Values) final override`
- L980 _public function_ `FORCEINLINE virtual void RHIClearUAVUint(FRHIUnorderedAccessView* UnorderedAccessViewRHI, const FUintVector4& Values) final override`
- L984 _public function_ `FORCEINLINE virtual void RHICopyTexture(FRHITexture* SourceTextureRHI, FRHITexture* DestTextureRHI, const FRHICopyTextureInfo& CopyInfo) final override`
- L988 _public function_ `FORCEINLINE virtual void RHICopyBufferRegion(FRHIBuffer* DestBuffer, uint64 DstOffset, FRHIBuffer* SourceBuffer, uint64 SrcOffset, uint64 NumBytes) final override`
- L992 _public function_ `FORCEINLINE virtual void RHIBeginRenderQuery(FRHIRenderQuery* RenderQuery) final override`
- L996 _public function_ `FORCEINLINE virtual void RHIEndRenderQuery(FRHIRenderQuery* RenderQuery) final override`
- L1000 _public function_ `FORCEINLINE virtual void RHISetStreamSource(uint32 StreamIndex, FRHIBuffer* VertexBuffer, uint32 Offset) final override`
- L1004 _public function_ `FORCEINLINE virtual void RHISetViewport(float MinX, float MinY, float MinZ, float MaxX, float MaxY, float MaxZ) final override`
- L1008 _public function_ `FORCEINLINE virtual void RHISetStereoViewport(float LeftMinX, float RightMinX, float LeftMinY, float RightMinY, float MinZ, float LeftMaxX, float RightMaxX, float LeftMaxY, float RightMaxY, float MaxZ) override`
- L1013 _public function_ `FORCEINLINE virtual void RHISetScissorRect(bool bEnable, uint32 MinX, uint32 MinY, uint32 MaxX, uint32 MaxY) final override`
- L1017 _public function_ `FORCEINLINE virtual void RHISetGraphicsPipelineState(FRHIGraphicsPipelineState* GraphicsPipelineState, uint32 StencilRef, bool bApplyAdditionalState) final override`
- L1021 _public function_ `FORCEINLINE virtual void RHISetStaticUniformBuffers(const FUniformBufferStaticBindings& InUniformBuffers) final override`
- L1025 _public function_ `FORCEINLINE virtual void RHISetStaticUniformBuffer(FUniformBufferStaticSlot Slot, FRHIUniformBuffer* Buffer) final override`
- L1029 _public function_ `FORCEINLINE virtual void RHISetShaderParameters(FRHIGraphicsShader* Shader, TConstArrayView<uint8> InParametersData, TConstArrayView<FRHIShaderParameter> InParameters, TConstArrayView<FRHIShaderParameterResource> InResourceParameters, TConstArrayView<FRHIShaderParameterResource> InBindlessParameters) final override`
- L1033 _public function_ `FORCEINLINE virtual void RHISetShaderUnbinds(FRHIGraphicsShader* Shader, TConstArrayView<FRHIShaderParameterUnbind> InUnbinds) final override`
- L1037 _public function_ `FORCEINLINE virtual void RHISetStencilRef(uint32 StencilRef) final override`
- L1041 _public function_ `FORCEINLINE void RHISetBlendFactor(const FLinearColor& BlendFactor) final override`
- L1045 _public function_ `FORCEINLINE void RHISetShaderRootConstants(const FUint32Vector4& Constants) final override`
- L1049 _public function_ `FORCEINLINE virtual void RHIDrawPrimitive(uint32 BaseVertexIndex, uint32 NumPrimitives, uint32 NumInstances) final override`
- L1053 _public function_ `FORCEINLINE virtual void RHIDrawPrimitiveIndirect(FRHIBuffer* ArgumentBuffer, uint32 ArgumentOffset) final override`
- L1057 _public function_ `FORCEINLINE virtual void RHIDrawIndexedPrimitive(FRHIBuffer* IndexBuffer, int32 BaseVertexIndex, uint32 FirstInstance, uint32 NumVertices, uint32 StartIndex, uint32 NumPrimitives, uint32 NumInstances) final override`
- L1061 _public function_ `FORCEINLINE virtual void RHIDrawIndexedPrimitiveIndirect(FRHIBuffer* IndexBuffer, FRHIBuffer* ArgumentBuffer, uint32 ArgumentOffset) final override`
- L1065 _public function_ `FORCEINLINE virtual void RHIMultiDrawIndexedPrimitiveIndirect(FRHIBuffer* IndexBuffer, FRHIBuffer* ArgumentBuffer, uint32 ArgumentOffset, FRHIBuffer* CountBuffer, uint32 CountBufferOffset, uint32 MaxDrawArguments) final override`
- L1070 _public function_ `FORCEINLINE virtual void RHIDispatchMeshShader(uint32 ThreadGroupCountX, uint32 ThreadGroupCountY, uint32 ThreadGroupCountZ) final override`
- L1074 _public function_ `FORCEINLINE virtual void RHIDispatchIndirectMeshShader(FRHIBuffer* ArgumentBuffer, uint32 ArgumentOffset) final override`
- L1079 _public function_ `FORCEINLINE virtual void RHISetDepthBounds(float MinDepth, float MaxDepth) final override`
- L1084 _public function_ `FORCEINLINE virtual void RHISetShadingRate(EVRSShadingRate ShadingRate, EVRSRateCombiner Combiner) final override`
- L1089 _public function_ `virtual void RHIBeginRenderPass(const FRHIRenderPassInfo& InInfo, const TCHAR* InName) final override`
- L1094 _public function_ `virtual void RHIEndRenderPass() final override`
- L1100 _public function_ `virtual void RHIExecuteMultiIndirectClusterOperation(const FRayTracingClusterOperationParams& Params) final override`
- L1105 _public function_ `virtual void RHIBuildAccelerationStructures(TConstArrayView<FRayTracingGeometryBuildParams> Params, const FRHIBufferRange& ScratchBufferRange) final override`
- L1114 _public function_ `virtual void RHIBuildAccelerationStructures(TConstArrayView<FRayTracingSceneBuildParams> Params) final override`
- L1119 _public function_ `virtual void RHIRayTraceDispatch(FRHIRayTracingPipelineState* RayTracingPipelineState, FRHIRayTracingShader* RayGenShader, FRHIShaderBindingTable* SBT, const FRayTracingShaderBindings& GlobalResourceBindings, uint32 Width, uint32 Height) final override`
- L1126 _public function_ `virtual void RHIRayTraceDispatchIndirect(FRHIRayTracingPipelineState* RayTracingPipelineState, FRHIRayTracingShader* RayGenShader, FRHIShaderBindingTable* SBT, const FRayTracingShaderBindings& GlobalResourceBindings, FRHIBuffer* ArgumentBuffer, uint32 ArgumentOffset) final override`
- L1133 _public function_ `virtual void RHISetBindingsOnShaderBindingTable(FRHIShaderBindingTable* SBT, FRHIRayTracingPipelineState* Pipeline, uint32 NumBindings, const FRayTracingLocalShaderBindings* Bindings, ERayTracingBindingType BindingType) final override`
- L1138 _public function_ `virtual void RHIBindAccelerationStructureMemory(FRHIRayTracingScene* Scene, FRHIBuffer* Buffer, uint32 BufferOffset) final override`
- L1143 _public function_ `virtual void RHICommitShaderBindingTable(FRHIShaderBindingTable* SBT, FRHIBuffer* InlineBindingDataBuffer) final override`
- L1150 _public function_ `virtual void RHISetGPUMask(FRHIGPUMask InGPUMask) final override`
- L1156 _public function_ `virtual FRHIGPUMask RHIGetGPUMask() const final override`
- L1163 _public function_ `FORCEINLINE void SetPhysicalGPUMask(FRHIGPUMask InGPUMask)` — Sets the mask of which GPUs can be supported, as opposed to the currently active set. RHISetGPUMask checks that the active mask is a subset of the physical mask.
- L1168 _public function_ `FORCEINLINE void SetPhysicalContext(FD3D12CommandContext* Context)`
- L1176 _public function_ `FORCEINLINE FD3D12CommandContext* GetSingleDeviceContext(uint32 GPUIndex) final override`
- L1181 _public function_ `virtual void SetExecutingCommandList(FRHICommandListBase* InCmdList) final override`
- L1191 _private member_ `TStaticArray<FD3D12CommandContext*, MAX_NUM_GPUS> PhysicalContexts;`

#### class `FD3D12ContextArray`  
`class FD3D12ContextArray : public TRHIPipelineArray<FD3D12CommandContextBase*>`  
_L1194-1215_
- inherits: `TRHIPipelineArray<FD3D12CommandContextBase*>`
- L1197 _public function_ `FD3D12ContextArray(FRHIContextArray const& Contexts)`
- L1205 _public function_ `operator FRHIContextArray() const`

#### Free symbols / members of external scopes

- L70 _member_ `FD3D12Resource* RHIObject;` (scope `FD3D12DeferredDeleteObject::__anon4ceecebb010a`)
- L71 _member_ `FD3D12Heap* Heap;` (scope `FD3D12DeferredDeleteObject::__anon4ceecebb010a`)
- L72 _member_ `FD3D12DescriptorHeap* DescriptorHeap;` (scope `FD3D12DeferredDeleteObject::__anon4ceecebb010a`)
- L73 _member_ `ID3D12Object* D3DObject;` (scope `FD3D12DeferredDeleteObject::__anon4ceecebb010a`)
- L75 _member_ `TUniqueFunction<void()>* Func;` (scope `FD3D12DeferredDeleteObject::__anon4ceecebb010a`)
- L80 _member_ `FRHIDescriptorAllocation Allocation;` (scope `FD3D12DeferredDeleteObject::__anon4ceecebb010a::__anon4ceecebb0208`)
- L81 _member_ `ERHIDescriptorTypeMask TypeMask;` (scope `FD3D12DeferredDeleteObject::__anon4ceecebb010a::__anon4ceecebb0208`)
- L82 _member_ `FD3D12Device* Device;` (scope `FD3D12DeferredDeleteObject::__anon4ceecebb010a::__anon4ceecebb0208`)
- L83 _member_ `} DescriptorAllocation;` (scope `FD3D12DeferredDeleteObject::__anon4ceecebb010a`)
- L87 _member_ `FRHIDescriptorHandle Handle;` (scope `FD3D12DeferredDeleteObject::__anon4ceecebb010a::__anon4ceecebb0308`)
- L88 _member_ `FD3D12Device* Device;` (scope `FD3D12DeferredDeleteObject::__anon4ceecebb010a::__anon4ceecebb0308`)
- L89 _member_ `} BindlessDescriptor;` (scope `FD3D12DeferredDeleteObject::__anon4ceecebb010a`)
- L92 _member_ `void* CPUAllocation;` (scope `FD3D12DeferredDeleteObject::__anon4ceecebb010a`)
- L96 _member_ `FD3D12OnlineDescriptorBlock* Block;` (scope `FD3D12DeferredDeleteObject::__anon4ceecebb010a::__anon4ceecebb0408`)
- L97 _member_ `FD3D12OnlineDescriptorManager* Manager;` (scope `FD3D12DeferredDeleteObject::__anon4ceecebb010a::__anon4ceecebb0408`)
- L98 _member_ `} DescriptorBlock;` (scope `FD3D12DeferredDeleteObject::__anon4ceecebb010a`)
- L102 _member_ `FPlatformMemory::FPlatformVirtualMemoryBlock VirtualBlock;` (scope `FD3D12DeferredDeleteObject::__anon4ceecebb010a::__anon4ceecebb0508`)
- L103 _member_ `ETextureCreateFlags Flags;` (scope `FD3D12DeferredDeleteObject::__anon4ceecebb010a::__anon4ceecebb0508`)
- L104 _member_ `uint64 CommittedTextureSize;` (scope `FD3D12DeferredDeleteObject::__anon4ceecebb010a::__anon4ceecebb0508`)
- L105 _member_ `void* RawMemory;` (scope `FD3D12DeferredDeleteObject::__anon4ceecebb010a::__anon4ceecebb0508`)
- L106 _member_ `} VirtualAllocDescriptor;` (scope `FD3D12DeferredDeleteObject::__anon4ceecebb010a`)
- L110 _member_ `FD3D12Texture* Texture;` (scope `FD3D12DeferredDeleteObject::__anon4ceecebb010a::__anon4ceecebb0608`)
- L111 _member_ `alignas(alignof(TUniquePtr<FD3D12LockedResource>)) uint8 LockedResourceStorage[sizeof(TUniquePtr<FD3D12LockedResource>)];` (scope `FD3D12DeferredDeleteObject::__anon4ceecebb010a::__anon4ceecebb0608`)
- L112 _member_ `uint32 Subresource;` (scope `FD3D12DeferredDeleteObject::__anon4ceecebb010a::__anon4ceecebb0608`)
- L113 _member_ `} TextureStagingBufferData;` (scope `FD3D12DeferredDeleteObject::__anon4ceecebb010a`)
- L296 _member_ `TArray<FD3D12SyncPointRef> ToWait;` (scope `FD3D12ContextCommon::__anon4ceecebb0708`)
- L297 _member_ `TArray<FD3D12SyncPointRef> ToSignal;` (scope `FD3D12ContextCommon::__anon4ceecebb0708`)
- L736 _function_ `` (scope `FD3D12CommandContext::RHIEndRenderPass`)
- L903 _macro_ `#define ContextRedirect(Call) { for (uint32 GPUIndex : GPUMask) PhysicalContexts[GPUIndex]-> Call; }`
- L904 _macro_ `#define ContextGPU0(Call) { PhysicalContexts[0]-> Call; }`

### `Source/Runtime/D3D12RHI/Private/D3D12CommandList.h` (Private)


#### class `FD3D12CommandAllocator`  
`class FD3D12CommandAllocator final`  
_L35-56_
- desc: Wraps a D3D command list allocator object. Allocators are obtained from the parent device, and recycled in that device's object pool.
- L39 _private prototype_ `FD3D12CommandAllocator(FD3D12CommandAllocator const&) = delete;`
- L40 _private prototype_ `FD3D12CommandAllocator(FD3D12CommandAllocator&&) = delete;`
- L42 _private prototype_ `FD3D12CommandAllocator(FD3D12Device* Device, ED3D12QueueType QueueType);`
- L45 _public prototype_ `~FD3D12CommandAllocator();`
- L47 _public member_ `FD3D12Device* const Device;`
- L48 _public member_ `ED3D12QueueType const QueueType;`
- L50 _public prototype_ `void Reset();`
- L52 _public function_ `operator ID3D12CommandAllocator*()`
- L55 _private member_ `TRefCountPtr<ID3D12CommandAllocator> CommandAllocator;`

#### class `FD3D12CommandList`  
`class FD3D12CommandList final`  
_L62-317_
- desc: Wraps a D3D command list object. Includes additional data required by the command context and submission thread. Command lists are obtained from the parent device, and recycled in that device's object pool.
- L70 _private prototype_ `FD3D12CommandList(FD3D12CommandList const&) = delete;`
- L71 _private prototype_ `FD3D12CommandList(FD3D12CommandList&&) = delete;`
- L73 _private prototype_ `FD3D12CommandList(FD3D12CommandAllocator* CommandAllocator, FD3D12QueryAllocator* TimestampAllocator, FD3D12QueryAllocator* PipelineStatsAllocator);`
- L75 _private prototype_ `void BeginLocalQueries();`
- L76 _private prototype_ `void EndLocalQueries();`
- L79 _public prototype_ `~FD3D12CommandList();`
- L81 _public prototype_ `void BeginQuery(FD3D12QueryLocation const& Location);`
- L82 _public prototype_ `void EndQuery (FD3D12QueryLocation const& Location);`
- L84 _public prototype_ `void Reset(FD3D12CommandAllocator* CommandAllocator, FD3D12QueryAllocator* TimestampAllocator, FD3D12QueryAllocator* PipelineStatsAllocator);`
- L85 _public prototype_ `void Close();`
- L87 _public function_ `bool IsOpen () const`
- L88 _public function_ `bool IsClosed() const`
- L90 _public function_ `uint32 GetNumCommands() const`
- L92 _public member_ `FD3D12Device* const Device;`
- L93 _public member_ `ED3D12QueueType const QueueType;`
- L96 _private member_ `FD3D12ResidencySet* const ResidencySet;`
- L102 _public prototype_ `void UpdateResidency(const FD3D12Resource* Resource);` — Indicate that a resource must be made resident before execution on GPU. Either immediately adds residency handle for this resource to the residency set or defers it until submission time (residency handles may not be known until then).
- L106 _public prototype_ `void AddToResidencySet(TConstArrayView<FD3D12ResidencyHandle*> Handles);` — Immediately add residency handles to the residency set for this command list.
- L109 _public prototype_ `FD3D12ResidencySet* CloseResidencySet();` — Closes and returns the residency set. Used only during submission.
- L113 _public function_ `template <typename TEventType, typename... TArgs> TEventType& EmplaceProfilerEvent(TArgs&&... Args)`
- L126 _public function_ `void FlushProfilerEvents(UE::RHI::GPUProfiler::FEventStream& Destination, uint64 CPUTimestamp)`
- L183 _private member_ `} Interfaces;`
- L225 _private function_ `template <typename FInterfaceType> auto BuildRValuePtr(TRefCountPtr<FInterfaceType> FInterfaces::* Member)`
- L231 _public function_ `auto BaseCommandList ()`
- L232 _public function_ `auto CopyCommandList ()`
- L233 _public function_ `auto GraphicsCommandList ()`
- L235 _public function_ `auto GraphicsCommandList1 ()`
- L238 _public function_ `auto GraphicsCommandList2 ()`
- L241 _public function_ `auto GraphicsCommandList3 ()`
- L244 _public function_ `auto GraphicsCommandList4 ()`
- L247 _public function_ `auto GraphicsCommandList5 ()`
- L250 _public function_ `auto GraphicsCommandList6 ()`
- L253 _public function_ `auto GraphicsCommandList7 ()`
- L256 _public function_ `auto GraphicsCommandList8 ()`
- L259 _public function_ `auto GraphicsCommandList9 ()`
- L262 _public function_ `auto GraphicsCommandList10()`
- L266 _public function_ `auto DebugCommandList ()`
- L269 _public function_ `auto RayTracingCommandList()`
- L272 _public function_ `auto AftermathHandle ()`
- L276 _private prototype_ `void WriteTimestamp(FD3D12QueryLocation const& Location, ED3D12QueryPosition Position);`
- L316 _private member_ `} State;`

#### struct `FD3D12CommandList::FInterfaces`  
`struct FInterfaces`  
_L137-183_
- L139 _public member_ `TRefCountPtr<ID3D12CommandList> CommandList;`
- L140 _public member_ `TRefCountPtr<ID3D12CopyCommandList> CopyCommandList;`
- L141 _public member_ `TRefCountPtr<ID3D12GraphicsCommandList> GraphicsCommandList;`
- L144 _public member_ `TRefCountPtr<ID3D12GraphicsCommandList1> GraphicsCommandList1;`
- L147 _public member_ `TRefCountPtr<ID3D12GraphicsCommandList2> GraphicsCommandList2;`
- L150 _public member_ `TRefCountPtr<ID3D12GraphicsCommandList3> GraphicsCommandList3;`
- L153 _public member_ `TRefCountPtr<ID3D12GraphicsCommandList4> GraphicsCommandList4;`
- L156 _public member_ `TRefCountPtr<ID3D12GraphicsCommandList5> GraphicsCommandList5;`
- L159 _public member_ `TRefCountPtr<ID3D12GraphicsCommandList6> GraphicsCommandList6;`
- L162 _public member_ `TRefCountPtr<ID3D12GraphicsCommandList7> GraphicsCommandList7;`
- L165 _public member_ `TRefCountPtr<ID3D12GraphicsCommandList8> GraphicsCommandList8;`
- L168 _public member_ `TRefCountPtr<ID3D12GraphicsCommandList9> GraphicsCommandList9;`
- L171 _public member_ `TRefCountPtr<ID3D12GraphicsCommandList10> GraphicsCommandList10;`
- L175 _public member_ `TRefCountPtr<ID3D12DebugCommandList> DebugCommandList;`
- L178 _public member_ `UE::RHICore::Nvidia::Aftermath::D3D12::FCommandList AftermathHandle = nullptr;`
- L181 _public member_ `uint64 IntelCommandListHandle = 0;`

#### class `FD3D12CommandList::TRValuePtr`  
`template <typename T> class TRValuePtr`  
_L192-221_
- desc: Wrapper type to prevent l-value use of the returned command list interfaces. A context's command list may be swapped out during recording. Users should access the command list via the context itself, to ensure they always have the correct command list instance.
- L196 _private member_ `FD3D12CommandList& CommandList;`
- L197 _private member_ `T* Ptr;`
- L199 _private function_ `TRValuePtr(FD3D12CommandList& CommandList, T* Ptr) : CommandList(CommandList) , Ptr(Ptr)`
- L205 _public prototype_ `TRValuePtr() = delete;`
- L207 _public prototype_ `TRValuePtr(TRValuePtr const&) = delete;`
- L208 _public prototype_ `TRValuePtr(TRValuePtr&&) = delete;`
- L210 _public prototype_ `TRValuePtr& operator= (TRValuePtr const&) = delete;`
- L211 _public prototype_ `TRValuePtr& operator= (TRValuePtr&&) = delete;`
- L213 _public function_ `operator bool () const&&`
- L214 _public function_ `bool operator!() const&&`
- L217 _public function_ `T* operator -> () &&` — These accessor functions count useful work on command lists
- L218 _public function_ `T* Get () &&`
- L220 _public function_ `T* GetNoRefCount() &&`

#### struct `FD3D12CommandList::FState`  
`struct FState`  
_L279-316_
- desc: Contents of the state struct are reset when the command list is recycled
- L281 _public prototype_ `FState(FD3D12CommandAllocator* CommandAllocator, FD3D12QueryAllocator* TimestampAllocator, FD3D12QueryAllocator* PipelineStatsAllocator);`
- L284 _public member_ `FD3D12CommandAllocator* CommandAllocator;` — The allocator currently assigned to this command list.
- L288 _public member_ `TArray<D3D12_RESOURCE_BARRIER> ResourceBarriers;` — Tracks all the resources barriers being issued on this command list in order
- L291 _public member_ `FD3D12QueryLocation BeginTimestamp;`
- L292 _public member_ `FD3D12QueryLocation EndTimestamp;`
- L294 _public member_ `FD3D12QueryLocation PipelineStats;`
- L296 _public member_ `TArray<FD3D12QueryLocation> TimestampQueries;`
- L297 _public member_ `TArray<FD3D12QueryLocation> OcclusionQueries;`
- L298 _public member_ `TArray<FD3D12QueryLocation> PipelineStatsQueries;`
- L302 _public member_ `TSet<const FD3D12Resource*> DeferredResidencyUpdateSet;` — Resources whose residency must be updated on the submission thread, as their residency handles are not known during translation. This includes reserved resources that may refer to different heaps at different points on the submission timeline.
- L304 _public member_ `uint32 NumCommands = 0;`
- L306 _public member_ `bool IsClosed = false;`
- L309 _public member_ `bool bLocalQueriesBegun = false;`
- L310 _public member_ `bool bLocalQueriesEnded = false;`
- L313 _public member_ `UE::RHI::GPUProfiler::FEventStream EventStream;`
- L314 _public member_ `TArray<UE::RHI::GPUProfiler::FEvent::FBeginWork*, TInlineAllocator<8>> BeginEvents;`

#### Free symbols / members of external scopes

- L25 _namespace_ `namespace D3DX12Residency`
- L29 _typedef_ `typedef D3DX12Residency::ResidencySet FD3D12ResidencySet;`

### `Source/Runtime/D3D12RHI/Private/D3D12ConstantBuffer.h` (Private)


#### class `FD3D12ConstantBuffer`  
`class FD3D12ConstantBuffer : public FD3D12DeviceChild`  
_L19-76_
- inherits: `FD3D12DeviceChild`
- desc: A D3D constant buffer
- L22 _public prototype_ `FD3D12ConstantBuffer(FD3D12Device* InParent, FD3D12FastConstantAllocator& InAllocator);`
- L23 _public prototype_ `virtual ~FD3D12ConstantBuffer();`
- L31 _public function_ `FORCEINLINE_DEBUGGABLE void UpdateConstant(const uint8* Data, uint16 Offset, uint16 InSize)` — Updates a variable in the constant buffer. @param Data - The data to copy into the constant buffer @param Offset - The offset in the constant buffer to place the data at @param InSize - The size of the data being copied
- L48 _public function_ `FORCEINLINE void Reset()`
- L50 _public prototype_ `bool Version(FD3D12ResourceLocation& BufferOut, bool bDiscardSharedConstants);`
- L53 _public function_ `inline D3D12_CPU_DESCRIPTOR_HANDLE GetOfflineCpuHandle() const`
- L58 _protected member_ `FD3D12ConstantBufferView* View = nullptr;`
- L61 _protected member_ `TArray<uint8> ShadowData;`
- L64 _protected member_ `uint32 CurrentUpdateSize;` — Size of all constants that has been updated since the last call to Commit.
- L70 _protected member_ `uint32 TotalUpdateSize;` — Size of all constants that has been updated since the last Discard. Includes "shared" constants that don't necessarily gets updated between every Commit.
- L73 _protected member_ `bool bIsDirty;` — Indicates that a constant has been updated but this one hasn't been flushed.
- L75 _protected member_ `FD3D12FastConstantAllocator& Allocator;`

#### Free symbols / members of external scopes

- L14 _macro_ `#define GLOBAL_CONSTANT_BUFFER_CHUNK_SIZE 512` — Chunk size for global constant buffer shadow data. Should always be a multiple of 256

### `Source/Runtime/D3D12RHI/Private/D3D12DescriptorCache.h` (Private)


#### class `FD3D12ConservativeMap`  
`template<typename KeyType, typename ValueType> class FD3D12ConservativeMap`  
_L37-99_
- desc: Like a TMap<KeyType, ValueType> Faster lookup performance, but possibly has false negatives
- L40 _public function_ `FD3D12ConservativeMap(uint32 Size)`
- L47 _public function_ `void Add(const KeyType& Key, const ValueType& Value)`
- L58 _public function_ `ValueType* Find(const KeyType& Key)`
- L75 _public function_ `void Reset()`
- L84 _private function_ `uint32 GetIndex(const KeyType& Key)`
- L98 _private member_ `TArray<Entry> Table;`

#### struct `FD3D12ConservativeMap::Entry`  
`struct Entry`  
_L91-96_
- L93 _public member_ `bool Valid;`
- L94 _public member_ `KeyType Key;`
- L95 _public member_ `ValueType Value;`

#### struct `FD3D12SamplerArrayDesc`  
`struct FD3D12SamplerArrayDesc`  
_L101-121_
- L103 _public member_ `uint32 Count;`
- L104 _public member_ `uint16 SamplerID[MAX_SAMPLERS];`
- L106 _public function_ `inline bool operator==(const FD3D12SamplerArrayDesc& rhs) const`

#### struct `FD3D12UniqueSamplerTable`  
`struct FD3D12UniqueSamplerTable`  
_L128-142_
- L130 _public prototype_ `FD3D12UniqueSamplerTable() = default;`
- L131 _public function_ `FD3D12UniqueSamplerTable(FD3D12SamplerArrayDesc KeyIn, D3D12_CPU_DESCRIPTOR_HANDLE* Table)`
- L137 _public member_ `FD3D12SamplerArrayDesc Key{};`
- L138 _public member_ `D3D12_CPU_DESCRIPTOR_HANDLE CPUTable[MAX_SAMPLERS]{};`
- L141 _public member_ `D3D12_GPU_DESCRIPTOR_HANDLE GPUHandle{};` — This will point to the table start in the global heap

#### struct `FD3D12UniqueSamplerTableKeyFuncs`  
`struct FD3D12UniqueSamplerTableKeyFuncs : BaseKeyFuncs<FD3D12UniqueSamplerTable, FD3D12UniqueSamplerTable, false>`  
_L146-172_
- inherits: `BaseKeyFuncs<FD3D12UniqueSamplerTable,FD3D12UniqueSamplerTable,false>`
- L148 _public typedef_ `typedef typename TCallTraits<FD3D12UniqueSamplerTable>::ParamType KeyInitType;`
- L149 _public typedef_ `typedef typename TCallTraits<FD3D12UniqueSamplerTable>::ParamType ElementInitType;`
- L154 _public function_ `static FORCEINLINE KeyInitType GetSetKey(ElementInitType Element)` — @return The key used to index the given element.
- L162 _public function_ `static FORCEINLINE bool Matches(KeyInitType A, KeyInitType B)` — @return True if the keys match.
- L168 _public function_ `static FORCEINLINE uint32 GetKeyHash(KeyInitType Key)` — Calculates a hash index for a key.

#### class `FD3D12OnlineHeap`  
`class FD3D12OnlineHeap : public FD3D12DeviceChild`  
_L177-219_
- inherits: `FD3D12DeviceChild`
- desc: Manages a D3D heap which is GPU visible - base class which can be used by the FD3D12DescriptorCache
- L180 _public prototype_ `FD3D12OnlineHeap(FD3D12Device* Device, bool CanLoopAround);`
- L181 _public prototype_ `virtual ~FD3D12OnlineHeap();`
- L183 _public prototype_ `void CleanupResources();`
- L185 _public function_ `ID3D12DescriptorHeap* GetHeap()`
- L187 _public function_ `FORCEINLINE D3D12_CPU_DESCRIPTOR_HANDLE GetCPUSlotHandle(uint32 Slot) const`
- L188 _public function_ `FORCEINLINE D3D12_GPU_DESCRIPTOR_HANDLE GetGPUSlotHandle(uint32 Slot) const`
- L194 _public prototype_ `bool CanReserveSlots(uint32 NumSlots);` — Call this to reserve descriptor heap slots for use by the command list you are currently recording. This will wait if necessary until slots are free (if they are currently in use by another command list.) If the reservation can be fulfilled, the index of the first reserved slot is returned (all reserved slots are consecutive.) If not, it will throw an exception.
- L195 _public prototype_ `uint32 ReserveSlots(uint32 NumSlotsRequested);`
- L197 _public prototype_ `void SetNextSlot(uint32 NextSlot);`
- L198 _public function_ `uint32 GetNextSlotIndex() const`
- L201 _public prototype_ `virtual bool RollOver() = 0;` — Function which can/should be implemented by the derived classes
- L202 _public function_ `virtual void HeapLoopedAround()`
- L203 _public function_ `virtual void OpenCommandList ()`
- L204 _public function_ `virtual void CloseCommandList()`
- L205 _public function_ `virtual uint32 GetTotalSize()`
- L209 _protected member_ `TRefCountPtr<FD3D12DescriptorHeap> Heap;` — Keeping this ptr around is basically just for lifetime management
- L212 _protected member_ `uint32 NextSlotIndex = 0;` — This index indicate where the next set of descriptors should be placed *if* there's room
- L215 _protected member_ `uint32 FirstUsedSlot = 0;` — Indicates the last free slot marked by the command list being finished
- L218 _protected member_ `const bool bCanLoopAround;` — Does the heap support loop around allocations

#### class `FD3D12GlobalOnlineSamplerHeap`  
`class FD3D12GlobalOnlineSamplerHeap : public FD3D12OnlineHeap`  
_L222-239_
- inherits: `FD3D12OnlineHeap`
- desc: Global sampler heap managed by the device which stored a unique set of sampler sets
- L225 _public prototype_ `FD3D12GlobalOnlineSamplerHeap(FD3D12Device* Device);`
- L227 _public prototype_ `void Init(uint32 TotalSize);`
- L230 _public prototype_ `virtual bool RollOver() final override;` — Override FD3D12OnlineHeap functions
- L232 _public prototype_ `void ConsolidateUniqueSamplerTables(TArrayView<FD3D12UniqueSamplerTable> UniqueTables);`
- L234 _public prototype_ `TSharedPtr<FD3D12SamplerSet> GetUniqueDescriptorTables();`
- L237 _private member_ `TSharedPtr<FD3D12SamplerSet> UniqueDescriptorTables;`
- L238 _private member_ `FRWLock Mutex;`

#### class `FD3D12SubAllocatedOnlineHeap`  
`class FD3D12SubAllocatedOnlineHeap : public FD3D12OnlineHeap`  
_L242-263_
- inherits: `FD3D12OnlineHeap`
- desc: Online heap which can be used by a FD3D12DescriptorCache to manage a block allocated from a GlobalHeap
- L245 _public prototype_ `FD3D12SubAllocatedOnlineHeap(FD3D12DescriptorCache& DescriptorCache, FD3D12CommandContext& Context);`
- L248 _public prototype_ `virtual bool RollOver() final override;` — Override FD3D12OnlineHeap functions
- L249 _public prototype_ `virtual void OpenCommandList() final override;`
- L250 _public function_ `virtual uint32 GetTotalSize() final override`
- L257 _private prototype_ `bool AllocateBlock();` — Allocate a new block from the global heap - return true if allocation succeeds
- L259 _private member_ `FD3D12OnlineDescriptorBlock* CurrentBlock = nullptr;`
- L261 _private member_ `FD3D12DescriptorCache& DescriptorCache;`
- L262 _private member_ `FD3D12CommandContext& Context;`

#### class `FD3D12LocalOnlineHeap`  
`class FD3D12LocalOnlineHeap : public FD3D12OnlineHeap`  
_L269-303_
- inherits: `FD3D12OnlineHeap`
- desc: Online heap which is not shared between multiple FD3D12DescriptorCache. Used as overflow heap when the global heaps are full or don't contain the required data
- L272 _public prototype_ `FD3D12LocalOnlineHeap(FD3D12DescriptorCache& DescriptorCache, FD3D12CommandContext& Context);`
- L275 _public prototype_ `void Init(uint32 InNumDescriptors, ERHIDescriptorHeapType InHeapType);` — Allocate the actual overflow heap
- L278 _public prototype_ `virtual bool RollOver() final override;` — Override FD3D12OnlineHeap functions
- L279 _public prototype_ `virtual void HeapLoopedAround() final override;`
- L280 _public prototype_ `virtual void OpenCommandList () final override;`
- L281 _public prototype_ `virtual void CloseCommandList() final override;`
- L289 _private member_ `TQueue<FSyncPointEntry> SyncPoints;`
- L296 _private member_ `FPoolEntry Entry {};`
- L297 _private member_ `TQueue<FPoolEntry> ReclaimPool;`
- L299 _private member_ `FD3D12DescriptorCache& DescriptorCache;`
- L300 _private member_ `FD3D12CommandContext& Context;`
- L302 _private prototype_ `void RecycleSlots();`

#### struct `FD3D12LocalOnlineHeap::FSyncPointEntry`  
`struct FSyncPointEntry`  
_L284-288_
- L286 _public member_ `FD3D12SyncPointRef SyncPoint;`
- L287 _public member_ `uint32 LastSlotInUse = 0;`

#### struct `FD3D12LocalOnlineHeap::FPoolEntry`  
`struct FPoolEntry`  
_L291-295_
- L293 _public member_ `TRefCountPtr<FD3D12DescriptorHeap> Heap;`
- L294 _public member_ `FD3D12SyncPointRef SyncPoint;`

#### enum `ED3D12SetDescriptorHeapsFlags`  
`enum class ED3D12SetDescriptorHeapsFlags`  
_L305-310_
- L307 _public enumerator_ `None = 0`
- L308 _public enumerator_ `ForceChanged = 1 << 0`
- L309 _public enumerator_ `Bindless = 1 << 1`

#### class `FD3D12DescriptorCache`  
`class FD3D12DescriptorCache : public FD3D12DeviceChild, public FD3D12SingleNodeGPUObject`  
_L313-451_
- inherits: `FD3D12DeviceChild,FD3D12SingleNodeGPUObject`
- L316 _public prototype_ `FD3D12DescriptorCache() = delete;`
- L317 _public prototype_ `FD3D12DescriptorCache(FD3D12CommandContext& Context, FRHIGPUMask Node);`
- L319 _public prototype_ `~FD3D12DescriptorCache();`
- L321 _public function_ `inline FD3D12OnlineHeap* GetCurrentViewHeap() const`
- L322 _public function_ `inline FD3D12OnlineHeap* GetCurrentSamplerHeap() const`
- L324 _public function_ `ID3D12DescriptorHeap* GetLastSetViewHeap() const`
- L327 _public function_ `bool IsHeapSet(ID3D12DescriptorHeap* const pHeap) const` — Checks if the specified descriptor heap has been set on the current command list.
- L335 _public prototype_ `void OpenCommandList();` — Notify the descriptor cache every time you start recording a command list. This sets descriptor heaps on the command list and indicates the current fence value which allows us to avoid querying DX12 for that value thousands of times per frame, which can be costly.
- L336 _public prototype_ `void CloseCommandList();`
- L341 _public prototype_ `void SetVertexBuffers(FD3D12VertexBufferCache& Cache);`
- L342 _public prototype_ `void SetRenderTargets(FD3D12RenderTargetView** RenderTargetViewArray, uint32 Count, FD3D12DepthStencilView* DepthStencilTarget);`
- L344 _public prototype_ `D3D12_GPU_DESCRIPTOR_HANDLE BuildUAVTable(EShaderFrequency ShaderStage, const FD3D12RootSignature* RootSignature, FD3D12UnorderedAccessViewCache& Cache, const UAVSlotMask& SlotsNeededMask, uint32 Count, uint32 &HeapSlot);`
- L345 _public prototype_ `D3D12_GPU_DESCRIPTOR_HANDLE BuildSamplerTable(EShaderFrequency ShaderStage, const FD3D12RootSignature* RootSignature, FD3D12SamplerStateCache& Cache, const SamplerSlotMask& SlotsNeededMask, uint32 Count, uint32& HeapSlot);`
- L346 _public prototype_ `D3D12_GPU_DESCRIPTOR_HANDLE BuildSRVTable(EShaderFrequency ShaderStage, const FD3D12RootSignature* RootSignature, FD3D12ShaderResourceViewCache& Cache, const SRVSlotMask& SlotsNeededMask, uint32 Count, uint32& HeapSlot);`
- L348 _public prototype_ `void SetUAVTable(EShaderFrequency ShaderStage, const FD3D12RootSignature* RootSignature, FD3D12UnorderedAccessViewCache& Cache, uint32 SlotsNeeded, const D3D12_GPU_DESCRIPTOR_HANDLE& BindDescriptor);`
- L349 _public prototype_ `void SetSamplerTable(EShaderFrequency ShaderStage, const FD3D12RootSignature* RootSignature, FD3D12SamplerStateCache& Cache, uint32 SlotsNeeded, const D3D12_GPU_DESCRIPTOR_HANDLE& BindDescriptor);`
- L350 _public prototype_ `void SetSRVTable(EShaderFrequency ShaderStage, const FD3D12RootSignature* RootSignature, FD3D12ShaderResourceViewCache& Cache, uint32 SlotsNeeded, const D3D12_GPU_DESCRIPTOR_HANDLE& BindDescriptor);`
- L352 _public prototype_ `void SetConstantBufferViews(EShaderFrequency ShaderStage, const FD3D12RootSignature* RootSignature, FD3D12ConstantBufferCache& Cache, CBVSlotMask SlotsNeededMask, uint32 Count, uint32& HeapSlot);`
- L353 _public prototype_ `void SetRootConstantBuffers(EShaderFrequency ShaderStage, const FD3D12RootSignature* RootSignature, FD3D12ConstantBufferCache& Cache, CBVSlotMask SlotsNeededMask, FD3D12StateCache* StateCache);`
- L355 _public prototype_ `void PrepareBindlessViews(EShaderFrequency ShaderStage, TConstArrayView<FD3D12ShaderResourceView*> SRVs, TConstArrayView<FD3D12UnorderedAccessView*> UAVs);`
- L357 _public prototype_ `bool HeapRolledOver(ERHIDescriptorHeapType InHeapType);`
- L358 _public prototype_ `void HeapLoopedAround(ERHIDescriptorHeapType InHeapType);`
- L359 _public prototype_ `void Init(uint32 InNumLocalViewDescriptors, uint32 InNumSamplerDescriptors);`
- L361 _public prototype_ `bool SwitchToContextLocalViewHeap();`
- L362 _public prototype_ `bool SwitchToContextLocalSamplerHeap();`
- L363 _public prototype_ `void SwitchToGlobalSamplerHeap();`
- L365 _public prototype_ `void SetExplicitDescriptorCache(FD3D12ExplicitDescriptorCache& ExplicitDescriptorCache);`
- L366 _public prototype_ `void UnsetExplicitDescriptorCache();`
- L368 _public function_ `bool UsingGlobalSamplerHeap() const`
- L373 _public function_ `FD3D12SamplerSet& GetLocalSamplerSet()`
- L380 _public prototype_ `bool SetDescriptorHeaps(ED3D12SetDescriptorHeapsFlags Flags);` — Sets the current descriptor tables on the command list and marks any descriptor tables as dirty if necessary. Returns true if one of the heaps actually changed, false otherwise.
- L384 _public function_ `bool CouldUseBindless() const`
- L385 _public function_ `bool IsFullyBindless() const`
- L387 _public function_ `constexpr bool CouldUseBindless() const`
- L388 _public function_ `constexpr bool IsFullyBindless() const`
- L392 _public function_ `void SetBindlessResourcesHeap(FD3D12DescriptorHeap* InHeap)`
- L397 _public function_ `void SetBindlessSamplersHeap(FD3D12DescriptorHeap* InHeap)`
- L402 _public function_ `FD3D12DescriptorHeap* GetBindlessResourcesHeap() const`
- L407 _public function_ `bool IsUsingBindlessHeap() const`
- L414 _protected member_ `FD3D12CommandContext& Context;`
- L415 _protected member_ `const FD3D12DefaultViews& DefaultViews;`
- L419 _private member_ `ID3D12DescriptorHeap* LastSetViewHeap = nullptr;` — The previous view and sampler heaps set on the current command list.
- L420 _private member_ `ID3D12DescriptorHeap* LastSetSamplerHeap = nullptr;`
- L422 _private member_ `FD3D12OnlineHeap* CurrentViewHeap = nullptr;`
- L423 _private member_ `FD3D12OnlineHeap* CurrentSamplerHeap = nullptr;`
- L425 _private member_ `FD3D12LocalOnlineHeap* LocalViewHeap = nullptr;`
- L426 _private member_ `FD3D12LocalOnlineHeap LocalSamplerHeap;`
- L427 _private member_ `FD3D12SubAllocatedOnlineHeap SubAllocatedViewHeap;`
- L429 _private member_ `FD3D12SamplerMap SamplerMap;`
- L431 _private member_ `TArray<FD3D12UniqueSamplerTable> UniqueTables;`
- L433 _private member_ `TSharedPtr<FD3D12SamplerSet> LocalSamplerSet;`
- L434 _private member_ `bool bUsingExplicitCacheHeaps = false;`
- L435 _private member_ `bool bExplicitViewHeapIsBindless = false;`
- L436 _private member_ `bool bLocalSamplerHeapOpen = false;`
- L437 _private member_ `bool bUsingViewHeap = true;`
- L439 _private member_ `uint32 NumLocalViewDescriptors = 0;`
- L442 _private member_ `bool bCouldUseBindless = false;`
- L443 _private member_ `bool bFullyBindless = false;`
- L445 _private member_ `bool bLastSetHeapsBindless = false;`
- L446 _private member_ `bool bLastSetHeapBeforeExplicitIsBindless = false;`
- L448 _private member_ `FD3D12DescriptorHeapPtr BindlessResourcesHeap = nullptr;`
- L449 _private member_ `FD3D12DescriptorHeapPtr BindlessSamplersHeap = nullptr;`

#### Free symbols / members of external scopes

- L32 _typedef_ `using FD3D12SyncPointRef = TRefCountPtr<FD3D12SyncPoint>;`
- L123 _prototype_ `uint32 GetTypeHash(const D3D12_SAMPLER_DESC& Desc);`
- L124 _prototype_ `uint32 GetTypeHash(const FD3D12SamplerArrayDesc& Key);`
- L126 _typedef_ `typedef FD3D12ConservativeMap<FD3D12SamplerArrayDesc, D3D12_GPU_DESCRIPTOR_HANDLE> FD3D12SamplerMap;`
- L143 _prototype_ `uint32 GetTypeHash(const FD3D12UniqueSamplerTable& Table);`
- L174 _typedef_ `typedef TSet<FD3D12UniqueSamplerTable, FD3D12UniqueSamplerTableKeyFuncs> FD3D12SamplerSet;`
- L311 _prototype_ `ENUM_CLASS_FLAGS(ED3D12SetDescriptorHeapsFlags);`

### `Source/Runtime/D3D12RHI/Private/D3D12DescriptorRange.h` (Private)


#### class `FD3D12DescriptorRange`  
`class FD3D12DescriptorRange : public FRHIDescriptorRange, public FD3D12DeviceChild, public FD3D12LinkedAdapterObject<FD3D12DescriptorRange>`  
_L12-34_
- inherits: `FRHIDescriptorRange,FD3D12DeviceChild,FD3D12LinkedAdapterObject<FD3D12DescriptorRange>`
- L16 _public prototype_ `FD3D12DescriptorRange(FD3D12Device* InParent);` — Constructs an invalid/empty descriptor range. Used as a fallback when allocation fails.
- L17 _public prototype_ `FD3D12DescriptorRange(FD3D12Device* InParent, const FRHIDescriptorRangeDesc& InDesc, TConstArrayView<FRHIDescriptorResource> InResources, FRHIDescriptorAllocation Allocation);`
- L18 _public prototype_ `~FD3D12DescriptorRange();`
- L20 _public prototype_ `FRHIDescriptorRangeShaderData GetShaderData() const override;`
- L22 _public prototype_ `void InitializeResources(TConstArrayView<FRHIDescriptorResource> InResources);`
- L23 _public prototype_ `void UpdateResources(const FRHIContextArray& Contexts, uint32 FirstResourceIndex, TConstArrayView<FRHIDescriptorResource> NewResources);`
- L26 _public prototype_ `void PopulateResidencyViews();` — Rebuilds the cached AllSrvs/AllUavs arrays from the current resource list.
- L28 _public member_ `FRHIDescriptorAllocation Allocation;`
- L32 _public member_ `TArray<FD3D12ShaderResourceView*> AllSrvs;` — Cached D3D12 views for all resources in the range. Rebuilt on create/update via PopulateResidencyViews(). Queued for residency (via QueueBindlessSRVs/UAVs) when the descriptor range is bound to a shader.
- L33 _public member_ `TArray<FD3D12UnorderedAccessView*> AllUavs;`

#### struct `TD3D12ResourceTraits`  
`template<> struct TD3D12ResourceTraits<FRHIDescriptorRange>`  
_L37-40_
- L39 _public typedef_ `using TConcreteType = FD3D12DescriptorRange;`

### `Source/Runtime/D3D12RHI/Private/D3D12Descriptors.h` (Private)


#### enum `ED3D12DescriptorHeapFlags`  
`enum class ED3D12DescriptorHeapFlags : uint8`  
_L64-69_
- L66 _public enumerator_ `None = 0`
- L67 _public enumerator_ `GpuVisible = 1 << 0`
- L68 _public enumerator_ `Poolable = 1 << 1`

#### struct `FD3D12DescriptorHeap`  
`struct FD3D12DescriptorHeap : public FD3D12DeviceChild, public FRefCountedObject`  
_L99-163_
- inherits: `FD3D12DeviceChild,FRefCountedObject`
- L102 _public prototype_ `FD3D12DescriptorHeap() = delete;`
- L105 _public prototype_ `FD3D12DescriptorHeap(FD3D12Device* InDevice, TRefCountPtr<ID3D12DescriptorHeap>&& InHeap, uint32 InNumDescriptors, ERHIDescriptorHeapType InType, ED3D12DescriptorHeapFlags InFlags, bool bInIsGlobal);` — Heap created with its own D3D heap object.
- L108 _public prototype_ `FD3D12DescriptorHeap(FD3D12DescriptorHeap* SubAllocateSourceHeap, uint32 InOffset, uint32 InNumDescriptors);` — Heap created as a suballocation of another heap.
- L111 _public prototype_ `FD3D12DescriptorHeap(FD3D12DescriptorManager* Manager, uint32 InOffset, uint32 InNumDescriptors);` — Heap created as an allocation from a descriptor manager.
- L113 _public prototype_ `~FD3D12DescriptorHeap();`
- L115 _public function_ `ID3D12DescriptorHeap* GetHeap() const`
- L116 _public function_ `ERHIDescriptorHeapType GetType() const`
- L117 _public function_ `ED3D12DescriptorHeapFlags GetFlags() const`
- L119 _public function_ `ERHIDescriptorTypeMask GetDescriptorTypeMask() const`
- L124 _public function_ `uint32 GetOffset() const`
- L125 _public function_ `uint32 GetNumDescriptors() const`
- L126 _public function_ `uint32 GetDescriptorSize() const`
- L127 _public function_ `bool IsGlobal() const`
- L128 _public function_ `bool IsSuballocation() const`
- L130 _public function_ `uint32 GetMemorySize() const`
- L132 _public function_ `D3D12_CPU_DESCRIPTOR_HANDLE GetCPUSlotHandle(uint32 Slot) const`
- L133 _public function_ `D3D12_GPU_DESCRIPTOR_HANDLE GetGPUSlotHandle(uint32 Slot) const`
- L135 _public function_ `bool CanBePooled() const`
- L138 _private member_ `TRefCountPtr<ID3D12DescriptorHeap> Heap;`
- L141 _private member_ `FD3D12DescriptorManager* Manager = nullptr;` — Manager this heap is a suballocation of, if any.
- L143 _private member_ `const CD3DX12_CPU_DESCRIPTOR_HANDLE CpuBase;`
- L144 _private member_ `const CD3DX12_GPU_DESCRIPTOR_HANDLE GpuBase;`
- L147 _private member_ `const uint32 Offset = 0;` — Offset in descriptors into the heap, only used when heap is suballocated.
- L150 _private member_ `const uint32 NumDescriptors;` — Total number of descriptors in this heap.
- L153 _private member_ `const uint32 DescriptorSize;` — Device provided size of each descriptor in this heap.
- L155 _private member_ `const ERHIDescriptorHeapType Type;`
- L156 _private member_ `const ED3D12DescriptorHeapFlags Flags;`
- L159 _private member_ `const bool bIsGlobal;` — Enabled if this heap is the "global" heap.
- L162 _private member_ `const bool bIsSuballocation;` — Enabled if this heap was allocated inside another heap.

#### class `FD3D12DescriptorManager`  
`class FD3D12DescriptorManager : public FD3D12DeviceChild, public FRHIHeapDescriptorAllocator`  
_L167-197_
- inherits: `FD3D12DeviceChild,FRHIHeapDescriptorAllocator`
- desc: Manager for resource descriptor allocations.
- L170 _public prototype_ `FD3D12DescriptorManager() = delete;`
- L171 _public prototype_ `FD3D12DescriptorManager(FD3D12Device* Device, FD3D12DescriptorHeap* InHeap, TConstArrayView<TStatId> InStats);`
- L172 _public prototype_ `~FD3D12DescriptorManager();`
- L174 _public function_ `inline FD3D12DescriptorHeap* GetHeap()`
- L175 _public function_ `inline const FD3D12DescriptorHeap* GetHeap() const`
- L177 _public prototype_ `FD3D12DescriptorHeap* AllocateSubheap(uint32 InNumDescriptors);`
- L178 _public prototype_ `void FreeSubheap(FD3D12DescriptorHeap* InHeap);`
- L180 _public function_ `bool HandlesHeapAllocationsWithFlags(ERHIDescriptorHeapType InHeapType, ED3D12DescriptorHeapFlags InHeapFlags) const`
- L185 _public function_ `bool HandlesAllocationWithFlags(ERHIDescriptorType InDescriptorType, ED3D12DescriptorHeapFlags InHeapFlags) const`
- L190 _public function_ `inline bool IsHeapAChild(const FD3D12DescriptorHeap* InHeap)`
- L196 _private member_ `FD3D12DescriptorHeapPtr Heap;`

#### struct `FD3D12OnlineDescriptorBlock`  
`struct FD3D12OnlineDescriptorBlock`  
_L200-212_
- desc: Heap sub block of an online heap
- L202 _public prototype_ `FD3D12OnlineDescriptorBlock() = delete;`
- L203 _public function_ `FD3D12OnlineDescriptorBlock(uint32 InBaseSlot, uint32 InSize) : BaseSlot(InBaseSlot) , Size(InSize)`
- L209 _public member_ `uint32 BaseSlot;`
- L210 _public member_ `uint32 Size;`
- L211 _public member_ `uint32 SizeUsed = 0;`

#### class `FD3D12OnlineDescriptorManager`  
`class FD3D12OnlineDescriptorManager : public FD3D12DeviceChild`  
_L215-244_
- inherits: `FD3D12DeviceChild`
- desc: Primary online heap from which sub blocks can be allocated and freed. Used when allocating blocks of descriptors for tables.
- L218 _public prototype_ `FD3D12OnlineDescriptorManager(FD3D12Device* Device);`
- L219 _public prototype_ `~FD3D12OnlineDescriptorManager();`
- L222 _public prototype_ `void Init(uint32 InTotalSize, uint32 InBlockSize, bool bBindlessResources);` — Setup the actual heap
- L223 _public prototype_ `void CleanupResources();`
- L226 _public prototype_ `FD3D12OnlineDescriptorBlock* AllocateHeapBlock();` — Allocate an available sub heap block from the global heap
- L227 _public prototype_ `void FreeHeapBlock(FD3D12OnlineDescriptorBlock* InHeapBlock);`
- L229 _public function_ `ID3D12DescriptorHeap* GetHeap(ERHIPipeline Pipeline)`
- L230 _public function_ `FD3D12DescriptorHeap* GetDescriptorHeap(ERHIPipeline Pipeline)`
- L232 _public function_ `D3D12_CPU_DESCRIPTOR_HANDLE GetCPUSlotHandle(ERHIPipeline Pipeline, FD3D12OnlineDescriptorBlock* InBlock) const`
- L233 _public function_ `D3D12_GPU_DESCRIPTOR_HANDLE GetGPUSlotHandle(ERHIPipeline Pipeline, FD3D12OnlineDescriptorBlock* InBlock) const`
- L236 _public prototype_ `void Recycle(FD3D12OnlineDescriptorBlock* Block);` — Called by the EOP task to recycle blocks
- L239 _private member_ `TRHIPipelineArray<FD3D12DescriptorHeapPtr> Heaps;`
- L241 _private member_ `TQueue<FD3D12OnlineDescriptorBlock*> FreeBlocks;`
- L243 _private member_ `FCriticalSection CriticalSection;`

#### struct `FD3D12OfflineHeapFreeRange`  
`struct FD3D12OfflineHeapFreeRange`  
_L246-250_
- L248 _public member_ `size_t Start;`
- L249 _public member_ `size_t End;`

#### struct `FD3D12OfflineHeapEntry`  
`struct FD3D12OfflineHeapEntry`  
_L252-262_
- L254 _public function_ `FD3D12OfflineHeapEntry(FD3D12DescriptorHeap* InHeap, const D3D12_CPU_DESCRIPTOR_HANDLE& InHeapBase, size_t InSize) : Heap(InHeap)`
- L260 _public member_ `TRefCountPtr<FD3D12DescriptorHeap> Heap;`
- L261 _public member_ `TDoubleLinkedList<FD3D12OfflineHeapFreeRange> FreeList;`

#### struct `FD3D12OfflineDescriptor`  
`struct FD3D12OfflineDescriptor : public D3D12_CPU_DESCRIPTOR_HANDLE`  
_L264-279_
- inherits: `D3D12_CPU_DESCRIPTOR_HANDLE`
- L267 _public function_ `operator bool () const`
- L268 _public function_ `FD3D12OfflineDescriptor()`
- L272 _public function_ `void IncrementVersion()` — Descriptor version can be used to invalidate any caches that are based on D3D12_CPU_DESCRIPTOR_HANDLE, for example to detect when a view has been updated following a resource rename.
- L273 _public function_ `uint32 GetVersion() const`
- L277 _private member_ `uint32 HeapIndex = 0;`
- L278 _private member_ `uint32 Version = 0;`

#### class `FD3D12OfflineDescriptorManager`  
`class FD3D12OfflineDescriptorManager : public FD3D12DeviceChild`  
_L282-307_
- inherits: `FD3D12DeviceChild`
- desc: Manages and allows allocations of CPU descriptors only. Creates small heaps on demand to satisfy allocations.
- L285 _public prototype_ `FD3D12OfflineDescriptorManager() = delete;`
- L286 _public prototype_ `FD3D12OfflineDescriptorManager(FD3D12Device* InDevice, ERHIDescriptorHeapType InHeapType);`
- L287 _public prototype_ `~FD3D12OfflineDescriptorManager();`
- L289 _public function_ `inline ERHIDescriptorHeapType GetHeapType() const`
- L291 _public prototype_ `FD3D12OfflineDescriptor AllocateHeapSlot();`
- L292 _public prototype_ `void FreeHeapSlot(FD3D12OfflineDescriptor& Descriptor);`
- L294 _public prototype_ `void CleanupResources();`
- L297 _private prototype_ `void AllocateHeap();`
- L299 _private member_ `TArray<FD3D12OfflineHeapEntry> Heaps;`
- L300 _private member_ `TDoubleLinkedList<uint32> FreeHeaps;`
- L302 _private member_ `ERHIDescriptorHeapType HeapType;`
- L303 _private member_ `uint32 NumDescriptorsPerHeap{};`
- L304 _private member_ `uint32 DescriptorSize{};`
- L306 _private member_ `FCriticalSection CriticalSection;`

#### class `FD3D12DescriptorHeapManager`  
`class FD3D12DescriptorHeapManager : public FD3D12DeviceChild`  
_L311-348_
- inherits: `FD3D12DeviceChild`
- desc: Primary descriptor heap and descriptor manager. All heap allocations come from here. All GPU visible resource heap allocations will be sub-allocated from a single heap in this manager.
- L314 _public prototype_ `FD3D12DescriptorHeapManager(FD3D12Device* InDevice);`
- L315 _public prototype_ `~FD3D12DescriptorHeapManager();`
- L317 _public prototype_ `void Init(uint32 InNumGlobalResourceDescriptors, uint32 InNumGlobalSamplerDescriptors);`
- L318 _public prototype_ `void Destroy();`
- L320 _public prototype_ `FD3D12DescriptorHeap* AllocateIndependentHeap(const TCHAR* InDebugName, ERHIDescriptorHeapType InHeapType, uint32 InNumDescriptors, ED3D12DescriptorHeapFlags InHeapFlags);`
- L321 _public prototype_ `FD3D12DescriptorHeap* AllocateHeap(const TCHAR* InDebugName, ERHIDescriptorHeapType InHeapType, uint32 InNumDescriptors, ED3D12DescriptorHeapFlags InHeapFlags);`
- L322 _public prototype_ `void DeferredFreeHeap(FD3D12DescriptorHeap* InHeap);`
- L324 _public prototype_ `void AddHeapToPool(TRefCountPtr<ID3D12DescriptorHeap>&& InHeap, ERHIDescriptorHeapType InType, uint32 InNumDescriptors, ED3D12DescriptorHeapFlags InFlags);`
- L327 _private prototype_ `TRefCountPtr<ID3D12DescriptorHeap> AcquirePooledHeap(ERHIDescriptorHeapType InType, uint32 InNumDescriptors, ED3D12DescriptorHeapFlags InFlags);`
- L329 _private member_ `TArray<FD3D12DescriptorManager, TFixedAllocator<2>> GlobalHeaps;` — Use TFixedAllocator to prevent move of CRITICAL_SECTION
- L346 _private member_ `TArray<FPooledHeap> PooledHeaps;`
- L347 _private member_ `FCriticalSection PooledHeapsCS;`

#### struct `FD3D12DescriptorHeapManager::FPooledHeap`  
`struct FPooledHeap`  
_L331-345_
- L333 _public function_ `FPooledHeap(TRefCountPtr<ID3D12DescriptorHeap>&& InHeap, ERHIDescriptorHeapType InType, uint32 InNumDescriptors, ED3D12DescriptorHeapFlags InFlags) : Heap(Forward<TRefCountPtr<ID3D12DescriptorHeap>>(InHeap)) , NumDescriptors(InNumDescriptors) , Type(InType) , Flags(InFlags)`
- L341 _public member_ `TRefCountPtr<ID3D12DescriptorHeap> Heap;`
- L342 _public member_ `uint32 NumDescriptors;`
- L343 _public member_ `ERHIDescriptorHeapType Type;`
- L344 _public member_ `ED3D12DescriptorHeapFlags Flags;`

#### Free symbols / members of external scopes

- L20 _function_ `inline D3D12_DESCRIPTOR_HEAP_TYPE Translate(ERHIDescriptorHeapType InHeapType)`
- L32 _function_ `inline D3D12_DESCRIPTOR_HEAP_TYPE Translate(ERHIDescriptorType InDescriptorType)`
- L49 _function_ `inline ERHIDescriptorTypeMask D3D12DescriptorTypeMaskFromHeapType(ERHIDescriptorHeapType InHeapType)`
- L70 _function_ `ENUM_CLASS_FLAGS(ED3D12DescriptorHeapFlags) inline D3D12_DESCRIPTOR_HEAP_FLAGS Translate(ED3D12DescriptorHeapFlags InHeapFlags)`
- L82 _typedef_ `using FD3D12DescriptorIndex = uint32;`
- L84 _namespace_ `namespace UE`
- L84 _namespace_ `namespace D3D12Descriptors` (scope `UE`)
- L86 _prototype_ `FD3D12DescriptorHeap* CreateDescriptorHeap(FD3D12Device* Device, const TCHAR* DebugName, ERHIDescriptorHeapType HeapType, uint32 NumDescriptors, ED3D12DescriptorHeapFlags Flags, bool bGlobal = false);` (scope `UE::D3D12Descriptors`)
- L88 _prototype_ `void CopyDescriptor(FD3D12Device* Device, FD3D12DescriptorHeap* TargetHeap, FD3D12DescriptorIndex DstIndex, D3D12_CPU_DESCRIPTOR_HANDLE SrcCpuHandle);` (scope `UE::D3D12Descriptors`)
- L89 _prototype_ `void CopyDescriptor(FD3D12Device* Device, FD3D12DescriptorHeap* TargetHeap, FRHIDescriptorHandle DstHandle, D3D12_CPU_DESCRIPTOR_HANDLE SrcCpuHandle);` (scope `UE::D3D12Descriptors`)
- L91 _prototype_ `void CopyDescriptors(FD3D12Device* Device, FD3D12DescriptorHeap* TargetHeap, FD3D12DescriptorHeap* SourceHeap, uint32 FirstDescriptor, uint32 NumDescriptors);` (scope `UE::D3D12Descriptors`)
- L92 _prototype_ `void CopyDescriptors(FD3D12Device* Device, FD3D12DescriptorHeap* TargetHeap, FD3D12DescriptorHeap* SourceHeap, TConstArrayView<FD3D12DescriptorIndex> Indices);` (scope `UE::D3D12Descriptors`)
- L94 _prototype_ `FD3D12OfflineDescriptor CreateOfflineCopy(FD3D12Device* Device, D3D12_CPU_DESCRIPTOR_HANDLE InDescriptor, ERHIDescriptorHeapType InType);` (scope `UE::D3D12Descriptors`)
- L95 _prototype_ `FD3D12OfflineDescriptor CreateOfflineCopy(FD3D12Device* Device, FD3D12DescriptorHeap* InHeap, FRHIDescriptorHandle InHandle);` (scope `UE::D3D12Descriptors`)
- L96 _prototype_ `void FreeOfflineCopy(FD3D12Device* Device, FD3D12OfflineDescriptor& InDescriptor, ERHIDescriptorHeapType InType);` (scope `UE::D3D12Descriptors`)
- L164 _typedef_ `using FD3D12DescriptorHeapPtr = TRefCountPtr<FD3D12DescriptorHeap>;`

### `Source/Runtime/D3D12RHI/Private/D3D12Device.h` (Private)


#### class `FD3D12DiagnosticBuffer`  
`class FD3D12DiagnosticBuffer : public FRHIDiagnosticBuffer`  
_L37-65_
- inherits: `FRHIDiagnosticBuffer`
- desc: Diagnostic buffer, backed by a virtual heap. Stays accessible after a GPU crash to allow readback of diagnostic messages. Also used to track the progress of the GPU via breadcrumb markers.
- L41 _private member_ `TRefCountPtr<FD3D12Heap> Heap;`
- L42 _private member_ `TRefCountPtr<FD3D12Resource> Resource;`
- L44 _private member_ `D3D12_GPU_VIRTUAL_ADDRESS GpuAddress = 0;`
- L45 _private function_ `D3D12_GPU_VIRTUAL_ADDRESS ToGPUAddress(void* Ptr) const`
- L51 _public prototype_ `FD3D12DiagnosticBuffer(FD3D12Queue& Queue);`
- L52 _public prototype_ `~FD3D12DiagnosticBuffer();`
- L54 _public function_ `D3D12_GPU_VIRTUAL_ADDRESS GetGPUQueueData () const`
- L57 _public function_ `D3D12_GPU_VIRTUAL_ADDRESS GetGPUQueueMarkerIn () const`
- L58 _public function_ `D3D12_GPU_VIRTUAL_ADDRESS GetGPUQueueMarkerOut() const`
- L60 _public function_ `uint32 ReadMarkerIn () const`
- L61 _public function_ `uint32 ReadMarkerOut() const`
- L64 _public function_ `bool IsValid() const`

#### class `FD3D12Timing`  
`class FD3D12Timing`  
_L68-81_
- desc: Encapsulates the state required for tracking GPU queue performance across a frame.
- L71 _public member_ `FD3D12Queue& Queue;`
- L72 _public member_ `D3D12_QUERY_DATA_PIPELINE_STATISTICS PipelineStats {};`
- L75 _public member_ `uint64 GPUFrequency = 0, GPUTimestamp = 0;` — Timer calibration data
- L75 _public member_ `uint64 GPUFrequency = 0, GPUTimestamp = 0;` — Timer calibration data
- L76 _public member_ `uint64 CPUFrequency = 0, CPUTimestamp = 0;`
- L76 _public member_ `uint64 CPUFrequency = 0, CPUTimestamp = 0;`
- L78 _public member_ `UE::RHI::GPUProfiler::FEventStream EventStream;`
- L80 _public prototype_ `FD3D12Timing(FD3D12Queue& Queue);`

#### class `FD3D12Queue`  
`class FD3D12Queue final`  
_L85-151_
- desc: Encapsulates a single D3D command queue, and maintains the state required by the submission thread for managing the queue.
- L88 _public prototype_ `void CleanupResources();`
- L90 _public member_ `FD3D12Device* const Device;`
- L91 _public member_ `ED3D12QueueType const QueueType;`
- L92 _public member_ `int32 const QueueIndex;`
- L95 _public member_ `TRefCountPtr<ID3D12CommandQueue> D3DCommandQueue;` — The underlying D3D queue object
- L98 _public member_ `FD3D12Fence Fence;` — A single D3D fence to manage completion of work on this queue
- L100 _public member_ `TMpscQueue<FD3D12Payload*> PendingSubmission;`
- L101 _public member_ `TSpscQueue<FD3D12Payload*> PendingInterrupt;`
- L103 _public member_ `FD3D12Payload* PayloadToSubmit = nullptr;`
- L104 _public member_ `FD3D12CommandAllocator* BarrierAllocator = nullptr;`
- L105 _public member_ `FD3D12QueryAllocator BarrierTimestamps;`
- L107 _public member_ `FD3D12BatchedPayloadObjects BatchedObjects;`
- L115 _public member_ `} ObjectPool;`
- L118 _public member_ `FD3D12Timing* Timing = nullptr;` — The active timing struct on this queue. Updated / accessed by the interrupt thread.
- L120 _public member_ `TUniquePtr<FD3D12DiagnosticBuffer> DiagnosticBuffer;`
- L123 _public member_ `FD3D12Buffer* RayTracingDispatchRaysDescBuffer = nullptr;`
- L127 _public member_ `bool bSupportsTileMapping = true;` — On some hardware, some auxiliary queue types may not support tile mapping and a separate queue must be used
- L129 _public member_ `static constexpr uint32 MaxBatchedPayloads = 128;`
- L130 _public typedef_ `using FPayloadArray = TArray<FD3D12Payload*, TInlineAllocator<MaxBatchedPayloads>>;`
- L133 _public prototype_ `uint64 FinalizePayload(bool bRequiresSignal, FPayloadArray& PayloadsToHandDown);` — Batches the current payload's command lists, returning the latest fence value signaled for this queue.
- L136 _public prototype_ `void ExecuteCommandLists(TArrayView<ID3D12CommandList*> D3DCommandLists #if ENABLE_RESIDENCY_MANAGEMENT , TArrayView<FD3D12ResidencySet*> ResidencySets #endif );` — Call the underlying ID3D12Queue::ExecuteCommandLists function
- L142 _public prototype_ `FD3D12Queue(FD3D12Device* Device, ED3D12QueueType QueueType, int32 QueueIndex);`
- L143 _public prototype_ `~FD3D12Queue();`
- L145 _public prototype_ `UE::RHI::GPUProfiler::FQueue GetProfilerQueue() const;`
- L149 _private member_ `FD3D12Fence ExecuteCommandListsFence;` — Internal fence which may be used before calling ExecuteCommandLists

#### struct `FD3D12Queue::(anonymous)`  
``  
_L111-115_

#### class `FD3D12Device`  
`class FD3D12Device final : public FD3D12SingleNodeGPUObject, public FNoncopyable, public FD3D12AdapterChild`  
_L153-336_
- inherits: `FD3D12SingleNodeGPUObject,FNoncopyable,FD3D12AdapterChild`
- L156 _public prototype_ `FD3D12Device(FRHIGPUMask InGPUMask, FD3D12Adapter* InAdapter);`
- L157 _public prototype_ `~FD3D12Device();`
- L159 _public prototype_ `ID3D12Device* GetDevice();`
- L161 _public prototype_ `uint64 GetTimestampFrequency(ED3D12QueueType QueueType);`
- L164 _public prototype_ `void BlockUntilIdle();` — Misc
- L165 _public prototype_ `D3D12_RESOURCE_ALLOCATION_INFO GetResourceAllocationInfoUncached(const FD3D12ResourceDesc& InDesc);`
- L166 _public prototype_ `D3D12_RESOURCE_ALLOCATION_INFO GetResourceAllocationInfo(const FD3D12ResourceDesc& InDesc);`
- L169 _public prototype_ `static void CopyDescriptors(ID3D12Device* D3DDevice, D3D12_CPU_DESCRIPTOR_HANDLE Destination, const D3D12_CPU_DESCRIPTOR_HANDLE* Source, uint32 NumSourceDescriptors, D3D12_DESCRIPTOR_HEAP_TYPE Type);` — Specialized wrapper of ID3D12Device::CopyDescriptors for a common case of a single descriptor range. Similar to CopyDescriptorsSimple(), except source is provided as an array.
- L170 _public function_ `void CopyDescriptors(D3D12_CPU_DESCRIPTOR_HANDLE Destination, const D3D12_CPU_DESCRIPTOR_HANDLE* Source, uint32 NumSourceDescriptors, D3D12_DESCRIPTOR_HEAP_TYPE Type)`
- L175 _public prototype_ `void InitExplicitDescriptorHeap();`
- L176 _public function_ `FD3D12ExplicitDescriptorHeapCache* GetExplicitDescriptorHeapCache()`
- L180 _public prototype_ `void InitRayTracing();`
- L181 _public prototype_ `void CleanupRayTracing();`
- L183 _public function_ `FD3D12RayTracingPipelineCache* GetRayTracingPipelineCache ()`
- L184 _public function_ `FD3D12Buffer* GetRayTracingDispatchRaysDescBuffer (ED3D12QueueType QueueType)`
- L185 _public function_ `FD3D12RayTracingCompactionRequestHandler* GetRayTracingCompactionRequestHandler()`
- L187 _public prototype_ `TRefCountPtr<ID3D12StateObject> DeserializeRayTracingStateObject(D3D12_SHADER_BYTECODE Bytecode, ID3D12RootSignature* RootSignature);`
- L189 _public prototype_ `void GetRaytracingAccelerationStructurePrebuildInfo( const D3D12_BUILD_RAYTRACING_ACCELERATION_STRUCTURE_INPUTS* pDesc, D3D12_RAYTRACING_ACCELERATION_STRUCTURE_PREBUILD_INFO* pInfo);`
- L194 _public prototype_ `bool GetRayTracingPipelineInfo(ID3D12StateObject* Pipeline, FD3D12RayTracingPipelineInfo* OutInfo);` — Queries ray tracing pipeline state object metrics such as VGPR usage (if available/supported). Returns true if query succeeded.
- L198 _public function_ `inline FD3D12GlobalOnlineSamplerHeap& GetGlobalSamplerHeap()` — Heaps
- L200 _public function_ `inline const D3D12_HEAP_PROPERTIES& GetConstantBufferPageProperties()`
- L203 _public function_ `inline FD3D12DescriptorHeapManager& GetDescriptorHeapManager ()` — Descriptor Managers
- L205 _public function_ `FD3D12BindlessDescriptorAllocator& GetBindlessDescriptorAllocator()`
- L206 _public function_ `FD3D12BindlessDescriptorManager& GetBindlessDescriptorManager()`
- L208 _public function_ `inline FD3D12OnlineDescriptorManager& GetOnlineDescriptorManager ()`
- L209 _public function_ `inline FD3D12OfflineDescriptorManager& GetOfflineDescriptorManager (ERHIDescriptorHeapType InType)`
- L215 _public function_ `const FD3D12DefaultViews& GetDefaultViews() const`
- L218 _public function_ `inline FD3D12DefaultBufferAllocator& GetDefaultBufferAllocator()` — Memory Allocators
- L219 _public function_ `inline FD3D12FastAllocator& GetDefaultFastAllocator ()`
- L220 _public function_ `inline FD3D12TextureAllocatorPool& GetTextureAllocator ()`
- L223 _public function_ `inline FD3D12ResidencyManager& GetResidencyManager()` — Residency
- L226 _public prototype_ `FD3D12SamplerState* CreateSampler(const FSamplerStateInitializerRHI& Initializer, FD3D12SamplerState* FirstLinkedObject);` — Samplers
- L227 _public prototype_ `void CreateSamplerInternal(const D3D12_SAMPLER_DESC& Desc, D3D12_CPU_DESCRIPTOR_HANDLE Descriptor);`
- L230 _public prototype_ `FD3D12CommandAllocator* ObtainCommandAllocator (ED3D12QueueType QueueType);` — Command Allocators
- L231 _public prototype_ `void ReleaseCommandAllocator(FD3D12CommandAllocator* Allocator);`
- L234 _public function_ `FD3D12CommandContext& GetDefaultCommandContext()` — Contexts
- L235 _public prototype_ `FD3D12ContextCommon* ObtainContext (ED3D12QueueType QueueType);`
- L236 _public function_ `FD3D12ContextCopy* ObtainContextCopy ()`
- L237 _public function_ `FD3D12CommandContext* ObtainContextCompute ()`
- L238 _public function_ `FD3D12CommandContext* ObtainContextGraphics ()`
- L239 _public prototype_ `void ReleaseContext (FD3D12ContextCommon* Context);`
- L242 _public prototype_ `TRefCountPtr<FD3D12QueryHeap> ObtainQueryHeap (ED3D12QueueType QueueType, D3D12_QUERY_TYPE QueryType);` — Queries
- L243 _public prototype_ `void ReleaseQueryHeap(FD3D12QueryHeap* QueryHeap);`
- L246 _public prototype_ `FD3D12CommandList* ObtainCommandList (FD3D12CommandAllocator* CommandAllocator, FD3D12QueryAllocator* TimestampAllocator, FD3D12QueryAllocator* PipelineStatsAllocator);` — Command Lists
- L247 _public prototype_ `void ReleaseCommandList(FD3D12CommandList* CommandList);`
- L250 _public function_ `FD3D12Queue& GetQueue(ED3D12QueueType QueueType)` — Queues
- L251 _public function_ `TArrayView<FD3D12Queue> GetQueues()`
- L255 _public prototype_ `void SetupAfterDeviceCreation();` — shared code for different D3D12  devices (e.g. PC DirectX12 and XboxOne) called after device creation and GRHISupportsAsyncTextureCreation was set and before resource init
- L256 _public prototype_ `void CleanupResources();`
- L259 _public prototype_ `HRESULT CreateCommandList( UINT nodeMask, D3D12_COMMAND_LIST_TYPE type, ID3D12CommandAllocator* pCommandAllocator, ID3D12PipelineState* pInitialState, REFIID riid, void** ppCommandList );` — Wrapper of ID3D12Device::CreateCommandList
- L269 _public prototype_ `void CreateUnorderedAccessViewAlias( ID3D12Resource* InResource, ID3D12Resource* InCounterResource, const D3D12_RESOURCE_DESC& InAliasResourceDesc, const D3D12_UNORDERED_ACCESS_VIEW_DESC& InAliasViewDesc, D3D12_CPU_DESCRIPTOR_HANDLE InOfflineCpuHandle);`
- L277 _public member_ `TRefCountPtr<ID3D12CommandQueue> TileMappingQueue;`
- L278 _public member_ `FD3D12Fence TileMappingFence;`
- L282 _private prototype_ `void CreateDefaultViews();` — called by SetupAfterDeviceCreation() when the device gets initialized
- L283 _private prototype_ `void UpdateMSAASettings();`
- L284 _private prototype_ `void UpdateConstantBufferPageProperties();`
- L290 _private member_ `} ResidencyManager;`
- L292 _private member_ `FD3D12DescriptorHeapManager DescriptorHeapManager;`
- L294 _private member_ `FD3D12BindlessDescriptorAllocator& BindlessDescriptorAllocator;`
- L295 _private member_ `FD3D12BindlessDescriptorManager BindlessDescriptorManager;`
- L297 _private member_ `TArray<FD3D12OfflineDescriptorManager, TFixedAllocator<(uint32)ERHIDescriptorHeapType::Count>> OfflineDescriptorManagers;`
- L299 _private member_ `FD3D12GlobalOnlineSamplerHeap GlobalSamplerHeap;`
- L300 _private member_ `FD3D12OnlineDescriptorManager OnlineDescriptorManager;`
- L302 _private member_ `FD3D12DefaultViews DefaultViews;`
- L304 _private member_ `TStaticArray<TD3D12ObjectPool<FD3D12QueryHeap>, 4> QueryHeapPool { InPlace };`
- L306 _private member_ `FD3D12CommandContext* ImmediateCommandContext = nullptr;`
- L308 _private member_ `TArray<FD3D12Queue, TFixedAllocator<(uint32)ED3D12QueueType::Count>> Queues;`
- L310 _private member_ `TLruCache<D3D12_SAMPLER_DESC, TRefCountPtr<FD3D12SamplerState>> SamplerCache;`
- L311 _private member_ `uint32 SamplerID = 0;`
- L314 _private member_ `FRWLock ResourceAllocationInfoMapMutex;` — Hashmap used to cache resource allocation size information
- L315 _private member_ `TMap<uint64, D3D12_RESOURCE_ALLOCATION_INFO> ResourceAllocationInfoMap;`
- L319 _private member_ `uint32 AvailableMSAAQualities[DX_MAX_MSAA_COUNT + 1];` — set by UpdateMSAASettings(), get by GetMSAAQuality() [SampleCount] = Quality, 0xffffffff if not supported
- L322 _private member_ `D3D12_HEAP_PROPERTIES ConstantBufferPageProperties;` — set by UpdateConstantBufferPageProperties, get by GetConstantBufferPageProperties
- L324 _private member_ `FD3D12DefaultBufferAllocator DefaultBufferAllocator;`
- L325 _private member_ `FD3D12FastAllocator DefaultFastAllocator;`
- L326 _private member_ `FD3D12TextureAllocatorPool TextureAllocator;`
- L329 _private member_ `FD3D12RayTracingPipelineCache* RayTracingPipelineCache = nullptr;`
- L330 _private member_ `FD3D12RayTracingCompactionRequestHandler* RayTracingCompactionRequestHandler = nullptr;`
- L334 _private member_ `FD3D12ExplicitDescriptorHeapCache* ExplicitDescriptorHeapCache = nullptr;`
- L335 _private prototype_ `void DestroyExplicitDescriptorCache();`

#### struct `FD3D12Device::FResidencyManager`  
`struct FResidencyManager : public FD3D12ResidencyManager`  
_L286-290_
- inherits: `FD3D12ResidencyManager`
- L288 _public prototype_ `FResidencyManager(FD3D12Device& Parent);`
- L289 _public prototype_ `~FResidencyManager();`

#### Free symbols / members of external scopes

- L112 _member_ `TD3D12ObjectPool<FD3D12ContextCommon > Contexts;` (scope `FD3D12Queue::__anon71d08ac70108`)
- L113 _member_ `TD3D12ObjectPool<FD3D12CommandAllocator> Allocators;` (scope `FD3D12Queue::__anon71d08ac70108`)
- L114 _member_ `TD3D12ObjectPool<FD3D12CommandList > Lists;` (scope `FD3D12Queue::__anon71d08ac70108`)

### `Source/Runtime/D3D12RHI/Private/D3D12DirectCommandListManager.h` (Private)


#### class `FD3D12ManualFence`  
`class FD3D12ManualFence final`  
_L17-51_
- desc: A fence that is manually signaled on the graphics pipe (all graphics pipes in mGPU setups). @todo: Remove this. Systems that rely on this fence should be converted to use sync points instead.
- L19 _private member_ `FD3D12Adapter* const Parent;`
- L20 _private member_ `TMap<FD3D12Queue*, TRefCountPtr<ID3D12Fence>> Fences;`
- L22 _private member_ `FThreadSafeCounter NextFenceValueTOP = 0;`
- L23 _private member_ `uint64 NextFenceValueBOP = 0;`
- L24 _private member_ `uint64 CompletedFenceValue = 0;`
- L26 _private prototype_ `FD3D12ManualFence(FD3D12ManualFence const&) = delete;`
- L27 _private prototype_ `FD3D12ManualFence(FD3D12ManualFence&&) = delete;`
- L30 _public prototype_ `FD3D12ManualFence(FD3D12Adapter* InParent);`
- L35 _public prototype_ `uint64 GetCompletedFenceValue(bool bUpdateCachedFenceValue);` — Returned the fence value which has been signaled by the GPU. If bUpdateCachedFenceValue is false, only the cached value is returned. Otherwise, the latest fence value is queried from the driver, and the cached value is updated.
- L38 _public function_ `bool IsFenceComplete(uint64 FenceValue, bool bUpdateCachedFenceValue)` — Determines if the given fence value has been signaled on the GPU.
- L44 _public function_ `uint64 GetNextFenceToSignal() const` — Returns the next value to be signaled.
- L49 _public prototype_ `void AdvanceTOP();`
- L50 _public prototype_ `void AdvanceBOP();`

#### Free symbols / members of external scopes

- L13 _externvar_ `extern int32 GEmitRgpFrameMarkers;`

### `Source/Runtime/D3D12RHI/Private/D3D12DiskCache.h` (Private)
_(no declarations extracted)_

### `Source/Runtime/D3D12RHI/Private/D3D12EnhancedBarriers.h` (Private)


#### class `FD3D12EnhancedBarriersForAdapter`  
`class FD3D12EnhancedBarriersForAdapter final : public ID3D12BarriersForAdapter`  
_L74-120_
- inherits: `ID3D12BarriersForAdapter`
- L78 _public prototype_ `virtual ~FD3D12EnhancedBarriersForAdapter();`
- L80 _public prototype_ `virtual void ConfigureDevice( ID3D12Device* Device, bool InWithD3DDebug) const override final;`
- L84 _public prototype_ `virtual uint64 GetTransitionDataSizeBytes() const override final;`
- L85 _public prototype_ `virtual uint64 GetTransitionDataAlignmentBytes() const override final;`
- L87 _public prototype_ `virtual void CreateTransition( FRHITransition* Transition, const FRHITransitionCreateInfo& CreateInfo) const override final;`
- L91 _public prototype_ `virtual void ReleaseTransition( FRHITransition* Transition) const override final;`
- L94 _public prototype_ `virtual HRESULT CreateCommittedResource( FD3D12Adapter& Adapter, const D3D12_HEAP_PROPERTIES& InHeapProps, D3D12_HEAP_FLAGS InHeapFlags, const FD3D12ResourceDesc& InDesc, ED3D12Access InInitialD3D12Access, const D3D12_CLEAR_VALUE* InClearValue, TRefCountPtr<ID3D12Resource>& OutResource) const override final;`
- L103 _public prototype_ `virtual HRESULT CreateReservedResource( FD3D12Adapter& Adapter, const FD3D12ResourceDesc& InDesc, ED3D12Access InInitialD3D12Access, const D3D12_CLEAR_VALUE* InClearValue, TRefCountPtr<ID3D12Resource>& OutResource) const override final;`
- L110 _public prototype_ `virtual HRESULT CreatePlacedResource( FD3D12Adapter& Adapter, ID3D12Heap* Heap, uint64 HeapOffset, const FD3D12ResourceDesc& InDesc, ED3D12Access InInitialD3D12Access, const D3D12_CLEAR_VALUE* InClearValue, TRefCountPtr<ID3D12Resource>& OutResource) const override final;`
- L119 _public prototype_ `virtual const TCHAR* GetImplementationName() const override final;`

#### class `FD3D12EnhancedBarriersForContext`  
`class FD3D12EnhancedBarriersForContext final : public ID3D12BarriersForContext`  
_L122-185_
- inherits: `ID3D12BarriersForContext`
- L126 _public prototype_ `FD3D12EnhancedBarriersForContext();`
- L127 _public prototype_ `virtual ~FD3D12EnhancedBarriersForContext();`
- L129 _public prototype_ `virtual void BeginTransitions( FD3D12CommandContext& Context, TArrayView<const FRHITransition*> Transitions) override final;`
- L133 _public prototype_ `virtual void EndTransitions( FD3D12CommandContext& Context, TArrayView<const FRHITransition*> Transitions) override final;`
- L137 _public prototype_ `virtual void AddGlobalBarrier( FD3D12ContextCommon& Context, ED3D12Access D3D12AccessBefore, ED3D12Access D3D12AccessAfter) override final;`
- L142 _public prototype_ `virtual void AddBarrier( FD3D12ContextCommon& Context, const FD3D12Resource* pResource, ED3D12Access D3D12AccessBefore, ED3D12Access D3D12AccessAfter, uint32 Subresource) override final;`
- L149 _public prototype_ `virtual void FlushIntoCommandList( class FD3D12CommandList& CommandList, class FD3D12QueryAllocator& TimestampAllocator) override final;`
- L153 _public prototype_ `virtual int32 GetNumPendingBarriers() const override final;`
- L168 _private prototype_ `bool AddBarriersForTransitionData( FD3D12CommandContext& Context, const FD3D12EnhancedBarriersTransitionData* InTransitionData, const class VARangeCollection& InVARangesToBeInitialized, EProcessEarlyTransitions InProcessEarlyTransitions, EBarrierPhase InBarrierPhase);`
- L175 _private prototype_ `void AddBarriersForTransitions( FD3D12CommandContext& Context, TArrayView<const FRHITransition*> InTransitions, EBarrierPhase InBarrierPhase);`
- L180 _private prototype_ `static void HandleReservedResourceCommits( FD3D12CommandContext& Context, const FD3D12EnhancedBarriersTransitionData* TransitionData);`
- L184 _private member_ `TUniquePtr<FD3D12EnhancedBarriersBatcher> Batcher;`

#### enum `FD3D12EnhancedBarriersForContext::EProcessEarlyTransitions`  
`enum class EProcessEarlyTransitions : bool`  
_L156-160_
- L158 _public enumerator_ `No = false`
- L159 _public enumerator_ `Yes = true`

#### enum `FD3D12EnhancedBarriersForContext::EBarrierPhase`  
`enum class EBarrierPhase : bool`  
_L162-166_
- L164 _public enumerator_ `Begin`
- L165 _public enumerator_ `End`

#### Free symbols / members of external scopes

- L27 _namespace_ `namespace FD3D12EnhancedBarriersForAdapterImpl`
- L29 _prototype_ `D3D12_BARRIER_LAYOUT GetInitialLayout( ED3D12Access InD3D12Access, const FD3D12ResourceDesc& InDesc);` (scope `FD3D12EnhancedBarriersForAdapterImpl`)
- L33 _prototype_ `void ConfigureDevice( ID3D12Device* Device, bool InWithD3DDebug);` (scope `FD3D12EnhancedBarriersForAdapterImpl`)
- L37 _prototype_ `uint64 GetTransitionDataSizeBytes();` (scope `FD3D12EnhancedBarriersForAdapterImpl`)
- L38 _prototype_ `uint64 GetTransitionDataAlignmentBytes();` (scope `FD3D12EnhancedBarriersForAdapterImpl`)
- L40 _prototype_ `void CreateTransition( FRHITransition* Transition, const FRHITransitionCreateInfo& CreateInfo);` (scope `FD3D12EnhancedBarriersForAdapterImpl`)
- L44 _prototype_ `void ReleaseTransition( FRHITransition* Transition);` (scope `FD3D12EnhancedBarriersForAdapterImpl`)
- L47 _prototype_ `HRESULT CreateCommittedResource( FD3D12Adapter& Adapter, const D3D12_HEAP_PROPERTIES& InHeapProps, D3D12_HEAP_FLAGS InHeapFlags, const FD3D12ResourceDesc& InDesc, ED3D12Access InInitialD3D12Access, const D3D12_CLEAR_VALUE* InClearValue, TRefCountPtr<ID3D12Resource>& OutResource);` (scope `FD3D12EnhancedBarriersForAdapterImpl`)
- L56 _prototype_ `HRESULT CreateReservedResource( FD3D12Adapter& Adapter, const FD3D12ResourceDesc& InDesc, ED3D12Access InInitialD3D12Access, const D3D12_CLEAR_VALUE* InClearValue, TRefCountPtr<ID3D12Resource>& OutResource);` (scope `FD3D12EnhancedBarriersForAdapterImpl`)
- L63 _prototype_ `HRESULT CreatePlacedResource( FD3D12Adapter& Adapter, ID3D12Heap* Heap, uint64 HeapOffset, const FD3D12ResourceDesc& InDesc, ED3D12Access InInitialD3D12Access, const D3D12_CLEAR_VALUE* InClearValue, TRefCountPtr<ID3D12Resource>& OutResource);` (scope `FD3D12EnhancedBarriersForAdapterImpl`)

### `Source/Runtime/D3D12RHI/Private/D3D12ExplicitDescriptorCache.h` (Private)


#### class `FD3D12ExplicitDescriptorHeapCache`  
`class FD3D12ExplicitDescriptorHeapCache : FD3D12DeviceChild`  
_L24-63_
- inherits: `FD3D12DeviceChild`
- desc: #dxr_todo UE-72158: FD3D12Device::GlobalViewHeap/GlobalSamplerHeap should be used instead of ad-hoc heaps here. Unfortunately, this requires a major refactor of how global heaps work. FD3D12CommandContext-s should not get static chunks of the global heap, but instead should dynamically allocate chunks on as-needed basis and release them when possible. This would allow calling code to sub-allocate heap blocks from the same global heap.
- L41 _public function_ `FD3D12ExplicitDescriptorHeapCache(FD3D12Device* Device) : FD3D12DeviceChild(Device)`
- L46 _public prototype_ `~FD3D12ExplicitDescriptorHeapCache();`
- L48 _public prototype_ `FEntry AllocateHeap(D3D12_DESCRIPTOR_HEAP_TYPE Type, uint32 NumDescriptors);`
- L49 _public prototype_ `void DeferredReleaseHeap(FEntry&& Entry);`
- L51 _public prototype_ `void FlushFreeList();`
- L55 _private prototype_ `void ReleaseHeap(FEntry&& Entry);`
- L58 _private prototype_ `void ReleaseStaleEntries(uint32 MaxAgeInFrames, float MaxAgeInSeconds);` — Assumes CriticalSection is already locked
- L60 _private member_ `FCriticalSection CriticalSection;`
- L61 _private member_ `TArray<FEntry> FreeList;`
- L62 _private member_ `uint32 NumAllocatedEntries = 0;`

#### struct `FD3D12ExplicitDescriptorHeapCache::FEntry`  
`struct FEntry`  
_L30-39_
- L32 _public member_ `ID3D12DescriptorHeap* Heap = nullptr;`
- L33 _public member_ `uint32 NumDescriptors = 0;`
- L34 _public member_ `D3D12_DESCRIPTOR_HEAP_TYPE Type = D3D12_DESCRIPTOR_HEAP_TYPE_NUM_TYPES;`
- L37 _public member_ `uint64 LastUsedFrame = 0;` — Information for stale entry release, updated upon adding the entry to the free list
- L38 _public member_ `double LastUsedTime = 0.0;`

#### struct `FD3D12ExplicitDescriptorHeap`  
`struct FD3D12ExplicitDescriptorHeap : public FD3D12DeviceChild`  
_L65-106_
- inherits: `FD3D12DeviceChild`
- L69 _public prototype_ `FD3D12ExplicitDescriptorHeap(FD3D12Device* Device);`
- L70 _public prototype_ `~FD3D12ExplicitDescriptorHeap();`
- L72 _public prototype_ `void Init(uint32 InMaxNumDescriptors, D3D12_DESCRIPTOR_HEAP_TYPE InType);`
- L76 _public prototype_ `int32 Allocate(uint32 InNumDescriptors);` — Returns descriptor heap base index or -1 if allocation is not possible. Thread-safe (uses atomic linear allocation).
- L78 _public prototype_ `void CopyDescriptors(int32 BaseIndex, const D3D12_CPU_DESCRIPTOR_HANDLE* InDescriptors, uint32 InNumDescriptors);`
- L80 _public prototype_ `bool CompareDescriptors(int32 BaseIndex, const D3D12_CPU_DESCRIPTOR_HANDLE* InDescriptors, uint32 InNumDescriptors);`
- L82 _public prototype_ `D3D12_CPU_DESCRIPTOR_HANDLE GetDescriptorCPU(uint32 Index) const;`
- L83 _public prototype_ `D3D12_GPU_DESCRIPTOR_HANDLE GetDescriptorGPU(uint32 Index) const;`
- L86 _public member_ `ID3D12Device* D3DDevice = nullptr;` — Cache D3D device pointer, as it's frequently accessed on the hot path in CopyDescriptors
- L88 _public member_ `D3D12_DESCRIPTOR_HEAP_TYPE Type = D3D12_DESCRIPTOR_HEAP_TYPE_NUM_TYPES;`
- L89 _public member_ `ID3D12DescriptorHeap* D3D12Heap = nullptr;`
- L90 _public member_ `uint32 MaxNumDescriptors = 0;`
- L92 _public member_ `int32 NumAllocatedDescriptors = 0;`
- L95 _public member_ `int32 NumWrittenSamplerDescriptors = 0;` — Marks the valid range of the heap when exhaustive sampler deduplication is enabled. Not used otherwise.
- L97 _public member_ `uint32 DescriptorSize = 0;`
- L98 _public member_ `D3D12_CPU_DESCRIPTOR_HANDLE CPUBase = {};`
- L99 _public member_ `D3D12_GPU_DESCRIPTOR_HANDLE GPUBase = {};`
- L101 _public member_ `FD3D12ExplicitDescriptorHeapCache::FEntry HeapCacheEntry;`
- L103 _public member_ `TArray<D3D12_CPU_DESCRIPTOR_HANDLE> Descriptors;`
- L105 _public member_ `bool bExhaustiveSamplerDeduplication = false;`

#### class `FD3D12ExplicitDescriptorCache`  
`class FD3D12ExplicitDescriptorCache : public FD3D12DeviceChild`  
_L108-198_
- inherits: `FD3D12DeviceChild`
- L114 _public function_ `FD3D12ExplicitDescriptorCache(FD3D12Device* Device, uint32 MaxWorkerCount) : FD3D12DeviceChild(Device) , ViewHeap(Device) , SamplerHeap(Device)`
- L123 _public prototype_ `void Init(uint32 NumConstantDescriptors, uint32 NumViewDescriptors, uint32 NumSamplerDescriptors, ERHIBindlessConfiguration BindlessConfig);`
- L126 _public prototype_ `int32 Allocate(const D3D12_CPU_DESCRIPTOR_HANDLE* Descriptors, uint32 NumDescriptors, D3D12_DESCRIPTOR_HEAP_TYPE Type, uint32 WorkerIndex);` — Returns descriptor heap base index for this descriptor table allocation or -1 if allocation failed.
- L129 _public prototype_ `int32 AllocateDeduplicated(const uint32* DescriptorVersions, const D3D12_CPU_DESCRIPTOR_HANDLE* Descriptors, uint32 NumDescriptors, D3D12_DESCRIPTOR_HEAP_TYPE Type, uint32 WorkerIndex);` — Returns descriptor heap base index for this descriptor table allocation (checking for duplicates and reusing existing tables) or -1 if allocation failed.
- L131 _public member_ `FD3D12ExplicitDescriptorHeap ViewHeap;`
- L132 _public member_ `FD3D12ExplicitDescriptorHeap SamplerHeap;`
- L135 _public member_ `ERHIBindlessConfiguration BindlessConfiguration{};`
- L136 _public member_ `bool bBindless = false;`
- L152 _public typedef_ `using TDescriptorHashMap = Experimental::TSherwoodMap<uint64, int32, TIdentityHash<uint64>>;`
- L180 _public function_ `void ReserveViewDescriptors(uint32 Count, uint32 WorkerIndex)`
- L197 _public member_ `TArray<FWorkerThreadData> WorkerData;`

#### struct `FD3D12ExplicitDescriptorCache::TIdentityHash`  
`template<typename KeyType> struct TIdentityHash`  
_L140-150_
- L142 _public function_ `static FORCEINLINE bool Matches(KeyType A, KeyType B)`
- L146 _public function_ `static FORCEINLINE uint32 GetKeyHash(KeyType Key)`

#### struct `FD3D12ExplicitDescriptorCache::FDescriptorSlotRange`  
`struct FDescriptorSlotRange`  
_L154-178_
- L156 _public prototype_ `FDescriptorSlotRange() = default;`
- L157 _public function_ `FDescriptorSlotRange(int32 BaseIndex, int32 Count) : Begin(BaseIndex) , Cursor(BaseIndex) , End(BaseIndex + Count)`
- L164 _public member_ `int32 Begin = 0;`
- L165 _public member_ `int32 Cursor = 0;`
- L166 _public member_ `int32 End = 0;`
- L168 _public function_ `int32 Allocate(int32 Count)`

#### struct `FD3D12ExplicitDescriptorCache::FWorkerThreadData`  
`struct alignas(PLATFORM_CACHE_LINE_SIZE) FWorkerThreadData`  
_L189-195_
- L191 _public member_ `TDescriptorHashMap ViewDescriptorTableCache;`
- L192 _public member_ `TDescriptorHashMap SamplerDescriptorTableCache;`
- L194 _public member_ `FDescriptorSlotRange ReservedViewDescriptors;`

### `Source/Runtime/D3D12RHI/Private/D3D12IntelExtensions.h` (Private)


#### struct `INTCSupportedVersion`  
`struct INTCSupportedVersion`  
_L15-19_
- L17 _public member_ `INTCExtensionVersion Version;` — Required version
- L18 _public member_ `IConsoleVariable* CVar;` — Console variable that controls this feature

#### Free symbols / members of external scopes

- L10 _externvar_ `extern bool GDX12INTCAtomicUInt64Emulation;`
- L20 _externvar_ `extern INTCExtensionVersion IntelExtensionsVersion;`
- L23 _macro_ `#define INTEL_EXTENSION_VERSION_GENERIC 0 // Generic version for all UE5 targets` — Offsets for the version structure
- L24 _macro_ `#define INTEL_EXTENSION_VERSION_BREADCRUMBS 1 // Intel Breadcrumbs support`
- L26 _prototype_ `bool MatchIntelExtensionVersion(const INTCExtensionVersion& Version);`
- L28 _prototype_ `INTCExtensionContext* CreateIntelExtensionsContext(ID3D12Device* Device, INTCExtensionInfo& INTCExtensionInfo, uint32 DeviceId = 0);`
- L29 _prototype_ `void DestroyIntelExtensionsContext(INTCExtensionContext* IntelExtensionContext);`
- L31 _prototype_ `bool EnableIntelAtomic64Support(INTCExtensionContext* IntelExtensionContext, INTCExtensionInfo& INTCExtensionInfo);`
- L32 _prototype_ `bool TryCheckIntelAsyncCompute(ID3D12Device* Device, uint32 DeviceId, bool &bOutSupported);`
- L35 _namespace_ `namespace UE`
- L35 _namespace_ `namespace RHICore` (scope `UE`)
- L35 _namespace_ `namespace Intel` (scope `UE::RHICore`)
- L35 _namespace_ `namespace GPUCrashDumps` (scope `UE::RHICore::Intel`)
- L35 _namespace_ `namespace D3D12` (scope `UE::RHICore::Intel::GPUCrashDumps`)
- L37 _prototype_ `uint64_t RegisterCommandList( ID3D12CommandList* pCommandList );` (scope `UE::RHICore::Intel::GPUCrashDumps::D3D12`)
- L41 _prototype_ `void BeginBreadcrumb( ID3D12GraphicsCommandList* pCommandList, FRHIBreadcrumbNode* Breadcrumb );` (scope `UE::RHICore::Intel::GPUCrashDumps::D3D12`)
- L42 _prototype_ `void EndBreadcrumb( ID3D12GraphicsCommandList* pCommandList, FRHIBreadcrumbNode* Breadcrumb );` (scope `UE::RHICore::Intel::GPUCrashDumps::D3D12`)

### `Source/Runtime/D3D12RHI/Private/D3D12LegacyBarriers.h` (Private)


#### class `FD3D12LegacyBarriersForAdapter`  
`class FD3D12LegacyBarriersForAdapter final : public ID3D12BarriersForAdapter`  
_L69-115_
- inherits: `ID3D12BarriersForAdapter`
- L73 _public prototype_ `virtual ~FD3D12LegacyBarriersForAdapter();`
- L75 _public prototype_ `virtual void ConfigureDevice( ID3D12Device* Device, bool InWithD3DDebug) const override final;`
- L79 _public prototype_ `virtual uint64 GetTransitionDataSizeBytes() const override final;`
- L80 _public prototype_ `virtual uint64 GetTransitionDataAlignmentBytes() const override final;`
- L82 _public prototype_ `virtual void CreateTransition( FRHITransition* Transition, const FRHITransitionCreateInfo& CreateInfo) const override final;`
- L86 _public prototype_ `virtual void ReleaseTransition( FRHITransition* Transition) const override final;`
- L89 _public prototype_ `virtual HRESULT CreateCommittedResource( FD3D12Adapter& Adapter, const D3D12_HEAP_PROPERTIES& InHeapProps, D3D12_HEAP_FLAGS InHeapFlags, const FD3D12ResourceDesc& InDesc, ED3D12Access InInitialD3D12Access, const D3D12_CLEAR_VALUE* InClearValue, TRefCountPtr<ID3D12Resource>& OutResource) const override final;`
- L98 _public prototype_ `virtual HRESULT CreateReservedResource( FD3D12Adapter& Adapter, const FD3D12ResourceDesc& InDesc, ED3D12Access InInitialD3D12Access, const D3D12_CLEAR_VALUE* InClearValue, TRefCountPtr<ID3D12Resource>& OutResource) const override final;`
- L105 _public prototype_ `virtual HRESULT CreatePlacedResource( FD3D12Adapter& Adapter, ID3D12Heap* Heap, uint64 InHeapOffset, const FD3D12ResourceDesc& InDesc, ED3D12Access InInitialD3D12Access, const D3D12_CLEAR_VALUE* InClearValue, TRefCountPtr<ID3D12Resource>& OutResource) const override final;`
- L114 _public prototype_ `virtual const TCHAR* GetImplementationName() const override final;`

#### class `FD3D12LegacyBarriersForContext`  
`class FD3D12LegacyBarriersForContext final : public ID3D12BarriersForContext`  
_L117-184_
- inherits: `ID3D12BarriersForContext`
- L121 _public prototype_ `FD3D12LegacyBarriersForContext();`
- L122 _public prototype_ `virtual ~FD3D12LegacyBarriersForContext();`
- L124 _public prototype_ `virtual void BeginTransitions( FD3D12CommandContext& Context, TArrayView<const FRHITransition*> Transitions) override final;`
- L128 _public prototype_ `virtual void EndTransitions( FD3D12CommandContext& Context, TArrayView<const FRHITransition*> Transitions) override final;`
- L132 _public prototype_ `virtual void AddGlobalBarrier( FD3D12ContextCommon& Context, ED3D12Access D3D12AccessBefore, ED3D12Access D3D12AccessAfter) override final;`
- L137 _public prototype_ `virtual void AddBarrier( FD3D12ContextCommon& Context, const FD3D12Resource* pResource, ED3D12Access D3D12AccessBefore, ED3D12Access D3D12AccessAfter, uint32 Subresource) override final;`
- L144 _public prototype_ `virtual void FlushIntoCommandList( class FD3D12CommandList& CommandList, class FD3D12QueryAllocator& TimestampAllocator) override final;`
- L148 _public prototype_ `virtual int32 GetNumPendingBarriers() const override final;`
- L153 _private prototype_ `static void HandleReservedResourceCommits( FD3D12CommandContext& Context, const FD3D12LegacyBarriersTransitionData* TransitionData);`
- L157 _private prototype_ `void HandleResourceDiscardTransitions( FD3D12CommandContext& Context, const FD3D12LegacyBarriersTransitionData* TransitionData, TArray<FD3D12DiscardResource>& ResourcesToDiscard);`
- L162 _private prototype_ `void HandleDiscardResources( FD3D12CommandContext& Context, TArrayView<const FRHITransition*> Transitions, bool bIsBeginTransition);`
- L167 _private prototype_ `void HandleTransientAliasing( FD3D12CommandContext& Context, const FD3D12LegacyBarriersTransitionData* TransitionData);`
- L171 _private prototype_ `void HandleResourceTransitions( FD3D12CommandContext& Context, const FD3D12LegacyBarriersTransitionData* TransitionData, bool& bUAVBarrier);`
- L176 _private prototype_ `void TransitionResource( FD3D12ContextCommon& Context, const FD3D12Resource* InResource, D3D12_RESOURCE_STATES InBeforeState, D3D12_RESOURCE_STATES InAfterState, uint32 InSubresourceIndex);`
- L183 _private member_ `const TUniquePtr<FD3D12LegacyBarriersBatcher> Batcher;`

#### Free symbols / members of external scopes

- L22 _namespace_ `namespace FD3D12LegacyBarriersForAdapterImpl`
- L24 _prototype_ `D3D12_RESOURCE_STATES GetInitialState( ED3D12Access InD3D12Access, const FD3D12ResourceDesc& InDesc);` (scope `FD3D12LegacyBarriersForAdapterImpl`)
- L28 _prototype_ `void ConfigureDevice( ID3D12Device* Device, bool InWithD3DDebug);` (scope `FD3D12LegacyBarriersForAdapterImpl`)
- L32 _prototype_ `uint64 GetTransitionDataSizeBytes();` (scope `FD3D12LegacyBarriersForAdapterImpl`)
- L33 _prototype_ `uint64 GetTransitionDataAlignmentBytes();` (scope `FD3D12LegacyBarriersForAdapterImpl`)
- L35 _prototype_ `void CreateTransition( FRHITransition* Transition, const FRHITransitionCreateInfo& CreateInfo);` (scope `FD3D12LegacyBarriersForAdapterImpl`)
- L39 _prototype_ `void ReleaseTransition( FRHITransition* Transition);` (scope `FD3D12LegacyBarriersForAdapterImpl`)
- L42 _prototype_ `HRESULT CreateCommittedResource( FD3D12Adapter& Adapter, const D3D12_HEAP_PROPERTIES& InHeapProps, D3D12_HEAP_FLAGS InHeapFlags, const FD3D12ResourceDesc& InDesc, ED3D12Access InInitialD3D12Access, const D3D12_CLEAR_VALUE* InClearValue, TRefCountPtr<ID3D12Resource>& OutResource);` (scope `FD3D12LegacyBarriersForAdapterImpl`)
- L51 _prototype_ `HRESULT CreateReservedResource( FD3D12Adapter& Adapter, const FD3D12ResourceDesc& InDesc, ED3D12Access InInitialD3D12Access, const D3D12_CLEAR_VALUE* InClearValue, TRefCountPtr<ID3D12Resource>& OutResource);` (scope `FD3D12LegacyBarriersForAdapterImpl`)
- L58 _prototype_ `HRESULT CreatePlacedResource( FD3D12Adapter& Adapter, ID3D12Heap* Heap, uint64 InHeapOffset, const FD3D12ResourceDesc& InDesc, ED3D12Access InInitialD3D12Access, const D3D12_CLEAR_VALUE* InClearValue, TRefCountPtr<ID3D12Resource>& OutResource);` (scope `FD3D12LegacyBarriersForAdapterImpl`)

### `Source/Runtime/D3D12RHI/Private/D3D12NvidiaExtensions.h` (Private)


#### Free symbols / members of external scopes

- L22 _namespace_ `namespace UE`
- L22 _namespace_ `namespace RHICore` (scope `UE`)
- L22 _namespace_ `namespace Nvidia` (scope `UE::RHICore`)
- L22 _namespace_ `namespace Aftermath` (scope `UE::RHICore::Nvidia`)
- L22 _namespace_ `namespace D3D12` (scope `UE::RHICore::Nvidia::Aftermath`)
- L24 _typedef_ `typedef struct GFSDK_Aftermath_ContextHandle__* FCommandList;` (scope `UE::RHICore::Nvidia::Aftermath::D3D12`)
- L25 _typedef_ `typedef struct GFSDK_Aftermath_ResourceHandle__* FResource;` (scope `UE::RHICore::Nvidia::Aftermath::D3D12`)
- L27 _prototype_ `void InitializeDevice(ID3D12Device* RootDevice);` (scope `UE::RHICore::Nvidia::Aftermath::D3D12`)
- L28 _prototype_ `void CreateShaderAssociations(float TimeLimitSeconds, uint32 FrameLimit);` (scope `UE::RHICore::Nvidia::Aftermath::D3D12`)
- L30 _prototype_ `FCommandList RegisterCommandList(ID3D12CommandList* D3DCommandList);` (scope `UE::RHICore::Nvidia::Aftermath::D3D12`)
- L31 _prototype_ `void UnregisterCommandList(FCommandList CommandList);` (scope `UE::RHICore::Nvidia::Aftermath::D3D12`)
- L33 _prototype_ `FResource RegisterResource(ID3D12Resource* D3DResource);` (scope `UE::RHICore::Nvidia::Aftermath::D3D12`)
- L34 _prototype_ `void UnregisterResource(FResource Resource);` (scope `UE::RHICore::Nvidia::Aftermath::D3D12`)
- L37 _prototype_ `void BeginBreadcrumb(FCommandList CommandList, FRHIBreadcrumbNode* Breadcrumb);` (scope `UE::RHICore::Nvidia::Aftermath::D3D12`)
- L38 _prototype_ `void EndBreadcrumb (FCommandList CommandList, FRHIBreadcrumbNode* Breadcrumb);` (scope `UE::RHICore::Nvidia::Aftermath::D3D12`)

### `Source/Runtime/D3D12RHI/Private/D3D12PipelineState.h` (Private)


#### struct `FD3D12_GRAPHICS_PIPELINE_STATE_DESC`  
`struct FD3D12_GRAPHICS_PIPELINE_STATE_DESC`  
_L60-90_
- desc: Graphics pipeline struct that represents the latest versions of PSO subobjects currently supported by the RHI.
- L62 _public member_ `ID3D12RootSignature *pRootSignature;`
- L63 _public member_ `D3D12_SHADER_BYTECODE VS;`
- L64 _public member_ `D3D12_SHADER_BYTECODE MS;`
- L65 _public member_ `D3D12_SHADER_BYTECODE AS;`
- L66 _public member_ `D3D12_SHADER_BYTECODE PS;`
- L67 _public member_ `D3D12_SHADER_BYTECODE GS;`
- L69 _public member_ `D3D12_BLEND_DESC BlendState;`
- L72 _public member_ `uint32 SampleMask;`
- L73 _public member_ `D3D12_RASTERIZER_DESC RasterizerState;`
- L74 _public member_ `D3D12_DEPTH_STENCIL_DESC1 DepthStencilState;`
- L76 _public member_ `D3D12_INPUT_LAYOUT_DESC InputLayout;`
- L77 _public member_ `D3D12_INDEX_BUFFER_STRIP_CUT_VALUE IBStripCutValue;`
- L78 _public member_ `D3D12_PRIMITIVE_TOPOLOGY_TYPE PrimitiveTopologyType;`
- L79 _public member_ `D3D12_RT_FORMAT_ARRAY RTFormatArray;`
- L80 _public member_ `DXGI_FORMAT DSVFormat;`
- L81 _public member_ `DXGI_SAMPLE_DESC SampleDesc;`
- L82 _public member_ `uint32 NodeMask;`
- L83 _public member_ `D3D12_CACHED_PIPELINE_STATE CachedPSO;`
- L84 _public member_ `D3D12_PIPELINE_STATE_FLAGS Flags;`
- L86 _public prototype_ `FD3D12_GRAPHICS_PIPELINE_STATE_STREAM PipelineStateStream() const;`
- L88 _public prototype_ `FD3D12_MESH_PIPELINE_STATE_STREAM MeshPipelineStateStream() const;`

#### struct `FD3D12LowLevelGraphicsPipelineStateDesc`  
`struct FD3D12LowLevelGraphicsPipelineStateDesc`  
_L92-137_
- L94 _public member_ `const FD3D12RootSignature *pRootSignature;`
- L95 _public member_ `FD3D12_GRAPHICS_PIPELINE_STATE_DESC Desc;`
- L96 _public member_ `ShaderBytecodeHash VSHash;`
- L97 _public member_ `ShaderBytecodeHash MSHash;`
- L98 _public member_ `ShaderBytecodeHash ASHash;`
- L99 _public member_ `ShaderBytecodeHash GSHash;`
- L100 _public member_ `ShaderBytecodeHash PSHash;`
- L101 _public member_ `uint32 InputLayoutHash;`
- L102 _public member_ `bool bFromPSOFileCache;`
- L104 _public member_ `SIZE_T CombinedHash;`
- L106 _public function_ `FORCEINLINE bool UsesMeshShaders() const`
- L115 _public member_ `const TArray<FShaderCodeVendorExtension>* VSExtensions;` — TODO: Replace with a global hash lookup to reduce overall footprint? Very few permutations, so a single > 0 u32 hash code would be lower memory usage, and very rarely cause a look up.
- L116 _public member_ `const TArray<FShaderCodeVendorExtension>* MSExtensions;`
- L117 _public member_ `const TArray<FShaderCodeVendorExtension>* ASExtensions;`
- L118 _public member_ `const TArray<FShaderCodeVendorExtension>* GSExtensions;`
- L119 _public member_ `const TArray<FShaderCodeVendorExtension>* PSExtensions;`
- L121 _public function_ `FORCEINLINE bool HasVendorExtensions() const`
- L132 _public function_ `FORCEINLINE FString GetName() const`
- L135 _public prototype_ `void Destroy();`

#### struct `FD3D12_COMPUTE_PIPELINE_STATE_DESC`  
`struct FD3D12_COMPUTE_PIPELINE_STATE_DESC : public D3D12_COMPUTE_PIPELINE_STATE_DESC`  
_L140-143_
- inherits: `D3D12_COMPUTE_PIPELINE_STATE_DESC`
- desc: Compute pipeline struct that represents the latest versions of PSO subobjects currently supported by the RHI.
- L142 _public prototype_ `FD3D12_COMPUTE_PIPELINE_STATE_STREAM PipelineStateStream() const;`

#### struct `FD3D12ComputePipelineStateDesc`  
`struct FD3D12ComputePipelineStateDesc`  
_L145-163_
- L147 _public member_ `const FD3D12RootSignature* pRootSignature;`
- L148 _public member_ `FD3D12_COMPUTE_PIPELINE_STATE_DESC Desc;`
- L149 _public member_ `ShaderBytecodeHash CSHash;`
- L151 _public member_ `SIZE_T CombinedHash;`
- L154 _public member_ `const TArray<FShaderCodeVendorExtension>* Extensions;`
- L155 _public function_ `FORCEINLINE bool HasVendorExtensions() const`
- L158 _public function_ `FORCEINLINE FString GetName() const`
- L161 _public prototype_ `void Destroy();`

#### struct `equality_pipeline_state_desc`  
`template <> struct equality_pipeline_state_desc<FD3D12LowLevelGraphicsPipelineStateDesc>`  
_L181-249_
- L183 _public function_ `bool operator()(const FD3D12LowLevelGraphicsPipelineStateDesc& lhs, const FD3D12LowLevelGraphicsPipelineStateDesc& rhs)`
- L253 _public function_ `bool operator()(const FD3D12ComputePipelineStateDesc& lhs, const FD3D12ComputePipelineStateDesc& rhs)`

#### struct `equality_pipeline_state_desc`  
`template <> struct equality_pipeline_state_desc<FD3D12ComputePipelineStateDesc>`  
_L251-273_
- L183 _public function_ `bool operator()(const FD3D12LowLevelGraphicsPipelineStateDesc& lhs, const FD3D12LowLevelGraphicsPipelineStateDesc& rhs)`
- L253 _public function_ `bool operator()(const FD3D12ComputePipelineStateDesc& lhs, const FD3D12ComputePipelineStateDesc& rhs)`

#### struct `FD3D12PipelineStateWorker`  
`struct FD3D12PipelineStateWorker : public FD3D12AdapterChild, public FNonAbandonableTask`  
_L280-297_
- inherits: `FD3D12AdapterChild,FNonAbandonableTask`
- L282 _public prototype_ `FD3D12PipelineStateWorker(FD3D12Adapter* Adapter, const ComputePipelineCreationArgs& InArgs);`
- L283 _public prototype_ `FD3D12PipelineStateWorker(FD3D12Adapter* Adapter, const GraphicsPipelineCreationArgs& InArgs);`
- L285 _public prototype_ `void DoWork();`
- L287 _public function_ `FORCEINLINE TStatId GetStatId() const`
- L293 _public member_ `} CreationArgs;`
- L295 _public member_ `const bool bIsGraphics;`
- L296 _public member_ `TRefCountPtr<ID3D12PipelineState> PSO;`

#### union `FD3D12PipelineStateWorker::PipelineCreationArgs`  
`union PipelineCreationArgs`  
_L289-293_
- L291 _public member_ `ComputePipelineCreationArgs_POD* ComputeArgs;`
- L292 _public member_ `GraphicsPipelineCreationArgs_POD* GraphicsArgs;`

#### struct `FD3D12PipelineState`  
`struct FD3D12PipelineState : public FD3D12AdapterChild, public FD3D12MultiNodeGPUObject, public FNoncopyable, public UE::Private::FQueryableRefCountedObject`  
_L299-364_
- inherits: `FD3D12AdapterChild,FD3D12MultiNodeGPUObject,FNoncopyable,UE::Private::FQueryableRefCountedObject`
- L302 _public prototype_ `explicit FD3D12PipelineState(FD3D12Adapter* Parent);`
- L303 _public prototype_ `~FD3D12PipelineState();`
- L305 _public prototype_ `void Create(const ComputePipelineCreationArgs& InCreationArgs);`
- L306 _public prototype_ `void CreateAsync(const ComputePipelineCreationArgs& InCreationArgs);`
- L309 _public prototype_ `void Create(const FGraphicsPipelineStateInitializer& Initializer, FD3D12PipelineState* BasePSO);`
- L312 _public prototype_ `void Create(const GraphicsPipelineCreationArgs& InCreationArgs);`
- L313 _public prototype_ `void CreateAsync(const GraphicsPipelineCreationArgs& InCreationArgs);`
- L315 _public function_ `FORCEINLINE bool IsValid()`
- L320 _public function_ `FORCEINLINE ID3D12PipelineState* GetPipelineState()`
- L332 _public function_ `FORCEINLINE uint64 GetContextSortKey() const`
- L337 _public function_ `FORCEINLINE void SetContextSortKey(uint64 InContextSortKey)`
- L342 _public prototype_ `FD3D12PipelineState& operator=(const FD3D12PipelineState& other) = delete;`
- L344 _public prototype_ `static bool UsePSORefCounting();`
- L347 _private prototype_ `ID3D12PipelineState* InternalGetPipelineState();`
- L350 _protected member_ `TRefCountPtr<ID3D12PipelineState> PipelineState;`
- L351 _protected member_ `FAsyncTask<FD3D12PipelineStateWorker>* Worker;`
- L352 _protected member_ `FRWLock GetPipelineStateMutex;`
- L360 _protected member_ `volatile PSOInitState InitState;`
- L363 _protected member_ `uint64 ContextSortKey = 0;` — GRHISupportsPipelineStateSortKey

#### enum `FD3D12PipelineState::PSOInitState`  
`enum class PSOInitState`  
_L354-359_
- L356 _public enumerator_ `Initialized`
- L357 _public enumerator_ `Uninitialized`
- L358 _public enumerator_ `CreationFailed`

#### struct `D3D12ResourceFrameCounter`  
`struct D3D12ResourceFrameCounter`  
_L366-380_
- L368 _public function_ `void Set(uint32_t Frame) const`
- L373 _public function_ `uint32 Get() const`
- L379 _public member_ `mutable std::atomic<uint32> LastUsedFrame{0};` — Note that the frame counter may be updated from any number of threads, and is not entirely synchronized

#### struct `FD3D12PipelineStateCommonData`  
`struct FD3D12PipelineStateCommonData`  
_L382-391_
- L384 _public prototype_ `FD3D12PipelineStateCommonData(const FD3D12RootSignature* InRootSignature, FD3D12PipelineState* InPipelineState);`
- L386 _public member_ `const FD3D12RootSignature* const RootSignature;`
- L388 _public member_ `FD3D12PipelineState* PipelineState;`
- L390 _public member_ `D3D12ResourceFrameCounter FrameCounter;`

#### struct `FD3D12GraphicsPipelineState`  
`struct FD3D12GraphicsPipelineState : public FRHIGraphicsPipelineState, FD3D12PipelineStateCommonData`  
_L393-421_
- inherits: `FRHIGraphicsPipelineState,FD3D12PipelineStateCommonData`
- L395 _public prototype_ `FD3D12GraphicsPipelineState() = delete;`
- L396 _public prototype_ `FD3D12GraphicsPipelineState(const FGraphicsPipelineStateInitializer& Initializer, const FD3D12RootSignature* InRootSignature, FD3D12PipelineState* InPipelineState);`
- L397 _public prototype_ `~FD3D12GraphicsPipelineState();`
- L399 _public function_ `FORCEINLINE FD3D12VertexShader* GetVertexShader() const`
- L400 _public function_ `FORCEINLINE FD3D12PixelShader* GetPixelShader() const`
- L401 _public function_ `FORCEINLINE FD3D12MeshShader* GetMeshShader() const`
- L402 _public function_ `FORCEINLINE FD3D12AmplificationShader* GetAmplificationShader() const`
- L403 _public function_ `FORCEINLINE FD3D12GeometryShader* GetGeometryShader() const`
- L405 _public function_ `FRHIGraphicsShader* GetShader(EShaderFrequency Frequency) const override`
- L418 _public member_ `FGraphicsPipelineStateInitializer PipelineStateInitializer;`
- L419 _public member_ `TStaticArray<uint16, MaxVertexElementCount> StreamStrides;`
- L420 _public member_ `bool bShaderNeedsGlobalConstantBuffer[SF_NumStandardFrequencies];`

#### struct `FD3D12ComputePipelineState`  
`struct FD3D12ComputePipelineState : public FRHIComputePipelineState, FD3D12PipelineStateCommonData`  
_L423-431_
- inherits: `FRHIComputePipelineState,FD3D12PipelineStateCommonData`
- L425 _public prototype_ `FD3D12ComputePipelineState() = delete;`
- L426 _public prototype_ `FD3D12ComputePipelineState(const FComputePipelineStateInitializer& InInitializer, const FD3D12RootSignature* InRootSignature, FD3D12PipelineState* InPipelineState);`
- L427 _public prototype_ `~FD3D12ComputePipelineState();`
- L429 _public member_ `bool bPSOPrecache : 1;`
- L430 _public member_ `bool bShaderNeedsGlobalConstantBuffer : 1;`

#### struct `FInitializerToGPSOMapKey`  
`struct FInitializerToGPSOMapKey`  
_L434-450_
- L436 _public member_ `const FGraphicsPipelineStateInitializer* Initializer;`
- L437 _public member_ `uint32 Hash;`
- L439 _public prototype_ `FInitializerToGPSOMapKey() = default;`
- L441 _public function_ `FInitializerToGPSOMapKey(const FGraphicsPipelineStateInitializer* InInitializer, uint32 InHash) : Initializer(InInitializer), Hash(InHash)`
- L446 _public function_ `inline bool operator==(const FInitializerToGPSOMapKey& Other) const`

#### class `FD3D12PipelineStateCacheBase`  
`class FD3D12PipelineStateCacheBase : public FD3D12AdapterChild`  
_L458-554_
- inherits: `FD3D12AdapterChild`
- L490 _protected typedef_ `template <typename TDesc, typename TValue = FD3D12PipelineState*> using TPipelineCache = TMap<TDesc, TValue, FDefaultSetAllocator, TStateCacheKeyFuncs<TDesc, TValue>>;`
- L492 _protected member_ `TMap<FInitializerToGPSOMapKey, FD3D12GraphicsPipelineState*> InitializerToGraphicsPipelineMap;`
- L493 _protected member_ `TMap<FD3D12ComputeShader*, FD3D12ComputePipelineState*> ComputeShaderToComputePipelineMap;`
- L495 _protected member_ `TPipelineCache<FD3D12LowLevelGraphicsPipelineStateDesc> LowLevelGraphicsPipelineStateCache;`
- L496 _protected member_ `TPipelineCache<FD3D12ComputePipelineStateDesc> ComputePipelineStateCache;`
- L500 _protected member_ `mutable FRWLock InitializerToGraphicsPipelineMapMutex;`
- L501 _protected member_ `mutable FRWLock ComputeShaderToComputePipelineMapMutex;`
- L503 _protected member_ `mutable FRWLock LowLevelGraphicsPipelineStateCacheMutex;`
- L504 _protected member_ `mutable FRWLock ComputePipelineStateCacheMutex;`
- L506 _protected member_ `FRWLock DiskCachesCS;`
- L507 _protected member_ `FDiskCacheInterface DiskCaches[NUM_PSO_CACHE_TYPES];`
- L509 _protected prototype_ `void CleanupPipelineStateCaches();`
- L511 _protected typedef_ `typedef TFunction<void(FD3D12PipelineState**, const FD3D12LowLevelGraphicsPipelineStateDesc&)> FPostCreateGraphicCallback;`
- L512 _protected typedef_ `typedef TFunction<void(FD3D12PipelineState*, const FD3D12ComputePipelineStateDesc&)> FPostCreateComputeCallback;`
- L515 _protected prototype_ `virtual FD3D12GraphicsPipelineState* AddToRuntimeCache(const FGraphicsPipelineStateInitializer& Initializer, uint32 InitializerHash, const FD3D12RootSignature* RootSignature, FD3D12PipelineState* PipelineState);`
- L516 _protected prototype_ `FD3D12ComputePipelineState* AddToRuntimeCache(FD3D12ComputeShader* ComputeShader, FD3D12PipelineState* PipelineState);`
- L519 _protected prototype_ `FD3D12PipelineState* FindInLowLevelCache(const FD3D12LowLevelGraphicsPipelineStateDesc& Desc);`
- L520 _protected prototype_ `FD3D12PipelineState* CreateAndAddToLowLevelCache(const FD3D12LowLevelGraphicsPipelineStateDesc& Desc);`
- L521 _protected prototype_ `void AddToLowLevelCache(const FD3D12LowLevelGraphicsPipelineStateDesc& Desc, FD3D12PipelineState** OutPipelineState, const FPostCreateGraphicCallback& PostCreateCallback);`
- L522 _protected prototype_ `virtual void OnPSOCreated(FD3D12PipelineState* PipelineState, const FD3D12LowLevelGraphicsPipelineStateDesc& Desc) = 0;`
- L524 _protected prototype_ `FD3D12PipelineState* FindInLowLevelCache(const FD3D12ComputePipelineStateDesc& Desc);`
- L525 _protected prototype_ `FD3D12PipelineState* CreateAndAddToLowLevelCache(const FD3D12ComputePipelineStateDesc& Desc);`
- L526 _protected prototype_ `void AddToLowLevelCache(const FD3D12ComputePipelineStateDesc& Desc, FD3D12PipelineState** OutPipelineState, const FPostCreateComputeCallback& PostCreateCallback);`
- L527 _protected prototype_ `virtual void OnPSOCreated(FD3D12PipelineState* PipelineState, const FD3D12ComputePipelineStateDesc& Desc) = 0;`
- L530 _protected prototype_ `FD3D12GraphicsPipelineState* FindInLoadedCache(const FGraphicsPipelineStateInitializer& Initializer, const FD3D12RootSignature* RootSignature, FD3D12LowLevelGraphicsPipelineStateDesc& OutLowLevelDesc);`
- L531 _protected prototype_ `FD3D12GraphicsPipelineState* CreateAndAdd(const FGraphicsPipelineStateInitializer& Initializer, const FD3D12RootSignature* RootSignature, const FD3D12LowLevelGraphicsPipelineStateDesc& LowLevelDesc);`
- L534 _public prototype_ `void RemoveFromLowLevelCache(FD3D12PipelineState* PipelineState, const FGraphicsPipelineStateInitializer& PipelineStateInitializer, const FD3D12RootSignature* RootSignature);`
- L535 _public prototype_ `void RemoveFromLowLevelCache(FD3D12PipelineState* PipelineState, const FD3D12ComputeShader* ComputeShader, const FD3D12RootSignature* RootSignature);`
- L538 _public prototype_ `FD3D12GraphicsPipelineState* FindInRuntimeCache(const FGraphicsPipelineStateInitializer& Initializer, uint32& OutHash);`
- L539 _public prototype_ `FD3D12GraphicsPipelineState* FindInLoadedCache(const FGraphicsPipelineStateInitializer& Initializer, uint32 InitializerHash, const FD3D12RootSignature* RootSignature, FD3D12LowLevelGraphicsPipelineStateDesc& OutLowLevelDesc);`
- L540 _public prototype_ `FD3D12GraphicsPipelineState* CreateAndAdd(const FGraphicsPipelineStateInitializer& Initializer, uint32 InitializerHash, const FD3D12RootSignature* RootSignature, const FD3D12LowLevelGraphicsPipelineStateDesc& LowLevelDesc);`
- L542 _public prototype_ `FD3D12ComputePipelineState* FindInRuntimeCache(const FD3D12ComputeShader* ComputeShader);`
- L544 _public prototype_ `FD3D12ComputePipelineState* FindInLoadedCache(const FComputePipelineStateInitializer& Initializer, const FD3D12RootSignature* RootSignature, FD3D12ComputePipelineStateDesc& OutLowLevelDesc);`
- L545 _public prototype_ `FD3D12ComputePipelineState* CreateAndAdd(const FComputePipelineStateInitializer& Initializer, const FD3D12RootSignature* RootSignature, const FD3D12ComputePipelineStateDesc& LowLevelDesc);`
- L547 _public prototype_ `static uint64 HashPSODesc(const FD3D12LowLevelGraphicsPipelineStateDesc& Desc);`
- L548 _public prototype_ `static uint64 HashPSODesc(const FD3D12ComputePipelineStateDesc& Desc);`
- L550 _public prototype_ `static uint64 HashData(const void* Data, int32 NumBytes);`
- L552 _public prototype_ `FD3D12PipelineStateCacheBase(FD3D12Adapter* InParent);`
- L553 _public prototype_ `virtual ~FD3D12PipelineStateCacheBase();`

#### enum `FD3D12PipelineStateCacheBase::PSO_CACHE_TYPE`  
`enum PSO_CACHE_TYPE`  
_L461-466_
- L463 _public enumerator_ `PSO_CACHE_GRAPHICS`
- L464 _public enumerator_ `PSO_CACHE_COMPUTE`
- L465 _public enumerator_ `NUM_PSO_CACHE_TYPES`

#### struct `FD3D12PipelineStateCacheBase::TStateCacheKeyFuncs`  
`template <typename TDesc, typename TValue> struct TStateCacheKeyFuncs : BaseKeyFuncs<TPair<TDesc, TValue>, TDesc, false>`  
_L469-487_
- inherits: `BaseKeyFuncs<TPair<TDesc,TValue>,TDesc,false>`
- L471 _public typedef_ `typedef typename TTypeTraits<TDesc>::ConstPointerType KeyInitType;`
- L472 _public typedef_ `typedef const TPairInitializer<typename TTypeTraits<TDesc>::ConstInitType, typename TTypeTraits<TValue>::ConstInitType>& ElementInitType;`
- L474 _public function_ `static FORCEINLINE KeyInitType GetSetKey(ElementInitType Element)`
- L478 _public function_ `static FORCEINLINE bool Matches(KeyInitType A, KeyInitType B)`
- L483 _public function_ `static FORCEINLINE uint32 GetKeyHash(KeyInitType Key)`

#### Free symbols / members of external scopes

- L26 _macro_ `#define D3D12RHI_USE_HIGH_LEVEL_PSO_CACHE 0`
- L29 _macro_ `#define D3D12_USE_DERIVED_PSO 0`
- L33 _macro_ `#define D3D12_USE_DERIVED_PSO_SHADER_EXPORTS 0`
- L166 _macro_ `#define PSO_IF_NOT_EQUAL_RETURN_FALSE( value ) if(lhs.value != rhs.value){ return false; }`
- L167 _macro_ `#define PSO_IF_MEMCMP_FAILS_RETURN_FALSE( value ) if(FMemory::Memcmp(&lhs.value, &rhs.value, sizeof(rhs.value)) != 0){ return false; }`
- L168 _macro_ `#define PSO_IF_STRING_COMPARE_FAILS_RETURN_FALSE( value ) \`
- L452 _function_ `inline uint32 GetTypeHash(const FInitializerToGPSOMapKey& Key)`

### `Source/Runtime/D3D12RHI/Private/D3D12PoolAllocator.h` (Private)


#### enum `EResourceAllocationStrategy`  
`enum class EResourceAllocationStrategy`  
_L7-19_
- L13 _public enumerator_ `kPlacedResource` — This strategy uses Placed Resources to sub-allocate a buffer out of an underlying ID3D12Heap. The benefit of this is that each buffer can have it's own resource state and can be treated as any other buffer. The downside of this strategy is the API limitation which enforces the minimum buffer size to 64k leading to large internal fragmentation in the allocator
- L18 _public enumerator_ `kManualSubAllocation` — The alternative is to manually sub-allocate out of a single large buffer which allows block allocation granularity down to 1 byte. However, this strategy is only really valid for buffers which will be treated as read-only after their creation (i.e. most Index and Vertex buffers). This is because the underlying resource can only have one state at a time.

#### struct `FD3D12ResourceInitConfig`  
`struct FD3D12ResourceInitConfig`  
_L23-47_
- desc: All data required to create a pool
- L25 _public function_ `static FD3D12ResourceInitConfig CreateUpload()`
- L35 _public function_ `bool operator==(const FD3D12ResourceInitConfig& InOther) const`
- L43 _public member_ `D3D12_HEAP_TYPE HeapType;`
- L44 _public member_ `D3D12_HEAP_FLAGS HeapFlags;`
- L45 _public member_ `D3D12_RESOURCE_FLAGS ResourceFlags;`
- L46 _public member_ `ED3D12Access InitialD3D12Access;`

#### struct `FD3D12VRAMCopyOperation`  
`struct FD3D12VRAMCopyOperation`  
_L53-69_
- desc: @brief Stores all required data for a VRAM copy operation - doesn't own the resources
- L61 _public member_ `FD3D12Resource* SrcResource;`
- L62 _public member_ `ED3D12Access SrcResourcED3D12Access;`
- L63 _public member_ `uint32 SrcOffset;`
- L64 _public member_ `FD3D12Resource* DstResource;`
- L65 _public member_ `ED3D12Access DstResourcED3D12Access;`
- L66 _public member_ `uint32 DstOffset;`
- L67 _public member_ `uint32 Size;`
- L68 _public member_ `ECopyType CopyType;`

#### enum `FD3D12VRAMCopyOperation::ECopyType`  
`enum ECopyType`  
_L55-59_
- L57 _public enumerator_ `BufferRegion`
- L58 _public enumerator_ `Resource`

#### struct `FD3D12HeapAndOffset`  
`struct FD3D12HeapAndOffset`  
_L72-76_
- desc: Heap and offset combined to specific location of a resource
- L74 _public member_ `FD3D12Heap* Heap;`
- L75 _public member_ `uint64 Offset;`

#### class `FD3D12MemoryPool`  
`class FD3D12MemoryPool : public FRHIMemoryPool, public FD3D12DeviceChild, public FD3D12MultiNodeGPUObject`  
_L86-119_
- inherits: `FRHIMemoryPool,FD3D12DeviceChild,FD3D12MultiNodeGPUObject`
- desc: @brief D3D12 specific implementation of the FRHIMemoryPool
- L91 _public prototype_ `FD3D12MemoryPool(FD3D12Device* ParentDevice, FRHIGPUMask VisibleNodes, const FD3D12ResourceInitConfig& InInitConfig, const FString& Name, EResourceAllocationStrategy InAllocationStrategy, int16 InPoolIndex, uint64 InPoolSize, uint32 InPoolAlignment, ERHIPoolResourceTypes InSupportedResourceTypes, EFreeListOrder InFreeListOrder, HeapId InTraceParentHeapId);` — Constructor
- L93 _public prototype_ `virtual ~FD3D12MemoryPool();`
- L96 _public prototype_ `virtual void Init() override;` — Setup/Shutdown
- L97 _public prototype_ `virtual void Destroy() override;`
- L99 _public function_ `FD3D12Resource* GetBackingResource()`
- L100 _public function_ `FD3D12Heap* GetBackingHeap()`
- L102 _public function_ `uint64 GetLastUsedFrameFence() const`
- L103 _public function_ `void UpdateLastUsedFrameFence(uint64 InFrameFence)`
- L107 _protected member_ `const FD3D12ResourceInitConfig InitConfig;`
- L108 _protected member_ `const FString Name;`
- L109 _protected member_ `EResourceAllocationStrategy AllocationStrategy;`
- L112 _protected member_ `TRefCountPtr<FD3D12Resource> BackingResource;` — Actual D3D resource - either resource or heap (see EResourceAllocationStrategy)
- L113 _protected member_ `TRefCountPtr<FD3D12Heap> BackingHeap;`
- L115 _protected member_ `uint64 LastUsedFrameFence;`
- L118 _private member_ `HeapId TraceHeapId;`

#### class `FD3D12PoolAllocator`  
`class FD3D12PoolAllocator : public FRHIPoolAllocator, public FD3D12DeviceChild, public FD3D12MultiNodeGPUObject, public ID3D12ResourceAllocator`  
_L129-240_
- inherits: `FRHIPoolAllocator,FD3D12DeviceChild,FD3D12MultiNodeGPUObject,ID3D12ResourceAllocator`
- desc: @brief D3D12 specific implementation of the FRHIPoolAllocator
- L134 _public prototype_ `FD3D12PoolAllocator(FD3D12Device* ParentDevice, FRHIGPUMask VisibleNodes, const FD3D12ResourceInitConfig& InInitConfig, const FString& InName, EResourceAllocationStrategy InAllocationStrategy, uint64 InDefaultPoolSize, uint32 InPoolAlignment, uint32 InMaxAllocationSize, FRHIMemoryPool::EFreeListOrder InFreeListOrder, bool bInDefragEnabled, HeapId InTraceParentHeapId, ERHIPoolAllocationStrategy InPoolAllocationStrategy, uint16 InOverFlowPoolsCount);` — Constructor
- L136 _public prototype_ `~FD3D12PoolAllocator();`
- L139 _public prototype_ `bool SupportsAllocation(D3D12_HEAP_TYPE InHeapType, D3D12_RESOURCE_FLAGS InResourceFlags, EBufferUsageFlags InBufferUsage, ED3D12ResourceStateMode InResourceStateMode, uint32 Alignment) const;` — Function names currently have to match with FD3D12DefaultBufferPool until we can make full replacement of the allocator
- L140 _public prototype_ `void AllocDefaultResource( D3D12_HEAP_TYPE InHeapType, const FD3D12ResourceDesc& InDesc, EBufferUsageFlags InBufferUsage, ED3D12ResourceStateMode InResourceStateMode, ED3D12Access InCreateD3D12Access, uint32 InAlignment, const TCHAR* InName, FD3D12ResourceLocation& ResourceLocation);`
- L149 _public prototype_ `virtual void DeallocateResource(FD3D12ResourceLocation& ResourceLocation, bool bDefragFree = false);`
- L152 _public prototype_ `virtual void AllocateResource( uint32 GPUIndex, D3D12_HEAP_TYPE InHeapType, const FD3D12ResourceDesc& InDesc, uint64 InSize, uint32 InAllocationAlignment, ED3D12Access InInitialD3D12Access, ED3D12ResourceStateMode InResourceStateMode, ED3D12Access InDefaultD3D12Access, const D3D12_CLEAR_VALUE* InClearValue, const TCHAR* InName, FD3D12ResourceLocation& ResourceLocation) override;` — Implementation of ID3D12ResourceAllocator
- L165 _public prototype_ `void CleanUpAllocations(uint64 InFrameLag, bool bForceFree = false);`
- L166 _public prototype_ `void FlushPendingCopyOps(FD3D12CommandContext& InCommandContext);`
- L168 _public prototype_ `void TransferOwnership(FD3D12ResourceLocation& InSource, FD3D12ResourceLocation& InDest);`
- L169 _public function_ `bool IsOwner(FD3D12ResourceLocation& ResourceLocation) const`
- L171 _public function_ `EResourceAllocationStrategy GetAllocationStrategy() const`
- L172 _public prototype_ `FD3D12Resource* GetBackingResource(FD3D12ResourceLocation& InResourceLocation) const;`
- L173 _public prototype_ `FD3D12HeapAndOffset GetBackingHeapAndAllocationOffsetInBytes(FD3D12ResourceLocation& InResourceLocation) const;`
- L174 _public prototype_ `FD3D12HeapAndOffset GetBackingHeapAndAllocationOffsetInBytes(const FRHIPoolAllocationData& InAllocationData) const;`
- L175 _public function_ `uint64 GetPendingDeleteRequestSize() const`
- L177 _public prototype_ `static FD3D12ResourceInitConfig GetResourceAllocatorInitConfig(D3D12_HEAP_TYPE InHeapType, D3D12_RESOURCE_FLAGS InResourceFlags, EBufferUsageFlags InBufferUsage);`
- L178 _public prototype_ `static EResourceAllocationStrategy GetResourceAllocationStrategy(D3D12_RESOURCE_FLAGS InResourceFlags, ED3D12ResourceStateMode InResourceStateMode, uint32 Alignment);`
- L183 _protected prototype_ `virtual FRHIMemoryPool* CreateNewPool(int16 InPoolIndex, uint32 InMinimumAllocationSize, ERHIPoolResourceTypes InAllocationResourceType) override;` — Implementation of FRHIPoolAllocator pure virtuals
- L184 _protected prototype_ `virtual bool HandleDefragRequest(FRHIContextArray const& Contexts, FRHIPoolAllocationData* InSourceBlock, FRHIPoolAllocationData& InTmpTargetBlock) override;`
- L187 _protected prototype_ `virtual FD3D12Resource* CreatePlacedResource( const FRHIPoolAllocationData& InAllocationData, const FD3D12ResourceDesc& InDesc, ED3D12Access InInitialD3D12Access, ED3D12ResourceStateMode InResourceStateMode, ED3D12Access InDefaultD3D12Access, const D3D12_CLEAR_VALUE* InClearValue, const TCHAR* InName);` — Placed resource allocation helper function which can be overriden
- L203 _protected prototype_ `virtual void UpdateAllocationTracking(FD3D12ResourceLocation& InAllocation, EAllocationType InAllocationType);`
- L222 _protected member_ `const FD3D12ResourceInitConfig InitConfig;`
- L223 _protected member_ `const FString Name;`
- L224 _protected member_ `EResourceAllocationStrategy AllocationStrategy;`
- L227 _protected member_ `TArray<FrameFencedAllocationData> FrameFencedOperations;` — All operations which need to happen on specific frame fences
- L230 _protected member_ `uint64 PendingDeleteRequestSize = 0;` — Size of all pending delete requests in the frame fence operation array
- L233 _protected member_ `TArray<FD3D12VRAMCopyOperation> PendingCopyOps;` — Pending copy ops which need to be flush this frame
- L236 _protected member_ `TArray<FRHIPoolAllocationData*> AllocationDataPool;` — Allocation data pool used to reduce allocation overhead
- L239 _private member_ `HeapId TraceHeapId;`

#### enum `FD3D12PoolAllocator::EAllocationType`  
`enum class EAllocationType`  
_L197-202_
- desc: Track the allocation
- L199 _public enumerator_ `Allocate` — Update tracking data on allocation
- L200 _public enumerator_ `DefragFree` — Update tracking data on free during defrag op
- L201 _public enumerator_ `Free` — Update tracking data when resource is actually freed

#### struct `FD3D12PoolAllocator::FrameFencedAllocationData`  
`struct FrameFencedAllocationData`  
_L206-220_
- desc: Locked allocation data which needs to do something specific at certain frame fence value
- L216 _public member_ `EOperation Operation = EOperation::Invalid;`
- L217 _public member_ `FD3D12Resource* PlacedResource = nullptr;`
- L218 _public member_ `uint64 FrameFence = 0;`
- L219 _public member_ `FRHIPoolAllocationData* AllocationData = nullptr;`

#### enum `FD3D12PoolAllocator::FrameFencedAllocationData::EOperation`  
`enum class EOperation`  
_L208-214_
- L210 _public enumerator_ `Invalid`
- L211 _public enumerator_ `Deallocate`
- L212 _public enumerator_ `Unlock`
- L213 _public enumerator_ `Nop`

### `Source/Runtime/D3D12RHI/Private/D3D12Query.h` (Private)


#### enum `ED3D12QueryType`  
`enum class ED3D12QueryType`  
_L14-28_
- L16 _public enumerator_ `None`
- L17 _public enumerator_ `PipelineStats`
- L18 _public enumerator_ `TimestampMicroseconds`
- L19 _public enumerator_ `TimestampRaw`
- L22 _public enumerator_ `ProfilerTimestampTOP` — Top-of-pipe GPU timestamp, converted to the CPU clock domain (i.e. relative to FPlatformTime::Cycles64())
- L25 _public enumerator_ `ProfilerTimestampBOP` — Bottom-of-pipe GPU timestamp, converted to the CPU clock domain (i.e. relative to FPlatformTime::Cycles64())
- L27 _public enumerator_ `Occlusion`

#### enum `ED3D12QueryPosition`  
`enum class ED3D12QueryPosition`  
_L30-37_
- L33 _public enumerator_ `TopOfPipe` — Query result should be written before any future command list work is started.
- L36 _public enumerator_ `BottomOfPipe` — Query result should be written after all prior command list work has completed.

#### class `FD3D12QueryHeap`  
`class FD3D12QueryHeap final : public FD3D12SingleNodeGPUObject`  
_L41-94_
- inherits: `FD3D12SingleNodeGPUObject`
- desc: Wraps an ID3D12QueryHeap and its readback buffer. Used by command contexts to create timestamp and occlusion queries. Ref-counting is used to recycle the heaps on parent device when all refering command lists have completed on the GPU.
- L44 _private member_ `static constexpr uint32 MaxHeapSize = 65536;` — All query heaps are allocated to fill a single 64KB page
- L50 _private prototype_ `FD3D12QueryHeap(FD3D12QueryHeap const&) = delete;`
- L51 _private prototype_ `FD3D12QueryHeap(FD3D12QueryHeap&&) = delete;`
- L53 _private prototype_ `FD3D12QueryHeap(FD3D12Device* Device, D3D12_QUERY_TYPE QueryType, D3D12_QUERY_HEAP_TYPE HeapType);`
- L56 _public prototype_ `~FD3D12QueryHeap();`
- L58 _public member_ `FD3D12Device* const Device;`
- L59 _public member_ `D3D12_QUERY_TYPE const QueryType;`
- L60 _public member_ `D3D12_QUERY_HEAP_TYPE const HeapType;`
- L61 _public member_ `uint32 const NumQueries;`
- L64 _public function_ `uint32 GetResultSize() const` — The byte size of a result for a single query
- L78 _public function_ `ID3D12QueryHeap* GetD3DQueryHeap() const`
- L79 _public function_ `FD3D12Resource* GetResultBuffer() const`
- L81 _public function_ `FD3D12ResidencyHandle& GetHeapResidencyHandle()`
- L84 _public function_ `uint32 AddRef()` — Ref-counting used for object pool recycling.
- L85 _public prototype_ `uint32 Release();`
- L88 _private member_ `TRefCountPtr<FD3D12Resource> ResultBuffer;`
- L89 _private member_ `uint8 const* ResultPtr = nullptr;`
- L90 _private member_ `TRefCountPtr<ID3D12QueryHeap> D3DQueryHeap;`
- L91 _private member_ `FD3D12ResidencyHandle ResidencyHandle;`
- L93 _private member_ `FThreadSafeCounter NumRefs;`

#### struct `FD3D12QueryRange`  
`struct FD3D12QueryRange`  
_L96-118_
- L98 _public member_ `uint32 Start = 0, End = 0;`
- L98 _public member_ `uint32 Start = 0, End = 0;`
- L100 _public prototype_ `FD3D12QueryRange() = default;`
- L101 _public function_ `FD3D12QueryRange(uint32 Start, uint32 End) : Start(Start) , End(End)`
- L106 _public prototype_ `inline bool IsFull(FD3D12QueryHeap* Heap) const;`
- L108 _public function_ `bool operator == (FD3D12QueryRange const& RHS) const`
- L114 _public function_ `bool operator < (FD3D12QueryRange const& RHS) const`
- L171 _function_ `inline bool FD3D12QueryRange::IsFull(FD3D12QueryHeap* Heap) const`

#### struct `FD3D12QueryLocation`  
`struct FD3D12QueryLocation`  
_L121-149_
- desc: The location of a single (timestamp or occlusion) query result.
- L124 _public member_ `FD3D12QueryHeap* Heap = nullptr;` — The heap in which the result is contained.
- L127 _public member_ `uint32 Index = 0;` — The index of the query within the heap.
- L129 _public member_ `ED3D12QueryType Type = ED3D12QueryType::None;`
- L132 _public member_ `void* Target = nullptr;` — The location into which the result is written by the interrupt thread.
- L135 _public prototype_ `inline void CopyResultTo(void* Dst) const;` — Reads the query result from the heap
- L138 _public prototype_ `template <typename TValueType> inline TValueType GetResult() const;`
- L140 _public prototype_ `FD3D12QueryLocation() = default;`
- L141 _public function_ `FD3D12QueryLocation(FD3D12QueryHeap* Heap, uint32 Index, ED3D12QueryType Type, void* Target) : Heap (Heap ) , Index (Index ) , Type (Type ) , Target(Target)`
- L148 _public function_ `operator bool() const`
- L151 _function_ `inline void FD3D12QueryLocation::CopyResultTo(void* Dst) const`
- L162 _function_ `template <typename TValueType> inline TValueType FD3D12QueryLocation::GetResult() const`

#### class `FD3D12QueryAllocator`  
`class FD3D12QueryAllocator`  
_L176-206_
- L179 _public function_ `FD3D12QueryAllocator(FD3D12Device* Device, ED3D12QueueType const QueueType, D3D12_QUERY_TYPE QueryType) : Device(Device) , QueueType(QueueType) , QueryType(QueryType)`
- L185 _public member_ `FD3D12Device* const Device;`
- L186 _public member_ `ED3D12QueueType const QueueType;`
- L187 _public member_ `D3D12_QUERY_TYPE const QueryType;`
- L191 _public prototype_ `FD3D12QueryLocation Allocate(ED3D12QueryType Type, void* Target);` — Allocate a query on a query heap, returning its location. The "target" is where the interrupt thread will write the result when completed by the GPU.
- L194 _public prototype_ `void CloseAndReset(TMap<TRefCountPtr<FD3D12QueryHeap>, TArray<FD3D12QueryRange>>& OutRanges);` — Resets the allocator and returns the used query ranges
- L196 _public function_ `bool HasQueries() const`
- L202 _private member_ `TMap<TRefCountPtr<FD3D12QueryHeap>, FD3D12QueryRange> Heaps;`
- L204 _private member_ `FD3D12QueryHeap* CurrentHeap = nullptr;`
- L205 _private member_ `FD3D12QueryRange* CurrentRange = nullptr;`

#### class `FD3D12RenderQuery`  
`class FD3D12RenderQuery : public FRHIRenderQuery, public FD3D12DeviceChild, public FD3D12LinkedAdapterObject<FD3D12RenderQuery>`  
_L209-226_
- inherits: `FRHIRenderQuery,FD3D12DeviceChild,FD3D12LinkedAdapterObject<FD3D12RenderQuery>`
- desc: D3D12 Render query
- L212 _public prototype_ `FD3D12RenderQuery(FD3D12Device* Parent, ERenderQueryType InQueryType);`
- L213 _public prototype_ `~FD3D12RenderQuery();`
- L215 _public member_ `ERenderQueryType const Type;`
- L218 _public member_ `FD3D12SyncPointRef SyncPoint;` — Signaled when the result is available. Nullptr if the query has never been used.
- L222 _public member_ `uint64* Result;` — The query result, read from the GPU. Heap allocated since it is accessed by the interrupt thread, and needs to outlive the RHI object.
- L225 _public member_ `FD3D12QueryLocation ActiveLocation;` — The current query location for occlusion queries.

#### struct `TD3D12ResourceTraits`  
`template<> struct TD3D12ResourceTraits<FRHIRenderQuery>`  
_L229-232_
- L231 _public typedef_ `typedef FD3D12RenderQuery TConcreteType;`

#### Free symbols / members of external scopes

- L11 _typedef_ `using FD3D12SyncPointRef = TRefCountPtr<FD3D12SyncPoint>;`

### `Source/Runtime/D3D12RHI/Private/D3D12Queue.h` (Private)


#### enum `ED3D12QueueType`  
`enum class ED3D12QueueType`  
_L10-17_
- desc: Defines a unique command queue type within a FD3D12Device (owner by the command list managers).
- L12 _public enumerator_ `Direct = 0`
- L13 _public enumerator_ `Copy`
- L14 _public enumerator_ `Async`
- L16 _public enumerator_ `Count`

#### Free symbols / members of external scopes

- L19 _variable_ `static constexpr uint32 GD3D12MaxNumQueues = MAX_NUM_GPUS * (uint32)ED3D12QueueType::Count;`
- L21 _function_ `inline ED3D12QueueType GetD3DCommandQueueType(ERHIPipeline Pipeline)`
- L31 _function_ `inline const TCHAR* GetD3DCommandQueueTypeName(ED3D12QueueType QueueType)`
- L42 _function_ `inline FName GetD3DCommandQueueTypeFName(ED3D12QueueType QueueType)`
- L53 _function_ `inline D3D12_COMMAND_LIST_TYPE GetD3DCommandListType(ED3D12QueueType QueueType)`

### `Source/Runtime/D3D12RHI/Private/D3D12RHICommon.h` (Private)


#### class `FD3D12AdapterChild`  
`class FD3D12AdapterChild`  
_L53-75_
- L56 _protected member_ `FD3D12Adapter* ParentAdapter;`
- L59 _public function_ `FD3D12AdapterChild(FD3D12Adapter* InParent = nullptr) : ParentAdapter(InParent)`
- L61 _public function_ `FORCEINLINE FD3D12Adapter* GetParentAdapter() const`
- L70 _public function_ `inline void SetParentAdapter(FD3D12Adapter* InParent)` — To be used with delayed setup

#### class `FD3D12DeviceChild`  
`class FD3D12DeviceChild`  
_L77-97_
- L80 _protected member_ `FD3D12Device* Parent;`
- L83 _public function_ `FD3D12DeviceChild(FD3D12Device* InParent = nullptr) : Parent(InParent)`
- L85 _public function_ `FORCEINLINE FD3D12Device* GetParentDevice() const`
- L93 _public function_ `FD3D12Device* GetParentDevice_Unsafe() const`

#### class `FD3D12GPUObject`  
`class FD3D12GPUObject`  
_L99-125_
- L102 _public function_ `FD3D12GPUObject(FRHIGPUMask InGPUMask, FRHIGPUMask InVisibiltyMask) #if WITH_MGPU : GPUMask(InGPUMask) , VisibilityMask(InVisibiltyMask) #endif`
- L112 _public function_ `FORCEINLINE FRHIGPUMask GetGPUMask() const`
- L113 _public function_ `FORCEINLINE FRHIGPUMask GetVisibilityMask() const`
- L115 _public function_ `SGPU_CONSTEXPR FRHIGPUMask GetGPUMask() const`
- L116 _public function_ `SGPU_CONSTEXPR FRHIGPUMask GetVisibilityMask() const`
- L121 _protected member_ `const FRHIGPUMask GPUMask;`
- L123 _protected member_ `const FRHIGPUMask VisibilityMask;` — Which GPUs have direct access to this object

#### class `FD3D12SingleNodeGPUObject`  
`class FD3D12SingleNodeGPUObject : public FD3D12GPUObject`  
_L127-150_
- inherits: `FD3D12GPUObject`
- L130 _public function_ `FD3D12SingleNodeGPUObject(FRHIGPUMask GPUMask) : FD3D12GPUObject(GPUMask, GPUMask) #if WITH_MGPU , GPUIndex(GPUMask.ToIndex()) #endif`
- L138 _public function_ `FORCEINLINE uint32 GetGPUIndex() const`
- L143 _public function_ `SGPU_CONSTEXPR uint32 GetGPUIndex() const`
- L148 _private member_ `uint32 GPUIndex;`

#### class `FD3D12MultiNodeGPUObject`  
`class FD3D12MultiNodeGPUObject : public FD3D12GPUObject`  
_L152-160_
- inherits: `FD3D12GPUObject`
- L155 _public function_ `FD3D12MultiNodeGPUObject(FRHIGPUMask NodeMask, FRHIGPUMask VisibiltyMask) : FD3D12GPUObject(NodeMask, VisibiltyMask)`

#### class `FD3D12LinkedAdapterObject`  
`template <typename ObjectType> class FD3D12LinkedAdapterObject`  
_L163-321_
- L166 _public typedef_ `using LinkedObjectType = ObjectType;`
- L167 _public typedef_ `using FDualLinkedObjectIterator = TD3D12DualLinkedObjectIterator<ObjectType, ObjectType>;`
- L169 _public function_ `~FD3D12LinkedAdapterObject()`
- L190 _public function_ `FORCEINLINE bool IsHeadLink() const`
- L200 _public function_ `template <typename ReturnType, typename CreationCoreFunction, typename CreationParameterFunction> static ReturnType* CreateLinkedObjects(FRHIGPUMask GPUMask, const CreationParameterFunction& pfnGetCreationParameter, const CreationCoreFunction& pfnCreationCore)` — The creation lambda function is passed FD3D12Device, and a pointer to the first linked object, or nullptr if the object being constructed is itself the first object.  The first object pointer is needed for cases where resources need to be shared for all linked objects, such as bindless resource descriptor handles, which need to be the same across GPUs for use in platform independent logic which generates descriptor tables.
- L239 _public function_ `ObjectType* GetLinkedObject(uint32 GPUIndex) const`
- L249 _public function_ `ObjectType* GetFirstLinkedObject() const`
- L258 _public function_ `FRHIGPUMask GetLinkedObjectsGPUMask() const`
- L302 _public function_ `FLinkedObjectIterator begin()`
- L303 _public function_ `FLinkedObjectIterator end()`
- L306 _protected function_ `FD3D12LinkedAdapterObject()`
- L319 _private member_ `FLinkedObjects LinkedObjects;`

#### class `FD3D12LinkedAdapterObject::FLinkedObjectIterator`  
`class FLinkedObjectIterator`  
_L267-300_
- L270 _public function_ `explicit FLinkedObjectIterator(FD3D12LinkedAdapterObject* InObject) : GPUIterator(0) , Object(nullptr)`
- L281 _public function_ `FLinkedObjectIterator& operator++()`
- L287 _public function_ `explicit operator bool() const`
- L288 _public function_ `bool operator !() const`
- L290 _public function_ `bool operator ==(FLinkedObjectIterator& Other) const`
- L291 _public function_ `bool operator !=(FLinkedObjectIterator& Other) const`
- L293 _public function_ `ObjectType& operator *() const`
- L294 _public function_ `ObjectType* operator ->() const`
- L295 _public function_ `ObjectType* Get() const`
- L298 _private member_ `FRHIGPUMask::FIterator GPUIterator;`
- L299 _private member_ `ObjectType* Object;`

#### struct `FD3D12LinkedAdapterObject::FLinkedObjects`  
`struct FLinkedObjects`  
_L310-318_
- L312 _public function_ `FLinkedObjects() : Objects(InPlace, nullptr)`
- L316 _public member_ `FRHIGPUMask GPUMask;`
- L317 _public member_ `TStaticArray<ObjectType*, MAX_NUM_GPUS> Objects;`

#### class `TD3D12DualLinkedObjectIterator`  
`template <typename ObjectType0, typename ObjectType1> class TD3D12DualLinkedObjectIterator`  
_L329-369_
- desc: Utility for iterating over a pair of FD3D12LinkedAdapterObjects. The linked objects must have identical GPU masks. Useful for copying data from one object list to another and for updating resource views.
- L332 _public function_ `TD3D12DualLinkedObjectIterator(FD3D12LinkedAdapterObject<typename ObjectType0::LinkedObjectType>* InObject0, FD3D12LinkedAdapterObject<typename ObjectType1::LinkedObjectType>* InObject1) : GPUIterator(0)`
- L343 _public function_ `TD3D12DualLinkedObjectIterator& operator++()`
- L358 _public function_ `explicit operator bool() const`
- L359 _public function_ `bool operator !() const`
- L361 _public function_ `ObjectType0* GetFirst() const`
- L362 _public function_ `ObjectType1* GetSecond() const`
- L363 _public function_ `uint32 GetGPUIndex() const`
- L366 _private member_ `FRHIGPUMask::FIterator GPUIterator;`
- L367 _private member_ `ObjectType0* Object0;`
- L368 _private member_ `ObjectType1* Object1;`

#### struct `TD3D12ResourceTraits`  
`template<class T> struct TD3D12ResourceTraits`  
_L373-375_
- desc: Template helper class for converting RHI resource types to D3D12RHI resource types

#### struct `TD3D12ObjectPool`  
`template <typename TObjectType> struct TD3D12ObjectPool : public TLockFreePointerListUnordered<TObjectType, PLATFORM_CACHE_LINE_SIZE>`  
_L379-393_
- inherits: `TLockFreePointerListUnordered<TObjectType,PLATFORM_CACHE_LINE_SIZE>`
- desc: Lock free pointer list that auto-destructs items remaining in the list.
- L381 _public function_ `~TD3D12ObjectPool()`
- L386 _public function_ `void CleanupResources()`

#### Free symbols / members of external scopes

- L29 _typedef_ `typedef uint16 CBVSlotMask;`
- L34 _variable_ `static const CBVSlotMask GRootCBVSlotMask = (1 << MAX_ROOT_CBVS) - 1;` — Mask for all slots that are used by root descriptors.
- L35 _variable_ `static const CBVSlotMask GDescriptorTableCBVSlotMask = static_cast<CBVSlotMask>((1<<MAX_CBS) - 1) & ~(GRootCBVSlotMask);` — Mask for all slots that are used by a root descriptor table.
- L38 _typedef_ `typedef uint64 SRVSlotMask;`
- L40 _typedef_ `typedef uint32 SRVSlotMask;`
- L44 _typedef_ `typedef uint32 SamplerSlotMask;`
- L47 _typedef_ `typedef uint16 UAVSlotMask;`
- L50 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogD3D12RHI, Log, All);`
- L50 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogD3D12RHI, Log, All);`
- L51 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogD3D12GapRecorder, Log, All);`
- L51 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogD3D12GapRecorder, Log, All);`
- L398 _macro_ `#define ENABLE_COPY_BUFFER_REGION_CHECK 1`
- L402 _macro_ `#define ENABLE_COPY_TEXTURE_REGION_CHECK 1`

### `Source/Runtime/D3D12RHI/Private/D3D12RHIDefinitions.h` (Private)


#### Free symbols / members of external scopes

- L10 _macro_ `#define DX_MAX_MSAA_COUNT 8` — DX12 doesn't support higher MSAA count
- L15 _macro_ `#define RESIDENCY_PIPELINE_DEPTH 6` — How many residency packets can be in flight before the rendering thread blocks for them to drain. Should be ~ NumBufferedFrames * AvgNumSubmissionsPerFrame i.e. enough to ensure that the GPU is rarely blocked by residency work
- L17 _macro_ `#define DEBUG_RESOURCE_STATES 0`
- L20 _macro_ `#define D3D12RHI_IDLE_AFTER_EVERY_GPU_EVENT 0` — Useful for debugging. Only flushes the default context though.
- L22 _macro_ `#define D3D12_RHI_RAYTRACING (RHI_RAYTRACING)`
- L25 _macro_ `#define D3D12_RHI_WORKGRAPHS 1`
- L26 _macro_ `#define D3D12_RHI_WORKGRAPHS_GRAPHICS 0`
- L28 _macro_ `#define D3D12_RHI_WORKGRAPHS 0`
- L41 _macro_ `#define D3D12RHI_SUPPORTS_ENHANCED_BARRIERS (D3D12RHI_ALLOW_ENHANCED_BARRIERS)`
- L43 _macro_ `#define D3D12RHI_SUPPORTS_ENHANCED_BARRIERS 0`
- L46 _macro_ `#define D3D12RHI_SUPPORTS_LEGACY_BARRIERS (D3D12RHI_ALLOW_LEGACY_BARRIERS)`
- L49 _macro_ `#define D3D12RHI_BARRIER_LOGGING !(UE_BUILD_SHIPPING)`
- L53 _macro_ `#define D3D12RHI_SUPPORTS_UNCOMPRESSED_UAV 1`
- L55 _macro_ `#define D3D12RHI_SUPPORTS_UNCOMPRESSED_UAV 0`
- L59 _macro_ `#define WITH_NVAPI_RAYTRACING_VALIDATION 1`
- L61 _macro_ `#define WITH_NVAPI_RAYTRACING_VALIDATION 0`
- L66 _macro_ `#define MAX_ROOT_CBVS MAX_CBS` — This value controls how many root constant buffers can be used per shader stage in a root signature. Note: Using root descriptors significantly increases the size of root signatures (each root descriptor is 2 DWORDs).
- L68 _macro_ `#define EXECUTE_DEBUG_COMMAND_LISTS 0`
- L69 _macro_ `#define NAME_OBJECTS RHI_USE_RESOURCE_DEBUG_NAME`
- L70 _macro_ `#define LOG_PSO_CREATES (0 && STATS) // Logs Create Pipeline State timings (also requires STATS)`
- L71 _macro_ `#define TRACK_RESOURCE_ALLOCATIONS (PLATFORM_WINDOWS && !UE_BUILD_SHIPPING && !UE_BUILD_TEST)`
- L73 _macro_ `#define READBACK_BUFFER_POOL_MAX_ALLOC_SIZE (64 * 1024)`
- L74 _macro_ `#define READBACK_BUFFER_POOL_DEFAULT_POOL_SIZE (4 * 1024 * 1024)`
- L76 _macro_ `#define TEXTURE_POOL_SIZE (8 * 1024 * 1024)`
- L79 _macro_ `#define LOG_EXECUTE_COMMAND_LISTS 1`
- L80 _macro_ `#define LOG_PRESENT 1`
- L82 _macro_ `#define LOG_EXECUTE_COMMAND_LISTS 0`
- L83 _macro_ `#define LOG_PRESENT 0`
- L86 _macro_ `#define DEBUG_FRAME_TIMING 0`
- L89 _macro_ `#define LOG_VIEWPORT_EVENTS 1`
- L93 _macro_ `#define LOG_VIEWPORT_EVENTS 0`
- L97 _macro_ `#define DEBUG_EXECUTE_COMMAND_LIST(scope) if ((scope)->ActiveQueries == 0) { (scope)->FlushCommands(ED3D12FlushFlags::WaitForCompletion); }`
- L98 _macro_ `#define DEBUG_EXECUTE_COMMAND_CONTEXT(context) if ((context).ActiveQueries == 0) { (context).FlushCommands(ED3D12FlushFlags::WaitForCompletion); }`
- L99 _macro_ `#define DEBUG_RHI_EXECUTE_COMMAND_LIST(scope) if ((scope)->GetRHIDevice(0)->GetDefaultCommandContext().ActiveQueries == 0) { (scope)->GetRHIDevice(0)->GetDefaultCommandContext().FlushCommands(ED3D12FlushFlags::WaitForCompletion); }`
- L101 _macro_ `#define DEBUG_EXECUTE_COMMAND_LIST(scope)`
- L102 _macro_ `#define DEBUG_EXECUTE_COMMAND_CONTEXT(context)`
- L103 _macro_ `#define DEBUG_RHI_EXECUTE_COMMAND_LIST(scope)`
- L107 _macro_ `#define D3D12_VIEWPORT_EXPOSES_SWAP_CHAIN 1`
- L112 _macro_ `#define DXGI_PRESENT_ALLOW_TEARING 0x00000200UL`
- L113 _macro_ `#define DXGI_SWAP_CHAIN_FLAG_ALLOW_TEARING 2048`
- L118 _macro_ `#define EMBED_DXGI_ERROR_LIST(PerEntry, Terminator) \`
- L144 _macro_ `#define DEFAULT_BUFFER_POOL_MAX_ALLOC_SIZE (64 * 1024 * 1024)` — #dxr_todo: Reevaluate these values. Currently optimized to reduce number of CreateCommitedResource() calls, at the expense of memory use.
- L145 _macro_ `#define DEFAULT_BUFFER_POOL_DEFAULT_POOL_SIZE (16 * 1024 * 1024)`
- L148 _macro_ `#define DEFAULT_BUFFER_POOL_MAX_ALLOC_SIZE (64 * 1024)` — On PC, buffers are 64KB aligned, so anything smaller should be sub-allocated
- L149 _macro_ `#define DEFAULT_BUFFER_POOL_DEFAULT_POOL_SIZE (8 * 1024 * 1024)`

### `Source/Runtime/D3D12RHI/Private/D3D12RHIPrivate.h` (Private)


#### struct `FD3D12UpdateTexture3DData`  
`struct FD3D12UpdateTexture3DData`  
_L119-123_
- L121 _public member_ `FD3D12ResourceLocation* UploadHeapResourceLocation;`
- L122 _public member_ `bool bComputeShaderCopy;`

#### struct `FD3D12RayTracingPipelineInfo`  
`struct FD3D12RayTracingPipelineInfo`  
_L129-141_
- desc: Structure that represents various RTPSO properties (0 if unknown). These can be used to report performance characteristics, sort shaders by occupancy, etc.
- L131 _public member_ `static constexpr uint32 MaxPerformanceGroups = 10;`
- L135 _public member_ `uint32 PerformanceGroup = 0;` — Estimated RTPSO group based on occupancy or other platform-specific heuristics. Group 0 is expected to be performing worst, 9 (MaxPerformanceGroups-1) is expected to be the best.
- L137 _public member_ `uint32 NumVGPR = 0;`
- L138 _public member_ `uint32 NumSGPR = 0;`
- L139 _public member_ `uint32 StackSize = 0;`
- L140 _public member_ `uint32 ScratchSize = 0;`

#### struct `FD3D12WorkaroundFlags`  
`struct FD3D12WorkaroundFlags`  
_L146-148_
- desc: Struct used for driver work around on certain driver versions

#### class `FD3D12DynamicRHI`  
`class FD3D12DynamicRHI : public ID3D12PlatformDynamicRHI`  
_L158-696_
- inherits: `ID3D12PlatformDynamicRHI`
- desc: The interface which is implemented by the dynamically bound RHI.
- L162 _private member_ `static FD3D12DynamicRHI* SingleD3DRHI;`
- L163 _private member_ `static bool bFormatAliasedTexturesMustBeCreatedUsingCommonLayout;`
- L167 _public function_ `static FD3D12DynamicRHI* GetD3DRHI()`
- L169 _public prototype_ `void TerminateOnOutOfMemory(ID3D12Device* InDevice, HRESULT D3DResult, bool bCreatingTextures);`
- L172 _public prototype_ `void OutputGPUCrashReport(FTextBuilder& ErrorMessage);` — Dump & Log all the information we have on a GPU crash (NvAfterMath, DRED, Breadcrumbs, ...)
- L176 _public prototype_ `bool IsInInterruptThread() const;` — Returns true if the calling thread is the interrupt thread (or acting as the interrupt thread when D3D12_USE_INTERRUPT_THREAD is zero).
- L179 _public prototype_ `void HandleFailedD3D12Result(HRESULT D3DResult, ID3D12Device* Device, bool bCreatingTextures, const TCHAR* Message);` — Main crash function for handling D3D API errors
- L184 _public prototype_ `void DumpActiveBreadcrumbs(FRHIBreadcrumbState::EVerbosity Verbosity);` — Prints the active breadcrumb tree to the log. Can only be called on the interrupt thread.
- L189 _private prototype_ `void TerminateOnGPUCrash(TOptional<HRESULT> D3DResult);` — Calls OutputGpuCrashReport, and also forces a quit.
- L192 _private member_ `int64 RequestedTexturePoolSize;` — Texture pool size
- L195 _private member_ `class FD3D12Thread* SubmissionThread = nullptr;`
- L196 _private member_ `class FD3D12Thread* InterruptThread = nullptr;`
- L200 _private member_ `uint32 InterruptThreadID = 0;` — Used when a dedicated interrupt thread is disabled (D3D12_USE_INTERRUPT_THREAD) Tracks the thread ID of the thread currently acting as the interrupt thread.
- L212 _private prototype_ `FRIEND_ENUM_CLASS_FLAGS(EQueueStatus);`
- L220 _private member_ `TQueue<TArray<FD3D12Payload*>*, EQueueMode::Mpsc> PendingPayloadsForSubmission;`
- L223 _private prototype_ `void FlushBatchedPayloads(FD3D12Queue::FPayloadArray& PayloadsToHandDown);` — Ensures all prior batched command lists have reached the driver ID3D12Queue object.
- L226 _private prototype_ `void UpdateReservedResources(FD3D12Payload* Payload);` — Executes reserved resource commit operations and cross-queue sync when required
- L228 _private member_ `FCriticalSection SubmissionCS;`
- L229 _private member_ `FCriticalSection InterruptCS;`
- L231 _private prototype_ `FProcessResult ProcessSubmissionQueue();`
- L232 _private prototype_ `FProcessResult ProcessInterruptQueue();`
- L234 _private member_ `FCriticalSection ObjectsToDeleteCS;`
- L235 _private member_ `TArray<FD3D12DeferredDeleteObject> ObjectsToDelete;`
- L237 _private prototype_ `virtual void UpdateMemoryStats();`
- L240 _private prototype_ `void FlushRaytracingValidationMessages();`
- L245 _public function_ `template <typename ...Args> void DeferredDelete(Args&&... InArgs)`
- L251 _public prototype_ `void SubmitCommands(TConstArrayView<struct FD3D12FinalizedCommands*> Commands);`
- L252 _public prototype_ `void SubmitPayloads(TArray<FD3D12Payload*>&& Payloads);`
- L256 _public prototype_ `void ProcessInterruptQueueUntil(FGraphEvent* GraphEvent);` — Processes the interrupt queue on the calling thread, until the specified GraphEvent is signaled. If the GraphEvent is nullptr, processes the queue until no further progress is made.
- L259 _public prototype_ `void ProcessInterruptQueueOnGPUCrash(HRESULT D3DResult);` — Called when the GPU has crashed. This function will not return.
- L269 _public member_ `FD3D12TimingArray CurrentTimingPerQueue;`
- L270 _public prototype_ `void ProcessTimestamps(FD3D12TimingArray const& TimingPerQueue);`
- L272 _public prototype_ `void InitializeSubmissionPipe();`
- L273 _public prototype_ `void ShutdownSubmissionPipe();`
- L276 _public prototype_ `void EnqueueEndOfPipeTask(TUniqueFunction<void()> TaskFunc, TUniqueFunction<void(FD3D12Payload&)> ModifyPayloadCallback = {});` — Inserts a task graph task which is executed once all previously submitted GPU work has completed (across all queues, device and adapters).
- L277 _public member_ `FGraphEventRef EopTask;`
- L278 _public member_ `TArray<TPair<FGraphEventRef, double>> EopTaskQueue;`
- L281 _public prototype_ `void ForEachQueue(TFunctionRef<void(FD3D12Queue&)> Callback);` — Enumerates all queues across all devices and active adapters
- L284 _public prototype_ `FD3D12DynamicRHI(TSharedPtr<FD3D12Adapter>& InChosenAdapter, bool bInPixEventEnabled);` — Initialization constructor.
- L287 _public prototype_ `virtual ~FD3D12DynamicRHI();` — Destructor
- L290 _public prototype_ `virtual void Init() override;` — FDynamicRHI interface.
- L291 _public prototype_ `virtual void PostInit() override;`
- L292 _public prototype_ `virtual void Shutdown() override;`
- L293 _public function_ `virtual const TCHAR* GetName() override`
- L296 _public function_ `template<typename TRHIType, typename TReturnType = typename TD3D12ResourceTraits<TRHIType>::TConcreteType> static FORCEINLINE TReturnType* ResourceCast(TRHIType* Resource)`
- L302 _public function_ `template<typename TRHIType, typename TReturnType = typename TD3D12ResourceTraits<TRHIType>::TConcreteType> static FORCEINLINE const TReturnType* ResourceCast(const TRHIType* Resource)`
- L308 _public function_ `template<typename TRHIType, typename TReturnType = typename TD3D12ResourceTraits<TRHIType>::TConcreteType> static FORCEINLINE_DEBUGGABLE TReturnType* ResourceCast(TRHIType* Resource, uint32 GPUIndex)`
- L315 _public function_ `template<typename TRHIType, typename TReturnType = typename TD3D12ResourceTraits<TRHIType>::TConcreteType> static FORCEINLINE_DEBUGGABLE const TReturnType* ResourceCast(const TRHIType* Resource, uint32 GPUIndex)`
- L321 _public function_ `virtual bool QueueSupportsTileMapping(ED3D12QueueType )`
- L323 _public prototype_ `virtual FD3D12CommandContext* CreateCommandContext(FD3D12Device* InParent, ED3D12QueueType InQueueType, bool InIsDefaultContext);`
- L324 _public prototype_ `virtual void CreateCommandQueue(FD3D12Device* Device, const D3D12_COMMAND_QUEUE_DESC& Desc, TRefCountPtr<ID3D12CommandQueue>& OutCommandQueue);`
- L326 _public prototype_ `virtual void RHIEndFrame_RenderThread(FRHICommandListImmediate& RHICmdList) final override;`
- L327 _public prototype_ `virtual void RHIEndFrame(const FRHIEndFrameArgs& Args) final override;`
- L329 _public prototype_ `virtual FSamplerStateRHIRef RHICreateSamplerState(const FSamplerStateInitializerRHI& Initializer) final override;`
- L330 _public prototype_ `virtual FRasterizerStateRHIRef RHICreateRasterizerState(const FRasterizerStateInitializerRHI& Initializer) final override;`
- L331 _public prototype_ `virtual FDepthStencilStateRHIRef RHICreateDepthStencilState(const FDepthStencilStateInitializerRHI& Initializer) final override;`
- L332 _public prototype_ `virtual FBlendStateRHIRef RHICreateBlendState(const FBlendStateInitializerRHI& Initializer) final override;`
- L333 _public prototype_ `virtual FVertexDeclarationRHIRef RHICreateVertexDeclaration(const FVertexDeclarationElementList& Elements) final override;`
- L334 _public prototype_ `virtual FPixelShaderRHIRef RHICreatePixelShader(const FRHICreateShaderDesc& CreateShaderDesc) final override;`
- L335 _public prototype_ `virtual FVertexShaderRHIRef RHICreateVertexShader(const FRHICreateShaderDesc& CreateShaderDesc) final override;`
- L336 _public prototype_ `virtual FMeshShaderRHIRef RHICreateMeshShader(const FRHICreateShaderDesc& CreateShaderDesc) final override;`
- L337 _public prototype_ `virtual FAmplificationShaderRHIRef RHICreateAmplificationShader(const FRHICreateShaderDesc& CreateShaderDesc) final override;`
- L338 _public prototype_ `virtual FGeometryShaderRHIRef RHICreateGeometryShader(const FRHICreateShaderDesc& CreateShaderDesc) final override;`
- L339 _public prototype_ `virtual FComputeShaderRHIRef RHICreateComputeShader(const FRHICreateShaderDesc& CreateShaderDesc) override;`
- L340 _public prototype_ `virtual FWorkGraphShaderRHIRef RHICreateWorkGraphShader(const FRHICreateShaderDesc& CreateShaderDesc, EShaderFrequency ShaderFrequency) override;`
- L341 _public prototype_ `virtual FGPUFenceRHIRef RHICreateGPUFence(const FName& Name) final override;`
- L342 _public prototype_ `virtual FStagingBufferRHIRef RHICreateStagingBuffer() final override;`
- L343 _public prototype_ `virtual void* RHILockStagingBuffer(FRHIStagingBuffer* StagingBuffer, FRHIGPUFence* Fence, uint32 Offset, uint32 SizeRHI) final override;`
- L344 _public prototype_ `virtual void RHIUnlockStagingBuffer(FRHIStagingBuffer* StagingBuffer) final override;`
- L345 _public prototype_ `virtual FBoundShaderStateRHIRef RHICreateBoundShaderState(FRHIVertexDeclaration* VertexDeclaration, FRHIVertexShader* VertexShader, FRHIPixelShader* PixelShader, FRHIGeometryShader* GeometryShader) final override;`
- L346 _public prototype_ `virtual FGraphicsPipelineStateRHIRef RHICreateGraphicsPipelineState(const FGraphicsPipelineStateInitializer& Initializer) final override;`
- L347 _public prototype_ `virtual FComputePipelineStateRHIRef RHICreateComputePipelineState(const FComputePipelineStateInitializer& Initializer) final override;`
- L348 _public prototype_ `virtual FWorkGraphPipelineStateRHIRef RHICreateWorkGraphPipelineState(const FWorkGraphPipelineStateInitializer& Initializer) final override;`
- L349 _public prototype_ `virtual void RHICreateTransition(FRHITransition* Transition, const FRHITransitionCreateInfo& CreateInfo) final override;`
- L350 _public prototype_ `virtual void RHIReleaseTransition(FRHITransition* Transition) final override;`
- L351 _public prototype_ `virtual FUniformBufferRHIRef RHICreateUniformBuffer(const void* Contents, const FRHIUniformBufferLayout* Layout, EUniformBufferUsage Usage, EUniformBufferValidation Validation) final override;`
- L352 _public prototype_ `virtual void RHIUpdateUniformBuffer(FRHICommandListBase& RHICmdList, FRHIUniformBuffer* UniformBufferRHI, const void* Contents) final override;`
- L354 _public prototype_ `[[nodiscard]] virtual FRHIBufferInitializer RHICreateBufferInitializer(FRHICommandListBase& RHICmdList, const FRHIBufferCreateDesc& CreateDesc) override;`
- L356 _public prototype_ `virtual void RHIReplaceResources(FRHICommandListBase& RHICmdList, TArray<FRHIResourceReplaceInfo>&& ReplaceInfos) final override;`
- L357 _public prototype_ `virtual void RHIWriteResourceGPUAddresses(FRHICommandListBase& RHICmdList, uint32 GPUIndex, TConstArrayView<FRHIResource*> Resources, uint64* AddressesPtr) final override;`
- L359 _public prototype_ `virtual void* RHILockBuffer(FRHICommandListBase& RHICmdList, FRHIBuffer* Buffer, uint32 Offset, uint32 Size, EResourceLockMode LockMode) final override;`
- L360 _public prototype_ `virtual void* RHILockBufferMGPU(FRHICommandListBase& RHICmdList, FRHIBuffer* Buffer, uint32 GPUIndex, uint32 Offset, uint32 Size, EResourceLockMode LockMode) final override;`
- L361 _public prototype_ `virtual void RHIUnlockBuffer(FRHICommandListBase& RHICmdList, FRHIBuffer* Buffer) final override;`
- L363 _public prototype_ `virtual void RHIUpdateAllocationTags(FRHICommandListBase& RHICmdList, FRHIBuffer* Buffer) final override;`
- L365 _public prototype_ `virtual void RHIUnlockBufferMGPU(FRHICommandListBase& RHICmdList, FRHIBuffer* Buffer, uint32 GPUIndex) final override;`
- L366 _public prototype_ `virtual FTextureReferenceRHIRef RHICreateTextureReference(FRHICommandListBase& RHICmdList, FRHITexture* InReferencedTexture) final override;`
- L367 _public prototype_ `virtual void RHIUpdateTextureReference(FRHICommandListBase& RHICmdList, FRHITextureReference* TextureRef, FRHITexture* NewTexture) final override;`
- L368 _public prototype_ `virtual FRHICalcTextureSizeResult RHICalcTexturePlatformSize(const FRHITextureDesc& Desc, uint32 FirstMipIndex) override;`
- L369 _public prototype_ `virtual void RHIGetTextureMemoryStats(FTextureMemoryStats& OutStats) final override;`
- L370 _public prototype_ `virtual bool RHIGetTextureMemoryVisualizeData(FColor* TextureData, int32 SizeX, int32 SizeY, int32 Pitch, int32 PixelSize) final override;`
- L371 _public prototype_ `virtual FTextureRHIRef RHIAsyncCreateTexture2D(uint32 SizeX, uint32 SizeY, uint8 Format, uint32 NumMips, ETextureCreateFlags Flags, ERHIAccess InResourceState, void** InitialMipData, uint32 NumInitialMips, const TCHAR* DebugName, FGraphEventRef& OutCompletionEvent) final override;`
- L373 _public prototype_ `[[nodiscard]] virtual FRHITextureInitializer RHICreateTextureInitializer(FRHICommandListBase& RHICmdList, const FRHITextureCreateDesc& CreateDesc) override;`
- L375 _public prototype_ `virtual uint32 RHIComputeMemorySize(FRHITexture* TextureRHI) final override;`
- L377 _public prototype_ `virtual void RHIGetMemoryStats(FRHIMemoryStats& OutStats) final override;`
- L379 _public prototype_ `virtual FRHILockTextureResult RHILockTexture(FRHICommandListImmediate& RHICmdList, const FRHILockTextureArgs& Arguments) final override;`
- L380 _public prototype_ `virtual void RHIUnlockTexture(FRHICommandListImmediate& RHICmdList, const FRHILockTextureArgs& Arguments) final override;`
- L382 _public prototype_ `virtual void RHIUpdateTexture2D(FRHICommandListBase& RHICmdList, FRHITexture* Texture, uint32 MipIndex, const struct FUpdateTextureRegion2D& UpdateRegion, uint32 SourcePitch, const uint8* SourceData) final override;`
- L383 _public prototype_ `virtual void RHIUpdateTexture3D(FRHICommandListBase& RHICmdList, FRHITexture* Texture, uint32 MipIndex, const struct FUpdateTextureRegion3D& UpdateRegion, uint32 SourceRowPitch, uint32 SourceDepthPitch, const uint8* SourceData) final override;`
- L384 _public prototype_ `virtual FUpdateTexture3DData RHIBeginUpdateTexture3D(FRHICommandListBase& RHICmdList, FRHITexture* Texture, uint32 MipIndex, const struct FUpdateTextureRegion3D& UpdateRegion) final override;`
- L385 _public prototype_ `virtual void RHIEndUpdateTexture3D(FRHICommandListBase& RHICmdList, FUpdateTexture3DData& UpdateData) final override;`
- L386 _public prototype_ `virtual void RHIEndMultiUpdateTexture3D(FRHICommandListBase& RHICmdList, TArray<FUpdateTexture3DData>& UpdateDataArray) final override;`
- L387 _public prototype_ `virtual void RHIBindDebugLabelName(FRHICommandListBase& RHICmdList, FRHITexture* Texture, const TCHAR* Name) final override;`
- L388 _public prototype_ `virtual void RHIBindDebugLabelName(FRHICommandListBase& RHICmdList, FRHIBuffer* Buffer, const TCHAR* Name) final override;`
- L389 _public prototype_ `virtual void RHIReadSurfaceData(FRHITexture* Texture, FIntRect Rect, TArray<FColor>& OutData, FReadSurfaceDataFlags InFlags) final override;`
- L390 _public prototype_ `virtual void RHIReadSurfaceData(FRHITexture* TextureRHI, FIntRect InRect, TArray<FLinearColor>& OutData, FReadSurfaceDataFlags InFlags) final override;`
- L391 _public prototype_ `virtual void RHIMapStagingSurface(FRHITexture* Texture, FRHIGPUFence* Fence, void*& OutData, int32& OutWidth, int32& OutHeight, uint32 GPUIndex = 0) final override;`
- L392 _public prototype_ `virtual void RHIUnmapStagingSurface(FRHITexture* Texture, uint32 GPUIndex = 0) final override;`
- L393 _public prototype_ `virtual void RHIReadSurfaceFloatData(FRHITexture* Texture, FIntRect Rect, TArray<FFloat16Color>& OutData, FReadSurfaceDataFlags InFlags) final override;`
- L394 _public prototype_ `virtual void RHIReadSurfaceFloatData(FRHITexture* Texture, FIntRect Rect, TArray<FFloat16Color>& OutData, ECubeFace CubeFace, int32 ArrayIndex, int32 MipIndex) final override;`
- L395 _public prototype_ `virtual void RHIRead3DSurfaceFloatData(FRHITexture* Texture, FIntRect Rect, FIntPoint ZMinMax, TArray<FFloat16Color>& OutData) final override;`
- L396 _public prototype_ `virtual void RHIRead3DSurfaceFloatData(FRHITexture* Texture, FIntRect Rect, FIntPoint ZMinMax, TArray<FFloat16Color>& OutData, FReadSurfaceDataFlags InFlags) final override;`
- L397 _public prototype_ `virtual FRenderQueryRHIRef RHICreateRenderQuery(ERenderQueryType QueryType) final override;`
- L398 _public prototype_ `virtual void RHIBeginRenderQueryBatch_TopOfPipe(FRHICommandListBase& RHICmdList, ERenderQueryType QueryType) final override;`
- L399 _public prototype_ `virtual void RHIEndRenderQueryBatch_TopOfPipe(FRHICommandListBase& RHICmdList, ERenderQueryType QueryType) final override;`
- L400 _public prototype_ `virtual void RHIEndRenderQuery_TopOfPipe(FRHICommandListBase& RHICmdList, FRHIRenderQuery* RenderQuery) final override;`
- L401 _public prototype_ `virtual bool RHIGetRenderQueryResult(FRHIRenderQuery* RenderQuery, uint64& OutResult, bool bWait, uint32 GPUIndex = INDEX_NONE) final override;`
- L402 _public prototype_ `virtual uint32 RHIGetViewportNextPresentGPUIndex(FRHIViewport* Viewport) final override;`
- L403 _public prototype_ `virtual FTextureRHIRef RHIGetViewportBackBuffer(FRHIViewport* Viewport) final override;`
- L405 _public prototype_ `virtual void RHIAliasTextureResources(FTextureRHIRef& DestTexture, FTextureRHIRef& SrcTexture) final override;`
- L406 _public prototype_ `virtual FTextureRHIRef RHICreateAliasedTexture(FTextureRHIRef& SourceTexture) final override;`
- L408 _public prototype_ `virtual void RHIGetDisplaysInformation(FDisplayInformationArray& OutDisplayInformation) final override;`
- L409 _public prototype_ `virtual uint64 RHIComputeStatePrecachePSOHash(const FGraphicsPipelineStateInitializer& Initializer) final override;`
- L410 _public prototype_ `virtual uint64 RHIComputePrecachePSOHash(const FGraphicsPipelineStateInitializer& Initializer) final override;`
- L411 _public prototype_ `virtual bool RHIMatchPrecachePSOInitializers(const FGraphicsPipelineStateInitializer& LHS, const FGraphicsPipelineStateInitializer& RHS) final override;`
- L412 _public prototype_ `virtual FViewportRHIRef RHICreateViewport(void* WindowHandle, uint32 SizeX, uint32 SizeY, bool bIsFullscreen, EPixelFormat PixelFormat) final override;`
- L413 _public prototype_ `virtual void RHIResizeViewport(FRHIViewport* ViewportRHI, uint32 SizeX, uint32 SizeY, bool bIsFullscreen, EPixelFormat PixelFormat) final override;`
- L414 _public prototype_ `virtual void RHIEndDrawingViewport(FRHICommandListImmediate& RHICmdList, FRHIViewport* Viewport, const FRHIPresentArgs& PresentArgs) final override;`
- L416 _public prototype_ `virtual void RHIHandleDisplayChange() final override;`
- L418 _public prototype_ `virtual void RHITick(float DeltaTime) final override;`
- L419 _public prototype_ `virtual void RHIBlockUntilGPUIdle() final override;`
- L420 _public prototype_ `virtual bool RHIGetAvailableResolutions(FScreenResolutionArray& Resolutions, bool bIgnoreRefreshRate) final override;`
- L421 _public prototype_ `virtual bool RHIGetAvailableResolutionsForDisplay(FScreenResolutionArray& Resolutions, bool bIgnoreRefreshRate, void* NativeMonitorHandle) final override;`
- L422 _public prototype_ `virtual void RHIGetSupportedResolution(uint32& Width, uint32& Height) final override;`
- L423 _public prototype_ `virtual void* RHIGetNativeDevice() final override;`
- L424 _public prototype_ `virtual void* RHIGetNativeGraphicsQueue() final override;`
- L425 _public prototype_ `virtual void* RHIGetNativeComputeQueue() final override;`
- L426 _public prototype_ `virtual class IRHICommandContext* RHIGetDefaultContext() final override;`
- L427 _public prototype_ `virtual IRHIComputeContext* RHIGetCommandContext(ERHIPipeline Pipeline) final override;`
- L428 _public prototype_ `virtual FRHIFinalizeContextsResult RHIFinalizeContexts(FRHIFinalizeContextsArgs&& Args) final override;`
- L429 _public prototype_ `virtual void RHISubmitCommandLists(FRHISubmitCommandListsArgs&& Args) final override;`
- L430 _public prototype_ `virtual void RHIProcessDeleteQueue() final override;`
- L433 _public function_ `virtual FRWLock* RHIGetSuspendedLock()` — Some RHIs can be suspended, most likely due to the HW going into suspend mode, this allows device dependent threads to wait until it's safe
- L435 _public prototype_ `virtual void RHIRunOnQueue(ED3D12RHIRunOnQueueType QueueType, TFunction<void(ID3D12CommandQueue*)>&& CodeToRun, bool bWaitForSubmission) final override;`
- L436 _public prototype_ `virtual void RHIFlushResourceBarriers(FRHICommandListBase& RHICmdList, uint32 InGPUIndex) final override;`
- L440 _public prototype_ `virtual void RHIUpdateResourceResidency(FRHICommandListBase& RHICmdList, uint32 InGPUIndex, FRHIResource* InResource) final override;` — Allows external plugins to add the given FRHIResource's residency handle to the current RHICmdList's context. This ensures resources used by external plugins and made resident before the work begins on the GPU.
- L442 _public prototype_ `virtual IRHITransientResourceAllocator* RHICreateTransientResourceAllocator() override;`
- L444 _public prototype_ `virtual void RHIWriteGPUFence_TopOfPipe(FRHICommandListBase& RHICmdList, FRHIGPUFence* FenceRHI) final override;`
- L447 _public prototype_ `virtual FShaderResourceViewRHIRef RHICreateShaderResourceView (class FRHICommandListBase& RHICmdList, FRHIViewableResource* Resource, FRHIViewDesc const& ViewDesc) override;` — SRV / UAV creation functions
- L448 _public prototype_ `virtual FUnorderedAccessViewRHIRef RHICreateUnorderedAccessView(class FRHICommandListBase& RHICmdList, FRHIViewableResource* Resource, FRHIViewDesc const& ViewDesc) override;`
- L450 _public prototype_ `virtual FRHIResourceCollectionRef RHICreateResourceCollection(FRHICommandListBase& RHICmdList, TConstArrayView<FRHIResourceCollectionMember> InMembers) override;`
- L451 _public prototype_ `virtual void RHIUpdateResourceCollection(FRHICommandListBase& RHICmdList, FRHIResourceCollection* InResourceCollection, uint32 InStartIndex, TConstArrayView<FRHIResourceCollectionMember> InMemberUpdates) override;`
- L453 _public prototype_ `virtual FDescriptorRangeRHIRef RHICreateDescriptorRange(FRHICommandListBase& RHICmdList, const FRHIDescriptorRangeDesc& Desc, TConstArrayView<FRHIDescriptorResource> InitialResources) override;`
- L454 _public prototype_ `virtual void RHIUpdateDescriptorRange(FRHICommandListBase& RHICmdList, FRHIDescriptorRange* Range, uint32 StartIndex, TConstArrayView<FRHIDescriptorResource> Resources) override;`
- L458 _public prototype_ `virtual TArray<FD3D12MinimalAdapterDesc> RHIGetAdapterDescs() const final override;` — ID3D12DynamicRHI interface.
- L459 _public prototype_ `virtual bool RHIIsPixEnabled() const final override;`
- L460 _public prototype_ `virtual ID3D12CommandQueue* RHIGetCommandQueue() const final override;`
- L461 _public prototype_ `virtual ID3D12Device* RHIGetDevice_NoMGPU() const final override;`
- L462 _public prototype_ `virtual ID3D12Device* RHIGetDevice(uint32 InIndex) const final override;`
- L463 _public prototype_ `virtual uint32 RHIGetDeviceNodeMask(uint32 InIndex) const final override;`
- L464 _public prototype_ `virtual ID3D12GraphicsCommandList* RHIGetGraphicsCommandList(FRHICommandListBase& ExecutingCmdList, uint32 InDeviceIndex) const final override;`
- L465 _public prototype_ `virtual FRHIViewport* RHIGetSingletonViewport() const final override;`
- L466 _public prototype_ `virtual DXGI_FORMAT RHIGetSwapChainFormat(EPixelFormat InFormat) const final override;`
- L467 _public prototype_ `virtual FTextureRHIRef RHICreateTexture2DFromResource(EPixelFormat Format, ETextureCreateFlags TexCreateFlags, const FClearValueBinding& ClearValueBinding, ID3D12Resource* Resource) final override;`
- L468 _public prototype_ `virtual FTextureRHIRef RHICreateTexture2DArrayFromResource(EPixelFormat Format, ETextureCreateFlags TexCreateFlags, const FClearValueBinding& ClearValueBinding, ID3D12Resource* Resource) final override;`
- L469 _public prototype_ `virtual FTextureRHIRef RHICreateTextureCubeFromResource(EPixelFormat Format, ETextureCreateFlags TexCreateFlags, const FClearValueBinding& ClearValueBinding, ID3D12Resource* Resource) final override;`
- L470 _public prototype_ `virtual ID3D12Resource* RHIGetResource(FRHIBuffer* InBuffer) const final override;`
- L471 _public prototype_ `virtual uint32 RHIGetResourceDeviceIndex(FRHIBuffer* InBuffer) const final override;`
- L472 _public prototype_ `virtual int64 RHIGetResourceMemorySize(FRHIBuffer* InBuffer) const final override;`
- L473 _public prototype_ `virtual bool RHIIsResourcePlaced(FRHIBuffer* InBuffer) const final override;`
- L474 _public prototype_ `virtual ID3D12Resource* RHIGetResource(FRHITexture* InTexture) const final override;`
- L475 _public prototype_ `virtual uint32 RHIGetResourceDeviceIndex(FRHITexture* InTexture) const final override;`
- L476 _public prototype_ `virtual int64 RHIGetResourceMemorySize(FRHITexture* InTexture) const final override;`
- L477 _public prototype_ `virtual bool RHIIsResourcePlaced(FRHITexture* InTexture) const final override;`
- L478 _public prototype_ `virtual D3D12_CPU_DESCRIPTOR_HANDLE RHIGetRenderTargetView(FRHITexture* InTexture, int32 InMipIndex = 0, int32 InArraySliceIndex = 0) const final override;`
- L479 _public prototype_ `virtual void RHIFinishExternalComputeWork(FRHICommandListBase& ExecutingCmdList, uint32 InDeviceIndex, ID3D12GraphicsCommandList* InCommandList) final override;`
- L480 _public prototype_ `virtual void RHITransitionResource(FRHICommandList& RHICmdList, FRHITexture* InTexture, D3D12_RESOURCE_STATES InState, uint32 InSubResource) final override;`
- L481 _public prototype_ `virtual void RHISignalManualFence(FRHICommandList& RHICmdList, ID3D12Fence* Fence, uint64 Value) final override;`
- L482 _public prototype_ `virtual void RHIWaitManualFence(FRHICommandList& RHICmdList, ID3D12Fence* Fence, uint64 Value, const TSharedPtr<std::atomic<bool>>& bHasSignalled) final override;`
- L483 _public prototype_ `virtual void RHIVerifyResult(ID3D12Device* Device, HRESULT Result, const ANSICHAR* Code, const ANSICHAR* Filename, uint32 Line, FString Message = FString()) const final override;`
- L487 _public prototype_ `virtual FRayTracingAccelerationStructureSize RHICalcRayTracingSceneSize(const FRayTracingSceneInitializer& Initializer) final override;`
- L488 _public prototype_ `virtual FRayTracingAccelerationStructureSize RHICalcRayTracingGeometrySize(const FRayTracingGeometryInitializer& Initializer) final override;`
- L489 _public prototype_ `virtual FRayTracingClusterOperationSize RHICalcRayTracingClusterOperationSize(const FRayTracingClusterOperationInitializer& Initializer) final override;`
- L491 _public prototype_ `virtual FRayTracingAccelerationStructureOfflineMetadata RHIGetRayTracingGeometryOfflineMetadata(const FRayTracingGeometryOfflineDataHeader& OfflineDataHeader) final override;`
- L493 _public prototype_ `virtual FRayTracingGeometryRHIRef RHICreateRayTracingGeometry(FRHICommandListBase& RHICmdList, const FRayTracingGeometryInitializer& Initializer) final override;`
- L494 _public prototype_ `virtual FRayTracingSceneRHIRef RHICreateRayTracingScene(FRayTracingSceneInitializer Initializer) final override;`
- L495 _public prototype_ `virtual FRayTracingShaderRHIRef RHICreateRayTracingShader(const FRHICreateShaderDesc& CreateShaderDesc, EShaderFrequency ShaderFrequency) final override;`
- L496 _public prototype_ `virtual FRayTracingPipelineStateRHIRef RHICreateRayTracingPipelineState(const FRayTracingPipelineStateInitializer& Initializer) final override;`
- L498 _public prototype_ `virtual FShaderBindingTableRHIRef RHICreateShaderBindingTable(FRHICommandListBase& RHICmdList, const FRayTracingShaderBindingTableInitializer& Initializer) final override;`
- L501 _public prototype_ `virtual FShaderBundleRHIRef RHICreateShaderBundle(const FShaderBundleCreateInfo& CreateInfo) override;`
- L503 _public prototype_ `virtual void HandleGpuTimeout(FD3D12Payload* Payload, double SecondsSinceSubmission);`
- L505 _public prototype_ `bool IsQuadBufferStereoEnabled() const;`
- L506 _public prototype_ `void DisableQuadBufferStereo();`
- L508 _public prototype_ `void* LockBuffer(FRHICommandListBase& RHICmdList, FD3D12Buffer* Buffer, uint32 BufferSize, EBufferUsageFlags BufferUsage, uint32 Offset, uint32 Size, EResourceLockMode LockMode);`
- L509 _public prototype_ `void UnlockBuffer(FRHICommandListBase& RHICmdList, FD3D12Buffer* Buffer, EBufferUsageFlags BufferUsage);`
- L511 _public function_ `virtual bool BeginUpdateTexture3D_ComputeShader(FUpdateTexture3DData& UpdateData, FD3D12UpdateTexture3DData* UpdateDataD3D12)`
- L516 _public function_ `virtual void EndUpdateTexture3D_ComputeShader(FRHIComputeCommandList& RHICmdList, FUpdateTexture3DData& UpdateData, FD3D12UpdateTexture3DData* UpdateDataD3D12)`
- L521 _public prototype_ `FUpdateTexture3DData BeginUpdateTexture3D_Internal(FRHITexture* Texture, uint32 MipIndex, const struct FUpdateTextureRegion3D& UpdateRegion);`
- L522 _public prototype_ `void EndUpdateTexture3D_Internal(FRHICommandListBase& RHICmdList, FUpdateTexture3DData& UpdateData);`
- L527 _public prototype_ `virtual void* CreateVirtualTexture( ETextureCreateFlags InFlags, D3D12_RESOURCE_DESC& ResourceDesc, const struct FD3D12TextureLayout& TextureLayout, FD3D12Resource** ppResource, FPlatformMemory::FPlatformVirtualMemoryBlock& RawTextureBlock, ED3D12Access InitialD3D12Access) = 0;`
- L534 _public prototype_ `virtual void DestroyVirtualTexture(ETextureCreateFlags InFlags, void* RawTextureMemory, FPlatformMemory::FPlatformVirtualMemoryBlock& RawTextureBlock, uint64 CommittedTextureSize) = 0;`
- L536 _public function_ `virtual bool HandleSpecialLock(FRHILockTextureResult& Result, FD3D12Texture* InTexture, const FRHILockTextureArgs& Arguments)`
- L537 _public function_ `virtual bool HandleSpecialUnlock(FRHICommandListBase& RHICmdList, FD3D12Texture* InTexture, const FRHILockTextureArgs& Arguments)`
- L539 _public function_ `FD3D12Adapter& GetAdapter()`
- L540 _public function_ `const FD3D12Adapter& GetAdapter() const`
- L542 _public function_ `bool HasAdapter() const`
- L544 _public function_ `bool IsPixEventEnabled() const`
- L547 _public prototype_ `template<typename PerDeviceFunction> void ForEachDevice(ID3D12Device* inDevice, const PerDeviceFunction& pfPerDeviceFunction);`
- L549 _public function_ `AGSContext* GetAmdAgsContext()`
- L550 _public function_ `void SetAmdSupportedExtensionFlags(uint32 Flags)`
- L551 _public function_ `uint32 GetAmdSupportedExtensionFlags() const`
- L553 _public function_ `INTCExtensionContext* GetIntelExtensionContext()`
- L557 _protected member_ `TSharedPtr<FD3D12Adapter> ChosenAdapter;`
- L559 _protected member_ `FRHIMemoryStats MemoryStats;`
- L562 _protected member_ `void* WinPixGpuCapturerHandle = nullptr;`
- L566 _protected member_ `bool bPixEventEnabled = false;` — Can pix events be used
- L569 _protected member_ `D3D_FEATURE_LEVEL FeatureLevel;` — The feature level of the device.
- L576 _protected member_ `AGSContext* AmdAgsContext;` — The context for the AMD AGS utility library. AGSContext does not implement AddRef/Release. Just use a bare pointer.
- L577 _protected member_ `uint32 AmdSupportedExtensionFlags;`
- L579 _protected member_ `bool bNvAPIInitialized = false;`
- L581 _protected member_ `INTCExtensionContext* IntelExtensionContext = nullptr;`
- L584 _protected member_ `void* RayTracingValidationCallbackHandle = nullptr;`
- L590 _protected member_ `bool bDriverCacheAwarePSOPrecaching = false;` — See r.PSOPrecache.D3D12.DriverCacheAware. The CVar is cached to prevent hotfixes or config dynamic layers from altering the value at runtime, which is not supported.
- L593 _protected member_ `void* ZeroBuffer;` — A buffer in system memory containing all zeroes of the specified size.
- L594 _protected member_ `uint32 ZeroBufferSize;`
- L597 _protected member_ `TRefCountPtr<IDXGIFactory2> DXGIFactoryForDisplayList;`
- L598 _protected member_ `TRefCountPtr<IDXGIFactory2> DXGIFactoryForResolutions;`
- L603 _public prototype_ `static void SetFormatAliasedTexturesMustBeCreatedUsingCommonLayout(bool bValue);`
- L605 _public prototype_ `virtual FD3D12ResourceDesc GetResourceDesc(const FRHITextureDesc& CreateInfo) const;`
- L616 _public prototype_ `virtual FCreateTextureInternalResult CreateTextureInternal(const FRHITextureCreateDesc& CreateDesc, ID3D12ResourceAllocator* ResourceAllocator = nullptr);` — Per-platform D3D12Texture creation.
- L619 _public function_ `FD3D12Texture* CreateD3D12Texture(const FRHITextureCreateDesc& CreateDesc, ID3D12ResourceAllocator* ResourceAllocator)` — Create D3D12 texture with a resource allocator. Does not currently support any post-creation state or uploading of data.
- L628 _public prototype_ `virtual FD3D12Texture* CreateNewD3D12Texture(const FRHITextureCreateDesc& CreateDesc, class FD3D12Device* Device);`
- L636 _public prototype_ `FCreateBufferInternalResult CreateBufferInternal(const FRHIBufferCreateDesc& CreateDesc, bool bHasInitialData, ID3D12ResourceAllocator* ResourceAllocator);`
- L638 _public function_ `FD3D12Buffer* CreateD3D12Buffer(FRHICommandListBase* RHICmdList, const FRHIBufferCreateDesc& CreateDesc, ID3D12ResourceAllocator* ResourceAllocator = nullptr)`
- L644 _public function_ `FD3D12Buffer* CreateD3D12Buffer(const FRHIBufferCreateDesc& CreateDesc, ID3D12ResourceAllocator* ResourceAllocator)`
- L649 _public prototype_ `bool SetupDisplayHDRMetaData();`
- L653 _protected prototype_ `FD3D12Texture* CreateTextureFromResource(bool bTextureArray, bool bCubeTexture, EPixelFormat Format, ETextureCreateFlags TexCreateFlags, const FClearValueBinding& ClearValueBinding, ID3D12Resource* Resource);`
- L655 _protected prototype_ `FD3D12Texture* CreateAliasedD3D12Texture2D(FD3D12Texture* SourceTexture);`
- L666 _protected prototype_ `void GetBestSupportedMSAASetting(DXGI_FORMAT PlatformFormat, uint32 MSAACount, uint32& OutBestMSAACount, uint32& OutMSAAQualityLevels);` — Gets the best supported MSAA settings from the provided MSAA count to check against. @param PlatformFormat		The format of the texture being created @param MSAACount				The MSAA count to check against. @param OutBestMSAACount		The best MSAA count that is suppored.  Could be smaller than MSAACount if it is not supported @param OutMSAAQualityLevels	The number MSAA quality levels for the best msaa count supported
- L676 _protected prototype_ `TRefCountPtr<FD3D12Resource> GetStagingTexture(FRHITexture* TextureRHI, FIntRect InRect, FIntRect& OutRect, FReadSurfaceDataFlags InFlags, D3D12_PLACED_SUBRESOURCE_FOOTPRINT &readBackHeapDesc, uint32 GPUIndex);` — Returns a pointer to a texture resource that can be used for CPU reads. Note: the returned resource could be the original texture or a new temporary texture. @param TextureRHI - Source texture to create a staging texture from. @param InRect - rectangle to 'stage'. @param StagingRectOUT - parameter is filled with the rectangle to read from the returned texture. @return The CPU readable Texture object.
- L678 _protected prototype_ `void ReadSurfaceDataNoMSAARaw(FRHITexture* TextureRHI, FIntRect Rect, TArray<uint8>& OutData, FReadSurfaceDataFlags InFlags);`
- L680 _protected prototype_ `void ReadSurfaceDataMSAARaw(FRHITexture* TextureRHI, FIntRect Rect, TArray<uint8>& OutData, FReadSurfaceDataFlags InFlags);`
- L683 _protected prototype_ `FD3D12Device* GetRHIDevice(uint32 GPUIndex) const;` — This should only be called by Dynamic RHI member functions
- L685 _protected prototype_ `void SetupD3D12Debug();`
- L687 _protected member_ `HANDLE FlipEvent;`
- L689 _protected member_ `FDisplayInformationArray DisplayList;`
- L691 _protected prototype_ `void ProcessDeferredDeletionQueue_Platform();`
- L694 _protected prototype_ `void InitializeDeviceAgnosticVendorAPI();`

#### enum `FD3D12DynamicRHI::EQueueStatus`  
`enum class EQueueStatus`  
_L202-211_
- L204 _public enumerator_ `None = 0`
- L207 _public enumerator_ `Processed = 1 << 0` — Work was processed through the queue.
- L210 _public enumerator_ `Pending = 1 << 1` — The queue has further, unprocessed work.

#### struct `FD3D12DynamicRHI::FProcessResult`  
`struct FProcessResult`  
_L214-218_
- L216 _public member_ `EQueueStatus Status = EQueueStatus::None;`
- L217 _public member_ `uint32 WaitTimeout = INFINITE;`

#### struct `FD3D12DynamicRHI::FD3D12TimingArray`  
`struct FD3D12TimingArray : public TArray<TUniquePtr<FD3D12Timing>, TInlineAllocator<GD3D12MaxNumQueues>>`  
_L261-267_
- inherits: `TArray<TUniquePtr<FD3D12Timing>,TInlineAllocator<GD3D12MaxNumQueues>>`
- L263 _public function_ `FD3D12Timing* CreateNew(FD3D12Queue& Queue)`

#### struct `FD3D12DynamicRHI::FCreateTextureInternalResult`  
`struct FCreateTextureInternalResult`  
_L607-613_
- L609 _public member_ `FD3D12Texture* Texture{};`
- L610 _public member_ `ED3D12Access CreateD3D12Access{};`
- L611 _public member_ `ED3D12Access DesiredD3D12Access{};`
- L612 _public member_ `bool bNeedsDiscard{};`

#### struct `FD3D12DynamicRHI::FCreateBufferInternalResult`  
`struct FCreateBufferInternalResult`  
_L630-634_
- L632 _public member_ `FD3D12Buffer* Buffer{};`
- L633 _public member_ `ED3D12Access DesiredD3D12Access{};`

#### class `FD3D12DynamicRHIModule`  
`class FD3D12DynamicRHIModule : public IDynamicRHIModule`  
_L701-732_
- inherits: `IDynamicRHIModule`
- desc: Implements the D3D12RHI module as a dynamic RHI providing module.
- L705 _public function_ `FD3D12DynamicRHIModule()`
- L709 _public prototype_ `~FD3D12DynamicRHIModule() = default;`
- L712 _public function_ `virtual bool SupportsDynamicReloading() override` — IModuleInterface
- L713 _public prototype_ `virtual void StartupModule() override;`
- L714 _public prototype_ `virtual void ShutdownModule() override;`
- L717 _public function_ `virtual bool IsSupported() override` — IDynamicRHIModule
- L718 _public prototype_ `virtual bool IsSupported(ERHIFeatureLevel::Type RequestedFeatureLevel) override;`
- L719 _public prototype_ `virtual FDynamicRHI* CreateRHI(ERHIFeatureLevel::Type RequestedFeatureLevel = ERHIFeatureLevel::Num) override;`
- L724 _private member_ `void* WindowsPixDllHandle = nullptr;`
- L725 _private member_ `void* WinPixGpuCapturerHandle = nullptr;`
- L728 _private member_ `TSharedPtr<FD3D12Adapter> ChosenAdapter;`
- L731 _private prototype_ `void FindAdapter();` — set MaxSupportedFeatureLevel and ChosenAdapter

#### class `FScopedResourceBarrier`  
`class FScopedResourceBarrier`  
_L735-794_
- desc: Helper to push/pop a desired state on a resource. Handles both tracked and untracked resources.
- L738 _private member_ `FD3D12ContextCommon& Context;`
- L739 _private member_ `const FD3D12Resource* pResource;`
- L740 _private member_ `ED3D12Access BeforeD3D12Access;`
- L741 _private member_ `const ED3D12Access DesiredD3D12Access;`
- L742 _private member_ `const uint32 Subresource;`
- L743 _private member_ `bool bRestoreState;`
- L746 _public function_ `FScopedResourceBarrier( FD3D12ContextCommon& InContext, const FD3D12Resource* InResource, ED3D12Access InBeforeD3D12Access, ED3D12Access InDesiredD3D12Access, uint32 InSubresource) : Context(InContext) , pResource(InResource) , BeforeD3D12Access(InBeforeD3D12Access) , DesiredD3D12Access(InDesiredD3D12Access) , Subresource (InSubresource) , bRestoreState(false)`
- L774 _public function_ `FScopedResourceBarrier( FD3D12ContextCommon& InContext, const FD3D12Resource* InResource, ED3D12Access InDesiredD3D12Access, uint32 InSubresource) : FScopedResourceBarrier( InContext, InResource, ED3D12Access::Unknown, InDesiredD3D12Access, InSubresource)`
- L787 _public function_ `~FScopedResourceBarrier()`

#### Free symbols / members of external scopes

- L67 _function_ `template< typename t_A, typename t_B > inline t_A RoundUpToNextMultiple(const t_A& a, const t_B& b)`
- L74 _externvar_ `extern TAutoConsoleVariable<int32> GD3D12DebugCvar;`
- L76 _function_ `static bool D3D12RHI_ShouldCreateWithWarp()`
- L83 _function_ `static bool D3D12RHI_AllowSoftwareFallback()`
- L89 _function_ `static bool D3D12RHI_ShouldAllowAsyncResourceCreation()`
- L95 _function_ `static bool D3D12RHI_ShouldForceCompatibility()`
- L104 _function_ `static bool D3D12RHI_IsRenderDocPresent(ID3D12Device* Device)`
- L150 _externvar_ `extern FD3D12WorkaroundFlags GD3D12WorkaroundFlags;`
- L698 _prototype_ `ENUM_CLASS_FLAGS(FD3D12DynamicRHI::EQueueStatus);`
- L797 _prototype_ `const TCHAR* LexToString(DXGI_FORMAT Format);` — Returns the given format as a string. Unsupported formats are treated as DXGI_FORMAT_UNKNOWN.

### `Source/Runtime/D3D12RHI/Private/D3D12RayTracing.h` (Private)


#### struct `ID3D12RayTracingGeometryUpdateListener`  
`struct ID3D12RayTracingGeometryUpdateListener`  
_L19-23_
- desc: Persistent SBT needs to be notified about hit group parameter changes because those are cached in the SBT - if persistent bindless handles are used then this could be removed
- L21 _public prototype_ `virtual void RemoveListener(FD3D12RayTracingGeometry* InGeometry) = 0;`
- L22 _public prototype_ `virtual void HitGroupParametersUpdated(FD3D12RayTracingGeometry* InGeometry) = 0;`

#### struct `FD3D12ShaderIdentifier`  
`struct FD3D12ShaderIdentifier`  
_L25-54_
- L27 _public member_ `uint64 Data[4] = {~0ull, ~0ull, ~0ull, ~0ull};`
- L30 _public member_ `static const FD3D12ShaderIdentifier Null;` — No shader is executed if a shader binding table record with null identifier is encountered.
- L32 _public function_ `bool operator == (const FD3D12ShaderIdentifier& Other) const`
- L40 _public function_ `bool operator != (const FD3D12ShaderIdentifier& Other) const`
- L45 _public function_ `bool IsValid() const`
- L50 _public function_ `void SetData(const void* InData)`

#### struct `FD3D12RayTracingShaderLibrary`  
`struct FD3D12RayTracingShaderLibrary`  
_L56-79_
- L58 _public function_ `void Reserve(uint32 NumShaders)`
- L64 _public function_ `int32 Find(FShaderHash Hash) const`
- L77 _public member_ `TArray<TRefCountPtr<FD3D12RayTracingShader>> Shaders;`
- L78 _public member_ `TArray<FD3D12ShaderIdentifier> Identifiers;`

#### class `FD3D12RayTracingPipelineState`  
`class FD3D12RayTracingPipelineState : public FRHIRayTracingPipelineState`  
_L81-125_
- inherits: `FRHIRayTracingPipelineState`
- L86 _public prototype_ `FD3D12RayTracingPipelineState(FD3D12Device* Device, const FRayTracingPipelineStateInitializer& Initializer);`
- L88 _public member_ `FD3D12Device* Device;`
- L90 _public member_ `FD3D12RayTracingShaderLibrary RayGenShaders;`
- L91 _public member_ `FD3D12RayTracingShaderLibrary MissShaders;`
- L92 _public member_ `FD3D12RayTracingShaderLibrary HitGroupShaders;`
- L93 _public member_ `FD3D12RayTracingShaderLibrary CallableShaders;`
- L95 _public member_ `ID3D12RootSignature* GlobalRootSignature = nullptr;`
- L97 _public member_ `TRefCountPtr<ID3D12StateObject> StateObject;`
- L98 _public member_ `TRefCountPtr<ID3D12StateObjectProperties> PipelineProperties;`
- L101 _public member_ `TArray<int32> SpecializationIndices;` — Maps raygen shader index to a specialized state object (may be -1 if no specialization is used for a shader)
- L104 _public member_ `TArray<TRefCountPtr<ID3D12StateObject>> SpecializedStateObjects;` — State objects with raygen shaders grouped by occupancy
- L106 _public member_ `uint32 MaxLocalRootSignatureSize = 0;`
- L107 _public member_ `uint32 MaxHitGroupViewDescriptors = 0;`
- L109 _public member_ `TSet<uint64> PipelineShaderHashes;`
- L111 _public member_ `uint32 PipelineStackSize = 0;`
- L121 _public member_ `TArray<FShaderStats> ShaderStats;`
- L124 _public member_ `D3D12ResourceFrameCounter FrameCounter;`

#### struct `FD3D12RayTracingPipelineState::FShaderStats`  
`struct FShaderStats`  
_L114-120_
- L116 _public member_ `const TCHAR* Name = nullptr;`
- L117 _public member_ `float CompileTimeMS = 0;`
- L118 _public member_ `uint32 StackSize = 0;`
- L119 _public member_ `uint32 ShaderSize = 0;`

#### class `FD3D12RayTracingGeometry`  
`class FD3D12RayTracingGeometry : public FRHIRayTracingGeometry, public FD3D12AdapterChild, public FD3D12ShaderResourceRenameListener, public FNoncopyable`  
_L127-244_
- inherits: `FRHIRayTracingGeometry,FD3D12AdapterChild,FD3D12ShaderResourceRenameListener,FNoncopyable`
- L131 _public prototype_ `FD3D12RayTracingGeometry(FRHICommandListBase& RHICmdList, FD3D12Adapter* Adapter, const FRayTracingGeometryInitializer& Initializer);`
- L132 _public prototype_ `~FD3D12RayTracingGeometry();`
- L134 _public function_ `D3D12_GPU_VIRTUAL_ADDRESS GetGPUVirtualAddress(uint64 GPUIndex) const`
- L142 _public function_ `virtual FRayTracingAccelerationStructureAddress GetAccelerationStructureAddress(uint64 GPUIndex) const final override PRAGMA_ENABLE_DEPRECATION_WARNINGS`
- L148 _public prototype_ `void SetupHitGroupSystemParameters(uint32 InGPUIndex);`
- L149 _public prototype_ `void UpdateResidency(FD3D12CommandContext& CommandContext);`
- L150 _public prototype_ `void CompactAccelerationStructure(FD3D12CommandContext& CommandContext, uint32 InGPUIndex, uint64 InSizeAfterCompaction);`
- L151 _public prototype_ `void CreateAccelerationStructureBuildDesc(FD3D12CommandContext& CommandContext, EAccelerationStructureBuildMode BuildMode, D3D12_GPU_VIRTUAL_ADDRESS ScratchBufferAddress, D3D12_BUILD_RAYTRACING_ACCELERATION_STRUCTURE_DESC& OutDesc, TArrayView<D3D12_RAYTRACING_GEOMETRY_DESC>& OutGeometryDescs) const;`
- L154 _public prototype_ `void CreateAccelerationStructureBuildDescEx(FD3D12CommandContext& CommandContext, EAccelerationStructureBuildMode BuildMode, D3D12_GPU_VIRTUAL_ADDRESS ScratchBufferAddress, NVAPI_D3D12_BUILD_RAYTRACING_ACCELERATION_STRUCTURE_DESC_EX& OutDescEx, TArrayView<NVAPI_D3D12_RAYTRACING_GEOMETRY_DESC_EX>& OutGeometryDescsEx) const;`
- L159 _public prototype_ `virtual void ResourceRenamed(FD3D12ContextArray const& Contexts, FD3D12BaseShaderResource* InRenamedResource, FD3D12ResourceLocation* InNewResourceLocation) override;` — Implement FD3D12ShaderResourceRenameListener interface
- L161 _public prototype_ `bool AllocateBufferSRVs(uint32 InGPUIndex);`
- L163 _public prototype_ `void RegisterAsRenameListener(uint32 InGPUIndex);`
- L164 _public prototype_ `void UnregisterAsRenameListener(uint32 InGPUIndex);`
- L166 _public prototype_ `void Swap(FD3D12RayTracingGeometry& Other);`
- L168 _public prototype_ `void ReleaseUnderlyingResource();`
- L170 _public function_ `void SetDirty(FRHIGPUMask GPUMask, bool bState)`
- L177 _public function_ `bool IsDirty(uint32 GPUIndex) const`
- L181 _public prototype_ `bool BuffersValid(uint32 GPUIndex) const;`
- L186 _public member_ `static constexpr uint32 IndicesPerTriangle = 3;`
- L187 _public member_ `static constexpr uint32 IndicesPerLinearSweptSphere = 2;`
- L199 _public member_ `TArray<FPerGPUState, TInlineAllocator<1>> PerGPUData;`
- L201 _public member_ `FDebugName DebugName;`
- L202 _public member_ `FName OwnerName;` — Store the path name of the owner object for resource tracking
- L204 _public member_ `uint64 AccelerationStructureCompactedSize = 0;`
- L206 _public member_ `uint32 ResourceGeneration = 0;`
- L211 _public function_ `void AddUpdateListener(ID3D12RayTracingGeometryUpdateListener* InUpdateListener) const`
- L218 _public function_ `void RemoveUpdateListener(ID3D12RayTracingGeometryUpdateListener* InUpdateListener) const`
- L226 _public function_ `bool HasListeners() const`
- L232 _public function_ `void HitGroupParamatersUpdated()`
- L242 _private member_ `mutable FCriticalSection UpdateListenersCS;`
- L243 _private member_ `mutable TArray<ID3D12RayTracingGeometryUpdateListener*> UpdateListeners;`

#### struct `FD3D12RayTracingGeometry::FPerGPUState`  
`struct FPerGPUState`  
_L189-198_
- L191 _public member_ `TRefCountPtr<FD3D12Buffer> AccelerationStructureBuffer;`
- L192 _public member_ `bool bIsAccelerationStructureDirty = false;`
- L193 _public member_ `bool bRegisteredAsRenameListener = false;`
- L194 _public member_ `bool bHasPendingCompactionRequests = false;`
- L195 _public member_ `TArray<FD3D12HitGroupSystemParameters> HitGroupSystemParameters;`
- L196 _public member_ `TSharedPtr<FD3D12ShaderResourceView> HitGroupSystemIndexBufferSRV;`
- L197 _public member_ `TArray<TSharedPtr<FD3D12ShaderResourceView>> HitGroupSystemSegmentVertexBufferSRVs;`

#### class `FD3D12RayTracingScene`  
`class FD3D12RayTracingScene : public FRHIRayTracingScene, public FD3D12AdapterChild, public FNoncopyable`  
_L246-305_
- inherits: `FRHIRayTracingScene,FD3D12AdapterChild,FNoncopyable`
- L250 _public prototype_ `FD3D12RayTracingScene(FD3D12Adapter* Adapter, FRayTracingSceneInitializer Initializer);`
- L251 _public prototype_ `~FD3D12RayTracingScene();`
- L253 _public function_ `const FRayTracingSceneInitializer& GetInitializer() const override final`
- L255 _public prototype_ `void BindBuffer(FRHIBuffer* Buffer, uint32 BufferOffset);`
- L256 _public prototype_ `void ReleaseBuffer();`
- L263 _public member_ `uint32 NumInstances = 0;`
- L293 _public member_ `TArray<FPerGPUState, TInlineAllocator<1>> PerGPUData;`
- L294 _public member_ `uint32 BufferOffset = 0;`
- L296 _public member_ `const FRayTracingSceneInitializer Initializer;`
- L299 _public prototype_ `void UpdateResidencyTracking(FD3D12CommandContext& CommandContext);`
- L302 _public prototype_ `void UpdateResidency(FD3D12CommandContext& CommandContext, bool bIncludeDispatchResources) const;`
- L304 _public member_ `bool bBuilt = false;`

#### struct `FD3D12RayTracingScene::FGeometryResidencyInfo`  
`struct FGeometryResidencyInfo`  
_L266-271_
- L268 _public member_ `uint32 ResourceGeneration = 0;`
- L269 _public member_ `const FD3D12Resource* CachedASResource = nullptr;`
- L270 _public member_ `TArray<const FD3D12Resource*, TInlineAllocator<2>> CachedDispatchResources;`

#### struct `FD3D12RayTracingScene::FPerGPUState`  
`struct FPerGPUState`  
_L274-292_
- L276 _public member_ `TRefCountPtr<FD3D12Buffer> AccelerationStructureBuffer;`
- L280 _public member_ `TArray<const FD3D12Resource*> ResourcesToMakeResident;` — Resources that must be resident when TLAS is built or traced against (BLAS acceleration structures).
- L281 _public member_ `TMap<const FD3D12Resource*, int32> ResourceRefCounts;`
- L286 _public member_ `TArray<const FD3D12Resource*> DispatchResourcesToMakeResident;` — Resources that only need to be resident at dispatch time (VB/IB). TODO: Once TriangleObjectPositions() is supported across all IHVs, remove this logic and move VB/IB residency tracking to SBT when using hit shaders.
- L287 _public member_ `TMap<const FD3D12Resource*, int32> DispatchResourceRefCounts;`
- L290 _public member_ `TMap<FRHIRayTracingGeometry*, FGeometryResidencyInfo> TrackedGeometries;` — Incremental residency tracking

#### class `FD3D12RayTracingCompactionRequestHandler`  
`class FD3D12RayTracingCompactionRequestHandler : FD3D12DeviceChild`  
_L308-335_
- inherits: `FD3D12DeviceChild`
- desc: Manages all the pending BLAS compaction requests
- L314 _public prototype_ `FD3D12RayTracingCompactionRequestHandler(FD3D12Device* Device);`
- L315 _public function_ `~FD3D12RayTracingCompactionRequestHandler()`
- L320 _public prototype_ `void RequestCompact(FD3D12RayTracingGeometry* InRTGeometry);`
- L321 _public prototype_ `bool ReleaseRequest(FD3D12RayTracingGeometry* InRTGeometry);`
- L323 _public prototype_ `void Update(FD3D12CommandContext& InCommandContext);`
- L327 _private member_ `FCriticalSection CS;`
- L328 _private member_ `TArray<FD3D12RayTracingGeometry*> PendingRequests;`
- L329 _private member_ `TArray<FD3D12RayTracingGeometry*> ActiveRequests;`
- L330 _private member_ `TArray<D3D12_GPU_VIRTUAL_ADDRESS> ActiveBLASGPUAddresses;`
- L332 _private member_ `TRefCountPtr<FD3D12Buffer> PostBuildInfoBuffer;`
- L333 _private member_ `FStagingBufferRHIRef PostBuildInfoStagingBuffer;`
- L334 _private member_ `FD3D12SyncPointRef PostBuildInfoBufferReadbackSyncPoint;`

### `Source/Runtime/D3D12RHI/Private/D3D12RayTracingDebug.h` (Private)


#### Free symbols / members of external scopes

- L7 _macro_ `#define D3D12_RHI_SUPPORT_RAYTRACING_SCENE_DEBUGGING (!UE_BUILD_SHIPPING && D3D12_RHI_RAYTRACING)`
- L11 _prototype_ `void D3D12RayTracingSceneDebugUpdate(const FD3D12RayTracingScene& Scene, FD3D12Buffer* InstanceBuffer, uint32 InstanceBufferOffset, FD3D12CommandContext& CommandContext);`

### `Source/Runtime/D3D12RHI/Private/D3D12Residency.h` (Private)


#### class `D3DX12Residency::ManagedObject`  
`class ManagedObject`  
_L19-19_

#### class `D3DX12Residency::ResidencySet`  
`class ResidencySet`  
_L20-20_

#### class `D3DX12Residency::ResidencyManager`  
`class ResidencyManager`  
_L21-21_

#### struct `FD3D12ResidencyHandle`  
`struct FD3D12ResidencyHandle : public D3DX12Residency::ManagedObject`  
_L46-51_
- inherits: `D3DX12Residency::ManagedObject`
- L49 _public member_ `class FD3D12GPUObject* GPUObject = nullptr;`

#### Free symbols / members of external scopes

- L12 _macro_ `#define D3D12_PLATFORM_NEEDS_RESIDENCY_MANAGEMENT 1`
- L17 _namespace_ `namespace D3DX12Residency`
- L42 _externvar_ `extern bool GEnableResidencyManagement;`
- L43 _externvar_ `extern bool GD3D12StartResourceResident;`
- L53 _namespace_ `namespace D3DX12Residency`
- L56 _function_ `inline void Initialize(FD3D12ResidencyHandle& Object, ID3D12Pageable* pResource, uint64 ObjectSize, class FD3D12GPUObject* GPUObject)` (scope `D3DX12Residency`)
- L68 _function_ `inline bool IsInitialized(FD3D12ResidencyHandle& Object)` (scope `D3DX12Residency`)
- L77 _function_ `inline bool IsInitialized(FD3D12ResidencyHandle* pObject)` (scope `D3DX12Residency`)
- L86 _function_ `inline void BeginTrackingObject(ResidencyManager& ResidencyManager, FD3D12ResidencyHandle& Object)` (scope `D3DX12Residency`)
- L96 _function_ `inline void EndTrackingObject(ResidencyManager& ResidencyManager, FD3D12ResidencyHandle& Object)` (scope `D3DX12Residency`)
- L107 _function_ `inline void InitializeResidencyManager(ResidencyManager& ResidencyManager, ID3D12Device* Device, uint32 GPUIndex, IDXGIAdapter3* Adapter, uint32 MaxLatency)` (scope `D3DX12Residency`)
- L117 _function_ `inline void DestroyResidencyManager(ResidencyManager& ResidencyManager)` (scope `D3DX12Residency`)
- L127 _function_ `inline ResidencySet* CreateResidencySet(ResidencyManager& ResidencyManager)` (scope `D3DX12Residency`)
- L136 _function_ `inline void DestroyResidencySet(ResidencyManager& ResidencyManager, ResidencySet* pSet)` (scope `D3DX12Residency`)
- L146 _function_ `inline void Open(ResidencySet* pSet)` (scope `D3DX12Residency`)
- L166 _function_ `inline void Close(ResidencySet* pSet)` (scope `D3DX12Residency`)
- L176 _function_ `inline void Insert(ResidencySet& Set, FD3D12ResidencyHandle& Object)` (scope `D3DX12Residency`)
- L187 _function_ `inline void Insert(ResidencySet& Set, FD3D12ResidencyHandle* pObject)` (scope `D3DX12Residency`)
- L199 _typedef_ `typedef D3DX12Residency::ResidencySet FD3D12ResidencySet;`
- L200 _typedef_ `typedef D3DX12Residency::ResidencyManager FD3D12ResidencyManager;`

### `Source/Runtime/D3D12RHI/Private/D3D12ResourceCollection.h` (Private)


#### class `FD3D12ResourceCollection`  
`class FD3D12ResourceCollection : public FRHIResourceCollection, public FD3D12DeviceChild, public FD3D12LinkedAdapterObject<FD3D12ResourceCollection>`  
_L16-31_
- inherits: `FRHIResourceCollection,FD3D12DeviceChild,FD3D12LinkedAdapterObject<FD3D12ResourceCollection>`
- L19 _public prototype_ `FD3D12ResourceCollection(FD3D12Device* InParent, FD3D12Buffer* InBuffer, TConstArrayView<FRHIResourceCollectionMember> InMembers, FD3D12ResourceCollection* FirstLinkedObject);`
- L20 _public prototype_ `~FD3D12ResourceCollection();`
- L22 _public prototype_ `virtual FRHIDescriptorHandle GetBindlessHandle() const final;`
- L24 _public function_ `FD3D12ShaderResourceView* GetShaderResourceView() const`
- L26 _public member_ `TRefCountPtr<FD3D12Buffer> Buffer;`
- L27 _public member_ `TSharedPtr<FD3D12ShaderResourceView> BufferSRV;`
- L29 _public member_ `TArray<FD3D12ShaderResourceView*> AllSrvs;`
- L30 _public member_ `TArray<FD3D12RHITextureReference*> AllTextureReferences;`

#### struct `TD3D12ResourceTraits`  
`template<> struct TD3D12ResourceTraits<FRHIResourceCollection>`  
_L34-37_
- L36 _public typedef_ `using TConcreteType = FD3D12ResourceCollection;`

### `Source/Runtime/D3D12RHI/Private/D3D12Resources.h` (Private)


#### enum `ED3D12ResourceStateMode`  
`enum class ED3D12ResourceStateMode`  
_L50-55_
- L52 _public enumerator_ `Default` — Decide if tracking is required based on flags
- L53 _public enumerator_ `SingleState` — Force disable state tracking of resource - resource will always be in the initial resource state
- L54 _public enumerator_ `MultiState` — Force enable state tracking of resource

#### class `FD3D12PendingResourceBarrier`  
`class FD3D12PendingResourceBarrier`  
_L57-69_
- L60 _public member_ `FD3D12Resource* Resource;`
- L61 _public member_ `D3D12_RESOURCE_STATES State;`
- L62 _public member_ `uint32 SubResource;`
- L64 _public function_ `FD3D12PendingResourceBarrier(FD3D12Resource* Resource, D3D12_RESOURCE_STATES State, uint32 SubResource) : Resource(Resource) , State(State) , SubResource(SubResource)`

#### class `FD3D12Heap`  
`class FD3D12Heap : public FRefCountedObject, public FD3D12DeviceChild, public FD3D12MultiNodeGPUObject`  
_L71-117_
- inherits: `FRefCountedObject,FD3D12DeviceChild,FD3D12MultiNodeGPUObject`
- L74 _public prototype_ `FD3D12Heap(FD3D12Device* Parent, FRHIGPUMask VisibleNodes, HeapId InTraceParentHeapId = EMemoryTraceRootHeap::VideoMemory);`
- L75 _public prototype_ `~FD3D12Heap();`
- L77 _public function_ `inline ID3D12Heap* GetHeap() const`
- L78 _public prototype_ `void SetHeap(ID3D12Heap* HeapIn, const TCHAR* const InName, bool bTrack = true, bool bForceGetGPUAddress = false);`
- L80 _public prototype_ `void BeginTrackingResidency(uint64 Size);`
- L81 _public prototype_ `void DisallowTrackingResidency();` — Part of workaround for UE-174791 and UE-202367
- L83 _public prototype_ `void DeferDelete();`
- L85 _public function_ `inline FName GetName() const`
- L86 _public function_ `inline D3D12_HEAP_DESC GetHeapDesc() const`
- L87 _public function_ `inline TConstArrayView<FD3D12ResidencyHandle*> GetResidencyHandles()`
- L101 _public function_ `inline D3D12_GPU_VIRTUAL_ADDRESS GetGPUVirtualAddress() const`
- L102 _public function_ `inline void SetIsTransient(bool bInIsTransient)`
- L103 _public function_ `inline bool GetIsTransient() const`
- L107 _private member_ `TRefCountPtr<ID3D12Heap> Heap;`
- L108 _private member_ `FName HeapName;`
- L109 _private member_ `bool bTrack = true;`
- L110 _private member_ `D3D12_HEAP_DESC HeapDesc;`
- L111 _private member_ `D3D12_GPU_VIRTUAL_ADDRESS GPUVirtualAddress = 0;`
- L112 _private member_ `FD3D12ResidencyHandle* ResidencyHandle = nullptr;` — Residency handle owned by this object
- L113 _private member_ `HeapId TraceHeapId;`
- L114 _private member_ `HeapId TraceParentHeapId;`
- L115 _private member_ `bool bIsTransient = false;` — Whether this is a transient heap
- L116 _private member_ `bool bRequiresResidencyTracking = bool(ENABLE_RESIDENCY_MANAGEMENT);`

#### struct `TZeroedStruct`  
`template <typename T> struct TZeroedStruct`  
_L124-130_
- desc: This can be used to guarantee that a struct's padding is zero, which is necessary for hashing in some cases NOTE: classes with virtual methods are not supported. The struct must be the first declared base class to ensure the correct ordering of the ctor calls
- L126 _public function_ `TZeroedStruct<T>()`

#### struct `FD3D12ResourceDesc`  
`struct FD3D12ResourceDesc : public TZeroedStruct<FD3D12ResourceDesc>, D3D12_RESOURCE_DESC`  
_L132-177_
- inherits: `TZeroedStruct<FD3D12ResourceDesc>,D3D12_RESOURCE_DESC`
- L134 _public function_ `FD3D12ResourceDesc() : TZeroedStruct<FD3D12ResourceDesc>()`
- L138 _public function_ `FD3D12ResourceDesc(const CD3DX12_RESOURCE_DESC& Other) : TZeroedStruct<FD3D12ResourceDesc>() , D3D12_RESOURCE_DESC(Other)`
- L145 _public function_ `FD3D12ResourceDesc(const D3D12_RESOURCE_DESC& Other) : TZeroedStruct<FD3D12ResourceDesc>() , D3D12_RESOURCE_DESC(Other)` — TODO: use this type everywhere and disallow implicit conversion
- L151 _public member_ `EPixelFormat PixelFormat{ PF_Unknown };`
- L154 _public member_ `EPixelFormat UAVPixelFormat{ PF_Unknown };` — PixelFormat for the Resource that aliases our current resource.
- L157 _public member_ `bool bRequires64BitAtomicSupport : 1 = false;`
- L160 _public member_ `bool bReservedResource : 1 = false;`
- L162 _public member_ `bool bBackBuffer : 1 = false;`
- L165 _public member_ `bool bExternal : 1 = false;` — External resources are owned by another application or middleware, not the Engine
- L169 _public function_ `inline bool NeedsUAVAliasWorkarounds() const`
- L170 _public function_ `inline bool SupportsUncompressedUAV() const`
- L172 _public prototype_ `TArray<DXGI_FORMAT, TInlineAllocator<4>> GetCastableFormats() const;`

#### class `FD3D12Resource`  
`class FD3D12Resource : public UE::Private::FQueryableRefCountedObject, public FD3D12DeviceChild, public FD3D12MultiNodeGPUObject`  
_L179-583_
- inherits: `UE::Private::FQueryableRefCountedObject,FD3D12DeviceChild,FD3D12MultiNodeGPUObject`
- L183 _private member_ `TRefCountPtr<ID3D12Resource> Resource;`
- L184 _private member_ `TRefCountPtr<FD3D12Heap> Heap;`
- L189 _private member_ `TUniquePtr<D3D12_RESOURCE_DESC> UAVAccessResourceDesc;` — Since certain formats cannot be aliased in D3D12, we create a placed UAV that aliases them. This resource description is used to create that UAV.
- L192 _private member_ `FD3D12ResidencyHandle* ResidencyHandle = nullptr;` — Residency handle owned by this object
- L194 _private member_ `D3D12_GPU_VIRTUAL_ADDRESS GPUVirtualAddress{};`
- L195 _private member_ `void* ResourceBaseAddress{};`
- L198 _private member_ `UE::RHICore::Nvidia::Aftermath::D3D12::FResource AftermathHandle{};`
- L200 _private member_ `const FD3D12ResourceDesc Desc;`
- L201 _private member_ `ED3D12Access InitialD3D12Access = ED3D12Access::Unknown;`
- L202 _private member_ `ED3D12Access DefaultD3D12Access = ED3D12Access::Unknown;`
- L204 _private member_ `D3D12_RESOURCE_STATES CompressedState{ D3D12_RESOURCE_STATE_CORRUPT };`
- L207 _private member_ `D3D12_HEAP_TYPE HeapType;`
- L208 _private member_ `FName DebugName;`
- L210 _private member_ `int32 NumMapCalls = 0;`
- L211 _private member_ `uint16 SubresourceCount{};`
- L212 _private member_ `uint8 PlaneCount;`
- L213 _private member_ `bool bRequiresResourceStateTracking : 1;` — 1st bit
- L214 _private member_ `bool bRequiresResidencyTracking : 1;` — 2nd bit
- L215 _private member_ `bool bDepthStencil : 1;` — 3rd bit
- L216 _private member_ `bool bDeferDelete : 1;` — 4th bit
- L219 _private member_ `static int64 TotalResourceCount;`
- L220 _private member_ `static int64 NoStateTrackingResourceCount;`
- L237 _private member_ `TUniquePtr<FD3D12ReservedResourceData> ReservedResourceData;`
- L240 _public prototype_ `FD3D12Resource() = delete;`
- L241 _public prototype_ `explicit FD3D12Resource(FD3D12Device* ParentDevice, FRHIGPUMask VisibleNodes, ID3D12Resource* InResource, ED3D12Access InInitialD3D12Access, FD3D12ResourceDesc const& InDesc, FD3D12Heap* InHeap = nullptr, D3D12_HEAP_TYPE InHeapType = D3D12_HEAP_TYPE_DEFAULT);`
- L249 _public prototype_ `explicit FD3D12Resource(FD3D12Device* ParentDevice, FRHIGPUMask VisibleNodes, ID3D12Resource* InResource, ED3D12Access InInitialD3D12Access, ED3D12ResourceStateMode InResourceStateMode, ED3D12Access InDefaultD3D12Access, FD3D12ResourceDesc const& InDesc, FD3D12Heap* InHeap, D3D12_HEAP_TYPE InHeapType);`
- L259 _public prototype_ `virtual ~FD3D12Resource();`
- L261 _public function_ `operator ID3D12Resource&()`
- L263 _public function_ `ID3D12Resource* GetResource() const`
- L266 _public function_ `const D3D12_RESOURCE_DESC* GetUAVAccessResourceDesc() const`
- L271 _public function_ `void SetUAVAccessResourceDesc(const D3D12_RESOURCE_DESC& InUAVAccessResourceDesc)`
- L277 _public function_ `inline void* Map(const D3D12_RANGE* ReadRange = nullptr)`
- L294 _public function_ `inline void Unmap()`
- L308 _public prototype_ `ID3D12Pageable* GetPageable();`
- L309 _public function_ `const FD3D12ResourceDesc& GetDesc() const`
- L310 _public function_ `D3D12_HEAP_TYPE GetHeapType() const`
- L311 _public function_ `D3D12_GPU_VIRTUAL_ADDRESS GetGPUVirtualAddress() const`
- L312 _public function_ `inline void SetGPUVirtualAddress(D3D12_GPU_VIRTUAL_ADDRESS Value)`
- L313 _public function_ `void* GetResourceBaseAddress() const`
- L314 _public function_ `uint16 GetMipLevels() const`
- L315 _public function_ `uint16 GetArraySize() const`
- L316 _public function_ `uint8 GetPlaneCount() const`
- L317 _public function_ `uint16 GetSubresourceCount() const`
- L318 _public function_ `ED3D12Access GetInitialAccess() const`
- L319 _public function_ `ED3D12Access GetDefaultAccess() const`
- L321 _public function_ `D3D12_RESOURCE_STATES GetCompressedState() const`
- L322 _public function_ `void SetCompressedState(D3D12_RESOURCE_STATES State)`
- L324 _public function_ `bool RequiresResourceStateTracking() const`
- L326 _public function_ `inline bool IsBackBuffer() const`
- L328 _public function_ `void SetName(const TCHAR* Name)`
- L339 _public function_ `FName GetName() const`
- L344 _public function_ `void DoNotDeferDelete()`
- L349 _public function_ `inline bool ShouldDeferDelete() const`
- L350 _public prototype_ `void DeferDelete();`
- L352 _public function_ `inline bool IsReservedResource() const`
- L353 _public function_ `inline bool IsPlacedResource() const`
- L354 _public function_ `inline FD3D12Heap* GetHeap() const`
- L355 _public function_ `inline bool IsDepthStencilResource() const`
- L357 _public function_ `inline uint64 GetCommittedReservedResourceSize() const`
- L363 _public function_ `inline bool NeedsDeferredResidencyUpdate() const`
- L365 _public prototype_ `void StartTrackingForResidency();`
- L367 _public function_ `bool IsResident() const`
- L400 _public function_ `TConstArrayView<FD3D12ResidencyHandle*> GetResidencyHandles() const`
- L426 _public function_ `template<typename TLambda> FORCEINLINE_DEBUGGABLE void GetBackingHeapsGpuAddresses(TLambda&& Lambda) const`
- L499 _public prototype_ `void CommitReservedResource(ID3D12CommandQueue* D3DCommandQueue, uint64 RequiredCommitSizeInBytes);` — Note: RequiredCommitSizeInBytes is clamped to the maximum size of the resource. Use UINT64_MAX to commit the entire resource.
- L502 _private function_ `void InitializeResourceState( const D3D12_HEAP_PROPERTIES* InHeapProps, ED3D12Access InInitialD3D12Access, ED3D12ResourceStateMode InResourceStateMode, ED3D12Access InDefaultD3D12Access)`
- L544 _private function_ `void DetermineResourceStates( const D3D12_HEAP_PROPERTIES* InHeapProps, ED3D12Access InInitialD3D12Access, ED3D12ResourceStateMode InResourceStateMode, ED3D12Access InDefaultD3D12Access)`

#### struct `FD3D12Resource::FD3D12ReservedResourceData`  
`struct FD3D12ReservedResourceData`  
_L223-236_
- L225 _public member_ `TArray<TRefCountPtr<FD3D12Heap>> BackingHeaps;`
- L228 _public member_ `TArray<FD3D12ResidencyHandle*> ResidencyHandles;` — Flattened array of residency handles owned by backing heaps, used to support batched GetResidencyHandles()
- L229 _public member_ `TArray<int32> NumResidencyHandlesPerHeap;`
- L232 _public member_ `uint32 NumCommittedTiles = 0;` — Tiles currently assigned to the resource
- L235 _public member_ `uint32 NumSlackTiles = 0;` — Available tiles at the end of the last backing heap

#### struct `FD3D12Resource::FD3D12ResourceTypeHelper`  
`struct FD3D12ResourceTypeHelper`  
_L437-495_
- L439 _public function_ `FD3D12ResourceTypeHelper(const FD3D12ResourceDesc& Desc, D3D12_HEAP_TYPE HeapType) : bSRV(!EnumHasAnyFlags(Desc.Flags, D3D12_RESOURCE_FLAG_DENY_SHADER_RESOURCE)), bDSV(EnumHasAnyFlags(Desc.Flags, D3D12_RESOURCE_FLAG_ALLOW_DEPTH_STENCIL)), bRTV(EnumHasAnyFlags(Desc.Flags, D3D12_RESOURCE_FLAG_ALLOW_RENDER_TARGET)), bUAV(EnumHasAnyFlags(Desc.Flags, D3D12_RESOURCE_FLAG_ALLOW_UNORDERED_ACCESS)), bWritable(bDSV || bRTV || bUAV), bSRVOnly(bSRV && !bWritable), bBuffer(Desc.Dimension == D3D12_RESOURCE_DIMENSION_BUFFER), bReadBackResource(HeapType == D3D12_HEAP_TYPE_READBACK)`
- L450 _public function_ `ED3D12Access GetOptimalInitialD3D12Access(ED3D12Access InD3D12Access, bool bAccurateWriteableStates) const`
- L487 _public member_ `const uint32 bSRV : 1;`
- L488 _public member_ `const uint32 bDSV : 1;`
- L489 _public member_ `const uint32 bRTV : 1;`
- L490 _public member_ `const uint32 bUAV : 1;`
- L491 _public member_ `const uint32 bWritable : 1;`
- L492 _public member_ `const uint32 bSRVOnly : 1;`
- L493 _public member_ `const uint32 bBuffer : 1;`
- L494 _public member_ `const uint32 bReadBackResource : 1;`

#### struct `FD3D12BuddyAllocatorPrivateData`  
`struct FD3D12BuddyAllocatorPrivateData`  
_L587-597_
- L589 _public member_ `uint32 Offset;`
- L590 _public member_ `uint32 Order;`
- L592 _public function_ `void Init()`

#### struct `FD3D12PoolAllocatorPrivateData`  
`struct FD3D12PoolAllocatorPrivateData`  
_L599-607_
- L601 _public member_ `FRHIPoolAllocationData PoolData;`
- L603 _public function_ `void Init()`

#### class `FD3D12ResourceLocation`  
`class FD3D12ResourceLocation : public FRHIPoolResource, public FD3D12DeviceChild, public FNoncopyable`  
_L613-791_
- inherits: `FRHIPoolResource,FD3D12DeviceChild,FNoncopyable`
- desc: A very light-weight and cache friendly way of accessing a GPU resource
- L636 _public prototype_ `FD3D12ResourceLocation(FD3D12Device* Parent);`
- L637 _public function_ `FD3D12ResourceLocation(FD3D12ResourceLocation&& Other) : FD3D12ResourceLocation(Other.GetParentDevice())`
- L643 _public prototype_ `~FD3D12ResourceLocation();`
- L645 _public prototype_ `void Clear();`
- L648 _public prototype_ `static void TransferOwnership(FD3D12ResourceLocation& Destination, FD3D12ResourceLocation& Source);` — Transfers the contents of 1 resource location to another, destroying the original but preserving the underlying resource
- L651 _public function_ `void SetOwner (FD3D12BaseShaderResource* InOwner)` — Setters
- L652 _public function_ `void SetType (ResourceLocationType Value)`
- L653 _public prototype_ `void SetResource(FD3D12Resource* Value);`
- L655 _public function_ `void SetAllocator (FD3D12BaseAllocatorType* Value)`
- L656 _public function_ `void SetPoolAllocator (FD3D12PoolAllocator* Value)`
- L658 _public function_ `void ClearAllocator()`
- L660 _public function_ `void SetMappedBaseAddress (void* Value )`
- L661 _public function_ `void SetGPUVirtualAddress (D3D12_GPU_VIRTUAL_ADDRESS Value)`
- L662 _public function_ `void SetOffsetFromBaseOfResource(uint64 Value )`
- L663 _public function_ `void SetSize (uint64 Value )`
- L666 _public function_ `ResourceLocationType GetType () const` — Getters
- L667 _public function_ `EAllocatorType GetAllocatorType () const`
- L668 _public function_ `FD3D12BaseAllocatorType* GetAllocator ()`
- L669 _public function_ `FD3D12PoolAllocator* GetPoolAllocator ()`
- L670 _public function_ `FD3D12Resource* GetResource () const`
- L671 _public function_ `void* GetMappedBaseAddress () const`
- L672 _public function_ `D3D12_GPU_VIRTUAL_ADDRESS GetGPUVirtualAddress () const`
- L673 _public function_ `uint64 GetOffsetFromBaseOfResource () const`
- L674 _public function_ `uint64 GetSize () const`
- L675 _public function_ `FD3D12BuddyAllocatorPrivateData& GetBuddyAllocatorPrivateData ()`
- L676 _public function_ `FD3D12PoolAllocatorPrivateData& GetPoolAllocatorPrivateData ()`
- L679 _public prototype_ `bool OnAllocationMoved(FD3D12ContextArray const& Contexts, FRHIPoolAllocationData* InNewData, ED3D12Access& OutRHIAccess);` — Pool allocation specific functions
- L680 _public prototype_ `void UnlockPoolData();`
- L682 _public function_ `bool IsValid() const`
- L684 _public prototype_ `void AsStandAlone(FD3D12Resource* Resource, uint64 InSize = 0, bool bInIsTransient = false, const D3D12_HEAP_PROPERTIES* CustomHeapProperties = nullptr);`
- L685 _public prototype_ `bool IsStandaloneOrPooledPlacedResource() const;`
- L687 _public function_ `void AsHeapAliased(FD3D12Resource* Resource)`
- L704 _public function_ `void AsFastAllocation(FD3D12Resource* Resource, uint32 BufferSize, D3D12_GPU_VIRTUAL_ADDRESS GPUBase, void* CPUBase, uint64 ResourceOffsetBase, uint64 Offset, bool bMultiFrame = false)`
- L730 _public prototype_ `static void Alias(FD3D12ResourceLocation& Destination, FD3D12ResourceLocation& Source);` — XR plugins alias textures so this allows 2+ resource locations to reference the same underlying resource. We should avoid this as much as possible as it requires expensive reference counting and it complicates the resource ownership model.
- L733 _public prototype_ `static void ReferenceNode(FD3D12Device* NodeDevice, FD3D12ResourceLocation& Destination, FD3D12ResourceLocation& Source);`
- L734 _public function_ `bool IsAliased() const`
- L740 _public function_ `void SetTransient(bool bInTransient)`
- L744 _public function_ `bool IsTransient() const`
- L750 _public function_ `void* GetAddressForLLMTracking() const` — Get an address used by LLM to track the GPU allocation that this location represents.
- L758 _private prototype_ `template<bool bReleaseResource> void InternalClear();`
- L760 _private prototype_ `void ReleaseResource();`
- L761 _private prototype_ `void UpdateStandAloneStats(bool bIncrement);`
- L763 _private member_ `FD3D12BaseShaderResource* Owner{};`
- L764 _private member_ `FD3D12Resource* UnderlyingResource{};`
- L778 _private member_ `} AllocatorData;`
- L781 _private member_ `void* MappedBaseAddress{};` — Note: These values refer to the start of this location including any padding *NOT* the start of the underlying resource
- L782 _private member_ `D3D12_GPU_VIRTUAL_ADDRESS GPUVirtualAddress{};`
- L783 _private member_ `uint64 OffsetFromBaseOfResource{};`
- L786 _private member_ `uint64 Size{};` — The size the application asked for
- L788 _private member_ `ResourceLocationType Type{ ResourceLocationType::eUndefined };`
- L789 _private member_ `EAllocatorType AllocatorType{ AT_Unknown };`
- L790 _private member_ `bool bTransient{ false };`

#### enum `FD3D12ResourceLocation::ResourceLocationType`  
`enum class ResourceLocationType : uint8`  
_L617-627_
- L619 _public enumerator_ `eUndefined`
- L620 _public enumerator_ `eStandAlone`
- L621 _public enumerator_ `eSubAllocation`
- L622 _public enumerator_ `eFastAllocation`
- L623 _public enumerator_ `eMultiFrameFastAllocation`
- L624 _public enumerator_ `eAliased` — XR HMDs are the only use cases
- L625 _public enumerator_ `eNodeReference`
- L626 _public enumerator_ `eHeapAliased`

#### enum `FD3D12ResourceLocation::EAllocatorType`  
`enum EAllocatorType : uint8`  
_L629-634_
- L631 _public enumerator_ `AT_Default` — FD3D12BaseAllocatorType
- L632 _public enumerator_ `AT_Pool` — FD3D12PoolAllocator
- L633 _public enumerator_ `AT_Unknown = 0xff`

#### union `FD3D12ResourceLocation::(anonymous)`  
``  
_L768-771_

#### union `FD3D12ResourceLocation::PrivateAllocatorData`  
`union PrivateAllocatorData`  
_L774-778_
- desc: Union to save memory
- L776 _public member_ `FD3D12BuddyAllocatorPrivateData BuddyAllocatorPrivateData;`
- L777 _public member_ `FD3D12PoolAllocatorPrivateData PoolAllocatorPrivateData;`

#### struct `ID3D12ResourceAllocator`  
`struct ID3D12ResourceAllocator`  
_L794-822_
- desc: Generic interface for every type D3D12 specific allocator
- L797 _public prototype_ `void AllocateTexture( uint32 GPUIndex, D3D12_HEAP_TYPE InHeapType, const FD3D12ResourceDesc& InDesc, EPixelFormat InUEFormat, ED3D12Access InInitialD3D12Access, ED3D12ResourceStateMode InResourceStateMode, ED3D12Access InDefaultD3D12Access, const D3D12_CLEAR_VALUE* InClearValue, const TCHAR* InName, FD3D12ResourceLocation& ResourceLocation);` — Helper function for textures to compute the correct size and alignment
- L810 _public prototype_ `virtual void AllocateResource( uint32 GPUIndex, D3D12_HEAP_TYPE InHeapType, const FD3D12ResourceDesc& InDesc, uint64 InSize, uint32 InAllocationAlignment, ED3D12Access InInitialD3D12Access, ED3D12ResourceStateMode InResourceStateMode, ED3D12Access InDefaultD3D12Access, const D3D12_CLEAR_VALUE* InClearValue, const TCHAR* InName, FD3D12ResourceLocation& ResourceLocation) = 0;` — Actual pure virtual resource allocation function

#### struct `FD3D12LockedResource`  
`struct FD3D12LockedResource : public FD3D12DeviceChild`  
_L824-848_
- inherits: `FD3D12DeviceChild`
- L826 _public function_ `FD3D12LockedResource(FD3D12Device* Device) : FD3D12DeviceChild(Device) , ResourceLocation(Device)`
- L831 _public function_ `inline void Reset()`
- L841 _public member_ `FD3D12ResourceLocation ResourceLocation;`
- L842 _public member_ `D3D12_SUBRESOURCE_FOOTPRINT Footprint = {};`
- L843 _public member_ `uint32 LockOffset = 0;`
- L844 _public member_ `uint32 LockSize = 0;`
- L845 _public member_ `uint32 bLocked : 1 = false;`
- L846 _public member_ `uint32 bLockedForReadOnly : 1 = false;`
- L847 _public member_ `uint32 bHasNeverBeenLocked : 1 = true;`

#### struct `FD3D12ShaderResourceRenameListener`  
`struct FD3D12ShaderResourceRenameListener`  
_L851-854_
- desc: Resource which might needs to be notified about changes on dependent resources (Views, RTGeometryObject, Cached binding tables)
- L853 _public prototype_ `virtual void ResourceRenamed(FD3D12ContextArray const& Contexts, FD3D12BaseShaderResource* InRenamedResource, FD3D12ResourceLocation* InNewResourceLocation) = 0;`

#### class `FD3D12BaseShaderResource`  
`class FD3D12BaseShaderResource : public FD3D12DeviceChild, public IRefCountedObject`  
_L858-916_
- inherits: `FD3D12DeviceChild,IRefCountedObject`
- desc: The base class of resources that may be bound as shader resources (texture or buffer).
- L861 _private member_ `mutable FCriticalSection RenameListenersCS;`
- L862 _private member_ `TArray<FD3D12ShaderResourceRenameListener*> RenameListeners;`
- L865 _public function_ `FD3D12Resource* GetResource() const`
- L867 _public function_ `void AddRenameListener(FD3D12ShaderResourceRenameListener* InRenameListener)`
- L874 _public function_ `void RemoveRenameListener(FD3D12ShaderResourceRenameListener* InRenameListener)`
- L882 _public function_ `bool HasLinkedViews() const`
- L888 _public function_ `void ResourceRenamed(FD3D12ContextArray const& Contexts)`
- L897 _public function_ `D3D12_GPU_VIRTUAL_ADDRESS GetGPUVirtualAddress() const`
- L902 _public member_ `FD3D12ResourceLocation ResourceLocation;`
- L905 _public function_ `FD3D12BaseShaderResource(FD3D12Device* InParent) : FD3D12DeviceChild(InParent) , ResourceLocation(InParent)`
- L912 _public function_ `~FD3D12BaseShaderResource()`

#### struct `ID3D12UniformBufferUpdateListener`  
`struct ID3D12UniformBufferUpdateListener`  
_L921-925_
- desc: Resource which might needs to be notified about changes on dependent resources (Views, RTGeometryObject, Cached binding tables)
- L923 _public prototype_ `virtual void RemoveListener(FD3D12UniformBuffer* InUniformBufferToRemove) = 0;`
- L924 _public prototype_ `virtual void UniformBufferUpdated(const FD3D12ContextArray& Contexts, FD3D12UniformBuffer* InUpdatedUniformBuffer) = 0;`

#### class `FD3D12UniformBuffer`  
`class FD3D12UniformBuffer : public FRHIUniformBuffer, public FD3D12DeviceChild, public FD3D12LinkedAdapterObject<FD3D12UniformBuffer>`  
_L928-987_
- inherits: `FRHIUniformBuffer,FD3D12DeviceChild,FD3D12LinkedAdapterObject<FD3D12UniformBuffer>`
- desc: Uniform buffer resource class.
- L931 _private member_ `mutable FCriticalSection UpdateListenersCS;`
- L932 _private member_ `TArray<ID3D12UniformBufferUpdateListener*> UpdateListeners;`
- L934 _public member_ `class FD3D12ConstantBufferView* View = nullptr;`
- L937 _public member_ `FD3D12ResourceLocation ResourceLocation;` — The D3D12 constant buffer resource
- L939 _public member_ `const EUniformBufferUsage UniformBufferUsage;`
- L942 _public function_ `FD3D12UniformBuffer(class FD3D12Device* InParent, const FRHIUniformBufferLayout* InLayout, EUniformBufferUsage InUniformBufferUsage) : FRHIUniformBuffer(InLayout) , FD3D12DeviceChild(InParent) , ResourceLocation(InParent) , UniformBufferUsage(InUniformBufferUsage)` — Initialization constructor.
- L950 _public prototype_ `virtual ~FD3D12UniformBuffer();`
- L952 _public prototype_ `virtual FRHIDescriptorHandle GetBindlessHandle() const override;`
- L956 _public function_ `TArray<TRefCountPtr<FRHIResource>>& GetResourceTable()` — Provides public non-const access to ResourceTable. @todo refactor uniform buffers to perform updates as a member function, so this isn't necessary.
- L958 _public function_ `void AddUpdateListener(ID3D12UniformBufferUpdateListener* InUpdateListener)`
- L965 _public function_ `void RemoveUpdateListener(ID3D12UniformBufferUpdateListener* InUpdateListener)`
- L973 _public function_ `bool HasListeners() const`
- L979 _public function_ `void UniformBufferUpdated(const FD3D12ContextArray& Contexts)`

#### class `FD3D12Buffer`  
`class FD3D12Buffer : public FRHIBuffer, public FD3D12BaseShaderResource, public FD3D12LinkedAdapterObject<FD3D12Buffer>`  
_L989-1061_
- inherits: `FRHIBuffer,FD3D12BaseShaderResource,FD3D12LinkedAdapterObject<FD3D12Buffer>`
- L992 _public function_ `FD3D12Buffer(FD3D12Device* InParent, const FRHIBufferCreateDesc& InCreateDesc) : FRHIBuffer(InCreateDesc) , FD3D12BaseShaderResource(InParent) , LockedData(InParent)`
- L999 _public prototype_ `virtual ~FD3D12Buffer();`
- L1001 _public prototype_ `static void UploadResourceData( FD3D12CommandContext& CommandContext, ED3D12Access DestinationD3D12Access, FD3D12ResourceLocation& DestinationResourceLocation, const FD3D12ResourceLocation& SourceResourceLocation, uint32 Size);`
- L1008 _public prototype_ `FD3D12SyncPointRef UploadResourceDataViaCopyQueue(FD3D12CommandContext& OwningContext, FResourceArrayUploadInterface* InResourceArray);`
- L1012 _public function_ `bool GetResourceInfo(FRHIResourceInfo& OutResourceInfo) const override`
- L1032 _public prototype_ `void Rename(FD3D12ContextArray const& Contexts, FD3D12ResourceLocation& NewLocation);`
- L1033 _public prototype_ `void RenameLDAChain(FD3D12ContextArray const& Contexts, FD3D12ResourceLocation& NewLocation);`
- L1035 _public prototype_ `void TakeOwnership(FD3D12Buffer& Other);`
- L1036 _public prototype_ `void ReleaseOwnership();`
- L1039 _public function_ `virtual void AddRef() const override final` — IRefCountedObject interface.
- L1043 _public function_ `virtual FReturnedRefCountValue Release() const override final`
- L1047 _public function_ `virtual FReturnedRefCountValue GetRefCount() const override final`
- L1052 _public prototype_ `static void GetResourceDescAndAlignment(const FRHIBufferCreateDesc& CreateDesc, D3D12_RESOURCE_DESC& ResourceDesc, uint32& Alignment);`
- L1056 _public prototype_ `void UpdateAllocationTags() const;`
- L1059 _public member_ `FD3D12LockedResource LockedData;`
- L1060 _public member_ `uint32 BufferAlignment = 0;`

#### class `FD3D12StagingBuffer`  
`class FD3D12StagingBuffer final : public FRHIStagingBuffer`  
_L1068-1093_
- inherits: `FRHIStagingBuffer`
- L1074 _public function_ `FD3D12StagingBuffer(FD3D12Device* InDevice) : FRHIStagingBuffer() , ResourceLocation(InDevice) , ShadowBufferSize(0)`
- L1081 _public function_ `void SafeRelease()`
- L1086 _public prototype_ `void* Lock(uint32 Offset, uint32 NumBytes) override;`
- L1087 _public prototype_ `void Unlock() override;`
- L1088 _public function_ `uint64 GetGPUSizeBytes() const override`
- L1091 _private member_ `FD3D12ResourceLocation ResourceLocation;`
- L1092 _private member_ `uint32 ShadowBufferSize;`

#### class `FD3D12ShaderBundle`  
`class FD3D12ShaderBundle : public FRHIShaderBundle, public FD3D12DeviceChild`  
_L1095-1106_
- inherits: `FRHIShaderBundle,FD3D12DeviceChild`
- L1101 _public function_ `FD3D12ShaderBundle(FD3D12Device* InDevice, const FShaderBundleCreateInfo& CreateInfo) : FRHIShaderBundle(CreateInfo) , FD3D12DeviceChild(InDevice)`

#### class `FD3D12GPUFence`  
`class FD3D12GPUFence final : public FRHIGPUFence`  
_L1108-1119_
- inherits: `FRHIGPUFence`
- L1111 _public prototype_ `FD3D12GPUFence(FName InName);`
- L1113 _public prototype_ `virtual void Clear() override;`
- L1114 _public prototype_ `virtual bool Poll() const override;`
- L1115 _public prototype_ `virtual bool Poll(FRHIGPUMask GPUMask) const override;`
- L1116 _public prototype_ `virtual void Wait(FRHICommandListImmediate& RHICmdList, FRHIGPUMask GPUMask) const override;`
- L1118 _public member_ `TArray<FD3D12SyncPointRef, TInlineAllocator<MAX_NUM_GPUS>> SyncPoints;`

#### struct `TD3D12ResourceTraits`  
`template<> struct TD3D12ResourceTraits<FRHIUniformBuffer>`  
_L1122-1125_
- L1124 _public typedef_ `typedef FD3D12UniformBuffer TConcreteType;`
- L1129 _public typedef_ `typedef FD3D12Buffer TConcreteType;`
- L1134 _public typedef_ `typedef FD3D12SamplerState TConcreteType;`
- L1139 _public typedef_ `typedef FD3D12RasterizerState TConcreteType;`
- L1144 _public typedef_ `typedef FD3D12DepthStencilState TConcreteType;`
- L1149 _public typedef_ `typedef FD3D12BlendState TConcreteType;`
- L1154 _public typedef_ `typedef FD3D12GraphicsPipelineState TConcreteType;`
- L1159 _public typedef_ `typedef FD3D12ComputePipelineState TConcreteType;`
- L1164 _public typedef_ `typedef FD3D12WorkGraphPipelineState TConcreteType;`
- L1169 _public typedef_ `typedef FD3D12GPUFence TConcreteType;`
- L1174 _public typedef_ `typedef FD3D12StagingBuffer TConcreteType;`
- L1179 _public typedef_ `typedef FD3D12ShaderBundle TConcreteType;`
- L1186 _public typedef_ `typedef FD3D12RayTracingScene TConcreteType;`
- L1191 _public typedef_ `typedef FD3D12RayTracingGeometry TConcreteType;`
- L1196 _public typedef_ `typedef FD3D12RayTracingPipelineState TConcreteType;`
- L1201 _public typedef_ `typedef FD3D12RayTracingShaderBindingTable TConcreteType;`
- L1206 _public typedef_ `typedef FD3D12RayTracingShader TConcreteType;`

#### struct `TD3D12ResourceTraits`  
`template<> struct TD3D12ResourceTraits<FRHIBuffer>`  
_L1127-1130_
- L1124 _public typedef_ `typedef FD3D12UniformBuffer TConcreteType;`
- L1129 _public typedef_ `typedef FD3D12Buffer TConcreteType;`
- L1134 _public typedef_ `typedef FD3D12SamplerState TConcreteType;`
- L1139 _public typedef_ `typedef FD3D12RasterizerState TConcreteType;`
- L1144 _public typedef_ `typedef FD3D12DepthStencilState TConcreteType;`
- L1149 _public typedef_ `typedef FD3D12BlendState TConcreteType;`
- L1154 _public typedef_ `typedef FD3D12GraphicsPipelineState TConcreteType;`
- L1159 _public typedef_ `typedef FD3D12ComputePipelineState TConcreteType;`
- L1164 _public typedef_ `typedef FD3D12WorkGraphPipelineState TConcreteType;`
- L1169 _public typedef_ `typedef FD3D12GPUFence TConcreteType;`
- L1174 _public typedef_ `typedef FD3D12StagingBuffer TConcreteType;`
- L1179 _public typedef_ `typedef FD3D12ShaderBundle TConcreteType;`
- L1186 _public typedef_ `typedef FD3D12RayTracingScene TConcreteType;`
- L1191 _public typedef_ `typedef FD3D12RayTracingGeometry TConcreteType;`
- L1196 _public typedef_ `typedef FD3D12RayTracingPipelineState TConcreteType;`
- L1201 _public typedef_ `typedef FD3D12RayTracingShaderBindingTable TConcreteType;`
- L1206 _public typedef_ `typedef FD3D12RayTracingShader TConcreteType;`

#### struct `TD3D12ResourceTraits`  
`template<> struct TD3D12ResourceTraits<FRHISamplerState>`  
_L1132-1135_
- L1124 _public typedef_ `typedef FD3D12UniformBuffer TConcreteType;`
- L1129 _public typedef_ `typedef FD3D12Buffer TConcreteType;`
- L1134 _public typedef_ `typedef FD3D12SamplerState TConcreteType;`
- L1139 _public typedef_ `typedef FD3D12RasterizerState TConcreteType;`
- L1144 _public typedef_ `typedef FD3D12DepthStencilState TConcreteType;`
- L1149 _public typedef_ `typedef FD3D12BlendState TConcreteType;`
- L1154 _public typedef_ `typedef FD3D12GraphicsPipelineState TConcreteType;`
- L1159 _public typedef_ `typedef FD3D12ComputePipelineState TConcreteType;`
- L1164 _public typedef_ `typedef FD3D12WorkGraphPipelineState TConcreteType;`
- L1169 _public typedef_ `typedef FD3D12GPUFence TConcreteType;`
- L1174 _public typedef_ `typedef FD3D12StagingBuffer TConcreteType;`
- L1179 _public typedef_ `typedef FD3D12ShaderBundle TConcreteType;`
- L1186 _public typedef_ `typedef FD3D12RayTracingScene TConcreteType;`
- L1191 _public typedef_ `typedef FD3D12RayTracingGeometry TConcreteType;`
- L1196 _public typedef_ `typedef FD3D12RayTracingPipelineState TConcreteType;`
- L1201 _public typedef_ `typedef FD3D12RayTracingShaderBindingTable TConcreteType;`
- L1206 _public typedef_ `typedef FD3D12RayTracingShader TConcreteType;`

#### struct `TD3D12ResourceTraits`  
`template<> struct TD3D12ResourceTraits<FRHIRasterizerState>`  
_L1137-1140_
- L1124 _public typedef_ `typedef FD3D12UniformBuffer TConcreteType;`
- L1129 _public typedef_ `typedef FD3D12Buffer TConcreteType;`
- L1134 _public typedef_ `typedef FD3D12SamplerState TConcreteType;`
- L1139 _public typedef_ `typedef FD3D12RasterizerState TConcreteType;`
- L1144 _public typedef_ `typedef FD3D12DepthStencilState TConcreteType;`
- L1149 _public typedef_ `typedef FD3D12BlendState TConcreteType;`
- L1154 _public typedef_ `typedef FD3D12GraphicsPipelineState TConcreteType;`
- L1159 _public typedef_ `typedef FD3D12ComputePipelineState TConcreteType;`
- L1164 _public typedef_ `typedef FD3D12WorkGraphPipelineState TConcreteType;`
- L1169 _public typedef_ `typedef FD3D12GPUFence TConcreteType;`
- L1174 _public typedef_ `typedef FD3D12StagingBuffer TConcreteType;`
- L1179 _public typedef_ `typedef FD3D12ShaderBundle TConcreteType;`
- L1186 _public typedef_ `typedef FD3D12RayTracingScene TConcreteType;`
- L1191 _public typedef_ `typedef FD3D12RayTracingGeometry TConcreteType;`
- L1196 _public typedef_ `typedef FD3D12RayTracingPipelineState TConcreteType;`
- L1201 _public typedef_ `typedef FD3D12RayTracingShaderBindingTable TConcreteType;`
- L1206 _public typedef_ `typedef FD3D12RayTracingShader TConcreteType;`

#### struct `TD3D12ResourceTraits`  
`template<> struct TD3D12ResourceTraits<FRHIDepthStencilState>`  
_L1142-1145_
- L1124 _public typedef_ `typedef FD3D12UniformBuffer TConcreteType;`
- L1129 _public typedef_ `typedef FD3D12Buffer TConcreteType;`
- L1134 _public typedef_ `typedef FD3D12SamplerState TConcreteType;`
- L1139 _public typedef_ `typedef FD3D12RasterizerState TConcreteType;`
- L1144 _public typedef_ `typedef FD3D12DepthStencilState TConcreteType;`
- L1149 _public typedef_ `typedef FD3D12BlendState TConcreteType;`
- L1154 _public typedef_ `typedef FD3D12GraphicsPipelineState TConcreteType;`
- L1159 _public typedef_ `typedef FD3D12ComputePipelineState TConcreteType;`
- L1164 _public typedef_ `typedef FD3D12WorkGraphPipelineState TConcreteType;`
- L1169 _public typedef_ `typedef FD3D12GPUFence TConcreteType;`
- L1174 _public typedef_ `typedef FD3D12StagingBuffer TConcreteType;`
- L1179 _public typedef_ `typedef FD3D12ShaderBundle TConcreteType;`
- L1186 _public typedef_ `typedef FD3D12RayTracingScene TConcreteType;`
- L1191 _public typedef_ `typedef FD3D12RayTracingGeometry TConcreteType;`
- L1196 _public typedef_ `typedef FD3D12RayTracingPipelineState TConcreteType;`
- L1201 _public typedef_ `typedef FD3D12RayTracingShaderBindingTable TConcreteType;`
- L1206 _public typedef_ `typedef FD3D12RayTracingShader TConcreteType;`

#### struct `TD3D12ResourceTraits`  
`template<> struct TD3D12ResourceTraits<FRHIBlendState>`  
_L1147-1150_
- L1124 _public typedef_ `typedef FD3D12UniformBuffer TConcreteType;`
- L1129 _public typedef_ `typedef FD3D12Buffer TConcreteType;`
- L1134 _public typedef_ `typedef FD3D12SamplerState TConcreteType;`
- L1139 _public typedef_ `typedef FD3D12RasterizerState TConcreteType;`
- L1144 _public typedef_ `typedef FD3D12DepthStencilState TConcreteType;`
- L1149 _public typedef_ `typedef FD3D12BlendState TConcreteType;`
- L1154 _public typedef_ `typedef FD3D12GraphicsPipelineState TConcreteType;`
- L1159 _public typedef_ `typedef FD3D12ComputePipelineState TConcreteType;`
- L1164 _public typedef_ `typedef FD3D12WorkGraphPipelineState TConcreteType;`
- L1169 _public typedef_ `typedef FD3D12GPUFence TConcreteType;`
- L1174 _public typedef_ `typedef FD3D12StagingBuffer TConcreteType;`
- L1179 _public typedef_ `typedef FD3D12ShaderBundle TConcreteType;`
- L1186 _public typedef_ `typedef FD3D12RayTracingScene TConcreteType;`
- L1191 _public typedef_ `typedef FD3D12RayTracingGeometry TConcreteType;`
- L1196 _public typedef_ `typedef FD3D12RayTracingPipelineState TConcreteType;`
- L1201 _public typedef_ `typedef FD3D12RayTracingShaderBindingTable TConcreteType;`
- L1206 _public typedef_ `typedef FD3D12RayTracingShader TConcreteType;`

#### struct `TD3D12ResourceTraits`  
`template<> struct TD3D12ResourceTraits<FRHIGraphicsPipelineState>`  
_L1152-1155_
- L1124 _public typedef_ `typedef FD3D12UniformBuffer TConcreteType;`
- L1129 _public typedef_ `typedef FD3D12Buffer TConcreteType;`
- L1134 _public typedef_ `typedef FD3D12SamplerState TConcreteType;`
- L1139 _public typedef_ `typedef FD3D12RasterizerState TConcreteType;`
- L1144 _public typedef_ `typedef FD3D12DepthStencilState TConcreteType;`
- L1149 _public typedef_ `typedef FD3D12BlendState TConcreteType;`
- L1154 _public typedef_ `typedef FD3D12GraphicsPipelineState TConcreteType;`
- L1159 _public typedef_ `typedef FD3D12ComputePipelineState TConcreteType;`
- L1164 _public typedef_ `typedef FD3D12WorkGraphPipelineState TConcreteType;`
- L1169 _public typedef_ `typedef FD3D12GPUFence TConcreteType;`
- L1174 _public typedef_ `typedef FD3D12StagingBuffer TConcreteType;`
- L1179 _public typedef_ `typedef FD3D12ShaderBundle TConcreteType;`
- L1186 _public typedef_ `typedef FD3D12RayTracingScene TConcreteType;`
- L1191 _public typedef_ `typedef FD3D12RayTracingGeometry TConcreteType;`
- L1196 _public typedef_ `typedef FD3D12RayTracingPipelineState TConcreteType;`
- L1201 _public typedef_ `typedef FD3D12RayTracingShaderBindingTable TConcreteType;`
- L1206 _public typedef_ `typedef FD3D12RayTracingShader TConcreteType;`

#### struct `TD3D12ResourceTraits`  
`template<> struct TD3D12ResourceTraits<FRHIComputePipelineState>`  
_L1157-1160_
- L1124 _public typedef_ `typedef FD3D12UniformBuffer TConcreteType;`
- L1129 _public typedef_ `typedef FD3D12Buffer TConcreteType;`
- L1134 _public typedef_ `typedef FD3D12SamplerState TConcreteType;`
- L1139 _public typedef_ `typedef FD3D12RasterizerState TConcreteType;`
- L1144 _public typedef_ `typedef FD3D12DepthStencilState TConcreteType;`
- L1149 _public typedef_ `typedef FD3D12BlendState TConcreteType;`
- L1154 _public typedef_ `typedef FD3D12GraphicsPipelineState TConcreteType;`
- L1159 _public typedef_ `typedef FD3D12ComputePipelineState TConcreteType;`
- L1164 _public typedef_ `typedef FD3D12WorkGraphPipelineState TConcreteType;`
- L1169 _public typedef_ `typedef FD3D12GPUFence TConcreteType;`
- L1174 _public typedef_ `typedef FD3D12StagingBuffer TConcreteType;`
- L1179 _public typedef_ `typedef FD3D12ShaderBundle TConcreteType;`
- L1186 _public typedef_ `typedef FD3D12RayTracingScene TConcreteType;`
- L1191 _public typedef_ `typedef FD3D12RayTracingGeometry TConcreteType;`
- L1196 _public typedef_ `typedef FD3D12RayTracingPipelineState TConcreteType;`
- L1201 _public typedef_ `typedef FD3D12RayTracingShaderBindingTable TConcreteType;`
- L1206 _public typedef_ `typedef FD3D12RayTracingShader TConcreteType;`

#### struct `TD3D12ResourceTraits`  
`template<> struct TD3D12ResourceTraits<FRHIWorkGraphPipelineState>`  
_L1162-1165_
- L1124 _public typedef_ `typedef FD3D12UniformBuffer TConcreteType;`
- L1129 _public typedef_ `typedef FD3D12Buffer TConcreteType;`
- L1134 _public typedef_ `typedef FD3D12SamplerState TConcreteType;`
- L1139 _public typedef_ `typedef FD3D12RasterizerState TConcreteType;`
- L1144 _public typedef_ `typedef FD3D12DepthStencilState TConcreteType;`
- L1149 _public typedef_ `typedef FD3D12BlendState TConcreteType;`
- L1154 _public typedef_ `typedef FD3D12GraphicsPipelineState TConcreteType;`
- L1159 _public typedef_ `typedef FD3D12ComputePipelineState TConcreteType;`
- L1164 _public typedef_ `typedef FD3D12WorkGraphPipelineState TConcreteType;`
- L1169 _public typedef_ `typedef FD3D12GPUFence TConcreteType;`
- L1174 _public typedef_ `typedef FD3D12StagingBuffer TConcreteType;`
- L1179 _public typedef_ `typedef FD3D12ShaderBundle TConcreteType;`
- L1186 _public typedef_ `typedef FD3D12RayTracingScene TConcreteType;`
- L1191 _public typedef_ `typedef FD3D12RayTracingGeometry TConcreteType;`
- L1196 _public typedef_ `typedef FD3D12RayTracingPipelineState TConcreteType;`
- L1201 _public typedef_ `typedef FD3D12RayTracingShaderBindingTable TConcreteType;`
- L1206 _public typedef_ `typedef FD3D12RayTracingShader TConcreteType;`

#### struct `TD3D12ResourceTraits`  
`template<> struct TD3D12ResourceTraits<FRHIGPUFence>`  
_L1167-1170_
- L1124 _public typedef_ `typedef FD3D12UniformBuffer TConcreteType;`
- L1129 _public typedef_ `typedef FD3D12Buffer TConcreteType;`
- L1134 _public typedef_ `typedef FD3D12SamplerState TConcreteType;`
- L1139 _public typedef_ `typedef FD3D12RasterizerState TConcreteType;`
- L1144 _public typedef_ `typedef FD3D12DepthStencilState TConcreteType;`
- L1149 _public typedef_ `typedef FD3D12BlendState TConcreteType;`
- L1154 _public typedef_ `typedef FD3D12GraphicsPipelineState TConcreteType;`
- L1159 _public typedef_ `typedef FD3D12ComputePipelineState TConcreteType;`
- L1164 _public typedef_ `typedef FD3D12WorkGraphPipelineState TConcreteType;`
- L1169 _public typedef_ `typedef FD3D12GPUFence TConcreteType;`
- L1174 _public typedef_ `typedef FD3D12StagingBuffer TConcreteType;`
- L1179 _public typedef_ `typedef FD3D12ShaderBundle TConcreteType;`
- L1186 _public typedef_ `typedef FD3D12RayTracingScene TConcreteType;`
- L1191 _public typedef_ `typedef FD3D12RayTracingGeometry TConcreteType;`
- L1196 _public typedef_ `typedef FD3D12RayTracingPipelineState TConcreteType;`
- L1201 _public typedef_ `typedef FD3D12RayTracingShaderBindingTable TConcreteType;`
- L1206 _public typedef_ `typedef FD3D12RayTracingShader TConcreteType;`

#### struct `TD3D12ResourceTraits`  
`template<> struct TD3D12ResourceTraits<FRHIStagingBuffer>`  
_L1172-1175_
- L1124 _public typedef_ `typedef FD3D12UniformBuffer TConcreteType;`
- L1129 _public typedef_ `typedef FD3D12Buffer TConcreteType;`
- L1134 _public typedef_ `typedef FD3D12SamplerState TConcreteType;`
- L1139 _public typedef_ `typedef FD3D12RasterizerState TConcreteType;`
- L1144 _public typedef_ `typedef FD3D12DepthStencilState TConcreteType;`
- L1149 _public typedef_ `typedef FD3D12BlendState TConcreteType;`
- L1154 _public typedef_ `typedef FD3D12GraphicsPipelineState TConcreteType;`
- L1159 _public typedef_ `typedef FD3D12ComputePipelineState TConcreteType;`
- L1164 _public typedef_ `typedef FD3D12WorkGraphPipelineState TConcreteType;`
- L1169 _public typedef_ `typedef FD3D12GPUFence TConcreteType;`
- L1174 _public typedef_ `typedef FD3D12StagingBuffer TConcreteType;`
- L1179 _public typedef_ `typedef FD3D12ShaderBundle TConcreteType;`
- L1186 _public typedef_ `typedef FD3D12RayTracingScene TConcreteType;`
- L1191 _public typedef_ `typedef FD3D12RayTracingGeometry TConcreteType;`
- L1196 _public typedef_ `typedef FD3D12RayTracingPipelineState TConcreteType;`
- L1201 _public typedef_ `typedef FD3D12RayTracingShaderBindingTable TConcreteType;`
- L1206 _public typedef_ `typedef FD3D12RayTracingShader TConcreteType;`

#### struct `TD3D12ResourceTraits`  
`template<> struct TD3D12ResourceTraits<FRHIShaderBundle>`  
_L1177-1180_
- L1124 _public typedef_ `typedef FD3D12UniformBuffer TConcreteType;`
- L1129 _public typedef_ `typedef FD3D12Buffer TConcreteType;`
- L1134 _public typedef_ `typedef FD3D12SamplerState TConcreteType;`
- L1139 _public typedef_ `typedef FD3D12RasterizerState TConcreteType;`
- L1144 _public typedef_ `typedef FD3D12DepthStencilState TConcreteType;`
- L1149 _public typedef_ `typedef FD3D12BlendState TConcreteType;`
- L1154 _public typedef_ `typedef FD3D12GraphicsPipelineState TConcreteType;`
- L1159 _public typedef_ `typedef FD3D12ComputePipelineState TConcreteType;`
- L1164 _public typedef_ `typedef FD3D12WorkGraphPipelineState TConcreteType;`
- L1169 _public typedef_ `typedef FD3D12GPUFence TConcreteType;`
- L1174 _public typedef_ `typedef FD3D12StagingBuffer TConcreteType;`
- L1179 _public typedef_ `typedef FD3D12ShaderBundle TConcreteType;`
- L1186 _public typedef_ `typedef FD3D12RayTracingScene TConcreteType;`
- L1191 _public typedef_ `typedef FD3D12RayTracingGeometry TConcreteType;`
- L1196 _public typedef_ `typedef FD3D12RayTracingPipelineState TConcreteType;`
- L1201 _public typedef_ `typedef FD3D12RayTracingShaderBindingTable TConcreteType;`
- L1206 _public typedef_ `typedef FD3D12RayTracingShader TConcreteType;`

#### struct `TD3D12ResourceTraits`  
`template<> struct TD3D12ResourceTraits<FRHIRayTracingScene>`  
_L1184-1187_
- L1124 _public typedef_ `typedef FD3D12UniformBuffer TConcreteType;`
- L1129 _public typedef_ `typedef FD3D12Buffer TConcreteType;`
- L1134 _public typedef_ `typedef FD3D12SamplerState TConcreteType;`
- L1139 _public typedef_ `typedef FD3D12RasterizerState TConcreteType;`
- L1144 _public typedef_ `typedef FD3D12DepthStencilState TConcreteType;`
- L1149 _public typedef_ `typedef FD3D12BlendState TConcreteType;`
- L1154 _public typedef_ `typedef FD3D12GraphicsPipelineState TConcreteType;`
- L1159 _public typedef_ `typedef FD3D12ComputePipelineState TConcreteType;`
- L1164 _public typedef_ `typedef FD3D12WorkGraphPipelineState TConcreteType;`
- L1169 _public typedef_ `typedef FD3D12GPUFence TConcreteType;`
- L1174 _public typedef_ `typedef FD3D12StagingBuffer TConcreteType;`
- L1179 _public typedef_ `typedef FD3D12ShaderBundle TConcreteType;`
- L1186 _public typedef_ `typedef FD3D12RayTracingScene TConcreteType;`
- L1191 _public typedef_ `typedef FD3D12RayTracingGeometry TConcreteType;`
- L1196 _public typedef_ `typedef FD3D12RayTracingPipelineState TConcreteType;`
- L1201 _public typedef_ `typedef FD3D12RayTracingShaderBindingTable TConcreteType;`
- L1206 _public typedef_ `typedef FD3D12RayTracingShader TConcreteType;`

#### struct `TD3D12ResourceTraits`  
`template<> struct TD3D12ResourceTraits<FRHIRayTracingGeometry>`  
_L1189-1192_
- L1124 _public typedef_ `typedef FD3D12UniformBuffer TConcreteType;`
- L1129 _public typedef_ `typedef FD3D12Buffer TConcreteType;`
- L1134 _public typedef_ `typedef FD3D12SamplerState TConcreteType;`
- L1139 _public typedef_ `typedef FD3D12RasterizerState TConcreteType;`
- L1144 _public typedef_ `typedef FD3D12DepthStencilState TConcreteType;`
- L1149 _public typedef_ `typedef FD3D12BlendState TConcreteType;`
- L1154 _public typedef_ `typedef FD3D12GraphicsPipelineState TConcreteType;`
- L1159 _public typedef_ `typedef FD3D12ComputePipelineState TConcreteType;`
- L1164 _public typedef_ `typedef FD3D12WorkGraphPipelineState TConcreteType;`
- L1169 _public typedef_ `typedef FD3D12GPUFence TConcreteType;`
- L1174 _public typedef_ `typedef FD3D12StagingBuffer TConcreteType;`
- L1179 _public typedef_ `typedef FD3D12ShaderBundle TConcreteType;`
- L1186 _public typedef_ `typedef FD3D12RayTracingScene TConcreteType;`
- L1191 _public typedef_ `typedef FD3D12RayTracingGeometry TConcreteType;`
- L1196 _public typedef_ `typedef FD3D12RayTracingPipelineState TConcreteType;`
- L1201 _public typedef_ `typedef FD3D12RayTracingShaderBindingTable TConcreteType;`
- L1206 _public typedef_ `typedef FD3D12RayTracingShader TConcreteType;`

#### struct `TD3D12ResourceTraits`  
`template<> struct TD3D12ResourceTraits<FRHIRayTracingPipelineState>`  
_L1194-1197_
- L1124 _public typedef_ `typedef FD3D12UniformBuffer TConcreteType;`
- L1129 _public typedef_ `typedef FD3D12Buffer TConcreteType;`
- L1134 _public typedef_ `typedef FD3D12SamplerState TConcreteType;`
- L1139 _public typedef_ `typedef FD3D12RasterizerState TConcreteType;`
- L1144 _public typedef_ `typedef FD3D12DepthStencilState TConcreteType;`
- L1149 _public typedef_ `typedef FD3D12BlendState TConcreteType;`
- L1154 _public typedef_ `typedef FD3D12GraphicsPipelineState TConcreteType;`
- L1159 _public typedef_ `typedef FD3D12ComputePipelineState TConcreteType;`
- L1164 _public typedef_ `typedef FD3D12WorkGraphPipelineState TConcreteType;`
- L1169 _public typedef_ `typedef FD3D12GPUFence TConcreteType;`
- L1174 _public typedef_ `typedef FD3D12StagingBuffer TConcreteType;`
- L1179 _public typedef_ `typedef FD3D12ShaderBundle TConcreteType;`
- L1186 _public typedef_ `typedef FD3D12RayTracingScene TConcreteType;`
- L1191 _public typedef_ `typedef FD3D12RayTracingGeometry TConcreteType;`
- L1196 _public typedef_ `typedef FD3D12RayTracingPipelineState TConcreteType;`
- L1201 _public typedef_ `typedef FD3D12RayTracingShaderBindingTable TConcreteType;`
- L1206 _public typedef_ `typedef FD3D12RayTracingShader TConcreteType;`

#### struct `TD3D12ResourceTraits`  
`template<> struct TD3D12ResourceTraits<FRHIShaderBindingTable>`  
_L1199-1202_
- L1124 _public typedef_ `typedef FD3D12UniformBuffer TConcreteType;`
- L1129 _public typedef_ `typedef FD3D12Buffer TConcreteType;`
- L1134 _public typedef_ `typedef FD3D12SamplerState TConcreteType;`
- L1139 _public typedef_ `typedef FD3D12RasterizerState TConcreteType;`
- L1144 _public typedef_ `typedef FD3D12DepthStencilState TConcreteType;`
- L1149 _public typedef_ `typedef FD3D12BlendState TConcreteType;`
- L1154 _public typedef_ `typedef FD3D12GraphicsPipelineState TConcreteType;`
- L1159 _public typedef_ `typedef FD3D12ComputePipelineState TConcreteType;`
- L1164 _public typedef_ `typedef FD3D12WorkGraphPipelineState TConcreteType;`
- L1169 _public typedef_ `typedef FD3D12GPUFence TConcreteType;`
- L1174 _public typedef_ `typedef FD3D12StagingBuffer TConcreteType;`
- L1179 _public typedef_ `typedef FD3D12ShaderBundle TConcreteType;`
- L1186 _public typedef_ `typedef FD3D12RayTracingScene TConcreteType;`
- L1191 _public typedef_ `typedef FD3D12RayTracingGeometry TConcreteType;`
- L1196 _public typedef_ `typedef FD3D12RayTracingPipelineState TConcreteType;`
- L1201 _public typedef_ `typedef FD3D12RayTracingShaderBindingTable TConcreteType;`
- L1206 _public typedef_ `typedef FD3D12RayTracingShader TConcreteType;`

#### struct `TD3D12ResourceTraits`  
`template<> struct TD3D12ResourceTraits<FRHIRayTracingShader>`  
_L1204-1207_
- L1124 _public typedef_ `typedef FD3D12UniformBuffer TConcreteType;`
- L1129 _public typedef_ `typedef FD3D12Buffer TConcreteType;`
- L1134 _public typedef_ `typedef FD3D12SamplerState TConcreteType;`
- L1139 _public typedef_ `typedef FD3D12RasterizerState TConcreteType;`
- L1144 _public typedef_ `typedef FD3D12DepthStencilState TConcreteType;`
- L1149 _public typedef_ `typedef FD3D12BlendState TConcreteType;`
- L1154 _public typedef_ `typedef FD3D12GraphicsPipelineState TConcreteType;`
- L1159 _public typedef_ `typedef FD3D12ComputePipelineState TConcreteType;`
- L1164 _public typedef_ `typedef FD3D12WorkGraphPipelineState TConcreteType;`
- L1169 _public typedef_ `typedef FD3D12GPUFence TConcreteType;`
- L1174 _public typedef_ `typedef FD3D12StagingBuffer TConcreteType;`
- L1179 _public typedef_ `typedef FD3D12ShaderBundle TConcreteType;`
- L1186 _public typedef_ `typedef FD3D12RayTracingScene TConcreteType;`
- L1191 _public typedef_ `typedef FD3D12RayTracingGeometry TConcreteType;`
- L1196 _public typedef_ `typedef FD3D12RayTracingPipelineState TConcreteType;`
- L1201 _public typedef_ `typedef FD3D12RayTracingShaderBindingTable TConcreteType;`
- L1206 _public typedef_ `typedef FD3D12RayTracingShader TConcreteType;`

#### Free symbols / members of external scopes

- L32 _typedef_ `using FD3D12SyncPointRef = TRefCountPtr<FD3D12SyncPoint>;`
- L43 _macro_ `#define D3D12_WITH_CUSTOM_TEXTURE_LAYOUT 0`
- L47 _prototype_ `extern void ApplyCustomTextureLayout(FD3D12ResourceDesc& TextureLayout, FD3D12Adapter& Adapter);`
- L585 _typedef_ `typedef class FD3D12BuddyAllocator FD3D12BaseAllocatorType;`
- L769 _member_ `FD3D12BaseAllocatorType* Allocator;` (scope `FD3D12ResourceLocation::__anon2ebbb012010a`)
- L770 _member_ `FD3D12PoolAllocator* PoolAllocator;` (scope `FD3D12ResourceLocation::__anon2ebbb012010a`)
- L1063 _namespace_ `namespace D3D12BufferStats`
- L1065 _prototype_ `void UpdateBufferStats(FD3D12Buffer& Buffer, bool bAllocating);` (scope `D3D12BufferStats`)

### `Source/Runtime/D3D12RHI/Private/D3D12RootSignature.h` (Private)


#### enum `ERootParameterKeys`  
`enum ERootParameterKeys`  
_L13-46_
- desc: Root parameter keys grouped by visibility.
- L15 _public enumerator_ `PS_SRVs`
- L16 _public enumerator_ `PS_CBVs`
- L17 _public enumerator_ `PS_RootCBVs`
- L18 _public enumerator_ `PS_Samplers`
- L19 _public enumerator_ `VS_SRVs`
- L20 _public enumerator_ `VS_CBVs`
- L21 _public enumerator_ `VS_RootCBVs`
- L22 _public enumerator_ `VS_Samplers`
- L23 _public enumerator_ `VS_UAVs`
- L24 _public enumerator_ `GS_SRVs`
- L25 _public enumerator_ `GS_CBVs`
- L26 _public enumerator_ `GS_RootCBVs`
- L27 _public enumerator_ `GS_Samplers`
- L29 _public enumerator_ `MS_SRVs`
- L30 _public enumerator_ `MS_CBVs`
- L31 _public enumerator_ `MS_RootCBVs`
- L32 _public enumerator_ `MS_Samplers`
- L33 _public enumerator_ `MS_UAVs`
- L34 _public enumerator_ `AS_SRVs`
- L35 _public enumerator_ `AS_CBVs`
- L36 _public enumerator_ `AS_RootCBVs`
- L37 _public enumerator_ `AS_Samplers`
- L38 _public enumerator_ `AS_UAVs`
- L40 _public enumerator_ `ALL_SRVs`
- L41 _public enumerator_ `ALL_CBVs`
- L42 _public enumerator_ `ALL_RootCBVs`
- L43 _public enumerator_ `ALL_Samplers`
- L44 _public enumerator_ `ALL_UAVs` — non-VS stages (PS, CS, etc.)
- L45 _public enumerator_ `RPK_RootParameterKeyCount`

#### class `FD3D12RootSignatureDesc`  
`class FD3D12RootSignatureDesc`  
_L50-74_
- L53 _public prototype_ `explicit FD3D12RootSignatureDesc(const FD3D12QuantizedBoundShaderState& QBSS, const D3D12_RESOURCE_BINDING_TIER ResourceBindingTier);`
- L55 _public function_ `inline const D3D12_VERSIONED_ROOT_SIGNATURE_DESC& GetDesc() const`
- L57 _public member_ `static constexpr uint32 MaxRootParameters = 32;` — Arbitrary max, increase as needed.
- L59 _public function_ `inline int8 GetRootConstantsSlot() const`
- L60 _public function_ `inline int8 GetDiagnosticBufferSlot() const`
- L61 _public function_ `inline int8 GetStaticShaderBindingSlot() const`
- L62 _public function_ `inline int8 GetStaticShaderBindingCount() const`
- L66 _private member_ `uint32 RootParametersSize;` — The size of all root parameters in the root signature. Size in DWORDs, the limit is 64.
- L67 _private member_ `int8 RootConstantsSlot = -1;`
- L68 _private member_ `int8 DiagnosticBufferSlot = -1;`
- L69 _private member_ `int8 StaticShaderBindingSlot = -1;`
- L70 _private member_ `int8 StaticShaderBindingCount = -1;`
- L71 _private member_ `CD3DX12_ROOT_PARAMETER1 TableSlots[MaxRootParameters];`
- L72 _private member_ `CD3DX12_DESCRIPTOR_RANGE1 DescriptorRanges[MaxRootParameters];`
- L73 _private member_ `CD3DX12_VERSIONED_ROOT_SIGNATURE_DESC RootDesc;`

#### class `FD3D12RootSignature`  
`class FD3D12RootSignature : public FD3D12AdapterChild`  
_L76-532_
- inherits: `FD3D12AdapterChild`
- L92 _public function_ `explicit FD3D12RootSignature(FD3D12Adapter* InParent) : FD3D12AdapterChild(InParent)`
- L95 _public function_ `explicit FD3D12RootSignature(FD3D12Adapter* InParent, const FD3D12QuantizedBoundShaderState& InQBSS) : FD3D12AdapterChild(InParent)`
- L101 _public prototype_ `void Init(const FD3D12QuantizedBoundShaderState& InQBSS);`
- L102 _public prototype_ `void Init(const D3D12_VERSIONED_ROOT_SIGNATURE_DESC& InDesc, ERootSignatureType InRootSignatureType);`
- L104 _public prototype_ `void InitStaticGraphicsRootSignature(EShaderBindingLayoutFlags InFlags);`
- L105 _public prototype_ `void InitStaticComputeRootSignatureDesc(EShaderBindingLayoutFlags InFlags);`
- L107 _public prototype_ `void InitStaticRayTracingGlobalRootSignatureDesc(EShaderBindingLayoutFlags InFlags);`
- L108 _public prototype_ `void InitStaticRayTracingLocalRootSignatureDesc(EShaderBindingLayoutFlags InFlags);`
- L111 _public function_ `ID3D12RootSignature* GetRootSignature() const`
- L112 _public function_ `ID3DBlob* GetRootSignatureBlob() const`
- L114 _public function_ `inline uint32 SamplerRDTBindSlot(EShaderFrequency ShaderStage) const`
- L132 _public function_ `inline uint32 SRVRDTBindSlot(EShaderFrequency ShaderStage) const`
- L150 _public function_ `inline uint32 CBVRDTBindSlot(EShaderFrequency ShaderStage) const`
- L168 _public function_ `inline uint32 CBVRDBaseBindSlot(EShaderFrequency ShaderStage) const`
- L188 _public function_ `inline uint32 CBVRDBindSlot(EShaderFrequency ShaderStage, uint32 BufferIndex) const`
- L194 _public function_ `inline uint32 UAVRDTBindSlot(EShaderFrequency ShaderStage) const`
- L213 _public function_ `inline static bool IsValidBindSlot(uint32 BindSlotMapIndex)`
- L218 _public function_ `inline bool HasUAVs() const`
- L219 _public function_ `inline bool HasSRVs() const`
- L220 _public function_ `inline bool HasCBVs() const`
- L221 _public function_ `inline bool HasRootCBs() const`
- L222 _public function_ `inline bool HasTableResources() const`
- L223 _public function_ `inline bool HasTableConstants() const`
- L224 _public function_ `inline bool HasSamplers() const`
- L227 _public function_ `bool UsesDynamicResources() const`
- L228 _public function_ `bool UsesDynamicSamplers() const`
- L230 _public function_ `constexpr bool UsesDynamicResources() const`
- L231 _public function_ `constexpr bool UsesDynamicSamplers() const`
- L234 _public function_ `inline bool HasVS() const`
- L235 _public function_ `inline bool HasMS() const`
- L236 _public function_ `inline bool HasAS() const`
- L237 _public function_ `inline bool HasGS() const`
- L238 _public function_ `inline bool HasPS() const`
- L239 _public function_ `inline bool HasCS() const` — Root signatures can be used for Graphics and/or Compute because they exist in separate bind spaces.
- L240 _public function_ `inline uint32 MaxSamplerCount(uint32 ShaderStage) const`
- L241 _public function_ `inline uint32 MaxSRVCount(uint32 ShaderStage) const`
- L242 _public function_ `inline uint32 MaxCBVCount(uint32 ShaderStage) const`
- L243 _public function_ `inline uint32 MaxUAVCount(uint32 ShaderStage) const`
- L244 _public function_ `inline CBVSlotMask CBVRegisterMask(uint32 ShaderStage) const`
- L246 _public function_ `uint32 GetBindSlotOffsetInBytes(uint8 BindSlotIndex) const`
- L247 _public function_ `uint32 GetTotalRootSignatureSizeInBytes() const`
- L249 _public function_ `inline int8 GetRootConstantsSlot() const`
- L250 _public function_ `inline int8 GetStaticShaderBindingSlot() const`
- L251 _public function_ `inline int8 GetStaticShaderBindingCount() const`
- L254 _public function_ `inline int8 GetDiagnosticBufferSlot() const` — Returns root parameter slot for the internal shader diagnostic buffer (used for asserts, etc.) or -1 if not available.
- L257 _private prototype_ `void AnalyzeSignature(const D3D12_VERSIONED_ROOT_SIGNATURE_DESC& Desc, ERootSignatureType InRootSignatureType);`
- L260 _private prototype_ `template<typename RootSignatureDescType> void InternalAnalyzeSignature(const RootSignatureDescType& Desc, ERootSignatureType InRootSignatureType);`
- L262 _private function_ `inline bool HasVisibility(const D3D12_SHADER_VISIBILITY& ParameterVisibility, const D3D12_SHADER_VISIBILITY& Visibility) const`
- L267 _private function_ `inline void SetSamplersRDTBindSlot(EShaderFrequency SF, uint8 RootParameterIndex)`
- L293 _private function_ `inline void SetSRVRDTBindSlot(EShaderFrequency SF, uint8 RootParameterIndex)`
- L319 _private function_ `inline void SetCBVRDTBindSlot(EShaderFrequency SF, uint8 RootParameterIndex)`
- L345 _private function_ `inline void SetCBVRDBindSlot(EShaderFrequency SF, uint8 RootParameterIndex)`
- L371 _private function_ `inline void SetUAVRDTBindSlot(EShaderFrequency SF, uint8 RootParameterIndex)`
- L396 _private function_ `inline void SetMaxSamplerCount(EShaderFrequency SF, uint8 Count)`
- L412 _private function_ `inline void SetMaxSRVCount(EShaderFrequency SF, uint8 Count)`
- L430 _private function_ `template<typename DescriptorRangeType> inline void UpdateCBVRegisterMaskWithDescriptorRange(EShaderFrequency SF, const DescriptorRangeType& Range)` — Update the mask that indicates what shader registers are used in the descriptor table.
- L449 _private function_ `template<typename DescriptorType> inline void UpdateCBVRegisterMaskWithDescriptor(EShaderFrequency SF, const DescriptorType& Descriptor)` — Update the mask that indicates what shader registers are used in the root descriptor.
- L462 _private function_ `inline void SetMaxCBVCount(EShaderFrequency SF, uint8 Count)`
- L478 _private function_ `inline void IncrementMaxCBVCount(EShaderFrequency SF, uint8 Count)`
- L494 _private function_ `inline void SetMaxUAVCount(EShaderFrequency SF, uint8 Count)`
- L510 _private member_ `TRefCountPtr<ID3D12RootSignature> RootSignature;`
- L511 _private member_ `uint8 BindSlotMap[RPK_RootParameterKeyCount];` — This map uses an enum as a key to lookup the root parameter index
- L512 _private member_ `static constexpr uint8 InvalidBindSlotMapIndex = 0xFF;`
- L513 _private member_ `ShaderStage Stage[SF_NumFrequencies];`
- L514 _private member_ `TRefCountPtr<ID3DBlob> RootSignatureBlob;`
- L516 _private member_ `uint8 BindSlotOffsetsInDWORDs[FD3D12RootSignatureDesc::MaxRootParameters] = {};`
- L517 _private member_ `uint8 TotalRootSignatureSizeInDWORDs = 0;`
- L518 _private member_ `int8 RootConstantsSlot = -1;`
- L519 _private member_ `int8 DiagnosticBufferSlot = -1;`
- L520 _private member_ `int8 StaticShaderBindingSlot = -1;`
- L521 _private member_ `int8 StaticShaderBindingCount = -1;`
- L523 _private member_ `uint8 bHasUAVs : 1;`
- L524 _private member_ `uint8 bHasSRVs : 1;`
- L525 _private member_ `uint8 bHasCBVs : 1;`
- L526 _private member_ `uint8 bHasRootCBs : 1;`
- L527 _private member_ `uint8 bHasSamplers : 1;`
- L529 _private member_ `uint8 bUsesDynamicResources : 1;`
- L530 _private member_ `uint8 bUsesDynamicSamplers : 1;`

#### struct `FD3D12RootSignature::ShaderStage`  
`struct ShaderStage`  
_L80-89_
- desc: Struct for all the useful info we want per shader stage.
- L83 _public member_ `uint8 MaxCBVCount = 0;` — TODO: Make these arrays and index into them by type instead of individual variables.
- L84 _public member_ `uint8 MaxSRVCount = 0;`
- L85 _public member_ `uint8 MaxSamplerCount = 0;`
- L86 _public member_ `uint8 MaxUAVCount = 0;`
- L87 _public member_ `CBVSlotMask CBVRegisterMask = 0;`
- L88 _public member_ `bool bVisible = false;`

#### class `FD3D12RootSignatureManager`  
`class FD3D12RootSignatureManager : public FD3D12AdapterChild`  
_L534-555_
- inherits: `FD3D12AdapterChild`
- L537 _public function_ `explicit FD3D12RootSignatureManager(FD3D12Adapter* InParent) : FD3D12AdapterChild(InParent)`
- L541 _public function_ `~FD3D12RootSignatureManager()`
- L545 _public prototype_ `void Destroy();`
- L547 _public prototype_ `FD3D12RootSignature* GetRootSignature(const FD3D12QuantizedBoundShaderState& QBSS);`
- L548 _public prototype_ `FD3D12QuantizedBoundShaderState GetQuantizedBoundShaderState(const FD3D12RootSignature* const RootSignature);`
- L551 _private member_ `FCriticalSection CS;`
- L552 _private prototype_ `FD3D12RootSignature* CreateRootSignature(const FD3D12QuantizedBoundShaderState& QBSS);`
- L554 _private member_ `TMap<FD3D12QuantizedBoundShaderState, FD3D12RootSignature*> RootSignatureMap;`

### `Source/Runtime/D3D12RHI/Private/D3D12Shader.h` (Private)


#### struct `TTypeTraits`  
`template <> struct TTypeTraits<D3D12_INPUT_ELEMENT_DESC> : public TTypeTraitsBase < D3D12_INPUT_ELEMENT_DESC >`  
_L17-20_
- inherits: `TTypeTraitsBase<D3D12_INPUT_ELEMENT_DESC>`

#### enum `TTypeTraits::(anonymous)`  
`enum`  
_L19-19_

#### class `FD3D12VertexDeclaration`  
`class FD3D12VertexDeclaration : public FRHIVertexDeclaration`  
_L26-47_
- inherits: `FRHIVertexDeclaration`
- desc: This represents a vertex declaration that hasn't been combined with a specific shader to create a bound shader.
- L30 _public member_ `FD3D12VertexElements VertexElements;` — Elements of the vertex declaration.
- L32 _public member_ `TStaticArray<uint16, MaxVertexElementCount> StreamStrides;`
- L33 _public member_ `uint32 Hash;`
- L34 _public member_ `uint32 HashNoStrides;`
- L37 _public function_ `explicit FD3D12VertexDeclaration(const FD3D12VertexElements& InElements, const uint16* InStrides, const uint32 InHash, const uint32 InHashNoStrides) : VertexElements(InElements) , Hash(InHash) , HashNoStrides(InHashNoStrides)` — Initialization constructor.
- L45 _public prototype_ `virtual bool GetInitializer(FVertexDeclarationElementList& Init) final override;`
- L46 _public function_ `virtual uint32 GetPrecachePSOHash() const final override`

#### struct `ShaderBytecodeHash`  
`struct ShaderBytecodeHash`  
_L53-66_
- L55 _public member_ `uint64 Hash[2];`
- L57 _public function_ `bool operator ==(const ShaderBytecodeHash& b) const`
- L62 _public function_ `bool operator !=(const ShaderBytecodeHash& b) const`

#### struct `FD3D12ShaderData`  
`struct FD3D12ShaderData`  
_L68-122_
- L71 _public member_ `TArray<uint8> Code;` — The shader's bytecode, with custom data in the last byte.
- L73 _public member_ `FShaderCodePackedResourceCounts ResourceCounts{};`
- L76 _public member_ `uint32 ShaderBindingLayoutHash = 0;` — Hash of the static shader binding layout used during shader gen
- L79 _public member_ `TArray<FShaderCodeVendorExtension> VendorExtensions;`
- L83 _public member_ `EShaderCodeFeatures Features = EShaderCodeFeatures::None;`
- L86 _public function_ `D3D12_SHADER_BYTECODE GetShaderBytecode() const`
- L91 _public function_ `ShaderBytecodeHash GetBytecodeHash() const`
- L108 _public function_ `FORCEINLINE EShaderCodeFeatures GetFeatures() const`
- L113 _public function_ `FORCEINLINE bool UsesDiagnosticBuffer() const`
- L114 _public function_ `FORCEINLINE bool UsesGlobalUniformBuffer() const`
- L116 _public function_ `FORCEINLINE bool UsesBindlessResources() const`
- L117 _public function_ `FORCEINLINE bool UsesBindlessSamplers() const`
- L119 _public function_ `FORCEINLINE bool UsesRootConstants() const`
- L121 _public prototype_ `bool InitCommon(TArrayView<const uint8> InCode);`

#### class `FD3D12VertexShader`  
`class FD3D12VertexShader : public FRHIVertexShader, public FD3D12ShaderData`  
_L125-129_
- inherits: `FRHIVertexShader,FD3D12ShaderData`
- desc: This represents a vertex shader that hasn't been combined with a specific declaration to create a bound shader.

#### enum `FD3D12VertexShader::(anonymous)`  
`enum`  
_L128-128_

#### class `FD3D12MeshShader`  
`class FD3D12MeshShader : public FRHIMeshShader, public FD3D12ShaderData`  
_L131-135_
- inherits: `FRHIMeshShader,FD3D12ShaderData`

#### enum `FD3D12MeshShader::(anonymous)`  
`enum`  
_L134-134_

#### class `FD3D12AmplificationShader`  
`class FD3D12AmplificationShader : public FRHIAmplificationShader, public FD3D12ShaderData`  
_L137-141_
- inherits: `FRHIAmplificationShader,FD3D12ShaderData`

#### enum `FD3D12AmplificationShader::(anonymous)`  
`enum`  
_L140-140_

#### class `FD3D12GeometryShader`  
`class FD3D12GeometryShader : public FRHIGeometryShader, public FD3D12ShaderData`  
_L143-147_
- inherits: `FRHIGeometryShader,FD3D12ShaderData`

#### enum `FD3D12GeometryShader::(anonymous)`  
`enum`  
_L146-146_

#### class `FD3D12PixelShader`  
`class FD3D12PixelShader : public FRHIPixelShader, public FD3D12ShaderData`  
_L149-157_
- inherits: `FRHIPixelShader,FD3D12ShaderData`
- L155 _public member_ `FString EntryPoint;`

#### enum `FD3D12PixelShader::(anonymous)`  
`enum`  
_L152-152_

#### class `FD3D12ComputeShader`  
`class FD3D12ComputeShader : public FRHIComputeShader, public FD3D12ShaderData`  
_L159-165_
- inherits: `FRHIComputeShader,FD3D12ShaderData`
- L164 _public member_ `const FD3D12RootSignature* RootSignature = nullptr;`

#### enum `FD3D12ComputeShader::(anonymous)`  
`enum`  
_L162-162_

#### class `FD3D12WorkGraphShader`  
`class FD3D12WorkGraphShader : public FRHIWorkGraphShader, public FD3D12ShaderData`  
_L167-175_
- inherits: `FRHIWorkGraphShader,FD3D12ShaderData`
- L170 _public function_ `explicit FD3D12WorkGraphShader(EShaderFrequency InFrequency) : FRHIWorkGraphShader(InFrequency)`
- L172 _public member_ `const FD3D12RootSignature* RootSignature = nullptr;`
- L174 _public member_ `FString EntryPoint;`

#### class `FD3D12RayTracingShader`  
`class FD3D12RayTracingShader : public FRHIRayTracingShader, public FD3D12ShaderData`  
_L179-191_
- inherits: `FRHIRayTracingShader,FD3D12ShaderData`
- L182 _public function_ `explicit FD3D12RayTracingShader(EShaderFrequency InFrequency) : FRHIRayTracingShader(InFrequency)`
- L184 _public member_ `const FD3D12RootSignature* LocalRootSignature = nullptr;`
- L187 _public member_ `FString EntryPoint;` — The shader's DXIL entrypoint & base export name for DXR (required for RTPSO creation)
- L188 _public member_ `FString AnyHitEntryPoint;` — Optional any-hit shader entry point for SF_RayHitGroup.
- L189 _public member_ `FString IntersectionEntryPoint;` — Optional intersection shader entry point for SF_RayHitGroup.
- L190 _public member_ `bool bPrecompiledPSO = false;`

#### struct `TD3D12ResourceTraits`  
`template<> struct TD3D12ResourceTraits<FRHIVertexShader>`  
_L196-199_
- L198 _public typedef_ `typedef FD3D12VertexShader TConcreteType;`
- L203 _public typedef_ `typedef FD3D12MeshShader TConcreteType;`
- L208 _public typedef_ `typedef FD3D12AmplificationShader TConcreteType;`
- L213 _public typedef_ `typedef FD3D12GeometryShader TConcreteType;`
- L218 _public typedef_ `typedef FD3D12PixelShader TConcreteType;`
- L223 _public typedef_ `typedef FD3D12ComputeShader TConcreteType;`
- L228 _public typedef_ `typedef FD3D12WorkGraphShader TConcreteType;`
- L233 _public typedef_ `typedef FD3D12VertexDeclaration TConcreteType;`

#### struct `TD3D12ResourceTraits`  
`template<> struct TD3D12ResourceTraits<FRHIMeshShader>`  
_L201-204_
- L198 _public typedef_ `typedef FD3D12VertexShader TConcreteType;`
- L203 _public typedef_ `typedef FD3D12MeshShader TConcreteType;`
- L208 _public typedef_ `typedef FD3D12AmplificationShader TConcreteType;`
- L213 _public typedef_ `typedef FD3D12GeometryShader TConcreteType;`
- L218 _public typedef_ `typedef FD3D12PixelShader TConcreteType;`
- L223 _public typedef_ `typedef FD3D12ComputeShader TConcreteType;`
- L228 _public typedef_ `typedef FD3D12WorkGraphShader TConcreteType;`
- L233 _public typedef_ `typedef FD3D12VertexDeclaration TConcreteType;`

#### struct `TD3D12ResourceTraits`  
`template<> struct TD3D12ResourceTraits<FRHIAmplificationShader>`  
_L206-209_
- L198 _public typedef_ `typedef FD3D12VertexShader TConcreteType;`
- L203 _public typedef_ `typedef FD3D12MeshShader TConcreteType;`
- L208 _public typedef_ `typedef FD3D12AmplificationShader TConcreteType;`
- L213 _public typedef_ `typedef FD3D12GeometryShader TConcreteType;`
- L218 _public typedef_ `typedef FD3D12PixelShader TConcreteType;`
- L223 _public typedef_ `typedef FD3D12ComputeShader TConcreteType;`
- L228 _public typedef_ `typedef FD3D12WorkGraphShader TConcreteType;`
- L233 _public typedef_ `typedef FD3D12VertexDeclaration TConcreteType;`

#### struct `TD3D12ResourceTraits`  
`template<> struct TD3D12ResourceTraits<FRHIGeometryShader>`  
_L211-214_
- L198 _public typedef_ `typedef FD3D12VertexShader TConcreteType;`
- L203 _public typedef_ `typedef FD3D12MeshShader TConcreteType;`
- L208 _public typedef_ `typedef FD3D12AmplificationShader TConcreteType;`
- L213 _public typedef_ `typedef FD3D12GeometryShader TConcreteType;`
- L218 _public typedef_ `typedef FD3D12PixelShader TConcreteType;`
- L223 _public typedef_ `typedef FD3D12ComputeShader TConcreteType;`
- L228 _public typedef_ `typedef FD3D12WorkGraphShader TConcreteType;`
- L233 _public typedef_ `typedef FD3D12VertexDeclaration TConcreteType;`

#### struct `TD3D12ResourceTraits`  
`template<> struct TD3D12ResourceTraits<FRHIPixelShader>`  
_L216-219_
- L198 _public typedef_ `typedef FD3D12VertexShader TConcreteType;`
- L203 _public typedef_ `typedef FD3D12MeshShader TConcreteType;`
- L208 _public typedef_ `typedef FD3D12AmplificationShader TConcreteType;`
- L213 _public typedef_ `typedef FD3D12GeometryShader TConcreteType;`
- L218 _public typedef_ `typedef FD3D12PixelShader TConcreteType;`
- L223 _public typedef_ `typedef FD3D12ComputeShader TConcreteType;`
- L228 _public typedef_ `typedef FD3D12WorkGraphShader TConcreteType;`
- L233 _public typedef_ `typedef FD3D12VertexDeclaration TConcreteType;`

#### struct `TD3D12ResourceTraits`  
`template<> struct TD3D12ResourceTraits<FRHIComputeShader>`  
_L221-224_
- L198 _public typedef_ `typedef FD3D12VertexShader TConcreteType;`
- L203 _public typedef_ `typedef FD3D12MeshShader TConcreteType;`
- L208 _public typedef_ `typedef FD3D12AmplificationShader TConcreteType;`
- L213 _public typedef_ `typedef FD3D12GeometryShader TConcreteType;`
- L218 _public typedef_ `typedef FD3D12PixelShader TConcreteType;`
- L223 _public typedef_ `typedef FD3D12ComputeShader TConcreteType;`
- L228 _public typedef_ `typedef FD3D12WorkGraphShader TConcreteType;`
- L233 _public typedef_ `typedef FD3D12VertexDeclaration TConcreteType;`

#### struct `TD3D12ResourceTraits`  
`template<> struct TD3D12ResourceTraits<FRHIWorkGraphShader>`  
_L226-229_
- L198 _public typedef_ `typedef FD3D12VertexShader TConcreteType;`
- L203 _public typedef_ `typedef FD3D12MeshShader TConcreteType;`
- L208 _public typedef_ `typedef FD3D12AmplificationShader TConcreteType;`
- L213 _public typedef_ `typedef FD3D12GeometryShader TConcreteType;`
- L218 _public typedef_ `typedef FD3D12PixelShader TConcreteType;`
- L223 _public typedef_ `typedef FD3D12ComputeShader TConcreteType;`
- L228 _public typedef_ `typedef FD3D12WorkGraphShader TConcreteType;`
- L233 _public typedef_ `typedef FD3D12VertexDeclaration TConcreteType;`

#### struct `TD3D12ResourceTraits`  
`template<> struct TD3D12ResourceTraits<FRHIVertexDeclaration>`  
_L231-234_
- L198 _public typedef_ `typedef FD3D12VertexShader TConcreteType;`
- L203 _public typedef_ `typedef FD3D12MeshShader TConcreteType;`
- L208 _public typedef_ `typedef FD3D12AmplificationShader TConcreteType;`
- L213 _public typedef_ `typedef FD3D12GeometryShader TConcreteType;`
- L218 _public typedef_ `typedef FD3D12PixelShader TConcreteType;`
- L223 _public typedef_ `typedef FD3D12ComputeShader TConcreteType;`
- L228 _public typedef_ `typedef FD3D12WorkGraphShader TConcreteType;`
- L233 _public typedef_ `typedef FD3D12VertexDeclaration TConcreteType;`

#### Free symbols / members of external scopes

- L19 _enumerator_ `enum { IsBytewiseComparable = true };` (scope `TTypeTraits::__anonff453a8e0103`)
- L23 _typedef_ `typedef TArray<D3D12_INPUT_ELEMENT_DESC, TFixedAllocator<MaxVertexElementCount> > FD3D12VertexElements;` — Convenience typedef: preallocated array of D3D12 input element descriptions.
- L128 _enumerator_ `enum { StaticFrequency = SF_Vertex };` (scope `FD3D12VertexShader::__anonff453a8e0203`)
- L134 _enumerator_ `enum { StaticFrequency = SF_Mesh };` (scope `FD3D12MeshShader::__anonff453a8e0303`)
- L140 _enumerator_ `enum { StaticFrequency = SF_Amplification };` (scope `FD3D12AmplificationShader::__anonff453a8e0403`)
- L146 _enumerator_ `enum { StaticFrequency = SF_Geometry };` (scope `FD3D12GeometryShader::__anonff453a8e0503`)
- L152 _enumerator_ `enum { StaticFrequency = SF_Pixel }; #if D3D12_RHI_WORKGRAPHS_GRAPHICS FString EntryPoint; #endif` (scope `FD3D12PixelShader::__anonff453a8e0603`)
- L162 _enumerator_ `enum { StaticFrequency = SF_Compute }; const FD3D12RootSignature* RootSignature = nullptr;` (scope `FD3D12ComputeShader::__anonff453a8e0703`)

### `Source/Runtime/D3D12RHI/Private/D3D12State.h` (Private)


#### class `FD3D12SamplerState`  
`class FD3D12SamplerState : public FRHISamplerState, public FD3D12DeviceChild, public FD3D12LinkedAdapterObject<FD3D12SamplerState>`  
_L12-26_
- inherits: `FRHISamplerState,FD3D12DeviceChild,FD3D12LinkedAdapterObject<FD3D12SamplerState>`
- L15 _public member_ `FD3D12OfflineDescriptor OfflineDescriptor;`
- L16 _public member_ `FRHIDescriptorHandle BindlessHandle;`
- L17 _public member_ `const uint16 ID;`
- L19 _public prototype_ `FD3D12SamplerState() = delete;`
- L20 _public prototype_ `FD3D12SamplerState(FD3D12Device* InParent, const D3D12_SAMPLER_DESC& Desc, uint16 SamplerID, FD3D12SamplerState* FirstLinkedObject);`
- L21 _public prototype_ `~FD3D12SamplerState();`
- L23 _public prototype_ `void FreeDescriptor();`
- L25 _public function_ `virtual FRHIDescriptorHandle GetBindlessHandle() const final`

#### class `FD3D12RasterizerState`  
`class FD3D12RasterizerState : public FRHIRasterizerState`  
_L28-34_
- inherits: `FRHIRasterizerState`
- L31 _public member_ `D3D12_RASTERIZER_DESC Desc;`
- L33 _public prototype_ `virtual bool GetInitializer(struct FRasterizerStateInitializerRHI& Init) final override;`

#### class `FD3D12DepthStencilState`  
`class FD3D12DepthStencilState : public FRHIDepthStencilState`  
_L36-46_
- inherits: `FRHIDepthStencilState`
- L40 _public member_ `D3D12_DEPTH_STENCIL_DESC1 Desc;`
- L43 _public member_ `FExclusiveDepthStencil AccessType;` — Describes the read/write state of the separate depth and stencil components of the DSV.
- L45 _public prototype_ `virtual bool GetInitializer(struct FDepthStencilStateInitializerRHI& Init) final override;`

#### class `FD3D12BlendState`  
`class FD3D12BlendState : public FRHIBlendState`  
_L48-55_
- inherits: `FRHIBlendState`
- L52 _public member_ `D3D12_BLEND_DESC Desc;`
- L54 _public prototype_ `virtual bool GetInitializer(class FBlendStateInitializerRHI& Init) final override;`

### `Source/Runtime/D3D12RHI/Private/D3D12StateCachePrivate.h` (Private)


#### enum `ED3D12PipelineType`  
`enum class ED3D12PipelineType : uint8`  
_L58-63_
- L60 _public enumerator_ `Graphics`
- L61 _public enumerator_ `Compute`
- L62 _public enumerator_ `RayTracing`

#### struct `FD3D12VertexBufferCache`  
`struct FD3D12VertexBufferCache`  
_L77-98_
- L79 _public function_ `FD3D12VertexBufferCache()`
- L84 _public function_ `inline void Clear()`
- L93 _public member_ `D3D12_VERTEX_BUFFER_VIEW CurrentVertexBufferViews[MAX_VBS];`
- L94 _public member_ `FD3D12ResourceLocation* CurrentVertexBufferResources[MAX_VBS];`
- L95 _public member_ `FD3D12Resource* Resources[MAX_VBS];`
- L96 _public member_ `int32 MaxBoundVertexBufferIndex;`
- L97 _public member_ `VBSlotMask BoundVBMask;`

#### struct `FD3D12IndexBufferCache`  
`struct FD3D12IndexBufferCache`  
_L100-113_
- L102 _public function_ `FD3D12IndexBufferCache()`
- L107 _public function_ `inline void Clear()`
- L112 _public member_ `D3D12_INDEX_BUFFER_VIEW CurrentIndexBufferView;`

#### struct `FD3D12ResourceCache`  
`template<typename ResourceSlotMask> struct FD3D12ResourceCache`  
_L116-169_
- L118 _public function_ `static inline void CleanSlot(ResourceSlotMask& SlotMask, uint32 SlotIndex)`
- L123 _public function_ `static inline void CleanSlots(ResourceSlotMask& SlotMask, uint32 NumSlots)`
- L128 _public function_ `static inline void DirtySlot(ResourceSlotMask& SlotMask, uint32 SlotIndex)`
- L133 _public function_ `static inline bool IsSlotDirty(const ResourceSlotMask& SlotMask, uint32 SlotIndex)`
- L139 _public function_ `inline void Dirty(EShaderFrequency ShaderFrequency, const ResourceSlotMask& SlotMask = -1)` — Mark a specific shader stage as dirty.
- L146 _public function_ `inline void DirtyGraphics(const ResourceSlotMask& SlotMask = -1)` — Mark specified bind slots, on all graphics stages, as dirty.
- L156 _public function_ `inline void DirtyCompute(const ResourceSlotMask& SlotMask = -1)` — Mark specified bind slots on compute as dirty.
- L162 _public function_ `inline void DirtyAll(const ResourceSlotMask& SlotMask = -1)` — Mark specified bind slots on graphics and compute as dirty.
- L168 _public member_ `ResourceSlotMask DirtySlotMask[SF_NumStandardFrequencies];`

#### struct `FD3D12ConstantBufferCache`  
`struct FD3D12ConstantBufferCache : public FD3D12ResourceCache<CBVSlotMask>`  
_L171-194_
- inherits: `FD3D12ResourceCache<CBVSlotMask>`
- L173 _public function_ `FD3D12ConstantBufferCache()`
- L178 _public function_ `inline void Clear()`
- L190 _public member_ `D3D12_CPU_DESCRIPTOR_HANDLE CBHandles[SF_NumStandardFrequencies][MAX_CBS];`
- L192 _public member_ `D3D12_GPU_VIRTUAL_ADDRESS CurrentGPUVirtualAddress[SF_NumStandardFrequencies][MAX_CBS];`
- L193 _public member_ `FD3D12Resource* Resources[SF_NumStandardFrequencies][MAX_CBS];`

#### struct `FD3D12ShaderResourceViewCache`  
`struct FD3D12ShaderResourceViewCache : public FD3D12ResourceCache<SRVSlotMask>`  
_L196-229_
- inherits: `FD3D12ResourceCache<SRVSlotMask>`
- L198 _public function_ `FD3D12ShaderResourceViewCache()`
- L203 _public function_ `inline void Clear()`
- L224 _public member_ `FD3D12ShaderResourceView* Views[SF_NumStandardFrequencies][MAX_SRVS];`
- L225 _public member_ `FD3D12Resource* Resources[SF_NumStandardFrequencies][MAX_SRVS];`
- L227 _public member_ `SRVSlotMask BoundMask[SF_NumStandardFrequencies];`
- L228 _public member_ `int32 MaxBoundIndex[SF_NumStandardFrequencies];`

#### struct `FD3D12UnorderedAccessViewCache`  
`struct FD3D12UnorderedAccessViewCache : public FD3D12ResourceCache<UAVSlotMask>`  
_L231-254_
- inherits: `FD3D12ResourceCache<UAVSlotMask>`
- L233 _public function_ `FD3D12UnorderedAccessViewCache()`
- L238 _public function_ `inline void Clear()`
- L251 _public member_ `FD3D12UnorderedAccessView* Views[SF_NumStandardFrequencies][MAX_UAVS];`
- L252 _public member_ `FD3D12Resource* Resources[SF_NumStandardFrequencies][MAX_UAVS];`
- L253 _public member_ `uint32 StartSlot[SF_NumStandardFrequencies];`

#### struct `FD3D12SamplerStateCache`  
`struct FD3D12SamplerStateCache : public FD3D12ResourceCache<SamplerSlotMask>`  
_L256-271_
- inherits: `FD3D12ResourceCache<SamplerSlotMask>`
- L258 _public function_ `FD3D12SamplerStateCache()`
- L263 _public function_ `inline void Clear()`
- L270 _public member_ `FD3D12SamplerState* States[SF_NumStandardFrequencies][MAX_SAMPLERS];`

#### class `FD3D12StateCache`  
`class FD3D12StateCache final : public FD3D12DeviceChild, public FD3D12SingleNodeGPUObject`  
_L299-796_
- inherits: `FD3D12DeviceChild,FD3D12SingleNodeGPUObject`
- L304 _protected member_ `FD3D12CommandContext& CmdContext;`
- L306 _protected member_ `bool bNeedSetVB = true;`
- L307 _protected member_ `bool bNeedSetRTs = true;`
- L308 _protected member_ `bool bNeedSetViewports = true;`
- L309 _protected member_ `bool bNeedSetScissorRects = true;`
- L310 _protected member_ `bool bNeedSetPrimitiveTopology = true;`
- L311 _protected member_ `bool bNeedSetBlendFactor = true;`
- L312 _protected member_ `bool bNeedSetStencilRef = true;`
- L313 _protected member_ `bool bNeedSetDepthBounds = true;`
- L314 _protected member_ `bool bNeedSetShadingRate = true;`
- L315 _protected member_ `bool bNeedSetShadingRateImage = true;`
- L317 _protected member_ `bool bSRVSCleared = true;`
- L319 _protected member_ `D3D12_RESOURCE_BINDING_TIER ResourceBindingTier;`
- L425 _protected member_ `} PipelineState = {};`
- L427 _protected member_ `FD3D12DescriptorCache DescriptorCache;`
- L429 _protected prototype_ `void InternalSetIndexBuffer(FD3D12Resource* Resource);`
- L430 _protected prototype_ `void InternalSetStreamSource(FD3D12ResourceLocation* VertexBufferLocation, uint32 StreamIndex, uint32 Stride, uint32 Offset);`
- L432 _protected prototype_ `bool InternalSetDescriptorHeaps(bool bBindless);`
- L433 _protected prototype_ `bool InternalSetRootSignature(ED3D12PipelineType InPipelineType, const FD3D12RootSignature* InRootSignature, bool bForce);`
- L434 _protected prototype_ `void InternalSetPipelineState(FD3D12PipelineState* InPipelineState);`
- L443 _private function_ `template <typename ContextType> static void SetDirtyUniformBuffers(ContextType& Context, EShaderFrequency Frequency)`
- L450 _public function_ `FD3D12DescriptorCache* GetDescriptorCache()`
- L455 _public function_ `FD3D12GraphicsPipelineState* GetGraphicsPipelineState() const`
- L460 _public function_ `FD3D12ComputePipelineState* GetComputePipelineState() const`
- L465 _public function_ `EPrimitiveType GetGraphicsPipelinePrimitiveType() const`
- L470 _public function_ `uint32 GetVertexCount(uint32 NumPrimitives)`
- L475 _public prototype_ `void ClearSRVs();`
- L477 _public prototype_ `void ClearResourceViewCaches(EShaderFrequency ShaderFrequency, FD3D12ResourceLocation*& ResourceLocation, EShaderParameterTypeMask ShaderParameterTypeMask);`
- L479 _public prototype_ `void SetShaderResourceView(EShaderFrequency ShaderFrequency, FD3D12ShaderResourceView* SRV, uint32 ResourceIndex);`
- L481 _public prototype_ `void SetScissorRects(uint32 Count, const D3D12_RECT* const ScissorRects);`
- L482 _public prototype_ `void SetScissorRect(const D3D12_RECT& ScissorRect);`
- L484 _public function_ `D3D12_STATE_CACHE_INLINE const D3D12_RECT& GetScissorRect(int32 Index = 0) const`
- L489 _public prototype_ `void SetViewport(const D3D12_VIEWPORT& Viewport);`
- L490 _public prototype_ `void SetViewports(uint32 Count, const D3D12_VIEWPORT* const Viewports);`
- L492 _public function_ `D3D12_STATE_CACHE_INLINE uint32 GetNumViewports() const`
- L497 _public function_ `D3D12_STATE_CACHE_INLINE const D3D12_VIEWPORT& GetViewport(int32 Index = 0) const`
- L502 _public function_ `D3D12_STATE_CACHE_INLINE void GetViewports(uint32* Count, D3D12_VIEWPORT* Viewports) const`
- L523 _public function_ `D3D12_STATE_CACHE_INLINE void SetSamplerState(EShaderFrequency ShaderFrequency, FD3D12SamplerState* SamplerState, uint32 SamplerIndex)`
- L534 _public function_ `D3D12_STATE_CACHE_INLINE void SetConstantsFromUniformBuffer(EShaderFrequency ShaderFrequency, uint32 SlotIndex, FD3D12UniformBuffer* UniformBuffer)`
- L572 _public function_ `D3D12_STATE_CACHE_INLINE void SetConstantBuffer(EShaderFrequency ShaderFrequency, FD3D12ConstantBuffer& Buffer, bool bDiscardSharedConstants)`
- L594 _public prototype_ `void SetBlendFactor(const float BlendFactor[4]);`
- L595 _public prototype_ `void SetStencilRef(uint32 StencilRef);`
- L597 _public function_ `FRHIShader* GetShader(EShaderFrequency InFrequency)`
- L611 _public prototype_ `void SetNewShaderData(EShaderFrequency InFrequency, const FD3D12ShaderData* InShaderData);`
- L612 _public prototype_ `void SetGraphicsPipelineState(FD3D12GraphicsPipelineState* GraphicsPipelineState);`
- L613 _public prototype_ `void SetComputePipelineState(FD3D12ComputePipelineState* ComputePipelineState);`
- L615 _public function_ `D3D12_STATE_CACHE_INLINE void SetStreamSource(FD3D12ResourceLocation* VertexBufferLocation, uint32 StreamIndex, uint32 Stride, uint32 Offset)`
- L621 _public function_ `D3D12_STATE_CACHE_INLINE void SetStreamSource(FD3D12ResourceLocation* VertexBufferLocation, uint32 StreamIndex, uint32 Offset)`
- L626 _public function_ `D3D12_STATE_CACHE_INLINE void ClearVertexBuffer(const FD3D12ResourceLocation* VertexBufferLocation)`
- L637 _public function_ `D3D12_STATE_CACHE_INLINE void ClearVertexBuffers()`
- L645 _public function_ `D3D12_STATE_CACHE_INLINE void SetIndexBuffer(const FD3D12ResourceLocation& IndexBufferLocation, DXGI_FORMAT Format, uint32 Offset)`
- L665 _public prototype_ `FD3D12StateCache(FD3D12CommandContext& CmdContext, FRHIGPUMask Node);`
- L666 _public prototype_ `~FD3D12StateCache() = default;`
- L670 _public function_ `void TransitionComputeState(ED3D12PipelineType PipelineType)` — When transitioning between RayGen and Compute, it is necessary to clear the state cache
- L682 _public member_ `ED3D12PipelineType LastComputePipelineType = ED3D12PipelineType::Compute;`
- L685 _public prototype_ `void ApplyState(ERHIPipeline HardwarePipe, ED3D12PipelineType PipelineType);`
- L686 _public prototype_ `void ApplySamplerTables(const FD3D12RootSignature* pRootSignature, uint32 StartStage, uint32 EndStage);`
- L687 _public prototype_ `void ApplyResourceTables(const FD3D12RootSignature* pRootSignature, uint32 StartStage, uint32 EndStage);`
- L688 _public prototype_ `void ApplyBindlessResources(const FD3D12RootSignature* pRootSignature, uint32 StartStage, uint32 EndStage);`
- L689 _public prototype_ `void ApplyConstants(const FD3D12RootSignature* pRootSignature, uint32 StartStage, uint32 EndStage);`
- L690 _public prototype_ `void DirtyStateForNewCommandList();`
- L691 _public prototype_ `void DirtyState();`
- L692 _public prototype_ `void DirtyViewDescriptorTables();`
- L693 _public prototype_ `void DirtySamplerDescriptorTables();`
- L694 _public prototype_ `bool AssertResourceStates(ED3D12PipelineType PipelineType);`
- L696 _public prototype_ `void SetRenderTargets(uint32 NumSimultaneousRenderTargets, FD3D12RenderTargetView** RTArray, FD3D12DepthStencilView* DSTarget);`
- L697 _public function_ `D3D12_STATE_CACHE_INLINE void GetRenderTargets(FD3D12RenderTargetView **RTArray, uint32* NumSimultaneousRTs, FD3D12DepthStencilView** DepthStencilTarget)`
- L712 _public prototype_ `void SetRootConstants(const FUint32Vector4& Constants);`
- L714 _public prototype_ `void SetUAV(EShaderFrequency ShaderStage, uint32 SlotIndex, FD3D12UnorderedAccessView* UAV);`
- L716 _public prototype_ `void ClearUAVs(EShaderFrequency ShaderStage);`
- L718 _public function_ `void SetDepthBounds(float MinDepth, float MaxDepth)`
- L729 _public function_ `void SetShadingRate(EVRSShadingRate ShadingRate, EVRSRateCombiner PerPrimitiveCombiner, EVRSRateCombiner ScreenSpaceCombiner)`
- L742 _public function_ `void SetShadingRateImage(FD3D12Resource* ShadingRateImage)`
- L751 _public function_ `void SetComputeBudget(EAsyncComputeBudget ComputeBudget)`
- L756 _public prototype_ `void FlushComputeShaderCache(bool bForce = false);`
- L763 _public prototype_ `void ClearState();` — Clears all D3D12 State, setting all input/output resource slots, shaders, input layouts, predications, scissor rectangles, depth-stencil state, rasterizer state, blend state, sampler state, and viewports to NULL
- L765 _public function_ `void ForceSetComputeRootSignature()`
- L766 _public function_ `void ForceSetGraphicsRootSignature()`
- L769 _public prototype_ `void SetNewBindlessResourcesHeap(FD3D12DescriptorHeap* InHeap);`
- L770 _public prototype_ `void SetNewBindlessSamplerHeap(FD3D12DescriptorHeap* InHeap);`
- L772 _public function_ `void BindlessHeapsInvalidated()`
- L779 _public function_ `void QueueBindlessSRV(EShaderFrequency ShaderFrequency, FD3D12ShaderResourceView* SRV)`
- L783 _public function_ `void QueueBindlessSRVs(EShaderFrequency ShaderFrequency, TConstArrayView<FD3D12ShaderResourceView*> SRVs)`
- L787 _public function_ `void QueueBindlessUAV(EShaderFrequency ShaderFrequency, FD3D12UnorderedAccessView* UAV)`
- L791 _public function_ `void QueueBindlessUAVs(EShaderFrequency ShaderFrequency, TConstArrayView<FD3D12UnorderedAccessView*> UAVs)`

#### struct `FD3D12StateCache::(anonymous)`  
``  
_L322-425_

#### struct `FD3D12StateCache::__anon0a1379c70108::FGraphicsState`  
`struct FGraphicsState`  
_L323-386_
- L326 _public member_ `TRefCountPtr<FD3D12GraphicsPipelineState> CurrentPipelineStateObject = nullptr;` — Cache
- L329 _public member_ `bool bNeedSetRootSignature;` — Note: Current root signature is part of the bound shader state, which is part of the PSO
- L332 _public member_ `uint32 CurrentReferenceStencil = D3D12_DEFAULT_STENCIL_REFERENCE;` — Depth Stencil State Cache
- L335 _public member_ `float CurrentBlendFactor[4] = { D3D12_DEFAULT_BLEND_FACTOR_RED, D3D12_DEFAULT_BLEND_FACTOR_GREEN, D3D12_DEFAULT_BLEND_FACTOR_BLUE, D3D12_DEFAULT_BLEND_FACTOR_ALPHA };` — Blend State Cache
- L344 _public member_ `uint32 CurrentNumberOfViewports = 0;` — Viewport
- L345 _public member_ `D3D12_VIEWPORT CurrentViewport[D3D12_VIEWPORT_AND_SCISSORRECT_OBJECT_COUNT_PER_PIPELINE] = {};`
- L348 _public member_ `FD3D12VertexBufferCache VBCache = {};` — Vertex Buffer State
- L351 _public member_ `FD3D12IndexBufferCache IBCache = {};` — Index Buffer State
- L354 _public member_ `EPrimitiveType CurrentPrimitiveType = PT_Num;` — Primitive Topology State
- L355 _public member_ `D3D_PRIMITIVE_TOPOLOGY CurrentPrimitiveTopology = D3D_PRIMITIVE_TOPOLOGY_UNDEFINED;`
- L356 _public member_ `uint32 PrimitiveTypeFactor;`
- L357 _public member_ `uint32 PrimitiveTypeOffset;`
- L360 _public member_ `D3D12_RECT CurrentScissorRects[D3D12_VIEWPORT_AND_SCISSORRECT_OBJECT_COUNT_PER_PIPELINE] = {};` — Input Layout State
- L361 _public member_ `uint32 CurrentNumberOfScissorRects = 0;`
- L363 _public member_ `TStaticArray<uint16, MaxVertexElementCount> StreamStrides;`
- L365 _public member_ `FD3D12RenderTargetView* RenderTargetArray[D3D12_SIMULTANEOUS_RENDER_TARGET_COUNT] = {};`
- L366 _public member_ `uint32 CurrentNumberOfRenderTargets = 0;`
- L368 _public member_ `FD3D12DepthStencilView* CurrentDepthStencilTarget = nullptr;`
- L370 _public member_ `float MinDepth = 0.0f;`
- L371 _public member_ `float MaxDepth = 1.0f;`
- L373 _public member_ `EVRSShadingRate DrawShadingRate = EVRSShadingRate::VRSSR_1x1;`
- L375 _public member_ `TStaticArray<EVRSRateCombiner, ED3D12VRSCombinerStages::Num> Combiners;`
- L377 _public member_ `FD3D12Resource* ShadingRateImage = nullptr;`
- L379 _public function_ `FGraphicsState()`

#### struct `FD3D12StateCache::__anon0a1379c70108::(anonymous)`  
``  
_L389-398_

#### struct `FD3D12StateCache::__anon0a1379c70108::(anonymous)`  
``  
_L401-424_

#### Free symbols / members of external scopes

- L32 _macro_ `#define D3D12_STATE_CACHE_RUNTIME_TOGGLE 0` — If set, includes a runtime toggle console command for debugging D3D12  state caching. ("TOGGLESTATECACHE")
- L38 _macro_ `#define NUM_SAMPLER_DESCRIPTORS D3D12_MAX_SHADER_VISIBLE_SAMPLER_HEAP_SIZE` — The number of view descriptors available per (online) descriptor heap, depending on hardware tier
- L41 _macro_ `#define D3D12_STATE_CACHE_INLINE FORCEINLINE_DEBUGGABLE` — Keep set state functions inline to reduce call overhead
- L44 _externvar_ `extern bool GD3D12SkipStateCaching;`
- L46 _variable_ `static const bool GD3D12SkipStateCaching = false;`
- L49 _externvar_ `extern int32 GGlobalResourceDescriptorHeapSize;`
- L50 _externvar_ `extern int32 GGlobalSamplerDescriptorHeapSize;`
- L52 _externvar_ `extern int32 GGlobalSamplerHeapSize;`
- L53 _externvar_ `extern int32 GOnlineDescriptorHeapSize;`
- L54 _externvar_ `extern int32 GOnlineDescriptorHeapBlockSize;`
- L55 _externvar_ `extern int32 GBindlessOnlineDescriptorHeapSize;`
- L56 _externvar_ `extern int32 GBindlessOnlineDescriptorHeapBlockSize;`
- L65 _namespace_ `namespace ED3D12VRSCombinerStages`
- L67 _variable_ `constexpr int32 PerPrimitive = 0;` (scope `ED3D12VRSCombinerStages`)
- L68 _variable_ `constexpr int32 ScreenSpace = PerPrimitive + 1;` (scope `ED3D12VRSCombinerStages`)
- L69 _variable_ `constexpr int32 Num = ScreenSpace + 1;` (scope `ED3D12VRSCombinerStages`)
- L72 _macro_ `#define MAX_VBS D3D12_IA_VERTEX_INPUT_RESOURCE_SLOT_COUNT`
- L74 _typedef_ `typedef uint32 VBSlotMask;`
- L274 _function_ `static inline D3D_PRIMITIVE_TOPOLOGY GetD3D12PrimitiveType(uint32 PrimitiveType)`
- L386 _member_ `} Graphics = {};` (scope `FD3D12StateCache::__anon0a1379c70108`)
- L391 _member_ `TRefCountPtr<FD3D12ComputePipelineState> CurrentPipelineStateObject = nullptr;` (scope `FD3D12StateCache::__anon0a1379c70108::__anon0a1379c70208`) — Cache
- L394 _member_ `bool bNeedSetRootSignature;` (scope `FD3D12StateCache::__anon0a1379c70108::__anon0a1379c70208`) — Note: Current root signature is part of the bound compute shader, which is part of the PSO
- L397 _member_ `EAsyncComputeBudget ComputeBudget = EAsyncComputeBudget::EAll_4;` (scope `FD3D12StateCache::__anon0a1379c70108::__anon0a1379c70208`) — Need to cache compute budget, as we need to reset if after PSO changes
- L398 _member_ `} Compute = {};` (scope `FD3D12StateCache::__anon0a1379c70108`)
- L402 _member_ `FD3D12ShaderResourceViewCache SRVCache = {};` (scope `FD3D12StateCache::__anon0a1379c70108::__anon0a1379c70308`)
- L403 _member_ `FD3D12ConstantBufferCache CBVCache = {};` (scope `FD3D12StateCache::__anon0a1379c70108::__anon0a1379c70308`)
- L404 _member_ `FD3D12UnorderedAccessViewCache UAVCache = {};` (scope `FD3D12StateCache::__anon0a1379c70108::__anon0a1379c70308`)
- L405 _member_ `FD3D12SamplerStateCache SamplerCache = {};` (scope `FD3D12StateCache::__anon0a1379c70108::__anon0a1379c70308`)
- L408 _member_ `ID3D12PipelineState* CurrentPipelineStateObject = nullptr;` (scope `FD3D12StateCache::__anon0a1379c70108::__anon0a1379c70308`) — PSO
- L409 _member_ `bool bNeedSetPSO;` (scope `FD3D12StateCache::__anon0a1379c70108::__anon0a1379c70308`)
- L412 _member_ `bool bNeedSetRootConstants;` (scope `FD3D12StateCache::__anon0a1379c70108::__anon0a1379c70308`) — Root Constants
- L413 _member_ `FUint32Vector4 ShaderRootConstants = FUint32Vector4(0, 0, 0, 0);` (scope `FD3D12StateCache::__anon0a1379c70108::__anon0a1379c70308`)
- L415 _member_ `uint32 CurrentShaderSamplerCounts[SF_NumStandardFrequencies] = {};` (scope `FD3D12StateCache::__anon0a1379c70108::__anon0a1379c70308`)
- L416 _member_ `uint32 CurrentShaderSRVCounts [SF_NumStandardFrequencies] = {};` (scope `FD3D12StateCache::__anon0a1379c70108::__anon0a1379c70308`)
- L417 _member_ `uint32 CurrentShaderCBCounts [SF_NumStandardFrequencies] = {};` (scope `FD3D12StateCache::__anon0a1379c70108::__anon0a1379c70308`)
- L418 _member_ `uint32 CurrentShaderUAVCounts [SF_NumStandardFrequencies] = {};` (scope `FD3D12StateCache::__anon0a1379c70108::__anon0a1379c70308`)
- L421 _member_ `TArray<FD3D12ShaderResourceView*> QueuedBindlessSRVs[SF_NumStandardFrequencies];` (scope `FD3D12StateCache::__anon0a1379c70108::__anon0a1379c70308`)
- L422 _member_ `TArray<FD3D12UnorderedAccessView*> QueuedBindlessUAVs[SF_NumStandardFrequencies];` (scope `FD3D12StateCache::__anon0a1379c70108::__anon0a1379c70308`)
- L424 _member_ `} Common = {};` (scope `FD3D12StateCache::__anon0a1379c70108`)

### `Source/Runtime/D3D12RHI/Private/D3D12Stats.h` (Private)


#### struct `FD3D12GlobalStats`  
`struct FD3D12GlobalStats`  
_L169-182_
- L172 _public member_ `static int64 GDedicatedVideoMemory;` — in bytes, never change after RHI, needed to scale game features
- L175 _public member_ `static int64 GDedicatedSystemMemory;` — in bytes, never change after RHI, needed to scale game features
- L178 _public member_ `static int64 GSharedSystemMemory;` — in bytes, never change after RHI, needed to scale game features
- L181 _public member_ `static int64 GTotalGraphicsMemory;` — In bytes. Never changed after RHI init. Our estimate of the amount of memory that we can use for graphics resources in total.

#### Free symbols / members of external scopes

- L11 _delegate_ `DECLARE_STATS_GROUP(TEXT("D3D12RHI"), STATGROUP_D3D12RHI, STATCAT_Ad`
- L12 _delegate_ `DECLARE_STATS_GROUP(TEXT("D3D12RHI: Memory"), STATGROUP_D3D12Memory, ST`
- L13 _delegate_ `DECLARE_STATS_GROUP(TEXT("D3D12RHI: Memory Details"), STATGROUP_D3D12MemoryDet`
- L14 _delegate_ `DECLARE_STATS_GROUP(TEXT("D3D12RHI: Resources"), STATGROUP_D3D12Resources,`
- L15 _delegate_ `DECLARE_STATS_GROUP(TEXT("D3D12RHI: Bindless"), STATGROUP_D3D12Bindless,`
- L16 _delegate_ `DECLARE_STATS_GROUP(TEXT("D3D12RHI: Buffer Details"), STATGROUP_D3D12BufferDet`
- L17 _delegate_ `DECLARE_STATS_GROUP(TEXT("D3D12RHI: Pipeline State (PSO)"), STATGROUP_D3D12Pip`
- L18 _delegate_ `DECLARE_STATS_GROUP(TEXT("D3D12RHI: Descriptor Heap (GPU Visible)"), STATGROUP_`
- L20 _delegate_ `DECLARE_CYCLE_STAT_EXTERN(TEXT("Present time"), STAT_D3D12PresentTime, STATGROUP_`
- L21 _delegate_ `DECLARE_CYCLE_STAT_EXTERN(TEXT("CustomPresent time"), STAT_D3D12CustomPresentTime, STAT`
- L23 _delegate_ `DECLARE_DWORD_ACCUMULATOR_STAT_EXTERN(TEXT("Num command allocators (3D, Compute, Copy)"), STAT_D3D12Nu`
- L24 _delegate_ `DECLARE_DWORD_ACCUMULATOR_STAT_EXTERN(TEXT("Num command lists (3D, Compute, Copy)"), STAT_D3D12Nu`
- L25 _delegate_ `DECLARE_DWORD_ACCUMULATOR_STAT_EXTERN(TEXT("Num Query Heaps"), STAT_D3D12NumQueryHeaps, STATGRO`
- L26 _delegate_ `DECLARE_DWORD_ACCUMULATOR_STAT_EXTERN(TEXT("Num pipeline state objects (PSOs)"), STAT_D3D`
- L28 _delegate_ `DECLARE_DWORD_COUNTER_STAT_EXTERN(TEXT("Executed Command Lists"), STAT_D3D12ExecutedCommandLists,`
- L29 _delegate_ `DECLARE_DWORD_COUNTER_STAT_EXTERN(TEXT("Executed Command List Batches"), STAT_D3D12ExecutedCommandListBa`
- L31 _delegate_ `DECLARE_DWORD_COUNTER_STAT_EXTERN(TEXT("Textures Allocated"), STAT_D3D12TexturesAllocated, STAT`
- L32 _delegate_ `DECLARE_DWORD_COUNTER_STAT_EXTERN(TEXT("Textures Released"), STAT_D3D12TexturesReleased, STATG`
- L33 _delegate_ `DECLARE_CYCLE_STAT_EXTERN(TEXT("CreateTexture time"), STAT_D3D12CreateTextureTime, STAT`
- L36 _delegate_ `DECLARE_CYCLE_STAT_EXTERN(TEXT("CreateBuffer time"), STAT_D3D12CreateBufferTime, STATG`
- L37 _delegate_ `DECLARE_CYCLE_STAT_EXTERN(TEXT("CopyToStagingBuffer time"), STAT_D3D12CopyToStagingBufferTime`
- L40 _delegate_ `DECLARE_CYCLE_STAT_EXTERN(TEXT("Commit transient resource time"), STAT_D3D12CommitTransientResour`
- L41 _delegate_ `DECLARE_CYCLE_STAT_EXTERN(TEXT("Decommit transient resource time"), STAT_D3D12DecommitTransientReso`
- L43 _delegate_ `DECLARE_DWORD_COUNTER_STAT_EXTERN(TEXT("UAV Barriers"), STAT_D3D12UAVBarriers, STATGROUP_`
- L45 _delegate_ `DECLARE_DWORD_ACCUMULATOR_STAT_EXTERN(TEXT("Resource Heaps Allocated"), STAT_D3D12BindlessResourceHeapsAllocated, STA`
- L46 _delegate_ `DECLARE_DWORD_ACCUMULATOR_STAT_EXTERN(TEXT("Resource Heaps Active"), STAT_D3D12BindlessResourceHeapsActive, STATGR`
- L47 _delegate_ `DECLARE_DWORD_ACCUMULATOR_STAT_EXTERN(TEXT("Resource Heaps in use by GPU"), STAT_D3D12BindlessResourceHeapsInUseByGPU,`
- L48 _delegate_ `DECLARE_DWORD_COUNTER_STAT_EXTERN(TEXT("Resource Heaps Versioned"), STAT_D3D12BindlessResourceHeapsVersioned, STA`
- L49 _delegate_ `DECLARE_DWORD_COUNTER_STAT_EXTERN(TEXT("Resource Descriptors Initialized"), STAT_D3D12BindlessResourceDescriptorsInitiali`
- L50 _delegate_ `DECLARE_DWORD_COUNTER_STAT_EXTERN(TEXT("Resource Descriptors Updated"), STAT_D3D12BindlessResourceDescriptorsUpdated,`
- L51 _delegate_ `DECLARE_DWORD_COUNTER_STAT_EXTERN(TEXT("Resource GPU Descriptors Copied"), STAT_D3D12BindlessResourceGPUDescriptorsCopi`
- L52 _delegate_ `DECLARE_MEMORY_STAT_EXTERN(TEXT("Resource Heaps GPU Memory Usage"), STAT_D3D12BindlessResourceHeapGPUMemoryUsa`
- L54 _delegate_ `DECLARE_CYCLE_STAT_EXTERN(TEXT("CreateBoundShaderState time"), STAT_D3D12CreateBoundShaderStateT`
- L55 _delegate_ `DECLARE_CYCLE_STAT_EXTERN(TEXT("New bound shader state time"), STAT_D3D12NewBoundShaderStateT`
- L56 _delegate_ `DECLARE_DWORD_ACCUMULATOR_STAT_EXTERN(TEXT("Num bound shader states"), STAT_D3D12NumBoundShaderState,`
- L57 _delegate_ `DECLARE_CYCLE_STAT_EXTERN(TEXT("Set bound shader state"), STAT_D3D12SetBoundShaderState,`
- L61 _delegate_ `DECLARE_CYCLE_STAT_EXTERN(TEXT("Commit resource tables"), STAT_D3D12CommitResourceTables,`
- L62 _delegate_ `DECLARE_DWORD_COUNTER_STAT_EXTERN(TEXT("Num textures in tables"), STAT_D3D12SetTextureInTableCalls,`
- L64 _delegate_ `DECLARE_CYCLE_STAT_EXTERN(TEXT("Dispatch shader bundle time"), STAT_D3D12DispatchShaderBun`
- L80 _delegate_ `DECLARE_CYCLE_STAT_EXTERN(TEXT("PSO Create time"), STAT_D3D12PSOCreateTime, STATGRO`
- L83 _delegate_ `DECLARE_CYCLE_STAT_EXTERN(TEXT("ExecuteCommandList time"), STAT_D3D12ExecuteCommandListTime,`
- L84 _delegate_ `DECLARE_CYCLE_STAT_EXTERN(TEXT("WaitForFence time"), STAT_D3D12WaitForFenceTime, STATG`
- L86 _delegate_ `DECLARE_CYCLE_STAT_EXTERN(TEXT("Global Constant buffer update time"), STAT_D3D12GlobalConstantBuffer`
- L88 _delegate_ `DECLARE_MEMORY_STAT_EXTERN(TEXT("TOTAL"), STAT_D3D12MemoryCurrentTotal, STATGROUP_D3D12Resource`
- L89 _delegate_ `DECLARE_MEMORY_STAT_EXTERN(TEXT("Render Targets"), STAT_D3D12RenderTargets, STATGROUP_D3D1`
- L90 _delegate_ `DECLARE_MEMORY_STAT_EXTERN(TEXT("UAV Textures"), STAT_D3D12UAVTextures, STATGROUP_D3D12R`
- L91 _delegate_ `DECLARE_MEMORY_STAT_EXTERN(TEXT("Textures"), STAT_D3D12Textures, STATGROUP_D3D12Resou`
- L92 _delegate_ `DECLARE_MEMORY_STAT_EXTERN(TEXT("UAV Buffers"), STAT_D3D12UAVBuffers, STATGROUP_D3D12Re`
- L93 _delegate_ `DECLARE_MEMORY_STAT_EXTERN(TEXT("RayTracing Buffers"), STAT_D3D12RTBuffers, STATGROUP_`
- L94 _delegate_ `DECLARE_MEMORY_STAT_EXTERN(TEXT("Buffers"), STAT_D3D12Buffer, STATGROUP_D3D12Resour`
- L95 _delegate_ `DECLARE_MEMORY_STAT_EXTERN(TEXT("Transient Heaps"), STAT_D3D12TransientHeaps, STATGROUP_D3D`
- L97 _delegate_ `DECLARE_MEMORY_STAT_EXTERN(TEXT("RenderTarget StandAlone Allocated"), STAT_D3D12RenderTargetStandAloneAllocated,`
- L98 _delegate_ `DECLARE_MEMORY_STAT_EXTERN(TEXT("UAVTexture StandAlone Allocated"), STAT_D3D12UAVTextureStandAloneAllocated, S`
- L99 _delegate_ `DECLARE_MEMORY_STAT_EXTERN(TEXT("Texture StandAlone Allocated"), STAT_D3D12TextureStandAloneAllocated, STAT`
- L100 _delegate_ `DECLARE_MEMORY_STAT_EXTERN(TEXT("UAVBuffer StandAlone Allocated"), STAT_D3D12UAVBufferStandAloneAllocated, ST`
- L101 _delegate_ `DECLARE_MEMORY_STAT_EXTERN(TEXT("Buffer StandAlone Allocated"), STAT_D3D12BufferStandAloneAllocated, STATG`
- L103 _delegate_ `DECLARE_DWORD_ACCUMULATOR_STAT_EXTERN(TEXT("RenderTarget StandAlone Allocated"), STAT_D3D12RenderTargetStandAloneCount,`
- L104 _delegate_ `DECLARE_DWORD_ACCUMULATOR_STAT_EXTERN(TEXT("UAVTexture StandAlone Allocated"), STAT_D3D12UAVTextureStandAloneCount, S`
- L105 _delegate_ `DECLARE_DWORD_ACCUMULATOR_STAT_EXTERN(TEXT("Texture StandAlone Allocated"), STAT_D3D12TextureStandAloneCount, STAT`
- L106 _delegate_ `DECLARE_DWORD_ACCUMULATOR_STAT_EXTERN(TEXT("UAVBuffer StandAlone Allocated"), STAT_D3D12UAVBufferStandAloneCount, ST`
- L107 _delegate_ `DECLARE_DWORD_ACCUMULATOR_STAT_EXTERN(TEXT("Buffer StandAlone Allocated"), STAT_D3D12BufferStandAloneCount, STATG`
- L109 _delegate_ `DECLARE_MEMORY_STAT_EXTERN(TEXT("Texture Allocator Allocated"), STAT_D3D12TextureAllocatorAllocated, STATG`
- L110 _delegate_ `DECLARE_MEMORY_STAT_EXTERN(TEXT("Texture Allocator Unused"), STAT_D3D12TextureAllocatorUnused, STATGROU`
- L111 _delegate_ `DECLARE_DWORD_ACCUMULATOR_STAT_EXTERN(TEXT("Texture Allocator Allocated"), STAT_D3D12TextureAllocatorCount, STATG`
- L116 _delegate_ `DECLARE_MEMORY_STAT_EXTERN(TEXT("BufferPool Memory Allocated"), STAT_D3D12BufferPoolMemoryAllocated, STATG`
- L117 _delegate_ `DECLARE_MEMORY_STAT_EXTERN(TEXT("BufferPool Memory Used"), STAT_D3D12BufferPoolMemoryUsed, STATGROUP_`
- L119 _delegate_ `DECLARE_MEMORY_STAT_EXTERN(TEXT("UploadPool Memory Allocated"), STAT_D3D12UploadPoolMemoryAllocated, STATG`
- L120 _delegate_ `DECLARE_MEMORY_STAT_EXTERN(TEXT("UploadPool Memory Used"), STAT_D3D12UploadPoolMemoryUsed, STATGROUP_`
- L122 _delegate_ `DECLARE_MEMORY_STAT_EXTERN(TEXT("BufferPool Memory Free"), STAT_D3D12BufferPoolMemoryFree, STATGROUP_`
- L123 _delegate_ `DECLARE_MEMORY_STAT_EXTERN(TEXT("BufferPool Memory Alignment Waste"), STAT_D3D12BufferPoolAlignmentWaste,`
- L124 _delegate_ `DECLARE_DWORD_ACCUMULATOR_STAT_EXTERN(TEXT("BufferPool Page Count"), STAT_D3D12BufferPoolPageCount, STATGROUP_D`
- L125 _delegate_ `DECLARE_DWORD_ACCUMULATOR_STAT_EXTERN(TEXT("BufferPool Full Pages"), STAT_D3D12BufferPoolFullPages, STATGROUP_D`
- L126 _delegate_ `DECLARE_MEMORY_STAT_EXTERN(TEXT("Bufferool Fragmentation"), STAT_D3D12BufferPoolFragmentation, STATGROUP`
- L127 _delegate_ `DECLARE_FLOAT_ACCUMULATOR_STAT_EXTERN(TEXT("Bufferool Fragmentation Percentage"), STAT_D3D12BufferPoolFragmentationPercentage`
- L129 _delegate_ `DECLARE_MEMORY_STAT_EXTERN(TEXT("UploadPool Memory Free"), STAT_D3D12UploadPoolMemoryFree, STATGROUP_`
- L130 _delegate_ `DECLARE_MEMORY_STAT_EXTERN(TEXT("UploadPool Memory Alignment Waste"), STAT_D3D12UploadPoolAlignmentWaste,`
- L131 _delegate_ `DECLARE_DWORD_ACCUMULATOR_STAT_EXTERN(TEXT("UploadPool Page Count"), STAT_D3D12UploadPoolPageCount, STATGROUP_D`
- L132 _delegate_ `DECLARE_DWORD_ACCUMULATOR_STAT_EXTERN(TEXT("UploadPool Full Pages"), STAT_D3D12UploadPoolFullPages, STATGROUP_D`
- L134 _delegate_ `DECLARE_MEMORY_STAT_EXTERN(TEXT("Reserved Resource Physical Memory"), STAT_D3D12ReservedResourcePhysical,`
- L139 _delegate_ `DECLARE_DWORD_ACCUMULATOR_STAT_EXTERN(TEXT("Unique Samplers"), STAT_UniqueSamplers, STATGROUP_D3D12Des` — Detailed Descriptor heap stats
- L141 _delegate_ `DECLARE_DWORD_COUNTER_STAT_EXTERN(TEXT("View: Heap changed"), STAT_ViewHeapChanged, STATGROUP_D3D12`
- L142 _delegate_ `DECLARE_DWORD_COUNTER_STAT_EXTERN(TEXT("Sampler: Heap changed"), STAT_SamplerHeapChanged, STATGROUP_D3`
- L144 _delegate_ `DECLARE_DWORD_ACCUMULATOR_STAT_EXTERN(TEXT("View: Num descriptor heaps"), STAT_NumViewOnlineDescriptorHeaps, STATGRO`
- L145 _delegate_ `DECLARE_DWORD_ACCUMULATOR_STAT_EXTERN(TEXT("Sampler: Num descriptor heaps"), STAT_NumSamplerOnlineDescriptorHeaps, STAT`
- L146 _delegate_ `DECLARE_DWORD_ACCUMULATOR_STAT_EXTERN(TEXT("Sampler: Num reusable unique descriptor table entries"), STAT_NumReuseableSamplerOnli`
- L147 _delegate_ `DECLARE_DWORD_ACCUMULATOR_STAT_EXTERN(TEXT("Sampler: Num reusable unique descriptors"), STAT_NumReuseableSamplerOnlineDescri`
- L148 _delegate_ `DECLARE_DWORD_COUNTER_STAT_EXTERN(TEXT("View: Num reserved descriptors"), STAT_NumReservedViewOnlineDescriptors, STA`
- L149 _delegate_ `DECLARE_DWORD_COUNTER_STAT_EXTERN(TEXT("Sampler: Num reserved descriptors"), STAT_NumReservedSamplerOnlineDescriptors,`
- L150 _delegate_ `DECLARE_DWORD_COUNTER_STAT_EXTERN(TEXT("Sampler: Num reused descriptors"), STAT_NumReusedSamplerOnlineDescriptors, ST`
- L152 _delegate_ `DECLARE_DWORD_ACCUMULATOR_STAT_EXTERN(TEXT("View Global: Free Descriptors"), STAT_GlobalViewHeapFreeDescriptors, STAT`
- L153 _delegate_ `DECLARE_DWORD_ACCUMULATOR_STAT_EXTERN(TEXT("View Global: Reserved Descriptors"), STAT_GlobalViewHeapReservedDescriptors,`
- L154 _delegate_ `DECLARE_DWORD_ACCUMULATOR_STAT_EXTERN(TEXT("View Global: Used Descriptors"), STAT_GlobalViewHeapUsedDescriptors, STAT`
- L155 _delegate_ `DECLARE_DWORD_ACCUMULATOR_STAT_EXTERN(TEXT("View Global: Wasted Descriptors"), STAT_GlobalViewHeapWastedDescriptors, ST`
- L156 _delegate_ `DECLARE_DWORD_COUNTER_STAT_EXTERN(TEXT("View Global: Block Allocations"), STAT_GlobalViewHeapBlockAllocations, STA`
- L158 _delegate_ `DECLARE_DWORD_ACCUMULATOR_STAT_EXTERN(TEXT("Explicit sampler descriptor heaps"), STAT_ExplicitSamplerDescriptorHeaps,`
- L159 _delegate_ `DECLARE_DWORD_ACCUMULATOR_STAT_EXTERN(TEXT("Explicit sampler descriptors"), STAT_ExplicitSamplerDescriptors, STATG`
- L161 _delegate_ `DECLARE_DWORD_ACCUMULATOR_STAT_EXTERN(TEXT("Explicit view descriptor heaps"), STAT_ExplicitViewDescriptorHeaps, STA`
- L162 _delegate_ `DECLARE_DWORD_ACCUMULATOR_STAT_EXTERN(TEXT("Explicit view descriptors"), STAT_ExplicitViewDescriptors, STATGROU`
- L164 _delegate_ `DECLARE_DWORD_COUNTER_STAT_EXTERN(TEXT("Max used explicit sampler descriptors in a single heap"), STAT_ExplicitMaxUse`
- L165 _delegate_ `DECLARE_DWORD_COUNTER_STAT_EXTERN(TEXT("Used explicit sampler descriptors (per frame)"), STAT_ExplicitUsedSamplerD`
- L166 _delegate_ `DECLARE_DWORD_COUNTER_STAT_EXTERN(TEXT("Used explicit view descriptors (per frame)"), STAT_ExplicitUsedViewDesc`

### `Source/Runtime/D3D12RHI/Private/D3D12Submission.h` (Private)


#### enum `ED3D12SyncPointType`  
`enum class ED3D12SyncPointType`  
_L33-42_
- L37 _public enumerator_ `GPUOnly` — Sync points of this type do not include an FGraphEvent, so cannot report completion to the CPU (via either IsComplete() or Wait())
- L41 _public enumerator_ `GPUAndCPU` — Sync points of this type include an FGraphEvent. The IsComplete() and Wait() functions can be used to poll for completion from the CPU, or block the CPU, respectively.

#### struct `FD3D12Fence`  
`struct FD3D12Fence`  
_L45-56_
- desc: Fence type used by the device queues to manage GPU completion
- L47 _public member_ `FD3D12Queue* const OwnerQueue;`
- L48 _public member_ `TRefCountPtr<ID3D12Fence> D3DFence;`
- L49 _public member_ `uint64 NextCompletionValue = 1;`
- L50 _public member_ `std::atomic<uint64> LastSignaledValue = 0;`
- L51 _public member_ `bool bInterruptAwaited = false;`
- L53 _public function_ `FD3D12Fence(FD3D12Queue* OwnerQueue) : OwnerQueue(OwnerQueue)`

#### struct `FD3D12ResolvedFence`  
`struct FD3D12ResolvedFence`  
_L59-68_
- desc: Used by FD3D12SyncPoint and the submission thread to fix up signaled fence values at the end-of-pipe
- L61 _public member_ `FD3D12Fence& Fence;`
- L62 _public member_ `uint64 Value = 0;`
- L64 _public function_ `FD3D12ResolvedFence(FD3D12Fence& Fence, uint64 Value) : Fence(Fence) , Value(Value)`

#### class `FD3D12SyncPoint`  
`class FD3D12SyncPoint final : public FRefCountedObject`  
_L79-164_
- inherits: `FRefCountedObject`
- desc: A sync point is a logical point on a GPU queue's timeline that can be awaited by other queues, or the CPU. These are used throughout the RHI as a way to abstract the underlying D3D12 fences. The submission thread manages the underlying fences and signaled values, and reports completion to the relevant sync points via an FGraphEvent. Sync points are one-shot, meaning they represent a single timeline point, and are released after use, via ref-counting. Use FD3D12SyncPoint::Create() to make a new sync point and hold a reference to it via a FD3D12SyncPointRef object.
- L84 _private member_ `static TLockFreePointerListUnordered<void, PLATFORM_CACHE_LINE_SIZE> MemoryPool;`
- L87 _private prototype_ `FD3D12SyncPoint(FD3D12SyncPoint const&) = delete;` — No copying or moving
- L88 _private prototype_ `FD3D12SyncPoint(FD3D12SyncPoint&&) = delete;`
- L90 _private member_ `TOptional<FD3D12ResolvedFence> ResolvedFence;`
- L91 _private member_ `FGraphEventRef GraphEvent;`
- L93 _private function_ `FD3D12SyncPoint(ED3D12SyncPointType Type, FName InDebugName) #if RHI_USE_SYNC_POINT_DEBUG_NAME :DebugName(InDebugName) #endif`
- L105 _public function_ `static FD3D12SyncPointRef Create(ED3D12SyncPointType Type, FName InDebugName)`
- L111 _public function_ `bool IsComplete() const`
- L117 _public prototype_ `void Wait() const;`
- L119 _public function_ `FGraphEvent* GetGraphEvent() const`
- L125 _public function_ `ED3D12SyncPointType GetType() const`
- L132 _public function_ `void* operator new(size_t Size)`
- L144 _public function_ `void operator delete(void* Pointer)`
- L149 _public function_ `inline FName GetDebugName() const`
- L161 _private member_ `FName DebugName;`

#### struct `FD3D12CommitReservedResourceDesc`  
`struct FD3D12CommitReservedResourceDesc`  
_L166-170_
- L168 _public member_ `FD3D12Resource* Resource = nullptr;`
- L169 _public member_ `uint64 CommitSizeInBytes = 0;`

#### struct `FD3D12BatchedPayloadObjects`  
`struct FD3D12BatchedPayloadObjects`  
_L172-188_
- L174 _public member_ `TArray<FD3D12QueryLocation> TimestampQueries;`
- L175 _public member_ `TArray<FD3D12QueryLocation> OcclusionQueries;`
- L176 _public member_ `TArray<FD3D12QueryLocation> PipelineStatsQueries;`
- L177 _public member_ `TMap<TRefCountPtr<FD3D12QueryHeap>, TArray<FD3D12QueryRange>> QueryRanges;`
- L179 _public function_ `bool IsEmpty() const`

#### struct `FD3D12PayloadBaseFixLayout`  
`struct FD3D12PayloadBaseFixLayout`  
_L191-194_
- desc: Hacky base class to avoid 8 bytes of padding after the vtable
- L193 _public prototype_ `virtual ~FD3D12PayloadBaseFixLayout() = default;`

#### struct `FD3D12PresentArgs`  
`struct FD3D12PresentArgs`  
_L196-210_
- L199 _public member_ `FGraphEventRef PresentEvent;` — Sync event -> Present called
- L202 _public member_ `FD3D12Viewport* DrawingViewport = nullptr;` — In params
- L203 _public member_ `uint64 FrameCounter = 0;`
- L204 _public member_ `bool bLockToVsync = false;`
- L206 _public function_ `inline bool IsValid() const`

#### struct `FD3D12PayloadBase`  
`struct FD3D12PayloadBase : public FD3D12PayloadBaseFixLayout`  
_L213-334_
- inherits: `FD3D12PayloadBaseFixLayout`
- desc: A single unit of work (specific to a single GPU node and queue type) to be processed by the submission thread.
- L236 _public member_ `FD3D12Queue& Queue;` — Constants
- L245 _public member_ `} SyncPointsToWait;`
- L252 _public member_ `TArray<FQueueFence, TInlineAllocator<GD3D12MaxNumQueues>> QueueFencesToWait;`
- L257 _public member_ `} ManualFencesToWait;`
- L259 _public prototype_ `void AddQueueFenceWait(FD3D12Fence& Fence, uint64 Value);`
- L262 _public member_ `TArray<FD3D12CommitReservedResourceDesc> ReservedResourcesToCommit;` — UpdateReservedResources
- L265 _public member_ `bool bAlwaysSignal = false;` — Flags.
- L266 _public member_ `std::atomic<bool> bSubmitted { false };`
- L269 _public member_ `TFunction<void(ID3D12CommandQueue*)> PreExecuteCallback;` — Used by RHIRunOnQueue
- L272 _public member_ `TArray<FD3D12CommandList*> CommandListsToExecute;` — Execute
- L275 _public member_ `TArray<FManualFence> ManualFencesToSignal;` — Signal
- L276 _public member_ `TArray<FD3D12SyncPointRef> SyncPointsToSignal;`
- L277 _public member_ `uint64 CompletionFenceValue = 0;`
- L279 _public member_ `FGraphEventRef SubmissionEvent;`
- L280 _public member_ `TOptional<uint64> SubmissionTime;`
- L282 _public member_ `TOptional<FD3D12Timing*> Timing;`
- L285 _public member_ `TArray<FD3D12CommandAllocator*> AllocatorsToRelease;` — Cleanup
- L287 _public member_ `FD3D12BatchedPayloadObjects BatchedObjects;`
- L289 _public member_ `FD3D12PresentArgs PresentArgs;`
- L292 _public member_ `FRHIBreadcrumbRange BreadcrumbRange {};`
- L293 _public member_ `TSharedPtr<FRHIBreadcrumbAllocatorArray> BreadcrumbAllocators {};`
- L296 _public member_ `UE::RHI::GPUProfiler::FEventStream EventStream;`
- L297 _public member_ `TOptional<UE::RHI::GPUProfiler::FEvent::FFrameBoundary> EndFrameEvent;`
- L299 _public prototype_ `virtual ~FD3D12PayloadBase();`
- L301 _public prototype_ `virtual void PreExecute();`
- L303 _public function_ `virtual bool HasPreExecuteWork() const`
- L308 _public function_ `virtual bool RequiresQueueFenceSignal() const`
- L313 _public function_ `virtual bool HasWaitWork() const`
- L318 _public function_ `virtual bool HasUpdateReservedResourcesWork() const`
- L323 _public function_ `virtual bool HasSignalWork() const`
- L333 _protected prototype_ `FD3D12PayloadBase(FD3D12Queue& Queue);`

#### struct `FD3D12PayloadBase::FManualFence`  
`struct FManualFence`  
_L216-233_
- desc: Used to signal FD3D12ManualFence instances on the submission thread.
- L219 _public member_ `TRefCountPtr<ID3D12Fence> Fence;` — The D3D fence to signal
- L222 _public member_ `uint64 Value;` — The value to signal the fence with.
- L225 _public member_ `TSharedPtr<std::atomic<bool>> bHasSignalled;` — Optional bool pointer to check whether this fence has been signalled
- L227 _public prototype_ `FManualFence() = default;`
- L228 _public function_ `FManualFence(TRefCountPtr<ID3D12Fence>&& Fence, uint64 Value, const TSharedPtr<std::atomic<bool>>& bHasSignalled) : Fence(MoveTemp(Fence)) , Value(Value) , bHasSignalled(bHasSignalled)`

#### struct `FD3D12PayloadBase::(anonymous)`  
`struct : public TArray<FD3D12SyncPointRef>`  
_L239-245_
- inherits: `TArray<FD3D12SyncPointRef>`
- desc: Wait

#### struct `FD3D12PayloadBase::FQueueFence`  
`struct FQueueFence`  
_L247-251_
- L249 _public member_ `FD3D12Fence& Fence;`
- L250 _public member_ `uint64 Value;`

#### struct `FD3D12PayloadBase::(anonymous)`  
`struct : TArray<FManualFence>`  
_L253-257_
- inherits: `TArray<FManualFence>`

#### Free symbols / members of external scopes

- L28 _typedef_ `using FD3D12SyncPointRef = TRefCountPtr<FD3D12SyncPoint>;`
- L31 _macro_ `#define UE_D3D12_STATIC_FNAME(String) (([]() -> const FName& { static const FName Name(TEXT(String)); return Name; })())` — Helper macro to create a static FName from a string literal, avoiding repeated FName construction.
- L243 _member_ `int32 Index = 0;` (scope `FD3D12PayloadBase::__anonbec1e4830108`) — Used to pause / resume iteration of the sync point array on the submission thread when we find a sync point that is unresolved.
- L255 _member_ `int32 Index = 0;` (scope `FD3D12PayloadBase::__anonbec1e4830208`)

### `Source/Runtime/D3D12RHI/Private/D3D12Texture.h` (Private)


#### class `FD3D12Texture`  
`class FD3D12Texture : public FRHITexture, public FD3D12BaseShaderResource, public FD3D12LinkedAdapterObject<FD3D12Texture>`  
_L30-185_
- inherits: `FRHITexture,FD3D12BaseShaderResource,FD3D12LinkedAdapterObject<FD3D12Texture>`
- desc: D3D12 RHI Texture class
- L35 _public prototype_ `static bool CanBe4KAligned(const FD3D12ResourceDesc& Desc, EPixelFormat UEFormat);` — Static helper functions
- L37 _public prototype_ `FD3D12Texture() = delete;`
- L40 _public function_ `FD3D12Texture( const FRHITextureCreateDesc& InDesc, class FD3D12Device* InParent) : FRHITexture(InDesc) , FD3D12BaseShaderResource(InParent)` — Initialization constructor.
- L45 _public prototype_ `virtual ~FD3D12Texture();`
- L48 _public function_ `virtual void AddRef() const override` — IRefCountedObject interface overrides from FD3D12BaseShaderResource
- L49 _public function_ `virtual FReturnedRefCountValue Release() const override`
- L50 _public function_ `virtual FReturnedRefCountValue GetRefCount() const override`
- L54 _public prototype_ `bool GetResourceInfo(FRHIResourceInfo& OutResourceInfo) const override;`
- L59 _public function_ `virtual void* GetTextureBaseRHI() override`
- L61 _public function_ `virtual void* GetTextureBaseRHI() override final`
- L63 _public prototype_ `virtual void* GetNativeResource() const override final;`
- L64 _public prototype_ `virtual FRHIDescriptorHandle GetDefaultBindlessHandle() const override;`
- L67 _public function_ `bool IsStreamable() const` — Accessors.
- L68 _public function_ `bool SkipsFastClearFinalize() const`
- L70 _public prototype_ `void GetReadBackHeapDesc(D3D12_PLACED_SUBRESOURCE_FOOTPRINT& OutFootprint, uint32 Subresource) const;`
- L72 _public function_ `bool HasCreatedRTVsPerSlice() const`
- L77 _public function_ `bool HasRenderTargetViews() const`
- L78 _public function_ `TConstArrayView<TSharedPtr<FD3D12RenderTargetView>> GetRenderTargetViews() const`
- L80 _public function_ `FD3D12ShaderResourceView* GetShaderResourceView() const`
- L81 _public prototype_ `FD3D12RenderTargetView* GetRenderTargetView(int32 MipIndex, int32 ArraySliceIndex) const;`
- L82 _public function_ `FD3D12DepthStencilView* GetDepthStencilView(FExclusiveDepthStencil AccessType) const`
- L85 _public function_ `bool GetRequiresTypelessResourceDiscardWorkaround() const`
- L89 _public prototype_ `void UploadInitialData(FRHICommandListBase& RHICmdList, FD3D12ResourceLocation&& SourceLocation, ED3D12Access InDestinationD3D12Access);` — Setup functionality
- L90 _public prototype_ `void CreateViews(FD3D12Texture* FirstLinkedObject);`
- L91 _public function_ `void SetCreatedRTVsPerSlice(bool Value, int32 InRTVArraySize)`
- L97 _public function_ `void SetNumRTVs(int32 Num)`
- L102 _public function_ `void EmplaceRTV(D3D12_RENDER_TARGET_VIEW_DESC const& RTVDesc, int32 Index, FD3D12Texture* FirstLinkedObject)`
- L111 _public function_ `void EmplaceDSV(D3D12_DEPTH_STENCIL_VIEW_DESC const& DSVDesc, int32 Index, FD3D12Texture* FirstLinkedObject)`
- L120 _public function_ `void EmplaceSRV(D3D12_SHADER_RESOURCE_VIEW_DESC const& SRVDesc, FD3D12Texture* FirstLinkedObject)`
- L135 _public prototype_ `FRHILockTextureResult Lock(FRHICommandListBase& RHICmdList, const FRHILockTextureArgs& Arguments);` — Locking/update functions
- L136 _public prototype_ `void Unlock(FRHICommandListBase& RHICmdList, const FRHILockTextureArgs& Arguments);`
- L138 _public prototype_ `void UpdateTexture2D(FRHICommandListBase& RHICmdList, uint32 MipIndex, const struct FUpdateTextureRegion2D& UpdateRegion, uint32 SourcePitch, const uint8* SourceData);`
- L139 _public prototype_ `void UpdateTexture(FD3D12CommandContext& Context, uint32 MipIndex, uint32 DestX, uint32 DestY, uint32 DestZ, const D3D12_TEXTURE_COPY_LOCATION& SourceCopyLocation, FD3D12Resource* SourceResource);`
- L141 _public prototype_ `void CopyTextureRegion(FD3D12CommandContext& Context, uint32 DestX, uint32 DestY, uint32 DestZ, FD3D12Texture* SourceTexture, const D3D12_BOX& SourceBox);`
- L145 _public prototype_ `void AliasResources(FD3D12Texture* Texture);` — Resource aliasing
- L146 _public function_ `void SetAliasingSource(FTextureRHIRef& SourceTextureRHI)`
- L153 _public prototype_ `void ReuseStagingBuffer(TUniquePtr<FD3D12LockedResource>&& LockedResource, uint32 Subresource);` — Staging buffer reuse
- L157 _protected member_ `TSharedPtr<FD3D12ShaderResourceView> ShaderResourceView;` — A shader resource view of the texture.
- L160 _protected member_ `bool bCreatedRTVsPerSlice{ false };` — Set when RTVs are created for each slice - TexCreate_TargetArraySlicesIndependently for TextureArrays & Cubemaps
- L163 _protected member_ `bool bRequiresTypelessResourceDiscardWorkaround = false;`
- L167 _protected member_ `int32 RTVArraySizePerMip{};` — Number of RTVs per mip when stored per slice
- L170 _protected member_ `TArray<TSharedPtr<FD3D12RenderTargetView>, TInlineAllocator<1>> RenderTargetViews;` — A render targetable view of the texture.
- L173 _protected member_ `TSharedPtr<FD3D12DepthStencilView> DepthStencilViews[FExclusiveDepthStencil::MaxIndex];` — A depth-stencil targetable view of the texture.
- L176 _protected member_ `TMap<uint32, TUniquePtr<FD3D12LockedResource>> LockedMap;` — Data for each subresource while texture is locked
- L179 _protected member_ `mutable TUniquePtr<D3D12_PLACED_SUBRESOURCE_FOOTPRINT> FirstSubresourceFootprint;` — Cached footprint size of first resource - optimization
- L183 _protected member_ `FTextureRHIRef AliasingSourceTexture;` — Source texture when aliased
- L187 _function_ `inline FD3D12RenderTargetView* FD3D12Texture::GetRenderTargetView(int32 MipIndex, int32 ArraySliceIndex) const`

#### struct `TD3D12ResourceTraits`  
`template<> struct TD3D12ResourceTraits<FRHITexture>`  
_L211-214_
- L213 _public typedef_ `typedef FD3D12Texture TConcreteType;`

#### class `FD3D12BackBufferReferenceTexture2D`  
`class FD3D12BackBufferReferenceTexture2D : public FD3D12Texture`  
_L219-238_
- inherits: `FD3D12Texture`
- L222 _public function_ `FD3D12BackBufferReferenceTexture2D(const FRHITextureCreateDesc& InDesc, FD3D12Viewport* InViewPort, FD3D12Device* InDevice) : FD3D12Texture(InDesc, InDevice) , Viewport(InViewPort)`
- L228 _public function_ `FD3D12Viewport* GetViewPort() const`
- L230 _public prototype_ `FRHITexture* GetBackBufferTexture() const;`
- L231 _public prototype_ `virtual FRHIDescriptorHandle GetDefaultBindlessHandle() const override;`
- L234 _public function_ `virtual void* GetTextureBaseRHI() override` — FRHITexture overrides
- L237 _private member_ `FD3D12Viewport* const Viewport;`

#### Free symbols / members of external scopes

- L13 _macro_ `#define GUARDED_TEXTURE_CREATES (PLATFORM_WINDOWS && !(UE_BUILD_SHIPPING || UE_BUILD_TEST || PLATFORM_COMPILER_CLANG))` — If true, guard texture creates with SEH to log more information about a driver crash we are seeing during texture streaming.
- L16 _prototype_ `void SafeCreateTexture2D( FD3D12Device* pDevice, FD3D12Adapter* Adapter, const FD3D12ResourceDesc& TextureDesc, const D3D12_CLEAR_VALUE* ClearValue, FD3D12ResourceLocation* OutTexture2D, FD3D12BaseShaderResource* Owner, EPixelFormat Format, ETextureCreateFlags Flags, ED3D12Access InInitialD3D12Access, ED3D12Access InDefaultD3D12Access, const TCHAR* Name);` — @todo don't make global here!
- L242 _function_ `FORCEINLINE FD3D12Texture* GetD3D12TextureFromRHITexture(FRHITexture* Texture)` — Given a pointer to a RHI texture that was created by the D3D12 RHI, returns a pointer to the FD3D12Texture it encapsulates.
- L255 _function_ `FORCEINLINE FD3D12Texture* GetD3D12TextureFromRHITexture(FRHITexture* Texture, uint32 GPUIndex)`
- L270 _namespace_ `namespace FD3D12TextureStats`
- L276 _prototype_ `void UpdateD3D12TextureStats(FD3D12Texture& Texture, const FD3D12ResourceDesc& ResourceDesc, const FRHITextureDesc& TextureDesc, uint64 TextureSize, bool bNewTexture, bool bAllocating);` (scope `FD3D12TextureStats`) — Note: This function can be called from many different threads @param TextureSize >0 to allocate, <0 to deallocate @param b3D true:3D, false:2D or cube map @param bStreamable true:Streamable, false:not streamable
- L278 _prototype_ `void D3D12TextureAllocated(FD3D12Texture& Texture);` (scope `FD3D12TextureStats`)
- L279 _prototype_ `void D3D12TextureDeleted(FD3D12Texture& Texture);` (scope `FD3D12TextureStats`)
- L282 _namespace_ `namespace UE`
- L282 _namespace_ `namespace D3D12RHI` (scope `UE`)
- L282 _namespace_ `namespace TextureUtils` (scope `UE::D3D12RHI`)
- L285 _prototype_ `D3D12_CLEAR_VALUE* FillClearValue(D3D12_CLEAR_VALUE& ClearValue, const FD3D12ResourceDesc& ResourceDesc, const FRHITextureDesc& TextureDesc);` (scope `UE::D3D12RHI::TextureUtils`) — Fills in the ClearValue argument based on the ResourceDesc and CreateDesc flags.
- L287 _prototype_ `void ReconcileInitialState(FRHICommandListBase& RHICmdList, FD3D12Texture* Texture, ED3D12Access CurrentD3D12Access, ED3D12Access NeededD3D12Access, bool bNeedsDiscard);` (scope `UE::D3D12RHI::TextureUtils`)
- L289 _prototype_ `uint64 CalculateResourceSize(FD3D12Texture* Texture);` (scope `UE::D3D12RHI::TextureUtils`)
- L290 _prototype_ `void CopyBulkData(void* UploadMemory, uint64 UploadMemorySize, FD3D12Texture* Texture, FResourceBulkDataInterface* BulkData);` (scope `UE::D3D12RHI::TextureUtils`)
- L291 _prototype_ `D3D12_PLACED_SUBRESOURCE_FOOTPRINT GetInitializerSubresourceFootprint(FD3D12Texture* Texture, uint32 Subresource, uint32& NumRows);` (scope `UE::D3D12RHI::TextureUtils`)

### `Source/Runtime/D3D12RHI/Private/D3D12TextureReference.h` (Private)


#### struct `FD3D12TextureReferenceReplaceListener`  
`struct FD3D12TextureReferenceReplaceListener`  
_L11-14_
- desc: Resource which might needs to be notified about changes on replaced referenced textures
- L13 _public prototype_ `virtual void TextureReplaced(FD3D12ContextArray const& Contexts, FD3D12RHITextureReference* TextureReference, FD3D12Texture* CurrentTexture, FD3D12Texture* NewTexture) = 0;`

#### class `FD3D12RHITextureReference`  
`class FD3D12RHITextureReference : public FD3D12DeviceChild, public FRHITextureReference, public FD3D12LinkedAdapterObject<FD3D12RHITextureReference> #if PLATFORM_SUPPORTS_BINDLESS_RENDERING , public FD3D12ShaderResourceRenameListener #endif`  
_L16-71_
- inherits: `FD3D12DeviceChild,FRHITextureReference,FD3D12LinkedAdapterObject<FD3D12RHITextureReference>,FD3D12ShaderResourceRenameListener`
- L22 _public prototype_ `FD3D12RHITextureReference() = delete;`
- L23 _public prototype_ `FD3D12RHITextureReference(FD3D12Device* InDevice, FD3D12Texture* InReferencedTexture, FD3D12RHITextureReference* FirstLinkedObject);`
- L24 _public prototype_ `~FD3D12RHITextureReference();`
- L28 _public prototype_ `virtual void ResourceRenamed(FD3D12ContextArray const& Contexts, FD3D12BaseShaderResource* InRenamedResource, FD3D12ResourceLocation* InNewResourceLocation) final override;` — FD3D12ShaderResourceRenameListener
- L31 _public prototype_ `void SwitchToNewTexture(FD3D12ContextArray const& Contexts, FD3D12Texture* InNewTexture);`
- L34 _public member_ `uint32 ReferencedDescriptorVersion{};`
- L37 _public function_ `void AddReplaceListener(FD3D12TextureReferenceReplaceListener* InListener)`
- L44 _public function_ `void RemoveReplaceListener(FD3D12TextureReferenceReplaceListener* InListener)`
- L54 _private function_ `bool HasListeners() const`
- L60 _private function_ `void NotifyListeners(FD3D12ContextArray const& Contexts, FD3D12Texture* CurrentTexture, FD3D12Texture* NewTexture)`
- L69 _private member_ `mutable FCriticalSection TextureReplaceListenersCS;`
- L70 _private member_ `TArray<FD3D12TextureReferenceReplaceListener*> TextureReplaceListeners;`

#### struct `TD3D12ResourceTraits`  
`template<> struct TD3D12ResourceTraits<FRHITextureReference>`  
_L74-77_
- L76 _public typedef_ `using TConcreteType = FD3D12RHITextureReference;`

### `Source/Runtime/D3D12RHI/Private/D3D12Tracing.h` (Private)


#### Free symbols / members of external scopes

- L17 _namespace_ `namespace RenderTracing`
- L17 _namespace_ `namespace D3D12` (scope `RenderTracing`)
- L20 _prototype_ `void AssociateContext(const FD3D12ContextCommon* D3D12Context, const IRHIComputeContext* RHIContext);` (scope `RenderTracing::D3D12`)
- L21 _prototype_ `void PayloadCreated(const FD3D12Payload* Payload, const FD3D12Queue& Queue);` (scope `RenderTracing::D3D12`)
- L22 _prototype_ `void AddPayload(const FD3D12ContextCommon* D3D12Context, const FD3D12Payload* Payload);` (scope `RenderTracing::D3D12`)
- L23 _prototype_ `void OpenCommandList(const FD3D12Payload* Payload, const ID3D12CommandList* D3D12CmdList);` (scope `RenderTracing::D3D12`)
- L24 _prototype_ `void CloseCommandList(const FD3D12Payload* Payload, const ID3D12CommandList* D3D12CmdList);` (scope `RenderTracing::D3D12`)
- L25 _prototype_ `void WaitSyncPoint(const FD3D12Payload* Payload, const FD3D12SyncPoint* SyncPoint);` (scope `RenderTracing::D3D12`)
- L26 _prototype_ `void SignalSyncPoint(const FD3D12Payload* Payload, const FD3D12SyncPoint* SyncPoint);` (scope `RenderTracing::D3D12`)
- L27 _prototype_ `void WaitManualFence(const FD3D12Payload* Payload, const ID3D12Fence* Fence, uint64 Value);` (scope `RenderTracing::D3D12`)
- L28 _prototype_ `void SignalManualFence(const FD3D12Payload* Payload, const ID3D12Fence* Fence, uint64 Value);` (scope `RenderTracing::D3D12`)
- L30 _prototype_ `void ProcessSubmissionQueueEnter();` (scope `RenderTracing::D3D12`)
- L31 _prototype_ `void SubmitYieldOnUnresolvedSyncPoint(const FD3D12Queue& Queue, const FD3D12Payload* Payload, const FD3D12SyncPoint* SyncPoint);` (scope `RenderTracing::D3D12`)
- L32 _prototype_ `void SubmitYieldOnUnresolvedManualFence(const FD3D12Queue& Queue, const FD3D12Payload* Payload, const ID3D12Fence* Fence, uint64 Value);` (scope `RenderTracing::D3D12`)
- L33 _prototype_ `void SubmitWaitQueueFence(const FD3D12Payload* Payload, const FD3D12Queue& ExecutingQueue, const FD3D12Queue& WaitOnQueue, uint64 Value);` (scope `RenderTracing::D3D12`)
- L34 _prototype_ `void SubmitWaitManualFence(const FD3D12Payload* Payload, const FD3D12Queue& ExecutingQueue, const ID3D12Fence* Fence, uint64 Value);` (scope `RenderTracing::D3D12`)
- L35 _prototype_ `void SubmitPlatformCommandLists(const FD3D12Queue& Queue, TConstArrayView<FD3D12Payload*> Payloads, TConstArrayView<ID3D12CommandList*> CmdLists);` (scope `RenderTracing::D3D12`)
- L36 _prototype_ `void SubmitSignalManualFence(const FD3D12Payload* Payload, const FD3D12Queue& Queue, const ID3D12Fence* Fence, uint64 Value);` (scope `RenderTracing::D3D12`)
- L37 _prototype_ `void SubmitSignalQueueFence(const FD3D12Payload* Payload, const FD3D12Queue& Queue, uint64 Value);` (scope `RenderTracing::D3D12`)
- L38 _prototype_ `void SubmitResolveSyncPoint(const FD3D12Queue& Queue, const FD3D12Payload* Payload, const FD3D12SyncPoint* SyncPoint, uint64 Value);` (scope `RenderTracing::D3D12`)
- L39 _prototype_ `void ProcessSubmissionQueueExit(uint8 Status);` (scope `RenderTracing::D3D12`)
- L41 _prototype_ `void ProcessInterruptQueueEnter();` (scope `RenderTracing::D3D12`)
- L42 _prototype_ `void InterruptQueueFenceSignaled(const FD3D12Queue& Queue, FD3D12Payload* PendingPayload, uint64 CurrentFenceValue, uint64 LastCPUSignaledFenceValue);` (scope `RenderTracing::D3D12`)
- L43 _prototype_ `void ProcessInterruptQueueExit(uint8 Status);` (scope `RenderTracing::D3D12`)

### `Source/Runtime/D3D12RHI/Private/D3D12TransientResourceAllocator.h` (Private)


#### class `FD3D12TransientHeap`  
`class FD3D12TransientHeap final : public FRHITransientHeap , public FRefCountedObject , public FD3D12LinkedAdapterObject<FD3D12TransientHeap>`  
_L8-21_
- inherits: `FRHITransientHeap,FRefCountedObject,FD3D12LinkedAdapterObject<FD3D12TransientHeap>`
- L14 _public prototype_ `FD3D12TransientHeap(const FInitializer& Initializer, FD3D12Adapter* Adapter, FD3D12Device* Device, FRHIGPUMask VisibleNodeMask);`
- L15 _public prototype_ `~FD3D12TransientHeap();`
- L17 _public function_ `FD3D12Heap* Get()`
- L20 _private member_ `TRefCountPtr<FD3D12Heap> Heap;`

#### class `FD3D12TransientHeapCache`  
`class FD3D12TransientHeapCache final : public FRHITransientHeapCache , public FD3D12AdapterChild`  
_L23-35_
- inherits: `FRHITransientHeapCache,FD3D12AdapterChild`
- L28 _public prototype_ `static TUniquePtr<FD3D12TransientHeapCache> Create(FD3D12Adapter* ParentAdapter);`
- L31 _public prototype_ `FRHITransientHeap* CreateHeap(const FRHITransientHeap::FInitializer& Initializer) override;` — FRHITransientResourceSystem Overrides
- L34 _private prototype_ `FD3D12TransientHeapCache(const FInitializer& Initializer, FD3D12Adapter* ParentAdapter);`

#### class `FD3D12TransientResourceHeapAllocator`  
`class FD3D12TransientResourceHeapAllocator final : public FRHITransientResourceHeapAllocator , public FD3D12AdapterChild`  
_L37-91_
- inherits: `FRHITransientResourceHeapAllocator,FD3D12AdapterChild`
- L42 _public prototype_ `FD3D12TransientResourceHeapAllocator(FD3D12TransientHeapCache& InHeapCache);`
- L45 _public function_ `bool SupportsResourceType(ERHITransientResourceType InType) const override` — IRHITransientResourceAllocator Overrides
- L55 _public prototype_ `FRHITransientTexture* CreateTexture(const FRHITextureCreateInfo& CreateInfo, const TCHAR* Name, const FRHITransientAllocationFences& Fences) override;`
- L56 _public prototype_ `FRHITransientBuffer* CreateBuffer(const FRHIBufferCreateInfo& CreateInfo, const TCHAR* Name, const FRHITransientAllocationFences& Fences) override;`
- L90 _private member_ `FD3D12Device* AllocationInfoQueryDevice;`

#### class `FD3D12TransientResourceHeapAllocator::FResourceAllocatorAdapter`  
`class FResourceAllocatorAdapter final : public FD3D12AdapterChild, public ID3D12ResourceAllocator`  
_L61-88_
- inherits: `FD3D12AdapterChild,ID3D12ResourceAllocator`
- desc: This adapter mocks the D3D12 resource allocator interface and performs placed resource creation.
- L64 _public function_ `FResourceAllocatorAdapter(FD3D12Adapter* Adapter, FD3D12TransientHeap& InHeap, const FRHITransientHeapAllocation& InAllocation, const D3D12_RESOURCE_DESC& InDesc) : FD3D12AdapterChild(Adapter) , Heap(InHeap) , Allocation(InAllocation) , Desc(InDesc)`
- L71 _public prototype_ `void AllocateResource( uint32 GPUIndex, D3D12_HEAP_TYPE InHeapType, const FD3D12ResourceDesc& InDesc, uint64 InSize, uint32 InAllocationAlignment, ED3D12Access InInitialD3D12Access, ED3D12ResourceStateMode InResourceStateMode, ED3D12Access InDefaultD3D12Access, const D3D12_CLEAR_VALUE* InClearValue, const TCHAR* InName, FD3D12ResourceLocation& ResourceLocation) override;`
- L84 _public member_ `FD3D12TransientHeap& Heap;`
- L85 _public member_ `const FRHITransientHeapAllocation& Allocation;`
- L86 _public member_ `const D3D12_RESOURCE_DESC Desc;`
- L87 _public member_ `uint64 GpuVirtualAddress = 0;`

### `Source/Runtime/D3D12RHI/Private/D3D12Util.h` (Private)


#### enum `EShaderVisibility`  
`enum EShaderVisibility`  
_L69-80_
- L71 _public enumerator_ `SV_Vertex`
- L72 _public enumerator_ `SV_Pixel`
- L73 _public enumerator_ `SV_Geometry`
- L75 _public enumerator_ `SV_Mesh`
- L76 _public enumerator_ `SV_Amplification`
- L78 _public enumerator_ `SV_All`
- L79 _public enumerator_ `SV_ShaderVisibilityCount`

#### enum `ERootSignatureType`  
`enum ERootSignatureType`  
_L82-90_
- L84 _public enumerator_ `RS_Raster`
- L85 _public enumerator_ `RS_RayTracingGlobal`
- L86 _public enumerator_ `RS_RayTracingLocal`
- L87 _public enumerator_ `RS_WorkGraphGlobal`
- L88 _public enumerator_ `RS_WorkGraphLocalCompute`
- L89 _public enumerator_ `RS_WorkGraphLocalRaster`

#### struct `FShaderRegisterCounts`  
`struct FShaderRegisterCounts`  
_L92-115_
- L94 _public member_ `uint8 SamplerCount;`
- L95 _public member_ `uint8 ConstantBufferCount;`
- L96 _public member_ `uint8 ShaderResourceCount;`
- L97 _public member_ `uint8 UnorderedAccessCount;`
- L99 _public function_ `inline bool operator==(const FShaderRegisterCounts& RHS) const`

#### struct `FD3D12QuantizedBoundShaderState`  
`struct FD3D12QuantizedBoundShaderState`  
_L117-159_
- L119 _public member_ `FRHIShaderBindingLayout ShaderBindingLayout;`
- L120 _public member_ `TStaticArray<FShaderRegisterCounts, SV_ShaderVisibilityCount> RegisterCounts;`
- L121 _public member_ `ERootSignatureType RootSignatureType = RS_Raster;`
- L138 _public function_ `inline bool operator==(const FD3D12QuantizedBoundShaderState& RHS) const`
- L158 _public prototype_ `static void InitShaderRegisterCounts(D3D12_RESOURCE_BINDING_TIER ResourceBindingTier, const FShaderCodePackedResourceCounts& Counts, FShaderRegisterCounts& Shader, bool bAllowUAVs = false);`

#### union `FD3D12QuantizedBoundShaderState::(anonymous)`  
``  
_L123-136_

#### struct `FD3D12QuantizedBoundShaderState::__anonbb02bb75010a::(anonymous)`  
``  
_L125-134_

#### class `FD3D12LockedKey`  
`class FD3D12LockedKey`  
_L197-236_
- desc: Keeps track of Locks for D3D12 objects
- L200 _public member_ `void* SourceObject;`
- L201 _public member_ `uint32 Subresource;`
- L204 _public function_ `FD3D12LockedKey() : SourceObject(NULL) , Subresource(0)`
- L207 _public function_ `FD3D12LockedKey(FD3D12Resource* source, uint32 subres = 0) : SourceObject((void*)source) , Subresource(subres)`
- L210 _public function_ `FD3D12LockedKey(class FD3D12ResourceLocation* source, uint32 subres = 0) : SourceObject((void*)source) , Subresource(subres)`
- L215 _public function_ `template<class ClassType> FD3D12LockedKey(ClassType* source, uint32 subres = 0) : SourceObject((void*)source) , Subresource(subres)`
- L218 _public function_ `bool operator==(const FD3D12LockedKey& Other) const`
- L222 _public function_ `bool operator!=(const FD3D12LockedKey& Other) const`
- L226 _public function_ `uint32 GetHash() const`

#### class `FD3D12BoundRenderTargets`  
`class FD3D12BoundRenderTargets`  
_L244-267_
- desc: Class for retrieving render targets currently bound to the device context.
- L248 _public prototype_ `explicit FD3D12BoundRenderTargets(FD3D12RenderTargetView** RTArray, uint32 NumActiveRTs, FD3D12DepthStencilView* DSView);` — Initialization constructor: requires the state cache.
- L251 _public prototype_ `~FD3D12BoundRenderTargets();` — Destructor.
- L254 _public function_ `FORCEINLINE int32 GetNumActiveTargets() const` — Accessors.
- L255 _public function_ `FORCEINLINE FD3D12RenderTargetView* GetRenderTargetView(int32 TargetIndex)`
- L256 _public function_ `FORCEINLINE FD3D12DepthStencilView* GetDepthStencilView()`
- L260 _private member_ `FD3D12RenderTargetView* RenderTargetViews[MaxSimultaneousRenderTargets];` — Active render target views.
- L263 _private member_ `FD3D12DepthStencilView* DepthStencilView;` — Active depth stencil view.
- L266 _private member_ `int32 NumActiveTargets;` — The number of active render targets.

#### struct `FThreadsafeQueue`  
`template <class Type> struct FThreadsafeQueue`  
_L275-363_
- desc: The base class of threadsafe reference counted objects.
- L278 _private member_ `mutable FCriticalSection SynchronizationObject;` — made this mutable so this class can have const functions and still be thread safe
- L279 _private member_ `TQueue<Type> Items;`
- L280 _private member_ `uint32 Size = 0;`
- L283 _public function_ `inline const uint32 GetSize() const`
- L285 _public function_ `void Enqueue(const Type& Item)`
- L292 _public function_ `bool Dequeue(Type& Result)`
- L300 _public function_ `template <typename CompareFunc> bool Dequeue(Type& Result, const CompareFunc& Func)`
- L319 _public function_ `template <typename ResultType, typename CompareFunc> bool BatchDequeue(TArray<ResultType>& Result, const CompareFunc& Func, uint32 MaxItems)`
- L344 _public function_ `bool Peek(Type& Result)`
- L350 _public function_ `bool IsEmpty()`
- L356 _public function_ `void Empty()`

#### struct `FD3D12ScopeLock`  
`struct FD3D12ScopeLock`  
_L665-672_
- L668 _public function_ `FD3D12ScopeLock(FCriticalSection* CritSec) : CS(CritSec)`
- L669 _public function_ `~FD3D12ScopeLock()`
- L671 _private member_ `FCriticalSection* CS;`

#### struct `FD3D12ScopeNoLock`  
`struct FD3D12ScopeNoLock`  
_L674-679_
- L677 _public function_ `FD3D12ScopeNoLock(FCriticalSection* CritSec)`
- L678 _public function_ `~FD3D12ScopeNoLock()`

#### Free symbols / members of external scopes

- L18 _namespace_ `namespace D3D12RHI`
- L27 _prototype_ `extern void VerifyD3D12Result(HRESULT Result, const ANSICHAR* Code, const ANSICHAR* Filename, uint32 Line, ID3D12Device* Device, FString Message = FString());` (scope `D3D12RHI`) — Checks that the given result isn't a failure.  If it is, the application exits with an appropriate error message. @param	Result - The result code to check @param	Code - The code which yielded the result. @param	Filename - The filename of the source file containing Code. @param	Line - The line number of Code within Filename.
- L36 _prototype_ `extern void VerifyD3D12CreateTextureResult(HRESULT D3DResult, const ANSICHAR* Code, const ANSICHAR* Filename, uint32 Line, const D3D12_RESOURCE_DESC& TextureDesc, ID3D12Device* Device);` (scope `D3D12RHI`) — Checks that the given result isn't a failure.  If it is, the application exits with an appropriate error message. @param	Result - The result code to check @param	Code - The code which yielded the result. @param	Filename - The filename of the source file containing Code. @param	Line - The line number of Code within Filename.
- L41 _macro_ `#define VERIFYD3D12RESULT_LAMBDA(x, Device, Lambda) {HRESULT hres = x; if (FAILED(hres)) { VerifyD3D12Result(hres, #x, __FILE__, __LINE__, Device, Lambda()); }}` — A macro for using VERIFYD3D12RESULT that automatically passes in the code and filename/line.
- L42 _macro_ `#define VERIFYD3D12RESULT_EX(x, Device) {HRESULT hres = x; if (FAILED(hres)) { VerifyD3D12Result(hres, #x, __FILE__, __LINE__, Device); }}`
- L43 _macro_ `#define VERIFYD3D12RESULT(x) {HRESULT hres = x; if (FAILED(hres)) { VerifyD3D12Result(hres, #x, __FILE__, __LINE__, nullptr); }}`
- L44 _macro_ `#define VERIFYD3D12CREATETEXTURERESULT(x, Desc, Device) {HRESULT hres = x; if (FAILED(hres)) { VerifyD3D12CreateTextureResult(hres, #x, __FILE__, __LINE__, Desc, Device); }}`
- L47 _prototype_ `void LogPageFaultData(class FD3D12Adapter* InAdapter, FD3D12Device* InDevice, D3D12_GPU_VIRTUAL_ADDRESS InPageFaultAddress);` (scope `D3D12RHI`) — Checks if given GPU virtual address corresponds to any known resource allocations and logs results
- L58 _prototype_ `bool ShouldSetD3D12ResourceName(const FD3D12ResourceLocation& ResourceLocation);`
- L60 _prototype_ `void SetD3D12ObjectName(ID3D12Object* Object, const TCHAR* Name);`
- L62 _prototype_ `void SetD3D12ResourceName(FD3D12ResourceLocation& ResourceLocation, const TCHAR* Name);`
- L63 _prototype_ `void SetD3D12ResourceName(FD3D12Resource* Resource, const TCHAR* Name);`
- L64 _prototype_ `void SetD3D12ResourceName(FD3D12Buffer* Resource, const TCHAR* Name);`
- L65 _prototype_ `void SetD3D12ResourceName(FD3D12Texture* Resource, const TCHAR* Name);`
- L67 _prototype_ `FString GetD312ObjectName(ID3D12Object* const Object);`
- L107 _function_ `friend uint32 GetTypeHash(const FShaderRegisterCounts& Counts)`
- L126 _member_ `uint8 bAllowIAInputLayout : 1;` (scope `FD3D12QuantizedBoundShaderState::__anonbb02bb75010a::__anonbb02bb750208`)
- L127 _member_ `uint8 bNeedsAgsIntrinsicsSpace : 1;` (scope `FD3D12QuantizedBoundShaderState::__anonbb02bb75010a::__anonbb02bb750208`)
- L128 _member_ `uint8 bNeedsNvIntrinsicsSpace : 1;` (scope `FD3D12QuantizedBoundShaderState::__anonbb02bb75010a::__anonbb02bb750208`)
- L129 _member_ `uint8 bUseDiagnosticBuffer : 1;` (scope `FD3D12QuantizedBoundShaderState::__anonbb02bb75010a::__anonbb02bb750208`)
- L130 _member_ `uint8 bUseDirectlyIndexedResourceHeap : 1;` (scope `FD3D12QuantizedBoundShaderState::__anonbb02bb75010a::__anonbb02bb750208`)
- L131 _member_ `uint8 bUseDirectlyIndexedSamplerHeap : 1;` (scope `FD3D12QuantizedBoundShaderState::__anonbb02bb75010a::__anonbb02bb750208`)
- L132 _member_ `uint8 bUseRootConstants : 1;` (scope `FD3D12QuantizedBoundShaderState::__anonbb02bb75010a::__anonbb02bb750208`)
- L133 _member_ `uint8 Padding : 1;` (scope `FD3D12QuantizedBoundShaderState::__anonbb02bb75010a::__anonbb02bb750208`)
- L135 _member_ `uint8 Flags;` (scope `FD3D12QuantizedBoundShaderState::__anonbb02bb75010a`)
- L146 _function_ `friend uint32 GetTypeHash(const FD3D12QuantizedBoundShaderState& State)`
- L166 _function_ `FORCEINLINE uint32 GetD3D12CubeFace(ECubeFace Face)` — Convert from ECubeFace to D3DCUBEMAP_FACES type @param Face - ECubeFace type to convert @return D3D cube face enum value
- L189 _function_ `FORCEINLINE uint32 CalcSubresource(uint32 MipSlice, uint32 ArraySlice, uint32 MipLevels)` — Calculate a subresource index for a texture
- L232 _function_ `friend uint32 GetTypeHash(const FD3D12LockedKey& K)` — Hashing function.
- L269 _prototype_ `void LogExecuteCommandLists(uint32 NumCommandLists, ID3D12CommandList *const *ppCommandLists);`
- L365 _function_ `inline bool IsCPUWritable(D3D12_HEAP_TYPE HeapType, const D3D12_HEAP_PROPERTIES *pCustomHeapProperties = nullptr)`
- L373 _function_ `inline bool IsGPUOnly(D3D12_HEAP_TYPE HeapType, const D3D12_HEAP_PROPERTIES *pCustomHeapProperties = nullptr)`
- L381 _function_ `inline bool IsCPUAccessible(D3D12_HEAP_TYPE HeapType, const D3D12_HEAP_PROPERTIES* pCustomHeapProperties = nullptr)`
- L386 _function_ `inline ED3D12Access DetermineInitialBufferD3D12Access(D3D12_HEAP_TYPE HeapType, const D3D12_HEAP_PROPERTIES* pCustomHeapProperties = nullptr)`
- L399 _function_ `static inline uint64 GetTilesNeeded(uint32 Width, uint32 Height, uint32 Depth, const D3D12_TILE_SHAPE& Shape)`
- L406 _function_ `static void Get4KTileShape(D3D12_TILE_SHAPE* pTileShape, DXGI_FORMAT DXGIFormat, EPixelFormat UEFormat, D3D12_RESOURCE_DIMENSION Dimension, uint32 SampleCount)`
- L571 _macro_ `#define ASSERT_RESOURCE_STATES 0 // Disabled for now.`
- L580 _prototype_ `bool AssertResourceState(ID3D12CommandList* pCommandList, FD3D12Resource* pResource, const D3D12_RESOURCE_STATES& State, uint32 Subresource);`
- L581 _prototype_ `bool AssertResourceState(ID3D12CommandList* pCommandList, FD3D12Resource* pResource, const D3D12_RESOURCE_STATES& State, const FD3D12ViewSubset& ViewSubset);`
- L584 _function_ `FORCEINLINE_DEBUGGABLE D3D12_PRIMITIVE_TOPOLOGY_TYPE TranslatePrimitiveTopologyType(EPrimitiveTopologyType TopologyType)`
- L598 _function_ `FORCEINLINE_DEBUGGABLE D3D_PRIMITIVE_TOPOLOGY TranslatePrimitiveType(EPrimitiveType PrimitiveType)`
- L618 _function_ `FORCEINLINE_DEBUGGABLE D3D12_PRIMITIVE_TOPOLOGY_TYPE D3D12PrimitiveTypeToTopologyType(D3D_PRIMITIVE_TOPOLOGY PrimitiveType)`
- L652 _function_ `FORCEINLINE_DEBUGGABLE uint32 GetMaxMSAAQuality(uint32 SampleCount)` — @return 0xffffffff if not not supported
- L682 _function_ `FORCEINLINE_DEBUGGABLE bool CheckResourceStateCompatibility(D3D12_RESOURCE_STATES State, D3D12_RESOURCE_FLAGS Flags, FString& IncompatibilityReason)`
- L727 _function_ `inline bool D3D12DoesShaderFrequencySupportUAV(EShaderFrequency ShaderFrequency)`

### `Source/Runtime/D3D12RHI/Private/D3D12View.h` (Private)


#### struct `FD3D12DefaultViews`  
`struct FD3D12DefaultViews`  
_L54-63_
- L56 _public member_ `FD3D12OfflineDescriptor NullSRV;`
- L57 _public member_ `FD3D12OfflineDescriptor NullRTV;`
- L58 _public member_ `FD3D12OfflineDescriptor NullUAV;`
- L59 _public member_ `FD3D12OfflineDescriptor NullCBV;`
- L60 _public member_ `FD3D12OfflineDescriptor NullDSV;`
- L62 _public member_ `TRefCountPtr<class FD3D12SamplerState> DefaultSampler;`

#### struct `FD3D12ViewRange`  
`struct FD3D12ViewRange`  
_L66-93_
- desc: Holds the mip, array and plane range for a view, as well as the total number of these for the underlying resource.
- L68 _public prototype_ `FD3D12ViewRange() = default;`
- L69 _public prototype_ `FD3D12ViewRange(D3D12_CONSTANT_BUFFER_VIEW_DESC const& ViewDesc);`
- L70 _public prototype_ `FD3D12ViewRange(D3D12_SHADER_RESOURCE_VIEW_DESC const& ViewDesc);`
- L71 _public prototype_ `FD3D12ViewRange(D3D12_UNORDERED_ACCESS_VIEW_DESC const& ViewDesc);`
- L72 _public prototype_ `FD3D12ViewRange(D3D12_RENDER_TARGET_VIEW_DESC const& ViewDesc);`
- L73 _public prototype_ `FD3D12ViewRange(D3D12_DEPTH_STENCIL_VIEW_DESC const& ViewDesc);`
- L76 _public function_ `bool DoesNotOverlap(FD3D12ViewRange const& Other) const` — @todo remove this
- L84 _public function_ `uint8 MostDetailedMip() const` — @todo remove this
- L90 _public member_ `FRHIRange16 Array;` — The subresource range covered by the view.
- L91 _public member_ `FRHIRange8 Plane;`
- L92 _public member_ `FRHIRange8 Mip;`

#### struct `FD3D12ResourceLayout`  
`struct FD3D12ResourceLayout`  
_L95-107_
- L97 _public prototype_ `FD3D12ResourceLayout() = default;`
- L98 _public function_ `FD3D12ResourceLayout(FD3D12ResourceDesc const& ResourceDesc) : NumArraySlices(ResourceDesc.DepthOrArraySize) , NumPlanes (UE::DXGIUtilities::GetPlaneCount(ResourceDesc.Format)) , NumMips (ResourceDesc.MipLevels)`
- L104 _public member_ `uint16 NumArraySlices = 0;`
- L105 _public member_ `uint8 NumPlanes = 0;`
- L106 _public member_ `uint8 NumMips = 0;`

#### struct `FD3D12ViewSubset`  
`struct FD3D12ViewSubset`  
_L109-208_
- L111 _public prototype_ `FD3D12ViewSubset() = default;`
- L112 _public function_ `FD3D12ViewSubset(FD3D12ResourceLayout const& Layout, FD3D12ViewRange const& Range) : Layout(Layout) , Range (Range)`
- L117 _public function_ `bool IsWholeResource() const`
- L125 _public function_ `bool HasPlane(uint32 PlaneIndex) const`
- L130 _public function_ `FD3D12ViewSubset SelectPlane(uint32 PlaneIndex) const`
- L203 _public function_ `FIterator begin() const`
- L204 _public function_ `FIterator end () const`
- L206 _public member_ `FD3D12ResourceLayout Layout;`
- L207 _public member_ `FD3D12ViewRange Range;`

#### class `FD3D12ViewSubset::FIterator`  
`class FIterator final`  
_L148-201_
- desc: This iterator iterates over the subresources within a view subset. eg: for (uint32 SubresourceIndex : ViewSubset) { // Action for each subresource }
- L151 _public function_ `FIterator(FD3D12ViewSubset const& ViewSubset, uint8 MipSlice, uint16 ArraySlice, uint8 PlaneSlice) : MipMax (ViewSubset.Range.Mip.Num) , ArrayMax (ViewSubset.Range.Array.Num) , ArrayStride(ViewSubset.Layout.NumMips) , PlaneStride(ViewSubset.Layout.NumMips * (ViewSubset.Layout.NumArraySlices - ViewSubset.Range.Array.Num))`
- L166 _public function_ `FIterator& operator ++ ()`
- L185 _public function_ `uint32 operator * () const`
- L187 _public function_ `bool operator == (FIterator const& RHS) const`
- L188 _public function_ `bool operator != (FIterator const& RHS) const`
- L192 _private member_ `uint32 const MipMax;` — Constants
- L193 _private member_ `uint32 const ArrayMax;`
- L194 _private member_ `uint32 const ArrayStride;`
- L195 _private member_ `uint32 const PlaneStride;`
- L198 _private member_ `uint32 MipRangeStart;` — Counters
- L199 _private member_ `uint32 MipOffset = 0;`
- L200 _private member_ `uint32 ArrayOffset = 0;`

#### enum `ED3D12ViewType`  
`enum class ED3D12ViewType : uint8`  
_L211-218_
- desc: Enumeration of supported view types. Each view type must pass this up to their parent FD3D12View constructor.
- L213 _public enumerator_ `ShaderResource`
- L214 _public enumerator_ `ConstantBuffer`
- L215 _public enumerator_ `UnorderedAccess`
- L216 _public enumerator_ `RenderTarget`
- L217 _public enumerator_ `DepthStencil`

#### class `FD3D12View`  
`class FD3D12View : public FD3D12DeviceChild, public FD3D12ShaderResourceRenameListener`  
_L221-298_
- inherits: `FD3D12DeviceChild,FD3D12ShaderResourceRenameListener`
- desc: Manages descriptor allocations and view creation
- L223 _private typedef_ `typedef FD3D12OfflineDescriptor FD3D12DefaultViews::* FNullDescPtr;`
- L255 _public function_ `FD3D12Resource* GetResource () const`
- L256 _public function_ `FD3D12BaseShaderResource* GetShaderResource () const`
- L257 _public function_ `FD3D12ResourceLocation* GetResourceLocation() const`
- L258 _public function_ `TConstArrayView<FD3D12ResidencyHandle*> GetResidencyHandles() const`
- L259 _public function_ `FD3D12ViewSubset const& GetViewSubset () const`
- L260 _public function_ `FD3D12OfflineDescriptor GetOfflineCpuHandle() const`
- L263 _public function_ `FRHIDescriptorHandle GetBindlessHandle() const`
- L264 _public function_ `bool IsBindless () const`
- L267 _public function_ `constexpr bool IsBindless () const`
- L271 _protected prototype_ `FD3D12View() = delete;`
- L272 _protected prototype_ `FD3D12View(FD3D12Device* InDevice, ERHIDescriptorType InDescriptorType, ERHIDescriptorHeapType InHeapType, FD3D12View* FirstLinkedObject);`
- L273 _protected prototype_ `virtual ~FD3D12View();`
- L275 _protected prototype_ `virtual void UpdateDescriptor() = 0;`
- L277 _protected prototype_ `void UpdateResourceInfo(FResourceInfo const& InResource, FNullDescPtr NullDescriptor);`
- L278 _protected prototype_ `void CreateView(FResourceInfo const& InResource, FNullDescPtr NullDescriptor);`
- L279 _protected prototype_ `void UpdateView(FD3D12ContextArray const& Contexts, const FResourceInfo& InResource, FNullDescPtr NullDescriptor);`
- L281 _protected function_ `bool IsInitialized() const`
- L283 _protected prototype_ `void InitializeBindlessSlot();`
- L284 _protected prototype_ `void UpdateBindlessSlot(FD3D12ContextArray const& Contexts);`
- L286 _protected member_ `FResourceInfo ResourceInfo;`
- L287 _protected member_ `FD3D12ViewSubset ViewSubset;`
- L289 _protected member_ `FD3D12OfflineDescriptor OfflineCpuHandle;`
- L294 _protected member_ `FRHIDescriptorHandle BindlessHandle;` — BindlessHandle is shared across multi-GPU linked objects.  First linked object is responsible for destroying the handle. The D3D12View class doesn't have access to FD3D12LinkedAdapterObject::IsHeadLink(), so this separate bool is used.
- L295 _protected member_ `bool bFirstLinkedObject;`
- L297 _protected member_ `ERHIDescriptorHeapType const HeapType;`

#### enum `FD3D12View::EReason`  
`enum class EReason`  
_L226-230_
- L228 _public enumerator_ `InitialCreate`
- L229 _public enumerator_ `UpdateOrRename`

#### struct `FD3D12View::FResourceInfo`  
`struct FResourceInfo`  
_L232-253_
- L234 _public member_ `FD3D12BaseShaderResource* BaseResource = nullptr;`
- L235 _public member_ `FD3D12ResourceLocation* ResourceLocation = nullptr;`
- L236 _public member_ `FD3D12Resource* Resource = nullptr;`
- L238 _public prototype_ `FResourceInfo() = default;`
- L241 _public function_ `FResourceInfo(FD3D12BaseShaderResource* InBaseResource) : BaseResource (InBaseResource) , ResourceLocation(InBaseResource ? &InBaseResource->ResourceLocation : nullptr) , Resource (InBaseResource ? InBaseResource->GetResource() : nullptr)` — Constructor for renamable shader resources
- L248 _public function_ `FResourceInfo(FD3D12ResourceLocation* InResourceLocation) : BaseResource (nullptr) , ResourceLocation(InResourceLocation) , Resource (InResourceLocation ? InResourceLocation->GetResource() : nullptr)` — Constructor for manual views (does not automatically register for resource renames)

#### class `TD3D12View`  
`template <typename TParent, typename TDesc> class TD3D12View : public FD3D12View`  
_L301-334_
- inherits: `FD3D12View`
- L304 _protected member_ `TDesc D3DViewDesc;`
- L306 _protected function_ `TD3D12View(FD3D12Device* InDevice, ERHIDescriptorType InDescriptorType, ERHIDescriptorHeapType InHeapType, TD3D12View* FirstLinkedObject) : FD3D12View(InDevice, InDescriptorType, InHeapType, FirstLinkedObject)`
- L310 _protected function_ `void CreateView(FResourceInfo const& InResource, TDesc const& InD3DViewDesc)`
- L317 _protected function_ `void UpdateView(FD3D12ContextArray const& Contexts, FResourceInfo const& InResource, TDesc const& InD3DViewDesc)`
- L324 _protected function_ `virtual void ResourceRenamed(FD3D12ContextArray const& Contexts, FD3D12BaseShaderResource* InRenamedResource, FD3D12ResourceLocation* InNewResourceLocation) override`
- L333 _public function_ `TDesc const& GetD3DDesc() const`

#### class `FD3D12ConstantBufferView`  
`class FD3D12ConstantBufferView final : public TD3D12View<FD3D12ConstantBufferView, D3D12_CONSTANT_BUFFER_VIEW_DESC>`  
_L336-350_
- inherits: `TD3D12View<FD3D12ConstantBufferView,D3D12_CONSTANT_BUFFER_VIEW_DESC>`
- L339 _public member_ `static constexpr FD3D12OfflineDescriptor FD3D12DefaultViews::*Null { &FD3D12DefaultViews::NullCBV };`
- L341 _public prototype_ `FD3D12ConstantBufferView(FD3D12Device* InParent, FD3D12ConstantBufferView* FirstLinkedObject, ERHIDescriptorType InDescriptorType = ERHIDescriptorType::Invalid);`
- L342 _public prototype_ `void CreateView(const FResourceInfo& InResource, uint32 InOffset, uint32 InAlignedSize);`
- L343 _public prototype_ `void UpdateView(const FD3D12ContextArray& Contexts, const FResourceInfo& InResource, uint32 InOffset, uint32 InAlignedSize);`
- L346 _private prototype_ `virtual void ResourceRenamed(FD3D12ContextArray const& Contexts, FD3D12BaseShaderResource* InRenamedResource, FD3D12ResourceLocation* InNewResourceLocation) override;`
- L347 _private prototype_ `virtual void UpdateDescriptor() override;`
- L349 _private member_ `uint32 Offset;`

#### class `FD3D12ShaderResourceView`  
`class FD3D12ShaderResourceView : public TD3D12View<FD3D12ShaderResourceView, D3D12_SHADER_RESOURCE_VIEW_DESC>`  
_L352-385_
- inherits: `TD3D12View<FD3D12ShaderResourceView,D3D12_SHADER_RESOURCE_VIEW_DESC>`
- L355 _public member_ `static constexpr FD3D12OfflineDescriptor FD3D12DefaultViews::*Null { &FD3D12DefaultViews::NullSRV };`
- L364 _public prototype_ `FD3D12ShaderResourceView(FD3D12Device* InDevice, FD3D12ShaderResourceView* FirstLinkedObject, ERHIDescriptorType InDescriptorType, FD3D12RayTracingScene* InRayTracingScene = nullptr);`
- L365 _public prototype_ `void CreateView(FResourceInfo const& InResource, D3D12_SHADER_RESOURCE_VIEW_DESC const& InD3DViewDesc, EFlags InFlags);`
- L366 _public prototype_ `void UpdateView(FD3D12ContextArray const& Contexts, const FResourceInfo& InResource, const D3D12_SHADER_RESOURCE_VIEW_DESC& InD3DViewDesc, EFlags InFlags);`
- L368 _public function_ `bool GetSkipFastClearFinalize() const`
- L369 _public prototype_ `void UpdateMinLODClamp(FD3D12ContextArray const& Contexts, float MinLODClamp);`
- L371 _public function_ `FD3D12RayTracingScene* GetRayTracingScene() const`
- L374 _protected prototype_ `void UpdateResourceInfo(const FResourceInfo& InResource, const D3D12_SHADER_RESOURCE_VIEW_DESC& InD3DViewDesc, EFlags InFlags);`
- L375 _protected prototype_ `virtual void ResourceRenamed(FD3D12ContextArray const& Contexts, FD3D12BaseShaderResource* InRenamedResource, FD3D12ResourceLocation* InNewResourceLocation) override;`
- L376 _protected prototype_ `virtual void UpdateDescriptor() override;`
- L379 _protected member_ `uint64 OffsetInBytes = 0;` — Required for resource renaming
- L380 _protected member_ `uint32 StrideInBytes = 0;`
- L382 _protected member_ `EFlags Flags = EFlags::None;`
- L384 _protected member_ `FD3D12RayTracingScene* RayTracingScene = nullptr;`

#### enum `FD3D12ShaderResourceView::EFlags`  
`enum class EFlags : uint8`  
_L357-361_
- L359 _public enumerator_ `None = 0`
- L360 _public enumerator_ `SkipFastClearFinalize = 1 << 0`

#### class `FD3D12UnorderedAccessView`  
`class FD3D12UnorderedAccessView : public TD3D12View<FD3D12UnorderedAccessView, D3D12_UNORDERED_ACCESS_VIEW_DESC>`  
_L389-420_
- inherits: `TD3D12View<FD3D12UnorderedAccessView,D3D12_UNORDERED_ACCESS_VIEW_DESC>`
- L392 _public member_ `static constexpr FD3D12OfflineDescriptor FD3D12DefaultViews::*Null { &FD3D12DefaultViews::NullUAV };`
- L401 _public prototype_ `FD3D12UnorderedAccessView(FD3D12Device* InDevice, FD3D12UnorderedAccessView* FirstLinkedObject, ERHIDescriptorType InDescriptorType);`
- L402 _public prototype_ `void CreateView(FResourceInfo const& InResource, D3D12_UNORDERED_ACCESS_VIEW_DESC const& InD3DViewDesc, EFlags InFlags);`
- L403 _public prototype_ `void UpdateView(FD3D12ContextArray const& Contexts, const FResourceInfo& InResource, const D3D12_UNORDERED_ACCESS_VIEW_DESC& InD3DViewDesc, EFlags InFlags);`
- L405 _public function_ `FD3D12Resource* GetCounterResource() const`
- L411 _protected prototype_ `void UpdateResourceInfo(const FResourceInfo& InResource, const D3D12_UNORDERED_ACCESS_VIEW_DESC& InD3DViewDesc, EFlags InFlags);`
- L412 _protected prototype_ `virtual void ResourceRenamed(FD3D12ContextArray const& Contexts, FD3D12BaseShaderResource* InRenamedResource, FD3D12ResourceLocation* InNewResourceLocation) override;`
- L413 _protected prototype_ `virtual void UpdateDescriptor() override;`
- L415 _protected member_ `TRefCountPtr<FD3D12Resource> CounterResource;`
- L418 _protected member_ `uint64 OffsetInBytes = 0;` — Required for resource renaming
- L419 _protected member_ `uint32 StrideInBytes = 0;`

#### enum `FD3D12UnorderedAccessView::EFlags`  
`enum class EFlags : uint8`  
_L394-398_
- L396 _public enumerator_ `None = 0`
- L397 _public enumerator_ `NeedsCounter = 1 << 0`

#### class `FD3D12RenderTargetView`  
`class FD3D12RenderTargetView final : public TD3D12View<FD3D12RenderTargetView, D3D12_RENDER_TARGET_VIEW_DESC>`  
_L424-434_
- inherits: `TD3D12View<FD3D12RenderTargetView,D3D12_RENDER_TARGET_VIEW_DESC>`
- L427 _public member_ `static constexpr FD3D12OfflineDescriptor FD3D12DefaultViews::*Null { &FD3D12DefaultViews::NullRTV };`
- L429 _public prototype_ `FD3D12RenderTargetView(FD3D12Device* InDevice, FD3D12RenderTargetView* FirstLinkedObject);`
- L433 _private prototype_ `virtual void UpdateDescriptor() override;`

#### class `FD3D12DepthStencilView`  
`class FD3D12DepthStencilView final : public TD3D12View<FD3D12DepthStencilView, D3D12_DEPTH_STENCIL_VIEW_DESC>`  
_L436-452_
- inherits: `TD3D12View<FD3D12DepthStencilView,D3D12_DEPTH_STENCIL_VIEW_DESC>`
- L439 _public member_ `static constexpr FD3D12OfflineDescriptor FD3D12DefaultViews::*Null { &FD3D12DefaultViews::NullDSV };`
- L441 _public prototype_ `FD3D12DepthStencilView(FD3D12Device* InDevice, FD3D12DepthStencilView* FirstLinkedObject);`
- L444 _public function_ `bool HasDepth () const`
- L445 _public function_ `bool HasStencil() const`
- L447 _public function_ `FD3D12ViewSubset GetDepthOnlySubset () const`
- L448 _public function_ `FD3D12ViewSubset GetStencilOnlySubset() const`
- L451 _private prototype_ `virtual void UpdateDescriptor() override;`

#### struct `FD3D12DeferredInitView`  
`template <typename TParent> struct FD3D12DeferredInitView : public FD3D12LinkedAdapterObject<TParent>`  
_L455-480_
- inherits: `FD3D12LinkedAdapterObject<TParent>`
- L457 _public function_ `void CreateViews(FRHICommandListBase& RHICmdList)`

#### class `FD3D12ShaderResourceView_RHI`  
`class FD3D12ShaderResourceView_RHI : public FRHIShaderResourceView , public FD3D12ShaderResourceView , public FD3D12DeferredInitView<FD3D12ShaderResourceView_RHI>`  
_L483-502_
- inherits: `FRHIShaderResourceView,FD3D12ShaderResourceView,FD3D12DeferredInitView<FD3D12ShaderResourceView_RHI>`
- desc: Wrapper classes to expose the internal SRV/UAV types to the render as actual RHI resources.
- L489 _public prototype_ `FD3D12ShaderResourceView_RHI(FD3D12Device* InDevice, FRHIViewableResource* InResource, FRHIViewDesc const& InViewDesc, FD3D12ShaderResourceView_RHI* FirstLinkedObject);`
- L491 _public prototype_ `virtual void CreateView();`
- L492 _public prototype_ `virtual void UpdateView(FD3D12ContextArray const& Contexts);`
- L494 _public function_ `virtual void ResourceRenamed(FD3D12ContextArray const& Contexts, FD3D12BaseShaderResource*, FD3D12ResourceLocation*) override`
- L501 _public function_ `virtual FRHIDescriptorHandle GetBindlessHandle() const override`

#### class `FD3D12UnorderedAccessView_RHI`  
`class FD3D12UnorderedAccessView_RHI : public FRHIUnorderedAccessView , public FD3D12UnorderedAccessView , public FD3D12DeferredInitView<FD3D12UnorderedAccessView_RHI>`  
_L504-523_
- inherits: `FRHIUnorderedAccessView,FD3D12UnorderedAccessView,FD3D12DeferredInitView<FD3D12UnorderedAccessView_RHI>`
- L510 _public prototype_ `FD3D12UnorderedAccessView_RHI(FD3D12Device* InDevice, FRHIViewableResource* InResource, FRHIViewDesc const& InViewDesc, FD3D12UnorderedAccessView_RHI* FirstLinkedObject);`
- L512 _public prototype_ `virtual void CreateView();`
- L513 _public prototype_ `virtual void UpdateView(FD3D12ContextArray const& Contexts);`
- L515 _public function_ `virtual void ResourceRenamed(FD3D12ContextArray const& Contexts, FD3D12BaseShaderResource*, FD3D12ResourceLocation*) override`
- L522 _public function_ `virtual FRHIDescriptorHandle GetBindlessHandle() const override`

#### struct `TD3D12ResourceTraits`  
`template<> struct TD3D12ResourceTraits<FRHIShaderResourceView>`  
_L526-529_
- L528 _public typedef_ `typedef FD3D12ShaderResourceView_RHI TConcreteType;`
- L533 _public typedef_ `typedef FD3D12UnorderedAccessView_RHI TConcreteType;`

#### struct `TD3D12ResourceTraits`  
`template<> struct TD3D12ResourceTraits<FRHIUnorderedAccessView>`  
_L531-534_
- L528 _public typedef_ `typedef FD3D12ShaderResourceView_RHI TConcreteType;`
- L533 _public typedef_ `typedef FD3D12UnorderedAccessView_RHI TConcreteType;`

#### Free symbols / members of external scopes

- L17 _function_ `inline ERHIDescriptorType RHIDescriptorTypeFromD3D12ViewDesc(const D3D12_SHADER_RESOURCE_VIEW_DESC& ViewDesc)`
- L39 _function_ `inline ERHIDescriptorType RHIDescriptorTypeFromD3D12ViewDesc(const D3D12_UNORDERED_ACCESS_VIEW_DESC& ViewDesc)`
- L460 _function_ `` (scope `FD3D12DeferredInitView::CreateViews`)

### `Source/Runtime/D3D12RHI/Private/D3D12Viewport.h` (Private)


#### class `FD3D12Viewport`  
`class FD3D12Viewport : public FRHIViewport, public FD3D12AdapterChild`  
_L24-295_
- inherits: `FRHIViewport,FD3D12AdapterChild`
- L31 _public member_ `static FCriticalSection DXGIBackBufferLock;` — Lock viewport windows association and back buffer destruction because of possible crash inside DXGI factory during a call to MakeWindowAssociation Backbuffer release will wait on the call to MakeWindowAssociation while this will fail internally with 'The requested operation is not implemented.' in KernelBase.dll Reported & known problem in DXGI and will be fixed with future release but DXGI is not part of the Agility SDK so a code side fix is needed for now.
- L33 _public prototype_ `FD3D12Viewport(class FD3D12Adapter* InParent, HWND InWindowHandle, uint32 InSizeX, uint32 InSizeY, bool bInIsFullscreen, EPixelFormat InPixelFormat, uint32 InNumBackBuffers);`
- L35 _public prototype_ `void Init();`
- L37 _public prototype_ `~FD3D12Viewport();`
- L39 _public prototype_ `void Resize(uint32 InSizeX, uint32 InSizeY, bool bInIsFullscreen, EPixelFormat PreferredPixelFormat);`
- L46 _public prototype_ `void ConditionalResetSwapChain(bool bIgnoreFocus);` — If the swap chain has been invalidated by DXGI, resets the swap chain to the expected state; otherwise, does nothing. Called once/frame by the game thread on all viewports. @param bIgnoreFocus - Whether the reset should happen regardless of whether the window is focused.
- L51 _public prototype_ `bool SchedulePresent(class FD3D12CommandContextBase* BaseContext, const FRHIPresentArgs& InPresentArgs);` — Schedule Present from the RHI Thread to the Submission Thread Returns true if Present was correctly setup.
- L55 _public prototype_ `void PresentOnSubmissionThread(FD3D12PresentArgs& PresentArgs);` — Presents the swap chain on the Submission Thread
- L59 _public prototype_ `void WaitForLastPresent() const;` — Wait for the last Present to be called from the Submission Thread
- L63 _public member_ `FGraphEventRef PresentEvent;` — Signal that the Presents on the device has been completed and the backbuffer index has been update
- L68 _public prototype_ `bool EndRendering(class FD3D12CommandContextBase& Context, const FRHIPresentArgs& InPresentArgs);` — Presents the swap chain. Returns true if Present was done by Engine.
- L71 _public function_ `FIntPoint GetSizeXY() const` — Accessors.
- L76 _public function_ `FD3D12Texture* GetBackBuffer_RenderThread() const`
- L87 _public prototype_ `FD3D12Texture* GetBackBuffer_RHIThread(bool bWaitForLastPresent = true) const;`
- L89 _public function_ `FD3D12Texture* GetSDRBackBuffer_RHIThread(bool bWaitForLastPresent = true) const`
- L107 _public function_ `FRHITexture* GetOptionalSDRBackBuffer(FRHITexture* BackBufferTex) const override`
- L123 _public function_ `uint32 GetNextPresentGPUIndex() const`
- L130 _public prototype_ `virtual void WaitForFrameEventCompletion() override;`
- L131 _public prototype_ `virtual void IssueFrameEvent() override;`
- L134 _public prototype_ `virtual void* GetNativeSwapChain() const override;`
- L137 _public prototype_ `virtual void* GetNativeBackBufferTexture() const override;`
- L138 _public prototype_ `virtual void* GetNativeBackBufferRT() const override;`
- L140 _public prototype_ `virtual void SetCustomPresent(FRHICustomPresent* InCustomPresent) override;`
- L141 _public prototype_ `virtual FRHICustomPresent* GetCustomPresent() const override;`
- L143 _public function_ `virtual void* GetNativeWindow(void** AddParam = nullptr) const override`
- L145 _public function_ `uint32 GetNumBackBuffers() const`
- L147 _public function_ `inline const bool IsFullscreen() const`
- L150 _public prototype_ `bool CurrentOutputSupportsHDR() const;` — Query the swap chain's current connected output for HDR support.
- L153 _public prototype_ `void AdvanceExpectedBackBufferIndex_RenderThread(bool bPresent);` — Advance and get the next present GPU index
- L155 _public prototype_ `void OnResumeRendering();`
- L156 _public prototype_ `void OnSuspendRendering();`
- L158 _public function_ `bool PresentedLastFrame()`
- L161 _private prototype_ `bool IsPresentAllowed();`
- L162 _private prototype_ `bool CheckSwapChain();`
- L163 _private prototype_ `void SyncToSubmissionThread(FD3D12CommandContextBase& ContextBase);`
- L165 _private prototype_ `FString GetStateString();`
- L168 _private prototype_ `FD3D12Texture* CreateDummyBackBufferTextures(FD3D12Adapter* InAdapter, EPixelFormat InPixelFormat, uint32 InSizeX, uint32 InSizeY);`
- L174 _private prototype_ `void PresentChecked(int32 SyncInterval);` — Presents the swap chain checking the return result.
- L180 _private prototype_ `HRESULT PresentInternal(int32 SyncInterval);` — Presents the backbuffer to the viewport window. Returns the HRESULT for the call.
- L182 _private prototype_ `void ResizeInternal();`
- L183 _private prototype_ `void FinalDestroyInternal();`
- L184 _private prototype_ `void ClearPresentQueue();`
- L187 _private prototype_ `void InitializeBackBufferArrays();` — Determine how deep the swapchain should be
- L190 _private prototype_ `bool CheckHDRSupport();` — See if HDR can be enabled or not based on RHI support and current engine settings.
- L193 _private prototype_ `void EnableHDR();` — Enable HDR meta data transmission and set the necessary color space.
- L196 _private prototype_ `void ShutdownHDR();` — Disable HDR meta data transmission and set the necessary color space.
- L200 _private prototype_ `void EnsureColorSpace(DXGI_COLOR_SPACE_TYPE NewColorSpace);` — Ensure the correct color space is set on the swap chain
- L203 _private prototype_ `void EnsureColorSpace(EDisplayColorGamut DisplayGamut, EDisplayOutputFormat OutputDevice);` — Ensure the correct color space is set on the swap chain
- L206 _private function_ `void SetBackBufferIndex_RHIThread(uint32 Index)`
- L212 _private function_ `void SetBackBufferIndex_RenderThread(uint32 Index)`
- L219 _private member_ `const HWND WindowHandle;`
- L220 _private member_ `uint32 SizeX = 0;`
- L221 _private member_ `uint32 SizeY = 0;`
- L222 _private member_ `EPixelFormat PixelFormat;`
- L224 _private member_ `static constexpr EPixelFormat SDRPixelFormat = PF_B8G8R8A8;`
- L227 _private member_ `bool bIsFullscreen = false;`
- L228 _private member_ `bool bFullscreenLost = false;`
- L229 _private member_ `bool bIsValid = true;`
- L230 _private member_ `bool bAllowTearing = true;`
- L231 _private member_ `bool bNeedSwapChain = false;`
- L232 _private member_ `bool bLastFramePresented = true;`
- L233 _private member_ `bool bResizeInProgress = false;`
- L235 _private member_ `uint32 CheckedPresentFailureCounter = 0;`
- L238 _private member_ `TRefCountPtr<IDXGISwapChain1> SwapChain1;`
- L240 _private member_ `TRefCountPtr<IDXGISwapChain2> SwapChain2;`
- L243 _private member_ `TRefCountPtr<IDXGISwapChain3> SwapChain3;`
- L246 _private member_ `TRefCountPtr<IDXGISwapChain4> SwapChain4;`
- L250 _private member_ `DXGI_COLOR_SPACE_TYPE ColorSpace = DXGI_COLOR_SPACE_RGB_FULL_G22_NONE_P709;`
- L266 _private member_ `uint32 NumBackBuffers = 0;`
- L267 _private member_ `TArray<FBackBufferData, TInlineAllocator<D3D12RHI_DEFAULT_NUM_BACKBUFFER>> BackBuffers;`
- L271 _private member_ `TRefCountPtr<FD3D12Texture> DummyBackBuffer_RenderThread;` — Dummy back buffer texture which always references the current back buffer on the RHI thread
- L274 _private member_ `FBackBufferData* CurrentBackBuffer_RHIThread = nullptr;`
- L275 _private member_ `FBackBufferData* CurrentBackBuffer_RenderThread = nullptr;`
- L277 _private member_ `uint32 CurrentBackBufferIndex_RHIThread = 0;`
- L278 _private member_ `uint32 ExpectedBackBufferIndex_RenderThread = 0;`
- L279 _private member_ `EDisplayColorGamut DisplayColorGamut = EDisplayColorGamut::sRGB_D65;`
- L280 _private member_ `EDisplayOutputFormat DisplayOutputFormat = EDisplayOutputFormat::SDR_sRGB;`
- L283 _private member_ `TArray<FD3D12SyncPointRef> FrameSyncPoints;` — A fence value used to track the GPU's progress.
- L285 _private member_ `FCustomPresentRHIRef CustomPresent;`
- L289 _private member_ `int32 BackbufferMultiGPUBinding = 0;` — Where INDEX_NONE cycles through the GPU, otherwise the GPU index.
- L292 _private member_ `mutable FCriticalSection ExpectedBackBufferIndexLock;` — Can very rarely be modified on the RHI thread as well if present is skipped

#### struct `FD3D12Viewport::FBackBufferData`  
`struct FBackBufferData`  
_L254-264_
- L256 _public member_ `TRefCountPtr<FD3D12Texture> Texture;`
- L259 _public member_ `TRefCountPtr<FD3D12Texture> TextureSDR;` — When HDR is enabled, SDR backbuffers may be required on some architectures for game DVR or broadcasting
- L262 _public member_ `uint32 GPUIndex = 0;`

#### struct `TD3D12ResourceTraits`  
`template<> struct TD3D12ResourceTraits<FRHIViewport>`  
_L298-301_
- L300 _public typedef_ `typedef FD3D12Viewport TConcreteType;`

#### Free symbols / members of external scopes

- L22 _typedef_ `using FD3D12SyncPointRef = TRefCountPtr<FD3D12SyncPoint>;`

### `Source/Runtime/D3D12RHI/Private/D3D12WorkGraph.h` (Private)


#### struct `FD3D12WorkGraphPipelineState`  
`struct FD3D12WorkGraphPipelineState : public FRHIWorkGraphPipelineState`  
_L12-42_
- inherits: `FRHIWorkGraphPipelineState`
- L17 _public prototype_ `FD3D12WorkGraphPipelineState(FD3D12Device* Device, const FWorkGraphPipelineStateInitializer& Initializer);`
- L19 _public member_ `FD3D12Device* Device;`
- L22 _public member_ `TRefCountPtr<ID3D12RootSignature> RootSignature;`
- L23 _public member_ `TRefCountPtr<ID3D12StateObject> StateObject;`
- L25 _public member_ `D3D12_PROGRAM_IDENTIFIER ProgramIdentifier = {};`
- L26 _public member_ `D3D12_GPU_VIRTUAL_ADDRESS_RANGE BackingMemoryAddressRange = {};`
- L28 _public member_ `uint32 RootArgStrideInBytes = 0;`
- L29 _public member_ `uint32 MaxRootArgOffset = 0;`
- L30 _public member_ `TArray<uint32> RootArgOffsets;`
- L32 _public member_ `TMap<FString, uint32> NodeCountPerName;`
- L34 _public member_ `bool bInitialized = false;`
- L36 _public member_ `D3D12ResourceFrameCounter FrameCounter;`
- L39 _public member_ `TArray<TRefCountPtr<FRHIShader>> Shaders;`

### `Source/Runtime/D3D12RHI/Private/ID3D12Barriers.h` (Private)


#### enum `ED3D12LogBarriersFlags`  
`enum ED3D12LogBarriersFlags : decltype(GD3D12LogBarriers)`  
_L61-66_
- L63 _public enumerator_ `D3D12LogBarriersNever = 0`
- L64 _public enumerator_ `D3D12LogBarriersWhenBatched = 1u << 0`
- L65 _public enumerator_ `D3D12LogBarriersWhenFlushed = 1u << 1`

#### class `ID3D12BarriersForAdapter`  
`class ID3D12BarriersForAdapter`  
_L82-127_
- L85 _public prototype_ `virtual ~ID3D12BarriersForAdapter() = default;`
- L87 _public prototype_ `virtual void ConfigureDevice( ID3D12Device* Device, bool InWithD3DDebug) const = 0;`
- L91 _public prototype_ `virtual uint64 GetTransitionDataSizeBytes() const = 0;`
- L92 _public prototype_ `virtual uint64 GetTransitionDataAlignmentBytes() const = 0;`
- L94 _public prototype_ `virtual void CreateTransition( FRHITransition* Transition, const FRHITransitionCreateInfo& CreateInfo) const = 0;`
- L98 _public prototype_ `virtual void ReleaseTransition( FRHITransition* Transition) const = 0;`
- L101 _public prototype_ `virtual HRESULT CreateCommittedResource( FD3D12Adapter& Adapter, const D3D12_HEAP_PROPERTIES& InHeapProps, D3D12_HEAP_FLAGS InHeapFlags, const FD3D12ResourceDesc& InDesc, ED3D12Access InInitialD3D12Access, const D3D12_CLEAR_VALUE* InClearValue, TRefCountPtr<ID3D12Resource>& OutResource) const = 0;`
- L110 _public prototype_ `virtual HRESULT CreateReservedResource( FD3D12Adapter& Adapter, const FD3D12ResourceDesc& InDesc, ED3D12Access InInitialD3D12Access, const D3D12_CLEAR_VALUE* InClearValue, TRefCountPtr<ID3D12Resource>& OutResource) const = 0;`
- L117 _public prototype_ `virtual HRESULT CreatePlacedResource( FD3D12Adapter& Adapter, ID3D12Heap* Heap, uint64 InHeapOffset, const FD3D12ResourceDesc& InDesc, ED3D12Access InInitialD3D12Access, const D3D12_CLEAR_VALUE* InClearValue, TRefCountPtr<ID3D12Resource>& OutResource) const = 0;`
- L126 _public prototype_ `virtual const TCHAR* GetImplementationName() const = 0;`

#### class `ID3D12BarriersForContext`  
`class ID3D12BarriersForContext`  
_L129-159_
- L132 _public prototype_ `virtual ~ID3D12BarriersForContext() = default;`
- L134 _public prototype_ `virtual void BeginTransitions( FD3D12CommandContext& Context, TArrayView<const FRHITransition*> Transitions) = 0;`
- L138 _public prototype_ `virtual void EndTransitions( FD3D12CommandContext& Context, TArrayView<const FRHITransition*> Transitions) = 0;`
- L142 _public prototype_ `virtual void AddGlobalBarrier( FD3D12ContextCommon& Context, ED3D12Access D3D12AccessBefore, ED3D12Access D3D12AccessAfter) = 0;`
- L147 _public prototype_ `virtual void AddBarrier( FD3D12ContextCommon& Context, const FD3D12Resource* pResource, ED3D12Access D3D12AccessBefore, ED3D12Access D3D12AccessAfter, uint32 Subresource) = 0;`
- L154 _public prototype_ `virtual void FlushIntoCommandList( FD3D12CommandList& CommandList, FD3D12QueryAllocator& TimestampAllocator) = 0;`
- L158 _public prototype_ `virtual int32 GetNumPendingBarriers() const = 0;`

#### Free symbols / members of external scopes

- L31 _variable_ `inline int32 GD3D12AllowDiscardResources = 1;`
- L32 _variable_ `inline FAutoConsoleVariableRef CVarD3D12AllowDiscardResources( TEXT("d3d12.AllowDiscardResources"), GD3D12AllowDiscardResources, TEXT("Whether to call DiscardResources after transient aliasing acquire. This is not needed on some platforms if newly acquired resources are cleared before use."), ECVF_RenderThreadSafe);`
- L38 _variable_ `inline int32 GD3D12DisableDiscardOfDepthResources = 0;`
- L39 _variable_ `inline FAutoConsoleVariableRef CVarDisableDiscardOfDepthResources( TEXT("d3d12.DisableDiscardOfDepthResources"), GD3D12DisableDiscardOfDepthResources, TEXT("Whet`
- L44 _variable_ `inline int32 GD3D12BatchResourceBarriers = 1;`
- L45 _variable_ `inline FAutoConsoleVariableRef CVarD3D12BatchResourceBarriers( TEXT("d3d12.BatchResourceBarriers"), GD3D12BatchResourceBarriers, TEXT("Whet`
- L51 _variable_ `inline int32 GD3D12LogBarriers = 0;`
- L52 _variable_ `inline FAutoConsoleVariableRef CVarD3D12LogBarriers( TEXT("d3d12.LogBarriers"), GD3D12LogBarriers, TEXT("Whether to log barriers. Use d3d12.LogBarriersResourceFilter to filter by resource name.\n") TEXT("0 - No logging\n") TEXT("1 - Log when batched\n") TEXT("2 - Log when flushed\n") TEXT("3 -`
- L70 _variable_ `inline FString GD3D12LogBarriersResourceFilter = "";` — Do not access the CVar directly as that will create a race. Instead use this variable for which updates are sync'd via the callback
- L71 _variable_ `inline FAutoConsoleVariable CVarD3D12LogBarriersResourceFilter( TEXT("d3d12.LogBarriersResourceFilter"), TEXT(""), TEXT("Which resources to log barriers for. Set to empty to log everything."), FConsoleVariableDelegate::CreateStatic( [](IConsoleVariable* CVarFilter) { GD3D12LogBarriersResourceFilter = CVarFilter->GetString(); }));`
- L77 _function_ ``

### `Source/Runtime/D3D12RHI/Private/Windows/WindowsD3D12Adapter.h` (Private)


#### class `FWindowsD3D12Adapter`  
`class FWindowsD3D12Adapter : public FD3D12Adapter`  
_L7-19_
- inherits: `FD3D12Adapter`
- L11 _public function_ `FWindowsD3D12Adapter(FD3D12AdapterDesc& InDesc) : FD3D12Adapter(InDesc)`
- L17 _protected prototype_ `virtual void CreateCommandSignatures() final override;`

### `Source/Runtime/D3D12RHI/Private/Windows/WindowsD3D12BarriersFactory.h` (Private)


#### Free symbols / members of external scopes

- L10 _typedef_ `using FD3D12BarriersFactory = TD3D12BarriersFactory< #if D3D12RHI_SUPPORTS_ENHANCED_BARRIERS TD3D12BarriersFactoryEntry< ED3D12BarrierImplementationType::Enhanced, FD3D12EnhancedBarriersForAdapter, FD3D12EnhancedBarriersForContext>, #endif #if D3D12RHI_SUPPORTS_LEGACY_BARRIERS TD3D12BarriersFactoryEntry< ED3D12BarrierImplementationType::Legacy, FD3D12LegacyBarriersForAdapter, FD3D12LegacyBarriersForContext>, #endif FNullD3D12BarriersFactoryEntry >;`

### `Source/Runtime/D3D12RHI/Private/Windows/WindowsD3D12BindlessDescriptors.h` (Private)


#### Free symbols / members of external scopes

- L5 _macro_ `#define D3D12RHI_CUSTOM_BINDLESS_RESOURCE_MANAGER 0`
- L6 _macro_ `#define D3D12RHI_BINDLESS_RESOURCE_MANAGER_SUPPORTS_RESIZING 1`

### `Source/Runtime/D3D12RHI/Private/Windows/WindowsD3D12DiskCache.h` (Private)


#### class `FDiskCacheInterface`  
`class FDiskCacheInterface`  
_L13-103_
- L17 _private member_ `static const uint32 mCurrentHeaderVersion = 11;` — Increment this if changes are made to the disk caches so stale caches get updated correctly
- L26 _private member_ `FString mFileName;`
- L27 _private member_ `uint8* mFileStart;`
- L28 _private member_ `HANDLE mFile;`
- L29 _private member_ `HANDLE mMemoryMap;`
- L30 _private member_ `HANDLE mMapAddress;`
- L31 _private member_ `SIZE_T mCurrentFileMapSize;`
- L32 _private member_ `SIZE_T mCurrentOffset;`
- L33 _private member_ `bool mCacheExists;`
- L34 _private member_ `bool mInErrorState;`
- L35 _private member_ `bool mEnableDiskCache;`
- L36 _private member_ `FDiskCacheHeader mHeader;`
- L42 _private member_ `TArray<void*> mBackedMemory;` — There is the potential for the file mapping to grow in that case all of the pointers will be invalid. Back some of the pointers we might read again (i.e. shade byte code for PSO mapping) in persitent system memory.
- L44 _private member_ `static const SIZE_T mFileGrowSize = (1024 * 1024);` — 1 megabyte;
- L46 _private prototype_ `void GrowMapping(SIZE_T size, bool firstrun);`
- L55 _public prototype_ `bool AppendData(const void* pData, size_t size);`
- L56 _public prototype_ `bool SetPointerAndAdvanceFilePosition(void** pDest, size_t size, bool backWithSystemMemory = false);`
- L57 _public prototype_ `void Reset(RESET_TYPE type);`
- L58 _public prototype_ `void Init(FString &filename, bool bEnable = true);`
- L59 _public prototype_ `void Close(uint32 numberOfPSOs);`
- L60 _public prototype_ `void Flush(uint32 numberOfPSOs);`
- L61 _public prototype_ `void ClearDiskCache();`
- L63 _public function_ `void ClearAndReinitialize()`
- L73 _public function_ `uint32 GetNumPSOs() const`
- L78 _public function_ `uint32 GetSizeInBytes() const`
- L83 _public function_ `FORCEINLINE_DEBUGGABLE bool IsInErrorState() const`
- L88 _public function_ `SIZE_T GetCurrentOffset() const`
- L90 _public prototype_ `void* GetDataAt(SIZE_T Offset) const;`
- L91 _public prototype_ `void* GetDataAtStart() const;`
- L93 _public function_ `~FDiskCacheInterface()`

#### struct `FDiskCacheInterface::FDiskCacheHeader`  
`struct FDiskCacheHeader`  
_L18-23_
- L20 _public member_ `uint32 mHeaderVersion;`
- L21 _public member_ `uint32 mNumPsos;`
- L22 _public member_ `size_t mSizeInBytes;` — The number of bytes after the header

#### enum `FDiskCacheInterface::RESET_TYPE`  
`enum RESET_TYPE`  
_L49-53_
- L51 _public enumerator_ `RESET_TO_FIRST_OBJECT`
- L52 _public enumerator_ `RESET_TO_AFTER_LAST_OBJECT`

#### Free symbols / members of external scopes

- L11 _macro_ `#define IL_MAX_SEMANTIC_NAME 255`

### `Source/Runtime/D3D12RHI/Private/Windows/WindowsD3D12PipelineState.h` (Private)


#### struct `FD3D12_GRAPHICS_PIPELINE_STATE_STREAM`  
`struct FD3D12_GRAPHICS_PIPELINE_STATE_STREAM`  
_L14-39_
- desc: Graphics pipeline stream struct that represents the latest version of PSO subobjects currently used by the RHI.
- L20 _public member_ `CD3DX12_PIPELINE_STATE_STREAM_NODE_MASK NodeMask;` — CD3DX12_PIPELINE_STATE_STREAM_FLAGS Flags;
- L21 _public member_ `CD3DX12_PIPELINE_STATE_STREAM_ROOT_SIGNATURE pRootSignature;`
- L22 _public member_ `CD3DX12_PIPELINE_STATE_STREAM_INPUT_LAYOUT InputLayout;`
- L23 _public member_ `CD3DX12_PIPELINE_STATE_STREAM_IB_STRIP_CUT_VALUE IBStripCutValue;`
- L24 _public member_ `CD3DX12_PIPELINE_STATE_STREAM_PRIMITIVE_TOPOLOGY PrimitiveTopologyType;`
- L25 _public member_ `CD3DX12_PIPELINE_STATE_STREAM_VS VS;`
- L26 _public member_ `CD3DX12_PIPELINE_STATE_STREAM_GS GS;`
- L27 _public member_ `CD3DX12_PIPELINE_STATE_STREAM_HS HS;`
- L28 _public member_ `CD3DX12_PIPELINE_STATE_STREAM_DS DS;`
- L29 _public member_ `CD3DX12_PIPELINE_STATE_STREAM_PS PS;`
- L30 _public member_ `CD3DX12_PIPELINE_STATE_STREAM_BLEND_DESC BlendState;`
- L31 _public member_ `CD3DX12_PIPELINE_STATE_STREAM_DEPTH_STENCIL1 DepthStencilState;`
- L32 _public member_ `CD3DX12_PIPELINE_STATE_STREAM_DEPTH_STENCIL_FORMAT DSVFormat;`
- L33 _public member_ `CD3DX12_PIPELINE_STATE_STREAM_RASTERIZER RasterizerState;`
- L34 _public member_ `CD3DX12_PIPELINE_STATE_STREAM_RENDER_TARGET_FORMATS RTVFormats;`
- L35 _public member_ `CD3DX12_PIPELINE_STATE_STREAM_SAMPLE_DESC SampleDesc;`
- L36 _public member_ `CD3DX12_PIPELINE_STATE_STREAM_SAMPLE_MASK SampleMask;`
- L37 _public member_ `CD3DX12_PIPELINE_STATE_STREAM_CACHED_PSO CachedPSO;`

#### struct `FD3D12_MESH_PIPELINE_STATE_STREAM`  
`struct FD3D12_MESH_PIPELINE_STATE_STREAM`  
_L42-63_
- L48 _public member_ `CD3DX12_PIPELINE_STATE_STREAM_NODE_MASK NodeMask;` — CD3DX12_PIPELINE_STATE_STREAM_FLAGS Flags;
- L49 _public member_ `CD3DX12_PIPELINE_STATE_STREAM_ROOT_SIGNATURE pRootSignature;`
- L50 _public member_ `CD3DX12_PIPELINE_STATE_STREAM_PRIMITIVE_TOPOLOGY PrimitiveTopologyType;`
- L51 _public member_ `CD3DX12_PIPELINE_STATE_STREAM_MS MS;`
- L52 _public member_ `CD3DX12_PIPELINE_STATE_STREAM_AS AS;`
- L53 _public member_ `CD3DX12_PIPELINE_STATE_STREAM_PS PS;`
- L54 _public member_ `CD3DX12_PIPELINE_STATE_STREAM_BLEND_DESC BlendState;`
- L55 _public member_ `CD3DX12_PIPELINE_STATE_STREAM_DEPTH_STENCIL1 DepthStencilState;`
- L56 _public member_ `CD3DX12_PIPELINE_STATE_STREAM_DEPTH_STENCIL_FORMAT DSVFormat;`
- L57 _public member_ `CD3DX12_PIPELINE_STATE_STREAM_RASTERIZER RasterizerState;`
- L58 _public member_ `CD3DX12_PIPELINE_STATE_STREAM_RENDER_TARGET_FORMATS RTVFormats;`
- L59 _public member_ `CD3DX12_PIPELINE_STATE_STREAM_SAMPLE_DESC SampleDesc;`
- L60 _public member_ `CD3DX12_PIPELINE_STATE_STREAM_SAMPLE_MASK SampleMask;`
- L61 _public member_ `CD3DX12_PIPELINE_STATE_STREAM_CACHED_PSO CachedPSO;`

#### struct `FD3D12_COMPUTE_PIPELINE_STATE_STREAM`  
`struct FD3D12_COMPUTE_PIPELINE_STATE_STREAM`  
_L67-77_
- desc: Compute pipeline stream struct that represents the latest version of PSO subobjects currently used by the RHI.
- L73 _public member_ `CD3DX12_PIPELINE_STATE_STREAM_NODE_MASK NodeMask;` — CD3DX12_PIPELINE_STATE_STREAM_FLAGS Flags;
- L74 _public member_ `CD3DX12_PIPELINE_STATE_STREAM_ROOT_SIGNATURE pRootSignature;`
- L75 _public member_ `CD3DX12_PIPELINE_STATE_STREAM_CS CS;`
- L76 _public member_ `CD3DX12_PIPELINE_STATE_STREAM_CACHED_PSO CachedPSO;`

#### struct `ComputePipelineCreationArgs_POD`  
`struct ComputePipelineCreationArgs_POD`  
_L86-100_
- L88 _public member_ `FD3D12ComputePipelineStateDesc Desc;`
- L89 _public member_ `ID3D12PipelineLibrary* Library;`
- L91 _public function_ `void Init(const ComputePipelineCreationArgs_POD& InArgs)`
- L99 _public prototype_ `void Destroy();`

#### struct `GraphicsPipelineCreationArgs_POD`  
`struct GraphicsPipelineCreationArgs_POD`  
_L102-120_
- L104 _public member_ `FD3D12LowLevelGraphicsPipelineStateDesc Desc;`
- L105 _public member_ `ID3D12PipelineLibrary* Library;`
- L107 _public function_ `void Init(const GraphicsPipelineCreationArgs_POD& InArgs)`
- L119 _public prototype_ `void Destroy();`

#### struct `ComputePipelineCreationArgs`  
`struct ComputePipelineCreationArgs`  
_L122-135_
- L124 _public function_ `ComputePipelineCreationArgs(const FD3D12ComputePipelineStateDesc* InDesc, ID3D12PipelineLibrary* InLibrary)`
- L130 _public function_ `ComputePipelineCreationArgs(const ComputePipelineCreationArgs& InArgs) : ComputePipelineCreationArgs(&InArgs.Args.Desc, InArgs.Args.Library)`
- L134 _public member_ `ComputePipelineCreationArgs_POD Args;`

#### struct `GraphicsPipelineCreationArgs`  
`struct GraphicsPipelineCreationArgs`  
_L137-150_
- L139 _public function_ `GraphicsPipelineCreationArgs(const FD3D12LowLevelGraphicsPipelineStateDesc* InDesc, ID3D12PipelineLibrary* InLibrary)`
- L145 _public function_ `GraphicsPipelineCreationArgs(const GraphicsPipelineCreationArgs& InArgs) : GraphicsPipelineCreationArgs(&InArgs.Args.Desc, InArgs.Args.Library)`
- L149 _public member_ `GraphicsPipelineCreationArgs_POD Args;`

#### class `FD3D12PipelineStateCache`  
`class FD3D12PipelineStateCache : public FD3D12PipelineStateCacheBase`  
_L152-220_
- inherits: `FD3D12PipelineStateCacheBase`
- L155 _private member_ `FDiskCacheInterface DiskBinaryCache;`
- L156 _private member_ `TRefCountPtr<ID3D12PipelineLibrary> PipelineLibrary;`
- L157 _private member_ `bool bUseAPILibaries;`
- L159 _private prototype_ `void WriteOutShaderBlob(PSO_CACHE_TYPE Cache, ID3D12PipelineState* APIPso);`
- L162 _private function_ `template<typename PipelineStateDescType> void ReadBackShaderBlob(PipelineStateDescType& Desc, PSO_CACHE_TYPE Cache)`
- L186 _private function_ `bool UsePipelineLibrary() const`
- L191 _private function_ `bool UseCachedBlobs() const`
- L200 _protected prototype_ `void OnPSOCreated(FD3D12PipelineState* PipelineState, const FD3D12LowLevelGraphicsPipelineStateDesc& Desc) final override;`
- L201 _protected prototype_ `void OnPSOCreated(FD3D12PipelineState* PipelineState, const FD3D12ComputePipelineStateDesc& Desc) final override;`
- L203 _protected prototype_ `void AddToDiskCache(const FD3D12LowLevelGraphicsPipelineStateDesc& Desc, FD3D12PipelineState* PipelineState);`
- L204 _protected prototype_ `void AddToDiskCache(const FD3D12ComputePipelineStateDesc& Desc, FD3D12PipelineState* PipelineState);`
- L211 _public prototype_ `void RebuildFromDiskCache();`
- L213 _public prototype_ `void Close();`
- L215 _public prototype_ `void Init(FString &GraphicsCacheFilename, FString &ComputeCacheFilename, FString &DriverBlobFilename);`
- L216 _public prototype_ `bool IsInErrorState() const;`
- L218 _public prototype_ `FD3D12PipelineStateCache(FD3D12Adapter* InParent);`
- L219 _public prototype_ `virtual ~FD3D12PipelineStateCache();`

#### Free symbols / members of external scopes

- L84 _prototype_ `void SaveByteCode(D3D12_SHADER_BYTECODE& ByteCode);`

### `Source/Runtime/D3D12RHI/Private/Windows/WindowsD3D12RHIDefinitions.h` (Private)


#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_D3D12_SDK_VERSION (D3D12_SDK_VERSION)`
- L9 _macro_ `#define D3D12RHI_DEFAULT_NUM_BACKBUFFER 3`
- L12 _typedef_ `typedef ID3D12GraphicsCommandList ID3D12CopyCommandList;` — Windows uses the graphics command list interface for the copy queue.
- L14 _macro_ `#define D3D12RHI_PLATFORM_COPY_COMMAND_LIST_TYPE D3D12_COMMAND_LIST_TYPE_COPY`
- L16 _macro_ `#define FD3D12_DESCRIPTOR_HEAP_TYPE_SAMPLER D3D12_DESCRIPTOR_HEAP_TYPE_SAMPLER`
- L19 _macro_ `#define D3D12RHI_PLATFORM_USES_TIMESTAMP_QUERIES 1` — Windows uses standard D3D12 query heaps for timestamps
- L21 _macro_ `#define D3D12RHI_RESOURCE_FLAG_ALLOW_INDIRECT_BUFFER D3D12_RESOURCE_FLAG_NONE`
- L22 _macro_ `#define D3D12RHI_HEAP_FLAG_ALLOW_INDIRECT_BUFFERS D3D12_HEAP_FLAG_NONE`
- L24 _macro_ `#define FD3D12_HEAP_FLAG_CREATE_NOT_ZEROED D3D12_HEAP_FLAG_CREATE_NOT_ZEROED`
- L26 _macro_ `#define D3D12RHI_NEEDS_VENDOR_EXTENSIONS 1`
- L27 _macro_ `#define D3D12RHI_NEEDS_SHADER_FEATURE_CHECKS 1`
- L29 _macro_ `#define USE_STATIC_ROOT_SIGNATURE 0`
- L30 _macro_ `#define D3D12RHI_USE_CONSTANT_BUFFER_VIEWS 0`
- L31 _macro_ `#define D3D12RHI_USE_DUMMY_BACKBUFFER 1`
- L32 _macro_ `#define D3D12RHI_USE_SDR_BACKBUFFER 0`
- L33 _macro_ `#define D3D12RHI_SUPPORTS_UAV_BACKBUFFER 0`
- L34 _macro_ `#define D3D12RHI_USE_DXGI_COLOR_SPACE 1`
- L37 _macro_ `#define D3D12RHI_ENABLE_PIPELINE_STATISTICS (1 && STATS)` — Only enable pipeline statistics if we've got the stats system enabled to display them
- L39 _macro_ `#define D3D12RHI_ALLOW_ENHANCED_BARRIERS 1`
- L40 _macro_ `#define D3D12RHI_ALLOW_LEGACY_BARRIERS 1`
- L42 _macro_ `#define D3D12RHI_HAS_LAYOUT_VIDEO_QUEUE_COMMON (UE_D3D12_SDK_VERSION < 618)`
- L43 _macro_ `#define D3D12RHI_HAS_LAYOUT_DIRECT_QUEUE_GENERIC_READ_COMPUTE_QUEUE_ACCESSIBLE (UE_D3D12_SDK_VERSION >= 618)`
- L44 _macro_ `#define D3D12RHI_COMMON_AND_PRESENT_ARE_DISTINCT 0`
- L47 _macro_ `#define D3D12RHI_SUPPORTS_ALIASED_RHI_RESOURCES 1` — Needed for XR
- L49 _macro_ `#define USE_BUFFER_POOL_ALLOCATOR 1`
- L50 _macro_ `#define USE_TEXTURE_POOL_ALLOCATOR 1`

### `Source/Runtime/D3D12RHI/Private/Windows/WindowsD3D12Submission.h` (Private)


#### struct `FD3D12Payload`  
`struct FD3D12Payload final : public FD3D12PayloadBase`  
_L14-21_
- inherits: `FD3D12PayloadBase`
- desc: Standard Windows implementation, used to mark the type as 'final'.
- L16 _public function_ `FD3D12Payload(FD3D12Queue& Queue) : FD3D12PayloadBase(Queue)`

### `Source/Runtime/D3D12RHI/Public/D3D12RHI.h` (Public)


#### Free symbols / members of external scopes

- L17 _macro_ `#define MAX_SRVS 64 // Cannot be set higher than 64 due to 64b Cache.BoundMask logic` — Note: We do not need to worry about these counts exceeding resource binding tiers 1 & 2 due to 2 reasons: 1) On PC the actual counts used to build the root signature are derived from the shader and the shader compiler profile required for a desired feature level will enforce the proper limits. 2) All platforms currently using the global root signature support resource binding tier 3, these counts are well within the limits of tier 3. More info here: https://learn.microsoft.com/en-us/windows/win32/direct3d12/hardware-support, https://en.wikipedia.org/wiki/Feature_levels_in_Direct3D
- L18 _macro_ `#define MAX_SAMPLERS 32`
- L19 _macro_ `#define MAX_UAVS 16`
- L20 _macro_ `#define MAX_CBS 16`
- L23 _macro_ `#define WITH_PIX_EVENT_RUNTIME 0`
- L27 _macro_ `#define D3D12RHI_PLATFORM_HAS_UNIFIED_MEMORY 0`
- L28 _macro_ `#define D3D12RHI_PLATFORM_LOW_LEVEL_RES_TRACK 0`
- L29 _macro_ `#define ENABLE_RESIDENCY_MANAGEMENT 1`
- L30 _macro_ `#define PIPELINE_STATE_FILE_LOCATION FPaths::ProjectSavedDir()`
- L31 _macro_ `#define USE_PIX WITH_PIX_EVENT_RUNTIME`
- L32 _macro_ `#define D3D12RHI_SUPPORTS_WIN_PIX USE_PIX`
- L34 _macro_ `#define FD3D12_TEXTURE_DATA_PITCH_ALIGNMENT D3D12_TEXTURE_DATA_PITCH_ALIGNMENT`

### `Source/Runtime/D3D12RHI/Public/D3D12RootSignatureDefinitions.h` (Public)


#### enum `D3D12ShaderUtils::ERootSignatureRangeType`  
`enum class ERootSignatureRangeType`  
_L33-39_
- L35 _public enumerator_ `CBV`
- L36 _public enumerator_ `SRV`
- L37 _public enumerator_ `UAV`
- L38 _public enumerator_ `Sampler`

#### enum `D3D12ShaderUtils::ERootSignatureVisibility`  
`enum class ERootSignatureVisibility`  
_L41-49_
- L43 _public enumerator_ `Vertex`
- L44 _public enumerator_ `Pixel`
- L45 _public enumerator_ `Geometry`
- L46 _public enumerator_ `Mesh`
- L47 _public enumerator_ `Amplification`
- L48 _public enumerator_ `All`

#### struct `D3D12ShaderUtils::FRootSignatureCreator`  
`struct FRootSignatureCreator`  
_L175-238_
- desc: Simple base class to help write out a root signature (subclass to generate either to a binary struct or a #define)
- L177 _public member_ `EShaderBindingLayoutFlags Flags = EShaderBindingLayoutFlags::None;`
- L178 _public member_ `uint32 RegisterSpace = 0;`
- L180 _public prototype_ `virtual ~FRootSignatureCreator() = default;`
- L182 _public prototype_ `virtual void AddRootFlag(D3D12_ROOT_SIGNATURE_FLAGS Flag) = 0;`
- L183 _public prototype_ `virtual void AddConstantBufferViewParameter(uint32 Register, uint32 Space, ERootSignatureVisibility Visibility = ERootSignatureVisibility::All) = 0;`
- L184 _public prototype_ `virtual void AddShaderResourceViewParameter(uint32 Register, uint32 Space, ERootSignatureVisibility Visibility = ERootSignatureVisibility::All) = 0;`
- L185 _public prototype_ `virtual void AddUnorderedAccessViewParameter(uint32 Register, uint32 Space, ERootSignatureVisibility Visibility = ERootSignatureVisibility::All) = 0;`
- L186 _public prototype_ `virtual void AddTable(ERootSignatureVisibility Visibility, ERootSignatureRangeType Type, int32 NumDescriptors, D3D12_DESCRIPTOR_RANGE_FLAGS FlagsOverride = D3D12_DESCRIPTOR_RANGE_FLAG_NONE) = 0;`
- L187 _public prototype_ `virtual void AddConstantsParameter(uint32 Num32BitValues, uint32 Register, uint32 Space) = 0;`
- L189 _public function_ `void SetFlags(EShaderBindingLayoutFlags InFlags)`
- L209 _public function_ `bool HasFlags(EShaderBindingLayoutFlags InFlags) const`
- L214 _public function_ `void SetRegisterSpace(uint32 InSpace)`
- L219 _public function_ `uint32 GetRegisterSpace() const`
- L224 _public function_ `inline bool ShouldSkipType(ERootSignatureRangeType Type) const`

#### struct `D3D12ShaderUtils::FBinaryRootSignatureCreator`  
`struct FBinaryRootSignatureCreator final : public FRootSignatureCreator`  
_L240-322_
- inherits: `FRootSignatureCreator`
- L242 _public member_ `D3D12_ROOT_SIGNATURE_FLAGS RootFlags = D3D12_ROOT_SIGNATURE_FLAG_NONE;`
- L243 _public member_ `TArray<CD3DX12_DESCRIPTOR_RANGE1> DescriptorRanges;`
- L244 _public member_ `TArray<CD3DX12_ROOT_PARAMETER1> Parameters;`
- L245 _public member_ `CD3DX12_VERSIONED_ROOT_SIGNATURE_DESC RootDesc;`
- L254 _public member_ `TArray<FPendingTable> PendingTables;`
- L256 _public function_ `void AddRootFlag(D3D12_ROOT_SIGNATURE_FLAGS RootFlag) override`
- L261 _public function_ `void AddConstantBufferViewParameter(uint32 Register, uint32 Space, ERootSignatureVisibility Visibility = ERootSignatureVisibility::All) override`
- L267 _public function_ `void AddShaderResourceViewParameter(uint32 Register, uint32 Space, ERootSignatureVisibility Visibility = ERootSignatureVisibility::All) override`
- L273 _public function_ `void AddUnorderedAccessViewParameter(uint32 Register, uint32 Space, ERootSignatureVisibility Visibility = ERootSignatureVisibility::All) override`
- L279 _public function_ `void AddConstantsParameter(uint32 Num32BitValues, uint32 Register, uint32 Space) override`
- L285 _public function_ `void AddTable(ERootSignatureVisibility Visibility, ERootSignatureRangeType Type, int32 NumDescriptors, D3D12_DESCRIPTOR_RANGE_FLAGS FlagsOverride = D3D12_DESCRIPTOR_RANGE_FLAG_NONE) override`
- L294 _public function_ `const D3D12_VERSIONED_ROOT_SIGNATURE_DESC& Finalize()`

#### struct `D3D12ShaderUtils::FBinaryRootSignatureCreator::FPendingTable`  
`struct FPendingTable`  
_L247-253_
- L249 _public member_ `ERootSignatureVisibility Visibility;`
- L250 _public member_ `ERootSignatureRangeType Type;`
- L251 _public member_ `int32 NumDescriptors;`
- L252 _public member_ `D3D12_DESCRIPTOR_RANGE_FLAGS FlagsOverride;`

#### struct `D3D12ShaderUtils::FTextRootSignatureCreator`  
`struct FTextRootSignatureCreator final : public FRootSignatureCreator`  
_L325-401_
- inherits: `FRootSignatureCreator`
- desc: Root signature generator for DXC
- L327 _public function_ `void AddRootFlag(D3D12_ROOT_SIGNATURE_FLAGS InFlag) override`
- L336 _public function_ `void AddConstantBufferViewParameter(uint32 Register, uint32 Space, ERootSignatureVisibility Visibility = ERootSignatureVisibility::All) override`
- L346 _public function_ `void AddShaderResourceViewParameter(uint32 Register, uint32 Space, ERootSignatureVisibility Visibility = ERootSignatureVisibility::All) override`
- L356 _public function_ `void AddUnorderedAccessViewParameter(uint32 Register, uint32 Space, ERootSignatureVisibility Visibility = ERootSignatureVisibility::All) override`
- L366 _public function_ `void AddConstantsParameter(uint32 Num32BitValues, uint32 Register, uint32 Space) override`
- L376 _public function_ `void AddTable(ERootSignatureVisibility Visibility, ERootSignatureRangeType Type, int32 NumDescriptors, D3D12_DESCRIPTOR_RANGE_FLAGS FlagsOverride = D3D12_DESCRIPTOR_RANGE_FLAG_NONE) override`
- L391 _public function_ `FString GenerateString() const`
- L399 _public member_ `FString RootFlags;`
- L400 _public member_ `FString Table;`

#### Free symbols / members of external scopes

- L19 _namespace_ `namespace D3D12ShaderUtils`
- L21 _namespace_ `namespace StaticRootSignatureConstants` (scope `D3D12ShaderUtils`)
- L24 _variable_ `constexpr D3D12_DESCRIPTOR_RANGE_FLAGS SRVDescriptorRangeFlags = D3D12_DESCRIPTOR_RANGE_FLAG_DATA_STATIC_WHILE_SET_AT_EXECUTE | D3D12_DESCRIPTOR_RANGE_FLAG_DESCRIPTORS_VOLATILE;` (scope `D3D12ShaderUtils::StaticRootSignatureConstants`) — Assume descriptors are volatile because we don't initialize all the descriptors in a table, just the ones used by the current shaders.
- L25 _variable_ `constexpr D3D12_DESCRIPTOR_RANGE_FLAGS CBVDescriptorRangeFlags = D3D12_DESCRIPTOR_RANGE_FLAG_DATA_STATIC_WHILE_SET_AT_EXECUTE | D3D12_DESCRIPTOR_RANGE_FLAG_DESCRIPTORS_VOLATILE;` (scope `D3D12ShaderUtils::StaticRootSignatureConstants`)
- L26 _variable_ `constexpr D3D12_DESCRIPTOR_RANGE_FLAGS UAVDescriptorRangeFlags = D3D12_DESCRIPTOR_RANGE_FLAG_DATA_VOLATILE | D3D12_DESCRIPTOR_RANGE_FLAG_DESCRIPTORS_VOLATILE;` (scope `D3D12ShaderUtils::StaticRootSignatureConstants`)
- L27 _variable_ `constexpr D3D12_DESCRIPTOR_RANGE_FLAGS SamplerDescriptorRangeFlags = D3D12_DESCRIPTOR_RANGE_FLAG_DESCRIPTORS_VOLATILE;` (scope `D3D12ShaderUtils::StaticRootSignatureConstants`)
- L30 _variable_ `constexpr D3D12_ROOT_DESCRIPTOR_FLAGS CBVRootDescriptorFlags = D3D12_ROOT_DESCRIPTOR_FLAG_DATA_STATIC;` (scope `D3D12ShaderUtils::StaticRootSignatureConstants`) — We always set the data in an upload heap before calling Set*RootConstantBufferView.
- L51 _function_ `inline D3D12_DESCRIPTOR_RANGE_TYPE GetD3D12DescriptorRangeType(ERootSignatureRangeType Type)` (scope `D3D12ShaderUtils`)
- L66 _function_ `inline D3D12_DESCRIPTOR_RANGE_FLAGS GetD3D12DescriptorRangeFlags(ERootSignatureRangeType Type)` (scope `D3D12ShaderUtils`)
- L83 _function_ `inline D3D12_SHADER_VISIBILITY GetD3D12ShaderVisibility(ERootSignatureVisibility Visibility)` (scope `D3D12ShaderUtils`)
- L104 _function_ `inline const TCHAR* GetVisibilityFlag(ERootSignatureVisibility Visibility)` (scope `D3D12ShaderUtils`)
- L125 _function_ `inline const TCHAR* GetTypePrefix(ERootSignatureRangeType Type)` (scope `D3D12ShaderUtils`)
- L140 _function_ `inline const TCHAR* GetFlagName(D3D12_ROOT_SIGNATURE_FLAGS Flag)` (scope `D3D12ShaderUtils`)
- L403 _function_ `inline void AddAllStandardTablesForVisibility(FRootSignatureCreator& Creator, ERootSignatureVisibility Visibility)` (scope `D3D12ShaderUtils`)
- L411 _function_ `inline void CreateGfxRootSignature(FRootSignatureCreator& Creator, EShaderBindingLayoutFlags InFlags)` (scope `D3D12ShaderUtils`) — Fat/Static Gfx Root Signature
- L443 _function_ `inline void CreateComputeRootSignature(FRootSignatureCreator& Creator, EShaderBindingLayoutFlags InFlags)` (scope `D3D12ShaderUtils`) — Fat/Static Compute Root Signature
- L463 _function_ `inline void CreateRayTracingSignature(FRootSignatureCreator& Creator, bool bLocalRootSignature, D3D12_ROOT_SIGNATURE_FLAGS BaseRootFlags, EShaderBindingLayoutFlags InFlags)` (scope `D3D12ShaderUtils`)
- L510 _function_ `inline FString GenerateRayTracingSignatureString(bool bLocalRootSignature, D3D12_ROOT_SIGNATURE_FLAGS BaseRootFlags, EShaderBindingLayoutFlags InFlags)` (scope `D3D12ShaderUtils`)
- L518 _function_ `inline FString GenerateRootSignatureString(EShaderFrequency InFrequency, EShaderBindingLayoutFlags InFlags)` (scope `D3D12ShaderUtils`)

### `Source/Runtime/D3D12RHI/Public/D3D12ShaderResources.h` (Public)


#### Free symbols / members of external scopes

- L12 _variable_ `const int32 PackedShaderKey = 'XSHA';` — Key used for determining whether shader code is packed or not.
- L15 _variable_ `const int32 RayTracingPrecompiledPSOKey = 'RTPS';` — Key indicating whether serialized ray tracing shader contains a DXIL library or a precompiled PSO.

### `Source/Runtime/D3D12RHI/Public/D3D12ThirdParty.h` (Public)
_(no declarations extracted)_

### `Source/Runtime/D3D12RHI/Public/ID3D12DynamicRHI.h` (Public)


#### struct `FD3D12MinimalAdapterDesc`  
`struct FD3D12MinimalAdapterDesc`  
_L9-13_
- L11 _public member_ `DXGI_ADAPTER_DESC Desc{};`
- L12 _public member_ `uint32 NumDeviceNodes{};`

#### enum `ED3D12RHIRunOnQueueType`  
`enum class ED3D12RHIRunOnQueueType`  
_L15-19_
- L17 _public enumerator_ `Graphics = 0`
- L18 _public enumerator_ `Copy`

#### struct `ID3D12DynamicRHI`  
`struct ID3D12DynamicRHI : public FDynamicRHI`  
_L21-69_
- inherits: `FDynamicRHI`
- L23 _public function_ `virtual ERHIInterfaceType GetInterfaceType() const override final`
- L25 _public prototype_ `virtual TArray<FD3D12MinimalAdapterDesc> RHIGetAdapterDescs() const = 0;`
- L26 _public prototype_ `virtual bool RHIIsPixEnabled() const = 0;`
- L29 _public prototype_ `virtual ID3D12Device* RHIGetDevice_NoMGPU() const = 0;` — Provided for backwards compatibility. Returns the 0th device, equivalent to RHIGetDevice(0), but also triggers an ensure if MGPU is enabled.
- L31 _public prototype_ `virtual ID3D12CommandQueue* RHIGetCommandQueue() const = 0;`
- L32 _public prototype_ `virtual ID3D12Device* RHIGetDevice(uint32 InIndex) const = 0;`
- L33 _public prototype_ `virtual uint32 RHIGetDeviceNodeMask(uint32 InIndex) const = 0;`
- L34 _public prototype_ `virtual ID3D12GraphicsCommandList* RHIGetGraphicsCommandList(FRHICommandListBase& ExecutingCmdList, uint32 InDeviceIndex) const = 0;`
- L35 _public prototype_ `virtual DXGI_FORMAT RHIGetSwapChainFormat(EPixelFormat InFormat) const = 0;`
- L37 _public prototype_ `virtual FTextureRHIRef RHICreateTexture2DFromResource(EPixelFormat Format, ETextureCreateFlags TexCreateFlags, const FClearValueBinding& ClearValueBinding, ID3D12Resource* Resource) = 0;`
- L38 _public prototype_ `virtual FTextureRHIRef RHICreateTexture2DArrayFromResource(EPixelFormat Format, ETextureCreateFlags TexCreateFlags, const FClearValueBinding& ClearValueBinding, ID3D12Resource* Resource) = 0;`
- L39 _public prototype_ `virtual FTextureRHIRef RHICreateTextureCubeFromResource(EPixelFormat Format, ETextureCreateFlags TexCreateFlags, const FClearValueBinding& ClearValueBinding, ID3D12Resource* Resource) = 0;`
- L41 _public prototype_ `virtual ID3D12Resource* RHIGetResource(FRHIBuffer* InBuffer) const = 0;`
- L42 _public prototype_ `virtual uint32 RHIGetResourceDeviceIndex(FRHIBuffer* InBuffer) const = 0;`
- L43 _public prototype_ `virtual int64 RHIGetResourceMemorySize(FRHIBuffer* InBuffer) const = 0;`
- L44 _public prototype_ `virtual bool RHIIsResourcePlaced(FRHIBuffer* InBuffer) const = 0;`
- L45 _public prototype_ `virtual ID3D12Resource* RHIGetResource(FRHITexture* InTexture) const = 0;`
- L46 _public prototype_ `virtual uint32 RHIGetResourceDeviceIndex(FRHITexture* InTexture) const = 0;`
- L47 _public prototype_ `virtual int64 RHIGetResourceMemorySize(FRHITexture* InTexture) const = 0;`
- L48 _public prototype_ `virtual bool RHIIsResourcePlaced(FRHITexture* InTexture) const = 0;`
- L50 _public prototype_ `virtual D3D12_CPU_DESCRIPTOR_HANDLE RHIGetRenderTargetView(FRHITexture* InTexture, int32 InMipIndex = 0, int32 InArraySliceIndex = 0) const = 0;`
- L52 _public prototype_ `virtual void RHIFinishExternalComputeWork(FRHICommandListBase& ExecutingCmdList, uint32 InDeviceIndex, ID3D12GraphicsCommandList* InCommandList) = 0;`
- L55 _public prototype_ `virtual void RHITransitionResource(FRHICommandList& RHICmdList, FRHITexture* InTexture, D3D12_RESOURCE_STATES InState, uint32 InSubResource) = 0;` — `UE_DEPRECATED(5.6, "RHITransitionResource without explicit Before and After states is deprecated. Please call RHICmdList.Transition() using ERHIAccess states to issue the transition, ERHIAccess::Unknown as Before state is supported.")`
- L57 _public prototype_ `virtual void RHISignalManualFence(FRHICommandList& RHICmdList, ID3D12Fence* Fence, uint64 Value) = 0;`
- L58 _public prototype_ `virtual void RHIWaitManualFence(FRHICommandList& RHICmdList, ID3D12Fence* Fence, uint64 Value, const TSharedPtr<std::atomic<bool>>& bHasSignalled) = 0;`
- L60 _public prototype_ `virtual void RHIVerifyResult(ID3D12Device* Device, HRESULT Result, const ANSICHAR* Code, const ANSICHAR* Filename, uint32 Line, FString Message = FString()) const = 0;`
- L62 _public prototype_ `virtual void RHIRunOnQueue(ED3D12RHIRunOnQueueType QueueType, TFunction<void(ID3D12CommandQueue*)>&& CodeToRun, bool bWaitForSubmission) = 0;`
- L64 _public prototype_ `virtual void RHIFlushResourceBarriers(FRHICommandListBase& RHICmdList, uint32 InGPUIndex) = 0;`
- L65 _public prototype_ `virtual void RHIUpdateResourceResidency(FRHICommandListBase& RHICmdList, uint32 InGPUIndex, FRHIResource* InResource) = 0;`
- L68 _public prototype_ `virtual FRHIViewport* RHIGetSingletonViewport() const = 0;` — Returns the RHI viewport, assuming only a single FRHIViewport instance exists. Otherwise, returns nullptr.

#### Free symbols / members of external scopes

- L71 _function_ `inline bool IsRHID3D12()`
- L76 _function_ `inline ID3D12DynamicRHI* GetID3D12DynamicRHI()`
- L85 _typedef_ `using ID3D12PlatformDynamicRHI = ID3D12DynamicRHI;`
- L87 _function_ `inline ID3D12PlatformDynamicRHI* GetID3D12PlatformDynamicRHI()`
