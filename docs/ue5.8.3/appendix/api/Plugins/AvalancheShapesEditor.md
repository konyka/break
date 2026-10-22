# Plugins / AvalancheShapesEditor

- module root: `Plugins/VirtualProduction/Avalanche/Source/AvalancheShapesEditor`
- headers: 36; symbols: 612
- symbol kinds: class=35, function=21, member=159, namespace=2, prototype=337, struct=14, typedef=29, variable=15
- PrivateDependencyModuleNames: Avalanche, AvalancheComponentVisualizers, AvalancheEditorCore, AvalancheInteractiveTools, AvalancheLevelViewport, AvalancheShapes, AvalancheViewport, ComponentVisualizers, CoreUObject, DeveloperSettings, EditorFramework, Engine, GeometryCore, GeometryFramework, InputCore, InteractiveToolsFramework, MeshConversion, MovieScene, MovieSceneTools, MovieSceneTracks, Projects, Sequencer, Slate, SlateCore, UnrealEd, WidgetRegistration
- PublicDependencyModuleNames: Core

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheShapesEditor/Private/AvaShapeFactory.h` (Private)


#### class `UAvaShapeFactory`  
`class UAvaShapeFactory : public UActorFactory`  
_L13-39_
- reflection: `UCLASS()`
- inherits: `UActorFactory`
- L18 _public prototype_ `UAvaShapeFactory();`
- L20 _public prototype_ `void SetMeshClass(TSubclassOf<UAvaShapeDynamicMeshBase> InMeshClass);`
- L21 _public prototype_ `void SetMeshSize(const FVector& InMeshSize);`
- L22 _public prototype_ `void SetMeshFunction(TFunction<void(UAvaShapeDynamicMeshBase*)> InFunction);`
- L23 _public prototype_ `void SetMeshNameOverride(const TOptional<FString>& InMeshNameOverride);`
- L27 _protected prototype_ `virtual bool CanCreateActorFrom(const FAssetData& AssetData, FText& OutErrorMsg) override;`
- L28 _protected prototype_ `virtual AActor* GetDefaultActor(const FAssetData& AssetData) override;`
- L29 _protected prototype_ `virtual AActor* SpawnActor(UObject* InAsset, ULevel* InLevel, const FTransform& InTransform, const FActorSpawnParameters& InSpawnParams) override;`
- L30 _protected prototype_ `virtual void PostSpawnActor(UObject* InAsset, AActor* InNewActor) override;`
- L31 _protected prototype_ `virtual void PostPlaceAsset(TArrayView<const FTypedElementHandle> InHandle, const FAssetPlacementInfo& InPlacementInfo, const FPlacementOptions& InPlacementOptions) override;`
- L32 _protected prototype_ `virtual FString GetDefaultActorLabel(UObject* InAsset) const override;`
- L35 _protected member_ `TSubclassOf<UAvaShapeDynamicMeshBase> MeshClass;`
- L36 _protected member_ `FVector MeshSize = FVector::ZeroVector;`
- L37 _protected member_ `TFunction<void(UAvaShapeDynamicMeshBase*)> MeshFunction;`
- L38 _protected member_ `TOptional<FString> MeshNameOverride;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheShapesEditor/Private/AvaShapesEditorCommands.h` (Private)


#### class `FAvaShapesEditorCommands`  
`class FAvaShapesEditorCommands : public TCommands<FAvaShapesEditorCommands>`  
_L7-37_
- inherits: `TCommands<FAvaShapesEditorCommands>`
- L10 _public prototype_ `FAvaShapesEditorCommands();`
- L13 _public prototype_ `virtual void RegisterCommands() override;`
- L16 _public prototype_ `void Register2DCommands();`
- L17 _public prototype_ `void Register3DCommands();`
- L20 _public member_ `TSharedPtr<FUICommandInfo> Tool_Shape_2DArrow;` — 2D Tools
- L21 _public member_ `TSharedPtr<FUICommandInfo> Tool_Shape_Chevron;`
- L22 _public member_ `TSharedPtr<FUICommandInfo> Tool_Shape_Ellipse;`
- L23 _public member_ `TSharedPtr<FUICommandInfo> Tool_Shape_IrregularPoly;`
- L24 _public member_ `TSharedPtr<FUICommandInfo> Tool_Shape_Line;`
- L25 _public member_ `TSharedPtr<FUICommandInfo> Tool_Shape_NGon;`
- L26 _public member_ `TSharedPtr<FUICommandInfo> Tool_Shape_Rectangle;`
- L27 _public member_ `TSharedPtr<FUICommandInfo> Tool_Shape_Square;`
- L28 _public member_ `TSharedPtr<FUICommandInfo> Tool_Shape_Ring;`
- L29 _public member_ `TSharedPtr<FUICommandInfo> Tool_Shape_Star;`
- L32 _public member_ `TSharedPtr<FUICommandInfo> Tool_Shape_Cone;` — 3D Tools
- L33 _public member_ `TSharedPtr<FUICommandInfo> Tool_Shape_Cylinder;`
- L34 _public member_ `TSharedPtr<FUICommandInfo> Tool_Shape_Cube;`
- L35 _public member_ `TSharedPtr<FUICommandInfo> Tool_Shape_Sphere;`
- L36 _public member_ `TSharedPtr<FUICommandInfo> Tool_Shape_Torus;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheShapesEditor/Private/AvaShapesEditorStyle.h` (Private)


#### class `FAvaShapesEditorStyle`  
`class FAvaShapesEditorStyle final : public FSlateStyleSet`  
_L7-18_
- inherits: `FSlateStyleSet`
- L10 _public function_ `static FAvaShapesEditorStyle& Get()`
- L16 _public prototype_ `FAvaShapesEditorStyle();`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheShapesEditor/Private/AvalancheShapesEditorModule.h` (Private)


#### class `FAvalancheShapesEditorModule`  
`class FAvalancheShapesEditorModule : public IModuleInterface`  
_L13-25_
- inherits: `IModuleInterface`
- L16 _private prototype_ `virtual void StartupModule() override;`
- L17 _private prototype_ `virtual void ShutdownModule() override;`
- L20 _private member_ `TArray<TSharedPtr<FComponentVisualizer>> Visualizers;`
- L22 _private prototype_ `void RegisterVisualizers();`
- L24 _private member_ `FDelegateHandle TrackEditorHandle;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheShapesEditor/Private/Tools/AvaShapesEditorShapeAreaToolBase.h` (Private)


#### class `UAvaShapesEditorShapeAreaToolBase`  
`class UAvaShapesEditorShapeAreaToolBase : public UAvaShapesEditorShapeToolBase`  
_L12-32_
- reflection: `UCLASS(Abstract)`
- inherits: `UAvaShapesEditorShapeToolBase`
- L19 _public prototype_ `UAvaShapesEditorShapeAreaToolBase();`
- L22 _public prototype_ `virtual void OnViewportPlannerUpdate() override;`
- L23 _public prototype_ `virtual void OnViewportPlannerComplete() override;`
- L27 _protected prototype_ `void UpdateShapeSize(AAvaShapeActor* InShapeActor) const;`
- L30 _protected prototype_ `virtual AActor* SpawnActor(TSubclassOf<AActor> InActorClass, EAvaViewportStatus InViewportStatus, const FVector2f& InViewportPosition, bool bInPreview, FString* InActorLabelOverride = nullptr) override;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheShapesEditor/Private/Tools/AvaShapesEditorShapeTool2DArrow.h` (Private)


#### class `UAvaShapesEditorShapeTool2DArrow`  
`class UAvaShapesEditorShapeTool2DArrow : public UAvaShapesEditorShapeAreaToolBase`  
_L9-20_
- reflection: `UCLASS()`
- inherits: `UAvaShapesEditorShapeAreaToolBase`
- L14 _public prototype_ `UAvaShapesEditorShapeTool2DArrow();`
- L18 _protected prototype_ `virtual void OnRegisterTool(IAvalancheInteractiveToolsModule* InAITModule) override;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheShapesEditor/Private/Tools/AvaShapesEditorShapeToolBase.h` (Private)


#### class `UAvaShapesEditorShapeToolBase`  
`class UAvaShapesEditorShapeToolBase : public UAvaInteractiveToolsActorToolBase`  
_L14-58_
- reflection: `UCLASS(Abstract)`
- inherits: `UAvaInteractiveToolsActorToolBase`
- L28 _public member_ `static const FShapeFactoryParameters DefaultParameters;`
- L30 _public prototype_ `UAvaShapesEditorShapeToolBase();`
- L35 _protected function_ `static UAvaShapeFactory* CreateFactory(const FShapeFactoryParameters& InParameters = DefaultParameters)`
- L46 _protected prototype_ `virtual bool OnBegin() override;`
- L50 _protected prototype_ `virtual bool UseIdentityLocation() const override;`
- L51 _protected prototype_ `virtual void OnActorSpawned(AActor* InActor) override;`
- L54 _protected prototype_ `virtual void SetShapeSize(AAvaShapeActor* InShapeActor, const FVector2D& InShapeSize) const;`
- L57 _protected member_ `TSubclassOf<UAvaShapeDynamicMeshBase> ShapeClass = nullptr;` — `UPROPERTY()`

#### struct `UAvaShapesEditorShapeToolBase::FShapeFactoryParameters`  
`struct FShapeFactoryParameters`  
_L21-26_
- L23 _public member_ `FVector Size = FVector(100);`
- L24 _public function_ `TFunction<void(UAvaShapeDynamicMeshBase*)> Functor = [](UAvaShapeDynamicMeshBase*)`
- L24 _public member_ `TFunction<void(UAvaShapeDynamicMeshBase*)> Functor = [](UAvaShapeDynamicMeshBase*){};`
- L25 _public member_ `TOptional<FString> NameOverride;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheShapesEditor/Private/Tools/AvaShapesEditorShapeToolChevron.h` (Private)


#### class `UAvaShapesEditorShapeToolChevron`  
`class UAvaShapesEditorShapeToolChevron : public UAvaShapesEditorShapeAreaToolBase`  
_L9-20_
- reflection: `UCLASS()`
- inherits: `UAvaShapesEditorShapeAreaToolBase`
- L14 _public prototype_ `UAvaShapesEditorShapeToolChevron();`
- L18 _protected prototype_ `virtual void OnRegisterTool(IAvalancheInteractiveToolsModule* InAITModule) override;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheShapesEditor/Private/Tools/AvaShapesEditorShapeToolCone.h` (Private)


#### class `UAvaShapesEditorShapeToolCone`  
`class UAvaShapesEditorShapeToolCone : public UAvaShapesEditorShapeAreaToolBase`  
_L9-20_
- reflection: `UCLASS()`
- inherits: `UAvaShapesEditorShapeAreaToolBase`
- L14 _public prototype_ `UAvaShapesEditorShapeToolCone();`
- L18 _protected prototype_ `virtual void OnRegisterTool(IAvalancheInteractiveToolsModule* InAITModule) override;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheShapesEditor/Private/Tools/AvaShapesEditorShapeToolCube.h` (Private)


#### class `UAvaShapesEditorShapeToolCube`  
`class UAvaShapesEditorShapeToolCube : public UAvaShapesEditorShapeAreaToolBase`  
_L9-20_
- reflection: `UCLASS()`
- inherits: `UAvaShapesEditorShapeAreaToolBase`
- L14 _public prototype_ `UAvaShapesEditorShapeToolCube();`
- L18 _protected prototype_ `virtual void OnRegisterTool(IAvalancheInteractiveToolsModule* InAITModule) override;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheShapesEditor/Private/Tools/AvaShapesEditorShapeToolEllipse.h` (Private)


#### class `UAvaShapesEditorShapeToolEllipse`  
`class UAvaShapesEditorShapeToolEllipse : public UAvaShapesEditorShapeAreaToolBase`  
_L9-20_
- reflection: `UCLASS()`
- inherits: `UAvaShapesEditorShapeAreaToolBase`
- L14 _public prototype_ `UAvaShapesEditorShapeToolEllipse();`
- L18 _protected prototype_ `virtual void OnRegisterTool(IAvalancheInteractiveToolsModule* InAITModule) override;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheShapesEditor/Private/Tools/AvaShapesEditorShapeToolIrregularPoly.h` (Private)


#### class `UAvaShapesEditorShapeToolIrregularPoly`  
`class UAvaShapesEditorShapeToolIrregularPoly : public UAvaShapesEditorShapeToolBase`  
_L9-36_
- reflection: `UCLASS()`
- inherits: `UAvaShapesEditorShapeToolBase`
- L14 _public prototype_ `UAvaShapesEditorShapeToolIrregularPoly();`
- L18 _protected member_ `static constexpr float MinDim = 5;` — The minimum dimension
- L21 _protected prototype_ `virtual void OnRegisterTool(IAvalancheInteractiveToolsModule* InAITModule) override;`
- L22 _protected prototype_ `virtual void DrawHUD(FCanvas* InCanvas, IToolsContextRenderAPI* InRenderAPI) override;`
- L23 _protected prototype_ `virtual void OnViewportPlannerUpdate() override;`
- L24 _protected function_ `virtual void OnViewportPlannerComplete() override` — Does nothing
- L28 _protected function_ `virtual void SetShapeSize(AAvaShapeActor* InShapeActor, const FVector2D& InShapeSize) const override`
- L31 _protected prototype_ `int32 FindOverlappingPointIndex(const FVector2f& InPosition) const;`
- L33 _protected prototype_ `void OnNewPointAdded();`
- L34 _protected prototype_ `void UpdateTransientLineColor();`
- L35 _protected prototype_ `void AddFinishedShape();`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheShapesEditor/Private/Tools/AvaShapesEditorShapeToolLine.h` (Private)


#### class `UAvaShapesEditorShapeToolLine`  
`class UAvaShapesEditorShapeToolLine : public UAvaShapesEditorShapeToolBase`  
_L9-33_
- reflection: `UCLASS()`
- inherits: `UAvaShapesEditorShapeToolBase`
- L14 _public prototype_ `UAvaShapesEditorShapeToolLine();`
- L18 _protected member_ `static constexpr float MinDim = 5;` — The minimum dimension
- L21 _protected prototype_ `virtual void OnRegisterTool(IAvalancheInteractiveToolsModule* InAITModule) override;`
- L22 _protected prototype_ `virtual void OnViewportPlannerUpdate() override;`
- L23 _protected function_ `virtual void OnViewportPlannerComplete() override` — Does nothing
- L27 _protected prototype_ `virtual void SetShapeSize(AAvaShapeActor* InShapeActor, const FVector2D& InShapeSize) const override;`
- L30 _protected prototype_ `void SetLineEnds(AAvaShapeActor* InShapeActor, const FVector2f& Start, const FVector2f& End);`
- L32 _protected member_ `FVector2f LineEndLocation = FVector2f::ZeroVector;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheShapesEditor/Private/Tools/AvaShapesEditorShapeToolNGon.h` (Private)


#### class `UAvaShapesEditorShapeToolNGon`  
`class UAvaShapesEditorShapeToolNGon : public UAvaShapesEditorShapeAreaToolBase`  
_L9-20_
- reflection: `UCLASS()`
- inherits: `UAvaShapesEditorShapeAreaToolBase`
- L14 _public prototype_ `UAvaShapesEditorShapeToolNGon();`
- L18 _protected prototype_ `virtual void OnRegisterTool(IAvalancheInteractiveToolsModule* InAITModule) override;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheShapesEditor/Private/Tools/AvaShapesEditorShapeToolRectangle.h` (Private)


#### class `UAvaShapesEditorShapeToolRectangle`  
`class UAvaShapesEditorShapeToolRectangle : public UAvaShapesEditorShapeAreaToolBase`  
_L9-20_
- reflection: `UCLASS()`
- inherits: `UAvaShapesEditorShapeAreaToolBase`
- L14 _public prototype_ `UAvaShapesEditorShapeToolRectangle();`
- L18 _protected prototype_ `virtual void OnRegisterTool(IAvalancheInteractiveToolsModule* InAITModule) override;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheShapesEditor/Private/Tools/AvaShapesEditorShapeToolRing.h` (Private)


#### class `UAvaShapesEditorShapeToolRing`  
`class UAvaShapesEditorShapeToolRing : public UAvaShapesEditorShapeAreaToolBase`  
_L9-20_
- reflection: `UCLASS()`
- inherits: `UAvaShapesEditorShapeAreaToolBase`
- L14 _public prototype_ `UAvaShapesEditorShapeToolRing();`
- L18 _protected prototype_ `virtual void OnRegisterTool(IAvalancheInteractiveToolsModule* InAITModule) override;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheShapesEditor/Private/Tools/AvaShapesEditorShapeToolSphere.h` (Private)


#### class `UAvaShapesEditorShapeToolSphere`  
`class UAvaShapesEditorShapeToolSphere : public UAvaShapesEditorShapeAreaToolBase`  
_L9-20_
- reflection: `UCLASS()`
- inherits: `UAvaShapesEditorShapeAreaToolBase`
- L14 _public prototype_ `UAvaShapesEditorShapeToolSphere();`
- L18 _protected prototype_ `virtual void OnRegisterTool(IAvalancheInteractiveToolsModule* InAITModule) override;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheShapesEditor/Private/Tools/AvaShapesEditorShapeToolStar.h` (Private)


#### class `UAvaShapesEditorShapeToolStar`  
`class UAvaShapesEditorShapeToolStar : public UAvaShapesEditorShapeAreaToolBase`  
_L9-20_
- reflection: `UCLASS()`
- inherits: `UAvaShapesEditorShapeAreaToolBase`
- L14 _public prototype_ `UAvaShapesEditorShapeToolStar();`
- L18 _protected prototype_ `virtual void OnRegisterTool(IAvalancheInteractiveToolsModule* InAITModule) override;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheShapesEditor/Private/Tools/AvaShapesEditorShapeToolTorus.h` (Private)


#### class `UAvaShapesEditorShapeToolTorus`  
`class UAvaShapesEditorShapeToolTorus : public UAvaShapesEditorShapeAreaToolBase`  
_L9-20_
- reflection: `UCLASS()`
- inherits: `UAvaShapesEditorShapeAreaToolBase`
- L14 _public prototype_ `UAvaShapesEditorShapeToolTorus();`
- L18 _protected prototype_ `virtual void OnRegisterTool(IAvalancheInteractiveToolsModule* InAITModule) override;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheShapesEditor/Private/TrackEditors/AvaShapeRectCornerTrackEditor.h` (Private)


#### class `FAvaShapeRectCornerTrackEditor`  
`class FAvaShapeRectCornerTrackEditor : public FPropertyTrackEditor<UMovieSceneAvaShapeRectCornerTrack>`  
_L12-44_
- inherits: `FPropertyTrackEditor<UMovieSceneAvaShapeRectCornerTrack>`
- desc: A Property track editor for FAvaShapeRectangleCornerSettings.
- L15 _public function_ `FAvaShapeRectCornerTrackEditor(TSharedRef<ISequencer> InSequencer) : FPropertyTrackEditor(InSequencer, GetAnimatedPropertyTypes())`
- L23 _public function_ `static TArray<FAnimatedPropertyKey, TInlineAllocator<1>> GetAnimatedPropertyTypes()` — Retrieve a list of all property types that this track editor animates
- L34 _public prototype_ `static TSharedRef<ISequencerTrackEditor> CreateTrackEditor(TSharedRef<ISequencer> InOwningSequencer);` — Creates an instance of this class (called by a sequence). @param InOwningSequencer The sequencer instance to be used by this tool. @return The new instance of this class.
- L38 _protected prototype_ `virtual FText GetDisplayName() const override;`
- L40 _protected prototype_ `virtual void GenerateKeysFromPropertyChanged(const FPropertyChangedParams& InPropertyChangedParams , UMovieSceneSection* InSectionToKey , FGeneratedTrackKeys& OutGeneratedKeys) override;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheShapesEditor/Private/Visualizers/AvaShape2DDynMeshVis.h` (Private)


#### class `FAvaShape2DDynamicMeshVisualizer`  
`class FAvaShape2DDynamicMeshVisualizer : public FAvaShapeDynamicMeshVisualizer`  
_L10-70_
- inherits: `FAvaShapeDynamicMeshVisualizer`
- L13 _public typedef_ `using Super = FAvaShapeDynamicMeshVisualizer;`
- L14 _public typedef_ `using FMeshType = UAvaShape2DDynMeshBase;`
- L16 _public prototype_ `FAvaShape2DDynamicMeshVisualizer();`
- L19 _public prototype_ `virtual TMap<UObject*, TArray<FProperty*>> GatherEditableProperties(UObject* InObject) const override;`
- L20 _public prototype_ `virtual bool VisProxyHandleClick(FEditorViewportClient* InViewportClient, HComponentVisProxy* InVisProxy, const FViewportClick& InClick) override;`
- L22 _public prototype_ `virtual bool GetWidgetLocation(const FEditorViewportClient* InViewportClient, FVector& OutLocation) const override;`
- L23 _public prototype_ `virtual bool GetWidgetMode(const FEditorViewportClient* InViewportClient, UE::Widget::EWidgetMode& OutMode) const override;`
- L24 _public prototype_ `virtual bool GetWidgetAxisList(const FEditorViewportClient* InViewportClient, UE::Widget::EWidgetMode InWidgetMode, EAxisList::Type& OutAxisList) const override;`
- L26 _public prototype_ `virtual bool HandleModifiedClick(FEditorViewportClient* InViewportClient, HHitProxy* InHitProxy, const FViewportClick& InClick) override;`
- L27 _public prototype_ `virtual bool ResetValue(FEditorViewportClient* InViewportClient, HHitProxy* InHitProxy) override;`
- L28 _public prototype_ `virtual bool IsEditing() const override;`
- L29 _public prototype_ `virtual void EndEditing() override;`
- L33 _protected member_ `FProperty* SizeProperty;`
- L35 _protected member_ `AvaAlignment SizeDragAnchor;` — XYZ
- L36 _protected member_ `FVector2D InitialSize;`
- L40 _protected member_ `static inline const TArray<AvaAlignment> SupportedAlignments { MakeAlignment(EAvaDepthAlignment::Back, EAvaHorizontalAlignment::Left, EAvaVerticalAlignment::Top),` — Supported alignments Center alignments removed on request.
- L47 _protected member_ `int32 UVSectionIdx;`
- L48 _protected member_ `bool bEditingUVAnchor;`
- L49 _protected member_ `FVector2D InitialPrimaryUVOffset;`
- L50 _protected member_ `FVector2D InitialPrimaryUVScale;`
- L51 _protected member_ `float InitialPrimaryUVRotation;`
- L52 _protected member_ `FVector2D InitialPrimaryUVAnchor;`
- L53 _protected member_ `FVector2D PrevShapeSize;`
- L55 _protected prototype_ `virtual void DrawVisualizationNotEditing(const UActorComponent* InComponent, const FSceneView* InView, FPrimitiveDrawInterface* InPDI, int32& InOutIconIndex) override;`
- L57 _protected prototype_ `virtual void DrawVisualizationEditing(const UActorComponent* Component, const FSceneView* View, FPrimitiveDrawInterface* InPDI, int32& InOutIconIndex) override;`
- L60 _protected prototype_ `virtual void DrawSizeButtons(const FMeshType* InDynMesh, const FSceneView* InView, FPrimitiveDrawInterface* InPDI);`
- L62 _protected prototype_ `virtual void StoreInitialValues() override;`
- L64 _protected prototype_ `virtual bool HandleInputDeltaInternal(FEditorViewportClient* InViewportClient, FViewport* InViewport, const FVector& InAccumulatedTranslation, const FRotator& InAccumulatedRotation, const FVector& InAccumulatedScale) override;`
- L67 _protected prototype_ `void SnapLocation2D(FEditorViewportClient* InViewportClient, const FTransform& InActorTransform, FVector2D& OutLocation2D) const;`
- L69 _protected prototype_ `bool IsExtendBothSidesEnabled(FMeshType* InDynMesh) const;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheShapesEditor/Private/Visualizers/AvaShape3DDynMeshVis.h` (Private)


#### class `FAvaShape3DDynamicMeshVisualizer`  
`class FAvaShape3DDynamicMeshVisualizer : public FAvaShapeDynamicMeshVisualizer`  
_L9-64_
- inherits: `FAvaShapeDynamicMeshVisualizer`
- L12 _public typedef_ `using Super = FAvaShapeDynamicMeshVisualizer;`
- L13 _public typedef_ `using FMeshType = UAvaShape3DDynMeshBase;`
- L15 _public prototype_ `FAvaShape3DDynamicMeshVisualizer();`
- L18 _public prototype_ `virtual TMap<UObject*, TArray<FProperty*>> GatherEditableProperties(UObject* InObject) const override;`
- L19 _public prototype_ `virtual bool VisProxyHandleClick(FEditorViewportClient* InViewportClient, HComponentVisProxy* InVisProxy, const FViewportClick& InClick) override;`
- L21 _public prototype_ `virtual bool GetWidgetLocation(const FEditorViewportClient* InViewportClient, FVector& OutLocation) const override;`
- L22 _public prototype_ `virtual bool GetWidgetMode(const FEditorViewportClient* InViewportClient, UE::Widget::EWidgetMode& OutMode) const override;`
- L23 _public prototype_ `virtual bool GetWidgetAxisList(const FEditorViewportClient* InViewportClient, UE::Widget::EWidgetMode InWidgetMode, EAxisList::Type& OutAxisList) const override;`
- L25 _public prototype_ `virtual bool HandleModifiedClick(FEditorViewportClient* InViewportClient, HHitProxy* InHitProxy, const FViewportClick& InClick) override;`
- L26 _public prototype_ `virtual bool ResetValue(FEditorViewportClient* InViewportClient, HHitProxy* InHitProxy) override;`
- L27 _public prototype_ `virtual bool IsEditing() const override;`
- L28 _public prototype_ `virtual void EndEditing() override;`
- L34 _protected member_ `FProperty* SizeProperty;` — direct access to size property to notify about update
- L36 _protected member_ `AvaAlignment SizeDragAnchor;` — this gives information about current handle XYZ we are updating
- L38 _protected member_ `FVector InitialSize;` — size before any update with visualizer
- L42 _protected member_ `static inline const TArray<AvaAlignment> SupportedAlignments { MakeAlignment(EAvaDepthAlignment::Back, EAvaHorizontalAlignment::Left, EAvaVerticalAlignment::Top), MakeAlignment(EAvaDepthAlignment::Back, EAvaHorizontalAlignment::Right, EAvaVerticalAlignment::Top), MakeAlignment(EAvaDepthAlignment::Back, EAvaHorizontalAlignment::Left, EAvaVerticalAlignment::Bottom), MakeAlignment(EAvaDepthAlignment::Back, EAvaHorizontalAlignment::Right, EAvaVerticalAlignment::Bottom), MakeAlignment(EAvaDepthAlignment::Front, EAvaHorizontalAlignment::Left, EAvaVerticalAlignment::Top), MakeAlignment(EAvaDepthAlignment::Front, EAvaHorizontalAlignment::Right, EAvaVerticalAlignment::Top), MakeAlignment(EAvaDepthAlignment::Front, EAvaHorizontalAlignment::Left, EAvaVerticalAlignment::Bottom), MakeAlignment(EAvaDepthAlignment::Front, EAvaHorizontalAlignment::Right, EAvaVerticalAlignment::Bottom), };` — Supported alignments Center alignments removed on request.
- L55 _protected prototype_ `virtual void DrawVisualizationNotEditing(const UActorComponent* InComponent, const FSceneView* InView, FPrimitiveDrawInterface* InPDI, int32& InOutIconIndex) override;`
- L57 _protected prototype_ `virtual void DrawVisualizationEditing(const UActorComponent* InComponent, const FSceneView* InView, FPrimitiveDrawInterface* InPDI, int32& InOutIconIndex) override;`
- L59 _protected prototype_ `virtual void StoreInitialValues() override;`
- L60 _protected prototype_ `virtual bool HandleInputDeltaInternal(FEditorViewportClient* InViewportClient, FViewport* InViewport, const FVector& InAccumulatedTranslation, const FRotator& InAccumulatedRotation, const FVector& InAccumulatedScale) override;`
- L63 _protected prototype_ `void SnapLocation3D(FEditorViewportClient* InViewportClient, const FTransform& InActorTransform, FVector& OutLocation) const;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheShapesEditor/Private/Visualizers/AvaShapeConeDynMeshVis.h` (Private)


#### class `FAvaShapeConeDynamicMeshVisualizer`  
`class FAvaShapeConeDynamicMeshVisualizer : public FAvaShape3DDynamicMeshVisualizer`  
_L9-58_
- inherits: `FAvaShape3DDynamicMeshVisualizer`
- L12 _public typedef_ `using Super = FAvaShape3DDynamicMeshVisualizer;`
- L13 _public typedef_ `using FMeshType = UAvaShapeConeDynamicMesh;`
- L15 _public prototype_ `FAvaShapeConeDynamicMeshVisualizer();`
- L18 _public prototype_ `virtual TMap<UObject*, TArray<FProperty*>> GatherEditableProperties(UObject* InObject) const override;`
- L19 _public prototype_ `virtual bool VisProxyHandleClick(FEditorViewportClient* InViewportClient, HComponentVisProxy* InVisProxy, const FViewportClick& InClick) override;`
- L21 _public prototype_ `virtual bool GetWidgetLocation(const FEditorViewportClient* InViewportClient, FVector& OutLocation) const override;`
- L22 _public prototype_ `virtual bool GetWidgetMode(const FEditorViewportClient* InViewportClient, UE::Widget::EWidgetMode& OutMode) const override;`
- L23 _public prototype_ `virtual bool GetWidgetAxisList(const FEditorViewportClient* InViewportClient, UE::Widget::EWidgetMode InWidgetMode, EAxisList::Type& OutAxisList) const override;`
- L25 _public prototype_ `virtual bool GetWidgetAxisListDragOverride(const FEditorViewportClient* InViewportClient, UE::Widget::EWidgetMode InWidgetMode, EAxisList::Type& OutAxisList) const override;`
- L27 _public prototype_ `virtual bool ResetValue(FEditorViewportClient* InViewportClient, HHitProxy* InHitProxy) override;`
- L28 _public prototype_ `virtual bool IsEditing() const override;`
- L29 _public prototype_ `virtual void EndEditing() override;`
- L33 _protected member_ `FProperty* TopRadiusProperty;`
- L34 _protected member_ `FProperty* NumSidesProperty;`
- L35 _protected member_ `FProperty* AngleDegreeProperty;`
- L37 _protected member_ `bool bEditingTopRadius;`
- L38 _protected member_ `float InitialTopRadius;`
- L39 _protected member_ `bool bEditingNumSides;`
- L40 _protected member_ `uint8 InitialNumSides;`
- L41 _protected member_ `bool bEditingAngleDegree;`
- L42 _protected member_ `float InitialAngleDegree;`
- L44 _protected prototype_ `virtual void DrawVisualizationNotEditing(const UActorComponent* InComponent, const FSceneView* InView, FPrimitiveDrawInterface* InPDI, int32& InOutIconIndex) override;`
- L46 _protected prototype_ `virtual void DrawVisualizationEditing(const UActorComponent* InComponent, const FSceneView* InView, FPrimitiveDrawInterface* InPDI, int32& InOutIconIndex) override;`
- L48 _protected prototype_ `virtual bool HandleInputDeltaInternal(FEditorViewportClient* InViewportClient, FViewport* InViewport, const FVector& InAccumulatedTranslation, const FRotator& InAccumulatedRotation, const FVector& InAccumulatedScale) override;`
- L50 _protected prototype_ `virtual void StoreInitialValues() override;`
- L52 _protected prototype_ `void DrawTopRadiusButton(const FMeshType* InDynMesh, const FSceneView* InView, FPrimitiveDrawInterface* InPDI, int32 InIconIndex, const FLinearColor& InColor) const;`
- L54 _protected prototype_ `void DrawNumSidesButton(const FMeshType* InDynMesh, const FSceneView* InView, FPrimitiveDrawInterface* InPDI, int32 InIconIndex, const FLinearColor& InColor) const;`
- L56 _protected prototype_ `void DrawAngleDegreeButton(const FMeshType* InDynMesh, const FSceneView* InView, FPrimitiveDrawInterface* InPDI, int32 InIconIndex, const FLinearColor& InColor) const;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheShapesEditor/Private/Visualizers/AvaShapeCubeDynMeshVis.h` (Private)


#### class `FAvaShapeCubeDynamicMeshVisualizer`  
`class FAvaShapeCubeDynamicMeshVisualizer : public FAvaShape3DDynamicMeshVisualizer`  
_L9-54_
- inherits: `FAvaShape3DDynamicMeshVisualizer`
- L12 _public typedef_ `using Super = FAvaShape3DDynamicMeshVisualizer;`
- L13 _public typedef_ `using FMeshType = UAvaShapeCubeDynamicMesh;`
- L15 _public prototype_ `FAvaShapeCubeDynamicMeshVisualizer();`
- L18 _public prototype_ `virtual TMap<UObject*, TArray<FProperty*>> GatherEditableProperties(UObject* InObject) const override;`
- L19 _public prototype_ `virtual bool VisProxyHandleClick(FEditorViewportClient* InViewportClient, HComponentVisProxy* InVisProxy, const FViewportClick& InClick) override;`
- L21 _public prototype_ `virtual bool GetWidgetLocation(const FEditorViewportClient* InViewportClient, FVector& OutLocation) const override;`
- L22 _public prototype_ `virtual bool GetWidgetMode(const FEditorViewportClient* InViewportClient, UE::Widget::EWidgetMode& OutMode) const override;`
- L23 _public prototype_ `virtual bool GetWidgetAxisList(const FEditorViewportClient* InViewportClient, UE::Widget::EWidgetMode InWidgetMode, EAxisList::Type& OutAxisList) const override;`
- L25 _public prototype_ `virtual bool GetWidgetAxisListDragOverride(const FEditorViewportClient* InViewportClient, UE::Widget::EWidgetMode InWidgetMode, EAxisList::Type& OutAxisList) const override;`
- L27 _public prototype_ `virtual bool ResetValue(FEditorViewportClient* InViewportClient, HHitProxy* InHitProxy) override;`
- L28 _public prototype_ `virtual bool IsEditing() const override;`
- L29 _public prototype_ `virtual void EndEditing() override;`
- L33 _protected member_ `FProperty* BevelSizeRatioProperty;`
- L34 _protected member_ `FProperty* BevelNumProperty;`
- L36 _protected member_ `bool bEditingBevelSizeRatio;`
- L37 _protected member_ `float InitialBevelSizeRatio;`
- L38 _protected member_ `bool bEditingBevelNum;`
- L39 _protected member_ `uint8 InitialBevelNum;`
- L41 _protected prototype_ `virtual void DrawVisualizationNotEditing(const UActorComponent* InComponent, const FSceneView* InView, FPrimitiveDrawInterface* InPDI, int32& InOutIconIndex) override;`
- L43 _protected prototype_ `virtual void DrawVisualizationEditing(const UActorComponent* InComponent, const FSceneView* InView, FPrimitiveDrawInterface* InPDI, int32& InOutIconIndex) override;`
- L45 _protected prototype_ `virtual bool HandleInputDeltaInternal(FEditorViewportClient* InViewportClient, FViewport* InViewport, const FVector& InAccumulatedTranslation, const FRotator& InAccumulatedRotation, const FVector& InAccumulatedScale) override;`
- L47 _protected prototype_ `virtual void StoreInitialValues() override;`
- L49 _protected prototype_ `void DrawBevelSizeRatioButton(const FMeshType* InDynMesh, const FSceneView* InView, FPrimitiveDrawInterface* InPDI, int32 InIconIndex, const FLinearColor& InColor) const;`
- L51 _protected prototype_ `void DrawBevelNumButton(const FMeshType* InDynMesh, const FSceneView* InView, FPrimitiveDrawInterface* InPDI, int32 InIconIndex, const FLinearColor& InColor) const;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheShapesEditor/Private/Visualizers/AvaShapeDynMeshVis.h` (Private)


#### struct `HAvaShapeSizeHitProxy`  
`struct HAvaShapeSizeHitProxy : HAvaHitProxy`  
_L10-21_
- inherits: `HAvaHitProxy`
- L12 _public prototype_ `DECLARE_HIT_PROXY();`
- L14 _public function_ `HAvaShapeSizeHitProxy( const UActorComponent* InComponent, AvaAlignment InAlignment) : HAvaHitProxy(InComponent) , DragAnchor(InAlignment)`
- L20 _public member_ `AvaAlignment DragAnchor;` — XYZ

#### struct `HAvaShapeUVHitProxy`  
`struct HAvaShapeUVHitProxy : HAvaHitProxy`  
_L23-33_
- inherits: `HAvaHitProxy`
- L25 _public prototype_ `DECLARE_HIT_PROXY();`
- L27 _public function_ `HAvaShapeUVHitProxy(const UActorComponent* InComponent, int32 InSectionIdx) : HAvaHitProxy(InComponent) , SectionIdx(InSectionIdx)`
- L32 _public member_ `int32 SectionIdx;`

#### struct `HAvaShapeNumSidesHitProxy`  
`struct HAvaShapeNumSidesHitProxy : HAvaHitProxy`  
_L35-42_
- inherits: `HAvaHitProxy`
- L37 _public prototype_ `DECLARE_HIT_PROXY();`
- L39 _public function_ `HAvaShapeNumSidesHitProxy(const UActorComponent* InComponent) : HAvaHitProxy(InComponent)`

#### struct `HAvaShapeNumPointsHitProxy`  
`struct HAvaShapeNumPointsHitProxy : HAvaHitProxy`  
_L44-51_
- inherits: `HAvaHitProxy`
- L46 _public prototype_ `DECLARE_HIT_PROXY();`
- L48 _public function_ `HAvaShapeNumPointsHitProxy(const UActorComponent* InComponent) : HAvaHitProxy(InComponent)`

#### struct `HAvaShapeInnerSizeHitProxy`  
`struct HAvaShapeInnerSizeHitProxy : HAvaHitProxy`  
_L53-60_
- inherits: `HAvaHitProxy`
- L55 _public prototype_ `DECLARE_HIT_PROXY();`
- L57 _public function_ `HAvaShapeInnerSizeHitProxy(const UActorComponent* InComponent) : HAvaHitProxy(InComponent)`

#### struct `HAvaShapeCornersHitProxy`  
`struct HAvaShapeCornersHitProxy : HAvaHitProxy`  
_L62-69_
- inherits: `HAvaHitProxy`
- L64 _public prototype_ `DECLARE_HIT_PROXY();`
- L66 _public function_ `HAvaShapeCornersHitProxy(const UActorComponent* InComponent) : HAvaHitProxy(InComponent)`

#### struct `HAvaShapeAngleDegreeHitProxy`  
`struct HAvaShapeAngleDegreeHitProxy : HAvaHitProxy`  
_L71-83_
- inherits: `HAvaHitProxy`
- L73 _public prototype_ `DECLARE_HIT_PROXY();`
- L75 _public function_ `HAvaShapeAngleDegreeHitProxy( const UActorComponent* InComponent, AvaAlignment InAlignment) : HAvaHitProxy(InComponent) , DragAnchor(InAlignment)`
- L82 _public member_ `AvaAlignment DragAnchor;` — XYZ

#### class `FAvaShapeDynamicMeshVisualizer`  
`class FAvaShapeDynamicMeshVisualizer : public FAvaVisualizerBase`  
_L85-134_
- inherits: `FAvaVisualizerBase`
- L88 _public typedef_ `using Super = FAvaVisualizerBase;`
- L90 _public prototype_ `UAvaShapeDynamicMeshBase* GetDynamicMesh() const;`
- L93 _public prototype_ `virtual UActorComponent* GetEditedComponent() const override;`
- L94 _public prototype_ `virtual TMap<UObject*, TArray<FProperty*>> GatherEditableProperties(UObject* InObject) const override;`
- L95 _public prototype_ `virtual const USceneComponent* GetEditedSceneComponent() const override;`
- L96 _public prototype_ `virtual const USceneComponent* GetEditedSceneComponent(const UActorComponent* InComponent) const override;`
- L97 _public prototype_ `virtual void StartEditing(FEditorViewportClient* InViewportClient, UActorComponent* InEditedComponent) override;`
- L98 _public prototype_ `virtual void EndEditing() override;`
- L102 _protected member_ `TWeakObjectPtr<UAvaShapeDynamicMeshBase> DynamicMeshComponent;`
- L103 _protected member_ `FTransform InitialTransform;`
- L105 _protected member_ `FProperty* MeshRegenWorldLocationProperty;`
- L106 _protected member_ `FProperty* MeshDataProperty;`
- L107 _protected member_ `FProperty* UVParamsProperty;`
- L108 _protected member_ `FProperty* UVOffsetProperty;`
- L109 _protected member_ `FProperty* UVScaleProperty;`
- L110 _protected member_ `FProperty* UVRotationProperty;`
- L111 _protected member_ `FProperty* UVAnchorProperty;`
- L112 _protected member_ `FProperty* UVModeProperty;`
- L113 _protected member_ `FProperty* UVHorizFlipProperty;`
- L114 _protected member_ `FProperty* UVVertFlipProperty;`
- L116 _protected prototype_ `FAvaShapeDynamicMeshVisualizer();`
- L118 _protected prototype_ `virtual void StoreInitialValues() override;`
- L119 _protected prototype_ `virtual FBox GetComponentBounds(const UActorComponent* InComponent) const override;`
- L120 _protected prototype_ `virtual FTransform GetComponentTransform(const UActorComponent* InComponent) const override;`
- L123 _protected prototype_ `void DrawSizeButton(const UAvaShapeDynamicMeshBase* InDynMesh, const FSceneView* InView, FPrimitiveDrawInterface* InPDI, AvaAlignment InSizeDragAnchor) const;` — draw size button hit proxy with icon at specific alignment location
- L127 _protected prototype_ `void DrawUVButton(const UAvaShapeDynamicMeshBase* InDynMesh, const FSceneView* InView, FPrimitiveDrawInterface* InPDI, int32 InIconIndex, int32 InSectionIdx, const FLinearColor& InColor) const;` — draw uv button hit proxy with icon for section index
- L131 _protected prototype_ `bool IsAnchorReachable(const UAvaShapeDynamicMeshBase* InDynMesh, const FSceneView* InView, const FVector& InAnchorLocation) const;` — checks whether an anchor location is on the correct size of the view and can be reachable
- L133 _protected prototype_ `FVector GetFinalAnchorLocation(const UAvaShapeDynamicMeshBase* InDynMesh, AvaAlignment InSizeDragAnchor) const;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheShapesEditor/Private/Visualizers/AvaShapeEllipseDynMeshVis.h` (Private)


#### class `FAvaShapeEllipseDynamicMeshVisualizer`  
`class FAvaShapeEllipseDynamicMeshVisualizer : public FAvaShape2DDynamicMeshVisualizer`  
_L9-49_
- inherits: `FAvaShape2DDynamicMeshVisualizer`
- L13 _public typedef_ `using Super = FAvaShape2DDynamicMeshVisualizer;`
- L14 _public typedef_ `using FMeshType = UAvaShapeEllipseDynamicMesh;`
- L16 _public prototype_ `FAvaShapeEllipseDynamicMeshVisualizer();`
- L19 _public prototype_ `virtual TMap<UObject*, TArray<FProperty*>> GatherEditableProperties(UObject* InObject) const override;`
- L20 _public prototype_ `virtual bool VisProxyHandleClick(FEditorViewportClient* InViewportClient, HComponentVisProxy* InVisProxy, const FViewportClick& InClick) override;`
- L22 _public prototype_ `virtual bool GetWidgetLocation(const FEditorViewportClient* InViewportClient, FVector& OutLocation) const override;`
- L23 _public prototype_ `virtual bool GetWidgetMode(const FEditorViewportClient* InViewportClient, UE::Widget::EWidgetMode& OutMode) const override;`
- L24 _public prototype_ `virtual bool GetWidgetAxisList(const FEditorViewportClient* InViewportClient, UE::Widget::EWidgetMode InWidgetMode, EAxisList::Type& OutAxisList) const override;`
- L26 _public prototype_ `virtual bool ResetValue(FEditorViewportClient* InViewportClient, HHitProxy* InHitProxy) override;`
- L27 _public prototype_ `virtual bool IsEditing() const override;`
- L28 _public prototype_ `virtual void EndEditing() override;`
- L32 _protected member_ `FProperty* NumSidesProperty;`
- L34 _protected member_ `bool bEditingNumSides;`
- L35 _protected member_ `int32 InitialNumSides;`
- L37 _protected prototype_ `virtual void DrawVisualizationNotEditing(const UActorComponent* InComponent, const FSceneView* InView, FPrimitiveDrawInterface* InPDI, int32& InOutIconIndex) override;`
- L39 _protected prototype_ `virtual void DrawVisualizationEditing(const UActorComponent* InComponent, const FSceneView* InView, FPrimitiveDrawInterface* InPDI, int32& InOutIconIndex) override;`
- L42 _protected prototype_ `virtual bool HandleInputDeltaInternal(FEditorViewportClient* InViewportClient, FViewport* InViewport, const FVector& InAccumulatedTranslation, const FRotator& InAccumulatedRotation, const FVector& InAccumulatedScale) override;`
- L45 _protected prototype_ `virtual void StoreInitialValues() override;`
- L47 _protected prototype_ `void DrawNumSidesButton(const FMeshType* InDynMesh, const FSceneView* InView, FPrimitiveDrawInterface* InPDI, int32 InIconIndex, const FLinearColor& InColor) const;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheShapesEditor/Private/Visualizers/AvaShapeIrregularPolygonDynMeshVis.h` (Private)


#### struct `HAvaShapeIrregularPolygonPointHitProxy`  
`struct HAvaShapeIrregularPolygonPointHitProxy : HAvaHitProxy`  
_L7-17_
- inherits: `HAvaHitProxy`
- L9 _public prototype_ `DECLARE_HIT_PROXY();`
- L11 _public function_ `HAvaShapeIrregularPolygonPointHitProxy(const UActorComponent* InComponent, int32 InPointIdx) : HAvaHitProxy(InComponent) , PointIdx(InPointIdx)`
- L16 _public member_ `int32 PointIdx;`

#### struct `HAvaShapeIrregularPolygonBevelHitProxy`  
`struct HAvaShapeIrregularPolygonBevelHitProxy : HAvaHitProxy`  
_L19-29_
- inherits: `HAvaHitProxy`
- L21 _public prototype_ `DECLARE_HIT_PROXY();`
- L23 _public function_ `HAvaShapeIrregularPolygonBevelHitProxy(const UActorComponent* InComponent, int32 InPointIdx) : HAvaHitProxy(InComponent) , PointIdx(InPointIdx)`
- L28 _public member_ `int32 PointIdx;`

#### struct `HAvaShapeIrregularPolygonBreakHitProxy`  
`struct HAvaShapeIrregularPolygonBreakHitProxy : HAvaHitProxy`  
_L31-41_
- inherits: `HAvaHitProxy`
- L33 _public prototype_ `DECLARE_HIT_PROXY();`
- L35 _public function_ `HAvaShapeIrregularPolygonBreakHitProxy(const UActorComponent* InComponent, int32 InPointIdx) : HAvaHitProxy(InComponent) , PointIdx(InPointIdx)`
- L40 _public member_ `int32 PointIdx;`

#### class `FAvaShapeIrregularPolygonDynamicMeshVisualizer`  
`class FAvaShapeIrregularPolygonDynamicMeshVisualizer : public FAvaShape2DDynamicMeshVisualizer`  
_L45-116_
- inherits: `FAvaShape2DDynamicMeshVisualizer`
- L49 _public typedef_ `using Super = FAvaShape2DDynamicMeshVisualizer;`
- L50 _public typedef_ `using FMeshType = UAvaShapeIrregularPolygonDynamicMesh;`
- L52 _public prototype_ `FAvaShapeIrregularPolygonDynamicMeshVisualizer();`
- L55 _public prototype_ `virtual TMap<UObject*, TArray<FProperty*>> GatherEditableProperties(UObject* InObject) const override;`
- L56 _public prototype_ `virtual bool VisProxyHandleClick(FEditorViewportClient* InViewportClient, HComponentVisProxy* InVisProxy, const FViewportClick& InClick) override;`
- L58 _public prototype_ `virtual bool GetWidgetMode(const FEditorViewportClient* InViewportClient, UE::Widget::EWidgetMode& OutMode) const override;`
- L59 _public prototype_ `virtual bool GetWidgetLocation(const FEditorViewportClient* InViewportClient, FVector& OutLocation) const override;`
- L60 _public prototype_ `virtual bool GetWidgetAxisList(const FEditorViewportClient* InViewportClient, UE::Widget::EWidgetMode InWidgetMode, EAxisList::Type& OutAxisList) const override;`
- L62 _public prototype_ `virtual bool GetWidgetAxisListDragOverride(const FEditorViewportClient* InViewportClient, UE::Widget::EWidgetMode InWidgetMode, EAxisList::Type& OutAxisList) const override;`
- L64 _public prototype_ `virtual bool GetCustomInputCoordinateSystem(const FEditorViewportClient* InViewportClient, FMatrix& OutMatrix) const override;`
- L65 _public prototype_ `virtual bool ResetValue(FEditorViewportClient* InViewportClient, HHitProxy* InHitProxy) override;`
- L66 _public prototype_ `virtual bool IsEditing() const override;`
- L67 _public prototype_ `virtual void EndEditing() override;`
- L68 _public prototype_ `virtual void TrackingStopped(FEditorViewportClient* InViewportClient, bool bInDidMove) override;`
- L72 _protected member_ `FProperty* GlobalBevelSizeProperty;`
- L73 _protected member_ `FProperty* PointsProperty;`
- L74 _protected member_ `FProperty* LocationProperty;`
- L75 _protected member_ `FProperty* BevelSizeProperty;`
- L77 _protected member_ `bool bEditingGlobalBevelSize;`
- L78 _protected member_ `float InitialGlobalBevelSize;`
- L79 _protected member_ `int32 EditingPointIdx;`
- L80 _protected member_ `int32 EditingBevelIdx;`
- L81 _protected member_ `FVector2D InitialPointLocation;`
- L82 _protected member_ `float InitialPointBevelSize;`
- L84 _protected prototype_ `virtual void DrawVisualizationNotEditing(const UActorComponent* InComponent, const FSceneView* InView, FPrimitiveDrawInterface* InPDI, int32& InOutIconIndex) override;`
- L86 _protected prototype_ `virtual void DrawVisualizationEditing(const UActorComponent* InComponent, const FSceneView* InView, FPrimitiveDrawInterface* InPDI, int32& InOutIconIndex) override;`
- L89 _protected prototype_ `virtual bool HandleInputDeltaInternal(FEditorViewportClient* InViewportClient, FViewport* InViewport, const FVector& InAccumulatedTranslation, const FRotator& InAccumulatedRotation, const FVector& InAccumulatedScale) override;`
- L92 _protected prototype_ `virtual void StoreInitialValues() override;`
- L94 _protected prototype_ `FVector2D GetCornerBevelDirection2D(const FMeshType* InDynMesh, int32 InPointIdx) const;`
- L96 _protected prototype_ `void DrawGlobalBevelButton(const FMeshType* InDynMesh, const FSceneView* InView, FPrimitiveDrawInterface* InPDI, int32 InIconIndex, const FLinearColor& InColor) const;`
- L99 _protected prototype_ `void DrawPointButton(const FMeshType* InDynMesh, const FSceneView* InView, FPrimitiveDrawInterface* InPDI, const FLinearColor& InColor, int32 InPointIdx) const;`
- L102 _protected prototype_ `void DrawBevelButton(const FMeshType* InDynMesh, const FSceneView* InView, FPrimitiveDrawInterface* InPDI, const FLinearColor& InColor, int32 InPointIdx) const;`
- L105 _protected prototype_ `void DrawBreakButton(const FMeshType* InDynMesh, const FSceneView* InView, FPrimitiveDrawInterface* InPDI, const FLinearColor& InColor, int32 InPointIdx) const;`
- L108 _protected prototype_ `FVector GetGlobalBevelLocation(const FMeshType* InDynMesh) const;`
- L109 _protected prototype_ `FVector GetPointLocation(const FMeshType* InDynMesh, int32 InPointIdx) const;`
- L110 _protected prototype_ `FVector GetBevelLocation(const FMeshType* InDynMesh, int32 InPointIdx) const;`
- L113 _protected prototype_ `FVector GetBreakLocation(const FMeshType* InDynMesh, int32 InPointIdx) const;` — Returns the half way point between the given point index and the one following it (0 for the last point.)
- L115 _protected prototype_ `virtual void GenerateContextSensitiveSnapPoints() override;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheShapesEditor/Private/Visualizers/AvaShapeLineDynMeshVis.h` (Private)


#### struct `HAvaShapeLineEndHitProxy`  
`struct HAvaShapeLineEndHitProxy : HAvaHitProxy`  
_L7-17_
- inherits: `HAvaHitProxy`
- L9 _public prototype_ `DECLARE_HIT_PROXY();`
- L11 _public function_ `HAvaShapeLineEndHitProxy(const UActorComponent* InComponent, bool bInIsStart) : HAvaHitProxy(InComponent) , bIsStart(bInIsStart)`
- L16 _public member_ `bool bIsStart;`

#### class `FAvaShapeLineDynamicMeshVisualizer`  
`class FAvaShapeLineDynamicMeshVisualizer : public FAvaShapeRoundedPolygonDynamicMeshVisualizer`  
_L21-69_
- inherits: `FAvaShapeRoundedPolygonDynamicMeshVisualizer`
- L24 _public typedef_ `using Super = FAvaShapeRoundedPolygonDynamicMeshVisualizer;`
- L25 _public typedef_ `using FMeshType = UAvaShapeLineDynamicMesh;`
- L27 _public prototype_ `FAvaShapeLineDynamicMeshVisualizer();`
- L30 _public prototype_ `virtual TMap<UObject*, TArray<FProperty*>> GatherEditableProperties(UObject* InObject) const override;`
- L31 _public prototype_ `virtual bool VisProxyHandleClick(FEditorViewportClient* InViewportClient, HComponentVisProxy* InVisProxy, const FViewportClick& InClick) override;`
- L33 _public prototype_ `virtual bool GetWidgetLocation(const FEditorViewportClient* InViewportClient, FVector& OutLocation) const override;`
- L34 _public prototype_ `virtual bool GetWidgetMode(const FEditorViewportClient* InViewportClient, UE::Widget::EWidgetMode& OutMode) const override;`
- L35 _public prototype_ `virtual bool GetWidgetAxisList(const FEditorViewportClient* InViewportClient, UE::Widget::EWidgetMode InWidgetMode, EAxisList::Type& OutAxisList) const override;`
- L37 _public prototype_ `virtual bool IsEditing() const override;`
- L38 _public prototype_ `virtual void EndEditing() override;`
- L42 _protected member_ `FProperty* VectorProperty;`
- L44 _protected member_ `bool bEditingStart;`
- L45 _protected member_ `FVector2D InitialStart;`
- L46 _protected member_ `bool bEditingEnd;`
- L47 _protected member_ `FVector2D InitialVector;`
- L49 _protected prototype_ `virtual void DrawVisualizationNotEditing(const UActorComponent* InComponent, const FSceneView* InView, FPrimitiveDrawInterface* InPDI, int32& InOutIconIndex) override;`
- L51 _protected prototype_ `virtual void DrawVisualizationEditing(const UActorComponent* InComponent, const FSceneView* InView, FPrimitiveDrawInterface* InPDI, int32& InOutIconIndex) override;`
- L54 _protected prototype_ `virtual bool HandleInputDeltaInternal(FEditorViewportClient* InViewportClient, FViewport* InViewport, const FVector& InAccumulatedTranslation, const FRotator& InAccumulatedRotation, const FVector& InAccumulatedScale) override;`
- L57 _protected prototype_ `virtual void StoreInitialValues() override;`
- L59 _protected prototype_ `void DrawStartButton(const FMeshType* InDynMesh, const FSceneView* InView, FPrimitiveDrawInterface* InPDI, const FLinearColor& InColor) const;`
- L62 _protected prototype_ `void DrawEndButton(const FMeshType* InDynMesh, const FSceneView* InView, FPrimitiveDrawInterface* InPDI, const FLinearColor& InColor) const;`
- L65 _protected prototype_ `FVector GetStartWorldLocation(const FMeshType* InDynMesh) const;`
- L66 _protected prototype_ `FVector GetEndWorldLocation(const FMeshType* InDynMesh) const;`
- L68 _protected prototype_ `virtual void GenerateContextSensitiveSnapPoints() override;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheShapesEditor/Private/Visualizers/AvaShapeNGonDynMeshVis.h` (Private)


#### class `FAvaShapeNGonDynamicMeshVisualizer`  
`class FAvaShapeNGonDynamicMeshVisualizer : public FAvaShapeRoundedPolygonDynamicMeshVisualizer`  
_L9-48_
- inherits: `FAvaShapeRoundedPolygonDynamicMeshVisualizer`
- L12 _public typedef_ `using Super = FAvaShapeRoundedPolygonDynamicMeshVisualizer;`
- L13 _public typedef_ `using FMeshType = UAvaShapeNGonDynamicMesh;`
- L15 _public prototype_ `FAvaShapeNGonDynamicMeshVisualizer();`
- L18 _public prototype_ `virtual TMap<UObject*, TArray<FProperty*>> GatherEditableProperties(UObject* InObject) const override;`
- L19 _public prototype_ `virtual bool VisProxyHandleClick(FEditorViewportClient* InViewportClient, HComponentVisProxy* InVisProxy, const FViewportClick& InClick) override;`
- L21 _public prototype_ `virtual bool GetWidgetLocation(const FEditorViewportClient* InViewportClient, FVector& OutLocation) const override;`
- L22 _public prototype_ `virtual bool GetWidgetMode(const FEditorViewportClient* InViewportClient, UE::Widget::EWidgetMode& OutMode) const override;`
- L23 _public prototype_ `virtual bool GetWidgetAxisList(const FEditorViewportClient* InViewportClient, UE::Widget::EWidgetMode InWidgetMode, EAxisList::Type& OutAxisList) const override;`
- L25 _public prototype_ `virtual bool ResetValue(FEditorViewportClient* InViewportClient, HHitProxy* InHitProxy) override;`
- L26 _public prototype_ `virtual bool IsEditing() const override;`
- L27 _public prototype_ `virtual void EndEditing() override;`
- L31 _protected member_ `FProperty* NumSidesProperty;`
- L33 _protected member_ `bool bEditingNumSides;`
- L34 _protected member_ `int32 InitialNumSides;`
- L36 _protected prototype_ `virtual void DrawVisualizationNotEditing(const UActorComponent* InComponent, const FSceneView* InView, FPrimitiveDrawInterface* InPDI, int32& InOutIconIndex) override;`
- L38 _protected prototype_ `virtual void DrawVisualizationEditing(const UActorComponent* InComponent, const FSceneView* InView, FPrimitiveDrawInterface* InPDI, int32& InOutIconIndex) override;`
- L41 _protected prototype_ `virtual bool HandleInputDeltaInternal(FEditorViewportClient* InViewportClient, FViewport* InViewport, const FVector& InAccumulatedTranslation, const FRotator& InAccumulatedRotation, const FVector& InAccumulatedScale) override;`
- L44 _protected prototype_ `virtual void StoreInitialValues() override;`
- L46 _protected prototype_ `void DrawNumSidesButton(const FMeshType* InDynMesh, const FSceneView* InView, FPrimitiveDrawInterface* InPDI, int32 InIconIndex, const FLinearColor& InColor) const;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheShapesEditor/Private/Visualizers/AvaShapeRectangleDynMeshVis.h` (Private)


#### struct `HAvaShapeRectangleCornerHitProxy`  
`struct HAvaShapeRectangleCornerHitProxy : HAvaHitProxy`  
_L8-18_
- inherits: `HAvaHitProxy`
- L10 _public prototype_ `DECLARE_HIT_PROXY();`
- L12 _public function_ `HAvaShapeRectangleCornerHitProxy(const UActorComponent* InComponent, EAvaAnchors InCorner) : HAvaHitProxy(InComponent) , Corner(InCorner)`
- L17 _public member_ `EAvaAnchors Corner;`

#### struct `HAvaShapeRectangleSlantHitProxy`  
`struct HAvaShapeRectangleSlantHitProxy : HAvaHitProxy`  
_L20-30_
- inherits: `HAvaHitProxy`
- L22 _public prototype_ `DECLARE_HIT_PROXY();`
- L24 _public function_ `HAvaShapeRectangleSlantHitProxy(const UActorComponent* InComponent, EAvaAnchors InSide) : HAvaHitProxy(InComponent) , Side(InSide)`
- L29 _public member_ `EAvaAnchors Side;`

#### class `FAvaShapeRectangleDynamicMeshVisualizer`  
`class FAvaShapeRectangleDynamicMeshVisualizer : public FAvaShape2DDynamicMeshVisualizer`  
_L34-110_
- inherits: `FAvaShape2DDynamicMeshVisualizer`
- L38 _public typedef_ `using Super = FAvaShape2DDynamicMeshVisualizer;`
- L39 _public typedef_ `using FMeshType = UAvaShapeRectangleDynamicMesh;`
- L41 _public prototype_ `FAvaShapeRectangleDynamicMeshVisualizer();`
- L44 _public prototype_ `virtual TMap<UObject*, TArray<FProperty*>> GatherEditableProperties(UObject* InObject) const override;`
- L45 _public prototype_ `virtual bool VisProxyHandleClick(FEditorViewportClient* InViewportClient, HComponentVisProxy* InVisProxy, const FViewportClick& InClick) override;`
- L47 _public prototype_ `virtual bool GetWidgetLocation(const FEditorViewportClient* InViewportClient, FVector& OutLocation) const override;`
- L48 _public prototype_ `virtual bool GetWidgetMode(const FEditorViewportClient* InViewportClient, UE::Widget::EWidgetMode& OutMode) const override;`
- L49 _public prototype_ `virtual bool GetWidgetAxisList(const FEditorViewportClient* InViewportClient, UE::Widget::EWidgetMode InWidgetMode, EAxisList::Type& OutAxisList) const override;`
- L51 _public prototype_ `virtual bool GetWidgetAxisListDragOverride(const FEditorViewportClient* InViewportClient, UE::Widget::EWidgetMode InWidgetMode, EAxisList::Type& OutAxisList) const override;`
- L53 _public prototype_ `virtual bool GetCustomInputCoordinateSystem(const FEditorViewportClient* InViewportClient, FMatrix& OutMatrix) const override;`
- L54 _public prototype_ `virtual bool HandleModifiedClick(FEditorViewportClient* InViewportClient, HHitProxy* InHitProxy, const FViewportClick& InClick) override;`
- L55 _public prototype_ `virtual bool ResetValue(FEditorViewportClient* InViewportClient, HHitProxy* InHitProxy) override;`
- L56 _public prototype_ `virtual bool IsEditing() const override;`
- L57 _public prototype_ `virtual void EndEditing() override;`
- L61 _protected prototype_ `static FVector GetGlobalBevelLocation(const FMeshType* InDynMesh);`
- L62 _protected prototype_ `static FVector GetCornerLocation(const FMeshType* InDynMesh, EAvaAnchors InCorner);`
- L63 _protected prototype_ `static FVector GetSlantLocation(const FMeshType* InDynMesh, EAvaAnchors InSide);`
- L64 _protected prototype_ `static FVector GetCornerDragLocation(const FMeshType* InDynMesh, EAvaAnchors InCorner);`
- L66 _protected prototype_ `static FVector GetAlignmentOffset(const FMeshType* InDynMesh);`
- L68 _protected member_ `FProperty* GlobalBevelSizeProperty;`
- L69 _protected member_ `FProperty* TopLeftCornerSettingsProperty;`
- L70 _protected member_ `FProperty* TopRightCornerSettingsProperty;`
- L71 _protected member_ `FProperty* BottomLeftCornerSettingsProperty;`
- L72 _protected member_ `FProperty* BottomRightCornerSettingsProperty;`
- L73 _protected member_ `FProperty* BevelSizeProperty;`
- L74 _protected member_ `FProperty* CornerTypeProperty;`
- L75 _protected member_ `FProperty* LeftSlantProperty;`
- L76 _protected member_ `FProperty* RightSlantProperty;`
- L78 _protected member_ `bool bEditingGlobalBevelSize;`
- L79 _protected member_ `float InitialGlobalBevelSize;`
- L80 _protected member_ `EAvaAnchors Corner;`
- L81 _protected member_ `float InitialTopLeftBevelSize;`
- L82 _protected member_ `float InitialTopRightBevelSize;`
- L83 _protected member_ `float InitialBottomLeftBevelSize;`
- L84 _protected member_ `float InitialBottomRightBevelSize;`
- L86 _protected member_ `EAvaAnchors SlantSide;`
- L87 _protected member_ `float InitialLeftSlant;`
- L88 _protected member_ `float InitialRightSlant;`
- L90 _protected prototype_ `virtual void DrawVisualizationNotEditing(const UActorComponent* InComponent, const FSceneView* InView, FPrimitiveDrawInterface* InPDI, int32& InOutIconIndex) override;`
- L92 _protected prototype_ `virtual void DrawVisualizationEditing(const UActorComponent* InComponent, const FSceneView* InView, FPrimitiveDrawInterface* InPDI, int32& InOutIconIndex) override;`
- L95 _protected prototype_ `virtual void DrawSizeButtons(const Super::FMeshType* InDynMesh, const FSceneView* InView, FPrimitiveDrawInterface* InPDI) override;`
- L97 _protected prototype_ `virtual bool HandleInputDeltaInternal(FEditorViewportClient* InViewportClient, FViewport* InViewport, const FVector& InAccumulatedTranslation, const FRotator& InAccumulatedRotation, const FVector& InAccumulatedScale) override;`
- L100 _protected prototype_ `virtual void StoreInitialValues() override;`
- L102 _protected prototype_ `void DrawGlobalBevelButton(const FMeshType* InDynMesh, const FSceneView* InView, FPrimitiveDrawInterface* InPDI, int32 InIconIndex, const FLinearColor& InColor) const;`
- L105 _protected prototype_ `void DrawBevelButton(const FMeshType* InDynMesh, const FSceneView* InView, FPrimitiveDrawInterface* InPDI, const FLinearColor& InColor, EAvaAnchors InCorner) const;`
- L108 _protected prototype_ `void DrawSlantButton(const FMeshType* InDynMesh, const FSceneView* InView, FPrimitiveDrawInterface* InPDI, const FLinearColor& InColor, EAvaAnchors InSide) const;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheShapesEditor/Private/Visualizers/AvaShapeRingDynMeshVis.h` (Private)


#### class `FAvaShapeRingDynamicMeshVisualizer`  
`class FAvaShapeRingDynamicMeshVisualizer : public FAvaShape2DDynamicMeshVisualizer`  
_L9-57_
- inherits: `FAvaShape2DDynamicMeshVisualizer`
- L13 _public typedef_ `using Super = FAvaShape2DDynamicMeshVisualizer;`
- L14 _public typedef_ `using FMeshType = UAvaShapeRingDynamicMesh;`
- L16 _public prototype_ `FAvaShapeRingDynamicMeshVisualizer();`
- L19 _public prototype_ `virtual TMap<UObject*, TArray<FProperty*>> GatherEditableProperties(UObject* InObject) const override;`
- L20 _public prototype_ `virtual bool VisProxyHandleClick(FEditorViewportClient* InViewportClient, HComponentVisProxy* InVisProxy, const FViewportClick& InClick) override;`
- L22 _public prototype_ `virtual bool GetWidgetLocation(const FEditorViewportClient* InViewportClient, FVector& OutLocation) const override;`
- L23 _public prototype_ `virtual bool GetWidgetMode(const FEditorViewportClient* InViewportClient, UE::Widget::EWidgetMode& OutMode) const override;`
- L24 _public prototype_ `virtual bool GetWidgetAxisList(const FEditorViewportClient* InViewportClient, UE::Widget::EWidgetMode InWidgetMode, EAxisList::Type& OutAxisList) const override;`
- L26 _public prototype_ `virtual bool GetWidgetAxisListDragOverride(const FEditorViewportClient* InViewportClient, UE::Widget::EWidgetMode InWidgetMode, EAxisList::Type& OutAxisList) const override;`
- L28 _public prototype_ `virtual bool ResetValue(FEditorViewportClient* InViewportClient, HHitProxy* InHitProxy) override;`
- L29 _public prototype_ `virtual bool IsEditing() const override;`
- L30 _public prototype_ `virtual void EndEditing() override;`
- L34 _protected member_ `FProperty* NumSidesProperty;`
- L35 _protected member_ `FProperty* InnerSizeProperty;`
- L37 _protected member_ `bool bEditingNumSides;`
- L38 _protected member_ `int32 InitialNumSides;`
- L39 _protected member_ `bool bEditingInnerSize;`
- L40 _protected member_ `float InitialInnerSize;`
- L42 _protected prototype_ `virtual void DrawVisualizationNotEditing(const UActorComponent* InComponent, const FSceneView* InView, FPrimitiveDrawInterface* InPDI, int32& InOutIconIndex) override;`
- L44 _protected prototype_ `virtual void DrawVisualizationEditing(const UActorComponent* InComponent, const FSceneView* InView, FPrimitiveDrawInterface* InPDI, int32& InOutIconIndex) override;`
- L47 _protected prototype_ `virtual bool HandleInputDeltaInternal(FEditorViewportClient* InViewportClient, FViewport* InViewport, const FVector& InAccumulatedTranslation, const FRotator& InAccumulatedRotation, const FVector& InAccumulatedScale) override;`
- L50 _protected prototype_ `virtual void StoreInitialValues() override;`
- L52 _protected prototype_ `void DrawNumSidesButton(const FMeshType* InDynMesh, const FSceneView* InView, FPrimitiveDrawInterface* InPDI, int32 InIconIndex, const FLinearColor& InColor) const;`
- L55 _protected prototype_ `void DrawInnerSizeButton(const FMeshType* InDynMesh, const FSceneView* InView, FPrimitiveDrawInterface* InPDI, int32 InIconIndex, const FLinearColor& InColor) const;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheShapesEditor/Private/Visualizers/AvaShapeRoundedPolygonDynMeshVis.h` (Private)


#### class `FAvaShapeRoundedPolygonDynamicMeshVisualizer`  
`class FAvaShapeRoundedPolygonDynamicMeshVisualizer : public FAvaShape2DDynamicMeshVisualizer`  
_L9-51_
- inherits: `FAvaShape2DDynamicMeshVisualizer`
- L13 _public typedef_ `using Super = FAvaShape2DDynamicMeshVisualizer;`
- L14 _public typedef_ `using FMeshType = UAvaShapeRoundedPolygonDynamicMesh;`
- L16 _public prototype_ `FAvaShapeRoundedPolygonDynamicMeshVisualizer();`
- L19 _public prototype_ `virtual TMap<UObject*, TArray<FProperty*>> GatherEditableProperties(UObject* InObject) const override;`
- L20 _public prototype_ `virtual bool VisProxyHandleClick(FEditorViewportClient* InViewportClient, HComponentVisProxy* InVisProxy, const FViewportClick& InClick) override;`
- L22 _public prototype_ `virtual bool GetWidgetLocation(const FEditorViewportClient* InViewportClient, FVector& OutLocation) const override;`
- L23 _public prototype_ `virtual bool GetWidgetMode(const FEditorViewportClient* InViewportClient, UE::Widget::EWidgetMode& OutMode) const override;`
- L24 _public prototype_ `virtual bool GetWidgetAxisList(const FEditorViewportClient* InViewportClient, UE::Widget::EWidgetMode InWidgetMode, EAxisList::Type& OutAxisList) const override;`
- L26 _public prototype_ `virtual bool GetWidgetAxisListDragOverride(const FEditorViewportClient* InViewportClient, UE::Widget::EWidgetMode InWidgetMode, EAxisList::Type& OutAxisList) const override;`
- L28 _public prototype_ `virtual bool ResetValue(FEditorViewportClient* InViewportClient, HHitProxy* InHitProxy) override;`
- L29 _public prototype_ `virtual bool IsEditing() const override;`
- L30 _public prototype_ `virtual void EndEditing() override;`
- L34 _protected member_ `FProperty* BevelSizeProperty;`
- L36 _protected member_ `bool bEditingCorners;`
- L37 _protected member_ `float InitialBevelSize;`
- L39 _protected prototype_ `virtual void DrawVisualizationNotEditing(const UActorComponent* InComponent, const FSceneView* InView, FPrimitiveDrawInterface* InPDI, int32& InOutIconIndex) override;`
- L41 _protected prototype_ `virtual void DrawVisualizationEditing(const UActorComponent* InComponent, const FSceneView* InView, FPrimitiveDrawInterface* InPDI, int32& InOutIconIndex) override;`
- L44 _protected prototype_ `virtual bool HandleInputDeltaInternal(FEditorViewportClient* InViewportClient, FViewport* InViewport, const FVector& InAccumulatedTranslation, const FRotator& InAccumulatedRotation, const FVector& InAccumulatedScale) override;`
- L47 _protected prototype_ `virtual void StoreInitialValues() override;`
- L49 _protected prototype_ `void DrawBevelButton(const FMeshType* InDynMesh, const FSceneView* InView, FPrimitiveDrawInterface* InPDI, int32 InIconIndex, const FLinearColor& InColor) const;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheShapesEditor/Private/Visualizers/AvaShapeSphereDynMeshVis.h` (Private)


#### class `FAvaShapeSphereDynamicMeshVisualizer`  
`class FAvaShapeSphereDynamicMeshVisualizer : public FAvaShape3DDynamicMeshVisualizer`  
_L10-60_
- inherits: `FAvaShape3DDynamicMeshVisualizer`
- L13 _public typedef_ `using Super = FAvaShape3DDynamicMeshVisualizer;`
- L14 _public typedef_ `using FMeshType = UAvaShapeSphereDynamicMesh;`
- L16 _public prototype_ `FAvaShapeSphereDynamicMeshVisualizer();`
- L19 _public prototype_ `virtual TMap<UObject*, TArray<FProperty*>> GatherEditableProperties(UObject* InObject) const override;`
- L20 _public prototype_ `virtual bool VisProxyHandleClick(FEditorViewportClient* InViewportClient, HComponentVisProxy* InVisProxy, const FViewportClick& InClick) override;`
- L22 _public prototype_ `virtual bool GetWidgetLocation(const FEditorViewportClient* InViewportClient, FVector& OutLocation) const override;`
- L23 _public prototype_ `virtual bool GetWidgetMode(const FEditorViewportClient* InViewportClient, UE::Widget::EWidgetMode& OutMode) const override;`
- L24 _public prototype_ `virtual bool GetWidgetAxisList(const FEditorViewportClient* InViewportClient, UE::Widget::EWidgetMode InWidgetMode, EAxisList::Type& OutAxisList) const override;`
- L26 _public prototype_ `virtual bool GetWidgetAxisListDragOverride(const FEditorViewportClient* InViewportClient, UE::Widget::EWidgetMode InWidgetMode, EAxisList::Type& OutAxisList) const override;`
- L28 _public prototype_ `virtual bool ResetValue(FEditorViewportClient* InViewportClient, HHitProxy* InHitProxy) override;`
- L29 _public prototype_ `virtual bool IsEditing() const override;`
- L30 _public prototype_ `virtual void EndEditing() override;`
- L34 _protected member_ `FProperty* NumSidesProperty;`
- L35 _protected member_ `FProperty* LatitudeDegreeProperty;`
- L36 _protected member_ `FProperty* StartLongitudeProperty;`
- L37 _protected member_ `FProperty* EndLongitudeProperty;`
- L39 _protected member_ `bool bEditingNumSides;`
- L40 _protected member_ `uint8 InitialNumSides;`
- L41 _protected member_ `bool bEditingLatitudeDegree;`
- L42 _protected member_ `float InitialLatitudeDegree;`
- L43 _protected member_ `bool bEditingStartLongitude;`
- L44 _protected member_ `float InitialStartRatio;`
- L45 _protected member_ `bool bEditingEndLongitude;`
- L46 _protected member_ `float InitialEndRatio;`
- L48 _protected prototype_ `virtual void DrawVisualizationNotEditing(const UActorComponent* InComponent, const FSceneView* InView, FPrimitiveDrawInterface* InPDI, int32& InOutIconIndex) override;`
- L50 _protected prototype_ `virtual void DrawVisualizationEditing(const UActorComponent* InComponent, const FSceneView* InView, FPrimitiveDrawInterface* InPDI, int32& InOutIconIndex) override;`
- L52 _protected prototype_ `virtual bool HandleInputDeltaInternal(FEditorViewportClient* InViewportClient, FViewport* InViewport, const FVector& InAccumulatedTranslation, const FRotator& InAccumulatedRotation, const FVector& InAccumulatedScale) override;`
- L54 _protected prototype_ `virtual void StoreInitialValues() override;`
- L56 _protected prototype_ `void DrawNumSidesButton(const FMeshType* InDynMesh, const FSceneView* InView, FPrimitiveDrawInterface* InPDI, int32 InIconIndex, const FLinearColor& InColor) const;`
- L58 _protected prototype_ `void DrawAngleDegreeButton(const FMeshType* InDynMesh, const FSceneView* InView, FPrimitiveDrawInterface* InPDI, int32 InIconIndex, const FLinearColor& InColor, AvaAlignment InAngleAnchor) const;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheShapesEditor/Private/Visualizers/AvaShapeStarDynMeshVis.h` (Private)


#### class `FAvaShapeStarDynamicMeshVisualizer`  
`class FAvaShapeStarDynamicMeshVisualizer : public FAvaShapeRoundedPolygonDynamicMeshVisualizer`  
_L9-56_
- inherits: `FAvaShapeRoundedPolygonDynamicMeshVisualizer`
- L12 _public typedef_ `using Super = FAvaShapeRoundedPolygonDynamicMeshVisualizer;`
- L13 _public typedef_ `using FMeshType = UAvaShapeStarDynamicMesh;`
- L15 _public prototype_ `FAvaShapeStarDynamicMeshVisualizer();`
- L18 _public prototype_ `virtual TMap<UObject*, TArray<FProperty*>> GatherEditableProperties(UObject* InObject) const override;`
- L19 _public prototype_ `virtual bool VisProxyHandleClick(FEditorViewportClient* InViewportClient, HComponentVisProxy* InVisProxy, const FViewportClick& InClick) override;`
- L21 _public prototype_ `virtual bool GetWidgetLocation(const FEditorViewportClient* InViewportClient, FVector& OutLocation) const override;`
- L22 _public prototype_ `virtual bool GetWidgetMode(const FEditorViewportClient* InViewportClient, UE::Widget::EWidgetMode& OutMode) const override;`
- L23 _public prototype_ `virtual bool GetWidgetAxisList(const FEditorViewportClient* InViewportClient, UE::Widget::EWidgetMode InWidgetMode, EAxisList::Type& OutAxisList) const override;`
- L25 _public prototype_ `virtual bool GetWidgetAxisListDragOverride(const FEditorViewportClient* InViewportClient, UE::Widget::EWidgetMode InWidgetMode, EAxisList::Type& OutAxisList) const override;`
- L27 _public prototype_ `virtual bool ResetValue(FEditorViewportClient* InViewportClient, HHitProxy* InHitProxy) override;`
- L28 _public prototype_ `virtual bool IsEditing() const override;`
- L29 _public prototype_ `virtual void EndEditing() override;`
- L33 _protected member_ `FProperty* NumPointsProperty;`
- L34 _protected member_ `FProperty* InnerSizeProperty;`
- L36 _protected member_ `bool bEditingNumPoints;`
- L37 _protected member_ `int32 InitialNumPoints;`
- L38 _protected member_ `bool bEditingInnerSize;`
- L39 _protected member_ `float InitialInnerSize;`
- L41 _protected prototype_ `virtual void DrawVisualizationNotEditing(const UActorComponent* InComponent, const FSceneView* InView, FPrimitiveDrawInterface* InPDI, int32& InOutIconIndex) override;`
- L43 _protected prototype_ `virtual void DrawVisualizationEditing(const UActorComponent* InComponent, const FSceneView* InView, FPrimitiveDrawInterface* InPDI, int32& InOutIconIndex) override;`
- L46 _protected prototype_ `virtual bool HandleInputDeltaInternal(FEditorViewportClient* InViewportClient, FViewport* InViewport, const FVector& InAccumulatedTranslation, const FRotator& InAccumulatedRotation, const FVector& InAccumulatedScale) override;`
- L49 _protected prototype_ `virtual void StoreInitialValues() override;`
- L51 _protected prototype_ `void DrawNumPointsButton(const FMeshType* InDynMesh, const FSceneView* InView, FPrimitiveDrawInterface* InPDI, int32 InIconIndex, const FLinearColor& InColor) const;`
- L54 _protected prototype_ `void DrawInnerSizeButton(const FMeshType* InDynMesh, const FSceneView* InView, FPrimitiveDrawInterface* InPDI, int32 InIconIndex, const FLinearColor& InColor) const;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheShapesEditor/Private/Visualizers/AvaShapeTorusDynMeshVis.h` (Private)


#### class `FAvaShapeTorusDynamicMeshVisualizer`  
`class FAvaShapeTorusDynamicMeshVisualizer : public FAvaShape3DDynamicMeshVisualizer`  
_L9-63_
- inherits: `FAvaShape3DDynamicMeshVisualizer`
- L12 _public typedef_ `using Super = FAvaShape3DDynamicMeshVisualizer;`
- L13 _public typedef_ `using FMeshType = UAvaShapeTorusDynamicMesh;`
- L15 _public prototype_ `FAvaShapeTorusDynamicMeshVisualizer();`
- L18 _public prototype_ `virtual TMap<UObject*, TArray<FProperty*>> GatherEditableProperties(UObject* InObject) const override;`
- L19 _public prototype_ `virtual bool VisProxyHandleClick(FEditorViewportClient* InViewportClient, HComponentVisProxy* InVisProxy, const FViewportClick& InClick) override;`
- L21 _public prototype_ `virtual bool GetWidgetLocation(const FEditorViewportClient* InViewportClient, FVector& OutLocation) const override;`
- L22 _public prototype_ `virtual bool GetWidgetMode(const FEditorViewportClient* InViewportClient, UE::Widget::EWidgetMode& OutMode) const override;`
- L23 _public prototype_ `virtual bool GetWidgetAxisList(const FEditorViewportClient* InViewportClient, UE::Widget::EWidgetMode InWidgetMode, EAxisList::Type& OutAxisList) const override;`
- L25 _public prototype_ `virtual bool GetWidgetAxisListDragOverride(const FEditorViewportClient* InViewportClient, UE::Widget::EWidgetMode InWidgetMode, EAxisList::Type& OutAxisList) const override;`
- L27 _public prototype_ `virtual bool ResetValue(FEditorViewportClient* InViewportClient, HHitProxy* InHitProxy) override;`
- L28 _public prototype_ `virtual bool IsEditing() const override;`
- L29 _public prototype_ `virtual void EndEditing() override;`
- L33 _protected member_ `FProperty* NumSlicesProperty;`
- L34 _protected member_ `FProperty* NumSidesProperty;`
- L35 _protected member_ `FProperty* InnerSizeProperty;`
- L36 _protected member_ `FProperty* AngleDegreeProperty;`
- L38 _protected member_ `bool bEditingNumSlices;`
- L39 _protected member_ `uint8 InitialNumSlices;`
- L40 _protected member_ `bool bEditingNumSides;`
- L41 _protected member_ `uint8 InitialNumSides;`
- L42 _protected member_ `bool bEditingInnerSize;`
- L43 _protected member_ `float InitialInnerSize;`
- L44 _protected member_ `bool bEditingAngleDegree;`
- L45 _protected member_ `float InitialAngleDegree;`
- L47 _protected prototype_ `virtual void DrawVisualizationNotEditing(const UActorComponent* InComponent, const FSceneView* InView, FPrimitiveDrawInterface* InPDI, int32& InOutIconIndex) override;`
- L49 _protected prototype_ `virtual void DrawVisualizationEditing(const UActorComponent* InComponent, const FSceneView* InView, FPrimitiveDrawInterface* InPDI, int32& InOutIconIndex) override;`
- L51 _protected prototype_ `virtual bool HandleInputDeltaInternal(FEditorViewportClient* InViewportClient, FViewport* InViewport, const FVector& InAccumulatedTranslation, const FRotator& InAccumulatedRotation, const FVector& InAccumulatedScale) override;`
- L53 _protected prototype_ `virtual void StoreInitialValues() override;`
- L55 _protected prototype_ `void DrawNumSlicesButton(const FMeshType* InDynMesh, const FSceneView* InView, FPrimitiveDrawInterface* InPDI, int32 InIconIndex, const FLinearColor& InColor) const;`
- L57 _protected prototype_ `void DrawNumSidesButton(const FMeshType* InDynMesh, const FSceneView* InView, FPrimitiveDrawInterface* InPDI, int32 InIconIndex, const FLinearColor& InColor) const;`
- L59 _protected prototype_ `void DrawInnerSizeButton(const FMeshType* InDynMesh, const FSceneView* InView, FPrimitiveDrawInterface* InPDI, int32 InIconIndex, const FLinearColor& InColor) const;`
- L61 _protected prototype_ `void DrawAngleDegreeButton(const FMeshType* InDynMesh, const FSceneView* InView, FPrimitiveDrawInterface* InPDI, int32 InIconIndex, const FLinearColor& InColor) const;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheShapesEditor/Public/AvaShapeSprites.h` (Public)


#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace AvaShapes` (scope `UE`)
- L9 _variable_ `constexpr const TCHAR* BevelSprite = TEXT("Bev` (scope `UE::AvaShapes`)
- L10 _variable_ `constexpr const TCHAR* BreakSideSprite = TEXT("Bre` (scope `UE::AvaShapes`)
- L11 _variable_ `constexpr const TCHAR* ColorSelectionSprite = TEXT("Col` (scope `UE::AvaShapes`)
- L12 _variable_ `constexpr const TCHAR* CornerSprite = TEXT("Cor` (scope `UE::AvaShapes`)
- L13 _variable_ `constexpr const TCHAR* DepthSprite = TEXT("Dep` (scope `UE::AvaShapes`)
- L14 _variable_ `constexpr const TCHAR* InnerSizeSprite = TEXT("Inn` (scope `UE::AvaShapes`)
- L15 _variable_ `constexpr const TCHAR* LinearGradientSprite = TEXT("Lin` (scope `UE::AvaShapes`)
- L16 _variable_ `constexpr const TCHAR* NumPointsSprite = TEXT("Num` (scope `UE::AvaShapes`)
- L17 _variable_ `constexpr const TCHAR* NumSidesSprite = TEXT("Num` (scope `UE::AvaShapes`)
- L18 _variable_ `constexpr const TCHAR* TextMaxHeightSprite = TEXT("Tex` (scope `UE::AvaShapes`)
- L19 _variable_ `constexpr const TCHAR* TextMaxWidthSprite = TEXT("Tex` (scope `UE::AvaShapes`)
- L20 _variable_ `constexpr const TCHAR* TextScaleProportionallySprite = TEXT("Tex` (scope `UE::AvaShapes`)
- L21 _variable_ `constexpr const TCHAR* SizeSprite = TEXT("Siz` (scope `UE::AvaShapes`)
- L22 _variable_ `constexpr const TCHAR* SlantSprite = TEXT("Sla` (scope `UE::AvaShapes`)
- L23 _variable_ `constexpr const TCHAR* UVSprite = TEXT("UV"` (scope `UE::AvaShapes`)
