# Plugins / AvalancheEditorCore

- module root: `Plugins/VirtualProduction/Avalanche/Source/AvalancheEditorCore`
- headers: 33; symbols: 498
- symbol kinds: class=28, delegate=3, enum=2, enumerator=5, function=87, member=102, namespace=1, prototype=254, struct=13, typedef=3
- PrivateDependencyModuleNames: ApplicationCore, CoreUObject, EditorFramework, Engine, LevelEditor, Projects, StatusBar, ToolMenus, TypedElementFramework, TypedElementRuntime, WorkspaceMenuStructure
- PublicDependencyModuleNames: AvalancheCore, Core, InputCore, Slate, SlateCore, UnrealEd

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheEditorCore/Private/AvaEdMode.h` (Private)


#### class `UAvaEdMode`  
`class UAvaEdMode : public UEdMode`  
_L16-50_
- reflection: `UCLASS()`
- inherits: `UEdMode`
- desc: Used primarily as means to add/override functionality such as Edit (Copy,Paste,etc) This Ed Mode gets automatically activated by the Ava Editor Init
- L21 _public member_ `static const FEditorModeID ModeID;`
- L23 _public prototype_ `UAvaEdMode();`
- L25 _public prototype_ `virtual ~UAvaEdMode() override = default;`
- L27 _public function_ `TSharedPtr<IAvaEditor> GetEditor() const`
- L30 _public prototype_ `virtual void Initialize();`
- L31 _public function_ `virtual bool IsCompatibleWith(FEditorModeID InOtherModeID) const override`
- L32 _public function_ `virtual EEditAction::Type GetActionEditCut() override`
- L33 _public function_ `virtual EEditAction::Type GetActionEditCopy() override`
- L34 _public function_ `virtual EEditAction::Type GetActionEditPaste() override`
- L35 _public function_ `virtual EEditAction::Type GetActionEditDuplicate() override`
- L36 _public function_ `virtual EEditAction::Type GetActionEditDelete() override`
- L37 _public prototype_ `virtual bool UsesToolkits() const override;`
- L38 _public prototype_ `virtual void CreateToolkit() override;`
- L39 _public prototype_ `virtual bool ProcessEditCut() override;`
- L40 _public prototype_ `virtual bool ProcessEditCopy() override;`
- L41 _public prototype_ `virtual bool ProcessEditPaste() override;`
- L42 _public prototype_ `virtual bool ProcessEditDuplicate() override;`
- L43 _public prototype_ `virtual bool ProcessEditDelete() override;`
- L46 _public prototype_ `TSharedPtr<FUICommandList> GetToolkitCommands() const;`
- L49 _private member_ `TWeakPtr<IAvaEditor> EditorWeak;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheEditorCore/Private/AvaEdModeToolkit.h` (Private)


#### class `FAvaEdModeToolkit`  
`class FAvaEdModeToolkit : public FModeToolkit`  
_L9-27_
- inherits: `FModeToolkit`
- L12 _public prototype_ `FAvaEdModeToolkit(UAvaEdMode* InEdMode);`
- L15 _public prototype_ `virtual FName GetToolkitFName() const override;`
- L16 _public prototype_ `virtual FText GetBaseToolkitName() const override;`
- L20 _public function_ `virtual void RequestModeUITabs() override`
- L21 _public function_ `virtual void InvokeUI() override`
- L22 _public prototype_ `virtual void ExtendSecondaryModeToolbar(UToolMenu* InToolbarMenu);`
- L26 _private member_ `TWeakObjectPtr<UAvaEdMode> EdModeWeak;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheEditorCore/Private/AvaEditor.h` (Private)


#### class `FAvaEditor`  
`class FAvaEditor : public IAvaEditor`  
_L22-122_
- inherits: `IAvaEditor`
- L25 _public prototype_ `UE_AVA_INHERITS(FAvaEditor, IAvaEditor);`
- L27 _public prototype_ `explicit FAvaEditor(FAvaEditorBuilder& Initializer);`
- L32 _protected function_ `virtual void ExtendLayout(FLayoutExtender& InExtender)`
- L34 _protected prototype_ `void InvokeTabs();`
- L36 _protected prototype_ `void ForEachExtension(TFunctionRef<void(const TSharedRef<IAvaEditorExtension>&)> InFunc) const;`
- L38 _protected prototype_ `void NotifySceneActivationEvent();`
- L41 _protected prototype_ `virtual void Construct() override;`
- L42 _protected prototype_ `virtual void Activate(TSharedPtr<IToolkitHost> InOverrideToolkitHost = nullptr) override;`
- L43 _protected prototype_ `virtual void Deactivate() override;`
- L44 _protected prototype_ `virtual void Cleanup() override;`
- L45 _protected function_ `virtual bool IsActive() const`
- L46 _protected prototype_ `virtual bool CanActivate() const override;`
- L47 _protected prototype_ `virtual bool ShouldAutoActivate() const override;`
- L48 _protected prototype_ `virtual void SetAutoActivate(bool bInAutoActivate) override;`
- L49 _protected prototype_ `virtual bool CanDeactivate() const override;`
- L50 _protected prototype_ `virtual void SetToolkitHost(TSharedRef<IToolkitHost> InToolkitHost) override;`
- L51 _protected prototype_ `virtual void BindCommands(const TSharedRef<FUICommandList>& InCommandList) override;`
- L52 _protected prototype_ `virtual void Save() override;`
- L53 _protected prototype_ `virtual void Load() override;`
- L54 _protected prototype_ `virtual TSharedPtr<FUICommandList> GetCommandList() const override;`
- L55 _protected function_ `virtual TSharedPtr<IToolkitHost> GetToolkitHost() const override`
- L56 _protected prototype_ `virtual TSharedPtr<FTabManager> GetTabManager() const override;`
- L57 _protected prototype_ `virtual FEditorModeTools* GetEditorModeTools() const override;`
- L58 _protected prototype_ `virtual UWorld* GetWorld() const override;`
- L59 _protected prototype_ `virtual void OnSceneObjectChanged() override;`
- L60 _protected prototype_ `virtual UObject* GetSceneObject(EAvaEditorObjectQueryType InQueryType) const override;`
- L61 _protected prototype_ `virtual void RegisterTabSpawners() override;`
- L62 _protected prototype_ `virtual void UnregisterTabSpawners() override;`
- L63 _protected prototype_ `virtual void ExtendToolbarMenu(UToolMenu* InMenu) override;`
- L64 _protected prototype_ `virtual void ExtendCreateSceneOptions(UToolMenu* InMenu) override;`
- L65 _protected prototype_ `virtual void CloseTabs() override;`
- L66 _protected prototype_ `virtual FReply DockInLayout(FName InTabId) override;`
- L67 _protected prototype_ `virtual TArray<TSharedRef<IAvaEditorExtension>> GetExtensions() const override;`
- L68 _protected prototype_ `virtual TSharedPtr<IAvaEditorExtension> FindExtensionImpl(FAvaTypeId InExtensionId) const override;`
- L69 _protected prototype_ `virtual void AddTabSpawnerImpl(TSharedRef<IAvaTabSpawner> InTabSpawner) override;`
- L70 _protected prototype_ `virtual void OnSelectionChanged(UObject* InSelection) override;`
- L71 _protected prototype_ `virtual bool EditCut() override;`
- L72 _protected prototype_ `virtual bool EditCopy() override;`
- L73 _protected prototype_ `virtual bool EditPaste() override;`
- L74 _protected prototype_ `virtual bool EditDuplicate() override;`
- L75 _protected prototype_ `virtual bool EditDelete() override;`
- L76 _protected prototype_ `virtual const TSharedPtr<FWorkspaceItem>& GetRootCategory() const override;`
- L77 _protected prototype_ `virtual const TSharedPtr<FWorkspaceItem>& GetOutlinerCategory() const override;`
- L78 _protected prototype_ `virtual const TSharedPtr<FWorkspaceItem>& GetToolsCategory() const override;`
- L81 _protected prototype_ `void DeactivateExtensions();`
- L85 _private prototype_ `void NotifySceneObjectCreated(UObject* InSceneObject) const;` — Called when the scene object has been created for the first time
- L87 _private prototype_ `bool CopyToString(FString& OutCopyData) const;`
- L89 _private prototype_ `bool PasteFromString(FString& InPastedData) const;`
- L91 _private prototype_ `void BindDelegates();`
- L93 _private prototype_ `void UnbindDelegates();`
- L95 _private prototype_ `void OnEnginePreExit();`
- L97 _private member_ `TSharedRef<IAvaEditorProvider> Provider;`
- L99 _private member_ `TMap<FAvaTypeId, TSharedRef<IAvaEditorExtension>> EditorExtensions;`
- L101 _private member_ `TMap<FName, TSharedRef<IAvaTabSpawner>> TabSpawners;`
- L103 _private member_ `TWeakPtr<IToolkitHost> ToolkitHostWeak;`
- L106 _private member_ `TWeakObjectPtr<UObject> SceneObjectWeak;` — Cached Scene Object to avoid having to call OnGetSceneObject everytime
- L109 _private member_ `TSharedPtr<FWorkspaceItem> RootCategory;` — Tab Categories
- L110 _private member_ `TSharedPtr<FWorkspaceItem> OutlinerCategory;`
- L111 _private member_ `TSharedPtr<FWorkspaceItem> ToolsCategory;`
- L113 _private member_ `FDelegateHandle OnSelectionChangedHandle;`
- L115 _private member_ `FDelegateHandle OnEnginePreExitHandle;`
- L117 _private member_ `bool bIsActive = false;`
- L119 _private member_ `bool bDuplicating = false;`
- L121 _private member_ `bool bActiveStateChanging = false;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheEditorCore/Private/AvaEditorCoreModule.h` (Private)


#### class `FAvaEditorCoreModule`  
`class FAvaEditorCoreModule : public IAvaEditorCoreModule`  
_L7-21_
- inherits: `IAvaEditorCoreModule`
- L11 _public prototype_ `virtual void StartupModule() override;`
- L12 _public prototype_ `virtual void ShutdownModule() override;`
- L16 _public prototype_ `virtual FOnExtendEditorToolbar& GetOnExtendEditorToolbar();`
- L20 _private member_ `FOnExtendEditorToolbar OnExtendEditorToolbar;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheEditorCore/Private/LevelEditor/AvaLevelEditor.h` (Private)


#### class `FAvaLevelEditor`  
`class FAvaLevelEditor : public FAvaEditor`  
_L12-53_
- inherits: `FAvaEditor`
- L15 _public prototype_ `UE_AVA_INHERITS(FAvaLevelEditor, FAvaEditor);`
- L17 _public prototype_ `explicit FAvaLevelEditor(FAvaEditorBuilder& Initializer);`
- L21 _public prototype_ `void CreateScene();`
- L23 _public prototype_ `bool CanCreateScene() const;`
- L27 _protected prototype_ `virtual void Construct() override;`
- L28 _protected prototype_ `virtual void ExtendLayout(FLayoutExtender& InExtender) override;`
- L32 _protected prototype_ `virtual void BindCommands(const TSharedRef<FUICommandList>& InCommandList) override;`
- L36 _private prototype_ `void OnCurrentLevelChanged(ULevel* InNewLevel, ULevel* InOldLevel, UWorld* InWorld);`
- L38 _private prototype_ `void TryOpenScene(EAvaEditorObjectQueryType InQueryType = EAvaEditorObjectQueryType::SearchOnly);`
- L40 _private prototype_ `void OnMapChanged(UWorld* InWorld, EMapChangeType InChangeType);`
- L42 _private prototype_ `void OnLevelEditorCreated(TSharedPtr<ILevelEditor> InLevelEditor);`
- L44 _private member_ `TSharedRef<FAvaLevelEditorToolbar> Toolbar;`
- L46 _private member_ `FDelegateHandle OnCurrentLevelChangedHandle;`
- L48 _private member_ `FDelegateHandle OnRegisterLayoutHandle;`
- L50 _private member_ `FDelegateHandle OnMapChangedHandle;`
- L52 _private member_ `FDelegateHandle OnLevelEditorCreatedHandle;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheEditorCore/Private/LevelEditor/AvaLevelEditorCommands.h` (Private)


#### class `FAvaLevelEditorCommands`  
`class FAvaLevelEditorCommands : public TCommands<FAvaLevelEditorCommands>`  
_L7-21_
- inherits: `TCommands<FAvaLevelEditorCommands>`
- L10 _public prototype_ `FAvaLevelEditorCommands();`
- L13 _public prototype_ `virtual void RegisterCommands() override;`
- L16 _public member_ `TSharedPtr<FUICommandInfo> CreateScene;`
- L18 _public member_ `TSharedPtr<FUICommandInfo> ActivateScene;`
- L20 _public member_ `TSharedPtr<FUICommandInfo> DeactivateScene;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheEditorCore/Private/LevelEditor/AvaLevelEditorStyle.h` (Private)


#### class `FAvaLevelEditorStyle`  
`class FAvaLevelEditorStyle final : public FSlateStyleSet`  
_L7-18_
- inherits: `FSlateStyleSet`
- L10 _public function_ `static FAvaLevelEditorStyle& Get()`
- L16 _public prototype_ `FAvaLevelEditorStyle();`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheEditorCore/Private/LevelEditor/AvaLevelEditorToolbar.h` (Private)


#### class `FAvaLevelEditorToolbar`  
`class FAvaLevelEditorToolbar : public TSharedFromThis<FAvaLevelEditorToolbar>`  
_L15-34_
- inherits: `TSharedFromThis<FAvaLevelEditorToolbar>`
- desc: Responsible for manipulating the Level Editor toolbar for the Motion Design Editor
- L18 _public prototype_ `FAvaLevelEditorToolbar();`
- L20 _public prototype_ `~FAvaLevelEditorToolbar();`
- L22 _public prototype_ `void Construct(const TSharedRef<FAvaLevelEditor>& InLevelEditor);`
- L24 _public prototype_ `void Destroy();`
- L27 _private prototype_ `void BindLevelEditorToolbarCommands(const TSharedRef<FAvaLevelEditor>& InLevelEditor);`
- L29 _private prototype_ `void ExtendLevelEditorToolbar(const TSharedRef<IAvaEditor>& InLevelEditor);`
- L31 _private member_ `TWeakPtr<FAvaLevelEditor> LevelEditorWeak;`
- L33 _private member_ `TSharedRef<FUICommandList> CommandList;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheEditorCore/Public/AvaEditorBuilder.h` (Public)


#### class `FAvaEditorBuilder`  
`class FAvaEditorBuilder`  
_L15-75_
- L26 _private member_ `template<typename InBaseExtensionType, typename InOverrideExtensionType> static constexpr bool TIsValidExtension_V = !std::is_abstract_v<InOverrideExtensionType> && std::is_base_of_v<IAvaEditorExtension, InBaseExtensionType> && std::is_base_of_v<InBaseExtensionType, InOverrideExtensionType>;` — For an Extension to be Consider valid, all these conditions must be met: 1) Both the Base Type and Override Type must be derived from IAvaEditorExtension 2) Override Type is the Base Type or a Derived Type of it 3) Override Type is not abstract
- L32 _public prototype_ `virtual ~FAvaEditorBuilder();`
- L35 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnEditorBuild, FAvaEditorBuilder&);` — Delegate to give an opportunity for others to override provider class or add extensions
- L36 _public member_ `static FOnEditorBuild OnEditorBuild;`
- L38 _public prototype_ `FName GetIdentifier() const;`
- L40 _public prototype_ `FAvaEditorBuilder& SetIdentifier(FName InIdentifier);`
- L44 _public function_ `FAvaEditorBuilder& SetProvider(InArgTypes&&... InArgs)`
- L52 _public function_ `FAvaEditorBuilder& AddExtension(InArgTypes&&... InArgs)`
- L61 _public prototype_ `TSharedRef<IAvaEditor> Build();` — Creates the editor and initializes it and its extensions
- L64 _protected prototype_ `virtual TSharedRef<IAvaEditor> CreateEditor();`
- L68 _private member_ `FName Identifier = NAME_None;` — Optional identifier for this Initializer instance
- L70 _private member_ `TSharedPtr<IAvaEditorProvider> Provider;`
- L72 _private member_ `TMap<FAvaTypeId, TSharedRef<IAvaEditorExtension>> Extensions;`
- L74 _private member_ `bool bFinalized = false;`

#### Free symbols / members of external scopes

- L35 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnEditorBuild, FAvaEditorBuilder&);` — Delegate to give an opportunity for others to override provider class or add extensions

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheEditorCore/Public/AvaEditorContext.h` (Public)


#### class `UAvaEditorContext`  
`class UAvaEditorContext : public UObject`  
_L12-25_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject`
- L17 _public prototype_ `UAvaEditorContext() = default;`
- L19 _public function_ `void SetAvaEditor(const TSharedRef<IAvaEditor>& InAvaEditor)`
- L21 _public function_ `TSharedPtr<IAvaEditor> GetAvaEditor() const`
- L24 _private member_ `TWeakPtr<IAvaEditor> AvaEditorWeak;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheEditorCore/Public/AvaEditorCoreStyle.h` (Public)


#### class `FAvaEditorCoreStyle`  
`class FAvaEditorCoreStyle final : public FSlateStyleSet`  
_L7-14_
- inherits: `FSlateStyleSet`
- L10 _public prototype_ `static FAvaEditorCoreStyle& Get();`
- L12 _public prototype_ `FAvaEditorCoreStyle();`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheEditorCore/Public/AvaEditorExtensionType.h` (Public)


#### struct `FAvaEditorExtensionType`  
`struct FAvaEditorExtensionType`  
_L11-36_
- L13 _public function_ `bool IsValid() const`
- L23 _public function_ `bool operator==(const FAvaEditorExtensionType& InOther) const`
- L28 _public member_ `FAvaTypeId TypeId = FAvaTypeId::Invalid();`
- L31 _public member_ `TArray<TWeakPtr<IAvaEditorExtension>> Extensions;` — Weak pointers to the instances of the type
- L33 _public member_ `void(*Startup)() = nullptr;`
- L35 _public member_ `void(*Shutdown)() = nullptr;`

#### Free symbols / members of external scopes

- L18 _function_ `friend uint32 GetTypeHash(const FAvaEditorExtensionType& InType)`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheEditorCore/Public/AvaEditorExtensionTypeRegistry.h` (Public)


#### struct `CAvaEditorStaticStartupProvider`  
`struct CAvaEditorStaticStartupProvider`  
_L12-16_
- desc: Requires a given type to have StaticStartup()
- L15 _public prototype_ `template<typename T> auto Requires()->decltype(T::StaticStartup());`

#### struct `CAvaEditorStaticShutdownProvider`  
`struct CAvaEditorStaticShutdownProvider`  
_L19-23_
- desc: Requires a given type to have StaticShutdown()
- L22 _public prototype_ `template<typename T> auto Requires()->decltype(T::StaticShutdown());`

#### class `FAvaEditorExtensionTypeRegistry`  
`class FAvaEditorExtensionTypeRegistry`  
_L25-68_
- L29 _private prototype_ `FAvaEditorExtensionTypeRegistry() = default;`
- L31 _private prototype_ `~FAvaEditorExtensionTypeRegistry();`
- L34 _public prototype_ `static FAvaEditorExtensionTypeRegistry& Get();`
- L38 _public function_ `void RegisterExtension(const TSharedRef<InExtensionType>& InExtension)`
- L60 _public prototype_ `void RemoveStaleEntries();`
- L63 _private prototype_ `void RegisterExtensionType(const TSharedRef<IAvaEditorExtension>& InExtension, FAvaEditorExtensionType&& InType);`
- L65 _private prototype_ `void Shutdown();`
- L67 _private member_ `TSet<FAvaEditorExtensionType> ExtensionTypes;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheEditorCore/Public/AvaEditorPastedActor.h` (Public)


#### class `FAvaEditorPastedActor`  
`class FAvaEditorPastedActor`  
_L14-41_
- desc: Data struct used by the editor and its extensions to process a pasted actor
- L17 _public prototype_ `FAvaEditorPastedActor(AActor* InActor, TSoftObjectPtr<AActor>&& InTemplateActor);`
- L19 _public prototype_ `AActor* GetActor() const;`
- L21 _public prototype_ `const TSoftObjectPtr<AActor>& GetTemplateActor() const;`
- L23 _public prototype_ `bool IsDuplicate() const;`
- L30 _public prototype_ `static TMap<FName, AActor*> BuildPastedActorMap(TConstArrayView<FAvaEditorPastedActor> InPastedActors, bool bIncludeDuplicatedActors);` — Helper to build a map of the original actor name to its created actor on paste @param InPastedActors the list of pasted actors to convert to the map @param bIncludeDuplicatedActors whether to add duplicates to the actor map
- L33 _public prototype_ `static TMap<AActor*, AActor*> BuildDuplicatedActorMap(TConstArrayView<FAvaEditorPastedActor> InPastedActors);` — Helper to build a map of the template actor to its duplicated actor
- L37 _private member_ `TWeakObjectPtr<AActor> Actor;` — Pasted Actor
- L40 _private member_ `TSoftObjectPtr<AActor> TemplateActor;` — Template Actor used for the Paste

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheEditorCore/Public/AvaEditorSubsystem.h` (Public)


#### class `UAvaEditorSubsystem`  
`class UAvaEditorSubsystem : public UWorldSubsystem, public TAvaWorldSubsystemInterface<UAvaEditorSubsystem>`  
_L14-46_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UWorldSubsystem,TAvaWorldSubsystemInterface<UAvaEditorSubsystem>`
- L19 _public prototype_ `virtual ~UAvaEditorSubsystem() override = default;`
- L23 _public function_ `TSharedPtr<InExtensionType> FindExtension() const`
- L32 _public function_ `TSharedPtr<IAvaEditor> GetActiveEditor() const`
- L37 _public prototype_ `void OnEditorActivated(const TSharedRef<IAvaEditor>& InAvaEditor);`
- L38 _public prototype_ `void OnEditorDeactivated();`
- L41 _protected member_ `TWeakPtr<IAvaEditor> ActiveEditorWeak;`
- L44 _protected prototype_ `virtual bool DoesSupportWorldType(const EWorldType::Type InWorldType) const override;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheEditorCore/Public/AvaEditorWidgetUtils.h` (Public)


#### struct `FAvaEditorWidgetUtils`  
`struct FAvaEditorWidgetUtils`  
_L15-25_
- L17 _public prototype_ `static TArray<TSharedRef<SWidget>> GetWidgetChildrenOfClass(const TSharedPtr<SWidget>& InWidget, const FSlateWidgetClassData& InWidgetClass);`
- L19 _public prototype_ `static TSharedPtr<SWidget> FindParentWidgetWithClass(const TSharedPtr<SWidget>& InWidget, const FName& InWidgetClassName);`
- L21 _public prototype_ `static FVector2f GetWidgetScale(const SWidget* InWidget);`
- L22 _public prototype_ `static FVector2f GetWidgetScale(const TSharedRef<SWidget> InWidget);`
- L24 _public prototype_ `static FText AddKeybindToTooltip(FText InDefaultTooltip, TSharedPtr<FUICommandInfo> InCommand);`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheEditorCore/Public/AvaTabSpawner.h` (Public)


#### class `FAvaTabSpawner`  
`class FAvaTabSpawner : public IAvaTabSpawner`  
_L14-48_
- inherits: `IAvaTabSpawner`
- desc: Base Implementation of IAvaTabSpawner with functionality and data likely to be used across most Tab Spawners
- L17 _public prototype_ `explicit FAvaTabSpawner(const TSharedRef<IAvaEditor>& InEditor, FName InTabId);`
- L20 _public function_ `virtual FName GetId() const override`
- L21 _public prototype_ `virtual bool CanSpawnTab(const FSpawnTabArgs& InArgs, TWeakPtr<FTabManager> InTabManagerWeak) const override;`
- L22 _public prototype_ `virtual TSharedRef<SDockTab> SpawnTab(const FSpawnTabArgs& InArgs, TWeakPtr<FTabManager> InTabManagerWeak) override;`
- L23 _public prototype_ `virtual FTabSpawnerEntry& RegisterTabSpawner(const TSharedRef<FTabManager>& InTabManager, const TSharedPtr<FWorkspaceItem>& InWorkspaceMenu) override;`
- L27 _protected prototype_ `bool HasValidScene() const;`
- L29 _protected prototype_ `TSharedRef<SWidget> GetNullWidget() const;`
- L31 _protected member_ `TWeakPtr<IAvaEditor> EditorWeak;`
- L33 _protected member_ `TWeakPtr<SDockTab> DockTab;`
- L35 _protected member_ `FName TabId;`
- L37 _protected member_ `FText TabLabel;`
- L39 _protected member_ `FText TabTooltipText;`
- L41 _protected member_ `FSlateIcon TabIcon;`
- L43 _protected member_ `ETabRole TabRole;`
- L45 _protected member_ `float TabInnerPadding = 0.f;`
- L47 _protected member_ `bool bAutosizeTab = false;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheEditorCore/Public/Bounds/AvaBoundsProviderSubsystem.h` (Public)


#### class `UAvaBoundsProviderSubsystem`  
`class UAvaBoundsProviderSubsystem : public UTickableWorldSubsystem, public TAvaWorldSubsystemInterface<UAvaBoundsProviderSubsystem>`  
_L18-106_
- reflection: `UCLASS()`
- inherits: `UTickableWorldSubsystem,TAvaWorldSubsystemInterface<UAvaBoundsProviderSubsystem>`
- L23 _public prototype_ `virtual ~UAvaBoundsProviderSubsystem() override = default;`
- L27 _public prototype_ `bool CacheComponentLocalBounds(UPrimitiveComponent* InComponent);`
- L30 _public prototype_ `bool CacheComponentWorldOrientedBounds(UPrimitiveComponent* InComponent);` — The cached oriented box of the component to the world.
- L33 _public prototype_ `bool CacheComponentActorOrientedBounds(UPrimitiveComponent* InComponent);` — The cached oriented box of the component to its container actor.
- L35 _public prototype_ `bool CacheActorLocalBounds(AActor* InActor);`
- L36 _public prototype_ `bool CacheActorOrientedBounds(AActor* InActor);`
- L37 _public prototype_ `bool CacheActorAndChildrenLocalBounds(AActor* InActor);`
- L38 _public prototype_ `bool CacheActorAndChildrenOrientedBounds(AActor* InActor);`
- L40 _public prototype_ `void ClearCachedBounds();`
- L42 _public prototype_ `bool HasCachedComponentLocalBounds(UPrimitiveComponent* InComponent) const;`
- L43 _public prototype_ `bool HasCachedComponentWorldOrientedBounds(UPrimitiveComponent* InComponent) const;`
- L44 _public prototype_ `bool HasCachedComponentActorOrientedBounds(UPrimitiveComponent* InComponent) const;`
- L45 _public prototype_ `bool HasCachedActorLocalBounds(AActor* InActor) const;`
- L46 _public prototype_ `bool HasCachedActorOrientedBounds(AActor* InActor) const;`
- L47 _public prototype_ `bool HasCachedActorAndChildrenLocalBounds(AActor* InActor) const;`
- L48 _public prototype_ `bool HasCachedActorAndChildrenOrientedBounds(AActor* InActor) const;`
- L50 _public prototype_ `FBox GetComponentLocalBounds(UPrimitiveComponent* InComponent);`
- L51 _public prototype_ `bool GetComponentWorldOrientedBounds(UPrimitiveComponent* InComponent, FOrientedBox& OutOrientedBounds);`
- L52 _public prototype_ `bool GetComponentActorOrientedBounds(UPrimitiveComponent* InComponent, FOrientedBox& OutOrientedBounds);`
- L54 _public prototype_ `FBox GetActorLocalBounds(AActor* InActor);`
- L55 _public prototype_ `bool GetActorOrientedBounds(AActor* InActor, FOrientedBox& OutOrientedBounds);`
- L57 _public prototype_ `FBox GetActorAndChildrenLocalBounds(AActor* InActor);`
- L58 _public prototype_ `bool GetActorAndChildrenOrientedBounds(AActor* InActor, FOrientedBox& OutOrientedBounds);`
- L62 _public prototype_ `const TMap<TWeakObjectPtr<UPrimitiveComponent>, FBox>& GetCachedComponentLocalBounds() const;`
- L63 _public prototype_ `const TMap<TWeakObjectPtr<UPrimitiveComponent>, FOrientedBox>& GetCachedComponentWorldOrientedBounds() const;`
- L64 _public prototype_ `const TMap<TWeakObjectPtr<UPrimitiveComponent>, FOrientedBox>& GetCachedComponentActorOrientedBounds() const;`
- L65 _public prototype_ `const TMap<TWeakObjectPtr<AActor>, FBox>& GetCachedActorLocalBounds() const;`
- L66 _public prototype_ `const TMap<TWeakObjectPtr<AActor>, FOrientedBox>& GetCachedActorOrientedBounds() const;`
- L67 _public prototype_ `const TMap<TWeakObjectPtr<AActor>, FBox>& GetCachedActorAndChildrenLocalBounds() const;`
- L68 _public prototype_ `const TMap<TWeakObjectPtr<AActor>, FOrientedBox>& GetCachedActorAndChildrenOrientedBounds() const;`
- L74 _public prototype_ `FBox GetSelectionBounds(bool bInIncludeChildrenOfSelectedActors);` — Gets the axis-aligned, world-scaled bounds of the selected actors. The base transform of this box is the first selected actor's location and rotation.Actor
- L77 _public prototype_ `bool GetSelectionOrientedBounds(bool bInIncludeChildrenOfSelectedActors, FOrientedBox& OutOrientedBounds);` — Returns the oriented box representing the bounds selected actors.
- L80 _public prototype_ `virtual bool IsTickableWhenPaused() const override;`
- L81 _public prototype_ `virtual bool IsTickableInEditor() const override;`
- L82 _public prototype_ `virtual TStatId GetStatId() const override;`
- L86 _public prototype_ `virtual void Tick(float DeltaTime) override;`
- L90 _protected member_ `TMap<TWeakObjectPtr<UPrimitiveComponent>, FBox> CachedComponentLocalBounds;`
- L91 _protected member_ `TMap<TWeakObjectPtr<UPrimitiveComponent>, FOrientedBox> CachedComponentWorldOrientedBounds;`
- L92 _protected member_ `TMap<TWeakObjectPtr<UPrimitiveComponent>, FOrientedBox> CachedComponentActorOrientedBounds;`
- L94 _protected member_ `TMap<TWeakObjectPtr<AActor>, FBox> CachedActorLocalBounds;`
- L95 _protected member_ `TMap<TWeakObjectPtr<AActor>, FOrientedBox> CachedActorOrientedBounds;`
- L97 _protected member_ `TMap<TWeakObjectPtr<AActor>, FBox> CachedActorAndChildrenLocalBounds;`
- L98 _protected member_ `TMap<TWeakObjectPtr<AActor>, FOrientedBox> CachedActorAndChildrenOrientedBounds;`
- L100 _protected member_ `FBox CachedSelectionBounds;`
- L101 _protected member_ `FBox CachedSelectionWithChildrenBounds;`
- L104 _protected prototype_ `virtual bool DoesSupportWorldType(const EWorldType::Type InWorldType) const override;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheEditorCore/Public/IAvaEditor.h` (Public)


#### enum `EAvaEditorObjectQueryType`  
`enum class EAvaEditorObjectQueryType : uint8`  
_L22-32_
- L25 _public enumerator_ `SearchOnly` — Returns cached version if valid. If invalid, it will try to find the object via Provider GetSceneObject
- L28 _public enumerator_ `SkipSearch` — Skip looking through the GetSceneObject and just get the cached version if valid, or return null
- L31 _public enumerator_ `CreateIfNotFound` — If there is no valid object (invalid cached version and not found), create it

#### class `IAvaEditor`  
`class IAvaEditor : public IAvaTypeCastable, public TSharedFromThis<IAvaEditor>`  
_L35-143_
- inherits: `IAvaTypeCastable,TSharedFromThis<IAvaEditor>`
- desc: Interface used to Extend an Editor (e.g. Level Editor) for the Motion Design Workflow that extends beyond the limits of Mode UI Layer
- L38 _public prototype_ `UE_AVA_INHERITS(IAvaEditor, IAvaTypeCastable);`
- L40 _public prototype_ `virtual ~IAvaEditor() override = default;`
- L43 _public function_ `virtual void Construct()` — Called to setup the basics without needing a Toolkit Host or Scene
- L45 _public prototype_ `virtual void SetToolkitHost(TSharedRef<IToolkitHost> InToolkitHost) = 0;`
- L47 _public prototype_ `virtual void Activate(TSharedPtr<IToolkitHost> InOverrideToolkitHost = nullptr) = 0;`
- L49 _public prototype_ `virtual void Deactivate() = 0;`
- L52 _public prototype_ `virtual void Cleanup() = 0;` — Gives all extension an opportunity to cleanup prior to Scene Object tear down
- L54 _public prototype_ `virtual bool IsActive() const = 0;`
- L56 _public prototype_ `virtual bool CanActivate() const = 0;`
- L59 _public prototype_ `virtual bool ShouldAutoActivate() const = 0;` — Whether the editor should auto-activate if available
- L62 _public prototype_ `virtual void SetAutoActivate(bool bInAutoActivate) = 0;` — Sets whether the editor should auto-activate
- L64 _public prototype_ `virtual bool CanDeactivate() const = 0;`
- L66 _public prototype_ `virtual void BindCommands(const TSharedRef<FUICommandList>& InCommandList) = 0;`
- L68 _public prototype_ `virtual void Save() = 0;`
- L70 _public prototype_ `virtual void Load() = 0;`
- L72 _public prototype_ `virtual TSharedPtr<FUICommandList> GetCommandList() const = 0;`
- L74 _public prototype_ `virtual TSharedPtr<IToolkitHost> GetToolkitHost() const = 0;`
- L76 _public prototype_ `virtual TSharedPtr<FTabManager> GetTabManager() const = 0;`
- L78 _public prototype_ `virtual FEditorModeTools* GetEditorModeTools() const = 0;`
- L80 _public prototype_ `virtual UWorld* GetWorld() const = 0;`
- L82 _public prototype_ `virtual void OnSceneObjectChanged() = 0;`
- L84 _public prototype_ `virtual UObject* GetSceneObject(EAvaEditorObjectQueryType InQueryType = EAvaEditorObjectQueryType::SearchOnly) const = 0;`
- L86 _public prototype_ `virtual void RegisterTabSpawners() = 0;`
- L88 _public prototype_ `virtual void UnregisterTabSpawners() = 0;`
- L90 _public function_ `virtual void ExtendToolbarMenu(UToolMenu* InMenu)`
- L93 _public function_ `virtual void ExtendCreateSceneOptions(UToolMenu* InMenu)` — Adds entries to the create scene options menu
- L95 _public prototype_ `virtual void CloseTabs() = 0;`
- L97 _public prototype_ `virtual FReply DockInLayout(FName InTabId) = 0;`
- L99 _public prototype_ `virtual TArray<TSharedRef<IAvaEditorExtension>> GetExtensions() const = 0;`
- L102 _public function_ `template<typename InExtensionType, typename = typename TEnableIf<TIsDerivedFrom<InExtensionType, IAvaEditorExtension>::Value>::Type> TSharedPtr<InExtensionType> FindExtension() const`
- L112 _public function_ `template<typename InTabSpawnerType, typename... InArgTypes, typename = typename TEnableIf<TIsDerivedFrom<InTabSpawnerType, IAvaTabSpawner>::Value>::Type> void AddTabSpawner(InArgTypes&&... InArgs)`
- L118 _public prototype_ `virtual void OnSelectionChanged(UObject* InSelection) = 0;`
- L120 _public prototype_ `virtual bool EditCut() = 0;`
- L122 _public prototype_ `virtual bool EditCopy() = 0;`
- L124 _public prototype_ `virtual bool EditPaste() = 0;`
- L126 _public prototype_ `virtual bool EditDuplicate() = 0;`
- L128 _public prototype_ `virtual bool EditDelete() = 0;`
- L131 _public prototype_ `virtual const TSharedPtr<FWorkspaceItem>& GetRootCategory() const = 0;` — Returns the root category for motion design tabs and other categories
- L134 _public prototype_ `virtual const TSharedPtr<FWorkspaceItem>& GetOutlinerCategory() const = 0;` — Returns the outliner sub-category for motion design tabs
- L137 _public prototype_ `virtual const TSharedPtr<FWorkspaceItem>& GetToolsCategory() const = 0;` — Returns the tools sub-category for motion design tabs
- L140 _protected prototype_ `virtual TSharedPtr<IAvaEditorExtension> FindExtensionImpl(FAvaTypeId InExtensionId) const = 0;`
- L142 _protected prototype_ `virtual void AddTabSpawnerImpl(TSharedRef<IAvaTabSpawner> InTabSpawner) = 0;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheEditorCore/Public/IAvaEditorCoreModule.h` (Public)


#### class `IAvaEditorCoreModule`  
`class IAvaEditorCoreModule : public IModuleInterface`  
_L11-29_
- inherits: `IModuleInterface`
- L13 _private member_ `static constexpr const TCHAR* ModuleName = TEXT("Ava`
- L16 _public function_ `static bool IsLoaded()`
- L21 _public function_ `static IAvaEditorCoreModule& Get()`
- L27 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnExtendEditorToolbar, UToolMenu&);` — Delegate to extend the Editor Toolbar
- L28 _public prototype_ `virtual FOnExtendEditorToolbar& GetOnExtendEditorToolbar() = 0;`

#### Free symbols / members of external scopes

- L27 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnExtendEditorToolbar, UToolMenu&);` — Delegate to extend the Editor Toolbar

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheEditorCore/Public/IAvaEditorExtension.h` (Public)


#### class `IAvaEditorExtension`  
`class IAvaEditorExtension : public IAvaTypeCastable, public TSharedFromThis<IAvaEditorExtension>`  
_L23-138_
- inherits: `IAvaTypeCastable,TSharedFromThis<IAvaEditorExtension>`
- L26 _public prototype_ `UE_AVA_INHERITS(IAvaEditorExtension, IAvaTypeCastable) static constexpr const TCHAR* DefaultSectionName = TEXT("Def`
- L32 _public function_ `virtual void Construct(const TSharedRef<IAvaEditor>& InEditor)` — Called as soon as this Editor Extension is created. Can use TSharedFromThis as it will be outside Ctor
- L35 _public function_ `virtual void Activate()` — Called when the Ava Editor is fully active (e.g. Toolkit and Scene have been set). Called right before invoking tabs
- L38 _public function_ `virtual void PostInvokeTabs()` — Called after Activate and after all the Extension Tabs have been invoked
- L45 _public function_ `virtual void Deactivate()` — Called when deactivating the Scene. This does not necessarily mean the scene object is being destroyed. For Destruction/Cleanup, use IAvaEditorExtension::Cleanup
- L48 _public function_ `virtual void Cleanup()` — Called when destroying the object containing the Scene Object for the Extension
- L50 _public prototype_ `virtual TSharedPtr<IAvaEditor> GetEditor() const = 0;`
- L52 _public function_ `virtual void BindCommands(const TSharedRef<FUICommandList>& InCommandList)`
- L55 _public function_ `virtual void OnSceneObjectCreated(UObject* InSceneObject)` — Called when the scene object has been created
- L58 _public function_ `virtual void OnSceneObjectChanged(UObject* InOldSceneObject, UObject* InNewSceneObject)` — Called when the scene object has been changed/replaced
- L60 _public function_ `virtual void RegisterTabSpawners(const TSharedRef<IAvaEditor>& InEditor) const`
- L63 _public function_ `virtual void ExtendToolbarMenu(UToolMenu& InMenu)` — Opportunity for an Extension to extend the Editor Toolbar
- L66 _public function_ `virtual void ExtendLevelEditorLayout(FLayoutExtender& InExtender) const` — Extend the Level Editor Layout (only called when instancing for Level Editor)
- L69 _public function_ `virtual void ExtendCreateSceneOptions(UToolMenu* InMenu)` — Opportunity for an extension to add to the create scene options menu
- L75 _public function_ `virtual FName GetCategoryName() const` — Name of the category this Extension belongs in. Used in places like Setting Details Category
- L85 _public function_ `virtual void ExtendSettingsCategory(IDetailCategoryBuilder& InCategoryBuilder)` — Extend the Settings Category by adding External Objects or Properties. Must have a valid category name to proceed. @see IAvaEditorExtension::GetCategoryName
- L87 _public function_ `virtual void Save()`
- L89 _public function_ `virtual void Load()`
- L92 _public function_ `virtual void NotifyOnSelectionChanged(const FAvaEditorSelection& InSelection)` — Called when a USelection relevant to the Toolkit Mode Tools has changed
- L95 _public function_ `virtual void OnCopyActors(FString& OutCopyData, TConstArrayView<AActor*> InActorsToCopy)` — Called when Actors are about to be copied and opportunity for Extension to add to the Copied String
- L98 _public function_ `virtual void PrePasteActors()` — Called prior to pasting the actors. Give opportunity for Extension to prepare for pasting
- L101 _public function_ `virtual void PostPasteActors(bool bInPasteSucceeded)` — Called after pasting the actors regardless if it successfully completes or not
- L104 _public function_ `virtual void OnPasteActors(FStringView InPastedData, TConstArrayView<FAvaEditorPastedActor> InPastedActors)` — Called when pasting new actors to give opportunity for Extension to handle Pasted Data and its Actors
- L106 _public function_ `UWorld* GetWorld() const`
- L112 _public function_ `FEditorModeTools* GetEditorModeTools() const`
- L119 _public function_ `template<typename InSceneObjectType = UObject> InSceneObjectType* GetSceneObject() const`
- L127 _public function_ `TSharedPtr<IToolkitHost> GetToolkitHost() const`
- L133 _public function_ `bool IsEditorActive() const`

#### class `FAvaEditorExtension`  
`class FAvaEditorExtension : public IAvaEditorExtension`  
_L140-152_
- inherits: `IAvaEditorExtension`
- L143 _public function_ `UE_AVA_INHERITS(FAvaEditorExtension, IAvaEditorExtension)`
- L147 _public function_ `virtual TSharedPtr<IAvaEditor> GetEditor() const override`
- L151 _private member_ `TWeakPtr<IAvaEditor> EditorWeak;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheEditorCore/Public/IAvaEditorProvider.h` (Public)


#### class `IAvaEditorProvider`  
`class IAvaEditorProvider : public TSharedFromThis<IAvaEditorProvider>`  
_L13-54_
- inherits: `TSharedFromThis<IAvaEditorProvider>`
- L16 _public prototype_ `virtual ~IAvaEditorProvider() = default;`
- L19 _public function_ `virtual void Construct()` — Called right after instantiating the provider
- L28 _public prototype_ `virtual UObject* GetSceneObject(UWorld* InWorld, EAvaEditorObjectQueryType InQueryType) = 0;` — Gets the Scene Object this Ava Editor Instance is using. @param InWorld the world to optionally help get the Scene Object @param InQueryType the type of query in order to get the object either from cache, or create one if not found
- L31 _public function_ `virtual bool ShouldAutoActivateScene(UObject* InSceneObject) const` — Whether the scene object can be auto-activated if the functionality is available
- L37 _public function_ `virtual void SetAutoActivateScene(UObject* InSceneObject, bool bInAutoActivateScene) const` — Sets the auto activate scene option for the scene object to persist it
- L43 _public function_ `virtual void GetActorsToEdit(TArray<AActor*>& InOutActorsToEdit) const` — Optional: Add/Remove from the Actor array when performing operations such as Copy/Cut
- L47 _public function_ `virtual void OnSceneActivated()`
- L51 _public function_ `virtual void OnSceneDeactivated()`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheEditorCore/Public/IAvaTabSpawner.h` (Public)


#### class `IAvaTabSpawner`  
`class IAvaTabSpawner : public TSharedFromThis<IAvaTabSpawner>`  
_L15-29_
- inherits: `TSharedFromThis<IAvaTabSpawner>`
- L18 _public prototype_ `virtual ~IAvaTabSpawner() = default;`
- L20 _public prototype_ `virtual FName GetId() const = 0;`
- L22 _public function_ `virtual bool CanSpawnTab(const FSpawnTabArgs& InArgs, TWeakPtr<FTabManager> InTabManagerWeak) const`
- L24 _public prototype_ `virtual TSharedRef<SDockTab> SpawnTab(const FSpawnTabArgs& InArgs, TWeakPtr<FTabManager> InTabManagerWeak) = 0;`
- L26 _public prototype_ `virtual TSharedRef<SWidget> CreateTabBody() = 0;`
- L28 _public prototype_ `virtual FTabSpawnerEntry& RegisterTabSpawner(const TSharedRef<FTabManager>& InTabManager, const TSharedPtr<FWorkspaceItem>& InWorkspaceMenu) = 0;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheEditorCore/Public/LevelEditor/AvaLevelEditorBuilder.h` (Public)


#### class `FAvaLevelEditorBuilder`  
`class FAvaLevelEditorBuilder : public FAvaEditorBuilder`  
_L7-13_
- inherits: `FAvaEditorBuilder`
- L11 _protected prototype_ `virtual TSharedRef<IAvaEditor> CreateEditor() override;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheEditorCore/Public/LevelEditor/AvaLevelEditorUtils.h` (Public)


#### class `FAvaLevelEditorUtils`  
`class FAvaLevelEditorUtils`  
_L11-19_
- desc: Utility class for the Level Editor and the Motion Design extension editor of it
- L14 _public prototype_ `static FLevelEditorModule* GetLevelEditorModule();`
- L16 _public prototype_ `static FLevelEditorModule* LoadLevelEditorModule();`
- L18 _public prototype_ `static TConstArrayView<FName> GetDetailsViewNames();`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheEditorCore/Public/Selection/AvaEditorSelection.h` (Public)


#### enum `EAvaSelectionSource`  
`enum class EAvaSelectionSource`  
_L15-21_
- L18 _public enumerator_ `Single` — Only consider one USelection Object, closest to the Object Type. E.g. AActor will use SelectedActors
- L20 _public enumerator_ `All` — Consider all USelection Objects in Editor Mode Tools (i.e. SelectedActors, SelectedComponents and SelectedObjects)

#### class `FAvaEditorSelection`  
`class FAvaEditorSelection`  
_L23-107_
- L26 _private typedef_ `template<typename InObjectType, typename InParentObjectType = UObject> using TDerivesFromUObject = typename TEnableIf<TIsDerivedFrom<InObjectType, InParentObjectType>::Value>::Type;`
- L29 _public function_ `FAvaEditorSelection(FEditorModeTools& InModeTools, UObject* InChangedSelection = nullptr) : ModeTools(InModeTools) , ChangedSelectionWeak(InChangedSelection)`
- L39 _public function_ `bool IsValid() const` — Determines this Selection valid either if there's either no Changed Selection (i.e. just handling Mode Tools) or the given Selection Object is one of the 3 in the given Editor Mode Tools
- L47 _public function_ `UObject* GetChangedSelection() const`
- L51 _public function_ `template<typename InObjectType = UObject, typename = TDerivesFromUObject<InObjectType>> USelection* GetSelection() const` — Retrieves the USelection object closest to Object Type
- L71 _public function_ `TArray<InObjectReturnType*> GetSelectedObjects() const`
- L91 _private function_ `template<typename InElementType> TArray<InElementType> GetSelectedObjects(USelection* InSelection) const`
- L103 _private member_ `FEditorModeTools& ModeTools;` — The Mode Tools used to get the USelection instances
- L106 _private member_ `TWeakObjectPtr<UObject> ChangedSelectionWeak;` — The Selection that changed that triggered this FAvaEditorSelection to be instanced. Can be null if nothing changed.

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheEditorCore/Public/Selection/AvaSelectionProviderSubsystem.h` (Public)


#### class `UAvaSelectionProviderSubsystem`  
`class UAvaSelectionProviderSubsystem : public UWorldSubsystem, public TAvaWorldSubsystemInterface<UAvaSelectionProviderSubsystem>`  
_L20-54_
- reflection: `UCLASS()`
- inherits: `UWorldSubsystem,TAvaWorldSubsystemInterface<UAvaSelectionProviderSubsystem>`
- L25 _public prototype_ `virtual ~UAvaSelectionProviderSubsystem() override = default;`
- L27 _public prototype_ `void UpdateSelection(const FAvaEditorSelection& InSelection);`
- L29 _public prototype_ `void ClearAttachedActorCache();`
- L31 _public function_ `TConstArrayView<TWeakObjectPtr<AActor>> GetSelectedActors() const`
- L32 _public function_ `TConstArrayView<TWeakObjectPtr<UActorComponent>> GetSelectedComponents() const`
- L39 _public prototype_ `FTransform GetSelectionTransform() const;` — Location: Center of the selected actors' bounds. Rotation: Rotation of the first actor. Scale: 1, 1, 1
- L41 _public prototype_ `TConstArrayView<TWeakObjectPtr<AActor>> GetAttachedActors(AActor* InActor, bool bInRecursive);`
- L44 _protected member_ `TArray<TWeakObjectPtr<AActor>> CachedSelectedActors;`
- L45 _protected member_ `TMap<TWeakObjectPtr<AActor>, TArray<TWeakObjectPtr<AActor>>> CachedDirectlyAttachedActors;`
- L46 _protected member_ `TMap<TWeakObjectPtr<AActor>, TArray<TWeakObjectPtr<AActor>>> CachedRecursivelyAttachedActors;`
- L49 _protected member_ `TArray<TWeakObjectPtr<UActorComponent>> CachedSelectedComponents;` — Does not cache selected root components. These should always be considered selected if the actor is.
- L52 _protected prototype_ `virtual bool DoesSupportWorldType(const EWorldType::Type InWorldType) const override;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheEditorCore/Public/Widgets/DataTypes/AvaUserInputDialogDataTypeBase.h` (Public)


#### struct `FAvaUserInputDialogDataTypeBase`  
`struct FAvaUserInputDialogDataTypeBase : public TSharedFromThis<FAvaUserInputDialogDataTypeBase>`  
_L11-34_
- inherits: `TSharedFromThis<FAvaUserInputDialogDataTypeBase>`
- L15 _public prototype_ `virtual ~FAvaUserInputDialogDataTypeBase() = default;`
- L17 _public prototype_ `virtual TSharedRef<SWidget> CreateInputWidget() = 0;`
- L19 _public function_ `virtual bool IsValueValid()`
- L25 _protected member_ `FSimpleDelegate OnCommit;`
- L27 _protected function_ `void OnUserCommit()`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheEditorCore/Public/Widgets/DataTypes/AvaUserInputDialogDataTypeNumeric.h` (Public)


#### struct `FAvaUserInputDialogNumericData`  
`struct FAvaUserInputDialogNumericData : public FAvaUserInputDialogDataTypeBase`  
_L12-67_
- inherits: `FAvaUserInputDialogDataTypeBase`
- L14 _public typedef_ `using FNumericType = InNumericType;`
- L15 _public typedef_ `using ThisStruct = FAvaUserInputDialogNumericData<FNumericType>;`
- L24 _public function_ `FAvaUserInputDialogNumericData(const FParams& InParams) : Value(InParams.InitialValue) , MinValue(InParams.MinValue) , MaxValue(InParams.MaxValue)`
- L31 _public function_ `FNumericType GetValue() const`
- L34 _public function_ `virtual TSharedRef<SWidget> CreateInputWidget()`
- L54 _protected member_ `FNumericType Value;`
- L55 _protected member_ `TOptional<FNumericType> MinValue;`
- L56 _protected member_ `TOptional<FNumericType> MaxValue;`
- L58 _protected function_ `void OnValueChanged(FNumericType InValue)`
- L63 _protected function_ `void OnValueCommitted(FNumericType InValue, ETextCommit::Type InCommitType)`

#### struct `FAvaUserInputDialogNumericData::FParams`  
`struct FParams`  
_L17-22_
- L19 _public member_ `FNumericType InitialValue = 0;`
- L20 _public member_ `TOptional<FNumericType> InMinValue = TOptional<FNumericType>();`
- L21 _public member_ `TOptional<FNumericType> InMaxValue = TOptional<FNumericType>();`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheEditorCore/Public/Widgets/DataTypes/AvaUserInputDialogDataTypeStruct.h` (Public)


#### struct `FAvaUserInputDialogDataTypeStruct`  
`struct FAvaUserInputDialogDataTypeStruct : FAvaUserInputDialogDataTypeBase`  
_L11-37_
- inherits: `FAvaUserInputDialogDataTypeBase`
- L21 _public prototype_ `FAvaUserInputDialogDataTypeStruct(const FParams& InParams);`
- L23 _public prototype_ `virtual ~FAvaUserInputDialogDataTypeStruct() override = default;`
- L25 _public prototype_ `const uint8* GetStructMemory() const;`
- L27 _public prototype_ `const UStruct* GetStruct() const;`
- L30 _public prototype_ `virtual TSharedRef<SWidget> CreateInputWidget() override;`
- L31 _public prototype_ `virtual bool IsValueValid() override;`
- L35 _protected member_ `TSharedRef<FStructOnScope> StructOnScope;`
- L36 _protected member_ `FIsValidDelegate IsValidDelegate;`

#### struct `FAvaUserInputDialogDataTypeStruct::FParams`  
`struct FParams`  
_L15-19_
- L17 _public member_ `UScriptStruct* Struct = nullptr;`
- L18 _public member_ `FIsValidDelegate IsValidDelegate;`

#### struct `TAvaUserInputDialogDataTypeStruct`  
`template<typename InStructType> struct TAvaUserInputDialogDataTypeStruct : FAvaUserInputDialogDataTypeStruct`  
_L40-72_
- inherits: `FAvaUserInputDialogDataTypeStruct`
- L47 _public function_ `explicit TAvaUserInputDialogDataTypeStruct(const FParams& InParams) : FAvaUserInputDialogDataTypeStruct({TBaseStructure<InStructType>::Get(), InParams.IsValidDelegate})`
- L52 _public prototype_ `virtual ~TAvaUserInputDialogDataTypeStruct() override = default;`
- L54 _public function_ `const InStructType* GetPtr() const`
- L64 _public function_ `const InStructType& Get() const`

#### struct `TAvaUserInputDialogDataTypeStruct::FParams`  
`struct FParams`  
_L42-45_
- L44 _public member_ `FIsValidDelegate IsValidDelegate;`

#### Free symbols / members of external scopes

- L13 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FIsValidDelegate, TSharedRef<FStructOnScope>) struct FParams { UScriptStruct* Struct = nullptr; FIsValidDelegate IsValidDelegate; };`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheEditorCore/Public/Widgets/DataTypes/AvaUserInputDialogDataTypeText.h` (Public)


#### struct `FAvaUserInputDialogTextData`  
`struct FAvaUserInputDialogTextData : public FAvaUserInputDialogDataTypeBase`  
_L12-44_
- inherits: `FAvaUserInputDialogDataTypeBase`
- L22 _public prototype_ `FAvaUserInputDialogTextData(const FParams& InParams);`
- L24 _public prototype_ `virtual ~FAvaUserInputDialogTextData() override = default;`
- L26 _public prototype_ `const FText& GetValue() const;`
- L29 _public prototype_ `virtual TSharedRef<SWidget> CreateInputWidget() override;`
- L30 _public prototype_ `virtual bool IsValueValid() override;`
- L34 _protected member_ `FText Value;`
- L35 _protected member_ `bool bAllowMultiline;`
- L36 _protected member_ `TOptional<int32> MaxLength;`
- L37 _protected member_ `FOnVerifyTextChanged OnVerifyDelegate;`
- L39 _protected prototype_ `void OnTextChanged(const FText& InValue);`
- L41 _protected prototype_ `void OnTextCommitted(const FText& InValue, ETextCommit::Type InCommitType);`
- L43 _protected prototype_ `bool OnTextVerify(const FText& InValue, FText& OutErrorText);`

#### struct `FAvaUserInputDialogTextData::FParams`  
`struct FParams`  
_L14-20_
- L16 _public member_ `FText InitialValue = FText::GetEmpty();`
- L17 _public member_ `bool bAllowMultiline = false;`
- L18 _public member_ `TOptional<int32> MaxLength = TOptional<int32>();`
- L19 _public member_ `FOnVerifyTextChanged OnVerifyDelegate;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace ETextCommit`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheEditorCore/Public/Widgets/SAvaMultiComboButton.h` (Public)


#### class `SAvaMultiComboButton`  
`class SAvaMultiComboButton : public SMenuAnchor`  
_L28-165_
- inherits: `SMenuAnchor`
- desc: A button that, when clicked, brings up a popup.
- L32 _public function_ `SLATE_BEGIN_ARGS( SAvaMultiComboButton ) : _ComboButtonStyle(&FAppStyle::Get().GetWidgetStyle< FComboButtonStyle >( "ComboButton" )) , _ButtonStyle(nullptr) , _ButtonContent() , _MenuContent() , _IsFocusable(true) , _HasDownArrow(true) , _ForegroundColor(FSlateColor::UseStyle()) , _ButtonColorAndOpacity(FLinearColor::White) , _MenuPlacement(MenuPlacement_ComboBox) , _HAlign(HAlign_Fill) , _VAlign(VAlign_Center) , _Method() , _CollapseMenuOnParentFocus(false)`
- L48 _public prototype_ `SLATE_STYLE_ARGUMENT( FComboButtonStyle, ComboButtonStyle ) SLATE_STYLE_ARGUMENT( FButtonStyle, ButtonStyle ) SLATE_NAMED_SLOT( FArguments, ButtonContent ) SLATE_NAMED_SLOT( FArguments, MenuContent ) SLATE_EVENT( FOnGetContent, OnGetMenuContent ) SLATE_EVENT( FOnIsOpenChanged, OnMenuOpenChanged ) SLATE_EVENT( FOnComboBoxOpened, OnComboBoxOpened ) SLATE_EVENT(FOnClicked, OnButtonClicked) SLATE_ARGUMENT( bool, IsFocusable ) SLATE_ARGUMENT( bool, HasDownArrow ) SLATE_ATTRIBUTE( FSlateColor, ForegroundColor ) SLATE_ATTRIBUTE( FSlateColor, ButtonColorAndOpacity ) SLATE_ATTRIBUTE( FMargin, ContentPadding ) SLATE_ATTRIBUTE( EMenuPlacement, MenuPlacement ) SLATE_ARGUMENT( EHorizontalAlignment, HAlign ) SLATE_ARGUMENT( EVerticalAlignment, VAlign ) SLATE_ARGUMENT( TOptional<EPopupMethod>, Method ) SLATE_ARGUMENT(bool, CollapseMenuOnParentFocus) SLATE_END_ARGS()`
- L89 _public prototype_ `void SetOnGetMenuContent( FOnGetContent InOnGetMenuContent );` — See the OnGetMenuContent event
- L96 _public prototype_ `void Construct(const FArguments& InArgs);` — Construct the widget from a declaration @param InArgs  The declaration from which to construct
- L98 _public function_ `void SetMenuContentWidgetToFocus( TWeakPtr<SWidget> InWidgetToFocusPtr )`
- L104 _public prototype_ `void SetButtonContentPadding(FMargin InPadding);` — See the padding for button content.
- L107 _public prototype_ `void SetHasDownArrow(bool InHasArrowDown);` — add/remove the expanding arrow.
- L110 _public prototype_ `virtual FReply OnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;`
- L117 _protected prototype_ `virtual FReply OnButtonClicked();` — Handle the button being clicked by summoning the ComboButton.
- L118 _protected prototype_ `virtual FReply OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent) override;`
- L127 _protected prototype_ `FText GetFilteredToolTipText(TAttribute<FText> ToolTipText) const;` — Called to query the tool tip text for this widget, but will return an empty text when the menu is already open @param	ToolTipText	Tool tip text to display, if possible @return	Tool tip text, or an empty text if filtered out
- L131 _protected member_ `SHorizontalBox::FSlot* ButtonContentSlot;` — Area where the button's content resides
- L134 _protected member_ `FOnComboBoxOpened OnComboBoxOpened;` — Delegate to execute when the combo list is opened
- L136 _protected member_ `TWeakPtr<SWidget> WidgetToFocusPtr;`
- L139 _protected member_ `const FSlateBrush* MenuBorderBrush;` — Brush to use to add a "menu border" around the drop-down content
- L142 _protected member_ `FMargin MenuBorderPadding;` — Padding to use to add a "menu border" around the drop-down content
- L145 _protected member_ `TWeakPtr<SWidget> ContentWidgetPtr;` — The content widget, if any, set by the user on creation
- L148 _protected member_ `bool bIsFocusable;` — Can this button be focused?
- L152 _private member_ `TSharedPtr<SButton> ButtonPtr;` — The button widget within the ComboButton
- L155 _private member_ `TSharedPtr<SHorizontalBox> HBox;` — The box containing the arrow
- L158 _private member_ `TSharedPtr<SImage> ShadowImage;` — The arrow image shadow
- L161 _private member_ `TSharedPtr<SImage> ForegroundArrowImage;` — The arrow image
- L164 _private member_ `const FComboButtonStyle* Style;` — The ComboButton style

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheEditorCore/Public/Widgets/SAvaUserInputDialog.h` (Public)


#### class `SAvaUserInputDialog`  
`class SAvaUserInputDialog : public SCompoundWidget`  
_L8-39_
- inherits: `SCompoundWidget`
- L13 _public prototype_ `static bool CreateModalDialog(const TSharedRef<FAvaUserInputDialogDataTypeBase>& InInputType, const TSharedPtr<SWidget>& InParent = nullptr, const TOptional<FText>& InPrompt = TOptional<FText>(), const TOptional<FText>& InTitle = TOptional<FText>());`
- L16 _public function_ `SLATE_BEGIN_ARGS(SAvaUserInputDialog)`
- L17 _public prototype_ `SLATE_ARGUMENT(FText, Prompt) SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TSharedRef<FAvaUserInputDialogDataTypeBase>& InInputType);`
- L22 _public prototype_ `TSharedPtr<FAvaUserInputDialogDataTypeBase> GetInputType() const;`
- L24 _public prototype_ `bool WasAccepted() const;`
- L27 _private member_ `TSharedPtr<FAvaUserInputDialogDataTypeBase> InputType;`
- L28 _private member_ `bool bAccepted = false;`
- L30 _private prototype_ `FReply OnAcceptClicked();`
- L32 _private prototype_ `bool GetAcceptedEnabled() const;`
- L34 _private prototype_ `FReply OnCancelClicked();`
- L36 _private prototype_ `void OnUserCommit();`
- L38 _private prototype_ `void Close(bool bInAccepted);`
