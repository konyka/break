# Plugins / InterchangeChaosClothAssetImport

- module root: `Plugins/Interchange/Extensions/ChaosClothAsset/Source/Import`
- headers: 7; symbols: 77
- symbol kinds: class=5, delegate=1, function=1, macro=3, member=13, namespace=5, prototype=39, struct=1, variable=9
- PrivateDependencyModuleNames: Chaos, ChaosClothAsset, ChaosClothAssetDataflowNodes, ChaosClothAssetEngine, DataflowEngine, InterchangeAnalytics, InterchangeCore, InterchangeEngine, InterchangeFactoryNodes, InterchangeImport, InterchangeNodes, MeshDescription, StaticMeshDescription
- PublicDependencyModuleNames: Core, CoreUObject, Engine

### `Plugins/Interchange/Extensions/ChaosClothAsset/Source/Import/Private/InterchangeChaosClothAssetImportLog.h` (Private)


#### Free symbols / members of external scopes

- L7 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogInterchangeChaosClothAssetImport, Log, All);`
- L7 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogInterchangeChaosClothAssetImport, Log, All);`

### `Plugins/Interchange/Extensions/ChaosClothAsset/Source/Import/Public/InterchangeChaosClothAssetDefinitions.h` (Public)


#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace Interchange` (scope `UE`)
- L8 _namespace_ `namespace ChaosCloth` (scope `UE::Interchange`)
- L11 _variable_ `inline const FString ClothRootTag = TEXT("Clo` (scope `UE::Interchange::ChaosCloth`) — We add this to scene nodes to flag them so that we can find them later with the ChaosCloth pipeline and produce cloth factory nodes
- L14 _variable_ `inline const FString RenderMeshesAttributeName = TEXT("Clo` (scope `UE::Interchange::ChaosCloth`) — These are used as user attributes names on the cloth root scene node, where we store the child render and simulation meshes
- L15 _variable_ `inline const FString SimMeshesAttributeName = TEXT("Clo` (scope `UE::Interchange::ChaosCloth`)
- L18 _variable_ `inline const FName ImportedCollectionVariableName = TEXT("Imp` (scope `UE::Interchange::ChaosCloth`) — Name of the variable that we'll override on the Dataflow graph with the import data
- L21 _variable_ `inline const FName OriginalIndicesName = TEXT("Ori` (scope `UE::Interchange::ChaosCloth`) — Name used by the chaos cloth import for tracking the original mesh triangle indices in the combined managed array collection
- L24 _variable_ `inline const FString SolverAirDamping = TEXT("air` (scope `UE::Interchange::ChaosCloth`) — Solver properties: We also store these as user attributes on the cloth root scene node, and hoist them into factory node custom attributes
- L25 _variable_ `inline const FString SolverGravity = TEXT("gra` (scope `UE::Interchange::ChaosCloth`)
- L26 _variable_ `inline const FString SolverSubStepCount = TEXT("sub` (scope `UE::Interchange::ChaosCloth`)
- L27 _variable_ `inline const FString SolverTimeStep = TEXT("tim` (scope `UE::Interchange::ChaosCloth`)

### `Plugins/Interchange/Extensions/ChaosClothAsset/Source/Import/Public/InterchangeChaosClothAssetFactory.h` (Public)


#### class `UInterchangeChaosClothAssetFactory`  
`class UInterchangeChaosClothAssetFactory : public UInterchangeFactoryBase`  
_L20-53_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UInterchangeFactoryBase`
- L26 _public prototype_ `virtual UClass* GetFactoryClass() const override;`
- L27 _public function_ `virtual EInterchangeFactoryAssetType GetFactoryAssetType() override`
- L28 _public prototype_ `virtual void CreatePayloadTasks(const FImportAssetObjectParams& Arguments, bool bAsync, TArray<TSharedPtr<UE::Interchange::FInterchangeTaskBase>>& PayloadTasks) override;`
- L29 _public prototype_ `virtual FImportAssetResult ImportAsset_Async(const FImportAssetObjectParams& Arguments);`
- L30 _public prototype_ `virtual FImportAssetResult BeginImportAsset_GameThread(const FImportAssetObjectParams& Arguments) override;`
- L31 _public prototype_ `virtual void SetupObject_GameThread(const FSetupObjectParams& Arguments) override;`
- L32 _public prototype_ `virtual bool GetSourceFilenames(const UObject* Object, TArray<FString>& OutSourceFilenames) const override;`
- L33 _public prototype_ `virtual bool SetSourceFilename(const UObject* Object, const FString& SourceFilename, int32 SourceIndex) const override;`
- L34 _public prototype_ `virtual void BackupSourceData(const UObject* Object) const override;`
- L35 _public prototype_ `virtual void ReinstateSourceData(const UObject* Object) const override;`
- L36 _public prototype_ `virtual void ClearBackupSourceData(const UObject* Object) const override;`
- L47 _private member_ `TArray<FRenderMeshPayloadData> RenderMeshPayloadDataArray;`
- L48 _private member_ `TArray<TSharedPtr<FManagedArrayCollection>> SimMeshPayloadDataArray;`
- L52 _private member_ `TSharedPtr<FManagedArrayCollection> CombinedCollection;` — Basically the final output of the factory, is added to the Dataflow graph as a variable override Shared ownership to easily meet the facade interfaces

#### struct `UInterchangeChaosClothAssetFactory::FRenderMeshPayloadData`  
`struct FRenderMeshPayloadData`  
_L41-46_
- desc: All the render data that we extract from a single render mesh prim
- L43 _public member_ `FString MeshFactoryNodeUid;`
- L44 _public member_ `UE::Interchange::FMeshPayload MeshPayload;`
- L45 _public member_ `TMap<FName, TSet<int32>> RenderPatterns;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API INTERCHANGECHAOSCLOTHASSETIMPORT_API`
- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace Interchange` (scope `UE`)

### `Plugins/Interchange/Extensions/ChaosClothAsset/Source/Import/Public/InterchangeChaosClothAssetFactoryNode.h` (Public)


#### class `UInterchangeChaosClothAssetFactoryNode`  
`class UInterchangeChaosClothAssetFactoryNode : public UInterchangeFactoryBaseNode`  
_L12-79_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UInterchangeFactoryBaseNode`
- L17 _public prototype_ `virtual FString GetTypeName() const override;`
- L18 _public prototype_ `virtual class UClass* GetObjectClass() const override;`
- L23 _public prototype_ `bool GetImportSimulationMeshes(bool& OutImportSimulationMeshes) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Chaos | Cloth")` — Gets whether to import the simulation mesh into the final ClothAsset
- L27 _public prototype_ `bool SetImportSimulationMeshes(bool ImportSimulationMeshes);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Chaos | Cloth")` — Sets whether to import the simulation mesh into the final ClothAsset
- L31 _public prototype_ `bool GetImportRenderMeshes(bool& OutImportRenderMeshes) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Chaos | Cloth")` — Gets whether to import the render mesh into the final ClothAsset
- L35 _public prototype_ `bool SetImportRenderMeshes(bool ImportRenderMeshes);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Chaos | Cloth")` — Sets whether to import the render mesh into the final ClothAsset
- L39 _public prototype_ `bool GetDataflowGraphPath(FSoftObjectPath& OutDataflowGraphPath) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Chaos | Cloth")` — Gets the content path to the Dataflow graph template to instantiate into the generated cloth asset
- L43 _public prototype_ `bool SetDataflowGraphPath(const FSoftObjectPath& DataflowGraphPath);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Chaos | Cloth")` — Sets the content path to the Dataflow graph template to instantiate into the generated cloth asset
- L47 _public prototype_ `bool GetAirDamping(float& OutAirDamping) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Chaos | Cloth | Solver")`
- L50 _public prototype_ `bool SetAirDamping(float AirDamping);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Chaos | Cloth | Solver")`
- L53 _public prototype_ `bool GetGravity(FVector3f& OutGravity) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Chaos | Cloth | Solver")`
- L56 _public prototype_ `bool SetGravity(const FVector3f& Gravity);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Chaos | Cloth | Solver")`
- L59 _public prototype_ `bool GetSubStepCount(int32& OutSubStepCount) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Chaos | Cloth | Solver")`
- L62 _public prototype_ `bool SetSubStepCount(int32 SubStepCount);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Chaos | Cloth | Solver")`
- L65 _public prototype_ `bool GetTimeStep(float& OutTimeStep) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Chaos | Cloth | Solver")`
- L68 _public prototype_ `bool SetTimeStep(float TimeStep);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Chaos | Cloth | Solver")`
- L71 _private prototype_ `IMPLEMENT_NODE_ATTRIBUTE_KEY(ImportSimulationMeshes);`
- L72 _private prototype_ `IMPLEMENT_NODE_ATTRIBUTE_KEY(ImportRenderMeshes);`
- L73 _private prototype_ `IMPLEMENT_NODE_ATTRIBUTE_KEY(DataflowGraphPath);`
- L75 _private prototype_ `IMPLEMENT_NODE_ATTRIBUTE_KEY(AirDamping);`
- L76 _private prototype_ `IMPLEMENT_NODE_ATTRIBUTE_KEY(Gravity);`
- L77 _private prototype_ `IMPLEMENT_NODE_ATTRIBUTE_KEY(SubStepCount);`
- L78 _private prototype_ `IMPLEMENT_NODE_ATTRIBUTE_KEY(TimeStep);`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API INTERCHANGECHAOSCLOTHASSETIMPORT_API`

### `Plugins/Interchange/Extensions/ChaosClothAsset/Source/Import/Public/InterchangeChaosClothAssetImportModule.h` (Public)


#### class `FInterchangeChaosClothAssetImportModule`  
`class FInterchangeChaosClothAssetImportModule : public IModuleInterface`  
_L8-13_
- inherits: `IModuleInterface`
- L11 _public prototype_ `virtual void StartupModule() override;`
- L12 _public prototype_ `virtual void ShutdownModule() override;`

### `Plugins/Interchange/Extensions/ChaosClothAsset/Source/Import/Public/InterchangeChaosClothAssetPayloadData.h` (Public)


#### class `UInterchangeChaosClothAssetPayloadData`  
`class UInterchangeChaosClothAssetPayloadData : public UInterchangeGenericPayloadData`  
_L13-29_
- reflection: `UCLASS()`
- inherits: `UInterchangeGenericPayloadData`
- desc: Cloth-specific payload data provided for a Mesh prim
- L22 _public member_ `TSharedPtr<FManagedArrayCollection> Collection;` — Collection extracted from the Mesh. Currently this is used only for simulation data. Owned by SharedPtr to easily meet Cloth Facade interfaces
- L28 _public member_ `TMap<FName, TSet<int32>> RenderPatterns;` — Mesh render data is mostly provided via the standard Interchange mesh payloads. We need this one additional bit of data for cloth render meshes however

### `Plugins/Interchange/Extensions/ChaosClothAsset/Source/Import/Public/InterchangeChaosClothAssetPipeline.h` (Public)


#### class `UInterchangeChaosClothAssetPipeline`  
`class UInterchangeChaosClothAssetPipeline : public UInterchangePipelineBase`  
_L16-53_
- reflection: `UCLASS(MinimalAPI, BlueprintType, editinlinenew)`
- inherits: `UInterchangePipelineBase`
- L21 _public prototype_ `static FString GetPipelineCategory(UClass* AssetClass);`
- L25 _public member_ `FString PipelineDisplayName;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cloth Assets", meta = (StandAlonePipelineProperty = "True", PipelineInternalEditionData = "True"))` — The name of the pipeline that will be displayed in the import dialog.
- L29 _public member_ `bool bImportClothAssets = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cloth Assets")` — If enabled, import all cloth assets found in the source.
- L33 _public member_ `bool bImportSimulationMeshes = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cloth Assets", meta = (EditCondition = "bImportClothAssets"))` — Whether to add simulation data to the produced cloth collection
- L37 _public member_ `bool bImportRenderMeshes = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cloth Assets", meta = (EditCondition = "bImportClothAssets"))` — Whether to add render data to the produced cloth collection
- L46 _public member_ `FSoftObjectPath DataflowGraphAsset;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cloth Assets", meta = (StandAlonePipelineProperty = "True", PipelineInternalEditionData = "True", AllowedClasses = "/Script/DataflowEngine.Dataflow"))` — Template of the dataflow graph that should be used on the spawned cloth assets. This pipeline will only set this on the produced cloth factory nodes. The cloth factory that ultimately will instantiate the template graph and add it to the spawned cloth asset.
- L49 _public prototype_ `virtual void ExecutePipeline(UInterchangeBaseNodeContainer* BaseNodeContainer, const TArray<UInterchangeSourceData*>& SourceDatas, const FString& ContentBasePath) override;`
- L51 _public prototype_ `virtual void GetSupportAssetClasses(TArray<UClass*>& PipelineSupportAssetClasses) const override;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API INTERCHANGECHAOSCLOTHASSETIMPORT_API`
