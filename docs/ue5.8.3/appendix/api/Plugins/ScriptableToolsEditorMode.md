# Plugins / ScriptableToolsEditorMode

- module root: `Plugins/Editor/ScriptableToolsEditorMode/Source/ScriptableToolsEditorMode`
- headers: 11; symbols: 231
- symbol kinds: class=11, delegate=3, function=15, macro=4, member=77, prototype=118, struct=2, typedef=1
- DynamicallyLoadedModuleNames: 
- PrivateDependencyModuleNames: AssetRegistry, Engine, KismetWidgets, ToolWidgets
- PublicDependencyModuleNames: Core, CoreUObject, DeveloperSettings, EditorFramework, EditorInteractiveToolsFramework, EditorScriptableToolsFramework, EditorWidgets, Engine, GeometryCore, InputCore, InteractiveToolsFramework, ModelingComponents, ModelingComponentsEditorOnly, PhysicsCore, Projects, PropertyEditor, RenderCore, ScriptableToolsFramework, Slate, SlateCore, StatusBar, ToolWidgets, UnrealEd, WidgetRegistration

### `Plugins/Editor/ScriptableToolsEditorMode/Source/ScriptableToolsEditorMode/Public/ScriptableToolsEditorMode.h` (Public)


#### class `UScriptableToolsEditorMode`  
`class UScriptableToolsEditorMode : public UBaseLegacyWidgetEdMode`  
_L26-116_
- reflection: `UCLASS(MinimalAPI, Transient)`
- inherits: `UBaseLegacyWidgetEdMode`
- L30 _public member_ `const static FEditorModeID EM_ScriptableToolsEditorModeId;`
- L32 _public prototype_ `UScriptableToolsEditorMode();`
- L33 _public prototype_ `UScriptableToolsEditorMode(FVTableHelper& Helper);`
- L34 _public prototype_ `~UScriptableToolsEditorMode();`
- L39 _public prototype_ `virtual void Tick(FEditorViewportClient* ViewportClient, float DeltaTime) override;`
- L41 _public prototype_ `virtual void ActorSelectionChangeNotify() override;`
- L43 _public prototype_ `virtual bool ShouldDrawWidget() const override;`
- L44 _public prototype_ `virtual bool ProcessEditDelete() override;`
- L45 _public prototype_ `virtual bool ProcessEditCut() override;`
- L47 _public prototype_ `virtual bool CanAutoSave() const override;`
- L49 _public prototype_ `virtual bool ComputeBoundingBoxForViewportFocus(AActor* Actor, UPrimitiveComponent* PrimitiveComponent, FBox& InOutBox) const override;`
- L51 _public prototype_ `virtual bool GetPivotForOrbit(FVector& OutPivot) const override;`
- L53 _public function_ `virtual bool RequiresLegacyViewportInteractions() const override`
- L60 _public prototype_ `virtual void Enter() override;` — called when we "start" this editor mode (ie switch to this tab)
- L63 _public prototype_ `virtual void Exit() override;` — called when we "end" this editor mode (ie switch to another tab)
- L65 _public prototype_ `virtual bool ShouldToolStartBeAllowed(const FString& ToolIdentifier) const override;`
- L74 _protected prototype_ `virtual void BindCommands() override;`
- L75 _protected prototype_ `virtual void CreateToolkit() override;`
- L76 _protected prototype_ `virtual void OnToolStarted(UInteractiveToolManager* Manager, UInteractiveTool* Tool) override;`
- L77 _protected prototype_ `virtual void OnToolEnded(UInteractiveToolManager* Manager, UInteractiveTool* Tool) override;`
- L79 _protected prototype_ `virtual void OnToolPostBuild(UInteractiveToolManager* InToolManager, EToolSide InSide, UInteractiveTool* InBuiltTool, UInteractiveToolBuilder* InToolBuilder, const FToolBuilderState& ToolState);`
- L81 _protected prototype_ `void OnToolsContextRender(IToolsContextRenderAPI* RenderAPI);`
- L83 _protected prototype_ `void AcceptActiveToolActionOrTool();`
- L84 _protected prototype_ `void CancelActiveToolActionOrTool();`
- L86 _protected prototype_ `void ConfigureRealTimeViewportsOverride(bool bEnable);`
- L88 _protected prototype_ `void OnBlueprintPreCompile(UBlueprint* Blueprint);`
- L89 _protected member_ `FDelegateHandle BlueprintPreCompileHandle;`
- L92 _protected function_ `void OnBlueprintCompiled()` — `UE_DEPRECATED(5.6, "Deprecated in favor of OnBlueprintPreCompile")`
- L95 _protected member_ `FDelegateHandle BlueprintCompiledHandle;` — `UE_DEPRECATED(5.6, "Deprecated in favor of OnBlueprintPreCompile")`
- L97 _protected prototype_ `void InitializeModeContexts();`
- L99 _protected prototype_ `void RebuildScriptableToolSet();`
- L101 _protected prototype_ `void SetFocusInViewport();`
- L105 _private member_ `TArray<TWeakObjectPtr<UScriptableToolContextObject>> ContextsToUpdateOnToolEnd;`
- L106 _private member_ `TArray<TWeakObjectPtr<UScriptableToolContextObject>> ContextsToShutdown;`
- L108 _private member_ `bool bRebuildScriptableToolSetOnTick = false;`
- L112 _protected member_ `TObjectPtr<UScriptableToolSet> ScriptableTools;` — `UPROPERTY()`
- L114 _public function_ `virtual UScriptableToolSet* GetActiveScriptableTools()`

#### Free symbols / members of external scopes

- L14 _macro_ `#define UE_API SCRIPTABLETOOLSEDITORMODE_API`

### `Plugins/Editor/ScriptableToolsEditorMode/Source/ScriptableToolsEditorMode/Public/ScriptableToolsEditorModeManagerCommands.h` (Public)


#### class `FScriptableToolsEditorModeManagerCommands`  
`class FScriptableToolsEditorModeManagerCommands : public TCommands<FScriptableToolsEditorModeManagerCommands>`  
_L11-55_
- inherits: `TCommands<FScriptableToolsEditorModeManagerCommands>`
- desc: TInteractiveToolCommands implementation for Modeling Mode Tools
- L14 _public prototype_ `FScriptableToolsEditorModeManagerCommands();`
- L22 _protected member_ `TArray<FStartToolCommand> RegisteredTools;` — Tool start-commands listed below are stored in this list
- L28 _public prototype_ `TSharedPtr<FUICommandInfo> FindToolByName(const FString& Name, bool& bFound) const;` — Find Tool start-command below by registered name (tool icon name in Mode palette)
- L30 _public prototype_ `TSharedPtr<FUICommandInfo> RegisterCommand( FName InCommandName, const FText& InCommandLabel, const FText& InCommandTooltip, const FSlateIcon& InIcon, const EUserInterfaceActionType InUserInterfaceType, const FInputChord& InDefaultChord);`
- L38 _public prototype_ `void NotifyCommandsChanged() const;`
- L44 _public member_ `TSharedPtr<FUICommandInfo> AcceptActiveTool;`
- L45 _public member_ `TSharedPtr<FUICommandInfo> CancelActiveTool;`
- L46 _public member_ `TSharedPtr<FUICommandInfo> CompleteActiveTool;`
- L48 _public member_ `TSharedPtr<FUICommandInfo> AcceptOrCompleteActiveTool;`
- L49 _public member_ `TSharedPtr<FUICommandInfo> CancelOrCompleteActiveTool;`
- L54 _public prototype_ `virtual void RegisterCommands() override;` — Initialize above commands

#### struct `FScriptableToolsEditorModeManagerCommands::FStartToolCommand`  
`struct FStartToolCommand`  
_L17-21_
- L19 _public member_ `FString ToolUIName;`
- L20 _public member_ `TSharedPtr<FUICommandInfo> ToolCommand;`

### `Plugins/Editor/ScriptableToolsEditorMode/Source/ScriptableToolsEditorMode/Public/ScriptableToolsEditorModeModule.h` (Public)


#### class `FScriptableToolsEditorModeModule`  
`class FScriptableToolsEditorModeModule : public IModuleInterface`  
_L8-18_
- inherits: `IModuleInterface`
- L13 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface implementation
- L14 _public prototype_ `virtual void ShutdownModule() override;`
- L17 _protected prototype_ `void OnPostEngineInit();`

### `Plugins/Editor/ScriptableToolsEditorMode/Source/ScriptableToolsEditorMode/Public/ScriptableToolsEditorModeSettings.h` (Public)


#### class `UScriptableToolsModeCustomizationSettings`  
`class UScriptableToolsModeCustomizationSettings : public UDeveloperSettings`  
_L15-44_
- reflection: `UCLASS(MinimalAPI, config = Editor)`
- inherits: `UDeveloperSettings`
- L22 _public function_ `virtual FName GetContainerName() const`
- L23 _public function_ `virtual FName GetCategoryName() const`
- L24 _public function_ `virtual FName GetSectionName() const`
- L26 _public prototype_ `virtual FText GetSectionText() const override;`
- L27 _public prototype_ `virtual FText GetSectionDescription() const override;`
- L32 _public member_ `FScriptableToolGroupSet ToolRegistrationFilters;` — `UPROPERTY(config, EditAnywhere, Category = "Scriptable Tools Mode|Tool Registration", meta = (EditCondition = "!bRegisterAllTools"))`
- L36 _public member_ `bool bUseLegacyPalette = false;` — `UPROPERTY(config, EditAnywhere, Category = "Scriptable Tools Mode|UI Customization")` — Toggle between the Legacy Scriptable Tools Palette and the new UI (requires exiting and re-entering the Mode)
- L40 _public member_ `bool bAlwaysShowToolButtons = true;` — `UPROPERTY(config, EditAnywhere, Category = "Scriptable Tools Mode|UI Customization")` — If true, Tool buttons will always be shown when in a Tool. By default they will be hidden.
- L42 _public function_ `bool RegisterAllTools() const`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API SCRIPTABLETOOLSEDITORMODE_API`

### `Plugins/Editor/ScriptableToolsEditorMode/Source/ScriptableToolsEditorMode/Public/ScriptableToolsEditorModeStyle.h` (Public)


#### class `FScriptableToolsEditorModeStyle`  
`class FScriptableToolsEditorModeStyle`  
_L11-52_
- L14 _public prototype_ `static void Initialize();`
- L16 _public prototype_ `static void Shutdown();`
- L18 _public prototype_ `static TSharedPtr< class ISlateStyle > Get();`
- L20 _public prototype_ `static FName GetStyleSetName();`
- L23 _public prototype_ `static const FSlateBrush* GetBrush(FName PropertyName, const ANSICHAR* Specifier = NULL);` — use to access icons defined by the style set by name, eg GetBrush("BrushFalloffIcons.Smooth")
- L37 _public prototype_ `static bool TryRegisterCustomIcon(FName StyleIconIdentifier, FString FileNameWithPath, FString ExternalRelativePath);` — `UE_DEPRECATED(5.7, "Use RegisterIconTexture(s) instead.")` — Try to find a png or svg icon at FileNameWithPath and register it in the style set with the given StyleIconIdentifier, ie so that later it can be found FSlateIcon(FScriptableToolsEditorModeStyle::Get()->GetStyleSetName(), StyleIconIdentifier). This is intended to be used for (eg) custom icons defined in Scriptable Tool Blueprints, that are not known at compile time. Will print error and return false if image is not found, or not png/svg format. FileNameWithPath must be the full on-disk path to the icon, which is constructed in code from a relative path the user enters as (eg) a property/etc. To help with debugging, this path can be provided as ExternalRelativePath, and it will be printed out instead of the absolute path as part of the log error message.
- L40 _public typedef_ `using FIconTextureMap = TMap<FName, TObjectPtr<UTexture2D>>;` — Register tool icons from a UTexture2D
- L41 _public prototype_ `static bool RegisterIconTexture(FName StyleIdentifier, TObjectPtr<UTexture2D> InTexture);`
- L42 _public prototype_ `static void RegisterIconTextures(const FIconTextureMap& InIcons);`
- L46 _private prototype_ `static FString InContent(const FString& RelativePath, const ANSICHAR* Extension);`
- L49 _private member_ `static TSharedPtr< class FSlateStyleSet > StyleSet;`
- L51 _private member_ `static TMap<FName, FSlateBrush*> IconTextureBrushes;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API SCRIPTABLETOOLSEDITORMODE_API`

### `Plugins/Editor/ScriptableToolsEditorMode/Source/ScriptableToolsEditorMode/Public/ScriptableToolsEditorModeToolkit.h` (Public)


#### class `FScriptableToolsEditorModeToolkit`  
`class FScriptableToolsEditorModeToolkit : public FModeToolkit`  
_L21-148_
- inherits: `FModeToolkit`
- L25 _public prototype_ `FScriptableToolsEditorModeToolkit();`
- L26 _public prototype_ `~FScriptableToolsEditorModeToolkit();`
- L29 _public prototype_ `virtual void Init(const TSharedPtr<IToolkitHost>& InitToolkitHost, TWeakObjectPtr<UEdMode> InOwningMode) override;` — FModeToolkit interface
- L32 _public prototype_ `virtual FName GetToolkitFName() const override;` — IToolkit interface
- L33 _public prototype_ `virtual FText GetBaseToolkitName() const override;`
- L34 _public function_ `virtual TSharedPtr<class SWidget> GetInlineContent() const override`
- L37 _public prototype_ `virtual void InitializeAfterModeSetup();` — initialize toolkit widgets that need to wait until mode is initialized/entered
- L40 _public prototype_ `virtual void PostNotification(const FText& Message);` — set/clear notification message area
- L41 _public prototype_ `virtual void ClearNotification();`
- L44 _public prototype_ `virtual void PostWarning(const FText& Message);` — set/clear warning message area
- L45 _public prototype_ `virtual void ClearWarning();`
- L48 _public prototype_ `void StartAsyncToolLoading();` — Async Tool Loading
- L49 _public prototype_ `void SetAsyncProgress(float PercentLoaded);`
- L50 _public prototype_ `void EndAsyncToolLoading();`
- L51 _public prototype_ `bool AreToolsLoading() const;`
- L52 _public prototype_ `TOptional<float> GetToolPercentLoaded() const;`
- L55 _public prototype_ `virtual void GetToolPaletteNames(TArray<FName>& InPaletteName) const override;` — Returns the Mode specific tabs in the mode toolbar
- L56 _public prototype_ `virtual FText GetToolPaletteDisplayName(FName PaletteName) const override;`
- L57 _public prototype_ `virtual void BuildToolPalette(FName PaletteName, class FToolBarBuilder& ToolbarBuilder) override;`
- L58 _public prototype_ `virtual void OnToolPaletteChanged(FName PaletteName) override;`
- L59 _public function_ `virtual bool HasIntegratedToolPalettes() const override`
- L60 _public function_ `virtual bool HasExclusiveToolPalettes() const override`
- L62 _public function_ `virtual FText GetActiveToolDisplayName() const override`
- L63 _public function_ `virtual FText GetActiveToolMessage() const override`
- L65 _public prototype_ `virtual void EnableShowRealtimeWarning(bool bEnable);`
- L67 _public prototype_ `virtual void OnToolStarted(UInteractiveToolManager* Manager, UInteractiveTool* Tool) override;`
- L68 _public prototype_ `virtual void OnToolEnded(UInteractiveToolManager* Manager, UInteractiveTool* Tool) override;`
- L70 _public prototype_ `virtual void CustomizeModeDetailsViewArgs(FDetailsViewArgs& ArgsInOut) override;`
- L72 _public prototype_ `void OnActiveViewportChanged(TSharedPtr<IAssetViewport>, TSharedPtr<IAssetViewport> );`
- L74 _public prototype_ `virtual void InvokeUI() override;`
- L76 _public prototype_ `virtual void ForceToolPaletteRebuild();`
- L78 _public prototype_ `void GetActiveToolPaletteNames(TArray<FName>& OutPaletteNames);`
- L80 _public prototype_ `void SetShowToolTagFilterBar(bool bShowToolTagFilterBarIn);`
- L86 _protected prototype_ `virtual void RebuildModeToolBar() override;` — FModeToolkit interface
- L87 _protected prototype_ `virtual bool ShouldShowModeToolbar() const override;`
- L89 _protected prototype_ `void RebuildModeToolPaletteWidgets();`
- L90 _protected prototype_ `void RebuildModeToolkitBuilderPalettes();`
- L94 _private member_ `const static TArray<FName> PaletteNames_Standard;`
- L96 _private member_ `FText ActiveToolName;`
- L97 _private member_ `FText ActiveToolMessage;`
- L98 _private member_ `FStatusBarMessageHandle ActiveToolMessageHandle;`
- L99 _private member_ `const FSlateBrush* ActiveToolIcon = nullptr;`
- L101 _private member_ `TSharedPtr<SWidget> ToolkitWidget;`
- L102 _private prototype_ `void UpdateActiveToolProperties();`
- L103 _private prototype_ `void InvalidateCachedDetailPanelState(UObject* ChangedObject);`
- L105 _private prototype_ `void RegisterPalettes();`
- L106 _private member_ `FDelegateHandle ActivePaletteChangedHandle;`
- L108 _private member_ `TSharedPtr<SWidget> ViewportOverlayWidget;`
- L110 _private member_ `TSharedPtr<STextBlock> ModeWarningArea;`
- L111 _private member_ `TSharedPtr<STextBlock> ModeHeaderArea;`
- L112 _private member_ `TSharedPtr<STextBlock> ToolWarningArea;`
- L113 _private member_ `TSharedPtr<SButton> AcceptButton;`
- L114 _private member_ `TSharedPtr<SButton> CancelButton;`
- L115 _private member_ `TSharedPtr<SButton> CompletedButton;`
- L118 _private member_ `bool bAsyncLoadInProgress = false;` — Palette
- L119 _private member_ `float AsyncLoadProgress;`
- L121 _private member_ `TSharedPtr<SVerticalBox> ToolBoxVBox;`
- L122 _private member_ `FDelegateHandle SettingsUpdateHandle;`
- L124 _private member_ `TSharedPtr<SWidget> ToolPaletteHeader;`
- L125 _private member_ `TSharedPtr<SWidget> ToolPaletteTagPanel;`
- L126 _private member_ `TSharedPtr<SWidget> ToolPaletteLoadBar;`
- L127 _private member_ `TSharedPtr<SVerticalBox> ToolDetailsHeader;`
- L129 _private member_ `bool bShowRealtimeWarning = false;`
- L130 _private prototype_ `void UpdateShowWarnings();`
- L138 _private member_ `TMap<FName, TArray<FScriptableToolData>> ActiveToolCategories;`
- L139 _private prototype_ `void UpdateActiveToolCategories();`
- L141 _private member_ `bool bFirstInitializeAfterModeSetup = true;`
- L143 _private member_ `bool bShowActiveSelectionActions = false;`
- L145 _private member_ `bool bShowToolTagFilterBar = true;`

#### struct `FScriptableToolsEditorModeToolkit::FScriptableToolData`  
`struct FScriptableToolData`  
_L132-137_
- L134 _public member_ `FText Category;`
- L135 _public member_ `UClass* ToolClass = nullptr;`
- L136 _public member_ `UBaseScriptableToolBuilder* Builder = nullptr;`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API SCRIPTABLETOOLSEDITORMODE_API`

### `Plugins/Editor/ScriptableToolsEditorMode/Source/ScriptableToolsEditorMode/Public/Tags/EditableScriptableToolGroupSet.h` (Public)


#### class `UEditableScriptableToolGroupSet`  
`class UEditableScriptableToolGroupSet : public UObject`  
_L10-28_
- reflection: `UCLASS(Transient, MinimalAPI)`
- inherits: `UObject`
- L15 _public prototype_ `UEditableScriptableToolGroupSet();`
- L17 _public prototype_ `void SetGroups(const FScriptableToolGroupSet::FGroupSet& InGroups);`
- L18 _public prototype_ `FScriptableToolGroupSet::FGroupSet& GetGroups();`
- L20 _public prototype_ `FString GetGroupSetExportText();`
- L24 _private member_ `FScriptableToolGroupSet GroupSet;` — `UPROPERTY()`
- L26 _private member_ `FProperty* GroupsProperty;`
- L27 _private member_ `FString GroupsPropertyAsString;`

### `Plugins/Editor/ScriptableToolsEditorMode/Source/ScriptableToolsEditorMode/Public/UI/SScriptableToolGroupSetCombo.h` (Public)


#### class `SScriptableToolGroupSetCombo`  
`class SScriptableToolGroupSetCombo : public SCompoundWidget`  
_L23-82_
- inherits: `SCompoundWidget`
- desc: Widget for editing a group set.
- L29 _public prototype_ `DECLARE_DELEGATE(FOnChanged);`
- L31 _public function_ `SLATE_BEGIN_ARGS(SScriptableToolGroupSetCombo) : _StructPropertyHandle(nullptr), _StructPtr(nullptr)`
- L34 _public prototype_ `SLATE_EVENT(FOnChanged, OnChanged)`
- L42 _public prototype_ `void Construct(const FArguments& InArgs);`
- L45 _public prototype_ `void ForceUpdate();` — Used to update internal state based on underlying data by external clients
- L49 _protected prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;`
- L53 _private prototype_ `TSharedRef<ITableRow> OnGenerateRow(UClass* InGroup, const TSharedRef<STableViewBase>& OwnerTable);` — Returns a table row with an SScriptableToolGroupTagChip.
- L56 _private prototype_ `TSharedRef<SWidget> OnGetMenuContent();` — Instantiates the tag picker and sets it as the widget to focus for the ComboButton.
- L59 _private prototype_ `FReply OnClearTagClicked(UClass* InGroup);` — Bound to/called via SScriptableToolGroupTagChip::OnClearPressed. Removes TagToClear from group set.
- L62 _private prototype_ `void RefreshListView();` — Populates ActiveGroupTags with the groups currently active on the group set.
- L65 _private member_ `TArray<UClass*> ActiveGroupTags;` — The set of group tags to display, based on the group tags present in the group set we are editing.
- L66 _private member_ `TSharedPtr<SListView<UClass*>> ActiveGroupTagsListView;`
- L69 _private member_ `TSharedPtr<SComboButton> ComboButton;` — Widgets we retain ownership of and refer to in a named manner.
- L70 _private member_ `TSharedPtr<SScriptableToolGroupSetPicker> TagPicker;`
- L73 _private member_ `TSharedPtr<IPropertyHandle> StructPropertyHandle;` — Property handle to an FScriptableToolGroupSet, used for accessing the source group set.
- L76 _private member_ `FScriptableToolGroupSet* StructPtr;` — A direct pointer to a group Set, an alternate pathway to the PropertyHandle
- L79 _private member_ `TStrongObjectPtr<UEditableScriptableToolGroupSet> HelperGroupSet;` — A helper class which is used for propagating changes to the source group set.
- L81 _private member_ `FOnChanged OnChanged;`

#### Free symbols / members of external scopes

- L29 _delegate_ `DECLARE_DELEGATE(FOnChanged);`

### `Plugins/Editor/ScriptableToolsEditorMode/Source/ScriptableToolsEditorMode/Public/UI/SScriptableToolGroupSetPicker.h` (Public)


#### class `SScriptableToolGroupSetPicker`  
`class SScriptableToolGroupSetPicker : public SCompoundWidget`  
_L26-93_
- inherits: `SCompoundWidget`
- desc: Widget allowing user to edit the group tags in a given group set.
- L29 _public prototype_ `DECLARE_DELEGATE(FOnChanged);`
- L31 _public function_ `SLATE_BEGIN_ARGS(SScriptableToolGroupSetPicker) : _StructPropertyHandle(nullptr)`
- L34 _public prototype_ `SLATE_EVENT(FOnChanged, OnChanged)`
- L45 _public prototype_ `void ForceUpdate();` — Used to update internal state based on underlying data by external clients
- L48 _private prototype_ `TSharedRef<SWidget> GetChildWidget();`
- L49 _private prototype_ `TSharedRef<ITableRow> OnGenerateRow(UClass* InItem, const TSharedRef<STableViewBase>& OwnerTable);`
- L52 _private prototype_ `void OnSearchStringChanged(const FText& NewString);` — Members for tracking and using search text.
- L53 _private member_ `TSharedPtr<SSearchBox> GroupSearchBox;`
- L54 _private member_ `FString SearchString;`
- L57 _private prototype_ `void RefreshListView();` — Populate VisibleGroupTags with the correct subset of AllGroupTags given our current search text.
- L60 _private member_ `TArray<UClass*> VisibleGroupTags;` — The set of group tags to display, based on our current search text.
- L61 _private member_ `TSharedPtr<SListView<UClass*>> VisibleGroupTagsListView;`
- L64 _private prototype_ `void PopulateVisibleClasses();` — Queries the asset registry to get all known group tags.
- L67 _private member_ `TArray<UClass*> AllGroupTags;` — The set of group tags which can be displayed.
- L70 _private prototype_ `ECheckBoxState IsTagChecked(UClass* InTag);` — Functions for querying the group set for information about a particular tag.
- L71 _private prototype_ `void PopulateCheckedTags();`
- L72 _private member_ `TMap<UClass*, bool> CheckedTags;`
- L75 _private prototype_ `void OnTagChecked(UClass* NodeChecked);` — Functions for adding/removing tags to/from the group set.
- L76 _private prototype_ `void OnTagUnchecked(UClass* NodeUnchecked);`
- L77 _private prototype_ `void OnUncheckAllTags();`
- L78 _private prototype_ `void OnCreateNewTag();`
- L81 _private prototype_ `void FlushHelperGroupSet() const;` — Brings the source group set to parity with HelperGroupSet. Generally called immediately after modifying HelperGroupSet.
- L84 _private member_ `TSharedPtr<IPropertyHandle> StructPropertyHandle;` — Property handle to an FScriptableToolGroupSet, used for accessing the source group set.
- L87 _private member_ `FScriptableToolGroupSet* StructPtr;` — A direct pointer to a Group Set, an alternate pathway to the PropertyHandle
- L90 _private member_ `TStrongObjectPtr<UEditableScriptableToolGroupSet> HelperGroupSet;` — A helper class which is used for propagating changes to the source group set.
- L92 _private member_ `FOnChanged OnChanged;`

#### Free symbols / members of external scopes

- L29 _delegate_ `DECLARE_DELEGATE(FOnChanged);`

### `Plugins/Editor/ScriptableToolsEditorMode/Source/ScriptableToolsEditorMode/Public/UI/SScriptableToolGroupTagChip.h` (Public)


#### class `SScriptableToolGroupTagChip`  
`class SScriptableToolGroupTagChip : public SCompoundWidget`  
_L13-51_
- inherits: `SCompoundWidget`
- desc: Widget for displaying a single group tag.
- L19 _public prototype_ `DECLARE_DELEGATE_RetVal(FReply, FOnClearPressed);`
- L21 _public function_ `SLATE_BEGIN_ARGS(SScriptableToolGroupTagChip)`
- L24 _public prototype_ `SLATE_ARGUMENT(UClass*, TagClass)` — The group subclass associated with this chip.
- L36 _public prototype_ `SScriptableToolGroupTagChip();`
- L37 _public prototype_ `void Construct(const FArguments& InArgs);`
- L40 _public member_ `inline static constexpr float ChipHeight = 25.f;` — This is public because it is used in SScriptableToolGroupSetCombo and SScriptableToolGroupSetPicker.
- L43 _private member_ `TSlateAttribute<FText> ToolTipTextAttribute;`
- L44 _private member_ `TSlateAttribute<FText> TextAttribute;`
- L46 _private member_ `FOnClearPressed OnClearPressed;`
- L48 _private member_ `TSharedPtr<SButton> ClearButton;`
- L50 _private member_ `UClass* TagClass;`

#### Free symbols / members of external scopes

- L19 _delegate_ `DECLARE_DELEGATE_RetVal(FReply, FOnClearPressed);`

### `Plugins/Editor/ScriptableToolsEditorMode/Source/ScriptableToolsEditorMode/Public/UI/ScriptableToolGroupSetCustomization.h` (Public)


#### class `FScriptableToolGroupSetCustomization`  
`class FScriptableToolGroupSetCustomization : public IPropertyTypeCustomization`  
_L10-18_
- inherits: `IPropertyTypeCustomization`
- L13 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance();`
- L16 _public prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> StructPropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& CustomizationUtils) override;` — IPropertyTypeCustomization interface
- L17 _public prototype_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> StructPropertyHandle, IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& CustomizationUtils) override;`
