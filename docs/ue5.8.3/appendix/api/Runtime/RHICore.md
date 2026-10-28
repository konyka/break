# Runtime / RHICore

- module root: `Source/Runtime/RHICore`
- headers: 20; symbols: 820
- symbol kinds: class=23, enum=6, enumerator=22, function=223, macro=5, member=264, namespace=36, prototype=191, struct=39, typedef=5, union=1, variable=5
- PrivateDependencyModuleNames: Core

### `Source/Runtime/RHICore/Internal/DXGIUtilities.h` (Internal)


#### class `FRHIFrameFlipStatTrackingRunnable`  
`class FRHIFrameFlipStatTrackingRunnable : public FRunnable`  
_L501-527_
- inherits: `FRunnable`
- L503 _private member_ `FRunnableThread* Thread = nullptr;`
- L504 _private member_ `TRefCountPtr<IDXGISwapChain1> SwapChain1;`
- L505 _private member_ `bool bInitialized = false;`
- L506 _private member_ `bool bRun = false;`
- L508 _private prototype_ `FRHIFrameFlipStatTrackingRunnable(const FRHIFrameFlipStatTrackingRunnable&) = delete;`
- L509 _private prototype_ `FRHIFrameFlipStatTrackingRunnable& operator=(const FRHIFrameFlipStatTrackingRunnable&) = delete;`
- L510 _private prototype_ `FRHIFrameFlipStatTrackingRunnable(FRHIFrameFlipStatTrackingRunnable&&) = delete;`
- L511 _private prototype_ `FRHIFrameFlipStatTrackingRunnable& operator=(FRHIFrameFlipStatTrackingRunnable&&) = delete;`
- L513 _private prototype_ `FRHIFrameFlipStatTrackingRunnable(TRefCountPtr<IDXGISwapChain1> InSwapChain1);`
- L514 _private prototype_ `~FRHIFrameFlipStatTrackingRunnable();`
- L516 _private prototype_ `virtual uint32 Run() override;`
- L517 _private prototype_ `virtual void Stop() override;`
- L519 _private prototype_ `void StartThread();`
- L520 _private prototype_ `void StopThread();`
- L525 _public prototype_ `static void Create(TRefCountPtr<IDXGISwapChain1> InSwapChain1);` — Refcounted process-wide singleton. First Create spins up the tracker thread; the matching final Release tears it down. One tracker is sufficient because RHIFrameInfoSetVsyncDetails is a global sink, and WaitForVBlank fires per monitor vblank regardless of swap chain count.
- L526 _public prototype_ `static void Release();`

#### Free symbols / members of external scopes

- L28 _namespace_ `namespace UE`
- L28 _namespace_ `namespace DXGIUtilities` (scope `UE`)
- L30 _prototype_ `const TCHAR* GetFormatString(DXGI_FORMAT Format);` (scope `UE::DXGIUtilities`)
- L31 _prototype_ `HRESULT GetD3DMemoryStats(IDXGIAdapter* Adapter, FRHIMemoryStats& OutStats);` (scope `UE::DXGIUtilities`)
- L33 _function_ `inline DXGI_FORMAT FindSharedResourceFormat(DXGI_FORMAT InFormat, bool bSRGB)` (scope `UE::DXGIUtilities`)
- L86 _function_ `inline DXGI_FORMAT FindShaderResourceFormat(DXGI_FORMAT InFormat, bool bSRGB)` (scope `UE::DXGIUtilities`) — Find an appropriate DXGI format for the input format and SRGB setting.
- L122 _function_ `inline DXGI_FORMAT FindDepthStencilResourceFormat(DXGI_FORMAT InFormat)` (scope `UE::DXGIUtilities`)
- L133 _function_ `inline DXGI_FORMAT GetPlatformTextureResourceFormat(DXGI_FORMAT InFormat, ETextureCreateFlags InFlags)` (scope `UE::DXGIUtilities`)
- L148 _function_ `inline DXGI_FORMAT GetPlatformTextureResourceFormat(EPixelFormat InPixelFormat, ETextureCreateFlags InFlags)` (scope `UE::DXGIUtilities`)
- L154 _function_ `inline DXGI_FORMAT FindUnorderedAccessFormat(DXGI_FORMAT InFormat)` (scope `UE::DXGIUtilities`) — Find an appropriate DXGI format unordered access of the raw format.
- L166 _function_ `inline DXGI_FORMAT FindDepthStencilFormat(DXGI_FORMAT InFormat)` (scope `UE::DXGIUtilities`) — Find the appropriate depth-stencil targetable DXGI format for the given format.
- L179 _function_ `inline DXGI_FORMAT FindDepthStencilParentDXGIFormat(DXGI_FORMAT InFormat)` (scope `UE::DXGIUtilities`) — Find the appropriate depth-stencil typeless DXGI format for the given format.
- L199 _function_ `inline bool HasStencilBits(DXGI_FORMAT InFormat)` (scope `UE::DXGIUtilities`) — Returns whether the given format contains stencil information. Must be passed a format returned by FindDepthStencilFormat, so that typeless versions are converted to their corresponding depth stencil view format.
- L210 _function_ `inline bool IsBlockCompressedFormat(DXGI_FORMAT Format)` (scope `UE::DXGIUtilities`)
- L217 _function_ `inline uint8 GetPlaneSliceFromViewFormat(DXGI_FORMAT ResourceFormat, DXGI_FORMAT ViewFormat)` (scope `UE::DXGIUtilities`)
- L258 _function_ `inline uint8 GetPlaneCount(DXGI_FORMAT Format)` (scope `UE::DXGIUtilities`)
- L271 _function_ `inline uint32 GetWidthAlignment(DXGI_FORMAT Format)` (scope `UE::DXGIUtilities`)
- L311 _function_ `inline uint32 GetHeightAlignment(DXGI_FORMAT Format)` (scope `UE::DXGIUtilities`)
- L344 _function_ `inline uint32 GetFormatSizeInBits(DXGI_FORMAT Format)` (scope `UE::DXGIUtilities`)
- L478 _function_ `inline uint32 GetFormatSizeInBytes(DXGI_FORMAT Format)` (scope `UE::DXGIUtilities`)
- L483 _function_ `inline DXGI_FORMAT GetSwapChainFormat(EPixelFormat PixelFormat)` (scope `UE::DXGIUtilities`)

### `Source/Runtime/RHICore/Internal/RHICoreBufferInitializer.h` (Internal)


#### struct `UE::RHICore::FDefaultBufferInitializer`  
`struct FDefaultBufferInitializer : public FRHIBufferInitializer`  
_L14-30_
- inherits: `FRHIBufferInitializer`
- desc: Buffer initializer that just returns the buffer on finalize.
- L16 _public function_ `FDefaultBufferInitializer(FRHICommandListBase& RHICmdList, FRHIBuffer* Buffer, void* InWritableData, uint64 InWritableSize) : FRHIBufferInitializer(RHICmdList, Buffer, InWritableData, InWritableSize, [Buffer = TRefCountPtr<FRHIBuffer>(Buffer)](FRHICommandListBase&) mutable { return MoveTemp(Buffer); } )`
- L19 _public function_ ``
- L26 _public function_ `FDefaultBufferInitializer(FRHICommandListBase& RHICmdList, FRHIBuffer* Buffer) : FDefaultBufferInitializer(RHICmdList, Buffer, nullptr, 0)`

#### struct `UE::RHICore::FLockBufferInitializer`  
`struct FLockBufferInitializer : public FRHIBufferInitializer`  
_L33-48_
- inherits: `FRHIBufferInitializer`
- desc: Buffer initializer that calls Lock on creation and Unlock on finalize.
- L35 _public function_ `FLockBufferInitializer(FRHICommandListBase& RHICmdList, FRHIBuffer* Buffer) : FRHIBufferInitializer( RHICmdList, Buffer, RHICmdList.LockBuffer(Buffer, 0, Buffer->GetDesc().Size, RLM_WriteOnly), Buffer->GetDesc().Size, [Buffer = TRefCountPtr<FRHIBuffer>(Buffer)](FRHICommandListBase& RHICmdList) mutable { RHICmdList.UnlockBuffer(Buffer); return MoveTemp(Buffer); })`
- L42 _public function_ ``

#### struct `UE::RHICore::FCustomBufferInitializer`  
`struct FCustomBufferInitializer : public FRHIBufferInitializer`  
_L51-57_
- inherits: `FRHIBufferInitializer`
- desc: Buffer initializer with custom implementation. This type is necessary for access to the FRHIBufferInitializer protected constructor.
- L53 _public function_ `FCustomBufferInitializer(FRHICommandListBase& RHICmdList, FRHIBuffer* Buffer, void* InWritableData, uint64 InWritableSize, FFinalizeCallback&& Func) : FRHIBufferInitializer(RHICmdList, Buffer, InWritableData, InWritableSize, Forward<FFinalizeCallback>(Func))`

#### class `UE::RHICore::FInvalidBuffer`  
`class FInvalidBuffer : public FRHIBuffer`  
_L59-66_
- inherits: `FRHIBuffer`
- L62 _public function_ `FInvalidBuffer(const FRHIBufferCreateDesc& CreateDesc) : FRHIBuffer(CreateDesc)`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace RHICore` (scope `UE`)
- L68 _function_ `static FRHIBufferInitializer HandleUnknownBufferInitializerInitAction(FRHICommandListBase& RHICmdList, const FRHIBufferCreateDesc& CreateDesc)` (scope `UE::RHICore`)
- L77 _function_ `static FRHIBufferInitializer CreateUnifiedMemoryBufferInitializer( FRHICommandListBase& RHICmdList , const FRHIBufferCreateDesc& CreateDesc , FRHIBuffer* Buffer , void* WritableData )` (scope `UE::RHICore`) — Create a buffer initializer for a unified memory platform. Any init actions not handled before here will use default implementations.

### `Source/Runtime/RHICore/Internal/RHICoreInitializerCommon.h` (Internal)


#### struct `UE::RHICore::FInitializerScopedMemory`  
`struct FInitializerScopedMemory : public FNoncopyable`  
_L11-35_
- inherits: `FNoncopyable`
- desc: Utility class for RHIs to use when they need to malloc aligned data up-front and make sure it's freed correctly by the Initializer lambda destruction
- L13 _public function_ `FInitializerScopedMemory(void* InPointer) : Pointer(InPointer)`
- L17 _public function_ `FInitializerScopedMemory(size_t InSize, uint32 InAlignment) : FInitializerScopedMemory(FMemory::Malloc(InSize, InAlignment))`
- L21 _public function_ `FInitializerScopedMemory(FInitializerScopedMemory&& InOther) : Pointer(InOther.Pointer)`
- L26 _public function_ `~FInitializerScopedMemory()`
- L34 _public member_ `void* Pointer{};`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace RHICore` (scope `UE`)

### `Source/Runtime/RHICore/Internal/RHICoreResourceCollection.h` (Internal)


#### class `UE::RHICore::FGenericResourceCollection`  
`class FGenericResourceCollection : public FRHIResourceCollection`  
_L85-112_
- inherits: `FRHIResourceCollection`
- L88 _public function_ `FGenericResourceCollection(FRHICommandListBase& RHICmdList, TConstArrayView<FRHIResourceCollectionMember> InMembers) : FRHIResourceCollection(InMembers) , Buffer(CreateResourceCollectionBuffer(RHICmdList, InMembers))`
- L96 _public prototype_ `~FGenericResourceCollection() = default;`
- L99 _public function_ `virtual FRHIDescriptorHandle GetBindlessHandle() const final` — FRHIResourceCollection
- L105 _public function_ `FRHIShaderResourceView* GetShaderResourceView() const`
- L110 _public member_ `TRefCountPtr<FRHIBuffer> Buffer;`
- L111 _public member_ `TRefCountPtr<FRHIShaderResourceView> ShaderResourceView;`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace RHICore` (scope `UE`)
- L16 _function_ `template<typename TType> inline size_t CalculateResourceCollectionMemorySize(TConstArrayView<TType> InValues)` (scope `UE::RHICore`)
- L21 _function_ `inline FRHIDescriptorHandle GetHandleForResourceCollectionValue(const FRHIResourceCollectionMember& Member)` (scope `UE::RHICore`)
- L36 _function_ `inline FRHIDescriptorHandle GetHandleForResourceCollectionValue(const FRHIDescriptorHandle& Handle)` (scope `UE::RHICore`)
- L41 _function_ `inline void FillResourceCollectionUpdateMemory(uint32* Destination, TConstArrayView<FRHIResourceCollectionMember> InValues)` (scope `UE::RHICore`)
- L57 _function_ `inline void FillResourceCollectionMemory(uint32* Destination, TConstArrayView<FRHIResourceCollectionMember> InValues)` (scope `UE::RHICore`)
- L64 _function_ `inline void FillResourceCollectionMemory(TRHIBufferInitializer<uint32>& Destination, TConstArrayView<FRHIResourceCollectionMember> InValues)` (scope `UE::RHICore`)
- L69 _function_ `inline FRHIBuffer* CreateResourceCollectionBuffer(FRHICommandListBase& RHICmdList, TConstArrayView<FRHIResourceCollectionMember> InMembers)` (scope `UE::RHICore`)
- L114 _function_ `inline FRHIResourceCollectionRef CreateGenericResourceCollection(FRHICommandListBase& RHICmdList, TConstArrayView<FRHIResourceCollectionMember> InMembers)` (scope `UE::RHICore`)
- L119 _function_ `inline TConstArrayView<FRHIResourceCollectionMember> GetValidResourceCollectionUpdateList(FRHIResourceCollection* ResourceCollection, uint32 StartIndex, TConstArrayView<FRHIResourceCollectionMember> InUpdates)` (scope `UE::RHICore`)
- L132 _function_ `inline void UpdateGenericResourceCollection(FRHICommandListBase& RHICmdList, FGenericResourceCollection* ResourceCollection, uint32 StartIndex, TConstArrayView<FRHIResourceCollectionMember> InMemberUpdates)` (scope `UE::RHICore`)

### `Source/Runtime/RHICore/Internal/RHICoreStats.h` (Internal)


#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace RHICore` (scope `UE`)
- L14 _prototype_ `void UpdateGlobalTextureStats(ETextureCreateFlags TextureFlags, ETextureDimension Dimension, uint64 TextureSizeInBytes, bool bOnlyStreamableTexturesInTexturePool, bool bAllocating);` (scope `UE::RHICore`)
- L15 _prototype_ `void UpdateGlobalTextureStats(const FRHITextureDesc& TextureDesc, uint64 TextureSizeInBytes, bool bOnlyStreamableTexturesInTexturePool, bool bAllocating);` (scope `UE::RHICore`)
- L17 _prototype_ `void FillBaselineTextureMemoryStats(FTextureMemoryStats& OutStats);` (scope `UE::RHICore`)
- L19 _prototype_ `void UpdateGlobalBufferStats(const FRHIBufferDesc& BufferDesc, int64 BufferSizeDelta);` (scope `UE::RHICore`)
- L20 _function_ `inline void UpdateGlobalBufferStats(const FRHIBufferDesc& BufferDesc, uint64 BufferSize, bool bAllocating)` (scope `UE::RHICore`)
- L26 _prototype_ `void UpdateGlobalUniformBufferStats(int64 BufferSize, bool bAllocating);` (scope `UE::RHICore`)
- L28 _prototype_ `void UpdateReservedResourceStatsOnCommit(int64 CommitDelta, bool bBuffer, bool bCommitting);` (scope `UE::RHICore`)

### `Source/Runtime/RHICore/Internal/RHICoreTexture.h` (Internal)


#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace RHICore` (scope `UE`)
- L10 _function_ `inline uint32 GetCombinedArrayIndex(const FRHITextureDesc& Desc, uint32 FaceIndex, uint32 ArrayIndex)` (scope `UE::RHICore`)
- L25 _function_ `inline uint32 GetLockArrayIndex(const FRHITextureDesc& Desc, const FRHILockTextureArgs& Arguments)` (scope `UE::RHICore`)

### `Source/Runtime/RHICore/Internal/RHICoreTextureInitializer.h` (Internal)


#### struct `UE::RHICore::FBaseTextureInitializerImplementation`  
`struct FBaseTextureInitializerImplementation : public FRHITextureInitializer`  
_L14-34_
- inherits: `FRHITextureInitializer`
- L16 _public function_ `FBaseTextureInitializerImplementation(FRHICommandListBase& RHICmdList, FRHITexture* InTexture, void* InWritableData, uint64 InWritableSize, FFinalizeCallback&& InFinalizeCallback, FGetSubresourceCallback&& InGetSubresourceCallback) : FRHITextureInitializer(RHICmdList, InTexture, InWritableData, InWritableSize, Forward<FFinalizeCallback>(InFinalizeCallback), Forward<FGetSubresourceCallback>(InGetSubresourceCallback))`
- L20 _public function_ `FBaseTextureInitializerImplementation(FRHICommandListBase& RHICmdList, FRHITexture* Texture, FFinalizeCallback&& InFinalizeCallback) : FRHITextureInitializer(RHICmdList, Texture, nullptr, 0, Forward<FFinalizeCallback>(InFinalizeCallback), nullptr)`
- L25 _public function_ `void* GetWritableData() const`
- L30 _public function_ `uint64 GetWritableSize() const`

#### struct `UE::RHICore::FDefaultTextureInitializer`  
`struct FDefaultTextureInitializer : public FBaseTextureInitializerImplementation`  
_L37-48_
- inherits: `FBaseTextureInitializerImplementation`
- desc: Texture initializer that just returns the texture on finalize.
- L39 _public function_ `FDefaultTextureInitializer(FRHICommandListBase& RHICmdList, FRHITexture* Texture) : FBaseTextureInitializerImplementation(RHICmdList, Texture, [Texture = TRefCountPtr<FRHITexture>(Texture)](FRHICommandListBase&) mutable { return MoveTemp(Texture); } )`
- L42 _public function_ ``

#### struct `UE::RHICore::FDefaultLayoutTextureInitializer`  
`struct FDefaultLayoutTextureInitializer : public FBaseTextureInitializerImplementation`  
_L50-72_
- inherits: `FBaseTextureInitializerImplementation`
- L52 _public function_ `FDefaultLayoutTextureInitializer(FRHICommandListBase& RHICmdList, FRHITexture* InTexture, void* InMemory, uint64 InMemorySize, FFinalizeCallback&& FinalizeFunc) : FBaseTextureInitializerImplementation(RHICmdList, InTexture, InMemory, InMemorySize, Forward<FFinalizeCallback>(FinalizeFunc), [Texture = TRefCountPtr<FRHITexture>(InTexture), WritableData = InMemory](FRHITextureInitializer::FSubresourceIndex SubresourceIndex) { const FRHITextureDesc& TextureDesc = Texture->GetDesc(); uint64 SubresourceStride = 0; uint64 SubresourceSize = 0; const uint64 Offset = UE::RHITextureUtils::CalculateSubresourceOffset(TextureDesc, SubresourceIndex.FaceIndex, SubresourceIndex.ArrayIndex, SubresourceIndex.MipIndex, SubresourceStride, SubresourceSize); FRHITextureSubresourceInitializer Result{}; Result.Data = reinterpret_cast<uint8*>(WritableData) + Offset; Result.Stride = SubresourceStride; Result.Size = SubresourceSize; return Result; } )`
- L55 _public function_ ``

#### struct `UE::RHICore::FLockTextureInitializer`  
`struct FLockTextureInitializer : public FDefaultLayoutTextureInitializer`  
_L75-113_
- inherits: `FDefaultLayoutTextureInitializer`
- desc: Texture Initializer that uses Lock/Unlock to upload initial data
- L77 _public function_ `FLockTextureInitializer(FRHICommandListBase& RHICmdList, FRHITexture* InTexture, void* InMemory, uint64 InMemorySize) : FDefaultLayoutTextureInitializer(RHICmdList, InTexture, InMemory, InMemorySize, [Texture = TRefCountPtr<FRHITexture>(InTexture), WritableMemory = FInitializerScopedMemory(InMemory)](FRHICommandListBase& InRHICmdList) mutable { FRHICommandListImmediate& RHICmdList = InRHICmdList.GetAsImmediate(); const FRHITextureDesc& TextureDesc = Texture->GetDesc(); const uint32 FaceCount = TextureDesc.IsTextureCube() ? 6 : 1; for (uint32 FaceIndex = 0; FaceIndex < FaceCount; FaceIndex++) { for (uint32 ArrayIndex = 0; ArrayIndex < TextureDesc.ArraySize; ArrayIndex++) { for (uint32 MipIndex = 0; MipIndex < TextureDesc.NumMips; MipIndex++) { uint64 SubresourceStride = 0; uint64 SubresourceSize = 0; const uint64 Offset = UE::RHITextureUtils::CalculateSubresourceOffset(TextureDesc, FaceIndex, ArrayIndex, MipIndex, SubresourceStride, SubresourceSize); const FRHILockTextureArgs LockArgs = FRHILockTextureArgs::LockCubeFace(Texture, FaceIndex, ArrayIndex, MipIndex, RLM_WriteOnly, false); FRHILockTextureResult LockResult = RHICmdList.LockTexture(LockArgs); check(LockResult.ByteCount <= SubresourceSize); check(LockResult.Stride == SubresourceStride); FMemory::Memcpy(LockResult.Data, reinterpret_cast<uint8*>(WritableMemory.Pointer) + Offset, SubresourceSize); RHICmdList.UnlockTexture(LockArgs); } } } return MoveTemp(Texture); })`
- L80 _public function_ ``

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace RHICore` (scope `UE`)
- L115 _function_ `static FLockTextureInitializer CreateLockTextureInitializer(FRHICommandListBase& RHICmdList, FRHITexture* Texture, const FRHITextureCreateDesc& CreateDesc)` (scope `UE::RHICore`)
- L123 _function_ `static FRHITextureInitializer HandleUnknownTextureInitializerInitAction(FRHICommandListBase& RHICmdList, const FRHITextureCreateDesc& CreateDesc)` (scope `UE::RHICore`)

### `Source/Runtime/RHICore/Internal/RHICoreTransitions.h` (Internal)


#### struct `UE::RHICore::FResourceState`  
`struct FResourceState`  
_L11-58_
- L13 _public function_ `FResourceState(IRHIComputeContext& Context, ERHIPipeline InSrcPipelines, ERHIPipeline InDstPipelines, const FRHITransitionInfo& Info) : AccessBefore(Info.AccessBefore) , AccessAfter(Info.AccessAfter) , SrcPipelines(InSrcPipelines) , DstPipelines(InDstPipelines)`
- L37 _public member_ `ERHIAccess AccessBefore;`
- L38 _public member_ `ERHIAccess AccessAfter;`
- L41 _public member_ `ERHIPipeline SrcPipelines;` — SrcPipeline may differ from the declared RHI SrcPipeline when CollapseToSinglePipeline is used, in which case this will be ERHIPipeline::All.
- L42 _public member_ `ERHIPipeline DstPipelines;`
- L45 _private function_ `bool NeedToReplaceBeforeInfo() const`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace RHICore` (scope `UE`)

### `Source/Runtime/RHICore/Internal/RHIShaderParametersShared.h` (Internal)


#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace RHICore` (scope `UE`)
- L9 _function_ `inline FRHIDescriptorHandle GetBindlessParameterHandle(const FRHIShaderParameterResource& Parameter)` (scope `UE::RHICore`)

### `Source/Runtime/RHICore/Internal/RHIUniformBufferDataShared.h` (Internal)


#### struct `UE::RHICore::FUniformDataReader`  
`struct FUniformDataReader`  
_L9-21_
- L11 _public prototype_ `FUniformDataReader() = delete;`
- L12 _public function_ `FUniformDataReader(const void* InData) : Data(reinterpret_cast<const uint8*>(InData))`
- L15 _public function_ `template<typename TResourceOut> const TResourceOut& Read(const FRHIUniformBufferResource& InResource) const`
- L20 _public member_ `const uint8* Data;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace RHICore` (scope `UE`)
- L23 _function_ `inline FRHIDescriptorHandle GetBindlessResourceHandle(FUniformDataReader Reader, const FRHIUniformBufferResource& Resource)` (scope `UE::RHICore`)
- L92 _function_ `inline void UpdateUniformBufferConstants(void* DestinationData, const void* SourceData, const FRHIUniformBufferLayout& Layout, bool bAllowBindless = true)` (scope `UE::RHICore`)

### `Source/Runtime/RHICore/Internal/ShaderBinaryUtilities.h` (Internal)


#### struct `UE::ShaderBinaryUtilities::FShaderDebugData`  
`struct FShaderDebugData`  
_L10-15_
- L12 _public member_ `FString FunctionName;`
- L13 _public member_ `FString PDBName;`
- L14 _public member_ `FString Hash;`

#### struct `UE::ShaderBinaryUtilities::DXBC::FHeader`  
`struct FHeader`  
_L23-28_
- L25 _public member_ `uint32 Identifier;`
- L26 _public member_ `uint32 Ignore[6];`
- L27 _public member_ `uint32 ChunkCount;`

#### struct `UE::ShaderBinaryUtilities::DXBC::FChunkHeader`  
`struct FChunkHeader`  
_L30-34_
- L32 _public member_ `uint32 Type;`
- L33 _public member_ `uint32 Size;`

#### struct `UE::ShaderBinaryUtilities::DXIL::FShaderDebugNameInfo`  
`struct FShaderDebugNameInfo`  
_L39-43_
- L41 _public member_ `uint16 Flags;`
- L42 _public member_ `uint16 NameLength;`

#### struct `UE::ShaderBinaryUtilities::DXIL::FShaderHashInfo`  
`struct FShaderHashInfo`  
_L45-49_
- L47 _public member_ `uint32 Flags;`
- L48 _public member_ `uint8 Digest[16];`

#### struct `UE::ShaderBinaryUtilities::DXIL::FPSVRevision3Info`  
`struct FPSVRevision3Info`  
_L51-55_
- L53 _public member_ `uint8 Ignore[48];`
- L54 _public member_ `uint32 EntryNameOffset;`

#### struct `UE::ShaderBinaryUtilities::FParseContext`  
`struct FParseContext`  
_L62-120_
- L64 _public function_ `FParseContext(const void* Start, const uint64 ByteSize) : Start(static_cast<const uint8*>(Start)), ByteSize(ByteSize)`
- L70 _public function_ `template<typename T> T Get()`
- L82 _public function_ `template<typename T> T Consume()`
- L95 _public function_ `FParseContext Split(uint64 InOffset) const`
- L102 _public function_ `void Skip(uint64 InOffset)`
- L107 _public function_ `uint64 PendingBytes() const`
- L112 _public function_ `const void* Data() const`
- L117 _public member_ `const uint8* Start = nullptr;`
- L118 _public member_ `const uint64 ByteSize = 0;`
- L119 _public member_ `uint64 Offset = 0;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace ShaderBinaryUtilities` (scope `UE`)
- L21 _namespace_ `namespace DXBC` (scope `UE::ShaderBinaryUtilities`)
- L37 _namespace_ `namespace DXIL` (scope `UE::ShaderBinaryUtilities`)
- L122 _function_ `static void GetShaderBinaryDebugHashDXBC(const void* ShaderBinary, uint32 ByteSize, FShaderDebugData& OutData)` (scope `UE::ShaderBinaryUtilities`)

### `Source/Runtime/RHICore/Public/BoundShaderStateHistory.h` (Public)


#### class `TBoundShaderStateHistory`  
`template<uint32 Size, bool TThreadSafe = true> class TBoundShaderStateHistory : public FRenderResource`  
_L13-62_
- inherits: `FRenderResource`
- desc: A list of the most recently used bound shader states. This is used to keep bound shader states that have been used recently from being freed, as they're likely to be used again soon.
- L16 _public prototype_ `TBoundShaderStateHistory() = default;`
- L19 _public function_ `inline void Add(FRHIBoundShaderState* BoundShaderState)` — Adds a bound shader state to the history.
- L33 _public function_ `FRHIBoundShaderState* GetLast()`
- L42 _public function_ `virtual void ReleaseRHI()` — FRenderResource interface.
- L59 _private member_ `FBoundShaderStateRHIRef BoundShaderStates[Size];`
- L60 _private member_ `uint32 NextBoundShaderStateIndex = 0;`
- L61 _private member_ `FCriticalSection BoundShaderStateHistoryLock;`

### `Source/Runtime/RHICore/Public/RHICore.h` (Public)


#### struct `UE::RHICore::FResolveTextureInfo`  
`struct FResolveTextureInfo`  
_L13-34_
- L15 _public prototype_ `FResolveTextureInfo() = default;`
- L17 _public function_ `FResolveTextureInfo( FRHITexture* InSourceTexture, FRHITexture* InDestTexture, uint8 InMipLevel, int32 InArraySlice, FResolveRect InResolveRect) : SourceTexture(InSourceTexture) , DestTexture(InDestTexture) , MipLevel(InMipLevel) , ArraySlice(InArraySlice)`
- L29 _public member_ `FRHITexture* SourceTexture = nullptr;`
- L30 _public member_ `FRHITexture* DestTexture = nullptr;`
- L31 _public member_ `uint8 MipLevel = 0;`
- L32 _public member_ `int32 ArraySlice = -1;`
- L33 _public member_ `FResolveRect ResolveRect;`

#### Free symbols / members of external scopes

- L8 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogRHICore, Log, VeryVerbose);`
- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace RHICore` (scope `UE`)
- L36 _prototype_ `void ResolveRenderPassTargets(const FRHIRenderPassInfo& Info, TFunction<void(FResolveTextureInfo)> Function);` (scope `UE::RHICore`)
- L37 _prototype_ `FRHIViewDesc::EDimension AdjustViewInfoDimensionForNarrowing(const FRHIViewDesc::FTexture::FViewInfo& ViewInfo, const FRHITextureDesc& TextureDesc);` (scope `UE::RHICore`)
- L39 _prototype_ `bool AreRayTracingShadersEnabled();` (scope `UE::RHICore`)
- L41 _prototype_ `bool AllowVendorDevice();` (scope `UE::RHICore`)
- L44 _prototype_ `ERHIBindlessConfiguration GetBindlessConfigurationOnStartup(EShaderPlatform Platform);` (scope `UE::RHICore`) — Utility for RHIs to load the bindless configuration before ShaderPlatformConfig is initialized.

### `Source/Runtime/RHICore/Public/RHICoreIntelBreadcrumbs.h` (Public)


#### class `UE::RHICore::Intel::GPUCrashDumps::FMarker`  
`class FMarker`  
_L43-71_
- L46 _private member_ `FRHIBreadcrumb::FBuffer Buffer;`
- L49 _private member_ `void const* Ptr = nullptr;`
- L50 _private member_ `uint32 Size = 0;`
- L53 _public function_ `FMarker(FRHIBreadcrumbNode* Breadcrumb)`
- L67 _public function_ `operator bool() const`
- L69 _public function_ `void* GetPtr () const`
- L70 _public function_ `uint32 GetSize() const`

#### Free symbols / members of external scopes

- L6 _macro_ `# define INTEL_GPU_CRASH_DUMPS 0`
- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace RHICore` (scope `UE`)
- L13 _namespace_ `namespace Intel` (scope `UE::RHICore`)
- L13 _namespace_ `namespace GPUCrashDumps` (scope `UE::RHICore::Intel`)
- L15 _variable_ `static bool bEnabled = false;` (scope `UE::RHICore::Intel::GPUCrashDumps`)
- L16 _variable_ `static uint32 Flags = 0;` (scope `UE::RHICore::Intel::GPUCrashDumps`)
- L19 _prototype_ `bool IsEnabled();` (scope `UE::RHICore::Intel::GPUCrashDumps`) — API
- L24 _prototype_ `void StartupModule();` (scope `UE::RHICore::Intel::GPUCrashDumps`) — Called on RHICore module startup to load the Intel Extensions library
- L29 _prototype_ `void InitializeBeforeDeviceCreation(uint32 DeviceId);` (scope `UE::RHICore::Intel::GPUCrashDumps`) — Called by platform RHIs to activate Intel Breadcrumbs
- L35 _prototype_ `bool OnGPUCrash();` (scope `UE::RHICore::Intel::GPUCrashDumps`) — Called by platform RHIs when a GPU crash is detected. Waits for for the processing to finish.
- L37 _variable_ `static inline constexpr TCHAR RootNodeName[] = TEXT("<ro` (scope `UE::RHICore::Intel::GPUCrashDumps`)

### `Source/Runtime/RHICore/Public/RHICoreNvidiaAftermath.h` (Public)


#### struct `UE::RHICore::Nvidia::Aftermath::FCrashResult`  
`struct FCrashResult`  
_L54-59_
- L56 _public member_ `FString OutputLog;`
- L57 _public member_ `TOptional<FString> DumpPath;`
- L58 _public member_ `TOptional<uint64> GPUFaultAddress;`

#### class `UE::RHICore::Nvidia::Aftermath::FMarker`  
`class FMarker`  
_L73-93_
- L75 _private member_ `void const* Ptr = nullptr;`
- L76 _private member_ `uint32 Size = 0;`
- L79 _public function_ `FMarker(FRHIBreadcrumbNode* Breadcrumb)`
- L89 _public function_ `operator bool() const`
- L91 _public function_ `void* GetPtr () const`
- L92 _public function_ `uint32 GetSize() const`

#### Free symbols / members of external scopes

- L6 _macro_ `#define NV_AFTERMATH 0`
- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace RHICore` (scope `UE`)
- L13 _namespace_ `namespace Nvidia` (scope `UE::RHICore`)
- L13 _namespace_ `namespace Aftermath` (scope `UE::RHICore::Nvidia`)
- L15 _typedef_ `typedef TUniqueFunction<void(float TimeLimitSeconds, uint32 FrameLimit)> FAssociateShadersFunc;` (scope `UE::RHICore::Nvidia::Aftermath`)
- L17 _prototype_ `bool IsEnabled();` (scope `UE::RHICore::Nvidia::Aftermath`)
- L18 _prototype_ `bool IsShaderRegistrationEnabled();` (scope `UE::RHICore::Nvidia::Aftermath`)
- L19 _prototype_ `bool IsResourceTrackingEnabled();` (scope `UE::RHICore::Nvidia::Aftermath`)
- L20 _prototype_ `bool AreMarkersEnabled();` (scope `UE::RHICore::Nvidia::Aftermath`)
- L25 _prototype_ `void InitializeBeforeDeviceCreation();` (scope `UE::RHICore::Nvidia::Aftermath`) — Called by platform RHIs to activate Aftermath.
- L30 _prototype_ `void SetLateShaderAssociateCallback(FAssociateShadersFunc ShaderAssociateFunc = {});` (scope `UE::RHICore::Nvidia::Aftermath`) — Called by the crash handler to associate shaders after a GPU fault
- L36 _prototype_ `bool InitializeDevice(TFunctionRef<uint32(uint32 AftermathFeatureFlags)> InitCallback);` (scope `UE::RHICore::Nvidia::Aftermath`) — Called by platform RHIs after device creation. InitCallback should return an Aftermath result value.
- L38 _typedef_ `using FShaderHash = uint64;` (scope `UE::RHICore::Nvidia::Aftermath`)
- L40 _variable_ `static constexpr FShaderHash InvalidShaderHash = UINT64_MAX;` (scope `UE::RHICore::Nvidia::Aftermath`)
- L46 _prototype_ `FShaderHash RegisterShaderBinary(const void* ShaderBinary, uint32 ByteSize, const FStringView& DebugName = nullptr);` (scope `UE::RHICore::Nvidia::Aftermath`) — Register a new shader binary with Aftermath, must be valid. Returns the internal shader hash, must be deregistered with DeregisterShaderBinary
- L52 _prototype_ `void DeregisterShaderBinary(FShaderHash Hash);` (scope `UE::RHICore::Nvidia::Aftermath`) — Deregister a shader binary from its hash. Will not release it immediately, but instead enqueue it for later eviction once the GPU work is done.
- L65 _prototype_ `bool OnGPUCrash(TArray<FCrashResult>& OutResults);` (scope `UE::RHICore::Nvidia::Aftermath`) — Called by platform RHIs when a GPU crash is detected. Waits for Aftermath to finish crash dump processing, then returns the result.
- L67 _variable_ `static inline constexpr TCHAR RootNodeName[] = TEXT("<ro` (scope `UE::RHICore::Nvidia::Aftermath`)

### `Source/Runtime/RHICore/Public/RHICoreShader.h` (Public)


#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L15 _namespace_ `namespace RHICore` (scope `UE`)
- L19 _prototype_ `extern void ValidateStaticUniformBuffer(FRHIUniformBuffer* UniformBuffer, FUniformBufferStaticSlot Slot, uint32 ExpectedHash);` (scope `UE::RHICore`) — Validates that the uniform buffer at the requested static slot.
- L20 _prototype_ `extern void SetupShaderCodeValidationData(FRHIShader* RHIShader, class FShaderCodeReader& ShaderCodeReader);` (scope `UE::RHICore`)
- L21 _prototype_ `extern void SetupShaderDiagnosticData(FRHIShader* RHIShader, class FShaderCodeReader& ShaderCodeReader);` (scope `UE::RHICore`)
- L22 _prototype_ `extern void RegisterDiagnosticMessages(const TArray<FShaderDiagnosticData>& In);` (scope `UE::RHICore`)
- L23 _prototype_ `extern const FString* GetDiagnosticMessage(uint32 MessageID);` (scope `UE::RHICore`)
- L27 _prototype_ `extern void DispatchShaderBundleEmulation( FRHIComputeCommandList& InRHICmdList, FRHIShaderBundle* ShaderBundle, FRHIBuffer* ArgumentBuffer, TConstArrayView<FRHIShaderParameterResource> SharedBindlessParameters, TConstArrayView<FRHIShaderBundleComputeDispatch> Dispatches );` (scope `UE::RHICore`)
- L35 _prototype_ `extern void DispatchShaderBundleEmulation( FRHICommandList& InRHICmdList, FRHIShaderBundle* ShaderBundle, FRHIBuffer* ArgumentBuffer, const FRHIShaderBundleGraphicsState& BundleState, TConstArrayView<FRHIShaderParameterResource> SharedBindlessParameters, TConstArrayView<FRHIShaderBundleGraphicsDispatch> Dispatches );` (scope `UE::RHICore`)
- L44 _function_ `inline void InitStaticUniformBufferSlots(FRHIShaderData* ShaderData)` (scope `UE::RHICore`)
- L65 _function_ `template <typename TApplyFunction> void ApplyStaticUniformBuffers( const FRHIShader* Shader, const TArray<FRHIUniformBuffer*>& UniformBuffers, TApplyFunction&& ApplyFunction )` (scope `UE::RHICore`)
- L95 _function_ `template <typename TRHIContext, typename TRHIShader> void ApplyStaticUniformBuffers( TRHIContext* CommandContext, const TRHIShader* Shader, const TArray<FRHIUniformBuffer*>& UniformBuffers)` (scope `UE::RHICore`)
- L102 _function_ `` (scope `UE::RHICore::ApplyStaticUniformBuffers`)

### `Source/Runtime/RHICore/Public/RHICoreTransientResourceAllocator.h` (Public)


#### struct `FRHITransientResourceStats`  
`struct FRHITransientResourceStats`  
_L52-86_
- desc: Tracks allocation statistics for buffer or texture resources.
- L54 _public prototype_ `FRHITransientResourceStats() = default;`
- L56 _public function_ `void Add(const FRHITransientResourceStats& Other)`
- L64 _public function_ `void Allocate(uint64 Size)`
- L70 _public function_ `void Deallocate(uint64 Size)`
- L76 _public member_ `uint64 AllocatedSize = 0;` — The number of bytes allocated from the transient allocator this cycle.
- L79 _public member_ `uint32 AllocationCount = 0;` — The number of allocations made from the transient allocator this cycle.
- L82 _public member_ `uint32 DeallocationCount = 0;` — the number of deallocations made from the transient allocator this cycle.
- L85 _public member_ `uint32 CreateCount = 0;` — The number of resource creations made from the transient allocator this cycle.

#### struct `FRHITransientMemoryStats`  
`struct FRHITransientMemoryStats`  
_L89-146_
- desc: Tracks all transient memory statistics for the current allocation cycle and reports results to various profilers.
- L92 _public prototype_ `FRHITransientMemoryStats() = default;`
- L94 _public function_ `void Accumulate(const FRHITransientMemoryStats& Other)`
- L101 _public function_ `void AllocateTexture(uint64 Size)`
- L108 _public function_ `void DeallocateTexture(uint64 Size)`
- L114 _public function_ `void AllocateBuffer(uint64 Size)`
- L121 _public function_ `void DeallocateBuffer(uint64 Size)`
- L127 _public function_ `void Reset()`
- L134 _public prototype_ `void Submit(uint64 TotalMemoryCapacity);`
- L136 _public function_ `bool HasDeallocations() const`
- L138 _public member_ `FRHITransientResourceStats Textures;`
- L139 _public member_ `FRHITransientResourceStats Buffers;`
- L142 _public member_ `uint64 AliasedSizeCurrent = 0;` — Total allocated memory usage with aliasing.
- L145 _public member_ `uint64 AliasedSize = 0;` — Current aliased size as items are being allocated / deallocated.

#### class `TRHITransientResourceCache`  
`template <typename TransientResourceType> class TRHITransientResourceCache`  
_L154-295_
- desc: An RHI transient resource cache designed to optimize fetches for resources placed into a heap with an offset. The cache has a fixed capacity whereby no garbage collection will occur. Once that capacity is exceeded, garbage collection is invoked on resources older than a specified generation (where generation is incremented with each cycle of forfeiting acquired resources).
- L157 _public member_ `static const uint32 kInfinity = ~0u;`
- L158 _public member_ `static const uint32 kDefaultCapacity = kInfinity;`
- L159 _public member_ `static const uint32 kDefaultGarbageCollectLatency = 32;`
- L161 _public function_ `TRHITransientResourceCache( uint32 InCapacity = kDefaultCapacity, uint32 InGarbageCollectLatency = kDefaultGarbageCollectLatency) : GarbageCollectLatency(InGarbageCollectLatency) , Capacity(InCapacity)`
- L173 _public function_ `~TRHITransientResourceCache()`
- L187 _public function_ `template <typename CreateFunctionType> TransientResourceType* Acquire(uint64 Hash, CreateFunctionType CreateFunction)`
- L211 _public function_ `template <typename ReleaseFunctionType> void Forfeit(uint64 CurrentFrameIndex, ReleaseFunctionType ReleaseFunction)`
- L240 _public function_ `void Forfeit(uint64 CurrentFrameIndex)`
- L245 _public function_ `TConstArrayView<TransientResourceType*> GetAllocated() const`
- L247 _public function_ `uint32 GetAllocatedCount() const`
- L249 _public function_ `uint32 GetSize() const`
- L251 _public function_ `uint32 GetCapacity() const`
- L253 _public function_ `uint32 GetHitCount() const`
- L255 _public function_ `uint32 GetMissCount() const`
- L257 _public function_ `float GetHitPercentage() const`
- L261 _private function_ `template <typename ReleaseFunctionType> bool TryReleaseItem(uint64 CurrentFrameIndex, ReleaseFunctionType ReleaseFunction)`
- L289 _private member_ `TArray<FCacheItem> Cache;`
- L290 _private member_ `TArray<TransientResourceType*> Allocated;`
- L291 _private member_ `uint32 GarbageCollectLatency;`
- L292 _private member_ `uint32 Capacity;`
- L293 _private member_ `uint32 HitCount = 0;`
- L294 _private member_ `uint32 MissCount = 0;`

#### struct `TRHITransientResourceCache::FCacheItem`  
`struct FCacheItem`  
_L276-287_
- L278 _public function_ `FCacheItem(TransientResourceType* InResource, uint64 InHash, uint64 InLastUsedFrame) : Resource(InResource) , Hash(InHash) , LastUsedFrame(InLastUsedFrame)`
- L284 _public member_ `TransientResourceType* Resource;`
- L285 _public member_ `uint64 Hash{};`
- L286 _public member_ `uint64 LastUsedFrame{};`

#### class `IRHITransientMemoryCache`  
`class IRHITransientMemoryCache`  
_L300-306_
- desc: Abstract base class for memory caching, providing a common garbage collection method.
- L303 _public prototype_ `virtual ~IRHITransientMemoryCache() = default;`
- L305 _public prototype_ `virtual void GarbageCollect() = 0;`

#### class `FRHITransientHeapAllocator`  
`class FRHITransientHeapAllocator`  
_L316-438_
- desc: First-fit allocator used for placing resources on a heap.
- L331 _public prototype_ `FRHITransientHeapAllocator(uint64 Capacity, uint32 Alignment);`
- L333 _public prototype_ `FRHITransientHeapAllocation Allocate(const FRHITransientAllocationFences& Fences, uint64 Size, uint32 Alignment, TArray<FAliasingOverlap>& OutAliasingOverlaps);`
- L335 _public prototype_ `void Deallocate(FRHITransientResource* Resource, const FRHITransientAllocationFences& Fences);`
- L337 _public prototype_ `void Flush();`
- L339 _public function_ `void SetGpuVirtualAddress(uint64 InGpuVirtualAddress)`
- L344 _public function_ `uint64 GetGpuVirtualAddress() const`
- L345 _public function_ `uint64 GetCapacity() const`
- L346 _public function_ `uint64 GetUsedSize() const`
- L347 _public function_ `uint64 GetFreeSize() const`
- L348 _public function_ `uint64 GetAlignmentWaste() const`
- L349 _public function_ `uint32 GetAllocationCount() const`
- L351 _public function_ `bool IsFull() const`
- L352 _public function_ `bool IsEmpty() const`
- L355 _private typedef_ `using FRangeHandle = uint16;`
- L356 _private member_ `static const FRangeHandle InvalidRangeHandle = FRangeHandle(~0);`
- L371 _private function_ `inline FRangeHandle GetFirstFreeRangeHandle()`
- L376 _private function_ `FRangeHandle CreateRange()`
- L386 _private function_ `FRangeHandle InsertRange(FRangeHandle PreviousHandle, FRHITransientResource* Resource, const FRHITransientAllocationFences& Fences, uint64 Offset, uint64 Size)`
- L403 _private function_ `FRangeHandle RemoveRange(FRangeHandle PreviousHandle, FRangeHandle CurrentHandle)`
- L426 _private prototype_ `void Validate();`
- L428 _private member_ `uint64 GpuVirtualAddress = 0;`
- L429 _private member_ `uint64 Capacity = 0;`
- L430 _private member_ `uint64 UsedSize = 0;`
- L431 _private member_ `uint64 AlignmentWaste = 0;`
- L432 _private member_ `uint32 AllocationCount = 0;`
- L433 _private member_ `uint32 AlignmentMin = 0;`
- L435 _private member_ `FRangeHandle HeadHandle = InvalidRangeHandle;`
- L436 _private member_ `TArray<FRangeHandle> RangeFreeList;`
- L437 _private member_ `TArray<FRange> Ranges;`

#### struct `FRHITransientHeapAllocator::FAliasingOverlap`  
`struct FAliasingOverlap`  
_L319-329_
- L321 _public prototype_ `FAliasingOverlap() = default;`
- L322 _public function_ `FAliasingOverlap(FRHITransientResource* InResource, uint32 InAcquireFence) : Resource(InResource) , AcquireFence(InAcquireFence)`
- L327 _public member_ `FRHITransientResource* Resource;`
- L328 _public member_ `uint32 AcquireFence;`

#### struct `FRHITransientHeapAllocator::FRange`  
`struct FRange`  
_L358-369_
- L360 _public member_ `FRHITransientResource* Resource = nullptr;`
- L361 _public member_ `FRHITransientAllocationFences Fences;`
- L362 _public member_ `uint64 Size = 0;`
- L363 _public member_ `uint64 Offset = 0;`
- L364 _public member_ `FRangeHandle NextFreeHandle = InvalidRangeHandle;`
- L365 _public member_ `FRangeHandle PrevFreeHandle = InvalidRangeHandle;`
- L367 _public function_ `inline uint64 GetStart() const`
- L368 _public function_ `inline uint64 GetEnd() const`

#### struct `FRHITransientHeapAllocator::FFindResult`  
`struct FFindResult`  
_L419-424_
- L421 _public member_ `uint64 LeftoverSize = 0;`
- L422 _public member_ `FRangeHandle PreviousHandle = InvalidRangeHandle;`
- L423 _public member_ `FRangeHandle FoundHandle = InvalidRangeHandle;`

#### enum `ERHITransientHeapFlags`  
`enum class ERHITransientHeapFlags : uint8`  
_L442-458_
- L445 _public enumerator_ `AllowBuffers = 1 << 0` — Supports placing buffers onto the heap.
- L448 _public enumerator_ `AllowTextures = 1 << 1` — Supports placing textures with UAV support onto the heap.
- L451 _public enumerator_ `AllowRenderTargets = 1 << 2` — Supports placing render targets onto the heap.
- L454 _public enumerator_ `AllowNNEBuffers = 1 << 3` — Supports placing NNE accessible buffers onto the heap.  Differentiation is required for DirectML with multi-GPU.
- L457 _public enumerator_ `AllowAll = AllowBuffers | AllowTextures | AllowRenderTargets | AllowNNEBuffers` — Supports all resource types.

#### class `FRHITransientHeap`  
`class FRHITransientHeap`  
_L466-591_
- desc: The base class for a platform heap implementation. Transient resources are placed on the heap at specific byte offsets. Each heap additionally contains a cache of RHI transient resources, each with its own RHI resource and cache of RHI views. The lifetime of the resource cache is tied to the heap.
- L505 _public typedef_ `using FCreateTextureFunction = TFunction<FRHITransientTexture* (const FResourceInitializer&)>;`
- L506 _public typedef_ `using FCreateBufferFunction = TFunction<FRHITransientBuffer* (const FResourceInitializer&)>;`
- L508 _public function_ `FRHITransientHeap(const FInitializer& InInitializer) : Initializer(InInitializer) , Allocator(InInitializer.Size, InInitializer.Alignment) , AlignmentLog2(FPlatformMath::CeilLogTwo64(InInitializer.Alignment)) , Textures(InInitializer.TextureCacheSize) , Buffers(InInitializer.BufferCacheSize)`
- L518 _public prototype_ `virtual ~FRHITransientHeap() = default;`
- L520 _public prototype_ `FRHITransientTexture* CreateTexture( const FRHITextureCreateInfo& CreateInfo, const TCHAR* DebugName, const FRHITransientAllocationFences& Fences, uint64 CurrentAllocatorCycle, uint64 TextureSize, uint32 TextureAlignment, FCreateTextureFunction CreateTextureFunction);`
- L529 _public prototype_ `void DeallocateMemory(FRHITransientTexture* Texture, const FRHITransientAllocationFences& Fences);`
- L531 _public prototype_ `FRHITransientBuffer* CreateBuffer( const FRHIBufferCreateInfo& CreateInfo, const TCHAR* DebugName, const FRHITransientAllocationFences& Fences, uint64 CurrentAllocatorCycle, uint64 BufferSize, uint32 BufferAlignment, FCreateBufferFunction CreateBufferFunction);`
- L540 _public prototype_ `void DeallocateMemory(FRHITransientBuffer* Buffer, const FRHITransientAllocationFences& Fences);`
- L542 _public prototype_ `void Flush(uint64 CurrentAllocatorCycle, FRHITransientMemoryStats& OutMemoryStats, FRHITransientAllocationStats* OutAllocationStats);`
- L544 _public function_ `const FInitializer& GetInitializer() const`
- L546 _public function_ `uint64 GetCapacity() const`
- L548 _public function_ `uint64 GetGPUVirtualAddress() const`
- L550 _public function_ `uint64 GetLastUsedGarbageCollectCycle() const`
- L552 _public function_ `uint64 GetCommitSize() const`
- L554 _public function_ `bool IsEmpty() const`
- L556 _public function_ `bool IsFull() const`
- L558 _public function_ `bool IsCommitRequired() const`
- L560 _public function_ `bool IsAllocationSupported(uint64 Size, ERHITransientHeapFlags Flags) const`
- L566 _protected function_ `void SetGpuVirtualAddress(uint64 InBaseGPUVirtualAddress)`
- L572 _private prototype_ `void AllocateMemoryInternal(FRHITransientResource* Resource, const FRHITransientHeapAllocation& Allocation);`
- L573 _private prototype_ `void DeallocateMemoryInternal(FRHITransientResource* Resource, const FRHITransientAllocationFences& Fences);`
- L575 _private member_ `FInitializer Initializer;`
- L576 _private member_ `FRHITransientHeapAllocator Allocator;`
- L578 _private member_ `uint64 LastUsedGarbageCollectCycle = 0;`
- L579 _private member_ `uint64 CommitSize = 0;`
- L580 _private member_ `std::atomic<uint64> CommitSizeMax{0};`
- L581 _private member_ `uint32 AlignmentLog2;`
- L583 _private member_ `TArray<FRHITransientHeapAllocator::FAliasingOverlap> AliasingOverlaps;`
- L585 _private member_ `FRHITransientMemoryStats Stats;`
- L586 _private member_ `TRHITransientResourceCache<FRHITransientTexture> Textures;`
- L587 _private member_ `TRHITransientResourceCache<FRHITransientBuffer> Buffers;`

#### struct `FRHITransientHeap::FInitializer`  
`struct FInitializer`  
_L469-485_
- L472 _public member_ `uint64 Size = 0;` — Size of the heap in bytes.
- L475 _public member_ `uint32 Alignment = 0;` — Alignment of the heap in bytes.
- L478 _public member_ `ERHITransientHeapFlags Flags = ERHITransientHeapFlags::AllowAll;` — Flags used to filter resource allocations within the heap.
- L481 _public member_ `uint32 TextureCacheSize = 0;` — Size of the texture cache before elements are evicted.
- L484 _public member_ `uint32 BufferCacheSize = 0;` — Size of the buffer cache before elements are evicted.

#### struct `FRHITransientHeap::FResourceInitializer`  
`struct FResourceInitializer`  
_L487-503_
- L489 _public function_ `FResourceInitializer(const FRHITransientHeapAllocation& InAllocation, uint64 InHash) : Heap(*InAllocation.Heap) , Allocation(InAllocation) , Hash(InHash)`
- L496 _public member_ `FRHITransientHeap& Heap;` — The heap on which to create the resource.
- L499 _public member_ `const FRHITransientHeapAllocation& Allocation;` — The allocation (offset / size) on the provided heap.
- L502 _public member_ `const uint64 Hash;` — The unique hash computed from the create info and allocation offset.

#### class `FRHITransientHeapCache`  
`class FRHITransientHeapCache : public IRHITransientMemoryCache`  
_L602-676_
- inherits: `IRHITransientMemoryCache`
- desc: The RHI transient heap system is a base class for the platform implementation. It has a persistent lifetime and contains a cache of transient heaps. The transient allocator acquires heaps from the system and forfeits them at the end of its lifetime. Garbage collection of heaps is done using an internal counter that increments with each GarbageCollect call. This should be done periodically. Heaps older than a platform-specified fence latency are destroyed. Additionally, statistics are gathered automatically and reported to the 'rhitransientmemory' stats group.
- L637 _public function_ `FRHITransientHeapCache(const FInitializer& InInitializer) : Initializer(InInitializer)`
- L641 _public prototype_ `virtual ~FRHITransientHeapCache();`
- L643 _public prototype_ `FRHITransientHeap* Acquire(uint64 FirstAllocationSize, ERHITransientHeapFlags FirstAllocationHeapFlags);`
- L645 _public prototype_ `void Forfeit(TConstArrayView<FRHITransientHeap*> Heaps);`
- L647 _public prototype_ `void GarbageCollect() override;`
- L649 _public function_ `const FInitializer& GetInitializer() const`
- L651 _public function_ `uint64 GetGarbageCollectCycle() const`
- L653 _public function_ `uint64 GetHeapSize(uint64 RequestedHeapSize) const`
- L663 _private prototype_ `virtual FRHITransientHeap* CreateHeap(const FRHITransientHeap::FInitializer& Initializer) = 0;` — Called when a new heap is being created and added to the pool.
- L667 _private member_ `FInitializer Initializer;`
- L668 _private member_ `FRHITransientMemoryStats Stats;`
- L670 _private member_ `FCriticalSection CriticalSection;`
- L671 _private member_ `TArray<FRHITransientHeap*> LiveList;`
- L672 _private member_ `TArray<FRHITransientHeap*> FreeList;`
- L673 _private member_ `uint64 GarbageCollectCycle = 0;`

#### struct `FRHITransientHeapCache::FInitializer`  
`struct FInitializer`  
_L605-635_
- L608 _public prototype_ `static FInitializer CreateDefault();` — Creates a default initializer using common RHI CVars.
- L610 _public member_ `static const uint32 kDefaultResourceCacheSize = 256;`
- L613 _public member_ `uint64 MinimumFirstHeapSize = 0;` — The minimum size to use when creating the first heap. This is the default but can grow based on allocations.
- L616 _public member_ `uint64 MinimumHeapSize = 0;` — The minimum size to use when creating a heap. This is the default but can grow based on allocations.
- L619 _public member_ `uint32 HeapAlignment = 0;` — The minimum alignment for resources in the heap.
- L622 _public member_ `uint32 GarbageCollectLatency = 0;` — The latency between the completed fence value and the used fence value to invoke garbage collection of the heap.
- L625 _public member_ `uint32 TextureCacheSize = kDefaultResourceCacheSize;` — Size of the texture cache before elements are evicted.
- L628 _public member_ `uint32 BufferCacheSize = kDefaultResourceCacheSize;` — Size of the buffer cache before elements are evicted.
- L631 _public member_ `bool bSupportsAllHeapFlags = true;` — Whether all heaps should be created with the AllowAll heap flag.
- L634 _public member_ `bool bSupportsVirtualMapping = false;` — Whether all heaps support mapping physical pages to the commit size. If false the physical memory usage is represented by the capacity instead.

#### class `FRHITransientResourceHeapAllocator`  
`class FRHITransientResourceHeapAllocator : public IRHITransientResourceAllocator`  
_L679-752_
- inherits: `IRHITransientResourceAllocator`
- desc: A base class for implementing IRHITransientResourceAllocator for a virtual aliasing placed resource heap allocation strategy.
- L682 _public prototype_ `FRHITransientResourceHeapAllocator(FRHITransientHeapCache& InHeapCache);`
- L683 _public prototype_ `~FRHITransientResourceHeapAllocator();`
- L686 _public prototype_ `void SetCreateMode(ERHITransientResourceCreateMode InCreateMode) override;` — Sets the create mode for allocations.
- L689 _public prototype_ `void DeallocateMemory(FRHITransientTexture* Texture, const FRHITransientAllocationFences& Fences) override;` — Deallocates a texture from its parent heap. Provide the current platform fence value used to update the heap.
- L692 _public prototype_ `void DeallocateMemory(FRHITransientBuffer* Buffer, const FRHITransientAllocationFences& Fences) override;` — Deallocates a buffer from its parent heap. Provide the current platform fence value used to update the heap.
- L695 _public prototype_ `void Flush(FRHICommandListImmediate& RHICmdList, FRHITransientAllocationStats* OutAllocationStats) override;` — Called to flush any active allocations prior to rendering.
- L698 _public function_ `inline TConstArrayView<FRHITransientHeap*> GetHeaps() const` — Returns the array of heaps used by this allocator, including the required commit size for each.
- L700 _public member_ `FRHITransientHeapCache& HeapCache;`
- L703 _public function_ `template <typename TransientResourceType, typename LambdaType, typename ResourceCreateInfo> TransientResourceType* CreateTransientResource(LambdaType&& Lambda, uint64 Hash, uint64 Size, const ResourceCreateInfo& CreateInfo)`
- L724 _protected prototype_ `FRHITransientTexture* CreateTextureInternal( const FRHITextureCreateInfo& CreateInfo, const TCHAR* DebugName, const FRHITransientAllocationFences& Fences, uint64 TextureSize, uint32 TextureAlignment, FRHITransientHeap::FCreateTextureFunction CreateTextureFunction);` — Allocates a texture on a heap at a specific offset, returning a cached RHI transient texture pointer, or null if the allocation failed. TextureSize and TextureAlignment are platform specific and must be derived from the texture create info and passed in, along with a platform-specific texture creation function if no cached resource if found.
- L737 _protected prototype_ `FRHITransientBuffer* CreateBufferInternal( const FRHIBufferCreateInfo& CreateInfo, const TCHAR* DebugName, const FRHITransientAllocationFences& Fences, uint32 BufferSize, uint32 BufferAlignment, FRHITransientHeap::FCreateBufferFunction CreateBufferFunction);` — Allocates a buffer on a heap at a specific offset, returning a cached RHI transient buffer pointer, or null if the allocation failed. BufferSize and BufferAlignment are platform specific and must be derived from the buffer create info and passed in, along with a platform-specific buffer creation function if no cached resource if found.
- L746 _private member_ `TArray<FRHITransientHeap*> Heaps;`
- L747 _private member_ `uint64 CurrentCycle = 0;`
- L748 _private member_ `uint32 DeallocationCount = 0;`
- L749 _private member_ `ERHITransientResourceCreateMode CreateMode = ERHITransientResourceCreateMode::Inline;`
- L751 _private prototype_ `IF_RHICORE_TRANSIENT_ALLOCATOR_DEBUG(TSet<FRHITransientResource*> ActiveResources);`

#### class `FRHITransientPageSpanAllocator`  
`class FRHITransientPageSpanAllocator`  
_L762-882_
- desc: Allocates page spans for a resource.
- L765 _public function_ `FRHITransientPageSpanAllocator(uint32 InPageCount, uint32 InPageSize) : MaxSpanCount(InPageCount + 2) , MaxPageCount(InPageCount) , PageSize(InPageSize)`
- L773 _public prototype_ `void Reset();`
- L775 _public prototype_ `bool Allocate(FRHITransientResource* Resource, const FRHITransientAllocationFences& Fences, uint32 PageCount, uint32& NumPagesAllocated, uint32& OutSpanIndex);`
- L777 _public prototype_ `void Deallocate(FRHITransientResource* Resource, const FRHITransientAllocationFences& Fences, uint32 SpanIndex);`
- L779 _public prototype_ `void Flush();`
- L782 _public function_ `template <typename SpanArrayType> void GetSpanArray(uint32 SpanIndex, SpanArrayType& OutPageSpans) const`
- L792 _public function_ `uint32 GetAllocationCount() const`
- L794 _public function_ `uint32 GetFreePageCount() const`
- L796 _public function_ `uint64 GetUsedSize() const`
- L798 _public function_ `uint64 GetFreeSize() const`
- L800 _public prototype_ `uint32 GetAllocationPageCount(uint32 SpanIndex) const;`
- L802 _public function_ `uint32 GetMaxSpanCount() const`
- L804 _public function_ `uint32 GetPageSize() const`
- L806 _public function_ `uint64 GetCapacity() const`
- L808 _public function_ `bool IsFull() const`
- L810 _public function_ `bool IsEmpty() const`
- L813 _private member_ `static const uint32 InvalidIndex = TNumericLimits<uint32>::Max();`
- L814 _private member_ `static const uint32 FreeSpanListHeadIndex = 0;`
- L815 _private member_ `static const uint32 FreeSpanListTailIndex = 1;`
- L828 _private prototype_ `void Init();`
- L831 _private prototype_ `void SplitSpan(uint32 SpanIndex, uint32 PageCount);` — Splits a span into two, so that the original span has PageCount pages and the new span contains the remaining ones
- L834 _private prototype_ `void MergeSpans(uint32 SpanIndex0, uint32 SpanIndex1);` — Merges two spans. They must be adjacent and in the same list
- L837 _private prototype_ `void InsertAfter(uint32 InsertPosition, uint32 InsertSpanIndex);` — Inserts a span after an existing span. The span to insert must be unlinked
- L840 _private prototype_ `void InsertBefore(uint32 InsertPosition, uint32 InsertSpanIndex);` — Inserts a span after an existing span. The span to insert must be unlinked
- L843 _private prototype_ `void Unlink(uint32 SpanIndex);` — Removes a span from its list, reconnecting neighbouring list elements
- L846 _private function_ `int AllocSpan()` — Allocates an unused span from the pool
- L855 _private function_ `void ReleaseSpan(uint32 SpanIndex)` — Releases a span back to the unused pool
- L863 _private prototype_ `void Validate();`
- L865 _private function_ `uint32 GetFirstSpanIndex() const`
- L870 _private member_ `TArray<int32> PageToSpanStart;` — [PAGE_COUNT + 1]
- L871 _private member_ `TArray<int32> PageToSpanEnd;` — [PAGE_COUNT + 1]
- L872 _private member_ `TArray<FPageSpan> PageSpans;` — [MAX_SPAN_COUNT]
- L873 _private member_ `TArray<int32> UnusedSpanList;` — [MAX_SPAN_COUNT]
- L875 _private member_ `uint32 FreePageCount;`
- L876 _private member_ `uint32 UnusedSpanListCount;`
- L878 _private member_ `const uint32 MaxSpanCount;`
- L879 _private member_ `const uint32 MaxPageCount;`
- L880 _private member_ `const uint32 PageSize;`
- L881 _private member_ `uint32 AllocationCount;`

#### struct `FRHITransientPageSpanAllocator::FPageSpan`  
`struct FPageSpan : FRHITransientPageSpan`  
_L817-826_
- inherits: `FRHITransientPageSpan`
- L819 _public function_ `const bool IsLinked()`
- L821 _public member_ `FRHITransientResource* Resource = nullptr;`
- L822 _public member_ `FRHITransientAllocationFences Fences;`
- L823 _public member_ `uint32 NextSpanIndex = InvalidIndex;`
- L824 _public member_ `uint32 PrevSpanIndex = 0;`
- L825 _public member_ `bool bAllocated = false;`

#### class `FRHITransientPagePool`  
`class FRHITransientPagePool`  
_L886-1008_
- L895 _public function_ `FRHITransientPagePool(const FInitializer& InInitializer) : Initializer(InInitializer) , Allocator(Initializer.PageCount, Initializer.PageSize)`
- L900 _public prototype_ `virtual ~FRHITransientPagePool() = default;`
- L937 _public prototype_ `void Allocate(FAllocationContext& AllocationContext);`
- L939 _public function_ `void Deallocate(FRHITransientResource* Resource, const FRHITransientAllocationFences& Fences, uint32 SpanIndex)`
- L944 _public prototype_ `void Flush(FRHICommandListImmediate& RHICmdList);`
- L946 _public function_ `uint64 GetLastUsedGarbageCollectCycle() const`
- L948 _public function_ `bool IsEmpty() const`
- L950 _public function_ `bool IsFull() const`
- L952 _public function_ `uint64 GetCapacity() const`
- L954 _public function_ `uint64 GetGpuVirtualAddress() const`
- L980 _public member_ `const FInitializer Initializer;`
- L983 _protected function_ `void SetGpuVirtualAddress(uint64 InGpuVirtualAddress)`
- L993 _private prototype_ `virtual void Flush(FRHICommandListImmediate& RHICmdList, TArray<FPageMapRequest>&& InPageMapRequests, TArray<FRHITransientPageSpan>&& InPageSpans) = 0;`
- L997 _private member_ `FRHITransientPageSpanAllocator Allocator;`
- L999 _private member_ `TArray<FPageMapRequest> PageMapRequests;`
- L1000 _private member_ `TArray<FRHITransientPageSpan> PageSpans;`
- L1001 _private member_ `uint64 GpuVirtualAddress = 0;`
- L1002 _private member_ `uint64 LastUsedGarbageCollectCycle = 0;`
- L1003 _private member_ `uint32 PageMapRequestCountMax = 0;`
- L1004 _private member_ `uint32 PageSpanCountMax = 0;`

#### struct `FRHITransientPagePool::FInitializer`  
`struct FInitializer`  
_L889-893_
- L891 _public member_ `uint32 PageCount = 0;`
- L892 _public member_ `uint32 PageSize = 0;`

#### struct `FRHITransientPagePool::FAllocationContext`  
`struct FAllocationContext`  
_L902-935_
- L904 _public function_ `FAllocationContext(FRHITransientResource& InResource, const FRHITransientAllocationFences& InFences, uint32 InPageSize) : Resource(InResource) , Allocations(InResource.GetPageAllocation().PoolAllocations) , Spans(InResource.GetPageAllocation().Spans) , AllocationsBefore(Allocations) , GpuVirtualAddress(Resource.GetGpuVirtualAddress()) , Size(Align(Resource.GetSize(), InPageSize)) , Fences(InFences) , PagesRemaining(Size / InPageSize)`
- L918 _public function_ `bool IsComplete() const`
- L920 _public member_ `FRHITransientResource& Resource;`
- L921 _public member_ `TArray<FRHITransientPagePoolAllocation>& Allocations;`
- L922 _public member_ `TArray<FRHITransientPageSpan>& Spans;`
- L923 _public member_ `const TArray<FRHITransientPagePoolAllocation, TInlineAllocator<8>> AllocationsBefore;`
- L924 _public member_ `const uint64 GpuVirtualAddress;`
- L925 _public member_ `const uint64 Size;`
- L926 _public member_ `const FRHITransientAllocationFences Fences;`
- L928 _public member_ `uint32 AllocationCount = 0;`
- L929 _public member_ `uint32 AllocationMatchingCount = 0;`
- L930 _public member_ `uint32 PagesRemaining = 0;`
- L931 _public member_ `uint32 MaxAllocationPage = 0;`
- L932 _public member_ `uint32 PagesAllocated = 0;`
- L933 _public member_ `uint32 PageSpansAllocated = 0;`
- L934 _public member_ `uint32 PagesMapped = 0;`

#### struct `FRHITransientPagePool::FPageMapRequest`  
`struct FPageMapRequest`  
_L956-978_
- L958 _public prototype_ `FPageMapRequest() = default;`
- L960 _public function_ `FPageMapRequest( uint64 InDestinationAddress, uint64 InSourcePagePoolAddress, uint32 InSourcePageCount, uint32 InPageSpanOffset, uint32 InPageSpanCount) : DestinationAddress(InDestinationAddress) , SourcePagePoolAddress(InSourcePagePoolAddress) , SourcePageCount(InSourcePageCount) , PageSpanOffset(InPageSpanOffset) , PageSpanCount(InPageSpanCount)`
- L973 _public member_ `uint64 DestinationAddress = 0;`
- L974 _public member_ `uint64 SourcePagePoolAddress = 0;`
- L975 _public member_ `uint32 SourcePageCount = 0;`
- L976 _public member_ `uint32 PageSpanOffset = 0;`
- L977 _public member_ `uint32 PageSpanCount = 0;`

#### class `FRHITransientPagePoolCache`  
`class FRHITransientPagePoolCache : public IRHITransientMemoryCache`  
_L1012-1084_
- inherits: `IRHITransientMemoryCache`
- L1041 _public function_ `FRHITransientPagePoolCache(const FInitializer& InInitializer) : Initializer(InInitializer)`
- L1045 _public prototype_ `FRHITransientPagePoolCache(const FRHITransientPagePoolCache&) = delete;`
- L1047 _public prototype_ `virtual ~FRHITransientPagePoolCache();`
- L1050 _public prototype_ `FRHITransientPagePool* Acquire();` — Called by the transient allocator to acquire a page pool from the cache.
- L1053 _public prototype_ `FRHITransientPagePool* GetFastPagePool();` — Called by the transient allocator to return the fast page pool if it exists.
- L1056 _public prototype_ `void Forfeit(TConstArrayView<FRHITransientPagePool*> PagePools);` — Called by the transient allocator to forfeit all acquired heaps back to the cache.
- L1058 _public prototype_ `void GarbageCollect() override;`
- L1060 _public member_ `const FInitializer Initializer;`
- L1067 _private function_ `virtual FRHITransientPagePool* CreateFastPagePool()` — Called to access the dedicated fast VRAM page pool, if it exists on the platform.
- L1070 _private prototype_ `virtual FRHITransientPagePool* CreatePagePool(const FRHITransientPagePool::FInitializer& Initializer) = 0;` — Called when a new heap is being created and added to the pool.
- L1074 _private member_ `FRHITransientMemoryStats Stats;`
- L1076 _private member_ `FCriticalSection CriticalSection;`
- L1077 _private member_ `FRHITransientPagePool* FastPagePool = nullptr;`
- L1078 _private member_ `TArray<FRHITransientPagePool*> LiveList;`
- L1079 _private member_ `TArray<FRHITransientPagePool*> FreeList;`
- L1080 _private member_ `uint64 GarbageCollectCycle = 0;`
- L1081 _private member_ `uint64 TotalMemoryCapacity = 0;`

#### struct `FRHITransientPagePoolCache::FInitializer`  
`struct FInitializer`  
_L1015-1039_
- L1018 _public prototype_ `static FInitializer CreateDefault();` — Creates a default initializer using common RHI CVars.
- L1020 _public member_ `static const uint32 kDefaultResourceCacheSize = 256;`
- L1023 _public member_ `uint64 PoolSize = 0;` — Size in bytes of the pool. Must be a multiple of PageSize.
- L1026 _public member_ `uint64 PoolSizeFirst = 0;` — Size in bytes of the first pool. Only takes effect if larger than PoolSize.
- L1029 _public member_ `uint32 PageSize = 0;` — Size of each page.
- L1032 _public member_ `uint32 GarbageCollectLatency = 0;` — The latency between the completed fence value and the used fence value to invoke garbage collection of the heap.
- L1035 _public member_ `uint32 TextureCacheSize = kDefaultResourceCacheSize;` — Size of the texture cache before elements are evicted.
- L1038 _public member_ `uint32 BufferCacheSize = kDefaultResourceCacheSize;` — Size of the buffer cache before elements are evicted.

#### class `FRHITransientResourcePageAllocator`  
`class FRHITransientResourcePageAllocator : public IRHITransientResourceAllocator`  
_L1088-1167_
- inherits: `IRHITransientResourceAllocator`
- L1091 _public function_ `FRHITransientResourcePageAllocator(FRHITransientPagePoolCache& InPagePoolCache) : PagePoolCache(InPagePoolCache) , Textures(InPagePoolCache.Initializer.TextureCacheSize, ResourceCacheGarbageCollectionLatency) , Buffers(InPagePoolCache.Initializer.BufferCacheSize, ResourceCacheGarbageCollectionLatency) , PageSize(PagePoolCache.Initializer.PageSize)`
- L1100 _public prototype_ `FRHITransientTexture* CreateTexture(const FRHITextureCreateInfo& CreateInfo, const TCHAR* DebugName, const FRHITransientAllocationFences& Fences) override;`
- L1101 _public prototype_ `FRHITransientBuffer* CreateBuffer(const FRHIBufferCreateInfo& CreateInfo, const TCHAR* DebugName, const FRHITransientAllocationFences& Fences) override;`
- L1102 _public prototype_ `void DeallocateMemory(FRHITransientTexture* Texture, const FRHITransientAllocationFences& Fences) override;`
- L1103 _public prototype_ `void DeallocateMemory(FRHITransientBuffer* Buffer, const FRHITransientAllocationFences& Fences) override;`
- L1104 _public prototype_ `void Flush(FRHICommandListImmediate& RHICmdList, FRHITransientAllocationStats* OutAllocationStats) override;`
- L1106 _public function_ `uint32 GetPageSize() const`
- L1108 _public function_ `uint32 GetPagePoolCount() const`
- L1110 _public member_ `FRHITransientPagePoolCache& PagePoolCache;`
- L1113 _private member_ `static constexpr uint32 ResourceCacheGarbageCollectionLatency = 2;`
- L1114 _private member_ `static constexpr uint64 KB = 1024;`
- L1115 _private member_ `static constexpr uint64 MB = 1024 * KB;`
- L1117 _private prototype_ `void AllocateMemoryInternal(FRHITransientResource* Resource, const TCHAR* DebugName, const FRHITransientAllocationFences& Fences, bool bFastPoolRequested, float FastPoolPercentageRequested);`
- L1118 _private prototype_ `void DeallocateMemoryInternal(FRHITransientResource* Resource, const FRHITransientAllocationFences& Fences);`
- L1123 _private prototype_ `virtual FRHITransientTexture* CreateTextureInternal( const FRHITextureCreateInfo& CreateInfo, const TCHAR* DebugName, uint64 Hash) = 0;`
- L1128 _private prototype_ `virtual FRHITransientBuffer* CreateBufferInternal( const FRHIBufferCreateInfo& CreateInfo, const TCHAR* DebugName, uint64 Hash) = 0;`
- L1133 _private prototype_ `virtual void ReleaseTextureInternal(FRHITransientTexture* Texture) = 0;`
- L1134 _private prototype_ `virtual void ReleaseBufferInternal(FRHITransientBuffer* Buffer) = 0;`
- L1139 _private function_ `template <typename FunctionType> void EnumeratePageSpans(const FRHITransientResource* Resource, FunctionType Function) const`
- L1152 _private member_ `FRHITransientMemoryStats Stats;`
- L1153 _private member_ `TRHITransientResourceCache<FRHITransientTexture> Textures;`
- L1154 _private member_ `TRHITransientResourceCache<FRHITransientBuffer> Buffers;`
- L1156 _private member_ `TArray<FRHITransientPagePool*> PagePools;`
- L1157 _private member_ `FRHITransientPagePool* FastPagePool = nullptr;`
- L1158 _private member_ `uint64 CurrentCycle = 0;`
- L1159 _private member_ `uint32 FirstNormalPagePoolIndex = 0;`
- L1160 _private member_ `uint32 DeallocationCount = 0;`
- L1161 _private member_ `uint32 PageSize = 0;`
- L1162 _private member_ `uint32 PageMapCount = 0;`
- L1163 _private member_ `uint32 PageAllocateCount = 0;`
- L1164 _private member_ `uint32 PageSpanCount = 0;`
- L1166 _private prototype_ `IF_RHICORE_TRANSIENT_ALLOCATOR_DEBUG(TSet<FRHITransientResource*> ActiveResources);`

#### Free symbols / members of external scopes

- L7 _macro_ `#define RHICORE_TRANSIENT_ALLOCATOR_DEBUG (!UE_BUILD_SHIPPING && !UE_BUILD_TEST)`
- L10 _macro_ `#define IF_RHICORE_TRANSIENT_ALLOCATOR_DEBUG(Op) Op`
- L12 _macro_ `#define IF_RHICORE_TRANSIENT_ALLOCATOR_DEBUG(Op)`
- L15 _function_ `inline uint64 ComputeHash(const FRHITextureCreateInfo& InCreateInfo, uint64 HeapOffset)`
- L24 _function_ `inline uint64 ComputeHash(const FRHITextureCreateInfo& InCreateInfo)`
- L33 _function_ `inline uint64 ComputeHash(const FRHIBufferCreateInfo& InCreateInfo, uint64 HeapOffset)`
- L42 _function_ `inline uint64 ComputeHash(const FRHIBufferCreateInfo& InCreateInfo)`
- L213 _function_ `const int32 FirstForfeitIndex = Algo::Partition(Allocated.GetData(), Allocated.Num(), [](const FRHITransientResource* Resource) { return Resource->IsAcquired(); });` (scope `TRHITransientResourceCache::Forfeit`)
- L224 _function_ `` (scope `TRHITransientResourceCache::Forfeit`)
- L242 _function_ `Forfeit(CurrentFrameIndex, [](TransientResourceType*) {});` (scope `TRHITransientResourceCache::Forfeit`)
- L460 _prototype_ `ENUM_CLASS_FLAGS(ERHITransientHeapFlags);`

### `Source/Runtime/RHICore/Public/RHIDescriptorAllocator.h` (Public)


#### struct `FRHIDescriptorAllocatorRange`  
`struct FRHIDescriptorAllocatorRange`  
_L11-16_
- L13 _public function_ `FRHIDescriptorAllocatorRange(uint32 InFirst, uint32 InLast) : First(InFirst), Last(InLast)`
- L14 _public member_ `uint32 First;`
- L15 _public member_ `uint32 Last;`

#### struct `FRHIDescriptorAllocation`  
`struct FRHIDescriptorAllocation`  
_L18-28_
- L20 _public function_ `FRHIDescriptorAllocation(uint32 InStartIndex, uint32 InCount) : StartIndex(InStartIndex) , Count(InCount)`
- L26 _public member_ `uint32 StartIndex = 0;`
- L27 _public member_ `uint32 Count = 0;`

#### class `FRHIDescriptorAllocator`  
`class FRHIDescriptorAllocator`  
_L30-97_
- L33 _public prototype_ `FRHIDescriptorAllocator();`
- L34 _public prototype_ `FRHIDescriptorAllocator(uint32 InNumDescriptors, TConstArrayView<TStatId> InStats);`
- L35 _public prototype_ `~FRHIDescriptorAllocator();`
- L37 _public prototype_ `void Init(uint32 InNumDescriptors, TConstArrayView<TStatId> InStats);`
- L38 _public prototype_ `void Shutdown();`
- L40 _public prototype_ `TOptional<FRHIDescriptorAllocation> ResizeGrowAndAllocate(uint32 NewCapacity, uint32 NumAllocations);`
- L42 _public prototype_ `TOptional<FRHIDescriptorAllocation> Allocate(uint32 NumDescriptors);`
- L43 _public prototype_ `void Free(FRHIDescriptorAllocation Allocation);`
- L45 _public prototype_ `FRHIDescriptorHandle Allocate(ERHIDescriptorType InType);`
- L46 _public prototype_ `void Free(TConstArrayView<FRHIDescriptorHandle> InHandles);`
- L47 _public prototype_ `void Free(FRHIDescriptorHandle InHandle);`
- L50 _public prototype_ `bool GetAllocatedRange(FRHIDescriptorAllocatorRange& OutRange);` — Get the range of allocated descriptors. Useful for determining the smallest range to copy between heaps.
- L52 _public function_ `uint32 GetCapacity() const`
- L56 _private prototype_ `TOptional<FRHIDescriptorAllocation> AllocateInternal(uint32 NumDescriptors);`
- L57 _private prototype_ `void FreeInternal(FRHIDescriptorAllocation Allocation);`
- L59 _private function_ `void RecordAlloc(uint32 Count)`
- L69 _private function_ `void RecordFree(uint32 Count)`
- L79 _private member_ `TArray<FRHIDescriptorAllocatorRange> Ranges;`
- L80 _private member_ `uint32 Capacity = 0;`
- L82 _private member_ `FCriticalSection CriticalSection;`
- L91 _private member_ `TMap<uint32, FDebugDescriptorAllocation> DebugOutstandingAllocations;`
- L95 _private member_ `TArray<TStatId> Stats;`

#### struct `FRHIDescriptorAllocator::FDebugDescriptorAllocation`  
`struct FDebugDescriptorAllocation`  
_L86-90_
- desc: Debug tracking of outstanding allocations to detect double-free.
- L88 _public member_ `uint32 Count = 0;`
- L89 _public member_ `TArray<uint64, TInlineAllocator<16>> Callstack;`

#### class `FRHIHeapDescriptorAllocator`  
`class FRHIHeapDescriptorAllocator : protected FRHIDescriptorAllocator`  
_L100-134_
- inherits: `FRHIDescriptorAllocator`
- L103 _public prototype_ `FRHIHeapDescriptorAllocator() = delete;`
- L104 _public prototype_ `FRHIHeapDescriptorAllocator(ERHIDescriptorTypeMask InTypeMask, uint32 InDescriptorCount, TConstArrayView<TStatId> InStats);`
- L106 _public prototype_ `FRHIDescriptorHandle Allocate(ERHIDescriptorType InType);`
- L107 _public prototype_ `void Free(TConstArrayView<FRHIDescriptorHandle> InHandles);`
- L108 _public prototype_ `void Free(FRHIDescriptorHandle InHandle);`
- L110 _public prototype_ `TOptional<FRHIDescriptorAllocation> Allocate(uint32 NumDescriptors);`
- L111 _public prototype_ `void Free(FRHIDescriptorAllocation Allocation);`
- L117 _public function_ `ERHIDescriptorTypeMask GetTypeMask() const`
- L122 _public function_ `bool HandlesAllocation(ERHIDescriptorType InType) const`
- L127 _public function_ `bool HandlesAllocations(ERHIDescriptorTypeMask InTypeMask) const`
- L133 _private member_ `const ERHIDescriptorTypeMask TypeMask;`

#### class `FRHIOffsetHeapDescriptorAllocator`  
`class FRHIOffsetHeapDescriptorAllocator : protected FRHIHeapDescriptorAllocator`  
_L136-156_
- inherits: `FRHIHeapDescriptorAllocator`
- L139 _public prototype_ `FRHIOffsetHeapDescriptorAllocator() = delete;`
- L140 _public prototype_ `FRHIOffsetHeapDescriptorAllocator(ERHIDescriptorTypeMask InTypeMask, uint32 InDescriptorCount, uint32 InHeapOffset, TConstArrayView<TStatId> InStats);`
- L142 _public prototype_ `FRHIDescriptorHandle Allocate(ERHIDescriptorType InType);`
- L143 _public prototype_ `void Free(FRHIDescriptorHandle InHandle);`
- L145 _public prototype_ `TOptional<FRHIDescriptorAllocation> Allocate(uint32 NumDescriptors);`
- L146 _public prototype_ `void Free(FRHIDescriptorAllocation Allocation);`
- L155 _private member_ `const uint32 HeapOffset;` — Offset from start of heap we belong to

### `Source/Runtime/RHICore/Public/RHIDiagnosticBuffer.h` (Public)


#### class `FRHIDiagnosticBuffer`  
`class FRHIDiagnosticBuffer`  
_L12-51_
- desc: Common base for platform-specific implementations of GPU diagnostic buffer. The diagnostic buffer contains GPU messages (debug logs, shader asserts, etc.) and GPU progress breadcrumbs. This buffer is persistently mapped and can be accessed on CPU at any point, including after a GPU crash has been detected. Platform-specific code is responsible for allocating the actual underlying resource and binding it to shaders that need it. Diagnostic buffer functionality may be used independently of GPU breadcrumbs.
- L44 _public member_ `static constexpr uint32 SizeInBytes = sizeof(FQueue);`
- L47 _public member_ `FQueue* Data = nullptr;` — Persistently mapped diagnostic buffer data, initialized by platform-specific code
- L50 _public prototype_ `FString GetShaderDiagnosticMessages(uint32 DeviceIndex, uint32 QueueIndex, const TCHAR* QueueName);` — Log the GPU progress of the given queue to the Error log if breadcrumb data is available

#### struct `FRHIDiagnosticBuffer::FLane`  
`struct FLane`  
_L17-27_
- desc: Counterpart to UEDiagnosticBuffer in shader code
- L19 _public member_ `uint32 Counter;`
- L20 _public member_ `uint32 MessageID;`
- L26 _public member_ `} Payload;`

#### union `FRHIDiagnosticBuffer::FLane::(anonymous)`  
``  
_L22-26_

#### struct `FRHIDiagnosticBuffer::FQueue`  
`struct FQueue`  
_L31-42_
- L34 _public member_ `static constexpr uint32 MaxLanes = 64;` — Counterpart to UEDiagnosticMaxLanes in shader code
- L35 _public member_ `FLane Lanes[MaxLanes];`
- L39 _public member_ `uint32 MarkerIn;` — GPU breadcrumb markers
- L40 _public member_ `uint32 MarkerOut;`

#### Free symbols / members of external scopes

- L23 _member_ `int32 AsInt[4];` (scope `FRHIDiagnosticBuffer::FLane::__anon415e1aca010a`)
- L24 _member_ `uint32 AsUint[4];` (scope `FRHIDiagnosticBuffer::FLane::__anon415e1aca010a`)
- L25 _member_ `float AsFloat[4];` (scope `FRHIDiagnosticBuffer::FLane::__anon415e1aca010a`)

### `Source/Runtime/RHICore/Public/RHIPoolAllocator.h` (Public)


#### class `FRHIPoolResource`  
`class FRHIPoolResource`  
_L18-20_
- desc: @brief Owner of the pool allocation data which needs to handle memory move operations

#### enum `ERHIPoolResourceTypes`  
`enum class ERHIPoolResourceTypes`  
_L26-32_
- desc: @brief Resource type supported by the pools (can be any or all)
- L28 _public enumerator_ `Buffers = 0x1`
- L29 _public enumerator_ `RTDSTextures = 0x2`
- L30 _public enumerator_ `NonRTDSTextures = 0x4`
- L31 _public enumerator_ `All = Buffers | RTDSTextures | NonRTDSTextures`

#### enum `ERHIPoolAllocationStrategy`  
`enum class ERHIPoolAllocationStrategy`  
_L37-42_
- desc: @brief Type of allocation strategy
- L39 _public enumerator_ `Immediate`
- L40 _public enumerator_ `Async`
- L41 _public enumerator_ `Count`

#### enum `ERHIPoolAllocationStatus`  
`enum class ERHIPoolAllocationStatus`  
_L47-53_
- desc: @brief Status of the Async pool allocation
- L49 _public enumerator_ `Idle`
- L50 _public enumerator_ `Allocating`
- L51 _public enumerator_ `ShutDown`
- L52 _public enumerator_ `Count`

#### struct `FRHIPoolAllocationData`  
`struct FRHIPoolAllocationData`  
_L58-143_
- desc: @brief Pool allocator internal data
- L63 _public prototype_ `void Reset();` — Reset to unknown state
- L66 _public prototype_ `void InitAsHead(int16 InPoolIndex);` — Initialize options
- L67 _public prototype_ `void InitAsFree(int16 InPoolIndex, uint32 InSize, uint32 InAlignment, uint32 InOffset);`
- L68 _public prototype_ `void InitAsAllocated(uint32 InSize, uint32 InPoolAlignment, uint32 InAllocationAlignment, FRHIPoolAllocationData* InFree);`
- L69 _public prototype_ `void MoveFrom(FRHIPoolAllocationData& InAllocated, bool InLocked);`
- L72 _public prototype_ `void MarkFree(uint32 InPoolAlignment, uint32 InAllocationAlignment);` — Free block operation (TODO: make internal)
- L75 _public prototype_ `void AddAlias(FRHIPoolAllocationData* InOther);` — Alias operations (NOTE: currently not accessed when pool lock is taken, needs to be fixed)
- L76 _public prototype_ `void RemoveAlias();`
- L77 _public function_ `FRHIPoolAllocationData* GetFirstAlias() const`
- L80 _public function_ `bool IsHead() const` — Type getters
- L81 _public function_ `bool IsFree() const`
- L82 _public function_ `bool IsAllocated() const`
- L85 _public function_ `uint32 GetSize() const` — Allocation data getters
- L86 _public function_ `uint32 GetAlignment() const`
- L87 _public function_ `uint32 GetOffset() const`
- L88 _public function_ `int16 GetPoolIndex() const`
- L91 _public function_ `FRHIPoolAllocationData* GetNext() const` — Linked list getters
- L92 _public function_ `FRHIPoolAllocationData* GetPrev() const`
- L95 _public function_ `void SetOwner(FRHIPoolResource* InOwner)` — Owner getter/setter - opaque data
- L96 _public function_ `FRHIPoolResource* GetOwner() const`
- L99 _public function_ `bool IsLocked() const` — Unlock can be public - no lock required
- L100 _public function_ `void Unlock()`
- L107 _private function_ `void Lock()`
- L109 _private prototype_ `void Merge(FRHIPoolAllocationData* InOther);`
- L112 _private prototype_ `void RemoveFromLinkedList();` — Linked list operation
- L113 _private prototype_ `void AddBefore(FRHIPoolAllocationData* InOther);`
- L114 _private prototype_ `void AddAfter(FRHIPoolAllocationData* InOther);`
- L123 _private function_ `EAllocationType GetAllocationType() const`
- L124 _private function_ `void SetAllocationType(EAllocationType InType)`
- L126 _private member_ `uint32 Size;`
- L127 _private member_ `uint32 Alignment;`
- L128 _private member_ `uint32 Offset;`
- L129 _private member_ `uint32 PoolIndex : 16;`
- L130 _private member_ `uint32 Type : 4;`
- L134 _private member_ `uint32 Locked : 1;` — Allocation data is locked after creation until initial data is filled in to make sure it's not being defragmented then. If a block is locked for read/write from CPU side then it also needs be locked. While it's defragmented then the block is also locked so make sure to wait for the GPU before destroying it
- L135 _private member_ `uint32 Unused : 11;`
- L138 _private member_ `FRHIPoolAllocationData* PreviousAllocation;` — TODO: Link list data could be stored as index into a fixed array managed by the memory pool. Then only a uin16 or uint32 is needed here to get the next and previous index
- L139 _private member_ `FRHIPoolAllocationData* NextAllocation;`
- L140 _private member_ `FRHIPoolAllocationData* AliasAllocation;` — Linked list of aliases
- L142 _private member_ `FRHIPoolResource* Owner;`

#### enum `FRHIPoolAllocationData::EAllocationType`  
`enum class EAllocationType : uint8`  
_L116-122_
- L118 _public enumerator_ `Unknown`
- L119 _public enumerator_ `Free`
- L120 _public enumerator_ `Allocated`
- L121 _public enumerator_ `Head`

#### class `FRHIMemoryPool`  
`class FRHIMemoryPool`  
_L154-236_
- desc: @brief Pool which stores for each allocation the previous and next allocation. Each block is either free or allocated.
- L158 _public member_ `static constexpr int16 InvalidPoolIndex = -1;`
- L167 _public prototype_ `FRHIMemoryPool(int16 InPoolIndex, uint64 InPoolSize, uint32 InPoolAlignment, ERHIPoolResourceTypes InSupportedResourceTypes, EFreeListOrder InFreeListOrder);` — Constructor
- L168 _public prototype_ `virtual ~FRHIMemoryPool();`
- L171 _public prototype_ `virtual void Init();` — Setup/Shutdown
- L172 _public prototype_ `virtual void Destroy();`
- L173 _public prototype_ `void InitFreeBlocks();`
- L176 _public prototype_ `bool TryAllocate(uint32 InSizeInBytes, uint32 InAllocationAlignment, ERHIPoolResourceTypes InAllocationResourceType, FRHIPoolAllocationData& AllocationData);` — AllocationData functions: allocate, free, move, ...
- L177 _public prototype_ `void Deallocate(FRHIPoolAllocationData& AllocationData);`
- L180 _public prototype_ `void TryClear(FRHIContextArray const& Contexts, FRHIPoolAllocator* InAllocator, uint32 InMaxCopySize, uint32& CopySize, const TArray<FRHIMemoryPool*>& InTargetPools);` — Bookkeeping and clearing
- L183 _public function_ `int16 GetPoolIndex() const` — Getters
- L184 _public function_ `uint64 GetPoolSize() const`
- L185 _public function_ `uint64 GetFreeSize() const`
- L186 _public function_ `uint64 GetUsedSize() const`
- L187 _public function_ `uint32 GetPoolAlignment() const`
- L188 _public function_ `uint32 GetAlignmentWaste() const`
- L189 _public function_ `uint32 GetAllocatedBlocks() const`
- L190 _public function_ `ERHIPoolResourceTypes GetSupportedResourceTypes() const`
- L191 _public function_ `bool IsResourceTypeSupported(ERHIPoolResourceTypes InType) const`
- L192 _public function_ `bool IsEmpty() const`
- L193 _public function_ `bool IsFull() const`
- L196 _public function_ `void SetPoolIndex(int16 InPoolIndex)` — Index setter for async allocation
- L199 _public prototype_ `static uint32 GetAlignedSize(uint32 InSizeInBytes, uint32 InPoolAlignment, uint32 InAllocationAlignment);` — Static public helper functions
- L200 _public prototype_ `static uint32 GetAlignedOffset(uint32 InOffset, uint32 InPoolAlignment, uint32 InAllocationAlignment);`
- L205 _protected prototype_ `int32 FindFreeBlock(uint32 InSizeInBytes, uint32 InAllocationAlignment) const;` — Free block management helper function
- L206 _protected prototype_ `FRHIPoolAllocationData* AddToFreeBlocks(FRHIPoolAllocationData* InFreeBlock);`
- L207 _protected prototype_ `void RemoveFromFreeBlocks(FRHIPoolAllocationData* InFreeBlock);`
- L210 _protected prototype_ `FRHIPoolAllocationData* GetNewAllocationData();` — Get/Release allocation data blocks
- L211 _protected prototype_ `void ReleaseAllocationData(FRHIPoolAllocationData* InData);`
- L214 _protected prototype_ `void Validate();` — Validate the linked list data - slow
- L217 _protected member_ `int16 PoolIndex;` — Const creation members
- L218 _protected member_ `const uint64 PoolSize;`
- L219 _protected member_ `const uint32 PoolAlignment;`
- L220 _protected member_ `const ERHIPoolResourceTypes SupportedResourceTypes;`
- L221 _protected member_ `const EFreeListOrder FreeListOrder;`
- L224 _protected member_ `uint64 FreeSize;` — Stats
- L225 _protected member_ `uint64 AligmnentWaste;`
- L226 _protected member_ `uint32 AllocatedBlocks;`
- L229 _protected member_ `FRHIPoolAllocationData HeadBlock;` — Special start block to mark the beginning and the end of the linked list
- L232 _protected member_ `TArray<FRHIPoolAllocationData*> FreeBlocks;` — Actual Free blocks
- L235 _protected member_ `TArray<FRHIPoolAllocationData*> AllocationDataPool;` — Allocation data pool used to reduce allocation overhead

#### enum `FRHIMemoryPool::EFreeListOrder`  
`enum class EFreeListOrder`  
_L160-164_
- L162 _public enumerator_ `SortBySize`
- L163 _public enumerator_ `SortByOffset`

#### class `FRHIPoolAllocator`  
`class FRHIPoolAllocator`  
_L246-315_
- desc: @brief Manages an array of FRHIMemoryPool and supports defragmentation between multiple pools
- L251 _public prototype_ `FRHIPoolAllocator(uint64 InDefaultPoolSize, uint32 InPoolAlignment, uint32 InMaxAllocationSize, FRHIMemoryPool::EFreeListOrder InFreeListOrder, bool InDefragEnabled, ERHIPoolAllocationStrategy InPoolAllocationStrategy, uint16 InOverFlowPoolsCount);` — Constructor
- L252 _public prototype_ `virtual ~FRHIPoolAllocator();`
- L255 _public prototype_ `void Initialize(ERHIPoolResourceTypes InAllocationResourceType);` — Setup/Shutdown
- L256 _public prototype_ `void Destroy();`
- L259 _public prototype_ `void Defrag(FRHIContextArray const& Contexts, uint32 InMaxCopySize, uint32& CurrentCopySize);` — Defrag & cleanup operation
- L262 _public prototype_ `void UpdateMemoryStats(uint32& IOMemoryAllocated, uint32& IOMemoryUsed, uint32& IOMemoryFree, uint32& IOMemoryEndFree, uint32& IOAlignmentWaste, uint32& IOAllocatedPageCount, uint32& IOFullPageCount);` — Stats
- L267 _protected prototype_ `bool TryAllocateInternal(uint32 InSizeInBytes, uint32 InAllocationAlignment, ERHIPoolResourceTypes InAllocationResourceType, FRHIPoolAllocationData& AllocationData);` — Supported allocator operations
- L268 _protected prototype_ `void DeallocateInternal(FRHIPoolAllocationData& AllocationData);`
- L270 _protected prototype_ `void SortPools();`
- L272 _protected prototype_ `void PoolAsyncAllocate(uint32 InSizeInBytes, uint32 InAllocationAlignment, ERHIPoolResourceTypes InAllocationResourceType);`
- L275 _protected prototype_ `virtual FRHIMemoryPool* CreateNewPool(int16 InPoolIndex, uint32 InMinimumAllocationSize, ERHIPoolResourceTypes InAllocationResourceType) = 0;` — Helper function to create a new platform specific pool
- L279 _protected prototype_ `virtual bool HandleDefragRequest(FRHIContextArray const& Contexts, FRHIPoolAllocationData* InSourceBlock, FRHIPoolAllocationData& InTmpTargetBlock) = 0;`
- L282 _protected member_ `const uint64 DefaultPoolSize;` — Const creation members - used to create new pools
- L283 _protected member_ `const uint32 PoolAlignment;`
- L284 _protected member_ `const uint64 MaxAllocationSize;`
- L285 _protected member_ `const FRHIMemoryPool::EFreeListOrder FreeListOrder;`
- L286 _protected member_ `const bool bDefragEnabled;`
- L289 _protected member_ `FCriticalSection CS;` — Critical section to lock access to the pools
- L292 _protected member_ `TArray<FRHIMemoryPool*> Pools;` — Actual pools managing each a linked list of allocations
- L295 _protected member_ `int32 LastDefragPoolIndex;` — Last defrag pool index - defrag is time slices to reduce CPU overhead
- L299 _protected member_ `TArray<uint32> PoolAllocationOrder;` — Allocation order of the pools when performing new allocations Can' sort the pools directly because pool index is stored in the allocation info
- L302 _protected member_ `uint32 TotalAllocatedBlocks;` — Stats
- L305 _protected member_ `TArray<FRHIMemoryPool*> OverFlowPools;` — Array of pre-allocated pools
- L308 _protected member_ `ERHIPoolAllocationStrategy PoolAllocationStrategy = ERHIPoolAllocationStrategy::Immediate;` — Pool allocation strategy
- L311 _protected member_ `ERHIPoolAllocationStatus PoolAllocationStatus = ERHIPoolAllocationStatus::Idle;` — Pool allocation status
- L314 _protected member_ `int16 OverFlowPoolsCount = 1;` — Max pre-allocated pool
