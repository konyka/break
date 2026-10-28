# Plugins / MeshResizingEditorTools

- module root: `Plugins/Experimental/MeshResizing/Source/MeshResizingEditorTools`
- headers: 2; symbols: 56
- symbol kinds: class=7, function=7, macro=1, member=16, namespace=2, prototype=22, struct=1
- PrivateDependencyModuleNames: DataflowCore, DataflowEditor, DataflowEngine, DynamicMesh, GeometryFramework, InteractiveToolsFramework, MeshModelingTools, MeshResizingCore, MeshResizingDataflowNodes, ModelingComponents, Slate, SlateCore
- PublicDependencyModuleNames: Core, CoreUObject, Engine, GeometryCore, UnrealEd
- PublicIncludePathModuleNames: 

### `Plugins/Experimental/MeshResizing/Source/MeshResizingEditorTools/Private/MeshResizing/MeshResizingToolActionCommandBindings.h` (Private)


#### class `FMeshResizingToolActionCommands`  
`template<typename T, typename ToolClass> class FMeshResizingToolActionCommands : public TInteractiveToolCommands<T>`  
_L21-31_
- inherits: `TInteractiveToolCommands<T>`
- L24 _public function_ `FMeshResizingToolActionCommands(const FName InContextName, const FText& InContextDesc) : TInteractiveToolCommands<T>(InContextName, InContextDesc, NAME_None, FAppStyle::GetAppStyleSetName())`
- L27 _public function_ `virtual void GetToolDefaultObjectList(TArray<UInteractiveTool*>& ToolCDOs) override`

#### class `FMeshWrapLandmarkSelectionToolActionCommands`  
`class FMeshWrapLandmarkSelectionToolActionCommands : public FMeshResizingToolActionCommands<FMeshWrapLandmarkSelectionToolActionCommands, UMeshWrapLandmarkSelectionTool>`  
_L35-39_
- inherits: `FMeshResizingToolActionCommands<FMeshWrapLandmarkSelectionToolActionCommands,UMeshWrapLandmarkSelectionTool>`
- L38 _public prototype_ `FMeshWrapLandmarkSelectionToolActionCommands();`

#### class `FMeshResizingToolActionCommandBindings`  
`class FMeshResizingToolActionCommandBindings : public UE::Dataflow::FDataflowToolRegistry::IDataflowToolActionCommands`  
_L43-50_
- inherits: `UE::Dataflow::FDataflowToolRegistry::IDataflowToolActionCommands`
- L47 _public prototype_ `FMeshResizingToolActionCommandBindings();`
- L48 _public prototype_ `virtual void UnbindActiveCommands(const TSharedPtr<FUICommandList>& UICommandList) const override;`
- L49 _public prototype_ `virtual void BindCommandsForCurrentTool(const TSharedPtr<FUICommandList>& UICommandList, UInteractiveTool* Tool) const override;`

### `Plugins/Experimental/MeshResizing/Source/MeshResizingEditorTools/Private/MeshResizing/MeshWrapLandmarkSelectionTool.h` (Private)


#### class `UMeshWrapLandmarkSelectionMechanic`  
`class UMeshWrapLandmarkSelectionMechanic : public UPolygonSelectionMechanic`  
_L23-35_
- reflection: `UCLASS()`
- inherits: `UPolygonSelectionMechanic`
- L27 _public prototype_ `virtual bool UpdateSelection(const FRay& WorldRay, FVector3d& LocalHitPositionOut, FVector3d& LocalHitNormalOut) override;`
- L29 _public function_ `bool GetHadShiftOnSelection() const`
- L30 _public function_ `bool GetHadCtrlOnSelection() const`
- L33 _private member_ `bool bHadShiftOnSelection = false;`
- L34 _private member_ `bool bHadCtrlOnSelection = false;`

#### struct `FMeshWrapToolLandmark`  
`struct FMeshWrapToolLandmark`  
_L41-56_
- reflection: `USTRUCT()`
- desc: Mesh Wrap Landmark Selection Tool Landmark
- L47 _public member_ `FString Identifier = TEXT("");` — `UPROPERTY(EditAnywhere, Category = "Mesh Wrap")` — Landmarks will be matched by comparing Identifiers
- L50 _public member_ `int32 VertexIndex = INDEX_NONE;` — `UPROPERTY(VisibleAnywhere, Category = "Mesh Wrap", Meta = (ClampMin = "-1"))`
- L52 _public function_ `bool operator==(const FMeshWrapToolLandmark& Other) const`

#### class `UMeshWrapLandmarkSelectionToolProperties`  
`class UMeshWrapLandmarkSelectionToolProperties : public UInteractiveToolPropertySet`  
_L60-79_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveToolPropertySet`
- L67 _public member_ `TArray<FMeshWrapToolLandmark> Landmarks;` — `UPROPERTY(EditAnywhere, Category = Landmarks, EditFixedSize, Transient)` — Landmark names
- L71 _public member_ `int32 CurrentEditableLandmark = INDEX_NONE;` — `UPROPERTY(EditAnywhere, Category = Landmarks, Meta = (ClampMin = "-1"))` — Currently editable landmark. Set to -1 or hold the Shift key to add a new landmark. Hold the Ctrl key and select an existing landmark to set this value.
- L74 _public member_ `bool bShowVertices = false;` — `UPROPERTY(EditAnywhere, Category = Visualization, meta = (DisplayName = "Show Vertices"))`
- L77 _public member_ `bool bShowEdges = false;` — `UPROPERTY(EditAnywhere, Category = Visualization, meta = (DisplayName = "Show Edges"))`

#### class `UMeshWrapLandmarkSelectionTool`  
`class UMeshWrapLandmarkSelectionTool : public USingleSelectionMeshEditingTool`  
_L82-134_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `USingleSelectionMeshEditingTool`
- L88 _public prototype_ `int32 GetFirstLandmarkWithID(const int32 Id) const;`
- L94 _private prototype_ `virtual void Setup() override;`
- L95 _private prototype_ `virtual void OnShutdown(EToolShutdownType ShutdownType) override;`
- L96 _private prototype_ `virtual void Render(IToolsContextRenderAPI* RenderAPI) override;`
- L97 _private prototype_ `virtual void DrawHUD(FCanvas* Canvas, IToolsContextRenderAPI* RenderAPI) override;`
- L99 _private function_ `virtual bool HasCancel() const override`
- L100 _private function_ `virtual bool HasAccept() const override`
- L101 _private prototype_ `virtual bool CanAccept() const override;`
- L104 _private prototype_ `virtual FBox GetWorldSpaceFocusBox() override;` — IInteractiveToolCameraFocusAPI implementation
- L106 _private prototype_ `void SetDataflowContextObject(TObjectPtr<UDataflowContextObject> InDataflowContextObject);`
- L108 _private prototype_ `void UpdateSelectedNode();`
- L109 _private prototype_ `void InitializeSculptMeshFromTarget();`
- L110 _private prototype_ `void SetPropertiesFromSelectedNode();`
- L111 _private prototype_ `void SetCurrentEditableLandmark(int32 Index);`
- L112 _private prototype_ `void UpdateLandmarkFromSelection();`
- L115 _private member_ `TObjectPtr<UMeshWrapLandmarkSelectionToolProperties> ToolProperties;` — `UPROPERTY()`
- L118 _private member_ `TObjectPtr<UPreviewMesh> PreviewMesh = nullptr;` — `UPROPERTY()`
- L121 _private member_ `TObjectPtr<UMeshWrapLandmarkSelectionMechanic> SelectionMechanic = nullptr;` — `UPROPERTY()`
- L124 _private member_ `TObjectPtr<UDataflowContextObject> DataflowContextObject = nullptr;` — `UPROPERTY()`
- L126 _private member_ `TUniquePtr<UE::Geometry::FGroupTopology> Topology;`
- L128 _private member_ `bool bAnyChangeMade = false;`
- L130 _private member_ `FMeshWrapLandmarksNode* SelectionNodeToUpdate = nullptr;`
- L132 _private member_ `FToolDataVisualizer LandmarkVisualizer;`

#### class `UMeshWrapLandmarkSelectionToolBuilder`  
`class UMeshWrapLandmarkSelectionToolBuilder : public UInteractiveToolWithToolTargetsBuilder, public IDataflowEditorToolBuilder`  
_L138-151_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveToolWithToolTargetsBuilder,IDataflowEditorToolBuilder`
- L145 _private prototype_ `virtual void GetSupportedConstructionViewModes(const UDataflowContextObject& ContextObject, TArray<const UE::Dataflow::IDataflowConstructionViewMode*>& Modes) const override;` — IDataflowEditorToolBuilder
- L148 _private prototype_ `virtual bool CanBuildTool(const FToolBuilderState& SceneState) const override;` — UInteractiveToolWithToolTargetsBuilder
- L149 _private prototype_ `virtual UInteractiveTool* BuildTool(const FToolBuilderState& SceneState) const override;`
- L150 _private prototype_ `virtual const FToolTargetTypeRequirements& GetTargetRequirements() const override;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API MESHRESIZINGEDITORTOOLS_API`
- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace Geometry` (scope `UE`)
