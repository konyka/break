# Plugins / SkeletalMeshMorphTargetEditingTools

- module root: `Plugins/Experimental/Animation/SkeletalMeshMorphTargetEditingTools/Source/SkeletalMeshMorphTargetEditingTools`
- headers: 8; symbols: 146
- symbol kinds: class=14, function=11, member=51, prototype=69, typedef=1
- DynamicallyLoadedModuleNames: 
- PrivateDependencyModuleNames: CoreUObject, DynamicMesh, Engine, GeometryCore, GeometryFramework, InputCore, InteractiveToolsFramework, MeshConversion, MeshDescription, MeshModelingTools, MeshModelingToolsEditorOnly, ModelingComponents, ModelingComponentsEditorOnly, Persona, SkeletalMeshDescription, SkeletalMeshEditor, SkeletalMeshModifiers, SkeletalMeshUtilitiesCommon, Slate, SlateCore, StaticMeshDescription, UnrealEd
- PublicDependencyModuleNames: Core, MeshModelingToolsEditorOnly, MeshModelingToolsEditorOnlyExp, ModelingToolsEditorMode, SkeletalMeshModelingTools

### `Plugins/Experimental/Animation/SkeletalMeshMorphTargetEditingTools/Source/SkeletalMeshMorphTargetEditingTools/Private/EraseMorphTargetBrushOps.h` (Private)


#### class `UEraseMorphTargetBrushOpProps`  
`class UEraseMorphTargetBrushOpProps : public UMeshSculptBrushOpProps`  
_L12-28_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMeshSculptBrushOpProps`
- L18 _public member_ `float Strength = 0.5;` — `UPROPERTY(EditAnywhere, Category = InflateBrush, meta = (DisplayName = "Strength", UIMin = "0.0", UIMax = "1.0", ClampMin = "0.0", ClampMax = "1.0", ModelingQuickEdit, ModelingQuickSettings = 200))` — Strength of the Brush
- L22 _public member_ `float Falloff = 0.5;` — `UPROPERTY(EditAnywhere, Category = InflateBrush, meta = (DisplayName = "Falloff", UIMin = "0.0", UIMax = "1.0", ClampMin = "0.0", ClampMax = "1.0"))` — Amount of falloff to apply
- L24 _public function_ `virtual float GetStrength() override`
- L25 _public function_ `virtual void SetStrength(float NewStrength) override`
- L26 _public function_ `virtual float GetFalloff() override`
- L27 _public function_ `virtual bool SupportsStrengthPressure() override`

#### class `FEraseMorphTargetBrushOp`  
`class FEraseMorphTargetBrushOp : public FMeshSculptBrushOp`  
_L30-92_
- inherits: `FMeshSculptBrushOp`
- L34 _public member_ `double BrushSpeedTuning = 2.0;`
- L36 _public typedef_ `typedef TUniqueFunction<const FDynamicMesh3*()> GetMeshWithoutCurrentMorphFuncType;`
- L38 _public member_ `GetMeshWithoutCurrentMorphFuncType GetMeshWithoutCurrentMorphFunc;`
- L40 _public function_ `FEraseMorphTargetBrushOp(GetMeshWithoutCurrentMorphFuncType InFunc)`
- L45 _public function_ `virtual ESculptBrushOpTargetType GetBrushTargetType() const override`
- L52 _public function_ `virtual bool SupportsStrokeType(EMeshSculptStrokeType StrokeType) const override` — Match FSingleNormalSculptBrushOp (Offset): Spacing-gated emission so a stationary cursor does not keep firing stamps.
- L65 _public function_ `virtual void ApplyStamp(const FDynamicMesh3* Mesh, const FSculptBrushStamp& Stamp, const TArray<int32>& Vertices, TArray<FVector3d>& NewPositionsOut) override`

#### Free symbols / members of external scopes

- L74 _function_ `` (scope `FEraseMorphTargetBrushOp::ApplyStamp`)

### `Plugins/Experimental/Animation/SkeletalMeshMorphTargetEditingTools/Source/SkeletalMeshMorphTargetEditingTools/Private/MorphTargetVertexSculptToolCommands.h` (Private)


#### class `FMorphTargetVertexSculptToolActionCommands`  
`class FMorphTargetVertexSculptToolActionCommands : public TInteractiveToolCommands<FMorphTargetVertexSculptToolActionCommands>`  
_L18-26_
- inherits: `TInteractiveToolCommands<FMorphTargetVertexSculptToolActionCommands>`
- desc: Per-tool UI commands for UMorphTargetVertexSculptTool. Self-contained: the tool's plugin owns the registration and lifetime, and the morph plugin advertises this command class to a host editor through FExtensionToolDescription::ToolCommandsGetter. Any host that consumes IModelingModeToolExtension already calls BindCommandsForCurrentTool / UnbindActiveCommands on this object during tool start / end (see USkeletalMeshModelingToolsEditorMode::OnToolStarted and UModelingToolsEditorMode::OnToolStarted).
- L22 _public prototype_ `FMorphTargetVertexSculptToolActionCommands();`
- L25 _public prototype_ `virtual void GetToolDefaultObjectList(TArray<UInteractiveTool*>& ToolCDOs) override;` — TInteractiveToolCommands

### `Plugins/Experimental/Animation/SkeletalMeshMorphTargetEditingTools/Source/SkeletalMeshMorphTargetEditingTools/Public/IMorphTargetEditingToolInterface.h` (Public)


#### class `UMorphTargetEditingToolInterface`  
`class UMorphTargetEditingToolInterface : public UInterface`  
_L14-17_
- reflection: `UINTERFACE(MinimalAPI)`
- inherits: `UInterface`

#### class `IMorphTargetEditingToolInterface`  
`class IMorphTargetEditingToolInterface : public IInterface`  
_L19-26_
- inherits: `IInterface`
- L23 _public prototype_ `virtual void SetupMorphEditingToolCommon();`
- L24 _public prototype_ `virtual void ShutdownMorphEditingToolCommon();`
- L25 _public prototype_ `virtual void SetupCommonProperties(const TFunction<void(UMorphTargetEditingToolProperties*)>& InSetupFunction) = 0;`

#### class `UMorphTargetEditingToolProperties`  
`class UMorphTargetEditingToolProperties : public UInteractiveToolPropertySet`  
_L29-35_
- reflection: `UCLASS()`
- inherits: `UInteractiveToolPropertySet`
- L34 _public member_ `FName EditMorphTargetName;` — `UPROPERTY(VisibleAnywhere, Category = "MorphTarget", meta = (NoResetToDefault, DisplayName = "Name"))`

### `Plugins/Experimental/Animation/SkeletalMeshMorphTargetEditingTools/Source/SkeletalMeshMorphTargetEditingTools/Public/MorphTargetMaskTool.h` (Public)


#### class `UMorphTargetMaskToolBuilder`  
`class UMorphTargetMaskToolBuilder : public UMeshSurfacePointMeshEditingToolBuilder`  
_L20-28_
- reflection: `UCLASS()`
- inherits: `UMeshSurfacePointMeshEditingToolBuilder`
- desc: MorphTarget Vertex Sculpt Tool Builder
- L25 _public prototype_ `virtual bool CanBuildTool(const FToolBuilderState& SceneState) const override;`
- L26 _public prototype_ `virtual UMeshSurfacePointTool* CreateNewTool(const FToolBuilderState& SceneState) const override;`
- L27 _public prototype_ `virtual const FToolTargetTypeRequirements& GetTargetRequirements() const override;`

#### class `UMorphTargetMaskToolProperties`  
`class UMorphTargetMaskToolProperties : public UInteractiveToolPropertySet`  
_L32-65_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveToolPropertySet`
- L37 _public prototype_ `void Setup(UMorphTargetMaskTool* InTool, TArray<FName> InVertexAttributes);`
- L38 _public prototype_ `void Shutdown(UMorphTargetMaskTool* InTool , EToolShutdownType InShutdownType);`
- L39 _public prototype_ `bool ShouldSaveMask() const;`
- L40 _public prototype_ `bool ShouldSaveNewMask() const;`
- L43 _public member_ `FName BaseMorphTarget = NAME_None;` — `UPROPERTY(EditAnywhere, Category = "Mask Settings", meta = (GetOptions = GetMorphTargets, NoResetToDefault))`
- L46 _public prototype_ `const TArray<FName>& GetMorphTargets();` — `UFUNCTION()`
- L48 _public member_ `TArray<FName> MorphTargets;`
- L51 _public member_ `FName VertexAttributeOption = CreateNewVertexAttributeOption;` — `UPROPERTY(EditAnywhere, Category = "Mask Settings", meta = (DisplayName = "Vertex Attribute", GetOptions = GetVertexAttributeOptions, NoResetToDefault))`
- L54 _public prototype_ `const TArray<FName>& GetVertexAttributeOptions();` — `UFUNCTION()`
- L56 _public member_ `TArray<FName> VertexAttributeOptions;`
- L57 _public member_ `TArray<FName> VertexAttributes;`
- L59 _public member_ `FString PropertySetCacheIdentifier;`
- L61 _public member_ `static const TCHAR* CreateNewVertexAttributeOption;`
- L62 _public member_ `static const TCHAR* DoNotSaveVertexAttributeOption;`
- L64 _public prototype_ `TOptional<int32> GetVertexAttributeIndex();`

#### class `UMorphTargetMaskTool`  
`class UMorphTargetMaskTool: public UMeshVertexAttributePaintToolBase, public IMorphTargetEditingToolInterface, public ISkeletalMeshGeometryIsolationAwareTool, public IHotkeyHintProvider`  
_L71-153_
- reflection: `UCLASS()`
- inherits: `UMeshVertexAttributePaintToolBase,IMorphTargetEditingToolInterface,ISkeletalMeshGeometryIsolationAwareTool,IHotkeyHintProvider`
- desc: MorphTarget Sculpt Tool
- L79 _private prototype_ `virtual bool SetupToolMesh(FDynamicMesh3& InOutToolMesh, int32& OutInitialAttributeIndex) override;`
- L80 _private prototype_ `virtual void CommitToolMesh(FDynamicMesh3& InToolMesh) override;`
- L81 _private prototype_ `virtual void UpdatePreview(const TSet<int32>* TrianglesToUpdate = nullptr, const TArray<int32>* VerticesToUpdate = nullptr) override;`
- L83 _public prototype_ `FName GetEditingMorphTarget();`
- L84 _public prototype_ `FName GetBaseMorphTarget();`
- L85 _public prototype_ `virtual TMap<FName, float> GetMorphTargetWeights();`
- L86 _public prototype_ `virtual const TArray<FTransform>& GetComponentSpaceBoneTransforms();`
- L87 _public prototype_ `virtual void ToggleBoneManipulation(bool bEnable);`
- L91 _public prototype_ `virtual void Setup() override;` — UMeshVertexSculptTool overrides
- L92 _public prototype_ `virtual void Shutdown(EToolShutdownType ShutdownType) override;`
- L93 _public prototype_ `virtual void OnTick(float DeltaTime) override;`
- L96 _public prototype_ `virtual bool IsInputIsolationValidOnOutput() const override;` — ISkeletalMeshGeometryIsolationAwareTool
- L99 _public prototype_ `virtual void GetHotkeyHints(TArray<FHotkeyHint>& OutHints) const override;` — IHotkeyHintProvider
- L104 _protected prototype_ `void HandlePoseChangeDetectorEvent(SkeletalMeshToolsHelper::FPoseChangeDetector::FPayload Payload);`
- L107 _protected prototype_ `virtual void SetupCommonProperties(const TFunction<void(UMorphTargetEditingToolProperties*)>& InSetupFunction) override;` — IMorphTargetEditingTool overrides
- L109 _protected prototype_ `void PosePreviewMesh( const TArray<FTransform>& ComponentSpaceTransforms, const TMap<FName, float>& MorphTargetWeights, const TSet<int32>* TrianglesToUpdate = nullptr, const TArray<int32>* VerticesToUpdate = nullptr );`
- L117 _protected member_ `TObjectPtr<class UMorphTargetEditingToolProperties> EditorToolProperties;` — `UPROPERTY()`
- L120 _protected member_ `TObjectPtr<class UMorphTargetMaskToolProperties> MaskToolProperties;` — `UPROPERTY()`
- L125 _protected member_ `TWeakObjectPtr<USkeletalMeshEditorContextObjectBase> EditorContext = nullptr;` — `UPROPERTY()`
- L127 _protected member_ `SkeletalMeshToolsHelper::FPoseChangeDetector PoseChangeDetector;`
- L129 _protected member_ `FDynamicMesh3 MaskToolCommitMesh;`
- L132 _protected member_ `TOptional<UE::Geometry::FDynamicSubmesh3> IsolationSubmesh;` — Geometry isolation: submesh mapping for vertex ID translation (null when no isolation)
- L134 _protected member_ `TArray<FTransform> ComponentSpaceTransformsRefPose;`
- L135 _protected member_ `TMap<FName, float> MorphTargetZeroWeights;`
- L137 _protected member_ `FName ToolMorphTargetName;`
- L138 _protected member_ `FName ToolMorphTargetBackupAttributeName;`
- L140 _protected member_ `TArray<FTransform> DefaultComponentSpaceBoneTransforms;`
- L142 _protected member_ `TValueWatcher<FName> BaseMorphTargetWatcher;`
- L143 _protected member_ `TValueWatcher<FName> VertexAttributeOptionWatcher;`
- L145 _protected member_ `bool bFastDeformPreviewMesh = false;`
- L146 _protected member_ `bool bRebuildOctree = false;`
- L148 _protected member_ `bool bMeshSelectorNeedsUpdate = false;`
- L151 _protected member_ `int32 TempPaintLayerAttributeIndex = INDEX_NONE;`
- L152 _protected member_ `int32 CurrentAttributeIndex = INDEX_NONE;`

### `Plugins/Experimental/Animation/SkeletalMeshMorphTargetEditingTools/Source/SkeletalMeshMorphTargetEditingTools/Public/MorphTargetVertexSculptTool.h` (Public)


#### class `UMorphTargetVertexSculptToolBuilder`  
`class UMorphTargetVertexSculptToolBuilder : public UMeshVertexSculptToolBuilder`  
_L22-30_
- reflection: `UCLASS()`
- inherits: `UMeshVertexSculptToolBuilder`
- desc: MorphTarget Vertex Sculpt Tool Builder
- L27 _public prototype_ `virtual bool CanBuildTool(const FToolBuilderState& SceneState) const override;`
- L28 _public prototype_ `virtual UMeshSurfacePointTool* CreateNewTool(const FToolBuilderState& SceneState) const override;`
- L29 _public prototype_ `virtual const FToolTargetTypeRequirements& GetTargetRequirements() const override;`

#### class `UMorphTargetVertexSculptTool`  
`class UMorphTargetVertexSculptTool : public UMeshVertexSculptTool, public ISkeletalMeshEditingInterface, public IMorphTargetEditingToolInterface, public ISkeletalMeshGeometryIsolationAwareTool, public IHotkeyHintProvider`  
_L37-136_
- reflection: `UCLASS()`
- inherits: `UMeshVertexSculptTool,ISkeletalMeshEditingInterface,IMorphTargetEditingToolInterface,ISkeletalMeshGeometryIsolationAwareTool,IHotkeyHintProvider`
- desc: MorphTarget Sculpt Tool
- L47 _public member_ `static constexpr const TCHAR* ActionCommandsContextName = TEXT("Ske`
- L49 _public prototype_ `virtual FName GetEditingMorphTarget();`
- L50 _public prototype_ `virtual TMap<FName, float> GetMorphTargetWeights();`
- L51 _public prototype_ `virtual const TArray<FTransform>& GetComponentSpaceBoneTransforms();`
- L52 _public prototype_ `virtual void ToggleBoneManipulation(bool bEnable);`
- L57 _public prototype_ `void MirrorEditingMorphTarget();` — Mirrors the editing morph target's deltas across the base-mesh symmetry plane in place, emits a single undoable change, and queues a sculpt-mesh refresh on the next tick. No-op while a stroke is in progress, no editing morph is selected, or no base-mesh symmetry is available.
- L60 _public prototype_ `bool CanMirrorEditingMorphTarget() const;` — True when MirrorEditingMorphTarget would actually do something.
- L64 _public prototype_ `virtual void InitializeSculptMeshComponent(UBaseDynamicMeshComponent* Component, AActor* Actor) override;` — UMeshSculptToolBase overrides
- L65 _public prototype_ `virtual void SetupBrushEditBehaviorSetup(ULocalTwoAxisPropertyEditInputBehavior& OutBehavior) override;`
- L68 _public prototype_ `virtual void Setup() override;` — UMeshVertexSculptTool overrides
- L69 _public prototype_ `virtual void Shutdown(EToolShutdownType ShutdownType) override;`
- L70 _public prototype_ `virtual void CommitResult(UBaseDynamicMeshComponent* Component, bool bModifiedTopology) override;`
- L71 _public prototype_ `virtual void OnTick(float DeltaTime) override;`
- L72 _public prototype_ `virtual void OnPropertyModified(UObject* PropertySet, FProperty* Property) override;`
- L73 _public prototype_ `virtual void OnBeginStroke(const FRay& WorldRay) override;`
- L74 _public prototype_ `virtual void OnEndStroke() override;`
- L77 _public prototype_ `virtual void RegisterActions(FInteractiveToolActionSet& ActionSet) override;` — UInteractiveTool overrides
- L80 _public prototype_ `virtual bool IsInputIsolationValidOnOutput() const override;` — ISkeletalMeshGeometryIsolationAwareTool
- L83 _public prototype_ `virtual void GetHotkeyHints(TArray<FHotkeyHint>& OutHints) const override;` — IHotkeyHintProvider
- L87 _protected prototype_ `virtual void RegisterBrushes() override;`
- L89 _protected prototype_ `void HandlePoseChangeDetectorEvent(SkeletalMeshToolsHelper::FPoseChangeDetector::FPayload Payload);`
- L92 _protected prototype_ `virtual void SetupCommonProperties(const TFunction<void(UMorphTargetEditingToolProperties*)>& InSetupFunction) override;` — IMorphTargetEditingTool overrides
- L95 _protected prototype_ `virtual void HandleSkeletalMeshModified(const TArray<FName>& Payload, const ESkeletalMeshNotifyType InNotifyType) override;` — ISkeletalMeshEditingInterface
- L99 _protected prototype_ `void PoseSculptMesh(const TArray<FTransform>& ComponentSpaceTransforms, const TMap<FName, float>& MorphTargetWeights);`
- L102 _protected member_ `TObjectPtr<class UMorphTargetEditingToolProperties> EditorToolProperties;` — `UPROPERTY()`
- L105 _protected member_ `TWeakObjectPtr<USkeletalMeshEditorContextObjectBase> EditorContext = nullptr;` — `UPROPERTY()`
- L107 _protected member_ `TFunction<const FDynamicMesh3*()> GetMeshWithoutCurrentMorphFunc;`
- L108 _protected member_ `FDynamicMesh3 PosedMeshWithoutEditingMorph;`
- L109 _protected member_ `bool bPosedMeshWithoutEditingMorphDirty = true;`
- L110 _protected prototype_ `void UpdatePosedMeshWithoutEditingMorph();`
- L112 _protected member_ `SkeletalMeshToolsHelper::FPoseChangeDetector PoseChangeDetector;`
- L116 _protected member_ `FDelegateHandle OnToolMeshChangedDelegate;`
- L119 _protected member_ `TObjectPtr<UDynamicMesh> ToolDynamicMesh;` — `UPROPERTY()`
- L122 _protected member_ `TOptional<UE::Geometry::FDynamicSubmesh3> IsolationSubmesh;` — Geometry isolation: submesh mapping for vertex ID translation (null when no isolation)
- L124 _protected member_ `TArray<FTransform> ComponentSpaceTransformsRefPose;`
- L126 _protected member_ `FName ToolMorphTargetName;`
- L129 _protected member_ `TArray<FTransform> DefaultComponentSpaceBoneTransforms;`
- L131 _protected member_ `TArray<FTransform> ComponentSpaceTransformsForPosedMesh;`
- L132 _protected member_ `TMap<FName, float> MorphTargetWeightsForPosedMesh;`
- L134 _protected member_ `bool bFastDeformSculptMesh = false;`
- L135 _protected member_ `bool bFullRefreshSculptMesh = false;`

### `Plugins/Experimental/Animation/SkeletalMeshMorphTargetEditingTools/Source/SkeletalMeshMorphTargetEditingTools/Public/SKMMorphTargetEditingToolsCommands.h` (Public)


#### class `FSkeletalMeshMorphTargetEditingToolsCommands`  
`class FSkeletalMeshMorphTargetEditingToolsCommands : public TCommands<FSkeletalMeshMorphTargetEditingToolsCommands>`  
_L8-19_
- inherits: `TCommands<FSkeletalMeshMorphTargetEditingToolsCommands>`
- L11 _public prototype_ `FSkeletalMeshMorphTargetEditingToolsCommands();`
- L14 _public member_ `TSharedPtr<FUICommandInfo> BeginMorphTargetTool;`
- L15 _public member_ `TSharedPtr<FUICommandInfo> BeginMorphTargetSculptTool;`
- L16 _public member_ `TSharedPtr<FUICommandInfo> BeginMorphTargetMaskTool;`
- L18 _public prototype_ `virtual void RegisterCommands() override;`

### `Plugins/Experimental/Animation/SkeletalMeshMorphTargetEditingTools/Source/SkeletalMeshMorphTargetEditingTools/Public/SKMMorphTargetEditingToolsModule.h` (Public)


#### class `FSkeletalMeshMorphTargetEditingToolsModule`  
`class FSkeletalMeshMorphTargetEditingToolsModule : public IModuleInterface, public ISkeletalMeshModelingModeToolExtension`  
_L10-28_
- inherits: `IModuleInterface,ISkeletalMeshModelingModeToolExtension`
- L14 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface implementation
- L15 _public prototype_ `virtual void ShutdownModule() override;`
- L18 _public function_ `virtual FText GetExtensionName() override` — ISkeletalMeshModelingModeToolExtension
- L20 _public function_ `virtual FText GetToolSectionName() override`
- L22 _public prototype_ `virtual void GetExtensionTools(const FExtensionToolQueryInfo& QueryInfo, TArray<FExtensionToolDescription>& OutTools) override;`
- L24 _public prototype_ `virtual bool GetExtensionExtendedInfo(FModelingModeExtensionExtendedInfo& InfoOut) override;`
- L26 _public prototype_ `virtual bool GetExtensionToolTargets(TArray<TSubclassOf<UToolTargetFactory>>& ToolTargetFactoriesOut) override;`

### `Plugins/Experimental/Animation/SkeletalMeshMorphTargetEditingTools/Source/SkeletalMeshMorphTargetEditingTools/Public/SKMMorphTargetEditingToolsStyle.h` (Public)


#### class `FSkeletalMeshMorphTargetEditingToolsStyle`  
`class FSkeletalMeshMorphTargetEditingToolsStyle : public FSlateStyleSet`  
_L8-22_
- inherits: `FSlateStyleSet`
- L12 _public prototype_ `static FSkeletalMeshMorphTargetEditingToolsStyle& Get();`
- L17 _protected prototype_ `static void Register();`
- L18 _protected prototype_ `static void Unregister();`
- L21 _private prototype_ `FSkeletalMeshMorphTargetEditingToolsStyle();`
