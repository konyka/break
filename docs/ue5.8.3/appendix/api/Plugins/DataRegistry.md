# Plugins / DataRegistry

- module root: `Plugins/Runtime/DataRegistry/Source/DataRegistry`
- headers: 11; symbols: 565
- symbol kinds: class=10, delegate=6, enum=12, enumerator=55, function=71, macro=7, member=116, prototype=260, struct=25, typedef=3
- PrivateDependencyModuleNames: UnrealEd
- PublicDependencyModuleNames: Core, CoreUObject, DeveloperSettings, Engine, GameplayTags

### `Plugins/Runtime/DataRegistry/Source/DataRegistry/Private/DataRegistryTypesPrivate.h` (Private)


#### struct `FDataRegistryBatchRequest`  
`struct FDataRegistryBatchRequest`  
_L13-29_
- desc: A multi-item cache request, will call callback when everything is done
- L16 _public member_ `FDataRegistryRequestId RequestId;` — Unique request id in cache
- L19 _public member_ `TArray<TPair<FDataRegistryId, FDataRegistryLookup> > RequestedItems;` — Array of id->resolved items requested
- L22 _public member_ `TArray<FDataRegistryLookup> RemainingAcquires;` — Ones left to process
- L25 _public member_ `FDataRegistryBatchAcquireCallback Callback;` — Callback when all are acquired
- L28 _public member_ `EDataRegistryAcquireStatus BatchStatus = EDataRegistryAcquireStatus::NotStarted;` — Worst result seen so far

#### struct `FCachedDataRegistryRequest`  
`struct FCachedDataRegistryRequest`  
_L32-42_
- desc: Info for a specific request for a cached item
- L35 _public member_ `FDataRegistryId RequestedId;` — Original registry id that was requested
- L38 _public member_ `FDataRegistryItemAcquiredCallback Callback;` — Callback to call on completion of request
- L41 _public member_ `FDataRegistryRequestId BatchId;` — Batch request that started this

#### struct `FCachedDataRegistryItem`  
`struct FCachedDataRegistryItem`  
_L45-90_
- desc: Cached information for a single data item
- L47 _public prototype_ `~FCachedDataRegistryItem();`
- L50 _public member_ `FDataRegistryLookup LookupKey;` — What this was stored as, here for cross referencing
- L53 _public member_ `EDataRegistryAcquireStatus AcquireStatus = EDataRegistryAcquireStatus::NotStarted;` — Worst availability of all resources
- L56 _public member_ `int32 AcquireLookupIndex = -1;` — What source index it is currently checking, if the acquire is a success this will be the source it found it in
- L59 _public member_ `uint8* ItemMemory = nullptr;` — Allocated instance of item struct
- L62 _public member_ `TWeakObjectPtr<UDataRegistrySource> ItemSource;` — What source this cached data came from
- L65 _public member_ `TSharedPtr<FStreamableHandle> ResourceHandle;` — Handle to assets async loaded as part of loading item
- L68 _public member_ `EDataRegistryAvailability ResourceAvailability = EDataRegistryAvailability::Unknown;` — Worst availability of all resources
- L71 _public member_ `TArray<FCachedDataRegistryRequest> ActiveRequests;` — List of active requests
- L74 _public member_ `float LastAccessTime;` — Time this was last accessed
- L77 _public prototype_ `float GetRelevancy(const FDataRegistryCachePolicy& CachePolicy, float CurrentTime) const;` — Returns a relevancy score based on time/future parameters. <= 0 means always drop, >= 1 means always keep
- L80 _public prototype_ `const UScriptStruct* GetItemStruct() const;` — Returns the struct used for item memory
- L83 _public prototype_ `void ClearItemMemory();` — Resets the item memory and nulls pointer
- L86 _public prototype_ `static uint8* AllocateItemMemory(const UScriptStruct* ItemStruct);` — Allocate struct that will eventually be stored in this cache
- L89 _public prototype_ `static void FreeItemMemory(const UScriptStruct* ItemStruct, uint8* ItemMemory);` — Allocate struct that will eventually be stored in this cache

#### struct `FDataRegistryCache`  
`struct FDataRegistryCache`  
_L93-124_
- desc: Structure for entire cache, here to avoid exposing publicly
- L96 _public member_ `TMap<FDataRegistryLookup, TUniquePtr<FCachedDataRegistryItem>> LookupCache;` — Cached data, this is stored for a resolved lookup based on request context
- L99 _public member_ `TSortedMap<FDataRegistryRequestId, TUniquePtr<FDataRegistryBatchRequest>> BatchRequests;` — Active batch requests
- L102 _public member_ `int32 CurrentCacheVersion = 0;` — Current Cache version, modified when anything is changed
- L105 _public prototype_ `FCachedDataRegistryItem* GetCacheEntry(const FDataRegistryLookup& Lookup);` — Gets an active cache entry
- L108 _public prototype_ `FCachedDataRegistryItem& GetOrCreateCacheEntry(const FDataRegistryLookup& Lookup);` — Get or create a cache entry
- L111 _public prototype_ `bool RemoveCacheEntry(const FDataRegistryLookup& Lookup);` — Deletes a cache entry
- L114 _public prototype_ `FDataRegistryBatchRequest* GetBatchRequest(const FDataRegistryRequestId& RequestId);` — Gets an active request
- L117 _public prototype_ `FDataRegistryBatchRequest& CreateNewBatchRequest();` — Creates a new request with a new unique id
- L120 _public prototype_ `bool RemoveBatchRequest(const FDataRegistryRequestId& RequestId);` — Deletes a cache entry
- L123 _public prototype_ `void ClearCache(bool bClearRequests);` — Clears entire cache

### `Plugins/Runtime/DataRegistry/Source/DataRegistry/Public/DataRegistry.h` (Public)


#### class `UDataRegistry`  
`class UDataRegistry : public UObject`  
_L24-335_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject`
- desc: Defines a place to efficiently store and retrieve structure data, can be used as a wrapper around Data/Curve Tables or extended with other sources
- L29 _public prototype_ `UDataRegistry();`
- L30 _public prototype_ `virtual ~UDataRegistry();`
- L33 _public prototype_ `const UScriptStruct* GetItemStruct() const;` — Returns the struct used by this registry, everything returned will be this or a subclass
- L36 _public prototype_ `bool DoesItemStructMatchFilter(FName FilterStructName) const;` — Returns true if this registry struct inherits from a particular named struct
- L39 _public prototype_ `const FDataRegistryIdFormat& GetIdFormat() const;` — Gets the formatting for this Id
- L42 _public prototype_ `const FName GetRegistryType() const;` — Returns the name for type exposed by this registry
- L45 _public prototype_ `virtual FText GetRegistryDescription() const;` — Gets a human readable summary of registry, for UI usage
- L48 _public prototype_ `virtual bool IsInitialized() const;` — Returns true if this state has been initialized for use
- L51 _public prototype_ `virtual bool Initialize();` — Initialize for requests, called when subsystem starts up and should return true on success
- L54 _public prototype_ `virtual void Deinitialize();` — Disable access and restore to state before initialization, won't do anything if not initialized
- L57 _public prototype_ `virtual void ResetRuntimeState();` — Reset caches and state because gameplay finished due to PIE shutting down or the game registering a return to main menu, but stay initialized for future use
- L60 _public prototype_ `virtual void MarkRuntimeDirty();` — Marks this registry for needing a runtime refresh at next opportunity
- L63 _public prototype_ `virtual void RuntimeRefreshIfNeeded();` — Conditionally refresh the runtime state if needed
- L69 _public prototype_ `virtual EDataRegistryRegisterAssetResult RegisterSpecificAsset(const FAssetData& AssetData, int32 AssetPriority = 0);` — Attempt to register a specified asset with a source, returns an EDataRegistryRegisterAssetResult, indicating whether the asset was registered or not. Can be used to update priority for existing asset as well @return An EDataRegistryRegisterAssetResult that indicates if the asset Was Registered, whether it failed to register, or did not register because the asset was already registered.
- L72 _public prototype_ `virtual bool DidRegisterAssetResultCauseChange(EDataRegistryRegisterAssetResult RegisterAssetStatus) const;` — Use this to confirm that a DataRegistryRegisterAssetResult caused a change to the Data Registry. Virtual so that different registries can decide what may cause a change.
- L75 _public prototype_ `virtual bool UnregisterSpecificAsset(const FSoftObjectPath& AssetPath);` — Removes references to a specific asset, returns bool if it was removed
- L78 _public prototype_ `virtual int32 UnregisterAssetsWithPriority(int32 AssetPriority);` — Unregisters all previously registered assets in a specific registry with a specific priority, can be used as a batch reset. Returns number of assets unregistered
- L81 _public prototype_ `virtual EDataRegistryAvailability GetLowestAvailability() const;` — Returns the worst availability for anything stored in this registry, if this is Precached then this registry is a wrapper around already loaded data
- L84 _public prototype_ `const FDataRegistryCachePolicy& GetRuntimeCachePolicy() const;` — Gets the current general cache policy
- L87 _public prototype_ `void SetRuntimeCachePolicy(const FDataRegistryCachePolicy& NewPolicy);` — Sets the current cache policy, could cause items to get released
- L90 _public prototype_ `virtual void ApplyCachePolicy();` — Applies the cache policy, is called regularly but can be manually executed
- L93 _public prototype_ `virtual bool IsCacheGetResultValid(FDataRegistryCacheGetResult Result) const;` — Checks if a previous cached get is still valid
- L96 _public prototype_ `virtual FDataRegistryCacheGetResult GetCacheResultVersion() const;` — Returns the current cache version for a successful get, may change depending on stack-specific resolve settings
- L99 _public prototype_ `virtual void InvalidateCacheVersion();` — Bump the cache version from some external event like game-specific file loading
- L102 _public prototype_ `virtual FDataRegistryCacheVersionCallback& OnCacheVersionInvalidated();` — Accesses the delegate called when cache version changes
- L105 _public prototype_ `virtual bool ResolveDataRegistryId(FDataRegistryLookup& OutLookup, const FDataRegistryId& ItemId, const uint8** PrecachedDataPtr = nullptr) const;` — Resolves an item id into a specific source and unique id, this can remap the names using game-specific rules. PrecachedDataPtr will be set if it is precached by another system
- L108 _public prototype_ `virtual void GetPossibleRegistryIds(TArray<FDataRegistryId>& OutRegistryIds, bool bSortForDisplay = true) const;` — Fills in a list of all item ids provided by this registry, sorted for display
- L111 _public prototype_ `virtual bool AcquireItem(const FDataRegistryId& ItemId, FDataRegistryItemAcquiredCallback DelegateToCall);` — Start an async request for a single item
- L114 _public prototype_ `virtual bool BatchAcquireItems(const TArray<FDataRegistryId>& ItemIds, FDataRegistryBatchAcquireCallback DelegateToCall);` — Start an async request for multiple items
- L117 _public prototype_ `virtual FDataRegistryCacheGetResult GetCachedItemRawFromLookup(const uint8*& OutItemMemory, const UScriptStruct*& OutItemStruct, const FDataRegistryId& ItemId, const FDataRegistryLookup& Lookup) const;` — Finds the cached item using a resolved lookup, this can be useful after a load has happened to ensure you get the exact item requested
- L120 _public prototype_ `virtual FDataRegistryCacheGetResult GetCachedItemRaw(const uint8*& OutItemMemory, const UScriptStruct*& OutItemStruct, const FDataRegistryId& ItemId) const;` — Returns the raw cached data and struct type, useful for generic C++ calls
- L123 _public prototype_ `virtual FDataRegistryCacheGetResult GetCachedCurveRaw(const FRealCurve*& OutCurve, const FDataRegistryId& ItemId) const;` — Curve wrapper for get function
- L126 _public prototype_ `virtual UDataRegistrySource* LookupSource(FName& OutResolvedName, const FDataRegistryLookup& Lookup, int32 LookupIndex) const;` — Find the source associated with a lookup index
- L130 _public function_ `template <class T> const T* GetCachedItem(const FDataRegistryId& ItemId) const` — Finds the cached item, using the request context to handle remapping
- L150 _public function_ `template <class T> void ForEachCachedItem(const FString& ContextString, TFunctionRef<void(const FName& Name, const T& Item)> Predicate) const` — Method to run the given predicate on all items
- L180 _public function_ `template <class T> void GetAllItems(const TCHAR* ContextString, TArray<const T*>& Items) const` — Method to get all items in the registry
- L206 _public prototype_ `void GetItemNames(TArray<FName>& ItemNames) const;` — Method to get all item names in teh registry
- L212 _public prototype_ `virtual FDataRegistryCacheGetResult GetAllCachedItems(TMap<FDataRegistryId, const uint8*>& OutItemMap, const UScriptStruct*& OutItemStruct) const;` — Fills in a map with all cached (and precached) ids and items for fast iteration. This will use the current resolve context so may not always be valid, and multiple ids can map to the same raw pointer
- L215 _public function_ `const TArray<TObjectPtr<UDataRegistrySource>>& GetDataSources() const` — Returns the list of data sources.
- L218 _public function_ `const TArray<TObjectPtr<UDataRegistrySource>>& GetRuntimeSources() const` — Returns the data sources obtained during runtime.
- L223 _public prototype_ `virtual void GetChildRuntimeSources(UDataRegistrySource* ParentSource, TArray<UDataRegistrySource*>& ChildSources) const;` — Gets list of child runtime sources created by passed in source, in order registered
- L226 _public prototype_ `int32 GetSourceIndex(const UDataRegistrySource* Source, bool bUseRuntimeSources = true) const;` — Returns the index of a source in the source list
- L229 _public prototype_ `virtual void HandleAcquireResult(const FDataRegistrySourceAcquireRequest& Request, EDataRegistryAcquireStatus Status, uint8* ItemMemory, UDataRegistrySource* Source);` — Call to indicate that a item is available, will insert into cache
- L232 _public prototype_ `static class FTimerManager* GetTimerManager();` — Returns a timer manager that is safe to use for asset loading actions. This will either be the editor or game instance one, or null during very early startup
- L235 _public prototype_ `static float GetCurrentTime();` — Gets the current time
- L238 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L239 _public prototype_ `virtual void PostRename(UObject* OldOuter, const FName OldName) override;`
- L242 _public prototype_ `virtual void EditorRefreshRegistry();` — Validate and refresh registration
- L245 _public prototype_ `virtual void GetAllSourceItems(TArray<FDataRegistrySourceItemId>& OutSourceItems) const;` — Returns all source ids for editor display
- L248 _public prototype_ `virtual bool BatchAcquireSourceItems(TArray<FDataRegistrySourceItemId>& SourceItems, FDataRegistryBatchAcquireCallback DelegateToCall);` — Request a list of source items
- L255 _protected member_ `FName RegistryType;` — `UPROPERTY(EditDefaultsOnly, Category = DataRegistry, AssetRegistrySearchable)` — Globally unique name used to identify this registry
- L259 _protected member_ `FDataRegistryIdFormat IdFormat;` — `UPROPERTY(EditDefaultsOnly, Category = DataRegistry)` — Rules for specifying valid item Ids, if default than any name can be used
- L263 _protected member_ `TObjectPtr<const UScriptStruct> ItemStruct;` — `UPROPERTY(EditDefaultsOnly, Category = DataRegistry, AssetRegistrySearchable, meta = (DisplayThumbnail = "false"))` — Structure type of all for items in this registry
- L267 _protected member_ `TArray<TObjectPtr<UDataRegistrySource>> DataSources;` — `UPROPERTY(EditDefaultsOnly, Instanced, Category = DataRegistry)` — List of data sources to search for items
- L272 _protected member_ `TArray<TObjectPtr<UDataRegistrySource>> RuntimeSources;` — `UPROPERTY(VisibleDefaultsOnly, Instanced, Transient, Category = DataRegistry)` — Runtime list of data sources, created from above list and includes sources added at runtime
- L276 _protected member_ `float TimerUpdateFrequency = 1.0f;` — `UPROPERTY(EditDefaultsOnly, Category = Cache)` — How often to check for cache updates
- L280 _protected member_ `FDataRegistryCachePolicy DefaultCachePolicy;` — `UPROPERTY(EditDefaultsOnly, Category = Cache)` — Editor-set cache policy
- L283 _protected member_ `FDataRegistryCachePolicy RuntimeCachePolicy;` — Runtime override
- L286 _protected member_ `FDataRegistryCacheVersionCallback OnCacheVersionInvalidatedCallback;` — Callback for when cache version changes, might be moved later
- L289 _protected prototype_ `virtual void RefreshRuntimeSources();` — Refresh the RuntimeSources list
- L292 _protected prototype_ `virtual void TimerUpdate();` — Called on timer tick when initialized
- L295 _protected prototype_ `virtual FName MapIdToResolvedName(const FDataRegistryId& ItemId, const UDataRegistrySource* RegistrySource) const;` — Maps from a type:name pair to a per-source resolved name, default just returns the name
- L298 _protected prototype_ `virtual void AddAllIdsForResolvedName(TSet<FDataRegistryId>& PossibleIds, const FName& ResolvedName, const UDataRegistrySource* RegistrySource) const;` — Adds all possible source ids for resolved name to set, regardless of request context, default just uses the name
- L301 _protected prototype_ `const FCachedDataRegistryItem* FindCachedData(const FDataRegistryId& ItemId, const uint8** PrecachedDataPtr = nullptr) const;` — Returns internal cached data or raw memory ptr for precached data
- L304 _protected prototype_ `virtual void HandleCacheEntryState(const FDataRegistryLookup& Lookup, FCachedDataRegistryItem& CachedEntry);` — Advances state machine for a cached entry
- L307 _protected prototype_ `virtual void HandleAcquireCallbacks(const FDataRegistryLookup& Lookup, FCachedDataRegistryItem& CachedEntry);` — Handle sending completion/error callbacks
- L310 _protected prototype_ `virtual void UpdateBatchRequest(const FDataRegistryRequestId& RequestId, const FDataRegistryAcquireResult& Result);` — Check on any batch requests that need processing, if filter is empty will process all
- L313 _protected prototype_ `virtual void DelayedHandleSuccessCallbacks(FDataRegistryLookup Lookup);` — Frame-delayed callback to call success for already loaded items
- L316 _protected prototype_ `virtual bool AcquireItemInternal(const FDataRegistryId& ItemId, const FDataRegistryLookup& Lookup, FDataRegistryItemAcquiredCallback DelegateToCall, const FDataRegistryRequestId& BatchRequestId);` — Start an async request
- L320 _protected prototype_ `virtual void BeginDestroy() override;` — Overrides
- L321 _protected prototype_ `static void AddReferencedObjects(UObject* InThis, FReferenceCollector& Collector);`
- L325 _private member_ `FDataRegistryCache* Cache = nullptr;` — Internal cache data, can't use TUniquePtr due to UObject weirdness
- L327 _private member_ `FTimerHandle UpdateTimer;`
- L330 _private member_ `bool bIsInitialized = false;` — True if this registry has been initialized and is expected to respond to requests
- L333 _private member_ `bool bNeedsRuntimeRefresh = false;` — True if this registry needs a runtime refresh due to asset changes

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API DATAREGISTRY_API`

### `Plugins/Runtime/DataRegistry/Source/DataRegistry/Public/DataRegistryId.h` (Public)


#### struct `FDataRegistryType`  
`struct FDataRegistryType`  
_L30-95_
- reflection: `USTRUCT(BlueprintType)`
- desc: Wrapper struct to represent a global data registry, represented as an FName internally and implicitly convertible back and forth. This exists so the blueprint API can understand it's not a normal FName.
- L35 _public member_ `static const FName ItemStructMetaData;` — MetaData tag for both Type and Id that is used to restrict available registries to a certain item struct base class, ex. meta=(ItemStruct="NativeBaseClass")
- L38 _public member_ `static const FDataRegistryType CustomContextType;` — Fake type that can be used in the picker UI to specify that the Id contains a context-specific name that will be interpreted later
- L42 _public function_ `inline FDataRegistryType()` — Constructors, one for each FName constructor
- L43 _public function_ `inline FDataRegistryType(FName InName) : Name(InName)`
- L44 _public function_ `inline FDataRegistryType(EName InName) : Name(FName(InName))`
- L45 _public function_ `inline FDataRegistryType(const WIDECHAR* InName) : Name(FName(InName))`
- L46 _public function_ `inline FDataRegistryType(const ANSICHAR* InName) : Name(FName(InName))`
- L49 _public function_ `inline operator FName& ()` — Implicitly convert to FName
- L50 _public function_ `inline operator const FName& () const`
- L53 _public function_ `inline FName GetName() const` — Returns internal Name explicitly, not normally needed
- L58 _public function_ `inline bool operator==(const FDataRegistryType& Other) const`
- L63 _public function_ `inline bool operator!=(const FDataRegistryType& Other) const`
- L69 _public function_ `inline bool IsValid() const` — Returns true if this is a valid Type
- L75 _public function_ `inline FString ToString() const` — Returns string version of this Type
- L81 _public prototype_ `bool ExportTextItem(FString& ValueStr, FDataRegistryType const& DefaultValue, UObject* Parent, int32 PortFlags, UObject* ExportRootScope) const;` — UStruct Overrides
- L82 _public prototype_ `bool ImportTextItem(const TCHAR*& Buffer, int32 PortFlags, UObject* Parent, FOutputDevice* ErrorText);`
- L83 _public prototype_ `bool SerializeFromMismatchedTag(struct FPropertyTag const& Tag, FStructuredArchive::FSlot Slot);`
- L94 _protected member_ `FName Name;` — `UPROPERTY(EditAnywhere, SaveGame, BlueprintReadWrite, Category = DataRegistryType)` — The FName representing this type

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FDataRegistryType> : public TStructOpsTypeTraitsBase2<FDataRegistryType>`  
_L98-109_
- inherits: `TStructOpsTypeTraitsBase2<FDataRegistryType>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L101-108_

#### struct `FDataRegistryId`  
`struct FDataRegistryId`  
_L113-206_
- reflection: `USTRUCT(BlueprintType)`
- desc: Identifier for a specific DataRegistryItem, provides the user with a Tag or dropdown-based UI for selecting based on the available index info
- L119 _public member_ `FDataRegistryType RegistryType;` — `UPROPERTY(EditAnywhere, SaveGame, BlueprintReadWrite, Category = DataRegistry)` — The type of this item, used to look up the correct registry
- L123 _public member_ `FName ItemName;` — `UPROPERTY(EditAnywhere, SaveGame, BlueprintReadWrite, Category = DataRegistry)` — The name of this object, may be a leaf gameplay tag or a raw name depending on the type
- L127 _public function_ `inline FDataRegistryId()` — Explicit constructors
- L130 _public function_ `inline FDataRegistryId(const FName& InRegistryType, const FName& InItemName) : RegistryType(InRegistryType) , ItemName(InItemName)` — Construct from two names, will also work with FDataRegistryType due to the implicit cast
- L136 _public function_ `inline explicit FDataRegistryId(const FString& TypeAndName) : FDataRegistryId(ParseTypeAndName(TypeAndName))` — Parses out the Type:Name format
- L141 _public function_ `inline bool IsValid() const` — True if this represents an actual registry item
- L147 _public prototype_ `FString ToString() const;` — Returns string version of this identifier in Type:Name format
- L150 _public prototype_ `FText ToText() const;` — Returns Text description of string
- L152 _public function_ `inline bool operator==(const FDataRegistryId& Other) const`
- L157 _public function_ `inline bool operator!=(const FDataRegistryId& Other) const`
- L164 _public function_ `inline static FDataRegistryId ParseTypeAndName(const TCHAR* TypeAndName, uint32 Len)` — Convert from Type:Name strings, these are inline to avoid linker errors for constructor
- L179 _public function_ `inline static FDataRegistryId ParseTypeAndName(FName TypeAndName)`
- L186 _public function_ `inline static FDataRegistryId ParseTypeAndName(const FString& TypeAndName)`
- L193 _public prototype_ `bool ExportTextItem(FString& ValueStr, FDataRegistryId const& DefaultValue, UObject* Parent, int32 PortFlags, UObject* ExportRootScope) const;` — UStruct Overrides
- L194 _public prototype_ `bool ImportTextItem(const TCHAR*& Buffer, int32 PortFlags, UObject* Parent, FOutputDevice* ErrorText);`
- L195 _public prototype_ `bool SerializeFromMismatchedTag(struct FPropertyTag const& Tag, FStructuredArchive::FSlot Slot);`
- L196 _public prototype_ `void PostSerialize(const FArchive& Ar);`

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FDataRegistryId> : public TStructOpsTypeTraitsBase2<FDataRegistryId>`  
_L209-221_
- inherits: `TStructOpsTypeTraitsBase2<FDataRegistryId>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L212-220_

#### Free symbols / members of external scopes

- L85 _function_ `friend inline uint32 GetTypeHash(const FDataRegistryType& Key)`
- L102 _enumerator_ `WithZeroConstructor = true` (scope `TStructOpsTypeTraits::__anon8b7463e20103`)
- L103 _enumerator_ `WithCopy = true` (scope `TStructOpsTypeTraits::__anon8b7463e20103`)
- L104 _enumerator_ `WithIdenticalViaEquality = true` (scope `TStructOpsTypeTraits::__anon8b7463e20103`)
- L105 _enumerator_ `WithExportTextItem = true` (scope `TStructOpsTypeTraits::__anon8b7463e20103`)
- L106 _enumerator_ `WithImportTextItem = true` (scope `TStructOpsTypeTraits::__anon8b7463e20103`)
- L107 _enumerator_ `WithStructuredSerializeFromMismatchedTag = true` (scope `TStructOpsTypeTraits::__anon8b7463e20103`)
- L198 _function_ `friend inline uint32 GetTypeHash(const FDataRegistryId& Key)`
- L213 _enumerator_ `WithZeroConstructor = true` (scope `TStructOpsTypeTraits::__anon8b7463e20203`)
- L214 _enumerator_ `WithCopy = true` (scope `TStructOpsTypeTraits::__anon8b7463e20203`)
- L215 _enumerator_ `WithIdenticalViaEquality = true` (scope `TStructOpsTypeTraits::__anon8b7463e20203`)
- L216 _enumerator_ `WithExportTextItem = true` (scope `TStructOpsTypeTraits::__anon8b7463e20203`)
- L217 _enumerator_ `WithImportTextItem = true` (scope `TStructOpsTypeTraits::__anon8b7463e20203`)
- L218 _enumerator_ `WithStructuredSerializeFromMismatchedTag = true` (scope `TStructOpsTypeTraits::__anon8b7463e20203`)
- L219 _enumerator_ `WithPostSerialize = true` (scope `TStructOpsTypeTraits::__anon8b7463e20203`)

### `Plugins/Runtime/DataRegistry/Source/DataRegistry/Public/DataRegistryModule.h` (Public)


#### class `FDataRegistryModule`  
`class FDataRegistryModule : public IModuleInterface`  
_L10-35_
- inherits: `IModuleInterface`
- desc: Module logic, most of the time you want to access DataRegistrySubsystem directly
- L20 _public function_ `static inline FDataRegistryModule& Get()` — Singleton-like access to this module's interface.  This is just for convenience! Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already. @return Returns singleton instance, loading the module on demand if needed
- L31 _public function_ `static inline bool IsAvailable()` — Checks to see if this module is loaded and ready.  It is only valid to call Get() if IsAvailable() returns true. @return True if the module is loaded and ready to use

### `Plugins/Runtime/DataRegistry/Source/DataRegistry/Public/DataRegistrySettings.h` (Public)


#### class `UDataRegistrySettings`  
`class UDataRegistrySettings : public UDeveloperSettings`  
_L17-47_
- reflection: `UCLASS(MinimalAPI, config = Game, defaultconfig, meta = (DisplayName = "Data Registry"))`
- inherits: `UDeveloperSettings`
- desc: Settings for the Data Registry subsystem, these settings are used to scan for registry assets and set runtime access rules
- L25 _public member_ `TArray<FDirectoryPath> DirectoriesToScan;` — `UPROPERTY(config, EditAnywhere, Category = "Data Registry", meta = (RelativeToGameContentDir, LongPackageName))` — List of directories to scan for data registry assets
- L29 _public member_ `bool bInitializeAllLoadedRegistries = false;` — `UPROPERTY(config, EditAnywhere, Category = "Data Registry")` — If false, only registry assets inside DirectoriesToScan will be initialized. If true, it will also initialize any in-memory DataRegistry assets outside the scan paths
- L33 _public member_ `bool bIgnoreMissingCookedAssetRegistryData = false;` — `UPROPERTY(config, EditAnywhere, Category = "Data Registry")` — If true, cooked builds will ignore errors with missing AssetRegistry data for specific registered assets like DataTables as it may have been stripped out
- L37 _public member_ `bool bDelayLoadingDataRegistriesUntilPIE = false;` — `UPROPERTY(config, EditAnywhere, Category = "Data Registry")` — If true, in the editor data registry assets will be loaded before the first PIE instead of during startup
- L41 _public prototype_ `bool CanIgnoreMissingAssetData() const;` — Return true if we are allowed to ignore missing asset registry data based on settings and build
- L44 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API DATAREGISTRY_API`

### `Plugins/Runtime/DataRegistry/Source/DataRegistry/Public/DataRegistrySource.h` (Public)


#### class `UDataRegistrySource`  
`class UDataRegistrySource : public UObject`  
_L20-115_
- reflection: `UCLASS(MinimalAPI, Abstract, EditInlineNew, DefaultToInstanced, Within = DataRegistry, CollapseCategories)`
- inherits: `UObject`
- desc: Specifies a source for DataRegistry items, which is an interface that provides asynchronous access to individual structs
- L26 _public prototype_ `const UDataRegistry* GetRegistry() const;` — The outer for this should always be a Registry
- L27 _public prototype_ `UDataRegistry* GetRegistry();`
- L30 _public prototype_ `const UScriptStruct* GetItemStruct() const;` — Gets structure from parent registry
- L33 _public prototype_ `virtual EDataRegistryAvailability GetSourceAvailability() const;` — Returns how available this data is generally
- L36 _public prototype_ `virtual EDataRegistryAvailability GetItemAvailability(const FName& ResolvedName, const uint8** PrecachedDataPtr) const;` — Returns availability of individual item, also get raw memory address if available
- L39 _public prototype_ `virtual void GetResolvedNames(TArray<FName>& Names) const;` — Fills in set of all names provided by this source
- L42 _public prototype_ `virtual bool IsInitialized() const;` — Returns true if this state has been initialized for use
- L45 _public prototype_ `virtual bool Initialize();` — Called on editor-defined sources to initialize this source so it is ready to take requests
- L48 _public prototype_ `virtual void Deinitialize();` — Called on editor-defined sources to disable access and restore to state before initialization, won't do anything if not initialized
- L51 _public prototype_ `virtual void RefreshRuntimeSources();` — Called to regenerate runtime sources if needed, won't do anything for simple sources
- L54 _public prototype_ `virtual void AddRuntimeSources(TArray<UDataRegistrySource*>& OutRuntimeSources);` — Gets the list of runtime sources that should be registered for this source, will either be itself or a list of children
- L57 _public prototype_ `virtual void ResetRuntimeState();` — Called on runtime sources to reset caches and related state because game has ended or registry settings have changed
- L60 _public prototype_ `virtual void TimerUpdate(float CurrentTime, float TimerUpdateFrequency);` — Called by owning source as periodic update, can release resources or refresh connections
- L63 _public prototype_ `virtual void HandleAcquireResult(const FDataRegistrySourceAcquireRequest& Request, EDataRegistryAcquireStatus Status, uint8* ItemMemory);` — Call to indicate that a item is available, will insert into cache
- L66 _public prototype_ `virtual bool AcquireItem(FDataRegistrySourceAcquireRequest&& Request);` — Call to start an acquire request
- L69 _public prototype_ `virtual FString GetDebugString() const;` — Return a useful debug name for this source
- L72 _public prototype_ `virtual FSoftObjectPath GetSourceAssetPath() const;` — Returns the path to the underlying source asset (data table, curve table, etc.) if there is one
- L75 _public prototype_ `virtual bool IsTransientSource() const;` — Returns true if this is a runtime-only source
- L78 _public prototype_ `virtual bool ResetTransientSource();` — Resets transient source so it can be correctly garbage collected
- L81 _public prototype_ `virtual UDataRegistrySource* GetOriginalSource();` — Returns the editor-defined source, which is either this or the parent source
- L84 _public prototype_ `virtual bool IsSpecificAssetRegistered(const FSoftObjectPath& AssetPath) const;` — Returns true if this asset is already registered with this source
- L90 _public prototype_ `virtual EDataRegistryRegisterAssetResult RegisterSpecificAsset(const FAssetData& AssetData, int32 AssetPriority = 0);` — Attempt to register a specified asset with a source, returns an EDataRegistryRegisterAssetResult, indicating whether the asset was registered or not. Can be used to update priority for existing asset as well @return An EDataRegistryRegisterAssetResult that indicates if the asset Was Registered, whether it failed to register, or did not register because the asset was already registered.
- L93 _public prototype_ `virtual bool UnregisterSpecificAsset(const FSoftObjectPath& AssetPath);` — Removes references to a specific asset, returns bool if it was removed
- L96 _public prototype_ `virtual int32 UnregisterAssetsWithPriority(int32 AssetPriority);` — Unregisters all previously registered assets in a specific registry with a specific priority, can be used as a batch reset. Returns number of assets unregistered
- L100 _public prototype_ `virtual void EditorRefreshSource();` — Called on editor-defined states to check to check a source is still valid after major changes
- L102 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L107 _protected prototype_ `UDataRegistrySource* CreateTransientSource(TSubclassOf<UDataRegistrySource> SourceClass);` — Creates a new runtime source, but does not register it yet
- L110 _protected member_ `bool bIsInitialized = false;` — True if this is currently considered to be initialized
- L114 _protected member_ `TObjectPtr<UDataRegistrySource> ParentSource = nullptr;` — `UPROPERTY()` — What data source we were created from, if this is a transient source

#### enum `EMetaDataRegistrySourceAssetUsage`  
`enum class EMetaDataRegistrySourceAssetUsage : uint8`  
_L120-133_
- reflection: `UENUM()`
- desc: Rules specifying how a meta source will deal with assets, arranged as a semi-bitfield
- L123 _public enumerator_ `NoAssets = 0` — Does not use assets, gets sources from somewhere else like a web database
- L126 _public enumerator_ `SearchAssets = 1` — Only loads assets off disk, does not accept registered assets
- L129 _public enumerator_ `RegisterAssets = 2` — Only accepts registered assets, does not do any scanning
- L132 _public enumerator_ `SearchAndRegisterAssets = 3` — Both does search and will accept registered assets, using search rules as filter

#### class `UMetaDataRegistrySource`  
`class UMetaDataRegistrySource : public UDataRegistrySource`  
_L138-192_
- reflection: `UCLASS(MinimalAPI, Abstract)`
- inherits: `UDataRegistrySource`
- desc: Base class for a data source that generates additional data sources at runtime
- L144 _public prototype_ `virtual TSubclassOf<UDataRegistrySource> GetChildSourceClass() const;` — Returns what subclass of source to use for children, must be overridden!
- L147 _public prototype_ `virtual bool SetDataForChild(FName SourceName, UDataRegistrySource* ChildSource);` — Fills in new or existing child source for specific name, must be overridden!
- L150 _public prototype_ `virtual void DetermineRuntimeNames(TArray<FName>& OutRuntimeNames);` — Fills in list of desired runtime names, must be overridden!
- L153 _public prototype_ `virtual bool DoesAssetPassFilter(const FAssetData& AssetData, bool bNewRegisteredAsset);` — Returns true if this asset data passes the filter for this meta source, bNewRegisteredAsset is true if it comes from a RegisterSpecificAsset call and needs extra path checking
- L156 _public prototype_ `virtual void RefreshRuntimeSources() override;` — Source Interface
- L157 _public prototype_ `virtual void AddRuntimeSources(TArray<UDataRegistrySource*>& OutRuntimeSources) override;`
- L158 _public prototype_ `virtual bool IsSpecificAssetRegistered(const FSoftObjectPath& AssetPath) const override;`
- L159 _public prototype_ `virtual EDataRegistryRegisterAssetResult RegisterSpecificAsset(const FAssetData& AssetData, int32 AssetPriority) override;`
- L160 _public prototype_ `virtual bool UnregisterSpecificAsset(const FSoftObjectPath& AssetPath) override;`
- L161 _public prototype_ `virtual int32 UnregisterAssetsWithPriority(int32 AssetPriority) override;`
- L165 _public member_ `EMetaDataRegistrySourceAssetUsage AssetUsage;` — `UPROPERTY(EditAnywhere, Category = DataRegistry)` — Asset usage
- L169 _public member_ `FAssetManagerSearchRules SearchRules;` — `UPROPERTY(EditAnywhere, Category = DataRegistry, Meta = (EditCondition = "AssetUsage != EMetaDataRegistrySourceAssetUsage::NoAssets"))` — Asset registry scan rules
- L174 _protected prototype_ `virtual void OnNewAssetSearchRoot(const FString& SearchRoot);` — Callback registered when an asset search root as been added post launch
- L177 _protected prototype_ `virtual void SortRegisteredAssets();` — Sort assets, default order is by priority then array order
- L181 _protected member_ `TMap<FName, TObjectPtr<UDataRegistrySource>> RuntimeChildren;` — `UPROPERTY(Transient)` — Map from source identifier such as package name to registered child
- L184 _protected member_ `TArray<FName> RuntimeNames;` — List of desired source ids, in order
- L187 _protected typedef_ `typedef TPair<FAssetData, int32> FRegisteredAsset;` — List of specific assets registered with source, in runtime order sorted by priority
- L188 _protected member_ `TArray<FRegisteredAsset> SpecificRegisteredAssets;`
- L191 _protected member_ `FDelegateHandle NewAssetSearchRootHandle;` — Delegate handle for OnNewAssetSearchRoot

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API DATAREGISTRY_API`
- L134 _prototype_ `ENUM_CLASS_FLAGS(EMetaDataRegistrySourceAssetUsage);`

### `Plugins/Runtime/DataRegistry/Source/DataRegistry/Public/DataRegistrySource_CurveTable.h` (Public)


#### class `UDataRegistrySource_CurveTable`  
`class UDataRegistrySource_CurveTable : public UDataRegistrySource`  
_L15-85_
- reflection: `UCLASS(MinimalAPI, Meta = (DisplayName = "CurveTable Source"))`
- inherits: `UDataRegistrySource`
- desc: Data source that loads from a specific curve table asset
- L22 _public member_ `TSoftObjectPtr<UCurveTable> SourceTable;` — `UPROPERTY(EditAnywhere, Category = DataRegistry)` — What table to load from
- L26 _public member_ `FDataRegistrySource_DataTableRules TableRules;` — `UPROPERTY(EditAnywhere, Category = DataRegistry)` — Access rules
- L29 _public prototype_ `void SetSourceTable(const TSoftObjectPtr<UCurveTable>& InSourceTable, const FDataRegistrySource_DataTableRules& InTableRules);` — Update source table and rules, meant to be called from a meta source
- L34 _protected member_ `TObjectPtr<UCurveTable> CachedTable;` — `UPROPERTY(Transient)` — Hard ref to loaded table
- L38 _protected member_ `TObjectPtr<UCurveTable> PreloadTable;` — `UPROPERTY()` — Preload table ref, will be set if this is a hard source
- L41 _protected member_ `mutable float LastAccessTime;` — Last time this was accessed
- L44 _protected member_ `bool bInvalidSourceTable = false;` — This is set if the table fails to load or could never load
- L47 _protected member_ `TSharedPtr<FStreamableHandle> LoadingTableHandle;` — Handle for in progress load
- L50 _protected member_ `TArray<FDataRegistrySourceAcquireRequest> PendingAcquires;` — List of requests to resolve when table is loaded
- L53 _protected prototype_ `virtual void SetCachedTable(bool bForceLoad = false);` — Tells it to set CachedTable if possible
- L56 _protected prototype_ `virtual void ClearCachedTable();` — Clears cached table pointer so it can be GCd
- L59 _protected prototype_ `virtual void HandlePendingAcquires();` — Tells it to go through each pending acquire
- L62 _protected prototype_ `virtual void OnTableLoaded();` — Callback after table loads
- L66 _protected prototype_ `virtual EDataRegistryAvailability GetSourceAvailability() const override;` — Source interface
- L67 _protected prototype_ `virtual EDataRegistryAvailability GetItemAvailability(const FName& ResolvedName, const uint8** PrecachedDataPtr) const override;`
- L68 _protected prototype_ `virtual void GetResolvedNames(TArray<FName>& Names) const override;`
- L69 _protected prototype_ `virtual void ResetRuntimeState() override;`
- L70 _protected prototype_ `virtual bool AcquireItem(FDataRegistrySourceAcquireRequest&& Request) override;`
- L71 _protected prototype_ `virtual void TimerUpdate(float CurrentTime, float TimerUpdateFrequency) override;`
- L72 _protected prototype_ `virtual FString GetDebugString() const override;`
- L73 _protected prototype_ `virtual FSoftObjectPath GetSourceAssetPath() const override;`
- L74 _protected prototype_ `virtual bool Initialize() override;`
- L77 _protected prototype_ `virtual void PostLoad() override;` — Object interface
- L79 _protected prototype_ `virtual void OnDataTableChanged();`
- L82 _protected prototype_ `virtual void PreSave(FObjectPreSaveContext ObjectSaveContext) override;`
- L83 _protected prototype_ `virtual void EditorRefreshSource() override;`

#### class `UMetaDataRegistrySource_CurveTable`  
`class UMetaDataRegistrySource_CurveTable : public UMetaDataRegistrySource`  
_L90-112_
- reflection: `UCLASS(MinimalAPI, Meta = (DisplayName = "CurveTable Meta Source"))`
- inherits: `UMetaDataRegistrySource`
- desc: Meta source that will generate CurveTable sources at runtime based on a directory scan or asset registration
- L95 _public prototype_ `UMetaDataRegistrySource_CurveTable();` — Constructor
- L99 _public member_ `TSubclassOf<UDataRegistrySource_CurveTable> CreatedSource;` — `UPROPERTY(EditAnywhere, Category = DataRegistry)` — What specific source class to spawn
- L103 _public member_ `FDataRegistrySource_DataTableRules TableRules;` — `UPROPERTY(EditAnywhere, Category = DataRegistry)` — Access rules
- L108 _protected prototype_ `virtual TSubclassOf<UDataRegistrySource> GetChildSourceClass() const override;` — Source interface
- L109 _protected prototype_ `virtual bool SetDataForChild(FName SourceId, UDataRegistrySource* ChildSource) override;`
- L110 _protected prototype_ `virtual bool DoesAssetPassFilter(const FAssetData& AssetData, bool bNewRegisteredAsset) override;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API DATAREGISTRY_API`

### `Plugins/Runtime/DataRegistry/Source/DataRegistry/Public/DataRegistrySource_DataTable.h` (Public)


#### struct `FDataRegistrySource_DataTableRules`  
`struct FDataRegistrySource_DataTableRules`  
_L16-27_
- reflection: `USTRUCT()`
- desc: Rules struct for data table access
- L22 _public member_ `bool bPrecacheTable = true;` — `UPROPERTY(EditAnywhere, Category = DataRegistry)` — True if the entire table should be loaded into memory when the source is loaded, false if the table is loaded on demand
- L26 _public member_ `float CachedTableKeepSeconds = -1.0;` — `UPROPERTY(EditAnywhere, Category = DataRegistry)` — Time in seconds to keep cached table alive if hard reference is off. 0 will release immediately, -1 will never release

#### class `UDataRegistrySource_DataTable`  
`class UDataRegistrySource_DataTable : public UDataRegistrySource`  
_L32-102_
- reflection: `UCLASS(MinimalAPI, Meta = (DisplayName = "DataTable Source"))`
- inherits: `UDataRegistrySource`
- desc: Data source that loads from a specific data table containing the same type of structs as the registry
- L39 _public member_ `TSoftObjectPtr<UDataTable> SourceTable;` — `UPROPERTY(EditAnywhere, Category = DataRegistry)` — What table to load from
- L43 _public member_ `FDataRegistrySource_DataTableRules TableRules;` — `UPROPERTY(EditAnywhere, Category = DataRegistry)` — Access rules
- L46 _public prototype_ `void SetSourceTable(const TSoftObjectPtr<UDataTable>& InSourceTable, const FDataRegistrySource_DataTableRules& InTableRules);` — Update source table and rules, meant to be called from a meta source
- L51 _protected member_ `TObjectPtr<UDataTable> CachedTable;` — `UPROPERTY(Transient)` — Hard ref to loaded table
- L55 _protected member_ `TObjectPtr<UDataTable> PreloadTable;` — `UPROPERTY()` — Preload table ref, will be set if this is a hard source
- L58 _protected member_ `mutable float LastAccessTime;` — Last time this was accessed
- L61 _protected member_ `bool bInvalidSourceTable = false;` — This is set if the table fails to load or could never load
- L64 _protected member_ `TSharedPtr<FStreamableHandle> LoadingTableHandle;` — Handle for in progress load
- L67 _protected member_ `TArray<FDataRegistrySourceAcquireRequest> PendingAcquires;` — List of requests to resolve when table is loaded
- L70 _protected prototype_ `virtual void SetCachedTable(bool bForceLoad = false);` — Tells it to set CachedTable if possible
- L73 _protected prototype_ `virtual void ClearCachedTable();` — Clears cached table pointer so it can be GCd
- L76 _protected prototype_ `virtual void HandlePendingAcquires();` — Tells it to go through each pending acquire
- L79 _protected prototype_ `virtual void OnTableLoaded();` — Callback after table loads
- L83 _protected prototype_ `virtual EDataRegistryAvailability GetSourceAvailability() const override;` — Source interface
- L84 _protected prototype_ `virtual EDataRegistryAvailability GetItemAvailability(const FName& ResolvedName, const uint8** PrecachedDataPtr) const override;`
- L85 _protected prototype_ `virtual void GetResolvedNames(TArray<FName>& Names) const override;`
- L86 _protected prototype_ `virtual void ResetRuntimeState() override;`
- L87 _protected prototype_ `virtual bool AcquireItem(FDataRegistrySourceAcquireRequest&& Request) override;`
- L88 _protected prototype_ `virtual void TimerUpdate(float CurrentTime, float TimerUpdateFrequency) override;`
- L89 _protected prototype_ `virtual FString GetDebugString() const override;`
- L90 _protected prototype_ `virtual FSoftObjectPath GetSourceAssetPath() const override;`
- L91 _protected prototype_ `virtual bool Initialize() override;`
- L94 _protected prototype_ `virtual void PostLoad() override;` — Object interface
- L96 _protected prototype_ `virtual void OnDataTableChanged();`
- L99 _protected prototype_ `virtual void PreSave(FObjectPreSaveContext ObjectSaveContext) override;`
- L100 _protected prototype_ `virtual void EditorRefreshSource() override;`

#### class `UMetaDataRegistrySource_DataTable`  
`class UMetaDataRegistrySource_DataTable : public UMetaDataRegistrySource`  
_L107-129_
- reflection: `UCLASS(MinimalAPI, Meta = (DisplayName = "DataTable Meta Source"))`
- inherits: `UMetaDataRegistrySource`
- desc: Meta source that will generate DataTable sources at runtime based on a directory scan or asset registration
- L112 _public prototype_ `UMetaDataRegistrySource_DataTable();` — Constructor
- L116 _public member_ `TSubclassOf<UDataRegistrySource_DataTable> CreatedSource;` — `UPROPERTY(EditAnywhere, Category = DataRegistry)` — What specific source class to spawn
- L120 _public member_ `FDataRegistrySource_DataTableRules TableRules;` — `UPROPERTY(EditAnywhere, Category = DataRegistry)` — Access rules
- L125 _protected prototype_ `virtual TSubclassOf<UDataRegistrySource> GetChildSourceClass() const override;` — Source interface
- L126 _protected prototype_ `virtual bool SetDataForChild(FName SourceId, UDataRegistrySource* ChildSource) override;`
- L127 _protected prototype_ `virtual bool DoesAssetPassFilter(const FAssetData& AssetData, bool bNewRegisteredAsset) override;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API DATAREGISTRY_API`

### `Plugins/Runtime/DataRegistry/Source/DataRegistry/Public/DataRegistrySubsystem.h` (Public)


#### enum `EDataRegistrySubsystemGetItemResult`  
`enum class EDataRegistrySubsystemGetItemResult : uint8`  
_L18-24_
- reflection: `UENUM()`
- desc: Enum used to indicate success or failure of finding a data registry item
- L21 _public enumerator_ `Found` — Found the row successfully.
- L23 _public enumerator_ `NotFound` — Failed to find the row.

#### class `UDataRegistrySubsystem`  
`class UDataRegistrySubsystem : public UEngineSubsystem`  
_L28-302_
- reflection: `UCLASS(MinimalAPI, NotBlueprintType)`
- inherits: `UEngineSubsystem`
- desc: Singleton manager that provides synchronous and asynchronous access to data registries
- L44 _public function_ `static bool GetCachedItemBP(FDataRegistryId ItemId, UPARAM(ref) FTableRowBase& OutItem)` — `UFUNCTION(BlueprintCallable, CustomThunk, Category = DataRegistry, meta = (DisplayName = "Get Data Registry Item", CustomStructureParam = "OutItem"))` — Attempts to get cached structure data stored in a DataRegistry, modifying OutItem if the item is available. This version has an input param and simple bool return. @param ItemID		Item identifier to lookup in cache @param OutItem		This must be the same type as the registry, if the item is found this will be filled in with the found data @returns				Returns true if the item was found and OutItem was modified
- L56 _public function_ `static void FindCachedItemBP(FDataRegistryId ItemId, EDataRegistrySubsystemGetItemResult& OutResult, FTableRowBase& OutItem)` — `UFUNCTION(BlueprintCallable, CustomThunk, Category = DataRegistry, meta = (DisplayName = "Find Data Registry Item", CustomStructureParam = "OutItem", ExpandEnumAsExecs = "OutResult"))` — Attempts to get cached structure data stored in a DataRegistry, returning OutItem if the item is available. This version has two output pins for convenience, and OutItem should not be accessed from the Not Found pin. @param ItemID		Item identifier to lookup in cache @param OutItem		This must be the same type as the registry, if the item is found this will be filled in with the found data @param OutResult		Pick execution pin based on if the item was found and OutItem is valid
- L69 _public function_ `static void FindCachedItemFromLookupBP(FDataRegistryId ItemId, const FDataRegistryLookup& ResolvedLookup, EDataRegistrySubsystemGetItemResult& OutResult, FTableRowBase& OutItem)` — `UFUNCTION(BlueprintCallable, CustomThunk, Category = DataRegistry, meta = (DisplayName = "Find Data Registry Item From Lookup", CustomStructureParam = "OutItem", ExpandEnumAsExecs = "OutResult"))` — Attempts to get structure data stored in a DataRegistry cache after an async acquire, returning OutItem if the item is available. OutItem should not be accessed from the Not Found pin was not found. @param ItemID			Item identifier to lookup in cache @param ResolvedLookup	Resolved identifier returned by acquire function @param OutItem			This must be the same type as the registry, if the item is found this will be filled in with the found data @param OutResult			Pick execution pin based on if the item was found and OutItem is valid
- L74 _public function_ `static bool GetCachedItemFromLookupBP(FDataRegistryId ItemId, const FDataRegistryLookup& ResolvedLookup, FTableRowBase& OutItem)` — `UFUNCTION(BlueprintCallable, CustomThunk, Category = DataRegistry, meta = (DeprecatedFunction = "Note", DeprecationMessage = "Use Find Data Registry Item From Lookup instead", DisplayName = "Get Data Registry Item From Lookup", CustomStructureParam = "OutItem"))` — Deprecated in favor of FindCachedItemFromLookupBP, but does still work properly
- L86 _public prototype_ `static bool AcquireItemBP(FDataRegistryId ItemId, FDataRegistryItemAcquiredBPCallback AcquireCallback);` — `UFUNCTION(BlueprintCallable, Category = DataRegistry, meta = (DisplayName = "Acquire Data Registry Item"))` — Starts an asynchronous acquire of a data registry item that may not yet be cached, and then accessed with Get Data Registry Item From Lookup This function will only work properly if the data registry is set up for asynchronous querying. @param ItemID			Item identifier to lookup in cache @param AcquireCallback	Delegate that will be called after acquire succeeds or failed @returns					Returns true if request was started, false on unrecoverable error
- L96 _public prototype_ `static void GetPossibleDataRegistryIdList(FDataRegistryType RegistryType, TArray<FDataRegistryId>& OutIdList);` — `UFUNCTION(BlueprintCallable, BlueprintPure = false, Category = DataRegistry, meta = (DisplayName = "Get Possible Data Registry Id List"))` — Returns the list of known identifiers for an active data registry so they can be iterated with Find or Acquire. Depending on how the registry is setup, this could be a large number of identifiers and they may not all be available. @param RegistryType	The type of data registry to query @param OutIdList		The list of known identifiers for the type, which will be empty if the type is not registered
- L107 _public prototype_ `static void EvaluateDataRegistryCurve(FDataRegistryId ItemId, float InputValue, float DefaultValue, EDataRegistrySubsystemGetItemResult& OutResult, float& OutValue);` — `UFUNCTION(BlueprintCallable, Category = DataRegistry, meta = (ExpandEnumAsExecs = "OutResult"))` — Attempts to evaluate a curve stored in a DataRegistry cache using a specific input value @param ItemID		Item identifier to lookup in cache @param InputValue	Time/level/parameter input value used to evaluate curve at certain position @param DefaultValue	Value to use if no curve found or input is outside acceptable range @param OutValue		Result will be replaced with evaluated value, or default if that fails
- L112 _public prototype_ `static bool IsValidDataRegistryType(FDataRegistryType DataRegistryType);` — `UFUNCTION(BlueprintPure, Category = DataRegistry, meta = (ScriptMethod = "IsValid", ScriptOperator = "bool", BlueprintThreadSafe))` — Returns true if this is a non-empty type, does not check if it is currently registered
- L116 _public prototype_ `static FString Conv_DataRegistryTypeToString(FDataRegistryType DataRegistryType);` — `UFUNCTION(BlueprintPure, meta = (DisplayName = "To String (DataRegistryType)", CompactNodeTitle = "->", ScriptMethod = "ToString", BlueprintThreadSafe), Category = DataRegistry)` — Converts a Data Registry Type to a string. The other direction is not provided because it cannot be validated
- L120 _public prototype_ `static bool EqualEqual_DataRegistryType(FDataRegistryType A, FDataRegistryType B);` — `UFUNCTION(BlueprintPure, meta = (DisplayName = "Equal (DataRegistryType)", CompactNodeTitle = "==", ScriptOperator = "==", BlueprintThreadSafe), Category = DataRegistry)` — Returns true if the values are equal (A == B)
- L124 _public prototype_ `static bool NotEqual_DataRegistryType(FDataRegistryType A, FDataRegistryType B);` — `UFUNCTION(BlueprintPure, meta = (DisplayName = "Not Equal (DataRegistryType)", CompactNodeTitle = "!=", ScriptOperator = "!=", BlueprintThreadSafe), Category = DataRegistry)` — Returns true if the values are not equal (A != B)
- L128 _public prototype_ `static bool IsValidDataRegistryId(FDataRegistryId DataRegistryId);` — `UFUNCTION(BlueprintPure, Category = "AssetManager", meta=(ScriptMethod="IsValid", ScriptOperator="bool", BlueprintThreadSafe))` — Returns true if this is a non-empty item identifier, does not check if it is currently registered
- L132 _public prototype_ `static FString Conv_DataRegistryIdToString(FDataRegistryId DataRegistryId);` — `UFUNCTION(BlueprintPure, meta = (DisplayName = "To String (DataRegistryId)", CompactNodeTitle = "->", ScriptMethod="ToString", BlueprintThreadSafe), Category = DataRegistry)` — Converts a Data Registry Id to a string. The other direction is not provided because it cannot be validated
- L136 _public prototype_ `static bool EqualEqual_DataRegistryId(FDataRegistryId A, FDataRegistryId B);` — `UFUNCTION(BlueprintPure, meta = (DisplayName = "Equal (DataRegistryId)", CompactNodeTitle = "==", ScriptOperator="==", BlueprintThreadSafe), Category = DataRegistry)` — Returns true if the values are equal (A == B)
- L140 _public prototype_ `static bool NotEqual_DataRegistryId(FDataRegistryId A, FDataRegistryId B);` — `UFUNCTION(BlueprintPure, meta = (DisplayName = "Not Equal (DataRegistryId)", CompactNodeTitle = "!=", ScriptOperator="!=", BlueprintThreadSafe), Category = DataRegistry)` — Returns true if the values are not equal (A != B)
- L146 _public prototype_ `static UDataRegistrySubsystem* Get();` — Returns the global subsystem instance, this can return null during early engine startup and shutdown
- L149 _public prototype_ `UDataRegistry* GetRegistryForType(FName RegistryType) const;` — Finds the right registry for a type name
- L152 _public prototype_ `FText GetDisplayTextForId(FDataRegistryId ItemId) const;` — Returns proper display text for an id, using the correct id format
- L155 _public prototype_ `void GetAllRegistries(TArray<UDataRegistry*>& AllRegistries, bool bSortByType = true) const;` — Gets list of all registries, useful for iterating in UI or utilities
- L158 _public prototype_ `void RefreshRegistryMap();` — Refreshes the active registry map based on what's in memory
- L161 _public prototype_ `void LoadAllRegistries();` — Loads all registry assets and initializes them, this is called early in startup
- L164 _public prototype_ `bool AreRegistriesInitialized() const;` — True if all registries should have been initialized
- L167 _public prototype_ `bool IsConfigEnabled(bool bWarnIfNotEnabled = false) const;` — Returns true if the system is enabled via any config scan settings, will optionally warn if not enabled
- L170 _public prototype_ `bool IsReadyForInitialization() const;` — Returns true if the system is ready for initialization, if it hasn't started already
- L173 _public prototype_ `FDataRegistrySubsystemInitializedCallback& OnSubsystemInitialized();` — Accesses the delegate called when the subsystem has finished scanning for and initializing all known data registries
- L176 _public prototype_ `FPreLoadAllDataRegistriesCallback& OnPreLoadAllDataRegistries();` — Accesses the delegate called before the subsystem has loaded data registries
- L179 _public prototype_ `void InitializeAllRegistries(bool bResetIfInitialized = false);` — Initializes all loaded registries and prepares them for queries
- L182 _public prototype_ `void DeinitializeAllRegistries();` — De-initializes all loaded registries
- L185 _public prototype_ `bool LoadRegistryPath(const FSoftObjectPath& RegistryAssetPath);` — Load and initialize a specific registry, useful for plugins. This can hitch so the asset should be preloaded elsewhere if needed
- L188 _public prototype_ `bool IgnoreRegistryPath(const FSoftObjectPath& RegistryAssetPath);` — Removes specific data registry asset from the registration map, can be undone with LoadRegistryPath
- L191 _public prototype_ `void ResetRuntimeState();` — Resets state for all registries, call when gameplay has concluded to destroy caches
- L194 _public prototype_ `void ReinitializeFromConfig();` — Handles changes to DataRegistrySettings while engine is running
- L204 _public prototype_ `bool RegisterSpecificAsset(FDataRegistryType RegistryType, FAssetData& AssetData, int32 AssetPriority = 0);` — Attempt to register a specified asset with all active sources that allow dynamic registration, returning true if anything changed. This will fail if the registry does not exist yet. @param RegistryType		Type to register with, if invalid will try all registries @param AssetData			Filled in asset data of asset to attempt to register @Param AssetPriority		Priority of asset relative to others, higher numbers will be searched first
- L207 _public prototype_ `bool UnregisterSpecificAsset(FDataRegistryType RegistryType, const FSoftObjectPath& AssetPath);` — Removes references to a specific asset, returns bool if it was removed
- L210 _public prototype_ `int32 UnregisterAssetsWithPriority(FDataRegistryType RegistryType, int32 AssetPriority);` — Unregisters all previously registered assets in a specific registry with a specific priority, can be used as a batch reset. Returns number of assets unregistered
- L213 _public prototype_ `void PreregisterSpecificAssets(const TMap<FDataRegistryType, TArray<FSoftObjectPath>>& AssetMap, int32 AssetPriority = 0);` — Schedules registration of assets by path, this will happen immediately or will be queued if the data registries don't exist yet
- L216 _public prototype_ `FDataRegistryCacheGetResult GetCachedItemRaw(const uint8*& OutItemMemory, const UScriptStruct*& OutItemStruct, const FDataRegistryId& ItemId) const;` — Gets the cached or precached data and struct type. The return value specifies the cache safety for the data
- L219 _public prototype_ `FDataRegistryCacheGetResult GetCachedItemRawFromLookup(const uint8*& OutItemMemory, const UScriptStruct*& OutItemStruct, const FDataRegistryId& ItemId, const FDataRegistryLookup& Lookup) const;` — Gets the cached or precached data and struct type using an async acquire result. The return value specifies the cache safety for the data
- L222 _public prototype_ `FDataRegistryCacheGetResult EvaluateCachedCurve(float& OutValue, const FRealCurve*& OutCurve, FDataRegistryId ItemId, float InputValue, float DefaultValue = 0.0f) const;` — Computes an evaluated curve value, as well as the actual curve if it is found. The return value specifies the cache safety for the curve
- L226 _public function_ `template <class T> const T* GetCachedItem(const FDataRegistryId& ItemId) const` — Returns a cached item of specified struct type. This will return null if the item is not already in memory
- L237 _public prototype_ `bool AcquireItem(const FDataRegistryId& ItemId, FDataRegistryItemAcquiredCallback DelegateToCall) const;` — Start an async load of an item, delegate will be called on success or failure of acquire. Returns false if delegate could not be scheduled
- L243 _public prototype_ `static void DumpRegistryTypeSummary();` — Outputs all registered types and some info
- L246 _public prototype_ `static void DumpCachedItems(const TArray<FString>& Args);` — Dumps out a text representation of every item in the registry
- L250 _public prototype_ `bool WantsDelayedDataRegistryLoadingUntilPIE() const;` — Returns true if the system will wait until first access to process pending Data Registry loads
- L254 _protected typedef_ `typedef TPair<FName, TObjectPtr<UDataRegistry>> FRegistryMapPair;`
- L255 _protected member_ `TSortedMap<FName, TObjectPtr<UDataRegistry>, FDefaultAllocator, FNameFastLess> RegistryMap;`
- L258 _protected prototype_ `virtual void PostEngineInit();` — Initialization order, need to wait for other early-load systems to initialize
- L259 _protected prototype_ `virtual void PostGameplayTags();`
- L260 _protected prototype_ `virtual void PostAssetManager();`
- L261 _protected prototype_ `virtual void ApplyPreregisterMap(UDataRegistry* Registry);`
- L263 _protected prototype_ `virtual void Initialize(FSubsystemCollectionBase& Collection) override;`
- L264 _protected prototype_ `virtual void Deinitialize() override;`
- L266 _protected prototype_ `static void AddReferencedObjects(UObject* InThis, FReferenceCollector& Collector);`
- L269 _protected member_ `TArray<FString> AssetScanPaths;` — Paths that will be scanned for registries
- L272 _protected member_ `TArray<FSoftObjectPath> RegistryPathsToLoad;` — Specific registries to load, will be added to AssetScanPaths at scan time
- L275 _protected member_ `TArray<FSoftObjectPath> RegistryPathsToIgnore;` — Specific registries to avoid registering, may be in memory but will not be registered
- L278 _protected typedef_ `typedef TPair<FSoftObjectPath, int32> FPreregisterAsset;` — List of assets to attempt to register when data registries come online
- L279 _protected member_ `TMap<FDataRegistryType, TArray<FPreregisterAsset>> PreregisterAssetMap;`
- L282 _protected member_ `bool bFullyInitialized = false;` — True if initialization has finished and registries were scanned, will be false if not config enabled
- L285 _protected member_ `bool bReadyForInitialization = false;` — True if initialization is ready to start, will be true even if config disabled
- L288 _protected member_ `FDataRegistrySubsystemInitializedCallback OnSubsystemInitializedCallback;` — Callback for when the subsystem has finished scanning for and initializing all known data registries
- L291 _protected member_ `FPreLoadAllDataRegistriesCallback OnPreLoadAllDataRegistriesCallback;` — Callback for before the subsystem has loaded data registries
- L294 _protected member_ `static TObjectPtr<UDataRegistrySubsystem> SingletonSubSystem;` — Singleton object for the DataRegistrySubsystem::Get function to use, populated in Initialize and cleared out in Deinitialize
- L297 _protected member_ `bool bLoadAllRegistriesOnNextPIE = false;`
- L298 _protected prototype_ `virtual void PreBeginPIE(bool bStartSimulate);`
- L299 _protected prototype_ `virtual void EndPIE(bool bStartSimulate);`
- L301 _protected prototype_ `void FlushDeferredRegistryLoad(bool bExpected) const;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API DATAREGISTRY_API`

### `Plugins/Runtime/DataRegistry/Source/DataRegistry/Public/DataRegistryTypes.h` (Public)


#### enum `EDataRegistryAvailability`  
`enum class EDataRegistryAvailability : uint8`  
_L14-33_
- reflection: `UENUM()`
- desc: General rule about how hard it is to access an item, with later entries being the most available and faster to access
- L17 _public enumerator_ `DoesNotExist` — Item definitely does not exist
- L20 _public enumerator_ `Unknown` — Not sure where item is located or if it exists at all
- L23 _public enumerator_ `Remote` — From a database or website with very high latency
- L26 _public enumerator_ `OnDisk` — From some other asset such as a json file available without internet access
- L29 _public enumerator_ `LocalAsset` — Comes from a local asset, can be sync loaded as needed
- L32 _public enumerator_ `PreCached` — This item has already been loaded into memory by a different system and is immediately available

#### struct `FDataRegistryIdFormat`  
`struct FDataRegistryIdFormat`  
_L38-49_
- reflection: `USTRUCT()`
- desc: Struct representing how a unique id is formatted and picked in the editor
- L44 _public member_ `FGameplayTag BaseGameplayTag;` — `UPROPERTY(EditAnywhere, Category=Default)` — If this is not empty, all ids are part of this hierarchy

#### struct `FDataRegistryCachePolicy`  
`struct FDataRegistryCachePolicy`  
_L54-81_
- reflection: `USTRUCT(BlueprintType)`
- desc: Rules to use when deciding how to unload registry items and related assets
- L60 _public member_ `bool bCacheIsAlwaysVolatile = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Cache)` — If this is true, the cache is always considered volatile when returning EDataRegistryCacheResult
- L64 _public member_ `bool bUseCurveTableCacheVersion = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Cache)` — If this is true, the cache version is synchronized with the global CurveTable cache version
- L68 _public member_ `int32 MinNumberKept = 0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Cache)` — Will not release items if fewer then this number loaded, 0 means infinite
- L72 _public member_ `int32 MaxNumberKept = 0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Cache)` — Maximum number of items to keep loaded, 0 means infinite
- L76 _public member_ `float ForceKeepSeconds = 0.0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Cache)` — Any item accessed within this amount of seconds is never unloaded
- L80 _public member_ `float ForceReleaseSeconds = 0.0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Cache)` — Any item not accessed within this amount of seconds is always unloaded

#### struct `FDataRegistryLookup`  
`struct FDataRegistryLookup`  
_L86-152_
- reflection: `USTRUCT(BlueprintType)`
- desc: A resolved unique id for a specific source, explains how to look it up. This type is opaque in blueprints and cannot be saved across runs
- L92 _public member_ `TArray<TTuple<uint8, FName>, TInlineAllocator<1>> SourceLookups;` — TODO can be more efficient, probably best option is pack it into the num field of the FName, no one really names entries Foo_2147483646
- L95 _public function_ `inline void Reset()` — Resets to default
- L101 _public function_ `inline void AddEntry(uint8 Index, FName ResolvedName)` — Adds a new entry to lookup
- L107 _public function_ `inline bool IsValid() const` — True if this lookup could work
- L113 _public function_ `inline int32 GetNum() const` — Get number of lookups
- L119 _public function_ `inline bool GetEntry(uint8& OutIndex, FName& OutResolvedName, int32 NumEntry) const` — Gets a name and num
- L131 _public prototype_ `FString ToString() const;` — Generate a debug string

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FDataRegistryLookup> : public TStructOpsTypeTraitsBase2<FDataRegistryLookup>`  
_L155-161_
- inherits: `TStructOpsTypeTraitsBase2<FDataRegistryLookup>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L158-160_

#### struct `FDataRegistrySourceItemId`  
`struct FDataRegistrySourceItemId`  
_L166-202_
- reflection: `USTRUCT()`
- desc: A debugging/editor struct used to describe the source for a single data registry item
- L171 _public member_ `FDataRegistryId ItemId;` — Id that can be used to look this up by default
- L174 _public member_ `FDataRegistryLookup CacheLookup;` — Lookup used for caching
- L177 _public member_ `FName SourceResolvedName;` — Name this resolves to in the appropriate source
- L183 _public prototype_ `FString GetDebugString() const;` — Gets a unique ID key for this item, or None for invalid cached data

#### enum `EDataRegistryCacheGetStatus`  
`enum class EDataRegistryCacheGetStatus : uint8`  
_L206-216_
- desc: Information about the cache status of an item
- L209 _public enumerator_ `NotFound` — Item was not found in the cache
- L212 _public enumerator_ `FoundVolatile` — Item was found, but is likely to change if requested again. This is never safe to cache outside the function stack
- L215 _public enumerator_ `FoundPersistent` — Item was found, and this will be safe to cache as long as the GetCacheVersion on the DataRegistry has not changed

#### enum `EDataRegistryRegisterAssetResult`  
`enum class EDataRegistryRegisterAssetResult: uint8`  
_L219-229_
- desc: Error code returned when attempting to register a specific asset.
- L222 _public enumerator_ `NotRegistered` — Asset was not registered
- L225 _public enumerator_ `AssetAlreadyRegistered` — Asset already registered in the data registry
- L228 _public enumerator_ `RegisteredSuccesfully` — Asset was successfully registered

#### enum `EDataRegistryCacheVersionSource`  
`enum class EDataRegistryCacheVersionSource : uint8`  
_L232-254_
- desc: Where the cache version comes from, the upper values of this can be used for game-specific sources
- L235 _public enumerator_ `Invalid` — Invalid version
- L238 _public enumerator_ `DataRegistry` — Per registry version
- L241 _public enumerator_ `CurveTable` — The global curve table version
- L244 _public enumerator_ `GameVersion1` — Game-specific versions
- L245 _public enumerator_ `GameVersion2`
- L246 _public enumerator_ `GameVersion3`
- L247 _public enumerator_ `GameVersion4`
- L248 _public enumerator_ `GameVersion5`
- L249 _public enumerator_ `GameVersion6`
- L250 _public enumerator_ `GameVersion7`
- L251 _public enumerator_ `GameVersion8`
- L252 _public enumerator_ `GameVersion9`
- L253 _public enumerator_ `GameVersion10`

#### struct `FDataRegistryCacheGetResult`  
`struct FDataRegistryCacheGetResult`  
_L257-332_
- desc: Information about success and usage safety of cache queries
- L260 _public prototype_ `FDataRegistryCacheGetResult() = default;` — Default constructors, represents a failed get
- L263 _public function_ `FDataRegistryCacheGetResult(EDataRegistryCacheGetStatus InStatus, EDataRegistryCacheVersionSource InVersionSource = EDataRegistryCacheVersionSource::Invalid, int32 InCacheVersion = INDEX_NONE) : ItemStatus(InStatus) , VersionSource(InVersionSource) , CacheVersion(InCacheVersion)` — Explicit constructor for successful get
- L270 _public function_ `inline bool WasFound() const` — Return true if get was successful
- L276 _public function_ `inline bool IsPersistent() const` — Returns true if this cached value is safe to persist
- L282 _public function_ `inline bool IsValidForVersion(EDataRegistryCacheVersionSource InVersionSource, int32 InVersion) const` — Returns true if this cached value is safe to use given the version number
- L288 _public function_ `inline EDataRegistryCacheGetStatus GetItemStatus() const` — Returns the success/failure status
- L294 _public function_ `inline EDataRegistryCacheVersionSource GetVersionSource() const` — Returns the version source, which is used to validate
- L300 _public function_ `inline int32 GetCacheVersion() const` — Returns the cache version number
- L307 _public prototype_ `FDataRegistryCacheGetResult(const FDataRegistryCacheGetResult& Other) = default;`
- L308 _public prototype_ `FDataRegistryCacheGetResult& operator=(const FDataRegistryCacheGetResult& Other) = default;`
- L310 _public function_ `inline explicit operator bool() const`
- L315 _public function_ `inline bool operator !() const`
- L324 _private member_ `EDataRegistryCacheGetStatus ItemStatus = EDataRegistryCacheGetStatus::NotFound;` — Status of item inside cache
- L327 _private member_ `EDataRegistryCacheVersionSource VersionSource = EDataRegistryCacheVersionSource::Invalid;` — Status of item inside cache
- L330 _private member_ `int32 CacheVersion = INDEX_NONE;` — For persistent cache results, the version number of the registry at cache retrieval time

#### enum `EDataRegistryAcquireStatus`  
`enum class EDataRegistryAcquireStatus : uint8`  
_L337-359_
- reflection: `UENUM()`
- desc: State of a registry async request
- L340 _public enumerator_ `NotStarted` — Not started yet
- L343 _public enumerator_ `WaitingForInitialAcquire` — Initial acquire still in progress
- L346 _public enumerator_ `InitialAcquireFinished` — Temporary state, finished acquiring data but need to check resources
- L349 _public enumerator_ `WaitingForResources` — Data requested and returned, still loading dependent resources
- L352 _public enumerator_ `AcquireFinished` — Fully loaded
- L355 _public enumerator_ `AcquireError` — Failed to acquire, may have timed out or had network issues, can be retried later
- L358 _public enumerator_ `DoesNotExist` — Known to not exist, cannot be retried

#### struct `FDataRegistryAcquireResult`  
`struct FDataRegistryAcquireResult`  
_L362-410_
- desc: Result struct for acquiring, this should never be stored long term and the memory is only valid in the current stack frame
- L365 _public prototype_ `FDataRegistryAcquireResult(const FDataRegistryAcquireResult&) = delete;` — It is not safe to copy or store this struct as the memory may not be valid outside this stack frame
- L366 _public prototype_ `FDataRegistryAcquireResult& operator=(const FDataRegistryAcquireResult&) = delete;`
- L368 _public function_ `FDataRegistryAcquireResult(const FDataRegistryId& InItemId, const FDataRegistryLookup& InResolvedLookup, EDataRegistryAcquireStatus InStatus, const UScriptStruct* InItemStruct = nullptr, const uint8* inItemMemory = nullptr) : ItemId(InItemId) , ResolvedLookup(InResolvedLookup) , Status(InStatus) , ItemStruct(InItemStruct) , ItemMemory(inItemMemory)`
- L377 _public member_ `FDataRegistryId ItemId;` — The identifier this item corresponds to, the same struct can have multiple ids to refer to it
- L380 _public member_ `FDataRegistryLookup ResolvedLookup;` — The lookup this was resolved to, can use this to get item out of cache later without re-resolving
- L383 _public member_ `EDataRegistryAcquireStatus Status = EDataRegistryAcquireStatus::NotStarted;` — Result of query
- L386 _public member_ `const UScriptStruct* ItemStruct = nullptr;` — Type of the data acquired
- L389 _public member_ `const uint8* ItemMemory = nullptr;` — Memory of struct, this will either be null, or a totally valid struct
- L393 _public function_ `template <class T> const T* GetItem() const` — Checks type and returns valid struct if it exists
- L409 _public prototype_ `static void UpdateAcquireStatus(EDataRegistryAcquireStatus& CurrentStatus, EDataRegistryAcquireStatus NewStatus);` — Modifies acquire status based on new information, will advance status but not override error results

#### struct `FDataRegistrySourceAcquireRequest`  
`struct FDataRegistrySourceAcquireRequest`  
_L414-421_
- desc: Simple struct describing an acquire request, can be subclassed by different sources
- L417 _public member_ `FDataRegistryLookup Lookup;` — What lookup we are acquiring for
- L420 _public member_ `int32 LookupIndex = -1;` — Which source in lookup this is for

#### struct `FDataRegistryRequestId`  
`struct FDataRegistryRequestId`  
_L425-460_
- desc: Simple unique id for an acquire request
- L428 _public function_ `bool IsValid() const` — Returns true if this is a real request
- L434 _public prototype_ `static FDataRegistryRequestId GetNewRequestId();` — Gets an id to add request
- L436 _public function_ `bool operator==(const FDataRegistryRequestId& Other) const`
- L441 _public function_ `bool operator!=(const FDataRegistryRequestId& Other) const`
- L446 _public function_ `bool operator<(const FDataRegistryRequestId& Other) const`
- L457 _private member_ `static const int32 InvalidId = 0;`
- L459 _private member_ `int32 RequestId = InvalidId;`

#### struct `FDataRegistryResolver`  
`struct FDataRegistryResolver`  
_L464-471_
- desc: Abstract structure used to resolve data registry IDs by game or plugin-specific systems
- L467 _public prototype_ `virtual bool ResolveIdToName(FName& OutResolvedName, const FDataRegistryId& ItemId, const class UDataRegistry* Registry, const class UDataRegistrySource* RegistrySource) = 0;` — Override this function, if it returns true then OutResolvedName should be used, otherwise will check other resolvers and default behavior
- L470 _public function_ `virtual bool IsVolatile()` — Return true if this resolver is considered volatile, which means that it should stop any long term caching of results. This should be true for most stack-based resolvers

#### struct `FDataRegistryResolverScope`  
`struct FDataRegistryResolverScope`  
_L474-522_
- desc: Scope object to set a temporary resolver, or register a global one
- L477 _public prototype_ `FDataRegistryResolverScope(FDataRegistryResolver& ScopeResolver);` — Creates a temporary resolver scope without requiring a dynamically allocated object. Only valid on game thread
- L480 _public prototype_ `FDataRegistryResolverScope(const TSharedPtr<FDataRegistryResolver>& ScopeResolver);` — Creates a temporary resolver scope, will use the passed in resolver until scope returns. Only valid on game thread
- L483 _public prototype_ `~FDataRegistryResolverScope();` — Clears scope
- L486 _public prototype_ `static void RegisterGlobalResolver(const TSharedPtr<FDataRegistryResolver>& ScopeResolver);` — Static function to register a global scope
- L489 _public prototype_ `static void UnregisterGlobalResolver(const TSharedPtr<FDataRegistryResolver>& ScopeResolver);` — Unregister a global scope, must have been registered already
- L492 _public prototype_ `static FDataRegistryResolver* ResolveNameFromId(FName& OutResolvedName, const FDataRegistryId& ItemId, const class UDataRegistry* Registry, const class UDataRegistrySource* RegistrySource);` — Use the stack to resolve an ID, will return the resolver as raw pointer if found
- L495 _public prototype_ `static bool IsStackVolatile();` — Returns true if there are any volatile resolvers on the stack
- L499 _private member_ `FDataRegistryResolver* AddedScopeResolver;` — Stack depth at point this was added
- L520 _private member_ `static TArray<FResolverStackEntry> ResolverStack;`

#### struct `FDataRegistryResolverScope::FResolverStackEntry`  
`struct FResolverStackEntry`  
_L502-518_
- desc: Global and temporary resolver stack, will go from last added back to 0, optionally able to push stack objects
- L504 _public function_ `FResolverStackEntry(const TSharedPtr<FDataRegistryResolver>& ScopeResolver) : AsSharedPtr(ScopeResolver) , AsRawPtr(ScopeResolver.Get())`
- L510 _public function_ `FResolverStackEntry(FDataRegistryResolver& ScopeResolver) : AsSharedPtr() , AsRawPtr(&ScopeResolver)`
- L516 _public member_ `TSharedPtr<FDataRegistryResolver> AsSharedPtr;`
- L517 _public member_ `FDataRegistryResolver* AsRawPtr;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API DATAREGISTRY_API`
- L133 _function_ `friend inline uint32 GetTypeHash(const FDataRegistryLookup& Lookup)`
- L143 _function_ `friend inline bool operator==(const FDataRegistryLookup& X, const FDataRegistryLookup& Y)`
- L148 _function_ `friend inline bool operator!=(const FDataRegistryLookup& X, const FDataRegistryLookup& Y)`
- L159 _enumerator_ `WithCopy = true` (scope `TStructOpsTypeTraits::__anon0220fdca0103`) — This ensures the opaque type is copied correctly in BPs
- L185 _function_ `friend inline uint32 GetTypeHash(const FDataRegistrySourceItemId& SourceItem)`
- L193 _function_ `friend inline bool operator==(const FDataRegistrySourceItemId& X, const FDataRegistrySourceItemId& Y)`
- L198 _function_ `friend inline bool operator!=(const FDataRegistrySourceItemId& X, const FDataRegistrySourceItemId& Y)`
- L451 _function_ `friend inline uint32 GetTypeHash(const FDataRegistryRequestId& Key)`
- L526 _delegate_ `DECLARE_DELEGATE_OneParam(FDataRegistryItemAcquiredCallback, const FDataRegistryAcquireResult&);` — Delegate called in C++ when item is loaded
- L526 _prototype_ `DECLARE_DELEGATE_OneParam(FDataRegistryItemAcquiredCallback, const FDataRegistryAcquireResult&);` — Delegate called in C++ when item is loaded
- L529 _delegate_ `DECLARE_DYNAMIC_DELEGATE_ThreeParams(FDataRegistryItemAcquiredBPCallback, FDataRegistryId, ItemId, FDataRegistryLookup, ResolvedLookup, EDataRegistryAcquireStatus, Status);` — Blueprint delegate called when item is loaded, you will need to re-query the cache
- L529 _prototype_ `DECLARE_DYNAMIC_DELEGATE_ThreeParams(FDataRegistryItemAcquiredBPCallback, FDataRegistryId, ItemId, FDataRegistryLookup, ResolvedLookup, EDataRegistryAcquireStatus, Status);` — Blueprint delegate called when item is loaded, you will need to re-query the cache
- L532 _delegate_ `DECLARE_DELEGATE_OneParam(FDataRegistryBatchAcquireCallback, EDataRegistryAcquireStatus);` — Delegate called in C++ when multiple items are acquired, returns worst error experienced
- L532 _prototype_ `DECLARE_DELEGATE_OneParam(FDataRegistryBatchAcquireCallback, EDataRegistryAcquireStatus);` — Delegate called in C++ when multiple items are acquired, returns worst error experienced
- L535 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FDataRegistryCacheVersionCallback, class UDataRegistry*);` — Multicast delegate broadcast called when a data registry's cache version has changed
- L535 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FDataRegistryCacheVersionCallback, class UDataRegistry*);` — Multicast delegate broadcast called when a data registry's cache version has changed
- L538 _delegate_ `DECLARE_MULTICAST_DELEGATE(FDataRegistrySubsystemInitializedCallback);` — Multicast delegate broadcast called when the data registry subsystem has finished scanning for and initializing all known data registries
- L538 _prototype_ `DECLARE_MULTICAST_DELEGATE(FDataRegistrySubsystemInitializedCallback);` — Multicast delegate broadcast called when the data registry subsystem has finished scanning for and initializing all known data registries
- L541 _delegate_ `DECLARE_MULTICAST_DELEGATE(FPreLoadAllDataRegistriesCallback);` — Multicast delegate broadcast called before the data registry subsystem loads all registries
- L541 _prototype_ `DECLARE_MULTICAST_DELEGATE(FPreLoadAllDataRegistriesCallback);` — Multicast delegate broadcast called before the data registry subsystem loads all registries
- L544 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogDataRegistry, Log, All);`

### `Plugins/Runtime/DataRegistry/Source/DataRegistry/Public/SoftDataRegistryOrTable.h` (Public)


#### struct `FSoftDataRegistryOrTable`  
`struct FSoftDataRegistryOrTable`  
_L16-179_
- reflection: `USTRUCT(BlueprintType)`
- desc: Defines a DataRegistry or a DataTable with a common interface to both
- L20 _public prototype_ `FSoftDataRegistryOrTable();`
- L21 _public prototype_ `FSoftDataRegistryOrTable(const UDataTable* InDataTable, const FDataRegistryType& InRegistryType);`
- L23 _public prototype_ `bool Serialize(FArchive& Ar);`
- L26 _public prototype_ `bool Matches(const UDataTable* InTable) const;` — Method to check if the given table matches the value in this struct
- L29 _public prototype_ `bool Matches(const UDataRegistry* InRegistry) const;` — Method to check if the given registry matches the value in this struct
- L32 _public prototype_ `bool Matches(const FDataRegistryOrTableRow& RegistryOrTableId) const;` — Method to check if the given FDataRegistryOrTableRow matches the value in this struct
- L35 _public prototype_ `bool IsValid() const;` — Method to check validity of this struct (Checks that the registry or data table is set)
- L38 _public function_ `template <class T> void ForEachItem(const FString& ContextString, TFunctionRef<void(const FName& Name, const T& Item)> Predicate) const`
- L65 _public function_ `template <class T> void GetItems(const TCHAR* ContextString, TArray<const T*>& Items) const` — This function returns an array of all items in the given registry or data table
- L92 _public function_ `template <class T> void GetAllItems(const FString& ContextString, TArray<T*>& Items) const` — This function returns an array of all items in the given registry or data table
- L98 _public function_ `void GetItemNames(TArray<FName>& ItemNames) const` — This function returns an array of all item names in the given registry or data table
- L123 _public function_ `FString GetName() const`
- L143 _public prototype_ `bool SerializeFromMismatchedTag(const FPropertyTag& Tag, FStructuredArchive::FSlot Slot);` — Used to upgrade a SoftObjectPtr to a FSoftDataRegistryOrTable
- L146 _public prototype_ `bool IsLoaded() const;` — Returns whether or not the registry or table is loaded
- L153 _public prototype_ `void LoadAsync(FStreamableDelegate DelegateToCall);` — Requests an async load of a data table using the StreamableManager and then execute the callback, which will happen even if the load fails. NOTE: Data registries cannot be loaded this way because they must be registered with the data registry subsystem. @param DelegateToCall		Delegate to call when load finishes. Will be called on the next tick if asset is already loaded, or many seconds later
- L158 _public prototype_ `const UScriptStruct* GetStruct() const;` — Returns the script struct used by this data registry or table
- L161 _public prototype_ `FDataRegistryOrTableRow GetRegistryOrTableRow(FName RowName) const;` — Method to get a FDataRegistryOrTableRow from the given row name
- L164 _public member_ `bool bUseDataRegistry = false;` — `UPROPERTY(EditAnywhere, Category = DataRegistryOrTable)`
- L168 _public member_ `TSoftObjectPtr<UDataTable> Table;` — `UPROPERTY(EditAnywhere, Category = DataRegistryOrTable, meta = (EditCondition = "!bUseDataRegistry", EditConditionHides))` — Data Table
- L172 _public member_ `FDataRegistryType RegistryType;` — `UPROPERTY(EditAnywhere, Category = DataRegistryOrTable, meta = (EditCondition = "bUseDataRegistry", EditConditionHides))` — Data Registry
- L177 _private prototype_ `const UDataRegistry* GetDataRegistry() const;` — Method to get the Data Registry

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FSoftDataRegistryOrTable> : public TStructOpsTypeTraitsBase2<FSoftDataRegistryOrTable>`  
_L182-189_
- inherits: `TStructOpsTypeTraitsBase2<FSoftDataRegistryOrTable>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L185-188_

#### struct `FDataRegistryOrTableRow`  
`struct FDataRegistryOrTableRow`  
_L193-246_
- reflection: `USTRUCT(BlueprintType)`
- desc: Defines a DataRegistryId or DataTableRowHandle with a common interface to both
- L197 _public prototype_ `FDataRegistryOrTableRow();`
- L198 _public prototype_ `FDataRegistryOrTableRow(const FDataTableRowHandle& RowHandle);`
- L199 _public prototype_ `FDataRegistryOrTableRow(const FDataRegistryId& RegistryId);`
- L202 _public prototype_ `bool SerializeFromMismatchedTag(const FPropertyTag& Tag, FStructuredArchive::FSlot Slot);` — Used to upgrade a FDataTableHandle to a FDataRegistryOrTableRow
- L205 _public prototype_ `const UDataRegistry* GetDataRegistry() const;` — Method to get the Data Registry for the given registry id
- L208 _public function_ `template <class T> const T* GetItem(const TCHAR* ContextString) const`
- L229 _public prototype_ `const UScriptStruct* GetStruct() const;` — Returns the script struct used for the data registry item or data table row. Only works for data registries that are registered
- L231 _public prototype_ `FString ToString() const;`
- L233 _public prototype_ `FName GetItemName() const;`
- L236 _public prototype_ `bool IsValid() const;` — method to check validity of this row
- L239 _public member_ `bool bUseDataRegistryId = false;` — `UPROPERTY(EditAnywhere, Category = DataRegistryOrTable)`
- L242 _public member_ `FDataTableRowHandle DataTableRow;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = DataRegistryOrTable, meta = (EditCondition = "!bUseDataRegistryId", EditConditionHides))`
- L245 _public member_ `FDataRegistryId DataRegistryId;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = DataRegistryOrTable, meta = (EditCondition = "bUseDataRegistryId", EditConditionHides))`

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FDataRegistryOrTableRow> : public TStructOpsTypeTraitsBase2<FDataRegistryOrTableRow>`  
_L249-255_
- inherits: `TStructOpsTypeTraitsBase2<FDataRegistryOrTableRow>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L252-254_

#### Free symbols / members of external scopes

- L186 _enumerator_ `WithSerializer = true` (scope `TStructOpsTypeTraits::__anonf2a29eba0103`)
- L187 _enumerator_ `WithStructuredSerializeFromMismatchedTag = true` (scope `TStructOpsTypeTraits::__anonf2a29eba0103`)
- L253 _enumerator_ `WithStructuredSerializeFromMismatchedTag = true` (scope `TStructOpsTypeTraits::__anonf2a29eba0203`)
