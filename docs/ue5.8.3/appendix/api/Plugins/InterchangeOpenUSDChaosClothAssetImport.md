# Plugins / InterchangeOpenUSDChaosClothAssetImport

- module root: `Plugins/Interchange/Extensions/OpenUSDChaosClothAsset/Source/Import`
- headers: 4; symbols: 92
- symbol kinds: class=3, macro=2, member=2, namespace=7, prototype=11, variable=67
- PrivateDependencyModuleNames: Chaos, ChaosClothAsset, ChaosClothAssetDataflowNodes, ChaosClothAssetEngine, InterchangeChaosClothAssetImport, InterchangeCore, InterchangeEngine, InterchangeFactoryNodes, InterchangeNodes, InterchangeOpenUSDImport, InterchangePipelines, MeshDescription, StaticMeshDescription, USDClasses, USDUtilities, UnrealUSDWrapper
- PublicDependencyModuleNames: Core, CoreUObject, Engine

### `Plugins/Interchange/Extensions/OpenUSDChaosClothAsset/Source/Import/Public/InterchangeOpenUSDChaosClothAssetDefinitions.h` (Public)


#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace Interchange` (scope `UE`)
- L7 _namespace_ `namespace USD` (scope `UE::Interchange`)
- L7 _namespace_ `namespace ChaosCloth` (scope `UE::Interchange::USD`)
- L10 _variable_ `inline const FString ClothRootAPI = TEXT("Clo` (scope `UE::Interchange::USD::ChaosCloth`) — Schema names
- L11 _variable_ `inline const FString ChaosSolverPropertiesAPI = TEXT("Cha` (scope `UE::Interchange::USD::ChaosCloth`)
- L12 _variable_ `inline const FString CloSolverPropertiesAPI = TEXT("Clo` (scope `UE::Interchange::USD::ChaosCloth`)
- L13 _variable_ `inline const FString SimMeshDataAPI = TEXT("Sim` (scope `UE::Interchange::USD::ChaosCloth`)
- L14 _variable_ `inline const FString CloFabricAPI = TEXT("Clo` (scope `UE::Interchange::USD::ChaosCloth`)
- L15 _variable_ `inline const FString SimPatternAPI = TEXT("Sim` (scope `UE::Interchange::USD::ChaosCloth`)
- L16 _variable_ `inline const FString RenderPatternAPI = TEXT("Ren` (scope `UE::Interchange::USD::ChaosCloth`)
- L17 _variable_ `inline const FString SewingAPI = TEXT("Sew` (scope `UE::Interchange::USD::ChaosCloth`)
- L18 _variable_ `inline const FString SpringAPI = TEXT("Spr` (scope `UE::Interchange::USD::ChaosCloth`)
- L21 _variable_ `inline const FString ClothSolverAPIPropertiesPrefix = TEXT("sol` (scope `UE::Interchange::USD::ChaosCloth`) — Properties of the ChaosSolverPropertiesAPI/CloSolverPropertiesAPI schemas
- L22 _variable_ `inline const FString ClothSolverAPIPropertiesSuffix = TEXT("pro` (scope `UE::Interchange::USD::ChaosCloth`)
- L25 _variable_ `inline const FString SolverNumIterations = TEXT("num` (scope `UE::Interchange::USD::ChaosCloth`) — Properties of the ChaosSolverPropertiesAPI schema
- L26 _variable_ `inline const FString SolverNumSubseps = TEXT("num` (scope `UE::Interchange::USD::ChaosCloth`)
- L29 _variable_ `inline const FString SolverAirDamping = TEXT("air` (scope `UE::Interchange::USD::ChaosCloth`) — Properties of the CloSolverPropertiesAPI schema
- L30 _variable_ `inline const FString SolverAvatarClothDetection_EdgeEdge = TEXT("ava` (scope `UE::Interchange::USD::ChaosCloth`)
- L31 _variable_ `inline const FString SolverAvatarClothDetection_TriangleVertex = TEXT("ava` (scope `UE::Interchange::USD::ChaosCloth`)
- L32 _variable_ `inline const FString SolverGravity = TEXT("gra` (scope `UE::Interchange::USD::ChaosCloth`)
- L33 _variable_ `inline const FString SolverIntersectionResolution = TEXT("int` (scope `UE::Interchange::USD::ChaosCloth`)
- L34 _variable_ `inline const FString SolverLayerBasedCollisionDetection = TEXT("lay` (scope `UE::Interchange::USD::ChaosCloth`)
- L35 _variable_ `inline const FString SolverProximityDetection_EdgeEdge = TEXT("pro` (scope `UE::Interchange::USD::ChaosCloth`)
- L36 _variable_ `inline const FString SolverProximityDetection_VertexTriangle = TEXT("pro` (scope `UE::Interchange::USD::ChaosCloth`)
- L37 _variable_ `inline const FString SolverSelfCollisionDetection_AvoidanceStiffness = TEXT("sel` (scope `UE::Interchange::USD::ChaosCloth`)
- L38 _variable_ `inline const FString SolverSelfCollisionDetection_EdgeEdge = TEXT("sel` (scope `UE::Interchange::USD::ChaosCloth`)
- L39 _variable_ `inline const FString SolverSelfCollisionDetection_TriangleVertex = TEXT("sel` (scope `UE::Interchange::USD::ChaosCloth`)
- L40 _variable_ `inline const FString SolverSubStepCount = TEXT("sub` (scope `UE::Interchange::USD::ChaosCloth`)
- L41 _variable_ `inline const FString SolverTimeStep = TEXT("tim` (scope `UE::Interchange::USD::ChaosCloth`)
- L44 _variable_ `inline const FString SimMeshDataRestPositionScale = TEXT("res` (scope `UE::Interchange::USD::ChaosCloth`) — Properties of the SimMeshDataAPI schema
- L47 _variable_ `inline const FString CloFabricBendingBiasLeft = TEXT("pri` (scope `UE::Interchange::USD::ChaosCloth`) — Properties of the CloFabricAPI schema
- L48 _variable_ `inline const FString CloFabricBendingBiasRight = TEXT("pri` (scope `UE::Interchange::USD::ChaosCloth`)
- L49 _variable_ `inline const FString CloFabricBendingWarp = TEXT("pri` (scope `UE::Interchange::USD::ChaosCloth`)
- L50 _variable_ `inline const FString CloFabricBendingWeft = TEXT("pri` (scope `UE::Interchange::USD::ChaosCloth`)
- L51 _variable_ `inline const FString CloFabricBucklingRatioBiasLeft = TEXT("pri` (scope `UE::Interchange::USD::ChaosCloth`)
- L52 _variable_ `inline const FString CloFabricBucklingRatioBiasRight = TEXT("pri` (scope `UE::Interchange::USD::ChaosCloth`)
- L53 _variable_ `inline const FString CloFabricBucklingRatioWarp = TEXT("pri` (scope `UE::Interchange::USD::ChaosCloth`)
- L54 _variable_ `inline const FString CloFabricBucklingRatioWeft = TEXT("pri` (scope `UE::Interchange::USD::ChaosCloth`)
- L55 _variable_ `inline const FString CloFabricBucklingStiffnessBiasLeft = TEXT("pri` (scope `UE::Interchange::USD::ChaosCloth`)
- L56 _variable_ `inline const FString CloFabricBucklingStiffnessBiasRight = TEXT("pri` (scope `UE::Interchange::USD::ChaosCloth`)
- L57 _variable_ `inline const FString CloFabricBucklingStiffnessWarp = TEXT("pri` (scope `UE::Interchange::USD::ChaosCloth`)
- L58 _variable_ `inline const FString CloFabricBucklingStiffnessWeft = TEXT("pri` (scope `UE::Interchange::USD::ChaosCloth`)
- L59 _variable_ `inline const FString CloFabricDensity = TEXT("pri` (scope `UE::Interchange::USD::ChaosCloth`)
- L60 _variable_ `inline const FString CloFabricFriction = TEXT("pri` (scope `UE::Interchange::USD::ChaosCloth`)
- L61 _variable_ `inline const FString CloFabricInternalDamping = TEXT("pri` (scope `UE::Interchange::USD::ChaosCloth`)
- L62 _variable_ `inline const FString CloFabricShearLeft = TEXT("pri` (scope `UE::Interchange::USD::ChaosCloth`)
- L63 _variable_ `inline const FString CloFabricShearRight = TEXT("pri` (scope `UE::Interchange::USD::ChaosCloth`)
- L64 _variable_ `inline const FString CloFabricShrinkage = TEXT("pri` (scope `UE::Interchange::USD::ChaosCloth`)
- L65 _variable_ `inline const FString CloFabricStretchWarp = TEXT("pri` (scope `UE::Interchange::USD::ChaosCloth`)
- L66 _variable_ `inline const FString CloFabricStretchWeft = TEXT("pri` (scope `UE::Interchange::USD::ChaosCloth`)
- L67 _variable_ `inline const FString CloFabricThickness = TEXT("pri` (scope `UE::Interchange::USD::ChaosCloth`)
- L68 _variable_ `inline const FString CloFabricBendingStiffness = TEXT("pri` (scope `UE::Interchange::USD::ChaosCloth`)
- L69 _variable_ `inline const FString CloFabricBendingStiffnessScale = TEXT("pri` (scope `UE::Interchange::USD::ChaosCloth`)
- L70 _variable_ `inline const FString CloFabricBendingWingInversed = TEXT("pri` (scope `UE::Interchange::USD::ChaosCloth`)
- L71 _variable_ `inline const FString CloFabricBucklingRatio = TEXT("pri` (scope `UE::Interchange::USD::ChaosCloth`)
- L72 _variable_ `inline const FString CloFabricBucklingScale = TEXT("pri` (scope `UE::Interchange::USD::ChaosCloth`)
- L73 _variable_ `inline const FString CloFabricDamp = TEXT("pri` (scope `UE::Interchange::USD::ChaosCloth`)
- L74 _variable_ `inline const FString CloFabricStiffness = TEXT("pri` (scope `UE::Interchange::USD::ChaosCloth`)
- L77 _variable_ `inline const FString ChaosFabricDensities = TEXT("pri` (scope `UE::Interchange::USD::ChaosCloth`) — Properties of the ChaosFabricAPI schema
- L78 _variable_ `inline const FString ChaosFabricEdgeStiffnesses = TEXT("pri` (scope `UE::Interchange::USD::ChaosCloth`)
- L79 _variable_ `inline const FString ChaosFabricBendingStiffnesses = TEXT("pri` (scope `UE::Interchange::USD::ChaosCloth`)
- L80 _variable_ `inline const FString ChaosFabricBucklingRatios = TEXT("pri` (scope `UE::Interchange::USD::ChaosCloth`)
- L81 _variable_ `inline const FString ChaosFabricBucklingStiffnesses = TEXT("pri` (scope `UE::Interchange::USD::ChaosCloth`)
- L82 _variable_ `inline const FString ChaosFabricFlatnessRatios = TEXT("pri` (scope `UE::Interchange::USD::ChaosCloth`)
- L83 _variable_ `inline const FString ChaosFabricAreaStiffnesses = TEXT("pri` (scope `UE::Interchange::USD::ChaosCloth`)
- L84 _variable_ `inline const FString ChaosFabricCollisionThicknesses = TEXT("pri` (scope `UE::Interchange::USD::ChaosCloth`)
- L85 _variable_ `inline const FString ChaosFabricFrictionCoefficients = TEXT("pri` (scope `UE::Interchange::USD::ChaosCloth`)
- L86 _variable_ `inline const FString ChaosFabricDrags = TEXT("pri` (scope `UE::Interchange::USD::ChaosCloth`)
- L87 _variable_ `inline const FString ChaosFabricLifts = TEXT("pri` (scope `UE::Interchange::USD::ChaosCloth`)
- L88 _variable_ `inline const FString ChaosFabricPressures = TEXT("pri` (scope `UE::Interchange::USD::ChaosCloth`)

### `Plugins/Interchange/Extensions/OpenUSDChaosClothAsset/Source/Import/Public/InterchangeOpenUSDChaosClothAssetImportModule.h` (Public)


#### class `FInterchangeOpenUSDChaosClothAssetImportModule`  
`class FInterchangeOpenUSDChaosClothAssetImportModule : public IModuleInterface`  
_L8-16_
- inherits: `IModuleInterface`
- L11 _public prototype_ `virtual void StartupModule() override;`
- L12 _public prototype_ `virtual void ShutdownModule() override;`
- L15 _private member_ `FString RegisteredHandlerName;`

### `Plugins/Interchange/Extensions/OpenUSDChaosClothAsset/Source/Import/Public/InterchangeOpenUSDChaosClothAssetPipeline.h` (Public)


#### class `UInterchangeOpenUSDChaosClothAssetPipeline`  
`class UInterchangeOpenUSDChaosClothAssetPipeline : public UInterchangePipelineBase`  
_L16-46_
- reflection: `UCLASS(MinimalAPI, BlueprintType, editinlinenew)`
- inherits: `UInterchangePipelineBase`
- L21 _public prototype_ `static FString GetPipelineCategory(UClass* AssetClass);`
- L25 _public member_ `FString PipelineDisplayName;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cloth Assets", meta = (StandAlonePipelineProperty = "True", PipelineInternalEditionData = "True"))` — The name of the pipeline that will be displayed in the import dialog.
- L45 _public prototype_ `virtual void ExecutePipeline(UInterchangeBaseNodeContainer* BaseNodeContainer, const TArray<UInterchangeSourceData*>& SourceDatas, const FString& ContentBasePath) override;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API INTERCHANGEOPENUSDCHAOSCLOTHASSETIMPORT_API`

### `Plugins/Interchange/Extensions/OpenUSDChaosClothAsset/Source/Import/Public/InterchangeOpenUSDChaosClothAssetRootSchemaHandler.h` (Public)


#### class `UE::Interchange::USD::FInterchangeOpenUSDChaosClothAssetRootSchemaHandler`  
`class FInterchangeOpenUSDChaosClothAssetRootSchemaHandler : public FSchemaHandler`  
_L13-38_
- inherits: `FSchemaHandler`
- L16 _public prototype_ `virtual const FString& GetHandlerName() const override;`
- L18 _public prototype_ `virtual const FString& GetTargetSchemaName() const override;`
- L20 _public prototype_ `virtual bool CanHandlePrim(const UE::FUsdPrim& Prim, const UInterchangeUsdContext& UsdContext) const override;`
- L22 _public prototype_ `virtual TOptional<bool> CanBeCollapsed(const UE::FUsdPrim& Prim, UInterchangeUsdContext& UsdContext) const override;`
- L24 _public prototype_ `virtual TOptional<bool> CollapsesChildren(const UE::FUsdPrim& Prim, UInterchangeUsdContext& UsdContext) const override;`
- L26 _public prototype_ `virtual bool OnTranslate( const UE::FUsdPrim& Prim, FTraversalInfo& TraversalInfo, FHandlerAccumulatedInfo& AccumulatedInfo, UInterchangeUsdContext& UsdContext ) override;`
- L33 _public prototype_ `virtual bool OnGetGenericPayloadData( const FString& PayloadKey, UInterchangeUsdContext& UsdContext, TObjectPtr<UInterchangeGenericPayloadData>& InOutPayloadData );`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API INTERCHANGEOPENUSDCHAOSCLOTHASSETIMPORT_API`
- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace Interchange` (scope `UE`)
- L11 _namespace_ `namespace USD` (scope `UE::Interchange`)
