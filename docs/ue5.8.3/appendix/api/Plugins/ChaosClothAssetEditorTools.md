# Plugins / ChaosClothAssetEditorTools

- module root: `Plugins/ChaosClothAssetEditorCore/Source/ChaosClothAssetEditorTools`
- headers: 7; symbols: 395
- symbol kinds: class=30, delegate=1, enum=8, enumerator=31, function=55, macro=4, member=116, namespace=14, prototype=136
- PrivateDependencyModuleNames: AdvancedPreviewScene, Chaos, ChaosCloth, ChaosClothAsset, ChaosClothAssetDataflowNodes, ChaosClothAssetEngine, ChaosClothAssetTools, ClothingSystemEditor, ClothingSystemEditorInterface, ClothingSystemRuntimeCommon, ClothingSystemRuntimeInterface, ContentBrowser, CoreUObject, DataflowCore, DataflowEditor, DataflowEngine, DynamicMesh, EditorFramework, EditorInteractiveToolsFramework, EditorStyle, EditorSubsystem, Engine, GeometryCore, GeometryFramework, LevelEditor, MeshConversion, MeshDescription, MeshModelingTools, MeshModelingToolsExp, ModelingComponents, ModelingComponentsEditorOnly, Projects, RenderCore, SkeletalMeshDescription, Slate, SlateCore, StatusBar, ToolMenus, ToolWidgets, WorkspaceMenuStructure
- PublicDependencyModuleNames: Core, InputCore, InteractiveToolsFramework, UnrealEd

### `Plugins/ChaosClothAssetEditorCore/Source/ChaosClothAssetEditorTools/Private/ChaosClothAsset/ClothMeshSelectionTool.h` (Private)


#### enum `EClothMeshSelectionToolActions`  
`enum class EClothMeshSelectionToolActions`  
_L24-32_
- reflection: `UENUM()`
- L26 _public enumerator_ `NoAction`
- L28 _public enumerator_ `GrowSelection`
- L29 _public enumerator_ `ShrinkSelection`
- L30 _public enumerator_ `FloodSelection`
- L31 _public enumerator_ `ClearSelection`

#### class `UClothMeshSelectionMechanic`  
`class UClothMeshSelectionMechanic : public UPolygonSelectionMechanic`  
_L36-43_
- reflection: `UCLASS()`
- inherits: `UPolygonSelectionMechanic`
- L42 _private prototype_ `virtual bool UpdateSelection(const FRay& WorldRay, FVector3d& LocalHitPositionOut, FVector3d& LocalHitNormalOut) override;`

#### class `UClothMeshSelectionToolActions`  
`class UClothMeshSelectionToolActions : public UInteractiveToolPropertySet`  
_L47-83_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveToolPropertySet`
- L53 _public member_ `TWeakObjectPtr<UClothMeshSelectionTool> ParentTool;`
- L55 _public function_ `void Initialize(UClothMeshSelectionTool* ParentToolIn)`
- L57 _public prototype_ `void PostAction(EClothMeshSelectionToolActions Action);`
- L60 _public function_ `void GrowSelection()` — `UFUNCTION(CallInEditor, Category = Selection)`
- L66 _public function_ `void ShrinkSelection()` — `UFUNCTION(CallInEditor, Category = Selection)`
- L72 _public function_ `void FloodSelection()` — `UFUNCTION(CallInEditor, Category = Selection)`
- L78 _public function_ `void ClearSelection()` — `UFUNCTION(CallInEditor, Category = Selection)`

#### class `UClothMeshSelectionToolProperties`  
`class UClothMeshSelectionToolProperties : public UInteractiveToolPropertySet`  
_L86-108_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveToolPropertySet`
- L93 _public member_ `FString Name;` — `UPROPERTY(EditAnywhere, Transient, Category = Selection, meta = (DisplayName = "Name", TransientToolProperty))`
- L96 _public member_ `EChaosClothAssetSelectionOverrideType SelectionOverrideType;` — `UPROPERTY(EditAnywhere, Transient, Category = Selection, meta = (TransientToolProperty))`
- L99 _public member_ `bool bShowVertices = false;` — `UPROPERTY(EditAnywhere, Category = Visualization, meta = (DisplayName = "Show Vertices"))`
- L102 _public member_ `bool bShowEdges = false;` — `UPROPERTY(EditAnywhere, Category = Visualization, meta = (DisplayName = "Show Edges"))`
- L106 _private prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`

#### class `UClothMeshSelectionTool`  
`class UClothMeshSelectionTool : public USingleSelectionMeshEditingTool`  
_L111-176_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `USingleSelectionMeshEditingTool`
- L119 _private prototype_ `virtual void Setup() override;`
- L120 _private prototype_ `virtual void OnShutdown(EToolShutdownType ShutdownType) override;`
- L121 _private prototype_ `virtual void Render(IToolsContextRenderAPI* RenderAPI) override;`
- L122 _private prototype_ `virtual void DrawHUD(FCanvas* Canvas, IToolsContextRenderAPI* RenderAPI) override;`
- L124 _private prototype_ `virtual void OnTick(float DeltaTime) override;`
- L126 _private function_ `virtual bool HasCancel() const override`
- L127 _private function_ `virtual bool HasAccept() const override`
- L128 _private prototype_ `virtual bool CanAccept() const override;`
- L131 _private prototype_ `virtual FBox GetWorldSpaceFocusBox() override;` — IInteractiveToolCameraFocusAPI implementation
- L133 _private prototype_ `void SetDataflowContextObject(TObjectPtr<UDataflowContextObject> InDataflowContextObject);`
- L135 _private prototype_ `bool GetSelectedNodeInfo(FString& OutMapName, UE::Geometry::FGroupTopologySelection& OutSelection, EChaosClothAssetSelectionOverrideType& OutOverrideType);`
- L136 _private prototype_ `void UpdateSelectedNode();`
- L139 _private member_ `TObjectPtr<UClothMeshSelectionToolProperties> ToolProperties;` — `UPROPERTY()`
- L142 _private member_ `TObjectPtr<UPreviewMesh> PreviewMesh = nullptr;` — `UPROPERTY()`
- L145 _private member_ `TObjectPtr<UPolygonSelectionMechanic> SelectionMechanic = nullptr;` — `UPROPERTY()`
- L148 _private member_ `TObjectPtr<UDataflowContextObject> DataflowContextObject = nullptr;` — `UPROPERTY()`
- L150 _private member_ `TUniquePtr<UE::Geometry::FGroupTopology> Topology;`
- L152 _private member_ `bool bAnyChangeMade = false;`
- L154 _private member_ `bool bHasNonManifoldMapping = false;`
- L155 _private member_ `TArray<int32> DynamicMeshToSelection;`
- L156 _private member_ `TArray<TArray<int32>> SelectionToDynamicMesh;`
- L158 _private member_ `FChaosClothAssetSelectionNode_v2* SelectionNodeToUpdate = nullptr;`
- L159 _private member_ `TSet<int32> InputSelectionSet;`
- L163 _public prototype_ `virtual void RequestAction(EClothMeshSelectionToolActions ActionType);`
- L165 _public prototype_ `void NotifyTargetChanged();`
- L168 _public member_ `TObjectPtr<UClothMeshSelectionToolActions> ActionsProps;` — `UPROPERTY()`
- L171 _private member_ `bool bHavePendingAction = false;`
- L172 _private member_ `EClothMeshSelectionToolActions PendingAction;`
- L173 _private prototype_ `virtual void ApplyAction(EClothMeshSelectionToolActions ActionType);`
- L175 _private prototype_ `void InitializeSculptMeshFromTarget();`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API CHAOSCLOTHASSETEDITORTOOLS_API`
- L17 _namespace_ `namespace UE`
- L17 _namespace_ `namespace Geometry` (scope `UE`)

### `Plugins/ChaosClothAssetEditorCore/Source/ChaosClothAssetEditorTools/Private/ChaosClothAsset/ClothToolActionCommandBindings.h` (Private)


#### class `FClothToolActionCommands`  
`template<typename T, typename ToolClass> class FClothToolActionCommands : public TInteractiveToolCommands<T>`  
_L23-33_
- inherits: `TInteractiveToolCommands<T>`
- L26 _public function_ `FClothToolActionCommands(const FName InContextName, const FText& InContextDesc) : TInteractiveToolCommands<T>(InContextName, InContextDesc, NAME_None, FAppStyle::GetAppStyleSetName())`
- L29 _public function_ `virtual void GetToolDefaultObjectList(TArray<UInteractiveTool*>& ToolCDOs) override`

#### class `FClothEditorWeightMapPaintToolActionCommands`  
`class FClothEditorWeightMapPaintToolActionCommands : public FClothToolActionCommands<FClothEditorWeightMapPaintToolActionCommands, UClothEditorWeightMapPaintTool>`  
_L37-41_
- inherits: `FClothToolActionCommands<FClothEditorWeightMapPaintToolActionCommands,UClothEditorWeightMapPaintTool>`
- L40 _public prototype_ `FClothEditorWeightMapPaintToolActionCommands();`

#### class `FClothMeshSelectionToolActionCommands`  
`class FClothMeshSelectionToolActionCommands : public FClothToolActionCommands<FClothMeshSelectionToolActionCommands, UClothMeshSelectionTool>`  
_L43-47_
- inherits: `FClothToolActionCommands<FClothMeshSelectionToolActionCommands,UClothMeshSelectionTool>`
- L46 _public prototype_ `FClothMeshSelectionToolActionCommands();`

#### class `FClothTransferSkinWeightsToolActionCommands`  
`class FClothTransferSkinWeightsToolActionCommands : public FClothToolActionCommands<FClothTransferSkinWeightsToolActionCommands, UClothTransferSkinWeightsTool>`  
_L49-53_
- inherits: `FClothToolActionCommands<FClothTransferSkinWeightsToolActionCommands,UClothTransferSkinWeightsTool>`
- L52 _public prototype_ `FClothTransferSkinWeightsToolActionCommands();`

#### class `FClothToolActionCommandBindings`  
`class FClothToolActionCommandBindings : public UE::Dataflow::FDataflowToolRegistry::IDataflowToolActionCommands`  
_L58-65_
- inherits: `UE::Dataflow::FDataflowToolRegistry::IDataflowToolActionCommands`
- L62 _public prototype_ `FClothToolActionCommandBindings();`
- L63 _public prototype_ `virtual void UnbindActiveCommands(const TSharedPtr<FUICommandList>& UICommandList) const override;`
- L64 _public prototype_ `virtual void BindCommandsForCurrentTool(const TSharedPtr<FUICommandList>& UICommandList, UInteractiveTool* Tool) const override;`

### `Plugins/ChaosClothAssetEditorCore/Source/ChaosClothAssetEditorTools/Private/ChaosClothAsset/ClothTransferSkinWeightsTool.h` (Private)


#### class `UClothTransferSkinWeightsToolProperties`  
`class UClothTransferSkinWeightsToolProperties : public UInteractiveToolPropertySet`  
_L25-44_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveToolPropertySet`
- L31 _public member_ `TObjectPtr<USkeletalMesh> SourceMesh;` — `UPROPERTY(EditAnywhere, Category = Source)`
- L34 _public member_ `FVector3d SourceMeshTranslation = FVector3d::ZeroVector;` — `UPROPERTY(EditAnywhere, Category = "Transform", meta = (DisplayName = "Location", EditCondition = "SourceMesh != nullptr"))`
- L37 _public member_ `FVector3d SourceMeshRotation = FVector3d::ZeroVector;` — `UPROPERTY(EditAnywhere, Category = "Transform", meta = (DisplayName = "Rotation", EditCondition = "SourceMesh != nullptr"))`
- L40 _public member_ `FVector3d SourceMeshScale = FVector3d::OneVector;` — `UPROPERTY(EditAnywhere, Category = "Transform", meta = (DisplayName = "Scale", AllowPreserveRatio, EditCondition = "SourceMesh != nullptr"))`
- L43 _public member_ `bool bHideSourceMesh = false;` — `UPROPERTY(EditAnywhere, Category = Source)`

#### class `UClothTransferSkinWeightsTool`  
`class UClothTransferSkinWeightsTool : public USingleSelectionMeshEditingTool, public UE::Geometry::IDynamicMeshOperatorFactory`  
_L47-105_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `USingleSelectionMeshEditingTool,UE::Geometry::IDynamicMeshOperatorFactory`
- L56 _private prototype_ `virtual void Setup() override;` — UInteractiveTool
- L57 _private prototype_ `virtual void Shutdown(EToolShutdownType ShutdownType) override;`
- L58 _private function_ `virtual bool HasAccept() const override`
- L59 _private function_ `virtual bool HasCancel() const override`
- L60 _private prototype_ `virtual bool CanAccept() const override;`
- L61 _private prototype_ `virtual void OnTick(float DeltaTime) override;`
- L64 _private prototype_ `virtual TUniquePtr<UE::Geometry::FDynamicMeshOperator> MakeNewOperator() override;` — IDynamicMeshOperatorFactory
- L66 _private prototype_ `void SetDataflowEditorContextObject(TObjectPtr<UDataflowContextObject> InDataflowContextObject);`
- L68 _private prototype_ `FTransform TransformFromProperties() const;`
- L69 _private prototype_ `void SetSRTPropertiesFromTransform(const FTransform& Transform) const;`
- L71 _private prototype_ `void UpdateSourceMesh(TObjectPtr<USkeletalMesh> Mesh);`
- L73 _private prototype_ `void OpFinishedCallback(const UE::Geometry::FDynamicMeshOperator* Op);`
- L75 _private prototype_ `void PreviewMeshUpdatedCallback(UMeshOpPreviewWithBackgroundCompute* Preview);`
- L79 _private member_ `TObjectPtr<UClothTransferSkinWeightsToolProperties> ToolProperties;` — `UPROPERTY(Transient)`
- L82 _private member_ `TObjectPtr<UDataflowContextObject> DataflowContextObject = nullptr;` — `UPROPERTY(Transient)`
- L85 _private member_ `TObjectPtr<UMeshOpPreviewWithBackgroundCompute> TargetClothPreview;` — `UPROPERTY(Transient)`
- L88 _private member_ `TObjectPtr<AInternalToolFrameworkActor> SourceMeshParentActor;` — `UPROPERTY(Transient)`
- L91 _private member_ `TObjectPtr<USkeletalMeshComponent> SourceMeshComponent;` — `UPROPERTY(Transient)`
- L95 _private member_ `TObjectPtr<UTransformProxy> SourceMeshTransformProxy;` — `UPROPERTY(Transient)` — Source mesh transform gizmo support
- L98 _private member_ `TObjectPtr<UCombinedTransformGizmo> SourceMeshTransformGizmo;` — `UPROPERTY(Transient)`
- L100 _private member_ `TSharedPtr<FTransformGizmoDataBinder> DataBinder;`
- L102 _private member_ `FChaosClothAssetTransferSkinWeightsNode* TransferSkinWeightsNode = nullptr;`
- L104 _private member_ `bool bHasOpFailedWarning = false;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API CHAOSCLOTHASSETEDITORTOOLS_API`

### `Plugins/ChaosClothAssetEditorCore/Source/ChaosClothAssetEditorTools/Private/ChaosClothAsset/ClothWeightMapPaintBrushOps.h` (Private)


#### class `FMeshVertexWeightMapEditBrushOp`  
`class FMeshVertexWeightMapEditBrushOp : public FMeshSculptBrushOp`  
_L11-35_
- inherits: `FMeshSculptBrushOp`
- L16 _public function_ `virtual void ApplyStamp( const FDynamicMesh3* Mesh, const FSculptBrushStamp& Stamp, const TArray<int32>& Vertices, TArray<FVector3d>& NewColorsOut) override` — not supported for this kind of brush op
- L26 _public prototype_ `virtual void ApplyStampByVertices( const FDynamicMesh3* Mesh, const FSculptBrushStamp& Stamp, const TArray<int32>& Vertices, TArray<double>& NewAttributesOut) = 0;`
- L33 _public member_ `bool bApplyRadiusLimit = true;` — If bApplyRadiusLimit is enabled, only vertices within the stamp radius are considered

#### class `UWeightMapEraseBrushOpProps`  
`class UWeightMapEraseBrushOpProps : public UMeshSculptBrushOpProps`  
_L44-56_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMeshSculptBrushOpProps`
- L51 _public member_ `double AttributeValue = 0;` — `UPROPERTY(EditAnywhere, Category = EraseBrush, meta = (DisplayName = "Erase Attribute", UIMin = 0))` — Attribute to set as Erased value
- L53 _public function_ `virtual double GetAttribute()`
- L55 _public function_ `virtual float GetFalloff() override`

#### class `FWeightMapEraseBrushOp`  
`class FWeightMapEraseBrushOp : public FMeshVertexWeightMapEditBrushOp`  
_L60-70_
- inherits: `FMeshVertexWeightMapEditBrushOp`
- L64 _public prototype_ `virtual void ApplyStampByVertices( const FDynamicMesh3* Mesh, const FSculptBrushStamp& Stamp, const TArray<int32>& Vertices, TArray<double>& NewAttributesOut) override;`

#### class `UWeightMapPaintBrushOpProps`  
`class UWeightMapPaintBrushOpProps : public UMeshSculptBrushOpProps`  
_L78-98_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMeshSculptBrushOpProps`
- L86 _public member_ `double AttributeValue = 1;` — `UPROPERTY(EditAnywhere, Category = PaintBrush, meta = (DisplayName = "Value", UIMin = 0))` — The Attribute that will be assigned to triangles within the brush region
- L90 _public member_ `float Strength = 0.5;` — `UPROPERTY(EditAnywhere, Category = PaintBrush, meta = (DisplayName = "Strength", UIMin = "0.0", UIMax = "10.", ClampMin = "0.0", ClampMax = "10."))` — Strength of the Brush
- L92 _public function_ `virtual double GetAttribute()`
- L94 _public function_ `virtual float GetStrength() override`
- L95 _public function_ `virtual void SetStrength(float NewStrength) override`
- L97 _public function_ `virtual float GetFalloff() override`

#### class `FWeightMapPaintBrushOp`  
`class FWeightMapPaintBrushOp : public FMeshVertexWeightMapEditBrushOp`  
_L101-116_
- inherits: `FMeshVertexWeightMapEditBrushOp`
- L105 _public function_ `virtual bool IgnoreZeroMovements() const override`
- L110 _public prototype_ `virtual void ApplyStampByVertices( const FDynamicMesh3* Mesh, const FSculptBrushStamp& Stamp, const TArray<int32>& Vertices, TArray<double>& NewAttributesOut) override;`

#### class `UWeightMapSmoothBrushOpProps`  
`class UWeightMapSmoothBrushOpProps : public UMeshSculptBrushOpProps`  
_L123-140_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMeshSculptBrushOpProps`
- L130 _public member_ `float Strength = 0.5;` — `UPROPERTY(EditAnywhere, Category = PaintBrush, meta = (DisplayName = "Strength", UIMin = "0.0", UIMax = "10.", ClampMin = "0.0", ClampMax = "10."))`
- L132 _public function_ `virtual float GetStrength() override`
- L133 _public function_ `virtual void SetStrength(float NewStrength) override`
- L136 _public member_ `float Falloff = 0.5;` — `UPROPERTY(EditAnywhere, Category = PaintBrush, meta = (DisplayName = "Falloff", UIMin = "0.0", UIMax = "1.", ClampMin = "0.0", ClampMax = "1."))`
- L138 _public function_ `virtual float GetFalloff() override`
- L139 _public function_ `virtual void SetFalloff(float NewFalloff) override`

#### class `FWeightMapSmoothBrushOp`  
`class FWeightMapSmoothBrushOp : public FMeshVertexWeightMapEditBrushOp`  
_L143-158_
- inherits: `FMeshVertexWeightMapEditBrushOp`
- L147 _public function_ `virtual bool IgnoreZeroMovements() const override`
- L152 _public prototype_ `virtual void ApplyStampByVertices( const FDynamicMesh3* Mesh, const FSculptBrushStamp& Stamp, const TArray<int32>& Vertices, TArray<double>& NewAttributesOut) override;`

### `Plugins/ChaosClothAssetEditorCore/Source/ChaosClothAssetEditorTools/Private/ChaosClothAsset/ClothWeightMapPaintTool.h` (Private)


#### enum `EClothEditorWeightMapDisplayType`  
`enum class EClothEditorWeightMapDisplayType : uint8`  
_L55-60_
- reflection: `UENUM()`
- L57 _public enumerator_ `BlackAndWhite`
- L58 _public enumerator_ `WhiteAndRed`
- L59 _public enumerator_ `LastValue UMETA(Hidden)`

#### enum `EClothEditorWeightMapPaintInteractionType`  
`enum class EClothEditorWeightMapPaintInteractionType : uint8`  
_L64-72_
- reflection: `UENUM()`
- desc: Mesh Sculpting Brush Types
- L66 _public enumerator_ `Brush`
- L67 _public enumerator_ `Fill`
- L68 _public enumerator_ `PolyLasso`
- L69 _public enumerator_ `Gradient`
- L70 _public enumerator_ `HideTriangles`
- L71 _public enumerator_ `LastValue UMETA(Hidden)`

#### enum `EClothEditorWeightMapPaintBrushType`  
`enum class EClothEditorWeightMapPaintBrushType : uint8`  
_L82-94_
- reflection: `UENUM()`
- desc: Mesh Sculpting Brush Types
- L85 _public enumerator_ `Paint UMETA(DisplayName = "Paint")` — Paint weights
- L88 _public enumerator_ `Smooth UMETA(DisplayName = "Smooth")` — Smooth existing weights
- L91 _public enumerator_ `Erase UMETA(Hidden, DisplayName = "Erase")` — Erase weights
- L93 _public enumerator_ `LastValue UMETA(Hidden)`

#### enum `EClothEditorWeightMapPaintBrushAreaType`  
`enum class EClothEditorWeightMapPaintBrushAreaType : uint8`  
_L99-103_
- reflection: `UENUM()`
- desc: Mesh Sculpting Brush Area Types
- L101 _public enumerator_ `Connected`
- L102 _public enumerator_ `Volumetric`

#### enum `EClothEditorWeightMapPaintVisibilityType`  
`enum class EClothEditorWeightMapPaintVisibilityType : uint8`  
_L107-111_
- reflection: `UENUM()`
- desc: Mesh Sculpting Brush Types
- L109 _public enumerator_ `None`
- L110 _public enumerator_ `Unoccluded`

#### enum `EClothEditorWeightMapPaintQueryType`  
`enum class EClothEditorWeightMapPaintQueryType : uint8`  
_L115-125_
- reflection: `UENUM()`
- desc: Value Query mode
- L118 _public enumerator_ `Interpolated UMETA(DisplayName = "Interpolated")` — Value is interpolated from triangle vertices
- L121 _public enumerator_ `NearestVertexFast UMETA(DisplayName = "Nearest Vertex (Fast)")` — Return the value at the closest vertex of the triangle under the mouse cursor
- L124 _public enumerator_ `NearestVertexAccurate UMETA(DisplayName = "Nearest Vertex (Accurate)")` — Return the value of the nearest vertex inside the brush radius, even if the vertex is not on the triangle under the mouse cursor

#### class `UClothEditorWeightMapPaintBrushFilterProperties`  
`class UClothEditorWeightMapPaintBrushFilterProperties : public UInteractiveToolPropertySet`  
_L131-218_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveToolPropertySet`
- L138 _public member_ `EClothEditorWeightMapDisplayType ColorMap = EClothEditorWeightMapDisplayType::BlackAndWhite;` — `UPROPERTY(EditAnywhere, Category = Display)`
- L141 _public member_ `bool bHighlightZeroAndOne = false;` — `UPROPERTY(EditAnywhere, Category = Display)`
- L144 _public member_ `EClothEditorWeightMapPaintInteractionType SubToolType = EClothEditorWeightMapPaintInteractionType::Brush;` — `UPROPERTY(EditAnywhere, Category = ActionType, meta = (DisplayName = "Action"))`
- L148 _public member_ `EClothEditorWeightMapPaintBrushType PrimaryBrushType = EClothEditorWeightMapPaintBrushType::Paint;` — `UPROPERTY(EditAnywhere, Category = ActionType, meta = (DisplayName = "Brush Mode", HideEditConditionToggle, EditConditionHides, EditCondition = "SubToolType == EClothEditorWeightMapPaintInteractionType::Brush"))`
- L153 _public member_ `float BrushSize = 0.25f;` — `UPROPERTY(EditAnywhere, Category = Brush, meta = (DisplayName = "Brush Size", UIMin = "0.0", UIMax = "1.0", ClampMin = "0.0", ClampMax = "10.0", HideEditConditionToggle, EditConditionHides, EditCondition = "SubToolType == EClothEditorWeightMapPaintInteractionType::Brush"))` — Relative size of brush
- L158 _public member_ `float Falloff = 0.5;` — `UPROPERTY(EditAnywhere, Category = Brush, meta = (UIMin = 0, ClampMin = 0, UIMax = 1, ClampMax = 1, HideEditConditionToggle, EditCondition = "SubToolType == EClothEditorWeightMapPaintInteractionType::Brush && PrimaryBrushType == EClothEditorWeightMapPaintBrushType::Smooth"))` — Relative size of falloff region inside the brush
- L162 _public member_ `bool bHitBackFaces = true;` — `UPROPERTY(EditAnywhere, Category = Brush, meta = (HideEditConditionToggle, EditConditionHides, EditCondition = "SubToolType == EClothEditorWeightMapPaintInteractionType::Brush"))` — Allow the Brush to hit the back-side of the mesh
- L168 _public member_ `double AttributeValue = 1;` — `UPROPERTY(EditAnywhere, Category = Brush, meta = (UIMin = 0, ClampMin = 0, UIMax = 1, ClampMax = 1, HideEditConditionToggle, EditConditionHides, EditCondition = "(SubToolType == EClothEditorWeightMapPaintInteractionType::Brush && PrimaryBrushType == EClothEditorWeightMapPaintBrushType::Paint) || SubToolType == EClothEditorWeightMapPaintInteractionType::Fill || SubToolType == EClothEditorWeightMapPaintInteractionType::PolyLasso"))` — The new value to paint on the mesh
- L174 _public member_ `double Strength = 1.0;` — `UPROPERTY(EditAnywhere, Category = Brush, meta = (UIMin = 0, ClampMin = 0, UIMax = 1, ClampMax = 1, HideEditConditionToggle, EditConditionHides, EditCondition = "SubToolType == EClothEditorWeightMapPaintInteractionType::Brush || SubToolType == EClothEditorWeightMapPaintInteractionType::Fill"))` — How quickly each brush stroke will drive mesh values towards the desired value
- L179 _public member_ `double GradientLowValue = 0.0;` — `UPROPERTY(EditAnywhere, Category = Gradient, meta = (UIMin = 0, ClampMin = 0, UIMax = 1, ClampMax = 1, HideEditConditionToggle, EditConditionHides, EditCondition = "SubToolType == EClothEditorWeightMapPaintInteractionType::Gradient"))` — The Gradient lower limit value
- L184 _public member_ `double GradientHighValue = 1.0;` — `UPROPERTY(EditAnywhere, Category = Gradient, meta = (UIMin = 0, ClampMin = 0, UIMax = 1, ClampMax = 1, HideEditConditionToggle, EditConditionHides, EditCondition = "SubToolType == EClothEditorWeightMapPaintInteractionType::Gradient"))` — The Gradient upper limit value
- L191 _public member_ `float AngleThreshold = 180.0f;` — `UPROPERTY(EditAnywhere, Category = Filters, meta = (UIMin = "0.0", ClampMin = "0.0", UIMax = "180.0", ClampMax = "180.0", HideEditConditionToggle, EditConditionHides, EditCondition = "SubToolType == EClothEditorWeightMapPaintInteractionType::Brush || SubToolType == EClothEditorWeightMapPaintInteractionType::Fill"))` — The Region affected by the current operation will be bounded by edge angles larger than this threshold
- L196 _public member_ `bool bUVSeams = false;` — `UPROPERTY(EditAnywhere, Category = Filters, meta = (HideEditConditionToggle, EditConditionHides, EditCondition = "SubToolType == EClothEditorWeightMapPaintInteractionType::Brush || SubToolType == EClothEditorWeightMapPaintInteractionType::Fill"))` — The Region affected by the current operation will be bounded by UV borders/seams
- L201 _public member_ `bool bNormalSeams = false;` — `UPROPERTY(EditAnywhere, Category = Filters, meta = (HideEditConditionToggle, EditConditionHides, EditCondition = "SubToolType == EClothEditorWeightMapPaintInteractionType::Brush || SubToolType == EClothEditorWeightMapPaintInteractionType::Fill"))` — The Region affected by the current operation will be bounded by Hard Normal edges/seams
- L206 _public member_ `EClothEditorWeightMapPaintVisibilityType VisibilityFilter = EClothEditorWeightMapPaintVisibilityType::None;` — `UPROPERTY(EditAnywhere, Category = Filters, meta = (HideEditConditionToggle, EditConditionHides, EditCondition = "SubToolType == EClothEditorWeightMapPaintInteractionType::Brush || SubToolType == EClothEditorWeightMapPaintInteractionType::Fill || SubToolType == EClothEditorWeightMapPaintInteractionType::PolyLasso"))` — Control which triangles can be affected by the current operation based on visibility. Applied after all other filters.
- L211 _public member_ `double ValueAtBrush = 0;` — `UPROPERTY(VisibleAnywhere, Transient, Category = Query, meta = (NoResetToDefault, HideEditConditionToggle, EditConditionHides, EditCondition = "SubToolType == EClothEditorWeightMapPaintInteractionType::Brush || SubToolType == EClothEditorWeightMapPaintInteractionType::Fill"))` — The weight value at the brush indicator
- L216 _public member_ `EClothEditorWeightMapPaintQueryType ValueAtBrushQueryType = EClothEditorWeightMapPaintQueryType::NearestVertexFast;` — `UPROPERTY(EditAnywhere, Transient, Category = Query, meta = (HideEditConditionToggle, EditConditionHides, EditCondition = "SubToolType == EClothEditorWeightMapPaintInteractionType::Brush || SubToolType == EClothEditorWeightMapPaintInteractionType::Fill"))` — How to compute the value under brush indicator

#### enum `EClothEditorWeightMapPaintToolActions`  
`enum class EClothEditorWeightMapPaintToolActions`  
_L225-234_
- reflection: `UENUM()`
- L227 _public enumerator_ `NoAction`
- L229 _public enumerator_ `FloodFillCurrent`
- L230 _public enumerator_ `ClearAll`
- L231 _public enumerator_ `Invert`
- L232 _public enumerator_ `Multiply`
- L233 _public enumerator_ `ClearHiddenTriangles`

#### class `UClothEditorMeshWeightMapPaintToolActions`  
`class UClothEditorMeshWeightMapPaintToolActions : public UInteractiveToolPropertySet`  
_L238-274_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveToolPropertySet`
- L244 _public member_ `TWeakObjectPtr<UClothEditorWeightMapPaintTool> ParentTool;`
- L246 _public function_ `void Initialize(UClothEditorWeightMapPaintTool* ParentToolIn)`
- L248 _public prototype_ `void PostAction(EClothEditorWeightMapPaintToolActions Action);`
- L251 _public function_ `void ClearAll()` — `UFUNCTION(CallInEditor, Category = Operations, meta = (DisplayPriority = 10))`
- L257 _public function_ `void FloodFillCurrent()` — `UFUNCTION(CallInEditor, Category = Operations, meta = (DisplayPriority = 12))`
- L263 _public function_ `void Invert()` — `UFUNCTION(CallInEditor, Category = Operations, meta = (DisplayPriority = 13))`
- L269 _public function_ `void Multiply()` — `UFUNCTION(CallInEditor, Category = Operations, meta = (DisplayPriority = 14))`

#### class `UClothEditorUpdateWeightMapProperties`  
`class UClothEditorUpdateWeightMapProperties : public UInteractiveToolPropertySet`  
_L277-292_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveToolPropertySet`
- L284 _public member_ `FString Name;` — `UPROPERTY(EditAnywhere, Category = UpdateNode, meta = (DisplayName = "Name"))`
- L287 _public member_ `EChaosClothAssetWeightMapOverrideType MapOverrideType;` — `UPROPERTY(EditAnywhere, Category = UpdateNode)`
- L291 _private prototype_ `virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;`

#### class `UClothEditorMeshWeightMapPaintToolShowHideProperties`  
`class UClothEditorMeshWeightMapPaintToolShowHideProperties : public UInteractiveToolPropertySet`  
_L296-316_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveToolPropertySet`
- desc: Property panel for controlling hiding triangles
- L302 _public member_ `TWeakObjectPtr<UClothEditorWeightMapPaintTool> ParentTool;`
- L303 _public function_ `void Initialize(UClothEditorWeightMapPaintTool* ParentToolIn)`
- L304 _public prototype_ `void PostAction(EClothEditorWeightMapPaintToolActions Action);`
- L308 _public member_ `TMap<int32, bool> ShowPatterns;` — `UPROPERTY(EditAnywhere, EditFixedSize, Transient, Category = TriangleVisibility, meta = (DisplayPriority = 2))` — Toggles whether each pattern is shown or hidden
- L312 _public function_ `void ShowAll()` — `UFUNCTION(CallInEditor, Category = TriangleVisibility, meta = (DisplayPriority = 1))` — Unhide all triangles

#### class `UClothEditorWeightMapPaintTool`  
`class UClothEditorWeightMapPaintTool : public UMeshSculptToolBase`  
_L323-628_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMeshSculptToolBase`
- desc: Mesh Element Paint Tool Class
- L328 _public prototype_ `virtual void RegisterActions(FInteractiveToolActionSet& ActionSet) override;`
- L330 _public prototype_ `virtual void Setup() override;`
- L331 _public prototype_ `virtual void Shutdown(EToolShutdownType ShutdownType) override;`
- L332 _public prototype_ `virtual void DrawHUD(FCanvas* Canvas, IToolsContextRenderAPI* RenderAPI) override;`
- L333 _public prototype_ `virtual void Render(IToolsContextRenderAPI* RenderAPI) override;`
- L334 _public prototype_ `virtual void UpdateMaterialMode(EMeshEditingMaterialModes MaterialMode) override;`
- L336 _public prototype_ `virtual void OnTick(float DeltaTime) override;`
- L338 _public function_ `virtual bool HasCancel() const override`
- L339 _public function_ `virtual bool HasAccept() const override`
- L340 _public prototype_ `virtual bool CanAccept() const override;`
- L342 _public prototype_ `virtual bool OnUpdateHover(const FInputDeviceRay& DevicePos) override;`
- L344 _public prototype_ `virtual void OnPropertyModified(UObject* PropertySet, FProperty* Property) override;`
- L346 _public prototype_ `bool IsInBrushSubMode() const;`
- L348 _public prototype_ `virtual void CommitResult(UBaseDynamicMeshComponent* Component, bool bModifiedTopology) override;`
- L350 _public prototype_ `void SetDataflowContextObject(TObjectPtr<UDataflowContextObject> InDataflowContextObject);`
- L352 _public prototype_ `virtual void SetupBrushEditBehaviorSetup(ULocalTwoAxisPropertyEditInputBehavior& OutBehavior) override;`
- L357 _private prototype_ `void InitializeSculptMeshFromTarget();` — Initialization support
- L358 _private prototype_ `void UpdateShowHideProperties();`
- L361 _private prototype_ `void PostSetupCheck() const;` — Make sure things are set up correctly after initialization or re-initialization
- L368 _public member_ `TObjectPtr<UClothEditorWeightMapPaintBrushFilterProperties> FilterProperties;` — `UPROPERTY()` — Filters on paint brush
- L373 _private member_ `TObjectPtr<UWeightMapPaintBrushOpProps> PaintBrushOpProperties;` — `UPROPERTY()`
- L376 _private member_ `TObjectPtr<UWeightMapSmoothBrushOpProps> SmoothBrushOpProperties;` — `UPROPERTY()`
- L379 _private member_ `TObjectPtr<UWeightMapEraseBrushOpProps> EraseBrushOpProperties;` — `UPROPERTY()`
- L381 _private prototype_ `void FloodFillCurrentWeightAction();`
- L382 _private prototype_ `void ClearAllWeightsAction();`
- L383 _private prototype_ `void InvertWeightsAction();`
- L384 _private prototype_ `void MultiplyWeightsAction();`
- L385 _private prototype_ `void ClearHiddenAction();`
- L388 _public prototype_ `void SetVerticesToWeightMap(const TSet<int32>& Vertices, double WeightValue, bool bIsErase);`
- L390 _public prototype_ `bool HaveVisibilityFilter() const;`
- L391 _public prototype_ `void ApplyVisibilityFilter(const TArray<int32>& Vertices, TArray<int32>& VisibleVertices);`
- L392 _public prototype_ `void ApplyVisibilityFilter(TSet<int32>& Triangles, TArray<int32>& ROIBuffer, TArray<int32>& OutputBuffer);`
- L395 _public prototype_ `virtual void IncreaseBrushRadiusAction();` — we override these so we can update the separate BrushSize property added for this tool
- L396 _public prototype_ `virtual void DecreaseBrushRadiusAction();`
- L397 _public prototype_ `virtual void IncreaseBrushRadiusSmallStepAction();`
- L398 _public prototype_ `virtual void DecreaseBrushRadiusSmallStepAction();`
- L402 _protected function_ `virtual UBaseDynamicMeshComponent* GetSculptMeshComponent()` — UMeshSculptToolBase API
- L403 _protected function_ `virtual FDynamicMesh3* GetBaseMesh()`
- L404 _protected function_ `virtual const FDynamicMesh3* GetBaseMesh() const`
- L406 _protected prototype_ `virtual int32 FindHitSculptMeshTriangleConst(const FRay3d& LocalRay) const override;`
- L407 _protected prototype_ `virtual int32 FindHitTargetMeshTriangleConst(const FRay3d& LocalRay) const override;`
- L408 _protected prototype_ `virtual void UpdateHitSculptMeshTriangle(int32 TriangleID, const FRay3d& LocalRay) override;`
- L411 _protected prototype_ `virtual void OnBeginStroke(const FRay& WorldRay) override;`
- L412 _protected prototype_ `virtual void OnCancelStroke() override;`
- L413 _protected prototype_ `virtual void OnEndStroke() override;`
- L415 _protected prototype_ `virtual TUniquePtr<FMeshSculptBrushOp>& GetActiveBrushOp();`
- L417 _protected function_ `virtual bool SharesBrushPropertiesChanges() const override`
- L419 _protected prototype_ `virtual void InitializeBrushSizeRange(const UE::Geometry::FAxisAlignedBox3d& TargetBounds) override;`
- L421 _protected prototype_ `virtual void NextBrushModeAction() override;`
- L422 _protected prototype_ `virtual void PreviousBrushModeAction() override;`
- L425 _protected prototype_ `virtual void IncreaseBrushSpeedAction() override;` — Note: these will actually modify the brush's Attribute Value since we don't use Speed in our brush
- L426 _protected prototype_ `virtual void DecreaseBrushSpeedAction() override;`
- L438 _public prototype_ `virtual void RequestAction(EClothEditorWeightMapPaintToolActions ActionType);`
- L441 _public member_ `TObjectPtr<UClothEditorMeshWeightMapPaintToolActions> ActionsProps;` — `UPROPERTY()`
- L444 _public member_ `TObjectPtr<UClothEditorUpdateWeightMapProperties> UpdateWeightMapProperties;` — `UPROPERTY()`
- L447 _protected member_ `bool bHavePendingAction = false;`
- L448 _protected member_ `EClothEditorWeightMapPaintToolActions PendingAction;`
- L449 _protected prototype_ `virtual void ApplyAction(EClothEditorWeightMapPaintToolActions ActionType);`
- L458 _public member_ `TObjectPtr<UPolyLassoMarqueeMechanic> PolyLassoMechanic;` — `UPROPERTY()`
- L461 _protected prototype_ `void OnPolyLassoFinished(const FCameraPolyLasso& Lasso, bool bCanceled);`
- L468 _protected member_ `TObjectPtr<UPolygonSelectionMechanic> PolygonSelectionMechanic;` — `UPROPERTY()` — Gradient Support
- L470 _protected member_ `TUniquePtr<UE::Geometry::FDynamicMeshAABBTree3> MeshSpatial = nullptr;`
- L472 _protected member_ `TUniquePtr<UE::Geometry::FTriangleGroupTopology> GradientSelectionTopology = nullptr;`
- L474 _protected member_ `FToolDataVisualizer GradientSelectionRenderer;`
- L476 _protected member_ `UE::Geometry::FGroupTopologySelection LowValueGradientVertexSelection;`
- L477 _protected member_ `UE::Geometry::FGroupTopologySelection HighValueGradientVertexSelection;`
- L479 _protected prototype_ `void ComputeGradient();`
- L480 _protected prototype_ `void OnSelectionModified();`
- L488 _protected member_ `TObjectPtr<UClothEditorMeshWeightMapPaintToolShowHideProperties> ShowHideProperties;` — `UPROPERTY()`
- L491 _protected member_ `TSet<int32> HiddenTriangles;` — Hidden triangles are not rendered, their wireframes are not rendered, and they don't block ray casts from the mouse
- L499 _protected member_ `TSet<int32> PendingHiddenTriangles;` — Pending hidden triangles are triangles that are selected by the current HideTriangles brush stroke. When the stroke finishes, these pending triangles are added to the set of hidden triangles, and this set is cleared. Pending hidden triangles are not rendered, but their wireframes *are* rendered, and they *do* block ray casts. - Wireframe update is delayed because its a relatively expensive operation, so we do it only when the stroke finishes - Ray cast blocking is delayed because otherwise one small mouse drag would drill through multiple mesh layers
- L502 _protected member_ `TArray<TPair<int32, int32>> PatternTriangleOffsetAndNum;` — Triangle index offset and number of triangles for each non-empty pattern. This is used when we want to hide/show entire patterns.
- L511 _protected member_ `TObjectPtr<AInternalToolFrameworkActor> PreviewMeshActor = nullptr;` — `UPROPERTY()`
- L514 _protected member_ `TObjectPtr<UDynamicMeshComponent> DynamicMeshComponent;` — `UPROPERTY()`
- L517 _protected member_ `TObjectPtr<UMeshElementsVisualizer> MeshElementsDisplay;` — `UPROPERTY()`
- L520 _protected member_ `TObjectPtr<UDataflowContextObject> DataflowContextObject = nullptr;` — `UPROPERTY()`
- L523 _protected prototype_ `void OnDynamicMeshComponentChanged(UDynamicMeshComponent* Component, const FMeshVertexChange* Change, bool bRevert);` — realtime visualization
- L524 _protected member_ `FDelegateHandle OnDynamicMeshComponentChangedHandle;`
- L526 _protected member_ `TConstArrayView<float> InputWeightMap;`
- L528 _protected member_ `UE::Geometry::FDynamicMeshWeightAttribute* ActiveWeightMap;`
- L529 _protected prototype_ `double GetCurrentWeightValue(int32 VertexId) const;`
- L530 _protected prototype_ `double GetCurrentWeightValueUnderBrush() const;`
- L531 _protected member_ `FVector3d CurrentBaryCentricCoords;`
- L532 _protected prototype_ `int32 GetBrushNearestVertex() const;`
- L533 _protected prototype_ `int32 GetBrushNearestVertexAccurate() const;`
- L535 _protected prototype_ `void GetCurrentWeightMap(TArray<float>& OutWeights) const;`
- L537 _protected prototype_ `void UpdateSubToolType(EClothEditorWeightMapPaintInteractionType NewType);`
- L539 _protected prototype_ `void UpdateBrushType(EClothEditorWeightMapPaintBrushType BrushType);`
- L541 _protected member_ `TSet<int32> AccumulatedTriangleROI;`
- L542 _protected member_ `bool bUndoUpdatePending = false;`
- L543 _protected member_ `TArray<int> NormalsBuffer;`
- L544 _protected prototype_ `void WaitForPendingUndoRedoUpdate();`
- L546 _protected member_ `TArray<int> TempROIBuffer;`
- L547 _protected member_ `TArray<int> VertexROI;`
- L548 _protected member_ `TArray<bool> VisibilityFilterBuffer;`
- L549 _protected member_ `TSet<int> VertexSetBuffer;`
- L550 _protected member_ `TSet<int> TriangleROI;`
- L551 _protected prototype_ `void UpdateROI(const FSculptBrushStamp& CurrentStamp);`
- L553 _protected member_ `EClothEditorWeightMapPaintBrushType PendingStampType = EClothEditorWeightMapPaintBrushType::Paint;`
- L555 _protected prototype_ `bool UpdateStampPosition(const FRay& WorldRay);`
- L556 _protected prototype_ `bool ApplyStamp();`
- L558 _protected member_ `UE::Geometry::FDynamicMeshOctree3 Octree;`
- L560 _protected prototype_ `bool UpdateBrushPosition(const FRay& WorldRay);`
- L562 _protected function_ `bool GetInEraseStroke()`
- L569 _protected member_ `bool bPendingPickWeight = false;`
- L571 _protected member_ `TArray<int32> ROITriangleBuffer;`
- L572 _protected member_ `TArray<double> ROIWeightValueBuffer;`
- L573 _protected prototype_ `bool SyncMeshWithWeightBuffer(FDynamicMesh3* Mesh);`
- L574 _protected prototype_ `bool SyncWeightBufferWithMesh(const FDynamicMesh3* Mesh);`
- L587 _protected member_ `TUniquePtr<TIndexedValuesChangeBuilder<float, FNodeBufferWeightChange>> ActiveChangeBuilder;`
- L588 _protected prototype_ `void BeginChange();`
- L589 _protected prototype_ `void EndChange();`
- L594 _protected prototype_ `int32 MeshIndexToNodeIndex(int32 MeshVertexIndex) const;` — The corresponding FChaosClothAssetWeightMapNode has a buffer of scalar weights. Depending on bHaveDynamicMeshToWeightConversion, the indexing of this buffer might be different than the mesh vertex indexing. This function returns the corresponding index in the node buffer for a given mesh vertex index.
- L597 _protected prototype_ `void UpdateMapValuesFromNodeValues(const TArray<int32>& Indices, const TArray<float>& Values);` — Update the active weight map attribute from the map of indices/values. The inputs are given in "node buffer format" (see function above).
- L600 _protected prototype_ `FColor GetColorForWeightValue(double WeightValue);`
- L602 _protected member_ `TArray<FVector3d> TriNormals;`
- L603 _protected member_ `TArray<int32> UVSeamEdges;`
- L604 _protected member_ `TArray<int32> NormalSeamEdges;`
- L605 _protected prototype_ `void PrecomputeFilterData();`
- L608 _protected member_ `bool bHaveDynamicMeshToWeightConversion = false;` — DynamicMesh might be unwelded mesh, but weights are on the welded mesh.
- L609 _protected member_ `TArray<int32> DynamicMeshToWeight;`
- L610 _protected member_ `TArray<TArray<int32>> WeightToDynamicMesh;`
- L613 _protected function_ `virtual bool ShowWorkPlane() const override`
- L616 _protected prototype_ `void NotifyTargetChanged();`
- L618 _protected member_ `bool bAnyChangeMade = false;`
- L622 _protected member_ `FChaosClothAssetWeightMapNode* WeightMapNodeToUpdate = nullptr;`
- L624 _protected prototype_ `void UpdateSelectedNode();`
- L626 _protected prototype_ `void UpdateVertexColorOverlay(const TSet<int>* TrianglesToUpdate = nullptr);`

#### class `UClothEditorWeightMapPaintTool::FNodeBufferWeightChange`  
`class FNodeBufferWeightChange : public TCustomIndexedValuesChange<float, int32>`  
_L579-586_
- inherits: `TCustomIndexedValuesChange<float,int32>`
- L582 _public function_ `virtual FString ToString() const override`

#### Free symbols / members of external scopes

- L29 _macro_ `#define UE_API CHAOSCLOTHASSETEDITORTOOLS_API`
- L40 _delegate_ `DECLARE_STATS_GROUP(TEXT("WeightMapPaintTool"), STATGROUP_WeightMapPaintTool,`

### `Plugins/ChaosClothAssetEditorCore/Source/ChaosClothAssetEditorTools/Public/ChaosClothAsset/ClothEditorContextObject.h` (Public)


#### class `UClothEditorContextObject`  
`class UE_DEPRECATED(5.6, "Use UDataflowContextObject instead") UClothEditorContextObject : public UObject`  
_L24-106_
- reflection: `UCLASS()`
- inherits: `UObject`
- L29 _public prototype_ `void Init(TWeakPtr<SDataflowGraphEditor> DataflowGraphEditor, TWeakPtr<UE::Dataflow::FEngineContext> DataflowContext, UE::Chaos::ClothAsset::EClothPatternVertexType InConstructionViewMode, TWeakPtr<FManagedArrayCollection> SelectedClothCollection, bool bInUsingInputCollection);`
- L32 _public function_ `void Init(TWeakPtr<SDataflowGraphEditor> InDataflowGraphEditor, UE::Chaos::ClothAsset::EClothPatternVertexType InConstructionViewMode, TWeakPtr<FManagedArrayCollection> InSelectedClothCollection, TWeakPtr<FManagedArrayCollection> InSelectedInputClothCollection = nullptr)` — `UE_DEPRECATED(5.5, "Use the Init with a DataflowContext")`
- L41 _public function_ `template<typename NodeType> NodeType* GetSingleSelectedNodeOfType() const` — Get a single selected node of the specified type. Return nullptr if the specified node is not selected, or if multiple nodes are selected
- L60 _public function_ `TWeakPtr<UE::Dataflow::FEngineContext> GetDataflowContext() const`
- L65 _public function_ `void SetDataflowContext(TWeakPtr<UE::Dataflow::FEngineContext> InDataflowContext)`
- L70 _public function_ `UDataflow* GetDataflowAsset() const`
- L85 _public prototype_ `void SetClothCollection(UE::Chaos::ClothAsset::EClothPatternVertexType ViewMode, TWeakPtr<FManagedArrayCollection> ClothCollection, bool bInUsingInputCollection);`
- L88 _public function_ `void SetClothCollection(UE::Chaos::ClothAsset::EClothPatternVertexType ViewMode, TWeakPtr<FManagedArrayCollection> ClothCollection, TWeakPtr<FManagedArrayCollection> InputClothCollection = nullptr)` — `UE_DEPRECATED(5.5, "SetClothCollection no longer takes a separate InputClothCollection argument")`
- L93 _public function_ `const TWeakPtr<const FManagedArrayCollection> GetSelectedClothCollection() const`
- L95 _public function_ `const TWeakPtr<const FManagedArrayCollection> GetSelectedInputClothCollection() const` — `UE_DEPRECATED(5.5, "There is no longer a separate input cloth collection.")`
- L96 _public function_ `UE::Chaos::ClothAsset::EClothPatternVertexType GetConstructionViewMode() const`
- L97 _public function_ `bool IsUsingInputCollection() const`
- L100 _private member_ `TWeakPtr<SDataflowGraphEditor> DataflowGraphEditor;`
- L101 _private member_ `TWeakPtr<UE::Dataflow::FEngineContext> DataflowContext;`
- L103 _private member_ `UE::Chaos::ClothAsset::EClothPatternVertexType ConstructionViewMode;`
- L104 _private member_ `TWeakPtr<const FManagedArrayCollection> SelectedClothCollection;`
- L105 _private member_ `bool bUsingInputCollection = false;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace Dataflow`
- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace Chaos` (scope `UE`)
- L16 _namespace_ `namespace ClothAsset` (scope `UE::Chaos`)

### `Plugins/ChaosClothAssetEditorCore/Source/ChaosClothAssetEditorTools/Public/ChaosClothAsset/ClothEditorToolBuilders.h` (Public)


#### class `UChaosClothAssetEditorToolBuilder`  
`class UChaosClothAssetEditorToolBuilder : public UInterface`  
_L29-32_
- reflection: `UINTERFACE(MinimalAPI)`
- inherits: `UInterface`

#### class `IChaosClothAssetEditorToolBuilder`  
`class IChaosClothAssetEditorToolBuilder`  
_L35-49_
- L42 _public function_ `virtual void GetSupportedViewModes(TArray<UE::Chaos::ClothAsset::EClothPatternVertexType>& Modes) const` — `UE_DEPRECATED(5.5, "Please use the version taking ContextObject")`
- L45 _public prototype_ `virtual void GetSupportedViewModes(const UDataflowContextObject& ContextObject, TArray<UE::Chaos::ClothAsset::EClothPatternVertexType>& Modes) const = 0;` — Returns all Construction View modes that this tool can operate in. The first element should be the preferred mode to switch to if necessary.
- L48 _public function_ `virtual bool CanSetConstructionViewWireframeActive() const` — Returns whether or not view can be set to wireframe when this tool is active..

#### class `UClothEditorWeightMapPaintToolBuilder`  
`class UClothEditorWeightMapPaintToolBuilder : public UMeshSurfacePointMeshEditingToolBuilder, public IChaosClothAssetEditorToolBuilder, public IDataflowEditorToolBuilder`  
_L53-72_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMeshSurfacePointMeshEditingToolBuilder,IChaosClothAssetEditorToolBuilder,IDataflowEditorToolBuilder`
- L60 _private prototype_ `virtual void GetSupportedConstructionViewModes(const UDataflowContextObject& ContextObject, TArray<const UE::Dataflow::IDataflowConstructionViewMode*>& Modes) const override;` — IDataflowEditorToolBuilder
- L61 _private prototype_ `virtual bool CanSceneStateChange(const UInteractiveTool* ActiveTool, const FToolBuilderState& SceneState) const override;`
- L62 _private prototype_ `virtual void SceneStateChanged(UInteractiveTool* ActiveTool, const FToolBuilderState& SceneState) override;`
- L65 _private prototype_ `virtual void GetSupportedViewModes(const UDataflowContextObject& ContextObject, TArray<UE::Chaos::ClothAsset::EClothPatternVertexType>& Modes) const override;` — IChaosClothAssetEditorToolBuilder
- L66 _private function_ `virtual bool CanSetConstructionViewWireframeActive() const`
- L69 _private prototype_ `virtual bool CanBuildTool(const FToolBuilderState& SceneState) const override;` — UMeshSurfacePointMeshEditingToolBuilder
- L71 _private prototype_ `virtual UMeshSurfacePointTool* CreateNewTool(const FToolBuilderState& SceneState) const override;`

#### class `UClothMeshSelectionToolBuilder`  
`class UClothMeshSelectionToolBuilder : public UInteractiveToolWithToolTargetsBuilder, public IChaosClothAssetEditorToolBuilder, public IDataflowEditorToolBuilder`  
_L76-97_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveToolWithToolTargetsBuilder,IChaosClothAssetEditorToolBuilder,IDataflowEditorToolBuilder`
- L80 _private function_ `virtual void GetSupportedViewModes(TArray<UE::Chaos::ClothAsset::EClothPatternVertexType>& Modes) const override`
- L85 _private prototype_ `virtual void GetSupportedConstructionViewModes(const UDataflowContextObject& ContextObject, TArray<const UE::Dataflow::IDataflowConstructionViewMode*>& Modes) const override;` — IDataflowEditorToolBuilder
- L86 _private prototype_ `virtual bool CanSceneStateChange(const UInteractiveTool* ActiveTool, const FToolBuilderState& SceneState) const override;`
- L87 _private prototype_ `virtual void SceneStateChanged(UInteractiveTool* ActiveTool, const FToolBuilderState& SceneState) override;`
- L90 _private prototype_ `virtual void GetSupportedViewModes(const UDataflowContextObject& ContextObject, TArray<UE::Chaos::ClothAsset::EClothPatternVertexType>& Modes) const override;` — IChaosClothAssetEditorToolBuilder
- L91 _private function_ `virtual bool CanSetConstructionViewWireframeActive() const`
- L94 _private prototype_ `virtual bool CanBuildTool(const FToolBuilderState& SceneState) const override;` — UInteractiveToolWithToolTargetsBuilder
- L95 _private prototype_ `virtual UInteractiveTool* BuildTool(const FToolBuilderState& SceneState) const override;`
- L96 _private prototype_ `virtual const FToolTargetTypeRequirements& GetTargetRequirements() const override;`

#### class `UClothTransferSkinWeightsToolBuilder`  
`class UClothTransferSkinWeightsToolBuilder : public USingleSelectionMeshEditingToolBuilder, public IChaosClothAssetEditorToolBuilder, public IDataflowEditorToolBuilder`  
_L100-116_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `USingleSelectionMeshEditingToolBuilder,IChaosClothAssetEditorToolBuilder,IDataflowEditorToolBuilder`
- L107 _private prototype_ `virtual void GetSupportedConstructionViewModes(const UDataflowContextObject& ContextObject, TArray<const UE::Dataflow::IDataflowConstructionViewMode*>& Modes) const override;` — IDataflowEditorToolBuilder
- L108 _private prototype_ `virtual bool CanSceneStateChange(const UInteractiveTool* ActiveTool, const FToolBuilderState& SceneState) const override;`
- L109 _private prototype_ `virtual void SceneStateChanged(UInteractiveTool* ActiveTool, const FToolBuilderState& SceneState) override;`
- L112 _private prototype_ `virtual void GetSupportedViewModes(const UDataflowContextObject& ContextObject, TArray<UE::Chaos::ClothAsset::EClothPatternVertexType>& Modes) const override;` — IChaosClothAssetEditorToolBuilder
- L115 _private prototype_ `virtual USingleSelectionMeshEditingTool* CreateNewTool(const FToolBuilderState& SceneState) const override;` — USingleSelectionMeshEditingToolBuilder

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API CHAOSCLOTHASSETEDITORTOOLS_API`
- L17 _namespace_ `namespace UE`
- L17 _namespace_ `namespace Dataflow` (scope `UE`)
- L22 _namespace_ `namespace UE`
- L22 _namespace_ `namespace Chaos` (scope `UE`)
- L22 _namespace_ `namespace ClothAsset` (scope `UE::Chaos`)
- L119 _namespace_ `namespace UE`
- L119 _namespace_ `namespace Chaos` (scope `UE`)
- L119 _namespace_ `namespace ClothAsset` (scope `UE::Chaos`)
- L122 _prototype_ `void GetClothEditorToolDefaultObjectList(TArray<UInteractiveTool*>& ToolCDOs);` (scope `UE::Chaos::ClothAsset`) — Provide a list of Tool default objects for us in TInteractiveToolCommands::RegisterCommands()
- L125 _prototype_ `EClothPatternVertexType DataflowViewModeToClothViewMode(const UE::Dataflow::IDataflowConstructionViewMode* DataflowViewMode);` (scope `UE::Chaos::ClothAsset`) — Mapping from Dataflow View Mode to Cloth View Mode. Input object must be one of FCloth2DSimViewMode, FCloth3DSimViewMode, or FClothRenderViewMode, defined in ClothDataflowViewModes.h
- L128 _prototype_ `FName ClothViewModeToDataflowViewModeName(EClothPatternVertexType ClothViewMode);` (scope `UE::Chaos::ClothAsset`) — Mapping from Cloth View Mode to Dataflow View Mode name. Ouptut will be one of "Cloth2DSimView", "Cloth3DSimView", or "ClothRenderView", as defined in ClothDataflowViewModes.cpp
