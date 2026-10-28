# Runtime / D3D11RHI

- module root: `Source/Runtime/Windows/D3D11RHI`
- headers: 13; symbols: 883
- symbol kinds: class=32, delegate=22, enum=11, enumerator=17, externvar=4, function=153, macro=27, member=232, namespace=6, prototype=311, struct=39, typedef=27, variable=2
- PrivateDependencyModuleNames: HeadMountedDisplay
- PublicDependencyModuleNames: WindowsD3D

### `Source/Runtime/Windows/D3D11RHI/Private/D3D11NvidiaAftermath.h` (Private)


#### Free symbols / members of external scopes

- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace RHICore` (scope `UE`)
- L14 _namespace_ `namespace Nvidia` (scope `UE::RHICore`)
- L14 _namespace_ `namespace Aftermath` (scope `UE::RHICore::Nvidia`)
- L14 _namespace_ `namespace D3D11` (scope `UE::RHICore::Nvidia::Aftermath`)
- L16 _typedef_ `typedef struct GFSDK_Aftermath_ContextHandle__* FCommandList;` (scope `UE::RHICore::Nvidia::Aftermath::D3D11`)
- L17 _typedef_ `typedef struct GFSDK_Aftermath_ResourceHandle__* FResource;` (scope `UE::RHICore::Nvidia::Aftermath::D3D11`)
- L19 _prototype_ `FCommandList InitializeDevice(ID3D11Device* Device, ID3D11DeviceContext* DeviceContext);` (scope `UE::RHICore::Nvidia::Aftermath::D3D11`)
- L20 _prototype_ `void UnregisterCommandList(FCommandList CommandList);` (scope `UE::RHICore::Nvidia::Aftermath::D3D11`)
- L23 _prototype_ `void BeginBreadcrumb(FCommandList CommandList, FRHIBreadcrumbNode* Breadcrumb);` (scope `UE::RHICore::Nvidia::Aftermath::D3D11`)
- L24 _prototype_ `void EndBreadcrumb (FCommandList CommandList, FRHIBreadcrumbNode* Breadcrumb);` (scope `UE::RHICore::Nvidia::Aftermath::D3D11`)

### `Source/Runtime/Windows/D3D11RHI/Private/D3D11RHIPrivate.h` (Private)


#### struct `FD3D11GlobalStats`  
`struct FD3D11GlobalStats`  
_L90-103_
- L93 _public member_ `static int64 GDedicatedVideoMemory;` — in bytes, never change after RHI, needed to scale game features
- L96 _public member_ `static int64 GDedicatedSystemMemory;` — in bytes, never change after RHI, needed to scale game features
- L99 _public member_ `static int64 GSharedSystemMemory;` — in bytes, never change after RHI, needed to scale game features
- L102 _public member_ `static int64 GTotalGraphicsMemory;` — In bytes. Never changed after RHI init. Our estimate of the amount of memory that we can use for graphics resources in total.

#### struct `FD3D11TransitionData`  
`struct FD3D11TransitionData`  
_L105-108_
- L107 _public member_ `bool bUAVBarrier;`

#### struct `FD3D11DeviceBasicInfo`  
`struct FD3D11DeviceBasicInfo`  
_L114-118_
- L116 _public member_ `D3D_FEATURE_LEVEL MaxFeatureLevel;`
- L117 _public member_ `bool bUMA;`

#### struct `FD3D11Adapter`  
`struct FD3D11Adapter`  
_L120-157_
- L123 _public member_ `TRefCountPtr<IDXGIAdapter> DXGIAdapter;` — Null if not supported or FindAdapter() wasn't called.
- L125 _public member_ `DXGI_ADAPTER_DESC DXGIAdapterDesc;`
- L128 _public member_ `D3D_FEATURE_LEVEL MaxSupportedFeatureLevel;` — The maximum D3D11 feature level supported. 0 if not supported or FindAdapter() wasn't called
- L131 _public member_ `bool bSoftwareAdapter;` — Whether this is a software adapter
- L134 _public member_ `bool bUMA;` — Whether the GPU has unified memory. This can be used to identify integrated GPU as well.
- L137 _public function_ `FD3D11Adapter()` — constructors
- L141 _public function_ `FD3D11Adapter(TRefCountPtr<IDXGIAdapter> InDXGIAdapter, bool bInSoftwareAdatper, const FD3D11DeviceBasicInfo& DeviceInfo) : DXGIAdapter(InDXGIAdapter) , MaxSupportedFeatureLevel(DeviceInfo.MaxFeatureLevel) , bSoftwareAdapter(bInSoftwareAdatper) , bUMA(DeviceInfo.bUMA)`
- L153 _public function_ `bool IsValid() const`

#### class `FD3D11DynamicRHI`  
`class FD3D11DynamicRHI : public ID3D11DynamicRHI, public IRHICommandContextPSOFallback`  
_L162-786_
- inherits: `ID3D11DynamicRHI,IRHICommandContextPSOFallback`
- desc: The interface which is implemented by the dynamically bound RHI.
- L165 _public typedef_ `typedef TMap<FD3D11LockedKey, FD3D11LockedData> FD3D11LockTracker;`
- L169 _public prototype_ `FD3D11DynamicRHI(IDXGIFactory1* InDXGIFactory1, D3D_FEATURE_LEVEL InFeatureLevel, const FD3D11Adapter& InAdapter);` — Initialization constructor.
- L172 _public prototype_ `virtual ~FD3D11DynamicRHI();` — Destructor
- L175 _public prototype_ `virtual void InitD3DDevice();` — If it hasn't been initialized yet, initializes the D3D device.
- L178 _public prototype_ `virtual void Init() override;` — FDynamicRHI interface.
- L179 _public prototype_ `virtual void Shutdown() override;`
- L180 _public function_ `virtual const TCHAR* GetName() override`
- L182 _public prototype_ `virtual void FlushPendingLogs() override;`
- L184 _public function_ `static FD3D11DynamicRHI& Get()`
- L187 _public function_ `template<typename TRHIType> static FORCEINLINE typename TD3D11ResourceTraits<TRHIType>::TConcreteType* ResourceCast(TRHIType* Resource)`
- L192 _public function_ `static inline FD3D11Texture* ResourceCast(FRHITexture* Texture)`
- L206 _public prototype_ `template<EShaderFrequency ShaderFrequency> void BindUniformBuffer(uint32 BufferIndex, FRHIUniformBuffer* BufferRHI);`
- L209 _public prototype_ `template <typename TRHIShader> void ApplyStaticUniformBuffers(TRHIShader* Shader);`
- L212 _public prototype_ `template<EShaderFrequency ShaderFrequency> void SetShaderParametersCommon(FD3D11ConstantBuffer* StageConstantBuffer, TConstArrayView<uint8> InParametersData, TConstArrayView<FRHIShaderParameter> InParameters, TConstArrayView<FRHIShaderParameterResource> InResourceParameters);`
- L215 _public prototype_ `template<EShaderFrequency ShaderFrequency> void SetShaderUnbindsCommon(TConstArrayView<FRHIShaderParameterUnbind> InUnbinds);`
- L226 _public prototype_ `bool GetQueryData(ID3D11Query* Query, void* Data, SIZE_T DataSize, bool bTimestamp, bool bWait);` — Reads a D3D query's data into the provided buffer. @param Query - The D3D query to read data from. @param Data - The buffer to read the data into. @param DataSize - The size of the buffer. @param QueryType e.g. RQT_Occlusion or RQT_AbsoluteTime @param bWait - If true, it will wait for the query to finish. @return true if the query finished.
- L228 _public prototype_ `virtual FSamplerStateRHIRef RHICreateSamplerState(const FSamplerStateInitializerRHI& Initializer) final override;`
- L229 _public prototype_ `virtual FRasterizerStateRHIRef RHICreateRasterizerState(const FRasterizerStateInitializerRHI& Initializer) final override;`
- L230 _public prototype_ `virtual FDepthStencilStateRHIRef RHICreateDepthStencilState(const FDepthStencilStateInitializerRHI& Initializer) final override;`
- L231 _public prototype_ `virtual FBlendStateRHIRef RHICreateBlendState(const FBlendStateInitializerRHI& Initializer) final override;`
- L232 _public prototype_ `virtual FVertexDeclarationRHIRef RHICreateVertexDeclaration(const FVertexDeclarationElementList& Elements) final override;`
- L233 _public prototype_ `virtual FPixelShaderRHIRef RHICreatePixelShader(const FRHICreateShaderDesc& CreateShaderDesc) final override;`
- L234 _public prototype_ `virtual FVertexShaderRHIRef RHICreateVertexShader(const FRHICreateShaderDesc& CreateShaderDesc) final override;`
- L235 _public prototype_ `virtual FGeometryShaderRHIRef RHICreateGeometryShader(const FRHICreateShaderDesc& CreateShaderDesc) final override;`
- L236 _public prototype_ `virtual FComputeShaderRHIRef RHICreateComputeShader(const FRHICreateShaderDesc& CreateShaderDesc) final override;`
- L237 _public prototype_ `virtual FStagingBufferRHIRef RHICreateStagingBuffer() final override;`
- L238 _public prototype_ `virtual void RHICopyToStagingBuffer(FRHIBuffer* SourceBuffer, FRHIStagingBuffer* DestinationStagingBuffer, uint32 Offset, uint32 NumBytes) final override;`
- L239 _public prototype_ `virtual FGPUFenceRHIRef RHICreateGPUFence(const FName& Name) final override;`
- L240 _public prototype_ `virtual void RHIWriteGPUFence_TopOfPipe(FRHICommandListBase& RHICmdList, FRHIGPUFence* FenceRHI) final override;`
- L241 _public prototype_ `virtual void RHIWriteGPUFence(FRHIGPUFence* Fence) final override;`
- L242 _public prototype_ `virtual void* RHILockStagingBuffer(FRHIStagingBuffer* StagingBuffer, FRHIGPUFence* Fence, uint32 Offset, uint32 SizeRHI) final override;`
- L243 _public prototype_ `virtual void RHIUnlockStagingBuffer(FRHIStagingBuffer* StagingBuffer) final override;`
- L244 _public prototype_ `virtual FBoundShaderStateRHIRef RHICreateBoundShaderState(FRHIVertexDeclaration* VertexDeclaration, FRHIVertexShader* VertexShader, FRHIPixelShader* PixelShader, FRHIGeometryShader* GeometryShader) final override;`
- L245 _public prototype_ `virtual FUniformBufferRHIRef RHICreateUniformBuffer(const void* Contents, const FRHIUniformBufferLayout* Layout, EUniformBufferUsage Usage, EUniformBufferValidation Validation) final override;`
- L246 _public prototype_ `virtual void RHIUpdateUniformBuffer(FRHICommandListBase& RHICmdList, FRHIUniformBuffer* UniformBufferRHI, const void* Contents) final override;`
- L249 _public prototype_ `virtual void RHIUpdateAllocationTags(FRHICommandListBase& RHICmdList, FRHIBuffer* Buffer) final override;`
- L252 _public prototype_ `[[nodiscard]] FD3D11Buffer* BeginCreateBufferInternal(const FRHIBufferCreateDesc& CreateDesc);`
- L253 _public prototype_ `void FinalizeCreateBufferInternal(FD3D11Buffer* Buffer, TConstArrayView<uint8> InitialData);`
- L254 _public prototype_ `[[nodiscard]] FD3D11Buffer* CreateBufferInternal(const FRHIBufferCreateDesc& CreateDesc, TConstArrayView<uint8> InitialData);`
- L256 _public prototype_ `[[nodiscard]] virtual FRHIBufferInitializer RHICreateBufferInitializer(FRHICommandListBase& RHICmdList, const FRHIBufferCreateDesc& CreateDesc) final override;`
- L258 _public prototype_ `virtual void RHIReplaceResources(FRHICommandListBase& RHICmdList, TArray<FRHIResourceReplaceInfo>&& ReplaceInfos) final override;`
- L259 _public prototype_ `virtual void* LockBuffer_BottomOfPipe(FRHICommandListBase& RHICmdList, FRHIBuffer* Buffer, uint32 Offset, uint32 Size, EResourceLockMode LockMode) final override;`
- L260 _public prototype_ `virtual void UnlockBuffer_BottomOfPipe(FRHICommandListBase& RHICmdList, FRHIBuffer* Buffer) final override;`
- L261 _public prototype_ `virtual FRHICalcTextureSizeResult RHICalcTexturePlatformSize(FRHITextureDesc const& Desc, uint32 FirstMipIndex) final override;`
- L262 _public prototype_ `virtual void RHIGetTextureMemoryStats(FTextureMemoryStats& OutStats) final override;`
- L263 _public prototype_ `virtual bool RHIGetTextureMemoryVisualizeData(FColor* TextureData,int32 SizeX,int32 SizeY,int32 Pitch,int32 PixelSize) final override;`
- L265 _public prototype_ `[[nodiscard]] FD3D11Texture* BeginCreateTextureInternal(const FRHITextureCreateDesc& CreateDesc);`
- L266 _public prototype_ `void FinalizeCreateTexture2DInternal(FD3D11Texture* Texture, TConstArrayView<D3D11_SUBRESOURCE_DATA> InitialData);`
- L267 _public prototype_ `void FinalizeCreateTexture3DInternal(FD3D11Texture* Texture, TConstArrayView<D3D11_SUBRESOURCE_DATA> InitialData);`
- L268 _public prototype_ `FD3D11Texture* FinalizeCreateTextureInternal(FD3D11Texture* Texture, const FRHITextureDesc& InDesc, TConstArrayView<uint8> InitialData);`
- L269 _public prototype_ `[[nodiscard]] FD3D11Texture* CreateTextureInternal(const FRHITextureCreateDesc& CreateDesc, TConstArrayView<uint8> InitialData);`
- L270 _public prototype_ `[[nodiscard]] virtual FRHITextureInitializer RHICreateTextureInitializer(FRHICommandListBase& RHICmdList, const FRHITextureCreateDesc& CreateDesc) final override;`
- L271 _public prototype_ `virtual FTextureRHIRef RHIAsyncCreateTexture2D(uint32 SizeX, uint32 SizeY, uint8 Format, uint32 NumMips, ETextureCreateFlags Flags, ERHIAccess InResourceState, void** InitialMipData, uint32 NumInitialMips, const TCHAR* DebugName, FGraphEventRef& OutCompletionEvent) final override;`
- L272 _public prototype_ `virtual uint32 RHIComputeMemorySize(FRHITexture* TextureRHI) final override;`
- L273 _public prototype_ `virtual void RHIGetMemoryStats(FRHIMemoryStats& OutStats) final override;`
- L275 _public prototype_ `virtual FRHILockTextureResult RHILockTexture(FRHICommandListImmediate& RHICmdList, const FRHILockTextureArgs& Arguments) final override;`
- L276 _public prototype_ `virtual void RHIUnlockTexture(FRHICommandListImmediate& RHICmdList, const FRHILockTextureArgs& Arguments) final override;`
- L278 _public prototype_ `virtual void RHIUpdateTexture2D(FRHICommandListBase& RHICmdList, FRHITexture* Texture, uint32 MipIndex, const struct FUpdateTextureRegion2D& UpdateRegion, uint32 SourcePitch, const uint8* SourceData) final override;`
- L279 _public prototype_ `virtual void RHIUpdateTexture3D(FRHICommandListBase& RHICmdList, FRHITexture* Texture, uint32 MipIndex, const struct FUpdateTextureRegion3D& UpdateRegion, uint32 SourceRowPitch, uint32 SourceDepthPitch, const uint8* SourceData) final override;`
- L280 _public prototype_ `virtual void RHIBindDebugLabelName(FRHICommandListBase& RHICmdList, FRHITexture* Texture, const TCHAR* Name) final override;`
- L281 _public prototype_ `virtual void RHIBindDebugLabelName(FRHICommandListBase& RHICmdList, FRHIBuffer* Buffer, const TCHAR* Name) final override;`
- L282 _public prototype_ `virtual void RHIBindDebugLabelName(FRHICommandListBase& RHICmdList, FRHIUnorderedAccessView* UnorderedAccessViewRHI, const TCHAR* Name) final override;`
- L283 _public prototype_ `virtual void RHIReadSurfaceData(FRHITexture* Texture,FIntRect Rect,TArray<FColor>& OutData,FReadSurfaceDataFlags InFlags) final override;`
- L284 _public prototype_ `virtual void RHIReadSurfaceData(FRHITexture* TextureRHI, FIntRect InRect, TArray<FLinearColor>& OutData, FReadSurfaceDataFlags InFlags) final override;`
- L285 _public prototype_ `virtual void RHIMapStagingSurface(FRHITexture* Texture, FRHIGPUFence* Fence, void*& OutData, int32& OutWidth, int32& OutHeight, uint32 GPUIndex = 0) final override;`
- L286 _public prototype_ `virtual void RHIUnmapStagingSurface(FRHITexture* Texture, uint32 GPUIndex = 0) final override;`
- L287 _public prototype_ `virtual void RHIReadSurfaceFloatData(FRHITexture* Texture,FIntRect Rect,TArray<FFloat16Color>& OutData,ECubeFace CubeFace,int32 ArrayIndex,int32 MipIndex) final override;`
- L288 _public prototype_ `virtual void RHIRead3DSurfaceFloatData(FRHITexture* Texture,FIntRect Rect,FIntPoint ZMinMax,TArray<FFloat16Color>& OutData) final override;`
- L289 _public prototype_ `virtual FRenderQueryRHIRef RHICreateRenderQuery(ERenderQueryType QueryType) final override;`
- L290 _public prototype_ `virtual bool RHIGetRenderQueryResult(FRHIRenderQuery* RenderQuery, uint64& OutResult, bool bWait, uint32 GPUIndex = INDEX_NONE) final override;`
- L291 _public prototype_ `virtual FTextureRHIRef RHIGetViewportBackBuffer(FRHIViewport* Viewport) final override;`
- L292 _public prototype_ `virtual void RHIAliasTextureResources(FTextureRHIRef& DestTexture, FTextureRHIRef& SrcTexture) final override;`
- L293 _public prototype_ `virtual FTextureRHIRef RHICreateAliasedTexture(FTextureRHIRef& SourceTexture) final override;`
- L294 _public prototype_ `virtual FViewportRHIRef RHICreateViewport(void* WindowHandle, uint32 SizeX, uint32 SizeY, bool bIsFullscreen, EPixelFormat PixelFormat) override;`
- L295 _public prototype_ `virtual void RHIResizeViewport(FRHIViewport* Viewport, uint32 SizeX, uint32 SizeY, bool bIsFullscreen, EPixelFormat PixelFormat) final override;`
- L296 _public prototype_ `virtual void RHIHandleDisplayChange() final override;`
- L297 _public prototype_ `virtual void RHITick(float DeltaTime) final override;`
- L298 _public prototype_ `virtual void RHIBlockUntilGPUIdle() final override;`
- L299 _public prototype_ `virtual bool RHIGetAvailableResolutions(FScreenResolutionArray& Resolutions, bool bIgnoreRefreshRate) final override;`
- L300 _public prototype_ `virtual bool RHIGetAvailableResolutionsForDisplay(FScreenResolutionArray& Resolutions, bool bIgnoreRefreshRate, void* NativeMonitorHandle) final override;`
- L301 _public prototype_ `virtual void RHIGetSupportedResolution(uint32& Width, uint32& Height) final override;`
- L302 _public prototype_ `virtual void* RHIGetNativeDevice() final override;`
- L303 _public prototype_ `virtual void* RHIGetNativeCommandBuffer() final override;`
- L304 _public prototype_ `virtual class IRHICommandContext* RHIGetDefaultContext() final override;`
- L305 _public prototype_ `virtual IRHIComputeContext* RHIGetCommandContext(ERHIPipeline Pipeline) final override;`
- L306 _public prototype_ `virtual FRHIFinalizeContextsResult RHIFinalizeContexts(FRHIFinalizeContextsArgs&& Args) final override;`
- L307 _public prototype_ `virtual void RHISubmitCommandLists(FRHISubmitCommandListsArgs&& Args) final override;`
- L310 _public prototype_ `virtual FShaderResourceViewRHIRef RHICreateShaderResourceView (class FRHICommandListBase& RHICmdList, FRHIViewableResource* Resource, FRHIViewDesc const& ViewDesc) final override;` — SRV / UAV creation functions
- L311 _public prototype_ `virtual FUnorderedAccessViewRHIRef RHICreateUnorderedAccessView(class FRHICommandListBase& RHICmdList, FRHIViewableResource* Resource, FRHIViewDesc const& ViewDesc) final override;`
- L313 _public prototype_ `virtual void RHISetComputeShader(FRHIComputeShader* ComputeShader) final override;`
- L314 _public prototype_ `virtual void RHIDispatchComputeShader(uint32 ThreadGroupCountX, uint32 ThreadGroupCountY, uint32 ThreadGroupCountZ) final override;`
- L315 _public prototype_ `virtual void RHIDispatchIndirectComputeShader(FRHIBuffer* ArgumentBuffer, uint32 ArgumentOffset) final override;`
- L316 _public prototype_ `virtual void RHISetMultipleViewports(uint32 Count, const FViewportBounds* Data) final override;`
- L317 _public prototype_ `virtual void RHIClearUAVFloat(FRHIUnorderedAccessView* UnorderedAccessViewRHI, const FVector4f& Values) final override;`
- L318 _public prototype_ `virtual void RHIClearUAVUint(FRHIUnorderedAccessView* UnorderedAccessViewRHI, const FUintVector4& Values) final override;`
- L319 _public prototype_ `virtual void RHICopyTexture(FRHITexture* SourceTexture, FRHITexture* DestTexture, const FRHICopyTextureInfo& CopyInfo) final override;`
- L320 _public prototype_ `virtual void RHICopyBufferRegion(FRHIBuffer* DestBuffer, uint64 DstOffset, FRHIBuffer* SourceBuffer, uint64 SrcOffset, uint64 NumBytes) final override;`
- L321 _public prototype_ `virtual void RHICreateTransition(FRHITransition* Transition, const FRHITransitionCreateInfo& CreateInfo) final override;`
- L322 _public prototype_ `virtual void RHIReleaseTransition(FRHITransition* Transition) final override;`
- L323 _public prototype_ `virtual void RHIBeginTransitions(TArrayView<const FRHITransition*> Transitions) override final;`
- L324 _public prototype_ `virtual void RHIEndTransitions(TArrayView<const FRHITransition*> Transitions) override final;`
- L326 _public prototype_ `virtual void RHIEndRenderQuery_TopOfPipe (FRHICommandListBase& RHICmdList, FRHIRenderQuery* RenderQuery) override final;`
- L327 _public prototype_ `virtual void RHIBeginRenderQuery(FRHIRenderQuery* RenderQuery) final override;`
- L328 _public prototype_ `virtual void RHIEndRenderQuery (FRHIRenderQuery* RenderQuery) final override;`
- L330 _public prototype_ `virtual void RHIEndDrawingViewport(FRHICommandListImmediate& RHICmdList, FRHIViewport* Viewport, const FRHIPresentArgs& PresentArgs) final override;`
- L331 _public prototype_ `virtual void RHIEndFrame(const FRHIEndFrameArgs& Args) final override;`
- L332 _public prototype_ `virtual void RHISetStreamSource(uint32 StreamIndex, FRHIBuffer* VertexBuffer, uint32 Offset) final override;`
- L333 _public prototype_ `virtual void RHISetRasterizerState(FRHIRasterizerState* NewState) final override;`
- L334 _public prototype_ `virtual void RHISetViewport(float MinX, float MinY, float MinZ, float MaxX, float MaxY, float MaxZ) final override;`
- L335 _public prototype_ `virtual void RHISetStereoViewport(float LeftMinX, float RightMinX, float LeftMinY, float RightMinY, float MinZ, float LeftMaxX, float RightMaxX, float LeftMaxY, float RightMaxY, float MaxZ) override;`
- L336 _public prototype_ `virtual void RHISetScissorRect(bool bEnable, uint32 MinX, uint32 MinY, uint32 MaxX, uint32 MaxY) final override;`
- L337 _public prototype_ `virtual void RHISetBoundShaderState(FRHIBoundShaderState* BoundShaderState) final override;`
- L338 _public prototype_ `virtual void RHISetGraphicsPipelineState(FRHIGraphicsPipelineState* GraphicsState, uint32 StencilRef, bool bApplyAdditionalState) final override;`
- L339 _public prototype_ `virtual void RHISetStaticUniformBuffers(const FUniformBufferStaticBindings& InUniformBuffers) final override;`
- L340 _public prototype_ `virtual void RHISetStaticUniformBuffer(FUniformBufferStaticSlot Slot, FRHIUniformBuffer* Buffer) final override;`
- L341 _public prototype_ `virtual void RHISetShaderParameters(FRHIComputeShader* Shader, TConstArrayView<uint8> InParametersData, TConstArrayView<FRHIShaderParameter> InParameters, TConstArrayView<FRHIShaderParameterResource> InResourceParameters, TConstArrayView<FRHIShaderParameterResource> InBindlessParameters) final override;`
- L342 _public prototype_ `virtual void RHISetShaderParameters(FRHIGraphicsShader* Shader, TConstArrayView<uint8> InParametersData, TConstArrayView<FRHIShaderParameter> InParameters, TConstArrayView<FRHIShaderParameterResource> InResourceParameters, TConstArrayView<FRHIShaderParameterResource> InBindlessParameters) final override;`
- L343 _public prototype_ `virtual void RHISetShaderUnbinds(FRHIComputeShader* Shader, TConstArrayView<FRHIShaderParameterUnbind> InUnbinds) final override;`
- L344 _public prototype_ `virtual void RHISetShaderUnbinds(FRHIGraphicsShader* Shader, TConstArrayView<FRHIShaderParameterUnbind> InUnbinds) final override;`
- L345 _public prototype_ `virtual void RHISetDepthStencilState(FRHIDepthStencilState* NewState, uint32 StencilRef) final override;`
- L346 _public prototype_ `virtual void RHISetStencilRef(uint32 StencilRef) final override;`
- L347 _public prototype_ `virtual void RHISetBlendState(FRHIBlendState* NewState, const FLinearColor& BlendFactor) final override;`
- L348 _public prototype_ `virtual void RHISetBlendFactor(const FLinearColor& BlendFactor) final override;`
- L349 _public prototype_ `void SetRenderTargets(uint32 NumSimultaneousRenderTargets, const FRHIRenderTargetView* NewRenderTargets, const FRHIDepthRenderTargetView* NewDepthStencilTarget);`
- L350 _public prototype_ `void InternalSetUAVCS(uint32 BindIndex, FD3D11UnorderedAccessView* UnorderedAccessViewRHI);`
- L351 _public prototype_ `void InternalSetUAVVSPS(uint32 BindIndex, FD3D11UnorderedAccessView* UnorderedAccessViewRHI);`
- L352 _public prototype_ `void SetRenderTargetsAndClear(const FRHISetRenderTargetsInfo& RenderTargetsInfo);`
- L353 _public prototype_ `virtual void RHIDrawPrimitive(uint32 BaseVertexIndex, uint32 NumPrimitives, uint32 NumInstances) final override;`
- L354 _public prototype_ `virtual void RHIDrawPrimitiveIndirect(FRHIBuffer* ArgumentBuffer, uint32 ArgumentOffset) final override;`
- L355 _public prototype_ `virtual void RHIDrawIndexedPrimitive(FRHIBuffer* IndexBuffer, int32 BaseVertexIndex, uint32 FirstInstance, uint32 NumVertices, uint32 StartIndex, uint32 NumPrimitives, uint32 NumInstances) final override;`
- L356 _public prototype_ `virtual void RHIDrawIndexedPrimitiveIndirect(FRHIBuffer* IndexBuffer, FRHIBuffer* ArgumentBuffer, uint32 ArgumentOffset) final override;`
- L357 _public function_ `virtual void RHIEnableDepthBoundsTest(bool bEnable) final override`
- L364 _public function_ `virtual void RHISetDepthBounds(float MinDepth, float MaxDepth) final override`
- L372 _public prototype_ `virtual void RHIBeginBreadcrumbGPU(FRHIBreadcrumbNode* Breadcrumb) final override;`
- L373 _public prototype_ `virtual void RHIEndBreadcrumbGPU (FRHIBreadcrumbNode* Breadcrumb) final override;`
- L376 _public prototype_ `void PollQueryResults();`
- L377 _public prototype_ `bool PollQueryResultsForEndFrame(FD3D11RenderQuery* Query);`
- L379 _public prototype_ `virtual void RHIEndUpdateTexture3D(FRHICommandListBase& RHICmdList, FUpdateTexture3DData& UpdateData) final override;`
- L381 _public prototype_ `virtual void RHIBeginRenderPass(const FRHIRenderPassInfo& InInfo, const TCHAR* InName) final override;`
- L382 _public prototype_ `virtual void RHIEndRenderPass() final override;`
- L384 _public prototype_ `void ResolveTexture(UE::RHICore::FResolveTextureInfo Info);`
- L387 _public prototype_ `virtual ID3D11Device* RHIGetDevice() const final override;` — ID3D11DynamicRHI interface
- L388 _public prototype_ `virtual ID3D11DeviceContext* RHIGetDeviceContext() const final override;`
- L389 _public prototype_ `virtual IDXGIAdapter* RHIGetAdapter() const final override;`
- L390 _public prototype_ `virtual IDXGISwapChain* RHIGetSwapChain(FRHIViewport* InViewport) const final override;`
- L391 _public prototype_ `virtual FRHIViewport* RHIGetSingletonViewport() const final override;`
- L392 _public prototype_ `virtual DXGI_FORMAT RHIGetSwapChainFormat(EPixelFormat InFormat) const final override;`
- L393 _public prototype_ `virtual FTextureRHIRef RHICreateTexture2DFromResource(EPixelFormat Format, ETextureCreateFlags TexCreateFlags, const FClearValueBinding& ClearValueBinding, ID3D11Texture2D* Resource) final override;`
- L394 _public prototype_ `virtual FTextureRHIRef RHICreateTexture2DArrayFromResource(EPixelFormat Format, ETextureCreateFlags TexCreateFlags, const FClearValueBinding&, ID3D11Texture2D* Resource) final override;`
- L395 _public prototype_ `virtual FTextureRHIRef RHICreateTextureCubeFromResource(EPixelFormat Format, ETextureCreateFlags TexCreateFlags, const FClearValueBinding& ClearValueBinding, ID3D11Texture2D* Resource) final override;`
- L396 _public prototype_ `virtual ID3D11Buffer* RHIGetResource(FRHIBuffer* InBuffer) const final override;`
- L397 _public prototype_ `virtual ID3D11Resource* RHIGetResource(FRHITexture* InTexture) const final override;`
- L398 _public prototype_ `virtual int64 RHIGetResourceMemorySize(FRHITexture* InTexture) const final override;`
- L399 _public prototype_ `virtual ID3D11RenderTargetView* RHIGetRenderTargetView(FRHITexture* InTexture, int32 InMipIndex = 0, int32 InArraySliceIndex = -1) const final override;`
- L400 _public prototype_ `virtual ID3D11ShaderResourceView* RHIGetShaderResourceView(FRHITexture* InTexture) const final override;`
- L401 _public prototype_ `virtual void RHIVerifyResult(ID3D11Device* Device, HRESULT Result, const ANSICHAR* Code, const ANSICHAR* Filename, uint32 Line) const final override;`
- L403 _public prototype_ `virtual void RHIGetDisplaysInformation(FDisplayInformationArray& OutDisplayInformation) final override;`
- L406 _public function_ `ID3D11Device* GetDevice() const` — Accessors.
- L410 _public function_ `FD3D11DeviceContext* GetDeviceContext() const`
- L415 _public function_ `IDXGIFactory1* GetFactory() const`
- L420 _public function_ `void AddLockedData(const FD3D11LockedKey& Key, const FD3D11LockedData& LockedData)`
- L426 _public function_ `bool RemoveLockedData(const FD3D11LockedKey& Key, FD3D11LockedData& OutLockedData)`
- L432 _public prototype_ `bool IsQuadBufferStereoEnabled();`
- L433 _public prototype_ `void DisableQuadBufferStereo();`
- L435 _public function_ `void BeginRecursiveCommand()`
- L442 _private prototype_ `void InitializeDeviceAgnosticVendorAPI();`
- L445 _private prototype_ `void EnableDepthBoundsTest(bool bEnable, float MinDepth, float MaxDepth);`
- L447 _private prototype_ `static void ClearUAV(TRHICommandList_RecursiveHazardous<FD3D11DynamicRHI>& RHICmdList, FD3D11UnorderedAccessView* UAV, const void* ClearValues, bool bFloat);`
- L455 _private prototype_ `virtual void RHIClearMRTImpl(const bool* bClearColorArray, int32 NumClearColors, const FLinearColor* ColorArray, bool bClearDepth, float Depth, bool bClearStencil, uint32 Stencil);`
- L458 _private prototype_ `template <EShaderFrequency ShaderFrequency> void ClearShaderResourceViews(FD3D11ViewableResource* Resource);`
- L461 _private prototype_ `template <EShaderFrequency ShaderFrequency> void ClearAllShaderResourcesForFrequency();`
- L464 _private prototype_ `template <EShaderFrequency ShaderFrequency> void InternalSetShaderResourceView(FD3D11ViewableResource* Resource, ID3D11ShaderResourceView* SRV, int32 ResourceIndex);`
- L466 _private prototype_ `void TrackResourceBoundAsVB(FD3D11ViewableResource* Resource, int32 StreamIndex);`
- L467 _private prototype_ `void TrackResourceBoundAsIB(FD3D11ViewableResource* Resource);`
- L469 _private function_ `void SetCurrentComputeShader(FRHIComputeShader* ComputeShader)`
- L474 _private function_ `const FComputeShaderRHIRef& GetCurrentComputeShader() const`
- L482 _public function_ `template <EShaderFrequency ShaderFrequency> void SetShaderResourceView(FD3D11ViewableResource* Resource, ID3D11ShaderResourceView* SRV, int32 ResourceIndex)`
- L487 _public prototype_ `void ClearState();`
- L488 _public prototype_ `void ConditionalClearShaderResource(FD3D11ViewableResource* Resource, bool bCheckBoundInputAssembler);`
- L489 _public prototype_ `void ClearAllShaderResources();`
- L491 _public prototype_ `EPixelFormat GetDisplayFormat(EPixelFormat InPixelFormat) const;`
- L493 _public function_ `FD3D11StateCache& GetStateCache()`
- L497 _protected member_ `TRefCountPtr<IDXGIFactory1> DXGIFactory1;` — The global D3D interface.
- L499 _protected member_ `TRefCountPtr<IDXGIFactory1> DXGIFactoryForDisplayList;`
- L500 _protected member_ `TRefCountPtr<IDXGIFactory1> DXGIFactoryForResolutions;`
- L504 _protected member_ `bool bDXGISupportsHDR;` — Whether HDR is available from the particular DXGI factories available
- L507 _protected member_ `TRefCountPtr<FD3D11DeviceContext> Direct3DDeviceIMContext;` — The global D3D device's immediate context
- L510 _protected member_ `TRefCountPtr<ID3DUserDefinedAnnotation> Direct3DDeviceIMAnnotation;`
- L514 _protected member_ `UE::RHICore::Nvidia::Aftermath::D3D11::FCommandList AftermathHandle = nullptr;`
- L518 _protected member_ `TRefCountPtr<FD3D11Device> Direct3DDevice;` — The global D3D device's immediate context
- L520 _protected member_ `FD3D11StateCache StateCache;`
- L523 _protected member_ `FD3D11LockTracker LockTracker;` — Tracks outstanding locks on each thread
- L524 _protected member_ `FCriticalSection LockTrackerCS;`
- L527 _protected member_ `TArray<FD3D11Viewport*> Viewports;` — A list of all viewport RHIs that have been created.
- L530 _protected member_ `D3D_FEATURE_LEVEL FeatureLevel;` — The feature level of the device.
- L537 _protected member_ `AGSContext* AmdAgsContext;` — The context for the AMD AGS utility library. AGSContext does not implement AddRef/Release. Just use a bare pointer.
- L539 _protected member_ `bool bNvAPIInitialized = false;`
- L543 _protected member_ `INTCExtensionContext* IntelExtensionContext;` — Context and functions for Intel extension framework utility library
- L544 _protected member_ `bool bIntelSupportsUAVOverlap;`
- L549 _protected member_ `uint32 AvailableMSAAQualities[DX_MAX_MSAA_COUNT + 1];` — set by UpdateMSAASettings(), get by GetMSAAQuality() [SampleCount] = Quality, 0xffffffff if not supported
- L552 _protected member_ `void* ZeroBuffer;` — A buffer in system memory containing all zeroes of the specified size.
- L553 _protected member_ `uint32 ZeroBufferSize;`
- L556 _protected member_ `bool bCurrentDepthStencilStateIsReadOnly;` — Tracks the currently set state blocks.
- L559 _protected member_ `EPrimitiveType PrimitiveType;` — Current PSO Primitive Type
- L561 _protected member_ `TRefCountPtr<ID3D11RenderTargetView> CurrentRenderTargets[D3D11_SIMULTANEOUS_RENDER_TARGET_COUNT];`
- L562 _protected member_ `TRefCountPtr<FD3D11UnorderedAccessView> CurrentUAVs[D3D11_PS_CS_UAV_REGISTER_COUNT];`
- L563 _protected member_ `ID3D11UnorderedAccessView* UAVBound[D3D11_PS_CS_UAV_REGISTER_COUNT];`
- L564 _protected member_ `uint32 UAVBindFirst;`
- L565 _protected member_ `uint32 UAVBindCount;`
- L566 _protected member_ `uint32 UAVSChanged;`
- L567 _protected member_ `uint32 CurrentRTVOverlapMask;`
- L568 _protected member_ `uint32 CurrentUAVMask;`
- L570 _protected member_ `TRefCountPtr<ID3D11DepthStencilView> CurrentDepthStencilTarget;`
- L571 _protected member_ `TRefCountPtr<FD3D11Texture> CurrentDepthTexture;`
- L572 _protected member_ `FD3D11ViewableResource* CurrentResourcesBoundAsSRVs[SF_NumStandardFrequencies][D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT];`
- L573 _protected member_ `FD3D11ViewableResource* CurrentResourcesBoundAsVBs[D3D11_IA_VERTEX_INPUT_RESOURCE_SLOT_COUNT];`
- L574 _protected member_ `FD3D11ViewableResource* CurrentResourceBoundAsIB;`
- L575 _protected member_ `int32 MaxBoundShaderResourcesIndex[SF_NumStandardFrequencies];`
- L576 _protected member_ `int32 MaxBoundVertexBufferIndex;`
- L577 _protected member_ `uint32 NumSimultaneousRenderTargets;`
- L578 _protected member_ `uint32 NumUAVs;`
- L585 _protected member_ `} ActiveQueries;`
- L622 _protected member_ `} Profiler;`
- L625 _protected function_ `template <typename TEventType, typename... TArgs> TEventType& EmplaceProfilerEvent(TArgs&&... Args)`
- L630 _protected prototype_ `FD3D11RenderQuery* InsertProfilerTimestamp(uint64* Target, bool bEndFrame);`
- L632 _protected function_ `void FlushProfilerStats()`
- L652 _public prototype_ `TOptional<FTimestampCalibration> CalibrateTimers();`
- L655 _protected member_ `TOptional<FTimestampCalibration> TimestampCalibration;`
- L661 _protected member_ `FRHIUniformBuffer* BoundUniformBuffers[SF_NumStandardFrequencies][MAX_UNIFORM_BUFFERS_PER_SHADER_STAGE];` — Track the currently bound uniform buffers.
- L664 _protected member_ `uint16 DirtyUniformBuffers[SF_NumStandardFrequencies];` — Bit array to track which uniform buffers have changed since the last draw call.
- L666 _protected member_ `TArray<FRHIUniformBuffer*> StaticUniformBuffers;`
- L669 _protected member_ `FExclusiveDepthStencil CurrentDSVAccessType;` — Tracks the current depth stencil access type.
- L672 _protected member_ `bool bDiscardSharedConstants;` — When a new shader is set, we discard all old constants set for the previous shader.
- L675 _protected member_ `TRefCountPtr<FD3D11ConstantBuffer> VSConstantBuffer;` — A list of all D3D constant buffers RHIs that have been created.
- L676 _protected member_ `TRefCountPtr<FD3D11ConstantBuffer> PSConstantBuffer;`
- L677 _protected member_ `TRefCountPtr<FD3D11ConstantBuffer> GSConstantBuffer;`
- L678 _protected member_ `TRefCountPtr<FD3D11ConstantBuffer> CSConstantBuffer;`
- L681 _protected member_ `TGlobalResource< TBoundShaderStateHistory<10000> > BoundShaderStateHistory;` — A history of the most recently used bound shader states, used to keep transient bound shader states from being recreated for each use.
- L682 _protected member_ `FComputeShaderRHIRef CurrentComputeShader;`
- L684 _protected member_ `FDisplayInformationArray DisplayList;`
- L686 _protected member_ `HANDLE ExceptionHandlerHandle = INVALID_HANDLE_VALUE;`
- L688 _protected member_ `bool bRenderDoc = false;`
- L691 _public function_ `inline const FD3D11Adapter& GetAdapter() const`
- L694 _protected member_ `FD3D11Adapter Adapter;`
- L695 _protected member_ `FRHIMemoryStats MemoryStats;`
- L697 _protected prototype_ `FD3D11Texture* CreateTextureFromResource(bool bTextureArray, bool bCubeTexture, EPixelFormat Format, ETextureCreateFlags TexCreateFlags, const FClearValueBinding& ClearValueBinding, ID3D11Texture2D* TextureResource);`
- L700 _protected prototype_ `void InitConstantBuffers();` — Initializes the constant buffers.  Called once at RHI initialization time.
- L703 _protected prototype_ `virtual void CommitNonComputeShaderConstants();` — needs to be called before each draw call
- L706 _protected prototype_ `virtual void CommitComputeShaderConstants();` — needs to be called before each dispatch call
- L708 _protected prototype_ `template <class ShaderType> void SetResourcesFromTables(const ShaderType* RESTRICT);`
- L710 _protected prototype_ `void CommitGraphicsResourceTables();`
- L711 _protected prototype_ `void CommitComputeResourceTables(FD3D11ComputeShader* ComputeShader);`
- L713 _protected prototype_ `void ValidateExclusiveDepthStencilAccess(FExclusiveDepthStencil Src) const;`
- L723 _protected prototype_ `void GetBestSupportedMSAASetting( DXGI_FORMAT PlatformFormat, uint32 MSAACount, uint32& OutBestMSAACount, uint32& OutMSAAQualityLevels );` — Gets the best supported MSAA settings from the provided MSAA count to check against. @param PlatformFormat		The format of the texture being created @param MSAACount				The MSAA count to check against. @param OutBestMSAACount		The best MSAA count that is suppored.  Could be smaller than MSAACount if it is not supported @param OutMSAAQualityLevels	The number MSAA quality levels for the best msaa count supported
- L727 _protected prototype_ `void SetupAfterDeviceCreation();` — shared code for different D3D11 devices (e.g. PC DirectX11 and XboxOne) called after device creation and GRHISupportsAsyncTextureCreation was set and before resource init
- L730 _protected prototype_ `void UpdateMSAASettings();` — called by SetupAfterDeviceCreation() when the device gets initialized
- L733 _protected prototype_ `uint32 GetMaxMSAAQuality(uint32 SampleCount);` — @return 0xffffffff if not not supported
- L735 _protected prototype_ `void CommitRenderTargetsAndUAVs();`
- L736 _protected prototype_ `void CommitRenderTargets(bool bClearUAVS);`
- L737 _protected prototype_ `void CommitUAVs();`
- L743 _protected prototype_ `virtual void CleanupD3DDevice();` — Cleanup the D3D device. This function must be called from the main game thread.
- L745 _protected prototype_ `void ReleasePooledUniformBuffers();`
- L748 _protected prototype_ `template<typename TPixelShader> static void ResolveTextureUsingShader( FD3D11DynamicRHI* const This, FD3D11Texture* const SourceTexture, FD3D11Texture* const DestTexture, ID3D11RenderTargetView* const DestTextureRTV, ID3D11DepthStencilView* const DestTextureDSV, D3D11_TEXTURE2D_DESC const& ResolveTargetDesc, FResolveRect const& SourceRect, FResolveRect const& DestRect, typename TPixelShader::FParameter const PixelShaderParameter );`
- L768 _protected prototype_ `TRefCountPtr<ID3D11Texture2D> GetStagingTexture(FRHITexture* TextureRHI,FIntRect InRect, FIntRect& OutRect, FReadSurfaceDataFlags InFlags);` — Returns a pointer to a texture resource that can be used for CPU reads. Note: the returned resource could be the original texture or a new temporary texture. @param TextureRHI - Source texture to create a staging texture from. @param InRect - rectangle to 'stage'. @param StagingRectOUT - parameter is filled with the rectangle to read from the returned texture. @return The CPU readable Texture object.
- L770 _protected prototype_ `void ReadSurfaceDataNoMSAARaw(FRHITexture* TextureRHI,FIntRect Rect,TArray<uint8>& OutData, FReadSurfaceDataFlags InFlags);`
- L772 _protected prototype_ `void ReadSurfaceDataMSAARaw(FRHITexture* TextureRHI, FIntRect Rect, TArray<uint8>& OutData, FReadSurfaceDataFlags InFlags);`
- L775 _protected prototype_ `void StartIntelExtensions();`
- L776 _protected prototype_ `void StopIntelExtensions();`
- L779 _protected member_ `bool bUAVOverlapEnabled = false;`
- L780 _protected prototype_ `void EnableUAVOverlap();`
- L781 _protected prototype_ `void DisableUAVOverlap();`
- L783 _protected prototype_ `bool SetupDisplayHDRMetaData();`
- L785 _protected prototype_ `void UpdateMemoryStats();`

#### enum `FD3D11DynamicRHI::EForceFullScreenClear`  
`enum class EForceFullScreenClear`  
_L449-453_
- L451 _public enumerator_ `EDoNotForce`
- L452 _public enumerator_ `EForce`

#### struct `FD3D11DynamicRHI::(anonymous)`  
``  
_L582-585_

#### struct `FD3D11DynamicRHI::FProfiler`  
`struct FProfiler`  
_L588-622_
- L616 _public member_ `FFrame Current;`
- L617 _public member_ `TQueue<TUniquePtr<FFrame>> Pending;`
- L619 _public member_ `TArray<FD3D11RenderQuery*> TimestampPool;`
- L620 _public member_ `TArray<FD3D11RenderQuery*> TimestampPoolEndFrame;`

#### struct `FD3D11DynamicRHI::FProfiler::FFrame`  
`struct FFrame`  
_L590-614_
- L603 _public member_ `} EndFrameQuery;`
- L605 _public member_ `UE::RHI::GPUProfiler::FEventStream EventStream;`
- L608 _public member_ `FRHIBreadcrumbAllocatorArray BreadcrumbAllocators{};`
- L611 _public function_ `FFrame() : EventStream(UE::RHI::GPUProfiler::FQueue(UE::RHI::GPUProfiler::FQueue::EType::Graphics, 0, 0))`

#### struct `FD3D11DynamicRHI::FProfiler::FFrame::FEndFrameQuery`  
`struct FEndFrameQuery`  
_L592-603_
- L594 _public member_ `FD3D11RenderQuery* Ptr = nullptr;`
- L596 _public prototype_ `FEndFrameQuery() = default;`
- L597 _public function_ `FEndFrameQuery(FEndFrameQuery&& Other) : Ptr(Other.Ptr)`

#### struct `FD3D11DynamicRHI::FTimestampCalibration`  
`struct FTimestampCalibration`  
_L643-650_
- L645 _public member_ `uint64 CPUTimestamp = 0;`
- L646 _public member_ `uint64 CPUFrequency = 0;`
- L648 _public member_ `uint64 GPUTimestamp = 0;`
- L649 _public member_ `uint64 GPUFrequency = 0;`

#### enum `FD3D11DynamicRHI::(anonymous)`  
`enum`  
_L658-658_
- desc: D3D11 defines a maximum of 14 constant buffers per shader stage.

#### class `FD3D11DynamicRHIModule`  
`class FD3D11DynamicRHIModule : public IDynamicRHIModule`  
_L791-807_
- inherits: `IDynamicRHIModule`
- desc: Implements the D3D11RHI module as a dynamic RHI providing module.
- L795 _public function_ `virtual bool SupportsDynamicReloading() override` — IModuleInterface
- L798 _public prototype_ `virtual bool IsSupported() override;` — IDynamicRHIModule
- L799 _public prototype_ `virtual bool IsSupported(ERHIFeatureLevel::Type RequestedFeatureLevel) override;`
- L800 _public prototype_ `virtual FDynamicRHI* CreateRHI(ERHIFeatureLevel::Type RequestedFeatureLevel = ERHIFeatureLevel::Num) override;`
- L803 _private member_ `FD3D11Adapter ChosenAdapter;`
- L806 _private prototype_ `void FindAdapter();` — set MaxSupportedFeatureLevel and ChosenAdapter

#### class `FRangeAllocator`  
`class FRangeAllocator`  
_L812-1149_
- desc: 1d, 31 bit (uses the sign bit for internal use), O(n) where n is the amount of elements stored does not enforce any alignment unoccupied regions get compacted but occupied don't get compacted
- L871 _public function_ `FRangeAllocator(uint32 TotalSize)` — constructor
- L881 _public function_ `void OccupyRange(FRange InRange)` — specified range must be non occupied
- L940 _public function_ `FRange AllocRange(uint32 InSize)` — @param InSize >0
- L978 _public function_ `void ReleaseRange(FRange In)` — @param In needs to be what was returned by AllocRange()
- L992 _public function_ `uint32 GetNumEntries() const` — for debugging
- L995 _public function_ `uint32 ComputeUnoccupiedSize() const` — for debugging
- L1016 _private function_ `void Compacten(uint32 StartIndex)` — compact unoccupied ranges
- L1053 _public function_ `static void Test()`
- L1148 _private member_ `TArray<FRange> Entries;` — ordered from small to large (for efficient compactening)

#### struct `FRangeAllocator::FRange`  
`struct FRange`  
_L816-867_
- L819 _public function_ `FRange() : Start(0) , Size(0)` — not valid
- L826 _public function_ `void SetOccupied(int32 InStart, int32 InSize)`
- L836 _public function_ `void SetUnOccupied(int32 InStart, int32 InSize)`
- L846 _public function_ `bool IsValid()`
- L848 _public function_ `bool IsOccupied() const`
- L849 _public function_ `uint32 ComputeSize() const`
- L852 _public function_ `void ExtendUnoccupied(int32 InSize)` — @apram InSize can be <0 to remove from the size
- L854 _public function_ `void MakeOccupied(int32 InSize)`
- L855 _public function_ `void MakeUnOccupied()`
- L857 _public function_ `bool operator==(const FRange& rhs) const`
- L859 _public function_ `int32 GetStart()`
- L860 _public function_ `int32 GetEnd()`
- L864 _private member_ `int32 Start;` — in bytes
- L866 _private member_ `int32 Size;` — in bytes, 0:not valid, <0:unoccupied, >0:occupied

#### Free symbols / members of external scopes

- L23 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogD3D11RHI, Log, All);`
- L23 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogD3D11RHI, Log, All);`
- L39 _macro_ `#define WITH_DX_PERF 1`
- L44 _macro_ `#define INTC_IGDEXT_D3D11 1`
- L50 _macro_ `#define DX_MAX_MSAA_COUNT 8` — DX11 doesn't support higher MSAA count
- L53 _macro_ `#define WITH_NV_API 0`
- L57 _macro_ `#define WITH_AMD_AGS 0`
- L63 _delegate_ `DECLARE_CYCLE_STAT_EXTERN(TEXT("Present time"),STAT_D3D11PresentTime,STATGROUP_` — The D3D RHI stats.
- L63 _variable_ `DECLARE_CYCLE_STAT_EXTERN(TEXT("Present time"),STAT_D3D11PresentTime,STATGROUP_` — The D3D RHI stats.
- L64 _delegate_ `DECLARE_CYCLE_STAT_EXTERN(TEXT("CustomPresent time"), STAT_D3D11CustomPresentTime, STAT`
- L65 _delegate_ `DECLARE_CYCLE_STAT_EXTERN(TEXT("CreateTexture time"),STAT_D3D11CreateTextureTime,STAT`
- L66 _delegate_ `DECLARE_CYCLE_STAT_EXTERN(TEXT("LockTexture time"),STAT_D3D11LockTextureTime,STATGR`
- L67 _delegate_ `DECLARE_CYCLE_STAT_EXTERN(TEXT("UnlockTexture time"),STAT_D3D11UnlockTextureTime,STAT`
- L68 _delegate_ `DECLARE_CYCLE_STAT_EXTERN(TEXT("CopyTexture time"),STAT_D3D11CopyTextureTime,STATGR`
- L69 _delegate_ `DECLARE_CYCLE_STAT_EXTERN(TEXT("CreateBoundShaderState time"),STAT_D3D11CreateBoundShaderState`
- L70 _delegate_ `DECLARE_CYCLE_STAT_EXTERN(TEXT("New bound shader state time"),STAT_D3D11NewBoundShaderState`
- L71 _delegate_ `DECLARE_CYCLE_STAT_EXTERN(TEXT("Clean uniform buffer pool"),STAT_D3D11CleanUniformBufferTi`
- L72 _delegate_ `DECLARE_CYCLE_STAT_EXTERN(TEXT("Clear shader resources"),STAT_D3D11ClearShaderResourceTime,`
- L73 _delegate_ `DECLARE_DWORD_ACCUMULATOR_STAT_EXTERN(TEXT("Uniform buffer pool num free"),STAT_D3D11NumFreeUniformBu`
- L74 _delegate_ `DECLARE_DWORD_COUNTER_STAT_EXTERN(TEXT("Immutable Uniform buffers"), STAT_D3D11NumImmutableUniformBuffer`
- L75 _delegate_ `DECLARE_DWORD_ACCUMULATOR_STAT_EXTERN(TEXT("Num Bound Shader State"), STAT_D3D11NumBoundShaderState,`
- L76 _delegate_ `DECLARE_MEMORY_STAT_EXTERN(TEXT("Uniform buffer pool memory"), STAT_D3D11FreeUniformBufferMemo`
- L77 _delegate_ `DECLARE_CYCLE_STAT_EXTERN(TEXT("Update uniform buffer"),STAT_D3D11UpdateUniformBufferTime,S`
- L78 _delegate_ `DECLARE_DWORD_COUNTER_STAT_EXTERN(TEXT("Textures Allocated"),STAT_D3D11TexturesAllocated,STAT`
- L79 _delegate_ `DECLARE_DWORD_COUNTER_STAT_EXTERN(TEXT("Textures Released"),STAT_D3D11TexturesReleased,STATG`
- L80 _delegate_ `DECLARE_MEMORY_STAT_EXTERN(TEXT("Texture object pool memory"),STAT_D3D11TexturePoolMem`
- L83 _delegate_ `DECLARE_CYCLE_STAT_EXTERN(TEXT("RenderTargetCommit"), STAT_D3D11RenderTargetCommits, STAT`
- L84 _delegate_ `DECLARE_CYCLE_STAT_EXTERN(TEXT("RenderTargetCommitUAV"), STAT_D3D11RenderTargetCommitsUAV, S`
- L86 _externvar_ `extern TAutoConsoleVariable<int32> GCVarUseSharedKeyedMutex;`
- L88 _externvar_ `extern TAutoConsoleVariable<int32> GD3D11DebugCvar;`
- L583 _member_ `FD3D11RenderQuery* First = nullptr;` (scope `FD3D11DynamicRHI::__anon9061700d0108`)
- L584 _member_ `FD3D11RenderQuery* Last = nullptr;` (scope `FD3D11DynamicRHI::__anon9061700d0108`)
- L658 _enumerator_ `enum { MAX_UNIFORM_BUFFERS_PER_SHADER_STAGE = 14 }; FRHIUniformBuffer* BoundUniformBuffers[SF_NumStandardFrequencies][MAX_UNIFORM_BUFFERS_PER_SHADER_STAGE]; uint16 DirtyUniformBuffers[SF_NumStandardFrequencies];` (scope `FD3D11DynamicRHI::__anon9061700d0203`) — D3D11 defines a maximum of 14 constant buffers per shader stage.
- L1151 _externvar_ `extern FD3D11DynamicRHI* GD3D11RHI;`

### `Source/Runtime/Windows/D3D11RHI/Private/D3D11StateCache.h` (Private)


#### Free symbols / members of external scopes

- L10 _typedef_ `typedef FD3D11StateCacheBase FD3D11StateCache;`

### `Source/Runtime/Windows/D3D11RHI/Private/D3D11StateCachePrivate.h` (Private)


#### class `FD3D11StateCacheBase`  
`class FD3D11StateCacheBase`  
_L58-659_
- L61 _public member_ `bool bDepthBoundsEnabled = false;`
- L62 _public member_ `float DepthBoundsMin = 0.0f;`
- L63 _public member_ `float DepthBoundsMax = 1.0f;`
- L66 _protected member_ `ID3D11DeviceContext* Direct3DDeviceIMContext;`
- L70 _protected member_ `ID3D11ShaderResourceView* CurrentShaderResourceViews[SF_NumStandardFrequencies][D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT];` — Shader Resource Views Cache
- L73 _protected member_ `ID3D11RasterizerState* CurrentRasterizerState;` — Rasterizer State Cache
- L76 _protected member_ `uint32 CurrentReferenceStencil;` — Depth Stencil State Cache
- L77 _protected member_ `ID3D11DepthStencilState* CurrentDepthStencilState;`
- L80 _protected member_ `ID3D11VertexShader* CurrentVertexShader;` — Shader Cache
- L81 _protected member_ `ID3D11GeometryShader* CurrentGeometryShader;`
- L82 _protected member_ `ID3D11PixelShader* CurrentPixelShader;`
- L83 _protected member_ `ID3D11ComputeShader* CurrentComputeShader;`
- L86 _protected member_ `float CurrentBlendFactor[4];` — Blend State Cache
- L87 _protected member_ `uint32 CurrentBlendSampleMask;`
- L88 _protected member_ `ID3D11BlendState* CurrentBlendState;`
- L91 _protected member_ `uint32 CurrentNumberOfViewports;` — Viewport
- L92 _protected member_ `D3D11_VIEWPORT CurrentViewport[D3D11_VIEWPORT_AND_SCISSORRECT_OBJECT_COUNT_PER_PIPELINE];`
- L101 _protected member_ `} CurrentVertexBuffers[D3D11_IA_VERTEX_INPUT_RESOURCE_SLOT_COUNT];`
- L104 _protected member_ `ID3D11Buffer* CurrentIndexBuffer;` — Index Buffer State
- L105 _protected member_ `DXGI_FORMAT CurrentIndexFormat;`
- L106 _protected member_ `uint32 CurrentIndexOffset;`
- L109 _protected member_ `D3D11_PRIMITIVE_TOPOLOGY CurrentPrimitiveTopology;` — Primitive Topology State
- L112 _protected member_ `ID3D11InputLayout* CurrentInputLayout;` — Input Layout State
- L114 _protected member_ `uint16 StreamStrides[MaxVertexElementCount];`
- L117 _protected member_ `ID3D11SamplerState* CurrentSamplerStates[SF_NumStandardFrequencies][D3D11_COMMONSHADER_SAMPLER_SLOT_COUNT];` — Sampler State
- L125 _protected member_ `} CurrentConstantBuffers[SF_NumStandardFrequencies][D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT];`
- L127 _protected member_ `bool bAlwaysSetIndexBuffers;`
- L132 _protected function_ `template <EShaderFrequency ShaderFrequency> D3D11_STATE_CACHE_INLINE void InternalSetShaderResourceView(uint32 ResourceIndex, ID3D11ShaderResourceView*& SRV)`
- L146 _protected function_ `template <EShaderFrequency ShaderFrequency> D3D11_STATE_CACHE_INLINE void InternalSetSamplerState(uint32 SamplerIndex, ID3D11SamplerState*& SamplerState)`
- L159 _protected function_ `template <EShaderFrequency ShaderFrequency> D3D11_STATE_CACHE_INLINE void InternalSetSetConstantBuffer(uint32 SlotIndex, ID3D11Buffer*& ConstantBuffer)`
- L171 _protected function_ `D3D11_STATE_CACHE_INLINE void InternalSetIndexBuffer(ID3D11Buffer* IndexBuffer, DXGI_FORMAT Format, uint32 Offset)`
- L190 _protected function_ `template <EShaderFrequency ShaderFrequency> D3D11_STATE_CACHE_INLINE void InternalSetShaderResourceView(ID3D11ShaderResourceView*& SRV, uint32 ResourceIndex)`
- L214 _protected function_ `D3D11_STATE_CACHE_INLINE void InternalSetStreamSource(ID3D11Buffer* VertexBuffer, uint32 StreamIndex, uint32 Stride, uint32 Offset)`
- L234 _protected function_ `template <EShaderFrequency ShaderFrequency> D3D11_STATE_CACHE_INLINE void InternalSetSamplerState(ID3D11SamplerState* SamplerState, uint32 SamplerIndex)`
- L252 _public function_ `template <EShaderFrequency ShaderFrequency> D3D11_STATE_CACHE_INLINE void ClearConstantBuffers()`
- L269 _public function_ `template <EShaderFrequency ShaderFrequency> D3D11_STATE_CACHE_INLINE void SetShaderResourceView(ID3D11ShaderResourceView* SRV, uint32 ResourceIndex)`
- L274 _public function_ `D3D11_STATE_CACHE_INLINE void SetViewport(D3D11_VIEWPORT Viewport)`
- L290 _public function_ `D3D11_STATE_CACHE_INLINE void SetViewports(uint32 Count, D3D11_VIEWPORT* Viewports)`
- L306 _public function_ `D3D11_STATE_CACHE_INLINE void GetViewport(D3D11_VIEWPORT *Viewport)`
- L317 _public function_ `D3D11_STATE_CACHE_INLINE void GetViewports(uint32* Count, D3D11_VIEWPORT *Viewports)`
- L344 _public function_ `template <EShaderFrequency ShaderFrequency> D3D11_STATE_CACHE_INLINE void SetSamplerState(ID3D11SamplerState* SamplerState, uint32 SamplerIndex)`
- L350 _public function_ `template <EShaderFrequency ShaderFrequency> D3D11_STATE_CACHE_INLINE void SetConstantBuffer(ID3D11Buffer* ConstantBuffer, uint32 SlotIndex)`
- L368 _public function_ `D3D11_STATE_CACHE_INLINE void SetRasterizerState(ID3D11RasterizerState* State)`
- L383 _public function_ `D3D11_STATE_CACHE_INLINE void SetBlendState(ID3D11BlendState* State, const float BlendFactor[4], uint32 SampleMask)`
- L400 _public function_ `D3D11_STATE_CACHE_INLINE void SetBlendFactor(const float BlendFactor[4], uint32 SampleMask)`
- L416 _public function_ `D3D11_STATE_CACHE_INLINE void SetDepthStencilState(ID3D11DepthStencilState* State, uint32 RefStencil)`
- L432 _public function_ `D3D11_STATE_CACHE_INLINE void SetStencilRef(uint32 RefStencil)`
- L447 _public function_ `D3D11_STATE_CACHE_INLINE void SetVertexShader(ID3D11VertexShader* Shader)`
- L462 _public function_ `D3D11_STATE_CACHE_INLINE void GetVertexShader(ID3D11VertexShader** VertexShader)`
- L475 _public function_ `D3D11_STATE_CACHE_INLINE void SetGeometryShader(ID3D11GeometryShader* Shader)`
- L490 _public function_ `D3D11_STATE_CACHE_INLINE void GetGeometryShader(ID3D11GeometryShader** GeometryShader)`
- L503 _public function_ `D3D11_STATE_CACHE_INLINE void SetPixelShader(ID3D11PixelShader* Shader)`
- L518 _public function_ `D3D11_STATE_CACHE_INLINE void GetPixelShader(ID3D11PixelShader** PixelShader)`
- L531 _public function_ `D3D11_STATE_CACHE_INLINE void SetComputeShader(ID3D11ComputeShader* Shader)`
- L546 _public function_ `D3D11_STATE_CACHE_INLINE void GetComputeShader(ID3D11ComputeShader** ComputeShader)`
- L559 _public function_ `D3D11_STATE_CACHE_INLINE void SetStreamStrides(const uint16* InStreamStrides)`
- L564 _public function_ `D3D11_STATE_CACHE_INLINE void SetInputLayout(ID3D11InputLayout* InputLayout)`
- L579 _public function_ `D3D11_STATE_CACHE_INLINE void SetStreamSource(ID3D11Buffer* VertexBuffer, uint32 StreamIndex, uint32 Stride, uint32 Offset)`
- L585 _public function_ `D3D11_STATE_CACHE_INLINE void SetStreamSource(ID3D11Buffer* VertexBuffer, uint32 StreamIndex, uint32 Offset)`
- L592 _public function_ `D3D11_STATE_CACHE_INLINE void SetIndexBuffer(ID3D11Buffer* IndexBuffer, DXGI_FORMAT Format, uint32 Offset)`
- L597 _public function_ `D3D11_STATE_CACHE_INLINE void SetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY PrimitiveTopology)`
- L612 _public function_ `FD3D11StateCacheBase() : Direct3DDeviceIMContext(nullptr)`
- L618 _public function_ `void Init(ID3D11DeviceContext* InDeviceContext, bool bInAlwaysSetIndexBuffers = false )`
- L627 _public prototype_ `virtual ~FD3D11StateCacheBase() = default;`
- L629 _public function_ `virtual D3D11_STATE_CACHE_INLINE void SetContext(ID3D11DeviceContext* InDeviceContext)`
- L641 _public prototype_ `virtual void ClearState();` — Clears all D3D11 State, setting all input/output resource slots, shaders, input layouts, predications, scissor rectangles, depth-stencil state, rasterizer state, blend state, sampler state, and viewports to NULL
- L647 _protected prototype_ `template <EShaderFrequency ShaderFrequency> void VerifySamplerStates();` — Debug helper methods to verify cached state integrity.
- L650 _protected prototype_ `template <EShaderFrequency ShaderFrequency> void VerifyConstantBuffers();`
- L653 _protected prototype_ `template <EShaderFrequency ShaderFrequency> void VerifyShaderResourceViews();`
- L655 _protected prototype_ `void VerifyCacheStatePre();`
- L656 _protected prototype_ `void VerifyCacheStatePost();`
- L657 _protected prototype_ `void VerifyCacheState();`

#### struct `FD3D11StateCacheBase::FD3D11VertexBufferState`  
`struct FD3D11VertexBufferState`  
_L96-101_
- desc: Vertex Buffer State
- L98 _public member_ `ID3D11Buffer* VertexBuffer;`
- L99 _public member_ `uint32 Stride;`
- L100 _public member_ `uint32 Offset;`

#### struct `FD3D11StateCacheBase::FD3D11ConstantBufferState`  
`struct FD3D11ConstantBufferState`  
_L120-125_
- desc: Constant Buffer State
- L122 _public member_ `ID3D11Buffer* Buffer;`
- L123 _public member_ `uint32 FirstConstant;`
- L124 _public member_ `uint32 NumConstants;`

#### Free symbols / members of external scopes

- L16 _macro_ `#define D3D11_ALLOW_STATE_CACHE 1` — If set, enables the D3D11 state caching system.
- L20 _macro_ `#define D3D11_STATE_CACHE_RUNTIME_TOGGLE 0` — If set, includes a runtime toggle console command for debugging D3D11 state caching. ("TOGGLESTATECACHE")
- L26 _macro_ `#define D3D11_STATE_CACHE_DEBUG 0`
- L34 _macro_ `#define D3D11_STATE_CACHE_INLINE FORCEINLINE` — Keep set state functions inline to reduce call overhead
- L40 _macro_ `#define D3D11_STATE_CACHE_VERIFY(...) VerifyCacheState()`
- L41 _macro_ `#define D3D11_STATE_CACHE_VERIFY_PRE(...) VerifyCacheStatePre()`
- L42 _macro_ `#define D3D11_STATE_CACHE_VERIFY_POST(...) VerifyCacheStatePost()`
- L44 _macro_ `#define D3D11_STATE_CACHE_VERIFY(...)`
- L45 _macro_ `#define D3D11_STATE_CACHE_VERIFY_PRE(...)`
- L46 _macro_ `#define D3D11_STATE_CACHE_VERIFY_POST(...)`
- L50 _externvar_ `extern bool GD3D11SkipStateCaching;`
- L52 _variable_ `static const bool GD3D11SkipStateCaching = false;`

### `Source/Runtime/Windows/D3D11RHI/Private/Windows/D3D11RHIPrivateUtil.h` (Private)
_(no declarations extracted)_

### `Source/Runtime/Windows/D3D11RHI/Private/Windows/WindowsD3D11ConstantBuffer.h` (Private)


#### class `FWinD3D11ConstantBuffer`  
`class FWinD3D11ConstantBuffer : public FD3D11ConstantBuffer`  
_L12-48_
- inherits: `FD3D11ConstantBuffer`
- L15 _public function_ `FWinD3D11ConstantBuffer(FD3D11DynamicRHI* InD3DRHI) : FD3D11ConstantBuffer(InD3DRHI)`
- L21 _public prototype_ `virtual void InitRHI(FRHICommandListBase& RHICmdList) override;` — FRenderResource interface.
- L22 _public prototype_ `virtual void ReleaseRHI() override;`
- L27 _public function_ `ID3D11Buffer* GetConstantBuffer() const` — Get the current pool buffer
- L32 _public prototype_ `uint32 FindSubBufferForAllocationSize(uint64 InSize) const;`
- L37 _public prototype_ `bool CommitConstantsToDevice(bool bDiscardSharedConstants);` — Unlocks the constant buffer so the data can be transmitted to the device
- L46 _private member_ `TArray<FSubBuffer> SubBuffers;`
- L47 _private member_ `uint32 CurrentSubBuffer = 0;`

#### struct `FWinD3D11ConstantBuffer::FSubBuffer`  
`struct FSubBuffer`  
_L40-45_
- L42 _public function_ `FSubBuffer(uint64 InSize) : Size(InSize)`
- L43 _public member_ `TRefCountPtr<ID3D11Buffer> Buffer;`
- L44 _public member_ `uint64 Size;`

### `Source/Runtime/Windows/D3D11RHI/Public/D3D11ConstantBuffer.h` (Public)


#### enum `ED3D11ShaderOffsetBuffer`  
`enum ED3D11ShaderOffsetBuffer`  
_L22-27_
- desc: !!! These offsets must match the cbuffer register definitions in Common.usf !!!
- L25 _public enumerator_ `GLOBAL_CONSTANT_BUFFER_INDEX = 0` — Default constant buffer.
- L26 _public enumerator_ `MAX_CONSTANT_BUFFER_SLOTS`

#### class `FD3D11ConstantBuffer`  
`class FD3D11ConstantBuffer : public FRenderResource, public FRefCountedObject`  
_L32-65_
- inherits: `FRenderResource,FRefCountedObject`
- desc: A D3D constant buffer
- L36 _public prototype_ `FD3D11ConstantBuffer(FD3D11DynamicRHI* InD3DRHI);` — New circular buffer system for faster constant uploads.  Avoids CopyResource and speeds things up considerably
- L37 _public prototype_ `virtual ~FD3D11ConstantBuffer();`
- L40 _public prototype_ `virtual void InitRHI(FRHICommandListBase& RHICmdList) override;` — FRenderResource interface.
- L41 _public prototype_ `virtual void ReleaseRHI() override;`
- L43 _public function_ `static inline constexpr uint32 GetMaxSize()`
- L51 _public function_ `void UpdateConstant(const uint8* Data, uint16 Offset, uint16 InSize)` — Updates a variable in the constant buffer. @param Data - The data to copy into the constant buffer @param Offset - The offset in the constant buffer to place the data at @param InSize - The size of the data being copied
- L60 _protected member_ `FD3D11DynamicRHI* D3DRHI;`
- L61 _protected member_ `uint8* ShadowData = nullptr;`
- L64 _protected member_ `uint32 CurrentUpdateSize = 0;` — Size of all constants that has been updated since the last call to Commit.

#### Free symbols / members of external scopes

- L18 _macro_ `#define MAX_GLOBAL_CONSTANT_BUFFER_BYTE_SIZE (16*4096)` — Size of the default constant buffer. Note: D3D11 allows for 64k of storage but increasing this has a negative impact on performance.
- L19 _macro_ `#define MIN_GLOBAL_CONSTANT_BUFFER_BYTE_SIZE 128`
- L67 _delegate_ `DECLARE_CYCLE_STAT_EXTERN(TEXT("Global Constant buffer update time"),STAT_D3D11GlobalConstantBuffe`

### `Source/Runtime/Windows/D3D11RHI/Public/D3D11RHI.h` (Public)
_(no declarations extracted)_

### `Source/Runtime/Windows/D3D11RHI/Public/D3D11Resources.h` (Public)


#### struct `TTypeTraits`  
`template <> struct TTypeTraits<D3D11_INPUT_ELEMENT_DESC> : public TTypeTraitsBase<D3D11_INPUT_ELEMENT_DESC>`  
_L17-20_
- inherits: `TTypeTraitsBase<D3D11_INPUT_ELEMENT_DESC>`

#### enum `TTypeTraits::(anonymous)`  
`enum`  
_L19-19_

#### class `FD3D11VertexDeclaration`  
`class FD3D11VertexDeclaration : public FRHIVertexDeclaration`  
_L26-40_
- inherits: `FRHIVertexDeclaration`
- desc: This represents a vertex declaration that hasn't been combined with a specific shader to create a bound shader.
- L30 _public member_ `FD3D11VertexElements VertexElements;` — Elements of the vertex declaration.
- L32 _public member_ `uint16 StreamStrides[MaxVertexElementCount];`
- L35 _public function_ `explicit FD3D11VertexDeclaration(const FD3D11VertexElements& InElements, const uint16* InStrides) : VertexElements(InElements)` — Initialization constructor.

#### struct `FD3D11ShaderData`  
`struct FD3D11ShaderData`  
_L42-48_
- L44 _public member_ `TArray<FShaderCodeVendorExtension> VendorExtensions;`
- L45 _public member_ `bool bShaderNeedsGlobalConstantBuffer;`
- L46 _public member_ `bool bIsSm6Shader;`
- L47 _public member_ `uint16 UAVMask;`

#### class `FD3D11VertexShader`  
`class FD3D11VertexShader : public FRHIVertexShader, public FD3D11ShaderData`  
_L51-64_
- inherits: `FRHIVertexShader,FD3D11ShaderData`
- desc: This represents a vertex shader that hasn't been combined with a specific declaration to create a bound shader.
- L57 _public member_ `TRefCountPtr<ID3D11VertexShader> Resource;` — The vertex shader resource.
- L60 _public member_ `TArray<uint8> Code;` — The vertex shader's bytecode, with custom data attached.
- L63 _public member_ `int32 Offset;` — TEMP remove with removal of bound shader state

#### enum `FD3D11VertexShader::(anonymous)`  
`enum`  
_L54-54_

#### class `FD3D11GeometryShader`  
`class FD3D11GeometryShader : public FRHIGeometryShader, public FD3D11ShaderData`  
_L66-73_
- inherits: `FRHIGeometryShader,FD3D11ShaderData`
- L72 _public member_ `TRefCountPtr<ID3D11GeometryShader> Resource;` — The shader resource.

#### enum `FD3D11GeometryShader::(anonymous)`  
`enum`  
_L69-69_

#### class `FD3D11PixelShader`  
`class FD3D11PixelShader : public FRHIPixelShader, public FD3D11ShaderData`  
_L75-82_
- inherits: `FRHIPixelShader,FD3D11ShaderData`
- L81 _public member_ `TRefCountPtr<ID3D11PixelShader> Resource;` — The shader resource.

#### enum `FD3D11PixelShader::(anonymous)`  
`enum`  
_L78-78_

#### class `FD3D11ComputeShader`  
`class FD3D11ComputeShader : public FRHIComputeShader, public FD3D11ShaderData`  
_L84-91_
- inherits: `FRHIComputeShader,FD3D11ShaderData`
- L90 _public member_ `TRefCountPtr<ID3D11ComputeShader> Resource;` — The shader resource.

#### enum `FD3D11ComputeShader::(anonymous)`  
`enum`  
_L87-87_

#### class `FD3D11BoundShaderState`  
`class FD3D11BoundShaderState : public FRHIBoundShaderState`  
_L97-128_
- inherits: `FRHIBoundShaderState`
- desc: Combined shader state and vertex definition for rendering geometry. Each unique instance consists of a vertex decl, vertex shader, and pixel shader.
- L101 _public member_ `FCachedBoundShaderStateLink CacheLink;`
- L102 _public member_ `uint16 StreamStrides[MaxVertexElementCount];`
- L103 _public member_ `TRefCountPtr<ID3D11InputLayout> InputLayout;`
- L104 _public member_ `TRefCountPtr<ID3D11VertexShader> VertexShader;`
- L105 _public member_ `TRefCountPtr<ID3D11PixelShader> PixelShader;`
- L106 _public member_ `TRefCountPtr<ID3D11GeometryShader> GeometryShader;`
- L108 _public member_ `bool bShaderNeedsGlobalConstantBuffer[SF_NumStandardFrequencies];`
- L112 _public prototype_ `FD3D11BoundShaderState( FRHIVertexDeclaration* InVertexDeclarationRHI, FRHIVertexShader* InVertexShaderRHI, FRHIPixelShader* InPixelShaderRHI, FRHIGeometryShader* InGeometryShaderRHI, ID3D11Device* Direct3DDevice );` — Initialization constructor.
- L120 _public prototype_ `~FD3D11BoundShaderState();`
- L125 _public function_ `inline FD3D11VertexShader* GetVertexShader() const` — Get the shader for the given frequency.
- L126 _public function_ `inline FD3D11PixelShader* GetPixelShader() const`
- L127 _public function_ `inline FD3D11GeometryShader* GetGeometryShader() const`

#### class `FD3D11ViewableResource`  
`class FD3D11ViewableResource`  
_L131-150_
- desc: The base class of resources that may be bound as shader resources.
- L134 _public function_ `~FD3D11ViewableResource()`
- L139 _public function_ `bool HasLinkedViews() const`
- L144 _public prototype_ `void UpdateLinkedViews();`
- L149 _private member_ `class FD3D11View* LinkedViews = nullptr;`

#### class `FD3D11Texture`  
`class FD3D11Texture final : public FRHITexture, public FD3D11ViewableResource`  
_L153-320_
- inherits: `FRHITexture,FD3D11ViewableResource`
- desc: Texture base class.
- L156 _public prototype_ `FD3D11Texture(const FRHITextureCreateDesc& InDesc);`
- L157 _public prototype_ `void FinalizeCreation( ID3D11Resource* InResource, ID3D11ShaderResourceView* InShaderResourceView, int32 InRTVArraySize, bool bInCreatedRTVsPerSlice, TConstArrayView<TRefCountPtr<ID3D11RenderTargetView>> InRenderTargetViews, TConstArrayView<TRefCountPtr<ID3D11DepthStencilView>> InDepthStencilViews );`
- L166 _public function_ `FD3D11Texture( const FRHITextureCreateDesc& InDesc, ID3D11Resource* InResource, ID3D11ShaderResourceView* InShaderResourceView, int32 InRTVArraySize, bool bInCreatedRTVsPerSlice, TConstArrayView<TRefCountPtr<ID3D11RenderTargetView>> InRenderTargetViews, TConstArrayView<TRefCountPtr<ID3D11DepthStencilView>> InDepthStencilViews) : FD3D11Texture(InDesc)`
- L180 _public prototype_ `explicit FD3D11Texture(FD3D11Texture const& Other, const FString& Name, EAliasResourceParam);`
- L181 _public prototype_ `void AliasResource(FD3D11Texture const& Other);`
- L183 _public prototype_ `virtual ~FD3D11Texture();`
- L185 _public function_ `inline uint64 GetMemorySize() const`
- L191 _public function_ `inline ID3D11Resource* GetResource() const` — Accessors.
- L192 _public function_ `inline ID3D11ShaderResourceView* GetShaderResourceView() const`
- L194 _public function_ `inline bool IsCubemap() const`
- L200 _public function_ `inline ID3D11Texture2D* GetD3D11Texture2D() const`
- L211 _public function_ `inline ID3D11Texture3D* GetD3D11Texture3D() const`
- L219 _public function_ `inline bool IsTexture3D() const`
- L224 _public function_ `virtual inline void* GetNativeResource() const override`
- L229 _public function_ `virtual inline void* GetNativeShaderResourceView() const override`
- L234 _public function_ `virtual inline void* GetTextureBaseRHI() override`
- L239 _public function_ `inline void SetIHVResourceHandle(void* InHandle)`
- L244 _public function_ `inline void* GetIHVResourceHandle() const`
- L253 _public function_ `inline ID3D11RenderTargetView* GetRenderTargetView(int32 MipIndex, int32 ArraySliceIndex) const` — Get the render target view for the specified mip and array slice. An array slice of -1 is used to indicate that no array slice should be required.
- L275 _public function_ `inline ID3D11DepthStencilView* GetDepthStencilView(FExclusiveDepthStencil AccessType) const`
- L281 _public function_ `virtual bool GetResourceInfo(FRHIResourceInfo& OutResourceInfo) const override`
- L295 _public prototype_ `FRHILockTextureResult Lock(FD3D11DynamicRHI* D3DRHI, const FRHILockTextureArgs& Arguments, bool bForceLockDeferred);` — Locks one of the texture's mip-maps. @return A pointer to the specified texture data.
- L298 _public prototype_ `void Unlock(FD3D11DynamicRHI* D3DRHI, const FRHILockTextureArgs& Arguments);` — Unlocks a previously locked mip-map.
- L302 _private member_ `void* IHVResourceHandle = nullptr;` — Resource handle for use by IHVs for SLI and other purposes.
- L305 _private member_ `TRefCountPtr<ID3D11Resource> Resource;` — The texture resource.
- L308 _private member_ `TRefCountPtr<ID3D11ShaderResourceView> ShaderResourceView;` — A shader resource view of the texture.
- L311 _private member_ `TArray<TRefCountPtr<ID3D11RenderTargetView> > RenderTargetViews;` — A render targetable view of the texture.
- L314 _private member_ `TRefCountPtr<ID3D11DepthStencilView> DepthStencilViews[FExclusiveDepthStencil::MaxIndex];` — A depth-stencil targetable view of the texture.
- L316 _private member_ `int32 RTVArraySize = 0;`
- L318 _private member_ `uint8 bCreatedRTVsPerSlice : 1;`
- L319 _private member_ `uint8 bAlias : 1;`

#### enum `FD3D11Texture::EAliasResourceParam`  
`enum EAliasResourceParam`  
_L179-179_
- L179 _public enumerator_ `enum EAliasResourceParam { CreateAlias }; D3D11RHI_API explicit FD3D11Texture(FD3D11Texture const& Other, const FString& Name, EAliasResourceParam); D3D11RHI_API void AliasResource(FD3D11Texture const& Other); D3D11RHI_API virtual ~FD3D11Texture(); inline uint64 GetMemorySize() const {`

#### class `FD3D11RenderQuery`  
`class FD3D11RenderQuery`  
_L322-360_
- L325 _private member_ `TRefCountPtr<ID3D11Query> Resource;`
- L328 _private member_ `uint64* Target = nullptr;` — Location the result is written to.
- L331 _private member_ `FD3D11RenderQuery** Prev = nullptr;` — Linked list pointers. Used to build a list of "active" queries, i.e. queries that need data to be polled from the GPU.
- L332 _private member_ `FD3D11RenderQuery* Next = nullptr;`
- L335 _public member_ `uint8 TOPCounter = 0;`
- L336 _public member_ `uint8 BOPCounter = 0;`
- L337 _public member_ `std::atomic<uint8> LastCachedBOPCounter = 0;`
- L345 _public member_ `} const Type;`
- L347 _public prototype_ `FD3D11RenderQuery(EType Type);`
- L348 _public prototype_ `~FD3D11RenderQuery();`
- L350 _public prototype_ `bool CacheResult(class FD3D11DynamicRHI& RHI, bool bWait);`
- L352 _public prototype_ `void Begin(ID3D11DeviceContext* Context);`
- L353 _public prototype_ `void End(ID3D11DeviceContext* Context, uint64* Target);`
- L355 _public function_ `bool IsLinked() const`
- L358 _private prototype_ `void Link();`
- L359 _private prototype_ `void Unlink();`

#### enum `FD3D11RenderQuery::EType`  
`enum class EType : uint8`  
_L339-345_
- L341 _public enumerator_ `Timestamp`
- L342 _public enumerator_ `Occlusion`
- L343 _public enumerator_ `Profiler`
- L344 _public enumerator_ `ProfilerEndFrame`

#### class `FD3D11RenderQuery_RHI`  
`class FD3D11RenderQuery_RHI : public FRHIRenderQuery, public FD3D11RenderQuery`  
_L363-371_
- inherits: `FRHIRenderQuery,FD3D11RenderQuery`
- desc: D3D11 render query
- L366 _public member_ `uint64 Result = 0;`
- L368 _public function_ `FD3D11RenderQuery_RHI(EType Type) : FD3D11RenderQuery(Type)`

#### struct `FRingAllocation`  
`struct FRingAllocation`  
_L377-386_
- desc: A ring allocation from the constants ring buffer.
- L379 _public member_ `ID3D11Buffer* Buffer;`
- L380 _public member_ `void* DataPtr;`
- L381 _public member_ `uint32 Offset;`
- L382 _public member_ `uint32 Size;`
- L384 _public function_ `FRingAllocation() : Buffer(NULL)`
- L385 _public function_ `inline bool IsValid() const`

#### class `FD3D11UniformBuffer`  
`class FD3D11UniformBuffer : public FRHIUniformBuffer`  
_L389-417_
- inherits: `FRHIUniformBuffer`
- desc: Uniform buffer resource class.
- L394 _public member_ `TRefCountPtr<ID3D11Buffer> Resource;` — The D3D11 constant buffer resource
- L397 _public member_ `FRingAllocation RingAllocation;` — Allocation in the constants ring buffer if applicable.
- L400 _public function_ `FD3D11UniformBuffer(class FD3D11DynamicRHI* InD3D11RHI, const FRHIUniformBufferLayout* InLayout, ID3D11Buffer* InResource,const FRingAllocation& InRingAllocation, bool bInAllocatedFromPool) : FRHIUniformBuffer(InLayout) , Resource(InResource) , RingAllocation(InRingAllocation) , D3D11RHI(InD3D11RHI) , bAllocatedFromPool(bInAllocatedFromPool)` — Initialization constructor.
- L408 _public prototype_ `virtual ~FD3D11UniformBuffer();`
- L412 _public function_ `TArray<TRefCountPtr<FRHIResource>>& GetResourceTable()` — Provides public non-const access to ResourceTable. @todo refactor uniform buffers to perform updates as a member function, so this isn't necessary.
- L415 _private member_ `class FD3D11DynamicRHI* D3D11RHI;`
- L416 _private member_ `bool bAllocatedFromPool;`

#### class `FD3D11Buffer`  
`class FD3D11Buffer : public FRHIBuffer, public FD3D11ViewableResource`  
_L420-452_
- inherits: `FRHIBuffer,FD3D11ViewableResource`
- desc: Buffer resource class.
- L424 _public member_ `TRefCountPtr<ID3D11Buffer> Resource;`
- L426 _public function_ `FD3D11Buffer(ID3D11Buffer* InResource, const FRHIBufferCreateDesc& InCreateDesc) : FRHIBuffer(InCreateDesc) , Resource(InResource)`
- L433 _public function_ `bool GetResourceInfo(FRHIResourceInfo& OutResourceInfo) const override`
- L443 _public prototype_ `virtual ~FD3D11Buffer();`
- L445 _public prototype_ `void TakeOwnership(FD3D11Buffer& Other);`
- L446 _public prototype_ `void ReleaseOwnership();`
- L448 _public function_ `ID3D11Resource* GetResource() const`

#### class `FD3D11StagingBuffer`  
`class FD3D11StagingBuffer final : public FRHIStagingBuffer`  
_L454-472_
- inherits: `FRHIStagingBuffer`
- L458 _public function_ `FD3D11StagingBuffer() : FRHIStagingBuffer()`
- L464 _public prototype_ `void* Lock(uint32 Offset, uint32 NumBytes) override;`
- L465 _public prototype_ `void Unlock() override;`
- L466 _public function_ `uint64 GetGPUSizeBytes() const override`
- L469 _private member_ `FD3D11DeviceContext* Context;`
- L470 _private member_ `TRefCountPtr<ID3D11Buffer> StagedRead;`
- L471 _private member_ `uint32 ShadowBufferSize;`

#### class `FD3D11Sync`  
`class FD3D11Sync`  
_L474-500_
- L477 _private member_ `FGraphEventRef Event;` — The graph event to trigger when the sync is resolved.
- L480 _private member_ `TRefCountPtr<ID3D11Query> Query;` — The D3D11 API query object to poll / wait on.
- L482 _private prototype_ `FD3D11Sync() = default;`
- L483 _private function_ `FD3D11Sync(FGraphEventRef&& Event, TRefCountPtr<ID3D11Query>&& Query) : Event(MoveTemp(Event)) , Query(MoveTemp(Query))`
- L489 _private member_ `static TSpscQueue<FD3D11Sync> ActiveSyncs;`
- L492 _public prototype_ `static void EnqueueSync(FGraphEventRef Event);`
- L494 _public prototype_ `static void PollSyncsUntil(FGraphEvent* Target);`
- L496 _public function_ `static void PollSyncs()`

#### class `FD3D11GPUFence`  
`class FD3D11GPUFence final : public FRHIGPUFence`  
_L502-515_
- inherits: `FRHIGPUFence`
- L505 _private member_ `FGraphEventRef Event;`
- L508 _public prototype_ `FD3D11GPUFence(FName InName);`
- L510 _public prototype_ `void Clear() override;`
- L511 _public prototype_ `bool Poll() const override;`
- L512 _public prototype_ `void Wait(FRHICommandListImmediate& RHICmdList, FRHIGPUMask GPUMask) const override;`
- L514 _public prototype_ `void WriteGPUFence_TopOfPipe(FRHICommandListBase& RHICmdList);`

#### class `FD3D11View`  
`class FD3D11View : public TIntrusiveLinkedList<FD3D11View>`  
_L523-532_
- inherits: `TIntrusiveLinkedList<FD3D11View>`
- L526 _public function_ `virtual ~FD3D11View()`
- L531 _public prototype_ `virtual void UpdateView() = 0;`

#### class `FD3D11ShaderResourceView`  
`class FD3D11ShaderResourceView final : public FRHIShaderResourceView, public FD3D11View`  
_L535-544_
- inherits: `FRHIShaderResourceView,FD3D11View`
- desc: Shader resource view class.
- L538 _public member_ `TRefCountPtr<ID3D11ShaderResourceView> View;`
- L540 _public prototype_ `FD3D11ShaderResourceView(FRHICommandListBase& RHICmdList, FRHIViewableResource* Resource, FRHIViewDesc const& ViewDesc);`
- L541 _public prototype_ `FD3D11ViewableResource* GetBaseResource() const;`
- L543 _public prototype_ `virtual void UpdateView() override;`

#### class `FD3D11UnorderedAccessView`  
`class FD3D11UnorderedAccessView final : public FRHIUnorderedAccessView, public FD3D11View`  
_L547-556_
- inherits: `FRHIUnorderedAccessView,FD3D11View`
- desc: Unordered access view class.
- L550 _public member_ `TRefCountPtr<ID3D11UnorderedAccessView> View;`
- L552 _public prototype_ `FD3D11UnorderedAccessView(FRHICommandListBase& RHICmdList, FRHIViewableResource* Resource, FRHIViewDesc const& ViewDesc);`
- L553 _public prototype_ `FD3D11ViewableResource* GetBaseResource() const;`
- L555 _public prototype_ `virtual void UpdateView() override;`

#### struct `TD3D11ResourceTraits`  
`template<class T> struct TD3D11ResourceTraits`  
_L559-561_
- L565 _public typedef_ `typedef FD3D11VertexDeclaration TConcreteType;`
- L570 _public typedef_ `typedef FD3D11VertexShader TConcreteType;`
- L575 _public typedef_ `typedef FD3D11GeometryShader TConcreteType;`
- L580 _public typedef_ `typedef FD3D11PixelShader TConcreteType;`
- L585 _public typedef_ `typedef FD3D11ComputeShader TConcreteType;`
- L590 _public typedef_ `typedef FD3D11BoundShaderState TConcreteType;`
- L595 _public typedef_ `typedef FD3D11RenderQuery_RHI TConcreteType;`
- L600 _public typedef_ `typedef FD3D11UniformBuffer TConcreteType;`
- L605 _public typedef_ `typedef FD3D11Buffer TConcreteType;`
- L610 _public typedef_ `typedef FD3D11StagingBuffer TConcreteType;`
- L616 _public typedef_ `typedef FD3D11GPUFence TConcreteType;`
- L621 _public typedef_ `typedef FD3D11ShaderResourceView TConcreteType;`
- L626 _public typedef_ `typedef FD3D11UnorderedAccessView TConcreteType;`

#### struct `TD3D11ResourceTraits`  
`template<> struct TD3D11ResourceTraits<FRHIVertexDeclaration>`  
_L563-566_
- L565 _public typedef_ `typedef FD3D11VertexDeclaration TConcreteType;`
- L570 _public typedef_ `typedef FD3D11VertexShader TConcreteType;`
- L575 _public typedef_ `typedef FD3D11GeometryShader TConcreteType;`
- L580 _public typedef_ `typedef FD3D11PixelShader TConcreteType;`
- L585 _public typedef_ `typedef FD3D11ComputeShader TConcreteType;`
- L590 _public typedef_ `typedef FD3D11BoundShaderState TConcreteType;`
- L595 _public typedef_ `typedef FD3D11RenderQuery_RHI TConcreteType;`
- L600 _public typedef_ `typedef FD3D11UniformBuffer TConcreteType;`
- L605 _public typedef_ `typedef FD3D11Buffer TConcreteType;`
- L610 _public typedef_ `typedef FD3D11StagingBuffer TConcreteType;`
- L616 _public typedef_ `typedef FD3D11GPUFence TConcreteType;`
- L621 _public typedef_ `typedef FD3D11ShaderResourceView TConcreteType;`
- L626 _public typedef_ `typedef FD3D11UnorderedAccessView TConcreteType;`

#### struct `TD3D11ResourceTraits`  
`template<> struct TD3D11ResourceTraits<FRHIVertexShader>`  
_L568-571_
- L565 _public typedef_ `typedef FD3D11VertexDeclaration TConcreteType;`
- L570 _public typedef_ `typedef FD3D11VertexShader TConcreteType;`
- L575 _public typedef_ `typedef FD3D11GeometryShader TConcreteType;`
- L580 _public typedef_ `typedef FD3D11PixelShader TConcreteType;`
- L585 _public typedef_ `typedef FD3D11ComputeShader TConcreteType;`
- L590 _public typedef_ `typedef FD3D11BoundShaderState TConcreteType;`
- L595 _public typedef_ `typedef FD3D11RenderQuery_RHI TConcreteType;`
- L600 _public typedef_ `typedef FD3D11UniformBuffer TConcreteType;`
- L605 _public typedef_ `typedef FD3D11Buffer TConcreteType;`
- L610 _public typedef_ `typedef FD3D11StagingBuffer TConcreteType;`
- L616 _public typedef_ `typedef FD3D11GPUFence TConcreteType;`
- L621 _public typedef_ `typedef FD3D11ShaderResourceView TConcreteType;`
- L626 _public typedef_ `typedef FD3D11UnorderedAccessView TConcreteType;`

#### struct `TD3D11ResourceTraits`  
`template<> struct TD3D11ResourceTraits<FRHIGeometryShader>`  
_L573-576_
- L565 _public typedef_ `typedef FD3D11VertexDeclaration TConcreteType;`
- L570 _public typedef_ `typedef FD3D11VertexShader TConcreteType;`
- L575 _public typedef_ `typedef FD3D11GeometryShader TConcreteType;`
- L580 _public typedef_ `typedef FD3D11PixelShader TConcreteType;`
- L585 _public typedef_ `typedef FD3D11ComputeShader TConcreteType;`
- L590 _public typedef_ `typedef FD3D11BoundShaderState TConcreteType;`
- L595 _public typedef_ `typedef FD3D11RenderQuery_RHI TConcreteType;`
- L600 _public typedef_ `typedef FD3D11UniformBuffer TConcreteType;`
- L605 _public typedef_ `typedef FD3D11Buffer TConcreteType;`
- L610 _public typedef_ `typedef FD3D11StagingBuffer TConcreteType;`
- L616 _public typedef_ `typedef FD3D11GPUFence TConcreteType;`
- L621 _public typedef_ `typedef FD3D11ShaderResourceView TConcreteType;`
- L626 _public typedef_ `typedef FD3D11UnorderedAccessView TConcreteType;`

#### struct `TD3D11ResourceTraits`  
`template<> struct TD3D11ResourceTraits<FRHIPixelShader>`  
_L578-581_
- L565 _public typedef_ `typedef FD3D11VertexDeclaration TConcreteType;`
- L570 _public typedef_ `typedef FD3D11VertexShader TConcreteType;`
- L575 _public typedef_ `typedef FD3D11GeometryShader TConcreteType;`
- L580 _public typedef_ `typedef FD3D11PixelShader TConcreteType;`
- L585 _public typedef_ `typedef FD3D11ComputeShader TConcreteType;`
- L590 _public typedef_ `typedef FD3D11BoundShaderState TConcreteType;`
- L595 _public typedef_ `typedef FD3D11RenderQuery_RHI TConcreteType;`
- L600 _public typedef_ `typedef FD3D11UniformBuffer TConcreteType;`
- L605 _public typedef_ `typedef FD3D11Buffer TConcreteType;`
- L610 _public typedef_ `typedef FD3D11StagingBuffer TConcreteType;`
- L616 _public typedef_ `typedef FD3D11GPUFence TConcreteType;`
- L621 _public typedef_ `typedef FD3D11ShaderResourceView TConcreteType;`
- L626 _public typedef_ `typedef FD3D11UnorderedAccessView TConcreteType;`

#### struct `TD3D11ResourceTraits`  
`template<> struct TD3D11ResourceTraits<FRHIComputeShader>`  
_L583-586_
- L565 _public typedef_ `typedef FD3D11VertexDeclaration TConcreteType;`
- L570 _public typedef_ `typedef FD3D11VertexShader TConcreteType;`
- L575 _public typedef_ `typedef FD3D11GeometryShader TConcreteType;`
- L580 _public typedef_ `typedef FD3D11PixelShader TConcreteType;`
- L585 _public typedef_ `typedef FD3D11ComputeShader TConcreteType;`
- L590 _public typedef_ `typedef FD3D11BoundShaderState TConcreteType;`
- L595 _public typedef_ `typedef FD3D11RenderQuery_RHI TConcreteType;`
- L600 _public typedef_ `typedef FD3D11UniformBuffer TConcreteType;`
- L605 _public typedef_ `typedef FD3D11Buffer TConcreteType;`
- L610 _public typedef_ `typedef FD3D11StagingBuffer TConcreteType;`
- L616 _public typedef_ `typedef FD3D11GPUFence TConcreteType;`
- L621 _public typedef_ `typedef FD3D11ShaderResourceView TConcreteType;`
- L626 _public typedef_ `typedef FD3D11UnorderedAccessView TConcreteType;`

#### struct `TD3D11ResourceTraits`  
`template<> struct TD3D11ResourceTraits<FRHIBoundShaderState>`  
_L588-591_
- L565 _public typedef_ `typedef FD3D11VertexDeclaration TConcreteType;`
- L570 _public typedef_ `typedef FD3D11VertexShader TConcreteType;`
- L575 _public typedef_ `typedef FD3D11GeometryShader TConcreteType;`
- L580 _public typedef_ `typedef FD3D11PixelShader TConcreteType;`
- L585 _public typedef_ `typedef FD3D11ComputeShader TConcreteType;`
- L590 _public typedef_ `typedef FD3D11BoundShaderState TConcreteType;`
- L595 _public typedef_ `typedef FD3D11RenderQuery_RHI TConcreteType;`
- L600 _public typedef_ `typedef FD3D11UniformBuffer TConcreteType;`
- L605 _public typedef_ `typedef FD3D11Buffer TConcreteType;`
- L610 _public typedef_ `typedef FD3D11StagingBuffer TConcreteType;`
- L616 _public typedef_ `typedef FD3D11GPUFence TConcreteType;`
- L621 _public typedef_ `typedef FD3D11ShaderResourceView TConcreteType;`
- L626 _public typedef_ `typedef FD3D11UnorderedAccessView TConcreteType;`

#### struct `TD3D11ResourceTraits`  
`template<> struct TD3D11ResourceTraits<FRHIRenderQuery>`  
_L593-596_
- L565 _public typedef_ `typedef FD3D11VertexDeclaration TConcreteType;`
- L570 _public typedef_ `typedef FD3D11VertexShader TConcreteType;`
- L575 _public typedef_ `typedef FD3D11GeometryShader TConcreteType;`
- L580 _public typedef_ `typedef FD3D11PixelShader TConcreteType;`
- L585 _public typedef_ `typedef FD3D11ComputeShader TConcreteType;`
- L590 _public typedef_ `typedef FD3D11BoundShaderState TConcreteType;`
- L595 _public typedef_ `typedef FD3D11RenderQuery_RHI TConcreteType;`
- L600 _public typedef_ `typedef FD3D11UniformBuffer TConcreteType;`
- L605 _public typedef_ `typedef FD3D11Buffer TConcreteType;`
- L610 _public typedef_ `typedef FD3D11StagingBuffer TConcreteType;`
- L616 _public typedef_ `typedef FD3D11GPUFence TConcreteType;`
- L621 _public typedef_ `typedef FD3D11ShaderResourceView TConcreteType;`
- L626 _public typedef_ `typedef FD3D11UnorderedAccessView TConcreteType;`

#### struct `TD3D11ResourceTraits`  
`template<> struct TD3D11ResourceTraits<FRHIUniformBuffer>`  
_L598-601_
- L565 _public typedef_ `typedef FD3D11VertexDeclaration TConcreteType;`
- L570 _public typedef_ `typedef FD3D11VertexShader TConcreteType;`
- L575 _public typedef_ `typedef FD3D11GeometryShader TConcreteType;`
- L580 _public typedef_ `typedef FD3D11PixelShader TConcreteType;`
- L585 _public typedef_ `typedef FD3D11ComputeShader TConcreteType;`
- L590 _public typedef_ `typedef FD3D11BoundShaderState TConcreteType;`
- L595 _public typedef_ `typedef FD3D11RenderQuery_RHI TConcreteType;`
- L600 _public typedef_ `typedef FD3D11UniformBuffer TConcreteType;`
- L605 _public typedef_ `typedef FD3D11Buffer TConcreteType;`
- L610 _public typedef_ `typedef FD3D11StagingBuffer TConcreteType;`
- L616 _public typedef_ `typedef FD3D11GPUFence TConcreteType;`
- L621 _public typedef_ `typedef FD3D11ShaderResourceView TConcreteType;`
- L626 _public typedef_ `typedef FD3D11UnorderedAccessView TConcreteType;`

#### struct `TD3D11ResourceTraits`  
`template<> struct TD3D11ResourceTraits<FRHIBuffer>`  
_L603-606_
- L565 _public typedef_ `typedef FD3D11VertexDeclaration TConcreteType;`
- L570 _public typedef_ `typedef FD3D11VertexShader TConcreteType;`
- L575 _public typedef_ `typedef FD3D11GeometryShader TConcreteType;`
- L580 _public typedef_ `typedef FD3D11PixelShader TConcreteType;`
- L585 _public typedef_ `typedef FD3D11ComputeShader TConcreteType;`
- L590 _public typedef_ `typedef FD3D11BoundShaderState TConcreteType;`
- L595 _public typedef_ `typedef FD3D11RenderQuery_RHI TConcreteType;`
- L600 _public typedef_ `typedef FD3D11UniformBuffer TConcreteType;`
- L605 _public typedef_ `typedef FD3D11Buffer TConcreteType;`
- L610 _public typedef_ `typedef FD3D11StagingBuffer TConcreteType;`
- L616 _public typedef_ `typedef FD3D11GPUFence TConcreteType;`
- L621 _public typedef_ `typedef FD3D11ShaderResourceView TConcreteType;`
- L626 _public typedef_ `typedef FD3D11UnorderedAccessView TConcreteType;`

#### struct `TD3D11ResourceTraits`  
`template<> struct TD3D11ResourceTraits<FRHIStagingBuffer>`  
_L608-611_
- L565 _public typedef_ `typedef FD3D11VertexDeclaration TConcreteType;`
- L570 _public typedef_ `typedef FD3D11VertexShader TConcreteType;`
- L575 _public typedef_ `typedef FD3D11GeometryShader TConcreteType;`
- L580 _public typedef_ `typedef FD3D11PixelShader TConcreteType;`
- L585 _public typedef_ `typedef FD3D11ComputeShader TConcreteType;`
- L590 _public typedef_ `typedef FD3D11BoundShaderState TConcreteType;`
- L595 _public typedef_ `typedef FD3D11RenderQuery_RHI TConcreteType;`
- L600 _public typedef_ `typedef FD3D11UniformBuffer TConcreteType;`
- L605 _public typedef_ `typedef FD3D11Buffer TConcreteType;`
- L610 _public typedef_ `typedef FD3D11StagingBuffer TConcreteType;`
- L616 _public typedef_ `typedef FD3D11GPUFence TConcreteType;`
- L621 _public typedef_ `typedef FD3D11ShaderResourceView TConcreteType;`
- L626 _public typedef_ `typedef FD3D11UnorderedAccessView TConcreteType;`

#### struct `TD3D11ResourceTraits`  
`template<> struct TD3D11ResourceTraits<FRHIGPUFence>`  
_L614-617_
- desc: @todo-staging Implement D3D11 fences.
- L565 _public typedef_ `typedef FD3D11VertexDeclaration TConcreteType;`
- L570 _public typedef_ `typedef FD3D11VertexShader TConcreteType;`
- L575 _public typedef_ `typedef FD3D11GeometryShader TConcreteType;`
- L580 _public typedef_ `typedef FD3D11PixelShader TConcreteType;`
- L585 _public typedef_ `typedef FD3D11ComputeShader TConcreteType;`
- L590 _public typedef_ `typedef FD3D11BoundShaderState TConcreteType;`
- L595 _public typedef_ `typedef FD3D11RenderQuery_RHI TConcreteType;`
- L600 _public typedef_ `typedef FD3D11UniformBuffer TConcreteType;`
- L605 _public typedef_ `typedef FD3D11Buffer TConcreteType;`
- L610 _public typedef_ `typedef FD3D11StagingBuffer TConcreteType;`
- L616 _public typedef_ `typedef FD3D11GPUFence TConcreteType;`
- L621 _public typedef_ `typedef FD3D11ShaderResourceView TConcreteType;`
- L626 _public typedef_ `typedef FD3D11UnorderedAccessView TConcreteType;`

#### struct `TD3D11ResourceTraits`  
`template<> struct TD3D11ResourceTraits<FRHIShaderResourceView>`  
_L619-622_
- L565 _public typedef_ `typedef FD3D11VertexDeclaration TConcreteType;`
- L570 _public typedef_ `typedef FD3D11VertexShader TConcreteType;`
- L575 _public typedef_ `typedef FD3D11GeometryShader TConcreteType;`
- L580 _public typedef_ `typedef FD3D11PixelShader TConcreteType;`
- L585 _public typedef_ `typedef FD3D11ComputeShader TConcreteType;`
- L590 _public typedef_ `typedef FD3D11BoundShaderState TConcreteType;`
- L595 _public typedef_ `typedef FD3D11RenderQuery_RHI TConcreteType;`
- L600 _public typedef_ `typedef FD3D11UniformBuffer TConcreteType;`
- L605 _public typedef_ `typedef FD3D11Buffer TConcreteType;`
- L610 _public typedef_ `typedef FD3D11StagingBuffer TConcreteType;`
- L616 _public typedef_ `typedef FD3D11GPUFence TConcreteType;`
- L621 _public typedef_ `typedef FD3D11ShaderResourceView TConcreteType;`
- L626 _public typedef_ `typedef FD3D11UnorderedAccessView TConcreteType;`

#### struct `TD3D11ResourceTraits`  
`template<> struct TD3D11ResourceTraits<FRHIUnorderedAccessView>`  
_L624-627_
- L565 _public typedef_ `typedef FD3D11VertexDeclaration TConcreteType;`
- L570 _public typedef_ `typedef FD3D11VertexShader TConcreteType;`
- L575 _public typedef_ `typedef FD3D11GeometryShader TConcreteType;`
- L580 _public typedef_ `typedef FD3D11PixelShader TConcreteType;`
- L585 _public typedef_ `typedef FD3D11ComputeShader TConcreteType;`
- L590 _public typedef_ `typedef FD3D11BoundShaderState TConcreteType;`
- L595 _public typedef_ `typedef FD3D11RenderQuery_RHI TConcreteType;`
- L600 _public typedef_ `typedef FD3D11UniformBuffer TConcreteType;`
- L605 _public typedef_ `typedef FD3D11Buffer TConcreteType;`
- L610 _public typedef_ `typedef FD3D11StagingBuffer TConcreteType;`
- L616 _public typedef_ `typedef FD3D11GPUFence TConcreteType;`
- L621 _public typedef_ `typedef FD3D11ShaderResourceView TConcreteType;`
- L626 _public typedef_ `typedef FD3D11UnorderedAccessView TConcreteType;`

#### Free symbols / members of external scopes

- L14 _typedef_ `typedef ID3D11DeviceContext FD3D11DeviceContext;`
- L19 _enumerator_ `enum { IsBytewiseComparable = true };` (scope `TTypeTraits::__anon4336d64e0103`)
- L23 _typedef_ `typedef TArray<D3D11_INPUT_ELEMENT_DESC,TFixedAllocator<MaxVertexElementCount> > FD3D11VertexElements;` — Convenience typedef: preallocated array of D3D11 input element descriptions.
- L54 _enumerator_ `enum { StaticFrequency = SF_Vertex }; TRefCountPtr<ID3D11VertexShader> Resource; TArray<uint8> Code;` (scope `FD3D11VertexShader::__anon4336d64e0203`)
- L69 _enumerator_ `enum { StaticFrequency = SF_Geometry }; TRefCountPtr<ID3D11GeometryShader> Resource;` (scope `FD3D11GeometryShader::__anon4336d64e0303`)
- L78 _enumerator_ `enum { StaticFrequency = SF_Pixel }; TRefCountPtr<ID3D11PixelShader> Resource;` (scope `FD3D11PixelShader::__anon4336d64e0403`)
- L87 _enumerator_ `enum { StaticFrequency = SF_Compute }; TRefCountPtr<ID3D11ComputeShader> Resource;` (scope `FD3D11ComputeShader::__anon4336d64e0503`)
- L517 _namespace_ `namespace D3D11BufferStats`
- L519 _prototype_ `void UpdateUniformBufferStats(ID3D11Buffer* Buffer, int64 BufferSize, bool bAllocating);` (scope `D3D11BufferStats`)
- L520 _prototype_ `void UpdateBufferStats(FD3D11Buffer& Buffer, bool bAllocating);` (scope `D3D11BufferStats`)

### `Source/Runtime/Windows/D3D11RHI/Public/D3D11State.h` (Public)


#### class `FD3D11SamplerState`  
`class FD3D11SamplerState : public FRHISamplerState`  
_L11-16_
- inherits: `FRHISamplerState`
- L15 _public member_ `TRefCountPtr<ID3D11SamplerState> Resource;`

#### class `FD3D11RasterizerState`  
`class FD3D11RasterizerState : public FRHIRasterizerState`  
_L18-23_
- inherits: `FRHIRasterizerState`
- L22 _public member_ `TRefCountPtr<ID3D11RasterizerState> Resource;`

#### class `FD3D11DepthStencilState`  
`class FD3D11DepthStencilState : public FRHIDepthStencilState`  
_L25-33_
- inherits: `FRHIDepthStencilState`
- L29 _public member_ `TRefCountPtr<ID3D11DepthStencilState> Resource;`
- L32 _public member_ `FExclusiveDepthStencil AccessType;` — Describes the read/write state of the separate depth and stencil components of the DSV.

#### class `FD3D11BlendState`  
`class FD3D11BlendState : public FRHIBlendState`  
_L35-40_
- inherits: `FRHIBlendState`
- L39 _public member_ `TRefCountPtr<ID3D11BlendState> Resource;`

#### struct `TD3D11ResourceTraits`  
`template<> struct TD3D11ResourceTraits<FRHISamplerState>`  
_L43-46_
- L45 _public typedef_ `typedef FD3D11SamplerState TConcreteType;`
- L50 _public typedef_ `typedef FD3D11RasterizerState TConcreteType;`
- L55 _public typedef_ `typedef FD3D11DepthStencilState TConcreteType;`
- L60 _public typedef_ `typedef FD3D11BlendState TConcreteType;`

#### struct `TD3D11ResourceTraits`  
`template<> struct TD3D11ResourceTraits<FRHIRasterizerState>`  
_L48-51_
- L45 _public typedef_ `typedef FD3D11SamplerState TConcreteType;`
- L50 _public typedef_ `typedef FD3D11RasterizerState TConcreteType;`
- L55 _public typedef_ `typedef FD3D11DepthStencilState TConcreteType;`
- L60 _public typedef_ `typedef FD3D11BlendState TConcreteType;`

#### struct `TD3D11ResourceTraits`  
`template<> struct TD3D11ResourceTraits<FRHIDepthStencilState>`  
_L53-56_
- L45 _public typedef_ `typedef FD3D11SamplerState TConcreteType;`
- L50 _public typedef_ `typedef FD3D11RasterizerState TConcreteType;`
- L55 _public typedef_ `typedef FD3D11DepthStencilState TConcreteType;`
- L60 _public typedef_ `typedef FD3D11BlendState TConcreteType;`

#### struct `TD3D11ResourceTraits`  
`template<> struct TD3D11ResourceTraits<FRHIBlendState>`  
_L58-61_
- L45 _public typedef_ `typedef FD3D11SamplerState TConcreteType;`
- L50 _public typedef_ `typedef FD3D11RasterizerState TConcreteType;`
- L55 _public typedef_ `typedef FD3D11DepthStencilState TConcreteType;`
- L60 _public typedef_ `typedef FD3D11BlendState TConcreteType;`

### `Source/Runtime/Windows/D3D11RHI/Public/D3D11Util.h` (Public)


#### struct `FD3D11ResizeViewportState`  
`struct FD3D11ResizeViewportState`  
_L71-77_
- L73 _public member_ `uint32 SizeX;`
- L74 _public member_ `uint32 SizeY;`
- L75 _public member_ `DXGI_FORMAT Format;`
- L76 _public member_ `bool bIsFullscreen;`

#### class `FD3D11LockedKey`  
`class FD3D11LockedKey`  
_L134-167_
- desc: Keeps track of Locks for D3D11 objects
- L137 _public member_ `ID3D11Resource* SourceObject = nullptr;`
- L138 _public member_ `uint32 Subresource = 0;`
- L140 _public prototype_ `FD3D11LockedKey() = default;`
- L142 _public function_ `FD3D11LockedKey(ID3D11Resource* InSource, uint32 InSubresource = 0) : SourceObject(InSource) , Subresource (InSubresource)`
- L147 _public function_ `bool operator == (const FD3D11LockedKey& Other) const`
- L152 _public function_ `bool operator != (const FD3D11LockedKey& Other) const`
- L157 _public function_ `uint32 GetHash() const`

#### struct `FD3D11LockedData`  
`struct FD3D11LockedData`  
_L170-217_
- desc: Information about a D3D resource that is currently locked.
- L172 _public member_ `TRefCountPtr<ID3D11Resource> StagingResource;`
- L173 _public member_ `uint32 Pitch;`
- L174 _public member_ `uint32 DepthPitch;`
- L177 _public function_ `FD3D11LockedData() : bAllocDataWasUsed(false) , bLockDeferred(false)` — constructor
- L184 _public function_ `void AllocData(uint32 Size)` — 16 byte alignment for best performance  (can be 30x faster than unaligned)
- L191 _public function_ `void SetData(void* InData)` — Some driver might return aligned memory so we don't enforce the alignment
- L196 _public function_ `uint8* GetData() const`
- L202 _public function_ `void FreeData()` — only call if AllocData() was used
- L211 _private member_ `uint8* Data;`
- L213 _private member_ `bool bAllocDataWasUsed;` — then FreeData
- L216 _public member_ `bool bLockDeferred;` — Whether the lock op is deferred

#### class `FD3D11BoundRenderTargets`  
`class FD3D11BoundRenderTargets`  
_L222-243_
- desc: Class for retrieving render targets currently bound to the device context.
- L226 _public prototype_ `explicit FD3D11BoundRenderTargets(ID3D11DeviceContext* InDeviceContext);` — Initialization constructor: requires the device context.
- L229 _public prototype_ `~FD3D11BoundRenderTargets();` — Destructor.
- L232 _public function_ `inline int32 GetNumActiveTargets() const` — Accessors.
- L233 _public function_ `inline ID3D11RenderTargetView* GetRenderTargetView(int32 TargetIndex)`
- L234 _public function_ `inline ID3D11DepthStencilView* GetDepthStencilView()`
- L238 _private member_ `ID3D11RenderTargetView* RenderTargetViews[MaxSimultaneousRenderTargets];` — Active render target views.
- L240 _private member_ `ID3D11DepthStencilView* DepthStencilView;` — Active depth stencil view.
- L242 _private member_ `int32 NumActiveTargets;` — The number of active render targets.

#### struct `FD3D11RHIGenericCommandString`  
`struct FD3D11RHIGenericCommandString`  
_L245-248_
- L247 _public function_ `static const TCHAR* TStr()`

#### class `TD3D11RHIGenericCommand`  
`class TD3D11RHIGenericCommand final : public FRHICommand<TD3D11RHIGenericCommand<JobType>, FD3D11RHIGenericCommandString>`  
_L255-270_
- inherits: `FRHICommand<TD3D11RHIGenericCommand<JobType>,FD3D11RHIGenericCommandString>`
- L259 _public function_ `TD3D11RHIGenericCommand(JobType&& InRHIJob) : RHIJob(Forward<JobType>(InRHIJob))` — InRHIJob is supposed to be called on RHIT (don't capture things that can become outdated here)
- L263 _public function_ `void Execute(FRHICommandListBase& RHICmdList)`
- L269 _private member_ `JobType RHIJob;`

#### Free symbols / members of external scopes

- L21 _macro_ `#define D3D11RHI_IMMEDIATE_CONTEXT (GD3D11RHI->GetDeviceContext())`
- L22 _macro_ `#define D3D11RHI_DEVICE (GD3D11RHI->GetDevice())`
- L24 _prototype_ `void SetD3D11ObjectName(ID3D11DeviceChild* Object, FAnsiStringView Name);`
- L25 _prototype_ `void SetD3D11ObjectName(ID3D11DeviceChild* Object, FStringView Name);`
- L26 _prototype_ `void SetD3D11ResourceName(FD3D11Texture* Texture, FStringView Name);`
- L27 _prototype_ `void SetD3D11ResourceName(FD3D11Buffer* Buffer, FStringView Name);`
- L28 _prototype_ `void SetD3D11ResourceName(FD3D11UnorderedAccessView* UAV, FStringView Name);`
- L37 _prototype_ `extern void VerifyD3D11ResultNoExit(HRESULT Result, const ANSICHAR* Code, const ANSICHAR* Filename, uint32 Line, ID3D11Device* Device);` — Checks that the given result isn't a failure.  If it is, the application does not exit and only logs an appropriate error message. @param	Result - The result code to check. @param	Code - The code which yielded the result. @param	Filename - The filename of the source file containing Code. @param	Line - The line number of Code within Filename.
- L46 _prototype_ `extern void VerifyD3D11Result(HRESULT Result,const ANSICHAR* Code,const ANSICHAR* Filename,uint32 Line, ID3D11Device* Device);` — Checks that the given result isn't a failure.  If it is, the application exits with an appropriate error message. @param	Result - The result code to check. @param	Code - The code which yielded the result. @param	Filename - The filename of the source file containing Code. @param	Line - The line number of Code within Filename.
- L57 _prototype_ `extern void VerifyD3D11ShaderResult(class FRHIShader* Shader, HRESULT Result, const ANSICHAR* Code, const ANSICHAR* Filename, uint32 Line, ID3D11Device* Device);` — Checks that the given result isn't a failure.  If it is, the application exits with an appropriate error message. @param	Shader - The shader we are trying to create. @param	Result - The result code to check. @param	Code - The code which yielded the result. @param	Filename - The filename of the source file containing Code. @param	Line - The line number of Code within Filename. @param	Device - The D3D device used to create the shader.
- L66 _prototype_ `extern void VerifyD3D11CreateTextureResult(HRESULT D3DResult, int32 UEFormat,const ANSICHAR* Code,const ANSICHAR* Filename,uint32 Line, uint32 SizeX,uint32 SizeY,uint32 SizeZ,uint8 D3DFormat,uint32 NumMips,uint32 Flags, D3D11_USAGE Usage, uint32 CPUAccessFlags, uint32 MiscFlags, uint32 SampleCount, uint32 SampleQuality, const void* SubResPtr, uint32 SubResPitch, uint32 SubResSlicePitch, ID3D11Device* Device, const TCHAR* DebugName);` — Checks that the given result isn't a failure.  If it is, the application exits with an appropriate error message. @param	Result - The result code to check @param	Code - The code which yielded the result. @param	Filename - The filename of the source file containing Code. @param	Line - The line number of Code within Filename.
- L79 _prototype_ `extern void VerifyD3D11ResizeViewportResult(HRESULT D3DResult, const ANSICHAR* Code, const ANSICHAR* Filename, uint32 Line, const FD3D11ResizeViewportState& OldState, const FD3D11ResizeViewportState& NewState, ID3D11Device* Device);`
- L82 _prototype_ `extern void VerifyD3D11CreateViewResult(HRESULT D3DResult, const ANSICHAR* Code, const ANSICHAR* Filename, uint32 Line, ID3D11Device* Device, FRHITexture* Texture, const D3D11_UNORDERED_ACCESS_VIEW_DESC& Desc);`
- L83 _prototype_ `extern void VerifyD3D11CreateViewResult(HRESULT D3DResult, const ANSICHAR* Code, const ANSICHAR* Filename, uint32 Line, ID3D11Device* Device, FRHIBuffer* Buffer, const D3D11_UNORDERED_ACCESS_VIEW_DESC& Desc);`
- L88 _macro_ `#define VERIFYD3D11RESULT_EX(x, Device) {HRESULT hr = x; if (FAILED(hr)) { VerifyD3D11Result(hr,#x,__FILE__,__LINE__, Device); }}` — A macro for using VERIFYD3D11RESULT that automatically passes in the code and filename/line.
- L89 _macro_ `#define VERIFYD3D11RESULT(x) {HRESULT hr = x; if (FAILED(hr)) { VerifyD3D11Result(hr,#x,__FILE__,__LINE__, 0); }}`
- L90 _macro_ `#define VERIFYD3D11RESULT_NOEXIT(x) {HRESULT hr = x; if (FAILED(hr)) { VerifyD3D11ResultNoExit(hr,#x,__FILE__,__LINE__, 0); }}`
- L91 _macro_ `#define VERIFYD3D11SHADERRESULT(Result, Shader, Device) {HRESULT hr = (Result); if (FAILED(hr)) { VerifyD3D11ShaderResult(Shader, hr, #Result,__FILE__,__LINE__, Device); }}`
- L93 _macro_ `#define VERIFYD3D11CREATETEXTURERESULT(x,UEFormat,SizeX,SizeY,SizeZ,Format,NumMips,Flags,Usage,CPUAccessFlags,MiscFlags,SampleCount,SampleQuality,SubResPtr,SubResPitch,SubResSlicePitch,Device,DebugName) {HRESULT hr = x; if (FAILED(hr)) { Ve`
- L94 _macro_ `#define VERIFYD3D11RESIZEVIEWPORTRESULT(x, OldState, NewState, Device) { HRESULT hr = x; if (FAILED(hr)) { VerifyD3D11ResizeViewportResult(hr, #x, __FILE__, __LINE__, OldState, NewState, Device); }}`
- L95 _macro_ `#define VERIFYD3D11CREATEVIEWRESULT(x, Device, Resource, Desc) {HRESULT hr = x; if (FAILED(hr)) { VerifyD3D11CreateViewResult(hr, #x, __FILE__, __LINE__, Device, Resource, Desc); }}`
- L100 _prototype_ `extern void VerifyComRefCount(IUnknown* Object,int32 ExpectedRefs,const TCHAR* Code,const TCHAR* Filename,int32 Line);` — Checks that a COM object has the expected number of references.
- L101 _macro_ `#define checkComRefCount(Obj,ExpectedRefs) VerifyComRefCount(Obj,ExpectedRefs,TEXT(#Obj),TEXT(__FILE__),__LINE__)`
- L104 _prototype_ `FString GetD3D11ErrorString(HRESULT ErrorCode, ID3D11Device* Device);` — Returns a string for the provided error code, can include device removed information if the device is provided.
- L111 _function_ `inline uint32 GetD3D11CubeFace(ECubeFace Face)` — Convert from ECubeFace to D3DCUBEMAP_FACES type @param Face - ECubeFace type to convert @return D3D cube face enum value
- L163 _function_ `friend uint32 GetTypeHash(const FD3D11LockedKey& K)` — Hashing function.
- L273 _function_ `template<typename JobType> inline void RunOnRHIThread(JobType&& InRHIJob)`
- L276 _typedef_ `typedef TD3D11RHIGenericCommand<JobType> CmdType;` (scope `RunOnRHIThread`) — check(IsInRenderingThread());
- L281 _function_ `inline bool ShouldNotEnqueueRHICommand()`

### `Source/Runtime/Windows/D3D11RHI/Public/D3D11Viewport.h` (Public)


#### class `FD3D11Viewport`  
`class FD3D11Viewport : public FRHIViewport`  
_L16-142_
- inherits: `FRHIViewport`
- L26 _public prototype_ `FD3D11Viewport(class FD3D11DynamicRHI* InD3DRHI, HWND InWindowHandle, uint32 InSizeX, uint32 InSizeY, bool bInIsFullscreen, EPixelFormat InPreferredPixelFormat);`
- L27 _public prototype_ `~FD3D11Viewport();`
- L29 _public prototype_ `virtual void Resize(uint32 InSizeX, uint32 InSizeY, bool bInIsFullscreen, EPixelFormat PreferredPixelFormat);`
- L36 _public prototype_ `void ConditionalResetSwapChain(bool bIgnoreFocus);` — If the swap chain has been invalidated by DXGI, resets the swap chain to the expected state; otherwise, does nothing. Called once/frame by the game thread on all viewports. @param bIgnoreFocus - Whether the reset should happen regardless of whether the window is focused.
- L41 _public prototype_ `void CheckHDRMonitorStatus();` — Called whenever the Viewport is moved to see if it has moved between HDR or LDR monitors
- L47 _public prototype_ `bool Present(IRHICommandContext& RHICmdContext, bool bLockToVsync);` — Presents the swap chain. Returns true if Present was done by Engine.
- L50 _public function_ `FIntPoint GetSizeXY() const` — Accessors.
- L51 _public function_ `FD3D11Texture* GetBackBuffer() const`
- L53 _public prototype_ `virtual void WaitForFrameEventCompletion() override;`
- L54 _public prototype_ `virtual void IssueFrameEvent() override;`
- L56 _public function_ `IDXGISwapChain* GetSwapChain() const`
- L58 _public prototype_ `virtual void* GetNativeSwapChain() const override;`
- L59 _public prototype_ `virtual void* GetNativeBackBufferTexture() const override;`
- L60 _public prototype_ `virtual void* GetNativeBackBufferRT() const override;`
- L62 _public function_ `virtual void SetCustomPresent(FRHICustomPresent* InCustomPresent) override`
- L66 _public function_ `virtual FRHICustomPresent* GetCustomPresent() const`
- L68 _public function_ `virtual void* GetNativeWindow(void** AddParam = nullptr) const override`
- L69 _public prototype_ `static FD3D11Texture* GetSwapChainSurface(FD3D11DynamicRHI* D3DRHI, EPixelFormat PixelFormat, uint32 SizeX, uint32 SizeY, IDXGISwapChain* SwapChain);`
- L71 _public function_ `static DXGI_FORMAT GetRenderTargetFormat(EPixelFormat PixelFormat)`
- L78 _protected prototype_ `void ResetSwapChainInternal(bool bIgnoreFocus);`
- L81 _protected prototype_ `uint32 GetSwapChainFlags();` — Gets the swap chain flags
- L84 _protected prototype_ `void PresentWithVsyncDWM(IRHICommandContext& RHICmdContext);` — Presents the frame synchronizing with DWM.
- L90 _protected prototype_ `bool PresentChecked(IRHICommandContext& RHICmdContext, int32 SyncInterval);` — Presents the swap chain checking the return result. Returns true if Present was done by Engine.
- L93 _protected prototype_ `void EnableHDR();` — Enable HDR meta data transmission and set the necessary color space.
- L96 _protected prototype_ `void ShutdownHDR();` — Disable HDR meta data transmission and set the necessary color space.
- L99 _protected member_ `FD3D11DynamicRHI* const D3DRHI;`
- L100 _protected member_ `HWND const WindowHandle;`
- L102 _protected member_ `EPixelFormat PixelFormat;`
- L103 _protected member_ `uint32 SizeX;`
- L104 _protected member_ `uint32 SizeY;`
- L105 _protected member_ `bool bIsFullscreen;`
- L107 _protected member_ `uint64 LastFlipTime = 0;`
- L108 _protected member_ `uint64 LastFrameComplete = 0;`
- L109 _protected member_ `uint64 LastCompleteTime = 0;`
- L110 _protected member_ `int32 SyncCounter = 0;`
- L111 _protected member_ `bool bSyncedLastFrame = false;`
- L112 _protected member_ `uint32 MaximumFrameLatency = 3;`
- L113 _protected member_ `uint32 BackBufferCount = 0;`
- L114 _protected member_ `uint32 PresentFailCount = 0;`
- L115 _protected member_ `TAtomic<uint32> ValidState = 0;`
- L116 _protected member_ `EDisplayColorGamut DisplayColorGamut = EDisplayColorGamut::sRGB_D65;`
- L117 _protected member_ `EDisplayOutputFormat DisplayOutputFormat = EDisplayOutputFormat::SDR_sRGB;`
- L118 _protected member_ `bool bAllowTearing = false;`
- L119 _protected member_ `bool bResizeInProgress = false;`
- L121 _protected member_ `static uint32 GSwapChainFlags;`
- L123 _protected member_ `TRefCountPtr<IDXGISwapChain> SwapChain;`
- L124 _protected member_ `TRefCountPtr<FD3D11Texture> BackBuffer;`
- L127 _protected member_ `TRefCountPtr<IDXGIOutput> ForcedFullscreenOutput;` — Support for selecting non-default output for display in fullscreen exclusive
- L128 _protected member_ `bool bForcedFullscreenDisplay;`
- L133 _protected member_ `bool bNeedSwapChain;` — Whether to create swap chain and use swap chain's back buffer surface, or don't create swap chain and create an off-screen back buffer surface. Currently used for pixel streaming plugin "windowless" mode to run in the cloud without on screen display.
- L136 _protected member_ `FGraphEventRef FrameSyncEvent;` — An event used to track the GPU's progress.
- L138 _protected member_ `FCustomPresentRHIRef CustomPresent;`
- L140 _protected prototype_ `DXGI_MODE_DESC SetupDXGI_MODE_DESC() const;`

#### enum `FD3D11Viewport::ED3DViewportValidFlags`  
`enum ED3DViewportValidFlags : uint32`  
_L19-24_
- L21 _public enumerator_ `VIEWPORT_INVALID = 0x1`
- L22 _public enumerator_ `VIEWPORT_FULLSCREEN_LOST = 0x2`

#### struct `TD3D11ResourceTraits`  
`template<> struct TD3D11ResourceTraits<FRHIViewport>`  
_L145-148_
- L147 _public typedef_ `typedef FD3D11Viewport TConcreteType;`

### `Source/Runtime/Windows/D3D11RHI/Public/ID3D11DynamicRHI.h` (Public)


#### struct `ID3D11DynamicRHI`  
`struct ID3D11DynamicRHI : public FDynamicRHIPSOFallback`  
_L15-45_
- inherits: `FDynamicRHIPSOFallback`
- L17 _public function_ `virtual ERHIInterfaceType GetInterfaceType() const override final`
- L19 _public prototype_ `virtual ID3D11Device* RHIGetDevice() const = 0;`
- L20 _public prototype_ `virtual ID3D11DeviceContext* RHIGetDeviceContext() const = 0;`
- L21 _public prototype_ `virtual IDXGIAdapter* RHIGetAdapter() const = 0;`
- L22 _public prototype_ `virtual IDXGISwapChain* RHIGetSwapChain(FRHIViewport* InViewport) const = 0;`
- L23 _public prototype_ `virtual DXGI_FORMAT RHIGetSwapChainFormat(EPixelFormat InFormat) const = 0;`
- L25 _public prototype_ `virtual FTextureRHIRef RHICreateTexture2DFromResource(EPixelFormat Format, ETextureCreateFlags TexCreateFlags, const FClearValueBinding& ClearValueBinding, ID3D11Texture2D* Resource) = 0;`
- L26 _public prototype_ `virtual FTextureRHIRef RHICreateTexture2DArrayFromResource(EPixelFormat Format, ETextureCreateFlags TexCreateFlags, const FClearValueBinding& ClearValueBinding, ID3D11Texture2D* Resource) = 0;`
- L27 _public prototype_ `virtual FTextureRHIRef RHICreateTextureCubeFromResource(EPixelFormat Format, ETextureCreateFlags TexCreateFlags, const FClearValueBinding& ClearValueBinding, ID3D11Texture2D* Resource) = 0;`
- L29 _public prototype_ `virtual ID3D11Buffer* RHIGetResource(FRHIBuffer* InBuffer) const = 0;`
- L30 _public prototype_ `virtual ID3D11Resource* RHIGetResource(FRHITexture* InTexture) const = 0;`
- L31 _public prototype_ `virtual int64 RHIGetResourceMemorySize(FRHITexture* InTexture) const = 0;`
- L33 _public prototype_ `virtual ID3D11RenderTargetView* RHIGetRenderTargetView(FRHITexture* InTexture, int32 InMipIndex = 0, int32 InArraySliceIndex = -1) const = 0;`
- L34 _public prototype_ `virtual ID3D11ShaderResourceView* RHIGetShaderResourceView(FRHITexture* InTexture) const = 0;`
- L36 _public prototype_ `virtual void RHIVerifyResult(ID3D11Device* Device, HRESULT Result, const ANSICHAR* Code, const ANSICHAR* Filename, uint32 Line) const = 0;`
- L39 _public prototype_ `virtual FRHIViewport* RHIGetSingletonViewport() const = 0;` — Returns the RHI viewport, assuming only a single FRHIViewport instance exists. Otherwise, returns nullptr.
- L42 _public function_ `void RHIRegisterWork(uint32 NumPrimitives)` — `UE_DEPRECATED(5.8, "RHIRegisterWork is deprecated, and there is no replacement. Remove calls to this function.")`

#### Free symbols / members of external scopes

- L12 _typedef_ `typedef ID3D11DeviceContext FD3D11DeviceContext;`
- L13 _typedef_ `typedef ID3D11Device FD3D11Device;`
- L47 _function_ `inline bool IsRHID3D11()`
- L52 _function_ `inline ID3D11DynamicRHI* GetID3D11DynamicRHI()`
