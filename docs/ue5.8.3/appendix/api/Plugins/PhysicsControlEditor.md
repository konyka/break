# Plugins / PhysicsControlEditor

- module root: `Plugins/Animation/PhysicsControl/Source/PhysicsControlEditor`
- headers: 28; symbols: 581
- symbol kinds: class=28, delegate=3, enum=3, enumerator=11, externvar=1, function=55, macro=4, member=179, namespace=1, prototype=276, struct=9, typedef=11
- DynamicallyLoadedModuleNames: 
- PrivateDependencyModuleNames: AdvancedPreviewScene, AnimGraph, AnimGraphRuntime, AnimationCore, AnimationEditMode, AnimationEditor, ApplicationCore, AssetDefinition, BlueprintGraph, Chaos, ComponentVisualizers, Core, CoreUObject, EditorFramework, EditorStyle, Engine, InputCore, Kismet, Persona, PhysicsControl, PhysicsControlUncookedOnly, PinnedCommandList, SkeletonEditor, Slate, SlateCore, ToolMenus, ToolWidgets, UnrealEd
- PublicDependencyModuleNames: Core

### `Plugins/Animation/PhysicsControl/Source/PhysicsControlEditor/Private/AssetDefinition_PhysicsControlAsset.h` (Private)


#### class `UAssetDefinition_PhysicsControlAsset`  
`class UAssetDefinition_PhysicsControlAsset : public UAssetDefinitionDefault`  
_L9-40_
- reflection: `UCLASS()`
- inherits: `UAssetDefinitionDefault`
- L14 _public function_ `virtual FText GetAssetDisplayName() const override` — UAssetDefinition Begin
- L19 _public function_ `virtual FLinearColor GetAssetColor() const override`
- L24 _public function_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override`
- L29 _public function_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override`
- L38 _public prototype_ `virtual EAssetCommandResult OpenAssets(const FAssetOpenArgs& OpenArgs) const override;`

### `Plugins/Animation/PhysicsControl/Source/PhysicsControlEditor/Private/PhysicsControlAssetEditorAnimInstance.h` (Private)


#### class `UPhysicsControlAssetEditorAnimInstance`  
`class UPhysicsControlAssetEditorAnimInstance : public UAnimPreviewInstance`  
_L16-28_
- reflection: `UCLASS(transient, NotBlueprintable)`
- inherits: `UAnimPreviewInstance`
- L20 _private prototype_ `void Grab(FName InBoneName, const FVector& Location, const FRotator& Rotation, bool bRotationConstrained);`
- L21 _private prototype_ `void Ungrab();`
- L22 _private prototype_ `void UpdateHandleTransform(const FTransform& NewTransform);`
- L23 _private prototype_ `void UpdateDriveSettings(bool bLinearSoft, float LinearStiffness, float LinearDamping);`
- L24 _private prototype_ `void CreateSimulationFloor(FBodyInstance* FloorBodyInstance, const FTransform& Transform);`
- L27 _protected prototype_ `virtual FAnimInstanceProxy* CreateAnimInstanceProxy() override;`

### `Plugins/Animation/PhysicsControl/Source/PhysicsControlEditor/Private/PhysicsControlAssetEditorAnimInstanceProxy.h` (Private)


#### struct `FPhysicsControlAssetEditorAnimInstanceProxy`  
`struct FPhysicsControlAssetEditorAnimInstanceProxy : public FAnimPreviewInstanceProxy`  
_L18-58_
- reflection: `USTRUCT()`
- inherits: `FAnimPreviewInstanceProxy`
- desc: Proxy override for this UAnimInstance-derived class
- L23 _public prototype_ `FPhysicsControlAssetEditorAnimInstanceProxy();`
- L25 _public prototype_ `FPhysicsControlAssetEditorAnimInstanceProxy(UAnimInstance* InAnimInstance);`
- L27 _public prototype_ `virtual ~FPhysicsControlAssetEditorAnimInstanceProxy();`
- L29 _public prototype_ `virtual void Initialize(UAnimInstance* InAnimInstance) override;`
- L30 _public prototype_ `virtual FAnimNode_Base* GetCustomRootNode() override;`
- L31 _public prototype_ `virtual void GetCustomNodes(TArray<FAnimNode_Base*>& OutNodes) override;`
- L33 _public prototype_ `virtual void UpdateAnimationNode(const FAnimationUpdateContext& InContext) override;`
- L34 _public prototype_ `virtual bool Evaluate_WithRoot(FPoseContext& Output, FAnimNode_Base* InRootNode) override;`
- L36 _public prototype_ `virtual void AddImpulseAtLocation(FVector Impulse, FVector Location, FName BoneName = NAME_None) override;`
- L38 _public prototype_ `void Grab(FName InBoneName, const FVector& Location, const FRotator& Rotation, bool bRotationConstrained);`
- L39 _public prototype_ `void Ungrab();`
- L40 _public prototype_ `void UpdateHandleTransform(const FTransform& NewTransform);`
- L41 _public prototype_ `void UpdateDriveSettings(bool bLinearSoft, float LinearStiffness, float LinearDamping);`
- L43 _public prototype_ `void CreateSimulationFloor(FBodyInstance* FloorBodyInstance, const FTransform& Transform);`
- L44 _public prototype_ `void DestroySimulationFloor();`
- L47 _private prototype_ `void ConstructNodes();`
- L49 _private member_ `FAnimNode_RigidBody RagdollNode;`
- L50 _private member_ `FAnimNode_ConvertComponentToLocalSpace ComponentToLocalSpace;`
- L51 _private member_ `FPhysicsAssetSolverSettings SolverSettings;`
- L52 _private member_ `FSolverIterations SolverIterations;`
- L54 _private member_ `ImmediatePhysics::FActorHandle* TargetActor;`
- L55 _private member_ `ImmediatePhysics::FActorHandle* HandleActor;`
- L56 _private member_ `ImmediatePhysics::FJointHandle* HandleJoint;`
- L57 _private member_ `ImmediatePhysics::FActorHandle* FloorActor;`

### `Plugins/Animation/PhysicsControl/Source/PhysicsControlEditor/Private/PhysicsControlAssetEditorCommands.h` (Private)


#### class `FPhysicsControlAssetEditorCommands`  
`class FPhysicsControlAssetEditorCommands : public TCommands<FPhysicsControlAssetEditorCommands>`  
_L14-64_
- inherits: `TCommands<FPhysicsControlAssetEditorCommands>`
- L18 _public function_ `FPhysicsControlAssetEditorCommands() : TCommands<FPhysicsControlAssetEditorCommands>( "PhysicsControlAssetEditor", NSLOCTEXT("Contexts", "PhysicsControlAssetEditor", "PhysicsControlAssetEditor"), NAME_None, FAppStyle::GetAppStyleSetName())` — Constructor
- L27 _public member_ `TSharedPtr<FUICommandInfo> Compile;` — See tooltips in cpp for documentation
- L28 _public member_ `TSharedPtr<FUICommandInfo> Simulation;`
- L29 _public member_ `TSharedPtr<FUICommandInfo> SimulationNoGravity;`
- L30 _public member_ `TSharedPtr<FUICommandInfo> SimulationFloorCollision;`
- L33 _public member_ `TSharedPtr<FUICommandInfo> SelectAllBodies;` — Selection commands
- L34 _public member_ `TSharedPtr<FUICommandInfo> SelectSimulatedBodies;`
- L35 _public member_ `TSharedPtr<FUICommandInfo> SelectKinematicBodies;`
- L38 _public member_ `TSharedPtr<FUICommandInfo> MeshRenderingMode_Solid;` — Rendering commands
- L39 _public member_ `TSharedPtr<FUICommandInfo> MeshRenderingMode_Wireframe;`
- L40 _public member_ `TSharedPtr<FUICommandInfo> MeshRenderingMode_None;`
- L41 _public member_ `TSharedPtr<FUICommandInfo> CollisionRenderingMode_Solid;`
- L42 _public member_ `TSharedPtr<FUICommandInfo> CollisionRenderingMode_Wireframe;`
- L43 _public member_ `TSharedPtr<FUICommandInfo> CollisionRenderingMode_SolidWireframe;`
- L44 _public member_ `TSharedPtr<FUICommandInfo> CollisionRenderingMode_None;`
- L45 _public member_ `TSharedPtr<FUICommandInfo> ConstraintRenderingMode_None;`
- L46 _public member_ `TSharedPtr<FUICommandInfo> ConstraintRenderingMode_AllPositions;`
- L47 _public member_ `TSharedPtr<FUICommandInfo> ConstraintRenderingMode_AllLimits;`
- L49 _public member_ `TSharedPtr<FUICommandInfo> MeshRenderingMode_Simulation_Solid;`
- L50 _public member_ `TSharedPtr<FUICommandInfo> MeshRenderingMode_Simulation_Wireframe;`
- L51 _public member_ `TSharedPtr<FUICommandInfo> MeshRenderingMode_Simulation_None;`
- L52 _public member_ `TSharedPtr<FUICommandInfo> CollisionRenderingMode_Simulation_Solid;`
- L53 _public member_ `TSharedPtr<FUICommandInfo> CollisionRenderingMode_Simulation_Wireframe;`
- L54 _public member_ `TSharedPtr<FUICommandInfo> CollisionRenderingMode_Simulation_SolidWireframe;`
- L55 _public member_ `TSharedPtr<FUICommandInfo> CollisionRenderingMode_Simulation_None;`
- L56 _public member_ `TSharedPtr<FUICommandInfo> ConstraintRenderingMode_Simulation_None;`
- L57 _public member_ `TSharedPtr<FUICommandInfo> ConstraintRenderingMode_Simulation_AllPositions;`
- L58 _public member_ `TSharedPtr<FUICommandInfo> ConstraintRenderingMode_Simulation_AllLimits;`
- L60 _public member_ `TSharedPtr<FUICommandInfo> DrawViolatedLimits;`
- L63 _public prototype_ `virtual void RegisterCommands() override;` — Initialize commands

### `Plugins/Animation/PhysicsControl/Source/PhysicsControlEditor/Private/PhysicsControlAssetEditorData.h` (Private)


#### class `FPhysicsControlAssetEditorData`  
`class FPhysicsControlAssetEditorData`  
_L19-137_
- desc: Helper/container for data used by the Physics Control Asset Editor
- L22 _public prototype_ `FPhysicsControlAssetEditorData();`
- L46 _public prototype_ `void Initialize(const TSharedRef<IPersonaPreviewScene>& InPreviewScene);` — Initializes members
- L49 _public prototype_ `void CachePreviewMesh();` — Caches a preview mesh. Sets us to a default mesh if none is set yet (or if an older one got deleted)
- L52 _public prototype_ `EPhysicsAssetEditorMeshViewMode GetCurrentMeshViewMode(bool bSimulation);` — Accessor for mesh view mode, allows access for simulation and non-simulation modes
- L55 _public prototype_ `EPhysicsAssetEditorCollisionViewMode GetCurrentCollisionViewMode(bool bSimulation);` — Accessor for collision view mode, allows access for simulation and non-simulation modes
- L58 _public prototype_ `EPhysicsAssetEditorConstraintViewMode GetCurrentConstraintViewMode(bool bSimulation);` — Accessor for constraint view mode, allows access for simulation and non-simulation modes
- L61 _public prototype_ `void AddReferencedObjects(FReferenceCollector& Collector);` — Prevents GC from collecting our objects
- L63 _public prototype_ `void EnableSimulation(bool bEnableSimulation);`
- L66 _public prototype_ `void ForceDisableSimulation();` — Force simulation off for all bodies, regardless of physics type
- L69 _public prototype_ `void ToggleSimulation();` — Toggle simulation on and off
- L72 _public prototype_ `void RecreateControlsAndModifiers();` — Destroys all existing controls modifiers and then recreates them from the control asset
- L75 _public prototype_ `void BroadcastPreviewChanged();` — broadcast a change in the preview
- L78 _public prototype_ `void BroadcastSelectionChanged();` — broadcast a selection change ( if bSuspendSelectionBroadcast is false )
- L81 _public prototype_ `void HitBone(int32 BodyIndex, EAggCollisionShape::Type PrimType, int32 PrimIndex, bool bGroupSelect);` — Handle clicking on a body
- L84 _public prototype_ `FSelection* GetSelectedBody();` — Selection
- L85 _public prototype_ `void ClearSelectedBody();`
- L86 _public prototype_ `void SetSelectedBody(const FSelection& Body, bool bSelected);`
- L87 _public prototype_ `void SetSelectedBodies(const TArray<FSelection>& Bodies, bool bSelected);`
- L88 _public prototype_ `bool IsBodySelected(const FSelection& Body) const;`
- L92 _public member_ `TObjectPtr<UPhysicsControlAsset> PhysicsControlAsset;` — The PhysicsControlAsset being inspected
- L95 _public member_ `TObjectPtr<UPhysicsControlAssetEditorSkeletalMeshComponent> EditorSkelComp;` — Skeletal mesh component specialized for this asset editor
- L98 _public member_ `TObjectPtr<UPhysicsControlComponent> PhysicsControlComponent;` — The physics control component used for testing/simulating on the character
- L104 _public member_ `TWeakPtr<IPersonaPreviewScene> PreviewScene;` — Preview scene
- L107 _public member_ `TObjectPtr<UPhysicsAssetEditorOptions> EditorOptions;` — Editor options
- L110 _public member_ `TObjectPtr<UPhysicsControlAssetEditorPhysicsHandleComponent> MouseHandle;` — Helps define how the asset behaves given user interaction in simulation mode
- L113 _public prototype_ `DECLARE_EVENT(FPhysicsControlAssetEditorSharedData, FPreviewChanged);` — Callback for triggering a refresh of the preview viewport
- L114 _public member_ `FPreviewChanged PreviewChangedEvent;`
- L117 _public prototype_ `DECLARE_EVENT_OneParam(FPhysicsAssetEditorSharedData, FSelectionChanged, const TArray<FSelection>&);` — Callback for handling selection changes
- L118 _public member_ `FSelectionChanged SelectionChangedEvent;`
- L120 _public member_ `TArray<FSelection> SelectedBodies;`
- L123 _public member_ `bool bRunningSimulation;` — Misc toggles
- L124 _public member_ `bool bNoGravitySimulation;`
- L127 _public member_ `bool bManipulating;` — Manipulation (rotate, translate, scale)
- L130 _public member_ `bool bSuspendSelectionBroadcast;` — when true, we don't broadcast every selection change - allows for bulk changes without so much overhead
- L133 _public member_ `int32 InsideSelChange;` — Used to prevent recursion with tree hierarchy ... needs to be rewritten!
- L136 _public member_ `const FTransform ResetTM;` — Where we put the component back to after simulating. It will just be identity.

#### struct `FPhysicsControlAssetEditorData::FSelection`  
`struct FSelection`  
_L25-43_
- desc: Encapsulates a selected set of bodies
- L27 _public member_ `int32 Index;`
- L28 _public member_ `EAggCollisionShape::Type PrimitiveType;`
- L29 _public member_ `int32 PrimitiveIndex;`
- L30 _public member_ `FTransform WidgetTM;`
- L31 _public member_ `FTransform ManipulateTM;`
- L33 _public function_ `FSelection(int32 GivenBodyIndex, EAggCollisionShape::Type GivenPrimitiveType, int32 GivenPrimitiveIndex) : Index(GivenBodyIndex), PrimitiveType(GivenPrimitiveType), PrimitiveIndex(GivenPrimitiveIndex), WidgetTM(FTransform::Identity), ManipulateTM(FTransform::Identity)`
- L39 _public function_ `bool operator==(const FSelection& rhs) const`

#### Free symbols / members of external scopes

- L113 _delegate_ `DECLARE_EVENT(FPhysicsControlAssetEditorSharedData, FPreviewChanged);` — Callback for triggering a refresh of the preview viewport
- L117 _delegate_ `DECLARE_EVENT_OneParam(FPhysicsAssetEditorSharedData, FSelectionChanged, const TArray<FSelection>&);` — Callback for handling selection changes

### `Plugins/Animation/PhysicsControl/Source/PhysicsControlEditor/Private/PhysicsControlAssetEditorHitProxies.h` (Private)


#### struct `HPhysicsControlAssetEditorEdBoneProxy`  
`struct HPhysicsControlAssetEditorEdBoneProxy : public HHitProxy`  
_L14-37_
- inherits: `HHitProxy`
- L16 _public prototype_ `DECLARE_HIT_PROXY();`
- L18 _public member_ `int32 BodyIndex;`
- L19 _public member_ `EAggCollisionShape::Type PrimType;`
- L20 _public member_ `int32 PrimIndex;`
- L22 _public function_ `HPhysicsControlAssetEditorEdBoneProxy(int32 InBodyIndex, EAggCollisionShape::Type InPrimType, int32 InPrimIndex) : HHitProxy(HPP_World) , BodyIndex(InBodyIndex) , PrimType(InPrimType) , PrimIndex(InPrimIndex)`
- L28 _public function_ `virtual EMouseCursor::Type GetMouseCursor()`
- L33 _public function_ `virtual bool AlwaysAllowsTranslucentPrimitives() const override`

#### struct `HPhysicsControlAssetEditorEdBoneNameProxy`  
`struct HPhysicsControlAssetEditorEdBoneNameProxy : public HHitProxy`  
_L39-53_
- inherits: `HHitProxy`
- L41 _public prototype_ `DECLARE_HIT_PROXY();`
- L43 _public member_ `int32 BoneIndex;`
- L45 _public function_ `HPhysicsControlAssetEditorEdBoneNameProxy(int32 InBoneIndex) : HHitProxy(HPP_Foreground) , BoneIndex(InBoneIndex)`
- L49 _public function_ `virtual bool AlwaysAllowsTranslucentPrimitives() const override`

### `Plugins/Animation/PhysicsControl/Source/PhysicsControlEditor/Private/PhysicsControlAssetEditorPhysicsHandleComponent.h` (Private)


#### class `UPhysicsControlAssetEditorPhysicsHandleComponent`  
`class UPhysicsControlAssetEditorPhysicsHandleComponent : public UPhysicsHandleComponent`  
_L15-36_
- reflection: `UCLASS()`
- inherits: `UPhysicsHandleComponent`
- desc: Extend the Physics Handle for PhAt. This adds support for manipulating the physics if it is running in a RigidBody AnimNode (which is always is with Chaos at the moment).
- L19 _private member_ `bool bAnimInstanceMode;`
- L22 _public prototype_ `void SetAnimInstanceMode(bool bInAnimInstanceMode);`
- L24 _public prototype_ `virtual void ReleaseComponent() override;`
- L26 _public prototype_ `void AddImpulseAtLocation( UPhysicsControlAssetEditorSkeletalMeshComponent* PhysicsControlAssetEditorSkeletalMeshComponent, FVector Impulse, FVector Location, FName BoneName);`
- L31 _protected prototype_ `virtual void UpdateHandleTransform(const FTransform& NewTransform) override;`
- L32 _protected prototype_ `virtual void UpdateDriveSettings() override;`
- L33 _protected prototype_ `virtual void GrabComponentImp( class UPrimitiveComponent* Component, FName InBoneName, const FVector& Location, const FRotator& Rotation, bool bRotationConstrained) override;`

### `Plugins/Animation/PhysicsControl/Source/PhysicsControlEditor/Private/PhysicsControlAssetEditorSkeletalMeshComponent.h` (Private)


#### class `UPhysicsControlAssetEditorSkeletalMeshComponent`  
`class UPhysicsControlAssetEditorSkeletalMeshComponent : public UDebugSkelMeshComponent`  
_L20-88_
- reflection: `UCLASS(Hidden)`
- inherits: `UDebugSkelMeshComponent`
- desc: This is an internal component used only by the Physics Control Asset editor preview scene. It is marked Hidden so it does not appear in editor class pickers (e.g. the component class dropdown), as it is not intended to be selected or used outside of that editor.
- L25 _private member_ `TSharedPtr<FPhysicsControlAssetEditorData> EditorData;` — Data and methods shared across multiple classes
- L29 _private member_ `FColor BoneUnselectedColor;`
- L30 _private member_ `FColor NoCollisionColor;`
- L31 _private member_ `FColor FixedColor;`
- L32 _private member_ `FColor ConstraintBone1Color;`
- L33 _private member_ `FColor ConstraintBone2Color;`
- L34 _private member_ `FColor HierarchyDrawColor;`
- L35 _private member_ `FColor AnimSkelDrawColor;`
- L36 _private member_ `float COMRenderSize;`
- L37 _private member_ `float InfluenceLineLength;`
- L38 _private member_ `FColor InfluenceLineColor;`
- L43 _private member_ `TObjectPtr<UMaterialInstanceDynamic> ElemSelectedMaterial;` — `UPROPERTY(transient)`
- L45 _private member_ `TObjectPtr<UMaterialInstanceDynamic> BoneUnselectedMaterial;` — `UPROPERTY(transient)`
- L47 _private member_ `TObjectPtr<UMaterialInstanceDynamic> BoneNoCollisionMaterial;` — `UPROPERTY(transient)`
- L50 _private member_ `TObjectPtr<UMaterialInterface> BoneMaterialHit;` — `UPROPERTY(transient)`
- L53 _private member_ `TArray<FTransform> AnimationSpaceBases;` — Mesh-space matrices showing state of just animation (ie before physics) - useful for debugging!
- L56 _private prototype_ `virtual TObjectPtr<UAnimPreviewInstance> CreatePreviewInstance() override;` — UDebugSkelMeshComponent interface
- L59 _private prototype_ `virtual FPrimitiveSceneProxy* CreateSceneProxy() override;` — UPrimitiveComponent interface
- L60 _private prototype_ `virtual void AddImpulseAtLocation(FVector Impulse, FVector Location, FName BoneName = NAME_None) override;`
- L61 _private prototype_ `virtual bool ShouldCreatePhysicsState() const override;`
- L64 _private prototype_ `virtual void RefreshBoneTransforms(FActorComponentTickFunction* TickFunction = nullptr) override;` — USkinnedMeshComponent interface
- L67 _private prototype_ `void DebugDraw(const FSceneView* View, FPrimitiveDrawInterface* PDI);` — Debug drawing
- L70 _private prototype_ `FTransform GetPrimitiveTransform(const FTransform& BoneTM, const int32 BodyIndex, const EAggCollisionShape::Type PrimType, const int32 PrimIndex, const float Scale) const;` — Accessors/helper methods
- L71 _private prototype_ `FColor GetPrimitiveColor(const int32 BodyIndex, const EAggCollisionShape::Type PrimitiveType, const int32 PrimitiveIndex) const;`
- L72 _private prototype_ `UMaterialInterface* GetPrimitiveMaterial(const int32 BodyIndex, const EAggCollisionShape::Type PrimitiveType, const int32 PrimitiveIndex) const;`
- L75 _private prototype_ `void Grab(FName InBoneName, const FVector& Location, const FRotator& Rotation, bool bRotationConstrained);` — Manipulator methods
- L76 _private prototype_ `void Ungrab();`
- L77 _private prototype_ `void UpdateHandleTransform(const FTransform& NewTransform);`
- L78 _private prototype_ `void UpdateDriveSettings(bool bLinearSoft, float LinearStiffness, float LinearDamping);`
- L81 _private prototype_ `void CreateSimulationFloor(FBodyInstance* FloorBodyInstance, const FTransform& Transform);` — Sim setup
- L84 _public function_ `virtual bool CanOverrideCollisionProfile() const override`
- L87 _private prototype_ `void UpdateSkinnedLevelSets();`

### `Plugins/Animation/PhysicsControl/Source/PhysicsControlEditor/Private/PhysicsControlAssetEditorSkeletonTreeBuilder.h` (Private)


#### class `FPhysicsControlAssetEditorSkeletonTreeBuilder`  
`class FPhysicsControlAssetEditorSkeletonTreeBuilder : public FSkeletonTreeBuilder`  
_L10-34_
- inherits: `FSkeletonTreeBuilder`
- L13 _public prototype_ `FPhysicsControlAssetEditorSkeletonTreeBuilder( UPhysicsAsset* InPhysicsAsset, const FSkeletonTreeBuilderArgs& InSkeletonTreeBuilderArgs = FSkeletonTreeBuilderArgs(true, false, true, false));`
- L18 _public prototype_ `virtual void Build(FSkeletonTreeBuilderOutput& Output) override;` — ISkeletonTreeBuilder interface
- L19 _public prototype_ `virtual ESkeletonTreeFilterResult FilterItem(const FSkeletonTreeFilterArgs& InArgs, const TSharedPtr<class ISkeletonTreeItem>& InItem) override;`
- L22 _public member_ `bool bShowBodies;` — Flags used for filtering
- L23 _public member_ `bool bShowKinematicBodies;`
- L24 _public member_ `bool bShowSimulatedBodies;`
- L25 _public member_ `bool bShowPrimitives;`
- L29 _private prototype_ `void AddBodies(FSkeletonTreeBuilderOutput& Output);` — Add bodies & their shapes to the tree
- L33 _private member_ `UPhysicsAsset* PhysicsAsset;` — The physics asset we use to populate the tree

### `Plugins/Animation/PhysicsControl/Source/PhysicsControlEditor/Private/PhysicsControlAssetEditorTabSummoners.h` (Private)


#### struct `FPhysicsControlAssetEditorSetupTabSummoner`  
`struct FPhysicsControlAssetEditorSetupTabSummoner : public FWorkflowTabFactory`  
_L10-24_
- inherits: `FWorkflowTabFactory`
- L13 _public member_ `static FName TabName;`
- L15 _public prototype_ `FPhysicsControlAssetEditorSetupTabSummoner( TSharedPtr<FAssetEditorToolkit> InHostingApp, UPhysicsControlAsset* InPhysicsControlAsset);`
- L19 _public prototype_ `virtual TSharedRef<SWidget> CreateTabBody(const FWorkflowTabSpawnInfo& Info) const override;` — FWorkflowTabFactory interface
- L20 _public prototype_ `virtual TSharedPtr<SToolTip> CreateTabToolTipWidget(const FWorkflowTabSpawnInfo& Info) const override;`
- L23 _public member_ `TWeakObjectPtr<UPhysicsControlAsset> PhysicsControlAsset;` — Reference to our Physics Asset

#### struct `FPhysicsControlAssetEditorProfileTabSummoner`  
`struct FPhysicsControlAssetEditorProfileTabSummoner : public FWorkflowTabFactory`  
_L27-41_
- inherits: `FWorkflowTabFactory`
- L30 _public member_ `static FName TabName;`
- L32 _public prototype_ `FPhysicsControlAssetEditorProfileTabSummoner( TSharedPtr<FAssetEditorToolkit> InHostingApp, UPhysicsControlAsset* InPhysicsControlAsset);`
- L36 _public prototype_ `virtual TSharedRef<SWidget> CreateTabBody(const FWorkflowTabSpawnInfo& Info) const override;` — FWorkflowTabFactory interface
- L37 _public prototype_ `virtual TSharedPtr<SToolTip> CreateTabToolTipWidget(const FWorkflowTabSpawnInfo& Info) const override;`
- L40 _public member_ `TWeakObjectPtr<UPhysicsControlAsset> PhysicsControlAsset;` — Reference to our Physics Asset

#### struct `FPhysicsControlAssetEditorPreviewTabSummoner`  
`struct FPhysicsControlAssetEditorPreviewTabSummoner : public FWorkflowTabFactory`  
_L44-58_
- inherits: `FWorkflowTabFactory`
- L47 _public member_ `static FName TabName;`
- L49 _public prototype_ `FPhysicsControlAssetEditorPreviewTabSummoner( TSharedPtr<FAssetEditorToolkit> InHostingApp, UPhysicsControlAsset* InPhysicsControlAsset);`
- L53 _public prototype_ `virtual TSharedRef<SWidget> CreateTabBody(const FWorkflowTabSpawnInfo& Info) const override;` — FWorkflowTabFactory interface
- L54 _public prototype_ `virtual TSharedPtr<SToolTip> CreateTabToolTipWidget(const FWorkflowTabSpawnInfo& Info) const override;`
- L57 _public member_ `TWeakObjectPtr<UPhysicsControlAsset> PhysicsControlAsset;` — Reference to our Physics Asset

#### struct `FPhysicsControlAssetEditorControlSetsTabSummoner`  
`struct FPhysicsControlAssetEditorControlSetsTabSummoner : public FWorkflowTabFactory`  
_L61-75_
- inherits: `FWorkflowTabFactory`
- L64 _public member_ `static FName TabName;`
- L66 _public prototype_ `FPhysicsControlAssetEditorControlSetsTabSummoner( TSharedPtr<FAssetEditorToolkit> InHostingApp, UPhysicsControlAsset* InPhysicsControlAsset);`
- L70 _public prototype_ `virtual TSharedRef<SWidget> CreateTabBody(const FWorkflowTabSpawnInfo& Info) const override;` — FWorkflowTabFactory interface
- L71 _public prototype_ `virtual TSharedPtr<SToolTip> CreateTabToolTipWidget(const FWorkflowTabSpawnInfo& Info) const override;`
- L74 _public member_ `TWeakObjectPtr<UPhysicsControlAsset> PhysicsControlAsset;` — Reference to our Physics Asset

#### struct `FPhysicsControlAssetEditorBodyModifierSetsTabSummoner`  
`struct FPhysicsControlAssetEditorBodyModifierSetsTabSummoner : public FWorkflowTabFactory`  
_L78-92_
- inherits: `FWorkflowTabFactory`
- L81 _public member_ `static FName TabName;`
- L83 _public prototype_ `FPhysicsControlAssetEditorBodyModifierSetsTabSummoner( TSharedPtr<FAssetEditorToolkit> InHostingApp, UPhysicsControlAsset* InPhysicsControlAsset);`
- L87 _public prototype_ `virtual TSharedRef<SWidget> CreateTabBody(const FWorkflowTabSpawnInfo& Info) const override;` — FWorkflowTabFactory interface
- L88 _public prototype_ `virtual TSharedPtr<SToolTip> CreateTabToolTipWidget(const FWorkflowTabSpawnInfo& Info) const override;`
- L91 _public member_ `TWeakObjectPtr<UPhysicsControlAsset> PhysicsControlAsset;` — Reference to our Physics Asset

### `Plugins/Animation/PhysicsControl/Source/PhysicsControlEditor/Private/PhysicsControlAssetEditorToolMenuContext.h` (Private)


#### class `UPhysicsControlAssetEditorToolMenuContext`  
`class UPhysicsControlAssetEditorToolMenuContext : public UObject`  
_L11-17_
- reflection: `UCLASS()`
- inherits: `UObject`
- L16 _public member_ `TWeakPtr<FPhysicsControlAssetEditor> PhysicsControlAssetEditor;`

### `Plugins/Animation/PhysicsControl/Source/PhysicsControlEditor/Private/PhysicsControlAssetFactory.h` (Private)


#### class `UPhysicsControlAssetFactory`  
`class UPhysicsControlAssetFactory : public UFactory`  
_L10-17_
- reflection: `UCLASS()`
- inherits: `UFactory`
- L14 _public prototype_ `UPhysicsControlAssetFactory(const FObjectInitializer& ObjectInitializer);`
- L15 _public prototype_ `UObject* FactoryCreateNew( UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn);`

### `Plugins/Animation/PhysicsControl/Source/PhysicsControlEditor/Private/PhysicsControlAssetInfoDetailsCustomization.h` (Private)


#### class `FPhysicsControlAssetInfoDetailsCustomization`  
`class FPhysicsControlAssetInfoDetailsCustomization : public IDetailCustomization`  
_L17-51_
- inherits: `IDetailCustomization`
- L27 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance( TWeakPtr<FPhysicsControlAssetEditor> InPhysicsControlAssetEditor, EInfoType InfoType);` — Makes a new instance of this detail layout class for a specific detail view requesting it
- L30 _public function_ `FPhysicsControlAssetInfoDetailsCustomization( TWeakPtr<FPhysicsControlAssetEditor> InPhysicsControlAssetEditor, EInfoType InInfoType) : PhysicsControlAssetEditor(InPhysicsControlAssetEditor) , InfoType(InInfoType)`
- L38 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailLayout) override;`
- L39 _public prototype_ `virtual void CustomizeDetails(const TSharedPtr<IDetailLayoutBuilder>& InDetailBuilder) override;`
- L43 _protected prototype_ `void OnControlAssetCompiled(bool bProfileListChanged);`
- L46 _protected member_ `TWeakPtr<FPhysicsControlAssetEditor> PhysicsControlAssetEditor;`
- L48 _protected member_ `TWeakPtr<IDetailLayoutBuilder> DetailLayoutBuilderWeak;`
- L50 _protected member_ `EInfoType InfoType;`

#### enum `FPhysicsControlAssetInfoDetailsCustomization::EInfoType`  
`enum class EInfoType : uint8`  
_L20-24_
- L22 _public enumerator_ `Controls`
- L23 _public enumerator_ `BodyModifiers`

### `Plugins/Animation/PhysicsControl/Source/PhysicsControlEditor/Private/PhysicsControlAssetPreviewDetailsCustomization.h` (Private)


#### class `FPhysicsControlAssetPreviewDetailsCustomization`  
`class FPhysicsControlAssetPreviewDetailsCustomization : public IDetailCustomization`  
_L18-40_
- inherits: `IDetailCustomization`
- L22 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance(TWeakPtr<FPhysicsControlAssetEditor> InPhysicsControlAssetEditor);` — Makes a new instance of this detail layout class for a specific detail view requesting it
- L24 _public prototype_ `FPhysicsControlAssetPreviewDetailsCustomization(TWeakPtr<FPhysicsControlAssetEditor> InPhysicsControlAssetEditor);`
- L27 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailLayout) override;`
- L28 _public prototype_ `virtual void CustomizeDetails(const TSharedPtr<IDetailLayoutBuilder>& InDetailBuilder) override;`
- L32 _protected prototype_ `FReply InvokeControlProfile(FName ProfileName);`
- L34 _protected prototype_ `void OnControlAssetCompiled(bool bProfileListChanged);`
- L37 _private member_ `TWeakPtr<FPhysicsControlAssetEditor> PhysicsControlAssetEditor;`
- L39 _private member_ `TWeakPtr<IDetailLayoutBuilder> DetailLayoutBuilderWeak;`

### `Plugins/Animation/PhysicsControl/Source/PhysicsControlEditor/Private/PhysicsControlAssetProfileDetailsCustomization.h` (Private)


#### class `FPhysicsControlAssetProfileDetailsCustomization`  
`class FPhysicsControlAssetProfileDetailsCustomization : public IDetailCustomization`  
_L22-47_
- inherits: `IDetailCustomization`
- L26 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance(TWeakPtr<FPhysicsControlAssetEditor> InPhysicsControlAssetEditor);` — Makes a new instance of this detail layout class for a specific detail view requesting it
- L28 _public function_ `FPhysicsControlAssetProfileDetailsCustomization(TWeakPtr<FPhysicsControlAssetEditor> InPhysicsControlAssetEditor) : PhysicsControlAssetEditor(InPhysicsControlAssetEditor)`
- L33 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailLayout) override;`
- L34 _public prototype_ `virtual void CustomizeDetails(const TSharedPtr<IDetailLayoutBuilder>& InDetailBuilder) override;`
- L38 _protected prototype_ `void OnProfilesChanged();`
- L39 _protected prototype_ `void OnProfileDetailsChanged();`
- L42 _protected prototype_ `FReply InvokeControlProfile(FName ProfileName);`
- L44 _protected member_ `TWeakPtr<FPhysicsControlAssetEditor> PhysicsControlAssetEditor;`
- L46 _protected member_ `TWeakPtr<IDetailLayoutBuilder> DetailLayoutBuilderWeak;`

### `Plugins/Animation/PhysicsControl/Source/PhysicsControlEditor/Private/PhysicsControlAssetSetupDetailsCustomization.h` (Private)


#### class `FPhysicsControlAssetSetupDetailsCustomization`  
`class FPhysicsControlAssetSetupDetailsCustomization : public IDetailCustomization`  
_L17-36_
- inherits: `IDetailCustomization`
- L21 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance(TWeakPtr<FPhysicsControlAssetEditor> InPhysicsControlAssetEditor);` — Makes a new instance of this detail layout class for a specific detail view requesting it
- L23 _public function_ `FPhysicsControlAssetSetupDetailsCustomization(TWeakPtr<FPhysicsControlAssetEditor> InPhysicsControlAssetEditor) : PhysicsControlAssetEditor(InPhysicsControlAssetEditor)`
- L28 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailLayout) override;` — IDetailCustomization interface
- L31 _protected prototype_ `void OnSetupChanged();`
- L32 _protected prototype_ `void OnSetupDetailsChanged();`
- L35 _protected member_ `TWeakPtr<FPhysicsControlAssetEditor> PhysicsControlAssetEditor;`

### `Plugins/Animation/PhysicsControl/Source/PhysicsControlEditor/Private/PhysicsControlComponentVisualizer.h` (Private)


#### class `FPhysicsControlComponentVisualizer`  
`class FPhysicsControlComponentVisualizer : public FComponentVisualizer`  
_L8-15_
- inherits: `FComponentVisualizer`
- L11 _private prototype_ `virtual void DrawVisualization( const UActorComponent* Component, const FSceneView* View, FPrimitiveDrawInterface* PDI) override;`

#### Free symbols / members of external scopes

- L6 _macro_ `#define UE_API PHYSICSCONTROLEDITOR_API`

### `Plugins/Animation/PhysicsControl/Source/PhysicsControlEditor/Private/SkeletonTreePhysicsControlBodyItem.h` (Private)


#### class `FSkeletonTreePhysicsControlBodyItem`  
`class FSkeletonTreePhysicsControlBodyItem : public FSkeletonTreePhysicsControlItem`  
_L9-46_
- inherits: `FSkeletonTreePhysicsControlItem`
- L12 _public prototype_ `SKELETON_TREE_ITEM_TYPE(FSkeletonTreePhysicsControlBodyItem, FSkeletonTreePhysicsControlItem);`
- L14 _public prototype_ `FSkeletonTreePhysicsControlBodyItem(class USkeletalBodySetup* InBodySetup, int32 InBodySetupIndex, const FName& InBoneName, bool bInHasBodySetup, bool bInHasShapes, class UPhysicsAsset* const InPhysicsAsset, const TSharedRef<class ISkeletonTree>& InSkeletonTree);`
- L16 _public prototype_ `virtual UObject* GetObject() const override;`
- L19 _public function_ `int32 GetBodySetupIndex() const` — Get the index of the body setup in the physics asset
- L22 _public prototype_ `virtual void OnToggleItemDisplayed(ECheckBoxState InCheckboxState) override;` — UI Callbacks
- L23 _public prototype_ `virtual ECheckBoxState IsItemDisplayed() const override;`
- L27 _private prototype_ `virtual const FSlateBrush* GetBrush() const override;` — Gets the icon to display for this body
- L30 _private prototype_ `virtual FSlateColor GetTextColor() const override;` — Gets the color to display the item's text
- L33 _private prototype_ `virtual FText GetNameColumnToolTip() const override;` — Gets the tool tip to display on hovering over the item's name
- L36 _private member_ `USkeletalBodySetup* BodySetup;` — The body setup we are representing
- L39 _private member_ `int32 BodySetupIndex;` — The index of the body setup in the physics asset
- L42 _private member_ `bool bHasBodySetup;` — Whether there is a body set up for this bone
- L45 _private member_ `bool bHasShapes;` — Whether this body has shapes

### `Plugins/Animation/PhysicsControl/Source/PhysicsControlEditor/Private/SkeletonTreePhysicsControlItem.h` (Private)


#### class `FSkeletonTreePhysicsControlItem`  
`class FSkeletonTreePhysicsControlItem : public FSkeletonTreeItem`  
_L13-48_
- inherits: `FSkeletonTreeItem`
- L16 _public prototype_ `SKELETON_TREE_ITEM_TYPE(FSkeletonTreePhysicsControlItem, FSkeletonTreeItem);`
- L18 _public prototype_ `FSkeletonTreePhysicsControlItem(class UPhysicsAsset* const InPhysicsAsset, const TSharedRef<class ISkeletonTree>& InSkeletonTree);`
- L21 _public prototype_ `virtual void GenerateWidgetForNameColumn(TSharedPtr< SHorizontalBox > Box, const TAttribute<FText>& FilterText, FIsSelected InIsSelected) override;` — ISkeletonTreeItem interface
- L22 _public prototype_ `virtual TSharedRef< SWidget > GenerateWidgetForDataColumn(const FName& DataColumnName, FIsSelected InIsSelected) override;`
- L23 _public function_ `virtual FName GetRowItemName() const override`
- L26 _public prototype_ `virtual void OnToggleItemDisplayed(ECheckBoxState InCheckboxState) = 0;` — UI Callbacks
- L27 _public prototype_ `virtual ECheckBoxState IsItemDisplayed() const = 0;`
- L31 _private prototype_ `virtual const FSlateBrush* GetBrush() const = 0;` — Gets the icon to display for this body
- L34 _private prototype_ `virtual FSlateColor GetTextColor() const = 0;` — Gets the color to display the item's text
- L37 _private prototype_ `virtual FText GetNameColumnToolTip() const = 0;` — Gets the tool tip to display on hovering over the item's name
- L41 _protected prototype_ `struct FPhysicsAssetRenderSettings* GetRenderSettings() const;` — Gets the physics asset render settings for this physics item
- L44 _protected member_ `uint32 PhysicsAssetPathNameHash;` — Unique ID of the physics asset for this physics item
- L47 _protected member_ `FName DisplayName;` — The name of the item in the tree

### `Plugins/Animation/PhysicsControl/Source/PhysicsControlEditor/Private/SkeletonTreePhysicsControlShapeItem.h` (Private)


#### class `FSkeletonTreePhysicsControlShapeItem`  
`class FSkeletonTreePhysicsControlShapeItem : public FSkeletonTreeItem`  
_L16-73_
- inherits: `FSkeletonTreeItem`
- L19 _public prototype_ `SKELETON_TREE_ITEM_TYPE(FSkeletonTreePhysicsControlShapeItem, FSkeletonTreeItem);`
- L21 _public prototype_ `FSkeletonTreePhysicsControlShapeItem(USkeletalBodySetup* InBodySetup, const FName& InBoneName, int32 InBodySetupIndex, EAggCollisionShape::Type InShapeType, int32 InShapeIndex, const TSharedRef<class ISkeletonTree>& InSkeletonTree);`
- L24 _public prototype_ `virtual void GenerateWidgetForNameColumn(TSharedPtr< SHorizontalBox > Box, const TAttribute<FText>& FilterText, FIsSelected InIsSelected) override;` — ISkeletonTreeItem interface
- L25 _public prototype_ `virtual TSharedRef< SWidget > GenerateWidgetForDataColumn(const FName& DataColumnName, FIsSelected InIsSelected) override;`
- L26 _public prototype_ `virtual FName GetRowItemName() const override;`
- L27 _public prototype_ `virtual UObject* GetObject() const override;`
- L28 _public prototype_ `virtual bool CanRenameItem() const override;`
- L29 _public prototype_ `virtual void RequestRename() override;`
- L30 _public prototype_ `virtual void OnItemDoubleClicked() override;`
- L33 _public function_ `int32 GetBodySetupIndex() const` — Get the index of the body setup in the physics asset
- L36 _public function_ `EAggCollisionShape::Type GetShapeType() const` — Get the shape type of this item
- L39 _public function_ `int32 GetShapeIndex() const` — Get the index of the shape in the physics assets aggregate geom
- L43 _private prototype_ `FText GetNameAsText() const;` — Get the text to display for this item
- L46 _private prototype_ `FString GetNameAsString() const;` — Get the text to display for this item
- L49 _private prototype_ `void HandleTextCommitted(const FText& InText, ETextCommit::Type InCommitType);` — Handle the shape being renamed
- L53 _private prototype_ `DECLARE_DELEGATE(FOnRenameRequested);` — Delegate for when the context menu requests a rename
- L54 _private member_ `FOnRenameRequested OnRenameRequested;`
- L57 _private member_ `USkeletalBodySetup* BodySetup;` — The body setup we are representing part of
- L60 _private member_ `FName DefaultLabel;` — The label we display in the tree
- L63 _private member_ `int32 BodySetupIndex;` — The index of the body setup in the physics asset
- L66 _private member_ `EAggCollisionShape::Type ShapeType;` — The kind of shape we represent
- L69 _private member_ `int32 ShapeIndex;` — The index into the relevant body setup array for this shape
- L72 _private member_ `const FSlateBrush* ShapeBrush;` — The brush to use for this shape

#### Free symbols / members of external scopes

- L53 _delegate_ `DECLARE_DELEGATE(FOnRenameRequested);` — Delegate for when the context menu requests a rename

### `Plugins/Animation/PhysicsControl/Source/PhysicsControlEditor/Public/OperatorViewer/OperatorTreeElements.h` (Public)


#### class `OperatorTreeItem`  
`class OperatorTreeItem`  
_L22-60_
- L26 _public prototype_ `virtual ~OperatorTreeItem() = default;`
- L38 _public prototype_ `virtual FText Name() const = 0;`
- L39 _public function_ `virtual FText Description() const`
- L41 _public prototype_ `virtual TSharedRef<ITableRow> GenerateRow(const TSharedRef<STableViewBase>& OwnerTable) const = 0;`
- L42 _public prototype_ `virtual FReply OnDoubleClick();`
- L43 _public function_ `virtual bool MatchesFilterText(const TArray<TArray<FString>>& FilterStructuredCriteria) const`
- L44 _public function_ `virtual bool HasTag(const FName Tag) const`
- L45 _public function_ `virtual bool IsExpandable() const`
- L46 _public function_ `virtual bool IsExpanded() const`
- L48 _public function_ `void AddChild(OperatorTreeItemPtr ItemPtr)`
- L49 _public function_ `bool HasChildren() const`
- L51 _public function_ `virtual OperatorTreeItemType GetType() const`
- L52 _public function_ `bool HasType(const OperatorTreeItemType InType) const`
- L54 _public member_ `TArray<OperatorTreeItemPtr> Children;`
- L56 _public member_ `static const EHorizontalAlignment HorizontalAlignment;`
- L57 _public member_ `static const EVerticalAlignment VerticalAlignment;`
- L58 _public member_ `static const float HorizontalPadding;`
- L59 _public member_ `static const float VerticalPadding;`

#### enum `OperatorTreeItem::OperatorTreeItemType`  
`enum OperatorTreeItemType`  
_L28-36_
- L30 _public enumerator_ `ControlType`
- L31 _public enumerator_ `ModifierType`
- L32 _public enumerator_ `TargetType`
- L33 _public enumerator_ `NodeType`
- L34 _public enumerator_ `MessageType`
- L35 _public enumerator_ `None`

#### class `OperatorTreeControlItem`  
`class OperatorTreeControlItem : public OperatorTreeItem`  
_L62-93_
- inherits: `OperatorTreeItem`
- L64 _private typedef_ `using Super = OperatorTreeItem;`
- L68 _public typedef_ `using OperatorNameAndTags = TPair<FName, TArray<FName>>;`
- L70 _public function_ `OperatorTreeControlItem()`
- L73 _public prototype_ `OperatorTreeControlItem(const OperatorTreeControlItem&) = default;`
- L75 _public function_ `OperatorTreeControlItem(const OperatorNameAndTags& InOperatorNameAndTags) : NameAndTags(InOperatorNameAndTags)`
- L79 _public prototype_ `virtual FText Name() const override;`
- L80 _public prototype_ `virtual FText Description() const override;`
- L82 _public prototype_ `virtual TSharedRef<ITableRow> GenerateRow(const TSharedRef<STableViewBase>& OwnerTable) const override;`
- L83 _public prototype_ `virtual bool MatchesFilterText(const TArray<TArray<FString>>& FilterStructuredCriteria) const override;`
- L84 _public prototype_ `virtual bool HasTag(const FName Tag) const override;`
- L85 _public prototype_ `FName OperatorTypeName() const;`
- L87 _public function_ `virtual OperatorTreeItemType GetType() const override`
- L88 _public function_ `static OperatorTreeItemType StaticType()`
- L90 _public member_ `OperatorNameAndTags NameAndTags;`
- L92 _public member_ `static const TArray<FName> HiddenTags;`

#### class `OperatorTreeNodeItem`  
`class OperatorTreeNodeItem : public OperatorTreeItem`  
_L102-131_
- inherits: `OperatorTreeItem`
- L104 _private typedef_ `using Super = OperatorTreeItem;`
- L108 _public function_ `OperatorTreeNodeItem()`
- L111 _public prototype_ `OperatorTreeNodeItem(const OperatorTreeNodeItem&) = default;`
- L113 _public prototype_ `OperatorTreeNodeItem(const UEdGraphNode* InNode, const FName& InName, const FString& InBlueprintName);`
- L115 _public prototype_ `virtual FText Name() const override;`
- L117 _public prototype_ `virtual TSharedRef<ITableRow> GenerateRow(const TSharedRef<STableViewBase>& OwnerTable) const override;`
- L118 _public prototype_ `virtual FReply OnDoubleClick() override;`
- L120 _public function_ `virtual OperatorTreeItemType GetType() const override`
- L121 _public function_ `static OperatorTreeItemType StaticType()`
- L123 _public function_ `const UEdGraphNode* GraphNode() const`
- L124 _public prototype_ `bool IsSelectedInGraph() const;`
- L125 _public prototype_ `FSlateColor ColorAndOpacity() const;`
- L128 _private member_ `const UEdGraphNode* Node = nullptr;`
- L129 _private member_ `FText NodeDisplayName;`

#### class `OperatorTreeMessageItem`  
`class OperatorTreeMessageItem : public OperatorTreeItem`  
_L137-167_
- inherits: `OperatorTreeItem`
- L139 _private typedef_ `using Super = OperatorTreeItem;`
- L150 _public prototype_ `OperatorTreeMessageItem() = default;`
- L151 _public prototype_ `OperatorTreeMessageItem(const OperatorTreeMessageItem&) = default;`
- L152 _public prototype_ `OperatorTreeMessageItem(const UEdGraphNode* InNode, const MessageType InType, const FText& InText);`
- L154 _public prototype_ `virtual FText Name() const override;`
- L156 _public prototype_ `virtual TSharedRef<ITableRow> GenerateRow(const TSharedRef<STableViewBase>& OwnerTable) const override;`
- L158 _public function_ `virtual OperatorTreeItemType GetType() const override`
- L159 _public function_ `static OperatorTreeItemType StaticType()`
- L161 _public function_ `const UEdGraphNode* GraphNode() const`
- L164 _private member_ `FText Text;`
- L165 _private member_ `const UEdGraphNode* Node = nullptr;`
- L166 _private member_ `MessageType Type = Log;`

#### enum `OperatorTreeMessageItem::MessageType`  
`enum MessageType`  
_L143-148_
- L145 _public enumerator_ `Log`
- L146 _public enumerator_ `Warning`
- L147 _public enumerator_ `Error`

#### Free symbols / members of external scopes

- L20 _typedef_ `using OperatorTreeItemPtr = TSharedPtr<OperatorTreeItem>;`
- L95 _typedef_ `using ControlItemPtr = TSharedPtr<OperatorTreeControlItem>;`
- L97 _function_ `inline bool operator==(const OperatorTreeControlItem& Lhs, const OperatorTreeControlItem& Rhs)`
- L133 _typedef_ `using NodeItemPtr = TSharedPtr<OperatorTreeNodeItem>;`
- L135 _prototype_ `bool operator==(const OperatorTreeNodeItem& Lhs, const OperatorTreeNodeItem& Rhs);`
- L169 _typedef_ `using MessageItemPtr = TSharedPtr<OperatorTreeMessageItem>;`
- L171 _function_ `inline bool operator==(const OperatorTreeMessageItem& Lhs, const OperatorTreeMessageItem& Rhs)`
- L176 _function_ `template<typename DerivedType> TSharedPtr<DerivedType> StaticCastOperatorItemPtr(const TSharedPtr<OperatorTreeItem> InItem)`
- L186 _prototype_ `bool IsEqual(const TSharedPtr<OperatorTreeItem> Lhs, const TSharedPtr<OperatorTreeItem> Rhs);`
- L189 _prototype_ `bool MatchSearchText(const FString& TextToSearch, const TArray<TArray<FString>>& StructuredSearchCriteria);` — Returns true if the TextToSearch string matches the search criteria. Used to identify operator or set names that match user specified search strings in the editor.

### `Plugins/Animation/PhysicsControl/Source/PhysicsControlEditor/Public/OperatorViewer/OperatorViewer.h` (Public)


#### class `FPhysicsControlOperatorViewer`  
`class FPhysicsControlOperatorViewer : public IPhysicsControlOperatorViewerInterface`  
_L13-35_
- inherits: `IPhysicsControlOperatorViewerInterface`
- L17 _public prototype_ `virtual ~FPhysicsControlOperatorViewer() = default;`
- L19 _public prototype_ `virtual void OpenOperatorNamesTab() override;`
- L20 _public prototype_ `virtual void CloseOperatorNamesTab() override;`
- L21 _public prototype_ `virtual void ToggleOperatorNamesTab() override;`
- L22 _public prototype_ `virtual bool IsOperatorNamesTabOpen() override;`
- L23 _public prototype_ `virtual void RequestRefresh() override;`
- L25 _public prototype_ `void Startup();`
- L26 _public prototype_ `void Shutdown();`
- L28 _public prototype_ `void OnTabClosed(TSharedRef<SDockTab> DockTab);`
- L31 _private prototype_ `TSharedRef<SDockTab> OnCreateTab(const FSpawnTabArgs& SpawnTabArgs);`
- L33 _private member_ `TSharedPtr<SOperatorViewerTabWidget> PersistentTabWidget;`
- L34 _private member_ `TSharedPtr<SDockTab> OperatorNamesTab;`

### `Plugins/Animation/PhysicsControl/Source/PhysicsControlEditor/Public/OperatorViewer/SOperatorTreeWidget.h` (Public)


#### class `SOperatorTreeWidget`  
`class SOperatorTreeWidget : public SCompoundWidget`  
_L25-80_
- inherits: `SCompoundWidget`
- desc: class SOperatorTreeWidget
- L27 _private typedef_ `using Parent = SCompoundWidget;`
- L30 _public typedef_ `using ItemType = OperatorTreeItemPtr;`
- L32 _public typedef_ `using FilterBarType = SBasicFilterBar<ItemType>;`
- L34 _public function_ `SLATE_BEGIN_ARGS(SOperatorTreeWidget)`
- L35 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L40 _public prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;`
- L42 _public prototype_ `TSharedRef<ITableRow> GenerateItemRow(ItemType InItem, const TSharedRef<STableViewBase>& OwnerTable);`
- L43 _public prototype_ `void OnItemGetChildren(ItemType InItem, TArray<ItemType>& OutChildren);`
- L44 _public prototype_ `void OnFilterBarFilterChanged();`
- L45 _public prototype_ `void OnFilterTextChanged(const FText& SearchText);`
- L47 _public prototype_ `bool MatchesSearchAndFilter(const ItemType InItem) const;`
- L49 _public prototype_ `bool HasTag(const ItemType Item, const FName Tag);`
- L51 _public prototype_ `virtual FReply OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent) override;`
- L53 _public prototype_ `void OnItemDoubleClicked(ItemType InItem);`
- L54 _public prototype_ `TSharedPtr<SWidget> CreateContextMenu();`
- L56 _public prototype_ `void RequestRefresh();`
- L58 _public prototype_ `void CopySelectedItemsNamesToClipboard() const;`
- L59 _public prototype_ `void CopySelectedItemsDescriptionsToClipboard() const;`
- L63 _protected prototype_ `void Construct_Internal();`
- L64 _protected prototype_ `virtual void CreateCustomFilters();`
- L65 _protected prototype_ `virtual void Refresh();`
- L67 _protected member_ `TSharedPtr<STreeView<ItemType>> TreeView;`
- L68 _protected member_ `TSharedPtr<SSearchBox> SearchBox;`
- L69 _protected member_ `TSharedPtr<FilterBarType> FilterBar;`
- L71 _protected member_ `TArray<TSharedRef<FFilterBase<ItemType>>> CustomFilters;`
- L72 _protected member_ `TArray<ItemType> TreeItems;`
- L73 _protected member_ `TSet<FName> SetNames;`
- L74 _protected member_ `FText FilterText;`
- L76 _protected member_ `TArray<TArray<FString>> FilterStructuredCriteria;`
- L77 _protected member_ `TSet<FName> FilterSetNames;`
- L79 _protected member_ `bool bRefreshRequested = false;`

### `Plugins/Animation/PhysicsControl/Source/PhysicsControlEditor/Public/OperatorViewer/SOperatorViewerTabWidget.h` (Public)


#### class `SOperatorViewerTabWidget`  
`class SOperatorViewerTabWidget : public SCompoundWidget`  
_L12-27_
- inherits: `SCompoundWidget`
- L16 _public function_ `SLATE_BEGIN_ARGS(SOperatorViewerTabWidget)`
- L22 _public prototype_ `void Construct(const FArguments& InArgs, int32 InTabIndex);`
- L23 _public prototype_ `void RequestRefresh();`
- L26 _private member_ `TSharedPtr<SOperatorTreeWidget> TreeViewWidget;`

### `Plugins/Animation/PhysicsControl/Source/PhysicsControlEditor/Public/PhysicsControlAssetApplicationMode.h` (Public)


#### class `FPhysicsControlAssetApplicationMode`  
`class FPhysicsControlAssetApplicationMode : public FApplicationMode`  
_L20-41_
- inherits: `FApplicationMode`
- desc: The application mode for the Physics Control Asset Editor This defines the layout of the UI. It basically spawns all the tabs, such as the viewport, details panels, etc.
- L24 _public member_ `static FName ModeName;` — The name of this mode.
- L26 _public prototype_ `FPhysicsControlAssetApplicationMode( TSharedRef<FWorkflowCentricApplication> InHostingApp, TSharedPtr<ISkeletonTree> SkeletonTree, TSharedRef<IPersonaPreviewScene> InPreviewScene);`
- L32 _public prototype_ `virtual void RegisterTabFactories(TSharedPtr<FTabManager> InTabManager) override;` — FApplicationMode overrides.
- L37 _protected member_ `TWeakPtr<FPhysicsControlAssetEditor> PhysicsControlAssetEditor = nullptr;` — The hosting app.
- L40 _protected member_ `FWorkflowAllowedTabSet TabFactories;` — The tab factories we support.

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API PHYSICSCONTROLEDITOR_API`

### `Plugins/Animation/PhysicsControl/Source/PhysicsControlEditor/Public/PhysicsControlAssetEditor.h` (Public)


#### class `FPhysicsControlAssetEditor`  
`class FPhysicsControlAssetEditor : public FPersonaAssetEditorToolkit, public IHasPersonaToolkit, public FGCObject, public FEditorUndoClient, public FTickableEditorObject`  
_L32-182_
- inherits: `FPersonaAssetEditorToolkit,IHasPersonaToolkit,FGCObject,FEditorUndoClient,FTickableEditorObject`
- desc: The main toolkit/editor for working with Physics Control Assets
- L49 _public prototype_ `void InitAssetEditor( const EToolkitMode::Type Mode, const TSharedPtr<IToolkitHost>& InitToolkitHost, UPhysicsControlAsset* InPhysicsControlAsset);` — Initialize the asset editor. This will register the application mode, init the preview scene, etc.
- L55 _public prototype_ `TSharedPtr<FPhysicsControlAssetEditorData> GetEditorData() const;` — Shared data accessor
- L58 _public prototype_ `virtual void RegisterTabSpawners(const TSharedRef<FTabManager>& InTabManager) override;` — FAssetEditorToolkit overrides.
- L59 _public prototype_ `virtual void UnregisterTabSpawners(const TSharedRef<FTabManager>& InTabManager) override;`
- L60 _public prototype_ `virtual FName GetToolkitFName() const override;`
- L61 _public prototype_ `virtual FText GetBaseToolkitName() const override;`
- L62 _public prototype_ `virtual FText GetToolkitName() const override;`
- L63 _public prototype_ `virtual FLinearColor GetWorldCentricTabColorScale() const override;`
- L64 _public prototype_ `virtual FString GetWorldCentricTabPrefix() const override;`
- L65 _public prototype_ `virtual void InitToolMenuContext(FToolMenuContext& MenuContext) override;`
- L69 _public function_ `virtual FString GetReferencerName() const override` — FGCObject overrides.
- L70 _public prototype_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override;`
- L74 _public prototype_ `virtual void Tick(float DeltaTime) override;` — FTickableEditorObject overrides.
- L75 _public function_ `virtual ETickableTickType GetTickableTickType() const override`
- L76 _public prototype_ `virtual TStatId GetStatId() const override;`
- L80 _public prototype_ `virtual TSharedRef<IPersonaToolkit> GetPersonaToolkit() const override;` — IHasPersonaToolkit overrides.
- L83 _public function_ `IPersonaToolkit* GetPersonaToolkitPointer() const`
- L86 _public prototype_ `void RefreshHierarchyTree();` — Repopulates the hierarchy tree view
- L89 _public prototype_ `void RefreshPreviewViewport();` — Refreshes the preview viewport
- L92 _public prototype_ `void InvokeControlProfile(FName ProfileName);` — Invokes the control profile with the name, assuming simulation is running
- L95 _public prototype_ `void ReinvokeControlProfile();` — Invokes the most recently invoked control profile
- L98 _public prototype_ `void RecreateControlsAndModifiers();` — Destroys all existing controls modifiers and then recreates them from the control asset
- L101 _protected prototype_ `FText GetSimulationToolTip() const;`
- L102 _protected prototype_ `FSlateIcon GetSimulationIcon() const;`
- L105 _protected prototype_ `void HandlePreviewSceneCreated(const TSharedRef<IPersonaPreviewScene>& InPersonaPreviewScene);` — Preview scene setup.
- L106 _protected prototype_ `void HandleViewportCreated(const TSharedRef<IPersonaViewport>& InPersonaViewport);`
- L107 _protected prototype_ `void HandleDetailsCreated(const TSharedRef<class IDetailsView>& InDetailsView);`
- L108 _protected prototype_ `void HandleSelectionChanged(const TArrayView<TSharedPtr<ISkeletonTreeItem>>& InSelectedItems, ESelectInfo::Type InSelectInfo);`
- L109 _protected prototype_ `void HandleGetFilterLabel(TArray<FText>& InOutItems) const;`
- L110 _protected prototype_ `void HandleExtendFilterMenu(FMenuBuilder& InMenuBuilder);`
- L111 _protected prototype_ `void HandleExtendContextMenu(FMenuBuilder& InMenuBuilder);`
- L112 _protected prototype_ `void OnFinishedChangingDetails(const FPropertyChangedEvent& PropertyChangedEvent);`
- L113 _protected prototype_ `void ShowEmptyDetails() const;`
- L115 _protected prototype_ `void ExtendMenu();`
- L116 _protected prototype_ `void ExtendToolbar();`
- L117 _protected prototype_ `void ExtendViewportMenus();`
- L118 _protected prototype_ `void BindCommands();`
- L121 _protected prototype_ `void BuildMenuWidgetSelection(FMenuBuilder& InMenuBuilder);` — Building the context menus
- L122 _protected prototype_ `void BuildMenuWidgetBody(FMenuBuilder& InMenuBuilder);`
- L125 _protected prototype_ `void OnCompile();` — Toolbar/menu commands
- L126 _protected prototype_ `bool IsCompilationNeeded();`
- L127 _protected prototype_ `void OnToggleSimulation();`
- L128 _protected prototype_ `void OnToggleSimulationNoGravity();`
- L129 _protected prototype_ `bool IsNoGravitySimulationEnabled() const;`
- L130 _protected prototype_ `void OnToggleSimulationFloorCollision();`
- L131 _protected prototype_ `bool IsSimulationFloorCollisionEnabled() const;`
- L132 _protected prototype_ `void OnMeshRenderingMode(EPhysicsAssetEditorMeshViewMode Mode, bool bSimulation);`
- L133 _protected prototype_ `bool IsMeshRenderingMode(EPhysicsAssetEditorMeshViewMode Mode, bool bSimulation) const;`
- L134 _protected prototype_ `void OnCollisionRenderingMode(EPhysicsAssetEditorCollisionViewMode Mode, bool bSimulation);`
- L135 _protected prototype_ `bool IsCollisionRenderingMode(EPhysicsAssetEditorCollisionViewMode Mode, bool bSimulation) const;`
- L136 _protected prototype_ `void OnConstraintRenderingMode(EPhysicsAssetEditorConstraintViewMode Mode, bool bSimulation);`
- L137 _protected prototype_ `bool IsConstraintRenderingMode(EPhysicsAssetEditorConstraintViewMode Mode, bool bSimulation) const;`
- L138 _protected prototype_ `void ToggleDrawViolatedLimits();`
- L139 _protected prototype_ `bool IsDrawingViolatedLimits() const;`
- L140 _protected prototype_ `bool IsRunningSimulation() const;`
- L141 _protected prototype_ `bool IsNotRunningSimulation() const;`
- L144 _protected prototype_ `TSharedRef<SWidget> MakeConstraintScaleWidget();` — Make the constraint scale widget
- L147 _protected prototype_ `TSharedRef<SWidget> MakeCollisionOpacityWidget();` — Make the collision opacity widget
- L151 _protected member_ `TSharedPtr<IPersonaToolkit> PersonaToolkit = nullptr;` — The persona toolkit.
- L154 _protected member_ `TSharedPtr<IPersonaViewport> PersonaViewport = nullptr;` — Persona viewport.
- L157 _protected member_ `TSharedPtr<FPhysicsControlAssetEditorData> EditorData;` — Data and methods shared across multiple classes
- L160 _protected member_ `TSharedPtr<IDetailsView> DetailsView;` — Asset properties tab
- L163 _protected member_ `TSharedPtr<ISkeletonTree> SkeletonTree;` — The skeleton tree widget
- L166 _protected member_ `TSharedPtr<FPhysicsControlAssetEditorSkeletonTreeBuilder> SkeletonTreeBuilder;` — The skeleton tree builder
- L169 _protected member_ `TSharedPtr<FUICommandList_Pinnable> SkeletonTreeCommandList;` — Command list for skeleton tree operations
- L172 _protected member_ `TSharedPtr<FUICommandList_Pinnable> ViewportCommandList;` — Command list for viewport operations
- L175 _protected member_ `bool bIsInitialized = false;` — Has the asset editor been initialized?
- L178 _protected member_ `bool bSelecting;` — True if in OnTreeSelectionChanged()... protects against infinite recursion
- L181 _protected member_ `FName PreviouslyInvokedControlProfile;` — Stored when a control profile is invoked

#### Free symbols / members of external scopes

- L14 _macro_ `#define UE_API PHYSICSCONTROLEDITOR_API`
- L24 _namespace_ `namespace PhysicsControlAssetEditorModes`
- L26 _externvar_ `extern const FName PhysicsControlAssetEditorMode;` (scope `PhysicsControlAssetEditorModes`)

### `Plugins/Animation/PhysicsControl/Source/PhysicsControlEditor/Public/PhysicsControlAssetEditorEditMode.h` (Public)


#### class `FPhysicsControlAssetEditorEditMode`  
`class FPhysicsControlAssetEditorEditMode : public IPersonaEditMode`  
_L18-103_
- inherits: `IPersonaEditMode`
- desc: The Physics Control Asset Editor edit mode.
- L22 _public member_ `static FName ModeName;` — The name of the mode.
- L24 _public prototype_ `FPhysicsControlAssetEditorEditMode();`
- L26 _public prototype_ `void SetEditorData( const TSharedRef<FPhysicsControlAssetEditor> InPhysicsControlAssetEditor, TSharedPtr<FPhysicsControlAssetEditorData> InEditorData);`
- L31 _public prototype_ `virtual bool GetCameraTarget(FSphere& OutTarget) const override;` — IPersonaEditMode overrides.
- L32 _public prototype_ `virtual class IPersonaPreviewScene& GetAnimPreviewScene() const override;`
- L33 _public function_ `virtual void GetOnScreenDebugInfo(TArray<FText>& OutDebugInfo) const override`
- L34 _public prototype_ `virtual void Exit() override;`
- L38 _public prototype_ `virtual bool InputKey(FEditorViewportClient* ViewportClient, FViewport* Viewport, FKey Key, EInputEvent Event) override;` — FEdMode overrides.
- L39 _public prototype_ `virtual bool InputAxis(FEditorViewportClient* InViewportClient, FViewport* Viewport, int32 ControllerId, FKey Key, float Delta, float DeltaTime) override;`
- L40 _public prototype_ `virtual void Tick(FEditorViewportClient* ViewportClient, float DeltaTime) override;`
- L41 _public prototype_ `virtual void Render(const FSceneView* View, FViewport* Viewport, FPrimitiveDrawInterface* PDI) override;`
- L42 _public prototype_ `virtual void DrawHUD(FEditorViewportClient* ViewportClient, FViewport* Viewport, const FSceneView* View, FCanvas* Canvas) override;`
- L43 _public function_ `virtual bool IsCompatibleWith(FEditorModeID OtherModeID) const override`
- L44 _public function_ `virtual bool AllowWidgetMove() override`
- L45 _public function_ `virtual bool ShouldDrawWidget() const override`
- L46 _public function_ `virtual bool UsesTransformWidget() const override`
- L47 _public function_ `virtual bool UsesTransformWidget(UE::Widget::EWidgetMode CheckMode) const override`
- L48 _public prototype_ `virtual bool HandleClick(FEditorViewportClient* InViewportClient, HHitProxy* HitProxy, const FViewportClick& Click) override;`
- L49 _public prototype_ `virtual bool ReceivedFocus(FEditorViewportClient* ViewportClient, FViewport* Viewport);`
- L50 _public prototype_ `virtual bool LostFocus(FEditorViewportClient* ViewportClient, FViewport* Viewport);`
- L55 _protected prototype_ `bool SimMousePress(FEditorViewportClient* InViewportClient, FKey Key);` — Simulation mouse forces
- L56 _protected prototype_ `void SimMouseMove(FEditorViewportClient* InViewportClient, float DeltaX, float DeltaY);`
- L57 _protected prototype_ `bool SimMouseRelease();`
- L58 _protected prototype_ `bool SimMouseWheelUp(FEditorViewportClient* InViewportClient);`
- L59 _protected prototype_ `bool SimMouseWheelDown(FEditorViewportClient* InViewportClient);`
- L61 _protected prototype_ `void OpenBodyMenu(FEditorViewportClient* InViewportClient);`
- L62 _protected prototype_ `void OpenSelectionMenu(FEditorViewportClient* InViewportClient);`
- L65 _protected prototype_ `void HitNothing(FEditorViewportClient* InViewportClient);` — Called when no scene proxy is hit, deselects everything
- L68 _protected member_ `TWeakPtr<FPhysicsControlAssetEditor> PhysicsControlAssetEditor;`
- L70 _protected member_ `TSharedPtr<FPhysicsControlAssetEditorData> EditorData;`
- L73 _protected member_ `UFont* PhysicsControlAssetEditorFont;` — Font used for drawing debug text to the viewport
- L76 _protected member_ `const float SimHoldDistanceChangeDelta;` — Misc consts
- L77 _protected member_ `const float SimMinHoldDistance;`
- L78 _protected member_ `const float SimGrabMoveSpeed;`
- L81 _protected member_ `FIntPoint LastClickPos;` — For mouse forces TODO Danny surely this doesn't need to be here unless its actually shared!
- L82 _protected member_ `FVector LastClickOrigin;`
- L83 _protected member_ `FVector LastClickDirection;`
- L84 _protected member_ `FVector LastClickHitPos;`
- L85 _protected member_ `FVector LastClickHitNormal;`
- L86 _protected member_ `bool bLastClickHit;`
- L89 _protected member_ `float SimGrabPush = 0.0f;` — Simulation mouse forces
- L90 _protected member_ `float SimGrabMinPush = 0.0f;`
- L91 _protected member_ `FVector SimGrabLocation = FVector::ZeroVector;`
- L92 _protected member_ `FVector SimGrabX = FVector::ZeroVector;`
- L93 _protected member_ `FVector SimGrabY = FVector::ZeroVector;`
- L94 _protected member_ `FVector SimGrabZ = FVector::ZeroVector;`
- L97 _protected member_ `TArray<FTransform> StartManRelConTM;` — For interacting with the asset while the simulation is running
- L98 _protected member_ `TArray<FTransform> StartManParentConTM;`
- L99 _protected member_ `TArray<FTransform> StartManChildConTM;`
- L100 _protected member_ `float DragX = 0.0f;`
- L101 _protected member_ `float DragY = 0.0f;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API PHYSICSCONTROLEDITOR_API`

### `Plugins/Animation/PhysicsControl/Source/PhysicsControlEditor/Public/PhysicsControlEditorModule.h` (Public)


#### class `FPhysicsControlEditorModule`  
`class FPhysicsControlEditorModule : public IModuleInterface`  
_L16-28_
- inherits: `IModuleInterface`
- desc: Module handles the Physics Control Asset editor, and also the Physics Control Visualizer
- L21 _public prototype_ `void StartupModule() override;` — IModuleInterface implementation
- L22 _public prototype_ `void ShutdownModule() override;`
- L26 _private member_ `TArray<FName> VisualizersToUnregisterOnShutdown;`
- L27 _private member_ `FPhysicsControlOperatorViewer* EditorInterface = nullptr;`
