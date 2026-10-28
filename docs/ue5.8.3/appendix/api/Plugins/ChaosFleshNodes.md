# Plugins / ChaosFleshNodes

- module root: `Plugins/Experimental/ChaosFlesh/Source/ChaosFleshNodes`
- headers: 34; symbols: 431
- symbol kinds: class=2, delegate=3, enum=4, enumerator=10, function=45, member=218, namespace=10, prototype=74, struct=48, typedef=17
- PrivateDependencyModuleNames: ChaosCaching
- PublicDependencyModuleNames: Chaos, ChaosCore, ChaosFlesh, ChaosFleshEngine, Core, CoreUObject, DataflowCore, DataflowEngine, DataflowSimulation, Engine, GeometryAlgorithms, GeometryCollectionEngine, GeometryCore, GeometryFramework, MeshConversion, MeshConversionEngineTypes, MeshDescription, SkeletalMeshDescription, TetMeshing

### `Plugins/Experimental/ChaosFlesh/Source/ChaosFleshNodes/Public/Dataflow/ChaosFleshAddKinematicParticlesNode.h` (Public)


#### struct `FAddKinematicParticlesDataflowNode`  
`struct FAddKinematicParticlesDataflowNode : public FDataflowNode`  
_L15-58_
- reflection: `USTRUCT(meta = (DataflowFlesh))`
- inherits: `FDataflowNode`
- L21 _public typedef_ `typedef FManagedArrayCollection DataType;`
- L24 _public member_ `FTransform Transform;` — `UPROPERTY(EditAnywhere, Category = "Dataflow")`
- L27 _public member_ `ESkeletalSeletionMode SkeletalSelectionMode = ESkeletalSeletionMode::Dataflow_SkeletalSelection_Single;` — `UPROPERTY(EditAnywhere, Category = "Dataflow")`
- L30 _public member_ `FManagedArrayCollection Collection;` — `UPROPERTY(meta = (DataflowInput, DataflowOutput, DisplayName = "Collection", DataflowPassthrough = "Collection"))`
- L33 _public member_ `TObjectPtr<USkeletalMesh> SkeletalMeshIn;` — `UPROPERTY(meta = (DataflowInput, DisplayName = "SkeletalMesh"))`
- L36 _public member_ `TArray<int32> VertexIndicesIn;` — `UPROPERTY(meta = (DataflowInput, DisplayName = "SelectionSet"))`
- L39 _public member_ `int32 BoneIndexIn = 0;` — `UPROPERTY(meta = (DataflowInput, DisplayName = "BoneIndex"))`
- L42 _public member_ `TArray<int32> TargetIndicesOut;` — `UPROPERTY(meta = (DataflowOutput, DisplayName = "TargetIndices"))`
- L46 _public function_ `FAddKinematicParticlesDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowNode(InParam, InGuid)`
- L57 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

### `Plugins/Experimental/ChaosFlesh/Source/ChaosFleshNodes/Public/Dataflow/ChaosFleshAppendTetrahedralCollectionNode.h` (Public)


#### struct `FAppendTetrahedralCollectionDataflowNode_v2`  
`struct FAppendTetrahedralCollectionDataflowNode_v2 : public FDataflowNode`  
_L20-51_
- reflection: `USTRUCT(meta = (DataflowFlesh))`
- inherits: `FDataflowNode`
- desc: Append another Tetrahedral Collection to this collection. All attributes will be appended to the end.
- L29 _private member_ `FManagedArrayCollection Collection;` — `UPROPERTY(meta = (DataflowInput, DataflowOutput, DataflowPassthrough = "Collection", DataflowRenderGroups = "Surface"))`
- L32 _private member_ `FManagedArrayCollection CollectionToAppend;` — `UPROPERTY(meta = (DataflowInput))`
- L36 _private member_ `bool bMergeTransform = false;` — `UPROPERTY(EditAnywhere, Category = "Dataflow", meta = (DisplayName = "Merge Transform"))` — If checked, non-geometry transforms from CollectionToAppend are merged into Collection by matching transform names.
- L39 _private member_ `FDataflowGeometrySelection CollectionGeometrySelection;` — `UPROPERTY(meta = (DataflowOutput))`
- L42 _private member_ `FDataflowGeometrySelection CollectionToAppendGeometrySelection;` — `UPROPERTY(meta = (DataflowOutput))`
- L45 _private member_ `TArray<FString> CollectionGeometryGroupGuids;` — `UPROPERTY(meta = (DataflowOutput))`
- L48 _private member_ `TArray<FString> CollectionToAppendGeometryGroupGuids;` — `UPROPERTY(meta = (DataflowOutput))`
- L50 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FAppendTetrahedralCollectionDataflowNode`  
`struct FAppendTetrahedralCollectionDataflowNode : public FDataflowNode`  
_L57-98_
- reflection: `USTRUCT(meta = (Deprecated = "5.7"))`
- inherits: `FDataflowNode`
- desc: Append another Tetrahedral Collection to this collection. All attributes will be copied.
- L64 _public member_ `FManagedArrayCollection Collection1;` — `UPROPERTY(meta = (DataflowInput, DataflowOutput, DisplayName = "Collection1", DataflowPassthrough = "Collection1", DataflowRenderGroups = "Surface"))`
- L67 _public member_ `FManagedArrayCollection Collection2;` — `UPROPERTY(meta = (DataflowInput, DisplayName = "Collection2"))`
- L71 _public member_ `bool bMergeTransform = false;` — `UPROPERTY(EditAnywhere, Category = "Dataflow", meta = (DisplayName = "Merge Transform"))` — if transforms from Collection2 are merged into Collection1 by matching transform name
- L74 _public member_ `FDataflowGeometrySelection GeometrySelection1;` — `UPROPERTY(meta = (DataflowOutput))`
- L77 _public member_ `FDataflowGeometrySelection GeometrySelection2;` — `UPROPERTY(meta = (DataflowOutput))`
- L80 _public member_ `TArray<FString> GeometryGroupGuidsOut1;` — `UPROPERTY(meta = (DataflowOutput, DisplayName = "GeometryGroupGuids1"))`
- L83 _public member_ `TArray<FString> GeometryGroupGuidsOut2;` — `UPROPERTY(meta = (DataflowOutput, DisplayName = "GeometryGroupGuids2"))`
- L85 _public function_ `FAppendTetrahedralCollectionDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowNode(InParam, InGuid)`
- L97 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FDeleteFleshVerticesDataflowNode`  
`struct FDeleteFleshVerticesDataflowNode : public FDataflowNode`  
_L104-125_
- reflection: `USTRUCT(meta = (DataflowFlesh))`
- inherits: `FDataflowNode`
- desc: Extract a Tetrahedral Collection from this collection based on selected vertex. Compatible attributes will be copied.
- L111 _public member_ `FManagedArrayCollection Collection;` — `UPROPERTY(meta = (DataflowInput, DataflowIntrinsic, DataflowOutput, DataflowPassthrough = "Collection"))`
- L114 _public member_ `FDataflowVertexSelection VertexSelection;` — `UPROPERTY(meta = (DataflowInput, DataflowIntrinsic))`
- L116 _public function_ `FDeleteFleshVerticesDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowNode(InParam, InGuid)`
- L124 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

### `Plugins/Experimental/ChaosFlesh/Source/ChaosFleshNodes/Public/Dataflow/ChaosFleshAuthorSceneCollisionCandidatesNode.h` (Public)


#### struct `FAuthorSceneCollisionCandidates`  
`struct FAuthorSceneCollisionCandidates : public FDataflowNode`  
_L18-52_
- reflection: `USTRUCT(meta = (DataflowFlesh))`
- inherits: `FDataflowNode`
- desc: Marks mesh vertices as candidates for scene collision raycasts.  Each vertex has an associated bone index to use as the origin of the raycast.  The runtime distance between the vertex and the bone designates the range of the scene query depth.
- L24 _public typedef_ `typedef FManagedArrayCollection DataType;`
- L27 _public member_ `FManagedArrayCollection Collection;` — `UPROPERTY(meta = (DataflowInput, DataflowOutput, DisplayName = "Collection", DataflowPassthrough = "Collection"))`
- L31 _public member_ `bool bSurfaceVerticesOnly = true;` — `UPROPERTY(EditAnywhere, Category = "Dataflow")` — Restricts vertices to only ones on the surface.  All vertices otherwise.
- L36 _public member_ `TArray<int32> VertexIndices;` — `UPROPERTY(EditAnywhere, Category = "Dataflow", meta = (DataflowInput, DisplayName = "Vertex Indices"))` — Indices to use with environment collisions.  If this input is not connected, then all indicies are used.
- L40 _public member_ `int32 OriginBoneIndex = 0;` — `UPROPERTY(EditAnywhere, Category = "Dataflow", meta = (DataflowInput, DisplayName = "Raycast Origin Bone Index"))` — Bone index to use as the world raycast origin.  -1 denotes the component transform.
- L42 _public function_ `FAuthorSceneCollisionCandidates(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowNode(InParam, InGuid)`
- L51 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### Free symbols / members of external scopes

- L10 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogAuthorSceneCollisionCandidates, Verbose, All);`
- L10 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogAuthorSceneCollisionCandidates, Verbose, All);`

### `Plugins/Experimental/ChaosFlesh/Source/ChaosFleshNodes/Public/Dataflow/ChaosFleshCalculateTetrehedralMetricsNode.h` (Public)


#### struct `FCalculateTetMetrics`  
`struct FCalculateTetMetrics : public FDataflowNode`  
_L15-34_
- reflection: `USTRUCT(meta = (DataflowFlesh))`
- inherits: `FDataflowNode`
- desc: Generate quality metrics
- L20 _public typedef_ `typedef FManagedArrayCollection DataType;`
- L24 _public member_ `FManagedArrayCollection Collection;` — `UPROPERTY(meta = (DataflowInput, DataflowOutput, DataflowPassthrough = "Collection", DisplayName = "Collection"))` — Passthrough geometry collection. Bindings are stored as standalone groups in the \p Collection, keyed by the name of the input render mesh and all available LOD's.
- L26 _public function_ `FCalculateTetMetrics(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowNode(InParam, InGuid)`
- L33 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

### `Plugins/Experimental/ChaosFlesh/Source/ChaosFleshNodes/Public/Dataflow/ChaosFleshCollisionBodyConstraintNode.h` (Public)


#### struct `FKinematicBodySetupInitializationDataflowNode`  
`struct FKinematicBodySetupInitializationDataflowNode : public FDataflowNode`  
_L15-41_
- reflection: `USTRUCT(meta = (DataflowFlesh))`
- inherits: `FDataflowNode`
- L21 _public typedef_ `typedef FManagedArrayCollection DataType;`
- L24 _public member_ `FTransform Transform;` — `UPROPERTY(EditAnywhere, Category = "Dataflow")`
- L27 _public member_ `FManagedArrayCollection Collection;` — `UPROPERTY(meta = (DataflowInput, DataflowOutput, DisplayName = "Collection", DataflowPassthrough = "Collection"))`
- L30 _public member_ `TObjectPtr<USkeletalMesh> SkeletalMeshIn;` — `UPROPERTY(meta = (DataflowInput, DisplayName = "SkeletalMesh"))`
- L32 _public function_ `FKinematicBodySetupInitializationDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowNode(InParam, InGuid)`
- L40 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

### `Plugins/Experimental/ChaosFlesh/Source/ChaosFleshNodes/Public/Dataflow/ChaosFleshComputeFiberFieldNode.h` (Public)


#### struct `FComputeFiberFieldNode`  
`struct FComputeFiberFieldNode : public FDataflowNode`  
_L20-78_
- reflection: `USTRUCT(meta = (DataflowFlesh))`
- inherits: `FDataflowNode`
- desc: Computes a muscle fiber direction per tetrahedron from a GeometryCollection containing tetrahedra, vertices, and origin & insertion vertex fields.  Fiber directions should smoothly follow the geometry oriented from the origin vertices pointing to the insertion vertices.
- L32 _public member_ `TArray<int32> OriginIndices;` — `UPROPERTY(meta = (DataflowInput, DisplayName = "OriginVertexIndices"))`
- L35 _public member_ `TArray<int32> InsertionIndices;` — `UPROPERTY(meta = (DataflowInput, DisplayName = "InsertionVertexIndices"))`
- L38 _public member_ `FString OriginInsertionGroupName = FString();` — `UPROPERTY(EditAnywhere, Category = "Dataflow")`
- L41 _public member_ `FString OriginVertexFieldName = FString("Ori` — `UPROPERTY(EditAnywhere, Category = "Dataflow")`
- L44 _public member_ `FString InsertionVertexFieldName = FString("Ins` — `UPROPERTY(EditAnywhere, Category = "Dataflow")`
- L47 _public member_ `int32 MaxIterations = 100;` — `UPROPERTY(EditAnywhere, Category = "Dataflow")`
- L50 _public member_ `float Tolerance = 1.0e-7f;` — `UPROPERTY(EditAnywhere, Category = "Dataflow")`
- L54 _public member_ `bool bShowMuscleColor = true;` — `UPROPERTY(EditAnywhere, Category = "Dataflow")` — If muscles are colored by the flow from origins (blue) to insertions (red). This becomes optional in 5.6
- L56 _public function_ `FComputeFiberFieldNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowNode(InParam, InGuid)`
- L65 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`
- L67 _public prototype_ `TArray<int32> GetNonZeroIndices(const TArray<uint8>& Map) const;`
- L69 _public prototype_ `void ComputeFiberField( const TManagedArray<FIntVector4>& Elements, const TManagedArray<FVector3f>& Vertex, const TManagedArray<TArray<int32>>& IncidentElements, const TManagedArray<TArray<int32>>& IncidentElementsLocalIndex, const TArray<int32>& Origin, const TArray<int32>& Insertion, TArray<FVector3f>& Directions, TArray<float>& ScalarField) const;`

#### struct `FComputeFiberStreamlineNode`  
`struct FComputeFiberStreamlineNode : public FDataflowNode`  
_L84-133_
- reflection: `USTRUCT(meta = (DataflowFlesh))`
- inherits: `FDataflowNode`
- desc: Computes fiber streamlines (line segments) flowing from muscle origins to insertions in the muscle fiber field.
- L96 _public member_ `TArray<int32> OriginIndices;` — `UPROPERTY(meta = (DataflowInput, DisplayName = "OriginVertexIndices"))`
- L99 _public member_ `TArray<int32> InsertionIndices;` — `UPROPERTY(meta = (DataflowInput, DisplayName = "InsertionVertexIndices"))`
- L102 _public member_ `FString OriginInsertionGroupName = FString();` — `UPROPERTY(EditAnywhere, Category = "Dataflow")`
- L105 _public member_ `FString OriginVertexFieldName = FString("Ori` — `UPROPERTY(EditAnywhere, Category = "Dataflow")`
- L108 _public member_ `FString InsertionVertexFieldName = FString("Ins` — `UPROPERTY(EditAnywhere, Category = "Dataflow")`
- L111 _public member_ `int32 MaxStreamlineIterations = 500;` — `UPROPERTY(EditAnywhere, Category = "Dataflow")`
- L114 _public member_ `int32 MaxPointsPerLine = 20;` — `UPROPERTY(EditAnywhere, Category = "Dataflow")`
- L117 _public member_ `int32 NumLinesMultiplier = 1;` — `UPROPERTY(EditAnywhere, Category = "Dataflow")`
- L120 _public member_ `FFieldCollection VectorField;` — `UPROPERTY(meta = (DataflowOutput, DisplayName = "VectorField"))`
- L122 _public function_ `FComputeFiberStreamlineNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowNode(InParam, InGuid)`
- L132 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

### `Plugins/Experimental/ChaosFlesh/Source/ChaosFleshNodes/Public/Dataflow/ChaosFleshComputeIslandsNode.h` (Public)


#### struct `FComputeIslandsNode`  
`struct FComputeIslandsNode : public FDataflowNode`  
_L13-31_
- reflection: `USTRUCT(meta = (DataflowFlesh))`
- inherits: `FDataflowNode`
- desc: @todo(deprecate)
- L23 _public function_ `FComputeIslandsNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowNode(InParam, InGuid)`
- L30 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

### `Plugins/Experimental/ChaosFlesh/Source/ChaosFleshNodes/Public/Dataflow/ChaosFleshComputeMuscleActivationNode.h` (Public)


#### struct `FComputeMuscleActivationDataNode`  
`struct FComputeMuscleActivationDataNode : public FDataflowNode`  
_L21-49_
- reflection: `USTRUCT(meta = (Deprecated = "5.6"))`
- inherits: `FDataflowNode`
- desc: Please use new version of this node, then use SetMuscleActivationParameter node to set up muscle activation parameters. Computes an orthogonal matrix for each element M = [v,w,u], where v is the fiber direction of that element, w and u are chosen to be orthogonal to v and each other.
- L31 _public member_ `TArray<int32> OriginIndicesIn;` — `UPROPERTY(meta = (DataflowInput, DisplayName = "OriginVertexIndices"))`
- L34 _public member_ `TArray<int32> InsertionIndicesIn;` — `UPROPERTY(meta = (DataflowInput, DisplayName = "InsertionVertexIndices"))`
- L37 _public member_ `float ContractionVolumeScale = 1.f;` — `UPROPERTY(EditAnywhere, Category = "Dataflow")`
- L39 _public function_ `FComputeMuscleActivationDataNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowNode(InParam, InGuid)`
- L48 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FComputeMuscleActivationDataNode_v2`  
`struct FComputeMuscleActivationDataNode_v2 : public FDataflowNode`  
_L55-80_
- reflection: `USTRUCT(meta = (DataflowFlesh))`
- inherits: `FDataflowNode`
- desc: Determines muscles that are eligible for activation and computes muscle activation data.
- L65 _public member_ `TArray<int32> OriginIndicesIn;` — `UPROPERTY(meta = (DataflowInput, DisplayName = "OriginVertexIndices"))`
- L68 _public member_ `TArray<int32> InsertionIndicesIn;` — `UPROPERTY(meta = (DataflowInput, DisplayName = "InsertionVertexIndices"))`
- L70 _public function_ `FComputeMuscleActivationDataNode_v2(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowNode(InParam, InGuid)`
- L79 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### class `FLengthActivationUtils`  
`class FLengthActivationUtils`  
_L82-96_
- L86 _public function_ `static void SetDefaultLengthActivationCurve(FRuntimeFloatCurve& OutCurve)` — Sets a default linear (0,0) -> (1,1) curve

#### struct `FPerMuscleParameter`  
`struct FPerMuscleParameter`  
_L102-126_
- reflection: `USTRUCT()`
- desc: Struct data structure to store per-muscle activation parameters
- L106 _public member_ `bool bCanEditMuscleName = false;` — `UPROPERTY(EditAnywhere, meta = (InlineEditConditionToggle), Category = "Muscle Activation Parameters")`
- L108 _public member_ `FString MuscleName;` — `UPROPERTY(EditAnywhere, meta = (EditCondition = "bCanEditMuscleName"), Category = "Muscle Activation Parameters")`
- L110 _public member_ `float ContractionVolumeScale = 1.f;` — `UPROPERTY(EditAnywhere, Category = "Muscle Activation Parameters", meta = (ClampMin = "0"))`
- L112 _public member_ `float FiberLengthRatioAtMaxActivation = 0.5f;` — `UPROPERTY(EditAnywhere, Category = "Muscle Activation Parameters", meta = (ClampMin = "0", ClampMax = "1"))`
- L114 _public member_ `float MuscleLengthRatioThresholdForMaxActivation = 0.75f;` — `UPROPERTY(EditAnywhere, Category = "Muscle Activation Parameters", meta = (ClampMin = "0", ClampMax = "1"))`
- L116 _public member_ `float InflationVolumeScale = 1.f;` — `UPROPERTY(EditAnywhere, Category = "Muscle Activation Parameters", meta = (ClampMin = "0"))`
- L118 _public member_ `bool bUseLengthActivationCurve = false;` — `UPROPERTY(EditAnywhere, meta = (InlineEditConditionToggle), Category = "Muscle Activation Parameters")`
- L120 _public member_ `FRuntimeFloatCurve LengthActivationCurve;` — `UPROPERTY(EditAnywhere, Category = "Muscle Activation Parameters", meta = (EditCondition = "bUseLengthActivationCurve"))`
- L122 _public function_ `FPerMuscleParameter()`

#### enum `EParameterMethod`  
`enum EParameterMethod : int`  
_L129-133_
- reflection: `UENUM()`
- L131 _public enumerator_ `Global UMETA(DisplayName = "Use global parameters")`
- L132 _public enumerator_ `Custom UMETA(DisplayName = "Override with custom parameters")`

#### struct `FSetMuscleActivationParameterNode`  
`struct FSetMuscleActivationParameterNode : public FDataflowNode`  
_L139-219_
- reflection: `USTRUCT(meta = (DataflowFlesh))`
- inherits: `FDataflowNode`
- desc: Sets per-muscle parameters for custom muscle contraction.
- L146 _public member_ `FManagedArrayCollection Collection;` — `UPROPERTY(meta = (DataflowInput, DataflowOutput, DisplayName = "Collection", DataflowPassthrough = "Collection"))`
- L149 _public member_ `TEnumAsByte<EParameterMethod> ParameterMethod = EParameterMethod::Global;` — `UPROPERTY(EditAnywhere, Category = "Parameter Method", meta = (EditCondition = false))`
- L153 _public member_ `FDataflowFunctionProperty ApplyGlobalParameters;` — `UPROPERTY(EditAnywhere, Category = "Global Parameters", meta = (ButtonImage = "Icons.Refresh"))` — Click on this button to apply global parameters.
- L157 _public member_ `float ContractionVolumeScale = 1.f;` — `UPROPERTY(EditAnywhere, Category = "Global Parameters", DisplayName = "Global Contraction Volume Scale", meta = (ClampMin = "0"))` — Muscles gain volume during contraction if > 1. Volume-preserving if 1. Default: 1
- L161 _public member_ `float GlobalFiberLengthRatioAtMaxActivation = 0.5f;` — `UPROPERTY(EditAnywhere, Category = "Global Parameters", meta = (ClampMin = "0", ClampMax = "1"))` — How much muscle fibers shorten at max activation 1. A smaller value means more contraction in the fiber direction. Default: 0.5
- L165 _public member_ `float GlobalMuscleLengthRatioThresholdForMaxActivation = 0.75f;` — `UPROPERTY(EditAnywhere, Category = "Global Parameters", meta = (ClampMin = "0", ClampMax = "1"))` — Muscle length ratio (defined by origin-insertion distance) below this threshold is considered to reach max activation 1. Default: 0.75
- L169 _public member_ `float GlobalInflationVolumeScale = 1.f;` — `UPROPERTY(EditAnywhere, Category = "Global Parameters", meta = (ClampMin = "0"))` — Inflates muscle rest volume if > 1 and deflates muscle rest volume if < 1. Default: 1
- L172 _public member_ `bool bUseLengthActivationCurve = false;` — `UPROPERTY(EditAnywhere, meta = (InlineEditConditionToggle), Category = "Global Parameters")`
- L178 _public member_ `FRuntimeFloatCurve GlobalLengthActivationCurve;` — `UPROPERTY(EditAnywhere, Category = "Global Parameters", meta = (EditCondition = "bUseLengthActivationCurve"))` — Curve editor for muscle length-activation curve. Default: linear X-axis: normalized muscle length level from 0 (rest state) to 1 (muscle length ratio = Muscle Length Ratio Threshold For Max Activation) Y-axis: muscle activation from 0 to 1
- L182 _public member_ `TObjectPtr<UAnimSequence> AnimationAsset = nullptr;` — `UPROPERTY(EditAnywhere, Category = "Animation Data", meta = (DataflowInput))` — Use minimum muscle lengths across this animation asset to infer MuscleLengthRatioThresholdForMaxActivation
- L188 _public member_ `TObjectPtr<USkeletalMesh> SkeletalMesh = nullptr;` — `UPROPERTY(EditAnywhere, Category = "Animation Data", meta = (DataflowInput))` — Skeletal mesh used to linear blend skin kinematic origins and insertions. This must be the same as the one used to create TransformSource group. Check geometry spreadsheet for more info.
- L194 _public member_ `float ThresholdScalingPercent = 100.f;` — `UPROPERTY(EditAnywhere, Category = "Animation Data", meta = (ClampMin = "0.0", ClampMax = "200.0", UIMin = "0.0", UIMax = "200.0", Units = "Percent"))` — This percentage (usually between 0 and 100%) globally scales minimum muscle lengths computed from the animation asset. For example, if minimum muscle length = 0.5 and ThresholdScalingPercent = 80%, the final MuscleLengthRatioThresholdForMaxActivation for this muscle is 1 - (1 - 0.5) * 80% = 0.6
- L198 _public member_ `FDataflowFunctionProperty ImportLowestMuscleLengthRatio;` — `UPROPERTY(EditAnywhere, Category = "Animation Data", meta = (ButtonImage = "Icons.Import"))` — Click on this button to import the minimum muscle lengths across the animation asset as MuscleLengthRatioThresholdForMaxActivation
- L202 _public member_ `FDataflowFunctionProperty ImportAllMuscleNames;` — `UPROPERTY(EditAnywhere, Category = "Custom Parameters", meta = (ButtonImage = "Icons.Import"))` — Click on this button to import muscle bone names (in the Transform group) from the collection.
- L206 _public member_ `FDataflowFunctionProperty ResetToGlobalParameters;` — `UPROPERTY(EditAnywhere, Category = "Custom Parameters", meta = (ButtonImage = "Icons.Import"))` — Click on this button to reset per-muscle parameters to global parameters.
- L210 _public member_ `FDataflowFunctionProperty ApplyCustomParameters;` — `UPROPERTY(EditAnywhere, Category = "Custom Parameters", meta = (ButtonImage = "Icons.Refresh"))` — Click on this button to apply custom muscle parameters.
- L213 _public member_ `TArray<FPerMuscleParameter> ParameterArray;` — `UPROPERTY(EditAnywhere, Category = "Custom Parameters", DisplayName = "Per-muscle Parameters")`
- L215 _public prototype_ `FSetMuscleActivationParameterNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L217 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`
- L218 _public prototype_ `virtual bool ShouldInvalidateOnPropertyChanged(const FPropertyChangedEvent& InPropertyChangedEvent) const override;`

#### struct `FCurveMuscleName`  
`struct FCurveMuscleName`  
_L225-236_
- reflection: `USTRUCT()`
- desc: Struct data structure to store curve names and muscle names
- L229 _public member_ `FString CurveName;` — `UPROPERTY(EditAnywhere, Category = "Muscle Activation Parameters")`
- L231 _public member_ `FString MuscleName;` — `UPROPERTY(EditAnywhere, Category = "Muscle Activation Parameters")`
- L233 _public prototype_ `FCurveMuscleName() = default;`
- L234 _public function_ `FCurveMuscleName(const FString& InCurveName, const FString& InMuscleName) : CurveName(InCurveName), MuscleName(InMuscleName)`

#### struct `FReadSkeletalMeshCurvesDataflowNode`  
`struct FReadSkeletalMeshCurvesDataflowNode : public FDataflowNode`  
_L239-271_
- reflection: `USTRUCT(meta = (DataflowFlesh))`
- inherits: `FDataflowNode`
- L245 _public prototype_ `FReadSkeletalMeshCurvesDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L249 _private member_ `FManagedArrayCollection Collection;` — `UPROPERTY(meta = (DataflowInput, DataflowOutput, DisplayName = "Collection", DataflowPassthrough = "Collection"))`
- L252 _private member_ `TObjectPtr<const USkeletalMesh> SkeletalMesh = nullptr;` — `UPROPERTY(EditAnywhere, Category = "Dataflow", meta = (DataflowInput, DisplayName = "SkeletalMesh"))`
- L255 _private member_ `FDataflowGeometrySelection GeometrySelection;` — `UPROPERTY(meta = (DataflowOutput))`
- L259 _private member_ `FDataflowFunctionProperty ImportSKMCurveNames;` — `UPROPERTY(EditAnywhere, Category = "Skeletal Mesh Curves", meta = (ButtonImage = "Icons.Import"))` — Click on this button to import curve names from the skeletal mesh.
- L263 _private member_ `FDataflowFunctionProperty AssignSKMCurveToMuscle;` — `UPROPERTY(EditAnywhere, Category = "Skeletal Mesh Curves", meta = (ButtonImage = "Icons.Refresh"))` — Click on this button to assign curve to muscles by name.
- L266 _private member_ `TArray<FCurveMuscleName> CurveMuscleNameArray;` — `UPROPERTY(EditAnywhere, Category = "Skeletal Mesh Curves", DisplayName = "Curve Name/Muscle Name")`
- L268 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`
- L269 _private prototype_ `virtual bool ShouldInvalidateOnPropertyChanged(const FPropertyChangedEvent& InPropertyChangedEvent) const override;`

### `Plugins/Experimental/ChaosFlesh/Source/ChaosFleshNodes/Public/Dataflow/ChaosFleshCreateTetrahedronNode.h` (Public)


#### struct `FCreateTetrahedronDataflowNode`  
`struct FCreateTetrahedronDataflowNode : public FDataflowNode`  
_L23-121_
- reflection: `USTRUCT(meta = (DataflowFlesh))`
- inherits: `FDataflowNode`
- desc: Note: disabled deprecation warnings due to deprecated member: IdealEdgeLength. Can remove these disable/enable pragmas once that member variable is removed.
- L30 _public typedef_ `typedef FManagedArrayCollection DataType;`
- L34 _public member_ `TEnumAsByte<TetMeshingMethod> Method = TetMeshingMethod::IsoStuffing;` — `UPROPERTY(EditAnywhere, Category = "Dataflow")` — Tetrahedral meshing method (TetWild or ISO-stuffing)
- L39 _public member_ `TArray<FString> Selection;` — `UPROPERTY(EditAnywhere, Category = "Dataflow")` — Name of the mesh in the collection. This is defined from the name of the mesh's parent transform. CollectionKey("BoneName","Vertices")
- L47 _public member_ `int32 NumCells = 32;` — `UPROPERTY(EditAnywhere, Category = "Dataflow", meta = (ClampMin = "1", EditCondition = "Method == TetMeshingMethod::IsoStuffing", EditConditionHides))` — General control for density for the tetrahedron.
- L51 _public member_ `double OffsetPercent = 0.05;` — `UPROPERTY(EditAnywhere, Category = "Dataflow", meta = (ClampMin = "-0.5", ClampMax = "0.5", EditCondition = "Method == TetMeshingMethod::IsoStuffing", EditConditionHides))` — Surface offset percentage to increase or decrease the surface alignment.
- L59 _public member_ `double IdealEdgeLengthRel = 0.05;` — `UPROPERTY(EditAnywhere, Category = "Dataflow", meta = (ClampMin = "0.0", EditCondition = "Method == TetMeshingMethod::TetWild", EditConditionHides))` — Desired relative edge length, as a fraction of bounding box size
- L62 _public member_ `double IdealEdgeLength = 0.05;` — `UE_DEPRECATED(5.6, "Use IdealEdgeLengthRel instead, which is relative to the bounding box size")`
- L66 _public member_ `int32 MaxIterations = 80;` — `UPROPERTY(EditAnywhere, Category = "Dataflow", meta = (ClampMin = "1", EditCondition = "Method == TetMeshingMethod::TetWild", EditConditionHides))` — Maximum number of optimization iterations.
- L70 _public member_ `double StopEnergy = 10;` — `UPROPERTY(EditAnywhere, Category = "Dataflow", meta = (ClampMin = "0.0", EditCondition = "Method == TetMeshingMethod::TetWild", EditConditionHides))` — Energy at which to stop optimizing tet quality and accept the result.
- L74 _public member_ `double EpsRel = 1e-3;` — `UPROPERTY(EditAnywhere, Category = "Dataflow", meta = (ClampMin = "0.0", EditCondition = "Method == TetMeshingMethod::TetWild", EditConditionHides))` — Relative tolerance, controlling how closely the mesh must follow the input surface.
- L78 _public member_ `bool bCoarsen = false;` — `UPROPERTY(EditAnywhere, Category = "Dataflow", meta = (EditCondition = "Method == TetMeshingMethod::TetWild", EditConditionHides))` — Coarsen the tet mesh result.
- L82 _public member_ `bool bExtractManifoldBoundarySurface = false;` — `UPROPERTY(EditAnywhere, Category = "Dataflow", meta = (EditCondition = "Method == TetMeshingMethod::TetWild", EditConditionHides))` — Enforce that the output boundary surface should be manifold.
- L86 _public member_ `bool bSkipSimplification = false;` — `UPROPERTY(EditAnywhere, Category = "Dataflow", meta = (EditCondition = "Method == TetMeshingMethod::TetWild", EditConditionHides))` — Skip the initial simplification step.
- L90 _public member_ `bool bInvertOutputTets = false;` — `UPROPERTY(EditAnywhere, Category = "Dataflow", meta = (EditCondition = "Method == TetMeshingMethod::TetWild", EditConditionHides))` — Invert tetrahedra.
- L96 _public member_ `bool bDiscardInteriorTriangles = true;` — `UPROPERTY(EditAnywhere, Category = "Dataflow")` — Common
- L101 _public member_ `FManagedArrayCollection Collection;` — `UPROPERTY(meta = (DataflowInput, DataflowOutput, DisplayName = "Collection"))` — Input pass-through collection. When connected, the generated tetrahedron will be nested into its associated parents transform.
- L106 _public member_ `FManagedArrayCollection SourceCollection;` — `UPROPERTY(meta = (DataflowInput, DisplayName = "SourceCollection"))` — Source collection used to generate the tetrahedron from. Closed geometry within the collections geometry group will be used to generate tetrahedron.
- L108 _public function_ `FCreateTetrahedronDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowNode(InParam, InGuid)`
- L116 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`
- L119 _protected prototype_ `void EvaluateIsoStuffing(UE::Dataflow::FContext& Context, FFleshCollection& InCollection, const UE::Geometry::FDynamicMesh3& DynamicMesh) const;`
- L120 _protected prototype_ `void EvaluateTetWild(UE::Dataflow::FContext& Context, FFleshCollection& InCollection, const UE::Geometry::FDynamicMesh3& DynamicMesh) const;`

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace UE`
- L15 _namespace_ `namespace Geometry` (scope `UE`)

### `Plugins/Experimental/ChaosFlesh/Source/ChaosFleshNodes/Public/Dataflow/ChaosFleshFleshAssetTerminalNode.h` (Public)


#### struct `FFleshAssetTerminalDataflowNode`  
`struct FFleshAssetTerminalDataflowNode : public FDataflowTerminalNode`  
_L16-42_
- reflection: `USTRUCT(meta = (DataflowFlesh, DataflowTerminal))`
- inherits: `FDataflowTerminalNode`
- L27 _public function_ `FFleshAssetTerminalDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowTerminalNode(InParam, InGuid)`
- L35 _public member_ `TObjectPtr<UFleshAsset> FleshAsset = nullptr;` — `UPROPERTY(EditAnywhere, Category = "Dataflow", meta = (DisplayName = "FleshAsset"))`
- L38 _public function_ `virtual TObjectPtr<UObject> GetTerminalAsset() const override` — Return the terminal asset
- L40 _public prototype_ `virtual void SetAssetValue(TObjectPtr<UObject> Asset, UE::Dataflow::FContext& Context) const override;`
- L41 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FCurveSamplingAnimationAssetTerminalNode`  
`struct FCurveSamplingAnimationAssetTerminalNode : public FDataflowTerminalNode`  
_L51-81_
- reflection: `USTRUCT(meta = (DataflowFlesh, DataflowTerminal))`
- inherits: `FDataflowTerminalNode`
- desc: terminal node to create an animation asset for muscle activation MLD training. The animation remains in the rest pose with the curves spiking from 0 to 1 to 0 in each block of frames (Number of frames per muscle) Curves will stay at value 0 most of the time. Only one curve is active at a time. Total animation frames = Frame Rate * Number of frames per muscle
- L61 _public member_ `TObjectPtr<UAnimSequence> AnimationAsset = nullptr;` — `UPROPERTY(EditAnywhere, Category = Asset, meta = (DataflowInput))`
- L65 _public member_ `int32 FrameRate = 30;` — `UPROPERTY(EditAnywhere, Category = "Record Parameter")` — Frame rate of the animation
- L69 _public member_ `int32 NumFramesPerMuscle = 10;` — `UPROPERTY(EditAnywhere, Category = "Record Parameter", DisplayName = "Number of Frames Per Muscle")` — Number of frames created for each curve. Within this window of frames, curve value will go from 0 to 1 to 0.
- L71 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context) const override;`
- L72 _public prototype_ `virtual void SetAssetValue(TObjectPtr<UObject> Asset, UE::Dataflow::FContext& Context) const override;`
- L75 _public function_ `FCurveSamplingAnimationAssetTerminalNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowTerminalNode(InParam, InGuid)`

### `Plugins/Experimental/ChaosFlesh/Source/ChaosFleshNodes/Public/Dataflow/ChaosFleshGenerateOriginInsertionNode.h` (Public)


#### struct `FGenerateOriginInsertionNode`  
`struct FGenerateOriginInsertionNode : public FDataflowNode`  
_L13-51_
- reflection: `USTRUCT(meta = (DataflowFlesh))`
- inherits: `FDataflowNode`
- desc: Given two sets of vertex indices, generate two sets of vertex indices for origins and insertions that are within X distance away.
- L25 _public member_ `TArray<int32> OriginIndicesIn;` — `UPROPERTY(meta = (DataflowInput, DisplayName = "OriginIndicesIn"))`
- L28 _public member_ `TArray<int32> InsertionIndicesIn;` — `UPROPERTY(meta = (DataflowInput, DisplayName = "InsertionIndicesIn"))`
- L31 _public member_ `TArray<int32> OriginIndicesOut;` — `UPROPERTY(meta = (DataflowOutput, DisplayName = "OriginIndicesOut"))`
- L34 _public member_ `TArray<int32> InsertionIndicesOut;` — `UPROPERTY(meta = (DataflowOutput, DisplayName = "InsertionIndicesOut"))`
- L37 _public member_ `float Radius = float(1);` — `UPROPERTY(EditAnywhere, Category = "Dataflow")`
- L39 _public function_ `FGenerateOriginInsertionNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowNode(InParam, InGuid)`
- L50 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

### `Plugins/Experimental/ChaosFlesh/Source/ChaosFleshNodes/Public/Dataflow/ChaosFleshGenerateSkeletalBindingsNode.h` (Public)


#### struct `FGenerateSkeletalBindings`  
`struct FGenerateSkeletalBindings : public FDataflowNode`  
_L18-47_
- reflection: `USTRUCT(meta = (DataflowFlesh))`
- inherits: `FDataflowNode`
- desc: Generate barycentric bindings (used by the FleshDeformer deformer graph) of a render surface to a tetrahedral mesh.
- L24 _public typedef_ `typedef FManagedArrayCollection DataType;`
- L28 _public member_ `FManagedArrayCollection Collection;` — `UPROPERTY(meta = (DataflowInput, DataflowOutput, DisplayName = "Collection", DataflowPassthrough = "Collection"))` — Passthrough geometry collection. Bindings are stored as standalone groups in the \p Collection, keyed by the name of the input render mesh and all available LOD's.
- L31 _public member_ `int32 BoneIndexIn = 0;` — `UPROPERTY(meta = (DataflowInput, DisplayName = "BoneIndex"))`
- L35 _public member_ `TObjectPtr<const USkeletalMesh> SkeletalMeshIn = nullptr;` — `UPROPERTY(EditAnywhere, Category = "Dataflow", meta = (DataflowInput, DisplayName = "SkeletalMesh"))` — The input mesh, whose render surface is used to generate bindings.
- L37 _public function_ `FGenerateSkeletalBindings(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowNode(InParam, InGuid)`
- L46 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### Free symbols / members of external scopes

- L14 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogSkeletalBindings, Verbose, All);`
- L14 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogSkeletalBindings, Verbose, All);`

### `Plugins/Experimental/ChaosFlesh/Source/ChaosFleshNodes/Public/Dataflow/ChaosFleshGenerateSurfaceBindingsNode.h` (Public)


#### struct `FGenerateSurfaceBindings`  
`struct FGenerateSurfaceBindings : public FDataflowNode`  
_L27-96_
- reflection: `USTRUCT(meta = (DataflowFlesh))`
- inherits: `FDataflowNode`
- desc: Generate barycentric bindings (used by the FleshDeformer deformer graph and Geometry Cache generation) of a render surface to a tetrahedral mesh and its surface. If a point is outside of the tetrahedral mesh, find surface embedding within SurfaceProjectionSearchRadius. Embeddings of LOD 0 are color coded in the render view: green: embedded on in a tetrahedron blue: embedded on a surface triangle red: orphan (cannot be embedded) yellow: orphan reparented to a tetrahedron from a node neighbor
- L41 _public prototype_ `.SetCanHidePin(true) .SetPinIsHidden(true);`
- L54 _private member_ `FManagedArrayCollection Collection;` — `UPROPERTY(meta = (DataflowInput, DataflowOutput, DataflowPassthrough = "Collection", DisplayName = "Collection"))` — Collection containing tetrahedral mesh and surface mesh. Bindings are stored as standalone groups in the \p Collection, keyed by the name of the input render mesh and all available LOD's.
- L58 _private member_ `TObjectPtr<const UStaticMesh> StaticMeshIn = nullptr;` — `UPROPERTY(EditAnywhere, Category = "Render Mesh", DisplayName = "Static Mesh", meta = (DataflowInput, EditCondition = "SkeletalMeshIn == nullptr"))` — The input mesh, whose render surface is used to generate bindings.
- L62 _private member_ `TObjectPtr<const USkeletalMesh> SkeletalMeshIn = nullptr;` — `UPROPERTY(EditAnywhere, Category = "Render Mesh", DisplayName = "Skeletal Mesh", meta = (DataflowInput, EditCondition = "StaticMeshIn == nullptr"))` — The input mesh, whose render surface is used to generate bindings.
- L66 _private member_ `FDataflowTransformSelection TransformSelection;` — `UPROPERTY(meta = (DataflowInput, DisplayName = "(Optional) TransformSelection"))` — Render mesh will only bind to geometries whose transforms are in TransformSelection.
- L70 _private member_ `TArray<FString> GeometryGroupGuidsIn;` — `UPROPERTY(meta = (DataflowInput, DisplayName = "(Optional) GeometryGroupGuids"))` — Render mesh will only bind to geometries whose GeometryGroupGuids match here.
- L73 _private member_ `bool bUseSkeletalMeshImportModel = false;` — Use the import geometry of the skeletal mesh.
- L77 _private member_ `TArray<int32> SkeletalMeshLODList;` — `UPROPERTY(EditAnywhere, Category = "Render Mesh", meta = (DisplayName = "Skeletal Mesh LOD List", EditCondition = "SkeletalMeshIn != nullptr && !bUseSkeletalMeshImportModel"))` — Select skeletal mesh LODs to embed. Default empty list selects all LODs.
- L81 _private member_ `bool bDoSurfaceProjection = true;` — `UPROPERTY(EditAnywhere, Category = "Surface Projection", meta = (DisplayName = "DoSurfaceProjection"))` — Enable binding to the exterior hull of the tetrahedron mesh.
- L85 _private member_ `float SurfaceProjectionSearchRadius = 1.f;` — `UPROPERTY(EditAnywhere, Category = "Surface Projection", meta = (DisplayName = "SurfaceProjectionSearchRadius", EditCondition = "bDoSurfaceProjection == true"))` — The search radius when looking for surface triangles to bind to.
- L89 _private member_ `bool bDoOrphanReparenting = true;` — `UPROPERTY(EditAnywhere, Category = "Orphan Reparenting", meta = (DisplayName = "DoOrphanReparenting"))` — When nodes aren't contained in tetrahedra and surface projection fails, try to find suitable bindings by looking to neighboring parents.
- L93 _private member_ `TObjectPtr<UDynamicMesh> SKMDynamicMesh;` — `UPROPERTY(meta = (DataflowOutput))` — Converted from embedded skeletal/static mesh
- L95 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### Free symbols / members of external scopes

- L17 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogMeshBindings, Verbose, All);`
- L17 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogMeshBindings, Verbose, All);`

### `Plugins/Experimental/ChaosFlesh/Source/ChaosFleshNodes/Public/Dataflow/ChaosFleshGetFleshAssetNode.h` (Public)


#### struct `FGetFleshAssetDataflowNode`  
`struct FGetFleshAssetDataflowNode : public FDataflowNode`  
_L13-33_
- reflection: `USTRUCT(meta = (DataflowFlesh))`
- inherits: `FDataflowNode`
- L24 _public member_ `FManagedArrayCollection Output;` — `UPROPERTY(meta = (DataflowOutput, DisplayName = "Collection"))`
- L26 _public function_ `FGetFleshAssetDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowNode(InParam, InGuid)`
- L32 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

### `Plugins/Experimental/ChaosFlesh/Source/ChaosFleshNodes/Public/Dataflow/ChaosFleshGetSurfaceIndicesNode.h` (Public)


#### struct `FGetSurfaceIndicesNode`  
`struct FGetSurfaceIndicesNode : public FDataflowNode`  
_L12-36_
- reflection: `USTRUCT(meta = (DataflowFlesh))`
- inherits: `FDataflowNode`
- L22 _public member_ `TArray<FString> GeometryGroupGuidsIn;` — `UPROPERTY(meta = (DataflowInput, DisplayName = "GeometryGroupGuidsIn"))`
- L25 _public member_ `FDataflowVertexSelection SurfaceVertexSelection;` — `UPROPERTY(meta = (DataflowOutput, DisplayName = "SurfaceVertexSelection"))`
- L27 _public function_ `FGetSurfaceIndicesNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowNode(InParam, InGuid)`
- L35 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### Free symbols / members of external scopes

- L38 _namespace_ `namespace UE`
- L38 _namespace_ `namespace Dataflow` (scope `UE`)
- L40 _prototype_ `void RegisterChaosFleshEngineAssetNodes();` (scope `UE::Dataflow`)

### `Plugins/Experimental/ChaosFlesh/Source/ChaosFleshNodes/Public/Dataflow/ChaosFleshIsolateComponentNode.h` (Public)


#### struct `FIsolateComponentNode`  
`struct FIsolateComponentNode : public FDataflowNode`  
_L13-38_
- reflection: `USTRUCT(meta = (DataflowFlesh))`
- inherits: `FDataflowNode`
- L25 _public member_ `bool bDeleteHiddenFaces = false;` — `UPROPERTY(EditAnywhere, Category = "Dataflow")`
- L28 _public member_ `FString TargetGeometryIndex = "";` — `UPROPERTY(EditAnywhere, Category = "Dataflow")`
- L30 _public function_ `FIsolateComponentNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowNode(InParam, InGuid)`
- L37 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

### `Plugins/Experimental/ChaosFlesh/Source/ChaosFleshNodes/Public/Dataflow/ChaosFleshKinematicConstraintNode.h` (Public)


#### struct `FKinematicInitializationDataflowNode`  
`struct FKinematicInitializationDataflowNode : public FDataflowNode`  
_L15-53_
- reflection: `USTRUCT(meta = (DataflowFlesh))`
- inherits: `FDataflowNode`
- desc: @todo(deprecate), rename to FKinematicConstraintDataflowNode
- L21 _public typedef_ `typedef FManagedArrayCollection DataType;`
- L24 _public member_ `float Radius = 40.f;` — `UPROPERTY(EditAnywhere, Category = "Dataflow")`
- L27 _public member_ `ESkeletalSeletionMode SkeletalSelectionMode = ESkeletalSeletionMode::Dataflow_SkeletalSelection_Single;` — `UPROPERTY(EditAnywhere, Category = "Dataflow")`
- L30 _public member_ `FManagedArrayCollection Collection;` — `UPROPERTY(meta = (DataflowInput, DataflowOutput, DisplayName = "Collection", DataflowPassthrough = "Collection"))`
- L33 _public member_ `TObjectPtr<USkeletalMesh> SkeletalMeshIn;` — `UPROPERTY(meta = (DataflowInput, DisplayName = "SkeletalMesh"))`
- L36 _public member_ `TArray<int32> VertexIndicesIn;` — `UPROPERTY(meta = (DataflowInput, DisplayName = "VertexIndices"))`
- L39 _public member_ `int32 BoneIndexIn = INDEX_NONE;` — `UPROPERTY(meta = (DataflowInput, DisplayName = "BoneIndex"))`
- L42 _public function_ `FKinematicInitializationDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowNode(InParam, InGuid)`
- L52 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

### `Plugins/Experimental/ChaosFlesh/Source/ChaosFleshNodes/Public/Dataflow/ChaosFleshKinematicMuscleAttachmentsNode.h` (Public)


#### struct `FKinematicMuscleAttachmentsDataflowNode`  
`struct FKinematicMuscleAttachmentsDataflowNode : public FDataflowNode`  
_L13-45_
- reflection: `USTRUCT(meta = (DataflowFlesh))`
- inherits: `FDataflowNode`
- L19 _public typedef_ `typedef FManagedArrayCollection DataType;`
- L22 _public member_ `FManagedArrayCollection Collection;` — `UPROPERTY(meta = (DataflowInput, DataflowOutput, DisplayName = "Collection", DataflowPassthrough = "Collection"))`
- L25 _public member_ `TArray<int32> OriginVertexIndicesIn;` — `UPROPERTY(meta = (DataflowInput, DisplayName = "OriginVertexIndices"))`
- L28 _public member_ `TArray<int32> InsertionVertexIndicesIn;` — `UPROPERTY(meta = (DataflowInput, DisplayName = "InsertionVertexIndices"))`
- L31 _public member_ `TObjectPtr<USkeletalMesh> SkeletalMeshIn;` — `UPROPERTY(EditAnywhere, Category = "Dataflow", meta = (DataflowInput, DisplayName = "SkeletalMesh"))`
- L34 _public function_ `FKinematicMuscleAttachmentsDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowNode(InParam, InGuid)`
- L44 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

### `Plugins/Experimental/ChaosFlesh/Source/ChaosFleshNodes/Public/Dataflow/ChaosFleshKinematicSkeletonConstraintNode.h` (Public)


#### struct `FKinematicSkeletonConstraintDataflowNode`  
`struct FKinematicSkeletonConstraintDataflowNode : public FDataflowNode`  
_L14-43_
- reflection: `USTRUCT(meta = (DataflowFlesh))`
- inherits: `FDataflowNode`
- desc: Bind a animation driven skeleton hierarchy into the tetrahedron on the collection.
- L20 _public typedef_ `typedef FManagedArrayCollection DataType;`
- L24 _public member_ `FManagedArrayCollection Collection;` — `UPROPERTY(meta = (DataflowInput, DataflowOutput, DisplayName = "Collection", DataflowPassthrough = "Collection"))` — Pass through collection to place constraints in to.
- L28 _public member_ `TObjectPtr<USkeleton> SkeletonIn = nullptr;` — `UPROPERTY(meta = (DataflowInput, DisplayName = "Skeleton"))` — Skeleton to constraint to the tetrahedron (Must be co-located with the tetrahedron).
- L32 _public member_ `FString ExclusionList = "";` — `UPROPERTY(EditAnywhere, Category = "Dataflow")` — Skeleton bones to exclude from the constraint.
- L34 _public function_ `FKinematicSkeletonConstraintDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowNode(InParam, InGuid)`
- L42 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

### `Plugins/Experimental/ChaosFlesh/Source/ChaosFleshNodes/Public/Dataflow/ChaosFleshMakeFleshAssetNode.h` (Public)


#### struct `FMakeFleshAssetNode`  
`struct FMakeFleshAssetNode : public FDataflowNode`  
_L13-46_
- reflection: `USTRUCT(Meta = (DataflowFlesh))`
- inherits: `FDataflowNode`
- desc: Converts managed array collection to a specified asset.
- L23 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput*) const override;`
- L24 _private prototype_ `virtual TArray<UE::Dataflow::FPin> AddPins() override;`
- L25 _private function_ `virtual bool CanAddPin() const override`
- L26 _private function_ `virtual bool CanRemovePin() const override`
- L27 _private prototype_ `virtual TArray<UE::Dataflow::FPin> GetPinsToRemove() const override;`
- L28 _private prototype_ `virtual void OnPinRemoved(const UE::Dataflow::FPin& Pin) override;`
- L29 _private prototype_ `virtual void PostSerialize(const FArchive& Ar) override;`
- L32 _private prototype_ `TArray<TUniquePtr<FFleshCollection>> GetCleanedCollectionLodValues(UE::Dataflow::FContext& Context) const;`
- L33 _private prototype_ `UE::Dataflow::TConnectionReference<FManagedArrayCollection> GetConnectionReference(int32 Index) const;`
- L37 _private member_ `TArray<FManagedArrayCollection> CollectionLods;` — `UPROPERTY()` — Input collection for this LOD.
- L41 _private member_ `TObjectPtr<UFleshAsset> Asset;` — `UPROPERTY(meta = (DataflowOutput))`
- L44 _private member_ `static constexpr int32 NumRequiredInputs = 0;` — This is for runtime only--used to determine if only properties need to be updated.
- L45 _private member_ `static constexpr int32 NumInitialCollectionLods = 1;`

### `Plugins/Experimental/ChaosFlesh/Source/ChaosFleshNodes/Public/Dataflow/ChaosFleshNodesPlugin.h` (Public)


#### class `IChaosFleshNodesPlugin`  
`class IChaosFleshNodesPlugin : public IModuleInterface`  
_L12-17_
- inherits: `IModuleInterface`
- desc: The public interface to this module
- L15 _public prototype_ `virtual void StartupModule();`
- L16 _public prototype_ `virtual void ShutdownModule();`

### `Plugins/Experimental/ChaosFlesh/Source/ChaosFleshNodes/Public/Dataflow/ChaosFleshNodesUtility.h` (Public)


#### enum `TetMeshingMethod`  
`enum TetMeshingMethod : int`  
_L12-16_
- reflection: `UENUM()`
- L14 _public enumerator_ `IsoStuffing UMETA(DisplayName = "IsoStuffing")`
- L15 _public enumerator_ `TetWild UMETA(DisplayName = "TetWild")`

#### enum `ESkeletalSeletionMode`  
`enum class ESkeletalSeletionMode : uint8`  
_L19-25_
- reflection: `UENUM(BlueprintType)`
- L21 _public enumerator_ `Dataflow_SkeletalSelection_Single UMETA(DisplayName = "Single")`
- L22 _public enumerator_ `Dataflow_SkeletalSelection_Branch UMETA(DisplayName = "Sub-Branch")`
- L24 _public enumerator_ `Chaos_Max UMETA(Hidden)`

#### Free symbols / members of external scopes

- L27 _namespace_ `namespace UE`
- L27 _namespace_ `namespace Dataflow` (scope `UE`)
- L29 _prototype_ `TArray<FIntVector3> GetSurfaceTriangles(const TArray<FIntVector4>& Tets, const bool bKeepInterior);` (scope `UE::Dataflow`)
- L37 _prototype_ `TArray<int32> GetMatchingMeshIndices(const TArray<FString>& MeshNames, const FManagedArrayCollection* InCollection);` (scope `UE::Dataflow`) — GetMatchingMeshIndices Find matching geometry names in the collection. If MeshNames is empty return all the geometry indices. @param MeshNames	: List of name to match, or empty for all indices @param Collection	: Collection to search

### `Plugins/Experimental/ChaosFlesh/Source/ChaosFleshNodes/Public/Dataflow/ChaosFleshRadialTetrahedronNode.h` (Public)


#### struct `FRadialTetrahedronDataflowNodes`  
`struct FRadialTetrahedronDataflowNodes : public FDataflowNode`  
_L16-59_
- reflection: `USTRUCT(meta = (DataflowFlesh))`
- inherits: `FDataflowNode`
- desc: @todo(deprecate), rename to FRadialTetrahedronDataflowNode
- L22 _public typedef_ `typedef FManagedArrayCollection DataType;`
- L25 _public member_ `FManagedArrayCollection Collection;` — `UPROPERTY(meta = (DataflowInput, DataflowOutput, DisplayName = "Collection"))`
- L28 _public member_ `double InnerRadius = double(1.0);` — `UPROPERTY(EditAnywhere, Category = "Dataflow", meta = (ClampMin = "0.0"))`
- L31 _public member_ `double OuterRadius = double(2.0);` — `UPROPERTY(EditAnywhere, Category = "Dataflow", meta = (ClampMin = "0.0"))`
- L34 _public member_ `double Height = double(1.0);` — `UPROPERTY(EditAnywhere, Category = "Dataflow", meta = (ClampMin = "0.0"))`
- L37 _public member_ `int32 RadialSample = 2;` — `UPROPERTY(EditAnywhere, Category = "Dataflow", meta = (ClampMin = "2"))`
- L40 _public member_ `int32 AngularSample = 4;` — `UPROPERTY(EditAnywhere, Category = "Dataflow", meta = (ClampMin = "3"))`
- L43 _public member_ `int32 VerticalSample = 2;` — `UPROPERTY(EditAnywhere, Category = "Dataflow", meta = (ClampMin = "2"))`
- L46 _public member_ `double BulgeRatio = double(0.0);` — `UPROPERTY(EditAnywhere, Category = "Dataflow", meta = (ClampMin = "0.0", ClampMax = "1.0"))`
- L49 _public member_ `bool bDiscardInteriorTriangles = true;` — `UPROPERTY(EditAnywhere, Category = "Dataflow")`
- L51 _public function_ `FRadialTetrahedronDataflowNodes(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowNode(InParam, InGuid)`
- L58 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

### `Plugins/Experimental/ChaosFlesh/Source/ChaosFleshNodes/Public/Dataflow/ChaosFleshSetFleshBonePositionTargetBindingNode.h` (Public)


#### enum `ESkeletalBindingMode`  
`enum class ESkeletalBindingMode : uint8`  
_L14-20_
- reflection: `UENUM(BlueprintType)`
- L16 _public enumerator_ `Dataflow_SkeletalBinding_Kinematic UMETA(DisplayName = "Kinematic")`
- L17 _public enumerator_ `Dataflow_SkeletalBinding_PositionTarget UMETA(DisplayName = "Position Target")`
- L19 _public enumerator_ `Chaos_Max UMETA(Hidden)`

#### struct `FSetFleshBonePositionTargetBindingDataflowNode`  
`struct FSetFleshBonePositionTargetBindingDataflowNode : public FDataflowNode`  
_L26-57_
- reflection: `USTRUCT(meta = (Deprecated = "5.6"))`
- inherits: `FDataflowNode`
- desc: Deprecated in 5.6 to support fixed distance search radius and improve binding method.
- L36 _public member_ `ESkeletalBindingMode SkeletalBindingMode = ESkeletalBindingMode::Dataflow_SkeletalBinding_PositionTarget;` — `UPROPERTY(EditAnywhere, Category = "Dataflow")`
- L39 _public member_ `float PositionTargetStiffness = 10000.f;` — `UPROPERTY(EditAnywhere, Category = "Dataflow", meta = (ClampMin = "0.0", EditCondition = "SkeletalBindingMode == ESkeletalBindingMode::Dataflow_SkeletalBinding_PositionTarget", EditConditionHides))`
- L42 _public member_ `TObjectPtr<USkeletalMesh> SkeletalMeshIn = nullptr;` — `UPROPERTY(EditAnywhere, Category = "Dataflow", meta = (DataflowInput, DisplayName = "SkeletalMesh"))`
- L45 _public member_ `float VertexRadiusRatio = .001f;` — `UPROPERTY(EditAnywhere, Category = "Dataflow", meta = (ClampMin = "0.0", ClampMax = "2.0", UIMin = "0.0", UIMax = "2.0"))`
- L48 _public function_ `FSetFleshBonePositionTargetBindingDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowNode(InParam, InGuid)`
- L56 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FSetFleshBonePositionTargetBindingDataflowNode_v2`  
`struct FSetFleshBonePositionTargetBindingDataflowNode_v2 : public FDataflowNode`  
_L63-102_
- reflection: `USTRUCT(meta = (DataflowFlesh))`
- inherits: `FDataflowNode`
- desc: Binds vertices from Collection to bone skeletal mesh surface via kinematic or weak constraints.
- L80 _private member_ `FManagedArrayCollection Collection;` — `UPROPERTY(meta = (DataflowInput, DataflowOutput, DisplayName = "Collection", DataflowPassthrough = "Collection"))`
- L83 _private member_ `ESkeletalBindingMode SkeletalBindingMode = ESkeletalBindingMode::Dataflow_SkeletalBinding_PositionTarget;` — `UPROPERTY(EditAnywhere, Category = "Dataflow")`
- L86 _private member_ `float PositionTargetStiffness = 10000.f;` — `UPROPERTY(EditAnywhere, Category = "Dataflow", meta = (ClampMin = "0.0", EditCondition = "SkeletalBindingMode == ESkeletalBindingMode::Dataflow_SkeletalBinding_PositionTarget", EditConditionHides))`
- L89 _private member_ `TObjectPtr<USkeletalMesh> SkeletalMeshIn = nullptr;` — `UPROPERTY(EditAnywhere, Category = "Dataflow", meta = (DataflowInput, DisplayName = "SkeletalMesh"))`
- L93 _private member_ `FDataflowVertexSelection VertexSelection;` — `UPROPERTY(meta = (DataflowInput, DisplayName = "(Optional) VertexSelection"))` — (optional) only create kinematic/weak constraints on vertices in the VertexSelection
- L99 _private member_ `float SearchRadius = 0.f;` — `UPROPERTY(EditAnywhere, Category = "Dataflow", meta = (ClampMin = "0.0"))` — Collection vertices are bound to their closest skeletal mesh vertices within the search radius
- L101 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### Free symbols / members of external scopes

- L104 _namespace_ `namespace UE`
- L104 _namespace_ `namespace Dataflow` (scope `UE`)
- L106 _prototype_ `void RegisterChaosFleshPositionTargetInitializationNodes();` (scope `UE::Dataflow`)

### `Plugins/Experimental/ChaosFlesh/Source/ChaosFleshNodes/Public/Dataflow/ChaosFleshSetFleshDefaultPropertiesNode.h` (Public)


#### struct `FSetFleshDefaultPropertiesNode`  
`struct FSetFleshDefaultPropertiesNode : public FDataflowNode`  
_L14-51_
- reflection: `USTRUCT(meta = (DataflowFlesh))`
- inherits: `FDataflowNode`
- L25 _public member_ `float VertexStiffness = 1e6;` — `UPROPERTY(EditAnywhere, Category = "Dataflow")`
- L28 _public member_ `float VertexDamping = 0.f;` — `UPROPERTY(EditAnywhere, Category = "Dataflow", meta = (ClampMin = "0.0", ClampMax = "1.0", UIMin = "0.0", UIMax = "1.0"))`
- L33 _public member_ `float VertexIncompressibility = 0.6f;` — `UPROPERTY(EditAnywhere, Category = "Dataflow", meta = (ClampMin = "0.00001", ClampMax = "1.0", UIMin = "0.00001", UIMax = "1.0"))` — Sets incompressibility on vertex basis. 0.6 is default behavior. 1 means absolutely incompressible. 0 means no incompressibility constraint on the material
- L38 _public member_ `float VertexInflation = 0.5f;` — `UPROPERTY(EditAnywhere, Category = "Dataflow", meta = (ClampMin = "0.00001", UIMin = "0.00001"))` — Sets inflation on vertex basis. 0.5 means no inflation/deflation. 1 means inflation to 2X volume on each dimension. 0 means the material is deflated to 0 volume.
- L41 _public member_ `FManagedArrayCollection Collection;` — `UPROPERTY(meta = (DataflowInput, DataflowOutput, DisplayName = "Collection", DataflowPassthrough = "Collection"))`
- L43 _public function_ `FSetFleshDefaultPropertiesNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowNode(InParam, InGuid)`
- L50 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

### `Plugins/Experimental/ChaosFlesh/Source/ChaosFleshNodes/Public/Dataflow/ChaosFleshSetVertexTetrahedraPositionTargetBindingNode.h` (Public)


#### struct `FSetVertexTetrahedraPositionTargetBindingDataflowNode`  
`struct FSetVertexTetrahedraPositionTargetBindingDataflowNode : public FDataflowNode`  
_L12-45_
- reflection: `USTRUCT(meta = (DataflowFlesh))`
- inherits: `FDataflowNode`
- L18 _public typedef_ `typedef FManagedArrayCollection DataType;`
- L22 _public member_ `FManagedArrayCollection Collection;` — `UPROPERTY(meta = (DataflowInput, DataflowOutput, DisplayName = "Collection", DataflowPassthrough = "Collection"))`
- L25 _public member_ `TArray<int32> TargetIndicesIn;` — `UPROPERTY(meta = (DataflowInput, DisplayName = "TargetIndicesIn"))`
- L28 _public member_ `TArray<FString> GeometryGroupGuidsIn;` — `UPROPERTY(meta = (DataflowInput, DisplayName = "GeometryGroupGuidsIn"))`
- L31 _public member_ `float PositionTargetStiffness = 10000.f;` — `UPROPERTY(EditAnywhere, Category = "Dataflow")`
- L35 _public function_ `FSetVertexTetrahedraPositionTargetBindingDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowNode(InParam, InGuid)`
- L44 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

### `Plugins/Experimental/ChaosFlesh/Source/ChaosFleshNodes/Public/Dataflow/ChaosFleshSetVertexTrianglePositionTargetBindingNode.h` (Public)


#### struct `FSetVertexTrianglePositionTargetBindingDataflowNode`  
`struct FSetVertexTrianglePositionTargetBindingDataflowNode : public FDataflowNode`  
_L18-59_
- reflection: `USTRUCT(meta = (DataflowFlesh))`
- inherits: `FDataflowNode`
- desc: Create point-triangle weak constraints (springs) between surface meshes of different geometries based on search radius.
- L28 _public member_ `float PositionTargetStiffness = 1.f;` — `UPROPERTY(EditAnywhere, Category = "Dataflow")`
- L32 _public member_ `FDataflowVertexSelection VertexSelection;` — `UPROPERTY(meta = (DataflowInput, DisplayName = "(Optional) VertexSelection"))` — (optional) only create weak constraints from surface vertices in VertexSelection to triangles in other geometries
- L36 _public member_ `float SearchRadius = 0.f;` — `UPROPERTY(EditAnywhere, Category = "Dataflow", meta = (ClampMin = "0.0"))` — Search radius for point-triangle pairs between geometry surfaces.
- L40 _public member_ `bool bAllowSliding = false;` — `UPROPERTY(EditAnywhere, Category = "Dataflow", meta = (DisplayName = "Allow Sliding"))` — if point-triangle weak constraints created are anisotropic and allow sliding along the triangle plane
- L43 _public member_ `bool bZeroRestLengthEditable = false;` — `UPROPERTY(EditAnywhere, Category = "Dataflow", meta = (InlineEditConditionToggle))`
- L48 _public member_ `bool bUseZeroRestLengthSprings = false;` — `UPROPERTY(EditAnywhere, Category = "Dataflow", meta = (DisplayName = "Use zero rest length springs", EditCondition = "bZeroRestLengthEditable"))` — if point-triangle weak constraints created are zero rest-length. if true, this will cause point triangle pair to stick together, as opposed to separated by their rest state distance.
- L50 _public function_ `FSetVertexTrianglePositionTargetBindingDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowNode(InParam, InGuid)`
- L58 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FDeleteVertexTrianglePositionTargetBindingDataflowNode`  
`struct FDeleteVertexTrianglePositionTargetBindingDataflowNode : public FDataflowNode`  
_L65-93_
- reflection: `USTRUCT(meta = (DataflowFlesh))`
- inherits: `FDataflowNode`
- desc: Delete vertex-triangle weak constraints (zero rest length springs) between VertexSelection1 and VertexSelection2.
- L82 _private member_ `FManagedArrayCollection Collection;` — `UPROPERTY(meta = (DataflowInput, DataflowIntrinsic, DataflowOutput, DisplayName = "Collection", DataflowPassthrough = "Collection"))`
- L86 _private member_ `FDataflowVertexSelection VertexSelection1;` — `UPROPERTY(meta = (DataflowInput, DataflowIntrinsic, DisplayName = "VertexSelection1"))` — This node deletes springs between VertexSelection1 and VertexSelection2.
- L90 _private member_ `FDataflowVertexSelection VertexSelection2;` — `UPROPERTY(meta = (DataflowInput, DataflowIntrinsic, DisplayName = "VertexSelection2"))` — This node deletes springs between VertexSelection1 and VertexSelection2.
- L92 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FSetCollidableVerticesDataflowNode`  
`struct FSetCollidableVerticesDataflowNode : public FDataflowNode`  
_L100-123_
- reflection: `USTRUCT(meta = (DataflowFlesh))`
- inherits: `FDataflowNode`
- desc: Set custom vertices so that only these vertices can collide with other surfaces. Unselected vertices will not collide with unselected vertices.
- L106 _public function_ `FSetCollidableVerticesDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowNode(InParam, InGuid)`
- L116 _private member_ `FManagedArrayCollection Collection;` — `UPROPERTY(meta = (DataflowInput, DataflowIntrinsic, DataflowOutput, DisplayName = "Collection", DataflowPassthrough = "Collection"))`
- L120 _private member_ `FDataflowVertexSelection VertexSelection;` — `UPROPERTY(meta = (DataflowInput, DataflowIntrinsic, DisplayName = "Collision Vertex Selection"))` — Vertices selected to be able to collide with others. Unselected vertices will not collide with unselected vertices
- L122 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FCreateAirTetrahedralConstraintDataflowNode`  
`struct FCreateAirTetrahedralConstraintDataflowNode : public FDataflowNode`  
_L131-168_
- reflection: `USTRUCT(meta = (DataflowFlesh))`
- inherits: `FDataflowNode`
- desc: Create air tetrahedral constraint between point-triangle pair from surface meshes of different geometries based on search radius. The added tetrahedra help to maintain distance between geometries. This node renders the boundary of the added tetrahedral mesh.
- L137 _public function_ `FCreateAirTetrahedralConstraintDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowNode(InParam, InGuid)`
- L150 _private member_ `FManagedArrayCollection Collection;` — `UPROPERTY(meta = (DataflowInput, DataflowOutput, DisplayName = "Collection", DataflowPassthrough = "Collection"))`
- L157 _private member_ `FDataflowVertexSelection VertexSelection;` — `UPROPERTY(meta = (DataflowInput, DisplayName = "(Optional) VertexSelection"))` — (optional) only create tetrahedral constraints from surface vertices in VertexSelection to triangles in other geometries. For example, if the VertexSelection contains only one geometry, only this geometry will bind to other geometries. No constraints will be created between two geometries that are not in the VertexSelection.
- L161 _private member_ `float SearchRadius = 0.f;` — `UPROPERTY(EditAnywhere, Category = "Dataflow", meta = (ClampMin = "0.0"))` — tetrahedral constraint search radius
- L165 _private member_ `TObjectPtr<UDynamicMesh> DynamicMesh;` — `UPROPERTY(meta = (DataflowOutput))` — Render dynamic mesh of the boundary mesh of added tetrahedra
- L167 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FCreateAirVolumeConstraintDataflowNode`  
`struct FCreateAirVolumeConstraintDataflowNode : public FDataflowNode`  
_L175-215_
- reflection: `USTRUCT(meta = (Experimental, DataflowFlesh))`
- inherits: `FDataflowNode`
- desc: Creates volume constraint (defined by point-triangle tetrahedron volume) between surface meshes of different geometries. This constraint allow sliding of the point along the triangle plane.
- L181 _public function_ `FCreateAirVolumeConstraintDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowNode(InParam, InGuid)`
- L194 _private member_ `FManagedArrayCollection Collection;` — `UPROPERTY(meta = (DataflowInput, DataflowOutput, DisplayName = "Collection", DataflowPassthrough = "Collection"))`
- L200 _private member_ `FDataflowVertexSelection VertexSelection;` — `UPROPERTY(meta = (DataflowInput, DisplayName = "(Optional) VertexSelection"))` — (optional) only create volume constraints from surface vertices in VertexSelection to triangles in other geometries. For example, if the VertexSelection contains only one geometry, only this geometry will bind to other geometries. No constraints will be created between two geometries that are not in the VertexSelection.
- L204 _private member_ `float SearchRadius = 0.f;` — `UPROPERTY(EditAnywhere, Category = "Dataflow", meta = (ClampMin = "0.0"))` — search radius for point-triangle pairs
- L208 _private member_ `float Stiffness = 1.f;` — `UPROPERTY(EditAnywhere, Category = "Dataflow", meta = (ClampMin = "0.0"))` — Stiffness of the volume constraint. This should be around the same magnitude as Young's modulus.
- L212 _private member_ `TObjectPtr<UDynamicMesh> DynamicMesh;` — `UPROPERTY(meta = (DataflowOutput))` — Render dynamic mesh of the boundary mesh of added volume
- L214 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

### `Plugins/Experimental/ChaosFlesh/Source/ChaosFleshNodes/Public/Dataflow/ChaosFleshSetVertexVertexPositionTargetBindingNode.h` (Public)


#### struct `FSetVertexVertexPositionTargetBindingDataflowNode`  
`struct FSetVertexVertexPositionTargetBindingDataflowNode : public FDataflowNode`  
_L13-44_
- reflection: `USTRUCT(meta = (DataflowFlesh))`
- inherits: `FDataflowNode`
- L19 _public typedef_ `typedef FManagedArrayCollection DataType;`
- L22 _public member_ `float RadiusRatio = .1f;` — `UPROPERTY(EditAnywhere, Category = "Dataflow", meta = (ClampMin = "0.0", ClampMax = "1.0", UIMin = "0.0", UIMax = "1.0"))`
- L25 _public member_ `FManagedArrayCollection Collection;` — `UPROPERTY(meta = (DataflowInput, DataflowOutput, DisplayName = "Collection", DataflowPassthrough = "Collection"))`
- L28 _public member_ `TArray<int32> TargetIndicesIn;` — `UPROPERTY(meta = (DataflowInput, DisplayName = "TargetIndicesIn"))`
- L31 _public member_ `float PositionTargetStiffness = 10000.f;` — `UPROPERTY(EditAnywhere, Category = "Dataflow")`
- L35 _public function_ `FSetVertexVertexPositionTargetBindingDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowNode(InParam, InGuid)`
- L43 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

### `Plugins/Experimental/ChaosFlesh/Source/ChaosFleshNodes/Public/Dataflow/ChaosFleshSkeletalMeshConstraintNode.h` (Public)


#### struct `FKinematicSkeletalMeshInitializationDataflowNode`  
`struct FKinematicSkeletalMeshInitializationDataflowNode : public FDataflowNode`  
_L14-41_
- reflection: `USTRUCT(meta = (DataflowFlesh))`
- inherits: `FDataflowNode`
- desc: @todo(deprecate), rename to FSkeletalMeshConstraintDataflowNode
- L20 _public typedef_ `typedef FManagedArrayCollection DataType;`
- L23 _public member_ `FManagedArrayCollection Collection;` — `UPROPERTY(meta = (DataflowInput, DataflowOutput, DisplayName = "Collection"))`
- L26 _public member_ `TObjectPtr<USkeletalMesh> SkeletalMeshIn;` — `UPROPERTY(meta = (DataflowInput, DisplayName = "SkeletalMesh"))`
- L29 _public member_ `TArray<int32> IndicesOut;` — `UPROPERTY(meta = (DataflowOutput, DisplayName = "SelectionSet"))`
- L31 _public function_ `FKinematicSkeletalMeshInitializationDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowNode(InParam, InGuid)`
- L40 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

### `Plugins/Experimental/ChaosFlesh/Source/ChaosFleshNodes/Public/Dataflow/ChaosFleshSkinSimulationPropertiesNode.h` (Public)


#### struct `FSkinSimulationPropertiesDataflowNodes`  
`struct FSkinSimulationPropertiesDataflowNodes : public FDataflowNode`  
_L17-41_
- reflection: `USTRUCT(meta = (DataflowFlesh))`
- inherits: `FDataflowNode`
- desc: Set triangle mesh to simulate using skin constraints
- L23 _public typedef_ `typedef FManagedArrayCollection DataType;`
- L26 _public member_ `bool bSkinConstraints = false;` — `UPROPERTY(EditAnywhere, Category = "Dataflow", meta = (DisplayName = "UseSkinConstraints"))`
- L29 _public member_ `FManagedArrayCollection Collection;` — `UPROPERTY(meta = (DataflowInput, DataflowOutput, DisplayName = "Collection"))`
- L32 _public function_ `FSkinSimulationPropertiesDataflowNodes(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowNode(InParam, InGuid)`
- L39 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

### `Plugins/Experimental/ChaosFlesh/Source/ChaosFleshNodes/Public/Dataflow/ChaosFleshTriangleMeshSimulationPropertiesNode.h` (Public)


#### struct `FTriangleMeshSimulationPropertiesDataflowNodes`  
`struct FTriangleMeshSimulationPropertiesDataflowNodes : public FDataflowNode`  
_L18-52_
- reflection: `USTRUCT(meta = (DataflowFlesh))`
- inherits: `FDataflowNode`
- desc: Convert tetmesh to simulate using surface traingle mesh only
- L24 _public typedef_ `typedef FManagedArrayCollection DataType;`
- L27 _public member_ `TArray<FString> MeshNames;` — `UPROPERTY(EditAnywhere, Category = "Dataflow", meta = (DisplayName = "MeshNames"))`
- L30 _public member_ `float TriangleMeshDensity = 1.f;` — `UPROPERTY(EditAnywhere, Category = "Dataflow")`
- L33 _public member_ `float VertexTriangleMeshStiffness = 1e6;` — `UPROPERTY(EditAnywhere, Category = "Dataflow")`
- L36 _public member_ `float VertexTriangleMeshDamping = 0.f;` — `UPROPERTY(EditAnywhere, Category = "Dataflow")`
- L39 _public member_ `FManagedArrayCollection Collection;` — `UPROPERTY(meta = (DataflowInput, DataflowOutput, DisplayName = "Collection"))`
- L42 _public function_ `FTriangleMeshSimulationPropertiesDataflowNodes(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowNode(InParam, InGuid)`
- L49 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

### `Plugins/Experimental/ChaosFlesh/Source/ChaosFleshNodes/Public/Dataflow/ChaosFleshVertexConstraintNode.h` (Public)


#### struct `FSetVerticesKinematicDataflowNode`  
`struct FSetVerticesKinematicDataflowNode : public FDataflowNode`  
_L14-37_
- reflection: `USTRUCT(meta = (Deprecated = "5.6"))`
- inherits: `FDataflowNode`
- desc: Use SetKinematicVertexSelection to set/reset kinematic vertices
- L20 _public typedef_ `typedef FManagedArrayCollection DataType;`
- L23 _public member_ `FManagedArrayCollection Collection;` — `UPROPERTY(meta = (DataflowInput, DataflowOutput, DisplayName = "Collection", DataflowPassthrough = "Collection"))`
- L26 _public member_ `TArray<int32> VertexIndicesIn;` — `UPROPERTY(meta = (DataflowInput, DisplayName = "SelectionSet"))`
- L28 _public function_ `FSetVerticesKinematicDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowNode(InParam, InGuid)`
- L36 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

### `Plugins/Experimental/ChaosFlesh/Source/ChaosFleshNodes/Public/Dataflow/ChaosFleshVisualizeFiberFieldNode.h` (Public)


#### struct `FVisualizeFiberFieldNode`  
`struct FVisualizeFiberFieldNode : public FDataflowNode`  
_L16-39_
- reflection: `USTRUCT(meta = (DataflowFlesh))`
- inherits: `FDataflowNode`
- desc: Visualizes a muscle fiber direction per tetrahedron from a GeometryCollection containing tetrahedra.
- L26 _public member_ `float VectorScale = 1.0;` — `UPROPERTY(EditAnywhere, Category = "Dataflow")`
- L29 _public member_ `FFieldCollection VectorField;` — `UPROPERTY(meta = (DataflowOutput, DisplayName = "VectorField"))`
- L31 _public function_ `FVisualizeFiberFieldNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowNode(InParam, InGuid)`
- L38 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FVisualizePositionTargetsNode`  
`struct FVisualizePositionTargetsNode : public FDataflowNode`  
_L45-65_
- reflection: `USTRUCT(meta = (DataflowFlesh))`
- inherits: `FDataflowNode`
- desc: Visualizes position target vectors from GeometryCollection.
- L55 _public member_ `FFieldCollection VectorField;` — `UPROPERTY(meta = (DataflowOutput, DisplayName = "VectorField"))`
- L57 _public function_ `FVisualizePositionTargetsNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowNode(InParam, InGuid)`
- L64 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FVisualizeKinematicFacesNode`  
`struct FVisualizeKinematicFacesNode : public FDataflowNode`  
_L71-88_
- reflection: `USTRUCT(meta = (DataflowFlesh))`
- inherits: `FDataflowNode`
- desc: Visualizes kinematic faces from GeometryCollection.
- L80 _public function_ `FVisualizeKinematicFacesNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowNode(InParam, InGuid)`
- L87 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

### `Plugins/Experimental/ChaosFlesh/Source/ChaosFleshNodes/Public/Dataflow/GeometryCollectionAppendCollectionTransformNode.h` (Public)


#### struct `FAppendToCollectionTransformAttributeDataflowNode`  
`struct FAppendToCollectionTransformAttributeDataflowNode : public FDataflowNode`  
_L12-42_
- reflection: `USTRUCT(meta = (DataflowFlesh))`
- inherits: `FDataflowNode`
- desc: @todo(deprecate), move to GeometryCollection as AppendCollectionTransformDataflowNode
- L18 _public typedef_ `typedef FManagedArrayCollection DataType;`
- L22 _public member_ `FManagedArrayCollection Collection;` — `UPROPERTY(meta = (DataflowInput, DataflowOutput, DisplayName = "Collection", DataflowPassthrough = "Collection"))`
- L25 _public member_ `FTransform TransformIn = FTransform::Identity;` — `UPROPERTY(meta = (DataflowInput, DisplayName = "Transform"))`
- L28 _public member_ `FString AttributeName = FString("Com` — `UPROPERTY(EditAnywhere, Category = "Dataflow")`
- L31 _public member_ `FString GroupName = FString("Com` — `UPROPERTY(EditAnywhere, Category = "Dataflow")`
- L33 _public function_ `FAppendToCollectionTransformAttributeDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowNode(InParam, InGuid)`
- L41 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### Free symbols / members of external scopes

- L44 _namespace_ `namespace UE`
- L44 _namespace_ `namespace Dataflow` (scope `UE`)
- L46 _prototype_ `void RegisterChaosFleshKinematicInitializationNodes();` (scope `UE::Dataflow`)
