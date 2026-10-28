# Editor / PlacementMode

- module root: `Source/Editor/PlacementMode`
- headers: 5; symbols: 239
- symbol kinds: class=7, delegate=12, function=46, member=62, prototype=104, struct=6, typedef=2
- PrivateDependencyModuleNames: AssetTools, CollectionManager, ContentBrowser, ContentBrowserData, Core, CoreUObject, EditorFramework, EditorWidgets, InputCore, LevelEditor, Slate, SlateCore, ToolMenus, TypedElementFramework, TypedElementRuntime, UnrealEd, WidgetRegistration
- PrivateIncludePathModuleNames: AssetTools
- PublicDependencyModuleNames: Engine

### `Source/Editor/PlacementMode/Private/PlacementModeLog.h` (Private)


#### Free symbols / members of external scopes

- L7 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogPlacementMode, Log, All);`
- L7 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogPlacementMode, Log, All);`

### `Source/Editor/PlacementMode/Private/SPlacementModeTools.h` (Private)


#### struct `TWidgetTypeTraits`  
`template <> struct TWidgetTypeTraits<class SPlacementAssetEntry>`  
_L22-25_
- L24 _public function_ `static constexpr bool SupportsInvalidation()`

#### class `SPlacementAssetEntry`  
`class SPlacementAssetEntry : public SCompoundWidget`  
_L31-68_
- inherits: `SCompoundWidget`
- desc: A tile representation of the class or the asset.  These are embedded into the views inside of each tab.
- L34 _public function_ `SLATE_BEGIN_ARGS(SPlacementAssetEntry)`
- L37 _public prototype_ `SLATE_ATTRIBUTE(FText, HighlightText) SLATE_EVENT( FOnGetContent, OnGetMenuContent ) SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TSharedPtr<const FPlaceableItem>& InItem);` — Highlight this text in the text block
- L44 _public prototype_ `virtual FReply OnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L45 _public prototype_ `virtual FReply OnMouseButtonUp(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L46 _public prototype_ `virtual FReply OnDragDetected(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L48 _public prototype_ `bool IsPressed() const;`
- L51 _public member_ `TSharedPtr<const FPlaceableItem> Item;`
- L56 _private member_ `FOnGetContent OnGetMenuContent;` — Delegate to execute to get the menu content of this button
- L58 _private prototype_ `const FSlateBrush* GetBorder() const;`
- L60 _private member_ `bool bIsPressed;`
- L63 _private member_ `const FSlateBrush* NormalImage;` — Brush resource that represents a button
- L65 _private member_ `const FSlateBrush* HoverImage;` — Brush resource that represents a button when it is hovered
- L67 _private member_ `const FSlateBrush* PressedImage;` — Brush resource that represents a button when it is pressed

#### class `SPlacementAssetMenuEntry`  
`class SPlacementAssetMenuEntry : public SCompoundWidget`  
_L70-99_
- inherits: `SCompoundWidget`
- L73 _public function_ `SLATE_BEGIN_ARGS(SPlacementAssetMenuEntry)`
- L74 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TSharedPtr<const FPlaceableItem>& InItem);`
- L78 _public prototype_ `virtual FReply OnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L79 _public prototype_ `virtual FReply OnMouseButtonUp(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L80 _public prototype_ `virtual FReply OnDragDetected(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L82 _public prototype_ `bool IsPressed() const;`
- L84 _public member_ `TSharedPtr<const FPlaceableItem> Item;`
- L86 _public prototype_ `virtual FSlateColor GetForegroundColor() const override;`
- L88 _private prototype_ `bool TryPlacingItemInLevel(TNotNull<ULevel*> DesiredLevel, AActor*& OutPlacedActor);`
- L91 _private prototype_ `const FSlateBrush* GetBorder() const;`
- L92 _private prototype_ `const FSlateBrush* GetIcon() const;`
- L94 _private member_ `bool bIsPressed;`
- L96 _private member_ `const FButtonStyle* Style;`
- L98 _private member_ `mutable const FSlateBrush* AssetImage;`

#### class `SPlacementModeTools`  
`class SPlacementModeTools : public SCompoundWidget`  
_L102-216_
- inherits: `SCompoundWidget`
- L105 _public function_ `SLATE_BEGIN_ARGS( SPlacementModeTools )`
- L106 _public prototype_ `SLATE_END_ARGS();`
- L108 _public prototype_ `void Construct(const FArguments& InArgs, TSharedRef<SDockTab> ParentTab);`
- L110 _public prototype_ `virtual ~SPlacementModeTools();`
- L117 _public prototype_ `TSharedRef<SWidget> GetPlacementAssetWidget(const TSharedPtr<FPlaceableItem>& InItem) const;` — Creates and returns the TSharedRef<SPlacementAssetEntry>for the given TSharedPtr<SPlacementAssetEntry> @param InItem the FPlaceableItem for which  the TSharedRef<SPlacementAssetEntry> will be created and returned
- L125 _public prototype_ `void UpdateContentForCategory( FName CategoryName, FText CategoryLabel );` — Given FName CategoryName as the Category that has been clicked, update the FCategoryDrivenContentBuilder with the proper content for the category @param CategoryName the name of the currently chosen Category @param CategoryLabel the label for the currently chosen Category
- L130 _private prototype_ `virtual void Tick( const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime ) override;`
- L135 _private prototype_ `FName GetActiveTab() const;` — Get the identifier of the currently active tab
- L138 _private prototype_ `void SetActiveTab(FName TabName);` — Changes the active tab
- L141 _private prototype_ `bool IsSearchActive() const;` — Check if a search is active
- L146 _private prototype_ `bool IsFavoritesCategorySelected() const;` — returns true is the favorites category is selected, else it returns false
- L149 _private prototype_ `void UpdateShownItems();` — Update the list of shown items
- L152 _private prototype_ `void RequestUpdateShownItems();` — Requests an update of the shown items
- L155 _private prototype_ `void RequestRefreshRecentlyPlaced( const TArray< FActorPlacementInfo >& RecentlyPlaced );` — Requests a refresh of the list of recently placed assets
- L158 _private prototype_ `void RequestRefreshAllClasses();` — Requests a refresh of placeable assets in the All Classes category
- L161 _private prototype_ `void OnCategoryRefresh(FName CategoryName);` — Called when the placement module performs a category refresh
- L164 _private prototype_ `void UpdatePlacementCategories();` — Refreshes the list of placement categories
- L167 _private prototype_ `void OnCategoryChanged(const ECheckBoxState NewState, FName InCategory);` — When the tab is clicked we adjust the check state, so that the right style is displayed.
- L170 _private prototype_ `void OnTabDrawerOpened();` — Called when the placement mode tools are opened from a tab drawer
- L173 _private prototype_ `ECheckBoxState GetPlacementTabCheckedState( FName CategoryName ) const;` — Gets the tab 'active' state, so that we can show the active style
- L178 _private prototype_ `void OnSearchChanged(const FText& InFilterText);` — Called when the search text changes
- L179 _private prototype_ `void OnSearchCommitted(const FText& InFilterText, ETextCommit::Type InCommitType);`
- L182 _private prototype_ `FText GetHighlightText() const;` — Get the text that should be highlighted on any items
- L186 _private member_ `bool bRefreshRecentlyPlaced;` — Flags to refresh particular categories on tick
- L187 _private member_ `bool bRefreshAllClasses;`
- L190 _private member_ `bool bUpdateShownItems;` — Flag to indicate that we need to update the list of shown items
- L193 _private member_ `bool bIsRawSearchChange;` — Flag to indicate that we're programmatically changing the search text and that we should skip updating the placement entries
- L196 _private typedef_ `typedef TTextFilter<const FPlaceableItem&> FPlacementAssetEntryTextFilter;` — The text filter used to filter the classes
- L197 _private member_ `TSharedPtr<FPlacementAssetEntryTextFilter> SearchTextFilter;`
- L200 _private member_ `TSharedPtr<SSearchBox> SearchBoxPtr;` — The search box used to update the filter text
- L203 _private member_ `TArray<TSharedPtr<FPlaceableItem>> FilteredItems;` — Array of filtered items to show in the list view
- L206 _private member_ `FName ActiveTabName;` — The name of the currently active tab (where no search is active)
- L209 _private member_ `TSharedPtr<SListView<TSharedPtr<FPlaceableItem>>> ListView;` — List view that shows placeable items
- L212 _private member_ `TSharedPtr<FCategoryDrivenContentBuilder> CategoryContentBuilder;` — The FCategoryDrivenContentBuilder which will build the UI for this mode, if defined
- L215 _private member_ `TArray<TSharedPtr<FPlaceableItem>> FavoriteItems;` — Array of favorite items to show in the favorites view

### `Source/Editor/PlacementMode/Public/ActorPlacementInfo.h` (Public)


#### class `FActorPlacementInfo`  
`class FActorPlacementInfo`  
_L8-46_
- L12 _public function_ `FActorPlacementInfo( const FString& InObjectPath, const FString& InFactory ) : ObjectPath( InObjectPath ) , Factory( InFactory )`
- L18 _public function_ `FActorPlacementInfo( const FString& String )`
- L26 _public function_ `bool operator==( const FActorPlacementInfo& Other ) const`
- L31 _public function_ `bool operator!=( const FActorPlacementInfo& Other ) const`
- L36 _public function_ `FString ToString() const`
- L44 _public member_ `FString ObjectPath;`
- L45 _public member_ `FString Factory;`

#### Free symbols / members of external scopes

- L48 _function_ `inline uint32 GetTypeHash(const FActorPlacementInfo& Object)`

### `Source/Editor/PlacementMode/Public/IPlacementModeModule.h` (Public)


#### class `FPlacementModeID`  
`class FPlacementModeID`  
_L26-42_
- desc: Struct that defines an identifier for a particular placeable item in this module. Only be obtainable through IPlacementModeModule::RegisterPlaceableItem
- L29 _public prototype_ `FPlacementModeID(const FPlacementModeID&) = default;`
- L30 _public prototype_ `FPlacementModeID& operator=(const FPlacementModeID&) = default;`
- L35 _private function_ `FPlacementModeID()`
- L38 _private member_ `FName Category;` — The category this item is held within
- L41 _private member_ `FGuid UniqueID;` — Unique identifier (always universally unique across categories)

#### struct `FPlacementCategoryInfo`  
`struct FPlacementCategoryInfo`  
_L47-88_
- desc: Struct providing information for a user category of placement objects
- L49 _public function_ `FPlacementCategoryInfo(FText InDisplayName, FSlateIcon InDisplayIcon, FName InHandle, FString InTag, int32 InSortOrder = 0, bool bInSortable = true) : DisplayName(InDisplayName), DisplayIcon(InDisplayIcon), UniqueHandle(InHandle), SortOrder(InSortOrder), TagMetaData(MoveTemp(InTag)), bSortable(bInSortable)`
- L54 _public function_ `FPlacementCategoryInfo(FText InDisplayName, FName InHandle, FString InTag, int32 InSortOrder = 0, bool bInSortable = true) : DisplayName(InDisplayName), DisplayIcon(), UniqueHandle(InHandle), SortOrder(InSortOrder), TagMetaData(MoveTemp(InTag)), bSortable(bInSortable)`
- L61 _public member_ `FText DisplayName;` — This category's display name
- L64 _public member_ `FText ShortDisplayName;` — This category's short display name (optional)
- L67 _public member_ `FSlateIcon DisplayIcon;` — This category's representative icon
- L70 _public member_ `FName UniqueHandle;` — A unique name for this category
- L73 _public member_ `int32 SortOrder;` — Sort order for the category tab (lowest first)
- L76 _public member_ `FString TagMetaData;` — Optional tag meta data for the tab widget
- L79 _public member_ `TFunction<TSharedRef<SWidget>()> CustomGenerator;` — Optional generator function used to construct this category's tab content. Called when the tab is activated.
- L82 _public member_ `bool bSortable;` — Whether the items in this category are automatically sortable by name. False if the items are already sorted.
- L87 _public member_ `TArray< TSharedRef<FPlaceableItem>> CustomDraggableItems;` — FPlaceableItems with custom drag handling, populated only if the category handles making its own draggable items

#### struct `FPlaceableItem`  
`struct FPlaceableItem`  
_L93-297_
- desc: Structure defining a placeable item in the placement mode panel
- L114 _public function_ `FPlaceableItem() : Factory(nullptr)` — Default constructor
- L119 _public function_ `FPlaceableItem(TScriptInterface<IAssetFactoryInterface> InAssetFactory, const FAssetData& InAssetData, TOptional<int32> InSortOrder = TOptional<int32>()) : Factory(Cast<UActorFactory>(InAssetFactory.GetObject())) , AssetFactory(InAssetFactory) , AssetData(InAssetData) , bAlwaysUseGenericThumbnail(false) , SortOrder(InSortOrder)` — Constructor that takes a specific factory and asset
- L136 _public function_ `FPlaceableItem(UActorFactory* InFactory, const FAssetData& InAssetData, TOptional<int32> InSortOrder = TOptional<int32>()) : Factory(InFactory) , AssetFactory(InFactory) , AssetData(InAssetData) , bAlwaysUseGenericThumbnail(false) , SortOrder(InSortOrder)` — Constructor that takes a specific actor factory and asset
- L149 _public function_ `FPlaceableItem(UClass& InActorFactoryClass, TOptional<int32> InSortOrder = TOptional<int32>()) : Factory(GEditor->FindActorFactoryByClass(&InActorFactoryClass)) , AssetFactory(Factory) , AssetData(Factory ? Factory->GetDefaultActorClass(FAssetData()) : FAssetData()) , bAlwaysUseGenericThumbnail(false) , SortOrder(InSortOrder)` — Constructor for any actor factory class
- L160 _public function_ `FPlaceableItem( TScriptInterface<IAssetFactoryInterface> InAssetFactory, const FAssetData& InAssetData, FName InClassThumbnailBrushOverride, FName InClassIconBrushOverride, TOptional<FLinearColor> InAssetTypeColorOverride = TOptional<FLinearColor>(), TOptional<int32> InSortOrder = TOptional<int32>(), TOptional<FText> InDisplayName = TOptional<FText>()) : Factory(Cast<UActorFactory>(InAssetFactory.GetObject())) , AssetFactory(InAssetFactory) , AssetData(InAssetData) , ClassThumbnailBrushOverride(InClassThumbnailBrushOverride) , ClassIconBrushOverride(InClassIconBrushOverride) , bAlwaysUseGenericThumbnail(true) , AssetTypeColorOverride(InAssetTypeColorOverride) , SortOrder(InSortOrder)` — Constructor that takes a specific factory and asset with brush and display name overrides
- L184 _public function_ `FPlaceableItem( TSharedPtr<FPlaceableItem::FDragHandler> InDragHandler , TOptional<int32> InSortOrder , FText InLabel , FString InName ): NativeName( InName ) , DisplayName( InLabel ) , bAlwaysUseGenericThumbnail(false) , SortOrder(InSortOrder) , DragHandler(InDragHandler)`
- L198 _public function_ `FPlaceableItem( UClass& InActorFactoryClass, const FAssetData& InAssetData, FName InClassThumbnailBrushOverride = NAME_None, FName InClassIconBrushOverride = NAME_None, TOptional<FLinearColor> InAssetTypeColorOverride = TOptional<FLinearColor>(), TOptional<int32> InSortOrder = TOptional<int32>(), TOptional<FText> InDisplayName = TOptional<FText>() ) : Factory(GEditor->FindActorFactoryByClass(&InActorFactoryClass)) , AssetFactory(Factory) , AssetData(InAssetData) , ClassThumbnailBrushOverride(InClassThumbnailBrushOverride) , ClassIconBrushOverride(InClassIconBrushOverride) , bAlwaysUseGenericThumbnail(true) , AssetTypeColorOverride(InAssetTypeColorOverride) , SortOrder(InSortOrder)` — Constructor for any placeable actor class with associated asset data, brush and display name overrides
- L224 _public function_ `void AutoSetNativeAndDisplayName()` — Automatically set this item's native and display names from its class or asset
- L246 _public function_ `void AutoSetDisplayName()` — `UE_DEPRECATED(4.27, "Use AutoSetNativeAndDisplayName instead")`
- L249 _public function_ `FName GetNativeFName() const` — Return NativeName as an FName (and cache it)
- L261 _public member_ `UActorFactory* Factory = nullptr;` — `UE_DEPRECATED(5.4, "Use AssetFactory instead.")`
- L264 _public member_ `TScriptInterface<IAssetFactoryInterface> AssetFactory = nullptr;` — The factory used to create an instance of this placeable item
- L267 _public member_ `FAssetData AssetData;` — Asset data pertaining to the class
- L270 _public member_ `FString NativeName;` — This item's native name
- L273 _public member_ `FText DisplayName;` — This item's display name
- L276 _public member_ `FName ClassThumbnailBrushOverride;` — Optional override for the thumbnail brush (passed to FClassIconFinder::FindThumbnailForClass in the form ClassThumbnail.<override>)
- L279 _public member_ `FName ClassIconBrushOverride;` — Optional override for the small icon brush
- L282 _public member_ `bool bAlwaysUseGenericThumbnail;` — Whether to always use the generic thumbnail for this item or not
- L285 _public member_ `TOptional<FLinearColor> AssetTypeColorOverride;` — Optional overridden color tint for the asset
- L288 _public member_ `TOptional<int32> SortOrder;` — Optional sort order (lowest first). Overrides default class name sorting.
- L291 _public member_ `TSharedPtr<FDragHandler> DragHandler;` — If provided, handles the drag for the item. This should be provided for objects which are not actors or assets, which have built in handling
- L296 _private member_ `mutable FName NativeFName;` — This item's native name as an FName (initialized on access only)

#### struct `FPlaceableItem::FDragHandler`  
`struct FDragHandler : public TSharedFromThis<FDragHandler>`  
_L98-111_
- inherits: `TSharedFromThis<FDragHandler>`
- desc: An object which provides handling for Drags.
- L101 _public prototype_ `DECLARE_DELEGATE_RetVal(TSharedRef<FDragDropOperation>, FGetContentToDrag );`
- L104 _public member_ `FGetContentToDrag GetContentToDrag;` — a delegate thart returns the FDragDropOperation for the  the draggable
- L107 _public member_ `TSharedPtr<IToolTip> ToolTip;` — the tooltip for the draggable
- L110 _public member_ `const FSlateBrush* IconBrush;` — the const FSlateBrush* that provides the icon for the draggable

#### struct `FBuiltInPlacementCategories`  
`struct FBuiltInPlacementCategories`  
_L300-310_
- desc: Structure of built-in placement categories. Defined as functions to enable external use without linkage
- L302 _public function_ `static FName Favorites()`
- L303 _public function_ `static FName RecentlyPlaced()`
- L304 _public function_ `static FName Basic()`
- L305 _public function_ `static FName Lights()`
- L306 _public function_ `static FName Shapes()`
- L307 _public function_ `static FName Visual()`
- L308 _public function_ `static FName Volumes()`
- L309 _public function_ `static FName AllClasses()`

#### class `IPlacementModeModule`  
`class IPlacementModeModule : public IModuleInterface`  
_L312-499_
- inherits: `IModuleInterface`
- L322 _public function_ `static inline IPlacementModeModule& Get()` — Singleton-like access to this module's interface.  This is just for convenience! Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already. @return Returns singleton instance, loading the module on demand if needed
- L332 _public function_ `static inline bool IsAvailable()` — Checks to see if this module is loaded and ready.  It is only valid to call Get() if IsAvailable() returns true. @return True if the module is loaded and ready to use
- L340 _public prototype_ `virtual void AddToRecentlyPlaced( const TArray< UObject* >& Assets, UActorFactory* FactoryUsed = NULL ) = 0;` — Add the specified assets to the recently placed items list
- L341 _public function_ `virtual void AddToRecentlyPlaced(const TArray< UObject* >& Assets, TScriptInterface<IAssetFactoryInterface> FactoryUsed)`
- L351 _public prototype_ `virtual void AddToRecentlyPlaced( UObject* Asset, UActorFactory* FactoryUsed = NULL ) = 0;` — Add the specified asset to the recently placed items list
- L352 _public function_ `virtual void AddToRecentlyPlaced(UObject* Asset, TScriptInterface<IAssetFactoryInterface> FactoryUsed)`
- L362 _public prototype_ `virtual const TArray< FActorPlacementInfo >& GetRecentlyPlaced() const = 0;` — Get a copy of the recently placed items
- L367 _public prototype_ `DECLARE_EVENT(IPlacementModeModule, FOnPlacementModeCategoryListChanged);` — @return the event that is broadcast whenever the user facing list of placement mode categories gets modified
- L368 _public prototype_ `virtual FOnPlacementModeCategoryListChanged& OnPlacementModeCategoryListChanged() = 0;`
- L373 _public prototype_ `DECLARE_EVENT_OneParam( IPlacementModeModule, FOnPlacementModeCategoryRefreshed, FName );` — @return the event that is broadcast whenever a placement mode category is refreshed
- L374 _public prototype_ `virtual FOnPlacementModeCategoryRefreshed& OnPlacementModeCategoryRefreshed() = 0;`
- L379 _public prototype_ `DECLARE_EVENT_OneParam( IPlacementModeModule, FOnRecentlyPlacedChanged, const TArray< FActorPlacementInfo >& );` — @return the event that is broadcast whenever the list of recently placed assets changes
- L380 _public prototype_ `virtual FOnRecentlyPlacedChanged& OnRecentlyPlacedChanged() = 0;`
- L385 _public prototype_ `DECLARE_EVENT( IPlacementModeModule, FOnAllPlaceableAssetsChanged );` — @return the event that is broadcast whenever the list of all placeable assets changes
- L386 _public prototype_ `virtual FOnAllPlaceableAssetsChanged& OnAllPlaceableAssetsChanged() = 0;`
- L391 _public prototype_ `DECLARE_EVENT(IPlacementModeModule, FOnPlaceableItemFilteringChanged);` — @return the event that is broadcast whenever the filtering of placeable items changes (system filtering, not user filtering)
- L392 _public prototype_ `virtual FOnPlaceableItemFilteringChanged& OnPlaceableItemFilteringChanged() = 0;`
- L397 _public prototype_ `virtual TSharedRef<SWidget> CreatePlacementModeBrowser(TSharedRef<SDockTab> ParentTab) = 0;` — Creates the placement browser widget
- L407 _public prototype_ `virtual bool RegisterPlacementCategory(const FPlacementCategoryInfo& Info) = 0;` — Register a new category of placement items @param Info		Information pertaining to the category @return true on success, false on failure (probably if the category's unique handle is already in use)
- L414 _public prototype_ `virtual void UnregisterPlacementCategory(FName Handle) = 0;` — Unregister a previously registered category @param UniqueHandle	The unique handle of the category to unregister
- L422 _public prototype_ `virtual const FPlacementCategoryInfo* GetRegisteredPlacementCategory(FName UniqueHandle) const = 0;` — Retrieve an already registered category @param UniqueHandle	The unique handle of the category to retrieve @return Ptr to the category's information structure, or nullptr if it does not exit
- L425 _public prototype_ `virtual TSharedRef<FNamePermissionList>& GetCategoryPermissionList() = 0;` — Placement categories deny list
- L432 _public prototype_ `virtual void GetSortedCategories(TArray<FPlacementCategoryInfo>& OutCategories) const = 0;` — Get all placement categories that aren't denied, sorted by SortOrder @param OutCategories	The array to populate with registered category information
- L441 _public prototype_ `virtual TOptional<FPlacementModeID> RegisterPlaceableItem(FName CategoryName, const TSharedRef<FPlaceableItem>& Item) = 0;` — Register a new placeable item for the specified category @param Item			The placeable item to register @param CategoryName	Unique handle to the category in which to place this item @return Optional unique identifier for the registered item, or empty on failure (if the category doesn't exist)
- L448 _public prototype_ `virtual void UnregisterPlaceableItem(FPlacementModeID ID) = 0;` — Unregister a previously registered placeable item @param ID			Unique identifier for the item. Will have been obtained from a previous call to RegisterPlaceableItem
- L450 _public typedef_ `typedef TFunction<bool(const TSharedPtr<FPlaceableItem>&)> TPlaceableItemPredicate;`
- L459 _public prototype_ `virtual bool RegisterPlaceableItemFilter(TPlaceableItemPredicate Predicate, FName OwnerName) = 0;` — Registers system-level (not user) filtering for placeable items. An item is displayed if at least one of the predicate returns true or if there's none registered. @param Predicate Function that returns true if the passed item should be available @param OwnerName Name of the predicate owner @return False on failure to register the predicate because one already exists under the specified owner name
- L465 _public prototype_ `virtual void UnregisterPlaceableItemFilter(FName OwnerName) = 0;` — Registers system-level (not user) filtering for placeable items. An item is displayed if at least one of the predicate returns true or if there's none registered.
- L473 _public prototype_ `virtual void GetItemsForCategory(FName Category, TArray<TSharedPtr<FPlaceableItem>>& OutItems) const = 0;` — Get all items in a given category, system filtered, unsorted @param Category		The unique handle of the category to get items for @param OutItems		Array to populate with the items in this category
- L482 _public prototype_ `virtual void GetFilteredItemsForCategory(FName Category, TArray<TSharedPtr<FPlaceableItem>>& OutItems, TFunctionRef<bool(const TSharedPtr<FPlaceableItem>&)> Filter) const = 0;` — Get all items in a given category, system and user filtered, unsorted @param Category		The unique handle of the category to get items for @param OutItems		Array to populate with the items in this category @param Filter 		Filter predicate used to filter out items. Return true to pass the filter, false otherwise
- L491 _public prototype_ `virtual void GetItemsWithNamesForCategory( FName CategoryName, TArray<TSharedPtr<FPlaceableItem>>& OutItems, const TArray<FName>& ItemNames ) const = 0;` — Puts the items that should be shown for Category CategoryName in the OutItems array @param CategoryName the name of the category to get the items for @param OutItems the array of FPlaceableItems to put the items in @param ItemNames the names of the FPlaceableItems to get and put in the OutItems array
- L498 _public prototype_ `virtual void RegenerateItemsForCategory(FName Category) = 0;` — Instruct the category associated with the specified unique handle that it should regenerate its items @param Category		The unique handle of the category to get items for

#### Free symbols / members of external scopes

- L101 _delegate_ `DECLARE_DELEGATE_RetVal(TSharedRef<FDragDropOperation>, FGetContentToDrag );`
- L367 _delegate_ `DECLARE_EVENT(IPlacementModeModule, FOnPlacementModeCategoryListChanged);` — @return the event that is broadcast whenever the user facing list of placement mode categories gets modified
- L373 _delegate_ `DECLARE_EVENT_OneParam( IPlacementModeModule, FOnPlacementModeCategoryRefreshed, FName );` — @return the event that is broadcast whenever a placement mode category is refreshed
- L379 _delegate_ `DECLARE_EVENT_OneParam( IPlacementModeModule, FOnRecentlyPlacedChanged, const TArray< FActorPlacementInfo >& );` — @return the event that is broadcast whenever the list of recently placed assets changes
- L385 _delegate_ `DECLARE_EVENT( IPlacementModeModule, FOnAllPlaceableAssetsChanged );` — @return the event that is broadcast whenever the list of all placeable assets changes
- L391 _delegate_ `DECLARE_EVENT(IPlacementModeModule, FOnPlaceableItemFilteringChanged);` — @return the event that is broadcast whenever the filtering of placeable items changes (system filtering, not user filtering)

### `Source/Editor/PlacementMode/Public/PlacementModeModule.h` (Public)


#### struct `FPlacementCategory`  
`struct FPlacementCategory : FPlacementCategoryInfo`  
_L9-30_
- inherits: `FPlacementCategoryInfo`
- L11 _public function_ `FPlacementCategory(const FPlacementCategoryInfo& SourceInfo) : FPlacementCategoryInfo(SourceInfo)`
- L17 _public function_ `FPlacementCategory(FPlacementCategory&& In) : FPlacementCategoryInfo(MoveTemp(In)) , Items(MoveTemp(In.Items))`
- L22 _public function_ `FPlacementCategory& operator=(FPlacementCategory&& In)`
- L29 _public member_ `TMap<FGuid, TSharedPtr<FPlaceableItem>> Items;`

#### class `FPlacementModeModule`  
`class FPlacementModeModule : public IPlacementModeModule`  
_L34-163_
- inherits: `IPlacementModeModule`
- L38 _public prototype_ `FPlacementModeModule();`
- L43 _public prototype_ `virtual void StartupModule() override;` — Called right after the module's DLL has been loaded and the module object has been created
- L48 _public prototype_ `virtual void PreUnloadCallback() override;` — Called before the module is unloaded, right before the module object is destroyed.
- L50 _public prototype_ `DECLARE_DERIVED_EVENT(FPlacementModeModule, IPlacementModeModule::FOnPlacementModeCategoryListChanged, FOnPlacementModeCategoryListChanged);`
- L51 _public function_ `virtual FOnPlacementModeCategoryListChanged& OnPlacementModeCategoryListChanged() override`
- L53 _public prototype_ `DECLARE_DERIVED_EVENT(FPlacementModeModule, IPlacementModeModule::FOnPlacementModeCategoryRefreshed, FOnPlacementModeCategoryRefreshed);`
- L54 _public function_ `virtual FOnPlacementModeCategoryRefreshed& OnPlacementModeCategoryRefreshed() override`
- L56 _public prototype_ `DECLARE_DERIVED_EVENT(FPlacementModeModule, IPlacementModeModule::FOnRecentlyPlacedChanged, FOnRecentlyPlacedChanged);`
- L57 _public function_ `virtual FOnRecentlyPlacedChanged& OnRecentlyPlacedChanged() override`
- L59 _public prototype_ `DECLARE_DERIVED_EVENT(FPlacementModeModule, IPlacementModeModule::FOnAllPlaceableAssetsChanged, FOnAllPlaceableAssetsChanged);`
- L60 _public function_ `virtual FOnAllPlaceableAssetsChanged& OnAllPlaceableAssetsChanged() override`
- L62 _public prototype_ `DECLARE_DERIVED_EVENT(FPlacementModeModule, IPlacementModeModule::FOnPlaceableItemFilteringChanged, FOnPlaceableItemFilteringChanged);`
- L63 _public function_ `virtual FOnPlaceableItemFilteringChanged& OnPlaceableItemFilteringChanged() override`
- L68 _public prototype_ `virtual void AddToRecentlyPlaced(const TArray< UObject* >& PlacedObjects, UActorFactory* FactoryUsed = NULL) override;` — Add the specified assets to the recently placed items list
- L69 _public prototype_ `virtual void AddToRecentlyPlaced(const TArray< UObject* >& Assets, TScriptInterface<IAssetFactoryInterface> FactoryUsed) override;`
- L74 _public prototype_ `virtual void AddToRecentlyPlaced(UObject* Asset, UActorFactory* FactoryUsed = NULL) override;` — Add the specified asset to the recently placed items list
- L75 _public prototype_ `virtual void AddToRecentlyPlaced(UObject* Asset, TScriptInterface<IAssetFactoryInterface> FactoryUsed) override;`
- L80 _public function_ `virtual const TArray< FActorPlacementInfo >& GetRecentlyPlaced() const override` — Get a copy of the recently placed items list
- L85 _public prototype_ `virtual TSharedRef<SWidget> CreatePlacementModeBrowser(TSharedRef<SDockTab> ParentTab) override;`
- L87 _public prototype_ `virtual bool RegisterPlacementCategory(const FPlacementCategoryInfo& Info);`
- L89 _public function_ `virtual const FPlacementCategoryInfo* GetRegisteredPlacementCategory(FName CategoryName) const override`
- L94 _public prototype_ `virtual void UnregisterPlacementCategory(FName Handle);`
- L96 _public function_ `virtual TSharedRef<FNamePermissionList>& GetCategoryPermissionList() override`
- L98 _public prototype_ `virtual void GetSortedCategories(TArray<FPlacementCategoryInfo>& OutCategories) const;`
- L100 _public prototype_ `virtual TOptional<FPlacementModeID> RegisterPlaceableItem(FName CategoryName, const TSharedRef<FPlaceableItem>& InItem);`
- L102 _public prototype_ `virtual void UnregisterPlaceableItem(FPlacementModeID ID);`
- L104 _public prototype_ `virtual bool RegisterPlaceableItemFilter(TPlaceableItemPredicate Predicate, FName OwnerName) override;`
- L106 _public prototype_ `virtual void UnregisterPlaceableItemFilter(FName OwnerName) override;`
- L108 _public prototype_ `virtual void GetItemsForCategory(FName CategoryName, TArray<TSharedPtr<FPlaceableItem>>& OutItems) const;`
- L110 _public prototype_ `virtual void GetFilteredItemsForCategory(FName CategoryName, TArray<TSharedPtr<FPlaceableItem>>& OutItems, TFunctionRef<bool(const TSharedPtr<FPlaceableItem>&)> Filter) const;`
- L119 _public prototype_ `virtual void GetItemsWithNamesForCategory( FName CategoryName, TArray<TSharedPtr<FPlaceableItem>>& OutItems, const TArray<FName>& ItemNames ) const override;` — Puts the FPlaceableItem instances with names matching the FNames in ItemNames for the placement category CategoryName in the OutItems TArray @param CategoryName the name of the Placement category that contains the FPlaceableItems @param OutItems  the TArray to fill with the Items that match the names in ItemNames @param ItemNames the names of the FPlaceableItem instances to put in OutItems
- L121 _public prototype_ `virtual void RegenerateItemsForCategory(FName Category) override;`
- L125 _private prototype_ `void OnAssetRemoved(const FAssetData& );`
- L126 _private prototype_ `void OnAssetRenamed(const FAssetData& AssetData, const FString& OldObjectPath);`
- L127 _private prototype_ `void OnAssetAdded(const FAssetData& AssetData);`
- L128 _private prototype_ `void OnInitialAssetsScanComplete();`
- L130 _private prototype_ `void RefreshRecentlyPlaced();`
- L131 _private prototype_ `void RefreshVolumes();`
- L132 _private prototype_ `void RefreshAllPlaceableClasses();`
- L134 _private prototype_ `FGuid CreateID();`
- L135 _private prototype_ `FPlacementModeID CreateID(FName InCategory);`
- L137 _private prototype_ `bool PassesFilters(const TSharedPtr<FPlaceableItem>& Item) const;`
- L139 _private prototype_ `void OnCategoryPermissionListChanged();`
- L143 _private member_ `TMap<FName, FPlacementCategory> Categories;`
- L145 _private member_ `TSharedRef<FNamePermissionList> CategoryPermissionList;`
- L147 _private member_ `TMap<FName, TPlaceableItemPredicate> PlaceableItemPredicates;`
- L149 _private member_ `TArray< FActorPlacementInfo > RecentlyPlaced;`
- L150 _private member_ `FOnRecentlyPlacedChanged RecentlyPlacedChanged;`
- L152 _private member_ `FOnAllPlaceableAssetsChanged AllPlaceableAssetsChanged;`
- L153 _private member_ `FOnPlacementModeCategoryRefreshed PlacementModeCategoryRefreshed;`
- L154 _private member_ `FOnPlaceableItemFilteringChanged PlaceableItemFilteringChanged;`
- L155 _private member_ `FOnPlacementModeCategoryListChanged PlacementModeCategoryListChanged;`
- L157 _private member_ `TArray< TSharedPtr<FExtender> > ContentPaletteFiltersExtenders;`
- L158 _private member_ `TArray< TSharedPtr<FExtender> > PaletteExtenders;`
- L162 _private member_ `TMap<FActorPlacementInfo, TWeakPtr<FPlaceableItem>> ManuallyCreatedPlaceableItems;` — When users explicitly add placeable items, they may add custom icons/descriptions, so we need to store extra data to be able to recreate the placeable item in "recently placed"

#### Free symbols / members of external scopes

- L32 _prototype_ `static TOptional<FLinearColor> GetBasicShapeColorOverride();`
- L50 _delegate_ `DECLARE_DERIVED_EVENT(FPlacementModeModule, IPlacementModeModule::FOnPlacementModeCategoryListChanged, FOnPlacementModeCategoryListChanged);`
- L53 _delegate_ `DECLARE_DERIVED_EVENT(FPlacementModeModule, IPlacementModeModule::FOnPlacementModeCategoryRefreshed, FOnPlacementModeCategoryRefreshed);`
- L56 _delegate_ `DECLARE_DERIVED_EVENT(FPlacementModeModule, IPlacementModeModule::FOnRecentlyPlacedChanged, FOnRecentlyPlacedChanged);`
- L59 _delegate_ `DECLARE_DERIVED_EVENT(FPlacementModeModule, IPlacementModeModule::FOnAllPlaceableAssetsChanged, FOnAllPlaceableAssetsChanged);`
- L62 _delegate_ `DECLARE_DERIVED_EVENT(FPlacementModeModule, IPlacementModeModule::FOnPlaceableItemFilteringChanged, FOnPlaceableItemFilteringChanged);`
