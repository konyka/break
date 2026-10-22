# Runtime / RuntimeAssetCache

- module root: `Source/Runtime/RuntimeAssetCache`
- headers: 13; symbols: 196
- symbol kinds: class=14, delegate=10, function=48, member=37, prototype=86, struct=1
- PrivateDependencyModuleNames: Core, CoreUObject, Engine

### `Source/Runtime/RuntimeAssetCache/Private/RuntimeAssetCache.h` (Private)


#### class `FRuntimeAssetCache`  
`class FRuntimeAssetCache final : public FRuntimeAssetCacheInterface`  
_L27-76_
- inherits: `FRuntimeAssetCacheInterface`
- desc: Concrete class implementing FRuntimeAssetCacheInterface.
- L31 _public prototype_ `virtual FVoidPtrParam GetSynchronous(IRuntimeAssetCacheBuilder* CacheBuilder) override;`
- L32 _public prototype_ `virtual int32 GetAsynchronous(IRuntimeAssetCacheBuilder* CacheBuilder, const FOnRuntimeAssetCacheAsyncComplete& OnCompletionDelegate) override;`
- L33 _public prototype_ `virtual int32 GetAsynchronous(IRuntimeAssetCacheBuilder* CacheBuilder) override;`
- L34 _public prototype_ `virtual int32 GetCacheSize(FName Bucket) const override;`
- L35 _public prototype_ `virtual bool ClearCache() override;`
- L36 _public prototype_ `virtual bool ClearCache(FName Bucket) override;`
- L37 _public prototype_ `virtual void WaitAsynchronousCompletion(int32 Handle) override;`
- L38 _public prototype_ `virtual FVoidPtrParam GetAsynchronousResults(int32 Handle) override;`
- L39 _public prototype_ `virtual bool PollAsynchronousCompletion(int32 Handle) override;`
- L40 _public prototype_ `virtual void AddToAsyncCompletionCounter(int32 Addend) override;`
- L41 _public prototype_ `virtual void Tick() override;`
- L46 _public prototype_ `FRuntimeAssetCache();` — Constructor
- L49 _public prototype_ `~FRuntimeAssetCache();` — Destructor
- L57 _private function_ `int32 GetNextHandle()` — Generates next handle of async worker. @return Worker handle.
- L63 _private member_ `TMap<FName, FRuntimeAssetCacheBucket*> Buckets;` — Map of bucket names to their configs.
- L66 _private member_ `TMap<int32, FAsyncTask<FRuntimeAssetCacheAsyncWorker>*> PendingTasks;` — Map of handle to pending task
- L69 _private member_ `FCriticalSection SynchronizationObject;` — Pending tasks synchronization object.
- L72 _private member_ `FThreadSafeCounter CurrentAsyncTaskHandle;` — Counter used to generate worker handles.
- L75 _private member_ `FThreadSafeCounter PendingTasksCounter;` — Number of pending tasks.

#### Free symbols / members of external scopes

- L16 _delegate_ `DECLARE_FLOAT_ACCUMULATOR_STAT_EXTERN(TEXT("RAC ASync Wait Time"), STAT_RAC_ASyncWaitTime` — Stats.

### `Source/Runtime/RuntimeAssetCache/Private/RuntimeAssetCacheAsyncWorker.h` (Private)


#### class `FRuntimeAssetCacheAsyncWorker`  
`class FRuntimeAssetCacheAsyncWorker : public FNonAbandonableTask`  
_L31-133_
- inherits: `FNonAbandonableTask`
- desc: Worker to retrieve entry from cache or build it in case of cache miss.
- L35 _public prototype_ `FRuntimeAssetCacheAsyncWorker(IRuntimeAssetCacheBuilder* InCacheBuilder, TMap<FName, FRuntimeAssetCacheBucket*>* InBuckets, int32 InHandle, const FOnRuntimeAssetCacheAsyncComplete& InCompletionCallback);` — Constructor
- L38 _public prototype_ `void DoWork();` — Async task interface implementation.
- L39 _public prototype_ `TStatId GetStatId() const;`
- L43 _public function_ `void* GetData()` — Gets serialized cache data.
- L49 _public function_ `int64 GetDataSize()` — Gets serialized cache data size in bytes.
- L55 _public function_ `FVoidPtrParam GetDataAndSize()` — Gets serialized cache data and data size.
- L63 _public prototype_ `void FireCompletionDelegate();` — Fires completion delegate only if it wasn't fired earlier.
- L70 _private function_ `bool FiredCompletionDelegate() const` — Checks if task already fired completion delegate. @return true if already fired completion delegate, false otherwise.
- L80 _private prototype_ `static FString SanitizeCacheKey(const TCHAR* CacheKey);` — Static function to make sure a cache key contains only legal characters by using an escape. @param CacheKey Cache key to sanitize @return Sanitized cache key
- L89 _private prototype_ `static FString BuildCacheKey(const TCHAR* VersionString, const TCHAR* PluginSpecificCacheKeySuffix);` — Static function to build a cache key out of the plugin name, versions and plugin specific info @param PluginName Name of the runtime asset data type @param VersionString Version string of the runtime asset data @param PluginSpecificCacheKeySuffix Whatever is needed to uniquely identify the specific cache entry. @return Assembled cache key
- L96 _private prototype_ `static FString BuildCacheKey(IRuntimeAssetCacheBuilder* CacheBuilder);` — Static function to build a cache key out of the CacheBuilder. @param CacheBuilder Builder to create key from. @return Assembled cache key
- L103 _private prototype_ `void FreeCacheSpace(FName Bucket, int32 SizeOfSpaceToFreeInBytes);` — Removes entries from cache until given number of bytes are freed (or more). @param Bucket Bucket to clean up. @param SizeOfSpaceToFreeInBytes Number of bytes to free (or more).
- L106 _private member_ `IRuntimeAssetCacheBuilder* CacheBuilder;` — Cache builder to create cache entry in case of cache miss.
- L109 _private member_ `void* Data;` — Data to return to caller.
- L112 _private member_ `int64 DataSize;` — Size of data returned to caller
- L115 _private member_ `TMap<FName, FRuntimeAssetCacheBucket*>* Buckets;` — Reference to map of bucket names to their descriptions.
- L121 _private member_ `bool bEntryRetrieved;` — True if successfully retrieved a cache entry. Can be false only when CacheBuilder returns false or no CacheBuilder was provided.
- L124 _private member_ `FOnRuntimeAssetCacheAsyncComplete CompletionCallback;` — Completion delegate called when cache entry is retrieved.
- L127 _private member_ `int32 Handle;` — Handle uniquely identifying this worker thread.
- L130 _private member_ `bool bFiredCompletionDelegate;` — True if completion delegate was already fired, false otherwise.
- L132 _private member_ `UClass* Class;`

#### Free symbols / members of external scopes

- L18 _delegate_ `DECLARE_DWORD_ACCUMULATOR_STAT_EXTERN(TEXT("RAC Num Build"), STAT_RAC_NumBuilds, STAT` — Stats
- L19 _delegate_ `DECLARE_DWORD_ACCUMULATOR_STAT_EXTERN(TEXT("RAC Num Cache Hits"), STAT_RAC_NumCacheHits,`
- L20 _delegate_ `DECLARE_DWORD_ACCUMULATOR_STAT_EXTERN(TEXT("RAC Num Retrieve fails"), STAT_RAC_NumFa`
- L21 _delegate_ `DECLARE_DWORD_ACCUMULATOR_STAT_EXTERN(TEXT("RAC Num Gets"), STAT_RAC_NumGets, STATG`
- L22 _delegate_ `DECLARE_DWORD_ACCUMULATOR_STAT_EXTERN(TEXT("RAC Num Puts"), STAT_RAC_NumPuts, STATG`

### `Source/Runtime/RuntimeAssetCache/Private/RuntimeAssetCacheBackend.h` (Private)


#### class `FRuntimeAssetCacheBackend`  
`class FRuntimeAssetCacheBackend : public FNoncopyable`  
_L20-117_
- inherits: `FNoncopyable`
- desc: Facade for runtime asset cache backend. Currently only file system backend is available.
- L27 _public function_ `static FRuntimeAssetCacheBackend& Get()` — Singleton getter. @return Backend implementation.
- L40 _public prototype_ `FCacheEntryMetadata* GetCachedData(FName Bucket, const TCHAR* CacheKey, void*& OutData, int64& OutDataSize);` — Retrieves cached entry. @param Bucket Bucket to query. @param CacheKey Key of cache entry to retrieve. @param OutData Serialized cache entry. Emptied if entry not found. @return Metadata descriptor of cache entry on cache hit, nullptr otherwise.
- L50 _public prototype_ `bool PutCachedData(FName Bucket, const TCHAR* CacheKey, void* InData, int64 InDataSize, FCacheEntryMetadata* Metadata);` — Puts entry to cache. @param Bucket Bucket to put entry to. @param CacheKey Key of cache entry to retrieve. @param InData Serialized cache entry. @param Metadata descriptor of cache entry. @return True if successfully put entry into cache.
- L58 _public prototype_ `virtual bool RemoveCacheEntry(FName Bucket, const TCHAR* CacheKey) = 0;` — Removes entry from cache. @param Bucket Bucket to remove entry from. @param CacheKey Key of cache entry to remove. @return True if successfully removed entry from cache.
- L64 _public prototype_ `virtual bool ClearCache() = 0;` — Removes all entries from cache. @return True if successfully removed all entries from cache.
- L71 _public prototype_ `virtual bool ClearCache(FName Bucket) = 0;` — Removes all entries from given bucket. @param Bucket Bucket to clean. @return True if successfully removed all entries from cache.
- L79 _public prototype_ `virtual FRuntimeAssetCacheBucket* PreLoadBucket(FName BucketName, int32 BucketSize) = 0;` — Preloads cache metadata and size for given bucket. @param BucketName Name of bucket to preload. @param BucketSize Size of bucket to preload. @return Preloaded bucket on success, nullptr otherwise.
- L85 _protected function_ `virtual ~FRuntimeAssetCacheBackend()` — Virtual destructor.
- L93 _protected prototype_ `virtual FArchive* CreateReadArchive(FName Bucket, const TCHAR* CacheKey) = 0;` — Creates archive to read data from. @param Bucket Bucket containing cache entry. @param CacheKey Key to cache entry. @return Archive storing data.
- L101 _protected prototype_ `virtual FArchive* CreateWriteArchive(FName Bucket, const TCHAR* CacheKey) = 0;` — Creates archive to write data into. @param Bucket Bucket containing cache entry. @param CacheKey Key to cache entry. @return Archive storing data.
- L108 _protected prototype_ `FCacheEntryMetadata* PreloadMetadata(FArchive* Ar);` — Preloads metadata from archive. @param Ar Archive to load metadata from @return Metadata.
- L115 _private prototype_ `static FRuntimeAssetCacheBackend* CreateBackend();` — Factory method to create actual backend implementation. @return Cache backend.

### `Source/Runtime/RuntimeAssetCache/Private/RuntimeAssetCacheBucket.h` (Private)


#### class `FRuntimeAssetCacheBucket`  
`class FRuntimeAssetCacheBucket`  
_L19-120_
- desc: Holds data about cache entries.
- L23 _public function_ `FRuntimeAssetCacheBucket() : Size(DefaultBucketSize) , CurrentSize(0)` — Default constructor.
- L32 _public function_ `FRuntimeAssetCacheBucket(int32 InSize) : Size(InSize) , CurrentSize(0)` — Constructor @param InSize Size of bucket in bytes.
- L38 _public prototype_ `~FRuntimeAssetCacheBucket();` — Destructor.
- L41 _public function_ `int32 GetSize() const` — Gets size in bytes of the bucket.
- L49 _public prototype_ `void Reset();` — Cleans up all metadata entries.
- L56 _public prototype_ `FCacheEntryMetadata* GetMetadata(const FString& Key);` — Gets metadata entry for given key. @param Key Key to get metadata for. @return Metadata for given key. Default value if Key is not found.
- L63 _public prototype_ `void RemoveMetadataEntry(const FString& Key, bool bBuildFailed = false);` — Removes metadata entry for given key. @param Key Key to remove metadata for. @param bBuildFailed Indicates that building cache entry failed and some checks should be skipped.
- L71 _public prototype_ `void AddMetadataEntry(const FString& Key, FCacheEntryMetadata* Value, bool bUpdateSize);` — Adds metadata entry for given key. @param Key Key to add metadata for. @param Value Metadata to add. If there is an entry for given key, it gets overwritten. @param bUpdateSize If true, function will update current size of bucket. Otherwise, it's up to caller.
- L76 _public function_ `int32 GetCurrentSize()` — Gets number of bytes used in cache so far.
- L86 _public function_ `void AddToCurrentSize(int32 Value)` — Adds to number of bytes used in cache so far. @param Value Number of bytes to add. Can be negative.
- L97 _public prototype_ `FCacheEntryMetadata* GetOldestEntry();` — Gets oldest metadata entry in cache. @return Oldest metadata entry.
- L100 _public member_ `static const int32 DefaultBucketSize;` — Default size of bucket in case it wasn't specified in config.
- L104 _private member_ `TMap<FString, FCacheEntryMetadata*> CacheMetadata;` — Map of cache keys to cache entries metadata.
- L107 _private member_ `FCriticalSection MetadataCriticalSection;` — Guard for modifying CacheMetadata (adding/removing elements). Each element has individual guard for modifying it.
- L110 _private member_ `int32 Size;` — Cache bucket size in bytes.
- L113 _private member_ `int32 CurrentSize;` — Used bucket size in bytes.
- L116 _private member_ `FCriticalSection CurrentSizeCriticalSection;` — Guard for modifying current size from multiple threads.

### `Source/Runtime/RuntimeAssetCache/Private/RuntimeAssetCacheBucketScopeLock.h` (Private)


#### class `FRuntimeAssetCacheBucketScopeLock`  
`class FRuntimeAssetCacheBucketScopeLock`  
_L11-28_
- desc: Scope lock guarding RuntimeAssetCache bucket metadata critical section.
- L14 _public function_ `FRuntimeAssetCacheBucketScopeLock(FRuntimeAssetCacheBucket& InBucket) : Bucket(InBucket)`
- L20 _public function_ `~FRuntimeAssetCacheBucketScopeLock()`
- L27 _private member_ `FRuntimeAssetCacheBucket& Bucket;` — Bucket to protect.

### `Source/Runtime/RuntimeAssetCache/Private/RuntimeAssetCacheEntryMetadata.h` (Private)


#### class `FCacheEntryMetadata`  
`class FCacheEntryMetadata`  
_L15-90_
- desc: Cache entry metadata.
- L18 _public function_ `FCacheEntryMetadata(const FDateTime& InLastAccessTime , int32 InCachedAssetSize , int32 InCachedAssetVersion , FName InName) : LastAccessTime(InLastAccessTime) , CachedAssetSize(InCachedAssetSize) , CachedAssetVersion(InCachedAssetVersion) , Name(InName) , bIsBuilding(true)`
- L29 _public function_ `FCacheEntryMetadata() : LastAccessTime(FDateTime::Now()) , CachedAssetSize(0) , CachedAssetVersion(0) , Name(NAME_None) , bIsBuilding(false)`
- L37 _public function_ `int32 GetCachedAssetVersion() const`
- L42 _public function_ `void SetCachedAssetVersion(int32 Version)`
- L47 _public function_ `int32 GetCachedAssetSize() const`
- L52 _public function_ `void SetCachedAssetSize(int64 Value)`
- L57 _public function_ `void SetLastAccessTime(FDateTime Value)`
- L62 _public function_ `FDateTime GetLastAccessTime() const`
- L67 _public function_ `FName GetName() const`
- L72 _public function_ `bool IsBuilding() const`
- L77 _public function_ `void FinishBuilding()`
- L85 _private member_ `FDateTime LastAccessTime;`
- L86 _private member_ `int64 CachedAssetSize;`
- L87 _private member_ `int32 CachedAssetVersion;`
- L88 _private member_ `FName Name;`
- L89 _private member_ `FThreadSafeBool bIsBuilding;`

#### Free symbols / members of external scopes

- L92 _prototype_ `FArchive& operator<<(FArchive& Ar, FCacheEntryMetadata& Metadata);`

### `Source/Runtime/RuntimeAssetCache/Private/RuntimeAssetCacheFilesystemBackend.h` (Private)


#### class `FRuntimeAssetCacheFilesystemBackend`  
`class FRuntimeAssetCacheFilesystemBackend : public FRuntimeAssetCacheBackend`  
_L16-35_
- inherits: `FRuntimeAssetCacheBackend`
- desc: File system implementation of runtime asset cache backend.
- L19 _public prototype_ `FRuntimeAssetCacheFilesystemBackend();`
- L22 _public prototype_ `virtual bool RemoveCacheEntry(FName Bucket, const TCHAR* CacheKey) override;` — FRuntimeAssetCacheBackend interface implementation.
- L23 _public prototype_ `virtual bool ClearCache() override;`
- L24 _public prototype_ `virtual bool ClearCache(FName Bucket) override;`
- L25 _public prototype_ `virtual FRuntimeAssetCacheBucket* PreLoadBucket(FName BucketName, int32 BucketSize) override;`
- L27 _protected prototype_ `virtual FArchive* CreateReadArchive(FName Bucket, const TCHAR* CacheKey) override;`
- L28 _protected prototype_ `virtual FArchive* CreateWriteArchive(FName Bucket, const TCHAR* CacheKey) override;`
- L34 _private member_ `FString PathToRAC;` — File system path to runtime asset cache.

### `Source/Runtime/RuntimeAssetCache/Private/RuntimeAssetCachePrivate.h` (Private)


#### Free symbols / members of external scopes

- L10 _delegate_ `DECLARE_STATS_GROUP(TEXT("RAC"), STATGROUP_RAC, STATCAT_Advance` — Stats
- L13 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(RuntimeAssetCache, Log, All);` — Logs
- L13 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(RuntimeAssetCache, Log, All);` — Logs

### `Source/Runtime/RuntimeAssetCache/Public/RuntimeAssetCacheBPHooks.h` (Public)


#### class `URuntimeAssetCacheBPHooks`  
`class URuntimeAssetCacheBPHooks : public UBlueprintFunctionLibrary`  
_L23-48_
- reflection: `UCLASS()`
- inherits: `UBlueprintFunctionLibrary`
- L29 _public prototype_ `static FVoidPtrParam GetSynchronous(TScriptInterface<IRuntimeAssetCacheBuilder> CacheBuilder);` — `UFUNCTION(BlueprintCallable, Category = RuntimeAssetCache)`
- L32 _public prototype_ `static int32 GetAsynchronous(TScriptInterface<IRuntimeAssetCacheBuilder> CacheBuilder, const FOnRuntimeAssetCacheAsyncComplete& CompletionDelegate);` — `UFUNCTION(BlueprintCallable, Category = RuntimeAssetCache)`
- L35 _public prototype_ `static int32 GetCacheSize(FName Bucket);` — `UFUNCTION(BlueprintCallable, Category = RuntimeAssetCache)`
- L38 _public prototype_ `static bool ClearCache(FName Bucket);` — `UFUNCTION(BlueprintCallable, Category = RuntimeAssetCache)`
- L41 _public prototype_ `static void WaitAsynchronousCompletion(int32 Handle);` — `UFUNCTION(BlueprintCallable, Category = RuntimeAssetCache)`
- L44 _public prototype_ `static FVoidPtrParam GetAsynchronousResults(int32 Handle);` — `UFUNCTION(BlueprintCallable, Category = RuntimeAssetCache)`
- L47 _public prototype_ `static bool PollAsynchronousCompletion(int32 Handle);` — `UFUNCTION(BlueprintCallable, Category = RuntimeAssetCache)`

### `Source/Runtime/RuntimeAssetCache/Public/RuntimeAssetCacheBuilders.h` (Public)


#### class `URuntimeAssetCacheBuilder_ObjectBase`  
`class URuntimeAssetCacheBuilder_ObjectBase : public UObject, public IRuntimeAssetCacheBuilder`  
_L24-168_
- reflection: `UCLASS(BlueprintType)`
- inherits: `UObject,IRuntimeAssetCacheBuilder`
- L28 _public function_ `virtual void PostInitProperties() override`
- L35 _public function_ `virtual const TCHAR* GetBucketConfigName() const override`
- L40 _public function_ `virtual const TCHAR* GetBuilderName() const override`
- L45 _public function_ `virtual FString GetAssetUniqueName() const override`
- L50 _public function_ `virtual bool IsBuildThreadSafe() const`
- L55 _public function_ `virtual bool ShouldBuildAsynchronously() const override`
- L60 _public function_ `virtual int32 GetAssetVersion() override`
- L68 _public function_ `virtual void SerializeAsset(FArchive& Ar)` — Override and make a custom serialization function to save/load the important UObject data to disk
- L76 _public function_ `virtual int64 GetSerializedDataSizeEstimate()` — Estimate the size (in bytes) of the Data saved in SerializeData. This makes the buffer memory usage is more efficient. This is not necessary. However, the closer the estimate is to the actual size the more efficient the memory allocations will be.
- L81 _public prototype_ `FVoidPtrParam Build() override;`
- L89 _public prototype_ `void GetFromCacheAsync(const FOnAssetCacheComplete& OnComplete);` — `UFUNCTION(BlueprintCallable, Category = RuntimeAssetCache)` — Call this to get the asset named AssetName from the runtime asset cache. If the asset does not exist on disk, then OnAssetCacheMiss will be called. Implement OnAssetCacheMiss in order to create the asset that you want cached.
- L92 _public prototype_ `void GetFromCacheAsyncComplete(int32 Handle, FVoidPtrParam DataPtr);` — `UFUNCTION()`
- L97 _public function_ `virtual void OnAssetPreLoad()` — Make sure Asset is set up and ready to be loaded into
- L102 _public function_ `virtual void OnAssetPostLoad()` — Perform any specific init functions after load
- L110 _public prototype_ `void OnAssetCacheMiss();` — `UFUNCTION(BlueprintNativeEvent, Category = RuntimeAssetCache)` — When you get OnAssetCacheMiss you need to load/create the asset that is missing. Call SaveNewAssetToCache after you're finished creating the asset to save it back into the cache for next time. This will then trigger OnAssetCacheComplete like normal, so you don't need additional code to handle it.
- L111 _public function_ `virtual void OnAssetCacheMiss_Implementation()`
- L126 _public prototype_ `void SaveNewAssetToCache(UObject* NewAsset);` — `UFUNCTION(BlueprintCallable, Category = RuntimeAssetCache)` — Call SaveNewAssetToCache to save an asset back into the cache for next time. This will then trigger OnAssetCacheComplete like normal, so you don't need additional code to handle it.
- L131 _public prototype_ `void SetAsset(UObject* NewAsset);` — This merely sets Asset and calls OnSetAsset. Use SaveNewAssetToCache to actually cache a new asset.
- L139 _public function_ `virtual void OnSetAsset(UObject* NewAsset)` — Please override in your child class to provide easy access to the Asset. Declare a specific UObject* variable in your subclass to make it easy for BP nodes to access, e.g. UPROPERTY() UTexture* Texture; This function will always get called when the Asset changes So set your specific variable here, e.g.  Texture = Cast<UTexture2D>(NewAsset);
- L145 _public function_ `virtual void Cleanup()`
- L155 _public member_ `int32 AssetVersion;` — `UPROPERTY(BlueprintReadWrite, Category = RuntimeAssetCache, meta = (ExposeOnSpawn = "true"))` — The asset version. Changing this will force a new version of the asset to get cached.
- L159 _public member_ `FString AssetName;` — `UPROPERTY(BlueprintReadWrite, Category = RuntimeAssetCache, meta = (ExposeOnSpawn = "true"))` — The name of the asset. This should be unique per asset, and is used to look it up from the cache. This should be something that can be known without having Asset in memory (so we can look it up in the cache).
- L161 _public member_ `int32 CacheHandle;`
- L164 _private member_ `UObject* Asset;`
- L165 _private member_ `int32 bProcessedCacheMiss : 1;`
- L166 _private member_ `FOnRuntimeAssetCacheAsyncComplete GetFromCacheAsyncCompleteDelegate;`
- L167 _private member_ `FOnAssetCacheComplete OnAssetCacheComplete;`

#### class `UExampleTextureCacheBuilder`  
`class UExampleTextureCacheBuilder : public URuntimeAssetCacheBuilder_ObjectBase`  
_L171-190_
- reflection: `UCLASS(BlueprintType)`
- inherits: `URuntimeAssetCacheBuilder_ObjectBase`
- L176 _public prototype_ `virtual void OnSetAsset(UObject* NewAsset);`
- L178 _public prototype_ `virtual void OnAssetCacheMiss_Implementation() override;`
- L180 _public prototype_ `virtual void SerializeAsset(FArchive& Ar) override;`
- L182 _public prototype_ `virtual void OnAssetPreLoad() override;`
- L184 _public prototype_ `virtual void OnAssetPostLoad() override;`
- L186 _public prototype_ `virtual int64 GetSerializedDataSizeEstimate() override;`
- L189 _public member_ `TObjectPtr<UTexture2D> Texture;` — `UPROPERTY(BlueprintReadOnly, Category = "Cache")`

#### Free symbols / members of external scopes

- L19 _delegate_ `DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnAssetCacheComplete, URuntimeAssetCacheBuilder_ObjectBase*, CachedAssetBuilder, bool, Success);`
- L19 _prototype_ `DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnAssetCacheComplete, URuntimeAssetCacheBuilder_ObjectBase*, CachedAssetBuilder, bool, Success);`

### `Source/Runtime/RuntimeAssetCache/Public/RuntimeAssetCacheInterface.h` (Public)


#### struct `FVoidPtrParam`  
`struct FVoidPtrParam`  
_L22-53_
- reflection: `USTRUCT(BlueprintType)`
- desc: Useful for passing around void* data and size
- L26 _public function_ `FVoidPtrParam(void* InData, int64 InDataSize) : Data(InData) , DataSize(InDataSize)`
- L31 _public function_ `FVoidPtrParam() : Data(nullptr) , DataSize(0)`
- L36 _public function_ `static FVoidPtrParam NullPtr()`
- L41 _public function_ `inline bool operator!() const`
- L46 _public function_ `inline explicit operator bool() const`
- L51 _public member_ `void* Data;`
- L52 _public member_ `int64 DataSize;`

#### class `FRuntimeAssetCacheInterface`  
`class FRuntimeAssetCacheInterface`  
_L66-147_
- desc: Interface for the Runtime Asset Cache. Cache is split into buckets to cache various assets separately. Bucket names and maximum sizes are configure via Engine.ini config file using the following syntax [RuntimeAssetCache] +BucketConfigs=(Name="<Plugin name>", Size=<Maximum bucket size in bytes>) This API is fully thread safe.
- L69 _public function_ `virtual ~FRuntimeAssetCacheInterface()`
- L78 _public prototype_ `virtual FVoidPtrParam GetSynchronous(IRuntimeAssetCacheBuilder* CacheBuilder) = 0;` — Synchronously gets value from cache. If value is not found, builds entry using CacheBuilder and updates cache. @param CacheBuilder Builder to produce cache key and in the event of a miss. @return Pointer to retrieved cache entry, nullptr on fail. Fail occurs only when - there's no entry in cache and CacheBuilder is nullptr or - CacheBuilder returned nullptr
- L86 _public prototype_ `virtual int32 GetAsynchronous(IRuntimeAssetCacheBuilder* CacheBuilder, const FOnRuntimeAssetCacheAsyncComplete& OnCompletionDelegate) = 0;` — Asynchronously checks the cache. If value is not found, builds entry using CacheBuilder and updates cache. @param CacheBuilder Builder to produce cache key and in the event of a miss, return the data. @param OnCompletionDelegate Delegate to call when cache is ready. Delegate is called on main thread. @return Handle to worker.
- L93 _public prototype_ `virtual int32 GetAsynchronous(IRuntimeAssetCacheBuilder* CacheBuilder) = 0;` — Asynchronously checks the cache. If value is not found, builds entry using CacheBuilder and updates cache. @param CacheBuilder Builder to produce cache key and in the event of a miss, return the data. @return Handle to worker.
- L100 _public prototype_ `virtual int32 GetCacheSize(FName Bucket) const = 0;` — Gets cache size. @param Bucket to check. @return Maximum allowed bucket size.
- L106 _public prototype_ `virtual bool ClearCache() = 0;` — Removes all cache entries. @return true if cache was successfully cleaned.
- L113 _public prototype_ `virtual bool ClearCache(FName Bucket) = 0;` — Removes all cache from given bucket. @param Bucket Bucket to clean. @return true if cache was successfully cleaned.
- L119 _public prototype_ `virtual void WaitAsynchronousCompletion(int32 Handle) = 0;` — Waits until worker finishes execution. @param Handle Worker handle to wait for.
- L128 _public prototype_ `virtual FVoidPtrParam GetAsynchronousResults(int32 Handle) = 0;` — Gets asynchronous query results. @param Handle Worker handle to check. @return Pointer to retrieved cache entry, nullptr on fail. Fail occurs only when - there's no entry in cache and CacheBuilder is nullptr or - CacheBuilder returned nullptr
- L135 _public prototype_ `virtual bool PollAsynchronousCompletion(int32 Handle) = 0;` — Checks if worker finished execution. @param Handle Worker handle to check. @return True if execution finished, false otherwise.
- L141 _public prototype_ `virtual void AddToAsyncCompletionCounter(int32 Addend) = 0;` — Adds a number from the thread safe counter which tracks outstanding async requests. This is used to ensure everything is complete prior to shutdown. @param Value to add to counter. Can be negative.
- L146 _public prototype_ `virtual void Tick() = 0;` — Ticks async thread.

#### Free symbols / members of external scopes

- L57 _delegate_ `DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnRuntimeAssetCacheAsyncComplete, int32, Handle, FVoidPtrParam, Data);` — Delegates.
- L57 _prototype_ `DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnRuntimeAssetCacheAsyncComplete, int32, Handle, FVoidPtrParam, Data);` — Delegates.

### `Source/Runtime/RuntimeAssetCache/Public/RuntimeAssetCacheModule.h` (Public)


#### class `FRuntimeAssetCacheModuleInterface`  
`class FRuntimeAssetCacheModuleInterface : public IModuleInterface`  
_L18-26_
- inherits: `IModuleInterface`
- desc: Module for the RuntimeAssetCache.
- L25 _public prototype_ `virtual FRuntimeAssetCacheInterface& GetRuntimeAssetCache() = 0;` — Gets runtime asset cache. @return Runtime asset cache.

#### Free symbols / members of external scopes

- L13 _prototype_ `FRuntimeAssetCacheInterface& GetRuntimeAssetCache();`

### `Source/Runtime/RuntimeAssetCache/Public/RuntimeAssetCachePluginInterface.h` (Public)


#### class `URuntimeAssetCacheBuilder`  
`class URuntimeAssetCacheBuilder : public UInterface`  
_L15-18_
- reflection: `UINTERFACE()`
- inherits: `UInterface`

#### class `IRuntimeAssetCacheBuilder`  
`class IRuntimeAssetCacheBuilder`  
_L24-93_
- desc: Interface for runtime asset cache cache builders. This API will be called concurrently.
- L34 _public prototype_ `virtual const TCHAR* GetBucketConfigName() const = 0;` — Get the builder type name. This is used to categorize cached data to buckets. @return Type name of builder.
- L40 _public prototype_ `virtual const TCHAR* GetBuilderName() const = 0;` — Get the name of cache builder, this is used as part of the cache key. @return Name of cache builder
- L46 _public prototype_ `virtual FString GetAssetUniqueName() const = 0;` — Returns the name uniquely describing the asset. @return Asset unique name.
- L52 _public prototype_ `virtual FVoidPtrParam Build() = 0;` — Does the work of creating serialized cache entry. @return Pointer to contiguous memory block with serialized cache entry on success, nullptr otherwise.
- L59 _public function_ `virtual void SerializeData(FArchive& Ar, FVoidPtrParam InData)` — Serializes data into archive @param Ar Archive to serialize to. @param InData Data to serialize.
- L68 _public prototype_ `virtual int32 GetAssetVersion() = 0;` — Gets asset version to rebuild cache if cached asset is too old. @return Asset version.
- L74 _public function_ `virtual bool CachedAssetVersionIsUpToDate(int32 CachedAssetVersion)` — Check if the cached asset is up to date. If the current AssetVersion is greater than the cached AssetVersion, the cached asset will be re-built. @return Whether the cached asset is good (return true) or needs to be rebuilt (return false).
- L83 _public function_ `virtual bool ShouldBuildAsynchronously() const` — Gets whether Build function must be called asynchronously. @return true if Build should be called asynchronously, false otherwise.
- L92 _public prototype_ `virtual bool IsBuildThreadSafe() const = 0;` — Gets whether Build function is threadsafe @return true if Build is threadsafe, false otherwise.
