# Plugins / MLDeformerFramework

- module root: `Plugins/Animation/MLDeformer/MLDeformerFramework/Source/MLDeformerFramework`
- headers: 25; symbols: 756
- symbol kinds: class=23, delegate=7, enum=6, enumerator=20, externvar=1, function=248, macro=16, member=179, namespace=16, prototype=225, struct=14, typedef=1
- DynamicallyLoadedModuleNames: 
- PrivateDependencyModuleNames: ComputeFramework, CoreUObject, Engine, GeometryCache, MeshDescription, OptimusCore, Projects, RHI, RenderCore, SkeletalMeshDescription
- PublicDependencyModuleNames: Core

### `Plugins/Animation/MLDeformer/MLDeformerFramework/Source/MLDeformerFramework/Private/DeformerGraphDataInterfaceSkeletonWithQuats.h` (Private)


#### class `UDeformerGraphSkeletonWithWeightedQuatsDataInterface`  
`class UDeformerGraphSkeletonWithWeightedQuatsDataInterface : public UOptimusComputeDataInterface`  
_L20-45_
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

#### class `UDeformerGraphSkeletonWithWeightedQuatsDataProvider`  
`class UDeformerGraphSkeletonWithWeightedQuatsDataProvider : public UComputeDataProvider`  
_L49-61_
- reflection: `UCLASS(MinimalAPI, BlueprintType, EditInlineNew, Category = ComputeFramework)`
- inherits: `UComputeDataProvider`
- desc: Compute Framework Data Provider for reading skeletal mesh.
- L56 _public member_ `TObjectPtr<USkinnedMeshComponent> SkinnedMesh = nullptr;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Binding)`
- L59 _public prototype_ `FComputeDataProviderRenderProxy* GetRenderProxy() override;`

#### class `UE::MLDeformer::FDeformerGraphSkeletonWithWeightedQuatsDataProviderProxy`  
`class FDeformerGraphSkeletonWithWeightedQuatsDataProviderProxy : public FComputeDataProviderRenderProxy`  
_L65-87_
- inherits: `FComputeDataProviderRenderProxy`
- L69 _public prototype_ `FDeformerGraphSkeletonWithWeightedQuatsDataProviderProxy(USkinnedMeshComponent* SkinnedMeshComponent);`
- L72 _public prototype_ `bool IsValid(FValidationData const& InValidationData) const override;`
- L73 _public prototype_ `void GatherPermutations(FPermutationData& InOutPermutationData) const override;`
- L74 _public prototype_ `void GatherDispatchData(FDispatchData const& InDispatchData) override;`
- L75 _public prototype_ `void AllocateResources(FRDGBuilder& GraphBuilder, FAllocationData const& InAllocationData) override;`
- L79 _private typedef_ `using FParameters = FSkeletonWithQuatsDataInterfaceParameters;`
- L80 _private prototype_ `void CacheRefToLocalQuats(TArray<FQuat4f>& OutRefToLocalQuats) const;`
- L82 _private member_ `FSceneInterface* SceneInterface = nullptr;`
- L83 _private member_ `FPrimitiveComponentId ComponentId;`
- L84 _private member_ `uint32 BoneRevisionNumber = 0;`
- L85 _private member_ `TArray<TArray<FQuat4f> > PerSectionRefToLocalQuats;`
- L86 _private member_ `TArray<FRDGBufferSRVRef> PerSectionRefToLocalQuatsSRVs;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API MLDEFORMERFRAMEWORK_API`
- L63 _namespace_ `namespace UE`
- L63 _namespace_ `namespace MLDeformer` (scope `UE`)

### `Plugins/Animation/MLDeformer/MLDeformerFramework/Source/MLDeformerFramework/Private/MLDeformerComponentSource.h` (Private)


#### class `UMLDeformerComponentSource`  
`class UMLDeformerComponentSource : public UOptimusComponentSource`  
_L11-29_
- reflection: `UCLASS(meta=(DisplayName="ML Deformer Component"))`
- inherits: `UOptimusComponentSource`
- L22 _public prototype_ `FText GetDisplayName() const override;` — UOptimusComponentSource implementations
- L23 _public function_ `FName GetBindingName() const override`
- L24 _public prototype_ `TSubclassOf<UActorComponent> GetComponentClass() const override;`
- L25 _public prototype_ `TArray<FName> GetExecutionDomains() const override;`
- L26 _public prototype_ `int32 GetLodIndex(const UActorComponent* InComponent) const override;`
- L27 _public prototype_ `uint32 GetDefaultNumInvocations(const UActorComponent* InComponent, int32 InLod) const override;`
- L28 _public prototype_ `bool GetComponentElementCountsForExecutionDomain(FName InDomainName, const UActorComponent* InComponent, int32 InLodIndex, TArray<int32>& OutElementCounts) const override;`

#### struct `UMLDeformerComponentSource::Domains`  
`struct Domains`  
_L16-19_
- L18 _public member_ `static FName Vertex;`

### `Plugins/Animation/MLDeformer/MLDeformerFramework/Source/MLDeformerFramework/Public/MLDeformerAsset.h` (Public)


#### class `UMLDeformerAsset`  
`class UMLDeformerAsset : public UObject`  
_L19-46_
- reflection: `UCLASS(MinimalAPI, BlueprintType, hidecategories=Object)`
- inherits: `UObject`
- desc: The machine learning deformer asset class. This class contains a Model property, through which most functionality happens.
- L26 _public prototype_ `virtual void Serialize(FArchive& Archive) override;` — UObject overrides.
- L27 _public prototype_ `virtual void GetAssetRegistryTags(FAssetRegistryTagsContext Context) const override;`
- L34 _public function_ `UMLDeformerModel* GetModel() const` — Get the ML Deformer model that is being applied by this asset. @return A pointer to the model.
- L40 _public function_ `void SetModel(UMLDeformerModel* InModel)` — Set the ML Deformer model that is used by this deformer asset. @param InModel A pointer to the model object.
- L45 _public member_ `TObjectPtr<UMLDeformerModel> Model = nullptr;` — `UPROPERTY()` — The ML Deformer model, used to deform the mesh.

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API MLDEFORMERFRAMEWORK_API`

### `Plugins/Animation/MLDeformer/MLDeformerFramework/Source/MLDeformerFramework/Public/MLDeformerComponent.h` (Public)


#### class `UMLDeformerComponent`  
`class UMLDeformerComponent : public UActorComponent`  
_L28-243_
- reflection: `UCLASS(MinimalAPI, Blueprintable, ClassGroup = Component, BlueprintType, meta = (BlueprintSpawnableComponent))`
- inherits: `UActorComponent`
- desc: The ML mesh deformer component. This works in combination with a MLDeformerAsset and SkeletalMeshComponent. The component will perform runtime inference of the deformer model setup inside the asset. When you have multiple skeletal mesh components on your actor, this component will try to use the skeletal mesh component that uses the same skeletal mesh as the applied deformer was trained on. If it cannot find that, it will use the first skeletal mesh component it finds.
- L35 _public prototype_ `void BeginDestroy() override;` — UObject overrides.
- L37 _public prototype_ `void PreEditChange(FProperty* Property) override;`
- L38 _public prototype_ `void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L43 _public prototype_ `void Activate(bool bReset=false) override;` — UActorComponent overrides.
- L44 _public prototype_ `void Deactivate() override;`
- L52 _public prototype_ `void SetupComponent(UMLDeformerAsset* InDeformerAsset, USkeletalMeshComponent* InSkelMeshComponent);` — Setup the ML Deformer, by picking the deformer asset and skeletal mesh component. @param InDeformerAsset The ML Deformer asset to apply to the specified skeletal mesh component. @param InSkelMeshComponent The skeletal mesh component to apply the specified deformer to.
- L59 _public function_ `float GetWeight() const` — `UFUNCTION(BlueprintCallable, Category = "MLDeformer")` — Get the current ML Deformer weight. A value of 0 means it is fully disabled, while 1 means fully active. Values can be anything between 0 and 1.
- L70 _public function_ `void SetWeight(float NormalizedWeightValue)` — `UFUNCTION(BlueprintCallable, Category = "MLDeformer")` — Set the ML Deformer weight. This determines how active the deformer is. You can see it as a blend weight. A value of 0 means it is inactive. Certain calculations will be skipped in that case. A value of 1 means it is fully active. Values between 0 and 1 blend between the two states. Call this after you call SetupComponent. @param NormalizedWeightValue The weight value.
- L82 _public function_ `void SetQualityLevel(int32 InQualityLevel)` — `UE_DEPRECATED(5.4, "This function will be removed.")` — `UFUNCTION(meta = (DeprecatedFunction, DeprecationMessage = "SetQualityLevel has been deprecated."))` — The quality level of the deformer. A value of 0 is the highest quality, 1 is a step lower, etc. It is up to the models to configure what each quality level means visually. If the quality level will be clamped to the available quality levels, so if you choose quality level 100, while there are only 3 levels, then quality level 3 will be used in this case, which represents the lowest available quality. In morph based models each quality level defines how many morph targets are active at most. @param InQualityLevel The quality level to switch to.
- L94 _public function_ `int32 GetQualityLevel() const` — `UE_DEPRECATED(5.4, "This function will be removed.")` — `UFUNCTION(meta = (DeprecatedFunction, DeprecationMessage = "GetQualityLevel has been deprecated."))` — The quality level of the deformer. A value of 0 is the highest quality, 1 is a step lower, etc. It is up to the models to configure what each quality level means visually. If the quality level will be clamped to the available quality levels, so if you choose quality level 100, while there are only 3 levels, then quality level 3 will be used in this case, which represents the lowest available quality. In morph based models each quality level defines how many morph targets are active at most. @param InQualityLevel The quality level to switch to.
- L101 _public function_ `UMLDeformerAsset* GetDeformerAsset() const` — `UFUNCTION(BlueprintCallable, Category = "MLDeformer")` — Get the ML Deformer asset that is used by this component. @return A pointer to the ML Deformer asset.
- L109 _public function_ `void SetDeformerAsset(UMLDeformerAsset* InDeformerAsset)` — `UFUNCTION(BlueprintCallable, Category = "MLDeformer")` — Set the deformer asset that is used by this component. This will trigger the internal ML Deformer instance to be recreated. @param InDeformerAsset A pointer to the deformer asset.
- L119 _public prototype_ `USkeletalMeshComponent* FindSkeletalMeshComponent(const UMLDeformerAsset* const Asset) const;` — `UFUNCTION(BlueprintCallable, Category = "MLDeformer")` — Find the skeletal mesh component to apply the deformer on. This will return the skeletal mesh component (on this actor) which uses the same skeletal mesh as the passed in ML Deformer asset was trained on. If there is no such skeletal mesh component then it will return a nullptr. @param Asset The ML Deformer asset to search a component for. @return The skeletal mesh component that would be the best.
- L127 _public function_ `UMLDeformerModelInstance* GetModelInstance() const` — `UFUNCTION(BlueprintCallable, Category = "MLDeformer")` — Get the ML Deformer model instance that this component currently uses. The instance is responsible for running inference and feeding the neural network with inputs. @return A pointer to the model instance object.
- L135 _public function_ `USkeletalMeshComponent* GetSkeletalMeshComponent() const` — `UFUNCTION(BlueprintCallable, Category = "MLDeformer")` — Get the skeletal mesh component that the ML Deformer will work on. The skeletal mesh that is setup inside the skeletal mesh component will be the mesh that will be deformed by this ML Deformer component. @return A pointer to the skeletal mesh component who's mesh will be deformed by this ML Deformer component.
- L139 _public prototype_ `void UpdateSkeletalMeshComponent();` — `UFUNCTION(BlueprintCallable, Category = "MLDeformer")` — Find the skeletal mesh component that this deformer should work on, and set it as our target component.
- L148 _public prototype_ `float GetFinalMLDeformerWeight() const;` — Get the final weight that is used when applying the ML Deformer. Some console command might override the weight that was set to this component. This method will return the real weight that will be applied, after console command modifications are applied as well. So this is the actual final weight used on the ML Deformer. @return The ML Deformer weight value that is used to deform the mesh, where 0 means it is not doing any deformations and 1 means it is fully active.
- L155 _public function_ `void SetSuppressMeshDeformerLogWarnings(bool bSuppress)` — Suppress logging warnings about mesh deformers not being set. A warning is logged when an ML Deformer is used that requires a deformer graph, but the skeletal mesh has no deformer graph setup. @param bSuppress Set to true to silent warnings about deformer graphs not being set, while the active ML Model needs one.
- L161 _public function_ `const UE::MLDeformer::FMLDeformerPerfCounter& GetTickPerfCounter() const` — Get the performance counter that measures how much time is spent inside the Tick function.
- L163 _public function_ `TObjectPtr<AActor> GetDebugActor() const`
- L164 _public function_ `void SetDebugActor(TObjectPtr<AActor> Actor)`
- L168 _public function_ `static FName GetDeformerAssetPropertyName()` — Get property names.
- L169 _public function_ `static FName GetWeightPropertyName()`
- L173 _protected prototype_ `virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;` — AActorComponent overrides.
- L177 _protected prototype_ `virtual void SetWeightInternal(const float NormalizedWeightValue);` — Set the ML Deformer weight.
- L180 _protected prototype_ `virtual void SetDeformerAssetInternal(UMLDeformerAsset* const InDeformerAsset);` — Set the ML Deformer asset.
- L188 _protected prototype_ `void Init();` — Initialize the component. This releases any existing deformer instance that is active, and creates a new one. It then also calls PostMLDeformerComponentInit. This method is called automatically by SetupComponent.
- L190 _protected prototype_ `void BindDelegates();`
- L191 _protected prototype_ `void UnbindDelegates();`
- L192 _protected prototype_ `void ReleaseModelInstance();`
- L197 _protected member_ `UE::MLDeformer::FMLDeformerPerfCounter TickPerfCounter;` — The performance counter that measures timing of the Tick function.
- L203 _protected member_ `TObjectPtr<AActor> DebugActor;` — The actor we are currently debugging. This can be used to copy over specific information from another actor, such as copying over external morph target weights. When set to a nullptr, then we're not debugging. This actor most likely is inside another UWorld.
- L207 _protected member_ `FRenderCommandFence RenderCommandFence;` — Render command fence that let's us wait for all other commands to finish.
- L214 _protected member_ `TObjectPtr<USkeletalMeshComponent> SkelMeshComponent;` — The skeletal mesh component we want to grab the bone transforms etc from. This can be a nullptr. When it is a nullptr then it will internally try to find the first skeletal mesh component on the actor. You can see this as an override. You can specify this override through the SetupComponent function.
- L217 _protected member_ `FDelegateHandle ReinitModelInstanceDelegateHandle;` — The delegate handle used to bind to the reinit model instance delegate handle.
- L220 _protected member_ `bool bSuppressMeshDeformerLogWarnings = false;` — Suppress mesh deformer logging warnings? This is used by the ML Deformer editor, as we don't want to show some warnings when using that.
- L224 _protected member_ `TObjectPtr<UMLDeformerAsset> DeformerAsset;` — `UPROPERTY(EditAnywhere, DisplayName = "ML Deformer Asset", Category = "ML Deformer")` — The deformer asset to use.
- L228 _protected member_ `float Weight = 1.0f;` — `UPROPERTY(EditAnywhere, Category = "ML Deformer", meta = (ClampMin = "0.0", ClampMax = "1.0"))` — How active is this deformer? Can be used to blend it in and out.
- L238 _protected member_ `int32 QualityLevel_DEPRECATED = 0;` — `UPROPERTY()` — The quality level of the deformer. A value of 0 is the highest quality, 1 is a step lower, etc. It is up to the models to configure what each quality level means visually. If the quality level will be clamped to the available quality levels, so if you choose quality level 100, while there are only 3 levels, then quality level 3 will be used in this case, which represents the lowest available quality. In morph based models each quality level defines how many morph targets are active at most.
- L242 _protected member_ `TObjectPtr<UMLDeformerModelInstance> ModelInstance;` — `UPROPERTY(Transient)` — The deformation model instance. This is used to perform the runtime updates and run the inference.

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API MLDEFORMERFRAMEWORK_API`

### `Plugins/Animation/MLDeformer/MLDeformerFramework/Source/MLDeformerFramework/Public/MLDeformerCurveReference.h` (Public)


#### struct `FMLDeformerCurveReference`  
`struct FMLDeformerCurveReference`  
_L13-47_
- reflection: `USTRUCT()`
- desc: A reference to a curve implemented as a name.
- L17 _public function_ `FMLDeformerCurveReference(const FName& InCurveName=NAME_None) : CurveName(InCurveName)`
- L22 _public function_ `bool operator==(const FMLDeformerCurveReference& Other) const`
- L27 _public function_ `bool operator!=(const FMLDeformerCurveReference& Other) const`
- L38 _public function_ `bool Serialize(FArchive& Ar)`
- L46 _public member_ `FName CurveName;` — `UPROPERTY(EditAnywhere, Category = AnimCurveReference)` — The name of the curve.

#### Free symbols / members of external scopes

- L32 _function_ `friend FArchive& operator<<(FArchive& Ar, FMLDeformerCurveReference& C)`

### `Plugins/Animation/MLDeformer/MLDeformerFramework/Source/MLDeformerFramework/Public/MLDeformerGeomCacheHelpers.h` (Public)


#### struct `UE::MLDeformer::FMLDeformerGeomCacheMeshMapping`  
`struct FMLDeformerGeomCacheMeshMapping`  
_L19-26_
- desc: A mapping between a geometry cache track and a mesh inside a USkeletalMesh.
- L21 _public member_ `int32 MeshIndex = INDEX_NONE;` — The imported model's mesh info index, inside the skeletal mesh.
- L22 _public member_ `int32 TrackIndex = INDEX_NONE;` — The geometry cache track that this mesh is mapped to.
- L23 _public member_ `TArray<int32> SkelMeshToTrackVertexMap;` — This maps imported model individual meshes to the geomcache track's mesh data.
- L24 _public member_ `TArray<int32> ImportedVertexToRenderVertexMap;` — Map the imported DCC vertex number to a render vertex. This is just one of the duplicates, which shares the same position.
- L25 _public member_ `TArray<int32> MaterialIndices;` — List of material indices that point inside the SkelMesh. These materials are used on parts of the mesh that are modified by the ML Deformer.

#### Free symbols / members of external scopes

- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace MLDeformer` (scope `UE`)
- L37 _prototype_ `FText GetGeomCacheErrorText(USkeletalMesh* InSkeletalMesh, UGeometryCache* InGeomCache);` (scope `UE::MLDeformer`) — Check whether the geometry cache has any issues when used in combination with a given skeletal mesh. Please note that this does not check the actual geometry data for matching vertex counts. What it does check is if the geometry cache has geometry at all, and whether it has imported vertex numbers and whether flattened tracks was enabled, while there are multiple meshes in the skeletal mesh. @param InSkeletalMesh The skeletal mesh that is being used. @param InGeomCache The geometry cache that is being used. @return The error text in case there are errors, or an empty text object in case there were no errors.
- L46 _prototype_ `FText GetGeomCacheAnimSequenceErrorText(const UGeometryCache* InGeomCache, const UAnimSequence* InAnimSequence);` (scope `UE::MLDeformer`) — Check for any issues between a geometry cache and an anim sequence when used together. This will check if the duration of both are the same or not. @param InGeomCache The geometry cache object. @param InAnimSequence The animation sequence object. @return The error text in case there are errors, or an empty text object in case there were no errors.
- L56 _prototype_ `FText GetGeomCacheMeshMappingErrorText(USkeletalMesh* InSkelMesh, UGeometryCache* InGeomCache);` (scope `UE::MLDeformer`) — Check for any mesh related issues between a skeletal mesh and geometry cache. This will check if the Skeletal Mesh contains all meshes that are required for the geometry cache tracks. It also checks for vertex count mismatches. @param InSkelMesh The skeletal mesh object. @param InGeomCache The geometry cache object. @return The error text in case there are errors, or an empty text object in case there were no errors.
- L65 _prototype_ `int32 ExtractNumImportedGeomCacheVertices(UGeometryCache* GeometryCache);` (scope `UE::MLDeformer`) — Get the number of imported geometry cache vertices. Imported vertices are the vertex count as you see in the DCC, so a cube would have 8. This is different from the render vertex count. @param GeometryCache The geometry cache to get the imported vertex count for. @return The number of vertices as seen in the DCC, so for example 8 for a cube.
- L79 _prototype_ `void GenerateGeomCacheMeshMappings(USkeletalMesh* SkelMesh, UGeometryCache* GeomCache, TArray<FMLDeformerGeomCacheMeshMapping>& OutMeshMappings, TArray<FString>& OutFailedImportedMeshNames, TArray<FString>& OutVertexMisMatchNames, bool bSuppressLog = false);` (scope `UE::MLDeformer`) — Generate the mapping between geometry cache tracks and meshes inside a specific skeletal mesh. This will check if the Skeletal Mesh contains all meshes that are required for the geometry cache tracks. It also checks for vertex count mismatches. This function is called by the GetGeomCacheMeshMappingErrorText function, in case you are just interested in the error checking part. @param SkelMesh The skeletal mesh object. @param GeomCache The geometry cache object. @param OutMeshMapping The mapping that will be generated. This information maps each geometry cache map with a given compatible mesh inside a skeletal mesh. @param OutFailedImportedMeshNames The array of geometry cache track names for which no mesh could be found inside the skeletal mesh object. @param OutVertexMisMatchNames The array of geometry cache track names for which the vertex counts didn't match the related meshes inside the skeletal mesh. @param bSuppressLog Set to true to suppress any log messages.
- L92 _prototype_ `void SampleGeomCachePositionsAtFrame( int32 InLODIndex, int32 FrameIndex, const TArray<FMLDeformerGeomCacheMeshMapping>& InMeshMappings, const USkeletalMesh* InSkelMesh, const UGeometryCache* InGeometryCache, const FTransform& InAlignmentTransform, TArray<FVector3f>& OutPositions);` (scope `UE::MLDeformer`) — Sample the vertex position data of a geometry cache, at a given time stamp. This basically allows you to sample ground truth or training target vertex positions. @param InLODIndex The LOD level to sample for. @param FrameIndex The frame number to sample. @param InMeshMappings The geometry cache to skeletal mesh mappings, which can be generated using the GenerateGeomCacheMeshMappings method. @param InSkelMesh The skeletal mesh object. @param InGeometryCache The geometry cache object. @param InAlignmentTransform This is the transformation that will be applied on the sampled positions, as post process. This can be used to rotate or scale the position data. @param OutPositions The resulting positions, as sampled at the specified time. This array will be resized internally.

### `Plugins/Animation/MLDeformer/MLDeformerFramework/Source/MLDeformerFramework/Public/MLDeformerGeomCacheModel.h` (Public)


#### class `UMLDeformerGeomCacheModel`  
`class UMLDeformerGeomCacheModel : public UMLDeformerModel`  
_L26-81_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMLDeformerModel`
- desc: An ML Deformer model that has a geometry cache as target mesh. Use this in combination with UMLDeformerGeomCacheVizSettings, FMLDeformerGeomCacheEditorModel, FMLDeformerGeomCacheVizSettingsDetails and FMLDeformerGeomCacheModelDetails.
- L33 _public prototype_ `virtual void PostLoad() override;` — UObject overrides.
- L34 _public prototype_ `virtual void GetAssetRegistryTags(FAssetRegistryTagsContext Context) const override;`
- L39 _public prototype_ `virtual bool HasTrainingGroundTruth() const override;`
- L40 _public prototype_ `virtual void SampleGroundTruthPositionsAtFrame(int32 FrameIndex, TArray<FVector3f>& OutPositions) override;`
- L41 _public prototype_ `virtual void SampleGroundTruthPositions(float SampleTime, TArray<FVector3f>& OutPositions) override;` — Deprecated in base class, will be removed soon.
- L44 _public prototype_ `virtual void UpdateNumTargetMeshVertices() override;`
- L51 _public prototype_ `UMLDeformerGeomCacheVizSettings* GetGeomCacheVizSettings() const;` — Get the visualization settings, already cast to a UMLDeformerGeomCacheVizSettings type. @return A pointer to the visualization settings.
- L61 _public function_ `TArray<UE::MLDeformer::FMLDeformerGeomCacheMeshMapping>& GetGeomCacheMeshMappings()` — Get the mapping between geometry cache tracks and meshes inside the skeletal mesh. This lets us know what parts of the skeletal mesh are related to what geometry cache tracks. Once we have that, we can calculate deltas between the two. @return The geometry cache mesh to skeletal mesh mappings.
- L62 _public function_ `const TArray<UE::MLDeformer::FMLDeformerGeomCacheMeshMapping>& GetGeomCacheMeshMappings() const`
- L64 _public function_ `TArray<FMLDeformerGeomCacheTrainingInputAnim>& GetTrainingInputAnims()`
- L65 _public function_ `const TArray<FMLDeformerGeomCacheTrainingInputAnim>& GetTrainingInputAnims() const`
- L67 _public function_ `static FName GetTrainingInputAnimsPropertyName()`
- L71 _private member_ `TArray<UE::MLDeformer::FMLDeformerGeomCacheMeshMapping> MeshMappings;` — The mappings between the geometry cache tracks and skeletal mesh imported meshes.
- L75 _private member_ `TSoftObjectPtr<UGeometryCache> GeometryCache_DEPRECATED;` — `UPROPERTY(meta=(DeprecatedProperty, DeprecationMessage="Use the training input anims instead."))` — The geometry cache that represents the target deformations.
- L79 _private member_ `TArray<FMLDeformerGeomCacheTrainingInputAnim> TrainingInputAnims;` — `UPROPERTY(EditAnywhere, Category = "Inputs")` — The training animation inputs.

#### Free symbols / members of external scopes

- L16 _macro_ `#define UE_API MLDEFORMERFRAMEWORK_API`

### `Plugins/Animation/MLDeformer/MLDeformerFramework/Source/MLDeformerFramework/Public/MLDeformerGeomCacheTrainingInputAnim.h` (Public)


#### struct `FMLDeformerGeomCacheTrainingInputAnim`  
`struct FMLDeformerGeomCacheTrainingInputAnim : public FMLDeformerTrainingInputAnim`  
_L17-43_
- reflection: `USTRUCT()`
- inherits: `FMLDeformerTrainingInputAnim`
- desc: An animation that is input to the training process, which has a geometry cache as target.
- L25 _public prototype_ `virtual int32 GetNumFramesToSample() const override;` — FMLDeformerTrainingInputAnim overrides
- L26 _public prototype_ `virtual bool IsValid() const override;`
- L27 _public prototype_ `virtual int32 ExtractNumAnimFrames() const override;`
- L30 _public function_ `void SetGeometryCache(TSoftObjectPtr<UGeometryCache> GeomCache)`
- L32 _public function_ `const UGeometryCache* GetGeometryCache() const`
- L33 _public function_ `UGeometryCache* GetGeometryCache()`
- L34 _public function_ `TSoftObjectPtr<UGeometryCache>& GetGeometryCacheSoftObjectPtr()`
- L35 _public function_ `const TSoftObjectPtr<UGeometryCache>& GetGeometryCacheSoftObjectPtr() const`
- L36 _public function_ `static FName GetGeomCachePropertyName()`
- L41 _private member_ `TSoftObjectPtr<UGeometryCache> GeometryCache;` — `UPROPERTY(EditAnywhere, Category = "Settings", meta = (DisplayPriority = 10))` — The geometry cache which contains the target deformations.

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API MLDEFORMERFRAMEWORK_API`

### `Plugins/Animation/MLDeformer/MLDeformerFramework/Source/MLDeformerFramework/Public/MLDeformerGeomCacheVizSettings.h` (Public)


#### class `UMLDeformerGeomCacheVizSettings`  
`class UMLDeformerGeomCacheVizSettings : public UMLDeformerVizSettings`  
_L17-48_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMLDeformerVizSettings`
- desc: The visualization settings for a model that has a geometry cache. This can be used in combination with a UMLDeformerGeomCacheModel.
- L25 _public function_ `virtual bool HasTestGroundTruth() const override` — UMLDeformerModel overrides.
- L32 _public function_ `UGeometryCache* GetTestGroundTruth() const` — Get the test ground truth geometry cache, which represents the ground truth version of the test animation sequence. @return A pointer to the geometry cache object.
- L38 _public function_ `void SetTestGroundTruth(TSoftObjectPtr<UGeometryCache> InGroundTruth)` — Set the test ground truth geometry cache. @param InGroundTruth The ground truth model.
- L41 _public function_ `static FName GetTestGroundTruthPropertyName()` — Get property names.
- L46 _protected member_ `TSoftObjectPtr<UGeometryCache> GroundTruth = nullptr;` — `UPROPERTY(EditAnywhere, Category = "Test Assets")` — The geometry cache that represents the ground truth of the test anim sequence.

### `Plugins/Animation/MLDeformer/MLDeformerFramework/Source/MLDeformerFramework/Public/MLDeformerGraphDebugDataInterface.h` (Public)


#### class `UMLDeformerGraphDebugDataInterface`  
`class UMLDeformerGraphDebugDataInterface : public UOptimusComputeDataInterface`  
_L27-52_
- reflection: `UCLASS(MinimalAPI, Category = ComputeFramework)`
- inherits: `UOptimusComputeDataInterface`
- desc: Compute Framework Data Interface for MLDeformer debugging data. This interfaces to editor only data, and so will only give valid results in that context.
- L34 _public prototype_ `virtual FString GetDisplayName() const override;` — UOptimusComputeDataInterface overrides.
- L35 _public prototype_ `virtual TArray<FOptimusCDIPinDefinition> GetPinDefinitions() const override;`
- L36 _public prototype_ `virtual TSubclassOf<UActorComponent> GetRequiredComponentClass() const override;`
- L40 _public function_ `TCHAR const* GetClassName() const override` — UComputeDataInterface overrides.
- L41 _public function_ `virtual bool CanSupportUnifiedDispatch() const override`
- L42 _public prototype_ `virtual void GetSupportedInputs(TArray<FShaderFunctionDefinition>& OutFunctions) const override;`
- L43 _public prototype_ `virtual void GetShaderParameters(TCHAR const* UID, FShaderParametersMetadataBuilder& OutBuilder, FShaderParametersMetadataAllocations& InOutAllocations) const override;`
- L44 _public prototype_ `virtual TCHAR const* GetShaderVirtualPath() const override;`
- L45 _public prototype_ `virtual void GetShaderHash(FString& InOutKey) const override;`
- L46 _public prototype_ `virtual void GetHLSL(FString& OutHLSL, FString const& InDataInterfaceName) const override;`
- L47 _public prototype_ `virtual UComputeDataProvider* CreateDataProvider(TObjectPtr<UObject> InBinding, uint64 InInputMask, uint64 InOutputMask) const override;`
- L51 _private member_ `static TCHAR const* TemplateFilePath;`

#### class `UMLDeformerGraphDebugDataProvider`  
`class UMLDeformerGraphDebugDataProvider : public UComputeDataProvider`  
_L56-74_
- reflection: `UCLASS(MinimalAPI, BlueprintType, EditInlineNew, Category = ComputeFramework)`
- inherits: `UComputeDataProvider`
- desc: Compute Framework Data Provider for MLDeformer debugging data.
- L62 _public function_ `virtual void Init()`
- L65 _public prototype_ `virtual FComputeDataProviderRenderProxy* GetRenderProxy() override;` — UComputeDataProvider overrides.
- L70 _public member_ `TObjectPtr<UMLDeformerComponent> DeformerComponent = nullptr;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Binding)`
- L73 _public member_ `TObjectPtr<UMLDeformerAsset> DeformerAsset = nullptr;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Binding)`

#### class `UE::MLDeformer::FMLDeformerGraphDebugDataProviderProxy`  
`class FMLDeformerGraphDebugDataProviderProxy : public FComputeDataProviderRenderProxy`  
_L80-107_
- inherits: `FComputeDataProviderRenderProxy`
- L84 _public prototype_ `FMLDeformerGraphDebugDataProviderProxy(UMLDeformerComponent* DeformerComponent, UMLDeformerAsset* DeformerAsset, UMLDeformerGraphDebugDataProvider* InProvider);`
- L86 _public prototype_ `virtual void HandleZeroGroundTruthPositions();`
- L89 _public prototype_ `bool IsValid(FValidationData const& InValidationData) const override;` — FComputeDataProviderRenderProxy overrides.
- L90 _public prototype_ `void AllocateResources(FRDGBuilder& GraphBuilder, FAllocationData const& InAllocationData) override;`
- L91 _public prototype_ `void GatherDispatchData(FDispatchData const& InDispatchData) override;`
- L94 _public function_ `TArray<FVector3f>& GetGroundTruthPositions()`
- L97 _protected member_ `TObjectPtr<UMLDeformerGraphDebugDataProvider> Provider = nullptr;`
- L98 _protected member_ `FSceneInterface* SceneInterface = nullptr;`
- L99 _protected member_ `FPrimitiveComponentId ComponentId;`
- L100 _protected member_ `TArray<FVector3f> GroundTruthPositions;`
- L101 _protected member_ `FRHIShaderResourceView* VertexMapBufferSRV = nullptr;`
- L102 _protected member_ `FRDGBuffer* GroundTruthBuffer = nullptr;`
- L103 _protected member_ `FRDGBufferSRV* GroundTruthBufferSRV = nullptr;`
- L104 _protected member_ `int32 HeatMapMode = 0;`
- L105 _protected member_ `float HeatMapMax = 0.0f;`
- L106 _protected member_ `float GroundTruthLerp = 0.0f;`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API MLDEFORMERFRAMEWORK_API`
- L78 _namespace_ `namespace UE`
- L78 _namespace_ `namespace MLDeformer` (scope `UE`)

### `Plugins/Animation/MLDeformer/MLDeformerFramework/Source/MLDeformerFramework/Public/MLDeformerInputInfo.h` (Public)


#### class `UMLDeformerInputInfo`  
`class UMLDeformerInputInfo : public UObject`  
_L21-258_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject`
- desc: The neural network input information. This contains arrays of names for things such as bones and curves. Knowing what bones etc are used as inputs, and in what order, helps us feeding the data during inference. It can also help us detect issues, for example when the character we apply the deformer to is missing any of those bones.
- L27 _public prototype_ `virtual ~UMLDeformerInputInfo() = default;`
- L30 _public prototype_ `virtual void GetAssetRegistryTags(FAssetRegistryTagsContext Context) const override;` — UObject overrides.
- L36 _public prototype_ `virtual void OnPostLoad();` — This method is executed post loading of the ML Deformer asset.
- L45 _public prototype_ `virtual bool IsCompatible(USkeletalMesh* InSkeletalMesh) const;` — Check whether the current inputs are compatible with a given skeletal mesh. For a more extensive check, please use IsCompatible that takes a USkeletalMeshComponent as parameter. @param InSkeletalMesh The skeletal mesh to check compatibility with. This may not be a nullptr. @return Returns true when we can safely apply the ML Deformer to a character using this skeletal mesh, otherwise false is returned. @note Use GenerateCompatibilityErrorString to get the error report.
- L53 _public prototype_ `virtual bool IsCompatible(const USkeletalMeshComponent* InSkeletalMeshComponent) const;` — Check whether the current inputs are compatible with a given skeletal mesh component. @param InSkeletalMeshComponent The skeletal mesh to check compatibility with. This may not be a nullptr. @return Returns true when we can safely apply the ML Deformer to a character using this skeletal mesh, otherwise false is returned. @note Use GenerateCompatibilityErrorString to get the error report.
- L59 _public prototype_ `virtual void Reset();` — Clear all contents. This can clear the list of all bone and curves that are part of this input info.
- L68 _public prototype_ `virtual FString GenerateCompatibilityErrorString(USkeletalMesh* InSkeletalMesh) const;` — `UE_DEPRECATED(5.7, "Please use the GenerateCompatibilityErrorString that takes a USkeletalMeshComponent as parameter instead.")` — Get the compatibility error report. @param InSkeletalMesh The skeletal mesh to check compatibility with. @return Returns an empty string in case there are no compatibility issues, otherwise it contains a string that describes the issue(s). In case a nullptr is passed as SkeletalMesh parameter, an empty string is returned.
- L76 _public prototype_ `virtual FString GenerateCompatibilityErrorString(const USkeletalMeshComponent* InSkeletalMeshComponent) const;` — Get the compatibility error report. @param InSkeletalMeshComponent The skeletal mesh component to check compatibility with. @return Returns an empty string in case there are no compatibility issues, otherwise it contains a string that describes the issue(s). In case a nullptr is passed as SkeletalMeshComponent parameter, an empty string is returned.
- L83 _public prototype_ `virtual bool IsEmpty() const;` — Check whether we have any training inputs or not. This happens when there are no bones or curves to use as inputs. @return Returns true when there are no bones or curves specified as inputs.
- L91 _public prototype_ `virtual int32 CalcNumNeuralNetInputs(int32 NumFloatsPerBone, int32 NumFloatsPerCurve) const;` — Calculate how many inputs this input info generates for the neural network. @param NumFloatsPerBone The number of floats used per bone. @param NumFloatsPerCurve The number of floats per curve. This can be used when padding is used on curve values. @return THe number of input float values to the neural network.
- L97 _public prototype_ `virtual void CopyMembersFrom(UMLDeformerInputInfo* Other);` — Copy members from the other class. @param Other The other class to copy over members from.
- L103 _public prototype_ `int32 GetNumBones() const;` — Get the number of bones that we trained on. @return The number of bones.
- L110 _public prototype_ `FName GetBoneName(int32 Index) const;` — Get the bone name as an FName, for a given bone we included during training. @param Index The bone index, which is a number in range of [0..GetNumBones()-1]. @result The name of the bone.
- L116 _public prototype_ `int32 GetNumCurves() const;` — Get the number of curves that we trained on. @return The number of curves.
- L122 _public prototype_ `TArray<FName>& GetBoneNames();` — Get the list of bone names that should be included as training inputs. @return An array of FName objects, one for each bone.
- L123 _public prototype_ `const TArray<FName>& GetBoneNames() const;`
- L129 _public prototype_ `TArray<FName>& GetCurveNames();` — Get the list of curve names that should be included as training inputs. @return An array of FName objects, one for each curve.
- L130 _public prototype_ `const TArray<FName>& GetCurveNames() const;`
- L137 _public prototype_ `FName GetCurveName(int32 Index) const;` — Get the curve name as an FName, for a given curve we included during training. @param Index The curve index, which is a number in range of [0..GetNumCurves()-1]. @result The name of the curve.
- L146 _public prototype_ `virtual void ExtractCurveValues(USkeletalMeshComponent* SkelMeshComponent, TArray<float>& OutValues, int32 NumFloatsPerCurve) const;` — Extract the curve values for all curves we're interested in. @param SkelMeshComponent The skeletal mesh component to sample from. @param OutValues The array to write the values to. This array will be reset/resized by this method. @param NumFloatsPerCurve The number of floats per curve. If larger than 1, the remaining floats (after the first one), will be set to 0. So if this is set to 4, you get an array like "0.75, 0, 0, 0", where 0.75 would represent the actual curve value.
- L152 _public prototype_ `static void RotationToTwoVectorsAsSixFloats(TArrayView<FTransform> Transforms, float* OutputBuffer);` — Batch convert a set of transform rotation quaternions into two column vectors.
- L159 _public prototype_ `static void RotationToTwoVectorsAsSixFloats(const FQuat& Rotation, float* SixFloatsOutputBuffer);` — Convert a rotation quaternion to two basis vectors, each represented as 3 floats, so 6 floats in total. @param Rotation The rotation quaternion to convert into the six float values. @param SixFloatsOutputBuffer The float buffer that we will write the 6 floats to. Make sure this buffer is at least 6 floats large.
- L168 _public prototype_ `virtual void ExtractBoneRotations(USkeletalMeshComponent* SkelMeshComponent, TArray<float>& OutRotations) const;` — Extract bone space rotations, as a float array. The number of output rotations are NumBones * 6, where the array contains a set two columns of a 3x3 rotation matrix values. components of the bone's bone space (local space) rotation quaternion. @param SkelMeshComponent The skeletal mesh component to sample from. @param OutRotations The output rotation values. This array will be resized internally.
- L174 _public prototype_ `int32 GetNumBaseMeshVertices() const;` — Get the number of imported vertices in the base mesh, which is the linear skinned skeletal mesh. @return The number of imported vertices in the base mesh.
- L181 _public prototype_ `void SetNumBaseVertices(int32 NumVerts);` — Set the number of vertices of our base mesh, which is the linear skinned skeletal mesh. The vertex count must be the same as in the DCC, so not the render mesh vertex count. @param NumVerts The number of vertices of our base mesh.
- L188 _public prototype_ `int32 GetNumTargetMeshVertices() const;` — Get the number of imported vertices in the target mesh, which is our training target/ground truth mesh. The number of vertices is the vertex count as in the DCC. @return The number of imported vertices in the target mesh.
- L195 _public prototype_ `void SetNumTargetVertices(int32 NumVerts);` — Set the number of target mesh vertices. The target mesh is our training target/ground truth mesh. The vertex count must be the same as in the DCC, so not the render mesh vertex count. @param NumVerts The number of vertices in the target mesh.
- L201 _public prototype_ `const FSoftObjectPath& GetSkeletalMesh() const;` — Get the path to the skeletal mesh that this deformer was trained on. @return The path to the skeletal mesh we used during training.
- L207 _public prototype_ `void SetSkeletalMesh(USkeletalMesh* InSkeletalMesh);` — Set skeletal mesh that we trained on. @param InSkeletalMesh A pointer to the skeletal mesh.
- L215 _public prototype_ `static void BuildCurveList(USkeletalMesh* InSkeletalMesh, TArray<FName>& OutCurveNames);` — Builds a list of available curves on the Skeletal Mesh provided, including its skeleton. This internally adds a merged set of curves that are found on the skeleton and the skeletal mesh itself. @param InSkeletalMesh The Skeletal Mesh to get the list of curves for. @param OutCurveNames The list of curve names that have been found.
- L223 _protected member_ `FSoftObjectPath SkeletalMesh;` — `UPROPERTY()` — The path to the skeletal mesh that this model was trained on.
- L228 _protected member_ `TArray<FString> BoneNameStrings_DEPRECATED;` — `UPROPERTY(meta = (DeprecatedProperty, DeprecationMessage = "Use BoneNames instead."))` — The list of bone names, but as string. This is deprecated since UE 5.2.
- L232 _protected member_ `TArray<FString> CurveNameStrings_DEPRECATED;` — `UPROPERTY(meta = (DeprecatedProperty, DeprecationMessage = "Use CurveNames instead."))` — The list of curve names, but as string. This is deprecated since UE 5.2.
- L241 _protected member_ `TArray<FName> BoneNames;` — `UPROPERTY()` — The name of each bone. The inputs to the network are in the order of this array. So if the array contains ["Root", "Child1", "Child2"] then the first bone transforms that we input to the neural network is the transform for "Root", followed by "Child1", followed by "Child2".
- L249 _protected member_ `TArray<FName> CurveNames;` — `UPROPERTY()` — The name of each curve. The inputs to the network are in the order of this array. So if the array contains ["Smile", "LeftEyeClosed", "RightEyeClosed"] then the first curve that we input to the neural network is the one for "Smile", followed by "LeftEyeClosed", followed by "RightEyeClosed".
- L253 _protected member_ `int32 NumBaseMeshVertices = 0;` — `UPROPERTY(AssetRegistrySearchable)` — Number of imported base mesh vertices, so not render vertices.
- L257 _protected member_ `int32 NumTargetMeshVertices = 0;` — `UPROPERTY()` — Number of imported target mesh vertices, so not render vertices.

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API MLDEFORMERFRAMEWORK_API`

### `Plugins/Animation/MLDeformer/MLDeformerFramework/Source/MLDeformerFramework/Public/MLDeformerMasking.h` (Public)


#### enum `EMLDeformerMaskingMode`  
`enum class EMLDeformerMaskingMode : uint8`  
_L10-17_
- reflection: `UENUM()`
- desc: Specifies whether a mask should be generated or not.
- L13 _public enumerator_ `Generated` — Use a generated mask, generated from the skinning weights of a set of bones.
- L16 _public enumerator_ `VertexAttribute` — Use a vertex attribute on the skeletal mesh. This can be a manually painted map.

#### struct `FMLDeformerMaskInfo`  
`struct FMLDeformerMaskInfo`  
_L27-43_
- reflection: `USTRUCT()`
- desc: Information needed to generate the mask for a specific bone. This includes a list of bone names. Each bone has a skinning influence mask. The final mask will be a merge of all the bone masks of bones listed inside this info struct. There will be an array of these structs, one for each bone.
- L34 _public member_ `TArray<FName> BoneNames;` — `UPROPERTY()` — The list of bone names that should be included in the mask generation.
- L38 _public member_ `EMLDeformerMaskingMode MaskMode = EMLDeformerMaskingMode::Generated;` — `UPROPERTY()` — The masking mode.
- L42 _public member_ `FName VertexAttributeName;` — `UPROPERTY()` — If the masking mode is set to VertexAttribute then we can check which attribute to use using this member.

### `Plugins/Animation/MLDeformer/MLDeformerFramework/Source/MLDeformerFramework/Public/MLDeformerModel.h` (Public)


#### enum `EMLDeformerMaskChannel`  
`enum class EMLDeformerMaskChannel : uint8`  
_L29-48_
- reflection: `UENUM()`
- desc: The channel to get the mask data from.
- L32 _public enumerator_ `Disabled` — Disable the weight mask.
- L35 _public enumerator_ `VertexColorRed` — The red vertex color channel.
- L38 _public enumerator_ `VertexColorGreen` — The green vertex color channel.
- L41 _public enumerator_ `VertexColorBlue` — The blue vertex color channel.
- L44 _public enumerator_ `VertexColorAlpha` — The alpha vertex color channel.
- L47 _public enumerator_ `VertexAttribute` — Use a set of vertex attributes on the skeletal mesh. You can create and editor those using the Skeletal Mesh editor plugin.

#### enum `EMLDeformerSkinningMode`  
`enum class EMLDeformerSkinningMode : int8`  
_L52-59_
- reflection: `UENUM()`
- desc: The skinning mode to use as base.
- L55 _public enumerator_ `Linear` — Linear blend skinning. This is the fastest at runtime, but can have a harder time reconstructing the ground truth.
- L58 _public enumerator_ `DualQuaternion` — Dual quaternion skinning. This is slower at runtime, but can result in better deformations.

#### class `UE::MLDeformer::FVertexMapBuffer`  
`class FVertexMapBuffer : public FVertexBufferWithSRV`  
_L70-89_
- inherits: `FVertexBufferWithSRV`
- desc: The vertex map, but in a GPU buffer. This map basically has a DCC vertex number for every render vertex. So if a cube requires 32 render vertices, there will be 32 ints inside this buffer, and each item in this buffer will in this specific example case contain a value between 0 and 7, as a cube has only 8 vertices.
- L78 _public function_ `void Init(const TArray<int32>& InVertexMap)` — Initialize the GPU buffer based on some array with integers. @param InVertexMap The array of ints we want to store on the GPU. The size of this array should be equal to the number of render vertices of the skeletal mesh.
- L85 _private prototype_ `virtual void InitRHI(FRHICommandListBase& RHICmdList) override;` — This does the actual render resource init, which means this creates and fills the buffer on the GPU. After it successfully initializes, it will empty our VertexMap member array to not store the data in both GPU memory and main memory.
- L88 _private member_ `TArray<int32> VertexMap;` — The array of integers we want to store on the GPU. This buffer will be emptied after successfully calling InitRHI.

#### class `UMLDeformerModel`  
`class UMLDeformerModel : public UObject , public IBoneReferenceSkeletonProvider`  
_L104-747_
- reflection: `UCLASS(MinimalAPI, Abstract)`
- inherits: `UObject,IBoneReferenceSkeletonProvider`
- desc: The ML Deformer runtime model base class. All models should be inherited from this class.
- L114 _public prototype_ `virtual ~UMLDeformerModel() = default;`
- L121 _public prototype_ `virtual void Init(UMLDeformerAsset* InDeformerAsset);` — Initialize the ML Deformer model. This will update the DeformerAsset and InputInfo properties. It internally calls CreateInputInfo if no InputInfo has been set yet. @param InDeformerAsset The deformer asset that this model will be part of.
- L127 _public prototype_ `virtual void InitGPUData();` — Initialize the data that should be stored on the GPU. This base class will store the VertexMap on the GPU by initializing the VertexMapBuffer member.
- L133 _public prototype_ `virtual UMLDeformerInputInfo* CreateInputInfo();` — Create the input info for this model. @return A pointer to the newly created input info.
- L140 _public prototype_ `virtual UMLDeformerModelInstance* CreateModelInstance(UMLDeformerComponent* Component);` — Create a new instance of this model, to be used in combination with a specific component. @param Component The ML Deformer component that will own this instance. @return A pointer to the model instance.
- L148 _public prototype_ `virtual FString GetDisplayName() const;` — Get the display name of this model. This will also define with what name this model will appear inside the UI. On default this will return the class name. @return The name of the model.
- L155 _public function_ `virtual bool DoesSupportBones() const` — Defines whether this model supports bone transforms as input or not. On default this is set to return true as most models have bone rotations as inputs to the neural network. @result Returns true when this model supports bones, or false otherwise.
- L162 _public function_ `virtual bool DoesSupportCurves() const` — Defines whether this model supports curves as inputs or not. A curve is just a single float value. On default this returns true. @result Returns true when this model supports curves, or false otherwise.
- L169 _public function_ `virtual bool DoesSupportLOD() const` — Check if this model supports LOD. When this returns false, the UI will not show options to setup the maximum number of LOD levels. @return Returns true if LOD is supported, otherwise false is returned, which means it only works on LOD0.
- L177 _public function_ `virtual bool IsNeuralNetworkOnGPU() const` — Check whether the neural network of this model should run on the GPU or not. This is false on default, which makes it a CPU based neural network. Some code internally that creates and initializes the neural network will use the return value of this method to mark it to be on CPU or GPU. @return Returns true if the neural network of this model should run on the GPU. False is returned when it should run on the CPU.
- L184 _public function_ `virtual FString GetDefaultDeformerGraphAssetPath() const` — Get the default deformer graph asset path that this model uses, or an empty string if it doesn't require any deformer graph. An example is some string like: "/DeformerGraph/Deformers/DG_LinearBlendSkin_Morph_Cloth_RecomputeNormals.DG_LinearBlendSkin_Morph_Cloth_RecomputeNormals". @return The asset path of the deformer graph that should be used on default. This can return an empty string when no deformer graph is required.
- L190 _public function_ `virtual int32 GetNumFloatsPerBone() const` — Get the number of floats used to represent a single bone rotation, used as input to the neural networks. @return The number of floats per individual bone.
- L196 _public function_ `virtual int32 GetNumFloatsPerCurve() const` — Get the number of floats used to represent a single bone rotation, used as input to the neural networks. @return The number of floats per individual bone.
- L199 _public function_ `virtual bool IsTrained() const` — Check whether this model has been trained or not.
- L206 _public function_ `const USkeletalMesh* GetSkeletalMesh() const` — Get the skeletal mesh that is used during training. You typically want to apply the ML Deformer on this specific skeletal mesh in your game as well. @return A pointer to the skeletal mesh.
- L207 _public function_ `USkeletalMesh* GetSkeletalMesh()`
- L213 _public function_ `void SetSkeletalMesh(USkeletalMesh* SkelMesh)` — Set the skeletal mesh that this deformer uses. @param SkelMesh The skeletal mesh.
- L224 _public prototype_ `virtual bool IsCompatibleDebugActor(const AActor* Actor, UMLDeformerComponent** OutDebugComponent = nullptr) const;` — Check if a given actor would be a compatible debugging actor. We check this by checking if it uses the same skeletal mesh and whether it uses the same ML Deformer asset. Debugging allows us to copy over the morph weights and pose of a character. But for that to be possible we need to make sure the other actor uses the same skeletal mesh and ML Deformer asset. This method helps us check that easily. @param Actor The actor to check compatibility with. @param OutDebugComponent A pointer to the ML Deformer component that we would be debugging. Can be set to nullptr to get it ignored. @return Returns true when the provided actor is compatible for debugging, otherwise false is returned.
- L237 _public function_ `const int32 GetMaxNumLODs() const` — Get the maximum number of LOD levels that we will generate. Some examples: A value of 1 means we only store one LOD, which means LOD0. A value of 2 means we support this ML Deformer on LOD0 and LOD1. A value of 3 means we support this ML Deformer on LOD0 and LOD1 and LOD2. We never generate more LOD levels for the ML Deformer than number of LOD levels in the Skeletal Mesh, so if this value is set to 100, while the Skeletal Mesh has only 4 LOD levels, we will only generate and store 4 ML Deformer LODs. The default value of 1 means we do not support this ML Deformer at LOD levels other than LOD0. @ return The maximum number of LOD levels we will generate.
- L245 _public function_ `virtual bool HasTrainingGroundTruth() const` — Check whether this model currently has a training mesh setup or not. For example if there is say a GeometryCache as target mesh, it could check whether that property is a nullptr or not. @return Returns true when the training target mesh has been selected, otherwise false is returned.
- L248 _public function_ `virtual void SampleGroundTruthPositions(float SampleTime, TArray<FVector3f>& OutPositions)` — `UE_DEPRECATED(5.5, "Please use SampleGroundTruthPositionAtFrame instead.")`
- L255 _public function_ `virtual void SampleGroundTruthPositionsAtFrame(int32 FrameIndex, TArray<FVector3f>& OutPositions)` — Sample the positions from the target (ground truth) mesh, at a specific frame. @param FrameIndex The frame number to sample the positions at. @param OutPositions The array that will receive the resulting vertex positions. This array will automatically be resized internally.
- L261 _public prototype_ `TArray<FName> GetVertexAttributeNames() const;` — `UFUNCTION()` — Get the attribute names of all vertex attributes on the skeletal mesh. This only includes ones that aren't auto generated by the engine.
- L266 _public prototype_ `virtual void UpdateCachedNumVertices();` — Update the cached number of vertices of both base and target meshes.
- L273 _public prototype_ `virtual void UpdateNumBaseMeshVertices();` — Update the cached number of vertices in the base mesh. The number of vertices should be the number of DCC vertices, so not the number of render vertices. This just updates the NumBaseMeshVerts property.
- L280 _public prototype_ `virtual void UpdateNumTargetMeshVertices();` — Update the cached number of target mesh vertices. Every model needs to implement this. The number of vertices should be the number of DCC vertices, so not the number of render vertices. This just updates the NumTargetMeshVerts property.
- L287 _public prototype_ `static int32 ExtractNumImportedSkinnedVertices(const USkeletalMesh* SkeletalMesh);` — Extract the number of imported (DCC) vertices from a skeletal mesh. @param SkeletalMesh The skeletal mesh to get the number of imported vertices for. @return The number of imported vertices, which is the vertex count as seen in the DCC.
- L290 _public prototype_ `void InvalidateMemUsage();` — Call this if you want it to recalculate the memory usage again after the tick has completed.
- L296 _public prototype_ `bool IsMemUsageInvalidated() const;` — Check whether we invalidated the memory usage. If this returns true, we need to recompute it. @return Returns true when we should make a call to UpdateMemoryUsage.
- L302 _public prototype_ `uint64 GetEditorAssetSizeInBytes() const;` — Get the estimated size of the asset on disk. This is the uncooked asset, which is larger than the cooked one. @return The size in bytes.
- L309 _public prototype_ `uint64 GetCookedAssetSizeInBytes() const;` — Get the estimated size of this asset on disk, when cooked. So this is the estimated size of the asset that will be packaged inside your project. @return The size in bytes.
- L315 _public prototype_ `uint64 GetMainMemUsageInBytes() const;` — Get the estimated main memory usage for this model. @return The number of bytes that this model uses.
- L321 _public prototype_ `uint64 GetGPUMemUsageInBytes() const;` — Get the estimated GPU memory usage for this model. @return The number of bytes that this model uses.
- L324 _public prototype_ `virtual void UpdateMemoryUsage();` — Force update the cached memory usage.
- L328 _public prototype_ `virtual void Serialize(FArchive& Archive) override;` — UObject overrides.
- L329 _public prototype_ `virtual void PreSave(FObjectPreSaveContext SaveContext) override;`
- L330 _public prototype_ `virtual void PostLoad() override;`
- L331 _public prototype_ `virtual void BeginDestroy() override;`
- L332 _public prototype_ `virtual bool IsReadyForFinishDestroy() override;`
- L333 _public prototype_ `virtual void GetAssetRegistryTags(FAssetRegistryTagsContext Context) const override;`
- L337 _public prototype_ `virtual USkeleton* GetSkeleton(bool& bInvalidSkeletonIsError, const IPropertyHandle* PropertyHandle) override;` — IBoneReferenceSkeletonProvider overrides.
- L344 _public prototype_ `UMLDeformerAsset* GetDeformerAsset() const;` — Get the ML deformer asset that this model is part of. @return A pointer to the ML deformer asset.
- L351 _public function_ `UMLDeformerInputInfo* GetInputInfo() const` — Get the input information, which is information about the inputs to the deformer. Inputs are things like bone transforms and curve values. @return A pointer to the input info object.
- L358 _public function_ `int32 GetNumBaseMeshVerts() const` — Get the number of vertices in the base mesh (linear skinned skeletal mesh). This is the number of vertices in the DCC, so not the render vertex count. @return The number of imported vertices inside linear skinned skeletal mesh.
- L365 _public function_ `int32 GetNumTargetMeshVerts() const` — Get the number of vertices of the target mesh. This is the number of vertices in the DCC, so not the render vertex count. @return The number of imported vertices inside the target mesh.
- L373 _public function_ `const TArray<int32>& GetVertexMap() const` — The mapping that maps from render vertices into dcc vertices. The length of this array is the same as the number of render vertices in the skeletal mesh. For a cube with 32 render vertices, the item values would be between 0..7 as in the dcc the cube has 8 vertices. @return A reference to the array that contains the DCC vertex number for each render vertex.
- L380 _public function_ `void SetVertexMap(const TArray<int32>& Map)` — Manually set the vertex map. This normally gets initialized automatically. @param Map The original vertex number indices for each render vertex. @see GetVertexMap.
- L387 _public function_ `const UE::MLDeformer::FVertexMapBuffer& GetVertexMapBuffer() const` — Get the GPU buffer of the VertexMap. @return A reference to the GPU buffer resource object that holds the vertex map. @see GetVertexMap
- L394 _public function_ `FMLDeformerReinitModelInstancesDelegate& GetReinitModelInstanceDelegate()` — Get the delegate which will be called when to inform when the model instance needs to be reinitialized. The ML Deformer component will hook into this for example. This is broadcast when something changes in the structure, such as when training finished and the neural network changed.
- L401 _public prototype_ `void SetRecoverStrippedDataAfterCook(bool bRecover);` — Specify whether we want to recover stripped data that is removed from this model when cooking. Examples of this data could be the raw uncompressed vertex deltas of all morph targets. On default we strip the data, save the cooked asset, and then recover the stripped data again. But using this method you can disable that, by setting it to false. Generally we only want to disable this during some automated tests.
- L407 _public prototype_ `bool GetRecoverStrippedDataAfterCook() const;` — Check whether we want to recover stripped data that is removed from this model when cooking. Examples of this data could be the raw uncompressed vertex deltas of all morph targets. On default we strip the data, save the cooked asset, and then recover the stripped data again. But some automated cooking tests might want this disabled.
- L410 _public function_ `const TArray<FString>& GetTrainingDeviceList() const` — `UFUNCTION()`
- L413 _public function_ `const FString& GetTrainingDevice() const` — `UFUNCTION(BlueprintCallable, Category = "Training")`
- L416 _public prototype_ `void SetTrainingDevice(const FString& DeviceName);` — `UFUNCTION()`
- L417 _public function_ `void SetTrainingDeviceToCpu()`
- L418 _public function_ `void SetTrainingDeviceList(const TArray<FString>& Devices)`
- L423 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;` — UObject overrides.
- L424 _public prototype_ `virtual void PostTransacted(const FTransactionObjectEvent& Event) override;`
- L425 _public prototype_ `virtual void PreEditUndo() override;`
- L426 _public prototype_ `virtual void PostEditUndo() override;`
- L435 _public prototype_ `void InitVertexMap();` — Initialize the vertex map. This will grab the skeletal mesh imported model and copy over the imported mapping from there. This will make sure the VertexMap member is initialized. @see GetVertexMap
- L441 _public function_ `FMLDeformerModelOnPostEditProperty& OnPostEditChangeProperty()` — The delegate that gets fired when a property value changes. @return A reference to the delegate.
- L447 _public function_ `FMLDeformerModelOnPostTransacted& OnPostTransacted()` — Get the delegate that gets fired when a transaction is done on this model. @return A reference to the delegate.
- L453 _public function_ `FMLDeformerModelOnPreEditUndo& OnPreEditUndo()` — Get the delegate that gets fired before we do undo. @return A reference to the delegate.
- L459 _public function_ `FMLDeformerModelOnPostEditUndo& OnPostEditUndo()` — Get the delegate that gets fired after we do undo. @return A reference to the delegate.
- L468 _public function_ `UMLDeformerVizSettings* GetVizSettings() const` — Get the visualization settings for this model. These settings are only used in the editor. Visualization settings contain settings for the left side of the ML Deformer asset editor, containing settings like what the mesh spacing is, whether to draw labels, what the test anim sequence is, etc. @return A pointer to the visualization settings. You can cast this to the type specific for your model, in case you inherited from the UMLDeformerVizSettings base class. This never return a nullptr.
- L476 _public function_ `int32 GetTrainingFrameLimit() const` — Get the maximum number of training frames to use during training. Your training anim sequence might contain say 10000 frames, but for quickly iterating you might want to train on only 2000 frames instead. You can do this by setting the maximum training frames to 2000. @return The max number of frames to use during training.
- L483 _public function_ `void SetTrainingFrameLimit(int32 MaxNumFrames)` — Set the maximum number of frames to train on. For example if your training data has 10000 frames, but you wish to only train on 2000 frames, you can set this to 2000. @param MaxNumFrames The maximum number of frames to train on.
- L493 _public function_ `const FTransform& GetAlignmentTransform() const` — Get the target mesh alignment transformation. This is a transformation that is applied to the vertex positions of the target mesh, before we calculate the deltas between the linear skinned mesh and the target mesh. This is useful when you imported target mesh that isn't scaled the same, or perhaps it is rotated 90 degrees over the x axis. The alignment transform is then used to correct this and align both base and target mesh. @return The alignment transformation. When set to Identity it will not do anything, which is its default.
- L500 _public function_ `void SetAlignmentTransform(const FTransform& Transform)` — Set the alignment transform, which is the transform applied to the target mesh vertices, before calculating the deltas. @param Transform The transformation to apply. @see GetAlignmentTransform.
- L512 _public function_ `TArray<FBoneReference>& GetBoneIncludeList()` — Get the list of bones that we configured to be included during training. A bone reference is basically just a name of a bone. This can be different from the bone list inside the InputInfo property though. Please keep in mind that the BoneIncludeList is what is setup in the UI, but the InputInfo contains the actual list of what we trained on, so what we use during inference. A user could change this bone list after they trained a model, in which case the input info and this bone include list will contain different items. @return The list of bones that should be included when performing the next training session.
- L513 _public function_ `const TArray<FBoneReference>& GetBoneIncludeList() const`
- L520 _public function_ `void SetBoneIncludeList(const TArray<FBoneReference>& List)` — Set the list of bones that should be included during training. If the list is empty, all bones will be included. @param List The list of bones to include.
- L532 _public function_ `TArray<FMLDeformerCurveReference>& GetCurveIncludeList()` — Get the list of curves that we configured to be included during training. A curve reference is basically just a name of a curve. This can be different from the curve list inside the InputInfo property though. Please keep in mind that the CurveIncludeList is what is setup in the UI, but the InputInfo contains the actual list of what we trained on, so what we use during inference. A user could change this curve list after they trained a model, in which case the input info and this curve include list will contain different items. @return The list of curves that should be included when performing the next training session.
- L533 _public function_ `const TArray<FMLDeformerCurveReference>& GetCurveIncludeList() const`
- L540 _public function_ `void SetCurveIncludeList(const TArray<FMLDeformerCurveReference>& List)` — Set the list of curves that should be included during training. If the list is empty, all curves will be included. @param List The list of curves to include.
- L547 _public function_ `void SetVizSettings(UMLDeformerVizSettings* VizSettingsObject)` — Set the visualization settings object. You need to call this in the constructor of your model. @param VizSettings The visualization settings object for this model.
- L554 _public function_ `UMLDeformerTrainingDataProcessorSettings* GetTrainingDataProcessorSettings() const` — Get the settings that have been configured inside the Training Data Processor tool. These settings are stored as part of the ML Deformer model. When this hasn't been set up it will return a nullptr. @return A pointer to the training data processor settings, or a nullptr in case no settings have been setup before.
- L560 _public function_ `void SetTrainingDataProcessorSettings(UMLDeformerTrainingDataProcessorSettings* Settings)` — Set the object that is used to store the settings for the training data processor tool. @param Settings The training settings, which will be saved along with the ML Deformer model.
- L563 _public function_ `static FName GetSkeletalMeshPropertyName()` — Get property names.
- L564 _public function_ `static FName GetAlignmentTransformPropertyName()`
- L565 _public function_ `static FName GetBoneIncludeListPropertyName()`
- L566 _public function_ `static FName GetCurveIncludeListPropertyName()`
- L567 _public function_ `static FName GetMaxTrainingFramesPropertyName()`
- L568 _public function_ `static FName GetMaxNumLODsPropertyName()`
- L569 _public function_ `static FName GetTrainingDevicePropertyName()`
- L578 _protected function_ `void SetInputInfo(UMLDeformerInputInfo* Input)` — Set the training input information. @param Input A pointer to the input information object. @see CreateInputInfo
- L588 _protected prototype_ `void FloatArrayToVector3Array(const TArray<float>& FloatArray, TArray<FVector3f>& OutVectorArray);` — Convert an array of floats to an array of Vector3's. A requirement is that the number of items in the float array is a multiple of 3 (xyz). The order of the float items must be like this: (x, y, z, x, y, z, x, y, z, ...). The OutVectorArray will be automatically resized internally. @param FloatArray The array of floats to build an array of Vector3's for. @param OutVectorArray The array that will contain the vectors instead of floats.
- L595 _protected function_ `void SetNumBaseMeshVerts(int32 NumVerts)` — Set the number of vertices in the base mesh. This is the number of imported (dcc) vertices, so not render vertices. @param NumVerts The number of vertices.
- L602 _protected function_ `void SetNumTargetMeshVerts(int32 NumVerts)` — Set the number of vertices in the target mesh. This is the number of imported (dcc) vertices, so not render vertices. @param NumVerts The number of vertices.
- L607 _protected member_ `bool bInvalidateMemUsage = true;` — Should we recalculate the memory usage?
- L610 _protected member_ `uint64 MemUsageInBytes = 0;` — Estimated main memory usage.
- L613 _protected member_ `uint64 EditorAssetSizeInBytes = 0;` — Estimated editor asset size.
- L616 _protected member_ `uint64 CookedAssetSizeInBytes = 0;` — Estimated cooked asset size.
- L619 _protected member_ `uint64 GPUMemUsageInBytes = 0;` — Estimated GPU memory usage.
- L628 _protected member_ `TSoftObjectPtr<UAnimSequence> AnimSequence_DEPRECATED;` — `UPROPERTY(meta=(DeprecatedProperty, DeprecationMessage="Use the training input anims instead."))` — The animation sequence to apply to the base mesh. This has to match the animation of the target mesh's geometry cache. Internally we force the Interpolation property for this motion to be "Step".
- L633 _private member_ `TObjectPtr<UMLDeformerAsset> DeformerAsset = nullptr;` — The deformer asset that this model is part of.
- L636 _private member_ `FMLDeformerModelOnPostEditProperty PostEditPropertyDelegate;` — The delegate that gets fired when a property is being modified.
- L639 _private member_ `FMLDeformerModelOnPostTransacted PostTransactedDelegate;` — The delegate to capture PostTransacted on this model uobject.
- L642 _private member_ `FMLDeformerModelOnPreEditUndo PreEditUndoDelegate;` — The delegate to capture PreEditUndo on this model uobject.
- L645 _private member_ `FMLDeformerModelOnPostEditUndo PostEditUndoDelegate;` — The delegate to capture PostEditUndo on this model uobject.
- L648 _private member_ `UE::MLDeformer::FVertexMapBuffer VertexMapBuffer;` — GPU buffers for Vertex Map.
- L651 _private member_ `FRenderCommandFence RenderResourceDestroyFence;` — Fence used in render thread cleanup on destruction.
- L654 _private member_ `FMLDeformerReinitModelInstancesDelegate ReinitModelInstanceDelegate;` — Delegate used to trigger reinitialization of the model instance.
- L658 _private member_ `int32 NumBaseMeshVerts = 0;` — `UPROPERTY()` — Cached number of skeletal mesh vertices.
- L662 _private member_ `int32 NumTargetMeshVerts = 0;` — `UPROPERTY()` — Cached number of target mesh vertices.
- L666 _private member_ `FString TrainingDevice;` — `UPROPERTY(EditAnywhere, AdvancedDisplay, Category = "Training Settings", meta = (GetOptions = "GetTrainingDeviceList", NoResetToDefault))` — The device used for training. On default it will init to Cuda's preferred device, or Cpu if no such device present.
- L669 _private member_ `TArray<FString> TrainingDeviceList;` — The list of training devices that will show in the combo box in the UI.
- L683 _private member_ `int32 MaxNumLODs = 1;` — `UPROPERTY(EditAnywhere, Category = "LOD Generation Settings", meta = (ClampMin = "1"))` — How many Skeletal Mesh LOD levels should we generate MLD lods for at most? Some examples: A value of 1 means we only store one LOD, which means LOD0. A value of 2 means we support this ML Deformer on LOD0 and LOD1. A value of 3 means we support this ML Deformer on LOD0 and LOD1 and LOD2. We never generate more LOD levels for the ML Deformer than number of LOD levels in the Skeletal Mesh, so if this value is set to 100, while the Skeletal Mesh has only 4 LOD levels, we will only generate and store 4 ML Deformer LODs. The default value of 1 means we do not support this ML Deformer at LOD levels other than LOD0. When cooking, the console variable "sg.MLDeformer.MaxLODLevelsOnCook" can be used to set the maximum value per device or platform.
- L689 _private member_ `TObjectPtr<UMLDeformerInputInfo> InputInfo;` — `UPROPERTY()` — The information about the neural network inputs. This contains things such as bone names and curve names.
- L693 _private member_ `TArray<int32> VertexMap;` — `UPROPERTY()` — This is an index per vertex in the mesh, indicating the imported vertex number from the source asset.
- L697 _private member_ `TObjectPtr<UMLDeformerTrainingDataProcessorSettings> TrainingDataProcessorSettings;` — `UPROPERTY()` — The settings for the training data processor.
- L701 _private member_ `TObjectPtr<USkeletalMesh> SkeletalMesh;` — `UPROPERTY(EditAnywhere, Category = "Base Mesh")` — The skeletal mesh that represents the linear skinned mesh.
- L705 _private member_ `TObjectPtr<UMLDeformerVizSettings> VizSettings;` — `UPROPERTY()`
- L710 _private member_ `bool bIncludeBones_DEPRECATED = true;` — `UE_DEPRECATED(5.3, "This property has been removed.")` — `UPROPERTY(meta = (DeprecatedProperty, DeprecationMessage = "This property has been removed and isn't used anymore."))` — Specifies whether bone transformations should be included as inputs during the training process.
- L715 _private member_ `bool bIncludeCurves_DEPRECATED = false;` — `UE_DEPRECATED(5.3, "This property has been removed.")` — `UPROPERTY(meta = (DeprecatedProperty, DeprecationMessage = "This property has been removed and isn't used anymore."))` — Specifies whether curve values (a float per curve) should be included as inputs during the training process.
- L719 _private member_ `FTransform AlignmentTransform = FTransform::Identity;` — `UPROPERTY(EditAnywhere, Category = "Inputs", DisplayName = "Target Alignment Transform")` — The transform that aligns the Geometry Cache to the SkeletalMesh. This will mostly apply some scale and a rotation, but no translation.
- L723 _private member_ `TArray<FBoneReference> BoneIncludeList;` — `UPROPERTY(meta = (EditCondition = "bIncludeBones"))` — The bones to include during training. When none are provided, all bones of the Skeleton will be included.
- L727 _private member_ `TArray<FMLDeformerCurveReference> CurveIncludeList;` — `UPROPERTY(meta = (EditCondition = "bIncludeCurves"))` — The curves to include during training. When none are provided, all curves of the Skeleton will be included.
- L731 _private member_ `int32 MaxTrainingFrames = 1000000;` — `UPROPERTY(EditAnywhere, Category = "Training Settings", meta = (ClampMin = "1"))` — The maximum numer of training frames (samples) to train on. Use this to train on a sub-section of your full training data.
- L739 _private member_ `float DeltaCutoffLength_DEPRECATED = 30.0f;` — `UE_DEPRECATED(5.5, "This property has been removed.")` — `UPROPERTY(meta = (DeprecatedProperty, DeprecationMessage = "This property has been removed and isn't used anymore."))` — Sometimes there can be some vertices that cause some issues that cause deltas to be very long. We can ignore these deltas by setting a cutoff value. Deltas that are longer than the cutoff value (in units), will be ignored and set to zero length.
- L745 _private member_ `bool bRecoverStrippedDataAfterCook = true;` — Do we want to recover stripped data at the end of the Serialize call during cook? This is enabled on default, but some automated tests might disable this.

#### Free symbols / members of external scopes

- L18 _macro_ `#define UE_API MLDEFORMERFRAMEWORK_API`
- L62 _namespace_ `namespace UE`
- L62 _namespace_ `namespace MLDeformer` (scope `UE`)
- L94 _delegate_ `DECLARE_EVENT_OneParam(UMLDeformerModel, FMLDeformerModelOnPostEditProperty, FPropertyChangedEvent&) DECLARE_EVENT_OneParam(UMLDeformerModel, FMLDeformerModelOnPostTransacted, const FTransactionObjectEvent&) DECLARE_EVENT(UMLDeformerModel, FMLDeformerModelOnPreEditUndo) DECLARE_EVENT(UMLDeformerModel, FMLDeformerModelOnPostEditUndo) UCLASS(MinimalAPI, Abstract) class UMLDeformerModel : public UObject , public IBoneReferenceSkeletonProvider { GENERATED_BODY() public: DECLARE_MULTICAST_DELEGATE(FMLDeformerReinitModelInstancesDelegate) virtual ~UMLDeformerModel() = default; virtual void Init(UMLDeformerAsset* InDeformerAsset); virtual void InitGPUData(); virtual UMLDeformerInputInfo* CreateInputInfo();` — DEPRECATED: Use FMLDeformerReinitModelInstancesDelegate instead.
- L95 _delegate_ `DECLARE_EVENT_OneParam(UMLDeformerModel, FMLDeformerModelOnPostTransacted, const FTransactionObjectEvent&) DECLARE_EVENT(UMLDeformerModel, FMLDeformerModelOnPreEditUndo) DECLARE_EVENT(UMLDeformerModel, FMLDeformerModelOnPostEditUndo) UCLASS(MinimalAPI, Abstract) class UMLDeformerModel : public UObject , public IBoneReferenceSkeletonProvider { GENERATED_BODY() public: DECLARE_MULTICAST_DELEGATE(FMLDeformerReinitModelInstancesDelegate) virtual ~UMLDeformerModel() = default; virtual void Init(UMLDeformerAsset* InDeformerAsset); virtual void InitGPUData(); virtual UMLDeformerInputInfo* CreateInputInfo();`
- L96 _delegate_ `DECLARE_EVENT(UMLDeformerModel, FMLDeformerModelOnPreEditUndo) DECLARE_EVENT(UMLDeformerModel, FMLDeformerModelOnPostEditUndo) UCLASS(MinimalAPI, Abstract) class UMLDeformerModel : public UObject , public IBoneReferenceSkeletonProvider { GENERATED_BODY() public: DECLARE_MULTICAST_DELEGATE(FMLDeformerReinitModelInstancesDelegate) virtual ~UMLDeformerModel() = default; virtual void Init(UMLDeformerAsset* InDeformerAsset); virtual void InitGPUData(); virtual UMLDeformerInputInfo* CreateInputInfo(); /**`
- L97 _delegate_ `DECLARE_EVENT(UMLDeformerModel, FMLDeformerModelOnPostEditUndo) UCLASS(MinimalAPI, Abstract) class UMLDeformerModel : public UObject , public IBoneReferenceSkeletonProvider { GENERATED_BODY() public: DECLARE_MULTICAST_DELEGATE(FMLDeformerReinitModelInstancesDelegate) virtual ~UMLDeformerModel() = default; virtual void Init(UMLDeformerAsset* InDeformerAsset); virtual void InitGPUData(); virtual UMLDeformerInputInfo* CreateInputInfo(); /** * Create a new instance of this model, to be used in combination with a specific component.`
- L112 _delegate_ `DECLARE_MULTICAST_DELEGATE(FMLDeformerReinitModelInstancesDelegate) virtual ~UMLDeformerModel() = default;` — Delegate used to signal that the UMLDeformerModelInstance should be reinitialized. The ML Deformer component will connect to this to be informed about needing to reinit the instance.

### `Plugins/Animation/MLDeformer/MLDeformerFramework/Source/MLDeformerFramework/Public/MLDeformerModelInstance.h` (Public)


#### class `UMLDeformerModelInstance`  
`class UMLDeformerModelInstance : public UObject`  
_L35-282_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject`
- desc: An instance of the ML Deformer model. The ML Deformer model contains shared data, while this instance contains data unique to the actor it is being applied to. So if you have 1 ML Deformer model, applied to 100 enemy actors, you will get 100 ML Deformer Model Instance objects. The model instance is created and managed by the ML Deformer component. The main task of the model instance is to feed the neural network with the right input values and run the neural network inference at runtime, and possibly do something with the output.
- L41 _public prototype_ `UMLDeformerModelInstance() = default;`
- L44 _public prototype_ `virtual void BeginDestroy() override;` — UObject overrides.
- L45 _public prototype_ `virtual bool IsReadyForFinishDestroy() override;`
- L54 _public prototype_ `virtual void Init(USkeletalMeshComponent* SkelMeshComponent);` — Initialize the model instance. This internally builds the structures to quickly grab bone transforms. If you override this method, you probably also want to call the Init of this base class inside your overloaded method. @param SkelMeshComponent The skeletal mesh component that we will grab bone transforms and curve values from.
- L61 _public function_ `virtual void PostMLDeformerComponentInit()` — Initialize this model, after the ML deformer component has been initialized. This is a post-step after component initialization. It can be used to register things such as external morph target sets that are generated by this model.
- L69 _public prototype_ `virtual void Tick(float DeltaTime, float ModelWeight);` — Update the deformer instance. If you use a neural network, this should provide inputs to the neural network. @param DeltaTime The delta time since the last frame, in seconds. @param ModelWeight The weight of the model, between 0 and 1, where 0 means it has no influence, and 1 means it is fully active.
- L77 _public function_ `virtual void PostTick(bool bExecuteCalled)` — Executed at the end of the tick. This is always executed when Tick is called, also if the model weight is 0 etc. When the model weight is tiny or setting the inputs failed, the Execute function wasn't called during Tick. The parameter that is passed to this method will let you know whether Execute got called or not. @param bExecuteCalled This is true when we called Execute, otherwise it is false.
- L87 _public prototype_ `virtual FString CheckCompatibility(USkeletalMeshComponent* InSkelMeshComponent, bool bLogIssues=false);` — Check whether the deformer is compatible with a given skeletal mesh component. This internally also edits the value returned by GetCompatibilityErrorText(). @param InSkelMeshComponent The skeletal mesh component to check compatibility with. @param bLogIssues Set to true to automatically log any compatibility errors. @return Returns the error string. When the returned string is empty, there were no errors and thus the specified skeletal mesh component is compatible.
- L95 _public prototype_ `virtual bool IsValidForDataProvider() const;` — Check if we are in a valid state for the deformer graph's data provider. In the base class this will check whether the neural network is valid, if the vertex map buffer is valid and whether the neural network instance handle is valid. @return Returns true if the data provider in would be in a valid state, otherwise false is returned.
- L105 _public prototype_ `virtual void CopyDataFromCurrentDebugActor();` — Copy over data from the debug actor, if any is used. You can get the debug actor using UMLDeformerComponent::GetDebugActor(). This should make calls to the CopyDataFromDebugActor, which takes the actor pointer and ML Deformer component as parameters. Compatibility checks between the debug actor and the current model instance should be done inside this method. This could for example copy over morph target weights etc.
- L113 _public function_ `virtual void CopyDataFromDebugActor(const AActor* DebugActor, const UMLDeformerComponent* DebugMLDeformerComponent)` — Copy data from a specific debug actor. This method already assumes DebugActor and MLDeformerComponent are compatible with the current model instance. @param DebugActor The debug actor object to copy data from. @param DebugMLDeformerComponent The debug ML Deformer component to copy data from.
- L119 _public prototype_ `void SetGroundTruthFrameIndex(int32 FrameIndex);` — Set the frame index that we use to sample the ground truth vertex positions when showing the heat map in ground truth mode. @param FrameIndex The frame number in the geometry cache that we sample the ground truth positions from.
- L125 _public prototype_ `int32 GetGroundTruthFrameIndex() const;` — Get the frame index that we use to sample the ground truth vertex positions when showing the heat map in ground truth mode. @return The frame number inside the geometry cache that we sample the ground truth positions from.
- L132 _public prototype_ `bool IsCompatible() const;` — Is the deformer asset used compatible with the skeletal mesh component used during the Init call? @return True if compatible, false if not.
- L138 _public prototype_ `const FString& GetCompatibilityErrorText() const;` — Get the compatibility error text. This will be a non-empty string in case IsCompatible() return false. @return Returns the string containing more information about the reasons for compatibility issues.
- L144 _public prototype_ `USkeletalMeshComponent* GetSkeletalMeshComponent() const;` — Get the skeletal mesh component we're working with. @return A pointer to the skeletal mesh component.
- L147 _public prototype_ `void UpdateCompatibilityStatus();` — Update the compatibility status, as returned by IsCompatible() and GetCompatibilityErrorText().
- L150 _public prototype_ `UMLDeformerModel* GetModel() const;` — Get the model that this is an instance of.
- L153 _public prototype_ `void SetModel(UMLDeformerModel* InModel);` — Set the deformer model that this is an instance of.
- L156 _public prototype_ `void SetHasPostInitialized(bool bHasInitialized);` — Set whether we had a successful call to UMLDeformerModel::PostMLDeformerComponentInit.
- L159 _public prototype_ `bool HasPostInitialized() const;` — Check whether we already called UMLDeformerModel::PostMLDeformerComponentInit.
- L165 _public prototype_ `UMLDeformerComponent* GetMLDeformerComponent() const;` — Get the ML Deformer component that this instance is part of. @return A pointer to the ML Deformer component.
- L173 _public prototype_ `USkeletalMeshComponent* GetFinalSkeletalMeshComponent() const;` — Get the skeletal mesh component to get transforms from etc. If we are debugging this will return the debugged skeletal mesh component, otherwise the skel mesh component of our own actor is returned. @return The skeletal mesh component to grab input data from.
- L180 _protected prototype_ `void DrawDebugInputPoses();` — Draw the input poses that are currently input to this instance. This is linked to the "MLDeformer.DebugDrawInputPoses" console command.
- L191 _protected prototype_ `virtual int64 SetNeuralNetworkInputValues(float* InputData, int64 NumInputFloats);` — Update the neural network input values directly inside its input tensor. This will copy over the bone transforms (and possibly morph and curve weights) into this flat array. @param InputData The buffer of floats to write the input values to. @param NumInputFloats The number of floats of the InputData buffer. Do not write more than this number of floats to the InputData buffer. @return Returns the new buffer element index. For example if there were 2 bones and 3 curves, and each bone takes 6 inputs and each curve takes one input, then after calling this base class method, it will return 15 (2*6 + 3*1). You could call this base class method and then write data after that, starting from the offset that is returned.
- L201 _protected function_ `virtual bool SetupInputs()` — Setup the neural network for this frame. This has to perform compatibility checks, valid pointer checks, and call the SetNeuralNetworkInputValues. After this method is executed, the neural network should be ready to execute. The UMLDeformerModelInstance::Tick method internally calls both the SetupNeuralNetworkForFrame and RunNeuralNetwork methods. @return Returns true when the setup is done correctly and the neural network is ready to be executed. Otherwise false is returned, which can happen when the NeuralNetwork pointer is invalid, when the model is not set, when the network is not compatible, etc.
- L208 _protected function_ `virtual void Execute(float ModelWeight)` — Execute the model instance, which can run the neural network inference in case the model uses a neural network. This already assumes that compatibility checks are done, and that the network inputs are set etc. @param ModelWeight The weight of the model, must be between 0 and 1.
- L216 _protected function_ `virtual void HandleZeroModelWeight()` — Handle when the model weight is zero. This is called when ticking with a zero model weight. The SetupNeuralNetworkForFrame and RunNeuralNetwork calls are skipped in case we have a model weight near zero, as optimization. Instead, this method is called in that case. It can be used to for example set morph target weights to zero.
- L225 _protected prototype_ `virtual int64 SetBoneTransforms(float* OutputBuffer, int64 OutputBufferSize, int64 StartIndex);` — Set the bone transformations inside a given output buffer, starting from a given StartIndex. @param OutputBuffer The buffer we need to write the transformations to. @param OutputBufferSize The number of floats inside the output buffer. Can be used to detect buffer overflows. @param StartIndex The index where we want to start writing the transformations to. @return The new start index into the output buffer, to be used when you write more data after this.
- L234 _protected prototype_ `virtual int64 SetCurveValues(float* OutputBuffer, int64 OutputBufferSize, int64 StartIndex);` — Set the animation curve values inside a given output buffer, starting from a given StartIndex. @param OutputBuffer The buffer we need to write the weights to. @param OutputBufferSize The number of floats inside the output buffer. Can be used to detect buffer overflows. @param StartIndex The index where we want to start writing the weights to. @return The new start index into the output buffer, to be used when you write more data after this.
- L239 _protected prototype_ `void UpdateBoneTransforms();` — Updates the bone transforms array.
- L246 _protected prototype_ `bool HasValidTransforms() const;` — Check whether we have valid transforms in the skeletal mesh component. When this returns false, we can't really execute the deformer. @return Returns true if the skeletal mesh component, or its leader component has non-empty transform buffers.
- L250 _protected member_ `FRenderCommandFence RenderCommandFence;` — The fence that let's us wait for all render commands to finish, before we continue.
- L254 _protected member_ `TObjectPtr<UMLDeformerModel> Model = nullptr;` — `UPROPERTY(Transient)` — The ML Deformer model that this is an instance of.
- L258 _protected member_ `TObjectPtr<USkeletalMeshComponent> SkeletalMeshComponent;` — `UPROPERTY(Transient)` — The skeletal mesh component we work with. This is mainly used for compatibility checks.
- L261 _protected member_ `TArray<FTransform> TrainingBoneTransforms;` — The cached current local space bone transforms for the current frame.
- L264 _protected member_ `TArray<FTransform> DebugBoneSpaceTransforms;` — The debug bone space transforms.
- L267 _protected member_ `TArray<int32> AssetBonesToSkelMeshMappings;` — Maps the ML deformer asset bone index to a skeletal mesh component bone index.
- L270 _protected member_ `FString ErrorText;` — The compatibility error text, in case bIsCompatible is false.
- L273 _protected member_ `bool bIsCompatible = false;` — Are the deformer asset and the used skeletal mesh component compatible?
- L276 _protected member_ `bool bHasPostInitialized = false;` — Has this instance had a successful UMLDeformerModel::PostMLDeformerComponentInit call?
- L280 _protected member_ `int32 GroundTruthFrameIndex = 0;` — The current ground truth frame index. This is used for displaying heatmaps versus the ground truth accurately.

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API MLDEFORMERFRAMEWORK_API`
- L18 _delegate_ `DECLARE_STATS_GROUP(TEXT("MLDeformer"), STATGROUP_MLDeformer, STATCAT_`
- L19 _delegate_ `DECLARE_CYCLE_STAT_EXTERN(TEXT("ML Deformer Inference"), STAT_MLDeformerInference, STA`
- L21 _namespace_ `namespace UE`
- L21 _namespace_ `namespace MLDeformer` (scope `UE`)
- L23 _externvar_ `extern TAutoConsoleVariable<bool> CVarMLDeformerDebugDrawInputPoses;` (scope `UE::MLDeformer`)

### `Plugins/Animation/MLDeformer/MLDeformerFramework/Source/MLDeformerFramework/Public/MLDeformerModule.h` (Public)


#### class `UE::MLDeformer::FMLDeformerModule`  
`class FMLDeformerModule : public IModuleInterface`  
_L19-32_
- inherits: `IModuleInterface`
- desc: The runtime module for the ML Deformer.
- L24 _public prototype_ `void StartupModule() override;` — IModuleInterface overrides.
- L25 _public prototype_ `void ShutdownModule() override;`
- L28 _public function_ `const IConsoleVariable& GetMaxLODLevelsOnCookCVar() const`
- L31 _private member_ `IConsoleVariable* CVarMLDeformerMaxLODLevels = nullptr;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API MLDEFORMERFRAMEWORK_API`
- L12 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogMLDeformer, Log, All);` — The log category for the ML Deformer framework.
- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace MLDeformer` (scope `UE`)

### `Plugins/Animation/MLDeformer/MLDeformerFramework/Source/MLDeformerFramework/Public/MLDeformerMorphModel.h` (Public)


#### class `UMLDeformerMorphModel`  
`class UMLDeformerMorphModel : public UMLDeformerGeomCacheModel`  
_L22-373_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMLDeformerGeomCacheModel`
- desc: The morph model base class. This is the base class for models that generate and drive morph targets. Use this in combination with UMLDeformerMorphModelInstance or inherited classes.
- L28 _public prototype_ `UMLDeformerMorphModel(const FObjectInitializer& ObjectInitializer);`
- L31 _public function_ `virtual bool IsNeuralNetworkOnGPU() const override` — UMLDeformerModel overrides.
- L32 _public function_ `virtual bool DoesSupportLOD() const override` — We support deformations in different LOD levels.
- L33 _public prototype_ `virtual void Serialize(FArchive& Archive) override;`
- L34 _public prototype_ `virtual UMLDeformerInputInfo* CreateInputInfo() override;`
- L35 _public prototype_ `virtual UMLDeformerModelInstance* CreateModelInstance(UMLDeformerComponent* Component) override;`
- L37 _public prototype_ `virtual void UpdateMemoryUsage() override;`
- L38 _public prototype_ `virtual void FinalizeMorphTargets();`
- L39 _public prototype_ `bool HasRawMorph() const;`
- L44 _public prototype_ `virtual void BeginDestroy() override;` — UObject overrides.
- L45 _public prototype_ `virtual bool IsReadyForFinishDestroy() override;`
- L46 _public prototype_ `virtual void PostLoad() override;`
- L47 _public prototype_ `virtual void GetAssetRegistryTags(FAssetRegistryTagsContext Context) const override;`
- L50 _public prototype_ `int32 GetNumMorphTargets(int32 LOD) const;`
- L51 _public function_ `uint64 GetCompressedMorphDataSizeInBytes() const`
- L52 _public function_ `uint64 GetUncompressedMorphDataSizeInBytes() const`
- L54 _public function_ `float GetMorphDeltaZeroThreshold() const`
- L55 _public function_ `float GetMorphCompressionLevel() const`
- L56 _public function_ `float GetMaxMorphTargetErrorInUnits() const`
- L57 _public function_ `bool GetIncludeMorphTargetNormals() const`
- L58 _public function_ `EMLDeformerMaskChannel GetMaskChannel() const`
- L59 _public function_ `bool GetInvertMaskChannel() const`
- L60 _public function_ `bool GetHasOnlyEmptyMorphs() const`
- L63 _public prototype_ `bool CanDynamicallyUpdateMorphTargets() const;` — `UFUNCTION(BlueprintPure, Category = "MLDeformerMorphModel")`
- L65 _public function_ `void SetMorphDeltaZeroThreshold(float Threshold)`
- L66 _public function_ `void SetMorphCompressionLevel(float Tolerance)`
- L67 _public function_ `void SetIncludeMorphTargetNormals(bool bInclude)`
- L68 _public function_ `void SetMaskChannel(EMLDeformerMaskChannel Channel)`
- L69 _public function_ `void SetInvertMaskChannel(bool bInvert)`
- L70 _public function_ `void SetClampMorphTargetsWeights(bool bEnabled)`
- L71 _public function_ `void SetHasOnlyEmptyMorphs(bool bOnlyEmpty)`
- L75 _public function_ `static FName GetMorphDeltaZeroThresholdPropertyName()` — Get property names.
- L76 _public function_ `static FName GetMorphCompressionLevelPropertyName()`
- L77 _public function_ `static FName GetIncludeMorphTargetNormalsPropertyName()`
- L78 _public function_ `static FName GetMaskChannelPropertyName()`
- L79 _public function_ `static FName GetInvertMaskChannelPropertyName()`
- L80 _public function_ `static FName GetCompressedMorphDataSizeInBytesPropertyName()`
- L81 _public function_ `static FName GetUncompressedMorphDataSizeInBytesPropertyName()`
- L82 _public function_ `static FName GetClampMorphTargetWeightsPropertyName()`
- L85 _public function_ `static FName GetGlobalMaskAttributePropertyName()`
- L90 _public prototype_ `virtual void UpdateStatistics();` — Update the statistics properties of this model.
- L102 _public prototype_ `void SetMorphTargetDeltaFloats(const TArray<float>& Deltas);` — `UFUNCTION(BlueprintCallable, Category = "MLDeformerMorphModel")` — Set the per vertex deltas, as a set of floats. Each vertex delta must have 3 floats. These deltas are used to generate compressed morph targets internally. You typically call this method from inside the python training script once your morph target deltas have been generated there. Concatenate all deltas into one buffer, so like this [morphdeltas_target0, morphdeltas_target1, ..., morphdeltas_targetN]. The vertex ordering should be: [(x, y, z), (x, y, z), (x, y, z)]. This is the same as SetMorphTargetDeltas, except that this takes an array of floats instead of vectors. @param Deltas The array of floats that contains the deltas. The number of items in the array must be equal to (NumMorphs * NumBaseMeshVerts * 3).
- L113 _public prototype_ `void SetMorphTargetDeltas(const TArray<FVector3f>& Deltas);` — `UFUNCTION(BlueprintCallable, Category = "MLDeformerMorphModel")` — Set the morph target model deltas as an array of 3D vectors. These deltas are used to generate compressed morph targets internally. You typically call this method from inside the python training script once your morph target deltas have been generated there. Concatenate all deltas into one buffer, so like this [morphdeltas_target0, morphdeltas_target1, ..., morphdeltas_targetN]. This is the same as SetMorphTargetDeltaFloats, except that it takes vectors instead of floats. @param Deltas The array of 3D vectors that contains the vertex deltas. The number of items in the array must be equal to (NumMorphs * NumBaseMeshVerts).
- L122 _public prototype_ `void SetMorphTargetsErrorOrder(const TArray<int32>& MorphTargetOrder, const TArray<float>& ErrorValues);` — `UFUNCTION(BlueprintCallable, Category = "MLDeformerMorphModel")` — Set the order of importance during LOD, for the morph targets. Basically this specifies the sorted order of the morph targets, based on the error they introduce when disabling them. @param MorphTargetOrder The array of morph target indices, starting with the most important morph target, and ending with the least important morph target's index. @param ErrorValues The error value for each morph target (not sorted), so index 0 contains the error value of the first morph target, which isn't necesarrily the one with highest error.
- L136 _public function_ `void SetMorphTargetsMaxWeights(const TArray<float>& MaxWeights)` — `UE_DEPRECATED(5.4, "This method will be removed.")` — `UFUNCTION(BlueprintCallable, Category = "MLDeformerMorphModel")` — Set the maximum weights for each morph target when we pass the training inputs into the trained neural network. After training we run the inputs through the trained network, and get the weights for each morph target. The array passed to this function must be the maximum of the absolute weight value over all training samples for each specific morph. We use this to scale the morph target deltas to get an estimate of the maximum length they will ever have, which we can in turn use to estimate how important a given morph target is. Keep in mind that these are the maximum of the absolute weights. As weights can be negative, we first take the absolute value of them. Training python scripts mostly will call this function to set the values. @param MaxWeights The maximum of the absolute weight values.
- L147 _public prototype_ `void SetMorphTargetsMinMaxWeights(const TArray<float>& MinValues, const TArray<float>& MaxValues);` — `UFUNCTION(BlueprintCallable, Category = "MLDeformerMorphModel")` — Set the minimum and maximum values that the morph targets weights have seen during training. We can clamp the network output weights within these ranges to try to make sure that the output doesn't go wild when we give inputs that are far outside of the range we have seen during training. The size of the array must equal the number of morph targets, or empty. In case it is empty, clamping will be ignored, even when enabled. @param MinValues The minimum weigth values, one for each morph target. @param MaxValues The maximum weight values, one for each morph target.
- L156 _public prototype_ `void SetMorphTargetsMinMaxWeights(const TArray<FFloatInterval>& MinMaxValues);` — Set the minimum and maximum values that the morph targets weights have seen during training. We can clamp the network output weights within these ranges to try to make sure that the output doesn't go wild when we give inputs that are far outside of the range we have seen during training. The size of the array must equal the number of morph targets, or empty. In case it is empty, clamping will be ignored, even when enabled. @param MinMaxValues The array of float intervals that contain the min and max values, one for each morph target.
- L169 _public function_ `const TArray<FFloatInterval>& GetMorphTargetsMinMaxWeights() const` — Get the min and max morph target weight values that we seen on the output of the training data set. These min and max values can be used to clamp the morph targets within this range. This can be used to prevent weights from getting very different values on unseen input data, and thus can prevent visually 'exploding' correctives.
- L180 _public function_ `bool IsMorphWeightClampingEnabled() const` — Check whether clamping of morph target weights is enabled. If enabled, the weights that are output will be clamped to the minimum and maximum values that are defined in the values returned by GetMorphTargetsMinMaxWeights(). It is up to the model to actually call the ClampMorphTargetWeights method though. You can check if a model supports weight clamping by calling FMLDeformerMorphModelEditorModel::IsMorphWeightClampingSupported(). If that would return false, even enabling clamping using SetClampMorphTargetsWeights(true) will not do anything. @return Returns true when clamping is enabled, otherwise false is returned.
- L186 _public prototype_ `void ClampMorphTargetWeights(TArrayView<float> WeightsArray);` — Perform the actual weight clamping to the values as set inside the MorphTargetsMinMaxWeights member. @param WeightsArray The array of input weights, that will be clamped. This method will modify the array values.
- L193 _public function_ `const TArray<FVector3f>& GetMorphTargetDeltas() const` — Get the morph target delta vectors array. The layout of this array is [morphdeltas_target0, morphdeltas_target1, ..., morphdeltas_targetN]. So the total number of items in the array returned equals (NumMorphTargets * NumBaseMeshVerts).
- L194 _public function_ `TArray<FVector3f>& GetMorphTargetDeltas()`
- L199 _public function_ `TSharedPtr<FExternalMorphSet> GetMorphTargetSet(int32 LOD) const` — Get the morph target set.
- L202 _public function_ `int32 GetNumLODs() const` — Get the number of LOD levels that we have deltas for.
- L203 _public prototype_ `void ClearMorphTargetSets();`
- L204 _public prototype_ `void AddMorphSets(int32 NumToAdd);`
- L212 _public prototype_ `int32 GetMorphTargetDeltaStartIndex(int32 MorphTargetIndex) const;` — Get the start index into the array of deltas (vectors3's), for a given morph target. This does not perform a bounds check to see if MorphTargetIndex is in a valid range, so be aware. @param MorphTargetIndex The morph target index. @return The start index, or INDEX_NONE in case there are no deltas.
- L221 _public prototype_ `TArrayView<const float> GetMorphTargetErrorValues() const;` — Get the morph target error values. This is an error value for each morph target, which indicates how much error you would introduce when disabling that specific morph target. It can be used as some sort of LOD system, where we disable morph targets that are marked with an error below a specific threshold. Keep in mind that the first morph target always contains the means, and is always active. So actually you have to +1 the index. @return The array view of the error values.
- L228 _public prototype_ `TArrayView<const int32> GetMorphTargetErrorOrder() const;` — Get the array of morph target indices, sorted by error value, from largest to smallest error. So the first array value contains the index of the most important morph target and the last element contains the least important morph target. @return An array view of the morph target indices.
- L236 _public prototype_ `float GetMorphTargetError(int32 MorphIndex) const;` — Get the estimated error that disabling a specific morph target would introduce. This error is represented in units, so in cm. @param MorphIndex The morph target index to get the error for. @return The estimated error value, in cm.
- L244 _public prototype_ `void SetMorphTargetError(int32 MorphIndex, float Error);` — Set the estimated error that disabling a specific morph target would introduce. This error is represented in units, so in cm. @param MorphIndex The morph target index to get the error for. @param Error The estimated error value, in cm.
- L248 _public prototype_ `FName GetGlobalMaskAttributeName() const;` — Get the name of the attribute used for the global mask.
- L253 _private member_ `TArray<TSharedPtr<FExternalMorphSet>> MorphTargetSets;` — A morph target set for each LOD. The number of LODs that have a morph target set can be smaller than the number of LOD levels in the Skeletal Mesh, but should never be larger.
- L263 _private member_ `bool bClampMorphWeights = true;` — `UPROPERTY(EditAnywhere, Category = "Morph Targets")` — Should we enable morph target weight clamping? The minimum and maximum values that it will be clamped against will be the min/max morph target weight values that have been seen when running the training dataset through the network. The advantage of clamping is that it can make deformations more stable when we have input poses that have not been seen during training. We basically prevent the weights from 'exploding' and getting very large values, which could make the mesh look very bad.
- L273 _private member_ `TArray<FVector3f> MorphTargetDeltas;` — `UPROPERTY(NonTransactional)` — The entire set of uncompressed morph target deltas, 3 per vertex, for each morph target, as one flattened buffer. So the size of this buffer is: (NumVertsPerMorphTarget * 3 * NumMorphTargets). You can get the number of vertices per morph target using Model->GetInputInfo()->GetNumBaseMeshVerts(). This property is Transient, because we don't want it included in undo/redo, as this can be a few hundred megabytes large. Instead, this data is serialized manually inside the Serialize method.
- L277 _private member_ `int32 NumMorphTargets_DEPRECATED = 0;` — `UPROPERTY()` — The number of morph targets.
- L281 _private member_ `uint64 CompressedMorphDataSizeInBytes = 0;` — `UPROPERTY()` — The compressed memory usage of the morph targets. This is approximately what this MLD asset will use in your packaged project.
- L285 _private member_ `uint64 UncompressedMorphDataSizeInBytes = 0;` — `UPROPERTY()` — The uncompressed memory usage of the morph targets. Please note that your packaged project will use the compressed amount of memory, and not the uncompresed amount of memory.
- L292 _private member_ `TArray<int32> MorphTargetErrorOrder;` — `UPROPERTY()` — An array of integers where the first element is the most important morph target and the last element is the least important one. The number of elements in the array is equal to the total number of morph targets.
- L296 _private member_ `TArray<float> MorphTargetErrors;` — `UPROPERTY()` — An error value, for each morph target.
- L300 _private member_ `TArray<float> MaxMorphWeights_DEPRECATED;` — `UPROPERTY()` — The maximum absolute weight values of the morph targets, during training. One value for each morph target.
- L310 _private member_ `TArray<FFloatInterval> MorphTargetsMinMaxWeights;` — `UPROPERTY()` — The minimum and maximum weight values that the morph targets weights have seen during training. We can clamp the network output weights within these ranges to try to make sure that the output doesn't go wild when we give inputs that are far outside of the range we have seen during training. It is possible that this array is empty, in which case this clamping isn't supported. The size of the array equals the number of morph targets.
- L318 _private member_ `TArray<FMLDeformerMorphModelQualityLevel> QualityLevels_DEPRECATED;` — `UPROPERTY()` — The list of quality levels, where the first item represents the highest quality and the last element the lowest quality level. The number in each quality level represents the number of active morph targets for that quality level. These numbers will be clamped internally to be within valid ranges in case they go beyond the amount of morphs that exist.
- L327 _private member_ `bool bIncludeNormals = false;` — `UPROPERTY(EditAnywhere, Category = "Morph Targets", meta = (EditCondition = "CanDynamicallyUpdateMorphTargets()"))` — Include vertex normals in the morph targets? The advantage of this can be that it is higher performance than recomputing the normals. The disadvantage is it can result in lower quality and uses more memory for the stored morph targets. In most cases you want this unchecked and calculate the normals using a deformer graph or using the skeletal mesh's tangent recompute settings in the section details.
- L336 _private member_ `float MorphDeltaZeroThreshold = 0.001f;` — `UPROPERTY(EditAnywhere, Category = "Morph Targets", DisplayName = "Delta Zero Threshold", meta = (ClampMin = "0.0", ClampMax = "1.0", ForceUnits="cm", EditCondition = "CanDynamicallyUpdateMorphTargets()"))` — Morph target delta values that are smaller than or equal to this threshold will be zeroed out. This essentially removes small deltas from morph targets, which will lower the memory usage at runtime, however when set too high it can also introduce visual artifacts. A value of 0 will result in the highest quality morph targets, at the cost of higher runtime memory usage. On the left side in the MLD asset editor you can see the estimated GPU Memory Usage. That value should change when you modify this property.
- L345 _private member_ `float MorphCompressionLevel = 1.0f;` — `UPROPERTY(EditAnywhere, Category = "Morph Targets", DisplayName = "Compression Level", meta = (ClampMin = "0.01", ClampMax = "1000", EditCondition = "CanDynamicallyUpdateMorphTargets()"))` — The morph target compression level. Higher values result in larger compression, but could result in visual artifacts. Most of the times this is a value between 1 and 50. It is best to first try increasing the "Delta Zero Threshold" property as high as you can though. Once that is set to the highest acceptable value, try increasing this morph comrpession level as high as visually acceptable. On the left side in the MLD asset editor you can see the estimated GPU Memory Usage. That value should change when you modify this property.
- L353 _private member_ `EMLDeformerMaskChannel MaskChannel = EMLDeformerMaskChannel::Disabled;` — `UPROPERTY(EditAnywhere, Category = "Morph Targets", meta = (EditCondition = "CanDynamicallyUpdateMorphTargets()"))` — The channel data that represents the delta mask multipliers. You can use this feather out influence of the ML Deformer in specific areas, such as neck line seams, where the head mesh connects with the body. The painted vertex color values will be like a weight multiplier on the ML deformer deltas applied to that vertex. You can invert the mask as well.
- L358 _private member_ `FName VertexAttributeName;` — `UPROPERTY(EditAnywhere, Category = "Morph Targets", meta = (EditCondition = "CanDynamicallyUpdateMorphTargets() && MaskChannel == EMLDeformerMaskChannel::VertexAttribute", GetOptions = "GetVertexAttributeNames", NoResetToDefault))` — The global vertex attribute attribute name. This is an attribute on the skeletal mesh, which can be created using the skeletal mesh editor.
- L366 _private member_ `bool bInvertMaskChannel = false;` — `UPROPERTY(EditAnywhere, Category = "Morph Targets", meta = (EditCondition = "CanDynamicallyUpdateMorphTargets() && MaskChannel != EMLDeformerMaskChannel::Disabled"))` — Enable this if you want to invert the mask channel values. For example if you painted the neck seam vertices in red, and you wish the vertices that got painted to NOT move, you have to invert the mask. On default you paint areas where the deformer should be active. If you enable the invert option, you paint areas where the deformer will not be active.
- L369 _private member_ `FRenderCommandFence RenderCommandFence;` — The fence that let's us wait for all render commands to finish, before this instance is destroyed.
- L372 _private member_ `bool bHasOnlyEmptyMorphs = true;` — Set to true when all the morph targets got their deltas filtered out. This can happen when your global mask is all 0's for example.

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API MLDEFORMERFRAMEWORK_API`

### `Plugins/Animation/MLDeformer/MLDeformerFramework/Source/MLDeformerFramework/Public/MLDeformerMorphModelInputInfo.h` (Public)


#### class `UMLDeformerMorphModelInputInfo`  
`class UMLDeformerMorphModelInputInfo : public UMLDeformerInputInfo`  
_L12-38_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMLDeformerInputInfo`
- L19 _public prototype_ `virtual void Serialize(FArchive& Archive) override;` — UObject overrides.
- L23 _public prototype_ `TArray<float>& GetInputItemMaskBuffer();`
- L24 _public prototype_ `const TArray<float>& GetInputItemMaskBuffer() const;`
- L25 _public prototype_ `const TArrayView<const float> GetMaskForItem(int32 MaskItemIndex) const;`
- L36 _protected member_ `TArray<float> InputItemMaskBuffer;` — `UPROPERTY()` — The buffer of mask values, which contains one float per imported vertex, for all input items. An input item is an input bone or curve (or other thing). The buffer first contains all masks for all input bones followed by all curve masks. Each mask contains GetNumBaseMeshVerts() number of floats. This data is stripped at cook time, as it is not needed at runtime.

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API MLDEFORMERFRAMEWORK_API`

### `Plugins/Animation/MLDeformer/MLDeformerFramework/Source/MLDeformerFramework/Public/MLDeformerMorphModelInstance.h` (Public)


#### class `UMLDeformerMorphModelInstance`  
`class UMLDeformerMorphModelInstance : public UMLDeformerModelInstance`  
_L23-53_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMLDeformerModelInstance`
- desc: The model instance for the UMLDeformerMorphModel. This instance will assume the neural network outputs a set of weights, one for each morph target. The weights of the morph targets in the external morph target set related to the ID of the model will be set to the weights that the neural network outputs. The first morph target contains the means, which need to always be added to the results. Therefore the weight of the first morph target will always be forced to a value of 1.
- L30 _public prototype_ `virtual void Init(USkeletalMeshComponent* SkelMeshComponent) override;` — UMLDeformerModelInstance overrides.
- L31 _public prototype_ `virtual void PostMLDeformerComponentInit() override;`
- L32 _public prototype_ `virtual void BeginDestroy() override;`
- L33 _public prototype_ `virtual void HandleZeroModelWeight() override;`
- L34 _public prototype_ `virtual bool IsValidForDataProvider() const override;`
- L35 _public prototype_ `virtual void PostTick(bool bExecuteCalled) override;`
- L38 _public prototype_ `int32 GetExternalMorphSetID() const;`
- L45 _public prototype_ `FExternalMorphSetWeights* FindWeightData(int32 LOD) const;` — Find the external morph target weight data for this model instance. @param LOD The LOD level to get the weight data for. @return A pointer to the weight data, or a nullptr in case it cannot be found.
- L49 _protected member_ `static TAtomic<int32> NextFreeMorphSetID;` — The next free morph target set ID. This is used to generate unique ID's for each morph model.
- L52 _protected member_ `int32 ExternalMorphSetID = -1;` — The ID of the external morph target set for this instance. This gets initialized during Init.

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API MLDEFORMERFRAMEWORK_API`

### `Plugins/Animation/MLDeformer/MLDeformerFramework/Source/MLDeformerFramework/Public/MLDeformerMorphModelQualityLevel.h` (Public)


#### struct `FMLDeformerMorphModelQualityLevel`  
`struct FMLDeformerMorphModelQualityLevel`  
_L14-25_
- reflection: `USTRUCT()`
- desc: A quality level for the Morph Model. Each quality level contains the maximum number of active morph targets.
- L19 _public function_ `int32 GetMaxActiveMorphs() const`
- L20 _public function_ `void SetMaxActiveMorphs(int32 NumMorphs)`
- L24 _public member_ `int32 MaxActiveMorphs = 0;` — `UPROPERTY(EditAnywhere, Category = "Quality Level", meta = (ClampMin = "1"))`

### `Plugins/Animation/MLDeformer/MLDeformerFramework/Source/MLDeformerFramework/Public/MLDeformerMorphModelVizSettings.h` (Public)


#### class `UMLDeformerMorphModelVizSettings`  
`class UMLDeformerMorphModelVizSettings : public UMLDeformerGeomCacheVizSettings`  
_L13-52_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMLDeformerGeomCacheVizSettings`
- desc: The visualization settings specific to the UMLDeformerMorphModel class, or inherited classes.
- L19 _public function_ `void SetMorphTargetNumber(int32 MorphIndexToPreview)`
- L20 _public function_ `void SetDrawMorphTargets(bool bDraw)`
- L22 _public function_ `int32 GetMorphTargetNumber() const`
- L23 _public function_ `bool GetDrawMorphTargets() const`
- L26 _public function_ `static FName GetMorphTargetNumberPropertyName()` — Get property names.
- L27 _public function_ `static FName GetDrawMorphTargetsPropertyName()`
- L36 _protected member_ `float MorphTargetDeltaThreshold_DEPRECATED = 0.01f;` — `UPROPERTY()` — The morph target delta threshold. This is a preview of what deltas would be included in the selected morph target when using a delta threshold during training that is equal to this value. This only can be used after you trained, in the same editor session directly after training.
- L43 _protected member_ `int32 MorphTargetNumber = 0;` — `UPROPERTY(EditAnywhere, Category = "Live Settings", meta = (ClampMin = "0"))` — The morph target to visualize. The first one always being the means, so not a sparse target. This only can be used after you trained, in the same editor session directly after training.
- L51 _protected member_ `bool bDrawMorphTargets = false;` — `UPROPERTY(EditAnywhere, Category = "Live Settings")` — Specify whether we want to debug draw the morph targets. Enabling this can help you see what the sparsity of the generated morph targets is. If the model supports input masking, it will also show the mask applied to the morph target.

### `Plugins/Animation/MLDeformer/MLDeformerFramework/Source/MLDeformerFramework/Public/MLDeformerObjectVersion.h` (Public)


#### struct `UE::MLDeformer::FMLDeformerObjectVersion`  
`struct FMLDeformerObjectVersion`  
_L12-37_
- desc: Custom serialization version for backwards compatibility during de-serialization
- L14 _public prototype_ `FMLDeformerObjectVersion() = delete;`
- L36 _public member_ `const static FGuid GUID;` — The GUID for this custom version number.

#### enum `UE::MLDeformer::FMLDeformerObjectVersion::Type`  
`enum Type`  
_L16-33_
- L19 _public enumerator_ `BeforeCustomVersionWasAdded` — Before any version changes were made.
- L22 _public enumerator_ `LODSupportAdded` — We added LOD support.
- L25 _public enumerator_ `MaskInfoMovedToFramework` — We deprecated the UNeuralMorphMaskInfo and should use FMLDeformerMaskInfo instead.
- L28 _public enumerator_ `UndoSupportAdded` — Undo support added.
- L31 _public enumerator_ `VersionPlusOne` — ----- New versions can be added above this line -----
- L32 _public enumerator_ `LatestVersion = VersionPlusOne - 1`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API MLDEFORMERFRAMEWORK_API`
- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace MLDeformer` (scope `UE`)

### `Plugins/Animation/MLDeformer/MLDeformerFramework/Source/MLDeformerFramework/Public/MLDeformerPerfCounter.h` (Public)


#### class `UE::MLDeformer::FMLDeformerPerfCounter`  
`class FMLDeformerPerfCounter`  
_L13-39_
- L16 _public prototype_ `FMLDeformerPerfCounter();`
- L19 _public prototype_ `void SetHistorySize(int32 NumHistoryItems);` — Main methods.
- L20 _public prototype_ `void Reset();`
- L21 _public prototype_ `void BeginSample();`
- L22 _public prototype_ `void EndSample();`
- L25 _public prototype_ `int32 GetCycles() const;` — Get statistics.
- L26 _public prototype_ `int32 GetCyclesMin() const;`
- L27 _public prototype_ `int32 GetCyclesMax() const;`
- L28 _public prototype_ `int32 GetCyclesAverage() const;`
- L29 _public prototype_ `int32 GetNumSamples() const;`
- L30 _public prototype_ `int32 GetHistorySize() const;`
- L33 _private member_ `int32 StartTime = 0;`
- L34 _private member_ `int32 NumSamples = 0;`
- L35 _private member_ `int32 Cycles = 0;`
- L36 _private member_ `int32 CyclesMin = 0;`
- L37 _private member_ `int32 CyclesMax = 0;`
- L38 _private member_ `TArray<int32> CycleHistory;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API MLDEFORMERFRAMEWORK_API`
- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace MLDeformer` (scope `UE`)

### `Plugins/Animation/MLDeformer/MLDeformerFramework/Source/MLDeformerFramework/Public/MLDeformerTrainingDataProcessorSettings.h` (Public)


#### struct `FMLDeformerTrainingDataProcessorAnim`  
`struct FMLDeformerTrainingDataProcessorAnim`  
_L15-27_
- reflection: `USTRUCT()`
- L22 _public member_ `TSoftObjectPtr<UAnimSequence> AnimSequence;` — `UPROPERTY(EditAnywhere, Category = "", meta = (NoResetToDefault))` — The animation sequence that we should sample frames from.
- L26 _public member_ `bool bEnabled = true;` — `UPROPERTY(EditAnywhere, Category = "")` — Should we sample frames from this animation sequence?

#### struct `FMLDeformerTrainingDataProcessorBoneGroup`  
`struct FMLDeformerTrainingDataProcessorBoneGroup`  
_L31-41_
- reflection: `USTRUCT()`
- L37 _public member_ `FString GroupName;` — `UPROPERTY()`
- L40 _public member_ `TArray<FName> BoneNames;` — `UPROPERTY()`

#### struct `FMLDeformerTrainingDataProcessorBoneGroupsList`  
`struct FMLDeformerTrainingDataProcessorBoneGroupsList`  
_L45-52_
- reflection: `USTRUCT()`
- L51 _public member_ `TArray<FMLDeformerTrainingDataProcessorBoneGroup> Groups;` — `UPROPERTY()`

#### struct `FMLDeformerTrainingDataProcessorBoneList`  
`struct FMLDeformerTrainingDataProcessorBoneList`  
_L56-63_
- reflection: `USTRUCT()`
- L62 _public member_ `TArray<FName> BoneNames;` — `UPROPERTY()`

#### class `UMLDeformerTrainingDataProcessorSettings`  
`class UMLDeformerTrainingDataProcessorSettings : public UObject`  
_L71-178_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject`
- desc: The settings for the ML Deformer Training Data Processor tool. These settings are also stored along with the ML Deformer asset.
- L77 _public prototype_ `UMLDeformerTrainingDataProcessorSettings() = default;`
- L85 _public prototype_ `USkeleton* FindSkeleton() const;` — This returns a pointer to the skeleton used by the SkeletalMesh that is set in the UMLDeformerModel that this settings class is part of. If there is no skeletal mesh set on the model, a nullptr will be returned. @return A pointer to the skeleton we should be using, or nullptr if not found.
- L92 _public prototype_ `int32 GetNumInputAnimationFrames() const;` — Get the number of frames of all enabled input animations combined. This will ignore disabled input animations. It will try to load the animation sequences and get their number of frames and sum them up. @return The number of frames that would be sampled.
- L100 _public prototype_ `bool IsValid(const USkeleton* Skeleton) const;` — Check whether these settings are valid when used with a given skeleton. The skeleton we use is likely the skeleton used by the ML Deformer asset. @param Skeleton The skeleton to check against. This makes sure the input animations must be the same as this provided skeleton. @return Returns true if this configuration is valid, or false otherwise.
- L109 _public member_ `TArray<FMLDeformerTrainingDataProcessorAnim> AnimList;` — `UPROPERTY(EditAnywhere, Category = "Input Animations", meta = (NoResetToDefault))` — The list of animation sequences from which we will grab a pose for each frame. This final list of poses then will go through the pose remixing and reduction steps.
- L116 _public member_ `FMLDeformerTrainingDataProcessorBoneList BoneList;` — `UPROPERTY(EditAnywhere, Category = "Frame Reduction", meta = (NoResetToDefault))` — The list of bones that is used to calculate which poses have most variation. It does not influence the number of output bones in the output animation.
- L126 _public member_ `FMLDeformerTrainingDataProcessorBoneGroupsList BoneGroups;` — `UPROPERTY(EditAnywhere, Category = "Pose Remixing", meta = (NoResetToDefault))` — The list of bone groups used during pose remixing. Pose remixing will basically shuffle the keyframes for the group of bones as a whole. So if you put the left arm bones in a group, the frame numbers of the arm will be shuffled, but while keeping all the arm bones at the same frame. The rest of the body can be in a different frame. This might sound strange, but it can help the machine learning deformer algorithm produce better reconstructions.
- L139 _public member_ `int32 NumOutputFrames = 5000;` — `UPROPERTY(EditAnywhere, Category = "Output", meta = (ClampMin="1", EditCondition = "bReduceFrames"))` — The number of output frames you want the output animation sequence to have. If this number is higher than the number of frames in the input animations, it will just use the maximum number of available frames. This can be used to reduce the number of frames for training, which is useful if you want to reduce the size of your training data set. This will also change the reordering of frames, so it is NOT just going to cut off some frames at the end. It will use a greedy algorithm to find poses that are as different as possible from each other. By doing that we hope to get as much pose space coverage as possible. This setting is only used when the "Reduce Frames" option is enabled.
- L150 _public member_ `bool bReduceFrames = true;` — `UPROPERTY(EditAnywhere, Category = "Output")` — Specify whether we should reduce the number of frames that we sampled from the input animations, or not. This can be used to reduce the number of frames for training, which is useful if you want to reduce the size of your training data set. This will also change the reordering of frames, so it is NOT just going to cut off some frames at the end. It will use a greedy algorithm to find poses that are as different as possible from each other. By doing that we hope to get as much pose space coverage as possible. This setting is only used when the "Reduce Frames" option is enabled.
- L160 _public member_ `bool bRemixPoses = true;` — `UPROPERTY(EditAnywhere, Category = "Output")` — Enable this when you want to perform pose remixing. Pose remixing will basically shuffle the keyframes for the group of bones as a whole. So if you put the left arm bones in a group, the frame numbers of the arm will be shuffled, but while keeping all the arm bones at the same frame. The rest of the body can be in a different frame. This might sound strange, but it can help the machine learning deformer algorithm produce better reconstructions.
- L169 _public member_ `int32 RandomSeed = 777;` — `UPROPERTY(EditAnywhere, Category = "Output", meta = (ClampMin = "0", EditCondition = "bRemixPoses"))` — The random seed that is used during pose remixing. The remixing algorithm shuffles frames, which uses randomization. In order to always get the same results if we perform pose remixing on the same data set, we have to use a fixed seed. Changing the seed could result in a different order of frames.
- L177 _public member_ `TSoftObjectPtr<UAnimSequence> OutputAnimSequence;` — `UPROPERTY(EditAnywhere, Category = "Output", meta = (NoResetToDefault))` — The output animation sequence. This animation sequence will be modified and will be filled with the generated frames. Please watch out with picking existing animation sequences, as their contents will be overwritten after you press Generate.

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API MLDEFORMERFRAMEWORK_API`

### `Plugins/Animation/MLDeformer/MLDeformerFramework/Source/MLDeformerFramework/Public/MLDeformerTrainingInputAnim.h` (Public)


#### struct `FMLDeformerTrainingInputAnim`  
`struct FMLDeformerTrainingInputAnim`  
_L17-89_
- reflection: `USTRUCT()`
- desc: An animation that is input to the training process. This is a base struct that only contains the animation sequence. For example a geometry cache based model should inherit from this struct and add a geom cache member property.
- L22 _public prototype_ `virtual ~FMLDeformerTrainingInputAnim() = default;`
- L29 _public function_ `virtual int32 GetNumFramesToSample() const` — Get the number of frames that we are sampling inside this animation. This can be less than the value returned by ExtractNumAnimFrames(). This might be the custom frame range, so a subsection of the animation frames.
- L32 _public function_ `virtual bool IsValid() const` — Is this input animation valid? Returns true if we can sample from it. This typically checks if the pointers to the source and target animations are valid.
- L35 _public function_ `virtual int32 ExtractNumAnimFrames() const` — How many frames does this input animation have? This is the maximum number of frames we can sample.
- L37 _public function_ `void SetEnabled(bool bEnable)`
- L38 _public function_ `void SetAnimSequence(TSoftObjectPtr<UAnimSequence> Seq)`
- L39 _public function_ `void SetUseCustomRange(bool bCustomRange)`
- L40 _public function_ `void SetStartFrame(int32 FrameIndex)`
- L41 _public function_ `void SetEndFrame(int32 FrameIndex)`
- L42 _public function_ `void SetVertexMask(FName MaskName)`
- L44 _public function_ `bool IsEnabled() const`
- L45 _public function_ `bool GetUseCustomRange() const`
- L46 _public function_ `int32 GetStartFrame() const`
- L47 _public function_ `int32 GetEndFrame() const`
- L48 _public function_ `FName GetVertexMask() const`
- L49 _public function_ `const UAnimSequence* GetAnimSequence() const`
- L50 _public function_ `UAnimSequence* GetAnimSequence()`
- L51 _public function_ `const TSoftObjectPtr<UAnimSequence>& GetAnimSequenceSoftObjectPtr() const`
- L52 _public function_ `TSoftObjectPtr<UAnimSequence>& GetAnimSequenceSoftObjectPtr()`
- L54 _public function_ `static FName GetAnimSequencePropertyName()`
- L55 _public function_ `static FName GetEnabledPropertyName()`
- L56 _public function_ `static FName GetUseCustomRangePropertyName()`
- L57 _public function_ `static FName GetStartFramePropertyName()`
- L58 _public function_ `static FName GetEndFramePropertyName()`
- L59 _public function_ `static FName GetVertexMaskPropertyName()`
- L64 _private member_ `TSoftObjectPtr<UAnimSequence> AnimSequence;` — `UPROPERTY(EditAnywhere, Category = "Settings", meta = (DisplayPriority = 0))` — The animation sequence.
- L68 _private member_ `bool bUseCustomRange = false;` — `UPROPERTY(EditAnywhere, Category = "Frame Settings")` — On default all frames are included, unless we specify a custom frame include range.
- L72 _private member_ `int32 StartFrame = 0;` — `UPROPERTY(EditAnywhere, Category = "Frame Settings", meta = (ClampMin="0", EditCondition="bUseCustomRange"))` — The start frame number of the range of included frames. Only used when not all frames are included.
- L76 _private member_ `int32 EndFrame = 0;` — `UPROPERTY(EditAnywhere, Category = "Frame Settings", meta = (ClampMin="0", EditCondition="bUseCustomRange"))` — The end frame number of the range of included frames. Only used when not all frames are included.
- L83 _private member_ `FName VertexMask;` — `UPROPERTY(EditAnywhere, Category = "Settings")` — The optional vertex attribute mask to use for this training data. This can be used to focus training on a specific area on the mesh. For example if you have training data for a hand, you can specify a mask that contains just the hand and maybe forearm.
- L87 _private member_ `bool bEnabled = true;` — `UPROPERTY(EditAnywhere, Category = "Settings", meta = (DisplayPriority = MAX_int32))` — Is this animation enabled? If not, it is excluded from the training process.

#### struct `FMLDeformerTrainingInputAnimName`  
`struct FMLDeformerTrainingInputAnimName`  
_L91-98_
- L94 _public member_ `FString Name;` — The name to display in the timeline combobox.
- L97 _public member_ `int32 TrainingInputAnimIndex = INDEX_NONE;` — The training input anim index. This is the index inside the FMLDeformerEditorModel::GetTrainingInputAnim(Index) method.

### `Plugins/Animation/MLDeformer/MLDeformerFramework/Source/MLDeformerFramework/Public/MLDeformerVizSettings.h` (Public)


#### enum `EMLDeformerVizMode`  
`enum class EMLDeformerVizMode : uint8`  
_L16-23_
- reflection: `UENUM()`
- desc: The visualization mode, which selects whether you want to view the training data, or test your already trained model.
- L19 _public enumerator_ `TrainingData = 0` — Preview the training data.
- L22 _public enumerator_ `TestData` — Preview testing data, used on trained models.

#### enum `EMLDeformerHeatMapMode`  
`enum class EMLDeformerHeatMapMode : uint8`  
_L27-34_
- reflection: `UENUM()`
- desc: The heat map mode which selects what the colors of the heatmap represent.
- L30 _public enumerator_ `Activations = 0` — Visualize areas where the deformer is applying corrections. The color represents the size of the correction it applies.
- L33 _public enumerator_ `GroundTruth` — Visualize the error versus the ground truth model. Requires a ground truth model to be setup.

#### struct `FMLDeformerCompareActor`  
`struct FMLDeformerCompareActor`  
_L38-49_
- reflection: `USTRUCT()`
- desc: A comparison actor.
- L44 _public member_ `FName Name;` — `UPROPERTY(EditAnywhere, Category = "Actor Settings")` — The name of the comparison actor, which is the label shown above it.
- L48 _public member_ `TSoftObjectPtr<UMLDeformerAsset> DeformerAsset;` — `UPROPERTY(EditAnywhere, Category = "Actor Settings")` — The ML Deformer asset that this actor should use.

#### class `UMLDeformerVizSettings`  
`class UMLDeformerVizSettings : public UObject`  
_L55-269_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject`
- desc: The visualization settings.
- L62 _public function_ `virtual bool IsEditorOnly() const override` — UObject overrides.
- L64 _public function_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)` — Forward to the UMLDeformerModel.
- L69 _public function_ `virtual bool HasTestGroundTruth() const`
- L71 _public function_ `void SetVisualizationMode(EMLDeformerVizMode Mode)`
- L72 _public function_ `void SetDeformerGraph(UMeshDeformer* InDeformerGraph)`
- L73 _public function_ `void SetTrainingFrameNumber(int32 FrameNumber)`
- L74 _public function_ `void SetTestingFrameNumber(int32 FrameNumber)`
- L75 _public function_ `void SetWeight(float InWeight)`
- L76 _public function_ `void SetTestAnimSequence(UAnimSequence* InAnim)`
- L77 _public function_ `void SetMeshSpacing(float Spacing)`
- L78 _public function_ `void SetLabelHeight(float Height)`
- L79 _public function_ `void SetLabelScale(float Scale)`
- L80 _public function_ `void SetDrawLabels(bool bDraw)`
- L81 _public function_ `void SetAnimPlaySpeed(float SpeedFactor)`
- L82 _public function_ `void SetDrawLinearSkinnedActor(bool bDraw)`
- L83 _public function_ `void SetDrawMLDeformedActor(bool bDraw)`
- L84 _public function_ `void SetDrawGroundTruthActor(bool bDraw)`
- L85 _public function_ `void SetDrawMLCompareActors(bool bDraw)`
- L86 _public function_ `void SetDrawDebugActorBounds(bool bDraw)`
- L87 _public function_ `void SetDrawVertexDeltas(bool bDraw)`
- L88 _public function_ `void SetXRayDeltas(bool bEnable)`
- L89 _public function_ `void SetHeatMapMax(float Value)`
- L90 _public function_ `void SetGroundTruthLerp(float Alpha)`
- L91 _public function_ `void SetShowHeatMap(bool bShow)`
- L92 _public function_ `void SetHeatMapMode(EMLDeformerHeatMapMode Mode)`
- L93 _public function_ `void SetDebugBoundsColor(const FColor& Color)`
- L94 _public function_ `void SetCompareActors(const TArray<FMLDeformerCompareActor>& Actors)`
- L96 _public function_ `FVector GetMeshSpacingOffsetVector() const`
- L97 _public function_ `float GetMeshSpacing() const`
- L98 _public function_ `float GetLabelHeight() const`
- L99 _public function_ `bool GetDrawLabels() const`
- L100 _public function_ `float GetLabelScale() const`
- L101 _public function_ `EMLDeformerVizMode GetVisualizationMode() const`
- L102 _public function_ `int32 GetTrainingFrameNumber() const`
- L103 _public function_ `int32 GetTestingFrameNumber() const`
- L104 _public function_ `float GetAnimPlaySpeed() const`
- L105 _public function_ `const UAnimSequence* GetTestAnimSequence() const`
- L106 _public function_ `UAnimSequence* GetTestAnimSequence()`
- L107 _public function_ `bool GetDrawLinearSkinnedActor() const`
- L108 _public function_ `bool GetDrawMLDeformedActor() const`
- L109 _public function_ `bool GetDrawGroundTruthActor() const`
- L110 _public function_ `bool GetDrawMLCompareActors() const`
- L111 _public function_ `bool GetDrawDebugActorBounds() const`
- L112 _public function_ `bool GetShowHeatMap() const`
- L113 _public function_ `EMLDeformerHeatMapMode GetHeatMapMode() const`
- L114 _public function_ `float GetHeatMapMax() const`
- L115 _public function_ `float GetGroundTruthLerp() const`
- L116 _public function_ `UMeshDeformer* GetDeformerGraph() const`
- L117 _public function_ `float GetWeight() const`
- L118 _public function_ `bool GetXRayDeltas() const`
- L119 _public function_ `bool GetDrawVertexDeltas() const`
- L120 _public function_ `const TArray<FMLDeformerCompareActor>& GetCompareActors() const`
- L121 _public function_ `TArray<FMLDeformerCompareActor>& GetCompareActors()`
- L122 _public function_ `FColor GetDebugBoundsColor() const`
- L125 _public function_ `static FName GetVisualizationModePropertyName()` — Get property names.
- L126 _public function_ `static FName GetMeshSpacingPropertyName()`
- L127 _public function_ `static FName GetDrawLabelsPropertyName()`
- L128 _public function_ `static FName GetLabelHeightPropertyName()`
- L129 _public function_ `static FName GetLabelScalePropertyName()`
- L130 _public function_ `static FName GetTrainingFrameNumberPropertyName()`
- L131 _public function_ `static FName GetTestingFrameNumberPropertyName()`
- L132 _public function_ `static FName GetAnimPlaySpeedPropertyName()`
- L133 _public function_ `static FName GetTestAnimSequencePropertyName()`
- L134 _public function_ `static FName GetDrawLinearSkinnedActorPropertyName()`
- L135 _public function_ `static FName GetDrawMLDeformedActorPropertyName()`
- L136 _public function_ `static FName GetDrawGroundTruthActorPropertyName()`
- L137 _public function_ `static FName GetDrawMLCompareActorsPropertyName()`
- L138 _public function_ `static FName GetDrawDebugActorBoundsPropertyName()`
- L139 _public function_ `static FName GetShowHeatMapPropertyName()`
- L140 _public function_ `static FName GetHeatMapModePropertyName()`
- L141 _public function_ `static FName GetHeatMapMaxPropertyName()`
- L142 _public function_ `static FName GetGroundTruthLerpPropertyName()`
- L143 _public function_ `static FName GetDeformerGraphPropertyName()`
- L144 _public function_ `static FName GetWeightPropertyName()`
- L145 _public function_ `static FName GetXRayDeltasPropertyName()`
- L146 _public function_ `static FName GetDrawVertexDeltasPropertyName()`
- L147 _public function_ `static FName GetCompareActorsPropertyName()`
- L148 _public function_ `static FName GetDebugBoundsColorPropertyName()`
- L155 _protected member_ `EMLDeformerVizMode VisualizationMode = EMLDeformerVizMode::TrainingData;` — `UPROPERTY()` — The data to visualize.
- L159 _protected member_ `TSoftObjectPtr<UAnimSequence> TestAnimSequence;` — `UPROPERTY(EditAnywhere, Category = "Test Assets")` — The animation sequence to play on the skeletal mesh.
- L163 _protected member_ `TSoftObjectPtr<UMeshDeformer> DeformerGraph;` — `UPROPERTY(EditAnywhere, Category = "Test Assets")` — The deformer graph to use on the asset editor's deformed test actor.
- L170 _protected member_ `TArray<FMLDeformerCompareActor> CompareActors;` — `UPROPERTY(EditAnywhere, Category = "Test Assets")` — The model comparison actors. Each will create a skeletal mesh with the selected ML Deformer applied to it. This is useful to compare the output of different models side by side.
- L174 _protected member_ `float AnimPlaySpeed = 1.0f;` — `UPROPERTY(EditAnywhere, Category = "Live Settings", meta = (ClampMin = "0.0", ClampMax = "2.0", ForceUnits="Multiplier"))` — The play speed factor of the test anim sequence.
- L178 _protected member_ `int32 TrainingFrameNumber = 0;` — `UPROPERTY(EditAnywhere, Category = "Training Meshes", meta = (ClampMin = "0"))` — The frame number of the training data to visualize.
- L182 _protected member_ `bool bDrawLabels = true;` — `UPROPERTY(EditAnywhere, Category = "Shared Settings")` — Specifies whether we should draw the labels, such as "Linear Skinned" and "ML Deformed" or not.
- L186 _protected member_ `float LabelHeight = 200.0f;` — `UPROPERTY(EditAnywhere, Category = "Shared Settings", meta = (EditCondition = "bDrawLabels", ForceUnits="cm"))` — The height in units to draw the labels at.
- L190 _protected member_ `float LabelScale = 1.0f;` — `UPROPERTY(EditAnywhere, Category = "Shared Settings", meta = (ClampMin = "0.001", EditCondition = "bDrawLabels", ForceUnits="Multiplier"))` — The scale of the label text.
- L194 _protected member_ `float MeshSpacing = 125.0f;` — `UPROPERTY(EditAnywhere, Category = "Shared Settings", meta = (ClampMin = "0", ForceUnits="cm"))` — The spacing between meshes.
- L198 _protected member_ `int32 TestingFrameNumber = 0;` — `UPROPERTY(EditAnywhere, Category = "Live Settings", meta = (ClampMin = "0"))` — The frame number of the test data to visualize.
- L202 _protected member_ `int32 QualityLevel_DEPRECATED = 0;` — `UPROPERTY(Transient)` — Deprecated quality level property, deprecated in 5.4.
- L206 _protected member_ `bool bShowHeatMap = false;` — `UPROPERTY(EditAnywhere, Category = "Live Settings")` — Specify whether the heatmap is enabled or not.
- L210 _protected member_ `EMLDeformerHeatMapMode HeatMapMode = EMLDeformerHeatMapMode::Activations;` — `UPROPERTY(EditAnywhere, Category = "Live Settings", meta = (EditCondition = "bShowHeatMap"))` — Specifies what the heatmap colors should represent.
- L220 _protected member_ `float HeatMapMax = 1.0f;` — `UPROPERTY(EditAnywhere, Category = "Live Settings", meta = (EditCondition = "bShowHeatMap", ClampMin = "0.001", ForceUnits="cm"))` — Specifies how many centimeters the most intense color of the heatmap represents. For example when set to 3, it means that everything that is red, is 3 cm or more. In Activations heat map mode this means that everything is red for all vertices with a delta longer than 3 cm, so with a corrective delta longer than 3 cm. In Ground Truth heat map mode this means that everything is red for all vertices where the difference between the ground truth and the ML Deformed model is larger than 3 cm.
- L228 _protected member_ `float GroundTruthLerp = 0.0f;` — `UPROPERTY(EditAnywhere, Transient, Category = "Live Settings", meta = (EditCondition = "HeatMapMode==EMLDeformerHeatMapMode::GroundTruth && bShowHeatMap", UIMin = "0.0", UIMax = "1.0", ClampMin = "0.0", ClampMax = "1.0"))` — The Lerp factor from ML deformed model to ground truth model when in heat map mode. A value of 0 means that we look exactly the same as the ML Deformed output, while a value of 1 means the output is exactly the same as the ground truth. This is the blend factor between those two.
- L232 _protected member_ `bool bDrawLinearSkinnedActor = true;` — `UPROPERTY(EditAnywhere, Category = "Live Settings")` — Specifies whether we draw the linear skinned model or not.
- L236 _protected member_ `bool bDrawMLDeformedActor = true;` — `UPROPERTY(EditAnywhere, Category = "Live Settings", DisplayName = "Draw ML Deformed Actor")` — Specifies whether we draw the ML Deformed model or not.
- L240 _protected member_ `bool bDrawGroundTruthActor = true;` — `UPROPERTY(EditAnywhere, Category = "Live Settings")` — Specifies whether we draw the ground truth model or not.
- L244 _protected member_ `bool bDrawMLCompareActors = true;` — `UPROPERTY(EditAnywhere, Category = "Live Settings", DisplayName = "Draw ML Compare Actors")` — Specifies whether we draw the comparison actors or not.
- L248 _protected member_ `bool bDrawDebugActorBounds = true;` — `UPROPERTY(EditAnywhere, Category = "Live Settings", DisplayName = "Highlight Debug Actors in PIE")` — Draw the debug actor's bounds in the PIE viewport? This only renders when PIE is active.
- L255 _protected member_ `FColor DebugBoundsColor = FColor::Purple;` — `UPROPERTY(EditAnywhere, Category = "Live Settings")` — The color of the bounding box rendered inside the PIE viewport. Keep in mind that the actor you are currently debugging is always rendered in green.
- L259 _protected member_ `float Weight = 1.0f;` — `UPROPERTY(EditAnywhere, Transient, Category = "Live Settings", meta = (ClampMin = "0.0", ClampMax = "1.0"))` — The scale factor of the ML deformer deltas being applied on top of the linear skinned results.
- L263 _protected member_ `bool bDrawDeltas = true;` — `UPROPERTY(EditAnywhere, Category = "Training Meshes")` — Specifiy whether we want to draw the vertex deltas or not.
- L267 _protected member_ `bool bXRayDeltas = true;` — `UPROPERTY(EditAnywhere, Category = "Training Meshes", meta = (EditCondition = "bDrawDeltas"))` — Specify whether the vertex deltas are rendered, even if they are behind the current mesh.
