# Runtime / IoStoreOnDemand

- module root: `Source/Runtime/Experimental/IoStore/OnDemand`
- headers: 20; symbols: 863
- symbol kinds: class=21, delegate=1, enum=10, enumerator=34, function=132, macro=12, member=251, namespace=39, prototype=284, struct=47, typedef=32
- PrivateDependencyModuleNames: Analytics, CoreUObject, IndexedCacheStorage, IoStoreHttpClient, Json, RSA, S3Client
- PublicDependencyModuleNames: Core, DownlinkBandwidthManager, IoStoreOnDemandCore, TraceLog

### `Source/Runtime/Experimental/IoStore/OnDemand/Private/AtomicFlags.h` (Private)


#### class `UE::TAtomicFlags`  
`template <typename FlagType> class TAtomicFlags`  
_L11-44_
- L13 _private typedef_ `using UnderlyingType = __underlying_type(FlagType);`
- L16 _public function_ `FlagType Add(FlagType FlagsToAdd, std::memory_order Order = std::memory_order_seq_cst)`
- L21 _public function_ `FlagType Remove(FlagType FlagsToAdd, std::memory_order Order = std::memory_order_seq_cst)`
- L26 _public function_ `bool HasAny(FlagType Contains, std::memory_order Order = std::memory_order_seq_cst)`
- L31 _public function_ `FlagType Get(std::memory_order Order = std::memory_order_seq_cst) const`
- L36 _public function_ `bool TrySet(FlagType FlagsToSet, std::memory_order Order = std::memory_order_seq_cst)`
- L43 _private member_ `std::atomic<UnderlyingType> Flags{0};`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`

### `Source/Runtime/Experimental/IoStore/OnDemand/Private/CVarUtilities.h` (Private)


#### struct `FConsoleCommandUnregister`  
`struct FConsoleCommandUnregister`  
_L10-13_
- L12 _public prototype_ `void operator()(IConsoleCommand* ConsoleCommandPtr) const;`

#### Free symbols / members of external scopes

- L16 _typedef_ `using FConsoleCommandPtr = TUniquePtr<IConsoleCommand, FConsoleCommandUnregister>;` — Experimental wrapper around a registered IConsoleCommand

### `Source/Runtime/Experimental/IoStore/OnDemand/Private/DebugCommands.h` (Private)


#### class `UE::IoStore::FOnDemandDebugCommands`  
`class FOnDemandDebugCommands`  
_L19-39_
- L22 _public prototype_ `FOnDemandDebugCommands() = delete;`
- L23 _public prototype_ `FOnDemandDebugCommands(FOnDemandIoStore* OnDemandIoStore);`
- L24 _public prototype_ `~FOnDemandDebugCommands();`
- L28 _private prototype_ `void BindConsoleCommands();`
- L29 _private prototype_ `void UnbindConsoleCommands();`
- L31 _private prototype_ `void RunRequestTest(const TArray<FString>& Args) const;`
- L32 _private prototype_ `void RunLatencyTests() const;`
- L34 _private prototype_ `void RecordReplayStop();`
- L36 _private member_ `FOnDemandIoStore* OnDemandIoStore = nullptr;`
- L38 _private member_ `TArray<IConsoleCommand*> DynamicConsoleCommands;`

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace IoStore` (scope `UE`)

### `Source/Runtime/Experimental/IoStore/OnDemand/Private/DiskCacheGovernor.h` (Private)


#### class `UE::IoStore::FDiskCacheGovernor`  
`class FDiskCacheGovernor`  
_L12-73_
- L36 _public prototype_ `FDiskCacheGovernor();`
- L39 _public prototype_ `void ConfigureStreamingCache(const FConfig& Config);`
- L40 _public prototype_ `int32 TryBeginWriteToStreamingCache(uint32 DemandPercent);`
- L41 _public prototype_ `int32 EndWriteToStreamingCache(uint32 UnusedAllowance);`
- L42 _public prototype_ `void OnInstallCacheFlushed(uint64 ByteCount, uint32 OpCount);`
- L47 _private prototype_ `static void Configure(FCacheState& CacheState, const FConfig& Config);`
- L48 _private prototype_ `static int32 TryBeginWrite(FCacheState& CacheState, uint32 DemandPercent, int64 Cycles);`
- L49 _private prototype_ `static int32 TryBeginWrite(FCacheState& CacheState, uint32 DemandPercent);`
- L50 _private prototype_ `static int32 EndWrite(struct FCacheState& CacheState, uint32 UnusedAllowance);`
- L51 _private prototype_ `static int32 GetMaxWaitCycles(FCacheState& CacheState);`
- L72 _private member_ `FCacheState StreamingCacheState;`

#### struct `UE::IoStore::FDiskCacheGovernor::FAllowance`  
`struct FAllowance`  
_L15-20_
- L17 _public member_ `uint32 Bytes = 16 << 20;`
- L18 _public member_ `uint32 Ops = 32;`
- L19 _public member_ `uint32 Seconds = 60;`

#### struct `UE::IoStore::FDiskCacheGovernor::FDemand`  
`struct FDemand`  
_L22-27_
- L24 _public member_ `uint8 Threshold = 30;`
- L25 _public member_ `uint8 Boost = 60;`
- L26 _public member_ `uint8 SuperBoost = 87;`

#### struct `UE::IoStore::FDiskCacheGovernor::FConfig`  
`struct FConfig`  
_L29-34_
- L31 _public member_ `FAllowance Allowance;`
- L32 _public member_ `FDemand Demand;`
- L33 _public member_ `uint32 CommitBufferSize = 0;`

#### struct `UE::IoStore::FDiskCacheGovernor::FCacheState`  
`struct FCacheState`  
_L53-70_
- L61 _public member_ `int64 OpInterval = 0;`
- L62 _public member_ `int64 PrevCycles = 0;`
- L63 _public member_ `uint32 RunOff = 0;`
- L64 _public member_ `uint32 OpCount = 0;`
- L65 _public member_ `uint32 MaxOpCount = 0;`
- L66 _public member_ `uint32 OpAllowance = 0;`
- L67 _public member_ `std::atomic_int64_t CyclesSuspended{0};`
- L68 _public member_ `FDemand Demand;`
- L69 _public member_ `EState State = EState::Waiting;`

#### enum `UE::IoStore::FDiskCacheGovernor::FCacheState::EState`  
`enum class EState : uint8`  
_L55-59_
- L57 _public enumerator_ `Waiting`
- L58 _public enumerator_ `Rolling`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace IoStore` (scope `UE`)

### `Source/Runtime/Experimental/IoStore/OnDemand/Private/IasCache.h` (Private)


#### class `UE::IoStore::IIasCache`  
`class IIasCache`  
_L21-61_
- desc: Cache for binary blobs with a 20 byte cache key.
- L24 _public prototype_ `virtual ~IIasCache() = default;`
- L29 _public prototype_ `virtual void Abandon() = 0;` — Deletes the IAS object, dropping all data persisted to disk and releasing OS resources. As this also deletes the object thus any unique pointers should be released prior to abandonment; TUniquePtr->Release()->Abandon().
- L32 _public prototype_ `virtual void Drop() = 0;` — Clears out the cache and resets it back to the default state.
- L35 _public prototype_ `virtual bool ContainsChunk(const FIoHash& Key) const = 0;` — Returns whether the specified cache key is present in the cache.
- L40 _public prototype_ `virtual EIoErrorCode Get(const FIoHash& Key, FIoBuffer& OutData) = 0;` — Get the chunk associated with the specified cache key. If the data is already in memory it is return in OutData. Otherwise the returned status indicates if the key can be materialized or if it does not exist
- L46 _public prototype_ `virtual void Materialize(const FIoHash& Key, FIoBuffer& Dest, EIoErrorCode& Status, UE::Tasks::FTaskEvent DoneEvent) = 0;` — Materializes a cached items data from disk. The data is read into Dest so Dest must remain valid throughout. The result of the disk read is returned in Status (same lifetime needs as Dest). DoneEvent is triggered when the read succeeds, is not found, or if an IO error occurred.
- L51 _public prototype_ `virtual void Cancel(FIoBuffer& GivenDest) = 0;` — Cancels a previously request to Materialize(). Note that the materialize already can still complete as the read operation may already be in flight. If the cancel succeeds, the materialize's DoneEvent is not triggered.
- L54 _public prototype_ `virtual FIoStatus Put(const FIoHash& Key, FIoBuffer& Data) = 0;` — Insert a new chunk into the cache.
- L57 _public prototype_ `virtual FIoStatus Evict(const FIoHash& Key) = 0;` — Evict an item from the cache. For example it might be corrupt
- L60 _public prototype_ `virtual void UpdateMagicValue(uint32 MagicValue) = 0;` — Update the value initially provided by FIasCacheConfig::JournalMagic

#### struct `UE::IoStore::FIasCacheConfig`  
`struct FIasCacheConfig`  
_L63-87_
- L79 _public member_ `FStringView Name = TEXT("ias`
- L80 _public member_ `uint64 DiskQuota = 512ull << 20;`
- L81 _public member_ `uint32 MemoryQuota = 2 << 20;`
- L82 _public member_ `uint32 JournalQuota = 4 << 20;` — description in JournalCache.cpp
- L83 _public member_ `uint32 JournalMagic = 0;` — can be used to invalidate cache
- L84 _public member_ `FRate WriteRate;`
- L85 _public member_ `FDemand Demand;`
- L86 _public member_ `bool DropCache = false;`

#### struct `UE::IoStore::FIasCacheConfig::FRate`  
`struct FRate`  
_L65-70_
- L67 _public member_ `uint32 Allowance = 16 << 20;`
- L68 _public member_ `uint32 Ops = 32;`
- L69 _public member_ `uint32 Seconds = 60;`

#### struct `UE::IoStore::FIasCacheConfig::FDemand`  
`struct FDemand`  
_L72-77_
- L74 _public member_ `uint8 Threshold = 30;`
- L75 _public member_ `uint8 Boost = 60;`
- L76 _public member_ `uint8 SuperBoost = 87;`

#### Free symbols / members of external scopes

- L15 _macro_ `#define UE_ALLOW_DROP_CACHE !UE_BUILD_SHIPPING`
- L17 _namespace_ `namespace UE`
- L17 _namespace_ `namespace IoStore` (scope `UE`)
- L89 _prototype_ `TUniquePtr<IIasCache> MakeIasCache(const TCHAR* RootDir, const FIasCacheConfig& Config, class FDiskCacheGovernor& Governor);` (scope `UE::IoStore`)

### `Source/Runtime/Experimental/IoStore/OnDemand/Private/IasHostGroup.h` (Private)


#### class `UE::IoStore::FIASHostGroup`  
`class FIASHostGroup final`  
_L16-68_
- L19 _private typedef_ `using FSharedImpl = TSharedPtr<FImpl, ESPMode::ThreadSafe>;`
- L22 _public prototype_ `static TIoStatusOr<FIASHostGroup> Create(FName Name, TConstArrayView<FAnsiString> HostUrls);`
- L23 _public prototype_ `static TIoStatusOr<FIASHostGroup> Create(FName Name, TConstArrayView<FString> HostUrls);`
- L25 _public prototype_ `FIASHostGroup();`
- L26 _public prototype_ `FIASHostGroup(FName Name, FAnsiStringView TestPath);`
- L27 _public prototype_ `FIASHostGroup(FName Name, FOnDemandHostGroup&& HostGroup);`
- L28 _public prototype_ `~FIASHostGroup() = default;`
- L30 _public prototype_ `FName GetName() const;`
- L31 _public prototype_ `const FAnsiString& GetTestPath() const;`
- L33 _public prototype_ `bool IsResolved() const;`
- L34 _public prototype_ `bool IsConnected() const;`
- L36 _public prototype_ `FIoStatus Resolve(TConstArrayView<FAnsiString> HostUrls);`
- L37 _public prototype_ `FIoStatus Resolve(TConstArrayView<FString> HostUrls);`
- L39 _public prototype_ `void Connect(int32 HostIndex);`
- L40 _public prototype_ `bool Disconnect();`
- L49 _public prototype_ `EReconnectionResult AttemptReconnection(bool bForce, uint32 TimeoutMs, std::atomic_bool& CancellationToken);`
- L51 _public prototype_ `void OnSuccessfulResponse();`
- L52 _public prototype_ `bool OnFailedResponse();`
- L54 _public prototype_ `FAnsiStringView GetPrimaryHostUrl() const;`
- L55 _public prototype_ `int32 GetPrimaryHostIndex() const;`
- L57 _public prototype_ `const FOnDemandHostGroup& GetUnderlyingHostGroup() const;`
- L59 _public prototype_ `TConstArrayView<FAnsiString> GetHostUrls() const;`
- L62 _private prototype_ `FIASHostGroup(FSharedImpl&& Impl);`
- L64 _private prototype_ `void SetPrimaryHost(int32 Index) const;`
- L65 _private prototype_ `void TrySetTestPath(FAnsiStringView TestPath);`
- L67 _private member_ `FSharedImpl Impl;`

#### enum `UE::IoStore::FIASHostGroup::EReconnectionResult`  
`enum class EReconnectionResult : uint8`  
_L42-47_
- L44 _public enumerator_ `AlreadyConnected = 0`
- L45 _public enumerator_ `Reconnected`
- L46 _public enumerator_ `FailedToConnect`

#### class `UE::IoStore::FHostGroupManager`  
`class FHostGroupManager final`  
_L70-110_
- L72 _private prototype_ `FHostGroupManager() = default;`
- L73 _private prototype_ `~FHostGroupManager() = default;`
- L76 _public prototype_ `DECLARE_TS_MULTICAST_DELEGATE(FOnHostGroupDisconnectedDelegate);`
- L78 _public prototype_ `static FHostGroupManager& Get();`
- L82 _public prototype_ `TIoStatusOr<FIASHostGroup> Register(FName Name, FAnsiStringView TestPath);` — <- Unresolved
- L83 _public prototype_ `TIoStatusOr<FIASHostGroup> Register(FName Name, TConstArrayView<FAnsiString> HostUrls);` — <- Resolved
- L85 _public prototype_ `FIASHostGroup Find(FName Name);`
- L86 _public prototype_ `void TrySetTestPath(FName Name, FAnsiStringView TestPath);`
- L89 _public prototype_ `bool ResolveInitialConnection(uint32 TimeoutMs, std::atomic_bool& CancellationToken);` — Returns true if we have tried to resolve at least one hostgroup and false if there are currently no hostgroups
- L91 _public prototype_ `void ForEachHostGroup(TFunctionRef<void (const FIASHostGroup&)> Callback) const;`
- L93 _public prototype_ `void Tick(uint32 TimeoutMs, std::atomic_bool& CancellationToken);`
- L95 _public prototype_ `void DisconnectAll();`
- L96 _public prototype_ `uint32 GetNumDisconnctedHosts() const;`
- L98 _public function_ `FOnHostGroupDisconnectedDelegate& OnHostGroupDisconncted()`
- L105 _private member_ `TArray<FIASHostGroup> HostGroups;`
- L107 _private member_ `FOnHostGroupDisconnectedDelegate HostGroupDisconnectedDelegate;`
- L109 _private member_ `mutable FRWLock Mutex;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace IoStore` (scope `UE`)
- L76 _delegate_ `DECLARE_TS_MULTICAST_DELEGATE(FOnHostGroupDisconnectedDelegate);`

### `Source/Runtime/Experimental/IoStore/OnDemand/Private/LatencyTesting.h` (Private)


#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace IoStore` (scope `UE`)
- L18 _prototype_ `void LatencyTest(FAnsiStringView Url, FAnsiStringView Path, uint32 TimeoutMs, TArrayView<int32> OutResults);` (scope `UE::IoStore`) — Tests a single url. @param Url			The url to be tested @param Path			The path on the CDN to be tested @param TimeoutMs		How long to wait for a response (in ms) before timing out @param OutResults	A pre-sized array to hold the results. One latency test will be made per element in this container.
- L30 _prototype_ `bool ConnectionTest(FAnsiStringView Url, FAnsiStringView Path, uint32 TimeoutMs);` (scope `UE::IoStore`) — An easy way to test if a valid connection can be made to a CDN or not. Instead of returning the latency to the CDN this function returns if the CDN can be contacted at all. @param Url			The url to be tested @param Path			The path on the CDN to be tested @param TimeoutMs		How long to wait for a response (in ms) before timing out @return True if the CDN can be reached and false if it cannot.
- L42 _prototype_ `int32 ConnectionTest(TConstArrayView<FAnsiString> Urls, FAnsiStringView Path, uint32 TimeoutMs, std::atomic_bool& bCancel);` (scope `UE::IoStore`) — Runs latency tests on a list of urls to find the first CDN that can be reached. @param Urls			A list of urls that should be tested @param Path			The path on the CDN(s) to be tested @param TimeoutMs		How long to wait for a response (in ms) before timing out @param bCancel		Provides a way for the caller to cancel the tests. When this bool is set to true the test will attempt to exit as fast as possible, usually when the next latency test has completed. @return				The index of the CDN that was successfully reached. INDEX_NONE will be returned if no CDN could be reached.

### `Source/Runtime/Experimental/IoStore/OnDemand/Private/OnDemandBackendStatus.h` (Private)


#### class `UE::IoStore::FBackendStatus`  
`class FBackendStatus`  
_L14-104_
- L28 _public function_ `bool IsHttpEnabled() const`
- L33 _public prototype_ `bool IsHttpEnabled(EIoChunkType ChunkType) const;`
- L35 _public function_ `bool IsCacheEnabled() const`
- L40 _public function_ `bool IsCacheWriteable() const`
- L46 _public function_ `bool IsCacheReadOnly() const`
- L52 _public function_ `void SetHttpEnabled(bool bEnabled)`
- L58 _public function_ `void SetHttpOptionalBulkEnabled(bool bEnabled)`
- L63 _public function_ `void SetCacheEnabled(bool bEnabled)`
- L68 _public prototype_ `void ToString(FStringBuilderBase& Builder) const;`
- L72 _private prototype_ `static bool IsHttpEnabled(uint8 FlagsToTest);`
- L74 _private function_ `bool HasAnyFlags(uint8 Contains) const`
- L79 _private function_ `bool HasAnyFlags(EFlags Contains) const`
- L84 _private function_ `uint8 AddFlags(EFlags FlagsToAdd)`
- L89 _private function_ `uint8 RemoveFlags(EFlags FlagsToRemove)`
- L94 _private function_ `uint8 AddOrRemoveFlags(EFlags FlagsToAddOrRemove, bool bValue)`
- L99 _private prototype_ `void AddOrRemoveFlags(EFlags FlagsToAddOrRemove, bool bValue, const TCHAR* DebugText);`
- L103 _private member_ `std::atomic<uint8> Flags{ 0 };`

#### enum `UE::IoStore::FBackendStatus::EFlags`  
`enum class EFlags : uint8`  
_L18-26_
- L20 _public enumerator_ `None = 0`
- L21 _public enumerator_ `CacheEnabled = 1 << 0`
- L22 _public enumerator_ `HttpEnabled = 1 << 1`
- L23 _public enumerator_ `HttpBulkOptionalDisabled = 1 << 2`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace IoStore` (scope `UE`)

### `Source/Runtime/Experimental/IoStore/OnDemand/Private/OnDemandConfig.h` (Private)


#### struct `UE::IoStore::FOnDemandHostGroupConfig`  
`struct FOnDemandHostGroupConfig`  
_L18-22_
- L20 _public member_ `FName HostGroupName;`
- L21 _public member_ `TArray<FAnsiString> Urls;`

#### struct `UE::IoStore::FOnDemandIoStoreConfig`  
`struct FOnDemandIoStoreConfig`  
_L24-29_
- L26 _public member_ `TArray<FOnDemandHostGroupConfig> HostConfigs;`
- L27 _public member_ `TArray<FOnDemandMountArgs> StartupMountArgs;`
- L28 _public member_ `bool bUsePerContainerTocs = false;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace IoStore` (scope `UE`)
- L31 _namespace_ `namespace Config` (scope `UE::IoStore`)
- L47 _prototype_ `int64 ParseSizeParam(FStringView Value);` (scope `UE::IoStore::Config`) — Attempts to convert the provided string to an integer. Unlike LexFromString this method supports postfixing the number with one of the following units of measurement: KB/KiB MB/MiB GB/GiB For example "1KB" would return 1024 or "1MiB" would return 1048576. Note that the SI units (KB) are treated as the IEC version (KiB). @param	Value	The string to parse the integer from. @return	The integer in the string, 0 if no valid integer was found.
- L65 _prototype_ `int64 ParseSizeParam(const TCHAR* CommandLine, const TCHAR* Param);` (scope `UE::IoStore::Config`) — Attempt to find the given Parameter in the provided CommandLine and return it's value as an integer. Unlike using FParse::Value directly this method supports postfixing the number with one of the following units of measurement: KB/KiB MB/MiB GB/GiB For example "-Param=1KB" would return 1024 or "-Param=1MiB" would return 1048576. Note that the SI units (KB) are treated as the IEC version (KiB). @param	CommandLine	The commandline to parse from. @param	Param		The parameter on the commandline to parse. @return	The parameter value as an integer, -1 if the parameter could not be found on the commandline and 0 if the parameter was not a valid integer.
- L67 _prototype_ `TIoStatusOr<FOnDemandIoStoreConfig> TryParseConfig(const TCHAR* CommandLine);` (scope `UE::IoStore::Config`)
- L69 _prototype_ `FIasCacheConfig GetStreamingCacheConfig(const TCHAR* CommandLine);` (scope `UE::IoStore::Config`)
- L71 _prototype_ `FString GetInstallCacheDirectory(const TCHAR* CommandLine);` (scope `UE::IoStore::Config`)
- L73 _prototype_ `TIoStatusOr<FOnDemandInstallCacheConfig> TryParseInstallCacheConfig(const TCHAR* CommandLine);` (scope `UE::IoStore::Config`)

### `Source/Runtime/Experimental/IoStore/OnDemand/Private/OnDemandContentInstallReplay.h` (Private)


#### struct `UE::IoStore::FOnDemandContentInstallReplay`  
`struct FOnDemandContentInstallReplay`  
_L18-132_
- L35 _public member_ `static const FGuid CustomVersionGuid;`
- L109 _public typedef_ `using FEventVariant = TVariant< FEmptyVariantState, FContentHandleEventData, FContentHandleDestroyedEventData, FInstallEventData, FCancelInstallEventData, FUpdatePriorityEventData, FInstallDestroyedEventData>;`
- L125 _public prototype_ `bool operator==(const FOnDemandContentInstallReplay& Other) const;`
- L128 _public prototype_ `static TResult<FOnDemandContentInstallReplay> Load(const FString& Filename, int64* OutFileSize = nullptr);`
- L129 _public prototype_ `static TResult<int64> Save(const FOnDemandContentInstallReplay& Replay, const FString& Filename);`
- L131 _public member_ `TArray64<FEvent> Events;`

#### enum `UE::IoStore::FOnDemandContentInstallReplay::EVersion`  
`enum class EVersion : int32`  
_L26-33_
- L28 _public enumerator_ `Invalid = 0`
- L29 _public enumerator_ `Initial`
- L31 _public enumerator_ `LatestPlusOne`
- L32 _public enumerator_ `Latest = LatestPlusOne - 1`

#### struct `UE::IoStore::FOnDemandContentInstallReplay::FHeader`  
`struct FHeader`  
_L37-47_
- L39 _public member_ `static const uint8 MagicSequence[16];`
- L41 _public prototype_ `bool IsValid() const;`
- L42 _public function_ `static int64 Size()`
- L44 _public member_ `uint8 Magic[16] = { 0 };`
- L45 _public member_ `EVersion Version = EVersion::Invalid;`
- L46 _public member_ `uint8 Pad[12] = { 0 };`

#### struct `UE::IoStore::FOnDemandContentInstallReplay::FFooter`  
`struct FFooter`  
_L50-58_
- L52 _public member_ `static const uint8 MagicSequence[16];`
- L54 _public function_ `static int64 Size()`
- L55 _public prototype_ `bool IsValid() const;`
- L57 _public member_ `uint8 Magic[16] = { 0 };`

#### struct `UE::IoStore::FOnDemandContentInstallReplay::FContentHandleEventData`  
`struct FContentHandleEventData`  
_L61-66_
- L63 _public member_ `FString DebugName;`
- L65 _public prototype_ `bool operator==(const FContentHandleEventData& Other) const = default;`

#### struct `UE::IoStore::FOnDemandContentInstallReplay::FContentHandleDestroyedEventData`  
`struct FContentHandleDestroyedEventData`  
_L68-73_
- L70 _public member_ `int64 ContentHandleEventId = -1;`
- L72 _public prototype_ `bool operator==(const FContentHandleDestroyedEventData& Other) const = default;`

#### struct `UE::IoStore::FOnDemandContentInstallReplay::FInstallEventData`  
`struct FInstallEventData`  
_L75-85_
- L77 _public member_ `FString MountId;`
- L78 _public member_ `TArray<FString> TagSets;`
- L79 _public member_ `TArray<FPackageId> PackageIds;`
- L80 _public member_ `int64 ContentHandleEventId = -1;`
- L81 _public member_ `int32 Priority = 0;`
- L82 _public member_ `EOnDemandInstallOptions Options = EOnDemandInstallOptions::None;`
- L84 _public prototype_ `bool operator==(const FInstallEventData& Other) const = default;`

#### struct `UE::IoStore::FOnDemandContentInstallReplay::FCancelInstallEventData`  
`struct FCancelInstallEventData`  
_L87-92_
- L89 _public member_ `int64 InstallEventId = -1;`
- L91 _public prototype_ `bool operator==(const FCancelInstallEventData& Other) const = default;`

#### struct `UE::IoStore::FOnDemandContentInstallReplay::FUpdatePriorityEventData`  
`struct FUpdatePriorityEventData`  
_L94-100_
- L96 _public member_ `int64 InstallEventId = -1;`
- L97 _public member_ `int32 NewPriority = 0;`
- L99 _public prototype_ `bool operator==(const FUpdatePriorityEventData& Other) const = default;`

#### struct `UE::IoStore::FOnDemandContentInstallReplay::FInstallDestroyedEventData`  
`struct FInstallDestroyedEventData`  
_L102-107_
- L104 _public member_ `int64 InstallEventId = -1;`
- L106 _public prototype_ `bool operator==(const FInstallDestroyedEventData& Other) const = default;`

#### struct `UE::IoStore::FOnDemandContentInstallReplay::FEvent`  
`struct FEvent`  
_L118-122_
- L120 _public member_ `int64 TimeOffset = 0;` — Time since start of replay
- L121 _public member_ `FEventVariant EventData;`

#### class `UE::IoStore::FOnDemandContentInstallReplayRecorder`  
`class FOnDemandContentInstallReplayRecorder`  
_L134-207_
- L137 _private member_ `static FOnDemandContentInstallReplayRecorder* Instance;`
- L140 _public prototype_ `static FOnDemandContentInstallReplayRecorder* Get();`
- L142 _public prototype_ `static void StartRecording(FOnDemandContentInstallReplayRecorder* InInstance);`
- L145 _public prototype_ `TValueOrError<FOnDemandContentInstallReplay, void> StopRecording();` — TODO: return TResult
- L148 _public prototype_ `void RecordContentHandle(UPTRINT HandleId, FString&& DebugName);` — Records the public content handle, no the internal implementation
- L150 _public prototype_ `void RecordContentHandleDestroyed(UPTRINT HandleId);`
- L152 _public prototype_ `void RecordInstall( UPTRINT RequestId, UPTRINT HandleId, const FString& MountId, const TArray<FString>& TagSets, const TArray<FPackageId>& PackageIds, int32 Priority, EOnDemandInstallOptions Options);`
- L161 _public prototype_ `void RecordInstall( UPTRINT RequestId, UPTRINT HandleId, FString&& MountId, TArray<FString>&& TagSets, TArray<FPackageId>&& PackageIds, int32 Priority, EOnDemandInstallOptions Options);`
- L170 _public prototype_ `void RecordCancel(UPTRINT RequestId);`
- L172 _public prototype_ `void RecordUpdatePriority(UPTRINT RequestId, int32 NewPriority);`
- L174 _public prototype_ `void RecordInstallDestroyed(UPTRINT RequestId);`
- L176 _public function_ `bool IsValid() const`
- L179 _private prototype_ `void StartRecordingInternal();`
- L181 _private prototype_ `void Reset(bool bInValid = false);`
- L183 _private prototype_ `int64 GetTimeOffset() const;`
- L186 _private function_ `template<typename EventType> int64 AddEvent(EventType&& InEvent)`
- L201 _private member_ `FMutex Mutex;`
- L202 _private member_ `TMap<UPTRINT, int64> ContentHandleEventToIndex;`
- L203 _private member_ `TMap<UPTRINT, int64> InstallEventToIndex;`
- L204 _private member_ `TPagedArray<FOnDemandContentInstallReplay::FEvent, 16384, FDefaultAllocator64> Events;`
- L205 _private member_ `FDateTime StartTime;`
- L206 _private member_ `bool bValid = true;`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace IoStore` (scope `UE`)

### `Source/Runtime/Experimental/IoStore/OnDemand/Private/OnDemandContentInstaller.h` (Private)


#### class `UE::IoStore::FOnDemandContentInstaller`  
`class FOnDemandContentInstaller`  
_L69-299_
- L221 _private function_ `static bool RequestSortPredicate(const FRequest& LHS, const FRequest& RHS)`
- L236 _private typedef_ `using FRequestAllocator = TSingleThreadedSlabAllocator<FRequest, 32>;`
- L240 _public prototype_ `FOnDemandContentInstaller(FOnDemandIoStore& IoStore);`
- L241 _public prototype_ `~FOnDemandContentInstaller();`
- L243 _public prototype_ `FSharedInternalInstallRequest EnqueueInstallRequest( FOnDemandInstallArgs&& Args, FOnDemandInstallCompleted&& OnCompleted, FOnDemandInstallProgressed&& OnProgress);`
- L247 _public prototype_ `void EnqueuePurgeRequest(FOnDemandPurgeArgs&& Args, FOnDemandPurgeCompleted&& OnCompleted);`
- L248 _public prototype_ `void EnqueueDefragRequest(FOnDemandDefragArgs&& Args, FOnDemandDefragCompleted&& OnCompleted);`
- L249 _public prototype_ `void EnqueueVerifyRequest(FOnDemandVerifyCacheCompleted&& OnCompleted);`
- L250 _public prototype_ `void EnqueueFlushLastAccessRequest(FOnDemandFlushLastAccessArgs&& Args, FOnDemandFlushLastAccessCompleted&& OnCompleted);`
- L251 _public prototype_ `void ScheduleReleaseContentRequestTask(UPTRINT HandleId);`
- L252 _public prototype_ `void CancelInstallRequest(FSharedInternalInstallRequest InstallRequest);`
- L253 _public prototype_ `void UpdateInstallRequestPriority(FSharedInternalInstallRequest InstallRequest, int32 NewPriority);`
- L254 _public prototype_ `void ReportAnalytics(TArray<FAnalyticsEventAttribute>& OutAnalyticsArray) const;`
- L257 _private prototype_ `bool CanExecuteRequest(FRequest& Request) const;`
- L258 _private prototype_ `void TryExecuteNextRequest();`
- L259 _private prototype_ `void ExecuteRequest(FRequest& Request);`
- L260 _private prototype_ `void PinCachedChunks( FRequest::FInstall& InstallRequest, TFunctionRef<void(int32, int32, bool)> OnChunkFound) const;`
- L263 _private prototype_ `void ProcessInstallRequest(FRequest& Request);`
- L264 _private prototype_ `void ExecuteInstallRequest(FRequest& Request);`
- L265 _private prototype_ `void ExecutePurgeRequest(FRequest& Request);`
- L266 _private prototype_ `void ExecuteDefragRequest(FRequest& Request);`
- L267 _private prototype_ `void ExecuteVerifyRequest(FRequest& Request);`
- L268 _private prototype_ `void ExectuteFlushLastAccessRequest(FRequest& Request);`
- L269 _private prototype_ `void ProcessDownloadedChunk( const FOnDemandChunkHash& Hash, uint32 RequestId, EIoErrorCode InErrorCode, uint32 HttpStatusCode, FIoBuffer&& Chunk);`
- L275 _private prototype_ `void OnProcessDownloadedChunkNotifyRequest(const FChunkHttpRequestHandle& HttpRequest, const FResult& ChunkDownloadResult, bool bChunkCancelled);`
- L276 _private prototype_ `void TryCancelHttpRequestsForInstallRequest(FRequest::FInstall& InstallRequest, int32& OutNumCancelled);`
- L277 _private prototype_ `void NotifyInstallProgress(FRequest& Request);`
- L278 _private prototype_ `void DestroyRequest(FRequest& Request);`
- L279 _private prototype_ `void CompleteInstallRequest(FRequest& Request);`
- L280 _private prototype_ `void CompletePurgeRequest(FRequest& Request);`
- L281 _private prototype_ `void CompleteDefragRequest(FRequest& Request);`
- L282 _private prototype_ `void CompleteVerifyRequest(FRequest& Request);`
- L283 _private prototype_ `void CompleteFlushLastAccessRequest(FRequest& Request);`
- L284 _private prototype_ `void Shutdown();`
- L286 _private member_ `FOnDemandIoStore& IoStore;`
- L287 _private member_ `UE::Tasks::FPipe InstallerPipe;`
- L289 _private member_ `FMutex Mutex;`
- L290 _private member_ `FRequestAllocator RequestAllocator;`
- L291 _private member_ `TArray<FRequest*> RequestQueue;`
- L292 _private member_ `TArray<FRequest*> RunningRequests;`
- L296 _private member_ `TMultiMap<FOnDemandChunkHash, FChunkDownloadRequest> PendingChunkDownloads;` — This needs to be a multimap to support cancelation. At any time, there may be multiple requests for the same iochunk but only one of them should be active with the remainder waiting on final callbacks after being cancelled. See FChunkDownloadRequest.
- L298 _private member_ `std::atomic_bool bShuttingDown{false};`

#### struct `UE::IoStore::FOnDemandContentInstaller::FChunkHttpRequestHandle`  
`struct FChunkHttpRequestHandle : public TIntrusiveListElement<FChunkHttpRequestHandle>`  
_L73-80_
- inherits: `TIntrusiveListElement<FChunkHttpRequestHandle>`
- L75 _public member_ `FChunkHttpRequestHandle* Next = nullptr;`
- L76 _public member_ `FRequest* OwnerRequest = nullptr;`
- L78 _public member_ `int32 ContainerIndex = INDEX_NONE;`
- L79 _public member_ `int32 EntryIndex = INDEX_NONE;`

#### struct `UE::IoStore::FOnDemandContentInstaller::FRequest`  
`struct FRequest`  
_L82-210_
- L146 _public typedef_ `using FRequestVariant = TVariant<FEmptyVariantState, FInstall, FPurge, FDefrag, FVerify, FFlushLastAccess>;`
- L148 _public function_ `FRequest(FOnDemandInstallArgs&& Args, FOnDemandInstallCompleted&& OnCompleted, FOnDemandInstallProgressed&& OnProgress)`
- L153 _public function_ `FRequest(FOnDemandPurgeArgs&& Args, FOnDemandPurgeCompleted&& OnCompleted)`
- L158 _public function_ `FRequest(FOnDemandDefragArgs&& Args, FOnDemandDefragCompleted&& OnCompleted)`
- L163 _public function_ `FRequest(FOnDemandVerifyCacheCompleted&& OnCompleted)`
- L168 _public function_ `FRequest(FOnDemandFlushLastAccessArgs&& Args, FOnDemandFlushLastAccessCompleted&& OnCompleted)`
- L173 _public function_ `bool IsCancelled() const`
- L174 _public function_ `bool TryCancel()`
- L179 _public function_ `bool IsOk() const`
- L180 _public function_ `FString GetErrorString() const`
- L182 _public function_ `bool IsInstall() const`
- L183 _public function_ `bool IsPurge() const`
- L184 _public function_ `bool IsDefrag() const`
- L185 _public function_ `bool IsVerify() const`
- L186 _public function_ `bool IsFlushLastAccess() const`
- L188 _public function_ `FInstall& AsInstall()`
- L189 _public function_ `FPurge& AsPurge()`
- L190 _public function_ `FDefrag& AsDefrag()`
- L191 _public function_ `FVerify& AsVerify()`
- L192 _public function_ `FFlushLastAccess& AsFlushLastAccess()`
- L194 _public function_ `const FInstall& AsInstall() const`
- L195 _public function_ `const FPurge& AsPurge() const`
- L196 _public function_ `const FDefrag& AsDefrag() const`
- L197 _public function_ `const FVerify& AsVerify() const`
- L198 _public function_ `const FFlushLastAccess& AsFlushLastAccess() const`
- L200 _public prototype_ `TOptional<UE::UnifiedError::FError> ConsumeError();`
- L202 _public member_ `static uint32 NextSeqNo;`
- L204 _public member_ `uint32 SeqNo = NextSeqNo++;`
- L205 _public member_ `int32 Priority = 0;`
- L206 _public member_ `uint64 StartTimeCycles = FPlatformTime::Cycles64();`
- L207 _public member_ `FResult Result = MakeValue();`
- L208 _public member_ `std::atomic_bool bCancelled{ false };`
- L209 _public member_ `FRequestVariant Variant;`

#### struct `UE::IoStore::FOnDemandContentInstaller::FRequest::FInstall`  
`struct FInstall`  
_L84-106_
- L86 _public prototype_ `FInstall( UPTRINT InstallerRequest, FOnDemandInstallArgs&& InArgs, FOnDemandInstallCompleted&& InOnCompleted, FOnDemandInstallProgressed&& InOnProgress);`
- L92 _public prototype_ `~FInstall();`
- L94 _public member_ `FOnDemandInstallArgs Args;`
- L95 _public member_ `FOnDemandInstallCompleted OnCompleted;`
- L96 _public member_ `FOnDemandInstallProgressed OnProgress;`
- L97 _public member_ `FSharedInternalInstallRequest Request;`
- L98 _public member_ `TArray<FOnDemandChunkInfoList> ResolvedChunks;`
- L99 _public member_ `TArray<FChunkHttpRequestHandle> HttpRequestHandles;`
- L100 _public member_ `FOnDemandInstallProgress Progress;`
- L101 _public member_ `uint64 DownloadedChunkCount = 0;`
- L102 _public member_ `uint64 LastProgressCycles = 0;`
- L103 _public member_ `TUniquePtr<FInstallCacheHandle> CacheHandle;`
- L104 _public member_ `bool bHttpRequestsIssued = false;`
- L105 _public member_ `std::atomic_bool bNotifyingProgressOnGameThread{false};`

#### struct `UE::IoStore::FOnDemandContentInstaller::FRequest::FPurge`  
`struct FPurge`  
_L108-116_
- L110 _public function_ `FPurge(FOnDemandPurgeArgs&& InArgs, FOnDemandPurgeCompleted&& InOnCompleted) : Args(MoveTemp(InArgs)) , OnCompleted(MoveTemp(InOnCompleted))`
- L114 _public member_ `FOnDemandPurgeArgs Args;`
- L115 _public member_ `FOnDemandPurgeCompleted OnCompleted;`

#### struct `UE::IoStore::FOnDemandContentInstaller::FRequest::FDefrag`  
`struct FDefrag`  
_L118-126_
- L120 _public function_ `FDefrag(FOnDemandDefragArgs&& InArgs, FOnDemandDefragCompleted&& InOnCompleted) : Args(MoveTemp(InArgs)) , OnCompleted(MoveTemp(InOnCompleted))`
- L124 _public member_ `FOnDemandDefragArgs Args;`
- L125 _public member_ `FOnDemandDefragCompleted OnCompleted;`

#### struct `UE::IoStore::FOnDemandContentInstaller::FRequest::FVerify`  
`struct FVerify`  
_L128-134_
- L130 _public function_ `FVerify(FOnDemandVerifyCacheCompleted&& InOnCompleted) : OnCompleted(MoveTemp(InOnCompleted))`
- L133 _public member_ `FOnDemandVerifyCacheCompleted OnCompleted;`

#### struct `UE::IoStore::FOnDemandContentInstaller::FRequest::FFlushLastAccess`  
`struct FFlushLastAccess`  
_L136-144_
- L138 _public function_ `FFlushLastAccess(FOnDemandFlushLastAccessArgs&& InArgs, FOnDemandFlushLastAccessCompleted&& InOnCompleted) : Args(MoveTemp(InArgs)) , OnCompleted(MoveTemp(InOnCompleted))`
- L142 _public member_ `FOnDemandFlushLastAccessArgs Args;`
- L143 _public member_ `FOnDemandFlushLastAccessCompleted OnCompleted;`

#### struct `UE::IoStore::FOnDemandContentInstaller::FChunkDownloadRequest`  
`struct FChunkDownloadRequest`  
_L212-219_
- L214 _public member_ `FIoHttpRequest HttpHandle;`
- L215 _public member_ `TIntrusiveList<FChunkHttpRequestHandle> ChunkRequestHttpHandles;`
- L217 _public member_ `uint32 RequestId = 0;` — Should only be used to compare two requests for the same iochunk, otherwise RequestId is not unique
- L218 _public member_ `bool bChunkCanceled = false;`

#### Free symbols / members of external scopes

- L26 _namespace_ `namespace UE`
- L26 _namespace_ `namespace IoStore` (scope `UE`)
- L33 _typedef_ `using FSharedOnDemandContainer = TSharedPtr<struct FOnDemandContainer, ESPMode::ThreadSafe>;` (scope `UE::IoStore`)
- L35 _typedef_ `using FEagerDefragChunkList = TOnDemandChunkInfoList<TInlineAllocator<64>>;` (scope `UE::IoStore`)
- L37 _namespace_ `namespace Private` (scope `UE::IoStore`)
- L42 _typedef_ `using FPackageDependencyVisitor = TFunctionRef< bool(FPackageId , EPackageStoreEntryStatus , const FPackageStoreEntry& , bool )>;` (scope `UE::IoStore::Private`) — Returns true to continue visiting dependencies
- L49 _prototype_ `void VisitPackageDependencies( const TSharedPtr<IOnDemandPackageStoreBackend>& OnDemandPackageStore, const TSet<FPackageId>& PackageIds, bool bIncludeSoftReferences, FPackageDependencyVisitor Visitor, FPackageStoreReadScope* InReadScope = nullptr);` (scope `UE::IoStore::Private`)
- L57 _prototype_ `void ResolveChunksToInstall( const TSharedPtr<IOnDemandPackageStoreBackend>& OnDemandPackageStore, const TSet<FSharedOnDemandContainer>& Containers, const TSet<FPackageId>& PackageIds, bool bIncludeSoftReferences, bool bIncludeOptionalBulkData, TArray<FOnDemandChunkInfoList>& OutResolvedContainerChunks, TSet<FIoChunkId>& OutMissing);` (scope `UE::IoStore::Private`)

### `Source/Runtime/Experimental/IoStore/OnDemand/Private/OnDemandHttpClient.h` (Private)


#### enum `UE::IoStore::EHttpRedirects`  
`enum class EHttpRedirects`  
_L46-52_
- L49 _public enumerator_ `Disabled` — Redirects will be rejected and handled as failed requests.
- L51 _public enumerator_ `Follow` — Follow redirects automatically.

#### struct `UE::IoStore::FMultiEndpointHttpClientConfig`  
`struct FMultiEndpointHttpClientConfig`  
_L54-68_
- L56 _public member_ `int32 MaxConnectionCount = 4;`
- L57 _public member_ `int32 ReceiveBufferSize = -1;`
- L58 _public member_ `int32 SendBufferSize = -1;`
- L59 _public member_ `int32 MaxRetryCount = -1;` — Positive: The number of times to retry a failed request
- L62 _public member_ `int32 TimeoutMs = 0;` — Zero: Failed requests will not be retried Negative: A failed request will retry once per provided host url
- L63 _public member_ `EHttpRedirects Redirects = EHttpRedirects::Follow;`
- L64 _public member_ `bool bEnableThreadSafetyChecks = false;`
- L65 _public member_ `bool bAllowChunkedTransfer = true;`
- L67 _public member_ `bool bResponseBodyOnError = false;` — When true the client will return the response body for requests outside of the 2XX range. When false only requests within the 2XX range will return the response body

#### enum `UE::IoStore::EMultiEndpointRequestFlags`  
`enum class EMultiEndpointRequestFlags : uint8`  
_L70-74_
- L72 _public enumerator_ `None`
- L73 _public enumerator_ `ResponseHeaders`

#### struct `UE::IoStore::FResponseBody`  
`struct FResponseBody`  
_L77-152_
- L80 _public prototype_ `FResponseBody() = default;`
- L82 _public function_ `FResponseBody(const FIoBuffer& InBody) : Body(InBody)`
- L87 _public function_ `FResponseBody(FIoBuffer&& InBody) : Body(MoveTemp(InBody))`
- L92 _public prototype_ `FResponseBody(FIoBuffer&& InBody, const FIoOffsetAndLength& Range);`
- L94 _public prototype_ `FIoStatus Parse(FIoBuffer&& Body, FAnsiStringView Boundary);`
- L103 _public function_ `uint64 GetSize() const` — Returns the total length of the body that was downloaded. Note that if the request was multi-part range then the body will include additional overhead as each range has it's own small header and so the  size will be larger than the sum of the requested ranged.
- L114 _public function_ `FIoBuffer GetBody() const` — Returns the entire body in a single buffer as it was returned from the CDN. Note that if the request was multi-part range then this buffer will include the headers for each range. It is up to the caller to manage that.
- L124 _public prototype_ `FIoBuffer GetData(const FIoOffsetAndLength& Range) const;` — Returns a view of the data for the given range. The requested range must be within the ranges for the initial request.
- L128 _private function_ `void Reset()`
- L134 _private member_ `FIoBuffer Body;` — The full body from the response
- L151 _private member_ `TArray<FRange> DataRanges;` — Views into the body of the originally requested ranges

#### struct `UE::IoStore::FResponseBody::FRange`  
`struct FRange`  
_L140-149_
- L143 _public member_ `uint32 BodyOffset = MAX_uint32;` — Offset into the Body buffer to where this range begins
- L146 _public member_ `uint32 StartByte = MAX_uint32;`
- L148 _public member_ `uint32 EndByte = 0;`

#### struct `UE::IoStore::FMultiEndpointHttpClientResponse`  
`struct FMultiEndpointHttpClientResponse`  
_L154-176_
- L156 _public function_ `bool IsOk() const`
- L161 _public function_ `bool IsCanceled() const`
- L166 _public member_ `FResponseBody Body;`
- L168 _public member_ `TArray<FAnsiString> Headers;`
- L169 _public member_ `FString Reason;`
- L170 _public member_ `HTTP::FTicketPerf::FSample Sample;`
- L171 _public member_ `uint32 StatusCode = 0;`
- L172 _public member_ `uint32 RetryCount = 0;`
- L173 _public member_ `int32 HostIndex = INDEX_NONE;`
- L174 _public member_ `bool bCanceled = false;`
- L175 _public member_ `int8 CDNCacheStatus = -1;`

#### class `UE::IoStore::FMultiEndpointHttpClient`  
`class FMultiEndpointHttpClient`  
_L188-318_
- desc: Todo - More documentation on the client behavior. Retry policy: If a request fails then the client will retry it up to FMultiEndpointHttpClientConfig::MaxRetryCount times. The first retry attempt will use the primary host with each subsequent attempt cycling to the next host in the FOnDemandHostGroup. If the end of the group is reached with retries remaining then the cycle will begin again at the start of the group. @see FOnDemandHostGroup for more info on how the host cycling works.
- L193 _public typedef_ `using FHttpTicketId = uint32;`
- L194 _public typedef_ `using FOnHttpResponse = TFunction<void(FMultiEndpointHttpClientResponse&&)>;`
- L196 _public prototype_ `~FMultiEndpointHttpClient();`
- L198 _public prototype_ `[[nodiscard]] static TUniquePtr<FMultiEndpointHttpClient> Create(const FMultiEndpointHttpClientConfig& Config);`
- L201 _public prototype_ `[[nodiscard]] static TIoStatusOr<FMultiEndpointHttpClientResponse> Get(FAnsiStringView Url, const FMultiEndpointHttpClientConfig& Config);` — Blocking method
- L203 _public prototype_ `[[nodiscard]] FHttpTicketId Get(const FOnDemandHostGroup& HostGroup, FAnsiStringView RelativeUrl, FOnHttpResponse&& OnResponse);`
- L204 _public prototype_ `[[nodiscard]] FHttpTicketId Get(const FOnDemandHostGroup& HostGroup, FAnsiStringView RelativeUrl, TArray<FIoOffsetAndLength>&& ChunkRanges, FOnHttpResponse&& OnResponse);`
- L205 _public prototype_ `[[nodiscard]] FHttpTicketId Get(const FOnDemandHostGroup& HostGroup, FAnsiStringView RelativeUrl, TArray<FIoOffsetAndLength>&& ChunkRanges, TArray<FAnsiString>&& Headers, EMultiEndpointRequestFlags Flags, FOnHttpResponse&& OnResponse);`
- L216 _public prototype_ `bool Tick(int32 WaitTimeMs, uint32 MaxKiBPerSecond);` — Process the underlying http client. @param WaitTimeMs		How long (in milliseconds) should the underlying http client wait for poll events before returning. @param MaxKiBPerSecond	The max amount of bandwidth that the underlying http client should use per second. A value of zero indicates that the bandwidth use should not be capped. @return True if the client still has work pending and more Tick calls will be needed, false if all work has been completed.
- L217 _public function_ `bool Tick()`
- L222 _public prototype_ `void CancelRequest(FHttpTicketId TicketId);`
- L224 _public prototype_ `void UpdateConnections();`
- L230 _public prototype_ `void GetHttpStats(FOnDemandHttpStats& Out) const;` — Samples the underlying http client for performance statistics and stores them in the provided FOnDemandHttpStats. Can be called from any thread, not just the http thread.
- L233 _private typedef_ `using FHttpConnectionPools = TArray<TUniquePtr<HTTP::FConnectionPool>, TInlineAllocator<4>>;`
- L284 _private prototype_ `FMultiEndpointHttpClient(const FMultiEndpointHttpClientConfig& Config);`
- L286 _private prototype_ `FHttpTicketId IssueRequest(FRequest&& Request);`
- L287 _private prototype_ `void CompleteRequest(FRequest&& Request, const UE::IoStore::HTTP::FTicketStatus& TicketStatus);`
- L288 _private prototype_ `void RetryRequest(FRequest&& Request);`
- L290 _private prototype_ `void ProcessFailedRequests();`
- L291 _private prototype_ `void ProcessRetryAttempts(uint32 TicketCount);`
- L293 _private prototype_ `TUniquePtr<HTTP::FConnectionPool> CreateConnection(FAnsiStringView HostUrl) const;`
- L294 _private prototype_ `FConnection& GetConnection(const FOnDemandHostGroup& HostGroup);`
- L295 _private prototype_ `FConnection* FindConnection(const FOnDemandHostGroup& HostGroup);`
- L297 _private prototype_ `uint32 GetRetryLimitForRequest(const FRequest& Request) const;`
- L299 _private prototype_ `void Log(const FMultiEndpointHttpClientResponse& Response, const FRequest& Request) const;`
- L300 _private prototype_ `void LogError(const FRequest& Request, const FString& ErrorReason) const;`
- L302 _private member_ `FMultiEndpointHttpClientConfig Config;`
- L303 _private member_ `TArray<TUniquePtr<FConnection>> Connections;`
- L304 _private member_ `HTTP::FEventLoop EventLoop;`
- L305 _private member_ `TArray<FRequest> Retries;`
- L307 _private member_ `TArray<FRequest> FailedRequests;` — Stores the response for requests that failed to be issued, to be flushed in the next Tick
- L315 _private member_ `UE::FRecursiveMutex TicketLookupMutex;`
- L316 _private member_ `TMap<FHttpTicketId, FTicketInfo> TicketLookupMap;`

#### struct `UE::IoStore::FMultiEndpointHttpClient::FConnection`  
`struct FConnection`  
_L235-240_
- L237 _public member_ `FOnDemandHostGroup HostGroup;`
- L238 _public member_ `FHttpConnectionPools Pools;`
- L239 _public member_ `int32 CurrentHost = INDEX_NONE;`

#### struct `UE::IoStore::FMultiEndpointHttpClient::FRequest`  
`struct FRequest`  
_L242-282_
- L244 _public member_ `FOnHttpResponse OnResponse;`
- L245 _public member_ `TArray<FAnsiString> RequestHeaders;`
- L246 _public member_ `TArray<FAnsiString> ResponseHeaders;`
- L247 _public member_ `FAnsiString RelativeUrl;`
- L248 _public member_ `TArray<FIoOffsetAndLength> Ranges;` — Consider inline storage?
- L249 _public member_ `FAnsiString MultiRangeBoundary;`
- L250 _public member_ `FHttpTicketId TicketId = 0;`
- L251 _public member_ `FConnection& Connection;`
- L253 _public member_ `FIoBuffer Body;` — Stored the response body
- L258 _public member_ `FIoBuffer Chunk;` — Stores each chunk being sent if the response uses chunked transfer, the chunks will be combined together so that the final result will be in Body once all chunks are processed.
- L260 _public member_ `FString ResponseMessage;` — Stores the response message if the StatusCode indicates a problem
- L261 _public member_ `uint64 StartTime = 0;`
- L262 _public member_ `uint32 RetryCount = 0;`
- L263 _public member_ `uint32 StatusCode = 0;`
- L264 _public member_ `int32 Host = INDEX_NONE;`
- L265 _public member_ `EMultiEndpointRequestFlags Flags = EMultiEndpointRequestFlags::None;`
- L266 _public member_ `bool bIsChunkedTransfer = false;`
- L267 _public member_ `int8 CDNCacheStatus = -1;`
- L271 _public member_ `int32 SinkCounter = 0;` — Used to make sure that the sink is only called with a completed state one per request attempt
- L275 _public prototype_ `uint64 GetTotalRangeLength() const;` — Returns the total length of all the ranges in the provided request
- L281 _public prototype_ `bool BuildRangeHeaderValue(FAnsiStringBuilderBase& OutString)const;` — Builds the value for a http 'range' header based on the ranges from the provided request. Returns true if a valid range exists and false if not.

#### struct `UE::IoStore::FMultiEndpointHttpClient::FTicketInfo`  
`struct FTicketInfo`  
_L309-313_
- L311 _public member_ `HTTP::FTicket HttpTicket;`
- L312 _public member_ `bool bCancelRequested = false;`

#### Free symbols / members of external scopes

- L22 _macro_ `#define UE_LOG_CATEGORY_TYPE FLogCategoryBase`
- L24 _macro_ `#define UE_LOG_CATEGORY_TYPE FNoLoggingCategory`
- L27 _namespace_ `namespace UE`
- L27 _namespace_ `namespace IoStore` (scope `UE`)
- L32 _prototype_ `FIoStatus LoadDefaultHttpCertificates(bool& bWasLoaded);` (scope `UE::IoStore`)
- L35 _function_ `inline bool IsHttpStatusOk(uint32 StatusCode)` (scope `UE::IoStore`) — Returns if a Http status code is okay (2XX) or not
- L41 _function_ `inline bool IsHttpServerError(uint32 StatusCode)` (scope `UE::IoStore`) — Returns if a Http status code indicates a server error (5XX) or not
- L75 _prototype_ `ENUM_CLASS_FLAGS(EMultiEndpointRequestFlags);` (scope `UE::IoStore`)

### `Source/Runtime/Experimental/IoStore/OnDemand/Private/OnDemandHttpIoDispatcher.h` (Private)


#### enum `UE::IoStore::EHttpRequestType`  
`enum class EHttpRequestType : uint8`  
_L14-20_
- desc: Describes the system making the request
- L16 _public enumerator_ `Streaming = 0`
- L17 _public enumerator_ `Installed` — Streaming = 0,	  IAS
- L19 _public enumerator_ `NUM_SOURCES`

#### class `UE::IoStore::IOnDemandHttpIoDispatcher`  
`class IOnDemandHttpIoDispatcher : public IHttpIoDispatcher`  
_L22-27_
- inherits: `IHttpIoDispatcher`
- L26 _public prototype_ `virtual ~IOnDemandHttpIoDispatcher() = default;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API IOSTOREONDEMANDCORE_API`
- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace IoStore` (scope `UE`)
- L29 _prototype_ `TSharedPtr<IOnDemandHttpIoDispatcher> MakeOnDemanHttpIoDispatcher(TUniquePtr<class IIasCache>&& Cache);` (scope `UE::IoStore`)

### `Source/Runtime/Experimental/IoStore/OnDemand/Private/OnDemandHttpIoDispatcherBackend.h` (Private)


#### class `UE::IoStore::IOnDemandHttpIoDispatcherBackend`  
`class IOnDemandHttpIoDispatcherBackend : public IIoDispatcherBackend`  
_L13-20_
- inherits: `IIoDispatcherBackend`
- L17 _public prototype_ `virtual ~IOnDemandHttpIoDispatcherBackend() = default;`
- L18 _public prototype_ `virtual void SetOptionalBulkDataEnabled(bool bEnabled) = 0;`
- L19 _public prototype_ `virtual void ReportAnalytics(TArray<FAnalyticsEventAttribute>& OutAnalyticsArray) const = 0;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace IoStore` (scope `UE`)
- L22 _prototype_ `TSharedPtr<IOnDemandHttpIoDispatcherBackend> MakeOnDemandHttpIoDispatcherBackend(class FOnDemandIoStore& IoStore);` (scope `UE::IoStore`)

### `Source/Runtime/Experimental/IoStore/OnDemand/Private/OnDemandInstallCache.h` (Private)


#### struct `UE::IoStore::FOnDemandInstallCacheStorageUsage`  
`struct FOnDemandInstallCacheStorageUsage`  
_L28-33_
- L30 _public member_ `uint64 MaxSize = 0;`
- L31 _public member_ `uint64 TotalSize = 0;`
- L32 _public member_ `uint64 ReferencedBlockSize = 0;`

#### class `UE::IoStore::FInstallCacheHandle`  
`class FInstallCacheHandle`  
_L35-39_
- L38 _public prototype_ `virtual ~FInstallCacheHandle();`

#### class `UE::IoStore::FInstallCachePurgeHandle`  
`class FInstallCachePurgeHandle`  
_L41-48_
- L44 _private member_ `EOnDemandInstallCasType CasType = EOnDemandInstallCasType::None;`
- L45 _private member_ `uint64 BytesToPurge = 0;`

#### class `UE::IoStore::IOnDemandInstallCache`  
`class IOnDemandInstallCache : public IIoDispatcherBackend`  
_L50-72_
- inherits: `IIoDispatcherBackend`
- L54 _public prototype_ `virtual ~IOnDemandInstallCache() = default;`
- L55 _public prototype_ `virtual TUniquePtr<FInstallCacheHandle> BeginInstall() = 0;`
- L56 _public prototype_ `virtual void PinCachedChunks(FInstallCacheHandle& Handle, const FOnDemandInternalContentHandle& ContentHandle, const FOnDemandChunkInfoList& Chunks, TFunctionRef<void(int32, bool)> OnChunkFound) = 0;`
- L57 _public prototype_ `virtual void PinChunks(FInstallCacheHandle& Handle, const FOnDemandInternalContentHandle& ContentHandle, const FOnDemandChunkInfoList& Chunks, TFunctionRef<void(int32)> OnChunkFound) = 0;`
- L58 _public prototype_ `virtual FResult PutChunk(EIoChunkType ChunkType, FIoBuffer&& Chunk, const FCasAddr& CasAddr) = 0;`
- L59 _public prototype_ `virtual void PostPutChunk(FInstallCacheHandle& Handle, EIoChunkType ChunkType) = 0;`
- L60 _public prototype_ `virtual FInstallCachePurgeHandle BeginPurge(EIoChunkType ChunkType) = 0;`
- L61 _public prototype_ `virtual void AddToPurge(FInstallCachePurgeHandle& Handle, EIoChunkType ChunkType, uint64 Size) = 0;`
- L62 _public prototype_ `virtual FResult Purge(const FInstallCachePurgeHandle& Handle) = 0;`
- L63 _public prototype_ `virtual FResult PurgeAllUnreferenced(EOnDemandInstallCasType CasType, bool bDefrag, const uint64* BytesToPurge = nullptr) = 0;`
- L64 _public prototype_ `virtual FResult DefragAll(EOnDemandInstallCasType CasType, const uint64* BytesToFree = nullptr) = 0;`
- L65 _public prototype_ `virtual FResult EagerDefrag(FInstallCacheHandle& Handle) = 0;`
- L66 _public prototype_ `virtual bool IsEagerDefragRequired(FInstallCacheHandle& Handle) = 0;`
- L67 _public prototype_ `virtual FResult ConditionallyFlushInstall(FInstallCacheHandle& Handle) = 0;`
- L68 _public prototype_ `virtual FResult Verify() = 0;`
- L69 _public prototype_ `virtual FResult FlushLastAccess(const TStaticArray<bool, EOnDemandInstallCasType::Count>& bFlushCasLastAccess) = 0;`
- L70 _public prototype_ `virtual void UpdateLastAccess(TConstArrayView<FCasAddr> CasAddrs, TStaticArray<bool, EOnDemandInstallCasType::Count>& bInOutLastAccessDirty) = 0;`
- L71 _public prototype_ `virtual FOnDemandInstallCacheUsage GetCacheUsage() = 0;`

#### struct `UE::IoStore::FOnDemandInstallCasConfig`  
`struct FOnDemandInstallCasConfig`  
_L74-83_
- L76 _public member_ `EOnDemandInstallCasType Type = EOnDemandInstallCasType::None;`
- L77 _public member_ `FString CasSubdirectory;`
- L78 _public member_ `uint64 DiskQuota = 1ull << 30;`
- L79 _public member_ `uint64 MinBlockSize = 32 << 19;`
- L80 _public member_ `uint64 MaxBlockSize = 32 << 20;`
- L81 _public member_ `double LastAccessGranularitySeconds = 60 * 60;`
- L82 _public member_ `uint32 EagerDefragBlockCount = 0;`

#### struct `UE::IoStore::FOnDemandInstallCacheConfig`  
`struct FOnDemandInstallCacheConfig`  
_L85-92_
- L87 _public member_ `TArray<FOnDemandInstallCasConfig> CasConfig;`
- L89 _public member_ `FString IndexedCacheStorageName;`
- L90 _public member_ `uint64 JournalMaxSize = 2ull << 20;`
- L91 _public member_ `bool bDropCache = false;`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace IoStore` (scope `UE`)
- L20 _typedef_ `using FSharedOnDemandContainer = TSharedPtr<struct FOnDemandContainer, ESPMode::ThreadSafe>;` (scope `UE::IoStore`)
- L21 _typedef_ `using FCasAddr = FHash96;` (scope `UE::IoStore`)
- L25 _typedef_ `using FOnDemandChunkInfoList = TOnDemandChunkInfoList<FDefaultAllocator>;` (scope `UE::IoStore`)
- L26 _typedef_ `using FEagerDefragChunkList = TOnDemandChunkInfoList<TInlineAllocator<64>>;` (scope `UE::IoStore`)
- L94 _prototype_ `TSharedPtr<IOnDemandInstallCache> MakeOnDemandInstallCache( FOnDemandIoStore& IoStore, const FOnDemandInstallCacheConfig& Config, FString RootDirectory, class FDiskCacheGovernor& Governor);` (scope `UE::IoStore`)

### `Source/Runtime/Experimental/IoStore/OnDemand/Private/OnDemandIoStore.h` (Private)


#### enum `UE::IoStore::EOnDemandContainerFlags`  
`enum class EOnDemandContainerFlags : uint8`  
_L47-58_
- L49 _public enumerator_ `None = 0`
- L50 _public enumerator_ `PendingEncryptionKey = (1 << 0)`
- L51 _public enumerator_ `Mounted = (1 << 1)`
- L52 _public enumerator_ `StreamOnDemand = (1 << 2)`
- L53 _public enumerator_ `InstallOnDemand = (1 << 3)`
- L54 _public enumerator_ `Encrypted = (1 << 4)`
- L55 _public enumerator_ `WithSoftReferences = (1 << 5)`
- L56 _public enumerator_ `PendingHostGroup = (1 << 6)`
- L57 _public enumerator_ `Last = PendingHostGroup`

#### struct `UE::IoStore::FOnDemandChunkEntryReferences`  
`struct FOnDemandChunkEntryReferences`  
_L71-75_
- L73 _public member_ `UPTRINT ContentHandleId = 0;`
- L74 _public member_ `TBitArray<> Indices;`

#### struct `UE::IoStore::FOnDemandContainerChunkEntryReferences`  
`struct FOnDemandContainerChunkEntryReferences`  
_L80-84_
- L82 _public member_ `FSharedOnDemandContainer Container;`
- L83 _public member_ `TBitArray<> Indices;`

#### struct `UE::IoStore::FOnDemandContainer`  
`struct FOnDemandContainer`  
_L87-125_
- L89 _public prototype_ `FString UniqueName() const;`
- L90 _public prototype_ `inline FString Name() const;`
- L91 _public function_ `FIoContainerId ContainerId() const`
- L92 _public function_ `const FGuid& EncryptionKeyGuid() const`
- L93 _public function_ `uint32 BlockSize() const`
- L94 _public prototype_ `inline int32 GetNumChunks() const;`
- L95 _public prototype_ `inline int32 FindChunkEntryIndex(const FIoChunkId& ChunkId) const;`
- L96 _public prototype_ `inline const FOnDemandChunkEntry* FindChunkEntry(const FIoChunkId& ChunkId, int32* OutIndex = nullptr) const;`
- L97 _public prototype_ `inline FOnDemandChunkEntryReferences& FindOrAddChunkEntryReferences(const FOnDemandInternalContentHandle& ContentHandle);`
- L98 _public prototype_ `inline TBitArray<> GetReferencedChunkEntries() const;`
- L99 _public prototype_ `inline bool IsReferenced(int32 ChunkEntryIndex) const;`
- L101 _public prototype_ `inline FAnsiString GetTestUrl();`
- L102 _public function_ `bool HasAnyFlags(EOnDemandContainerFlags Contains) const`
- L103 _public function_ `bool HasAllFlags(EOnDemandContainerFlags Contains) const`
- L105 _public member_ `FAES::FAESKey EncryptionKey;`
- L106 _public member_ `FOnDemandTocStorage Storage;`
- L107 _public member_ `FOnDemandContainerTocHeaderView HeaderView;`
- L108 _public member_ `FIoBuffer ContainerHeaderChunk;`
- L109 _public member_ `FSharedContainerHeader Header;`
- L110 _public member_ `FIASHostGroup HostGroup;`
- L111 _public member_ `FString MountId;`
- L112 _public member_ `TConstArrayView<FOnDemandPartitionEntry> PartitionEntries;`
- L113 _public member_ `TConstArrayView<FIoChunkId> ChunkIds;`
- L114 _public member_ `TConstArrayView<FOnDemandChunkEntry> ChunkEntries;`
- L115 _public member_ `TConstArrayView<uint32> BlockSizes;`
- L116 _public member_ `TConstArrayView<FIoBlockHash> BlockHashes;`
- L117 _public member_ `TConstArrayView<FOnDemandTagSet> TagSets;`
- L118 _public member_ `TConstArrayView<uint32> TagSetIndices;`
- L119 _public member_ `TArray<FOnDemandChunkEntryReferences> ChunkEntryReferences;`
- L120 _public member_ `FIoRelativeUrl RelativeUrl;`
- L121 _public member_ `FName CompressionFormat;`
- L122 _public member_ `FName HostGroupName = FOnDemandHostGroup::DefaultName;`
- L123 _public member_ `mutable UE::FMutex ReferencesMutex;`
- L124 _public member_ `EOnDemandContainerFlags Flags = EOnDemandContainerFlags::None;`
- L128 _function_ `inline FString FOnDemandContainer::Name() const`
- L133 _function_ `int32 FOnDemandContainer::GetNumChunks() const`
- L138 _function_ `int32 FOnDemandContainer::FindChunkEntryIndex(const FIoChunkId& ChunkId) const`
- L151 _function_ `const FOnDemandChunkEntry* FOnDemandContainer::FindChunkEntry(const FIoChunkId& ChunkId, int32* OutIndex) const`
- L165 _function_ `FOnDemandChunkEntryReferences& FOnDemandContainer::FindOrAddChunkEntryReferences(const FOnDemandInternalContentHandle& ContentHandle)`
- L184 _function_ `TBitArray<> FOnDemandContainer::GetReferencedChunkEntries() const`
- L197 _function_ `bool FOnDemandContainer::IsReferenced(int32 ChunkEntryIndex) const`
- L210 _function_ `FAnsiString FOnDemandContainer::GetTestUrl()`

#### struct `UE::IoStore::FOnDemandChunkInfo`  
`struct FOnDemandChunkInfo`  
_L230-280_
- L232 _public prototype_ `FOnDemandChunkInfo() = default;`
- L233 _public function_ `FOnDemandChunkInfo(const FOnDemandChunkInfo& Other) : SharedContainer(Other.SharedContainer) , Entry(Other.Entry)`
- L236 _public function_ `FOnDemandChunkInfo(FOnDemandChunkInfo&& Other) : SharedContainer(MoveTemp(Other.SharedContainer)) , Entry(Other.Entry)`
- L240 _public function_ `const FOnDemandChunkHash& Hash() const`
- L241 _public prototype_ `inline const FIoChunkId& Id() const;`
- L242 _public function_ `const FIoHash& PartitionHash() const`
- L243 _public function_ `uint32 PartitionOffset() const`
- L244 _public function_ `uint32 RawSize() const`
- L245 _public function_ `uint32 EncodedSize() const`
- L246 _public function_ `uint32 DiskSize() const`
- L247 _public function_ `uint32 BlockSize() const`
- L248 _public function_ `FName CompressionFormat() const`
- L249 _public function_ `FMemoryView EncryptionKey() const`
- L250 _public prototype_ `inline TConstArrayView<uint32> Blocks() const;`
- L251 _public prototype_ `inline TConstArrayView<FIoBlockHash> BlockHashes() const;`
- L252 _public function_ `FIoRelativeUrl RelativeUrl() const`
- L253 _public function_ `const FOnDemandChunkEntry& ChunkEntry() const`
- L254 _public prototype_ `inline const FIASHostGroup& HostGroup() const;`
- L255 _public function_ `FName HostGroupName() const`
- L257 _public function_ `bool IsValid() const`
- L258 _public function_ `operator bool() const`
- L260 _public prototype_ `inline static FOnDemandChunkInfo Find(FSharedOnDemandContainer Container, const FIoChunkId& ChunkId);`
- L262 _public member_ `static const FOnDemandChunkEntry NullEntry;`
- L264 _public function_ `explicit FOnDemandChunkInfo(FSharedOnDemandContainer InContainer, const FOnDemandChunkEntry& InEntry = FOnDemandChunkInfo::NullEntry) : SharedContainer(InContainer) , Entry(InEntry)`
- L278 _public member_ `FSharedOnDemandContainer SharedContainer;`
- L279 _public member_ `const FOnDemandChunkEntry& Entry = NullEntry;`
- L282 _function_ `const FIoChunkId& FOnDemandChunkInfo::Id() const`
- L293 _function_ `TConstArrayView<uint32> FOnDemandChunkInfo::Blocks() const`
- L301 _function_ `TConstArrayView<FIoBlockHash> FOnDemandChunkInfo::BlockHashes() const`
- L311 _function_ `const FIASHostGroup& FOnDemandChunkInfo::HostGroup() const`
- L316 _function_ `FOnDemandChunkInfo FOnDemandChunkInfo::Find(FSharedOnDemandContainer Container, const FIoChunkId& ChunkId)`

#### struct `UE::IoStore::FOnDemandChunkInfoListBase`  
`struct FOnDemandChunkInfoListBase`  
_L328-356_
- L330 _public prototype_ `FOnDemandChunkInfoListBase() = default;`
- L331 _public function_ `explicit FOnDemandChunkInfoListBase(FSharedOnDemandContainer InContainer) : SharedContainer(MoveTemp(InContainer))`
- L335 _public function_ `const FOnDemandChunkHash& Hash(int32 Index) const`
- L336 _public function_ `const FIoChunkId& Id(int32 Index) const`
- L337 _public function_ `const FIoHash& PartitionHash(int32 Index) const`
- L338 _public function_ `uint32 PartitionOffset(int32 Index) const`
- L339 _public function_ `uint32 RawSize(int32 Index) const`
- L340 _public function_ `uint32 EncodedSize(int32 Index) const`
- L341 _public function_ `uint32 DiskSize(int32 Index) const`
- L342 _public function_ `uint32 BlockSize() const`
- L343 _public function_ `FName CompressionFormat() const`
- L344 _public function_ `FMemoryView EncryptionKey() const`
- L345 _public prototype_ `inline TConstArrayView<uint32> Blocks(int32 Index) const;`
- L346 _public prototype_ `inline TConstArrayView<FIoBlockHash> BlockHashes(int32 Index) const;`
- L347 _public function_ `FIoRelativeUrl RelativeUrl() const`
- L348 _public function_ `const FOnDemandChunkEntry& ChunkEntry(int32 Index) const`
- L349 _public prototype_ `inline const FIASHostGroup& HostGroup() const;`
- L350 _public function_ `FName HostGroupName() const`
- L352 _public function_ `bool IsValid() const`
- L353 _public function_ `operator bool() const`
- L355 _public member_ `FSharedOnDemandContainer SharedContainer;`
- L358 _function_ `TConstArrayView<uint32> FOnDemandChunkInfoListBase::Blocks(int32 Index) const`
- L367 _function_ `TConstArrayView<FIoBlockHash> FOnDemandChunkInfoListBase::BlockHashes(int32 Index) const`
- L378 _function_ `const FIASHostGroup& FOnDemandChunkInfoListBase::HostGroup() const`

#### struct `UE::IoStore::TOnDemandChunkInfoList`  
`template<typename Allocator > struct TOnDemandChunkInfoList : public FOnDemandChunkInfoListBase`  
_L384-441_
- inherits: `FOnDemandChunkInfoListBase`
- L386 _public prototype_ `TOnDemandChunkInfoList() = default;`
- L388 _public function_ `template<typename OtherAllocator> TOnDemandChunkInfoList(const TOnDemandChunkInfoList<OtherAllocator>& Other) : FOnDemandChunkInfoListBase(Other.SharedContainer) , Indices(Other.Indices)`
- L392 _public function_ `TOnDemandChunkInfoList(TOnDemandChunkInfoList&& Other) : FOnDemandChunkInfoListBase(MoveTemp(Other.SharedContainer)) , Indices(MoveTemp(Other.Indices))`
- L397 _public function_ `explicit TOnDemandChunkInfoList(FSharedOnDemandContainer InContainer) : FOnDemandChunkInfoListBase(MoveTemp(InContainer))`
- L402 _public function_ `template<typename OtherAllocator> explicit TOnDemandChunkInfoList(FSharedOnDemandContainer InContainer, const TArray<int32, OtherAllocator>& InIndices) : FOnDemandChunkInfoListBase(MoveTemp(InContainer)) , Indices(InIndices)`
- L408 _public function_ `template<typename OtherAllocator> explicit TOnDemandChunkInfoList(FSharedOnDemandContainer InContainer, TArray<int32, OtherAllocator>&& InIndices) : FOnDemandChunkInfoListBase(MoveTemp(InContainer)) , Indices(MoveTemp(InIndices))`
- L413 _public function_ `inline uint64 TotalDiskSize() const`
- L424 _public function_ `inline static TOnDemandChunkInfoList Find(FSharedOnDemandContainer Container, TConstArrayView<FIoChunkId> ChunkIds)`
- L440 _public member_ `TArray<int32, Allocator> Indices;`

#### struct `UE::IoStore::FOnDemandFlushLastAccessArgs`  
`struct FOnDemandFlushLastAccessArgs`  
_L447-451_
- desc: Flush last access args.
- L449 _public member_ `TArray<TPair<FSharedOnDemandContainer, TBitArray<>>> RemovedChunkEntryReferences;`
- L450 _public member_ `bool bForceLastAccessDirty = true;`

#### struct `UE::IoStore::FOnDemandFlushLastAccessResult`  
`struct FOnDemandFlushLastAccessResult`  
_L454-462_
- desc: Result from flushing cache last access times.
- L457 _public function_ `bool IsOk() const` — Returns True if the request succeeded.
- L459 _public member_ `double DurationInSeconds = 0.0;` — Duration in seconds.
- L461 _public member_ `TOptional<UE::UnifiedError::FError> Error;` — Error information about the request.

#### class `UE::IoStore::FOnDemandIoStore`  
`class FOnDemandIoStore : public TSharedFromThis<FOnDemandIoStore, ESPMode::ThreadSafe> , public IOnDemandIoStore`  
_L468-581_
- inherits: `TSharedFromThis<FOnDemandIoStore,ESPMode::ThreadSafe>,IOnDemandIoStore`
- L479 _private typedef_ `using FSharedMountRequest = TSharedRef<FMountRequest>;`
- L484 _public prototype_ `FOnDemandIoStore();`
- L485 _public prototype_ `~FOnDemandIoStore();`
- L487 _public prototype_ `FOnDemandChunkInfo GetStreamingChunkInfo(const FIoChunkId& ChunkId);`
- L488 _public prototype_ `FOnDemandChunkInfo GetInstalledChunkInfo(const FIoChunkId& ChunkId, EIoErrorCode& OutErrorCode);`
- L492 _public prototype_ `TArray<FIoChunkId> DebugFindStreamingChunkIds(int32 NumToFind);` — Used to access a number of FIoChunkId that exist in the system when running tests and is not intended for production use
- L494 _public prototype_ `void GetReferencedContent(TArray<FSharedOnDemandContainer>& OutContainers, TArray<TBitArray<>>& OutChunkEntryIndices, bool bPackageStore = false);`
- L495 _public prototype_ `TBitArray<> GetReferencedContent(const FSharedOnDemandContainer& Container);`
- L496 _public prototype_ `void GetReferencedContentByHandle(TMap<FOnDemandWeakContentHandle, TArray<FOnDemandContainerChunkEntryReferences>>& OutReferencesByHandle) const;`
- L499 _public prototype_ `virtual FIoStatus Initialize() override;` — IOnDemandIoStore interface
- L500 _public prototype_ `virtual FIoStatus InitializePostHotfix() override;`
- L501 _public prototype_ `virtual FOnDemandRegisterHostGroupResult RegisterHostGroup(FOnDemandRegisterHostGroupArgs&& Args) override;`
- L502 _public prototype_ `virtual void Mount(FOnDemandMountArgs&& Args, FOnDemandMountCompleted&& OnCompleted) override;`
- L503 _public prototype_ `virtual FOnDemandInstallRequest Install(FOnDemandInstallArgs&& Args, FOnDemandInstallCompleted&& OnCompleted, FOnDemandInstallProgressed&& OnProgress = nullptr) override;`
- L506 _public prototype_ `virtual void Purge(FOnDemandPurgeArgs&& Args, FOnDemandPurgeCompleted&& OnCompleted) override;`
- L507 _public prototype_ `virtual void Defrag(FOnDemandDefragArgs&& Args, FOnDemandDefragCompleted&& OnCompleted) override;`
- L508 _public prototype_ `virtual void Verify(FOnDemandVerifyCacheCompleted&& OnCompleted) override;`
- L509 _public prototype_ `virtual FIoStatus Unmount(FStringView MountId) override;`
- L510 _public prototype_ `virtual TIoStatusOr<FOnDemandInstallSizeResult> GetInstallSize(const FOnDemandGetInstallSizeArgs& Args) const override;`
- L511 _public prototype_ `virtual FIoStatus GetInstallSizesByMountId(const FOnDemandGetInstallSizeArgs& Args, TMap<FString, uint64>& OutSizesByMountId) const override;`
- L512 _public prototype_ `virtual FIoStatus GetIsOnDemand(TConstArrayView<FOnDemandIsOnDemandArgs> Args, TArrayView<FOnDemandIsOnDemandResult> OutResults) const override;`
- L513 _public prototype_ `virtual FOnDemandCacheUsage GetCacheUsage(const FOnDemandGetCacheUsageArgs& Args) const override;`
- L514 _public prototype_ `virtual void DumpMountedContainersToLog() const override;`
- L515 _public prototype_ `virtual bool IsOnDemandStreamingEnabled() const override;`
- L516 _public prototype_ `virtual void SetStreamingOptions(EOnDemandStreamingOptions Options) override;`
- L517 _public prototype_ `virtual void GetHttpStats(FOnDemandHttpStats& Out) const override;`
- L518 _public prototype_ `virtual void ReportAnalytics(TArray<FAnalyticsEventAttribute>& OutAnalyticsArray) const override;`
- L519 _public prototype_ `virtual TUniquePtr<IAnalyticsRecording> StartAnalyticsRecording() const override;`
- L520 _public prototype_ `virtual void OnImmediateAnalytic(FOnDemandImmediateAnalyticHandler EventHandler) override;`
- L521 _public prototype_ `virtual void SetDevelopmentExtension(FSharedOnDemandDevelopmentExtension Ext) override;`
- L522 _public prototype_ `virtual bool IsDevelopmentModeEnabled() const override;`
- L523 _public prototype_ `virtual void CancelInstallRequest(FSharedInternalInstallRequest InstallRequest) override;`
- L524 _public prototype_ `virtual void UpdateInstallRequestPriority(FSharedInternalInstallRequest InstallRequest, int32 NewPriority) override;`
- L525 _public prototype_ `virtual void ReleaseContent(FOnDemandInternalContentHandle& ContentHandle) override;`
- L527 _public function_ `IOnDemandDevelopmentExtension* TryGetDevelopmentExtension()`
- L528 _public prototype_ `TArray<FSharedOnDemandContainer> GetContainers(EOnDemandContainerFlags ContainerFlags = EOnDemandContainerFlags::None) const;`
- L529 _public prototype_ `void FlushLastAccess(FOnDemandFlushLastAccessArgs&& Args, FOnDemandFlushLastAccessCompleted&& OnCompleted);`
- L534 _private prototype_ `FIoStatus GetContainersForInstall( FStringView MountId, TSet<FSharedOnDemandContainer>& OutContainersForInstallation) const;`
- L537 _private prototype_ `FIoStatus GetContainersAndPackagesForInstall( FStringView MountId, const TArray<FString>& TagSets, const TArray<FPackageId>& PackageIds, TSet<FSharedOnDemandContainer>& OutContainersForInstallation, TSet<FPackageId>& OutPackageIdsToInstall) const;`
- L543 _private prototype_ `FIoStatus InitializeInstallCache(FOnDemandInstallCacheConfig& OnDemandInstallCacheConfig);`
- L544 _private prototype_ `void TryEnterTickLoop();`
- L545 _private prototype_ `void TickLoop();`
- L546 _private prototype_ `bool Tick();`
- L547 _private prototype_ `void EnqueueMountRequest(FOnDemandMountArgs&& Args, FOnDemandMountCompleted&& OnCompleted);`
- L548 _private prototype_ `FIoStatus ProcessMountRequest(FMountRequest& MountRequest);`
- L549 _private prototype_ `void CompleteMountRequest(FMountRequest& MountRequest, FOnDemandMountResult&& MountResult);`
- L550 _private prototype_ `void OnEncryptionKeyAdded(const FGuid& Id, const FAES::FAESKey& Key);`
- L551 _private prototype_ `void OnHostGroupRegistered(const FName& HostGroup);`
- L552 _private prototype_ `static FIoStatus CreateContainersFromToc( FOnDemandMountArgs& MountArgs, TConstArrayView<FIoContainerId> Existing, TArray<FSharedOnDemandContainer>& Out);`
- L556 _private prototype_ `static FIoStatus SetupHostGroup(const FSharedOnDemandContainer& Container, const FOnDemandMountArgs& MountArgs);`
- L559 _private member_ `TUniquePtr<FOnDemandDebugCommands> DebugCommands;`
- L562 _private member_ `TUniquePtr<FOnDemandContentInstaller> Installer;`
- L563 _private member_ `FSharedInstallCache InstallCache;`
- L564 _private member_ `FSharedPackageStoreBackend PackageStoreBackend;`
- L565 _private member_ `FSharedHttpIoBackend HttpIoBackend;`
- L566 _private member_ `FDiskCacheGovernor DiskCacheGovernor;`
- L568 _private member_ `FDelegateHandle OnMountPakHandle;`
- L569 _private member_ `FDelegateHandle OnServerPostForkHandle;`
- L570 _private member_ `TArray<FSharedOnDemandContainer> Containers;`
- L571 _private member_ `mutable UE::FMutex ContainerMutex;`
- L573 _private member_ `TArray<FSharedMountRequest> MountRequests;`
- L574 _private member_ `UE::FMutex RequestMutex;`
- L576 _private member_ `EOnDemandStreamingOptions StreamingOptions = EOnDemandStreamingOptions::Default;`
- L577 _private member_ `bool bTicking = false;`
- L578 _private member_ `bool bTickRequested = false;`
- L579 _private member_ `TFuture<void> TickFuture;`
- L580 _private member_ `FSharedOnDemandDevelopmentExtension DevExt;`

#### struct `UE::IoStore::FOnDemandIoStore::FMountRequest`  
`struct FMountRequest`  
_L472-477_
- L474 _public member_ `FOnDemandMountArgs Args;`
- L475 _public member_ `FOnDemandMountCompleted OnCompleted;`
- L476 _public member_ `double DurationInSeconds = 0.0;`

#### Free symbols / members of external scopes

- L28 _typedef_ `using FSharedContainerHeader = TSharedPtr<FIoContainerHeader>;`
- L30 _namespace_ `namespace UE`
- L30 _namespace_ `namespace IoStore` (scope `UE`)
- L38 _typedef_ `using FSharedPackageStoreBackend = TSharedPtr<class IOnDemandPackageStoreBackend>;` (scope `UE::IoStore`)
- L39 _typedef_ `using FSharedInstallCache = TSharedPtr<class IOnDemandInstallCache>;` (scope `UE::IoStore`)
- L40 _typedef_ `using FSharedHttpIoBackend = TSharedPtr<class IOnDemandHttpIoDispatcherBackend>;` (scope `UE::IoStore`)
- L43 _prototype_ `bool IsDevModeEnabled();` (scope `UE::IoStore`)
- L44 _prototype_ `bool IsPackageStreamingEnabled();` (scope `UE::IoStore`)
- L59 _prototype_ `ENUM_CLASS_FLAGS(EOnDemandContainerFlags);` (scope `UE::IoStore`)
- L62 _typedef_ `using FOnDemandPartitionEntry = UE::IoStore::Serialization::V2::FOnDemandPartitionEntry;` (scope `UE::IoStore`)
- L63 _typedef_ `using FOnDemandChunkEntry = UE::IoStore::Serialization::V2::FOnDemandChunkEntry;` (scope `UE::IoStore`)
- L64 _typedef_ `using FOnDemandTagSet = UE::IoStore::Serialization::V2::FOnDemandTagSetEntry;` (scope `UE::IoStore`)
- L65 _typedef_ `using FOnDemandTocStorage = UE::IoStore::Serialization::FOnDemandTocStorage;` (scope `UE::IoStore`)
- L66 _typedef_ `using FOnDemandContainerTocHeaderView = UE::IoStore::Serialization::V2::FOnDemandContainerTocHeaderView;` (scope `UE::IoStore`)
- L67 _typedef_ `using FOnDemandPartitionHash = UE::IoStore::Serialization::V2::FOnDemandPartitionHash;` (scope `UE::IoStore`)
- L68 _typedef_ `using FOnDemandChunkHash = UE::IoStore::Serialization::V2::FOnDemandChunkHash;` (scope `UE::IoStore`)
- L77 _typedef_ `using FSharedOnDemandContainer = TSharedPtr<struct FOnDemandContainer, ESPMode::ThreadSafe>;` (scope `UE::IoStore`)
- L443 _typedef_ `using FOnDemandChunkInfoList = TOnDemandChunkInfoList<FDefaultAllocator>;` (scope `UE::IoStore`)
- L465 _typedef_ `using FOnDemandFlushLastAccessCompleted = TUniqueFunction<void(FOnDemandFlushLastAccessResult)>;` (scope `UE::IoStore`) — Flush last access completion callback.
- L586 _prototype_ `FStringBuilderBase& operator<<(FStringBuilderBase& Sb, UE::IoStore::EOnDemandContainerFlags Flags);`
- L587 _prototype_ `FString LexToString(UE::IoStore::EOnDemandContainerFlags Flags);`

### `Source/Runtime/Experimental/IoStore/OnDemand/Private/OnDemandMisc.h` (Private)


#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API IOSTOREONDEMAND_API`
- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace IoStore` (scope `UE`)
- L15 _prototype_ `FStringView TryConvertChunkIdToPackageName( const FIoChunkId& ChunkId, FUtf8StringBuilderBase& OutFilename, FStringBuilderBase& OutPackageName, FStringBuilderBase* OutError = nullptr);` (scope `UE::IoStore`)
- L21 _prototype_ `FString TryConvertChunkIdToPackageName( const FIoChunkId& ChunkId, FString& OutFilename, FStringBuilderBase* OutError = nullptr);` (scope `UE::IoStore`)

### `Source/Runtime/Experimental/IoStore/OnDemand/Private/OnDemandPackageStoreBackend.h` (Private)


#### enum `UE::IoStore::EOnDemandPackageStoreUpdateMode`  
`enum class EOnDemandPackageStoreUpdateMode : uint8`  
_L16-21_
- L18 _public enumerator_ `None`
- L19 _public enumerator_ `Full`
- L20 _public enumerator_ `ReferencedPackages`

#### class `UE::IoStore::IOnDemandPackageStoreBackend`  
`class IOnDemandPackageStoreBackend : public IPackageStoreBackend`  
_L23-31_
- inherits: `IPackageStoreBackend`
- L27 _public prototype_ `virtual ~IOnDemandPackageStoreBackend() = default;`
- L29 _public prototype_ `virtual EPackageStoreEntryStatus GetPackageStoreEntryInternal(FPackageId PackageId, FPackageStoreEntry& Out) = 0;`
- L30 _public prototype_ `virtual void NeedsUpdate(EOnDemandPackageStoreUpdateMode Mode = EOnDemandPackageStoreUpdateMode::Full) = 0;`

#### Free symbols / members of external scopes

- L11 _typedef_ `using FSharedContainerHeader = TSharedPtr<FIoContainerHeader>;`
- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace IoStore` (scope `UE`)
- L33 _prototype_ `TSharedPtr<IOnDemandPackageStoreBackend> MakeOnDemandPackageStoreBackend(TWeakPtr<FOnDemandIoStore> OnDemandIoStore);` (scope `UE::IoStore`)

### `Source/Runtime/Experimental/IoStore/OnDemand/Private/Statistics.h` (Private)


#### enum `UE::IoStore::ECacheType`  
`enum class ECacheType : uint8`  
_L44-50_
- L47 _public enumerator_ `Memory` — The data was returned immediately from the in memory cache.
- L49 _public enumerator_ `Disk` — The data was returned at a later point from the disk cache.

#### class `UE::IoStore::FOnDemandIoBackendStats`  
`class FOnDemandIoBackendStats`  
_L66-136_
- L114 _private prototype_ `void OnApplicationResume();`
- L115 _private prototype_ `void OnCSVProfileEndRequested();`
- L117 _private prototype_ `void UpdateCSVValues();`
- L118 _private prototype_ `void PrintPeriodicLogging();`
- L120 _private prototype_ `void ResetOnScreenStatistics();`
- L121 _private prototype_ `void PrintOnScreenStatistics(FCoreDelegates::FSeverityMessageMap& OutMessages);`
- L123 _private member_ `FDelegateHandle OnApplicationResumeHandle;`
- L124 _private member_ `FDelegateHandle EndFrameDelegateHandle;`
- L125 _private member_ `FDelegateHandle OnScreenDelegateHandle;`
- L126 _private member_ `FDelegateHandle CSVProfileEndRequestedHandle;`
- L129 _private member_ `FConsoleCommandPtr ResetStatisticsCommand;`
- L132 _private member_ `const FBackendStatus& BackendStatus;`
- L134 _private member_ `bool bValuesValidForAnalytics = true;`

#### class `UE::IoStore::FOnDemandContentInstallerStats`  
`class FOnDemandContentInstallerStats`  
_L139-153_

#### class `UE::IoStore::FOnDemandInstallCacheStats`  
`class FOnDemandInstallCacheStats`  
_L156-187_

#### Free symbols / members of external scopes

- L15 _macro_ `# define IAS_WITH_STATISTICS 1`
- L17 _macro_ `# define IAS_WITH_STATISTICS 0`
- L22 _macro_ `#define UE_TRACK_CDN_HIT_STATUS 1`
- L24 _macro_ `#define UE_TRACK_CDN_HIT_STATUS 0`
- L28 _macro_ `#define UE_ENABLE_ONSCREEN_STATISTICS !UE_BUILD_SHIPPING`
- L34 _prototype_ `LLM_DECLARE_TAG(Ias);`
- L36 _namespace_ `namespace UE`
- L36 _namespace_ `namespace IoStore` (scope `UE`)
- L53 _macro_ `# define IAS_STATISTICS_IMPL(...) ;`
- L55 _macro_ `# define IAS_STATISTICS_IMPL(...) { return __VA_ARGS__; }`
- L60 _prototype_ `extern void OnDemandSetImmediateAnalyticHandler(FOnDemandImmediateAnalyticHandler&& EventHandler);` (scope `UE::IoStore`)
- L62 _function_ `inline void OnDemandSetImmediateAnalyticHandler(FOnDemandImmediateAnalyticHandler&& EventHandler)` (scope `UE::IoStore`)

### `Source/Runtime/Experimental/IoStore/OnDemand/Private/ThreadSafeIntrusiveQueue.h` (Private)


#### class `UE::IoStore::TThreadSafeIntrusiveQueue`  
`template<typename T> class TThreadSafeIntrusiveQueue`  
_L18-204_
- desc: Note that the type used requires the following members: NextRequest: A pointer to the same type, this is used to maintain the list. Priority: An int32 value used to store the priority of the value
- L21 _public function_ `void Enqueue(T* Request)`
- L41 _public function_ `void EnqueueByPriority(T* Request)`
- L49 _public function_ `T* Dequeue(int32 NumToRemove = MAX_int32)`
- L97 _public function_ `void Reprioritize(T* Request, int32 NewPriority)`
- L111 _public function_ `int32 Num() const`
- L118 _private function_ `void EnqueueByPriorityInternal(T* Request)`
- L154 _private function_ `bool RemoveInternal(T* Request)`
- L198 _private member_ `mutable FCriticalSection CriticalSection;`
- L200 _private member_ `T* Head = nullptr;`
- L201 _private member_ `T* Tail = nullptr;`
- L203 _private member_ `int32 ListNum = 0;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace IoStore` (scope `UE`)
