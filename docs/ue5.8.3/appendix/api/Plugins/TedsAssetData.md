# Plugins / TedsAssetData

- module root: `Plugins/Experimental/EditorDataStorageFeatures/Source/TedsAssetData`
- headers: 29; symbols: 429
- symbol kinds: class=27, delegate=3, function=3, member=97, namespace=49, prototype=200, struct=49, variable=1
- PrivateDependencyModuleNames: AssetDefinition, AssetRegistry, AssetTools, ContentBrowserData, Core, CoreUObject, Engine, Slate, SlateCore, TedsAlerts, TedsTableViewer, ToolWidgets, TypedElementFramework, UnrealEd
- PublicDependencyModuleNames: ContentBrowser, Projects

### `Plugins/Experimental/EditorDataStorageFeatures/Source/TedsAssetData/Private/CB/TagsMetadataCache.h` (Private)


#### class `UE::Editor::AssetData::Private::FTagsMetadataCache`  
`class FTagsMetadataCache`  
_L15-48_
- L31 _public prototype_ `void CacheClass(FTopLevelAssetPath InClassName);`
- L33 _public prototype_ `const FClassPropertiesCache* FindCacheForClass(FTopLevelAssetPath InClassName) const;`
- L36 _public function_ `template<typename TContainer> void BatchCacheClasses(const TContainer& InClasses)`
- L47 _private member_ `TMap<FTopLevelAssetPath, FClassPropertiesCache> ClassPathToCachedClass;`

#### struct `UE::Editor::AssetData::Private::FTagsMetadataCache::FClassPropertiesCache`  
`struct FClassPropertiesCache`  
_L19-28_
- L22 _public prototype_ `TSharedPtr<UE::Editor::AssetData::FItemAttributeMetadata> GetCacheForTag(const FName InTagName) const;`
- L27 _private member_ `TMap<FName, TSharedPtr<UE::Editor::AssetData::FItemAttributeMetadata>> TagNameToCachedProperty;`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace Editor` (scope `UE`)
- L13 _namespace_ `namespace AssetData` (scope `UE::Editor`)
- L13 _namespace_ `namespace Private` (scope `UE::Editor::AssetData`)

### `Plugins/Experimental/EditorDataStorageFeatures/Source/TedsAssetData/Private/CB/TedsAssetDataCBDataSource.h` (Private)


#### class `UE::Editor::AssetData::Private::FTedsAssetDataCBDataSource`  
`class FTedsAssetDataCBDataSource`  
_L30-93_
- L33 _public prototype_ `explicit FTedsAssetDataCBDataSource(UE::Editor::DataStorage::ICoreProvider& InDatabase);`
- L34 _public prototype_ `~FTedsAssetDataCBDataSource();`
- L37 _public prototype_ `void EnableMetadataStorage(bool bEnable);` — Toggle the storage of the metadata from the asset registry into teds
- L56 _private prototype_ `void InitVirtualPathProcessor();`
- L57 _private prototype_ `void PrepopulateTagsMetadataCache();`
- L60 _private prototype_ `void OnPluginContentMounted(IPlugin& InPlugin);`
- L61 _private prototype_ `void OnPluginUnmounted(IPlugin& InPlugin);`
- L69 _private prototype_ `bool GenerateVirtualPath(const FStringView InAssetPath, FNameBuilder& OutVirtualizedPath) const;` — Check if we should generate a virtual a path to the path and if so do generate a virtualized path for it. @param InAssetPath The internal path to virtualize @param OutVirtualizedPath The virtualized path generated if needed. @return True if the path virtual path was generated.
- L71 _private prototype_ `void AddAssetDataColumns(DataStorage::IQueryContext& Context, DataStorage::RowHandle Row, const FAssetData& AssetData, const FAssetPackageData* OptionalPackageData) const;`
- L73 _private prototype_ `void ProcessPathQueryCallback(DataStorage::IQueryContext& Context, const DataStorage::RowHandle* Rows, const FAssetPathColumn_Experimental* PathColumn) const;`
- L74 _private prototype_ `void ProcessAssetDataPathUpdateQueryCallback(DataStorage::IQueryContext& Context, const DataStorage::RowHandle* Rows, const FAssetDataColumn_Experimental* AssetDataColumn) const;`
- L75 _private prototype_ `void ProcessAssetDataAndPathUpdateQueryCallback(DataStorage::IQueryContext& Context, const DataStorage::RowHandle* Rows, const FAssetDataColumn_Experimental* AssetDataColumn) const;`
- L76 _private prototype_ `void ProcessAssetDataUpdateQueryCallback(DataStorage::IQueryContext& Context, const DataStorage::RowHandle*Rows, const FAssetDataColumn_Experimental* AssetDataColumn) const;`
- L78 _private member_ `UE::Editor::DataStorage::ICoreProvider& Database;`
- L79 _private member_ `DataStorage::QueryHandle ProcessPathQuery;`
- L80 _private member_ `DataStorage::QueryHandle ProcessAssetDataPathUpdateQuery;`
- L81 _private member_ `DataStorage::QueryHandle ProcessAssetDataAndPathUpdateQuery;`
- L82 _private member_ `DataStorage::QueryHandle ProcessAssetDataUpdateQuery;`
- L83 _private member_ `DataStorage::QueryHandle ReprocessesAssetDataColumns;`
- L85 _private member_ `FVirtualPathProcessor VirtualPathProcessor;`
- L86 _private member_ `bool bPopulateMetadataColumns = false;`
- L87 _private member_ `FName RepopulateAssetDataColumns = TEXT("Rep`
- L89 _private member_ `TUniquePtr<FTagsMetadataCache> TagsMetadataCache;`
- L91 _private member_ `const IAssetRegistry* AssetRegistry = nullptr;`

#### struct `UE::Editor::AssetData::Private::FTedsAssetDataCBDataSource::FVirtualPathProcessor`  
`struct FVirtualPathProcessor`  
_L40-54_
- L48 _public member_ `TMap<FString, FCachedPluginData> PluginNameToCachedData;`
- L50 _public member_ `bool bShowAllFolder = false;`
- L51 _public member_ `bool bOrganizeFolders = false;`
- L53 _public prototype_ `void ConvertInternalPathToVirtualPath(const FStringView InternalPath, FStringBuilderBase& OutVirtualPath) const;`

#### struct `UE::Editor::AssetData::Private::FTedsAssetDataCBDataSource::FVirtualPathProcessor::FCachedPluginData`  
`struct FCachedPluginData`  
_L42-46_
- L44 _public member_ `EPluginLoadedFrom LoadedFrom;`
- L45 _public member_ `FString EditorCustomVirtualPath;`

#### Free symbols / members of external scopes

- L21 _namespace_ `namespace UE`
- L21 _namespace_ `namespace Editor` (scope `UE`)
- L21 _namespace_ `namespace DataStorage` (scope `UE::Editor`)
- L27 _namespace_ `namespace UE`
- L27 _namespace_ `namespace Editor` (scope `UE`)
- L27 _namespace_ `namespace AssetData` (scope `UE::Editor`)
- L27 _namespace_ `namespace Private` (scope `UE::Editor::AssetData`)

### `Plugins/Experimental/EditorDataStorageFeatures/Source/TedsAssetData/Private/Processors/AssetProcessors.h` (Private)


#### struct `FUnresolvedFavoriteColumn`  
`struct FUnresolvedFavoriteColumn final : public FEditorDataStorageColumn`  
_L22-27_
- reflection: `USTRUCT(meta = (DisplayName = "Unresolved Favorite"))`
- inherits: `FEditorDataStorageColumn`
- desc: Temp tag added to a row when it is a favorite before TEDS asset data has processed it
- L26 _public member_ `UE::Editor::DataStorage::FMapKey MappingIndex;`

#### class `UTedsAssetDataFactory`  
`class UTedsAssetDataFactory : public UEditorDataStorageFactory`  
_L30-51_
- reflection: `UCLASS()`
- inherits: `UEditorDataStorageFactory`
- L35 _public prototype_ `~UTedsAssetDataFactory() override = default;`
- L37 _public prototype_ `virtual void RegisterTables(UE::Editor::DataStorage::ICoreProvider& DataStorage) override;`
- L38 _public prototype_ `void RegisterQueries(UE::Editor::DataStorage::ICoreProvider& DataStorage) override;`
- L39 _public prototype_ `virtual void PreRegister(UE::Editor::DataStorage::ICoreProvider& DataStorage) override;`
- L40 _public prototype_ `virtual void PostRegister(UE::Editor::DataStorage::ICoreProvider& DataStorage) override;`
- L41 _public prototype_ `virtual void PreShutdown(UE::Editor::DataStorage::ICoreProvider& DataStorage) override;`
- L45 _protected prototype_ `void OnSetFolderColor(const FString& Path, UE::Editor::DataStorage::ICoreProvider* DataStorage);`
- L46 _protected prototype_ `void OnFavoritesChanged(const FContentBrowserItemPath& ItemPath, bool bAdded, UE::Editor::DataStorage::ICoreProvider* DataStorage);`
- L47 _protected prototype_ `void OnAssetDataStorageEnabled(UE::Editor::DataStorage::ICoreProvider* DataStorage);`
- L50 _protected member_ `FDelegateHandle OnFavoritesChangedDelegateHandle;`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace Editor` (scope `UE`)
- L13 _namespace_ `namespace DataStorage` (scope `UE::Editor`)

### `Plugins/Experimental/EditorDataStorageFeatures/Source/TedsAssetData/Private/TedsAssetData.h` (Private)


#### class `UE::Editor::AssetData::Private::FTedsAssetData`  
`class FTedsAssetData`  
_L21-106_
- desc: Manage the registration and life cycle of the row related representing the data from the asset registry into TEDS.
- L26 _public prototype_ `FTedsAssetData(UE::Editor::DataStorage::ICoreProvider& InDatabase);`
- L28 _public prototype_ `~FTedsAssetData();`
- L30 _public prototype_ `void Initialize();`
- L31 _public prototype_ `void StartProcessing();`
- L32 _public prototype_ `void PauseProcessing();`
- L34 _public prototype_ `void ProcessAllEvents();`
- L37 _private prototype_ `void OnARScanStarted();`
- L38 _private prototype_ `void OnARScanEnded();`
- L40 _private prototype_ `void OnAssetsAdded(TConstArrayView<FAssetData> InAssetsAdded);`
- L41 _private prototype_ `FTimespan ProcessAddedAssets(const FTimespan& AllowedTime);`
- L43 _private prototype_ `void OnAssetsRemoved(TConstArrayView<FAssetData> InAssetsRemoved);`
- L45 _private prototype_ `void OnAssetsUpdated(TConstArrayView<FAssetData> InAssetsUpdated);`
- L46 _private prototype_ `void OnAssetsUpdatedOnDisk(TConstArrayView<FAssetData> InAssetsUpdated);`
- L47 _private prototype_ `void OnAssetsUpdated_Impl(TConstArrayView<FAssetData> InAssetsUpdated);`
- L48 _private prototype_ `FTimespan ProcessUpdatedAssets(const FTimespan& AllowedTime);`
- L50 _private prototype_ `void OnAssetRenamed(const FAssetData& InAsset, const FString& InOldObjectPath);`
- L52 _private prototype_ `void OnPathsAdded(TConstArrayView<FStringView> InPathsAdded);`
- L53 _private prototype_ `FTimespan ProcessAddedPaths(const FTimespan& AllowedTIme);`
- L55 _private prototype_ `void OnPathsRemoved(TConstArrayView<FStringView> InPathsRemoved);`
- L57 _private prototype_ `void OnDatabaseUpdate();`
- L59 _private prototype_ `void UpdateAvgProcessedTime(double& OutAverageTime, uint64 LatestStartTime, uint64 LatestEndTime, int32 LastBatchSize);`
- L61 _private prototype_ `void ProcessTaskQueues(const FTimespan AllowedTime);`
- L63 _private prototype_ `void RecordAssetDataStats();`
- L65 _private member_ `bool bIsInitialized = false;`
- L66 _private member_ `bool bIsPaused = true;`
- L68 _private member_ `TArray<FName> AddedPaths;`
- L69 _private member_ `TArray<FAssetData> AddedAssets;`
- L70 _private member_ `TArray<FAssetData> UpdatedAssets;`
- L72 _private member_ `const FTimespan MaxAllowedTimePerTick = FTimespan::FromMilliseconds(6);`
- L73 _private member_ `const FTimespan DefaultMaxTimePerProcessCategory = MaxAllowedTimePerTick / 3;`
- L74 _private member_ `const uint32 DefaultNumberOfProcessedItems = 500;`
- L76 _private member_ `double AvgTimePerProcessedPathAdd = static_cast<double>((DefaultMaxTimePerProcessCategory / DefaultNumberOfProcessedItems).GetTicks());`
- L77 _private member_ `double AvgTimePerProcessedAssetAdd = static_cast<double>((DefaultMaxTimePerProcessCategory / DefaultNumberOfProcessedItems).GetTicks());`
- L78 _private member_ `double AvgTimePerProcessedAssetUpdate = static_cast<double>((DefaultMaxTimePerProcessCategory / DefaultNumberOfProcessedItems).GetTicks());`
- L80 _private member_ `const int32 MinimumBatchSize = 250;`
- L81 _private member_ `int32 LastAddedPathBatchSize = 0;`
- L82 _private member_ `int32 LastAddedAssetBatchSize = 0;`
- L83 _private member_ `int32 LastUpdatedAssetBatchSize = 0;`
- L85 _private member_ `static std::atomic<uint32> ProcessedAddedPathBatchSize;`
- L86 _private member_ `static std::atomic<uint32> ProcessedAddedAssetBatchSize;`
- L87 _private member_ `static std::atomic<uint32> ProcessedUpdatedAssetBatchSize;`
- L89 _private member_ `uint64 ProcessingStartTime = 0;`
- L91 _private member_ `static std::atomic<uint64> ProcessPathAddStartTime;`
- L92 _private member_ `static std::atomic<uint64> ProcessPathAddEndTime;`
- L94 _private member_ `static std::atomic<uint64> ProcessAssetAddStartTime;`
- L95 _private member_ `static std::atomic<uint64> ProcessAssetAddEndTime;`
- L97 _private member_ `static std::atomic<uint64> ProcessAssetUpdateStartTime;`
- L98 _private member_ `static std::atomic<uint64> ProcessAssetUpdateEndTime;`
- L100 _private member_ `UE::Editor::DataStorage::ICoreProvider& Database;`
- L101 _private member_ `DataStorage::TableHandle PathsTable = DataStorage::InvalidTableHandle;`
- L102 _private member_ `DataStorage::TableHandle AssetsDataTable = DataStorage::InvalidTableHandle;`
- L104 _private member_ `DataStorage::QueryHandle RemoveUpdatedPathTagQuery = DataStorage::InvalidQueryHandle;`
- L105 _private member_ `DataStorage::QueryHandle RemoveUpdatedAssetDataTagQuery = DataStorage::InvalidQueryHandle;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace Editor` (scope `UE`)
- L11 _namespace_ `namespace DataStorage` (scope `UE::Editor`)
- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace Editor` (scope `UE`)
- L16 _namespace_ `namespace AssetData` (scope `UE::Editor`)
- L16 _namespace_ `namespace Private` (scope `UE::Editor::AssetData`)

### `Plugins/Experimental/EditorDataStorageFeatures/Source/TedsAssetData/Private/TedsAssetDataModule.h` (Private)


#### class `UE::Editor::AssetData::FTedsAssetDataModule`  
`class FTedsAssetDataModule : public IModuleInterface`  
_L18-45_
- inherits: `IModuleInterface`
- L21 _public prototype_ `virtual void StartupModule() override;`
- L22 _public prototype_ `virtual void ShutdownModule() override;`
- L24 _public prototype_ `static FTedsAssetDataModule* Get();`
- L25 _public prototype_ `static FTedsAssetDataModule& GetChecked();`
- L26 _public prototype_ `void EnableTedsAssetRegistryStorage();`
- L27 _public prototype_ `void DisableTedsAssetRegistryStorage();`
- L28 _public prototype_ `bool IsTedsAssetRegistryStorageEnabled() const;`
- L29 _public prototype_ `void EnableAssetDataMetadataStorage();`
- L30 _public prototype_ `void DisableAssetDataMetadataStorage();`
- L31 _public prototype_ `FSimpleMulticastDelegate& OnAssetRegistryStorageInit();`
- L37 _public prototype_ `void ProcessDependentEvents();` — Process now any pending event that might make the Teds database out of sync with the asset registry. Note: This isn't needed when using the editor so it should be only called by the automation scripts that need it to avoid creating some unneeded stalls.
- L40 _private prototype_ `void InitAssetRegistryStorage();`
- L42 _private member_ `TUniquePtr<Private::FTedsAssetDataCBDataSource> AssetDataCBDataSource;`
- L43 _private member_ `TUniquePtr<Private::FTedsAssetData> AssetRegistryStorage;`
- L44 _private member_ `FSimpleMulticastDelegate OnAssetRegistryStorageInitDelegate;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace Editor` (scope `UE`)
- L9 _namespace_ `namespace AssetData` (scope `UE::Editor`)
- L12 _namespace_ `namespace Private` (scope `UE::Editor::AssetData`)

### `Plugins/Experimental/EditorDataStorageFeatures/Source/TedsAssetData/Private/Widgets/AssetDataDiskSizeWidget.h` (Private)


#### class `UDiskSizeWidgetFactory`  
`class UDiskSizeWidgetFactory : public UEditorDataStorageFactory`  
_L13-22_
- reflection: `UCLASS()`
- inherits: `UEditorDataStorageFactory`
- L18 _public prototype_ `~UDiskSizeWidgetFactory() override = default;`
- L20 _public prototype_ `void RegisterWidgetConstructors(UE::Editor::DataStorage::ICoreProvider& DataStorage, UE::Editor::DataStorage::IUiProvider& DataStorageUi) const override;`

#### struct `FDiskSizeWidgetConstructor`  
`struct FDiskSizeWidgetConstructor : public FSimpleWidgetConstructor`  
_L26-40_
- reflection: `USTRUCT()`
- inherits: `FSimpleWidgetConstructor`
- desc: Widget to show disk size in bytes
- L31 _public prototype_ `FDiskSizeWidgetConstructor();`
- L32 _public prototype_ `~FDiskSizeWidgetConstructor() override = default;`
- L34 _public prototype_ `virtual TSharedPtr<SWidget> CreateWidget( UE::Editor::DataStorage::ICoreProvider* DataStorage, UE::Editor::DataStorage::IUiProvider* DataStorageUi, UE::Editor::DataStorage::RowHandle TargetRow, UE::Editor::DataStorage::RowHandle WidgetRow, const UE::Editor::DataStorage::FMetaDataView& Arguments) override;`

### `Plugins/Experimental/EditorDataStorageFeatures/Source/TedsAssetData/Private/Widgets/AssetDataItemTypeWidget.h` (Private)


#### class `UAssetDataItemTypeWidgetFactory`  
`class UAssetDataItemTypeWidgetFactory : public UEditorDataStorageFactory`  
_L11-20_
- reflection: `UCLASS()`
- inherits: `UEditorDataStorageFactory`
- L16 _public prototype_ `~UAssetDataItemTypeWidgetFactory() override = default;`
- L18 _public prototype_ `void RegisterWidgetConstructors(UE::Editor::DataStorage::ICoreProvider& DataStorage, UE::Editor::DataStorage::IUiProvider& DataStorageUi) const override;`

#### struct `FAssetDataItemTypeWidgetConstructor`  
`struct FAssetDataItemTypeWidgetConstructor : public FSimpleWidgetConstructor`  
_L24-38_
- reflection: `USTRUCT()`
- inherits: `FSimpleWidgetConstructor`
- desc: Widget to show Item type (folder/material/mesh etc...)
- L29 _public prototype_ `FAssetDataItemTypeWidgetConstructor();`
- L30 _public prototype_ `~FAssetDataItemTypeWidgetConstructor() override = default;`
- L32 _public prototype_ `virtual TSharedPtr<SWidget> CreateWidget( UE::Editor::DataStorage::ICoreProvider* DataStorage, UE::Editor::DataStorage::IUiProvider* DataStorageUi, UE::Editor::DataStorage::RowHandle TargetRow, UE::Editor::DataStorage::RowHandle WidgetRow, const UE::Editor::DataStorage::FMetaDataView& Arguments) override;`

### `Plugins/Experimental/EditorDataStorageFeatures/Source/TedsAssetData/Private/Widgets/AssetDataThumbnailWidget.h` (Private)


#### class `UAssetThumbnailWidgetFactory`  
`class UAssetThumbnailWidgetFactory : public UEditorDataStorageFactory`  
_L15-25_
- reflection: `UCLASS()`
- inherits: `UEditorDataStorageFactory`
- L20 _public prototype_ `virtual ~UAssetThumbnailWidgetFactory() override = default;`
- L22 _public prototype_ `virtual void RegisterWidgetPurposes(UE::Editor::DataStorage::IUiProvider& DataStorageUi) const override;`
- L23 _public prototype_ `virtual void RegisterWidgetConstructors(UE::Editor::DataStorage::ICoreProvider& DataStorage, UE::Editor::DataStorage::IUiProvider& DataStorageUi) const override;`

#### struct `FAssetThumbnailWidgetConstructor`  
`struct FAssetThumbnailWidgetConstructor : public FSimpleWidgetConstructor`  
_L29-44_
- reflection: `USTRUCT()`
- inherits: `FSimpleWidgetConstructor`
- desc: Thumbnail widget for assets in TEDS
- L34 _public prototype_ `FAssetThumbnailWidgetConstructor();`
- L35 _public prototype_ `explicit FAssetThumbnailWidgetConstructor(const UScriptStruct* TypeInfo);`
- L36 _public prototype_ `virtual ~FAssetThumbnailWidgetConstructor() override = default;`
- L38 _public prototype_ `virtual TSharedPtr<SWidget> CreateWidget( UE::Editor::DataStorage::ICoreProvider* DataStorage, UE::Editor::DataStorage::IUiProvider* DataStorageUi, UE::Editor::DataStorage::RowHandle TargetRow, UE::Editor::DataStorage::RowHandle WidgetRow, const UE::Editor::DataStorage::FMetaDataView& Arguments) override;`

### `Plugins/Experimental/EditorDataStorageFeatures/Source/TedsAssetData/Private/Widgets/AssetDataVirtualPathWidget.h` (Private)


#### class `UE::Editor::DataStorage::FAssetDataVirtualPathWidgetSorter`  
`class FAssetDataVirtualPathWidgetSorter final : public FColumnSorterInterface`  
_L12-22_
- inherits: `FColumnSorterInterface`
- L15 _public prototype_ `virtual int32 Compare(const ICoreProvider& Storage, RowHandle Left, RowHandle Right) const override;`
- L16 _public prototype_ `virtual FPrefixInfo CalculatePrefix(const ICoreProvider& Storage, RowHandle Row, uint32 ByteIndex) const override;`
- L17 _public prototype_ `virtual ESortType GetSortType() const override;`
- L18 _public prototype_ `virtual FText GetShortName() const override;`
- L21 _private prototype_ `bool ExtractString(FString& Result, const ICoreProvider& Storage, RowHandle Row) const;`

#### class `UAssetDataVirtualPathWidgetFactory`  
`class UAssetDataVirtualPathWidgetFactory : public UEditorDataStorageFactory`  
_L26-35_
- reflection: `UCLASS()`
- inherits: `UEditorDataStorageFactory`
- L31 _public prototype_ `~UAssetDataVirtualPathWidgetFactory() override = default;`
- L33 _public prototype_ `void RegisterWidgetConstructors(UE::Editor::DataStorage::ICoreProvider& DataStorage, UE::Editor::DataStorage::IUiProvider& DataStorageUi) const override;`

#### struct `FAssetDataVirtualPathWidgetConstructor`  
`struct FAssetDataVirtualPathWidgetConstructor : public FSimpleWidgetConstructor`  
_L39-58_
- reflection: `USTRUCT()`
- inherits: `FSimpleWidgetConstructor`
- desc: Widget to show disk size in bytes
- L44 _public prototype_ `FAssetDataVirtualPathWidgetConstructor();`
- L45 _public prototype_ `~FAssetDataVirtualPathWidgetConstructor() override = default;`
- L47 _public prototype_ `virtual TSharedPtr<SWidget> CreateWidget( UE::Editor::DataStorage::ICoreProvider* DataStorage, UE::Editor::DataStorage::IUiProvider* DataStorageUi, UE::Editor::DataStorage::RowHandle TargetRow, UE::Editor::DataStorage::RowHandle WidgetRow, const UE::Editor::DataStorage::FMetaDataView& Arguments) override;`
- L54 _public prototype_ `virtual TArray<TSharedPtr<const UE::Editor::DataStorage::FColumnSorterInterface>> ConstructColumnSorters( UE::Editor::DataStorage::ICoreProvider* DataStorage, UE::Editor::DataStorage::IUiProvider* DataStorageUi, const UE::Editor::DataStorage::FMetaDataView& Arguments) override;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace Editor` (scope `UE`)
- L10 _namespace_ `namespace DataStorage` (scope `UE::Editor`)

### `Plugins/Experimental/EditorDataStorageFeatures/Source/TedsAssetData/Private/Widgets/AssetLabelWidget.h` (Private)


#### class `UAssetLabelWidgetFactory`  
`class UAssetLabelWidgetFactory : public UEditorDataStorageFactory`  
_L15-24_
- reflection: `UCLASS()`
- inherits: `UEditorDataStorageFactory`
- L20 _public prototype_ `virtual ~UAssetLabelWidgetFactory() override = default;`
- L22 _public prototype_ `virtual void RegisterWidgetConstructors(UE::Editor::DataStorage::ICoreProvider& DataStorage, UE::Editor::DataStorage::IUiProvider& DataStorageUi) const override;`

#### struct `FAssetLabelWidgetConstructor`  
`struct FAssetLabelWidgetConstructor : public FSimpleWidgetConstructor`  
_L28-43_
- reflection: `USTRUCT()`
- inherits: `FSimpleWidgetConstructor`
- desc: Label for assets in TEDS
- L33 _public prototype_ `FAssetLabelWidgetConstructor();`
- L34 _public prototype_ `explicit FAssetLabelWidgetConstructor(const UScriptStruct* TypeInfo);`
- L35 _public prototype_ `virtual ~FAssetLabelWidgetConstructor() override = default;`
- L37 _public prototype_ `virtual TSharedPtr<SWidget> CreateWidget( UE::Editor::DataStorage::ICoreProvider* DataStorage, UE::Editor::DataStorage::IUiProvider* DataStorageUi, UE::Editor::DataStorage::RowHandle TargetRow, UE::Editor::DataStorage::RowHandle WidgetRow, const UE::Editor::DataStorage::FMetaDataView& Arguments) override;`

### `Plugins/Experimental/EditorDataStorageFeatures/Source/TedsAssetData/Private/Widgets/AssetPreview/AssetPreviewGeneralWidgetRegistrationFactory.h` (Private)


#### class `UAssetPreviewGeneralWidgetRegistrationFactory`  
`class UAssetPreviewGeneralWidgetRegistrationFactory : public UEditorDataStorageFactory`  
_L11-19_
- reflection: `UCLASS()`
- inherits: `UEditorDataStorageFactory`
- L16 _public prototype_ `~UAssetPreviewGeneralWidgetRegistrationFactory() override = default;`
- L18 _public prototype_ `void RegisterWidgetPurposes(UE::Editor::DataStorage::IUiProvider& DataStorageUi) const override;`

### `Plugins/Experimental/EditorDataStorageFeatures/Source/TedsAssetData/Private/Widgets/AssetPreview/Widgets/AdvancedInfo/AssetPreviewAdvancedInfoWidget.h` (Private)


#### class `UAssetPreviewAdvancedInfoWidgetFactory`  
`class UAssetPreviewAdvancedInfoWidgetFactory : public UEditorDataStorageFactory`  
_L15-24_
- reflection: `UCLASS()`
- inherits: `UEditorDataStorageFactory`
- L20 _public prototype_ `virtual ~UAssetPreviewAdvancedInfoWidgetFactory() override = default;`
- L22 _public prototype_ `virtual void RegisterWidgetConstructors(UE::Editor::DataStorage::ICoreProvider& DataStorage, UE::Editor::DataStorage::IUiProvider& DataStorageUi) const override;`

#### struct `FAssetPreviewAdvancedInfoWidgetConstructor`  
`struct FAssetPreviewAdvancedInfoWidgetConstructor : public FSimpleWidgetConstructor`  
_L28-42_
- reflection: `USTRUCT()`
- inherits: `FSimpleWidgetConstructor`
- desc: Widget for the AssetPreview Advanced Info
- L33 _public prototype_ `FAssetPreviewAdvancedInfoWidgetConstructor();`
- L34 _public prototype_ `virtual ~FAssetPreviewAdvancedInfoWidgetConstructor() override = default;`
- L36 _public prototype_ `virtual TSharedPtr<SWidget> CreateWidget( UE::Editor::DataStorage::ICoreProvider* DataStorage, UE::Editor::DataStorage::IUiProvider* DataStorageUi, UE::Editor::DataStorage::RowHandle TargetRow, UE::Editor::DataStorage::RowHandle WidgetRow, const UE::Editor::DataStorage::FMetaDataView& Arguments) override;`

### `Plugins/Experimental/EditorDataStorageFeatures/Source/TedsAssetData/Private/Widgets/AssetPreview/Widgets/BaseInfo/AssetPreviewBaseInfoWidget.h` (Private)


#### class `UAssetPreviewBaseInfoWidgetFactory`  
`class UAssetPreviewBaseInfoWidgetFactory : public UEditorDataStorageFactory`  
_L13-22_
- reflection: `UCLASS()`
- inherits: `UEditorDataStorageFactory`
- L18 _public prototype_ `virtual ~UAssetPreviewBaseInfoWidgetFactory() override = default;`
- L20 _public prototype_ `virtual void RegisterWidgetConstructors(UE::Editor::DataStorage::ICoreProvider& DataStorage, UE::Editor::DataStorage::IUiProvider& DataStorageUi) const override;`

#### struct `FAssetPreviewBaseInfoWidgetConstructor`  
`struct FAssetPreviewBaseInfoWidgetConstructor : public FSimpleWidgetConstructor`  
_L26-43_
- reflection: `USTRUCT()`
- inherits: `FSimpleWidgetConstructor`
- desc: Widget for the AssetPreview Basic Info
- L31 _public prototype_ `FAssetPreviewBaseInfoWidgetConstructor();`
- L32 _public prototype_ `virtual ~FAssetPreviewBaseInfoWidgetConstructor() override = default;`
- L34 _public prototype_ `virtual TSharedPtr<SWidget> CreateWidget( UE::Editor::DataStorage::ICoreProvider* DataStorage, UE::Editor::DataStorage::IUiProvider* DataStorageUi, UE::Editor::DataStorage::RowHandle TargetRow, UE::Editor::DataStorage::RowHandle WidgetRow, const UE::Editor::DataStorage::FMetaDataView& Arguments) override;`
- L42 _private prototype_ `TArray<TWeakObjectPtr<const UScriptStruct>> GetLabelColumns();`

### `Plugins/Experimental/EditorDataStorageFeatures/Source/TedsAssetData/Private/Widgets/AssetPreview/Widgets/Header/AssetPreviewHeaderWidget.h` (Private)


#### class `UAssetPreviewHeaderWidgetFactory`  
`class UAssetPreviewHeaderWidgetFactory : public UEditorDataStorageFactory`  
_L14-24_
- reflection: `UCLASS()`
- inherits: `UEditorDataStorageFactory`
- L19 _public prototype_ `virtual ~UAssetPreviewHeaderWidgetFactory() override = default;`
- L21 _public prototype_ `virtual void RegisterWidgetPurposes(UE::Editor::DataStorage::IUiProvider& DataStorageUi) const override;`
- L22 _public prototype_ `virtual void RegisterWidgetConstructors(UE::Editor::DataStorage::ICoreProvider& DataStorage, UE::Editor::DataStorage::IUiProvider& DataStorageUi) const override;`

#### struct `FAssetPreviewHeaderWidgetConstructor`  
`struct FAssetPreviewHeaderWidgetConstructor : public FSimpleWidgetConstructor`  
_L28-48_
- reflection: `USTRUCT()`
- inherits: `FSimpleWidgetConstructor`
- desc: Widget for the AssetPreview Header
- L33 _public prototype_ `FAssetPreviewHeaderWidgetConstructor();`
- L34 _public prototype_ `virtual ~FAssetPreviewHeaderWidgetConstructor() override = default;`
- L36 _public prototype_ `virtual TSharedPtr<SWidget> CreateWidget( UE::Editor::DataStorage::ICoreProvider* DataStorage, UE::Editor::DataStorage::IUiProvider* DataStorageUi, UE::Editor::DataStorage::RowHandle TargetRow, UE::Editor::DataStorage::RowHandle WidgetRow, const UE::Editor::DataStorage::FMetaDataView& Arguments) override;`
- L43 _public prototype_ `virtual TConstArrayView<const UScriptStruct*> GetAdditionalColumnsList() const override;`
- L46 _private prototype_ `TArray<TWeakObjectPtr<const UScriptStruct>> GetEditModeColumns();`
- L47 _private prototype_ `TArray<TWeakObjectPtr<const UScriptStruct>> GetItemContextMenuColumns();`

### `Plugins/Experimental/EditorDataStorageFeatures/Source/TedsAssetData/Private/Widgets/AssetPreview/Widgets/Header/EditModeToggleHeaderWidget.h` (Private)


#### class `UEditModeToggleHeaderWidgetFactory`  
`class UEditModeToggleHeaderWidgetFactory : public UEditorDataStorageFactory`  
_L14-24_
- reflection: `UCLASS()`
- inherits: `UEditorDataStorageFactory`
- L19 _public prototype_ `virtual ~UEditModeToggleHeaderWidgetFactory() override = default;`
- L21 _public prototype_ `virtual void RegisterWidgetPurposes(UE::Editor::DataStorage::IUiProvider& DataStorageUi) const override;`
- L22 _public prototype_ `virtual void RegisterWidgetConstructors(UE::Editor::DataStorage::ICoreProvider& DataStorage, UE::Editor::DataStorage::IUiProvider& DataStorageUi) const override;`

#### struct `FEditModeToggleHeaderWidgetConstructor`  
`struct FEditModeToggleHeaderWidgetConstructor : public FSimpleWidgetConstructor`  
_L28-44_
- reflection: `USTRUCT()`
- inherits: `FSimpleWidgetConstructor`
- desc: Widget that display the Edit button for the AssetPreview panel
- L33 _public prototype_ `FEditModeToggleHeaderWidgetConstructor();`
- L34 _public prototype_ `virtual ~FEditModeToggleHeaderWidgetConstructor() override = default;`
- L36 _public prototype_ `virtual TSharedPtr<SWidget> CreateWidget( UE::Editor::DataStorage::ICoreProvider* DataStorage, UE::Editor::DataStorage::IUiProvider* DataStorageUi, UE::Editor::DataStorage::RowHandle TargetRow, UE::Editor::DataStorage::RowHandle WidgetRow, const UE::Editor::DataStorage::FMetaDataView& Arguments) override;`
- L43 _public prototype_ `virtual TConstArrayView<const UScriptStruct*> GetAdditionalColumnsList() const override;`

### `Plugins/Experimental/EditorDataStorageFeatures/Source/TedsAssetData/Private/Widgets/AssetPreview/Widgets/Header/ItemContextMenuWidget.h` (Private)


#### class `UItemContextMenuWidgetFactory`  
`class UItemContextMenuWidgetFactory : public UEditorDataStorageFactory`  
_L14-24_
- reflection: `UCLASS()`
- inherits: `UEditorDataStorageFactory`
- L19 _public prototype_ `virtual ~UItemContextMenuWidgetFactory() override = default;`
- L21 _public prototype_ `virtual void RegisterWidgetPurposes(UE::Editor::DataStorage::IUiProvider& DataStorageUi) const override;`
- L22 _public prototype_ `virtual void RegisterWidgetConstructors(UE::Editor::DataStorage::ICoreProvider& DataStorage, UE::Editor::DataStorage::IUiProvider& DataStorageUi) const override;`

#### struct `FItemContextMenuWidgetConstructor`  
`struct FItemContextMenuWidgetConstructor : public FSimpleWidgetConstructor`  
_L28-44_
- reflection: `USTRUCT()`
- inherits: `FSimpleWidgetConstructor`
- desc: Widget that display the ContextMenu button for the AssetPreview panel
- L33 _public prototype_ `FItemContextMenuWidgetConstructor();`
- L34 _public prototype_ `virtual ~FItemContextMenuWidgetConstructor() override = default;`
- L36 _public prototype_ `virtual TSharedPtr<SWidget> CreateWidget( UE::Editor::DataStorage::ICoreProvider* DataStorage, UE::Editor::DataStorage::IUiProvider* DataStorageUi, UE::Editor::DataStorage::RowHandle TargetRow, UE::Editor::DataStorage::RowHandle WidgetRow, const UE::Editor::DataStorage::FMetaDataView& Arguments) override;`
- L43 _public prototype_ `virtual TConstArrayView<const UScriptStruct*> GetAdditionalColumnsList() const override;`

### `Plugins/Experimental/EditorDataStorageFeatures/Source/TedsAssetData/Private/Widgets/AssetPreview/Widgets/Thumbnail/AssetPreviewThumbnailWidget.h` (Private)


#### class `UAssetPreviewThumbnailWidgetFactory`  
`class UAssetPreviewThumbnailWidgetFactory : public UEditorDataStorageFactory`  
_L15-25_
- reflection: `UCLASS()`
- inherits: `UEditorDataStorageFactory`
- L20 _public prototype_ `virtual ~UAssetPreviewThumbnailWidgetFactory() override = default;`
- L22 _public prototype_ `virtual void RegisterWidgetPurposes(UE::Editor::DataStorage::IUiProvider& DataStorageUi) const override;`
- L23 _public prototype_ `virtual void RegisterWidgetConstructors(UE::Editor::DataStorage::ICoreProvider& DataStorage, UE::Editor::DataStorage::IUiProvider& DataStorageUi) const override;`

#### struct `FAssetPreviewThumbnailWidgetConstructor`  
`struct FAssetPreviewThumbnailWidgetConstructor : public FSimpleWidgetConstructor`  
_L29-49_
- reflection: `USTRUCT()`
- inherits: `FSimpleWidgetConstructor`
- desc: Thumbnail widget for the asset preview
- L34 _public prototype_ `FAssetPreviewThumbnailWidgetConstructor();`
- L35 _public prototype_ `virtual ~FAssetPreviewThumbnailWidgetConstructor() override = default;`
- L37 _public prototype_ `virtual TSharedPtr<SWidget> CreateWidget( UE::Editor::DataStorage::ICoreProvider* DataStorage, UE::Editor::DataStorage::IUiProvider* DataStorageUi, UE::Editor::DataStorage::RowHandle TargetRow, UE::Editor::DataStorage::RowHandle WidgetRow, const UE::Editor::DataStorage::FMetaDataView& Arguments) override;`
- L44 _public prototype_ `virtual TConstArrayView<const UScriptStruct*> GetAdditionalColumnsList() const override;`
- L48 _private prototype_ `TArray<TWeakObjectPtr<const UScriptStruct>> GetThumbnailColumns();` — Get the columns used for the Thumbnail TEDS widget

### `Plugins/Experimental/EditorDataStorageFeatures/Source/TedsAssetData/Private/Widgets/ContentBrowserListViewNameWidget.h` (Private)


#### class `UContentBrowserListViewNameWidgetFactory`  
`class UContentBrowserListViewNameWidgetFactory : public UEditorDataStorageFactory`  
_L19-32_
- reflection: `UCLASS()`
- inherits: `UEditorDataStorageFactory`
- L24 _public member_ `static UE::Editor::DataStorage::IUiProvider::FPurposeID WidgetPurpose;`
- L26 _public prototype_ `~UContentBrowserListViewNameWidgetFactory() override = default;`
- L28 _public prototype_ `virtual void RegisterWidgetPurposes(UE::Editor::DataStorage::IUiProvider& DataStorageUi) const override;`
- L30 _public prototype_ `void RegisterWidgetConstructors(UE::Editor::DataStorage::ICoreProvider& DataStorage, UE::Editor::DataStorage::IUiProvider& DataStorageUi) const override;`

#### struct `FContentBrowserListViewNameWidgetConstructor`  
`struct FContentBrowserListViewNameWidgetConstructor : public FSimpleWidgetConstructor`  
_L36-54_
- reflection: `USTRUCT()`
- inherits: `FSimpleWidgetConstructor`
- desc: Content Browser Label + Thumbnail widget
- L41 _public prototype_ `FContentBrowserListViewNameWidgetConstructor();`
- L42 _public prototype_ `explicit FContentBrowserListViewNameWidgetConstructor(const UScriptStruct* TypeInfo);`
- L43 _public prototype_ `~FContentBrowserListViewNameWidgetConstructor() override = default;`
- L45 _public prototype_ `virtual TSharedPtr<SWidget> CreateWidget( UE::Editor::DataStorage::ICoreProvider* DataStorage, UE::Editor::DataStorage::IUiProvider* DataStorageUi, UE::Editor::DataStorage::RowHandle TargetRow, UE::Editor::DataStorage::RowHandle WidgetRow, const UE::Editor::DataStorage::FMetaDataView& Arguments) override;`
- L53 _private prototype_ `TArray<TWeakObjectPtr<const UScriptStruct>> GetLabelColumns();`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace Editor` (scope `UE`)
- L12 _namespace_ `namespace DataStorage` (scope `UE::Editor`)

### `Plugins/Experimental/EditorDataStorageFeatures/Source/TedsAssetData/Private/Widgets/DynamicAssetDataColumnBaseWidget.h` (Private)


#### class `UDynamicAssetDataColumnBaseWidgetFactory`  
`class UDynamicAssetDataColumnBaseWidgetFactory : public UEditorDataStorageFactory`  
_L11-20_
- reflection: `UCLASS()`
- inherits: `UEditorDataStorageFactory`
- L16 _public prototype_ `~UDynamicAssetDataColumnBaseWidgetFactory() override = default;`
- L18 _public prototype_ `void RegisterWidgetConstructors(UE::Editor::DataStorage::ICoreProvider& DataStorage, UE::Editor::DataStorage::IUiProvider& DataStorageUi) const override;`

#### struct `FDynamicAssetDataColumnBaseWidgetConstructor`  
`struct FDynamicAssetDataColumnBaseWidgetConstructor : public FSimpleWidgetConstructor`  
_L23-37_
- reflection: `USTRUCT()`
- inherits: `FSimpleWidgetConstructor`
- L28 _public prototype_ `FDynamicAssetDataColumnBaseWidgetConstructor();`
- L29 _public prototype_ `~FDynamicAssetDataColumnBaseWidgetConstructor() override = default;`
- L31 _public prototype_ `virtual TSharedPtr<SWidget> CreateWidget( UE::Editor::DataStorage::ICoreProvider* DataStorage, UE::Editor::DataStorage::IUiProvider* DataStorageUi, UE::Editor::DataStorage::RowHandle TargetRow, UE::Editor::DataStorage::RowHandle WidgetRow, const UE::Editor::DataStorage::FMetaDataView& Arguments) override;`

### `Plugins/Experimental/EditorDataStorageFeatures/Source/TedsAssetData/Private/Widgets/SHyperlinkAssetPreviewWidget.h` (Private)


#### class `SHyperlinkAssetPreviewWidget`  
`class SHyperlinkAssetPreviewWidget : public SHyperlink`  
_L14-51_
- inherits: `SHyperlink`
- desc: Widget to display a Hyperlink with a Preview of the asset
- L17 _public function_ `SLATE_BEGIN_ARGS(SHyperlinkAssetPreviewWidget)`
- L20 _public prototype_ `SLATE_ATTRIBUTE(FAssetData, AssetData) SLATE_EVENT(FOnNavigateAsset, OnNavigateAsset) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L30 _public prototype_ `TSharedRef<SWidget> GetThumbnailWidget() const;` — Get the preview tooltip for the hyperlink text
- L34 _private prototype_ `void OnNavigate_Internal() const;` — Called when trying to navigate to the asset
- L37 _private prototype_ `EVisibility GetHyperlinkVisibility() const;` — Visible if the AssetData is valid, Collapsed otherwise
- L40 _private prototype_ `FText GetAssetDisplayName() const;` — Retrieve the asset name to use
- L44 _private member_ `TAttribute<FAssetData> AssetDataAttribute;` — AssetData to link
- L47 _private member_ `TSharedPtr<FAssetThumbnail> AssetThumbnailTooltip;` — AssetThumbnail used for the tooltip
- L50 _private member_ `FOnNavigateAsset OnNavigateAssetDelegate;` — Callback when trying to navigate to an asset

#### Free symbols / members of external scopes

- L11 _delegate_ `DECLARE_DELEGATE_OneParam(FOnNavigateAsset, const FAssetData&) class SHyperlinkAssetPreviewWidget : public SHyperlink { public: SLATE_BEGIN_ARGS(SHyperlinkAssetPreviewWidget) {} SLATE_ATTRIBUTE(FAssetData, AssetData) SLATE_EVENT(FOnNavigateAsset, OnNavigateAsset) SLATE_END_ARGS() void Construct(const FArguments& InArgs); TSharedRef<SWidget> GetThumbnailWidget() const; private: void OnNavigate_Internal() const; EVisibility GetHyperlinkVisibility() const; FText GetAssetDisplayName() const; private: TAttribute<FAssetData> AssetDataAttribute; TSharedPtr<FAssetThumbnail> AssetThumbnailTooltip; FOnNavigateAsset OnNavigateAssetDelegate;`

### `Plugins/Experimental/EditorDataStorageFeatures/Source/TedsAssetData/Private/Widgets/StaticMeshTrianglesWidget.h` (Private)


#### class `UStaticMeshTrianglesWidgetFactory`  
`class UStaticMeshTrianglesWidgetFactory : public UEditorDataStorageFactory`  
_L11-20_
- reflection: `UCLASS()`
- inherits: `UEditorDataStorageFactory`
- L16 _public prototype_ `~UStaticMeshTrianglesWidgetFactory() override = default;`
- L18 _public prototype_ `void RegisterWidgetConstructors(UE::Editor::DataStorage::ICoreProvider& DataStorage, UE::Editor::DataStorage::IUiProvider& DataStorageUi) const override;`

#### struct `FStaticMeshTrianglesWidgetConstructor`  
`struct FStaticMeshTrianglesWidgetConstructor : public FSimpleWidgetConstructor`  
_L24-38_
- reflection: `USTRUCT()`
- inherits: `FSimpleWidgetConstructor`
- desc: Specialized widget to display the "Triangles" metadata on static mesh assets
- L29 _public prototype_ `FStaticMeshTrianglesWidgetConstructor();`
- L30 _public prototype_ `~FStaticMeshTrianglesWidgetConstructor() override = default;`
- L32 _public prototype_ `virtual TSharedPtr<SWidget> CreateWidget( UE::Editor::DataStorage::ICoreProvider* DataStorage, UE::Editor::DataStorage::IUiProvider* DataStorageUi, UE::Editor::DataStorage::RowHandle TargetRow, UE::Editor::DataStorage::RowHandle WidgetRow, const UE::Editor::DataStorage::FMetaDataView& Arguments) override;`

### `Plugins/Experimental/EditorDataStorageFeatures/Source/TedsAssetData/Public/TedsAssetDataColumns.h` (Public)


#### struct `FAssetPathColumn_Experimental`  
`struct FAssetPathColumn_Experimental : public FEditorDataStorageColumn`  
_L26-32_
- reflection: `USTRUCT()`
- inherits: `FEditorDataStorageColumn`
- L31 _public member_ `FName Path;` — `UPROPERTY(meta = (Searchable, Sortable))`

#### struct `FFolderTypeColumn_Experimental`  
`struct FFolderTypeColumn_Experimental : public FEditorDataStorageColumn`  
_L35-40_
- reflection: `USTRUCT()`
- inherits: `FEditorDataStorageColumn`
- L39 _public member_ `EFolderType FolderType;`

#### struct `FAssetDataColumn_Experimental`  
`struct FAssetDataColumn_Experimental : public FEditorDataStorageColumn`  
_L43-49_
- reflection: `USTRUCT()`
- inherits: `FEditorDataStorageColumn`
- L48 _public member_ `FAssetData AssetData;` — `UPROPERTY()`

#### struct `FAssetTag`  
`struct FAssetTag final : public FEditorDataStorageTag`  
_L53-56_
- reflection: `USTRUCT(meta = (DisplayName = "Asset"))`
- inherits: `FEditorDataStorageTag`
- desc: Tag to identify assets

#### struct `FPrivateAssetTag`  
`struct FPrivateAssetTag final : public FEditorDataStorageTag`  
_L60-63_
- reflection: `USTRUCT(meta = (DisplayName = "Private Asset"))`
- inherits: `FEditorDataStorageTag`
- desc: Tag to identify assets with private visibility

#### struct `FEpicInternalAssetTag`  
`struct FEpicInternalAssetTag final : public FEditorDataStorageTag`  
_L67-70_
- reflection: `USTRUCT(meta = (DisplayName = "Epic Internal Asset"))`
- inherits: `FEditorDataStorageTag`
- desc: Tag to identify assets with epic internal visibility

#### struct `FPublicAssetTag`  
`struct FPublicAssetTag final : public FEditorDataStorageTag`  
_L74-77_
- reflection: `USTRUCT(meta = (DisplayName = "Public Asset"))`
- inherits: `FEditorDataStorageTag`
- desc: Tag to identify assets with public visibility

#### struct `FAssetNameColumn`  
`struct FAssetNameColumn final : public FEditorDataStorageColumn`  
_L81-88_
- reflection: `USTRUCT(meta = (DisplayName = "Name"))`
- inherits: `FEditorDataStorageColumn`
- desc: Column to store the name of an asset
- L87 _public member_ `FName Name;` — `UPROPERTY(meta = (Searchable, Sortable))` — The name of the asset

#### struct `FAssetClassColumn`  
`struct FAssetClassColumn final : public FEditorDataStorageColumn`  
_L92-99_
- reflection: `USTRUCT(meta = (DisplayName = "Type"))`
- inherits: `FEditorDataStorageColumn`
- desc: Column to store the type of an asset
- L98 _public member_ `FTopLevelAssetPath ClassPath;` — `UPROPERTY()` — The path of the type

#### struct `FDiskSizeColumn`  
`struct FDiskSizeColumn final : public FEditorDataStorageColumn`  
_L103-110_
- reflection: `USTRUCT(meta = (DisplayName = "Disk Size"))`
- inherits: `FEditorDataStorageColumn`
- desc: Column to store the disk size of an asset
- L109 _public member_ `int64 DiskSize = 0;` — `UPROPERTY(meta = (Sortable))` — Size on disk (in bytes)

#### struct `FVersePathColumn`  
`struct FVersePathColumn final : public FEditorDataStorageColumn`  
_L115-120_
- reflection: `USTRUCT(meta = (DisplayName = "Verse Path"))`
- inherits: `FEditorDataStorageColumn`
- desc: Column to store the verse path of an asset
- L119 _public member_ `UE::Core::FVersePath VersePath;`

#### struct `FUpdatedPathTag`  
`struct FUpdatedPathTag : public FEditorDataStorageTag`  
_L124-127_
- reflection: `USTRUCT()`
- inherits: `FEditorDataStorageTag`
- desc: Used to notify the dependent queries of the update to the path of the row

#### struct `FUpdatedAssetDataTag`  
`struct FUpdatedAssetDataTag : public FEditorDataStorageTag`  
_L131-134_
- reflection: `USTRUCT()`
- inherits: `FEditorDataStorageTag`
- desc: Used to notify the dependent queries of a update to the asset data

#### struct `FVirtualPathColumn_Experimental`  
`struct FVirtualPathColumn_Experimental : public FEditorDataStorageColumn`  
_L137-143_
- reflection: `USTRUCT(meta = (DisplayName = "CB Item Path"))`
- inherits: `FEditorDataStorageColumn`
- L142 _public member_ `FName VirtualPath;` — `UPROPERTY(meta = (Searchable, Sortable))`

#### struct `FItemAttributeBaseColumn_Experimental`  
`struct FItemAttributeBaseColumn_Experimental : public FEditorDataStorageColumn`  
_L146-151_
- reflection: `USTRUCT()`
- inherits: `FEditorDataStorageColumn`
- L150 _public member_ `TSharedPtr<const UE::Editor::AssetData::FItemAttributeMetadata> AttributeMetadata;`

#### struct `FItemTextAttributeColumn_Experimental`  
`struct FItemTextAttributeColumn_Experimental : public FItemAttributeBaseColumn_Experimental`  
_L154-160_
- reflection: `USTRUCT()`
- inherits: `FItemAttributeBaseColumn_Experimental`
- L159 _public member_ `FText Value;` — `UPROPERTY(meta = (Searchable, Sortable))`

#### struct `FItemStringAttributeColumn_Experimental`  
`struct FItemStringAttributeColumn_Experimental : public FItemAttributeBaseColumn_Experimental`  
_L163-169_
- reflection: `USTRUCT(meta=(EditorDataStorage_DynamicColumnTemplate))`
- inherits: `FItemAttributeBaseColumn_Experimental`
- L168 _public member_ `FString Value;` — `UPROPERTY(meta = (Searchable, Sortable))`

#### Free symbols / members of external scopes

- L20 _namespace_ `namespace UE`
- L20 _namespace_ `namespace Editor` (scope `UE`)
- L20 _namespace_ `namespace AssetData` (scope `UE::Editor`)
- L22 _variable_ `inline static const FName MappingDomain = "As` (scope `UE::Editor::AssetData`)

### `Plugins/Experimental/EditorDataStorageFeatures/Source/TedsAssetData/Public/TedsAssetDataHelper.h` (Public)


#### Free symbols / members of external scopes

- L8 _namespace_ `namespace TedsAssetDataHelper`
- L10 _namespace_ `namespace MetaDataNames` (scope `TedsAssetDataHelper`)
- L12 _prototype_ `FName GetThumbnailStatusMetaDataName();` (scope `TedsAssetDataHelper::MetaDataNames`)
- L13 _prototype_ `FName GetThumbnailFadeInMetaDataName();` (scope `TedsAssetDataHelper::MetaDataNames`)
- L14 _prototype_ `FName GetThumbnailHintTextMetaDataName();` (scope `TedsAssetDataHelper::MetaDataNames`)
- L15 _prototype_ `FName GetThumbnailRealTimeOnHoveredMetaDataName();` (scope `TedsAssetDataHelper::MetaDataNames`)
- L16 _prototype_ `FName GetThumbnailSizeOffsetMetaDataName();` (scope `TedsAssetDataHelper::MetaDataNames`)
- L17 _prototype_ `FName GetThumbnailCanDisplayEditModePrimitiveTools();` (scope `TedsAssetDataHelper::MetaDataNames`)
- L20 _namespace_ `namespace TableView` (scope `TedsAssetDataHelper`)
- L22 _prototype_ `FName GetWidgetTableName();` (scope `TedsAssetDataHelper::TableView`)
- L26 _prototype_ `FString RemoveSlashFromStart(const FString& InStringToModify);` (scope `TedsAssetDataHelper`) — Remove all / from the start of InStringToModify
- L29 _prototype_ `FString RemoveAllFromLastSlash(const FString& InStringToModify);` (scope `TedsAssetDataHelper`) — Remove Last / and successive char from InStringToModify

### `Plugins/Experimental/EditorDataStorageFeatures/Source/TedsAssetData/Public/TedsAssetDataStructs.h` (Public)


#### struct `UE::Editor::AssetData::FItemAttributeMetadata`  
`struct FItemAttributeMetadata`  
_L12-31_
- L15 _public member_ `UObject::FAssetRegistryTag::ETagType TagType = UObject::FAssetRegistryTag::TT_Hidden;` — The kind of data represented by this tag value
- L18 _public member_ `uint32 DisplayFlags = UObject::FAssetRegistryTag::TD_None;` — Flags giving hints at how to display this tag value in the UI (see ETagDisplay)
- L21 _public member_ `FText DisplayName;` — Resolved display name of the associated tag
- L24 _public member_ `FText TooltipText;` — Optional tooltip of the associated tag
- L27 _public member_ `FText Suffix;` — Optional suffix to apply to values of the tag attribute in the UI
- L30 _public member_ `FString ImportantValue;` — Optional value which denotes which values should be considered "important" in the UI

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace Editor` (scope `UE`)
- L9 _namespace_ `namespace AssetData` (scope `UE::Editor`)

### `Plugins/Experimental/EditorDataStorageFeatures/Source/TedsAssetData/Public/TedsAssetDataWidgetColumns.h` (Public)


#### struct `FThumbnailSizeColumn_Experimental`  
`struct FThumbnailSizeColumn_Experimental final : public FEditorDataStorageColumn`  
_L17-23_
- reflection: `USTRUCT(meta = (DisplayName = "Thumbnail Size"))`
- inherits: `FEditorDataStorageColumn`
- desc: Column to store the thumbnail size enum value of an asset
- L22 _public member_ `EThumbnailSize ThumbnailSize;` — EThumbnailSize

#### struct `FSizeValueColumn_Experimental`  
`struct FSizeValueColumn_Experimental final : public FEditorDataStorageColumn`  
_L27-33_
- reflection: `USTRUCT(meta = (DisplayName = "Size Value"))`
- inherits: `FEditorDataStorageColumn`
- desc: Column to store the size value of a widget
- L32 _public member_ `float SizeValue = 0;` — `UPROPERTY(meta = (IgnoreForMemberInitializationTest))`

#### struct `FWidgetPaddingColumn_Experimental`  
`struct FWidgetPaddingColumn_Experimental final : public FEditorDataStorageColumn`  
_L37-43_
- reflection: `USTRUCT(meta = (DisplayName = "Padding"))`
- inherits: `FEditorDataStorageColumn`
- desc: Column to store the padding
- L42 _public member_ `FMargin Padding;` — `UPROPERTY()`

#### struct `FThumbnailEditModeColumn_Experimental`  
`struct FThumbnailEditModeColumn_Experimental final : public FEditorDataStorageColumn`  
_L49-55_
- reflection: `USTRUCT(meta = (DisplayName = "Content Browser Settings"))`
- inherits: `FEditorDataStorageColumn`
- desc: Column added to a widget row to allow systems to provide an external EditMode trigger
- L54 _public member_ `bool IsEditModeToggled = false;` — `UPROPERTY(meta = (IgnoreForMemberInitializationTest))`

#### struct `FTextOverflowPolicyColumn_Experimental`  
`struct FTextOverflowPolicyColumn_Experimental : public FEditorDataStorageColumn`  
_L61-65_
- reflection: `USTRUCT(meta = (DisplayName = "Widget with externally managed OverflowPolicy"))`
- inherits: `FEditorDataStorageColumn`
- desc: Column added to a widget row to allow systems to provide an external Overflow Policy
- L64 _public member_ `ETextOverflowPolicy OverflowPolicy;`

#### struct `FWidgetVisibilityColumn_Experimental`  
`struct FWidgetVisibilityColumn_Experimental : public FEditorDataStorageColumn`  
_L71-75_
- reflection: `USTRUCT(meta = (DisplayName = "Widget with externally managed Visibility"))`
- inherits: `FEditorDataStorageColumn`
- desc: Column added to a widget row to allow systems to provide an external Visibility
- L74 _public member_ `EVisibility Visibility;`

#### struct `FFontStyleColumn_Experimental`  
`struct FFontStyleColumn_Experimental : public FEditorDataStorageColumn`  
_L81-85_
- reflection: `USTRUCT(meta = (DisplayName = "Widget with externally managed FontStyle"))`
- inherits: `FEditorDataStorageColumn`
- desc: Column added to a widget row to allow systems to provide an external FontStyle
- L84 _public member_ `FSlateFontInfo FontInfo;`

#### struct `FLocalWidgetTooltipColumn_Experimental`  
`struct FLocalWidgetTooltipColumn_Experimental : public FEditorDataStorageColumn`  
_L91-95_
- reflection: `USTRUCT(meta = (DisplayName = "Widget Tooltip"))`
- inherits: `FEditorDataStorageColumn`
- desc: Column added to a widget row to allow systems to store the widget tooltip
- L94 _public member_ `TSharedPtr<class IToolTip> Tooltip;`

#### struct `FOnGetWidgetSlateBrushColumn_Experimental`  
`struct FOnGetWidgetSlateBrushColumn_Experimental : public FEditorDataStorageColumn`  
_L103-107_
- reflection: `USTRUCT(meta = (DisplayName = "Widget with externally managed Brush"))`
- inherits: `FEditorDataStorageColumn`
- desc: Column added to a widget row to allow systems to provide an external brush callback for the widget TODO: This need to be later on removed and replaced by updating the value only when needed (Hover/Selection etc...)
- L106 _public member_ `TSharedPtr<FOnGetWidgetSlateBrush> OnGetWidgetSlateBrush;`

#### struct `FOnGetWidgetColorAndOpacityColumn_Experimental`  
`struct FOnGetWidgetColorAndOpacityColumn_Experimental : public FEditorDataStorageColumn`  
_L115-119_
- reflection: `USTRUCT(meta = (DisplayName = "Widget with externally managed ColorAndOpacity"))`
- inherits: `FEditorDataStorageColumn`
- desc: Column added to a widget row to allow systems to provide an external ColorAndOpacity callback for the widget TODO: This need to be later on removed and replaced by updating the value only when needed (Hover/Selection etc...)
- L118 _public member_ `TSharedPtr<FOnGetWidgetColorAndOpacity> OnGetWidgetColorAndOpacity;`

#### Free symbols / members of external scopes

- L97 _delegate_ `DECLARE_DELEGATE_RetVal(const FSlateBrush*, FOnGetWidgetSlateBrush) USTRUCT(meta = (DisplayName = "Widget with externally managed Brush")) struct FOnGetWidgetSlateBrushColumn_Experimental : public FEditorDataStorageColumn { GENERATED_BODY() TSharedPtr<FOnGetWidgetSlateBrush> OnGetWidgetSlateBrush; };`
- L109 _delegate_ `DECLARE_DELEGATE_RetVal(FSlateColor, FOnGetWidgetColorAndOpacity) USTRUCT(meta = (DisplayName = "Widget with externally managed ColorAndOpacity")) struct FOnGetWidgetColorAndOpacityColumn_Experimental : public FEditorDataStorageColumn { GENERATED_BODY() TSharedPtr<FOnGetWidgetColorAndOpacity> OnGetWidgetColorAndOpacity; };`

### `Plugins/Experimental/EditorDataStorageFeatures/Source/TedsAssetData/Public/Widgets/AssetDataLabelWidget.h` (Public)


#### class `UAssetDataLabelWidgetFactory`  
`class UAssetDataLabelWidgetFactory : public UEditorDataStorageFactory`  
_L20-29_
- reflection: `UCLASS()`
- inherits: `UEditorDataStorageFactory`
- L25 _public prototype_ `~UAssetDataLabelWidgetFactory() override = default;`
- L27 _public prototype_ `void RegisterWidgetConstructors(UE::Editor::DataStorage::ICoreProvider& DataStorage, UE::Editor::DataStorage::IUiProvider& DataStorageUi) const override;`

#### struct `FAssetDataLabelWidgetConstructor`  
`struct FAssetDataLabelWidgetConstructor : public FSimpleWidgetConstructor`  
_L33-51_
- reflection: `USTRUCT()`
- inherits: `FSimpleWidgetConstructor`
- desc: Label widget for assets in TEDS
- L38 _public prototype_ `FAssetDataLabelWidgetConstructor();`
- L39 _public prototype_ `explicit FAssetDataLabelWidgetConstructor(const UScriptStruct* TypeInfo);`
- L40 _public prototype_ `~FAssetDataLabelWidgetConstructor() override = default;`
- L42 _public prototype_ `virtual TSharedPtr<SWidget> CreateWidget( UE::Editor::DataStorage::ICoreProvider* DataStorage, UE::Editor::DataStorage::IUiProvider* DataStorageUi, UE::Editor::DataStorage::RowHandle TargetRow, UE::Editor::DataStorage::RowHandle WidgetRow, const UE::Editor::DataStorage::FMetaDataView& Arguments) override;`
- L50 _private prototype_ `TArray<TWeakObjectPtr<const UScriptStruct>> GetLabelColumns();`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace Editor` (scope `UE`)
- L12 _namespace_ `namespace DataStorage` (scope `UE::Editor`)

### `Plugins/Experimental/EditorDataStorageFeatures/Source/TedsAssetData/Public/Widgets/AssetNameWidget.h` (Public)


#### class `UE::Editor::DataStorage::FAssetNameWidgetSorter_NoSlash`  
`class FAssetNameWidgetSorter_NoSlash final : public TColumnSorterInterface<FColumnSorterInterface::ESortType::HybridSort, FAssetNameColumn>`  
_L18-26_
- inherits: `TColumnSorterInterface<FColumnSorterInterface::ESortType::HybridSort,FAssetNameColumn>`
- L21 _public prototype_ `virtual FText GetShortName() const override;`
- L24 _protected prototype_ `virtual int32 Compare(const FAssetNameColumn& Left, const FAssetNameColumn& Right) const override;`
- L25 _protected prototype_ `virtual FPrefixInfo CalculatePrefix(const FAssetNameColumn& Column, uint32 ByteIndex) const override;`

#### class `UE::Editor::DataStorage::FAssetNameWidgetSorter_WithSlash`  
`class FAssetNameWidgetSorter_WithSlash final : public TColumnSorterInterface<FColumnSorterInterface::ESortType::HybridSort, FAssetNameColumn>`  
_L28-36_
- inherits: `TColumnSorterInterface<FColumnSorterInterface::ESortType::HybridSort,FAssetNameColumn>`
- L31 _public prototype_ `virtual FText GetShortName() const override;`
- L34 _protected prototype_ `virtual int32 Compare(const FAssetNameColumn& Left, const FAssetNameColumn& Right) const override;`
- L35 _protected prototype_ `virtual FPrefixInfo CalculatePrefix(const FAssetNameColumn& Column, uint32 ByteIndex) const override;`

#### class `UAssetNameWidgetFactory`  
`class UAssetNameWidgetFactory : public UEditorDataStorageFactory`  
_L40-49_
- reflection: `UCLASS()`
- inherits: `UEditorDataStorageFactory`
- L45 _public prototype_ `virtual ~UAssetNameWidgetFactory() override = default;`
- L47 _public prototype_ `virtual void RegisterWidgetConstructors(UE::Editor::DataStorage::ICoreProvider& DataStorage, UE::Editor::DataStorage::IUiProvider& DataStorageUi) const override;`

#### struct `FAssetNameWidgetConstructor`  
`struct FAssetNameWidgetConstructor : public FSimpleWidgetConstructor`  
_L53-71_
- reflection: `USTRUCT()`
- inherits: `FSimpleWidgetConstructor`
- desc: Label for assets in TEDS
- L58 _public prototype_ `FAssetNameWidgetConstructor();`
- L60 _public prototype_ `virtual TSharedPtr<SWidget> CreateWidget( UE::Editor::DataStorage::ICoreProvider* DataStorage, UE::Editor::DataStorage::IUiProvider* DataStorageUi, UE::Editor::DataStorage::RowHandle TargetRow, UE::Editor::DataStorage::RowHandle WidgetRow, const UE::Editor::DataStorage::FMetaDataView& Arguments) override;`
- L67 _public prototype_ `virtual TArray<TSharedPtr<const UE::Editor::DataStorage::FColumnSorterInterface>> ConstructColumnSorters( UE::Editor::DataStorage::ICoreProvider* DataStorage, UE::Editor::DataStorage::IUiProvider* DataStorageUi, const UE::Editor::DataStorage::FMetaDataView& Arguments) override;`

#### Free symbols / members of external scopes

- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace Editor` (scope `UE`)
- L16 _namespace_ `namespace DataStorage` (scope `UE::Editor`)

### `Plugins/Experimental/EditorDataStorageFeatures/Source/TedsAssetData/Public/Widgets/AssetPreview/STedsAssetPreviewWidget.h` (Public)


#### class `STedsAssetPreviewWidget`  
`class STedsAssetPreviewWidget : public SCompoundWidget`  
_L16-109_
- inherits: `SCompoundWidget`
- L19 _public function_ `SLATE_BEGIN_ARGS(STedsAssetPreviewWidget) : _WidgetPurpose(UE::Editor::DataStorage::IUiProvider::FPurposeInfo("AssetPreview", "Default", NAME_None).GeneratePurposeID()) , _HeaderWidgetPurpose(UE::Editor::DataStorage::IUiProvider::FPurposeInfo("AssetPreview", "Header", "Default").GeneratePurposeID()) , _ThumbnailWidgetPurpose(UE::Editor::DataStorage::IUiProvider::FPurposeInfo("AssetPreview", "Thumbnail", NAME_None).GeneratePurposeID()) , _TargetRow(UE::Editor::DataStorage::InvalidRowHandle)`
- L27 _public prototype_ `SLATE_ARGUMENT(UE::Editor::DataStorage::IUiProvider::FPurposeID, WidgetPurpose)` — The widget purpose to use to create the tile widget
- L43 _public prototype_ `UE::Editor::DataStorage::RowHandle GetWidgetRowHandle() const;` — Get the Widget Row Handle of this TedsWidget
- L46 _public prototype_ `void ReconstructTedsWidget();` — Reconstructs all the TedsWidget used in this widget
- L49 _public prototype_ `void SetTargetRow(UE::Editor::DataStorage::RowHandle InTargetRow);` — Set the current Target Row to use, needs ReconstructTedsWidget to change
- L53 _private prototype_ `void CreateTedsWidget();` — Create and initialize the ITedsWidget
- L56 _private prototype_ `void ConstructWidget();` — Create all Teds widgets for this widget based on the current TargetRow
- L59 _private prototype_ `TArray<TWeakObjectPtr<const UScriptStruct>> GetHeaderColumns();` — Get the columns used for the Asset Preview Header TEDS widget
- L62 _private prototype_ `TArray<TWeakObjectPtr<const UScriptStruct>> GetThumbnailColumns();` — Get the columns used for the Thumbnail TEDS widget
- L65 _private prototype_ `TArray<TWeakObjectPtr<const UScriptStruct>> GetBasicInfoColumns();` — Get the columns used for the Asset Preview BasicInfo TEDS widget
- L68 _private prototype_ `TArray<TWeakObjectPtr<const UScriptStruct>> GetAdvancedInfoColumns();` — Get the columns used for the Asset Preview AdvancedInfo TEDS widget
- L71 _private prototype_ `UE::Editor::DataStorage::RowHandle GetReferencedRowHandle() const;` — Get the current Target Row
- L75 _private member_ `UE::Editor::DataStorage::RowHandle HeaderWidgetRowHandle = UE::Editor::DataStorage::InvalidRowHandle;` — Header Row Handle
- L78 _private member_ `UE::Editor::DataStorage::RowHandle ThumbnailWidgetRowHandle = UE::Editor::DataStorage::InvalidRowHandle;` — Thumbnail Row Handle
- L81 _private member_ `UE::Editor::DataStorage::RowHandle BasicInfoWidgetRowHandle = UE::Editor::DataStorage::InvalidRowHandle;` — Basic Info Row Handle
- L84 _private member_ `UE::Editor::DataStorage::RowHandle AdvancedInfoWidgetRowHandle = UE::Editor::DataStorage::InvalidRowHandle;` — Advanced Info Row Handle
- L87 _private member_ `UE::Editor::DataStorage::RowHandle TargetRow = UE::Editor::DataStorage::InvalidRowHandle;` — Target Row Handle
- L90 _private member_ `UE::Editor::DataStorage::IUiProvider::FPurposeID WidgetPurpose;` — Asset preview Purpose
- L93 _private member_ `UE::Editor::DataStorage::IUiProvider::FPurposeID WidgetHeaderPurpose;` — Asset preview Header Purpose
- L96 _private member_ `UE::Editor::DataStorage::IUiProvider::FPurposeID ThumbnailWidgetPurpose;` — Asset preview Thumbnail Purpose
- L99 _private member_ `bool bIsThumbnailExpanded = false;` — Whether the thumbnail is big or small
- L102 _private member_ `bool IsEditModeEnabled = false;` — Whether the thumbnail edit mode is enabled or not
- L105 _private member_ `TSharedPtr<UE::Editor::DataStorage::ITedsWidget> TedsWidget;` — Our teds widget
- L108 _private member_ `TSharedPtr<SBorder> PreviewPanel;` — Border containing the widget (child of the TedsWdiget)

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace Editor` (scope `UE`)
- L9 _namespace_ `namespace DataStorage` (scope `UE::Editor`)

### `Plugins/Experimental/EditorDataStorageFeatures/Source/TedsAssetData/Public/Widgets/AssetPreview/TedsAssetPreviewWidgetColumns.h` (Public)


#### struct `FExternalWidgetOnClickedColumn_Experimental`  
`struct FExternalWidgetOnClickedColumn_Experimental : public FEditorDataStorageColumn`  
_L16-24_
- reflection: `USTRUCT(meta = (DisplayName = "Widget with externally managed On Clicked behavior"))`
- inherits: `FEditorDataStorageColumn`
- desc: Column added to a widget row when an external widget manages On Clicked behavior
- L23 _public member_ `TSharedPtr<TDelegate<void()>> OnClicked;` — TODO: BindEvent currently do not support custom return value, since FReply do not have a default constructor it will fail FOnClicked OnClicked;
