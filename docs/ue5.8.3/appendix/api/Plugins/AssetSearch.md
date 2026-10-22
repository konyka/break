# Plugins / AssetSearch

- module root: `Plugins/Editor/AssetSearch/Source`
- headers: 27; symbols: 404
- symbol kinds: class=31, delegate=1, enum=2, enumerator=5, function=47, macro=2, member=131, prototype=175, struct=7, typedef=3
- PrivateDependencyModuleNames: AssetRegistry, BlueprintGraph, DeveloperSettings, EditorFramework, GameplayTags, InputCore, JsonUtilities, Projects, PropertyPath, SQLiteCore, Slate, SlateCore, UMG, UMGEditor, UnrealEd, WorkspaceMenuStructure
- PrivateIncludePathModuleNames: DerivedDataCache, MaterialEditor
- PublicDependencyModuleNames: Core, CoreUObject, Engine, Json, StudioTelemetry

### `Plugins/Editor/AssetSearch/Source/Private/AssetSearchDatabase.h` (Private)


#### class `FAssetSearchDatabase`  
`class FAssetSearchDatabase`  
_L19-120_
- L22 _public prototype_ `FAssetSearchDatabase();`
- L23 _public prototype_ `~FAssetSearchDatabase();`
- L25 _public prototype_ `FAssetSearchDatabase(const FAssetSearchDatabase&) = delete;`
- L26 _public prototype_ `FAssetSearchDatabase& operator=(const FAssetSearchDatabase&) = delete;`
- L28 _public prototype_ `FAssetSearchDatabase(FAssetSearchDatabase&&) = default;`
- L29 _public prototype_ `FAssetSearchDatabase& operator=(FAssetSearchDatabase&&) = default;`
- L34 _public prototype_ `bool IsValid() const;` — Is this a valid database? (ie, has been successfully opened).
- L43 _public prototype_ `bool Open(const FString& InSessionPath);` — Open (or create) a database file. @param InSessionPath				The root path to store all the data for this session under. @return True if the database was opened, false otherwise.
- L53 _public prototype_ `bool Open(const FString& InSessionPath, const ESQLiteDatabaseOpenMode InOpenMode);` — Open (or create) a database file. @param InSessionPath				The root path to store all the data for this session under. @param InOpenMode				How should the database be opened? @return True if the database was opened, false otherwise.
- L60 _public prototype_ `bool Close(const bool InDeleteDatabase = false);` — Close an open database file. @param InDeleteDatabase			True if the session database and its associated data should be deleted after closing the database.
- L66 _public prototype_ `FString GetFilename() const;` — Get the filename of the currently open database, or an empty string. @note The returned filename will be an absolute pathname.
- L71 _public prototype_ `FString GetLastError() const;` — Get the last error reported by this database.
- L76 _public prototype_ `bool IsAssetUpToDate(const FAssetData& InAssetData, const FString& IndexedJsonHash);` — Is the asset cache up to date for this asset?
- L81 _public prototype_ `void AddOrUpdateAsset(const FAssetData& InAssetData, const FString& IndexedJson, const FString& IndexedJsonHash);` — Adds an asset to the search database.
- L86 _public prototype_ `bool EnumerateSearchResults(const FString& QueryText, TFunctionRef<bool(FSearchRecord&&)> InCallback);` — Search for some stuff.
- L91 _public prototype_ `int64 GetTotalSearchRecords() const;` — Get the total number of records.
- L96 _public prototype_ `void RemoveAsset(const FAssetData& InAssetData);` — Remove asset from the the search database.
- L101 _public prototype_ `void RemoveAssetsNotInThisSet(const TArray<FAssetData>& InAssets);` — Remove asset from the the search database that are not in this set of assets.
- L103 _public member_ `bool bEnableIntegrityChecks = false;`
- L106 _private prototype_ `void LogLastError() const;`
- L110 _private member_ `TUniquePtr<FSQLiteDatabase> Database;` — Internal SQLite database
- L113 _private member_ `FString DatabaseFileName;` — The database filename name we use
- L116 _private member_ `FString SessionPath;` — Root path to store all session data under
- L119 _private member_ `TUniquePtr<FAssetSearchDatabaseStatements> Statements;` — Prepared statements for the currently open database

#### Free symbols / members of external scopes

- L17 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogAssetSearch, Log, All);`
- L17 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogAssetSearch, Log, All);`

### `Plugins/Editor/AssetSearch/Source/Private/AssetSearchManager.h` (Private)


#### class `FAssetSearchManager`  
`class FAssetSearchManager : public FRunnable`  
_L23-153_
- inherits: `FRunnable`
- L25 _private member_ `static const FName AssetSearchIndexVersionTag;`
- L26 _private member_ `static const FName AssetSearchIndexHashTag;`
- L27 _private member_ `static const FName AssetSearchIndexDataTag;`
- L30 _public prototype_ `FAssetSearchManager();`
- L31 _public prototype_ `virtual ~FAssetSearchManager();`
- L33 _public prototype_ `void Start();`
- L34 _public prototype_ `void RegisterAssetIndexer(const UClass* AssetClass, TUniquePtr<IAssetIndexer>&& Indexer);`
- L35 _public prototype_ `void RegisterSearchProvider(FName SearchProviderName, TUniquePtr<ISearchProvider>&& InSearchProvider);`
- L37 _public prototype_ `FSearchStats GetStats() const;`
- L39 _public prototype_ `void Search(FSearchQueryPtr SearchQuery);`
- L42 _public prototype_ `void ForceIndexOnAssetsMissingIndex();` — Utility
- L45 _private prototype_ `void TryConnectToDatabase();`
- L47 _private prototype_ `bool Tick_GameThread(float DeltaTime);`
- L48 _private prototype_ `virtual uint32 Run() override;`
- L49 _private prototype_ `void Tick_DatabaseOperationThread();`
- L52 _private prototype_ `void UpdateScanningAssets();`
- L53 _private prototype_ `void StartScanningAssets();`
- L54 _private prototype_ `void StopScanningAssets();`
- L56 _private prototype_ `void OnAssetAdded(const FAssetData& InAssetData);`
- L57 _private prototype_ `void OnAssetRemoved(const FAssetData& InAssetData);`
- L58 _private prototype_ `void StartScanningAssetsOnAssetScanFinished();`
- L59 _private prototype_ `TArray<FAssetData> StartScanningAssetsOnAssetScanFinishedInternal();`
- L61 _private prototype_ `void HandleOnGetExtraObjectTags(FAssetRegistryTagsContext Context);`
- L62 _private prototype_ `void HandlePackageSaved(const FString& PackageFilename, UPackage* Package, FObjectPostSaveContext ObjectSaveContext);`
- L63 _private prototype_ `void OnAssetLoaded(UObject* InObject);`
- L65 _private prototype_ `void AddOrUpdateAsset(const FAssetData& InAsset, const FString& IndexedJson, const FString& DerivedDataKey);`
- L67 _private prototype_ `bool RequestIndexAsset_DDC(const UObject* InAsset);`
- L68 _private prototype_ `bool IsAssetIndexable(const UObject* InAsset) const;`
- L70 _private prototype_ `bool TryLoadIndexForAsset(const FAssetData& InAsset);`
- L71 _private prototype_ `bool TryLoadIndexForAsset_Tags(const FAssetData& InAssetData);`
- L72 _private prototype_ `bool TryLoadIndexForAsset_DDC(const FAssetData& InAssetData);`
- L74 _private prototype_ `void AsyncRequestDownload(const FAssetData& InAssetData, const FString& InDDCKey);`
- L75 _private prototype_ `bool AsyncGetDerivedDataKey(const FAssetData& UnindexedAsset, TFunction<void(bool, FString)> DDCKeyCallback);`
- L76 _private prototype_ `bool HasIndexerForClass(const UClass* InAssetClass) const;`
- L78 _private prototype_ `FString GetBaseIndexKey(const UClass* InAssetClass) const;`
- L79 _private prototype_ `FString GetIndexerVersion(const UClass* InAssetClass) const;`
- L80 _private prototype_ `bool IndexAsset(const FAssetData& InAssetData, const UObject* InAsset, FString& OutIndexedJson) const;`
- L82 _private prototype_ `void StoreIndexForAsset(const UObject* InAsset);`
- L83 _private prototype_ `void StoreIndexForAsset_Tags(const UObject* InAsset);`
- L84 _private prototype_ `void StoreIndexForAsset_DDC(const UObject* InAsset);`
- L86 _private prototype_ `void LoadDDCContentIntoDatabase(const FAssetData& InAsset, const TArray<uint8>& Content, const FString& DerivedDataKey);`
- L88 _private prototype_ `void AsyncMainThreadTask(TFunction<void()> Task);`
- L89 _private prototype_ `void ProcessGameThreadTasks();`
- L91 _private prototype_ `uint64 GetTextHash(FStringView PackageRelativeExportPath) const;`
- L94 _private member_ `bool bStarted = false;`
- L95 _private member_ `bool bFinishedOnce = false;`
- L98 _private member_ `mutable FCriticalSection AssetSearchManagerCS;`
- L99 _private member_ `FFileInfoDatabase FileInfoDatabase;`
- L100 _private member_ `FCriticalSection FileInfoDatabaseCS;`
- L101 _private member_ `FAssetSearchDatabase SearchDatabase;`
- L102 _private member_ `FCriticalSection SearchDatabaseCS;`
- L103 _private member_ `TAtomic<int32> PendingDatabaseUpdates;`
- L104 _private member_ `TAtomic<int32> IsAssetUpToDateCount;`
- L105 _private member_ `TAtomic<int32> ActiveDownloads;`
- L106 _private member_ `TAtomic<int32> DownloadQueueCount;`
- L107 _private member_ `TAtomic<int64> TotalSearchRecords;`
- L109 _private member_ `double LastRecordCountUpdateSeconds;`
- L112 _private member_ `TMap<FName, TUniquePtr<IAssetIndexer>> Indexers;`
- L114 _private member_ `TMap<FName, TUniquePtr<ISearchProvider>> SearchProviders;`
- L116 _private member_ `TArray<TWeakObjectPtr<UObject>> RequestIndexQueue;`
- L124 _private member_ `TArray<FAssetOperation> ProcessAssetQueue;`
- L132 _private member_ `TQueue<FAssetDDCRequest, EQueueMode::Mpsc> DownloadQueue;`
- L133 _private member_ `TQueue<FAssetDDCRequest, EQueueMode::Mpsc> ProcessDDCQueue;`
- L135 _private member_ `TArray<FAssetData> AssetNeedingReindexing;`
- L137 _private member_ `FTSTicker::FDelegateHandle TickerHandle;`
- L139 _private member_ `TQueue<TFunction<void()>, EQueueMode::Mpsc> GT_Tasks;`
- L142 _private member_ `volatile bool bDatabaseOpen = false;`
- L143 _private member_ `volatile double LastConnectionAttempt = 0;`
- L145 _private member_ `ESearchIntermediateStorage IntermediateStorage;`
- L147 _private member_ `TAtomic<bool> RunThread;`
- L148 _private member_ `FRunnableThread* DatabaseThread = nullptr;`
- L150 _private member_ `TQueue<TFunction<void()>, EQueueMode::Mpsc> ImmediateOperations;`
- L151 _private member_ `TQueue<TFunction<void()>, EQueueMode::Mpsc> FeedOperations;`
- L152 _private member_ `TQueue<TFunction<void()>, EQueueMode::Mpsc> UpdateOperations;`

#### struct `FAssetSearchManager::FAssetOperation`  
`struct FAssetOperation`  
_L118-122_
- L120 _public member_ `FAssetData Asset;`
- L121 _public member_ `bool bRemoval = false;`

#### struct `FAssetSearchManager::FAssetDDCRequest`  
`struct FAssetDDCRequest`  
_L126-131_
- L128 _public member_ `FAssetData AssetData;`
- L129 _public member_ `FString DDCKey;`
- L130 _public member_ `uint32 DDCHandle;`

### `Plugins/Editor/AssetSearch/Source/Private/FileInfoDatabase.h` (Private)


#### struct `FAssetFileInfo`  
`struct FAssetFileInfo`  
_L13-18_
- L15 _public member_ `FName PackageName;`
- L16 _public member_ `FDateTime LastModified;`
- L17 _public member_ `FMD5Hash Hash;`

#### class `FFileInfoDatabase`  
`class FFileInfoDatabase`  
_L20-101_
- L23 _public prototype_ `FFileInfoDatabase();`
- L24 _public prototype_ `~FFileInfoDatabase();`
- L26 _public prototype_ `FFileInfoDatabase(const FFileInfoDatabase&) = delete;`
- L27 _public prototype_ `FFileInfoDatabase& operator=(const FFileInfoDatabase&) = delete;`
- L29 _public prototype_ `FFileInfoDatabase(FFileInfoDatabase&&) = default;`
- L30 _public prototype_ `FFileInfoDatabase& operator=(FFileInfoDatabase&&) = default;`
- L35 _public prototype_ `bool IsValid() const;` — Is this a valid database? (ie, has been successfully opened).
- L44 _public prototype_ `bool Open(const FString& InSessionPath);` — Open (or create) a database file. @param InSessionPath				The root path to store all the data for this session under. @return True if the database was opened, false otherwise.
- L54 _public prototype_ `bool Open(const FString& InSessionPath, const ESQLiteDatabaseOpenMode InOpenMode);` — Open (or create) a database file. @param InSessionPath				The root path to store all the data for this session under. @param InOpenMode				How should the database be opened? @return True if the database was opened, false otherwise.
- L61 _public prototype_ `bool Close(const bool InDeleteDatabase = false);` — Close an open database file. @param InDeleteDatabase			True if the session database and its associated data should be deleted after closing the database.
- L67 _public prototype_ `FString GetFilename() const;` — Get the filename of the currently open database, or an empty string. @note The returned filename will be an absolute pathname.
- L72 _public prototype_ `FString GetLastError() const;` — Get the last error reported by this database.
- L77 _public prototype_ `bool AddOrUpdateFileInfo(const FAssetData& InAssetData, FAssetFileInfo& OutFileInfo);` — Update the file hash table.
- L78 _public prototype_ `void AddOrUpdateFileInfos(const TArray<FAssetData>& InAssets);`
- L80 _public prototype_ `void UpdateFileHash(const FAssetData& InAssetData, FAssetFileInfo& OutFileInfo);`
- L82 _public prototype_ `TMap<FName, FAssetFileInfo> GetAllFileInfos();`
- L84 _public member_ `bool bEnableIntegrityChecks = false;`
- L87 _private prototype_ `void LogLastError() const;`
- L91 _private member_ `TUniquePtr<FSQLiteDatabase> Database;` — Internal SQLite database
- L94 _private member_ `FString DatabaseFileName;` — The database filename name we use
- L97 _private member_ `FString SessionPath;` — Root path to store all session data under
- L100 _private member_ `TUniquePtr<FFileInfoDatabaseStatements> Statements;` — Prepared statements for the currently open database

### `Plugins/Editor/AssetSearch/Source/Private/Indexers/ActorIndexer.h` (Private)


#### class `FActorIndexer`  
`class FActorIndexer : public IAssetIndexer`  
_L10-15_
- inherits: `IAssetIndexer`
- L12 _private function_ `virtual FString GetName() const override`
- L13 _private prototype_ `virtual int32 GetVersion() const override;`
- L14 _private prototype_ `virtual void IndexAsset(const UObject* InAssetObject, FSearchSerializer& Serializer) const override;`

### `Plugins/Editor/AssetSearch/Source/Private/Indexers/BlueprintIndexer.h` (Private)


#### class `FBlueprintIndexer`  
`class FBlueprintIndexer : public IAssetIndexer`  
_L15-28_
- inherits: `IAssetIndexer`
- L18 _public function_ `virtual FString GetName() const override`
- L19 _public prototype_ `virtual int32 GetVersion() const override;`
- L20 _public prototype_ `virtual void IndexAsset(const UObject* InAssetObject, FSearchSerializer& Serializer) const override;`
- L23 _private prototype_ `void IndexClassDefaultObject(const UBlueprint* InBlueprint, FSearchSerializer& Serializer) const;`
- L24 _private prototype_ `void IndexComponents(const UBlueprint* InBlueprint, FSearchSerializer& Serializer) const;`
- L25 _private prototype_ `void IndexGraphs(const UBlueprint* InBlueprint, FSearchSerializer& Serializer) const;`
- L26 _private prototype_ `void IndexMemberReference(FSearchSerializer& Serializer, const FMemberReference& MemberReference, const FString& MemberType) const;`
- L27 _private prototype_ `void IndexExtensions(const UBlueprint* InBlueprint, FSearchSerializer& Serializer) const;`

### `Plugins/Editor/AssetSearch/Source/Private/Indexers/CurveTableIndexer.h` (Private)


#### class `FCurveTableIndexer`  
`class FCurveTableIndexer : public IAssetIndexer`  
_L10-15_
- inherits: `IAssetIndexer`
- L12 _private function_ `virtual FString GetName() const override`
- L13 _private prototype_ `virtual int32 GetVersion() const override;`
- L14 _private prototype_ `virtual void IndexAsset(const UObject* InAssetObject, FSearchSerializer& Serializer) const override;`

### `Plugins/Editor/AssetSearch/Source/Private/Indexers/DataTableIndexer.h` (Private)


#### class `FDataTableIndexer`  
`class FDataTableIndexer : public IAssetIndexer`  
_L10-15_
- inherits: `IAssetIndexer`
- L12 _private function_ `virtual FString GetName() const override`
- L13 _private prototype_ `virtual int32 GetVersion() const override;`
- L14 _private prototype_ `virtual void IndexAsset(const UObject* InAssetObject, FSearchSerializer& Serializer) const override;`

### `Plugins/Editor/AssetSearch/Source/Private/Indexers/DialogueWaveIndexer.h` (Private)


#### class `FDialogueWaveIndexer`  
`class FDialogueWaveIndexer : public IAssetIndexer`  
_L10-15_
- inherits: `IAssetIndexer`
- L12 _private function_ `virtual FString GetName() const override`
- L13 _private prototype_ `virtual int32 GetVersion() const override;`
- L14 _private prototype_ `virtual void IndexAsset(const UObject* InAssetObject, FSearchSerializer& Serializer) const override;`

### `Plugins/Editor/AssetSearch/Source/Private/Indexers/GenericObjectIndexer.h` (Private)


#### class `FGenericObjectIndexer`  
`class FGenericObjectIndexer : public IAssetIndexer`  
_L10-24_
- inherits: `IAssetIndexer`
- L13 _public function_ `FGenericObjectIndexer(const FString& InName) : Name(InName)`
- L18 _public function_ `virtual FString GetName() const override`
- L19 _public prototype_ `virtual int32 GetVersion() const override;`
- L20 _public prototype_ `virtual void IndexAsset(const UObject* InAssetObject, FSearchSerializer& Serializer) const override;`
- L23 _protected member_ `const FString Name;`

### `Plugins/Editor/AssetSearch/Source/Private/Indexers/LevelIndexer.h` (Private)


#### class `FLevelIndexer`  
`class FLevelIndexer : public IAssetIndexer`  
_L10-16_
- inherits: `IAssetIndexer`
- L12 _private function_ `virtual FString GetName() const override`
- L13 _private prototype_ `virtual int32 GetVersion() const override;`
- L14 _private prototype_ `virtual void IndexAsset(const UObject* InAssetObject, FSearchSerializer& Serializer) const override;`
- L15 _private prototype_ `virtual void GetNestedAssetTypes(TArray<UClass*>& OutTypes) const override;`

### `Plugins/Editor/AssetSearch/Source/Private/Indexers/MaterialExpressionIndexer.h` (Private)


#### class `FMaterialExpressionIndexer`  
`class FMaterialExpressionIndexer : public IAssetIndexer`  
_L12-27_
- inherits: `IAssetIndexer`
- L15 _public function_ `FMaterialExpressionIndexer(const FString& InName) : Name(InName)`
- L20 _public function_ `virtual FString GetName() const override`
- L21 _public prototype_ `virtual int32 GetVersion() const override;`
- L22 _public prototype_ `virtual void IndexAsset(const UObject* InAssetObject, FSearchSerializer& Serializer) const override;`
- L25 _private prototype_ `void IndexParameters(const UObject* InAssetObject, FSearchSerializer& Serializer) const;`
- L26 _private member_ `const FString Name;`

### `Plugins/Editor/AssetSearch/Source/Private/Indexers/SoundCueIndexer.h` (Private)


#### class `FSoundCueIndexer`  
`class FSoundCueIndexer : public IAssetIndexer`  
_L10-15_
- inherits: `IAssetIndexer`
- L12 _private function_ `virtual FString GetName() const override`
- L13 _private prototype_ `virtual int32 GetVersion() const override;`
- L14 _private prototype_ `virtual void IndexAsset(const UObject* InAssetObject, FSearchSerializer& Serializer) const override;`

### `Plugins/Editor/AssetSearch/Source/Private/Indexers/WidgetBlueprintIndexer.h` (Private)


#### class `FWidgetBlueprintIndexer`  
`class FWidgetBlueprintIndexer : public IAssetIndexer`  
_L10-15_
- inherits: `IAssetIndexer`
- L12 _private function_ `virtual FString GetName() const override`
- L13 _private prototype_ `virtual int32 GetVersion() const override;`
- L14 _private prototype_ `virtual void IndexAsset(const UObject* InAssetObject, FSearchSerializer& Serializer) const override;`

### `Plugins/Editor/AssetSearch/Source/Private/Providers/AssetRegistrySearchProvider.h` (Private)


#### class `FAssetRegistrySearchProvider`  
`class FAssetRegistrySearchProvider : public ISearchProvider`  
_L7-12_
- inherits: `ISearchProvider`
- L10 _public function_ `virtual ~FAssetRegistrySearchProvider()`
- L11 _public prototype_ `virtual void Search(FSearchQueryPtr SearchQuery) override;`

### `Plugins/Editor/AssetSearch/Source/Private/Settings/SearchProjectSettings.h` (Private)


#### enum `ESearchIntermediateStorage`  
`enum class ESearchIntermediateStorage : uint8`  
_L11-18_
- reflection: `UENUM()`
- L14 _public enumerator_ `DerivedDataCache` — Stores the json snippets of indexable data in the DDC so that they can be downloaded as needed.
- L17 _public enumerator_ `AssetTagData` — Stores the json snippets and the json hash in the tag data for the asset.  This increases the size of all assets that are indexed, but can be a great benefit to teams that don't have a large shared DDC.

#### class `USearchProjectSettings`  
`class USearchProjectSettings : public UDeveloperSettings`  
_L21-37_
- reflection: `UCLASS(config = Editor, defaultconfig, meta=(DisplayName="Search"))`
- inherits: `UDeveloperSettings`
- L26 _public prototype_ `USearchProjectSettings();`
- L29 _public member_ `ESearchIntermediateStorage IntermediateStorage = ESearchIntermediateStorage::DerivedDataCache;` — `UPROPERTY(config, EditAnywhere, Category=General, Meta = (ConfigRestartRequired = true))`
- L32 _public member_ `TArray<FDirectoryPath> IgnoredPaths;` — `UPROPERTY(config, EditAnywhere, Category=General)`
- L36 _public member_ `bool bDisableDDC;` — `UPROPERTY(config, EditAnywhere, Category=General)` — Disable put/fetch operations with the DDC, without changing storage location

### `Plugins/Editor/AssetSearch/Source/Private/Settings/SearchUserSettings.h` (Private)


#### struct `FSearchPerformance`  
`struct FSearchPerformance`  
_L11-24_
- reflection: `USTRUCT()`
- L17 _public member_ `int32 ParallelDownloads = 0;` — `UPROPERTY(EditAnywhere, Category = "Performance")`
- L20 _public member_ `int32 DownloadProcessRate = 0;` — `UPROPERTY(EditAnywhere, AdvancedDisplay, Category = "Performance")`
- L23 _public member_ `int32 AssetScanRate = 0;` — `UPROPERTY(EditAnywhere, AdvancedDisplay, Category = "Performance")`

#### class `USearchUserSettings`  
`class USearchUserSettings : public UDeveloperSettings`  
_L27-65_
- reflection: `UCLASS(config = EditorPerProjectUserSettings, meta=(DisplayName="Search"))`
- inherits: `UDeveloperSettings`
- L32 _public prototype_ `USearchUserSettings();`
- L36 _public member_ `bool bEnableSearch;` — `UPROPERTY(config, EditAnywhere, Category = General)` — Enable this to begin using search.
- L40 _public member_ `bool bEnableIntegrityChecks;` — `UPROPERTY(config, EditAnywhere, Category=General)` — Enable sqlite integrity checks on database load/setup. Slow.
- L43 _public member_ `TArray<FDirectoryPath> IgnoredPaths;` — `UPROPERTY(config, EditAnywhere, Category=General)`
- L46 _public member_ `bool bShowAssetsNeedingIndexing = true;` — `UPROPERTY(config, EditAnywhere, Category=General)`
- L49 _public member_ `bool bAutoExpandAssets = true;` — `UPROPERTY(config, EditAnywhere, Category = General)`
- L52 _public member_ `bool bThrottleInBackground = true;` — `UPROPERTY(config, EditAnywhere, Category = Performance)`
- L55 _public member_ `FSearchPerformance DefaultOptions;` — `UPROPERTY(config, EditAnywhere, Category = Performance)`
- L58 _public member_ `FSearchPerformance BackgroundtOptions;` — `UPROPERTY(config, EditAnywhere, Category = Performance)`
- L60 _public prototype_ `const FSearchPerformance& GetPerformanceOptions() const;`
- L64 _public member_ `int32 SearchInForeground = 0;` — `UPROPERTY(Transient)`

### `Plugins/Editor/AssetSearch/Source/Private/Widgets/SSearchBrowser.h` (Private)


#### class `SSearchBrowser`  
`class SSearchBrowser : public SCompoundWidget`  
_L22-93_
- inherits: `SCompoundWidget`
- desc: Implements the undo history panel.
- L26 _public function_ `SLATE_BEGIN_ARGS(SSearchBrowser)`
- L31 _public prototype_ `virtual ~SSearchBrowser();`
- L38 _public prototype_ `void Construct( const FArguments& InArgs );` — Construct this widget @param InArgs The declaration data for this widget.
- L41 _public prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;`
- L45 _private prototype_ `TSharedRef<SWidget> GetViewMenuWidget();`
- L47 _private prototype_ `FText GetSearchBackgroundText() const;`
- L48 _private prototype_ `FText GetStatusText() const;`
- L49 _private prototype_ `FText GetAdvancedStatus() const;`
- L50 _private prototype_ `FText GetUnindexedAssetsText() const;`
- L52 _private prototype_ `void HandleForceIndexOfAssetsMissingIndex();`
- L54 _private prototype_ `FReply OnRefresh();`
- L56 _private prototype_ `EColumnSortMode::Type GetColumnSortMode(const FName ColumnId) const;`
- L57 _private prototype_ `void OnColumnSortModeChanged(const EColumnSortPriority::Type SortPriority, const FName& ColumnId, const EColumnSortMode::Type InSortMode);`
- L59 _private prototype_ `void RefreshList();`
- L60 _private prototype_ `void AppendResult(FSearchRecord&& InResult);`
- L62 _private prototype_ `void OnSearchTextCommited(const FText& InText, ETextCommit::Type InCommitType);`
- L63 _private prototype_ `void OnSearchTextChanged(const FText& InText);`
- L64 _private prototype_ `void TryRefreshingSearch(const FText& InText);`
- L66 _private prototype_ `TSharedRef<ITableRow> HandleListGenerateRow(TSharedPtr<FSearchNode> TransactionInfo, const TSharedRef<STableViewBase>& OwnerTable);`
- L67 _private prototype_ `void GetChildrenForInfo(TSharedPtr<FSearchNode> InInfo, TArray< TSharedPtr<FSearchNode> >& OutChildren);`
- L69 _private prototype_ `void HandleListSelectionChanged(TSharedPtr<FSearchNode> TransactionInfo, ESelectInfo::Type SelectInfo);`
- L71 _private prototype_ `bool IsSearching() const;`
- L75 _private member_ `FText FilterText;`
- L78 _private member_ `FString FilterString;` — Filters
- L80 _private member_ `FSearchQueryWeakPtr ActiveSearchPtr;`
- L82 _private member_ `TMap<FString, TSharedPtr<FAssetNode>> SearchResultHierarchy;`
- L83 _private member_ `TArray< TSharedPtr<FSearchNode> > SearchResults;`
- L85 _private member_ `TSharedPtr< STreeView< TSharedPtr<FSearchNode> > > SearchTreeView;`
- L87 _private member_ `IAssetRegistry* AssetRegistry = nullptr;`
- L89 _private member_ `TSharedPtr<SHeaderRow> HeaderColumns;`
- L91 _private member_ `FName SortByColumn;`
- L92 _private member_ `EColumnSortMode::Type SortMode;`

### `Plugins/Editor/AssetSearch/Source/Private/Widgets/SSearchTreeRow.h` (Private)


#### class `SSearchTreeRow`  
`class SSearchTreeRow : public SMultiColumnTableRow<TSharedPtr<FSearchNode>>`  
_L17-55_
- inherits: `SMultiColumnTableRow<TSharedPtr<FSearchNode>>`
- desc: Implements a row widget for a live uobject.
- L21 _public function_ `SLATE_BEGIN_ARGS(SSearchTreeRow)`
- L27 _public member_ `static FName NAME_ColumnName;`
- L28 _public member_ `static FName NAME_ColumnType;`
- L34 _public function_ `SSearchTreeRow()`
- L38 _public prototype_ `void Construct(const FArguments& InArgs, const TSharedRef<STableViewBase>& InOwnerTableView, IAssetRegistry* InAssetRegistry, TSharedPtr<FAssetThumbnailPool> InThumbnailPool);`
- L42 _public prototype_ `virtual TSharedRef<SWidget> GenerateWidget();`
- L44 _public prototype_ `virtual TSharedRef<SWidget> GenerateWidgetForColumn(const FName& ColumnName) override;`
- L46 _public prototype_ `virtual FReply OnMouseButtonDoubleClick(const FGeometry& InMyGeometry, const FPointerEvent& InMouseEvent) override;`
- L50 _private member_ `TSharedPtr<FSearchNode> BrowserObject;`
- L52 _private member_ `IAssetRegistry* AssetRegistry;`
- L54 _private member_ `TSharedPtr<FAssetThumbnailPool> ThumbnailPool;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define LOCTEXT_NAMESPACE "SObjectBrowserTableRow"`

### `Plugins/Editor/AssetSearch/Source/Private/Widgets/SearchModel.h` (Private)


#### enum `ESearchNodeType`  
`enum class ESearchNodeType : uint8`  
_L7-12_
- L9 _public enumerator_ `Asset`
- L10 _public enumerator_ `Object`
- L11 _public enumerator_ `Property`

#### class `FSearchNode`  
`class FSearchNode : public TSharedFromThis<FSearchNode>`  
_L14-29_
- inherits: `TSharedFromThis<FSearchNode>`
- L17 _public function_ `virtual ~FSearchNode()`
- L18 _public function_ `virtual void GetChildren(TArray<TSharedPtr<FSearchNode>>& OutChildren)`
- L19 _public prototype_ `virtual ESearchNodeType GetType() const = 0;`
- L20 _public prototype_ `virtual FString GetText() const = 0;`
- L21 _public prototype_ `virtual FString GetObjectPath() const = 0;`
- L23 _public function_ `float GetTotalScore() const`
- L24 _public function_ `float GetMaxScore() const`
- L27 _protected member_ `float TotalScore = 0;`
- L28 _protected member_ `float MaxScore = 0;`

#### class `FAssetObjectPropertyNode`  
`class FAssetObjectPropertyNode : public FSearchNode`  
_L31-51_
- inherits: `FSearchNode`
- L34 _public function_ `FAssetObjectPropertyNode(const FSearchRecord& InResult) : Record(InResult)`
- L39 _public function_ `virtual ESearchNodeType GetType() const override`
- L40 _public function_ `virtual FString GetText() const override`
- L45 _public function_ `virtual FString GetObjectPath() const override`
- L50 _public member_ `FSearchRecord Record;`

#### class `FAssetObjectNode`  
`class FAssetObjectNode : public FSearchNode`  
_L53-96_
- inherits: `FSearchNode`
- L56 _public function_ `FAssetObjectNode(const FSearchRecord& InResult) : object_name(InResult.object_name) , object_path(InResult.object_path) , object_native_class(InResult.object_native_class)`
- L64 _public function_ `void Append(const FSearchRecord& InResult)`
- L71 _public function_ `virtual ESearchNodeType GetType() const override`
- L73 _public function_ `virtual void GetChildren(TArray<TSharedPtr<FSearchNode>>& OutChildren) override`
- L81 _public function_ `virtual FString GetText() const override`
- L86 _public function_ `virtual FString GetObjectPath() const override`
- L91 _public member_ `FString object_name;`
- L92 _public member_ `FString object_path;`
- L93 _public member_ `FString object_native_class;`
- L95 _public member_ `TArray<TSharedPtr<FAssetObjectPropertyNode>> Properties;`

#### class `FAssetNode`  
`class FAssetNode : public FSearchNode`  
_L98-173_
- inherits: `FSearchNode`
- L101 _public function_ `FAssetNode(const FSearchRecord& InResult) : AssetName(InResult.AssetName) , AssetPath(InResult.AssetPath) , AssetClass(InResult.AssetClass.ToString())`
- L109 _public function_ `void Append(const FSearchRecord& InResult)`
- L140 _public function_ `virtual ESearchNodeType GetType() const override`
- L142 _public function_ `virtual void GetChildren(TArray<TSharedPtr<FSearchNode>>& OutChildren) override`
- L155 _public function_ `virtual FString GetText() const override`
- L160 _public function_ `virtual FString GetObjectPath() const override`
- L165 _public member_ `FString AssetName;`
- L166 _public member_ `FString AssetPath;`
- L167 _public member_ `FString AssetClass;`
- L169 _public member_ `TArray<TSharedPtr<FAssetObjectPropertyNode>> Properties;`
- L170 _public member_ `TMap<FString, TSharedPtr<FAssetObjectNode>> Objects;`
- L172 _public member_ `TArray<TSharedPtr<FAssetObjectNode>> SortedObjectArray;`

### `Plugins/Editor/AssetSearch/Source/Private/Widgets/SearchStyle.h` (Private)


#### class `FPluginStyleSet`  
`class FPluginStyleSet : public FSlateStyleSet`  
_L10-14_
- inherits: `FSlateStyleSet`
- L13 _public prototype_ `FPluginStyleSet(const FName& InPluginName, const FName& InStyleSetName = NAME_None);`

#### class `FSearchStyle`  
`class FSearchStyle : public FPluginStyleSet`  
_L19-30_
- inherits: `FPluginStyleSet`
- L24 _public prototype_ `static FSearchStyle& Get();` — Access the singleton instance for this style set
- L28 _private prototype_ `FSearchStyle();`
- L29 _private prototype_ `~FSearchStyle();`

### `Plugins/Editor/AssetSearch/Source/Public/AssetSearchCommands.h` (Public)


#### class `FAssetSearchCommands`  
`class FAssetSearchCommands : public TCommands<FAssetSearchCommands>`  
_L8-18_
- inherits: `TCommands<FAssetSearchCommands>`
- L11 _public prototype_ `FAssetSearchCommands();`
- L14 _public prototype_ `virtual void RegisterCommands() override;` — TCommands<> interface
- L17 _public member_ `TSharedPtr<FUICommandInfo> ViewAssetSearch;`

### `Plugins/Editor/AssetSearch/Source/Public/IAssetIndexer.h` (Public)


#### class `IAssetIndexer`  
`class IAssetIndexer`  
_L10-24_
- L14 _public prototype_ `virtual ~IAssetIndexer() = 0;`
- L15 _public prototype_ `virtual FString GetName() const = 0;`
- L16 _public prototype_ `virtual int32 GetVersion() const = 0;`
- L17 _public prototype_ `virtual void IndexAsset(const UObject* InAssetObject, FSearchSerializer& Serializer) const = 0;`
- L23 _public function_ `virtual void GetNestedAssetTypes(TArray<UClass*>& OutTypes) const` — If your package contains a nested asset, such as the Blueprint stored in Level/World packages, it would return UBlueprint's class in the array.  This is only important if you use IndexNestedAsset.
- L26 _prototype_ `inline IAssetIndexer::~IAssetIndexer() = default;`

### `Plugins/Editor/AssetSearch/Source/Public/IAssetSearchModule.h` (Public)


#### struct `FSearchStats`  
`struct FSearchStats`  
_L12-26_
- L14 _public member_ `int32 Scanning = 0;`
- L15 _public member_ `int32 Processing = 0;`
- L16 _public member_ `int32 Updating = 0;`
- L18 _public member_ `int32 AssetsMissingIndex = 0;`
- L20 _public member_ `int64 TotalRecords = 0;`
- L22 _public function_ `bool IsUpdating() const`

#### class `IAssetSearchModule`  
`class IAssetSearchModule : public IModuleInterface`  
_L31-59_
- inherits: `IModuleInterface`
- L34 _public function_ `static inline IAssetSearchModule& Get()`
- L40 _public function_ `static inline bool IsAvailable()`
- L46 _public prototype_ `virtual FSearchStats GetStats() const = 0;`
- L48 _public prototype_ `virtual void Search(FSearchQueryPtr SearchQuery) = 0;`
- L50 _public prototype_ `virtual void ForceIndexOnAssetsMissingIndex() = 0;`
- L52 _public prototype_ `virtual void RegisterAssetIndexer(const UClass* AssetClass, TUniquePtr<IAssetIndexer>&& Indexer) = 0;`
- L53 _public prototype_ `virtual void RegisterSearchProvider(FName SearchProviderName, TUniquePtr<ISearchProvider>&& InSearchProvider) = 0;`
- L58 _public function_ `virtual ~IAssetSearchModule()` — Virtual destructor.

### `Plugins/Editor/AssetSearch/Source/Public/ISearchProvider.h` (Public)


#### class `ISearchProvider`  
`class ISearchProvider`  
_L7-12_
- L10 _public function_ `virtual ~ISearchProvider()`
- L11 _public prototype_ `virtual void Search(FSearchQueryPtr SearchQuery) = 0;`

### `Plugins/Editor/AssetSearch/Source/Public/SearchQuery.h` (Public)


#### struct `FSearchRecord`  
`struct FSearchRecord`  
_L9-27_
- L11 _public member_ `FString AssetName;`
- L12 _public member_ `FString AssetPath;`
- L13 _public member_ `FTopLevelAssetPath AssetClass;`
- L15 _public member_ `FString object_name;`
- L16 _public member_ `FString object_path;`
- L17 _public member_ `FString object_native_class;`
- L19 _public member_ `FString property_name;`
- L20 _public member_ `FString property_field;`
- L21 _public member_ `FString property_class;`
- L23 _public member_ `FString value_text;`
- L24 _public member_ `FString value_hidden;`
- L26 _public member_ `float Score;`

#### class `FSearchQuery`  
`class FSearchQuery : public TSharedFromThis<FSearchQuery, ESPMode::ThreadSafe>`  
_L29-71_
- inherits: `TSharedFromThis<FSearchQuery,ESPMode::ThreadSafe>`
- L32 _public typedef_ `typedef TFunction<void(TArray<FSearchRecord>&&)> ResultsCallbackFunction;`
- L34 _public function_ `FSearchQuery(FString InQueryText) : QueryText(InQueryText)`
- L39 _public member_ `const FString QueryText;`
- L41 _public function_ `void SetResultsCallback(ResultsCallbackFunction InCallback)`
- L47 _public function_ `void ClearResultsCallback()`
- L53 _public function_ `bool IsQueryStillImportant() const`
- L58 _public function_ `ResultsCallbackFunction GetResultsCallback() const`
- L69 _private member_ `ResultsCallbackFunction Callback;`
- L70 _private member_ `mutable FCriticalSection CallbackCS;`

#### Free symbols / members of external scopes

- L73 _typedef_ `typedef TSharedPtr<FSearchQuery, ESPMode::ThreadSafe> FSearchQueryPtr;`
- L74 _typedef_ `typedef TWeakPtr<FSearchQuery, ESPMode::ThreadSafe> FSearchQueryWeakPtr;`

### `Plugins/Editor/AssetSearch/Source/Public/SearchSerializer.h` (Public)


#### class `FSearchSerializer`  
`class FSearchSerializer : public FNoncopyable`  
_L12-79_
- inherits: `FNoncopyable`
- L15 _public prototype_ `FSearchSerializer(const FAssetData& InAsset, FArchive& InAr);`
- L16 _public prototype_ `FSearchSerializer(const FAssetData& InAsset, FString* const Stream);`
- L17 _public prototype_ `~FSearchSerializer();`
- L19 _public prototype_ `static int32 GetVersion();`
- L21 _public prototype_ `bool IndexAsset(const UObject* InAsset, const TMap<FName, TUniquePtr<IAssetIndexer>>& Indexers);`
- L23 _public prototype_ `void BeginIndexer(const IAssetIndexer* InIndexer);`
- L27 _public prototype_ `void BeginIndexingObject(const UObject* InObject, const FString& InFriendlyName);`
- L28 _public prototype_ `void BeginIndexingObject(const UObject* InObject, const FText& InFriendlyName);`
- L29 _public prototype_ `void EndIndexingObject();`
- L33 _public prototype_ `void IndexProperty(const FString& InName, const FName& InValue);`
- L34 _public prototype_ `void IndexProperty(const FString& InName, const FText& InValue);`
- L35 _public prototype_ `void IndexProperty(const FString& InName, const FString& InValue);`
- L36 _public prototype_ `void IndexProperty(const UClass* InPropertyClass, const FString& InName, const FString& InValue);`
- L37 _public prototype_ `void IndexProperty(const UClass* InPropertyClass, const FString& InName, const FText& InValue);`
- L38 _public prototype_ `void IndexProperty(const FProperty* InProperty, const FString& InValue);`
- L42 _public prototype_ `void IndexNestedAsset(UObject* InNestedAsset);`
- L46 _public prototype_ `void EndIndexer();`
- L49 _private prototype_ `void IndexProperty(const FFieldClass& InPropertyFieldClass, const UClass* PropertyClass, const FString& InName, const FString& InValue);`
- L52 _private prototype_ `void Initialize(const FAssetData& InAsset);`
- L55 _private member_ `TSharedRef< TJsonWriter<TCHAR, TCondensedJsonPrintPolicy<TCHAR> > > JsonWriter;`
- L57 _private member_ `FAssetData AssetData;`
- L59 _private member_ `const IAssetIndexer* CurrentIndexer = nullptr;`
- L61 _private member_ `const UObject* CurrentObject = nullptr;`
- L62 _private member_ `FString CurrentObjectName;`
- L63 _private member_ `FString CurrentObjectClass;`
- L64 _private member_ `FString CurrentObjectPath;`
- L76 _private member_ `TArray<FIndexedValue> Values;`
- L78 _private member_ `TArray<UObject*> NestedAssets;`

#### struct `FSearchSerializer::FIndexedValue`  
`struct FIndexedValue`  
_L66-74_
- L68 _public member_ `FString PropertyName;`
- L69 _public member_ `FString PropertyFieldClass;`
- L70 _public member_ `FName PropertyClass;`
- L72 _public member_ `FString Text;`
- L73 _public member_ `FString HiddenText;`

### `Plugins/Editor/AssetSearch/Source/Public/Utility/IndexerUtilities.h` (Public)


#### class `FIndexerUtilities`  
`class FIndexerUtilities`  
_L15-20_
- L18 _public prototype_ `static void IterateIndexableProperties(const UObject* InObject, TFunctionRef<void(const FProperty* , const FString& )> Callback);`
- L19 _public prototype_ `static void IterateIndexableProperties(const UStruct* InStruct, const void* InStructValue, TFunctionRef<void(const FProperty* , const FString& )> Callback);`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API ASSETSEARCH_API`
