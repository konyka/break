# Editor / ContentBrowserData

- module root: `Source/Editor/ContentBrowserData`
- headers: 14; symbols: 812
- symbol kinds: class=27, delegate=13, enum=10, enumerator=53, function=54, macro=8, member=151, namespace=3, prototype=456, struct=19, typedef=3, variable=15
- PrivateDependencyModuleNames: Slate, SlateCore
- PublicDependencyModuleNames: Core, CoreUObject, EditorSubsystem, Engine, Projects, UnrealEd
- PublicIncludePathModuleNames: CollectionManager

### `Source/Editor/ContentBrowserData/Private/ContentBrowserVirtualFolderDataPayload.h` (Private)


#### class `FContentBrowserVirtualFolderItemDataPayload`  
`class FContentBrowserVirtualFolderItemDataPayload : public IContentBrowserItemDataPayload`  
_L7-17_
- inherits: `IContentBrowserItemDataPayload`
- L10 _public function_ `explicit FContentBrowserVirtualFolderItemDataPayload (bool InIsCustomVirtual) : bIsCustomVirtualFolder(InIsCustomVirtual)`
- L16 _private member_ `bool bIsCustomVirtualFolder;`

### `Source/Editor/ContentBrowserData/Public/ContentBrowserDataDragDropOp.h` (Public)


#### struct `FThumbnailOverrideParams`  
`struct FThumbnailOverrideParams`  
_L24-36_
- desc: Additional params for FContentBrowserDataDragDropOp to override the thumbnail used if dragging only folders
- L26 _public function_ `FThumbnailOverrideParams()`
- L29 _public member_ `FName FolderBrushName = NAME_None;` — Folder brush name to use
- L32 _public member_ `FName FolderShadowBrushName = NAME_None;` — Folder shadow brush name to use
- L35 _public member_ `FLinearColor FolderColorOverride = FLinearColor::Gray;` — Override color for the final brush

#### class `FContentBrowserDataDragDropOp`  
`class FContentBrowserDataDragDropOp : public FAssetDragDropOp`  
_L38-89_
- inherits: `FAssetDragDropOp`
- L41 _public prototype_ `DRAG_DROP_OPERATOR_TYPE(FContentBrowserDataDragDropOp, FAssetDragDropOp) static TSharedRef<FContentBrowserDataDragDropOp> New(TArrayView<const FContentBrowserItem> InDraggedItems, FThumbnailOverrideParams InThumbnailOverrideParams = FThumbnailOverrideParams());`
- L45 _public prototype_ `static TSharedRef<FContentBrowserDataDragDropOp> Legacy_New(TArrayView<const FAssetData> InAssetData, TArrayView<const FString> InAssetPaths = TArrayView<const FString>(), UActorFactory* InActorFactory = nullptr);`
- L47 _public function_ `const TArray<FContentBrowserItem>& GetDraggedItems() const`
- L52 _public function_ `const TArray<FContentBrowserItem>& GetDraggedFiles() const`
- L57 _public function_ `const TArray<FContentBrowserItem>& GetDraggedFolders() const`
- L63 _private prototype_ `void Init(TArrayView<const FContentBrowserItem> InDraggedItems);`
- L64 _private prototype_ `void LegacyInit(TArrayView<const FAssetData> InAssetData, TArrayView<const FString> InAssetPaths, UActorFactory* ActorFactory);`
- L65 _private prototype_ `virtual void InitThumbnail() override;`
- L67 _private prototype_ `virtual bool HasFiles() const override;`
- L68 _private prototype_ `virtual bool HasFolders() const override;`
- L70 _private prototype_ `virtual int32 GetTotalCount() const override;`
- L71 _private prototype_ `virtual FText GetFirstItemText() const override;`
- L74 _private prototype_ `bool ShouldOverrideThumbnailWidget() const;` — Return whether or not it should override the thumbnail widget
- L77 _private prototype_ `TSharedPtr<SWidget> GetFolderWidget() const;` — Return the folder widget or nullptr if the BrushName is not valid
- L80 _private prototype_ `TSharedPtr<SWidget> GetFolderWidgetDragAndDrop() const;` — Return the folder widget for DragAndDrop or nullptr if there is no basic folder widget
- L83 _private member_ `FName FolderBrushName;`
- L84 _private member_ `FName FolderShadowBrushName;`
- L85 _private member_ `FLinearColor FolderColorOverride = FLinearColor::Gray;`
- L86 _private member_ `TArray<FContentBrowserItem> DraggedItems;`
- L87 _private member_ `TArray<FContentBrowserItem> DraggedFiles;`
- L88 _private member_ `TArray<FContentBrowserItem> DraggedFolders;`

#### Free symbols / members of external scopes

- L16 _macro_ `#define UE_API CONTENTBROWSERDATA_API`

### `Source/Editor/ContentBrowserData/Public/ContentBrowserDataFilter.h` (Public)


#### enum `EContentBrowserItemTypeFilter`  
`enum class EContentBrowserItemTypeFilter : uint8`  
_L35-41_
- reflection: `UENUM(Flags)`
- desc: Flags controlling which item types should be included Generally matches EContentBrowserItemFlags::Type_MASK
- L37 _public enumerator_ `IncludeNone = 0`
- L38 _public enumerator_ `IncludeFolders = 1<<0`
- L39 _public enumerator_ `IncludeFiles = 1<<1`
- L40 _public enumerator_ `IncludeAll = IncludeFolders | IncludeFiles`

#### enum `EContentBrowserItemCategoryFilter`  
`enum class EContentBrowserItemCategoryFilter : uint8`  
_L49-58_
- reflection: `UENUM(Flags)`
- desc: Flags controlling which item categories should be included Generally matches EContentBrowserItemFlags::Category_MASK
- L51 _public enumerator_ `IncludeNone = 0`
- L52 _public enumerator_ `IncludeAssets = 1<<0`
- L53 _public enumerator_ `IncludeClasses = 1<<1`
- L54 _public enumerator_ `IncludeCollections = 1<<2`
- L55 _public enumerator_ `IncludeRedirectors = 1 << 3`
- L56 _public enumerator_ `IncludeMisc = 1 << 4`
- L57 _public enumerator_ `IncludeAll = IncludeAssets | IncludeClasses | IncludeCollections | IncludeRedirectors | IncludeMisc`

#### enum `EContentBrowserItemAttributeFilter`  
`enum class EContentBrowserItemAttributeFilter : uint8`  
_L63-72_
- reflection: `UENUM(Flags)`
- desc: Flags controlling which item attributes should be included
- L65 _public enumerator_ `IncludeNone = 0`
- L66 _public enumerator_ `IncludeProject = 1<<0`
- L67 _public enumerator_ `IncludeEngine = 1<<1`
- L68 _public enumerator_ `IncludePlugins = 1<<2`
- L69 _public enumerator_ `IncludeDeveloper = 1<<3`
- L70 _public enumerator_ `IncludeLocalized = 1<<4`
- L71 _public enumerator_ `IncludeAll = IncludeProject | IncludeEngine | IncludePlugins | IncludeDeveloper | IncludeLocalized`

#### class `IContentBrowserHideFolderIfEmptyFilter`  
`class IContentBrowserHideFolderIfEmptyFilter`  
_L79-86_
- desc: Structure used to filter folders by their path @note All implementations of this filter should copy all dependent data on creation such that all calls to HideFolderIfEmpty for a given path return the same value for a instance of the implementation.
- L82 _public prototype_ `IContentBrowserHideFolderIfEmptyFilter() = default;`
- L83 _public prototype_ `virtual ~IContentBrowserHideFolderIfEmptyFilter() = default;`
- L85 _public prototype_ `virtual bool HideFolderIfEmpty(FName Path, FStringView PathString) const = 0;`

#### struct `FContentBrowserDataFilterList`  
`struct FContentBrowserDataFilterList`  
_L92-172_
- desc: A list of typed filter structs and their associated data. This allows systems to add new filter types that the core Content Browser data module doesn't know about.
- L96 _public prototype_ `FContentBrowserDataFilterList() = default;` — Constructor
- L99 _public prototype_ `FContentBrowserDataFilterList(const FContentBrowserDataFilterList& InOther);` — Copy support
- L100 _public prototype_ `FContentBrowserDataFilterList& operator=(const FContentBrowserDataFilterList& InOther);`
- L103 _public prototype_ `FContentBrowserDataFilterList(FContentBrowserDataFilterList&&) = default;` — Move support
- L104 _public prototype_ `FContentBrowserDataFilterList& operator=(FContentBrowserDataFilterList&&) = default;`
- L108 _public function_ `template <typename T> T& FindOrAddFilter()` — Find the filter associated with the given type, or add a default instance if it doesn't exist in the list
- L112 _public prototype_ `void* FindOrAddFilter(const UScriptStruct* InFilterType);`
- L116 _public function_ `template <typename T> void SetFilter(const T& InFilter)` — Set the filter associated with the given type, replacing any instance of this type that may exist in the list
- L120 _public prototype_ `void SetFilter(const UScriptStruct* InFilterType, const void* InFilterData);`
- L124 _public function_ `template <typename T> const T* FindFilter() const` — Find the filter associated with the given type, if it exists in the list
- L128 _public prototype_ `const void* FindFilter(const UScriptStruct* InFilterType) const;`
- L132 _public function_ `template <typename T> T* FindMutableFilter()` — Find the filter associated with the given type, if it exists in the list
- L139 _public function_ `template <typename T> const T& GetFilter() const` — Get the filter associated with the given type, asserting if it doesn't exist in the list
- L148 _public function_ `template <typename T> T& GetMutableFilter()` — Get the filter associated with the given type, asserting if it doesn't exist in the list
- L155 _public function_ `template <typename T> void RemoveFilter()` — Remove the filter associated with the given type
- L159 _public prototype_ `void RemoveFilter(const UScriptStruct* InFilterType);`
- L162 _public prototype_ `void ClearFilters();` — Remove all filters in the list
- L164 _public prototype_ `TArray<const UScriptStruct*> GetFilterTypes() const;`
- L168 _private prototype_ `void SetTo(const FContentBrowserDataFilterList& InOther);` — Set the contents of this list to be a deep copy of the contents of the other list
- L171 _private member_ `TArray<FStructOnScope> TypedFilters;` — Array of typed filter structs

#### struct `FContentBrowserDataFilterCacheID`  
`struct FContentBrowserDataFilterCacheID`  
_L174-196_
- L177 _public function_ `operator bool() const`
- L182 _public function_ `bool IsSet() const`
- L190 _private member_ `int64 ID = INDEX_NONE;`

#### struct `FContentBrowserDataFilter`  
`struct FContentBrowserDataFilter`  
_L203-229_
- reflection: `USTRUCT(BlueprintType)`
- desc: A filter used to control what is returned from Content Browser data queries. @note The compiled version of this, FContentBrowserDataCompiledFilter, is produced via UContentBrowserDataSubsystem::CompileFilter.
- L210 _public member_ `bool bRecursivePaths = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="ContentBrowser")` — Whether we should include sub-paths in this query
- L214 _public member_ `EContentBrowserItemTypeFilter ItemTypeFilter = EContentBrowserItemTypeFilter::IncludeAll;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="ContentBrowser")` — Flags controlling which item types should be included in this query
- L218 _public member_ `EContentBrowserItemCategoryFilter ItemCategoryFilter = EContentBrowserItemCategoryFilter::IncludeAll;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="ContentBrowser")` — Flags controlling which item categories should be included in this query
- L222 _public member_ `EContentBrowserItemAttributeFilter ItemAttributeFilter = EContentBrowserItemAttributeFilter::IncludeAll;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="ContentBrowser")` — Flags controlling which item attributes should be included in this query
- L225 _public member_ `FContentBrowserDataFilterList ExtraFilters;` — A list of extra filter structs to be interpreted by the Content Browser data sources
- L228 _public member_ `FContentBrowserDataFilterCacheID CacheID;` — An optional id used by the data sources to cache and reuse some data when compiling the filter(s)

#### struct `FContentBrowserDataCompiledFilter`  
`struct FContentBrowserDataCompiledFilter`  
_L235-248_
- desc: A filter used to control what is returned from Content Browser data queries. @note The source version of this, FContentBrowserDataFilter, is used with UContentBrowserDataSubsystem::CompileFilter to produce a compiled filter.
- L238 _public member_ `EContentBrowserItemTypeFilter ItemTypeFilter = EContentBrowserItemTypeFilter::IncludeAll;` — Flags controlling which item types should be included in this query
- L241 _public member_ `EContentBrowserItemCategoryFilter ItemCategoryFilter = EContentBrowserItemCategoryFilter::IncludeAll;` — Flags controlling which item categories should be included in this query
- L244 _public member_ `EContentBrowserItemAttributeFilter ItemAttributeFilter = EContentBrowserItemAttributeFilter::IncludeAll;` — Flags controlling which item attributes should be included in this query
- L247 _public member_ `TSortedMap<const UContentBrowserDataSource*, FContentBrowserDataFilterList> CompiledFilters;` — Per data-source compiled filter structs - typically optimized for both search queries and per-item queries

#### struct `FContentBrowserDataObjectFilter`  
`struct FContentBrowserDataObjectFilter`  
_L255-277_
- reflection: `USTRUCT(BlueprintType)`
- desc: Data used to filter object instances by their name and tags. @note This will typically limit your query to returning assets.
- L262 _public member_ `TArray<FName> ObjectNamesToInclude;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="ContentBrowser")` — Array of object names that should be included in this query
- L266 _public member_ `TArray<FName> ObjectNamesToExclude;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="ContentBrowser")` — Array of object names that should be excluded from this query
- L270 _public member_ `bool bOnDiskObjectsOnly = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="ContentBrowser")` — Whether we should only include on-disk objects (ignoring those that exist only in memory)
- L273 _public member_ `TMultiMap<FName, TOptional<FString>> TagsAndValuesToInclude;` — Map of object tags (with optional values) that should be included in this query
- L276 _public member_ `TMultiMap<FName, TOptional<FString>> TagsAndValuesToExclude;` — Map of object tags (with optional values) that should be excluded from this query

#### struct `FContentBrowserDataPackageFilter`  
`struct FContentBrowserDataPackageFilter`  
_L284-315_
- reflection: `USTRUCT(BlueprintType)`
- desc: Data used to filter object instances by their package. @note This will typically limit your query to returning assets.
- L291 _public member_ `TArray<FName> PackageNamesToInclude;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="ContentBrowser")` — Array of package names that should be included in this query
- L295 _public member_ `TArray<FName> PackageNamesToExclude;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="ContentBrowser")` — Array of package names that should be excluded from this query
- L299 _public member_ `TArray<FName> PackagePathsToInclude;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="ContentBrowser")` — Array of package paths that should be included in this query
- L303 _public member_ `TArray<FName> PackagePathsToExclude;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="ContentBrowser")` — Array of package paths that should be excluded from this query
- L307 _public member_ `bool bRecursivePackagePathsToInclude = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="ContentBrowser")` — Whether we should include inclusive package sub-paths in this query
- L311 _public member_ `bool bRecursivePackagePathsToExclude = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="ContentBrowser")` — Whether we should include exclusive package sub-paths in this query
- L314 _public member_ `TSharedPtr<FPathPermissionList> PathPermissionList;` — Optional set of additional path filtering

#### struct `FContentBrowserDataClassFilter`  
`struct FContentBrowserDataClassFilter`  
_L322-345_
- reflection: `USTRUCT(BlueprintType)`
- desc: Data used to filter object instances by their class. @note This will typically limit your query to returning assets.
- L329 _public member_ `TArray<FString> ClassNamesToInclude;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="ContentBrowser")` — Array of class names that should be included in this query
- L333 _public member_ `TArray<FString> ClassNamesToExclude;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="ContentBrowser")` — Array of class names that should be excluded from this query
- L337 _public member_ `bool bRecursiveClassNamesToInclude = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="ContentBrowser")` — Whether we should include inclusive sub-classes in this query
- L341 _public member_ `bool bRecursiveClassNamesToExclude = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="ContentBrowser")` — Whether we should include exclusive sub-classes in this query
- L344 _public member_ `TSharedPtr<FPathPermissionList> ClassPermissionList;` — Optional set of additional class filtering

#### struct `FContentBrowserDataCollectionFilter`  
`struct FContentBrowserDataCollectionFilter`  
_L352-378_
- reflection: `USTRUCT(BlueprintType)`
- desc: Data used to filter items by their collection. @note This will typically limit your query to items that support being inside a collection.
- L357 _public prototype_ `FContentBrowserDataCollectionFilter() = default;`
- L361 _public prototype_ `FContentBrowserDataCollectionFilter(const FContentBrowserDataCollectionFilter&) = default;`
- L362 _public prototype_ `FContentBrowserDataCollectionFilter(FContentBrowserDataCollectionFilter&&) = default;`
- L364 _public prototype_ `FContentBrowserDataCollectionFilter& operator=(const FContentBrowserDataCollectionFilter&) = default;`
- L365 _public prototype_ `FContentBrowserDataCollectionFilter& operator=(FContentBrowserDataCollectionFilter&&) = default;`
- L370 _public member_ `TArray<FCollectionRef> Collections;` — Array of collections to include in this query
- L373 _public member_ `TArray<FCollectionNameType> SelectedCollections;` — `UE_DEPRECATED(5.6, "Use Collections instead.")`
- L377 _public member_ `bool bIncludeChildCollections = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="ContentBrowser")` — Whether we should include child collections in this query

#### struct `FContentBrowserFolderContentsFilter`  
`struct FContentBrowserFolderContentsFilter`  
_L383-397_
- desc: Structure used to optionally filter folders by their broad contents
- L386 _public member_ `EContentBrowserItemTypeFilter ItemTypeFilter = EContentBrowserItemTypeFilter::IncludeAll;`
- L388 _public member_ `EContentBrowserItemCategoryFilter ItemCategoryFilter = EContentBrowserItemCategoryFilter::IncludeAll;`
- L390 _public member_ `EContentBrowserItemAttributeFilter ItemAttributeFilter = EContentBrowserItemAttributeFilter::IncludeAll;`
- L396 _public member_ `TSharedPtr<IContentBrowserHideFolderIfEmptyFilter> HideFolderIfEmptyFilter;` — Used to filter out empty folders. All empty folders will get filtered out if this TSharedPtr is null. Intended for content folders that always exist but do not generally contain assets, such as /Game/Collections

#### struct `FContentBrowserDataUnsupportedClassFilter`  
`struct FContentBrowserDataUnsupportedClassFilter`  
_L404-412_
- reflection: `USTRUCT()`
- desc: Data used to tell the content browser to show the item that doesn't pass the class permission list as a unsupported asset @note This will restrict user interaction with those asset in the content browser and only affect the asset in the folders specified in the permission list
- L409 _public member_ `TSharedPtr<FPathPermissionList> ClassPermissionList;`
- L411 _public member_ `TSharedPtr<FPathPermissionList> FolderPermissionList;`

#### struct `FContentBrowserDataFilterCacheIDOwner`  
`struct FContentBrowserDataFilterCacheIDOwner`  
_L421-472_
- desc: ID used by the data sources to cache some data between the filter compilations How use the filter compilation cache. 1) Initialize the id by using the UContentBrowserDataSubsystem once. 2) When compiling the filters pass the Cache ID Owner to the cacheID of the ContentBrowserDataFilter. 3) When the filter settings change call RemoveUnusedCachedData to clean the cache and to remove the potential invalid data.
- L424 _public function_ `operator FContentBrowserDataFilterCacheID() const`
- L431 _public prototype_ `FContentBrowserDataFilterCacheIDOwner() = default;`
- L433 _public function_ `FContentBrowserDataFilterCacheIDOwner(FContentBrowserDataFilterCacheIDOwner&& Other) : ID(Other.ID) , DataSource(MoveTemp(Other.DataSource))`
- L441 _public function_ `FContentBrowserDataFilterCacheIDOwner& operator=(FContentBrowserDataFilterCacheIDOwner&& Other)`
- L451 _public function_ `~FContentBrowserDataFilterCacheIDOwner()`
- L456 _public prototype_ `FContentBrowserDataFilterCacheIDOwner(const FContentBrowserDataFilterCacheIDOwner&) = delete;`
- L457 _public prototype_ `FContentBrowserDataFilterCacheIDOwner& operator=(const FContentBrowserDataFilterCacheIDOwner&) = delete;`
- L459 _public prototype_ `void Initialaze(UContentBrowserDataSubsystem* InContentBrowserDataSubsystem);`
- L461 _public prototype_ `void RemoveUnusedCachedData(TArrayView<const FName> InVirtualPathsInUse, const FContentBrowserDataFilter& DataFilter) const;`
- L463 _public prototype_ `void ClearCachedData() const;`
- L465 _public prototype_ `void Reset();`
- L470 _private member_ `int64 ID = INDEX_NONE;`
- L471 _private member_ `TWeakObjectPtr<UContentBrowserDataSubsystem> DataSource;`

#### Free symbols / members of external scopes

- L23 _macro_ `#define UE_API CONTENTBROWSERDATA_API`
- L42 _prototype_ `ENUM_CLASS_FLAGS(EContentBrowserItemTypeFilter);`
- L59 _prototype_ `ENUM_CLASS_FLAGS(EContentBrowserItemCategoryFilter);`
- L73 _prototype_ `ENUM_CLASS_FLAGS(EContentBrowserItemAttributeFilter);`
- L192 _function_ `friend uint32 GetTypeHash(const FContentBrowserDataFilterCacheID& CacheID)`

### `Source/Editor/ContentBrowserData/Public/ContentBrowserDataLegacyBridge.h` (Public)


#### struct `FContentBrowserDataLegacyFilter`  
`struct FContentBrowserDataLegacyFilter`  
_L28-34_
- reflection: `USTRUCT()`
- desc: Filter data used to provide legacy information to the asset data source
- L33 _public member_ `FOnGetCustomSourceAssets OnGetCustomSourceAssets;`

#### Free symbols / members of external scopes

- L21 _delegate_ `DECLARE_DELEGATE_TwoParams(FOnGetCustomSourceAssets, const FARFilter& , TArray<FAssetData>& );` — Called to add extra asset data to the asset view, to display virtual assets. These get treated similar to Class assets
- L21 _prototype_ `DECLARE_DELEGATE_TwoParams(FOnGetCustomSourceAssets, const FARFilter& , TArray<FAssetData>& );` — Called to add extra asset data to the asset view, to display virtual assets. These get treated similar to Class assets
- L24 _delegate_ `DECLARE_DELEGATE_FiveParams(FOnCreateNewAsset, const FName , const FName , UClass* , UFactory* , UContentBrowserDataMenuContext_AddNewMenu::FOnBeginItemCreation );` — Called to begin user controlled asset creation via the asset data source (if available)
- L24 _prototype_ `DECLARE_DELEGATE_FiveParams(FOnCreateNewAsset, const FName , const FName , UClass* , UFactory* , UContentBrowserDataMenuContext_AddNewMenu::FOnBeginItemCreation );` — Called to begin user controlled asset creation via the asset data source (if available)
- L36 _namespace_ `namespace ContentBrowserDataLegacyBridge`
- L40 _prototype_ `FOnCreateNewAsset& OnCreateNewAsset();` (scope `ContentBrowserDataLegacyBridge`) — Called to begin user controlled asset creation via the asset data source (if available)

### `Source/Editor/ContentBrowserData/Public/ContentBrowserDataMenuContexts.h` (Public)


#### enum `EContentBrowserDataMenuContext_AddNewMenuDomain`  
`enum class EContentBrowserDataMenuContext_AddNewMenuDomain : uint8`  
_L14-19_
- reflection: `UENUM()`
- L16 _public enumerator_ `Toolbar`
- L17 _public enumerator_ `AssetView`
- L18 _public enumerator_ `PathView`

#### class `UContentBrowserDataMenuContext_AddNewMenu`  
`class UContentBrowserDataMenuContext_AddNewMenu : public UObject`  
_L22-45_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject`
- L27 _public prototype_ `DECLARE_DELEGATE_OneParam(FOnBeginItemCreation, const FContentBrowserItemDataTemporaryContext&);`
- L30 _public member_ `TArray<FName> SelectedPaths;` — `UPROPERTY(BlueprintReadOnly, Category = ContentBrowser)`
- L34 _public member_ `bool bContainsValidPackagePath = false;` — `UPROPERTY(BlueprintReadOnly, Category = ContentBrowser)` — At least one of the selected paths maps to a mounted content root
- L37 _public member_ `bool bCanBeModified = true;` — `UPROPERTY(BlueprintReadOnly, Category = ContentBrowser)`
- L40 _public member_ `EContentBrowserDataMenuContext_AddNewMenuDomain OwnerDomain = EContentBrowserDataMenuContext_AddNewMenuDomain::Toolbar;` — `UPROPERTY(BlueprintReadOnly, Category = ContentBrowser)`
- L42 _public member_ `FOnBeginItemCreation OnBeginItemCreation;`
- L44 _public member_ `const FContentBrowserInstanceConfig* OwningInstanceConfig;`

#### class `UContentBrowserDataMenuContext_FolderMenu`  
`class UContentBrowserDataMenuContext_FolderMenu : public UObject`  
_L48-60_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject`
- L54 _public member_ `TArray<FContentBrowserItem> SelectedItems;` — `UPROPERTY(BlueprintReadOnly, Category=ContentBrowser)`
- L57 _public member_ `bool bCanBeModified = true;` — `UPROPERTY(BlueprintReadOnly, Category = ContentBrowser)`
- L59 _public member_ `TWeakPtr<SWidget> ParentWidget;`

#### class `UContentBrowserDataMenuContext_FileMenu`  
`class UContentBrowserDataMenuContext_FileMenu : public UObject`  
_L63-97_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject`
- L68 _public prototype_ `DECLARE_DELEGATE_OneParam(FOnShowInPathsView, TArrayView<const FContentBrowserItem>);`
- L70 _public prototype_ `DECLARE_DELEGATE(FOnRefreshView);`
- L73 _public member_ `TArray<FContentBrowserItem> SelectedItems;` — `UPROPERTY(BlueprintReadOnly, Category = ContentBrowser)`
- L75 _public member_ `TArray<FCollectionRef> CollectionSources;`
- L78 _public member_ `TArray<FCollectionNameType> SelectedCollections;` — `UE_DEPRECATED(5.6, "Use CollectionSources instead.")`
- L81 _public member_ `bool bCanBeModified = true;` — `UPROPERTY(BlueprintReadOnly, Category = ContentBrowser)`
- L84 _public member_ `bool bCanView = true;` — `UPROPERTY(BlueprintReadOnly, Category = ContentBrowser)`
- L87 _public member_ `bool bHasCookedPackages = false;` — `UPROPERTY(BlueprintReadOnly, Category = ContentBrowser)`
- L90 _public member_ `bool bContainsUnsupportedAssets = true;` — `UPROPERTY(BlueprintReadOnly, Category = ContentBrowser)`
- L92 _public member_ `TWeakPtr<SWidget> ParentWidget;`
- L94 _public member_ `FOnShowInPathsView OnShowInPathsView;`
- L96 _public member_ `FOnRefreshView OnRefreshView;`

#### class `UContentBrowserDataMenuContext_DragDropMenu`  
`class UContentBrowserDataMenuContext_DragDropMenu : public UObject`  
_L100-118_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject`
- L106 _public member_ `FContentBrowserItem DropTargetItem;` — `UPROPERTY(BlueprintReadOnly, Category = ContentBrowser)`
- L109 _public member_ `TArray<FContentBrowserItem> DraggedItems;` — `UPROPERTY(BlueprintReadOnly, Category = ContentBrowser)`
- L112 _public member_ `bool bCanMove = true;` — `UPROPERTY(BlueprintReadOnly, Category = ContentBrowser)`
- L115 _public member_ `bool bCanCopy = true;` — `UPROPERTY(BlueprintReadOnly, Category = ContentBrowser)`
- L117 _public member_ `TWeakPtr<SWidget> ParentWidget;`

#### Free symbols / members of external scopes

- L27 _delegate_ `DECLARE_DELEGATE_OneParam(FOnBeginItemCreation, const FContentBrowserItemDataTemporaryContext&);`
- L68 _delegate_ `DECLARE_DELEGATE_OneParam(FOnShowInPathsView, TArrayView<const FContentBrowserItem>);`
- L70 _delegate_ `DECLARE_DELEGATE(FOnRefreshView);`

### `Source/Editor/ContentBrowserData/Public/ContentBrowserDataSource.h` (Public)


#### class `UContentBrowserDataSource`  
`class UContentBrowserDataSource : public UObject, public IModularFeature`  
_L142-990_
- reflection: `UCLASS(MinimalAPI, Abstract, Transient)`
- inherits: `UObject,IModularFeature`
- desc: A common implementation of a "do nothing" data source for the Content Browser. You should derive from this type to create new data sources for the Content Browser, overriding any required functionality and validation logic. Data sources create and operate on FContentBrowserItemData instances that represent the folders and files within each data source. FContentBrowserItemData itself is a concrete type, so extensibility is handled via the IContentBrowserItemDataPayload interface, which can be used to store any data source defined payload data that is required to operate on the underlying thing that the item represents. This is the only API you need to implement to create a data source, as each FContentBrowserItemData instance knows which data source owns it, and uses that information to pass itself back into the correct data source instance when asked to perform actions or validation. In that sense you can think of this like a C API, where the data source returns an opaque object that is later passed back into the data source functions so that they can interpret the opaque object and provide functionality for it.
- L148 _public prototype_ `virtual void BeginDestroy() override final;`
- L153 _public prototype_ `static FName GetModularFeatureTypeName();` — Get the name used when registering data source modular feature instances for use with the Content Browser Data Subsystem.
- L159 _public prototype_ `void RegisterDataSource();` — Register this data source instance for use with the Content Browser Data Subsystem. @note This does not activate the data source. @see the EnabledDataSources array in the Content Browser Data Subsystem for more information on activation.
- L164 _public prototype_ `void UnregisterDataSource();` — Unregister this data source instance from the Content Browser Data Subsystem.
- L170 _public prototype_ `void SetDataSink(IContentBrowserItemDataSink* InDataSink);` — Set the data sink that can be used to communicate with the Content Browser Data Subsystem. This is set to a valid instance when the data source is activated, and set to null when it is deactivated.
- L176 _public prototype_ `bool IsInitialized() const;` — True if this data source is currently initialized. A data source should be initialized before it is registered.
- L184 _public prototype_ `void Initialize(const bool InAutoRegister = true);` — Initialize this data source instance, optionally registering it once the initialization has finished (@see RegisterDataSource). @note This function is non-virtual because its signature may change on derived types, and so should be called directly on an instance of the correct type. @param InAutoRegister True to automatically register this instance once initialization has finished.
- L190 _public prototype_ `virtual void Shutdown();` — Shutdown this data source instance. @note This is called during the BeginDestroy phase of object destruction.
- L196 _public prototype_ `virtual void Tick(const float InDeltaTime);` — Tick this data source instance. @note Called once every 0.1 seconds, prior to the Content Browser Data Subsystem emitting any pending item update notifications.
- L201 _public prototype_ `bool IsVirtualPathUnderMountRoot(const FName InPath) const;` — Test whether the given virtual path is under the virtual mount root that was passed to Initialize. @note This also returns true if the given virtual path *is* the virtual mount root.
- L213 _public prototype_ `virtual void CompileFilter(const FName InPath, const FContentBrowserDataFilter& InFilter, FContentBrowserDataCompiledFilter& OutCompiledFilter);` — Given a path and a data filter, produce an optimized filter that can be used to efficiently enumerate items that match it, and also query whether an item would pass it. @note This function *must not* block waiting on content discovery! It should use the current state as known at this point in time. @note A compiled filter should be short-lived (no more than 1 frame). @see EnumerateItemsMatchingFilter and DoesItemPassFilter. @param InPath The virtual path to search for items under. @param InFilter Rules describing how items should be filtered. @param OutCompiledFilter The compiled filter instance to fill with the result.
- L224 _public prototype_ `virtual void EnumerateItemsMatchingFilter(const FContentBrowserDataCompiledFilter& InFilter, TFunctionRef<bool(FContentBrowserItemData&&)> InCallback);` — Enumerate items that match the given compiled filter, invoking the callback for each matching item. @note This function *must not* block waiting on content discovery! It should use the current state as known at this point in time. @see CompileFilter. @param InFilter The compiled filter used to find matching items. @param InCallback The function to invoke for each matching item (return true to continue enumeration). @param InSink Parameter provided to receive output as either a callback or an array.
- L225 _public prototype_ `virtual void EnumerateItemsMatchingFilter(const FContentBrowserDataCompiledFilter& InFilter, const TGetOrEnumerateSink<FContentBrowserItemData>& InSink);`
- L236 _public prototype_ `virtual void EnumerateItemsAtPath(const FName InPath, const EContentBrowserItemTypeFilter InItemTypeFilter, TFunctionRef<bool(FContentBrowserItemData&&)> InCallback);` — Enumerate items that have the given virtual path, optionally filtering by type, and invoking the callback for each matching item. @note This function *must not* block waiting on content discovery! It should use the current state as known at this point in time. @param InPath The virtual path to find items for. @param InItemTypeFilter The types of items we want to find. @param InCallback The function to invoke for each matching item (return true to continue enumeration). @param InSink Parameter provided to receive output as either a callback or an array.
- L237 _public prototype_ `virtual void EnumerateItemsAtPath(const FName InPath, const EContentBrowserItemTypeFilter InItemTypeFilter, const TGetOrEnumerateSink<FContentBrowserItemData>& InSink);`
- L247 _public prototype_ `virtual bool EnumerateItemsAtPaths(const TArrayView<FContentBrowserItemPath> InPaths, const EContentBrowserItemTypeFilter InItemTypeFilter, TFunctionRef<bool(FContentBrowserItemData&&)> InCallback);` — Enumerate the items (folders and/or files) that exist at the given content browser paths. @note Multiple items may have the same virtual path if they are different types, or come from different data sources. @param InPaths The paths to search for @param InItemTypeFilter The types of items we want to find. @param InCallback The function to invoke for each matching item (return true to continue enumeration).
- L259 _public prototype_ `virtual void EnumerateItemsAtUserProvidedPath(const FStringView InPath, const EContentBrowserItemTypeFilter InItemTypeFilter, TFunctionRef<bool(FContentBrowserItemData&&)> InCallback);` — Enumerate items at the given user provided path, optionally filtering by type, and invoking the callback for each matching item. The user provided path can be any path format the data source supports other than a virtual path. The data source will deduce the path type. @note This function *must not* block waiting on content discovery! It should use the current state as known at this point in time. @param InPath The user provided path to find items for. @param InItemTypeFilter The types of items we want to find. @param InCallback The function to invoke for each matching item (return true to continue enumeration). @param InSink Parameter provided to receive output as either a callback or an array.
- L260 _public prototype_ `virtual void EnumerateItemsAtUserProvidedPath(const FStringView InPath, const EContentBrowserItemTypeFilter InItemTypeFilter, const TGetOrEnumerateSink<FContentBrowserItemData>& InSink);`
- L269 _public prototype_ `virtual bool EnumerateItemsForObjects(const TArrayView<UObject*> InObjects, TFunctionRef<bool(FContentBrowserItemData&&)> InCallback);` — Enumerate the items (files) that exist for the given objects. @note Multiple items may have the same virtual path if they are different types, or come from different data sources. @param InObjects The objects to enumerate @param InCallback The function to invoke for each matching item (return true to continue enumeration).
- L277 _public prototype_ `virtual TArray<FContentBrowserItemPath> GetAliasesForPath(const FSoftObjectPath& InInternalPath) const;` — Get a list of other paths that the data source may be using to represent a specific path @param InInternalPath The internal path (or object path) of an asset to get aliases for @return All alternative paths that represent the input path (not including the input path itself)
- L286 _public prototype_ `virtual bool GetItemAliasedPath(const FContentBrowserItemData& InItemData, FSoftObjectPath& OutObjectPath) const;` — Get the source asset path of an alias. @param InItemData The content browser item of an alias @param OutObjectPath The soft object path to fill with the result @return True if @code InItemData @endcode is an alias and a path was found, false otherwise
- L289 _public prototype_ `TArray<FContentBrowserItemPath> GetAliasesForPath(FName InInternalPath) const;` — `UE_DEPRECATED(5.1, "FNames containing full asset paths are deprecated. Use FSoftObjectPath instead.")`
- L294 _public prototype_ `virtual bool IsDiscoveringItems(FText* OutStatus = nullptr);` — Query whether this data source instance is currently discovering content, and retrieve an optional status message that can be shown in the UI.
- L300 _public prototype_ `virtual bool PrioritizeSearchPath(const FName InPath);` — If possible, attempt to prioritize content discovery for the given virtual path. @note This will be called in response to a user attempting to browse content under the given virtual path.
- L309 _public prototype_ `virtual bool IsFolderVisible(const FName Path, const EContentBrowserIsFolderVisibleFlags Flags, const FContentBrowserFolderContentsFilter& ContentsFilter);` — Query whether the given virtual folder should be visible in the UI. @note This function must be able to answer the question quickly or not at all (and assume visible). It *must not* block doing something like a file system scan. @param Path Virtual path of folder e.g. /All/GameData/Stuff @param Flags Currently unused @param ContentsFilter Optional filter for limiting visibility to only folders with a certain type of contents based on desired view filtering. If this is unset, folders may be visible regardless of their contents or empty status.
- L319 _public prototype_ `virtual bool CanCreateFolder(const FName InPath, FText* OutErrorMsg);` — Query whether a folder can be created at the given virtual path, optionally providing error information if it cannot. @param InPath The virtual path of the folder that is being queried. @param OutErrorMessage Optional error message to fill on failure. @return True if the folder can be created, false otherwise.
- L329 _public prototype_ `virtual bool CreateFolder(const FName InPath, const TSharedPtr<IContentBrowserHideFolderIfEmptyFilter>& HideFolderIfEmptyFilter, FContentBrowserItemDataTemporaryContext& OutPendingItem);` — Attempt to begin the process of asynchronously creating a folder at the given virtual path, populating a temporary item that can be finalized or canceled by the user. @param InPath The initial virtual path of the folder that is being created. @param OutPendingItem Temporary item context to fill with information about the pending folder item. @return True if the pending folder was created, false otherwise.
- L341 _public prototype_ `virtual bool DoesItemPassFilter(const FContentBrowserItemData& InItem, const FContentBrowserDataCompiledFilter& InFilter);` — Query whether the given item passes the given compiled filter. Should be called after ConvertItemForFilter @see CompileFilter. @param InItem The item to query. @param InFilter The compiled filter used to test matching items. @return True if the item passes the filter, false otherwise.
- L354 _public prototype_ `virtual bool ConvertItemForFilter(FContentBrowserItemData& Item, const FContentBrowserDataCompiledFilter& InFilter);` — Let the compiled filter decide the payload and the type of the item Some Compiled filter might change the type/payload of the item. This allow these filter to work properly and should be called before the filtering (see DoesItemPassFilter) @see CompileFilter @param Item The item that might be converted @param InFilter The compiled filter used to possibly convert the matching items. @return True if the item was converted by the filter.
- L366 _public prototype_ `virtual bool GetItemAttribute(const FContentBrowserItemData& InItem, const bool InIncludeMetaData, const FName InAttributeKey, FContentBrowserItemDataAttributeValue& OutAttributeValue);` — Query the value of the given attribute on the given item. @param InItem The item to query. @param InIncludeMetaData True if we should also include any additional meta-data for the value. @param InAttributeKey The name of the attribute to query. @param OutAttributeValue The attribute value to fill with the result. @return True if the attribute was found and its value was filled, false otherwise.
- L377 _public prototype_ `virtual bool GetItemAttributes(const FContentBrowserItemData& InItem, const bool InIncludeMetaData, FContentBrowserItemDataAttributeValues& OutAttributeValues);` — Query the values of all attributes on the given item. @param InItem The item to query. @param InIncludeMetaData True if we should also include any additional meta-data for the values. @param OutAttributeValues Map to fill with any attributes available on this item, along with their values. @return True attributes were found and their values reported, false otherwise.
- L388 _public prototype_ `virtual bool GetItemPhysicalPath(const FContentBrowserItemData& InItem, FString& OutDiskPath);` — Query the physical (on-disk) path of the given item. @note Not all items or data sources will map to an physical path (eg, some may be purely virtualized views of data that doesn't exist on disk). @param InItem The item to query. @param OutDiskPath The string to fill with the result. @return True if the physical path was found and the result filled, false otherwise.
- L398 _public prototype_ `virtual bool GetItemAssetAccessSpecifier(const FContentBrowserItemData& InItem, EAssetAccessSpecifier& OutAssetAccessSpecifier);` — Query the EAssetAccessSpecifier of the item @param InItem The item to query. @param OutAssetAccessSpecifier The EAssetAccessSpecifier reference that will be filled. @return True if OutAssetAccessSpecifier was filled.
- L407 _public prototype_ `virtual bool CanModifyItemAssetAccessSpecifier(const FContentBrowserItemData& InItem);` — Query the item's ability to modify its EAssetAccessSpecifier @param InItem The item to query. @return True if the item has an EAssetAccessSpecifier that can be modified.
- L416 _public prototype_ `virtual bool IsItemDirty(const FContentBrowserItemData& InItem);` — Query whether the given item is considered dirty (ie, has unsaved changes). @param InItem The item to query. @return True if the item is considered dirty, false otherwise.
- L426 _public prototype_ `virtual bool CanEditItem(const FContentBrowserItemData& InItem, FText* OutErrorMsg);` — Query whether the given item is can be edited, optionally providing error information if it cannot. @param InItem The item to query. @param OutErrorMessage Optional error message to fill on failure. @return True if the item can be edited, false otherwise.
- L435 _public prototype_ `virtual bool EditItem(const FContentBrowserItemData& InItem);` — Attempt to open the given item for editing. @param InItem The item to edit. @return True if the item was opened for editing, false otherwise.
- L445 _public prototype_ `virtual bool BulkEditItems(TArrayView<const FContentBrowserItemData> InItems);` — Attempt to open the given item for editing. @note The default implementation of this will call EditItem for each item. Override if you can provide a more efficient implementation. @param InItems The items to edit. @return True if any items were opened for editing, false otherwise.
- L455 _public prototype_ `virtual bool CanViewItem(const FContentBrowserItemData& InItem, FText* OutErrorMsg);` — Query whether the given item is can be viewed (a read-only asset editor), optionally providing error information if it cannot. @param InItem The item to query. @param OutErrorMessage Optional error message to fill on failure. @return True if the item can be viewed in a read-only editor, false otherwise.
- L464 _public prototype_ `virtual bool ViewItem(const FContentBrowserItemData& InItem);` — Attempt to open the given item for read-only viewing. @param InItem The item to view. @return True if the item was opened for read-only viewing, false otherwise.
- L474 _public prototype_ `virtual bool BulkViewItems(TArrayView<const FContentBrowserItemData> InItems);` — Attempt to open the given items for read-only viewing. @note The default implementation of this will call ViewItem for each item. Override if you can provide a more efficient implementation. @param InItems The items to view. @return True if any items were opened for read-only viewing, false otherwise.
- L484 _public prototype_ `virtual bool CanPreviewItem(const FContentBrowserItemData& InItem, FText* OutErrorMsg);` — Query whether the given item is can be previewed, optionally providing error information if it cannot. @param InItem The item to query. @param OutErrorMessage Optional error message to fill on failure. @return True if the item can be previewed, false otherwise.
- L493 _public prototype_ `virtual bool PreviewItem(const FContentBrowserItemData& InItem);` — Attempt to preview the given item. @param InItem The item to preview. @return True if the item was previewed, false otherwise.
- L503 _public prototype_ `virtual bool BulkPreviewItems(TArrayView<const FContentBrowserItemData> InItems);` — Attempt to preview the given items. @note The default implementation of this will call PreviewItem for each item. Override if you can provide a more efficient implementation. @param InItems The items to preview. @return True if any items were previewed, false otherwise.
- L513 _public prototype_ `virtual bool CanDuplicateItem(const FContentBrowserItemData& InItem, FText* OutErrorMsg);` — Query whether the given item is can be duplicated, optionally providing error information if it cannot. @param InItem The item to query. @param OutErrorMessage Optional error message to fill on failure. @return True if the item can be duplicated, false otherwise.
- L524 _public prototype_ `virtual bool DuplicateItem(const FContentBrowserItemData& InItem, FContentBrowserItemDataTemporaryContext& OutPendingItem);` — Attempt to begin the process of asynchronously duplicating the given item, populating a temporary item that can be finalized or canceled by the user. @note This duplicates the item at its current path and assigns it a default unique name. @param InItem The item to duplicate. @param OutPendingItem Temporary item context to fill with information about the pending duplicated item. @return True if the pending item was created, false otherwise.
- L535 _public prototype_ `virtual bool BulkDuplicateItems(TArrayView<const FContentBrowserItemData> InItems, TArray<FContentBrowserItemData>& OutNewItems);` — Attempt to synchronously duplicate the given items. @note This duplicates the items at their current paths and assigns them a default unique name. @param InItems The items to duplicate. @param OutNewItems The new items duplicated from the originals. @return True if any items were duplicated, false otherwise.
- L546 _public prototype_ `virtual bool CanSaveItem(const FContentBrowserItemData& InItem, const EContentBrowserItemSaveFlags InSaveFlags, FText* OutErrorMsg);` — Query whether the given item is can be saved, optionally providing error information if it cannot. @param InItem The item to query. @param InSaveFlags Flags controlling the rules behind when the item should be saved. @param OutErrorMessage Optional error message to fill on failure. @return True if the item can be saved, false otherwise.
- L556 _public prototype_ `virtual bool SaveItem(const FContentBrowserItemData& InItem, const EContentBrowserItemSaveFlags InSaveFlags);` — Attempt to save the given item. @param InItem The item to save. @param InSaveFlags Flags controlling the rules behind when the item should be saved. @return True if the item was saved, false otherwise.
- L567 _public prototype_ `virtual bool BulkSaveItems(TArrayView<const FContentBrowserItemData> InItems, const EContentBrowserItemSaveFlags InSaveFlags);` — Attempt to save the given items. @note The default implementation of this will call SaveItem for each item. Override if you can provide a more efficient implementation. @param InItems The items to save. @param InSaveFlags Flags controlling the rules behind when the item should be saved. @return True if any items were saved, false otherwise.
- L577 _public prototype_ `virtual bool CanDeleteItem(const FContentBrowserItemData& InItem, FText* OutErrorMsg);` — Query whether the given item is can be deleted, optionally providing error information if it cannot. @param InItem The item to query. @param OutErrorMessage Optional error message to fill on failure. @return True if the item can be deleted, false otherwise.
- L586 _public prototype_ `virtual bool DeleteItem(const FContentBrowserItemData& InItem);` — Attempt to delete the given item. @param InItem The item to delete. @return True if the item was deleted, false otherwise.
- L596 _public prototype_ `virtual bool BulkDeleteItems(TArrayView<const FContentBrowserItemData> InItems);` — Attempt to delete the given items. @note The default implementation of this will call DeleteItem for each item. Override if you can provide a more efficient implementation. @param InItems The items to delete. @return True if any items were deleted, false otherwise.
- L606 _public prototype_ `virtual bool CanPrivatizeItem(const FContentBrowserItemData& InItem, FText* OutErrorMsg);` — Query whether the given item can be privatized, optionally providing error information if it cannot. @param InItem The item to query. @param OutErrorMessage Optional error message to fill on failure. @return True if the item was deleted, false otherwise.
- L615 _public prototype_ `virtual bool PrivatizeItem(const FContentBrowserItemData& InItem, const EAssetAccessSpecifier InAssetAccessSpecifier = EAssetAccessSpecifier::Private);` — Attempt to mark the given item as private (NotExternallyReferenceable). @param InItem The item to mark private. @return True if the item was marked private, false otherwise
- L625 _public prototype_ `virtual bool BulkPrivatizeItems(TArrayView<const FContentBrowserItemData> InItems, const EAssetAccessSpecifier InAssetAccessSpecifier = EAssetAccessSpecifier::Private);` — Attempt to mark the given items as InAssetAccessSpecifier @param InItems The items to be marked InAssetAccessSpecifier. @param InAssetAccessSpecifier The AssetAccessSpecifier to be marked the assets as. @return True if any items were marked InAssetAccessSpecifier, false otherwise
- L636 _public prototype_ `virtual bool CanRenameItem(const FContentBrowserItemData& InItem, const FString* InNewName, const IContentBrowserHideFolderIfEmptyFilter* HideFolderIfEmptyFilter, FText* OutErrorMsg);` — Query whether the given item is can be renamed, optionally providing error information if it cannot. @param InItem The item to query. @param InNewName Optional name that will be tested for validity alongside the general ability to rename this item. @param OutErrorMessage Optional error message to fill on failure. @return True if the item can be renamed, false otherwise.
- L647 _public prototype_ `virtual bool RenameItem(const FContentBrowserItemData& InItem, const FString& InNewName, FContentBrowserItemData& OutNewItem);` — Attempt to rename the given item. @param InItem The item to rename. @param InNewName The new name to give the item. @param OutNewItem The item after it has been renamed. @return True if the item was renamed, false otherwise.
- L658 _public prototype_ `virtual bool CanCopyItem(const FContentBrowserItemData& InItem, const FName InDestPath, FText* OutErrorMsg);` — Query whether the given item is can be copied, optionally providing error information if it cannot. @param InItem The item to query. @param InDestPath The virtual path that the item will be copied to. @param OutErrorMessage Optional error message to fill on failure. @return True if the item can be copied, false otherwise.
- L668 _public prototype_ `virtual bool CopyItem(const FContentBrowserItemData& InItem, const FName InDestPath);` — Attempt to copy the given item to the given virtual path. @param InItem The item to copy. @param InDestPath The virtual path that the item will be copied to. @return True if the item was copied, false otherwise.
- L679 _public prototype_ `virtual bool BulkCopyItems(TArrayView<const FContentBrowserItemData> InItems, const FName InDestPath);` — Attempt to copy the given items to the given virtual path. @note The default implementation of this will call CopyItem for each item. Override if you can provide a more efficient implementation. @param InItems The items to copy. @param InDestPath The virtual path that the item will be copied to. @return True if any items were copied, false otherwise.
- L690 _public prototype_ `virtual bool CanMoveItem(const FContentBrowserItemData& InItem, const FName InDestPath, FText* OutErrorMsg);` — Query whether the given item is can be moved, optionally providing error information if it cannot. @param InItem The item to query. @param InDestPath The virtual path that the item will be moved to. @param OutErrorMessage Optional error message to fill on failure. @return True if the item can be moved, false otherwise.
- L700 _public prototype_ `virtual bool MoveItem(const FContentBrowserItemData& InItem, const FName InDestPath);` — Attempt to move the given item to the given virtual path. @param InItem The item to move. @param InDestPath The virtual path that the item will be moved to. @return True if the item was moved, false otherwise.
- L711 _public prototype_ `virtual bool BulkMoveItems(TArrayView<const FContentBrowserItemData> InItems, const FName InDestPath);` — Attempt to move the given items to the given virtual path. @note The default implementation of this will call MoveItem for each item. Override if you can provide a more efficient implementation. @param InItems The items to move. @param InDestPath The virtual path that the item will be moved to. @return True if any items were moved, false otherwise.
- L722 _public prototype_ `virtual bool AppendItemReference(const FContentBrowserItemData& InItem, FString& InOutStr);` — Attempt to append any path references for the given item to the given string. @note Used when copying item references to the clipboard. @param InItem The item to query. @param InOutStr The string to append to (LINE_TERMINATOR delimited). @return True if references were appended, false otherwise.
- L733 _public prototype_ `virtual bool AppendItemObjectPath(const FContentBrowserItemData& InItem, FString& InOutStr);` — Attempt to append any object path for the given item to the given string. @note Used when copying item object path to the clipboard. @param InItem The item to query. @param InOutStr The string to append to (LINE_TERMINATOR delimited). @return True if package name were appended, false otherwise.
- L744 _public prototype_ `virtual bool AppendItemPackageName(const FContentBrowserItemData& InItem, FString& InOutStr);` — Attempt to append any package name for the given item to the given string. @note Used when copying item package name to the clipboard. @param InItem The item to query. @param InOutStr The string to append to (LINE_TERMINATOR delimited). @return True if package name were appended, false otherwise.
- L754 _public prototype_ `virtual bool UpdateThumbnail(const FContentBrowserItemData& InItem, FAssetThumbnail& InThumbnail);` — Attempt to update the thumbnail associated with the given item. @param InItems The items to query. @param InThumbnail The thumbnail to update. @return True if the thumbnail was updated, false otherwise.
- L764 _public prototype_ `virtual TSharedPtr<FDragDropOperation> CreateCustomDragOperation(TArrayView<const FContentBrowserItemData> InItems);` — Called to provide custom drag and drop handling when starting a drag event. @note If you override this then you are responsible for *all* drag and drop handling (including the default move/copy behavior) via the HandleDrag functions below! @param InItems The items being dragged. @return A custom drag operation, or null to allow another data source (or the default handler) to deal with it instead.
- L774 _public prototype_ `virtual bool HandleDragEnterItem(const FContentBrowserItemData& InItem, const FDragDropEvent& InDragDropEvent);` — Called to provide custom drag and drop handling when a drag event enters an item, such as performing validation and reporting error information. @param InItem The item that the drag entered. @param InDragDropEvent The drag and drop event. @return True if this data source can handle the drag event (even if it won't because it's invalid), or false to allow another data source (or the default handler) to deal with it instead.
- L784 _public prototype_ `virtual bool HandleDragOverItem(const FContentBrowserItemData& InItem, const FDragDropEvent& InDragDropEvent);` — Called to provide custom drag and drop handling while a drag event is over an item, such as performing validation and reporting error information. @param InItem The item that is the current drop target. @param InDragDropEvent The drag and drop event. @return True if this data source can handle the drag event (even if it won't because it's invalid), or false to allow another data source (or the default handler) to deal with it instead.
- L794 _public prototype_ `virtual bool HandleDragLeaveItem(const FContentBrowserItemData& InItem, const FDragDropEvent& InDragDropEvent);` — Called to provide custom drag and drop handling when a drag event leaves an item, such as clearing any error information set during earlier validation. @param InItem The item that the drag left. @param InDragDropEvent The drag and drop event. @return True if this data source can handle the drag event (even if it won't because it's invalid), or false to allow another data source (or the default handler) to deal with it instead.
- L804 _public prototype_ `virtual bool HandleDragDropOnItem(const FContentBrowserItemData& InItem, const FDragDropEvent& InDragDropEvent);` — Called to provide custom drag and drop handling when a drag event is dropped on an item. @param InItem The item that was the drop target. @param InDragDropEvent The drag and drop event. @return True if this data source can handle the drag event (even if it didn't because it was invalid), or false to allow another data source (or the default handler) to deal with it instead.
- L814 _public prototype_ `virtual bool TryGetCollectionId(const FContentBrowserItemData& InItem, FSoftObjectPath& OutCollectionId);` — Attempt to retrieve the identifier that should be used when storing a reference to the given item within a collection. @param InItem The item to query. @param OutCollectionId The collection ID to fill. @return True if the ID was retrieved, false otherwise.
- L826 _public prototype_ `virtual bool Legacy_TryGetPackagePath(const FContentBrowserItemData& InItem, FName& OutPackagePath);` — Attempt to retrieve the package path associated with the given item. @note This exists to allow the Content Browser to interface with external callbacks that only operate on package paths and should ideally be avoided for new code. @note Only items which historically represented package paths within the Content Browser should return data from this function (ie, assets and classes). @param InItem The item to query. @param InOutStr The package path to fill. @return True if the package path was retrieved, false otherwise.
- L838 _public prototype_ `virtual bool Legacy_TryGetAssetData(const FContentBrowserItemData& InItem, FAssetData& OutAssetData);` — Attempt to retrieve the asset data associated with the given item. @note This exists to allow the Content Browser to interface with external callbacks that only operate on asset data and should ideally be avoided for new code. @note Only items which historically represented asset data within the Content Browser should return data from this function (ie, assets and classes). @param InItem The item to query. @param InOutStr The asset data to fill. @return True if the asset data was retrieved, false otherwise.
- L850 _public prototype_ `virtual bool Legacy_TryConvertPackagePathToVirtualPath(const FName InPackagePath, FName& OutPath);` — Attempt to convert the given package path to a virtual path associated with this data source. @note This exists to allow the Content Browser to interface with public APIs that only operate on package paths and should ideally be avoided for new code. @note This function only adjusts the path to something that could represent a virtualized item within this data source, but it doesn't guarantee that an item actually exists at that path. @param InPackagePath The package path to query. @param OutPath The virtualized path to fill. @return True if the package path was mapped, false otherwise.
- L863 _public prototype_ `virtual bool Legacy_TryConvertAssetDataToVirtualPath(const FAssetData& InAssetData, const bool InUseFolderPaths, FName& OutPath);` — Attempt to convert the given asset data to a virtual path associated with this data source. @note This exists to allow the Content Browser to interface with public APIs that only operate on asset data and should ideally be avoided for new code. @note This function only adjusts the path to something that could represent a virtualized item within this data source, but it doesn't guarantee that an item actually exists at that path. @param InAssetData The asset data to query. @param InUseFolderPaths True if this conversion is for the paths view (so should use the parent folder of an asset), or false if it is for the asset view. @param OutPath The virtualized path to fill. @return True if the asset data was mapped, false otherwise.
- L868 _public prototype_ `void SetVirtualPathTreeNeedsRebuild();` — Sets a flag to force rebuild of virtual path tree with next call to RefreshVirtualPathTreeIfNeeded()
- L873 _public prototype_ `void RefreshVirtualPathTreeIfNeeded();` — Call after a change that could affect rules of virtual path generation.
- L882 _public prototype_ `EContentBrowserPathType TryConvertVirtualPath(const FStringView InPath, FStringBuilderBase& OutPath) const;` — Attempt to convert the given virtual path @note Does test if virtual portion of path exists @note Does not test if internal portion of path exists @return None if virtual path prefix of InPath does not exist, Virtual if path exists and is fully virtual (stops before it reaches internal root), Internal if virtual path part of prefix exists and there is text after the virtual prefix
- L883 _public prototype_ `EContentBrowserPathType TryConvertVirtualPath(const FStringView InPath, FString& OutPath) const;`
- L884 _public prototype_ `EContentBrowserPathType TryConvertVirtualPath(const FStringView InPath, FName& OutPath) const;`
- L885 _public prototype_ `EContentBrowserPathType TryConvertVirtualPath(const FName InPath, FName& OutPath) const;`
- L890 _public prototype_ `virtual void BuildRootPathVirtualTree();` — Rebuilds the tree of virtual paths that ends with internal roots
- L892 _public function_ `const FContentBrowserVirtualPathTree& GetRootPathVirtualTree() const`
- L897 _public prototype_ `FContentBrowserItemData CreateVirtualFolderItem(const FName InFolderPath);` — Creates item data for a fully virtual folder.
- L908 _public prototype_ `virtual bool TryConvertVirtualPathToInternal(const FName InPath, FName& OutInternalPath);` — Convert a virtualized path to its internal form, based on the mount root set on this data source. @note The default implementation expects to produce a package path like result, eg) "/Folder/Folder/File". @param InPath The virtualized path to query. @param OutInternalPath The internal path to fill. @return True if the virtual path was mapped, false otherwise.
- L919 _public prototype_ `virtual bool TryConvertInternalPathToVirtual(const FName InInternalPath, FName& OutPath);` — Convert an internal path to its virtualized form, based on the mount root set on this data source. @note The default implementation expects to consume a package path like input, eg) "/Folder/Folder/File". @param InInternalPath The internal path to query. @param OutPath The virtual path to fill. @return True if the internal path was mapped, false otherwise.
- L924 _public prototype_ `virtual void RemoveUnusedCachedFilterData(const FContentBrowserDataFilterCacheIDOwner& IDOwner, TArrayView<const FName> InVirtualPathsInUse, const FContentBrowserDataFilter& DataFilter);` — Tell the data source to remove any cached data for the filter compilation that might not be needed any more.
- L929 _public prototype_ `virtual void ClearCachedFilterData(const FContentBrowserDataFilterCacheIDOwner& IDOwner);` — Tell the data source to remove the cached data for the filter compilation for this specific owner.
- L939 _protected prototype_ `void QueueItemDataUpdate(FContentBrowserItemDataUpdate&& InUpdate);` — Queue an incremental item data update, for data sources that can provide delta-updates. These updates are flushed out at the end of the next call to Tick on the Content Browser Data Subsystem. @param InUpdate The update describing how the item has changed.
- L945 _protected prototype_ `void NotifyItemDataRefreshed();` — `UE_DEPRECATED(5.5, "No data source should be able request a full data refresh. On large projects this can quickly destroy the editor performance. To avoid that all data sources should support queueing the required incremental data updates for their items. Look for uses of the function QueueItemDataUpdate for examples.")` — Notify a wholesale item data update, for data sources that can't provide delta-updates.
- L950 _protected prototype_ `void RootPathAdded(const FStringView InInternalPath);` — Adds internal root path to virtual path tree
- L955 _protected prototype_ `void RootPathRemoved(const FStringView InInternalPath);` — Removes internal root path from virtual path tree
- L961 _protected member_ `FContentBrowserVirtualPathTree RootPathVirtualTree;` — Tree of virtual paths that ends with internal roots. Used for enumeration and conversion of paths.
- L967 _private member_ `bool bIsInitialized = false;` — True if this data source is currently initialized.
- L972 _private member_ `bool bVirtualPathTreeNeedsRebuild = true;` — True if this data source's virtual path tree needs rebuilding.
- L983 _private member_ `FVirtualPathTreeRulesCachedState VirtualPathTreeRulesCachedState;` — Cached state of rules used to detect when virtual path tree needs rebuilding
- L989 _private member_ `IContentBrowserItemDataSink* DataSink = nullptr;` — The data sink that can be used to communicate with the Content Browser Data Subsystem. This is set to a valid instance when the data source is activated, and set to null when it is deactivated.

#### struct `UContentBrowserDataSource::FVirtualPathTreeRulesCachedState`  
`struct FVirtualPathTreeRulesCachedState`  
_L974-978_
- L976 _public member_ `bool bShowAllFolder = false;`
- L977 _public member_ `bool bOrganizeFolders = false;`

#### Free symbols / members of external scopes

- L24 _macro_ `#define UE_API CONTENTBROWSERDATA_API`
- L34 _namespace_ `namespace ContentBrowserItemAttributes`
- L40 _variable_ `const FName ItemTypeName = "It` (scope `ContentBrowserItemAttributes`) — Attribute key that can be used to query the internal type name of an item. Type: FName.
- L46 _variable_ `const FName ItemTypeDisplayName = "It` (scope `ContentBrowserItemAttributes`) — Attribute key that can be used to query the internal type display name of an item. Type: FText.
- L52 _variable_ `const FName ItemDescription = "It` (scope `ContentBrowserItemAttributes`) — Attribute key that can be used to query the internal description of an item. Type: FText.
- L58 _variable_ `const FName ItemDiskSize = "It` (scope `ContentBrowserItemAttributes`) — Attribute key that can be used to query the internal disk size of an item. Type: int64.
- L64 _variable_ `const FName VirtualizedData = "Ha` (scope `ContentBrowserItemAttributes`) — Attribute key that can be used to query if the item has virtualized data or not. Type: bool.
- L70 _variable_ `const FName ItemIsDeveloperContent = "It` (scope `ContentBrowserItemAttributes`) — Attribute key that can be used to query whether the given item is considered to be developer content. Type: bool.
- L76 _variable_ `const FName ItemIsLocalizedContent = "It` (scope `ContentBrowserItemAttributes`) — Attribute key that can be used to query whether the given item is considered to be localized content. Type: bool.
- L82 _variable_ `const FName ItemIsEngineContent = "It` (scope `ContentBrowserItemAttributes`) — Attribute key that can be used to query whether the given item is considered to be engine content (including engine plugin content). Type: bool.
- L88 _variable_ `const FName ItemIsProjectContent = "It` (scope `ContentBrowserItemAttributes`) — Attribute key that can be used to query whether the given item is considered to be project content (including project plugin content). Type: bool.
- L94 _variable_ `const FName ItemIsPluginContent = "It` (scope `ContentBrowserItemAttributes`) — Attribute key that can be used to query whether the given item is considered to be plugin content. Type: bool.
- L101 _variable_ `const FName ItemIsCustomVirtualFolder = "It` (scope `ContentBrowserItemAttributes`) — Attribute key that can be used to query whether the given item is considered to be a custom virtual folder for organizational purposes that should be presented with a different folder icon. Type: bool.
- L107 _variable_ `const FName ItemColor = "It` (scope `ContentBrowserItemAttributes`) — Attribute key that can be used to query the display color of an item. Type: FLinearColor (as FString).
- L113 _variable_ `const FName ItemAssetTreeFolderOpenBrush = "It` (scope `ContentBrowserItemAttributes`) — Attribute key that can be used to query the item's brush to use for an open folder in an asset tree. Type: Brush name (as FName).
- L119 _variable_ `const FName ItemAssetTreeFolderClosedBrush = "It` (scope `ContentBrowserItemAttributes`) — Attribute key that can be used to query the item's brush to use for a closed folder in an asset tree. Type: Brush name (as FName).
- L125 _variable_ `const FName ItemListViewFolderBrush = "It` (scope `ContentBrowserItemAttributes`) — Attribute key that can be used to query the item's brush to use for a folder in a list view. Type: Brush name (as FName).

### `Source/Editor/ContentBrowserData/Public/ContentBrowserDataSubsystem.h` (Public)


#### enum `EContentBrowserPathType`  
`enum class EContentBrowserPathType : uint8`  
_L45-53_
- reflection: `UENUM(BlueprintType)`
- L48 _public enumerator_ `None` — No path type set
- L50 _public enumerator_ `Internal` — Internal path compatible with asset registry and engine calls (eg,. "/PluginA/MyFile")
- L52 _public enumerator_ `Virtual` — Virtual path for enumerating Content Browser data (eg, "/All/Plugins/PluginA/MyFile")

#### enum `EContentBrowserIsFolderVisibleFlags`  
`enum class EContentBrowserIsFolderVisibleFlags : uint8`  
_L55-68_
- L57 _public enumerator_ `None = 0`
- L62 _public enumerator_ `HideEmptyFolders UE_DEPRECATED(5.5, "Empty folder filtering is now dependent on which types of contents are visible, use the FContentBrowserFolderContentsFilter argument to IsFolderVisible") = 1 << 0` — Hide folders that recursively contain no file items.
- L67 _public enumerator_ `Default = None` — Default visibility flags.

#### struct `FContentBrowserCompiledSubsystemFilter`  
`struct FContentBrowserCompiledSubsystemFilter`  
_L91-97_
- reflection: `USTRUCT()`
- desc: Internal - Filter data used to inject dummy items for the path down to the mount root of each data source
- L96 _public member_ `TArray<FName> MountRootsToEnumerate;`

#### struct `FContentBrowserCompiledVirtualFolderFilter`  
`struct FContentBrowserCompiledVirtualFolderFilter`  
_L101-107_
- reflection: `USTRUCT()`
- desc: Internal - Filter data used to inject dummy items
- L106 _public member_ `TMap<FName, FContentBrowserItemData> CachedSubPaths;`

#### class `UContentBrowserDataSubsystem`  
`class UContentBrowserDataSubsystem : public UEditorSubsystem, public IContentBrowserItemDataSink`  
_L114-643_
- reflection: `UCLASS(MinimalAPI, config=Editor)`
- inherits: `UEditorSubsystem,IContentBrowserItemDataSink`
- desc: Subsystem that provides access to Content Browser data. This type deals with the composition of multiple data sources, which provide information about the folders and files available in the Content Browser.
- L121 _public prototype_ `UContentBrowserDataSubsystem();`
- L123 _public prototype_ `virtual void Initialize(FSubsystemCollectionBase& Collection) override;`
- L124 _public prototype_ `virtual void Deinitialize() override;`
- L125 _public prototype_ `virtual void ConvertInternalPathToVirtual(const FStringView InPath, FStringBuilderBase& OutPath) override;`
- L132 _public prototype_ `bool ActivateDataSource(const FName Name);` — `UFUNCTION(BlueprintCallable, Category="ContentBrowser")` — Attempt to activate the named data source. @return True if the data source was available and not already active, false otherwise.
- L139 _public prototype_ `bool DeactivateDataSource(const FName Name);` — `UFUNCTION(BlueprintCallable, Category="ContentBrowser")` — Attempt to deactivate the named data source. @return True if the data source was available and active, false otherwise.
- L145 _public prototype_ `void ActivateAllDataSources();` — `UFUNCTION(BlueprintCallable, Category="ContentBrowser")` — Activate all available data sources.
- L151 _public prototype_ `void DeactivateAllDataSources();` — `UFUNCTION(BlueprintCallable, Category="ContentBrowser")` — Deactivate all active data sources.
- L157 _public prototype_ `TArray<FName> GetAvailableDataSources() const;` — `UFUNCTION(BlueprintCallable, Category="ContentBrowser")` — Get the list of current available data sources.
- L163 _public prototype_ `TArray<FName> GetActiveDataSources() const;` — `UFUNCTION(BlueprintCallable, Category="ContentBrowser")` — Get the list of current active data sources.
- L168 _public prototype_ `FOnContentBrowserItemDataUpdated& OnItemDataUpdated();` — Delegate called for incremental item data updates from data sources that can provide delta-updates.
- L173 _public prototype_ `FOnContentBrowserItemDataRefreshed& OnItemDataRefreshed();` — Delegate called for wholesale item data updates from data sources that can't provide delta-updates, or when the set of active data sources is modified.
- L179 _public prototype_ `FOnContentBrowserItemDataDiscoveryComplete& OnItemDataDiscoveryComplete();` — Delegate called when all active data sources have completed their initial content discovery scan. @note May be called multiple times if new data sources are registered after the current set of active data sources have completed their initial scan.
- L185 _public prototype_ `void CompileFilter(const FName InPath, const FContentBrowserDataFilter& InFilter, FContentBrowserDataCompiledFilter& OutCompiledFilter) const;` — Take a raw data filter and convert it into a compiled version that could be re-used for multiple queries using the same data (typically this is only useful for post-filtering multiple items). @note The compiled filter is only valid until the data source changes, so only keep it for a short time (typically within a function call, or 1-frame).
- L190 _public prototype_ `void EnumerateItemsMatchingFilter( const FContentBrowserDataCompiledFilter& InFilter, TFunctionRef<bool(FContentBrowserItem&&)> InCallback) const;` — Enumerate the items (folders and/or files) that match a previously compiled filter.
- L192 _public prototype_ `void EnumerateItemsMatchingFilter(const FContentBrowserDataCompiledFilter& InFilter, TFunctionRef<bool(FContentBrowserItemData&&)> InCallback) const;`
- L194 _public prototype_ `void EnumerateItemsMatchingFilter( const FContentBrowserDataCompiledFilter& InFilter, const TGetOrEnumerateSink<FContentBrowserItemData>& InSink) const;`
- L200 _public prototype_ `void EnumerateItemsUnderPath(const FName InPath, const FContentBrowserDataFilter& InFilter, TFunctionRef<bool(FContentBrowserItem&&)> InCallback) const;` — Enumerate the items (folders and/or files) that exist under the given virtual path.
- L203 _public prototype_ `void EnumerateItemsUnderPath(const FName InPath, const FContentBrowserDataFilter& InFilter, TFunctionRef<bool(FContentBrowserItemData&&)> InCallback) const;`
- L207 _public prototype_ `void EnumerateItemsUnderPath(const FName InPath, const FContentBrowserDataFilter& InFilter, const TGetOrEnumerateSink<FContentBrowserItemData>& InSink) const;` — Version which allows passing an array or a callback, allows sources to presize the array for large queries
- L215 _public prototype_ `TArray<FContentBrowserItem> GetItemsUnderPath(const FName InPath, const FContentBrowserDataFilter& InFilter) const;` — `UFUNCTION(BlueprintCallable, Category="ContentBrowser")` — Get the items (folders and/or files) that exist under the given virtual path.
- L221 _public prototype_ `void EnumerateItemsAtPath(const FName InPath, const EContentBrowserItemTypeFilter InItemTypeFilter, TFunctionRef<bool(FContentBrowserItem&&)> InCallback) const;` — Enumerate the items (folders and/or files) that exist at the given virtual path. @note Multiple items may have the same virtual path if they are different types, or come from different data sources.
- L222 _public prototype_ `void EnumerateItemsAtPath(const FName InPath, const EContentBrowserItemTypeFilter InItemTypeFilter, TFunctionRef<bool(FContentBrowserItemData&&)> InCallback) const;`
- L232 _public prototype_ `bool EnumerateItemsAtPaths(const TArrayView<struct FContentBrowserItemPath> InItemPaths, const EContentBrowserItemTypeFilter InItemTypeFilter, TFunctionRef<bool(FContentBrowserItemData&&)> InCallback) const;` — Enumerate the items (files) that exist at the given paths. @note Multiple items may have the same virtual path if they are different types, or come from different data sources. @param InItemPaths The paths to enumerate @param InItemTypeFilter The types of items we want to find. @param InCallback The function to invoke for each matching item (return true to continue enumeration).
- L239 _public prototype_ `void EnumerateItemsAtUserProvidedPath(const FStringView InPath, const EContentBrowserItemTypeFilter InItemTypeFilter, TFunctionRef<bool(FContentBrowserItem&&)> InCallback) const;` — Enumerate the items (folders and/or files) that exist at the given user provided path. The user provided path can be any path format any of the data sources support other than a virtual path. The data sources will deduce the path type. @note Multiple items may have the same virtual path if they are different types, or come from different data sources.
- L240 _public prototype_ `void EnumerateItemsAtUserProvidedPath(const FStringView InPath, const EContentBrowserItemTypeFilter InItemTypeFilter, TFunctionRef<bool(FContentBrowserItemData&&)> InCallback) const;`
- L249 _public prototype_ `bool EnumerateItemsForObjects(const TArrayView<UObject*> InObjects, TFunctionRef<bool(FContentBrowserItemData&&)> InCallback) const;` — Enumerate the items (files) that exist for the given objects. @note Multiple items may have the same virtual path if they are different types, or come from different data sources. @param InObjects The objects to enumerate @param InCallback The function to invoke for each matching item (return true to continue enumeration).
- L256 _public prototype_ `TArray<FContentBrowserItem> GetItemsAtPath(const FName InPath, const EContentBrowserItemTypeFilter InItemTypeFilter) const;` — `UFUNCTION(BlueprintCallable, Category="ContentBrowser")` — Get the items (folders and/or files) that exist at the given virtual path. @note Multiple items may have the same virtual path if they are different types, or come from different data sources.
- L262 _public prototype_ `FContentBrowserItem GetItemAtPath(const FName InPath, const EContentBrowserItemTypeFilter InItemTypeFilter) const;` — `UFUNCTION(BlueprintCallable, Category="ContentBrowser")` — Get the first item (folder and/or file) that exists at the given virtual path.
- L269 _public prototype_ `TArray<FContentBrowserItem> GetItemsAtUserProvidedPath(const FStringView InPath, const EContentBrowserItemTypeFilter InItemTypeFilter) const;` — Get the items (folders and/or files) that exist at the given user provided path. The user provided path can be any path format any of the data sources support other than a virtual path. The data sources will deduce the path type. @note Multiple items may have the same virtual path if they are different types, or come from different data sources.
- L277 _public prototype_ `TArray<FContentBrowserItemPath> GetAliasesForPath(const FSoftObjectPath& InInternalPath) const;` — Get a list of other paths that the data source may be using to represent a specific path @param The internal path (or object path) of an asset to get aliases for @return All alternative paths that represent the input path (not including the input path itself)
- L278 _public prototype_ `TArray<FContentBrowserItemPath> GetAliasesForPath(const FContentBrowserItemPath InPath) const;`
- L279 _public prototype_ `TArray<FContentBrowserItemPath> GetAliasesForPath(const FName InInternalPath) const;`
- L284 _public prototype_ `bool IsDiscoveringItems(TArray<FText>* OutStatus = nullptr) const;` — Query whether any data sources are currently discovering content, and retrieve optional status messages that can be shown in the UI.
- L289 _public prototype_ `bool PrioritizeSearchPath(const FName InPath);` — If possible, attempt to prioritize content discovery for the given virtual path.
- L296 _public prototype_ `bool IsFolderVisible(const FName Path, const EContentBrowserIsFolderVisibleFlags Flags = EContentBrowserIsFolderVisibleFlags::Default) const;` — Query whether the given virtual folder should be visible in the UI. @param Path Virtual path of folder e.g. /All/GameData/Stuff @param Flags Currently unused
- L304 _public prototype_ `bool IsFolderVisible(const FName Path, const EContentBrowserIsFolderVisibleFlags Flags, const FContentBrowserFolderContentsFilter& ContentsFilter) const;` — Query whether the given virtual folder should be visible in the UI. @param Path Virtual path of folder e.g. /All/GameData/Stuff @param Flags Currently unused @param ContentsFilter Filter for limiting visibility to only folders with a certain type of contents based on desired view filtering.
- L310 _public prototype_ `bool IsFolderVisibleIfHidingEmpty(const FName InPath) const;` — `UE_DEPRECATED(5.3, "IsFolderVisibleIfHidingEmpty is deprecated. Use IsFolderVisible instead and add EContentBrowserIsFolderVisibleFlags::HideEmptyFolders to the flags.")` — Query whether the given virtual folder should be visible if the UI is asking to hide empty content folders.
- L320 _public prototype_ `bool CanCreateFolder(const FName InPath, FText* OutErrorMsg) const;` — Query whether a folder can be created at the given virtual path, optionally providing error information if it cannot. @param InPath The virtual path of the folder that is being queried. @param OutErrorMessage Optional error message to fill on failure. @return True if the folder can be created, false otherwise.
- L329 _public prototype_ `FContentBrowserItemTemporaryContext CreateFolder(const FName InPath) const;` — Attempt to begin the process of asynchronously creating a folder at the given virtual path, returning a temporary item that can be finalized or canceled by the user. @param InPath The initial virtual path of the folder that is being created. @return The pending folder item to create (test for validity).
- L339 _public prototype_ `FContentBrowserItemTemporaryContext CreateFolder(const FName InPath, const TSharedPtr<IContentBrowserHideFolderIfEmptyFilter>& HideFolderIfEmptyFilter) const;` — Attempt to begin the process of asynchronously creating a folder at the given virtual path, returning a temporary item that can be finalized or canceled by the user. @param InPath The initial virtual path of the folder that is being created. @param HideFolderIfEmptyFilter Current empty folder filter used to permit new folder operations on hidden folders. @return The pending folder item to create (test for validity).
- L346 _public prototype_ `void Legacy_TryConvertPackagePathToVirtualPaths(const FName InPackagePath, TFunctionRef<bool(FName)> InCallback);` — Attempt to convert the given package path to virtual paths associated with the active data sources (callback will be called for each successful conversion). @note This exists to allow the Content Browser to interface with public APIs that only operate on package paths and should ideally be avoided for new code. @note This function only adjusts the path to something that could represent a virtualized item within this data source, but it doesn't guarantee that an item actually exists at that path.
- L353 _public prototype_ `void Legacy_TryConvertAssetDataToVirtualPaths(const FAssetData& InAssetData, const bool InUseFolderPaths, TFunctionRef<bool(FName)> InCallback);` — Attempt to convert the given asset data to a virtual paths associated with the active data sources (callback will be called for each successful conversion). @note This exists to allow the Content Browser to interface with public APIs that only operate on asset data and should ideally be avoided for new code. @note This function only adjusts the path to something that could represent a virtualized item within this data source, but it doesn't guarantee that an item actually exists at that path.
- L358 _public prototype_ `void RefreshVirtualPathTreeIfNeeded();` — Rebuild the virtual path tree if rules have changed.
- L363 _public prototype_ `void SetVirtualPathTreeNeedsRebuild();` — Call when rules of virtual path generation have changed beyond content browser settings.
- L368 _public prototype_ `void ConvertInternalPathToVirtual(const FStringView InPath, FName& OutPath);` — Converts an internal path to a virtual path based on current rules
- L369 _public prototype_ `void ConvertInternalPathToVirtual(FName InPath, FName& OutPath);`
- L370 _public prototype_ `FName ConvertInternalPathToVirtual(FName InPath);`
- L371 _public prototype_ `TArray<FString> ConvertInternalPathsToVirtual(const TArray<FString>& InPaths);`
- L377 _public prototype_ `FText ConvertVirtualPathToDisplay(const FStringView InVirtualPath, const EContentBrowserItemTypeFilter InLeafType) const;` — Converts a virtual path to a display path, where each path segment is replaced with the display name of its corresponding FContentBrowserItem. This path will display similar to the Content Browser's navigation bar.
- L378 _public prototype_ `FText ConvertVirtualPathToDisplay(FName InVirtualPath, const EContentBrowserItemTypeFilter InLeafType) const;`
- L379 _public prototype_ `FText ConvertVirtualPathToDisplay(const FContentBrowserItem& InItem) const;`
- L384 _public prototype_ `EContentBrowserPathType TryConvertVirtualPath(const FStringView InPath, FStringBuilderBase& OutPath) const;` — Converts virtual path back into an internal or invariant path
- L385 _public prototype_ `EContentBrowserPathType TryConvertVirtualPath(const FStringView InPath, FString& OutPath) const;`
- L386 _public prototype_ `EContentBrowserPathType TryConvertVirtualPath(const FStringView InPath, FName& OutPath) const;`
- L387 _public prototype_ `EContentBrowserPathType TryConvertVirtualPath(const FName InPath, FName& OutPath) const;`
- L392 _public prototype_ `TArray<FString> TryConvertVirtualPathsToInternal(const TArray<FString>& InVirtualPaths) const;` — Returns array of paths converted to internal.
- L397 _public prototype_ `void SetPathViewSpecialSortFolders(const TArray<FName>& InSpecialSortFolders);` — Customize list of folders that appear first in content browser based on internal or invariant paths
- L402 _public prototype_ `const TArray<FName>& GetPathViewSpecialSortFolders() const;` — Returns reference to list of paths that appear first in content browser based on internal or invariant paths
- L407 _public prototype_ `const TArray<FName>& GetDefaultPathViewSpecialSortFolders() const;` — Returns reference to default list of paths that appear first in content browser based on internal or invariant paths
- L412 _public prototype_ `void SetGenerateVirtualPathPrefixDelegate(const FContentBrowserGenerateVirtualPathDelegate& InDelegate);` — Set delegate used to generate a virtual path.
- L417 _public prototype_ `FContentBrowserGenerateVirtualPathDelegate& OnGenerateVirtualPathPrefix();` — Delegate called to generate a virtual path. Can be set to override default behavior.
- L422 _public prototype_ `bool UsePluginVersePath(const TSharedRef<IPlugin>& Plugin);` — Return whether the plugin VersePath should be its path in the content browser, if it has one
- L427 _public prototype_ `void SetUsePluginVersePathDelegate(FContentBrowserUsePluginVersePathDelegate InDelegate);` — Set delegate to check whether the plugin VersePath should be its path in the content browser, if it has one
- L432 _public prototype_ `FContentBrowserUsePluginVersePathDelegate& GetUsePluginVersePathDelegate();` — Delegate to check whether the plugin VersePath should be its path in the content browser, if it has one
- L438 _public prototype_ `TSharedPtr<IContentBrowserHideFolderIfEmptyFilter> CreateHideFolderIfEmptyFilter() const;` — Creates the default IContentBrowserHideFolderIfEmptyFilter, and combines it with the results of any additional registered FContentBrowserCreateHideFolderIfEmptyFilter delegates. @note The filter is only valid until any dependent data changes, so only keep it for a short time (typically within a function call tree).
- L444 _public prototype_ `FDelegateHandle RegisterCreateHideFolderIfEmptyFilter(FContentBrowserCreateHideFolderIfEmptyFilter Delegate);` — Registers/deregisters a delegate used to create a filter used to filter out empty folders. If multiple delegates are registered they will get or'd togeather. Intended for content folders that always exist but do not generally contain assets, such as /Game/Collections
- L445 _public prototype_ `void UnregisterCreateHideFolderIfEmptyFilter(FDelegateHandle DelegateHandle);`
- L450 _public prototype_ `const FString& GetAllFolderPrefix() const;` — Prefix to use when generating virtual paths and "Show All Folder" option is enabled
- L456 _public prototype_ `TSharedRef<FPathPermissionList>& GetEditableFolderPermissionList();` — Permission list that controls whether content in a given folder path can be edited. Note: This does not control if the folder path is writable or if content can be deleted.
- L475 _private prototype_ `void InitializeCacheIDOwner(FContentBrowserDataFilterCacheIDOwner& IDOwner);`
- L477 _private prototype_ `void RemoveUnusedCachedFilterData(const FContentBrowserDataFilterCacheIDOwner& IDOwner, TArrayView<const FName> InVirtualPathsInUse, const FContentBrowserDataFilter& DataFilter) const;`
- L479 _private prototype_ `void ClearCachedFilterData(const FContentBrowserDataFilterCacheIDOwner& IDOwner) const;`
- L481 _private typedef_ `using FNameToDataSourceMap = TSortedMap<FName, UContentBrowserDataSource*, FDefaultAllocator, FNameFastLess>;`
- L487 _private prototype_ `void HandleDataSourceRegistered(const FName& Type, class IModularFeature* Feature);` — Called to handle a data source modular feature being registered. @note Will activate the data source if it is in the EnabledDataSources array.
- L493 _private prototype_ `void HandleDataSourceUnregistered(const FName& Type, class IModularFeature* Feature);` — Called to handle a data source modular feature being unregistered. @note Will deactivate the data source if it is in the ActiveDataSources map.
- L499 _private prototype_ `void Tick(const float InDeltaTime);` — Tick this subsystem. @note Called once every 0.1 seconds.
- L504 _private prototype_ `bool AllowModifiedItemDataUpdates() const;` — Returns true if item data modifications are being processed.
- L509 _private prototype_ `void OnBeginPIE(const bool bIsSimulating);` — Called when Play in Editor begins.
- L514 _private prototype_ `void OnEndPIE(const bool bIsSimulating);` — Called when Play in Editor stops.
- L520 _private prototype_ `void OnContentPathMounted(const FString& AssetPath, const FString& ContentPath);` — Called when Content added to delay content browser tick for a frame Prevents content browser from slowing down initialization by ticking as content is loaded
- L523 _private prototype_ `virtual void QueueItemDataUpdate(FContentBrowserItemDataUpdate&& InUpdate) override;`
- L526 _private prototype_ `virtual void NotifyItemDataRefreshed() override;` — `UE_DEPRECATED(5.5, "NotifyItemDataRefreshed is deprecated, for editor performance reasons no external systems should be able to request a full refresh.")`
- L531 _private member_ `FTSTicker::FDelegateHandle TickHandle;` — Handle for the Tick callback.
- L536 _private member_ `FNameToDataSourceMap ActiveDataSources;` — Map of data sources that are currently active.
- L541 _private member_ `FNameToDataSourceMap AvailableDataSources;` — Map of data sources that are currently available.
- L547 _private member_ `TSet<FName> ActiveDataSourcesDiscoveringContent;` — Set of data sources that are currently running content discovery. ItemDataDiscoveryCompleteDelegate will be called each time this set becomes empty.
- L553 _private member_ `TArray<FName> EnabledDataSources;` — `UPROPERTY(config)` — Array of data source names that should be activated when available.
- L559 _private member_ `TArray<FContentBrowserItemDataUpdate> PendingUpdates;` — Queue of incremental item data updates. These will be passed to ItemDataUpdatedDelegate on the end of Tick.
- L565 _private member_ `TMap<FContentBrowserItemKey, FContentBrowserItemDataUpdate> DelayedPendingUpdates;` — Set of item data updates that are delayed to preserve the editor performance. These will be passed to the PendingUpdates when we exit a pie session.
- L570 _private member_ `bool bPendingItemDataRefreshedNotification = false;` — True if an item data refresh notification is pending.
- L575 _private member_ `bool bIsPIEActive = false;` — True if Play in Editor is active.
- L580 _private member_ `bool bContentMountedThisFrame = false;` — True if content was just mounted this frame
- L586 _private member_ `int32 TickSuppressionCount = 0;` — >0 if Tick events have currently been suppressed. @see FScopedSuppressContentBrowserDataTick
- L591 _private member_ `FOnContentBrowserItemDataUpdated ItemDataUpdatedDelegate;` — Delegate called for incremental item data updates from data sources that can provide delta-updates.
- L596 _private member_ `FOnContentBrowserItemDataRefreshed ItemDataRefreshedDelegate;` — Delegate called for wholesale item data updates from data sources that can't provide delta-updates, or when the set of active data sources is modified.
- L602 _private member_ `FOnContentBrowserItemDataDiscoveryComplete ItemDataDiscoveryCompleteDelegate;` — Delegate called when all active data sources have completed their initial content discovery scan. @note May be called multiple times if new data sources are registered after the current set of active data sources have completed their initial scan.
- L607 _private member_ `FContentBrowserGenerateVirtualPathDelegate GenerateVirtualPathPrefixDelegate;` — Generates an optional virtual path prefix for a given internal path
- L612 _private member_ `FContentBrowserUsePluginVersePathDelegate UsePluginVersePathDelegate;` — Delegate to check whether the plugin VersePath should be its path in the content browser, if it has one
- L617 _private member_ `TSharedPtr<IContentBrowserHideFolderIfEmptyFilter> DefaultHideFolderIfEmptyFilter;` — Default filter used to check whether an empty folder should always be filtered out in the Content Browser
- L622 _private member_ `TArray<FContentBrowserCreateHideFolderIfEmptyFilter> CreateHideFolderIfEmptyFilterDelegates;` — Delegates to create filters that check whether an empty folder should always be filtered out in the Content Browser
- L627 _private member_ `TArray<FName> PathViewSpecialSortFolders;` — Optional array of invariant paths to use when sorting
- L632 _private member_ `TArray<FName> DefaultPathViewSpecialSortFolders;` — Default array of invariant paths to use when sorting
- L637 _private member_ `FString AllFolderPrefix;` — Prefix to use when generating virtual paths and "Show All Folder" option is enabled
- L640 _private member_ `TSharedRef<FPathPermissionList> EditableFolderPermissionList;` — Permission list of folder paths we can edit
- L642 _private member_ `int64 LastCacheIDForFilter = INDEX_NONE;`

#### struct `UContentBrowserDataSubsystem::FContentBrowserFilterCacheApi`  
`struct FContentBrowserFilterCacheApi`  
_L463-471_
- desc: Provide an partial access to private api for the filter cache ID owners See FContentBrowserDataFilterCacheIDOwner declaration for how to use the caching for filter compilation
- L468 _private prototype_ `static void InitializeCacheIDOwner(UContentBrowserDataSubsystem& Subsystem, FContentBrowserDataFilterCacheIDOwner& IDOwner);`
- L469 _private prototype_ `static void RemoveUnusedCachedData(const UContentBrowserDataSubsystem& Subsystem, const FContentBrowserDataFilterCacheIDOwner& IDOwner, TArrayView<const FName> InVirtualPathsInUse, const FContentBrowserDataFilter& DataFilter);`
- L470 _private prototype_ `static void ClearCachedData(const UContentBrowserDataSubsystem& Subsystem, const FContentBrowserDataFilterCacheIDOwner& IDOwner);`

#### class `FScopedSuppressContentBrowserDataTick`  
`class FScopedSuppressContentBrowserDataTick`  
_L648-669_
- desc: Helper to suppress Tick events during critical times, when the underlying data should not be updated.
- L651 _public function_ `explicit FScopedSuppressContentBrowserDataTick(UContentBrowserDataSubsystem* InContentBrowserData) : ContentBrowserData(InContentBrowserData)`
- L658 _public function_ `~FScopedSuppressContentBrowserDataTick()`
- L664 _public prototype_ `FScopedSuppressContentBrowserDataTick(const FScopedSuppressContentBrowserDataTick&) = delete;`
- L665 _public prototype_ `FScopedSuppressContentBrowserDataTick& operator=(const FScopedSuppressContentBrowserDataTick&) = delete;`
- L668 _private member_ `UContentBrowserDataSubsystem* ContentBrowserData = nullptr;`

#### Free symbols / members of external scopes

- L32 _macro_ `#define UE_API CONTENTBROWSERDATA_API`
- L69 _prototype_ `ENUM_CLASS_FLAGS(EContentBrowserIsFolderVisibleFlags);`
- L72 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnContentBrowserItemDataUpdated, TArrayView<const FContentBrowserItemDataUpdate>);` — Called for incremental item data updates from data sources that can provide delta-updates
- L72 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnContentBrowserItemDataUpdated, TArrayView<const FContentBrowserItemDataUpdate>);` — Called for incremental item data updates from data sources that can provide delta-updates
- L75 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnContentBrowserItemDataRefreshed);` — Called for wholesale item data updates from data sources that can't provide delta-updates, or when the set of active data sources is modified
- L75 _prototype_ `DECLARE_MULTICAST_DELEGATE(FOnContentBrowserItemDataRefreshed);` — Called for wholesale item data updates from data sources that can't provide delta-updates, or when the set of active data sources is modified
- L78 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnContentBrowserItemDataDiscoveryComplete);` — Called when all active data sources have completed their initial content discovery scan. May be called multiple times if new data sources are registered after the current set of active data sources have completed their initial scan
- L78 _prototype_ `DECLARE_MULTICAST_DELEGATE(FOnContentBrowserItemDataDiscoveryComplete);` — Called when all active data sources have completed their initial content discovery scan. May be called multiple times if new data sources are registered after the current set of active data sources have completed their initial scan
- L81 _delegate_ `DECLARE_DELEGATE_TwoParams(FContentBrowserGenerateVirtualPathDelegate, const FStringView, FStringBuilderBase&);` — Called when generating a virtual path, allows customization of how a virtual path is generated.
- L81 _prototype_ `DECLARE_DELEGATE_TwoParams(FContentBrowserGenerateVirtualPathDelegate, const FStringView, FStringBuilderBase&);` — Called when generating a virtual path, allows customization of how a virtual path is generated.
- L84 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FContentBrowserUsePluginVersePathDelegate, const TSharedRef<IPlugin>&);` — Called to check whether the plugin VersePath should be its path in the content browser, if it has one
- L84 _prototype_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FContentBrowserUsePluginVersePathDelegate, const TSharedRef<IPlugin>&);` — Called to check whether the plugin VersePath should be its path in the content browser, if it has one
- L87 _delegate_ `DECLARE_DELEGATE_RetVal(TSharedPtr<IContentBrowserHideFolderIfEmptyFilter>, FContentBrowserCreateHideFolderIfEmptyFilter);` — Called to create a IContentBrowserHideFolderIfEmptyFilter filter
- L87 _prototype_ `DECLARE_DELEGATE_RetVal(TSharedPtr<IContentBrowserHideFolderIfEmptyFilter>, FContentBrowserCreateHideFolderIfEmptyFilter);` — Called to create a IContentBrowserHideFolderIfEmptyFilter filter

### `Source/Editor/ContentBrowserData/Public/ContentBrowserDataUtils.h` (Public)


#### Free symbols / members of external scopes

- L17 _namespace_ `namespace ContentBrowserDataUtils`
- L20 _prototype_ `int32 CalculateFolderDepthOfPath(const FStringView InPath);` (scope `ContentBrowserDataUtils`) — Returns number of folders in forward slashed path (Eg, 1 for "/Path", 2 for "/Path/Name")
- L23 _prototype_ `bool IsTopLevelFolder(const FStringView InFolderPath);` (scope `ContentBrowserDataUtils`) — Returns true if folder has a depth of 1
- L26 _prototype_ `bool IsTopLevelFolder(const FName InFolderPath);` (scope `ContentBrowserDataUtils`) — Returns true if folder has a depth of 1
- L29 _prototype_ `int32 GetMaxFolderDepthRequiredForAttributeFilter();` (scope `ContentBrowserDataUtils`) — Return the test depth after which it is not needed to test the attribute filter if the parent folder was tested
- L40 _prototype_ `bool PathPassesAttributeFilter(const FStringView InPath, const int32 InAlreadyCheckedDepth, const EContentBrowserItemAttributeFilter InAttributeFilter);` (scope `ContentBrowserDataUtils`) — Tests internal path against attribute filter @param InPath Invariant path to test @param InAlreadyCheckedDepth Number of folders deep that have already been tested to avoid re-testing during recursion. Pass 0 if portion of path not already tested. @param InItemAttributeFilter Filter to test against @return True if passes filter
- L52 _prototype_ `FText GetFolderItemDisplayNameOverride(const FName InFolderPath, const FString& InFolderItemName, const bool bIsClassesFolder, const bool bIsCookedPath = false);` (scope `ContentBrowserDataUtils`) — Get display name override if there is one for InFolderPath @param InFolderPath Internal path to get display name override for @param InFolderItemName Short name of InFolderPath (rightmost folder name) @param bIsClassesFolder True if this folder is a classes folder @param bIsCookedPath True if this folder only contains cooked content (recursively), or false if it contains any uncooked content @return Override display name or empty string
- L54 _prototype_ `bool IsPrimaryAsset(const FAssetData& InAssetData);` (scope `ContentBrowserDataUtils`)
- L56 _prototype_ `bool IsPrimaryAsset(UObject* InObject);` (scope `ContentBrowserDataUtils`)

### `Source/Editor/ContentBrowserData/Public/ContentBrowserItem.h` (Public)


#### struct `FContentBrowserItem`  
`struct FContentBrowserItem`  
_L41-520_
- reflection: `USTRUCT(BlueprintType)`
- desc: Representation of a Content Browser item. FContentBrowserItem is potentially a composite of multiple internal items (eg, combining equivalent folder items from different data sources), and defers back to these internal items to provide its functionality (via the data source that owns each internal item).
- L46 _public typedef_ `using FItemDataArrayView = TArrayView<const FContentBrowserItemData>;`
- L52 _public prototype_ `FContentBrowserItem() = default;` — Default constructor. Produces an item that is empty (IsValid() will return false).
- L57 _public prototype_ `explicit FContentBrowserItem(FContentBrowserItemData&& InItem);` — Construct this composite item from the given internal item(s).
- L58 _public prototype_ `explicit FContentBrowserItem(const FContentBrowserItemData& InItem);`
- L59 _public prototype_ `explicit FContentBrowserItem(TArrayView<const FContentBrowserItemData> InItems);`
- L64 _public prototype_ `FContentBrowserItem(const FContentBrowserItem&) = default;` — Copy support.
- L65 _public prototype_ `FContentBrowserItem& operator=(const FContentBrowserItem&) = default;`
- L70 _public prototype_ `FContentBrowserItem(FContentBrowserItem&&) = default;` — Move support.
- L71 _public prototype_ `FContentBrowserItem& operator=(FContentBrowserItem&&) = default;`
- L76 _public prototype_ `bool IsValid() const;` — Check to see whether this item is valid (contains at least one internal item).
- L81 _public prototype_ `void Append(const FContentBrowserItem& InOther);` — Append the given item to this one, asserting if the combination isn't possible.
- L87 _public prototype_ `bool TryAppend(const FContentBrowserItem& InOther, FText* OutError = nullptr);` — Attempt to append the given item to this one, providing error information if the combination isn't possible. @return True if the combination was possible, false otherwise.
- L92 _public prototype_ `void Append(const FContentBrowserItemData& InOther);` — Append the given item to this one, asserting if the combination isn't possible.
- L98 _public prototype_ `bool TryAppend(const FContentBrowserItemData& InOther, FText* OutError = nullptr);` — Attempt to append the given item to this one, providing error information if the combination isn't possible. @return True if the combination was possible, false otherwise.
- L103 _public prototype_ `void Remove(const FContentBrowserItem& InOther);` — Remove the given item from this one, asserting if the removal wasn't possible.
- L109 _public prototype_ `bool TryRemove(const FContentBrowserItem& InOther, FText* OutError = nullptr);` — Attempt to remove the given item from this one, providing error information if the removal wasn't possible. @return True if the removal was possible, false otherwise.
- L114 _public prototype_ `void Remove(const FContentBrowserItemData& InOther);` — Remove the given item from this one, asserting if the removal wasn't possible.
- L120 _public prototype_ `bool TryRemove(const FContentBrowserItemData& InOther, FText* OutError = nullptr);` — Attempt to remove the given item from this one, providing error information if the removal wasn't possible. @return True if the removal was possible, false otherwise.
- L126 _public prototype_ `FContentBrowserItemData TryRemove(const FContentBrowserMinimalItemData& InKey, FText* OutError = nullptr);` — Attempt to remove an item matching the given minimal representation from this one, providing error information if the removal wasn't possible. @return A valid item data (IsValid) if anything was removed, an invalid one otherwise.
- L131 _public prototype_ `FItemDataArrayView GetInternalItems() const;` — Get the array of internal items that comprise this composite item.
- L136 _public prototype_ `const FContentBrowserItemData* GetPrimaryInternalItem() const;` — Get the primary internal item from this composite item, if any.
- L142 _public prototype_ `bool IsFolder() const;` — Check to see whether this item is a folder. @note Equivalent to testing whether EContentBrowserItemFlags::Type_Folder is set on GetItemFlags().
- L148 _public prototype_ `bool IsFile() const;` — Check to see whether this item is a file. @note Equivalent to testing whether EContentBrowserItemFlags::Type_File is set on GetItemFlags().
- L154 _public prototype_ `bool IsInPlugin() const;` — Check to see whether this item is in a plugin. @note Equivalent to testing whether EContentBrowserItemFlags::Category_Plugin is set on GetItemFlags().
- L161 _public prototype_ `bool IsSupported() const;` — Check if the item is representing a supported item The content browser can also display some unsupported asset @note Equivalent to testing whether EContentBrowserItemFlags::Misc_Unsupported is not set on GetItemFlags()
- L167 _public prototype_ `bool IsTemporary() const;` — Check to see whether this item is temporary. @note Equivalent to testing whether any of EContentBrowserItemFlags::Temporary_MASK is set on GetItemFlags().
- L173 _public prototype_ `bool IsDisplayOnlyFolder() const;` — Check to see whether this item is a display only folder. @note Equivalent to testing whether all of EContentBrowserItemFlags::Category_MASK are unset on GetItemFlags().
- L178 _public prototype_ `EContentBrowserItemFlags GetItemFlags() const;` — Get the flags denoting basic state information for this item instance.
- L184 _public prototype_ `EContentBrowserItemFlags GetItemType() const;` — Get the flags denoting the item type information for this item instance. @note Equivalent to applying EContentBrowserItemFlags::Type_MASK to GetItemFlags().
- L190 _public prototype_ `EContentBrowserItemFlags GetItemCategory() const;` — Get the flags denoting the item category information for this item instance. @note Equivalent to applying EContentBrowserItemFlags::Category_MASK to GetItemFlags().
- L196 _public prototype_ `EContentBrowserItemFlags GetItemTemporaryReason() const;` — Get the flags denoting the item temporary reason information for this item instance. @note Equivalent to applying EContentBrowserItemFlags::Temporary_MASK to GetItemFlags().
- L201 _public prototype_ `FName GetVirtualPath() const;` — Get the complete virtual path that uniquely identifies this item within its owner data source (eg, "/MyRoot/MyFolder/MyFile").
- L206 _public prototype_ `FName GetInvariantPath() const;` — Gets the path that will not change based on toggling "Show All Folder", "Organize Folders" or other rules (eg,. "/Plugins").
- L211 _public prototype_ `FName GetInternalPath() const;` — Gets the internal path if it has one (eg,. "/Game").
- L216 _public prototype_ `FName GetItemName() const;` — Get the leaf-name of this item (eg, "MyFile").
- L221 _public prototype_ `FText GetDisplayName() const;` — Get the user-facing name of this item (eg, "MyFile").
- L230 _public prototype_ `bool GetItemAssetAccessSpecifier(EAssetAccessSpecifier& OutAssetAccessSpecifier) const;` — Query the EAssetAccessSpecifier of the item. @param OutAssetAccessSpecifier The EAssetAccessSpecifier reference that will be filled. @return True if OutAssetAccessSpecifier was filled.
- L237 _public prototype_ `bool CanModifyItemAssetAccessSpecifier() const;` — Query the item's ability to modify its EAssetAccessSpecifier. @return True if the item has an EAssetAccessSpecifier that can be modified.
- L247 _public prototype_ `FContentBrowserItemDataAttributeValue GetItemAttribute(const FName InAttributeKey, const bool InIncludeMetaData = false) const;` — Query the value of the given attribute on this item. @param InAttributeKey The name of the attribute to query. @param InIncludeMetaData True if we should also include any additional meta-data for the value. @return The attribute value (test for validity).
- L256 _public prototype_ `FContentBrowserItemDataAttributeValues GetItemAttributes(const bool InIncludeMetaData = false) const;` — Query the values of all attributes on this item. @param InIncludeMetaData True if we should also include any additional meta-data for the values. @return Map of any attributes available on this item, along with their values.
- L265 _public prototype_ `bool GetItemPhysicalPath(FString& OutDiskPath) const;` — Query the physical (on-disk) path of this item. @param OutDiskPath The string to fill with the result. @return True if the physical path was found and the result filled, false otherwise.
- L271 _public prototype_ `bool IsDirty() const;` — Query whether this item is considered dirty (ie, has unsaved changes). @return True if the item is considered dirty, false otherwise.
- L280 _public prototype_ `bool CanEdit(FText* OutErrorMsg = nullptr) const;` — Query whether this item is can be edited, optionally providing error information if it cannot. @param OutErrorMessage Optional error message to fill on failure. @return True if the item can be edited, false otherwise.
- L286 _public prototype_ `bool Edit() const;` — Attempt to open this item for editing. @return True if the item was opened for editing, false otherwise.
- L295 _public prototype_ `bool CanPreview(FText* OutErrorMsg = nullptr) const;` — Query whether this item is can be previewed, optionally providing error information if it cannot. @param OutErrorMessage Optional error message to fill on failure. @return True if the item can be previewed, false otherwise.
- L304 _public prototype_ `bool CanView(FText* OutErrorMsg = nullptr) const;` — Query whether the given item is can be viewed (a read-only asset editor), optionally providing error information if it cannot. @param OutErrorMessage Optional error message to fill on failure. @return True if the item can be viewed in a read-only editor, false otherwise.
- L310 _public prototype_ `bool Preview() const;` — Attempt to preview this item. @return True if the item was previewed, false otherwise.
- L319 _public prototype_ `bool CanDuplicate(FText* OutErrorMsg = nullptr) const;` — Query whether this item is can be duplicated, optionally providing error information if it cannot. @param OutErrorMessage Optional error message to fill on failure. @return True if the item can be duplicated, false otherwise.
- L327 _public prototype_ `FContentBrowserItemDataTemporaryContext Duplicate() const;` — Attempt to begin the process of asynchronously duplicating this item, populating a temporary item that can be finalized or canceled by the user. @note This duplicates the item at its current path and assigns it a default unique name. @return The temporary context of the duplicate item (test for validity).
- L337 _public prototype_ `bool CanSave(const EContentBrowserItemSaveFlags InSaveFlags, FText* OutErrorMsg = nullptr) const;` — Query whether this item is can be saved, optionally providing error information if it cannot. @param InSaveFlags Flags controlling the rules behind when the item should be saved. @param OutErrorMessage Optional error message to fill on failure. @return True if the item can be saved, false otherwise.
- L346 _public prototype_ `bool Save(const EContentBrowserItemSaveFlags InSaveFlags) const;` — Attempt to save this item. @param InSaveFlags Flags controlling the rules behind when the item should be saved. @return True if the item was saved, false otherwise.
- L355 _public prototype_ `bool CanDelete(FText* OutErrorMsg = nullptr) const;` — Query whether this item is can be deleted, optionally providing error information if it cannot. @param OutErrorMessage Optional error message to fill on failure. @return True if the item can be deleted, false otherwise.
- L361 _public prototype_ `bool Delete() const;` — Attempt to delete this item. @return True if the item was deleted, false otherwise.
- L371 _public prototype_ `bool CanRename(const FString* InNewName, FText* OutErrorMsg = nullptr) const;` — Query whether this item is can be renamed, optionally providing error information if it cannot. @param InNewName Optional name that will be tested for validity alongside the general ability to rename this item. @param OutErrorMessage Optional error message to fill on failure. @return True if the item can be renamed, false otherwise.
- L382 _public prototype_ `bool CanRename(const FString* InNewName, const IContentBrowserHideFolderIfEmptyFilter* HideFolderIfEmptyFilter, FText* OutErrorMsg = nullptr) const;` — Query whether this item is can be renamed, optionally providing error information if it cannot. @param InNewName Optional name that will be tested for validity alongside the general ability to rename this item. @param HideFolderIfEmptyFilter Current empty folder filter used to permit rename operations to hidden folders. @param OutErrorMsg Optional error message to fill on failure. @return True if the item can be renamed, false otherwise.
- L392 _public prototype_ `bool Rename(const FString& InNewName, FContentBrowserItem* OutNewItem = nullptr) const;` — Attempt to rename this item. @param InNewName The new name to give the item. @param OutNewItem The item after it has been renamed. @return True if the item was renamed, false otherwise.
- L402 _public prototype_ `bool CanCopy(const FName InDestPath, FText* OutErrorMsg = nullptr) const;` — Query whether this item is can be copied, optionally providing error information if it cannot. @param InDestPath The virtual path that the item will be copied to. @param OutErrorMessage Optional error message to fill on failure. @return True if the item can be copied, false otherwise.
- L411 _public prototype_ `bool Copy(const FName InDestPath) const;` — Attempt to copy this item to the given virtual path. @param InDestPath The virtual path that the item will be copied to. @return True if the item was copied, false otherwise.
- L421 _public prototype_ `bool CanMove(const FName InDestPath, FText* OutErrorMsg = nullptr) const;` — Query whether this item is can be moved, optionally providing error information if it cannot. @param InDestPath The virtual path that the item will be moved to. @param OutErrorMessage Optional error message to fill on failure. @return True if the item can be moved, false otherwise.
- L430 _public prototype_ `bool Move(const FName InDestPath) const;` — Attempt to move this item to the given virtual path. @param InDestPath The virtual path that the item will be moved to. @return True if the item was moved, false otherwise.
- L440 _public prototype_ `bool AppendItemReference(FString& InOutStr) const;` — Attempt to append any path references for this item to the given string. @note Used when copying item references to the clipboard. @param InOutStr The string to append to (LINE_TERMINATOR delimited). @return True if references were appended, false otherwise.
- L450 _public prototype_ `bool AppendItemObjectPath(FString& InOutStr) const;` — Attempt to append any object path for this item to the given string. @note Used when copying item object path to the clipboard. @param InOutStr The string to append to (LINE_TERMINATOR delimited). @return True if references were appended, false otherwise.
- L460 _public prototype_ `bool AppendItemPackageName(FString& InOutStr) const;` — Attempt to append any package name for this item to the given string. @note Used when copying item package name to the clipboard. @param InOutStr The string to append to (LINE_TERMINATOR delimited). @return True if references were appended, false otherwise.
- L469 _public prototype_ `bool UpdateThumbnail(FAssetThumbnail& InThumbnail) const;` — Attempt to update the thumbnail associated with this item. @param InThumbnail The thumbnail to update. @return True if the thumbnail was updated, false otherwise.
- L478 _public prototype_ `bool TryGetCollectionId(FSoftObjectPath& OutCollectionId) const;` — Attempt to retrieve the identifier that should be used when storing a reference to this item within a collection. @param InOutStr The collection ID to fill. @return True if the ID was retrieved, false otherwise.
- L488 _public prototype_ `bool Legacy_TryGetPackagePath(FName& OutPackagePath) const;` — Attempt to retrieve the package path associated with this item. @note This exists to allow the Content Browser to interface with external callbacks that only operate on package paths and should ideally be avoided for new code. @param InOutStr The package path to fill. @return True if the package path was retrieved, false otherwise.
- L498 _public prototype_ `bool Legacy_TryGetAssetData(FAssetData& OutAssetData) const;` — Attempt to retrieve the asset data associated with this item. @note This exists to allow the Content Browser to interface with external callbacks that only operate on asset data and should ideally be avoided for new code. @param InOutStr The asset data to fill. @return True if the asset data was retrieved, false otherwise.
- L506 _public prototype_ `bool GetItemAliasedPath(FSoftObjectPath& OutObjectPath) const;` — Attempt to retrieve the source asset path of an alias. @param OutObjectPath The soft object path to fill with the result @return True if @code this @endcode is an alias and a path was found, false otherwise
- L512 _public prototype_ `FContentBrowserItemPath GetItemPath() const;` — Creates a ContentBrowserItemPath, potentially looking up internal paths. @return The Item Path.
- L519 _private member_ `TArray<FContentBrowserItemData, TInlineAllocator<1>> ItemDataArray;` — Array of internal items that comprise this composite item. @note Optimized to avoid allocation for the file case, where each composite item has a single internal item.

#### class `UContentBrowserItemLibrary`  
`class UContentBrowserItemLibrary : public UBlueprintFunctionLibrary`  
_L524-540_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UBlueprintFunctionLibrary`
- desc: TODO: Script API exposure
- L530 _public prototype_ `static bool IsFolder(const FContentBrowserItem& Item);` — `UFUNCTION(BlueprintPure, Category="ContentBrowser", meta=(ScriptMethod))`
- L533 _public prototype_ `static bool IsFile(const FContentBrowserItem& Item);` — `UFUNCTION(BlueprintPure, Category="ContentBrowser", meta=(ScriptMethod))`
- L536 _public prototype_ `static FName GetVirtualPath(const FContentBrowserItem& Item);` — `UFUNCTION(BlueprintPure, Category="ContentBrowser", meta=(ScriptMethod))`
- L539 _public prototype_ `static FText GetDisplayName(const FContentBrowserItem& Item);` — `UFUNCTION(BlueprintPure, Category="ContentBrowser", meta=(ScriptMethod))`

#### class `FContentBrowserItemTemporaryContext`  
`class FContentBrowserItemTemporaryContext`  
_L547-587_
- desc: Context for asynchronous item creation (for new items or duplicating existing ones). Data sources will return one of these (hosting a temporary item with any required context) when they want to begin the creation or duplication of an item item. UI involved in this creation flow should call ValidateItem for any name changes, as well as before calling FinalizeItem. Once finalized the temporary item should be replaced with the real one.
- L553 _public prototype_ `bool IsValid() const;` — Check to see whether this context is valid (has been set to a temporary item).
- L558 _public prototype_ `void AppendContext(FContentBrowserItemDataTemporaryContext&& InContext);` — Append the given context to this one.
- L563 _public prototype_ `const FContentBrowserItem& GetItem() const;` — Get the data representing the temporary item instance.
- L569 _public prototype_ `bool ValidateItem(const FString& InProposedName, FText* OutErrorMsg = nullptr) const;` — Invoke the delegate used to validate that the proposed item name is valid. @note Returns True if no validation delegate is bound.
- L574 _public prototype_ `FContentBrowserItem FinalizeItem(const FString& InProposedName, FText* OutErrorMsg = nullptr) const;` — Invoke the delegate used to finalize the creation of the temporary item, and return the real item.
- L580 _private member_ `FContentBrowserItem Item;` — Data representing the temporary item instance.
- L586 _private member_ `TArray<FContentBrowserItemDataTemporaryContext, TInlineAllocator<1>> ItemDataContextArray;` — Array of internal contexts that comprise this composite context. @note Optimized to avoid allocation for the file case, where each composite context has a single internal context.

#### class `FContentBrowserItemKey`  
`class FContentBrowserItemKey : public FContentBrowserItemDataKey`  
_L592-645_
- inherits: `FContentBrowserItemDataKey`
- desc: Minimal representation of a FContentBrowserItem instance that can be used as a map key.
- L599 _public prototype_ `FContentBrowserItemKey() = default;` — Default constructor. Produces a key that is empty.
- L604 _public prototype_ `explicit FContentBrowserItemKey(const FContentBrowserItem& InItem);` — Construct this key from the given item.
- L605 _public prototype_ `explicit FContentBrowserItemKey(const FContentBrowserItemData& InItemData);`
- L610 _public prototype_ `FContentBrowserItemKey(EContentBrowserItemFlags InItemType, FName InPath, const UContentBrowserDataSource* InDataSource);` — Construct this key from the given item type, virtual path, and data source.
- L615 _public function_ `bool operator==(const FContentBrowserItemKey& InOther) const` — Equality support.
- L624 _public function_ `bool operator!=(const FContentBrowserItemKey& InOther) const` — Inequality support.
- L641 _protected prototype_ `void Initialize(const FContentBrowserItemData& InItemData);` — Internal common function shared by the FContentBrowserItem and FContentBrowserItemData constructors.
- L644 _protected member_ `const UContentBrowserDataSource* DataSource = nullptr;` — A pointer to the data source that manages the thing represented by this key

#### class `FContentBrowserItemUpdate`  
`class FContentBrowserItemUpdate`  
_L651-683_
- desc: Type describing an update to an item. @note This is only really useful for script exposure, as it's more efficient for C++ to use FContentBrowserItemDataUpdate directly
- L657 _public prototype_ `explicit FContentBrowserItemUpdate(const FContentBrowserItemDataUpdate& InItemDataUpdate);` — Create an item update from an internal update event.
- L662 _public prototype_ `EContentBrowserItemUpdateType GetUpdateType() const;` — Get the value denoting the types of updates that can be emitted for an item.
- L667 _public prototype_ `const FContentBrowserItem& GetItemData() const;` — Get the item data for the update.
- L672 _public prototype_ `FName GetPreviousVirtualPath() const;` — Get the previous virtual path (UpdateType == Moved).
- L676 _private member_ `EContentBrowserItemUpdateType UpdateType;` — Value denoting the types of updates that can be emitted for an item
- L679 _private member_ `FContentBrowserItem ItemData;` — Item data for the update
- L682 _private member_ `FName PreviousVirtualPath;` — Previous virtual path (UpdateType == Moved)

#### Free symbols / members of external scopes

- L22 _macro_ `#define UE_API CONTENTBROWSERDATA_API`
- L632 _function_ `friend inline uint32 GetTypeHash(const FContentBrowserItemKey& InKey)` — Get the hash of the given instance.

### `Source/Editor/ContentBrowserData/Public/ContentBrowserItemData.h` (Public)


#### enum `EContentBrowserItemFlags`  
`enum class EContentBrowserItemFlags : uint16`  
_L30-55_
- desc: Flags denoting basic state information for an item instance
- L33 _public enumerator_ `None = 0` — No flags
- L36 _public enumerator_ `Type_Folder = 1<<0` — Flags denoting the item type (mutually exclusive)
- L37 _public enumerator_ `Type_File = 1<<1`
- L38 _public enumerator_ `Type_MASK = Type_Folder | Type_File`
- L41 _public enumerator_ `Category_Asset = 1<<2` — Flags denoting the item category
- L42 _public enumerator_ `Category_Class = 1<<3`
- L43 _public enumerator_ `Category_Collection = 1<<4`
- L44 _public enumerator_ `Category_Plugin = 1 << 5` — Plugin content or classes - note that folders containing plugins do not have this flag set
- L45 _public enumerator_ `Category_Misc = 1<<6`
- L46 _public enumerator_ `Category_MASK = Category_Asset | Category_Class | Category_Collection | Category_Plugin | Category_Misc`
- L49 _public enumerator_ `Temporary_Creation = 1<<7` — Flags denoting additional information for temporary items (mutually exclusive)
- L50 _public enumerator_ `Temporary_Duplication = 1<<8`
- L51 _public enumerator_ `Temporary_MASK = Temporary_Creation | Temporary_Duplication`
- L54 _public enumerator_ `Misc_Unsupported = 1 << 9` — Flag to mark the item as showing something that is unsupported

#### enum `EContentBrowserItemSaveFlags`  
`enum class EContentBrowserItemSaveFlags : uint8`  
_L59-67_
- desc: Flags denoting the save behavior of items
- L62 _public enumerator_ `None = 0` — No flags
- L64 _public enumerator_ `SaveOnlyIfDirty = 1<<0` — Save the item only if it is considered dirty
- L66 _public enumerator_ `SaveOnlyIfLoaded = 1<<1` — Save the item only if it is currently loaded (will load the item if required when this flag isn't set)

#### enum `EContentBrowserItemDataAttributeValueType`  
`enum class EContentBrowserItemDataAttributeValueType : uint8`  
_L71-81_
- desc: Enum denoting the types of values that an item attribute can store
- L74 _public enumerator_ `None` — No value is set
- L76 _public enumerator_ `String` — An FString value is set
- L78 _public enumerator_ `Name` — An FName value is set
- L80 _public enumerator_ `Text` — An FText value is set

#### enum `EContentBrowserItemUpdateType`  
`enum class EContentBrowserItemUpdateType : uint8`  
_L84-96_
- desc: Enum denoting the types of updates that can be emitted for an item
- L87 _public enumerator_ `Added` — This item was newly added
- L89 _public enumerator_ `Modified` — This item already existed, and has been modified
- L91 _public enumerator_ `Moved` — This item already existed, and has been moved to a new location or renamed
- L93 _public enumerator_ `Removed` — This item existed and has been deleted
- L95 _public enumerator_ `Unmounted` — This item existed and has been unmounted

#### class `IContentBrowserItemDataPayload`  
`class IContentBrowserItemDataPayload`  
_L102-106_
- desc: Interface used to store any data source defined payload data that is required to operate on the underlying thing that a Content Browser item represents. @note This is deliberately opaque as only the owner data source should know what it is.
- L105 _public prototype_ `virtual ~IContentBrowserItemDataPayload() = default;`

#### class `FContentBrowserItemData`  
`class FContentBrowserItemData final`  
_L122-311_
- desc: The primitive data that represents an internal Content Browser item, as defined and managed by a Content Browser data source. FContentBrowserItemData itself is a concrete type, so extensibility is handled via the IContentBrowserItemDataPayload interface, which can be used to store any data source defined payload data that is required to operate on the underlying thing that this item represents. FContentBrowserItemData has no real functionality, and relies on passing itself back into the correct data source instance when asked to perform actions or validation. @note This is the lower-level version of FContentBrowserItem, and is used internally by data sources. External code is more likely to use FContentBrowserItem directly, as that type can composite multiple internal items together (eg, combining equivalent folder items from different data sources). @see UContentBrowserDataSource.
- L129 _public prototype_ `FContentBrowserItemData() = default;` — Default constructor. Produces an item that is empty (IsValid() will return false).
- L145 _public prototype_ `FContentBrowserItemData( UContentBrowserDataSource* InOwnerDataSource, EContentBrowserItemFlags InItemFlags, FName InVirtualPath, FName InItemName, FText InDisplayNameOverride, TSharedPtr<const IContentBrowserItemDataPayload> InPayload, FName InInternalPath);` — Create an internal Content Browser item. @param InOwnerDataSource A pointer to the data source that manages the thing represented by this item. This is usually set, but may be null in rare circumstances (ie, creating a dummy placeholder item with no owner). @param InItemFlags Flags denoting basic state information for this item instance. @param InVirtualPath The complete virtual path that uniquely identifies this item within its owner data source (eg, "/MyRoot/MyFolder/MyFile"). @param InItemName The leaf-name of this item (eg, "MyFile"). @param InDisplayNameOverride The user-facing name of this item (eg, "MyFile"). This will be lazily set to InItemName if no override is provided. @param InPayload Any data source defined payload data for this item. @param InInternalPath Internal path if any (some items such as "virtual folders" may not have an internal path)
- L157 _public prototype_ `FContentBrowserItemData(const FContentBrowserItemData&) = default;` — Copy support.
- L158 _public prototype_ `FContentBrowserItemData& operator=(const FContentBrowserItemData&) = default;`
- L163 _public prototype_ `FContentBrowserItemData(FContentBrowserItemData&&) = default;` — Move support.
- L164 _public prototype_ `FContentBrowserItemData& operator=(FContentBrowserItemData&&) = default;`
- L169 _public prototype_ `bool operator==(const FContentBrowserItemData& InOther) const;` — Comparison support.
- L170 _public prototype_ `bool operator!=(const FContentBrowserItemData& InOther) const;`
- L175 _public prototype_ `bool IsValid() const;` — Check to see whether this item is valid (is either a folder or a file).
- L181 _public prototype_ `bool IsFolder() const;` — Check to see whether this item is a folder. @note Equivalent to testing whether EContentBrowserItemFlags::Type_Folder is set on GetItemFlags().
- L187 _public prototype_ `bool IsFile() const;` — Check to see whether this item is a file. @note Equivalent to testing whether EContentBrowserItemFlags::Type_File is set on GetItemFlags().
- L193 _public prototype_ `bool IsPlugin() const;` — Check to see whether this item is in a plugin. Folders and files inside plugins return true, folders which contain and organize plugins do not.
- L200 _public prototype_ `bool IsSupported() const;` — Check if the item is representing a supported item The content browser can also display some unsupported asset @note Equivalent to testing whether EContentBrowserItemFlags::Misc_Unsupported is not set on GetItemFlags()
- L206 _public prototype_ `bool IsTemporary() const;` — Check to see whether this item is temporary. @note Equivalent to testing whether any of EContentBrowserItemFlags::Temporary_MASK is set on GetItemFlags().
- L212 _public prototype_ `bool IsDisplayOnlyFolder() const;` — Check to see whether this item is a display only folder. @note Equivalent to testing whether all of EContentBrowserItemFlags::Category_MASK are unset on GetItemFlags().
- L218 _public prototype_ `UContentBrowserDataSource* GetOwnerDataSource() const;` — Get the pointer to the data source that manages the thing represented by this item. @note This is usually set for valid items, but may be null in rare circumstances (ie, creating a dummy placeholder item with no owner).
- L223 _public prototype_ `EContentBrowserItemFlags GetItemFlags() const;` — Get the flags denoting basic state information for this item instance.
- L229 _public prototype_ `EContentBrowserItemFlags GetItemType() const;` — Get the flags denoting the item type information for this item instance. @note Equivalent to applying EContentBrowserItemFlags::Type_MASK to GetItemFlags().
- L235 _public prototype_ `EContentBrowserItemFlags GetItemCategory() const;` — Get the flags denoting the item category information for this item instance. @note Equivalent to applying EContentBrowserItemFlags::Category_MASK to GetItemFlags().
- L241 _public prototype_ `EContentBrowserItemFlags GetItemTemporaryReason() const;` — Get the flags denoting the item temporary reason information for this item instance. @note Equivalent to applying EContentBrowserItemFlags::Temporary_MASK to GetItemFlags().
- L246 _public prototype_ `FName GetVirtualPath() const;` — Get the complete virtual path that uniquely identifies this item within its owner data source (eg, "/All/MyRoot/MyFolder/MyFile").
- L252 _public prototype_ `FName GetInvariantPath() const;` — Get the complete invariant path that uniquely identifies this item within its owner data source (eg, "/MyRoot/MyFolder/MyFile"). This path will be the same regardless of the options being toggled 'Show All Folder' or 'Organize Folders'
- L257 _public prototype_ `FName GetInternalPath() const;` — Get the complete internal path that uniquely identifies this item within its owner data source if it has one (eg, "/MyRoot/MyFolder/MyFile").
- L262 _public prototype_ `FName GetItemName() const;` — Get the leaf-name of this item (eg, "MyFile").
- L267 _public prototype_ `FText GetDisplayName() const;` — Get the user-facing name of this item (eg, "MyFile").
- L276 _public prototype_ `bool GetItemAssetAccessSpecifier(EAssetAccessSpecifier& OutAssetAccessSpecifier) const;` — Query the EAssetAccessSpecifier of the item. @param OutAssetAccessSpecifier The EAssetAccessSpecifier reference that will be filled. @return True if OutAssetAccessSpecifier was filled.
- L283 _public prototype_ `bool CanModifyItemAssetAccessSpecifier() const;` — Query the item's ability to modify its EAssetAccessSpecifier. @return True if the item has an EAssetAccessSpecifier that can be modified.
- L288 _public prototype_ `TSharedPtr<const IContentBrowserItemDataPayload> GetPayload() const;` — Get any data source defined payload data for this item.
- L292 _private member_ `TWeakObjectPtr<UContentBrowserDataSource> OwnerDataSource;` — A pointer to the data source that manages the thing represented by this item. This is usually set for valid items, but may be null in rare circumstances (ie, creating a dummy placeholder item with no owner)
- L295 _private member_ `EContentBrowserItemFlags ItemFlags = EContentBrowserItemFlags::None;` — Flags denoting basic state information for this item instance
- L298 _private member_ `FName VirtualPath;` — The complete virtual path that uniquely identifies this item within its owner data source (eg, "/MyRoot/MyFolder/MyFile")
- L301 _private member_ `FName ItemName;` — The leaf-name of this item (eg, "MyFile")
- L304 _private member_ `FName InternalPath;` — Internal path used to identify item within the owner data source
- L307 _private member_ `FText CachedDisplayName;` — The user-facing name of this item (eg, "MyFile")
- L310 _private member_ `TSharedPtr<const IContentBrowserItemDataPayload> Payload;` — Any data source defined payload data for this item

#### class `FContentBrowserItemDataAttributeMetaData`  
`class FContentBrowserItemDataAttributeMetaData`  
_L317-354_
- desc: Type describing the meta-data associated with an item attribute value. This provides additional context and information that can be used to interpret and display the value.
- L323 _public prototype_ `FContentBrowserItemDataAttributeMetaData() = default;` — Constructor.
- L328 _public prototype_ `FContentBrowserItemDataAttributeMetaData(const FContentBrowserItemDataAttributeMetaData&) = default;` — Copy support.
- L329 _public prototype_ `FContentBrowserItemDataAttributeMetaData& operator=(const FContentBrowserItemDataAttributeMetaData&) = default;`
- L334 _public prototype_ `FContentBrowserItemDataAttributeMetaData(FContentBrowserItemDataAttributeMetaData&&) = default;` — Move support.
- L335 _public prototype_ `FContentBrowserItemDataAttributeMetaData& operator=(FContentBrowserItemDataAttributeMetaData&&) = default;`
- L338 _public member_ `UObject::FAssetRegistryTag::ETagType AttributeType = UObject::FAssetRegistryTag::TT_Hidden;` — The kind of data represented by this attribute value
- L341 _public member_ `uint32 DisplayFlags = UObject::FAssetRegistryTag::TD_None;` — Flags giving hints at how to display this attribute value in the UI (see ETagDisplay)
- L344 _public member_ `FText DisplayName;` — Resolved display name of the associated attribute
- L347 _public member_ `FText TooltipText;` — Optional tooltip of the associated attribute
- L350 _public member_ `FText Suffix;` — Optional suffix to apply to values of the associated attribute in the UI
- L353 _public member_ `bool bIsImportant = false;` — True if this attribute value is considered "important" in the UI

#### class `FContentBrowserItemDataAttributeValue`  
`class FContentBrowserItemDataAttributeValue`  
_L360-482_
- desc: Type describing the value of an item attribute. Internally this is optimized to store the value as either an FString, FName, or FText.
- L367 _public prototype_ `FContentBrowserItemDataAttributeValue() = default;` — Default constructor. Produces an attribute value that is empty (IsValid() will return false).
- L372 _public prototype_ `explicit FContentBrowserItemDataAttributeValue(const TCHAR* InStr);` — Construct this attribute value from the given string.
- L373 _public prototype_ `explicit FContentBrowserItemDataAttributeValue(const FString& InStr);`
- L374 _public prototype_ `explicit FContentBrowserItemDataAttributeValue(FString&& InStr);`
- L379 _public prototype_ `explicit FContentBrowserItemDataAttributeValue(const FName InName);` — Construct this attribute value from the given name.
- L384 _public prototype_ `explicit FContentBrowserItemDataAttributeValue(FText InText);` — Construct this attribute value from the given text.
- L389 _public prototype_ `FContentBrowserItemDataAttributeValue(const FContentBrowserItemDataAttributeValue&) = default;` — Copy support.
- L390 _public prototype_ `FContentBrowserItemDataAttributeValue& operator=(const FContentBrowserItemDataAttributeValue&) = default;`
- L395 _public prototype_ `FContentBrowserItemDataAttributeValue(FContentBrowserItemDataAttributeValue&&) = default;` — Move support.
- L396 _public prototype_ `FContentBrowserItemDataAttributeValue& operator=(FContentBrowserItemDataAttributeValue&&) = default;`
- L401 _public prototype_ `bool IsValid() const;` — Check to see whether this attribute value is valid (has been set to an internal value).
- L406 _public prototype_ `void Reset();` — Reset this attribute value to its empty default state.
- L411 _public prototype_ `EContentBrowserItemDataAttributeValueType GetValueType() const;` — Get the value denoting what type of internal value is stored within this attribute value.
- L418 _public prototype_ `template <typename ValueAttrType> ValueAttrType GetValue() const;` — Get this attribute value as the requested type, converting its internal value to the given type if required. @note This function is specialized for FString, FName, and FText, with the generic implementation requiring a LexFromString implementation for the requested type.
- L426 _public prototype_ `template <typename ValueAttrType> void SetValue(ValueAttrType InValue);` — Set this attribute value from the given type, converting it to a type we can store internally if required. @note This function is overloaded for FString, FName, and FText, with the generic implementation requiring a LexToString implementation for the given type. @note This function will reset the type during the set, so will also clear any currently associated meta-data.
- L427 _public prototype_ `void SetValue(const TCHAR* InStr);`
- L428 _public prototype_ `void SetValue(const FString& InStr);`
- L429 _public prototype_ `void SetValue(FString&& InStr);`
- L430 _public prototype_ `void SetValue(const FName InName);`
- L431 _public prototype_ `void SetValue(FText InText);`
- L436 _public prototype_ `FStringView GetValueStringView(FStringBuilderBase& ScratchBuffer) const;` — Get this attribute value as a string view, converting its internal value using the scratch buffer if required (if ValueType == Name).
- L442 _public prototype_ `const FString& GetValueString() const;` — Get the internal string value. @note Only valid when ValueType == String.
- L448 _public prototype_ `FName GetValueName() const;` — Get the internal name value. @note Only valid when ValueType == Name.
- L454 _public prototype_ `FText GetValueText() const;` — Get the internal text value. @note Only valid when ValueType == Name.
- L459 _public prototype_ `const FContentBrowserItemDataAttributeMetaData& GetMetaData() const;` — Get the meta-data associated with this attribute value.
- L464 _public prototype_ `void SetMetaData(const FContentBrowserItemDataAttributeMetaData& InMetaData);` — Set the meta-data associated with this attribute value.
- L465 _public prototype_ `void SetMetaData(FContentBrowserItemDataAttributeMetaData&& InMetaData);`
- L469 _private member_ `EContentBrowserItemDataAttributeValueType ValueType = EContentBrowserItemDataAttributeValueType::None;` — Value denoting what type of internal value is stored within this attribute value
- L472 _private member_ `FString StrValue;` — Internal string value
- L475 _private member_ `FName NameValue;` — Internal name value
- L478 _private member_ `FText TextValue;` — Internal text value
- L481 _private member_ `TSharedPtr<const FContentBrowserItemDataAttributeMetaData> MetaData;` — Meta-data associated with this attribute value
- L485 _function_ `template <typename ValueAttrType> inline ValueAttrType FContentBrowserItemDataAttributeValue::GetValue() const`
- L515 _function_ `template <> inline FString FContentBrowserItemDataAttributeValue::GetValue<FString>() const`
- L533 _function_ `template <> inline FText FContentBrowserItemDataAttributeValue::GetValue<FText>() const`
- L551 _function_ `template <> inline FName FContentBrowserItemDataAttributeValue::GetValue<FName>() const`
- L569 _function_ `template <typename ValueAttrType> void FContentBrowserItemDataAttributeValue::SetValue(ValueAttrType InValue)`

#### class `FContentBrowserItemDataTemporaryContext`  
`class FContentBrowserItemDataTemporaryContext`  
_L581-647_
- desc: Context for asynchronous item creation (for new items or duplicating existing ones). Data sources will return one of these (hosting a temporary item with any required context) when they want to begin the creation or duplication of an item item. UI involved in this creation flow should call ValidateItem for any name changes, as well as before calling FinalizeItem. Once finalized the temporary item should be replaced with the real one.
- L585 _public prototype_ `DECLARE_DELEGATE_RetVal_ThreeParams(bool, FOnValidateItem, const FContentBrowserItemData& , const FString& , FText* );` — Delegate used to validate that the proposed item name is valid
- L588 _public prototype_ `DECLARE_DELEGATE_RetVal_ThreeParams(FContentBrowserItemData, FOnFinalizeItem, const FContentBrowserItemData& , const FString& , FText* );` — Delegate used to finalize the creation of the temporary item, and return the real item
- L594 _public prototype_ `FContentBrowserItemDataTemporaryContext() = default;` — Default constructor. Produces a context that is empty (IsValid() will return false).
- L603 _public prototype_ `FContentBrowserItemDataTemporaryContext(FContentBrowserItemData&& InItemData, FOnValidateItem InOnValidateItem, FOnFinalizeItem InOnFinalizeItem);` — Create a context instance. @param InItemData Data representing the temporary item instance. @param InOnValidateItem Delegate used to validate that the proposed item name is valid (optional). @param InOnFinalizeItem Delegate used to finalize the creation of the temporary item, and return the real item.
- L608 _public prototype_ `FContentBrowserItemDataTemporaryContext(const FContentBrowserItemDataTemporaryContext&) = default;` — Copy support.
- L609 _public prototype_ `FContentBrowserItemDataTemporaryContext& operator=(const FContentBrowserItemDataTemporaryContext&) = default;`
- L614 _public prototype_ `FContentBrowserItemDataTemporaryContext(FContentBrowserItemDataTemporaryContext&&) = default;` — Move support.
- L615 _public prototype_ `FContentBrowserItemDataTemporaryContext& operator=(FContentBrowserItemDataTemporaryContext&&) = default;`
- L620 _public prototype_ `bool IsValid() const;` — Check to see whether this context is valid (has been set to a temporary item).
- L625 _public prototype_ `const FContentBrowserItemData& GetItemData() const;` — Get the data representing the temporary item instance.
- L631 _public prototype_ `bool ValidateItem(const FString& InProposedName, FText* OutErrorMsg = nullptr) const;` — Invoke the delegate used to validate that the proposed item name is valid. @note Returns True if no validation delegate is bound.
- L636 _public prototype_ `FContentBrowserItemData FinalizeItem(const FString& InProposedName, FText* OutErrorMsg = nullptr) const;` — Invoke the delegate used to finalize the creation of the temporary item, and return the real item.
- L640 _private member_ `FContentBrowserItemData ItemData;` — Data representing the temporary item instance
- L643 _private member_ `FOnValidateItem OnValidateItem;` — Delegate used to validate that the proposed item name is valid (optional)
- L646 _private member_ `FOnFinalizeItem OnFinalizeItem;` — Delegate used to finalize the creation of the temporary item, and return the real item

#### class `FContentBrowserMinimalItemData`  
`class FContentBrowserMinimalItemData`  
_L654-701_
- desc: Minimal representation of a FContentBrowserItemData instance for comparison purposes. @note Unlike FContentBrowserItemDataKey this does consider the data source, and unlike FContentBrowserItemKey it considers the data source for folder items. It can be used to identify a FContentBrowserItemData for removal from an FContentBrowserItem
- L657 _public prototype_ `explicit FContentBrowserMinimalItemData(const FContentBrowserItemData& InItemData);`
- L658 _public prototype_ `FContentBrowserMinimalItemData(EContentBrowserItemFlags InItemType, FName InVirtualPath, const UContentBrowserDataSource* InSource);`
- L660 _public function_ `bool operator==(const FContentBrowserMinimalItemData& Other) const`
- L664 _public function_ `bool operator!=(const FContentBrowserMinimalItemData& Other) const`
- L670 _public prototype_ `FString ToString() const;` — Return a string representation for debugging.
- L672 _public function_ `EContentBrowserItemFlags GetItemType() const`
- L677 _public function_ `FName GetVirtualPath() const`
- L682 _public function_ `const UContentBrowserDataSource* GetDataSource() const`
- L692 _private member_ `EContentBrowserItemFlags ItemType = EContentBrowserItemFlags::None;` — Flags denoting the item type information for an item instance. @note This is always masked against EContentBrowserItemFlags::Type_MASK to remove any non-type information.
- L697 _private member_ `FName VirtualPath;` — The complete virtual path that uniquely identifies an item within its owner data source.
- L700 _private member_ `const UContentBrowserDataSource* DataSource = nullptr;` — A pointer to the data source that manages the thing represented by this key

#### class `FContentBrowserItemDataKey`  
`class FContentBrowserItemDataKey`  
_L708-763_
- desc: Minimal representation of a FContentBrowserItemData instance that can be used as a map key. @note This key doesn't consider the data source, so should only be used for maps within a given data source. Use FContentBrowserItemKey for more general use where items may have come from different data sources.
- L715 _public prototype_ `FContentBrowserItemDataKey() = default;` — Default constructor. Produces a key that is empty.
- L720 _public prototype_ `explicit FContentBrowserItemDataKey(const FContentBrowserItemData& InItemData);` — Construct this key from the given item.
- L725 _public prototype_ `FContentBrowserItemDataKey(EContentBrowserItemFlags InItemType, FName InVirtualPath);` — Construct this key from the given item type and virtual path.
- L730 _public function_ `bool operator==(const FContentBrowserItemDataKey& InOther) const` — Equality support.
- L739 _public function_ `bool operator!=(const FContentBrowserItemDataKey& InOther) const` — Inequality support.
- L757 _protected member_ `EContentBrowserItemFlags ItemType = EContentBrowserItemFlags::None;` — Flags denoting the item type information for an item instance. @note This is always masked against EContentBrowserItemFlags::Type_MASK to remove any non-type information.
- L762 _protected member_ `FName VirtualPath;` — The complete virtual path that uniquely identifies an item within its owner data source.

#### class `FContentBrowserItemDataUpdate`  
`class FContentBrowserItemDataUpdate`  
_L768-820_
- desc: Type describing an update to an item.
- L774 _public prototype_ `static FContentBrowserItemDataUpdate MakeItemAddedUpdate(FContentBrowserItemData InItemData);` — Create an item update for when a new item is added.
- L779 _public prototype_ `static FContentBrowserItemDataUpdate MakeItemModifiedUpdate(FContentBrowserItemData InItemData);` — Create an item update for when an existing item is updated.
- L784 _public prototype_ `static FContentBrowserItemDataUpdate MakeItemMovedUpdate(FContentBrowserItemData InItemData, FName InPreviousVirtualPath);` — Create an item update for when an existing item is moved (or renamed), including its previous virtual path.
- L789 _public prototype_ `static FContentBrowserItemDataUpdate MakeItemRemovedUpdate(FContentBrowserItemData InItemData);` — Create an item update for when an item is deleted.
- L794 _public prototype_ `static FContentBrowserItemDataUpdate MakeItemUnmountedUpdate(FContentBrowserItemData InItemData);` — Create an item update for when an item is unmounted.
- L799 _public prototype_ `EContentBrowserItemUpdateType GetUpdateType() const;` — Get the value denoting the types of updates that can be emitted for an item.
- L804 _public prototype_ `const FContentBrowserItemData& GetItemData() const;` — Get the item data for the update.
- L809 _public prototype_ `FName GetPreviousVirtualPath() const;` — Get the previous virtual path (UpdateType == Moved).
- L813 _private member_ `EContentBrowserItemUpdateType UpdateType;` — Value denoting the types of updates that can be emitted for an item
- L816 _private member_ `FContentBrowserItemData ItemData;` — Item data for the update
- L819 _private member_ `FName PreviousVirtualPath;` — Previous virtual path (UpdateType == Moved)

#### class `IContentBrowserItemDataSink`  
`class IContentBrowserItemDataSink`  
_L825-848_
- desc: The data sink interface that can be used to communicate with the Content Browser Data Subsystem.
- L831 _public prototype_ `virtual ~IContentBrowserItemDataSink() = default;` — Destructor.
- L836 _public prototype_ `virtual void QueueItemDataUpdate(FContentBrowserItemDataUpdate&& InUpdate) = 0;` — Queue an incremental item data update, for data sources that can provide delta-updates.
- L842 _public prototype_ `virtual void NotifyItemDataRefreshed() = 0;` — `UE_DEPRECATED(5.5, "NotifyItemDataRefreshed is deprecated, for editor performance reasons no external systems should be able to request a full refresh.")` — Notify a wholesale item data update, for data sources that can't provide delta-updates.
- L847 _public prototype_ `virtual void ConvertInternalPathToVirtual(const FStringView InPath, FStringBuilderBase& OutPath) = 0;` — Converts an internal path to a virtual path.

#### Free symbols / members of external scopes

- L22 _macro_ `#define UE_API CONTENTBROWSERDATA_API`
- L56 _prototype_ `ENUM_CLASS_FLAGS(EContentBrowserItemFlags);`
- L68 _prototype_ `ENUM_CLASS_FLAGS(EContentBrowserItemSaveFlags);`
- L574 _typedef_ `typedef TMap<FName, FContentBrowserItemDataAttributeValue> FContentBrowserItemDataAttributeValues;`
- L585 _delegate_ `DECLARE_DELEGATE_RetVal_ThreeParams(bool, FOnValidateItem, const FContentBrowserItemData& , const FString& , FText* );` — Delegate used to validate that the proposed item name is valid
- L588 _delegate_ `DECLARE_DELEGATE_RetVal_ThreeParams(FContentBrowserItemData, FOnFinalizeItem, const FContentBrowserItemData& , const FString& , FText* );` — Delegate used to finalize the creation of the temporary item, and return the real item
- L747 _function_ `friend inline uint32 GetTypeHash(const FContentBrowserItemDataKey& InKey)` — Get the hash of the given instance.

### `Source/Editor/ContentBrowserData/Public/ContentBrowserItemPath.h` (Public)


#### struct `FContentBrowserItemPath`  
`struct FContentBrowserItemPath`  
_L30-94_
- reflection: `USTRUCT(BlueprintType, meta=(HasNativeBreak="/Script/ContentBrowserData.ContentBrowserItemPathExtensions.BreakContentBrowserItemPath", HasNativeMake="/Script/ContentBrowserData.ContentBrowserItemPathExtensions.MakeContentBrowserItemPath"))`
- desc: Hold multiple versions of a path as FNames Path conversion each time Set is called
- L34 _public prototype_ `FContentBrowserItemPath();`
- L36 _public function_ `FContentBrowserItemPath(const FName InVirtualPath, const FName InInternalPath) : VirtualPath(InVirtualPath) , InternalPath(InInternalPath)`
- L44 _public prototype_ `FContentBrowserItemPath(const FStringView InPath, const EContentBrowserPathType InPathType);`
- L45 _public prototype_ `FContentBrowserItemPath(const TCHAR* InPath, const EContentBrowserPathType InPathType);`
- L46 _public prototype_ `FContentBrowserItemPath(const FName InPath, const EContentBrowserPathType InPathType);`
- L48 _public function_ `bool operator==(const FContentBrowserItemPath& Other) const`
- L56 _public prototype_ `void SetPathFromString(const FStringView InPath, const EContentBrowserPathType InPathType);` — Set the path being stored
- L61 _public prototype_ `void SetPathFromName(const FName InPath, const EContentBrowserPathType InPathType);` — Set the path being stored
- L66 _public prototype_ `FName GetVirtualPathName() const;` — Returns virtual path as FName (eg, "/All/Plugins/PluginA/MyFile").
- L71 _public prototype_ `FName GetInternalPathName() const;` — Returns internal path if there is one (eg,. "/PluginA/MyFile").
- L76 _public prototype_ `FString GetVirtualPathString() const;` — Returns virtual path as newly allocated FString (eg, "/All/Plugins/PluginA/MyFile").
- L81 _public prototype_ `FString GetInternalPathString() const;` — Returns internal path as newly allocated FString if there is one or empty FString (eg,. "/PluginA/MyFile").
- L86 _public prototype_ `bool HasInternalPath() const;` — Returns true if there is an internal path
- L90 _private member_ `FName VirtualPath;` — Path as virtual (eg, "/All/Plugins/PluginA/MyFile")
- L93 _private member_ `FName InternalPath;` — Path as internal (eg,. "/PluginA/MyFile")

#### class `UContentBrowserItemPathExtensions`  
`class UContentBrowserItemPathExtensions : public UBlueprintFunctionLibrary`  
_L97-142_
- reflection: `UCLASS()`
- inherits: `UBlueprintFunctionLibrary`
- L107 _public function_ `static void SetPath(UPARAM(ref) FContentBrowserItemPath& ItemPath, const FName InPath, const EContentBrowserPathType InPathType)` — `UFUNCTION(BlueprintCallable, Category = "Content Browser", meta = (ScriptMethod))` — Set the path being stored
- L116 _public function_ `static FName GetVirtualPath(const FContentBrowserItemPath& ItemPath)` — `UFUNCTION(BlueprintCallable, Category = "Content Browser", meta = (ScriptMethod))` — Returns virtual path as FName (eg, "/All/Plugins/PluginA/MyFile").
- L125 _public function_ `static FName GetInternalPath(const FContentBrowserItemPath& ItemPath)` — `UFUNCTION(BlueprintCallable, Category = "Content Browser", meta = (ScriptMethod))` — Returns internal path if there is one (eg,. "/PluginA/MyFile").
- L131 _public function_ `static FContentBrowserItemPath MakeContentBrowserItemPath(const FName InPath, const EContentBrowserPathType InPathType)` — `UFUNCTION(BlueprintPure, Category = "Content Browser", meta = (Keywords = "construct build", NativeMakeFunc))`
- L137 _public function_ `static void BreakContentBrowserItemPath(const FContentBrowserItemPath& ItemPath, FName& VirtualPath, FName& InternalPath)` — `UFUNCTION(BlueprintPure, Category = "Content Browser", meta = (NativeBreakFunc))`

#### Free symbols / members of external scopes

- L19 _macro_ `#define UE_API CONTENTBROWSERDATA_API`

### `Source/Editor/ContentBrowserData/Public/ContentBrowserVirtualPathTree.h` (Public)


#### class `FContentBrowserVirtualPathTree`  
`class FContentBrowserVirtualPathTree`  
_L22-114_
- desc: Tree of virtual paths ending where internal paths start. Used for conversion of paths and during enumerate.
- L26 _public prototype_ `bool CachePath(FName Path, FName InternalPath, TFunctionRef<void(FName)> OnPathAdded);` — Adds the specified path to the tree, creating nodes as needed and calling OnPathAdded for any new paths added. Returns true if the specified path was actually added (as opposed to already existed)
- L29 _public prototype_ `bool RemovePath(FName Path, TFunctionRef<void(FName)> OnPathRemoved);` — Removes the specified path from the tree, calling OnPathRemoved for any existing paths removed. Returns true if the path was found and removed.
- L32 _public prototype_ `bool PathExists(FName Path, bool& bIsFullyVirtual) const;` — Checks whether the given path is one that we know about
- L35 _public function_ `bool PathExists(FName Path) const` — Checks whether the given path is one that we know about
- L42 _public prototype_ `bool GetAllPaths(TSet<FName>& OutPaths) const;` — Get all of the paths we know about
- L45 _public prototype_ `void EnumerateAllPaths(TFunctionRef<bool(FName)> Callback) const;` — Enumerate all of the paths we know about
- L48 _public prototype_ `bool GetSubPaths(FName BasePath, TSet<FName>& OutPaths, bool bRecurse = true) const;` — Recursively gathers all child paths from the specified base path relative to this node
- L51 _public prototype_ `bool EnumerateSubPaths(FName BasePath, TFunctionRef<bool(FName, FName)> Callback, bool bRecurse = true) const;` — Recursively enumerates all child paths from the specified base path relative to this node
- L53 _public function_ `SIZE_T GetAllocatedSize(void) const`
- L66 _public prototype_ `void Reset();` — Clears all paths
- L69 _public prototype_ `FName GetParentPath(FName Path) const;` — Returns name of parent virtual path when given a virtual path
- L72 _public prototype_ `int32 NumPaths() const;` — Returns number of paths in total
- L75 _public function_ `const TMap<FName, FName>& GetVirtualToInternalMounts() const` — Returns reference to map that allows looking up an internal path when given a virtual path
- L86 _public prototype_ `static FStringView GetMountPointFromPath(const FStringView InPath, bool& bOutHadClassesPrefix);` — @note Use FPathViews::GetMountPointNameFromPath instead Returns name of the first folder in a path Removes starting forward slash and Classes_ prefix Example: "/Classes_A/Textures" returns "A" and sets bOutHadClassesPrefix=true
- L94 _public prototype_ `EContentBrowserPathType TryConvertVirtualPathToInternal(FStringView InPath, FStringBuilderBase& OutPath) const;` — Tries to converts virtual path into an internal path. Returns None if virtual prefix portion of the path does not exist in this path tree Returns Virtual if virtual prefix portion of the path exists in this path tree and there is no text past the virtual prefix portion Returns Internal if virtual prefix portion of the path exists in this path tree and there is text afterwards @Note: When Internal is the return value it does not check to see if the internal path actually exists or not
- L95 _public prototype_ `EContentBrowserPathType TryConvertVirtualPathToInternal(FStringView InPath, FString& OutPath) const;`
- L96 _public prototype_ `EContentBrowserPathType TryConvertVirtualPathToInternal(FName InPath, FName& OutPath) const;`
- L101 _private prototype_ `bool IsShowAllFolderEnabled() const;` — Is the user option to show the all folder enabled
- L104 _private prototype_ `const FString& GetAllFolderPrefix() const;` — Get the string to use when show all folder is enabled
- L107 _private member_ `TMap<FName, FName> VirtualToInternalMounts;` — A one-to-one mapping between a virtual path and internal path
- L110 _private member_ `TMap<FName, TSet<FName>> ParentPathToChildPaths;` — A one-to-many mapping between a parent path and its child paths.
- L113 _private member_ `TMap<FName, FName> ChildPathToParentPath;` — A one-to-one mapping between a child path and its parent path. Paths without a parent (root paths) will not appear in this map.

#### Free symbols / members of external scopes

- L14 _macro_ `#define UE_API CONTENTBROWSERDATA_API`

### `Source/Editor/ContentBrowserData/Public/GetOrEnumerateSink.h` (Public)


#### class `TGetOrEnumerateSink`  
`template<typename ItemType> class TGetOrEnumerateSink`  
_L18-62_
- desc: Utility class to simplify implementation of data sources that can be called as 'get' (fill an array) or 'enumerate' (call a callback). Usage: Functions should take TGetOrEnumerateSink by value or const ref to allow in-place construction. @tparam ItemType The type of item produced. The sink can be constructed with TArray<ItemType> or TFunctionRef<ItemType&&>.
- L21 _public function_ `explicit TGetOrEnumerateSink(TFunctionRef<bool(ItemType&&)> InCallback) : Callback(MoveTemp(InCallback))`
- L25 _public function_ `explicit TGetOrEnumerateSink(TArray<ItemType>& InOutput) : Array(&InOutput)`
- L31 _public prototype_ `TGetOrEnumerateSink(const TGetOrEnumerateSink&) = default;` — Allow copying for delegation to other methods if desired. Just copies pointers into sink. No state needs to be maintained between copies.
- L32 _public prototype_ `TGetOrEnumerateSink& operator=(const TGetOrEnumerateSink&) = default;`
- L35 _public prototype_ `TGetOrEnumerateSink(TGetOrEnumerateSink&&) = default;` — Allow moving to delegate the sink into other calls
- L36 _public prototype_ `TGetOrEnumerateSink& operator=(TGetOrEnumerateSink&&) = default;`
- L38 _public function_ `void ReserveMore(int32 NumAdditionalItems) const`
- L46 _public function_ `bool ProduceItem(ItemType&& Item) const`
- L60 _private member_ `TArray<ItemType>* Array = nullptr;`
- L61 _private member_ `TOptional<TFunctionRef<bool(ItemType&&)>> Callback;`

### `Source/Editor/ContentBrowserData/Public/IContentBrowserDataModule.h` (Public)


#### class `IContentBrowserDataModule`  
`class IContentBrowserDataModule : public IModuleInterface`  
_L11-40_
- inherits: `IModuleInterface`
- L14 _public prototype_ `virtual ~IContentBrowserDataModule() = default;`
- L22 _public function_ `static IContentBrowserDataModule& Get()` — Singleton-like access to this module's interface. @note Beware of calling this during the shutdown phase. Your module might have been unloaded already (@see GetPtr). @return Returns the singleton instance, loading the module on demand if needed.
- L33 _public function_ `static IContentBrowserDataModule* GetPtr()` — Singleton-like access to this module's interface. @return Returns singleton instance, or null if the module isn't loaded or has been unloaded.
- L39 _public prototype_ `virtual UContentBrowserDataSubsystem* GetSubsystem() const = 0;`
