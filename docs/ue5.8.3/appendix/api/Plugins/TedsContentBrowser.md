# Plugins / TedsContentBrowser

- module root: `Plugins/Experimental/EditorDataStorageFeatures/Source/TedsContentBrowser`
- headers: 3; symbols: 115
- symbol kinds: class=5, member=25, namespace=8, prototype=74, struct=3
- DynamicallyLoadedModuleNames: 
- PrivateDependencyModuleNames: ContentBrowser, ContentBrowserData, InputCore, Slate, SlateCore, TedsAlerts, TedsAssetData, TedsQueryStack, TedsTableViewer, ToolWidgets, TypedElementFramework
- PublicDependencyModuleNames: Core, CoreUObject

### `Plugins/Experimental/EditorDataStorageFeatures/Source/TedsContentBrowser/Private/TedsContentBrowserModule.h` (Private)


#### class `UE::Editor::ContentBrowser::FTestContentSource`  
`class FTestContentSource : public IContentSource`  
_L31-40_
- inherits: `IContentSource`
- desc: A test content source that currently displays the query used by the Outliner
- L34 _public prototype_ `virtual ~FTestContentSource() override = default;`
- L36 _public prototype_ `virtual FName GetName() override;`
- L37 _public prototype_ `virtual FText GetDisplayName() override;`
- L38 _public prototype_ `virtual FSlateIcon GetIcon() override;`
- L39 _public prototype_ `virtual void GetAssetViewInitParams(FTableViewerInitParams& OutInitParams) override;`

#### class `UE::Editor::ContentBrowser::FTedsContentBrowserViewExtender`  
`class FTedsContentBrowserViewExtender : public IContentBrowserViewExtender`  
_L43-172_
- inherits: `IContentBrowserViewExtender`
- desc: A custom view for the content browser that uses the TEDS asset registry integration to display rows with widgets using TEDS UI
- L47 _public prototype_ `FTedsContentBrowserViewExtender();`
- L50 _public prototype_ `virtual TSharedRef<SWidget> CreateView(TArray<TSharedPtr<FAssetViewItem>>* InItemsSource) override;` — IContentBrowserViewExtender interface
- L51 _public prototype_ `virtual TArray<TSharedPtr<FAssetViewItem>> GetSelectedItems() override;`
- L52 _public prototype_ `virtual FOnSelectionChanged& OnSelectionChanged() override;`
- L53 _public prototype_ `virtual FOnContextMenuOpening& OnContextMenuOpened() override;`
- L54 _public prototype_ `virtual FOnItemScrolledIntoView& OnItemScrolledIntoView() override;`
- L55 _public prototype_ `virtual FOnMouseButtonClick& OnItemDoubleClicked() override;`
- L56 _public prototype_ `virtual FText GetViewDisplayName() override;`
- L57 _public prototype_ `virtual FText GetViewTooltipText() override;`
- L58 _public prototype_ `virtual void FocusList() override;`
- L59 _public prototype_ `virtual void SetSelection(const TSharedPtr<FAssetViewItem>& Item, bool bSelected, const ESelectInfo::Type SelectInfo)override;`
- L60 _public prototype_ `virtual void RequestScrollIntoView(const TSharedPtr<FAssetViewItem>& Item) override;`
- L61 _public prototype_ `virtual void ClearSelection() override;`
- L62 _public prototype_ `virtual bool IsRightClickScrolling() override;`
- L63 _public prototype_ `virtual void OnItemListChanged(TArray<TSharedPtr<FAssetViewItem>>* InItemsSource) override;`
- L67 _public prototype_ `void RefreshRows(TArray<TSharedPtr<FAssetViewItem>>* InItemsSource);` — Refresh the rows in the current view by syncing the the items source
- L70 _public prototype_ `void AddRow(const TSharedPtr<FAssetViewItem>& Item);` — Add a single row to the table viewer
- L73 _public prototype_ `TSharedPtr<FAssetViewItem> GetAssetViewItemFromRow(DataStorage::RowHandle Row);` — Get the internal FAssetViewItem from a row handle
- L75 _public prototype_ `DataStorage::RowHandle GetRowFromAssetViewItem(const TSharedPtr<FAssetViewItem>& Item);`
- L79 _protected prototype_ `void CreateListView();` — Update the table viewer used by the integration to use a list view
- L82 _protected prototype_ `void CreateTileView();` — Update the table viewer used by the integration to use a tile view
- L85 _protected prototype_ `void BindViewColumns();` — Bind the table viewer's columns to CB delegates
- L88 _protected prototype_ `void CreateAssetPreview();` — Create the asset preview widget
- L91 _protected prototype_ `void BindAssetPreviewColumns();` — Bind the AssetPreview columns to CB delegates
- L94 _protected prototype_ `void UpdateAssetPreviewTargetRow() const;` — Update the AssetPreview Target Row
- L98 _private prototype_ `float GetTileViewTypeNameHeight() const;` — Get the name area total height
- L101 _private prototype_ `float GetThumbnailSizeValue() const;` — Get the thumbnail size value
- L104 _private prototype_ `EThumbnailSize GetThumbnailSize() const;` — Get the thumbnail size
- L107 _private prototype_ `float GetTileViewItemWidth() const;` — Get the tile item width
- L110 _private prototype_ `float GetTileViewItemHeight() const;` — Get the tile item height
- L113 _private prototype_ `float GetListViewItemHeight() const;` — Get the list item height
- L116 _private prototype_ `FMargin GetListViewItemPadding() const;` — Get the list item padding
- L119 _private prototype_ `void UpdateThumbnailSize() const;` — Update the thumbnail size of the Tile/Column view and broadcast the event
- L122 _private prototype_ `void UpdateSizeValue() const;` — Update the size value of the Tile/Column view and broadcast the event
- L125 _private prototype_ `void UpdateEditMode() const;` — Update the EditMode value of the Tile view and broadcast the event
- L129 _private member_ `TSharedPtr<STedsAssetPreviewWidget> AssetPreviewWidget;` — AssetPreview widget
- L132 _private member_ `ETableViewMode::Type CustomViewType = ETableViewMode::List;` — Custom view type
- L135 _private member_ `EThumbnailSize CurrentThumbnailSize = EThumbnailSize::Medium;` — The current Thumbnail size
- L138 _private member_ `float ThumbnailSizeValue = 80.f;` — The current Thumbnail size value
- L141 _private member_ `bool IsThumbnailEditMode = false;` — Whether the thumbnail edit mode is enabled
- L144 _private member_ `static constexpr float TedsTileViewTypeNameHeight = 67.f;` — Name area total height
- L147 _private member_ `static constexpr int32 TedsTileViewHeightPadding = 9;` — Vertical padding for the TileViewItem
- L150 _private member_ `static constexpr int32 TedsTileViewWidthPadding = 8;` — Horizontal padding for the TileViewItem
- L153 _private member_ `static constexpr int32 TedsListViewHeightPadding = 2;` — Vertical padding for the ListViewItem
- L156 _private member_ `DataStorage::ICoreProvider* DataStorage;` — Ptr to the data storage interface
- L159 _private member_ `TSharedPtr<DataStorage::ITableViewer> TableViewer;` — The actual table viewer widget
- L162 _private member_ `TSharedPtr<DataStorage::QueryStack::FRowArrayNode> RowQueryStack;` — Query stack used by the table viewer
- L165 _private member_ `TMap<DataStorage::RowHandle, TWeakPtr<FAssetViewItem>> ContentBrowserItemMap;` — A map from row handle -> FAssetView item for lookups
- L168 _private member_ `FOnSelectionChanged OnSelectionChangedDelegate;` — Delegates fired when specific events happen on the list
- L169 _private member_ `FOnContextMenuOpening OnContextMenuOpenedDelegate;`
- L170 _private member_ `FOnItemScrolledIntoView OnItemScrolledIntoViewDelegate;`
- L171 _private member_ `FOnMouseButtonClick OnItemDoubleClickedDelegate;`

#### class `UE::Editor::ContentBrowser::FTedsContentBrowserModule`  
`class FTedsContentBrowserModule : public IModuleInterface`  
_L177-192_
- inherits: `IModuleInterface`
- desc: Implements the Teds Content Browser module.
- L182 _public prototype_ `FTedsContentBrowserModule() = default;`
- L184 _public prototype_ `static TSharedPtr<IContentBrowserViewExtender> CreateContentBrowserViewExtender();`
- L186 _public prototype_ `void RegisterTestContentSource();`
- L187 _public prototype_ `void UnregisterTestContentSource();`
- L190 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface interface
- L191 _public prototype_ `virtual void ShutdownModule() override;`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace Editor` (scope `UE`)
- L12 _namespace_ `namespace DataStorage` (scope `UE::Editor`)
- L18 _namespace_ `namespace QueryStack` (scope `UE::Editor::DataStorage`)
- L27 _namespace_ `namespace UE`
- L27 _namespace_ `namespace Editor` (scope `UE`)
- L27 _namespace_ `namespace ContentBrowser` (scope `UE::Editor`)

### `Plugins/Experimental/EditorDataStorageFeatures/Source/TedsContentBrowser/Private/Widgets/ContentBrowserTileViewWidget.h` (Private)


#### class `UContentBrowserTileViewWidgetFactory`  
`class UContentBrowserTileViewWidgetFactory : public UEditorDataStorageFactory`  
_L27-38_
- reflection: `UCLASS()`
- inherits: `UEditorDataStorageFactory`
- L32 _public prototype_ `~UContentBrowserTileViewWidgetFactory() override = default;`
- L34 _public prototype_ `virtual void RegisterWidgetPurposes(UE::Editor::DataStorage::IUiProvider& DataStorageUi) const override;`
- L36 _public prototype_ `void RegisterWidgetConstructors(UE::Editor::DataStorage::ICoreProvider& DataStorage, UE::Editor::DataStorage::IUiProvider& DataStorageUi) const override;`

#### struct `FContentBrowserTileViewWidgetConstructor`  
`struct FContentBrowserTileViewWidgetConstructor : public FSimpleWidgetConstructor`  
_L42-111_
- reflection: `USTRUCT()`
- inherits: `FSimpleWidgetConstructor`
- desc: Content Browser Label + Thumbnail widget
- L47 _public prototype_ `FContentBrowserTileViewWidgetConstructor();`
- L49 _public prototype_ `virtual TSharedPtr<SWidget> CreateWidget( UE::Editor::DataStorage::ICoreProvider* DataStorage, UE::Editor::DataStorage::IUiProvider* DataStorageUi, UE::Editor::DataStorage::RowHandle TargetRow, UE::Editor::DataStorage::RowHandle WidgetRow, const UE::Editor::DataStorage::FMetaDataView& Arguments) override;`
- L56 _public prototype_ `virtual TConstArrayView<const UScriptStruct*> GetAdditionalColumnsList() const override;`
- L74 _private prototype_ `const FSlateBrush* GetFolderBackgroundShadowImage(FTedsTileViewCommonArguments InTedsTileViewCommonArguments) const;` — Get the folder shadow image
- L77 _private prototype_ `const FSlateBrush* GetFolderSlotBorder(FTedsTileViewCommonArguments InTedsTileViewCommonArguments) const;` — Get the folder image slot border
- L80 _private prototype_ `const FSlateBrush* GetAssetThumbnailBorderOverride(FTedsTileViewCommonArguments InTedsTileViewCommonArguments) const;` — Get the asset thumbnail border to use
- L83 _private prototype_ `const FSlateBrush* GetNameAreaBackgroundImage(FTedsTileViewCommonArguments InTedsTileViewCommonArguments) const;` — Get the name are background image
- L86 _private prototype_ `FSlateFontInfo GetThumbnailFont() const;` — Get the font to use for the thumbnail label
- L89 _private prototype_ `FSlateColor GetNameAreaTextColor(FTedsTileViewCommonArguments InTedsTileViewCommonArguments) const;` — Get the name area text color
- L92 _private prototype_ `FOptionalSize GetNameAreaMaxDesiredHeight() const;` — Get the maximum height for the name area
- L95 _private prototype_ `EVisibility GetAssetClassLabelVisibility(bool bIsAsset) const;` — Gets the visibility of the asset class label in thumbnails
- L98 _private prototype_ `FSlateColor GetAssetClassLabelTextColor(FTedsTileViewCommonArguments InTedsTileViewCommonArguments) const;` — Gets the color and opacity of the asset class type
- L101 _private prototype_ `const FSlateBrush* GetFolderBackgroundImage(FTedsTileViewCommonArguments InTedsTileViewCommonArguments) const;` — Gets the background image for folders
- L104 _private prototype_ `TSharedPtr<SWidget> CreateThumbnailWidget(FTedsTileViewCommonArguments InTedsTileViewCommonArguments, UE::Editor::DataStorage::RowHandle& OutThumbnailWidgetRowHandle) const;` — Create the thumbnail widget through TEDS
- L107 _private prototype_ `TSharedPtr<SWidget> CreateItemTypeWidget(FTedsTileViewCommonArguments InTedsTileViewCommonArguments, UE::Editor::DataStorage::RowHandle& OutItemTypeWidgetRowHandle) const;` — Create the item type widget through TEDS
- L110 _private prototype_ `TArray<TWeakObjectPtr<const UScriptStruct>> GetItemTypeColumns() const;` — Get the ItemType columns

#### struct `FContentBrowserTileViewWidgetConstructor::FTedsTileViewCommonArguments`  
`struct FTedsTileViewCommonArguments`  
_L61-71_
- desc: Common data needed for various function
- L63 _public member_ `UE::Editor::DataStorage::ICoreProvider* DataStorage;`
- L64 _public member_ `UE::Editor::DataStorage::IUiProvider* DataStorageUi;`
- L65 _public member_ `UE::Editor::DataStorage::RowHandle TargetRow;`
- L66 _public member_ `UE::Editor::DataStorage::RowHandle WidgetRow;`
- L67 _public member_ `UE::Editor::DataStorage::RowHandle ParentWidgetRowHandle;`
- L68 _public member_ `bool bIsAsset;`
- L69 _public member_ `TSharedPtr<SWidget> ThumbnailWidget;`
- L70 _public member_ `TSharedPtr<SWidget> TileItem;`

#### Free symbols / members of external scopes

- L20 _namespace_ `namespace Purpose`
- L22 _prototype_ `FName GetPurposeNamespace();` (scope `Purpose`)
- L23 _prototype_ `FName GetPurposeName();` (scope `Purpose`)

### `Plugins/Experimental/EditorDataStorageFeatures/Source/TedsContentBrowser/Private/Widgets/TedsContentBrowserAssetViewWidget.h` (Private)


#### class `UContentBrowserAssetViewWidgetFactory`  
`class UContentBrowserAssetViewWidgetFactory : public UEditorDataStorageFactory`  
_L15-26_
- reflection: `UCLASS()`
- inherits: `UEditorDataStorageFactory`
- L20 _public prototype_ `~UContentBrowserAssetViewWidgetFactory() override = default;`
- L22 _public prototype_ `virtual void RegisterWidgetPurposes(UE::Editor::DataStorage::IUiProvider& DataStorageUi) const override;`
- L24 _public prototype_ `void RegisterWidgetConstructors(UE::Editor::DataStorage::ICoreProvider& DataStorage, UE::Editor::DataStorage::IUiProvider& DataStorageUi) const override;`

#### struct `FContentBrowserAssetViewWidgetConstructor`  
`struct FContentBrowserAssetViewWidgetConstructor : public FSimpleWidgetConstructor`  
_L30-47_
- reflection: `USTRUCT()`
- inherits: `FSimpleWidgetConstructor`
- desc: Default asset view widget shown by a content source - the query and other init params are populated by the content source itself
- L35 _public prototype_ `FContentBrowserAssetViewWidgetConstructor();`
- L36 _public prototype_ `explicit FContentBrowserAssetViewWidgetConstructor(const UScriptStruct* TypeInfo);`
- L37 _public prototype_ `~FContentBrowserAssetViewWidgetConstructor() override = default;`
- L39 _public prototype_ `virtual TSharedPtr<SWidget> CreateWidget( UE::Editor::DataStorage::ICoreProvider* DataStorage, UE::Editor::DataStorage::IUiProvider* DataStorageUi, UE::Editor::DataStorage::RowHandle TargetRow, UE::Editor::DataStorage::RowHandle WidgetRow, const UE::Editor::DataStorage::FMetaDataView& Arguments) override;`
