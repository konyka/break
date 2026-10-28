# Plugins / NeuralPostProcessing

- module root: `Plugins/Experimental/NeuralRendering/Source/NeuralPostProcessing`
- headers: 3; symbols: 67
- symbol kinds: class=7, delegate=1, enum=2, enumerator=6, function=11, macro=1, member=13, namespace=1, prototype=24, typedef=1
- DynamicallyLoadedModuleNames: 
- PrivateDependencyModuleNames: CoreUObject, Engine, NNE, Projects, RHI, RenderCore, Renderer, Slate, SlateCore
- PublicDependencyModuleNames: Core

### `Plugins/Experimental/NeuralRendering/Source/NeuralPostProcessing/Private/NeuralPostProcessModelInstance.h` (Private)


#### class `UNeuralPostProcessModelInstance`  
`class UNeuralPostProcessModelInstance : public UObject`  
_L23-100_
- reflection: `UCLASS()`
- inherits: `UObject`
- L31 _public prototype_ `void Update(UNNEModelData* NNEModelData, FString RuntimeName);` — Engine thread If the model data and the Runtime name is different, recreate the model
- L34 _public prototype_ `void CreateRDGBuffers(class FRDGBuilder& GraphBuilder);` — Render thread functions
- L38 _public prototype_ `void CreateRDGBuffersIfNeeded(class FRDGBuilder& GraphBuilder, bool bForceCreate = false);` — Create the input and output buffer on demand useful to use multiple post processing material to read/write
- L40 _public prototype_ `void Execute(class FRDGBuilder& GraphBuilder);`
- L42 _public prototype_ `UE::NNE::FTensorShape GetResolvedInputTensorShape();`
- L44 _public prototype_ `UE::NNE::FTensorShape GetResolvedOutputTensorShape();`
- L47 _public prototype_ `FRDGBufferRef GetInputBuffer();` — TODO: different type support
- L48 _public prototype_ `FRDGBufferRef GetOutputBuffer();`
- L50 _public prototype_ `FRDGBufferRef GetTiledInputBuffer();`
- L51 _public prototype_ `FRDGBufferRef GetTiledOutputBuffer();`
- L53 _public function_ `void UpdateDispatchSize(int InDispatchSize)`
- L54 _public function_ `int GetDispatchSize() const`
- L55 _public function_ `void UpdateTileDimension(FIntPoint InTileDim)`
- L56 _public function_ `FIntPoint GetTileDimension() const`
- L57 _public function_ `void UpdateModelTileType(ENeuralModelTileType InTileType)`
- L58 _public function_ `ENeuralModelTileType GetModelTileType() const`
- L59 _public function_ `void UpdateTileOverlap(FIntPoint InTileOverlap)`
- L60 _public function_ `FIntPoint GetTileOverlap() const`
- L61 _public function_ `void UpdateTileOverlapResolveType(ETileOverlapResolveType InTileOverlapResolveType)`
- L62 _public function_ `ETileOverlapResolveType GetTileOverlapResolveType() const`
- L64 _public function_ `bool IsValid()`
- L66 _public prototype_ `bool ModifyInputShape(int Dim, int Size);`
- L69 _private prototype_ `void CreateDefaultNNEModel(UNNEModelData* NNEModelData, FString RuntimeName);`
- L72 _private member_ `FRDGBufferRef RDGInputBuffer;` — Input Buffer for neural post process network pass
- L75 _private member_ `FRDGBufferRef RDGOutputBuffer;` — Output Buffer for Neural post process network pass
- L78 _private member_ `FRDGBufferRef RDGTiledInputBuffer;` — Temporary buffers to emulate batchsize
- L80 _private member_ `FRDGBufferRef RDGTiledOutputBuffer;`
- L82 _private member_ `ENeuralModelTileType ModelTileSize;`
- L84 _private member_ `int DispatchSize = 1;`
- L85 _private member_ `FIntPoint TileDim = FIntPoint(1,1);`
- L88 _private member_ `TSharedPtr<UE::NNE::IModelInstanceRDG> ModelInstanceRDG;` — The NNE RDG Model
- L91 _private member_ `UE::NNE::FTensorShape ResolvedInputTensorShape;` — Resolved Input Tensorshape
- L94 _private member_ `UE::NNE::FTensorShape ResolvedOutputTensorShape;` — Output Tensorshape
- L96 _private member_ `FIntVector4 DimensionOverride;`
- L98 _private member_ `FIntPoint TileOverlap;`
- L99 _private member_ `ETileOverlapResolveType TileOverlapResolveType;`

#### Free symbols / members of external scopes

- L13 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogNeuralPostProcessing, Log, All);`
- L13 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogNeuralPostProcessing, Log, All);`
- L17 _prototype_ `TSharedPtr<UE::NNE::IModelInstanceRDG> CreateNNEModelInstance(UNNEModelData* NNEModelData, FString RuntimeName);` — Util functions

### `Plugins/Experimental/NeuralRendering/Source/NeuralPostProcessing/Private/NeuralPostProcessingCS.h` (Private)


#### class `NeuralPostProcessng::FNeuralPostProcessingBuildIndirectDispatchArgsCS`  
`class FNeuralPostProcessingBuildIndirectDispatchArgsCS : public FGlobalShader`  
_L22-37_
- inherits: `FGlobalShader`
- L25 _public prototype_ `DECLARE_GLOBAL_SHADER(FNeuralPostProcessingBuildIndirectDispatchArgsCS);`
- L26 _public prototype_ `SHADER_USE_PARAMETER_STRUCT(FNeuralPostProcessingBuildIndirectDispatchArgsCS, FGlobalShader) static void ModifyCompilationEnvironment(const FGlobalShaderPermutationParameters& Parameters, FShaderCompilerEnvironment& OutEnvironment);`
- L31 _public prototype_ `SHADER_PARAMETER_RDG_BUFFER_UAV(RWBuffer<uint>, RWIndirectDispatchArgsBuffer) SHADER_PARAMETER_RDG_BUFFER_SRV(Buffer<uint>, SourceType) SHADER_PARAMETER(FIntPoint, TargetDimension) END_SHADER_PARAMETER_STRUCT() static bool ShouldCompilePermutation(const FGlobalShaderPermutationParameters& Parameters);`

#### class `NeuralPostProcessng::FDownScaleTextureCS`  
`class FDownScaleTextureCS : public FGlobalShader`  
_L39-56_
- inherits: `FGlobalShader`
- L47 _public prototype_ `SHADER_PARAMETER_STRUCT(FNueralPostProcessInput, Source) SHADER_PARAMETER_SAMPLER(SamplerState, SourceTextureSampler) SHADER_PARAMETER(int32, TargetWidth) SHADER_PARAMETER(int32, TargetHeight) SHADER_PARAMETER_RDG_TEXTURE_UAV(RWTexture2D<float4>, TargetTexture) RDG_BUFFER_ACCESS(IndirectDispatchArgsBuffer, ERHIAccess::IndirectArgs) END_SHADER_PARAMETER_STRUCT() static void ModifyCompilationEnvironment(const FGlobalShaderPermutationParameters& InParameters, FShaderCompilerEnvironment& OutEnvironment);`

#### class `NeuralPostProcessng::FDownScaleTexture`  
`class FDownScaleTexture : public FGlobalShader`  
_L58-74_
- inherits: `FGlobalShader`
- L66 _public prototype_ `SHADER_PARAMETER_STRUCT(FNueralPostProcessInput, Source) SHADER_PARAMETER_SAMPLER(SamplerState, SourceTextureSampler) SHADER_PARAMETER(int32, TargetWidth) SHADER_PARAMETER(int32, TargetHeight) RENDER_TARGET_BINDING_SLOTS() END_SHADER_PARAMETER_STRUCT() static void ModifyCompilationEnvironment(const FGlobalShaderPermutationParameters& InParameters, FShaderCompilerEnvironment& OutEnvironment);`

#### class `NeuralPostProcessng::FUpscaleTexture`  
`class FUpscaleTexture :public FGlobalShader`  
_L76-90_
- inherits: `FGlobalShader`
- L82 _public prototype_ `SHADER_PARAMETER_RDG_TEXTURE(Texture2D<float4>, Source_Texture) SHADER_PARAMETER(int32, SourceWidth) SHADER_PARAMETER(int32, SourceHeight) SHADER_PARAMETER(FIntPoint,ViewportSize) RENDER_TARGET_BINDING_SLOTS() END_SHADER_PARAMETER_STRUCT() static void ModifyCompilationEnvironment(const FGlobalShaderPermutationParameters& InParameters, FShaderCompilerEnvironment& OutEnvironment);`

#### class `NeuralPostProcessng::FCopyBetweenTextureAndOverlappedTileBufferCS`  
`class FCopyBetweenTextureAndOverlappedTileBufferCS : public FGlobalShader`  
_L92-136_
- inherits: `FGlobalShader`
- L100 _public prototype_ `SHADER_PARAMETER(int32, SourceWidth) SHADER_PARAMETER(int32, SourceHeight) SHADER_PARAMETER_RDG_TEXTURE_UAV(RWTexture2D<float4>,RWSourceTexture) SHADER_PARAMETER_SAMPLER(SamplerState, SourceTextureSampler) SHADER_PARAMETER(int32, TargetOverlappedTileWidth) SHADER_PARAMETER(int32, TargetOverlappedTileHeight) SHADER_PARAMETER(FIntPoint, ViewTileDimension) SHADER_PARAMETER(FVector2f, TileOverlap) SHADER_PARAMETER(int32, NumOfChannel) SHADER_PARAMETER(int32, bVisualizeOverlap) SHADER_PARAMETER(float, OverlapVisualizeIntensity) SHADER_PARAMETER_RDG_BUFFER_UAV(RWBuffer<float4>, TargetBuffer) RDG_BUFFER_ACCESS(IndirectDispatchArgsBuffer, ERHIAccess::IndirectArgs) END_SHADER_PARAMETER_STRUCT() static void ModifyCompilationEnvironment(const FGlobalShaderPermutationParameters& InParameters, FShaderCompilerEnvironment& OutEnvironment);`
- L135 _public typedef_ `using FPermutationDomain = TShaderPermutationDomain<FDimensionCopyDirection, FDimensionOverlapResolveType>;`

#### enum `NeuralPostProcessng::FCopyBetweenTextureAndOverlappedTileBufferCS::EDirection`  
`enum class EDirection : uint32`  
_L119-124_
- L121 _public enumerator_ `ToOverlappedTiles`
- L122 _public enumerator_ `FromOverlappedTiles`
- L123 _public enumerator_ `MAX`

#### enum `NeuralPostProcessng::FCopyBetweenTextureAndOverlappedTileBufferCS::EOverlapResolveType`  
`enum class EOverlapResolveType : uint32`  
_L126-131_
- L128 _public enumerator_ `Ignore`
- L129 _public enumerator_ `Feathering`
- L130 _public enumerator_ `MAX`

#### Free symbols / members of external scopes

- L10 _macro_ `#define NEURAL_POST_PROCESSING_THREAD_GROUP_SIZE 32`
- L12 _namespace_ `namespace NeuralPostProcessng`
- L16 _prototype_ `SHADER_PARAMETER_STRUCT_INCLUDE(FScreenPassTextureViewportParameters, Viewport) SHADER_PARAMETER_RDG_TEXTURE(Texture2D, Texture) END_SHADER_PARAMETER_STRUCT() FNueralPostProcessInput GetNeuralPostProcessInput(FRDGTextureRef Texture, const FScreenPassTextureViewportParameters& ViewportParameters);` (scope `NeuralPostProcessng`)

### `Plugins/Experimental/NeuralRendering/Source/NeuralPostProcessing/Public/NeuralPostProcessing.h` (Public)


#### class `FNeuralPostProcessingModule`  
`class FNeuralPostProcessingModule : public IModuleInterface`  
_L8-15_
- inherits: `IModuleInterface`
- L13 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface implementation
- L14 _public prototype_ `virtual void ShutdownModule() override;`
