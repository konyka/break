# Plugins / NearestNeighborModel

- module root: `Plugins/Animation/MLDeformer/NearestNeighborModel/Source/NearestNeighborModel`
- headers: 8; symbols: 414
- symbol kinds: class=15, delegate=1, enum=2, enumerator=7, function=47, macro=5, member=110, namespace=13, prototype=205, struct=2, typedef=7
- DynamicallyLoadedModuleNames: 
- PrivateDependencyModuleNames: ComputeFramework, CoreUObject, Engine, GeometryCache, MLDeformerFramework, MeshDescription, NNE, NNERuntimeBasicCpu, OptimusCore, Projects, RHI, RenderCore, SkeletalMeshDescription
- PublicDependencyModuleNames: Core

### `Plugins/Animation/MLDeformer/NearestNeighborModel/Source/NearestNeighborModel/Private/NearestNeighborOptimizedNetwork.h` (Private)


#### struct `FNearestNeighborNetworkParameter`  
`struct UE_DEPRECATED(5.4, "Nearest Neighbor Network Parameter no longer used for inference.") FNearestNeighborNetworkParameter`  
_L19-28_
- reflection: `USTRUCT()`
- L24 _public member_ `TArray<float> Values;` — `UPROPERTY()`
- L27 _public member_ `TArray<int32> Shape;` — `UPROPERTY()`

#### class `UNearestNeighborNetworkLayer`  
`class UE_DEPRECATED(5.4, "Nearest Neighbor Network Layer no longer used for inference.") UNearestNeighborNetworkLayer : public UObject`  
_L31-49_
- reflection: `UCLASS()`
- inherits: `UObject`
- L38 _public member_ `int32 NumInputs = 0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MLDeformer")`
- L41 _public member_ `int32 NumOutputs = 0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MLDeformer")`
- L46 _public member_ `TArray<FNearestNeighborNetworkParameter> Parameters;` — `UPROPERTY()`

#### class `UNearestNeighborNetworkLayer_Gemm_Prelu`  
`class UE_DEPRECATED(5.4, "Nearest Neighbor Network Layer no longer used for inference.") UNearestNeighborNetworkLayer_Gemm_Prelu : public UNearestNeighborNetworkLayer`  
_L54-57_
- reflection: `UCLASS()`
- inherits: `UNearestNeighborNetworkLayer`

#### class `UNearestNeighborNetworkLayer_Gemm`  
`class UE_DEPRECATED(5.4, "Nearest Neighbor Network Layer no longer used for inference.") UNearestNeighborNetworkLayer_Gemm : public UNearestNeighborNetworkLayer`  
_L60-63_
- reflection: `UCLASS()`
- inherits: `UNearestNeighborNetworkLayer`

#### class `UNearestNeighborOptimizedNetwork`  
`class UNearestNeighborOptimizedNetwork : public UObject`  
_L72-165_
- reflection: `UCLASS()`
- inherits: `UObject`
- desc: The specialized neural network for the MLDeformerModel. This class is used to do inference at runtime at a higher performance than using UNeuralNetwork.
- L79 _public prototype_ `virtual void PostLoad() override;`
- L83 _public prototype_ `virtual void Empty();` — `UFUNCTION(BlueprintCallable, Category = "MLDeformer")` — Clear the network, getting rid of all layers.
- L91 _public prototype_ `virtual bool IsEmpty() const;` — Check if the network is empty or not. If it is empty, it means it hasn't been loaded, and cannot do anything. Empty means it has no inputs, outputs or weights. @return Returns true if empty, otherwise false is returned.
- L99 _public prototype_ `virtual bool Load(const FString& Filename);` — Load the network from a file on disk. When loading fails, the network will be emptied. @param Filename The file path to load from. @return Returns true when successfully loaded this model, otherwise false is returned.
- L105 _public prototype_ `virtual UNearestNeighborOptimizedNetworkInstance* CreateInstance(UObject* Parent = nullptr) const;` — Create an instance of this neural network. @return A pointer to the neural network instance.
- L112 _public prototype_ `virtual int32 GetNumInputs() const;` — Get the number of inputs, which is the number of floats the network takes as input. @result The number of input floats to the network.
- L118 _public prototype_ `virtual int32 GetNumOutputs() const;` — Get the number of outputs, which is the number of floats the network will output. @return The number of floats that the network outputs.
- L124 _public prototype_ `virtual void SetNumInputs(int32 InNumInputs);` — Sets the number of inputs, which is the number of floats the network takes as input. @param InNumInputs The number of input floats to the network.
- L130 _public prototype_ `virtual void SetNumOutputs(int32 InNumOutputs);` — Sets the number of outputs, which is the number of floats the network will output. @param InNumOutputs The number of floats that the network outputs.
- L136 _public prototype_ `UE::NNE::IModelCPU* GetModel() const;` — Get the Model. @return A pointer to the Model.
- L142 _protected member_ `TObjectPtr<UNNEModelData> ModelData;` — `UPROPERTY()` — The Model Data used for network
- L145 _protected member_ `TSharedPtr<UE::NNE::IModelCPU> Model;` — The Neural Network used.
- L148 _protected member_ `int32 NumInputs = 0;` — `UPROPERTY()`
- L151 _protected member_ `int32 NumOutputs = 0;` — `UPROPERTY()`
- L157 _protected member_ `TArray<TObjectPtr<UNearestNeighborNetworkLayer>> Layers_DEPRECATED;` — `UE_DEPRECATED(5.4, "Layers Object no longer available.")` — `UPROPERTY(meta = (DeprecatedProperty, DeprecationMessage = "Network format changed."))`
- L163 _private member_ `static const TCHAR* RuntimeName;`
- L164 _private member_ `static const TCHAR* RuntimeModuleName;`

#### class `UNearestNeighborOptimizedNetworkInstance`  
`class UNearestNeighborOptimizedNetworkInstance : public UObject`  
_L173-237_
- reflection: `UCLASS()`
- inherits: `UObject`
- desc: An instance of a UNearestNeighborOptimizedNetwork. The instance holds its own input and output buffers and only reads from the network object it was instanced from. This allows it to be multithreaded.
- L183 _public prototype_ `UNearestNeighborOptimizedNetworkInstance();` — These are required because of the use of TUniquePtr
- L184 _public prototype_ `UNearestNeighborOptimizedNetworkInstance(const FObjectInitializer& ObjectInitializer);`
- L185 _public prototype_ `UNearestNeighborOptimizedNetworkInstance(FVTableHelper& Helper);`
- L186 _public prototype_ `virtual ~UNearestNeighborOptimizedNetworkInstance();`
- L192 _public prototype_ `TArrayView<float> GetInputs();` — Get the network input buffer. @return The array view of floats that represents the network inputs.
- L193 _public prototype_ `TArrayView<const float> GetInputs() const;`
- L199 _public prototype_ `TArrayView<float> GetOutputs();` — Get the network output buffer. @return The array view of floats that represents the network outputs.
- L200 _public prototype_ `TArrayView<const float> GetOutputs() const;`
- L206 _public prototype_ `const UNearestNeighborOptimizedNetwork* GetNeuralNetwork() const;` — Get the neural network this is an instance of. @return A reference to the neural network.
- L213 _public prototype_ `virtual void Run();` — Run the neural network, performing inference. This will update the values in the output buffer that you can get with the GetOutputs method. This also assumes you have set all the right input values already.
- L222 _protected prototype_ `void Init(const UNearestNeighborOptimizedNetwork* InNeuralNetwork);` — Initialize this instance using a given network object. This is automatically called by the UNearestNeighborOptimizedNetwork::CreateInstance() method. @param InNeuralNetwork The network that this is an instance of.
- L226 _protected member_ `TArray<float> Inputs;` — The input values.
- L229 _protected member_ `TArray<float> Outputs;` — The output values.
- L232 _protected member_ `TSharedPtr<UE::NNE::IModelInstanceCPU> Instance;` — The instance data for this Network Instance.
- L236 _protected member_ `TObjectPtr<const UNearestNeighborOptimizedNetwork> Network;` — `UPROPERTY(Transient)` — The neural network this is an instance of.

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace NNE` (scope `UE`)

### `Plugins/Animation/MLDeformer/NearestNeighborModel/Source/NearestNeighborModel/Private/OptimusDataInterfaceSkeletonWithQuats.h` (Private)


#### class `UOptimusSkeletonWithQuatsDataInterface`  
`class UOptimusSkeletonWithQuatsDataInterface : public UOptimusComputeDataInterface`  
_L21-45_
- reflection: `UCLASS(MinimalAPI, Category = ComputeFramework)`
- inherits: `UOptimusComputeDataInterface`
- desc: Compute Framework Data Interface for skeletal data.
- L27 _public prototype_ `FString GetDisplayName() const override;`
- L28 _public prototype_ `TArray<FOptimusCDIPinDefinition> GetPinDefinitions() const override;`
- L29 _public prototype_ `TSubclassOf<UActorComponent> GetRequiredComponentClass() const override;`
- L33 _public function_ `TCHAR const* GetClassName() const override`
- L34 _public prototype_ `void GetSupportedInputs(TArray<FShaderFunctionDefinition>& OutFunctions) const override;`
- L35 _public prototype_ `void GetShaderParameters(TCHAR const* UID, FShaderParametersMetadataBuilder& InOutBuilder, FShaderParametersMetadataAllocations& InOutAllocations) const override;`
- L36 _public prototype_ `void GetPermutations(FComputeKernelPermutationVector& OutPermutationVector) const override;`
- L37 _public prototype_ `TCHAR const* GetShaderVirtualPath() const override;`
- L38 _public prototype_ `void GetShaderHash(FString& InOutKey) const override;`
- L39 _public prototype_ `void GetHLSL(FString& OutHLSL, FString const& InDataInterfaceName) const override;`
- L40 _public prototype_ `UComputeDataProvider* CreateDataProvider(TObjectPtr<UObject> InBinding, uint64 InInputMask, uint64 InOutputMask) const override;`
- L44 _private member_ `static TCHAR const* TemplateFilePath;`

#### class `UOptimusSkeletonWithQuatsDataProvider`  
`class UOptimusSkeletonWithQuatsDataProvider : public UComputeDataProvider`  
_L49-60_
- reflection: `UCLASS(BlueprintType, editinlinenew, Category = ComputeFramework)`
- inherits: `UComputeDataProvider`
- desc: Compute Framework Data Provider for reading skeletal mesh.
- L55 _public member_ `TObjectPtr<USkinnedMeshComponent> SkinnedMesh = nullptr;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Binding)`
- L58 _public prototype_ `FComputeDataProviderRenderProxy* GetRenderProxy() override;`

#### class `FOptimusSkeletonWithQuatsDataProviderProxy`  
`class FOptimusSkeletonWithQuatsDataProviderProxy : public FComputeDataProviderRenderProxy`  
_L62-83_
- inherits: `FComputeDataProviderRenderProxy`
- L65 _public prototype_ `FOptimusSkeletonWithQuatsDataProviderProxy(USkinnedMeshComponent* SkinnedMeshComponent);`
- L68 _public prototype_ `bool IsValid(FValidationData const& InValidationData) const override;`
- L69 _public prototype_ `void GatherPermutations(FPermutationData& InOutPermutationData) const override;`
- L70 _public prototype_ `void GatherDispatchData(FDispatchData const& InDispatchData) override;`
- L71 _public prototype_ `void AllocateResources(FRDGBuilder& GraphBuilder, FAllocationData const& InAllocationData) override;`
- L75 _private typedef_ `using FParameters = FSkeletonWithQuatsDataInterfaceParameters;`
- L76 _private prototype_ `void CacheRefToLocalQuats(TArray<FQuat4f>& OutRefToLocalQuats) const;`
- L78 _private member_ `FSceneInterface* SceneInterface = nullptr;`
- L79 _private member_ `FPrimitiveComponentId ComponentId;`
- L80 _private member_ `uint32 BoneRevisionNumber = 0;`
- L81 _private member_ `TArray<TArray<FQuat4f> > PerSectionRefToLocalQuats;`
- L82 _private member_ `TArray<FRDGBufferSRVRef> PerSectionRefToLocalQuatsSRVs;`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API NEARESTNEIGHBORMODEL_API`

### `Plugins/Animation/MLDeformer/NearestNeighborModel/Source/NearestNeighborModel/Public/NearestNeighborModel.h` (Public)


#### struct `FClothPartData`  
`struct UE_DEPRECATED(5.4, "FClothPartData is deprecated. Use UNearestNeighborModelSection instead.") FClothPartData`  
_L27-73_
- reflection: `USTRUCT(BlueprintType, Blueprintable)`
- L33 _public member_ `int32 PCACoeffNum = 128;` — `UPROPERTY()` — Number of PCA coefficients for this cloth part.
- L37 _public member_ `uint32 PCACoeffStart = 0;` — `UPROPERTY()` — The start index of PCA coeffcients of this cloth part
- L41 _public member_ `uint32 NumVertices = 0;` — `UPROPERTY()` — Number of vertices in this cloth part
- L45 _public member_ `uint32 NumNeighbors = 0;` — `UPROPERTY()` — Number of neighbors used for this cloth part
- L49 _public member_ `TArray<uint32> VertexMap;` — `UPROPERTY()` — Vertex indices for this cloth part
- L53 _public member_ `TArray<float> PCABasis;` — `UPROPERTY()` — PCA basis for this cloth part. This is a flattened array of size (PCACoeffNum, NumVertices * 3)
- L57 _public member_ `TArray<float> VertexMean;` — `UPROPERTY()` — Vertex mean for PCA computation. This has the size of NumVertices * 3
- L61 _public member_ `TArray<float> AssetNeighborCoeffs;` — `UPROPERTY()` — PCA coefficients of the nearest neighbors. This is a flattened array of size (NumNeighbors, PCACoeffNum)
- L65 _public member_ `TArray<float> AssetNeighborOffsets;` — `UPROPERTY()` — The remaining offsets of the nearest neighbor shapes (after reducing PCA offsets). This is a flattened array of size (NumNeighbors, PCACoeffNum)
- L69 _public member_ `TArray<int32> AssetNeighborIndexMap;` — `UPROPERTY()` — Mapping from NeighborCoeffs to AssetNeighborCoeffs
- L72 _public member_ `TArray<float> NeighborCoeffs;` — `UPROPERTY()`

#### enum `ENearestNeighborModelSectionWeightMapCreationMethod`  
`enum class ENearestNeighborModelSectionWeightMapCreationMethod : uint8`  
_L77-87_
- reflection: `UENUM()`
- L80 _public enumerator_ `FromText` — Include all vertices from text with weight 1.
- L82 _public enumerator_ `SelectedBones` — Use skinning weights from selected bones.
- L84 _public enumerator_ `VertexAttributes` — Use weights from a vertex attribute.
- L86 _public enumerator_ `ExternalTxt` — Using an external .txt file

#### class `UNearestNeighborModelSection`  
`class UNearestNeighborModelSection : public UObject`  
_L99-320_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject`
- desc: The section of the nearest neighbor model. Each section contains a set of vertices in the original skeletal mesh. The nearest neighbor search is performed on each section separately. For example, if a character asset has both shirt and pants mesh, user can define sperate two separate sections for shirt and pants, and the nearest neighbor search will be performed separately on those two sections.
- L104 _public prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FPropertyChangedDelegate, FPropertyChangedEvent&, UNearestNeighborModelSection&);`
- L105 _public typedef_ `using EOpFlag = UE::NearestNeighborModel::EOpFlag;`
- L108 _public prototype_ `int32 GetNumBasis() const;` — `UFUNCTION(BlueprintPure, Category = "Section")`
- L110 _public prototype_ `int32 GetNumVertices() const;`
- L111 _public prototype_ `int32 GetRuntimeNumNeighbors() const;`
- L113 _public prototype_ `bool IsReadyForTraining() const;`
- L114 _public prototype_ `bool IsReadyForInference() const;`
- L116 _public prototype_ `const TArray<float>& GetNeighborCoeffs() const;`
- L119 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L121 _public prototype_ `void SetNumBasis(const int32 InNumBasis);`
- L124 _public prototype_ `int32 GetAssetNumNeighbors() const;` — `UFUNCTION(BlueprintPure, Category = "Section")`
- L126 _public prototype_ `const UAnimSequence* GetNeighborPoses() const;`
- L127 _public prototype_ `const UGeometryCache* GetNeighborMeshes() const;`
- L129 _public prototype_ `UAnimSequence* GetMutableNeighborPoses() const;` — Avoid mutable getters. Changing NeighborPoses or NeighborMeshes may cause unexpected errors.
- L130 _public prototype_ `UGeometryCache* GetMutableNeighborMeshes() const;`
- L132 _public prototype_ `void SetVertexMapString(const FString& InString);`
- L134 _public prototype_ `int32 GetMeshIndex() const;`
- L135 _public prototype_ `void SetMeshIndex(int32 Index);`
- L138 _public prototype_ `const TArray<int32>& GetVertexMap() const;` — `UFUNCTION(BlueprintPure, Category = "Section")`
- L141 _public prototype_ `const TArray<float>& GetVertexWeights() const;` — `UFUNCTION(BlueprintPure, Category = "Section")`
- L144 _public prototype_ `const TArray<float>& GetBasis() const;` — `UFUNCTION(BlueprintPure, Category = "Section")`
- L147 _public prototype_ `const TArray<float>& GetVertexMean() const;` — `UFUNCTION(BlueprintPure, Category = "Section")`
- L150 _public prototype_ `const TArray<float>& GetAssetNeighborCoeffs() const;` — `UFUNCTION(BlueprintPure, Category = "Section")`
- L153 _public prototype_ `bool DoesUsePCA() const;` — `UFUNCTION(BlueprintPure, Category = "Section")`
- L155 _public prototype_ `const TArray<float>& GetAssetNeighborOffsets() const;`
- L156 _public prototype_ `const TArray<int32>& GetExcludedFrames() const;`
- L157 _public prototype_ `const TArray<int32>& GetAssetNeighborIndexMap() const;`
- L159 _public prototype_ `FMLDeformerGeomCacheTrainingInputAnim* GetInputAnim() const;`
- L161 _public prototype_ `EOpFlag UpdateVertexWeights();`
- L163 _public prototype_ `EOpFlag UpdateForTraining();`
- L164 _public prototype_ `EOpFlag UpdateForInference();`
- L165 _public prototype_ `void InvalidateTraining();`
- L166 _public prototype_ `void InvalidateInference();`
- L168 _public prototype_ `bool UpdateRuntimeNeighbors();`
- L169 _public prototype_ `bool GetRuntimeNeighborOffsets(TArray<float>& OutNeighborOffsets) const;`
- L171 _public prototype_ `void SetModel(UNearestNeighborModel* InModel);`
- L172 _public prototype_ `const UNearestNeighborModel* GetModel() const;`
- L174 _public prototype_ `ENearestNeighborModelSectionWeightMapCreationMethod GetWeightMapCreationMethod() const;`
- L175 _public prototype_ `FString GetBoneNamesString() const;`
- L176 _public prototype_ `const TArray<FName>& GetBoneNames() const;`
- L177 _public prototype_ `void SetBoneNames(const TArray<FName>& InBoneNames);`
- L178 _public prototype_ `FString GetExternalTxtFile() const;`
- L179 _public prototype_ `void SetExternalTxtFile(const FString& InFile);`
- L183 _public prototype_ `EOpFlag NormalizeVertexWeights();` — Do not call this function directly. Call UNearestNeighborModel::NormalizeVertexWeights() instead.
- L185 _public prototype_ `void ClearReferences();`
- L186 _public prototype_ `void FinalizeMorphTargets();`
- L189 _public function_ `static FName GetNumBasisPropertyName()`
- L190 _public function_ `static FName GetVertexMapStringPropertyName()`
- L191 _public function_ `static FName GetNeighborPosesPropertyName()`
- L192 _public function_ `static FName GetNeighborMeshesPropertyName()`
- L193 _public function_ `static FName GetExcludedFramesPropertyName()`
- L194 _public function_ `static FName GetWeightMapCreationMethodPropertyName()`
- L195 _public function_ `static FName GetAttributeNamePropertyName()`
- L196 _public function_ `static FName GetExternalTxtFilePropertyName()`
- L202 _protected member_ `TObjectPtr<UAnimSequence> NeighborPoses;` — `UPROPERTY(EditAnywhere, Category = "Section", meta = (DisplayName = "Neighbor Sequence"))` — Poses of the nearest neighbor ROM.
- L206 _protected member_ `TObjectPtr<UGeometryCache> NeighborMeshes;` — `UPROPERTY(EditAnywhere, Category = "Section", meta = (DisplayName = "Neighbor Geom Cache"))` — Geometry cache of the nearest neighbor ROM.
- L210 _protected member_ `ENearestNeighborModelSectionWeightMapCreationMethod WeightMapCreationMethod = ENearestNeighborModelSectionWeightMapCreationMethod::FromText;` — `UPROPERTY(EditAnywhere, Category = "Section")` — Method to create weight map for this section.
- L214 _protected member_ `TArray<FName> BoneNames;` — `UPROPERTY()` — Bone names used to create weight map.
- L218 _protected member_ `FName AttributeName;` — `UPROPERTY(EditAnywhere, Category = "Section", meta = (GetOptions = "GetVertexAttributeNames", NoResetToDefault))` — A float vertex attribute that is used to compute weight maps
- L222 _protected member_ `FString VertexMapString;` — `UPROPERTY(EditAnywhere, Category = "Section", meta = (DisplayName = "Vertex Indices"))` — A string containing vertex indices for this section, e.g. "2, 3, 5-8, 9, 11-20"
- L226 _protected member_ `FString ExternalTxtFile;` — `UPROPERTY(VisibleAnywhere, Category = "Section")` — The path to the txt file containing vertex weights. The number of lines equals to the number of vertices in skeletal mesh with each line being a float for vertex weight.
- L230 _protected member_ `TArray<int32> ExcludedFrames;` — `UPROPERTY(EditAnywhere, Category = "Section")` — Frames to be excluded from the nearest neighbor ROM
- L234 _protected member_ `int32 MeshIndex = 0;` — `UPROPERTY()` — The mesh index in SkeletalMeshRenderData
- L238 _protected member_ `TObjectPtr<UNearestNeighborModel> Model = nullptr;` — `UPROPERTY()` — The parent nearest neighbor model
- L242 _protected member_ `TArray<int32> VertexMap;` — `UPROPERTY()` — Vertex indices for this section. VertexMap.Num() == NumVertices
- L246 _protected member_ `TArray<float> VertexWeights;` — `UPROPERTY()` — The vertex weights for this section. VertexWeights.Num() == NumVertices.
- L250 _protected member_ `TArray<float> Basis;` — `UPROPERTY()` — Flattened array of basis. The shape of basis is (CoeffNum, NumVertices * 3)
- L254 _protected member_ `TArray<float> VertexMean;` — `UPROPERTY()` — The vertex mean on the shape. This array has a size of NumVertices * 3
- L258 _protected member_ `TArray<float> AssetNeighborCoeffs;` — `UPROPERTY()` — Flattened array of neighbor coefficients before excluding frames. The shape of this array is (NumNeighbors, NumCoeffs)
- L262 _protected member_ `TArray<float> AssetNeighborOffsets;` — `UPROPERTY()` — Flattened array of neighbor offsets before excluding frames. The shape of this array is (NumNeighbors, NumVertices * 3)
- L266 _protected member_ `TArray<int32> AssetNeighborIndexMap;` — `UPROPERTY()` — The index into the original nearest neighbor ROM asset after frames are excluded.
- L271 _protected member_ `int32 NumPCACoeffs = 64;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "1", DefaultValue = "64", EditCondition = "DoesUsePCA()"), Category = "Section", DisplayName = "Num Basis")` — Number of PCA coefficients for this section.
- L275 _protected member_ `int32 NumVertices = 0;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Section Private")` — Number of vertices in this section
- L279 _protected member_ `int32 RuntimeNumNeighbors = 0;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Section Private")` — Number of neighbors in this section after excluding frames
- L283 _protected member_ `TArray<float> RuntimeNeighborCoeffs;` — `UPROPERTY()` — Flattened array of neighbor offsets after excluding frames.
- L288 _private member_ `bool bIsReadyForTraining = false;` — `UPROPERTY()` — Whether the section is ready for training
- L292 _private member_ `bool bIsReadyForInference = false;` — `UPROPERTY()` — Whether the section is ready for inference
- L295 _private prototype_ `bool IsBasisValid() const;`
- L296 _private prototype_ `bool IsBasisEmpty() const;`
- L297 _private prototype_ `bool IsNearestNeighborValid() const;`
- L298 _private prototype_ `bool IsNearestNeighborEmpty() const;`
- L301 _private prototype_ `void SetBasisData(const TArray<float>& InVertexMean, const TArray<float>& InBasis);` — `UFUNCTION(BlueprintCallable, Category = "Section")`
- L304 _private prototype_ `void SetNeighborData(const TArray<float>& InNeighborCoeffs, const TArray<float>& InNeighborOffsets);` — `UFUNCTION(BlueprintCallable, Category = "Section")`
- L306 _private prototype_ `void Reset();`
- L307 _private prototype_ `void ResetBasisData();`
- L308 _private prototype_ `void ResetNearestNeighborData();`
- L309 _private prototype_ `EOpFlag UpdateVertexWeightsFromText();`
- L310 _private prototype_ `EOpFlag UpdateVertexWeightsSelectedBones();`
- L311 _private prototype_ `EOpFlag UpdateVertexWeightsVertexAttributes();`
- L312 _private prototype_ `EOpFlag UpdateVertexWeightsExternalTxt();`
- L315 _private prototype_ `TArray<FName> GetVertexAttributeNames() const;` — `UFUNCTION()`
- L318 _private member_ `mutable TUniquePtr<FMLDeformerGeomCacheTrainingInputAnim> InputAnim;` — A temporary InputAnim used by GetInputAnim() function.

#### class `UNearestNeighborModel`  
`class UNearestNeighborModel : public UMLDeformerMorphModel`  
_L335-681_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMLDeformerMorphModel`
- desc: The nearest neighbor model. This model contains the linear basis of the vertex deltas and a small set of meshes for nearest neighbor search. Given a new pose, the pre-trained neural network first predicts the coefficients of the vertex deltas. Then this model uses the predicted coeffcients to find a nearest neighbor in the small dataset. The total vertex delta is computed by vertex_delta = mean_delta + basis * coeff + nearest_neighbor_delta To prevent popping, a time filtering is applied on predicted vertex deltas. The vertex delta at time t is computed by vertex_delta(t) = decay_factor * vertex_delta(t-1) + (1 - decay_factor) * vertex_delta The mesh can be separated into several sections (e.g. shirt, pants...). The nearest neighbor search is carried out separately for each section. The basis and the nearest neighbor data are compressed into morph targets.
- L341 _public typedef_ `using FSection = UNearestNeighborModelSection;`
- L342 _public typedef_ `using UNetwork = UNearestNeighborOptimizedNetwork;`
- L344 _public prototype_ `UNearestNeighborModel(const FObjectInitializer& ObjectInitializer);`
- L347 _public prototype_ `virtual void GetAssetRegistryTags(FAssetRegistryTagsContext Context) const override;` — UObject overrides.
- L349 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L350 _public prototype_ `virtual void PostEditChangeChainProperty(FPropertyChangedChainEvent& PropertyChangedEvent) override;`
- L351 _public prototype_ `virtual void FinalizeMorphTargets() override;`
- L356 _public prototype_ `virtual void PostLoad() override;` — UMLDeformerModel overrides.
- L357 _public prototype_ `virtual void Serialize(FArchive& Archive) override;`
- L358 _public prototype_ `virtual UMLDeformerModelInstance* CreateModelInstance(UMLDeformerComponent* Component) override;`
- L359 _public prototype_ `virtual UMLDeformerInputInfo* CreateInputInfo() override;`
- L360 _public prototype_ `virtual FString GetDisplayName() const override;`
- L361 _public function_ `virtual int32 GetNumFloatsPerBone() const override`
- L362 _public function_ `virtual int32 GetNumFloatsPerCurve() const override`
- L363 _public prototype_ `virtual bool IsTrained() const override;`
- L364 _public prototype_ `virtual FString GetDefaultDeformerGraphAssetPath() const;`
- L368 _public prototype_ `int32 GetNumSections() const;` — `UFUNCTION(BlueprintPure, Category = "Nearest Neighbor Model")`
- L372 _public prototype_ `const UNearestNeighborModelSection* GetSectionPtr(int32 Index) const;` — `UFUNCTION(BlueprintPure, Category = "Python")` — GetSectionPtr is reserved for python. Use GetSection for C++.
- L373 _public prototype_ `const UNearestNeighborModelSection& GetSection(int32 Index) const;`
- L374 _public prototype_ `UNearestNeighborModelSection& GetSection(int32 Index);`
- L377 _public prototype_ `const TArray<int32>& GetPCACoeffStarts() const;` — `UFUNCTION(BlueprintPure, Category = "Nearest Neighbor Model")`
- L380 _public prototype_ `int32 GetTotalNumBasis() const;` — `UFUNCTION(BlueprintPure, Category = "Nearest Neighbor Model")`
- L381 _public prototype_ `int32 GetNumBasisPerSection() const;`
- L383 _public prototype_ `int32 GetTotalNumNeighbors() const;`
- L384 _public prototype_ `float GetDecayFactor() const;`
- L385 _public prototype_ `float GetNearestNeighborOffsetWeight() const;`
- L387 _public prototype_ `TWeakObjectPtr<const UNetwork> GetOptimizedNetwork() const;`
- L388 _public prototype_ `int32 GetNumNetworkOutputs() const;`
- L389 _public prototype_ `void ClipInputs(TArrayView<float> Inputs) const;`
- L392 _public prototype_ `bool IsReadyForTraining() const;` — `UFUNCTION(BlueprintPure, Category = "Nearest Neighbor Model")`
- L395 _public prototype_ `bool IsReadyForInference() const;` — `UFUNCTION(BlueprintPure, Category = "Nearest Neighbor Model")`
- L397 _public prototype_ `bool DoesUseRBF() const;`
- L398 _public prototype_ `float GetRBFSigma() const;`
- L401 _public function_ `bool DoesUsePCA() const` — `UFUNCTION(BlueprintPure, Category = "Nearest Neighbor Model")`
- L404 _public prototype_ `TArray<FInt32Range> GetMeshVertRanges(const USkeletalMesh& SkelMesh);`
- L409 _public function_ `int32 GetInputDim() const` — `UFUNCTION(BlueprintPure, Category = "Nearest Neighbor Model")`
- L412 _public function_ `TArray<int32> GetHiddenLayerDims() const` — `UFUNCTION(BlueprintPure, Category = "Nearest Neighbor Model")`
- L415 _public function_ `int32 GetOutputDim() const` — `UFUNCTION(BlueprintPure, Category = "Nearest Neighbor Model")`
- L419 _public function_ `int32 GetNumEpochs() const` — `UE_DEPRECATED(5.5, "GetNumEpochs() is deprecated.")` — `UFUNCTION(meta = (DeprecatedFunction, DeprecationMessage = "GetNumEpochs has been deprecated. Convert from GetNumIterations instead."))`
- L422 _public function_ `int32 GetNumIterations() const` — `UFUNCTION(BlueprintPure, Category = "Nearest Neighbor Model")`
- L425 _public function_ `int32 GetBatchSize() const` — `UFUNCTION(BlueprintPure, Category = "Nearest Neighbor Model")`
- L428 _public function_ `float GetLearningRate() const` — `UFUNCTION(BlueprintPure, Category = "Nearest Neighbor Model")`
- L431 _public function_ `int32 GetEarlyStopEpochs() const` — `UFUNCTION(BlueprintPure, Category = "Nearest Neighbor Model")`
- L434 _public function_ `float GetRegularizationFactor() const` — `UFUNCTION(BlueprintPure, Category = "Nearest Neighbor Model")`
- L437 _public function_ `float GetSmoothLossBeta() const` — `UFUNCTION(BlueprintPure, Category = "Nearest Neighbor Model")`
- L440 _public prototype_ `FString GetModelDir() const;` — `UFUNCTION(BlueprintPure, Category = "Nearest Neighbor Model")`
- L442 _public function_ `bool DoesUseFileCache() const`
- L443 _public function_ `bool DoesUseDualQuaternionDeltas() const`
- L445 _public prototype_ `FDateTime GetNetworkLastWriteTime() const;`
- L446 _public prototype_ `FString GetNetworkLastWriteArchitectureString() const;`
- L447 _public prototype_ `FDateTime GetMorphTargetsLastWriteTime() const;`
- L450 _public prototype_ `TArray<FString> GetCachedDeltasPaths() const;` — `UFUNCTION(BlueprintPure, Category = "Nearest Neighbor Model")`
- L453 _public prototype_ `TArray<FString> GetCachedPCAPaths() const;` — `UFUNCTION(BlueprintPure, Category = "Nearest Neighbor Model")`
- L456 _public prototype_ `TArray<FString> GetCachedNetworkPaths() const;` — `UFUNCTION(BlueprintPure, Category = "Nearest Neighbor Model")`
- L458 _public prototype_ `TOptional<FDateTime> GetCachedDeltasTimestamp() const;`
- L459 _public prototype_ `TOptional<FDateTime> GetCachedPCATimestamp() const;`
- L460 _public prototype_ `TOptional<FDateTime> GetCachedNetworkTimestamp() const;`
- L462 _public typedef_ `using EOpFlag = UE::NearestNeighborModel::EOpFlag;`
- L463 _public prototype_ `EOpFlag UpdateForTraining();`
- L464 _public prototype_ `void InvalidateTraining();`
- L465 _public prototype_ `void InvalidateTrainingModelOnly();`
- L466 _public prototype_ `EOpFlag UpdateForInference();`
- L467 _public prototype_ `void InvalidateInference();`
- L468 _public prototype_ `void InvalidateInferenceModelOnly();`
- L469 _public prototype_ `bool LoadOptimizedNetworkFromFile(const FString& Filename);`
- L470 _public prototype_ `void ClearOptimizedNetwork();`
- L471 _public prototype_ `void RemoveAllSections();`
- L473 _public prototype_ `FMLDeformerGeomCacheTrainingInputAnim* GetNearestNeighborAnim(int32 SectionIndex);`
- L474 _public prototype_ `const FMLDeformerGeomCacheTrainingInputAnim* GetNearestNeighborAnim(int32 SectionIndex) const;`
- L476 _public function_ `void AddSection(TObjectPtr<UNearestNeighborModelSection> Section)`
- L478 _public prototype_ `void UpdateFileCache();`
- L479 _public prototype_ `const FString& GetFileCacheDirectory() const;`
- L480 _public prototype_ `void SetFileCacheDirectory(const FString& InFileCacheDirectory);`
- L484 _public prototype_ `void UpdateMorphTargetsLastWriteTime();` — Make sure to call this function after changing the morph targets. Do not call this function without calling InitEngineMorphTargets first.
- L486 _public prototype_ `void UpdateNetworkInputDim();`
- L487 _public prototype_ `void UpdateNetworkOutputDim();`
- L489 _public prototype_ `void ClearReferences();`
- L491 _public prototype_ `bool IsBeforeCustomVersionWasAdded() const;`
- L492 _public prototype_ `bool IsBeforeTrainedBasisAdded() const;`
- L493 _public prototype_ `bool IsBeforeDeprecateNumEpochs() const;`
- L494 _public prototype_ `const TArray<float>& GetVertexWeightSum() const;`
- L496 _public function_ `static FName GetInputDimPropertyName()`
- L497 _public function_ `static FName GetHiddenLayerDimsPropertyName()`
- L498 _public function_ `static FName GetOutputDimPropertyName()`
- L499 _public function_ `static FName GetNumIterationsPropertyName()`
- L500 _public function_ `static FName GetBatchSizePropertyName()`
- L501 _public function_ `static FName GetLearningRatePropertyName()`
- L502 _public function_ `static FName GetEarlyStopEpochsPropertyName()`
- L503 _public function_ `static FName GetSectionsPropertyName()`
- L504 _public function_ `static FName GetNearestNeighborOffsetWeightPropertyName()`
- L505 _public function_ `static FName GetUseFileCachePropertyName()`
- L506 _public function_ `static FName GetFileCacheDirectoryPropertyName()`
- L507 _public function_ `static FName GetUsePCAPropertyName()`
- L508 _public function_ `static FName GetNumBasisPerSectionPropertyName()`
- L509 _public function_ `static FName GetUseDualQuaternionDeltasPropertyName()`
- L510 _public function_ `static FName GetDecayFactorPropertyName()`
- L511 _public function_ `static FName GetUseRBFPropertyName()`
- L512 _public function_ `static FName GetRBFSigmaPropertyName()`
- L518 _protected member_ `int32 InputDim = 0;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Training Settings")` — Network input dimensions.
- L522 _protected member_ `int32 OutputDim = 0;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Training Settings")` — Network output dimensions.
- L527 _protected member_ `TArray<int32> HiddenLayerDims;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Training Settings")` — Dimension of hidden layers in the network. This cannot be empty.
- L532 _protected member_ `int32 NumEpochs_DEPRECATED = 2500;` — `UE_DEPRECATED(5.5, "NumEpochs is deprecated. Convert to NumIterations instead.")` — `UPROPERTY(meta = (DeprecatedProperty, DeprecationMessage = "NumEpochs is deprecated. Convert to NumIterations instead.", ClampMin = "1"))` — Max number of cycles iterated through the training set.
- L536 _protected member_ `int32 NumIterations = 5000;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Training Settings", meta = (ClampMin = "1", ClampMax = "1000000"))` — The number of iterations to train the model for.
- L540 _protected member_ `int32 BatchSize = 256;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Training Settings", AdvancedDisplay, meta = (ClampMin = "1"))` — Number of data samples processed together as a group in a single pass.
- L544 _protected member_ `float RegularizationFactor = 1.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Training Settings", AdvancedDisplay, meta = (ClampMin = "0", EditCondition = "!bUsePCA"))` — The regularization factor. Higher values can help generate more sparse morph targets, but can also lead to visual artifacts.
- L548 _protected member_ `float SmoothLossBeta = 1.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, AdvancedDisplay, Category = "Training Settings", meta = (ClampMin = "0.0", EditCondition = "!bUsePCA"))` — The beta parameter in the smooth L1 loss function, which describes below which absolute error to use a squared term. If the error is above or equal to this beta value, it will use the L1 loss.
- L552 _protected member_ `float LearningRate = 0.001f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Training Settings", AdvancedDisplay, meta = (ClampMin = "0.000001", ClampMax = "1.0"))` — The size of the step when optimizing the network.
- L556 _protected member_ `int32 EarlyStopEpochs = 100;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Training Settings", AdvancedDisplay, meta = (ClampMin = "1", EditCondition = "bUsePCA"))` — The number of epochs to stop training if there is no improvement in accuracy.
- L560 _protected member_ `bool bUseFileCache = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "File Cache", meta = (DisplayName = "Use File Cache (Advanced)"))` — Whether to cache intermediate results on disk. CAUTION: failing to manually clear caches could cause unexpected results.
- L564 _protected member_ `FString FileCacheDirectory = FPaths::ProjectIntermediateDir() + "Ne` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "File Cache", meta = (EditCondition = "bUseFileCache", EditConditionHides))` — Directory to save the intermediate results.
- L566 _protected member_ `TOptional<FDateTime> CachedDeltasTimestamp;`
- L567 _protected member_ `TOptional<FDateTime> CachedPCATimestamp;`
- L568 _protected member_ `TOptional<FDateTime> CachedNetworkTimestamp;`
- L573 _protected member_ `TArray<FClothPartData> ClothPartData_DEPRECATED;` — `UE_DEPRECATED(5.4, "ClothPartData is deprecated. Use Sections instead.")` — `UPROPERTY()`
- L577 _protected member_ `static constexpr int32 NearestNeighborNumFloatsPerBone = 3;`
- L578 _protected member_ `static constexpr int32 NearestNeighborNumFloatsPerCurve = 0;`
- L582 _protected member_ `bool bUseInputMultipliers = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Debugging")` — Whether to use input multipliers. This can be used to debug bad network input.
- L586 _protected member_ `TArray<FVector3f> InputMultipliers;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Debugging")` — Values to be multiplied to the input. This can be used to debug bad network input.
- L590 _protected member_ `TArray<float> InputsMin;` — `UPROPERTY(BlueprintReadWrite, Category = "Network IO")` — The min input values observed throughout the entire training set. This is used to clamp the input value at inference time.  The values are set in python.
- L594 _protected member_ `TArray<float> InputsMax;` — `UPROPERTY(BlueprintReadWrite, Category = "Network IO")` — The max input values observed throughout the entire training set. This is used to clamp the input value at inference time.  The values are set in python.
- L598 _protected member_ `bool bUsePCA = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Nearest Neighbor Settings")` — Whether to use pre-computed PCA basis. If false, basis will be learned at training time.
- L602 _protected member_ `int32 NumBasisPerSection = 128;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Nearest Neighbor Settings", meta = (EditCondition = "!bUsePCA", EditConditionHides))` — The number of basis used in each section.
- L606 _protected member_ `bool bUseDualQuaternionDeltas = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Nearest Neighbor Settings")` — Whether to use dual quaternion deltas. If false, LBS deltas will be used.
- L610 _protected member_ `float DecayFactor = 0.85f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Nearest Neighbor Settings", META = (ClampMin = "0", ClampMax = "1"))` — The ratio of previous frame deltas added into the current frame deltas. A bigger value will make wrinkles "stick" longer.
- L614 _protected member_ `float NearestNeighborOffsetWeight = 1.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Nearest Neighbor Settings", META = (ClampMin = "0", ClampMax = "1"))` — The weight multiplied to nearest neighbor deltas. A value of 0 means completely removing nearest neighbor deltas.
- L618 _protected member_ `bool bUseRBF = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Nearest Neighbor Settings")` — Whether to use radial basis function to blend multiple nearest neighbors to produce smoother result.
- L622 _protected member_ `float RBFSigma = 1.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Nearest Neighbor Settings", META = (ClampMin = "0"))` — Range to blend nearest neighbors. A bigger range will blend more neighbors, produce smoother result and may be slower in game.
- L626 _public prototype_ `UNearestNeighborModelSection* OnSectionAdded(int32 NewIndex);`
- L630 _private prototype_ `TWeakObjectPtr<UNetwork> GetOptimizedNetwork();`
- L634 _private prototype_ `void SetOptimizedNetwork(UNearestNeighborOptimizedNetwork* InOptimizedNetwork);`
- L636 _private prototype_ `void UpdatePCACoeffStarts();`
- L638 _private prototype_ `EOpFlag CheckHiddenLayerDims();`
- L639 _private prototype_ `void UpdateInputMultipliers();`
- L641 _private prototype_ `void UpdateSectionNumBasis();`
- L642 _private prototype_ `void UpdateCachedDeltasTimestamp();`
- L643 _private prototype_ `void UpdateCachedPCATimestamp();`
- L644 _private prototype_ `void UpdateCachedNetworkTimestamp();`
- L646 _private prototype_ `void NormalizeVertexWeights();`
- L647 _private prototype_ `void UpdateVersion();`
- L653 _private member_ `TArray<TObjectPtr<UNearestNeighborModelSection>> Sections;` — `UPROPERTY(EditAnywhere, Category = "Mesh Sections")`
- L656 _private member_ `TArray<int32> PCACoeffStarts;` — `UPROPERTY()`
- L659 _private member_ `bool bIsReadyForTraining = false;` — `UPROPERTY()`
- L662 _private member_ `bool bIsReadyForInference = false;` — `UPROPERTY()`
- L665 _private member_ `TObjectPtr<UNearestNeighborOptimizedNetwork> OptimizedNetwork;` — `UPROPERTY()`
- L667 _private member_ `int32 Version = INDEX_NONE;`
- L671 _private member_ `int64 NetworkLastWriteTime = 0;` — `UPROPERTY()`
- L674 _private member_ `int64 MorphTargetsLastWriteTime = 0;` — `UPROPERTY()`
- L677 _private member_ `FString NetworkLastWriteArchitectureString;` — `UPROPERTY()`
- L679 _private member_ `TArray<float> VertexWeightSum;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API NEARESTNEIGHBORMODEL_API`
- L19 _namespace_ `namespace UE`
- L19 _namespace_ `namespace NearestNeighborModel` (scope `UE`)
- L104 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FPropertyChangedDelegate, FPropertyChangedEvent&, UNearestNeighborModelSection&);`

### `Plugins/Animation/MLDeformer/NearestNeighborModel/Source/NearestNeighborModel/Public/NearestNeighborModelHelpers.h` (Public)


#### class `UE::NearestNeighborModel::FHelpers`  
`class FHelpers`  
_L18-60_
- desc: Use a helper class to avoid adding NEARESTNEIGHBORMODEL_API to all functions.
- L22 _public prototype_ `static int32 GetNumFrames(const UAnimSequence* AnimSequence);`
- L23 _public prototype_ `static int32 GetNumFrames(const UGeometryCache* GeometryCache);`
- L26 _public function_ `template<class T> static T* NewDerivedObject()`
- L39 _public function_ `template<typename T> static TArray<T> Range(T End)`
- L51 _public function_ `template<typename T> static TArray<T> Range(const T Start, const T End)`

#### enum `UE::NearestNeighborModel::EOpFlag`  
`enum class EOpFlag : uint8`  
_L62-67_
- L64 _public enumerator_ `Success = 0`
- L65 _public enumerator_ `Error = 1`
- L66 _public enumerator_ `Warning = 2`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API NEARESTNEIGHBORMODEL_API`
- L13 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogNearestNeighborModel, Log, All);`
- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace NearestNeighborModel` (scope `UE`)
- L69 _namespace_ `namespace OpFlag` (scope `UE::NearestNeighborModel`)
- L71 _prototype_ `bool HasError(EOpFlag Flag);` (scope `UE::NearestNeighborModel::OpFlag`)
- L72 _prototype_ `EOpFlag AddError(EOpFlag Flag);` (scope `UE::NearestNeighborModel::OpFlag`)
- L73 _prototype_ `bool HasWarning(EOpFlag Flag);` (scope `UE::NearestNeighborModel::OpFlag`)
- L74 _prototype_ `EOpFlag AddWarning(EOpFlag Flag);` (scope `UE::NearestNeighborModel::OpFlag`)
- L76 _prototype_ `EOpFlag operator|(EOpFlag A, EOpFlag B);` (scope `UE::NearestNeighborModel`)
- L77 _prototype_ `EOpFlag& operator|=(EOpFlag& A, EOpFlag B);` (scope `UE::NearestNeighborModel`)
- L78 _prototype_ `EOpFlag operator&(EOpFlag A, EOpFlag B);` (scope `UE::NearestNeighborModel`)
- L79 _prototype_ `EOpFlag& operator&=(EOpFlag& A, EOpFlag B);` (scope `UE::NearestNeighborModel`)
- L80 _prototype_ `EOpFlag ToOpFlag(int32 Value);` (scope `UE::NearestNeighborModel`)

### `Plugins/Animation/MLDeformer/NearestNeighborModel/Source/NearestNeighborModel/Public/NearestNeighborModelInputInfo.h` (Public)


#### class `UNearestNeighborModelInputInfo`  
`class UNearestNeighborModelInputInfo : public UMLDeformerMorphModelInputInfo`  
_L16-37_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMLDeformerMorphModelInputInfo`
- L23 _public prototype_ `virtual int32 CalcNumNeuralNetInputs(int32 NumFloatsPerBone, int32 NumFloatsPerCurve) const override;` — UMLDeformerInputInfo overrides
- L24 _public prototype_ `virtual void ExtractBoneRotations(USkeletalMeshComponent* SkelMeshComponent, TArray<float>& OutRotations) const override;`
- L27 _public prototype_ `void ComputeNetworkInput(TConstArrayView<FQuat> BoneRotations, TArrayView<float> OutputView) const;`
- L32 _private prototype_ `void InitRefBoneRotations(const USkeletalMesh* SkelMesh);`
- L36 _private member_ `TArray<FQuat> RefBoneRotations;` — `UPROPERTY()`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API NEARESTNEIGHBORMODEL_API`
- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace NearestNeighborModel` (scope `UE`)

### `Plugins/Animation/MLDeformer/NearestNeighborModel/Source/NearestNeighborModel/Public/NearestNeighborModelInstance.h` (Public)


#### class `UNearestNeighborModelInstance`  
`class UNearestNeighborModelInstance : public UMLDeformerMorphModelInstance`  
_L22-77_
- reflection: `UCLASS(MinimalAPI, Blueprintable)`
- inherits: `UMLDeformerMorphModelInstance`
- L29 _public prototype_ `virtual void Init(USkeletalMeshComponent* SkelMeshComponent) override;` — UMLDeformerModelInstance overrides
- L30 _public prototype_ `virtual void Execute(float ModelWeight) override;`
- L31 _public prototype_ `virtual bool SetupInputs() override;`
- L32 _public prototype_ `virtual FString CheckCompatibility(USkeletalMeshComponent* InSkelMeshComponent, bool LogIssues=false) override;`
- L33 _public prototype_ `virtual void Tick(float DeltaTime, float ModelWeight) override;`
- L34 _public prototype_ `virtual int64 SetBoneTransforms(float* OutputBuffer, int64 OutputBufferSize, int64 StartIndex) override;`
- L38 _public prototype_ `void Reset();` — `UFUNCTION(BlueprintCallable, Category = "NearestNeighborModel")`
- L47 _public prototype_ `TArray<uint32> GetNearestNeighborIds() const;`
- L51 _private typedef_ `using UNetworkPtr = TWeakObjectPtr<UNearestNeighborOptimizedNetwork>;`
- L52 _private typedef_ `using UConstNetworkPtr = const TWeakObjectPtr<const UNearestNeighborOptimizedNetwork>;`
- L54 _private prototype_ `void InitInstanceData(int32 NumMorphWeights = INDEX_NONE);`
- L56 _private prototype_ `UNearestNeighborModel* GetCastModel() const;`
- L57 _private prototype_ `void InitOptimizedNetworkInstance();`
- L58 _private prototype_ `TOptional<TArrayView<float>> GetInputView() const;`
- L59 _private prototype_ `TOptional<TArrayView<float>> GetOutputView() const;`
- L61 _private prototype_ `void RunNearestNeighborModel(float DeltaTime, float ModelWeight);`
- L65 _private prototype_ `TArray<float> Eval(const TArray<float>& InputData);` — `UFUNCTION(BlueprintCallable, Category = "Python")` — This is the slow version of network inference. It is used by python.
- L68 _private member_ `TArray<uint32> NearestNeighborIds;`
- L71 _private member_ `TArray<float> PreviousWeights;`
- L72 _private member_ `TArray<float> DistanceBuffer;`
- L73 _private member_ `bool bNeedsReset = true;`
- L76 _private member_ `TObjectPtr<UNearestNeighborOptimizedNetworkInstance> OptimizedNetworkInstance;` — `UPROPERTY()`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API NEARESTNEIGHBORMODEL_API`
- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace NearestNeighborModel` (scope `UE`)

### `Plugins/Animation/MLDeformer/NearestNeighborModel/Source/NearestNeighborModel/Public/NearestNeighborModelVizSettings.h` (Public)


#### class `UNearestNeighborModelVizSettings`  
`class UNearestNeighborModelVizSettings : public UMLDeformerMorphModelVizSettings`  
_L18-49_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMLDeformerMorphModelVizSettings`
- desc: The vizualization settings specific to the the vertex delta model.
- L24 _public function_ `static FName GetNearestNeighborIdsPropertyName()`
- L28 _public member_ `bool bDrawVerts = false;` — `UPROPERTY(EditAnywhere, Category = "Training Meshes")` — Whether to show verts
- L32 _public member_ `int32 VertVizSectionIndex = INDEX_NONE;` — `UPROPERTY(EditAnywhere, Category = "Training Meshes", Meta = (DisplayName = "Show Verts in", EditorCondition = "bDrawVerts"))` — Show vertices in this section
- L35 _public member_ `float NearestNeighborActorsOffset_DEPRECATED = 2.0f;` — `UPROPERTY()`
- L39 _public member_ `int32 NearestNeighborActorSectionIndex = 0;` — `UPROPERTY(EditAnywhere, Category = "Live Settings", Meta = (DisplayName = "Actor Section Index"))` — The section used to display the nearest neighbor.
- L42 _public member_ `TArray<int32> NearestNeighborIds;` — `UPROPERTY(VisibleAnywhere, Category = "Live Settings")`
- L45 _public member_ `int32 NeighborStatsPartId = 0;` — `UPROPERTY(EditAnywhere, Category = "Live Settings", meta = (DisplayName = "Part Id"))`
- L47 _public function_ `void SetNearestNeighborIds(const TArray<int32>& InNearestNeighborIds)`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace NearestNeighborModel` (scope `UE`)

### `Plugins/Animation/MLDeformer/NearestNeighborModel/Source/NearestNeighborModel/Public/NearestNeighborOptimizedNetworkLoader.h` (Public)


#### class `UNearestNeighborOptimizedNetworkLoader`  
`class UE_DEPRECATED(5.4, "UNearestNeighborOptimizedNetworkLoader is deprecated. Use NNE instead.") UNearestNeighborOptimizedNetworkLoader : public UObject`  
_L14-30_
- reflection: `UCLASS()`
- inherits: `UObject`
- desc: Helper class to load the optimized network from disk. LoadOptimizedNetwork is implemented in python.
- L21 _public prototype_ `bool LoadOptimizedNetwork(const FString& OnnxPath);` — `UFUNCTION(BlueprintImplementableEvent, Category = "Nearest Neighbor Model")`
- L23 _public prototype_ `void SetOptimizedNetwork(UNearestNeighborOptimizedNetwork* InNetwork);`
- L26 _public prototype_ `UNearestNeighborOptimizedNetwork* GetOptimizedNetwork() const;` — `UFUNCTION(BlueprintPure, Category = "Nearest Neighbor Model")`
- L29 _protected member_ `TObjectPtr<UNearestNeighborOptimizedNetwork> Network = nullptr;`
