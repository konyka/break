# Plugins / InstanceDataObjectFixupTool

- module root: `Plugins/Experimental/InstanceDataObjectFixupTool/Source`
- headers: 8; symbols: 135
- symbol kinds: class=7, enum=2, enumerator=9, function=3, macro=4, member=22, namespace=9, prototype=76, typedef=1, variable=2
- PrivateDependencyModuleNames: EditorWidgets, InputCore, Json, PropertyEditor, SceneOutliner, Slate, SlateCore, TedsAlerts, TedsOutliner, TedsQueryStack, TedsTableViewer, TedsTypeInfo, ToolWidgets, TypedElementFramework, UnrealEd, WorkspaceMenuStructure
- PublicDependencyModuleNames: Core, CoreUObject, Engine

### `Plugins/Experimental/InstanceDataObjectFixupTool/Source/Private/DataRecoveryToolStyle.h` (Private)


#### class `FDataRecoveryToolStyle`  
`class FDataRecoveryToolStyle : public FSlateStyleSet`  
_L10-27_
- inherits: `FSlateStyleSet`
- desc: Manages the style which provides resources for data recovery tool widgets.
- L13 _public prototype_ `static void Register();`
- L14 _public prototype_ `static void Unregister();`
- L15 _public prototype_ `static void Shutdown();`
- L18 _public prototype_ `static const FDataRecoveryToolStyle& Get();` — @return The Slate style set for data recovery tool widgets
- L20 _public prototype_ `static void ReinitializeStyle();`
- L21 _public prototype_ `void InitPadding();`
- L24 _private prototype_ `FDataRecoveryToolStyle();`
- L26 _private member_ `static TSharedPtr<FDataRecoveryToolStyle> DataRecoveryToolStyle;`

### `Plugins/Experimental/InstanceDataObjectFixupTool/Source/Private/DataRecoveryToolUtils.h` (Private)


#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace DataRecoveryTool` (scope `UE`)
- L12 _namespace_ `namespace Utils` (scope `UE::DataRecoveryTool`)
- L14 _prototype_ `TObjectPtr<UObject> GetInstanceDataObjectFromSelectedClassPath(const FTopLevelAssetPath& ClassPath, TObjectPtr<UObject>* OutOwner = nullptr);` (scope `UE::DataRecoveryTool::Utils`)
- L16 _prototype_ `void ApplyTransforms(const TWeakPtr<TMap<FTopLevelAssetPath, FInstanceDataTransformSet>>& StagedTransformsWeak, UObject*& IDO, TNotNull<UObject*> Owner);` (scope `UE::DataRecoveryTool::Utils`)
- L18 _prototype_ `bool ContainsPath(const FTopLevelAssetPath& Parent, const FTopLevelAssetPath& Candidate);` (scope `UE::DataRecoveryTool::Utils`)
- L20 _namespace_ `namespace Snapshot` (scope `UE::DataRecoveryTool::Utils`)
- L22 _variable_ `constexpr EObjectFlags FlagsToAdd = RF_Transient | RF_DuplicateTransient;` (scope `UE::DataRecoveryTool::Utils::Snapshot`)
- L23 _variable_ `constexpr EObjectFlags FlagsToRemove = RF_Public | RF_Standalone;` (scope `UE::DataRecoveryTool::Utils::Snapshot`)
- L25 _prototype_ `bool IsASnapshot(const UObject* Instance);` (scope `UE::DataRecoveryTool::Utils::Snapshot`)
- L28 _prototype_ `void UpdateTedsIdoAlertColumn( Editor::DataStorage::ICoreProvider* Storage, Editor::DataStorage::RowHandle Row, const uint32 InstanceWithIdoCount );` (scope `UE::DataRecoveryTool::Utils`)

### `Plugins/Experimental/InstanceDataObjectFixupTool/Source/Private/InstanceDataObjectFixupDetailCustomization.h` (Private)


#### class `FInstanceDataObjectNameWidgetOverride`  
`class FInstanceDataObjectNameWidgetOverride : public FDetailsNameWidgetOverrideCustomization`  
_L19-41_
- inherits: `FDetailsNameWidgetOverrideCustomization`
- L22 _public prototype_ `FInstanceDataObjectNameWidgetOverride(const TSharedRef<FInstanceDataObjectFixupPanel>& DiffPanel);`
- L23 _public prototype_ `virtual ~FInstanceDataObjectNameWidgetOverride() override = default;`
- L24 _public prototype_ `virtual TSharedRef<SWidget> CustomizeName(TSharedRef<SWidget> InnerNameContent, FPropertyPath& Path) override;`
- L27 _private prototype_ `int32 GetNameWidgetIndex(FPropertyPath Path) const;`
- L28 _private prototype_ `TSharedRef<SWidget> GeneratePropertyRedirectMenu(FPropertyPath Path) const;`
- L30 _private prototype_ `TSet<FPropertyPath> GetRedirectOptions(const UStruct* Struct, void* Value) const;`
- L31 _private prototype_ `void GetRedirectOptions(const UStruct* Struct, void* Value, const FPropertyPath& Path, TSet<FPropertyPath>& OutPaths) const;`
- L32 _private prototype_ `void GetRedirectOptions(const FProperty* Property, void* Value, const FPropertyPath& Path, TSet<FPropertyPath>& OutPaths) const;`
- L34 _private member_ `TWeakPtr<FInstanceDataObjectFixupPanel> DiffPanel;`

#### enum `FInstanceDataObjectNameWidgetOverride::ENameWidgetIndex`  
`enum ENameWidgetIndex : uint8`  
_L36-40_
- L38 _public enumerator_ `DisplayRegularName = 0`
- L39 _public enumerator_ `DisplayRedirectMenu = 1`

#### Free symbols / members of external scopes

- L14 _macro_ `#define UE_API INSTANCEDATAOBJECTFIXUPTOOL_API`

### `Plugins/Experimental/InstanceDataObjectFixupTool/Source/Private/InstanceDataObjectFixupPanel.h` (Private)


#### class `FInstanceDataObjectFixupPanel`  
`class FInstanceDataObjectFixupPanel : public TSharedFromThis<FInstanceDataObjectFixupPanel>`  
_L13-76_
- inherits: `TSharedFromThis<FInstanceDataObjectFixupPanel>`
- L30 _public prototype_ `FInstanceDataObjectFixupPanel(const TObjectPtr<UObject>& InstanceDataObject, EViewFlags ViewFlags, const TWeakPtr<TMap<FTopLevelAssetPath, UE::FInstanceDataTransformSet>>& StagedTransforms);`
- L32 _public prototype_ `void RefreshDetailsView();`
- L33 _public prototype_ `TSharedPtr<IDetailsView>& GenerateDetailsView(bool bScrollbarOnLeft = false);`
- L35 _public prototype_ `void SetDiffAgainstLeft(const TSharedPtr<FAsyncDetailViewDiff>& DiffAgainstLeft);`
- L36 _public prototype_ `void SetDiffAgainstRight(const TSharedPtr<FAsyncDetailViewDiff>& DiffAgainstRight);`
- L37 _public prototype_ `TSharedPtr<FAsyncDetailViewDiff> GetDiffAgainstLeft() const;`
- L38 _public prototype_ `TSharedPtr<FAsyncDetailViewDiff> GetDiffAgainstRight() const;`
- L40 _public prototype_ `bool AreAllConflictsRedirected() const;`
- L42 _public prototype_ `void MarkForDelete(const FPropertyPath& Path);`
- L44 _public prototype_ `void OnMarkForDelete(FPropertyPath Path);` — pass-by-copy version for delegates. Use MarkForDelete when possible
- L46 _public prototype_ `void AutoApplyMarkDeletedActions();` — mark all conflicted properties for delete (FixupMode only)
- L49 _public prototype_ `bool PropertyNeedsRedirect(const FPropertyPath& Path) const;` — returns true if the provided path is an unknown property that needs to be redirected via IDT
- L51 _public prototype_ `bool HasViewFlag(EViewFlags Flag);`
- L54 _public member_ `TSharedPtr<IDetailsView> DetailsView;` — Initialized by SInstanceDataObjectFixupTool
- L55 _public member_ `TSharedPtr<SLinkableScrollBar> LinkableScrollBar;`
- L61 _private prototype_ `UE::FInstanceDataTransformSet* GetStagedTransformsForStruct(UStruct* ClassOrStruct);`
- L63 _private prototype_ `void RedirectProperty(const FPropertyPath& From, const FPropertyPath& To);`
- L65 _private prototype_ `bool CanConvert(const FPropertyPath& SourcePropertyPath, FProperty* DestinationProperty);`
- L68 _private prototype_ `void OnRedirectProperty(FPropertyPath From, FPropertyPath To);` — pass-by-copy version for delegates. Use RedirectProperty when possible
- L70 _private member_ `TObjectPtr<UObject> InstanceDataObject;`
- L72 _private member_ `TWeakPtr<FAsyncDetailViewDiff> DiffAgainstLeft;`
- L73 _private member_ `TWeakPtr<FAsyncDetailViewDiff> DiffAgainstRight;`
- L74 _private member_ `EViewFlags ViewFlags = EViewFlags::None;`
- L75 _private member_ `TWeakPtr<TMap<FTopLevelAssetPath, UE::FInstanceDataTransformSet>> StagedTransforms;`

#### enum `FInstanceDataObjectFixupPanel::EViewFlags`  
`enum class EViewFlags : uint8`  
_L16-28_
- L18 _public enumerator_ `None = 0`
- L19 _public enumerator_ `HideLooseProperties = (1 << 0)` — hide properties with isLoose metadata set to true
- L20 _public enumerator_ `IncludeOnlySetBySerialization = (1 << 1)` — hide properties that weren't set by serialization
- L21 _public enumerator_ `ReadonlyValues = (1 << 2)`
- L22 _public enumerator_ `AllowRemapLooseProperties = (1 << 3)`
- L25 _public enumerator_ `DefaultLeftPanel = IncludeOnlySetBySerialization | AllowRemapLooseProperties | ReadonlyValues` — displays only properties found in the property bag, allow remapping, and disallow value edits
- L27 _public enumerator_ `DefaultRightPanel = HideLooseProperties` — display only properties found in latest version of the class but allow value edits

### `Plugins/Experimental/InstanceDataObjectFixupTool/Source/Private/InstanceDataObjectFixupToolTedsQueries.h` (Private)


#### class `UInstanceDataObjectFixupToolTedsQueryFactory`  
`class UInstanceDataObjectFixupToolTedsQueryFactory : public UEditorDataStorageFactory`  
_L12-25_
- reflection: `UCLASS()`
- inherits: `UEditorDataStorageFactory`
- L17 _public prototype_ `~UInstanceDataObjectFixupToolTedsQueryFactory() override = default;`
- L19 _public prototype_ `void RegisterQueries(UE::Editor::DataStorage::ICoreProvider& DataStorage) override;`
- L22 _private prototype_ `static void ShowFixUpToolForPlaceholders(UE::Editor::DataStorage::RowHandle Row);`
- L23 _private prototype_ `static void ShowFixUpToolForLooseProperties(UE::Editor::DataStorage::RowHandle Row);`
- L24 _private prototype_ `static void ShowFixUpTool(UE::Editor::DataStorage::RowHandle Row, bool bRecurseIntoObject);`

### `Plugins/Experimental/InstanceDataObjectFixupTool/Source/Public/DataRecoveryTool.h` (Public)


#### class `SDataRecoveryTool`  
`class SDataRecoveryTool : public SCompoundWidget`  
_L30-75_
- inherits: `SCompoundWidget`
- L33 _public function_ `SLATE_BEGIN_ARGS(SDataRecoveryTool)`
- L35 _public prototype_ `SLATE_ARGUMENT(TOptional<FTopLevelAssetPath>, SelectedClassPath) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L40 _public prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;`
- L42 _public prototype_ `void SetDockTab(const TSharedRef<SDockTab>& DockTab);`
- L46 _private prototype_ `TSharedRef<SWidget> MakeTopBar();`
- L48 _private prototype_ `TSharedRef<SWidget> MakePanel(const FText& InTitle, const TSharedRef<SWidget>& InContent, const TOptional<FOnGetContent>& InMenuContent = TOptional<FOnGetContent>{});`
- L51 _private prototype_ `TSharedRef<SWidget> MakeClassesPanel();`
- L52 _private prototype_ `TSharedRef<SWidget> MakeTEDSTableViewer();`
- L53 _private prototype_ `void OnListSelectionChanged(UE::Editor::DataStorage::RowHandle RowItem, ESelectInfo::Type Info);`
- L55 _private prototype_ `void SetSelectedClass();`
- L57 _private prototype_ `TSharedRef<SWidget> MakeRightPanel();`
- L59 _private prototype_ `TSharedRef<SWidget> MakeDiffSection();`
- L61 _private prototype_ `FReply OnApplyClicked() const;`
- L62 _private prototype_ `FReply OnSaveAndApplyClicked() const;`
- L64 _private member_ `TWeakPtr<SDockTab> OwningDockTab;`
- L66 _private member_ `TSharedPtr<FTopLevelAssetPath> SelectedClassPath;`
- L68 _private member_ `TSharedPtr<TMap<FTopLevelAssetPath, UE::FInstanceDataTransformSet>> StagedTransforms;`
- L70 _private member_ `TSharedPtr<UE::Editor::DataStorage::STedsTableViewer> ClassesTableViewer;`
- L72 _private member_ `TSharedPtr<UE::Editor::DataStorage::QueryStack::IRowNode> ReferenceQueryResultsNode;`
- L74 _private member_ `TSharedPtr<SInstanceDataObjectFixupTool> DiffView;`

#### Free symbols / members of external scopes

- L14 _macro_ `#define UE_API INSTANCEDATAOBJECTFIXUPTOOL_API`
- L19 _namespace_ `namespace UE`
- L21 _namespace_ `namespace Editor` (scope `UE`)
- L21 _namespace_ `namespace DataStorage` (scope `UE::Editor`)
- L21 _namespace_ `namespace QueryStack` (scope `UE::Editor::DataStorage`)

### `Plugins/Experimental/InstanceDataObjectFixupTool/Source/Public/InstanceDataObjectFixupTool.h` (Public)


#### class `SInstanceDataObjectFixupTool`  
`class SInstanceDataObjectFixupTool : public SCompoundWidget`  
_L26-73_
- inherits: `SCompoundWidget`
- desc: This tool diffs multiple property bags of one format against the same number of property bags of another format.
- L29 _public typedef_ `using FStagedTransformMap = TMap<FTopLevelAssetPath, UE::FInstanceDataTransformSet>;`
- L31 _public function_ `SLATE_BEGIN_ARGS(SInstanceDataObjectFixupTool)`
- L33 _public prototype_ `SLATE_ARGUMENT(TWeakPtr<FTopLevelAssetPath>, SelectedClassPath) SLATE_ARGUMENT(TWeakPtr<FStagedTransformMap>, StagedTransforms) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L40 _public prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;`
- L42 _public prototype_ `void SetDockTab(const TSharedRef<SDockTab>& DockTab);`
- L43 _public prototype_ `void GenerateDetailsViews();`
- L44 _public prototype_ `static FLinearColor GetRowHighlightColor(const TUniquePtr<FAsyncDetailViewDiff::DiffNodeType>& DiffNode);`
- L45 _public prototype_ `bool IsResolved() const;`
- L48 _private prototype_ `void ResetDiff();`
- L49 _private prototype_ `TObjectPtr<UObject> CreateInstanceDataObjectSnapshot();`
- L51 _private prototype_ `FReply OnAutoMarkForDeletion() const;`
- L52 _private prototype_ `bool CanAutoMarkForDeletion() const;`
- L54 _private prototype_ `TSharedRef<SWidget> MakeDiffViewPanel();`
- L56 _private prototype_ `FReply OnResetInstanceDataObjectSnapshot();`
- L57 _private prototype_ `bool CanResetInstanceDataObjectSnapshot() const;`
- L59 _private prototype_ `UE::FInstanceDataTransformSet* GetSelectedStagedTransforms() const;`
- L61 _private member_ `TWeakPtr<SDockTab> OwningDockTab;`
- L62 _private member_ `TStaticArray<TSharedPtr<FInstanceDataObjectFixupPanel>, 2> Panels;`
- L63 _private member_ `TSharedPtr<FAsyncDetailViewDiff> PanelDiff;`
- L65 _private member_ `TSharedPtr<SDetailsSplitter> Splitter;`
- L67 _private member_ `TWeakPtr<TMap<FTopLevelAssetPath, UE::FInstanceDataTransformSet>> StagedTransforms;`
- L69 _private member_ `TSharedPtr<SBorder> Border;`
- L70 _private member_ `TWeakPtr<FTopLevelAssetPath> SelectedClassPath;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API INSTANCEDATAOBJECTFIXUPTOOL_API`
- L17 _namespace_ `namespace UE`

### `Plugins/Experimental/InstanceDataObjectFixupTool/Source/Public/InstanceDataObjectFixupToolModule.h` (Public)


#### class `FInstanceDataObjectFixupToolModule`  
`class FInstanceDataObjectFixupToolModule : public FDefaultModuleImpl`  
_L9-29_
- inherits: `FDefaultModuleImpl`
- L12 _public prototype_ `virtual void StartupModule() override;`
- L13 _public prototype_ `virtual void ShutdownModule() override;`
- L15 _public function_ `static FInstanceDataObjectFixupToolModule& Get()`
- L20 _public prototype_ `void CreateDataRecoveryToolDialog(const TOptional<FTopLevelAssetPath>& ClassPath) const;`
- L22 _public prototype_ `void RegisterTabSpawners(const TOptional<FTopLevelAssetPath>& ClassPath = {}) const;`
- L23 _public prototype_ `void UnregisterTabSpawners() const;`
- L26 _private prototype_ `TSharedRef<SDockTab> CreateDataRecoveryToolTab(const TOptional<FTopLevelAssetPath>& ClassPath = {}) const;`
- L28 _private prototype_ `bool IsDataRecoveryToolEnabled() const;`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API INSTANCEDATAOBJECTFIXUPTOOL_API`
