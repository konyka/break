# Runtime / NullDrv

- module root: `Source/Runtime/NullDrv`
- headers: 2; symbols: 119
- symbol kinds: class=5, function=104, member=1, prototype=7, struct=2
- PrivateDependencyModuleNames: Core, RHI, RenderCore

### `Source/Runtime/NullDrv/Public/NullDrv.h` (Public)


#### class `FNullDynamicRHIModule`  
`class FNullDynamicRHIModule : public IDynamicRHIModule`  
_L12-26_
- inherits: `IDynamicRHIModule`
- desc: Implements the NullDrv module as a dynamic RHI providing module.
- L19 _public function_ `virtual bool SupportsDynamicReloading() override`
- L20 _public prototype_ `virtual bool IsSupported() override;`
- L22 _public function_ `virtual FDynamicRHI* CreateRHI(ERHIFeatureLevel::Type RequestedFeatureLevel = ERHIFeatureLevel::Num) override`

### `Source/Runtime/NullDrv/Public/NullRHI.h` (Public)


#### class `FNullDynamicRHI`  
`class FNullDynamicRHI : public FDynamicRHIPSOFallback, public IRHICommandContextPSOFallback`  
_L15-582_
- inherits: `FDynamicRHIPSOFallback,IRHICommandContextPSOFallback`
- desc: A null implementation of the dynamically bound RHI.
- L19 _public prototype_ `FNullDynamicRHI();`
- L22 _public prototype_ `virtual void Init();` — FDynamicRHI interface.
- L23 _public prototype_ `virtual void Shutdown();`
- L24 _public function_ `virtual const TCHAR* GetName() override`
- L25 _public function_ `virtual ERHIInterfaceType GetInterfaceType() const override`
- L27 _public function_ `virtual FSamplerStateRHIRef RHICreateSamplerState(const FSamplerStateInitializerRHI& Initializer) final override`
- L31 _public function_ `virtual FRasterizerStateRHIRef RHICreateRasterizerState(const FRasterizerStateInitializerRHI& Initializer) final override`
- L35 _public function_ `virtual FDepthStencilStateRHIRef RHICreateDepthStencilState(const FDepthStencilStateInitializerRHI& Initializer) final override`
- L39 _public function_ `virtual FBlendStateRHIRef RHICreateBlendState(const FBlendStateInitializerRHI& Initializer) final override`
- L43 _public function_ `virtual FVertexDeclarationRHIRef RHICreateVertexDeclaration(const FVertexDeclarationElementList& Elements) final override`
- L48 _public function_ `virtual FPixelShaderRHIRef RHICreatePixelShader(const FRHICreateShaderDesc& CreateShaderDesc) final override`
- L53 _public function_ `virtual FVertexShaderRHIRef RHICreateVertexShader(const FRHICreateShaderDesc& CreateShaderDesc) final override`
- L58 _public function_ `virtual FGeometryShaderRHIRef RHICreateGeometryShader(const FRHICreateShaderDesc& CreateShaderDesc) final override`
- L63 _public function_ `virtual FComputeShaderRHIRef RHICreateComputeShader(const FRHICreateShaderDesc& CreateShaderDesc) final override`
- L69 _public function_ `virtual FBoundShaderStateRHIRef RHICreateBoundShaderState(FRHIVertexDeclaration* VertexDeclaration, FRHIVertexShader* VertexShader, FRHIPixelShader* PixelShader, FRHIGeometryShader* GeometryShader) final override`
- L75 _public function_ `virtual FBoundShaderStateRHIRef RHICreateBoundShaderState(FRHIAmplificationShader* AmplificationShader, FRHIMeshShader* MeshShader, FRHIPixelShader* PixelShader) final override`
- L81 _public function_ `virtual void RHISetComputeShader(FRHIComputeShader* ComputeShader) final override`
- L86 _public function_ `virtual void RHIDispatchComputeShader(uint32 ThreadGroupCountX, uint32 ThreadGroupCountY, uint32 ThreadGroupCountZ) final override`
- L91 _public function_ `virtual void RHIDispatchIndirectComputeShader(FRHIBuffer* ArgumentBuffer, uint32 ArgumentOffset) final override`
- L96 _public function_ `virtual void RHICreateTransition(FRHITransition* Transition, const FRHITransitionCreateInfo& CreateInfo) final override`
- L100 _public function_ `virtual void RHIReleaseTransition(FRHITransition* Transition) final override`
- L104 _public function_ `virtual void RHIBeginTransitions(TArrayView<const FRHITransition*> Transitions) final override`
- L108 _public function_ `virtual void RHIEndTransitions(TArrayView<const FRHITransition*> Transitions) final override`
- L112 _public function_ `virtual void RHISetMultipleViewports(uint32 Count, const FViewportBounds* Data) final override`
- L117 _public function_ `virtual FUniformBufferRHIRef RHICreateUniformBuffer(const void* Contents, const FRHIUniformBufferLayout* Layout, EUniformBufferUsage Usage, EUniformBufferValidation Validation) final override`
- L122 _public function_ `virtual void RHIUpdateUniformBuffer(FRHICommandListBase& RHICmdList, FRHIUniformBuffer* UniformBufferRHI, const void* Contents) final override`
- L150 _public function_ `virtual FRHIBufferInitializer RHICreateBufferInitializer(FRHICommandListBase& RHICmdList, const FRHIBufferCreateDesc& CreateDesc) final override`
- L171 _public function_ `virtual void* LockBuffer_BottomOfPipe(FRHICommandListBase& RHICmdList, FRHIBuffer* Buffer, uint32 Offset, uint32 SizeRHI, EResourceLockMode LockMode) final override`
- L176 _public function_ `virtual void UnlockBuffer_BottomOfPipe(FRHICommandListBase& RHICmdList, FRHIBuffer* Buffer) final override`
- L181 _public function_ `virtual void RHIReplaceResources(FRHICommandListBase& RHICmdList, TArray<FRHIResourceReplaceInfo>&& ReplaceInfos) final override`
- L186 _public function_ `virtual void RHIClearUAVFloat(FRHIUnorderedAccessView* UnorderedAccessViewRHI, const FVector4f& Values) final override`
- L191 _public function_ `virtual void RHIClearUAVUint(FRHIUnorderedAccessView* UnorderedAccessViewRHI, const FUintVector4& Values) final override`
- L196 _public function_ `virtual FRHICalcTextureSizeResult RHICalcTexturePlatformSize(FRHITextureDesc const& Desc, uint32 FirstMipIndex) override final`
- L201 _public function_ `virtual void RHIGetTextureMemoryStats(FTextureMemoryStats& OutStats) final override`
- L206 _public function_ `virtual bool RHIGetTextureMemoryVisualizeData(FColor* TextureData,int32 SizeX,int32 SizeY,int32 Pitch,int32 PixelSize) final override`
- L248 _public function_ `virtual FRHITextureInitializer RHICreateTextureInitializer(FRHICommandListBase& RHICmdList, const FRHITextureCreateDesc& CreateDesc)`
- L269 _public function_ `virtual FTextureRHIRef RHIAsyncCreateTexture2D(uint32 SizeX, uint32 SizeY, uint8 Format, uint32 NumMips, ETextureCreateFlags Flags, ERHIAccess InResourceState, void** InitialMipData, uint32 NumInitialMips, const TCHAR* DebugName, FGraphEventRef& OutCompletionEvent) final override`
- L281 _public function_ `virtual FShaderResourceViewRHIRef RHICreateShaderResourceView(class FRHICommandListBase& RHICmdList, FRHIViewableResource* Resource, FRHIViewDesc const& ViewDesc)`
- L286 _public function_ `virtual FUnorderedAccessViewRHIRef RHICreateUnorderedAccessView(class FRHICommandListBase& RHICmdList, FRHIViewableResource* Resource, FRHIViewDesc const& ViewDesc)`
- L291 _public function_ `virtual uint32 RHIComputeMemorySize(FRHITexture* TextureRHI) final override`
- L296 _public function_ `virtual FRHILockTextureResult RHILockTexture(FRHICommandListImmediate& RHICmdList, const FRHILockTextureArgs& Arguments) final override`
- L305 _public function_ `virtual void RHIUnlockTexture(FRHICommandListImmediate& RHICmdList, const FRHILockTextureArgs& Arguments) final override`
- L310 _public function_ `virtual void RHIUpdateAllocationTags(FRHICommandListBase& RHICmdList, FRHIBuffer* Buffer) final override`
- L315 _public function_ `virtual void RHIUpdateTexture2D(FRHICommandListBase&, FRHITexture* Texture, uint32 MipIndex, const struct FUpdateTextureRegion2D& UpdateRegion, uint32 SourcePitch, const uint8* SourceData) final override`
- L319 _public function_ `virtual void RHIUpdateTexture3D(FRHICommandListBase&, FRHITexture* Texture, uint32 MipIndex, const struct FUpdateTextureRegion3D& UpdateRegion, uint32 SourceRowPitch, uint32 SourceDepthPitch, const uint8* SourceData) final override`
- L324 _public function_ `virtual void RHICopyTexture(FRHITexture* SourceTexture, FRHITexture* DestTexture, const FRHICopyTextureInfo& CopyInfo) final override`
- L329 _public function_ `virtual void RHICopyBufferRegion(FRHIBuffer* DestBuffer, uint64 DstOffset, FRHIBuffer* SourceBuffer, uint64 SrcOffset, uint64 NumBytes) final override`
- L333 _public function_ `virtual void RHIBindDebugLabelName(FRHICommandListBase& RHICmdList, FRHITexture* Texture, const TCHAR* Name) final override`
- L338 _public function_ `virtual void RHIReadSurfaceData(FRHITexture* Texture,FIntRect Rect,TArray<FColor>& OutData,FReadSurfaceDataFlags InFlags) final override`
- L344 _public function_ `virtual FGPUFenceRHIRef RHICreateGPUFence(const FName& Name)`
- L369 _public function_ `virtual void RHIMapStagingSurface(FRHITexture* Texture, FRHIGPUFence* Fence, void*& OutData, int32& OutWidth, int32& OutHeight, uint32 GPUIndex) final override`
- L375 _public function_ `virtual void RHIUnmapStagingSurface(FRHITexture* Texture, uint32 GPUIndex) final override`
- L380 _public function_ `virtual void RHIReadSurfaceFloatData(FRHITexture* Texture,FIntRect Rect,TArray<FFloat16Color>& OutData,ECubeFace CubeFace,int32 ArrayIndex,int32 MipIndex) final override`
- L385 _public function_ `virtual void RHIRead3DSurfaceFloatData(FRHITexture* Texture,FIntRect Rect,FIntPoint ZMinMax,TArray<FFloat16Color>& OutData) final override`
- L392 _public function_ `virtual FRenderQueryRHIRef RHICreateRenderQuery(ERenderQueryType QueryType) final override`
- L397 _public function_ `virtual void RHIBeginRenderQuery(FRHIRenderQuery* RenderQuery) final override`
- L401 _public function_ `virtual void RHIEndRenderQuery(FRHIRenderQuery* RenderQuery) final override`
- L407 _public function_ `virtual bool RHIGetRenderQueryResult(FRHIRenderQuery* RenderQuery, uint64& OutResult, bool bWait, uint32 GPUIndex = INDEX_NONE) final override`
- L412 _public function_ `virtual void RHIEndDrawingViewport(FRHICommandListImmediate& RHICmdList, FRHIViewport* Viewport, const FRHIPresentArgs& PresentArgs) final override`
- L416 _public function_ `virtual FTextureRHIRef RHIGetViewportBackBuffer(FRHIViewport* Viewport) final override`
- L425 _public prototype_ `virtual void RHIEndFrame(const FRHIEndFrameArgs& Args) final override;`
- L427 _public function_ `virtual void RHIAliasTextureResources(FTextureRHIRef& DestTexture, FTextureRHIRef& SrcTexture) final override`
- L432 _public function_ `virtual FViewportRHIRef RHICreateViewport(void* WindowHandle, uint32 SizeX, uint32 SizeY, bool bIsFullscreen, EPixelFormat PixelFormat) final override`
- L437 _public function_ `virtual void RHIResizeViewport(FRHIViewport* Viewport, uint32 SizeX, uint32 SizeY, bool bIsFullscreen, EPixelFormat PixelFormat) final override`
- L442 _public function_ `virtual void RHITick(float DeltaTime) final override`
- L447 _public function_ `virtual void RHISetStreamSource(uint32 StreamIndex, FRHIBuffer* VertexBuffer, uint32 Offset) final override`
- L451 _public function_ `virtual void RHISetRasterizerState(FRHIRasterizerState* NewState) final override`
- L456 _public function_ `virtual void RHISetViewport(float MinX, float MinY, float MinZ, float MaxX, float MaxY, float MaxZ) final override`
- L461 _public function_ `virtual void RHISetScissorRect(bool bEnable, uint32 MinX, uint32 MinY, uint32 MaxX, uint32 MaxY) final override`
- L465 _public function_ `virtual void RHISetBoundShaderState(FRHIBoundShaderState* BoundShaderState) final override`
- L469 _public function_ `virtual void RHISetShaderParameters(FRHIGraphicsShader* Shader, TConstArrayView<uint8> InParametersData, TConstArrayView<FRHIShaderParameter> InParameters, TConstArrayView<FRHIShaderParameterResource> InResourceParameters, TConstArrayView<FRHIShaderParameterResource> InBindlessParameters) final override`
- L473 _public function_ `virtual void RHISetShaderParameters(FRHIComputeShader* Shader, TConstArrayView<uint8> InParametersData, TConstArrayView<FRHIShaderParameter> InParameters, TConstArrayView<FRHIShaderParameterResource> InResourceParameters, TConstArrayView<FRHIShaderParameterResource> InBindlessParameters) final override`
- L477 _public function_ `virtual void RHISetDepthStencilState(FRHIDepthStencilState* NewState, uint32 StencilRef) final override`
- L482 _public function_ `virtual void RHISetBlendState(FRHIBlendState* NewState, const FLinearColor& BlendFactor) final override`
- L487 _public function_ `virtual void RHIBeginRenderPass(const FRHIRenderPassInfo& InInfo, const TCHAR* InName)`
- L491 _public function_ `virtual void RHIEndRenderPass()`
- L495 _public function_ `virtual void RHIDrawPrimitive(uint32 BaseVertexIndex, uint32 NumPrimitives, uint32 NumInstances) final override`
- L499 _public function_ `virtual void RHIDrawPrimitiveIndirect(FRHIBuffer* ArgumentBuffer, uint32 ArgumentOffset) final override`
- L503 _public function_ `virtual void RHIDrawIndexedPrimitive(FRHIBuffer* IndexBuffer, int32 BaseVertexIndex, uint32 FirstInstance, uint32 NumVertices, uint32 StartIndex, uint32 NumPrimitives, uint32 NumInstances) final override`
- L507 _public function_ `virtual void RHIDrawIndexedPrimitiveIndirect(FRHIBuffer* IndexBuffer, FRHIBuffer* ArgumentBuffer, uint32 ArgumentOffset) final override`
- L511 _public function_ `virtual void RHIMultiDrawIndexedPrimitiveIndirect(FRHIBuffer* IndexBuffer, FRHIBuffer* ArgumentBuffer, uint32 ArgumentOffset, FRHIBuffer* CountBuffer, uint32 CountBufferOffset, uint32 MaxDrawArguments) final override`
- L515 _public function_ `virtual void RHIBlockUntilGPUIdle() final override`
- L518 _public function_ `virtual bool RHIGetAvailableResolutions(FScreenResolutionArray& Resolutions, bool bIgnoreRefreshRate) final override`
- L522 _public function_ `virtual void RHIGetSupportedResolution(uint32& Width, uint32& Height) final override`
- L526 _public function_ `virtual void RHIEnableDepthBoundsTest(bool bEnable) final override`
- L529 _public function_ `virtual void RHISetDepthBounds(float MinDepth, float MaxDepth) final override`
- L532 _public function_ `virtual void RHISetShadingRate(EVRSShadingRate ShadingRate, EVRSRateCombiner Combiner) final override`
- L535 _public function_ `virtual void* RHIGetNativeDevice() final override`
- L540 _public function_ `virtual void RHISetStaticUniformBuffers(const FUniformBufferStaticBindings& InUniformBuffers) final override`
- L544 _public function_ `virtual void RHISetStaticUniformBuffer(FUniformBufferStaticSlot Slot, FRHIUniformBuffer* UniformBuffer) final override`
- L549 _public function_ `virtual void RHIBeginBreadcrumbGPU(FRHIBreadcrumbNode* Breadcrumb) final override`
- L552 _public function_ `virtual void RHIEndBreadcrumbGPU(FRHIBreadcrumbNode* Breadcrumb) final override`
- L557 _public function_ `virtual class IRHICommandContext* RHIGetDefaultContext() final override`
- L562 _public function_ `virtual IRHIComputeContext* RHIGetCommandContext(ERHIPipeline Pipeline) final override`
- L567 _public function_ `virtual FRHIFinalizeContextsResult RHIFinalizeContexts(FRHIFinalizeContextsArgs&& Args) final override`
- L572 _public function_ `virtual void RHISubmitCommandLists(FRHISubmitCommandListsArgs&& Args) final override`
- L577 _private member_ `FLargeMemoryData MemoryBuffer;`
- L580 _private prototype_ `void* GetStaticBuffer(size_t Size);` — Allocates a static buffer for RHI functions to return as a write destination.
- L581 _private prototype_ `void* GetStaticTextureBuffer(int32 SizeX, int32 SizeY, EPixelFormat Format, uint32& DestStride, uint64* OutLockedByteCount = nullptr);`

#### class `FNullDynamicRHI::FNullBuffer`  
`class FNullBuffer : public FRHIBuffer`  
_L127-134_
- inherits: `FRHIBuffer`
- L130 _public function_ `FNullBuffer(const FRHIBufferCreateDesc& CreateDesc) : FRHIBuffer(CreateDesc)`

#### struct `FNullDynamicRHI::FNullBufferInitializer`  
`struct FNullBufferInitializer : public FRHIBufferInitializer`  
_L136-147_
- inherits: `FRHIBufferInitializer`
- L138 _public function_ `FNullBufferInitializer(FRHICommandListBase& RHICmdList, FNullBuffer* Buffer, void* InWritableData, uint64 InWritableDataSize) : FRHIBufferInitializer(RHICmdList, Buffer, InWritableData, InWritableDataSize, [Buffer = TRefCountPtr<FNullBuffer>(Buffer)](FRHICommandListBase&) mutable { return TRefCountPtr<FRHIBuffer>(MoveTemp(Buffer)); } )`
- L141 _public function_ ``

#### class `FNullDynamicRHI::FNullTexture`  
`class FNullTexture : public FRHITexture`  
_L211-217_
- inherits: `FRHITexture`
- L214 _public function_ `FNullTexture(const FRHITextureCreateDesc& InDesc) : FRHITexture(InDesc)`

#### struct `FNullDynamicRHI::FNullTextureInitializer`  
`struct FNullTextureInitializer : public FRHITextureInitializer`  
_L219-245_
- inherits: `FRHITextureInitializer`
- L221 _public function_ `FNullTextureInitializer(FRHICommandListBase& RHICmdList, FRHITexture* Texture, void* InWritableData, uint64 InWritableDataSize) : FRHITextureInitializer(RHICmdList, Texture, InWritableData, InWritableDataSize, [Texture = TRefCountPtr<FRHITexture>(Texture)](FRHICommandListBase&) mutable { return MoveTemp(Texture); }, [Texture = TRefCountPtr<FRHITexture>(Texture), WritableData = InWritableData](FRHITextureInitializer::FSubresourceIndex SubresourceIndex) { const FRHITextureDesc& TextureDesc = Texture->GetDesc(); uint64 SubresourceStride = 0; uint64 SubresourceSize = 0; const uint64 Offset = UE::RHITextureUtils::CalculateSubresourceOffset(TextureDesc, SubresourceIndex.FaceIndex, SubresourceIndex.ArrayIndex, SubresourceIndex.MipIndex, SubresourceStride, SubresourceSize); FRHITextureSubresourceInitializer Result{}; Result.Data = reinterpret_cast<uint8*>(WritableData) + Offset; Result.Stride = SubresourceStride; Result.Size = SubresourceSize; return Result; } )`
- L224 _public function_ ``

#### class `FNullDynamicRHI::RHICreateGPUFence::FNullGPUFence`  
`class FNullGPUFence final : public FRHIGPUFence`  
_L346-365_
- inherits: `FRHIGPUFence`
- L349 _public function_ `FNullGPUFence(const FName& Name) : FRHIGPUFence(Name)`
- L353 _public function_ `virtual void Clear() override`
- L357 _public function_ `virtual bool Poll() const override`
- L362 _public function_ `virtual void Wait(FRHICommandListImmediate& RHICmdList, FRHIGPUMask GPUMask) const override`
