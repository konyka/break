# Plugins / AvalancheTransitionEditor

- module root: `Plugins/VirtualProduction/Avalanche/Source/AvalancheTransitionEditor`
- headers: 85; symbols: 727
- symbol kinds: class=70, delegate=4, enum=3, enumerator=11, function=82, macro=3, member=142, namespace=6, prototype=391, struct=11, typedef=1, variable=3
- PrivateDependencyModuleNames: ApplicationCore, AssetDefinition, AssetTools, AvalancheCore, AvalancheTransition, DeveloperSettings, EditorStyle, Engine, InputCore, MessageLog, Projects, PropertyBindingUtils, PropertyEditor, Slate, SlateCore, StateTreeModule, StructUtilsEditor, ToolMenus, UnrealEd
- PublicDependencyModuleNames: AvalancheTag, Core, CoreUObject, StateTreeEditorModule

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheTransitionEditor/Private/Actions/AvaTransitionActions.h` (Private)


#### class `FAvaTransitionActions`  
`class FAvaTransitionActions : public TSharedFromThis<FAvaTransitionActions>`  
_L10-23_
- inherits: `TSharedFromThis<FAvaTransitionActions>`
- L13 _public prototype_ `explicit FAvaTransitionActions(FAvaTransitionEditorViewModel& InOwner);`
- L15 _public prototype_ `virtual ~FAvaTransitionActions() = default;`
- L17 _public prototype_ `virtual void BindCommands(const TSharedRef<FUICommandList>& InCommandList) = 0;`
- L19 _public prototype_ `bool IsEditMode() const;`
- L22 _protected member_ `FAvaTransitionEditorViewModel& Owner;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheTransitionEditor/Private/Actions/AvaTransitionStateActions.h` (Private)


#### class `FAvaTransitionStateActions`  
`class FAvaTransitionStateActions : public FAvaTransitionActions`  
_L15-65_
- inherits: `FAvaTransitionActions`
- L18 _public function_ `explicit FAvaTransitionStateActions(FAvaTransitionEditorViewModel& InOwner) : FAvaTransitionActions(InOwner)`
- L23 _public prototype_ `static bool CanAddStatesFromDrop(const TSharedRef<FAvaTransitionViewModel>& InTarget, const FAvaTransitionStateDragDropOp& InStateDragDropOp);`
- L25 _public prototype_ `static bool AddStatesFromDrop(const TSharedRef<FAvaTransitionViewModel>& InTarget, EItemDropZone InDropZone, const FAvaTransitionStateDragDropOp& InStateDragDropOp);`
- L29 _protected prototype_ `virtual void BindCommands(const TSharedRef<FUICommandList>& InCommandList) override;`
- L32 _protected prototype_ `TConstArrayView<TSharedRef<FAvaTransitionViewModel>> GetSelectedViewModels() const;`
- L34 _protected prototype_ `TArray<UStateTreeState*> GetSelectedStates() const;`
- L36 _protected prototype_ `TSharedPtr<FAvaTransitionStateViewModel> GetLastSelectedStateViewModel() const;`
- L38 _protected prototype_ `bool HasSelectedStates() const;`
- L40 _protected prototype_ `bool CanEditSelectedStates() const;`
- L42 _protected prototype_ `bool CanAddStateComment() const;`
- L43 _protected prototype_ `void AddStateComment();`
- L45 _protected prototype_ `bool CanRemoveStateComment() const;`
- L46 _protected prototype_ `void RemoveStateComment();`
- L48 _protected prototype_ `void AddState(EItemDropZone InDropZone);`
- L50 _protected prototype_ `bool AreStatesEnabled() const;`
- L51 _protected prototype_ `void ToggleEnableStates();`
- L53 _protected prototype_ `void CopyStates(bool bInDeleteStatesAfterCopy);`
- L55 _protected prototype_ `void PasteStates();`
- L57 _protected prototype_ `void DuplicateStates();`
- L59 _protected prototype_ `void DeleteStates();`
- L62 _private prototype_ `static bool AddStates(const TSharedRef<FAvaTransitionViewModel>& InTarget, EItemDropZone InDropZone, TArray<UStateTreeState*> InStates);`
- L64 _private prototype_ `void DeleteStates(UAvaTransitionTreeEditorData& InEditorData, TConstArrayView<UStateTreeState*> InStates);`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheTransitionEditor/Private/Actions/AvaTransitionTreeActions.h` (Private)


#### class `FAvaTransitionTreeActions`  
`class FAvaTransitionTreeActions : public FAvaTransitionActions`  
_L10-36_
- inherits: `FAvaTransitionActions`
- L13 _public function_ `explicit FAvaTransitionTreeActions(FAvaTransitionEditorViewModel& InOwner) : FAvaTransitionActions(InOwner)`
- L20 _protected prototype_ `virtual void BindCommands(const TSharedRef<FUICommandList>& InCommandList) override;`
- L23 _protected prototype_ `bool CanShowExportTransitionTree() const;`
- L25 _protected prototype_ `void ExportTransitionTree();`
- L27 _protected prototype_ `void ImportTransitionTree();`
- L29 _protected prototype_ `void ImportTransitionTree(UAvaTransitionTree* InTemplateTree);`
- L32 _protected prototype_ `void ToggleDebugger();`
- L34 _protected prototype_ `bool IsDebuggerActive() const;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheTransitionEditor/Private/AppModes/AvaTransitionAdvancedMode.h` (Private)


#### class `FAvaTransitionAdvancedMode`  
`class FAvaTransitionAdvancedMode : public FAvaTransitionAppMode`  
_L7-11_
- inherits: `FAvaTransitionAppMode`
- L10 _public prototype_ `FAvaTransitionAdvancedMode(const TSharedRef<FAvaTransitionEditor>& InEditor);`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheTransitionEditor/Private/AppModes/AvaTransitionAppMode.h` (Private)


#### class `FAvaTransitionAppMode`  
`class FAvaTransitionAppMode : public FApplicationMode`  
_L14-39_
- inherits: `FApplicationMode`
- L17 _public prototype_ `static FName StaticGetModeName(EAvaTransitionEditorMode InEditorMode);`
- L19 _public prototype_ `FAvaTransitionAppMode(const TSharedRef<FAvaTransitionEditor>& InEditor, EAvaTransitionEditorMode InEditorMode);`
- L21 _public prototype_ `void AddToToolbar(const TSharedRef<FExtender>& InToolbarExtender);`
- L24 _protected prototype_ `void RegisterDefaultTabFactories();`
- L26 _protected prototype_ `void ExtendToolbar(FToolBarBuilder& InToolbarBuilder);`
- L29 _protected prototype_ `virtual void RegisterTabFactories(TSharedPtr<FTabManager> InTabManager) override final;`
- L32 _protected member_ `TWeakPtr<FAvaTransitionEditor> EditorWeak;`
- L34 _protected member_ `FWorkflowAllowedTabSet TabFactories;`
- L36 _protected member_ `TAttribute<const FSlateBrush*> ModeIcon;`
- L38 _protected member_ `EAvaTransitionEditorMode EditorMode;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheTransitionEditor/Private/AppModes/AvaTransitionParameterMode.h` (Private)


#### class `FAvaTransitionParameterMode`  
`class FAvaTransitionParameterMode : public FAvaTransitionAppMode`  
_L7-11_
- inherits: `FAvaTransitionAppMode`
- L10 _public prototype_ `FAvaTransitionParameterMode(const TSharedRef<FAvaTransitionEditor>& InEditor);`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheTransitionEditor/Private/AppModes/AvaTransitionSimpleMode.h` (Private)


#### class `FAvaTransitionSimpleMode`  
`class FAvaTransitionSimpleMode : public FAvaTransitionAppMode`  
_L7-11_
- inherits: `FAvaTransitionAppMode`
- L10 _public prototype_ `FAvaTransitionSimpleMode(const TSharedRef<FAvaTransitionEditor>& InEditor);`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheTransitionEditor/Private/AssetDefinition_AvaTransitionTree.h` (Private)


#### class `UAssetDefinition_AvaTransitionTree`  
`class UAssetDefinition_AvaTransitionTree : public UAssetDefinitionDefault`  
_L9-21_
- reflection: `UCLASS()`
- inherits: `UAssetDefinitionDefault`
- L15 _public prototype_ `virtual FText GetAssetDisplayName() const override;`
- L16 _public prototype_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override;`
- L17 _public prototype_ `virtual FLinearColor GetAssetColor() const override;`
- L18 _public prototype_ `virtual EAssetCommandResult OpenAssets(const FAssetOpenArgs& InOpenArgs) const override;`
- L19 _public prototype_ `virtual FAssetOpenSupport GetAssetOpenSupport(const FAssetOpenSupportArgs& InOpenSupportArgs) const override;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheTransitionEditor/Private/AvaTransitionCommands.h` (Private)


#### class `FAvaTransitionEditorCommands`  
`class FAvaTransitionEditorCommands : public TCommands<FAvaTransitionEditorCommands>`  
_L8-35_
- inherits: `TCommands<FAvaTransitionEditorCommands>`
- L11 _public prototype_ `FAvaTransitionEditorCommands();`
- L14 _public prototype_ `virtual void RegisterCommands() override;`
- L17 _public member_ `TSharedPtr<FUICommandInfo> AddComment;`
- L18 _public member_ `TSharedPtr<FUICommandInfo> RemoveComment;`
- L20 _public member_ `TSharedPtr<FUICommandInfo> AddSiblingState;`
- L21 _public member_ `TSharedPtr<FUICommandInfo> AddChildState;`
- L22 _public member_ `TSharedPtr<FUICommandInfo> EnableStates;`
- L24 _public member_ `TSharedPtr<FUICommandInfo> ImportTransitionTree;`
- L25 _public member_ `TSharedPtr<FUICommandInfo> ExportTransitionTree;`
- L27 _public member_ `TSharedPtr<FUICommandInfo> Compile;`
- L28 _public member_ `TSharedPtr<FUICommandInfo> SaveOnCompile_Never;`
- L29 _public member_ `TSharedPtr<FUICommandInfo> SaveOnCompile_SuccessOnly;`
- L30 _public member_ `TSharedPtr<FUICommandInfo> SaveOnCompile_Always;`
- L33 _public member_ `TSharedPtr<FUICommandInfo> ToggleDebug;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheTransitionEditor/Private/AvaTransitionEditor.h` (Private)


#### struct `FAvaTransitionEditorInitSettings`  
`struct FAvaTransitionEditorInitSettings`  
_L14-28_
- L16 _public function_ `explicit FAvaTransitionEditorInitSettings(const FAssetOpenArgs& InOpenArgs) : ToolkitHost(InOpenArgs.ToolkitHost) , ToolkitMode(InOpenArgs.GetToolkitMode()) , OpenMethod(InOpenArgs.OpenMethod)`
- L23 _public member_ `TSharedPtr<IToolkitHost> ToolkitHost;`
- L25 _public member_ `EToolkitMode::Type ToolkitMode;`
- L27 _public member_ `EAssetOpenMethod OpenMethod;`

#### class `FAvaTransitionEditor`  
`class FAvaTransitionEditor : public FWorkflowCentricApplication`  
_L30-75_
- inherits: `FWorkflowCentricApplication`
- L32 _private member_ `static const FName ToolkitName;`
- L35 _public prototype_ `FAvaTransitionEditor();`
- L37 _public prototype_ `void InitEditor(UAvaTransitionTree* InTransitionTree, const FAvaTransitionEditorInitSettings& InInitSettings);`
- L39 _public function_ `TSharedPtr<FAvaTransitionEditorViewModel> GetEditorViewModel() const`
- L44 _public prototype_ `void SetEditorMode(EAvaTransitionEditorMode InEditorMode);`
- L46 _public function_ `bool IsReadOnly() const`
- L52 _protected prototype_ `void RegisterApplicationModes();`
- L54 _protected prototype_ `void ExtendMenus();`
- L56 _protected prototype_ `void ExtendToolbar(UToolMenu* InToolMenu);`
- L59 _protected prototype_ `virtual void SetupReadOnlyMenuProfiles(FReadOnlyAssetEditorCustomization& InReadOnlyCustomization) override;`
- L63 _protected prototype_ `virtual FName GetToolkitFName() const override;`
- L64 _protected prototype_ `virtual FText GetBaseToolkitName() const override;`
- L65 _protected prototype_ `virtual FString GetWorldCentricTabPrefix() const override;`
- L66 _protected prototype_ `virtual FLinearColor GetWorldCentricTabColorScale() const override;`
- L70 _private member_ `TSharedPtr<FAvaTransitionEditorViewModel> EditorViewModel;`
- L72 _private member_ `TSharedRef<FExtender> ToolbarExtender;`
- L74 _private member_ `bool bReadOnly = false;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheTransitionEditor/Private/AvaTransitionEditorEnums.h` (Private)


#### enum `EAvaTransitionEditorMode`  
`enum class EAvaTransitionEditorMode : uint8`  
_L7-17_
- L10 _public enumerator_ `Default` — Simplified view of the State Tree. Core features for most Transition Logic Needs
- L13 _public enumerator_ `Advanced` — All the features in State Tree
- L16 _public enumerator_ `Parameter` — Only Parameters shown

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheTransitionEditor/Private/AvaTransitionEditorLog.h` (Private)


#### Free symbols / members of external scopes

- L7 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogAvaEditorTransition, Log, All);`
- L7 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogAvaEditorTransition, Log, All);`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheTransitionEditor/Private/AvaTransitionEditorModule.h` (Private)


#### class `FAvaTransitionEditorModule`  
`class FAvaTransitionEditorModule : public IAvaTransitionEditorModule`  
_L10-25_
- inherits: `IAvaTransitionEditorModule`
- L13 _private prototype_ `virtual void StartupModule() override;`
- L14 _private prototype_ `virtual void ShutdownModule() override;`
- L18 _private prototype_ `virtual FOnBuildDefaultTransitionTree& GetOnBuildDefaultTransitionTree() override;`
- L19 _private prototype_ `virtual void GenerateTransitionTreeOptionsMenu(UToolMenu* InMenu, IAvaTransitionBehavior* InTransitionBehavior) override;`
- L22 _private prototype_ `void ValidateStateTree(UAvaTransitionTree* InTransitionTree);`
- L24 _private member_ `FOnBuildDefaultTransitionTree OnBuildDefaultTransitionTree;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheTransitionEditor/Private/AvaTransitionEditorUtils.h` (Private)


#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace AvaTransitionEditor` (scope `UE`)
- L15 _prototype_ `TSharedPtr<SWidget> CreateTransitionStatusWidget(IAvaTransitionBehavior* InTransitionBehavior);` (scope `UE::AvaTransitionEditor`)
- L17 _prototype_ `TSharedPtr<SWidget> CreateTransitionLayerPicker(IAvaTransitionBehavior* InTransitionBehavior);` (scope `UE::AvaTransitionEditor`)
- L19 _prototype_ `TSharedPtr<SWidget> CreateTransitionInstancingModeSelector(IAvaTransitionBehavior* InTransitionBehavior);` (scope `UE::AvaTransitionEditor`)
- L21 _prototype_ `void ValidateTree(UAvaTransitionTree& InTransitionTree);` (scope `UE::AvaTransitionEditor`)
- L23 _prototype_ `uint32 CalculateTreeHash(UAvaTransitionTree& InTransitionTree);` (scope `UE::AvaTransitionEditor`)
- L25 _prototype_ `bool PickTransitionTreeAsset(const FText& InDialogTitle, UAvaTransitionTree*& OutTransitionTree);` (scope `UE::AvaTransitionEditor`)
- L27 _prototype_ `void ToggleTransitionTreeEnabled(TWeakInterfacePtr<IAvaTransitionBehavior> InTransitionBehaviorWeak);` (scope `UE::AvaTransitionEditor`)
- L29 _prototype_ `bool IsTransitionTreeEnabled(TWeakInterfacePtr<IAvaTransitionBehavior> InTransitionBehaviorWeak);` (scope `UE::AvaTransitionEditor`)

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheTransitionEditor/Private/AvaTransitionSelection.h` (Private)


#### class `FAvaTransitionSelection`  
`class FAvaTransitionSelection : public TSharedFromThis<FAvaTransitionSelection>`  
_L13-35_
- inherits: `TSharedFromThis<FAvaTransitionSelection>`
- L16 _public prototype_ `void SetSelectedItems(TConstArrayView<TSharedPtr<FAvaTransitionViewModel>> InSelectedItems);`
- L18 _public prototype_ `void ClearSelectedItems();`
- L20 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnSelectionChanged, TConstArrayView<TSharedRef<FAvaTransitionViewModel>>);`
- L21 _public function_ `FOnSelectionChanged& OnSelectionChanged()`
- L26 _public function_ `TConstArrayView<TSharedRef<FAvaTransitionViewModel>> GetSelectedItems() const`
- L32 _private member_ `TArray<TSharedRef<FAvaTransitionViewModel>> SelectedViewModels;`
- L34 _private member_ `FOnSelectionChanged OnSelectionChangedDelegate;`

#### Free symbols / members of external scopes

- L20 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnSelectionChanged, TConstArrayView<TSharedRef<FAvaTransitionViewModel>>);`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheTransitionEditor/Private/AvaTransitionTreeFactory.h` (Private)


#### class `UAvaTransitionTreeFactory`  
`class UAvaTransitionTreeFactory : public UFactory`  
_L9-20_
- reflection: `UCLASS()`
- inherits: `UFactory`
- L14 _public prototype_ `UAvaTransitionTreeFactory();`
- L17 _public prototype_ `virtual uint32 GetMenuCategories() const override;`
- L18 _public prototype_ `virtual UObject* FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags InFlags, UObject* InContext, FFeedbackContext* InWarn) override;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheTransitionEditor/Private/Compiler/AvaTransitionCompiler.h` (Private)


#### class `FAvaTransitionCompiler`  
`class FAvaTransitionCompiler`  
_L17-52_
- L20 _public prototype_ `FAvaTransitionCompiler();`
- L22 _public prototype_ `void SetTransitionTree(UAvaTransitionTree* InTransitionTree);`
- L24 _public prototype_ `IMessageLogListing& GetCompilerResultsListing();`
- L26 _public prototype_ `FSimpleDelegate& GetOnCompileFailed();`
- L28 _public prototype_ `bool Compile(EAvaTransitionEditorMode InCompileMode);`
- L30 _public prototype_ `void UpdateTree();`
- L32 _public prototype_ `FSlateIcon GetCompileStatusIcon() const;`
- L34 _public prototype_ `TSharedRef<SWidget> CreateCompilerResultsWidget() const;`
- L36 _public prototype_ `static void SetSaveOnCompile(EStateTreeSaveOnCompile InSaveOnCompileType);`
- L38 _public prototype_ `static bool HasSaveOnCompile(EStateTreeSaveOnCompile InSaveOnCompileType);`
- L40 _public prototype_ `static void GenerateCompileOptionsMenu(UToolMenu* InMenu);`
- L43 _private member_ `TWeakObjectPtr<UAvaTransitionTree> TransitionTreeWeak;`
- L45 _private member_ `TSharedRef<IMessageLogListing> CompilerResultsListing;`
- L47 _private member_ `FSimpleDelegate OnCompileFail;`
- L49 _private member_ `uint32 EditorDataHash = 0;`
- L51 _private member_ `bool bLastCompileSucceeded = true;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheTransitionEditor/Private/Customizations/AvaStateTreeStateCustomization.h` (Private)


#### class `FAvaStateTreeStateCustomization`  
`class FAvaStateTreeStateCustomization : public IDetailCustomization`  
_L10-24_
- inherits: `IDetailCustomization`
- desc: Customization that re-uses the module-registered Customization for UStateTreeState, and tweaks a few settings for it
- L13 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();`
- L15 _public prototype_ `static bool IsPropertyVisible(const FPropertyAndParent& InPropertyAndParent);`
- L19 _protected prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& InDetailBuilder) override;`
- L23 _private prototype_ `TSharedPtr<IDetailCustomization> GetDefaultCustomization() const;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheTransitionEditor/Private/Customizations/AvaTransitionTreeEditorDataCustomization.h` (Private)


#### class `FAvaTransitionTreeEditorDataCustomization`  
`class FAvaTransitionTreeEditorDataCustomization : public IDetailCustomization`  
_L11-31_
- inherits: `IDetailCustomization`
- desc: Customization that re-uses the module-registered Customization for UStateTreeEditorData, and tweaks a few settings for it
- L14 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance(TWeakPtr<FAvaTransitionViewModelSharedData> InSharedDataWeak);`
- L16 _public prototype_ `FAvaTransitionTreeEditorDataCustomization(const TWeakPtr<FAvaTransitionViewModelSharedData>& InSharedDataWeak);`
- L20 _protected prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& InDetailBuilder) override;`
- L24 _private prototype_ `void CustomizeParameters(IDetailLayoutBuilder& InDetailBuilder);`
- L26 _private prototype_ `EAvaTransitionEditorMode GetEditorMode() const;`
- L28 _private prototype_ `TSharedPtr<IDetailCustomization> GetDefaultCustomization() const;`
- L30 _private member_ `TWeakPtr<FAvaTransitionViewModelSharedData> SharedDataWeak;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheTransitionEditor/Private/Customizations/Widgets/SAvaTransitionTransitionType.h` (Private)


#### class `SAvaTransitionTransitionType`  
`class SAvaTransitionTransitionType : public SCompoundWidget`  
_L13-38_
- inherits: `SCompoundWidget`
- L16 _public function_ `SLATE_BEGIN_ARGS(SAvaTransitionTransitionType)`
- L17 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TSharedPtr<IPropertyHandleArray>& InTransitionsHandle);`
- L23 _protected prototype_ `virtual void Tick(const FGeometry& InAllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;`
- L27 _private prototype_ `void UpdateTransition();`
- L29 _private prototype_ `ECheckBoxState GetTransitionCheckState(EStateTreeTransitionType InTransitionType) const;`
- L31 _private prototype_ `void SetTransitionType(ECheckBoxState InCheckState, EStateTreeTransitionType InTransitionType);`
- L33 _private member_ `TSharedPtr<IPropertyHandleArray> TransitionArrayHandle;`
- L35 _private member_ `TSharedPtr<IPropertyHandle> TransitionHandle;`
- L37 _private member_ `TOptional<EStateTreeTransitionType> TransitionType;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheTransitionEditor/Private/Debugger/AvaTransitionDebugDefinitions.h` (Private)


#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_AVA_WITH_TRANSITION_DEBUG (WITH_STATETREE_DEBUG && WITH_STATETREE_TRACE_DEBUGGER)`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheTransitionEditor/Private/Debugger/AvaTransitionDebugInfo.h` (Private)


#### struct `FAvaTransitionDebugInfo`  
`struct FAvaTransitionDebugInfo`  
_L14-21_
- desc: Debug Information to identify a Tree Debug Instance
- L16 _public member_ `FStateTreeInstanceDebugId Id;`
- L18 _public member_ `FString Name;`
- L20 _public member_ `FLinearColor Color;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheTransitionEditor/Private/Debugger/AvaTransitionDebugger.h` (Private)


#### class `FAvaTransitionDebugger`  
`class FAvaTransitionDebugger : public TSharedFromThis<FAvaTransitionDebugger>`  
_L21-79_
- inherits: `TSharedFromThis<FAvaTransitionDebugger>`
- desc: Handles forwarding the debug events from state tree execution to the debuggables
- L24 _public prototype_ `FAvaTransitionDebugger();`
- L26 _public prototype_ `~FAvaTransitionDebugger();`
- L29 _public prototype_ `void Initialize(const TSharedRef<FAvaTransitionEditorViewModel>& InEditorViewModel);` — Called once to set the editor view model
- L32 _public prototype_ `void Start();` — Starts the debugger
- L35 _public prototype_ `void Stop();` — Stops the debugger
- L38 _public prototype_ `bool IsActive() const;` — Returns whether the debugger is currently active
- L41 _public prototype_ `void OnTreeInstanceStarted(const FStateTreeInstanceDebugId& InInstanceDebugId, const FString& InInstanceName);` — Called when an instance of the transition tree has started
- L44 _public prototype_ `void OnTreeInstanceStopped(const FStateTreeInstanceDebugId& InInstanceDebugId);` — Called when an instance of the transition tree has stopped
- L47 _public prototype_ `void OnNodeEntered(const FGuid& InNodeId, const FStateTreeInstanceDebugId& InInstanceDebugId);` — Called when a node with the given id was started / entered
- L50 _public prototype_ `void OnNodeExited(const FGuid& InNodeId, const FStateTreeInstanceDebugId& InInstanceDebugId);` — Called when a node with the given id was stopped / exited
- L53 _private prototype_ `void RegisterDelegates();`
- L54 _private prototype_ `void UnregisterDelegates();`
- L57 _private prototype_ `void OnBeginUpdatePhase(const FStateTreeExecutionContext& InExecutionContext, EStateTreeUpdatePhase InPhase, FStateTreeStateHandle InStateHandle);` — Called when an update phase has started
- L60 _private prototype_ `void OnStateEvent(const FStateTreeExecutionContext& InExecutionContext, FStateTreeStateHandle InStateHandle, EStateTreeTraceEventType InEventType);` — Called when a state event has triggered
- L63 _private prototype_ `TSharedPtr<IAvaTransitionDebuggableExtension> FindDebuggable(const FGuid& InNodeId) const;` — Finds the view model with the matching id and returns it as debuggable extension, or null if the view model doesn't exist or doesn't have a debuggable extension
- L66 _private member_ `TWeakPtr<FAvaTransitionEditorViewModel> EditorViewModelWeak;` — the view model owning this debugger
- L69 _private member_ `TArray<FAvaTransitionTreeDebugInstance> TreeDebugInstances;` — All the tree instances that are in execution and being debugged
- L72 _private member_ `FDelegateHandle OnBeginUpdatePhaseHandle;` — Handle to the delegate when an update phase has begun
- L75 _private member_ `FDelegateHandle OnStateEventHandle;` — Handle to the delegate when a state event has triggered
- L78 _private member_ `bool bActive = false;` — Determines whether the debugger is currently active

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheTransitionEditor/Private/Debugger/AvaTransitionStateDebugInstance.h` (Private)


#### enum `EAvaTransitionStateDebugStatus`  
`enum class EAvaTransitionStateDebugStatus : uint8`  
_L12-28_
- L15 _public enumerator_ `Entering` — Instance started to enter
- L18 _public enumerator_ `Entered` — Instance finished entering
- L21 _public enumerator_ `ExitingGrace` — Instance is in grace period before it can start exiting
- L24 _public enumerator_ `Exiting` — Instance started exiting
- L27 _public enumerator_ `Exited` — Instance ended exiting and can now be removed

#### class `FAvaTransitionStateDebugInstance`  
`class FAvaTransitionStateDebugInstance`  
_L31-73_
- desc: Represents a Debug Instance active in a State
- L34 _public prototype_ `explicit FAvaTransitionStateDebugInstance(const FAvaTransitionDebugInfo& InDebugInfo);`
- L36 _public prototype_ `~FAvaTransitionStateDebugInstance();`
- L38 _public prototype_ `void Enter();`
- L40 _public prototype_ `void Exit();`
- L42 _public prototype_ `void Tick(float InDeltaTime);`
- L45 _public prototype_ `float GetStatusProgress() const;` — Returns 0 if Exited, 1 if Entered, or anything in between if switching status
- L47 _public function_ `EAvaTransitionStateDebugStatus GetDebugStatus() const`
- L52 _public function_ `const FAvaTransitionDebugInfo& GetDebugInfo() const`
- L57 _public function_ `bool operator==(const FStateTreeInstanceDebugId& InDebugInstanceId) const`
- L63 _private prototype_ `void UpdateActivationState();`
- L65 _private prototype_ `void SetDebugState(EAvaTransitionStateDebugStatus InDebugState);`
- L67 _private member_ `FAvaTransitionDebugInfo DebugInfo;`
- L69 _private member_ `EAvaTransitionStateDebugStatus DebugStatus = EAvaTransitionStateDebugStatus::Exited;`
- L72 _private member_ `float StatusElapsedTime = 0.f;` — Elapsed Time in the current status

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheTransitionEditor/Private/Debugger/AvaTransitionTreeDebugInstance.h` (Private)


#### class `FAvaTransitionTreeDebugInstance`  
`class FAvaTransitionTreeDebugInstance`  
_L17-36_
- desc: Active State Tree Instance running in debug mode
- L20 _public prototype_ `explicit FAvaTransitionTreeDebugInstance(const FStateTreeInstanceDebugId& InId, const FString& InName);`
- L22 _public prototype_ `~FAvaTransitionTreeDebugInstance();`
- L24 _public prototype_ `bool operator==(const FStateTreeInstanceDebugId& InId) const;`
- L26 _public prototype_ `void EnterDebuggable(const TSharedPtr<IAvaTransitionDebuggableExtension>& InDebuggable);`
- L28 _public prototype_ `void ExitDebuggable(const TSharedPtr<IAvaTransitionDebuggableExtension>& InDebuggable);`
- L31 _private prototype_ `void Reset();`
- L33 _private member_ `TArray<TWeakPtr<IAvaTransitionDebuggableExtension>> Debuggables;`
- L35 _private member_ `FAvaTransitionDebugInfo DebugInfo;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheTransitionEditor/Private/DragDrop/AvaTransitionStateDragDropOp.h` (Private)


#### class `FAvaTransitionStateDragDropOp`  
`class FAvaTransitionStateDragDropOp : public FDecoratedDragDropOp`  
_L13-37_
- inherits: `FDecoratedDragDropOp`
- L16 _public prototype_ `DRAG_DROP_OPERATOR_TYPE(FAvaTransitionStateDragDropOp, FDecoratedDragDropOp) static TSharedRef<FAvaTransitionStateDragDropOp> New(const TSharedRef<FAvaTransitionStateViewModel>& InStateViewModel, bool bInDuplicateStates);`
- L20 _public function_ `TConstArrayView<TSharedRef<FAvaTransitionStateViewModel>> GetStateViewModels() const`
- L25 _public function_ `bool ShouldDuplicateStates() const`
- L31 _protected prototype_ `void Init(const TSharedRef<FAvaTransitionStateViewModel>& InStateViewModel, bool bInDuplicateStates);`
- L34 _private member_ `TArray<TSharedRef<FAvaTransitionStateViewModel>> StateViewModels;`
- L36 _private member_ `bool bDuplicateStates = false;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheTransitionEditor/Private/Extensions/IAvaTransitionDebuggableExtension.h` (Private)


#### class `IAvaTransitionDebuggableExtension`  
`class IAvaTransitionDebuggableExtension`  
_L13-23_
- desc: Extension for  View Model that can be debugged
- L16 _public prototype_ `UE_AVA_TYPE(IAvaTransitionDebuggableExtension) #if UE_AVA_WITH_TRANSITION_DEBUG virtual void DebugEnter(const FAvaTransitionDebugInfo& InDebugInfo) = 0;`
- L21 _public prototype_ `virtual void DebugExit(const FAvaTransitionDebugInfo& InDebugInfo) = 0;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheTransitionEditor/Private/Extensions/IAvaTransitionDragDropExtension.h` (Private)


#### class `IAvaTransitionDragDropExtension`  
`class IAvaTransitionDragDropExtension`  
_L15-25_
- desc: Extension for a View Model that can handle drag / drop operations
- L18 _public prototype_ `UE_AVA_TYPE(IAvaTransitionDragDropExtension) virtual TOptional<EItemDropZone> OnCanAcceptDrop(const FDragDropEvent& InDragDropEvent, EItemDropZone InDropZone) = 0;`
- L22 _public prototype_ `virtual FReply OnAcceptDrop(const FDragDropEvent& InDragDropEvent, EItemDropZone InDropZone) = 0;`
- L24 _public prototype_ `virtual FReply OnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) = 0;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheTransitionEditor/Private/Extensions/IAvaTransitionGuidExtension.h` (Private)


#### class `IAvaTransitionGuidExtension`  
`class IAvaTransitionGuidExtension`  
_L10-16_
- desc: Extension for a View Model that can be handles an underlying Guid
- L13 _public prototype_ `UE_AVA_TYPE(IAvaTransitionGuidExtension) virtual const FGuid& GetGuid() const = 0;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheTransitionEditor/Private/Extensions/IAvaTransitionObjectExtension.h` (Private)


#### class `IAvaTransitionObjectExtension`  
`class IAvaTransitionObjectExtension`  
_L11-19_
- desc: Extension for a View Model that represents a UObject
- L14 _public prototype_ `UE_AVA_TYPE(IAvaTransitionObjectExtension) virtual UObject* GetObject() const = 0;`
- L18 _public prototype_ `virtual void OnPropertiesChanged(const FPropertyChangedEvent& InPropertyChangedEvent) = 0;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheTransitionEditor/Private/Extensions/IAvaTransitionSelectableExtension.h` (Private)


#### class `IAvaTransitionSelectableExtension`  
`class IAvaTransitionSelectableExtension`  
_L8-16_
- desc: Extension for a View Model that supports being selected
- L11 _public prototype_ `UE_AVA_TYPE(IAvaTransitionSelectableExtension) virtual void SetSelected(bool bInIsSelected) = 0;`
- L15 _public prototype_ `virtual bool IsSelected() const = 0;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheTransitionEditor/Private/Extensions/IAvaTransitionTickableExtension.h` (Private)


#### class `IAvaTransitionTickableExtension`  
`class IAvaTransitionTickableExtension`  
_L8-14_
- desc: Extension for a View Model that supports ticking
- L11 _public prototype_ `UE_AVA_TYPE(IAvaTransitionTickableExtension) virtual void Tick(float InDeltaTime) = 0;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheTransitionEditor/Private/Extensions/IAvaTransitionTreeRowExtension.h` (Private)


#### class `IAvaTransitionTreeRowExtension`  
`class IAvaTransitionTreeRowExtension`  
_L13-30_
- desc: Extension for a View Model that supports being a Tree Row
- L16 _public function_ `UE_AVA_TYPE(IAvaTransitionTreeRowExtension) virtual bool CanGenerateRow() const`
- L23 _public prototype_ `virtual TSharedRef<ITableRow> GenerateRow(const TSharedRef<STableViewBase>& InOwningTableView) = 0;`
- L26 _public prototype_ `virtual bool IsExpanded() const = 0;` — Indication whether the View Model is Expanded
- L29 _public prototype_ `virtual void SetExpanded(bool bInIsExpanded) = 0;` — Sets the Expansion state of the View Model

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheTransitionEditor/Private/Extensions/IAvaTransitionWidgetExtension.h` (Private)


#### class `IAvaTransitionWidgetExtension`  
`class IAvaTransitionWidgetExtension`  
_L11-17_
- desc: Extension for a View Model that can supports creating its own widget
- L14 _public prototype_ `UE_AVA_TYPE(IAvaTransitionWidgetExtension) virtual TSharedRef<SWidget> CreateWidget() = 0;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheTransitionEditor/Private/Menu/AvaTransitionMenuContext.h` (Private)


#### class `UAvaTransitionMenuContext`  
`class UAvaTransitionMenuContext : public UObject`  
_L12-31_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject`
- L17 _public prototype_ `UAvaTransitionMenuContext() = default;`
- L19 _public function_ `TSharedPtr<FAvaTransitionEditorViewModel> GetEditorViewModel() const`
- L24 _public function_ `void SetEditorViewModel(const TSharedRef<FAvaTransitionEditorViewModel>& InEditorViewModel)`
- L30 _private member_ `TWeakPtr<FAvaTransitionEditorViewModel> EditorViewModelWeak;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheTransitionEditor/Private/Menu/AvaTransitionToolbar.h` (Private)


#### class `FAvaTransitionToolbar`  
`class FAvaTransitionToolbar : public TSharedFromThis<FAvaTransitionToolbar>`  
_L14-41_
- inherits: `TSharedFromThis<FAvaTransitionToolbar>`
- L17 _public prototype_ `explicit FAvaTransitionToolbar(FAvaTransitionEditorViewModel& InOwner);`
- L19 _public function_ `static FName GetTreeToolbarName()`
- L24 _public prototype_ `void SetReadOnlyProfileName(FName InToolMenuToolbarName, FName InReadOnlyProfileName);`
- L26 _public prototype_ `void ExtendEditorToolbar(UToolMenu* InToolbarMenu);`
- L28 _public prototype_ `void ExtendTreeToolbar(UToolMenu* InToolbarMenu);`
- L30 _public prototype_ `void SetupReadOnlyCustomization(FReadOnlyAssetEditorCustomization& InReadOnlyCustomization);`
- L32 _public prototype_ `TSharedRef<SWidget> GenerateTreeToolbarWidget();`
- L35 _private prototype_ `void ApplyReadOnlyPermissionList(const FNamePermissionList& InPermissionList);`
- L37 _private member_ `FAvaTransitionEditorViewModel& Owner;`
- L39 _private member_ `FName ToolMenuToolbarName;`
- L40 _private member_ `FName ReadOnlyProfileName;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheTransitionEditor/Private/Menu/AvaTransitionTreeContextMenu.h` (Private)


#### class `FAvaTransitionTreeContextMenu`  
`class FAvaTransitionTreeContextMenu : public TSharedFromThis<FAvaTransitionTreeContextMenu>`  
_L12-31_
- inherits: `TSharedFromThis<FAvaTransitionTreeContextMenu>`
- L15 _public function_ `explicit FAvaTransitionTreeContextMenu(FAvaTransitionEditorViewModel& InOwner) : Owner(InOwner)`
- L20 _public function_ `static FName GetTreeContextMenuName()`
- L25 _public prototype_ `TSharedRef<SWidget> GenerateTreeContextMenuWidget();`
- L28 _private prototype_ `void ExtendTreeContextMenu(UToolMenu* InContextMenu);`
- L30 _private member_ `FAvaTransitionEditorViewModel& Owner;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheTransitionEditor/Private/Menu/Widgets/AvaTransitionTreeStatus.h` (Private)


#### class `SAvaTransitionTreeStatus`  
`class SAvaTransitionTreeStatus : public SCompoundWidget`  
_L10-39_
- inherits: `SCompoundWidget`
- L20 _public function_ `SLATE_BEGIN_ARGS(SAvaTransitionTreeStatus)`
- L21 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, IAvaTransitionBehavior* InTransitionBehavior);`
- L26 _private prototype_ `bool IsStatusButtonEnabled() const;`
- L28 _private prototype_ `FReply OnStatusButtonClicked();`
- L30 _private prototype_ `EStatus GetStatus() const;`
- L32 _private prototype_ `FText GetStatusText(EStatus InStatus) const;`
- L34 _private prototype_ `FText GetStatusTooltipText() const;`
- L36 _private prototype_ `const FSlateBrush* GetStatusIcon() const;`
- L38 _private member_ `TWeakInterfacePtr<IAvaTransitionBehavior> TransitionBehaviorWeak;`

#### enum `SAvaTransitionTreeStatus::EStatus`  
`enum class EStatus : uint8`  
_L12-17_
- L14 _public enumerator_ `Invalid`
- L15 _public enumerator_ `Disabled`
- L16 _public enumerator_ `Enabled`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheTransitionEditor/Private/Menu/Widgets/SAvaTransitionTreeInstancingModeSelector.h` (Private)


#### class `SAvaTransitionTreeInstancingModeSelector`  
`class SAvaTransitionTreeInstancingModeSelector : public SCompoundWidget`  
_L11-31_
- inherits: `SCompoundWidget`
- L14 _public function_ `SLATE_BEGIN_ARGS(SAvaTransitionTreeInstancingModeSelector)`
- L15 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, IAvaTransitionBehavior* InTransitionBehavior);`
- L20 _protected prototype_ `TSharedRef<SWidget> GenerateWidget(FName InItem) const;`
- L21 _protected prototype_ `void HandleSelectionChanged(FName InProposedSelection, ESelectInfo::Type InSelectInfo);`
- L22 _protected prototype_ `FText GetDisplayTextFromProperty() const;`
- L23 _protected prototype_ `FName GetItemFromProperty() const;`
- L24 _protected prototype_ `FText GetDisplayTextFromItem(FName InItem) const;`
- L25 _protected prototype_ `void UpdateItems();`
- L28 _protected member_ `TWeakInterfacePtr<IAvaTransitionBehavior> TransitionBehaviorWeak;`
- L29 _protected member_ `TSharedPtr<SComboBox<FName>> Combo;`
- L30 _protected member_ `TArray<FName> Items;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheTransitionEditor/Private/Serialization/AvaTransitionStateExportData.h` (Private)


#### class `UAvaTransitionStateExportData`  
`class UAvaTransitionStateExportData : public UObject`  
_L11-18_
- reflection: `UCLASS(Hidden)`
- inherits: `UObject`
- L17 _public member_ `TArray<FStateTreePropertyPathBinding> Bindings;` — `UPROPERTY()`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheTransitionEditor/Private/Serialization/AvaTransitionStateSerializer.h` (Private)


#### class `FAvaTransitionStateSerializer`  
`class FAvaTransitionStateSerializer`  
_L12-18_
- L15 _public prototype_ `static FString ExportText(UAvaTransitionTreeEditorData& InEditorData, TConstArrayView<UStateTreeState*> InStates);`
- L17 _public prototype_ `static bool ImportText(const FString& InText, UAvaTransitionTreeEditorData& InEditorData, UStateTreeState* InState, TArray<UStateTreeState*>& OutNewStates, UObject*& OutParent);`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheTransitionEditor/Private/Styling/AvaTransitionEditorStyle.h` (Private)


#### class `FAvaTransitionEditorStyle`  
`class FAvaTransitionEditorStyle final : public FSlateStyleSet`  
_L9-27_
- inherits: `FSlateStyleSet`
- L12 _public function_ `static FAvaTransitionEditorStyle& Get()`
- L18 _public prototype_ `FAvaTransitionEditorStyle();`
- L21 _public prototype_ `static FLinearColor LerpColorSRGB(const FLinearColor& InA, const FLinearColor& InB, float InAlpha);`
- L23 _public prototype_ `static FSlateIcon ParseIcon(FName InIconName);`
- L26 _private prototype_ `void SetupFonts();`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheTransitionEditor/Private/Styling/AvaTransitionTextStyling.h` (Private)


#### class `FAvaTransitionTextStyleDecorator`  
`class FAvaTransitionTextStyleDecorator : public ITextDecorator`  
_L14-30_
- inherits: `ITextDecorator`
- desc: Simple decorator for SRichTextBlock, which allows to map simple/shorthand tags to specific style names. The decorator also strips away any tags, e.g. in case the initial text came with nested tags. Sourced from FTextStyleDecorator
- L17 _public prototype_ `static TSharedRef<FAvaTransitionTextStyleDecorator> Create(FString InName, const FTextBlockStyle& InTextStyle);`
- L20 _public prototype_ `virtual bool Supports(const FTextRunParseResults& InRunInfo, const FString& InText) const override;`
- L21 _public prototype_ `virtual TSharedRef<ISlateRun> Create(const TSharedRef<FTextLayout>& InTextLayout,const FTextRunParseResults& InRunParseResult,const FString& InOriginalText,const TSharedRef<FString>& InModelText,const ISlateStyle* InStyle) override;`
- L26 _private member_ `FString DecoratorName;` — Name of this decorator
- L29 _private member_ `FTextBlockStyle TextStyle;` — Color of this decorator

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheTransitionEditor/Private/Styling/AvaTransitionWidgetStyling.h` (Private)


#### struct `FAvaTransitionWidgetStyling`  
`struct FAvaTransitionWidgetStyling`  
_L10-13_
- L12 _public prototype_ `static FSlateWidgetRun::FWidgetRunInfo CreateOperandWidget(const FTextRunInfo& InRunInfo, const ISlateStyle* InStyle);`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheTransitionEditor/Private/TabFactories/AvaTransitionCompilerResultsTabFactory.h` (Private)


#### class `FAvaTransitionCompilerResultsTabFactory`  
`class FAvaTransitionCompilerResultsTabFactory : public FAvaTransitionTabFactory`  
_L7-17_
- inherits: `FAvaTransitionTabFactory`
- L10 _public member_ `static const FName TabId;`
- L12 _public prototype_ `explicit FAvaTransitionCompilerResultsTabFactory(const TSharedRef<FAvaTransitionEditor>& InEditor);`
- L15 _public prototype_ `virtual TSharedRef<SWidget> CreateTabBody(const FWorkflowTabSpawnInfo& InInfo) const override;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheTransitionEditor/Private/TabFactories/AvaTransitionParameterTabFactory.h` (Private)


#### class `FAvaTransitionParameterTabFactory`  
`class FAvaTransitionParameterTabFactory : public FAvaTransitionTabFactory`  
_L7-17_
- inherits: `FAvaTransitionTabFactory`
- L10 _public member_ `static const FName TabId;`
- L12 _public prototype_ `explicit FAvaTransitionParameterTabFactory(const TSharedRef<FAvaTransitionEditor>& InEditor);`
- L15 _public prototype_ `virtual TSharedRef<SWidget> CreateTabBody(const FWorkflowTabSpawnInfo& InInfo) const override;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheTransitionEditor/Private/TabFactories/AvaTransitionSelectionDetailsTabFactory.h` (Private)


#### class `FAvaTransitionSelectionDetailsTabFactory`  
`class FAvaTransitionSelectionDetailsTabFactory : public FAvaTransitionTabFactory`  
_L9-22_
- inherits: `FAvaTransitionTabFactory`
- L12 _public member_ `static const FName TabId;`
- L14 _public prototype_ `explicit FAvaTransitionSelectionDetailsTabFactory(const TSharedRef<FAvaTransitionEditor>& InEditor, EAvaTransitionEditorMode InEditorMode);`
- L17 _public prototype_ `virtual TSharedRef<SWidget> CreateTabBody(const FWorkflowTabSpawnInfo& InInfo) const override;`
- L21 _private member_ `EAvaTransitionEditorMode EditorMode;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheTransitionEditor/Private/TabFactories/AvaTransitionTabFactory.h` (Private)


#### class `FAvaTransitionTabFactory`  
`class FAvaTransitionTabFactory : public FWorkflowTabFactory`  
_L9-28_
- inherits: `FWorkflowTabFactory`
- desc: Base class for all Tab Factories in Motion Design Transition Editor
- L12 _public function_ `explicit FAvaTransitionTabFactory(FName InTabId, const TSharedRef<FAvaTransitionEditor>& InEditor) : FWorkflowTabFactory(InTabId, InEditor)`
- L17 _public function_ `TSharedPtr<FAvaTransitionEditor> GetEditor() const`
- L24 _protected prototype_ `virtual FTabSpawnerEntry& RegisterTabSpawner(TSharedRef<FTabManager> InTabManager, const FApplicationMode* InCurrentApplicationMode) const override;`
- L27 _protected member_ `ETabReadOnlyBehavior ReadOnlyBehavior = ETabReadOnlyBehavior::Disabled;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheTransitionEditor/Private/TabFactories/AvaTransitionTreeDetailsTabFactory.h` (Private)


#### class `FAvaTransitionTreeDetailsTabFactory`  
`class FAvaTransitionTreeDetailsTabFactory : public FAvaTransitionTabFactory`  
_L7-17_
- inherits: `FAvaTransitionTabFactory`
- L10 _public member_ `static const FName TabId;`
- L12 _public prototype_ `explicit FAvaTransitionTreeDetailsTabFactory(const TSharedRef<FAvaTransitionEditor>& InEditor);`
- L15 _public prototype_ `virtual TSharedRef<SWidget> CreateTabBody(const FWorkflowTabSpawnInfo& InInfo) const override;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheTransitionEditor/Private/TabFactories/AvaTransitionTreeTabFactory.h` (Private)


#### class `FAvaTransitionTreeTabFactory`  
`class FAvaTransitionTreeTabFactory : public FAvaTransitionTabFactory`  
_L7-17_
- inherits: `FAvaTransitionTabFactory`
- L10 _public member_ `static const FName TabId;`
- L12 _public prototype_ `explicit FAvaTransitionTreeTabFactory(const TSharedRef<FAvaTransitionEditor>& InEditor);`
- L15 _public prototype_ `virtual TSharedRef<SWidget> CreateTabBody(const FWorkflowTabSpawnInfo& Info) const override;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheTransitionEditor/Private/ViewModels/AvaTransitionCastedViewModel.h` (Private)


#### struct `TAvaTransitionCastedViewModel`  
`template<typename T UE_REQUIRES(TIsValidAvaType<T>::Value)> struct TAvaTransitionCastedViewModel`  
_L10-14_
- desc: Casted View Model that has both the Base View Model & the Casted Instance
- L12 _public member_ `TSharedRef<class FAvaTransitionViewModel> Base;`
- L13 _public member_ `TSharedRef<T> Casted;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheTransitionEditor/Private/ViewModels/AvaTransitionContainerViewModel.h` (Private)


#### class `FAvaTransitionContainerViewModel`  
`class FAvaTransitionContainerViewModel : public FAvaTransitionViewModel`  
_L12-29_
- inherits: `FAvaTransitionViewModel`
- desc: View Model serving as a container for a particular group of elements in a State
- L15 _public prototype_ `UE_AVA_INHERITS(FAvaTransitionContainerViewModel, FAvaTransitionViewModel) explicit FAvaTransitionContainerViewModel(UStateTreeState* InState);`
- L19 _public prototype_ `UStateTreeState* GetState() const;`
- L21 _public prototype_ `UAvaTransitionTreeEditorData* GetEditorData() const;`
- L24 _public prototype_ `virtual bool IsValid() const override;`
- L28 _private member_ `TWeakObjectPtr<UStateTreeState> StateWeak;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheTransitionEditor/Private/ViewModels/AvaTransitionEditorViewModel.h` (Private)


#### class `FAvaTransitionEditorViewModel`  
`class FAvaTransitionEditorViewModel : public FAvaTransitionViewModel, public FSelfRegisteringEditorUndoClient, public IAvaTransitionObjectExtension`  
_L28-132_
- inherits: `FAvaTransitionViewModel,FSelfRegisteringEditorUndoClient,IAvaTransitionObjectExtension`
- desc: View Model for the Tree Editor Data
- L31 _public prototype_ `UE_AVA_INHERITS(FAvaTransitionEditorViewModel, FAvaTransitionViewModel, IAvaTransitionObjectExtension) DECLARE_MULTICAST_DELEGATE(FOnPostRefresh);`
- L34 _public function_ `FOnPostRefresh::RegistrationType& GetOnPostRefresh() const`
- L39 _public prototype_ `explicit FAvaTransitionEditorViewModel(UAvaTransitionTree* InTransitionTree, const TSharedPtr<FAvaTransitionEditor>& InEditor);`
- L43 _public prototype_ `void BindCommands(const TSharedRef<FUICommandList>& InCommandList);`
- L45 _public function_ `TSharedRef<FUICommandList> GetCommandList() const`
- L50 _public prototype_ `const FAvaTransitionCompiler& GetCompiler() const;`
- L52 _public prototype_ `bool CanCompile() const;`
- L54 _public prototype_ `void Compile();`
- L56 _public prototype_ `UAvaTransitionTree* GetTransitionTree() const;`
- L58 _public prototype_ `UAvaTransitionTreeEditorData* GetEditorData() const;`
- L60 _public prototype_ `bool UpdateEditorData(bool bInCreateIfNotFound = false);`
- L62 _public prototype_ `void UpdateTree();`
- L64 _public prototype_ `void RefreshTreeView();`
- L66 _public prototype_ `TSharedPtr<FAvaTransitionEditor> GetEditor() const;`
- L68 _public prototype_ `TSharedRef<FAvaTransitionSelection> GetSelection() const;`
- L70 _public function_ `TSharedRef<FAvaTransitionToolbar> GetToolbar() const`
- L75 _public function_ `TSharedRef<FAvaTransitionTreeContextMenu> GetContextMenu() const`
- L80 _public prototype_ `TSharedRef<SWidget> GetTreeWidget();`
- L83 _public prototype_ `virtual void OnInitialize() override;`
- L84 _public prototype_ `virtual void PostRefresh() override;`
- L85 _public prototype_ `virtual void GatherChildren(FAvaTransitionViewModelChildren& OutChildren) override;`
- L89 _public prototype_ `virtual void PostRedo(bool bInSuccess) override;`
- L90 _public prototype_ `virtual void PostUndo(bool bInSuccess) override;`
- L94 _public prototype_ `virtual UObject* GetObject() const override;`
- L95 _public function_ `virtual void OnPropertiesChanged(const FPropertyChangedEvent& InPropertyChangedEvent) override`
- L99 _private prototype_ `void BindDelegates();`
- L101 _private prototype_ `void UnbindDelegates();`
- L103 _private prototype_ `void OnPostCompile(const UStateTree& InStateTree);`
- L105 _private prototype_ `void OnIdentifierChanged(const UStateTree& InStateTree);`
- L107 _private prototype_ `void OnSchemaChanged(const UStateTree& InStateTree);`
- L109 _private prototype_ `void OnCompileFailed();`
- L111 _private prototype_ `void OnMessageTokenClicked(const TSharedRef<IMessageToken>& InMessageToken);`
- L113 _private member_ `TSharedRef<FAvaTransitionToolbar> Toolbar;`
- L115 _private member_ `TSharedRef<FAvaTransitionTreeContextMenu> ContextMenu;`
- L117 _private member_ `TWeakObjectPtr<UAvaTransitionTree> TransitionTreeWeak;`
- L119 _private member_ `TWeakObjectPtr<UAvaTransitionTreeEditorData> EditorDataWeak;`
- L121 _private member_ `TWeakPtr<FAvaTransitionEditor> EditorWeak;`
- L123 _private member_ `FAvaTransitionCompiler Compiler;`
- L125 _private member_ `TSharedRef<FUICommandList> CommandList;`
- L127 _private member_ `TSharedPtr<SAvaTransitionTreeView> TreeView;`
- L129 _private member_ `TArray<TSharedRef<FAvaTransitionActions>> Actions;`
- L131 _private member_ `mutable FOnPostRefresh OnPostRefreshDelegate;`

#### Free symbols / members of external scopes

- L33 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnPostRefresh);`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheTransitionEditor/Private/ViewModels/AvaTransitionNodeViewModel.h` (Private)


#### class `FAvaTransitionNodeViewModel`  
`class FAvaTransitionNodeViewModel : public FAvaTransitionViewModel, public IAvaTransitionGuidExtension`  
_L17-62_
- inherits: `FAvaTransitionViewModel,IAvaTransitionGuidExtension`
- desc: View Model for an Editor Node (base of Task or Condition)
- L20 _public prototype_ `UE_AVA_INHERITS(FAvaTransitionNodeViewModel, FAvaTransitionViewModel, IAvaTransitionGuidExtension) explicit FAvaTransitionNodeViewModel(const FStateTreeEditorNode& InEditorNode);`
- L24 _public prototype_ `UStateTreeState* GetState() const;`
- L26 _public prototype_ `FSlateColor GetStateColor() const;`
- L28 _public prototype_ `UAvaTransitionTreeEditorData* GetEditorData() const;`
- L30 _public prototype_ `FStateTreeEditorNode* GetEditorNode() const;`
- L32 _public prototype_ `const FInstancedStruct* GetNode() const;`
- L35 _public function_ `template<typename T = FStateTreeNodeBase UE_REQUIRES(TIsDerivedFrom<T, FStateTreeNodeBase>::Value)> const T* GetTypedNode() const`
- L45 _public prototype_ `virtual TArrayView<FStateTreeEditorNode> GetNodes(UStateTreeState& InState) const = 0;` — Get the Nodes for a given State
- L47 _public function_ `const FGuid& GetNodeId() const`
- L53 _public prototype_ `virtual bool IsValid() const override;`
- L57 _public prototype_ `virtual const FGuid& GetGuid() const override;`
- L61 _private member_ `FGuid NodeId;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheTransitionEditor/Private/ViewModels/AvaTransitionViewModel.h` (Private)


#### class `FAvaTransitionViewModel`  
`class FAvaTransitionViewModel : public IAvaTypeCastable, public TSharedFromThis<FAvaTransitionViewModel>`  
_L13-66_
- inherits: `IAvaTypeCastable,TSharedFromThis<FAvaTransitionViewModel>`
- L16 _public prototype_ `UE_AVA_INHERITS(FAvaTransitionViewModel, IAvaTypeCastable) FAvaTransitionViewModel();`
- L20 _public prototype_ `void Initialize(const TSharedPtr<FAvaTransitionViewModel>& InParent);`
- L22 _public function_ `virtual void OnInitialize()`
- L27 _public function_ `virtual bool IsValid() const` — Returns true if the View Model is in a valid state
- L33 _public prototype_ `void Refresh();` — Resets and gathers all the children for this View Model and all its descendants iteratively
- L36 _public function_ `virtual void PostRefresh()` — Called after all the Children have been gathered recursively
- L40 _public function_ `TSharedRef<FAvaTransitionViewModelSharedData> GetSharedData() const`
- L45 _public function_ `TSharedPtr<FAvaTransitionViewModel> GetParent() const`
- L50 _public function_ `TConstArrayView<TSharedRef<FAvaTransitionViewModel>> GetChildren() const`
- L56 _public function_ `virtual void GatherChildren(FAvaTransitionViewModelChildren& OutChildren)` — Gathers only the top-level children for the View Model
- L61 _private member_ `TSharedPtr<FAvaTransitionViewModelSharedData> SharedData;`
- L63 _private member_ `FAvaTransitionViewModelChildren Children;`
- L65 _private member_ `TWeakPtr<FAvaTransitionViewModel> ParentWeak;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheTransitionEditor/Private/ViewModels/AvaTransitionViewModelChildren.h` (Private)


#### class `FAvaTransitionViewModelChildren`  
`class FAvaTransitionViewModelChildren`  
_L16-47_
- desc: Container class for Child View Models Automatically handles setting the Parent when a Child View Model is allocated and disallows items from being added if they're in an invalid state
- L19 _public prototype_ `explicit FAvaTransitionViewModelChildren(FAvaTransitionViewModel& InParent);`
- L21 _public function_ `TConstArrayView<TSharedRef<FAvaTransitionViewModel>> GetViewModels() const`
- L26 _public prototype_ `void Reserve(int32 InExpectedCount);`
- L28 _public prototype_ `void Reset();`
- L31 _public function_ `template<typename T, typename... InArgTypes UE_REQUIRES(TIsValidAvaType<T>::Value)> TSharedPtr<T> Add(InArgTypes&&... InArgs)`
- L42 _private prototype_ `bool AddImpl(const TSharedRef<FAvaTransitionViewModel>& InViewModel);`
- L44 _private member_ `FAvaTransitionViewModel& Parent;`
- L46 _private member_ `TArray<TSharedRef<FAvaTransitionViewModel>> ViewModels;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheTransitionEditor/Private/ViewModels/AvaTransitionViewModelSharedData.h` (Private)


#### class `FAvaTransitionViewModelSharedData`  
`class FAvaTransitionViewModelSharedData : public TSharedFromThis<FAvaTransitionViewModelSharedData>`  
_L22-87_
- inherits: `TSharedFromThis<FAvaTransitionViewModelSharedData>`
- desc: Shared Data is designed to house data accessible by any View Model in a hierarchy. A Shared Data instance is created at the topmost view model in a hierarchy (i.e. the view model with no parent), and shared across the rest of the view models
- L25 _public prototype_ `FAvaTransitionViewModelSharedData();`
- L27 _public prototype_ `void Initialize(const TSharedRef<FAvaTransitionEditorViewModel>& InEditorViewModel);`
- L29 _public prototype_ `void Refresh();`
- L31 _public function_ `TSharedPtr<FAvaTransitionEditorViewModel> GetEditorViewModel() const`
- L36 _public function_ `TSharedRef<FAvaTransitionViewModelRegistryCollection> GetRegistryCollection() const`
- L41 _public function_ `TSharedRef<FAvaTransitionSelection> GetSelection() const`
- L47 _public function_ `TSharedRef<FAvaTransitionDebugger> GetDebugger() const`
- L53 _public function_ `EAvaTransitionEditorMode GetEditorMode() const`
- L58 _public function_ `void SetEditorMode(EAvaTransitionEditorMode InEditorMode)`
- L63 _public function_ `bool IsReadOnly() const`
- L68 _public function_ `void SetReadOnly(bool bInReadOnly)`
- L74 _private member_ `TSharedRef<FAvaTransitionViewModelRegistryCollection> RegistryCollection;`
- L76 _private member_ `TSharedRef<FAvaTransitionSelection> Selection;`
- L79 _private member_ `TSharedRef<FAvaTransitionDebugger> Debugger;`
- L82 _private member_ `TWeakPtr<FAvaTransitionEditorViewModel> EditorViewModelWeak;`
- L84 _private member_ `EAvaTransitionEditorMode EditorMode = EAvaTransitionEditorMode::Default;`
- L86 _private member_ `bool bReadOnly = false;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheTransitionEditor/Private/ViewModels/AvaTransitionViewModelUtils.h` (Private)


#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace AvaTransitionEditor` (scope `UE`)
- L15 _prototype_ `bool IsDescendantOf(const TSharedRef<FAvaTransitionViewModel>& InViewModel, const TSharedRef<FAvaTransitionViewModel>& InParentViewModel);` (scope `UE::AvaTransitionEditor`)
- L24 _prototype_ `EAvaTransitionIterationResult ForEachViewModel(TConstArrayView<TSharedRef<FAvaTransitionViewModel>> InViewModels, TFunctionRef<void(const TSharedRef<FAvaTransitionViewModel>&, EAvaTransitionIterationResult&)> InCallable, bool bInRecursive = false);` (scope `UE::AvaTransitionEditor`) — Iterates each view model with option to recurse through all descendants and/or break iteration @param InViewModels the view models to iterate @param InCallable the function to call for every view model @param bInRecursive true to recurse all the descendants of each view model @return the result of the for each flow (e.g. to query whether it was stopped)
- L34 _function_ `template<typename T UE_REQUIRES(TIsValidAvaType<T>::Value)> EAvaTransitionIterationResult ForEachViewModelOfType(TConstArrayView<TSharedRef<FAvaTransitionViewModel>> InViewModels, TFunctionRef<void(const TAvaTransitionCastedViewModel<T>&, EAvaTransitionIterationResult&)> InCallable, bool bInRecursive)` (scope `UE::AvaTransitionEditor`) — Iterates each view model of a given type with option to recurse through all descendants and/or break iteration @param InViewModels the view models to iterate @param InCallable the function to call for every view model with matching type @param bInRecursive true to recurse all the descendants of each view model @return the result of the for each flow (e.g. to query whether it was stopped)
- L68 _prototype_ `EAvaTransitionIterationResult ForEachChild(const FAvaTransitionViewModel& InViewModel, TFunctionRef<void(const TSharedRef<FAvaTransitionViewModel>&, EAvaTransitionIterationResult&)> InCallable, bool bInRecursive = false);` (scope `UE::AvaTransitionEditor`) — Iterates each child with options to recurse through all descendants and/or break iteration @param InViewModel the view model whose children will be iterated @param InCallable the function to call for every child @param bInRecursive true to recurse all the descendants, false to only iterate through the immediate children @return the result of the for each flow (e.g. to query whether it was stopped)
- L78 _function_ `template<typename T UE_REQUIRES(TIsValidAvaType<T>::Value)> EAvaTransitionIterationResult ForEachChildOfType(const FAvaTransitionViewModel& InViewModel, TFunctionRef<void(const TAvaTransitionCastedViewModel<T>&, EAvaTransitionIterationResult&)> InCallable, bool bInRecursive = false)` (scope `UE::AvaTransitionEditor`) — Iterates each child type with option to recurse through all descendants and/or break iteration @param InViewModel the view model whose children will be iterated @param InCallable the function to call for every child with matching type @param bInRecursive true to recurse all the descendants, false to only iterate through the immediate children @return the result of the for each flow (e.g. to query whether it was stopped)
- L90 _function_ `template<typename T UE_REQUIRES(TIsValidAvaType<T>::Value)> TArray<TSharedRef<T>> GetViewModelsOfType(TConstArrayView<TSharedRef<FAvaTransitionViewModel>> InViewModels, bool bInRecursive = false)` (scope `UE::AvaTransitionEditor`) — Gets all the view models matching a given type @param InViewModels the view models to iterate @param bInRecursive true to recurse all the descendants of each view model @return the view models casted to the given type
- L97 _function_ `` (scope `UE::AvaTransitionEditor::GetViewModelsOfType`)
- L112 _function_ `template<typename T UE_REQUIRES(TIsValidAvaType<T>::Value)> TArray<TSharedRef<T>> GetChildrenOfType(const FAvaTransitionViewModel& InViewModel, bool bInRecursive = false)` (scope `UE::AvaTransitionEditor`) — Gets all the child view models matching a given type @param InViewModel the view models whose children will be iterated @param bInRecursive true to recurse all the descendants of each view model @return the view models casted to the given type
- L124 _function_ `template<typename T UE_REQUIRES(TIsValidAvaType<T>::Value)> TSharedPtr<T> FindAncestorOfType(const FAvaTransitionViewModel& InViewModel, bool bIncludeSelf = false)` (scope `UE::AvaTransitionEditor`) — Finds the first ancestor matching the given type @param InViewModel the view model in question @param bIncludeSelf whether to also include the passed in view model if it's of the requested type @return the view model ancestor that matched the type (or null if not found)
- L144 _prototype_ `void RemoveNestedViewModels(TArray<TSharedRef<FAvaTransitionViewModel>>& InViewModels);` (scope `UE::AvaTransitionEditor`) — Removes any view model whose ancestor is in the provided array

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheTransitionEditor/Private/ViewModels/Condition/AvaTransitionConditionContainerViewModel.h` (Private)


#### class `FAvaTransitionConditionContainerViewModel`  
`class FAvaTransitionConditionContainerViewModel : public FAvaTransitionContainerViewModel, public IAvaTransitionWidgetExtension`  
_L12-32_
- inherits: `FAvaTransitionContainerViewModel,IAvaTransitionWidgetExtension`
- desc: View Model serving as a container of all the Enter Conditions in a State
- L15 _public prototype_ `UE_AVA_INHERITS(FAvaTransitionConditionContainerViewModel, FAvaTransitionContainerViewModel, IAvaTransitionWidgetExtension) explicit FAvaTransitionConditionContainerViewModel(UStateTreeState* InState);`
- L19 _public prototype_ `void OnConditionsChanged();`
- L21 _public prototype_ `EVisibility GetVisibility() const;`
- L23 _public prototype_ `FText UpdateStateDescription() const;`
- L26 _public prototype_ `virtual void GatherChildren(FAvaTransitionViewModelChildren& OutChildren) override;`
- L30 _public prototype_ `virtual TSharedRef<SWidget> CreateWidget() override;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheTransitionEditor/Private/ViewModels/Condition/AvaTransitionConditionViewModel.h` (Private)


#### class `FAvaTransitionConditionViewModel`  
`class FAvaTransitionConditionViewModel : public FAvaTransitionNodeViewModel`  
_L12-22_
- inherits: `FAvaTransitionNodeViewModel`
- desc: View Model for an Enter Condition Node
- L15 _public prototype_ `UE_AVA_INHERITS(FAvaTransitionConditionViewModel, FAvaTransitionNodeViewModel) explicit FAvaTransitionConditionViewModel(const FStateTreeEditorNode& InEditorNode);`
- L20 _public prototype_ `virtual TArrayView<FStateTreeEditorNode> GetNodes(UStateTreeState& InState) const override;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheTransitionEditor/Private/ViewModels/Registry/AvaTransitionGuidViewModelRegistry.h` (Private)


#### struct `TAvaTransitionViewModelRegistryKey`  
`template<> struct TAvaTransitionViewModelRegistryKey<FGuid>`  
_L9-16_
- L11 _public member_ `static constexpr int32 Id = 2;`
- L13 _public prototype_ `static bool IsValid(const FGuid& InKey);`
- L15 _public prototype_ `static bool TryGetKey(const TSharedRef<FAvaTransitionViewModel>& InViewModel, FGuid& OutKey);`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheTransitionEditor/Private/ViewModels/Registry/AvaTransitionKeyableViewModelRegistry.h` (Private)


#### struct `TAvaTransitionKeyableViewModelRegistry`  
`template<typename InKeyType> struct TAvaTransitionKeyableViewModelRegistry : IAvaTransitionViewModelRegistry`  
_L12-25_
- inherits: `IAvaTransitionViewModelRegistry`
- desc: Registry Template for registries that allow finding a view model via a key
- L14 _public typedef_ `using FRegistryKey = TAvaTransitionViewModelRegistryKey<InKeyType>;`
- L16 _public prototype_ `TSharedPtr<FAvaTransitionViewModel> FindViewModel(const InKeyType& InKey) const;`
- L19 _public prototype_ `virtual void RegisterViewModel(const TSharedRef<FAvaTransitionViewModel>& InViewModel) override final;`
- L20 _public prototype_ `virtual void Refresh() override final;`
- L24 _private member_ `TMap<InKeyType, TWeakPtr<FAvaTransitionViewModel>> ViewModels;`
- L28 _function_ `template<typename InKeyType> TSharedPtr<FAvaTransitionViewModel> TAvaTransitionKeyableViewModelRegistry<InKeyType>::FindViewModel(const InKeyType& InKey) const`
- L42 _function_ `template<typename InKeyType> void TAvaTransitionKeyableViewModelRegistry<InKeyType>::RegisterViewModel(const TSharedRef<FAvaTransitionViewModel>& InViewModel)`
- L52 _function_ `template<typename InKeyType> void TAvaTransitionKeyableViewModelRegistry<InKeyType>::Refresh()`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheTransitionEditor/Private/ViewModels/Registry/AvaTransitionObjectViewModelRegistry.h` (Private)


#### struct `TAvaTransitionViewModelRegistryKey`  
`template<> struct TAvaTransitionViewModelRegistryKey<FObjectKey>`  
_L9-16_
- L11 _public member_ `static constexpr int32 Id = 1;`
- L13 _public prototype_ `static bool IsValid(const FObjectKey& InKey);`
- L15 _public prototype_ `static bool TryGetKey(const TSharedRef<FAvaTransitionViewModel>& InViewModel, FObjectKey& OutKey);`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheTransitionEditor/Private/ViewModels/Registry/AvaTransitionTickableViewModelRegistry.h` (Private)


#### struct `FAvaTransitionTickableViewModelRegistry`  
`struct FAvaTransitionTickableViewModelRegistry : IAvaTransitionViewModelRegistry, FTickableEditorObject`  
_L13-27_
- inherits: `IAvaTransitionViewModelRegistry,FTickableEditorObject`
- desc: Registry containing all View Models that are tickable
- L16 _public prototype_ `virtual void RegisterViewModel(const TSharedRef<FAvaTransitionViewModel>& InViewModel) override;`
- L17 _public prototype_ `virtual void Refresh() override;`
- L21 _public prototype_ `virtual TStatId GetStatId() const override;`
- L22 _public prototype_ `virtual void Tick(float InDeltaTime) override;`
- L26 _private member_ `TArray<TWeakPtr<IAvaTransitionTickableExtension>> TickablesWeak;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheTransitionEditor/Private/ViewModels/Registry/AvaTransitionViewModelRegistryCollection.h` (Private)


#### class `FAvaTransitionViewModelRegistryCollection`  
`class FAvaTransitionViewModelRegistryCollection`  
_L15-45_
- L18 _public prototype_ `FAvaTransitionViewModelRegistryCollection();`
- L20 _public prototype_ `void RegisterViewModel(const TSharedRef<FAvaTransitionViewModel>& InViewModel);`
- L23 _public function_ `template<typename InKeyType UE_REQUIRES(TAvaTransitionViewModelRegistryKey<InKeyType>::Id != -1)> TSharedPtr<FAvaTransitionViewModel> FindViewModel(const InKeyType& InKey) const`
- L29 _public function_ `TSharedPtr<FAvaTransitionViewModel> FindViewModel(const UObject* InObject) const`
- L34 _public prototype_ `void Refresh();`
- L41 _private member_ `const TMap<int32, TSharedRef<IAvaTransitionViewModelRegistry>> KeyableRegistries;` — Registries holding Keyable View Models (i.e. view models that can be found via a key) @see FAvaTransitionViewModelRegistryCollection::FindViewModel
- L44 _private member_ `const TArray<TSharedRef<IAvaTransitionViewModelRegistry>> PrivateRegistries;` — Private registries used for their own contained purpose. These registries aren't used to find a view model

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheTransitionEditor/Private/ViewModels/Registry/AvaTransitionViewModelRegistryKey.h` (Private)


#### struct `TAvaTransitionViewModelRegistryKey`  
`template<typename InKeyType> struct TAvaTransitionViewModelRegistryKey`  
_L12-25_
- desc: Template struct to allow for specializations to handle the Registry Key Type
- L15 _public member_ `static constexpr int32 Id = -1;` — Id unique to each specialization
- L18 _public prototype_ `static bool IsValid(const InKeyType& InKey);` — Determines whether the provided Key is valid or not
- L24 _public prototype_ `static bool TryGetKey(const TSharedRef<FAvaTransitionViewModel>& InViewModel, InKeyType& OutKey);` — Attempts to get a key of the given type from the provided view model @return true if succeeded in getting the key, false otherwise

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheTransitionEditor/Private/ViewModels/Registry/IAvaTransitionViewModelRegistry.h` (Private)


#### struct `IAvaTransitionViewModelRegistry`  
`struct IAvaTransitionViewModelRegistry`  
_L13-20_
- desc: Interface to allow View Models to be registered via some common interface or trait @see TAvaTransitionViewModelRegistry, TAvaTransitionViewModelRegistryKey
- L15 _public prototype_ `virtual ~IAvaTransitionViewModelRegistry() = default;`
- L17 _public prototype_ `virtual void RegisterViewModel(const TSharedRef<FAvaTransitionViewModel>& InViewModel) = 0;`
- L19 _public prototype_ `virtual void Refresh() = 0;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheTransitionEditor/Private/ViewModels/State/AvaTransitionStateViewModel.h` (Private)


#### class `FAvaTransitionStateViewModel`  
`class FAvaTransitionStateViewModel : public FAvaTransitionViewModel , public IAvaTransitionSelectableExtension , public IAvaTransitionTreeRowExtension , public IAvaTransitionObjectExtension , public IAvaTransitionDragDropExtension , public IAvaTransitionGuidExtension , public IAvaTransitionTickableExtension , public IAvaTransitionDebuggableExtension`  
_L37-195_
- inherits: `FAvaTransitionViewModel,IAvaTransitionSelectableExtension,IAvaTransitionTreeRowExtension,IAvaTransitionObjectExtension,IAvaTransitionDragDropExtension,IAvaTransitionGuidExtension,IAvaTransitionTickableExtension,IAvaTransitionDebuggableExtension`
- desc: View Model for a State Tree State
- L48 _public prototype_ `UE_AVA_INHERITS(FAvaTransitionStateViewModel , FAvaTransitionViewModel , IAvaTransitionSelectableExtension , IAvaTransitionTreeRowExtension , IAvaTransitionObjectExtension , IAvaTransitionDragDropExtension , IAvaTransitionGuidExtension , IAvaTransitionTickableExtension , IAvaTransitionDebuggableExtension ) explicit FAvaTransitionStateViewModel(UStateTreeState* InState);`
- L61 _public prototype_ `bool IsStateEnabled() const;`
- L63 _public prototype_ `void SetStateEnabled(bool bInEnabled);`
- L65 _public function_ `const FGuid& GetStateId() const`
- L70 _public prototype_ `UStateTreeState* GetState() const;`
- L72 _public prototype_ `UStateTreeState* GetParentState() const;`
- L74 _public prototype_ `UAvaTransitionTreeEditorData* GetEditorData() const;`
- L77 _public function_ `static FSlateColor GetDefaultStateColor()` — Get the Default State Color to use when the State Color is unable to be retrieved
- L83 _public prototype_ `FSlateColor GetStateColor() const;` — Gets the color for the State, assigned by the Editor Data
- L89 _public prototype_ `bool TryGetSelectionBehavior(EStateTreeStateSelectionBehavior& OutRuntimeBehavior, EStateTreeStateSelectionBehavior& OutStoredBehavior) const;` — Returns both the Stored Selection Behavior and the one that will run for a given State. These two will typically be the same all the conditions to have such behavior are met
- L91 _public prototype_ `FText GetStateDescription() const;`
- L93 _public prototype_ `FText GetStateTooltip() const;`
- L95 _public prototype_ `FStringView GetComment() const;`
- L97 _public prototype_ `void SetComment(const FString& InComment);`
- L99 _public prototype_ `bool HasAnyBreakpoint() const;`
- L101 _public prototype_ `FText GetBreakpointTooltip() const;`
- L103 _public prototype_ `void UpdateStateDescription(bool bInSetStateName);`
- L105 _public function_ `TSharedPtr<FAvaTransitionConditionContainerViewModel> GetConditionContainer() const`
- L110 _public function_ `TSharedPtr<FAvaTransitionTaskContainerViewModel> GetTaskContainer() const`
- L115 _public function_ `TSharedPtr<FAvaTransitionTransitionContainerViewModel> GetTransitionContainer() const`
- L121 _public function_ `TConstArrayView<FAvaTransitionStateDebugInstance> GetDebugInstances() const`
- L126 _public prototype_ `TSharedRef<SWidget> GetOrCreateDebugIndicatorWidget();`
- L128 _public prototype_ `const FAvaTransitionStateDebugInstance* FindDebugInstance(const FStateTreeInstanceDebugId& InId) const;`
- L132 _public prototype_ `virtual void GatherChildren(FAvaTransitionViewModelChildren& OutChildren) override;`
- L133 _public prototype_ `virtual bool IsValid() const override;`
- L137 _public prototype_ `virtual void SetSelected(bool bInIsSelected) override;`
- L138 _public function_ `virtual bool IsSelected() const override`
- L142 _public prototype_ `virtual bool CanGenerateRow() const override;`
- L143 _public prototype_ `virtual TSharedRef<ITableRow> GenerateRow(const TSharedRef<STableViewBase>& InOwningTableView) override;`
- L144 _public prototype_ `virtual bool IsExpanded() const override;`
- L145 _public prototype_ `virtual void SetExpanded(bool bInIsExpanded) override;`
- L149 _public prototype_ `virtual UObject* GetObject() const override;`
- L150 _public prototype_ `virtual void OnPropertiesChanged(const FPropertyChangedEvent& InPropertyChangedEvent) override;`
- L154 _public prototype_ `virtual TOptional<EItemDropZone> OnCanAcceptDrop(const FDragDropEvent& InDragDropEvent, EItemDropZone InDropZone) override;`
- L155 _public prototype_ `virtual FReply OnAcceptDrop(const FDragDropEvent& InDragDropEvent, EItemDropZone InDropZone) override;`
- L156 _public prototype_ `virtual FReply OnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;`
- L160 _public prototype_ `virtual const FGuid& GetGuid() const override;`
- L164 _public prototype_ `virtual void Tick(float InDeltaTime) override;`
- L169 _public prototype_ `virtual void DebugEnter(const FAvaTransitionDebugInfo& InDebugInfo) override;`
- L170 _public prototype_ `virtual void DebugExit(const FAvaTransitionDebugInfo& InDebugInfo) override;`
- L176 _private member_ `FGuid StateId;` — Cached Guid of the State to avoid having to resolve the State for something that is unchanged
- L178 _private member_ `TWeakObjectPtr<UStateTreeState> StateWeak;`
- L180 _private member_ `TSharedPtr<FAvaTransitionConditionContainerViewModel> ConditionContainer;`
- L182 _private member_ `TSharedPtr<FAvaTransitionTaskContainerViewModel> TaskContainer;`
- L184 _private member_ `TSharedPtr<FAvaTransitionTransitionContainerViewModel> TransitionContainer;`
- L187 _private member_ `TArray<FAvaTransitionStateDebugInstance> DebugInstances;`
- L189 _private member_ `TSharedPtr<SAvaTransitionStateDebugInstanceContainer> DebugIndicatorWidget;`
- L192 _private member_ `FText StateDescription;`
- L194 _private member_ `bool bIsSelected = false;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheTransitionEditor/Private/ViewModels/Task/AvaTransitionTaskContainerViewModel.h` (Private)


#### class `FAvaTransitionTaskContainerViewModel`  
`class FAvaTransitionTaskContainerViewModel : public FAvaTransitionContainerViewModel, public IAvaTransitionWidgetExtension`  
_L12-33_
- inherits: `FAvaTransitionContainerViewModel,IAvaTransitionWidgetExtension`
- desc: View Model serving as a container of all the Tasks in a State
- L15 _public prototype_ `UE_AVA_INHERITS(FAvaTransitionTaskContainerViewModel, FAvaTransitionContainerViewModel, IAvaTransitionWidgetExtension) explicit FAvaTransitionTaskContainerViewModel(UStateTreeState* InState);`
- L19 _public prototype_ `void RefreshTaskBox();`
- L21 _public prototype_ `void OnTasksChanged();`
- L24 _public prototype_ `virtual void GatherChildren(FAvaTransitionViewModelChildren& OutChildren) override;`
- L28 _public prototype_ `virtual TSharedRef<SWidget> CreateWidget() override;`
- L32 _private member_ `TSharedRef<SHorizontalBox> TaskBox;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheTransitionEditor/Private/ViewModels/Task/AvaTransitionTaskViewModel.h` (Private)


#### class `FAvaTransitionTaskViewModel`  
`class FAvaTransitionTaskViewModel : public FAvaTransitionNodeViewModel, public IAvaTransitionWidgetExtension`  
_L14-49_
- inherits: `FAvaTransitionNodeViewModel,IAvaTransitionWidgetExtension`
- desc: View Model for a Task Node
- L17 _public prototype_ `UE_AVA_INHERITS(FAvaTransitionTaskViewModel, FAvaTransitionNodeViewModel, IAvaTransitionWidgetExtension) explicit FAvaTransitionTaskViewModel(const FStateTreeEditorNode& InEditorNode);`
- L21 _public prototype_ `FText GetTaskDescription() const;`
- L23 _public prototype_ `FSlateColor GetTaskColor() const;`
- L25 _public prototype_ `EVisibility GetTaskIconVisibility() const;`
- L27 _public prototype_ `const FSlateBrush* GetTaskIcon() const;`
- L29 _public prototype_ `FSlateColor GetTaskIconColor() const;`
- L31 _public prototype_ `bool IsEnabled() const;`
- L33 _public prototype_ `EVisibility GetBreakpointVisibility() const;`
- L35 _public prototype_ `FText GetBreakpointTooltip() const;`
- L37 _public prototype_ `void UpdateTaskDescription();`
- L40 _public prototype_ `virtual TArrayView<FStateTreeEditorNode> GetNodes(UStateTreeState& InState) const override;`
- L44 _public prototype_ `virtual TSharedRef<SWidget> CreateWidget() override;`
- L48 _private member_ `FText TaskDescription;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheTransitionEditor/Private/ViewModels/Transition/AvaTransitionTransitionContainerViewModel.h` (Private)


#### class `FAvaTransitionTransitionContainerViewModel`  
`class FAvaTransitionTransitionContainerViewModel : public FAvaTransitionContainerViewModel, public IAvaTransitionWidgetExtension`  
_L12-33_
- inherits: `FAvaTransitionContainerViewModel,IAvaTransitionWidgetExtension`
- desc: View Model serving as a container of all the Transitions in a State
- L15 _public prototype_ `UE_AVA_INHERITS(FAvaTransitionTransitionContainerViewModel, FAvaTransitionContainerViewModel, IAvaTransitionWidgetExtension) explicit FAvaTransitionTransitionContainerViewModel(UStateTreeState* InState);`
- L19 _public prototype_ `void RefreshTransitionBox();`
- L21 _public prototype_ `void OnTransitionsChanged();`
- L24 _public prototype_ `virtual void GatherChildren(FAvaTransitionViewModelChildren& OutChildren) override;`
- L28 _public prototype_ `virtual TSharedRef<SWidget> CreateWidget() override;`
- L32 _private member_ `TSharedRef<SHorizontalBox> TransitionBox;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheTransitionEditor/Private/ViewModels/Transition/AvaTransitionTransitionViewModel.h` (Private)


#### class `FAvaTransitionTransitionViewModel`  
`class FAvaTransitionTransitionViewModel : public FAvaTransitionViewModel, public IAvaTransitionWidgetExtension`  
_L16-45_
- inherits: `FAvaTransitionViewModel,IAvaTransitionWidgetExtension`
- desc: View Model for a State Tree Transition
- L19 _public prototype_ `UE_AVA_INHERITS(FAvaTransitionTransitionViewModel, FAvaTransitionViewModel, IAvaTransitionWidgetExtension) explicit FAvaTransitionTransitionViewModel(const FStateTreeTransition& InTransition);`
- L23 _public prototype_ `UAvaTransitionTreeEditorData* GetEditorData() const;`
- L25 _public prototype_ `UStateTreeState* GetState() const;`
- L27 _public prototype_ `FStateTreeTransition* GetTransition() const;`
- L29 _public prototype_ `const FSlateBrush* GetIcon() const;`
- L31 _public prototype_ `FText GetDescription() const;`
- L33 _public prototype_ `EVisibility GetBreakpointVisibility() const;`
- L36 _public prototype_ `virtual void GatherChildren(FAvaTransitionViewModelChildren& OutChildren) override;`
- L40 _public prototype_ `virtual TSharedRef<SWidget> CreateWidget() override;`
- L44 _private member_ `FGuid TransitionId;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheTransitionEditor/Private/Views/Debugger/SAvaTransitionStateDebugInstance.h` (Private)


#### class `SAvaTransitionStateDebugInstance`  
`class SAvaTransitionStateDebugInstance : public SCompoundWidget`  
_L15-35_
- inherits: `SCompoundWidget`
- L18 _public function_ `SLATE_BEGIN_ARGS(SAvaTransitionStateDebugInstance)`
- L19 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TSharedPtr<FAvaTransitionStateViewModel>& InStateViewModel, const FAvaTransitionStateDebugInstance& InDebugInstance);`
- L24 _public prototype_ `virtual void Tick(const FGeometry& InAllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;`
- L28 _private prototype_ `const FAvaTransitionStateDebugInstance* FindDebugInstance() const;`
- L30 _private prototype_ `int32 GetWidgetIndex() const;`
- L32 _private member_ `TWeakPtr<FAvaTransitionStateViewModel> StateViewModelWeak;`
- L34 _private member_ `FStateTreeInstanceDebugId InstanceDebugId;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheTransitionEditor/Private/Views/Debugger/SAvaTransitionStateDebugInstanceContainer.h` (Private)


#### class `SAvaTransitionStateDebugInstanceContainer`  
`class SAvaTransitionStateDebugInstanceContainer : public SCompoundWidget`  
_L17-33_
- inherits: `SCompoundWidget`
- desc: Widget holding all the Debug Instance Widgets
- L20 _public function_ `SLATE_BEGIN_ARGS(SAvaTransitionStateDebugInstanceContainer)`
- L21 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TSharedRef<FAvaTransitionStateViewModel>& InStateViewModel);`
- L25 _public prototype_ `void Refresh();`
- L28 _private prototype_ `EVisibility GetDebuggerVisibility() const;`
- L30 _private member_ `TSharedPtr<SHorizontalBox> DebugInstanceContainer;`
- L32 _private member_ `TWeakPtr<FAvaTransitionStateViewModel> StateViewModelWeak;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheTransitionEditor/Private/Views/SAvaTransitionParameterDetails.h` (Private)


#### class `SAvaTransitionParameterDetails`  
`class SAvaTransitionParameterDetails : public SCompoundWidget`  
_L9-16_
- inherits: `SCompoundWidget`
- L12 _public function_ `SLATE_BEGIN_ARGS(SAvaTransitionParameterDetails)`
- L13 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TSharedRef<FAvaTransitionEditorViewModel>& InEditorViewModel);`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheTransitionEditor/Private/Views/SAvaTransitionSelectionDetails.h` (Private)


#### class `SAvaTransitionSelectionDetails`  
`class SAvaTransitionSelectionDetails : public SCompoundWidget`  
_L16-45_
- inherits: `SCompoundWidget`
- L19 _public function_ `SLATE_BEGIN_ARGS(SAvaTransitionSelectionDetails) : _AdvancedView(false) , _ReadOnly(false)`
- L24 _public prototype_ `SLATE_ARGUMENT(bool, AdvancedView) SLATE_ARGUMENT(bool, ReadOnly) SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TSharedRef<FAvaTransitionSelection>& InSelection);`
- L33 _private prototype_ `void Refresh(const UStateTree& InStateTree);`
- L35 _private prototype_ `void OnSelectionChanged(TConstArrayView<TSharedRef<FAvaTransitionViewModel>> InSelectedItems);`
- L37 _private prototype_ `void OnFinishedChangingProperties(const FPropertyChangedEvent& InPropertyChangedEvent);`
- L39 _private member_ `TWeakPtr<FAvaTransitionSelection> SelectionWeak;`
- L41 _private member_ `TSharedPtr<IDetailsView> DetailsView;`
- L43 _private member_ `FDelegateHandle OnParametersChangedHandle;`
- L44 _private member_ `FDelegateHandle OnSelectionChangedHandle;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheTransitionEditor/Private/Views/SAvaTransitionStateMetadata.h` (Private)


#### class `SAvaTransitionStateMetadata`  
`class SAvaTransitionStateMetadata : public SCompoundWidget`  
_L10-32_
- inherits: `SCompoundWidget`
- L13 _public function_ `SLATE_BEGIN_ARGS(SAvaTransitionStateMetadata)`
- L14 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TSharedRef<FAvaTransitionStateViewModel>& InStateViewModel);`
- L19 _private prototype_ `EVisibility GetCommentVisibility() const;`
- L21 _private prototype_ `FText GetCommentText() const;`
- L23 _private prototype_ `FReply OnCommentButtonClicked();`
- L25 _private prototype_ `void OnCommentTextCommitted(const FText& InCommentText, ETextCommit::Type InCommitType);`
- L27 _private member_ `TWeakPtr<FAvaTransitionStateViewModel> StateViewModelWeak;`
- L29 _private member_ `TSharedPtr<SEditableTextBox> CommentEditableTextBox;`
- L31 _private member_ `bool bEditingComment = false;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheTransitionEditor/Private/Views/SAvaTransitionStateRow.h` (Private)


#### class `SAvaTransitionStateRow`  
`class SAvaTransitionStateRow : public STableRow<TSharedPtr<FAvaTransitionViewModel>>`  
_L16-32_
- inherits: `STableRow<TSharedPtr<FAvaTransitionViewModel>>`
- L19 _public function_ `SLATE_BEGIN_ARGS(SAvaTransitionStateRow)`
- L20 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TSharedRef<STableViewBase>& InOwnerTableView, const TSharedRef<FAvaTransitionStateViewModel>& InStateViewModel);`
- L26 _protected prototype_ `virtual void ConstructChildren(ETableViewMode::Type InOwnerTableMode, const TAttribute<FMargin>& InPadding, const TSharedRef<SWidget>& InContent) override;`
- L29 _protected prototype_ `TOptional<EItemDropZone> OnCanAcceptDrop(const FDragDropEvent& InDragDropEvent, EItemDropZone InDropZone, TSharedPtr<FAvaTransitionViewModel> InItem);`
- L31 _protected prototype_ `FReply OnAcceptDrop(const FDragDropEvent& InDragDropEvent, EItemDropZone InDropZone, TSharedPtr<FAvaTransitionViewModel> InItem);`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheTransitionEditor/Private/Views/SAvaTransitionStateView.h` (Private)


#### class `SAvaTransitionStateView`  
`class SAvaTransitionStateView : public SCompoundWidget`  
_L12-32_
- inherits: `SCompoundWidget`
- L15 _public function_ `SLATE_BEGIN_ARGS(SAvaTransitionStateView)`
- L16 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TSharedRef<FAvaTransitionStateViewModel>& InStateViewModel);`
- L21 _private prototype_ `TSharedRef<SWidget> CreateStateSlotWidget(const TSharedRef<SHorizontalBox>& InStateBox, const TSharedRef<FAvaTransitionStateViewModel>& InStateViewModel);`
- L23 _private prototype_ `const FSlateBrush* GetSelectorIcon() const;`
- L25 _private prototype_ `FText GetSelectorTooltip() const;`
- L27 _private prototype_ `FSlateColor GetActiveStateColor() const;`
- L29 _private prototype_ `EVisibility GetStateBreakpointVisibility() const;`
- L31 _private member_ `TWeakPtr<FAvaTransitionStateViewModel> StateViewModelWeak;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheTransitionEditor/Private/Views/SAvaTransitionTreeDetails.h` (Private)


#### class `SAvaTransitionTreeDetails`  
`class SAvaTransitionTreeDetails : public SCompoundWidget`  
_L10-28_
- inherits: `SCompoundWidget`
- L13 _public function_ `SLATE_BEGIN_ARGS(SAvaTransitionTreeDetails)`
- L14 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TSharedRef<FAvaTransitionEditorViewModel>& InEditorViewModel);`
- L21 _private prototype_ `void Refresh();`
- L23 _private member_ `TWeakPtr<FAvaTransitionEditorViewModel> EditorViewModelWeak;`
- L25 _private member_ `TSharedPtr<IDetailsView> DetailsView;`
- L27 _private member_ `FDelegateHandle OnRefreshHandle;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheTransitionEditor/Private/Views/SAvaTransitionTreeView.h` (Private)


#### class `SAvaTransitionTreeView`  
`class SAvaTransitionTreeView : public SCompoundWidget`  
_L15-56_
- inherits: `SCompoundWidget`
- L18 _public function_ `SLATE_BEGIN_ARGS(SAvaTransitionTreeView)`
- L19 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TSharedRef<FAvaTransitionEditorViewModel>& InEditorViewModel);`
- L25 _public prototype_ `void Refresh();`
- L27 _public prototype_ `void SetSelectedItems(TConstArrayView<TSharedRef<FAvaTransitionViewModel>> InSelectedItems);`
- L29 _public function_ `TSharedRef<SScrollBar> GetVerticalScrollbar() const`
- L35 _private prototype_ `void OnGetChildren(TSharedPtr<FAvaTransitionViewModel> InItem, TArray<TSharedPtr<FAvaTransitionViewModel>>& OutChildren);`
- L37 _private prototype_ `TSharedRef<ITableRow> OnGenerateRow(TSharedPtr<FAvaTransitionViewModel> InItem, const TSharedRef<STableViewBase>& InOwningTableView);`
- L39 _private prototype_ `void OnSelectionChanged(TSharedPtr<FAvaTransitionViewModel> InItem, ESelectInfo::Type InSelectInfo);`
- L41 _private prototype_ `void OnExpansionChanged(TSharedPtr<FAvaTransitionViewModel> InItem, bool bIsExpanded);`
- L43 _private prototype_ `void OnSetExpansionRecursive(TSharedPtr<FAvaTransitionViewModel> InItem, bool bInShouldExpand);`
- L45 _private prototype_ `TSharedPtr<SWidget> OnContextMenuOpening();`
- L47 _private member_ `TWeakPtr<FAvaTransitionEditorViewModel> EditorViewModelWeak;`
- L49 _private member_ `TSharedPtr<STreeView<TSharedPtr<FAvaTransitionViewModel>>> TreeView;`
- L51 _private member_ `TArray<TSharedPtr<FAvaTransitionViewModel>> TopLevelItems;`
- L53 _private member_ `TSharedPtr<SScrollBar> VerticalScrollbar;`
- L55 _private member_ `bool bSyncingSelection = false;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheTransitionEditor/Public/AvaTransitionTreeEditorData.h` (Public)


#### class `UAvaTransitionTreeEditorData`  
`class UAvaTransitionTreeEditorData : public UStateTreeEditorData`  
_L25-71_
- reflection: `UCLASS(MinimalAPI, HideCategories=(Common))`
- inherits: `UStateTreeEditorData`
- L30 _public prototype_ `UAvaTransitionTreeEditorData();`
- L32 _public prototype_ `UStateTreeState& CreateState(const UStateTreeState& InSiblingState, bool bInAfter);`
- L35 _public prototype_ `bool Compare(const UAvaTransitionTreeEditorData* InEditorData) const;` — Returns true if this has the same data as the given editor data
- L38 _public prototype_ `FAvaTagHandle GetTransitionLayer() const;` — `UE_DEPRECATED(5.8, "GetTransitionLayer is deprecated. Use IAvaTransitionBehavior::GetTransitionLayer instead")`
- L41 _public prototype_ `void SetTransitionLayer(const FAvaTagHandle& InTransitionLayer);` — `UE_DEPRECATED(5.8, "SetTransitionLayer is deprecated. Use IAvaTransitionBehavior::SetTransitionLayer instead")`
- L44 _public prototype_ `static FName GetTransitionLayerPropertyName();` — `UE_DEPRECATED(5.8, "Editor data TransitionLayer is deprecated. Use IAvaTransitionBehavior instead")`
- L46 _public function_ `const FAvaTransitionStateMetadata* FindStateMetadata(const FGuid& InStateId) const`
- L51 _public function_ `FAvaTransitionStateMetadata& FindOrAddStateMetadata(const FGuid& InStateId)`
- L56 _public function_ `FSimpleMulticastDelegate& GetOnTreeRequestRefresh()`
- L64 _private member_ `FAvaTagHandle TransitionLayer_DEPRECATED;` — `UE_DEPRECATED(5.8, "TransitionLayer is deprecated. Use IAvaTransitionBehavior Set/Get TransitionLayer instead")` — `UPROPERTY()`
- L68 _private member_ `TMap<FGuid, FAvaTransitionStateMetadata> StateMetadata;` — `UPROPERTY()` — Map of a state's id to its metadata
- L70 _private member_ `FSimpleMulticastDelegate OnTreeRequestRefresh;`

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API AVALANCHETRANSITIONEDITOR_API`
- L17 _namespace_ `namespace UE`
- L17 _namespace_ `namespace AvaTransitionEditor` (scope `UE`)
- L19 _variable_ `constexpr FGuid ColorId_Default;` (scope `UE::AvaTransitionEditor`)
- L20 _variable_ `constexpr FGuid ColorId_In(0x1DDBC788, 0xD5EB400E, 0xBB71E5DA, 0xB27A784D);` (scope `UE::AvaTransitionEditor`)
- L21 _variable_ `constexpr FGuid ColorId_Out(0xE549EFA0, 0xDEFF45A7, 0xA8D907AF, 0xDB8F7643);` (scope `UE::AvaTransitionEditor`)

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheTransitionEditor/Public/IAvaTransitionEditorModule.h` (Public)


#### class `IAvaTransitionEditorModule`  
`class IAvaTransitionEditorModule : public IModuleInterface`  
_L13-33_
- inherits: `IModuleInterface`
- L15 _private member_ `static constexpr const TCHAR* ModuleName = TEXT("Ava`
- L18 _public function_ `static bool IsLoaded()`
- L23 _public function_ `static IAvaTransitionEditorModule& Get()`
- L28 _public prototype_ `DECLARE_DELEGATE_OneParam(FOnBuildDefaultTransitionTree, UAvaTransitionTreeEditorData&);`
- L30 _public prototype_ `virtual FOnBuildDefaultTransitionTree& GetOnBuildDefaultTransitionTree() = 0;` — Returns delegate to build the default Transition Tree
- L32 _public prototype_ `virtual void GenerateTransitionTreeOptionsMenu(UToolMenu* InMenu, IAvaTransitionBehavior* InTransitionBehavior) = 0;`

#### Free symbols / members of external scopes

- L28 _delegate_ `DECLARE_DELEGATE_OneParam(FOnBuildDefaultTransitionTree, UAvaTransitionTreeEditorData&);`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheTransitionEditor/Public/Settings/AvaTransitionEditorSettings.h` (Public)


#### class `UAvaTransitionEditorSettings`  
`class UAvaTransitionEditorSettings : public UDeveloperSettings`  
_L15-39_
- reflection: `UCLASS(MinimalAPI, config=EditorPerProjectUserSettings, meta=(DisplayName="Transition Logic"))`
- inherits: `UDeveloperSettings`
- L20 _public prototype_ `UAvaTransitionEditorSettings();`
- L22 _public prototype_ `UAvaTransitionTreeEditorData* LoadDefaultTemplateEditorData() const;`
- L24 _public function_ `bool ShouldCreateTransitionLogicDefaultScene() const`
- L29 _public prototype_ `void ToggleCreateTransitionLogicDefaultScene();`
- L34 _private member_ `TSoftObjectPtr<UAvaTransitionTree> DefaultTemplate;` — `UPROPERTY(Config, EditAnywhere, Category="Motion Design")` — The template to use when building new transition trees
- L38 _private member_ `bool bCreateTransitionLogicDefaultScene = true;` — `UPROPERTY(Config, EditAnywhere, Category="Motion Design")` — Whether to create the default scene when creating a Motion Design scene for the first time

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API AVALANCHETRANSITIONEDITOR_API`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheTransitionEditor/Public/State/AvaTransitionStateMetadata.h` (Public)


#### struct `FAvaTransitionStateMetadata`  
`struct FAvaTransitionStateMetadata`  
_L9-15_
- reflection: `USTRUCT()`
- L14 _public member_ `FString Comment;` — `UPROPERTY()`
