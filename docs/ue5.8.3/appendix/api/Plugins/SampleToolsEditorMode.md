# Plugins / SampleToolsEditorMode

- module root: `Plugins/Editor/SampleToolsEditorMode/Source`
- headers: 7; symbols: 88
- symbol kinds: class=13, function=3, member=27, prototype=45
- DynamicallyLoadedModuleNames: 
- PrivateDependencyModuleNames: ContentBrowser, CoreUObject, EditorFramework, EditorInteractiveToolsFramework, Engine, InputCore, InteractiveToolsFramework, LevelEditor, Slate, SlateCore, UnrealEd
- PublicDependencyModuleNames: Core

### `Plugins/Editor/SampleToolsEditorMode/Source/Private/SampleTools/CreateActorSampleTool.h` (Private)


#### class `UCreateActorSampleToolBuilder`  
`class UCreateActorSampleToolBuilder : public UInteractiveToolBuilder`  
_L13-20_
- reflection: `UCLASS()`
- inherits: `UInteractiveToolBuilder`
- desc: Builder for UCreateActorSampleTool
- L18 _public function_ `virtual bool CanBuildTool(const FToolBuilderState& SceneState) const override`
- L19 _public prototype_ `virtual UInteractiveTool* BuildTool(const FToolBuilderState& SceneState) const override;`

#### class `UCreateActorSampleToolProperties`  
`class UCreateActorSampleToolProperties : public UInteractiveToolPropertySet`  
_L29-42_
- reflection: `UCLASS(Transient)`
- inherits: `UInteractiveToolPropertySet`
- desc: Settings UObject for UCreateActorSampleTool. This UClass inherits from UInteractiveToolPropertySet, which provides an OnModified delegate that the Tool will listen to for changes in property values.
- L33 _public prototype_ `UCreateActorSampleToolProperties();`
- L37 _public member_ `bool PlaceOnObjects;` — `UPROPERTY(EditAnywhere, Category = Options, meta = (DisplayName = "Place On Objects"))` — Place actors on existing objects
- L41 _public member_ `float GroundHeight;` — `UPROPERTY(EditAnywhere, Category = Options, meta = (DisplayName = "Ground Height", UIMin = "-1000.0", UIMax = "1000.0", ClampMin = "-1000000", ClampMax = "1000000.0"))` — Height of ground plane

#### class `UCreateActorSampleTool`  
`class UCreateActorSampleTool : public USingleClickTool`  
_L53-75_
- reflection: `UCLASS()`
- inherits: `USingleClickTool`
- desc: UCreateActorSampleTool is an example Tool that drops an empty Actor at each position the user clicks left mouse button. The Actors are placed at the first ray intersection in the scene, or on a ground plane if no scene objects are hit. All the action is in the ::OnClicked handler.
- L58 _public prototype_ `UCreateActorSampleTool();`
- L60 _public prototype_ `virtual void SetWorld(UWorld* World);`
- L62 _public prototype_ `virtual void Setup() override;`
- L64 _public prototype_ `virtual void OnClicked(const FInputDeviceRay& ClickPos);`
- L69 _protected member_ `TObjectPtr<UCreateActorSampleToolProperties> Properties;` — `UPROPERTY()`
- L74 _protected member_ `UWorld* TargetWorld;` — target World we will raycast into and create Actor in

### `Plugins/Editor/SampleToolsEditorMode/Source/Private/SampleTools/DrawCurveOnMeshSampleTool.h` (Private)


#### class `UDrawCurveOnMeshSampleToolBuilder`  
`class UDrawCurveOnMeshSampleToolBuilder : public UMeshSurfacePointToolBuilder`  
_L13-19_
- reflection: `UCLASS(Transient)`
- inherits: `UMeshSurfacePointToolBuilder`
- desc: UMeshSurfacePointToolBuilder override for UDrawCurveOnMeshSampleTool
- L18 _public prototype_ `virtual UMeshSurfacePointTool* CreateNewTool(const FToolBuilderState& SceneState) const override;`

#### class `UDrawCurveOnMeshSampleToolProperties`  
`class UDrawCurveOnMeshSampleToolProperties : public UInteractiveToolPropertySet`  
_L27-50_
- reflection: `UCLASS(Transient)`
- inherits: `UInteractiveToolPropertySet`
- desc: Settings UObject for UDrawCurveOnMeshSampleTool. This UClass inherits from UInteractiveToolPropertySet, which provides an OnModified delegate that the Tool will listen to for changes in property values.
- L31 _public prototype_ `UDrawCurveOnMeshSampleToolProperties();`
- L34 _public member_ `FLinearColor Color;` — `UPROPERTY(EditAnywhere, Category = Options)`
- L37 _public member_ `float Thickness;` — `UPROPERTY(EditAnywhere, Category = Options, meta = (DisplayName = "Thickness", UIMin = "0.25", UIMax = "10.0", ClampMin = "0.01", ClampMax = "1000.0"))`
- L40 _public member_ `float MinSpacing;` — `UPROPERTY(EditAnywhere, Category = Options, meta = (DisplayName = "Min Spacing", UIMin = "0.01", UIMax = "10.0"))`
- L43 _public member_ `float NormalOffset;` — `UPROPERTY(EditAnywhere, Category = Options, meta = (DisplayName = "Offset", UIMin = "0.0", UIMax = "10.0", ClampMin = "-1000.0", ClampMax = "1000.0"))`
- L46 _public member_ `float DepthBias;` — `UPROPERTY(EditAnywhere, Category = Options, meta = (DisplayName = "Depth Bias", UIMin = "-10.0", UIMax = "10.0"))`
- L49 _public member_ `bool bScreenSpace;` — `UPROPERTY(EditAnywhere, Category = Options)`

#### class `UDrawCurveOnMeshSampleTool`  
`class UDrawCurveOnMeshSampleTool : public UMeshSurfacePointTool`  
_L60-89_
- reflection: `UCLASS(Transient)`
- inherits: `UMeshSurfacePointTool`
- desc: UDrawCurveOnMeshSampleTool is a sample Tool that allows the user to draw curves on the surface of a selected Mesh Component. The various rendering properties of the polycurve are exposed and can be tweaked. Nothing is done with the curve, it is just drawn by ::Render() and discarded when the Tool exits.
- L65 _public prototype_ `UDrawCurveOnMeshSampleTool();`
- L69 _public prototype_ `virtual void Setup() override;`
- L71 _public prototype_ `virtual void Render(IToolsContextRenderAPI* RenderAPI) override;`
- L74 _public prototype_ `virtual void OnBeginDrag(const FRay& Ray) override;` — UMeshSurfacePointTool API
- L75 _public prototype_ `virtual void OnUpdateDrag(const FRay& Ray) override;`
- L76 _public prototype_ `virtual void OnEndDrag(const FRay& Ray) override;`
- L77 _public prototype_ `virtual void OnCancelDrag() override;`
- L81 _protected member_ `TObjectPtr<UDrawCurveOnMeshSampleToolProperties> Settings;` — `UPROPERTY()`
- L84 _protected member_ `TArray<FVector> Positions;` — `UPROPERTY()`
- L87 _protected member_ `TArray<FVector> Normals;` — `UPROPERTY()`

### `Plugins/Editor/SampleToolsEditorMode/Source/Private/SampleTools/MeasureDistanceSampleTool.h` (Private)


#### class `UMeasureDistanceSampleToolBuilder`  
`class UMeasureDistanceSampleToolBuilder : public UInteractiveToolBuilder`  
_L15-22_
- reflection: `UCLASS()`
- inherits: `UInteractiveToolBuilder`
- desc: Builder for UMeasureDistanceSampleTool
- L20 _public prototype_ `virtual bool CanBuildTool(const FToolBuilderState& SceneState) const override;`
- L21 _public prototype_ `virtual UInteractiveTool* BuildTool(const FToolBuilderState& SceneState) const override;`

#### class `UMeasureDistanceProperties`  
`class UMeasureDistanceProperties : public UInteractiveToolPropertySet`  
_L29-47_
- reflection: `UCLASS(Transient)`
- inherits: `UInteractiveToolPropertySet`
- desc: Property set for the UMeasureDistanceSampleTool
- L34 _public prototype_ `UMeasureDistanceProperties();`
- L38 _public member_ `FVector StartPoint;` — `UPROPERTY(EditAnywhere, Category = Options)` — First point of measurement
- L42 _public member_ `FVector EndPoint;` — `UPROPERTY(EditAnywhere, Category = Options)` — Second point of measurement
- L46 _public member_ `float Distance;` — `UPROPERTY(EditAnywhere, Category = Options)` — Current distance measurement

#### class `UMeasureDistanceSampleTool`  
`class UMeasureDistanceSampleTool : public UInteractiveTool, public IClickDragBehaviorTarget`  
_L57-100_
- reflection: `UCLASS()`
- inherits: `UInteractiveTool,IClickDragBehaviorTarget`
- desc: UMeasureDistanceSampleTool is an example Tool that allows the user to measure the distance between two points. The first point is set by click-dragging the mouse, and the second point is set by shift-click-dragging the mouse.
- L62 _public prototype_ `virtual void SetWorld(UWorld* World);`
- L66 _public prototype_ `virtual void Setup() override;`
- L67 _public prototype_ `virtual void Render(IToolsContextRenderAPI* RenderAPI) override;`
- L68 _public prototype_ `virtual void OnPropertyModified(UObject* PropertySet, FProperty* Property) override;`
- L72 _public prototype_ `virtual FInputRayHit CanBeginClickDragSequence(const FInputDeviceRay& PressPos) override;`
- L73 _public prototype_ `virtual void OnClickPress(const FInputDeviceRay& PressPos) override;`
- L74 _public prototype_ `virtual void OnClickDrag(const FInputDeviceRay& DragPos) override;`
- L76 _public function_ `virtual void OnClickRelease(const FInputDeviceRay& ReleasePos) override` — these are not used in this Tool
- L77 _public function_ `virtual void OnTerminateDragSequence() override`
- L81 _public prototype_ `virtual void OnUpdateModifierState(int ModifierID, bool bIsOn) override;`
- L87 _protected member_ `TObjectPtr<UMeasureDistanceProperties> Properties;` — `UPROPERTY()` — Properties of the tool are stored here
- L91 _protected member_ `UWorld* TargetWorld = nullptr;` — target World we will raycast into
- L93 _protected member_ `static const int MoveSecondPointModifierID = 1;` — identifier we associate with the shift key
- L94 _protected member_ `bool bSecondPointModifierDown = false;` — flag we use to keep track of modifier state
- L95 _protected member_ `bool bMoveSecondPoint = false;` — flag we use to keep track of which point we are moving during a press-drag
- L97 _protected prototype_ `FInputRayHit FindRayHit(const FRay& WorldRay, FVector& HitPos);` — raycasts into World
- L98 _protected prototype_ `void UpdatePosition(const FRay& WorldRay);` — updates first or second point based on raycast
- L99 _protected prototype_ `void UpdateDistance();` — updates distance

### `Plugins/Editor/SampleToolsEditorMode/Source/Public/SampleToolsEditorMode.h` (Public)


#### class `USampleToolsEditorMode`  
`class USampleToolsEditorMode : public UEdMode`  
_L21-41_
- reflection: `UCLASS()`
- inherits: `UEdMode`
- desc: This class provides an example of how to extend a UEdMode to add some simple tools using the InteractiveTools framework. The various UEdMode input event handlers (see UEdMode.h) forward events to a UEdModeInteractiveToolsContext instance, which has all the logic for interacting with the InputRouter, ToolManager, etc. The functions provided here are the minimum to get started inserting some custom behavior. Take a look at the UEdMode markup for more extensibility options.
- L26 _public member_ `const static FEditorModeID EM_SampleToolsEditorModeId;`
- L28 _public prototype_ `USampleToolsEditorMode();`
- L29 _public prototype_ `virtual ~USampleToolsEditorMode();`
- L33 _public prototype_ `virtual void Enter() override;` — UEdMode interface
- L34 _public prototype_ `virtual void ActorSelectionChangeNotify() override;`
- L35 _public prototype_ `virtual void CreateToolkit() override;`
- L36 _public prototype_ `virtual TMap<FName, TArray<TSharedPtr<FUICommandInfo>>> GetModeCommands() const override;`

### `Plugins/Editor/SampleToolsEditorMode/Source/Public/SampleToolsEditorModeCommands.h` (Public)


#### class `FSampleToolsEditorModeCommands`  
`class FSampleToolsEditorModeCommands : public TCommands<FSampleToolsEditorModeCommands>`  
_L8-23_
- inherits: `TCommands<FSampleToolsEditorModeCommands>`
- L11 _public prototype_ `FSampleToolsEditorModeCommands();`
- L13 _public prototype_ `virtual void RegisterCommands() override;`
- L14 _public prototype_ `static TMap<FName, TArray<TSharedPtr<FUICommandInfo>>> GetCommands();`
- L16 _public member_ `TSharedPtr<FUICommandInfo> CreateActorTool;`
- L17 _public member_ `TSharedPtr<FUICommandInfo> DrawCurveOnMeshTool;`
- L18 _public member_ `TSharedPtr<FUICommandInfo> MeasureDistanceTool;`
- L19 _public member_ `TSharedPtr<FUICommandInfo> SurfacePointTool;`
- L22 _protected member_ `TMap<FName, TArray<TSharedPtr<FUICommandInfo>>> Commands;`

### `Plugins/Editor/SampleToolsEditorMode/Source/Public/SampleToolsEditorModeModule.h` (Public)


#### class `FSampleToolsEditorModeModule`  
`class FSampleToolsEditorModeModule : public IModuleInterface`  
_L8-15_
- inherits: `IModuleInterface`
- L13 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface implementation
- L14 _public prototype_ `virtual void ShutdownModule() override;`

### `Plugins/Editor/SampleToolsEditorMode/Source/Public/SampleToolsEditorModeToolkit.h` (Public)


#### class `FSampleToolsEditorModeToolkit`  
`class FSampleToolsEditorModeToolkit : public FModeToolkit`  
_L16-28_
- inherits: `FModeToolkit`
- desc: This FModeToolkit just creates a basic UI panel that allows various InteractiveTools to be initialized, and a DetailsView used to show properties of the active Tool.
- L19 _public prototype_ `FSampleToolsEditorModeToolkit();`
- L22 _public prototype_ `virtual void Init(const TSharedPtr<IToolkitHost>& InitToolkitHost, TWeakObjectPtr<UEdMode> InOwningMode) override;` — FModeToolkit interface
- L23 _public prototype_ `virtual void GetToolPaletteNames(TArray<FName>& PaletteNames) const override;`
- L26 _public prototype_ `virtual FName GetToolkitFName() const override;` — IToolkit interface
- L27 _public prototype_ `virtual FText GetBaseToolkitName() const override;`
