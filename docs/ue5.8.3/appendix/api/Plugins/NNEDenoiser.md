# Plugins / NNEDenoiser

- module root: `Plugins/NNE/NNEDenoiser/Source/NNEDenoiser`
- headers: 28; symbols: 378
- symbol kinds: class=25, delegate=1, enum=6, enumerator=19, function=23, macro=3, member=86, namespace=77, prototype=124, struct=12, typedef=2
- PrivateDependencyModuleNames: CoreUObject, DeveloperSettings, Engine, NNE, NNEDenoiserShaders, RHI, Renderer
- PublicDependencyModuleNames: Core, RenderCore

### `Plugins/NNE/NNEDenoiser/Source/NNEDenoiser/Private/NNEDenoiser.h` (Private)


#### class `FNNEDenoiserModule`  
`class FNNEDenoiserModule : public IModuleInterface`  
_L13-22_
- inherits: `IModuleInterface`
- L17 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface implementation
- L18 _public prototype_ `virtual void ShutdownModule() override;`
- L21 _private member_ `TSharedPtr<UE::NNEDenoiser::Private::FViewExtension, ESPMode::ThreadSafe> ViewExtension;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace NNEDenoiser` (scope `UE`)
- L8 _namespace_ `namespace Private` (scope `UE::NNEDenoiser`)

### `Plugins/NNE/NNEDenoiser/Source/NNEDenoiser/Private/NNEDenoiserAutoExposure.h` (Private)


#### class `UE::NNEDenoiser::Private::IAutoExposure`  
`class IAutoExposure`  
_L14-21_
- L17 _public prototype_ `virtual ~IAutoExposure() = default;`
- L19 _public prototype_ `virtual void Run(TConstArrayView<FLinearColor> InputData, FIntPoint Size, float& OutputValue) const = 0;`
- L20 _public prototype_ `virtual void EnqueueRDG(FRDGBuilder& GraphBuilder, FRDGTextureRef InputTexture, FRDGBufferRef OutputBuffer) const = 0;`

#### class `UE::NNEDenoiser::Private::FAutoExposure`  
`class FAutoExposure : public IAutoExposure`  
_L23-30_
- inherits: `IAutoExposure`
- L26 _public prototype_ `virtual ~FAutoExposure() = default;`
- L28 _public prototype_ `virtual void Run(TConstArrayView<FLinearColor> InputData, FIntPoint Size, float& OutputValue) const override;`
- L29 _public prototype_ `virtual void EnqueueRDG(FRDGBuilder& GraphBuilder, FRDGTextureRef InputTexture, FRDGBufferRef OutputBuffer) const override;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace NNEDenoiser` (scope `UE`)
- L11 _namespace_ `namespace Private` (scope `UE::NNEDenoiser`)

### `Plugins/NNE/NNEDenoiser/Source/NNEDenoiser/Private/NNEDenoiserDump.h` (Private)


#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace NNEDenoiser` (scope `UE`)
- L10 _namespace_ `namespace Private` (scope `UE::NNEDenoiser`)
- L13 _prototype_ `FString GetDefaultDumpPath();` (scope `UE::NNEDenoiser::Private`)
- L15 _prototype_ `void ScheduleDumpBuffer(FRDGBuilder& GraphBuilder, FRDGBufferRef Buffer, const FString& Name, const FString& FilePath = FString());` (scope `UE::NNEDenoiser::Private`)
- L19 _macro_ `#define NNEDENOISER_DUMP_BUFFERS_SCHEDULE(GraphBuilder, Buffers, Prefix) \`
- L25 _macro_ `#define NNEDENOISER_DUMP_BUFFERS_SCHEDULE(GraphBuilder, Buffers, Prefix)`

### `Plugins/NNE/NNEDenoiser/Source/NNEDenoiser/Private/NNEDenoiserGenericDenoiser.h` (Private)


#### class `UE::NNEDenoiser::Private::FGenericDenoiser`  
`class FGenericDenoiser`  
_L24-65_
- L27 _public prototype_ `FGenericDenoiser( TUniquePtr<IModelInstance> ModelInstance, TUniquePtr<IInputProcess> InputProcess, TUniquePtr<IOutputProcess> OutputProcess, FParameters DenoiserParameters, TUniquePtr<IAutoExposure> AutoExposure, TSharedPtr<ITransferFunction> TransferFunction );`
- L36 _public prototype_ `~FGenericDenoiser();`
- L39 _public function_ `const TCHAR* GetDebugName() const` — IPathTracingSpatialTemporalDenoiser interface
- L41 _public prototype_ `TUniquePtr<FHistory> AddPasses( FRDGBuilder &GraphBuilder, FRDGTextureRef ColorTex, FRDGTextureRef AlbedoTex, FRDGTextureRef NormalTex, FRDGTextureRef OutputTex, FRDGTextureRef FlowTex, const FRHIGPUMask& GPUMask, FHistory* History);`
- L52 _private prototype_ `bool Prepare(FIntPoint Extent);`
- L54 _private member_ `inline static const FString DebugName = TEXT("FGe`
- L56 _private member_ `TUniquePtr<IModelInstance> ModelInstance;`
- L57 _private member_ `TUniquePtr<IInputProcess> InputProcess;`
- L58 _private member_ `TUniquePtr<IOutputProcess> OutputProcess;`
- L59 _private member_ `FParameters DenoiserParameters;`
- L60 _private member_ `TUniquePtr<IAutoExposure> AutoExposure;`
- L61 _private member_ `TSharedPtr<ITransferFunction> TransferFunction;`
- L63 _private member_ `FIntPoint LastExtent = { -1, -1 };`
- L64 _private member_ `FTiling Tiling{};`

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace NNEDenoiser` (scope `UE`)
- L14 _namespace_ `namespace Private` (scope `UE::NNEDenoiser`)

### `Plugins/NNE/NNEDenoiser/Source/NNEDenoiser/Private/NNEDenoiserHistory.h` (Private)


#### class `UE::NNEDenoiser::Private::FHistory`  
`class FHistory : public IPathTracingSpatialTemporalDenoiser::IHistory`  
_L18-34_
- inherits: `IPathTracingSpatialTemporalDenoiser::IHistory`
- L21 _public function_ `FHistory(const TCHAR* DebugName, TMap<EResourceName, TArray<TRefCountPtr<IPooledRenderTarget>>> ResourceMap) : DebugName(DebugName), ResourceMap(MoveTemp(ResourceMap))`
- L25 _public prototype_ `virtual ~FHistory() = default;`
- L27 _public function_ `const TCHAR* GetDebugName() const override`
- L29 _public function_ `const TMap<EResourceName, TArray<TRefCountPtr<IPooledRenderTarget>>>& GetResourceMap() const`
- L32 _private member_ `const TCHAR* DebugName;`
- L33 _private member_ `TMap<EResourceName, TArray<TRefCountPtr<IPooledRenderTarget>>> ResourceMap;`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace NNEDenoiser` (scope `UE`)
- L13 _namespace_ `namespace Private` (scope `UE::NNEDenoiser`)

### `Plugins/NNE/NNEDenoiser/Source/NNEDenoiser/Private/NNEDenoiserIOProcess.h` (Private)


#### class `UE::NNEDenoiser::Private::IResourceAccess`  
`class IResourceAccess`  
_L15-20_
- L18 _public prototype_ `virtual FRDGTextureRef GetTexture(EResourceName TensorName, int32 FrameIdx) const = 0;`
- L19 _public prototype_ `virtual FRDGTextureRef GetIntermediateTexture(EResourceName TensorName, int32 FrameIdx) const = 0;`

#### class `UE::NNEDenoiser::Private::IInputProcess`  
`class IInputProcess`  
_L22-39_
- L25 _public prototype_ `virtual ~IInputProcess() = default;`
- L27 _public prototype_ `virtual bool Validate(const IModelInstance& ModelInstance, FIntPoint Extent) const = 0;`
- L29 _public prototype_ `virtual bool Prepare(IModelInstance& ModelInstance, FIntPoint Extent) const = 0;`
- L31 _public prototype_ `virtual int32 NumFrames(EResourceName Name) const = 0;`
- L33 _public prototype_ `virtual void AddPasses( FRDGBuilder& GraphBuilder, TConstArrayView<UE::NNE::FTensorDesc> TensorDescs, TConstArrayView<UE::NNE::FTensorShape> TensorShapes, const IResourceAccess& ResourceAccess, TConstArrayView<FRDGBufferRef> OutputBuffers) const = 0;`

#### class `UE::NNEDenoiser::Private::IOutputProcess`  
`class IOutputProcess`  
_L41-55_
- L44 _public prototype_ `virtual ~IOutputProcess() = default;`
- L46 _public prototype_ `virtual bool Validate(const IModelInstance& ModelInstance, FIntPoint Extent) const = 0;`
- L48 _public prototype_ `virtual void AddPasses( FRDGBuilder& GraphBuilder, TConstArrayView<UE::NNE::FTensorDesc> TensorDescs, TConstArrayView<UE::NNE::FTensorShape> TensorShapes, const IResourceAccess& ResourceAccess, TConstArrayView<FRDGBufferRef> Buffers, FRDGTextureRef OutputTexture) const = 0;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace NNEDenoiser` (scope `UE`)
- L9 _namespace_ `namespace Private` (scope `UE::NNEDenoiser`)

### `Plugins/NNE/NNEDenoiser/Source/NNEDenoiser/Private/NNEDenoiserIOProcessBase.h` (Private)


#### class `UE::NNEDenoiser::Private::FInputProcessBase`  
`class FInputProcessBase : public IInputProcess`  
_L13-57_
- inherits: `IInputProcess`
- L16 _public function_ `FInputProcessBase(FResourceMappingList InputLayout, TSharedPtr<ITransferFunction> TransferFunction) : InputLayout(InputLayout), TransferFunction(TransferFunction)`
- L21 _public prototype_ `virtual ~FInputProcessBase() = default;`
- L23 _public prototype_ `virtual bool Validate(const IModelInstance& ModelInstance, FIntPoint Extent) const override;`
- L25 _public prototype_ `virtual bool Prepare(IModelInstance& ModelInstance, FIntPoint Extent) const override;`
- L27 _public prototype_ `virtual int32 NumFrames(EResourceName Name) const override;`
- L29 _public prototype_ `void AddPasses( FRDGBuilder& GraphBuilder, TConstArrayView<UE::NNE::FTensorDesc> TensorDescs, TConstArrayView<UE::NNE::FTensorShape> TensorShapes, const IResourceAccess& ResourceAccess, TConstArrayView<FRDGBufferRef> OutputBuffers) const override;`
- L37 _protected prototype_ `virtual bool HasPreprocessInput(EResourceName TensorName, int32 FrameIdx) const;`
- L39 _protected prototype_ `virtual void PreprocessInput( FRDGBuilder& GraphBuilder, FRDGTextureRef Texture, EResourceName TensorName, int32 FrameIdx, FRDGTextureRef PreprocessedTexture) const;`
- L46 _protected prototype_ `virtual void WriteInputBuffer( FRDGBuilder& GraphBuilder, const UE::NNE::FTensorDesc& TensorDesc, const UE::NNE::FTensorShape& TensorShape, const IResourceAccess& ResourceAccess, const FResourceMapping& ResourceMapping, FRDGBufferRef Buffer) const;`
- L55 _private member_ `FResourceMappingList InputLayout;`
- L56 _private member_ `TSharedPtr<ITransferFunction> TransferFunction;`

#### class `UE::NNEDenoiser::Private::FOutputProcessBase`  
`class FOutputProcessBase : public IOutputProcess`  
_L59-99_
- inherits: `IOutputProcess`
- L62 _public function_ `FOutputProcessBase(FResourceMappingList OutputLayout, TSharedPtr<ITransferFunction> TransferFunction) : OutputLayout(OutputLayout), TransferFunction(TransferFunction)`
- L67 _public prototype_ `virtual ~FOutputProcessBase() = default;`
- L69 _public prototype_ `virtual bool Validate(const IModelInstance& ModelInstance, FIntPoint Extent) const override;`
- L71 _public prototype_ `void AddPasses( FRDGBuilder& GraphBuilder, TConstArrayView<UE::NNE::FTensorDesc> TensorDescs, TConstArrayView<UE::NNE::FTensorShape> TensorShapes, const IResourceAccess& ResourceAccess, TConstArrayView<FRDGBufferRef> Buffers, FRDGTextureRef OutputTexture) const override;`
- L80 _protected prototype_ `virtual bool HasPostprocessOutput(EResourceName TensorName, int32 FrameIdx) const;`
- L82 _protected prototype_ `virtual void ReadOutputBuffer( FRDGBuilder& GraphBuilder, const UE::NNE::FTensorDesc& TensorDesc, const UE::NNE::FTensorShape& TensorShape, const IResourceAccess& ResourceAccess, FRDGBufferRef Buffer, const FResourceMapping& ResourceMapping, FRDGTextureRef Texture) const;`
- L91 _protected prototype_ `virtual void PostprocessOutput( FRDGBuilder& GraphBuilder, FRDGTextureRef Texture, FRDGTextureRef PostprocessedTexture) const;`
- L97 _private member_ `FResourceMappingList OutputLayout;`
- L98 _private member_ `TSharedPtr<ITransferFunction> TransferFunction;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace NNEDenoiser` (scope `UE`)
- L8 _namespace_ `namespace Private` (scope `UE::NNEDenoiser`)

### `Plugins/NNE/NNEDenoiser/Source/NNEDenoiser/Private/NNEDenoiserLog.h` (Private)


#### Free symbols / members of external scopes

- L8 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogNNEDenoiser, Log, All);`
- L8 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogNNEDenoiser, Log, All);`

### `Plugins/NNE/NNEDenoiser/Source/NNEDenoiser/Private/NNEDenoiserModelInstance.h` (Private)


#### class `UE::NNEDenoiser::Private::IModelInstance`  
`class IModelInstance : public NNE::IModelInstanceRDG`  
_L10-17_
- inherits: `NNE::IModelInstanceRDG`
- L13 _public typedef_ `using ESetInputTensorShapesStatus = NNE::IModelInstanceRDG::ESetInputTensorShapesStatus;`
- L14 _public typedef_ `using EEnqueueRDGStatus = NNE::IModelInstanceRDG::EEnqueueRDGStatus;`
- L16 _public prototype_ `virtual ~IModelInstance() = default;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace NNEDenoiser` (scope `UE`)
- L7 _namespace_ `namespace Private` (scope `UE::NNEDenoiser`)

### `Plugins/NNE/NNEDenoiser/Source/NNEDenoiser/Private/NNEDenoiserModelInstanceCPU.h` (Private)


#### class `UE::NNEDenoiser::Private::FModelInstanceCPU`  
`class FModelInstanceCPU : public IModelInstance`  
_L18-44_
- inherits: `IModelInstance`
- L21 _public prototype_ `explicit FModelInstanceCPU(TSharedRef<UE::NNE::IModelInstanceCPU> ModelInstance);`
- L23 _public prototype_ `static TUniquePtr<FModelInstanceCPU> Make(UNNEModelData& ModelData, const FString& RuntimeName);`
- L25 _public prototype_ `virtual ~FModelInstanceCPU();`
- L27 _public prototype_ `virtual TConstArrayView<NNE::FTensorDesc> GetInputTensorDescs() const override;`
- L29 _public prototype_ `virtual TConstArrayView<NNE::FTensorDesc> GetOutputTensorDescs() const override;`
- L31 _public prototype_ `virtual TConstArrayView<NNE::FTensorShape> GetInputTensorShapes() const override;`
- L33 _public prototype_ `virtual TConstArrayView<NNE::FTensorShape> GetOutputTensorShapes() const override;`
- L35 _public prototype_ `virtual ESetInputTensorShapesStatus SetInputTensorShapes(TConstArrayView<NNE::FTensorShape> InInputShapes) override;`
- L37 _public prototype_ `virtual EEnqueueRDGStatus EnqueueRDG(FRDGBuilder &GraphBuilder, TConstArrayView<NNE::FTensorBindingRDG> Inputs, TConstArrayView<NNE::FTensorBindingRDG> Outputs) override;`
- L40 _private member_ `TSharedRef<UE::NNE::IModelInstanceCPU> ModelInstance;`
- L42 _private member_ `TArray<TArray<uint8>> ScratchInputBuffers;`
- L43 _private member_ `TArray<TArray<uint8>> ScratchOutputBuffers;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace NNE` (scope `UE`)
- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace NNEDenoiser` (scope `UE`)
- L15 _namespace_ `namespace Private` (scope `UE::NNEDenoiser`)

### `Plugins/NNE/NNEDenoiser/Source/NNEDenoiser/Private/NNEDenoiserModelInstanceGPU.h` (Private)


#### class `UE::NNEDenoiser::Private::FModelInstanceGPU`  
`class FModelInstanceGPU : public IModelInstance`  
_L16-42_
- inherits: `IModelInstance`
- L19 _public prototype_ `explicit FModelInstanceGPU(TSharedRef<UE::NNE::IModelInstanceGPU> ModelInstance);`
- L21 _public prototype_ `static TUniquePtr<FModelInstanceGPU> Make(UNNEModelData& ModelData, const FString& RuntimeName);`
- L23 _public prototype_ `virtual ~FModelInstanceGPU();`
- L25 _public prototype_ `virtual TConstArrayView<NNE::FTensorDesc> GetInputTensorDescs() const override;`
- L27 _public prototype_ `virtual TConstArrayView<NNE::FTensorDesc> GetOutputTensorDescs() const override;`
- L29 _public prototype_ `virtual TConstArrayView<NNE::FTensorShape> GetInputTensorShapes() const override;`
- L31 _public prototype_ `virtual TConstArrayView<NNE::FTensorShape> GetOutputTensorShapes() const override;`
- L33 _public prototype_ `virtual ESetInputTensorShapesStatus SetInputTensorShapes(TConstArrayView<NNE::FTensorShape> InInputShapes) override;`
- L35 _public prototype_ `virtual EEnqueueRDGStatus EnqueueRDG(FRDGBuilder &GraphBuilder, TConstArrayView<NNE::FTensorBindingRDG> Inputs, TConstArrayView<NNE::FTensorBindingRDG> Outputs) override;`
- L38 _private member_ `TSharedRef<UE::NNE::IModelInstanceGPU> ModelInstance;`
- L40 _private member_ `TArray<TArray<uint8>> ScratchInputBuffers;`
- L41 _private member_ `TArray<TArray<uint8>> ScratchOutputBuffers;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace NNE` (scope `UE`)
- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace NNEDenoiser` (scope `UE`)
- L13 _namespace_ `namespace Private` (scope `UE::NNEDenoiser`)

### `Plugins/NNE/NNEDenoiser/Source/NNEDenoiser/Private/NNEDenoiserModelInstanceRDG.h` (Private)


#### class `UE::NNEDenoiser::Private::FModelInstanceRDG`  
`class FModelInstanceRDG : public IModelInstance`  
_L16-39_
- inherits: `IModelInstance`
- L19 _public prototype_ `explicit FModelInstanceRDG(TSharedRef<UE::NNE::IModelInstanceRDG> ModelInstance);`
- L21 _public prototype_ `static TUniquePtr<FModelInstanceRDG> Make(UNNEModelData& ModelData, const FString& RuntimeName);`
- L23 _public prototype_ `virtual ~FModelInstanceRDG();`
- L25 _public prototype_ `virtual TConstArrayView<NNE::FTensorDesc> GetInputTensorDescs() const override;`
- L27 _public prototype_ `virtual TConstArrayView<NNE::FTensorDesc> GetOutputTensorDescs() const override;`
- L29 _public prototype_ `virtual TConstArrayView<NNE::FTensorShape> GetInputTensorShapes() const override;`
- L31 _public prototype_ `virtual TConstArrayView<NNE::FTensorShape> GetOutputTensorShapes() const override;`
- L33 _public prototype_ `virtual ESetInputTensorShapesStatus SetInputTensorShapes(TConstArrayView<NNE::FTensorShape> InInputShapes) override;`
- L35 _public prototype_ `virtual EEnqueueRDGStatus EnqueueRDG(FRDGBuilder &GraphBuilder, TConstArrayView<NNE::FTensorBindingRDG> Inputs, TConstArrayView<NNE::FTensorBindingRDG> Outputs) override;`
- L38 _private member_ `TSharedRef<UE::NNE::IModelInstanceRDG> ModelInstance;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace NNE` (scope `UE`)
- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace NNEDenoiser` (scope `UE`)
- L13 _namespace_ `namespace Private` (scope `UE::NNEDenoiser`)

### `Plugins/NNE/NNEDenoiser/Source/NNEDenoiser/Private/NNEDenoiserParameters.h` (Private)


#### struct `UE::NNEDenoiser::Private::FParameters`  
`struct FParameters`  
_L10-21_
- L20 _public member_ `FTilingConfig TilingConfig{};`

#### struct `UE::NNEDenoiser::Private::FParameters::FTilingConfig`  
`struct FTilingConfig`  
_L12-18_
- L14 _public member_ `int32 Alignment = 1;`
- L15 _public member_ `int32 Overlap{};`
- L16 _public member_ `int32 MaxSize{};`
- L17 _public member_ `int32 MinSize = 1;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace NNEDenoiser` (scope `UE`)
- L7 _namespace_ `namespace Private` (scope `UE::NNEDenoiser`)

### `Plugins/NNE/NNEDenoiser/Source/NNEDenoiser/Private/NNEDenoiserPathTracingDenoiser.h` (Private)


#### class `UE::NNEDenoiser::Private::FPathTracingDenoiser`  
`class FPathTracingDenoiser final : public IPathTracingDenoiser`  
_L15-29_
- inherits: `IPathTracingDenoiser`
- L19 _public prototype_ `explicit FPathTracingDenoiser(TUniquePtr<FGenericDenoiser> Denoiser);`
- L21 _public prototype_ `~FPathTracingDenoiser() = default;`
- L23 _public function_ `bool NeedTextureCreateExtraFlags() const override`
- L25 _public prototype_ `void AddPasses(FRDGBuilder& GraphBuilder, const FSceneView& View, const FInputs& Inputs) const override;`
- L28 _private member_ `TUniquePtr<FGenericDenoiser> Denoiser;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace NNEDenoiser` (scope `UE`)
- L8 _namespace_ `namespace Private` (scope `UE::NNEDenoiser`)

### `Plugins/NNE/NNEDenoiser/Source/NNEDenoiser/Private/NNEDenoiserPathTracingSpatialTemporalDenoiser.h` (Private)


#### class `UE::NNEDenoiser::Private::FPathTracingSpatialTemporalDenoiser`  
`class FPathTracingSpatialTemporalDenoiser final : public IPathTracingSpatialTemporalDenoiser`  
_L15-33_
- inherits: `IPathTracingSpatialTemporalDenoiser`
- L18 _public prototype_ `explicit FPathTracingSpatialTemporalDenoiser(TUniquePtr<FGenericDenoiser> Denoiser);`
- L20 _public prototype_ `~FPathTracingSpatialTemporalDenoiser() = default;`
- L23 _public prototype_ `const TCHAR* GetDebugName() const override;` — IPathTracingSpatialTemporalDenoiser interface
- L25 _public function_ `bool NeedTextureCreateExtraFlags() const override`
- L27 _public prototype_ `FOutputs AddPasses(FRDGBuilder& GraphBuilder, const FSceneView& View, const FInputs& Inputs) const override;`
- L29 _public prototype_ `void AddMotionVectorPass(FRDGBuilder& GraphBuilder, const FSceneView& View, const FMotionVectorInputs& Inputs) const override;`
- L32 _private member_ `TUniquePtr<FGenericDenoiser> Denoiser;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace NNEDenoiser` (scope `UE`)
- L8 _namespace_ `namespace Private` (scope `UE::NNEDenoiser`)

### `Plugins/NNE/NNEDenoiser/Source/NNEDenoiser/Private/NNEDenoiserResourceManager.h` (Private)


#### class `UE::NNEDenoiser::Private::FResourceManager`  
`class FResourceManager`  
_L19-53_
- L22 _public function_ `FResourceManager(FRDGBuilder& GraphBuilder, FTiling Tiling, TMap<EResourceName, TArray<TRefCountPtr<IPooledRenderTarget>>> ResourceMap = {}) : GraphBuilder(GraphBuilder), Tiling(Tiling), ResourceMap(ResourceMap)`
- L28 _public prototype_ `void AddTexture(EResourceName Name, FRDGTextureRef Current, int32 NumFrames);`
- L30 _public prototype_ `void BeginTile(int32 TileIndex);`
- L31 _public prototype_ `void EndTile();`
- L33 _public prototype_ `FRDGTextureRef GetIntermediateTexture(EResourceName Name, int32 FrameIdx) const;`
- L35 _public function_ `FRDGTextureRef GetTexture(EResourceName Name, int32 FrameIdx) const`
- L40 _public prototype_ `TMap<EResourceName, TArray<TRefCountPtr<IPooledRenderTarget>>> MakeHistoryResourceMap();`
- L43 _private prototype_ `FRDGTextureRef GetTexture(EResourceName Name, int32 FrameIdx, bool bBaseTexture) const;`
- L45 _private member_ `FRDGBuilder& GraphBuilder;`
- L46 _private member_ `FTiling Tiling;`
- L47 _private member_ `TMap<EResourceName, TArray<TRefCountPtr<IPooledRenderTarget>>> ResourceMap;`
- L49 _private member_ `TMap<EResourceName, TArray<FRDGTextureRef>> TextureMap;`
- L50 _private member_ `TMap<EResourceName, TArray<FRDGTextureRef>> IntermediateTextureMap;`
- L52 _private member_ `int32 CurrentTileIdx = -1;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace NNE` (scope `UE`)
- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace NNEDenoiser` (scope `UE`)
- L16 _namespace_ `namespace Private` (scope `UE::NNEDenoiser`)

### `Plugins/NNE/NNEDenoiser/Source/NNEDenoiser/Private/NNEDenoiserResourceMapping.h` (Private)


#### struct `UE::NNEDenoiser::Private::FResourceInfo`  
`struct FResourceInfo`  
_L13-18_
- L15 _public member_ `EResourceName Name;`
- L16 _public member_ `int32 Channel;`
- L17 _public member_ `int32 Frame;`

#### struct `UE::NNEDenoiser::Private::FChannelMapping`  
`struct FChannelMapping`  
_L20-24_
- L22 _public member_ `int32 TensorChannel;`
- L23 _public member_ `int32 ResourceChannel;`

#### class `UE::NNEDenoiser::Private::FResourceMapping`  
`class FResourceMapping`  
_L29-54_
- desc: Resource mapping for one tensor: 0: ResourceInfo0 -> tensor channel 0 maps to channel ResourceInfo0.Channel of resource ResourceInfo0.Name from frame ResourceInfo0.Frame 1: ...
- L33 _public prototype_ `void Add(FResourceInfo Info);` — Add mapping from tensor channel Num()-1 to resource defined by 'Info'
- L36 _public prototype_ `FResourceInfo& Add_GetRef(FResourceInfo Info);` — Add mapping from tensor channel Num()-1 to resource defined by 'Info' and return reference to it
- L38 _public prototype_ `const FResourceInfo& GetChecked(int32 Channel) const;`
- L41 _public prototype_ `int32 Num() const;` — Number of mapped tensor channels
- L44 _public prototype_ `int32 NumFrames(EResourceName Name) const;` — Number of past frames affected by the mapping including current frame for resource 'Name'
- L47 _public prototype_ `bool HasResource(EResourceName Name) const;` — Does mapping use resource 'Name'
- L50 _public prototype_ `TMap<int32, TArray<FChannelMapping>> GetChannelMappingPerFrame(EResourceName Name) const;` — Get mapping from tensor channel to resource channel per frame for resource 'Name'
- L53 _private member_ `TArray<FResourceInfo> ChannelMapping;`

#### class `UE::NNEDenoiser::Private::FResourceMappingList`  
`class FResourceMappingList`  
_L59-91_
- desc: Resource mapping list for multiple tensors: 0: ResourceMapping0 -> tensor 0 maps to resources as defined by ResourceMapping0 1: ...
- L63 _public prototype_ `void Add(FResourceMapping ResourceMapping);` — Add resource mapping for tensor Num()-1
- L66 _public prototype_ `FResourceMapping& Add_GetRef(FResourceMapping ResourceMapping);` — Add resource mapping for tensor Num()-1 and return reference to it
- L68 _public prototype_ `const FResourceMapping* Get(int32 InputIndex) const;`
- L69 _public prototype_ `const FResourceMapping& GetChecked(int32 InputIndex) const;`
- L72 _public prototype_ `int32 Num() const;` — Number of mapped tensors
- L75 _public prototype_ `int32 NumChannels(int32 InputIndex) const;` — Number of mapped tensor channels for input tensor 'InputIndex'
- L78 _public prototype_ `int32 NumFrames(EResourceName Name) const;` — Number of past frames affected by the mapping including current frame for resource 'Name'
- L81 _public prototype_ `bool HasResource(EResourceName Name) const;` — Does mapping use resource 'Name'
- L84 _public prototype_ `bool HasResource(int32 InputIndex, EResourceName Name) const;` — Does mapping for tensor 'InputIndex' use resource 'Name'
- L87 _public prototype_ `TMap<int32, TArray<FChannelMapping>> GetChannelMappingPerFrame(int32 InputIndex, EResourceName Name) const;` — Get mapping from tensor channel to resource channel per frame for resource 'Name' and tensor 'InputIndex"
- L90 _private member_ `TArray<FResourceMapping> InputMapping;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace NNEDenoiser` (scope `UE`)
- L10 _namespace_ `namespace Private` (scope `UE::NNEDenoiser`)
- L95 _prototype_ `template<class RowStructType> FResourceMappingList MakeTensorLayout(UDataTable* DataTable);` (scope `UE::NNEDenoiser::Private`) — Helper method to make resource mapping list from data table asset using row struct 'RowStructType'

### `Plugins/NNE/NNEDenoiser/Source/NNEDenoiser/Private/NNEDenoiserTiling.h` (Private)


#### struct `UE::NNEDenoiser::Private::FTile`  
`struct FTile`  
_L14-21_
- L16 _public function_ `FTile(FIntPoint Position, FIntRect InputOffsets, FIntRect OutputOffsets) : Position(Position), InputOffsets(InputOffsets), OutputOffsets(OutputOffsets)`
- L18 _public member_ `FIntPoint Position;`
- L19 _public member_ `FIntRect InputOffsets;`
- L20 _public member_ `FIntRect OutputOffsets;`

#### struct `UE::NNEDenoiser::Private::FTiling`  
`struct FTiling`  
_L23-30_
- L25 _public prototype_ `FTiling() = default;`
- L27 _public member_ `FIntPoint TileSize;`
- L28 _public member_ `FIntPoint Count;`
- L29 _public member_ `TArray<FTile> Tiles;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace NNEDenoiser` (scope `UE`)
- L11 _namespace_ `namespace Private` (scope `UE::NNEDenoiser`)
- L32 _function_ `inline FTiling CreateTiling(FIntPoint TargetTileSize, FIntPoint MaxTileSize, FIntPoint MinTileSize, int32 TileAlignment, FIntPoint MinimumOverlap, FIntPoint Size)` (scope `UE::NNEDenoiser::Private`)
- L35 _function_ `` (scope `UE::NNEDenoiser::Private::CreateTiling`)

### `Plugins/NNE/NNEDenoiser/Source/NNEDenoiser/Private/NNEDenoiserTransferFunction.h` (Private)


#### class `UE::NNEDenoiser::Private::ITransferFunction`  
`class ITransferFunction`  
_L13-25_
- L16 _public prototype_ `virtual ~ITransferFunction() = default;`
- L18 _public prototype_ `virtual void Forward(TConstArrayView<FLinearColor> InputImage, float InputScale, TArray<FLinearColor>& OutputImage) const = 0;`
- L19 _public prototype_ `virtual void Inverse(TConstArrayView<FLinearColor> InputImage, float InvInputScale, TArray<FLinearColor>& OutputImage) const = 0;`
- L21 _public prototype_ `virtual void RDGSetInputScale(FRDGBufferRef InputScaleBuffer) = 0;`
- L23 _public prototype_ `virtual void RDGForward(FRDGBuilder& GraphBuilder, FRDGTextureRef InputTexture, FRDGTextureRef OutputTexture) const = 0;`
- L24 _public prototype_ `virtual void RDGInverse(FRDGBuilder& GraphBuilder, FRDGTextureRef InputTexture, FRDGTextureRef OutputTexture) const = 0;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace NNEDenoiser` (scope `UE`)
- L10 _namespace_ `namespace Private` (scope `UE::NNEDenoiser`)

### `Plugins/NNE/NNEDenoiser/Source/NNEDenoiser/Private/NNEDenoiserTransferFunctionOidn.h` (Private)


#### class `UE::NNEDenoiser::Private::Oidn::FTransferFunction`  
`class FTransferFunction : public ITransferFunction`  
_L10-28_
- inherits: `ITransferFunction`
- L13 _public prototype_ `FTransferFunction();`
- L14 _public prototype_ `virtual ~FTransferFunction() = default;`
- L16 _public prototype_ `virtual void Forward(TConstArrayView<FLinearColor> InputImage, float InputScale, TArray<FLinearColor>& OutputImage) const override;`
- L17 _public prototype_ `virtual void Inverse(TConstArrayView<FLinearColor> InputImage, float InvInputScale, TArray<FLinearColor>& OutputImage) const override;`
- L19 _public prototype_ `virtual void RDGSetInputScale(FRDGBufferRef InInputScaleBuffer) override;`
- L21 _public prototype_ `virtual void RDGForward(FRDGBuilder& GraphBuilder, FRDGTextureRef InputTexture, FRDGTextureRef OutputTexture) const override;`
- L22 _public prototype_ `virtual void RDGInverse(FRDGBuilder& GraphBuilder, FRDGTextureRef InputTexture, FRDGTextureRef OutputTexture) const override;`
- L25 _private member_ `float NormScale = 1.0f;`
- L26 _private member_ `float InvNormScale = 1.0f;`
- L27 _private member_ `FRDGBufferRef InputScaleBuffer{};`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace NNEDenoiser` (scope `UE`)
- L7 _namespace_ `namespace Private` (scope `UE::NNEDenoiser`)
- L7 _namespace_ `namespace Oidn` (scope `UE::NNEDenoiser::Private`)

### `Plugins/NNE/NNEDenoiser/Source/NNEDenoiser/Private/NNEDenoiserUtils.h` (Private)


#### Free symbols / members of external scopes

- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace NNEDenoiser` (scope `UE`)
- L14 _namespace_ `namespace Private` (scope `UE::NNEDenoiser`)
- L18 _function_ `template<typename Int, typename IntB> Int CeilDiv(Int a, IntB b)` (scope `UE::NNEDenoiser::Private`) — Returns ceil(a / b) for non-negative integers
- L25 _function_ `template<typename Int, typename IntB> Int RoundUp(Int a, IntB b)` (scope `UE::NNEDenoiser::Private`) — Returns a rounded up to multiple of b
- L31 _function_ `template<class IntType> bool IsTensorShapeValid(TConstArrayView<IntType> ShapeData, TConstArrayView<int32> RequiredShapeData, const FString& Label)` (scope `UE::NNEDenoiser::Private`)
- L54 _function_ `template <typename PixelType> void CopyTextureFromGPUToCPU(FRHICommandListImmediate& RHICmdList, FRHITexture* SrcTexture, FIntPoint Size, TArray<PixelType>& DstArray)` (scope `UE::NNEDenoiser::Private`)
- L76 _function_ `template <typename PixelType> void CopyTextureFromCPUToGPU(FRHICommandListImmediate& RHICmdList, const TArray<PixelType>& SrcArray, FIntPoint Size, FRHITexture* DstTexture)` (scope `UE::NNEDenoiser::Private`)
- L92 _function_ `template <typename ElementType> void CopyBufferFromGPUToCPU(FRHICommandListImmediate& RHICmdList, FRHIBuffer* SrcBuffer, int32 Count, TArray<ElementType>& DstArray)` (scope `UE::NNEDenoiser::Private`)
- L112 _function_ `template <typename ElementType> void CopyBufferFromCPUToGPU(FRHICommandListImmediate& RHICmdList, const TArray<ElementType>& SrcArray, int32 Count, FRHIBuffer* DstBuffer)` (scope `UE::NNEDenoiser::Private`)
- L124 _function_ `inline EPixelFormat GetBufferFormat(ENNETensorDataType TensorDataType)` (scope `UE::NNEDenoiser::Private`)
- L136 _function_ `inline UE::NNEDenoiserShaders::Internal::EDataType GetDenoiserShaderDataType(ENNETensorDataType TensorDataType)` (scope `UE::NNEDenoiser::Private`)
- L150 _function_ `inline UE::NNEDenoiserShaders::Internal::EDataType GetDenoiserShaderDataType(EPixelFormat Format)` (scope `UE::NNEDenoiser::Private`)

### `Plugins/NNE/NNEDenoiser/Source/NNEDenoiser/Private/NNEDenoiserViewExtension.h` (Private)


#### class `UE::NNEDenoiser::Private::FViewExtension`  
`class FViewExtension final : public FSceneViewExtensionBase`  
_L17-39_
- inherits: `FSceneViewExtensionBase`
- L20 _public prototype_ `FViewExtension(const FAutoRegister& AutoRegister);`
- L21 _public prototype_ `virtual ~FViewExtension();`
- L23 _public prototype_ `void BeginRenderViewFamily(FSceneViewFamily& InViewFamily) override;`
- L25 _public prototype_ `void PreRenderViewFamily_RenderThread(FRDGBuilder& GraphBuilder, FSceneViewFamily& InViewFamily) override;`
- L28 _private member_ `TUniquePtr<UE::Renderer::Private::IPathTracingDenoiser> DenoiserToSwap;`
- L29 _private member_ `TUniquePtr<UE::Renderer::Private::IPathTracingSpatialTemporalDenoiser> SpatialTemporalDenoiserToSwap;`
- L32 _private member_ `bool bIsActive = false;` — Cached settings and CVar values
- L33 _private member_ `int32 TimeoutCounter = 0;`
- L34 _private member_ `EDenoiserRuntimeType RuntimeType;`
- L35 _private member_ `FString RuntimeName;`
- L36 _private member_ `FString AssetName;`
- L37 _private member_ `FString TemporalAssetName;`
- L38 _private member_ `uint32 MaximumTileSizeOverride;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace Renderer` (scope `UE`)
- L8 _namespace_ `namespace Private` (scope `UE::Renderer`)
- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace NNEDenoiser` (scope `UE`)
- L14 _namespace_ `namespace Private` (scope `UE::NNEDenoiser`)

### `Plugins/NNE/NNEDenoiser/Source/NNEDenoiser/Public/NNEDenoiserAsset.h` (Public)


#### class `UNNEDenoiserAsset`  
`class UNNEDenoiserAsset : public UDataAsset`  
_L14-34_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UDataAsset`
- desc: Denoiser model data asset
- L21 _public member_ `TSoftObjectPtr<UNNEModelData> ModelData;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=NNEDenoiser)` — NNE model data
- L25 _public member_ `TSoftObjectPtr<UDataTable> InputMapping;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=NNEDenoiser, meta = (RequiredAssetDataTags = "RowStructure=/Script/NNEDenoiser.NNEDenoiserInputMappingData"))` — Input mapping table
- L29 _public member_ `TSoftObjectPtr<UDataTable> OutputMapping;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=NNEDenoiser, meta = (RequiredAssetDataTags = "RowStructure=/Script/NNEDenoiser.NNEDenoiserOutputMappingData"))` — Output mapping table
- L33 _public member_ `FTilingConfig TilingConfig{};` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=NNEDenoiser)` — Tiling configuration

### `Plugins/NNE/NNEDenoiser/Source/NNEDenoiser/Public/NNEDenoiserIOMappingData.h` (Public)


#### enum `EInputResourceName`  
`enum class EInputResourceName : uint8`  
_L12-18_
- reflection: `UENUM()`
- desc: An enum to represent resource names used for denoiser input mapping
- L14 _public enumerator_ `Color`
- L15 _public enumerator_ `Albedo`
- L16 _public enumerator_ `Normal`
- L17 _public enumerator_ `Output`

#### enum `EOutputResourceName`  
`enum class EOutputResourceName : uint8`  
_L22-25_
- reflection: `UENUM()`
- desc: An enum to represent resource names used for denoiser output mapping
- L24 _public enumerator_ `Output`

#### enum `ETemporalInputResourceName`  
`enum class ETemporalInputResourceName : uint8`  
_L29-36_
- reflection: `UENUM()`
- desc: An enum to represent resource names used for temporal denoiser input mapping
- L31 _public enumerator_ `Color`
- L32 _public enumerator_ `Albedo`
- L33 _public enumerator_ `Normal`
- L34 _public enumerator_ `Flow`
- L35 _public enumerator_ `Output`

#### enum `ETemporalOutputResourceName`  
`enum class ETemporalOutputResourceName : uint8`  
_L40-43_
- reflection: `UENUM()`
- desc: An enum to represent resource names used for temporal denoiser output mapping
- L42 _public enumerator_ `Output`

#### struct `FNNEDenoiserBaseMappingData`  
`struct FNNEDenoiserBaseMappingData : public FTableRowBase`  
_L47-63_
- reflection: `USTRUCT(BlueprintType)`
- inherits: `FTableRowBase`
- desc: Table row base for denoiser basic input and output mapping
- L54 _public member_ `int32 TensorIndex = 0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=NNEDenoiser)` — Input/output tensor index
- L58 _public member_ `int32 TensorChannel = 0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=NNEDenoiser)` — Input/output tensor channel
- L62 _public member_ `int32 ResourceChannel = 0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=NNEDenoiser)` — Resource channel

#### struct `FNNEDenoiserInputMappingData`  
`struct FNNEDenoiserInputMappingData : public FNNEDenoiserBaseMappingData`  
_L67-74_
- reflection: `USTRUCT(BlueprintType)`
- inherits: `FNNEDenoiserBaseMappingData`
- desc: Table row base for denoiser input mapping
- L73 _public member_ `EInputResourceName Resource = EInputResourceName::Color;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=NNEDenoiser)` — Mapped resource name

#### struct `FNNEDenoiserOutputMappingData`  
`struct FNNEDenoiserOutputMappingData : public FNNEDenoiserBaseMappingData`  
_L78-85_
- reflection: `USTRUCT(BlueprintType)`
- inherits: `FNNEDenoiserBaseMappingData`
- desc: Table row base for denoiser output mapping
- L84 _public member_ `EOutputResourceName Resource = EOutputResourceName::Output;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=NNEDenoiser)` — Mapped resource name

#### struct `FNNEDenoiserTemporalInputMappingData`  
`struct FNNEDenoiserTemporalInputMappingData : public FNNEDenoiserBaseMappingData`  
_L89-101_
- reflection: `USTRUCT(BlueprintType)`
- inherits: `FNNEDenoiserBaseMappingData`
- desc: Table row base for temporal denoiser input mapping
- L96 _public member_ `ETemporalInputResourceName Resource = ETemporalInputResourceName::Color;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=NNEDenoiser)` — Mapped resource name
- L100 _public member_ `int32 FrameIndex = 0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=NNEDenoiser)` — Resource frame index

#### struct `FNNEDenoiserTemporalOutputMappingData`  
`struct FNNEDenoiserTemporalOutputMappingData : public FNNEDenoiserBaseMappingData`  
_L105-112_
- reflection: `USTRUCT(BlueprintType)`
- inherits: `FNNEDenoiserBaseMappingData`
- desc: Table row base for temporal denoiser output mapping
- L111 _public member_ `ETemporalOutputResourceName Resource = ETemporalOutputResourceName::Output;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=NNEDenoiser)` — Mapped resource name

#### Free symbols / members of external scopes

- L114 _namespace_ `namespace UE`
- L114 _namespace_ `namespace NNEDenoiser` (scope `UE`)
- L117 _prototype_ `EResourceName ToResourceName(EInputResourceName Name);` (scope `UE::NNEDenoiser`)
- L118 _prototype_ `EResourceName ToResourceName(EOutputResourceName Name);` (scope `UE::NNEDenoiser`)
- L119 _prototype_ `EResourceName ToResourceName(ETemporalInputResourceName Name);` (scope `UE::NNEDenoiser`)
- L120 _prototype_ `EResourceName ToResourceName(ETemporalOutputResourceName Name);` (scope `UE::NNEDenoiser`)

### `Plugins/NNE/NNEDenoiser/Source/NNEDenoiser/Public/NNEDenoiserResourceName.h` (Public)


#### enum `EResourceName`  
`enum class EResourceName : uint8`  
_L9-16_
- reflection: `UENUM()`
- desc: An enum to represent resource names used for input and output mapping
- L11 _public enumerator_ `Color`
- L12 _public enumerator_ `Albedo`
- L13 _public enumerator_ `Normal`
- L14 _public enumerator_ `Flow`
- L15 _public enumerator_ `Output`

### `Plugins/NNE/NNEDenoiser/Source/NNEDenoiser/Public/NNEDenoiserSettings.h` (Public)


#### enum `EDenoiserRuntimeType`  
`enum EDenoiserRuntimeType : uint8`  
_L15-20_
- reflection: `UENUM()`
- desc: An enum to represent denoiser NNE runtime type
- L17 _public enumerator_ `CPU`
- L18 _public enumerator_ `GPU`
- L19 _public enumerator_ `RDG`

#### class `UNNEDenoiserSettings`  
`class UNNEDenoiserSettings : public UDeveloperSettingsBackedByCVars`  
_L24-52_
- reflection: `UCLASS(MinimalAPI, Config = Engine, meta = (DisplayName = "NNE Denoiser"))`
- inherits: `UDeveloperSettingsBackedByCVars`
- desc: Settings to select a NNE Denoiser and its runtime
- L29 _public prototype_ `UNNEDenoiserSettings();`
- L31 _public prototype_ `virtual void PostInitProperties() override;`
- L35 _public member_ `TSoftObjectPtr<UNNEDenoiserAsset> DenoiserAsset;` — `UPROPERTY(Config, EditAnywhere, Category = "NNE Denoiser", meta = (DisplayName = "Denoiser Asset", ToolTip = "Select the denoiser asset"))` — Denoiser asset data used to create a NNE Denoiser
- L38 _public member_ `TSoftObjectPtr<UNNEDenoiserTemporalAsset> TemporalDenoiserAsset;` — Temporal denoiser asset data used to create a NNE Denoiser (Currently not used and therefore "hidden")
- L42 _public member_ `int32 MaximumTileSizeOverride = -1;` — `UPROPERTY(Config, EditAnywhere, Category = "NNE Denoiser", meta = (DisplayName = "Maximum tile size override", ToolTip = "Override the maximum tile size given by the asset.\nSpecial values:\n -1 = Do not override"))` — Override the maximum tile size defined per asset, but be aware not to set it lower than the assets minimum tile size (This can reduce GPU memory usage for GPU and RDG backed denoisers).
- L47 _private member_ `TEnumAsByte<EDenoiserRuntimeType> RuntimeType;` — `UPROPERTY(Config, EditAnywhere, Category = "NNE Denoiser", meta = (DisplayName = "Runtime Type", ToolTip = "Select a Runtime type", ConsoleVariable = "NNEDenoiser.Runtime.Type"))` — Runtime type used to run the NNE Denoiser model. Backed by the console variable 'NNEDenoiser.Runtime.Type'.
- L51 _private member_ `FString RuntimeName;` — `UPROPERTY(Config, EditAnywhere, Category = "NNE Denoiser", meta = (DisplayName = "Runtime Name Override", ToolTip = "(Optional) Specify the Runtime name", ConsoleVariable = "NNEDenoiser.Runtime.Name"))` — Runtime name used to run the NNE Denoiser model. Backed by the console variable 'NNEDenoiser.Runtime.Name'.

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API NNEDENOISER_API`

### `Plugins/NNE/NNEDenoiser/Source/NNEDenoiser/Public/NNEDenoiserTemporalAsset.h` (Public)


#### class `UNNEDenoiserTemporalAsset`  
`class UNNEDenoiserTemporalAsset : public UDataAsset`  
_L14-34_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UDataAsset`
- desc: Denoiser model data asset
- L21 _public member_ `TSoftObjectPtr<UNNEModelData> ModelData;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=NNEDenoiser)` — NNE model data
- L25 _public member_ `TSoftObjectPtr<UDataTable> InputMapping;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=NNEDenoiser, meta = (RequiredAssetDataTags = "RowStructure=/Script/NNEDenoiser.NNEDenoiserTemporalInputMappingData"))` — Input mapping table
- L29 _public member_ `TSoftObjectPtr<UDataTable> OutputMapping;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=NNEDenoiser, meta = (RequiredAssetDataTags = "RowStructure=/Script/NNEDenoiser.NNEDenoiserTemporalOutputMappingData"))` — Output mapping table
- L33 _public member_ `FTilingConfig TilingConfig{};` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=NNEDenoiser)` — Tiling configuration

### `Plugins/NNE/NNEDenoiser/Source/NNEDenoiser/Public/NNEDenoiserTilingConfig.h` (Public)


#### struct `FTilingConfig`  
`struct FTilingConfig`  
_L9-28_
- reflection: `USTRUCT(BlueprintType)`
- desc: Tiling configuration for fixed and dynamic size models
- L15 _public member_ `int32 Alignment = 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=NNEDenoiser, meta = (DisplayName = "Size Alignment"))` — Tile size alignment (applies only to dynamic size models)
- L19 _public member_ `int32 Overlap = 0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=NNEDenoiser)` — Tile overlap
- L23 _public member_ `int32 MaxSize = 0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=NNEDenoiser)` — Maximum tile size (applies only to dynamic size models)
- L27 _public member_ `int32 MinSize = 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=NNEDenoiser)` — Minimum tile size (applies only to dynamic size models)
