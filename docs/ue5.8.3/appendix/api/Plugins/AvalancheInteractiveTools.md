# Plugins / AvalancheInteractiveTools

- module root: `Plugins/VirtualProduction/Avalanche/Source/AvalancheInteractiveTools`
- headers: 25; symbols: 409
- symbol kinds: class=27, delegate=5, enum=4, enumerator=12, function=43, member=93, namespace=2, prototype=221, struct=1, typedef=1
- PrivateDependencyModuleNames: Avalanche, AvalancheInteractiveToolsRuntime, AvalancheText, AvalancheViewport, DeveloperSettings, EditorFramework, EditorInteractiveToolsFramework, InputCore, InteractiveToolsFramework, PlacementMode, Projects, ToolMenus, TypedElementRuntime, UnrealEd, WidgetRegistration
- PublicDependencyModuleNames: Core, CoreUObject, Engine, Slate, SlateCore

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheInteractiveTools/Private/AvaInteractiveToolsStyle.h` (Private)


#### class `FAvaInteractiveToolsStyle`  
`class FAvaInteractiveToolsStyle final : public FSlateStyleSet`  
_L7-18_
- inherits: `FSlateStyleSet`
- L10 _public function_ `static FAvaInteractiveToolsStyle& Get()`
- L16 _public prototype_ `FAvaInteractiveToolsStyle();`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheInteractiveTools/Private/AvalancheInteractiveToolsModule.h` (Private)


#### class `FAvalancheInteractiveToolsModule`  
`class FAvalancheInteractiveToolsModule : public IAvalancheInteractiveToolsModule, public FGCObject`  
_L11-77_
- inherits: `IAvalancheInteractiveToolsModule,FGCObject`
- L14 _public function_ `static FAvalancheInteractiveToolsModule& Get()`
- L20 _public function_ `static FAvalancheInteractiveToolsModule* GetPtr()`
- L27 _public prototype_ `virtual void StartupModule() override;`
- L28 _public prototype_ `virtual void ShutdownModule() override;`
- L32 _public prototype_ `virtual void RegisterCategory(FName InCategoryName, TSharedPtr<FUICommandInfo> InCategoryCommand, int32 InPlacementModeSortPriority = NoPlacementCategory) override;`
- L34 _public prototype_ `virtual void RegisterTool(FName InCategory, FAvaInteractiveToolsToolParameters&& InToolParams) override;`
- L35 _public prototype_ `virtual const TMap<FName, TSharedPtr<FUICommandInfo>>& GetCategories() override;`
- L36 _public prototype_ `virtual const TArray<FAvaInteractiveToolsToolParameters>* GetTools(FName InCategory) override;`
- L37 _public prototype_ `virtual const FAvaInteractiveToolsToolParameters* GetTool(const FString& InToolIdentifier) override;`
- L38 _public prototype_ `virtual FName GetToolCategory(const FString& InToolIdentifier) override;`
- L39 _public prototype_ `virtual bool HasActiveTool() const override;`
- L43 _public prototype_ `virtual void AddReferencedObjects(FReferenceCollector& InCollector) override;`
- L44 _public prototype_ `virtual FString GetReferencerName() const override;`
- L47 _public prototype_ `void OnToolActivated(const FString& InToolIdentifier);`
- L48 _public prototype_ `void OnToolDeactivated();`
- L49 _public prototype_ `FString GetActiveToolIdentifier() const;`
- L51 _public function_ `virtual FToolEvent::RegistrationType& OnToolActivation() override`
- L56 _public function_ `virtual FToolEvent::RegistrationType& OnToolDeactivation() override`
- L62 _private member_ `TMap<FName, TSharedPtr<FUICommandInfo>> Categories;`
- L63 _private member_ `TMap<FName, TArray<FAvaInteractiveToolsToolParameters>> Tools;`
- L64 _private member_ `TOptional<FString> ActiveToolIdentifier;`
- L65 _private member_ `FToolEvent OnToolActivationDelegate;`
- L66 _private member_ `FToolEvent OnToolDeactivationDelegate;`
- L68 _private prototype_ `void OnPostEngineInit();`
- L70 _private prototype_ `void BroadcastRegisterCategories();`
- L71 _private prototype_ `void RegisterDefaultCategories();`
- L73 _private prototype_ `void RegisterAutoRegisterTools();`
- L74 _private prototype_ `void BroadcastRegisterTools();`
- L76 _private prototype_ `void OnPlacementCategoryRefreshed(FName InCategory);`

#### Free symbols / members of external scopes

- L9 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogAvaInteractiveTools, Log, All);`
- L9 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogAvaInteractiveTools, Log, All);`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheInteractiveTools/Private/EdMode/AvaInteractiveToolsEdMode.h` (Private)


#### class `UAvaInteractiveToolsEdMode`  
`class UAvaInteractiveToolsEdMode : public UBaseLegacyWidgetEdMode`  
_L13-43_
- reflection: `UCLASS()`
- inherits: `UBaseLegacyWidgetEdMode`
- L18 _public prototype_ `UAvaInteractiveToolsEdMode();`
- L19 _public prototype_ `virtual ~UAvaInteractiveToolsEdMode() override = default;`
- L22 _public prototype_ `virtual bool IsCompatibleWith(FEditorModeID OtherModeID) const override;`
- L23 _public prototype_ `virtual void BindCommands() override;`
- L24 _public prototype_ `virtual void Enter() override;`
- L25 _public prototype_ `virtual void CreateToolkit() override;`
- L26 _public prototype_ `virtual TMap<FName, TArray<TSharedPtr<FUICommandInfo>>> GetModeCommands() const override;`
- L27 _public prototype_ `virtual void Exit() override;`
- L30 _public prototype_ `void OnToolPaletteChanged(FName InPaletteName);`
- L31 _public prototype_ `void OnToolSetup(UInteractiveTool* InTool);`
- L32 _public prototype_ `void OnToolShutdown(UInteractiveTool* InTool, EToolShutdownType InShutdownType);`
- L33 _public function_ `FString GetLastActiveTool() const`
- L34 _public function_ `double GetLastToolActivateTime() const`
- L35 _public prototype_ `void OnToolActivateEnd();`
- L38 _protected member_ `FString LastActiveTool;`
- L39 _protected member_ `TWeakObjectPtr<UTypedElementSelectionSet> WeakActorSelectionSet;`
- L40 _protected member_ `double LastToolActivateTime = -1.0;`
- L42 _protected prototype_ `void OnActorSelectionChange(const UTypedElementSelectionSet* InSelectionSet);`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheInteractiveTools/Private/EdMode/AvaInteractiveToolsEdModeToolkit.h` (Private)


#### class `FAvaInteractiveToolsEdModeToolkit`  
`class FAvaInteractiveToolsEdModeToolkit : public FModeToolkit`  
_L11-60_
- inherits: `FModeToolkit`
- L14 _public prototype_ `FAvaInteractiveToolsEdModeToolkit();`
- L17 _public prototype_ `void SetViewportToolbarVisibility(bool bInShow);`
- L18 _public function_ `bool GetViewportToolbarVisibility() const`
- L25 _protected prototype_ `virtual FName GetToolkitFName() const override;`
- L26 _protected prototype_ `virtual FText GetBaseToolkitName() const override;`
- L27 _protected prototype_ `virtual TSharedPtr<SWidget> GetInlineContent() const override;`
- L31 _protected prototype_ `virtual void Init(const TSharedPtr<IToolkitHost>& InitToolkitHost, TWeakObjectPtr<UEdMode> InOwningMode) override;`
- L32 _protected prototype_ `virtual void GetToolPaletteNames(TArray<FName>& PaletteNames) const override;`
- L33 _protected prototype_ `virtual FText GetToolPaletteDisplayName(FName Palette) const override;`
- L34 _protected prototype_ `virtual void OnToolPaletteChanged(FName PaletteName) override;`
- L35 _protected function_ `virtual bool HasIntegratedToolPalettes() const override`
- L36 _protected function_ `virtual bool HasExclusiveToolPalettes() const override`
- L37 _protected prototype_ `virtual void OnToolStarted(UInteractiveToolManager* InManager, UInteractiveTool* InTool) override;`
- L38 _protected prototype_ `virtual void OnToolEnded(UInteractiveToolManager* InManager, UInteractiveTool* InTool) override;`
- L39 _protected prototype_ `virtual void InvokeUI() override;`
- L43 _protected prototype_ `virtual void RequestModeUITabs() override;`
- L48 _private prototype_ `void MakeViewportOverlayToolbar();` — Creates an viewport overlay toolbar
- L50 _private prototype_ `void MakeToolkitPalettes();`
- L52 _private prototype_ `FText GetToolWarningText() const;`
- L54 _private prototype_ `void OnSettingsChanged(UObject* InSettings, FPropertyChangedEvent& InEvent);`
- L55 _private prototype_ `void OnViewportChanged(TSharedPtr<IAssetViewport> InOldViewport, TSharedPtr<IAssetViewport> InNewViewport);`
- L57 _private member_ `TSharedPtr<SWidget> ToolkitWidget;`
- L58 _private member_ `TSharedPtr<SWidget> ViewportToolbarWidget;`
- L59 _private member_ `bool bViewportToolbarVisible = true;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheInteractiveTools/Private/Tools/AvaInteractiveToolsActorToolNull.h` (Private)


#### class `UAvaInteractiveToolsActorToolNull`  
`class UAvaInteractiveToolsActorToolNull : public UAvaInteractiveToolsActorPointToolBase`  
_L9-20_
- reflection: `UCLASS()`
- inherits: `UAvaInteractiveToolsActorPointToolBase`
- L14 _public prototype_ `UAvaInteractiveToolsActorToolNull();`
- L17 _public function_ `virtual bool UseIdentityRotation() const override`
- L18 _public prototype_ `virtual void OnRegisterTool(IAvalancheInteractiveToolsModule* InAITModule) override;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheInteractiveTools/Private/Tools/AvaInteractiveToolsActorToolSpline.h` (Private)


#### class `UAvaInteractiveToolsActorToolSpline`  
`class UAvaInteractiveToolsActorToolSpline : public UAvaInteractiveToolsActorPointToolBase`  
_L9-20_
- reflection: `UCLASS()`
- inherits: `UAvaInteractiveToolsActorPointToolBase`
- L14 _public prototype_ `UAvaInteractiveToolsActorToolSpline();`
- L17 _public function_ `virtual bool UseIdentityRotation() const override`
- L18 _public prototype_ `virtual void OnRegisterTool(IAvalancheInteractiveToolsModule* InAITModule) override;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheInteractiveTools/Private/Widgets/SAvaInteractiveToolsToolbarCategoryButton.h` (Private)


#### class `SAvaInteractiveToolsToolbarCategoryButton`  
`class SAvaInteractiveToolsToolbarCategoryButton : public SCompoundWidget`  
_L12-48_
- inherits: `SCompoundWidget`
- L15 _public function_ `SLATE_BEGIN_ARGS(SAvaInteractiveToolsToolbarCategoryButton)`
- L18 _public prototype_ `SLATE_ARGUMENT(FName, ToolCategory) SLATE_ARGUMENT(TSharedPtr<FUICommandInfo>, Command) SLATE_ARGUMENT(TSharedPtr<FUICommandList>, CommandList) SLATE_ARGUMENT(bool, ShowLabel) SLATE_END_ARGS() void Construct(const FArguments& InArgs);` — Category to retrieve ITF commands from
- L32 _protected prototype_ `virtual FReply OnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;`
- L35 _protected prototype_ `void CreateActiveCommandWidget();`
- L36 _protected prototype_ `void ShowCommandsContextMenu();`
- L37 _protected prototype_ `void HideCommandsContextMenu();`
- L39 _protected prototype_ `void OnToolActivated(const FString& InToolIdentifier);`
- L42 _private member_ `TSharedPtr<FUICommandInfo> Command;`
- L43 _private member_ `TSharedPtr<FUICommandList> CommandList;`
- L44 _private member_ `TSharedPtr<IMenu> ContextMenu;`
- L45 _private member_ `bool bShowLabel = false;`
- L46 _private member_ `FName ToolCategory = NAME_None;`
- L47 _private member_ `FString ActiveToolIdentifier;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheInteractiveTools/Public/AvaInteractiveToolsCommands.h` (Public)


#### class `FAvaInteractiveToolsCommands`  
`class FAvaInteractiveToolsCommands : public TCommands<FAvaInteractiveToolsCommands>`  
_L7-36_
- inherits: `TCommands<FAvaInteractiveToolsCommands>`
- L10 _public prototype_ `static const FAvaInteractiveToolsCommands* GetExternal();`
- L12 _public prototype_ `FAvaInteractiveToolsCommands();`
- L15 _public prototype_ `virtual void RegisterCommands() override;`
- L18 _public prototype_ `void RegisterEdModeCommands();`
- L19 _public prototype_ `void RegisterCategoryCommands();`
- L20 _public prototype_ `void RegisterActorCommands();`
- L23 _public member_ `TSharedPtr<FUICommandInfo> CancelActiveTool;` — Ed Mode
- L24 _public member_ `TSharedPtr<FUICommandInfo> ToggleViewportToolbar;`
- L25 _public member_ `TSharedPtr<FUICommandInfo> OpenViewportToolbarSettings;`
- L28 _public member_ `TSharedPtr<FUICommandInfo> Category_2D;` — Categories
- L29 _public member_ `TSharedPtr<FUICommandInfo> Category_3D;`
- L30 _public member_ `TSharedPtr<FUICommandInfo> Category_Actor;`
- L31 _public member_ `TSharedPtr<FUICommandInfo> Category_Cloner;`
- L32 _public member_ `TSharedPtr<FUICommandInfo> Category_Effector;`
- L34 _public member_ `TSharedPtr<FUICommandInfo> Tool_Actor_Null;`
- L35 _public member_ `TSharedPtr<FUICommandInfo> Tool_Actor_Spline;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheInteractiveTools/Public/AvaInteractiveToolsDelegates.h` (Public)


#### class `FAvaInteractiveToolsDelegates`  
`class FAvaInteractiveToolsDelegates`  
_L13-19_
- L16 _public prototype_ `static FAvaInteractiveToolsRegisterToolsDelegate& GetRegisterToolsDelegate();`
- L18 _public prototype_ `static FAvaInteractiveToolsRegisterCategoriesDelegate& GetRegisterCategoriesDelegate();`

#### Free symbols / members of external scopes

- L10 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FAvaInteractiveToolsRegisterCategoriesDelegate, IAvalancheInteractiveToolsModule*) DECLARE_MULTICAST_DELEGATE_OneParam(FAvaInteractiveToolsRegisterToolsDelegate, IAvalancheInteractiveToolsModule*);`
- L10 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FAvaInteractiveToolsRegisterCategoriesDelegate, IAvalancheInteractiveToolsModule*) DECLARE_MULTICAST_DELEGATE_OneParam(FAvaInteractiveToolsRegisterToolsDelegate, IAvalancheInteractiveToolsModule*);`
- L11 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FAvaInteractiveToolsRegisterToolsDelegate, IAvalancheInteractiveToolsModule*);`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheInteractiveTools/Public/AvaInteractiveToolsSettings.h` (Public)


#### enum `EAvaInteractiveToolsDefaultActionAlignment`  
`enum class EAvaInteractiveToolsDefaultActionAlignment : uint8`  
_L9-13_
- reflection: `UENUM()`
- L11 _public enumerator_ `Axis`
- L12 _public enumerator_ `Camera`

#### enum `EAvaInteractiveToolsViewportToolbarPosition`  
`enum class EAvaInteractiveToolsViewportToolbarPosition : uint8`  
_L16-28_
- reflection: `UENUM()`
- L19 _public enumerator_ `None` — Disabled
- L21 _public enumerator_ `Bottom` — Horizontal
- L23 _public enumerator_ `Top` — Horizontal
- L25 _public enumerator_ `Left` — Vertical
- L27 _public enumerator_ `Right` — Vertical

#### class `UAvaInteractiveToolsSettings`  
`class UAvaInteractiveToolsSettings : public UDeveloperSettings`  
_L31-68_
- reflection: `UCLASS(Config = EditorPerProjectUserSettings, meta = (DisplayName = "Interactive Tools"))`
- inherits: `UDeveloperSettings`
- L36 _public prototype_ `static bool IsViewportToolbarProperty(FName InPropertyName);`
- L38 _public prototype_ `static UAvaInteractiveToolsSettings* Get();`
- L40 _public prototype_ `UAvaInteractiveToolsSettings();`
- L43 _public prototype_ `void OpenEditorSettingsWindow() const;` — Open these settings in the editor
- L46 _public prototype_ `bool IsViewportToolbarSupported() const;` — Checks if active mode supports viewport toolbar
- L49 _public prototype_ `void SetViewportToolbarVisible(bool bInVisible) const;` — Set visibility of viewport toolbar
- L52 _public prototype_ `bool GetViewportToolbarVisible() const;` — Get visibility of viewport toolbar
- L56 _public member_ `float CameraDistance = 500.f;` — `UPROPERTY(Config, EditAnywhere, Category = "Motion Design")` — Distance from the camera at which actors are created.
- L59 _public member_ `EAvaInteractiveToolsDefaultActionAlignment DefaultActionActorAlignment = EAvaInteractiveToolsDefaultActionAlignment::Axis;` — `UPROPERTY(Config, EditAnywhere, Category = "Motion Design")`
- L63 _public member_ `EAvaInteractiveToolsViewportToolbarPosition ViewportToolbarPosition = EAvaInteractiveToolsViewportToolbarPosition::Bottom;` — `UPROPERTY(Config, EditAnywhere, Category = "Motion Design")` — Position of the viewport overlay toolbar position
- L67 _public member_ `bool bViewportToolbarLabelEnabled = false;` — `UPROPERTY(Config, EditAnywhere, Category = "Motion Design")` — Show viewport overlay toolbar label under each item

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheInteractiveTools/Public/Behaviors/AvaSingleClickAndDragBehavior.h` (Public)


#### class `IAvaSingleClickAndDragBehaviorTarget`  
`class IAvaSingleClickAndDragBehaviorTarget : public IModifierToggleBehaviorTarget`  
_L19-59_
- inherits: `IModifierToggleBehaviorTarget`
- desc: Functions required to apply standard "Click" and "Click-Drag" state machines to a target object.
- L22 _public function_ `virtual ~IAvaSingleClickAndDragBehaviorTarget()`
- L29 _public prototype_ `virtual FInputRayHit CanBeginSingleClickAndDragSequence(const FInputDeviceRay& InPressPos) = 0;` — Test if target can begin click-drag interaction at this point @param PressPos device position/ray at click point @return hit information at this point
- L35 _public prototype_ `virtual void OnClickPress(const FInputDeviceRay& InPressPos) = 0;` — Notify Target that click press ocurred @param PressPos device position/ray at click point
- L41 _public prototype_ `virtual void OnDragStart(const FInputDeviceRay& InDragPos) = 0;` — Notify Target that the drag process has started @param DragPos device position/ray at move point
- L47 _public prototype_ `virtual void OnClickDrag(const FInputDeviceRay& InDragPos) = 0;` — Notify Target that input position has changed @param DragPos device position/ray at click point
- L53 _public prototype_ `virtual void OnClickRelease(const FInputDeviceRay& InReleasePos, bool bInIsDragOperation) = 0;` — Notify Target that click release occurred @param ReleasePos device position/ray at click point
- L58 _public prototype_ `virtual void OnTerminateSingleClickAndDragSequence() = 0;` — Notify Target that click-drag sequence has been explicitly terminated (eg by escape key)

#### class `UAvaSingleClickAndDragBehavior`  
`class UAvaSingleClickAndDragBehavior : public UAnyButtonInputBehavior`  
_L79-168_
- reflection: `UCLASS()`
- inherits: `UAnyButtonInputBehavior`
- desc: UAvaSingleClickAndDragInputBehavior implements a combination of "button-click" and "button-click-drag"-style input behavior. If the mouse is moved away from the original location, and update will occur and a drag operation will start. If the mouse is released without moving too far away, a click event will occur. Once the drag has started, returning to the original location will not produce a click event will not be produced, but the drag operation will continue. An IAvaSingleClickAndDragBehaviorTarget instance must be provided which is manipulated by this behavior. The state machine works as follows: 1) on input-device-button-press, call Target::CanBeginSingleClickDragSequence to determine if capture should begin 2) on input-device-move, call Target::OnClickDrag if drag mode has been started or Target::OnDragStart if it crosses that threshold. 3) on input-device-button-release, call Target::OnClickRelease If a ForceEndCapture occurs we call Target::OnTerminateDragClickSequence
- L84 _public prototype_ `UAvaSingleClickAndDragBehavior();`
- L89 _public member_ `FInputBehaviorModifierStates Modifiers;` — The modifier set for this behavior
- L95 _public prototype_ `virtual void Initialize(IAvaSingleClickAndDragBehaviorTarget* InTarget);` — Initialize this behavior with the given Target @param Target implementor of hit-test and on-clicked functions
- L100 _public member_ `TFunction<bool(const FInputDeviceState&)> ModifierCheckFunc = nullptr;` — WantsCapture() will only return capture request if this function returns true (or is null)
- L103 _public prototype_ `virtual FInputCaptureRequest WantsCapture(const FInputDeviceState& InInput) override;`
- L104 _public prototype_ `virtual FInputCaptureUpdate BeginCapture(const FInputDeviceState& InInput, EInputCaptureSide InSide) override;`
- L105 _public prototype_ `virtual FInputCaptureUpdate UpdateCapture(const FInputDeviceState& InInput, const FInputCaptureData& InData) override;`
- L106 _public prototype_ `virtual void ForceEndCapture(const FInputCaptureData& InData) override;`
- L109 _public function_ `const FInputDeviceRay& GetInitialMouseDownRay() const`
- L115 _public member_ `bool bSupportsDrag = true;` — `UPROPERTY()` — If false, will never change into a drag event.
- L122 _public member_ `bool bDistanceTestClick = true;` — `UPROPERTY()` — If drag is not supported, then check distance when releasing the button. The distance used is the drag start distance.
- L130 _public member_ `bool bUpdateModifiersDuringDrag = false;` — `UPROPERTY()` — If true, then we will update Modifier states in UpdateCapture(). This defaults to false because in most cases during a capture you don't want this, eg in a brush interaction, if you have a shift-to-smooth modifier, you don't want to toggle this on/off during a sculpting stroke.
- L134 _public member_ `float DragStartDistance = 5.f;` — `UPROPERTY()` — The distance the mouse has to travel to trigger a drag.
- L138 _protected member_ `IAvaSingleClickAndDragBehaviorTarget* Target;` — Click Target object
- L141 _protected member_ `bool bInClickDrag = false;` — set to true if we are in a capture
- L144 _protected member_ `bool bIsDragOperation = false;` — Set to true if this is a drag operation.
- L147 _protected member_ `FInputDeviceRay InitialMouseDownRay;` — The initial mouse down position.
- L152 _protected prototype_ `virtual void OnClickPressInternal(const FInputDeviceState& InInput, EInputCaptureSide InSide);` — Internal function that forwards click evens to Target::OnClickPress, you can customize behavior here
- L157 _protected prototype_ `virtual void OnDragStartedInternal(const FInputDeviceState& InInput, const FInputCaptureData& InData);` — Internal function that forwards click evens to Target::OnDragStarted, you can customize behavior here
- L162 _protected prototype_ `virtual void OnClickDragInternal(const FInputDeviceState& InInput, const FInputCaptureData& InData);` — Internal function that forwards click evens to Target::OnClickDrag, you can customize behavior here
- L167 _protected prototype_ `virtual void OnClickReleaseInternal(const FInputDeviceState& InInput, const FInputCaptureData& InData);` — Internal function that forwards click evens to Target::OnClickRelease, you can customize behavior here

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheInteractiveTools/Public/Builders/AvaInteractiveToolsActorToolBuilder.h` (Public)


#### class `UAvaInteractiveToolsActorToolBuilder`  
`class UAvaInteractiveToolsActorToolBuilder : public UAvaInteractiveToolsToolBuilder`  
_L18-64_
- reflection: `UCLASS()`
- inherits: `UAvaInteractiveToolsToolBuilder`
- L23 _public prototype_ `static FAvaInteractiveToolsToolParameters CreateToolParameters(FName InCategory, TSharedPtr<FUICommandInfo> InCommand, const FString& InIdentifier, int32 InPriority, TSubclassOf<AActor> InActorClass, TSubclassOf<UAvaInteractiveToolsActorTool> InToolClass = UAvaInteractiveToolsActorTool::StaticClass());`
- L28 _public function_ `template<class InActorClass> static FAvaInteractiveToolsToolParameters CreateToolParameters(FName InCategory, TSharedPtr<FUICommandInfo> InCommand, const FString& InIdentifier, int32 InPriority, TSubclassOf<UAvaInteractiveToolsActorTool> InToolClass = UAvaInteractiveToolsActorTool::StaticClass())`
- L35 _public prototype_ `static UAvaInteractiveToolsActorToolBuilder* CreateActorToolBuilder(UEdMode* InEdMode, FName InCategory, TSharedPtr<FUICommandInfo> InCommand, const FString& InIdentifier, int32 InPriority, TSubclassOf<AActor> InActorClass, TSubclassOf<UAvaInteractiveToolsActorTool> InToolClass = UAvaInteractiveToolsActorTool::StaticClass());`
- L40 _public function_ `template<class InActorClass> static UAvaInteractiveToolsActorToolBuilder* CreateActorToolBuilder(UEdMode* InEdMode, FName InCategory, TSharedPtr<FUICommandInfo> InCommand, const FString& InIdentifier, int32 InPriority, TSubclassOf<UAvaInteractiveToolsActorTool> InToolClass = UAvaInteractiveToolsActorTool::StaticClass())`
- L48 _public prototype_ `virtual UInteractiveTool* BuildTool(const FToolBuilderState& SceneState) const override;`
- L52 _private member_ `FName Category;`
- L53 _private member_ `TSharedPtr<FUICommandInfo> Command;`
- L54 _private member_ `FString Identifier;`
- L55 _private member_ `int32 Priority;`
- L58 _private member_ `TSubclassOf<AActor> ActorClass;` — `UPROPERTY()`
- L61 _private member_ `TSubclassOf<UAvaInteractiveToolsActorTool> ToolClass;` — `UPROPERTY()`
- L63 _private prototype_ `UAvaInteractiveToolsActorToolBuilder();`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheInteractiveTools/Public/Builders/AvaInteractiveToolsStaticMeshActorToolBuilder.h` (Public)


#### class `UAvaInteractiveToolsStaticMeshActorToolBuilder`  
`class UAvaInteractiveToolsStaticMeshActorToolBuilder : public UAvaInteractiveToolsToolBuilder`  
_L18-53_
- reflection: `UCLASS()`
- inherits: `UAvaInteractiveToolsToolBuilder`
- L23 _public prototype_ `static FAvaInteractiveToolsToolParameters CreateToolParameters(FName InCategory, TSharedPtr<FUICommandInfo> InCommand, const FString& InIdentifier, int32 InPriority, UStaticMesh* InStaticMesh, TSubclassOf<UAvaInteractiveToolsStaticMeshActorTool> InToolClass = UAvaInteractiveToolsStaticMeshActorTool::StaticClass());`
- L27 _public prototype_ `static FAvaInteractiveToolsToolParameters CreateToolParameters(FName InCategory, TSharedPtr<FUICommandInfo> InCommand, const FString& InIdentifier, int32 InPriority, const TCHAR* InStaticMeshPath, TSubclassOf<UAvaInteractiveToolsStaticMeshActorTool> InToolClass = UAvaInteractiveToolsStaticMeshActorTool::StaticClass());`
- L31 _public prototype_ `static UAvaInteractiveToolsStaticMeshActorToolBuilder* CreateStaticMeshActorToolBuilder(UEdMode* InEdMode, FName InCategory, TSharedPtr<FUICommandInfo> InCommand, const FString& InIdentifier, int32 InPriority, UStaticMesh* InStaticMesh, TSubclassOf<UAvaInteractiveToolsStaticMeshActorTool> InToolClass = UAvaInteractiveToolsStaticMeshActorTool::StaticClass());`
- L35 _public prototype_ `static UAvaInteractiveToolsStaticMeshActorToolBuilder* CreateStaticMeshActorToolBuilder(UEdMode* InEdMode, FName InCategory, TSharedPtr<FUICommandInfo> InCommand, const FString& InIdentifier, int32 InPriority, const TCHAR* InStaticMeshPath, TSubclassOf<UAvaInteractiveToolsStaticMeshActorTool> InToolClass = UAvaInteractiveToolsStaticMeshActorTool::StaticClass());`
- L40 _public prototype_ `virtual UInteractiveTool* BuildTool(const FToolBuilderState& SceneState) const override;`
- L44 _private member_ `FName Category;`
- L45 _private member_ `TSharedPtr<FUICommandInfo> Command;`
- L46 _private member_ `FString Identifier;`
- L47 _private member_ `int32 Priority;`
- L50 _private member_ `TObjectPtr<UStaticMesh> StaticMesh;` — `UPROPERTY()`
- L52 _private prototype_ `UAvaInteractiveToolsStaticMeshActorToolBuilder();`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheInteractiveTools/Public/Builders/AvaInteractiveToolsToolBuilder.h` (Public)


#### class `UAvaInteractiveToolsToolBuilder`  
`class UAvaInteractiveToolsToolBuilder : public UInteractiveToolBuilder`  
_L12-34_
- reflection: `UCLASS()`
- inherits: `UInteractiveToolBuilder`
- L17 _public prototype_ `static UAvaInteractiveToolsToolBuilder* CreateToolBuilder(UEdMode* InEdMode, TSubclassOf<UAvaInteractiveToolsToolBase> InToolClass);`
- L20 _public function_ `template<class InToolClass> static UAvaInteractiveToolsToolBuilder* CreateToolBuilder(UEdMode* InEdMode)`
- L26 _public function_ `virtual bool CanBuildTool(const FToolBuilderState& SceneState) const override`
- L27 _public prototype_ `virtual UInteractiveTool* BuildTool(const FToolBuilderState& SceneState) const override;`
- L31 _protected member_ `TSubclassOf<UAvaInteractiveToolsToolBase> ToolClass;`
- L33 _protected prototype_ `UAvaInteractiveToolsToolBuilder();`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheInteractiveTools/Public/IAvalancheInteractiveToolsModule.h` (Public)


#### struct `FAvaInteractiveToolsToolParameters`  
`struct FAvaInteractiveToolsToolParameters`  
_L25-32_
- L27 _public member_ `TSharedPtr<FUICommandInfo> UICommand = nullptr;`
- L28 _public member_ `FString ToolIdentifier = "";`
- L29 _public member_ `int32 Priority = 0;`
- L30 _public member_ `FAvalancheInteractiveToolsCreateBuilder CreateBuilder;`
- L31 _public member_ `TVariant<TSubclassOf<AActor>, TObjectPtr<UActorFactory>> ActorFactory;`

#### class `IAvalancheInteractiveToolsModule`  
`class IAvalancheInteractiveToolsModule : public IModuleInterface`  
_L39-82_
- inherits: `IModuleInterface`
- L42 _public member_ `static const inline FEditorModeID EM_AvaInteractiveToolsEdModeId = TEXT("EM_`
- L43 _public member_ `static constexpr int32 NoPlacementCategory = -1;`
- L45 _public member_ `static const inline FName CategoryName2D = FName(TEXT("AvaT`
- L46 _public member_ `static const inline FName CategoryName3D = FName(TEXT("AvaT`
- L47 _public member_ `static const inline FName CategoryNameActor = FName(TEXT("AvaT`
- L48 _public member_ `static const inline FName CategoryNameCloner = FName(TEXT("AvaT`
- L49 _public member_ `static const inline FName CategoryNameEffector = FName(TEXT("AvaT`
- L51 _public function_ `static IAvalancheInteractiveToolsModule& Get()`
- L57 _public function_ `static IAvalancheInteractiveToolsModule* GetPtr()`
- L64 _public prototype_ `virtual void RegisterCategory(FName InCategoryName, TSharedPtr<FUICommandInfo> InCategoryCommand, int32 InPlacementModeSortPriority = NoPlacementCategory) = 0;` — -1 on the sort priority skips the placement mode tab.
- L67 _public prototype_ `virtual const TMap<FName, TSharedPtr<FUICommandInfo>>& GetCategories() = 0;`
- L69 _public prototype_ `virtual void RegisterTool(FName InCategory, FAvaInteractiveToolsToolParameters&& InToolParams) = 0;`
- L71 _public prototype_ `virtual const TArray<FAvaInteractiveToolsToolParameters>* GetTools(FName InCategory) = 0;`
- L73 _public prototype_ `virtual const FAvaInteractiveToolsToolParameters* GetTool(const FString& InToolIdentifier) = 0;`
- L75 _public prototype_ `virtual FName GetToolCategory(const FString& InToolIdentifier) = 0;`
- L77 _public prototype_ `virtual bool HasActiveTool() const = 0;`
- L79 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FToolEvent, const FString& ) virtual FToolEvent::RegistrationType& OnToolActivation() = 0;`
- L81 _public prototype_ `virtual FToolEvent::RegistrationType& OnToolDeactivation() = 0;`

#### Free symbols / members of external scopes

- L23 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(UInteractiveToolBuilder*, FAvalancheInteractiveToolsCreateBuilder, UEdMode*) struct FAvaInteractiveToolsToolParameters { TSharedPtr<FUICommandInfo> UICommand = nullptr; FString ToolIdentifier = ""; int32 Priority = 0; FAvalancheInteractiveToolsCreateBuilder CreateBuilder; TVariant<TSubclassOf<AActor>, TObjectPtr<UActorFactory>> ActorFactory; };`
- L34 _namespace_ `namespace UE`
- L34 _namespace_ `namespace AvaInteractiveTools` (scope `UE`)
- L36 _typedef_ `using FAvaInteractiveToolsCategoryToolMap = TMap<FName, TArray<FAvaInteractiveToolsToolParameters>>;` (scope `UE::AvaInteractiveTools`)
- L79 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FToolEvent, const FString& ) virtual FToolEvent::RegistrationType& OnToolActivation() = 0;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheInteractiveTools/Public/Planners/AvaInteractiveToolsToolViewportAreaPlanner.h` (Public)


#### class `UAvaInteractiveToolsToolViewportAreaPlanner`  
`class UAvaInteractiveToolsToolViewportAreaPlanner : public UAvaInteractiveToolsToolViewportPlanner`  
_L9-48_
- reflection: `UCLASS(BlueprintType, Blueprintable)`
- inherits: `UAvaInteractiveToolsToolViewportPlanner`
- L14 _public function_ `const FVector2f& GetStartPosition() const`
- L15 _public prototype_ `void SetStartPosition(const FVector2f& InStartPosition);`
- L16 _public function_ `const FVector2f& GetEndPosition() const`
- L17 _public prototype_ `void SetEndPosition(const FVector2f& InEndPosition);`
- L18 _public prototype_ `FVector2f GetCenterPosition() const;`
- L19 _public prototype_ `FVector2f GetTopLeftCorner() const;`
- L20 _public prototype_ `FVector2f GetTopRightCorner() const;`
- L21 _public prototype_ `FVector2f GetBottomLeftCorner() const;`
- L22 _public prototype_ `FVector2f GetBottomRightCorner() const;`
- L23 _public prototype_ `FVector2f GetSize() const;`
- L24 _public prototype_ `FVector GetStartPositionWorld() const;`
- L25 _public prototype_ `FVector GetEndPositionWorld() const;`
- L26 _public prototype_ `FVector GetTopLeftCornerWorld() const;`
- L27 _public prototype_ `FVector GetTopRightCornerWorld() const;`
- L28 _public prototype_ `FVector GetBottomLeftCornerWorld() const;`
- L29 _public prototype_ `FVector GetBottomRightCornerWorld() const;`
- L30 _public prototype_ `FVector2D GetWorldSize() const;`
- L32 _public prototype_ `FVector ViewportToWorldPosition(const FVector2f& InViewportPosition) const;`
- L35 _public prototype_ `virtual void Setup(UAvaInteractiveToolsToolBase* InTool) override;`
- L36 _public prototype_ `virtual void OnTick(float InDeltaTime) override;`
- L37 _public prototype_ `virtual void DrawHUD(FCanvas* InCanvas, IToolsContextRenderAPI* InRenderAPI) override;`
- L38 _public prototype_ `virtual void OnClicked(const FInputDeviceRay& InClickPos) override;`
- L39 _public function_ `virtual bool HasStarted() const override`
- L43 _protected member_ `bool bStartedAreaPlanning;`
- L44 _protected member_ `FVector2f StartPosition;`
- L45 _protected member_ `FVector2f EndPosition;`
- L47 _protected prototype_ `void UpdateEndPosition(const FVector2f& InNewPosition);`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheInteractiveTools/Public/Planners/AvaInteractiveToolsToolViewportPlanner.h` (Public)


#### class `UAvaInteractiveToolsToolViewportPlanner`  
`class UAvaInteractiveToolsToolViewportPlanner : public UObject`  
_L20-52_
- reflection: `UCLASS(Abstract, BlueprintType, Blueprintable)`
- inherits: `UObject`
- L25 _public prototype_ `UAvaInteractiveToolsToolViewportPlanner();`
- L26 _public prototype_ `virtual void Setup(UAvaInteractiveToolsToolBase* InTool);`
- L27 _public function_ `virtual void DrawHUD(FCanvas* InCanvas, IToolsContextRenderAPI* InRenderAPI)`
- L28 _public function_ `virtual void Render(IToolsContextRenderAPI* InRenderAPI)`
- L29 _public function_ `virtual void OnTick(float InDeltaTime)`
- L30 _public function_ `virtual void OnClicked(const FInputDeviceRay& InClickPos)`
- L31 _public prototype_ `virtual void Shutdown(EToolShutdownType ShutdownType);`
- L32 _public prototype_ `virtual bool HasStarted() const PURE_VIRTUAL(UAvaInteractiveToolsToolViewportPlanner::HasStarted, return false;) FViewport* GetViewport(EAvaViewportStatus InViewportStatus) const;`
- L38 _protected member_ `static constexpr float MinDim = 5;` — The minimum dimension for things
- L41 _protected member_ `TObjectPtr<UAvaInteractiveToolsToolBase> Tool;` — `UPROPERTY()`
- L43 _protected member_ `bool bAttemptedToCreateSnapOperation;`
- L44 _protected member_ `TSharedPtr<FAvaSnapOperation> SnapOperation;`
- L46 _protected prototype_ `FVector2f GetConstrainedMousePosition() const;`
- L47 _protected prototype_ `FVector2f GetConstrainedMousePosition(const FVector2f& InClickPos) const;`
- L48 _protected prototype_ `FVector2f GetConstrainedMousePosition(FViewport* InViewport) const;`
- L50 _protected prototype_ `void StartSnapOperation();`
- L51 _protected prototype_ `void SnapLocation(FVector2f& InOutLocation);`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheInteractiveTools/Public/Planners/AvaInteractiveToolsToolViewportPointListPlanner.h` (Public)


#### enum `EAvaInteractiveToolsToolViewportPointListPlannerLineStatus`  
`enum class EAvaInteractiveToolsToolViewportPointListPlannerLineStatus : uint8`  
_L9-14_
- reflection: `UENUM(BlueprintType)`
- L11 _public enumerator_ `Neutral`
- L12 _public enumerator_ `Allowed`
- L13 _public enumerator_ `Disallowed`

#### class `UAvaInteractiveToolsToolViewportPointListPlanner`  
`class UAvaInteractiveToolsToolViewportPointListPlanner : public UAvaInteractiveToolsToolViewportPlanner`  
_L17-48_
- reflection: `UCLASS(BlueprintType, Blueprintable)`
- inherits: `UAvaInteractiveToolsToolViewportPlanner`
- L22 _public function_ `const FVector2f& GetCurrentViewportPosition() const`
- L24 _public prototype_ `void OverrideCurrentViewportPosition(const FVector2f InPosition);`
- L26 _public function_ `const TArray<FVector2f>& GetViewportPositions() const`
- L28 _public function_ `TArray<FVector2f>& GetViewportPositions()`
- L30 _public prototype_ `void AddViewportPosition(const FVector2f& InViewportPosition);`
- L32 _public function_ `EAvaInteractiveToolsToolViewportPointListPlannerLineStatus GetLineStatus() const`
- L34 _public prototype_ `void SetLineStatus(EAvaInteractiveToolsToolViewportPointListPlannerLineStatus InLineStatus);`
- L37 _public prototype_ `virtual void Setup(UAvaInteractiveToolsToolBase* InTool) override;`
- L38 _public prototype_ `virtual void OnTick(float InDeltaTime) override;`
- L39 _public prototype_ `virtual void DrawHUD(FCanvas* InCanvas, IToolsContextRenderAPI* InRenderAPI) override;`
- L40 _public prototype_ `virtual void OnClicked(const FInputDeviceRay& InClickPos) override;`
- L41 _public function_ `virtual bool HasStarted() const override`
- L45 _protected member_ `TArray<FVector2f> ViewportPositions;`
- L46 _protected member_ `FVector2f CurrentViewportPosition;`
- L47 _protected member_ `EAvaInteractiveToolsToolViewportPointListPlannerLineStatus LineStatus;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheInteractiveTools/Public/Planners/AvaInteractiveToolsToolViewportPointPlanner.h` (Public)


#### class `UAvaInteractiveToolsToolViewportPointPlanner`  
`class UAvaInteractiveToolsToolViewportPointPlanner : public UAvaInteractiveToolsToolViewportPlanner`  
_L9-26_
- reflection: `UCLASS(BlueprintType, Blueprintable)`
- inherits: `UAvaInteractiveToolsToolViewportPlanner`
- L14 _public function_ `const FVector2f& GetViewportPosition() const`
- L15 _public prototype_ `void SetViewportPosition(const FVector2f& InViewportPosition);`
- L18 _public prototype_ `virtual void Setup(UAvaInteractiveToolsToolBase* InTool) override;`
- L19 _public prototype_ `virtual void OnTick(float InDeltaTime) override;`
- L20 _public prototype_ `virtual void OnClicked(const FInputDeviceRay& InClickPos) override;`
- L21 _public function_ `virtual bool HasStarted() const override` — Start is also the end
- L25 _protected member_ `FVector2f ViewportPosition;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheInteractiveTools/Public/Tools/AvaInteractiveToolsActorAreaToolBase.h` (Public)


#### class `UAvaInteractiveToolsActorAreaToolBase`  
`class UAvaInteractiveToolsActorAreaToolBase : public UAvaInteractiveToolsActorToolBase`  
_L9-32_
- reflection: `UCLASS(Abstract)`
- inherits: `UAvaInteractiveToolsActorToolBase`
- L16 _public prototype_ `UAvaInteractiveToolsActorAreaToolBase();`
- L19 _public prototype_ `virtual void OnViewportPlannerUpdate() override;`
- L20 _public prototype_ `virtual void OnViewportPlannerComplete() override;`
- L24 _protected member_ `FVector OriginalActorSize;`
- L26 _protected prototype_ `void SetActorScale(AActor* InActor) const;`
- L29 _protected prototype_ `virtual AActor* SpawnActor(TSubclassOf<AActor> InActorClass, EAvaViewportStatus InViewportStatus, const FVector2f& InViewportPosition, bool bInPreview, FString* InActorLabelOverride = nullptr) override;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheInteractiveTools/Public/Tools/AvaInteractiveToolsActorPointToolBase.h` (Public)


#### class `UAvaInteractiveToolsActorPointToolBase`  
`class UAvaInteractiveToolsActorPointToolBase : public UAvaInteractiveToolsActorToolBase`  
_L9-20_
- reflection: `UCLASS(Abstract)`
- inherits: `UAvaInteractiveToolsActorToolBase`
- L14 _public prototype_ `UAvaInteractiveToolsActorPointToolBase();`
- L17 _public prototype_ `virtual void OnViewportPlannerUpdate() override;`
- L18 _public prototype_ `virtual void OnViewportPlannerComplete() override;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheInteractiveTools/Public/Tools/AvaInteractiveToolsActorTool.h` (Public)


#### class `UAvaInteractiveToolsActorTool`  
`class UAvaInteractiveToolsActorTool : public UAvaInteractiveToolsActorPointToolBase`  
_L15-33_
- reflection: `UCLASS()`
- inherits: `UAvaInteractiveToolsActorPointToolBase`
- L22 _public prototype_ `UAvaInteractiveToolsActorTool();`
- L25 _public prototype_ `virtual void OnRegisterTool(IAvalancheInteractiveToolsModule* InAITModule) override;`
- L29 _protected member_ `FName Category;`
- L30 _protected member_ `TSharedPtr<FUICommandInfo> Command;`
- L31 _protected member_ `FString Identifier;`
- L32 _protected member_ `int32 Priority = 0;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheInteractiveTools/Public/Tools/AvaInteractiveToolsActorToolBase.h` (Public)


#### class `UAvaInteractiveToolsActorToolBase`  
`class UAvaInteractiveToolsActorToolBase : public UAvaInteractiveToolsToolBase`  
_L10-28_
- reflection: `UCLASS(Abstract)`
- inherits: `UAvaInteractiveToolsToolBase`
- L18 _protected member_ `TSubclassOf<AActor> ActorClass = nullptr;` — `UPROPERTY()`
- L21 _protected prototype_ `virtual bool OnBegin() override;`
- L22 _protected prototype_ `virtual void DefaultAction() override;`
- L23 _protected function_ `virtual bool UseIdentityLocation() const override`
- L24 _protected prototype_ `virtual bool UseIdentityRotation() const override;`
- L27 _protected prototype_ `FAvaInteractiveToolsToolParameters CreateDefaultToolParameters() const;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheInteractiveTools/Public/Tools/AvaInteractiveToolsStaticMeshActorTool.h` (Public)


#### class `UAvaInteractiveToolsStaticMeshActorTool`  
`class UAvaInteractiveToolsStaticMeshActorTool : public UAvaInteractiveToolsActorTool`  
_L14-35_
- reflection: `UCLASS()`
- inherits: `UAvaInteractiveToolsActorTool`
- L21 _public prototype_ `UAvaInteractiveToolsStaticMeshActorTool();`
- L24 _public prototype_ `virtual void OnRegisterTool(IAvalancheInteractiveToolsModule* InAITModule) override;`
- L29 _protected member_ `TObjectPtr<UStaticMesh> StaticMesh;` — `UPROPERTY()`
- L32 _protected prototype_ `virtual AActor* SpawnActor(TSubclassOf<AActor> InActorClass, EAvaViewportStatus InViewportStatus, const FVector2f& InViewportPosition, bool bInPreview, FString* InActorLabelOverride = nullptr) override;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheInteractiveTools/Public/Tools/AvaInteractiveToolsToolBase.h` (Public)


#### class `UAvaInteractiveToolsRightClickBehavior`  
`class UAvaInteractiveToolsRightClickBehavior : public USingleClickInputBehavior`  
_L21-29_
- reflection: `UCLASS()`
- inherits: `USingleClickInputBehavior`
- L26 _public prototype_ `UAvaInteractiveToolsRightClickBehavior();`
- L28 _public prototype_ `virtual void Clicked(const FInputDeviceState& Input, const FInputCaptureData& Data) override;`

#### enum `EAvaViewportStatus`  
`enum class EAvaViewportStatus : uint8`  
_L31-35_
- L33 _public enumerator_ `Hovered`
- L34 _public enumerator_ `Focused`

#### class `UAvaInteractiveToolsToolBase`  
`class UAvaInteractiveToolsToolBase : public UInteractiveTool #if CPP , public IAvaSingleClickAndDragBehaviorTarget , public IClickBehaviorTarget #endif`  
_L38-201_
- reflection: `UCLASS(Abstract)`
- inherits: `UInteractiveTool,IAvaSingleClickAndDragBehaviorTarget,IClickBehaviorTarget`
- L48 _public member_ `static constexpr int32 BID_Cancel = 1;` — Cancel Behavior ID
- L54 _public prototype_ `static UObject* GetDetailsObjectFromActor(AActor* InActor);` — Checks the given actor and its components against UAvaInteractiveToolsModeDetailsObject and UAvaInteractiveToolsModeDetailsObjectProvider.
- L56 _public prototype_ `virtual ~UAvaInteractiveToolsToolBase() override = default;`
- L59 _public prototype_ `virtual void Setup() override;`
- L60 _public prototype_ `virtual void Shutdown(EToolShutdownType ShutdownType) override;`
- L61 _public prototype_ `virtual void DrawHUD(FCanvas* InCanvas, IToolsContextRenderAPI* InRenderAPI) override;`
- L62 _public prototype_ `virtual void Render(IToolsContextRenderAPI* InRenderAPI) override;`
- L63 _public prototype_ `virtual void OnTick(float InDeltaTime) override;`
- L67 _public prototype_ `virtual bool SupportsDefaultAction() const;` — Returns true if this supports a default action.
- L69 _public prototype_ `FString GetActiveToolIdentifier() const;`
- L70 _public prototype_ `const FAvaInteractiveToolsToolParameters* GetActiveToolParameters() const;`
- L73 _public prototype_ `virtual void OnUpdateModifierState(int InModifierID, bool bInIsOn) override;`
- L77 _public prototype_ `virtual FInputRayHit CanBeginSingleClickAndDragSequence(const FInputDeviceRay& InPressPos) override;`
- L78 _public prototype_ `virtual void OnClickPress(const FInputDeviceRay& InPressPos) override;`
- L79 _public prototype_ `virtual void OnDragStart(const FInputDeviceRay& InDragPos) override;`
- L80 _public prototype_ `virtual void OnClickDrag(const FInputDeviceRay& InDragPos) override;`
- L81 _public prototype_ `virtual void OnClickRelease(const FInputDeviceRay& InReleasePos, bool bInIsDragOperation) override;`
- L82 _public prototype_ `virtual void OnTerminateSingleClickAndDragSequence() override;`
- L86 _public prototype_ `virtual FInputRayHit IsHitByClick(const FInputDeviceRay& InClickPos) override;`
- L87 _public prototype_ `virtual void OnClicked(const FInputDeviceRay& InClickPos) override;`
- L90 _public function_ `AActor* GetSpawnedActor() const`
- L92 _public function_ `virtual void OnViewportPlannerUpdate()`
- L93 _public prototype_ `virtual void OnViewportPlannerComplete();`
- L94 _public prototype_ `virtual void OnActorSpawned(AActor* InActor);`
- L97 _public prototype_ `bool ViewportPositionToWorldPositionAndOrientation(EAvaViewportStatus InViewportStatus, const FVector2f& InViewportPosition, UWorld*& OutWorld, FVector& OutPosition, FRotator& OutRotation) const;` — Calls the below function with the default camera distance.
- L101 _public prototype_ `bool ViewportPositionToWorldPositionAndOrientation(EAvaViewportStatus InViewportStatus, const FVector2f& InViewportPosition, float InDistance, UWorld*& OutWorld, FVector& OutPosition, FRotator& OutRotation) const;` — Converts viewport position to camera plane transform at given distance.
- L104 _public prototype_ `FViewport* GetViewport(EAvaViewportStatus InViewportStatus) const;`
- L106 _public function_ `bool ShouldAutoRegister() const`
- L111 _public function_ `virtual void OnRegisterTool(IAvalancheInteractiveToolsModule* InAITModule)`
- L117 _protected function_ `static InActorFactoryClass* CreateActorFactory()`
- L123 _protected member_ `TObjectPtr<UAvaSingleClickAndDragBehavior> LeftClickBehavior = nullptr;` — `UPROPERTY()`
- L126 _protected member_ `TObjectPtr<UAvaInteractiveToolsRightClickBehavior> RightClickBehavior = nullptr;` — `UPROPERTY()`
- L129 _protected member_ `TObjectPtr<USingleKeyCaptureBehavior> EscapeKeyBehavior = nullptr;` — `UPROPERTY()`
- L132 _protected member_ `TSubclassOf<UAvaInteractiveToolsToolViewportPlanner> ViewportPlannerClass = nullptr;` — `UPROPERTY()`
- L135 _protected member_ `TObjectPtr<UAvaInteractiveToolsToolViewportPlanner> ViewportPlanner = nullptr;` — `UPROPERTY()`
- L138 _protected member_ `TObjectPtr<AActor> PreviewActor = nullptr;` — `UPROPERTY()`
- L141 _protected member_ `TObjectPtr<AActor> SpawnedActor = nullptr;` — `UPROPERTY()`
- L143 _protected member_ `bool bPerformingDefaultAction = false;`
- L145 _protected member_ `bool bAutoRegister = true;`
- L147 _protected prototype_ `virtual bool CanActivate(const FString& InToolIdentifier, bool bInReactivate) const;`
- L148 _protected prototype_ `virtual void Activate(const FString& InToolIdentifier, bool bInReactivate);`
- L151 _protected prototype_ `virtual void OnActivate();` — Called when the tool is selected in the InteractiveTools tab.
- L154 _protected prototype_ `virtual bool OnBegin();` — Returns false if tool fails to initialise.
- L157 _protected prototype_ `virtual void OnPostBegin();` — Called if Begin() is successful.
- L160 _protected prototype_ `virtual void OnCancel();` — Cancels the tool and shuts it down.
- L163 _protected prototype_ `virtual void OnComplete();` — Completes the tool and shuts it down.
- L165 _protected prototype_ `void BeginTransaction();`
- L167 _protected prototype_ `void EndTransaction();`
- L169 _protected prototype_ `void CancelTransaction();`
- L171 _protected prototype_ `void RequestShutdown(EToolShutdownType InShutdownType);`
- L174 _protected prototype_ `virtual void DefaultAction();` — Creates a default actor in the world, without user input.
- L177 _protected function_ `virtual bool UseIdentityLocation() const` — Returns true if actors should be spawned at {0, 0, 0}.
- L180 _protected function_ `virtual bool UseIdentityRotation() const` — Returns true if actors should be spawned oriented to {0, 0, 0}.
- L182 _protected prototype_ `bool ConditionalIdentityRotation() const;`
- L185 _protected prototype_ `AActor* SpawnActor(TSubclassOf<AActor> InActorClass, bool bInPreview, FString* InActorLabelOverride = nullptr);` — Calls the other spawn actor with the centre of the last active viewport as the position.
- L188 _protected prototype_ `virtual AActor* SpawnActor(TSubclassOf<AActor> InActorClass, EAvaViewportStatus InViewportStatus, const FVector2f& InViewportPosition, bool bInPreview, FString* InActorLabelOverride = nullptr);` — Spawns an actor of the given class at the correct distance from the camera in the given viewport position.
- L191 _protected prototype_ `void SetToolkitSettingsObject(UObject* InObject) const;`
- L193 _protected prototype_ `bool IsMotionDesignViewport() const;`
- L195 _protected prototype_ `virtual bool ShouldForceDefaultAction() const;`
- L197 _protected prototype_ `void DestroyPreviewActor();`
- L200 _protected prototype_ `void OnPreviewActorDestroyed(AActor* InDestroyedActor);` — `UFUNCTION()`
