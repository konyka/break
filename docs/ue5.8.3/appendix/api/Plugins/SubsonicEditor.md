# Plugins / SubsonicEditor

- module root: `Plugins/Experimental/Subsonic/Source/SubsonicEditor`
- headers: 8; symbols: 156
- symbol kinds: class=14, function=14, member=29, namespace=23, prototype=67, struct=1, typedef=8
- PrivateDependencyModuleNames: AssetDefinition, AudioEditor, AudioMixer, AudioWidgets, BlueprintGraph, ContentBrowser, EditorSubsystem, Engine, GameplayTags, GameplayTagsEditor, InputCore, PropertyBindingUtils, PropertyBindingUtilsEditor, PropertyEditor, Slate, SlateCore, SubsonicCore, SubsonicEngine, ToolWidgets, UnrealEd
- PublicDependencyModuleNames: Core, CoreUObject

### `Plugins/Experimental/Subsonic/Source/SubsonicEditor/Private/SubsonicAssetDefinitions.h` (Private)


#### class `UE::Subsonic::UAssetDefinition_SubsonicEventCollection`  
`class UAssetDefinition_SubsonicEventCollection : public UAssetDefinitionDefault_AudioDiffable`  
_L13-32_
- reflection: `UCLASS()`
- inherits: `UAssetDefinitionDefault_AudioDiffable`
- L19 _public function_ `virtual FText GetAssetDisplayName() const override` — UAssetDefinition Begin
- L20 _public prototype_ `virtual FLinearColor GetAssetColor() const override;`
- L21 _public prototype_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override;`
- L22 _public prototype_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override;`
- L23 _public prototype_ `virtual EAssetCommandResult OpenAssets(const FAssetOpenArgs& OpenArgs) const override;`
- L25 _public prototype_ `virtual bool GetThumbnailActionOverlay(const FAssetData& InAssetData, FAssetActionThumbnailOverlayInfo& OutActionOverlayInfo) const override;`
- L26 _public prototype_ `virtual EAssetCommandResult ActivateAssets(const FAssetActivateArgs& ActivateArgs) const override;`
- L27 _public prototype_ `virtual void GetAssetActionButtonExtensions(const FAssetData& InAssetData, TArray<FAssetButtonActionExtension>& OutExtensions) const override;`
- L29 _public prototype_ `virtual const FSlateBrush* GetThumbnailBrush(const FAssetData& InAssetData, const FName InClassName) const override;`
- L30 _public prototype_ `virtual const FSlateBrush* GetIconBrush(const FAssetData& InAssetData, const FName InClassName) const override;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace Subsonic` (scope `UE`)

### `Plugins/Experimental/Subsonic/Source/SubsonicEditor/Private/SubsonicEditorSubsystem.h` (Private)


#### class `UE::Subsonic::USubsonicEditorSubsystem`  
`class USubsonicEditorSubsystem final : public UEditorSubsystem`  
_L19-38_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UEditorSubsystem`
- desc: Interface to the Subsonic Editor Functionality.
- L24 _public prototype_ `void Initialize(FSubsystemCollectionBase& Collection) override;`
- L25 _public prototype_ `void Deinitialize() override;`
- L31 _public prototype_ `void RebuildActionStructChildCache();` — Rebuilds the action struct child cache (called on initialize, but available to refresh if new modules are loaded or unloaded). Cached to allow for faster iteration over projects with large numbers of registered struct types.
- L34 _public prototype_ `void ForEachActionStruct(TFunctionRef<void(const UScriptStruct& Struct)> StructIter) const;` — Iterates over cached action struct child pointers.
- L37 _private member_ `TArray<TWeakObjectPtr<const UScriptStruct>> ActionStructs;`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace Subsonic` (scope `UE`)

### `Plugins/Experimental/Subsonic/Source/SubsonicEditor/Private/SubsonicEventCollectionEditor.h` (Private)


#### class `UE::Subsonic::Editor::FEventCollectionEditor`  
`class FEventCollectionEditor : public FAssetEditorToolkit, public FNotifyHook, public FEditorUndoClient`  
_L25-173_
- inherits: `FAssetEditorToolkit,FNotifyHook,FEditorUndoClient`
- L28 _public typedef_ `using FActionHandle = Core::FActionHandle;`
- L29 _public typedef_ `using FEventHandle = Core::FEventHandle;`
- L30 _public typedef_ `using FCollectionHandle = Core::FCollectionHandle;`
- L32 _public typedef_ `using FSubsonicEvent = Core::FSubsonicEvent;`
- L33 _public typedef_ `using FSubsonicEventActionDefinition = Core::FSubsonicEventActionDefinition;`
- L34 _public typedef_ `using FSubsonicEventCollectionDefinition = Core::FSubsonicEventCollectionDefinition;`
- L36 _public member_ `static const FName EditorName;`
- L38 _public prototype_ `FEventCollectionEditor() = default;`
- L39 _public prototype_ `virtual ~FEventCollectionEditor();`
- L41 _public prototype_ `virtual void RegisterTabSpawners(const TSharedRef<FTabManager>& TabManager) override;`
- L42 _public prototype_ `virtual void UnregisterTabSpawners(const TSharedRef<FTabManager>& TabManager) override;`
- L44 _public prototype_ `void Init(const EToolkitMode::Type Mode, const TSharedPtr<IToolkitHost>& InitToolkitHost, USubsonicEventCollection& EventCollection);`
- L46 _public prototype_ `USubsonicEventCollection* GetEventCollection() const;`
- L49 _public prototype_ `void SelectEventInTree(FName EventName);` — Selects the event row (not an action row) in the event tree for the given event name.
- L51 _public prototype_ `void TryInvokeTab(FName TabName) const;`
- L54 _public prototype_ `virtual FName GetToolkitFName() const override;` — IToolkit Interface
- L55 _public prototype_ `virtual FText GetBaseToolkitName() const override;`
- L56 _public prototype_ `virtual FString GetWorldCentricTabPrefix() const override;`
- L57 _public prototype_ `virtual FLinearColor GetWorldCentricTabColorScale() const override;`
- L58 _public prototype_ `virtual const FSlateBrush* GetDefaultTabIcon() const override;`
- L59 _public prototype_ `virtual FLinearColor GetDefaultTabColor() const override;`
- L62 _public prototype_ `virtual FName GetEditorName() const override;` — IAssetEditorInstance Interface
- L65 _public prototype_ `virtual void PostUndo(bool bSuccess) override;` — FEditorUndoClient Interface
- L66 _public function_ `virtual void PostRedo(bool bSuccess) override`
- L69 _public prototype_ `virtual void NotifyPostChange(const FPropertyChangedEvent& PropertyChangedEvent, FProperty* PropertyThatChanged) override;` — FNotifyHook Interface
- L72 _private prototype_ `void TransactEvent(const Core::FEventHandle EventHandle, FText Description, TFunctionRef<void(FSubsonicEvent&)> TransactionFunc) const;`
- L73 _private prototype_ `void TransactEventCollection(FText Description, TFunctionRef<void(FSubsonicEventCollectionDefinition&)> TransactionFunc) const;`
- L75 _private prototype_ `TSharedRef<SWidget> InitEventTreeView();`
- L114 _private prototype_ `Core::FSubsonicEventActionDefinition* InsertAction(const FHandleVariant& InHandleVariant);` — Inserts action. If the handle variant points at an event, adds to end of event array. If it points to an action, inserts before the given action.
- L117 _private prototype_ `void MoveDroppedAction(const Core::FActionHandle& SourceAction, const FHandleVariant& HandleVariant, EItemDropZone DropZone);` — Moves an action to the position relative to TargetAction per the given DropZone.
- L119 _private prototype_ `void BuildTransport();`
- L121 _private prototype_ `void ExecutePreviewEvent(const Core::FEventHandle& EventHandle);`
- L123 _private prototype_ `void InitBindings();`
- L125 _private typedef_ `using SHandleVariantTableRow = STableRow<TSharedPtr<FHandleVariant>>;`
- L128 _private prototype_ `TSharedRef<SHandleVariantTableRow> InitDraggableEventRow(TSharedPtr<FHandleVariant> HandleVariant, const TSharedRef<STableViewBase>& TableView);` — Currently, only supports actions. Could support dragging and ordering events in specialized view sorted by user-defined index in the future.
- L130 _private prototype_ `TSharedRef<ITableRow> OnEventTree_GenerateRow(TSharedPtr<FHandleVariant> HandleVariant, const TSharedRef<STableViewBase>& TableView);`
- L131 _private prototype_ `void OnEventTree_GetChildren(TSharedPtr<FHandleVariant> InParent, TArray<TSharedPtr<FHandleVariant>>& OutChildren);`
- L132 _private prototype_ `void OnEventTree_RowSelected(TSharedPtr<FHandleVariant> HandleVariant, ESelectInfo::Type SelectInfo);`
- L134 _private prototype_ `void ExpandAllEvents();`
- L135 _private prototype_ `void CollapseAllEvents();`
- L137 _private prototype_ `void RebuildEventTree(bool bRebuildListView = false);`
- L139 _private prototype_ `void RestartAudition(bool bAutoEventsEnabled = true);`
- L140 _private prototype_ `void StartAudition();`
- L141 _private prototype_ `void StopAudition();`
- L142 _private prototype_ `void ToggleAudition();`
- L144 _private member_ `TStrongObjectPtr<USubsonicEventCollectionExecutor> PreviewExecutor;`
- L146 _private member_ `TSharedPtr<IDetailsView> EventTreeInspectorView;`
- L147 _private member_ `TSharedPtr<FTabManager::FStack> DetailsStack;`
- L148 _private member_ `TStrongObjectPtr<USubsonicEventTreeDetailsView> TreeDetailsView;`
- L150 _private member_ `TSharedPtr<FTabManager::FStack> EventTreeStack;`
- L152 _private member_ `TSharedPtr<IDetailsView> ParametersDetailsView;`
- L153 _private member_ `TSharedPtr<FTabManager::FStack> ParametersStack;`
- L154 _private member_ `TStrongObjectPtr<USubsonicCollectionParametersView> ParametersView;`
- L156 _private member_ `TArray<TSharedPtr<FHandleVariant>> EventTreeRootHandles;`
- L157 _private member_ `TMap<FName, TArray<TSharedPtr<FHandleVariant>>> EventTreeChildHandles;`
- L158 _private member_ `TSharedPtr<STreeView<TSharedPtr<FHandleVariant>>> EventTreeView;`
- L159 _private member_ `FString EventViewFilter;`
- L162 _private member_ `TArray<TSharedPtr<FString>> ActionComboValues;` — Value names of selectable actions in event tree view
- L166 _private member_ `TSharedPtr<ISinglePropertyView> CollectionView;` — Single property view of collection for use to capture bespoke property handles for visualization in contexts outside of a contextual details layout/panel
- L168 _private member_ `FDelegateHandle StaleBindingsDelegateHandle;`
- L172 _private member_ `TMap<FName, double> EventExecuteLerpTimes;` — Tracks the last time each event was test-executed via the play button, used to Lerp the button green and fade back to white.

#### class `UE::Subsonic::Editor::FEventCollectionEditor::FHandleVariant`  
`class FHandleVariant`  
_L77-110_
- L79 _private member_ `TVariant<Core::FEventHandle, Core::FActionHandle> Handle;`
- L82 _public function_ `const Core::FActionHandle& GetAction() const`
- L88 _public function_ `const Core::FEventHandle& GetEvent() const`
- L95 _public function_ `bool IsAction() const`
- L100 _public function_ `bool IsEvent() const`
- L106 _public function_ `template <typename HandleType> void Set(HandleType NewHandle)`

#### Free symbols / members of external scopes

- L21 _namespace_ `namespace UE`
- L21 _namespace_ `namespace Subsonic` (scope `UE`)
- L23 _namespace_ `namespace Editor` (scope `UE::Subsonic`)

### `Plugins/Experimental/Subsonic/Source/SubsonicEditor/Private/SubsonicEventCollectionEditorCommands.h` (Private)


#### class `UE::Subsonic::Editor::FEventCollectionEditorCommands`  
`class FEventCollectionEditorCommands : public TCommands<FEventCollectionEditorCommands>`  
_L9-28_
- inherits: `TCommands<FEventCollectionEditorCommands>`
- L12 _public function_ `FEventCollectionEditorCommands() : TCommands<FEventCollectionEditorCommands>("SubsonicEditor", NSLOCTEXT("SubsonicEditor", "SubsonicEditorCommands_EditorName", "Subsonic Event Collection Editor"), NAME_None, "SubsonicStyle")`
- L18 _public member_ `TSharedPtr<FUICommandInfo> StartAudition;` — Creates and initializes Subsonic audition executor
- L21 _public member_ `TSharedPtr<FUICommandInfo> StopAudition;` — Destroys the auditioning executor, clearing associate subscriber state.
- L24 _public member_ `TSharedPtr<FUICommandInfo> ToggleAudition;` — Starts or stops the currently auditioning executor
- L27 _public prototype_ `virtual void RegisterCommands() override;` — Initialize commands

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace Subsonic` (scope `UE`)
- L7 _namespace_ `namespace Editor` (scope `UE::Subsonic`)

### `Plugins/Experimental/Subsonic/Source/SubsonicEditor/Private/SubsonicEventCollectionFactory.h` (Private)


#### class `UE::Subsonic::Editor::USubsonicEventCollectionFactory`  
`class USubsonicEventCollectionFactory : public UFactory`  
_L16-23_
- reflection: `UCLASS()`
- inherits: `UFactory`
- L21 _private prototype_ `virtual UObject* FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags InFlags, UObject* InContext, FFeedbackContext* InFeedbackContext) override;`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace Subsonic` (scope `UE`)
- L13 _namespace_ `namespace Editor` (scope `UE::Subsonic`)

### `Plugins/Experimental/Subsonic/Source/SubsonicEditor/Private/SubsonicEventCollectionViews.h` (Private)


#### class `UE::Subsonic::Editor::USubsonicEventCollectionViewBase`  
`class USubsonicEventCollectionViewBase : public UObject`  
_L16-28_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject`
- desc: Base implementation for Subsonic Collection view wrappers that coincide with edit customizations
- L22 _public function_ `void SetCollection(USubsonicEventCollection* InCollection)`
- L23 _public function_ `const USubsonicEventCollection* GetConstCollection() const`
- L24 _public function_ `USubsonicEventCollection* GetCollection()`
- L27 _private member_ `TWeakObjectPtr<USubsonicEventCollection> Collection;`

#### class `UE::Subsonic::Editor::USubsonicCollectionParametersView`  
`class USubsonicCollectionParametersView : public USubsonicEventCollectionViewBase`  
_L31-34_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `USubsonicEventCollectionViewBase`

#### class `UE::Subsonic::Editor::USubsonicEventTreeDetailsView`  
`class USubsonicEventTreeDetailsView : public USubsonicEventCollectionViewBase`  
_L37-44_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `USubsonicEventCollectionViewBase`
- L42 _public member_ `FName Event;`
- L43 _public member_ `int32 ActionIndex = INDEX_NONE;`

#### class `UE::Subsonic::Editor::FCollectionPropertyCustomizationBase`  
`class FCollectionPropertyCustomizationBase : public IDetailCustomization`  
_L46-58_
- inherits: `IDetailCustomization`
- L49 _protected member_ `FText HeaderName;`
- L52 _protected prototype_ `static TSharedPtr<IPropertyHandle> CacheCollectionPropertyHandle( IDetailLayoutBuilder& LayoutBuilder, USubsonicEventCollectionViewBase& View, FName ChildPropertyName);`
- L57 _protected prototype_ `static USubsonicEventCollectionViewBase* GetViewFromBuilder(IDetailLayoutBuilder& LayoutBuilder);`

#### class `UE::Subsonic::Editor::FCollectionParametersDetailCustomization`  
`class FCollectionParametersDetailCustomization : public FCollectionPropertyCustomizationBase`  
_L60-68_
- inherits: `FCollectionPropertyCustomizationBase`
- L63 _public prototype_ `FCollectionParametersDetailCustomization();`
- L66 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailLayout) override;` — IDetailCustomization interface

#### class `UE::Subsonic::Editor::FEventTreeSelectionDetailCustomization`  
`class FEventTreeSelectionDetailCustomization : public FCollectionPropertyCustomizationBase`  
_L70-76_
- inherits: `FCollectionPropertyCustomizationBase`
- L73 _public prototype_ `FEventTreeSelectionDetailCustomization();`
- L75 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& LayoutBuilder) override;`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace Subsonic` (scope `UE`)
- L12 _namespace_ `namespace Editor` (scope `UE::Subsonic`)

### `Plugins/Experimental/Subsonic/Source/SubsonicEditor/Private/SubsonicPropertyBindingExtension.h` (Private)


#### struct `UE::Subsonic::Editor::FSubsonicBindingContextStruct`  
`struct FSubsonicBindingContextStruct : public FBindingContextStruct`  
_L29-42_
- inherits: `FBindingContextStruct`
- desc: Extends FBindingContextStruct to accept a const UPropertyBag* and track whether the binding originates from an event-level parameter bag. The const_cast in the constructor is required because FBindingContextStruct::Struct is a non-const UStruct* — the underlying property-access API is not const-correct.
- L31 _public member_ `bool bIsEventBinding = false;`
- L33 _public function_ `FSubsonicBindingContextStruct( const UPropertyBag* InBag, const FSlateBrush* InIcon = nullptr, const FText& InDisplayText = FText::GetEmpty(), const FText& InTooltipText = FText::GetEmpty(), const FText& InSection = FText::GetEmpty()) : FBindingContextStruct(const_cast<UPropertyBag*>(InBag), InIcon, InDisplayText, InTooltipText, InSection)`

#### class `UE::Subsonic::Editor::FSubsonicPropertyBindingExtension`  
`class FSubsonicPropertyBindingExtension : public FPropertyBindingExtension`  
_L50-99_
- inherits: `FPropertyBindingExtension`
- desc: Only shows the binding dropdown on properties not decorated with 'NoBinding' Metadata tag. Overrides ExtendWidgetRow to populate the binding menu with parameters from the collection- or event-level (Event value supersedes collection value if types match) Subsonic 'Parameter' property bags.
- L53 _public typedef_ `using FNavigateToPropertyOwnerFunc = TFunction<void(FName)>;`
- L55 _public prototype_ `explicit FSubsonicPropertyBindingExtension(FNavigateToPropertyOwnerFunc InNavigateToPropertyOwner);`
- L58 _public prototype_ `virtual bool IsPropertyExtendable(const UClass* InObjectClass, const IPropertyHandle& InPropertyHandle) const override;`
- L59 _public prototype_ `virtual void ExtendWidgetRow(FDetailWidgetRow& WidgetRow, const IDetailLayoutBuilder& InDetailBuilder, const UClass* InObjectClass, TSharedPtr<IPropertyHandle> InPropertyHandle) override;`
- L65 _private member_ `static const int32 CollectionContextIndex = 0;` — Index into the BindingContextStructs array built in GenerateBindingMenu / ExtendWidgetRow. Collection is always added first (index 0), event second (index 1).
- L67 _private prototype_ `FPropertyBindingWidgetArgs InitWidgetRow( USubsonicEventCollection& Collection, USubsonicEventTreeDetailsView& View, const FProperty* TargetProperty, FDetailWidgetRow& WidgetRow);`
- L73 _private prototype_ `TSharedRef<SWidget> GenerateBindingMenu( const FProperty* TargetProperty, TFunction<FName()> GetCurrentBindingParam, TWeakObjectPtr<USubsonicEventCollection> WeakCollection, TWeakObjectPtr<USubsonicEventTreeDetailsView> WeakView);`
- L79 _private prototype_ `static FText GetBindingText( TFunction<FName()> GetCurrentBindingParam, TWeakObjectPtr<USubsonicEventCollection> WeakCollection, TWeakObjectPtr<USubsonicEventTreeDetailsView> WeakView);`
- L84 _private prototype_ `static void RemoveBinding( TWeakObjectPtr<USubsonicEventCollection> WeakCollection, TWeakObjectPtr<USubsonicEventTreeDetailsView> WeakView, const FProperty* TargetProperty);`
- L89 _private prototype_ `static void AddParamBinding( USubsonicEventCollection* Collection, USubsonicEventTreeDetailsView* DetailsView, FName PropertyName, const int32 SourceStructIndex, const FProperty* SourceProperty);`
- L96 _private prototype_ `static TSharedRef<FCheckBoxStyle> GetCheckboxEntryStyle(const FProperty& BagProp);`
- L98 _private member_ `FNavigateToPropertyOwnerFunc NavigateToPropertyOwner;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace Subsonic` (scope `UE`)
- L15 _namespace_ `namespace Core` (scope `UE::Subsonic`)
- L20 _namespace_ `namespace Editor` (scope `UE::Subsonic`)
- L44 _prototype_ `void TransactEventCollection(FText Description, USubsonicEventCollection& Collection, TFunctionRef<void(Core::FSubsonicEventCollectionDefinition&)> TransactionFunc);` (scope `UE::Subsonic::Editor`)

### `Plugins/Experimental/Subsonic/Source/SubsonicEditor/Private/SubsonicSlateStyle.h` (Private)


#### class `UE::Subsonic::Editor::FSlateStyle`  
`class FSlateStyle final : public FSlateStyleSet`  
_L11-61_
- inherits: `FSlateStyleSet`
- L14 _public function_ `FSlateStyle() : FSlateStyleSet("SubsonicStyle")`
- L57 _public function_ `~FSlateStyle()`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace Subsonic` (scope `UE`)
- L9 _namespace_ `namespace Editor` (scope `UE::Subsonic`)
