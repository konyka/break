# Plugins / VertexDeltaModel

- module root: `Plugins/Animation/MLDeformer/VertexDeltaModel/Source/VertexDeltaModel`
- headers: 5; symbols: 109
- symbol kinds: class=9, function=14, member=35, namespace=4, prototype=47
- DynamicallyLoadedModuleNames: 
- PrivateDependencyModuleNames: ComputeFramework, CoreUObject, Engine, GeometryCache, MLDeformerFramework, NNE, NNERuntimeORT, OptimusCore, Projects, RHI, RenderCore
- PublicDependencyModuleNames: Core

### `Plugins/Animation/MLDeformer/VertexDeltaModel/Source/VertexDeltaModel/Public/VertexDeltaGraphDataInterface.h` (Public)


#### class `UVertexDeltaGraphDataInterface`  
`class UVertexDeltaGraphDataInterface : public UOptimusComputeDataInterface`  
_L29-54_
- reflection: `UCLASS(Category = ComputeFramework)`
- inherits: `UOptimusComputeDataInterface`
- desc: Compute Framework Data Interface for MLDefomer data.
- L36 _public prototype_ `virtual FString GetDisplayName() const override;` — UOptimusComputeDataInterface overrides.
- L37 _public prototype_ `virtual TArray<FOptimusCDIPinDefinition> GetPinDefinitions() const override;`
- L38 _public prototype_ `virtual TSubclassOf<UActorComponent> GetRequiredComponentClass() const override;`
- L42 _public function_ `TCHAR const* GetClassName() const override` — UComputeDataInterface overrides.
- L43 _public function_ `virtual bool CanSupportUnifiedDispatch() const override`
- L44 _public prototype_ `virtual void GetSupportedInputs(TArray<FShaderFunctionDefinition>& OutFunctions) const override;`
- L45 _public prototype_ `virtual void GetShaderParameters(TCHAR const* UID, FShaderParametersMetadataBuilder& InOutBuilder, FShaderParametersMetadataAllocations& InOutAllocations) const override;`
- L46 _public prototype_ `virtual TCHAR const* GetShaderVirtualPath() const override;`
- L47 _public prototype_ `virtual void GetShaderHash(FString& InOutKey) const override;`
- L48 _public prototype_ `virtual void GetHLSL(FString& OutHLSL, FString const& InDataInterfaceName) const override;`
- L49 _public prototype_ `virtual UComputeDataProvider* CreateDataProvider(TObjectPtr<UObject> InBinding, uint64 InInputMask, uint64 InOutputMask) const override;`
- L53 _private member_ `static TCHAR const* TemplateFilePath;`

#### class `UVertexDeltaGraphDataProvider`  
`class UVertexDeltaGraphDataProvider : public UComputeDataProvider`  
_L58-71_
- reflection: `UCLASS(BlueprintType, EditInlineNew, Category = ComputeFramework)`
- inherits: `UComputeDataProvider`
- desc: Compute Framework Data Provider for MLDeformer data.
- L66 _public member_ `TObjectPtr<UMLDeformerComponent> DeformerComponent = nullptr;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Binding)` — The deformer component that this data provider works on.
- L69 _public prototype_ `virtual FComputeDataProviderRenderProxy* GetRenderProxy() override;` — UComputeDataProvider overrides.

#### class `UE::VertexDeltaModel::FVertexDeltaGraphDataProviderProxy`  
`class FVertexDeltaGraphDataProviderProxy : public FComputeDataProviderRenderProxy`  
_L76-98_
- inherits: `FComputeDataProviderRenderProxy`
- desc: Compute Framework Data Provider Proxy for MLDeformer data.
- L80 _public prototype_ `FVertexDeltaGraphDataProviderProxy(UMLDeformerComponent* DeformerComponent);`
- L83 _public prototype_ `bool IsValid(FValidationData const& InValidationData) const override;` — FComputeDataProviderRenderProxy overrides.
- L84 _public prototype_ `void GatherDispatchData(FDispatchData const& InDispatchData) override;`
- L85 _public prototype_ `void AllocateResources(FRDGBuilder& GraphBuilder, FAllocationData const& InAllocationData) override;`
- L89 _protected member_ `FSceneInterface* SceneInterface = nullptr;`
- L90 _protected member_ `FPrimitiveComponentId ComponentId;`
- L91 _protected member_ `UE::NNE::IModelInstanceRDG* NNEModelInstanceRDG = nullptr;`
- L92 _protected member_ `UVertexDeltaModelInstance* VertexDeltaModelInstance = nullptr;`
- L93 _protected member_ `FRHIShaderResourceView* VertexMapBufferSRV = nullptr;`
- L94 _protected member_ `FRDGBuffer* Buffer = nullptr;`
- L95 _protected member_ `FRDGBufferSRV* BufferSRV = nullptr;`
- L96 _protected member_ `int32 NeuralNetworkInferenceHandle = -1;`
- L97 _protected member_ `float Weight = 1.0f;`

#### Free symbols / members of external scopes

- L73 _namespace_ `namespace UE`
- L73 _namespace_ `namespace VertexDeltaModel` (scope `UE`)

### `Plugins/Animation/MLDeformer/VertexDeltaModel/Source/VertexDeltaModel/Public/VertexDeltaGraphDebugDataInterface.h` (Public)


#### class `UDEPRECATED_VertexDeltaGraphDebugDataInterface`  
`class UDEPRECATED_VertexDeltaGraphDebugDataInterface : public UOptimusComputeDataInterface`  
_L26-51_
- reflection: `UCLASS(Deprecated, Category = ComputeFramework, meta = (DeprecationMessage = "Please use UMLDeformerGraphDebugDataInterface instead."))`
- inherits: `UOptimusComputeDataInterface`
- desc: Compute Framework Data Interface for MLDeformer debugging data. This interfaces to editor only data, and so will only give valid results in that context.
- L33 _public prototype_ `virtual FString GetDisplayName() const override;` — UOptimusComputeDataInterface overrides.
- L34 _public prototype_ `virtual TArray<FOptimusCDIPinDefinition> GetPinDefinitions() const override;`
- L35 _public prototype_ `virtual TSubclassOf<UActorComponent> GetRequiredComponentClass() const override;`
- L39 _public function_ `TCHAR const* GetClassName() const override` — UComputeDataInterface overrides.
- L40 _public function_ `virtual bool CanSupportUnifiedDispatch() const override`
- L41 _public prototype_ `virtual void GetSupportedInputs(TArray<FShaderFunctionDefinition>& OutFunctions) const override;`
- L42 _public prototype_ `virtual void GetShaderParameters(TCHAR const* UID, FShaderParametersMetadataBuilder& OutBuilder, FShaderParametersMetadataAllocations& InOutAllocations) const override;`
- L43 _public prototype_ `virtual TCHAR const* GetShaderVirtualPath() const override;`
- L44 _public prototype_ `virtual void GetShaderHash(FString& InOutKey) const override;`
- L45 _public prototype_ `virtual void GetHLSL(FString& OutHLSL, FString const& InDataInterfaceName) const override;`
- L46 _public prototype_ `virtual UComputeDataProvider* CreateDataProvider(TObjectPtr<UObject> InBinding, uint64 InInputMask, uint64 InOutputMask) const override;`
- L50 _private member_ `static TCHAR const* TemplateFilePath;`

#### class `UDEPRECATED_VertexDeltaGraphDebugDataProvider`  
`class UDEPRECATED_VertexDeltaGraphDebugDataProvider : public UComputeDataProvider`  
_L55-73_
- reflection: `UCLASS(Deprecated, BlueprintType, EditInlineNew, Category = ComputeFramework, meta = (DeprecationMessage = "Please use UMLDeformerGraphDebugDataProvider instead."))`
- inherits: `UComputeDataProvider`
- desc: Compute Framework Data Provider for MLDeformer debugging data.
- L61 _public function_ `virtual void Init()`
- L64 _public prototype_ `virtual FComputeDataProviderRenderProxy* GetRenderProxy() override;` — UComputeDataProvider overrides.
- L69 _public member_ `TObjectPtr<UMLDeformerComponent> DeformerComponent = nullptr;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Binding)`
- L72 _public member_ `TObjectPtr<UMLDeformerAsset> DeformerAsset = nullptr;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Binding)`

#### class `UE::VertexDeltaModel::FVertexDeltaGraphDebugDataProviderProxy`  
`class UE_DEPRECATED(5.2, "Please use UE::MLDeformer::FMLDeformerDebugDataProviderProxy instead.") FVertexDeltaGraphDebugDataProviderProxy : public FComputeDataProviderRenderProxy`  
_L79-106_
- inherits: `FComputeDataProviderRenderProxy`
- L83 _public prototype_ `FVertexDeltaGraphDebugDataProviderProxy(UMLDeformerComponent* DeformerComponent, UMLDeformerAsset* DeformerAsset, UDEPRECATED_VertexDeltaGraphDebugDataProvider* InProvider);`
- L85 _public prototype_ `virtual void HandleZeroGroundTruthPositions();`
- L88 _public prototype_ `bool IsValid(FValidationData const& InValidationData) const override;` — FComputeDataProviderRenderProxy overrides.
- L89 _public prototype_ `void AllocateResources(FRDGBuilder& GraphBuilder, FAllocationData const& InAllocationData) override;`
- L90 _public prototype_ `void GatherDispatchData(FDispatchData const& InDispatchData) override;`
- L93 _public function_ `TArray<FVector3f>& GetGroundTruthPositions()`
- L96 _protected member_ `TObjectPtr<UDEPRECATED_VertexDeltaGraphDebugDataProvider> Provider = nullptr;`
- L97 _protected member_ `FSceneInterface* SceneInterface = nullptr;`
- L98 _protected member_ `FPrimitiveComponentId ComponentId;`
- L99 _protected member_ `TArray<FVector3f> GroundTruthPositions;`
- L100 _protected member_ `FRHIShaderResourceView* VertexMapBufferSRV = nullptr;`
- L101 _protected member_ `FRDGBuffer* GroundTruthBuffer = nullptr;`
- L102 _protected member_ `FRDGBufferSRV* GroundTruthBufferSRV = nullptr;`
- L103 _protected member_ `int32 HeatMapMode = 0;`
- L104 _protected member_ `float HeatMapMax = 0.0f;`
- L105 _protected member_ `float GroundTruthLerp = 0.0f;`

#### Free symbols / members of external scopes

- L77 _namespace_ `namespace UE`
- L77 _namespace_ `namespace VertexDeltaModel` (scope `UE`)

### `Plugins/Animation/MLDeformer/VertexDeltaModel/Source/VertexDeltaModel/Public/VertexDeltaModel.h` (Public)


#### class `UVertexDeltaModel`  
`class UVertexDeltaModel : public UMLDeformerGeomCacheModel`  
_L23-80_
- reflection: `UCLASS()`
- inherits: `UMLDeformerGeomCacheModel`
- desc: The vertex delta model, which uses a GPU based neural network. This model acts more as an example of how to implement a model that only uses the GPU. It is not as efficient as the Neural Morph Model, even though that model runs on the CPU. Unlike the Neural Morph Model this Vertex Delta Model does not generate any morph targets. All the vertex deltas are directly output by the neural network. This buffer of output deltas remains on the GPU and is then used as input buffer directly inside an optimus deformer graph.
- L29 _public prototype_ `UVertexDeltaModel(const FObjectInitializer& ObjectInitializer);`
- L32 _public prototype_ `virtual void GetAssetRegistryTags(FAssetRegistryTagsContext Context) const override;` — UObject overrides.
- L36 _public function_ `virtual FString GetDisplayName() const override` — UMLDeformerModel overrides.
- L37 _public prototype_ `virtual UMLDeformerModelInstance* CreateModelInstance(UMLDeformerComponent* Component) override;`
- L38 _public function_ `virtual bool IsNeuralNetworkOnGPU() const override` — GPU neural network.
- L39 _public prototype_ `virtual FString GetDefaultDeformerGraphAssetPath() const override;`
- L40 _public prototype_ `virtual bool IsTrained() const override;`
- L44 _public function_ `int32 GetNumHiddenLayers() const`
- L45 _public function_ `int32 GetNumNeuronsPerLayer() const`
- L46 _public function_ `int32 GetNumIterations() const`
- L47 _public function_ `int32 GetBatchSize() const`
- L48 _public function_ `float GetLearningRate() const`
- L51 _public prototype_ `void SetNNEModelData(TObjectPtr<UNNEModelData> ModelData);`
- L52 _public function_ `const FString GetNNERuntimeName() const`
- L57 _public member_ `TObjectPtr<UNNEModelData> NNEModel;` — `UPROPERTY()` — The NNE neural network model.
- L62 _public member_ `int32 NumHiddenLayers = 3;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Training Settings", meta = (ClampMin = "1", ClampMax = "10"))` — The number of hidden layers that the neural network model will have.\nHigher numbers will slow down performance but can deal with more complex deformations.
- L66 _public member_ `int32 NumNeuronsPerLayer = 256;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Training Settings", meta = (ClampMin = "1"))` — The number of units/neurons per hidden layer. Higher numbers will slow down performance but allow for more complex mesh deformations.
- L70 _public member_ `int32 NumIterations = 10000;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Training Settings", meta = (ClampMin = "1"))` — The number of iterations to train the model for.
- L74 _public member_ `int32 BatchSize = 128;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Training Settings", meta = (ClampMin = "1"))` — The number of frames per batch when training the model.
- L78 _public member_ `float LearningRate = 0.001f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Training Settings", meta = (ClampMin = "0.000001", ClampMax = "1.0"))` — The learning rate used during the model training.

#### Free symbols / members of external scopes

- L11 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogVertexDeltaModel, Log, All);`

### `Plugins/Animation/MLDeformer/VertexDeltaModel/Source/VertexDeltaModel/Public/VertexDeltaModelInstance.h` (Public)


#### class `UVertexDeltaModelInstance`  
`class UVertexDeltaModelInstance : public UMLDeformerModelInstance`  
_L17-70_
- reflection: `UCLASS()`
- inherits: `UMLDeformerModelInstance`
- L24 _public prototype_ `virtual FString CheckCompatibility(USkeletalMeshComponent* InSkelMeshComponent, bool bLogIssues) override;` — UMLDeformerModelInstance overrides.
- L25 _public prototype_ `virtual bool IsValidForDataProvider() const override;`
- L26 _public prototype_ `virtual void Execute(float ModelWeight) override;`
- L27 _public prototype_ `virtual bool SetupInputs() override;`
- L30 _public prototype_ `UVertexDeltaModel* GetVertexDeltaModel() const;`
- L31 _public prototype_ `virtual void PostMLDeformerComponentInit() override;`
- L37 _public prototype_ `UE::NNE::IModelInstanceRDG* GetNNEModelInstanceRDG() const;` — Get the RDG Neural Network Model Instance @return The IModelInstanceRDG if successfully created, or nullptr
- L43 _public prototype_ `TRefCountPtr<FRDGPooledBuffer> GetOutputRDGBuffer() const;` — Get the output vertex delta buffer @return The FRDGBuffer for vertex deltas
- L49 _public prototype_ `bool GetRDGVertexBufferDesc(TConstArrayView<UE::NNE::FTensorDesc>& InOutputTensorDescs, FRDGBufferDesc& OutBufferDesc);` — Get the render graph buffer description required for the output of a neural network. Return false if a flat buffer is not appropriate @return True if the OutputTensorDescs can be represented by a flat float  FRDGBuffer
- L53 _private prototype_ `void CreateRDGBuffers(TConstArrayView<UE::NNE::FTensorDesc>& OutputTensorDescs);`
- L54 _private prototype_ `void CreateNNEModel();`
- L57 _private member_ `TRefCountPtr<FRDGPooledBuffer> RDGInputBuffer;` — Input Buffer for Joint Matrices / Curve Floats
- L60 _private member_ `TRefCountPtr<FRDGPooledBuffer> RDGVertexDeltaBuffer;` — Output Buffer for Vertex Deltas
- L63 _private member_ `TSharedPtr<UE::NNE::IModelInstanceRDG> ModelInstanceRDG;` — The NNE RDG Model
- L66 _private member_ `TArray<float> NNEInputTensorBuffer;` — The CPU Input Tensor Buffer
- L69 _private member_ `bool bNNECreationAttempted = false;` — Only attempt to create NNE Model once

### `Plugins/Animation/MLDeformer/VertexDeltaModel/Source/VertexDeltaModel/Public/VertexDeltaModelVizSettings.h` (Public)


#### class `UVertexDeltaModelVizSettings`  
`class UVertexDeltaModelVizSettings : public UMLDeformerGeomCacheVizSettings`  
_L17-21_
- reflection: `UCLASS()`
- inherits: `UMLDeformerGeomCacheVizSettings`
- desc: The vizualization settings specific to the the vertex delta model. This is inherited from the UMLDeformerGeomCacheVizSettings. We cannot directly use that as we have to register the detail customization using a unique class for our model. This is the reason why we just inherit a new class from it.
