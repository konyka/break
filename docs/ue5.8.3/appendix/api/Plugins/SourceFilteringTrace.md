# Plugins / SourceFilteringTrace

- module root: `Plugins/Developer/TraceSourceFiltering/Source/SourceFilteringTrace`
- headers: 19; symbols: 423
- symbol kinds: class=17, delegate=2, enum=1, enumerator=2, function=59, macro=25, member=140, namespace=2, prototype=159, struct=14, typedef=2
- PrivateDependencyModuleNames: AssetRegistry, Core, CoreUObject, DeveloperSettings, Engine, PropertyPath, SourceFilteringCore, TraceLog, UnrealEd

### `Plugins/Developer/TraceSourceFiltering/Source/SourceFilteringTrace/Private/ActorFiltering.h` (Private)


#### struct `FFilteredActorIterator`  
`struct FFilteredActorIterator`  
_L10-90_
- desc: Simplified version of TActorIterator
- L15 _public function_ `FORCEINLINE const AActor* operator*() const`
- L20 _public function_ `FORCEINLINE uint32 Index() const`
- L25 _public function_ `FORCEINLINE const AActor* operator->() const`
- L30 _public function_ `FORCEINLINE const AActor* GetActorChecked() const`
- L38 _public function_ `FORCEINLINE explicit operator bool() const`
- L43 _public function_ `void operator++()`
- L56 _private function_ `FFilteredActorIterator(const TArray<TWeakObjectPtr<const AActor>>& InActors, uint32 InStartIndex, uint32 InLength) : StartIndex(InStartIndex), CurrentIndex(InStartIndex), CurrentActor(nullptr), Actors(InActors)`
- L82 _private member_ `uint32 StartIndex;` — Range indices
- L83 _private member_ `uint32 EndIndex;`
- L85 _private member_ `uint32 CurrentIndex;` — Current index and corresponding AActor instance
- L86 _private member_ `TWeakObjectPtr<const AActor> CurrentActor;`
- L89 _private member_ `const TArray<TWeakObjectPtr<const AActor>>& Actors;` — All Actors retrieved by FActorCollector, over which we iterate within the defined range

#### class `FFilteredActorCollector`  
`class FFilteredActorCollector`  
_L93-226_
- desc: Used for retrieving AActor instances of particular classes from the owned UWorld, derived from FActorIteratorState
- L96 _public function_ `FFilteredActorCollector(UWorld* InWorld, const TArray<FActorClassFilter>& FilteredClasses) : CurrentWorld(InWorld)`
- L108 _public function_ `void UpdateFilterClasses(const TArray<FActorClassFilter>& FilteredClasses)` — Update the UClass instances used for filtering AActor instances
- L140 _public function_ `void CollectActors()` — Collect actor instances within UWorld who's class is contained by AllFilteredClasses
- L196 _public function_ `FFilteredActorIterator GetIterator(uint32 StartIndex = 0, uint32 Length = 0)` — Retrieve iterator over the provided range
- L202 _public function_ `int32 NumActors() const` — Return total number of actors 'collected'
- L207 _public function_ `TArray<const UClass*> GetAllFilteredClasses() const`
- L222 _protected member_ `UWorld* CurrentWorld;`
- L224 _protected member_ `TArray<TWeakObjectPtr<const AActor>> ActorArray;`
- L225 _protected member_ `TArray<TWeakObjectPtr<const UClass>> AllFilteredClasses;`

#### Free symbols / members of external scopes

- L179 _function_ `` (scope `FFilteredActorCollector::CollectActors`)

### `Plugins/Developer/TraceSourceFiltering/Source/SourceFilteringTrace/Private/ResultCache.h` (Private)


#### struct `FActorFilterInfo`  
`struct FActorFilterInfo`  
_L16-29_
- L19 _public member_ `const AActor* Actor;` — Actor itself
- L21 _public member_ `uint32 ActorHash;` — Actor's GetTypeHash value
- L23 _public member_ `const FHashSet* PassSets;` — Set of filterset hashes which can be regarded as passing for this actor
- L25 _public member_ `const FHashSet* DiscardSets;` — Set of filterset hashes which can be regarded as rejected for this actor
- L28 _public member_ `uint32 ActorIndex;` — Actor index (relative to FFilteredActorCollector::ActorArray)

#### enum `EFilterType`  
`enum EFilterType`  
_L31-35_
- L33 _public enumerator_ `GameThreadFilters`
- L34 _public enumerator_ `AsynchronousFilters`

#### struct `FResultCache`  
`struct FResultCache`  
_L38-95_
- desc: Structure used to store (inter-)frame per-actor and per-filter results
- L41 _public prototype_ `void Reset();` — Resets all internal data
- L44 _public prototype_ `void ResetFrameData(uint32 InNumActors, uint32 InNumFilterEntries);` — Resets any frame-transient data
- L47 _public prototype_ `void AddTickedIntervalFilter(const FFilter& Filter);` — Add an entry for interval-ticked filter
- L50 _public prototype_ `void ProcessIntervalFilterResults(const TArray<uint32>& ActorHashes);` — Processes all interval-ticked filter results from this frame
- L54 _public prototype_ `template<EFilterType FilterType> void CacheFilterSetResult(const FFilterSet& FilterSet, const FActorFilterInfo& ActorInfo, bool bResult);` — Caches the result of evaluating a filterset for the provided actor
- L57 _public prototype_ `bool RetrieveFilterSetResult(const FFilterSet& FilterSet, const FActorFilterInfo& ActorInfo) const;` — Retrieves the, previously cached, result for a filter-set / actor combination
- L60 _public prototype_ `void CacheFilterResult(const FFilter& Filter, const FActorFilterInfo& ActorInfo, bool bResult);` — Caches the result of evaluating a filter for the provided actor
- L63 _public prototype_ `void CacheSpawnFilterResult(uint32 FilterHash, const uint32 ActorHash, bool bResult);` — Caches the result of evaluating a spawn-only filter for the provided actor
- L66 _public prototype_ `bool RetrieveCachedResult(const FFilter& Filter, const FActorFilterInfo& ActorInfo) const;` — Retrieves the, previously cached, result for a filter / actor combination
- L69 _public prototype_ `void ProcessSpawnFilterResults();` — Appends this frames spawn filter results to SpawnFilterResults
- L73 _protected member_ `uint32 NumActors;` — Cached value of total number of actors for which results could be cached
- L77 _protected member_ `uint32 NumActorBits;` — Total number of actor bits to allocate
- L79 _protected member_ `TBitArray<FDefaultBitArrayAllocator> BitResults;`
- L81 _protected member_ `TArray<bool> Results;`
- L85 _protected member_ `TSet<uint32> IntervalFilterResults;` — contains actor + filter hash, for interval-ticked filters (if passed)
- L87 _protected member_ `TSet<uint32> SpawnFilterResults;` — contains actor + filter hash, for spawn filters (if passed)
- L90 _protected member_ `TSet<uint32> NewSpawnFilterPassResults;` — Frame-accumulated spawn filter results, applied to SpawnFilterResults at the end of the frame
- L91 _protected member_ `TSet<uint32> NewSpawnFilterRejectResults;`
- L94 _protected member_ `TMap<uint32, uint32> IntervalFilterIndexAndHash;` — Contains filter index + its hash, map is re-populated each frame with interval filters which will be tick during it (see AddTickedIntervalFilter)

#### Free symbols / members of external scopes

- L12 _macro_ `#define USE_BITSET_STORAGE 1` — Whether or not to use a BitArray to store per-actor/filter results
- L14 _typedef_ `typedef TSet<uint32 > FHashSet;`

### `Plugins/Developer/TraceSourceFiltering/Source/SourceFilteringTrace/Private/SourceFilter.h` (Private)


#### struct `FFilter`  
`struct FFilter`  
_L8-41_
- desc: Simplified structure representing a DataSourceFilter and its state within the FSourceFilterManager
- L11 _public member_ `const class UDataSourceFilter* Filter;` — Filter object
- L14 _public member_ `uint32 FilterHash;` — Filter's type-hash value
- L17 _public member_ `uint32 FilterSetHash;` — Hash of the filter run (set) this filter is contained by
- L20 _public member_ `uint32 TickFrameOffset;` — Index into FSourceFilterManager::(Last)FilterTickFrameIndices
- L23 _public member_ `uint32 ResultOffset;` — Cached Offset into the result (bit) array
- L26 _public member_ `uint8 TickInterval;` — Interval, in frames, between whenever the filter should be applied to actors
- L29 _public member_ `uint8 bExpectedValue : 1;` — Value this filter is expected to return for a given actor, in order for it to pass. (accumulated NOT operation)
- L32 _public member_ `uint8 bNative : 1;` — Whether or not the filter implementation is native, means we can call the native implemented function directly (rather than thunk)
- L34 _public member_ `uint8 bOnSpawnOnly : 1;` — Whether or not this filter should only be applied during actor spawning, and reapplied whenever the filter set changes
- L36 _public member_ `uint8 bCanRunAsynchronously : 1;` — Whether or not this filter was marked to be able to run off the game thread
- L38 _public member_ `uint8 bEarlyOutPass : 1;` — Whether or not the actor, when passing this filter, should be regarded as passing for the entire filter-set
- L40 _public member_ `uint8 bEarlyOutDiscard : 1;` — Whether or not the actor, when failing to pass this filter, should be discarded for the entire filter-set

### `Plugins/Developer/TraceSourceFiltering/Source/SourceFilteringTrace/Private/SourceFilterManager.h` (Private)


#### class `FSourceFilterManager`  
`class FSourceFilterManager`  
_L23-146_
- desc: Per-UWorld object that keeps track of the its contained AActor's filtering states
- L35 _public prototype_ `FSourceFilterManager(UWorld* InWorld);`
- L36 _public prototype_ `~FSourceFilterManager();`
- L40 _protected prototype_ `void OnFilterSetupChanged();` — Update the internal data based upon the changed filter setup
- L41 _protected prototype_ `void OnSourceFilteringSettingsChanged();`
- L42 _protected prototype_ `void ResetFilterData();`
- L46 _protected prototype_ `template<EFilterType FilterType> void ApplyFilters();` — Applies all UDataSourceFilters to the specified AActor, and updates it filtering state accordingly
- L48 _protected prototype_ `void ApplyGameThreadFilters();`
- L49 _protected prototype_ `void ApplyAsyncFilters();`
- L52 _protected prototype_ `template<EFilterType FilterType> bool ApplyFilterSetToActor(const FFilterSet& FilterSet, const FActorFilterInfo& ActorInfo);`
- L55 _protected prototype_ `void ApplySpawnFilters();` — Spawn filtering
- L56 _protected prototype_ `void ApplySpawnFiltersToActor(const AActor* Actor);`
- L57 _protected prototype_ `void AddOnSpawnFilter(const UDataSourceFilter* Filter, bool bExpectedResult, uint32 RunHash);`
- L60 _protected prototype_ `void ApplyFilterResults();` — Apply the previously determined results to the Trace filtering state
- L63 _protected prototype_ `void ApplyFilterResultsToActor(const FActorFilterInfo& ActorInfo);` — Determine the filtering state for an individual Actor
- L64 _protected prototype_ `bool DetermineActorFilteringState(const FActorFilterInfo& ActorInfo) const;`
- L66 _protected prototype_ `bool ApplyClassFilterToActor(const AActor* Actor);`
- L69 _protected prototype_ `void DrawFilterResults();` — Debug drawing
- L70 _protected prototype_ `void DrawFilterResults(const AActor* Actor);`
- L73 _protected prototype_ `void SetupAsyncTasks(ENamedThreads::Type CurrentThread);` — Set and kick-off async tasks
- L76 _protected prototype_ `void WaitForAsyncTasks();` — Waits for any previously kicked of async tasks
- L79 _protected prototype_ `void ResetPerFrameData();` — Reset last frame's transient data and setup the next
- L82 _protected prototype_ `void SetupIntervalData();` — Setting up per-frame data for any contained interval-based filters
- L83 _protected prototype_ `void SetupIntervalFilterSet(const FFilterSet& FilterSet);`
- L84 _protected prototype_ `void SetupIntervalFilter(const FFilter& Filter);`
- L87 _protected prototype_ `void RegisterTickFunctions();` — Tick functions used to kick-off the individual (async) tasks
- L88 _protected prototype_ `void UnregisterTickFunctions();`
- L92 _protected member_ `FDelegateHandle ActorSpawningDelegateHandle;` — Registered delegate for whenever an AActor is spawned, and before, within World
- L93 _protected member_ `FDelegateHandle PreActorSpawningDelegateHandle;`
- L96 _protected member_ `UTraceSourceFilteringSettings* Settings;` — Filtering settings for the running instance
- L99 _protected member_ `UWorld* World;` — UWorld instance that this instance corresponds to
- L102 _protected member_ `TMap<uint32, FHashSet> PassedFilterSets;` — Maps from Actor Hash to FilterSets (hash) that will pass due to previous Spawn Only filter results
- L104 _protected member_ `TMap<uint32, FHashSet> DiscardedFilterSets;` — Maps from Actor Hash to FilterSets (hash) that will not pass due to previous Spawn Only filter results
- L107 _protected member_ `TSet<uint32> DiscardedActorHashes;` — Actor hashes for those that were previously discarded by, or passed a spawn filter
- L108 _protected member_ `TSet<uint32> PassedActorsHashes;`
- L111 _protected member_ `FSourceFilteringTickFunction PrePhysicsTickFunction;` — Tick functions
- L112 _protected member_ `FSourceFilteringTickFunction LastDemotableTickFunction;`
- L115 _protected member_ `FGraphEventRef AsyncTasks[2];` — Async task-graph handles
- L116 _protected member_ `FGraphEventRef FinishTask;`
- L117 _protected member_ `FGraphEventRef DrawTask;`
- L120 _protected member_ `uint8 bAreTickFunctionsRegistered : 1;` — Flags used to determine what type (or if any) filters are contained in the current filter-set
- L131 _protected member_ `FFilterStats Statistics;`
- L133 _protected member_ `FResultCache ResultCache;`
- L135 _protected member_ `TArray<uint32> ActorHashes;`
- L136 _protected member_ `FFilteredActorCollector ActorCollector;`
- L138 _protected member_ `FSourceFilterSetup& FilterSetup;`
- L139 _protected member_ `FPerWorldData WorldData;`

#### struct `FSourceFilterManager::FFilterStats`  
`struct FFilterStats`  
_L122-130_
- L124 _public member_ `uint32 TotalActors;`
- L125 _public member_ `uint32 EarlyRejectedActors;`
- L126 _public member_ `uint32 EarlyPassedActors;`
- L127 _public member_ `uint32 RejectedActors;`
- L128 _public member_ `uint32 PassedActors;`
- L129 _public member_ `uint32 EvaluatedActors;`

#### struct `FSourceFilterManager::FFilterTraceScopeLock`  
`struct FFilterTraceScopeLock`  
_L141-145_
- L143 _public prototype_ `FFilterTraceScopeLock();`
- L144 _public prototype_ `~FFilterTraceScopeLock();`

#### Free symbols / members of external scopes

- L20 _delegate_ `DECLARE_STATS_GROUP(TEXT("FSourceFilterManager"), STATGROUP_SourceFilterManager`

### `Plugins/Developer/TraceSourceFiltering/Source/SourceFilteringTrace/Private/SourceFilterPresets.h` (Private)


#### struct `FSourceFilterPresets`  
`struct FSourceFilterPresets`  
_L11-23_
- L14 _public prototype_ `static void GetPresets(TArray<FAssetData>& InOutPresetAssetData);` — Return array of FAssetData entries representing load-able filter presets
- L17 _public prototype_ `static void LoadPreset(const FSoftObjectPath& PresetPath);` — Loading and replacing the current filtering state with a preset
- L20 _public prototype_ `static void ListAvailablePresets();` — Logs all available filter preset paths
- L22 _public prototype_ `static void LoadPresetCommand(const TArray<FString>& Arguments);` — Console command functionality for loading a preset my path or index (relative to GetPresets())

### `Plugins/Developer/TraceSourceFiltering/Source/SourceFilteringTrace/Private/SourceFilterSet.h` (Private)


#### struct `FFilterSet`  
`struct FFilterSet`  
_L13-36_
- desc: Simplified structure representing a DataSourceFilterSet and its state within the FSourceFilterManager
- L16 _public member_ `TArray<FFilter, FilterSetAllocator> FilterEntries;` — Contained (at least one) filters
- L19 _public member_ `TArray<FFilterSet> ChildFilterSets;` — Any contained child filter sets
- L22 _public member_ `uint32 FilterSetHash;` — Typehash for the corresponding UDataSourceFilterSet
- L25 _public member_ `uint32 ResultOffset;` — Cached Offset into the result (bit) array
- L28 _public member_ `EFilterSetMode Mode;` — Set operation
- L31 _public member_ `uint8 bContainsGameThreadFilter : 1;` — Whether or not this filter set contains any gamethread filters
- L33 _public member_ `uint8 bContainsAsyncFilter : 1;` — Whether or not this filter set contains any async filters
- L35 _public member_ `uint8 bInitialPassingValue : 1;` — Expected value (true/false) for whether or not an applied filter within this set passes

#### Free symbols / members of external scopes

- L10 _typedef_ `typedef TInlineAllocator<8> FilterSetAllocator;`

### `Plugins/Developer/TraceSourceFiltering/Source/SourceFilteringTrace/Private/SourceFilterSetup.h` (Private)


#### struct `FPerWorldData`  
`struct FPerWorldData`  
_L20-26_
- L23 _public member_ `TArray<uint32, FilterSetAllocator> IntervalFilterFrames;` — Cache containing frame indices at which each interval filter was last evaluated
- L25 _public member_ `TArray<bool, FilterSetAllocator> IntervalFilterShouldTick;` — Contains flag for each interval filter, determining whether or not it should be evaluated this frame

#### class `FSourceFilterSetup`  
`class FSourceFilterSetup`  
_L28-146_
- L32 _public prototype_ `static FSourceFilterSetup& GetFilterSetup();` — Get singleton filter setup instance
- L35 _public function_ `FSimpleMulticastDelegate& GetFilterSetupUpdated()` — Retrieve delegate broadcasted whenever the contained setup changes
- L38 _public prototype_ `void PopulatePerWorldData(FPerWorldData& InData);` — Populates per-world data based upon the current setup
- L41 _public function_ `const FFilterSet& GetRootSet() const` — Return (top-level) root filter set
- L43 _public function_ `const TArray<FFilter>& GetSpawnFilters() const` — Retrieve setup spawn filters
- L45 _public function_ `const TArray<FActorClassFilter>& GetActorFilters() const` — Retriever setup actor-class filters
- L48 _public function_ `FHashSet GetSpawnFilterDiscardableSets(const FFilter& SpawnFilter)` — Retrieve array of filter-set hashes which can be regarded as rejected for the provided spawn filter
- L55 _public function_ `FHashSet GetSpawnFilterSkippableSets(const FFilter& SpawnFilter)` — Retrieve array of filter-set hashes which can be regarded as passing for the provided spawn filter
- L62 _public function_ `bool RequiresApplyingFilters() const` — Whether nor not the setup contains any filters that need per-frame evaluation / applying
- L64 _public function_ `bool HasAnyFilters() const` — Whether or not the setup contains any filters at all
- L66 _public function_ `bool HasAnySpawnFilters() const` — Whether or not the setup contains any spawn filters
- L68 _public function_ `bool HasOnlySpawnFilters() const` — Whether or not the setup contains only spawn filters
- L70 _public function_ `bool HasGameThreadFilters() const` — Whether or not the setup contains any filters requiring evaluation on the gamethread
- L72 _public function_ `bool HasAsyncFilters() const` — Whether or not the setup contains any filters can be evaluated off the gamethread
- L74 _public function_ `bool HasAnyClassFilters() const` — Whether or not the setup contains any actor class filters
- L77 _public function_ `uint32 NumFilterAndSetEntries() const` — Total number of filter(set)s contained by the setup
- L79 _protected prototype_ `FSourceFilterSetup();`
- L80 _protected prototype_ `~FSourceFilterSetup();`
- L83 _protected prototype_ `void Reset();` — Resets any contained data
- L86 _protected prototype_ `void ShutdownOnPreExit();` — FCoreDelegates::OnPreExit shutdown callback
- L89 _protected prototype_ `void OnSourceFiltersUpdated();` — Callback registered with SourceFilterCollection
- L92 _protected prototype_ `void SetupUserFilters(const TArray<UDataSourceFilter*>& Filters, bool bOutputState);` — Generated internal data according to provided filters
- L93 _protected prototype_ `void ProcessFilterRecursively(const UDataSourceFilter* InFilter, FFilterSet& InOutFilterSet, bool bResultValue);`
- L94 _protected prototype_ `void AddFilterToSet(FFilterSet& FilterSet, const UDataSourceFilter* Filter, bool bExpectedResult);`
- L103 _protected prototype_ `FOptimizationResult OptimizeFiltersInSet(FFilterSet& FilterSet);` — Used to optimize filtering setup, flattening filter sets where possible and reordering filter evaluation according to their estimated cost
- L106 _protected prototype_ `FFilter& GetSpawnFilter(uint32 FilterHash);` — Find spawn-only filter according to its hash
- L109 _protected prototype_ `bool DetermineDefaultPassingValueForSet(const UDataSourceFilterSet* FilterSet);` — Determine what the expected boolean return value is when evaluating the filter set
- L112 _protected prototype_ `void OutputFilterSetState(const FFilterSet& FilterSet, FString& Output, int32 Depth = 0);` — Recursively outputs the filtering state for the provided filter set
- L115 _protected member_ `FFilterSet RootSet;` — Root filter set, contains TopLevelFilters entries
- L118 _protected member_ `TArray<FFilter> OnSpawnFilters;` — All Spawn only filters contained by Rootset
- L121 _protected member_ `TArray<FActorClassFilter> ActorClassFilters;` — Actor class filter
- L125 _protected member_ `TMap<uint32, FHashSet> OnSpawnFilterSetDiscards;` — Maps from individual FFilterEntry Hash (Spawn filters only), to an array of FFilterRun hashes that can be disregarded when applying them to an Actor, as they will fail
- L129 _protected member_ `TMap<uint32, FHashSet> OnSpawnFilterSetPass;` — Maps from individual FFilterEntry Hash (Spawn filters only), to an array of FFilterRun hashes that can be disregarded when applying them to an Actor, as they will pass
- L132 _protected member_ `UTraceSourceFilteringSettings* FilterSettings;` — Filtering settings for the running instance
- L134 _protected member_ `USourceFilterCollection* FilterCollection;` — Filter collection, containing the UDataSourceFilters, for the running instance
- L136 _protected member_ `FSimpleMulticastDelegate FilterSetupUpdated;`
- L139 _protected member_ `uint8 bContainsGameThreadFilters : 1;` — Flags used to determine what type (or if any) filters are contained in the current filter-set
- L140 _protected member_ `uint8 bContainsNonGameThreadFilters : 1;`
- L141 _protected member_ `uint8 bContainsAnyFilters : 1;`
- L142 _protected member_ `uint8 bContainsAnySpawnOnlyFilters : 1;`
- L144 _protected member_ `uint32 TotalNumEntries;`
- L145 _protected member_ `uint32 TotalIntervalEntries;`

#### struct `FSourceFilterSetup::FOptimizationResult`  
`struct FOptimizationResult`  
_L96-101_
- L98 _public member_ `int32 TotalCost;`
- L99 _public member_ `int32 NumSpawnFilters;`
- L100 _public member_ `TSet<uint32> OnSpawnFilterHashes;`

### `Plugins/Developer/TraceSourceFiltering/Source/SourceFilteringTrace/Private/SourceFilteringAsyncTasks.h` (Private)


#### class `FActorFilterAsyncTask`  
`class FActorFilterAsyncTask`  
_L10-29_
- desc: Async task executed on both GT and async thread to apply the corresponding type of filters
- L12 _private member_ `FSourceFilterManager* Manager;`
- L13 _private member_ `bool bRunAsAsync;`
- L15 _public function_ `FActorFilterAsyncTask(FSourceFilterManager* InManager, bool bShouldRunAsAsync) : Manager(InManager), bRunAsAsync(bShouldRunAsAsync)`
- L17 _public function_ `FORCEINLINE TStatId GetStatId() const`
- L22 _public function_ `ENamedThreads::Type GetDesiredThread()`
- L27 _public function_ `static ESubsequentsMode::Type GetSubsequentsMode()`
- L28 _public prototype_ `void DoTask(ENamedThreads::Type CurrentThread, const FGraphEventRef& MyCompletionGraphEvent);`

#### class `FActorFilterApplyAsyncTask`  
`class FActorFilterApplyAsyncTask`  
_L32-50_
- desc: Async task which handles applying the filtering result to the Engine-level trace filtering system (non-GT)
- L34 _private member_ `FSourceFilterManager* Manager;`
- L36 _public function_ `FActorFilterApplyAsyncTask(FSourceFilterManager* InManager) : Manager(InManager)`
- L38 _public function_ `FORCEINLINE TStatId GetStatId() const`
- L43 _public function_ `ENamedThreads::Type GetDesiredThread()`
- L48 _public function_ `static ESubsequentsMode::Type GetSubsequentsMode()`
- L49 _public prototype_ `void DoTask(ENamedThreads::Type CurrentThread, const FGraphEventRef& MyCompletionGraphEvent);`

#### class `FActorFilterDrawStateAsyncTask`  
`class FActorFilterDrawStateAsyncTask`  
_L53-72_
- desc: Async task which handles drawing the filtering state on the GT
- L55 _private member_ `FSourceFilterManager* Manager;`
- L58 _public function_ `FActorFilterDrawStateAsyncTask(FSourceFilterManager* InManager) : Manager(InManager)`
- L60 _public function_ `FORCEINLINE TStatId GetStatId() const`
- L65 _public function_ `ENamedThreads::Type GetDesiredThread()`
- L70 _public function_ `static ESubsequentsMode::Type GetSubsequentsMode()`
- L71 _public prototype_ `void DoTask(ENamedThreads::Type CurrentThread, const FGraphEventRef& MyCompletionGraphEvent);`

### `Plugins/Developer/TraceSourceFiltering/Source/SourceFilteringTrace/Private/SourceFilteringTickFunction.h` (Private)


#### struct `FSourceFilteringTickFunction`  
`struct FSourceFilteringTickFunction : public FTickFunction`  
_L10-20_
- inherits: `FTickFunction`
- desc: Tick function used for handling FSourceFilterManager ticking + kicking off async tasks
- L14 _public function_ `FSourceFilteringTickFunction() : Manager(nullptr)`
- L16 _private prototype_ `virtual void ExecuteTick(float DeltaTime, ELevelTick TickType, ENamedThreads::Type CurrentThread, const FGraphEventRef& MyCompletionGraphEvent) override;`
- L17 _private prototype_ `virtual FString DiagnosticMessage() override;`
- L19 _protected member_ `FSourceFilterManager* Manager;`

### `Plugins/Developer/TraceSourceFiltering/Source/SourceFilteringTrace/Private/SourceFilteringTraceModule.h` (Private)


#### class `FSourceFilteringTraceModule`  
`class FSourceFilteringTraceModule : public IModuleInterface`  
_L8-18_
- inherits: `IModuleInterface`
- L11 _public prototype_ `virtual void StartupModule() override;`
- L12 _public prototype_ `virtual void ShutdownModule() override;`
- L14 _protected prototype_ `void TraceFilterClasses();`
- L16 _protected prototype_ `void HandleNewFilterBlueprintCreated(class UBlueprint* InBlueprint);`

### `Plugins/Developer/TraceSourceFiltering/Source/SourceFilteringTrace/Public/DataSourceFilter.h` (Public)


#### class `UDataSourceFilter`  
`class UDataSourceFilter : public UObject, public IDataSourceFilterInterface`  
_L12-42_
- reflection: `UCLASS(MinimalAPI, Blueprintable)`
- inherits: `UObject,IDataSourceFilterInterface`
- L19 _public prototype_ `UDataSourceFilter();`
- L20 _public prototype_ `virtual ~UDataSourceFilter();`
- L23 _public prototype_ `bool DoesActorPassFilter(const AActor* InActor) const;` — `UFUNCTION(BlueprintNativeEvent, Category = TraceSourceFiltering)`
- L24 _public prototype_ `virtual bool DoesActorPassFilter_Implementation(const AActor* InActor) const;`
- L27 _public prototype_ `virtual void SetEnabled(bool bState) override;` — Begin IDataSourceFilterInterface overrides
- L28 _public prototype_ `virtual bool IsEnabled() const final;`
- L29 _public prototype_ `virtual const FDataSourceFilterConfiguration& GetConfiguration() const final;`
- L31 _protected prototype_ `virtual void GetDisplayText_Internal(FText& OutDisplayText) const override;`
- L34 _protected prototype_ `virtual bool DoesActorPassFilter_Internal(const AActor* InActor) const;`
- L38 _protected member_ `FDataSourceFilterConfiguration Configuration;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Filtering)` — Filter specific settings
- L41 _protected member_ `bool bIsEnabled;` — Whether or not this filter is enabled

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API SOURCEFILTERINGTRACE_API`

### `Plugins/Developer/TraceSourceFiltering/Source/SourceFilteringTrace/Public/DataSourceFilterSet.h` (Public)


#### class `UDataSourceFilterSet`  
`class UDataSourceFilterSet : public UDataSourceFilter, public IDataSourceFilterSetInterface`  
_L14-44_
- reflection: `UCLASS(MinimalAPI, NotBlueprintable)`
- inherits: `UDataSourceFilter,IDataSourceFilterSetInterface`
- desc: Engine implementation of IDataSourceFilterSetInterface
- L22 _public function_ `const TArray<TObjectPtr<UDataSourceFilter>>& GetFilters() const`
- L23 _public prototype_ `void SetFilterMode(EFilterSetMode InMode);`
- L26 _public prototype_ `virtual EFilterSetMode GetFilterSetMode() const override;` — Begin IDataSourceFilterSetInterface overrides
- L30 _public prototype_ `virtual void SetEnabled(bool bState) override;` — Begin UDataSourceFilter overrides
- L32 _protected prototype_ `virtual bool DoesActorPassFilter_Internal(const AActor* InActor) const override;`
- L33 _protected prototype_ `virtual void GetDisplayText_Internal(FText& OutDisplayText) const override;`
- L39 _protected member_ `TArray<TObjectPtr<UDataSourceFilter>> Filters;` — `UPROPERTY()` — Contained Filter instance
- L43 _protected member_ `EFilterSetMode Mode;` — `UPROPERTY()` — Current Filter set operation

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API SOURCEFILTERINGTRACE_API`

### `Plugins/Developer/TraceSourceFiltering/Source/SourceFilteringTrace/Public/EmptySourceFilter.h` (Public)


#### class `UEmptySourceFilter`  
`class UEmptySourceFilter : public UDataSourceFilter`  
_L11-29_
- reflection: `UCLASS(MinimalAPI, NotBlueprintable, hidedropdown)`
- inherits: `UDataSourceFilter`
- desc: Source filter implementation used to replace filter instance who's UClass is not loaded and or does not exist, primarily used by Filter Preset loading
- L17 _public member_ `FString MissingClassName;` — `UPROPERTY()`
- L20 _protected function_ `virtual bool DoesActorPassFilter_Internal(const AActor* InActor) const override`
- L25 _protected function_ `virtual void GetDisplayText_Internal(FText& OutDisplayText) const override`

### `Plugins/Developer/TraceSourceFiltering/Source/SourceFilteringTrace/Public/SourceFilterCollection.h` (Public)


#### class `USourceFilterCollection`  
`class USourceFilterCollection : public UDataAsset`  
_L17-125_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UDataAsset`
- L21 _public prototype_ `virtual ~USourceFilterCollection() = default;`
- L24 _public prototype_ `virtual void Serialize(FArchive& Ar) override;` — Begin UDataAsset overrides
- L28 _public prototype_ `FSimpleMulticastDelegate& GetSourceFiltersUpdated();` — Delegate which is broadcasted any of this collection's state changes
- L31 _public prototype_ `void AddFilter(UDataSourceFilter* NewFilter);` — Add Filter instance to the collection, will be added at the root level
- L34 _public prototype_ `UDataSourceFilter* AddFilterOfClass(const TSubclassOf<UDataSourceFilter>& FilterClass);` — Add a Filter instance of the provided class, will be added at the root level
- L36 _public prototype_ `UDataSourceFilter* AddFilterOfClassToSet(const TSubclassOf<UDataSourceFilter>& FilterClass, UDataSourceFilterSet* FilterSet);` — Add a Filter instance of the provided class, added to the provided filter set
- L39 _public prototype_ `void RemoveFilter(UDataSourceFilter* ToRemoveFilter);` — Remove Filter instance, regardless of whether it is a root-level filter or part of a filter set
- L41 _public prototype_ `void RemoveFilterFromSet(UDataSourceFilter* ToRemoveFilter, UDataSourceFilterSet* FilterSet);` — Remove a Filter Instance from a specific Filter Set
- L44 _public prototype_ `void ReplaceFilter(UDataSourceFilter* Destination, UDataSourceFilter* Source);` — Replace a Filter Instance with another
- L47 _public prototype_ `void MoveFilter(UDataSourceFilter* Filter, UDataSourceFilterSet* Destination);` — Move a Filter instance to a specific Filter Set (moved to root-level if Destination = nullptr)
- L50 _public prototype_ `void SetFilterState(UDataSourceFilter* Filter, bool bEnabledState);` — Sets whether or not a filter is enabled
- L53 _public prototype_ `UDataSourceFilterSet* ConvertFilterToSet(UDataSourceFilter* ReplacedFilter, EFilterSetMode Mode);` — Convert a Filter Instance to a Filter Set (with provided mode), this creates set containing the replace filter
- L55 _public prototype_ `UDataSourceFilterSet* MakeFilterSet(UDataSourceFilter* FilterOne, UDataSourceFilter* FilterTwo, EFilterSetMode Mode);` — Create a Filter set (with provided mode) containing both Filter Instances
- L57 _public prototype_ `void SetFilterSetMode(UDataSourceFilterSet* FilterSet, EFilterSetMode Mode);` — Set the filtering mode for the provided filter set
- L60 _public prototype_ `UDataSourceFilterSet* MakeEmptyFilterSet(EFilterSetMode Mode);` — Creates an empty Filter Set (with provided mode)
- L63 _public prototype_ `void AddFiltersFromPreset(const TArray<FString>& ClassNames, const TMap<int32, int32>& ChildToParentIndices);` — Creates a new collection of filter (sets), provided the filter class names and parent/child relationship
- L66 _public prototype_ `void Reset();` — Resets all contained filter data
- L69 _public function_ `const TArray<UDataSourceFilter*>& GetFilters() const` — Returns all top-level Filter instances
- L72 _public prototype_ `void GetFlatFilters(TArray<TObjectPtr<UDataSourceFilter>>& OutFilters);` — Returns flattened Filter instances
- L75 _public prototype_ `void CopyData(USourceFilterCollection* OtherCollection);` — Copies Filter data from other provided Filter Collection
- L78 _public prototype_ `void AddClassFilter(TSubclassOf<AActor> InClass);` — Add a class filter, used to filter AActors on a high-level
- L79 _public prototype_ `void RemoveClassFilter(TSubclassOf<AActor> InClass);`
- L81 _public function_ `const TArray<FActorClassFilter>& GetClassFilters() const` — Returns all class filters
- L83 _public prototype_ `void UpdateClassFilter(TSubclassOf<AActor> InClass, bool bIncludeDerivedClasses);` — Updating whether or not classes derived from the filter class should be included when applying filtering
- L86 _public prototype_ `void OnObjectsReplaced(const TMap<UObject*, UObject*>& OldToNewInstanceMap);` — Callback for patching up contained UDataSourceFilter blueprint instances which just got re-instanced
- L89 _public prototype_ `UDataSourceFilterSet* GetParentForFilter(UDataSourceFilter* Filter);` — Returns parent filter set, if any, for provided filter
- L92 _protected prototype_ `void RemoveFilterRecursive(UDataSourceFilter* ToRemoveFilter);` — Recursively removes filter and any contained child filters
- L94 _protected prototype_ `void AddFilterToSet(UDataSourceFilter* Filter, UDataSourceFilterSet* FilterSet);`
- L97 _protected prototype_ `void AddClassName(UDataSourceFilter* Filter);` — Adds unique filter class name
- L98 _protected prototype_ `void RecursiveRetrieveFilterClassNames(UDataSourceFilter* Filter);`
- L99 _protected prototype_ `void RecursiveGenerateFilterClassNames(UDataSourceFilter* Filter);`
- L100 _protected prototype_ `UDataSourceFilter* RecursiveCopyFilter(UDataSourceFilter* Filter, int32& FilterOffset);`
- L102 _protected prototype_ `template<typename T> T* CreateNewFilter(UClass* Class = T::StaticClass());`
- L103 _protected prototype_ `template<typename T> T* CreateNewFilter(UClass* Class = T::StaticClass());`
- L107 _protected member_ `TArray<TObjectPtr<UDataSourceFilter>> Filters;` — `UPROPERTY(VisibleAnywhere, Category=Filtering)` — Root-level filter instances
- L111 _protected member_ `TArray<FActorClassFilter> ClassFilters;` — `UPROPERTY(VisibleAnywhere, Category = Filtering)` — Class filters, used for high-level filtering of AActor instances inside of a UWorld
- L114 _protected member_ `TMap<FObjectKey, FString> FilterClassMap;` — Mapping from Filter Instance FObjectKeys to their class names
- L118 _protected member_ `TArray<FString> FilterClasses;` — `UPROPERTY()` — Flat version of the Filter classes contained by this collection, stored according to Filters ordering, with child filters inline
- L122 _protected member_ `TMap<TObjectPtr<UDataSourceFilter>, TObjectPtr<UDataSourceFilterSet>> ChildToParent;` — `UPROPERTY()` — Child / Parent mapping for Filter (sets)
- L124 _protected member_ `FSimpleMulticastDelegate SourceFiltersUpdatedDelegate;`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API SOURCEFILTERINGTRACE_API`

### `Plugins/Developer/TraceSourceFiltering/Source/SourceFilteringTrace/Public/SourceFilterTrace.h` (Public)


#### struct `FSourceFilterTrace`  
`struct FSourceFilterTrace`  
_L29-75_
- L32 _public prototype_ `static void OutputClass(const TSubclassOf<UDataSourceFilter> InClass);` — Output trace data for a UDataSourceFilter (sub) class
- L34 _public prototype_ `static void OutputInstance(const UDataSourceFilter* InFilter);` — Output trace data for a UDataSourceFilter object instance
- L36 _public prototype_ `static void OutputSet(const UDataSourceFilterSet* InFilterSet);` — Output trace data for a UDataSourceFilterSet object instance
- L38 _public prototype_ `static void OutputFilterOperation(const UDataSourceFilter* InFilter, ESourceActorFilterOperation Operation, uint64 Parameter);` — Output trace data for an operation involving a UDataSourceFilter(Set) instance
- L41 _public prototype_ `static void OutputFilterSettingsValue(const FString& InPropertyName, const uint8 InValue);` — Output trace data for a change in the UTraceSourceFilteringSettings for this running instance
- L44 _public prototype_ `static void OutputWorld(const UWorld* InWorld);` — Output trace data for a UWorld's filtering related information
- L46 _public prototype_ `static void OutputWorldOperation(const UWorld* InWorld, EWorldFilterOperation Operation, uint32 Parameter);` — Output trace data for an operation involving a UWorld instance
- L49 _public prototype_ `static UClass* RetrieveClassById(uint64 ClassId);` — Tries to retrieve a UClass instance according to its Object Identifier
- L51 _public prototype_ `static UClass* RetrieveClassByName(const FString& ClassName);` — Tries to retrieve a UClass instance according to its name
- L54 _public prototype_ `static UDataSourceFilter* RetrieveFilterbyId(uint64 FilterId);` — Tries to retrieve a UDataSourceFilter instance according to its Object Identifier
- L56 _public prototype_ `static UWorld* RetrieveWorldById(uint64 WorldId);` — Tries to retrieve a UWorld instance according to its Object Identifier
- L60 _protected member_ `static TMap<FObjectKey, uint64> FilterClassIds;` — Mapping from a UClass's ObjectKey to their Object identifier retrieved from FObjectTrace::GetObjectId
- L62 _protected member_ `static TMap<uint64, FObjectKey> IDToFilterClass;` — Mapping from a UClass's Object identifier to an FObjectKey
- L65 _protected member_ `static TMap<uint64, FObjectKey> IDToFilter;` — Mapping from a UDataSourceFilter's Object identifier to their FObjectKey
- L68 _protected member_ `static TSet<FObjectKey> FilterInstances;` — Set of FObjectKey's, representing UDataSourceFilter instances, which have previously been traced out
- L71 _protected member_ `static TMap<FString, FObjectKey> DataSourceFilterClasses;` — Mapping from an UClass's (sub class of UDataSourceFilter) name to their FObjectKey
- L74 _protected member_ `static TMap<uint64, FObjectKey> IDsToWorldInstance;` — Mapping from an Object identifier (generated from a UWorld instance) to its FObjectKey

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API SOURCEFILTERINGTRACE_API`
- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace Trace` (scope `UE`)
- L18 _macro_ `#define SOURCE_FILTER_TRACE_ENABLED 1`
- L20 _macro_ `#define SOURCE_FILTER_TRACE_ENABLED 0`
- L77 _macro_ `#define TRACE_FILTER_CLASS(Class) \`
- L80 _macro_ `#define TRACE_FILTER_INSTANCE(Instance) \`
- L83 _macro_ `#define TRACE_FILTER_SET(Set) \`
- L86 _macro_ `#define TRACE_FILTER_OPERATION(Instance, Operation, Parameter) \`
- L89 _macro_ `#define TRACE_FILTER_SETTINGS_VALUE(Name, Value) \`
- L92 _macro_ `#define TRACE_WORLD_INSTANCE(World) \`
- L95 _macro_ `#define TRACE_WORLD_OPERATION(Instance, Operation, Parameter) \`
- L98 _macro_ `#define TRACE_FILTER_IDENTIFIER(Object) \`
- L102 _macro_ `#define TRACE_FILTER_CLASS(Class)`
- L103 _macro_ `#define TRACE_FILTER_INSTANCE(Filter)`
- L104 _macro_ `#define TRACE_FILTER_SET(Set)`
- L105 _macro_ `#define TRACE_FILTER_OPERATION(Instance, Operation, Parameter)`
- L106 _macro_ `#define TRACE_FILTER_SETTINGS_VALUE(Name, Value)`
- L108 _macro_ `#define TRACE_WORLD_INSTANCE(World)`
- L109 _macro_ `#define TRACE_WORLD_OPERATION(Instance, Operation, Parameter)`
- L111 _macro_ `#define TRACE_FILTER_IDENTIFIER(Object) 0`

### `Plugins/Developer/TraceSourceFiltering/Source/SourceFilteringTrace/Public/TraceSourceFiltering.h` (Public)


#### class `FTraceSourceFiltering`  
`class FTraceSourceFiltering : public FGCObject`  
_L14-52_
- inherits: `FGCObject`
- desc: Object managing the currently active UDataSourceFilter instances and UTraceSourceFilteringSettings
- L17 _public prototype_ `static void Initialize();`
- L18 _public prototype_ `static FTraceSourceFiltering& Get();`
- L21 _public prototype_ `USourceFilterCollection* GetFilterCollection();` — Returns the running instance its Filter Collection, containing active set of filters
- L23 _public prototype_ `UTraceSourceFilteringSettings* GetSettings();` — Returns the running instance its Filtering Settings
- L26 _public prototype_ `void ProcessRemoteCommand(const FString& Command, const TArray<FString>& Arguments);` — Processes an received filtering command, altering the Filter Collection and or Settings accordingly
- L29 _public prototype_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override;` — Begin FGCObject overrides
- L30 _public function_ `virtual FString GetReferencerName() const override`
- L36 _protected prototype_ `FTraceSourceFiltering();`
- L37 _protected prototype_ `void PopulateRemoteTraceCommands();`
- L40 _protected member_ `TObjectPtr<UTraceSourceFilteringSettings> Settings;`
- L41 _protected member_ `TObjectPtr<USourceFilterCollection> FilterCollection;`
- L51 _protected member_ `TMap<FString, FFilterCommand> CommandMap;` — Mapping for all filtering commands from their name to respective FFilterCommand object

#### struct `FTraceSourceFiltering::FFilterCommand`  
`struct FFilterCommand`  
_L44-48_
- desc: Structure representing a remotely 'callable' filter command
- L46 _public member_ `TFunction<void(const TArray<FString>&)> Function;`
- L47 _public member_ `int32 NumExpectedArguments;`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API SOURCEFILTERINGTRACE_API`

### `Plugins/Developer/TraceSourceFiltering/Source/SourceFilteringTrace/Public/TraceSourceFilteringProjectSettings.h` (Public)


#### class `UTraceSourceFilteringProjectSettings`  
`class UTraceSourceFilteringProjectSettings : public UDeveloperSettings`  
_L14-24_
- reflection: `UCLASS(MinimalAPI, config = Engine, meta = (DisplayName = "Trace Source Filtering"), defaultconfig)`
- inherits: `UDeveloperSettings`
- L20 _public member_ `TArray<TSoftClassPtr<UDataSourceFilter>> CookedSourceFilterClasses;` — `UPROPERTY(config, EditAnywhere, Category = TraceSourceFiltering, AdvancedDisplay, meta = (DisplayName = "Source Filter Classes, which should be incorporated into the cook", RelativeToGameContentDir))`
- L23 _public member_ `TSoftObjectPtr<USourceFilterCollection> DefaultFilterPreset;` — `UPROPERTY(config, EditAnywhere, Category = TraceSourceFiltering, AdvancedDisplay, meta = (DisplayName = "Default Filter preset, which should be loaded during boot", RelativeToGameContentDir))`

### `Plugins/Developer/TraceSourceFiltering/Source/SourceFilteringTrace/Public/TraceSourceFilteringTestBase.h` (Public)


#### class `FTraceSourceFilteringTestBase`  
`class FTraceSourceFilteringTestBase : public FAutomationTestBase`  
_L19-154_
- inherits: `FAutomationTestBase`
- desc: Base class for setting up functional Trace Source Filtering tests
- L22 _public function_ `FTraceSourceFilteringTestBase(const FString& InName, bool bIsComplex) : FAutomationTestBase(InName, bIsComplex), NumTicks(1)`
- L23 _public prototype_ `virtual ~FTraceSourceFilteringTestBase() = default;`
- L26 _public function_ `virtual EAutomationTestFlags GetTestFlags() const override` — Begin FAutomationTestBase overrides
- L27 _public function_ `virtual bool IsStressTest() const`
- L28 _public function_ `virtual uint32 GetRequiredDeviceNum() const override`
- L29 _public prototype_ `virtual bool RunTest(const FString& Parameters) override;`
- L102 _protected prototype_ `virtual void SetupTest(const FString& Parameters) = 0;` — Function used for setting up the test data, required to be implemented for a given test
- L105 _protected prototype_ `FFilterSet& AddFilterSet(EFilterSetMode InMode);` — Adds a filter set, with the provided mode to the setup
- L109 _protected function_ `template<typename T> FFilter<T>& AddFilter()` — Adds a filter for the provided class to the test filtering state
- L120 _protected function_ `template<typename T> T* AddActor(bool bExpectedFilteringState)` — Adds an actor and its expected filtering state (at the end of running the test) to the setup
- L129 _private prototype_ `void Init();`
- L130 _private prototype_ `void TickFiltering();`
- L131 _private prototype_ `void ManualTick();`
- L132 _private prototype_ `bool CompareExpectedResults();`
- L133 _private prototype_ `void Cleanup();`
- L134 _private prototype_ `void Reset();`
- L137 _protected member_ `TStrongObjectPtr<UWorld> World;` — Pocket world used for testing
- L139 _protected member_ `FSourceFilterManager* Manager;` — Manager representing World's filtering state
- L141 _protected member_ `FPreviewScene* PreviewScene;` — Preview scene used to setup the pocket world
- L143 _protected member_ `USourceFilterCollection* FilterCollection;` — Cached filter collection singleton ptr
- L146 _protected member_ `TIndirectArray<FFilterSet> FilterSets;` — Contained filter (sets)
- L147 _protected member_ `TIndirectArray<IFilter> Filters;`
- L150 _protected member_ `TMap<AActor*, bool> ActorExpectedFilterResults;` — Map from setup actor instances to its expected filtering state
- L153 _protected member_ `uint32 NumTicks;` — Total number of ticks this test is required to perform

#### class `FTraceSourceFilteringTestBase::IFilter`  
`class IFilter`  
_L34-38_
- desc: Helper classes to make it easier to setup the test filter data
- L37 _public prototype_ `virtual ~IFilter() = default;`

#### class `FTraceSourceFilteringTestBase::FFilter`  
`template<typename T> class FFilter : public IFilter`  
_L41-64_
- inherits: `IFilter`
- L46 _public function_ `T* operator->() const`
- L51 _public function_ `T* operator*() const`
- L57 _protected function_ `FFilter(T* InFilter) : Filter(InFilter)`
- L61 _protected prototype_ `virtual ~FFilter() = default;`
- L63 _protected member_ `T* Filter;`

#### class `FTraceSourceFilteringTestBase::FFilterSet`  
`class FFilterSet`  
_L66-98_
- L72 _public function_ `template<typename T> FFilterSet& InsertFilter(FFilter<T>& Filter)`
- L78 _public function_ `FFilterSet& InsertFilter(FFilterSet& FilterSet)`
- L85 _protected function_ `FFilterSet(USourceFilterCollection* InCollection, EFilterSetMode InMode) : Collection(InCollection)`
- L91 _protected member_ `USourceFilterCollection* Collection;` — Collection this set is part of
- L93 _protected member_ `UDataSourceFilterSet* Set;` — UObject representation for this set
- L95 _protected member_ `TArray<FFilterSet*> FilterSets;` — Contained filter sets
- L97 _protected member_ `TArray<IFilter*> Filters;` — Contained filters

### `Plugins/Developer/TraceSourceFiltering/Source/SourceFilteringTrace/Public/TraceWorldFiltering.h` (Public)


#### struct `FTraceWorldFiltering`  
`struct FTraceWorldFiltering`  
_L12-72_
- desc: UWorld specific Trace filter, marks individual instances to not be traced out (and all containing actors / objects)
- L14 _public prototype_ `DECLARE_MULTICAST_DELEGATE(FTraceWorldFilterStateChanged);`
- L16 _public prototype_ `static void Initialize();`
- L17 _public prototype_ `static void Destroy();`
- L20 _public prototype_ `static const FSourceFilterManager* GetWorldSourceFilterManager(const UWorld* World);` — Retrieve a FSourceFilterManager instance representing the source filtering for a specific, provided) World instance
- L23 _public prototype_ `static const TArray<const UWorld*>& GetWorlds();` — Return all Worlds currently tracked for Filtering
- L26 _public prototype_ `static bool IsWorldTypeTraceable(EWorldType::Type InType);` — Check whether or not a specific World Type can output Trace Data (not filtered out)
- L28 _public prototype_ `static bool IsWorldNetModeTraceable(ENetMode InNetMode);` — Check whether or not a specific World's Net Mode can output Trace Data (not filtered out)
- L31 _public prototype_ `static void SetStateByWorldType(EWorldType::Type WorldType, bool bState);` — Set whether or not a specific World Type should be filtered out (or in)
- L33 _public prototype_ `static void SetStateByWorldNetMode(ENetMode NetMode, bool bState);` — Set whether or not a specific World Net Mode should be filtered out (or in)
- L35 _public prototype_ `static void SetWorldState(const UWorld* InWorld, bool bState);` — Set whether or not a specific UWorld instance's filtering state
- L38 _public prototype_ `static void GetWorldDisplayString(const UWorld* InWorld, FString& OutDisplayString);` — Returns a user facing display string for the provided UWorld instance
- L41 _public prototype_ `static FTraceWorldFilterStateChanged& OnFilterStateChanged();` — Delegate which will be broadcast whenever the filtering state for any world (type, netmode) changes
- L45 _protected prototype_ `static void OnWorldInit(UWorld* World, const UWorld::InitializationValues IVS);` — Callbacks used to keep tracking of active (alive) UWorld instances
- L46 _protected prototype_ `static void OnWorldPostInit(UWorld* World, const UWorld::InitializationValues IVS);`
- L47 _protected prototype_ `static void OnWorldCleanup(UWorld* World, bool bSessionEnded, bool bCleanupResources);`
- L48 _protected prototype_ `static void RemoveWorld(UWorld* InWorld);`
- L50 _protected prototype_ `static void UpdateWorldFiltering();`
- L53 _protected member_ `static FDelegateHandle WorldInitHandle;`
- L54 _protected member_ `static FDelegateHandle WorldPostInitHandle;`
- L55 _protected member_ `static FDelegateHandle WorldBeginTearDownHandle;`
- L56 _protected member_ `static FDelegateHandle WorldCleanupHandle;`
- L57 _protected member_ `static FDelegateHandle PreWorldFinishDestroyHandle;`
- L60 _protected member_ `static FTraceWorldFilterStateChanged FilterStateChangedDelegate;` — Delegate for broadcasting filtering changes
- L63 _protected member_ `static TArray<const UWorld*> Worlds;` — Array of currently active and alive UWorlds
- L65 _protected member_ `static TMap<EWorldType::Type, bool> WorldTypeFilterStates;` — Per EWorldType enum entry flag, determines whether or not UWorld's of this type should be filtered out
- L67 _protected member_ `static TMap<ENetMode, bool> NetModeFilterStates;` — Per ENetMode enum entry flag, determines whether or not UWorld's using this netmode should be filtered out
- L69 _protected member_ `static FCriticalSection WorldFilterStatesCritical;` — Synchronization object for accessing WorldTypeFilterStates and NetModeFilterStates, required to ensure there is not competing access between Networking and Gamethread
- L71 _protected member_ `static TMap<const UWorld*, FSourceFilterManager*> WorldSourceFilterManagers;` — Mapping from UWorld instance to FSourceFilterManager, entries correspond to world instances in Worlds

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API SOURCEFILTERINGTRACE_API`
- L14 _delegate_ `DECLARE_MULTICAST_DELEGATE(FTraceWorldFilterStateChanged);`
