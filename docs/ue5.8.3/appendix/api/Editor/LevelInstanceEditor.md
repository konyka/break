# Editor / LevelInstanceEditor

- module root: `Source/Editor/LevelInstanceEditor`
- headers: 13; symbols: 177
- symbol kinds: class=17, delegate=3, function=31, member=38, prototype=87, struct=1
- DynamicallyLoadedModuleNames: 
- PrivateDependencyModuleNames: AssetTools, ClassViewer, ContentBrowser, Core, CoreUObject, DeveloperSettings, EditorFramework, EditorInteractiveToolsFramework, EditorWidgets, Engine, InputCore, InteractiveToolsFramework, Kismet, LevelEditor, MainFrame, MessageLog, NewLevelDialog, PropertyEditor, SceneOutliner, Slate, SlateCore, ToolMenus, TypedElementFramework, TypedElementRuntime, UnrealEd, WorldPartitionEditor
- PrivateIncludePathModuleNames: 

### `Source/Editor/LevelInstanceEditor/Private/LevelInstanceActorDetails.h` (Private)


#### class `FLevelInstanceActorDetails`  
`class FLevelInstanceActorDetails : public IDetailCustomization`  
_L9-22_
- inherits: `IDetailCustomization`
- L13 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();` — Makes a new instance of this detail layout class for a specific detail view requesting it
- L16 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;` — IDetailCustomization interface
- L21 _private prototype_ `FLevelInstanceActorDetails();` — Use MakeInstance to create an instance of this class

### `Source/Editor/LevelInstanceEditor/Private/LevelInstanceActorFactory.h` (Private)


#### class `ULevelInstanceActorFactory`  
`class ULevelInstanceActorFactory : public UActorFactory`  
_L11-19_
- reflection: `UCLASS(MinimalAPI, config = Editor)`
- inherits: `UActorFactory`
- L16 _private prototype_ `virtual void PostSpawnActor(UObject* Asset, AActor* NewActor) override;`
- L17 _private prototype_ `virtual bool CanCreateActorFrom(const FAssetData& AssetData, FText& OutErrorMsg) override;`

### `Source/Editor/LevelInstanceEditor/Private/LevelInstanceEditorMode.h` (Private)


#### class `ULevelInstanceEditorBehaviorSource`  
`class ULevelInstanceEditorBehaviorSource : public UObject, public IInputBehaviorSource`  
_L12-24_
- reflection: `UCLASS()`
- inherits: `UObject,IInputBehaviorSource`
- L16 _public function_ `virtual const UInputBehaviorSet* GetInputBehaviors() const override`
- L17 _public prototype_ `void Initialize(UEditorInteractiveToolsContext* InteractiveToolsContext);`
- L21 _private member_ `TObjectPtr<UInputBehaviorSet> InputBehaviorSet;` — `UPROPERTY(Transient)`
- L23 _private member_ `TUniquePtr<IMouseWheelBehaviorTarget> MouseWheelBehaviorTarget;`

#### class `ULevelInstanceEditorMode`  
`class ULevelInstanceEditorMode : public UEdMode`  
_L27-70_
- reflection: `UCLASS()`
- inherits: `UEdMode`
- L31 _public member_ `static FEditorModeID EM_LevelInstanceEditorModeId;`
- L34 _public prototype_ `ULevelInstanceEditorMode();` — Constructor
- L37 _public prototype_ `virtual ~ULevelInstanceEditorMode();` — Destructor
- L40 _public prototype_ `virtual void Enter() override;`
- L41 _public prototype_ `virtual void Exit() override;`
- L42 _public prototype_ `virtual void CreateToolkit() override;`
- L43 _public prototype_ `virtual void ModeTick(float DeltaTime) override;`
- L45 _public prototype_ `virtual bool IsCompatibleWith(FEditorModeID OtherModeID) const override;`
- L48 _public prototype_ `virtual bool IsSelectionDisallowed(AActor* InActor, bool bInSelection) const override;` — Check to see if an actor can be selected in this mode - no side effects
- L49 _public prototype_ `virtual bool IsEditingDisallowed(AActor* InActor) const override;`
- L51 _public function_ `virtual bool IsOperationSupportedForCurrentAsset(EAssetOperation InOperation) const` — Only accept saving on current asset
- L54 _public prototype_ `static TScriptInterface<IInputBehaviorSource> CreateDefaultModeBehaviorSource(UEditorInteractiveToolsContext* InteractiveToolContext);`
- L57 _private prototype_ `void OnPreBeginPIE(bool bSimulate);`
- L58 _private prototype_ `void UpdateEngineShowFlags();`
- L59 _private prototype_ `virtual void BindCommands() override;`
- L61 _private prototype_ `void ExitModeCommand();`
- L62 _private prototype_ `void ToggleContextRestrictionCommand();`
- L63 _private prototype_ `bool IsContextRestrictionCommandEnabled() const;`
- L64 _private prototype_ `bool IsContextRestrictedForWorld(UWorld* InWorld) const;`
- L66 _private member_ `bool bContextRestriction;`
- L69 _private member_ `TScriptInterface<IInputBehaviorSource> ModeBehaviorSource;` — `UPROPERTY(Transient)`

### `Source/Editor/LevelInstanceEditor/Private/LevelInstanceEditorModeCommands.h` (Private)


#### class `FLevelInstanceEditorModeCommands`  
`class FLevelInstanceEditorModeCommands : public TCommands<FLevelInstanceEditorModeCommands>`  
_L14-38_
- inherits: `TCommands<FLevelInstanceEditorModeCommands>`
- L18 _public function_ `FLevelInstanceEditorModeCommands() : TCommands<FLevelInstanceEditorModeCommands> ( "LevelInstanceEditorMode", NSLOCTEXT("Contexts", "LevelInstanceEditor", "Level Instance Editor"), NAME_None, FAppStyle::GetAppStyleSetName()`
- L29 _public member_ `TSharedPtr<FUICommandInfo> ExitMode;` — Exit Editor Mode
- L32 _public member_ `TSharedPtr<FUICommandInfo> ToggleContextRestriction;` — Toggle Restrict Selection
- L37 _public prototype_ `virtual void RegisterCommands() override;` — Initialize commands

### `Source/Editor/LevelInstanceEditor/Private/LevelInstanceEditorModeToolkit.h` (Private)


#### class `FLevelInstanceEditorModeToolkit`  
`class FLevelInstanceEditorModeToolkit : public FModeToolkit`  
_L13-29_
- inherits: `FModeToolkit`
- L16 _public prototype_ `FLevelInstanceEditorModeToolkit();`
- L17 _public prototype_ `virtual ~FLevelInstanceEditorModeToolkit();`
- L20 _public prototype_ `virtual void Init(const TSharedPtr<IToolkitHost>& InitToolkitHost, TWeakObjectPtr<UEdMode> InOwningMode);` — IToolkit interface
- L22 _public prototype_ `virtual FName GetToolkitFName() const override;`
- L23 _public prototype_ `virtual FText GetBaseToolkitName() const override;`
- L25 _public prototype_ `virtual void RequestModeUITabs() override;`
- L28 _private member_ `TSharedPtr<SWidget> ViewportOverlayWidget;`

### `Source/Editor/LevelInstanceEditor/Private/LevelInstanceEditorModule.h` (Private)


#### class `FLevelInstanceEditorModule`  
`class FLevelInstanceEditorModule : public ILevelInstanceEditorModule, public FGCObject`  
_L23-141_
- inherits: `ILevelInstanceEditorModule,FGCObject`
- desc: The module holding all of the UI related pieces for LevelInstance management
- L26 _public prototype_ `virtual ~FLevelInstanceEditorModule()= default;`
- L31 _public prototype_ `virtual void StartupModule();` — Called right after the module DLL has been loaded and the module object has been created
- L36 _public prototype_ `virtual void ShutdownModule();` — Called before the module is unloaded, right before the module object is destroyed.
- L38 _public prototype_ `virtual void BroadcastTryExitEditorMode() override;`
- L40 _public prototype_ `DECLARE_DERIVED_EVENT(FLevelInstanceEditorModule, ILevelInstanceEditorModule::FExitEditorModeEvent, FExitEditorModeEvent);`
- L41 _public function_ `virtual FExitEditorModeEvent& OnExitEditorMode() override`
- L43 _public prototype_ `DECLARE_DERIVED_EVENT(FLevelInstanceEditorModule, ILevelInstanceEditorModule::FTryExitEditorModeEvent, FTryExitEditorModeEvent);`
- L44 _public function_ `virtual FTryExitEditorModeEvent& OnTryExitEditorMode() override`
- L46 _public function_ `virtual FOnLevelInstanceEditModeChanged& OnLevelInstanceEditModeChanged() override`
- L47 _public function_ `virtual void BroadcastOnLevelInstanceEditModeChanged(ILevelInstanceInterface* LevelInstance, ELevelInstanceEditMode NewMode) override`
- L49 _public prototype_ `virtual bool IsEditInPlaceStreamingEnabled() const override;`
- L50 _public prototype_ `virtual bool IsSubSelectionEnabled() const override;`
- L52 _public prototype_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override;`
- L53 _public function_ `virtual FString GetReferencerName() const override`
- L55 _public prototype_ `virtual void UpdateAllPackedLevelActorsForWorldAsset(const TSoftObjectPtr<UWorld>& InWorldAsset, bool bInLoadedOnly = false) override;`
- L58 _private prototype_ `virtual void UpdateEditorMode(bool bActivated) override;`
- L60 _private prototype_ `void OnEditorModeIDChanged(const FEditorModeID& InModeID, bool bIsEnteringMode);`
- L61 _private prototype_ `void OnLevelActorDeleted(AActor* Actor);`
- L62 _private prototype_ `void CanMoveActorToLevel(const AActor* ActorToMove, const ULevel* DestLevel, bool& bOutCanMove);`
- L64 _private prototype_ `void ExtendContextMenu();`
- L66 _private prototype_ `void OnLevelEditorCreated(TSharedPtr<ILevelEditor> InLevelEditor);`
- L67 _private prototype_ `void OnCreateActorBrowserColumns(FSceneOutlinerInitializationOptions& InitOptions, UWorld* World);`
- L68 _private prototype_ `void RegisterToFirstLevelEditor();`
- L69 _private prototype_ `FTopLevelAssetPath GetBrowseToLevelInstanceAsset(const UObject* Object) const;`
- L71 _private prototype_ `TSharedRef<ISceneOutlinerColumn> CreateLevelInstanceColumn(ISceneOutliner& SceneOutliner) const;`
- L109 _private member_ `TUniquePtr<FPropertyEditorPolicy> PropertyEditorPolicy;`
- L111 _private function_ `virtual bool IsPropertyEditConst(const FEditPropertyChain& PropertyChain, UObject* Object) override`
- L116 _private function_ `virtual bool IsPropertyEditConst(const FProperty* Property, UObject* Object) override`
- L121 _private function_ `virtual UObject* GetArchetype(const UObject* Object) override`
- L126 _private function_ `virtual void SetPropertyOverridePolicy(ILevelInstanceEditorModule::IPropertyOverridePolicy* InPropertyOverridePolicy) override`
- L135 _private member_ `FExitEditorModeEvent ExitEditorModeEvent;`
- L136 _private member_ `FTryExitEditorModeEvent TryExitEditorModeEvent;`
- L138 _private member_ `FOnLevelInstanceEditModeChanged OnLevelInstanceEditModeChangedDelegate;`
- L140 _private member_ `TScriptInterface<IInputBehaviorSource> DefaultBehaviorSource;`

#### class `FLevelInstanceEditorModule::FPropertyEditorPolicy`  
`class FPropertyEditorPolicy : public PropertyEditorPolicy::IEditConstPolicy, public PropertyEditorPolicy::IArchetypePolicy`  
_L73-107_
- inherits: `PropertyEditorPolicy::IEditConstPolicy,PropertyEditorPolicy::IArchetypePolicy`
- L77 _public function_ `FPropertyEditorPolicy(ILevelInstanceEditorModule::IPropertyOverridePolicy* InPropertyOverridePolicy) : PropertyOverridePolicy(InPropertyOverridePolicy)`
- L85 _public function_ `virtual ~FPropertyEditorPolicy()`
- L91 _public function_ `virtual UObject* GetArchetypeForObject(const UObject* Object) const override`
- L96 _public function_ `virtual bool CanEditProperty(const FEditPropertyChain& PropertyChain, const UObject* Object) const override`
- L101 _public function_ `virtual bool CanEditProperty(const FProperty* Property, const UObject* Object) const override`
- L106 _public member_ `ILevelInstanceEditorModule::IPropertyOverridePolicy* PropertyOverridePolicy = nullptr;`

#### Free symbols / members of external scopes

- L40 _delegate_ `DECLARE_DERIVED_EVENT(FLevelInstanceEditorModule, ILevelInstanceEditorModule::FExitEditorModeEvent, FExitEditorModeEvent);`
- L43 _delegate_ `DECLARE_DERIVED_EVENT(FLevelInstanceEditorModule, ILevelInstanceEditorModule::FTryExitEditorModeEvent, FTryExitEditorModeEvent);`

### `Source/Editor/LevelInstanceEditor/Private/LevelInstanceFilterPropertyTypeCustomization.h` (Private)


#### class `FLevelInstancePropertyTypeIdentifier`  
`class FLevelInstancePropertyTypeIdentifier : public IPropertyTypeIdentifier`  
_L16-30_
- inherits: `IPropertyTypeIdentifier`
- L19 _public function_ `FLevelInstancePropertyTypeIdentifier(bool bInIsEditFilter) : bIsEditFilter(bInIsEditFilter)`
- L23 _public function_ `virtual bool IsPropertyTypeCustomized(const IPropertyHandle& PropertyHandle) const override`
- L29 _private member_ `bool bIsEditFilter;`

#### struct `FLevelInstanceFilterPropertyTypeCustomization`  
`struct FLevelInstanceFilterPropertyTypeCustomization : public FWorldPartitionActorFilterPropertyTypeCustomization`  
_L33-50_
- inherits: `FWorldPartitionActorFilterPropertyTypeCustomization`
- desc: Registered (FLevelInstanceEditorModule::StartupModule) Property Customization for properties of type FWorldPartitionActorFilter for Level Instances
- L36 _public function_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance(bool bInIsEditFilter)`
- L41 _private function_ `FLevelInstanceFilterPropertyTypeCustomization(bool bInIsEditFilter) : bIsEditFilter(bInIsEditFilter)`
- L45 _private prototype_ `virtual TSharedPtr<FWorldPartitionActorFilterMode::FFilter> CreateModeFilter(TArray<UObject*> OuterObjects) override;`
- L46 _private prototype_ `virtual void ApplyFilter(TSharedRef<IPropertyHandle> PropertyHandle, const FWorldPartitionActorFilterMode& Mode) override;`
- L48 _private member_ `TMap<ILevelInstanceInterface*, int32> LevelInstances;`
- L49 _private member_ `bool bIsEditFilter;`

### `Source/Editor/LevelInstanceEditor/Private/LevelInstancePivotDetails.h` (Private)


#### class `FLevelInstancePivotDetails`  
`class FLevelInstancePivotDetails : public IDetailCustomization`  
_L13-41_
- inherits: `IDetailCustomization`
- L17 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();` — Makes a new instance of this detail layout class for a specific detail view requesting it
- L20 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;` — IDetailCustomization interface
- L25 _private prototype_ `FLevelInstancePivotDetails();` — Use MakeInstance to create an instance of this class
- L27 _private prototype_ `bool IsApplyButtonEnabled(TWeakObjectPtr<AActor> LevelInstancePivot) const;`
- L28 _private prototype_ `FReply OnApplyButtonClicked(TWeakObjectPtr<AActor> LevelInstancePivot);`
- L30 _private prototype_ `int32 GetSelectedPivotType() const;`
- L31 _private prototype_ `void OnSelectedPivotTypeChanged(int32 NewValue, ESelectInfo::Type SelectionType, TWeakObjectPtr<AActor> LevelInstancePivot);`
- L33 _private prototype_ `void OnPivotActorPicked(AActor* InPivotActor, TWeakObjectPtr<AActor> LevelInstancePivot);`
- L34 _private prototype_ `bool IsPivotActorSelectionEnabled() const;`
- L36 _private prototype_ `void ShowPivotLocation(const TWeakObjectPtr<AActor>& LevelInstancePivot);`
- L39 _private member_ `ELevelInstancePivotType PivotType;` — Settings for Apply button
- L40 _private member_ `TWeakObjectPtr<AActor> PivotActor;`

### `Source/Editor/LevelInstanceEditor/Private/LevelInstanceSceneOutlinerColumn.h` (Private)


#### class `FLevelInstanceSceneOutlinerColumn`  
`template<typename ItemType> class STableRow;`  
_L12-29_
- inherits: `ISceneOutlinerColumn`
- L15 _public function_ `FLevelInstanceSceneOutlinerColumn(ISceneOutliner& SceneOutliner) : WeakOutliner(StaticCastSharedRef<ISceneOutliner>(SceneOutliner.AsShared()))`
- L17 _public prototype_ `virtual ~FLevelInstanceSceneOutlinerColumn() = default;`
- L18 _public prototype_ `static FName GetID();`
- L21 _public function_ `virtual FName GetColumnID() override`
- L22 _public prototype_ `virtual SHeaderRow::FColumn::FArguments ConstructHeaderRowColumn() override;`
- L23 _public prototype_ `virtual const TSharedRef<SWidget> ConstructRowWidget(FSceneOutlinerTreeItemRef TreeItem, const STableRow<FSceneOutlinerTreeItemPtr>& Row) override;`
- L24 _public function_ `virtual bool SupportsSorting() const override`
- L28 _private member_ `TWeakPtr<ISceneOutliner> WeakOutliner;`

### `Source/Editor/LevelInstanceEditor/Private/SLevelInstancePivotPicker.h` (Private)


#### class `SLevelInstancePivotPicker`  
`class SLevelInstancePivotPicker : public SCompoundWidget`  
_L13-30_
- inherits: `SCompoundWidget`
- L16 _public function_ `SLATE_BEGIN_ARGS(SLevelInstancePivotPicker)`
- L21 _public prototype_ `void Construct(const FArguments& InArgs);`
- L24 _private prototype_ `FText GetSelectedPivotActorText() const;`
- L25 _private prototype_ `void OnPivotActorPicked(AActor* PickedActor);`
- L27 _private member_ `FOnPivotActorPicked OnPivotActorPickedEvent;`
- L28 _private member_ `TWeakObjectPtr<AActor> PivotActor;`
- L29 _private member_ `TSharedPtr<SComboButton> PivotActorPicker;`

#### Free symbols / members of external scopes

- L11 _delegate_ `DECLARE_DELEGATE_OneParam(FOnPivotActorPicked, AActor*) class SLevelInstancePivotPicker : public SCompoundWidget { public: SLATE_BEGIN_ARGS(SLevelInstancePivotPicker) {} SLATE_EVENT(FOnPivotActorPicked, OnPivotActorPicked) SLATE_END_ARGS() public: void Construct(const FArguments& InArgs); private: FText GetSelectedPivotActorText() const; void OnPivotActorPicked(AActor* PickedActor); FOnPivotActorPicked OnPivotActorPickedEvent; TWeakObjectPtr<AActor> PivotActor; TSharedPtr<SComboButton> PivotActorPicker; };`

### `Source/Editor/LevelInstanceEditor/Private/SNewLevelInstanceDialog.h` (Private)


#### class `SNewLevelInstanceDialog`  
`class SNewLevelInstanceDialog : public SCompoundWidget`  
_L24-64_
- inherits: `SCompoundWidget`
- L28 _public function_ `SLATE_BEGIN_ARGS(SNewLevelInstanceDialog)`
- L30 _public prototype_ `SLATE_ATTRIBUTE(TSharedPtr<SWindow>, ParentWindow) SLATE_ATTRIBUTE(TArray<AActor*>, PivotActors) SLATE_END_ARGS() ~SNewLevelInstanceDialog() = default;` — A pointer to the parent window
- L42 _public prototype_ `void Construct(const FArguments& InArgs);` — Construct this widget.  Called by the SNew() Slate macro. @param	InArgs				Declaration used by the SNew() macro to construct this widget @param	InViewModel			The UI logic not specific to slate
- L44 _public member_ `static const FVector2D DEFAULT_WINDOW_SIZE;`
- L46 _public function_ `bool ClickedOk() const`
- L48 _public function_ `FNewLevelInstanceParams& GetCreationParams()`
- L51 _private prototype_ `FReply OnOkClicked();`
- L52 _private prototype_ `bool IsOkEnabled() const;`
- L54 _private prototype_ `FReply OnCancelClicked();`
- L57 _private member_ `TWeakPtr<SWindow> ParentWindowPtr;` — Pointer to the parent window, so we know to destroy it when done
- L60 _private member_ `FNewLevelInstanceParams CreationParams;` — Dialog Result
- L63 _private member_ `bool bClickedOk;` — Dialog Result

#### class `FNewLevelInstanceParamsDetails`  
`class FNewLevelInstanceParamsDetails : public IDetailCustomization`  
_L66-87_
- inherits: `IDetailCustomization`
- L70 _public function_ `FNewLevelInstanceParamsDetails(TArray<AActor*> InPivotActors) : CreationParams(nullptr), PivotActors(InPivotActors)`
- L74 _public function_ `static TSharedRef<IDetailCustomization> MakeInstance(TArray<AActor*> InPivotActors)`
- L79 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;`
- L81 _public prototype_ `void OnSelectedPivotActorChanged(AActor* NewValue);`
- L82 _public prototype_ `bool IsPivotActorSelectionEnabled() const;`
- L85 _protected member_ `FNewLevelInstanceParams* CreationParams;`
- L86 _protected member_ `TArray<AActor*> PivotActors;`

### `Source/Editor/LevelInstanceEditor/Public/LevelInstanceEditorSettings.h` (Public)


#### class `ULevelInstanceEditorSettings`  
`class ULevelInstanceEditorSettings : public UDeveloperSettings`  
_L14-33_
- reflection: `UCLASS(config = Editor, defaultconfig, meta = (DisplayName = "Level Instance"))`
- inherits: `UDeveloperSettings`
- L19 _public prototype_ `ULevelInstanceEditorSettings();`
- L23 _public member_ `TArray<FTemplateMapInfo> TemplateMapInfos;` — `UPROPERTY(config)` — List of info for all known LevelInstance template maps
- L26 _public member_ `FString LevelInstanceClassName;` — `UPROPERTY(config)`
- L29 _public member_ `bool bEnableStreaming;` — `UPROPERTY(config, EditAnywhere, Category="World Partition", meta = (ToolTip="Create World Partition Level Instances with Streaming Enabled/Disabled by default"))`
- L32 _public member_ `bool bIsEditInPlaceStreamingEnabled;` — `UPROPERTY(config, EditAnywhere, Category="World Partition", meta = (ToolTip="Allow Editing Level Instances with Streaming Enabled"))`

#### class `ULevelInstanceEditorPerProjectUserSettings`  
`class ULevelInstanceEditorPerProjectUserSettings : public UDeveloperSettings`  
_L36-74_
- reflection: `UCLASS(config = EditorPerProjectUserSettings, meta = (DisplayName = "Level Instance"))`
- inherits: `UDeveloperSettings`
- L41 _public prototype_ `ULevelInstanceEditorPerProjectUserSettings();`
- L43 _public prototype_ `static void UpdateFrom(const FNewLevelInstanceParams& Params);`
- L46 _public function_ `virtual FName GetCategoryName() const override` — Gets the category for the settings, some high level grouping like, Editor, Engine, Game...etc.
- L50 _public member_ `bool bAlwaysShowDialog;` — `UPROPERTY(config, EditAnywhere, Category = Create)` — If false, create dialog will not be shown and last settings will be used.
- L53 _public member_ `ELevelInstancePivotType PivotType;` — `UPROPERTY(config, EditAnywhere, Category = Pivot)`
- L57 _public member_ `bool bIsSubSelectionEnabled;` — `UPROPERTY(config, EditAnywhere, Category = "Selection", meta = (ToolTip = "Allow Read Only Selection of Level Instance Level Actors"))` — If true, allows read only selection of actors inside a Level Instance
- L61 _public member_ `bool bIsViewportSubSelectionEnabled;` — `UPROPERTY(config, EditAnywhere, Category = "Selection", meta = (DisplayName = "Is Viewport Sub Selection Enabled (Shift + Mouse Scroll Up/Down)", ToolTip = "Allow Read Only Selection of Level Instance Level Actors in the Viewport (Shortcut: Shift + Mouse Scroll Up/Down)"))` — If true, allows read only selection of actors inside a Level Instance through the viewport
- L73 _public member_ `bool bKeepFoldersDuringBreak = false;` — `UPROPERTY(config, EditAnywhere, Category = Break)` — When the Level Instance is broken via "Level->Break..", its actors will be placed inside the folder the LI is inside of, under a subfolder with the name of the Level Instance, and also keeping their original folder structure. So if i.e. the Level Instance Actor is called "Desert/LI_House2", and an actor inside is named "Lights/Light_Sun", the actor will be moved to "Desert/LI_House2/Lights/Light_Sun" in the outer level. If this flag is not set, actors will be placed either in the root folder of the outer level (but their original folders from the LI kept), or, if "Current Folder" is set, they'll be moved there without any subfolders.

### `Source/Editor/LevelInstanceEditor/Public/PackedLevelActorUtils.h` (Public)


#### class `FPackedLevelActorUtils`  
`class FPackedLevelActorUtils`  
_L12-28_
- L15 _public prototype_ `static void GetPackedBlueprintsForWorldAsset(const TSoftObjectPtr<UWorld>& InWorldAsset, TSet<TSoftObjectPtr<UBlueprint>>& OutPackedBlueprintAssets, bool bInLoadedOnly = false);`
- L17 _public prototype_ `static bool CanPack();`
- L19 _public prototype_ `static void PackAllLoadedActors();`
- L21 _public prototype_ `static bool CreateOrUpdateBlueprint(ILevelInstanceInterface* InLevelInstance, TSoftObjectPtr<UBlueprint> InBlueprintAsset, bool bCheckoutAndSave = true, bool bPromptForSave = true);`
- L23 _public prototype_ `static bool CreateOrUpdateBlueprint(TSoftObjectPtr<UWorld> InWorldAsset, TSoftObjectPtr<UBlueprint> InBlueprintAsset, bool bCheckoutAndSave = true, bool bPromptForSave = true);`
- L25 _public prototype_ `static void UpdateBlueprint(UBlueprint* InBlueprint, bool bCheckoutAndSave = true);`
- L27 _public prototype_ `static void UpdateAllPackedBlueprintsForWorldAssetBlueprint(const TSoftObjectPtr<UWorld>& InWorldAsset, bool bInLoadedOnly = false);`
