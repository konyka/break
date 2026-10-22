# Plugins / ChaosRigidAssetNodes

- module root: `Plugins/Experimental/ChaosRigidAsset/Source/ChaosRigidAssetNodes`
- headers: 12; symbols: 478
- symbol kinds: class=11, delegate=1, enum=9, enumerator=15, function=78, member=138, namespace=18, prototype=154, struct=49, typedef=5
- PrivateDependencyModuleNames: CoreUObject
- PublicDependencyModuleNames: ChaosRigidAssetEngine, Core, DataflowCore, DataflowEngine, DataflowEnginePlugin, DynamicMesh, Engine, GeometryCore

### `Plugins/Experimental/ChaosRigidAsset/Source/ChaosRigidAssetNodes/Internal/PhysicsAssetDataflowState.h` (Internal)


#### struct `FPhysicsAssetDataflowState`  
`struct FPhysicsAssetDataflowState`  
_L25-58_
- reflection: `USTRUCT()`
- desc: State container for physics asset data during dataflow graph evaluation. Represents the complete state required to build a physics asset. Datflow nodes populate this container until it reaches a terminal which packages it into a final UPhysicsAsset. This allows us to keep the const invariant for dataflow evaluation by adding copy-on-write support to the state. During node evaluation this object should be passed by-value as it is a collection of pts to the actual data. If the copy-on-write arrays are modified they will automatically duplicate if required
- L31 _public prototype_ `FPhysicsAssetDataflowState();`
- L32 _public prototype_ `explicit FPhysicsAssetDataflowState(TObjectPtr<USkeleton> TargetSkeleton, TObjectPtr<USkeletalMesh> TargetMesh);`
- L34 _public prototype_ `USkeleton* GetSkeleton() const;`
- L35 _public prototype_ `USkeletalMesh* GetMesh() const;`
- L36 _public prototype_ `USkeletalBodySetup* GetBody(FName BoneName) const;`
- L37 _public prototype_ `void SetBody(FName BoneName, USkeletalBodySetup* InSetup);`
- L38 _public prototype_ `USkeletalBodySetup* FindOrCreateBody(FName BoneName, USkeletalBodySetup* TemplateBody = nullptr);`
- L39 _public prototype_ `USkeletalBodySetup* FindOrCreateBodyChecked(FName BoneName, USkeletalBodySetup* TemplateBody = nullptr);`
- L40 _public prototype_ `const TCopyOnWriteArray<TObjectPtr<USkeletalBodySetup>>& GetBodies() const;`
- L42 _public prototype_ `void AddStructReferencedObjects(FReferenceCollector& Collector);`
- L45 _public member_ `TCopyOnWriteArray<TObjectPtr<UPhysicsConstraintTemplate>> Constraints;` — Bodies and constraints in the simulation setup
- L47 _public prototype_ `void DebugLog() const;`
- L48 _public prototype_ `bool HasData() const;`
- L53 _private member_ `TObjectPtr<USkeleton> TargetSkeleton = nullptr;` — Base asset data
- L54 _private member_ `TObjectPtr<USkeletalMesh> TargetMesh = nullptr;`
- L56 _private member_ `TCopyOnWriteArray<int32> BoneIndexToBody;`
- L57 _private member_ `TCopyOnWriteArray<TObjectPtr<USkeletalBodySetup>> Bodies;`

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FPhysicsAssetDataflowState> : public TStructOpsTypeTraitsBase2<FPhysicsAssetDataflowState>`  
_L64-70_
- inherits: `TStructOpsTypeTraitsBase2<FPhysicsAssetDataflowState>`
- desc: The state struct has UObject references within the copy-on-write arrays, enable handling for that here

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L67-69_

#### Free symbols / members of external scopes

- L68 _enumerator_ `WithAddStructReferencedObjects = true` (scope `TStructOpsTypeTraits::__anon7e5bae8d0103`)

### `Plugins/Experimental/ChaosRigidAsset/Source/ChaosRigidAssetNodes/Private/AnimationTerminalNodes.h` (Private)


#### struct `FDataflowAnimSequenceAssetTerminalNode`  
`struct FDataflowAnimSequenceAssetTerminalNode : public FDataflowTerminalNode`  
_L18-37_
- reflection: `USTRUCT(meta = (DataflowTerminal))`
- inherits: `FDataflowTerminalNode`
- desc: Terminal node that writes to a animation sequence asset
- L30 _private member_ `TObjectPtr<UAnimSequence> Animation;` — `UPROPERTY(meta = (DataflowInput))`
- L33 _private member_ `TObjectPtr<UAnimSequence> AnimationAsset;` — `UPROPERTY(EditAnywhere, Category = Asset, meta = (DataflowInput))`
- L35 _private prototype_ `void SetAssetValue(TObjectPtr<UObject> Asset, UE::Dataflow::FContext& Context) const override;`
- L36 _private prototype_ `void Evaluate(UE::Dataflow::FContext& Context) const override;`

#### struct `FDataflowAnimBankAssetTerminalNode`  
`struct FDataflowAnimBankAssetTerminalNode : public FDataflowTerminalNode`  
_L45-97_
- reflection: `USTRUCT(meta = (DataflowTerminal))`
- inherits: `FDataflowTerminalNode`
- desc: Terminal node that writes to a animation bank asset an AnimBank is made of multiple anim sequences and used to animate GPU
- L51 _public prototype_ `FDataflowAnimBankAssetTerminalNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L55 _private member_ `TObjectPtr<UAnimBank> AnimationBankAsset = nullptr;` — `UPROPERTY(EditAnywhere, Category = Asset, meta = (DataflowInput))`
- L58 _private member_ `TArray<TObjectPtr<UAnimSequence>> AnimSequences;` — `UPROPERTY()`
- L61 _private member_ `bool bLooping = true;` — `UPROPERTY(EditAnywhere, Category = Animation)`
- L64 _private member_ `bool bAutoStart = true;` — `UPROPERTY(EditAnywhere, Category = Animation)`
- L67 _private member_ `float Position = 0.0f;` — `UPROPERTY(EditAnywhere, Category = Animation)`
- L70 _private member_ `float PlayRate = 1.0f;` — `UPROPERTY(EditAnywhere, Category = Animation)`
- L78 _private member_ `float BoundsScale = 1.0f;` — `UPROPERTY(EditAnywhere, Category = Animation, meta = (ClampMin = "1", UIMin = "1", ClampMax = "10.0", UIMax = "10.0"))` — Scales the bounds of the instances playing this sequence. This is useful when the animation moves the vertices of the mesh outside of its bounds. Warning: Increasing the bounds will reduce performance!
- L80 _private prototype_ `void SetAssetValue(TObjectPtr<UObject> Asset, UE::Dataflow::FContext& Context) const override;`
- L81 _private prototype_ `void Evaluate(UE::Dataflow::FContext& Context) const override;`
- L84 _private prototype_ `virtual TArray<UE::Dataflow::FPin> AddPins() override;` — Begin FDataflowNode interface
- L85 _private prototype_ `virtual bool CanAddPin() const override;`
- L86 _private prototype_ `virtual bool CanRemovePin() const override;`
- L87 _private prototype_ `virtual TArray<UE::Dataflow::FPin> GetPinsToRemove() const override;`
- L88 _private prototype_ `virtual void OnPinRemoved(const UE::Dataflow::FPin& Pin) override;`
- L89 _private prototype_ `virtual void PostSerialize(const FArchive& Ar) override;`
- L92 _private prototype_ `UE::Dataflow::TConnectionReference<TObjectPtr<UAnimSequence>> GetConnectionReference(int32 Index) const;`
- L94 _private member_ `inline static constexpr int32 NumRequiredDataflowInputs = 1;`
- L95 _private member_ `inline static constexpr int32 NumInitialInputs = 2;`

#### Free symbols / members of external scopes

- L101 _namespace_ `namespace UE`
- L101 _namespace_ `namespace Dataflow` (scope `UE`)
- L103 _prototype_ `void RegisterAnimationTerminalNodes();` (scope `UE::Dataflow`)

### `Plugins/Experimental/ChaosRigidAsset/Source/ChaosRigidAssetNodes/Private/Generators/BoneGeometryGenerators.h` (Private)


#### enum `EMergeOperation`  
`enum class EMergeOperation`  
_L27-31_
- reflection: `UENUM()`
- desc: Merge operation to perform
- L29 _public enumerator_ `MergeAll`
- L30 _public enumerator_ `MergeSmall`

#### enum `ESmallBoneOperation`  
`enum class ESmallBoneOperation`  
_L42-46_
- reflection: `UENUM()`
- desc: Operation to use for small bones Skip will ignore a bone, and all of its geometry when attempting to generate collision shapes Merge will use the corresponding merge thresholds in the generation settings to decide whether to roll bones up as a single geometry and use all of their render data as a source for the generation process
- L44 _public enumerator_ `Skip`
- L45 _public enumerator_ `Merge`

#### enum `EVertexSelectMode`  
`enum class EVertexSelectMode`  
_L56-60_
- reflection: `UENUM()`
- desc: Operation for vertex extraction Any will extract all verts that have an influence for the selected bone DominantOnly will only extract verts that have the selcted bone as the dominant weight
- L58 _public enumerator_ `Any`
- L59 _public enumerator_ `DominantOnly`

#### enum `EVertexMergeMode`  
`enum class EVertexMergeMode`  
_L68-72_
- reflection: `UENUM()`
- desc: Whether to include merged bones in returned vertext data
- L70 _public enumerator_ `RootOnly`
- L71 _public enumerator_ `Merged`

#### enum `EBodyAlignment`  
`enum class EBodyAlignment`  
_L82-86_
- reflection: `UENUM()`
- desc: How to align a body during generation Bone will align along the bone direction and wrap the shape around the verts Verts will align along the major axis of the selected verts
- L84 _public enumerator_ `Bone`
- L85 _public enumerator_ `Verts`

#### struct `FBaseGenerationSettings`  
`struct FBaseGenerationSettings`  
_L94-124_
- reflection: `USTRUCT()`
- desc: Generic configuration for all generator types
- L99 _public member_ `EMergeOperation Operation = EMergeOperation::MergeSmall;` — `UPROPERTY(EditAnywhere, Category = "Generation")`
- L103 _public member_ `float MinimumBoneSize = 20.0f;` — `UPROPERTY(EditAnywhere, Category = "Generation", meta=(EditCondition="Operation==EMergeOperation::MergeSmall", EditConditionHides, Units=cm))` — Bones under this limit will be classified as a "Small" bone and apply the requested operation
- L107 _public member_ `ESmallBoneOperation SmallBoneOp = ESmallBoneOperation::Skip;` — `UPROPERTY(EditAnywhere, Category = "Generation", meta = (EditCondition = "Operation==EMergeOperation::MergeSmall", EditConditionHides))` — Which operation to apply to small bones
- L111 _public member_ `float SmallBoneMergeThresholdOverride = 0.0f;` — `UPROPERTY(EditAnywhere, Category = "Generation", meta = (EditCondition = "Operation==EMergeOperation::MergeSmall", EditConditionHides, Units=cm))` — For the "Merge" small-bone operation - only merge over this threshold and skip otherwise
- L115 _public member_ `EVertexSelectMode VertexMode = EVertexSelectMode::DominantOnly;` — `UPROPERTY(EditAnywhere, Category = "Generation")` — Vertex extraction operation, see EVertexSelectMode
- L119 _public member_ `int32 SourceLod = 0;` — `UPROPERTY(EditAnywhere, Category = "Generation")` — The render LOD to use for geometry generation, render data will be extracted from this LOD
- L123 _public member_ `float Thickness = 0.0f;` — `UPROPERTY(EditAnywhere, Category = "Generation", meta=(Units=cm))` — Extra thickness added to generated geometry after the genration process produces a geometry

#### struct `FBoneVertData`  
`struct FBoneVertData`  
_L129-136_
- desc: Data extracted from a bone for body generation
- L131 _public member_ `TArray<FVector3f> Positions;`
- L132 _public member_ `TArray<FVector3f> Normals;`
- L133 _public member_ `TArray<float> Weights;`
- L134 _public member_ `TArray<FIntVector3> Triangles;`
- L135 _public member_ `FBoxSphereBounds3f Bounds;`

#### struct `FRigidAssetBoneGeometry`  
`struct FRigidAssetBoneGeometry`  
_L138-142_
- L140 _public member_ `FRigidAssetBoneInfo Bone;`
- L141 _public member_ `UE::Chaos::RigidAsset::FSimpleGeometry Geometry;`

#### class `UBoneGeometryGenerator`  
`class UBoneGeometryGenerator : public UObject`  
_L155-177_
- reflection: `UCLASS(EditInlineNew, Abstract)`
- inherits: `UObject`
- desc: Base geometry generator for each render->physics generation type.
- L161 _public function_ `virtual TArray<FRigidAssetBoneGeometry> Build(FRigidAssetBoneSelection Bones)`
- L167 _public prototype_ `virtual bool CanDebugDraw() const;`
- L168 _public prototype_ `virtual bool CanDebugDrawViewMode(const FName& ViewModeName) const;`
- L169 _public prototype_ `virtual void DebugDraw(UE::Dataflow::FContext& Context, IDataflowDebugDrawInterface& DataflowRenderingInterface, const FDataflowNode::FDebugDrawParameters& DebugDrawParameters, FRigidAssetBoneSelection Bones) const;`
- L176 _protected member_ `FBaseGenerationSettings BaseSettings;` — `UPROPERTY(EditAnywhere, Category = "Generation", meta = (EditInline))` — Base settings for all generation types

#### class `UBoneGeometryGenerator_Box`  
`class UBoneGeometryGenerator_Box : public UBoneGeometryGenerator`  
_L186-195_
- reflection: `UCLASS()`
- inherits: `UBoneGeometryGenerator`
- desc: Basic box generator Takes the extracted verts and wraps a tight box around them
- L192 _public prototype_ `TArray<FRigidAssetBoneGeometry> Build(FRigidAssetBoneSelection Bones) final override;`

#### class `UBoneGeometryGenerator_Sphere`  
`class UBoneGeometryGenerator_Sphere : public UBoneGeometryGenerator`  
_L204-230_
- reflection: `UCLASS()`
- inherits: `UBoneGeometryGenerator`
- desc: Basic sphere generator Takes the extracted verts and wraps a sphere around them
- L210 _public prototype_ `TArray<FRigidAssetBoneGeometry> Build(FRigidAssetBoneSelection Bones) final override;`
- L213 _public prototype_ `virtual bool CanDebugDraw() const override;`
- L214 _public prototype_ `virtual bool CanDebugDrawViewMode(const FName& ViewModeName) const override;`
- L215 _public prototype_ `virtual void DebugDraw(UE::Dataflow::FContext& Context, IDataflowDebugDrawInterface& DataflowRenderingInterface, const FDataflowNode::FDebugDrawParameters& DebugDrawParameters, FRigidAssetBoneSelection Bones) const override;`
- L221 _private member_ `bool bUseGeometry = true;` — `UPROPERTY(EditAnywhere, Category = Settings)`
- L225 _private member_ `bool bDrawVerts = true;` — `UPROPERTY(EditAnywhere, Category=Debug)`
- L228 _private member_ `FName DrawVertsForBoneName = NAME_None;` — `UPROPERTY(EditAnywhere, Category=Debug)`

#### class `UBoneGeometryGenerator_Capsule`  
`class UBoneGeometryGenerator_Capsule : public UBoneGeometryGenerator`  
_L239-265_
- reflection: `UCLASS()`
- inherits: `UBoneGeometryGenerator`
- desc: Capsule generator Takes the extracted verts and wraps capsule around them
- L245 _public prototype_ `TArray<FRigidAssetBoneGeometry> Build(FRigidAssetBoneSelection Bones) final override;`
- L248 _public prototype_ `virtual bool CanDebugDraw() const override;`
- L249 _public prototype_ `virtual bool CanDebugDrawViewMode(const FName& ViewModeName) const override;`
- L250 _public prototype_ `virtual void DebugDraw(UE::Dataflow::FContext& Context, IDataflowDebugDrawInterface& DataflowRenderingInterface, const FDataflowNode::FDebugDrawParameters& DebugDrawParameters, FRigidAssetBoneSelection Bones) const override;`
- L256 _private member_ `EBodyAlignment Alignment = EBodyAlignment::Bone;` — `UPROPERTY(EditAnywhere, Category=Geometry)`
- L260 _private member_ `bool bDrawVerts = true;` — `UPROPERTY(EditAnywhere, Category=Debug)`
- L263 _private member_ `FName DrawVertsForBoneName = NAME_None;` — `UPROPERTY(EditAnywhere, Category=Debug)`

#### class `UBoneGeometryGenerator_Convex`  
`class UBoneGeometryGenerator_Convex : public UBoneGeometryGenerator`  
_L274-283_
- reflection: `UCLASS()`
- inherits: `UBoneGeometryGenerator`
- desc: Convex generator Takes the extracted verts then uses them to generate a single convex hull
- L280 _public prototype_ `TArray<FRigidAssetBoneGeometry> Build(FRigidAssetBoneSelection Bones) final override;`

#### enum `EDecompositionMethod`  
`enum class EDecompositionMethod`  
_L288-292_
- reflection: `UENUM()`
- L290 _public enumerator_ `Simple`
- L291 _public enumerator_ `NegativeSpace`

#### class `UBoneGeometryGenerator_ConvexDecomposition`  
`class UBoneGeometryGenerator_ConvexDecomposition : public UBoneGeometryGenerator`  
_L299-351_
- reflection: `UCLASS()`
- inherits: `UBoneGeometryGenerator`
- desc: Convex decomposition generator Takes the extracted verts then uses them to generate a convex hull decomposition of multiple hulls
- L306 _public member_ `EDecompositionMethod Method = EDecompositionMethod::Simple;` — `UPROPERTY(EditAnywhere, Category = Geometry)`
- L310 _public member_ `int32 NumHulls = 4;` — `UPROPERTY(EditAnywhere, Category = Geometry, meta = (EditCondition="Method == EDecompositionMethod::Simple", EditConditionHides))` — Number of hulls to create in the Simple decomposition mode
- L314 _public member_ `bool bOnlyConnectedToHull = true;` — `UPROPERTY(EditAnywhere, Category = Geometry, meta = (EditCondition="Method == EDecompositionMethod::NegativeSpace", EditConditionHides))` — When protecting negative space, only look for space that is connected out to the convex hull. This removes inaccessable internal negative space from consideration.
- L318 _public member_ `float NegativeSpaceTolerance = 2.0f;` — `UPROPERTY(EditAnywhere, Category = Geometry, meta = (EditCondition="Method == EDecompositionMethod::NegativeSpace", EditConditionHides))` — Amount of space to leave between convex hulls and protected negative space
- L322 _public member_ `float NegativeSpaceMinRadius = 10.0f;` — `UPROPERTY(EditAnywhere, Category = Geometry, meta = (EditCondition="Method == EDecompositionMethod::NegativeSpace", EditConditionHides))` — Spheres smaller than this are not included in the negative space
- L330 _public member_ `int32 NegativeSpaceMaxSplits = 0;` — `UPROPERTY(EditAnywhere, Category = Geometry, meta = (EditCondition="Method == EDecompositionMethod::NegativeSpace", EditConditionHides))` — Number of splits to target in the final decomposition when using the negative space method. If 0 the number of splits will be driven by the decomposition and may produce a more accurate result but take longer. If >0 the number of splits will be truncated at the specified value
- L334 _public member_ `double MinThicknessTolerance = 0;` — `UPROPERTY(EditAnywhere, Category = Geometry, meta = (EditCondition="Method == EDecompositionMethod::NegativeSpace", EditConditionHides))` — Optional tolerance (in cm) for merging after decomposition. Hulls under this size will always be merged
- L338 _public member_ `bool bSimplifyHulls = false;` — `UPROPERTY(EditAnywhere, Category = Geometry)` — Whether to simplify the resulting hull meshes
- L342 _public member_ `int32 SimplifyTargetMaxFaces = 128;` — `UPROPERTY(EditAnywhere, Category = Geometry, meta = (EditCondition="bSimplifyHulls", EditConditionHides))` — The number of faces to target during simplification
- L346 _public member_ `double SimplifyGeometricToleranceAfterTarget = 0;` — `UPROPERTY(EditAnywhere, Category = Geometry, meta = (EditCondition="bSimplifyHulls", EditConditionHides))` — If >0 the mesh will be further simplified beloc SimplifyTargetMaxFaces if the mesh error can be kept below this limit
- L348 _public prototype_ `TArray<FRigidAssetBoneGeometry> Build(FRigidAssetBoneSelection Bones) final override;`

#### struct `FMakeBoxBoneGeometryGenerator`  
`struct FMakeBoxBoneGeometryGenerator : public FRigidDataflowNode`  
_L359-379_
- reflection: `USTRUCT()`
- inherits: `FRigidDataflowNode`
- desc: Make nodes for each generator, each creates a configured generator that can be wired into the generation node
- L366 _public function_ `FMakeBoxBoneGeometryGenerator(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FRigidDataflowNode(InParam, InGuid)`
- L375 _private member_ `TObjectPtr<UBoneGeometryGenerator> Generator;` — `UPROPERTY(EditAnywhere, Instanced, Category = "Generator", meta = (DataflowOutput))`
- L377 _private prototype_ `void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`
- L378 _private prototype_ `void Register();`

#### struct `FMakeSphereBoneGeometryGenerator`  
`struct FMakeSphereBoneGeometryGenerator : public FRigidDataflowNode`  
_L384-404_
- reflection: `USTRUCT()`
- inherits: `FRigidDataflowNode`
- L391 _public function_ `FMakeSphereBoneGeometryGenerator(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FRigidDataflowNode(InParam, InGuid)`
- L400 _private member_ `TObjectPtr<UBoneGeometryGenerator> Generator;` — `UPROPERTY(EditAnywhere, Instanced, Category = "Generator", meta = (DataflowOutput))`
- L402 _private prototype_ `void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`
- L403 _private prototype_ `void Register();`

#### struct `FMakeCapsuleBoneGeometryGenerator`  
`struct FMakeCapsuleBoneGeometryGenerator : public FRigidDataflowNode`  
_L409-429_
- reflection: `USTRUCT()`
- inherits: `FRigidDataflowNode`
- L416 _public function_ `FMakeCapsuleBoneGeometryGenerator(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FRigidDataflowNode(InParam, InGuid)`
- L425 _private member_ `TObjectPtr<UBoneGeometryGenerator> Generator;` — `UPROPERTY(EditAnywhere, Instanced, Category = "Generator", meta = (DataflowOutput))`
- L427 _private prototype_ `void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`
- L428 _private prototype_ `void Register();`

#### struct `FMakeConvexBoneGeometryGenerator`  
`struct FMakeConvexBoneGeometryGenerator : public FRigidDataflowNode`  
_L434-454_
- reflection: `USTRUCT()`
- inherits: `FRigidDataflowNode`
- L441 _public function_ `FMakeConvexBoneGeometryGenerator(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FRigidDataflowNode(InParam, InGuid)`
- L450 _private member_ `TObjectPtr<UBoneGeometryGenerator> Generator;` — `UPROPERTY(EditAnywhere, Instanced, Category = "Generator", meta = (DataflowOutput))`
- L452 _private prototype_ `void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`
- L453 _private prototype_ `void Register();`

#### struct `FMakeConvexDecompBoneGeometryGenerator`  
`struct FMakeConvexDecompBoneGeometryGenerator : public FRigidDataflowNode`  
_L459-479_
- reflection: `USTRUCT()`
- inherits: `FRigidDataflowNode`
- L466 _public function_ `FMakeConvexDecompBoneGeometryGenerator(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FRigidDataflowNode(InParam, InGuid)`
- L475 _private member_ `TObjectPtr<UBoneGeometryGenerator> Generator;` — `UPROPERTY(EditAnywhere, Instanced, Category = "Generator", meta = (DataflowOutput))`
- L477 _private prototype_ `void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`
- L478 _private prototype_ `void Register();`

#### Free symbols / members of external scopes

- L14 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogBoneGeometryGenerators, Log, All);`
- L14 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogBoneGeometryGenerators, Log, All);`
- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace Dataflow` (scope `UE`)
- L18 _prototype_ `void RegisterBoneGeometryGeneratorNodes();` (scope `UE::Dataflow`)
- L149 _prototype_ `FRigidAssetBoneSelection MergeSelection(const FBaseGenerationSettings& Settings, const FRigidAssetBoneSelection& InSelectionSorted);` — Given a bone selection, produce a set of merged bones according the the specified generation settings @param Settings Generation setting to apply for the merge algorithm @param InSelectionSorted A pre-sorted selection of bones

### `Plugins/Experimental/ChaosRigidAsset/Source/ChaosRigidAssetNodes/Private/Generators/ConstraintGenerators.h` (Private)


#### struct `FBaseConstraintGenerationSettings`  
`struct FBaseConstraintGenerationSettings`  
_L22-25_
- reflection: `USTRUCT()`
- desc: Shared settings for all generator types

#### class `UConstraintGenerator`  
`class UConstraintGenerator : public UObject`  
_L33-48_
- reflection: `UCLASS(EditInlineNew, Abstract)`
- inherits: `UObject`
- desc: Base class for constraint generators
- L39 _public function_ `virtual TArray<TObjectPtr<UPhysicsConstraintTemplate>> Build(TObjectPtr<UPhysicsConstraintTemplate> ConstraintTemplate, FRigidAssetBoneSelection Bones) const`
- L47 _private member_ `FBaseConstraintGenerationSettings BaseSettings;` — `UPROPERTY(EditAnywhere, Category = "Generation", meta=(EditInline))`

#### class `UConstraintGenerator_SwingTwist`  
`class UConstraintGenerator_SwingTwist : public UConstraintGenerator`  
_L57-75_
- reflection: `UCLASS()`
- inherits: `UConstraintGenerator`
- desc: Swing/Twist constraint generator Given limits for each of the angular axes, this generator will link all the bones in the input set together with the specified limits
- L63 _public prototype_ `TArray<TObjectPtr<UPhysicsConstraintTemplate>> Build(TObjectPtr<UPhysicsConstraintTemplate> ConstraintTemplate, FRigidAssetBoneSelection Bones) const override;`
- L68 _private member_ `float Swing1Limit;` — `UPROPERTY(EditAnywhere, Category=Constraint)`
- L71 _private member_ `float Swing2Limit;` — `UPROPERTY(EditAnywhere, Category=Constraint)`
- L74 _private member_ `float TwistLimit;` — `UPROPERTY(EditAnywhere, Category=Constraint)`

#### struct `FMakeSwingTwistConstraintGenerator`  
`struct FMakeSwingTwistConstraintGenerator : public FRigidDataflowNode`  
_L83-103_
- reflection: `USTRUCT()`
- inherits: `FRigidDataflowNode`
- desc: Generator make nodes
- L90 _public function_ `FMakeSwingTwistConstraintGenerator(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FRigidDataflowNode(InParam, InGuid)`
- L99 _private member_ `TObjectPtr<UConstraintGenerator> Generator;` — `UPROPERTY(EditAnywhere, Instanced, Category = "Generator", meta = (DataflowOutput))`
- L101 _private prototype_ `void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`
- L102 _private prototype_ `void Register();`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace Dataflow` (scope `UE`)
- L13 _prototype_ `void RegisterConstraintGeneratorNodes();` (scope `UE::Dataflow`)

### `Plugins/Experimental/ChaosRigidAsset/Source/ChaosRigidAssetNodes/Private/Generators/SimulationAffector.h` (Private)


#### struct `FDataflowSimulationAffector`  
`struct FDataflowSimulationAffector`  
_L12-18_
- reflection: `USTRUCT()`
- L16 _public prototype_ `virtual ~FDataflowSimulationAffector() = default;`
- L17 _public function_ `virtual void Process(const TArray<ImmediatePhysics::FActorHandle*>& Actors) const`

#### struct `FDataflowSimulationAffectorTypes`  
`struct FDataflowSimulationAffectorTypes : public FDataflowAnyType`  
_L22-27_
- reflection: `USTRUCT()`
- inherits: `FDataflowAnyType`
- desc: UStruct based types
- L24 _public typedef_ `using FPolicyType = FDataflowUDerivedStructTypePolicy<FDataflowSimulationAffector>;`
- L25 _public typedef_ `using FStorageType = void;`

#### struct `FDataflowSimulationAccelerationAffector`  
`struct FDataflowSimulationAccelerationAffector: public FDataflowSimulationAffector`  
_L37-47_
- reflection: `USTRUCT()`
- inherits: `FDataflowSimulationAffector`
- L41 _public prototype_ `virtual ~FDataflowSimulationAccelerationAffector() override = default;`
- L42 _public prototype_ `virtual void Process(const TArray<ImmediatePhysics::FActorHandle*>& Actors) const override;`
- L46 _private member_ `FVector Acceleration = FVector(0, 0, -980);` — `UPROPERTY(EditAnywhere, Category = Physics, meta = (ForceUnits = "cm/s2"))` — default to earth gravity

#### struct `FDataflowSimulationAccelerationAffectorNode`  
`struct FDataflowSimulationAccelerationAffectorNode : public FDataflowNode`  
_L53-66_
- reflection: `USTRUCT()`
- inherits: `FDataflowNode`
- desc: Output a affector that apply a constant acceleration to all dynamic actors
- L59 _public prototype_ `FDataflowSimulationAccelerationAffectorNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L63 _private member_ `FDataflowSimulationAccelerationAffector Affector;` — `UPROPERTY(EditAnywhere, Category = Affector, meta = (DataflowOutput, ShowOnlyInnerProperties))`
- L65 _private prototype_ `void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FDataflowSimulationWindAffector`  
`struct FDataflowSimulationWindAffector : public FDataflowSimulationAffector`  
_L71-87_
- reflection: `USTRUCT()`
- inherits: `FDataflowSimulationAffector`
- L75 _public prototype_ `virtual ~FDataflowSimulationWindAffector() override = default;`
- L76 _public prototype_ `virtual void Process(const TArray<ImmediatePhysics::FActorHandle*>& Actors) const override;`
- L80 _private member_ `float AirDensity = 1.2f;` — `UPROPERTY(EditAnywhere, Category = Physics, meta = (ForceUnits = "kg/m3"))` — standard air density at about 20C
- L83 _private member_ `float WindSpeed = 15.f;` — `UPROPERTY(EditAnywhere, Category = Physics, meta = (ForceUnits = "km/h"))`
- L86 _private member_ `FVector WindDirection = FVector::XAxisVector;` — `UPROPERTY(EditAnywhere, Category = Physics)`

#### struct `FDataflowSimulationWindAffectorNode`  
`struct FDataflowSimulationWindAffectorNode : public FDataflowNode`  
_L93-106_
- reflection: `USTRUCT()`
- inherits: `FDataflowNode`
- desc: Output a affector that apply a Wind force onto the rigid bodies
- L99 _public prototype_ `FDataflowSimulationWindAffectorNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L103 _private member_ `FDataflowSimulationWindAffector Affector;` — `UPROPERTY(EditAnywhere, Category = Affector, meta = (DataflowOutput, ShowOnlyInnerProperties))`
- L105 _private prototype_ `void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### Free symbols / members of external scopes

- L29 _namespace_ `namespace UE`
- L29 _namespace_ `namespace Dataflow` (scope `UE`)
- L31 _prototype_ `void RegisterSimulationAffectorNodes();` (scope `UE::Dataflow`)

### `Plugins/Experimental/ChaosRigidAsset/Source/ChaosRigidAssetNodes/Private/PhysicsAssetBuilder.h` (Private)


#### class `UE::Chaos::RigidAsset::FPhysicsAssetBuilder`  
`class FPhysicsAssetBuilder`  
_L20-59_
- desc: Builder for physics assets Takes source data for physics assets (bodies, constraints, mesh, skeleton) and creates a UPhysicsAsset (or writes to a target asset)
- L25 _public prototype_ `static FPhysicsAssetBuilder Make(TObjectPtr<USkeleton> InTargetSkeleton);` — Overloads for creating a builder from required data.
- L26 _public prototype_ `static FPhysicsAssetBuilder Make(TObjectPtr<USkeleton> InTargetSkeleton, const TArray<TObjectPtr<USkeletalBodySetup>>& InBodies, const TArray<TObjectPtr<UPhysicsConstraintTemplate>>& InConstraints);`
- L29 _public prototype_ `FPhysicsAssetBuilder& Body(TObjectPtr<USkeletalBodySetup> NewBody);` — Append a new body to the asset
- L32 _public prototype_ `FPhysicsAssetBuilder& Joint(TObjectPtr<UPhysicsConstraintTemplate> NewJoint);` — Append a new constraint to the asset
- L35 _public prototype_ `FPhysicsAssetBuilder& JoinLast(TObjectPtr<UPhysicsConstraintTemplate> NewJoint);` — Apply the provided constraint template to the last pair of bodies in the builder
- L38 _public prototype_ `FPhysicsAssetBuilder& Path(FString InDesiredPath);` — If not targetting a specific asset, set the path to where the resulting asset will be stored
- L39 _public prototype_ `FPhysicsAssetBuilder& Path(TObjectPtr<UObject> InObjectReferenceForPath);`
- L42 _public prototype_ `FPhysicsAssetBuilder& SetTargetAsset(TObjectPtr<UPhysicsAsset> InAsset);` — Set a target asset instead of a path - this asset will be overwritten with new state when Build() is called
- L45 _public prototype_ `TObjectPtr<UPhysicsAsset> Build();` — Finalize the physics asset and apply the builder to it
- L49 _private prototype_ `FPhysicsAssetBuilder();`
- L51 _private prototype_ `void CreateNewAsset();`
- L53 _private member_ `FString DesiredPath;`
- L55 _private member_ `TObjectPtr<USkeleton> TargetSkeleton;`
- L56 _private member_ `TArray<TObjectPtr<USkeletalBodySetup>> Bodies;`
- L57 _private member_ `TArray<TObjectPtr<UPhysicsConstraintTemplate>> Constraints;`
- L58 _private member_ `TObjectPtr<UPhysicsAsset> TargetAsset;`

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace Chaos` (scope `UE`)
- L14 _namespace_ `namespace RigidAsset` (scope `UE::Chaos`)

### `Plugins/Experimental/ChaosRigidAsset/Source/ChaosRigidAssetNodes/Private/PhysicsAssetDataflowNodes.h` (Private)


#### struct `FDataflowPhysicsAssetMakeState`  
`struct FDataflowPhysicsAssetMakeState : public FRigidDataflowNode`  
_L41-66_
- reflection: `USTRUCT()`
- inherits: `FRigidDataflowNode`
- desc: The asset state is the object that holds the intermediate data that is built throughout the execution of the dataflow graph. It's analogous to a collection used in other dataflow graphs. This graph doesn't use a collection due to needing support for copy-on-write with UObjects Asset state objects are lightweight and should be passed by-value as they support copy-on-write so each state instance is fairly small and references its shared state
- L51 _public prototype_ `Register();`
- L58 _private member_ `TObjectPtr<USkeletalMesh> TargetMesh;` — `UPROPERTY(EditAnywhere, Category = Config, meta = (DataflowInput))` — Optional mesh input if creating a state for a mesh that isn't currently being edited
- L62 _private member_ `FPhysicsAssetDataflowState State;` — `UPROPERTY(meta = (DataflowOutput))` — Resulting state for the mesh
- L64 _private prototype_ `void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`
- L65 _private prototype_ `void Register();`

#### struct `FDataflowAggGeomAddShape`  
`struct FDataflowAggGeomAddShape : public FRigidDataflowMultiInputNode`  
_L74-108_
- reflection: `USTRUCT()`
- inherits: `FRigidDataflowMultiInputNode`
- desc: Add a shape to an aggregate geometry
- L82 _public function_ `FDataflowAggGeomAddShape(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FRigidDataflowMultiInputNode(Shapes, InParam, InGuid)`
- L93 _private member_ `TArray<UE::Chaos::RigidAsset::FSimpleGeometry> Shapes;` — `UPROPERTY()` — Shapes to add to the aggregate geometry
- L97 _private member_ `FKAggregateGeom AggGeom;` — `UPROPERTY(meta = (DataflowInput, DataflowOutput, DataflowPassthrough = AggGeom))` — The aggregate geometry to add the shape to
- L100 _private prototype_ `bool CanDebugDraw() const override;`
- L101 _private prototype_ `bool CanDebugDrawViewMode(const FName& ViewModeName) const override;`
- L102 _private prototype_ `void DebugDraw(UE::Dataflow::FContext& Context, IDataflowDebugDrawInterface& DataflowRenderingInterface, const FDebugDrawParameters& DebugDrawParameters) const override;`
- L106 _private prototype_ `void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`
- L107 _private prototype_ `void Register();`

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FDataflowAggGeomAddShape> : public TStructOpsTypeTraitsBase2<FDataflowAggGeomAddShape>`  
_L111-117_
- inherits: `TStructOpsTypeTraitsBase2<FDataflowAggGeomAddShape>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L114-116_

#### struct `FDataflowPhysicsAssetTerminalNode`  
`struct FDataflowPhysicsAssetTerminalNode : public FDataflowTerminalNode`  
_L125-148_
- reflection: `USTRUCT(meta = (DataflowTerminal))`
- inherits: `FDataflowTerminalNode`
- desc: Terminal node that converts an asset state into the final asset
- L132 _public prototype_ `FDataflowPhysicsAssetTerminalNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L138 _private member_ `FPhysicsAssetDataflowState State;` — `UPROPERTY(meta = (DataflowInput))` — The state to convert into the final asset
- L142 _private member_ `TObjectPtr<UPhysicsAsset> PhysicsAsset = nullptr;` — `UPROPERTY(EditAnywhere, Category = Asset, meta = (DataflowInput))` — Override target asset to write to - optional, defaults to the current asset in the editor
- L145 _private prototype_ `void SetAssetValue(TObjectPtr<UObject> Asset, UE::Dataflow::FContext& Context) const override;` — FDataflowTerminalNode
- L146 _private prototype_ `void Evaluate(UE::Dataflow::FContext& Context) const override;`

#### struct `FDataflowPhysicsAssetAddBody`  
`struct FDataflowPhysicsAssetAddBody : public FRigidDataflowNode`  
_L156-176_
- reflection: `USTRUCT()`
- inherits: `FRigidDataflowNode`
- desc: Add a body setup to an asset state
- L163 _public prototype_ `FDataflowPhysicsAssetAddBody(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L169 _private member_ `TObjectPtr<USkeletalBodySetup> Body;` — `UPROPERTY(meta = (DataflowInput))` — Body to add
- L173 _private member_ `FPhysicsAssetDataflowState State;` — `UPROPERTY(meta = (DataflowInput, DataflowOutput, DataflowPassthrough = State))` — State to write to
- L175 _private prototype_ `void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FDataflowMakeBody`  
`struct FDataflowMakeBody : public FRigidDataflowNode`  
_L184-216_
- reflection: `USTRUCT()`
- inherits: `FRigidDataflowNode`
- desc: Make a single body setup from a template
- L191 _public function_ `FDataflowMakeBody(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FRigidDataflowNode(InParam, InGuid)`
- L200 _private prototype_ `bool CanDebugDraw() const override;`
- L201 _private prototype_ `bool CanDebugDrawViewMode(const FName& ViewModeName) const override;`
- L202 _private prototype_ `void DebugDraw(UE::Dataflow::FContext& Context, IDataflowDebugDrawInterface& DataflowRenderingInterface, const FDebugDrawParameters& DebugDrawParameters) const override;`
- L208 _private member_ `TObjectPtr<USkeletalBodySetup> Body;` — `UPROPERTY(EditAnywhere, Instanced, Category = Body, meta = (DataflowOutput))` — Template body setup for details panel and output new body instance
- L212 _private member_ `FName BoneName;` — `UPROPERTY(EditAnywhere, Category = Body, meta = (DataflowInput))` — Bone that this body should be bound to
- L214 _private prototype_ `void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`
- L215 _private prototype_ `void Register(const UE::Dataflow::FNodeParameters& InParam);`

#### struct `FDataflowMakeJoint`  
`struct FDataflowMakeJoint : public FRigidDataflowNode`  
_L224-244_
- reflection: `USTRUCT()`
- inherits: `FRigidDataflowNode`
- desc: Make a single joint setup from a template
- L231 _public function_ `FDataflowMakeJoint(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FRigidDataflowNode(InParam, InGuid)`
- L240 _private member_ `TObjectPtr<UPhysicsConstraintTemplate> Joint;` — `UPROPERTY(EditAnywhere, Instanced, Category = Body, meta = (DataflowOutput))`
- L242 _private prototype_ `void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`
- L243 _private prototype_ `void Register(const UE::Dataflow::FNodeParameters& InParam);`

#### struct `FDataflowSelectBonesByName`  
`struct FDataflowSelectBonesByName : public FRigidDataflowNode`  
_L252-282_
- reflection: `USTRUCT()`
- inherits: `FRigidDataflowNode`
- desc: Select bones in a mesh given a name search pattern
- L260 _public function_ `FDataflowSelectBonesByName(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FRigidDataflowNode(InParam, InGuid)`
- L270 _private member_ `FPhysicsAssetDataflowState State;` — `UPROPERTY(meta = (DataflowInput))` — State to select bones within
- L274 _private member_ `FRigidAssetBoneSelection Selection;` — `UPROPERTY(meta = (DataflowOutput))` — Resulting selection
- L278 _private member_ `FString SearchString;` — `UPROPERTY(EditAnywhere, Category = Parameters)` — Search pattern to use. Supports wildcards (? - match single character, * - match sequence)
- L280 _private prototype_ `void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`
- L281 _private prototype_ `void Register(const UE::Dataflow::FNodeParameters& InParam);`

#### struct `FDataflowAppendBoneSelection`  
`struct FDataflowAppendBoneSelection : public FRigidDataflowNode`  
_L290-320_
- reflection: `USTRUCT()`
- inherits: `FRigidDataflowNode`
- desc: Append a bone selection to another
- L298 _public function_ `FDataflowAppendBoneSelection(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FRigidDataflowNode(InParam, InGuid)`
- L308 _private member_ `FRigidAssetBoneSelection A;` — `UPROPERTY(meta = (DataflowInput))` — First selection
- L312 _private member_ `FRigidAssetBoneSelection B;` — `UPROPERTY(meta = (DataflowInput))` — Second selection
- L316 _private member_ `FRigidAssetBoneSelection Selection;` — `UPROPERTY(meta = (DataflowOutput))` — Resulting selection, a combination of A and B
- L318 _private prototype_ `void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`
- L319 _private prototype_ `void Register();`

#### struct `FDataflowSelectConnectedBones`  
`struct FDataflowSelectConnectedBones : public FRigidDataflowNode`  
_L328-358_
- reflection: `USTRUCT()`
- inherits: `FRigidDataflowNode`
- desc: Select bones connected to each bone already in a selection.
- L336 _public function_ `FDataflowSelectConnectedBones(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FRigidDataflowNode(InParam, InGuid)`
- L346 _private member_ `int32 DistanceUp = 0;` — `UPROPERTY(EditAnywhere, Category = Settings)` — Disance to walk up the hierarchy to find bones
- L350 _private member_ `int32 DistanceDown = 0;` — `UPROPERTY(EditAnywhere, Category = Settings)` — Distance to walk down the hierarchy to find bones
- L354 _private member_ `FRigidAssetBoneSelection Selection;` — `UPROPERTY(meta = (DataflowInput, DataflowOutput, DataflowPassthrough = "Selection"))` — Resulting bone selction
- L356 _private prototype_ `void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`
- L357 _private prototype_ `void Register(const UE::Dataflow::FNodeParameters& InParam);`

#### struct `FDataflowMergeBoneSelection`  
`struct FDataflowMergeBoneSelection : public FRigidDataflowNode`  
_L366-392_
- reflection: `USTRUCT()`
- inherits: `FRigidDataflowNode`
- desc: Merge a bone selection using the specified merge profile
- L374 _public function_ `FDataflowMergeBoneSelection(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FRigidDataflowNode(InParam, InGuid)`
- L384 _private member_ `FRigidAssetBoneSelection Selection;` — `UPROPERTY(meta = (DataflowInput, DataflowOutput, DataflowPassthrough = "Selection"))` — Resulting bone selection
- L388 _private member_ `FBaseGenerationSettings MergeProfile;` — `UPROPERTY(EditAnywhere, Category = Settings)` — Merge settings to use to decide how to merge the bones
- L390 _private prototype_ `void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`
- L391 _private prototype_ `void Register(const UE::Dataflow::FNodeParameters& InParam);`

#### struct `FDataflowCreateGeometryForBones`  
`struct FDataflowCreateGeometryForBones : public FRigidDataflowNode`  
_L402-442_
- reflection: `USTRUCT()`
- inherits: `FRigidDataflowNode`
- desc: Apply a geometry generator to a bone selection, creating bodies for each bone The method of geometry generation is generic and offloaded to a "Generator" object/ @see UBoneGeometryGenerator for implementation and creating your own generator node.
- L410 _public function_ `FDataflowCreateGeometryForBones(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FRigidDataflowNode(InParam, InGuid)`
- L419 _private member_ `TObjectPtr<UBoneGeometryGenerator> Generator;` — `UPROPERTY(meta=(DataflowInput))`
- L423 _private member_ `TObjectPtr<USkeletalBodySetup> TemplateBody;` — `UPROPERTY(meta=(DataflowInput))`
- L426 _private member_ `bool bCreateMissingBodies = true;` — `UPROPERTY(EditAnywhere, Category=Generation)`
- L429 _private member_ `FPhysicsAssetDataflowState State;` — `UPROPERTY(meta = (DataflowInput, DataflowOutput, DataflowPassthrough = "State"))`
- L432 _private member_ `FRigidAssetBoneSelection Selection;` — `UPROPERTY(meta = (DataflowInput))`
- L435 _private prototype_ `bool CanDebugDraw() const override;`
- L436 _private prototype_ `bool CanDebugDrawViewMode(const FName& ViewModeName) const override;`
- L437 _private prototype_ `void DebugDraw(UE::Dataflow::FContext& Context, IDataflowDebugDrawInterface& DataflowRenderingInterface, const FDebugDrawParameters& DebugDrawParameters) const override;`
- L440 _private prototype_ `void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`
- L441 _private prototype_ `void Register();`

#### struct `FDataflowAutoConstrainBodies`  
`struct FDataflowAutoConstrainBodies : public FRigidDataflowNode`  
_L452-485_
- reflection: `USTRUCT()`
- inherits: `FRigidDataflowNode`
- desc: Apply a constraint generator to a bone selection, creating constraints for each pair of bodies The method of constraint generation is generic and offloaded to a "Generator" object/ @see UConstraintGenerator for implementation and creating your own generator node.
- L459 _public function_ `FDataflowAutoConstrainBodies(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FRigidDataflowNode(InParam, InGuid)`
- L469 _private member_ `TObjectPtr<UConstraintGenerator> Generator;` — `UPROPERTY(meta=(DataflowInput))` — Generation method to use
- L473 _private member_ `TObjectPtr<UPhysicsConstraintTemplate> TemplateConstraint;` — `UPROPERTY(meta=(DataflowInput))` — Template constraint to take properties from
- L477 _private member_ `FPhysicsAssetDataflowState State;` — `UPROPERTY(meta = (DataflowInput, DataflowOutput, DataflowPassthrough = "State"))` — State to apply the joints to
- L481 _private member_ `FRigidAssetBoneSelection Selection;` — `UPROPERTY(meta = (DataflowInput))` — Optional selection, restricts the bodies that will attempt to auto constrain
- L483 _private prototype_ `void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`
- L484 _private prototype_ `void Register();`

#### struct `FDataflowSetBodyGeometry`  
`struct FDataflowSetBodyGeometry : public FRigidDataflowNode`  
_L493-524_
- reflection: `USTRUCT()`
- inherits: `FRigidDataflowNode`
- desc: Given a body setup, replace the internal aggregate geometry with the provided geometry
- L500 _public function_ `FDataflowSetBodyGeometry(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FRigidDataflowNode(InParam, InGuid)`
- L510 _private member_ `TObjectPtr<USkeletalBodySetup> Body;` — `UPROPERTY(meta = (DataflowInput, DataflowOutput, DataflowPassthrough = "Body"))` — The body to modify
- L514 _private member_ `FKAggregateGeom Geometry;` — `UPROPERTY(meta = (DataflowInput))` — The Geometry to set on the body
- L517 _private prototype_ `bool CanDebugDraw() const override;`
- L518 _private prototype_ `bool CanDebugDrawViewMode(const FName& ViewModeName) const override;`
- L519 _private prototype_ `void DebugDraw(UE::Dataflow::FContext& Context, IDataflowDebugDrawInterface& DataflowRenderingInterface, const FDebugDrawParameters& DebugDrawParameters) const override;`
- L522 _private prototype_ `void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`
- L523 _private prototype_ `void Register();`

#### struct `FDataflowNewBoneSelection`  
`struct FDataflowNewBoneSelection : public FRigidDataflowNode`  
_L532-561_
- reflection: `USTRUCT()`
- inherits: `FRigidDataflowNode`
- desc: Create a new, empty selection for the specified mesh
- L539 _public function_ `FDataflowNewBoneSelection(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FRigidDataflowNode(InParam, InGuid)`
- L549 _private member_ `FRigidAssetBoneSelection Selection;` — `UPROPERTY(meta = (DataflowOutput))` — The created selection
- L553 _private member_ `TObjectPtr<USkeleton> Skeleton = nullptr;` — `UPROPERTY(meta = (DataflowInput))` — The skeleton to target if not using the currently edited asset
- L557 _private member_ `TObjectPtr<USkeletalMesh> Mesh = nullptr;` — `UPROPERTY(meta = (DataflowInput))` — The Mesh to target if not using the currently edited asset
- L559 _private prototype_ `void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`
- L560 _private prototype_ `void Register(const UE::Dataflow::FNodeParameters& InParam);`

#### struct `FDataflowRigidSimulationCachingNode`  
`struct FDataflowRigidSimulationCachingNode : public FRigidDataflowNode`  
_L569-627_
- reflection: `USTRUCT(meta = (Experimental))`
- inherits: `FRigidDataflowNode`
- desc: Run a rigid simulation of a Physics asset state and bake it into an animation file
- L576 _public function_ `FDataflowRigidSimulationCachingNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FRigidDataflowNode(InParam, InGuid)`
- L586 _private member_ `FPhysicsAssetDataflowState State;` — `UPROPERTY(meta = (DataflowInput))` — Input physics asset state to use for the simulation
- L590 _private member_ `TObjectPtr<UAnimSequence> Animation = nullptr;` — `UPROPERTY(meta = (DataflowOutput))` — Output animation asset
- L594 _private member_ `float Duration = 5.0;` — `UPROPERTY(EditAnywhere, Category = Caching, meta = (DataflowInput, ClampMin=0))` — Duration in seconds of the simulation
- L598 _private member_ `int32 FrameRate = 30;` — `UPROPERTY(EditAnywhere, Category = Caching, meta = (DataflowInput, ClampMin = 1))` — Number of frames per second
- L602 _private member_ `FVector Gravity = FVector(0, 0, 980);` — `UPROPERTY(EditAnywhere, Category = Simulation, meta = (DataflowInput))` — Gravity vector in cm/s^2
- L606 _private member_ `FVector Velocity = FVector(0, 0, 0);` — `UPROPERTY(EditAnywhere, Category = Simulation, meta = (DataflowInput))` — Simulation space velocity in cm/s
- L610 _private member_ `FDataflowSimulationAffectorTypes Affector;` — `UPROPERTY(EditAnywhere, Category = Simulation, meta = (DataflowInput))` — Affector used to manipulate objects in the simulation
- L612 _private prototype_ `void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`
- L613 _private prototype_ `void Register(const UE::Dataflow::FNodeParameters& InParam);`
- L615 _private prototype_ `TUniquePtr<FBodyInstance> CreateBodyInstance(USkeletalBodySetup* BodySetup) const;`
- L625 _private prototype_ `void BuildSimulationFromState(const FPhysicsAssetDataflowState& InState, FSimulationState& OutSimState) const;`
- L626 _private prototype_ `void RunSimulation(FSimulationState& Simulation, const FVector& InGravity) const;`

#### struct `FDataflowRigidSimulationCachingNode::FSimulationState`  
`struct FSimulationState`  
_L617-623_
- L619 _public member_ `float FixedTimeStep = 0;`
- L620 _public member_ `TUniquePtr<ImmediatePhysics::FSimulation> Simulation;`
- L621 _public member_ `TMap<FName, ImmediatePhysics::FActorHandle*> ActorsByName;`
- L622 _public member_ `TArray<ImmediatePhysics::FActorHandle*> Actors;`

#### Free symbols / members of external scopes

- L115 _enumerator_ `WithCopy = false` (scope `TStructOpsTypeTraits::__anon134d88030103`)
- L631 _namespace_ `namespace UE`
- L631 _namespace_ `namespace Dataflow` (scope `UE`)
- L633 _prototype_ `void RegisterPhysicsAssetTerminalNode();` (scope `UE::Dataflow`)
- L634 _prototype_ `void RegisterPhysicsAssetNodes();` (scope `UE::Dataflow`)

### `Plugins/Experimental/ChaosRigidAsset/Source/ChaosRigidAssetNodes/Private/RigidDataflowNode.h` (Private)


#### struct `FRigidDataflowNode`  
`struct FRigidDataflowNode : public FDataflowNode`  
_L16-112_
- reflection: `USTRUCT()`
- inherits: `FDataflowNode`
- desc: Intermediate node for rigid asset node implementations encapsulating common functionality
- L22 _public prototype_ `FRigidDataflowNode() = default;`
- L24 _public function_ `FRigidDataflowNode(const UE::Dataflow::FNodeParameters& Param, FGuid InGuid) : FDataflowNode(Param, InGuid) , Owner(Param.OwningObject)`
- L32 _public function_ `TObjectPtr<UObject> GetOwner() const` — Get the owning UObject for the node, to store UObjects in the asset safely
- L39 _public function_ `template<typename... T> void AddInputs(T&&... Args)` — Multi-input versions of the pin registration functions
- L45 _public function_ `template<typename... T> void AddOutputs(T&&... Args)`
- L51 _public function_ `template<typename... T> void AddPassthroughs(T&&... Args)`
- L60 _protected function_ `template<typename T> TObjectPtr<T> GetContextOwnerAs(UE::Dataflow::FContext& InContext) const` — Grab the context owner and return it as T if possible, otherwise nullptr
- L70 _protected function_ `TObjectPtr<UObject> GetContextOwner(UE::Dataflow::FContext& InContext) const`
- L81 _protected function_ `TObjectPtr<UDataflowAttachment> GetAttachment(UE::Dataflow::FContext& InContext) const` — Get the dataflow attachement if it is avaialble for the current asset
- L86 _protected function_ `TObjectPtr<UObject> GetAttachmentOwner(UE::Dataflow::FContext& InContext) const`
- L97 _protected function_ `template<typename T> TObjectPtr<T> GetAttachmentOwnerAs(UE::Dataflow::FContext& InContext) const`
- L110 _private member_ `TObjectPtr<UObject> Owner;` — `UPROPERTY()`

#### struct `IMultiPinArrayConnector`  
`struct IMultiPinArrayConnector`  
_L114-127_
- L116 _public function_ `virtual ~IMultiPinArrayConnector()`
- L120 _public prototype_ `virtual void InitPins() = 0;`
- L121 _public prototype_ `virtual TArray<UE::Dataflow::FPin> AddPins() = 0;`
- L122 _public prototype_ `virtual bool CanAddPin() const = 0;`
- L123 _public prototype_ `virtual TArray<UE::Dataflow::FPin> GetPinsToRemove() const = 0;`
- L124 _public prototype_ `virtual void OnPinRemoved(const UE::Dataflow::FPin& Pin) = 0;`
- L125 _public prototype_ `virtual bool CanRemovePin() const = 0;`
- L126 _public prototype_ `virtual void PostSerialize(const FArchive& Ar) = 0;`

#### struct `TMultiPinArrayConnector`  
`template<typename T> struct TMultiPinArrayConnector : public IMultiPinArrayConnector`  
_L130-250_
- inherits: `IMultiPinArrayConnector`
- L132 _public prototype_ `TMultiPinArrayConnector() = delete;`
- L133 _public function_ `explicit TMultiPinArrayConnector(FRigidDataflowNode& InNode, TArray<T>& InPinContainer, int32 InMinimumNumPins) : Node(InNode) , PinContainer(InPinContainer) , MinimumNumPins(InMinimumNumPins)`
- L141 _public function_ `void InitPins() override`
- L151 _public function_ `TArray<UE::Dataflow::FPin> AddPins() override`
- L168 _public function_ `bool CanAddPin() const override`
- L174 _public function_ `TArray<UE::Dataflow::FPin> GetPinsToRemove() const override`
- L200 _public function_ `void OnPinRemoved(const UE::Dataflow::FPin& Pin) override`
- L205 _public function_ `bool CanRemovePin() const override`
- L210 _public function_ `void PostSerialize(const FArchive& Ar) override`
- L247 _private member_ `FRigidDataflowNode& Node;`
- L248 _private member_ `TArray<T>& PinContainer;`
- L249 _private member_ `int32 MinimumNumPins;`

#### struct `FRigidDataflowMultiInputNode`  
`struct FRigidDataflowMultiInputNode : public FRigidDataflowNode`  
_L253-339_
- reflection: `USTRUCT()`
- inherits: `FRigidDataflowNode`
- L257 _public prototype_ `FRigidDataflowMultiInputNode() = default;`
- L260 _public function_ `template<typename T> explicit FRigidDataflowMultiInputNode(TArray<T>& InPinContainer, const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid) : FRigidDataflowNode(InParam, InGuid)`
- L266 _public function_ `void InitPins()`
- L274 _public function_ `TArray<UE::Dataflow::FPin> AddPins() override`
- L284 _public function_ `bool CanAddPin() const override`
- L295 _public function_ `TArray<UE::Dataflow::FPin> GetPinsToRemove() const override`
- L306 _public function_ `void OnPinRemoved(const UE::Dataflow::FPin& Pin) override`
- L317 _public function_ `bool CanRemovePin() const override`
- L327 _public function_ `void PostSerialize(const FArchive& Ar) override`
- L338 _private member_ `TUniquePtr<IMultiPinArrayConnector> Connector = nullptr;`

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FRigidDataflowMultiInputNode> : public TStructOpsTypeTraitsBase2<FRigidDataflowMultiInputNode>`  
_L342-348_
- inherits: `TStructOpsTypeTraitsBase2<FRigidDataflowMultiInputNode>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L345-347_

#### Free symbols / members of external scopes

- L346 _enumerator_ `WithCopy = false` (scope `TStructOpsTypeTraits::__anon2580a79c0103`)

### `Plugins/Experimental/ChaosRigidAsset/Source/ChaosRigidAssetNodes/Private/ShapeElemNodes.h` (Private)


#### struct `UE::Chaos::RigidAsset::FSimpleGeometry`  
`struct FSimpleGeometry`  
_L25-47_
- reflection: `USTRUCT()`
- desc: Generic container for any geometry element while referenced in a dataflow graph
- L29 _public prototype_ `FSimpleGeometry() = default;`
- L31 _public function_ `FSimpleGeometry(TSharedPtr<FKShapeElem> InElem) : GeometryElement(InElem)`
- L36 _public function_ `FSimpleGeometry(const FTransform InLocalTransform, TSharedPtr<FKShapeElem> InElem) : LocalTransform(InLocalTransform) , GeometryElement(InElem)`
- L43 _public prototype_ `FSimpleGeometry Duplicate();` — Duplicate this geometry handling the geometry type correctly
- L45 _public member_ `FTransform LocalTransform = FTransform::Identity;`
- L46 _public member_ `TSharedPtr<FKShapeElem> GeometryElement = nullptr;`

#### struct `UE::Chaos::RigidAsset::FMakeBoxElemDataflowNode`  
`struct FMakeBoxElemDataflowNode : public FDataflowNode`  
_L55-80_
- reflection: `USTRUCT()`
- inherits: `FDataflowNode`
- desc: Make single-element nodes.
- L62 _public function_ `FMakeBoxElemDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowNode(InParam, InGuid)`
- L72 _private member_ `FKBoxElem Box;` — `UPROPERTY(EditAnywhere, Category=Settings)` — Input box data
- L76 _private member_ `FSimpleGeometry Geometry;` — `UPROPERTY(meta = (DataflowOutput))` — Produced geometry
- L78 _private prototype_ `void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`
- L79 _private prototype_ `void Register();`

#### struct `UE::Chaos::RigidAsset::FMakeSphereElemDataflowNode`  
`struct FMakeSphereElemDataflowNode : public FDataflowNode`  
_L85-110_
- reflection: `USTRUCT()`
- inherits: `FDataflowNode`
- L92 _public function_ `FMakeSphereElemDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowNode(InParam, InGuid)`
- L102 _private member_ `FKSphereElem Sphere;` — `UPROPERTY(EditAnywhere, Category=Settings)` — Input Sphere data
- L106 _private member_ `FSimpleGeometry Geometry;` — `UPROPERTY(meta = (DataflowOutput))` — Produced geometry
- L108 _private prototype_ `void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`
- L109 _private prototype_ `void Register();`

#### struct `UE::Chaos::RigidAsset::FMakeCapsuleElemDataflowNode`  
`struct FMakeCapsuleElemDataflowNode : public FDataflowNode`  
_L115-140_
- reflection: `USTRUCT()`
- inherits: `FDataflowNode`
- L122 _public function_ `FMakeCapsuleElemDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowNode(InParam, InGuid)`
- L132 _private member_ `FKSphylElem Capsule;` — `UPROPERTY(EditAnywhere, Category=Settings)` — Input capsule data
- L136 _private member_ `FSimpleGeometry Geometry;` — `UPROPERTY(meta = (DataflowOutput))` — Produced geometry
- L138 _private prototype_ `void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`
- L139 _private prototype_ `void Register();`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace Dataflow` (scope `UE`)
- L14 _prototype_ `void RegisterShapeNodes();` (scope `UE::Dataflow`)
- L17 _namespace_ `namespace UE`
- L17 _namespace_ `namespace Chaos` (scope `UE`)
- L17 _namespace_ `namespace RigidAsset` (scope `UE::Chaos`)

### `Plugins/Experimental/ChaosRigidAsset/Source/ChaosRigidAssetNodes/Public/BoneSelection.h` (Public)


#### struct `FRigidAssetBoneInfo`  
`struct FRigidAssetBoneInfo`  
_L17-42_
- reflection: `USTRUCT()`
- desc: Represents a single bone in a selection
- L21 _public prototype_ `FRigidAssetBoneInfo() = default;`
- L22 _public prototype_ `FRigidAssetBoneInfo(FName InName, int32 InIndex, int32 InDepth);`
- L26 _public member_ `FName Name = NAME_None;` — `UPROPERTY()` — Bone name in the skeleton
- L30 _public member_ `int32 Index = INDEX_NONE;` — `UPROPERTY()` — Raw bone index in the skeleton
- L34 _public member_ `int32 Depth = INDEX_NONE;` — `UPROPERTY()` — Depth of this bone in the hierarchy (distance from root)
- L38 _public member_ `TArray<int32> MergedChildren;` — `UPROPERTY()` — List of child bones merged into this one
- L40 _public prototype_ `bool operator ==(const FRigidAssetBoneInfo& Other) const = default;`
- L41 _public prototype_ `bool operator <(const FRigidAssetBoneInfo& Other) const;`

#### struct `FRigidAssetBoneSelection`  
`struct FRigidAssetBoneSelection`  
_L48-71_
- reflection: `USTRUCT()`
- desc: Represents a selection set of bones within a skeleton
- L54 _public member_ `TArray<FRigidAssetBoneInfo> SelectedBones;` — `UPROPERTY()` — Individual bones in the selection
- L58 _public member_ `TObjectPtr<USkeleton> Skeleton;` — `UPROPERTY()` — Skeleton that the bones reference
- L62 _public member_ `TObjectPtr<USkeletalMesh> Mesh;` — `UPROPERTY()` — Mesh that the bones reference
- L66 _public prototype_ `bool ContainsIndex(int32 InBoneIndex) const;` — Contains for index and name, cannot check the skeleton matches, so care should be taken that the search items here are representative of the mesh and skeleton bound to the selection
- L67 _public prototype_ `bool Contains(FName InBoneName) const;`
- L70 _public prototype_ `void SortBones();` — Sorts bones so parents are before children

### `Plugins/Experimental/ChaosRigidAsset/Source/ChaosRigidAssetNodes/Public/ChaosRigidAssetNodesModule.h` (Public)


#### class `FChaosRigidAssetNodesModule`  
`class FChaosRigidAssetNodesModule : public IModuleInterface`  
_L7-15_
- inherits: `IModuleInterface`
- L11 _public prototype_ `virtual void StartupModule() override;`
- L12 _public prototype_ `virtual void ShutdownModule() override;`

### `Plugins/Experimental/ChaosRigidAsset/Source/ChaosRigidAssetNodes/Public/CopyOnWriteArray.h` (Public)


#### class `TCopyOnWriteArray`  
`template<typename T> class TCopyOnWriteArray`  
_L47-296_
- desc: Wrapper for an array that implements copy-on-write for the array. If there are N readers but no writers there will be a single copy of the array If a codepath writes to the array and they aren't the only referencer, the array will be duplicated This means each modification will not implicitly duplicate - only if there are multiple referencers otherwise, we modify in place.
- L50 _public typedef_ `using InnerArrayType = TArray<T>;`
- L51 _public typedef_ `using AllocatorType = InnerArrayType::AllocatorType;`
- L52 _public typedef_ `using SizeType = InnerArrayType::SizeType;`
- L54 _public function_ `TCopyOnWriteArray()`
- L59 _public function_ `TCopyOnWriteArray(const TCopyOnWriteArray& Other)`
- L64 _public function_ `TCopyOnWriteArray(TCopyOnWriteArray&& Other)`
- L69 _public function_ `TCopyOnWriteArray& operator=(const TCopyOnWriteArray& Other)`
- L75 _public function_ `TCopyOnWriteArray& operator=(TCopyOnWriteArray&& Other)`
- L81 _public function_ `const T& operator [](int32 Index) const`
- L87 _public function_ `TArray<T>::RangedForConstIteratorType begin() const`
- L99 _public function_ `TArray<T>::RangedForConstIteratorType end() const`
- L112 _public function_ `template<typename... Args> int32 Emplace(Args&&... InArgs)`
- L122 _public function_ `int32 Add(const T& Value)`
- L132 _public function_ `int32 Add(T&& Value)`
- L142 _public function_ `void Modify(int32 AtIndex, const T& Value)`
- L150 _public function_ `void Modify(int32 AtIndex, T&& Value)`
- L158 _public function_ `void Append(const TArray<T>& Other)`
- L166 _public function_ `void SetNum(SizeType NewNum, EAllowShrinking AllowShrink = UE::Core::Private::AllowShrinkingByDefault<AllocatorType>())`
- L174 _public function_ `void SetNumZeroed(SizeType NewNum, EAllowShrinking AllowShrink = UE::Core::Private::AllowShrinkingByDefault<AllocatorType>())`
- L182 _public function_ `SizeType Num() const`
- L187 _public function_ `const T& Last(SizeType IndexFromEnd = 0) const`
- L194 _public function_ `void AddReferencedObjects(FReferenceCollector& Collector) const requires CIsUObjectType<T>` — If the array contains UObjects, we need to emit references to them directly
- L212 _public function_ `void AddReferencedObjects(FReferenceCollector& Collector) const requires CIsUStructType<T>` — If the array contains USTRUCT types, they might reference UObject types and need to emit references. Defer to the struct here to add required references
- L229 _public function_ `void AddReferencedObjects(FReferenceCollector& Collector) const` — Base case for storage types that don't emit references
- L235 _public function_ `TArray<T> ToArray() const` — Copy the internal state into a new TArray
- L251 _private function_ `void CheckCopyOnWrite()`
- L260 _private function_ `void Duplicate()`
- L294 _private member_ `TRefCountPtr<FState> State = nullptr;`
- L295 _private member_ `FRWLock Lock;`

#### struct `TCopyOnWriteArray::FState`  
`struct FState : public UE::Private::FQueryableRefCountedObject`  
_L289-292_
- inherits: `UE::Private::FQueryableRefCountedObject`
- L291 _public member_ `TArray<T> Arr;`

#### Free symbols / members of external scopes

- L300 _function_ `template<typename... T> void AddArrayReferences(FReferenceCollector& Collector, const T&... Args)` — Variadic helper to call AddReferencedObjects on multiple arrays
