# Programs / UbaCommon

- module root: `Source/Programs/UnrealBuildAccelerator/Common`
- headers: 68; symbols: 4173
- symbol kinds: class=54, enum=30, enumerator=76, externvar=4, function=319, macro=59, member=1750, namespace=68, prototype=1466, struct=191, typedef=73, union=1, variable=82
- PrivateDependencyModuleNames: Detours, OpenSSL, UbaMimalloc
- PublicDependencyModuleNames: OodleDataCompression, UbaCore

### `Source/Programs/UnrealBuildAccelerator/Common/Private/UbaObjectFileCoff.h` (Private)


#### class `uba::ObjectFileCoff`  
`class ObjectFileCoff : public ObjectFile`  
_L10-39_
- inherits: `ObjectFile`
- L13 _public prototype_ `ObjectFileCoff();`
- L14 _public prototype_ `virtual bool Parse(Logger& logger, ObjectFileParseMode parseMode, const tchar* hint) override;`
- L16 _public prototype_ `static bool CreateExtraFile(Logger& logger, const StringView& platform, MemoryBlock& memoryBlock, const AllExternalImports& allExternalImports, const AllInternalImports& allInternalImports, const UnorderedExports& allSharedExports, const UnorderedExports& allExplicitExports, bool includeExportsInFile);`
- L21 _private prototype_ `bool ParseExports(UnorderedExports& outExports);`
- L22 _private prototype_ `template<typename SymbolType> void ParseAllSymbols();`
- L34 _private member_ `bool m_isBigObj = false;`
- L35 _private member_ `Info m_info;`
- L37 _private member_ `UnorderedSymbols m_loopbacksToAdd;`
- L38 _private member_ `UnorderedSymbols m_toRemove;`

#### struct `uba::ObjectFileCoff::Info`  
`struct Info`  
_L24-32_
- L26 _public member_ `u32 sectionsMemOffset = 0;`
- L27 _public member_ `u32 sectionCount = 0;`
- L28 _public member_ `u64 directiveSectionMemOffset = 0;`
- L29 _public member_ `u32 stringTableMemPos = 0;`
- L30 _public member_ `u32 symbolsMemPos = 0;`
- L31 _public member_ `u32 symbolCount = 0;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace uba`
- L41 _prototype_ `bool IsCoffFile(const u8* data, u64 dataSize);` (scope `uba`)

### `Source/Programs/UnrealBuildAccelerator/Common/Private/UbaObjectFileElf.h` (Private)


#### class `uba::ObjectFileElf`  
`class ObjectFileElf : public ObjectFile`  
_L9-21_
- inherits: `ObjectFile`
- L12 _public prototype_ `ObjectFileElf();`
- L13 _public prototype_ `virtual bool Parse(Logger& logger, ObjectFileParseMode parseMode, const tchar* hint) override;`
- L15 _public prototype_ `static bool CreateExtraFile(Logger& logger, const StringView& platform, MemoryBlock& memoryBlock, const AllExternalImports& allExternalImports, const AllInternalImports& allInternalImports, const AllExports& allExports, bool includeExportsInFile);`
- L18 _private member_ `u64 m_symTableNamesOffset = 0;`
- L19 _private member_ `u64 m_dynTableNamesOffset = 0;`
- L20 _private member_ `bool m_useVisibilityForExports = true;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace uba`
- L23 _prototype_ `bool IsElfFile(const u8* data, u64 dataSize);` (scope `uba`)

### `Source/Programs/UnrealBuildAccelerator/Common/Private/UbaObjectFileImportLib.h` (Private)


#### class `uba::ObjectFileImportLib`  
`class ObjectFileImportLib : public ObjectFile`  
_L9-17_
- inherits: `ObjectFile`
- L12 _public prototype_ `virtual bool Parse(Logger& logger, ObjectFileParseMode parseMode, const tchar* hint) override;`
- L13 _public prototype_ `virtual const char* GetLibName() override;`
- L16 _private member_ `std::string m_libName;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace uba`
- L20 _prototype_ `bool IsImportLib(const u8* data, u64 dataSize);` (scope `uba`)

### `Source/Programs/UnrealBuildAccelerator/Common/Private/UbaObjectFileLLVMIR.h` (Private)


#### class `uba::ObjectFileLLVMIR`  
`class ObjectFileLLVMIR : public ObjectFile`  
_L10-58_
- inherits: `ObjectFile`
- L13 _public prototype_ `ObjectFileLLVMIR();`
- L14 _public prototype_ `~ObjectFileLLVMIR();`
- L16 _public prototype_ `virtual bool Parse(Logger& logger, ObjectFileParseMode parseMode, const tchar* hint) override;`
- L19 _private member_ `enum BlockInfoCodes : u8;`
- L20 _private member_ `enum Encoding : u8;`
- L21 _private member_ `enum EntryKind : u8;`
- L22 _private member_ `enum FixedAbbrevIDs : u8;`
- L27 _private typedef_ `using AbbrevPtr = std::shared_ptr<Abbrev>;`
- L30 _private prototype_ `bool ParseBlock(Logger& logger, BitStreamReader& reader, BlockInfo& blockInfo, u32 blockId, u32 indent);`
- L34 _private prototype_ `void AddType(u32 typeCode, const Vector<u64>& ops);` — Resolves a TYPE_BLOCK record (in stream order) to its byte size, used to give GLOBALVAR exports a real st_size. Copy relocations against a data symbol require a non-zero size, which bitcode otherwise omits.
- L35 _private member_ `Vector<u64> m_typeSizes;`
- L36 _private member_ `Vector<u64> m_typeAligns;`
- L54 _private member_ `Vector<BitStreamEntry> m_globalVarOrFunctionRecords;`
- L56 _private member_ `u64 m_strTabPos;`
- L57 _private member_ `u64 m_strTabSize;`

#### enum `uba::ObjectFileLLVMIR::DllStorage`  
`enum DllStorage : u8`  
_L38-43_
- L40 _public enumerator_ `DllStorage_None`
- L41 _public enumerator_ `DllStorage_Export`
- L42 _public enumerator_ `DllStorage_Import`

#### struct `uba::ObjectFileLLVMIR::BitStreamEntry`  
`struct BitStreamEntry`  
_L45-52_
- L47 _public member_ `u64 pos;`
- L48 _public member_ `u32 word;`
- L49 _public member_ `u32 wordBits;`
- L50 _public member_ `u32 code;`
- L51 _public member_ `Vector<AbbrevOp> operands;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace uba`
- L61 _prototype_ `bool IsLLVMIRFile(const u8* data, u64 dataSize);` (scope `uba`)

### `Source/Programs/UnrealBuildAccelerator/Common/Private/UbaObjectFileMachO.h` (Private)


#### class `uba::ObjectFileMachO`  
`class ObjectFileMachO : public ObjectFile`  
_L9-20_
- inherits: `ObjectFile`
- L12 _public prototype_ `ObjectFileMachO();`
- L13 _public prototype_ `virtual bool Parse(Logger& logger, ObjectFileParseMode parseMode, const tchar* hint) override;`
- L16 _private member_ `u64 m_symtabOffset = 0;`
- L17 _private member_ `u32 m_symbolCount = 0;`
- L18 _private member_ `u64 m_strtabOffset = 0;`
- L19 _private member_ `u32 m_strtabSize = 0;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace uba`
- L22 _prototype_ `bool IsMachOFile(const u8* data, u64 dataSize);` (scope `uba`)

### `Source/Programs/UnrealBuildAccelerator/Common/Public/UbaAWS.h` (Public)


#### class `uba::Cloud`  
`class Cloud`  
_L15-263_
- L32 _public member_ `static constexpr Provider g_providers[] { { TC("AWS"), "PUT", "latest/api/token", "X-aws-ec2-metadata-token-ttl-seconds: 21600\r\n", TC("X-aws-ec2-metadata-token: "), "latest/meta-data/instance-id", "latest/meta-data/instance-life-cycle", "latest/meta-data/autoscaling/target-lifecycle-state", "latest/meta-data/placement/availability-zone", nullptr,`
- L61 _public member_ `static constexpr char g_imdsHost[] = "16`
- L62 _public member_ `static constexpr char g_imdsAutoScalingLifeCycleState[] = "la`
- L63 _public member_ `static constexpr char g_imdsSpotInstanceAction[] = "la`
- L65 _public function_ `bool QueryToken(Logger& logger, const tchar* rootDir)`
- L106 _public function_ `bool QueryInformation(Logger& logger, StringBufferBase& outExtraInfo, const tchar* rootDir)`
- L149 _public function_ `bool QueryAvailabilityZone(Logger& logger, const tchar* rootDir)`
- L173 _public function_ `bool IsNotCloud(Logger& logger, const tchar* rootDir, const tchar* provider)` — Returns true if we _know_ we are not in this cloud provider
- L182 _public function_ `bool WriteIsNotCloud(Logger& logger, const tchar* rootDir, const tchar* provider)`
- L194 _public function_ `const tchar* GetProvider() const`
- L201 _public function_ `bool IsTerminating(Logger& logger, StringBufferBase& outReason, u64& outTerminationTimeMs)`
- L253 _public function_ `const tchar* GetAvailabilityZone()`
- L258 _public member_ `TString m_availabilityZone;`
- L259 _public member_ `std::string m_tokenString;`
- L260 _public member_ `const Provider* m_provider = nullptr;`
- L261 _public member_ `bool m_isSpot = false;`
- L262 _public member_ `bool m_isAutoscaling = false;`

#### struct `uba::Cloud::Provider`  
`struct Provider`  
_L18-30_
- L20 _public member_ `const tchar* name;`
- L21 _public member_ `const char* tokenCommand;`
- L22 _public member_ `const char* tokenImds;`
- L23 _public member_ `const char* tokenHeader;`
- L24 _public member_ `const tchar* tokenPrefix;`
- L25 _public member_ `const char* instanceIdImds;`
- L26 _public member_ `const char* instanceLifeCycleImds;`
- L27 _public member_ `const char* autoScalingLifeCycleStateImds;`
- L28 _public member_ `const char* availabilityZoneImds;`
- L29 _public member_ `const char* maintenanceEventImds;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UBA_USE_CLOUD !PLATFORM_MAC`
- L13 _namespace_ `namespace uba`

### `Source/Programs/UnrealBuildAccelerator/Common/Public/UbaApplication.h` (Public)


#### Free symbols / members of external scopes

- L8 _namespace_ `namespace uba`
- L10 _function_ `inline bool ExpandEnvironmentVariables(StringBufferBase& str, const Function<bool(const tchar*)>& errorFunc)` (scope `uba`)

### `Source/Programs/UnrealBuildAccelerator/Common/Public/UbaBottleneck.h` (Public)


#### struct `uba::BottleneckTicket`  
`struct BottleneckTicket`  
_L12-16_
- L14 _public member_ `Event ev;`
- L15 _public member_ `BottleneckTicket* next = nullptr;`

#### struct `uba::Bottleneck`  
`struct Bottleneck`  
_L18-79_
- L20 _public function_ `Bottleneck(u32 mc) : m_maxCount(mc)`
- L22 _public function_ `void Enter(BottleneckTicket& ticket, Timer& timer)`
- L46 _public function_ `bool TryEnter()`
- L55 _public function_ `void Leave(BottleneckTicket& ticket)`
- L71 _public function_ `u32 GetMaxCount() const`
- L74 _private member_ `Futex m_lock;`
- L75 _private member_ `BottleneckTicket* m_first = nullptr;`
- L76 _private member_ `BottleneckTicket* m_last = nullptr;`
- L77 _private member_ `Atomic<u32> m_activeCount = 0;`
- L78 _private member_ `u32 m_maxCount;`

#### struct `uba::BottleneckScope`  
`struct BottleneckScope`  
_L81-88_
- L83 _public function_ `BottleneckScope(Bottleneck& b, Timer& timer) : bottleneck(b)`
- L84 _public function_ `~BottleneckScope()`
- L86 _public member_ `Bottleneck& bottleneck;`
- L87 _public member_ `BottleneckTicket ticket;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace uba`

### `Source/Programs/UnrealBuildAccelerator/Common/Public/UbaBufferCache.h` (Public)


#### struct `uba::BufferCache`  
`struct BufferCache`  
_L13-24_
- L15 _public prototype_ `inline u8* Pop();`
- L16 _public prototype_ `inline void Push(u8* slot);`
- L18 _public prototype_ `inline BufferCache(u32 bufferSize);`
- L19 _public prototype_ `inline ~BufferCache();`
- L21 _public member_ `u32 m_bufferSize;`
- L22 _public member_ `Futex m_slotsLock;`
- L23 _public member_ `Vector<u8*> m_slots;`
- L44 _function_ `u8* BufferCache::Pop()`
- L64 _function_ `void BufferCache::Push(u8* slot)`
- L78 _function_ `BufferCache::BufferCache(u32 bufferSize) : m_bufferSize(bufferSize)`
- L82 _function_ `BufferCache::~BufferCache()`

#### struct `uba::BinaryWriterUsingCache`  
`struct BinaryWriterUsingCache : BinaryWriter`  
_L28-33_
- inherits: `BinaryWriter`
- L30 _public function_ `BinaryWriterUsingCache(BufferCache& cache) : BinaryWriter(cache.Pop(), 0, cache.m_bufferSize), m_cache(cache)`
- L31 _public function_ `~BinaryWriterUsingCache()`
- L32 _public member_ `BufferCache& m_cache;`

#### struct `uba::BinaryReaderUsingCache`  
`struct BinaryReaderUsingCache : BinaryReader`  
_L35-40_
- inherits: `BinaryReader`
- L37 _public function_ `BinaryReaderUsingCache(BufferCache& cache) : BinaryReader(cache.Pop(), 0, cache.m_bufferSize), m_cache(cache)`
- L38 _public function_ `~BinaryReaderUsingCache()`
- L39 _public member_ `BufferCache& m_cache;`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UBA_CHECK_BUFFER_SLOTS 0`
- L9 _namespace_ `namespace uba`

### `Source/Programs/UnrealBuildAccelerator/Common/Public/UbaCacheBucket.h` (Public)


#### struct `uba::CacheBucket`  
`struct CacheBucket`  
_L13-48_
- L15 _public prototype_ `CacheBucket(u64 id, u32 version);`
- L17 _public member_ `ReaderWriterLock m_cacheEntryLookupLock;`
- L18 _public member_ `UnorderedMap<CasKey, CacheEntries> m_cacheEntryLookup;`
- L20 _public member_ `CompactPathTable m_pathTable;`
- L21 _public member_ `CompactCasKeyTable m_casKeyTable;`
- L23 _public member_ `u64 m_id;`
- L24 _public member_ `u64 totalEntryCount = 0;`
- L25 _public member_ `u64 totalEntrySize = 0;`
- L26 _public member_ `Atomic<bool> hasDeletedEntries = false;`
- L27 _public member_ `Atomic<bool> needsSave = false;`
- L30 _public member_ `Atomic<u64> lastSavedTime = 0;` — Times are in file time from creation of cache database
- L31 _public member_ `Atomic<u64> lastUsedTime = 0;`
- L32 _public member_ `u64 oldestUsedTime = 0;`
- L34 _public member_ `u32 index = ~0u;`
- L37 _public member_ `MaintenanceContext* m_maintenanceContext = nullptr;`
- L46 _public prototype_ `bool Load(Logger& logger, BinaryReader& reader, u32 databaseVersion, LoadStats& outStats, StorageServer& storage);`
- L47 _public prototype_ `bool Validate(Logger& logger, WorkManager& workManager);`

#### struct `uba::CacheBucket::LoadStats`  
`struct LoadStats`  
_L39-44_
- L41 _public member_ `Atomic<u32> totalPathTableSize;`
- L42 _public member_ `Atomic<u32> totalCasKeyTableSize;`
- L43 _public member_ `Atomic<u64> totalCacheEntryCount;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace uba`

### `Source/Programs/UnrealBuildAccelerator/Common/Public/UbaCacheClient.h` (Public)


#### struct `uba::CacheClientCreateInfo`  
`struct CacheClientCreateInfo`  
_L37-56_
- L39 _public function_ `CacheClientCreateInfo(LogWriter& w, StorageImpl& st, NetworkClient& c, Session& se) : writer(w), storage(st), client(c), session(se)`
- L40 _public member_ `LogWriter& writer;`
- L41 _public member_ `StorageImpl& storage;`
- L42 _public member_ `NetworkClient& client;`
- L43 _public member_ `Session& session;`
- L45 _public prototype_ `void Apply(Config& config, const tchar* tableName = TC("Cach`
- L47 _public member_ `bool reportCacheKey = false;`
- L48 _public member_ `bool reportMissReason = false;` — Report the reason no matching cache entry was found
- L49 _public member_ `bool useDirectoryPreparsing = true;` — This is used to minimize syscalls. GetFileAttributes can be very expensive on cloud machines and we can enable this to minimize syscall count
- L50 _public member_ `bool validateCacheWritesInput = false;` — Set to true to validate cas of all input files before sent to cache
- L51 _public member_ `bool validateCacheWritesOutput = false;` — Set to true to validate cas of all output files before sent to cache
- L52 _public member_ `bool useRoots = true;` — Set this to false to allow paths that are not under roots and to not fix them up
- L53 _public member_ `bool useCacheHit = true;` — Set this to false to ignore found cache hits.. this is for debugging/testing only
- L54 _public member_ `bool useMappingForCreatedCas = true;` — Set to this to false to make sure cas created when sending cas are stored on disk
- L55 _public member_ `const tchar* hint = TC("");` — Hint will show up in cache server log

#### struct `uba::CacheResult`  
`struct CacheResult`  
_L60-64_
- L62 _public member_ `bool hit = false;`
- L63 _public member_ `Vector<ProcessLogLine> logLines;`

#### class `uba::CacheClient`  
`class CacheClient`  
_L68-179_
- L71 _public prototype_ `CacheClient(const CacheClientCreateInfo& info);`
- L72 _public prototype_ `~CacheClient();`
- L74 _public prototype_ `bool RegisterPathHash(const tchar* path, const CasKey& hash);`
- L76 _public prototype_ `bool WriteToCache(u32 bucketId, const ProcessStartInfo& info, const u8* inputs, u64 inputsSize, const u8* outputs, u64 outputsSize, const u8* logLines, u64 logLinesSize, u32 processId = 0);`
- L77 _public prototype_ `bool WriteToCache(const RootPaths& rootPaths, u32 bucketId, const ProcessStartInfo& info, const u8* inputs, u64 inputsSize, const u8* outputs, u64 outputsSize, const u8* logLines, u64 logLinesSize, u32 processId = 0);`
- L78 _public prototype_ `bool FetchFromCache(CacheResult& outResult, RootsHandle rootsHandle, u32 bucketId, const ProcessStartInfo& info);`
- L79 _public prototype_ `bool FetchFromCache(CacheResult& outResult, const RootPaths& rootPaths, u32 bucketId, const ProcessStartInfo& info);`
- L80 _public prototype_ `bool RequestServerShutdown(const tchar* reason);`
- L82 _public prototype_ `bool ExecuteCommand(Logger& logger, const tchar* command, const tchar* destinationFile = nullptr, const tchar* additionalInfo = nullptr);`
- L84 _public function_ `inline MutableLogger& GetLogger()`
- L85 _public function_ `inline NetworkClient& GetClient()`
- L86 _public function_ `inline StorageImpl& GetStorage()`
- L87 _public function_ `inline Session& GetSession()`
- L89 _public prototype_ `void Disable();`
- L91 _public prototype_ `void TraceSummary();`
- L108 _public prototype_ `bool FetchEntryFromCache(CacheResult& outResult, FetchContext& context, u32 bucketId);`
- L109 _public prototype_ `bool FetchFilesFromCache(CacheResult& outResult, FetchContext& context, bool writePlaceholders);`
- L111 _public prototype_ `u64 RegisterSpeculativeOutputs(FetchContext& context);`
- L112 _public prototype_ `void UnregisterSpeculativeOutputs(u64 id);`
- L117 _private prototype_ `u64 MakeId(u32 bucketId);`
- L120 _private prototype_ `UBA_NOINLINE bool SendPathTable(Bucket& bucket, CacheSendStats& stats, u32 requiredPathTableSize);` — No inlining because they use lots of stack space
- L121 _private prototype_ `UBA_NOINLINE bool SendCasTable(Bucket& bucket, CacheSendStats& stats, u32 requiredCasTableSize);`
- L122 _private prototype_ `UBA_NOINLINE bool SendCacheEntry(TrackWorkScope& tws, Bucket& bucket, CacheSendStats& stats, const RootPaths& rootPaths, const CasKey& cmdKey, const Map<u32, u32>& inputsStringToCasKey, const Map<u32, u32>& outputsStringToCasKey, const u8* logLines, u64 logLinesSize, const ProcessStartInfo& info);`
- L123 _private prototype_ `UBA_NOINLINE bool SendCacheEntryMessage(BinaryReader& out, Bucket& bucket, CacheSendStats& stats, const CasKey& cmdKey, const Map<u32, u32>& inputsStringToCasKey, const Map<u32, u32>& outputsStringToCasKey, const u8* logLines, u64 logLinesSize);`
- L124 _private prototype_ `UBA_NOINLINE bool FetchCasTable(TrackWorkScope& tws, Bucket& bucket, CacheFetchStats& stats, u32 requiredCasTableOffset);`
- L125 _private prototype_ `UBA_NOINLINE bool FetchPathTable(TrackWorkScope& tws, Bucket& bucket, CacheFetchStats& stats, u32 requiredPathTableOffset);`
- L126 _private prototype_ `UBA_NOINLINE bool FetchFile(Bucket& bucket, const RootPaths& rootPaths, const ProcessStartInfo& info, CacheFetchStats& cacheStats, StorageStats& storageStats, u32 casKeyOffset, bool writePlaceholders);`
- L127 _private prototype_ `template<typename TableType> bool FetchCompactTable(u32 bucketId, TableType& table, u32 requiredTableOffset, u8 messageType);`
- L128 _private prototype_ `template<typename TableType> bool FetchCompactTable(u32 bucketId, TableType& table, u32 requiredTableOffset, u8 messageType);`
- L129 _private prototype_ `bool HasEnoughPathData(Bucket& bucket, u32 requiredPathTableOffset);`
- L130 _private prototype_ `UBA_NOINLINE bool ReportUsedEntry(Vector<ProcessLogLine>& outLogLines, bool ownedLogLines, Bucket& bucket, const CasKey& cmdKey, u32 entryId);`
- L131 _private prototype_ `bool PopulateLogLines(Vector<ProcessLogLine>& outLogLines, const u8* mem, u64 memLen);`
- L133 _private prototype_ `UBA_NOINLINE CasKey GetCmdKey(const RootPaths& rootPaths, const ProcessStartInfo& info, bool report, u32 bucketId);`
- L134 _private prototype_ `bool DevirtualizePath(StringBufferBase& inOut, RootsHandle rootsHandle);`
- L135 _private prototype_ `bool ShouldNormalize(const StringBufferBase& path);`
- L137 _private prototype_ `bool GetLocalPathAndCasKey(Bucket& bucket, const RootPaths& rootPaths, StringBufferBase& outPath, CasKey& outKey, CompactCasKeyTable& casKeyTable, CompactPathTable& pathTable, u32 offset);`
- L138 _private prototype_ `UBA_NOINLINE void PreparseDirectory(const StringKey& fileNameKey, const StringBufferBase& filePath);`
- L140 _private member_ `MutableLogger m_logger;`
- L141 _private member_ `StorageImpl& m_storage;`
- L142 _private member_ `NetworkClient& m_client;`
- L143 _private member_ `Session& m_session;`
- L144 _private member_ `bool m_reportCacheKey;`
- L145 _private member_ `bool m_reportMissReason;`
- L146 _private member_ `bool m_useDirectoryPreParsing;`
- L147 _private member_ `bool m_validateCacheWritesInput;`
- L148 _private member_ `bool m_validateCacheWritesOutput;`
- L149 _private member_ `bool m_useRoots;`
- L150 _private member_ `bool m_useCacheHit;`
- L151 _private member_ `bool m_useMappingForCreatedCas;`
- L153 _private member_ `Atomic<bool> m_connected;`
- L155 _private member_ `Futex m_bucketsLock;`
- L156 _private member_ `UnorderedMap<u32, Bucket> m_buckets;`
- L158 _private member_ `Futex m_sendOneAtTheTimeLock;`
- L160 _private member_ `Futex m_directoryPreparserLock;`
- L162 _private member_ `UnorderedMap<StringKey, PreparedDir> m_directoryPreparser;`
- L165 _private member_ `Vector<PathHash> m_pathHashes;`
- L167 _private member_ `Futex m_speculativeCasKeysLock;`
- L168 _private member_ `UnorderedMap<StringKey, CasKey> m_speculativeCasKeys;`
- L169 _private member_ `UnorderedMap<u64, Vector<StringKey>> m_speculativeOutputsById;`
- L170 _private member_ `u64 m_nextSpeculativeOutputId = 1;`
- L173 _private member_ `BufferCache m_sendBufferSlots;`
- L176 _private prototype_ `CacheClient(const CacheClient&) = delete;`
- L177 _private prototype_ `CacheClient& operator=(const CacheClient&) = delete;`

#### struct `uba::CacheClient::FetchContext`  
`struct FetchContext`  
_L95-106_
- L97 _public prototype_ `FetchContext(const ProcessStartInfo& info, Session& session, RootsHandle rootsHandle, MessagePriority priority);`
- L98 _public prototype_ `FetchContext(const ProcessStartInfo& info, const RootPaths& rootPaths);`
- L100 _public member_ `const ProcessStartInfo& info;`
- L102 _public member_ `RootPaths rootPaths;`
- L103 _public member_ `Bucket* bucket = nullptr;`
- L104 _public member_ `Vector<u32> casKeyOffsets;`
- L105 _public member_ `MessagePriority priority;`

#### struct `uba::CacheClient::PreparedDir`  
`struct PreparedDir`  
_L161-161_
- L161 _public member_ `struct PreparedDir { Futex lock; Atomic<bool> done = false; };`
- L161 _public member_ `struct PreparedDir { Futex lock; Atomic<bool> done = false; };`

#### struct `uba::CacheClient::PathHash`  
`struct PathHash`  
_L164-164_
- L164 _public member_ `struct PathHash { TString path; CasKey hash; };`
- L164 _public member_ `struct PathHash { TString path; CasKey hash; };`

#### Free symbols / members of external scopes

- L14 _macro_ `#define UBA_CACHE_USE_SEND_MAX_BUFFER_CACHE PLATFORM_MAC // To prevent stack overflow`
- L16 _namespace_ `namespace uba`
- L33 _typedef_ `using RootsHandle = u64;` (scope `uba`)

### `Source/Programs/UnrealBuildAccelerator/Common/Public/UbaCacheEntry.h` (Public)


#### enum `uba::LogLinesType`  
`enum LogLinesType : u8`  
_L17-22_
- L19 _public enumerator_ `LogLinesType_Empty`
- L20 _public enumerator_ `LogLinesType_Shared`
- L21 _public enumerator_ `LogLinesType_Owned`

#### struct `uba::CacheEntry`  
`struct CacheEntry`  
_L24-37_
- L27 _public member_ `u64 creationTime = 0;` — Times are in file time from creation of cache database
- L28 _public member_ `u64 lastUsedTime = 0;`
- L30 _public member_ `u32 id = 0;`
- L31 _public member_ `LogLinesType logLinesType = LogLinesType_Empty;`
- L33 _public member_ `Vector<u8> sharedInputCasKeyOffsetRanges;`
- L34 _public member_ `Vector<u8> extraInputCasKeyOffsets;`
- L35 _public member_ `Vector<u8> outputCasKeyOffsets;`
- L36 _public member_ `Vector<u8> logLines;`

#### struct `uba::CacheEntries`  
`struct CacheEntries`  
_L39-68_
- L41 _public member_ `ReaderWriterLock lock;`
- L42 _public member_ `List<CacheEntry> entries;`
- L43 _public member_ `Vector<u8> sharedInputCasKeyOffsets;`
- L44 _public member_ `Vector<u8> sharedLogLines;`
- L45 _public member_ `u32 idCounter = 0;`
- L46 _public member_ `u32 primaryId = ~0u;` — Id of entry that shared offsets was made from
- L47 _public member_ `UnorderedSet<u32> inputsThatAreOutputs;`
- L49 _public prototype_ `u64 GetSharedSize();`
- L50 _public prototype_ `u64 GetEntrySize(CacheEntry& entry, u32 clientVersion, bool toDisk);`
- L51 _public prototype_ `u64 GetTotalSize(u32 clientVersion, bool toDisk);`
- L52 _public prototype_ `bool Write(BinaryWriter& writer, u32 clientVersion, bool toDisk);`
- L53 _public prototype_ `bool ReadFromDisk(Logger& logger, BinaryReader& reader, u32 databaseVersion, StorageImpl& storage, CompactCasKeyTable& table);`
- L54 _public prototype_ `void BuildInputs(CacheEntry& entry, const Set<u32>& inputs);`
- L55 _public prototype_ `void UpdateEntries(Logger& logger, const HashMap2<u32, u32>& oldToNewCasKeyOffset, Vector<u32>& temp, Vector<u8>& temp2, Vector<u8>& temp3);`
- L56 _public prototype_ `bool Validate(Logger& logger);`
- L58 _public prototype_ `void Flatten(Vector<u8>& out, const CacheEntry& entry);`
- L59 _public prototype_ `void Flatten(Vector<u32>& out, const CacheEntry& entry, const Vector<u8>& sharedOffsets);`
- L62 _public prototype_ `template<typename Container> void BuildInputsT(CacheEntry& entry, const Container& sortedInputs, bool populateShared, Vector<u8>& temp);`
- L65 _public prototype_ `template<typename Container> void BuildRangesFromExcludedT(CacheEntry& entry, const Container& sortedExcludedInputs);`
- L67 _public prototype_ `void PopulateInputsThatAreOutputs(const Vector<u8>& inputData, StorageImpl& storage, CompactCasKeyTable& table);`

#### struct `uba::CacheEntriesTraverser`  
`struct CacheEntriesTraverser`  
_L71-132_
- L73 _public function_ `CacheEntriesTraverser(BinaryReader& r) : reader(r)`
- L84 _public function_ `template<typename Func> bool TraverseEntryInputs(const Func& func)`
- L111 _public function_ `template<typename Func> bool TraverseEntryOutputs(const Func& func)`
- L122 _public function_ `void SkipEntryOutputs()`
- L128 _public member_ `BinaryReader& reader;`
- L129 _public member_ `const u8* sharedInputOffsets = nullptr;`
- L130 _public member_ `u32 entryCount = 0;`
- L131 _public member_ `u32 lastId = 0;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace uba`

### `Source/Programs/UnrealBuildAccelerator/Common/Public/UbaCacheServer.h` (Public)


#### struct `uba::CacheServerCreateInfo`  
`struct CacheServerCreateInfo`  
_L24-51_
- L26 _public function_ `CacheServerCreateInfo(StorageServer& s, const tchar* rd, LogWriter& w = g_consoleLogWriter) : storage(s), rootDir(rd), logWriter(w)`
- L29 _public member_ `StorageServer& storage;` — Storage server
- L32 _public member_ `const tchar* rootDir = nullptr;` — Root dir
- L35 _public member_ `LogWriter& logWriter;` — Log writer
- L38 _public member_ `bool checkInputsForDeletedCas = true;` — Will check cache entry inputs of they depend on cas files that have been deleted
- L42 _public member_ `u64 expirationTimeSeconds = 2*24*60*60;` — The time cache entries will stay around after they were last used in hours (defaults to two days) Set to zero to never expire
- L45 _public member_ `u64 maintenanceReserveSize = 256ull * 1024 * 1024;` — The amount of reserved memory used per bucket when doing maintenance
- L48 _public member_ `u64 bucketCasTableMaxSize = 32ull * 1024 * 1024;` — Max size of cas bucket. When within 2mb it will start decreasing expiry time by one hour
- L50 _public prototype_ `void Apply(Config& config);`

#### class `uba::CacheServer`  
`class CacheServer`  
_L53-141_
- L56 _public prototype_ `CacheServer(const CacheServerCreateInfo& info);`
- L57 _public prototype_ `~CacheServer();`
- L59 _public prototype_ `bool Load(bool validateBuckets);`
- L60 _public prototype_ `bool Save();`
- L62 _public prototype_ `void SetForceFullMaintenance();`
- L64 _public prototype_ `void PrintStatusLine(const tchar* additionalInfo);`
- L65 _public prototype_ `bool RunMaintenance(bool force, bool allowSave, const Function<bool()>& shouldExit);`
- L67 _public prototype_ `bool ShouldShutdown();`
- L70 _private typedef_ `using Bucket = CacheBucket;`
- L72 _private prototype_ `bool RunMaintenanceInternal(const Function<bool()>& shouldExit, bool allowSave);`
- L73 _private prototype_ `bool SaveBucket(Bucket& bucket, Vector<u8>& temp);`
- L74 _private prototype_ `bool SaveNoLock();`
- L75 _private prototype_ `bool SaveDbNoLock();`
- L76 _private prototype_ `bool DeleteEmptyBuckets();`
- L77 _private prototype_ `void OnDisconnected(u32 clientId);`
- L82 _private prototype_ `ConnectionBucket& GetConnectionBucket(const ConnectionInfo& connectionInfo, BinaryReader& reader, u32* outClientVersion = nullptr);`
- L83 _private prototype_ `Bucket& GetBucket(BinaryReader& reader, const tchar* reason);`
- L84 _private prototype_ `Bucket& GetBucket(u64 id, const tchar* reason, bool addCommon = true);`
- L85 _private prototype_ `u32 GetBucketWorkerCount();`
- L87 _private prototype_ `bool HandleMessage(const ConnectionInfo& connectionInfo, u8 messageType, BinaryReader& reader, BinaryWriter& writer);`
- L88 _private prototype_ `bool HandleStoreEntry(ConnectionBucket& bucket, BinaryReader& reader, BinaryWriter& writer, u32 clientVersion, u32 clientId);`
- L89 _private prototype_ `bool HandleStoreEntryDone(const ConnectionInfo& connectionInfo, BinaryReader& reader);`
- L90 _private prototype_ `bool HandleFetchPathTable(BinaryReader& reader, BinaryWriter& writer);`
- L91 _private prototype_ `bool HandleFetchCasTable(BinaryReader& reader, BinaryWriter& writer);`
- L92 _private prototype_ `bool HandleFetchPathTable2(BinaryReader& reader, BinaryWriter& writer);`
- L93 _private prototype_ `bool HandleFetchCasTable2(BinaryReader& reader, BinaryWriter& writer);`
- L94 _private prototype_ `bool HandleFetchEntries(BinaryReader& reader, BinaryWriter& writer, u32 clientId);`
- L95 _private prototype_ `bool HandleReportUsedEntry(BinaryReader& reader, BinaryWriter& writer, u32 clientId);`
- L96 _private prototype_ `bool HandleExecuteCommand(BinaryReader& reader, BinaryWriter& writer);`
- L98 _private member_ `MutableLogger m_logger;`
- L99 _private member_ `NetworkServer& m_server;`
- L100 _private member_ `StorageServer& m_storage;`
- L102 _private member_ `StringBuffer<MaxPath> m_rootDir;`
- L104 _private member_ `Atomic<u32> m_addsSinceMaintenance = 0;`
- L105 _private member_ `Atomic<u64> m_cacheKeyFetchCount = 0;`
- L106 _private member_ `Atomic<u64> m_cacheKeyHitCount = 0;`
- L107 _private member_ `Atomic<bool> m_isRunningMaintenance = false;`
- L108 _private member_ `Atomic<bool> m_bucketIsOverflowing = false;`
- L109 _private member_ `Atomic<bool> m_forceMaintenance = false;`
- L111 _private member_ `Futex m_bucketsLock;`
- L112 _private member_ `Map<u64, Bucket> m_buckets;`
- L114 _private member_ `Futex m_connectionsLock;`
- L115 _private member_ `Map<u32, Connection> m_connections;`
- L117 _private member_ `UnorderedSet<CasKey> m_trackedDeletes;`
- L119 _private member_ `Atomic<bool> m_shutdownRequested = false;`
- L120 _private member_ `Atomic<u64> m_totalEntryCount = 0;`
- L122 _private member_ `u64 m_maintenanceReserveSize = 0;`
- L123 _private member_ `u64 m_bucketCasTableMaxSize = 0;`
- L124 _private member_ `u64 m_creationTime = 0;`
- L125 _private member_ `u64 m_bootTime = 0;`
- L126 _private member_ `u64 m_lastMaintenance = 0;`
- L127 _private member_ `u64 m_longestMaintenance = 0;`
- L128 _private member_ `u64 m_expirationTimeSeconds = 0;`
- L129 _private member_ `u32 m_peakConnectionCount = 0;`
- L130 _private member_ `bool m_dbfileDirty = false;`
- L132 _private member_ `bool m_checkInputsForDeletedCas = true;`
- L134 _private member_ `bool m_shouldWipe = false;`
- L135 _private member_ `bool m_forceAllSteps = false;`
- L137 _private member_ `StringKey m_statusLineKey;`
- L139 _private prototype_ `CacheServer(const CacheServer&) = delete;`
- L140 _private prototype_ `CacheServer& operator=(const CacheServer&) = delete;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace uba`

### `Source/Programs/UnrealBuildAccelerator/Common/Public/UbaCompactTables.h` (Public)


#### class `uba::CompactPathTable`  
`class CompactPathTable`  
_L19-81_
- L22 _public prototype_ `CompactPathTable(bool caseSensitive, u64 reservePathCount, u64 reserveSegmentCount, u32 version);`
- L24 _public prototype_ `u32 Add(const tchar* str, u64 strLen);`
- L25 _public prototype_ `u32 Add(const tchar* str, u64 strLen, u32& outRequiredPathTableSize);`
- L26 _public prototype_ `u32 AddNoLock(const tchar* str, u64 strLen);`
- L29 _public prototype_ `u32 AddNoLock(AddContext& context, u32 offset);`
- L31 _public prototype_ `void AddCommonStringSegments();`
- L33 _public prototype_ `bool GetString(StringBufferBase& out, u64 offset) const;`
- L34 _public prototype_ `bool TryGetString(Logger& logger, StringBufferBase& out, u64 offset) const;`
- L36 _public prototype_ `u8* GetMemory();`
- L37 _public prototype_ `u32 GetSize() const;`
- L38 _public prototype_ `u32 GetCommonSize();`
- L39 _public prototype_ `bool GetCaseInsensitive();`
- L40 _public prototype_ `u32 GetVersion();`
- L42 _public prototype_ `bool ReadMem(BinaryReader& reader, bool populateLookup);`
- L43 _public prototype_ `u8* BeginCommit(u64 size);`
- L44 _public prototype_ `void EndCommit(u8* data, u64 written);`
- L45 _public prototype_ `void Swap(CompactPathTable& other);`
- L47 _public function_ `u64 GetPathCount()`
- L48 _public function_ `u64 GetSegmentCount()`
- L51 _public prototype_ `template<typename Func> bool TraversePaths(const Func& func) const;`
- L53 _public prototype_ `void InitMem();`
- L67 _private prototype_ `u32 InternalAdd(const tchar* str, const tchar* stringKeyString, u64 strLen);`
- L68 _private prototype_ `u32 InternalAddWithNewSegment(u32 offset, u32 parentOffset, bool separator, const StringView& segment);`
- L69 _private prototype_ `void InternalAddWithExistingSegment(u32 offset, u32 parentOffset, bool separator, u32 segmentOffset);`
- L71 _private member_ `mutable Futex m_lock;`
- L72 _private member_ `MemoryBlock m_pathTableMem;`
- L73 _private member_ `HashMap<StringKey, u32, true> m_offsets;`
- L74 _private member_ `HashMap<StringKey, u32, true> m_segmentOffsets;`
- L75 _private member_ `u32 m_version = 0;`
- L76 _private member_ `u32 m_commonSize = 0;`
- L77 _private member_ `bool m_caseInsensitive = true;`
- L79 _private prototype_ `CompactPathTable(const CompactPathTable&) = delete;`
- L80 _private prototype_ `void operator=(const CompactPathTable&) = delete;`
- L140 _function_ `template<typename Func> bool CompactPathTable::TraversePaths(const Func& func) const`

#### enum `uba::CompactPathTable::(anonymous)`  
`enum`  
_L55-55_
- desc: This number is arbitrary.. don't know how many folders/dots deep something can be. We want it to be as low as possible to catch corrupt tables

#### struct `uba::CompactPathTable::AddContext`  
`struct AddContext`  
_L56-64_
- L58 _public member_ `const CompactPathTable& fromTable;`
- L59 _public member_ `StringBuffer<> path;`
- L60 _public member_ `u32 fromOffsets[MaxSegments] = { 0 };`
- L61 _public member_ `u32 toOffsets[MaxSegments] = { 0 };`
- L62 _public member_ `u32 pathOffsets[MaxSegments] = { 0 };`
- L63 _public member_ `u32 offsetsCount = 1;`

#### class `uba::CompactCasKeyTable`  
`class CompactCasKeyTable`  
_L83-137_
- L86 _public prototype_ `CompactCasKeyTable(u64 reserveOffsetsCount = 1024);`
- L87 _public prototype_ `~CompactCasKeyTable();`
- L89 _public prototype_ `u32 Add(const CasKey& casKey, u64 stringOffset, u32& outRequiredCasTableSize);`
- L90 _public prototype_ `u32 AddNoLock(const CasKey& casKey, u64 stringOffset);`
- L93 _public prototype_ `template<typename Func> void TraverseOffsets(const CasKey& casKey, const Func& func) const;`
- L95 _public prototype_ `void GetKey(CasKey& outKey, u64 offset) const;`
- L96 _public prototype_ `bool GetPathAndKey(StringBufferBase& outPath, CasKey& outKey, const CompactPathTable& pathTable, u64 offset) const;`
- L98 _public prototype_ `u8* GetMemory();`
- L99 _public prototype_ `u32 GetSize();`
- L101 _public prototype_ `void ReadMem(BinaryReader& reader, bool populateLookup);`
- L102 _public prototype_ `u8* BeginCommit(u64 size);`
- L103 _public prototype_ `void EndCommit(u8* data, u64 written);`
- L104 _public prototype_ `void Swap(CompactCasKeyTable& other);`
- L106 _public prototype_ `void Debug(const CompactPathTable& pathTable);`
- L108 _public function_ `u64 GetKeyCount()`
- L111 _private prototype_ `u32* InternalAdd(const CasKey& casKey, u64 stringOffset, bool& outAdded);`
- L113 _private member_ `Futex m_lock;`
- L114 _private member_ `MemoryBlock m_casKeyTableMem;`
- L133 _private member_ `HashMap<CasKey, Value, true> m_offsets;`
- L135 _private prototype_ `CompactCasKeyTable(const CompactCasKeyTable&) = delete;`
- L136 _private prototype_ `void operator=(const CompactCasKeyTable&) = delete;`
- L153 _function_ `template<typename Func> void CompactCasKeyTable::TraverseOffsets(const CasKey& casKey, const Func& func) const`

#### struct `uba::CompactCasKeyTable::StringAndKey`  
`struct StringAndKey`  
_L116-120_
- L118 _public member_ `u32 stringOffset;`
- L119 _public member_ `u32 casKeyOffset;`

#### struct `uba::CompactCasKeyTable::Value`  
`struct Value`  
_L122-131_
- L130 _public member_ `u32 count;` — If count is 1, single is set, otherwise array is allocated up to 8 elements and contains two offsets per entry. After 8 it turns to a stringlookup

#### union `uba::CompactCasKeyTable::Value::(anonymous)`  
``  
_L125-129_

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace uba`
- L16 _variable_ `static constexpr u32 PathTableMaxSize = 128*1024*1024;` (scope `uba`) — Max size for string memory
- L17 _variable_ `static constexpr u32 CasKeyTableMaxSize = 256*1024*1024;` (scope `uba`)
- L55 _enumerator_ `enum { MaxSegments = 48 }; struct AddContext { const CompactPathTable& fromTable; StringBuffer<> path; u32 fromOffsets[MaxSegments] = { 0 }; u32 toOffsets[MaxSegments] = { 0 }; u32 pathOffsets[MaxSegments] = { 0 };` (scope `uba::CompactPathTable::__anon9095d6710103`) — This number is arbitrary.. don't know how many folders/dots deep something can be. We want it to be as low as possible to catch corrupt tables
- L126 _member_ `StringAndKey single;` (scope `uba::CompactCasKeyTable::Value::__anon9095d671020a`)
- L127 _member_ `StringAndKey* array;` (scope `uba::CompactCasKeyTable::Value::__anon9095d671020a`)
- L128 _member_ `UnorderedMap<u32, u32>* stringLookup;` (scope `uba::CompactCasKeyTable::Value::__anon9095d671020a`)

### `Source/Programs/UnrealBuildAccelerator/Common/Public/UbaConfig.h` (Public)


#### class `uba::ConfigTable`  
`class ConfigTable`  
_L16-50_
- L19 _public prototype_ `bool GetValueAsString(const tchar*& out, const tchar* key) const;`
- L20 _public prototype_ `bool GetValueAsString(TString& out, const tchar* key) const;`
- L21 _public prototype_ `bool GetValueAsU32(u32& out, const tchar* key) const;`
- L22 _public prototype_ `bool GetValueAsU64(u64& out, const tchar* key) const;`
- L23 _public prototype_ `bool GetValueAsBytes(u64& out, const tchar* key) const;`
- L24 _public prototype_ `bool GetValueAsInt(int& out, const tchar* key) const;`
- L25 _public prototype_ `bool GetValueAsBool(bool& out, const tchar* key) const;`
- L27 _public prototype_ `const ConfigTable* GetTable(const tchar* name) const;`
- L30 _public function_ `template<typename Func > void IterateTables(const Func& func) const`
- L32 _public prototype_ `ConfigTable& AddTable(const tchar* name);`
- L34 _public prototype_ `void AddValue(const tchar* key, int value);`
- L35 _public prototype_ `void AddValue(const tchar* key, u32 value);`
- L36 _public prototype_ `void AddValue(const tchar* key, u64 value);`
- L37 _public prototype_ `void AddValue(const tchar* key, bool value);`
- L38 _public prototype_ `void AddValue(const tchar* key, const tchar* str);`
- L40 _public prototype_ `bool SaveToText(Logger& logger, Vector<char>& outText) const;`
- L41 _public prototype_ `bool LoadFromText(Logger& logger, const char* text, u64 textLen);`
- L44 _private member_ `ConfigTable* m_parent = nullptr;`
- L47 _private member_ `Map<TString, Value> m_values;`
- L48 _private member_ `UnorderedMap<TString, ConfigTable> m_tables;`

#### enum `uba::ConfigTable::ValueType`  
`enum ValueType`  
_L45-45_
- L45 _public enumerator_ `enum ValueType { ValueType_Value, ValueType_String }; struct Value { ValueType type; TString string; }; Map<TString`
- L45 _public enumerator_ `enum ValueType { ValueType_Value, ValueType_String }; struct Value { ValueType type; TString string; }; Map<TString`

#### struct `uba::ConfigTable::Value`  
`struct Value`  
_L46-46_
- L46 _public member_ `struct Value { ValueType type; TString string; };`
- L46 _public member_ `struct Value { ValueType type; TString string; };`

#### class `uba::Config`  
`class Config : public ConfigTable`  
_L53-62_
- inherits: `ConfigTable`
- L56 _public prototype_ `bool LoadFromFile(Logger& logger, const tchar* configFile);`
- L57 _public prototype_ `bool IsLoaded() const;`
- L59 _public prototype_ `bool SaveToFile(Logger& logger, const tchar* configFile) const;`
- L61 _public member_ `bool m_isLoaded = false;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace uba`

### `Source/Programs/UnrealBuildAccelerator/Common/Public/UbaCoordinator.h` (Public)


#### struct `uba::CoordinatorCreateInfo`  
`struct CoordinatorCreateInfo`  
_L7-13_
- L9 _public member_ `const tchar* workDir = nullptr;`
- L10 _public member_ `const tchar* binariesDir = nullptr;`
- L11 _public member_ `u32 maxCoreCount = 0;`
- L12 _public member_ `bool logging = false;`

#### class `uba::Coordinator`  
`class Coordinator`  
_L15-35_
- L18 _public typedef_ `using AddClientCallback = bool(void* userData, const tchar* ip, u16 port, const tchar* crypto);`
- L19 _public prototype_ `virtual void SetAddClientCallback(AddClientCallback* callback, void* userData) = 0;`
- L20 _public prototype_ `virtual void SetTargetCoreCount(u32 count) = 0;`
- L22 _public typedef_ `using UpdateStatusCallback = void(void* userData, const tchar* status);`
- L23 _public function_ `virtual void SetUpdateStatusCallback(UpdateStatusCallback* callback, void* userData)`
- L25 _public typedef_ `using LogCallback = void(void* userData, LogEntryType type, const tchar* str);`
- L26 _public function_ `virtual void SetLogCallback(LogCallback* callback, void* userData)`
- L28 _public function_ `virtual bool RequestCacheServer(tchar* outEndpoint, u32 outEndpointCapacity, Guid& outSessionKey, bool& outWriteAccess)`
- L34 _public function_ `virtual void Stop()` — Tells the coordinator that no more agents should be requested. Subsequent SetTargetCoreCount calls become no-ops. Called before the coordinator-update loop is shut down so a final in-flight SetTargetCoreCount returns immediately instead of spawning new agents whose connect we'll then have to abort.

#### Free symbols / members of external scopes

- L5 _namespace_ `namespace uba`
- L38 _typedef_ `using UbaCreateCoordinatorFunc = Coordinator*(const CoordinatorCreateInfo& info);` (scope `uba`) — This is how the function signatures creating/destroying the coordinator module needs to exported
- L39 _typedef_ `using UbaDestroyCoordinatorFunc = void(Coordinator* coordinator);` (scope `uba`)

### `Source/Programs/UnrealBuildAccelerator/Common/Public/UbaCoordinatorWrapper.h` (Public)


#### class `uba::CoordinatorWrapper`  
`class CoordinatorWrapper`  
_L24-160_
- L27 _public function_ `bool Create(Logger& logger, const tchar* coordinatorType, const CoordinatorCreateInfo& info, NetworkBackend& networkBackend, NetworkServer& networkServer, Trace& trace, u32 traceRow = 10)`
- L91 _public function_ `bool IsCreated()`
- L96 _public function_ `void SetScheduler(Scheduler* scheduler)`
- L101 _public function_ `bool RequestCacheServer(StringBufferBase& outEndpoint, Guid& outSessionKey, bool& outWriteAccess)`
- L110 _public function_ `bool RequestHelpers(u32 maxCoreCount)`
- L121 _public function_ `void ThreadUpdate(u32 maxCoreCount)`
- L134 _public function_ `void Destroy()`
- L151 _public member_ `Coordinator* m_coordinator = nullptr;`
- L152 _public member_ `NetworkBackend* m_networkBackend = nullptr;`
- L153 _public member_ `NetworkServer* m_networkServer = nullptr;`
- L154 _public member_ `Trace* m_trace;`
- L155 _public member_ `Scheduler* m_scheduler = nullptr;`
- L156 _public member_ `UbaDestroyCoordinatorFunc* m_destroyCoordinator = nullptr;`
- L157 _public member_ `Event m_loopCoordinator;`
- L158 _public member_ `Thread m_coordinatorThread;`
- L159 _public member_ `u32 m_traceRow = 0;`

#### Free symbols / members of external scopes

- L14 _macro_ `#define GetProcAddress dlsym`
- L15 _macro_ `#define LoadLibrary(name) dlopen(name, RTLD_LAZY);`
- L16 _macro_ `#define LoadLibraryError dlerror()`
- L17 _macro_ `#define HMODULE void*`
- L19 _macro_ `#define LoadLibraryError LastErrorToText().data`
- L22 _namespace_ `namespace uba`
- L64 _function_ `` (scope `uba::CoordinatorWrapper::Create`)
- L117 _function_ `m_coordinatorThread.Start([this, mcc = maxCoreCount]() { ThreadUpdate(mcc); return 0; }, TC("UbaC` (scope `uba::CoordinatorWrapper::RequestHelpers`)

### `Source/Programs/UnrealBuildAccelerator/Common/Public/UbaCrypto.h` (Public)


#### enum `uba::CryptoKey`  
`enum CryptoKey : u64`  
_L11-11_

#### class `uba::Crypto`  
`class Crypto`  
_L14-23_
- L17 _public prototype_ `static CryptoKey CreateKey(Logger& logger, const u8* key128);`
- L18 _public prototype_ `static CryptoKey DuplicateKey(Logger& logger, CryptoKey original);`
- L19 _public prototype_ `static void DestroyKey(CryptoKey key);`
- L21 _public prototype_ `static bool Encrypt(Logger& logger, CryptoKey key, u8* data, u32 size, Guid& inOutInitVector);`
- L22 _public prototype_ `static bool Decrypt(Logger& logger, CryptoKey key, u8* data, u32 size, Guid& inOutInitVector);`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace uba`
- L12 _variable_ `inline constexpr CryptoKey InvalidCryptoKey = (CryptoKey)0;` (scope `uba`)
- L25 _prototype_ `bool CryptoFromString(u8* out, u32 outSize, const tchar* str);` (scope `uba`)

### `Source/Programs/UnrealBuildAccelerator/Common/Public/UbaDefaultConstants.h` (Public)


#### Free symbols / members of external scopes

- L7 _namespace_ `namespace uba`
- L10 _variable_ `static constexpr u16 DefaultPort = 1345;` (scope `uba`) — Default constants
- L11 _variable_ `static constexpr u16 DefaultStorageProxyPort = DefaultPort + 1;` (scope `uba`)
- L12 _variable_ `static constexpr u16 DefaultCachePort = DefaultPort + 2;` (scope `uba`)
- L13 _variable_ `static constexpr u32 SendDefaultSize = 256*1024;` (scope `uba`)
- L14 _variable_ `static constexpr u32 DefaultNetworkReceiveTimeoutSeconds = 10*60;` (scope `uba`)
- L15 _variable_ `static constexpr u32 DefaultNetworkSendTimeoutSeconds = 10*60;` (scope `uba`)
- L18 _variable_ `static constexpr u32 ProcessPriority_Normal = 0x00000020;` (scope `uba`)
- L19 _variable_ `static constexpr u32 ProcessPriority_BelowNormal = 0x00004000;` (scope `uba`)
- L21 _variable_ `static constexpr u32 DefaultMemoryWorkingSet = 512*1024*1024;` (scope `uba`)

### `Source/Programs/UnrealBuildAccelerator/Common/Public/UbaDependencyCrawler.h` (Public)


#### class `uba::DependencyCrawler`  
`class DependencyCrawler`  
_L29-124_
- L32 _public prototype_ `inline DependencyCrawler(Logger& logger, WorkManager& workManager, u32 bottleneckMax = ~0u);`
- L34 _public typedef_ `using FileExistsFunc = Function<bool(const StringView& fileName, u32& outAttr)>;`
- L35 _public typedef_ `using FileFunc = Function<void(const StringView& file, bool isDirectory)>;`
- L36 _public typedef_ `using TraverseFilesFunc = Function<void(const StringView& path, const FileFunc& fileFunc)>;`
- L38 _public typedef_ `using AccessFileFunc = Function<bool(const void* data, u64 dataSize)>;`
- L39 _public typedef_ `using DevirtualizePathFunc = Function<bool(StringBufferBase& inOut)>;`
- L40 _public typedef_ `using CreateFileFunc = Function<bool(TrackWorkScope& tracker, const StringView& fileName, const AccessFileFunc& func, bool& stopCrawling)>;`
- L42 _public prototype_ `inline void Init(FileExistsFunc&& fileExistsFunc, TraverseFilesFunc&& traverseFilesFunc, bool useBloomFilter = true);`
- L43 _public prototype_ `inline bool AddRsp(const tchar* rsp, const tchar* workDir, CreateFileFunc&& createFileFunc, DevirtualizePathFunc&& devirtualizePathFunc, const tchar* app, DependencyCrawlerType type, u32 ruleIndex);`
- L44 _public prototype_ `inline bool AddCommandLine(const tchar* commandLine, const tchar* workDir, CreateFileFunc&& createFileFunc, DevirtualizePathFunc&& devirtualizePathFunc, const tchar* app, DependencyCrawlerType type, u32 ruleIndex);`
- L46 _public member_ `Logger& m_logger;`
- L47 _public member_ `WorkManager& m_workManager;`
- L55 _public member_ `HandledFiles m_handledFiles;`
- L57 _public member_ `Futex m_pchLookupLock;`
- L59 _public member_ `UnorderedMap<StringKey, Pch> m_pchLookup;`
- L60 _public member_ `bool m_useBloomFilter = true;`
- L97 _public member_ `Futex m_builtIncludesHandledLock;`
- L98 _public member_ `UnorderedSet<u32> m_builtIncludesHandled;`
- L99 _public member_ `FileExistsFunc m_fileExistsFunc;`
- L100 _public member_ `TraverseFilesFunc m_traverseFilesFunc;`
- L102 _public member_ `Bottleneck m_bottleneck;`
- L105 _public typedef_ `using CodeFiles = List<CodeFile>;`
- L107 _public prototype_ `inline bool ParseRsp(TrackWorkScope& tracker, Instance& instance, const StringView& rsp, CodeFiles& outCodeFiles);`
- L108 _public prototype_ `template<typename CharType> inline bool ParseRsp2(TrackWorkScope& tracker, Instance& instance, const void* data, u64 dataSize, const tchar* rsp, CodeFiles& outCodeFiles);`
- L109 _public prototype_ `template<typename CharType> inline bool ParseRsp2(TrackWorkScope& tracker, Instance& instance, const void* data, u64 dataSize, const tchar* rsp, CodeFiles& outCodeFiles);`
- L110 _public prototype_ `inline bool ParseCodeFile(TrackWorkScope& tracker, Instance& instance, HandledFiles& handledFiles, const StringView& codeFile, bool parseDefines, const StringView& caller);`
- L111 _public prototype_ `inline bool ParseCodeFile2(TrackWorkScope& tracker, Instance& instance, HandledFiles& handledFiles, const void* data, u64 dataSize, const StringView& codeFile, bool parseDefines);`
- L112 _public prototype_ `inline bool HandleInclude(TrackWorkScope& tracker, Instance& instance, HandledFiles& handledFiles, const StringView& rootPath, const StringView& include, const StringView& codeFile, bool parseDefines);`
- L113 _public prototype_ `inline bool TraverseInclude(TrackWorkScope& tracker, Instance& instance, const StringView& rootPathWithSlash);`
- L114 _public prototype_ `inline bool TraverseCodeFiles(const WorkContext& context, Instance& instance, const CodeFiles& codeFiles, u32 ruleIndex);`
- L116 _public function_ `inline u32 GetBottleneckMax(WorkManager& workManager, u32 bottleneckMax)`
- L126 _function_ `DependencyCrawler::DependencyCrawler(Logger& logger, WorkManager& workManager, u32 bottleneckMax) : m_logger(logger) , m_workManager(workManager) , m_bottleneck(GetBottleneckMax(workManager, bottleneckMax))`
- L133 _function_ `void DependencyCrawler::Init(FileExistsFunc&& fileExistsFunc, TraverseFilesFunc&& traverseFilesFunc, bool useBloomFilter)`
- L141 _function_ `bool DependencyCrawler::AddRsp(const tchar* rsp, const tchar* workDir, CreateFileFunc&& createFileFunc, DevirtualizePathFunc&& devirtualizePathFunc, const tchar* app, DependencyCrawlerType type, u32 ruleIndex)`
- L167 _function_ `bool DependencyCrawler::AddCommandLine(const tchar* commandLine, const tchar* workDir, CreateFileFunc&& createFileFunc, DevirtualizePathFunc&& devirtualizePathFunc, const tchar* app, DependencyCrawlerType type, u32 ruleIndex)`
- L194 _function_ `bool DependencyCrawler::ParseRsp(TrackWorkScope& tracker, Instance& instance, const StringView& rsp, CodeFiles& outCodeFiles)`
- L209 _function_ `template<typename CharType> bool DependencyCrawler::ParseRsp2(TrackWorkScope& tracker, Instance& instance, const void* data, u64 dataSize, const tchar* rsp, CodeFiles& outCodeFiles)`
- L539 _function_ `bool DependencyCrawler::ParsePch(Pch& pch, Instance& instance, const void* data, u64 dataSize)`
- L587 _function_ `bool DependencyCrawler::ParseCodeFile(TrackWorkScope& tracker, Instance& instance, HandledFiles& handledFiles, const StringView& codeFile, bool parseDefines, const StringView& caller)`
- L595 _function_ `bool DependencyCrawler::ParseCodeFile2(TrackWorkScope& tracker, Instance& instance, HandledFiles& handledFiles, const void* data, u64 dataSize, const StringView& codeFile, bool parseDefines)`
- L829 _function_ `bool DependencyCrawler::HandleInclude(TrackWorkScope& tracker, Instance& instance, HandledFiles& handledFiles, const StringView& rootPath, const StringView& include, const StringView& codeFile, bool parseDefines)`
- L865 _function_ `bool DependencyCrawler::TraverseInclude(TrackWorkScope& tracker, Instance& instance, const StringView& rootPathWithSlash)`
- L898 _function_ `inline bool DependencyCrawler::TraverseCodeFiles(const WorkContext& context, Instance& instance, const CodeFiles& codeFiles, u32 ruleIndex)`

#### struct `uba::DependencyCrawler::HandledFile`  
`struct HandledFile`  
_L49-49_
- L49 _public member_ `struct HandledFile { Futex lock; bool handled = false; };`
- L49 _public member_ `struct HandledFile { Futex lock; bool handled = false; };`

#### struct `uba::DependencyCrawler::HandledFiles`  
`struct HandledFiles`  
_L50-54_
- L52 _public member_ `Futex lookupLock;`
- L53 _public member_ `UnorderedMap<StringKey, HandledFile> lookup;`

#### struct `uba::DependencyCrawler::Pch`  
`struct Pch`  
_L58-58_
- L58 _public member_ `struct Pch { Futex lock; bool handled = false; UnorderedSet<StringKey> files; };`
- L58 _public member_ `struct Pch { Futex lock; bool handled = false; UnorderedSet<StringKey> files; };`
- L58 _public member_ `struct Pch { Futex lock; bool handled = false; UnorderedSet<StringKey> files; };`

#### struct `uba::DependencyCrawler::IncludeRoot`  
`struct IncludeRoot`  
_L62-66_
- L64 _public member_ `TString path;`
- L65 _public member_ `BloomFilter bloomFilter;`

#### struct `uba::DependencyCrawler::Instance`  
`struct Instance`  
_L68-87_
- L70 _public member_ `DependencyCrawlerType type;`
- L71 _public member_ `TString application;`
- L72 _public member_ `TString rsp;`
- L73 _public member_ `TString workDir;`
- L74 _public member_ `TString platform;`
- L75 _public member_ `TString compiledPlatform;`
- L76 _public member_ `TString overriddenPlatformName;`
- L77 _public member_ `TString builtinIncludesDir;`
- L78 _public member_ `TString frameworksDir;`
- L79 _public member_ `bool platformIsExtension = false;`
- L80 _public member_ `bool usePch = false;`
- L81 _public member_ `CreateFileFunc createFileFunc;`
- L82 _public member_ `DevirtualizePathFunc devirtualizePathFunc;`
- L83 _public member_ `Vector<IncludeRoot> includeRoots;`
- L84 _public member_ `Pch* pch = nullptr;`
- L86 _public member_ `Atomic<u32> refCount = 0;`

#### struct `uba::DependencyCrawler::InstanceRef`  
`struct InstanceRef`  
_L89-95_
- L91 _public function_ `InstanceRef(Instance& i) : instance(i)`
- L92 _public function_ `InstanceRef(const InstanceRef& i) : instance(i.instance)`
- L93 _public function_ `~InstanceRef()`
- L94 _public member_ `Instance& instance;`

#### struct `uba::DependencyCrawler::CodeFile`  
`struct CodeFile`  
_L104-104_
- L104 _public member_ `struct CodeFile { TString path; bool hasPch = false; };`
- L104 _public member_ `struct CodeFile { TString path; bool hasPch = false; };`

#### struct `uba::DependencyCrawler::ParseRsp2::MsvcOptionWithArg`  
`struct MsvcOptionWithArg`  
_L259-259_
- L259 _public member_ `struct MsvcOptionWithArg { const StringView name; bool addRoot; };`
- L259 _public member_ `struct MsvcOptionWithArg { const StringView name; bool addRoot; };`

#### enum `uba::DependencyCrawler::ParseRsp2::ArgType`  
`enum ArgType`  
_L394-394_
- L394 _public enumerator_ `enum ArgType { ArgType_None, ArgType_Ignore, ArgType_RootPath, ArgType_ISysRootPath, ArgType_ResourceDir, ArgType_Code }; struct OptionWithArg { const StringView name; ArgType type; }; constexpr const OptionWithArg dashOptionsWithArg[] = { { TCV("-D"), ArgType_Ignore }, { TCV("-x"), ArgType_Ignore }, { TCV("-o"), ArgType_Ignore }, { TCV("-include"), ArgType_Code },`
- L394 _public enumerator_ `enum ArgType { ArgType_None, ArgType_Ignore, ArgType_RootPath, ArgType_ISysRootPath, ArgType_ResourceDir, ArgType_Code }; struct OptionWithArg { const StringView name; ArgType type; }; constexpr const OptionWithArg dashOptionsWithArg[] = { { TCV("-D"), ArgType_Ignore }, { TCV("-x"), ArgType_Ignore }, { TCV("-o"), ArgType_Ignore }, { TCV("-include"), ArgType_Code },`
- L394 _public enumerator_ `enum ArgType { ArgType_None, ArgType_Ignore, ArgType_RootPath, ArgType_ISysRootPath, ArgType_ResourceDir, ArgType_Code }; struct OptionWithArg { const StringView name; ArgType type; }; constexpr const OptionWithArg dashOptionsWithArg[] = { { TCV("-D"), ArgType_Ignore }, { TCV("-x"), ArgType_Ignore }, { TCV("-o"), ArgType_Ignore }, { TCV("-include"), ArgType_Code },`
- L394 _public enumerator_ `enum ArgType { ArgType_None, ArgType_Ignore, ArgType_RootPath, ArgType_ISysRootPath, ArgType_ResourceDir, ArgType_Code }; struct OptionWithArg { const StringView name; ArgType type; }; constexpr const OptionWithArg dashOptionsWithArg[] = { { TCV("-D"), ArgType_Ignore }, { TCV("-x"), ArgType_Ignore }, { TCV("-o"), ArgType_Ignore }, { TCV("-include"), ArgType_Code },`
- L394 _public enumerator_ `enum ArgType { ArgType_None, ArgType_Ignore, ArgType_RootPath, ArgType_ISysRootPath, ArgType_ResourceDir, ArgType_Code }; struct OptionWithArg { const StringView name; ArgType type; }; constexpr const OptionWithArg dashOptionsWithArg[] = { { TCV("-D"), ArgType_Ignore }, { TCV("-x"), ArgType_Ignore }, { TCV("-o"), ArgType_Ignore }, { TCV("-include"), ArgType_Code },`
- L394 _public enumerator_ `enum ArgType { ArgType_None, ArgType_Ignore, ArgType_RootPath, ArgType_ISysRootPath, ArgType_ResourceDir, ArgType_Code }; struct OptionWithArg { const StringView name; ArgType type; }; constexpr const OptionWithArg dashOptionsWithArg[] = { { TCV("-D"), ArgType_Ignore }, { TCV("-x"), ArgType_Ignore }, { TCV("-o"), ArgType_Ignore }, { TCV("-include"), ArgType_Code },`

#### struct `uba::DependencyCrawler::ParseRsp2::OptionWithArg`  
`struct OptionWithArg`  
_L395-395_
- L395 _public member_ `struct OptionWithArg { const StringView name; ArgType type; };`
- L395 _public member_ `struct OptionWithArg { const StringView name; ArgType type; };`

#### Free symbols / members of external scopes

- L15 _macro_ `#define UBA_LOG_DEVIRTUALIZATION_ERROR(x, ...) m_logger.Info(TC(x), __VA_ARGS__)`
- L17 _macro_ `#define UBA_LOG_DEVIRTUALIZATION_ERROR(x, ...) do { } while(false)`
- L20 _macro_ `#define UBA_CRAWLER_DEBUG_PRINT(str1, str2) //wprintf(TC("") str1 ": %s\n", str2);`
- L27 _namespace_ `namespace uba`
- L158 _function_ `` (scope `uba::DependencyCrawler::AddRsp`)
- L185 _function_ `` (scope `uba::DependencyCrawler::AddCommandLine`)
- L203 _function_ `if (!instance.createFileFunc(tracker, fixedPath, [&](const void* data, u64 dataSize) { return ParseRsp2<char>(tracker, instance, data, dataSize, rsp.data, outCodeFiles); }, stopCrawling)) return stopCrawling ? false : m_logger.Warning(TC("Failed to pars` (scope `uba::DependencyCrawler::ParseRsp`)
- L212 _function_ `` (scope `uba::DependencyCrawler::ParseRsp2`)
- L246 _function_ `` (scope `uba::DependencyCrawler::ParseRsp2::__anon6a1ea19e0502`)
- L255 _function_ `auto IgnoreOption = [](const StringView& path)` (scope `uba::DependencyCrawler::ParseRsp2`)
- L542 _function_ `` (scope `uba::DependencyCrawler::ParsePch`)
- L590 _function_ `if (!instance.createFileFunc(tracker, codeFile, [&](const void* data, u64 dataSize) { return ParseCodeFile2(tracker, instance, handledFiles, data, dataSize, codeFile, parseDefines); }, stopCrawling)) return stopCrawling ? false : m_logger.Warning(TC("Failed to parse code file %s fou` (scope `uba::DependencyCrawler::ParseCodeFile`)
- L716 _function_ `` (scope `uba::DependencyCrawler::ParseCodeFile2`)
- L869 _function_ `` (scope `uba::DependencyCrawler::TraverseInclude`)
- L875 _function_ `` (scope `uba::DependencyCrawler::TraverseInclude::__anon6a1ea19e0f02`)
- L922 _function_ `` (scope `uba::DependencyCrawler::TraverseCodeFiles`)

### `Source/Programs/UnrealBuildAccelerator/Common/Public/UbaDirectoryIterator.h` (Public)


#### struct `uba::DirectoryEntry`  
`struct DirectoryEntry`  
_L14-23_
- L16 _public member_ `const tchar* name;`
- L17 _public member_ `u32 nameLen;`
- L18 _public member_ `u64 lastWritten;`
- L19 _public member_ `u32 attributes;`
- L20 _public member_ `u32 volumeSerial;`
- L21 _public member_ `u64 id;`
- L22 _public member_ `u64 size;`

#### struct `uba::DirectoryInfo`  
`struct DirectoryInfo`  
_L25-30_
- L27 _public member_ `u32 attributes;`
- L28 _public member_ `u32 volumeSerial;`
- L29 _public member_ `u64 id;`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace uba`
- L32 _typedef_ `using IteratorFunc = Function<void(const DirectoryEntry&)>;` (scope `uba`)
- L33 _typedef_ `using DirectoryInfoFunc = Function<void(const DirectoryInfo&)>;` (scope `uba`)
- L41 _prototype_ `extern "C" NTSTATUS NtQueryDirectoryFile(HANDLE FileHandle, HANDLE Event, PIO_APC_ROUTINE ApcRoutine, PVOID ApcContext, PIO_STATUS_BLOCK IoStatusBlock, PVOID FileInformation, ULONG Length, FILE_INFORMATION_CLASS FileInformationClass, BOOLEAN ReturnSingleEntry, PUNICODE_STRING FileName, BOOLEAN RestartScan)`
- L43 _namespace_ `namespace uba`
- L45 _function_ `inline bool TraverseDir(Logger& logger, StringView dirPath, const IteratorFunc& iteratorFunc, bool errorOnNotFound = false, const DirectoryInfoFunc& infoFunc = {})` (scope `uba`)
- L67 _function_ `auto mg = MakeGuard([&]() { KernelStats::GetCurrent().traverseDir += timer; });` (scope `uba::TraverseDir`)
- L93 _function_ `auto hg = MakeGuard([&]() { NtClose(handle); });` (scope `uba::TraverseDir`)
- L175 _namespace_ `namespace uba`
- L194 _function_ `auto dg = MakeGuard([&]() { closedir(dir); });` (scope `uba::TraverseDir`)

### `Source/Programs/UnrealBuildAccelerator/Common/Public/UbaDirectoryTableHolder.h` (Public)


#### struct `uba::DirectoryTableOverlay`  
`struct DirectoryTableOverlay`  
_L16-26_
- L18 _public member_ `ReaderWriterLock lock;`
- L19 _public member_ `FileMappingHandle handle;`
- L20 _public member_ `u8* memory = nullptr;`
- L21 _public member_ `u32 committed = 0;`
- L22 _public member_ `u32 size = 0;`
- L24 _public member_ `UnorderedMap<StringKey, Dir> lookup;`
- L25 _public member_ `Vector<StringKey> roots;`

#### struct `uba::DirectoryTableOverlay::Dir`  
`struct Dir`  
_L23-23_
- L23 _public member_ `struct Dir { u32 offset = 0; UnorderedMap<StringKey, u32> files; };`
- L23 _public member_ `struct Dir { u32 offset = 0; UnorderedMap<StringKey, u32> files; };`

#### struct `uba::OverlayEditScope`  
`struct OverlayEditScope`  
_L30-36_
- L32 _public prototype_ `OverlayEditScope(DirectoryTableOverlay& o);`
- L33 _public prototype_ `~OverlayEditScope();`
- L35 _public member_ `DirectoryTableOverlay& overlay;`

#### class `uba::DirectoryTableHolder`  
`class DirectoryTableHolder`  
_L40-114_
- L43 _public prototype_ `DirectoryTableHolder(LogWriter& logWriter, const tchar* logPrefix = TC(""), bool runningRemote = false);`
- L44 _public prototype_ `virtual ~DirectoryTableHolder();`
- L45 _public prototype_ `void SetTreatTempDirAsEmpty();` — We never want to populate files in Temp
- L47 _public prototype_ `bool RefreshDirectory(const tchar* dirPath, bool forceRegister = false);` — Tell uba a directory on disk has been changed by some other system while session is running
- L48 _public prototype_ `bool RegisterNewFile(const tchar* filePath);` — Tell uba a new file on disk has been added by some other system while session is running
- L49 _public prototype_ `void RegisterDeleteFile(const tchar* filePath);` — Tell uba a file on disk has been deleted by some other system while session is running
- L50 _public prototype_ `bool RegisterNewDirectory(const tchar* directoryPath, bool ensureAncestors = false);` — Tell uba a directory on disk has been added by some other system while session is running
- L51 _public prototype_ `bool EnsurePath(StringView path);` — Ensure path's parent chain is at populatedOffset==1, so a subsequent register/write of path will see well-formed ancestors. The leaf is never inspected (no GetFileInformation), so it need not exist on disk yet. Repairs ancestors stuck at populatedOffset==2 from out-of-order RegisterNewDirectory call
- L53 _public prototype_ `const u8* GetDirectoryTableMemory();`
- L54 _public prototype_ `DirTableSize GetDirectoryTableSize(DirectoryTableOverlay* overlay);`
- L56 _public prototype_ `void CreateOverlay(DirectoryTableOverlay& overlay);`
- L57 _public prototype_ `void ResetOverlay(DirectoryTableOverlay& overlay, void* data, u64 dataSize);`
- L58 _public prototype_ `bool EnsureOverlayMemory(DirectoryTableOverlay& overlay, u64 neededSize);`
- L59 _public prototype_ `void DestroyOverlay(DirectoryTableOverlay& overlay);`
- L61 _public prototype_ `void PrintOverlay(DirectoryTableOverlay& overlay);`
- L62 _public prototype_ `void PrintOverlay(DirectoryTableOverlay& overlay, DirectoryTableOverlay::Dir& dir, StringBufferBase& path);`
- L64 _public prototype_ `bool RegisterOverlayCreateOrWrite(OverlayEditScope& scope, StringKey filePathKey, StringView filePath, u64 fileSize, u64 lastWriteTime, u32 attributes, StringView symlinkContent = {});`
- L65 _public prototype_ `bool RegisterOverlayDelete(OverlayEditScope& scope, StringKey filePathKey, StringView filePath);`
- L66 _public prototype_ `bool RegisterNonRootedDir(OverlayEditScope& scope, StringView dirPath);` — Will not register parent dirs recursively
- L68 _public typedef_ `using GetOverlayFileInformation = Function<bool(FileInformation& out, StringKey, StringView)>;`
- L69 _public prototype_ `bool PopulateOverlayFile(DirectoryTableOverlay& overlay, StringView filePath, const GetOverlayFileInformation& getFileInformation = {});`
- L71 _public prototype_ `bool AddOverlayFile(DirTableOffset& outOffset, OverlayEditScope& scope, StringView filePath);`
- L72 _public prototype_ `bool WriteOverlayEntry(OverlayEditScope& scope, StringView filePath, const FileInformation& fileInfo, StringView symlinkContent = {}, DirTableOffset* outOffset = nullptr);`
- L73 _public prototype_ `bool WriteOverlayEntry(OverlayEditScope& scope, StringKey dirKey, StringView filePath, StringView fileName, const FileInformation& fileInfo, bool populateMainTableParentDir, StringView symlinkContent = {}, DirTableOffset* outOffset = nullptr);`
- L74 _public prototype_ `bool WriteOverlayEntry(OverlayEditScope& scope, StringKey dirKey, DirectoryTableOverlay::Dir& dir, StringView fileName, const FileInformation& fileInfo, u32& outFileOffset, StringView symlinkContent = {});`
- L75 _public prototype_ `bool WriteOverlayDirInLookup(OverlayEditScope& scope, StringView tempDir);`
- L76 _public prototype_ `bool WriteOverlayDirectoryEntriesRecursive(OverlayEditScope& scope, StringKey filePathKey, StringView filePath);`
- L78 _public prototype_ `bool RegisterCreateFileForWrite(StringKey filePathKey, StringView filePath, u64 fileSize, u64 lastWriteTime, u32 attributes, bool registerRealFile, bool invalidateStorage);`
- L79 _public prototype_ `bool RegisterDeleteFile(StringKey filePathKey, StringView filePath);`
- L81 _public prototype_ `u32 WriteDirectoryEntries(StringKey dirKey, StringView dirPath, DirTableOffset* outTableOffset = nullptr);`
- L82 _public prototype_ `void WriteDirectoryEntriesRecursive(DirTableOffset& outTableOffset, StringKey dirKey, StringView dirPath, StringKey tableOffsetIsFile);`
- L83 _public prototype_ `bool WriteDirectoryEntriesInternal(DirTableOffset& outTableOffset, DirectoryTable::Directory& dir, const StringKey& dirKey, StringView dirPath, bool isRefresh);`
- L85 _public prototype_ `void EnsureDirectoryTableMemory(u64 neededSize);`
- L87 _public prototype_ `virtual bool IsInTemp(StringView path);`
- L88 _public prototype_ `virtual void FileEntryAdded(StringKey filePathKey, u64 lastWritten, u64 size);`
- L89 _public prototype_ `virtual bool ShouldWriteToDisk(StringView filePath);`
- L90 _public prototype_ `virtual void InvalidateCachedFileInfo(const StringKey& filePathKey);`
- L92 _public prototype_ `bool WriteDirectoryTableToFile(StringView filePath);`
- L95 _public prototype_ `void CreateDebugLogger(const tchar* outputFile);`
- L98 _public member_ `MutableLogger m_logger;`
- L99 _public member_ `bool m_runningRemote;`
- L101 _public member_ `Atomic<u64> m_fileIndexCounter = 8000000000;` — Try not to collide with ntfs
- L102 _public member_ `MemoryBlock m_directoryTableMemory;`
- L103 _public member_ `FileMappingHandle m_directoryTableHandle;`
- L104 _public member_ `u8* m_directoryTableMem;`
- L105 _public member_ `u64 m_directoryTableMemCommitted = 0;`
- L106 _public member_ `DirectoryTable m_directoryTable;`
- L107 _public member_ `StringKey m_directoryForcedEmpty;`
- L108 _public member_ `VolumeCache m_volumeCache;`
- L111 _public member_ `Logger* m_debugLogger = nullptr;`

#### struct `uba::DirTableSnapshot`  
`struct DirTableSnapshot`  
_L121-127_
- L123 _public member_ `FileMappingHandle handle;`
- L124 _public member_ `u8* mappedMemory = 0;` — consumers must mmap at same VA — m_lookup buckets hold raw Node*
- L125 _public member_ `u32 mappedSize = 0;`
- L126 _public member_ `Atomic<u32> refCount = 0;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace uba`
- L118 _prototype_ `bool GetDirKey(StringKey& outDirKey, StringBufferBase& outDirPath, const tchar*& outLastSlash, StringView filePath);` (scope `uba`)
- L119 _prototype_ `StringKey GetKeyAndFixedName(StringBuffer<>& outFixedFilePath, const tchar* filePath);` (scope `uba`)
- L128 _prototype_ `bool CreateDirectoryTableSnapshot(DirTableSnapshot& out, u64 mappingSize, const u8* prevSnapshot, u64 prevSnapshotSize, const u8* mainMem, u32 mainSize, const u8* overlayMem, u32 overlaySize, const tchar* hint, Logger& logger);` (scope `uba`)

### `Source/Programs/UnrealBuildAccelerator/Common/Public/UbaEnvironment.h` (Public)


#### enum `uba::MutexHandle`  
`enum MutexHandle : u64`  
_L9-9_

#### enum `uba::ProcHandle`  
`enum ProcHandle : u64`  
_L15-15_

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace uba`
- L10 _variable_ `inline constexpr MutexHandle InvalidMutexHandle = MutexHandle(0);` (scope `uba`)
- L11 _prototype_ `MutexHandle CreateMutexW(bool bInitialOwner, const tchar* name);` (scope `uba`)
- L12 _prototype_ `void ReleaseMutex(MutexHandle mutex);` (scope `uba`)
- L13 _prototype_ `void CloseMutex(MutexHandle mutex);` (scope `uba`)
- L16 _variable_ `inline constexpr ProcHandle InvalidProcHandle = (ProcHandle)0ull;` (scope `uba`)
- L17 _prototype_ `ProcHandle GetCurrentProcessHandle();` (scope `uba`)
- L19 _prototype_ `u32 GetEnvironmentVariableW(const tchar* name, tchar* buffer, u32 nSize);` (scope `uba`)
- L20 _prototype_ `bool SetEnvironmentVariableW(const tchar* name, const tchar* value);` (scope `uba`)
- L21 _prototype_ `u32 ExpandEnvironmentStringsW(const tchar* lpSrc, tchar* lpDst, u32 nSize);` (scope `uba`)
- L22 _prototype_ `u32 GetLogicalProcessorCount();` (scope `uba`)
- L23 _prototype_ `u32 GetProcessorGroupCount();` (scope `uba`)
- L25 _prototype_ `void ElevateCurrentThreadPriority();` (scope `uba`)
- L26 _prototype_ `void PrefetchVirtualMemory(const void* mem, u64 size);` (scope `uba`)
- L28 _prototype_ `void GetMachineId(StringBufferBase& out);` (scope `uba`)
- L29 _prototype_ `bool GetMemoryInfo(Logger& logger, u64& outAvailable, u64& outTotal, u64* outMaxPageFileSize = nullptr);` (scope `uba`)
- L30 _prototype_ `void GetSystemInfo(Logger& logger, StringBufferBase& out);` (scope `uba`)
- L31 _prototype_ `bool GetCpuTime(u64& outTotalTime, u64& outIdleTime);` (scope `uba`)
- L33 _prototype_ `void SetMemoryWorkingSet(Logger& logger, u64 minWorkingSet);` (scope `uba`)
- L34 _prototype_ `void LockMemory(Logger& logger, void* dest, u64 size, const tchar* hint);` (scope `uba`)
- L37 _prototype_ `void SetupOrphanReaper();` (scope `uba`) — Fork sidecar surviving host death; kills every descendant (cgroup.kill on Linux, ps-sid walk on macOS).
- L38 _prototype_ `void CancelProcessTree(int leaderPid);` (scope `uba`) — Synchronous SIGKILL of leader + every descendant via kill(-pgid) + /proc walk by UBA_SESSION_PROCESS.
- L40 _prototype_ `const char* GetOrphanReaperCgroup();` (scope `uba`) — Cgroup v2 path created by SetupOrphanReaper; empty when delegation unavailable.
- L45 _prototype_ `StringView GetUbaWineModulePath();` (scope `uba`)
- L46 _prototype_ `void* GetUbaWineModule();` (scope `uba`)

### `Source/Programs/UnrealBuildAccelerator/Common/Public/UbaFile.h` (Public)


#### struct `uba::FileBasicInformation`  
`struct FileBasicInformation`  
_L53-58_
- L55 _public member_ `u32 attributes = 0;`
- L56 _public member_ `u64 lastWriteTime = 0;`
- L57 _public member_ `u64 size = 0;`

#### struct `uba::FileInformation`  
`struct FileInformation`  
_L64-71_
- L66 _public member_ `u32 attributes = 0;`
- L67 _public member_ `u32 volumeSerialNumber = 0;`
- L68 _public member_ `u64 lastWriteTime = 0;`
- L69 _public member_ `u64 size = 0;`
- L70 _public member_ `u64 index = 0;`

#### class `uba::SearchPathCache`  
`class SearchPathCache`  
_L121-129_
- L124 _public prototype_ `bool SearchPathForFile(Logger& logger, StringBufferBase& out, StringView file, StringView workingDir, StringView applicationDir);`
- L127 _private member_ `Futex m_lock;`
- L128 _private member_ `UnorderedMap<TString, TString> m_map;`

#### class `uba::DirectoryCache`  
`class DirectoryCache`  
_L133-143_
- L136 _public prototype_ `bool CreateDirectory(Logger& logger, const tchar* dir, bool* outAlreadyExists = nullptr);`
- L137 _public prototype_ `void Clear();`
- L140 _private member_ `Futex m_createdDirsLock;`
- L142 _private member_ `UnorderedMap<TString, CreatedDir> m_createdDirs;`

#### struct `uba::DirectoryCache::CreatedDir`  
`struct CreatedDir`  
_L141-141_
- L141 _public member_ `struct CreatedDir { Futex lock; Atomic<bool> handled = false; };`
- L141 _public member_ `struct CreatedDir { Futex lock; Atomic<bool> handled = false; };`

#### struct `uba::VolumeCache`  
`struct VolumeCache`  
_L194-218_
- L196 _public prototype_ `~VolumeCache();`
- L197 _public prototype_ `bool Init(Logger& logger);`
- L198 _public prototype_ `u32 GetSerialIndex(u32 volumeSerial);`
- L199 _public prototype_ `void Write(BinaryWriter& writer);`
- L200 _public prototype_ `void Read(BinaryReader& reader);`
- L217 _public member_ `Vector<Volume> volumes;`

#### struct `uba::VolumeCache::Volume`  
`struct Volume`  
_L202-215_
- L204 _public member_ `u32 serialNumber = 0;`
- L205 _public member_ `TString drives;`
- L206 _public member_ `FileHandle handle = InvalidFileHandle;`
- L207 _public member_ `u64 prevQueryTime = 0;`
- L208 _public member_ `u64 prevIdleTime = 0;`
- L209 _public member_ `u32 prevReadCount = 0;`
- L210 _public member_ `u32 prevWriteCount = 0;`
- L211 _public member_ `u64 prevReadBytes = 0;`
- L212 _public member_ `u64 prevWriteBytes = 0;`
- L214 _public prototype_ `bool UpdateStats(u8& outBusyPercent, u32& outReadCount, u64& outReadBytes, u32& outWriteCount, u64& outWriteBytes);`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace uba`
- L17 _variable_ `inline constexpr u32 ERROR_FILE_NOT_FOUND = ENOENT;` (scope `uba`)
- L18 _variable_ `inline constexpr u32 ERROR_PATH_NOT_FOUND = ENOENT;` (scope `uba`)
- L19 _variable_ `inline constexpr u32 ERROR_ALREADY_EXISTS = EEXIST;` (scope `uba`)
- L20 _variable_ `inline constexpr u32 ERROR_FILE_EXISTS = EEXIST;` (scope `uba`)
- L21 _variable_ `inline constexpr u32 ERROR_ACCESS_DENIED = EACCES;` (scope `uba`)
- L22 _variable_ `inline constexpr u32 ERROR_DIRECTORY = ENOTDIR;` (scope `uba`)
- L23 _variable_ `inline constexpr u32 ERROR_DIR_NOT_EMPTY = ENOTEMPTY;` (scope `uba`)
- L24 _variable_ `inline constexpr u32 MOVEFILE_REPLACE_EXISTING = 0x00000001;` (scope `uba`)
- L25 _variable_ `inline constexpr u32 INVALID_FILE_ATTRIBUTES = (u32)-1;` (scope `uba`)
- L27 _variable_ `inline constexpr u32 GENERIC_WRITE = 0x40000000L;` (scope `uba`)
- L28 _variable_ `inline constexpr u32 DELETE = 0x00010000L;` (scope `uba`)
- L29 _variable_ `inline constexpr u32 GENERIC_READ = 0x80000000L;` (scope `uba`)
- L30 _variable_ `inline constexpr u32 FILE_WRITE_ATTRIBUTES = 0x100L;` (scope `uba`)
- L32 _variable_ `inline constexpr u32 FILE_SHARE_READ = 0x00000001;` (scope `uba`)
- L33 _variable_ `inline constexpr u32 FILE_SHARE_WRITE = 0x00000002;` (scope `uba`)
- L34 _variable_ `inline constexpr u32 FILE_SHARE_DELETE = 0x00000004;` (scope `uba`)
- L36 _variable_ `inline constexpr u32 FILE_FLAG_NO_BUFFERING = 0;` (scope `uba`)
- L37 _variable_ `inline constexpr u32 FILE_FLAG_OVERLAPPED = 0;` (scope `uba`)
- L38 _variable_ `inline constexpr u32 FILE_FLAG_BACKUP_SEMANTICS = 0x02000000;` (scope `uba`)
- L39 _variable_ `inline constexpr u32 FILE_FLAG_SEQUENTIAL_SCAN = 0;` (scope `uba`)
- L41 _variable_ `inline constexpr u32 CREATE_NEW = 1;` (scope `uba`)
- L42 _variable_ `inline constexpr u32 CREATE_ALWAYS = 2;` (scope `uba`)
- L43 _variable_ `inline constexpr u32 OPEN_EXISTING = 3;` (scope `uba`)
- L45 _variable_ `inline constexpr u32 FILE_SHARE_ALL = 0x00000007;` (scope `uba`)
- L48 _variable_ `inline constexpr u64 OverlappedIoFlag = 0x0000'0001'0000'0000;` (scope `uba`) — Only used by windows
- L59 _prototype_ `bool GetFileBasicInformationByHandle(FileBasicInformation& out, Logger& logger, const tchar* fileName, FileHandle hFile, bool errorOnFail = true);` (scope `uba`)
- L60 _prototype_ `bool GetFileBasicInformation(FileBasicInformation& out, Logger& logger, const tchar* fileName, bool errorOnFail = true);` (scope `uba`)
- L72 _prototype_ `bool GetFileInformationByHandle(FileInformation& out, Logger& logger, const tchar* fileName, FileHandle hFile);` (scope `uba`)
- L73 _prototype_ `bool GetFileInformation(FileInformation& out, Logger& logger, StringView fileName);` (scope `uba`)
- L77 _prototype_ `bool ReadFile(Logger& logger, const tchar* fileName, FileHandle fileHandle, void* b, u64 bufferLen);` (scope `uba`)
- L78 _prototype_ `bool WriteFile(Logger& logger, const tchar* fileName, FileHandle fileHandle, const void* b, u64 bufferLen);` (scope `uba`)
- L79 _prototype_ `bool OpenFileSequentialRead(Logger& logger, const tchar* fileName, FileHandle& outHandle, bool fileNotFoundIsError = true, bool overlapped = false, bool showErrors = true);` (scope `uba`)
- L80 _prototype_ `bool FileExists(Logger& logger, const tchar* fileName, u64* outSize = nullptr, u32* outAttributes = nullptr, u64* lastWriteTime = nullptr);` (scope `uba`)
- L81 _prototype_ `bool SetFilePointer(Logger& logger, const tchar* fileName, FileHandle handle, u64 position);` (scope `uba`)
- L82 _prototype_ `bool SetEndOfFile(Logger& logger, const tchar* fileName, FileHandle handle, u64 size);` (scope `uba`)
- L83 _prototype_ `bool MakeSparse(Logger& logger, const tchar* fileName, FileHandle h, u64 size);` (scope `uba`)
- L84 _prototype_ `bool GetDirectoryOfCurrentModule(Logger& logger, StringBufferBase& out);` (scope `uba`)
- L85 _prototype_ `bool DeleteAllFiles(Logger& logger, const tchar* dir, bool deleteDir = true, u32* count = nullptr);` (scope `uba`)
- L86 _prototype_ `bool SearchPathForFile(Logger& logger, StringBufferBase& out, StringView file, StringView workingDir, StringView applicationDir);` (scope `uba`)
- L90 _prototype_ `FileHandle CreateFileW(const tchar* fileName, u32 desiredAccess, u32 shareMode, u32 createDisp, u32 flagsAndAttributes);` (scope `uba`)
- L91 _prototype_ `bool CloseFile(const tchar* fileName, FileHandle h);` (scope `uba`)
- L92 _prototype_ `bool CreateDirectoryW(const tchar* pathName);` (scope `uba`)
- L93 _prototype_ `bool RemoveDirectoryW(const tchar* pathName);` (scope `uba`)
- L94 _prototype_ `bool DeleteFileW(const tchar* fileName);` (scope `uba`)
- L95 _prototype_ `bool CopyFileW(const tchar* existingFileName, const tchar* newFileName, bool bFailIfExists, u8* scratch = nullptr, u64 scratchSize = 0);` (scope `uba`)
- L96 _prototype_ `u32 GetLongPathNameW(const tchar* lpszShortPath, tchar* lpszLongPath, u32 cchBuffer);` (scope `uba`)
- L97 _prototype_ `bool GetFileLastWriteTime(u64& outTime, FileHandle hFile);` (scope `uba`)
- L98 _prototype_ `bool SetFileLastWriteTime(FileHandle fileHandle, u64 writeTime);` (scope `uba`)
- L99 _prototype_ `bool MoveFileExW(const tchar* existingFileName, const tchar* newFileName, u32 dwFlags);` (scope `uba`)
- L100 _prototype_ `bool GetFileSizeEx(u64& outFileSize, FileHandle hFile);` (scope `uba`)
- L102 _prototype_ `u32 GetFileAttributesW(const tchar* fileName);` (scope `uba`)
- L103 _prototype_ `bool IsReadOnly(u32 attributes);` (scope `uba`)
- L104 _prototype_ `u32 DefaultAttributes(bool execute = false);` (scope `uba`)
- L105 _prototype_ `u32 DefaultDirAttributes();` (scope `uba`)
- L106 _prototype_ `bool CreateHardLinkW(const tchar* newFileName, const tchar* existingFileName);` (scope `uba`)
- L107 _prototype_ `u32 GetFullPathNameW(const tchar* fileName, u32 nBufferLength, tchar* lpBuffer, tchar** lpFilePart);` (scope `uba`)
- L108 _prototype_ `bool SearchPathW(const tchar* a, const tchar* b, const tchar* c, u32 d, tchar* e, tchar** f);` (scope `uba`)
- L109 _prototype_ `u64 GetSystemTimeAsFileTime();` (scope `uba`)
- L110 _prototype_ `u64 GetFileTimeAsSeconds(u64 fileTime);` (scope `uba`)
- L111 _prototype_ `u64 GetFileTimeAsTime(u64 fileTime);` (scope `uba`)
- L112 _prototype_ `u64 GetSecondsAsFileTime(u64 seconds);` (scope `uba`)
- L113 _prototype_ `bool GetCurrentDirectoryW(StringBufferBase& out);` (scope `uba`)
- L114 _prototype_ `bool GetAlternativeUbaPath(Logger& logger, StringBufferBase& out, StringView firstPath, bool isWindowsArm);` (scope `uba`)
- L116 _prototype_ `void ReportSystemError(u32 error);` (scope `uba`)
- L117 _prototype_ `void SetSystemErrorCallback(const Function<void(u32)>& callback);` (scope `uba`)
- L148 _function_ `template<typename LineFunc> bool ReadLines(Logger& logger, const tchar* file, const LineFunc& lineFunc)` (scope `uba`)
- L153 _function_ `auto fg = MakeGuard([&]() { CloseFile(file, handle); });` (scope `uba::ReadLines`)

### `Source/Programs/UnrealBuildAccelerator/Common/Public/UbaFileAccessor.h` (Public)


#### class `uba::FileAccessor`  
`class FileAccessor`  
_L10-56_
- L13 _public prototype_ `FileAccessor(Logger& logger, const tchar* fileName);`
- L14 _public prototype_ `~FileAccessor();`
- L17 _public prototype_ `bool CreateWrite(bool allowRead = false, u32 flagsAndAttributes = DefaultAttributes(), u64 size = 0, const tchar* tempPath = nullptr);` — tempPath is only used by posix and will create a temp file and then move it to place when done. (Since DeleteOnClose does not exist)
- L18 _public prototype_ `bool CreateMemoryWrite(bool allowRead = false, u32 flagsAndAttributes = DefaultAttributes(), u64 size = 0, const tchar* tempPath = nullptr);`
- L19 _public prototype_ `bool Close(u64* lastWriteTime = nullptr);`
- L21 _public prototype_ `bool Write(const void* data, u64 dataLen, u64 offset = 0, bool lastWrite = false);`
- L23 _public prototype_ `bool OpenRead();`
- L24 _public prototype_ `bool OpenMemoryRead(u64 offset = 0, bool errorOnFail = true);`
- L27 _public function_ `const tchar* GetFileName()`
- L28 _public function_ `inline FileHandle GetHandle()`
- L29 _public function_ `inline u8* GetData()`
- L30 _public function_ `inline u64 GetSize()`
- L33 _public prototype_ `bool GetFileBasicInformationByHandle(FileBasicInformation& out);` — Can be called if file is opened
- L36 _private prototype_ `bool InternalCreateWrite(bool allowRead, u32 flagsAndAttributes, u64 size, const tchar* tempPath, bool isMemoryMap);`
- L37 _private prototype_ `bool InternalWrite(const void* data, u64 dataLen, u64 offset, bool lastWrite);`
- L38 _private prototype_ `bool InternalClose(bool success, u64* lastWriteTime);`
- L39 _private member_ `Logger& m_logger;`
- L40 _private member_ `const tchar* m_fileName;`
- L41 _private member_ `FileHandle m_fileHandle = InvalidFileHandle;`
- L42 _private member_ `FileMappingHandle m_mappingHandle;`
- L43 _private member_ `u64 m_size = 0;`
- L44 _private member_ `u8* m_data = nullptr;`
- L45 _private member_ `u32 m_flagsAndAttributes = 0;`
- L46 _private member_ `bool m_isWrite = false;`
- L49 _private member_ `const tchar* m_tempPath = nullptr;`
- L50 _private member_ `u32 m_tempFileIndex = 0;`
- L53 _private member_ `u32 m_writeThroughBufferSize = 0;`
- L54 _private member_ `u8* m_writeThroughBuffer = nullptr;`
- L55 _private member_ `u64 m_writeThroughBufferPos = 0;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace uba`

### `Source/Programs/UnrealBuildAccelerator/Common/Public/UbaFileMappingBuffer.h` (Public)


#### struct `uba::MappedView`  
`struct MappedView`  
_L16-22_
- L18 _public member_ `SharedMemoryHandle handle;`
- L19 _public member_ `u64 offset = 0;`
- L20 _public member_ `u64 size = 0;`
- L21 _public member_ `u8* memory = nullptr;`

#### class `uba::FileMappingBuffer`  
`class FileMappingBuffer`  
_L26-68_
- L29 _public prototype_ `FileMappingBuffer(Logger& logger, SharedMemoryAllocator& allocator);`
- L30 _public prototype_ `~FileMappingBuffer();`
- L32 _public prototype_ `bool Init(const tchar* name, u64 capacity, u64 commitStepSize);`
- L34 _public prototype_ `MappedView AllocAndMapView(u64 size, u64 alignment, const tchar* hint, bool isIndependent = false);`
- L35 _public prototype_ `MappedView MapView(SharedMemoryHandle handle, u64 offset, u64 size, const tchar* hint);`
- L36 _public prototype_ `MappedView MapView(StringView handleName, u64 size, const tchar* hint);`
- L37 _public prototype_ `void UnmapView(MappedView view, const tchar* hint, u64 newSize = InvalidValue);`
- L39 _public prototype_ `bool IsIndependent(SharedMemoryHandle handle);`
- L40 _public prototype_ `void CloseIndependent(SharedMemoryHandle handle, u64 size, const tchar* hint);`
- L42 _public prototype_ `SharedMemoryHandle GetMemoryHandle();`
- L43 _public prototype_ `u64 GetUsed();`
- L45 _public prototype_ `void TraceStatus(Trace& trace, u32 startRow, const tchar* hint, u32 traceLevel);`
- L48 _private prototype_ `MappedView InternalMapView(SharedMemoryHandle handle, u64 offset, u64 size, const tchar* hint);`
- L50 _private member_ `Logger& m_logger;`
- L51 _private member_ `SharedMemoryAllocator& m_allocator;`
- L53 _private member_ `TString m_name;`
- L54 _private member_ `u64 m_commitStepSize = 0;`
- L56 _private member_ `SharedMemoryHandle m_memoryHandle;`
- L57 _private member_ `Futex m_usedLock;`
- L58 _private member_ `u8* m_memory = nullptr;`
- L59 _private member_ `u64 m_capacity = 0;`
- L60 _private member_ `u64 m_committed = 0;`
- L61 _private member_ `u64 m_used = 0;`
- L63 _private member_ `Atomic<u64> m_independentMappingCount = 0;`
- L64 _private member_ `Atomic<u64> m_independentSize = 0;`
- L66 _private prototype_ `FileMappingBuffer(const FileMappingBuffer&) = delete;`
- L67 _private prototype_ `void operator=(const FileMappingBuffer&) = delete;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace uba`

### `Source/Programs/UnrealBuildAccelerator/Common/Public/UbaFixedSizeFileMappingAllocator.h` (Public)


#### struct `uba::FileMappingAllocation`  
`struct FileMappingAllocation`  
_L14-19_
- L16 _public member_ `FileMappingHandle handle;`
- L17 _public member_ `u64 offset = 0;`
- L18 _public member_ `u8* memory = nullptr;`

#### class `uba::FixedSizeFileMappingAllocator`  
`class FixedSizeFileMappingAllocator`  
_L23-50_
- L26 _public prototype_ `FixedSizeFileMappingAllocator(Logger& logger, const tchar* name);`
- L27 _public prototype_ `~FixedSizeFileMappingAllocator();`
- L29 _public prototype_ `bool Init(u64 blockSize, u64 capacity);`
- L31 _public prototype_ `FileMappingAllocation Alloc(const tchar* hint);`
- L32 _public prototype_ `void Free(FileMappingAllocation allocation);`
- L34 _public prototype_ `u64 GetSize();`
- L37 _private member_ `Logger& m_logger;`
- L38 _private member_ `const tchar* m_name;`
- L39 _private member_ `u64 m_capacity = 0;`
- L40 _private member_ `u64 m_blockSize = 0;`
- L42 _private member_ `Futex m_mappingLock;`
- L43 _private member_ `FileMappingHandle m_mappingHandle;`
- L44 _private member_ `u64 m_mappingCount = 0;`
- L46 _private member_ `Set<u64> m_availableBlocks;`
- L48 _private prototype_ `FixedSizeFileMappingAllocator(const FixedSizeFileMappingAllocator&) = delete;`
- L49 _private prototype_ `void operator=(const FixedSizeFileMappingAllocator&) = delete;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace uba`

### `Source/Programs/UnrealBuildAccelerator/Common/Public/UbaHashMap.h` (Public)


#### struct `uba::HashMap`  
`template<typename Key, typename Value, bool AllowGrow = false> struct HashMap`  
_L16-241_
- L24 _public function_ `~HashMap()`
- L30 _public function_ `void Init(MemoryBlock& mem, u64 reserveCount, const tchar* hint = TC(""))`
- L38 _public function_ `void Init(u64 reserveCount = 4, const tchar* hint = TC(""))`
- L53 _public function_ `bool IsInitialized()`
- L58 _public function_ `Value& Insert(const Key& key)`
- L64 _public function_ `Value& Insert(const Key& key, bool& outAdded)`
- L70 _public function_ `u32 InsertIndex(const Key& key, bool& outAdded)`
- L121 _public function_ `Value* Find(const Key& key) const`
- L139 _public function_ `const Key* GetKey(Value* value)`
- L148 _public function_ `Value& GetValueFromIndex(u32 index)`
- L153 _public function_ `u32 Size()`
- L158 _public function_ `void Erase(const Key& key)`
- L194 _public function_ `Value* ValuesBegin() const`
- L195 _public function_ `Value* ValuesEnd() const`
- L197 _public function_ `void Swap(HashMap& o)`
- L205 _public function_ `u64 GetMemoryNeeded(u64 reserveCount)`
- L213 _private function_ `void InternalInit(u64 reserveCount, u64 lookupCount, const tchar* hint)`
- L224 _private function_ `u64 GetNextReserveCount(u64 reserveCount)`
- L231 _private member_ `MemoryBlock* m_memory = nullptr;`
- L233 _private member_ `Entry* m_entries = nullptr;`
- L234 _private member_ `Value* m_values = nullptr;`
- L235 _private member_ `u32* m_lookup = nullptr;`
- L237 _private member_ `u32 m_mask = 0;`
- L238 _private member_ `u32 m_nextAvailableEntry = 0;`
- L239 _private member_ `u32 m_reserveCount = 0;`
- L240 _private member_ `bool m_ownsMemory = false;`

#### struct `uba::HashMap::Entry`  
`struct Entry`  
_L18-22_
- L20 _public member_ `Key key;`
- L21 _public member_ `u32 next;` — If this is 0 it means that it is unused, ~0u means it is the end of a chain, otherwise offset into entry array

#### struct `uba::HashMap2`  
`template<typename Key, typename Value> struct HashMap2`  
_L248-333_
- L257 _public function_ `void Init(MemoryBlock& memory, u64 maxSize, const tchar* hint = TC(""))`
- L269 _public function_ `Value& Insert(const Key& key)`
- L306 _public function_ `Value* Find(const Key& key) const`
- L324 _public function_ `u32 Size()`
- L329 _public member_ `Entry* entries;`
- L330 _public member_ `u32* lookup;`
- L331 _public member_ `u32 mask;`
- L332 _public member_ `u32 nextAvailableEntry;`

#### struct `uba::HashMap2::Entry`  
`struct Entry`  
_L250-255_
- L252 _public member_ `Key key;`
- L253 _public member_ `Value value;`
- L254 _public member_ `u32 next;` — If this is 0 it means that it is unused, ~0u means it is the end of a chain, otherwise offset into entry array

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace uba`

### `Source/Programs/UnrealBuildAccelerator/Common/Public/UbaLinuxNetworkWrappers.h` (Public)


#### Free symbols / members of external scopes

- L10 _function_ `bool CatFile(char* outBuffer, int bufferCapacity, const char* path)`
- L22 _function_ `bool UnixGetTcpAutoTuning(int* outReadMin, int* outReadDefault, int* outReadMax, int* outWriteMin, int* outWriteDefault, int* outWriteMax)`

### `Source/Programs/UnrealBuildAccelerator/Common/Public/UbaLogWriter.h` (Public)


#### enum `uba::LogEntryType`  
`enum LogEntryType : u8`  
_L9-16_
- L11 _public enumerator_ `LogEntryType_Error = 0`
- L12 _public enumerator_ `LogEntryType_Warning = 1`
- L13 _public enumerator_ `LogEntryType_Info = 2`
- L14 _public enumerator_ `LogEntryType_Detail = 3`
- L15 _public enumerator_ `LogEntryType_Debug = 4`

#### class `uba::LogWriter`  
`class LogWriter`  
_L18-25_
- L21 _public prototype_ `virtual ~LogWriter() = default;`
- L22 _public prototype_ `virtual void BeginScope() = 0;`
- L23 _public prototype_ `virtual void EndScope() = 0;`
- L24 _public prototype_ `virtual void Log(LogEntryType type, const tchar* str, u32 strLen, const tchar* prefix = nullptr, u32 prefixLen = 0) = 0;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace uba`
- L27 _externvar_ `extern LogWriter& g_consoleLogWriter;` (scope `uba`)
- L28 _externvar_ `extern LogWriter& g_nullLogWriter;` (scope `uba`)

### `Source/Programs/UnrealBuildAccelerator/Common/Public/UbaLogger.h` (Public)


#### struct `uba::LogEntry`  
`struct LogEntry`  
_L25-29_
- L27 _public member_ `LogEntryType type;`
- L28 _public member_ `const tchar* string;`

#### class `uba::Logger`  
`class Logger`  
_L33-52_
- L36 _public function_ `Logger()`
- L37 _public prototype_ `bool Error(const tchar* format, ...);`
- L38 _public prototype_ `bool Warning(const tchar* format, ...);`
- L39 _public prototype_ `Logger& Info(const tchar* format, ...);`
- L40 _public prototype_ `Logger& Detail(const tchar* format, ...);`
- L41 _public prototype_ `Logger& Debug(const tchar* format, ...);`
- L42 _public prototype_ `Logger& Logf(LogEntryType type, const tchar* format, ...);`
- L43 _public prototype_ `void LogArg(LogEntryType type, const tchar* format, va_list& args);`
- L44 _public prototype_ `void Log(LogEntryType type, const StringView& str);`
- L46 _public prototype_ `virtual void BeginScope() = 0;`
- L47 _public prototype_ `virtual void EndScope() = 0;`
- L48 _public prototype_ `virtual void Log(LogEntryType type, const tchar* str, u32 strLen) = 0;`
- L49 _public function_ `virtual ~Logger()`
- L51 _public function_ `bool ToFalse()`

#### class `uba::LoggerWithWriter`  
`class LoggerWithWriter : public Logger`  
_L56-68_
- inherits: `Logger`
- L59 _public prototype_ `LoggerWithWriter(LogWriter& writer, const tchar* prefix = nullptr);`
- L60 _public function_ `virtual void BeginScope()`
- L61 _public function_ `virtual void EndScope()`
- L62 _public function_ `virtual void Log(LogEntryType type, const tchar* str, u32 strLen)`
- L65 _public member_ `LogWriter& m_writer;`
- L66 _public member_ `const tchar* m_prefix;`
- L67 _public member_ `u32 m_prefixLen;`

#### struct `uba::MutableLogger`  
`struct MutableLogger : public LoggerWithWriter`  
_L72-78_
- inherits: `LoggerWithWriter`
- L74 _public function_ `MutableLogger(LogWriter& writer, const tchar* prefix) : LoggerWithWriter(writer, prefix)`
- L75 _public function_ `virtual void Log(LogEntryType type, const tchar* str, u32 strLen) override`
- L77 _public member_ `Atomic<u32> isMuted = false;`

#### class `uba::FilteredLogWriter`  
`class FilteredLogWriter : public LogWriter`  
_L82-92_
- inherits: `LogWriter`
- L85 _public function_ `FilteredLogWriter(LogWriter& writer, LogEntryType level = LogEntryType_Detail) : m_writer(writer), m_level(level)`
- L86 _public function_ `virtual void BeginScope() override`
- L87 _public function_ `virtual void EndScope() override`
- L88 _public prototype_ `virtual void Log(LogEntryType type, const tchar* str, u32 strLen, const tchar* prefix = nullptr, u32 prefixLen = 0) override;`
- L90 _private member_ `LogWriter& m_writer;`
- L91 _private member_ `LogEntryType m_level;`

#### struct `uba::BytesToText`  
`struct BytesToText`  
_L96-102_
- L98 _public prototype_ `BytesToText(u64 bytes, bool base2 = false);`
- L99 _public function_ `operator const tchar* () const`
- L100 _public prototype_ `operator StringView () const;`
- L101 _public member_ `tchar str[32];`

#### struct `uba::CountToText`  
`struct CountToText`  
_L106-112_
- L108 _public prototype_ `CountToText(u64 count);`
- L109 _public function_ `operator const tchar* () const`
- L110 _public prototype_ `operator StringView () const;`
- L111 _public member_ `tchar str[32];`

#### struct `uba::TimeToText`  
`struct TimeToText`  
_L116-124_
- L118 _public prototype_ `TimeToText(float seconds, bool allowMinutes = false);`
- L119 _public prototype_ `TimeToText(u64 time, bool allowMinutes = false);`
- L120 _public prototype_ `TimeToText(u64 time, bool allowMinutes, u64 frequency);`
- L121 _public function_ `operator const tchar*() const`
- L122 _public prototype_ `operator StringView () const;`
- L123 _public member_ `tchar str[32];`

#### struct `uba::DateToText`  
`struct DateToText`  
_L126-131_
- L128 _public prototype_ `DateToText(float seconds);`
- L129 _public prototype_ `DateToText(u64 fileTime);`
- L130 _public member_ `tchar str[128];`

#### struct `uba::CallstackInfo`  
`struct CallstackInfo`  
_L143-143_
- L143 _public member_ `struct CallstackInfo { Vector<u8> data; Vector<u32> threadIds; TString desc; };`
- L143 _public member_ `struct CallstackInfo { Vector<u8> data; Vector<u32> threadIds; TString desc; };`
- L143 _public member_ `struct CallstackInfo { Vector<u8> data; Vector<u32> threadIds; TString desc; };`

#### struct `uba::LogStallScope`  
`struct LogStallScope`  
_L149-159_
- L151 _public prototype_ `LogStallScope(Logger& logger, LogEntryType type, u64 timeSeconds, const tchar* messageFormat);`
- L152 _public prototype_ `~LogStallScope();`
- L153 _public prototype_ `void Leave();`
- L154 _public member_ `Logger& logger;`
- L155 _public member_ `LogEntryType type;`
- L156 _public member_ `u64 timeSeconds;`
- L157 _public member_ `u64 timeStart;`
- L158 _public member_ `const tchar* messageFormat;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UBA_DEBUG_LOGGER 0`
- L12 _macro_ `#define UBA_LOG_STALLS 0`
- L14 _namespace_ `namespace uba`
- L21 _typedef_ `using TraverseThreadErrorFunc = Function<void(const StringView& error)>;` (scope `uba`)
- L136 _prototype_ `Logger* StartDebugLogger(Logger& outerLogger, const tchar* fileName);` (scope `uba`)
- L137 _prototype_ `Logger* StopDebugLogger(Logger* logger);` (scope `uba`)
- L140 _prototype_ `void ParseCallstackInfo(StringBufferBase& out, BinaryReader& reader, const tchar* executable, const StringView* searchPaths, bool writeHeader = true);` (scope `uba`)
- L141 _prototype_ `void PrintContentionSummary(class Logger& logger);` (scope `uba`)
- L144 _prototype_ `void TraverseAllCallstacks(const Function<void(const CallstackInfo&)>& func, const TraverseThreadErrorFunc& errorFunc);` (scope `uba`)
- L145 _prototype_ `void PrintAllCallstacks(Logger& logger);` (scope `uba`)
- L161 _macro_ `#define LOG_STALL_SCOPE(logger, timeSeconds, messageFormat) LogStallScope lss(logger, LogEntryType_Error, timeSeconds, messageFormat);`
- L163 _macro_ `#define LOG_STALL_SCOPE(logger, timeSeconds, messageFormat)`
- L166 _prototype_ `void LogToConsoleNoLineFeed(LogEntryType type, const tchar* str, u32 strLen);` (scope `uba`)
- L167 _prototype_ `u64 GetConsoleLogLineCount();` (scope `uba`) — monotonic count of complete (newline-terminated) lines written to g_consoleLogWriter

### `Source/Programs/UnrealBuildAccelerator/Common/Public/UbaMap.h` (Public)


#### class `uba::StdAllocator`  
`template<typename Type> class StdAllocator`  
_L13-29_
- L16 _public typedef_ `using value_type = Type;`
- L18 _public function_ `StdAllocator()`
- L19 _public function_ `StdAllocator(const StdAllocator& o)`
- L20 _public function_ `StdAllocator(StdAllocator&& o) noexcept`
- L21 _public function_ `constexpr bool operator==(const StdAllocator&) const noexcept`
- L23 _public function_ `template <class _Other> constexpr StdAllocator(const StdAllocator<_Other>&) noexcept`
- L25 _public function_ `value_type* allocate(u64 n)`
- L26 _public function_ `void deallocate(value_type* p, u64 n)`
- L27 _public function_ `bool try_grow_in_place(value_type* p, u64 , u64 newCount)`
- L28 _public function_ `u64 max_size() const`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace uba`
- L36 _typedef_ `template<typename Key, typename Value, typename Less = std::less<>> using Map = std::map<Key, Value, Less, StdAllocator<std::pair<const Key, Value>>>;` (scope `uba`)
- L39 _typedef_ `template<typename Key, typename Less = std::less<>> using Set = std::set<Key, Less, StdAllocator<Key>>;` (scope `uba`)

### `Source/Programs/UnrealBuildAccelerator/Common/Public/UbaNetwork.h` (Public)


#### enum `uba::SystemMessageType`  
`enum SystemMessageType : u8`  
_L102-107_
- L105 _public enumerator_ `UBA_SYSTEM_MESSAGES #undef UBA_SYSTEM_MESSAGE`

#### enum `uba::StorageMessageType`  
`enum StorageMessageType : u8`  
_L109-114_
- L112 _public enumerator_ `UBA_STORAGE_MESSAGES #undef UBA_STORAGE_MESSAGE`

#### enum `uba::SessionMessageType`  
`enum SessionMessageType : u8`  
_L116-121_
- L119 _public enumerator_ `UBA_SESSION_MESSAGES #undef UBA_SESSION_MESSAGE`

#### enum `uba::CacheMessageType`  
`enum CacheMessageType : u8`  
_L123-128_
- L126 _public enumerator_ `UBA_CACHE_MESSAGES #undef UBA_CACHE_MESSAGE`

#### enum `uba::SessionProcessAvailableResponse`  
`enum SessionProcessAvailableResponse : u32`  
_L150-155_
- desc: Response types for SessionMessageType_ProcessAvailable
- L152 _public enumerator_ `SessionProcessAvailableResponse_None = 0`
- L153 _public enumerator_ `SessionProcessAvailableResponse_Disconnect = ~u32(0)`
- L154 _public enumerator_ `SessionProcessAvailableResponse_RemoteExecutionDisabled = ~u32(0) - 1`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace uba`
- L10 _variable_ `static constexpr u32 SendMaxSize = 256*1024;` (scope `uba`)
- L12 _variable_ `static constexpr u8 SystemServiceId = 0;` (scope `uba`)
- L13 _variable_ `static constexpr u8 StorageServiceId = 1;` (scope `uba`)
- L14 _variable_ `static constexpr u8 SessionServiceId = 2;` (scope `uba`)
- L15 _variable_ `static constexpr u8 CacheServiceId = 3;` (scope `uba`)
- L17 _variable_ `static constexpr u32 SystemNetworkVersion = 1339;` (scope `uba`)
- L18 _variable_ `static constexpr u32 SystemNetworkVersionMin = 1339;` (scope `uba`)
- L19 _variable_ `static constexpr u32 SystemNetworkVersionRoute = 1340;` (scope `uba`)
- L20 _variable_ `static constexpr u32 StorageNetworkVersion = 4;` (scope `uba`)
- L21 _variable_ `static constexpr u32 SessionNetworkVersion = 55;` (scope `uba`)
- L22 _variable_ `static constexpr u32 CacheNetworkVersion = 5;` (scope `uba`)
- L23 _variable_ `static constexpr u32 CacheBucketVersion = 3;` (scope `uba`)
- L25 _macro_ `#define UBA_TRACK_NETWORK_TIMES 1 // Enable to track times on messages, connections etc`
- L29 _macro_ `#define UBA_SYSTEM_MESSAGES \`
- L35 _macro_ `#define UBA_STORAGE_MESSAGES \`
- L49 _macro_ `#define UBA_SESSION_MESSAGES \`
- L87 _macro_ `#define UBA_CACHE_MESSAGES \`
- L104 _macro_ `#define UBA_SYSTEM_MESSAGE(x) SystemMessageType_##x,`
- L111 _macro_ `#define UBA_STORAGE_MESSAGE(x) StorageMessageType_##x,`
- L118 _macro_ `#define UBA_SESSION_MESSAGE(x) SessionMessageType_##x,`
- L125 _macro_ `#define UBA_CACHE_MESSAGE(x) CacheMessageType_##x,`
- L130 _prototype_ `StringView ToString(SystemMessageType type);` (scope `uba`)
- L131 _prototype_ `StringView ToString(StorageMessageType type);` (scope `uba`)
- L132 _prototype_ `StringView ToString(SessionMessageType type);` (scope `uba`)
- L133 _prototype_ `StringView ToString(CacheMessageType type);` (scope `uba`)
- L134 _prototype_ `StringView MessageToString(u8 serviceId, u8 messageType);` (scope `uba`)
- L136 _variable_ `constexpr u32 MessageErrorSize = 0xffffff;` (scope `uba`)
- L137 _variable_ `constexpr u32 MessageKeepAliveSize = 0xffffff - 1;` (scope `uba`)
- L139 _variable_ `constexpr u16 FetchCasIdDone = u16(~0);` (scope `uba`)
- L140 _variable_ `constexpr u16 FetchCasIdDisallowed = u16(~0) - 1;` (scope `uba`)
- L142 _variable_ `constexpr bool DownloadDebugSymbols = false;` (scope `uba`)
- L144 _variable_ `static constexpr u32 KeepAliveIdleSeconds = 60;` (scope `uba`)
- L145 _variable_ `static constexpr u32 KeepAliveIntervalSeconds = 1;` (scope `uba`)
- L146 _variable_ `static constexpr u32 KeepAliveProbeCount = 10;` (scope `uba`)
- L147 _variable_ `static constexpr u32 UserTimeoutSeconds = 60;` (scope `uba`)
- L157 _variable_ `inline constexpr const char EncryptionHandshakeString[] = "Th` (scope `uba`)

### `Source/Programs/UnrealBuildAccelerator/Common/Public/UbaNetworkBackend.h` (Public)


#### class `uba::NetworkBackend`  
`class NetworkBackend`  
_L23-88_
- L26 _public function_ `virtual ~NetworkBackend()`
- L30 _public prototype_ `virtual void Shutdown(void* connection) = 0;` — Shutdown the connection (stops/finishes traffic) External code should wait for disconnect callback before assuming that no more recv callbacks can happen
- L40 _public prototype_ `virtual bool Send(Logger& logger, void* connection, const void* data, u32 dataSize, SendContext& sendContext, const tchar* sendHint) = 0;` — Send data to connection. If sendContext is set it means that backend expects sendContext to stay around in memory until send is done (or rather, response is received)
- L44 _public typedef_ `using RecvHeaderCallback = bool(void* context, const Guid& connectionUid, u8* headerData, void*& outBodyContext, u8*& outBodyData, u32& outBodySize);` — Recv data from connection. This is callback based so header callback is called first after headerSize bytes have been read If header callback sets a value in outBodySize, body callback will be called once body size bytes are received.
- L45 _public typedef_ `using RecvBodyCallback = bool(void* context, bool recvError, u8* headerData, void* bodyContext, u8* bodyData, u32 bodySize);`
- L46 _public prototype_ `virtual void SetRecvCallbacks(void* connection, void* context, u32 headerSize, RecvHeaderCallback* h, RecvBodyCallback* b, const tchar* recvHint) = 0;`
- L48 _public typedef_ `using RecvTimeoutCallback = bool(void* context, u32 timeoutMs, const tchar* recvHint, const tchar* hint);`
- L49 _public prototype_ `virtual void SetRecvTimeout(void* connection, u32 timeoutMs, void* context, RecvTimeoutCallback* callback) = 0;`
- L52 _public typedef_ `using DataSentCallback = void(void* context, u32 bytes);` — Callbacks to be able to track stats
- L53 _public typedef_ `using DataReceivedCallback = void(void* context, u32 bytes);`
- L54 _public function_ `virtual void SetDataSentCallback(void* connection, void* context, DataSentCallback* callback)`
- L55 _public function_ `virtual void SetDataReceivedCallback(void* connection, void* context, DataReceivedCallback* callback)`
- L56 _public function_ `virtual void TraverseConnections(const Function<void(void*)>& func)`
- L59 _public prototype_ `virtual void SetThreadedSend(void* connection) = 0;` — Change so send is handled in a separate thread instead of directly on calling thread
- L62 _public typedef_ `using DisconnectCallback = void(void* context, const Guid& connectionUid, void* connection);` — Disconnect callback. This is called as soon as connection is interrupted from send, recv or shutdown.
- L63 _public prototype_ `virtual void SetDisconnectCallback(void* connection, void* context, DisconnectCallback* callback) = 0;`
- L64 _public prototype_ `virtual void SetAllowLessThanBodySize(void* connection, bool allow) = 0;`
- L67 _public prototype_ `virtual void SetPriority(void* connection) = 0;` — Set priority of connection
- L70 _public typedef_ `using ListenConnectedFunc = Function<bool(void* connection, const sockaddr& remoteSocketAddr)>;` — Start listen on port/ip.
- L71 _public prototype_ `virtual bool StartListen(Logger& logger, u16 port, const tchar* ip, const ListenConnectedFunc& connectedFunc, bool linger = false) = 0;`
- L72 _public prototype_ `virtual void StopListen() = 0;`
- L75 _public typedef_ `using ConnectedFunc = Function<bool(void* connection, const sockaddr& remoteSocketAddr, bool* timedOut)>;` — Connect to remote ip/port
- L76 _public prototype_ `virtual bool Connect(Logger& logger, const tchar* ip, const ConnectedFunc& connectedFunc, u16 port = DefaultPort, bool* timedOut = nullptr) = 0;`
- L77 _public prototype_ `virtual bool Connect(Logger& logger, const sockaddr& remoteSocketAddr, const ConnectedFunc& connectedFunc, bool* timedOut = nullptr, const tchar* nameHint = nullptr) = 0;`
- L80 _public prototype_ `virtual void DeleteConnection(void* connection) = 0;` — Remove connection (user guarantee connection is not referenced anywhere)
- L83 _public prototype_ `virtual void SetSendBufferSize(void* connection, u32 bytes) = 0;` — Set internal buffer sizes for send and recv
- L84 _public prototype_ `virtual void SetRecvBufferSize(void* connection, u32 bytes) = 0;`
- L86 _public prototype_ `virtual void GetTotalSendAndRecv(u64& outSend, u64& outRecv) = 0;`
- L87 _public prototype_ `virtual void Validate(Logger& logger, const Vector<void*>& connections, bool full) = 0;`

#### enum `uba::NetworkBackend::(anonymous)`  
``  
_L33-36_

#### struct `uba::NetworkBackend::SendContext`  
`struct NetworkBackend::SendContext`  
_L90-100_
- L92 _public member_ `u64 data[2];`
- L93 _public member_ `u32 size = 0;`
- L94 _public member_ `u8 flags;`
- L95 _public member_ `bool isUsed = false;`
- L96 _public member_ `bool isFinished = false;`
- L98 _public function_ `SendContext(u8 sendFlags = 0) : flags(sendFlags)`
- L99 _public function_ `~SendContext()` — UBA_ASSERT(isFinished); }

#### class `uba::HttpConnection`  
`class HttpConnection`  
_L102-118_
- L105 _public prototype_ `HttpConnection();`
- L106 _public prototype_ `~HttpConnection();`
- L107 _public prototype_ `bool Query(Logger& logger, const char* type, StringBufferBase& outResponse, u32& outStatusCode, const char* host, const char* path, const char* header = "", u32 timeoutMs = 3000);`
- L109 _public prototype_ `void SetConnectTimeout(u32 timeOutMs);`
- L112 _private prototype_ `bool Connect(Logger& logger, const char* host);`
- L114 _private member_ `char m_host[256];`
- L115 _private member_ `u64 m_socket;`
- L116 _private member_ `bool m_wsaInitDone = false;`
- L117 _private member_ `u32 m_connectTimeOutMs = 0;`

#### Free symbols / members of external scopes

- L10 _typedef_ `typedef struct sockaddr SOCKADDR;`
- L15 _namespace_ `namespace uba`
- L20 _prototype_ `void TraverseNetworkAddresses(Logger& logger, const Function<bool(const StringBufferBase& addr)>& func);` (scope `uba`)
- L21 _prototype_ `bool TraverseRemoteAddresses(Logger& logger, const tchar* addr, u16 port, const Function<bool(const sockaddr& remoteSockaddr)>& func);` (scope `uba`)
- L34 _enumerator_ `SendFlags_Async = 1 << 0` (scope `uba::NetworkBackend::__anon066bb4610103`) — Data is sent async and call is returned before data has been transmitted. (can be used inside recv callbacks). Will make copy of data
- L35 _enumerator_ `SendFlags_ExternalWait = 1 << 1` (scope `uba::NetworkBackend::__anon066bb4610103`) — Same as async but will not do any copies of context or data. Assumes something outside is handling the waiting

### `Source/Programs/UnrealBuildAccelerator/Common/Public/UbaNetworkBackendMemory.h` (Public)


#### class `uba::NetworkBackendMemory`  
`class NetworkBackendMemory final : public NetworkBackend`  
_L11-45_
- inherits: `NetworkBackend`
- L14 _public prototype_ `NetworkBackendMemory(LogWriter& writer, const tchar* prefix = TC("Netw`
- L15 _public prototype_ `virtual ~NetworkBackendMemory();`
- L16 _public prototype_ `virtual void Shutdown(void* connection) override;`
- L17 _public prototype_ `virtual bool Send(Logger& logger, void* connection, const void* data, u32 dataSize, SendContext& sendContext, const tchar* sendHint) override;`
- L18 _public prototype_ `virtual void SetDataSentCallback(void* connection, void* context, DataSentCallback* callback) override;`
- L19 _public prototype_ `virtual void SetDataReceivedCallback(void* connection, void* context, DataReceivedCallback* callback) override;`
- L20 _public prototype_ `virtual void SetRecvCallbacks(void* connection, void* context, u32 headerSize, RecvHeaderCallback* h, RecvBodyCallback* b, const tchar* recvHint) override;`
- L21 _public prototype_ `virtual void SetRecvTimeout(void* connection, u32 timeoutMs, void* context, RecvTimeoutCallback* callback) override;`
- L22 _public prototype_ `virtual void SetThreadedSend(void* connection) override;`
- L23 _public prototype_ `virtual void SetDisconnectCallback(void* connection, void* context, DisconnectCallback* callback) override;`
- L24 _public prototype_ `virtual void SetAllowLessThanBodySize(void* connection, bool allow) override;`
- L25 _public prototype_ `virtual void SetPriority(void* connection) override;`
- L27 _public prototype_ `virtual bool StartListen(Logger& logger, u16 port, const tchar* ip, const ListenConnectedFunc& connectedFunc, bool linger = false) override;`
- L28 _public prototype_ `virtual void StopListen() override;`
- L29 _public prototype_ `virtual bool Connect(Logger& logger, const tchar* ip, const ConnectedFunc& connectedFunc, u16 port = DefaultPort, bool* timedOut = nullptr) override;`
- L30 _public prototype_ `virtual bool Connect(Logger& logger, const sockaddr& remoteSocketAddr, const ConnectedFunc& connectedFunc, bool* timedOut = nullptr, const tchar* nameHint = nullptr) override;`
- L31 _public prototype_ `virtual void DeleteConnection(void* connection) override;`
- L33 _public prototype_ `virtual void SetSendBufferSize(void* connection, u32 bytes) override;`
- L34 _public prototype_ `virtual void SetRecvBufferSize(void* connection, u32 bytes) override;`
- L36 _public prototype_ `virtual void GetTotalSendAndRecv(u64& outSend, u64& outRecv) override;`
- L37 _public prototype_ `virtual void Validate(Logger& logger, const Vector<void*>& connections, bool full) override;`
- L41 _private member_ `Connection* m_connection = nullptr;`
- L43 _private member_ `ReaderWriterLock m_connectedFuncLock;`
- L44 _private member_ `ListenConnectedFunc m_connectedFunc;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace uba`

### `Source/Programs/UnrealBuildAccelerator/Common/Public/UbaNetworkBackendQuic.h` (Public)


#### struct `uba::NetworkBackendQuic`  
`struct NetworkBackendQuic : public NetworkBackend`  
_L26-109_
- inherits: `NetworkBackend`
- L29 _public prototype_ `NetworkBackendQuic(LogWriter& writer, const wchar_t* prefix = L"Net`
- L30 _public prototype_ `bool Init(const char* app);`
- L31 _public prototype_ `virtual ~NetworkBackendQuic();`
- L32 _public prototype_ `virtual void Shutdown(void* connection) override;`
- L33 _public prototype_ `virtual void Close(void* connection) override;`
- L34 _public prototype_ `virtual bool Send(Logger& logger, void* connection, const void* data, u32 dataSize, SendContext& sendContext, const tchar* sendHint) override;`
- L35 _public prototype_ `virtual void SetDataSentCallback(void* connection, void* context, DataSentCallback* callback) override;`
- L36 _public prototype_ `virtual void SetRecvCallbacks(void* connection, void* context, u32 headerSize, RecvHeaderCallback* h, RecvBodyCallback* b, const wchar_t* recvHint) override;`
- L37 _public prototype_ `virtual void SetRecvTimeout(void* connection, u32 timeoutMs) override;`
- L38 _public prototype_ `virtual void SetThreadedSend(void* connection) override;`
- L39 _public prototype_ `virtual void SetDisconnectCallback(void* connection, void* context, DisconnectCallback* callback) override;`
- L41 _public prototype_ `virtual bool StartListen(Logger& logger, u16 port, const wchar_t* ip, const ListenConnectedFunc& connectedFunc, bool linger = false) override;`
- L42 _public prototype_ `virtual void StopListen() override;`
- L44 _public prototype_ `virtual bool Connect(Logger& logger, const wchar_t* ip, const ConnectedFunc& connectedFunc, u16 port = DefaultPort, bool* timedOut = nullptr) override;`
- L45 _public prototype_ `virtual bool Connect(Logger& logger, const sockaddr& remoteSocketAddr, const ConnectedFunc& connectedFunc, bool* timedOut = nullptr, const wchar_t* nameHint = nullptr) override;`
- L49 _private prototype_ `QUIC_STATUS StreamCallback(Connection& connection, HQUIC streamHandle, QUIC_STREAM_EVENT* Event);`
- L51 _private member_ `LoggerWithWriter m_logger;`
- L52 _private member_ `const QUIC_API_TABLE* m_msQuic = nullptr;`
- L53 _private member_ `HQUIC m_registration = NULL;`
- L54 _private member_ `HQUIC m_configuration = NULL;`
- L94 _private member_ `ReaderWriterLock m_connectionsLock;`
- L95 _private member_ `UnorderedMap<HQUIC, Connection*> m_connections;`
- L97 _private prototype_ `QUIC_STATUS ConnectionCallback(HQUIC Connection, QUIC_CONNECTION_EVENT* Event);`
- L98 _private prototype_ `QUIC_STATUS ListenerCallback(HQUIC Listener, QUIC_LISTENER_EVENT* Event);`
- L99 _private prototype_ `QUIC_STATUS ListenerConnectionCallback(HQUIC Connection, QUIC_CONNECTION_EVENT* Event);`
- L100 _private prototype_ `void StreamCreated(HQUIC conn, HQUIC stream);`
- L101 _private prototype_ `void StreamShutdown(Connection& conn, HQUIC streamHandle);`
- L102 _private prototype_ `void CloseConnection(HQUIC connection);`
- L103 _private prototype_ `void CloseConnection(Connection& connection);`
- L104 _private prototype_ `void InitNetworkSettings(QUIC_SETTINGS& Settings, bool isClient);`
- L105 _private prototype_ `bool LoadCredentials(bool isClient);`
- L107 _private member_ `HQUIC m_listener = NULL;`
- L108 _private member_ `ListenConnectedFunc m_listenConnectedFunc;`

#### struct `uba::NetworkBackendQuic::Stream`  
`struct Stream`  
_L56-67_
- L58 _public member_ `HQUIC handle;`
- L60 _public member_ `u8 headerData[16];`
- L61 _public member_ `u8 headerRead = 0;`
- L63 _public member_ `void* bodyContext = nullptr;`
- L64 _public member_ `u8* bodyData = nullptr;`
- L65 _public member_ `u32 bodySize = 0;`
- L66 _public member_ `u32 bodyRead = 0;`

#### struct `uba::NetworkBackendQuic::Connection`  
`struct Connection`  
_L69-93_
- L71 _public prototype_ `Connection(NetworkBackendQuic& b, HQUIC ch);`
- L72 _public prototype_ `void AddRef();`
- L73 _public prototype_ `void Release();`
- L75 _public member_ `NetworkBackendQuic& backend;`
- L76 _public member_ `HQUIC connectionHandle;`
- L77 _public member_ `AtomicU64 refCount;`
- L78 _public member_ `UnorderedMap<HQUIC, Stream> recvStreams;`
- L79 _public member_ `Event ready;`
- L80 _public member_ `AtomicU64 streamHandleIt;`
- L81 _public member_ `bool connected = false;`
- L83 _public member_ `void* disconnectContext = nullptr;`
- L84 _public member_ `DisconnectCallback* disconnectCallback = nullptr;`
- L86 _public member_ `DataSentCallback* dataSentCallback = nullptr;`
- L88 _public member_ `RecvHeaderCallback* headerCallback = nullptr;`
- L89 _public member_ `RecvBodyCallback* bodyCallback = nullptr;`
- L90 _public member_ `void* context = nullptr;`
- L91 _public member_ `u32 headerSize = 0;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UBA_USE_QUIC 0`
- L15 _typedef_ `typedef struct QUIC_API_TABLE QUIC_API_TABLE;`
- L16 _typedef_ `typedef struct QUIC_HANDLE QUIC_HANDLE;`
- L17 _typedef_ `typedef struct QUIC_HANDLE* HQUIC;`
- L18 _typedef_ `typedef struct QUIC_CONNECTION_EVENT QUIC_CONNECTION_EVENT;`
- L19 _typedef_ `typedef struct QUIC_STREAM_EVENT QUIC_STREAM_EVENT;`
- L20 _typedef_ `typedef struct QUIC_LISTENER_EVENT QUIC_LISTENER_EVENT;`
- L21 _typedef_ `typedef struct QUIC_SETTINGS QUIC_SETTINGS;`
- L22 _macro_ `#define QUIC_STATUS long`
- L24 _namespace_ `namespace uba`

### `Source/Programs/UnrealBuildAccelerator/Common/Public/UbaNetworkBackendTcp.h` (Public)


#### struct `uba::NetworkBackendTcpCreateInfo`  
`struct NetworkBackendTcpCreateInfo`  
_L16-29_
- L18 _public function_ `NetworkBackendTcpCreateInfo(LogWriter& w = g_consoleLogWriter) : logWriter(w)`
- L19 _public member_ `LogWriter& logWriter;`
- L20 _public member_ `u32 statusUpdateSeconds = 0;` — Zero means never
- L21 _public member_ `bool disableNagle = true;`
- L22 _public member_ `bool useOverlappedSend = true;`
- L23 _public member_ `u32 iocpWorkerCount = 0;` — Iocp is turned off by default
- L25 _public member_ `u32 recvBufferSize = 0;` — 0 means default
- L26 _public member_ `u32 sendBufferSize = 0;` — 0 means default
- L28 _public prototype_ `void Apply(const Config& config, const tchar* tableName = TC("Netw`

#### class `uba::NetworkBackendTcp`  
`class NetworkBackendTcp final : public NetworkBackend`  
_L33-113_
- inherits: `NetworkBackend`
- L36 _public prototype_ `NetworkBackendTcp(const NetworkBackendTcpCreateInfo& info, const tchar* prefix = TC("Netw`
- L37 _public prototype_ `virtual ~NetworkBackendTcp();`
- L38 _public prototype_ `virtual void Shutdown(void* connection) override;`
- L39 _public prototype_ `virtual bool Send(Logger& logger, void* connection, const void* data, u32 dataSize, SendContext& sendContext, const tchar* sendHint) override;`
- L40 _public prototype_ `virtual void SetRecvCallbacks(void* connection, void* context, u32 headerSize, RecvHeaderCallback* h, RecvBodyCallback* b, const tchar* recvHint) override;`
- L41 _public prototype_ `virtual void SetRecvTimeout(void* connection, u32 timeoutMs, void* context, RecvTimeoutCallback* callback) override;`
- L42 _public prototype_ `virtual void SetThreadedSend(void* connection) override;`
- L43 _public prototype_ `virtual void SetDisconnectCallback(void* connection, void* context, DisconnectCallback* callback) override;`
- L44 _public prototype_ `virtual void SetAllowLessThanBodySize(void* connection, bool allow) override;`
- L45 _public prototype_ `virtual void SetPriority(void* connection) override;`
- L47 _public prototype_ `virtual bool StartListen(Logger& logger, u16 port, const tchar* ip, const ListenConnectedFunc& connectedFunc, bool linger = false) override;`
- L48 _public prototype_ `virtual void StopListen() override;`
- L49 _public prototype_ `virtual bool Connect(Logger& logger, const tchar* ip, const ConnectedFunc& connectedFunc, u16 port = DefaultPort, bool* timedOut = nullptr) override;`
- L50 _public prototype_ `virtual bool Connect(Logger& logger, const sockaddr& remoteSocketAddr, const ConnectedFunc& connectedFunc, bool* timedOut = nullptr, const tchar* nameHint = nullptr) override;`
- L51 _public prototype_ `virtual void DeleteConnection(void* connection) override;`
- L53 _public prototype_ `virtual void SetDataSentCallback(void* connection, void* context, DataSentCallback* callback) override;`
- L54 _public prototype_ `virtual void SetDataReceivedCallback(void* connection, void* context, DataReceivedCallback* callback) override;`
- L55 _public prototype_ `virtual void TraverseConnections(const Function<void(void*)>& func) override;`
- L57 _public prototype_ `virtual void SetSendBufferSize(void* connection, u32 bytes) override;`
- L58 _public prototype_ `virtual void SetRecvBufferSize(void* connection, u32 bytes) override;`
- L60 _public prototype_ `virtual void GetTotalSendAndRecv(u64& outSend, u64& outRecv) override;`
- L61 _public prototype_ `virtual void Validate(Logger& logger, const Vector<void*>& connections, bool full) override;`
- L63 _public prototype_ `static bool CheckEnvironment(Logger& logger, bool printTips);`
- L64 _public prototype_ `static bool KillTcpHogs(Logger& logger, u16 port);`
- L67 _private prototype_ `bool EnsureInitialized(Logger& logger);`
- L72 _private prototype_ `bool ThreadListen(Logger& logger, ListenEntry& entry);`
- L73 _private prototype_ `void ThreadRecv(Connection& connection);`
- L74 _private prototype_ `void ThreadSend(Connection& connection);`
- L75 _private prototype_ `bool HandleSendError(Connection& connection, Logger& logger, const tchar* hint);`
- L76 _private prototype_ `bool SendSocket(Connection& connection, Logger& logger, const void* b, u64 bufferLen, const tchar* hint);`
- L77 _private prototype_ `bool RecvSocket(Connection& connection, RecvCache& recvCache, void* b, u32& bufferLen, const tchar* hint, bool isFirstCall, bool allowLess);`
- L79 _private prototype_ `void ThreadIocp();`
- L80 _private prototype_ `bool PostIocpRead(Connection& connection, u8* data, u32 dataSize);`
- L82 _private prototype_ `void ThreadStatus(u32 statusUpdateSeconds);`
- L83 _private prototype_ `void PrintTcpStatistics(Logger& logger, u32 statusUpdateSeconds, void* prevStats);`
- L85 _private member_ `LoggerWithWriter m_logger;`
- L86 _private member_ `Futex m_listenEntriesLock;`
- L87 _private member_ `List<ListenEntry> m_listenEntries;`
- L89 _private member_ `Futex m_connectionsLock;`
- L90 _private member_ `List<Connection> m_connections;`
- L92 _private member_ `Atomic<u64> m_totalSend = 0;`
- L93 _private member_ `Atomic<u64> m_totalRecv = 0;`
- L95 _private member_ `bool m_disableNagle;`
- L98 _private member_ `Futex m_initLock;`
- L99 _private member_ `bool m_initDone = false;`
- L100 _private member_ `bool m_initSuccess = false;`
- L101 _private member_ `bool m_useOverlappedSend;`
- L102 _private member_ `u16 m_iocpWorkerCount;`
- L105 _private member_ `u32 m_recvBufferSize;`
- L106 _private member_ `u32 m_sendBufferSize;`
- L108 _private member_ `List<Thread> m_iocpThreads;`
- L109 _private member_ `void* m_iocpHandle = nullptr;`
- L111 _private member_ `Event m_tcpStatusLoop;`
- L112 _private member_ `Thread m_tcpStatusThread;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace uba`

### `Source/Programs/UnrealBuildAccelerator/Common/Public/UbaNetworkClient.h` (Public)


#### struct `uba::NetworkClientCreateInfo`  
`struct NetworkClientCreateInfo`  
_L22-37_
- L24 _public function_ `NetworkClientCreateInfo(LogWriter& w = g_consoleLogWriter) : logWriter(w)`
- L25 _public member_ `LogWriter& logWriter;`
- L26 _public member_ `u32 sendSize = SendDefaultSize;`
- L27 _public member_ `u32 receiveTimeoutSeconds = DefaultNetworkReceiveTimeoutSeconds;`
- L28 _public member_ `u32 workerCount = ~0u;` — ~0u means logical processor count will be used
- L29 _public member_ `bool useMessagePriority = false;`
- L30 _public member_ `bool useThreadedSend = false;`
- L31 _public member_ `const u8* cryptoKey128 = nullptr;`
- L33 _public member_ `u32 recvBufferSize = 0;`
- L34 _public member_ `u32 sendBufferSize = 0;`
- L36 _public prototype_ `void Apply(Config& config, const tchar* tableName = TC("Netw`

#### class `uba::NetworkClient`  
`class NetworkClient : public WorkManagerImpl`  
_L39-146_
- inherits: `WorkManagerImpl`
- L42 _public prototype_ `NetworkClient(bool& outCtorSuccess, const NetworkClientCreateInfo& info = {}, const tchar* name = TC("UbaC`
- L43 _public prototype_ `~NetworkClient();`
- L45 _public prototype_ `bool Connect(NetworkBackend& backend, const tchar* ip, u16 port = DefaultPort, bool* timedOut = nullptr);`
- L46 _public prototype_ `void Disconnect(bool flushWork = true);`
- L48 _public prototype_ `bool StartListen(NetworkBackend& backend, u16 port = DefaultPort, const tchar* ip = TC("0.0.`
- L49 _public prototype_ `bool SetConnectionCount(u32 count);`
- L50 _public prototype_ `bool SendKeepAlive();`
- L52 _public prototype_ `bool FetchConfig(Config& config);`
- L54 _public prototype_ `bool IsConnected(u32 waitTimeoutMs = 0);`
- L55 _public prototype_ `bool IsOrWasConnected(u32 waitTimeoutMs = 0);`
- L57 _public prototype_ `void ValidateNetwork(Logger& logger, bool full);`
- L58 _public prototype_ `void PrintSummary(Logger& logger);`
- L60 _public typedef_ `using OnConnectedFunction = Function<void()>;`
- L61 _public prototype_ `void RegisterOnConnected(const OnConnectedFunction& function);`
- L63 _public typedef_ `using OnDisconnectedFunction = Function<void()>;`
- L64 _public prototype_ `void RegisterOnDisconnected(const OnDisconnectedFunction& function);`
- L66 _public typedef_ `using OnVersionMismatchFunction = Function<void(const CasKey& exeKey, const CasKey& dllKey)>;`
- L67 _public prototype_ `void RegisterOnVersionMismatch(OnVersionMismatchFunction&& function);`
- L68 _public prototype_ `void InvokeVersionMismatch(const CasKey& exeKey, const CasKey& dllKey);`
- L70 _public prototype_ `u64 GetMessageHeaderSize();`
- L71 _public prototype_ `u64 GetMessageMaxSize();`
- L72 _public prototype_ `u64 GetMessageReceiveHeaderSize();`
- L73 _public function_ `const Guid& GetUid()`
- L74 _public function_ `LogWriter& GetLogWriter()`
- L75 _public function_ `u32 GetConnectionCount()`
- L76 _public function_ `u64 GetTotalSentBytes()`
- L77 _public function_ `u64 GetTotalRecvBytes()`
- L79 _public prototype_ `NetworkBackend* GetFirstConnectionBackend();`
- L80 _public prototype_ `void TraverseConnections(const Function<void(NetworkBackend&, void*)>& func);`
- L85 _private prototype_ `bool AddConnection(NetworkBackend& backend, void* backendConnection, bool* timedOut);`
- L86 _private prototype_ `bool ConnectedCallback(NetworkBackend& backend, void* backendConnection, const Guid& cryptoIV);`
- L87 _private prototype_ `static void DisconnectCallback(void* context, const Guid& connectionUid, void* connection);`
- L88 _private prototype_ `static bool ReceiveResponseHeader(void* context, const Guid& connectionUid, u8* headerData, void*& outBodyContext, u8*& outBodyData, u32& outBodySize);`
- L89 _private prototype_ `static bool ReceiveResponseBody(void* context, bool recvError, u8* headerData, void* bodyContext, u8* bodyData, u32 bodySize);`
- L90 _private prototype_ `void OnDisconnected(Connection& connection, u32 reason);`
- L91 _private prototype_ `bool Send(NetworkMessage& message, void* response, u32 responseCapacity, bool async);`
- L92 _private prototype_ `const tchar* SetGetPrefix(const tchar* originalPrefix);`
- L94 _private member_ `LogWriter& m_logWriter;`
- L95 _private member_ `Guid m_uid;`
- L96 _private member_ `TString m_prefix;`
- L97 _private member_ `LoggerWithWriter m_logger;`
- L98 _private member_ `u32 m_sendSize;`
- L99 _private member_ `u32 m_recvBufferSize;`
- L100 _private member_ `u32 m_sendBufferSize;`
- L101 _private member_ `u32 m_receiveTimeoutSeconds;`
- L102 _private member_ `Atomic<u64> m_sendBytes = 0;`
- L103 _private member_ `Atomic<u64> m_recvBytes = 0;`
- L104 _private member_ `Atomic<u32> m_recvCount = 0;`
- L105 _private member_ `Atomic<bool> m_isDisconnecting = false;`
- L106 _private member_ `Timer m_sendTimer;`
- L108 _private member_ `Futex m_serverUidLock;`
- L109 _private member_ `Guid m_serverUid;`
- L111 _private member_ `Event m_isConnected;`
- L112 _private member_ `Event m_isOrWasConnected;`
- L113 _private member_ `Atomic<u32> m_connectionCount = 0;`
- L114 _private member_ `bool m_useMessagePriority;`
- L115 _private member_ `bool m_useThreadedSend;`
- L117 _private member_ `Futex m_onConnectedFunctionsLock;`
- L118 _private member_ `Vector<OnConnectedFunction> m_onConnectedFunctions;`
- L119 _private member_ `ReaderWriterLock m_onDisconnectedFunctionsLock;`
- L120 _private member_ `Vector<OnDisconnectedFunction> m_onDisconnectedFunctions;`
- L121 _private member_ `OnVersionMismatchFunction m_versionMismatchFunction;`
- L123 _private member_ `ReaderWriterLock m_connectionsLock;`
- L124 _private member_ `List<Connection> m_connections;`
- L125 _private member_ `Futex m_connectionsItLock;`
- L126 _private member_ `List<Connection>::iterator m_connectionsIt;`
- L129 _private member_ `ReaderWriterLock m_activeMessagesLock;`
- L130 _private member_ `u16 m_activeMessageIdMax = 1;`
- L131 _private member_ `Vector<u16> m_availableMessageIds;`
- L132 _private member_ `Vector<NetworkMessage*> m_activeMessages;`
- L134 _private member_ `CryptoKey m_cryptoKey = InvalidCryptoKey;`
- L135 _private member_ `Timer m_encryptTimer;`
- L136 _private member_ `Timer m_decryptTimer;`
- L139 _private member_ `u64 m_startTime = 0;`
- L144 _private prototype_ `NetworkClient(const NetworkClient&) = delete;`
- L145 _private prototype_ `NetworkClient& operator=(const NetworkClient&) = delete;`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace uba`

### `Source/Programs/UnrealBuildAccelerator/Common/Public/UbaNetworkMessage.h` (Public)


#### enum `uba::MessagePriority`  
`enum MessagePriority : u8`  
_L10-10_
- L10 _public enumerator_ `enum MessagePriority : u8 { NormalPriority, HasPriority }; struct NetworkMessage { NetworkMessage(NetworkClient& client, u8 serviceId, u8 messageType, BinaryWriter& sendWriter, MessagePriority priority = NormalPriority); NetworkMessage() {} ~NetworkMessage();`
- L10 _public enumerator_ `enum MessagePriority : u8 { NormalPriority, HasPriority }; struct NetworkMessage { NetworkMessage(NetworkClient& client, u8 serviceId, u8 messageType, BinaryWriter& sendWriter, MessagePriority priority = NormalPriority); NetworkMessage() {} ~NetworkMessage();`

#### struct `uba::NetworkMessage`  
`struct NetworkMessage`  
_L12-56_
- L14 _public prototype_ `NetworkMessage(NetworkClient& client, u8 serviceId, u8 messageType, BinaryWriter& sendWriter, MessagePriority priority = NormalPriority);`
- L15 _public function_ `NetworkMessage()`
- L16 _public prototype_ `~NetworkMessage();`
- L18 _public prototype_ `void Init(NetworkClient& client, u8 serviceId, u8 messageType, BinaryWriter& sendWriter, MessagePriority priority = NormalPriority);`
- L20 _public prototype_ `bool Send(BinaryReader& response);`
- L21 _public prototype_ `bool Send(BinaryReader& response, Timer& outTimer);`
- L22 _public prototype_ `bool Send();`
- L23 _public prototype_ `bool Send(Timer& outTimer);`
- L25 _public typedef_ `using DoneFunc = void(bool error, void* userData);`
- L26 _public prototype_ `bool SendAsync(BinaryReader& response, DoneFunc* func, void* userData);` — Try to minimize work in GetResponseFunc since it is running on receiving thread
- L27 _public prototype_ `bool ProcessAsyncResults(BinaryReader& response);` — Note, this must be called after GetResponseFunc has been called
- L29 _public function_ `u32 GetError() const`
- L30 _public prototype_ `u8 GetServiceId();`
- L31 _public prototype_ `u8 GetMessageType();`
- L34 _private prototype_ `void Done(bool shouldLock = true);`
- L36 _private member_ `NetworkClient* m_client = nullptr;`
- L37 _private member_ `BinaryWriter* m_sendWriter = nullptr;`
- L38 _private member_ `DoneFunc* m_doneFunc = nullptr;`
- L39 _private member_ `void* m_doneUserData = nullptr;`
- L40 _private member_ `void* m_response = nullptr;`
- L41 _private member_ `NetworkBackend::SendContext m_sendContext;`
- L42 _private member_ `u32 m_responseSize = 0;`
- L43 _private member_ `u32 m_responseCapacity = 0;`
- L44 _private member_ `u16 m_id = 0;`
- L45 _private member_ `MessagePriority m_priority;`
- L46 _private member_ `Atomic<u32> m_error = 0;`
- L47 _private member_ `NetworkClient::Connection* m_connection = nullptr;`
- L48 _private member_ `Guid m_cryptoIV;`
- L50 _private prototype_ `NetworkMessage(const NetworkMessage&) = delete;`
- L51 _private prototype_ `NetworkMessage(NetworkMessage&&) = delete;`
- L54 _private member_ `u64 m_sendTime = 0;`

#### enum `uba::NetworkMessageError`  
`enum NetworkMessageError`  
_L58-61_
- L60 _public enumerator_ `NetworkMessageError_Disconnecting = 1`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace uba`

### `Source/Programs/UnrealBuildAccelerator/Common/Public/UbaNetworkServer.h` (Public)


#### struct `uba::ConnectionInfo`  
`struct ConnectionInfo`  
_L23-35_
- L25 _public prototype_ `const Guid& GetUid() const;`
- L26 _public prototype_ `u32 GetId() const;`
- L27 _public prototype_ `bool GetName(StringBufferBase& out) const;`
- L28 _public prototype_ `u64 GetCryptoUserData() const;`
- L29 _public prototype_ `bool ShouldDisconnect() const;`
- L31 _public prototype_ `void SetStorageVersion(u32 version) const;`
- L32 _public prototype_ `u32 GetStorageVersion() const;`
- L34 _public member_ `void* internalData = nullptr;`

#### struct `uba::NetworkServerCreateInfo`  
`struct NetworkServerCreateInfo`  
_L37-54_
- L39 _public function_ `NetworkServerCreateInfo(LogWriter& w = g_consoleLogWriter) : logWriter(w)`
- L41 _public prototype_ `void Apply(Config& config, const tchar* tableName = TC("Netw`
- L43 _public member_ `LogWriter& logWriter;`
- L44 _public member_ `u32 workerCount = 0;` — Zero means it will use the number of logical cores as worker count
- L45 _public member_ `u32 sendSize = SendDefaultSize;`
- L46 _public member_ `u32 receiveTimeoutSeconds = DefaultNetworkReceiveTimeoutSeconds;`
- L47 _public member_ `bool logConnections = true;`
- L48 _public member_ `bool useKeepAlive = false;`
- L49 _public member_ `bool useMessagePriority = false;`
- L50 _public member_ `bool useThreadedSend = false;`
- L52 _public member_ `u32 recvBufferSize = 0;`
- L53 _public member_ `u32 sendBufferSize = 0;`

#### struct `uba::MessageInfo`  
`struct MessageInfo`  
_L56-61_
- L58 _public member_ `u32 connectionId;`
- L59 _public member_ `u16 messageId;`
- L60 _public member_ `u8 type;`

#### class `uba::NetworkServer`  
`class NetworkServer : public WorkManager`  
_L63-222_
- inherits: `WorkManager`
- L66 _public prototype_ `NetworkServer(bool& outCtorSuccess, const NetworkServerCreateInfo& info = {}, const tchar* name = TC("UbaS`
- L67 _public prototype_ `virtual ~NetworkServer();`
- L69 _public prototype_ `bool StartListen(NetworkBackend& backend, u16 port = DefaultPort, const tchar* ip = TC("0.0.0.0"), bool requiresCrypto =` — Start listen for new connections/clients
- L70 _public prototype_ `void DisallowNewClients();` — Disallow new clients to connect but old clients can still create more connections
- L71 _public prototype_ `void DisconnectClients();` — Disconnect all active connections
- L72 _public prototype_ `void ShutdownActiveConnections();` — Signal each currently-active connection to disconnect (backend.Shutdown — sets shutdownCalled + wakes recv/send polls). Connections tear down via the normal recv-exit path; m_workersEnabled / m_allClientsDisconnected are NOT touched, so the server stays usable. Used by CacheServer maintenance to dra
- L74 _public prototype_ `bool RegisterCryptoKey(const u8* cryptoKey128, u64 expirationTime = ~u64(0), u64 cryptoUserData = 0);`
- L75 _public prototype_ `void SetClientsConfig(const Config& config);`
- L76 _public prototype_ `void SetTrace(Trace* trace);`
- L78 _public prototype_ `bool AddClient(NetworkBackend& backend, const tchar* ip, u16 port = DefaultPort, const u8* cryptoKey128 = nullptr);` — Adds a client that server will create one or more connections to (note this will return before we know if it was a success or not)
- L79 _public prototype_ `bool HasConnectInProgress();`
- L81 _public prototype_ `void PrintSummary(Logger& logger);`
- L83 _public typedef_ `using TypeToNameFunction = StringView(u8 type);`
- L84 _public typedef_ `using WorkerFunction = Function<bool(const ConnectionInfo& connectionInfo, const WorkContext& workContext, MessageInfo& messageInfo, BinaryReader& reader, BinaryWriter& writer)>;`
- L85 _public prototype_ `void RegisterService(u8 serviceId, const WorkerFunction& function, TypeToNameFunction* typeToNameFunc = nullptr);`
- L86 _public prototype_ `void UnregisterService(u8 serviceId);`
- L88 _public typedef_ `using OnConnectionFunction = Function<bool(const Guid& clientUid, u32 clientId)>;`
- L89 _public prototype_ `void RegisterOnClientConnected(u8 id, const OnConnectionFunction& func);`
- L90 _public prototype_ `void UnregisterOnClientConnected(u8 id);`
- L92 _public typedef_ `using OnDisconnectFunction = Function<void(const Guid& clientUid, u32 clientId)>;`
- L93 _public prototype_ `void RegisterOnClientDisconnected(u8 id, const OnDisconnectFunction& func);`
- L94 _public prototype_ `void UnregisterOnClientDisconnected(u8 id);`
- L100 _public prototype_ `virtual void AddWork(WorkFunction&& work, u32 count, const tchar* desc, const Color& color = ColorWork, WorkPriority priority = WorkPriority_Normal, Bottleneck* bottleneck = nullptr) override final;`
- L101 _public prototype_ `virtual void DoWork(u32 count = 1) override final;`
- L102 _public prototype_ `virtual u32 GetWorkerCount() override final;`
- L103 _public prototype_ `virtual bool FlushWork(u32 timeoutMs = 0) override final;`
- L112 _public prototype_ `MutableLogger& GetLogger();`
- L113 _public prototype_ `u64 GetTotalSentBytes();`
- L114 _public prototype_ `u64 GetTotalRecvBytes();`
- L115 _public prototype_ `Timer& GetTotalSentTimer();`
- L116 _public prototype_ `u32 GetClientCount();`
- L117 _public prototype_ `u32 GetConnectionCount();`
- L118 _public prototype_ `void GetClientStats(ClientStats& out, u32 clientId);`
- L119 _public prototype_ `bool IsConnectedSlow(u32 clientId);`
- L120 _public prototype_ `void ResetTotalStats();`
- L122 _public prototype_ `bool DoAdditionalWork();`
- L124 _public prototype_ `bool SendResponse(const MessageInfo& info, const u8* body, u32 bodySize);`
- L125 _public prototype_ `bool SendKeepAlive();`
- L127 _public prototype_ `void RemoveDisconnectedConnections();`
- L135 _private prototype_ `Worker* PopWorker();`
- L136 _private prototype_ `Worker* PopWorkerNoLock();`
- L137 _private prototype_ `void PushWorker(Worker* worker);`
- L138 _private prototype_ `void PushWorkerNoLock(Worker* worker);`
- L139 _private prototype_ `void FlushWorkers();`
- L141 _private prototype_ `bool HandleSystemMessage(const ConnectionInfo& connectionInfo, u8 messageType, BinaryReader& reader, BinaryWriter& writer);`
- L142 _private prototype_ `bool AddConnection(NetworkBackend& backend, void* backendConnection, const sockaddr& remoteSocketAddr, bool requiresCrypto, CryptoKey cryptoKey);`
- L144 _private member_ `MutableLogger m_logger;`
- L152 _private member_ `Futex m_cryptoKeysLock;`
- L153 _private member_ `List<CryptoEntry> m_cryptoKeys;`
- L155 _private member_ `Guid m_uid;`
- L156 _private member_ `bool m_allowNewClients = true;`
- L159 _private member_ `WorkerRec m_workerFunctions[4];`
- L160 _private member_ `OnConnectionFunction m_onConnectionFunction;`
- L163 _private member_ `ReaderWriterLock m_onDisconnectFunctionsLock;`
- L164 _private member_ `List<OnDisconnectEntry> m_onDisconnectFunctions;`
- L166 _private member_ `u32 m_maxWorkerCount = 0;`
- L168 _private member_ `WorkQueue m_additionalWorkQueue;`
- L170 _private member_ `Futex m_availableWorkersLock;`
- L171 _private member_ `Worker* m_firstAvailableWorker = nullptr;`
- L172 _private member_ `Worker* m_firstActiveWorker = nullptr;`
- L180 _private member_ `PopWorkerRequest* m_firstRequest = nullptr;`
- L181 _private member_ `PopWorkerRequest* m_lastRequest = nullptr;`
- L183 _private member_ `u32 m_sendSize = 0;`
- L184 _private member_ `u32 m_receiveTimeoutMs = 0;`
- L185 _private member_ `u32 m_createdWorkerCount = 0;`
- L186 _private member_ `u32 m_maxCreatedWorkerCount = 0;`
- L187 _private member_ `u32 m_recvBufferSize;`
- L188 _private member_ `u32 m_sendBufferSize;`
- L189 _private member_ `bool m_workersEnabled = true;`
- L190 _private member_ `bool m_logConnections = true;`
- L191 _private member_ `bool m_useKeepAlive = false;`
- L192 _private member_ `bool m_useMessagePriority = false;`
- L193 _private member_ `bool m_useThreadedSend = false;`
- L194 _private member_ `bool m_allClientsDisconnected = false;`
- L196 _private member_ `Futex m_addConnectionsLock;`
- L197 _private member_ `List<Thread> m_addConnections;`
- L199 _private member_ `ReaderWriterLock m_connectionsLock;`
- L200 _private member_ `List<Connection> m_connections;`
- L201 _private member_ `u32 m_connectionIdCounter = 1;`
- L202 _private member_ `u32 m_maxActiveConnections = 0;`
- L204 _private member_ `Vector<char> m_clientsConfig;`
- L207 _private member_ `ReaderWriterLock m_clientsLock;`
- L208 _private member_ `UnorderedMap<u32, Client> m_clients;`
- L209 _private member_ `u32 m_clientCounter = 0;`
- L211 _private member_ `Timer m_sendTimer;`
- L212 _private member_ `Timer m_encryptTimer;`
- L213 _private member_ `Timer m_decryptTimer;`
- L214 _private member_ `Atomic<u64> m_sendBytes = 0;`
- L215 _private member_ `Atomic<u64> m_recvBytes = 0;`
- L216 _private member_ `Atomic<u32> m_recvCount = 0;`
- L218 _private member_ `Trace* m_trace = nullptr;`
- L220 _private prototype_ `NetworkServer(const NetworkServer&) = delete;`
- L221 _private prototype_ `void operator=(const NetworkServer&) = delete;`

#### struct `uba::NetworkServer::ClientStats`  
`struct ClientStats`  
_L105-110_
- L107 _public member_ `u64 send = 0;`
- L108 _public member_ `u64 recv = 0;`
- L109 _public member_ `u32 connectionCount = 0;`

#### struct `uba::NetworkServer::CryptoEntry`  
`struct CryptoEntry`  
_L146-151_
- L148 _public member_ `CryptoKey key;`
- L149 _public member_ `u64 expirationTime;`
- L150 _public member_ `u64 userData;`

#### struct `uba::NetworkServer::WorkerRec`  
`struct WorkerRec`  
_L158-158_
- L158 _public member_ `struct WorkerRec { WorkerFunction func; TypeToNameFunction* toString = nullptr; };`
- L158 _public member_ `struct WorkerRec { WorkerFunction func; TypeToNameFunction* toString = nullptr; };`

#### struct `uba::NetworkServer::OnDisconnectEntry`  
`struct OnDisconnectEntry`  
_L162-162_
- L162 _public member_ `struct OnDisconnectEntry { u8 id; OnDisconnectFunction function; };`
- L162 _public member_ `struct OnDisconnectEntry { u8 id; OnDisconnectFunction function; };`

#### struct `uba::NetworkServer::PopWorkerRequest`  
`struct PopWorkerRequest`  
_L174-179_
- L176 _public member_ `EventSlim ev;`
- L177 _public member_ `PopWorkerRequest* next = nullptr;`
- L178 _public member_ `Worker* worker = nullptr;`

#### Free symbols / members of external scopes

- L15 _namespace_ `namespace uba`

### `Source/Programs/UnrealBuildAccelerator/Common/Public/UbaObjectFile.h` (Public)


#### struct `uba::ExportInfo`  
`struct ExportInfo`  
_L23-23_
- L23 _public member_ `struct ExportInfo { std::string symbol; u8 isData = 0; u32 index = 0; u64 size = 0; u8 isHidden = 0; u32 alignment = 0; };`
- L23 _public member_ `struct ExportInfo { std::string symbol; u8 isData = 0; u32 index = 0; u64 size = 0; u8 isHidden = 0; u32 alignment = 0; };`
- L23 _public member_ `struct ExportInfo { std::string symbol; u8 isData = 0; u32 index = 0; u64 size = 0; u8 isHidden = 0; u32 alignment = 0; };`
- L23 _public member_ `struct ExportInfo { std::string symbol; u8 isData = 0; u32 index = 0; u64 size = 0; u8 isHidden = 0; u32 alignment = 0; };`
- L23 _public member_ `struct ExportInfo { std::string symbol; u8 isData = 0; u32 index = 0; u64 size = 0; u8 isHidden = 0; u32 alignment = 0; };`
- L23 _public member_ `struct ExportInfo { std::string symbol; u8 isData = 0; u32 index = 0; u64 size = 0; u8 isHidden = 0; u32 alignment = 0; };`

#### enum `uba::ObjectFileType`  
`enum ObjectFileType : u8`  
_L28-35_
- L30 _public enumerator_ `ObjectFileType_Unknown`
- L31 _public enumerator_ `ObjectFileType_Coff`
- L32 _public enumerator_ `ObjectFileType_Elf`
- L33 _public enumerator_ `ObjectFileType_LLVMIR`
- L34 _public enumerator_ `ObjectFileType_MachO`

#### enum `uba::ObjectFileParseMode`  
`enum ObjectFileParseMode : u8`  
_L37-41_
- L39 _public enumerator_ `ObjectFileParseMode_Exports`
- L40 _public enumerator_ `ObjectFileParseMode_All`

#### class `uba::ObjectFile`  
`class ObjectFile`  
_L43-147_
- L46 _public prototype_ `static ObjectFile* OpenAndParse(Logger& logger, ObjectFileParseMode parseMode, const tchar* fileName);`
- L47 _public prototype_ `static ObjectFile* Parse(Logger& logger, ObjectFileParseMode parseMode, u8* data, u64 dataSize, const tchar* hint);`
- L49 _public prototype_ `virtual bool CopyMemoryAndClose();`
- L50 _public prototype_ `bool WriteImportsAndExports(Logger& logger, MemoryBlock& memoryBlock, bool verbose, u8 version = SymbolFileVersion);`
- L51 _public prototype_ `bool WriteImportsAndExports(Logger& logger, const tchar* exportsFilename, bool verbose, u8 version = SymbolFileVersion);`
- L52 _public prototype_ `template<typename WriteFunc> bool WriteImportsAndExports(Logger& logger, const WriteFunc& write, bool verbose, u8 version = SymbolFileVersion);`
- L54 _public prototype_ `virtual const char* GetLibName();`
- L56 _public prototype_ `const tchar* GetFileName() const;`
- L57 _public prototype_ `const UnorderedSymbols& GetImports() const;`
- L58 _public prototype_ `const UnorderedExports& GetExports() const;`
- L59 _public prototype_ `const UnorderedExports& GetExplicitExports() const;` — Symbols this file explicitly exports (COFF /EXPORT: directives). Verbatim names.
- L60 _public prototype_ `const UnorderedSymbols& GetPotentialDuplicates() const;`
- L62 _public prototype_ `static bool CreateExtraFile(Logger& logger, const StringView& extraObjFilename, const StringView& moduleName, const StringView& platform, const AllExternalImports& allExternalImports, const AllInternalImports& allInternalImports, const AllExports& allExports, const AllExports& allExplicitExports, const ExtraExports& extraExports, bool includeExportsInFile);`
- L64 _public prototype_ `virtual ~ObjectFile();`
- L66 _public prototype_ `void RemoveExportedSymbol(const char* symbol);`
- L67 _public function_ `u8* GetData()`
- L68 _public function_ `u64 GetDataSize()`
- L71 _protected prototype_ `virtual bool Parse(Logger& logger, ObjectFileParseMode parseMode, const tchar* hint) = 0;`
- L73 _protected prototype_ `static bool CreateVersionScript(Logger& logger, MemoryBlock& memoryBlock, const AllExternalImports& allExternalImports, const AllInternalImports& allInternalImports, const AllExports& allExports, const ExtraExports& extraExports, bool includeExportsInFile, bool isDynList);`
- L74 _protected prototype_ `static bool CreateEmdFile(Logger& logger, MemoryBlock& memoryBlock, const StringView& moduleName, const AllExternalImports& allExternalImports, const AllInternalImports& allInternalImports, const AllExports& allExports, bool includeExportsInFile);`
- L75 _protected prototype_ `static bool CreateExportedSymbolsList(Logger& logger, MemoryBlock& memoryBlock, const AllExternalImports& allExternalImports, const AllInternalImports& allInternalImports, const AllExports& allExports, const ExtraExports& extraExports);`
- L77 _protected member_ `FileAccessor* m_file = nullptr;`
- L78 _protected member_ `u8* m_data = nullptr;`
- L79 _protected member_ `u64 m_dataSize = 0;`
- L80 _protected member_ `bool m_ownsData = false;`
- L82 _protected member_ `ObjectFileType m_type;`
- L83 _protected member_ `UnorderedSymbols m_imports;`
- L84 _protected member_ `UnorderedExports m_exports;`
- L85 _protected member_ `UnorderedExports m_explicitExports;`
- L86 _protected member_ `UnorderedSymbols m_potentialDuplicates;`

#### struct `uba::ObjectFile::AnsiStringView`  
`struct AnsiStringView`  
_L89-146_
- L91 _public member_ `const char* strBegin;`
- L92 _public member_ `const char* strEnd;`
- L94 _public function_ `char operator[](u64 pos) const`
- L99 _public function_ `u32 Length() const`
- L104 _public function_ `bool StartsWith(const char* str, u32 strLen) const`
- L111 _public function_ `bool Contains(const char* str, u32 strLen) const`
- L124 _public function_ `bool Equals(const char* str, u32 strLen) const`
- L131 _public function_ `std::string ToString() const`
- L136 _public function_ `std::string& ToString(std::string& out) const`
- L142 _public function_ `AnsiStringView Skip(u64 count) const`
- L144 _public function_ `AnsiStringView(const char* b, const char* e) : strBegin(b), strEnd(e)`
- L145 _public function_ `AnsiStringView(const std::string& s) : strBegin(s.data()), strEnd(strBegin + s.size())`

#### struct `uba::SymbolFile`  
`struct SymbolFile`  
_L149-157_
- L151 _public member_ `UnorderedSymbols imports;`
- L152 _public member_ `UnorderedExports exports;`
- L153 _public member_ `UnorderedExports explicitExports;` — Verbatim names of symbols the source file explicitly exported (COFF /EXPORT:).
- L154 _public member_ `ObjectFileType type;`
- L156 _public prototype_ `bool ParseFile(Logger& logger, const tchar* filename);`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace uba`
- L16 _externvar_ `extern u8 SymbolFileVersion;` (scope `uba`) — Current/default .exi format written. Reader accepts this and older (down to 2).
- L18 _typedef_ `using UnorderedSymbols = UnorderedSet<std::string>;` (scope `uba`)
- L19 _typedef_ `using AllExternalImports = UnorderedSymbols;` (scope `uba`)
- L20 _typedef_ `using AllInternalImports = UnorderedSymbols;` (scope `uba`)
- L21 _typedef_ `using ExtraExports = Vector<std::string>;` (scope `uba`)
- L24 _typedef_ `using UnorderedExports = UnorderedMap<StringKey, ExportInfo>;` (scope `uba`)
- L26 _typedef_ `using AllExports = UnorderedExports;` (scope `uba`)

### `Source/Programs/UnrealBuildAccelerator/Common/Public/UbaProcess.h` (Public)


#### class `uba::Process`  
`class Process`  
_L14-43_
- L17 _public prototype_ `virtual const ProcessStartInfo& GetStartInfo() const = 0;`
- L18 _public function_ `virtual u32 GetId()`
- L19 _public function_ `virtual u32 GetExitCode()`
- L20 _public function_ `virtual bool HasExited()`
- L21 _public function_ `virtual bool WaitForExit(u32 millisecondsTimeout)`
- L22 _public function_ `virtual u64 GetTotalProcessorTime() const`
- L23 _public function_ `virtual u64 GetTotalWallTime() const`
- L24 _public function_ `virtual u64 GetPeakMemory() const`
- L25 _public prototype_ `virtual const Vector<ProcessLogLine>& GetLogLines() const = 0;`
- L26 _public prototype_ `virtual const Vector<u8>& GetTrackedInputs() const = 0;`
- L27 _public prototype_ `virtual const Vector<u8>& GetTrackedOutputs() const = 0;`
- L28 _public function_ `virtual bool Cancel()`
- L29 _public function_ `virtual bool IsCalledFromThis() const`
- L30 _public function_ `virtual const tchar* GetExecutingHost() const`
- L31 _public function_ `virtual bool IsRemote() const`
- L32 _public function_ `virtual ProcessExecutionType GetExecutionType() const`
- L33 _public function_ `virtual bool IsChild()`
- L34 _public function_ `virtual bool IsArm()`
- L35 _public function_ `virtual void TraverseOutputFiles(const Function<void(StringView file)>& func)`
- L38 _protected prototype_ `void AddRef();`
- L39 _protected prototype_ `void Release();`
- L40 _protected function_ `virtual ~Process()`
- L41 _protected member_ `Atomic<u32> m_refCount = 0;`

#### class `uba::ProcessImpl`  
`class ProcessImpl final : public Process`  
_L45-220_
- inherits: `Process`
- L49 _public function_ `virtual const ProcessStartInfo& GetStartInfo() const override`
- L50 _public function_ `virtual u32 GetId() override`
- L51 _public function_ `virtual u32 GetExitCode() override`
- L52 _public function_ `virtual bool HasExited() override`
- L53 _public prototype_ `virtual bool WaitForExit(u32 millisecondsTimeout) override;`
- L54 _public prototype_ `virtual u64 GetTotalProcessorTime() const override;`
- L55 _public prototype_ `virtual u64 GetTotalWallTime() const override;`
- L56 _public prototype_ `virtual u64 GetPeakMemory() const override;`
- L57 _public function_ `virtual const Vector<ProcessLogLine>& GetLogLines() const override`
- L58 _public function_ `virtual const Vector<u8>& GetTrackedInputs() const override`
- L59 _public function_ `virtual const Vector<u8>& GetTrackedOutputs() const override`
- L60 _public prototype_ `virtual bool Cancel() override;`
- L61 _public prototype_ `virtual bool IsCalledFromThis() const override;`
- L62 _public function_ `virtual const tchar* GetExecutingHost() const override`
- L63 _public function_ `virtual bool IsRemote() const override`
- L64 _public function_ `virtual ProcessExecutionType GetExecutionType() const override`
- L65 _public function_ `virtual bool IsChild() override`
- L66 _public function_ `virtual bool IsArm() override`
- L67 _public prototype_ `virtual void TraverseOutputFiles(const Function<void(StringView file)>& func) override;`
- L69 _public prototype_ `ProcessImpl(Session& session, u32 id, ProcessImpl* parent, bool detourEnabled);`
- L70 _public prototype_ `~ProcessImpl();`
- L74 _public prototype_ `bool Start(const ProcessStartInfo& startInfo, bool runningRemote, Vector<tchar>& environment, bool async, void* userDataOverride);`
- L76 _public prototype_ `bool IsActive();`
- L77 _public prototype_ `bool IsCancelled();`
- L78 _public prototype_ `bool HasFailedMessage();`
- L80 _public prototype_ `bool WaitForRead();`
- L81 _public prototype_ `void SetWritten();`
- L83 _public prototype_ `void ThreadRun(Vector<tchar>& environment);`
- L84 _public prototype_ `void ThreadExit();`
- L86 _public prototype_ `bool HandleMessage(BinaryReader& reader, BinaryWriter& writer);`
- L87 _public prototype_ `bool HandleSpecialApplication();`
- L88 _public prototype_ `bool HandleGetWrittenFiles(bool isInit, BinaryWriter& writer);`
- L89 _public prototype_ `void CallSession(MessageType type, bool success);`
- L94 _public prototype_ `bool WriteCreateProcessResponse(ProcessHandle h, BinaryWriter& writer, bool isChild);`
- L96 _public prototype_ `void LogLine(bool printInSession, TString&& line, LogEntryType logType);`
- L97 _public prototype_ `bool CreateTempFile(BinaryReader& reader, ProcHandle nativeProcessHandle, const tchar* application);`
- L98 _public prototype_ `bool OpenTempFile(BinaryReader& reader, BinaryWriter& writer, const tchar* application);`
- L99 _public prototype_ `bool WriteFilesToDisk();`
- L100 _public prototype_ `void CleanupWrittenFiles();`
- L102 _public prototype_ `const tchar* InternalGetChildLogFile(StringBufferBase& temp);`
- L105 _public prototype_ `bool PollStdPipes(PipeReader& outReader, PipeReader& errReader, int timeoutMs = -1);`
- L108 _public prototype_ `u32 InternalCreateProcess(Vector<tchar>& environment, FileMappingHandle communicationHandle, u64 communicationOffset);`
- L109 _public prototype_ `u32 InternalExitProcess(bool cancel);`
- L110 _public prototype_ `void InternalLogLine(bool printInSession, TString&& line, LogEntryType logType);`
- L111 _public prototype_ `void InternalDestroyEvents();`
- L112 _public prototype_ `void WaitForParent();`
- L113 _public prototype_ `void WaitForChildrenExit();`
- L114 _public prototype_ `bool CancelWithError(bool dummy = true);`
- L115 _public prototype_ `void CallExitedFunc();`
- L117 _public member_ `ProcessStartInfoHolder m_startInfo;`
- L118 _public member_ `Session& m_session;`
- L119 _public member_ `ProcessImpl* m_parentProcess;`
- L120 _public member_ `Futex m_initLock;`
- L121 _public member_ `u32 m_id;`
- L122 _public member_ `FileMappingAllocation m_comMemory;`
- L123 _public member_ `void* m_userDataOverride = nullptr;`
- L126 _public member_ `SharedEvent m_cancelEvent;`
- L127 _public member_ `SharedEvent m_writeEvent;`
- L128 _public member_ `SharedEvent m_readEvent;`
- L130 _public member_ `Futex m_comMemoryLock;`
- L131 _public member_ `SharedEvent& m_cancelEvent;`
- L132 _public member_ `SharedEvent& m_writeEvent;`
- L133 _public member_ `SharedEvent& m_readEvent;`
- L135 _public member_ `int m_stdOutPipe = -1;`
- L136 _public member_ `int m_stdErrPipe = -1;`
- L137 _public member_ `bool m_doOneExtraCheckForExitMessage = true;`
- L140 _public member_ `ProcHandle m_nativeProcessHandle = InvalidProcHandle;`
- L143 _public member_ `HANDLE m_nativeThreadHandle = 0;`
- L144 _public member_ `HANDLE m_accountingJobObject = NULL;`
- L173 _public member_ `OverflowedWrittenFilesMessage* m_firstOverflowMessage = nullptr;`
- L174 _public member_ `DirTableSnapshot* m_dirTableSnapshot = nullptr;`
- L176 _public member_ `u32 m_nativeProcessId = 0;`
- L177 _public member_ `u32 m_nativeProcessExitCode = ~0u;`
- L178 _public member_ `u64 m_nativeProcessCreationTime = 0;`
- L179 _public member_ `u32 m_exitCode = ~0u;`
- L180 _public member_ `u32 m_messageCount = 0;`
- L181 _public member_ `Atomic<bool> m_cancelAllowed = true;`
- L182 _public member_ `Atomic<bool> m_cancelled = false;`
- L183 _public member_ `Atomic<bool> m_hasExited = false;`
- L184 _public member_ `Atomic<bool> m_parentReportedExit = false;`
- L185 _public member_ `MessageType m_firstMessageError = MessageType_None;`
- L186 _public member_ `bool m_runningRemote = false;`
- L187 _public member_ `bool m_gotExitMessage = false;`
- L188 _public member_ `bool m_detourEnabled = true;`
- L189 _public member_ `bool m_isArmBinary = false;`
- L190 _public member_ `TString m_realApplication;`
- L191 _public member_ `const tchar* m_realWorkingDir = nullptr;`
- L192 _public member_ `u64 m_startTime = 0;`
- L193 _public member_ `u64 m_exitTime = 0;`
- L194 _public member_ `Event m_waitForParent;`
- L195 _public member_ `Futex m_logLinesLock;`
- L196 _public member_ `Vector<ProcessLogLine> m_logLines;`
- L197 _public member_ `Vector<u8> m_trackedInputs;`
- L198 _public member_ `Vector<u8> m_trackedOutputs;`
- L199 _public member_ `Vector<ProcessHandle> m_childProcesses;`
- L200 _public member_ `Shared& m_shared;`
- L201 _public member_ `SessionStats m_sessionStats;`
- L202 _public member_ `StorageStats m_storageStats;`
- L203 _public member_ `ProcessStats m_processStats;`
- L204 _public member_ `KernelStats m_kernelStats;`
- L210 _public member_ `Futex m_usedFileMappingsLock;`
- L211 _public member_ `UnorderedMap<StringKey, UsedFileMapping> m_usedFileMappings;`
- L213 _public member_ `Event m_messageThreadDone;`
- L214 _public member_ `Thread* m_messageThread = nullptr;`
- L216 _public member_ `u8 m_extractExportsVersion = 0;` — .exi format version requested by the /extractexports<N> token (2 or 3); 0 = no extraction
- L218 _public prototype_ `ProcessImpl(const ProcessImpl&) = delete;`
- L219 _public prototype_ `void operator=(const ProcessImpl&) = delete;`

#### struct `uba::ProcessImpl::MoveSource`  
`struct MoveSource`  
_L149-149_
- L149 _public member_ `struct MoveSource { TString name; TString backedName; };`
- L149 _public member_ `struct MoveSource { TString name; TString backedName; };`

#### struct `uba::ProcessImpl::Shared`  
`struct Shared`  
_L151-171_
- L153 _public member_ `Futex activeFilesLock;`
- L154 _public member_ `UnorderedMap<u32, ActiveFile> activeFiles;`
- L156 _public member_ `Futex writtenFilesLock;`
- L157 _public member_ `UnorderedMap<StringKey, WrittenFile> writtenFiles;`
- L158 _public member_ `UnorderedSet<SharedMemoryHandle> sharedMemoryHandles;` — Track created memory handles. entries can be transferred to WrittenFiles
- L159 _public member_ `DirectoryTableOverlay overlay;`
- L160 _public member_ `TString m_tempPath;`
- L161 _public member_ `u32 m_tempPathId = ~0u;`
- L163 _public member_ `Set<TString> createdDirectories;`
- L164 _public member_ `Set<TString> removedDirectories;`
- L165 _public member_ `Set<TString> deletedFiles;`
- L166 _public member_ `Map<TString, MoveSource> movedFiles;` — To, From (note it is backwards). From can have backedName so we can turn it to a write if source gets overwritten
- L169 _public member_ `Map<TString, TString> symlinks;`

#### struct `uba::ProcessImpl::UsedFileMapping`  
`struct UsedFileMapping`  
_L206-209_
- L208 _public member_ `bool closeAfterWritten;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UBA_EXIT_CODE(x) (9000 + x)`
- L12 _namespace_ `namespace uba`
- L91 _macro_ `#define UBA_PROCESS_MESSAGE(M) bool Handle##M(BinaryReader& reader, BinaryWriter& writer);`

### `Source/Programs/UnrealBuildAccelerator/Common/Public/UbaProcessHandle.h` (Public)


#### struct `uba::ProcessLogLine`  
`struct ProcessLogLine`  
_L20-24_
- L22 _public member_ `TString text;`
- L23 _public member_ `LogEntryType type = LogEntryType_Info;`

#### enum `uba::ProcessExecutionType`  
`enum ProcessExecutionType : u8`  
_L26-33_
- L28 _public enumerator_ `ProcessExecutionType_Native` — Local with no detour
- L29 _public enumerator_ `ProcessExecutionType_Local` — Local with detour
- L30 _public enumerator_ `ProcessExecutionType_Remote` — Remotely with detour
- L31 _public enumerator_ `ProcessExecutionType_FromCache` — Downloaded from cache (scheduler only)
- L32 _public enumerator_ `ProcessExecutionType_Skipped` — Skipped (scheduler only)

#### class `uba::ProcessHandle`  
`class ProcessHandle`  
_L35-74_
- L38 _public prototype_ `bool IsValid() const;` — Returns true if handle points to a process
- L39 _public prototype_ `const ProcessStartInfo& GetStartInfo() const;` — Get the info used to start process
- L40 _public prototype_ `u32 GetId() const;` — Unique id of process. Is an increasing index internally
- L41 _public prototype_ `u32 GetExitCode() const;` — Exit code of process. Will return ~0u if not finished or default error
- L42 _public prototype_ `bool HasExited() const;` — Returns true if process has exited
- L43 _public prototype_ `bool WaitForExit(u32 millisecondsTimeout) const;` — Wait for process until it exists or time reach timeout
- L44 _public prototype_ `const Vector<ProcessLogLine>& GetLogLines() const;` — Log lines produced by the process
- L45 _public prototype_ `const Vector<u8>& GetTrackedInputs() const;` — If ProcessStartInfo.trackInputs was true, this will return a buffer to wchar/char strings
- L46 _public prototype_ `const Vector<u8>& GetTrackedOutputs() const;` — If ProcessStartInfo.trackInputs was true, this will return a buffer to wchar/char strings
- L47 _public prototype_ `u64 GetTotalProcessorTime() const;` — Total used cpu time (in time units. Use TimeToMs etc)
- L48 _public prototype_ `u64 GetTotalWallTime() const;` — Total wall time (in time units. Use TimeToMs etc)
- L49 _public prototype_ `u64 GetPeakMemory() const;` — Peak memory usage (in bytes)
- L50 _public prototype_ `bool Cancel() const;` — Request to cancel process. Returns false if failed to cancel (might be at the end of exiting process)
- L51 _public prototype_ `const tchar* GetExecutingHost() const;` — Host that is executing process.
- L52 _public prototype_ `bool IsRemote() const;` — Returns true if process is a remote process
- L53 _public prototype_ `ProcessExecutionType GetExecutionType() const;` — Returns execution type
- L55 _public prototype_ `void TraverseOutputFiles(const Function<void(StringView file)>& func) const;` — Traverse output files.
- L57 _public prototype_ `ProcessHandle();`
- L58 _public prototype_ `ProcessHandle(const ProcessHandle& o);`
- L59 _public prototype_ `ProcessHandle(ProcessHandle&& o) noexcept;`
- L60 _public prototype_ `ProcessHandle& operator=(const ProcessHandle& o);`
- L61 _public prototype_ `ProcessHandle& operator=(ProcessHandle&& o) noexcept;`
- L62 _public prototype_ `~ProcessHandle();`
- L63 _public function_ `inline bool operator==(const ProcessHandle& o) const`
- L64 _public function_ `inline u64 GetHash() const`
- L66 _public prototype_ `ProcessHandle(Process* process);`
- L68 _private member_ `Process* m_process;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace uba`
- L17 _variable_ `constexpr u32 ProcessCancelExitCode = 99999;` (scope `uba`) — Exit code returned by ProcessHandle.GetExitCode() if build was cancelled

### `Source/Programs/UnrealBuildAccelerator/Common/Public/UbaProcessStartInfo.h` (Public)


#### struct `uba::ProcessStartInfo`  
`struct ProcessStartInfo`  
_L15-51_
- L17 _public prototype_ `ProcessStartInfo();`
- L18 _public prototype_ `~ProcessStartInfo();`
- L19 _public prototype_ `ProcessStartInfo(const ProcessStartInfo&);`
- L21 _public prototype_ `const tchar* GetDescription() const;` — Use this instead since it will use application name if description is not set
- L23 _public member_ `const tchar* application = TC("");` — Application name, cl.exe etc. Use full path
- L24 _public member_ `const tchar* arguments = TC("");` — Arguments. Should not include application name
- L25 _public member_ `const tchar* workingDir = TC("");` — Working directory. Use full path
- L26 _public member_ `const tchar* description = TC("");` — Description. Used for on-screen logging and log file names if session.logToFile is set but logFile is ""
- L27 _public member_ `const tchar* logFile = TC("");` — Log file. If set, will always log. If not full path the session log dir will be prepended.
- L28 _public member_ `u32 priorityClass = ProcessPriority_Normal;` — Priority of process.
- L29 _public member_ `bool trackInputs = false;` — Track all files read. Can read result in ProcessHandle.GetTrackedInputs()
- L30 _public member_ `bool useCustomAllocator = true;` — Disable detouring of allocator inside processes. If Session.disableCustomAllocator is false this will be overridden
- L31 _public member_ `bool writeOutputFilesOnFail = false;` — If set to true, output files will be written to disk regardless if process succeeds or not
- L32 _public member_ `const tchar* breadcrumbs = TC("");` — If not empty, write additional information to the UBA trace file
- L33 _public member_ `bool startSuspended = false;` — Start process suspended.. a bit internal atm and only supported on windows
- L34 _public member_ `bool reportAllExceptions = false;` — Report all SEH exceptions happening in the process regardless if they are handled or not
- L35 _public member_ `bool expanded = false;` — Internal: set to true by ProcessStartInfoHolder::Expand so subsequent Expand calls are no-ops. Lives on the base struct so it survives slicing via ProcessStartInfoHolder's conversion constructor (which copies the base via *(ProcessStartInfo*)this = si).
- L37 _public member_ `RootsHandle rootsHandle = 0;` — Handle if using vfs. Handle is generated through Session::RegisterRoots
- L39 _public typedef_ `using LogLineCallback = void(void* userData, const tchar* line, u32 length, LogEntryType type);`
- L40 _public member_ `LogLineCallback* logLineFunc = nullptr;` — Callback for when log entries happens
- L41 _public member_ `void* logLineUserData = nullptr;` — User data provided to logLine callback
- L43 _public typedef_ `using ExitedCallback = void(void* userData, const ProcessHandle&, ProcessExitedResponse&);`
- L44 _public member_ `ExitedCallback* exitedFunc = nullptr;` — Callback for when process is done (it has already exited)
- L45 _public member_ `void* userData = nullptr;` — User data provided to exit and predicted memory callbacks
- L47 _public member_ `const tchar* overlayFiles = TC("");` — Semi colon separated string containing paths to overlay files (files that are only visible to this process)
- L49 _public member_ `const ApplicationRules* rules = nullptr;` — Internal use (for now)
- L50 _public member_ `int uiLanguage = 1033;` — Internal use

#### enum `uba::ProcessExitedResponse`  
`enum ProcessExitedResponse : u8`  
_L53-58_
- L55 _public enumerator_ `ProcessExitedResponse_None`
- L56 _public enumerator_ `ProcessExitedResponse_RerunLocal`
- L57 _public enumerator_ `ProcessExitedResponse_RerunNative`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace uba`
- L13 _typedef_ `using RootsHandle = u64;` (scope `uba`)

### `Source/Programs/UnrealBuildAccelerator/Common/Public/UbaProcessStartInfoHolder.h` (Public)


#### struct `uba::ProcessStartInfoHolder`  
`struct ProcessStartInfoHolder : public ProcessStartInfo`  
_L25-152_
- inherits: `ProcessStartInfo`
- L27 _public prototype_ `ProcessStartInfoHolder() = default;`
- L29 _public function_ `ProcessStartInfoHolder(const ProcessStartInfo& si)`
- L59 _public function_ `void Write(BinaryWriter& writer, const StringView& applicationOverride)`
- L76 _public function_ `void Read(BinaryReader& reader)`
- L105 _public function_ `ProcessStartInfoHolder(const ProcessStartInfoHolder& o)`
- L110 _public function_ `void operator=(const ProcessStartInfoHolder& o)`
- L138 _public prototype_ `bool Expand();`
- L140 _public prototype_ `void Apply(const Config& config, const uba::tchar* configTable = TC(""));`
- L142 _public member_ `TString descriptionStr;`
- L143 _public member_ `TString applicationStr;`
- L144 _public member_ `TString argumentsStr;`
- L145 _public member_ `TString workingDirStr;`
- L146 _public member_ `TString logFileStr;`
- L147 _public member_ `TString breadcrumbsStr;`
- L148 _public member_ `TString overlayFilesStr;`
- L149 _public member_ `float weight = 1.0f;`
- L151 _public prototype_ `bool InternalExpand(const tchar* firstArgBegin, const tchar* firstArgEnd);`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace uba`
- L14 _function_ `inline void FixFileName(StringBufferBase& out, const tchar* fileName, const tchar* workingDir)` (scope `uba`)

### `Source/Programs/UnrealBuildAccelerator/Common/Public/UbaRootPaths.h` (Public)


#### class `uba::RootPaths`  
`class RootPaths`  
_L12-55_
- L16 _public prototype_ `bool RegisterRoot(Logger& logger, const tchar* rootPath, bool includeInKey = true, u8 id = 0);`
- L17 _public prototype_ `bool RegisterSystemRoots(Logger& logger, u8 startId = 0);`
- L18 _public prototype_ `bool RegisterIgnoredRoot(Logger& logger, const tchar* rootPath);`
- L20 _public prototype_ `bool IsEmpty() const;`
- L30 _public prototype_ `const Root* FindRoot(const StringView& path) const;`
- L31 _public prototype_ `const TString& GetRoot(u32 index) const;`
- L33 _public prototype_ `TString GetAllRoots() const;`
- L36 _public prototype_ `template<typename CharType, typename Func> bool NormalizeString(Logger& logger, const CharType* str, u64 strLen, const Func& func, bool allowPathsWithoutRoot, const tchar* hint, const tchar* hint2 = TC("")) const;`
- L38 _public prototype_ `CasKey NormalizeAndHashFile(Logger& logger, const tchar* filename, bool warnOnFileNotFound = false) const;`
- L40 _public member_ `static constexpr u8 RootStartByte = ' ';`
- L49 _private prototype_ `bool InternalRegisterRoot(Logger& logger, Roots& roots, const tchar* rootPath, bool includeInKey, u8 id);`
- L50 _private prototype_ `bool InternalRegisterRoot2(Logger& logger, Roots& roots, const tchar* rootPath, bool includeInKey, u8 index);`
- L51 _private prototype_ `const Root* InternalFindRoot(const Roots& roots, const StringView& path) const;`
- L53 _private member_ `Roots m_roots;`
- L54 _private member_ `Roots m_ignoredRoots;`
- L60 _function_ `template<typename CharType, typename Func> bool RootPaths::NormalizeString(Logger& logger, const CharType* str, u64 strLen, const Func& func, bool allowPathsWithoutRoot, const tchar* hint, const tchar* hint2) const`

#### struct `uba::RootPaths::Root`  
`struct Root`  
_L22-28_
- L24 _public member_ `TString path;`
- L25 _public member_ `StringKey shortestPathKey;`
- L26 _public member_ `u8 index;`
- L27 _public member_ `bool includeInKey;`

#### struct `uba::RootPaths::Roots`  
`struct Roots : Vector<Root>`  
_L43-47_
- inherits: `Vector<Root>`
- L45 _public member_ `u32 shortestRoot = 0;`
- L46 _public member_ `u32 longestRoot = 0;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace uba`
- L10 _variable_ `static constexpr u32 PathsPerRoot = IsWindows ? 4u : 1;` (scope `uba`)

### `Source/Programs/UnrealBuildAccelerator/Common/Public/UbaScheduler.h` (Public)


#### struct `uba::SchedulerCreateInfo`  
`struct SchedulerCreateInfo`  
_L27-55_
- L29 _public function_ `SchedulerCreateInfo(SessionServer& s) : session(s)`
- L31 _public prototype_ `void Apply(const Config& config);`
- L33 _public member_ `SessionServer& session;`
- L34 _public member_ `CacheClient** cacheClients = nullptr;` — Set cache clients for scheduler to use when building
- L35 _public member_ `u32 cacheClientCount = 0;`
- L36 _public member_ `u32 maxLocalProcessors = ~0u;` — Max local processors to use. ~0u means it will use all processors
- L37 _public member_ `u32 maxParallelCacheQueries = 16u;` — Max number of parallel cache queries allowed
- L38 _public member_ `bool enableProcessReuse = false;` — If this is true, the system will allow processes to be reused when they're asking for it.
- L39 _public member_ `bool forceRemote = false;` — Force all processes that can run remotely to run remotely.
- L40 _public member_ `bool forceNative = false;` — Force all processes to run native (not detoured)
- L41 _public member_ `bool writeToCache = false;` — Set to true in combination with setting cacheClient to populate cache
- L42 _public member_ `bool useThreadToExitRemoteProcess = false;` — Set this to true to move exit process call from job to thread.
- L43 _public member_ `bool memWatchdog = false;` — Will watch memory and throttle/kill processes if needed
- L44 _public member_ `bool writeTrackedInputs = false;` — Set to true to write out log files with tracked inputs
- L45 _public member_ `bool deferRemoteCapableProcesses = false;` — Set to true to have local session first pick local-only processes
- L46 _public member_ `bool enableSpeculativeCacheTest = false;` — Set to true to allow cache testing of a process before its dependencies have finished downloading. Requires CacheClient support for speculative CAS keys to be correct.
- L47 _public member_ `bool traceDetails = false;` — Show details of scheduler states in visualizer
- L48 _public member_ `bool leakMemoryAtShutdown = false;`
- L49 _public member_ `u32 maxRacingPercent = 0u;` — If processor weights go below this percent, then we will start filling up with racing processes
- L50 _public member_ `u8 memTracingLevel = 0;`
- L51 _public member_ `u8 memStartWaitPercent = 85;` — When memory usage goes above this percent, no new processes will be spawned until back below
- L52 _public member_ `u8 memStartKillPercent = 95;` — When memory usage goes above this percent, newest processes will be killed to bring it back below
- L53 _public member_ `u32 memPagefileActivityThreshold = 0;` — When page file activity goes over this number between each watchdog update we start killing processes. 0=disabled
- L54 _public member_ `ConfigTable* processConfigs = nullptr;`

#### struct `uba::EnqueueProcessInfo`  
`struct EnqueueProcessInfo`  
_L59-88_
- L61 _public function_ `EnqueueProcessInfo(const ProcessStartInfo& i) : info(i)`
- L63 _public member_ `const ProcessStartInfo& info;`
- L65 _public member_ `float weight = 1.0f;` — Weight of process. This is used towards max local processors. If a process is multithreaded it is likely it's weight should be more than 1.0
- L66 _public member_ `bool canDetour = true;` — If true, uba will detour the process. If false it will just create pipes for std out and then run the process as-is.
- L67 _public member_ `bool canExecuteRemotely = true;` — If true, this process can run on other machines, if false it will always be executed locally
- L68 _public member_ `bool canCrossArchitecture = false;` — If true, this process can run on other architecture
- L69 _public member_ `bool canCrossPlatform = false;` — If true, this process can run on other platform.
- L71 _public member_ `const void* knownInputs = nullptr;` — knownInputs is a memory block with null terminated tchar strings followed by an empty null terminated string to end.
- L72 _public member_ `u32 knownInputsBytes = 0;` — knownInputsBytes is the total size in bytes of knownInputs
- L73 _public member_ `u32 knownInputsCount = 0;` — knownInputsCount is the number of strings in the memory block
- L75 _public member_ `const void* knownOutputs = nullptr;` — knownOutputs is a memory block with null terminated tchar strings followed by an empty null terminated string to end.
- L76 _public member_ `u32 knownOutputsBytes = 0;` — knownOutputsBytes is the total size in bytes of knownOutputs
- L77 _public member_ `u32 knownOutputsCount = 0;` — knownOutputsCount is the number of strings in the memory block
- L79 _public member_ `const u32* dependencies = nullptr;` — An array of u32 holding indicies to processes this process depends on. Index is a rolling number returned by EnqueueProcess
- L80 _public member_ `u32 dependencyCount = 0;` — Number of elements in dependencies
- L82 _public member_ `u32 cacheBucketId = 0;` — Bucket that cache should be fetched from. Zero means that it will not fetch anything
- L83 _public member_ `u64 memoryGroupId = 0;` — Group that calculates average of memory usage.
- L85 _public member_ `u64 predictedMemoryUsage = 0;` — If zero, this will not be used for memory predictions
- L87 _public member_ `bool skipAsSuccessWhenScheduled = false;` — If set to true, then this process will be seen as successful straight away when scheduled

#### struct `uba::SchedulerStats`  
`struct SchedulerStats`  
_L106-121_
- L119 _public member_ `u32 activeCacheQueries = 0;`
- L120 _public member_ `u32 activeCacheDownloads = 0;`

#### class `uba::Scheduler`  
`class Scheduler`  
_L125-356_
- L128 _public prototype_ `Scheduler(const SchedulerCreateInfo& info);`
- L129 _public prototype_ `~Scheduler();`
- L131 _public prototype_ `void Start();` — Start scheduler thread. Should be called before server starts listen to connections if using remote help
- L132 _public prototype_ `void Stop();` — Will wait on all active processes and then exit.
- L133 _public prototype_ `void Cancel();` — Cancel and wait
- L134 _public prototype_ `void SetMaxLocalProcessors(u32 maxLocalProcessors);` — Set max local processes
- L135 _public prototype_ `void SetAllowDisableRemoteExecution(bool allow);` — Allow scheduler to tell clients to disconnect early if running out of processes
- L137 _public prototype_ `u32 EnqueueProcess(const EnqueueProcessInfo& info);` — Returns index of process. Index is a rolling number
- L139 _public prototype_ `u32 EnqueueSuspendedProcess();` — Can be used to put entries in the queue early in order to calculate process info afterwards
- L140 _public prototype_ `void ResumeQueuedProcess(u32 index, const EnqueueProcessInfo& info);` — Resume process queued with EnqueueSuspended
- L142 _public prototype_ `u32 GetTotalProcesses();`
- L143 _public prototype_ `void GetStats(u32& outQueued, u32& outActiveLocal, u32& outActiveRemote, u32& outFinished);`
- L144 _public prototype_ `void GetStats(SchedulerStats& outStats);`
- L145 _public prototype_ `void GetResults(u32& outSucceeded, u32& outFailed, u32& outSkipped);`
- L147 _public prototype_ `bool IsEmpty();` — Returns true if scheduler is entirely empty.. as in no processes are left in the system
- L149 _public prototype_ `bool EnqueueFromFile(const tchar* yamlFilename, const Function<void(EnqueueProcessInfo&)>& enqueued = {});` — Enqueue actions from file. Example of format of file is at the end of this file
- L150 _public prototype_ `bool EnqueueFromSpecialJson(const tchar* jsonFilename, const tchar* workingDir, const tchar* description, RootsHandle rootsHandle, void* userData = nullptr);`
- L152 _public prototype_ `void SetProcessFinishedCallback(const Function<void(const ProcessHandle&)>& processFinished);` — Set callback
- L153 _public prototype_ `void SetPredictedMemoryCallback(const Function<u64(void* userData)>& predictedMemory);` — Set callback queried per process (via its userData) to obtain an up-to-date memory estimate in bytes (0 means unknown). Called from the scheduler thread while it holds internal locks, so it must return quickly and must not call back into the scheduler.
- L155 _public function_ `SessionServer& GetSession()`
- L156 _public function_ `u32 GetCacheClientCount()`
- L157 _public function_ `CacheClient& GetCacheClient(u32 index)`
- L159 _public prototype_ `u32 GetProcessCountThatCanRunRemotelyNow();`
- L160 _public prototype_ `void GetProcessWeightThatCanRunRemotelyNow(float& outTotal, float& outCrossArchitecture, float& outCrossPlatform);`
- L199 _private prototype_ `UBA_NOINLINE void ThreadLoop();`
- L205 _private prototype_ `ProcessEntry CreateProcessEntry(const EnqueueProcessInfo& info);`
- L206 _private prototype_ `ProcessQueue& GetReadyToRunQueue(ProcessEntry& entry);`
- L207 _private prototype_ `void AddToQueue(ProcessQueue& queue, u32 entryIndex);`
- L208 _private prototype_ `u32 PopFromQueue(ProcessQueue& queue);`
- L209 _private prototype_ `ProcessEntry* PeekFromQueue(ProcessQueue& queue);`
- L210 _private prototype_ `void EraseFromQueue(ProcessQueue& queue, u32 entryIndex);`
- L211 _private prototype_ `u32 GetQueueCount(ProcessQueue& queue);`
- L212 _private prototype_ `void ClearQueue(ProcessQueue& queue);`
- L213 _private prototype_ `void SetupDependents(ProcessEntry& entry, u32 entryIndex, const EnqueueProcessInfo& info);`
- L214 _private prototype_ `void UpdateDependents(RunStatus newRunStatus, ProcessLink* firstDependent, bool hadCacheHit);`
- L215 _private prototype_ `void UpdateSpeculativeDependentsOnCacheHit(ProcessLink* firstDependent);`
- L216 _private prototype_ `bool DrainCompleteFromCache();`
- L217 _private prototype_ `void SkipAllQueued();`
- L218 _private prototype_ `bool ProcessReturned(Process& process, bool isLocal);`
- L219 _private prototype_ `void HandleCacheMissed(u32 processIndex);`
- L220 _private prototype_ `void RemoteSlotAvailable(bool isCrossArchitecture, bool isCrossPlatform);`
- L221 _private prototype_ `void ProcessExited(ExitProcessInfo* info, const ProcessHandle& handle);`
- L222 _private prototype_ `bool CanRun();`
- L223 _private prototype_ `u32 PopProcessNoLock(bool isLocal, bool isCrossArchitecture, bool isCrossPlatform, RunStatus& outPrevStatus, bool forReuse, bool& outShouldSleep, ProcessLink*& outSkipFirstDependent);`
- L224 _private prototype_ `bool RunCacheQuery();`
- L225 _private prototype_ `bool RunQueuedProcess(bool isLocal, bool isCrossArchitecture, bool isCrossPlatform);`
- L226 _private prototype_ `bool RaceRemoteProcess();`
- L227 _private prototype_ `bool HandleGetNextProcess(Process& process, NextProcessInfo& outNextProcess, u32 prevExitCode, BinaryReader& prevStats, u32 timeoutMs);`
- L228 _private prototype_ `void ExitProcess(ExitProcessInfo& info, Process& process, u32 exitCode, bool fromCache, bool forReuse);`
- L229 _private prototype_ `void SkipProcess(ProcessStartInfo2& info);`
- L230 _private prototype_ `void UpdateStatusHitMissCount();`
- L231 _private prototype_ `void UpdateQueueCounter();`
- L232 _private prototype_ `void StatsActive(SchedulerStats& s, Category cat, int d, float w);`
- L233 _private prototype_ `void StatsReady(SchedulerStats& s, Category cat, int d, float w);`
- L234 _private prototype_ `void StatsPending(SchedulerStats& s, Category cat, int d, float w);`
- L235 _private prototype_ `void StatsRunning(SchedulerStats& s, Category cat, int d, float w);`
- L236 _private prototype_ `void TransitionStats(ProcessEntry& entry, StatsState newState, float weight);`
- L237 _private prototype_ `void FinishProcess(const ProcessHandle& handle);`
- L238 _private prototype_ `void CreateCacheInputsAndOutputs(Vector<u8>& outInputs, Vector<u8>& outOutputs, ProcessStartInfo2& info, Process& process);`
- L239 _private prototype_ `void WriteTrackedInputs(const Vector<u8>& inputs, const Vector<u8>& outputs, Process& process);`
- L240 _private prototype_ `void KillNewestLocalProcess(StringView reason);`
- L241 _private prototype_ `void NativeProcessCreated(ProcessImpl& process);`
- L242 _private prototype_ `void LocalProcessStart(ProcessStartInfo2& info);`
- L243 _private prototype_ `void UpdatePredictedMemoryUsage(ProcessStartInfo2& info);`
- L244 _private prototype_ `bool LocalProcessMemoryOkToSpawn(u32 runningLocalCount, u64 predictedMemoryUsage);`
- L245 _private prototype_ `void SetMemDelaySpawning(bool delaySpawning);`
- L246 _private prototype_ `bool LocalProcessOkToSpawn(u32 runningLocalCount, u64 predictedMemoryUsage = 0);`
- L247 _private prototype_ `void LocalProcessExit(ProcessStartInfo2& info, const ProcessHandle& handle);`
- L248 _private prototype_ `void LoadMemTrackTable();`
- L249 _private prototype_ `void SaveMemTrackTable();`
- L250 _private prototype_ `UBA_NOINLINE void ThreadMemoryCheckLoop();`
- L268 _private member_ `SessionServer& m_session;`
- L269 _private member_ `u32 m_maxLocalProcessors;`
- L270 _private member_ `float m_maxRacingWeight;`
- L271 _private member_ `u32 m_maxParallelCacheQueries;`
- L273 _private member_ `Futex m_processEntriesLock;`
- L274 _private member_ `Vector<ProcessEntry> m_processEntries;`
- L276 _private member_ `ProcessQueue m_readyToTestCache;`
- L277 _private member_ `ProcessQueue m_readyToDownloadCache;`
- L278 _private member_ `ProcessQueue m_readyToRunLocal;` — Can only run locally
- L279 _private member_ `ProcessQueue m_readyToRunRemote;` — Can run remotely on same architecture
- L280 _private member_ `ProcessQueue m_readyToRunCrossArchitecture;` — Can run remotely on a different architecture
- L281 _private member_ `ProcessQueue m_readyToRunCrossPlatform;` — Can run remotely on a different platform
- L282 _private member_ `ProcessQueue m_readyToRunCrossArchAndPlatform;` — Can run remotely on a different architecture AND platform
- L283 _private member_ `ProcessQueue m_readyToSkip;`
- L284 _private member_ `ProcessQueue m_readyToCompleteFromCache;` — Cache download done but deps were still pending; fired when last dep completes
- L286 _private member_ `Function<void(const ProcessHandle&)> m_processFinished;`
- L287 _private member_ `Function<u64(void* userData)> m_predictedMemoryFunc;`
- L289 _private member_ `Event m_updateThreadWakeup;`
- L290 _private member_ `Thread m_updateThread;`
- L292 _private member_ `Atomic<bool> m_loop = false;`
- L293 _private member_ `bool m_enableProcessReuse;`
- L294 _private member_ `bool m_forceRemote;`
- L295 _private member_ `bool m_forceNative;`
- L296 _private member_ `bool m_useThreadToExitRemoteProcess;`
- L297 _private member_ `bool m_allowDisableRemoteExecution = false;`
- L298 _private member_ `bool m_writeTrackedInputs = false;`
- L299 _private member_ `bool m_deferRemoteCapableProcesses = false;`
- L300 _private member_ `bool m_enableSpeculativeCacheTest = false;`
- L301 _private member_ `bool m_leakMemoryAtShutdown = false;`
- L302 _private member_ `bool m_traceDetails = false;`
- L303 _private member_ `bool m_cancelled = false;`
- L304 _private member_ `bool m_hadMatchingSystemRequest = false;`
- L305 _private member_ `bool m_hadCrossSystemRequest = false;`
- L306 _private member_ `ConfigTable* m_processConfigs = nullptr;`
- L308 _private member_ `Atomic<float> m_activeLocalProcessWeight = 0.0f;`
- L309 _private member_ `Atomic<float> m_activeRacingProcessWeight = 0.0f;`
- L310 _private member_ `Atomic<u32> m_getNextQueueCount = 0;`
- L312 _private member_ `SchedulerStats m_stats;`
- L314 _private member_ `Atomic<u32> m_totalProcesses = 0;` — Process count registered in to scheduler
- L315 _private member_ `Atomic<u32> m_finishedProcesses = 0;` — Processes finished (includes skipped)
- L316 _private member_ `Atomic<u32> m_errorCount = 0;`
- L317 _private member_ `Atomic<u32> m_cacheHitCount = 0;`
- L318 _private member_ `Atomic<u32> m_cacheMissCount = 0;`
- L320 _private member_ `Vector<CacheClient*> m_cacheClients;`
- L321 _private member_ `Vector<RootPaths*> m_rootPaths;`
- L322 _private member_ `bool m_writeToCache;`
- L324 _private member_ `WorkManagerImpl* m_cacheWorkManager = nullptr;`
- L325 _private member_ `List<Thread> m_finishedRemoteProcessThreads;`
- L327 _private member_ `CriticalSection m_wasReturnedLock;`
- L329 _private member_ `bool m_memWatchdog = false;`
- L330 _private member_ `Event m_memThreadEvent;`
- L331 _private member_ `Thread m_memThread;`
- L332 _private member_ `bool m_memDelaySpawning = false;`
- L333 _private member_ `Atomic<u64> m_memEstimatedUsage = 0;`
- L334 _private member_ `Atomic<u64> m_memWaitThreshold = 0;`
- L335 _private member_ `Atomic<u64> m_lastKillTime = 0;`
- L336 _private member_ `u8 m_memStartWaitPercent = 0;`
- L337 _private member_ `u8 m_memStartKillPercent = 0;`
- L338 _private member_ `u8 m_memTracingLevel = 0;`
- L339 _private member_ `u32 m_memPagefileActivityThreshold = 0;`
- L343 _private member_ `Futex m_memGroupLookupLock;`
- L344 _private member_ `UnorderedMap<u64, MemGroupStats> m_memGroupLookup;`
- L345 _private member_ `UnorderedMap<u64, MemGroupEntry> m_memGroupDb;`
- L347 _private member_ `Futex m_processesLock;`
- L349 _private member_ `UnorderedMap<StringKey, ProcessRecord> m_processes;`
- L351 _private member_ `Futex m_racingProcessesLock;`
- L352 _private member_ `List<ProcessHandle> m_racingProcesses;`
- L354 _private prototype_ `Scheduler(const Scheduler&) = delete;`
- L355 _private prototype_ `void operator=(const Scheduler&) = delete;`

#### enum `uba::Scheduler::RunStatus`  
`enum RunStatus : u8`  
_L167-175_
- L169 _public enumerator_ `RunStatus_Suspended`
- L170 _public enumerator_ `RunStatus_QueuedForRun`
- L171 _public enumerator_ `RunStatus_Running`
- L172 _public enumerator_ `RunStatus_Success`
- L173 _public enumerator_ `RunStatus_Failed`
- L174 _public enumerator_ `RunStatus_Skipped`

#### enum `uba::Scheduler::StatsState`  
`enum StatsState : u8`  
_L177-177_
- L177 _public enumerator_ `enum StatsState : u8 { StatsState_None, StatsState_Pending, StatsState_Ready, StatsState_Active }; enum CacheStatus : u8 { CacheStatus_Suspended, CacheStatus_QueuedForTest, CacheStatus_QueuedForTestSpeculative, CacheStatus_Testing,`
- L177 _public enumerator_ `enum StatsState : u8 { StatsState_None, StatsState_Pending, StatsState_Ready, StatsState_Active }; enum CacheStatus : u8 { CacheStatus_Suspended, CacheStatus_QueuedForTest, CacheStatus_QueuedForTestSpeculative, CacheStatus_Testing,`
- L177 _public enumerator_ `enum StatsState : u8 { StatsState_None, StatsState_Pending, StatsState_Ready, StatsState_Active }; enum CacheStatus : u8 { CacheStatus_Suspended, CacheStatus_QueuedForTest, CacheStatus_QueuedForTestSpeculative, CacheStatus_Testing,`
- L177 _public enumerator_ `enum StatsState : u8 { StatsState_None, StatsState_Pending, StatsState_Ready, StatsState_Active }; enum CacheStatus : u8 { CacheStatus_Suspended, CacheStatus_QueuedForTest, CacheStatus_QueuedForTestSpeculative, CacheStatus_Testing,`

#### enum `uba::Scheduler::CacheStatus`  
`enum CacheStatus : u8`  
_L179-190_
- L181 _public enumerator_ `CacheStatus_Suspended`
- L182 _public enumerator_ `CacheStatus_QueuedForTest` — not yet in any queue; blocked on deps or awaiting initial scheduling
- L183 _public enumerator_ `CacheStatus_QueuedForTestSpeculative` — in m_readyToTestCache; deps still pending (speculative start)
- L184 _public enumerator_ `CacheStatus_Testing` — test worker in flight
- L185 _public enumerator_ `CacheStatus_QueuedForDownload` — hit confirmed; in m_readyToDownloadCache
- L186 _public enumerator_ `CacheStatus_Downloading` — download worker in flight
- L187 _public enumerator_ `CacheStatus_PendingCompletion` — download done; deps still pending (will fire when last dep completes)
- L188 _public enumerator_ `CacheStatus_Success`
- L189 _public enumerator_ `CacheStatus_Failed`

#### enum `uba::Scheduler::Category`  
`enum Category : u8`  
_L192-197_
- L195 _public enumerator_ `UBA_PROCESS_CATEGORIES #undef UBA_PROCESS_CATEGORY`

#### struct `uba::Scheduler::ProcessEntry`  
`struct ProcessEntry`  
_L252-264_
- L254 _public member_ `ProcessStartInfo2* info;`
- L255 _public member_ `ProcessLink* firstDependent;`
- L256 _public member_ `u32 dependencyCount;`
- L257 _public member_ `u32 speculativeDependencyCount;`
- L258 _public member_ `CacheStatus cacheStatus;`
- L259 _public member_ `RunStatus runStatus;`
- L260 _public member_ `StatsState statsState;`
- L261 _public member_ `Category category;`
- L262 _public member_ `bool shouldSkip;`
- L263 _public member_ `bool canDetour;`

#### struct `uba::Scheduler::ProcessQueue`  
`struct ProcessQueue : Set<u32>`  
_L266-266_
- inherits: `Set<u32>`
- L266 _public member_ `struct ProcessQueue : Set<u32> { Futex lock; };`

#### struct `uba::Scheduler::ProcessRecord`  
`struct ProcessRecord`  
_L348-348_
- L348 _public member_ `struct ProcessRecord { ProcessImpl& process; ExitProcessInfo* ep; };`
- L348 _public member_ `struct ProcessRecord { ProcessImpl& process; ExitProcessInfo* ep; };`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace uba`
- L92 _macro_ `#define UBA_PROCESS_CATEGORIES \`
- L108 _macro_ `#define UBA_PROCESS_CATEGORY(cat) \`
- L194 _macro_ `#define UBA_PROCESS_CATEGORY(cat) Category_##cat,`

### `Source/Programs/UnrealBuildAccelerator/Common/Public/UbaSentry.h` (Public)


#### Free symbols / members of external scopes

- L4 _macro_ `#define SENTRY_BUILD_STATIC 1`
- L6 _macro_ `#define UBA_SENTRY_INFO(...) do { if (x) break; StringBuffer<> _buf; _buf.Appendf(__VA_ARGS__); sentry_capture_event(sentry_value_new_message_event(SENTRY_LEVEL_INFO, "custom", _buf.data); } while(false)`
- L8 _macro_ `#define UBA_SENTRY_INFO(...)`

### `Source/Programs/UnrealBuildAccelerator/Common/Public/UbaSession.h` (Public)


#### class `uba::Session`  
`class Session : public DirectoryTableHolder`  
_L67-421_
- inherits: `DirectoryTableHolder`
- L70 _public prototype_ `ProcessHandle RunProcess(const ProcessStartInfo& startInfo, bool async = true, bool enableDetour = true);` — Run process. if async is false it will not return until process is done
- L71 _public prototype_ `void CancelAllProcessesAndWait(bool terminate = true);` — Cancel all processes and wait for them to go away
- L72 _public prototype_ `void CancelAllProcesses();` — Cancel all processes
- L74 _public prototype_ `void PrintSummary(Logger& logger);` — Print summary stats of session
- L75 _public prototype_ `bool RegisterVirtualFile(const tchar* filePath, const tchar* sourceFile, u64 sourceOffset, u64 sourceSize);`
- L76 _public prototype_ `bool CreateVirtualFile(const tchar* filePath, const void* memory, u64 memorySize, bool transient, bool registerToDir = true);`
- L77 _public prototype_ `bool DeleteVirtualFile(const tchar* filePath, bool registerToDir);`
- L79 _public prototype_ `RootsHandle RegisterRoots(const void* rootsData, uba::u64 rootsDataSize);`
- L81 _public typedef_ `using CustomServiceFunction = Function<u32(Process& handle, const void* recv, u32 recvSize, void* send, u32 sendCapacity)>;`
- L82 _public prototype_ `void RegisterCustomService(CustomServiceFunction&& function);` — Register a custom service (that can be communicated with from the remote agents)
- L84 _public typedef_ `using GetNextProcessFunction = Function<bool(Process& handle, NextProcessInfo& outNextProcess, u32 prevExitCode, BinaryReader& prevStats, u32 timeoutMs, bool& outShouldExit)>;`
- L85 _public prototype_ `void RegisterGetNextProcess(GetNextProcessFunction&& function);` — Register a custom service (that can be communicated with from the remote agents)
- L87 _public prototype_ `bool AddEnvironmentVariable(const tchar* name, const tchar* value);`
- L89 _public prototype_ `bool GetOutputFileSize(u64& outSize, const tchar* filePath);` — Available if ShouldWriteToDisk is false
- L90 _public prototype_ `bool GetOutputFileData(void* outData, const tchar* filePath, bool deleteInternalMapping);` — Available if ShouldWriteToDisk is false
- L91 _public prototype_ `bool WriteOutputFile(const tchar* filePath, bool deleteInternalMapping);` — Available if ShouldWriteToDisk is false
- L93 _public prototype_ `const tchar* GetId();` — Id for session. Will be "yymmdd_hhmmss" unless SessionCreateInfo.useUniqueId is set to false
- L94 _public prototype_ `u32 GetActiveProcessCount();` — Current active processes running inside session
- L95 _public prototype_ `Storage& GetStorage();` — Storage (only used when remote machines are connected)
- L96 _public prototype_ `MutableLogger& GetLogger();` — Logger used for logging
- L97 _public prototype_ `LogWriter& GetLogWriter();` — LogWriter used by logger
- L98 _public prototype_ `WorkManager& GetWorkManager();`
- L99 _public prototype_ `Trace& GetTrace();` — Trace written to be session
- L100 _public prototype_ `SearchPathCache& GetSearchPathCache();`
- L101 _public prototype_ `const ApplicationRules* GetRules(const ProcessStartInfo& si);` — Get application rules used for process
- L102 _public prototype_ `const tchar* GetTempPath();` — Path for temp files used for current session
- L103 _public prototype_ `const tchar* GetRootDir();` — Root dir for session files
- L104 _public prototype_ `const tchar* GetSessionDir();` — Session dir
- L105 _public function_ `bool ShouldStoreIntermediateFilesCompressed() const`
- L106 _public function_ `bool WritePlaceholders() const`
- L107 _public function_ `bool HasDetailedtrace() const`
- L108 _public function_ `bool AllowKeepFilesInMemory() const`
- L111 _public prototype_ `bool SaveSnapshotOfTrace();` — Will write current state of trace directly to disk
- L113 _public prototype_ `virtual ~Session();`
- L115 _public prototype_ `u32 CreateProcessId();`
- L117 _public prototype_ `bool VirtualizePath(StringBufferBase& inOut, RootsHandle rootsHandle);`
- L118 _public prototype_ `bool DevirtualizePath(StringBufferBase& inOut, RootsHandle rootsHandle, bool reportError = true);`
- L119 _public prototype_ `bool DevirtualizeString(TString& inOut, RootsHandle rootsHandle, bool allowPathsWithoutRoot, const tchar* hint = TC(""));`
- L120 _public prototype_ `bool PopulateLocalToIndexRoots(RootPaths& out, RootsHandle rootsHandle);`
- L122 _public prototype_ `bool PopulateOverlayFiles(DirectoryTableOverlay& overlay, StringView overlayFiles);`
- L124 _public prototype_ `void FlushDeadProcesses(bool reapZombies);`
- L126 _public prototype_ `bool UpdateDirTableSnapshot(bool force);`
- L128 _public prototype_ `const tchar* FixLogFile(const tchar* logFile, StringBufferBase& temp, const tchar* processArguments, u32 processId);`
- L129 _public prototype_ `void SetProcessAsIdle(ProcessImpl& process, BinaryReader& prevStats, u32 prevExitCode);`
- L132 _protected prototype_ `Session(const SessionCreateInfo& info, const tchar* logPrefix, bool runningRemote, WorkManager& workManager);`
- L133 _protected prototype_ `bool Create(const SessionCreateInfo& info);`
- L135 _protected prototype_ `void ValidateStartInfo(const ProcessStartInfo& startInfo);`
- L136 _protected prototype_ `ProcessHandle InternalRunProcess(const ProcessStartInfo& startInfo, bool async, ProcessImpl* parent, bool enableDetour, void* userData);`
- L137 _protected prototype_ `void ProcessAdded(Process& process, u32 sessionId);`
- L138 _protected prototype_ `void ProcessExited(ProcessImpl& process, u64 executionTime);`
- L139 _protected prototype_ `void PrintProcessStats(ProcessStats& stats, const tchar* logName);`
- L140 _protected prototype_ `u32 GetFileMappingSize();`
- L141 _protected prototype_ `u32 GetMemoryMapAlignment(const StringView& fileName) const;`
- L142 _protected prototype_ `u32 GetMemoryMapAlignment(const StringView& fileName, bool runningRemote) const;`
- L144 _protected prototype_ `SessionStats& Stats();`
- L148 _protected prototype_ `bool GetBinaryModules(BinaryAndDeps& out, const tchar* application, bool isLinuxBinary);`
- L149 _protected prototype_ `void Free(BinaryAndDeps& v);`
- L150 _protected prototype_ `bool IsRarelyRead(ProcessImpl& process, const StringView& fileName) const;`
- L151 _protected prototype_ `bool IsMaybeReadAfterWritten(ProcessImpl& process, const StringView& fileName) const;`
- L152 _protected prototype_ `bool IsKnownSystemFile(const tchar* applicationName);`
- L153 _protected prototype_ `virtual bool IsInTemp(StringView path) override;`
- L154 _protected prototype_ `virtual bool ShouldWriteToDisk(StringView fileName) override;`
- L155 _protected prototype_ `virtual void InvalidateCachedFileInfo(const StringKey& fileNameKey);`
- L157 _protected prototype_ `u32 AddFileMapping(StringKey fileNameKey, const tchar* fileName, const tchar* newFileName, u64 fileSize = InvalidValue);`
- L161 _protected prototype_ `bool GetOrCreateMemoryMapFromFile(MemoryMap& out, StringKey fileNameKey, const tchar* fileName, bool isCompressedCas, u64 alignment, const tchar* hint, ProcessImpl* requestingProcess, bool canBeFreed);`
- L162 _protected prototype_ `bool GetOrCreateMemoryMapFromStorage(MemoryMap& out, StringKey fileNameKey, const tchar* fileName, const CasKey& casKey, u64 alignment);`
- L163 _protected prototype_ `void ThreadGcFileMappings();`
- L165 _protected prototype_ `virtual bool PrepareProcess(ProcessImpl& process, bool isChild, StringBufferBase& outRealApplication, const tchar*& outRealWorkingDir);`
- L166 _protected prototype_ `virtual Vector<tchar>& GetProcessEnvironmentVariables();`
- L167 _protected prototype_ `virtual void PrintSessionStats(Logger& logger);`
- L169 _protected prototype_ `bool RegisterVirtualFileInternal(const StringKey& fileNameKey, const StringView& filePath, const tchar* sourceFile, u64 sourceOffset, u64 sourceSize);`
- L170 _protected prototype_ `bool CreateVirtualFileInternal(const StringKey& fileNameKey, const StringView& filePath, const void* memory, u64 memorySize, bool transient);`
- L171 _protected prototype_ `bool RegisterVirtualFileInternal(const StringKey& fileNameKey, const StringView& filePath, SharedMemoryHandle memoryHandle, u64 mappingSize, u64 mappingOffset, bool transient);`
- L173 _protected prototype_ `virtual bool GetOutputFileSizeInternal(u64& outSize, const StringKey& fileNameKey, StringView filePath);`
- L174 _protected prototype_ `virtual bool GetOutputFileDataInternal(void* outData, const StringKey& fileNameKey, StringView filePath, bool deleteInternalMapping);`
- L175 _protected prototype_ `virtual bool WriteOutputFileInternal(const StringKey& fileNameKey, StringView filePath, bool deleteInternalMapping);`
- L177 _protected prototype_ `virtual bool ProcessThreadStart(ProcessImpl& process);`
- L178 _protected prototype_ `virtual bool ProcessNativeCreated(ProcessImpl& process);`
- L179 _protected prototype_ `virtual bool ProcessCancelled(ProcessImpl& process);`
- L180 _protected prototype_ `virtual bool GetInitResponse(InitResponse& out, const InitMessage& msg);`
- L181 _protected prototype_ `virtual bool CreateFile(CreateFileResponse& out, const CreateFileMessage& msg);`
- L182 _protected prototype_ `virtual bool CreateFileForRead(CreateFileResponse& out, TrackWorkScope& tws, StringView fileName, StringKey fileNameKey, ProcessImpl& process, const ApplicationRules& rules);`
- L183 _protected prototype_ `virtual bool CloseFile(CloseFileResponse& out, const CloseFileMessage& msg);`
- L184 _protected prototype_ `virtual bool DeleteFile(DeleteFileResponse& out, const DeleteFileMessage& msg);`
- L185 _protected prototype_ `virtual bool CopyFile(CopyFileResponse& out, const CopyFileMessage& msg);`
- L186 _protected prototype_ `virtual bool MoveFile(MoveFileResponse& out, const MoveFileMessage& msg);`
- L187 _protected prototype_ `virtual bool Chmod(ChmodResponse& out, const ChmodMessage& msg);`
- L188 _protected prototype_ `virtual bool Symlink(SymlinkResponse& out, const SymlinkMessage& msg);`
- L189 _protected prototype_ `virtual bool CreateDirectory(CreateDirectoryResponse& out, const CreateDirectoryMessage& msg);`
- L190 _protected prototype_ `virtual bool RemoveDirectory(RemoveDirectoryResponse& out, const RemoveDirectoryMessage& msg);`
- L191 _protected prototype_ `virtual bool GetFullFileName(GetFullFileNameResponse& out, const GetFullFileNameMessage& msg);`
- L192 _protected prototype_ `virtual bool GetLongPathName(GetLongPathNameResponse& out, const GetLongPathNameMessage& msg);`
- L193 _protected prototype_ `virtual bool GetListDirectoryInfo(ListDirectoryResponse& out, const StringView& dirName, const StringKey& dirKey, DirectoryTableOverlay* overlay);`
- L194 _protected prototype_ `virtual bool WriteFilesToDisk(ProcessImpl& process, WrittenFile** files, u32 fileCount);`
- L195 _protected prototype_ `virtual bool AllocFailed(Process& process, const tchar* allocType, u32 error);`
- L196 _protected prototype_ `virtual bool GetNextProcess(Process& process, bool& outNewProcess, bool& outShouldExit, NextProcessInfo& outNextProcess, u32 prevExitCode, BinaryReader& prevStats, u32 timeoutMs);`
- L197 _protected prototype_ `virtual bool CustomMessage(Process& process, BinaryReader& reader, BinaryWriter& writer);`
- L198 _protected prototype_ `virtual bool SHGetKnownFolderPath(Process& process, BinaryReader& reader, BinaryWriter& writer);`
- L199 _protected prototype_ `virtual bool HostRun(BinaryReader& reader, BinaryWriter& writer);`
- L200 _protected prototype_ `virtual bool GetSymbols(const tchar* application, bool isLinux, bool isArm, BinaryReader& reader, BinaryWriter& writer);`
- L201 _protected prototype_ `virtual bool CheckRemapping(ProcessImpl& process, BinaryReader& reader, BinaryWriter& writer);`
- L202 _protected prototype_ `virtual bool RunSpecialProgram(ProcessImpl& process, BinaryReader& reader, BinaryWriter& writer);`
- L203 _protected prototype_ `virtual bool FlushWrittenFiles(ProcessImpl& process);`
- L204 _protected prototype_ `virtual bool UpdateEnvironment(ProcessImpl& process, const StringView& reason, bool resetStats);`
- L205 _protected prototype_ `virtual bool LogLine(ProcessImpl& process, const tchar* line, LogEntryType logType);`
- L206 _protected prototype_ `virtual void EmergencyShutdown();`
- L208 _protected member_ `static constexpr CasKey CasKeyIsDirectory = { ~u64(0), ~u64(0), ~u32(0) };`
- L210 _protected prototype_ `void RemoveWrittenFile(ProcessImpl& process, const StringKey& fileKey);`
- L211 _protected prototype_ `bool WriteFileToDisk(ProcessImpl& process, WrittenFile& file);`
- L212 _protected prototype_ `bool WriteMemoryToDisk(FileAccessor& destinationFile, const void* fileMem, u64 fileSize, StringBufferBase* outWriteMode);`
- L213 _protected prototype_ `bool GetFileMemory(const Function<bool(const void*, u64)>& func, const StringKey& fileNameKey, StringView filePath, bool deleteInternalMapping);`
- L214 _protected prototype_ `void AddEnvironmentVariableNoLock(StringView key, StringView value);`
- L215 _protected prototype_ `bool CopyImports(BinaryAndDeps& out, const tchar* library, tchar* applicationDir, tchar* applicationDirEnd, UnorderedSet<TString>& handledImports, const tchar* const* loaderPaths, bool isLinuxBinary, const tchar* hint);`
- L216 _protected prototype_ `bool CreateProcessJobObject();`
- L217 _protected prototype_ `void GetSessionInfo(StringBufferBase& out);`
- L219 _protected prototype_ `bool HasVfs(RootsHandle handle) const;`
- L220 _protected prototype_ `RootsHandle WithVfs(RootsHandle key, bool vfs) const;`
- L222 _protected prototype_ `const RootsEntry* GetRootsEntry(RootsHandle rootsHandle);`
- L223 _protected prototype_ `void PopulateRootsEntry(RootsEntry& entry, const void* rootsData, uba::u64 rootsDataSize);`
- L225 _protected prototype_ `u32 PopTempDirectory(TString& out);`
- L226 _protected prototype_ `void PushTempDirectory(u32 id);`
- L227 _protected prototype_ `void ClearTempDirectory(u32 id);`
- L229 _protected prototype_ `bool CreateSnapshot(u32 currSize);`
- L230 _protected prototype_ `DirTableSnapshot* ReferenceDirTableSnapshot();`
- L231 _protected prototype_ `void ReleaseDirTableSnapshot(DirTableSnapshot* snapshot);`
- L233 _protected prototype_ `bool ExtractSymbolsFromObjectFile(ProcessImpl& process, const tchar* fileName, const tchar* backedName, u64 fileSize, SharedMemoryHandle memoryHandle, u32 attributes);`
- L234 _protected prototype_ `bool ExtractSymbolsForProcessTree(ProcessImpl& rootProcess);`
- L235 _protected prototype_ `bool DevirtualizeDepsFile(RootsHandle rootsHandle, MemoryBlock& destData, const void* sourceData, u64 sourceSize, bool escapeSpaces, const tchar* hint);`
- L238 _protected prototype_ `bool TryPatchBinary(StringBufferBase& out, StringView in);`
- L241 _protected prototype_ `void TraceWrittenFile(u32 processId, const StringView& file, u64 size = 0);`
- L243 _protected prototype_ `void RunDependencyCrawler(ProcessImpl& process);`
- L244 _protected prototype_ `bool OpenFileForDependencyCrawler(TrackWorkScope& tracker, StringView fileName, const DependencyCrawler::AccessFileFunc& func, bool& stopCrawling, ProcessHandle& ph, bool isLinkCrawler, const ApplicationRules& rules);`
- L246 _protected member_ `Storage& m_storage;`
- L247 _protected member_ `SharedMemoryAllocator& m_sharedMemory;`
- L248 _protected member_ `WorkManager& m_workManager;`
- L250 _protected member_ `StringBuffer<32> m_id;`
- L251 _protected member_ `StringBuffer<MaxPath> m_rootDir;`
- L252 _protected member_ `StringBuffer<MaxPath> m_sessionDir;`
- L253 _protected member_ `StringBuffer<MaxPath> m_sessionBinDir;`
- L254 _protected member_ `StringBuffer<MaxPath> m_sessionOutputDir;`
- L255 _protected member_ `StringBuffer<MaxPath> m_sessionLogDir;`
- L256 _protected member_ `StringBuffer<MaxPath> m_systemPath;`
- L257 _protected member_ `StringBuffer<MaxPath> m_tempPath;`
- L260 _protected member_ `bool m_allowCustomAllocator;`
- L261 _protected member_ `bool m_allowLazyCopyOnWrite;`
- L262 _protected member_ `bool m_allowMemoryMaps;`
- L263 _protected member_ `bool m_allowKeepFilesInMemory;`
- L264 _protected member_ `bool m_allowOutputFiles;`
- L265 _protected member_ `bool m_allowSpecialApplications;`
- L266 _protected member_ `bool m_suppressLogging;`
- L267 _protected member_ `bool m_shouldWriteToDisk;`
- L268 _protected member_ `bool m_writePlaceholders;`
- L269 _protected member_ `bool m_detailedTrace;`
- L270 _protected member_ `bool m_traceChildProcesses;`
- L271 _protected member_ `bool m_traceWrittenFiles;`
- L272 _protected member_ `bool m_logToFile;`
- L273 _protected member_ `bool m_storeIntermediateFilesCompressed;`
- L274 _protected member_ `bool m_readIntermediateFilesCompressed;`
- L275 _protected member_ `bool m_allowLocalDetour;`
- L276 _protected member_ `bool m_extractObjFilesSymbols;`
- L277 _protected member_ `bool m_allowLinkDependencyCrawler;`
- L278 _protected member_ `bool m_allowDiscardVirtualMemory;`
- L279 _protected member_ `bool m_dirTableSnapshotEnabled;`
- L280 _protected member_ `bool m_ownsTrace;`
- L282 _protected member_ `u64 m_keepOutputFileMemoryMapsThreshold;`
- L284 _protected member_ `Atomic<u32> m_processIdCounter = 0;`
- L285 _protected member_ `FileMappingHandle m_fileMappingTableHandle;`
- L286 _protected member_ `FileMappingBuffer m_fileMappingBuffer;`
- L288 _protected member_ `Atomic<u64> m_independentMappingCreated = 0;`
- L289 _protected member_ `Atomic<u64> m_independentMappingActive = 0;`
- L290 _protected member_ `Atomic<u64> m_reuseCount = 0;`
- L292 _protected member_ `ReaderWriterLock m_fileMappingTableMemLock;`
- L293 _protected member_ `u8* m_fileMappingTableMem = nullptr;`
- L294 _protected member_ `u32 m_fileMappingTableSize = 0;`
- L295 _protected member_ `Futex m_fileMappingTableLookupLock;`
- L322 _protected member_ `UnorderedMap<StringKey, FileMappingEntry> m_fileMappingTableLookup;`
- L324 _protected member_ `Futex m_fileMappingsThatCanBeFreedLock;`
- L325 _protected member_ `UnorderedMap<StringKey, u64> m_fileMappingsThatCanBeFreed;`
- L326 _protected member_ `Thread m_fileMappingGcThread;`
- L327 _protected member_ `Event m_fileMappingGcDone;`
- L329 _protected member_ `static constexpr u64 NameToHashMemSize = 48*1024*1024;`
- L330 _protected member_ `MemoryBlock m_nameToHashTableMem;`
- L332 _protected member_ `FixedSizeFileMappingAllocator m_processCommunicationAllocator;`
- L333 _protected member_ `std::string m_detoursLibrary[2][2];` — [nonlinux/linux][x64/arm64]
- L336 _protected member_ `TString m_stubBinary[2];` — [x64/arm64]
- L339 _protected member_ `Futex m_processStatsLock;`
- L340 _protected member_ `ProcessStats m_processStats;`
- L342 _protected member_ `Futex m_processesLock;`
- L343 _protected member_ `UnorderedMap<u32, ProcessHandle> m_processes;`
- L344 _protected member_ `Vector<ProcessHandle> m_deadProcesses;`
- L345 _protected member_ `WorkManagerImpl& m_processMessageThreads;`
- L347 _protected member_ `UnorderedMap<TString, Timer> m_applicationStats;`
- L349 _protected member_ `Futex m_virtualSourceFilesLock;`
- L351 _protected member_ `UnorderedMap<StringKey, VirtualSourceFile> m_virtualSourceFiles;`
- L353 _protected member_ `Futex m_rootsLookupLock;`
- L354 _protected member_ `UnorderedMap<RootsHandle, RootsEntry> m_rootsLookup;`
- L356 _protected member_ `Atomic<u32> m_wantsOnCloseIdCounter = 1;`
- L358 _protected member_ `SessionStats m_stats;`
- L359 _protected member_ `Trace& m_trace;`
- L360 _protected member_ `TString m_traceOutputFile;`
- L361 _protected member_ `TString m_extraInfo;`
- L364 _protected member_ `Futex m_processJobObjectLock;`
- L365 _protected member_ `HANDLE m_processJobObject = NULL;`
- L368 _protected member_ `Vector<u8> m_environmentMemory;`
- L370 _protected member_ `Futex m_environmentVariablesLock;`
- L371 _protected member_ `Vector<tchar> m_environmentVariables;`
- L372 _protected member_ `UnorderedSet<const tchar*, HashStringNoCase, EqualStringNoCase> m_localEnvironmentVariables;`
- L373 _protected member_ `Vector<std::pair<TString, TString>> m_additionalEnvironmentVariables;`
- L375 _protected member_ `GetNextProcessFunction m_getNextProcessFunction;`
- L376 _protected member_ `CustomServiceFunction m_customServiceFunction;`
- L378 _protected member_ `Bottleneck m_writeFilesBottleneck;`
- L379 _protected member_ `u64 m_writeFilesFileMapMax;`
- L380 _protected member_ `u64 m_writeFilesNoBufferingMin;`
- L383 _protected member_ `Futex m_isX64ApplicationLock;`
- L384 _protected member_ `UnorderedMap<TString, bool> m_isX64Application;`
- L388 _protected prototype_ `u32 GetSessionId();`
- L389 _protected prototype_ `bool StartSemaphoreService();`
- L390 _protected prototype_ `void StopSemaphoreService();`
- L391 _protected prototype_ `void ThreadSemaphoreService();`
- L392 _protected member_ `u32 m_sessionId;`
- L394 _protected member_ `Thread m_semaphoreServiceThread;`
- L395 _protected member_ `SemaphoreServiceInfo* m_semaphoreServiceInfo;`
- L398 _protected member_ `Futex m_availableTempDirectoriesLock;`
- L399 _protected member_ `List<u32> m_availableTempDirectories;`
- L400 _protected member_ `u32 m_availableTempDirectoriesMax = 0;`
- L402 _protected member_ `DependencyCrawler m_dependencyCrawler;`
- L404 _protected member_ `SearchPathCache m_searchPathCache;`
- L406 _protected member_ `ReaderWriterLock m_dirTableSnapshotLock;`
- L407 _protected member_ `DirTableSnapshot* m_dirTableSnapshot = nullptr;`
- L408 _protected member_ `Atomic<u32> m_dirTableSnapshotInProgress = 0;`
- L409 _protected member_ `u32 m_dirTableSizeForSnapshot = 0;`
- L412 _protected member_ `Futex m_patchedBinariesLock;`
- L414 _protected member_ `UnorderedMap<TString, PatchedBinary> m_patchedBinaries;`
- L415 _protected member_ `Futex m_handledPatchedCasKeysLock;`
- L416 _protected member_ `UnorderedMap<CasKey, Futex> m_handledPatchedCasKeys;`

#### struct `uba::Session::BinaryModule`  
`struct BinaryModule`  
_L146-146_
- L146 _public member_ `struct BinaryModule { TString name; TString path; u32 fileAttributes = 0; bool isSystem = false; u32 minOsVersion = 0; };`
- L146 _public member_ `struct BinaryModule { TString name; TString path; u32 fileAttributes = 0; bool isSystem = false; u32 minOsVersion = 0; };`
- L146 _public member_ `struct BinaryModule { TString name; TString path; u32 fileAttributes = 0; bool isSystem = false; u32 minOsVersion = 0; };`
- L146 _public member_ `struct BinaryModule { TString name; TString path; u32 fileAttributes = 0; bool isSystem = false; u32 minOsVersion = 0; };`
- L146 _public member_ `struct BinaryModule { TString name; TString path; u32 fileAttributes = 0; bool isSystem = false; u32 minOsVersion = 0; };`

#### struct `uba::Session::BinaryAndDeps`  
`struct BinaryAndDeps`  
_L147-147_
- L147 _public member_ `struct BinaryAndDeps { Vector<BinaryModule> modules; bool isShebang = false; };`
- L147 _public member_ `struct BinaryAndDeps { Vector<BinaryModule> modules; bool isShebang = false; };`

#### struct `uba::Session::MemoryMap`  
`struct MemoryMap`  
_L159-159_
- L159 _public member_ `struct MemoryMap { StringBuffer<128> name; u64 size = 0; };`
- L159 _public member_ `struct MemoryMap { StringBuffer<128> name; u64 size = 0; };`

#### struct `uba::Session::RootsEntry`  
`struct RootsEntry`  
_L221-221_
- L221 _public member_ `struct RootsEntry { Vector<u8> memory; RootPaths roots; Vector<TString> locals; Vector<TString> vfs; Futex lock; bool handled = false; };`
- L221 _public member_ `struct RootsEntry { Vector<u8> memory; RootPaths roots; Vector<TString> locals; Vector<TString> vfs; Futex lock; bool handled = false; };`
- L221 _public member_ `struct RootsEntry { Vector<u8> memory; RootPaths roots; Vector<TString> locals; Vector<TString> vfs; Futex lock; bool handled = false; };`
- L221 _public member_ `struct RootsEntry { Vector<u8> memory; RootPaths roots; Vector<TString> locals; Vector<TString> vfs; Futex lock; bool handled = false; };`
- L221 _public member_ `struct RootsEntry { Vector<u8> memory; RootPaths roots; Vector<TString> locals; Vector<TString> vfs; Futex lock; bool handled = false; };`
- L221 _public member_ `struct RootsEntry { Vector<u8> memory; RootPaths roots; Vector<TString> locals; Vector<TString> vfs; Futex lock; bool handled = false; };`

#### struct `uba::Session::FileMappingEntry`  
`struct FileMappingEntry`  
_L296-321_
- L298 _public member_ `Futex lock;`
- L300 _public member_ `SharedMemoryHandle memoryHandle;`
- L301 _public member_ `u64 memoryOffset = 0;`
- L303 _public member_ `u64 contentSize = 0;` — Size of uncompressed file or mapping
- L304 _public member_ `u64 lastWriteTime = 0;`
- L305 _public member_ `u64 storedSize = InvalidValue;` — Size stored on disk. Can be compressed or uncompressed
- L306 _public member_ `u16 refCount = 0;`
- L307 _public member_ `u8 usedCount = 0;`
- L308 _public member_ `u8 usedCountBeforeFree = 0;`
- L310 _public member_ `u8 isDir:1 = false;`
- L311 _public member_ `u8 handled:1 = false;`
- L312 _public member_ `u8 success:1 = false;`
- L313 _public member_ `u8 canBeFreed:1 = false;`
- L314 _public member_ `u8 createIndependentMapping:1 = false;`
- L315 _public member_ `u8 isInvisible:1 = false;`
- L316 _public member_ `u8 dropCasAfterUse:1 = false;`
- L319 _public member_ `TString name;`

#### struct `uba::Session::VirtualSourceFile`  
`struct VirtualSourceFile`  
_L350-350_
- L350 _public member_ `struct VirtualSourceFile { FileMappingHandle mappingHandle; SharedMemoryHandle memoryHandle; u64 size; };`
- L350 _public member_ `struct VirtualSourceFile { FileMappingHandle mappingHandle; SharedMemoryHandle memoryHandle; u64 size; };`
- L350 _public member_ `struct VirtualSourceFile { FileMappingHandle mappingHandle; SharedMemoryHandle memoryHandle; u64 size; };`

#### struct `uba::Session::PatchedBinary`  
`struct PatchedBinary`  
_L413-413_
- L413 _public member_ `struct PatchedBinary { CasKey key; Futex lock; bool handled = false; };`
- L413 _public member_ `struct PatchedBinary { CasKey key; Futex lock; bool handled = false; };`
- L413 _public member_ `struct PatchedBinary { CasKey key; Futex lock; bool handled = false; };`

#### enum `uba::(anonymous)`  
``  
_L432-436_

#### struct `uba::InitMessage`  
`struct InitMessage`  
_L440-443_
- L442 _public member_ `ProcessImpl& process;`

#### struct `uba::InitResponse`  
`struct InitResponse`  
_L445-456_
- L447 _public member_ `SharedMemoryAllocatorHandle sharedMemoryAllocatorHandle;`
- L448 _public member_ `SharedMemoryHandle permanentFilesHandle;`
- L449 _public member_ `u64 permanentFilesOffset = 0;`
- L450 _public member_ `FileMappingHandle directoryTableHandle = 0;`
- L451 _public member_ `DirTableSize directoryTableSize;`
- L452 _public member_ `u32 directoryTableCount = 0;`
- L453 _public member_ `FileMappingHandle mappedFileTableHandle = 0;`
- L454 _public member_ `u32 mappedFileTableSize = 0;`
- L455 _public member_ `u32 mappedFileTableCount = 0;`

#### struct `uba::CreateFileMessage`  
`struct CreateFileMessage`  
_L458-464_
- L460 _public member_ `ProcessImpl& process;`
- L461 _public member_ `StringBuffer<> fileName;`
- L462 _public member_ `StringKey fileNameKey;`
- L463 _public member_ `FileAccess access;`

#### struct `uba::CreateFileResponse`  
`struct CreateFileResponse`  
_L466-475_
- L468 _public member_ `StringBuffer<> fileName;`
- L469 _public member_ `StringBuffer<> virtualFileName;`
- L470 _public member_ `u64 size = InvalidValue;`
- L471 _public member_ `u32 closeId = 0;`
- L472 _public member_ `u32 mappedFileTableSize = 0;`
- L473 _public member_ `DirTableSize directoryTableSize;`
- L474 _public member_ `DirTableOffset dirTableOffset;`

#### struct `uba::CloseFileMessage`  
`struct CloseFileMessage`  
_L477-490_
- L479 _public member_ `ProcessImpl& process;`
- L480 _public member_ `StringBuffer<> fileName;`
- L481 _public member_ `StringKey newNameKey;`
- L482 _public member_ `StringBuffer<> newName;`
- L483 _public member_ `u32 closeId = 0;`
- L484 _public member_ `u32 attributes = 0;`
- L485 _public member_ `bool deleteOnClose = false;`
- L486 _public member_ `bool success = true;`
- L487 _public member_ `SharedMemoryHandle memoryHandle;`
- L488 _public member_ `u64 fileSize = 0;`
- L489 _public member_ `u64 lastWriteTime = 0;`

#### struct `uba::CloseFileResponse`  
`struct CloseFileResponse`  
_L492-495_
- L494 _public member_ `DirTableSize directoryTableSize;`

#### struct `uba::DeleteFileMessage`  
`struct DeleteFileMessage`  
_L497-503_
- L499 _public member_ `ProcessImpl& process;`
- L500 _public member_ `StringBuffer<> fileName;`
- L501 _public member_ `StringKey fileNameKey;`
- L502 _public member_ `u32 closeId = 0;`

#### struct `uba::DeleteFileResponse`  
`struct DeleteFileResponse`  
_L505-510_
- L507 _public member_ `bool result = false;`
- L508 _public member_ `u32 errorCode = ~0u;`
- L509 _public member_ `DirTableSize directoryTableSize;`

#### struct `uba::CopyFileMessage`  
`struct CopyFileMessage`  
_L512-523_
- L514 _public member_ `ProcessImpl& process;`
- L515 _public member_ `StringKey fromKey;`
- L516 _public member_ `StringBuffer<> fromName;`
- L517 _public member_ `u64 fileSize = 0;`
- L518 _public member_ `u64 lastWriteTime = 0;`
- L519 _public member_ `u32 fileAttributes = 0;`
- L521 _public member_ `StringKey toKey;`
- L522 _public member_ `StringBuffer<> toName;`

#### struct `uba::CopyFileResponse`  
`struct CopyFileResponse`  
_L525-532_
- L527 _public member_ `StringBuffer<> fromName;`
- L528 _public member_ `StringBuffer<> toName;`
- L529 _public member_ `u32 closeId = 0;`
- L530 _public member_ `u32 errorCode = ~0u;`
- L531 _public member_ `DirTableSize directoryTableSize;`

#### struct `uba::MoveFileMessage`  
`struct MoveFileMessage`  
_L534-551_
- L536 _public member_ `ProcessImpl& process;`
- L537 _public member_ `StringKey fromKey;`
- L538 _public member_ `StringBuffer<> fromName;`
- L539 _public member_ `u64 fileSize = 0;`
- L540 _public member_ `u64 lastWriteTime = 0;`
- L541 _public member_ `u32 fileAttributes = 0;`
- L543 _public member_ `StringKey toKey;`
- L544 _public member_ `StringBuffer<> toName;`
- L546 _public member_ `u32 flags = 0;`
- L550 _public member_ `StringBuffer<MaxPath> symlinkContent;` — Preserved across the rename when fromName is a symlink — RegisterOverlayCreateOrWrite needs the target string to keep S_IFLNK on the destination entry.

#### struct `uba::MoveFileResponse`  
`struct MoveFileResponse`  
_L553-558_
- L555 _public member_ `bool result = false;`
- L556 _public member_ `u32 errorCode = ~0u;`
- L557 _public member_ `DirTableSize directoryTableSize;`

#### struct `uba::ChmodMessage`  
`struct ChmodMessage`  
_L560-566_
- L562 _public member_ `ProcessImpl& process;`
- L563 _public member_ `StringKey fileNameKey;`
- L564 _public member_ `StringBuffer<> fileName;`
- L565 _public member_ `u32 fileMode = 0;`

#### struct `uba::ChmodResponse`  
`struct ChmodResponse`  
_L568-571_
- L570 _public member_ `u32 errorCode = ~0u;`

#### struct `uba::SymlinkMessage`  
`struct SymlinkMessage`  
_L573-584_
- L575 _public member_ `ProcessImpl& process;`
- L576 _public member_ `StringKey filePathKey;`
- L577 _public member_ `StringBuffer<> symlinkFilePath;`
- L578 _public member_ `StringKey contentPathKey;`
- L579 _public member_ `StringBuffer<MaxPath> symlinkContentPath;`
- L580 _public member_ `StringBuffer<MaxPath> symlinkContent;`
- L581 _public member_ `u64 fileSize = 0;`
- L582 _public member_ `u64 lastWriteTime = 0;`
- L583 _public member_ `u32 fileAttributes = 0;`

#### struct `uba::SymlinkResponse`  
`struct SymlinkResponse`  
_L586-591_
- L588 _public member_ `bool success = false;`
- L589 _public member_ `u32 errorCode = ~0u;`
- L590 _public member_ `DirTableSize directoryTableSize;`

#### struct `uba::GetFullFileNameMessage`  
`struct GetFullFileNameMessage`  
_L593-600_
- L595 _public member_ `ProcessImpl& process;`
- L596 _public member_ `StringBuffer<> fileName;`
- L597 _public member_ `StringKey fileNameKey;`
- L598 _public member_ `const u8* loaderPaths = nullptr;`
- L599 _public member_ `u32 loaderPathsSize = 0;`

#### struct `uba::GetFullFileNameResponse`  
`struct GetFullFileNameResponse`  
_L602-607_
- L604 _public member_ `StringBuffer<> fileName;`
- L605 _public member_ `StringBuffer<> virtualFileName;`
- L606 _public member_ `u32 mappedFileTableSize = 0;`

#### struct `uba::GetLongPathNameMessage`  
`struct GetLongPathNameMessage`  
_L609-613_
- L611 _public member_ `ProcessImpl& process;`
- L612 _public member_ `StringBuffer<> fileName;`

#### struct `uba::GetLongPathNameResponse`  
`struct GetLongPathNameResponse`  
_L615-619_
- L617 _public member_ `StringBuffer<> fileName;`
- L618 _public member_ `u32 errorCode = ~0u;`

#### struct `uba::CreateDirectoryMessage`  
`struct CreateDirectoryMessage`  
_L621-626_
- L623 _public member_ `ProcessImpl& process;`
- L624 _public member_ `StringKey nameKey;`
- L625 _public member_ `StringBuffer<> name;`

#### struct `uba::CreateDirectoryResponse`  
`struct CreateDirectoryResponse`  
_L628-631_
- L630 _public member_ `DirTableSize directoryTableSize;`

#### struct `uba::RemoveDirectoryMessage`  
`struct RemoveDirectoryMessage`  
_L633-638_
- L635 _public member_ `ProcessImpl& process;`
- L636 _public member_ `StringKey nameKey;`
- L637 _public member_ `StringBuffer<> name;`

#### struct `uba::RemoveDirectoryResponse`  
`struct RemoveDirectoryResponse`  
_L640-643_
- L642 _public member_ `DirTableSize directoryTableSize;`

#### struct `uba::ListDirectoryMessage`  
`struct ListDirectoryMessage`  
_L645-649_
- L647 _public member_ `StringBuffer<> directoryName;`
- L648 _public member_ `StringKey directoryNameKey;`

#### struct `uba::ListDirectoryResponse`  
`struct ListDirectoryResponse`  
_L651-655_
- L653 _public member_ `DirTableOffset tableOffset;`
- L654 _public member_ `DirTableSize directoryTableSize;`

#### struct `uba::ActiveFile`  
`struct ActiveFile`  
_L659-664_
- L661 _public member_ `TString name;`
- L662 _public member_ `StringKey nameKey;`
- L663 _public member_ `u32 refCount = 0;`

#### struct `uba::WrittenFile`  
`struct WrittenFile`  
_L668-686_
- L670 _public member_ `StringKey key;`
- L671 _public member_ `TString name;`
- L672 _public member_ `TString backedName;`
- L674 _public member_ `SharedMemoryHandle memoryHandle;`
- L675 _public member_ `SharedMemoryHandle originalMemoryHandle;`
- L677 _public member_ `u64 memoryWritten = 0;`
- L678 _public member_ `u64 lastWriteTime = 0;`
- L679 _public member_ `u32 attributes = 0;`
- L681 _public member_ `u32 ownerId = 0;` — Last process who write it
- L685 _public member_ `Session::FileMappingEntry* entryToReduceRefCount = nullptr;` — TODO: Ugly placement of this pointer. Here to make sure FileMappingEntry is not garbage collecting before process exit callback is called

#### struct `uba::NextProcessInfo`  
`struct NextProcessInfo`  
_L690-698_
- L692 _public member_ `TString arguments;`
- L693 _public member_ `TString workingDir;`
- L694 _public member_ `TString description;`
- L695 _public member_ `TString logFile;`
- L696 _public member_ `TString breadcrumbs;`
- L697 _public member_ `Vector<u8> overlayFiles;`

#### struct `std::hash`  
`template<> struct std::hash<uba::ProcessHandle>`  
_L703-703_
- L703 _public function_ `template<> struct std::hash<uba::ProcessHandle>`

#### Free symbols / members of external scopes

- L20 _macro_ `#define UBA_DEBUG_TRACK_MAPPING 0//UBA_DEBUG_LOGGER`
- L22 _namespace_ `namespace uba`
- L63 _typedef_ `using RootsHandle = u64;` (scope `uba`)
- L425 _prototype_ `void GenerateNameForProcess(StringBufferBase& out, const tchar* arguments, u32 counterSuffix);` (scope `uba`)
- L426 _prototype_ `bool GetZone(StringBufferBase& outZone);` (scope `uba`)
- L429 _typedef_ `using FileAccess = u8;` (scope `uba`)
- L433 _enumerator_ `FileAccess_Read = 1` (scope `uba::__anon5015f4b30103`)
- L434 _enumerator_ `FileAccess_Write = 2` (scope `uba::__anon5015f4b30103`)
- L435 _enumerator_ `FileAccess_ReadWrite = 3` (scope `uba::__anon5015f4b30103`)

### `Source/Programs/UnrealBuildAccelerator/Common/Public/UbaSessionClient.h` (Public)


#### struct `uba::SessionClientCreateInfo`  
`struct SessionClientCreateInfo : SessionCreateInfo`  
_L12-35_
- inherits: `SessionCreateInfo`
- L14 _public prototype_ `SessionClientCreateInfo(Storage& s, NetworkClient& c, LogWriter& writer = g_consoleLogWriter);`
- L15 _public prototype_ `void Apply(const Config& config);`
- L17 _public member_ `NetworkClient& client;`
- L18 _public member_ `StringBuffer<128> name;`
- L19 _public member_ `u32 maxProcessCount = 1;`
- L20 _public member_ `u32 defaultPriorityClass = ProcessPriority_BelowNormal;`
- L21 _public member_ `u32 maxIdleSeconds = ~0u;`
- L22 _public member_ `u32 pingTimeoutSecondsPrintCallstacks = 0;`
- L23 _public member_ `u32 osVersion = 0;`
- L24 _public member_ `u8 memWaitLoadPercent = 80;` — When memory usage goes above this percent, no new processes will be spawned until back below
- L25 _public member_ `u8 memKillLoadPercent = 90;` — When memory usage goes above this percent, newest processes will be killed to bring it back below
- L26 _public member_ `bool dedicated = false;` — If true, server will not disconnect client when starting to run out of work.
- L27 _public member_ `bool disableCustomAllocator = false;`
- L28 _public member_ `bool useBinariesAsVersion = false;`
- L29 _public member_ `bool killRandom = false;`
- L30 _public member_ `bool useStorage = true;`
- L31 _public member_ `bool downloadDetoursLib = true;`
- L32 _public member_ `bool useDependencyCrawler = false;` — Dependency crawler will go wide and try to prefetch all dependencies needed by the process
- L33 _public member_ `bool useKnownLocalBinaries = true;` — Will use local binaries like sh, ln, cp etc if available
- L34 _public member_ `Function<void(const ProcessHandle&)> processFinished;`

#### class `uba::SessionClient`  
`class SessionClient final : public Session`  
_L37-207_
- inherits: `Session`
- L40 _public prototype_ `SessionClient(const SessionClientCreateInfo& info);`
- L41 _public prototype_ `~SessionClient();`
- L43 _public prototype_ `bool Start();`
- L44 _public prototype_ `void Stop(bool wait = true);`
- L45 _public prototype_ `bool Wait(u32 milliseconds = 0xFFFFFFFF, Event* wakeupEvent = nullptr);`
- L46 _public prototype_ `void SendSummary(const Function<void(Logger&)>& extraInfo);`
- L47 _public prototype_ `void SetIsTerminating(const tchar* reason = TC("Terminating"), u64 de` — Session stores pointer directly. Can't be temporary
- L48 _public prototype_ `void SetMaxProcessCount(u32 count);`
- L49 _public prototype_ `void SetMaxIdleTime(u32 seconds);`
- L50 _public prototype_ `void SetAllowSpawn(bool allow);`
- L52 _public prototype_ `u64 GetBestPing();`
- L53 _public prototype_ `u32 GetMaxProcessCount();`
- L54 _public prototype_ `u32 GetDesiredConnectionCount();`
- L56 _public prototype_ `bool Exists(const StringView& path, u32& outAttributes);`
- L58 _public prototype_ `void SendNotification(StringView text);`
- L61 _private prototype_ `bool RetrieveCasFile(CasKey& outNewKey, u64& outSize, const CasKey& casKey, StringKey keyHint, const tchar* hint, bool storeUncompressed, bool allowProxy = true);`
- L63 _private prototype_ `virtual bool PrepareProcess(ProcessImpl& process, bool isChild, StringBufferBase& outRealApplication, const tchar*& outRealWorkingDir) override;`
- L64 _private prototype_ `virtual Vector<tchar>& GetProcessEnvironmentVariables() override;`
- L65 _private prototype_ `virtual bool ProcessThreadStart(ProcessImpl& process) override;`
- L66 _private prototype_ `virtual bool CreateFileForRead(CreateFileResponse& out, TrackWorkScope& tws, StringView fileName, StringKey fileNameKey, ProcessImpl& process, const ApplicationRules& rules) override;`
- L67 _private prototype_ `virtual bool DeleteFile(DeleteFileResponse& out, const DeleteFileMessage& msg) override;`
- L68 _private prototype_ `virtual bool MoveFile(MoveFileResponse& out, const MoveFileMessage& msg) override;`
- L69 _private prototype_ `virtual bool Chmod(ChmodResponse& out, const ChmodMessage& msg) override;`
- L70 _private prototype_ `virtual bool GetFullFileName(GetFullFileNameResponse& out, const GetFullFileNameMessage& msg) override;`
- L71 _private prototype_ `virtual bool GetLongPathName(GetLongPathNameResponse& out, const GetLongPathNameMessage& msg) override;`
- L72 _private prototype_ `virtual bool GetListDirectoryInfo(ListDirectoryResponse& out, const StringView& dirName, const StringKey& dirKey, DirectoryTableOverlay* overlay) override;`
- L73 _private prototype_ `virtual bool WriteFilesToDisk(ProcessImpl& process, WrittenFile** files, u32 fileCount) override;`
- L74 _private prototype_ `virtual bool AllocFailed(Process& process, const tchar* allocType, u32 error) override;`
- L75 _private prototype_ `virtual void PrintSessionStats(Logger& logger) override;`
- L76 _private prototype_ `virtual bool GetNextProcess(Process& process, bool& outNewProcess, bool& outShouldExit, NextProcessInfo& outNextProcess, u32 prevExitCode, BinaryReader& statsReader, u32 timeoutMs) override;`
- L77 _private prototype_ `virtual bool CustomMessage(Process& process, BinaryReader& reader, BinaryWriter& writer) override;`
- L78 _private prototype_ `virtual bool SHGetKnownFolderPath(Process& process, BinaryReader& reader, BinaryWriter& writer) override;`
- L79 _private prototype_ `virtual bool HostRun(BinaryReader& reader, BinaryWriter& writer) override;`
- L80 _private prototype_ `virtual bool GetSymbols(const tchar* application, bool isLinux, bool isArm, BinaryReader& reader, BinaryWriter& writer);`
- L81 _private prototype_ `virtual bool FlushWrittenFiles(ProcessImpl& process) override;`
- L82 _private prototype_ `virtual bool UpdateEnvironment(ProcessImpl& process, const StringView& reason, bool resetStats) override;`
- L83 _private prototype_ `virtual bool LogLine(ProcessImpl& process, const tchar* line, LogEntryType logType) override;`
- L85 _private prototype_ `void TraceSessionUpdate();`
- L90 _private prototype_ `bool GetCasKeyForFile(CasKey& out, u32 processId, const StringView& fileName, const StringKey& fileNameKey);`
- L91 _private prototype_ `bool ReadModules(List<ModuleInfo>& outModules, bool& outIsShebang, StringBufferBase& outVirtualApplication, u32 processId, StringView application, StringView workingDir);`
- L92 _private prototype_ `bool EnsureBinaryFile(StringBufferBase& out, StringBufferBase& outVirtual, u32 processId, StringView fileName, const StringKey& fileNameKey, StringView applicationDir, StringView workingDir, const u8* loaderPaths, u32 loaderPathsSize);`
- L93 _private prototype_ `bool WriteBinFile(StringBufferBase& out, const StringView& binaryName, const CasKey& casKey, const KeyToString& applicationDir, u32 fileAttributes);`
- L94 _private prototype_ `bool ShouldSend(ProcessImpl& process, StringView path);`
- L95 _private prototype_ `bool SendFileSystemOperations(ProcessImpl& process);`
- L96 _private prototype_ `bool SendFiles(ProcessImpl& process);`
- L97 _private prototype_ `bool SendFile(WrittenFile& file, u32 processId, bool keepMappingInMemory, bool compressed);`
- L98 _private prototype_ `bool SendUpdateDirectoryTable(StackBinaryReader<SendMaxSize>& reader);` — Note, reader is sent in to save stack space.
- L99 _private prototype_ `bool UpdateDirectoryTableFromServer(StackBinaryReader<SendMaxSize>& reader);`
- L100 _private prototype_ `bool SendUpdateNameToHashTable(StackBinaryReader<SendMaxSize>& reader);`
- L101 _private prototype_ `bool UpdateNameToHashTableFromServer(StackBinaryReader<SendMaxSize>& reader);`
- L102 _private prototype_ `void Connect();`
- L103 _private prototype_ `void BuildEnvironmentVariables(BinaryReader& reader);`
- L104 _private prototype_ `bool SendProcessAvailable(Vector<InternalProcessStartInfo>& outStartInfos, Vector<u32>& outCancelled, float availableWeight);`
- L105 _private prototype_ `bool SendGetNextMessage();`
- L106 _private prototype_ `void CancelGetNextMessageQueue();`
- L107 _private prototype_ `bool HandleGetNextResponse(BinaryReader& reader, u32 processId, bool& outNewProcess, bool& outShouldExit, NextProcessInfo& outNextProcess);`
- L108 _private prototype_ `void SendReturnProcess(u32 processId, const tchar* reason, ...);`
- L109 _private prototype_ `bool SendProcessInputs(ProcessImpl& process);`
- L110 _private prototype_ `bool SendProcessFinished(ProcessImpl& process, u32 exitCode);`
- L111 _private prototype_ `void SendPing(u64 memAvail, u64 memTotal);`
- L112 _private prototype_ `void SendLogEntry(StringView text, LogEntryType type = LogEntryType_Info, bool ack = false);`
- L113 _private prototype_ `bool SendRootsHandle(RootsHandle rootsHandle);`
- L114 _private prototype_ `void SendLogFilesToServer(ProcessImpl& pi);`
- L115 _private prototype_ `void GetLogFiles(List<WrittenFile>& outLogFiles, ProcessImpl& pi);`
- L116 _private prototype_ `void GetLogFileName(StringBufferBase& out, const tchar* logFile, const tchar* arguments, u32 processId);`
- L117 _private prototype_ `u32 WriteLogLines(BinaryWriter& writer, ProcessImpl& process);`
- L118 _private prototype_ `bool ParseDirectoryTable();`
- L119 _private prototype_ `bool EntryExists(StringView path, DirTableOffset& outTableOffset);`
- L120 _private prototype_ `void RunSpeedTest(StringView args);`
- L122 _private prototype_ `void ThreadCreateProcessLoop();`
- L124 _private member_ `NetworkClient& m_client;`
- L125 _private member_ `static constexpr u8 ServiceId = SessionServiceId;`
- L127 _private member_ `StringBuffer<128> m_name;`
- L128 _private member_ `StringBuffer<MaxPath> m_processWorkingDir;`
- L129 _private member_ `u32 m_sessionId = ~0u;`
- L130 _private member_ `u32 m_uiLanguage = 0;`
- L131 _private member_ `u32 m_defaultPriorityClass;`
- L132 _private member_ `Atomic<u32> m_maxIdleSeconds = ~0u;`
- L133 _private member_ `u32 m_osVersion = 0;`
- L134 _private member_ `u32 m_killRandomIndex = ~0u;`
- L135 _private member_ `u32 m_killRandomCounter = 0;`
- L136 _private member_ `u8 m_memWaitLoadPercent;`
- L137 _private member_ `u8 m_memKillLoadPercent;`
- L138 _private member_ `bool m_disableCustomAllocator;`
- L139 _private member_ `bool m_useBinariesAsVersion;`
- L140 _private member_ `bool m_dedicated = false;`
- L141 _private member_ `bool m_useStorage = true;`
- L142 _private member_ `bool m_downloadDetoursLib = true;`
- L143 _private member_ `bool m_shouldSendLogToServer = false;`
- L144 _private member_ `bool m_shouldSendTraceToServer = false;`
- L145 _private member_ `bool m_remoteExecutionEnabled = true;`
- L146 _private member_ `bool m_useDependencyCrawler = false;`
- L147 _private member_ `bool m_useKnownLocalBinaries = true;`
- L149 _private member_ `Atomic<const tchar*> m_terminationReason = nullptr;`
- L150 _private member_ `Atomic<u64> m_terminationTime = 0;`
- L151 _private member_ `Atomic<u32> m_maxProcessCount = 0;`
- L152 _private member_ `Atomic<u32> m_desiredConnectionCount = 0;`
- L153 _private member_ `Atomic<float> m_cpuUsage = 0.0f;`
- L156 _private member_ `Futex m_handledApplicationEnvironmentsLock;`
- L157 _private member_ `UnorderedMap<TString, ApplicationEnvironment> m_handledApplicationEnvironments;`
- L159 _private member_ `Futex m_binFileLock;`
- L160 _private member_ `UnorderedMap<TString, CasKey> m_writtenBinFiles;`
- L162 _private member_ `Futex m_nameToNameLookupLock;`
- L164 _private member_ `UnorderedMap<StringKey, NameRec> m_nameToNameLookup;`
- L167 _private member_ `UnorderedMap<StringKey, HashRec> m_nameToHashLookup;`
- L168 _private member_ `Futex m_nameToHashLookupLock;`
- L169 _private member_ `ReaderWriterLock m_nameToHashMemLock;`
- L171 _private member_ `Futex m_directoryTableLock;`
- L172 _private member_ `u32 m_directoryTableMemPos = 0;`
- L173 _private member_ `bool m_directoryTableError = false;`
- L175 _private member_ `ActiveUpdateDirectoryEntry* m_firstEmptyWait = nullptr;`
- L176 _private member_ `ActiveUpdateDirectoryEntry* m_firstReadWait = nullptr;`
- L178 _private member_ `Event m_waitToSendEvent;`
- L179 _private member_ `Thread m_loopThread;`
- L180 _private member_ `Atomic<bool> m_loop = true;`
- L181 _private member_ `Atomic<bool> m_sendPing = false;`
- L182 _private member_ `Atomic<bool> m_allowSpawn = true;`
- L184 _private member_ `Function<void(const ProcessHandle&)> m_processFinished;`
- L186 _private member_ `SessionSummaryStats m_stats;`
- L189 _private member_ `GetNextEntry* m_firstGetNextEntry = nullptr;`
- L190 _private member_ `Futex m_getNextEntryLock;`
- L192 _private member_ `Atomic<u64> m_bestPing = 0;`
- L193 _private member_ `Atomic<u64> m_lastPing = 0;`
- L194 _private member_ `u64 m_lastPingSendTime = 0;`
- L195 _private member_ `u32 m_pingTimeoutSecondsPrintCallstacks = 0;`
- L197 _private member_ `Atomic<u64> m_memAvail = 0;`
- L198 _private member_ `Atomic<u64> m_memTotal = 0;`
- L200 _private member_ `UnorderedMap<CasKey, Vector<u8>> m_hostRunCache;`
- L201 _private member_ `Futex m_hostRunCacheLock;`
- L203 _private member_ `u32 m_dirtableParsedPosition = 0;`
- L204 _private member_ `Futex m_dirVisitedLock;`
- L206 _private member_ `UnorderedMap<StringKey, DirVisitedEntry> m_dirVisited;`

#### struct `uba::SessionClient::ApplicationEnvironment`  
`struct ApplicationEnvironment`  
_L155-155_
- L155 _public member_ `struct ApplicationEnvironment { Futex lock; TString virtualApplication; TString realApplication; bool isShebang = false; };`
- L155 _public member_ `struct ApplicationEnvironment { Futex lock; TString virtualApplication; TString realApplication; bool isShebang = false; };`
- L155 _public member_ `struct ApplicationEnvironment { Futex lock; TString virtualApplication; TString realApplication; bool isShebang = false; };`
- L155 _public member_ `struct ApplicationEnvironment { Futex lock; TString virtualApplication; TString realApplication; bool isShebang = false; };`

#### struct `uba::SessionClient::NameRec`  
`struct NameRec`  
_L163-163_
- L163 _public member_ `struct NameRec { TString name; TString virtualName; Futex lock; bool handled = false; };`
- L163 _public member_ `struct NameRec { TString name; TString virtualName; Futex lock; bool handled = false; };`
- L163 _public member_ `struct NameRec { TString name; TString virtualName; Futex lock; bool handled = false; };`
- L163 _public member_ `struct NameRec { TString name; TString virtualName; Futex lock; bool handled = false; };`

#### struct `uba::SessionClient::HashRec`  
`struct HashRec`  
_L166-166_
- L166 _public member_ `struct HashRec { CasKey key; u64 serverTime = 0; Futex lock; };`
- L166 _public member_ `struct HashRec { CasKey key; u64 serverTime = 0; Futex lock; };`
- L166 _public member_ `struct HashRec { CasKey key; u64 serverTime = 0; Futex lock; };`

#### struct `uba::SessionClient::DirVisitedEntry`  
`struct DirVisitedEntry`  
_L205-205_
- L205 _public member_ `struct DirVisitedEntry { Futex lock; bool handled = false; };`
- L205 _public member_ `struct DirVisitedEntry { Futex lock; bool handled = false; };`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace uba`

### `Source/Programs/UnrealBuildAccelerator/Common/Public/UbaSessionCreateInfo.h` (Public)


#### struct `uba::SessionCreateInfo`  
`struct SessionCreateInfo`  
_L13-61_
- L15 _public function_ `SessionCreateInfo(Storage& s, LogWriter& w = g_consoleLogWriter) : storage(s), logWriter(w)`
- L17 _public prototype_ `void Apply(const Config& config);`
- L19 _public member_ `Storage& storage;`
- L20 _public member_ `LogWriter& logWriter;`
- L21 _public member_ `const tchar* rootDir = nullptr;` — Root dir for logs, binaries, temp files
- L22 _public member_ `const tchar* traceName = nullptr;` — Name of trace. This name can be used by UbaVisualizer to watch progress live
- L23 _public member_ `const tchar* traceChannelName = nullptr;` — If set, the trace name is announced on this TraceChannel. When launchVisualizer is also set, a new visualizer is only spawned if no listener is detected on the channel; otherwise the existing visualizer picks up the trace via the channel.
- L24 _public member_ `const tchar* traceOutputFile = nullptr;` — Output file. Will be written at end of run.
- L25 _public member_ `const tchar* extraInfo = nullptr;` — Extra info that will be stored in the trace info about the session
- L26 _public member_ `bool logToFile = false;` — Set to true to have all processes write a log file with function calls.
- L27 _public member_ `bool useUniqueId = true;` — If true, id of session will be "yymmdd_hhmmss". Otherwise "Debug"
- L28 _public member_ `bool allowCustomAllocator = true;` — Allow detouring of allocator inside processes.
- L29 _public member_ `bool allowLazyCopyOnWrite = true;` — Allow detoured process to map CoW as read-only and then make pages CoW based on need
- L30 _public member_ `bool launchVisualizer = false;` — Launch a UbaVisualizer process (this automatically enable trace)
- L31 _public member_ `bool allowMemoryMaps = true;` — Use memory maps where possible. Session creates memory maps of files that processes use
- L32 _public member_ `bool allowKeepFilesInMemory = true;` — Allow detoured process to keep output files in memory and send them to session through file mapping handle
- L33 _public member_ `bool allowOutputFiles = true;` — Allow (selected) output files to be written to disk after process has ended.
- L34 _public member_ `bool allowSpecialApplications = true;` — Allow uba to expand cmd.exe and call known commands instead of running additional process
- L35 _public member_ `bool suppressLogging = false;` — Suppress all logging produced by detoured processes. Will be made in detoured process to improve performance when needed
- L36 _public member_ `bool shouldWriteToDisk = true;` — Set to false to skip writing output files to disk
- L37 _public member_ `bool writePlaceholders = false;` — If this is true, 1-byte placeholder files will be written where possible
- L38 _public member_ `bool traceEnabled = false;` — Set to true to always create in-memory trace data. Is not needed if traceName, traceOutputFile or launchVisualizer is set
- L39 _public member_ `bool detailedTrace = false;` — Enable detailed trace to include jobs, individual file I/O etc in trace dump
- L40 _public member_ `bool traceChildProcesses = false;` — Trace and visualize child processes so they can be seen in visualizer
- L41 _public member_ `bool traceWrittenFiles = false;` — Will add process output files to trace
- L42 _public member_ `bool storeIntermediateFilesCompressed = false;` — Compiler will write intermediate files (.obj, .pch etc) compressed to disk and will be decompressed when used
- L43 _public member_ `bool readIntermediateFilesCompressed = false;` — Set to true to support reading compressed .obj files. This flag will not compress new obj files
- L44 _public member_ `bool allowLocalDetour = true;` — Allow local processes to be detoured. If this is false it is up to outside logic to register all created/deleted files
- L45 _public member_ `bool extractObjFilesSymbols = false;` — Will extract import/export symbols to a file
- L46 _public member_ `bool treatTempDirAsEmpty = true;` — If this is true, directory table will always see temp as empty. Use sub directories of temp instead
- L47 _public member_ `bool useFakeVolumeSerial = true;` — Fake volume serials reduce the directory table size since serials end up being compressed down to one byte
- L48 _public member_ `bool allowDiscardVirtualMemory = false;` — Set to true to use DiscardVirtualMemory around map/unmap views of file mappings. This seems to speed up perf quite a lot
- L49 _public member_ `bool allowLinkDependencyCrawler = true;` — Enable crawler that reads ahead to find needed obj files for linker
- L50 _public member_ `bool dirTableSnapshotEnabled = true;` — Creates a snapshot of the dir table when everytime it grows by 200kb or more
- L51 _public member_ `int linkCrawlerMaxParallel = -2;` — If allowLinkDependencyCrawler is set, this controls number of decompress in parallel. If negative it is max cores - value
- L52 _public member_ `u64 deleteSessionsOlderThanSeconds = 12 * 60 * 60;` — Delete session folders older than 12 hours by default . Set to 0 to not delete or 1 to delete all
- L53 _public member_ `u64 keepOutputFileMemoryMapsThreshold = 256 * 1024;` — If allowMemoryMaps is true, output files will be kept in memory if smaller than this size
- L54 _public member_ `u32 traceReserveSizeMb = 128;` — Memory reserved for trace file (in mb)
- L55 _public member_ `u32 writeFilesBottleneck = 16;` — When writing files to disk this number will control how many that can write in parallel
- L56 _public member_ `u32 writeFilesFileMapMaxMb = 100000;` — If file size is smaller than this number, then use memory maps for writing to disk
- L57 _public member_ `u32 writeFilesNoBufferingMinMb = 16;` — If file size is at least this number, then overlapped io with no buffering will be used
- L58 _public member_ `u32 traceIntervalMs = 500;` — milliseconds between each trace entry
- L60 _public member_ `Trace* trace = nullptr;` — If no trace is provided, session will create a new one

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace uba`

### `Source/Programs/UnrealBuildAccelerator/Common/Public/UbaSessionServer.h` (Public)


#### class `uba::SessionServer`  
`class SessionServer final : public Session`  
_L16-244_
- inherits: `Session`
- L20 _public prototype_ `SessionServer(const SessionServerCreateInfo& info, const u8* environment = nullptr, u32 environmentSize = 0);` — Ctor/dtor. "environmnent" should be an array of utf8-written strings. This is really only needed for posix platforms where process is a c# process
- L21 _public prototype_ `~SessionServer();`
- L28 _public prototype_ `ProcessHandle RunProcessRemote(const ProcessStartInfo& startInfo, float weight = 1.0f, const void* knownInputs = nullptr, u32 knownInputsCount = 0, bool canCrossArchitecture = false, bool canCrossPlatform = false);` — Run process remotely. startInfo contains info about the process to run remotely weight is the expected core usage of the process. If processes are multithreaded it makes sense to increase weight. As an example, in UnrealBuildTool we see cl.exe as 1.5 and clang.exe as 1.0 knownInputs is a memory block with null terminated tchar strings followed by an empty null terminated string to end. knownInputsCount is the number of strings in the memory block strings should be absolute or relative to working dir.
- L32 _public typedef_ `using ProcessToRaceCallback = Function<bool(ProcessHandle&, ProcessStartInfo&)>;` — Will kick off a local process with the same startInfo as the one provided to start the process with id matching raceAgainstRemoteProcessId This can be useful if there are free local cores and we know local machine is faster or network connection to remote is slow
- L33 _public prototype_ `ProcessHandle RunProcessRacing(const ProcessToRaceCallback& callback);`
- L36 _public prototype_ `void DisableRemoteExecution();` — Disable remote execution. This will tell all clients to stop taking on new processes and disconnect as soon as their current processes are finished
- L37 _public prototype_ `bool IsRemoteExecutionDisabled();`
- L38 _public prototype_ `void ReenableRemoteExecution();`
- L39 _public prototype_ `bool DisableRemoteExecutionOnAgent(const tchar* agentName);`
- L44 _public prototype_ `void SetCustomCasKeyFromTrackedInputs(const tchar* fileName, const tchar* workingDir, const u8* trackedInputs, u32 trackedInputsBytes);` — This can be used to set a custom cas key based on a file and its inputs. Can be used for non-deterministic outputs to still be able to use cached cas content on clients For example, when a pch is built on the host we can use all the input involved to create the pch and use that as the cas key for the resulting huge file This means that if a remote machine has a pch from an older run where all the input matches, it can reuse the cas content even though the output differs
- L45 _public prototype_ `bool GetCasKeyFromTrackedInputs(CasKey& out, const tchar* fileName, const tchar* workingDir, const u8* data, u32 dataLen);`
- L48 _public typedef_ `using RemoteProcessAvailableCallback = Function<void(bool isCrossArchitecture, bool isCrossPlatform)>;` — Callback that will be called when a client is asking for processes to run. All remotes frequently ask for processes to run if they have free process slots
- L49 _public prototype_ `void SetRemoteProcessSlotAvailableEvent(const RemoteProcessAvailableCallback& remoteProcessSlotAvailableEvent);`
- L52 _public prototype_ `void SetRemoteProcessReturnedEvent(const Function<void(Process&)>& remoteProcessReturnedEvent);` — Callback that is called when process is returned. This could be because a client unexpectedly disconnected or is running out of memory
- L55 _public prototype_ `void SetNativeProcessCreatedFunc(const Function<void(ProcessImpl&)>& func);` — Callback that is called when process is returned. This could be because a client unexpectedly disconnected or is running out of memory
- L58 _public prototype_ `void WaitOnAllTasks();` — Wait for all queued up/active tasks to finish
- L61 _public prototype_ `void WaitOnAllClients();` — Wait for all clients to disconnect.
- L64 _public prototype_ `void SetMaxRemoteProcessCount(u32 count);` — Can be used to hint the session how many processes (that can run remotely that are left.. session can then start disabling remote execution on clients not needed anymore
- L67 _public prototype_ `u32 BeginExternalProcess(const tchar* description, const tchar* breadcrumbs = TC(""));` — Report an external process just to get it visible in the trace stream/visualizer. Returns an unique id that should be sent in to EndExternalProcess
- L70 _public prototype_ `void EndExternalProcess(u32 id, u32 exitCode);`
- L73 _public prototype_ `void UpdateProgress(u32 processesTotal, u32 processesDone, u32 errorCount);` — Update progress. Will show in visualizer
- L76 _public prototype_ `void UpdateStatus(u32 statusRow, u32 statusColumn, const tchar* statusText, LogEntryType statusType, const tchar* statusLink);` — Add external status information to trace stream. Will show in visualizer
- L79 _public prototype_ `void AddProcessBreadcrumbs(u32 processId, const tchar* breadcrumbs, bool deleteOld = false);` — Add additional breadcrumbs to process. Can be done while process is running or after it is done
- L82 _public prototype_ `NetworkServer& GetServer();` — Get the network server used by this session
- L85 _public typedef_ `using NetworkTrafficProvider = Function<void(u64& outSent, u64& outReceive, u32& outConnectionCount)>;` — Additional network traffic provider. Can be used to add more network stats to trace
- L86 _public prototype_ `void RegisterNetworkTrafficProvider(u64 key, const NetworkTrafficProvider& provider);`
- L87 _public prototype_ `void UnregisterNetworkTrafficProvider(u64 key);`
- L90 _public prototype_ `bool RegisterCrossArchitectureMapping(const tchar* from, const tchar* to);` — Register mappings for cross architecture helpers (helpers with different architecture will use the mapping)
- L92 _public prototype_ `void SetOuterScheduler(Scheduler* scheduler);`
- L93 _public prototype_ `Scheduler* GetOuterScheduler();`
- L95 _public prototype_ `bool GetRemoteTraceEnabled();`
- L97 _public prototype_ `ProcessHandle GetNewestLocalProcess();`
- L98 _public prototype_ `bool WasEverConnected();`
- L103 _protected prototype_ `void OnDisconnected(const Guid& clientUid, u32 clientId);`
- L108 _protected prototype_ `bool StoreCasFile(CasKey& out, const StringKey& fileNameKey, const tchar* fileName);`
- L109 _protected prototype_ `bool WriteDirectoryTable(ClientSession& session, BinaryReader& reader, BinaryWriter& writer);`
- L110 _protected prototype_ `bool WriteNameToHashTable(BinaryReader& reader, BinaryWriter& writer, u32 requestedSize);`
- L115 _protected prototype_ `RemoteProcess* DequeueProcess(ClientSession& session, u32 sessionId, u32 clientId);`
- L116 _protected prototype_ `void OnCancelled(RemoteProcess* process);`
- L117 _protected prototype_ `void OnRaceLost(RemoteProcess& process);`
- L118 _protected prototype_ `ProcessHandle ProcessRemoved(u32 processId);`
- L120 _protected prototype_ `ProcessHandle GetProcess(u32 processId);`
- L121 _protected prototype_ `TString GetProcessDescription(u32 processId);`
- L123 _protected prototype_ `virtual bool ProcessNativeCreated(ProcessImpl& process) override;`
- L124 _protected prototype_ `virtual bool CreateFileForRead(CreateFileResponse& out, TrackWorkScope& tws, StringView fileName, StringKey fileNameKey, ProcessImpl& process, const ApplicationRules& rules) override final;`
- L125 _protected prototype_ `virtual bool GetOutputFileSizeInternal(u64& outSize, const StringKey& fileNameKey, StringView filePath) override;`
- L126 _protected prototype_ `virtual bool GetOutputFileDataInternal(void* outData, const StringKey& fileNameKey, StringView filePath, bool deleteInternalMapping) override;`
- L127 _protected prototype_ `virtual bool WriteOutputFileInternal(const StringKey& fileNameKey, StringView filePath, bool deleteInternalMapping) override;`
- L128 _protected prototype_ `virtual void FileEntryAdded(StringKey fileNameKey, u64 lastWritten, u64 size) override final;`
- L129 _protected prototype_ `virtual bool RunSpecialProgram(ProcessImpl& process, BinaryReader& reader, BinaryWriter& writer) override final;`
- L130 _protected prototype_ `virtual void PrintSessionStats(Logger& logger) override final;`
- L133 _protected prototype_ `bool WriteReceivedFile(ReceivedFile& file, RemoteProcess* process, const ConnectionInfo& connectionInfo);`
- L134 _protected prototype_ `bool WriteReceivedFiles(Vector<ReceivedFile>& receivedFiles, RemoteProcess& process, Timer& writeFilesTimer, const ConnectionInfo& connectionInfo);`
- L135 _protected prototype_ `void SkipReceivedFiles(Vector<ReceivedFile>& receivedFiles, const ConnectionInfo& connectionInfo);`
- L136 _protected prototype_ `void ReleaseReceivedFiles(Vector<ReceivedFile>& receivedFiles);`
- L138 _protected prototype_ `void TraceSessionUpdate();`
- L140 _protected prototype_ `void WriteRemoteEnvironmentVariables(BinaryWriter& writer);`
- L141 _protected prototype_ `bool InitializeNameToHashTable();`
- L144 _protected member_ `NetworkServer& m_server;`
- L145 _protected member_ `u32 m_uiLanguage;`
- L146 _protected member_ `Atomic<u32> m_maxRemoteProcessCount = ~0u;`
- L147 _protected member_ `bool m_resetCas;`
- L148 _protected member_ `bool m_remoteExecutionEnabled;`
- L149 _protected member_ `bool m_nameToHashTableEnabled;`
- L151 _protected member_ `Vector<tchar> m_remoteEnvironmentVariables;`
- L153 _protected member_ `static constexpr u8 ServiceId = SessionServiceId;`
- L155 _protected member_ `ReaderWriterLock m_remoteProcessSlotAvailableEventLock;`
- L156 _protected member_ `RemoteProcessAvailableCallback m_remoteProcessSlotAvailableEvent;`
- L158 _protected member_ `ReaderWriterLock m_remoteProcessReturnedEventLock;`
- L159 _protected member_ `Function<void(Process&)> m_remoteProcessReturnedEvent;`
- L161 _protected member_ `Function<void(ProcessImpl&)> m_nativeProcessCreatedFunc;`
- L163 _protected member_ `CriticalSection m_remoteProcessAndSessionLock;` — Can be re-entrant.
- L164 _protected member_ `List<ProcessHandle> m_queuedRemoteProcesses;`
- L165 _protected member_ `UnorderedSet<ProcessHandle> m_activeRemoteProcesses;`
- L166 _protected member_ `u32 m_finishedRemoteProcessCount = 0;`
- L167 _protected member_ `u32 m_returnedRemoteProcessCount = 0;`
- L168 _protected member_ `u32 m_availableRemoteSlotCount = 0;`
- L169 _protected member_ `u32 m_connectionCount = 0;`
- L171 _protected member_ `Futex m_binKeysLock;`
- L172 _protected member_ `CasKey m_detoursBinaryKey[2][2];` — [platform][isarm]
- L173 _protected member_ `CasKey m_agentBinaryKey[2];` — [isarm]
- L175 _protected member_ `CasKey m_stubBinaryKey[2];` — [isarm]
- L203 _protected member_ `Vector<ClientSession*> m_clientSessions;`
- L211 _protected member_ `Futex m_customCasKeysLock;`
- L212 _protected member_ `UnorderedMap<StringKey, CustomCasKey> m_customCasKeys;`
- L214 _protected member_ `UnorderedMap<StringKey, CasKey> m_nameToHashLookup;`
- L215 _protected member_ `Futex m_nameToHashLookupLock;`
- L216 _protected member_ `Atomic<bool> m_nameToHashInitialized = false;`
- L218 _protected member_ `ReaderWriterLock m_receivedFilesLock;`
- L219 _protected member_ `UnorderedMap<StringKey, CasKey> m_receivedFiles;`
- L221 _protected member_ `Futex m_fillUpOneAtTheTimeLock;`
- L223 _protected member_ `Futex m_applicationDataLock;`
- L225 _protected member_ `UnorderedMap<StringKey, ApplicationData> m_applicationData;`
- L228 _protected member_ `Vector<NetworkTrafficProviderRec> m_providers;`
- L230 _protected member_ `ReaderWriterLock m_crossArchitectureMappingsLock;`
- L232 _protected member_ `Vector<CrossArchitectureMapping> m_crossArchitectureMappings;`
- L234 _protected member_ `bool m_remoteLogEnabled = false;`
- L235 _protected member_ `bool m_remoteTraceEnabled = false;`
- L236 _protected member_ `bool m_traceIOEnabled = false;`
- L237 _protected member_ `bool m_customCasKeysEnabled = false;`
- L238 _protected member_ `bool m_useFillLock = false;`
- L240 _protected member_ `Scheduler* m_outerScheduler = nullptr;`
- L242 _protected prototype_ `SessionServer(const SessionServer&) = delete;`
- L243 _protected prototype_ `void operator=(const SessionServer&) = delete;`

#### struct `uba::SessionServer::ClientSession`  
`struct ClientSession`  
_L178-202_
- L180 _public member_ `TString name;`
- L181 _public member_ `UnorderedSet<CasKey> sentKeys;`
- L182 _public member_ `Vector<u32> processesLostRace;`
- L183 _public member_ `Futex dirTablePosLock;`
- L184 _public member_ `u32 dirTablePos = 0;`
- L185 _public member_ `u32 clientId = ~0u;`
- L186 _public member_ `u32 processSlotCount = 1;`
- L187 _public member_ `u32 usedSlotCount = 0;`
- L188 _public member_ `u64 lastPing = 0;`
- L189 _public member_ `u64 memAvail = 0;`
- L190 _public member_ `u64 memTotal = 0;`
- L191 _public member_ `u64 pingTime = 0;`
- L192 _public member_ `float cpuLoad = 0;`
- L193 _public member_ `bool connected = true;`
- L194 _public member_ `bool enabled = true;`
- L195 _public member_ `bool dedicated = false;`
- L196 _public member_ `bool abort = false;`
- L197 _public member_ `bool crashdump = false;`
- L198 _public member_ `bool hasNotification = false;`
- L199 _public member_ `bool isArm = false;`
- L200 _public member_ `bool isLinux = false;` — Only used for non-linux
- L201 _public member_ `bool remoteExecutionEnabled = true;`

#### struct `uba::SessionServer::CustomCasKey`  
`struct CustomCasKey`  
_L205-210_
- L207 _public member_ `CasKey casKey;`
- L208 _public member_ `TString workingDir;`
- L209 _public member_ `Vector<u8> trackedInputs;`

#### struct `uba::SessionServer::ApplicationData`  
`struct ApplicationData`  
_L224-224_
- L224 _public member_ `struct ApplicationData { Futex lock; Vector<u8> bytes; };`
- L224 _public member_ `struct ApplicationData { Futex lock; Vector<u8> bytes; };`

#### struct `uba::SessionServer::NetworkTrafficProviderRec`  
`struct NetworkTrafficProviderRec`  
_L227-227_
- L227 _public member_ `struct NetworkTrafficProviderRec { u64 key; NetworkTrafficProvider provider; };`
- L227 _public member_ `struct NetworkTrafficProviderRec { u64 key; NetworkTrafficProvider provider; };`

#### struct `uba::SessionServer::CrossArchitectureMapping`  
`struct CrossArchitectureMapping`  
_L231-231_
- L231 _public member_ `struct CrossArchitectureMapping { TString from; TString to; };`
- L231 _public member_ `struct CrossArchitectureMapping { TString from; TString to; };`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace uba`
- L104 _macro_ `#define UBA_SESSION_MESSAGE(x) bool Handle##x(const ConnectionInfo& connectionInfo, const WorkContext& workContext, BinaryReader& reader, BinaryWriter& writer);`

### `Source/Programs/UnrealBuildAccelerator/Common/Public/UbaSessionServerCreateInfo.h` (Public)


#### struct `uba::SessionServerCreateInfo`  
`struct SessionServerCreateInfo : SessionCreateInfo`  
_L11-26_
- inherits: `SessionCreateInfo`
- L13 _public function_ `SessionServerCreateInfo(Storage& s, NetworkServer& c, LogWriter& writer = g_consoleLogWriter) : SessionCreateInfo(s, writer), server(c)`
- L15 _public prototype_ `void Apply(const Config& config);`
- L17 _public member_ `NetworkServer& server;`
- L18 _public member_ `bool resetCas = false;`
- L19 _public member_ `bool remoteExecutionEnabled = true;`
- L20 _public member_ `bool nameToHashTableEnabled = true;`
- L21 _public member_ `bool remoteLogEnabled = false;` — If Uba is built in debug, then the logs will be sent back to server
- L22 _public member_ `bool remoteTraceEnabled = false;` — If this is true, the agents will run trace and send the .uba file back to server
- L23 _public member_ `bool traceIOEnabled = true;` — Enable IO information for storage
- L24 _public member_ `bool customCasKeysEnabled = false;` — Need to set this to true to be able to use SetCustomCasKeyFromTrackedInputs
- L25 _public member_ `bool useFillLock = true;` — Will fill one process request at the time. Useful if files that are similar are queued together

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace uba`

### `Source/Programs/UnrealBuildAccelerator/Common/Public/UbaSharedMemoryAllocator.h` (Public)


#### class `uba::SharedMemoryAllocator`  
`class SharedMemoryAllocator`  
_L23-115_
- L26 _public prototype_ `bool Init(u64 capacity, u64 commitStepSize = 16ull*1024*1024, const tchar* tempFile = TC(""), bool tempFileSparse = true);`
- L27 _public prototype_ `void Deinit(bool keepFileMapping);` — keepFileMapping can be used to just leak handle for shutdown
- L28 _public prototype_ `void Reserve(u64 size);`
- L30 _public prototype_ `operator SharedMemoryAllocatorHandle() const;`
- L31 _public prototype_ `u64 GetCapacity();`
- L32 _public prototype_ `u64 GetUsed();`
- L34 _public prototype_ `SharedMemoryHandle CreateHandle(Logger& logger, const tchar* hint, bool priority = false);` — Priority means it will have a compressable handle id
- L35 _public prototype_ `SharedMemoryHandle DuplicateHandle(SharedMemoryHandle handle, const tchar* hint);`
- L36 _public prototype_ `void ClearHandle(SharedMemoryHandle handle);`
- L37 _public prototype_ `void CloseHandle(Logger& logger, SharedMemoryHandle handle, const tchar* hint);`
- L39 _public prototype_ `void ExtendMemory(BinaryWriter& out, SharedMemoryHandle handle, u64 size, const tchar* hint = TC(""), bool zeroMemory = true);`
- L40 _public prototype_ `void ExtendMemory(SharedMemoryHandle handle, u64 size, const tchar* hint = TC(""), bool zeroMemory = true);`
- L41 _public prototype_ `void ExtendMemory(SharedMemoryView& view, SharedMemoryHandle handle, u64 size, const tchar* hint = TC(""), bool zeroMemory = true);`
- L42 _public prototype_ `void TrimMemory(SharedMemoryHandle handle, u64 usedSize);`
- L44 _public prototype_ `u8* ReserveMemory(SharedMemoryHandle handle, u64 size);`
- L45 _public prototype_ `void CommitMemory(SharedMemoryHandle handle, u64 offset, u64 size);`
- L46 _public prototype_ `void DecommitMemory(SharedMemoryHandle handle, u64 offset, u64 size);`
- L47 _public prototype_ `void UnreserveMemory(SharedMemoryHandle handle);`
- L49 _public prototype_ `u64 GetCommitted(SharedMemoryHandle handle);`
- L50 _public prototype_ `u64 GetRefCount(SharedMemoryHandle handle);`
- L51 _public prototype_ `FileMappingBackend& GetFileMappingBackend();`
- L53 _public prototype_ `void WriteViewSlices(BinaryWriter& out, SharedMemoryHandle handle, u64 offset = 0, u64 size = ~0llu);`
- L54 _public prototype_ `bool MapView(SharedMemoryView& view, SharedMemoryHandle handle, const tchar* hint, SharedMemoryMapType mapType = SharedMemoryMapType_ReadOnly, u64 offset = 0, u64 size = ~0llu);`
- L57 _public prototype_ `u8* MapView(SharedMemoryHandle handle, const tchar* hint, SharedMemoryMapType mapType = SharedMemoryMapType_ReadOnly);`
- L58 _public prototype_ `void UnmapView(SharedMemoryHandle handle, u8* memory);`
- L61 _public prototype_ `void TraceStats(Trace& trace, u32 startRow);`
- L63 _public prototype_ `SharedMemoryAllocator(Logger& logger, FileMappingBackend& fileMappingBackend);`
- L64 _public prototype_ `~SharedMemoryAllocator();`
- L67 _public prototype_ `SharedMemoryHandle RegisterExternalMapping(FileMappingHandle file);` — This is really ugly. But very contained for virtual file mappings
- L68 _public prototype_ `bool IsExternalMapping(SharedMemoryHandle handle);`
- L69 _public prototype_ `void UnmapExternalMapping(SharedMemoryHandle handle, u8* memory, u64 size);`
- L75 _private prototype_ `InternalHandle& GetHandle(SharedMemoryHandle h);`
- L76 _private prototype_ `void ReleaseHandle(SharedMemoryHandle h);`
- L77 _private prototype_ `void ExtendHandle(InternalHandle& handle, u64 size, const tchar* hint, bool zeroMemory);`
- L78 _private prototype_ `void ClearHandle(InternalHandle& handle);`
- L79 _private prototype_ `Slice AllocateNoLock(u64 desiredSize);`
- L80 _private prototype_ `void FreeNoLock(Slice slice);`
- L82 _private member_ `Logger& m_logger;`
- L83 _private member_ `FileMappingBackend& m_fileMappingBackend;`
- L85 _private member_ `u64 m_commitStepSize;`
- L86 _private member_ `FileHandle m_tempFile = InvalidFileHandle;`
- L87 _private member_ `FileMappingHandle m_fileMapping;`
- L88 _private member_ `u64 m_capacity = 0;` — Capacity is total reserved address space from system
- L89 _private member_ `u64 m_reserved = 0;` — Reserved is the amount of address space used
- L90 _private member_ `u64 m_committed = 0;` — Committed is the amount of pages in address space that has been committed
- L91 _private member_ `u8* m_memory = nullptr;`
- L93 _private member_ `Atomic<u64> m_used = 0;` — Amount of memory used through ExtendMemory
- L95 _private member_ `Futex m_lock;`
- L97 _private member_ `Map<u64, u64> m_freeMemory;` — memory slots. Key is offset, value is size
- L100 _private member_ `Set<SizeAndOffset> m_freeMemoryBySize;` — Sorted by size and then offset. To find best fit allocations
- L102 _private member_ `Atomic<u64> m_handleCount = 0;`
- L104 _private member_ `InternalHandle* m_priorityHandles[8];`
- L105 _private member_ `Atomic<u32> m_priorityHandleCounter = 0;`
- L107 _private prototype_ `SharedMemoryAllocator(const SharedMemoryAllocator&) = delete;`
- L108 _private prototype_ `SharedMemoryAllocator& operator=(const SharedMemoryAllocator&) = delete;`
- L111 _private member_ `InternalHandle* m_firstHandle = nullptr;`
- L112 _private member_ `Futex m_handleLock;`
- L113 _private member_ `CasKey m_lastSent;`

#### struct `uba::SharedMemoryAllocator::SizeAndOffset`  
`struct SizeAndOffset`  
_L99-99_
- L99 _public function_ `struct SizeAndOffset`
- L99 _public member_ `struct SizeAndOffset { u64 size; u64 offset; bool operator<(const SizeAndOffset& o) const { return size != o.size ? size < o.size : offset < o.offset; } };`
- L99 _public member_ `struct SizeAndOffset { u64 size; u64 offset; bool operator<(const SizeAndOffset& o) const { return size != o.size ? size < o.size : offset < o.offset; } };`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UBA_TRACK_SHARED_MEMORY_ALLOCATIONS 0` — Track shared memory allocations to be able to trace biggest allocations
- L14 _namespace_ `namespace uba`
- L119 _prototype_ `void GetMappingString(StringBufferBase& out, SharedMemoryHandle handle, u64 offset, bool canBeFreed);` (scope `uba`)

### `Source/Programs/UnrealBuildAccelerator/Common/Public/UbaSocket.h` (Public)


#### struct `uba::Socket`  
`struct Socket`  
_L11-11_
- L11 _public function_ `struct Socket`
- L11 _public member_ `struct Socket { u64 internal = ~0ull; bool operator==(const Socket& o) const { return internal == o.internal; } };`

#### struct `uba::SendBuf`  
`struct SendBuf`  
_L35-39_
- L37 _public member_ `u32 len;`
- L38 _public member_ `const void* data;`

#### struct `uba::RecvBuf`  
`struct RecvBuf`  
_L41-45_
- L43 _public member_ `u32 len;`
- L44 _public member_ `void* data;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace uba`
- L12 _variable_ `inline constexpr Socket InvalidSocket;` (scope `uba`)
- L15 _function_ `inline SOCKET ToPlatformSocket(Socket socket)` (scope `uba`)
- L16 _function_ `inline Socket FromPlatformSocket(SOCKET socket)` (scope `uba`)
- L18 _function_ `inline int ToPlatformSocket(Socket socket)` (scope `uba`)
- L19 _function_ `inline Socket FromPlatformSocket(int socket)` (scope `uba`)
- L24 _variable_ `inline constexpr int PollIN = 0x0001;` (scope `uba`)
- L25 _variable_ `inline constexpr int PollPRI = 0x0002;` (scope `uba`)
- L26 _variable_ `inline constexpr int PollOUT = 0x0004;` (scope `uba`)
- L27 _variable_ `inline constexpr int PollERR = 0x0008;` (scope `uba`)
- L28 _variable_ `inline constexpr int PollHUP = 0x0010;` (scope `uba`)
- L29 _variable_ `inline constexpr int PollNVAL = 0x0020;` (scope `uba`)
- L30 _variable_ `inline constexpr int PollRDNORM = 0x0040;` (scope `uba`)
- L31 _variable_ `inline constexpr int PollRDBAND = 0x0080;` (scope `uba`)
- L32 _variable_ `inline constexpr int PollWRNORM = 0x0100;` (scope `uba`)
- L33 _variable_ `inline constexpr int PollWRBAND = 0x0200;` (scope `uba`)
- L47 _prototype_ `Socket SocketCreate(int family = AF_INET, int type = SOCK_STREAM, int protocol = IPPROTO_TCP);` (scope `uba`)
- L48 _prototype_ `int SocketConnect(Socket s, const sockaddr* addr, u32 addrSize, bool isBlocking = true);` (scope `uba`)
- L49 _prototype_ `int SocketClose(Socket s);` (scope `uba`)
- L50 _prototype_ `int SocketSetBlocking(Socket s, bool blocking);` (scope `uba`)
- L51 _prototype_ `int SocketReuseAddr(Socket s);` (scope `uba`)
- L52 _prototype_ `int SocketBind(Socket s, const sockaddr* addr, u32 addrSize);` (scope `uba`)
- L53 _prototype_ `int SocketListen(Socket s);` (scope `uba`)
- L54 _prototype_ `int SocketSetKeepAlive(Socket s, int keepAliveTime, int keepAliveTimeInterval);` (scope `uba`)
- L55 _prototype_ `int SocketSetUserTimeout(Socket s, int timeoutMs);` (scope `uba`)
- L56 _prototype_ `int SocketGetLastError();` (scope `uba`)
- L57 _prototype_ `int SocketSetNoDelay(Socket s);` (scope `uba`)
- L58 _prototype_ `int SocketSetLinger(Socket s, int lingerSeconds);` (scope `uba`)
- L59 _prototype_ `int SocketSetTimeout(Socket s, int timeoutMs);` (scope `uba`)
- L60 _prototype_ `int SocketSetRecvBuf(Socket s, int size);` (scope `uba`)
- L61 _prototype_ `int SocketSetSendBuf(Socket s, int size);` (scope `uba`)
- L62 _prototype_ `int SocketSetPriority(Socket s);` (scope `uba`)
- L63 _prototype_ `int SocketPoll(Socket s, int events, int timeoutMs, int* outRevents);` (scope `uba`)
- L64 _prototype_ `int SocketPoll2(Socket s, int events, int timeoutMs, Socket wakeupSocket, int* outRevents);` (scope `uba`)
- L65 _prototype_ `Socket SocketCreateWakeupSocket();` (scope `uba`)
- L66 _prototype_ `int SocketWakeup(Socket wakeupSocket);` (scope `uba`)
- L67 _prototype_ `Socket SocketAccept(Socket s, sockaddr* outAddr, int addrLen);` (scope `uba`)
- L68 _prototype_ `int SocketRecv(Socket s, void* data, int len);` (scope `uba`)
- L69 _prototype_ `int SocketRecv2(Socket s, RecvBuf* bufs, int bufCount);` (scope `uba`)
- L70 _prototype_ `int SocketSend(Socket s, SendBuf* bufs, int bufCount);` (scope `uba`)
- L71 _prototype_ `bool SocketShouldPoll(bool* outRetry);` (scope `uba`)
- L72 _prototype_ `int SocketCheckConnect(Socket s, bool* outTimedOut);` (scope `uba`)
- L73 _prototype_ `int SocketShutdown(Socket s);` (scope `uba`)
- L74 _prototype_ `int SocketGetCongestionAlgorithm(Socket s, char* out, int outCapacity);` (scope `uba`)
- L75 _prototype_ `int SocketGetRecvBuf(Socket s, int& outSize);` (scope `uba`)
- L76 _prototype_ `int SocketGetSendBuf(Socket s, int& outSize);` (scope `uba`)

### `Source/Programs/UnrealBuildAccelerator/Common/Public/UbaSocket.inl` (Public)


#### Free symbols / members of external scopes

- L7 _function_ `Socket SocketCreate(int family, int type, int protocol)`
- L18 _function_ `int SocketConnect(Socket s, const sockaddr* addr, u32 addrSize, bool isBlocking)`
- L33 _function_ `int SocketClose(Socket s)`
- L42 _function_ `int SocketSetBlocking(Socket s, bool blocking)`
- L57 _function_ `int SocketReuseAddr(Socket s)`
- L63 _function_ `int SocketBind(Socket s, const sockaddr* addr, u32 addrSize)`
- L67 _function_ `int SocketListen(Socket s)`
- L71 _function_ `int SocketSetKeepAlive(Socket s, int keepAliveTime, int keepAliveTimeInterval)`
- L102 _function_ `int SocketSetUserTimeout(Socket s, int timeoutMs)`
- L116 _function_ `int SocketGetLastError()`
- L125 _function_ `int SocketSetNoDelay(Socket s)`
- L135 _function_ `int SocketSetLinger(Socket s, int lingerSeconds)`
- L143 _function_ `int SocketSetTimeout(Socket s, int timeoutMs)`
- L159 _function_ `int SocketSetRecvBuf(Socket s, int size)`
- L168 _function_ `int SocketSetSendBuf(Socket s, int size)`
- L177 _function_ `int SocketSetPriority(Socket s)`
- L181 _function_ `` (scope `SocketSetPriority`)
- L204 _function_ `int SocketPoll(Socket s, int events, int timeoutMs, int* outRevents)`
- L244 _function_ `int SocketPoll2(Socket s, int events, int timeoutMs, Socket wakeupSocket, int* outRevents)`
- L295 _function_ `Socket SocketCreateWakeupSocket()`
- L338 _function_ `int SocketWakeup(Socket wakeupSocket)`
- L346 _function_ `Socket SocketAccept(Socket s, sockaddr* outAddr, int addrLen)`
- L356 _function_ `int SocketRecv(Socket s, void* data, int len)`
- L361 _function_ `int SocketRecv2(Socket s, RecvBuf* bufs, int bufCount)`
- L381 _function_ `int SocketSend(Socket s, SendBuf* bufs, int bufCount)`
- L400 _function_ `bool SocketShouldPoll(bool* outRetry)`
- L412 _function_ `int SocketCheckConnect(Socket s, bool* outTimedOut)`
- L443 _function_ `int SocketShutdown(Socket s)`
- L461 _function_ `int SocketGetCongestionAlgorithm(Socket s, char* out, int outCapacity)`
- L472 _function_ `int SocketGetRecvBuf(Socket s, int& outSize)`
- L478 _function_ `int SocketGetSendBuf(Socket s, int& outSize)`

### `Source/Programs/UnrealBuildAccelerator/Common/Public/UbaSocketWin.h` (Public)


#### Free symbols / members of external scopes

- L5 _namespace_ `namespace uba`
- L9 _namespace_ `namespace impl` (scope `uba`)
- L16 _macro_ `#define SOCKET_FUNCTIONS \`
- L48 _macro_ `#define SOCKET_FUNCTION(func) decltype(impl::Socket##func)* g_socket##func##Func = impl::Socket##func;`
- L54 _function_ `Socket SocketCreate(int family, int type, int protocol)` (scope `uba`)
- L55 _function_ `int SocketConnect(Socket s, const sockaddr* addr, u32 addrSize, bool isBlocking)` (scope `uba`)
- L56 _function_ `int SocketClose(Socket s)` (scope `uba`)
- L57 _function_ `int SocketSetBlocking(Socket s, bool blocking)` (scope `uba`)
- L58 _function_ `int SocketReuseAddr(Socket s)` (scope `uba`)
- L59 _function_ `int SocketBind(Socket s, const sockaddr* addr, u32 addrSize)` (scope `uba`)
- L60 _function_ `int SocketListen(Socket s)` (scope `uba`)
- L61 _function_ `int SocketSetKeepAlive(Socket s, int keepAliveTime, int keepAliveTimeInterval)` (scope `uba`)
- L62 _function_ `int SocketSetUserTimeout(Socket s, int timeoutMs)` (scope `uba`)
- L63 _function_ `int SocketGetLastError()` (scope `uba`)
- L64 _function_ `int SocketSetNoDelay(Socket s)` (scope `uba`)
- L65 _function_ `int SocketSetLinger(Socket s, int lingerSeconds)` (scope `uba`)
- L66 _function_ `int SocketSetTimeout(Socket s, int timeoutMs)` (scope `uba`)
- L67 _function_ `int SocketSetRecvBuf(Socket s, int size)` (scope `uba`)
- L68 _function_ `int SocketSetSendBuf(Socket s, int size)` (scope `uba`)
- L69 _function_ `int SocketPoll(Socket s, int events, int timeoutMs, int* outRevents)` (scope `uba`)
- L70 _function_ `int SocketPoll2(Socket s, int events, int timeoutMs, Socket wakeupSocket, int* outRevents)` (scope `uba`)
- L71 _function_ `Socket SocketCreateWakeupSocket()` (scope `uba`)
- L72 _function_ `int SocketWakeup(Socket wakeupSocket)` (scope `uba`)
- L73 _function_ `Socket SocketAccept(Socket s, sockaddr* outAddr, int addrLen)` (scope `uba`)
- L74 _function_ `int SocketRecv(Socket s, void* data, int len)` (scope `uba`)
- L75 _function_ `int SocketRecv2(Socket s, RecvBuf* bufs, int bufCount)` (scope `uba`)
- L76 _function_ `int SocketSend(Socket s, SendBuf* bufs, int bufCount)` (scope `uba`)
- L77 _function_ `int SocketCheckConnect(Socket s, bool* outTimedOut)` (scope `uba`)
- L78 _function_ `bool SocketShouldPoll(bool* outRetry)` (scope `uba`)
- L79 _function_ `int SocketShutdown(Socket s)` (scope `uba`)
- L80 _function_ `int SocketGetCongestionAlgorithm(Socket s, char* out, int outCapacity)` (scope `uba`)
- L81 _function_ `int SocketGetRecvBuf(Socket s, int& outSize)` (scope `uba`)
- L82 _function_ `int SocketGetSendBuf(Socket s, int& outSize)` (scope `uba`)
- L83 _function_ `int SocketSetPriority(Socket s)` (scope `uba`)
- L87 _function_ `bool SocketInitWine(Logger& logger, HMODULE wineDll)` (scope `uba`)
- L89 _macro_ `#define SOCKET_FUNCTION(func) \`
- L95 _macro_ `#define SOCKET_FUNCTION(func) g_socket##func##Func = func##Func;`
- L102 _function_ `bool UsingNativeSockets()` (scope `uba`)

### `Source/Programs/UnrealBuildAccelerator/Common/Public/UbaStaticPatcher.h` (Public)


#### Free symbols / members of external scopes

- L9 _namespace_ `namespace uba`
- L28 _prototype_ `bool BinaryRequiresPatching(Logger& logger, StringView inputPath, const u8* inputData, u32 inputSize);` (scope `uba`) — Returns true if `path` is a statically-linked ELF that UBA can detour by injecting the static stub blob — i.e. either: * a Go-static binary (has internal/runtime/syscall.Syscall6 in its .symtab so the stub can hook it), OR * a glibc-static binary (has a usable .symtab AND ≥ 5 of the 9 MVP libc wrappers: __libc_open / __openat / __libc_read / __libc_write / __libc_close / __libc_lseek / __fxstat / __mmap / __access — STT_FUNC GLOBAL/WEAK, first byte not 0x0F 0x05). Returns false for everything else: dynamic ELFs (use the normal LD_PRELOAD path), non-ELFs, missing files, plain static ELFs that have neither the Go nor the glibc fingerprint (musl-static and stripped statics land here — we can't hook by name without a symtab), and any parse error. All errors are logged at Info level so this can be called speculatively on every launch.
- L46 _prototype_ `bool PatchStaticBinary(Logger& logger, StringView inputPath, const u8* inputData, u32 inputSize, StringView outputPath, StringView stubBlobPath);` (scope `uba`) — Produces a patched copy of a statically-linked ELF binary with the UBA static-detour stub embedded. Internally dispatches to the Go-static path (e_entry rewrite + Syscall6 / runtime.exit baking) or the glibc-static path (Go-style stub injection plus per-libc- wrapper JMP installation and ImportSlot stamping for the target's __errno_location). The stub blob is loaded from disk (UbaStaticStub.bin, shipped alongside UbaCli / UbaAgent). The caller is expected to have already filtered with RequiresPatching(); calling PatchBinary on a binary that doesn't pass that filter will fail. Intended call sites: - UbaCli -patchbinary=<in> -out=<out> - UbaSession::CookProcessAndIo (local/native launches) - UbaSessionServer remote-binary serving path
- L58 _prototype_ `bool IsGoStaticBinary(Logger& logger, StringView inputPath, const u8* inputData, u32 inputSize);` (scope `uba`)
- L59 _prototype_ `bool IsGlibcStaticBinary(Logger& logger, StringView inputPath, const u8* inputData, u32 inputSize);` (scope `uba`)
- L61 _prototype_ `bool PatchGlibcStaticBinary(Logger& logger, StringView inputPath, const u8* inputData, u32 inputSize, StringView outputPath, StringView stubBlobPath);` (scope `uba`)
- L62 _prototype_ `bool LooksAlreadyPatched(const u8* data, u32 size);` (scope `uba`)

### `Source/Programs/UnrealBuildAccelerator/Common/Public/UbaStats.h` (Public)


#### struct `uba::StorageStats`  
`struct StorageStats`  
_L32-51_
- L38 _public prototype_ `void Write(BinaryWriter& writer);`
- L39 _public prototype_ `void Read(BinaryReader& reader, u32 version);`
- L40 _public prototype_ `void Add(const StorageStats& other);`
- L41 _public prototype_ `void Print(Logger& logger, u64 frequency = GetFrequency());`
- L42 _public prototype_ `bool IsEmpty();`
- L43 _public prototype_ `static StorageStats* GetCurrent();`

#### enum `uba::StorageStats::(anonymous)`  
``  
_L46-50_

#### struct `uba::StorageStatsScope`  
`struct StorageStatsScope`  
_L53-60_
- L55 _public prototype_ `StorageStatsScope(StorageStats& stats);`
- L56 _public prototype_ `~StorageStatsScope();`
- L57 _public prototype_ `StorageStatsScope(const StorageStatsScope&) = delete;`
- L58 _public prototype_ `void operator=(const StorageStatsScope&) = delete;`
- L59 _public member_ `StorageStats& stats;`

#### struct `uba::SessionStats`  
`struct SessionStats`  
_L78-97_
- L84 _public prototype_ `void Write(BinaryWriter& writer);`
- L85 _public prototype_ `void Read(BinaryReader& reader, u32 version);`
- L86 _public prototype_ `void Add(const SessionStats& other);`
- L87 _public prototype_ `void Print(Logger& logger, u64 frequency = GetFrequency());`
- L88 _public prototype_ `bool IsEmpty();`
- L89 _public prototype_ `static SessionStats* GetCurrent();`

#### enum `uba::SessionStats::(anonymous)`  
``  
_L92-96_

#### struct `uba::SessionStatsScope`  
`struct SessionStatsScope`  
_L99-106_
- L101 _public prototype_ `SessionStatsScope(SessionStats& stats);`
- L102 _public prototype_ `~SessionStatsScope();`
- L103 _public prototype_ `SessionStatsScope(const SessionStatsScope&) = delete;`
- L104 _public prototype_ `void operator=(const SessionStatsScope&) = delete;`
- L105 _public member_ `SessionStats& stats;`

#### struct `uba::SessionSummaryStats`  
`struct SessionSummaryStats`  
_L121-133_
- L123 _public member_ `SessionStats stats;`
- L129 _public function_ `SessionSummaryStats() : waitMemPressure(0), killCount(0)`
- L130 _public prototype_ `void Write(BinaryWriter& writer);`
- L131 _public prototype_ `void Read(BinaryReader& reader, u32 version);`
- L132 _public prototype_ `void Print(Logger& logger, u64 frequency = GetFrequency());`

#### struct `uba::CacheFetchStats`  
`struct CacheFetchStats`  
_L144-154_
- L150 _public prototype_ `void Write(BinaryWriter& writer);`
- L151 _public prototype_ `void Read(BinaryReader& reader, u32 version);`
- L152 _public prototype_ `void Print(Logger& logger, u64 frequency = GetFrequency());`
- L153 _public prototype_ `bool IsEmpty();`

#### struct `uba::CacheSendStats`  
`struct CacheSendStats`  
_L166-176_
- L172 _public prototype_ `void Write(BinaryWriter& writer);`
- L173 _public prototype_ `void Read(BinaryReader& reader, u32 version);`
- L174 _public prototype_ `void Print(Logger& logger, u64 frequency = GetFrequency());`
- L175 _public prototype_ `bool IsEmpty();`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace uba`
- L11 _macro_ `#define UBA_STORAGE_STATS \`
- L34 _macro_ `#define UBA_STORAGE_STAT(type, var, ver) type var;`
- L47 _macro_ `#define UBA_STORAGE_STAT(type, var, ver) Bit_##var,`
- L48 _enumerator_ `UBA_STORAGE_STATS #undef UBA_STORAGE_STAT` (scope `uba::StorageStats::__anon77d509fe0103`)
- L62 _macro_ `#define UBA_SESSION_STATS \`
- L80 _macro_ `#define UBA_SESSION_STAT(type, var, ver) type var;`
- L93 _macro_ `#define UBA_SESSION_STAT(type, var, ver) Bit_##var,`
- L94 _enumerator_ `UBA_SESSION_STATS #undef UBA_SESSION_STAT` (scope `uba::SessionStats::__anon77d509fe0203`)
- L108 _macro_ `#define UBA_SESSION_SUMMARY_STATS \`
- L125 _macro_ `#define UBA_SESSION_SUMMARY_STAT(type, var) type var;`
- L135 _macro_ `#define UBA_CACHE_FETCH_STATS \`
- L146 _macro_ `#define UBA_CACHE_STAT(type, var, ver) type var;`
- L156 _macro_ `#define UBA_CACHE_SEND_STATS \`

### `Source/Programs/UnrealBuildAccelerator/Common/Public/UbaStorage.h` (Public)


#### struct `uba::MappedView2`  
`struct MappedView2 : MappedView`  
_L27-33_
- inherits: `MappedView`
- L29 _public prototype_ `MappedView2() = default;`
- L30 _public prototype_ `MappedView2(const MappedView2&) = default;`
- L31 _public function_ `MappedView2(const MappedView& v)`
- L32 _public member_ `bool isCompressed = true;`

#### class `uba::Storage`  
`class Storage`  
_L35-115_
- L38 _public function_ `virtual ~Storage()`
- L39 _public prototype_ `virtual bool StoreCompressed() const = 0;`
- L40 _public prototype_ `virtual void PrintSummary(Logger& logger) = 0;`
- L41 _public prototype_ `virtual bool Reset() = 0;`
- L42 _public prototype_ `virtual bool SaveCasTable(bool deleteIsRunningfile, bool deleteDropped = true) = 0;`
- L43 _public prototype_ `virtual u64 GetStorageCapacity() = 0;`
- L44 _public prototype_ `virtual u64 GetStorageUsed() = 0;`
- L45 _public prototype_ `virtual bool GetZone(StringBufferBase& out) = 0;`
- L46 _public function_ `virtual bool HasProxy(u32 clientId)`
- L48 _public prototype_ `virtual bool DecompressFileToMemory(const tchar* fileName, FileHandle fileHandle, u8* dest, u64 decompressedSize, const tchar* writeHint, u64 fileStartOffset) = 0;`
- L49 _public prototype_ `virtual bool DecompressMemoryToMemory(const u8* compressedData, u64 compressedSize, u8* writeData, u64 decompressedSize, const tchar* readHint, const tchar* writeHint) = 0;`
- L50 _public prototype_ `virtual bool CreateDirectory(const tchar* dir, bool* outAlreadyExists = nullptr) = 0;`
- L51 _public prototype_ `virtual bool DeleteCasForFile(const tchar* file) = 0;`
- L52 _public prototype_ `virtual bool GetFileSize(u64& outSize, const CasKey& casKey, const tchar* hint) = 0;`
- L53 _public prototype_ `virtual bool GetFileData(void* outData, const CasKey& casKey, const tchar* hint) = 0;`
- L56 _public prototype_ `virtual bool RetrieveCasFile(RetrieveResult& out, const CasKey& casKey, StringKey keyHint, const tchar* hint, FileMappingBuffer* mappingBuffer = nullptr, bool createIndependentMapping = false, u64 memoryMapAlignment = 1, bool allowProxy = true, u32 clientId = 0) = 0;`
- L58 _public prototype_ `virtual bool AddRef(const CasKey& casKey) = 0;`
- L59 _public prototype_ `virtual bool ReleaseRef(const CasKey& casKey, bool dropIfZero) = 0;`
- L62 _public prototype_ `virtual bool VerifyAndGetCachedFileInfo(CachedFileInfo& out, StringKey fileNameKey, u64 verifiedLastWriteTime, u64 verifiedSize) = 0;`
- L63 _public prototype_ `virtual bool InvalidateCachedFileInfo(StringKey fileNameKey) = 0;`
- L65 _public prototype_ `virtual bool StoreCasFile(CasKey& out, const tchar* fileName, const CasKey& casKeyOverride, bool deferCreation) = 0;`
- L66 _public prototype_ `virtual bool StoreCasFileClient(CasKey& out, StringKey fileNameKey, const tchar* fileName, SharedMemoryHandle memoryHandle, u64 memoryOffset, u64 fileSize, const tchar* hint, bool keepMappingInMemory = false, bool storeCompressed = true) = 0;`
- L67 _public prototype_ `virtual bool DropCasFile(const CasKey& casKey, bool forceDelete, const tchar* hint, bool reduceRefCount = false) = 0;`
- L68 _public prototype_ `virtual bool ReportBadCasFile(const CasKey& casKey) = 0;`
- L69 _public prototype_ `virtual bool CalculateCasKey(CasKey& out, StringKey fileNameKey, const tchar* fileName) = 0;`
- L71 _public typedef_ `using FormattingFunc = Function<bool(MemoryBlock& destData, const void* sourceData, u64 sourceSize, const tchar* hint)>;`
- L72 _public prototype_ `virtual bool CopyOrLink(const CasKey& casKey, const tchar* destination, u32 fileAttributes, bool writeCompressed = false, u32 clientId = 0, const FormattingFunc& formattingFunc = {}, bool isTemp = false, bool allowHardLink = true) = 0;`
- L73 _public prototype_ `virtual bool WritePlaceholder(const CasKey& casKey, const tchar* destination, u32 fileAttributes, u32 clientId) = 0;`
- L74 _public prototype_ `virtual bool FakeCopy(const CasKey& casKey, const tchar* destination, u64 size, u64 lastWritten, u32 fileAttributes, bool deleteExisting = true) = 0;`
- L75 _public function_ `virtual bool SkipWrite(const CasKey& casKey, u32 clientId)`
- L76 _public prototype_ `virtual bool GetCasFileName(StringBufferBase& out, const CasKey& casKey) = 0;`
- L78 _public prototype_ `virtual MappedView2 MapView(const CasKey& casKey, const tchar* hint) = 0;`
- L79 _public prototype_ `virtual void UnmapView(const MappedView& view, const tchar* hint) = 0;`
- L81 _public prototype_ `virtual void ReportFileWrite(StringKey fileNameKey, const tchar* fileName) = 0;`
- L83 _public prototype_ `virtual StorageStats& Stats() = 0;`
- L84 _public prototype_ `virtual void AddStats(StorageStats& stats) = 0;`
- L85 _public prototype_ `virtual void TraceUpdate(Trace& trace, u32 startRow) = 0;`
- L87 _public function_ `virtual void SetTrace(Trace* trace, bool detailed)`
- L88 _public function_ `virtual void Ping()`
- L90 _public prototype_ `virtual SharedMemoryAllocator& GetSharedMemory() = 0;`
- L100 _public prototype_ `virtual bool WriteCompressedFile(WriteResult& out, const tchar* from, FileHandle readHandle, u8* readMem, u64 fileSize, const tchar* toFile, const void* header, u64 headerSize, u64 lastWriteTime = 0) = 0;`
- L112 _public typedef_ `using ExternalFileMappingsProvider = Function<bool(ExternalFileMapping& out, StringKey fileNameKey, const tchar* fileName)>;`
- L113 _public function_ `virtual void RegisterExternalFileMappingsProvider(ExternalFileMappingsProvider&& provider)`
- L114 _public function_ `virtual void DeleteExternalFileMapping(StringKey fileNameKey, const tchar* fileName)`

#### struct `uba::Storage::RetrieveResult`  
`struct RetrieveResult`  
_L55-55_
- L55 _public member_ `struct RetrieveResult { CasKey casKey; u64 size = 0; MappedView2 view; };`
- L55 _public member_ `struct RetrieveResult { CasKey casKey; u64 size = 0; MappedView2 view; };`
- L55 _public member_ `struct RetrieveResult { CasKey casKey; u64 size = 0; MappedView2 view; };`

#### struct `uba::Storage::CachedFileInfo`  
`struct CachedFileInfo`  
_L61-61_
- L61 _public member_ `struct CachedFileInfo { CasKey casKey; };`

#### struct `uba::Storage::WriteResult`  
`struct WriteResult`  
_L92-99_
- L94 _public member_ `SharedMemoryHandle memoryHandle;`
- L95 _public member_ `u64 memoryOffset = InvalidValue;`
- L96 _public member_ `u64 storedSize = InvalidValue;` — Stored size of the destination
- L97 _public member_ `u64 sourceStoredSize = InvalidValue;` — Stored size of the source used to write compressed file. Can be both compressed and uncompressed
- L98 _public member_ `bool isIndependent = false;`

#### struct `uba::Storage::ExternalFileMapping`  
`struct ExternalFileMapping`  
_L102-111_
- L104 _public member_ `SharedMemoryHandle handle;` — Will close handle so provider needs to DuplicateHandle when setting it in ExternalFileMapping
- L105 _public member_ `u64 offset = 0;`
- L106 _public member_ `u64 size = 0;`
- L107 _public member_ `u64 lastWriteTime = 0;`
- L108 _public member_ `u64 storedSize = InvalidValue;` — Size stored on disk. Can be compressed or uncompressed
- L109 _public member_ `bool createIndependentMapping = false;`
- L110 _public member_ `bool dropCasAfterUse = false;`

#### struct `uba::StorageCreateInfo`  
`struct StorageCreateInfo`  
_L117-148_
- L119 _public prototype_ `StorageCreateInfo(const tchar* rootDir_, LogWriter& w, WorkManager& wm);`
- L121 _public prototype_ `void Apply(const Config& config);`
- L123 _public member_ `LogWriter& writer;`
- L124 _public member_ `WorkManager& workManager;`
- L125 _public member_ `const tchar* rootDir;`
- L126 _public member_ `u64 casCapacityBytes = 20llu * 1024 * 1024 * 1024;`
- L127 _public member_ `u32 fileEntryTableWipeThreshold = 1'000'000;`
- L128 _public member_ `u32 maxParallelCopyOrLink = 1000;`
- L129 _public member_ `u32 deleteCasBatchSize = 10;`
- L130 _public member_ `bool storeCompressed = true;`
- L131 _public member_ `bool manuallyHandleOverflow = false;`
- L132 _public member_ `bool asyncUnmapViewOfFile = true;`
- L133 _public member_ `bool writeToDisk = true;`
- L134 _public member_ `bool allowDeleteVerified = false;`
- L135 _public member_ `bool allowDeferredDeletes = true;`
- L136 _public member_ `bool allowMemfd = true;`
- L137 _public member_ `bool skipCleanupOnShutdown = false;`
- L138 _public member_ `bool allowUnDropOfCas = true;`
- L139 _public member_ `bool sideStepWineForSharedMemory = true;`
- L140 _public member_ `u64 sharedMemoryCapacity = 1024ull*1024*1024*1024;` — 1TB
- L141 _public member_ `u64 sharedMemoryCommitSize = 64ull*1024*1024;`
- L142 _public member_ `u64 sharedMemoryInitialCommit = 0ull;`
- L143 _public member_ `const tchar* sharedMemoryTempFile = TC("");`
- L144 _public member_ `bool sharedMemoryTempFileSparse = true;`
- L145 _public member_ `MutexHandle exclusiveMutex = InvalidMutexHandle;` — Set this to hand over pre-exclusive access to storage. Storage will release mutex on shutdown
- L146 _public member_ `u8 casCompressor = 0;`
- L147 _public member_ `u8 casCompressionLevel = 0;`

#### class `uba::StorageImpl`  
`class StorageImpl : public Storage`  
_L153-375_
- inherits: `Storage`
- L156 _public prototype_ `StorageImpl(const StorageCreateInfo& info, const tchar* logPrefix = TC("UbaS`
- L157 _public prototype_ `virtual ~StorageImpl();`
- L159 _public prototype_ `bool LoadCasTable(bool logStats = true, bool alwaysCheckAllFiles = false, bool* outWasTerminated = nullptr);`
- L160 _public prototype_ `bool CheckCasContent(Vector<TString>* badFiles = nullptr);`
- L161 _public prototype_ `bool CheckFileTable(const tchar* searchPath);`
- L162 _public prototype_ `const tchar* GetTempPath();`
- L164 _public prototype_ `virtual bool SaveCasTable(bool deleteIsRunningfile, bool deleteDropped = true) override final;`
- L165 _public prototype_ `virtual u64 GetStorageCapacity() override final;`
- L166 _public prototype_ `virtual u64 GetStorageUsed() override final;`
- L167 _public prototype_ `virtual bool GetZone(StringBufferBase& out) override;`
- L168 _public prototype_ `virtual bool Reset() override final;`
- L169 _public prototype_ `bool DeleteAllCas();`
- L170 _public function_ `bool IsCasTableLoaded() const`
- L172 _public function_ `virtual bool StoreCompressed() const final`
- L173 _public prototype_ `virtual void PrintSummary(Logger& logger) override;`
- L175 _public prototype_ `virtual bool DecompressFileToMemory(const tchar* fileName, FileHandle fileHandle, u8* dest, u64 decompressedSize, const tchar* writeHint, u64 fileStartOffset) override final;`
- L176 _public prototype_ `virtual bool CreateDirectory(const tchar* dir, bool* outAlreadyExists = nullptr) override final;`
- L177 _public prototype_ `virtual bool DeleteCasForFile(const tchar* file) override final;`
- L178 _public prototype_ `virtual bool GetFileSize(u64& outSize, const CasKey& casKey, const tchar* hint) override final;`
- L179 _public prototype_ `virtual bool GetFileData(void* outData, const CasKey& casKey, const tchar* hint) override final;`
- L180 _public prototype_ `virtual bool RetrieveCasFile(RetrieveResult& out, const CasKey& casKey, StringKey keyHint, const tchar* hint, FileMappingBuffer* mappingBuffer = nullptr, bool createIndependentMapping = false, u64 memoryMapAlignment = 1, bool allowProxy = true, u32 clientId = 0) override;`
- L181 _public prototype_ `virtual bool AddRef(const CasKey& casKey) override final;`
- L182 _public prototype_ `virtual bool ReleaseRef(const CasKey& casKey, bool dropIfZero) override final;`
- L183 _public prototype_ `virtual bool VerifyAndGetCachedFileInfo(CachedFileInfo& out, StringKey fileNameKey, u64 verifiedLastWriteTime, u64 verifiedSize) override final;`
- L184 _public prototype_ `virtual bool InvalidateCachedFileInfo(StringKey fileNameKey) override final;`
- L185 _public prototype_ `virtual bool StoreCasFile(CasKey& out, const tchar* fileName, const CasKey& casKeyOverride, bool deferCreation) override;`
- L186 _public prototype_ `virtual bool StoreCasFileClient(CasKey& out, StringKey fileNameKey, const tchar* fileName, SharedMemoryHandle memoryHandle, u64 memoryOffset, u64 fileSize, const tchar* hint, bool keepMappingInMemory = false, bool storeCompressed = true) override;`
- L187 _public prototype_ `virtual bool DropCasFile(const CasKey& casKey, bool forceDelete, const tchar* hint, bool reduceRefCount = false) override final;`
- L188 _public prototype_ `virtual bool ReportBadCasFile(const CasKey& casKey) override final;`
- L189 _public prototype_ `virtual bool CalculateCasKey(CasKey& out, StringKey fileNameKey, const tchar* fileName) override final;`
- L190 _public prototype_ `virtual bool CopyOrLink(const CasKey& casKey, const tchar* destination, u32 fileAttributes, bool writeCompressed = false, u32 clientId = 0, const FormattingFunc& formattingFunc = {}, bool isTemp = false, bool allowHardLink = true) override;`
- L191 _public prototype_ `virtual bool WritePlaceholder(const CasKey& casKey, const tchar* destination, u32 fileAttributes, u32 clientId) override;`
- L192 _public prototype_ `virtual bool FakeCopy(const CasKey& casKey, const tchar* destination, u64 size, u64 lastWritten, u32 fileAttributes, bool deleteExisting = true) override final;`
- L193 _public prototype_ `virtual bool GetCasFileName(StringBufferBase& out, const CasKey& casKey) override;`
- L194 _public prototype_ `virtual MappedView2 MapView(const CasKey& casKey, const tchar* hint) override;`
- L195 _public prototype_ `virtual void UnmapView(const MappedView& view, const tchar* hint) override final;`
- L196 _public prototype_ `virtual SharedMemoryAllocator& GetSharedMemory() override final;`
- L198 _public prototype_ `virtual void ReportFileWrite(StringKey fileNameKey, const tchar* fileName) override final;`
- L200 _public prototype_ `virtual StorageStats& Stats() final;`
- L201 _public prototype_ `virtual void AddStats(StorageStats& stats) override final;`
- L202 _public prototype_ `virtual void TraceUpdate(Trace& trace, u32 startRow) override final;`
- L208 _public prototype_ `virtual bool StoreCasFile(CasKey& out, const tchar* fileName, const CasKey& casKeyOverride, bool deferCreation, CasEntry** outEntry);`
- L209 _public prototype_ `virtual bool HasCasFile(const CasKey& casKey, CasEntry** out, bool useMapping, bool allowFail);`
- L211 _public prototype_ `bool EnsureCasFile(const CasKey& casKey, const tchar* fileName);`
- L212 _public prototype_ `CasKey CalculateCasKey(const tchar* fileName, FileHandle fileHandle, u64 fileSize, bool storeCompressed);`
- L213 _public prototype_ `CasKey CalculateCasKey(const u8* fileMem, u64 fileSize, bool storeCompressed);`
- L214 _public prototype_ `bool StoreCasKey(CasKey& out, const tchar* fileName, const CasKey& casKeyOverride);`
- L215 _public prototype_ `bool StoreCasKey(CasKey& out, const StringKey& fileNameKey, const tchar* fileName, const CasKey& casKeyOverride, bool showErrors = true);`
- L216 _public prototype_ `bool IsFileVerified(const StringKey& fileNameKey);`
- L217 _public prototype_ `void ReportFileInfoWeak(const StringKey& fileNameKey, u64 verifiedLastWriteTime, u64 verifiedSize);`
- L218 _public prototype_ `bool HasBeenSeen(const CasKey& casKey);`
- L219 _public prototype_ `void ReleaseCasEntry(CasEntry& casEntry, bool dropIfZero);`
- L220 _public prototype_ `void ReleaseCasEntryNoLock(CasEntry& casEntry, bool dropIfZero);`
- L227 _public prototype_ `virtual void RegisterExternalFileMappingsProvider(ExternalFileMappingsProvider&& provider) override final;`
- L228 _public prototype_ `virtual void DeleteExternalFileMapping(StringKey fileNameKey, const tchar* fileName) override final;`
- L229 _public prototype_ `virtual bool WriteCompressedFile(WriteResult& out, const tchar* from, FileHandle readHandle, u8* readMem, u64 fileSize, const tchar* toFile, const void* header, u64 headerSize, u64 lastWriteTime = 0) final;`
- L230 _public prototype_ `bool WriteCasFileNoCheck(WriteCasResult& out, const StringKey& fileNameKey, const tchar* fileName, const CasKey& casKey, const tchar* casFile, bool storeCompressed, bool useMapping, DeferredSource* deferredSource, bool allowFail);`
- L231 _public prototype_ `bool WriteCasFile(WriteCasResult& out, const tchar* fileName, const CasKey& casKey, bool useMapping, DeferredSource* deferredSouirce, bool allowFail);`
- L232 _public prototype_ `bool VerifyExisting(bool& outReturnValue, CasEntryWriteLock& casEntryLock, const CasKey& casKey, CasEntry& casEntry, StringBufferBase& casFile);`
- L233 _public prototype_ `bool AddCasFile(StringKey fileNameKey, const tchar* fileName, const CasKey& casKey, bool deferCreation, u64 fileSize, u64 lastWriteTime, CasEntry** outEntry, bool dropCasAfterUse);`
- L234 _public prototype_ `void CasEntryAccessed(const CasKey& casKey);`
- L235 _public prototype_ `virtual bool IsDisallowedPath(const tchar* fileName);`
- L236 _public prototype_ `virtual bool DecompressMemoryToMemory(const u8* compressedData, u64 compressedSize, u8* writeData, u64 decompressedSize, const tchar* readHint, const tchar* writeHint) override final;`
- L238 _public prototype_ `void CasEntryAccessed(CasEntry& entry);`
- L239 _public prototype_ `void CasEntryWritten(CasEntry& entry, u64 size);`
- L240 _public prototype_ `void CasEntryDeleted(CasEntry& entry, u64 size);`
- L241 _public prototype_ `void AttachEntry(CasEntry& entry);`
- L242 _public prototype_ `void DetachEntry(CasEntry& entry);`
- L243 _public prototype_ `void TraverseAllCasFiles(const tchar* dir, const Function<void(const StringBufferBase& fullPath, const DirectoryEntry& e)>& func, bool allowParallel = false);`
- L244 _public prototype_ `void TraverseAllCasFiles(const Function<void(const CasKey& key, u64 size)>& func, bool allowParallel = false);`
- L245 _public prototype_ `bool CheckAllCasFiles(u64 checkContentOfFilesNewerThanTime = ~u64(0));`
- L246 _public prototype_ `void HandleOverflow(UnorderedSet<CasKey>* outDeletedFiles);`
- L247 _public prototype_ `void DeleteOldestCasEntries();`
- L249 _public prototype_ `static MutexHandle GetExclusiveAccess(Logger& logger, const StringView& rootDir, bool reportError);`
- L250 _public prototype_ `bool DeleteIsRunningFile();`
- L251 _public prototype_ `bool TouchIsRunningFile();`
- L254 _public prototype_ `FileEntry& GetOrCreateFileEntry(const StringKey& fileNameKey);`
- L255 _public prototype_ `CasEntry& GetOrCreateCasEntry(const CasKey& casKey);`
- L256 _public prototype_ `bool GetFileEntry(FileEntry*& out, const tchar* file);`
- L258 _public member_ `MutableLogger m_logger;`
- L259 _public member_ `WorkManager& m_workManager;`
- L260 _public member_ `SharedMemoryAllocator m_sharedMemory;`
- L261 _public member_ `BufferCache m_bufferSlots;`
- L263 _public member_ `StringBuffer<> m_rootDir;`
- L264 _public member_ `StringBuffer<> m_tempPath;`
- L266 _public member_ `ReaderWriterLock m_fileTableLookupLock;`
- L280 _public member_ `UnorderedMap<StringKey, FileEntry> m_fileTableLookup;`
- L282 _public member_ `ReaderWriterLock m_casLookupLock;`
- L322 _public member_ `UnorderedMap<CasKey, CasEntry> m_casLookup;`
- L323 _public member_ `UnorderedSet<CasKey>* m_trackedDeletes = nullptr;`
- L324 _public member_ `Futex m_accessLock;`
- L325 _public member_ `CasEntry* m_newestAccessed = nullptr;`
- L326 _public member_ `CasEntry* m_oldestAccessed = nullptr;`
- L327 _public member_ `u64 m_casTotalBytes = 0;`
- L328 _public member_ `u64 m_casQueuedDeleteBytes = 0;`
- L329 _public member_ `u64 m_casMaxBytes = 0;`
- L330 _public member_ `u64 m_casCapacityBytes = 0;`
- L331 _public member_ `u64 m_casEvictedBytes = 0;`
- L332 _public member_ `u32 m_casEvictedCount = 0;`
- L333 _public member_ `u64 m_casDroppedBytes = 0;`
- L334 _public member_ `u32 m_casDroppedCount = 0;`
- L335 _public member_ `u32 m_fileEntryTableWipeThreshold = 0;`
- L336 _public member_ `u32 m_deleteCasBatchSize;`
- L337 _public member_ `bool m_overflowReported = false;`
- L338 _public member_ `bool m_storeCompressed = false;`
- L339 _public member_ `bool m_manuallyHandleOverflow = false;`
- L340 _public member_ `bool m_asyncUnmapViewOfFile = true;`
- L341 _public member_ `bool m_allowDeleteVerified = false;`
- L342 _public member_ `bool m_allowDeferredDeletes = true;`
- L343 _public member_ `bool m_skipCleanupOnShutdown = false;`
- L344 _public member_ `bool m_allowUnDropOfCas = true;`
- L345 _public member_ `bool m_writeToDisk;`
- L347 _public member_ `MutexHandle m_exclusiveMutex = InvalidMutexHandle;`
- L349 _public member_ `ExternalFileMappingsProvider m_externalFileMappingsProvider;`
- L351 _public member_ `Bottleneck m_maxParallelCopyOrLinkBottleneck;`
- L353 _public member_ `Futex m_casTableLoadSaveLock;`
- L354 _public member_ `bool m_casTableLoaded = false;`
- L355 _public member_ `u32 m_casTableVersion = 0;`
- L357 _public member_ `FileMappingBuffer m_casDataBuffer;`
- L359 _public member_ `Futex m_deferredCasCreationLookupLock;`
- L361 _public typedef_ `using NameToCas = UnorderedMap<StringKey, DeferredSource>;`
- L363 _public member_ `UnorderedMap<CasKey, DeferredCasCreation> m_deferredCasCreationLookup;`
- L364 _public member_ `NameToCas m_deferredCasCreationLookupByName;`
- L366 _public member_ `DirectoryCache m_dirCache;`
- L368 _public member_ `u8 m_casCompressor;`
- L369 _public member_ `u8 m_casCompressionLevel;`
- L371 _public member_ `StorageStats m_stats;`
- L373 _public prototype_ `StorageImpl(const StorageImpl&) = delete;`
- L374 _public prototype_ `void operator=(const StorageImpl&) = delete;`

#### struct `uba::StorageImpl::WriteCasResult`  
`struct WriteCasResult : WriteResult`  
_L222-225_
- inherits: `WriteResult`
- L224 _public member_ `bool dropAfterUse = false;`

#### struct `uba::StorageImpl::FileEntry`  
`struct FileEntry`  
_L267-279_
- L269 _public member_ `Futex lock;`
- L270 _public member_ `CasKey casKey;`
- L271 _public member_ `u64 size = 0;`
- L272 _public member_ `u64 lastWritten = 0;`
- L273 _public member_ `bool verified = false;`
- L274 _public member_ `bool isTemp = false;`
- L277 _public member_ `bool isExecutable = false;`

#### struct `uba::StorageImpl::CasEntryReadLock`  
`struct CasEntryReadLock`  
_L284-290_
- L286 _public prototype_ `CasEntryReadLock(CasEntry& e);`
- L287 _public prototype_ `~CasEntryReadLock();`
- L288 _public member_ `CasEntry& entry;`
- L289 _public member_ `bool active;`

#### struct `uba::StorageImpl::CasEntryWriteLock`  
`struct CasEntryWriteLock`  
_L292-300_
- L294 _public prototype_ `CasEntryWriteLock(CasEntry& e);`
- L295 _public prototype_ `~CasEntryWriteLock();`
- L296 _public prototype_ `void Enter();`
- L297 _public prototype_ `void Leave();`
- L298 _public member_ `CasEntry& entry;`
- L299 _public member_ `bool active;`

#### struct `uba::StorageImpl::CasEntry`  
`struct CasEntry`  
_L302-320_
- L304 _public function_ `CasEntry(const CasKey& k) : key(k)`
- L305 _public member_ `ReaderWriterLock internalLock;`
- L306 _public member_ `CasKey key;`
- L307 _public member_ `CasEntry* prevAccessed = nullptr;`
- L308 _public member_ `CasEntry* nextAccessed = nullptr;`
- L309 _public member_ `u64 size = 0;` — Stored size of cas entry. Can be both compressed or uncompressed
- L310 _public member_ `Atomic<u16> refCount = 0;` — This is set while file is being read or queued to be written over network
- L311 _public member_ `bool verified = false;` — This flag needs to be set for below flags to be reliable. if this is false below flags are assumptions
- L312 _public member_ `bool exists = false;` — File exists on disk
- L313 _public member_ `bool dropped = false;` — This file is not seen anymore. will be deleted when refCount reaches zero or during shutdown
- L314 _public member_ `bool beingWritten = false;` — This is set while file is being written (when coming from network)..
- L315 _public member_ `bool disallowed = false;` — This is set if cas is created from disallowed file
- L317 _public member_ `SharedMemoryHandle memoryHandle;`
- L318 _public member_ `u64 memoryOffset = 0;`
- L319 _public member_ `u64 memorySize = 0;`

#### struct `uba::StorageImpl::DeferredSource`  
`struct DeferredSource`  
_L360-360_
- L360 _public member_ `struct DeferredSource { CasKey key; TString fileName; u64 fileSize = InvalidValue; u64 lastWriteTime = 0; bool manualDelete = false; };`
- L360 _public member_ `struct DeferredSource { CasKey key; TString fileName; u64 fileSize = InvalidValue; u64 lastWriteTime = 0; bool manualDelete = false; };`
- L360 _public member_ `struct DeferredSource { CasKey key; TString fileName; u64 fileSize = InvalidValue; u64 lastWriteTime = 0; bool manualDelete = false; };`
- L360 _public member_ `struct DeferredSource { CasKey key; TString fileName; u64 fileSize = InvalidValue; u64 lastWriteTime = 0; bool manualDelete = false; };`
- L360 _public member_ `struct DeferredSource { CasKey key; TString fileName; u64 fileSize = InvalidValue; u64 lastWriteTime = 0; bool manualDelete = false; };`

#### struct `uba::StorageImpl::DeferredCasCreation`  
`struct DeferredCasCreation`  
_L362-362_
- L362 _public member_ `struct DeferredCasCreation { Futex lock; List<StringKey> sources; u32 refCount = 0; };`
- L362 _public member_ `struct DeferredCasCreation { Futex lock; List<StringKey> sources; u32 refCount = 0; };`
- L362 _public member_ `struct DeferredCasCreation { Futex lock; List<StringKey> sources; u32 refCount = 0; };`

#### Free symbols / members of external scopes

- L16 _macro_ `#define UBA_TRACK_IS_EXECUTABLE !PLATFORM_WINDOWS`
- L18 _namespace_ `namespace uba`
- L25 _externvar_ `extern CasKey EmptyFileKey;` (scope `uba`)
- L150 _variable_ `static constexpr u64 BufferSlotSize = 16*1024*1024;` (scope `uba`)
- L151 _variable_ `static constexpr u64 BufferSlotHalfSize = BufferSlotSize/2;` (scope `uba`) — This must be three times a msg size or more.

### `Source/Programs/UnrealBuildAccelerator/Common/Public/UbaStorageClient.h` (Public)


#### struct `uba::StorageClientCreateInfo`  
`struct StorageClientCreateInfo : StorageCreateInfo`  
_L15-37_
- inherits: `StorageCreateInfo`
- L17 _public function_ `StorageClientCreateInfo(NetworkClient& c, const tchar* rootDir_) : StorageCreateInfo(rootDir_, c.GetLogWriter(), c), client(c)`
- L19 _public prototype_ `void Apply(const Config& config);`
- L21 _public member_ `NetworkClient& client;`
- L22 _public member_ `const tchar* zone = TC("");`
- L23 _public member_ `u16 proxyPort = DefaultStorageProxyPort;`
- L24 _public member_ `const tchar* proxyAddress = TC("");`
- L25 _public member_ `bool sendCompressed = true;`
- L26 _public member_ `bool allowProxy = true;`
- L27 _public member_ `bool sendOneBigFileAtTheTime = true;`
- L28 _public member_ `bool fileParallelSend = false;`
- L29 _public member_ `bool checkExistsOnServer = false;` — There is no point having this enabled if server is not writing received cas files to disk (which is default)
- L30 _public member_ `bool resendCas = false;` — Will try to send created file everytime even if the cas has been seen before
- L32 _public member_ `u32 proxyConnectionCount = 4;`
- L33 _public member_ `GetProxyBackendCallback* getProxyBackendCallback = nullptr;`
- L34 _public member_ `void* getProxyBackendUserData = nullptr;`
- L35 _public member_ `StartProxyCallback* startProxyCallback = nullptr;`
- L36 _public member_ `void* startProxyUserData = nullptr;`

#### class `uba::StorageClient`  
`class StorageClient final : public StorageImpl`  
_L40-102_
- inherits: `StorageImpl`
- L43 _public prototype_ `StorageClient(const StorageClientCreateInfo& info);`
- L44 _public prototype_ `~StorageClient();`
- L46 _public prototype_ `bool Start();`
- L48 _public prototype_ `bool IsUsingProxy();`
- L49 _public prototype_ `void StopProxy();`
- L51 _public typedef_ `using DirVector = Vector<TString>;`
- L52 _public prototype_ `bool PopulateCasFromDirs(const DirVector& directories, u32 workerCount, const Function<bool()>& shouldExit = {});`
- L54 _public prototype_ `virtual bool GetCasFileName(StringBufferBase& out, const CasKey& casKey) override;`
- L56 _public prototype_ `virtual MappedView2 MapView(const CasKey& casKey, const tchar* hint) override;`
- L58 _public prototype_ `virtual bool GetZone(StringBufferBase& out) override;`
- L59 _public prototype_ `virtual bool RetrieveCasFile(RetrieveResult& out, const CasKey& casKey, StringKey keyHint, const tchar* hint, FileMappingBuffer* mappingBuffer = nullptr, bool createIndependentMapping = false, u64 memoryMapAlignment = 1, bool allowProxy = true, u32 clientId = 0) override;`
- L60 _public prototype_ `virtual bool StoreCasFile(CasKey& out, const tchar* fileName, const CasKey& casKeyOverride, bool deferCreation) override;`
- L61 _public prototype_ `virtual bool StoreCasFileClient(CasKey& out, StringKey fileNameKey, const tchar* fileName, SharedMemoryHandle mappingFile, u64 mappingOffset, u64 fileSize, const tchar* hint, bool keepMappingInMemory = false, bool storeCompressed = true) override;`
- L62 _public prototype_ `virtual bool HasCasFile(const CasKey& casKey, CasEntry** out, bool useMapping, bool allowFail) override;`
- L63 _public prototype_ `virtual void Ping() override;`
- L64 _public prototype_ `virtual void PrintSummary(Logger& logger) override;`
- L67 _private prototype_ `bool PopulateCasFromDirsRecursive(const tchar* dir, WorkManager& workManager, UnorderedSet<u64>& seenIds, Futex& seenIdsLock, const Function<bool()>& shouldExit);`
- L69 _private member_ `NetworkClient& m_client;`
- L70 _private member_ `bool m_sendCompressed;`
- L71 _private member_ `bool m_allowProxy;`
- L72 _private member_ `bool m_sendOneBigFileAtTheTime;`
- L73 _private member_ `bool m_fileParallelSend;`
- L74 _private member_ `bool m_checkExistsOnServer;`
- L75 _private member_ `bool m_resendCas;`
- L77 _private member_ `Guid m_storageServerUid;`
- L79 _private member_ `TString m_zone;`
- L81 _private member_ `ReaderWriterLock m_localStorageFilesLock;`
- L83 _private member_ `UnorderedMap<CasKey, LocalFile> m_localStorageFiles;`
- L85 _private member_ `Futex m_sendOneAtTheTimeLock;`
- L86 _private member_ `Futex m_retrieveOneBatchAtTheTimeLock;`
- L88 _private member_ `static constexpr u8 ServiceId = StorageServiceId;`
- L91 _private member_ `Futex m_proxyClientLock;`
- L92 _private member_ `ProxyClient* m_proxyClient = nullptr;`
- L93 _private member_ `u64 m_proxyClientKeepAliveTime = 0;`
- L95 _private member_ `GetProxyBackendCallback* m_getProxyBackendCallback = nullptr;`
- L96 _private member_ `void* m_getProxyBackendUserData = nullptr;`
- L97 _private member_ `StartProxyCallback* m_startProxyCallback = nullptr;`
- L98 _private member_ `void* m_startProxyUserData = nullptr;`
- L99 _private member_ `u32 m_proxyConnectionCount;`
- L100 _private member_ `u16 m_proxyPort = 0;`
- L101 _private member_ `TString m_proxyAddress;`

#### struct `uba::StorageClient::LocalFile`  
`struct LocalFile`  
_L82-82_
- L82 _public function_ `struct LocalFile`
- L82 _public member_ `struct LocalFile { CasEntry casEntry; TString fileName; Event hasBeenSent; LocalFile() : casEntry(CasKeyZero) {} };`
- L82 _public member_ `struct LocalFile { CasEntry casEntry; TString fileName; Event hasBeenSent; LocalFile() : casEntry(CasKeyZero) {} };`
- L82 _public member_ `struct LocalFile { CasEntry casEntry; TString fileName; Event hasBeenSent; LocalFile() : casEntry(CasKeyZero) {} };`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace uba`
- L12 _typedef_ `using StartProxyCallback = bool(void* userData, u16 port, const Guid& storageServerUid);` (scope `uba`)
- L13 _typedef_ `using GetProxyBackendCallback = NetworkBackend&(void* userData, const tchar* proxyHost);` (scope `uba`)

### `Source/Programs/UnrealBuildAccelerator/Common/Public/UbaStorageProxy.h` (Public)


#### struct `uba::StorageProxyCreateInfo`  
`struct StorageProxyCreateInfo`  
_L22-32_
- L24 _public member_ `NetworkServer& server;`
- L25 _public member_ `NetworkClient& client;`
- L26 _public member_ `Guid storageServerUid;`
- L27 _public member_ `const tchar* name = TC("");`
- L28 _public member_ `StorageImpl* localStorage = nullptr;`
- L29 _public member_ `bool useLocalStorage = false;` — Use local storage to populate proxy
- L31 _public prototype_ `void Apply(Config& config, const tchar* tableName = TC("Stor`

#### class `uba::StorageProxy`  
`class StorageProxy`  
_L34-117_
- L37 _public prototype_ `StorageProxy(const StorageProxyCreateInfo& info);`
- L38 _public prototype_ `~StorageProxy();`
- L39 _public prototype_ `void PrintSummary();`
- L41 _public prototype_ `u32 GetActiveFetchCount();`
- L44 _protected prototype_ `u16 PopId();`
- L45 _protected prototype_ `void PushId(u16 id);`
- L46 _protected prototype_ `bool HandleMessage(const ConnectionInfo& connectionInfo, const WorkContext& workContext, MessageInfo& messageInfo, BinaryReader& reader, BinaryWriter& writer);`
- L47 _protected prototype_ `bool HandleConnect(const ConnectionInfo& connectionInfo, BinaryReader& reader, BinaryWriter& writer);`
- L50 _protected prototype_ `bool HandleFetchBegin(const ConnectionInfo& connectionInfo, const WorkContext& workContext, MessageInfo& messageInfo, BinaryReader& reader, BinaryWriter& writer);`
- L51 _protected prototype_ `void HandleFetchBeginReceived(BeginMessage& m, bool error);`
- L54 _protected prototype_ `bool HandleFetchSegment(const ConnectionInfo& connectionInfo, const WorkContext& workContext, MessageInfo& messageInfo, BinaryReader& reader, BinaryWriter& writer);`
- L55 _protected prototype_ `void HandleFetchSegmentReceived(SegmentMessage& mif);`
- L57 _protected prototype_ `bool HandleDefault(MessageInfo& messageInfo, BinaryReader& reader, BinaryWriter& writer);`
- L60 _protected prototype_ `bool GetFileFromLocalStorage(u32 clientId, const CasKey& casKey, FileEntry& file, ScopedFutex& fileLock);`
- L61 _protected prototype_ `bool SendFetchBeginResponse(u32 clientId, FileEntry& file, BinaryWriter& writer, bool writeData = true);`
- L62 _protected prototype_ `bool UpdateFetch(u32 clientId, u16 fetchId, u64 segmentSize);`
- L63 _protected prototype_ `bool SendEnd(const CasKey& key);`
- L65 _protected member_ `static constexpr u8 ServiceId = StorageServiceId;`
- L67 _protected member_ `NetworkServer& m_server;`
- L68 _protected member_ `NetworkClient& m_client;`
- L69 _protected member_ `StorageImpl* m_localStorage;`
- L71 _protected member_ `MutableLogger m_logger;`
- L73 _protected member_ `Guid m_storageServerUid;`
- L75 _protected member_ `TString m_name;`
- L77 _protected member_ `Atomic<u32> m_inProcessClientId = 0;`
- L97 _protected member_ `Futex m_filesLock;`
- L98 _protected member_ `UnorderedMap<CasKey, FileEntry> m_files;`
- L108 _protected member_ `ReaderWriterLock m_activeFetchesLock;`
- L109 _protected member_ `UnorderedMap<u16, ActiveFetch> m_activeFetches;`
- L111 _protected member_ `ReaderWriterLock m_largeFileLock;`
- L113 _protected member_ `Vector<u16> m_availableIds;`
- L114 _protected member_ `u16 m_availableIdsHigh = 1;`
- L116 _protected member_ `bool m_useLocalStorage;`

#### struct `uba::StorageProxy::FileEntry`  
`struct FileEntry`  
_L79-95_
- L81 _public member_ `Futex lock;`
- L82 _public member_ `u8* memory = nullptr;`
- L83 _public member_ `u64 size = 0;`
- L84 _public member_ `Atomic<u64> received = 0;`
- L85 _public member_ `CasKey casKey;`
- L86 _public member_ `u32 trackId = 0;`
- L87 _public member_ `u16 fetchId = 0;`
- L88 _public member_ `bool storeCompressed = false;`
- L89 _public member_ `bool sendEnd = false;`
- L90 _public member_ `bool error = false;`
- L91 _public member_ `bool disallowed = false;`
- L92 _public member_ `bool available = false;`
- L93 _public member_ `BeginMessage* beginMessage = nullptr;`
- L94 _public member_ `Vector<SegmentMessage*> segmentMessages;`

#### struct `uba::StorageProxy::ActiveFetch`  
`struct ActiveFetch`  
_L100-106_
- L102 _public member_ `FileEntry* file = nullptr;`
- L103 _public member_ `u64 fetchedSize = 0;`
- L104 _public member_ `u32 clientId = ~0u;`
- L105 _public member_ `u32 connectionId = 0;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace uba`

### `Source/Programs/UnrealBuildAccelerator/Common/Public/UbaStorageServer.h` (Public)


#### struct `uba::StorageServerCreateInfo`  
`struct StorageServerCreateInfo : StorageCreateInfo`  
_L12-24_
- inherits: `StorageCreateInfo`
- L14 _public function_ `StorageServerCreateInfo(NetworkServer& s, const tchar* rootDir_, LogWriter& writer) : StorageCreateInfo(rootDir_, writer, s), server(s)`
- L16 _public prototype_ `void Apply(const Config& config);`
- L18 _public member_ `NetworkServer& server;`
- L19 _public member_ `bool allowHintAsFallback = true;` — Will fallback to file system to recalculate cas if cas content does not exist anymore
- L20 _public member_ `bool writeReceivedCasFilesToDisk = false;` — Write received files to disk. This is only useful if we expect same file to be written multiple times (requires deterministic outputs ofc)
- L21 _public member_ `bool createIndependentMappings = true;` — Set to true if we want every store to end up in its own file mapping. This will use more memory but makes it possible to delete files
- L22 _public member_ `bool dropIndependentMappingsOnCopy = true;` — Will drop independent mappings once they have been copyorlink to destination
- L23 _public member_ `const tchar* zone = TC("");`

#### class `uba::StorageServer`  
`class StorageServer final : public StorageImpl`  
_L26-171_
- inherits: `StorageImpl`
- L29 _public prototype_ `StorageServer(const StorageServerCreateInfo& info);`
- L30 _public prototype_ `~StorageServer();`
- L32 _public prototype_ `bool RegisterDisallowedPath(const tchar* path);`
- L35 _public function_ `NetworkServer& GetServer()` — Get the network server used by this session
- L39 _public prototype_ `void WaitForActiveWork();`
- L40 _public prototype_ `bool WaitForCasFile(const CasKey& casKey, const tchar* hint, u32 clientId = 0);`
- L42 _public prototype_ `virtual bool CopyOrLink(const CasKey& casKey, const tchar* destination, u32 fileAttributes, bool writeCompressed = false, u32 clientId = 0, const FormattingFunc& formattingFunc = {}, bool isTemp = false, bool allowHardLink = true) override;`
- L43 _public prototype_ `virtual bool WritePlaceholder(const CasKey& casKey, const tchar* destination, u32 fileAttributes, u32 clientId) override;`
- L44 _public prototype_ `virtual bool SkipWrite(const CasKey& casKey, u32 clientId) override;`
- L48 _protected prototype_ `virtual bool GetZone(StringBufferBase& out) override;`
- L49 _protected prototype_ `virtual bool RetrieveCasFile(RetrieveResult& out, const CasKey& casKey, StringKey keyHint, const tchar* hint, FileMappingBuffer* mappingBuffer = nullptr, bool createIndependentMapping = false, u64 memoryMapAlignment = 1, bool allowProxy = true, u32 clientId = 0) override;`
- L50 _protected prototype_ `virtual bool IsDisallowedPath(const tchar* fileName) override;`
- L51 _protected prototype_ `virtual void SetTrace(Trace* trace, bool detailed) override;`
- L52 _protected prototype_ `virtual bool HasProxy(u32 clientId) override;`
- L54 _protected prototype_ `void OnDisconnected(u32 clientId);`
- L55 _protected prototype_ `void ReleaseActiveRefCount(const CasKey& casKey, u32 clientId);`
- L56 _protected prototype_ `void UpdateWaitEntries(const CasKey& casKey, bool success);`
- L57 _protected prototype_ `bool HandleMessage(const ConnectionInfo& connectionInfo, const WorkContext& workContext, u8 messageType, BinaryReader& reader, BinaryWriter& writer);`
- L58 _protected prototype_ `bool WaitForWritten(CasEntry& casEntry, CasEntryWriteLock& casEntryLock, const ConnectionInfo& connectionInfo, const tchar* hint);`
- L59 _protected prototype_ `bool VerifyExists(bool& outExists, CasEntry& casEntry, CasEntryWriteLock& casEntryLock, const CasKey& casKey);`
- L60 _protected prototype_ `bool GetProxy(BinaryWriter& writer, u32 clientId, bool writeCasHeader);`
- L62 _protected prototype_ `u16 PopId();`
- L63 _protected prototype_ `void PushId(u16 id);`
- L66 _protected prototype_ `void GetProxyName(StringBufferBase& out, const Info& info);`
- L68 _protected member_ `NetworkServer& m_server;`
- L69 _protected member_ `bool m_traceFetch = false;`
- L70 _protected member_ `bool m_traceStore = false;`
- L72 _protected member_ `Guid m_uid;`
- L74 _protected member_ `static constexpr u8 ServiceId = StorageServiceId;`
- L77 _protected member_ `Futex m_waitEntriesLock;`
- L86 _protected member_ `UnorderedMap<CasKey, WaitEntry> m_waitEntries;`
- L105 _protected member_ `ReaderWriterLock m_activeStoresLock;`
- L106 _protected member_ `UnorderedMap<u16, ActiveStore> m_activeStores;`
- L129 _protected member_ `ReaderWriterLock m_activeFetchesLock;`
- L130 _protected member_ `UnorderedMap<u16, ActiveFetch> m_activeFetches;`
- L131 _protected member_ `Atomic<u32> m_activeUnmap = 0;`
- L133 _protected member_ `ReaderWriterLock m_activeRefCountsLock;`
- L134 _protected member_ `UnorderedMap<u32, List<CasEntry*>> m_activeRefCounts;`
- L136 _protected member_ `Futex m_availableIdsLock;`
- L137 _protected member_ `Vector<u16> m_availableIds;`
- L138 _protected member_ `u16 m_availableIdsHigh = 1;`
- L148 _protected member_ `ReaderWriterLock m_proxiesLock;`
- L149 _protected member_ `UnorderedMap<StringKey, ProxyEntry> m_proxies;`
- L151 _protected member_ `TString m_zone;`
- L160 _protected member_ `ReaderWriterLock m_connectionInfoLock;`
- L161 _protected member_ `UnorderedMap<u32, Info> m_connectionInfo;`
- L163 _protected member_ `Trace* m_trace = nullptr;`
- L165 _protected member_ `Vector<TString> m_disallowedPaths;`
- L167 _protected member_ `bool m_allowHintAsFallback;`
- L168 _protected member_ `bool m_writeReceivedCasFilesToDisk;`
- L169 _protected member_ `bool m_createIndependentMappings;`
- L170 _protected member_ `bool m_dropIndependentMappingsOnCopy;`

#### struct `uba::StorageServer::WaitEntry`  
`struct WaitEntry`  
_L79-85_
- L81 _public function_ `WaitEntry() : done(EventResetType_Manual)`
- L82 _public member_ `Event done;`
- L83 _public member_ `bool success = false;`
- L84 _public member_ `u32 refCount = 0;`

#### struct `uba::StorageServer::ActiveStore`  
`struct ActiveStore`  
_L89-103_
- L91 _public member_ `u32 clientId = ~0u;`
- L92 _public member_ `MappedView mappedView;`
- L93 _public member_ `FileAccessor* fileAccessor = nullptr;`
- L94 _public member_ `CasEntry* casEntry = nullptr;`
- L95 _public member_ `Atomic<u64> totalWritten = 0;`
- L96 _public member_ `Atomic<u64> recvCasTime = 0;`
- L97 _public member_ `u64 fileSize = 0;`
- L98 _public member_ `u64 actualSize = 0;`
- L101 _public member_ `TString hint;`

#### struct `uba::StorageServer::ActiveFetch`  
`struct ActiveFetch`  
_L109-128_
- L111 _public member_ `u32 clientId = ~0u;`
- L112 _public member_ `Atomic<u64> left = 0;`
- L113 _public member_ `CasEntry* casEntry;`
- L114 _public member_ `Atomic<u64> sendCasTime = 0;`
- L116 _public member_ `FileHandle readFileHandle = InvalidFileHandle;`
- L117 _public member_ `FileMappingHandle fileMappingHandle;`
- L118 _public member_ `MappedView mappedView;`
- L119 _public member_ `const u8* memoryBegin = nullptr;`
- L120 _public member_ `const u8* memoryPos = nullptr;`
- L121 _public member_ `bool ownsMapping = false;`
- L124 _public member_ `TString hint;`
- L127 _public prototype_ `void Release(StorageServer& server, const tchar* reason);`

#### struct `uba::StorageServer::ProxyEntry`  
`struct ProxyEntry`  
_L140-147_
- L142 _public member_ `u32 clientId = ~0u;`
- L143 _public member_ `TString zone;`
- L144 _public member_ `TString host;`
- L145 _public member_ `u16 port = 0;`
- L146 _public member_ `UnorderedSet<u32> failedClients;`

#### struct `uba::StorageServer::Info`  
`struct Info`  
_L153-159_
- L155 _public member_ `TString zone;`
- L156 _public member_ `TString internalAddress;`
- L157 _public member_ `u64 storageSize = 0;`
- L158 _public member_ `u16 proxyPort = 0;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UBA_TRACK_FETCH_STORE_HINTS 0`
- L10 _namespace_ `namespace uba`

### `Source/Programs/UnrealBuildAccelerator/Common/Public/UbaStorageUtils.h` (Public)


#### struct `uba::FileSender`  
`struct FileSender`  
_L33-47_
- L35 _public prototype_ `bool SendFileCompressed(const CasKey& casKey, const tchar* fileName, const u8* sourceMem, u64 sourceSize, const tchar* hint);`
- L37 _public member_ `Logger& m_logger;`
- L38 _public member_ `NetworkClient& m_client;`
- L39 _public member_ `BufferCache& m_bufferSlots;`
- L40 _public member_ `StorageStats& m_stats;`
- L41 _public member_ `Futex& m_sendOneAtTheTimeLock;`
- L42 _public member_ `u8 m_casCompressor = DefaultCompressor;`
- L43 _public member_ `u8 m_casCompressionLevel = DefaultCompressionLevel;`
- L44 _public member_ `bool m_sendOneBigFileAtTheTime = true;`
- L45 _public member_ `bool m_parallelSend = false;`
- L46 _public member_ `u64 m_bytesSent = 0;`

#### struct `uba::FileFetcher`  
`struct FileFetcher`  
_L51-63_
- L53 _public prototype_ `bool RetrieveFile(Logger& logger, NetworkClient& client, const CasKey& casKey, const tchar* destination, bool writeCompressed, MemoryBlock* destinationMem = nullptr, u32 attributes = DefaultAttributes());`
- L55 _public member_ `BufferCache& m_bufferSlots;`
- L56 _public member_ `StorageStats& m_stats;`
- L57 _public member_ `StringBuffer<> m_tempPath;`
- L58 _public member_ `bool m_errorOnFail = true;`
- L60 _public member_ `u64 lastWritten = 0;`
- L61 _public member_ `u64 sizeOnDisk = 0;`
- L62 _public member_ `u64 bytesReceived = 0;`

#### struct `uba::LinearWriter`  
`struct LinearWriter`  
_L67-72_
- L69 _public prototype_ `virtual bool Write(const void* data, u64 dataLen) = 0;`
- L70 _public prototype_ `virtual u64 GetWritten() = 0;`
- L71 _public prototype_ `virtual const tchar* GetHint() = 0;`

#### struct `uba::CompressWriter`  
`struct CompressWriter`  
_L76-94_
- L78 _public prototype_ `CompressWriter(Logger& l, SharedMemoryAllocator& a, BufferCache& bs, WorkManager& wm, StorageStats& s, u8 cc = DefaultCompressor, u8 ccl = DefaultCompressionLevel, bool avof = false);`
- L80 _public prototype_ `bool CompressToFile(u64& outCompressedSize, const tchar* from, FileHandle readHandle, u8* readMem, u64 fileSize, const tchar* toFile, const void* header, u64 headerSize, u64 lastWriteTime, const tchar* tempPath);`
- L81 _public prototype_ `bool CompressToMapping(SharedMemoryHandle& outMappingHandle, u64& outMappingSize, u8* readMem, u64 fileSize, const tchar* hint);`
- L82 _public prototype_ `bool CompressToMappingFromFile(SharedMemoryHandle& outMappingHandle, u64& outMappingSize, FileHandle readHandle, u64 fileSize, const tchar* hint);`
- L83 _public prototype_ `bool CompressFromMem(LinearWriter& destination, u32 workCount, const u8* uncompressedData, u64 fileSize, u64 maxUncompressedBlock, u64& totalWritten);`
- L84 _public prototype_ `bool CompressFromMemOrFile(LinearWriter& destination, const tchar* from, FileHandle readHandle, u8* readMem, u64 fileSize);`
- L86 _public member_ `Logger& m_logger;`
- L87 _public member_ `SharedMemoryAllocator& m_allocator;`
- L88 _public member_ `BufferCache& m_bufferSlots;`
- L89 _public member_ `WorkManager& m_workManager;`
- L90 _public member_ `StorageStats& m_stats;`
- L91 _public member_ `u8 m_casCompressor;`
- L92 _public member_ `u8 m_casCompressionLevel;`
- L93 _public member_ `bool m_asyncUnmapViewOfFile;`

#### struct `uba::LinearWriterFile`  
`struct LinearWriterFile final : public LinearWriter`  
_L98-106_
- inherits: `LinearWriter`
- L100 _public prototype_ `LinearWriterFile(FileAccessor& f);`
- L101 _public prototype_ `virtual bool Write(const void* data, u64 dataLen) override;`
- L102 _public prototype_ `virtual u64 GetWritten() override;`
- L103 _public prototype_ `virtual const tchar* GetHint() override;`
- L104 _public member_ `FileAccessor& file;`
- L105 _public member_ `u64 written = 0;`

#### struct `uba::LinearWriterMem`  
`struct LinearWriterMem final : public LinearWriter`  
_L110-119_
- inherits: `LinearWriter`
- L112 _public prototype_ `LinearWriterMem(u8* d, u64 c);`
- L113 _public prototype_ `virtual bool Write(const void* data, u64 dataLen) override;`
- L114 _public prototype_ `virtual u64 GetWritten() override;`
- L115 _public prototype_ `virtual const tchar* GetHint() override;`
- L116 _public member_ `u8* pos;`
- L117 _public member_ `u64 size;`
- L118 _public member_ `u64 capacity;`

#### struct `uba::DecompressWriter`  
`struct DecompressWriter`  
_L123-133_
- L125 _public prototype_ `bool DecompressMemoryToMemory(const u8* compressedData, u64 compressedSize, u8* writeData, u64 decompressedSize, const tchar* readHint, const tchar* writeHint);`
- L126 _public prototype_ `bool DecompressMemoryToFile(const u8* compressedData, FileAccessor& destination, u64 decompressedSize, bool useNoBuffering);`
- L127 _public prototype_ `bool DecompressFileToMemory(const tchar* fileName, FileHandle fileHandle, u8* dest, u64 decompressedSize, const tchar* writeHint, u64 fileStartOffset);`
- L129 _public member_ `Logger& m_logger;`
- L130 _public member_ `BufferCache& m_bufferSlots;`
- L131 _public member_ `WorkManager& m_workManager;`
- L132 _public member_ `StorageStats& m_stats;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace uba`
- L21 _variable_ `static constexpr u8 DefaultCompressor = OodleLZ_Compressor_Kraken;` (scope `uba`)
- L22 _variable_ `static constexpr u8 DefaultCompressionLevel = OodleLZ_CompressionLevel_SuperFast;` (scope `uba`)
- L24 _prototype_ `u8 GetCompressor(const tchar* str);` (scope `uba`)
- L25 _prototype_ `u8 GetCompressionLevel(const tchar* str);` (scope `uba`)
- L27 _prototype_ `CasKey CalculateCasKey(const u8* fileMem, u64 fileSize, bool storeCompressed, WorkManager* workManager, const tchar* hint);` (scope `uba`)
- L28 _prototype_ `bool SendBatchMessages(Logger& logger, NetworkClient& client, u16 fetchId, u8* slot, u64 capacity, u64 left, u32 messageMaxSize, u32& readIndex, u32& responseSize, const Function<bool()>& runInWaitFunc = {}, const tchar* hint = TC(""), u32* outError = nullptr, const Function<bool(u64)>& progressFunc = {});` (scope `uba`)
- L29 _prototype_ `bool SendFile(Logger& logger, NetworkClient& client, WorkManager* workManager, const CasKey& casKey, const u8* sourceMem, u64 sourceSize, const tchar* hint);` (scope `uba`)

### `Source/Programs/UnrealBuildAccelerator/Common/Public/UbaThread.h` (Public)


#### class `uba::Thread`  
`class Thread`  
_L17-46_
- L20 _public prototype_ `Thread();`
- L21 _public prototype_ `Thread(Function<u32()>&& func, const tchar* description = nullptr);`
- L22 _public prototype_ `~Thread();`
- L23 _public prototype_ `void Start(Function<u32()>&& func, const tchar* description = nullptr);`
- L24 _public prototype_ `bool Wait(u32 milliseconds = ~0u, Event* wakeupEvent = nullptr);`
- L25 _public prototype_ `bool IsInside() const;`
- L26 _public function_ `void* GetNativeHandle() const`
- L29 _private member_ `Function<u32()> m_func;`
- L30 _private member_ `void* m_handle = nullptr;`
- L31 _private member_ `ReaderWriterLock m_funcLock;`
- L34 _private member_ `Event m_finished;`
- L38 _private member_ `Thread* m_next = nullptr;`
- L39 _private member_ `Thread* m_prev = nullptr;`
- L42 _private prototype_ `Thread(const Thread&) = delete;`
- L43 _private prototype_ `void operator=(const Thread&) = delete;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UBA_TRACK_THREADS 0`
- L11 _namespace_ `namespace uba`
- L14 _typedef_ `using TraverseThreadFunc = Function<void(u32 tid, void** callstack, u32 callstackCount, const tchar* description)>;` (scope `uba`)
- L15 _typedef_ `using TraverseThreadErrorFunc = Function<void(const StringView& error)>;` (scope `uba`)
- L48 _prototype_ `bool AlternateThreadGroupAffinity(void* nativeThreadHandle);` (scope `uba`)
- L52 _prototype_ `bool DistributeProcessSoft(void* nativeProcessHandle, void* nativeMainThreadHandle);` (scope `uba`) — Distribute a process across processor groups via CPU sets + ideal-processor hint. Returns false pre-Win10-1607 / when CpuSet APIs are unavailable; caller falls back to GROUP_AFFINITY.
- L54 _prototype_ `bool TraverseAllThreads(const TraverseThreadFunc& func, const TraverseThreadErrorFunc& errorFunc);` (scope `uba`)

### `Source/Programs/UnrealBuildAccelerator/Common/Public/UbaTrace.h` (Public)


#### enum `uba::TraceType`  
`enum TraceType : u8`  
_L63-68_
- L66 _public enumerator_ `UBA_TRACE_TYPES #undef UBA_TRACE_TYPE`

#### class `uba::Trace`  
`class Trace final : public WorkTracker`  
_L75-203_
- inherits: `WorkTracker`
- L78 _public prototype_ `Trace(LogWriter& logWriter);`
- L79 _public prototype_ `~Trace();`
- L81 _public prototype_ `bool StartWriteAndThread(const tchar* namedTrace, u64 traceMemCapacity, bool logStart, const tchar* channelName = TC("Defa`
- L83 _public prototype_ `void StartThread();`
- L84 _public prototype_ `void StopThread();`
- L86 _public prototype_ `void SetThreadUpdateCallback(Function<void()>&& callback, u32 traceIntervalMs = 500);`
- L89 _public prototype_ `bool StartWrite(const tchar* namedTrace, u64 traceMemCapacity, const tchar* channelName = TC("Defa`
- L92 _public prototype_ `bool Write(const tchar* writeFileName, bool writeSummary);` — Writes the current state of the trace to the specified output file without stopping anything
- L95 _public prototype_ `bool StopWrite(const tchar* writeFileName);` — Stops the trace and writes it to the specified output file. This releases the internal memory buffer.
- L98 _public function_ `const TString& GetNamedTrace()`
- L99 _public function_ `bool IsWriting() const`
- L100 _public function_ `TraceChannel& GetChannel()`
- L102 _public prototype_ `void SessionAdded(u32 sessionId, u32 clientId, StringView name, StringView machineId);`
- L103 _public prototype_ `void SessionInfo(u32 sessionId, StringView info);`
- L104 _public prototype_ `void SessionUpdate(u32 sessionId, u32 connectionCount, u64 send, u64 recv, u64 lastPing, u64 memAvail, u64 memTotal, float cpuLoad);`
- L105 _public prototype_ `void SessionNotification(u32 sessionId, const tchar* text);`
- L106 _public prototype_ `void SessionSummary(u32 sessionId, const u8* data, u64 dataSize);`
- L107 _public prototype_ `void SessionDisconnect(u32 sessionId);`
- L108 _public prototype_ `void ProcessAdded(u32 sessionId, u32 processId, StringView description, StringView breadcrumbs);`
- L109 _public prototype_ `void ProcessEnvironmentUpdated(u32 processId, StringView reason, u32 prevExitCode, const u8* prevStats, u64 prevStatsSize, StringView breadcrumbs);`
- L110 _public prototype_ `void ProcessExited(u32 processId, u32 exitCode, const u8* data, u64 dataSize, const Vector<ProcessLogLine>& logLines);`
- L111 _public prototype_ `void ProcessExited(u32 processId, u32 exitCode);`
- L112 _public prototype_ `void ProcessReturned(u32 processId, StringView reason);`
- L113 _public prototype_ `void ProcessAddBreadcrumbs(u32 processId, StringView breadcrumbs, bool deleteOld);`
- L114 _public prototype_ `void ProcessRace(u32 processId, u32 remoteProcess);`
- L115 _public prototype_ `void ProxyCreated(u32 clientId, const tchar* proxyName);`
- L116 _public prototype_ `void ProxyUsed(u32 clientId, const tchar* proxyName);`
- L117 _public prototype_ `void FileFetchLight(u32 clientId, const CasKey& key, u64 fileSize);`
- L118 _public prototype_ `void FileFetchBegin(u32 clientId, const CasKey& key, StringView hint);`
- L119 _public prototype_ `void FileFetchSize(u32 clientId, const CasKey& key, u64 size);`
- L120 _public prototype_ `void FileFetchEnd(u32 clientId, const CasKey& key);`
- L121 _public prototype_ `void FileStoreBegin(u32 clientId, const CasKey& key, u64 size, StringView hint, bool detailed);`
- L122 _public prototype_ `void FileStoreEnd(u32 clientId, const CasKey& key);`
- L123 _public prototype_ `void WorkBegin(u32 workIndex, StringView desc, const Color& color);`
- L124 _public prototype_ `void WorkHint(u32 workIndex, StringView hint, u64 startTime);`
- L125 _public prototype_ `void WorkEnd(u32 workIndex);`
- L126 _public prototype_ `void ProgressUpdate(u32 processesTotal, u32 processesDone, u32 errorCount);`
- L127 _public prototype_ `void StatusUpdate(u32 statusRow, u32 statusColumn, StringView statusText, LogEntryType statusType, StringView statusLink = {});`
- L128 _public prototype_ `u32 StringAdd(StringView string);`
- L129 _public prototype_ `void StatusUpdate2(u32 statusRow, u32 statusColumn, u32 stringId);`
- L130 _public prototype_ `void DriveUpdate(const tchar drive, u8 busyPercent, u32 readCount, u64 readBytes, u32 writeCount, u64 writeBytes);`
- L131 _public prototype_ `void RemoteExecutionDisabled();`
- L132 _public prototype_ `void SchedulerUpdate(bool spawnPaused);`
- L133 _public prototype_ `void SchedulerKillProcess(u32 processId, StringView reason);`
- L135 _public prototype_ `void CacheBeginFetch(u32 fetchId, const tchar* description);`
- L136 _public prototype_ `void CacheEndFetch(u32 fetchId, bool success, const u8* data, u64 dataSize);`
- L137 _public prototype_ `void CacheBeginWrite(u32 processId);`
- L138 _public prototype_ `void CacheEndWrite(u32 processId, bool success, const u8* data, u64 dataSize);`
- L139 _public prototype_ `void CacheSummary(const u8* data, u64 dataSize);`
- L141 _public prototype_ `void TaskBegin(u32 processId, StringView description, StringView details, const Color& color);`
- L142 _public prototype_ `void TaskHint(u32 processId, StringView hint);`
- L143 _public prototype_ `void TaskEnd(u32 processId, bool success);`
- L145 _public prototype_ `void TableUpdate(u32 name, u32 rowCharWidth, u32 rowMaxCount, const u32* items, u32 itemCount);`
- L147 _public prototype_ `virtual u32 TrackWorkStart(const StringView& desc, const Color& color) final override;`
- L148 _public prototype_ `virtual void TrackWorkHint(u32 id, const StringView& hint, u64 startTime = 0) final override;`
- L149 _public prototype_ `virtual void TrackWorkEnd(u32 id) final override;`
- L151 _public prototype_ `void WriteSessionSummary(const Function<void(Logger& logger)>& summaryFunc);`
- L152 _public prototype_ `static void WriteSummaryText(BinaryWriter& writer, const Function<void(Logger& logger)>& summaryFunc);`
- L154 _public prototype_ `float UpdateCpuLoad();`
- L159 _public prototype_ `void PublishIfQuiet();` — Backstop publish hook. Called from SessionServer::TraceSessionUpdate so the size header keeps advancing under steady write pressure even when no single writer happens to be the last-out.
- L163 _public prototype_ `u32 GetPublishedSize();` — Snapshot of the published size header. Drives PublishIfQuiet first so callers streaming the trace to remote consumers see a fresh value.
- L167 _private prototype_ `void ThreadLoop();`
- L168 _private prototype_ `void FreeMemory();`
- L169 _private prototype_ `bool CommitTo(u64 endPosition);` — Slow path. Caller must hold m_memoryLock.
- L170 _private prototype_ `void PublishHeaderTo(u64 desired);`
- L171 _private prototype_ `u32 AddString(StringView string);`
- L173 _private member_ `LoggerWithWriter m_logger;`
- L174 _private member_ `TString m_namedTrace;`
- L175 _private member_ `TraceChannel m_channel;`
- L176 _private member_ `Futex m_memoryLock;` — Only held during the page-commit slow path.
- L177 _private member_ `FileMappingHandle m_memoryHandle;`
- L178 _private member_ `u8* m_memoryBegin = nullptr;`
- L179 _private member_ `Atomic<u64> m_memoryReserved = 0;`
- L180 _private member_ `Atomic<u64> m_memoryCommitted = 0;`
- L181 _private member_ `Atomic<u64> m_firstAbortPos = ~u64(0);`
- L182 _private member_ `Atomic<u32> m_inflightWriters = 0;`
- L183 _private member_ `u64 m_memoryCapacity = 0;`
- L184 _private member_ `u64 m_startTime = ~u64(0);`
- L186 _private member_ `Futex m_stringsLock;`
- L187 _private member_ `UnorderedMap<StringKey, u32> m_strings;`
- L189 _private member_ `Atomic<u32> m_workCounter = 0;`
- L191 _private member_ `Futex m_threadCallbackLock;`
- L192 _private member_ `Function<void()> m_threadCallback;`
- L193 _private member_ `u32 m_threadIntervalMs = 500;`
- L194 _private member_ `Event m_threadEvent;`
- L195 _private member_ `Thread m_thread;`
- L197 _private member_ `u64 m_previousTotalCpuTime = 0;`
- L198 _private member_ `u64 m_previousIdleCpuTime = 0;`
- L199 _private member_ `float m_cpuLoad = 0;`

#### struct `uba::OwnerInfo`  
`struct OwnerInfo`  
_L207-211_
- L209 _public member_ `const tchar* id;`
- L210 _public member_ `u32 pid;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace uba`
- L18 _macro_ `#define UBA_TRACE_TYPES \`
- L65 _macro_ `#define UBA_TRACE_TYPE(name) TraceType_##name,`
- L70 _variable_ `static constexpr u32 TraceVersion = 53;` (scope `uba`)
- L71 _variable_ `static constexpr u32 TraceReadCompatibilityVersion = 6;` (scope `uba`)
- L213 _prototype_ `const OwnerInfo& GetOwnerInfo();` (scope `uba`)

### `Source/Programs/UnrealBuildAccelerator/Common/Public/UbaTraceChannel.h` (Public)


#### class `uba::TraceChannel`  
`class TraceChannel`  
_L15-48_
- L18 _public prototype_ `TraceChannel(Logger& logger);`
- L19 _public prototype_ `~TraceChannel();`
- L21 _public prototype_ `bool Init(const tchar* channelName = TC("Defa`
- L22 _public prototype_ `void Deinit();`
- L23 _public prototype_ `bool Write(const tchar* traceName, const tchar* ifMatching = nullptr);`
- L24 _public prototype_ `bool Read(StringBufferBase& outTraceName);`
- L25 _public prototype_ `bool IsInitialized();`
- L30 _public prototype_ `bool StartListening();` — Register that the current process is actively listening on this channel. The registration is held for the lifetime of the TraceChannel and is automatically released by the OS if the process exits.
- L33 _public prototype_ `bool IsListenerActive();` — True if some process has called StartListening on this channel and is still alive.
- L35 _public member_ `Logger& m_logger;`
- L38 _public member_ `TString m_channelFile;`
- L39 _public member_ `TString m_listenerFile;`
- L40 _public member_ `struct timespec m_lastModified;`
- L42 _public member_ `TString m_channelName;`
- L43 _public member_ `MutexHandle m_mutex = InvalidMutexHandle;`
- L44 _public member_ `MutexHandle m_listenerMutex = InvalidMutexHandle;`
- L45 _public member_ `FileMappingHandle m_memHandle;`
- L46 _public member_ `void* m_mem = nullptr;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UBA_USE_TRACE_CHANNEL_FILE !PLATFORM_WINDOWS`
- L11 _namespace_ `namespace uba`

### `Source/Programs/UnrealBuildAccelerator/Common/Public/UbaWorkManager.h` (Public)


#### class `uba::WorkTracker`  
`class WorkTracker`  
_L32-38_
- L35 _public prototype_ `virtual u32 TrackWorkStart(const StringView& desc, const Color& color) = 0;`
- L36 _public prototype_ `virtual void TrackWorkHint(u32 id, const StringView& hint, u64 startTime = 0) = 0;`
- L37 _public prototype_ `virtual void TrackWorkEnd(u32 id) = 0;`

#### struct `uba::WorkContext`  
`struct WorkContext`  
_L42-46_
- L44 _public member_ `TrackWorkScope& tracker;`
- L45 _public member_ `Thread* thread = nullptr;`

#### enum `uba::WorkPriority`  
`enum WorkPriority : u8`  
_L52-57_
- L54 _public enumerator_ `WorkPriority_High`
- L55 _public enumerator_ `WorkPriority_Normal`
- L56 _public enumerator_ `WorkPriority_Low`

#### class `uba::WorkManager`  
`class WorkManager : public WorkTracker`  
_L61-81_
- inherits: `WorkTracker`
- L64 _public prototype_ `virtual void AddWork(WorkFunction&& work, u32 count, const tchar* desc, const Color& color = ColorWork, WorkPriority priority = WorkPriority_Normal, Bottleneck* bottleneck = nullptr) = 0;`
- L65 _public prototype_ `virtual u32 GetWorkerCount() = 0;`
- L66 _public prototype_ `virtual void DoWork(u32 count = 1) = 0;`
- L67 _public prototype_ `virtual bool FlushWork(u32 timeoutMs = 0) = 0;`
- L69 _public prototype_ `u32 TrackWorkStart(const StringView& desc, const Color& color);`
- L70 _public prototype_ `void TrackWorkHint(u32 id, const StringView& hint, u64 startTime = 0);`
- L71 _public prototype_ `void TrackWorkEnd(u32 id);`
- L73 _public prototype_ `void SetWorkTracker(WorkTracker* workTracker);`
- L74 _public function_ `WorkTracker* GetWorkTracker()`
- L77 _public prototype_ `template<u32 BatchSize = 1, typename TContainer, typename TFunc> void ParallelFor(u32 workCount, TContainer& container, TFunc&& func, const StringView& description = AsView(TC("")), WorkPriority priority = WorkPriority_Normal, Bottleneck* bottleneck = nullptr);`
- L80 _protected member_ `Atomic<WorkTracker*> m_workTracker = nullptr;`
- L158 _function_ `template<u32 BatchSize, typename TContainer, typename TFunc> void WorkManager::ParallelFor(u32 workCount, TContainer& container, TFunc&& func, const StringView& description, WorkPriority priority, Bottleneck* bottleneck)`

#### struct `uba::Work`  
`struct Work`  
_L85-85_
- L85 _public member_ `struct Work { WorkFunction func; Bottleneck* bottleneck; TString desc; Work* next; };`
- L85 _public member_ `struct Work { WorkFunction func; Bottleneck* bottleneck; TString desc; Work* next; };`
- L85 _public member_ `struct Work { WorkFunction func; Bottleneck* bottleneck; TString desc; Work* next; };`
- L85 _public member_ `struct Work { WorkFunction func; Bottleneck* bottleneck; TString desc; Work* next; };`

#### struct `uba::WorkQueue`  
`struct WorkQueue`  
_L87-101_
- L89 _public prototype_ `~WorkQueue();`
- L90 _public prototype_ `void Enqueue(WorkFunction&& func, u32 count, const tchar* desc, const Color& color, WorkPriority priority, Bottleneck* bottleneck, bool trackWork);`
- L91 _public prototype_ `Work* Dequeue(BottleneckTicket& ticket);`
- L92 _public prototype_ `void Finish(Work* work, BottleneckTicket& ticket);`
- L93 _public prototype_ `bool IsEmpty();`
- L95 _public prototype_ `bool IsEmptyNoLock();`
- L97 _public member_ `Futex lock;`
- L98 _public member_ `Work* first[3] = { 0 };`
- L99 _public member_ `Work* last[3] = { 0 };`
- L100 _public member_ `Work* free = nullptr;`

#### class `uba::WorkManagerImpl`  
`class WorkManagerImpl : public WorkManager`  
_L105-128_
- inherits: `WorkManager`
- L108 _public prototype_ `WorkManagerImpl(u32 maxWorkerCount, const tchar* workerDesc = TC("UbaWrk"), u32 precreateWorkerCount`
- L109 _public prototype_ `virtual ~WorkManagerImpl();`
- L110 _public prototype_ `virtual void AddWork(WorkFunction&& work, u32 count, const tchar* desc, const Color& color = ColorWork, WorkPriority priority = WorkPriority_Normal, Bottleneck* bottleneck = nullptr) override final;`
- L111 _public prototype_ `virtual u32 GetWorkerCount() override final;`
- L112 _public prototype_ `virtual void DoWork(u32 count = 1) override final;`
- L113 _public prototype_ `virtual bool FlushWork(u32 timeoutMs = 0) override final;`
- L117 _private prototype_ `void PushWorkerNoLock(Worker* worker);`
- L118 _private prototype_ `Worker* PopWorkerNoLock();`
- L120 _private member_ `u32 m_maxWorkerCount;`
- L121 _private member_ `TString m_workerDesc;`
- L122 _private member_ `List<Worker> m_workers;`
- L123 _private member_ `WorkQueue m_workQueue;`
- L124 _private member_ `Atomic<u32> m_activeWorkerCount = 0;`
- L126 _private member_ `Futex m_availableWorkersLock;`
- L127 _private member_ `Worker* m_firstAvailableWorker = nullptr;`

#### struct `uba::TrackWorkScope`  
`struct TrackWorkScope`  
_L132-142_
- L134 _public prototype_ `TrackWorkScope();`
- L135 _public prototype_ `TrackWorkScope(WorkTracker& t, StringView desc, const Color& color = ColorWork);`
- L136 _public prototype_ `void AddHint(StringView hint, u64 startTime = 0);`
- L137 _public prototype_ `~TrackWorkScope();`
- L138 _public prototype_ `static TrackWorkScope* GetActiveScope();`
- L139 _public member_ `WorkTracker* tracker;`
- L140 _public member_ `TrackWorkScope* outerScope;`
- L141 _public member_ `u32 id;`

#### struct `uba::TrackHintScope`  
`struct TrackHintScope`  
_L146-153_
- L148 _public function_ `TrackHintScope(TrackWorkScope& t, StringView h) : tws(t), hint(h), startTime(GetTime())`
- L149 _public function_ `~TrackHintScope()`
- L150 _public member_ `TrackWorkScope& tws;`
- L151 _public member_ `StringView hint;`
- L152 _public member_ `u64 startTime;`

#### struct `uba::WorkManager::ParallelFor::Context`  
`struct Context`  
_L183-191_
- L185 _public member_ `iterator it;`
- L186 _public member_ `iterator end;`
- L187 _public member_ `u32 activeCount;`
- L188 _public member_ `bool isDone;`
- L189 _public member_ `Futex lock;`
- L190 _public member_ `EventSlim* doneEvent;`

#### struct `uba::IndexContainer`  
`struct IndexContainer`  
_L266-281_
- L276 _public function_ `IndexContainer(u64 c) : count(u32(c))`
- L277 _public function_ `iterator begin() const`
- L278 _public function_ `iterator end() const`
- L279 _public function_ `u32 size() const`
- L280 _public member_ `u32 count;`

#### struct `uba::IndexContainer::iterator`  
`struct iterator`  
_L268-275_
- L270 _public function_ `iterator() : index(0)`
- L271 _public function_ `iterator(u32 i) : index(i)`
- L272 _public function_ `iterator operator++(int)`
- L273 _public function_ `bool operator==(const iterator& o) const`
- L274 _public member_ `u32 index;`

#### Free symbols / members of external scopes

- L13 _macro_ `#define UBA_TRACK_WORK 1`
- L15 _namespace_ `namespace uba`
- L25 _typedef_ `using Color = u32;` (scope `uba`)
- L26 _function_ `constexpr inline Color ToColor(u8 r, u8 g, u8 b)` (scope `uba`)
- L27 _variable_ `constexpr Color ColorWhite = ToColor(255, 255, 255);` (scope `uba`)
- L28 _variable_ `constexpr Color ColorWork = ToColor(70, 70, 100);` (scope `uba`)
- L50 _typedef_ `using WorkFunction = Function<void(const WorkContext& context)>;` (scope `uba`)
- L162 _typedef_ `typedef typename TContainer::iterator iterator;` (scope `uba::WorkManager::ParallelFor`)
- L207 _function_ `` (scope `uba::WorkManager::ParallelFor`)
