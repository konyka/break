# Editor / AnimationModifiers

- module root: `Source/Editor/AnimationModifiers`
- headers: 13; symbols: 274
- symbol kinds: class=15, delegate=3, enum=1, enumerator=6, function=37, macro=4, member=71, namespace=2, prototype=130, struct=3, typedef=2
- PrivateDependencyModuleNames: AnimationBlueprintLibrary, AssetRegistry, AssetTools, ClassViewer, ContentBrowser, Core, CoreUObject, DeveloperSettings, Engine, InputCore, MainFrame, PropertyEditor, Slate, SlateCore, ToolMenus, UnrealEd

### `Source/Editor/AnimationModifiers/Private/AnimationModifierDetailCustomization.h` (Private)


#### class `FAnimationModifierDetailCustomization`  
`class FAnimationModifierDetailCustomization : public IDetailCustomization`  
_L14-26_
- inherits: `IDetailCustomization`
- desc: Animation modifier detail customization
- L17 _public function_ `static TSharedRef<IDetailCustomization> MakeInstance()`
- L19 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;`
- L21 _protected prototype_ `FReply OnUpdateRevisionButtonClicked();`
- L22 _protected prototype_ `FReply OnApplyButtonClicked(bool bForceApply);`
- L24 _protected member_ `TSharedPtr<SButton> UpdateRevisionButton;`
- L25 _protected member_ `UAnimationModifier* ModifierInstance;`

### `Source/Editor/AnimationModifiers/Private/AnimationModifierHelpers.h` (Private)


#### class `FAnimationModifierHelpers`  
`class FAnimationModifierHelpers`  
_L16-117_
- L34 _public function_ `static TSharedRef<SWidget> GetModifierPicker(const FOnClassPicked& OnClassPicked)`
- L56 _public function_ `static UAnimationModifier* CreateModifierInstance(UObject* Outer, UClass* InClass, UObject* Template = nullptr)` — Creates a new Modifier instance to store with the current asset
- L65 _public function_ `static UAnimationModifiersAssetUserData* RetrieveOrCreateModifierUserData(TScriptInterface<IInterface_AssetUserData> AssetUserDataInterface)`
- L83 _public function_ `template<typename Func> static void EnumerateAnimationModifierTags(FStringView Tag, Func&& Callback)` — @brief Enumerate the List[ModifierName,RevisionGuid] formed tag @param[in] Tag The tag to parse @param[in] Callback (FStringView, FGuid) -> bool, the function to apply to each modifier=revision pair, return false to _break_ from enumeration

#### class `FAnimationModifierHelpers::FModifierClassFilter`  
`class FModifierClassFilter : public IClassViewerFilter`  
_L20-32_
- inherits: `IClassViewerFilter`
- desc: ClassViewerFilter for Animation Modifier classes
- L23 _public function_ `bool IsClassAllowed(const FClassViewerInitializationOptions& InInitOptions, const UClass* InClass, TSharedRef< FClassViewerFilterFuncs > InFilterFuncs) override`
- L28 _public function_ `virtual bool IsUnloadedClassAllowed(const FClassViewerInitializationOptions& InInitOptions, const TSharedRef< const IUnloadedBlueprintData > InClass, TSharedRef< FClassViewerFilterFuncs > InFilterFuncs) override`

### `Source/Editor/AnimationModifiers/Private/AnimationModifierSettings.h` (Private)


#### class `UAnimationModifierSettings`  
`class UAnimationModifierSettings : public UDeveloperSettings`  
_L13-25_
- reflection: `UCLASS(config=Engine, meta=(DisplayName="Animation Modifiers"))`
- inherits: `UDeveloperSettings`
- L20 _public member_ `TArray<TSubclassOf<UAnimationModifier>> DefaultAnimationModifiers;` — `UPROPERTY(config, EditAnywhere, Category = Modifiers)` — Set of Animation Modifiers to be added whenever a new Animation Sequence is imported
- L24 _public member_ `bool bApplyAnimationModifiersOnImport = false;` — `UPROPERTY(config, EditAnywhere, Category = Modifiers)` — Whether or not to apply animation modifiers post (re)import

### `Source/Editor/AnimationModifiers/Private/AnimationModifiersModule.h` (Private)


#### class `FAssetTypeActions_AnimationModifier`  
`class FAssetTypeActions_AnimationModifier : public FAssetTypeActions_Base`  
_L22-31_
- inherits: `FAssetTypeActions_Base`
- L26 _public function_ `virtual FText GetName() const override` — IAssetTypeActions Implementation
- L27 _public function_ `virtual FColor GetTypeColor() const override`
- L28 _public function_ `virtual UClass* GetSupportedClass() const override`
- L29 _public function_ `virtual bool HasActions(const TArray<UObject*>& InObjects) const override`
- L30 _public function_ `virtual uint32 GetCategories() override`

#### class `FAnimationModifiersModule`  
`class FAnimationModifiersModule : public IAnimationModifiersModule`  
_L34-69_
- inherits: `IAnimationModifiersModule`
- desc: Animation modifiers module, handles injecting of the AnimationModifiersTab into animation and skeleton editor modes
- L38 _public prototype_ `virtual void StartupModule() override;` — Called right after the module DLL has been loaded and the module object has been created
- L41 _public prototype_ `virtual void ShutdownModule() override;` — Called before the module is unloaded, right before the module object is destroyed
- L44 _public prototype_ `virtual void ShowAddAnimationModifierWindow(const TArray<UAnimSequence*>& InSequences) override;` — Begin IAnimationModifiersModule overrides
- L45 _public prototype_ `virtual void ShowRemoveAnimationModifierWindow(const TArray<UAnimSequence*>& InSequences) override;`
- L46 _public prototype_ `virtual void ApplyAnimationModifiers(const TArray<UAnimSequence*>& InSequences, bool bForceApply = true) override;`
- L51 _protected prototype_ `TSharedRef<FApplicationMode> ExtendApplicationMode(const FName ModeName, TSharedRef<FApplicationMode> InMode);` — Callback for extending an application mode
- L53 _protected prototype_ `void RegisterMenus();`
- L56 _protected member_ `TArray<TWeakPtr<FApplicationMode>> RegisteredApplicationModes;` — Weak list of application modes for which a tab factory was registered
- L58 _protected member_ `FWorkflowApplicationModeExtender Extender;`
- L60 _protected member_ `FDelegateHandle OnGetExtraObjectTagsHandle;`
- L63 _protected prototype_ `void OnAssetPostImport(UFactory* ImportFactory, UObject* ImportedObject);` — Callbacks used to add and apply default animation modifier classes
- L64 _protected prototype_ `void OnAssetPostReimport(UObject* ReimportedObject);`
- L65 _protected prototype_ `void OnInMemoryAssetCreated(UObject* Object);`
- L67 _protected member_ `TSharedPtr<FAssetTypeActions_AnimationModifier> AssetAction;`
- L68 _protected member_ `FDelegateHandle DelegateHandle;`

### `Source/Editor/AnimationModifiers/Private/AnimationModifiersTabSummoner.h` (Private)


#### struct `FAnimationModifiersTabSummoner`  
`struct FAnimationModifiersTabSummoner : public FWorkflowTabFactory`  
_L12-39_
- inherits: `FWorkflowTabFactory`
- desc: Tab summoner which creates the Animation modifiers tab inside of the animation and skeleton editor
- L16 _public member_ `static const FName AnimationModifiersName;` — Tab ID name
- L18 _public function_ `FAnimationModifiersTabSummoner(TSharedPtr<class FAssetEditorToolkit> InHostingApp) : FWorkflowTabFactory(AnimationModifiersName, InHostingApp)`
- L25 _public function_ `virtual TSharedRef<SWidget> CreateTabBody(const FWorkflowTabSpawnInfo& Info) const override`
- L30 _public function_ `virtual FText GetTabToolTipText(const FWorkflowTabSpawnInfo& Info) const override`
- L35 _public function_ `static TSharedPtr<FWorkflowTabFactory> CreateFactory(TSharedPtr<FAssetEditorToolkit> InAssetEditor)`

#### Free symbols / members of external scopes

- L9 _macro_ `#define LOCTEXT_NAMESPACE "AnimationModifiersModule"`

### `Source/Editor/AnimationModifiers/Private/ModifierOutputFilter.h` (Private)


#### class `FCategoryLogOutputFilter`  
`class FCategoryLogOutputFilter : public FStringOutputDevice`  
_L10-54_
- inherits: `FStringOutputDevice`
- L12 _private typedef_ `typedef FStringOutputDevice Super;`
- L14 _private member_ `TArray<FName> CategoryNames;`
- L15 _private member_ `bool bError;`
- L16 _private member_ `bool bWarning;`
- L18 _public function_ `FCategoryLogOutputFilter(const TCHAR* OutputDeviceName = TEXT("")) : Super(OutputDeviceName), bError(false), bWarning(false)`
- L22 _public function_ `void AddCategoryName(const FName& CategoryName)`
- L27 _public function_ `void RemoveCategoryName(const FName& CategoryName)`
- L32 _public function_ `bool ContainsErrors()`
- L37 _public function_ `bool ContainsWarnings()`
- L42 _public function_ `virtual void Serialize(const TCHAR* InData, ELogVerbosity::Type Verbosity, const class FName& Category) override`

### `Source/Editor/AnimationModifiers/Private/SAnimationModifierContentBrowserWindow.h` (Private)


#### class `SAnimationModifierContentBrowserWindow`  
`class SAnimationModifierContentBrowserWindow : public SCompoundWidget`  
_L24-68_
- inherits: `SCompoundWidget`
- desc: UI slate widget allowing the user to add Animation Modifier(s) to a selection of Animation Sequences
- L27 _public function_ `SLATE_BEGIN_ARGS(SAnimationModifierContentBrowserWindow) : _WidgetWindow()`
- L35 _public function_ `SAnimationModifierContentBrowserWindow()`
- L36 _public prototype_ `void Construct(const FArguments& InArgs);`
- L37 _public function_ `virtual bool SupportsKeyboardFocus() const override`
- L38 _public prototype_ `virtual FReply OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent) override;`
- L41 _protected prototype_ `void OnModifierPicked(UClass* PickedClass);` — Callback for when the user picks a specific animation modifier class
- L43 _protected prototype_ `void RemoveModifiersCallback(const TArray<TWeakObjectPtr<UAnimationModifier>>& ModifiersToRemove);` — Callback for when the user wants to remove modifier(s) from the listview
- L46 _protected prototype_ `void CreateInstanceDetailsView();` — Creates the details view widget used to show Animation Modifier object details
- L49 _protected prototype_ `FReply OnApply();` — Button callback, this applies all currently set up Animation Modifiers to the previously selected Animation Sequences
- L51 _protected prototype_ `FReply OnCancel();` — Button callback, closes the dialog/window
- L53 _protected prototype_ `bool CanApply() const;` — Check to see whether or not the user can apply the modifiers in the current state
- L56 _private member_ `TWeakPtr<SWindow> WidgetWindow;` — Window owning this window
- L58 _private member_ `TSharedPtr<IDetailsView> ModifierInstanceDetailsView;`
- L59 _private member_ `TSharedPtr<SMenuAnchor> AddModifierCombobox;`
- L60 _private member_ `TSharedPtr<SModifierListView> ModifierListView;`
- L63 _private member_ `TArray<TSharedPtr<FModifierListviewItem>> ModifierItems;` — Data structures used by the Modifier List View widget
- L65 _private member_ `TArray<UAnimationModifier*> Modifiers;` — Current set of Animation Modifiers that would be added during Apply
- L67 _private member_ `TArray<UAnimSequence*> AnimSequences;` — Previously user-selected Animation Sequences

#### class `SRemoveAnimationModifierContentBrowserWindow`  
`class SRemoveAnimationModifierContentBrowserWindow : public SCompoundWidget`  
_L73-121_
- inherits: `SCompoundWidget`
- desc: UI slate widget allowing the user to remove Animation Modifier(s) to a selection of Animation Sequences
- L76 _public function_ `SLATE_BEGIN_ARGS(SRemoveAnimationModifierContentBrowserWindow) : _WidgetWindow()`
- L84 _public function_ `SRemoveAnimationModifierContentBrowserWindow()`
- L85 _public prototype_ `void Construct(const FArguments& InArgs);`
- L86 _public function_ `virtual bool SupportsKeyboardFocus() const override`
- L87 _public prototype_ `virtual FReply OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent) override;`
- L91 _protected prototype_ `void OnModifierPicked(UClass* PickedClass);` — Callback for when the user picks a specific animation modifier class
- L94 _protected prototype_ `void RemoveModifiersCallback(const TArray<TWeakObjectPtr<UAnimationModifier>>& ModifiersToRemove);` — Callback for when the user wants to remove modifier(s) from the listview
- L97 _protected prototype_ `TSharedRef<SWidget> GenerateAnimationModifierPicker();` — Creates a picker that only displays Animation Modifier(s) currently applied to the selected Animation Sequences
- L100 _protected prototype_ `FReply OnApply();` — Button callback, this applies all currently set up Animation Modifiers to the previously selected Animation Sequences
- L102 _protected prototype_ `FReply OnCancel() const;` — Button callback, closes the dialog/window
- L104 _protected prototype_ `bool CanApply() const;` — Check to see whether or not the user can apply the modifiers in the current state
- L108 _private member_ `TWeakPtr<SWindow> WidgetWindow;` — Window owning this window
- L110 _private member_ `TSharedPtr<IDetailsView> ModifierInstanceDetailsView;`
- L111 _private member_ `TSharedPtr<SMenuAnchor> AddModifierCombobox;`
- L112 _private member_ `TSharedPtr<SModifierListView> ModifierListView;`
- L113 _private member_ `TSharedPtr<SAnimSequencesToBeModifiedViewer> AnimSequencesToBeModifiedListViewer;`
- L116 _private member_ `TArray<TSharedPtr<FModifierListviewItem>> ModifierItems;` — Data structures used by the Modifier List View widget
- L118 _private member_ `TArray<UAnimationModifier*> Modifiers;` — Current set of Animation Modifiers that would be added during Apply
- L120 _private member_ `TArray<UAnimSequence*> AnimSequences;` — Previously user-selected Animation Sequences

### `Source/Editor/AnimationModifiers/Private/SAnimationModifiersTab.h` (Private)


#### class `SAnimationModifiersTab`  
`class SAnimationModifiersTab : public SCompoundWidget, public FEditorUndoClient`  
_L28-107_
- inherits: `SCompoundWidget,FEditorUndoClient`
- L31 _public function_ `SLATE_BEGIN_ARGS(SAnimationModifiersTab)`
- L33 _public prototype_ `SLATE_ARGUMENT(TWeakPtr<class FAssetEditorToolkit>, InHostingApp) SLATE_END_ARGS() SAnimationModifiersTab();`
- L37 _public prototype_ `~SAnimationModifiersTab();`
- L40 _public prototype_ `void Construct(const FArguments& InArgs);` — SWidget functions
- L43 _public prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;` — Begin SCompoundWidget
- L47 _public prototype_ `virtual void PostUndo(bool bSuccess) override;` — Begin FEditorUndoClient
- L48 _public prototype_ `virtual void PostRedo(bool bSuccess) override;`
- L52 _protected prototype_ `void OnModifierPicked(UClass* PickedClass);` — Callback for when user has picked a modifier to add
- L54 _protected prototype_ `void CreateInstanceDetailsView();`
- L57 _protected prototype_ `FReply OnApplyAllModifiersClicked();` — UI apply all modifiers button callback
- L60 _protected prototype_ `void OnApplyModifier(const TArray<TWeakObjectPtr<UAnimationModifier>>& Instances);` — Callbacks for available modifier actions
- L61 _protected prototype_ `void OnRevertModifier(const TArray<TWeakObjectPtr<UAnimationModifier>>& Instances);`
- L62 _protected prototype_ `bool OnCanRevertModifier(const TArray<TWeakObjectPtr<UAnimationModifier>>& Instances);`
- L63 _protected prototype_ `void OnRemoveModifier(const TArray<TWeakObjectPtr<UAnimationModifier>>& Instances);`
- L64 _protected prototype_ `void OnOpenModifier(const TWeakObjectPtr<UAnimationModifier>& Instance);`
- L66 _protected prototype_ `void OnMoveModifierUp(const TWeakObjectPtr<UAnimationModifier>& Instance);`
- L67 _protected prototype_ `void OnMoveModifierDown(const TWeakObjectPtr<UAnimationModifier>& Instance);`
- L70 _protected prototype_ `void Refresh();` — Flags UI dirty and will refresh during the next Tick
- L73 _protected prototype_ `void OnBlueprintCompiled(UBlueprint* Blueprint);` — Callback for compiled blueprints, this ensures to refresh the UI
- L75 _protected prototype_ `void OnAssetOpened(UObject* Object, IAssetEditorInstance* Instance);` — Callback to keep track of when an asset is opened, this is necessary for when an editor document tab is reused and this tab isn't recreated
- L78 _protected prototype_ `void ApplyModifiers(const TArray<UAnimationModifier*>& Modifiers);` — Applying and reverting of modifiers
- L79 _protected prototype_ `void RevertModifiers(const TArray<UAnimationModifier*>& Modifiers);`
- L82 _protected prototype_ `void RetrieveAnimationAsset();` — Retrieves the currently opened animation asset type and modifier user data
- L85 _protected prototype_ `void FindAnimSequencesForSkeleton(TArray<UAnimSequence *> &ReferencedAnimSequences);` — Retrieves all animation sequences which are dependent on the current opened skeleton
- L87 _protected member_ `TWeakPtr<class FAssetEditorToolkit> HostingApp;`
- L90 _protected member_ `USkeleton* Skeleton;` — Retrieved currently open animation asset type
- L91 _protected member_ `UAnimSequence* AnimationSequence;`
- L93 _protected member_ `UAnimationModifiersAssetUserData* AssetUserData;` — Asset user data retrieved from AnimSequence or Skeleton
- L95 _protected member_ `TArray<UBlueprint*> DelegateRegisteredBlueprints;` — List of blueprints for which a delegate was registered for OnCompiled
- L97 _protected member_ `bool bDirty;` — Flag whether or not the UI should be refreshed
- L100 _protected member_ `TSharedPtr<IDetailsView> ModifierInstanceDetailsView;` — UI elements and data
- L101 _protected member_ `TArray<ModifierListviewItem> ModifierItems;`
- L102 _protected member_ `TSharedPtr<SModifierListView> ModifierListView;`
- L103 _protected member_ `TSharedPtr<SMenuAnchor> AddModifierCombobox;`
- L105 _private prototype_ `void RetrieveModifierData();`
- L106 _private prototype_ `void ResetModifierData();`

#### Free symbols / members of external scopes

- L14 _macro_ `#define UE_API ANIMATIONMODIFIERS_API`

### `Source/Editor/AnimationModifiers/Private/SModifierItemRow.h` (Private)


#### class `SModifierItemRow`  
`class SModifierItemRow : public STableRow<ModifierListviewItem>`  
_L18-33_
- inherits: `STableRow<ModifierListviewItem>`
- desc: Listview row widget representing a single modifier instance
- L21 _public function_ `SLATE_BEGIN_ARGS(SModifierItemRow)`
- L22 _public prototype_ `SLATE_ARGUMENT(FOnSingleModifier, OnOpenModifier);`
- L23 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TSharedRef<STableViewBase>& InOwnerTableView, const ModifierListviewItem& Item);`
- L26 _public prototype_ `FReply OnDoubleClicked(const FGeometry& MyGeometry, const FPointerEvent& PointerEvent);`
- L29 _protected prototype_ `FText GetInstanceText() const;`
- L31 _protected member_ `ModifierListviewItem InternalItem;`
- L32 _protected member_ `FOnSingleModifier OnOpenModifier;`

### `Source/Editor/AnimationModifiers/Private/SModifierListview.h` (Private)


#### struct `FModifierListviewItem`  
`struct FModifierListviewItem`  
_L36-43_
- desc: Data representation of a modifier in the listview
- L38 _public member_ `TSubclassOf<UAnimationModifier> Class;`
- L39 _public member_ `TWeakObjectPtr<UAnimationModifier> Instance;`
- L40 _public member_ `int32 Index;`
- L41 _public member_ `UClass* OuterClass;`
- L42 _public member_ `bool OutOfDate;`

#### class `SModifierListView`  
`class SModifierListView : public SCompoundWidget`  
_L47-105_
- inherits: `SCompoundWidget`
- L49 _private function_ `SLATE_BEGIN_ARGS(SModifierListView) : _Items(nullptr)`
- L51 _private prototype_ `SLATE_ARGUMENT(TArray<ModifierListviewItem>*, Items) SLATE_ARGUMENT(TSharedPtr<IDetailsView>, InstanceDetailsView) SLATE_ARGUMENT(FOnModifierArray, OnApplyModifier);`
- L54 _private prototype_ `SLATE_ARGUMENT(FOnCanModifierArray, OnCanRevertModifier) SLATE_ARGUMENT(FOnModifierArray, OnRevertModifier);`
- L56 _private prototype_ `SLATE_ARGUMENT(FOnModifierArray, OnRemoveModifier);`
- L57 _private prototype_ `SLATE_ARGUMENT(FOnSingleModifier, OnOpenModifier);`
- L58 _private prototype_ `SLATE_ARGUMENT(FOnSingleModifier, OnMoveUpModifier);`
- L59 _private prototype_ `SLATE_ARGUMENT(FOnSingleModifier, OnMoveDownModifier);`
- L60 _private prototype_ `SLATE_EVENT(FOnSingleModifier, OnSelectedModifierChanged);`
- L61 _private prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L65 _private prototype_ `TSharedRef<ITableRow> OnGenerateWidgetForList(ModifierListviewItem Item, const TSharedRef<STableViewBase>& OwnerTable);`
- L66 _private prototype_ `void OnSelectionChanged(ModifierListviewItem SelectedItem, ESelectInfo::Type SelectInfo);`
- L69 _private prototype_ `void OnApplyModifier();` — Context menu callbacks for modifier actions
- L70 _private prototype_ `void OnRemoveModifier();`
- L71 _private prototype_ `void OnOpenModifier();`
- L72 _private prototype_ `void OnRevertModifier();`
- L73 _private prototype_ `bool OnCanRevertModifier();`
- L74 _private prototype_ `void OnMoveUpModifier();`
- L75 _private prototype_ `void OnMoveDownModifier();`
- L78 _private prototype_ `const TArray<TWeakObjectPtr<UAnimationModifier>> GetSelectedModifierInstances();` — Retrieve currently select Modifier instances
- L81 _private prototype_ `void Refresh();` — Refreshes the listview panel
- L84 _private prototype_ `TSharedPtr<SWidget> OnContextMenuOpening();` — Generate the context menu widget when requested
- L88 _protected member_ `TSharedPtr<SListView<ModifierListviewItem>> Listview;` — UI elements and listview data
- L89 _protected member_ `TArray<ModifierListviewItem>* ListviewItems;`
- L90 _protected member_ `TSharedPtr<IDetailsView> InstanceDetailsView;`
- L93 _protected member_ `FOnModifierArray OnApplyModifierDelegate;` — Delegates back to SAnimationModifiersTab functionality
- L94 _protected member_ `FOnModifierArray OnRevertModifierDelegate;`
- L95 _protected member_ `FOnCanModifierArray OnCanRevertModifierDelegate;`
- L96 _protected member_ `FOnModifierArray OnRemoveModifierDelegate;`
- L97 _protected member_ `FOnSingleModifier OnOpenModifierDelegate;`
- L98 _protected member_ `FOnSingleModifier OnMoveUpModifierDelegate;`
- L99 _protected member_ `FOnSingleModifier OnMoveDownModifierDelegate;`
- L100 _protected member_ `FOnSingleModifier OnSelectedModifierChangedDelegate;`
- L103 _protected prototype_ `bool CanMoveSelectedItemUp();` — Check whether or not selected modifier can moved in either direction
- L104 _protected prototype_ `bool CanMoveSelectedItemDown();`

#### Free symbols / members of external scopes

- L31 _delegate_ `DECLARE_DELEGATE_OneParam(FOnModifierArray, const TArray<TWeakObjectPtr<UAnimationModifier>>&);`
- L31 _prototype_ `DECLARE_DELEGATE_OneParam(FOnModifierArray, const TArray<TWeakObjectPtr<UAnimationModifier>>&);`
- L32 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FOnCanModifierArray, const TArray<TWeakObjectPtr<UAnimationModifier>>&);`
- L32 _prototype_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FOnCanModifierArray, const TArray<TWeakObjectPtr<UAnimationModifier>>&);`
- L33 _delegate_ `DECLARE_DELEGATE_OneParam(FOnSingleModifier, const TWeakObjectPtr<UAnimationModifier>&);`
- L33 _prototype_ `DECLARE_DELEGATE_OneParam(FOnSingleModifier, const TWeakObjectPtr<UAnimationModifier>&);`
- L45 _typedef_ `typedef TSharedPtr<FModifierListviewItem> ModifierListviewItem;`

### `Source/Editor/AnimationModifiers/Public/AnimationModifier.h` (Public)


#### class `UAnimationModifier`  
`class UAnimationModifier : public UObject`  
_L34-144_
- reflection: `UCLASS(MinimalAPI, Blueprintable, config = Editor, defaultconfig)`
- inherits: `UObject`
- L40 _public prototype_ `UAnimationModifier();`
- L43 _public prototype_ `void ApplyToAnimationSequence(UAnimSequence* AnimSequence) const;` — Applying and reverting the modifier for the given Animation Sequence
- L44 _public prototype_ `void RevertFromAnimationSequence(UAnimSequence* AnimSequence) const;`
- L48 _public prototype_ `void OnApply(UAnimSequence* AnimationSequence);` — `UFUNCTION(BlueprintNativeEvent)` — Executed when the Animation is initialized (native event for debugging / testing purposes)
- L49 _public function_ `virtual void OnApply_Implementation(UAnimSequence* AnimationSequence)`
- L52 _public prototype_ `void OnRevert(UAnimSequence* AnimationSequence);` — `UFUNCTION(BlueprintNativeEvent)`
- L53 _public function_ `virtual void OnRevert_Implementation(UAnimSequence* AnimationSequence)`
- L56 _public prototype_ `bool CanRevert(IInterface_AssetUserData* AssetUserDataInterface) const;` — Returns whether or not this modifier can be reverted, which means it will have to been applied to the given AnimationSequence
- L59 _public prototype_ `bool IsLatestRevisionApplied(IInterface_AssetUserData* AssetUserDataInterface) const;` — Whether or not the latest compiled version of the blueprint is applied for this instance
- L62 _public prototype_ `FGuid GetLatestRevisionGuid() const;` — @brief Get the latest revision GUID of this modifier class
- L66 _public prototype_ `static void GetAssetRegistryTagsForAppliedModifiersFromSkeleton(FAssetRegistryTagsContext Context);` — @brief Get Asset Registry tags for applied modifiers from _skeleton_ @param[out] OutTags AnimationModifiers = %PATH%=%REVISION%;...
- L68 _public member_ `static const FName AnimationModifiersTag;`
- L69 _public member_ `static constexpr TCHAR AnimationModifiersDelimiter = ';`
- L70 _public member_ `static constexpr TCHAR AnimationModifiersAssignment = '=';`
- L73 _public function_ `bool HasLegacyPreviousAppliedModifierOnSkeleton() const` — @brief Check if this Modifier On Skeleton has PreviouslyAppliedModifier_DEPRECATED from previous version
- L75 _public prototype_ `void RemoveLegacyPreviousAppliedModifierOnSkeleton(USkeleton* Skeleton);` — @brief Mark this modifier on skeleton as reverted (affect CanRevert, IsLatestRevisionApplied)
- L78 _public prototype_ `virtual void PostInitProperties() override;`
- L79 _public prototype_ `virtual void Serialize(FArchive& Ar) override;`
- L80 _public prototype_ `virtual void PostLoad() override;`
- L85 _public member_ `bool bReapplyPostOwnerChange = false;` — `UPROPERTY(EditAnywhere, Category = "Settings")` — If this is set to true then the animation modifier will call it's reapply function after any change made to the owning asset.
- L89 _protected prototype_ `const UAnimSequence* GetAnimationSequence();` — Derived class accessors to skeleton and anim sequence
- L90 _protected prototype_ `const USkeleton* GetSkeleton();`
- L93 _protected prototype_ `virtual int32 GetNativeClassRevision() const;` — Used for natively updating the revision GUID, fairly basic and relies on config files currently
- L96 _protected prototype_ `void UpdateCompressedAnimationData();` — Checks if the animation data has to be re-baked / compressed and does so
- L99 _protected prototype_ `void UpdateRevisionGuid(UClass* ModifierClass);` — Updating of blueprint and native GUIDs
- L100 _protected prototype_ `void UpdateNativeRevisionGuid();`
- L102 _protected prototype_ `void ExecuteOnRevert(UAnimSequence* InAnimSequence);`
- L103 _protected prototype_ `void ExecuteOnApply(UAnimSequence* InAnimSequence);`
- L106 _protected prototype_ `static void ApplyToAll(TSubclassOf<UAnimationModifier> ModifierSubClass, bool bForceApply = true);` — Applies all instances of the provided Modifier class to its outer Animation Sequence
- L107 _protected prototype_ `static void LoadModifierReferencers(TSubclassOf<UAnimationModifier> ModifierSubClass);`
- L110 _private member_ `UAnimSequence* CurrentAnimSequence = nullptr;` — These value were not set during OnRevert, prefer to use the input from OnApply() or OnRevert()
- L111 _private member_ `USkeleton* CurrentSkeleton = nullptr;`
- L114 _private prototype_ `UAnimationModifier* GetAppliedModifier(IInterface_AssetUserData* AssetUserDataInterface) const;` — @brief Try get the applied modifier instance (associated with this modifier) on the animation sequence, null if not applied on the sequence
- L117 _private prototype_ `void SetAppliedModifier(TScriptInterface<IInterface_AssetUserData> AssetUserDataInterface, UAnimationModifier* AppliedModifier) const;` — @brief Set the applied modifier instance on the Animation Sequence
- L120 _private prototype_ `UAnimationModifier* FindAndRemoveAppliedModifier(TScriptInterface<IInterface_AssetUserData> AssetUserDataInterface) const;` — @brief Remove the applied modifier instance (associated with this modifier) from the Animation Sequence @return The modifier instance removed
- L124 _private prototype_ `UAnimationModifier* GetLegacyPreviouslyAppliedModifierForModifierOnSkeleton() const;` — @brief Get the applied modifier instance for modifier on skeleton read from _legacy_ version @note This function is only intended for backward compatibility with existing asset @return PreviouslyAppliedModifier_DEPRECATED on Modifier on Skeleton, _before_ upgrade
- L131 _private member_ `FGuid RevisionGuid;` — `UPROPERTY(/*VisibleAnywhere for testing, Category = Revision*/)` — - On class-default-objects, this is the latest revision GUID - On applied modifier instances, this is the revision applied - Not used for other instances
- L135 _private member_ `FGuid AppliedGuid_DEPRECATED;` — `UPROPERTY(/*VisibleAnywhere for testing, Category = Revision */)` — This indicates whether or not the modifier is newer than what has been applied
- L139 _private member_ `int32 StoredNativeRevision;` — `UPROPERTY(config)` — This holds the latest value returned by UpdateNativeRevisionGuid during the last PostLoad (changing this value will invalidate the GUIDs for all instances)
- L143 _private member_ `TObjectPtr<UAnimationModifier> PreviouslyAppliedModifier_DEPRECATED = nullptr;` — `UPROPERTY()` — Serialized version of the modifier that has been previously applied to the Animation Asset

#### struct `UE::Anim::FApplyModifiersScope`  
`struct FApplyModifiersScope`  
_L151-212_
- desc: RAII object to determine how Animation Modifier warning/errors are handled (ignore, user dialog, etc.)
- L179 _public prototype_ `FApplyModifiersScope(const FApplyModifiersScope&) = delete;`
- L180 _public function_ `explicit FApplyModifiersScope(ESuppressionMode Mode = NoChange)`
- L185 _public function_ `~FApplyModifiersScope()`
- L190 _public function_ `static bool IsScopePending()`
- L193 _protected prototype_ `static void HandleError(const UAnimationModifier* Modifier, const FText& Message, const FText& Title);` — Determine how to handle an Animation Modifier error, and execute accordingly
- L196 _protected prototype_ `static bool HandleWarning(const UAnimationModifier* Modifier, const FText& Message, const FText& Title);` — Determine how to handle an Animation Modifier warning, and execute accordingly. Returns whether or not the warning was handled (true) or warrants reverting the applied Animation Modifier (false)
- L200 _private prototype_ `static ESuppressionMode Open(ESuppressionMode Mode = NoChange);` — Open a scope to control error handling when batch applying animation modifiers
- L202 _private prototype_ `static void Close();` — Close the most recent scope
- L204 _private prototype_ `static ESuppressionMode CurrentMode();`
- L207 _private member_ `static TSet<FObjectKey> ErrorResponse;` — Errors already acknowledged
- L209 _private member_ `static TMap<FObjectKey, EAppReturnType::Type> WarningResponse;` — Warnings already ignored or treated as error
- L211 _private member_ `static TArray<ESuppressionMode, TInlineAllocator<4>> ScopeModeStack;` — Error handle mode stack for scopes

#### enum `UE::Anim::FApplyModifiersScope::ESuppressionMode`  
`enum ESuppressionMode : uint8`  
_L155-177_
- L159 _public enumerator_ `NoChange` — Do not change the error handling mode on this scope Use the mode set by parent scope or default (ShowDialog)
- L163 _public enumerator_ `SuppressWarningAndError` — Suppress error dialogs Suppress warnings dialogs, always apply modifiers No user interaction required
- L166 _public enumerator_ `SuppressWarning` — Show error dialogs Suppress warnings dialogs, always apply modifiers
- L169 _public enumerator_ `ShowDialog` — Show warning and error dialogs for first encounter Error dialog for each modifier class will only be showed once
- L172 _public enumerator_ `ForceDialog` — Always show the error or warning dialog Default behavior when no scope was open
- L176 _public enumerator_ `RevertAtWarning` — Suppress error dialogs Suppress warnings dialogs, always revert modifiers No user interaction required

#### Free symbols / members of external scopes

- L23 _macro_ `#define UE_API ANIMATIONMODIFIERS_API`
- L146 _namespace_ `namespace UE`
- L148 _namespace_ `namespace Anim` (scope `UE`)

### `Source/Editor/AnimationModifiers/Public/AnimationModifiersAssetUserData.h` (Public)


#### class `UAnimationModifiersAssetUserData`  
`class UAnimationModifiersAssetUserData : public UAssetUserData`  
_L23-80_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UAssetUserData`
- desc: Asset user data which can be added to a USkeleton or UAnimSequence to keep track of Animation Modifiers
- L33 _public prototype_ `UAnimationModifiersAssetUserData(const FObjectInitializer& ObjectInitializer);`
- L34 _public prototype_ `const TArray<UAnimationModifier*>& GetAnimationModifierInstances() const;`
- L37 _public prototype_ `static bool AddAnimationModifierOfClass(UAnimSequenceBase* AnimationSequenceBase, TSubclassOf<UAnimationModifier> InModifierClass);` — `UFUNCTION(BlueprintCallable, Category=Animation, meta = (ScriptMethod))`
- L40 _protected prototype_ `virtual void PostLoad() override;` — Begin UAssetUserData overrides
- L41 _protected prototype_ `virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;`
- L42 _protected prototype_ `virtual void Serialize(FArchive& Ar) override;`
- L44 _protected prototype_ `virtual void PostEditChangeOwner(const FPropertyChangedEvent& PropertyChangedEvent) override;`
- L48 _protected prototype_ `void AddAnimationModifier(UAnimationModifier* Instance);`
- L49 _protected prototype_ `void RemoveAnimationModifierInstance(UAnimationModifier* Instance);`
- L50 _protected prototype_ `void ChangeAnimationModifierIndex(UAnimationModifier* Instance, int32 Direction);`
- L52 _private prototype_ `void RemoveInvalidModifiers();`
- L55 _protected member_ `TArray<TObjectPtr<UAnimationModifier>> AnimationModifierInstances;` — `UPROPERTY(BlueprintReadOnly, Category="Animation Modifiers")`
- L79 _protected member_ `TMap<FSoftObjectPath, TObjectPtr<UAnimationModifier>> AppliedModifiers;` — `UPROPERTY(BlueprintReadOnly, Category="Animation Modifiers")` — Animation modifiers APPLIED on the owning animation sequence - Key = Modifier in AnimationModifierInstances of owning animation sequence or skeleton - Value = Modifier instance applied Applied modifier instances stores (Properties, RevisionGuid, ...) at Apply Time Which are not visible or editable from user interface In contrast, modifiers in AnimationModifierInstances are objects displayed at the Animation Data Modifier window Where Properties are displayed for user editing anytime Note, Modifier on Skeleton (MoS) applied instances are stored on each animation sequence's asset user data, instead of the skeleton's this design is important to enable applied modifiers can be reverted for each sequence also ensure applying MoS (when [re]importing animation) will not affect the skeleton asset The only time MoS stores an applied instance here is upgrading from previous version The "UAnimationModifier::PreviouslyAppliedModifier_DEPRECATED" data will be migrated here To support proper revert for them For more compatibility handling, check UAnimationModifier::PostLoad() and GetAppliedModifier()

#### Free symbols / members of external scopes

- L15 _macro_ `#define UE_API ANIMATIONMODIFIERS_API`

### `Source/Editor/AnimationModifiers/Public/IAnimationModifiersModule.h` (Public)


#### class `IAnimationModifiersModule`  
`class IAnimationModifiersModule : public IModuleInterface`  
_L10-21_
- inherits: `IModuleInterface`
- L14 _public prototype_ `virtual void ShowAddAnimationModifierWindow(const TArray<UAnimSequence*>& InSequences) = 0;` — Shows a new modal dialog allowing the user to setup Animation Modifiers to be added for all AnimSequences part of InSequences
- L17 _public prototype_ `virtual void ShowRemoveAnimationModifierWindow(const TArray<UAnimSequence*>& InSequences) = 0;` — Shows a new modal dialog allowing the user to setup Animation Modifiers to be removed for all AnimSequences part of InSequences
- L20 _public prototype_ `virtual void ApplyAnimationModifiers(const TArray<UAnimSequence*>& InSequences, bool bForceApply = true) = 0;` — Apply animation modifiers contained by provided Animation Sequences to its respective outers
