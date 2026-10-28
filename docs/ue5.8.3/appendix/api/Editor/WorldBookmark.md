# Editor / WorldBookmark

- module root: `Source/Editor/WorldBookmark`
- headers: 19; symbols: 416
- symbol kinds: class=16, delegate=4, enum=2, enumerator=4, externvar=6, function=34, member=85, namespace=31, prototype=223, struct=5, typedef=6
- PrivateDependencyModuleNames: ApplicationCore, AssetDefinition, AssetRegistry, AssetTools, ContentBrowser, ContentBrowserData, Core, CoreUObject, DeveloperSettings, EditorConfig, EditorSubsystem, Engine, InputCore, Json, JsonUtilities, LevelEditor, Projects, PropertyEditor, SceneOutliner, Slate, SlateCore, SourceControl, ToolMenus, ToolWidgets, UncontrolledChangelists, UnrealEd, WorkspaceMenuStructure

### `Source/Editor/WorldBookmark/Private/WorldBookmark/AssetDefinition_WorldBookmark.h` (Private)


#### class `UAssetDefinition_WorldBookmark`  
`class UAssetDefinition_WorldBookmark : public UAssetDefinitionDefault`  
_L12-36_
- reflection: `UCLASS()`
- inherits: `UAssetDefinitionDefault`
- L18 _public function_ `virtual FText GetAssetDisplayName() const override` — UAssetDefinition Begin
- L19 _public function_ `virtual FLinearColor GetAssetColor() const override`
- L20 _public function_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override`
- L21 _public function_ `virtual FAssetSupportResponse CanLocalize(const FAssetData& InAsset) const override`
- L23 _public function_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override`
- L29 _public function_ `virtual bool ShouldFindEditorForAsset() const override`
- L30 _public prototype_ `virtual EAssetCommandResult ActivateAssets(const FAssetActivateArgs& ActivateArgs) const override;`
- L31 _public prototype_ `virtual EAssetCommandResult OpenAssets(const FAssetOpenArgs& OpenArgs) const override;`
- L35 _private member_ `mutable bool bOpenFromContentBrowser = false;`

### `Source/Editor/WorldBookmark/Private/WorldBookmark/Browser/BookmarkTableRow.h` (Private)


#### class `UE::WorldBookmark::Browser::FWorldBookmarkTableRow`  
`class FWorldBookmarkTableRow : public SMultiColumnTableRow<FWorldBookmarkTreeItemPtr>, public FWorldBookmarkTableRowBase<FWorldBookmarkTreeItem>`  
_L15-36_
- inherits: `SMultiColumnTableRow<FWorldBookmarkTreeItemPtr>,FWorldBookmarkTableRowBase<FWorldBookmarkTreeItem>`
- L18 _public prototype_ `void Construct(const FArguments& InArgs, const TSharedRef<STableViewBase>& OwnerTable, FWorldBookmarkTreeItemRef InItem);`
- L20 _public prototype_ `virtual TSharedRef<SWidget> GenerateWidgetForColumn(const FName& ColumnName) override;`
- L22 _public prototype_ `TSharedRef<SWidget> GenerateLabelForTreeView();`
- L23 _public prototype_ `TSharedRef<SWidget> GenerateLabelForListView();`
- L25 _public prototype_ `FText GetLastAccessedText() const;`
- L26 _public prototype_ `EVisibility GetLastAccessedTextVisibility() const;`
- L28 _public prototype_ `FText GetWorldNameText() const;`
- L30 _public prototype_ `FLinearColor GetCategoryColor() const;`
- L31 _public prototype_ `FText GetCategoryText() const;`
- L33 _public prototype_ `FSlateColor GetIconColor() const;`
- L35 _public prototype_ `UWorldBookmark* GetBookmark() const;`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace WorldBookmark` (scope `UE`)
- L12 _namespace_ `namespace Browser` (scope `UE::WorldBookmark`)

### `Source/Editor/WorldBookmark/Private/WorldBookmark/Browser/BookmarkTreeItem.h` (Private)


#### struct `UE::WorldBookmark::Browser::FWorldBookmarkTreeItem`  
`struct FWorldBookmarkTreeItem : public ITreeItem`  
_L11-40_
- inherits: `ITreeItem`
- L14 _public function_ `FWorldBookmarkTreeItem(const FAssetData& InBookmarkAsset) : ITreeItem(Type) , BookmarkAsset(InBookmarkAsset)`
- L21 _public member_ `static const ETreeItemType Type;` — Static type identifier for this tree item class
- L23 _public member_ `FAssetData BookmarkAsset;`
- L25 _public prototype_ `virtual FName GetName() const override;`
- L26 _public prototype_ `virtual FName GetAssetName() const override;`
- L27 _public prototype_ `virtual bool CanRename() const override;`
- L28 _public prototype_ `virtual bool TryRename(FName InNewName, FText& OutErrorMessage) const override;`
- L29 _public prototype_ `virtual bool Rename(FName InNewName) override;`
- L30 _public prototype_ `virtual bool Delete() override;`
- L31 _public prototype_ `virtual FName GetIconName() const override;`
- L32 _public prototype_ `virtual FText GetText() const override;`
- L33 _public prototype_ `virtual FText GetTooltipText() const override;`
- L34 _public prototype_ `virtual void ShowInContentBrowser() const override;`
- L36 _public prototype_ `const FSoftObjectPath& GetBookmarkWorld() const;`
- L39 _private member_ `mutable FSoftObjectPath CachedBookmarkWorld;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace WorldBookmark` (scope `UE`)
- L8 _namespace_ `namespace Browser` (scope `UE::WorldBookmark`)
- L42 _typedef_ `typedef TSharedPtr<FWorldBookmarkTreeItem> FWorldBookmarkTreeItemPtr;` (scope `UE::WorldBookmark::Browser`)
- L43 _typedef_ `typedef TSharedRef<FWorldBookmarkTreeItem> FWorldBookmarkTreeItemRef;` (scope `UE::WorldBookmark::Browser`)

### `Source/Editor/WorldBookmark/Private/WorldBookmark/Browser/Columns.h` (Private)


#### struct `UE::WorldBookmark::Browser::Columns::FColumnDefinition`  
`struct FColumnDefinition`  
_L10-15_
- L12 _public member_ `FName Id;`
- L13 _public member_ `FText DisplayText;`
- L14 _public member_ `FText ToolTipText;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace WorldBookmark` (scope `UE`)
- L8 _namespace_ `namespace Browser` (scope `UE::WorldBookmark`)
- L8 _namespace_ `namespace Columns` (scope `UE::WorldBookmark::Browser`)
- L17 _externvar_ `extern const FColumnDefinition Favorite;` (scope `UE::WorldBookmark::Browser::Columns`)
- L18 _externvar_ `extern const FColumnDefinition RecentlyUsed;` (scope `UE::WorldBookmark::Browser::Columns`)
- L19 _externvar_ `extern const FColumnDefinition Label;` (scope `UE::WorldBookmark::Browser::Columns`)
- L20 _externvar_ `extern const FColumnDefinition World;` (scope `UE::WorldBookmark::Browser::Columns`)
- L21 _externvar_ `extern const FColumnDefinition Category;` (scope `UE::WorldBookmark::Browser::Columns`)
- L23 _externvar_ `extern const TArray<FName> DefaultHiddenColumns;` (scope `UE::WorldBookmark::Browser::Columns`)

### `Source/Editor/WorldBookmark/Private/WorldBookmark/Browser/CommonTableRow.h` (Private)


#### class `UE::WorldBookmark::Browser::FWorldBookmarkTableRowBase`  
`template <class TItemType = ITreeItem> class FWorldBookmarkTableRowBase`  
_L20-167_
- L23 _public function_ `TSharedPtr<TItemType> GetTreeItem() const`
- L36 _public function_ `FText GetText() const`
- L46 _public function_ `FText GetTooltipText() const`
- L56 _public function_ `const FSlateBrush* GetIcon() const`
- L66 _public function_ `FSlateColor GetIconColor() const`
- L71 _public function_ `FSimpleDelegate& GetRenameRequestedDelegate()`
- L76 _public function_ `bool IsReadOnly() const`
- L86 _public function_ `bool OnLabelTextVerifyChanged(const FText& InNewText, FText& OutErrorMessage)`
- L99 _public function_ `void OnLabelTextCommitted(const FText& InNewText, ETextCommit::Type InTextCommit)`
- L113 _public function_ `void OnEnterEditingMode()`
- L121 _public function_ `void OnExitEditingMode()`
- L129 _public function_ `FReply OnRowDragDetected(const FGeometry& Geometry, const FPointerEvent& PointerEvent)`
- L143 _public function_ `TOptional<EItemDropZone> OnRowCanAcceptDrop(const FDragDropEvent& Event, EItemDropZone Zone, TSharedPtr<TItemType> Item)`
- L154 _public function_ `FReply OnRowAcceptDrop(const FDragDropEvent& Event, EItemDropZone Zone, TSharedPtr<TItemType> Item)`
- L166 _protected member_ `TWeakPtr<TItemType> WeakTreeItem;`

#### Free symbols / members of external scopes

- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace WorldBookmark` (scope `UE`)
- L16 _namespace_ `namespace Browser` (scope `UE::WorldBookmark`)
- L170 _function_ `template <class TTableRow> TSharedRef<SWidget> CreateEditableLabelWidget(TSharedRef<TTableRow> TableRow)` (scope `UE::WorldBookmark::Browser`)
- L188 _function_ `template <class TTableRow> TSharedRef<SWidget> CreateTreeLabelWidget(TSharedRef<TTableRow> TableRow)` (scope `UE::WorldBookmark::Browser`)
- L221 _function_ `.Image_Lambda([TableRow] { return TableRow->GetIcon(); }) .ToolTipText(TableRow->GetTooltipText()) .ColorAndOpacity_Lambda([TableRow] { return TableRow->GetIconColor(); }) ] ] + SHorizontalBox::Slot() .FillWidth(1.0f) .VAlign(VAlign_Center) .Padding(0.0f, 0.0f) [ CreateEditableLabelWidget(TableRow) ] ] ];` (scope `UE::WorldBookmark::Browser::CreateTreeLabelWidget`)
- L223 _function_ `.ColorAndOpacity_Lambda([TableRow] { return TableRow->GetIconColor(); }) ] ] + SHorizontalBox::Slot() .FillWidth(1.0f) .VAlign(VAlign_Center) .Padding(0.0f, 0.0f) [ CreateEditableLabelWidget(TableRow) ] ] ];` (scope `UE::WorldBookmark::Browser::CreateTreeLabelWidget`)

### `Source/Editor/WorldBookmark/Private/WorldBookmark/Browser/DragDropOperation.h` (Private)


#### class `UE::WorldBookmark::Browser::FTableRowDragDropOp`  
`class FTableRowDragDropOp : public FDecoratedDragDropOp`  
_L12-22_
- inherits: `FDecoratedDragDropOp`
- L15 _public prototype_ `DRAG_DROP_OPERATOR_TYPE(FTableRowDragDropOp, FDecoratedDragDropOp) static TSharedPtr<FTableRowDragDropOp> New(FTreeItemPtr TreeItem);`
- L18 _public prototype_ `TOptional<EItemDropZone> CanAcceptDrop(FTreeItemPtr DropTarget) const;`
- L19 _public prototype_ `FReply AcceptDrop(FTreeItemPtr DropTarget) const;`
- L21 _public member_ `TWeakPtr<ITreeItem> DraggedItem;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace WorldBookmark` (scope `UE`)
- L9 _namespace_ `namespace Browser` (scope `UE::WorldBookmark`)

### `Source/Editor/WorldBookmark/Private/WorldBookmark/Browser/FolderTableRow.h` (Private)


#### class `UE::WorldBookmark::Browser::FFolderTableRow`  
`class FFolderTableRow : public STableRow<FFolderTreeItemPtr>, public FWorldBookmarkTableRowBase<FFolderTreeItem>`  
_L13-17_
- inherits: `STableRow<FFolderTreeItemPtr>,FWorldBookmarkTableRowBase<FFolderTreeItem>`
- L16 _public prototype_ `void Construct(const FArguments& InArgs, const TSharedRef<STableViewBase>& InOwnerTableView, FFolderTreeItemRef InItem);`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace WorldBookmark` (scope `UE`)
- L10 _namespace_ `namespace Browser` (scope `UE::WorldBookmark`)

### `Source/Editor/WorldBookmark/Private/WorldBookmark/Browser/FolderTreeItem.h` (Private)


#### struct `UE::WorldBookmark::Browser::FFolderTreeItem`  
`struct FFolderTreeItem : public ITreeItem`  
_L9-90_
- inherits: `ITreeItem`
- L13 _public member_ `static const ETreeItemType Type;` — Static type identifier for this tree item class
- L15 _public prototype_ `FFolderTreeItem(const FName InName = NAME_None);`
- L17 _public prototype_ `virtual FName GetName() const override;`
- L18 _public prototype_ `virtual FName GetAssetName() const override;`
- L19 _public prototype_ `virtual bool CanRename() const override;`
- L20 _public prototype_ `virtual bool TryRename(FName InNewName, FText& OutErrorMessage) const override;`
- L21 _public prototype_ `virtual bool Rename(FName InNewName) override;`
- L22 _public prototype_ `virtual bool Delete() override;`
- L23 _public prototype_ `virtual FName GetIconName() const override;`
- L24 _public prototype_ `virtual FText GetText() const override;`
- L25 _public prototype_ `virtual FText GetTooltipText() const override;`
- L26 _public prototype_ `virtual void ShowInContentBrowser() const override;`
- L28 _public prototype_ `const TArray<FTreeItemPtr>& GetChildren() const;`
- L29 _public prototype_ `void AddChild(FTreeItemPtr InChildItem);`
- L31 _public prototype_ `TSharedPtr<FFolderTreeItem> CreateMountPoint(const FString& InPath, const FString& InMountPointName);`
- L32 _public prototype_ `TSharedPtr<FFolderTreeItem> CreatePath(const FString& InPath);`
- L33 _public prototype_ `void ExpandPath(FName InPath) const;`
- L35 _public prototype_ `bool IsExpanded() const;`
- L36 _public prototype_ `void SetExpanded(bool bInExpanded);`
- L38 _public prototype_ `bool IsVirtual() const;`
- L39 _public prototype_ `bool IsMountPoint() const;`
- L41 _public prototype_ `void Sort(TFunctionRef<bool(const FTreeItemPtr&, const FTreeItemPtr&)> SortFunc);`
- L43 _public prototype_ `void Reset();`
- L45 _public prototype_ `void ClearBookmarkItems();`
- L46 _public prototype_ `bool ClearEmptyFolders();`
- L48 _public prototype_ `bool Move(FTreeItemPtr NewChild);`
- L51 _public function_ `template <typename T> void ForEachChild(TFunctionRef<void(TSharedPtr<T>)> InFunc)`
- L63 _public function_ `template <typename T> void ForEachChildRecursive(TFunctionRef<void(TSharedPtr<T>)> InFunc)`
- L80 _private prototype_ `TSharedPtr<FFolderTreeItem> CreatePath(const FString& InPath, bool bIsCreatingMountPoint);`
- L81 _private prototype_ `TSharedPtr<FFolderTreeItem> CreatePath(const TArrayView<FName>& InPath, bool bIsCreatingMountPoint);`
- L82 _private prototype_ `void ExpandPath(const TArrayView<FName>& InPath) const;`
- L84 _private member_ `FName Name;`
- L85 _private member_ `FName MountPointName;`
- L86 _private member_ `bool bIsExpanded;`
- L87 _private member_ `bool bIsVirtual;`
- L88 _private member_ `bool bIsMountPoint;`
- L89 _private member_ `TArray<FTreeItemPtr> Children;`

#### Free symbols / members of external scopes

- L6 _namespace_ `namespace UE`
- L6 _namespace_ `namespace WorldBookmark` (scope `UE`)
- L6 _namespace_ `namespace Browser` (scope `UE::WorldBookmark`)
- L92 _typedef_ `typedef TSharedPtr<FFolderTreeItem> FFolderTreeItemPtr;` (scope `UE::WorldBookmark::Browser`)
- L93 _typedef_ `typedef TSharedRef<FFolderTreeItem> FFolderTreeItemRef;` (scope `UE::WorldBookmark::Browser`)

### `Source/Editor/WorldBookmark/Private/WorldBookmark/Browser/Icons.h` (Private)


#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace WorldBookmark` (scope `UE`)
- L9 _namespace_ `namespace Browser` (scope `UE::WorldBookmark`)
- L11 _prototype_ `FSlateIcon GetFavoriteWorldBookmarkIcon(bool bIsFavorite);` (scope `UE::WorldBookmark::Browser`)
- L12 _prototype_ `FSlateIcon GetRecentlyUsedWorldBookmarkIcon();` (scope `UE::WorldBookmark::Browser`)
- L13 _prototype_ `FSlateIcon GetFolderIcon(bool bIsExpanded);` (scope `UE::WorldBookmark::Browser`)
- L14 _prototype_ `FSlateIcon GetWorldBookmarkIcon();` (scope `UE::WorldBookmark::Browser`)
- L15 _prototype_ `TSharedRef<SWidget> CreateIconWidget(const FSlateIcon& SlateIcon, const FText& ToolTip = FText());` (scope `UE::WorldBookmark::Browser`)

### `Source/Editor/WorldBookmark/Private/WorldBookmark/Browser/SWorldBookmarkBrowser.h` (Private)


#### class `UE::WorldBookmark::Browser::SWorldBookmarkBrowser`  
`class SWorldBookmarkBrowser : public SCompoundWidget`  
_L21-141_
- inherits: `SCompoundWidget`
- L24 _public function_ `SLATE_BEGIN_ARGS(SWorldBookmarkBrowser)`
- L28 _public prototype_ `SWorldBookmarkBrowser();`
- L29 _public prototype_ `virtual ~SWorldBookmarkBrowser();`
- L31 _public prototype_ `void Construct(const FArguments& InArgs);`
- L35 _private prototype_ `void OnGetChildren(FTreeItemPtr InItem, TArray<FTreeItemPtr>& OutChildren);`
- L36 _private prototype_ `TSharedRef<ITableRow> OnGenerateRow(FTreeItemPtr InTreeItem, const TSharedRef<STableViewBase>& OwnerTable);`
- L37 _private prototype_ `void OnSelectionChanged(FTreeItemPtr InTreeItem, ESelectInfo::Type SelectionType);`
- L38 _private prototype_ `void OnMouseButtonDoubleClicked(FTreeItemPtr InTreeItem);`
- L39 _private prototype_ `TSharedPtr<SWidget> OnContextMenuOpening();`
- L40 _private prototype_ `void OnItemScrolledIntoView(FTreeItemPtr WorldBookmarkTreeItem, const TSharedPtr<ITableRow>& Widget);`
- L43 _private prototype_ `FReply OnCreateNewWorldBookmarkClicked();`
- L44 _private prototype_ `void OnSearchBoxTextChanged(const FText& InSearchText);`
- L45 _private prototype_ `void OnColumnSortChanged(const EColumnSortPriority::Type SortPriority, const FName& ColumnId, const EColumnSortMode::Type InSortMode);`
- L46 _private prototype_ `TSharedRef<SWidget> GetSettingsMenuContent();`
- L49 _private prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;` — SWidget interface
- L50 _private prototype_ `virtual FReply OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent) override;`
- L52 _private prototype_ `void RefreshItems(bool bForceRefresh = false);`
- L53 _private prototype_ `void SortItems();`
- L55 _private prototype_ `void RecreateColumns();`
- L56 _private prototype_ `EColumnSortMode::Type GetColumnSortMode(const FName ColumnId) const;`
- L57 _private prototype_ `EColumnSortPriority::Type GetColumnSortPriority(const FName InColumnId) const;`
- L58 _private prototype_ `TArray<FAssetViewCustomColumn> GetCustomColumns() const;`
- L60 _private prototype_ `void OnAssetsAdded(TConstArrayView<FAssetData> InAssets);`
- L61 _private prototype_ `void OnAssetRemoved(const FAssetData& InAssetData);`
- L62 _private prototype_ `void OnAssetRenamed(const FAssetData& InAssetData, const FString& InOldObjectPath);`
- L63 _private prototype_ `void OnAssetUpdated(const FAssetData& InAssetData);`
- L64 _private prototype_ `void OnAssetUpdatedOnDisk(const FAssetData& InAssetData);`
- L65 _private prototype_ `void OnObjectPropertyChanged(UObject* InObject, FPropertyChangedEvent& InPropertyChangedEvent);`
- L66 _private prototype_ `void OnObjectPreSave(UObject* InObject, FObjectPreSaveContext InObjectPreSaveContext);`
- L68 _private prototype_ `void OnMapChanged(UWorld* World, EMapChangeType MapChangeType);`
- L70 _private prototype_ `void OnSettingsChanged();`
- L72 _private prototype_ `void OnUncontrolledChangelistModuleChanged();`
- L74 _private prototype_ `FTreeItemPtr GetSelectedTreeItem() const;`
- L75 _private prototype_ `FWorldBookmarkTreeItemPtr GetSelectedBookmarkTreeItem() const;`
- L76 _private prototype_ `UWorldBookmark* GetSelectedBookmark() const;`
- L77 _private prototype_ `void SetSelectedBookmark(UWorldBookmark* InBookmark);`
- L78 _private prototype_ `bool IsValidBookmarkSelected() const;`
- L79 _private prototype_ `bool IsValidItemSelected() const;`
- L81 _private prototype_ `bool CanExecuteBookmarkAction() const;`
- L83 _private prototype_ `void LoadSelectedBookmark();`
- L84 _private prototype_ `void UpdateSelectedBookmark();`
- L86 _private prototype_ `bool IsSelectedBookmarkFavorite() const;`
- L87 _private prototype_ `bool IsSelectedBookmarkNotFavorite() const;`
- L88 _private prototype_ `void AddSelectedBookmarkToFavorites();`
- L89 _private prototype_ `void RemoveSelectedBookmarkFromFavorites();`
- L91 _private prototype_ `void FindSelectedItemInContentBrowser();`
- L92 _private prototype_ `void RequestRenameSelectedItem();`
- L94 _private prototype_ `bool CanRenameOrDeleteSelectedItem() const;`
- L95 _private prototype_ `void DeleteSelectedItem();`
- L97 _private prototype_ `bool CanGoToSelectedBookmarkLocation() const;`
- L98 _private prototype_ `void PlayFromSelectedBookmarkLocation();`
- L99 _private prototype_ `void GoToSelectedBookmarkLocation();`
- L101 _private prototype_ `void UpdateDetailsView(UWorldBookmark* InSelectedWorldBookmark);`
- L103 _private prototype_ `void OnItemExpansionChanged(FTreeItemPtr InTreeItem, bool bIsExpanded);`
- L104 _private prototype_ `void SetItemExpansionRecursive(FTreeItemPtr InTreeItem, bool bIsExpanded);`
- L106 _private prototype_ `void MoveSelectedBookmarkToNewFolder();`
- L107 _private prototype_ `void CreateBookmarkInSelectedFolder();`
- L109 _private prototype_ `bool AskForWorldChangeConfirmation(UWorldBookmark* WorldBookmark) const;`
- L112 _private member_ `FDelegateHandle OnAssetAddedHandle;`
- L113 _private member_ `FDelegateHandle OnAssetRemovedHandle;`
- L114 _private member_ `FDelegateHandle OnAssetRenamedHandle;`
- L115 _private member_ `FDelegateHandle OnAssetUpdatedHandle;`
- L116 _private member_ `FDelegateHandle OnAssetUpdatedOnDiskHandle;`
- L117 _private member_ `FDelegateHandle OnObjectPropertyChangedHandle;`
- L118 _private member_ `FDelegateHandle OnMapChangedHandle;`
- L119 _private member_ `FDelegateHandle OnSettingsChangedHandle;`
- L120 _private member_ `FDelegateHandle OnUncontrolledChangelistModuleChangedHandle;`
- L122 _private member_ `FFolderTreeItemPtr TreeRoot;`
- L123 _private member_ `TMap<FName, FWorldBookmarkTreeItemPtr> BookmarkTreeItems;`
- L125 _private member_ `TSharedPtr<SHeaderRow> HeaderRow;`
- L126 _private member_ `TSharedPtr<STreeView<FTreeItemPtr>> BookmarksView;`
- L127 _private member_ `TSharedPtr<IDetailsView> PropertyView;`
- L128 _private member_ `TSharedPtr<SVerticalBox> DetailsBox;`
- L130 _private member_ `TSharedPtr<FUICommandList> Commands;`
- L132 _private member_ `TPair<FName, EColumnSortMode::Type> ColumnsSortingParams[EColumnSortPriority::Max];`
- L134 _private member_ `FText CurrentSearchString;`
- L136 _private member_ `FTreeItemPtr TreeItemPendingRename;`
- L138 _private member_ `bool bIsInTick;`
- L139 _private member_ `bool bPendingRefresh;`
- L140 _private member_ `bool bExpandAllItemsOnNextRefresh;`

#### Free symbols / members of external scopes

- L18 _namespace_ `namespace UE`
- L18 _namespace_ `namespace WorldBookmark` (scope `UE`)
- L18 _namespace_ `namespace Browser` (scope `UE::WorldBookmark`)

### `Source/Editor/WorldBookmark/Private/WorldBookmark/Browser/Settings.h` (Private)


#### enum `EWorldBookmarkBrowserViewMode`  
`enum class EWorldBookmarkBrowserViewMode : uint8`  
_L9-13_
- reflection: `UENUM()`
- L11 _public enumerator_ `ListView`
- L12 _public enumerator_ `TreeView`

#### class `UWorldBookmarkBrowserSettings`  
`class UWorldBookmarkBrowserSettings : public UEditorConfigBase`  
_L16-76_
- reflection: `UCLASS(EditorConfig = "WorldBookmarkBrowser")`
- inherits: `UEditorConfigBase`
- L21 _public prototype_ `DECLARE_MULTICAST_DELEGATE(FWorldBookmarkBrowserSettingChanged) static FWorldBookmarkBrowserSettingChanged& OnSettingsChanged();`
- L25 _public prototype_ `static bool GetShowOnlyBookmarksForCurrentWorld();`
- L26 _public prototype_ `static void ToggleShowOnlyBookmarksForCurrentWorld();`
- L28 _public prototype_ `static bool GetShowOnlyUncontrolledBookmarks();`
- L29 _public prototype_ `static void ToggleShowOnlyUncontrolledBookmarks();`
- L31 _public prototype_ `static bool GetShowOnlyFavoriteBookmarks();`
- L32 _public prototype_ `static void ToggleShowOnlyFavoriteBookmarks();`
- L34 _public prototype_ `static bool GetShowOnlyLastRecentlyUsedBookmarks();`
- L35 _public prototype_ `static void ToggleShowOnlyLastRecentlyUsedBookmarks();`
- L37 _public prototype_ `static TArray<FName> GetHiddenColumns();`
- L38 _public prototype_ `static void SetHiddenColumns(const TArray<FName>& InHiddenColumns);`
- L40 _public prototype_ `static int32 GetMaxLastRecentlyUsedItems();`
- L41 _public prototype_ `static void SetMaxLastRecentlyUsedItems(int32 InMaxLastRecentlyUsedItems);`
- L43 _public prototype_ `static EWorldBookmarkBrowserViewMode GetViewMode();`
- L44 _public prototype_ `static bool IsViewMode(EWorldBookmarkBrowserViewMode InViewMode);`
- L45 _public prototype_ `static void SetViewMode(EWorldBookmarkBrowserViewMode InViewMode);`
- L48 _private prototype_ `static UWorldBookmarkBrowserSettings& Get();`
- L50 _private prototype_ `void ApplySettingsChanges();`
- L53 _private member_ `bool bShowOnlyBookmarksForCurrentWorld = true;` — `UPROPERTY(meta=(EditorConfig))`
- L56 _private member_ `bool bShowOnlyUncontrolledBookmarks = false;` — `UPROPERTY(meta=(EditorConfig))`
- L59 _private member_ `bool bShowOnlyFavoriteBookmarks = false;` — `UPROPERTY(meta=(EditorConfig))`
- L62 _private member_ `bool bShowOnlyLastRecentlyUsedBookmarks = false;` — `UPROPERTY(meta=(EditorConfig))`
- L65 _private member_ `int32 MaxLastRecentlyUsedItems = 5;` — `UPROPERTY(meta=(EditorConfig))`
- L68 _private member_ `TArray<FName> HiddenColumns;` — `UPROPERTY(meta=(EditorConfig))`
- L71 _private member_ `EWorldBookmarkBrowserViewMode ViewMode;` — `UPROPERTY(meta=(EditorConfig))`
- L73 _private member_ `FWorldBookmarkBrowserSettingChanged OnSettingsChangedDelegate;`
- L75 _private member_ `static TObjectPtr<UWorldBookmarkBrowserSettings> Instance;`

#### Free symbols / members of external scopes

- L21 _delegate_ `DECLARE_MULTICAST_DELEGATE(FWorldBookmarkBrowserSettingChanged) static FWorldBookmarkBrowserSettingChanged& OnSettingsChanged();`

### `Source/Editor/WorldBookmark/Private/WorldBookmark/Browser/TreeItem.h` (Private)


#### enum `UE::WorldBookmark::Browser::ETreeItemType`  
`enum ETreeItemType`  
_L10-14_
- L12 _public enumerator_ `Folder`
- L13 _public enumerator_ `WorldBookmark`

#### struct `UE::WorldBookmark::Browser::ITreeItem`  
`struct ITreeItem : public TSharedFromThis<ITreeItem>`  
_L17-88_
- inherits: `TSharedFromThis<ITreeItem>`
- desc: Define a common base class for your items
- L22 _public function_ `template <typename T> T* Cast()` — Attempt to cast this item to another type if it is of that type. Returns nullptr if it fails
- L29 _public function_ `template <typename T> const T* Cast() const` — Attempt to cast this item to another type if it is of that type. Returns nullptr if it fails
- L36 _public function_ `template <typename T> bool IsA() const` — Returns true if this item is of the specified type
- L42 _public function_ `template <> bool IsA<ITreeItem>() const`
- L47 _public prototype_ `virtual FName GetName() const = 0;`
- L49 _public prototype_ `virtual FName GetAssetName() const = 0;`
- L51 _public prototype_ `virtual bool CanRename() const = 0;`
- L53 _public prototype_ `virtual bool TryRename(FName InNewName, FText& OutErrorMessage) const = 0;`
- L55 _public prototype_ `virtual bool Rename(FName InNewName) = 0;`
- L57 _public prototype_ `virtual bool Delete() = 0;`
- L59 _public prototype_ `virtual FName GetIconName() const = 0;`
- L61 _public prototype_ `virtual FText GetText() const = 0;`
- L63 _public prototype_ `virtual FText GetTooltipText() const = 0;`
- L65 _public prototype_ `virtual void ShowInContentBrowser() const = 0;`
- L67 _public member_ `bool bInEditingMode = false;`
- L70 _public prototype_ `DECLARE_DELEGATE(FOnRenameRequested);` — Delegate for when the context menu requests a rename
- L71 _public member_ `FOnRenameRequested OnRenameRequested;`
- L74 _public member_ `ETreeItemType TreeItemType;` — Tree item type identifier
- L76 _public prototype_ `ITreeItem* GetParent() const;`
- L78 _public prototype_ `void SetParent(ITreeItem* InParent);`
- L80 _public prototype_ `FString GetAssetPath() const;`
- L83 _private member_ `ITreeItem* ParentItem;`
- L86 _protected prototype_ `ITreeItem(ETreeItemType InType);`
- L87 _protected prototype_ `virtual ~ITreeItem();`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace WorldBookmark` (scope `UE`)
- L7 _namespace_ `namespace Browser` (scope `UE::WorldBookmark`)
- L70 _delegate_ `DECLARE_DELEGATE(FOnRenameRequested);` — Delegate for when the context menu requests a rename
- L90 _typedef_ `typedef TSharedPtr<ITreeItem> FTreeItemPtr;` (scope `UE::WorldBookmark::Browser`)
- L91 _typedef_ `typedef TSharedRef<ITreeItem> FTreeItemRef;` (scope `UE::WorldBookmark::Browser`)

### `Source/Editor/WorldBookmark/Private/WorldBookmark/WorldBookmarkCommands.h` (Private)


#### class `FWorldBookmarkCommands`  
`class FWorldBookmarkCommands : public TCommands<FWorldBookmarkCommands>`  
_L6-25_
- inherits: `TCommands<FWorldBookmarkCommands>`
- L9 _public prototype_ `FWorldBookmarkCommands();`
- L12 _public member_ `TSharedPtr<FUICommandInfo> LoadBookmark;` — Context Menu
- L13 _public member_ `TSharedPtr<FUICommandInfo> UpdateBookmark;`
- L14 _public member_ `TSharedPtr<FUICommandInfo> AddToFavorite;`
- L15 _public member_ `TSharedPtr<FUICommandInfo> RemoveFromFavorite;`
- L16 _public member_ `TSharedPtr<FUICommandInfo> PlayFromLocation;`
- L17 _public member_ `TSharedPtr<FUICommandInfo> MoveCameraToLocation;`
- L18 _public member_ `TSharedPtr<FUICommandInfo> MoveBookmarkToNewFolder;`
- L19 _public member_ `TSharedPtr<FUICommandInfo> CreateBookmarkInFolder;`
- L24 _public prototype_ `virtual void RegisterCommands() override;` — Initialize commands

### `Source/Editor/WorldBookmark/Private/WorldBookmark/WorldBookmarkDetailsCustomization.h` (Private)


#### class `FWorldBookmarkDetailsCustomization`  
`class FWorldBookmarkDetailsCustomization : public IDetailCustomization, public FEditorUndoClient`  
_L15-59_
- inherits: `IDetailCustomization,FEditorUndoClient`
- desc: UI customization for UWorldBookmark
- L18 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();`
- L20 _public prototype_ `FWorldBookmarkDetailsCustomization();`
- L21 _public prototype_ `~FWorldBookmarkDetailsCustomization();`
- L25 _protected prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;`
- L29 _protected prototype_ `virtual void PostUndo(bool bSuccess) override;` — FEditorUndoClient interface
- L30 _protected prototype_ `virtual void PostRedo(bool bSuccess) override;`
- L33 _protected prototype_ `void RefreshCustomDetail();`
- L36 _private prototype_ `TSharedRef<SWidget> MakeCategoryComboWidget(TSharedPtr<FWorldBookmarkCategory> InItem);`
- L38 _private prototype_ `void OnCategoryChanged(TSharedPtr<FWorldBookmarkCategory> NewSelection, ESelectInfo::Type SelectInfo);`
- L39 _private prototype_ `bool CreateNewCategory(FWorldBookmarkCategory& OutNewCategory);`
- L41 _private prototype_ `FLinearColor GetCategoryColor() const;`
- L42 _private prototype_ `EVisibility GetCategoryColorVisibility() const;`
- L43 _private prototype_ `FText GetCategoryText() const;`
- L45 _private prototype_ `void OnWorldBookmarkSettingsChanged(UObject* InSettings, FPropertyChangedEvent& InPropertyChangedEvent);`
- L47 _private prototype_ `void RefreshBookmarkCategoriesList();`
- L50 _private member_ `IDetailLayoutBuilder* CachedDetailBuilder;` — The detail builder for this cusomtomisation.
- L52 _private member_ `TArray<TSharedPtr<FWorldBookmarkCategory>> KnownCategories;`
- L53 _private member_ `TSharedPtr<SComboBox<TSharedPtr<FWorldBookmarkCategory>>> CategoriesComboBox;`
- L56 _private member_ `UWorldBookmark* WorldBookmark;` — The currently edited bookmark
- L58 _private member_ `FDelegateHandle OnWorldBookmarkEditorSettingsChangedHandle;`

#### class `FWorldBookmarkCategoryCustomization`  
`class FWorldBookmarkCategoryCustomization : public IPropertyTypeCustomization`  
_L62-75_
- inherits: `IPropertyTypeCustomization`
- desc: UI customization for FWorldBookmarkCategory
- L66 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance();` — Factory method to create an instance
- L69 _public prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> StructPropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& CustomizationUtils) override;` — IPropertyTypeCustomization overrides
- L70 _public prototype_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> StructPropertyHandle, IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& CustomizationUtils) override;`
- L72 _public prototype_ `const FWorldBookmarkCategory& GetEditedCategory() const;`
- L74 _public member_ `TSharedPtr<IPropertyHandle> CachedStructPropertyHandle;`

### `Source/Editor/WorldBookmark/Private/WorldBookmark/WorldBookmarkEditorSettings.h` (Private)


#### class `UWorldBookmarkEditorSettings`  
`class UWorldBookmarkEditorSettings : public UDeveloperSettings`  
_L13-33_
- reflection: `UCLASS(config = Editor, DefaultConfig, meta = (DisplayName = "World Bookmark"))`
- inherits: `UDeveloperSettings`
- L18 _public prototype_ `DECLARE_MULTICAST_DELEGATE(UWorldBookmarkEditorSettingsChanged) static FOnSettingsChanged& OnSettingsChanged();`
- L22 _public prototype_ `static const FWorldBookmarkCategory& GetCategory(const FGuid& InCategoryGuid);`
- L23 _public prototype_ `static void AddCategory(const FWorldBookmarkCategory& InCategory);`
- L25 _public prototype_ `static const TArray<FWorldBookmarkCategory>& GetCategories();`
- L28 _protected prototype_ `virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;`
- L32 _private member_ `TArray<FWorldBookmarkCategory> Categories;` — `UPROPERTY(config, EditAnywhere, Category = "Bookmark Categories", meta=(NoElementDuplicate, EditFixedOrder))`

#### class `UWorldBookmarkEditorPerProjectUserSettings`  
`class UWorldBookmarkEditorPerProjectUserSettings : public UDeveloperSettings`  
_L37-55_
- reflection: `UCLASS(config = EditorPerProjectUserSettings, meta = (DisplayName = "World Bookmark"))`
- inherits: `UDeveloperSettings`
- L42 _public prototype_ `UWorldBookmarkEditorPerProjectUserSettings();`
- L46 _public member_ `bool bEnableDefaultBookmarks;` — `UPROPERTY(config, EditAnywhere, Category="Default Level Bookmark")` — When enabled, the default bookmark will be applied when loading a level
- L50 _public member_ `bool bEnableHomeBookmark;` — `UPROPERTY(config, EditAnywhere, Category = "Home Bookmark")` — When enabled, the home bookmark will be applied when starting the editor without specifying a map
- L54 _public member_ `TSoftObjectPtr<UWorldBookmark> HomeBookmark;` — `UPROPERTY(config, EditAnywhere, Category = "Home Bookmark", meta = (EditCondition = "bEnableHomeBookmark"))` — Bookmark to be applied when starting the editor without specifying a map

#### Free symbols / members of external scopes

- L18 _delegate_ `DECLARE_MULTICAST_DELEGATE(UWorldBookmarkEditorSettingsChanged) static FOnSettingsChanged& OnSettingsChanged();`

### `Source/Editor/WorldBookmark/Private/WorldBookmark/WorldBookmarkFactory.h` (Private)


#### class `UWorldBookmarkFactory`  
`class UWorldBookmarkFactory : public UFactory`  
_L16-23_
- reflection: `UCLASS()`
- inherits: `UFactory`
- L21 _private prototype_ `virtual UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;`

### `Source/Editor/WorldBookmark/Private/WorldBookmark/WorldBookmarkModule.h` (Private)


#### class `FWorldBookmarkModule`  
`class FWorldBookmarkModule : public IModuleInterface`  
_L18-71_
- inherits: `IModuleInterface`
- desc: Module dedicated to the World Bookmark feature
- L24 _public prototype_ `virtual void StartupModule();` — Called right after the module DLL has been loaded and the module object has been created
- L29 _public prototype_ `virtual void ShutdownModule();` — Called before the module is unloaded, right before the module object is destroyed.
- L34 _public prototype_ `static FString CaptureToString();` — Capture a bookmark as a string, can be restored with RestoreFromString().
- L39 _public prototype_ `static void CaptureToClipboard();` — Capture a bookmark to the clipboard, can be restored with RestoreFromClipboard().
- L44 _public prototype_ `static bool RestoreFromString(const FString& InBookmarkAsString);` — Restore a bookmark from the provided string.
- L49 _public prototype_ `static bool RestoreFromClipboard();` — Restore a bookmark from the clipboard.
- L52 _private prototype_ `void RegisterWorldBookmarkBrowserTab(TSharedPtr<FTabManager> InTabManager);`
- L53 _private prototype_ `TSharedRef<SDockTab> SpawnWorldBookmarkBrowserTab(const FSpawnTabArgs& Args);`
- L54 _private prototype_ `TSharedRef<SWidget> CreateWorldBookmarkBrowser();`
- L56 _private prototype_ `void OnAddExtraObjectsToDelete(const TArray<UObject*>& InObjectsToDelete, TSet<UObject*>& OutSecondaryObjects);`
- L57 _private prototype_ `void OnMapChanged(UWorld* InWorld, EMapChangeType InMapChangeType);`
- L58 _private prototype_ `void OnDefaultBookmarkChanged(AWorldSettings* InWorldSettings);`
- L59 _private prototype_ `void OnEditorLoadDefaultStartupMap(FCanLoadMap& InOutCanLoadDefaultStartupMap);`
- L61 _private prototype_ `bool IsDefaultBookmarkValid(const AWorldSettings* InWorldSettings) const;`
- L62 _private prototype_ `void ShowInvalidDefaultBookmarkNotification(const FText& InNotificationTitle) const;`
- L64 _private member_ `FDelegateHandle OnAddExtraObjectsToDeleteDelegateHandle;`
- L65 _private member_ `FDelegateHandle OnMapChangedHandle;`
- L66 _private member_ `FDelegateHandle OnDefaultBookmarkChangedHandle;`
- L67 _private member_ `FDelegateHandle OnEditorLoadDefaultStartupMapHandle;`
- L69 _private member_ `TArray<FName> ClassesToUnregisterOnShutdown;`
- L70 _private member_ `TArray<FName> StructsToUnregisterOnShutdown;`

### `Source/Editor/WorldBookmark/Private/WorldBookmark/WorldBookmarkStyle.h` (Private)


#### class `FWorldBookmarkStyle`  
`class FWorldBookmarkStyle final : public FSlateStyleSet`  
_L8-15_
- inherits: `FSlateStyleSet`
- L11 _public prototype_ `FWorldBookmarkStyle();`
- L12 _public prototype_ `virtual ~FWorldBookmarkStyle();`
- L14 _public prototype_ `static FWorldBookmarkStyle& Get();`

### `Source/Editor/WorldBookmark/Public/WorldBookmark/WorldBookmark.h` (Public)


#### struct `FWorldBookmarkCategory`  
`struct FWorldBookmarkCategory`  
_L17-36_
- reflection: `USTRUCT()`
- desc: World Bookmark Category
- L21 _public member_ `static const FWorldBookmarkCategory None;`
- L23 _public prototype_ `FWorldBookmarkCategory();`
- L24 _public prototype_ `FWorldBookmarkCategory(FName InName, FColor InColor);`
- L26 _public prototype_ `bool operator<(const FWorldBookmarkCategory& Other) const;`
- L29 _public member_ `FName Name;` — `UPROPERTY(EditAnywhere, Category=Category)`
- L32 _public member_ `FColor Color;` — `UPROPERTY(EditAnywhere, Category=Category, Meta=(HideAlphaChannel, DontUpdateWhileEditing, IgnoreForMemberInitializationTest))`
- L35 _public member_ `FGuid Guid;` — `UPROPERTY(Meta=(IgnoreForMemberInitializationTest))`

#### class `UWorldBookmark`  
`class UWorldBookmark : public UBookmarkBase`  
_L42-143_
- reflection: `UCLASS(MinimalAPI, Config = UserWorldBookmarks, PerObjectConfig)`
- inherits: `UBookmarkBase`
- desc: World Bookmarks are assets that stores the state of the editor world.
- L47 _private prototype_ `bool CanLoad(FText* FailureReason = nullptr) const;` — Test whether it's possible to load this bookmark given the current state of the editor.
- L50 _private prototype_ `bool CanUpdate(FText* FailureReason = nullptr) const;` — Test whether it's possible to update this bookmark given the current state of the editor.
- L53 _private prototype_ `void Load();` — Load the bookmark data, restoring the editor state (loaded world, camera location, etc) to what is defined by the bookmark.
- L56 _private prototype_ `void Update();` — Update the bookmark so that it reflects the current state of the editor.
- L59 _private prototype_ `void LoadStates(const TArray<TSubclassOf<UEditorState>>& InStatesToLoad);` — Load the bookmark data, restoring only a specific set of editor states.
- L62 _private prototype_ `void UpdateStates(const TArray<TSubclassOf<UEditorState>>& InStatesToUpdate);` — Update a set of states for the bookmark.
- L65 _private prototype_ `bool HasEditorStates() const;` — Return true if the world bookmark contains states that can be restored.
- L68 _private prototype_ `bool GetIsUserFavorite() const;` — Return true if this bookmark was flagged as being a favorite bookmark of the user.
- L71 _private prototype_ `void SetIsUserFavorite(bool bIsUserFavorite);` — Mark this bookmark as being a favorite bookmark of the user.
- L74 _private prototype_ `FDateTime GetUserLastLoadedTimeStampUTC() const;` — Retrieve the last time that bookmark was loaded, in UTC.
- L77 _private prototype_ `void SetUserLastLoadedTimeStampUTC(const FDateTime& InLastLoadedTimeStampUTC);` — Store the last time that bookmark was loaded, in UTC.
- L80 _private prototype_ `const FWorldBookmarkCategory& GetBookmarkCategory() const;` — Retrieve the world bookmark category for this bookmark.
- L83 _private prototype_ `static FName GetWorldNameAssetTag();` — Get the asset registry tag used to store the matching world's name.
- L86 _private prototype_ `static FName GetCategoryAssetTag();` — Get the asset registry tag used to store bookmark category info.
- L89 _private prototype_ `static FSoftObjectPath GetWorldFromAssetData(const FAssetData& InAssetData);` — Get the world associated with a bookmark's asset data.
- L92 _private function_ `template <typename TEditorStateType> typename TEnableIf<TIsDerivedFrom<TEditorStateType, UEditorState>::IsDerived, bool>::Type HasEditorState() const`
- L98 _private function_ `template <typename TEditorStateType> typename TEnableIf<TIsDerivedFrom<TEditorStateType, UEditorState>::IsDerived, const TEditorStateType*>::Type GetEditorState() const`
- L107 _private prototype_ `virtual void PostLoad() override;`
- L108 _private prototype_ `virtual void PreSave(FObjectPreSaveContext ObjectSaveContext) override;`
- L109 _private prototype_ `virtual void GetAssetRegistryTags(FAssetRegistryTagsContext Context) const override;`
- L110 _private prototype_ `virtual void PostInitProperties() override;`
- L111 _private prototype_ `virtual void PostDuplicate(bool bDuplicateForPIE) override;`
- L112 _private prototype_ `virtual void OverridePerObjectConfigSection(FString& SectionName) override;`
- L118 _private member_ `FEditorStateCollection EditorState;` — `UPROPERTY()` — State of the editor.
- L121 _private member_ `FGuid CategoryGuid;` — `UPROPERTY(EditAnywhere, Category=Category, meta=(DisplayName="Category"))`
- L126 _private member_ `FGuid BookmarkGuid;` — `UPROPERTY(DuplicateTransient)` — BookmarkGuid is our key to fetch the user settings for this bookmark in the Bookmarks.ini config file. It will remain unique even if redirectors are created for the world or the bookmark itself.
- L132 _private member_ `FDateTime LastLoadedTimeStampUTC;` — `UPROPERTY(Config, Transient)` — Last loaded time (UTC)
- L136 _private member_ `bool bFavorite;` — `UPROPERTY(Config, Transient)` — User favorite
- L140 _private member_ `FString BookmarkAssetPath;` — `UPROPERTY(Config, Transient)` — Unused - The sole purpose of this property is to help users who would want to investigate/make changes to the ini themselves, as GUIDs are pretty opaque.

#### Free symbols / members of external scopes

- L11 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogWorldBookmark, Log, All);`
- L11 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogWorldBookmark, Log, All);`
