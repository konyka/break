# Plugins / ModelViewViewModelDebuggerEditor

- module root: `Plugins/Runtime/ModelViewViewModel/Source/ModelViewViewModelDebuggerEditor`
- headers: 8; symbols: 163
- symbol kinds: class=12, enum=2, enumerator=4, function=29, member=26, namespace=19, prototype=60, struct=4, typedef=7
- PrivateDependencyModuleNames: InputCore, LevelEditor, MessageLog, Projects, Slate, SlateCore, ToolMenus, ToolWidgets, WorkspaceMenuStructure
- PublicDependencyModuleNames: Core, CoreUObject, ModelViewViewModel, ModelViewViewModelDebugger

### `Plugins/Runtime/ModelViewViewModel/Source/ModelViewViewModelDebuggerEditor/Private/Styling/MVVMDebuggerEditorStyle.h` (Private)


#### class `UE::MVVM::FMVVMDebuggerEditorStyle`  
`class FMVVMDebuggerEditorStyle : public FSlateStyleSet`  
_L13-39_
- inherits: `FSlateStyleSet`
- L17 _public prototype_ `static void CreateInstance();`
- L18 _public prototype_ `static void DestroyInstance();`
- L20 _public function_ `static FMVVMDebuggerEditorStyle& Get()`
- L27 _private prototype_ `FMVVMDebuggerEditorStyle();`
- L28 _private prototype_ `FMVVMDebuggerEditorStyle(const FMVVMDebuggerEditorStyle&) = delete;`
- L29 _private prototype_ `FMVVMDebuggerEditorStyle& operator=(const FMVVMDebuggerEditorStyle&) = delete;`
- L30 _private prototype_ `~FMVVMDebuggerEditorStyle();`
- L38 _private member_ `static TUniquePtr<FMVVMDebuggerEditorStyle, FCustomDeleter> Instance;`

#### struct `UE::MVVM::FMVVMDebuggerEditorStyle::FCustomDeleter`  
`struct FCustomDeleter`  
_L31-37_
- L33 _public function_ `void operator()(FMVVMDebuggerEditorStyle* Ptr) const`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace MVVM` (scope `UE`)

### `Plugins/Runtime/ModelViewViewModel/Source/ModelViewViewModelDebuggerEditor/Private/Widgets/SDetailsTab.h` (Private)


#### class `UE::MVVM::SDetailsTab`  
`class SDetailsTab : public SCompoundWidget`  
_L14-29_
- inherits: `SCompoundWidget`
- L17 _public function_ `SLATE_BEGIN_ARGS(SDetailsTab)`
- L18 _public prototype_ `SLATE_ARGUMENT_DEFAULT(bool, UseStructDetailView) = false;`
- L22 _public prototype_ `void Construct(const FArguments& InArgs);`
- L23 _public prototype_ `void SetObjects(const TArray<UObject*>& InObjects);`
- L24 _public prototype_ `void SetStruct(TSharedPtr<FStructOnScope> InStructData);`
- L27 _private member_ `TSharedPtr<IDetailsView> DetailView;`
- L28 _private member_ `TSharedPtr<IStructureDetailsView> StructDetailView;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace MVVM` (scope `UE`)

### `Plugins/Runtime/ModelViewViewModel/Source/ModelViewViewModelDebuggerEditor/Private/Widgets/SMainDebugTab.h` (Private)


#### class `UE::MVVM::SMainDebug`  
`class SMainDebug : public SCompoundWidget`  
_L25-75_
- inherits: `SCompoundWidget`
- L28 _public function_ `SLATE_BEGIN_ARGS(SMainDebug)`
- L32 _public prototype_ `void Construct(const FArguments& InArgs, const TSharedRef<SDockTab>& InParentTab);`
- L35 _private prototype_ `void BuildToolMenu();`
- L36 _private prototype_ `void HandlePullDownWindowMenu(FMenuBuilder& MenuBuilder);`
- L37 _private prototype_ `TSharedRef<SWidget> HandleSnapshotMenuContent();`
- L39 _private prototype_ `void HandleTakeSnapshot();`
- L40 _private prototype_ `void HandleLoadSnapshot();`
- L41 _private prototype_ `void HandleSaveSnapshot();`
- L42 _private prototype_ `bool HasValidSnapshot() const;`
- L44 _private prototype_ `void HandleViewSelectionChanged();`
- L45 _private prototype_ `void HandleViewModleSelectionChanged();`
- L46 _private prototype_ `void Selection();`
- L48 _private prototype_ `TSharedRef<SWidget> CreateDockingArea(const TSharedRef<SDockTab>& InParentTab);`
- L49 _private prototype_ `TSharedRef<SDockTab> SpawnViewSelectionTab(const FSpawnTabArgs& Args);`
- L50 _private prototype_ `TSharedRef<SDockTab> SpawnViewModelSelectionTab(const FSpawnTabArgs& Args);`
- L51 _private prototype_ `TSharedRef<SDockTab> SpawnBindingTab(const FSpawnTabArgs& Args);`
- L52 _private prototype_ `TSharedRef<SDockTab> SpawnLiveDetailTab(const FSpawnTabArgs& Args);`
- L53 _private prototype_ `TSharedRef<SDockTab> SpawnEntryDetailTab(const FSpawnTabArgs& Args);`
- L54 _private prototype_ `TSharedRef<SDockTab> SpawnMessagesTab(const FSpawnTabArgs& Args);`
- L57 _private member_ `TSharedPtr<FTabManager> TabManager;`
- L59 _private member_ `TWeakPtr<SDetailsTab> LiveDetailView;`
- L60 _private member_ `TWeakPtr<SDetailsTab> EntryDetailView;`
- L61 _private member_ `TWeakPtr<SMessagesLog> MessageLog;`
- L62 _private member_ `TWeakPtr<SViewSelection> ViewSelection;`
- L63 _private member_ `TWeakPtr<SViewModelSelection> ViewModelSelection;`
- L64 _private member_ `TWeakPtr<SViewModelBindingDetail> ViewModelBindingDetail;`
- L66 _private member_ `TSharedPtr<FDebugSnapshot> Snapshot;`
- L74 _private member_ `ESelection CurrentSelection = ESelection::None;`

#### enum `UE::MVVM::SMainDebug::ESelection`  
`enum class ESelection`  
_L68-73_
- L70 _public enumerator_ `None`
- L71 _public enumerator_ `View`
- L72 _public enumerator_ `ViewModel`

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace MVVM` (scope `UE`)

### `Plugins/Runtime/ModelViewViewModel/Source/ModelViewViewModelDebuggerEditor/Private/Widgets/SMessagesLog.h` (Private)


#### class `UE::MVVM::SMessagesLog`  
`class SMessagesLog : public SCompoundWidget`  
_L11-22_
- inherits: `SCompoundWidget`
- L14 _public function_ `SLATE_BEGIN_ARGS(SMessagesLog)`
- L18 _public prototype_ `void Construct(const FArguments& InArgs);`
- L21 _private prototype_ `FText GetMessageCountText() const;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace MVVM` (scope `UE`)

### `Plugins/Runtime/ModelViewViewModel/Source/ModelViewViewModelDebuggerEditor/Private/Widgets/SSelectionBase.h` (Private)


#### class `UE::MVVM::Private::SSelectionBase`  
`class SSelectionBase : public SCompoundWidget`  
_L24-55_
- inherits: `SCompoundWidget`
- L27 _public function_ `SLATE_BEGIN_ARGS(SSelectionBase)`
- L28 _public prototype_ `SLATE_EVENT(FSimpleDelegate, OnSelectionChanged) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L33 _public prototype_ `void SetSnapshot(const TSharedPtr<FDebugSnapshot> Snapshot);`
- L34 _public function_ `TSharedPtr<FDebugSnapshot> GetSnapshot() const`
- L40 _protected member_ `TSharedPtr<SFilterSearchBox> SearchBox;`
- L41 _protected member_ `TSharedPtr<FDebugSnapshot> Snapshot;`
- L42 _protected member_ `FSimpleDelegate OnSelectionChanged;`
- L43 _protected member_ `bool bIsSelectionReentrant = false;`
- L46 _protected prototype_ `virtual void UpdateSource() = 0;`
- L47 _protected prototype_ `virtual TSharedRef<STableViewBase> BuildListImpl() = 0;`
- L48 _protected prototype_ `virtual FText FilterTextChangedImpl(const FText& InFilterText) = 0;`
- L51 _private prototype_ `void HandleFilterTextChanged(const FText& InFilterText);`
- L52 _private prototype_ `TSharedRef<SWidget> GetViewButtonContent() const;`
- L53 _private prototype_ `FText GetFilterStatusText() const;`
- L54 _private prototype_ `FSlateColor GetFilterStatusTextColor() const;`

#### class `UE::MVVM::SSelectionBase`  
`template <typename ItemType, typename ItemWidgetType> class SSelectionBase : public Private::SSelectionBase`  
_L59-144_
- inherits: `Private::SSelectionBase`
- L62 _public function_ `SLATE_BEGIN_ARGS(SSelectionBase)`
- L67 _public function_ `void Construct(const FArguments& InArgs)`
- L74 _public function_ `TArray<ItemType> GetSelectedItems() const`
- L82 _protected prototype_ `virtual void GatherFilterStringsImpl(ItemType Item, TArray<FString>& OutStrings) const = 0;`
- L83 _protected prototype_ `virtual TSharedRef<SHeaderRow> BuildHeaderRowImpl() const = 0;`
- L84 _protected prototype_ `virtual TArray<ItemType> UpdateSourceImpl(TSharedPtr<TTextFilter<ItemType>> TextFilter) = 0;`
- L86 _protected function_ `virtual FText FilterTextChangedImpl(const FText& InFilterText) override`
- L93 _private function_ `virtual void UpdateSource() override`
- L100 _private function_ `virtual TSharedRef<STableViewBase> BuildListImpl() override`
- L112 _private function_ `void HandleGetFilterStrings(ItemType Item, TArray<FString>& OutStrings)`
- L117 _private function_ `void HandleListSelectionChanged(ItemType TreeItem, ESelectInfo::Type SelectInfo)`
- L131 _private function_ `TSharedRef<ITableRow> HandleGenerateWidgetForItem(ItemType Entry, const TSharedRef<STableViewBase>& OwnerTable) const`
- L139 _protected member_ `TArray<ItemType> FilteredSource;`
- L140 _protected member_ `TSharedPtr<SListView<ItemType>> ListView;`
- L142 _protected typedef_ `using FTextFilter = TTextFilter<ItemType>;`
- L143 _protected member_ `TSharedPtr<FTextFilter> SearchFilter;`

#### Free symbols / members of external scopes

- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace MVVM` (scope `UE`)
- L21 _namespace_ `namespace Private` (scope `UE::MVVM`)

### `Plugins/Runtime/ModelViewViewModel/Source/ModelViewViewModelDebuggerEditor/Private/Widgets/SViewModelBindingDetail.h` (Private)


#### class `UE::MVVM::SViewModelBindingDetail`  
`class SViewModelBindingDetail : public SCompoundWidget`  
_L20-56_
- inherits: `SCompoundWidget`
- L33 _public function_ `friend uint32 GetTypeHash(const FViewModelBindingId& Value)`
- L40 _public function_ `SLATE_BEGIN_ARGS(SViewModelBindingDetail)`
- L44 _public prototype_ `void Construct(const FArguments& InArgs);`
- L46 _public prototype_ `void SetViewModels(TArray<TSharedPtr<FMVVMViewModelDebugEntry>> ViewModel);`
- L49 _private prototype_ `TSharedRef<ITableRow> HandleGenerateWidgetForItem(FViewModelBindingId Entry, const TSharedRef<STableViewBase>& OwnerTable);`
- L50 _private prototype_ `void HandleListSelectionChanged(FViewModelBindingId TreeItem, ESelectInfo::Type SelectInfo);`
- L53 _private member_ `TArray<TSharedPtr<FMVVMViewModelDebugEntry>> ViewModels;`
- L54 _private member_ `TArray<FViewModelBindingId> Entries;`
- L55 _private member_ `TSharedPtr<SListView<FViewModelBindingId>> ListView;`

#### struct `UE::MVVM::SViewModelBindingDetail::FViewModelBindingId`  
`struct FViewModelBindingId`  
_L23-37_
- L25 _public member_ `TSharedPtr<FMVVMViewModelDebugEntry> ViewModel;`
- L26 _public member_ `int32 Index = INDEX_NONE;`
- L28 _public function_ `bool operator==(const FViewModelBindingId& Other) const`

#### struct `TListTypeTraits`  
`template <> struct TListTypeTraits<UE::MVVM::SViewModelBindingDetail::SViewModelBindingDetail::FViewModelBindingId>`  
_L62-106_
- L65 _public typedef_ `typedef UE::MVVM::SViewModelBindingDetail::FViewModelBindingId NullableType;`
- L67 _public typedef_ `using MapKeyFuncs = TDefaultMapHashableKeyFuncs<UE::MVVM::SViewModelBindingDetail::SViewModelBindingDetail::FViewModelBindingId, TSharedRef<ITableRow>, false>;`
- L68 _public typedef_ `using MapKeyFuncsSparse = TDefaultMapHashableKeyFuncs<UE::MVVM::SViewModelBindingDetail::SViewModelBindingDetail::FViewModelBindingId, FSparseItemInfo, false>;`
- L69 _public typedef_ `using SetKeyFuncs = DefaultKeyFuncs<UE::MVVM::SViewModelBindingDetail::SViewModelBindingDetail::FViewModelBindingId>;`
- L72 _public function_ `template<typename U> static void AddReferencedObjects(FReferenceCollector& Collector , TArray<UE::MVVM::SViewModelBindingDetail::FViewModelBindingId>& ItemsWithGeneratedWidgets , TSet<UE::MVVM::SViewModelBindingDetail::FViewModelBindingId>& SelectedItems , TMap<const U*, UE::MVVM::SViewModelBindingDetail::FViewModelBindingId>& WidgetToItemMap)`
- L79 _public function_ `static bool IsPtrValid(const UE::MVVM::SViewModelBindingDetail::FViewModelBindingId& InValue)`
- L84 _public function_ `static void ResetPtr(UE::MVVM::SViewModelBindingDetail::FViewModelBindingId& InValue)`
- L90 _public function_ `static UE::MVVM::SViewModelBindingDetail::FViewModelBindingId MakeNullPtr()`
- L95 _public function_ `static UE::MVVM::SViewModelBindingDetail::FViewModelBindingId NullableItemTypeConvertToItemType(const UE::MVVM::SViewModelBindingDetail::FViewModelBindingId& InValue)`
- L100 _public function_ `static FString DebugDump(UE::MVVM::SViewModelBindingDetail::FViewModelBindingId InValue)`

#### class `TListTypeTraits::SerializerType`  
`class SerializerType`  
_L105-105_

#### struct `TIsValidListItem`  
`template <> struct TIsValidListItem<UE::MVVM::SViewModelBindingDetail::SViewModelBindingDetail::FViewModelBindingId>`  
_L109-115_

#### enum `TIsValidListItem::(anonymous)`  
``  
_L112-114_

#### Free symbols / members of external scopes

- L17 _namespace_ `namespace UE`
- L17 _namespace_ `namespace MVVM` (scope `UE`)
- L113 _enumerator_ `Value = true` (scope `TIsValidListItem::__anon546c89670103`)

### `Plugins/Runtime/ModelViewViewModel/Source/ModelViewViewModelDebuggerEditor/Private/Widgets/SViewModelSelection.h` (Private)


#### class `UE::MVVM::Private::SViewModelSelectionItem`  
`class SViewModelSelectionItem : public SMultiColumnTableRow<TSharedPtr<FMVVMViewModelDebugEntry>>`  
_L16-27_
- inherits: `SMultiColumnTableRow<TSharedPtr<FMVVMViewModelDebugEntry>>`
- L18 _private function_ `SLATE_BEGIN_ARGS(SViewModelSelectionItem)`
- L19 _private prototype_ `SLATE_ARGUMENT(TSharedPtr<FMVVMViewModelDebugEntry>, Entry) SLATE_END_ARGS() void Construct(const FArguments& Args, const TSharedRef<STableViewBase>& OwnerTableView);`
- L23 _private prototype_ `virtual TSharedRef<SWidget> GenerateWidgetForColumn(const FName& ColumnName) override;`
- L26 _private member_ `TSharedPtr<FMVVMViewModelDebugEntry> Entry;`

#### class `UE::MVVM::SViewModelSelection`  
`class SViewModelSelection : public SSelectionBase<TSharedPtr<FMVVMViewModelDebugEntry>, Private::SViewModelSelectionItem>`  
_L30-48_
- inherits: `SSelectionBase<TSharedPtr<FMVVMViewModelDebugEntry>,Private::SViewModelSelectionItem>`
- L33 _private typedef_ `using Super = SSelectionBase<TSharedPtr<FMVVMViewModelDebugEntry>, Private::SViewModelSelectionItem>;`
- L36 _public function_ `SLATE_BEGIN_ARGS(SViewModelSelection)`
- L41 _public prototype_ `void Construct(const FArguments& InArgs);`
- L42 _public prototype_ `void SetSelection(FGuid);`
- L45 _protected prototype_ `virtual void GatherFilterStringsImpl(TSharedPtr<FMVVMViewModelDebugEntry> Item, TArray<FString>& OutStrings) const override;`
- L46 _protected prototype_ `virtual TSharedRef<SHeaderRow> BuildHeaderRowImpl() const override;`
- L47 _protected prototype_ `virtual TArray<TSharedPtr<FMVVMViewModelDebugEntry>> UpdateSourceImpl(TSharedPtr<TTextFilter<TSharedPtr<FMVVMViewModelDebugEntry>>> TextFilter) override;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace MVVM` (scope `UE`)
- L14 _namespace_ `namespace Private` (scope `UE::MVVM`)

### `Plugins/Runtime/ModelViewViewModel/Source/ModelViewViewModelDebuggerEditor/Private/Widgets/SViewSelection.h` (Private)


#### class `UE::MVVM::Private::SViewSelectionItem`  
`class SViewSelectionItem : public SMultiColumnTableRow<TSharedPtr<FMVVMViewDebugEntry>>`  
_L15-26_
- inherits: `SMultiColumnTableRow<TSharedPtr<FMVVMViewDebugEntry>>`
- L17 _private function_ `SLATE_BEGIN_ARGS(SViewSelectionItem)`
- L18 _private prototype_ `SLATE_ARGUMENT(TSharedPtr<FMVVMViewDebugEntry>, Entry) SLATE_END_ARGS() void Construct(const FArguments& Args, const TSharedRef<STableViewBase>& OwnerTableView);`
- L22 _private prototype_ `TSharedRef<SWidget> GenerateWidgetForColumn(const FName& ColumnName);`
- L25 _private member_ `TSharedPtr<FMVVMViewDebugEntry> Entry;`

#### class `UE::MVVM::SViewSelection`  
`class SViewSelection : public SSelectionBase<TSharedPtr<FMVVMViewDebugEntry>, Private::SViewSelectionItem>`  
_L29-47_
- inherits: `SSelectionBase<TSharedPtr<FMVVMViewDebugEntry>,Private::SViewSelectionItem>`
- L32 _private typedef_ `using Super = SSelectionBase<TSharedPtr<FMVVMViewDebugEntry>, Private::SViewSelectionItem>;`
- L35 _public function_ `SLATE_BEGIN_ARGS(SViewSelection)`
- L40 _public prototype_ `void Construct(const FArguments& InArgs);`
- L41 _public prototype_ `void SetSelection(FGuid Id);`
- L44 _protected prototype_ `virtual void GatherFilterStringsImpl(TSharedPtr<FMVVMViewDebugEntry> Item, TArray<FString>& OutStrings) const override;`
- L45 _protected prototype_ `virtual TSharedRef<SHeaderRow> BuildHeaderRowImpl() const override;`
- L46 _protected prototype_ `virtual TArray<TSharedPtr<FMVVMViewDebugEntry>> UpdateSourceImpl(TSharedPtr<TTextFilter<TSharedPtr<FMVVMViewDebugEntry>>> TextFilter) override;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace MVVM` (scope `UE`)
- L13 _namespace_ `namespace Private` (scope `UE::MVVM`)
