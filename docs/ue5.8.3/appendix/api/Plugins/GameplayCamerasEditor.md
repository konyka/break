# Plugins / GameplayCamerasEditor

- module root: `Plugins/Cameras/GameplayCameras/Source/GameplayCamerasEditor`
- headers: 126; symbols: 2062
- symbol kinds: class=130, delegate=20, enum=3, enumerator=11, function=110, macro=5, member=488, namespace=156, prototype=1093, struct=29, typedef=17
- PrivateDependencyModuleNames: ApplicationCore, AssetDefinition, AssetRegistry, AssetTools, BlueprintGraph, CinematicCamera, ContentBrowser, Core, CoreUObject, CurveEditor, DeveloperSettings, EditorFramework, EditorSubsystem, Engine, GameplayCameras, GameplayCamerasUncookedOnly, GraphEditor, InputCore, InteractiveToolsFramework, Kismet, KismetWidgets, LevelEditor, MovieScene, MovieSceneTools, MovieSceneTracks, Projects, RHI, RenderCore, RewindDebuggerInterface, Sequencer, Slate, SlateCore, StructUtilsEditor, StructViewer, TimeManagement, ToolMenus, ToolWidgets, TraceAnalysis, TraceInsights, TraceLog, TraceServices, UnrealEd
- PrivateIncludePathModuleNames: EditorWidgets, Kismet, MessageLog

### `Plugins/Cameras/GameplayCameras/Source/GameplayCamerasEditor/Private/ActorFactories/GameplayCameraActorFactory.h` (Private)


#### class `UGameplayCameraActorFactory`  
`class UGameplayCameraActorFactory : public UActorFactory`  
_L11-25_
- reflection: `UCLASS()`
- inherits: `UActorFactory`
- L17 _public prototype_ `UGameplayCameraActorFactory(const FObjectInitializer& ObjInit);`
- L22 _public prototype_ `virtual AActor* SpawnActor(UObject* InAsset, ULevel* InLevel, const FTransform& InTransform, const FActorSpawnParameters& InSpawnParams) override;` — UActorFactory interface.
- L23 _public prototype_ `virtual bool CanCreateActorFrom( const FAssetData& AssetData, FText& OutErrorMsg ) override;`
- L24 _public prototype_ `virtual UObject* GetAssetFromActorInstance(AActor* ActorInstance) override;`

### `Plugins/Cameras/GameplayCameras/Source/GameplayCamerasEditor/Private/ActorFactories/GameplayCameraRigActorFactory.h` (Private)


#### class `UGameplayCameraRigActorFactory`  
`class UGameplayCameraRigActorFactory : public UActorFactory`  
_L11-25_
- reflection: `UCLASS()`
- inherits: `UActorFactory`
- L17 _public prototype_ `UGameplayCameraRigActorFactory(const FObjectInitializer& ObjInit);`
- L22 _public prototype_ `virtual AActor* SpawnActor(UObject* InAsset, ULevel* InLevel, const FTransform& InTransform, const FActorSpawnParameters& InSpawnParams) override;` — UActorFactory interface.
- L23 _public prototype_ `virtual bool CanCreateActorFrom( const FAssetData& AssetData, FText& OutErrorMsg ) override;`
- L24 _public prototype_ `virtual UObject* GetAssetFromActorInstance(AActor* ActorInstance) override;`

### `Plugins/Cameras/GameplayCameras/Source/GameplayCamerasEditor/Private/AssetTools/AssetDefinition_CameraAsset.h` (Private)


#### class `UAssetDefinition_CameraAsset`  
`class UAssetDefinition_CameraAsset : public UAssetDefinitionDefault`  
_L11-24_
- reflection: `UCLASS()`
- inherits: `UAssetDefinitionDefault`
- L18 _public prototype_ `virtual FText GetAssetDisplayName() const override;` — UAssetDefinition interface
- L19 _public prototype_ `virtual FLinearColor GetAssetColor() const override;`
- L20 _public prototype_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override;`
- L21 _public prototype_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override;`
- L22 _public prototype_ `virtual FAssetOpenSupport GetAssetOpenSupport(const FAssetOpenSupportArgs& OpenSupportArgs) const override;`
- L23 _public prototype_ `virtual EAssetCommandResult OpenAssets(const FAssetOpenArgs& OpenArgs) const override;`

### `Plugins/Cameras/GameplayCameras/Source/GameplayCamerasEditor/Private/AssetTools/AssetDefinition_CameraRigAsset.h` (Private)


#### class `UAssetDefinition_CameraRigAsset`  
`class UAssetDefinition_CameraRigAsset : public UAssetDefinitionDefault`  
_L11-24_
- reflection: `UCLASS()`
- inherits: `UAssetDefinitionDefault`
- L18 _public prototype_ `virtual FText GetAssetDisplayName() const override;` — UAssetDefinition interface
- L19 _public prototype_ `virtual FLinearColor GetAssetColor() const override;`
- L20 _public prototype_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override;`
- L21 _public prototype_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override;`
- L22 _public prototype_ `virtual FAssetOpenSupport GetAssetOpenSupport(const FAssetOpenSupportArgs& OpenSupportArgs) const override;`
- L23 _public prototype_ `virtual EAssetCommandResult OpenAssets(const FAssetOpenArgs& OpenArgs) const override;`

### `Plugins/Cameras/GameplayCameras/Source/GameplayCamerasEditor/Private/AssetTools/AssetDefinition_CameraRigProxyAsset.h` (Private)


#### class `UAssetDefinition_CameraRigProxyAsset`  
`class UAssetDefinition_CameraRigProxyAsset : public UAssetDefinitionDefault`  
_L11-24_
- reflection: `UCLASS()`
- inherits: `UAssetDefinitionDefault`
- L18 _public prototype_ `virtual FText GetAssetDisplayName() const override;` — UAssetDefinition interface
- L19 _public prototype_ `virtual FLinearColor GetAssetColor() const override;`
- L20 _public prototype_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override;`
- L21 _public prototype_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override;`
- L22 _public prototype_ `virtual FAssetOpenSupport GetAssetOpenSupport(const FAssetOpenSupportArgs& OpenSupportArgs) const override;`
- L23 _public prototype_ `virtual EAssetCommandResult OpenAssets(const FAssetOpenArgs& OpenArgs) const override;`

### `Plugins/Cameras/GameplayCameras/Source/GameplayCamerasEditor/Private/AssetTools/AssetDefinition_CameraShakeAsset.h` (Private)


#### class `UAssetDefinition_CameraShakeAsset`  
`class UAssetDefinition_CameraShakeAsset : public UAssetDefinitionDefault`  
_L11-24_
- reflection: `UCLASS()`
- inherits: `UAssetDefinitionDefault`
- L18 _public prototype_ `virtual FText GetAssetDisplayName() const override;` — UAssetDefinition interface
- L19 _public prototype_ `virtual FLinearColor GetAssetColor() const override;`
- L20 _public prototype_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override;`
- L21 _public prototype_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override;`
- L22 _public prototype_ `virtual FAssetOpenSupport GetAssetOpenSupport(const FAssetOpenSupportArgs& OpenSupportArgs) const override;`
- L23 _public prototype_ `virtual EAssetCommandResult OpenAssets(const FAssetOpenArgs& OpenArgs) const override;`

### `Plugins/Cameras/GameplayCameras/Source/GameplayCamerasEditor/Private/AssetTools/AssetDefinition_CameraVariableCollection.h` (Private)


#### class `UAssetDefinition_CameraVariableCollection`  
`class UAssetDefinition_CameraVariableCollection : public UAssetDefinitionDefault`  
_L10-25_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UAssetDefinitionDefault`
- L16 _public prototype_ `static TConstArrayView<FAssetCategoryPath> StaticMenuCategories();`
- L19 _public prototype_ `virtual FText GetAssetDisplayName() const override;` — UAssetDefinition interface
- L20 _public prototype_ `virtual FLinearColor GetAssetColor() const override;`
- L21 _public prototype_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override;`
- L22 _public prototype_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override;`
- L23 _public prototype_ `virtual FAssetOpenSupport GetAssetOpenSupport(const FAssetOpenSupportArgs& OpenSupportArgs) const override;`
- L24 _public prototype_ `virtual EAssetCommandResult OpenAssets(const FAssetOpenArgs& OpenArgs) const override;`

### `Plugins/Cameras/GameplayCameras/Source/GameplayCamerasEditor/Private/Compat/EditorCompat.h` (Private)


#### Free symbols / members of external scopes

- L12 _typedef_ `using FSlateCompatVector2f = FVector2f;`
- L14 _typedef_ `using FPerformGraphActionLocation = const FVector2f&;`
- L18 _typedef_ `using FSlateCompatVector2f = FVector2D;`
- L20 _typedef_ `using FPerformGraphActionLocation = const FVector2D;`
- L22 _typedef_ `using FDelegateUserObjectConst = const void*;`

### `Plugins/Cameras/GameplayCameras/Source/GameplayCamerasEditor/Private/Compat/SResizeBox.h` (Private)


#### class `SVerticalResizeBox`  
`class SVerticalResizeBox : public SCompoundWidget`  
_L14-59_
- inherits: `SCompoundWidget`
- L17 _public prototype_ `DECLARE_DELEGATE_OneParam(FOnContentHeightChanged, float);`
- L20 _public function_ `SLATE_BEGIN_ARGS(SVerticalResizeBox) : _HandleHeight(5) , _ContentHeight(50) , _HandleColor(FLinearColor(0.0f, 0.0f, 0.0f, 0.0f)) , _HandleHighlightColor(FLinearColor(1.0f, 1.0f, 1.0f, 0.5f))`
- L26 _public prototype_ `SLATE_ARGUMENT(float, HandleHeight) SLATE_ATTRIBUTE(float, ContentHeight) SLATE_ATTRIBUTE(FLinearColor, HandleColor) SLATE_ATTRIBUTE(FLinearColor, HandleHighlightColor) SLATE_EVENT(FOnContentHeightChanged, ContentHeightChanged) SLATE_DEFAULT_SLOT(FArguments, Content);`
- L32 _public prototype_ `SLATE_END_ARGS();`
- L34 _public prototype_ `void Construct(const FArguments& InArgs);`
- L36 _public prototype_ `virtual FReply OnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L37 _public prototype_ `virtual FReply OnMouseButtonUp(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L38 _public prototype_ `virtual FReply OnMouseMove(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L39 _public prototype_ `virtual FCursorReply OnCursorQuery(const FGeometry& MyGeometry, const FPointerEvent& CursorEvent) const override;`
- L40 _public prototype_ `virtual int32 OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyClippingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const override;`
- L43 _private prototype_ `FOptionalSize GetHeightOverride() const;`
- L46 _private member_ `TOptional<float> LastMouseLocation;`
- L48 _private member_ `TAttribute<float> ContentHeight;`
- L49 _private member_ `float HandleHeight;`
- L51 _private member_ `float DragStartLocation;`
- L52 _private member_ `float DragStartContentHeight;`
- L54 _private member_ `TAttribute<FLinearColor> HandleColor;`
- L55 _private member_ `TAttribute<FLinearColor> HandleHighlightColor;`
- L56 _private member_ `FSlateBrush HandleBrush;`
- L58 _private member_ `FOnContentHeightChanged ContentHeightChanged;`

#### Free symbols / members of external scopes

- L17 _delegate_ `DECLARE_DELEGATE_OneParam(FOnContentHeightChanged, float);`

### `Plugins/Cameras/GameplayCameras/Source/GameplayCamerasEditor/Private/ComponentVisualizers/GameplayCameraComponentVisualizer.h` (Private)


#### class `UE::Cameras::FGameplayCameraComponentVisualizer`  
`class FGameplayCameraComponentVisualizer : public FComponentVisualizer`  
_L14-21_
- inherits: `FComponentVisualizer`
- L19 _public prototype_ `virtual void DrawVisualization(const UActorComponent* Component, const FSceneView* View, FPrimitiveDrawInterface* PDI) override;` — FComponentVisualizer interface.
- L20 _public prototype_ `virtual void DrawVisualizationHUD(const UActorComponent* Component, const FViewport* Viewport, const FSceneView* View, FCanvas* Canvas) override;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace Cameras` (scope `UE`)

### `Plugins/Cameras/GameplayCameras/Source/GameplayCamerasEditor/Private/CurveEditor/CurvePropertyEditorTreeItem.h` (Private)


#### struct `UE::Cameras::FCurvePropertyInfo`  
`struct FCurvePropertyInfo`  
_L19-33_
- desc: Structure for providing information about a curve property, to be shown in a curve editor tree item (see FCurvePropertyEditorTreeItem).
- L22 _public member_ `FText DisplayName;` — Display name of the tree item.
- L24 _public member_ `FLinearColor Color = FLinearColor::White;` — Color of the tree item and any associated curve.
- L27 _public member_ `FName PropertyName;` — Name of the property on the owning object.
- L29 _public member_ `TWeakObjectPtr<> WeakOwner;` — The object on which the curve property resides.
- L32 _public member_ `FRichCurve* Curve = nullptr;` — The curve associated with the tree item.

#### struct `UE::Cameras::FCurvePropertyEditorTreeItem`  
`struct FCurvePropertyEditorTreeItem : public ICurveEditorTreeItem`  
_L38-54_
- inherits: `ICurveEditorTreeItem`
- desc: Curve editor tree view item for a curve tied to an object's property.
- L40 _public member_ `FCurvePropertyInfo Info;`
- L44 _public prototype_ `FCurvePropertyEditorTreeItem();`
- L45 _public prototype_ `FCurvePropertyEditorTreeItem(FCurvePropertyInfo&& InInfo);`
- L46 _public prototype_ `FCurvePropertyEditorTreeItem(const FText& InDisplayName, TWeakObjectPtr<> InWeakOwner);`
- L47 _public prototype_ `FCurvePropertyEditorTreeItem(FRichCurve* InRichCurve, const FText& InCurveName, const FLinearColor& InCurveColor, TWeakObjectPtr<> InWeakOwner);`
- L49 _public function_ `UObject* GetOwner() const`
- L52 _public prototype_ `virtual TSharedPtr<SWidget> GenerateCurveEditorTreeWidget(const FName& InColumnName, TWeakPtr<FCurveEditor> InCurveEditor, FCurveEditorTreeItemID InTreeItemID, const TSharedRef<ITableRow>& TableRow) override;` — ICurveEditorTreeItem interface.
- L53 _public prototype_ `virtual void CreateCurveModels(TArray<TUniquePtr<FCurveModel>>& OutCurveModels) override;`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace Cameras` (scope `UE`)

### `Plugins/Cameras/GameplayCameras/Source/GameplayCamerasEditor/Private/Debugger/GameplayCamerasDebugger.h` (Private)


#### class `UE::Cameras::FGameplayCamerasDebugger`  
`class FGameplayCamerasDebugger`  
_L10-12_

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace Cameras` (scope `UE`)

### `Plugins/Cameras/GameplayCameras/Source/GameplayCamerasEditor/Private/Debugger/SBlendStacksDebugPanel.h` (Private)


#### class `UE::Cameras::SBlendStacksDebugPanel`  
`class SBlendStacksDebugPanel : public SCompoundWidget`  
_L13-21_
- inherits: `SCompoundWidget`
- L17 _public function_ `SLATE_BEGIN_ARGS(SBlendStacksDebugPanel)`
- L18 _public prototype_ `SLATE_END_ARGS();`
- L20 _public prototype_ `void Construct(const FArguments& InArgs);`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace Cameras` (scope `UE`)

### `Plugins/Cameras/GameplayCameras/Source/GameplayCamerasEditor/Private/Debugger/SCameraDirectorTreeDebugPanel.h` (Private)


#### class `UE::Cameras::SCameraDirectorTreeDebugPanel`  
`class SCameraDirectorTreeDebugPanel : public SCompoundWidget`  
_L13-21_
- inherits: `SCompoundWidget`
- L17 _public function_ `SLATE_BEGIN_ARGS(SCameraDirectorTreeDebugPanel)`
- L18 _public prototype_ `SLATE_END_ARGS();`
- L20 _public prototype_ `void Construct(const FArguments& InArgs);`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace Cameras` (scope `UE`)

### `Plugins/Cameras/GameplayCameras/Source/GameplayCamerasEditor/Private/Debugger/SCameraNodeTreeDebugPanel.h` (Private)


#### class `UE::Cameras::SCameraNodeTreeDebugPanel`  
`class SCameraNodeTreeDebugPanel : public SCompoundWidget`  
_L13-21_
- inherits: `SCompoundWidget`
- L17 _public function_ `SLATE_BEGIN_ARGS(SCameraNodeTreeDebugPanel)`
- L18 _public prototype_ `SLATE_END_ARGS();`
- L20 _public prototype_ `void Construct(const FArguments& InArgs);`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace Cameras` (scope `UE`)

### `Plugins/Cameras/GameplayCameras/Source/GameplayCamerasEditor/Private/Debugger/SCameraPoseStatsDebugPanel.h` (Private)


#### class `UE::Cameras::SCameraPoseStatsDebugPanel`  
`class SCameraPoseStatsDebugPanel : public SCompoundWidget`  
_L13-21_
- inherits: `SCompoundWidget`
- L17 _public function_ `SLATE_BEGIN_ARGS(SCameraPoseStatsDebugPanel)`
- L18 _public prototype_ `SLATE_END_ARGS();`
- L20 _public prototype_ `void Construct(const FArguments& InArgs);`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace Cameras` (scope `UE`)

### `Plugins/Cameras/GameplayCameras/Source/GameplayCamerasEditor/Private/Debugger/SDebugCategoryButton.h` (Private)


#### class `UE::Cameras::SDebugCategoryButton`  
`class SDebugCategoryButton : public SCompoundWidget`  
_L16-44_
- inherits: `SCompoundWidget`
- L19 _public function_ `SLATE_BEGIN_ARGS(SDebugCategoryButton)`
- L20 _public prototype_ `SLATE_ATTRIBUTE(const FSlateBrush*, IconImage) SLATE_ATTRIBUTE(FText, DisplayText) SLATE_ATTRIBUTE(FText, ToolTipText) SLATE_ATTRIBUTE(FString, DebugCategoryName) SLATE_ATTRIBUTE(bool, IsDebugCategoryActive) SLATE_EVENT(FOnDebugCategoryChangeRequested, RequestDebugCategoryChange) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L32 _private prototype_ `ECheckBoxState GetDebugCategoryCheckState() const;`
- L33 _private prototype_ `void OnDebugCategoryCheckStateChanged(ECheckBoxState CheckBoxState);`
- L37 _private member_ `FString DebugCategoryName;`
- L38 _private member_ `TAttribute<bool> IsDebugCategoryActive;`
- L39 _private member_ `FOnDebugCategoryChangeRequested RequestDebugCategoryChange;`
- L41 _private member_ `const FSlateBrush* ActiveModeBorderImage;`
- L42 _private member_ `const FSlateBrush* InactiveModeBorderImage;`
- L43 _private member_ `const FSlateBrush* HoverBorderImage;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace Cameras` (scope `UE`)
- L14 _delegate_ `DECLARE_DELEGATE_OneParam(FOnDebugCategoryChangeRequested, const FString&);`
- L14 _prototype_ `DECLARE_DELEGATE_OneParam(FOnDebugCategoryChangeRequested, const FString&);` (scope `UE::Cameras`)

### `Plugins/Cameras/GameplayCameras/Source/GameplayCamerasEditor/Private/Debugger/SDebugWidgetUtils.h` (Private)


#### class `UE::Cameras::SDebugWidgetUtils`  
`class SDebugWidgetUtils`  
_L19-37_
- desc: Utility class for creating Slate widgets that drive console variables.
- L24 _public prototype_ `static TSharedRef<SWidget> CreateConsoleVariableCheckBox(const FText& Text, const FString& ConsoleVariableName);` — Creates a checkbox that sets a boolean console variable.
- L26 _public prototype_ `static TSharedRef<SWidget> CreateConsoleVariableSpinBox(const FString& ConsoleVariableName);` — Creates a spinbox that sets a float console variable.
- L28 _public prototype_ `static TSharedRef<SWidget> CreateConsoleVariableSpinBox(const FText& Text, const FString& ConsoleVariableName);` — Creates a spinbox that sets a float console variable, with a text label.
- L30 _public prototype_ `static TSharedRef<SWidget> CreateConsoleVariableComboBox(const FString& ConsoleVariableName, TArray<TSharedPtr<FString>>* OptionsSource);` — Creates a combox box that sets a string console variable.
- L32 _public prototype_ `static TSharedRef<SWidget> CreateConsoleVariableTextBox(const FString& ConsoleVariableName);` — Creates a text box that sets a string console variable.
- L36 _private prototype_ `static IConsoleVariable* GetConsoleVariable(const FString& ConsoleVariableName);`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace Cameras` (scope `UE`)

### `Plugins/Cameras/GameplayCameras/Source/GameplayCamerasEditor/Private/Debugger/SEvaluationServicesDebugPanel.h` (Private)


#### class `UE::Cameras::SEvaluationServicesDebugPanel`  
`class SEvaluationServicesDebugPanel : public SCompoundWidget`  
_L13-21_
- inherits: `SCompoundWidget`
- L17 _public function_ `SLATE_BEGIN_ARGS(SEvaluationServicesDebugPanel)`
- L18 _public prototype_ `SLATE_END_ARGS();`
- L20 _public prototype_ `void Construct(const FArguments& InArgs);`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace Cameras` (scope `UE`)

### `Plugins/Cameras/GameplayCameras/Source/GameplayCamerasEditor/Private/Debugger/SGameplayCamerasDebugger.h` (Private)


#### class `UE::Cameras::FGameplayCamerasDebuggerContext`  
`class FGameplayCamerasDebuggerContext`  
_L23-47_
- L27 _public prototype_ `FGameplayCamerasDebuggerContext();`
- L28 _public prototype_ `~FGameplayCamerasDebuggerContext();`
- L30 _public prototype_ `UWorld* GetContext();`
- L32 _public function_ `FSimpleMulticastDelegate& OnContextChanged()`
- L36 _private prototype_ `void UpdateContext();`
- L37 _private prototype_ `void InvalidateContext();`
- L39 _private prototype_ `void OnPieEvent(bool bIsSimulating);`
- L40 _private prototype_ `void OnMapChange(uint32 MapChangeFlags);`
- L41 _private prototype_ `void OnWorldListChanged(UWorld* InWorld);`
- L45 _private member_ `TWeakObjectPtr<UWorld> WeakContext;`
- L46 _private member_ `FSimpleMulticastDelegate OnContextChangedEvent;`

#### class `UE::Cameras::SGameplayCamerasDebugger`  
`class SGameplayCamerasDebugger : public SCompoundWidget`  
_L49-114_
- inherits: `SCompoundWidget`
- L53 _public member_ `static const FName WindowName;`
- L54 _public member_ `static const FName MenubarName;`
- L55 _public member_ `static const FName ToolbarName;`
- L57 _public prototype_ `static void RegisterTabSpawners();`
- L58 _public prototype_ `static TSharedRef<SDockTab> SpawnGameplayCamerasDebugger(const FSpawnTabArgs& Args);`
- L59 _public prototype_ `static void UnregisterTabSpawners();`
- L63 _public function_ `SLATE_BEGIN_ARGS(SGameplayCamerasDebugger)`
- L64 _public prototype_ `SLATE_END_ARGS();`
- L66 _public prototype_ `SGameplayCamerasDebugger();`
- L67 _public prototype_ `virtual ~SGameplayCamerasDebugger();`
- L69 _public prototype_ `void Construct(const FArguments& InArgs);`
- L74 _protected prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;` — SWidget interface.
- L78 _protected prototype_ `static SGameplayCamerasDebugger* FromContext(UToolMenu* InMenu);`
- L79 _protected prototype_ `TSharedRef<SWidget> ConstructMenubar();`
- L80 _protected prototype_ `TSharedRef<SWidget> ConstructToolbar(TSharedRef<FUICommandList> InCommandList);`
- L81 _protected prototype_ `TSharedRef<SWidget> ConstructGeneralOptions(TSharedRef<FUICommandList> InCommandList);`
- L82 _protected prototype_ `void ConstructDebugPanels();`
- L84 _protected prototype_ `void InitializeColorSchemeNames();`
- L86 _protected prototype_ `static bool IsDebugCategoryActive(FString InCategoryName);`
- L87 _protected prototype_ `void SetActiveDebugCategoryPanel(FString InCategoryName);`
- L89 _protected prototype_ `void ToggleDebugDraw();`
- L90 _protected prototype_ `bool IsDebugDrawing() const;`
- L91 _protected prototype_ `FText GetToggleDebugDrawText() const;`
- L92 _protected prototype_ `FSlateIcon GetToggleDebugDrawIcon() const;`
- L94 _protected prototype_ `void GetCameraSystemPickerContent(UToolMenu* ToolMenu);`
- L96 _protected prototype_ `void BindToCameraSystem(FCameraSystemDebugID InDebugID);`
- L97 _protected prototype_ `bool IsBoundToCameraSystem(FCameraSystemDebugID InDebugID);`
- L99 _protected prototype_ `void OnDebugContextChanged();`
- L103 _private member_ `FName GameplayCamerasEditorStyleName;`
- L105 _private member_ `FGameplayCamerasDebuggerContext DebugContext;`
- L106 _private member_ `bool bRefreshDebugID = false;`
- L108 _private member_ `TSharedPtr<SBox> PanelHost;`
- L110 _private member_ `TSharedPtr<SWidget> EmptyPanel;`
- L111 _private member_ `TMap<FString, TSharedPtr<SWidget>> DebugPanels;`
- L113 _private member_ `TArray<TSharedPtr<FString>> ColorSchemeNames;`

#### class `UGameplayCamerasDebuggerMenuContext`  
`class UGameplayCamerasDebuggerMenuContext : public UObject`  
_L119-126_
- reflection: `UCLASS()`
- inherits: `UObject`
- L125 _public member_ `TWeakPtr<UE::Cameras::SGameplayCamerasDebugger> CamerasDebugger;`

#### Free symbols / members of external scopes

- L20 _namespace_ `namespace UE`
- L20 _namespace_ `namespace Cameras` (scope `UE`)

### `Plugins/Cameras/GameplayCameras/Source/GameplayCamerasEditor/Private/Editors/CameraNodeGraphPinColors.h` (Private)


#### struct `UE::Cameras::FCameraNodeGraphPinColors`  
`struct FCameraNodeGraphPinColors`  
_L12-29_
- L14 _public prototype_ `void Initialize();`
- L16 _public prototype_ `FLinearColor GetPinColor(const FName& TypeName) const;`
- L17 _public prototype_ `FLinearColor GetContextDataPinColor(const FName& DataTypeName) const;`
- L21 _private member_ `TMap<FName, FLinearColor> PinColors;`
- L22 _private member_ `FLinearColor DefaultPinColor;`
- L23 _private member_ `FLinearColor NamePinColor;`
- L24 _private member_ `FLinearColor StringPinColor;`
- L25 _private member_ `FLinearColor EnumPinColor;`
- L26 _private member_ `FLinearColor StructPinColor;`
- L27 _private member_ `FLinearColor ObjectPinColor;`
- L28 _private member_ `FLinearColor ClassPinColor;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace Cameras` (scope `UE`)

### `Plugins/Cameras/GameplayCameras/Source/GameplayCamerasEditor/Private/Editors/SCameraVariablePicker.h` (Private)


#### class `UE::Cameras::SCameraVariablePicker`  
`class SCameraVariablePicker : public SCompoundWidget`  
_L20-55_
- inherits: `SCompoundWidget`
- desc: A picker widget for selecting a camera variable.
- L24 _public function_ `SLATE_BEGIN_ARGS(SCameraVariablePicker)`
- L26 _public prototype_ `SLATE_ARGUMENT(FCameraVariablePickerConfig, CameraVariablePickerConfig) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L33 _private prototype_ `void SetupInitialSelections(UCameraVariableAsset* InSelectedCameraVariable);`
- L35 _private prototype_ `TSharedRef<SWidget> BuildVariableCollectionAssetPicker(const FCameraVariablePickerConfig& InPickerConfig);`
- L37 _private prototype_ `void OnAssetSelected(const FAssetData& SelectedAsset);`
- L39 _private prototype_ `void UpdateVariableListItemsSource(UCameraVariableCollection* InCameraVariableCollection = nullptr);`
- L40 _private prototype_ `TSharedRef<ITableRow> OnVariableListGenerateRow(UCameraVariableAsset* Item, const TSharedRef<STableViewBase>& OwnerTable);`
- L41 _private prototype_ `void OnVariableListSelectionChanged(UCameraVariableAsset* Item, ESelectInfo::Type SelectInfo) const;`
- L43 _private prototype_ `FText GetCameraVariableCountText() const;`
- L47 _private member_ `TSharedPtr<SListView<UCameraVariableAsset*>> CameraVariableListView;`
- L48 _private member_ `TArray<UCameraVariableAsset*> CameraVariableItemsSource;`
- L50 _private member_ `UClass* VariableClass = nullptr;`
- L52 _private member_ `FGetCurrentSelectionDelegate GetCurrentAssetPickerSelection;`
- L54 _private member_ `FOnCameraVariableSelected OnCameraVariableSelected;`

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace Cameras` (scope `UE`)

### `Plugins/Cameras/GameplayCameras/Source/GameplayCamerasEditor/Private/Factories/CameraAssetFactory.h` (Private)


#### class `UCameraAssetFactory`  
`class UCameraAssetFactory : public UFactory`  
_L16-34_
- reflection: `UCLASS(hidecategories=Object)`
- inherits: `UFactory`
- desc: Implements a factory for UCameraAsset objects.
- L22 _public prototype_ `UCameraAssetFactory(const FObjectInitializer& ObjectInitializer);`
- L25 _public prototype_ `virtual UObject* FactoryCreateNew(UClass* Class, UObject* Parent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;` — UFactory Interface
- L26 _public prototype_ `virtual bool ConfigureProperties() override;`
- L27 _public prototype_ `virtual bool ShouldShowInNewMenu() const override;`
- L33 _private member_ `TSubclassOf<UCameraDirector> CameraDirectorClass;` — `UPROPERTY(EditAnywhere, Category=Camera)` — The type of camera director to create for this asset.

### `Plugins/Cameras/GameplayCameras/Source/GameplayCamerasEditor/Private/Factories/CameraRigAssetFactory.h` (Private)


#### class `UCameraRigAssetFactory`  
`class UCameraRigAssetFactory : public UFactory`  
_L15-25_
- reflection: `UCLASS(hidecategories=Object)`
- inherits: `UFactory`
- desc: Implements a factory for UCameraRigAsset objects.
- L19 _private prototype_ `UCameraRigAssetFactory(const FObjectInitializer& ObjectInitializer);`
- L22 _private prototype_ `virtual UObject* FactoryCreateNew(UClass* Class, UObject* Parent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;` — UFactory Interface
- L23 _private prototype_ `virtual bool ConfigureProperties() override;`
- L24 _private prototype_ `virtual bool ShouldShowInNewMenu() const override;`

### `Plugins/Cameras/GameplayCameras/Source/GameplayCamerasEditor/Private/Factories/CameraRigProxyAssetFactory.h` (Private)


#### class `UCameraRigProxyAssetFactory`  
`class UCameraRigProxyAssetFactory : public UFactory`  
_L15-25_
- reflection: `UCLASS(hidecategories=Object)`
- inherits: `UFactory`
- desc: Implements a factory for UCameraRigProxyAsset objects.
- L19 _private prototype_ `UCameraRigProxyAssetFactory(const FObjectInitializer& ObjectInitializer);`
- L22 _private prototype_ `virtual UObject* FactoryCreateNew(UClass* Class, UObject* Parent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;` — UFactory Interface
- L23 _private prototype_ `virtual bool ConfigureProperties() override;`
- L24 _private prototype_ `virtual bool ShouldShowInNewMenu() const override;`

### `Plugins/Cameras/GameplayCameras/Source/GameplayCamerasEditor/Private/Factories/CameraShakeAssetFactory.h` (Private)


#### class `UCameraShakeAssetFactory`  
`class UCameraShakeAssetFactory : public UFactory`  
_L15-25_
- reflection: `UCLASS(hidecategories=Object)`
- inherits: `UFactory`
- desc: Implements a factory for UCameraShakeAsset objects.
- L19 _private prototype_ `UCameraShakeAssetFactory(const FObjectInitializer& ObjectInitializer);`
- L22 _private prototype_ `virtual UObject* FactoryCreateNew(UClass* Class, UObject* Parent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;` — UFactory Interface
- L23 _private prototype_ `virtual bool ConfigureProperties() override;`
- L24 _private prototype_ `virtual bool ShouldShowInNewMenu() const override;`

### `Plugins/Cameras/GameplayCameras/Source/GameplayCamerasEditor/Private/Factories/CameraVariableCollectionFactory.h` (Private)


#### class `UCameraVariableCollectionFactory`  
`class UCameraVariableCollectionFactory : public UFactory`  
_L15-26_
- reflection: `UCLASS(hidecategories=Object)`
- inherits: `UFactory`
- desc: Implements a factory for camera variable collections.
- L21 _public prototype_ `UCameraVariableCollectionFactory(const FObjectInitializer& ObjectInit);`
- L24 _public prototype_ `virtual FText GetDisplayName() const override;` — UFactory Interface
- L25 _public prototype_ `virtual UObject* FactoryCreateNew(UClass* Class, UObject* Parent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;`

### `Plugins/Cameras/GameplayCameras/Source/GameplayCamerasEditor/Private/Family/CameraAssetFamily.h` (Private)


#### class `UE::Cameras::FCameraAssetFamily`  
`class FCameraAssetFamily : public IGameplayCamerasFamily`  
_L12-29_
- inherits: `IGameplayCamerasFamily`
- L16 _public prototype_ `FCameraAssetFamily(UCameraAsset* InRootAsset);`
- L19 _public prototype_ `virtual UObject* GetRootAsset() const override;` — IGameplayCamerasFamily interface.
- L20 _public prototype_ `virtual void GetAssetTypes(TArray<UClass*>& OutAssetTypes) const override;`
- L21 _public prototype_ `virtual void FindAssetsOfType(UClass* InAssetType, TArray<FAssetData>& OutAssets) const override;`
- L22 _public prototype_ `virtual FText GetAssetTypeTooltip(UClass* InAssetType) const override;`
- L23 _public prototype_ `virtual const FSlateBrush* GetAssetIcon(UClass* InAssetType) const override;`
- L24 _public prototype_ `virtual FSlateColor GetAssetTint(UClass* InAssetType) const override;`
- L28 _private member_ `UCameraAsset* RootAsset;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace Cameras` (scope `UE`)

### `Plugins/Cameras/GameplayCameras/Source/GameplayCamerasEditor/Private/Family/CameraRigAssetFamily.h` (Private)


#### class `UE::Cameras::FCameraRigAssetFamily`  
`class FCameraRigAssetFamily : public IGameplayCamerasFamily`  
_L12-29_
- inherits: `IGameplayCamerasFamily`
- L16 _public prototype_ `FCameraRigAssetFamily(UCameraRigAsset* InRootAsset);`
- L19 _public prototype_ `virtual UObject* GetRootAsset() const override;` — IGameplayCamerasFamily interface.
- L20 _public prototype_ `virtual void GetAssetTypes(TArray<UClass*>& OutAssetTypes) const override;`
- L21 _public prototype_ `virtual void FindAssetsOfType(UClass* InAssetType, TArray<FAssetData>& OutAssets) const override;`
- L22 _public prototype_ `virtual FText GetAssetTypeTooltip(UClass* InAssetType) const override;`
- L23 _public prototype_ `virtual const FSlateBrush* GetAssetIcon(UClass* InAssetType) const override;`
- L24 _public prototype_ `virtual FSlateColor GetAssetTint(UClass* InAssetType) const override;`
- L28 _private member_ `UCameraRigAsset* RootAsset;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace Cameras` (scope `UE`)

### `Plugins/Cameras/GameplayCameras/Source/GameplayCamerasEditor/Private/Family/CameraRigProxyAssetFamily.h` (Private)


#### class `UE::Cameras::FCameraRigProxyAssetFamily`  
`class FCameraRigProxyAssetFamily : public IGameplayCamerasFamily`  
_L12-29_
- inherits: `IGameplayCamerasFamily`
- L16 _public prototype_ `FCameraRigProxyAssetFamily(UCameraRigProxyAsset* InRootAsset);`
- L19 _public prototype_ `virtual UObject* GetRootAsset() const override;` — IGameplayCamerasFamily interface.
- L20 _public prototype_ `virtual void GetAssetTypes(TArray<UClass*>& OutAssetTypes) const override;`
- L21 _public prototype_ `virtual void FindAssetsOfType(UClass* InAssetType, TArray<FAssetData>& OutAssets) const override;`
- L22 _public prototype_ `virtual FText GetAssetTypeTooltip(UClass* InAssetType) const override;`
- L23 _public prototype_ `virtual const FSlateBrush* GetAssetIcon(UClass* InAssetType) const override;`
- L24 _public prototype_ `virtual FSlateColor GetAssetTint(UClass* InAssetType) const override;`
- L28 _private member_ `UCameraRigProxyAsset* RootAsset;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace Cameras` (scope `UE`)

### `Plugins/Cameras/GameplayCameras/Source/GameplayCamerasEditor/Private/Family/GameplayCamerasFamilyHelper.h` (Private)


#### class `UE::Cameras::FGameplayCamerasFamilyHelper`  
`class FGameplayCamerasFamilyHelper`  
_L18-29_
- L22 _public prototype_ `static const FSlateBrush* GetAssetIcon(UClass* InAssetType);`
- L24 _public prototype_ `static FSlateColor GetAssetTint(UClass* InAssetType);`
- L26 _public prototype_ `static void FindRelatedCameraAssets(UCameraRigAsset* CameraRig, TArray<FAssetData>& OutCameraAssets);`
- L27 _public prototype_ `static void FindRelatedCameraAssets(UCameraRigProxyAsset* CameraRigProxy, TArray<FAssetData>& OutCameraAssets);`
- L28 _public prototype_ `static void GetExternalCameraDirectorAssets(TArrayView<FAssetData> CameraAssets, TArray<FAssetData>& OutExternalCameraDirectors);`

#### Free symbols / members of external scopes

- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace Cameras` (scope `UE`)

### `Plugins/Cameras/GameplayCameras/Source/GameplayCamerasEditor/Private/GameplayCamerasLiveEditManager.h` (Private)


#### class `UE::Cameras::FGameplayCamerasLiveEditManager`  
`class FGameplayCamerasLiveEditManager : public IGameplayCamerasLiveEditManager`  
_L15-50_
- inherits: `IGameplayCamerasLiveEditManager`
- L19 _public prototype_ `FGameplayCamerasLiveEditManager();`
- L20 _public prototype_ `~FGameplayCamerasLiveEditManager();`
- L25 _public prototype_ `virtual bool CanRunInEditor() const override;` — IGameplayCamerasLiveEditManager interface
- L26 _public prototype_ `virtual void NotifyPostBuildAsset(const UPackage* InAssetPackage) const override;`
- L27 _public prototype_ `virtual void AddListener(const UPackage* InAssetPackage, IGameplayCamerasLiveEditListener* Listener) override;`
- L28 _public prototype_ `virtual void RemoveListener(const UPackage* InAssetPackage, IGameplayCamerasLiveEditListener* Listener) override;`
- L29 _public prototype_ `virtual void NotifyPostEditChangeProperty(const UCameraNode* InCameraNode, const FPropertyChangedEvent& PropertyChangedEvent) const override;`
- L30 _public prototype_ `virtual void AddListener(const UCameraNode* InCameraNode, IGameplayCamerasLiveEditListener* Listener) override;`
- L31 _public prototype_ `virtual void RemoveListener(const UCameraNode* InCameraNode, IGameplayCamerasLiveEditListener* Listener) override;`
- L32 _public prototype_ `virtual void RemoveListener(IGameplayCamerasLiveEditListener* Listener) override;`
- L36 _private prototype_ `void OnPostGarbageCollection();`
- L37 _private prototype_ `void OnBeginPIE(const bool bSimulate);`
- L39 _private prototype_ `void RemoveGarbage();`
- L43 _private typedef_ `using FListenerArray = TArray<IGameplayCamerasLiveEditListener*, TInlineAllocator<4>>;`
- L45 _private typedef_ `using FPackageListenerMap = TMap<TWeakObjectPtr<const UPackage>, FListenerArray>;`
- L46 _private member_ `FPackageListenerMap PackageListenerMap;`
- L48 _private typedef_ `using FNodeListenerMap = TMap<TWeakObjectPtr<const UCameraNode>, FListenerArray>;`
- L49 _private member_ `FNodeListenerMap NodeListenerMap;`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace Cameras` (scope `UE`)

### `Plugins/Cameras/GameplayCameras/Source/GameplayCamerasEditor/Private/Helpers/AssetTypeMenuOverlayHelper.h` (Private)


#### class `UE::Cameras::FAssetTypeMenuOverlayHelper`  
`class FAssetTypeMenuOverlayHelper`  
_L14-19_
- L18 _public prototype_ `static TSharedRef<SWidget> CreateMenuOverlay(UClass* InAssetType);`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace Cameras` (scope `UE`)

### `Plugins/Cameras/GameplayCameras/Source/GameplayCamerasEditor/Private/Helpers/CameraDirectorClassPicker.h` (Private)


#### class `UE::Cameras::FCameraDirectorClassPicker`  
`class FCameraDirectorClassPicker`  
_L13-27_
- L17 _public prototype_ `FCameraDirectorClassPicker();`
- L19 _public prototype_ `void AddCommonCameraDirector(TSubclassOf<UCameraDirector> InClass);`
- L20 _public prototype_ `void ResetCommonCameraDirectors();`
- L22 _public prototype_ `bool PickCameraDirectorClass(TSubclassOf<UCameraDirector>& OutChosenClass);`
- L26 _private member_ `TArray<TSubclassOf<UCameraDirector>> CommonCameraDirectorClasses;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace Cameras` (scope `UE`)

### `Plugins/Cameras/GameplayCameras/Source/GameplayCamerasEditor/Private/Sequencer/CameraFramingZoneTrackEditor.h` (Private)


#### class `UE::Cameras::FCameraFramingZoneTrackEditor`  
`class FCameraFramingZoneTrackEditor : public FPropertyTrackEditor<UMovieSceneCameraFramingZoneTrack>`  
_L25-51_
- inherits: `FPropertyTrackEditor<UMovieSceneCameraFramingZoneTrack>`
- L29 _public function_ `FCameraFramingZoneTrackEditor(TSharedRef<ISequencer> InSequencer) : FPropertyTrackEditor(InSequencer, GetAnimatedPropertyTypes())`
- L34 _public function_ `static TArray<FAnimatedPropertyKey, TInlineAllocator<1>> GetAnimatedPropertyTypes()`
- L39 _public prototype_ `static TSharedRef<ISequencerTrackEditor> CreateTrackEditor(TSharedRef<ISequencer> OwningSequencer);`
- L43 _protected prototype_ `virtual void GenerateKeysFromPropertyChanged( const FPropertyChangedParams& PropertyChangedParams, UMovieSceneSection* SectionToKey, FGeneratedTrackKeys& OutGeneratedKeys) override;`
- L47 _private member_ `static FName LeftName;`
- L48 _private member_ `static FName TopName;`
- L49 _private member_ `static FName RightName;`
- L50 _private member_ `static FName BottomName;`

#### Free symbols / members of external scopes

- L22 _namespace_ `namespace UE`
- L22 _namespace_ `namespace Cameras` (scope `UE`)

### `Plugins/Cameras/GameplayCameras/Source/GameplayCamerasEditor/Private/Sequencer/GameplayCameraComponentTrackEditor.h` (Private)


#### class `FGameplayCameraComponentTrackEditor`  
`class FGameplayCameraComponentTrackEditor : public FMovieSceneTrackEditor`  
_L24-76_
- inherits: `FMovieSceneTrackEditor`
- L28 _public prototype_ `static TSharedRef<ISequencerTrackEditor> CreateTrackEditor(TSharedRef<ISequencer> OwningSequencer);`
- L30 _public prototype_ `FGameplayCameraComponentTrackEditor(TSharedRef<ISequencer> InSequencer);`
- L35 _protected prototype_ `virtual void BindCommands(TSharedRef<FUICommandList> SequencerCommandBindings) override;` — ISequencerTrackEditor interface.
- L36 _protected prototype_ `virtual void BuildAddTrackMenu(FMenuBuilder& MenuBuilder) override;`
- L37 _protected prototype_ `virtual void BuildTrackContextMenu(FMenuBuilder& MenuBuilder, UMovieSceneTrack* Track) override;`
- L38 _protected prototype_ `virtual void ExtendObjectBindingTrackMenu(TSharedRef<FExtender> Extender, const TArray<FGuid>& ObjectBindings, const UClass* ObjectClass) override;`
- L39 _protected prototype_ `virtual TSharedPtr<SWidget> BuildOutlinerEditWidget(const FGuid& ObjectBinding, UMovieSceneTrack* Track, const FBuildEditWidgetParams& Params) override;`
- L40 _protected prototype_ `virtual TSharedPtr<SWidget> BuildOutlinerColumnWidget(const FBuildColumnWidgetParams& Params, const FName& ColumnName) override;`
- L41 _protected prototype_ `virtual TSharedRef<ISequencerSection> MakeSectionInterface(UMovieSceneSection& SectionObject, UMovieSceneTrack& Track, FGuid ObjectBinding) override;`
- L42 _protected prototype_ `virtual void OnRelease() override;`
- L43 _protected prototype_ `virtual bool SupportsType(TSubclassOf<UMovieSceneTrack> Type) const override;`
- L44 _protected prototype_ `virtual void Tick(float DeltaTime) override;`
- L45 _protected prototype_ `virtual const FSlateBrush* GetIconBrush() const override;`
- L46 _protected prototype_ `virtual bool OnAllowDrop(const FDragDropEvent& DragDropEvent, FSequencerDragDropParams& DragDropParams) override;`
- L47 _protected prototype_ `virtual FReply OnDrop(const FDragDropEvent& DragDropEvent, const FSequencerDragDropParams& DragDropParams) override;`
- L51 _private prototype_ `UGameplayCameraComponentBase* GetCameraComponentForBinding(const FGuid& ObjectBinding) const;`
- L53 _private prototype_ `void OnExtendObjectBindingTrackMenu(FMenuBuilder& MenuBuilder, TArray<FGuid> ObjectBindings);`
- L70 _private prototype_ `void BuildAddParameterTrackMenuItems(const FGuid& ObjectBinding, FMenuBuilder& MenuBuilder, TArray<FPropertyPath> KeyablePropertyPaths, int32 PropertyNameIndexStart);`
- L71 _private prototype_ `void BuildAddParameterTrackSubMenuItems(FMenuBuilder& MenuBuilder, FGuid ObjectBinding, TArray<FPropertyPath> KeyablePropertyPaths, int32 PropertyNameIndexStart);`
- L72 _private prototype_ `void BuildAddParameterTrackMenuItem(FMenuBuilder& MenuBuilder, const FPropertyMenuData& KeyablePropertyMenuData, const FGuid& ObjectBinding);`
- L74 _private prototype_ `void AddCameraParameterTrack(FPropertyMenuData PropertyMenuData, FGuid ObjectBinding);`
- L75 _private prototype_ `bool CanAddCameraParameterTrack(FPropertyMenuData PropertyMenuData, FGuid ObjectBinding) const;`

#### struct `FGameplayCameraComponentTrackEditor::FPropertyMenuData`  
`struct FPropertyMenuData`  
_L57-68_
- L59 _public member_ `FString MenuName;`
- L60 _public member_ `FPropertyPath PropertyPath;`
- L61 _public member_ `int32 PropertyIndexForMenuName = INDEX_NONE;`
- L63 _public function_ `bool operator< (const FPropertyMenuData& Other) const`

#### Free symbols / members of external scopes

- L18 _namespace_ `namespace UE`
- L18 _namespace_ `namespace Sequencer` (scope `UE`)

### `Plugins/Cameras/GameplayCameras/Source/GameplayCamerasEditor/Private/Styles/GameplayCamerasEditorStyle.h` (Private)


#### class `UE::Cameras::FGameplayCamerasEditorStyle`  
`class FGameplayCamerasEditorStyle final : public FSlateStyleSet`  
_L13-25_
- inherits: `FSlateStyleSet`
- desc: Implements the visual style of the gameplay cameras editors.
- L17 _public prototype_ `FGameplayCamerasEditorStyle();`
- L18 _public prototype_ `virtual ~FGameplayCamerasEditorStyle();`
- L20 _public prototype_ `static TSharedRef<FGameplayCamerasEditorStyle> Get();`
- L24 _private member_ `static TSharedPtr<FGameplayCamerasEditorStyle> Singleton;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace Cameras` (scope `UE`)

### `Plugins/Cameras/GameplayCameras/Source/GameplayCamerasEditor/Private/Styles/ObjectTreeGraphEditorStyle.h` (Private)


#### class `FObjectTreeGraphEditorStyle`  
`class FObjectTreeGraphEditorStyle final : public FSlateStyleSet`  
_L10-22_
- inherits: `FSlateStyleSet`
- desc: Implements the visual style of generic object tree graph editors
- L14 _public prototype_ `FObjectTreeGraphEditorStyle();`
- L15 _public prototype_ `virtual ~FObjectTreeGraphEditorStyle();`
- L17 _public prototype_ `static TSharedRef<FObjectTreeGraphEditorStyle> Get();`
- L21 _private member_ `static TSharedPtr<FObjectTreeGraphEditorStyle> Singleton;`

### `Plugins/Cameras/GameplayCameras/Source/GameplayCamerasEditor/Private/Trace/CameraSystemRewindDebuggerExtension.h` (Private)


#### class `UE::Cameras::FCameraSystemRewindDebuggerExtension`  
`class FCameraSystemRewindDebuggerExtension : public IRewindDebuggerExtension`  
_L27-53_
- inherits: `IRewindDebuggerExtension`
- desc: Rewind debugger extension for the camera system evaluation trace.
- L31 _public prototype_ `FCameraSystemRewindDebuggerExtension();`
- L32 _public prototype_ `virtual ~FCameraSystemRewindDebuggerExtension();`
- L35 _public prototype_ `virtual void Update(float DeltaTime, IRewindDebugger* RewindDebugger) override;` — IRewindDebuggerExtension interface.
- L36 _public prototype_ `virtual void Clear(IRewindDebugger* RewindDebugger) override;`
- L40 _private prototype_ `void EnsureDebugDrawDelegate(bool bIsRegistered);`
- L41 _private prototype_ `void DebugDraw(UCanvas* Canvas, APlayerController* PlayController);`
- L45 _private member_ `FDelegateHandle DebugDrawDelegateHandle;`
- L46 _private member_ `double LastTraceTime = 0.f;`
- L48 _private member_ `FLevelEditorModule* LevelEditorModule = nullptr;`
- L49 _private member_ `TWeakObjectPtr<UWorld> WeakVisualizedWorld;`
- L51 _private member_ `FCameraDebugBlockStorage DebugBlockStorage;`
- L52 _private member_ `FRootCameraDebugBlock* RootDebugBlock = nullptr;`

#### Free symbols / members of external scopes

- L19 _namespace_ `namespace UE`
- L19 _namespace_ `namespace Cameras` (scope `UE`)

### `Plugins/Cameras/GameplayCameras/Source/GameplayCamerasEditor/Private/Trace/CameraSystemRewindDebuggerTrack.h` (Private)


#### struct `UE::Cameras::FCameraSystemRewindDebuggerTrackTimelineData`  
`struct FCameraSystemRewindDebuggerTrackTimelineData`  
_L20-32_
- desc: Data for drawing the rewind debugger track that corresponds to the camera system evaluation trace.
- L31 _public member_ `TArray<DataWindow> Windows;`

#### struct `UE::Cameras::FCameraSystemRewindDebuggerTrackTimelineData::DataWindow`  
`struct DataWindow`  
_L24-29_
- L26 _public member_ `double TimeStart;`
- L27 _public member_ `double TimeEnd;`
- L28 _public member_ `FLinearColor Color;`

#### class `UE::Cameras::FCameraSystemRewindDebuggerTrack`  
`class FCameraSystemRewindDebuggerTrack : public RewindDebugger::FRewindDebuggerTrack`  
_L37-54_
- inherits: `RewindDebugger::FRewindDebuggerTrack`
- desc: Rewing debugger track for the camera system evaluation trace.
- L41 _public prototype_ `FCameraSystemRewindDebuggerTrack();`
- L45 _protected prototype_ `virtual FSlateIcon GetIconInternal() override;`
- L46 _protected prototype_ `virtual FText GetDisplayNameInternal() const override;`
- L47 _protected prototype_ `virtual FName GetNameInternal() const override;`
- L48 _protected prototype_ `virtual TSharedPtr<SWidget> GetTimelineViewInternal() override;`
- L52 _private member_ `FSlateIcon Icon;`
- L53 _private member_ `TSharedPtr<FCameraSystemRewindDebuggerTrackTimelineData> TimelineData;`

#### class `UE::Cameras::FCameraSystemRewindDebuggerTrackCreator`  
`class FCameraSystemRewindDebuggerTrackCreator : public RewindDebugger::IRewindDebuggerTrackCreator`  
_L60-72_
- inherits: `RewindDebugger::IRewindDebuggerTrackCreator`
- desc: Factory class that creates the rewind debugger track for the camera system evaluation trace.
- L64 _protected prototype_ `virtual FName GetTargetTypeNameInternal() const override;`
- L65 _protected prototype_ `virtual FName GetNameInternal() const override;`
- L66 _protected prototype_ `virtual void GetTrackTypesInternal(TArray<RewindDebugger::FRewindDebuggerTrackType>& Types) const override;`
- L68 _protected prototype_ `virtual TSharedPtr<RewindDebugger::FRewindDebuggerTrack> CreateTrackInternal(const RewindDebugger::FObjectId& InObjectId) const override;`
- L70 _protected prototype_ `virtual TSharedPtr<RewindDebugger::FRewindDebuggerTrack> CreateTrackInternal(uint64 InObjectId) const override;`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace Cameras` (scope `UE`)

### `Plugins/Cameras/GameplayCameras/Source/GameplayCamerasEditor/Private/Trace/CameraSystemTraceAnalyzer.h` (Private)


#### class `UE::Cameras::FCameraSystemTraceAnalyzer`  
`class FCameraSystemTraceAnalyzer : public UE::Trace::IAnalyzer`  
_L21-35_
- inherits: `UE::Trace::IAnalyzer`
- desc: Trace analyzer for the camera system evaluation.
- L25 _public prototype_ `FCameraSystemTraceAnalyzer(TraceServices::IAnalysisSession& InSession, FCameraSystemTraceProvider& InProvider);`
- L28 _public prototype_ `virtual void OnAnalysisBegin(const FOnAnalysisContext& Context) override;` — IAnalyzer interface
- L29 _public prototype_ `virtual bool OnEvent(uint16 RouteId, EStyle Style, const FOnEventContext& Context) override;`
- L33 _private member_ `TraceServices::IAnalysisSession& Session;`
- L34 _private member_ `FCameraSystemTraceProvider& Provider;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace TraceServices`
- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace Cameras` (scope `UE`)

### `Plugins/Cameras/GameplayCameras/Source/GameplayCamerasEditor/Private/Trace/CameraSystemTraceModule.h` (Private)


#### class `UE::Cameras::FCameraSystemTraceModule`  
`class FCameraSystemTraceModule : public TraceServices::IModule`  
_L17-31_
- inherits: `TraceServices::IModule`
- desc: Trace module for camera system evaluation.
- L22 _public prototype_ `virtual void GetModuleInfo(TraceServices::FModuleInfo& OutModuleInfo) override;` — TraceServices::IModule interface
- L23 _public prototype_ `virtual void OnAnalysisBegin(TraceServices::IAnalysisSession& Session) override;`
- L24 _public prototype_ `virtual void GetLoggers(TArray<const TCHAR *>& OutLoggers) override;`
- L25 _public prototype_ `virtual void GenerateReports(const TraceServices::IAnalysisSession& Session, const TCHAR* CmdLine, const TCHAR* OutputDirectory) override;`
- L26 _public function_ `virtual const TCHAR* GetCommandLineArgument() override`
- L30 _private member_ `static FName ModuleName;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace Cameras` (scope `UE`)

### `Plugins/Cameras/GameplayCameras/Source/GameplayCamerasEditor/Private/Trace/CameraSystemTraceProvider.h` (Private)


#### struct `UE::Cameras::FCameraSystemTraceFrameData`  
`struct FCameraSystemTraceFrameData`  
_L20-27_
- desc: Data for one frame of tracing.
- L22 _public member_ `int32 CameraSystemID;`
- L23 _public member_ `FVector3d EvaluatedLocation;`
- L24 _public member_ `FRotator3d EvaluatedRotation;`
- L25 _public member_ `float EvaluatedFieldOfView;`
- L26 _public member_ `TArray<uint8> SerializedBlocks;`

#### class `UE::Cameras::FCameraSystemTraceProvider`  
`class FCameraSystemTraceProvider : public TraceServices::IProvider`  
_L34-52_
- inherits: `TraceServices::IProvider`
- desc: Trace provider for the camera system evaluation.
- L38 _public member_ `static FName ProviderName;`
- L40 _public prototype_ `FCameraSystemTraceProvider(TraceServices::IAnalysisSession& InSession);`
- L42 _public prototype_ `void AppendFrameData(double InRecordingTime, FCameraSystemTraceFrameData&& InFrameData);`
- L44 _public function_ `const FCameraSystemTraceTimeline* GetTimeline() const`
- L48 _private member_ `TraceServices::IAnalysisSession& Session;`
- L50 _private typedef_ `using FFrameDataPointTimeline = TraceServices::TPointTimeline<FCameraSystemTraceFrameData>;`
- L51 _private member_ `TSharedPtr<FFrameDataPointTimeline> Timeline;`

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace TraceServices`
- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace Cameras` (scope `UE`)
- L29 _typedef_ `using FCameraSystemTraceTimeline = TraceServices::ITimeline<FCameraSystemTraceFrameData>;` (scope `UE::Cameras`)

### `Plugins/Cameras/GameplayCameras/Source/GameplayCamerasEditor/Private/Widgets/SCameraFamilyAssetShortcut.h` (Private)


#### class `UE::Cameras::SCameraFamilyAssetShortcut`  
`class SCameraFamilyAssetShortcut : public SCompoundWidget`  
_L20-74_
- inherits: `SCompoundWidget`
- L24 _public function_ `SLATE_BEGIN_ARGS(SCameraFamilyAssetShortcut)`
- L26 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TSharedRef<FBaseAssetToolkit>& InToolkit, const TSharedRef<IGameplayCamerasFamily>& InFamily, UClass* InAssetType);`
- L29 _public prototype_ `~SCameraFamilyAssetShortcut();`
- L33 _protected prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;`
- L37 _public prototype_ `const FSlateBrush* GetAssetIcon() const;`
- L38 _public prototype_ `FSlateColor GetAssetTint() const;`
- L39 _public prototype_ `ECheckBoxState GetCheckState() const;`
- L40 _public prototype_ `FText GetButtonTooltip() const;`
- L41 _public prototype_ `void HandleButtonClick(ECheckBoxState InState);`
- L43 _public prototype_ `EVisibility GetSoloButtonVisibility() const;`
- L44 _public prototype_ `bool IsSoloButtonEnabled() const;`
- L46 _public prototype_ `EVisibility GetComboButtonVisibility() const;`
- L47 _public prototype_ `EVisibility GetComboDropdownVisibility() const;`
- L48 _public prototype_ `TSharedRef<SWidget> HandleGetDropdownMenuContent();`
- L49 _public prototype_ `void HandleOpenSecondaryAsset(const FAssetData& InAssetData);`
- L51 _public prototype_ `bool DoesFamilySupport(const FAssetData& InAssetData);`
- L53 _public prototype_ `void HandleFilesLoaded();`
- L54 _public prototype_ `void HandleAssetRemoved(const FAssetData& InAssetData);`
- L55 _public prototype_ `void HandleAssetRenamed(const FAssetData& InAssetData, const FString& InOldObjectPath);`
- L56 _public prototype_ `void HandleAssetAdded(const FAssetData& InAssetData);`
- L58 _public prototype_ `void HandleCameraAssetBuilt(const UCameraAsset* InCameraAsset);`
- L59 _public prototype_ `void HandleCameraRigAssetBuilt(const UCameraRigAsset* InCameraAsset);`
- L63 _private member_ `TWeakPtr<FBaseAssetToolkit> WeakToolkit;`
- L65 _private member_ `TSharedPtr<IGameplayCamerasFamily> Family;`
- L66 _private member_ `UClass* FamilyAssetType;`
- L68 _private member_ `TSharedPtr<SCheckBox> SoloCheckBox;`
- L69 _private member_ `TSharedPtr<SCheckBox> ComboCheckBox;`
- L70 _private member_ `TSharedPtr<SComboButton> ComboDropdown;`
- L72 _private member_ `TArray<FAssetData> AssetDatas;`
- L73 _private member_ `bool bRefreshAssetDatas = false;`

#### Free symbols / members of external scopes

- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace Cameras` (scope `UE`)

### `Plugins/Cameras/GameplayCameras/Source/GameplayCamerasEditor/Public/AssetTools/CameraAssetEditor.h` (Public)


#### class `UCameraAssetEditor`  
`class UCameraAssetEditor : public UAssetEditor`  
_L16-36_
- reflection: `UCLASS(Transient)`
- inherits: `UAssetEditor`
- desc: Editor for a camera asset.
- L22 _public prototype_ `void Initialize(TObjectPtr<UCameraAsset> InCameraAsset);`
- L24 _public function_ `UCameraAsset* GetCameraAsset() const`
- L29 _public prototype_ `virtual void GetObjectsToEdit(TArray<UObject*>& InObjectsToEdit) override;` — UAssetEditor interface
- L30 _public prototype_ `virtual TSharedPtr<FBaseAssetToolkit> CreateToolkit() override;`
- L35 _private member_ `TObjectPtr<UCameraAsset> CameraAsset;` — `UPROPERTY()`

### `Plugins/Cameras/GameplayCameras/Source/GameplayCamerasEditor/Public/AssetTools/CameraRigAssetEditor.h` (Public)


#### class `UCameraRigAssetEditor`  
`class UCameraRigAssetEditor : public UAssetEditor`  
_L16-36_
- reflection: `UCLASS(Transient)`
- inherits: `UAssetEditor`
- desc: Editor for a camera rig asset.
- L22 _public prototype_ `void Initialize(TObjectPtr<UCameraRigAsset> InCameraRigAsset);`
- L24 _public function_ `UCameraRigAsset* GetCameraRigAsset() const`
- L29 _public prototype_ `virtual void GetObjectsToEdit(TArray<UObject*>& InObjectsToEdit) override;` — UAssetEditor interface
- L30 _public prototype_ `virtual TSharedPtr<FBaseAssetToolkit> CreateToolkit() override;`
- L35 _private member_ `TObjectPtr<UCameraRigAsset> CameraRigAsset;` — `UPROPERTY()`

### `Plugins/Cameras/GameplayCameras/Source/GameplayCamerasEditor/Public/AssetTools/CameraRigProxyAssetEditor.h` (Public)


#### class `UCameraRigProxyAssetEditor`  
`class UCameraRigProxyAssetEditor : public UAssetEditor`  
_L16-36_
- reflection: `UCLASS(Transient)`
- inherits: `UAssetEditor`
- desc: Editor for a camera rig proxy asset.
- L22 _public prototype_ `void Initialize(TObjectPtr<UCameraRigProxyAsset> InCameraRigProxyAsset);`
- L24 _public function_ `UCameraRigProxyAsset* GetCameraRigProxyAsset() const`
- L29 _public prototype_ `virtual void GetObjectsToEdit(TArray<UObject*>& InObjectsToEdit) override;` — UAssetEditor interface
- L30 _public prototype_ `virtual TSharedPtr<FBaseAssetToolkit> CreateToolkit() override;`
- L35 _private member_ `TObjectPtr<UCameraRigProxyAsset> CameraRigProxyAsset;` — `UPROPERTY()`

### `Plugins/Cameras/GameplayCameras/Source/GameplayCamerasEditor/Public/AssetTools/CameraRigTransitionEditor.h` (Public)


#### class `UCameraRigTransitionEditor`  
`class UCameraRigTransitionEditor : public UAssetEditor`  
_L15-35_
- reflection: `UCLASS(Transient)`
- inherits: `UAssetEditor`
- desc: Editor for camera transitions.
- L21 _public prototype_ `void Initialize(TObjectPtr<UObject> InTransitionOwner);`
- L23 _public function_ `UObject* GetTransitionOwner() const`
- L28 _public prototype_ `virtual void GetObjectsToEdit(TArray<UObject*>& InObjectsToEdit) override;` — UAssetEditor interface
- L29 _public prototype_ `virtual TSharedPtr<FBaseAssetToolkit> CreateToolkit() override;`
- L34 _private member_ `TObjectPtr<UObject> TransitionOwner;` — `UPROPERTY()`

### `Plugins/Cameras/GameplayCameras/Source/GameplayCamerasEditor/Public/AssetTools/CameraShakeAssetEditor.h` (Public)


#### class `UCameraShakeAssetEditor`  
`class UCameraShakeAssetEditor : public UAssetEditor`  
_L16-36_
- reflection: `UCLASS(Transient)`
- inherits: `UAssetEditor`
- desc: Editor for a camera rig asset.
- L22 _public prototype_ `void Initialize(TObjectPtr<UCameraShakeAsset> InCameraShakeAsset);`
- L24 _public function_ `UCameraShakeAsset* GetCameraShakeAsset() const`
- L29 _public prototype_ `virtual void GetObjectsToEdit(TArray<UObject*>& InObjectsToEdit) override;` — UAssetEditor interface
- L30 _public prototype_ `virtual TSharedPtr<FBaseAssetToolkit> CreateToolkit() override;`
- L35 _private member_ `TObjectPtr<UCameraShakeAsset> CameraShakeAsset;` — `UPROPERTY()`

### `Plugins/Cameras/GameplayCameras/Source/GameplayCamerasEditor/Public/AssetTools/CameraVariableCollectionEditor.h` (Public)


#### class `UCameraVariableCollectionEditor`  
`class UCameraVariableCollectionEditor : public UAssetEditor`  
_L16-35_
- reflection: `UCLASS(Transient)`
- inherits: `UAssetEditor`
- desc: Editor for a camera variable collection.
- L22 _public prototype_ `void Initialize(TObjectPtr<UCameraVariableCollection> InVariableCollection);`
- L24 _public function_ `UCameraVariableCollection* GetVariableCollection() const`
- L29 _public prototype_ `virtual void GetObjectsToEdit(TArray<UObject*>& InObjectsToEdit) override;` — UAssetEditor interface
- L30 _public prototype_ `virtual TSharedPtr<FBaseAssetToolkit> CreateToolkit() override;`
- L34 _private member_ `TObjectPtr<UCameraVariableCollection> VariableCollection;`

### `Plugins/Cameras/GameplayCameras/Source/GameplayCamerasEditor/Public/Commands/CameraAssetEditorCommands.h` (Public)


#### class `UE::Cameras::FCameraAssetEditorCommands`  
`class FCameraAssetEditorCommands : public TCommands<FCameraAssetEditorCommands>`  
_L15-38_
- inherits: `TCommands<FCameraAssetEditorCommands>`
- L19 _public prototype_ `FCameraAssetEditorCommands();`
- L21 _public prototype_ `virtual void RegisterCommands() override;`
- L25 _public member_ `TSharedPtr<FUICommandInfo> Build;`
- L27 _public member_ `TSharedPtr<FUICommandInfo> ShowCameraDirector;`
- L28 _public member_ `TSharedPtr<FUICommandInfo> ShowCameraRigs;`
- L29 _public member_ `TSharedPtr<FUICommandInfo> ShowSharedTransitions;`
- L31 _public member_ `TSharedPtr<FUICommandInfo> ChangeCameraDirector;`
- L33 _public member_ `TSharedPtr<FUICommandInfo> ShowMessages;`
- L34 _public member_ `TSharedPtr<FUICommandInfo> FindInCamera;`
- L36 _public member_ `TSharedPtr<FUICommandInfo> RenameInterfaceParameter;`
- L37 _public member_ `TSharedPtr<FUICommandInfo> DeleteInterfaceParameter;`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace Cameras` (scope `UE`)

### `Plugins/Cameras/GameplayCameras/Source/GameplayCamerasEditor/Public/Commands/CameraRigAssetEditorCommands.h` (Public)


#### class `UE::Cameras::FCameraRigAssetEditorCommands`  
`class FCameraRigAssetEditorCommands : public TCommands<FCameraRigAssetEditorCommands>`  
_L15-36_
- inherits: `TCommands<FCameraRigAssetEditorCommands>`
- L19 _public prototype_ `FCameraRigAssetEditorCommands();`
- L21 _public prototype_ `virtual void RegisterCommands() override;`
- L25 _public member_ `TSharedPtr<FUICommandInfo> Build;`
- L27 _public member_ `TSharedPtr<FUICommandInfo> ShowNodeHierarchy;`
- L28 _public member_ `TSharedPtr<FUICommandInfo> ShowTransitions;`
- L30 _public member_ `TSharedPtr<FUICommandInfo> ShowMessages;`
- L31 _public member_ `TSharedPtr<FUICommandInfo> FindInCameraRig;`
- L32 _public member_ `TSharedPtr<FUICommandInfo> FocusHome;`
- L34 _public member_ `TSharedPtr<FUICommandInfo> RenameInterfaceParameter;`
- L35 _public member_ `TSharedPtr<FUICommandInfo> DeleteInterfaceParameter;`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace Cameras` (scope `UE`)

### `Plugins/Cameras/GameplayCameras/Source/GameplayCamerasEditor/Public/Commands/CameraRigTransitionEditorCommands.h` (Public)


#### class `UE::Cameras::FCameraRigTransitionEditorCommands`  
`class FCameraRigTransitionEditorCommands : public TCommands<FCameraRigTransitionEditorCommands>`  
_L15-27_
- inherits: `TCommands<FCameraRigTransitionEditorCommands>`
- L19 _public prototype_ `FCameraRigTransitionEditorCommands();`
- L21 _public prototype_ `virtual void RegisterCommands() override;`
- L25 _public member_ `TSharedPtr<FUICommandInfo> FindInTransitions;`
- L26 _public member_ `TSharedPtr<FUICommandInfo> FocusHome;`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace Cameras` (scope `UE`)

### `Plugins/Cameras/GameplayCameras/Source/GameplayCamerasEditor/Public/Commands/CameraShakeAssetEditorCommands.h` (Public)


#### class `UE::Cameras::FCameraShakeAssetEditorCommands`  
`class FCameraShakeAssetEditorCommands : public TCommands<FCameraShakeAssetEditorCommands>`  
_L15-33_
- inherits: `TCommands<FCameraShakeAssetEditorCommands>`
- L19 _public prototype_ `FCameraShakeAssetEditorCommands();`
- L21 _public prototype_ `virtual void RegisterCommands() override;`
- L25 _public member_ `TSharedPtr<FUICommandInfo> Build;`
- L27 _public member_ `TSharedPtr<FUICommandInfo> ShowMessages;`
- L28 _public member_ `TSharedPtr<FUICommandInfo> FindInCameraShake;`
- L29 _public member_ `TSharedPtr<FUICommandInfo> FocusHome;`
- L31 _public member_ `TSharedPtr<FUICommandInfo> RenameInterfaceParameter;`
- L32 _public member_ `TSharedPtr<FUICommandInfo> DeleteInterfaceParameter;`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace Cameras` (scope `UE`)

### `Plugins/Cameras/GameplayCameras/Source/GameplayCamerasEditor/Public/Commands/CameraVariableCollectionEditorCommands.h` (Public)


#### class `UE::Cameras::FCameraVariableCollectionEditorCommands`  
`class FCameraVariableCollectionEditorCommands : public TCommands<FCameraVariableCollectionEditorCommands>`  
_L15-28_
- inherits: `TCommands<FCameraVariableCollectionEditorCommands>`
- L19 _public prototype_ `FCameraVariableCollectionEditorCommands();`
- L21 _public prototype_ `virtual void RegisterCommands() override;`
- L25 _public member_ `TSharedPtr<FUICommandInfo> CreateVariable;`
- L26 _public member_ `TSharedPtr<FUICommandInfo> RenameVariable;`
- L27 _public member_ `TSharedPtr<FUICommandInfo> DeleteVariable;`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace Cameras` (scope `UE`)

### `Plugins/Cameras/GameplayCameras/Source/GameplayCamerasEditor/Public/Commands/GameplayCamerasDebuggerCommands.h` (Public)


#### class `UE::Cameras::FGameplayCamerasDebuggerCommands`  
`class FGameplayCamerasDebuggerCommands : public TCommands<FGameplayCamerasDebuggerCommands>`  
_L15-26_
- inherits: `TCommands<FGameplayCamerasDebuggerCommands>`
- L19 _public prototype_ `FGameplayCamerasDebuggerCommands();`
- L21 _public prototype_ `virtual void RegisterCommands() override;`
- L25 _public member_ `TSharedPtr<FUICommandInfo> EnableDebugInfo;`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace Cameras` (scope `UE`)

### `Plugins/Cameras/GameplayCameras/Source/GameplayCamerasEditor/Public/Commands/ObjectTreeGraphEditorCommands.h` (Public)


#### class `UE::Cameras::FObjectTreeGraphEditorCommands`  
`class FObjectTreeGraphEditorCommands : public TCommands<FObjectTreeGraphEditorCommands>`  
_L15-28_
- inherits: `TCommands<FObjectTreeGraphEditorCommands>`
- L19 _public prototype_ `FObjectTreeGraphEditorCommands();`
- L21 _public prototype_ `virtual void RegisterCommands() override;`
- L25 _public member_ `TSharedPtr<FUICommandInfo> InsertArrayItemPinBefore;`
- L26 _public member_ `TSharedPtr<FUICommandInfo> InsertArrayItemPinAfter;`
- L27 _public member_ `TSharedPtr<FUICommandInfo> RemoveArrayItemPin;`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace Cameras` (scope `UE`)

### `Plugins/Cameras/GameplayCameras/Source/GameplayCamerasEditor/Public/Customizations/CameraAssetReferenceDetailsCustomization.h` (Public)


#### class `UE::Cameras::FCameraAssetReferenceDetailsCustomization`  
`class FCameraAssetReferenceDetailsCustomization : public IPropertyTypeCustomization`  
_L14-39_
- inherits: `IPropertyTypeCustomization`
- L18 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance();`
- L22 _public prototype_ `~FCameraAssetReferenceDetailsCustomization();`
- L25 _public prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> InStructPropertyHandle, FDetailWidgetRow& InHeaderRow, IPropertyTypeCustomizationUtils& InCustomizationUtils) override;` — IPropertyTypeCustomization interface.
- L26 _public prototype_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> InStructPropertyHandle, IDetailChildrenBuilder& InChildrenBuilder, IPropertyTypeCustomizationUtils& InCustomizationUtils) override;`
- L30 _private prototype_ `void OnCameraAssetBuilt(const UCameraAsset* InCameraAsset);`
- L31 _private prototype_ `void RebuildParametersIfNeeded();`
- L35 _private member_ `TSharedPtr<IPropertyHandle> StructPropertyHandle;`
- L36 _private member_ `TSharedPtr<IPropertyHandle> CameraAssetPropertyHandle;`
- L37 _private member_ `TSharedPtr<IPropertyHandle> ParametersPropertyHandle;`
- L38 _private member_ `TSharedPtr<IPropertyUtilities> PropertyUtilities;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace Cameras` (scope `UE`)

### `Plugins/Cameras/GameplayCameras/Source/GameplayCamerasEditor/Public/Customizations/CameraFramingZoneDetailsCustomization.h` (Public)
_(no declarations extracted)_

### `Plugins/Cameras/GameplayCameras/Source/GameplayCamerasEditor/Public/Customizations/CameraObjectInterfaceParameterDetailsCustomization.h` (Public)


#### class `UE::Cameras::FCameraObjectInterfaceParameterDetailsCustomization`  
`class FCameraObjectInterfaceParameterDetailsCustomization : public IDetailCustomization`  
_L18-28_
- inherits: `IDetailCustomization`
- desc: Details customization for a camera object parameter.
- L22 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();`
- L27 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;` — IDetailCustomization interface.

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace Cameras` (scope `UE`)

### `Plugins/Cameras/GameplayCameras/Source/GameplayCamerasEditor/Public/Customizations/CameraObjectInterfaceParameterOverrideDataDetails.h` (Public)


#### class `UE::Cameras::TCameraObjectInterfaceParameterOverrideDataDetails`  
`template<typename AssetReferenceStruct> class TCameraObjectInterfaceParameterOverrideDataDetails : public FPropertyBagInstanceDataDetails`  
_L18-94_
- inherits: `FPropertyBagInstanceDataDetails`
- desc: Helper class for detail customizations that want to show the camera object interface's parameters in the UI as a property bag of overridable properties.
- L22 _public function_ `TCameraObjectInterfaceParameterOverrideDataDetails( TSharedPtr<IPropertyHandle> InStructPropertyHandle, TSharedPtr<IPropertyHandle> InParametersPropertyHandle, TSharedPtr<IPropertyUtilities>& InPropertyUtilities) : FPropertyBagInstanceDataDetails(InParametersPropertyHandle, InPropertyUtilities, true) , StructPropertyHandle(InStructPropertyHandle)`
- L54 _protected function_ `virtual bool HasPropertyOverrides() const override`
- L59 _protected function_ `virtual void PreChangeOverrides() override`
- L64 _protected function_ `virtual void PostChangeOverrides() override`
- L70 _protected function_ `virtual void EnumeratePropertyBags(TSharedPtr<IPropertyHandle> PropertyBagHandle, const EnumeratePropertyBagFuncRef& Func) const override`
- L93 _private member_ `TSharedPtr<IPropertyHandle> StructPropertyHandle;`

#### struct `UE::Cameras::TCameraObjectInterfaceParameterOverrideDataDetails::FOverrideProvider`  
`struct FOverrideProvider : public IPropertyBagOverrideProvider`  
_L33-52_
- inherits: `IPropertyBagOverrideProvider`
- L35 _public function_ `FOverrideProvider(AssetReferenceStruct& InAssetReference) : AssetReference(InAssetReference)`
- L40 _public function_ `virtual bool IsPropertyOverridden(const FGuid PropertyID) const override`
- L45 _public function_ `virtual void SetPropertyOverride(const FGuid PropertyID, const bool bIsOverridden) const override`
- L51 _private member_ `AssetReferenceStruct& AssetReference;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace Cameras` (scope `UE`)
- L73 _function_ `` (scope `UE::Cameras::TCameraObjectInterfaceParameterOverrideDataDetails::EnumeratePropertyBags`)

### `Plugins/Cameras/GameplayCameras/Source/GameplayCamerasEditor/Public/Customizations/CameraParameterDetailsCustomizations.h` (Public)


#### class `UE::Cameras::FCameraParameterDetailsCustomization`  
`class FCameraParameterDetailsCustomization : public IPropertyTypeCustomization , public FTickableEditorObject`  
_L24-114_
- inherits: `IPropertyTypeCustomization,FTickableEditorObject`
- desc: Base details customization for camera parameters.
- L31 _public prototype_ `static void Register(FPropertyEditorModule& PropertyEditorModule);` — Registers details customizations for all camera parameter types.
- L33 _public prototype_ `static void Unregister(FPropertyEditorModule& PropertyEditorModule);` — Unregisters details customizations for all camera parameter types.
- L38 _public prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> PropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& CustomizationUtils) override;` — IPropertyTypeCustomization interface.
- L39 _public prototype_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> PropertyHandle, IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& CustomizationUtils) override;`
- L42 _public prototype_ `virtual void Tick(float DeltaTime) override;` — FTickableEditorObject interface.
- L43 _public function_ `virtual ETickableTickType GetTickableTickType() const override`
- L44 _public function_ `virtual TStatId GetStatId() const override`
- L48 _protected prototype_ `virtual bool HasOverride(void* InRawData) = 0;`
- L49 _protected prototype_ `virtual bool HasNonUserOverride(void* InRawData) = 0;`
- L50 _protected prototype_ `virtual void SetParameterVariable(void* InRawData, UCameraVariableAsset* InVariable) = 0;`
- L73 _private prototype_ `void UpdateVariableInfo();`
- L75 _private prototype_ `TSharedRef<SWidget> BuildCameraVariableBrowser();`
- L77 _private prototype_ `bool IsValueEditorEnabled() const;`
- L78 _private prototype_ `bool IsCameraVariableBrowserEnabled() const;`
- L79 _private prototype_ `FText GetCameraVariableBrowserToolTip() const;`
- L81 _private prototype_ `FText GetVariableInfoText() const;`
- L82 _private prototype_ `EVisibility GetVariableInfoTextVisibility() const;`
- L83 _private prototype_ `FOptionalSize GetVariableInfoTextMaxWidth() const;`
- L85 _private prototype_ `FText GetVariableErrorText() const;`
- L86 _private prototype_ `EVisibility GetVariableErrorTextVisibility() const;`
- L87 _private prototype_ `FOptionalSize GetVariableErrorTextMaxWidth() const;`
- L89 _private prototype_ `bool CanGoToVariable() const;`
- L90 _private prototype_ `void OnGoToVariable();`
- L92 _private prototype_ `bool CanClearVariable() const;`
- L93 _private prototype_ `void OnClearVariable();`
- L95 _private prototype_ `void OnSetVariable(UCameraVariableAsset* InVariable);`
- L97 _private prototype_ `bool IsResetToDefaultVisible(TSharedPtr<IPropertyHandle> InPropertyHandle) const;`
- L98 _private prototype_ `void OnResetToDefault(TSharedPtr<IPropertyHandle> InPropertyHandle);`
- L102 _protected member_ `UClass* VariableClass = nullptr;`
- L104 _protected member_ `FCameraVariableInfo VariableInfo;`
- L106 _protected member_ `TSharedPtr<IPropertyUtilities> PropertyUtilities;`
- L108 _protected member_ `TSharedPtr<IPropertyHandle> StructProperty;`
- L109 _protected member_ `TSharedPtr<IPropertyHandle> ValueProperty;`
- L110 _protected member_ `TSharedPtr<IPropertyHandle> VariableProperty;`
- L112 _protected member_ `TSharedPtr<SHorizontalBox> LayoutBox;`
- L113 _protected member_ `TSharedPtr<SComboButton> VariableBrowserButton;`

#### enum `UE::Cameras::FCameraParameterDetailsCustomization::ECameraVariableValue`  
`enum class ECameraVariableValue`  
_L54-60_
- L56 _public enumerator_ `NotSet`
- L57 _public enumerator_ `Set`
- L58 _public enumerator_ `MultipleSet`
- L59 _public enumerator_ `Invalid`

#### struct `UE::Cameras::FCameraParameterDetailsCustomization::FCameraVariableInfo`  
`struct FCameraVariableInfo`  
_L62-71_
- L64 _public member_ `UCameraVariableAsset* CommonVariable = nullptr;`
- L65 _public member_ `ECameraVariableValue VariableValue = ECameraVariableValue::NotSet;`
- L66 _public member_ `bool bHasNonUserOverride = false;`
- L67 _public member_ `bool bHasOverride = false;`
- L69 _public member_ `FText InfoText;`
- L70 _public member_ `FText ErrorText;`

#### Free symbols / members of external scopes

- L18 _namespace_ `namespace UE`
- L18 _namespace_ `namespace Cameras` (scope `UE`)
- L117 _macro_ `#define UE_CAMERA_VARIABLE_FOR_TYPE(ValueType, ValueName)\` — Create all the individual classes.

### `Plugins/Cameras/GameplayCameras/Source/GameplayCamerasEditor/Public/Customizations/CameraRigAssetReferenceDetailsCustomization.h` (Public)


#### class `UE::Cameras::FCameraRigAssetReferenceDetailsCustomization`  
`class FCameraRigAssetReferenceDetailsCustomization : public IPropertyTypeCustomization`  
_L14-39_
- inherits: `IPropertyTypeCustomization`
- L18 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance();`
- L22 _public prototype_ `~FCameraRigAssetReferenceDetailsCustomization();`
- L25 _public prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> InStructPropertyHandle, FDetailWidgetRow& InHeaderRow, IPropertyTypeCustomizationUtils& InCustomizationUtils) override;` — IPropertyTypeCustomization interface.
- L26 _public prototype_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> InStructPropertyHandle, IDetailChildrenBuilder& InChildrenBuilder, IPropertyTypeCustomizationUtils& InCustomizationUtils) override;`
- L30 _private prototype_ `void OnCameraRigAssetBuilt(const UCameraRigAsset* CameraRig);`
- L31 _private prototype_ `void RebuildParametersIfNeeded();`
- L35 _private member_ `TSharedPtr<IPropertyHandle> StructPropertyHandle;`
- L36 _private member_ `TSharedPtr<IPropertyHandle> CameraRigAssetPropertyHandle;`
- L37 _private member_ `TSharedPtr<IPropertyHandle> ParametersPropertyHandle;`
- L38 _private member_ `TSharedPtr<IPropertyUtilities> PropertyUtilities;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace Cameras` (scope `UE`)

### `Plugins/Cameras/GameplayCameras/Source/GameplayCamerasEditor/Public/Customizations/CameraShakeAssetReferenceDetailsCustomization.h` (Public)


#### class `UE::Cameras::FCameraShakeAssetReferenceDetailsCustomization`  
`class FCameraShakeAssetReferenceDetailsCustomization : public IPropertyTypeCustomization`  
_L14-39_
- inherits: `IPropertyTypeCustomization`
- L18 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance();`
- L22 _public prototype_ `~FCameraShakeAssetReferenceDetailsCustomization();`
- L25 _public prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> InStructPropertyHandle, FDetailWidgetRow& InHeaderRow, IPropertyTypeCustomizationUtils& InCustomizationUtils) override;` — IPropertyTypeCustomization interface.
- L26 _public prototype_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> InStructPropertyHandle, IDetailChildrenBuilder& InChildrenBuilder, IPropertyTypeCustomizationUtils& InCustomizationUtils) override;`
- L30 _private prototype_ `void OnCameraShakeAssetBuilt(const UCameraShakeAsset* CameraShake);`
- L31 _private prototype_ `void RebuildParametersIfNeeded();`
- L35 _private member_ `TSharedPtr<IPropertyHandle> StructPropertyHandle;`
- L36 _private member_ `TSharedPtr<IPropertyHandle> CameraShakeAssetPropertyHandle;`
- L37 _private member_ `TSharedPtr<IPropertyHandle> ParametersPropertyHandle;`
- L38 _private member_ `TSharedPtr<IPropertyUtilities> PropertyUtilities;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace Cameras` (scope `UE`)

### `Plugins/Cameras/GameplayCameras/Source/GameplayCamerasEditor/Public/Customizations/CameraVariableReferenceDetailsCustomizations.h` (Public)


#### class `UE::Cameras::FCameraVariableReferenceDetailsCustomization`  
`class FCameraVariableReferenceDetailsCustomization : public IPropertyTypeCustomization`  
_L19-63_
- inherits: `IPropertyTypeCustomization`
- desc: Base details customization for camera variable references.
- L24 _public prototype_ `static void Register(FPropertyEditorModule& PropertyEditorModule);` — Registers details customizations for all camera variable reference types.
- L26 _public prototype_ `static void Unregister(FPropertyEditorModule& PropertyEditorModule);` — Unregisters details customizations for all camera variable reference types.
- L31 _public prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> PropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& CustomizationUtils) override;` — IPropertyTypeCustomization interface
- L32 _public prototype_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> PropertyHandle, IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& CustomizationUtils) override;`
- L36 _protected prototype_ `virtual bool HasNonUserOverride(void* InRawData) const = 0;`
- L37 _protected prototype_ `virtual void SetReferenceVariable(void* InRawData, UCameraVariableAsset* InVariable) = 0;`
- L41 _private prototype_ `TSharedRef<SWidget> BuildCameraVariableBrowser();`
- L43 _private prototype_ `bool IsCameraVariableBrowserEnabled() const;`
- L45 _private prototype_ `FText GetVariableName() const;`
- L47 _private prototype_ `bool CanClearVariable() const;`
- L48 _private prototype_ `void OnClearVariable();`
- L50 _private prototype_ `void OnSetVariable(UCameraVariableAsset* InVariable);`
- L51 _private prototype_ `void OnResetToDefault();`
- L55 _protected member_ `UClass* VariableClass = nullptr;`
- L57 _protected member_ `TSharedPtr<IPropertyUtilities> PropertyUtilities;`
- L59 _protected member_ `TSharedPtr<IPropertyHandle> StructProperty;`
- L60 _protected member_ `TSharedPtr<IPropertyHandle> VariableProperty;`
- L62 _protected member_ `TSharedPtr<SComboButton> VariableBrowserButton;`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace Cameras` (scope `UE`)
- L66 _macro_ `#define UE_CAMERA_VARIABLE_FOR_TYPE(ValueType, ValueName)\` — Create all the individual classes.

### `Plugins/Cameras/GameplayCameras/Source/GameplayCamerasEditor/Public/Customizations/FilmbackCameraNodeDetailsCustomization.h` (Public)


#### class `UE::Cameras::FFilmbackCameraNodeDetailsCustomization`  
`class FFilmbackCameraNodeDetailsCustomization : public IDetailCustomization`  
_L19-47_
- inherits: `IDetailCustomization`
- desc: Details customization for the filmback camera node.
- L23 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();`
- L28 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;` — IDetailCustomization interface
- L32 _private prototype_ `void BuildPresetComboList();`
- L34 _private prototype_ `bool IsPresetEnabled() const;`
- L35 _private prototype_ `TSharedRef<SWidget> MakePresetComboWidget(TSharedPtr<FText> InItem);`
- L36 _private prototype_ `void OnPresetChanged(TSharedPtr<FText> NewSelection, ESelectInfo::Type SelectInfo);`
- L38 _private prototype_ `FText GetPresetComboBoxContent() const;`
- L42 _private member_ `TSharedPtr<IPropertyHandle> SensorWidthProperty;`
- L43 _private member_ `TSharedPtr<IPropertyHandle> SensorHeightProperty;`
- L45 _private member_ `TSharedPtr<SComboBox<TSharedPtr<FText>>> PresetComboBox;`
- L46 _private member_ `TArray<TSharedPtr<FText>> PresetComboList;`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace Cameras` (scope `UE`)

### `Plugins/Cameras/GameplayCameras/Source/GameplayCamerasEditor/Public/Customizations/RichCurveDetailsCustomizations.h` (Public)


#### class `UE::Cameras::FRichCurveDetailsCustomization`  
`class FRichCurveDetailsCustomization : public IPropertyTypeCustomization`  
_L22-67_
- inherits: `IPropertyTypeCustomization`
- L26 _public prototype_ `static void Register(FPropertyEditorModule& PropertyEditorModule);`
- L27 _public prototype_ `static void Unregister(FPropertyEditorModule& PropertyEditorModule);`
- L29 _public function_ `static FOnInvokeCurveEditor& OnInvokeCurveEditor()`
- L33 _private member_ `static FOnInvokeCurveEditor OnInvokeCurveEditorDelegate;`
- L37 _public prototype_ `~FRichCurveDetailsCustomization();`
- L40 _public prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> PropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& CustomizationUtils) override;` — IPropertyTypeCustomization interface
- L41 _public prototype_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> PropertyHandle, IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& CustomizationUtils) override;`
- L45 _protected prototype_ `virtual void AddCurves( TSharedRef<IPropertyHandle> PropertyHandle, TSharedRef<SRichCurveViewport> InRichCurveViewport, const FText& PropertyDisplayName, UObject* OuterObject, void* RawData) = 0;`
- L54 _private prototype_ `void OnPropertyValueChanged();`
- L55 _private prototype_ `void OnObjectPropertyChanged(UObject* Object, FPropertyChangedEvent& PropertyChangedEvent);`
- L57 _private prototype_ `FReply OnFocusInCurvesTab();`
- L59 _private prototype_ `TSharedRef<FCurveEditor> CreateCurveEditor();`
- L60 _private prototype_ `TSharedRef<SWidget> CreateCurveEditorPanel(TSharedRef<FCurveEditor> CurveEditor);`
- L64 _private member_ `TSharedPtr<IPropertyHandle> PrivatePropertyHandle;`
- L65 _private member_ `TSharedPtr<SHorizontalBox> HeaderLayout;`
- L66 _private member_ `TSharedPtr<SRichCurveViewport> RichCurveViewport;`

#### class `UE::Cameras::FRichSingleCurveDetailsCustomization`  
`class FRichSingleCurveDetailsCustomization : public FRichCurveDetailsCustomization`  
_L69-78_
- inherits: `FRichCurveDetailsCustomization`
- L72 _protected prototype_ `virtual void AddCurves( TSharedRef<IPropertyHandle> PropertyHandle, TSharedRef<SRichCurveViewport> InRichCurveViewport, const FText& PropertyDisplayName, UObject* OuterObject, void* RawData) override;`

#### class `UE::Cameras::FRichRotatorCurveDetailsCustomization`  
`class FRichRotatorCurveDetailsCustomization : public FRichCurveDetailsCustomization`  
_L80-89_
- inherits: `FRichCurveDetailsCustomization`
- L83 _protected prototype_ `virtual void AddCurves( TSharedRef<IPropertyHandle> PropertyHandle, TSharedRef<SRichCurveViewport> InRichCurveViewport, const FText& PropertyDisplayName, UObject* OuterObject, void* RawData) override;`

#### class `UE::Cameras::FRichVectorCurveDetailsCustomization`  
`class FRichVectorCurveDetailsCustomization : public FRichCurveDetailsCustomization`  
_L91-100_
- inherits: `FRichCurveDetailsCustomization`
- L94 _protected prototype_ `virtual void AddCurves( TSharedRef<IPropertyHandle> PropertyHandle, TSharedRef<SRichCurveViewport> InRichCurveViewport, const FText& PropertyDisplayName, UObject* OuterObject, void* RawData) override;`

#### Free symbols / members of external scopes

- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace Cameras` (scope `UE`)
- L20 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnInvokeCurveEditor, UObject*, FName);`
- L20 _prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnInvokeCurveEditor, UObject*, FName);` (scope `UE::Cameras`)

### `Plugins/Cameras/GameplayCameras/Source/GameplayCamerasEditor/Public/Editors/CameraNodeGraphDragDropOp.h` (Public)


#### class `FCameraNodeGraphInterfaceParameterDragDropOp`  
`class FCameraNodeGraphInterfaceParameterDragDropOp : public FDecoratedDragDropOp`  
_L11-25_
- inherits: `FDecoratedDragDropOp`
- L15 _public prototype_ `DRAG_DROP_OPERATOR_TYPE(FCameraNodeGraphInterfaceParameterDragDropOp, FDecoratedDragDropOp) static TSharedRef<FCameraNodeGraphInterfaceParameterDragDropOp> New(UCameraObjectInterfaceParameterBase* InInterfaceParameter);`
- L19 _public prototype_ `FReply ExecuteDragOver(TSharedPtr<SGraphEditor> GraphEditor);`
- L20 _public prototype_ `FReply ExecuteDrop(TSharedPtr<SGraphEditor> GraphEditor, const FSlateCompatVector2f& NewLocation);`
- L24 _private member_ `UCameraObjectInterfaceParameterBase* InterfaceParameter;`

### `Plugins/Cameras/GameplayCameras/Source/GameplayCamerasEditor/Public/Editors/CameraNodeGraphNode.h` (Public)


#### class `UCameraNodeGraphNode`  
`class UCameraNodeGraphNode : public UObjectTreeGraphNode`  
_L16-39_
- reflection: `UCLASS()`
- inherits: `UObjectTreeGraphNode`
- desc: Custom graph node for camera nodes. They mostly differ by showing input pins for any camera parameter property.
- L23 _public prototype_ `UCameraNodeGraphNode(const FObjectInitializer& ObjInit);` — Creates a new graph node.
- L25 _public prototype_ `virtual void BeginDestroy() override;`
- L30 _public prototype_ `virtual void AllocateDefaultPins() override;` — UEdGraphNode interface.
- L31 _public prototype_ `virtual TSharedPtr<SGraphNode> CreateVisualWidget() override;`
- L34 _public prototype_ `virtual void OnInitialize() override;` — UObjectTreeGraphNode interface.
- L38 _private prototype_ `void OnCustomCameraNodeParametersChanged(const UCameraNode* CameraNode);`

### `Plugins/Cameras/GameplayCameras/Source/GameplayCamerasEditor/Public/Editors/CameraObjectGraphSchemaBase.h` (Public)


#### class `UCameraObjectGraphSchemaBase`  
`class UCameraObjectGraphSchemaBase : public UObjectTreeGraphSchema`  
_L21-60_
- reflection: `UCLASS()`
- inherits: `UObjectTreeGraphSchema`
- desc: Base schema class for any kind of camera node graph.
- L27 _public member_ `static const FName PC_CameraParameter;` — A camera parameter pin.
- L28 _public member_ `static const FName PC_CameraVariableReference;` — A variable reference pin.
- L29 _public member_ `static const FName PC_CameraContextData;` — A context data pin.
- L31 _public prototype_ `UCameraObjectGraphSchemaBase(const FObjectInitializer& ObjInit);`
- L34 _public prototype_ `FObjectTreeGraphConfig BuildGraphConfig() const;` — Builds the config for a graph managed by this schema.
- L39 _protected prototype_ `virtual void GetGraphContextActions(FGraphContextMenuBuilder& ContextMenuBuilder) const override;` — UEdGraphSchema interface.
- L40 _protected prototype_ `virtual const FPinConnectionResponse CanCreateConnection(const UEdGraphPin* A, const UEdGraphPin* B) const override;`
- L41 _protected prototype_ `virtual bool OnBreakCustomPinLinks(UEdGraphPin& TargetPin) const;`
- L42 _protected prototype_ `virtual bool OnBreakSingleCustomPinLink(UEdGraphPin* SourcePin, UEdGraphPin* TargetPin) const;`
- L43 _protected prototype_ `virtual FLinearColor GetPinTypeColor(const FEdGraphPinType& PinType) const override;`
- L46 _protected prototype_ `virtual void OnCreateAllNodes(UObjectTreeGraph* InGraph, const FCreatedNodes& InCreatedNodes) const override;` — UObjectTreeGraphSchema interface.
- L47 _protected prototype_ `virtual bool OnTryCreateCustomConnection(UEdGraphPin* A, UEdGraphPin* B) const;`
- L52 _protected function_ `virtual void OnBuildGraphConfig(FObjectTreeGraphConfig& InOutGraphConfig) const` — UCameraObjectGraphSchemaBase interface.
- L56 _private prototype_ `void CreateValueFlowConnections(UObjectTreeGraph* InGraph, const FCreatedNodes& InCreatedNodes) const;`
- L57 _private prototype_ `UEdGraphPin* FindPinByType(UEdGraphNode* InNode, const FName& InPinCategory) const;`
- L59 _private member_ `UE::Cameras::FCameraNodeGraphPinColors PinColors;`

#### struct `FCameraObjectGraphSchemaAction_NewInterfaceParameterNode`  
`struct FCameraObjectGraphSchemaAction_NewInterfaceParameterNode : public FEdGraphSchemaAction`  
_L66-87_
- reflection: `USTRUCT()`
- inherits: `FEdGraphSchemaAction`
- desc: Graph editor action for adding a new camera rig parameter, plus an associated getter node in the graph.
- L74 _public member_ `FCameraObjectInterfaceParameterDefinition ParameterDefinition;` — `UPROPERTY()` — The new parameter's definition.
- L78 _public prototype_ `FCameraObjectGraphSchemaAction_NewInterfaceParameterNode();`
- L79 _public prototype_ `FCameraObjectGraphSchemaAction_NewInterfaceParameterNode(FText InNodeCategory, FText InMenuDesc, FText InToolTip, const int32 InGrouping = 0, FText InKeywords = FText());`
- L84 _public function_ `static FName StaticGetTypeId()` — FEdGraphSchemaAction interface.
- L85 _public function_ `virtual FName GetTypeId() const override`
- L86 _public prototype_ `virtual UEdGraphNode* PerformAction(UEdGraph* ParentGraph, UEdGraphPin* FromPin, FPerformGraphActionLocation Location, bool bSelectNewNode = true) override;`

#### struct `FCameraObjectGraphSchemaAction_AddInterfaceParameterGetterNode`  
`struct FCameraObjectGraphSchemaAction_AddInterfaceParameterGetterNode : public FEdGraphSchemaAction`  
_L93-114_
- reflection: `USTRUCT()`
- inherits: `FEdGraphSchemaAction`
- desc: Graph editor action for adding a new getter node for an existing camera rig parameter.
- L101 _public member_ `TObjectPtr<UCameraObjectInterfaceParameterBase> InterfaceParameter;` — `UPROPERTY()` — The existing camera rig parameter to create a getter node for.
- L105 _public prototype_ `FCameraObjectGraphSchemaAction_AddInterfaceParameterGetterNode();`
- L106 _public prototype_ `FCameraObjectGraphSchemaAction_AddInterfaceParameterGetterNode(FText InNodeCategory, FText InMenuDesc, FText InToolTip, const int32 InGrouping = 0, FText InKeywords = FText());`
- L111 _public function_ `static FName StaticGetTypeId()` — FEdGraphSchemaAction interface.
- L112 _public function_ `virtual FName GetTypeId() const override`
- L113 _public prototype_ `virtual UEdGraphNode* PerformAction(UEdGraph* ParentGraph, UEdGraphPin* FromPin, FPerformGraphActionLocation Location, bool bSelectNewNode = true) override;`

### `Plugins/Cameras/GameplayCameras/Source/GameplayCamerasEditor/Public/Editors/CameraObjectInterfaceParameterGraphNode.h` (Public)


#### class `UCameraObjectInterfaceParameterGraphNode`  
`class UCameraObjectInterfaceParameterGraphNode : public UObjectTreeGraphNode`  
_L15-32_
- reflection: `UCLASS()`
- inherits: `UObjectTreeGraphNode`
- desc: Custom graph editor node for a camera rig parameter getter.
- L22 _public prototype_ `UCameraObjectInterfaceParameterGraphNode(const FObjectInitializer& ObjInit);` — Creates a new graph node.
- L25 _public prototype_ `UCameraObjectInterfaceParameterBase* GetInterfaceParameter() const;` — Finds the camera interface parameter.
- L30 _public prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;` — UEdGraphNode interface
- L31 _public prototype_ `virtual TSharedPtr<SGraphNode> CreateVisualWidget() override;`

### `Plugins/Cameras/GameplayCameras/Source/GameplayCamerasEditor/Public/Editors/CameraRigCameraNodeGraphSchema.h` (Public)


#### class `UCameraRigCameraNodeGraphSchema`  
`class UCameraRigCameraNodeGraphSchema : public UCameraObjectGraphSchemaBase`  
_L13-28_
- reflection: `UCLASS()`
- inherits: `UCameraObjectGraphSchemaBase`
- desc: Schema class for camera node graph.
- L19 _public prototype_ `UCameraRigCameraNodeGraphSchema(const FObjectInitializer& ObjInit);`
- L24 _protected prototype_ `virtual void CollectAllObjects(UObjectTreeGraph* InGraph, TSet<UObject*>& OutAllObjects) const override;` — UObjectTreeGraphSchema interface.
- L27 _protected prototype_ `virtual void OnBuildGraphConfig(FObjectTreeGraphConfig& InOutGraphConfig) const override;` — UCameraObjectGraphSchemaBase interface.

### `Plugins/Cameras/GameplayCameras/Source/GameplayCamerasEditor/Public/Editors/CameraRigPickerConfig.h` (Public)


#### struct `UE::Cameras::FCameraRigPickerConfig`  
`struct FCameraRigPickerConfig`  
_L25-66_
- desc: Configuration structure for a camera rig picker widget. This is a widget that shows the list of camera rigs inside a given camera asset. See IGameplayCamerasEditorModule for creating that widget.
- L28 _public member_ `FAssetData InitialCameraAssetSelection;` — The initially selected camera asset, if any.
- L31 _public member_ `UCameraRigAsset* InitialCameraRigSelection = nullptr;` — The initially selected camera rig, specified as a pointer, if any.
- L34 _public member_ `FGuid InitialCameraRigSelectionGuid;` — The initially selected camera rig, specified by its Guid, if any.
- L41 _public member_ `bool bCanSelectCameraAsset = true;` — Whether a camera asset can be picked, or whether InitialCameraAssetSelection determines the only asset to be used. If the latter (when the value is false), then no camera asset picker is shown. Only the list of rigs is shown.
- L44 _public member_ `EAssetViewType::Type CameraAssetViewType = EAssetViewType::List;` — Asset picker view type for the camera asset picker.
- L47 _public member_ `FString CameraAssetSaveSettingsName;` — Asset picker settings name for the camera asset picker.
- L50 _public member_ `bool bFocusCameraRigSearchBoxWhenOpened = true;` — Whether the camera rig search box should be focused initially.
- L53 _public member_ `FText WarningMessage;` — An optional warning message to display.
- L56 _public member_ `FText ErrorMessage;` — An optional error message to display.
- L59 _public member_ `FOnCameraRigSelected OnCameraRigSelected;` — Callback for when a camera rig has been selected.
- L65 _public member_ `TSharedPtr<IPropertyHandle> PropertyToSet;` — An optional property handle to set the selected camera rig on. Properties of type FGuid and UCameraRigAsset* are handled.

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace Cameras` (scope `UE`)
- L16 _delegate_ `DECLARE_DELEGATE_OneParam(FOnCameraRigSelected, UCameraRigAsset*);`
- L16 _prototype_ `DECLARE_DELEGATE_OneParam(FOnCameraRigSelected, UCameraRigAsset*);` (scope `UE::Cameras`)

### `Plugins/Cameras/GameplayCameras/Source/GameplayCamerasEditor/Public/Editors/CameraRigTransitionGraphSchema.h` (Public)


#### class `UCameraRigTransitionGraphSchema`  
`class UCameraRigTransitionGraphSchema : public UCameraRigTransitionGraphSchemaBase`  
_L13-21_
- reflection: `UCLASS()`
- inherits: `UCameraRigTransitionGraphSchemaBase`
- desc: Schema class for a camera rig's transition graph.
- L20 _protected prototype_ `virtual void OnBuildGraphConfig(FObjectTreeGraphConfig& InOutGraphConfig) const override;` — UCameraRigTransitionGraphSchemaBase interface.

### `Plugins/Cameras/GameplayCameras/Source/GameplayCamerasEditor/Public/Editors/CameraRigTransitionGraphSchemaBase.h` (Public)


#### class `UCameraRigTransitionGraphSchemaBase`  
`class UCameraRigTransitionGraphSchemaBase : public UCameraObjectGraphSchemaBase`  
_L15-26_
- reflection: `UCLASS()`
- inherits: `UCameraObjectGraphSchemaBase`
- desc: Base schema class for camera transition graph.
- L22 _protected prototype_ `virtual void CollectAllObjects(UObjectTreeGraph* InGraph, TSet<UObject*>& OutAllObjects) const override;` — UObjectTreeGraphSchema interface.
- L25 _protected prototype_ `virtual void OnBuildGraphConfig(FObjectTreeGraphConfig& InOutGraphConfig) const override;` — UCameraObjectGraphSchemaBase interface.

### `Plugins/Cameras/GameplayCameras/Source/GameplayCamerasEditor/Public/Editors/CameraShakeCameraNodeGraphSchema.h` (Public)


#### class `UCameraShakeCameraNodeGraphSchema`  
`class UCameraShakeCameraNodeGraphSchema : public UCameraObjectGraphSchemaBase`  
_L13-28_
- reflection: `UCLASS()`
- inherits: `UCameraObjectGraphSchemaBase`
- desc: Schema class for camera node graph.
- L19 _public prototype_ `UCameraShakeCameraNodeGraphSchema(const FObjectInitializer& ObjInit);`
- L24 _protected prototype_ `virtual void CollectAllObjects(UObjectTreeGraph* InGraph, TSet<UObject*>& OutAllObjects) const override;` — UObjectTreeGraphSchema interface.
- L27 _protected prototype_ `virtual void OnBuildGraphConfig(FObjectTreeGraphConfig& InOutGraphConfig) const override;` — UCameraObjectGraphSchemaBase interface.

### `Plugins/Cameras/GameplayCameras/Source/GameplayCamerasEditor/Public/Editors/CameraSharedTransitionGraphSchema.h` (Public)


#### class `UCameraSharedTransitionGraphSchema`  
`class UCameraSharedTransitionGraphSchema : public UCameraRigTransitionGraphSchemaBase`  
_L13-21_
- reflection: `UCLASS()`
- inherits: `UCameraRigTransitionGraphSchemaBase`
- desc: Schema class for a camera asset's shared transition graph.
- L20 _protected prototype_ `virtual void OnBuildGraphConfig(FObjectTreeGraphConfig& InOutGraphConfig) const override;` — UCameraRigTransitionGraphSchemaBase interface.

### `Plugins/Cameras/GameplayCameras/Source/GameplayCamerasEditor/Public/Editors/CameraVariablePickerConfig.h` (Public)


#### struct `UE::Cameras::FCameraVariablePickerConfig`  
`struct FCameraVariablePickerConfig`  
_L23-46_
- desc: Configuration structure for a camera variable picker widget. This is a widget that shows the list of camera variables inside a given camera variable collection. It can be filtered by variable type. See IGameplayCamerasEditorModule for creating that widget.
- L26 _public member_ `FAssetData InitialCameraVariableCollectionSelection;` — The initially selected camera variable collection, if any.
- L33 _public member_ `UCameraVariableAsset* InitialCameraVariableSelection = nullptr;` — The initially selected camera variable, if any. When set, InitialCameraVariableCollectionSelection is ignored, and the outer collection of the selected variable is used instead.
- L36 _public member_ `UClass* CameraVariableClass = nullptr;` — The type of variable to select.
- L39 _public member_ `EAssetViewType::Type CameraAssetViewType = EAssetViewType::List;` — Asset picker view type for the camera variable collection picker.
- L42 _public member_ `FString CameraVariableCollectionSaveSettingsName;` — Asset picker settings name for the camera variable collection picker.
- L45 _public member_ `FOnCameraVariableSelected OnCameraVariableSelected;` — Callback for when a camera variable has been selected.

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace Cameras` (scope `UE`)
- L14 _delegate_ `DECLARE_DELEGATE_OneParam(FOnCameraVariableSelected, UCameraVariableAsset*);`
- L14 _prototype_ `DECLARE_DELEGATE_OneParam(FOnCameraVariableSelected, UCameraVariableAsset*);` (scope `UE::Cameras`)

### `Plugins/Cameras/GameplayCameras/Source/GameplayCamerasEditor/Public/Editors/GameplayCamerasGraphPanelPinFactory.h` (Public)


#### struct `UE::Cameras::FGameplayCamerasGraphPanelPinFactory`  
`struct FGameplayCamerasGraphPanelPinFactory : public FGraphPanelPinFactory`  
_L16-22_
- inherits: `FGraphPanelPinFactory`
- desc: Graph editor pin factory for camera-specific pin widgets.
- L21 _public prototype_ `virtual TSharedPtr<SGraphPin> CreatePin(UEdGraphPin* Pin) const override;` — FGraphPanelPinFactory interface.

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace Cameras` (scope `UE`)

### `Plugins/Cameras/GameplayCameras/Source/GameplayCamerasEditor/Public/Editors/ObjectTreeConnectionDrawingPolicy.h` (Public)


#### class `FObjectTreeConnectionDrawingPolicy`  
`class FObjectTreeConnectionDrawingPolicy : public FConnectionDrawingPolicy`  
_L7-12_
- inherits: `FConnectionDrawingPolicy`
- L11 _public prototype_ `FObjectTreeConnectionDrawingPolicy(int32 InBackLayerID, int32 InFrontLayerID, float InZoomFactor, const FSlateRect& InClippingRect, FSlateWindowElementList& InDrawElements);`

### `Plugins/Cameras/GameplayCameras/Source/GameplayCamerasEditor/Public/Editors/ObjectTreeDragDropOp.h` (Public)


#### class `FObjectTreeClassDragDropOp`  
`class FObjectTreeClassDragDropOp : public FDecoratedDragDropOp`  
_L15-36_
- inherits: `FDecoratedDragDropOp`
- desc: Drag-drop operation for creating a new object (and corresponding graph node) in an object tree graph by dragging one of the entries from the toolbox widget.
- L19 _public prototype_ `DRAG_DROP_OPERATOR_TYPE(FObjectTreeClassDragDropOp, FDecoratedDragDropOp) static TSharedRef<FObjectTreeClassDragDropOp> New(UClass* InObjectClass);`
- L22 _public prototype_ `static TSharedRef<FObjectTreeClassDragDropOp> New(TArrayView<UClass*> InObjectClasses);`
- L24 _public function_ `TArrayView<UClass* const> GetObjectClasses() const`
- L26 _public prototype_ `FReply ExecuteDragOver(TSharedPtr<SGraphEditor> GraphEditor);`
- L27 _public prototype_ `FReply ExecuteDrop(TSharedPtr<SGraphEditor> GraphEditor, const FSlateCompatVector2f& NewLocation);`
- L31 _private prototype_ `TArray<UClass*> FilterPlaceableObjectClasses(UObjectTreeGraph* InGraph);`
- L35 _private member_ `TArray<UClass*> ObjectClasses;`

### `Plugins/Cameras/GameplayCameras/Source/GameplayCamerasEditor/Public/Editors/ObjectTreeGraph.h` (Public)


#### class `UObjectTreeGraph`  
`class UObjectTreeGraph : public UEdGraph`  
_L22-59_
- reflection: `UCLASS()`
- inherits: `UEdGraph`
- desc: A node graph that represents a hierarchy of objects and their relationships.
- L29 _public prototype_ `UObjectTreeGraph(const FObjectInitializer& ObjInit);` — Creates a new graph.
- L32 _public prototype_ `void Reset(TObjectPtr<UObject> InRootObject, const FObjectTreeGraphConfig& InConfig);` — Initializes the graph given a root object and a graph configuration.
- L35 _public function_ `UObject* GetRootObject() const` — Gets the root object.
- L37 _public function_ `UObjectTreeGraphNode* GetRootObjectNode() const` — Gets the root object's graph node.
- L40 _public prototype_ `UObjectTreeGraphNode* FindObjectNode(UObject* InObject) const;` — Finds a node for the given object.
- L43 _public prototype_ `const FObjectTreeGraphConfig& GetConfig() const;` — Gets the graph configuration.
- L47 _public prototype_ `void RebuildGraph();`
- L51 _private member_ `TWeakObjectPtr<> WeakRootObject;`
- L53 _private member_ `FObjectTreeGraphConfig Config;`
- L56 _private member_ `TObjectPtr<UObjectTreeGraphNode> RootObjectNode;` — `UPROPERTY()`

### `Plugins/Cameras/GameplayCameras/Source/GameplayCamerasEditor/Public/Editors/ObjectTreeGraphCommentNode.h` (Public)


#### class `UObjectTreeGraphCommentNode`  
`class UObjectTreeGraphCommentNode : public UEdGraphNode_Comment`  
_L14-43_
- reflection: `UCLASS(MinimalAPI, Optional)`
- inherits: `UEdGraphNode_Comment`
- L21 _public prototype_ `void Initialize(UObjectTreeGraphComment* InObject);` — Initializes this graph node for the given comment object.
- L24 _public function_ `UObjectTreeGraphComment* GetObject() const` — Gets the underlying comment object represented by this graph node.
- L29 _public prototype_ `virtual TSharedPtr<SGraphNode> CreateVisualWidget() override;` — UEdGraphNode interface.
- L30 _public prototype_ `virtual void GetNodeContextMenuActions(UToolMenu* Menu, UGraphNodeContextMenuContext* Context) const override;`
- L31 _public prototype_ `virtual void PostPlacedNewNode() override;`
- L32 _public prototype_ `virtual void ResizeNode(const FSlateCompatVector2f& NewSize) override;`
- L33 _public prototype_ `virtual void OnRenameNode(const FString& NewName) override;`
- L37 _public prototype_ `void OnGraphNodeMoved(bool bMarkDirty);`
- L42 _private member_ `TWeakObjectPtr<UObjectTreeGraphComment> WeakObject;` — `UPROPERTY()`

### `Plugins/Cameras/GameplayCameras/Source/GameplayCamerasEditor/Public/Editors/ObjectTreeGraphConfig.h` (Public)


#### struct `FObjectTreeGraphClassConfig`  
`struct FObjectTreeGraphClassConfig`  
_L49-160_
- desc: A structure providing optional configuration options for a given object class.
- L112 _public prototype_ `FObjectTreeGraphClassConfig();`
- L115 _public prototype_ `FObjectTreeGraphClassConfig& OnlyAsRoot();` — A shortcut for disabling CanCreateNew and CanDelete.
- L120 _public function_ `TArrayView<const FString> StripDisplayNameSuffixes() const` — Gets the name suffixes to strip.
- L123 _public function_ `FObjectTreeGraphClassConfig& StripDisplayNameSuffix(const FString& InSuffix)` — Adds a new suffix to strip from the display name.
- L130 _public function_ `FObjectTreeGraphClassConfig& StripDisplayNameSuffixes(std::initializer_list<FString> InSuffixes)` — Adds multiple suffixes to strip from the display name.
- L137 _public function_ `const TMap<FName, EEdGraphPinDirection>& PropertyPinDirectionOverrides() const` — Gets the custom property pin directions for given named properties.
- L140 _public function_ `FObjectTreeGraphClassConfig& SetPropertyPinDirectionOverride(const FName& InPropertyName, EEdGraphPinDirection InDirection)` — Adds a new custom property pin direction for a given named property.
- L147 _public function_ `TOptional<EEdGraphPinDirection> GetPropertyPinDirectionOverride(const FName& InPropertyName) const` — Gets the custom property pin direction for a given named property.
- L158 _private member_ `TArray<FString> _StripDisplayNameSuffixes;`
- L159 _private member_ `TMap<FName, EEdGraphPinDirection> _PropertyPinDirectionOverrides;`

#### struct `FObjectTreeGraphClassConfigs`  
`struct FObjectTreeGraphClassConfigs`  
_L187-247_
- desc: A composite of multiple class configurations, for handling configuration options set on different classes in a class hierarchy.
- L231 _public prototype_ `FObjectTreeGraphClassConfigs();`
- L232 _public prototype_ `FObjectTreeGraphClassConfigs(TArrayView<const FObjectTreeGraphClassConfig*> InClassConfigs);`
- L237 _public prototype_ `void GetStripDisplayNameSuffixes(TArray<FString>& OutSuffixes) const;` — Gets the name suffixes to strip.
- L240 _public prototype_ `TOptional<EEdGraphPinDirection> GetPropertyPinDirectionOverride(const FName& InPropertyName) const;` — Gets the custom property pin direction for a given named property.
- L244 _private member_ `static FObjectTreeGraphClassConfig DefaultConfig;`
- L246 _private member_ `TArray<const FObjectTreeGraphClassConfig*, TInlineAllocator<2>> InnerConfigs;`

#### struct `FObjectTreeGraphConfig`  
`struct FObjectTreeGraphConfig`  
_L255-363_
- desc: A structure that provides all the information needed to build, edit, and maintain an object tree graph.
- L262 _public member_ `FName GraphName;` — The name of the graph, passed to some APIs like IObjectTreeGraphRootObject.
- L272 _public member_ `TArray<UClass*> ConnectableObjectClasses;` — The list of connectable object classes. Objects whose class is connectable (which includes sub-classes) will be eligible to be nodes in the graph. Properties on those objects that point to other connectable objects (either with a direct object property or an array property) will show up as pins on the object's node.
- L278 _public member_ `TArray<UClass*> NonConnectableObjectClasses;` — The list of unconnectable object classes. This serves as an exception list to the ConnectableObjectClasses list.
- L283 _public member_ `TSubclassOf<UObjectTreeGraphNode> DefaultGraphNodeClass;` — The default graph node class to use in the graph. Defaults to UObjectTreeGraphNode.
- L286 _public member_ `FName DefaultSelfPinName;` — The default name for a node's self pin.
- L288 _public member_ `FText DefaultSelfPinFriendlyName;` — The default friendly name for a node's self pin.
- L291 _public member_ `FLinearColor DefaultGraphNodeTitleColor;` — The default title background color for an object's graph node.
- L293 _public member_ `FLinearColor DefaultGraphNodeTitleTextColor;` — The default title text color for an object's graph node.
- L295 _public member_ `FLinearColor DefaultGraphNodeBodyTintColor;` — The default body color for an object's graph node.
- L298 _public member_ `FOnFormatObjectDisplayName OnFormatObjectDisplayName;` — A custom callback to format an object's display name.
- L301 _public member_ `FGraphDisplayInfo GraphDisplayInfo;` — The graph display information.
- L304 _public member_ `FOnGetGraphDisplayInfo OnGetGraphDisplayInfo;` — A custom callback to get the graph display information, to override GraphDisplayInfo.
- L307 _public member_ `TMap<UClass*, FObjectTreeGraphClassConfig> ObjectClassConfigs;` — Advanced, optional bits of configuration for specific classes and sub-classes of objects.
- L312 _public prototype_ `FObjectTreeGraphConfig();` — Creates a new graph config.
- L320 _public prototype_ `bool IsConnectable(UClass* InObjectClass) const;` — Returns whether the given class is connectable. It is connectable if it, or one of its parent classes, is inside ConnectableObjectClasses, and nor it or any of its parent classes is in NonConnectableObjectClasses.
- L328 _public prototype_ `bool IsConnectable(FObjectProperty* InObjectProperty) const;` — Returns whether the given object reference property is connectable. It is connectable if the property's reference type is for a connectable class, and if the property doesn't have the ObjectTreeGraphHidden metadata.
- L336 _public prototype_ `bool IsConnectable(FArrayProperty* InArrayProperty) const;` — Returns whether the given object array property is connectable. It is connectable if the array's item type is for a connectable class, and if the array property doesn't have the ObjectTreeGraphHidden metadata.
- L343 _public prototype_ `void GetConnectableClasses(TArray<UClass*>& OutClasses, bool bPlaceableOnly = false);` — Gets all possible known connectable classes. @param bPlaceableOnly  If set, only return those that can be created.
- L346 _public prototype_ `FObjectTreeGraphClassConfigs GetObjectClassConfigs(const UClass* InObjectClass) const;` — Gets the advanced class-specific configuration for the given class.
- L349 _public prototype_ `FText GetDisplayNameText(const UObject* InObject) const;` — Computes the display name of the given object.
- L351 _public prototype_ `FText GetDisplayNameText(const UClass* InClass) const;` — Computes the display name of the given object class.
- L354 _public prototype_ `EEdGraphPinDirection GetSelfPinDirection(const UClass* InObjectClass) const;` — Gets the "self" pin direction for a given class.
- L357 _public prototype_ `EEdGraphPinDirection GetPropertyPinDirection(const UClass* InObjectClass, const FName& InPropertyName) const;` — Gets the custom property pin direction for a given named property.
- L361 _private prototype_ `FText GetDisplayNameText(const UClass* InClass, const FObjectTreeGraphClassConfigs& InClassConfig) const;`
- L362 _private prototype_ `void FormatDisplayNameText(const UObject* InObject, const FObjectTreeGraphClassConfigs& InClassConfig, FText& InOutDisplayNameText) const;`

#### Free symbols / members of external scopes

- L24 _delegate_ `DECLARE_DELEGATE_OneParam(FOnBuildObjectTreeGraphConfig, FObjectTreeGraphConfig& InOutConfig);`
- L24 _prototype_ `DECLARE_DELEGATE_OneParam(FOnBuildObjectTreeGraphConfig, FObjectTreeGraphConfig& InOutConfig);`
- L26 _delegate_ `DECLARE_DELEGATE_OneParam(FOnSetupNewObject, UObject*);`
- L26 _prototype_ `DECLARE_DELEGATE_OneParam(FOnSetupNewObject, UObject*);`
- L27 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(FText, FOnGetObjectClassDisplayName, const UClass*);`
- L27 _prototype_ `DECLARE_DELEGATE_RetVal_OneParam(FText, FOnGetObjectClassDisplayName, const UClass*);`
- L29 _delegate_ `DECLARE_DELEGATE_TwoParams(FOnGetGraphDisplayInfo, const UObjectTreeGraph*, FGraphDisplayInfo&);`
- L29 _prototype_ `DECLARE_DELEGATE_TwoParams(FOnGetGraphDisplayInfo, const UObjectTreeGraph*, FGraphDisplayInfo&);`
- L30 _delegate_ `DECLARE_DELEGATE_TwoParams(FOnFormatObjectDisplayName, const UObject*, FText&);`
- L30 _prototype_ `DECLARE_DELEGATE_TwoParams(FOnFormatObjectDisplayName, const UObject*, FText&);`
- L32 _macro_ `#define OTGCC_FIELD(FieldType, FieldName)\`
- L43 _macro_ `#define OTGCC_FIELD_FLAG(FieldName)\`
- L165 _macro_ `#define OTGCCS_FIELD(FieldType, FieldName)\`

### `Plugins/Cameras/GameplayCameras/Source/GameplayCamerasEditor/Public/Editors/ObjectTreeGraphNode.h` (Public)


#### class `UObjectTreeGraphNode`  
`class UObjectTreeGraphNode : public UEdGraphNode`  
_L21-125_
- reflection: `UCLASS()`
- inherits: `UEdGraphNode`
- desc: A graph node that represents an object inside an object tree graph.
- L28 _public prototype_ `UObjectTreeGraphNode(const FObjectInitializer& ObjInit);` — Creates a new graph node.
- L31 _public prototype_ `void Initialize(UObject* InObject);` — Initializes this graph node for the given object.
- L34 _public function_ `UObject* GetObject() const` — Gets the underlying object represented by this graph node.
- L36 _public prototype_ `template<typename ObjectClass> bool IsObjectA() const;` — Gets whether we have a valid underlying object, and that it's a type of ObjectClass.
- L38 _public prototype_ `template<typename ObjectClass> ObjectClass* CastObject() const;` — Gets the underlying object as a point to the given sub-class.
- L41 _public prototype_ `void GetAllConnectableProperties(TArray<FProperty*>& OutProperties) const;` — Gets all connectable properties on the underlying object.
- L44 _public prototype_ `UEdGraphPin* GetSelfPin() const;` — Finds the self pin that represents the underlying object itself.
- L46 _public prototype_ `void OverrideSelfPinDirection(EEdGraphPinDirection Direction);` — Changes the direction of the self pin.
- L49 _public prototype_ `UEdGraphPin* GetPinForProperty(FObjectProperty* InProperty) const;` — Finds the pin for the given object property.
- L51 _public prototype_ `UEdGraphPin* GetPinForProperty(FArrayProperty* InProperty) const;` — Finds the invisible parent pin for the given array property.
- L53 _public prototype_ `UEdGraphPin* GetPinForProperty(FArrayProperty* InProperty, int32 Index) const;` — Finds the pin for the given item in an array property.
- L55 _public prototype_ `FProperty* GetPropertyForPin(const UEdGraphPin* InPin) const;` — Gets the underlying property represented by the given pin.
- L57 _public prototype_ `UClass* GetConnectedObjectClassForPin(const UEdGraphPin* InPin) const;` — Gets the type of object that can connect to the given pin.
- L59 _public prototype_ `int32 GetIndexOfArrayPin(const UEdGraphPin* InPin) const;` — Gets the index of the given pin's underlying value inside an array property.
- L64 _public prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;` — UEdGraphNode interface.
- L65 _public prototype_ `virtual TSharedPtr<SGraphNode> CreateVisualWidget() override;`
- L66 _public prototype_ `virtual FLinearColor GetNodeTitleColor() const override;`
- L68 _public prototype_ `virtual FLinearColor GetNodeTitleTextColor() const override;`
- L70 _public prototype_ `virtual FLinearColor GetNodeBodyTintColor() const override;`
- L71 _public prototype_ `virtual FText GetTooltipText() const override;`
- L72 _public prototype_ `virtual void AllocateDefaultPins() override;`
- L73 _public prototype_ `virtual void PostPlacedNewNode() override;`
- L74 _public prototype_ `virtual void AutowireNewNode(UEdGraphPin* FromPin) override;`
- L75 _public prototype_ `virtual void PinConnectionListChanged(UEdGraphPin* Pin) override;`
- L76 _public prototype_ `virtual void NodeConnectionListChanged() override;`
- L77 _public prototype_ `virtual void OnPinRemoved(UEdGraphPin* InRemovedPin) override;`
- L78 _public prototype_ `virtual void ReconstructNode() override;`
- L79 _public prototype_ `virtual void GetNodeContextMenuActions(class UToolMenu* Menu, class UGraphNodeContextMenuContext* Context) const override;`
- L80 _public prototype_ `virtual bool GetCanRenameNode() const override;`
- L81 _public prototype_ `virtual void OnRenameNode(const FString& NewName) override;`
- L82 _public prototype_ `virtual bool CanDuplicateNode() const override;`
- L83 _public prototype_ `virtual bool CanUserDeleteNode() const override;`
- L84 _public prototype_ `virtual bool SupportsCommentBubble() const override;`
- L85 _public prototype_ `virtual void OnUpdateCommentText(const FString& NewComment) override;`
- L88 _public function_ `virtual void OnInitialize()` — UObjectTreeGraphNode interface.
- L89 _public prototype_ `virtual void OnGraphNodeMoved(bool bMarkDirty);`
- L90 _public function_ `virtual void OnDoubleClicked()`
- L95 _public prototype_ `void GetArrayProperties(TArray<FArrayProperty*>& OutArrayProperties, EEdGraphPinDirection Direction) const;` — Internal API.
- L96 _public prototype_ `void CreateNewItemPins(FArrayProperty& InArrayProperty, int32 NumExtraPins);`
- L97 _public prototype_ `void CreateNewItemPins(UEdGraphPin* InParentArrayPin, int32 NumExtraPins);`
- L98 _public prototype_ `void InsertNewItemPin(UEdGraphPin* InParentArrayPin, int32 Index);`
- L99 _public prototype_ `void RemoveItemPin(UEdGraphPin* InItemPin);`
- L100 _public prototype_ `void RefreshArrayPropertyPinNames();`
- L112 _protected prototype_ `FNodeContext GetNodeContext() const;`
- L113 _protected prototype_ `const FObjectTreeGraphClassConfigs GetObjectClassConfigs() const;`
- L118 _private member_ `TWeakObjectPtr<UObject> WeakObject;` — `UPROPERTY()`
- L121 _private member_ `TEnumAsByte<EEdGraphPinDirection> SelfPinDirectionOverride;` — `UPROPERTY()`
- L124 _private member_ `bool bOverrideSelfPinDirection;` — `UPROPERTY()`
- L128 _function_ `template<typename ObjectClass> bool UObjectTreeGraphNode::IsObjectA() const`
- L138 _function_ `template<typename ObjectClass> ObjectClass* UObjectTreeGraphNode::CastObject() const`

#### struct `UObjectTreeGraphNode::FNodeContext`  
`struct FNodeContext`  
_L104-110_
- L106 _public member_ `UClass* ObjectClass;`
- L107 _public member_ `UObjectTreeGraph* Graph;`
- L108 _public member_ `const FObjectTreeGraphConfig& GraphConfig;`
- L109 _public member_ `const FObjectTreeGraphClassConfigs ObjectClassConfigs;`

### `Plugins/Cameras/GameplayCameras/Source/GameplayCamerasEditor/Public/Editors/ObjectTreeGraphSchema.h` (Public)


#### class `UObjectTreeGraphSchema`  
`class UObjectTreeGraphSchema : public UEdGraphSchema`  
_L28-144_
- reflection: `UCLASS()`
- inherits: `UEdGraphSchema`
- desc: Schema class for an object tree graph.
- L35 _public member_ `static const FName PC_Self;` — Pin categories.
- L36 _public member_ `static const FName PC_Property;` — A property pin.
- L39 _public member_ `static const FName PSC_ObjectProperty;` — Pin sub-categories.
- L40 _public member_ `static const FName PSC_ArrayProperty;` — An array property pin (generally hidden).
- L41 _public member_ `static const FName PSC_ArrayPropertyItem;` — A pin for an item inside an array property.
- L46 _public prototype_ `UObjectTreeGraphSchema(const FObjectInitializer& ObjInit);` — Creates a new schema.
- L49 _public prototype_ `void RebuildGraph(UObjectTreeGraph* InGraph) const;` — Rebuilds the graph from scratch.
- L52 _public prototype_ `UEdGraphNode* CreateObjectNode(UObjectTreeGraph* InGraph, UObject* InObject) const;` — Creates an object graph node for the given object.
- L55 _public prototype_ `void AddConnectableObject(UObjectTreeGraph* InGraph, UObject* InNewObject) const;` — Adds an object to the underlying data after it has been added to the graph.
- L58 _public prototype_ `void RemoveConnectableObject(UObjectTreeGraph* InGraph, UObject* InRemovedObject) const;` — Removes an object from the underlying data after it has been removed from the graph.
- L61 _public prototype_ `FString ExportNodesToText(const FGraphPanelSelectionSet& Nodes, bool bOnlyCanDuplicateNodes, bool bOnlyCanDeleteNodes) const;` — Export the given selection into a text suitable for copy/pasting.
- L64 _public prototype_ `void ImportNodesFromText(UObjectTreeGraph* InGraph, const FString& TextToImport, TArray<UEdGraphNode*>& OutPastedNodes) const;` — Imports the given text into the given graph.
- L67 _public prototype_ `bool CanImportNodesFromText(UObjectTreeGraph* InGraph, const FString& TextToImport) const;` — Checks if the given text is suitable for importing.
- L70 _public prototype_ `void InsertArrayItemPin(UEdGraphPin* ArrayPin, int32 Index = INDEX_NONE) const;` — Inserts a new array property item pin.
- L73 _public prototype_ `void InsertArrayItemPinBefore(UEdGraphPin* ArrayItemPin) const;` — Inserts a new array property item pin before the given pin.
- L76 _public prototype_ `void InsertArrayItemPinAfter(UEdGraphPin* ArrayItemPin) const;` — Inserts a new array property item pin after the given pin.
- L79 _public prototype_ `void RemoveArrayItemPin(UEdGraphPin* ArrayItemPin) const;` — Removes an array property item pin.
- L84 _public prototype_ `virtual void GetGraphContextActions(FGraphContextMenuBuilder& ContextMenuBuilder) const override;` — UEdGraphSchema interface.
- L85 _public prototype_ `virtual void GetContextMenuActions(class UToolMenu* Menu, class UGraphNodeContextMenuContext* Context) const override;`
- L86 _public prototype_ `virtual TSharedPtr<FEdGraphSchemaAction> GetCreateCommentAction() const override;`
- L87 _public prototype_ `virtual FName GetParentContextMenuName() const override;`
- L88 _public prototype_ `virtual FLinearColor GetPinTypeColor(const FEdGraphPinType& PinType) const override;`
- L89 _public prototype_ `virtual class FConnectionDrawingPolicy* CreateConnectionDrawingPolicy(int32 InBackLayerID, int32 InFrontLayerID, float InZoomFactor, const FSlateRect& InClippingRect, class FSlateWindowElementList& InDrawElements, UEdGraph* InGraph) const override;`
- L90 _public prototype_ `virtual bool ShouldAlwaysPurgeOnModification() const override;`
- L91 _public prototype_ `virtual FPinConnectionResponse CanCreateNewNodes(UEdGraphPin* InSourcePin) const override;`
- L92 _public prototype_ `virtual const FPinConnectionResponse CanCreateConnection(const UEdGraphPin* A, const UEdGraphPin* B) const override;`
- L93 _public prototype_ `virtual bool TryCreateConnection(UEdGraphPin* A, UEdGraphPin* B) const override;`
- L94 _public prototype_ `virtual void BreakNodeLinks(UEdGraphNode& TargetNode) const override;`
- L95 _public prototype_ `virtual void BreakPinLinks(UEdGraphPin& TargetPin, bool bSendsNodeNotification) const override;`
- L96 _public prototype_ `virtual void BreakSinglePinLink(UEdGraphPin* SourcePin, UEdGraphPin* TargetPin) const override;`
- L97 _public prototype_ `virtual bool SupportsDropPinOnNode(UEdGraphNode* InTargetNode, const FEdGraphPinType& InSourcePinType, EEdGraphPinDirection InSourcePinDirection, FText& OutErrorMessage) const override;`
- L98 _public prototype_ `virtual bool SafeDeleteNodeFromGraph(UEdGraph* Graph, UEdGraphNode* Node) const override;`
- L99 _public prototype_ `virtual void GetGraphDisplayInformation(const UEdGraph& Graph, FGraphDisplayInfo& OutDisplayInfo) const override;`
- L109 _protected prototype_ `virtual void CollectAllObjects(UObjectTreeGraph* InGraph, TSet<UObject*>& OutAllObjects) const;` — UObjectTreeGraphSchema interface.
- L110 _protected prototype_ `virtual void OnCreateAllNodes(UObjectTreeGraph* InGraph, const FCreatedNodes& InCreatedNodes) const;`
- L111 _protected prototype_ `virtual UEdGraphNode* OnCreateObjectNode(UObjectTreeGraph* InGraph, UObject* InObject) const;`
- L112 _protected prototype_ `virtual void OnAddConnectableObject(UObjectTreeGraph* InGraph, UObject* InNewObject) const;`
- L113 _protected prototype_ `virtual void OnRemoveConnectableObject(UObjectTreeGraph* InGraph, UObject* InRemovedObject) const;`
- L114 _protected prototype_ `virtual void CopyNonObjectNodes(TArrayView<UObject*> InObjects, FStringOutputDevice& OutDevice) const;`
- L115 _protected prototype_ `virtual bool OnTryCreateCustomConnection(UEdGraphPin* A, UEdGraphPin* B) const;`
- L116 _protected prototype_ `virtual bool OnBreakCustomPinLinks(UEdGraphPin& TargetPin) const;`
- L117 _protected prototype_ `virtual bool OnBreakSingleCustomPinLink(UEdGraphPin* SourcePin, UEdGraphPin* TargetPin) const;`
- L118 _protected prototype_ `virtual bool OnApplyConnection(UEdGraphPin* A, UEdGraphPin* B) const;`
- L119 _protected prototype_ `virtual bool OnApplyDisconnection(UEdGraphPin* TargetPin) const;`
- L120 _protected prototype_ `virtual bool OnApplyDisconnection(UEdGraphPin* SourcePin, UEdGraphPin* TargetPin) const;`
- L121 _protected prototype_ `virtual void OnDeleteNodeFromGraph(UObjectTreeGraph* Graph, UEdGraphNode* Node) const;`
- L122 _protected prototype_ `virtual void FilterGraphContextPlaceableClasses(TArray<UClass*>& InOutClasses) const;`
- L126 _protected prototype_ `static void CollectAllReferencedObjects(UObjectTreeGraph* InGraph, TSet<UObject*>& OutAllObjects);`
- L127 _protected prototype_ `static bool CollectAllConnectableObjectsFromRootInterface(UObjectTreeGraph* InGraph, TSet<UObject*>& OutAllObjects, bool bAllowNoRootInterface);`
- L129 _protected prototype_ `const FObjectTreeGraphClassConfigs GetObjectClassConfigs(const UObjectTreeGraphNode* InNode) const;`
- L130 _protected prototype_ `const FObjectTreeGraphClassConfigs GetObjectClassConfigs(const UObjectTreeGraph* InGraph, UClass* InObjectClass) const;`
- L132 _protected prototype_ `void ApplyConnection(UEdGraphPin* A, UEdGraphPin* B) const;`
- L133 _protected prototype_ `void ApplyDisconnection(UEdGraphPin* TargetPin) const;`
- L134 _protected prototype_ `void ApplyDisconnection(UEdGraphPin* SourcePin, UEdGraphPin* TargetPin) const;`
- L138 _private prototype_ `void RemoveAllNodes(UObjectTreeGraph* InGraph) const;`
- L139 _private prototype_ `void CreateAllNodes(UObjectTreeGraph* InGraph) const;`
- L140 _private prototype_ `void CreateConnections(UObjectTreeGraphNode* InGraphNode, const FCreatedNodes& InCreatedNodes) const;`
- L142 _private prototype_ `UEdGraphNode* CreateCommentNode(UObjectTreeGraph* InGraph, UObjectTreeGraphComment* InComment) const;`
- L143 _private prototype_ `void GetCommentAction(FGraphActionMenuBuilder& ActionMenuBuilder) const;`

#### struct `UObjectTreeGraphSchema::FCreatedNodes`  
`struct FCreatedNodes`  
_L103-106_
- L105 _public member_ `TMap<UObject*, UEdGraphNode*> CreatedNodes;`

#### struct `FObjectTreeGraphSchemaAction_NewNode`  
`struct FObjectTreeGraphSchemaAction_NewNode : public FEdGraphSchemaAction`  
_L150-180_
- reflection: `USTRUCT()`
- inherits: `FEdGraphSchemaAction`
- desc: Graph action to create a new object (and corresponding graph node) of a given class.
- L158 _public member_ `TObjectPtr<UObject> ObjectOuter;` — `UPROPERTY()` — The outer for the new object. Defaults to the root object's package.
- L162 _public member_ `TObjectPtr<UClass> ObjectClass;` — `UPROPERTY()` — The class of the new object.
- L166 _public prototype_ `FObjectTreeGraphSchemaAction_NewNode();`
- L167 _public prototype_ `FObjectTreeGraphSchemaAction_NewNode(FText InNodeCategory, FText InMenuDesc, FText InToolTip, const int32 InGrouping = 0, FText InKeywords = FText());`
- L172 _public function_ `static FName StaticGetTypeId()` — FEdGraphSchemaAction interface.
- L173 _public function_ `virtual FName GetTypeId() const override`
- L174 _public prototype_ `virtual UEdGraphNode* PerformAction(UEdGraph* ParentGraph, UEdGraphPin* FromPin, FPerformGraphActionLocation Location, bool bSelectNewNode = true) override;`
- L178 _protected prototype_ `virtual UObject* CreateObject();`
- L179 _protected prototype_ `virtual void AutoSetupNewNode(UEdGraphNode* NewNode, UEdGraphPin* FromPin);`

#### struct `FObjectTreeGraphSchemaAction_NewComment`  
`struct FObjectTreeGraphSchemaAction_NewComment : public FEdGraphSchemaAction`  
_L183-198_
- reflection: `USTRUCT()`
- inherits: `FEdGraphSchemaAction`
- L189 _public prototype_ `FObjectTreeGraphSchemaAction_NewComment();`
- L190 _public prototype_ `FObjectTreeGraphSchemaAction_NewComment(FText InNodeCategory, FText InMenuDesc, FText InToolTip, const int32 InGrouping = 0, FText InKeywords = FText());`
- L195 _public function_ `static FName StaticGetTypeId()` — FEdGraphSchemaAction interface.
- L196 _public function_ `virtual FName GetTypeId() const override`
- L197 _public prototype_ `virtual UEdGraphNode* PerformAction(UEdGraph* ParentGraph, UEdGraphPin* FromPin, FPerformGraphActionLocation Location, bool bSelectNewNode = true) override;`

### `Plugins/Cameras/GameplayCameras/Source/GameplayCamerasEditor/Public/Editors/ObjectTreeGraphSearch.h` (Public)


#### struct `FObjectTreeGraphSearchResult`  
`struct FObjectTreeGraphSearchResult`  
_L15-33_
- desc: Search result for an object tree graph search.
- L18 _public member_ `UEdGraph* Graph = nullptr;` — The graph in which the result was found.
- L21 _public member_ `UEdGraphNode* Node = nullptr;` — The node found to match the search.
- L24 _public member_ `FName PinName;` — The name of the pin that matched the search. None if the node itself matches.
- L28 _public function_ `FObjectTreeGraphSearchResult()`
- L30 _public function_ `FObjectTreeGraphSearchResult(UEdGraph* InGraph, UEdGraphNode* InNode, FName InPinName = NAME_None) : Graph(InGraph), Node(InNode), PinName(InPinName)`

#### class `FObjectTreeGraphSearch`  
`class FObjectTreeGraphSearch`  
_L39-74_
- desc: A utility class that can search a series of string tokens across an object tree graph.
- L43 _public prototype_ `FObjectTreeGraphSearch();`
- L48 _public prototype_ `void AddGraph(UEdGraph* InGraph);` — Adds a graph to search inside of.
- L50 _public prototype_ `void SetGraphs(TConstArrayView<UEdGraph*> InGraphs);` — Sets the graphs to search inside of.
- L53 _public prototype_ `void Search(TArrayView<FString> InTokens, TArray<FObjectTreeGraphSearchResult>& OutResults) const;` — Searchs for the given string tokens.
- L57 _private typedef_ `using FSearchResult = FObjectTreeGraphSearchResult;`
- L66 _private prototype_ `void SearchGraph(UEdGraph* Graph, FSearchState& State) const;`
- L67 _private prototype_ `void SearchNode(UEdGraphNode* Node, FSearchState& State) const;`
- L69 _private prototype_ `bool MatchString(const FString& InString, const FSearchState& InState) const;`
- L73 _private member_ `TArray<UEdGraph*> SearchGraphs;`

#### struct `FObjectTreeGraphSearch::FSearchState`  
`struct FSearchState`  
_L59-64_
- L61 _public member_ `UEdGraph* Graph = nullptr;`
- L62 _public member_ `TArrayView<FString> Tokens;`
- L63 _public member_ `TArray<FSearchResult> Results;`

### `Plugins/Cameras/GameplayCameras/Source/GameplayCamerasEditor/Public/Editors/SCameraAssetInterfaceParametersPanel.h` (Public)


#### class `UE::Cameras::SCameraAssetInterfaceParametersPanel`  
`class SCameraAssetInterfaceParametersPanel : public SCompoundWidget , public ICameraAssetEventHandler`  
_L21-86_
- inherits: `SCompoundWidget,ICameraAssetEventHandler`
- L27 _public member_ `static const FName ParameterTypeColumn;`
- L28 _public member_ `static const FName ParameterNameColumn;`
- L29 _public member_ `static const FName SourceCameraRigColumn;`
- L30 _public member_ `static const FName SourceParameterNameColumn;`
- L34 _public function_ `SLATE_BEGIN_ARGS(SCameraAssetInterfaceParametersPanel)`
- L36 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& Args, FCameraAssetEditorToolkit* OwnerToolkit);`
- L41 _public prototype_ `void RequestListRefresh();` — Request that the list of parameters be refreshed.
- L44 _public prototype_ `void RenameSelectedParameter();` — Rename the selected parameter in the focused panel.
- L47 _public prototype_ `void DeleteSelectedParameter();` — Delete the selected parameter in the focused panel.
- L50 _public function_ `FOnCameraAssetInterfaceParameterEvent& OnInterfaceParameterSelected()` — Delegate invoked when a parmeter is selected in the panel.
- L55 _protected prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;` — SWidget interface.
- L58 _protected prototype_ `virtual void OnCameraAssetInterfaceChanged() override;` — ICameraAssetEventHandler interface.
- L62 _private prototype_ `TSharedRef<ITableRow> OnGenerateInterfaceParameterRow(TObjectPtr<UCameraAssetInterfaceParameter> Item, const TSharedRef<STableViewBase>& OwnerTable);`
- L63 _private prototype_ `void OnInterfaceParameterSelectionChanged(TObjectPtr<UCameraAssetInterfaceParameter> Item, ESelectInfo::Type Type);`
- L64 _private prototype_ `TSharedPtr<SWidget> OnInterfaceParameterContextMenuOpening();`
- L66 _private prototype_ `FReply OnAddInterfaceParameter();`
- L67 _private prototype_ `FReply OnDeleteSelectedInterfaceParameter();`
- L69 _private prototype_ `void OnRenameInterfaceParameter(TObjectPtr<UCameraAssetInterfaceParameter> Item);`
- L70 _private prototype_ `void OnDeleteInterfaceParameter(TObjectPtr<UCameraAssetInterfaceParameter> Item);`
- L72 _private prototype_ `FString GetNewParameterName();`
- L76 _private member_ `UCameraAsset* CameraAsset = nullptr;`
- L77 _private member_ `FCameraAssetEditorToolkit* Toolkit = nullptr;`
- L79 _private member_ `TCameraEventHandler<ICameraAssetEventHandler> EventHandler;`
- L81 _private member_ `TSharedPtr<SListView<TObjectPtr<UCameraAssetInterfaceParameter>>> ParametersListView;`
- L83 _private member_ `FOnCameraAssetInterfaceParameterEvent OnInterfaceParameterSelectedDelegate;`
- L85 _private member_ `bool bListRefreshRequested = false;`

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace Cameras` (scope `UE`)
- L19 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnCameraAssetInterfaceParameterEvent, UCameraAssetInterfaceParameter*);`
- L19 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnCameraAssetInterfaceParameterEvent, UCameraAssetInterfaceParameter*);` (scope `UE::Cameras`)

### `Plugins/Cameras/GameplayCameras/Source/GameplayCamerasEditor/Public/Editors/SCameraNodeGraphEditor.h` (Public)


#### class `SCameraNodeGraphEditor`  
`class SCameraNodeGraphEditor : public SObjectTreeGraphEditor`  
_L7-15_
- inherits: `SObjectTreeGraphEditor`
- L13 _protected prototype_ `virtual FReply OnDragOver(const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent) override;` — SWidget interface.
- L14 _protected prototype_ `virtual FReply OnDrop(const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent) override;`

### `Plugins/Cameras/GameplayCameras/Source/GameplayCamerasEditor/Public/Editors/SCameraNodeGraphNode.h` (Public)


#### class `SCameraNodeGraphNode`  
`class SCameraNodeGraphNode : public SObjectTreeGraphNode`  
_L7-23_
- inherits: `SObjectTreeGraphNode`
- L11 _public function_ `SLATE_BEGIN_ARGS(SCameraNodeGraphNode) : _GraphNode(nullptr)`
- L14 _public prototype_ `SLATE_ARGUMENT(UObjectTreeGraphNode*, GraphNode) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L22 _public prototype_ `virtual TSharedPtr<SGraphPin> CreatePinWidget(UEdGraphPin* InPin) const override;` — SGraphNode interface.

### `Plugins/Cameras/GameplayCameras/Source/GameplayCamerasEditor/Public/Editors/SCameraObjectInterfaceParameterGraphNode.h` (Public)


#### class `SCameraObjectInterfaceParameterGraphNode`  
`class SCameraObjectInterfaceParameterGraphNode : public SObjectTreeGraphNode`  
_L12-34_
- inherits: `SObjectTreeGraphNode`
- desc: Custom graph editor node widget for a camera rig parameter getter node.
- L16 _public function_ `SLATE_BEGIN_ARGS(SCameraObjectInterfaceParameterGraphNode) : _GraphNode(nullptr)`
- L19 _public prototype_ `SLATE_ARGUMENT(UCameraObjectInterfaceParameterGraphNode*, GraphNode) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L27 _protected prototype_ `virtual void UpdateGraphNode() override;` — SGraphNode interface.
- L28 _protected prototype_ `virtual const FSlateBrush* GetShadowBrush(bool bSelected) const override;`
- L29 _protected prototype_ `virtual TSharedPtr<SGraphPin> CreatePinWidget(UEdGraphPin* InPin) const override;`
- L33 _private prototype_ `FText GetInterfaceParameterName() const;`

### `Plugins/Cameras/GameplayCameras/Source/GameplayCamerasEditor/Public/Editors/SCameraObjectInterfaceParametersPanel.h` (Public)


#### class `UE::Cameras::SCameraObjectInterfaceParametersPanel`  
`class SCameraObjectInterfaceParametersPanel : public SCompoundWidget , public ICameraObjectEventHandler`  
_L26-110_
- inherits: `SCompoundWidget,ICameraObjectEventHandler`
- desc: The overall interface parameters panel, showing two sub-panels, one for blendable parameters, and one for data parameters.
- L32 _public member_ `static const FName ParameterTypeColumn;`
- L33 _public member_ `static const FName ParameterNameColumn;`
- L37 _public function_ `SLATE_BEGIN_ARGS(SCameraObjectInterfaceParametersPanel)`
- L39 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& Args, FCameraObjectInterfaceParametersToolkit* OwnerToolkit);`
- L44 _public prototype_ `void RequestListRefresh();` — Refresh the lists of parameters.
- L47 _public prototype_ `void RenameSelectedParameter();` — Rename the selected parameter in the focused panel.
- L50 _public prototype_ `void DeleteSelectedParameter();` — Delete the selected parameter in the focused panel.
- L55 _protected prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;` — SWidget interface.
- L58 _protected prototype_ `virtual void OnCameraObjectInterfaceChanged() override;` — ICameraObjectEventHandler interface.
- L62 _private prototype_ `TSharedRef<ITableRow> OnGenerateBlendableParameterRow(TObjectPtr<UCameraObjectInterfaceBlendableParameter> Item, const TSharedRef<STableViewBase>& OwnerTable);`
- L63 _private prototype_ `TSharedRef<ITableRow> OnGenerateDataParameterRow(TObjectPtr<UCameraObjectInterfaceDataParameter> Item, const TSharedRef<STableViewBase>& OwnerTable);`
- L65 _private prototype_ `void OnBlendableSelectionChanged(TObjectPtr<UCameraObjectInterfaceBlendableParameter> Item, ESelectInfo::Type Type);`
- L66 _private prototype_ `void OnDataParameterSelectionChanged(TObjectPtr<UCameraObjectInterfaceDataParameter> Item, ESelectInfo::Type Type);`
- L68 _private prototype_ `TSharedPtr<SWidget> OnBlendableParameterContextMenuOpening();`
- L69 _private prototype_ `TSharedPtr<SWidget> OnDataParameterContextMenuOpening();`
- L71 _private prototype_ `void OnSearchInterfaceParameter(TObjectPtr<UCameraObjectInterfaceParameterBase> Item);`
- L74 _private prototype_ `template<typename ItemType> TSharedPtr<SWidget> OnInterfaceParameterContextMenuOpening( TSharedPtr<SListView<TObjectPtr<ItemType>>> ListView, TObjectPtr<ItemType> Item);`
- L77 _private prototype_ `template<typename ItemType> void OnRenameInterfaceParameter( TSharedPtr<SListView<TObjectPtr<ItemType>>> ListView, TObjectPtr<ItemType> Item);`
- L80 _private prototype_ `template<typename ItemType> void OnDeleteInterfaceParameter( TSharedPtr<SListView<TObjectPtr<ItemType>>> ListView, TObjectPtr<ItemType> Item);`
- L84 _private prototype_ `template<typename ItemType> void OnRenameSelectedInterfaceParameter(TSharedPtr<SListView<TObjectPtr<ItemType>>> ListView);`
- L86 _private prototype_ `template<typename ItemType> void OnDeleteSelectedInterfaceParameter(TSharedPtr<SListView<TObjectPtr<ItemType>>> ListView);`
- L88 _private prototype_ `FReply OnAddBlendableParameter();`
- L89 _private prototype_ `FReply OnAddDataParameter();`
- L91 _private prototype_ `void OnRenameSelectedBlendableParameter();`
- L92 _private prototype_ `void OnRenameSelectedDataParameter();`
- L94 _private prototype_ `FReply OnDeleteSelectedBlendableParameter();`
- L95 _private prototype_ `FReply OnDeleteSelectedDataParameter();`
- L97 _private prototype_ `FString GetNewParameterName() const;`
- L101 _private member_ `UBaseCameraObject* CameraObject = nullptr;`
- L102 _private member_ `FCameraObjectInterfaceParametersToolkit* Toolkit = nullptr;`
- L104 _private member_ `TCameraEventHandler<ICameraObjectEventHandler> EventHandler;`
- L106 _private member_ `TSharedPtr<SListView<TObjectPtr<UCameraObjectInterfaceBlendableParameter>>> BlendableParametersListView;`
- L107 _private member_ `TSharedPtr<SListView<TObjectPtr<UCameraObjectInterfaceDataParameter>>> DataParametersListView;`
- L109 _private member_ `bool bListRefreshRequested = false;`

#### class `UEdGraphSchema_CameraNodeK2`  
`class UEdGraphSchema_CameraNodeK2 : public UEdGraphSchema_K2`  
_L116-130_
- reflection: `UCLASS(MinimalAPI, Hidden)`
- inherits: `UEdGraphSchema_K2`
- desc: Dummy Blueprint schema used only for getting proper icons and colors for parameter types.
- L122 _public function_ `virtual bool SupportsPinTypeContainer(TWeakPtr<const FEdGraphSchemaAction> SchemaAction, const FEdGraphPinType& PinType, const EPinContainerType& ContainerType) const`

#### Free symbols / members of external scopes

- L17 _namespace_ `namespace UE`
- L17 _namespace_ `namespace Cameras` (scope `UE`)

### `Plugins/Cameras/GameplayCameras/Source/GameplayCamerasEditor/Public/Editors/SCameraRigAssetEditor.h` (Public)


#### enum `UE::Cameras::ECameraRigAssetEditorMode`  
`enum class ECameraRigAssetEditorMode`  
_L25-31_
- desc: The current mode of the camera rig asset editor.
- L28 _public enumerator_ `NodeGraph` — Show the node hierarchy editor.
- L30 _public enumerator_ `TransitionGraph` — Show the transition editor.

#### class `UE::Cameras::SCameraRigAssetEditor`  
`class SCameraRigAssetEditor : public SCompoundWidget`  
_L39-139_
- inherits: `SCompoundWidget`
- desc: A camera rig asset editor. This implements only the dual-graph editor, for the node hierarchy and transitions. The rest of the UI such as the details view or the toolbox aren't included here.
- L44 _public function_ `SLATE_BEGIN_ARGS(SCameraRigAssetEditor)`
- L47 _public prototype_ `SLATE_ARGUMENT(TObjectPtr<UCameraRigAsset>, CameraRigAsset) SLATE_ARGUMENT(TSharedPtr<IDetailsView>, DetailsView) SLATE_ARGUMENT(TWeakPtr<FAssetEditorToolkit>, AssetEditorToolkit) SLATE_END_ARGS() void Construct(const FArguments& InArgs);` — The camera rig asset to edit.
- L55 _public prototype_ `~SCameraRigAssetEditor();`
- L57 _public prototype_ `void SetCameraRigAsset(UCameraRigAsset* InCameraRig);`
- L62 _public prototype_ `ECameraRigAssetEditorMode GetEditorMode() const;` — Gets the current editor mode.
- L64 _public prototype_ `bool IsEditorMode(ECameraRigAssetEditorMode InMode) const;` — Checks if the editor is in the current mode.
- L66 _public prototype_ `void SetEditorMode(ECameraRigAssetEditorMode InMode);` — Changes the editor's current mode.
- L69 _public prototype_ `void GetGraphs(TArray<UEdGraph*>& OutGraphs) const;` — Gets both the node hierarchy and transition graphs.
- L72 _public prototype_ `UEdGraph* GetFocusedGraph() const;` — Gets the graph for the current mode.
- L74 _public prototype_ `const FObjectTreeGraphConfig& GetFocusedGraphConfig() const;` — Gets the graph configuration for the current mode.
- L77 _public prototype_ `void FocusHome();` — Focuses the current graph to the root object node.
- L79 _public prototype_ `bool JumpToNode(UEdGraphNode* InNode, FName InPinName = NAME_None);` — Jumps to a node.
- L81 _public prototype_ `bool FindAndJumpToObjectNode(UObject* InObject);` — Finds a node for the given object and, if so, jumps to it.
- L84 _public prototype_ `FDelegateHandle AddOnAnyGraphChanged(FOnGraphChanged::FDelegate InAddDelegate);` — Adds a callback that will be invoked when a graph editor is changed.
- L86 _public prototype_ `void RemoveOnAnyGraphChanged(FDelegateHandle InDelegateHandle);` — Removes a previous added callback.
- L88 _public prototype_ `void RemoveOnAnyGraphChanged(FDelegateUserObjectConst InUserObject);` — Removes a previous added callback.
- L92 _protected prototype_ `void CreateGraphEditors();`
- L93 _protected prototype_ `void CreateNodeGraphEditor();`
- L94 _protected prototype_ `void CreateTransitionGraphEditor();`
- L95 _protected prototype_ `void DiscardGraphEditors();`
- L97 _protected prototype_ `void SetEditorModeImpl(ECameraRigAssetEditorMode InMode, bool bForceSet);`
- L99 _protected prototype_ `void OnGraphChanged(const FEdGraphEditAction& InEditAction);`
- L101 _protected prototype_ `FText GetCameraRigAssetName(UObjectTreeGraph* ForGraph) const;`
- L102 _protected prototype_ `bool IsGraphEditorEnabled() const;`
- L104 _protected prototype_ `bool FindAndJumpToObjectNode(UObject* InObject, ECameraRigAssetEditorMode InEditorMode);`
- L109 _private member_ `TObjectPtr<UCameraRigAsset> CameraRigAsset;` — The asset being edited
- L112 _private member_ `TSharedPtr<IDetailsView> DetailsView;` — Reference to the details view
- L115 _private member_ `TWeakPtr<FAssetEditorToolkit> AssetEditorToolkit;` — Reference to the owning asset editor
- L118 _private member_ `TObjectPtr<UObjectTreeGraph> NodeGraph;` — The node hierarchy graph
- L120 _private member_ `TSharedPtr<SObjectTreeGraphEditor> NodeGraphEditor;` — The node hierarchy graph editor
- L123 _private member_ `TObjectPtr<UObjectTreeGraph> TransitionGraph;` — The transition graph
- L125 _private member_ `TSharedPtr<SObjectTreeGraphEditor> TransitionGraphEditor;` — The transition graph editor
- L128 _private member_ `TSharedPtr<SBox> BoxPanel;` — Box panel holding either the node hierarchy or transition graph editor
- L131 _private member_ `ECameraRigAssetEditorMode CurrentMode;` — The mode for the currently shown graph editor
- L134 _private member_ `FDelegateHandle NodeGraphChangedHandle;` — Handles for listening to changes in the graphs editors
- L135 _private member_ `FDelegateHandle TransitionGraphChangedHandle;`
- L138 _private member_ `FOnGraphChanged OnAnyGraphChanged;` — Forwarding delegate for changes in any of the graphs

#### Free symbols / members of external scopes

- L21 _namespace_ `namespace UE`
- L21 _namespace_ `namespace Cameras` (scope `UE`)

### `Plugins/Cameras/GameplayCameras/Source/GameplayCamerasEditor/Public/Editors/SCameraRigTransitionEditor.h` (Public)


#### class `UE::Cameras::SCameraRigTransitionEditor`  
`class SCameraRigTransitionEditor : public SCompoundWidget`  
_L30-114_
- inherits: `SCompoundWidget`
- desc: A graph editor for any object that has enter and exit transitions.
- L34 _public function_ `SLATE_BEGIN_ARGS(SCameraRigTransitionEditor)`
- L37 _public prototype_ `SLATE_ARGUMENT(UObject*, TransitionOwner) SLATE_ARGUMENT(TSubclassOf<UCameraRigTransitionGraphSchemaBase>, TransitionGraphSchemaClass) SLATE_ARGUMENT(TSharedPtr<IDetailsView>, DetailsView) SLATE_ARGUMENT(TWeakPtr<FAssetEditorToolkit>, AssetEditorToolkit) SLATE_ATTRIBUTE(FGraphAppearanceInfo, TransitionGraphEditorAppearance) SLATE_END_ARGS() void Construct(const FArguments& InArgs);` — The object owning the transitions.
- L49 _public prototype_ `~SCameraRigTransitionEditor();`
- L52 _public prototype_ `void SetTransitionOwner(UObject* InTransitionOwner);` — Sets the asset being edited for transitions.
- L57 _public prototype_ `UEdGraph* GetTransitionGraph() const;` — Gets the transition graph.
- L59 _public prototype_ `const FObjectTreeGraphConfig& GetTransitionGraphConfig() const;` — Gets the transition graph configuration.
- L62 _public prototype_ `void FocusHome();` — Focuses the current graph to the root object node.
- L64 _public prototype_ `void JumpToNode(UEdGraphNode* InGraphNode, FName InPinName = NAME_None);` — Jumps the current graph to the given node.
- L66 _public prototype_ `bool FindAndJumpToObjectNode(UObject* InObject);` — Finds a node for the given object and, if so, jumps to it.
- L69 _public prototype_ `FDelegateHandle AddOnGraphChanged(FOnGraphChanged::FDelegate InAddDelegate);` — Adds a callback that will be invoked when the editor is changed.
- L71 _public prototype_ `void RemoveOnGraphChanged(FDelegateHandle InDelegateHandle);` — Removes a previous added callback.
- L73 _public prototype_ `void RemoveOnGraphChanged(FDelegateUserObjectConst InUserObject);` — Removes a previous added callback.
- L77 _protected prototype_ `void CreateTransitionGraphEditor();`
- L78 _protected prototype_ `void DiscardTransitionGraphEditor();`
- L80 _protected prototype_ `void OnGraphChanged(const FEdGraphEditAction& InEditAction);`
- L82 _protected prototype_ `FText GetTransitionOwnerName() const;`
- L87 _private member_ `UObject* TransitionOwner;` — The asset being edited.
- L90 _private member_ `TSubclassOf<UCameraRigTransitionGraphSchemaBase> TransitionGraphSchemaClass;` — The graph schema class to use.
- L93 _private member_ `TSharedPtr<IDetailsView> DetailsView;` — The details view for this editor.
- L96 _private member_ `TWeakPtr<FAssetEditorToolkit> AssetEditorToolkit;` — The owning toolkit.
- L99 _private member_ `TObjectPtr<UObjectTreeGraph> TransitionGraph;` — The transition graph.
- L101 _private member_ `TSharedPtr<SObjectTreeGraphEditor> TransitionGraphEditor;` — The transition graph editor.
- L104 _private member_ `TAttribute<FGraphAppearanceInfo> TransitionGraphEditorAppearance;` — Appearance info for the transition graph editor.
- L107 _private member_ `TSharedPtr<SBox> BoxPanel;` — The panel holding the graph editor.
- L110 _private member_ `FDelegateHandle TransitionGraphChangedHandle;` — Handle for listening to changes in the graph editor.
- L113 _private member_ `FOnGraphChanged OnTransitionGraphChanged;` — Forwarding delegate for changes in the graph editor.

#### Free symbols / members of external scopes

- L24 _namespace_ `namespace UE`
- L24 _namespace_ `namespace Cameras` (scope `UE`)

### `Plugins/Cameras/GameplayCameras/Source/GameplayCamerasEditor/Public/Editors/SCameraVariableCollectionEditor.h` (Public)


#### class `UE::Cameras::SCameraVariableCollectionEditor`  
`class SCameraVariableCollectionEditor : public SCompoundWidget`  
_L27-102_
- inherits: `SCompoundWidget`
- desc: An editor widget for a camera variable collection.
- L31 _public function_ `SLATE_BEGIN_ARGS(SCameraVariableCollectionEditor)`
- L34 _public prototype_ `SLATE_ARGUMENT(TObjectPtr<UCameraVariableCollection>, VariableCollection) SLATE_ARGUMENT(TWeakPtr<IDetailsView>, DetailsView) SLATE_ARGUMENT(TWeakPtr<FAssetEditorToolkit>, AssetEditorToolkit) SLATE_ARGUMENT(TSharedPtr<FUICommandList>, AdditionalCommands) SLATE_END_ARGS() void Construct(const FArguments& InArgs);` — The camera variable collection to edit.
- L44 _public prototype_ `~SCameraVariableCollectionEditor();`
- L49 _public prototype_ `void GetSelectedVariables(TArray<UCameraVariableAsset*>& OutSelection) const;` — Gets the selected variables in the list view.
- L52 _public prototype_ `void SelectVariable(UCameraVariableAsset* InItem);` — Selects the given variable if it is in the list view.
- L55 _public prototype_ `void RequestRenameVariable(UCameraVariableAsset* InItem, FSimpleDelegate InOnRenamedItem);` — Enter editing mode for the given variable's name.
- L58 _public prototype_ `void RequestRenameSelectedVariable();` — Enter editing mode for the first currently selected variable's name.
- L61 _public prototype_ `void RequestListRefresh();` — Requests that the list view be refreshed by the next tick.
- L66 _protected prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;`
- L70 _private prototype_ `void UpdateFilteredItemSource();`
- L71 _private prototype_ `void SetDetailsViewObject(UObject* InObject) const;`
- L73 _private prototype_ `TSharedRef<ITableRow> OnListGenerateRow(UCameraVariableAsset* Item, const TSharedRef<STableViewBase>& OwnerTable);`
- L74 _private prototype_ `void OnListSectionChanged(UCameraVariableAsset* Item, ESelectInfo::Type SelectInfo) const;`
- L75 _private prototype_ `void OnListItemScrolledIntoView(UCameraVariableAsset* Item, const TSharedPtr<ITableRow>& ItemWidget);`
- L76 _private prototype_ `TSharedPtr<SWidget> OnListContextMenuOpening();`
- L78 _private prototype_ `void GetEntryStrings(const UCameraVariableAsset* InItem, TArray<FString>& OutStrings);`
- L79 _private prototype_ `void OnSearchTextChanged(const FText& InFilterText);`
- L80 _private prototype_ `void OnSearchTextCommitted(const FText& InFilterText, ETextCommit::Type InCommitType);`
- L81 _private prototype_ `FText GetHighlightText() const;`
- L85 _private member_ `TObjectPtr<UCameraVariableCollection> VariableCollection;`
- L87 _private member_ `TWeakPtr<IDetailsView> WeakDetailsView;`
- L89 _private member_ `TSharedPtr<FUICommandList> CommandList;`
- L91 _private member_ `TSharedPtr<SListView<UCameraVariableAsset*>> ListView;`
- L93 _private member_ `TArray<UCameraVariableAsset*> FilteredItemSource;`
- L95 _private typedef_ `using FEntryTextFilter = TTextFilter<const UCameraVariableAsset*>;`
- L96 _private member_ `TSharedPtr<FEntryTextFilter> SearchTextFilter;`
- L97 _private member_ `TSharedPtr<SSearchBox> SearchBox;`
- L99 _private member_ `bool bUpdateFilteredItemSource = false;`
- L100 _private member_ `bool bDeferredRequestRenameItem = false;`
- L101 _private member_ `FSimpleDelegate OnDeferredRenamedItem;`

#### Free symbols / members of external scopes

- L21 _namespace_ `namespace UE`
- L21 _namespace_ `namespace Cameras` (scope `UE`)

### `Plugins/Cameras/GameplayCameras/Source/GameplayCamerasEditor/Public/Editors/SCameraVariableNameGraphPin.h` (Public)


#### class `UE::Cameras::SCameraVariableNameGraphPin`  
`class SCameraVariableNameGraphPin : public SGraphPin`  
_L19-60_
- inherits: `SGraphPin`
- desc: A custom widget for a graph editor pin that shows a camera rig picker dialog.
- L23 _public function_ `SLATE_BEGIN_ARGS(SCameraVariableNameGraphPin)`
- L25 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj);`
- L32 _protected prototype_ `virtual TSharedRef<SWidget> GetDefaultValueWidget() override;` — SGraphPin interface.
- L33 _protected prototype_ `virtual bool DoesWidgetHandleSettingEditingEnabled() const override;`
- L37 _private member_ `static constexpr float ActiveComboAlpha = 1.f;`
- L38 _private member_ `static constexpr float InactiveComboAlpha = 0.6f;`
- L39 _private member_ `static constexpr float ActivePinForegroundAlpha = 1.f;`
- L40 _private member_ `static constexpr float InactivePinForegroundAlpha = 0.15f;`
- L41 _private member_ `static constexpr float ActivePinBackgroundAlpha = 0.8f;`
- L42 _private member_ `static constexpr float InactivePinBackgroundAlpha = 0.4f;`
- L44 _private prototype_ `FSlateColor OnGetComboForeground() const;`
- L45 _private prototype_ `FSlateColor OnGetWidgetForeground() const;`
- L46 _private prototype_ `FSlateColor OnGetWidgetBackground() const;`
- L48 _private prototype_ `FText OnGetSelectedCameraVariableName() const;`
- L49 _private prototype_ `FText OnGetCameraVariablePickerToolTipText() const;`
- L50 _private prototype_ `TSharedRef<SWidget> OnBuildCameraVariablePicker() const;`
- L51 _private prototype_ `void OnPickerAssetSelected(UCameraVariableAsset* SelectedItem) const;`
- L53 _private prototype_ `FReply OnResetButtonClicked();`
- L55 _private prototype_ `void SetCameraVariable(UCameraVariableAsset* SelectedCameraVariable) const;`
- L59 _private member_ `TSharedPtr<SComboButton> CameraVariablePickerButton;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace Cameras` (scope `UE`)

### `Plugins/Cameras/GameplayCameras/Source/GameplayCamerasEditor/Public/Editors/SFindInObjectTreeGraph.h` (Public)


#### struct `FFindInObjectTreeGraphSource`  
`struct FFindInObjectTreeGraphSource`  
_L22-26_
- desc: Struct describing one source of possible results for a search.
- L25 _public member_ `UEdGraph* Graph = nullptr;` — The graph where results are to be found.

#### struct `FFindInObjectTreeGraphResult`  
`struct FFindInObjectTreeGraphResult`  
_L31-68_
- desc: Structure for a search result inside an object tree graph.
- L36 _public member_ `TWeakPtr<FFindInObjectTreeGraphResult> Parent;` — Parent result.
- L38 _public member_ `TArray<TSharedPtr<FFindInObjectTreeGraphResult>> Children;` — Children results.
- L41 _public member_ `FText CustomText;` — Custom text for this result.
- L43 _public member_ `TWeakObjectPtr<UEdGraphNode> WeakNode;` — The node that this result refers to.
- L45 _public member_ `FName PinName;` — The pin name that this result refers to.
- L50 _public prototype_ `FFindInObjectTreeGraphResult(const FText& InCustomText);` — Creates a new result with a custom text.
- L52 _public prototype_ `FFindInObjectTreeGraphResult( TSharedPtr<FFindInObjectTreeGraphResult>& InParent, UEdGraphNode* InNode, FName PinName = NAME_None);` — Creates a new result referring to an object, under a parent result.
- L58 _public prototype_ `TSharedRef<SWidget> GetIcon() const;` — Gets the icon for this result.
- L60 _public prototype_ `FText GetCategory() const;` — Gets the category for this result.
- L62 _public prototype_ `FText GetText() const;` — Gets the display text for this result.
- L64 _public prototype_ `FText GetCommentText() const;` — Gets the comment text for this result.
- L67 _public prototype_ `FReply OnClick(TSharedRef<SFindInObjectTreeGraph> FindInObjectTreeGraph);` — Go to the graph node, pin, etc.

#### class `SFindInObjectTreeGraph`  
`class SFindInObjectTreeGraph : public SCompoundWidget`  
_L73-125_
- inherits: `SCompoundWidget`
- desc: A search panel to find things in one or more object tree graphs.
- L77 _public prototype_ `DECLARE_DELEGATE_OneParam(FOnGetGraphsToSearch, TArray<FFindInObjectTreeGraphSource>&);`
- L78 _public prototype_ `DECLARE_DELEGATE_TwoParams(FOnJumpToNodeRequested, UEdGraphNode*, FName);`
- L80 _public function_ `SLATE_BEGIN_ARGS(SFindInObjectTreeGraph)`
- L83 _public prototype_ `SLATE_EVENT(FOnGetGraphsToSearch, OnGetGraphsToSearch) SLATE_EVENT(FOnJumpToNodeRequested, OnJumpToNodeRequested) SLATE_END_ARGS() void Construct(const FArguments& InArgs);` — The callback to get the graphs to search.
- L90 _public prototype_ `void FocusSearchEditBox();`
- L92 _public prototype_ `void Search(const FString& InSearchQuery);`
- L96 _protected typedef_ `typedef TSharedPtr<FFindInObjectTreeGraphResult> FResultPtr;`
- L97 _protected typedef_ `typedef STreeView<FResultPtr> SResultTreeView;`
- L99 _protected prototype_ `void OnSearchTextChanged(const FText& Text);`
- L100 _protected prototype_ `void OnSearchTextCommitted(const FText& Text, ETextCommit::Type CommitType);`
- L102 _protected prototype_ `TSharedRef<ITableRow> OnResultTreeViewGenerateRow(FResultPtr InItem, const TSharedRef<STableViewBase>& OwnerTable);`
- L103 _protected prototype_ `void OnResultTreeViewGetChildren(FResultPtr InItem, TArray<FResultPtr>& OutChildren);`
- L104 _protected prototype_ `void OnResultTreeViewSelectionChanged(FResultPtr Item, ESelectInfo::Type SelectInfo);`
- L105 _protected prototype_ `void OnResultTreeViewMouseButtonDoubleClick(FResultPtr Item);`
- L109 _protected prototype_ `void StartSearch();`
- L113 _protected member_ `FOnGetGraphsToSearch OnGetGraphsToSearch;`
- L114 _protected member_ `FOnJumpToNodeRequested OnJumpToNodeRequested;`
- L116 _protected member_ `TSharedPtr<SSearchBox> SearchBox;`
- L117 _protected member_ `TSharedPtr<SResultTreeView> ResultTreeView;`
- L119 _protected member_ `FString SearchQuery;`
- L120 _protected member_ `TArray<FResultPtr> Results;`
- L122 _protected member_ `FText HighlightText;`

#### Free symbols / members of external scopes

- L77 _delegate_ `DECLARE_DELEGATE_OneParam(FOnGetGraphsToSearch, TArray<FFindInObjectTreeGraphSource>&);`
- L78 _delegate_ `DECLARE_DELEGATE_TwoParams(FOnJumpToNodeRequested, UEdGraphNode*, FName);`

### `Plugins/Cameras/GameplayCameras/Source/GameplayCamerasEditor/Public/Editors/SObjectTreeGraphCommentNode.h` (Public)


#### class `SObjectTreeGraphCommentNode`  
`class SObjectTreeGraphCommentNode : public SGraphNodeComment`  
_L13-35_
- inherits: `SGraphNodeComment`
- desc: The widget for object tree graph comment nodes.
- L17 _public function_ `SLATE_BEGIN_ARGS(SObjectTreeGraphCommentNode) : _GraphNode(nullptr)`
- L20 _public prototype_ `SLATE_ARGUMENT(UObjectTreeGraphCommentNode*, GraphNode) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L25 _public function_ `UObjectTreeGraphCommentNode* GetObjectGraphNode() const`
- L30 _public prototype_ `virtual void MoveTo(const FSlateCompatVector2f& NewPosition, FNodeSet& NodeFilter, bool bMarkDirty=true) override;` — SNodePanel::SNode interface.
- L34 _protected member_ `UObjectTreeGraphCommentNode* ObjectGraphNode;`

### `Plugins/Cameras/GameplayCameras/Source/GameplayCamerasEditor/Public/Editors/SObjectTreeGraphEditor.h` (Public)


#### class `SObjectTreeGraphEditor`  
`class SObjectTreeGraphEditor : public SCompoundWidget , public FEditorUndoClient`  
_L17-129_
- inherits: `SCompoundWidget,FEditorUndoClient`
- desc: A graph editor for an object tree graph.
- L23 _public prototype_ `static TSharedPtr<SObjectTreeGraphEditor> FindGraphEditor(UObjectTreeGraph* InGraph);`
- L24 _public prototype_ `static void OnBeginEditingGraph(UObjectTreeGraph* InGraph, TSharedRef<SObjectTreeGraphEditor> InGraphEditor);`
- L25 _public prototype_ `static void OnEndEditingGraph(UObjectTreeGraph* InGraph, TSharedRef<SObjectTreeGraphEditor> InGraphEditor);`
- L29 _private member_ `static TMap<UObjectTreeGraph*, TSharedPtr<SObjectTreeGraphEditor>> ActiveGraphEditors;`
- L33 _public function_ `SLATE_BEGIN_ARGS(SObjectTreeGraphEditor)`
- L36 _public prototype_ `SLATE_ARGUMENT(TSharedPtr<FUICommandList>, AdditionalCommands) SLATE_ARGUMENT(TSharedPtr<SWidget>, GraphTitleBar) SLATE_ARGUMENT(TSharedPtr<IDetailsView>, DetailsView) SLATE_ARGUMENT(UObjectTreeGraph*, GraphToEdit) SLATE_ARGUMENT(TWeakPtr<FAssetEditorToolkit>, AssetEditorToolkit) SLATE_ATTRIBUTE(FGraphAppearanceInfo, Appearance) SLATE_ATTRIBUTE(FText, GraphTitle) SLATE_END_ARGS() void Construct(const FArguments& InArgs);` — Any additional command mappings to use in the graph editor.
- L52 _public prototype_ `~SObjectTreeGraphEditor();`
- L54 _public prototype_ `void RegisterEditor();`
- L55 _public prototype_ `void UnregisterEditor();`
- L57 _public prototype_ `void JumpToNode(UEdGraphNode* InNode, FName InPinName = NAME_None);`
- L58 _public prototype_ `bool FindAndJumpToObjectNode(UObject* InObject, FName InPropertyName = NAME_None);`
- L60 _public prototype_ `void ResyncDetailsView();`
- L62 _public function_ `TSharedPtr<SGraphEditor> GetGraphEditor()`
- L67 _protected prototype_ `virtual FReply OnDragOver(const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent) override;` — SWidget interface.
- L68 _protected prototype_ `virtual FReply OnDrop(const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent) override;`
- L71 _protected prototype_ `virtual void PostUndo(bool bSuccess) override;` — FEditorUndoClient interface.
- L72 _protected prototype_ `virtual void PostRedo(bool bSuccess) override;`
- L76 _protected prototype_ `void InitializeBuiltInCommands();`
- L78 _protected prototype_ `void OnGraphSelectionChanged(const FGraphPanelSelectionSet& SelectionSet);`
- L79 _protected prototype_ `void OnNodeTextCommitted(const FText& InText, ETextCommit::Type InCommitType, UEdGraphNode* InEditedNode);`
- L80 _protected prototype_ `void OnNodeDoubleClicked(UEdGraphNode* InClickedNode);`
- L81 _protected prototype_ `void OnDoubleClicked();`
- L83 _protected prototype_ `FString ExportNodesToText(const FGraphPanelSelectionSet& Nodes, bool bOnlyCanDuplicateNodes, bool bOnlyCanDeleteNodes);`
- L84 _protected prototype_ `void ImportNodesFromText(const FSlateCompatVector2f& Location, const FString& TextToImport);`
- L85 _protected prototype_ `bool CanImportNodesFromText(const FString& TextToImport);`
- L86 _protected prototype_ `void DeleteNodes(TArrayView<UEdGraphNode*> NodesToDelete);`
- L88 _protected prototype_ `void SelectAllNodes();`
- L89 _protected prototype_ `bool CanSelectAllNodes();`
- L91 _protected prototype_ `void DeleteSelectedNodes();`
- L92 _protected prototype_ `bool CanDeleteSelectedNodes();`
- L94 _protected prototype_ `void CopySelectedNodes();`
- L95 _protected prototype_ `bool CanCopySelectedNodes();`
- L97 _protected prototype_ `void CutSelectedNodes();`
- L98 _protected prototype_ `bool CanCutSelectedNodes();`
- L100 _protected prototype_ `void PasteNodes();`
- L101 _protected prototype_ `bool CanPasteNodes();`
- L103 _protected prototype_ `void DuplicateNodes();`
- L104 _protected prototype_ `bool CanDuplicateNodes();`
- L106 _protected prototype_ `void OnRenameNode();`
- L107 _protected prototype_ `bool CanRenameNode();`
- L109 _protected prototype_ `void OnAlignTop();`
- L110 _protected prototype_ `void OnAlignMiddle();`
- L111 _protected prototype_ `void OnAlignBottom();`
- L112 _protected prototype_ `void OnAlignLeft();`
- L113 _protected prototype_ `void OnAlignCenter();`
- L114 _protected prototype_ `void OnAlignRight();`
- L116 _protected prototype_ `void OnStraightenConnections();`
- L117 _protected prototype_ `void OnDistributeNodesHorizontally();`
- L118 _protected prototype_ `void OnDistributeNodesVertically();`
- L120 _protected prototype_ `void OnInsertArrayItemPinBefore();`
- L121 _protected prototype_ `void OnInsertArrayItemPinAfter();`
- L122 _protected prototype_ `void OnRemoveArrayItemPin();`
- L126 _protected member_ `TSharedPtr<SGraphEditor> GraphEditor;`
- L127 _protected member_ `TSharedPtr<IDetailsView> DetailsView;`
- L128 _protected member_ `TSharedPtr<FUICommandList> BuiltInCommands;`

### `Plugins/Cameras/GameplayCameras/Source/GameplayCamerasEditor/Public/Editors/SObjectTreeGraphNode.h` (Public)


#### class `SObjectTreeGraphNode`  
`class SObjectTreeGraphNode : public SGraphNode`  
_L15-55_
- inherits: `SGraphNode`
- desc: The widget used by default for object tree graph nodes.
- L19 _public function_ `SLATE_BEGIN_ARGS(SObjectTreeGraphNode) : _GraphNode(nullptr)`
- L22 _public prototype_ `SLATE_ARGUMENT(UObjectTreeGraphNode*, GraphNode) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L27 _public function_ `UObjectTreeGraphNode* GetObjectGraphNode() const`
- L32 _public prototype_ `virtual const FSlateBrush* GetShadowBrush(bool bSelected) const override;` — SGraphNode interface.
- L33 _public prototype_ `virtual void CreateInputSideAddButton(TSharedPtr<SVerticalBox> InputBox) override;`
- L34 _public prototype_ `virtual void CreateOutputSideAddButton(TSharedPtr<SVerticalBox> OutputBox) override;`
- L35 _public prototype_ `virtual TSharedPtr<SGraphPin> CreatePinWidget(UEdGraphPin* InPin) const override;`
- L36 _public prototype_ `virtual void AddPin(const TSharedRef<SGraphPin>& PinToAdd) override;`
- L37 _public prototype_ `virtual void SetDefaultTitleAreaWidget(TSharedRef<SOverlay> DefaultTitleAreaWidget) override;`
- L38 _public prototype_ `virtual const FSlateBrush* GetNodeBodyBrush() const override;`
- L41 _public prototype_ `virtual void MoveTo(const FSlateCompatVector2f& NewPosition, FNodeSet& NodeFilter, bool bMarkDirty=true) override;` — SNodePanel::SNode interface.
- L45 _protected prototype_ `void MakeAllAddArrayPropertyPinButtons(TSharedPtr<SVerticalBox> Box, EEdGraphPinDirection Direction);`
- L46 _protected prototype_ `TSharedRef<SWidget> MakeAddArrayPropertyPinButton(FArrayProperty* ArrayProperty);`
- L48 _protected prototype_ `FReply OnAddArrayPropertyPin(FArrayProperty* ArrayProperty);`
- L52 _protected member_ `UObjectTreeGraphNode* ObjectGraphNode;`
- L54 _protected member_ `bool bHasAddPinButtons = false;`

### `Plugins/Cameras/GameplayCameras/Source/GameplayCamerasEditor/Public/Editors/SObjectTreeGraphTitleBar.h` (Public)


#### struct `FObjectTreeGraphInfo`  
`struct FObjectTreeGraphInfo`  
_L19-22_
- L21 _public member_ `FString GraphName;`

#### class `SObjectTreeGraphTitleBar`  
`class SObjectTreeGraphTitleBar : public SCompoundWidget`  
_L27-59_
- inherits: `SCompoundWidget`
- desc: The default object graph title bar used by the object tree graph editor.
- L30 _public function_ `SLATE_BEGIN_ARGS(SObjectTreeGraphTitleBar) : _Graph(nullptr)`
- L33 _public prototype_ `SLATE_ATTRIBUTE(FText, TitleText) SLATE_ARGUMENT(UEdGraph*, Graph) SLATE_ARGUMENT(const TArray<TSharedPtr<FObjectTreeGraphInfo>>*, GraphList) SLATE_ARGUMENT(TSharedPtr<SWidget>, HistoryNavigationWidget) SLATE_EVENT(FObjectTreeGraphEvent, OnBreadcrumbClicked) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L44 _protected prototype_ `TSharedRef<ITableRow> GenerateGraphInfoRow(TSharedPtr<FObjectTreeGraphInfo> Item, const TSharedRef<STableViewBase>& OwnerTable);`
- L46 _protected prototype_ `void OnBreadcrumbClickedImpl(UEdGraph* const& Item);`
- L47 _protected prototype_ `void RebuildBreadcrumbTrail();`
- L48 _protected prototype_ `static FText GetTitleForOneCrumb(const UEdGraph* BaseGraph, const UEdGraph* CurGraph);`
- L52 _protected member_ `UEdGraph* Graph;`
- L54 _protected member_ `TSharedPtr<SListView<TSharedPtr<FObjectTreeGraphInfo>>> GraphListView;`
- L56 _protected member_ `TSharedPtr<SBreadcrumbTrail<UEdGraph*>> BreadcrumbTrail;`
- L57 _protected member_ `TSharedPtr<SScrollBox> BreadcrumbTrailScrollBox;`
- L58 _protected member_ `FObjectTreeGraphEvent OnBreadcrumbClicked;`

#### Free symbols / members of external scopes

- L17 _delegate_ `DECLARE_DELEGATE_OneParam(FObjectTreeGraphEvent, UEdGraph*);`
- L17 _prototype_ `DECLARE_DELEGATE_OneParam(FObjectTreeGraphEvent, UEdGraph*);`

### `Plugins/Cameras/GameplayCameras/Source/GameplayCamerasEditor/Public/Editors/SObjectTreeGraphToolbox.h` (Public)


#### class `SObjectTreeGraphToolboxEntry`  
`class SObjectTreeGraphToolboxEntry : public SCompoundWidget`  
_L21-59_
- inherits: `SCompoundWidget`
- desc: A widget for an object tree graph toolbox entry, showing a specific instantiable object class that can be added to a graph.
- L25 _public function_ `SLATE_BEGIN_ARGS(SObjectTreeGraphToolboxEntry) : _ObjectClass(nullptr) , _GraphConfig(nullptr)`
- L30 _public prototype_ `SLATE_ARGUMENT(UClass*, ObjectClass) SLATE_ARGUMENT(const FObjectTreeGraphConfig*, GraphConfig) SLATE_ATTRIBUTE(FText, HighlightText) SLATE_END_ARGS() void Construct(const FArguments& InArgs);` — The object class represented by this entry.
- L39 _public function_ `UClass* GetObjectClass() const`
- L43 _protected prototype_ `virtual FReply OnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L44 _protected prototype_ `virtual FReply OnMouseButtonUp(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L45 _protected prototype_ `virtual FReply OnDragDetected(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L47 _protected prototype_ `const FSlateBrush* GetBorder() const;`
- L51 _private member_ `UClass* ObjectClass = nullptr;`
- L52 _private member_ `FText DisplayNameText;`
- L54 _private member_ `bool bIsPressed = false;`
- L56 _private member_ `const FSlateBrush* NormalImage = nullptr;`
- L57 _private member_ `const FSlateBrush* HoverImage = nullptr;`
- L58 _private member_ `const FSlateBrush* PressedImage = nullptr;`

#### class `SObjectTreeGraphToolbox`  
`class SObjectTreeGraphToolbox : public SCompoundWidget`  
_L65-115_
- inherits: `SCompoundWidget`
- desc: A toolbox widget that shows all the possible instantiable classes of objects for a given object tree graph.
- L69 _public function_ `SLATE_BEGIN_ARGS(SObjectTreeGraphToolbox)`
- L71 _public prototype_ `SLATE_ARGUMENT(FObjectTreeGraphConfig, GraphConfig) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L80 _public prototype_ `void SetGraphConfig(const FObjectTreeGraphConfig& InGraphConfig);` — Updates the toolbox to reflect the list of instantiable objects for the given graph configuration.
- L85 _protected prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;` — SWidget interface
- L89 _private prototype_ `void GetEntryStrings(const UClass* InItem, TArray<FString>& OutStrings);`
- L91 _private prototype_ `void UpdateItemSource();`
- L92 _private prototype_ `void UpdateFilteredItemSource();`
- L94 _private prototype_ `TSharedRef<ITableRow> OnGenerateItemRow(UClass* Item, const TSharedRef<STableViewBase>& OwnerTable);`
- L96 _private prototype_ `void OnSearchTextChanged(const FText& InFilterText);`
- L97 _private prototype_ `void OnSearchTextCommitted(const FText& InFilterText, ETextCommit::Type InCommitType);`
- L98 _private prototype_ `FText GetHighlightText() const;`
- L102 _private member_ `FObjectTreeGraphConfig GraphConfig;`
- L104 _private member_ `TArray<UClass*> ItemSource;`
- L105 _private member_ `TSharedPtr<SListView<UClass*>> ListView;`
- L107 _private typedef_ `using FEntryTextFilter = TTextFilter<const UClass*>;`
- L108 _private member_ `TSharedPtr<FEntryTextFilter> SearchTextFilter;`
- L109 _private member_ `TSharedPtr<SSearchBox> SearchBox;`
- L111 _private member_ `TArray<UClass*> FilteredItemSource;`
- L113 _private member_ `bool bUpdateItemSource = false;`
- L114 _private member_ `bool bUpdateFilteredItemSource = false;`

### `Plugins/Cameras/GameplayCameras/Source/GameplayCamerasEditor/Public/GameplayCamerasEditorSettings.h` (Public)


#### class `UGameplayCamerasEditorSettings`  
`class UGameplayCamerasEditorSettings : public UDeveloperSettings`  
_L15-64_
- reflection: `UCLASS(Config=EditorPerProjectUserSettings, MinimalAPI, meta=(DisplayName="Gameplay Cameras Editor"))`
- inherits: `UDeveloperSettings`
- L21 _public prototype_ `UGameplayCamerasEditorSettings(const FObjectInitializer& ObjectInitializer);`
- L27 _public member_ `FLinearColor CameraNodeTitleColor;` — `UPROPERTY(EditAnywhere, Config, Category=NodeTitleColors)` — Title color for common camera nodes.
- L31 _public member_ `FLinearColor CameraAssetTitleColor;` — `UPROPERTY(EditAnywhere, Config, Category=NodeTitleColors)` — Title color for a camera asset's root node.
- L35 _public member_ `FLinearColor CameraRigAssetTitleColor;` — `UPROPERTY(EditAnywhere, Config, Category=NodeTitleColors)` — Title color for a camera rig asset's root node.
- L39 _public member_ `FLinearColor CameraShakeAssetTitleColor;` — `UPROPERTY(EditAnywhere, Config, Category=NodeTitleColors)` — Title color for a camera shake asset's root node.
- L43 _public member_ `FLinearColor CameraRigTransitionTitleColor;` — `UPROPERTY(EditAnywhere, Config, Category=NodeTitleColors)` — Title color for a camera transition node.
- L47 _public member_ `FLinearColor CameraRigTransitionConditionTitleColor;` — `UPROPERTY(EditAnywhere, Config, Category=NodeTitleColors)` — Title color for a camera transition condition node.
- L51 _public member_ `FLinearColor CameraBlendNodeTitleColor;` — `UPROPERTY(EditAnywhere, Config, Category=NodeTitleColors)` — Title color for a camera blend node.
- L57 _public member_ `FName LastCameraAssetToolkitModeName;` — `UPROPERTY()` — Camera asset mode to restore on open (director, shared transitions, etc.)
- L63 _public member_ `bool bEnableRunInEditor = true;` — `UPROPERTY(EditAnywhere, Config, Category="Editor Preview")` — Global enable/disable flag for running camera rigs in editor.

### `Plugins/Cameras/GameplayCameras/Source/GameplayCamerasEditor/Public/IGameplayCamerasEditorModule.h` (Public)


#### struct `UE::Cameras::FCameraDebugCategoryInfo`  
`struct FCameraDebugCategoryInfo`  
_L30-36_
- L32 _public member_ `FString Name;`
- L33 _public member_ `FText DisplayText;`
- L34 _public member_ `FText ToolTipText;`
- L35 _public member_ `FSlateIcon IconImage;`

#### class `IGameplayCamerasEditorModule`  
`class IGameplayCamerasEditorModule : public IModuleInterface`  
_L46-105_
- inherits: `IModuleInterface`
- desc: The gameplay cameras editor module.
- L50 _public member_ `static const FName GameplayCamerasEditorAppIdentifier;`
- L51 _public member_ `static const FName CameraRigAssetEditorToolBarName;`
- L53 _public prototype_ `static IGameplayCamerasEditorModule& Get();`
- L55 _public prototype_ `virtual ~IGameplayCamerasEditorModule() = default;`
- L59 _public typedef_ `using FCameraVariablePickerConfig = UE::Cameras::FCameraVariablePickerConfig;`
- L62 _public prototype_ `virtual UCameraAssetEditor* CreateCameraAssetEditor(const EToolkitMode::Type Mode, const TSharedPtr<IToolkitHost>& InitToolkitHost, UCameraAsset* CameraAsset) = 0;` — Creates an editor for the given camera asset
- L65 _public prototype_ `virtual UCameraRigAssetEditor* CreateCameraRigEditor(const EToolkitMode::Type Mode, const TSharedPtr<IToolkitHost>& InitToolkitHost, UCameraRigAsset* CameraRig) = 0;` — Creates an editor for the given camera rig asset
- L68 _public prototype_ `virtual UCameraRigProxyAssetEditor* CreateCameraRigProxyEditor(const EToolkitMode::Type Mode, const TSharedPtr<IToolkitHost>& InitToolkitHost, UCameraRigProxyAsset* CameraRigProxy) = 0;` — Creates an editor for the given camera rig proxy asset
- L71 _public prototype_ `virtual UCameraShakeAssetEditor* CreateCameraShakeEditor(const EToolkitMode::Type Mode, const TSharedPtr<IToolkitHost>& InitToolkitHost, UCameraShakeAsset* CameraShake) = 0;` — Creates an editor for the given camera shake asset
- L74 _public prototype_ `virtual UCameraVariableCollectionEditor* CreateCameraVariableCollectionEditor(const EToolkitMode::Type Mode, const TSharedPtr<IToolkitHost>& InitToolkitHost, UCameraVariableCollection* VariableCollection) = 0;` — Creates an editor for the given variable collection
- L77 _public prototype_ `virtual TSharedRef<SWidget> CreateCameraVariablePicker(const FCameraVariablePickerConfig& InPickerConfig) = 0;` — Creates a new camera varable asset picker widget
- L82 _public prototype_ `virtual FDelegateHandle RegisterCameraDirectorEditor(FOnCreateCameraDirectorAssetEditorMode InOnCreateEditor) = 0;` — Registers a new camera director editor creator.
- L84 _public prototype_ `virtual TArrayView<const FOnCreateCameraDirectorAssetEditorMode> GetCameraDirectorEditorCreators() const = 0;` — Gets the registered camera director editor creators.
- L86 _public prototype_ `virtual void UnregisterCameraDirectorEditor(FDelegateHandle InHandle) = 0;` — Unregisters a camera director editor creator.
- L90 _public typedef_ `using FCameraDebugCategoryInfo = UE::Cameras::FCameraDebugCategoryInfo;`
- L93 _public prototype_ `virtual void RegisterDebugCategory(const UE::Cameras::FCameraDebugCategoryInfo& InCategoryInfo) = 0;` — Registers a new debug category, to be displayed in the camera debugger tool.
- L95 _public prototype_ `virtual void GetRegisteredDebugCategories(TArray<UE::Cameras::FCameraDebugCategoryInfo>& OutCategoryInfos) = 0;` — Gets all registered debug categories.
- L97 _public prototype_ `virtual void UnregisterDebugCategory(const FString& InCategoryName) = 0;` — Unregisters a debug category.
- L100 _public prototype_ `virtual void RegisterDebugCategoryPanel(const FString& InCategoryName, FOnCreateDebugCategoryPanel OnCreatePanel) = 0;` — Registers a custom UI panel for a given debug category.
- L102 _public prototype_ `virtual TSharedPtr<SWidget> CreateDebugCategoryPanel(const FString& InCategoryName) = 0;` — Creates the custom UI panel (if any) for a given debug category.
- L104 _public prototype_ `virtual void UnregisterDebugCategoryPanel(const FString& InCategoryName) = 0;` — Unregisters a debug category's custom UI panel.

#### Free symbols / members of external scopes

- L23 _namespace_ `namespace UE`
- L23 _namespace_ `namespace Cameras` (scope `UE`)
- L40 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(TSharedPtr<UE::Cameras::FCameraDirectorAssetEditorMode>, FOnCreateCameraDirectorAssetEditorMode, UCameraAsset*);`
- L40 _prototype_ `DECLARE_DELEGATE_RetVal_OneParam(TSharedPtr<UE::Cameras::FCameraDirectorAssetEditorMode>, FOnCreateCameraDirectorAssetEditorMode, UCameraAsset*);`
- L41 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(TSharedRef<SWidget>, FOnCreateDebugCategoryPanel, const FString&);`
- L41 _prototype_ `DECLARE_DELEGATE_RetVal_OneParam(TSharedRef<SWidget>, FOnCreateDebugCategoryPanel, const FString&);`
- L107 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogCameraSystemEditor, Log, All);`
- L107 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogCameraSystemEditor, Log, All);`

### `Plugins/Cameras/GameplayCameras/Source/GameplayCamerasEditor/Public/IGameplayCamerasFamily.h` (Public)


#### class `UE::Cameras::IGameplayCamerasFamily`  
`class IGameplayCamerasFamily : public TSharedFromThis<IGameplayCamerasFamily>`  
_L14-35_
- inherits: `TSharedFromThis<IGameplayCamerasFamily>`
- L18 _public prototype_ `virtual ~IGameplayCamerasFamily() = default;`
- L20 _public prototype_ `virtual UObject* GetRootAsset() const = 0;`
- L22 _public prototype_ `virtual void GetAssetTypes(TArray<UClass*>& OutAssetTypes) const = 0;`
- L24 _public prototype_ `virtual void FindAssetsOfType(UClass* InAssetType, TArray<FAssetData>& OutAssets) const = 0;`
- L26 _public prototype_ `virtual FText GetAssetTypeTooltip(UClass* InAssetType) const = 0;`
- L28 _public prototype_ `virtual const FSlateBrush* GetAssetIcon(UClass* InAssetType) const = 0;`
- L30 _public prototype_ `virtual FSlateColor GetAssetTint(UClass* InAssetType) const = 0;`
- L34 _public prototype_ `static TSharedPtr<IGameplayCamerasFamily> CreateFamily(UObject* InAsset);`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace Cameras` (scope `UE`)

### `Plugins/Cameras/GameplayCameras/Source/GameplayCamerasEditor/Public/Toolkits/AssetEditorMode.h` (Public)


#### struct `UE::Cameras::FAssetEditorModeActivateParams`  
`struct FAssetEditorModeActivateParams`  
_L20-27_
- desc: Parameter structure for activating an asset editor mode.
- L22 _public member_ `TSharedPtr<FAssetEditorToolkit> Toolkit;`
- L23 _public member_ `TSharedPtr<FTabManager> TabManager;`
- L24 _public member_ `TSharedPtr<FWorkspaceItem> AssetEditorTabsCategory;`
- L25 _public member_ `TSharedPtr<FUICommandList> CommandList;`
- L26 _public member_ `FName ToolbarMenuName;`

#### struct `UE::Cameras::FAssetEditorModeDeactivateParams`  
`struct FAssetEditorModeDeactivateParams`  
_L32-36_
- desc: Parameter structure for deactivating an asset editor mode.
- L34 _public member_ `TSharedPtr<FAssetEditorToolkit> Toolkit;`
- L35 _public member_ `TSharedPtr<FTabManager> TabManager;`

#### class `UE::Cameras::FAssetEditorMode`  
`class FAssetEditorMode : public TSharedFromThis<FAssetEditorMode>`  
_L44-76_
- inherits: `TSharedFromThis<FAssetEditorMode>`
- desc: An editor mode inside an FAssetEditorModeManagerToolkit. This changes the toolkit's editor to match a desired "editing mode" or "workflow" in that editor. The layout changes, the tabs change, the toolbars change, etc.
- L49 _public prototype_ `FAssetEditorMode();`
- L50 _public prototype_ `FAssetEditorMode(FName InModeName);`
- L51 _public prototype_ `virtual ~FAssetEditorMode();`
- L53 _public prototype_ `void ActivateMode(const FAssetEditorModeActivateParams& InParams);`
- L54 _public prototype_ `void DeactivateMode(const FAssetEditorModeDeactivateParams& InParams);`
- L56 _public function_ `FName GetModeName() const`
- L57 _public function_ `TSharedPtr<FTabManager::FLayout> GetDefaultLayout() const`
- L58 _public function_ `TSharedPtr<FExtender> GetToolbarExtender() const`
- L59 _public function_ `TSharedPtr<FLayoutExtender> GetLayoutExtender() const`
- L61 _public prototype_ `void InitToolMenuContext(FToolMenuContext& MenuContext);`
- L65 _protected function_ `virtual void OnActivateMode(const FAssetEditorModeActivateParams& InParams)`
- L66 _protected function_ `virtual void OnInitToolMenuContext(FToolMenuContext& MenuContext)`
- L67 _protected function_ `virtual void OnDeactivateMode(const FAssetEditorModeDeactivateParams& InParams)`
- L71 _protected member_ `FName ModeName;`
- L73 _protected member_ `TSharedPtr<FTabManager::FLayout> DefaultLayout;`
- L74 _protected member_ `TSharedPtr<FExtender> ToolbarExtender;`
- L75 _protected member_ `TSharedPtr<FLayoutExtender> LayoutExtender;`

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace Cameras` (scope `UE`)

### `Plugins/Cameras/GameplayCameras/Source/GameplayCamerasEditor/Public/Toolkits/AssetEditorModeManagerToolkit.h` (Public)


#### class `UE::Cameras::FAssetEditorModeManagerToolkit`  
`class FAssetEditorModeManagerToolkit : public FBaseAssetToolkit`  
_L22-64_
- inherits: `FBaseAssetToolkit`
- desc: An editor toolkit that can manage different "editor modes". Similar to FWorkflowCentricApplication but with a few nuances such as making it possible to retain some common tabs between modes.
- L27 _public prototype_ `FAssetEditorModeManagerToolkit(UAssetEditor* InOwningAssetEditor);`
- L28 _public prototype_ `~FAssetEditorModeManagerToolkit();`
- L33 _protected prototype_ `virtual void InitToolMenuContext(FToolMenuContext& MenuContext) override;` — FBaseAssetToolkit interface
- L36 _protected function_ `virtual void OnEditorToolkitModeActivated()` — FCameraAssetEditorToolkitMode interface
- L40 _protected prototype_ `void AddEditorMode(TSharedRef<FAssetEditorMode> InMode);`
- L41 _protected prototype_ `void RemoveEditorMode(TSharedRef<FAssetEditorMode> InMode);`
- L42 _protected prototype_ `void RemoveEditorMode(FName InModeName);`
- L44 _protected prototype_ `TSharedPtr<FAssetEditorMode> GetEditorMode(FName InModeName) const;`
- L45 _protected prototype_ `void GetEditorModes(TArray<TSharedPtr<FAssetEditorMode>>& OutModes) const;`
- L47 _protected prototype_ `void SetEditorMode(FName InModeName);`
- L48 _protected prototype_ `bool CanSetEditorMode(FName InModeName) const;`
- L49 _protected prototype_ `bool IsEditorMode(FName InModeName) const;`
- L50 _protected prototype_ `FName GetCurrentEditorModeName() const;`
- L53 _protected function_ `template<typename EditorModeClass> TSharedPtr<EditorModeClass> GetTypedEditorMode(FName InModeName) const`
- L60 _private member_ `TMap<FName, TSharedPtr<FAssetEditorMode>> EditorModes;`
- L62 _private member_ `FName CurrentEditorModeName;`
- L63 _private member_ `TSharedPtr<FAssetEditorMode> CurrentEditorMode;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace Cameras` (scope `UE`)

### `Plugins/Cameras/GameplayCameras/Source/GameplayCamerasEditor/Public/Toolkits/BlueprintCameraDirectorAssetEditorMode.h` (Public)


#### class `UE::Cameras::FBlueprintCameraDirectorAssetEditorMode`  
`class FBlueprintCameraDirectorAssetEditorMode : public FCameraDirectorAssetEditorMode , public ICameraAssetEventHandler`  
_L11-24_
- inherits: `FCameraDirectorAssetEditorMode,ICameraAssetEventHandler`
- L17 _public prototype_ `static TSharedPtr<FCameraDirectorAssetEditorMode> CreateInstance(UCameraAsset* InCameraAsset);`
- L19 _public prototype_ `FBlueprintCameraDirectorAssetEditorMode(UCameraAsset* InCameraAsset);`
- L23 _private member_ `TCameraEventHandler<ICameraAssetEventHandler> EventHandler;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace Cameras` (scope `UE`)

### `Plugins/Cameras/GameplayCameras/Source/GameplayCamerasEditor/Public/Toolkits/BuildButtonToolkit.h` (Public)


#### class `UE::Cameras::FBuildButtonToolkit`  
`class FBuildButtonToolkit : public TSharedFromThis<FBuildButtonToolkit>`  
_L21-40_
- inherits: `TSharedFromThis<FBuildButtonToolkit>`
- desc: A utility toolkit for have a "Build" toolbar button that features a different icon based on the target asset's build status.
- L25 _public prototype_ `FBuildButtonToolkit();`
- L26 _public prototype_ `FBuildButtonToolkit(TScriptInterface<IHasCameraBuildStatus> InTarget);`
- L28 _public prototype_ `void SetTarget(TScriptInterface<IHasCameraBuildStatus> InTarget);`
- L30 _public prototype_ `FToolMenuEntry MakeToolbarButton(TSharedPtr<FUICommandInfo> InCommand);`
- L34 _private prototype_ `FSlateIcon GetBuildButtonIcon() const;`
- L35 _private prototype_ `FText GetBuildButtonTooltip() const;`
- L39 _private member_ `TScriptInterface<IHasCameraBuildStatus> Target;`

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace Cameras` (scope `UE`)

### `Plugins/Cameras/GameplayCameras/Source/GameplayCamerasEditor/Public/Toolkits/CameraAssetEditorToolkit.h` (Public)


#### class `UE::Cameras::FCameraAssetEditorToolkit`  
`class FCameraAssetEditorToolkit : public FAssetEditorModeManagerToolkit , public FEditorUndoClient , public FGCObject , public UE::Cameras::ICameraAssetEventHandler`  
_L33-133_
- inherits: `FAssetEditorModeManagerToolkit,FEditorUndoClient,FGCObject,UE::Cameras::ICameraAssetEventHandler`
- desc: Editor toolkit for a camera asset.
- L41 _public prototype_ `FCameraAssetEditorToolkit(UCameraAssetEditor* InOwningAssetEditor);`
- L42 _public prototype_ `~FCameraAssetEditorToolkit();`
- L44 _public function_ `UCameraAsset* GetCameraAsset() const`
- L49 _protected prototype_ `virtual void RegisterTabSpawners(const TSharedRef<class FTabManager>& TabManager) override;` — FBaseAssetToolkit interface
- L50 _protected prototype_ `virtual void UnregisterTabSpawners(const TSharedRef<FTabManager>& InTabManager) override;`
- L51 _protected prototype_ `virtual void CreateWidgets() override;`
- L52 _protected prototype_ `virtual void RegisterToolbar() override;`
- L53 _protected prototype_ `virtual void InitToolMenuContext(FToolMenuContext& MenuContext) override;`
- L54 _protected prototype_ `virtual void PostInitAssetEditor() override;`
- L55 _protected prototype_ `virtual void PostRegenerateMenusAndToolbars() override;`
- L58 _protected prototype_ `virtual FText GetBaseToolkitName() const override;` — IToolkit interface
- L59 _protected prototype_ `virtual FName GetToolkitFName() const override;`
- L60 _protected prototype_ `virtual FString GetWorldCentricTabPrefix() const override;`
- L61 _protected prototype_ `virtual FLinearColor GetWorldCentricTabColorScale() const override;`
- L64 _protected prototype_ `virtual void PostUndo(bool bSuccess) override;` — FEditorUndoClient interface
- L65 _protected prototype_ `virtual void PostRedo(bool bSuccess) override;`
- L68 _protected prototype_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override;` — FGCObject interface
- L69 _protected prototype_ `virtual FString GetReferencerName() const override;`
- L72 _protected prototype_ `virtual void OnEditorToolkitModeActivated() override;` — FAssetEditorModeManagerToolkit interface
- L75 _protected prototype_ `virtual void OnCameraDirectorChanged(UCameraAsset* InCameraAsset, const TCameraPropertyChangedEvent<UCameraDirector*>& Event) override;` — ICameraAssetEventHandler interface
- L79 _private prototype_ `TSharedRef<SDockTab> SpawnTab_Search(const FSpawnTabArgs& Args);`
- L80 _private prototype_ `TSharedRef<SDockTab> SpawnTab_Messages(const FSpawnTabArgs& Args);`
- L81 _private prototype_ `TSharedRef<SDockTab> SpawnTab_InterfaceParameters(const FSpawnTabArgs& Args);`
- L83 _private prototype_ `void FillCameraMenu(FMenuBuilder& MenuBuilder);`
- L85 _private prototype_ `TSharedPtr<FAssetEditorMode> CreateCameraDirectorAssetEditorMode();`
- L87 _private prototype_ `void OnChangeCameraDirector();`
- L88 _private prototype_ `void OnBuild();`
- L89 _private prototype_ `void OnFindInCamera();`
- L91 _private prototype_ `void OnGetGraphsToSearch(TArray<FFindInObjectTreeGraphSource>& OutSources);`
- L92 _private prototype_ `void OnJumpToNode(UEdGraphNode* Node, FName PinName = NAME_None);`
- L94 _private prototype_ `void OnJumpToObject(UObject* Object);`
- L95 _private prototype_ `void OnJumpToObject(UObject* Object, FName PropertyName);`
- L97 _private prototype_ `void OnInterfaceParameterSelected(UCameraAssetInterfaceParameter* InterfaceParameter);`
- L99 _private prototype_ `void UpgradeLegacyCameraAssets();`
- L103 _private member_ `static const FName SearchTabId;`
- L104 _private member_ `static const FName MessagesTabId;`
- L105 _private member_ `static const FName InterfaceParametersTabId;`
- L108 _private member_ `TObjectPtr<UCameraAsset> CameraAsset;` — The asset being edited
- L111 _private member_ `UE::Cameras::TCameraEventHandler<UE::Cameras::ICameraAssetEventHandler> CameraAssetEventHandler;` — Event listener for the camera asset
- L114 _private member_ `TSharedPtr<FStandardToolkitLayout> StandardLayout;` — The layout for this toolkit
- L117 _private member_ `TSharedPtr<FBuildButtonToolkit> BuildButtonToolkit;` — The "Build" button
- L120 _private member_ `TSharedPtr<FCameraBuildLogToolkit> BuildLogToolkit;` — The output/log window
- L123 _private member_ `TSharedPtr<SFindInObjectTreeGraph> SearchWidget;` — The search results window
- L126 _private member_ `TSharedPtr<SCameraAssetInterfaceParametersPanel> InterfaceParametersPanel;` — The panel for exposing parameters.
- L129 _private member_ `TObjectPtr<UGameplayCamerasEditorSettings> Settings;` — A cached pointer to the editor settings.
- L132 _private member_ `TSharedPtr<IGameplayCamerasLiveEditManager> LiveEditManager;` — Live edit manager for updating the assets in the runtime

#### class `UCameraAssetEditorMenuContext`  
`class UCameraAssetEditorMenuContext : public UObject`  
_L138-145_
- reflection: `UCLASS()`
- inherits: `UObject`
- L144 _public member_ `TWeakPtr<UE::Cameras::FCameraAssetEditorToolkit> Toolkit;`

#### Free symbols / members of external scopes

- L21 _namespace_ `namespace UE`
- L21 _namespace_ `namespace Cameras` (scope `UE`)

### `Plugins/Cameras/GameplayCameras/Source/GameplayCamerasEditor/Public/Toolkits/CameraBuildLogToolkit.h` (Public)


#### class `UE::Cameras::FCameraBuildLogToolkit`  
`class FCameraBuildLogToolkit : public TSharedFromThis<FCameraBuildLogToolkit>`  
_L25-51_
- inherits: `TSharedFromThis<FCameraBuildLogToolkit>`
- desc: A utility toolkit class that creates and manages a "messages" or "output" tab that can show the build log of a camera asset or camera rig asset.
- L29 _public prototype_ `FCameraBuildLogToolkit();`
- L31 _public prototype_ `void Initialize(FName InLogName);`
- L33 _public function_ `TSharedPtr<IMessageLogListing> GetMessageListing() const`
- L34 _public function_ `TSharedPtr<SWidget> GetMessagesWidget() const`
- L36 _public function_ `FRequestJumpToObject& OnRequestJumpToObject()`
- L38 _public prototype_ `void PopulateMessageListing(FCameraBuildLog& InBuildLog);`
- L42 _private prototype_ `void OnMessageTokenClicked(const TSharedRef<IMessageToken>& InMessageToken);`
- L46 _private member_ `TSharedPtr<IMessageLogListing> MessageListing;`
- L48 _private member_ `TSharedPtr<SWidget> MessagesWidget;`
- L50 _private member_ `FRequestJumpToObject RequestJumpToObject;`

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace Cameras` (scope `UE`)
- L19 _delegate_ `DECLARE_DELEGATE_OneParam(FRequestJumpToObject, UObject*);`
- L19 _prototype_ `DECLARE_DELEGATE_OneParam(FRequestJumpToObject, UObject*);` (scope `UE::Cameras`)

### `Plugins/Cameras/GameplayCameras/Source/GameplayCamerasEditor/Public/Toolkits/CameraDirectorAssetEditorMode.h` (Public)


#### class `UE::Cameras::FCameraDirectorAssetEditorMode`  
`class FCameraDirectorAssetEditorMode : public FAssetEditorMode , public FNotifyHook`  
_L18-54_
- inherits: `FAssetEditorMode,FNotifyHook`
- L24 _public member_ `static FName ModeName;`
- L26 _public prototype_ `FCameraDirectorAssetEditorMode(UCameraAsset* InCameraAsset);`
- L28 _public prototype_ `bool JumpToObject(UObject* InObject, FName InPropertyName);`
- L33 _protected prototype_ `virtual void OnActivateMode(const FAssetEditorModeActivateParams& InParams) override;` — FAssetEditorMode interface.
- L34 _protected prototype_ `virtual void OnDeactivateMode(const FAssetEditorModeDeactivateParams& InParams) override;`
- L37 _protected prototype_ `virtual void NotifyPostChange(const FPropertyChangedEvent& PropertyChangedEvent, FProperty* PropertyThatChanged) override;` — FNotifyHook interface.
- L41 _private prototype_ `TSharedRef<SDockTab> SpawnTab_DirectorEditor(const FSpawnTabArgs& Args);`
- L45 _private member_ `static FName DirectorEditorTabId;`
- L47 _private member_ `UCameraAsset* CameraAsset;`
- L49 _private member_ `TSharedPtr<FStandardToolkitLayout> StandardLayout;`
- L51 _private member_ `TSharedPtr<IDetailsView> DetailsView;`
- L53 _private member_ `bool bInitializedToolkit = false;`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace Cameras` (scope `UE`)

### `Plugins/Cameras/GameplayCameras/Source/GameplayCamerasEditor/Public/Toolkits/CameraObjectInterfaceParametersToolkit.h` (Public)


#### class `UE::Cameras::FCameraObjectInterfaceParametersToolkit`  
`class FCameraObjectInterfaceParametersToolkit : public TSharedFromThis<FCameraObjectInterfaceParametersToolkit> , public FEditorUndoClient`  
_L26-74_
- inherits: `TSharedFromThis<FCameraObjectInterfaceParametersToolkit>,FEditorUndoClient`
- desc: Utility toolkit for the "interface parameters" panel of any camera object editor.
- L32 _public prototype_ `FCameraObjectInterfaceParametersToolkit();`
- L33 _public prototype_ `~FCameraObjectInterfaceParametersToolkit();`
- L36 _public function_ `UBaseCameraObject* GetCameraObject() const` — Gets the camera object asset to edit.
- L38 _public prototype_ `void SetCameraObject(UBaseCameraObject* InCameraObject);` — Sets the camera object to edit. This re-creates the panel widget.
- L41 _public prototype_ `TSharedPtr<SWidget> GetInterfaceParametersPanel() const;` — Gets the panel widget.
- L46 _public prototype_ `void RenameSelectedParameter();` — Rename the selected parameter in the focused panel.
- L49 _public prototype_ `void DeleteSelectedParameter();` — Delete the selected parameter in the focused panel.
- L54 _public function_ `FOnCameraObjectInterfaceParameterEvent& OnInterfaceParameterSelected()` — Delegate invoked when a parmeter is selected in the panel.
- L57 _public function_ `FOnCameraObjectInterfaceParameterEvent& OnSearchInterfaceParameterNodes()` — Delegate invoked when the user requests finding getter nodes in the graph.
- L62 _protected prototype_ `virtual void PostUndo(bool bSuccess) override;` — FEditorUndoClient interface
- L63 _protected prototype_ `virtual void PostRedo(bool bSuccess) override;`
- L67 _private member_ `TObjectPtr<UBaseCameraObject> CameraObject;`
- L69 _private member_ `FOnCameraObjectInterfaceParameterEvent OnInterfaceParameterSelectedDelegate;`
- L70 _private member_ `FOnCameraObjectInterfaceParameterEvent OnSearchInterfaceParameterNodesDelegate;`
- L72 _private member_ `TSharedPtr<SBox> PanelContainer;`
- L73 _private member_ `TSharedPtr<SCameraObjectInterfaceParametersPanel> Panel;`

#### Free symbols / members of external scopes

- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace Cameras` (scope `UE`)
- L21 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnCameraObjectInterfaceParameterEvent, UCameraObjectInterfaceParameterBase*);`
- L21 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnCameraObjectInterfaceParameterEvent, UCameraObjectInterfaceParameterBase*);` (scope `UE::Cameras`)

### `Plugins/Cameras/GameplayCameras/Source/GameplayCamerasEditor/Public/Toolkits/CameraRigAssetEditorToolkit.h` (Public)


#### class `UE::Cameras::FCameraRigAssetEditorToolkit`  
`class FCameraRigAssetEditorToolkit : public FBaseAssetToolkit , public ICameraRigAssetEventHandler`  
_L27-114_
- inherits: `FBaseAssetToolkit,ICameraRigAssetEventHandler`
- L33 _public prototype_ `FCameraRigAssetEditorToolkit(UAssetEditor* InOwningAssetEditor);`
- L34 _public prototype_ `~FCameraRigAssetEditorToolkit();`
- L36 _public prototype_ `void SetCameraRigAsset(UCameraRigAsset* InCameraRig);`
- L41 _protected prototype_ `virtual void RegisterTabSpawners(const TSharedRef<class FTabManager>& InTabManager) override;` — FBaseAssetToolkit interface
- L42 _protected prototype_ `virtual void UnregisterTabSpawners(const TSharedRef<FTabManager>& InTabManager) override;`
- L43 _protected prototype_ `virtual void CreateWidgets() override;`
- L44 _protected prototype_ `virtual void RegisterToolbar() override;`
- L45 _protected prototype_ `virtual void InitToolMenuContext(FToolMenuContext& MenuContext) override;`
- L46 _protected prototype_ `virtual void PostInitAssetEditor() override;`
- L47 _protected prototype_ `virtual void PostRegenerateMenusAndToolbars() override;`
- L50 _protected prototype_ `virtual FText GetBaseToolkitName() const override;` — IToolkit interface
- L51 _protected prototype_ `virtual FName GetToolkitFName() const override;`
- L52 _protected prototype_ `virtual FString GetWorldCentricTabPrefix() const override;`
- L53 _protected prototype_ `virtual FLinearColor GetWorldCentricTabColorScale() const override;`
- L56 _protected prototype_ `virtual void OnObjectAddedToGraph(const FName GraphName, UObject* Object) override;` — ICameraRigAssetEventHandler interface
- L57 _protected prototype_ `virtual void OnObjectRemovedFromGraph(const FName GraphName, UObject* Object) override;`
- L61 _private prototype_ `TSharedRef<SDockTab> SpawnTab_Search(const FSpawnTabArgs& Args);`
- L62 _private prototype_ `TSharedRef<SDockTab> SpawnTab_Messages(const FSpawnTabArgs& Args);`
- L63 _private prototype_ `TSharedRef<SDockTab> SpawnTab_Curves(const FSpawnTabArgs& Args);`
- L64 _private prototype_ `TSharedRef<SDockTab> SpawnTab_InterfaceParameters(const FSpawnTabArgs& Args);`
- L66 _private prototype_ `void OnCurvesTabClosed(TSharedRef<SDockTab> InTab);`
- L68 _private prototype_ `void OnCameraObjectInterfaceParameterSelected(UCameraObjectInterfaceParameterBase* Object);`
- L69 _private prototype_ `void OnSearchCameraObjectInterfaceParameterNodes(UCameraObjectInterfaceParameterBase* Object);`
- L71 _private prototype_ `void OnBuild();`
- L72 _private prototype_ `void OnFindInCameraRig();`
- L74 _private prototype_ `void OnGetGraphsToSearch(TArray<FFindInObjectTreeGraphSource>& OutSources);`
- L75 _private prototype_ `void OnJumpToNode(UEdGraphNode* Node, FName PinName);`
- L77 _private prototype_ `void OnInvokeCurveEditor(UObject* Object, FName PropertyName);`
- L81 _private member_ `static const FName SearchTabId;`
- L82 _private member_ `static const FName MessagesTabId;`
- L83 _private member_ `static const FName CurvesTabId;`
- L84 _private member_ `static const FName InterfaceParametersTabId;`
- L87 _private member_ `TSharedPtr<FCameraRigAssetEditorToolkitBase> Impl;` — Base implementation
- L90 _private member_ `FObjectTreeGraphConfig NodeGraphConfig;` — Cached config for the node graph
- L92 _private member_ `FObjectTreeGraphConfig TransitionGraphConfig;` — Cached config for the transition graph
- L95 _private member_ `TSharedPtr<FBuildButtonToolkit> BuildButtonToolkit;` — The build button
- L97 _private member_ `TSharedPtr<FCameraBuildLogToolkit> BuildLogToolkit;` — The output log
- L99 _private member_ `TSharedPtr<FCurveEditorToolkit> CurveEditorToolkit;` — The curve editor
- L101 _private member_ `TSharedPtr<FCameraObjectInterfaceParametersToolkit> InterfaceParametersToolkit;` — The interface parameters panel
- L104 _private member_ `TSharedPtr<SFindInObjectTreeGraph> SearchWidget;` — Search widget
- L107 _private member_ `TSharedPtr<IGameplayCamerasLiveEditManager> LiveEditManager;` — Live edit manager for updating the assets in the runtime
- L110 _private member_ `TCameraEventHandler<ICameraRigAssetEventHandler> EventHandler;` — Event handler
- L113 _private member_ `bool bIsInitialized = false;` — Whether the toolkit has finished initializing

#### class `UCameraRigAssetEditorMenuContext`  
`class UCameraRigAssetEditorMenuContext : public UObject`  
_L119-126_
- reflection: `UCLASS()`
- inherits: `UObject`
- L125 _public member_ `TWeakPtr<UE::Cameras::FCameraRigAssetEditorToolkit> Toolkit;`

#### Free symbols / members of external scopes

- L17 _namespace_ `namespace UE`
- L17 _namespace_ `namespace Cameras` (scope `UE`)

### `Plugins/Cameras/GameplayCameras/Source/GameplayCamerasEditor/Public/Toolkits/CameraRigAssetEditorToolkitBase.h` (Public)


#### class `UE::Cameras::FCameraRigAssetEditorToolkitBase`  
`class FCameraRigAssetEditorToolkitBase : public FGCObject , public FNotifyHook , public TSharedFromThis<FCameraRigAssetEditorToolkitBase>`  
_L30-102_
- inherits: `FGCObject,FNotifyHook,TSharedFromThis<FCameraRigAssetEditorToolkitBase>`
- desc: Editor toolkit for a camera rig asset.
- L37 _public prototype_ `FCameraRigAssetEditorToolkitBase(FName InLayoutName);`
- L38 _public prototype_ `~FCameraRigAssetEditorToolkitBase();`
- L40 _public function_ `UCameraRigAsset* GetCameraRigAsset() const`
- L41 _public prototype_ `void SetCameraRigAsset(UCameraRigAsset* InCameraRig);`
- L43 _public function_ `TSharedPtr<FStandardToolkitLayout> GetStandardLayout() const`
- L44 _public function_ `TSharedPtr<IDetailsView> GetDetailsView() const`
- L45 _public function_ `TSharedPtr<SCameraRigAssetEditor> GetCameraRigAssetEditor() const`
- L47 _public prototype_ `void RegisterTabSpawners(TSharedRef<FTabManager> InTabManager, TSharedPtr<FWorkspaceItem> InAssetEditorTabsCategory);`
- L48 _public prototype_ `void UnregisterTabSpawners(TSharedRef<FTabManager> InTabManager);`
- L49 _public prototype_ `void CreateWidgets();`
- L50 _public prototype_ `void BuildToolbarMenu(UToolMenu* ToolbarMenu);`
- L51 _public prototype_ `void BindCommands(TSharedRef<FUICommandList> CommandList);`
- L53 _public prototype_ `void SetLiveEditManager(TSharedPtr<IGameplayCamerasLiveEditManager> InLiveEditManager);`
- L55 _public prototype_ `ECameraRigAssetEditorMode GetCameraRigEditorMode() const;`
- L56 _public prototype_ `bool IsCameraRigEditorMode(ECameraRigAssetEditorMode InEditorMode) const;`
- L61 _protected prototype_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override;` — FGCObject interface
- L62 _protected prototype_ `virtual FString GetReferencerName() const override;`
- L65 _protected prototype_ `virtual void NotifyPostChange(const FPropertyChangedEvent& PropertyChangedEvent, FProperty* PropertyThatChanged) override;` — FNotifyHook interface
- L69 _protected prototype_ `void SetCameraRigEditorMode(ECameraRigAssetEditorMode InEditorMode);`
- L73 _private prototype_ `TSharedRef<SDockTab> SpawnTab_Toolbox(const FSpawnTabArgs& Args);`
- L74 _private prototype_ `TSharedRef<SDockTab> SpawnTab_CameraRigEditor(const FSpawnTabArgs& Args);`
- L75 _private prototype_ `TSharedRef<SDockTab> SpawnTab_Details(const FSpawnTabArgs& Args);`
- L77 _private prototype_ `void OnAnyGraphChanged(const FEdGraphEditAction& InEditAction);`
- L81 _private member_ `static const FName ToolboxTabId;`
- L82 _private member_ `static const FName CameraRigEditorTabId;`
- L83 _private member_ `static const FName DetailsViewTabId;`
- L86 _private member_ `TObjectPtr<UCameraRigAsset> CameraRigAsset;` — The asset being edited
- L89 _private member_ `TSharedPtr<FStandardToolkitLayout> StandardLayout;` — The layout for this editor toolkit
- L92 _private member_ `TSharedPtr<IDetailsView> DetailsView;` — The details view
- L95 _private member_ `TSharedPtr<SCameraRigAssetEditor> CameraRigEditorWidget;` — Camera rig editor widget
- L98 _private member_ `TSharedPtr<SObjectTreeGraphToolbox> ToolboxWidget;` — Toolbox widget
- L101 _private member_ `TSharedPtr<IGameplayCamerasLiveEditManager> LiveEditManager;` — Live editing manager

#### Free symbols / members of external scopes

- L19 _namespace_ `namespace UE`
- L19 _namespace_ `namespace Cameras` (scope `UE`)

### `Plugins/Cameras/GameplayCameras/Source/GameplayCamerasEditor/Public/Toolkits/CameraRigProxyAssetEditorToolkit.h` (Public)


#### class `UE::Cameras::FCameraRigProxyAssetEditorToolkit`  
`class FCameraRigProxyAssetEditorToolkit : public FBaseAssetToolkit , public FGCObject`  
_L20-57_
- inherits: `FBaseAssetToolkit,FGCObject`
- desc: Editor toolkit for a camera rig proxy asset.
- L26 _public prototype_ `FCameraRigProxyAssetEditorToolkit(UCameraRigProxyAssetEditor* InOwningAssetEditor);`
- L27 _public prototype_ `~FCameraRigProxyAssetEditorToolkit();`
- L29 _public prototype_ `void SetCameraRigProxyAsset(UCameraRigProxyAsset* InCameraRigProxyAsset);`
- L34 _protected prototype_ `virtual void RegisterTabSpawners(const TSharedRef<class FTabManager>& TabManager) override;` — FBaseAssetToolkit interface
- L35 _protected prototype_ `virtual void UnregisterTabSpawners(const TSharedRef<FTabManager>& InTabManager) override;`
- L36 _protected prototype_ `virtual void CreateWidgets() override;`
- L37 _protected prototype_ `virtual void RegisterToolbar() override;`
- L38 _protected prototype_ `virtual void PostInitAssetEditor() override;`
- L39 _protected prototype_ `virtual void PostRegenerateMenusAndToolbars() override;`
- L42 _protected prototype_ `virtual FText GetBaseToolkitName() const override;` — IToolkit interface
- L43 _protected prototype_ `virtual FName GetToolkitFName() const override;`
- L44 _protected prototype_ `virtual FString GetWorldCentricTabPrefix() const override;`
- L45 _protected prototype_ `virtual FLinearColor GetWorldCentricTabColorScale() const override;`
- L48 _protected prototype_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override;` — FGCObject interface
- L49 _protected prototype_ `virtual FString GetReferencerName() const override;`
- L53 _private member_ `static const FName DetailsViewTabId;`
- L56 _private member_ `TObjectPtr<UCameraRigProxyAsset> CameraRigProxyAsset;` — The asset being edited

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace Cameras` (scope `UE`)

### `Plugins/Cameras/GameplayCameras/Source/GameplayCamerasEditor/Public/Toolkits/CameraRigTransitionEditorToolkit.h` (Public)


#### class `UE::Cameras::FCameraRigTransitionEditorToolkit`  
`class FCameraRigTransitionEditorToolkit : public FBaseAssetToolkit`  
_L20-46_
- inherits: `FBaseAssetToolkit`
- desc: Editor toolkit for camera transitions.
- L25 _public prototype_ `FCameraRigTransitionEditorToolkit(UAssetEditor* InOwningAssetEditor);`
- L27 _public prototype_ `void SetTransitionOwner(UObject* InTransitionOwner);`
- L32 _protected prototype_ `virtual void RegisterTabSpawners(const TSharedRef<FTabManager>& InTabManager) override;` — FBaseAssetToolkit interface
- L33 _protected prototype_ `virtual void UnregisterTabSpawners(const TSharedRef<FTabManager>& InTabManager) override;`
- L34 _protected prototype_ `virtual void CreateWidgets() override;`
- L35 _protected prototype_ `virtual void RegisterToolbar() override;`
- L38 _protected prototype_ `virtual FText GetBaseToolkitName() const override;` — IToolkit interface
- L39 _protected prototype_ `virtual FName GetToolkitFName() const override;`
- L40 _protected prototype_ `virtual FString GetWorldCentricTabPrefix() const override;`
- L41 _protected prototype_ `virtual FLinearColor GetWorldCentricTabColorScale() const override;`
- L45 _private member_ `TSharedPtr<FCameraRigTransitionEditorToolkitBase> Impl;`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace Cameras` (scope `UE`)

### `Plugins/Cameras/GameplayCameras/Source/GameplayCamerasEditor/Public/Toolkits/CameraRigTransitionEditorToolkitBase.h` (Public)


#### class `UE::Cameras::FCameraRigTransitionEditorToolkitBase`  
`class FCameraRigTransitionEditorToolkitBase : public FGCObject , public FNotifyHook , public TSharedFromThis<FCameraRigTransitionEditorToolkitBase>`  
_L26-88_
- inherits: `FGCObject,FNotifyHook,TSharedFromThis<FCameraRigTransitionEditorToolkitBase>`
- L33 _public prototype_ `FCameraRigTransitionEditorToolkitBase(FName InLayoutName);`
- L34 _public prototype_ `~FCameraRigTransitionEditorToolkitBase();`
- L36 _public function_ `UObject* GetTransitionOwner() const`
- L37 _public prototype_ `void SetTransitionOwner(UObject* InTransitionOwner);`
- L39 _public function_ `TSharedPtr<FStandardToolkitLayout> GetStandardLayout() const`
- L40 _public function_ `TSharedPtr<SCameraRigTransitionEditor> GetCameraRigTransitionEditor() const`
- L42 _public prototype_ `void RegisterTabSpawners(TSharedRef<FTabManager> InTabManager, TSharedPtr<FWorkspaceItem> InAssetEditorTabsCategory);`
- L43 _public prototype_ `void UnregisterTabSpawners(TSharedRef<FTabManager> InTabManager);`
- L44 _public prototype_ `void CreateWidgets();`
- L45 _public prototype_ `void BuildToolbarMenu(UToolMenu* ToolbarMenu);`
- L50 _protected prototype_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override;` — FGCObject interface
- L51 _protected prototype_ `virtual FString GetReferencerName() const override;`
- L54 _protected prototype_ `virtual void NotifyPostChange(const FPropertyChangedEvent& PropertyChangedEvent, FProperty* PropertyThatChanged) override;` — FNotifyHook interface
- L57 _protected prototype_ `virtual TSubclassOf<UCameraRigTransitionGraphSchemaBase> GetTransitionGraphSchemaClass();` — FCameraRigTransitionEditorToolkitBase interface
- L58 _protected function_ `virtual void GetTransitionGraphAppearanceInfo(FGraphAppearanceInfo& OutGraphAppearanceInfo)`
- L62 _private prototype_ `TSharedRef<SDockTab> SpawnTab_Toolbox(const FSpawnTabArgs& Args);`
- L63 _private prototype_ `TSharedRef<SDockTab> SpawnTab_TransitionEditor(const FSpawnTabArgs& Args);`
- L64 _private prototype_ `TSharedRef<SDockTab> SpawnTab_Details(const FSpawnTabArgs& Args);`
- L66 _private prototype_ `void OnTransitionGraphChanged(const FEdGraphEditAction& InEditAction);`
- L70 _private member_ `static const FName ToolboxTabId;`
- L71 _private member_ `static const FName TransitionEditorTabId;`
- L72 _private member_ `static const FName DetailsViewTabId;`
- L75 _private member_ `TObjectPtr<UObject> TransitionOwner;` — The object being edited
- L78 _private member_ `TSharedPtr<FStandardToolkitLayout> StandardLayout;` — The layout for this editor
- L81 _private member_ `TSharedPtr<IDetailsView> DetailsView;` — The details view for this editor
- L84 _private member_ `TSharedPtr<SCameraRigTransitionEditor> TransitionEditorWidget;` — Camera transition editor widget
- L87 _private member_ `TSharedPtr<SObjectTreeGraphToolbox> ToolboxWidget;` — Toolbox widget

#### Free symbols / members of external scopes

- L20 _namespace_ `namespace UE`
- L20 _namespace_ `namespace Cameras` (scope `UE`)

### `Plugins/Cameras/GameplayCameras/Source/GameplayCamerasEditor/Public/Toolkits/CameraShakeAssetEditorToolkit.h` (Public)


#### class `UE::Cameras::FCameraShakeAssetEditorToolkit`  
`class FCameraShakeAssetEditorToolkit : public FBaseAssetToolkit , public FGCObject , public FNotifyHook`  
_L30-129_
- inherits: `FBaseAssetToolkit,FGCObject,FNotifyHook`
- L37 _public prototype_ `FCameraShakeAssetEditorToolkit(UAssetEditor* InOwningAssetEditor);`
- L38 _public prototype_ `~FCameraShakeAssetEditorToolkit();`
- L40 _public prototype_ `void SetCameraShakeAsset(UCameraShakeAsset* InCameraShake);`
- L45 _protected prototype_ `virtual void RegisterTabSpawners(const TSharedRef<class FTabManager>& InTabManager) override;` — FBaseAssetToolkit interface
- L46 _protected prototype_ `virtual void UnregisterTabSpawners(const TSharedRef<FTabManager>& InTabManager) override;`
- L47 _protected prototype_ `virtual void CreateWidgets() override;`
- L48 _protected prototype_ `virtual void RegisterToolbar() override;`
- L49 _protected prototype_ `virtual void InitToolMenuContext(FToolMenuContext& MenuContext) override;`
- L50 _protected prototype_ `virtual void PostInitAssetEditor() override;`
- L51 _protected prototype_ `virtual void PostRegenerateMenusAndToolbars() override;`
- L54 _protected prototype_ `virtual FText GetBaseToolkitName() const override;` — IToolkit interface
- L55 _protected prototype_ `virtual FName GetToolkitFName() const override;`
- L56 _protected prototype_ `virtual FString GetWorldCentricTabPrefix() const override;`
- L57 _protected prototype_ `virtual FLinearColor GetWorldCentricTabColorScale() const override;`
- L60 _protected prototype_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override;` — FGCObject interface
- L61 _protected prototype_ `virtual FString GetReferencerName() const override;`
- L64 _protected prototype_ `virtual void NotifyPostChange(const FPropertyChangedEvent& PropertyChangedEvent, FProperty* PropertyThatChanged) override;` — FNotifyHook interface
- L68 _private prototype_ `TSharedRef<SDockTab> SpawnTab_CameraShakeEditor(const FSpawnTabArgs& Args);`
- L69 _private prototype_ `TSharedRef<SDockTab> SpawnTab_Details(const FSpawnTabArgs& Args);`
- L70 _private prototype_ `TSharedRef<SDockTab> SpawnTab_Search(const FSpawnTabArgs& Args);`
- L71 _private prototype_ `TSharedRef<SDockTab> SpawnTab_Messages(const FSpawnTabArgs& Args);`
- L72 _private prototype_ `TSharedRef<SDockTab> SpawnTab_Toolbox(const FSpawnTabArgs& Args);`
- L73 _private prototype_ `TSharedRef<SDockTab> SpawnTab_InterfaceParameters(const FSpawnTabArgs& Args);`
- L75 _private prototype_ `void CreateNodeGraphEditor();`
- L76 _private prototype_ `void DiscardNodeGraphEditor();`
- L78 _private prototype_ `FText GetCameraShakeAssetName() const;`
- L79 _private prototype_ `bool IsGraphEditorEnabled() const;`
- L81 _private prototype_ `void OnCameraObjectInterfaceParameterSelected(UCameraObjectInterfaceParameterBase* Object);`
- L83 _private prototype_ `void OnBuild();`
- L84 _private prototype_ `void OnFindInCameraShake();`
- L86 _private prototype_ `void OnGetGraphsToSearch(TArray<FFindInObjectTreeGraphSource>& OutSources);`
- L87 _private prototype_ `void OnJumpToNode(UEdGraphNode* Node, FName PinName);`
- L89 _private prototype_ `void OnJumpToObject(UObject* Object, FName PropertyName);`
- L90 _private prototype_ `void OnFocusHome();`
- L94 _private member_ `static const FName CameraShakeEditorTabId;`
- L96 _private member_ `static const FName DetailsViewTabId;`
- L98 _private member_ `static const FName SearchTabId;`
- L99 _private member_ `static const FName MessagesTabId;`
- L101 _private member_ `static const FName ToolboxTabId;`
- L102 _private member_ `static const FName InterfaceParametersTabId;`
- L105 _private member_ `TObjectPtr<UCameraShakeAsset> CameraShakeAsset;` — The asset being edited
- L108 _private member_ `TSharedPtr<FStandardToolkitLayout> StandardLayout;` — The layout for this editor toolkit
- L111 _private member_ `FObjectTreeGraphConfig NodeGraphConfig;` — Cached config for the node graph
- L114 _private member_ `TObjectPtr<UObjectTreeGraph> NodeGraph;` — The node hierarchy graph
- L116 _private member_ `TSharedPtr<SObjectTreeGraphEditor> NodeGraphEditor;` — The node hierarchy graph editor
- L119 _private member_ `TSharedPtr<FBuildButtonToolkit> BuildButtonToolkit;` — The build button
- L121 _private member_ `TSharedPtr<FCameraBuildLogToolkit> BuildLogToolkit;` — The output log
- L123 _private member_ `TSharedPtr<SObjectTreeGraphToolbox> ToolboxWidget;` — Toolbox widget
- L125 _private member_ `TSharedPtr<FCameraObjectInterfaceParametersToolkit> InterfaceParametersToolkit;` — The interface parameters panel
- L128 _private member_ `TSharedPtr<SFindInObjectTreeGraph> SearchWidget;` — Search widget

#### class `UCameraShakeAssetEditorMenuContext`  
`class UCameraShakeAssetEditorMenuContext : public UObject`  
_L134-141_
- reflection: `UCLASS()`
- inherits: `UObject`
- L140 _public member_ `TWeakPtr<UE::Cameras::FCameraShakeAssetEditorToolkit> Toolkit;`

#### Free symbols / members of external scopes

- L21 _namespace_ `namespace UE`
- L21 _namespace_ `namespace Cameras` (scope `UE`)

### `Plugins/Cameras/GameplayCameras/Source/GameplayCamerasEditor/Public/Toolkits/CameraSharedTransitionsAssetEditorMode.h` (Public)


#### class `UE::Cameras::FCameraSharedTransitionsAssetEditorMode`  
`class FCameraSharedTransitionsAssetEditorMode : public FAssetEditorMode`  
_L18-45_
- inherits: `FAssetEditorMode`
- L23 _public member_ `static FName ModeName;`
- L25 _public prototype_ `FCameraSharedTransitionsAssetEditorMode(UCameraAsset* InCameraAsset);`
- L27 _public prototype_ `void OnGetGraphsToSearch(TArray<FFindInObjectTreeGraphSource>& OutSources);`
- L28 _public prototype_ `void JumpToNode(UEdGraphNode* InNode, FName InPinName);`
- L29 _public prototype_ `bool JumpToObject(UObject* InObject, FName InPropertyName);`
- L33 _protected prototype_ `virtual void OnActivateMode(const FAssetEditorModeActivateParams& InParams) override;`
- L34 _protected prototype_ `virtual void OnDeactivateMode(const FAssetEditorModeDeactivateParams& InParams) override;`
- L38 _private member_ `UCameraAsset* CameraAsset;`
- L40 _private member_ `TSharedPtr<FCameraRigTransitionEditorToolkitBase> Impl;`
- L42 _private member_ `FObjectTreeGraphConfig TransitionGraphConfig;`
- L44 _private member_ `bool bInitializedToolkit = false;`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace Cameras` (scope `UE`)

### `Plugins/Cameras/GameplayCameras/Source/GameplayCamerasEditor/Public/Toolkits/CameraVariableCollectionEditorToolkit.h` (Public)


#### class `UE::Cameras::FCameraVariableCollectionEditorToolkit`  
`class FCameraVariableCollectionEditorToolkit : public FBaseAssetToolkit , public FEditorUndoClient , public FGCObject`  
_L24-86_
- inherits: `FBaseAssetToolkit,FEditorUndoClient,FGCObject`
- desc: Editor toolkit for a camera variable collection.
- L31 _public prototype_ `FCameraVariableCollectionEditorToolkit(UCameraVariableCollectionEditor* InOwningAssetEditor);`
- L32 _public prototype_ `~FCameraVariableCollectionEditorToolkit();`
- L35 _public prototype_ `virtual void FocusWindow(UObject* ObjectToFocusOn = nullptr) override;` — IAssetEditorInstance interface
- L40 _protected prototype_ `virtual void RegisterTabSpawners(const TSharedRef<class FTabManager>& InTabManager) override;` — FBaseAssetToolkit interface
- L41 _protected prototype_ `virtual void UnregisterTabSpawners(const TSharedRef<FTabManager>& InTabManager) override;`
- L42 _protected prototype_ `virtual void CreateWidgets() override;`
- L43 _protected prototype_ `virtual void RegisterToolbar() override;`
- L44 _protected prototype_ `virtual void InitToolMenuContext(FToolMenuContext& MenuContext) override;`
- L45 _protected prototype_ `virtual void PostInitAssetEditor() override;`
- L46 _protected prototype_ `virtual void PostRegenerateMenusAndToolbars() override;`
- L49 _protected prototype_ `virtual FText GetBaseToolkitName() const override;` — IToolkit interface
- L50 _protected prototype_ `virtual FName GetToolkitFName() const override;`
- L51 _protected prototype_ `virtual FString GetWorldCentricTabPrefix() const override;`
- L52 _protected prototype_ `virtual FLinearColor GetWorldCentricTabColorScale() const override;`
- L55 _protected prototype_ `virtual void PostUndo(bool bSuccess) override;` — FEditorUndoClient interface
- L56 _protected prototype_ `virtual void PostRedo(bool bSuccess) override;`
- L59 _protected prototype_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override;` — FGCObject interface
- L60 _protected prototype_ `virtual FString GetReferencerName() const override;`
- L64 _private prototype_ `TSharedRef<SDockTab> SpawnTab_VariableCollectionEditor(const FSpawnTabArgs& Args);`
- L66 _private prototype_ `static void GenerateAddNewVariableMenu(UToolMenu* InMenu);`
- L68 _private prototype_ `void OnCreateVariable(TSubclassOf<UCameraVariableAsset> InVariableClass);`
- L70 _private prototype_ `void OnRenameVariable();`
- L71 _private prototype_ `bool CanRenameVariable();`
- L73 _private prototype_ `void OnDeleteVariable();`
- L74 _private prototype_ `bool CanDeleteVariable();`
- L78 _private member_ `static const FName VariableCollectionEditorTabId;`
- L79 _private member_ `static const FName DetailsViewTabId;`
- L82 _private member_ `TObjectPtr<UCameraVariableCollection> VariableCollection;` — The asset being edited
- L85 _private member_ `TSharedPtr<SCameraVariableCollectionEditor> VariableCollectionEditorWidget;` — Camera variable collection editor widget

#### class `UCameraVariableCollectionEditorMenuContext`  
`class UCameraVariableCollectionEditorMenuContext : public UObject`  
_L91-98_
- reflection: `UCLASS()`
- inherits: `UObject`
- L97 _public member_ `TWeakPtr<UE::Cameras::FCameraVariableCollectionEditorToolkit> EditorToolkit;`

#### Free symbols / members of external scopes

- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace Cameras` (scope `UE`)

### `Plugins/Cameras/GameplayCameras/Source/GameplayCamerasEditor/Public/Toolkits/CurveEditorToolkit.h` (Public)


#### class `UE::Cameras::FCurveEditorToolkit`  
`class FCurveEditorToolkit : public TSharedFromThis<FCurveEditorToolkit>`  
_L29-79_
- inherits: `TSharedFromThis<FCurveEditorToolkit>`
- desc: A utility toolkit that hosts a curve editor showing curves from any object that has curve properties.
- L33 _public prototype_ `FCurveEditorToolkit();`
- L36 _public prototype_ `void Initialize();` — Initializes the toolkit and creates the curve editor.
- L38 _public prototype_ `void Initialize(TArrayView<UObject*> InCurveOwners);` — Initializes the toolkit and creates the curve editor, plus adds curves from the given objects.
- L41 _public function_ `bool IsInitialized() const` — Whether this toolkit is initialized and has a valid curve editor.
- L44 _public prototype_ `void Shutdown();` — Removes all curves and destroys the curve editor.
- L50 _public prototype_ `void AddCurveOwner(UObject* InCurveOwner);` — Adds curves for any curve property on the given object. If the object doesn't have any recognizable curve properties, nothing happens.
- L55 _public prototype_ `void AddCurveOwners(TArrayView<UObject*> InCurveOwners);` — Adds curves for any curve property on the given objects. If the object doesn't have any recognizable curve properties, nothing happens.
- L59 _public prototype_ `void RemoveCurveOwner(UObject* InCurveOwner);` — Removes any existing curves belonging to the given object.
- L62 _public prototype_ `void RemoveAllCurveOwners();` — Removes all curves from all curve owners.
- L65 _public prototype_ `void SelectCurves(UObject* InCurveOwner, FName InPropertyName);` — Selects the curves associated with the given object and property name.
- L68 _public function_ `TSharedPtr<SWidget> GetCurveEditorWidget() const` — Gets the curve editor widget.
- L72 _private prototype_ `void AddCurves(UObject* InObject);`
- L73 _private prototype_ `FCurveEditorTreeItem* AddTreeItem(FCurveEditorTreeItemID ParentID, FCurvePropertyInfo&& CurveInfo);`
- L77 _private member_ `TSharedPtr<FCurveEditor> CurveEditor;`
- L78 _private member_ `TSharedPtr<SWidget> CurveEditorWidget;`

#### Free symbols / members of external scopes

- L20 _namespace_ `namespace UE`
- L20 _namespace_ `namespace Cameras` (scope `UE`)

### `Plugins/Cameras/GameplayCameras/Source/GameplayCamerasEditor/Public/Toolkits/SingleCameraDirectorAssetEditorMode.h` (Public)


#### class `UE::Cameras::FSingleCameraDirectorAssetEditorMode`  
`class FSingleCameraDirectorAssetEditorMode : public FCameraDirectorAssetEditorMode , public ICameraAssetEventHandler`  
_L11-24_
- inherits: `FCameraDirectorAssetEditorMode,ICameraAssetEventHandler`
- L17 _public prototype_ `static TSharedPtr<FCameraDirectorAssetEditorMode> CreateInstance(UCameraAsset* InCameraAsset);`
- L19 _public prototype_ `FSingleCameraDirectorAssetEditorMode(UCameraAsset* InCameraAsset);`
- L23 _private member_ `TCameraEventHandler<ICameraAssetEventHandler> EventHandler;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace Cameras` (scope `UE`)

### `Plugins/Cameras/GameplayCameras/Source/GameplayCamerasEditor/Public/Toolkits/StandardToolkitLayout.h` (Public)


#### class `UE::Cameras::FStandardToolkitLayout`  
`class FStandardToolkitLayout`  
_L15-47_
- desc: A utility class for building a standard layout with tab stacks on the left, right, and bottom of a central document area.
- L19 _public member_ `static const FName LeftStackExtensionId;`
- L20 _public member_ `static const FName CenterStackExtensionId;`
- L21 _public member_ `static const FName RightStackExtensionId;`
- L22 _public member_ `static const FName BottomStackExtensionId;`
- L24 _public prototype_ `FStandardToolkitLayout(FName LayoutName);`
- L26 _public prototype_ `TSharedPtr<FTabManager::FLayout> GetLayout() const;`
- L28 _public prototype_ `void AddLeftTab(FName InTabId, ETabState::Type InTabState = ETabState::OpenedTab);`
- L29 _public prototype_ `void AddRightTab(FName InTabId, ETabState::Type InTabState = ETabState::OpenedTab);`
- L30 _public prototype_ `void AddBottomTab(FName InTabId, ETabState::Type InTabState = ETabState::OpenedTab);`
- L31 _public prototype_ `void AddCenterTab(FName InTabId, ETabState::Type InTabState = ETabState::OpenedTab);`
- L35 _private prototype_ `void BuildLayout();`
- L39 _private member_ `FName LayoutName;`
- L41 _private member_ `TSharedPtr<FTabManager::FLayout> Layout;`
- L43 _private member_ `TSharedPtr<FTabManager::FStack> LeftTabStack;`
- L44 _private member_ `TSharedPtr<FTabManager::FStack> CenterTabStack;`
- L45 _private member_ `TSharedPtr<FTabManager::FStack> RightTabStack;`
- L46 _private member_ `TSharedPtr<FTabManager::FStack> BottomTabStack;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace Cameras` (scope `UE`)

### `Plugins/Cameras/GameplayCameras/Source/GameplayCamerasEditor/Public/Widgets/SCameraFamilyShortcutBar.h` (Public)


#### class `UE::Cameras::SCameraFamilyShortcutBar`  
`class SCameraFamilyShortcutBar : public SCompoundWidget`  
_L16-37_
- inherits: `SCompoundWidget`
- L20 _public function_ `SLATE_BEGIN_ARGS(SCameraFamilyShortcutBar)`
- L22 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TSharedRef<FBaseAssetToolkit>& InToolkit, const TSharedRef<IGameplayCamerasFamily>& InFamily);`
- L28 _private prototype_ `void BuildShortcuts();`
- L32 _private member_ `TWeakPtr<FBaseAssetToolkit> WeakToolkit;`
- L34 _private member_ `TSharedPtr<IGameplayCamerasFamily> Family;`
- L36 _private member_ `TSharedPtr<SHorizontalBox> HorizontalBox;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace Cameras` (scope `UE`)

### `Plugins/Cameras/GameplayCameras/Source/GameplayCamerasEditor/Public/Widgets/SDeleteCameraObjectDialog.h` (Public)


#### class `UE::Cameras::SDeleteCameraObjectDialog`  
`class SDeleteCameraObjectDialog : public SCompoundWidget`  
_L18-96_
- inherits: `SCompoundWidget`
- desc: Re-usable dialog for deleting camera objects that are sub-objects of an asset.
- L22 _public function_ `SLATE_BEGIN_ARGS(SDeleteCameraObjectDialog) : _RenameObjectsAsTrash(false)`
- L26 _public prototype_ `SLATE_ARGUMENT(TWeakPtr<SWindow>, ParentWindow) SLATE_ARGUMENT(TArrayView<UObject*>, ObjectsToDelete) SLATE_ATTRIBUTE(bool, RenameObjectsAsTrash) SLATE_EVENT(FOnDeletedObject, OnDeletedObject) SLATE_END_ARGS() void Construct(const FArguments& InArgs);` — The modal window containing this dialog.
- L37 _public prototype_ `bool ShouldPerformDelete() const;`
- L38 _public prototype_ `void PerformReferenceReplacement();`
- L42 _public prototype_ `static void RenameObjectAsTrash(FString& InOutName);`
- L43 _public prototype_ `static FString MakeTrashName(const FString& InName);`
- L48 _protected prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;` — SCompoundWidget interface.
- L49 _protected prototype_ `virtual FReply OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent) override;`
- L53 _private prototype_ `void StartScanning();`
- L54 _private prototype_ `void ScanNextObject(IAssetRegistry& AssetRegistry);`
- L55 _private prototype_ `void ScanNextReferencingPackage();`
- L56 _private prototype_ `void FinishScanning();`
- L58 _private prototype_ `TOptional<float> GetProgressBarPercent() const;`
- L60 _private prototype_ `TSharedRef<SWidget> BuildReferencerAssetPicker();`
- L61 _private prototype_ `bool OnShouldFilterReferencerAsset(const FAssetData& InAssetData) const;`
- L63 _private prototype_ `EVisibility GetNoReferencesVisibility() const;`
- L64 _private prototype_ `EVisibility GetReferencesVisiblity() const;`
- L65 _private prototype_ `EVisibility GetProgressBarVisibility() const;`
- L67 _private prototype_ `void OnAssetsActivated(const TArray<FAssetData>& ActivatedAssets, EAssetTypeActivationMethod::Type ActivationMethod);`
- L68 _private prototype_ `bool IsDeleteEnabled() const;`
- L69 _private prototype_ `FReply OnDeleteClicked();`
- L70 _private prototype_ `FReply OnCancelClicked();`
- L72 _private prototype_ `void CloseWindow();`
- L78 _private member_ `TWeakPtr<SWindow> WeakParentWindow;`
- L80 _private member_ `TArray<UObject*> ObjectsToDelete;`
- L82 _private member_ `EState State = EState::Waiting;`
- L84 _private member_ `TSet<FName> ReferencingPackages;`
- L85 _private member_ `TSet<FName> PossiblyReferencingPackages;`
- L86 _private member_ `bool bIsAnyReferencedInMemoryByNonUndo = false;`
- L87 _private member_ `bool bIsAnyReferencedInMemoryByUndo = false;`
- L89 _private member_ `TArray<FName> ReferencingPackagesToScan;`
- L90 _private member_ `int32 NextObjectToScan = INDEX_NONE;`
- L91 _private member_ `int32 NextPackageToScan = INDEX_NONE;`
- L93 _private member_ `bool bPerformDelete = false;`
- L94 _private member_ `bool bRenameObjectsAsTrash = false;`
- L95 _private member_ `FOnDeletedObject OnDeletedObject;`

#### enum `UE::Cameras::SDeleteCameraObjectDialog::EState`  
`enum class EState`  
_L76-76_
- L76 _public enumerator_ `enum class EState { Waiting, StartScanning, ScanNextObject, ScanNextReferencingPackage, FinishScanning }; TWeakPtr<SWindow> WeakParentWindow; TArray<UObject*> ObjectsToDelete; EState State = EState::Waiting;`
- L76 _public enumerator_ `enum class EState { Waiting, StartScanning, ScanNextObject, ScanNextReferencingPackage, FinishScanning }; TWeakPtr<SWindow> WeakParentWindow; TArray<UObject*> ObjectsToDelete; EState State = EState::Waiting;`
- L76 _public enumerator_ `enum class EState { Waiting, StartScanning, ScanNextObject, ScanNextReferencingPackage, FinishScanning }; TWeakPtr<SWindow> WeakParentWindow; TArray<UObject*> ObjectsToDelete; EState State = EState::Waiting;`
- L76 _public enumerator_ `enum class EState { Waiting, StartScanning, ScanNextObject, ScanNextReferencingPackage, FinishScanning }; TWeakPtr<SWindow> WeakParentWindow; TArray<UObject*> ObjectsToDelete; EState State = EState::Waiting;`
- L76 _public enumerator_ `enum class EState { Waiting, StartScanning, ScanNextObject, ScanNextReferencingPackage, FinishScanning }; TWeakPtr<SWindow> WeakParentWindow; TArray<UObject*> ObjectsToDelete; EState State = EState::Waiting;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace Cameras` (scope `UE`)
- L13 _delegate_ `DECLARE_DELEGATE_OneParam(FOnDeletedObject, UObject*);`
- L13 _prototype_ `DECLARE_DELEGATE_OneParam(FOnDeletedObject, UObject*);` (scope `UE::Cameras`)
