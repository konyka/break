# Developer / TraceServices

- module root: `Source/Developer/TraceServices`
- headers: 132; symbols: 5192
- symbol kinds: class=186, delegate=4, enum=79, enumerator=423, externvar=9, function=746, macro=11, member=1719, namespace=144, prototype=1548, struct=233, typedef=81, union=8, variable=1
- PublicDependencyModuleNames: Cbor, Core, CoreUObject, SymsLib, TraceAnalysis

### `Source/Developer/TraceServices/Private/AnalysisCache.h` (Private)


#### class `TraceServices::FAnalysisCache`  
`class FAnalysisCache : public IAnalysisCache`  
_L20-167_
- inherits: `IAnalysisCache`
- L23 _public prototype_ `explicit FAnalysisCache(const TCHAR* Path);`
- L26 _public prototype_ `virtual FCacheId GetCacheId(const TCHAR* Name, uint16 Flags) override;`
- L27 _public prototype_ `virtual FMutableMemoryView GetUserData(FCacheId CacheId) override;`
- L28 _public prototype_ `virtual FSharedBuffer CreateBlocks(FCacheId CacheId, uint32 Count) override;`
- L29 _public prototype_ `virtual FSharedBuffer GetBlocks(FCacheId CacheId, uint32 BlockIndexStart, uint32 BlockCount = 1) override;`
- L36 _private typedef_ `typedef uint32 BlockKeyType;` — Compound key identifying a block. Warning: Changing this type also affects file contents.
- L122 _private prototype_ `void ReleaseBlocks(uint8* BlockBuffer, FCacheId CacheId, uint32 BlockIndexStart, uint64 Size);` — Called when a shared buffer is released. Checks if content has change and updates cached block correspondingly and finally frees memory. @param BlockBuffer Allocated memory @param CacheId Unique cache id @param BlockIndexStart Block index for this cache entry @param Size of buffer
- L130 _private function_ `static BlockKeyType CreateBlockKey(FCacheId CacheId, uint32 BlockIndex)` — Creates a block key identifier @param CacheId Unique cache id @param BlockIndex Block index for this cache entry @return Unique key identifying a single block
- L143 _private function_ `static uint32 GetCacheId(BlockKeyType BlockKey)` — Extract the cache id from a block key @param BlockKey Unique key identifying a single block @return Unique cache id
- L153 _private function_ `static uint32 GetBlockIndex(BlockKeyType BlockKey)` — Extract the block index from a block key @param BlockKey Unique key identifying a single block @return Block index for this cache entry
- L158 _private prototype_ `FAnalysisCache() = delete;`
- L159 _private prototype_ `FAnalysisCache(FAnalysisCache& Other) = delete;`
- L161 _private member_ `constexpr static uint32 BlockAlignment = 1024*4;`
- L163 _private member_ `TUniquePtr<FFileContents> Contents;`
- L164 _private member_ `FStats Stats;`
- L165 _private member_ `TMap<BlockKeyType,FSharedBuffer> CachedBlocks;`
- L166 _private member_ `TMap<uint32,uint32> IndexBlockCount;`

#### struct `TraceServices::FAnalysisCache::FFileContents`  
`struct FFileContents`  
_L41-103_
- desc: Wrapper for file contents
- L44 _public member_ `static constexpr uint32 CurrentVersion = 2;` — Current file format version
- L46 _public member_ `static constexpr uint32 ReservedSizeV1 = 512 * 1024;` — Number of bytes at the start of the file reserved for table of contents and header.
- L47 _public member_ `static constexpr uint32 ReservedSizeV2 = 1024 * 1024;`
- L49 _public member_ `static constexpr uint32 IndexOffset = 6;` — Offset of the table of contents in bytes
- L51 _public member_ `static constexpr uint32 ReservedSizeIndex = ReservedSizeV2 - IndexOffset;` — Size for the index object
- L53 _public member_ `static constexpr uint32 UserDataSize = 64;` — Number of bytes allocated for user data (per named entry)
- L55 _public prototype_ `explicit FFileContents(const TCHAR* FilePath);`
- L56 _public prototype_ `~FFileContents();`
- L57 _public prototype_ `FCacheId GetId(const TCHAR* Name, uint16 Flags);`
- L58 _public prototype_ `FMutableMemoryView GetUserData(FCacheId Id);`
- L59 _public prototype_ `uint16 GetFlags(FCacheId Id);`
- L60 _public prototype_ `bool Save();`
- L61 _public prototype_ `bool Load();`
- L62 _public prototype_ `uint64 UpdateBlock(FMemoryView Block, BlockKeyType BlockKey);`
- L63 _public prototype_ `uint64 LoadBlock(FMutableMemoryView Block, BlockKeyType BlockKey);`
- L64 _public prototype_ `IFileHandle* GetFileHandleForWrite();`
- L65 _public prototype_ `IFileHandle* GetFileHandleForRead();`
- L85 _public member_ `FString CacheFilePath;`
- L86 _public member_ `TUniquePtr<IFileHandle> CacheFile;`
- L87 _public member_ `TUniquePtr<IFileHandle> CacheFileWrite;`
- L88 _public member_ `TArray<FIndexEntry> IndexEntries;`
- L89 _public member_ `TArray<FBlockEntry> Blocks;`
- L91 _public member_ `bool bTransientMode = false;` — When this is set blocks or table of contents are never written.
- L92 _public member_ `uint32 Version = 0;`
- L95 _private prototype_ `static uint32 ReadHeader(IFileHandle* File);`
- L96 _private prototype_ `static bool WriteHeader(IFileHandle* File, uint32 Version);`
- L97 _private prototype_ `void LoadVersion1Index(const FCbPackage& Package);`
- L98 _private prototype_ `void SaveVersion1Index(FCbWriter& Writer);`
- L99 _private prototype_ `bool SaveVersion1(IFileHandle* File);`
- L100 _private prototype_ `bool SaveVersion2(IFileHandle* File);`
- L101 _private prototype_ `bool LoadVersion1(IFileHandle* File);`
- L102 _private prototype_ `bool LoadVersion2(IFileHandle* File);`

#### struct `TraceServices::FAnalysisCache::FFileContents::FIndexEntry`  
`struct FIndexEntry`  
_L67-73_
- L69 _public member_ `FString Name;`
- L70 _public member_ `uint32 Id;`
- L71 _public member_ `uint32 Flags;`
- L72 _public member_ `uint8 UserData[UserDataSize];`

#### struct `TraceServices::FAnalysisCache::FFileContents::FBlockEntry`  
`struct FBlockEntry`  
_L75-83_
- L77 _public member_ `BlockKeyType BlockKey;`
- L78 _public member_ `uint32 Flags;`
- L79 _public member_ `uint64 Offset;`
- L80 _public member_ `uint64 CompressedSize;`
- L81 _public member_ `uint64 UncompressedSize;`
- L82 _public member_ `FIoHash Hash;`

#### struct `TraceServices::FAnalysisCache::FStats`  
`struct FStats`  
_L108-112_
- desc: Life time statistics
- L110 _public member_ `uint64 BytesRead;`
- L111 _public member_ `uint64 BytesWritten;`

#### Free symbols / members of external scopes

- L15 _namespace_ `namespace TraceServices`

### `Source/Developer/TraceServices/Private/AnalysisServicePrivate.h` (Private)


#### class `TraceServices::FAnalysisSessionLock`  
`class FAnalysisSessionLock`  
_L22-36_
- L25 _public prototype_ `void ReadAccessCheck() const;`
- L26 _public prototype_ `void WriteAccessCheck() const;`
- L28 _public prototype_ `void BeginRead();`
- L29 _public prototype_ `void EndRead();`
- L31 _public prototype_ `void BeginEdit();`
- L32 _public prototype_ `void EndEdit();`
- L35 _private member_ `FRWLock RWLock;`

#### class `TraceServices::FAnalysisSession`  
`class FAnalysisSession : public IAnalysisSession`  
_L38-114_
- inherits: `IAnalysisSession`
- L42 _public prototype_ `FAnalysisSession(uint32 TraceId, const TCHAR* SessionName, TUniquePtr<UE::Trace::IInDataStream>&& InDataStream);`
- L43 _public prototype_ `virtual ~FAnalysisSession();`
- L45 _public prototype_ `void Start();`
- L46 _public prototype_ `virtual void Stop(bool bAndWait) const override;`
- L47 _public prototype_ `virtual void Wait() const override;`
- L48 _public function_ `virtual bool IsAnalysisComplete() const override`
- L50 _public function_ `virtual const TCHAR* GetName() const override`
- L51 _public function_ `virtual uint32 GetTraceId() const override`
- L53 _public function_ `virtual double GetDurationSeconds() const override`
- L54 _public function_ `virtual void UpdateDurationSeconds(double Duration) override`
- L56 _public function_ `virtual double GetBaseDateTime() const override`
- L57 _public function_ `virtual void SetBaseDateTime(double InBaseDateTime) override`
- L59 _public function_ `virtual uint32 GetMetadataCount() const override`
- L60 _public prototype_ `virtual void EnumerateMetadata(TFunctionRef<void(const FTraceSessionMetadata& Metadata)> Callback) const override;`
- L61 _public prototype_ `virtual void AddMetadata(FName InName, int64 InValue) override;`
- L62 _public prototype_ `virtual void AddMetadata(FName InName, double InValue) override;`
- L63 _public prototype_ `virtual void AddMetadata(FName InName, FString InValue) override;`
- L65 _public prototype_ `virtual uint32 GetNumPendingMessages() const override;`
- L66 _public prototype_ `virtual TArray<FAnalysisMessage> DrainPendingMessages() override;`
- L68 _public function_ `virtual ILinearAllocator& GetLinearAllocator() override`
- L69 _public function_ `virtual IStringStore& GetStringStore() override`
- L70 _public function_ `virtual const TCHAR* StoreString(const TCHAR* String) override`
- L71 _public function_ `virtual const TCHAR* StoreString(const FStringView& String) override`
- L73 _public function_ `virtual IAnalysisCache& GetCache() override`
- L75 _public function_ `virtual void BeginRead() const override`
- L76 _public function_ `virtual void EndRead() const override`
- L78 _public function_ `virtual void BeginEdit() override`
- L79 _public function_ `virtual void EndEdit() override`
- L81 _public function_ `virtual void ReadAccessCheck() const override`
- L82 _public function_ `virtual void WriteAccessCheck() override`
- L84 _public prototype_ `virtual void AddAnalyzer(UE::Trace::IAnalyzer* Analyzer) override;`
- L85 _public prototype_ `virtual void AddAnalyzer(TSharedRef<UE::Trace::IAnalyzer> Analyzer) override;`
- L86 _public prototype_ `virtual void AddProvider(const FName& Name, TSharedPtr<IProvider> Provider, TSharedPtr<IEditableProvider> EditableProvider = nullptr) override;`
- L88 _public function_ `const TArray<UE::Trace::IAnalyzer*> ReadAnalyzers()`
- L91 _private prototype_ `virtual const IProvider* ReadProviderPrivate(const FName& Name) const override;`
- L92 _private prototype_ `virtual IEditableProvider* EditProviderPrivate(const FName& Name) override;`
- L94 _private prototype_ `void OnAnalysisMessage(UE::Trace::EAnalysisMessageSeverity Severity, FStringView Message);`
- L95 _private prototype_ `void OnAnalysisComplete();`
- L98 _private member_ `mutable FAnalysisSessionLock Lock;`
- L99 _private member_ `FString Name;`
- L100 _private member_ `uint32 TraceId = 0;`
- L101 _private member_ `double DurationSeconds = 0.0;`
- L102 _private member_ `double BaseDateTime = 0.0;`
- L103 _private member_ `TMap<FName, FTraceSessionMetadata> Metadata;`
- L104 _private member_ `FSlabAllocator Allocator;`
- L105 _private member_ `FStringStore StringStore;`
- L106 _private member_ `FAnalysisCache Cache;`
- L107 _private member_ `TArray<UE::Trace::IAnalyzer*> Analyzers;`
- L108 _private member_ `TMap<FName, TTuple<TSharedPtr<IProvider>, TSharedPtr<IEditableProvider>>> Providers;`
- L109 _private member_ `TArray<FAnalysisMessage> PendingMessages;`
- L110 _private member_ `mutable std::atomic<uint32> PendingMessagesCount;`
- L111 _private member_ `mutable std::atomic<bool> bDataStreamClosed { false };`
- L112 _private member_ `mutable TUniquePtr<UE::Trace::IInDataStream> DataStream;`
- L113 _private member_ `mutable UE::Trace::FAnalysisProcessor Processor;`

#### class `TraceServices::FAnalysisService`  
`class FAnalysisService : public IAnalysisService`  
_L116-128_
- inherits: `IAnalysisService`
- L120 _public prototype_ `FAnalysisService(FModuleService& ModuleService);`
- L121 _public prototype_ `virtual ~FAnalysisService();`
- L122 _public prototype_ `virtual TSharedPtr<const IAnalysisSession> Analyze(const TCHAR* SessionUri) override;`
- L123 _public prototype_ `virtual TSharedPtr<const IAnalysisSession> StartAnalysis(const TCHAR* SessionUri) override;`
- L124 _public prototype_ `virtual TSharedPtr<const IAnalysisSession> StartAnalysis(uint32 TraceId, const TCHAR* SessionName, TUniquePtr<UE::Trace::IInDataStream>&& DataStream) override;`
- L127 _private member_ `FModuleService& ModuleService;`

#### Free symbols / members of external scopes

- L17 _namespace_ `namespace TraceServices`

### `Source/Developer/TraceServices/Private/Analyzers/AllocationsAnalysis.h` (Private)


#### class `TraceServices::FAllocationsAnalyzer`  
`class FAllocationsAnalyzer : public UE::Trace::IAnalyzer`  
_L15-60_
- inherits: `UE::Trace::IAnalyzer`
- L43 _public prototype_ `FAllocationsAnalyzer(IAnalysisSession& Session, FAllocationsProvider& AllocationsProvider, FMetadataProvider& MetadataProvider);`
- L44 _public prototype_ `~FAllocationsAnalyzer();`
- L45 _public prototype_ `virtual void OnAnalysisBegin(const FOnAnalysisContext& Context) override;`
- L46 _public prototype_ `virtual void OnAnalysisEnd() override;`
- L47 _public prototype_ `virtual bool OnEvent(uint16 RouteId, EStyle Style, const FOnEventContext& Context) override;`
- L48 _public prototype_ `double GetCurrentTime() const;`
- L51 _private member_ `IAnalysisSession& Session;`
- L52 _private member_ `FAllocationsProvider& AllocationsProvider;`
- L53 _private member_ `FMetadataProvider& MetadataProvider;`
- L54 _private member_ `uint64 BaseCycle = 0;`
- L55 _private member_ `uint64 LastMarkerCycle = 0;`
- L56 _private member_ `double LastMarkerSeconds = 0.0;`
- L57 _private member_ `uint32 MarkerPeriod = 0;`
- L58 _private member_ `uint16 TagIdMetadataType = ~0;`
- L59 _private member_ `uint8 SizeShift = 0;`

#### enum `TraceServices::FAllocationsAnalyzer::(anonymous)`  
``  
_L19-40_

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace TraceServices`
- L20 _enumerator_ `RouteId_Init` (scope `TraceServices::FAllocationsAnalyzer::__anon233706b20103`)
- L21 _enumerator_ `RouteId_Alloc` (scope `TraceServices::FAllocationsAnalyzer::__anon233706b20103`)
- L22 _enumerator_ `RouteId_AllocSystem` (scope `TraceServices::FAllocationsAnalyzer::__anon233706b20103`)
- L23 _enumerator_ `RouteId_AllocVideo` (scope `TraceServices::FAllocationsAnalyzer::__anon233706b20103`)
- L24 _enumerator_ `RouteId_Free` (scope `TraceServices::FAllocationsAnalyzer::__anon233706b20103`)
- L25 _enumerator_ `RouteId_FreeSystem` (scope `TraceServices::FAllocationsAnalyzer::__anon233706b20103`)
- L26 _enumerator_ `RouteId_FreeVideo` (scope `TraceServices::FAllocationsAnalyzer::__anon233706b20103`)
- L27 _enumerator_ `RouteId_ReallocAlloc` (scope `TraceServices::FAllocationsAnalyzer::__anon233706b20103`)
- L28 _enumerator_ `RouteId_ReallocAllocSystem` (scope `TraceServices::FAllocationsAnalyzer::__anon233706b20103`)
- L29 _enumerator_ `RouteId_ReallocFree` (scope `TraceServices::FAllocationsAnalyzer::__anon233706b20103`)
- L30 _enumerator_ `RouteId_ReallocFreeSystem` (scope `TraceServices::FAllocationsAnalyzer::__anon233706b20103`)
- L31 _enumerator_ `RouteId_HeapMarkAlloc` (scope `TraceServices::FAllocationsAnalyzer::__anon233706b20103`)
- L32 _enumerator_ `RouteId_HeapUnmarkAlloc` (scope `TraceServices::FAllocationsAnalyzer::__anon233706b20103`)
- L33 _enumerator_ `RouteId_UpdateAlloc` (scope `TraceServices::FAllocationsAnalyzer::__anon233706b20103`) — added in UE 5.6
- L34 _enumerator_ `RouteId_MemSwapOp` (scope `TraceServices::FAllocationsAnalyzer::__anon233706b20103`) — added in UE 5.5
- L35 _enumerator_ `RouteId_Marker` (scope `TraceServices::FAllocationsAnalyzer::__anon233706b20103`)
- L36 _enumerator_ `RouteId_TagSpec` (scope `TraceServices::FAllocationsAnalyzer::__anon233706b20103`)
- L37 _enumerator_ `RouteId_HeapSpec` (scope `TraceServices::FAllocationsAnalyzer::__anon233706b20103`)
- L38 _enumerator_ `RouteId_MemScopeTag` (scope `TraceServices::FAllocationsAnalyzer::__anon233706b20103`)
- L39 _enumerator_ `RouteId_MemScopePtr` (scope `TraceServices::FAllocationsAnalyzer::__anon233706b20103`)

### `Source/Developer/TraceServices/Private/Analyzers/BookmarksTraceAnalysis.h` (Private)


#### class `TraceServices::FBookmarksAnalyzer`  
`class FBookmarksAnalyzer : public UE::Trace::IAnalyzer`  
_L18-44_
- inherits: `UE::Trace::IAnalyzer`
- L22 _public prototype_ `FBookmarksAnalyzer(IAnalysisSession& Session, IEditableBookmarkProvider& EditableBookmarkProvider, IEditableLogProvider* InEditableLogProvider);`
- L23 _public prototype_ `virtual void OnAnalysisBegin(const FOnAnalysisContext& Context) override;`
- L24 _public prototype_ `virtual bool OnEvent(uint16 RouteId, EStyle Style, const FOnEventContext& Context) override;`
- L33 _private member_ `IAnalysisSession& Session;`
- L34 _private member_ `IEditableBookmarkProvider& EditableBookmarkProvider;`
- L35 _private member_ `IEditableLogProvider* EditableLogProvider;`
- L36 _private member_ `uint64 BookmarkLogCategoryId = uint64(-1);`
- L42 _private member_ `TCHAR FormatBuffer[FormatBufferSize];`
- L43 _private member_ `TCHAR TempBuffer[FormatBufferSize];`

#### enum `TraceServices::FBookmarksAnalyzer::(anonymous)`  
``  
_L28-31_

#### enum `TraceServices::FBookmarksAnalyzer::(anonymous)`  
``  
_L39-41_

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace TraceServices`
- L29 _enumerator_ `RouteId_BookmarkSpec` (scope `TraceServices::FBookmarksAnalyzer::__anone33041910103`)
- L30 _enumerator_ `RouteId_Bookmark` (scope `TraceServices::FBookmarksAnalyzer::__anone33041910103`)
- L40 _enumerator_ `FormatBufferSize = 65536` (scope `TraceServices::FBookmarksAnalyzer::__anone33041910203`)

### `Source/Developer/TraceServices/Private/Analyzers/CallstacksAnalysis.h` (Private)


#### class `TraceServices::FCallstacksAnalyzer`  
`class FCallstacksAnalyzer : public UE::Trace::IAnalyzer`  
_L15-27_
- inherits: `UE::Trace::IAnalyzer`
- L19 _public prototype_ `FCallstacksAnalyzer(IAnalysisSession& Session, FCallstacksProvider* Provider);`
- L20 _public prototype_ `virtual void OnAnalysisBegin(const FOnAnalysisContext& Context) override;`
- L21 _public prototype_ `virtual bool OnEvent(uint16 RouteId, EStyle Style, const FOnEventContext& Context) override;`
- L25 _private member_ `IAnalysisSession& Session;`
- L26 _private member_ `FCallstacksProvider* Provider;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace TraceServices`

### `Source/Developer/TraceServices/Private/Analyzers/CookAnalysis.h` (Private)


#### class `TraceServices::FCookAnalyzer`  
`class FCookAnalyzer : public UE::Trace::IAnalyzer`  
_L12-38_
- inherits: `UE::Trace::IAnalyzer`
- L15 _public prototype_ `FCookAnalyzer(IAnalysisSession& Session, FCookProfilerProvider& CookProfilerProvider);`
- L16 _public prototype_ `virtual ~FCookAnalyzer();`
- L18 _public prototype_ `virtual void OnAnalysisBegin(const FOnAnalysisContext& Context) override;`
- L19 _public prototype_ `virtual bool OnEvent(uint16 RouteId, EStyle Style, const FOnEventContext& Context) override;`
- L36 _private member_ `IAnalysisSession& Session;`
- L37 _private member_ `FCookProfilerProvider& CookProfilerProvider;`

#### enum `TraceServices::FCookAnalyzer::(anonymous)`  
``  
_L23-34_

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace TraceServices`
- L25 _enumerator_ `RouteId_Package` (scope `TraceServices::FCookAnalyzer::__anon943c55850103`) — Common
- L26 _enumerator_ `RouteId_PackageAssetClass` (scope `TraceServices::FCookAnalyzer::__anon943c55850103`)
- L29 _enumerator_ `RouteId_PackageStat` (scope `TraceServices::FCookAnalyzer::__anon943c55850103`) — Version 1
- L32 _enumerator_ `RouteId_PackageStatBeginScope` (scope `TraceServices::FCookAnalyzer::__anon943c55850103`) — Version 2 (UE 5.5+)
- L33 _enumerator_ `RouteId_PackageStatEndScope` (scope `TraceServices::FCookAnalyzer::__anon943c55850103`)

### `Source/Developer/TraceServices/Private/Analyzers/CountersTraceAnalysis.h` (Private)


#### class `TraceServices::FCountersAnalyzer`  
`class FCountersAnalyzer : public UE::Trace::IAnalyzer`  
_L15-41_
- inherits: `UE::Trace::IAnalyzer`
- L19 _public prototype_ `FCountersAnalyzer(IAnalysisSession& Session, IEditableCounterProvider& EditableCounterProvider);`
- L20 _public prototype_ `~FCountersAnalyzer();`
- L21 _public prototype_ `virtual void OnAnalysisBegin(const FOnAnalysisContext& Context) override;`
- L22 _public prototype_ `virtual bool OnEvent(uint16 RouteId, EStyle Style, const FOnEventContext& Context) override;`
- L36 _private member_ `IAnalysisSession& Session;`
- L37 _private member_ `IEditableCounterProvider& EditableCounterProvider;`
- L38 _private member_ `TMap<uint16, IEditableCounter*> EditableCountersMap;`
- L39 _private member_ `TUniquePtr<FTraceStatsHelper> TraceStatsHelper;`
- L40 _private member_ `uint64 LastStatTimeCycle = 0;`

#### enum `TraceServices::FCountersAnalyzer::(anonymous)`  
``  
_L26-32_

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace TraceServices`
- L27 _enumerator_ `RouteId_Spec` (scope `TraceServices::FCountersAnalyzer::__anonc9fa2b1b0103`)
- L28 _enumerator_ `RouteId_SetValueInt` (scope `TraceServices::FCountersAnalyzer::__anonc9fa2b1b0103`)
- L29 _enumerator_ `RouteId_SetValueFloat` (scope `TraceServices::FCountersAnalyzer::__anonc9fa2b1b0103`)
- L30 _enumerator_ `RouteId_TraceBwStats` (scope `TraceServices::FCountersAnalyzer::__anonc9fa2b1b0103`)
- L31 _enumerator_ `RouteId_TraceMemStats` (scope `TraceServices::FCountersAnalyzer::__anonc9fa2b1b0103`)

### `Source/Developer/TraceServices/Private/Analyzers/CpuProfilerTraceAnalysis.h` (Private)


#### class `TraceServices::FCpuProfilerAnalyzer`  
`class FCpuProfilerAnalyzer : public UE::Trace::IAnalyzer`  
_L23-116_
- inherits: `UE::Trace::IAnalyzer`
- L27 _public prototype_ `FCpuProfilerAnalyzer(IAnalysisSession& Session, IEditableTimingProfilerProvider& InEditableTimingProfilerProvider, IEditableThreadProvider& InEditableThreadProvider);`
- L28 _public prototype_ `~FCpuProfilerAnalyzer();`
- L29 _public prototype_ `virtual void OnAnalysisBegin(const FOnAnalysisContext& Context) override;`
- L30 _public prototype_ `virtual void OnAnalysisEnd( ) override;`
- L31 _public prototype_ `virtual bool OnEvent(uint16 RouteId, EStyle Style, const FOnEventContext& Context) override;`
- L78 _private prototype_ `void ProcessBuffer(const FEventTime& EventTime, FThreadState& ThreadState, const uint8* BufferPtr, uint32 BufferSize);`
- L79 _private prototype_ `void ProcessBufferV2(const FEventTime& EventTime, FThreadState& ThreadState, const uint8* BufferPtr, uint32 BufferSize, int32 Version);`
- L80 _private prototype_ `void DispatchPendingEvents(uint64& LastCycle, uint64 CurrentCycle, FThreadState& ThreadState, const FPendingEvent*& PendingCursor, int32& RemainingPending, bool bIsBeginEvent);`
- L81 _private prototype_ `void DispatchRemainingPendingEvents(FThreadState& ThreadState);`
- L82 _private prototype_ `void EndOpenEvents(FThreadState& ThreadState, double Timestamp);`
- L83 _private prototype_ `void OnCpuScopeEnter(const FOnEventContext& Context);`
- L84 _private prototype_ `void OnCpuScopeLeave(const FOnEventContext& Context);`
- L85 _private prototype_ `void OnEventSpec(const FOnEventContext& Context);`
- L86 _private prototype_ `void OnMetadataSpec(const FOnEventContext& Context);`
- L88 _private prototype_ `uint32 GetOrAddTimer(uint32 SpecId);`
- L89 _private prototype_ `uint32 AddCpuTimer(uint32 SpecId, const TCHAR* TimerName, const TCHAR* File = nullptr, uint32 Line = 0);` — returns the TimerId
- L90 _private prototype_ `uint32 DefineMergedTimer(uint32 SpecId, const TCHAR* TimerName, const TCHAR* File, uint32 Line);` — returns the TimerId
- L91 _private prototype_ `uint32 DefineUniqueTimer(uint32 SpecId, const TCHAR* TimerName, const TCHAR* File, uint32 Line);` — returns the TimerId
- L92 _private prototype_ `const TCHAR* GetTimerName(uint32 TimerId) const;`
- L93 _private prototype_ `void SetTimerName(uint32 SpecId, uint32 TimerId, const TCHAR* TimerName);`
- L95 _private prototype_ `FThreadState& GetOrAddThreadState(uint32 ThreadId);`
- L98 _private member_ `IAnalysisSession& Session;`
- L99 _private member_ `IEditableTimingProfilerProvider& EditableTimingProfilerProvider;`
- L100 _private member_ `IEditableThreadProvider& EditableThreadProvider;`
- L102 _private member_ `TMap<uint32, FThreadState*> ThreadStatesMap;`
- L103 _private member_ `TMap<uint32, uint32> SpecIdToTimerIdMap;` — SpecId --> TimerId
- L104 _private member_ `TMap<uint64, FTimerInfo> ScopeNameToTimerIdMap;` — (uint64)Name --> FTimerInfo
- L105 _private member_ `TMap<uint32, uint32> MetadataIdToTimerIdMap;` — MetadataId --> TimerId
- L107 _private member_ `uint32 CoroutineTimerId = ~0;`
- L108 _private member_ `uint32 CoroutineUnknownTimerId = ~0;`
- L109 _private member_ `uint32 MetadataUnknownTimerId = ~0;`
- L110 _private member_ `uint64 TotalEventSize = 0;`
- L111 _private member_ `uint64 TotalScopeCount = 0;`
- L112 _private member_ `double BytesPerScope = 0.0;`
- L114 _private member_ `uint32 NumTimerWarnings = 0;`
- L115 _private member_ `static constexpr uint32 NumMaxWarnings = 100;`

#### struct `TraceServices::FCpuProfilerAnalyzer::FEventScopeState`  
`struct FEventScopeState`  
_L34-38_
- L36 _public member_ `uint64 StartCycle;`
- L37 _public member_ `uint32 EventTypeId;`

#### struct `TraceServices::FCpuProfilerAnalyzer::FPendingEvent`  
`struct FPendingEvent`  
_L40-45_
- L42 _public member_ `uint64 Cycle;`
- L43 _public member_ `double Time;`
- L44 _public member_ `uint32 TimerId;`

#### struct `TraceServices::FCpuProfilerAnalyzer::FThreadState`  
`struct FThreadState`  
_L47-57_
- L49 _public member_ `uint32 ThreadId = 0;`
- L50 _public member_ `TArray<FEventScopeState> ScopeStack;`
- L51 _public member_ `TArray<FPendingEvent> PendingEvents;`
- L52 _public member_ `IEditableTimeline<FTimingProfilerEvent>* Timeline = nullptr;`
- L53 _public member_ `uint64 LastCycle = 0;`
- L54 _public member_ `bool bShouldIgnorePendingEvents = false;` — becomes true when we detect first pending event with incorrect timestamp (i.e < LastCycle)
- L55 _public member_ `double LastPendingEventTime = 0;`
- L56 _public member_ `int32 MetadataEventsDepth = 0;`

#### struct `TraceServices::FCpuProfilerAnalyzer::FTimerInfo`  
`struct FTimerInfo`  
_L59-63_
- L61 _public member_ `uint32 Id;`
- L62 _public member_ `uint32 Count;`

#### enum `TraceServices::FCpuProfilerAnalyzer::(anonymous)`  
``  
_L66-76_

#### Free symbols / members of external scopes

- L16 _namespace_ `namespace TraceServices`
- L67 _enumerator_ `RouteId_EventSpec` (scope `TraceServices::FCpuProfilerAnalyzer::__anon0a8525730103`)
- L68 _enumerator_ `RouteId_EndThread` (scope `TraceServices::FCpuProfilerAnalyzer::__anon0a8525730103`)
- L69 _enumerator_ `RouteId_EventBatchV3` (scope `TraceServices::FCpuProfilerAnalyzer::__anon0a8525730103`)
- L70 _enumerator_ `RouteId_EventBatchV2` (scope `TraceServices::FCpuProfilerAnalyzer::__anon0a8525730103`) — backward compatibility
- L71 _enumerator_ `RouteId_EventBatch` (scope `TraceServices::FCpuProfilerAnalyzer::__anon0a8525730103`) — backward compatibility
- L72 _enumerator_ `RouteId_EndCapture` (scope `TraceServices::FCpuProfilerAnalyzer::__anon0a8525730103`) — backward compatibility
- L73 _enumerator_ `RouteId_CpuScope` (scope `TraceServices::FCpuProfilerAnalyzer::__anon0a8525730103`)
- L74 _enumerator_ `RouteId_MetadataSpec` (scope `TraceServices::FCpuProfilerAnalyzer::__anon0a8525730103`)
- L75 _enumerator_ `RouteId_Metadata` (scope `TraceServices::FCpuProfilerAnalyzer::__anon0a8525730103`)

### `Source/Developer/TraceServices/Private/Analyzers/CsvProfilerTraceAnalysis.h` (Private)


#### class `TraceServices::FCsvProfilerAnalyzer`  
`class FCsvProfilerAnalyzer : public UE::Trace::IAnalyzer`  
_L19-149_
- inherits: `UE::Trace::IAnalyzer`
- L23 _public prototype_ `FCsvProfilerAnalyzer(IAnalysisSession& Session, FCsvProfilerProvider& CsvProfilerProvider, IEditableCounterProvider& EditableCounterProvider, const IFrameProvider& FrameProvider, const IThreadProvider& ThreadProvider);`
- L24 _public prototype_ `~FCsvProfilerAnalyzer();`
- L25 _public prototype_ `virtual void OnAnalysisBegin(const FOnAnalysisContext& Context) override;`
- L26 _public prototype_ `virtual bool OnEvent(uint16 RouteId, EStyle Style, const FOnEventContext& Context) override;`
- L27 _public prototype_ `virtual void OnAnalysisEnd() override;`
- L115 _private prototype_ `FThreadState& GetThreadState(uint32 ThreadId);`
- L116 _private prototype_ `FStatSeriesDefinition* CreateStatSeries(const TCHAR* Name, int32 CategoryIndex);`
- L117 _private prototype_ `void DefineStatSeries(uint64 StatId, const TCHAR* Name, int32 CategoryIndex, bool bIsInline);`
- L118 _private prototype_ `const TCHAR* GetStatSeriesName(const FStatSeriesDefinition* Definition, ECsvStatSeriesType Type, FThreadState& ThreadState, bool bIsCount);`
- L119 _private prototype_ `FStatSeriesInstance& GetStatSeries(uint64 StatId, ECsvStatSeriesType Type, FThreadState& ThreadState);`
- L120 _private prototype_ `void HandleMarkerEvent(const FOnEventContext& Context, bool bIsExclusive, bool bIsBegin);`
- L121 _private prototype_ `void HandleMarker(const FOnEventContext& Context, FThreadState& ThreadState, const FTimingMarker& Marker);`
- L122 _private prototype_ `void HandleCustomStatEvent(const FOnEventContext& Context, bool bIsFloat);`
- L123 _private prototype_ `void HandleEventEvent(const FOnEventContext& Context);`
- L124 _private prototype_ `void Flush(FStatSeriesInstance& StatSeries);`
- L125 _private prototype_ `void FlushIfNewFrame(FStatSeriesInstance& StatSeries, uint32 FrameNumber);`
- L126 _private prototype_ `void FlushAtEndOfCapture(FStatSeriesInstance& StatSeries, uint32 CaptureEndFrame);`
- L127 _private prototype_ `void SetTimerValue(FStatSeriesInstance& StatSeries, uint32 FrameNumber, double ElapsedTime, bool bCount);`
- L128 _private prototype_ `void SetCustomStatValue(FStatSeriesInstance& StatSeries, uint32 FrameNumber, ECsvOpType OpType, int32 Value);`
- L129 _private prototype_ `void SetCustomStatValue(FStatSeriesInstance& StatSeries, uint32 FrameNumber, ECsvOpType OpType, float Value);`
- L131 _private member_ `IAnalysisSession& Session;`
- L132 _private member_ `FCsvProfilerProvider& CsvProfilerProvider;`
- L133 _private member_ `IEditableCounterProvider& EditableCounterProvider;`
- L134 _private member_ `const IFrameProvider& FrameProvider;`
- L135 _private member_ `const IThreadProvider& ThreadProvider;`
- L137 _private member_ `TMap<uint32, FThreadState*> ThreadStatesMap;`
- L138 _private member_ `TMap<int32, const TCHAR*> CategoryMap;`
- L139 _private member_ `TMap<uint64, FStatSeriesDefinition*> StatSeriesMap;`
- L140 _private member_ `TMap<TTuple<int32, FString>, FStatSeriesDefinition*> StatSeriesStringMap;`
- L141 _private member_ `TArray<FStatSeriesDefinition*> StatSeriesDefinitionArray;`
- L142 _private member_ `TArray<FStatSeriesInstance*> StatSeriesInstanceArray;`
- L143 _private member_ `uint32 RenderThreadId = 0;`
- L144 _private member_ `uint32 RHIThreadId = 0;`
- L145 _private member_ `bool bEnableCounts = false;`
- L146 _private member_ `uint32 UndefinedStatSeriesCount = 0;`
- L148 _private member_ `TArray<uint64> FrameBoundaries[TraceFrameType_Count];`

#### enum `TraceServices::FCsvProfilerAnalyzer::(anonymous)`  
``  
_L31-45_

#### enum `TraceServices::FCsvProfilerAnalyzer::ECsvOpType`  
`enum ECsvOpType`  
_L47-53_
- L49 _public enumerator_ `CsvOpType_Set`
- L50 _public enumerator_ `CsvOpType_Min`
- L51 _public enumerator_ `CsvOpType_Max`
- L52 _public enumerator_ `CsvOpType_Accumulate`

#### union `TraceServices::FCsvProfilerAnalyzer::FStatSeriesID`  
`union FStatSeriesID`  
_L55-65_
- L63 _public member_ `} Fields;`
- L64 _public member_ `uint64 Hash;`

#### struct `TraceServices::FCsvProfilerAnalyzer::FStatSeriesID::(anonymous)`  
``  
_L58-63_

#### struct `TraceServices::FCsvProfilerAnalyzer::FStatSeriesValue`  
`struct FStatSeriesValue`  
_L67-76_
- L69 _public function_ `FStatSeriesValue()`
- L74 _public member_ `} Value;`
- L75 _public member_ `bool bIsValid = false;`

#### union `TraceServices::FCsvProfilerAnalyzer::FStatSeriesValue::(anonymous)`  
``  
_L71-74_

#### struct `TraceServices::FCsvProfilerAnalyzer::FStatSeriesDefinition`  
`struct FStatSeriesDefinition`  
_L78-83_
- L80 _public member_ `const TCHAR* Name = nullptr;`
- L81 _public member_ `int32 CategoryIndex = -1;`
- L82 _public member_ `int32 ColumnIndex = -1;`

#### struct `TraceServices::FCsvProfilerAnalyzer::FStatSeriesInstance`  
`struct FStatSeriesInstance`  
_L85-95_
- L87 _public member_ `uint64 ProviderHandle = uint64(-1);`
- L88 _public member_ `uint64 ProviderCountHandle = uint64(-1);`
- L89 _public member_ `IEditableCounter* Counter = nullptr;`
- L90 _public member_ `uint32 CurrentFrame = 0;`
- L91 _public member_ `FStatSeriesValue CurrentValue;`
- L92 _public member_ `int64 CurrentCount = 0;`
- L93 _public member_ `ECsvStatSeriesType Type = CsvStatSeriesType_CustomStatInt;`
- L94 _public member_ `ETraceFrameType FrameType = TraceFrameType_Game;`

#### struct `TraceServices::FCsvProfilerAnalyzer::FTimingMarker`  
`struct FTimingMarker`  
_L97-104_
- L99 _public member_ `uint64 StatId = 0;`
- L100 _public member_ `uint64 Cycle = 0;`
- L101 _public member_ `bool bIsBegin = false;`
- L102 _public member_ `bool bIsExclusive = false;`
- L103 _public member_ `bool bIsExclusiveInsertedMarker = false;`

#### struct `TraceServices::FCsvProfilerAnalyzer::FThreadState`  
`struct FThreadState`  
_L106-113_
- L108 _public member_ `TArray<FTimingMarker> MarkerStack;`
- L109 _public member_ `TArray<FTimingMarker> ExclusiveMarkerStack;`
- L110 _public member_ `ETraceFrameType FrameType = TraceFrameType_Game;`
- L111 _public member_ `TArray<FStatSeriesInstance*> StatSeries;`
- L112 _public member_ `FString ThreadName;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace TraceServices`
- L32 _enumerator_ `RouteId_RegisterCategory` (scope `TraceServices::FCsvProfilerAnalyzer::__anonddb795570103`)
- L33 _enumerator_ `RouteId_DefineInlineStat` (scope `TraceServices::FCsvProfilerAnalyzer::__anonddb795570103`)
- L34 _enumerator_ `RouteId_DefineDeclaredStat` (scope `TraceServices::FCsvProfilerAnalyzer::__anonddb795570103`)
- L35 _enumerator_ `RouteId_BeginStat` (scope `TraceServices::FCsvProfilerAnalyzer::__anonddb795570103`)
- L36 _enumerator_ `RouteId_EndStat` (scope `TraceServices::FCsvProfilerAnalyzer::__anonddb795570103`)
- L37 _enumerator_ `RouteId_BeginExclusiveStat` (scope `TraceServices::FCsvProfilerAnalyzer::__anonddb795570103`)
- L38 _enumerator_ `RouteId_EndExclusiveStat` (scope `TraceServices::FCsvProfilerAnalyzer::__anonddb795570103`)
- L39 _enumerator_ `RouteId_CustomStatInt` (scope `TraceServices::FCsvProfilerAnalyzer::__anonddb795570103`)
- L40 _enumerator_ `RouteId_CustomStatFloat` (scope `TraceServices::FCsvProfilerAnalyzer::__anonddb795570103`)
- L41 _enumerator_ `RouteId_Event` (scope `TraceServices::FCsvProfilerAnalyzer::__anonddb795570103`)
- L42 _enumerator_ `RouteId_Metadata` (scope `TraceServices::FCsvProfilerAnalyzer::__anonddb795570103`)
- L43 _enumerator_ `RouteId_BeginCapture` (scope `TraceServices::FCsvProfilerAnalyzer::__anonddb795570103`)
- L44 _enumerator_ `RouteId_EndCapture` (scope `TraceServices::FCsvProfilerAnalyzer::__anonddb795570103`)
- L59 _member_ `uint64 IsFName : 1;` (scope `TraceServices::FCsvProfilerAnalyzer::FStatSeriesID::__anonddb795570208`)
- L60 _member_ `uint64 IsCountStat : 1;` (scope `TraceServices::FCsvProfilerAnalyzer::FStatSeriesID::__anonddb795570208`)
- L61 _member_ `uint64 CategoryIndex : 11;` (scope `TraceServices::FCsvProfilerAnalyzer::FStatSeriesID::__anonddb795570208`)
- L62 _member_ `uint64 FNameOrIndex : 51;` (scope `TraceServices::FCsvProfilerAnalyzer::FStatSeriesID::__anonddb795570208`)
- L72 _member_ `int64 AsInt;` (scope `TraceServices::FCsvProfilerAnalyzer::FStatSeriesValue::__anonddb79557030a`)
- L73 _member_ `double AsDouble;` (scope `TraceServices::FCsvProfilerAnalyzer::FStatSeriesValue::__anonddb79557030a`)

### `Source/Developer/TraceServices/Private/Analyzers/DiagnosticsAnalysis.h` (Private)


#### class `TraceServices::FDiagnosticsAnalyzer`  
`class FDiagnosticsAnalyzer : public UE::Trace::IAnalyzer`  
_L15-36_
- inherits: `UE::Trace::IAnalyzer`
- L19 _public prototype_ `FDiagnosticsAnalyzer(IAnalysisSession& Session, FDiagnosticsProvider* InProvider);`
- L20 _public prototype_ `~FDiagnosticsAnalyzer();`
- L22 _public prototype_ `virtual void OnAnalysisBegin(const FOnAnalysisContext& Context) override;`
- L23 _public prototype_ `virtual bool OnEvent(uint16 RouteId, EStyle Style, const FOnEventContext& Context) override;`
- L26 _private prototype_ `void UpdateSessionMetadata(const UE::Trace::IAnalyzer::FEventData& EventData);`
- L34 _private member_ `IAnalysisSession& Session;`
- L35 _private member_ `FDiagnosticsProvider* Provider;`

#### enum `TraceServices::FDiagnosticsAnalyzer::(anonymous)`  
``  
_L29-32_

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace TraceServices`
- L30 _enumerator_ `RouteId_Session` (scope `TraceServices::FDiagnosticsAnalyzer::__anon93e58d910103`)
- L31 _enumerator_ `RouteId_Session2` (scope `TraceServices::FDiagnosticsAnalyzer::__anon93e58d910103`)

### `Source/Developer/TraceServices/Private/Analyzers/GpuProfilerTraceAnalysis.h` (Private)


#### class `TraceServices::FGpuProfilerAnalyzer`  
`class FGpuProfilerAnalyzer : public UE::Trace::IAnalyzer`  
_L22-112_
- inherits: `UE::Trace::IAnalyzer`
- desc: The New GPU Profiler
- L79 _public prototype_ `FGpuProfilerAnalyzer(FAnalysisSession& Session, FTimingProfilerProvider& TimingProfilerProvider, IEditableCounterProvider& EditableCounterProvider);`
- L80 _public prototype_ `virtual void OnAnalysisBegin(const FOnAnalysisContext& Context) override;`
- L81 _public prototype_ `virtual void OnAnalysisEnd() override;`
- L82 _public prototype_ `virtual bool OnEvent(uint16 RouteId, EStyle Style, const FOnEventContext& Context) override;`
- L85 _private prototype_ `FQueue& GetOrAddQueue(uint32 QueueId);`
- L86 _private prototype_ `void BeginEvent(FQueue& Queue, int32 StackIndex, double Time, uint32 TimerId);`
- L87 _private prototype_ `void EndEvent(FQueue& Queue, int32 StackIndex, double Time, uint32 TimerId);`
- L88 _private prototype_ `void OnEventBreadcrumbSpec(const FOnEventContext& Context);`
- L90 _private prototype_ `uint32 GetOrAddTimer(uint32 SpecId, const FString& Breadcrumb);`
- L91 _private prototype_ `uint32 AddGpuTimer(uint32 SpecId, const FString& Breadcrumb);`
- L92 _private prototype_ `const TCHAR* GetTimerName(uint32 TimerId) const;`
- L93 _private prototype_ `void SetTimerName(uint32 SpecId, uint32 TimerId, FStringView TimerName);`
- L95 _private prototype_ `void InitCounters(FQueue& FoundQueue);`
- L96 _private prototype_ `void InitCountersDesc(FQueue& FoundQueue, uint8 Gpu, uint8 Index, const TCHAR* Name);`
- L99 _private member_ `FAnalysisSession& Session;`
- L100 _private member_ `FTimingProfilerProvider& TimingProfilerProvider;`
- L101 _private member_ `IEditableCounterProvider& EditableCounterProvider;`
- L103 _private member_ `uint32 Version = 0;`
- L104 _private member_ `static constexpr uint32 InvalidTimerId = 0;`
- L105 _private member_ `uint32 GpuWorkTimerId = InvalidTimerId;`
- L106 _private member_ `uint32 GpuWaitTimerId = InvalidTimerId;`
- L107 _private member_ `TMap<uint32, uint32> SpecIdToTimerIdMap;` — breadcrumb spec id --> GPU timer id
- L108 _private member_ `TMap<FString, uint32> BreadcrumbMap;` — breadcrumb name --> GPU timer id
- L109 _private member_ `TMap<uint32, const TCHAR*> TimerMap;` — GPU timer id --> persistent timer name
- L110 _private member_ `TMap<uint32, FQueue> Queues;` — QueueId --> FQueue
- L111 _private member_ `FErrorData ErrorData;`

#### enum `TraceServices::FGpuProfilerAnalyzer::(anonymous)`  
``  
_L26-39_

#### struct `TraceServices::FGpuProfilerAnalyzer::FOpenEvent`  
`struct FOpenEvent`  
_L41-45_
- L43 _public member_ `double Time;`
- L44 _public member_ `uint32 TimerId;`

#### struct `TraceServices::FGpuProfilerAnalyzer::FQueue`  
`struct FQueue`  
_L47-57_
- L49 _public member_ `uint32 Id = 0;`
- L50 _public member_ `uint32 FrameNumber = 0;`
- L51 _public member_ `TArray<FOpenEvent> Stack[2];` — [0] = breadcrumbs, [1] = work
- L52 _public member_ `IEditableCounter* NumDrawsCounter;`
- L53 _public member_ `IEditableCounter* NumPrimitivesCounter;`
- L54 _public member_ `uint64 NumDraws = 0;`
- L55 _public member_ `uint64 NumPrimitives = 0;`
- L56 _public member_ `double LastTime = 0.0f;`

#### struct `TraceServices::FGpuProfilerAnalyzer::FErrorData`  
`struct FErrorData`  
_L59-76_
- L61 _public member_ `static constexpr uint32 NumMaxWarnings = 100;`
- L62 _public member_ `static constexpr uint32 NumMaxErrors = 100;`
- L64 _public member_ `uint32 NumWarnings = 0;`
- L65 _public member_ `uint32 NumTimerWarnings = 0;`
- L66 _public member_ `uint32 NumErrors = 0;`
- L68 _public member_ `uint32 NumInterleavedEvents = 0;`
- L69 _public member_ `uint32 NumInterleavedAndReversedEvents = 0;`
- L70 _public member_ `uint32 NumMismatchedEvents = 0;`
- L71 _public member_ `uint32 NumNegativeDurationEvents = 0;`
- L73 _public member_ `double InterleavedEventsMaxDelta = 0.0f;`
- L74 _public member_ `double InterleavedAndReversedEventsMaxDelta = 0.0f;`
- L75 _public member_ `double NegativeDurationEventsMaxDelta = 0.0f;`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace TraceServices`
- L27 _enumerator_ `RouteId_Init` (scope `TraceServices::FGpuProfilerAnalyzer::__anonc70ff1f70103`)
- L28 _enumerator_ `RouteId_QueueSpec` (scope `TraceServices::FGpuProfilerAnalyzer::__anonc70ff1f70103`)
- L29 _enumerator_ `RouteId_EventFrameBoundary` (scope `TraceServices::FGpuProfilerAnalyzer::__anonc70ff1f70103`)
- L30 _enumerator_ `RouteId_EventBreadcrumbSpec` (scope `TraceServices::FGpuProfilerAnalyzer::__anonc70ff1f70103`)
- L31 _enumerator_ `RouteId_EventBeginBreadcrumb` (scope `TraceServices::FGpuProfilerAnalyzer::__anonc70ff1f70103`)
- L32 _enumerator_ `RouteId_EventEndBreadcrumb` (scope `TraceServices::FGpuProfilerAnalyzer::__anonc70ff1f70103`)
- L33 _enumerator_ `RouteId_EventBeginWork` (scope `TraceServices::FGpuProfilerAnalyzer::__anonc70ff1f70103`)
- L34 _enumerator_ `RouteId_EventEndWork` (scope `TraceServices::FGpuProfilerAnalyzer::__anonc70ff1f70103`)
- L35 _enumerator_ `RouteId_EventWait` (scope `TraceServices::FGpuProfilerAnalyzer::__anonc70ff1f70103`)
- L36 _enumerator_ `RouteId_EventStats` (scope `TraceServices::FGpuProfilerAnalyzer::__anonc70ff1f70103`)
- L37 _enumerator_ `RouteId_SignalFence` (scope `TraceServices::FGpuProfilerAnalyzer::__anonc70ff1f70103`)
- L38 _enumerator_ `RouteId_WaitFence` (scope `TraceServices::FGpuProfilerAnalyzer::__anonc70ff1f70103`)

### `Source/Developer/TraceServices/Private/Analyzers/KnownEventProcessor.h` (Private)


#### class `TraceServices::FKnownEventProcessor`  
`class FKnownEventProcessor`  
_L17-180_
- L20 _public typedef_ `typedef TFunction<void(uint32 ThreadId, const UE::Trace::IAnalyzer::FOnEventContext& Context, uint64 Cycle)> FOnUpdateThreadTimeFunc;`
- L119 _private typedef_ `typedef TFunction<void(const UE::Trace::IAnalyzer::FOnEventContext& Context)> KnownEventCallback;`
- L135 _public prototype_ `FKnownEventProcessor();`
- L136 _public prototype_ `virtual ~FKnownEventProcessor();`
- L138 _public prototype_ `void Reset();`
- L140 _public function_ `void SetOnUpdateThreadTime(const FOnUpdateThreadTimeFunc& Callback)`
- L145 _public prototype_ `void OnAnalysisBegin(const UE::Trace::IAnalyzer::FOnAnalysisContext& Context);`
- L146 _public prototype_ `void OnAnalysisEnd();`
- L147 _public prototype_ `void OnNewEvent(const UE::Trace::IAnalyzer::FEventTypeInfo& TypeInfo);`
- L148 _public prototype_ `void OnEvent(uint32 EventId, const UE::Trace::IAnalyzer::FOnEventContext& Context);`
- L151 _private function_ `bool IsKnownEvent(uint32 EventId, EKnownEvent KnownEvent) const`
- L156 _private prototype_ `void RegisterCallbacks();`
- L158 _private prototype_ `void ProcessCpuEventBatchV1(const UE::Trace::IAnalyzer::FOnEventContext& Context, const uint8* BufferPtr, uint32 BufferSize);`
- L159 _private prototype_ `uint64 ProcessCpuEventBatchV1(const UE::Trace::IAnalyzer::FOnEventContext& Context, const uint8* BufferPtr, uint32 BufferSize, uint64 ThreadCycle);`
- L161 _private prototype_ `void ProcessCpuEventBatchV2V3(const UE::Trace::IAnalyzer::FOnEventContext& Context, const uint8* BufferPtr, uint32 BufferSize, int32 Version);`
- L162 _private prototype_ `uint64 ProcessCpuEventBatchV2V3(const UE::Trace::IAnalyzer::FOnEventContext& Context, const uint8* BufferPtr, uint32 BufferSize, int32 Version, uint64 ThreadCycle);`
- L164 _private prototype_ `FThreadInfo& GetOrAddThread(uint32 ThreadId);`
- L166 _private prototype_ `void UpdateThreadTime(const UE::Trace::IAnalyzer::FOnEventContext& Context, uint64 Cycle);`
- L167 _private prototype_ `void OnUpdateThreadTime(uint32 ThreadId, const UE::Trace::IAnalyzer::FOnEventContext& Context, uint64 Cycle);`
- L170 _private member_ `static constexpr uint32 InvalidEventId = ~0u;`
- L171 _private member_ `static constexpr uint32 MaxKnownEventId = 0xFFFF;`
- L173 _private member_ `TArray<FKnownEvent> KnownEvents;` — [EKnownEvent::Count]
- L174 _private member_ `TArray<EKnownEvent> KnownEventMap;` — index == EventId --> EKnownEvent; [MaxKnownEventId + 1]
- L175 _private member_ `TSet<uint32> CycleEvents;` — events with a uint64 "Cycle" field.
- L177 _private member_ `TMap<uint32, FThreadInfo> ThreadMap;` — ThreadId --> FThreadInfo
- L179 _private member_ `FOnUpdateThreadTimeFunc OnUpdateThreadTimeCallback;`

#### enum `TraceServices::FKnownEventProcessor::EKnownEvent`  
`enum class EKnownEvent : uint32`  
_L23-117_
- L25 _public enumerator_ `Invalid`
- L27 _public enumerator_ `Trace_NewEvent`
- L45 _public enumerator_ `Misc_Bookmark` — Misc_CreateThread, Misc_SetThreadGroup, Misc_BeginThreadGroupScope, Misc_BookmarkSpec,
- L46 _public enumerator_ `Misc_ScreenshotHeader`
- L48 _public enumerator_ `Misc_RegionBegin` — Misc_ScreenshotChunk,
- L49 _public enumerator_ `Misc_RegionBeginWithId`
- L50 _public enumerator_ `Misc_RegionEnd`
- L51 _public enumerator_ `Misc_RegionEndWithId`
- L56 _public enumerator_ `Misc_BeginFrame` — Misc_BeginGameFrame, // deprecated Misc_EndGameFrame, // deprecated Misc_BeginRenderFrame, // deprecated Misc_EndRenderFrame, // deprecated
- L57 _public enumerator_ `Misc_EndFrame`
- L61 _public enumerator_ `Logging_LogMessage` — Logging_LogCategory, Logging_LogMessageSpec,
- L63 _public enumerator_ `PlatformFile_BeginOpen`
- L64 _public enumerator_ `PlatformFile_EndOpen`
- L65 _public enumerator_ `PlatformFile_BeginRead`
- L66 _public enumerator_ `PlatformFile_EndRead`
- L67 _public enumerator_ `PlatformFile_BeginClose`
- L68 _public enumerator_ `PlatformFile_EndClose`
- L80 _public enumerator_ `GpuProfiler_EventBeginBreadcrumb` — GpuProfiler_EventSpec, // old GpuProfiler, deprecated GpuProfiler_Frame, // old GpuProfiler, deprecated GpuProfiler_Frame2, // old GpuProfiler, deprecated GpuProfiler_Init, GpuProfiler_QueueSpec, GpuProfiler_EventFrameBoundary, GpuProfiler_EventBreadcrumbSpec,
- L81 _public enumerator_ `GpuProfiler_EventEndBreadcrumb`
- L82 _public enumerator_ `GpuProfiler_EventBeginWork`
- L83 _public enumerator_ `GpuProfiler_EventEndWork`
- L84 _public enumerator_ `GpuProfiler_EventWait`
- L86 _public enumerator_ `GpuProfiler_SignalFence` — GpuProfiler_EventStats,
- L87 _public enumerator_ `GpuProfiler_WaitFence`
- L91 _public enumerator_ `CpuProfiler_Metadata` — CpuProfiler_EventSpec, CpuProfiler_MetadataSpec, // added in UE 5.x
- L92 _public enumerator_ `CpuProfiler_EventBatchV3` — added in UE 5.6
- L93 _public enumerator_ `CpuProfiler_EventBatchV2` — backward compatibility; added in UE 5.1, removed in 5.6
- L94 _public enumerator_ `CpuProfiler_EventBatch` — backward compatibility; removed in UE 5.1
- L95 _public enumerator_ `CpuProfiler_EndCapture` — backward compatibility; removed in UE 5.1
- L96 _public enumerator_ `CpuProfiler_EndThread` — "Cycle" field added in UE 5.4
- L108 _public enumerator_ `Memory_Marker`
- L110 _public enumerator_ `LLM_TagValue`
- L114 _public enumerator_ `SlateTrace_AddWidget`
- L116 _public enumerator_ `Count`

#### struct `TraceServices::FKnownEventProcessor::FKnownEvent`  
`struct FKnownEvent`  
_L121-125_
- L123 _public member_ `uint32 Id = InvalidEventId;`
- L124 _public member_ `KnownEventCallback Callback = nullptr;`

#### struct `TraceServices::FKnownEventProcessor::FThreadInfo`  
`struct FThreadInfo`  
_L127-132_
- L129 _public member_ `uint32 Id = 0;`
- L130 _public member_ `uint32 Reserved = 0;` — for padding
- L131 _public member_ `uint64 Cycle = 0;`

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace TraceServices`

### `Source/Developer/TraceServices/Private/Analyzers/LoadTimeTraceAnalysis.h` (Private)


#### class `TraceServices::FAsyncLoadingTraceAnalyzer`  
`class FAsyncLoadingTraceAnalyzer : public UE::Trace::IAnalyzer`  
_L22-185_
- inherits: `UE::Trace::IAnalyzer`
- L25 _public prototype_ `FAsyncLoadingTraceAnalyzer(IAnalysisSession& Session, FLoadTimeProfilerProvider& LoadTimeProfilerProvider);`
- L26 _public prototype_ `virtual ~FAsyncLoadingTraceAnalyzer();`
- L28 _public prototype_ `virtual void OnAnalysisBegin(const FOnAnalysisContext& Context) override;`
- L29 _public prototype_ `virtual void OnAnalysisEnd() override;`
- L30 _public prototype_ `virtual bool OnEvent(uint16 RouteId, EStyle Style, const FOnEventContext& Context) override;`
- L94 _private prototype_ `void PackageRequestAssociation(const FOnEventContext& Context, FAsyncPackageState* AsyncPackageState, FRequestState* RequestState);`
- L95 _private prototype_ `FThreadState& GetThreadState(uint32 ThreadId);`
- L96 _private prototype_ `const FClassInfo* GetClassInfo(uint64 ClassPtr) const;`
- L140 _private member_ `TCHAR FormatBuffer[FormatBufferSize];`
- L141 _private member_ `TCHAR TempBuffer[FormatBufferSize];`
- L143 _private member_ `IAnalysisSession& Session;`
- L144 _private member_ `FLoadTimeProfilerProvider& LoadTimeProfilerProvider;`
- L172 _private typedef_ `template<typename ValueType> using TPointerMap = TMap<uint64, ValueType, FDefaultSetAllocator, FPointerMapKeyFuncs<ValueType>>;`
- L174 _private member_ `TPointerMap<FAsyncPackageState*> ActiveAsyncPackagesMap;`
- L175 _private member_ `TPointerMap<FLinkerLoadState*> ActiveLinkersMap;`
- L176 _private member_ `TPointerMap<FPackageExportInfo*> ExportsMap;`
- L177 _private member_ `TMap<uint64, FRequestState*> ActiveRequestsMap;`
- L178 _private member_ `TArray<FRequestState*> FakeRequestsStack;`
- L179 _private member_ `TPointerMap<uint64> ActiveBatchesMap;`
- L180 _private member_ `TMap<uint32, FThreadState*> ThreadStatesMap;`
- L181 _private member_ `TPointerMap<const FClassInfo*> ClassInfosMap;`
- L182 _private member_ `FPackageInfo* UnknownPackageInfo = nullptr;`
- L183 _private member_ `uint64 ErrorCount = 0;`
- L184 _private member_ `uint64 WarningCount = 0;`

#### struct `TraceServices::FAsyncLoadingTraceAnalyzer::FRequestGroupState`  
`struct FRequestGroupState`  
_L37-44_
- L39 _public member_ `FString Name;`
- L40 _public member_ `TArray<FRequestState*> Requests;`
- L41 _public member_ `FLoadRequest* LoadRequest = nullptr;`
- L42 _public member_ `uint64 LatestEndCycle = 0;`
- L43 _public member_ `uint64 ActiveRequestsCount = 0;`

#### struct `TraceServices::FAsyncLoadingTraceAnalyzer::FRequestState`  
`struct FRequestState`  
_L46-53_
- L48 _public member_ `uint64 WallTimeStartCycle;`
- L49 _public member_ `uint64 WallTimeEndCycle;`
- L50 _public member_ `uint32 ThreadId;`
- L51 _public member_ `TSharedPtr<FRequestGroupState> Group;`
- L52 _public member_ `TArray<FAsyncPackageState*> AsyncPackages;`

#### struct `TraceServices::FAsyncLoadingTraceAnalyzer::FAsyncPackageState`  
`struct FAsyncPackageState`  
_L55-62_
- L57 _public member_ `FPackageInfo* PackageInfo = nullptr;`
- L58 _public member_ `FRequestState* Request = nullptr;`
- L59 _public member_ `FLinkerLoadState* Linker = nullptr;`
- L60 _public member_ `TSet<FAsyncPackageState*> ImportedAsyncPackages;`
- L61 _public member_ `TSet<FAsyncPackageState*> ImportedByAsyncPackages;`

#### struct `TraceServices::FAsyncLoadingTraceAnalyzer::FLinkerLoadState`  
`struct FLinkerLoadState`  
_L64-69_
- L66 _public member_ `FPackageInfo* PackageInfo = nullptr;`
- L67 _public member_ `FAsyncPackageState* AsyncPackage = nullptr;`
- L68 _public member_ `bool bHasFakeAsyncPackageState = false;`

#### struct `TraceServices::FAsyncLoadingTraceAnalyzer::FScopeStackEntry`  
`struct FScopeStackEntry`  
_L71-75_
- L73 _public member_ `FLoadTimeProfilerCpuEvent Event;`
- L74 _public member_ `bool EnteredEvent;`

#### struct `TraceServices::FAsyncLoadingTraceAnalyzer::FThreadState`  
`struct FThreadState`  
_L77-92_
- L79 _public member_ `FScopeStackEntry CpuScopeStack[256];`
- L80 _public member_ `uint64 CpuScopeStackDepth = 0;`
- L81 _public member_ `int64 PostLoadScopeDepth = 0;`
- L82 _public member_ `FLoadTimeProfilerCpuEvent CurrentEvent;`
- L83 _public member_ `TArray<TSharedPtr<FRequestGroupState>> RequestGroupStack;`
- L85 _public member_ `FLoadTimeProfilerProvider::CpuTimelineInternal* CpuTimeline;`
- L87 _public prototype_ `void EnterScope(double Time, const FPackageInfo* PackageInfo);`
- L88 _public prototype_ `void EnterScope(double Time, const FPackageExportInfo* ExportInfo, ELoadTimeProfilerObjectEventType EventType);`
- L89 _public prototype_ `void LeaveScope(double Time);`
- L90 _public prototype_ `ELoadTimeProfilerObjectEventType GetCurrentScopeEventType();`
- L91 _public prototype_ `FPackageExportInfo* GetCurrentExportScope();`

#### enum `TraceServices::FAsyncLoadingTraceAnalyzer::(anonymous)`  
``  
_L99-134_

#### enum `TraceServices::FAsyncLoadingTraceAnalyzer::(anonymous)`  
``  
_L137-139_

#### struct `TraceServices::FAsyncLoadingTraceAnalyzer::FPointerMapKeyFuncs`  
`template<typename ValueType> struct FPointerMapKeyFuncs`  
_L147-169_
- L149 _public typedef_ `typedef uint64 KeyType;`
- L150 _public typedef_ `typedef uint64 KeyInitType;`
- L151 _public typedef_ `typedef const TPairInitializer<uint64, ValueType>& ElementInitType;`
- L155 _public function_ `static FORCEINLINE bool Matches(uint64 A, uint64 B)`
- L160 _public function_ `static FORCEINLINE uint32 GetKeyHash(uint64 Key)`
- L165 _public function_ `static FORCEINLINE KeyInitType GetSetKey(ElementInitType Element)`

#### enum `TraceServices::FAsyncLoadingTraceAnalyzer::FPointerMapKeyFuncs::(anonymous)`  
`enum`  
_L153-153_

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace TraceServices`
- L15 _function_ `inline bool operator!=(const FLoadTimeProfilerCpuEvent& Lhs, const FLoadTimeProfilerCpuEvent& Rhs)` (scope `TraceServices`)
- L100 _enumerator_ `RouteId_StartAsyncLoading` (scope `TraceServices::FAsyncLoadingTraceAnalyzer::__anon9933a2170103`)
- L101 _enumerator_ `RouteId_SuspendAsyncLoading` (scope `TraceServices::FAsyncLoadingTraceAnalyzer::__anon9933a2170103`)
- L102 _enumerator_ `RouteId_ResumeAsyncLoading` (scope `TraceServices::FAsyncLoadingTraceAnalyzer::__anon9933a2170103`)
- L103 _enumerator_ `RouteId_NewAsyncPackage` (scope `TraceServices::FAsyncLoadingTraceAnalyzer::__anon9933a2170103`)
- L104 _enumerator_ `RouteId_DestroyAsyncPackage` (scope `TraceServices::FAsyncLoadingTraceAnalyzer::__anon9933a2170103`)
- L105 _enumerator_ `RouteId_NewLinker` (scope `TraceServices::FAsyncLoadingTraceAnalyzer::__anon9933a2170103`)
- L106 _enumerator_ `RouteId_DestroyLinker` (scope `TraceServices::FAsyncLoadingTraceAnalyzer::__anon9933a2170103`)
- L107 _enumerator_ `RouteId_BeginRequest` (scope `TraceServices::FAsyncLoadingTraceAnalyzer::__anon9933a2170103`)
- L108 _enumerator_ `RouteId_EndRequest` (scope `TraceServices::FAsyncLoadingTraceAnalyzer::__anon9933a2170103`)
- L109 _enumerator_ `RouteId_BeginRequestGroup` (scope `TraceServices::FAsyncLoadingTraceAnalyzer::__anon9933a2170103`)
- L110 _enumerator_ `RouteId_EndRequestGroup` (scope `TraceServices::FAsyncLoadingTraceAnalyzer::__anon9933a2170103`)
- L111 _enumerator_ `RouteId_PackageSummary` (scope `TraceServices::FAsyncLoadingTraceAnalyzer::__anon9933a2170103`)
- L112 _enumerator_ `RouteId_AsyncPackageRequestAssociation` (scope `TraceServices::FAsyncLoadingTraceAnalyzer::__anon9933a2170103`)
- L113 _enumerator_ `RouteId_AsyncPackageLinkerAssociation` (scope `TraceServices::FAsyncLoadingTraceAnalyzer::__anon9933a2170103`)
- L114 _enumerator_ `RouteId_AsyncPackageImportDependency` (scope `TraceServices::FAsyncLoadingTraceAnalyzer::__anon9933a2170103`)
- L115 _enumerator_ `RouteId_BeginProcessSummary` (scope `TraceServices::FAsyncLoadingTraceAnalyzer::__anon9933a2170103`)
- L116 _enumerator_ `RouteId_EndProcessSummary` (scope `TraceServices::FAsyncLoadingTraceAnalyzer::__anon9933a2170103`)
- L117 _enumerator_ `RouteId_BeginCreateExport` (scope `TraceServices::FAsyncLoadingTraceAnalyzer::__anon9933a2170103`)
- L118 _enumerator_ `RouteId_EndCreateExport` (scope `TraceServices::FAsyncLoadingTraceAnalyzer::__anon9933a2170103`)
- L119 _enumerator_ `RouteId_BeginSerializeExport` (scope `TraceServices::FAsyncLoadingTraceAnalyzer::__anon9933a2170103`)
- L120 _enumerator_ `RouteId_EndSerializeExport` (scope `TraceServices::FAsyncLoadingTraceAnalyzer::__anon9933a2170103`)
- L121 _enumerator_ `RouteId_BeginPostLoad` (scope `TraceServices::FAsyncLoadingTraceAnalyzer::__anon9933a2170103`)
- L122 _enumerator_ `RouteId_EndPostLoad` (scope `TraceServices::FAsyncLoadingTraceAnalyzer::__anon9933a2170103`)
- L123 _enumerator_ `RouteId_BeginPostLoadObject` (scope `TraceServices::FAsyncLoadingTraceAnalyzer::__anon9933a2170103`)
- L124 _enumerator_ `RouteId_EndPostLoadObject` (scope `TraceServices::FAsyncLoadingTraceAnalyzer::__anon9933a2170103`)
- L125 _enumerator_ `RouteId_ClassInfo` (scope `TraceServices::FAsyncLoadingTraceAnalyzer::__anon9933a2170103`)
- L126 _enumerator_ `RouteId_BatchIssued` (scope `TraceServices::FAsyncLoadingTraceAnalyzer::__anon9933a2170103`)
- L127 _enumerator_ `RouteId_BatchResolved` (scope `TraceServices::FAsyncLoadingTraceAnalyzer::__anon9933a2170103`)
- L130 _enumerator_ `RouteId_BeginObjectScope` (scope `TraceServices::FAsyncLoadingTraceAnalyzer::__anon9933a2170103`) — Backwards compatibility
- L131 _enumerator_ `RouteId_EndObjectScope` (scope `TraceServices::FAsyncLoadingTraceAnalyzer::__anon9933a2170103`)
- L132 _enumerator_ `RouteId_BeginPostLoadExport` (scope `TraceServices::FAsyncLoadingTraceAnalyzer::__anon9933a2170103`)
- L133 _enumerator_ `RouteId_EndPostLoadExport` (scope `TraceServices::FAsyncLoadingTraceAnalyzer::__anon9933a2170103`)
- L138 _enumerator_ `FormatBufferSize = 65536` (scope `TraceServices::FAsyncLoadingTraceAnalyzer::__anon9933a2170203`)
- L153 _enumerator_ `enum { bAllowDuplicateKeys = false }; static FORCEINLINE bool Matches(uint64 A, uint64 B) { return A == B; } static FORCEINLINE uint32 GetKeyHash(uint64 Key)` (scope `TraceServices::FAsyncLoadingTraceAnalyzer::FPointerMapKeyFuncs::__anon9933a2170303`)

### `Source/Developer/TraceServices/Private/Analyzers/LogTraceAnalysis.h` (Private)


#### class `TraceServices::FLogTraceAnalyzer`  
`class FLogTraceAnalyzer : public UE::Trace::IAnalyzer`  
_L13-32_
- inherits: `UE::Trace::IAnalyzer`
- L17 _public prototype_ `FLogTraceAnalyzer(IAnalysisSession& Session, FLogProvider& LogProvider);`
- L18 _public prototype_ `virtual void OnAnalysisBegin(const FOnAnalysisContext& Context) override;`
- L19 _public prototype_ `virtual void OnAnalysisEnd() override;`
- L20 _public prototype_ `virtual bool OnEvent(uint16 RouteId, EStyle Style, const FOnEventContext& Context) override;`
- L30 _private member_ `IAnalysisSession& Session;`
- L31 _private member_ `FLogProvider& LogProvider;`

#### enum `TraceServices::FLogTraceAnalyzer::(anonymous)`  
``  
_L24-28_

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace TraceServices`
- L25 _enumerator_ `RouteId_LogCategory` (scope `TraceServices::FLogTraceAnalyzer::__anonc59f3d8a0103`)
- L26 _enumerator_ `RouteId_LogMessageSpec` (scope `TraceServices::FLogTraceAnalyzer::__anonc59f3d8a0103`)
- L27 _enumerator_ `RouteId_LogMessage` (scope `TraceServices::FLogTraceAnalyzer::__anonc59f3d8a0103`)

### `Source/Developer/TraceServices/Private/Analyzers/MemoryAnalysis.h` (Private)


#### class `TraceServices::FMemoryAnalyzer`  
`class FMemoryAnalyzer : public UE::Trace::IAnalyzer`  
_L16-38_
- inherits: `UE::Trace::IAnalyzer`
- L20 _public prototype_ `FMemoryAnalyzer(IAnalysisSession& Session, FMemoryProvider* InProvider);`
- L21 _public prototype_ `~FMemoryAnalyzer();`
- L22 _public prototype_ `virtual void OnAnalysisBegin(const FOnAnalysisContext& Context) override;`
- L23 _public prototype_ `virtual void OnAnalysisEnd() override;`
- L24 _public prototype_ `virtual bool OnEvent(uint16 RouteId, EStyle Style, const FOnEventContext& Context) override;`
- L35 _private member_ `IAnalysisSession& Session;`
- L36 _private member_ `FMemoryProvider* Provider;`
- L37 _private member_ `uint64 Sample = 0;`

#### enum `TraceServices::FMemoryAnalyzer::(anonymous)`  
``  
_L28-33_

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace TraceServices`
- L29 _enumerator_ `RouteId_TagsSpec` (scope `TraceServices::FMemoryAnalyzer::__anonda9391320103`)
- L30 _enumerator_ `RouteId_TagSetSpec` (scope `TraceServices::FMemoryAnalyzer::__anonda9391320103`)
- L31 _enumerator_ `RouteId_TrackerSpec` (scope `TraceServices::FMemoryAnalyzer::__anonda9391320103`)
- L32 _enumerator_ `RouteId_TagValue` (scope `TraceServices::FMemoryAnalyzer::__anonda9391320103`)

### `Source/Developer/TraceServices/Private/Analyzers/MetadataAnalysis.h` (Private)


#### class `TraceServices::FMetadataAnalysis`  
`class FMetadataAnalysis : public UE::Trace::IAnalyzer`  
_L14-38_
- inherits: `UE::Trace::IAnalyzer`
- L17 _public prototype_ `FMetadataAnalysis(IAnalysisSession& Session, FMetadataProvider* InProvider);`
- L20 _public prototype_ `virtual void OnAnalysisBegin(const FOnAnalysisContext& Context) override;`
- L21 _public prototype_ `virtual void OnAnalysisEnd() override;`
- L22 _public prototype_ `virtual bool OnEvent(uint16 RouteId, EStyle Style, const FOnEventContext& Context) override;`
- L25 _private prototype_ `uint16 GetOrRegisterType(const FEventTypeInfo& EventInfo);`
- L35 _private member_ `IAnalysisSession& Session;`
- L36 _private member_ `FMetadataProvider* MetadataProvider;`
- L37 _private member_ `TMap<uint32,uint16> EncounteredMetadataTypes;`

#### enum `TraceServices::FMetadataAnalysis::EMetadataRouteIds`  
`enum EMetadataRouteIds`  
_L27-33_
- L29 _public enumerator_ `RouteId_ClearScope`
- L30 _public enumerator_ `RouteId_SaveStack`
- L31 _public enumerator_ `RouteId_RestoreStack`
- L32 _public enumerator_ `RouteId_Metascope`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace TraceServices`

### `Source/Developer/TraceServices/Private/Analyzers/MiscTraceAnalysis.h` (Private)


#### class `TraceServices::FMiscTraceAnalyzer`  
`class FMiscTraceAnalyzer : public UE::Trace::IAnalyzer`  
_L21-81_
- inherits: `UE::Trace::IAnalyzer`
- L25 _public prototype_ `FMiscTraceAnalyzer(IAnalysisSession& Session, FThreadProvider& ThreadProvider, FLogProvider& LogProvider, FFrameProvider& FrameProvider, FChannelProvider& ChannelProvider, FScreenshotProvider& ScreenshotProvider, FRegionProvider& RegionProvider);`
- L32 _public prototype_ `virtual void OnAnalysisBegin(const FOnAnalysisContext& Context) override;`
- L33 _public prototype_ `virtual void OnAnalysisEnd() override;`
- L34 _public prototype_ `virtual void OnThreadInfo(const FThreadInfo& ThreadInfo) override;`
- L35 _public prototype_ `virtual bool OnEvent(uint16 RouteId, EStyle Style, const FOnEventContext& Context) override;`
- L66 _private prototype_ `FThreadState* GetThreadState(uint32 ThreadId);`
- L67 _private prototype_ `void OnChannelAnnounce(const FOnEventContext& Context);`
- L68 _private prototype_ `void OnChannelToggle(const FOnEventContext& Context);`
- L70 _private member_ `IAnalysisSession& Session;`
- L71 _private member_ `FThreadProvider& ThreadProvider;`
- L72 _private member_ `FLogProvider& LogProvider;`
- L73 _private member_ `FFrameProvider& FrameProvider;`
- L74 _private member_ `FChannelProvider& ChannelProvider;`
- L75 _private member_ `FScreenshotProvider& ScreenshotProvider;`
- L76 _private member_ `FRegionProvider& RegionProvider;`
- L78 _private member_ `TMap<uint32, TSharedRef<FThreadState>> ThreadStateMap;`
- L79 _private member_ `uint64 LastFrameCycle[TraceFrameType_Count] = { 0, 0 };`
- L80 _private member_ `uint64 ScreenshotLogCategoryId = uint64(-1);`

#### enum `TraceServices::FMiscTraceAnalyzer::(anonymous)`  
``  
_L39-59_

#### struct `TraceServices::FMiscTraceAnalyzer::FThreadState`  
`struct FThreadState`  
_L61-64_
- L63 _public member_ `TArray<const TCHAR*> ThreadGroupStack;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace TraceServices`
- L40 _enumerator_ `RouteId_RegisterGameThread` (scope `TraceServices::FMiscTraceAnalyzer::__anonf01689340103`)
- L41 _enumerator_ `RouteId_CreateThread` (scope `TraceServices::FMiscTraceAnalyzer::__anonf01689340103`)
- L42 _enumerator_ `RouteId_SetThreadGroup` (scope `TraceServices::FMiscTraceAnalyzer::__anonf01689340103`)
- L43 _enumerator_ `RouteId_BeginThreadGroupScope` (scope `TraceServices::FMiscTraceAnalyzer::__anonf01689340103`)
- L44 _enumerator_ `RouteId_EndThreadGroupScope` (scope `TraceServices::FMiscTraceAnalyzer::__anonf01689340103`)
- L45 _enumerator_ `RouteId_BeginFrame` (scope `TraceServices::FMiscTraceAnalyzer::__anonf01689340103`)
- L46 _enumerator_ `RouteId_EndFrame` (scope `TraceServices::FMiscTraceAnalyzer::__anonf01689340103`)
- L47 _enumerator_ `RouteId_BeginGameFrame` (scope `TraceServices::FMiscTraceAnalyzer::__anonf01689340103`)
- L48 _enumerator_ `RouteId_EndGameFrame` (scope `TraceServices::FMiscTraceAnalyzer::__anonf01689340103`)
- L49 _enumerator_ `RouteId_BeginRenderFrame` (scope `TraceServices::FMiscTraceAnalyzer::__anonf01689340103`)
- L50 _enumerator_ `RouteId_EndRenderFrame` (scope `TraceServices::FMiscTraceAnalyzer::__anonf01689340103`)
- L51 _enumerator_ `RouteId_ChannelAnnounce` (scope `TraceServices::FMiscTraceAnalyzer::__anonf01689340103`)
- L52 _enumerator_ `RouteId_ChannelToggle` (scope `TraceServices::FMiscTraceAnalyzer::__anonf01689340103`)
- L53 _enumerator_ `RouteId_ScreenshotHeader` (scope `TraceServices::FMiscTraceAnalyzer::__anonf01689340103`)
- L54 _enumerator_ `RouteId_ScreenshotChunk` (scope `TraceServices::FMiscTraceAnalyzer::__anonf01689340103`)
- L55 _enumerator_ `RouteId_RegionBegin` (scope `TraceServices::FMiscTraceAnalyzer::__anonf01689340103`)
- L56 _enumerator_ `RouteId_RegionBeginWithId` (scope `TraceServices::FMiscTraceAnalyzer::__anonf01689340103`)
- L57 _enumerator_ `RouteId_RegionEnd` (scope `TraceServices::FMiscTraceAnalyzer::__anonf01689340103`)
- L58 _enumerator_ `RouteId_RegionEndWithId` (scope `TraceServices::FMiscTraceAnalyzer::__anonf01689340103`)

### `Source/Developer/TraceServices/Private/Analyzers/ModuleAnalysis.h` (Private)


#### class `TraceServices::FModuleAnalyzer`  
`class FModuleAnalyzer : public UE::Trace::IAnalyzer`  
_L13-29_
- inherits: `UE::Trace::IAnalyzer`
- L17 _public prototype_ `FModuleAnalyzer(IAnalysisSession& Session);`
- L18 _public prototype_ `virtual void OnAnalysisBegin(const FOnAnalysisContext& Context) override;`
- L19 _public prototype_ `virtual void OnAnalysisEnd() override;`
- L20 _public prototype_ `virtual bool OnEvent(uint16 RouteId, EStyle Style, const FOnEventContext& Context) override;`
- L23 _private prototype_ `uint64 GetBaseAddress(const FEventData& EventData) const;`
- L26 _private member_ `IAnalysisSession& Session;`
- L27 _private member_ `IModuleAnalysisProvider* Provider;`
- L28 _private member_ `uint8 ModuleBaseShift;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace TraceServices`

### `Source/Developer/TraceServices/Private/Analyzers/NetTraceAnalyzer.h` (Private)


#### class `TraceServices::FNetTraceAnalyzer`  
`class FNetTraceAnalyzer : public UE::Trace::IAnalyzer`  
_L18-166_
- inherits: `UE::Trace::IAnalyzer`
- L22 _public prototype_ `FNetTraceAnalyzer(IAnalysisSession& Session, FNetProfilerProvider& NetProfilerProvider);`
- L23 _public prototype_ `virtual void OnAnalysisBegin(const FOnAnalysisContext& Context) override;`
- L24 _public prototype_ `virtual bool OnEvent(uint16 RouteId, EStyle Style, const FOnEventContext& Context) override;`
- L25 _public prototype_ `virtual void OnAnalysisEnd() override;`
- L58 _private member_ `IAnalysisSession& Session;`
- L59 _private member_ `FNetProfilerProvider& NetProfilerProvider;`
- L60 _private member_ `const IFrameProvider& FrameProvider;`
- L61 _private member_ `uint32 NetTraceVersion;`
- L62 _private member_ `uint32 NetTraceReporterVersion;`
- L65 _private member_ `FNetProfilerNameIndexType BunchHeaderNameIndex;` — Default names
- L66 _private member_ `FNetProfilerNameIndexType PendingNameIndex;`
- L69 _private member_ `TMap<FNetProfilerNameIndexType, FNetProfilerNameIndexType> TracedNameIdToNetProfilerNameIdMap;` — Shared for trace
- L71 _private member_ `TMap<uint64, uint32> TraceEventTypeToNetProfilerEventTypeIndexMap;`
- L73 _private member_ `TMap<FNetProfilerNameIndexType, uint32> TraceNetStatsCounterIdToNetProfilerStatsCounterTypeIndexMap;`
- L129 _private prototype_ `uint32 GetTracedEventTypeIndex(FNetProfilerNameIndexType NameIndex, uint8 Level);`
- L130 _private prototype_ `uint32 GetOrCreateNetProfilerStatsCounterTypeIndex(FNetProfilerNameIndexType NameId, ENetProfilerStatsCounterType StatsType);`
- L132 _private prototype_ `TSharedRef<FNetTraceGameInstanceState> GetOrCreateActiveGameInstanceState(uint32 GameInstanceId);`
- L133 _private prototype_ `void DestroyActiveGameInstanceState(uint32 GameInstanceId);`
- L135 _private prototype_ `FNetTraceConnectionState* GetActiveConnectionState(uint32 GameInstanceId, uint32 ConnectionId);`
- L136 _private function_ `FNetProfilerTimeStamp GetLastTimestamp() const`
- L138 _private prototype_ `void FlushPacketEvents(FNetTraceConnectionState& ConnectionState, FNetProfilerConnectionData& ConnectionData, const ENetProfilerConnectionMode ConnectionMode);`
- L140 _private prototype_ `void FlushFrameStatsCounters(FNetTraceGameInstanceState& GameInstanceState);`
- L141 _private prototype_ `uint32 GetCurrentNetProfilerFrameIndexAndFlushFrameStatsCountersIfNeeded(uint32 GameInstanceId, uint32 EngineFrameIndex);`
- L143 _private prototype_ `void HandlePacketEvent(const FOnEventContext& Context, const FEventData& EventData);`
- L144 _private prototype_ `void HandlePacketContentEvent(const FOnEventContext& Context, const FEventData& EventData);`
- L145 _private prototype_ `void HandlePacketDroppedEvent(const FOnEventContext& Context, const FEventData& EventData);`
- L146 _private prototype_ `void HandleConnectionStateUpdatedEvent(const FOnEventContext& Context, const FEventData& EventData);`
- L147 _private prototype_ `void HandleConnectionCreatedEvent(const FOnEventContext& Context, const FEventData& EventData);`
- L148 _private prototype_ `void HandleConnectionUpdatedEvent(const FOnEventContext& Context, const FEventData& EventData);`
- L149 _private prototype_ `void HandleConnectionClosedEvent(const FOnEventContext& Context, const FEventData& EventData);`
- L150 _private prototype_ `void HandleFrameStatsCounterEvent(const FOnEventContext& Context, const FEventData& EventData);`
- L151 _private prototype_ `void HandlePacketStatsCounterEvent(const FOnEventContext& Context, const FEventData& EventData);`
- L152 _private prototype_ `void HandleObjectCreatedEvent(const FOnEventContext& Context, const FEventData& EventData);`
- L153 _private prototype_ `void HandleObjectExistsEvent(const FOnEventContext& Context, const FEventData& EventData);`
- L154 _private prototype_ `void HandleObjectDestroyedEvent(const FOnEventContext& Context, const FEventData& EventData);`
- L156 _private prototype_ `void HandleGameInstanceUpdatedEvent(const FOnEventContext& Context, const FEventData& EventData);`
- L158 _private prototype_ `void AddEvent(TPagedArray<FNetProfilerContentEvent>& Events, const FNetProfilerContentEvent& Event, uint32 Offset, uint32 LevelOffset);`
- L159 _private prototype_ `void AddEvent(TPagedArray<FNetProfilerContentEvent>& Events, uint32 StartPos, uint32 EndPos, uint32 Level, FNetProfilerNameIndexType NameIndex, FNetProfilerBunchInfo Info);`
- L163 _private member_ `TMap<uint32, TSharedRef<FNetTraceGameInstanceState>> ActiveGameInstances;`
- L164 _private member_ `FNetProfilerTimeStamp StartTimeStamp;`
- L165 _private member_ `FNetProfilerTimeStamp LastTimeStamp;`

#### enum `TraceServices::FNetTraceAnalyzer::(anonymous)`  
``  
_L30-47_

#### enum `TraceServices::FNetTraceAnalyzer::EContentEventType`  
`enum class EContentEventType : uint8`  
_L50-56_
- desc: This must be kept in sync with Event types in NetTrace.h
- L52 _public enumerator_ `Object = 0`
- L53 _public enumerator_ `NameId = 1`
- L54 _public enumerator_ `BunchEvent = 2`
- L55 _public enumerator_ `BunchHeaderEvent = 3`

#### struct `TraceServices::FNetTraceAnalyzer::FBunchInfo`  
`struct FBunchInfo`  
_L75-83_
- L77 _public member_ `FNetProfilerBunchInfo BunchInfo;`
- L78 _public member_ `uint32 BunchBits;`
- L79 _public member_ `uint32 HeaderBits;`
- L80 _public member_ `int32 FirstBunchEventIndex;`
- L81 _public member_ `uint32 EventCount;`
- L82 _public member_ `FNetProfilerNameIndexType NameIndex;`

#### struct `TraceServices::FNetTraceAnalyzer::FNetTraceConnectionState`  
`struct FNetTraceConnectionState`  
_L85-104_
- L88 _public member_ `uint32 ConnectionIndex;` — Index into persistent connection array
- L91 _public member_ `uint32 CurrentPacketStartIndex[ENetProfilerConnectionMode::Count];` — Current packet data
- L92 _public member_ `uint32 CurrentPacketBitOffset[ENetProfilerConnectionMode::Count];`
- L93 _public member_ `uint32 CurrentPacketStatsStartIndex[ENetProfilerConnectionMode::Count];`
- L96 _public member_ `TArray<FNetProfilerStats> PacketStats;` — StatsCounters reported during the current packet
- L99 _public member_ `TArray<FNetProfilerContentEvent> BunchEvents[ENetProfilerConnectionMode::Count];` — Current bunch data
- L101 _public member_ `TArray<FBunchInfo> BunchInfos[ENetProfilerConnectionMode::Count];`
- L103 _public member_ `ENetProfilerConnectionState ConnectionState;`

#### struct `TraceServices::FNetTraceAnalyzer::FNetTraceActiveObjectState`  
`struct FNetTraceActiveObjectState`  
_L106-110_
- L108 _public member_ `uint32 ObjectIndex;`
- L109 _public member_ `FNetProfilerNameIndexType NameIndex;`

#### struct `TraceServices::FNetTraceAnalyzer::FNetTraceGameInstanceState`  
`struct FNetTraceGameInstanceState`  
_L113-125_
- desc: Map from instance id to index in the persistent instance array
- L115 _public member_ `TMap<uint32, TSharedRef<FNetTraceConnectionState>> ActiveConnections;`
- L116 _public member_ `TMap<uint64, FNetTraceActiveObjectState> ActiveObjects;`
- L117 _public member_ `TMap<int32, FNetProfilerNameIndexType> ChannelNames;`
- L120 _public member_ `TArray<FNetProfilerStats> FrameStatsCounters;` — StatsCounters reported during the current frame
- L121 _public member_ `uint32 CurrentEngineFrameIndex = 0;`
- L122 _public member_ `uint32 CurrentNetProfilerFrameIndex = 0;`
- L124 _public member_ `uint32 GameInstanceIndex;`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace TraceServices`
- L31 _enumerator_ `RouteId_InitEvent` (scope `TraceServices::FNetTraceAnalyzer::__anon84780ff10103`)
- L32 _enumerator_ `RouteId_InstanceDestroyedEvent` (scope `TraceServices::FNetTraceAnalyzer::__anon84780ff10103`)
- L33 _enumerator_ `RouteId_NameEvent` (scope `TraceServices::FNetTraceAnalyzer::__anon84780ff10103`)
- L34 _enumerator_ `RouteId_PacketContentEvent` (scope `TraceServices::FNetTraceAnalyzer::__anon84780ff10103`)
- L35 _enumerator_ `RouteId_PacketEvent` (scope `TraceServices::FNetTraceAnalyzer::__anon84780ff10103`)
- L36 _enumerator_ `RouteId_PacketDroppedEvent` (scope `TraceServices::FNetTraceAnalyzer::__anon84780ff10103`)
- L37 _enumerator_ `RouteId_ConnectionCreatedEvent` (scope `TraceServices::FNetTraceAnalyzer::__anon84780ff10103`)
- L38 _enumerator_ `RouteId_ConnectionUpdatedEvent` (scope `TraceServices::FNetTraceAnalyzer::__anon84780ff10103`)
- L39 _enumerator_ `RouteId_ConnectionClosedEvent` (scope `TraceServices::FNetTraceAnalyzer::__anon84780ff10103`)
- L40 _enumerator_ `RouteId_PacketStatsCounterEvent` (scope `TraceServices::FNetTraceAnalyzer::__anon84780ff10103`)
- L41 _enumerator_ `RouteId_FrameStatsCounterEvent` (scope `TraceServices::FNetTraceAnalyzer::__anon84780ff10103`)
- L42 _enumerator_ `RouteId_ObjectCreatedEvent` (scope `TraceServices::FNetTraceAnalyzer::__anon84780ff10103`)
- L43 _enumerator_ `RouteId_ObjectExistsEvent` (scope `TraceServices::FNetTraceAnalyzer::__anon84780ff10103`)
- L44 _enumerator_ `RouteId_ObjectDestroyedEvent` (scope `TraceServices::FNetTraceAnalyzer::__anon84780ff10103`)
- L45 _enumerator_ `RouteId_ConnectionStateUpdatedEvent` (scope `TraceServices::FNetTraceAnalyzer::__anon84780ff10103`)
- L46 _enumerator_ `RouteId_InstanceUpdatedEvent` (scope `TraceServices::FNetTraceAnalyzer::__anon84780ff10103`)

### `Source/Developer/TraceServices/Private/Analyzers/ObjectTraceAnalysis.h` (Private)


#### class `TraceServices::FObjectAnalyzer`  
`class FObjectAnalyzer : public UE::Trace::IAnalyzer`  
_L16-56_
- inherits: `UE::Trace::IAnalyzer`
- L36 _public prototype_ `FObjectAnalyzer(IAnalysisSession& Session, IEditableObjectProvider& InEditableObjectProvider);`
- L37 _public prototype_ `virtual void OnAnalysisBegin(const FOnAnalysisContext& Context) override;`
- L38 _public prototype_ `virtual void OnAnalysisEnd() override;`
- L39 _public prototype_ `virtual bool OnEvent(uint16 RouteId, EStyle Style, const FOnEventContext& Context) override;`
- L42 _private prototype_ `bool CheckValidSnapshotForEvent(const ANSICHAR* EventName);`
- L43 _private prototype_ `void LogErrorForEventWithInvalidObjectId(const ANSICHAR* EventName, uint32 Id);`
- L46 _private member_ `IAnalysisSession& Session;`
- L47 _private member_ `IEditableObjectProvider& EditableProvider;`
- L49 _private member_ `static constexpr uint32 InvalidSnapshotId = uint32(-1);`
- L50 _private member_ `uint32 CurrentSnapshotId = InvalidSnapshotId;`
- L51 _private member_ `double SnapshotLastTime = 0.0;`
- L52 _private member_ `uint32 NumWarnings = 0;`
- L53 _private member_ `uint32 NumErrors = 0;`
- L54 _private member_ `static constexpr uint32 MaxWarningMessages = 100;`
- L55 _private member_ `static constexpr uint32 MaxErrorMessages = 100;`

#### enum `TraceServices::FObjectAnalyzer::(anonymous)`  
``  
_L20-33_

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace TraceServices`
- L21 _enumerator_ `RouteId_BeginSnapshot` (scope `TraceServices::FObjectAnalyzer::__anonc15f749f0103`)
- L22 _enumerator_ `RouteId_EndSnapshot` (scope `TraceServices::FObjectAnalyzer::__anonc15f749f0103`)
- L23 _enumerator_ `RouteId_ObjectSpec` (scope `TraceServices::FObjectAnalyzer::__anonc15f749f0103`)
- L24 _enumerator_ `RouteId_VerseExtraSpec` (scope `TraceServices::FObjectAnalyzer::__anonc15f749f0103`)
- L25 _enumerator_ `RouteId_ResourceSizeExtraSpec` (scope `TraceServices::FObjectAnalyzer::__anonc15f749f0103`)
- L26 _enumerator_ `RouteId_TotalResourceSizeExtraSpec` (scope `TraceServices::FObjectAnalyzer::__anonc15f749f0103`)
- L27 _enumerator_ `RouteId_FieldExtraSpec` (scope `TraceServices::FObjectAnalyzer::__anonc15f749f0103`)
- L28 _enumerator_ `RouteId_StructExtraSpec` (scope `TraceServices::FObjectAnalyzer::__anonc15f749f0103`)
- L29 _enumerator_ `RouteId_ClassExtraSpec` (scope `TraceServices::FObjectAnalyzer::__anonc15f749f0103`)
- L30 _enumerator_ `RouteId_FunctionExtraSpec` (scope `TraceServices::FObjectAnalyzer::__anonc15f749f0103`)
- L31 _enumerator_ `RouteId_PackageExtraSpec` (scope `TraceServices::FObjectAnalyzer::__anonc15f749f0103`)
- L32 _enumerator_ `RouteId_ObjectRef` (scope `TraceServices::FObjectAnalyzer::__anonc15f749f0103`)

### `Source/Developer/TraceServices/Private/Analyzers/OldGpuProfilerTraceAnalysis.h` (Private)


#### class `TraceServices::FOldGpuProfilerAnalyzer`  
`class FOldGpuProfilerAnalyzer : public UE::Trace::IAnalyzer`  
_L17-46_
- inherits: `UE::Trace::IAnalyzer`
- desc: The Old GPU Profiler (deprecated in UE 5.6) Analysis code is maintained for backward compatibility with old traces.
- L28 _public prototype_ `FOldGpuProfilerAnalyzer(FAnalysisSession& Session, FTimingProfilerProvider& TimingProfilerProvider);`
- L29 _public prototype_ `virtual void OnAnalysisBegin(const FOnAnalysisContext& Context) override;`
- L30 _public prototype_ `virtual void OnAnalysisEnd() override;`
- L31 _public prototype_ `virtual bool OnEvent(uint16 RouteId, EStyle Style, const FOnEventContext& Context) override;`
- L34 _private prototype_ `void OnEventSpec(const FOnEventContext& Context);`
- L35 _private prototype_ `void OnFrame(const FOnEventContext& Context, uint32 GpuIndex = 0);`
- L38 _private member_ `FAnalysisSession& Session;`
- L39 _private member_ `FTimingProfilerProvider& TimingProfilerProvider;`
- L41 _private member_ `TMap<uint64, uint32> EventTypeMap;`
- L42 _private member_ `double MinTime = DBL_MIN;`
- L43 _private member_ `double MinTime2 = DBL_MIN;`
- L44 _private member_ `uint32 NumFrames = 0;`
- L45 _private member_ `uint32 NumFramesWithErrors = 0;`

#### enum `TraceServices::FOldGpuProfilerAnalyzer::(anonymous)`  
``  
_L21-25_

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace TraceServices`
- L22 _enumerator_ `RouteId_EventSpec` (scope `TraceServices::FOldGpuProfilerAnalyzer::__anon677338b60103`)
- L23 _enumerator_ `RouteId_Frame` (scope `TraceServices::FOldGpuProfilerAnalyzer::__anon677338b60103`) — GPU Index 0
- L24 _enumerator_ `RouteId_Frame2` (scope `TraceServices::FOldGpuProfilerAnalyzer::__anon677338b60103`) — GPU Index 1

### `Source/Developer/TraceServices/Private/Analyzers/PlatformEventTraceAnalysis.h` (Private)


#### class `TraceServices::FPlatformEventTraceAnalyzer`  
`class FPlatformEventTraceAnalyzer : public UE::Trace::IAnalyzer`  
_L15-39_
- inherits: `UE::Trace::IAnalyzer`
- L19 _public prototype_ `FPlatformEventTraceAnalyzer(IAnalysisSession& Session, FContextSwitchesProvider& ContextSwitchesProvider, FStackSamplesProvider& StackSamplesProvider);`
- L22 _public prototype_ `virtual void OnAnalysisBegin(const FOnAnalysisContext& Context) override;`
- L23 _public prototype_ `virtual void OnAnalysisEnd() override;`
- L24 _public prototype_ `virtual bool OnEvent(uint16 RouteId, EStyle Style, const FOnEventContext& Context) override;`
- L25 _public prototype_ `virtual void OnThreadInfo(const FThreadInfo& ThreadInfo) override;`
- L36 _private member_ `IAnalysisSession& Session;`
- L37 _private member_ `FContextSwitchesProvider& ContextSwitchesProvider;`
- L38 _private member_ `FStackSamplesProvider& StackSamplesProvider;`

#### enum `TraceServices::FPlatformEventTraceAnalyzer::(anonymous)`  
``  
_L29-34_

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace TraceServices`
- L30 _enumerator_ `RouteId_Settings` (scope `TraceServices::FPlatformEventTraceAnalyzer::__anon273893af0103`)
- L31 _enumerator_ `RouteId_ContextSwitch` (scope `TraceServices::FPlatformEventTraceAnalyzer::__anon273893af0103`)
- L32 _enumerator_ `RouteId_StackSample` (scope `TraceServices::FPlatformEventTraceAnalyzer::__anon273893af0103`)
- L33 _enumerator_ `RouteId_ThreadName` (scope `TraceServices::FPlatformEventTraceAnalyzer::__anon273893af0103`)

### `Source/Developer/TraceServices/Private/Analyzers/PlatformFileTraceAnalysis.h` (Private)


#### class `TraceServices::FPlatformFileTraceAnalyzer`  
`class FPlatformFileTraceAnalyzer : public UE::Trace::IAnalyzer`  
_L15-55_
- inherits: `UE::Trace::IAnalyzer`
- L19 _public prototype_ `FPlatformFileTraceAnalyzer(IAnalysisSession& Session, FFileActivityProvider& FileActivityProvider);`
- L20 _public prototype_ `virtual void OnAnalysisBegin(const FOnAnalysisContext& Context) override;`
- L21 _public prototype_ `virtual bool OnEvent(uint16 RouteId, EStyle Style, const FOnEventContext& Context) override;`
- L47 _private member_ `IAnalysisSession& Session;`
- L48 _private member_ `FFileActivityProvider& FileActivityProvider;`
- L49 _private member_ `TMap<uint64, uint32> OpenFilesMap;`
- L50 _private member_ `TMap<uint32, FPendingActivity> PendingOpenMap;`
- L51 _private member_ `TMap<uint32, FPendingActivity> PendingReOpenMap;`
- L52 _private member_ `TMap<uint32, FPendingActivity> PendingCloseMap;`
- L53 _private member_ `TMap<uint64, FPendingActivity> ActiveReadsMap;`
- L54 _private member_ `TMap<uint64, FPendingActivity> ActiveWritesMap;`

#### enum `TraceServices::FPlatformFileTraceAnalyzer::(anonymous)`  
``  
_L25-38_

#### struct `TraceServices::FPlatformFileTraceAnalyzer::FPendingActivity`  
`struct FPendingActivity`  
_L40-45_
- L42 _public member_ `uint64 ActivityIndex;`
- L43 _public member_ `uint32 FileIndex;`
- L44 _public member_ `uint32 ThreadId;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace TraceServices`
- L26 _enumerator_ `RouteId_BeginOpen` (scope `TraceServices::FPlatformFileTraceAnalyzer::__anon74a83b2d0103`)
- L27 _enumerator_ `RouteId_EndOpen` (scope `TraceServices::FPlatformFileTraceAnalyzer::__anon74a83b2d0103`)
- L28 _enumerator_ `RouteId_BeginReOpen` (scope `TraceServices::FPlatformFileTraceAnalyzer::__anon74a83b2d0103`)
- L29 _enumerator_ `RouteId_EndReOpen` (scope `TraceServices::FPlatformFileTraceAnalyzer::__anon74a83b2d0103`)
- L30 _enumerator_ `RouteId_BeginClose` (scope `TraceServices::FPlatformFileTraceAnalyzer::__anon74a83b2d0103`)
- L31 _enumerator_ `RouteId_EndClose` (scope `TraceServices::FPlatformFileTraceAnalyzer::__anon74a83b2d0103`)
- L32 _enumerator_ `RouteId_BeginRead` (scope `TraceServices::FPlatformFileTraceAnalyzer::__anon74a83b2d0103`)
- L33 _enumerator_ `RouteId_EndRead` (scope `TraceServices::FPlatformFileTraceAnalyzer::__anon74a83b2d0103`)
- L34 _enumerator_ `RouteId_BeginWrite` (scope `TraceServices::FPlatformFileTraceAnalyzer::__anon74a83b2d0103`)
- L35 _enumerator_ `RouteId_EndWrite` (scope `TraceServices::FPlatformFileTraceAnalyzer::__anon74a83b2d0103`)
- L37 _enumerator_ `RouteId_Count` (scope `TraceServices::FPlatformFileTraceAnalyzer::__anon74a83b2d0103`)

### `Source/Developer/TraceServices/Private/Analyzers/StatsTraceAnalysis.h` (Private)


#### class `TraceServices::FStatsAnalyzer`  
`class FStatsAnalyzer : public UE::Trace::IAnalyzer`  
_L17-52_
- inherits: `UE::Trace::IAnalyzer`
- L21 _public prototype_ `FStatsAnalyzer(IAnalysisSession& Session, IEditableCounterProvider& InEditableCounterProvider);`
- L22 _public prototype_ `virtual void OnAnalysisBegin(const FOnAnalysisContext& Context) override;`
- L23 _public prototype_ `virtual void OnAnalysisEnd() override;`
- L24 _public prototype_ `virtual bool OnEvent(uint16 RouteId, EStyle Style, const FOnEventContext& Context) override;`
- L27 _private prototype_ `void CreateFrameCounters();`
- L44 _private prototype_ `TSharedRef<FThreadState> GetThreadState(uint32 ThreadId);`
- L46 _private member_ `IAnalysisSession& Session;`
- L47 _private member_ `IEditableCounterProvider& EditableCounterProvider;`
- L48 _private member_ `TMap<uint32, IEditableCounter*> EditableCountersMap;`
- L49 _private member_ `TMap<uint32, IEditableCounter*> Int64ResetEveryFrameCountersMap;`
- L50 _private member_ `TMap<uint32, IEditableCounter*> FloatResetEveryFrameCountersMap;`
- L51 _private member_ `TMap<uint32, TSharedRef<FThreadState>> ThreadStatesMap;`

#### enum `TraceServices::FStatsAnalyzer::(anonymous)`  
``  
_L31-37_

#### struct `TraceServices::FStatsAnalyzer::FThreadState`  
`struct FThreadState`  
_L39-42_
- L41 _public member_ `uint64 LastCycle = 0;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace TraceServices`
- L32 _enumerator_ `RouteId_Spec` (scope `TraceServices::FStatsAnalyzer::__anon93748d770103`)
- L33 _enumerator_ `RouteId_EventBatch` (scope `TraceServices::FStatsAnalyzer::__anon93748d770103`)
- L34 _enumerator_ `RouteId_EventBatch2` (scope `TraceServices::FStatsAnalyzer::__anon93748d770103`)
- L35 _enumerator_ `RouteId_BeginFrame` (scope `TraceServices::FStatsAnalyzer::__anon93748d770103`)
- L36 _enumerator_ `RouteId_EndFrame` (scope `TraceServices::FStatsAnalyzer::__anon93748d770103`)

### `Source/Developer/TraceServices/Private/Analyzers/StringsAnalyzer.h` (Private)


#### class `TraceServices::FStringsAnalyzer`  
`class FStringsAnalyzer : public UE::Trace::IAnalyzer`  
_L9-27_
- inherits: `UE::Trace::IAnalyzer`
- L12 _public function_ `FStringsAnalyzer(IAnalysisSession& InSession) : Session(InSession)`
- L23 _private prototype_ `virtual void OnAnalysisBegin(const FOnAnalysisContext& Context) override;`
- L24 _private prototype_ `virtual bool OnEvent(uint16 RouteId, EStyle Style, const FOnEventContext& Context) override;`
- L26 _private member_ `IAnalysisSession& Session;`

#### enum `TraceServices::FStringsAnalyzer::ERouteId`  
`enum ERouteId : uint16`  
_L18-22_
- L20 _public enumerator_ `RouteId_StaticString`
- L21 _public enumerator_ `RouteId_FName`

#### Free symbols / members of external scopes

- L6 _namespace_ `namespace TraceServices`

### `Source/Developer/TraceServices/Private/Analyzers/TasksAnalysis.h` (Private)


#### class `TraceServices::FTasksAnalyzer`  
`class FTasksAnalyzer : public UE::Trace::IAnalyzer`  
_L13-41_
- inherits: `UE::Trace::IAnalyzer`
- desc: deserialises tasks traces and feeds them to FTasksProvider
- L16 _public prototype_ `FTasksAnalyzer(IAnalysisSession& Session, FTasksProvider& TasksProvider);`
- L17 _public prototype_ `virtual void OnAnalysisBegin(const FOnAnalysisContext& Context) override;`
- L18 _public prototype_ `virtual bool OnEvent(uint16 RouteId, EStyle Style, const FOnEventContext& Context) override;`
- L39 _private member_ `IAnalysisSession& Session;`
- L40 _private member_ `FTasksProvider& TasksProvider;`

#### enum `TraceServices::FTasksAnalyzer::(anonymous)`  
``  
_L22-37_

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace TraceServices`
- L23 _enumerator_ `RouteId_Init` (scope `TraceServices::FTasksAnalyzer::__anon3336401f0103`)
- L24 _enumerator_ `RouteId_Created` (scope `TraceServices::FTasksAnalyzer::__anon3336401f0103`)
- L25 _enumerator_ `RouteId_Launched` (scope `TraceServices::FTasksAnalyzer::__anon3336401f0103`)
- L26 _enumerator_ `RouteId_Scheduled` (scope `TraceServices::FTasksAnalyzer::__anon3336401f0103`)
- L27 _enumerator_ `RouteId_SubsequentAdded` (scope `TraceServices::FTasksAnalyzer::__anon3336401f0103`)
- L28 _enumerator_ `RouteId_Started` (scope `TraceServices::FTasksAnalyzer::__anon3336401f0103`)
- L30 _enumerator_ `RouteId_NestedAdded` (scope `TraceServices::FTasksAnalyzer::__anon3336401f0103`) — `NestedAdded` was removed from `TaskTrace` but left here to avoid crashing TasksInsights when used with an old trace file
- L31 _enumerator_ `RouteId_Finished` (scope `TraceServices::FTasksAnalyzer::__anon3336401f0103`)
- L32 _enumerator_ `RouteId_Completed` (scope `TraceServices::FTasksAnalyzer::__anon3336401f0103`)
- L33 _enumerator_ `RouteId_Destroyed` (scope `TraceServices::FTasksAnalyzer::__anon3336401f0103`)
- L35 _enumerator_ `RouteId_WaitingStarted` (scope `TraceServices::FTasksAnalyzer::__anon3336401f0103`)
- L36 _enumerator_ `RouteId_WaitingFinished` (scope `TraceServices::FTasksAnalyzer::__anon3336401f0103`)

### `Source/Developer/TraceServices/Private/Analyzers/TrimAnalyzer.h` (Private)


#### class `TraceServices::FTrimAnalyzer`  
`class FTrimAnalyzer : public UE::Trace::IAnalyzer`  
_L29-133_
- inherits: `UE::Trace::IAnalyzer`
- L61 _public prototype_ `FTrimAnalyzer(FTrimParameters& InParameters, UE::Trace::FTraceWriter& InTraceWriter);`
- L62 _public prototype_ `virtual ~FTrimAnalyzer();`
- L64 _public function_ `uint32 GetNumErrors() const`
- L65 _public function_ `uint32 GetNumWarnings() const`
- L68 _private prototype_ `void InitNameFilter(const FAnsiString& InFilter, FNameFilter& OutNameFilter);`
- L69 _private prototype_ `bool FilterByEventName(const ANSICHAR* LoggerName, const ANSICHAR* EventName);`
- L71 _private prototype_ `virtual void OnAnalysisBegin(const UE::Trace::IAnalyzer::FOnAnalysisContext& Context) override;`
- L72 _private prototype_ `virtual void OnAnalysisEnd() override;`
- L73 _private prototype_ `virtual void OnVersion(uint32 InTransportVersion, uint32 InProtocolVersion) override;`
- L74 _private prototype_ `virtual bool OnNewEvent(uint16 RouteId, const FEventTypeInfo& TypeInfo) override;`
- L75 _private prototype_ `virtual bool OnEvent(uint16 RouteId, EStyle, const UE::Trace::IAnalyzer::FOnEventContext& Context) override;`
- L77 _private prototype_ `void WriteArrayField(uint32 FieldIndex, const UE::Trace::IAnalyzer::FEventFieldInfo& FieldInfo, const UE::Trace::IAnalyzer::FEventData& EventData, UE::Trace::FTraceWriterEventBuilder& EventBuilder);`
- L78 _private prototype_ `void WriteScalarField(uint32 FieldIndex, const UE::Trace::IAnalyzer::FEventFieldInfo& FieldInfo, const UE::Trace::IAnalyzer::FEventData& EventData, UE::Trace::FTraceWriterEventBuilder& EventBuilder);`
- L80 _private prototype_ `FThreadInfo& GetOrAddThread(uint32 ThreadId);`
- L81 _private prototype_ `void SortThreads(int32 ThreadIndex);`
- L82 _private prototype_ `bool UpdateThreadsOnSyncEvent(FThreadInfo& CurrentThread);`
- L83 _private prototype_ `void SetCurrentThread(uint32 ThreadId);`
- L84 _private prototype_ `void UpdateThreadTime(FThreadInfo& Thread, const UE::Trace::IAnalyzer::FOnEventContext& Context, uint64 Cycle);`
- L87 _private member_ `FTrimParameters& Parameters;`
- L88 _private member_ `UE::Trace::FTraceWriter& TraceWriter;`
- L90 _private member_ `uint32 TransportVersion = 4;`
- L91 _private member_ `uint32 ProtocolVersion = 7;`
- L93 _private member_ `static constexpr uint32 ThreadTableInitialSize = 1024;`
- L94 _private member_ `static constexpr uint32 ThreadTableMaxSize = 4 * 1024;`
- L96 _private member_ `TMap<uint32, FThreadInfo*> ThreadMap;` — ThreadId --> FThreadInfo
- L97 _private member_ `TArray<FThreadInfo*> ThreadTable;` — index == ThreadId, for ThreadId < ThreadTableMaxSize
- L98 _private member_ `TArray<FThreadInfo*> SortedThreads;` — sorted threads by time
- L100 _private member_ `TMap<uint32, FEventInfo> EventInfos;` — EventId --> FEventInfo
- L101 _private member_ `FEventInfo EmptyEventInfo;`
- L103 _private member_ `uint64 ReadEvents = 0;`
- L104 _private member_ `uint64 WrittenEvents = 0;`
- L106 _private member_ `uint64 LastProgressMessageTimestamp = 0;`
- L107 _private member_ `uint64 ProgressMessageInterval = 0;`
- L109 _private member_ `uint64 AnalysisBeginTimestamp = 0;` — realtime timestamp
- L111 _private member_ `uint64 SessionCycleFrequency = 0;`
- L112 _private member_ `uint64 SessionStartCycle = 0;`
- L113 _private member_ `double SessionStartTimeSinceEpoch = 0.0;`
- L115 _private member_ `uint64 SessionCurrentCycle = 0;` — absolute session time
- L116 _private member_ `double SessionCurrentTime = 0.0;` — relative session time, in [seconds]
- L118 _private member_ `FNameFilter IncludeFilter;`
- L119 _private member_ `FNameFilter ExcludeFilter;`
- L121 _private member_ `static constexpr uint32 InvalidEventId = ~0u;`
- L122 _private member_ `static constexpr uint32 InvalidWriterEventId = ~0u;`
- L124 _private member_ `uint32 TraceNewTraceEventId = InvalidEventId;`
- L125 _private member_ `bool bIsTraceNewTraceEventDetected = false;`
- L127 _private member_ `uint32 TraceThreadInfoEventId = InvalidEventId;`
- L129 _private member_ `FKnownEventProcessor KnownEvents;`
- L131 _private member_ `uint32 NumErrors = 0;`
- L132 _private member_ `uint32 NumWarnings = 0;`

#### struct `TraceServices::FTrimAnalyzer::FEventInfo`  
`struct FEventInfo`  
_L32-37_
- L34 _public member_ `const FEventTypeInfo* TypeInfo = nullptr;`
- L35 _public member_ `uint32 WriterEventId = ~0u;`
- L36 _public member_ `bool bIsFilteredOut = false;`

#### struct `TraceServices::FTrimAnalyzer::FNameFilterPattern`  
`struct FNameFilterPattern`  
_L39-43_
- L41 _public member_ `FAnsiString LoggerName;`
- L42 _public member_ `FAnsiString EventName;`

#### struct `TraceServices::FTrimAnalyzer::FNameFilter`  
`struct FNameFilter`  
_L45-50_
- L47 _public function_ `bool IsEmpty() const`
- L49 _public member_ `TArray<FNameFilterPattern> Patterns;`

#### struct `TraceServices::FTrimAnalyzer::FThreadInfo`  
`struct FThreadInfo`  
_L52-58_
- L54 _public member_ `uint32 Id = 0;`
- L55 _public member_ `int32 SortIndex = 0;`
- L56 _public member_ `uint64 CurrentCycle = 0;`
- L57 _public member_ `double CurrentTime = 0.0;`

#### Free symbols / members of external scopes

- L18 _namespace_ `namespace UE`
- L18 _namespace_ `namespace Trace` (scope `UE`)
- L24 _namespace_ `namespace TraceServices`

### `Source/Developer/TraceServices/Private/Analyzers/VerseTraceAnalysis.h` (Private)


#### class `TraceServices::FVerseAnalyzer`  
`class FVerseAnalyzer : public UE::Trace::IAnalyzer`  
_L18-55_
- inherits: `UE::Trace::IAnalyzer`
- L29 _public prototype_ `FVerseAnalyzer(IAnalysisSession& Session, FTimingProfilerProvider& InTimingProfilerProvider);`
- L30 _public prototype_ `virtual void OnAnalysisBegin(const FOnAnalysisContext& Context) override;`
- L31 _public prototype_ `virtual void OnAnalysisEnd() override;`
- L32 _public prototype_ `virtual bool OnEvent(uint16 RouteId, EStyle Style, const FOnEventContext& Context) override;`
- L35 _private prototype_ `uint32 GetUnknownVerseTimerId();`
- L36 _private prototype_ `uint32 GetVerseBytecodeTimerId();`
- L37 _private prototype_ `uint32 GetVerseNativeTimerId();`
- L40 _private member_ `IAnalysisSession& Session;`
- L41 _private member_ `FTimingProfilerProvider& TimingProfilerProvider;`
- L43 _private member_ `TArray<uint32> LastSampleStack;`
- L44 _private member_ `double LastSampleTime = 0.0;`
- L45 _private member_ `uint32 NumSamples = 0;`
- L46 _private member_ `int32 MaxStackSize = 0;`
- L48 _private member_ `TMap<uint32, uint32> Timers;` — string id -> timer id
- L49 _private member_ `uint32 UnknownTimerId = 0;`
- L50 _private member_ `uint32 BytecodeTimerId = 0;`
- L51 _private member_ `uint32 NativeTimerId = 0;`
- L52 _private member_ `uint32 NumVerseTimers = 0;`
- L54 _private member_ `static constexpr double MaxSampleDuration = 0.002;` — 2ms

#### enum `TraceServices::FVerseAnalyzer::(anonymous)`  
``  
_L22-26_

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace TraceServices`
- L23 _enumerator_ `RouteId_DeclareString` (scope `TraceServices::FVerseAnalyzer::__anon2cd46aad0103`)
- L24 _enumerator_ `RouteId_BytecodeSample` (scope `TraceServices::FVerseAnalyzer::__anon2cd46aad0103`)
- L25 _enumerator_ `RouteId_NativeSample` (scope `TraceServices::FVerseAnalyzer::__anon2cd46aad0103`)

### `Source/Developer/TraceServices/Private/Common/FormatArgs.h` (Private)


#### struct `TraceServices::FFormatArgsHelper`  
`struct FFormatArgsHelper`  
_L10-41_
- L12 _public prototype_ `static void Format(TCHAR* Out, uint64 MaxOut, TCHAR* Temp, uint64 MaxTemp, const TCHAR* FormatString, const uint8* FormatArgs);`
- L34 _private prototype_ `static const TCHAR* ExtractNextFormatArg(const TCHAR* FormatString, FFormatArgSpec& Spec);`
- L35 _private prototype_ `static void InitArgumentStream(FFormatArgsStreamContext& Context, const uint8* ArgumentsData);`
- L36 _private prototype_ `static bool AdvanceArgumentStream(FFormatArgsStreamContext& Context);`
- L37 _private prototype_ `static uint64 ExtractIntegerArgument(FFormatArgsStreamContext& ArgStream);`
- L38 _private prototype_ `static double ExtractFloatingPointArgument(FFormatArgsStreamContext& ArgStream);`
- L39 _private prototype_ `static const TCHAR* ExtractStringArgument(FFormatArgsStreamContext& ArgStream, TCHAR* Temp, int32 MaxTemp);`
- L40 _private prototype_ `static int32 FormatArgument(TCHAR* Out, int32 MaxOut, TCHAR* Temp, int32 MaxTemp, const FFormatArgSpec& ArgSpec, FFormatArgsStreamContext& ArgStream);`

#### struct `TraceServices::FFormatArgsHelper::FFormatArgSpec`  
`struct FFormatArgSpec`  
_L15-23_
- L17 _public member_ `int32 PassthroughLength;`
- L18 _public member_ `TCHAR FormatString[255];`
- L19 _public member_ `uint8 ExpectedTypeCategory;`
- L20 _public member_ `uint8 AdditionalIntegerArgumentCount;`
- L21 _public member_ `bool Valid;`
- L22 _public member_ `bool NothingPrinted;`

#### struct `TraceServices::FFormatArgsHelper::FFormatArgsStreamContext`  
`struct FFormatArgsStreamContext`  
_L25-32_
- L27 _public member_ `uint8 ArgumentCount;`
- L28 _public member_ `uint8 ArgumentTypeCategory;`
- L29 _public member_ `uint8 ArgumentTypeSize;`
- L30 _public member_ `const uint8* DescriptorPtr;`
- L31 _public member_ `const uint8* PayloadPtr;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace TraceServices`

### `Source/Developer/TraceServices/Private/Common/StringStore.h` (Private)


#### class `TraceServices::FStringStore`  
`class FStringStore : public IStringStore`  
_L16-40_
- inherits: `IStringStore`
- L19 _public prototype_ `FStringStore(FSlabAllocator& Allocator);`
- L20 _public prototype_ `virtual ~FStringStore();`
- L22 _public prototype_ `virtual const TCHAR* Find(const TCHAR* String) const override;`
- L23 _public prototype_ `virtual const TCHAR* Find(const FStringView& String) const override;`
- L25 _public prototype_ `virtual const TCHAR* Store(const TCHAR* String) override;`
- L26 _public prototype_ `virtual const TCHAR* Store(const FStringView& String) override;`
- L33 _private member_ `mutable FCriticalSection Cs;`
- L34 _private member_ `FSlabAllocator& Allocator;`
- L35 _private member_ `TMultiMap<uint32, const TCHAR*> StoredStrings;`
- L36 _private member_ `mutable TArray<const TCHAR*> FindStoredStrings;`
- L37 _private member_ `TCHAR* BufferPtr = nullptr;`
- L38 _private member_ `uint64 BufferLeft = 0;`
- L39 _private member_ `uint64 BlockCount = 0;`

#### enum `TraceServices::FStringStore::(anonymous)`  
``  
_L30-32_

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace TraceServices`
- L31 _enumerator_ `BlockSize = 4 << 20` (scope `TraceServices::FStringStore::__anone06cea890103`)

### `Source/Developer/TraceServices/Private/Common/SymbolHelper.h` (Private)


#### class `TraceServices::FSymbolHelper`  
`class FSymbolHelper`  
_L13-44_
- L17 _public typedef_ `typedef FNoLoggingCategory FLogCategoryAlias;`
- L28 _public prototype_ `static void GetSymbolSearchPaths(const FLogCategoryAlias& LogCategory, TArray<FString>& OutSearchPaths);` — Gets the list of symbol search paths declared by environment variables and the symbol search paths declared in the UnrealInsightsSettings.ini configuration file. @param LogCategory The log category the messages should be emitted to. @param OutSearchPaths An array where the found paths area added.
- L36 _private prototype_ `static void GetPathsFromEnvVars(const FLogCategoryAlias& LogCategory, TArray<FString>& OutSearchPaths);` — Gets the list of symbol search paths declared by environment variables. @param LogCategory The log category the messages should be emitted to. @param OutSearchPaths An array where the found paths area added.
- L43 _private prototype_ `static void GetPathsFromSettings(const FLogCategoryAlias& LogCategory, TArray<FString>& OutSearchPaths);` — Gets the list of symbol search paths declared in the UnrealInsightsSettings.ini configuration file. @param LogCategory The log category the messages should be emitted to. @param OutSearchPaths An array where the found paths area added.

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace TraceServices`

### `Source/Developer/TraceServices/Private/Common/SymbolStringAllocator.h` (Private)


#### class `TraceServices::FSymbolStringAllocator`  
`class FSymbolStringAllocator`  
_L17-56_
- desc: An allocator for strings as a wrapper over a linear allocator. The memory allocated is owned by the provided linear allocator. So, the lifetime of stored strings is the same as the linear allocator.
- L20 _public function_ `FSymbolStringAllocator(ILinearAllocator& InAllocator, uint32 InBlockSize) : Allocator(InAllocator) , BlockSize(InBlockSize)`
- L26 _public function_ `const TCHAR* Store(const TCHAR* InString)`
- L31 _public prototype_ `const TCHAR* Store(const FStringView InString);`
- L33 _public function_ `uint64 GetUsedSize() const`
- L38 _public function_ `uint64 GetAllocatedSize() const`
- L43 _public function_ `uint32 GetNumAllocatedBlocks() const`
- L49 _private member_ `ILinearAllocator& Allocator;`
- L50 _private member_ `TCHAR* Block = nullptr;`
- L51 _private member_ `uint32 BlockSize;`
- L52 _private member_ `uint32 BlockRemaining = 0;`
- L53 _private member_ `uint32 NumAllocatedBlocks = 0;`
- L54 _private member_ `uint64 TotalAllocatedSize = 0;`
- L55 _private member_ `uint64 TotalUsedSize = 0;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace TraceServices`

### `Source/Developer/TraceServices/Private/Common/TimelineStatistics.h` (Private)


#### struct `TraceServices::FAggregatedTimingStats`  
`struct FAggregatedTimingStats`  
_L24-38_
- L26 _public member_ `uint64 InstanceCount = 0;`
- L27 _public member_ `double AverageInstanceCount = 0.0;`
- L28 _public member_ `double TotalInclusiveTime = 0.0;`
- L29 _public member_ `double MinInclusiveTime = DBL_MAX;`
- L30 _public member_ `double MaxInclusiveTime = -DBL_MAX;`
- L31 _public member_ `double AverageInclusiveTime = 0.0;`
- L32 _public member_ `double MedianInclusiveTime = 0.0;`
- L33 _public member_ `double TotalExclusiveTime = 0.0;`
- L34 _public member_ `double MinExclusiveTime = DBL_MAX;`
- L35 _public member_ `double MaxExclusiveTime = -DBL_MAX;`
- L36 _public member_ `double AverageExclusiveTime = 0.0;`
- L37 _public member_ `double MedianExclusiveTime = 0.0;`

#### struct `TraceServices::FFrameData`  
`struct FFrameData`  
_L40-44_
- L42 _public member_ `double StartTime;`
- L43 _public member_ `double EndTime;`

#### class `TraceServices::FTimelineStatistics`  
`class FTimelineStatistics`  
_L46-552_
- L101 _public function_ `static void CreateAggregation( const TArray<const TimelineType*>& Timelines, BucketMappingFunc BucketMapper, double IntervalStart, double IntervalEnd, TSharedPtr<FCancellationToken> CancellationToken, TAggregationResult<BucketKeyType, FAggregatedTimingStats>& Result)`
- L155 _public function_ `static void CreateFrameStatsAggregation( const TArray<const TimelineType*>& Timelines, BucketMappingFunc BucketMapper, const TArray<FFrameData>& Frames, TSharedPtr<FCancellationToken> CancellationToken, TAggregationResult<BucketKeyType, FAggregatedTimingStats>& Result, double RatioOfThreadsToUse)`
- L392 _private function_ `static void ProcessTimeline( const TimelineType* Timeline, BucketMappingFunc BucketMapper, CallbackType Callback, double IntervalStart, double IntervalEnd, TAggregationResult<BucketKeyType, FInternalAggregationEntry>& InternalResult)`
- L459 _private function_ `static void ProcessTimelineForFrameStats( const TimelineType* Timeline, BucketMappingFunc BucketMapper, CallbackType Callback, double IntervalStart, double IntervalEnd, TAggregationResult<BucketKeyType, FAggregatedTimingStats>& InternalResult)`
- L524 _private function_ `static void GatherKeysFromTimeline( const TimelineType* Timeline, BucketMappingFunc BucketMapper, double IntervalStart, double IntervalEnd, TAggregationResult<BucketKeyType, FAggregatedTimingStats>& InternalResult)`
- L546 _private prototype_ `static void UpdateTotalMinMaxTimerAggregationStats(FInternalAggregationEntry& AggregationEntry, double InclTime, double ExclTime);`
- L547 _private prototype_ `static void UpdateTotalMinMaxTimerStats(FAggregatedTimingStats& Stats, double InclTime, double ExclTime);`
- L548 _private prototype_ `static void InitHistogram(FInternalAggregationEntry& AggregationEntry, ILinearAllocator& Allocator);`
- L549 _private prototype_ `static void UpdateHistogram(FInternalAggregationEntry& AggregationEntry, double InclTime, double ExclTime);`
- L550 _private prototype_ `static void ComputeMedianFromHistogram(FInternalAggregationEntry& AggregationEntry);`
- L551 _private prototype_ `static void PostProcessTimerStats(FInternalAggregationEntry& AggregationEntry, bool bComputeMedian);`

#### class `TraceServices::FTimelineStatistics::TAggregationResult`  
`template<typename KeyType, typename ValueType> class TAggregationResult`  
_L50-93_
- L53 _private member_ `static constexpr uint64 AllocatorSlabSize = 1 * 1024 * 1024;`
- L56 _public function_ `TAggregationResult() : Allocator(AllocatorSlabSize)`
- L61 _public function_ `TAggregationResult(TSparseMap<KeyType, ValueType>& InMap) : Allocator(AllocatorSlabSize) , Map(InMap)`
- L68 _public prototype_ `TAggregationResult(const TAggregationResult&) = delete;` — Non-copyable
- L69 _public prototype_ `TAggregationResult& operator=(const TAggregationResult&) = delete;`
- L71 _public function_ `~TAggregationResult()`
- L75 _public function_ `ILinearAllocator& GetAllocator()`
- L80 _public function_ `TSparseMap<KeyType, ValueType>& GetMap()`
- L85 _public function_ `const TSparseMap<KeyType, ValueType>& GetMap() const`
- L91 _private member_ `FSlabAllocator Allocator;` — to allocate extra data for histograms
- L92 _private member_ `TSparseMap<KeyType, ValueType> Map;`

#### struct `TraceServices::FTimelineStatistics::FInternalAggregationEntry`  
`struct FInternalAggregationEntry`  
_L364-376_
- L366 _public prototype_ `FInternalAggregationEntry() = default;`
- L367 _public prototype_ `~FInternalAggregationEntry();`
- L369 _public member_ `FAggregatedTimingStats Stats;`
- L372 _public member_ `class FInternalHistogram* InclHistogram = nullptr;` — Histogram for computing median inclusive time.
- L375 _public member_ `class FInternalHistogram* ExclHistogram = nullptr;` — Histogram for computing median exclusive time.

#### struct `TraceServices::FTimelineStatistics::FInternalFrameAggregationEntry`  
`struct FInternalFrameAggregationEntry`  
_L378-384_
- L380 _public member_ `FInternalAggregationEntry Inner;`
- L382 _public member_ `TArray<double> FrameInclusiveTimes;`
- L383 _public member_ `TArray<double> FrameExclusiveTimes;`

#### struct `TraceServices::FTimelineStatistics::ProcessTimeline::FStackEntry`  
`struct FStackEntry`  
_L400-405_
- L402 _public member_ `double StartTime;`
- L403 _public member_ `double ExclusiveTime;`
- L404 _public member_ `BucketKeyType BucketKey;`

#### struct `TraceServices::FTimelineStatistics::ProcessTimelineForFrameStats::FStackEntry`  
`struct FStackEntry`  
_L467-472_
- L469 _public member_ `double StartTime;`
- L470 _public member_ `double ExclusiveTime;`
- L471 _public member_ `BucketKeyType BucketKey;`

#### Free symbols / members of external scopes

- L21 _namespace_ `namespace TraceServices`
- L214 _function_ `` (scope `TraceServices::FTimelineStatistics::CreateFrameStatsAggregation`)
- L413 _function_ `` (scope `TraceServices::FTimelineStatistics::ProcessTimeline`)
- L480 _function_ `` (scope `TraceServices::FTimelineStatistics::ProcessTimelineForFrameStats`)
- L534 _function_ `` (scope `TraceServices::FTimelineStatistics::GatherKeysFromTimeline`)

### `Source/Developer/TraceServices/Private/Common/Utils.h` (Private)


#### Free symbols / members of external scopes

- L10 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogTraceServices, Log, All);`
- L10 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogTraceServices, Log, All);`
- L12 _namespace_ `namespace TraceServices`
- L13 _namespace_ `namespace FTraceAnalyzerUtils` (scope `TraceServices`)
- L15 _function_ `inline uint64 Decode7bit(const uint8*& BufferPtr)` (scope `TraceServices::FTraceAnalyzerUtils`)
- L30 _function_ `inline int64 DecodeZigZag(const uint8*& BufferPtr)` (scope `TraceServices::FTraceAnalyzerUtils`)
- L36 _function_ `inline uint32 GetThreadIdField( const UE::Trace::IAnalyzer::FOnEventContext& Context, const ANSICHAR* FieldName="ThreadId")` (scope `TraceServices::FTraceAnalyzerUtils`)

### `Source/Developer/TraceServices/Private/Model/AllocMap.h` (Private)


#### class `TraceServices::FAllocMap`  
`class FAllocMap`  
_L11-136_
- L14 _public typedef_ `typedef int32 SizeType;`
- L17 _public function_ `FORCEINLINE FAllocMap()`
- L21 _public function_ `FORCEINLINE ~FAllocMap()`
- L26 _public function_ `FORCEINLINE void Empty(SizeType ExpectedNumElements = 0)`
- L32 _public function_ `FORCEINLINE void Reset()`
- L38 _public function_ `FORCEINLINE SizeType Num() const`
- L45 _public function_ `FORCEINLINE FAllocationItem* FindRef(uint64 Address) const` — Finds the allocation with the specified address. Returns the found allocation or nullptr if not found.
- L52 _public function_ `FORCEINLINE FAllocationItem* FindRange(uint64 Address) const` — Finds an allocation containing the specified address. Returns the found allocation or nullptr if not found.
- L64 _public function_ `FORCEINLINE void Enumerate(TFunctionRef<void(const FAllocationItem& Alloc)> Callback) const`
- L72 _public function_ `FORCEINLINE void Enumerate(uint64 StartAddress, uint64 EndAddress, TFunctionRef<void(const FAllocationItem& Alloc)> Callback) const`
- L85 _public function_ `FORCEINLINE void Add(FAllocationItem* Alloc)` — The collection keeps ownership of FAllocationItem* until Remove is called.
- L91 _public function_ `FORCEINLINE FAllocationItem* Remove(uint64 Address)` — The caller takes ownership of FAllocationItem*. Returns nullptr if Address is not found.
- L102 _private function_ `FORCEINLINE void DestructAllocs()`
- L135 _private member_ `TSparseMap<uint64, FAllocationItem*, FDefaultSparseSetAllocator, TAddressKeyFuncs<FAllocationItem*>> AllocsMap;`

#### struct `TraceServices::FAllocMap::TAddressKeyFuncs`  
`template<typename ValueType> struct TAddressKeyFuncs : BaseKeyFuncs<TPair<uint64, ValueType>, uint64, false>`  
_L113-132_
- inherits: `BaseKeyFuncs<TPair<uint64,ValueType>,uint64,false>`
- L115 _public typedef_ `typedef typename TTypeTraits<uint64>::ConstPointerType KeyInitType;`
- L116 _public typedef_ `typedef const TPairInitializer<typename TTypeTraits<uint64>::ConstInitType, typename TTypeTraits<ValueType>::ConstInitType>& ElementInitType;`
- L118 _public function_ `static FORCEINLINE uint64 GetSetKey(ElementInitType Element)`
- L123 _public function_ `static FORCEINLINE bool Matches(uint64 A, uint64 B)`
- L128 _public function_ `static FORCEINLINE uint32 GetKeyHash(uint64 Key)`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace TraceServices`

### `Source/Developer/TraceServices/Private/Model/AllocationItem.h` (Private)


#### struct `TraceServices::FAllocationItem`  
`struct FAllocationItem`  
_L13-153_
- L15 _public member_ `static constexpr uint64 MaxSize = (1ull << 56) - 1ull;`
- L16 _public member_ `static constexpr uint32 MaxThreadId = (1u << 16) - 1u;`
- L17 _public member_ `static constexpr uint32 MaxHeapId = (1u << 24) - 1u;`
- L18 _public member_ `static constexpr uint32 MaxFlagsValue = (1u << 8) - 1u;`
- L20 _public function_ `FORCEINLINE bool IsContained(uint64 InAddress) const`
- L25 _public function_ `FORCEINLINE uint64 GetEndAddress() const`
- L30 _public function_ `FORCEINLINE uint64 GetSize() const`
- L35 _public function_ `FORCEINLINE void SetSize(uint64 InSize)`
- L41 _public function_ `FORCEINLINE uint32 GetAlignment() const`
- L46 _public function_ `FORCEINLINE void SetAlignment(uint32 InAlignment)`
- L52 _public function_ `FORCEINLINE uint32 GetEventDistance() const`
- L57 _public function_ `FORCEINLINE void SetStartEventIndex(uint32 EventIndex)`
- L62 _public function_ `FORCEINLINE void SetEndEventIndex(uint32 EventIndex)`
- L68 _public function_ `FORCEINLINE void SetEndTime(double Time)`
- L74 _public function_ `FORCEINLINE void SetAllocThreadId(uint32 ThreadId)`
- L80 _public function_ `FORCEINLINE void SetFreeThreadId(uint32 ThreadId)`
- L86 _public function_ `FORCEINLINE HeapId GetHeapId() const`
- L91 _public function_ `FORCEINLINE void SetHeapId(HeapId InHeapId)`
- L97 _public function_ `FORCEINLINE EMemoryTraceHeapAllocationFlags GetFlags() const`
- L102 _public function_ `FORCEINLINE bool HasAnyFlags(EMemoryTraceHeapAllocationFlags Contains) const`
- L107 _public function_ `FORCEINLINE bool IsHeap() const`
- L112 _public function_ `FORCEINLINE bool IsSwap() const`
- L117 _public function_ `FORCEINLINE void SetFlags(EMemoryTraceHeapAllocationFlags InFlags)`
- L123 _public function_ `FORCEINLINE void AddHeapFlag()`
- L128 _public function_ `FORCEINLINE void RemoveHeapFlag()`
- L133 _public function_ `FORCEINLINE void AddSwapFlag()`
- L138 _public member_ `uint64 Address;`
- L139 _public member_ `uint64 Size : 56;`
- L140 _public member_ `uint64 AlignmentPow2 : 8;`
- L141 _public member_ `uint32 StartEventIndex;`
- L142 _public member_ `uint32 EndEventIndex;`
- L143 _public member_ `double StartTime;`
- L144 _public member_ `double EndTime;`
- L145 _public member_ `uint16 AllocThreadId;`
- L146 _public member_ `uint16 FreeThreadId;`
- L147 _public member_ `uint32 AllocCallstackId;`
- L148 _public member_ `uint32 FreeCallstackId;`
- L149 _public member_ `uint32 MetadataId;`
- L150 _public member_ `TagIdType Tag;` — uint32
- L151 _public member_ `uint32 Heap : 24;`
- L152 _public member_ `uint32 Flags : 8;` — EMemoryTraceHeapAllocationFlags

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace TraceServices`

### `Source/Developer/TraceServices/Private/Model/AllocationsProvider.h` (Private)


#### class `TraceServices::FTagTracker`  
`class FTagTracker`  
_L27-92_
- L30 _private member_ `static constexpr uint32 TrackerIdShift = 24;`
- L31 _private member_ `static constexpr uint32 TrackerIdMask = 0xFF000000;`
- L32 _private member_ `static constexpr TagIdType UntaggedTagId = 0;`
- L33 _private member_ `static constexpr TagIdType InvalidTagId = ~0;`
- L62 _public prototype_ `explicit FTagTracker(IAnalysisSession& Session);`
- L63 _public prototype_ `void AddTagSpec(TagIdType Tag, TagIdType ParentTag, const TCHAR* Display);`
- L64 _public prototype_ `void PushTag(uint32 ThreadId, uint8 Tracker, TagIdType Tag);`
- L65 _public prototype_ `void PopTag(uint32 ThreadId, uint8 Tracker);`
- L66 _public prototype_ `TagIdType GetCurrentTag(uint32 ThreadId, uint8 Tracker) const;`
- L67 _public prototype_ `const TCHAR* GetTagString(TagIdType Tag) const;`
- L68 _public prototype_ `const TCHAR* GetTagFullPath(TagIdType Tag) const;`
- L69 _public prototype_ `void EnumerateTags(TFunctionRef<void(const TCHAR*, const TCHAR*, TagIdType, TagIdType)> Callback) const;`
- L71 _public prototype_ `void PushTagFromPtr(uint32 ThreadId, uint8 Tracker, TagIdType Tag);`
- L72 _public prototype_ `void PopTagFromPtr(uint32 ThreadId, uint8 Tracker);`
- L73 _public prototype_ `bool HasTagFromPtrScope(uint32 ThreadId, uint8 Tracker) const;`
- L75 _public function_ `uint32 GetNumErrors() const`
- L76 _public function_ `uint32 GetNumWarnings() const`
- L79 _private prototype_ `void BuildTagPath(FStringBuilderBase& OutString, FStringView Name, TagIdType ParentTagId);`
- L80 _private function_ `static inline uint32 GetTrackerThreadId(uint32 ThreadId, uint8 Tracker)`
- L85 _private member_ `IAnalysisSession& Session;`
- L86 _private member_ `TMap<uint32, FThreadState> TrackerThreadStates;`
- L87 _private member_ `TMap<TagIdType, FTagEntry> TagMap;`
- L88 _private member_ `TArray<TTuple<TagIdType, FString>> PendingTags;`
- L89 _private member_ `TagIdType CustomNameTag = InvalidTagId;`
- L90 _private member_ `uint32 NumErrors = 0;`
- L91 _private member_ `uint32 NumWarnings = 0;`

#### enum `TraceServices::FTagTracker::ETagStackFlags`  
`enum class ETagStackFlags : uint32`  
_L35-39_
- L37 _public enumerator_ `None = 0`
- L38 _public enumerator_ `PtrScope = 1 << 0`

#### struct `TraceServices::FTagTracker::FTagStackEntry`  
`struct FTagStackEntry`  
_L41-47_
- L43 _public member_ `TagIdType Tag;`
- L44 _public member_ `ETagStackFlags Flags;`
- L46 _public function_ `inline bool IsPtrScope() const`

#### struct `TraceServices::FTagTracker::FThreadState`  
`struct FThreadState`  
_L49-52_
- L51 _public member_ `TArray<FTagStackEntry> TagStack;`

#### struct `TraceServices::FTagTracker::FTagEntry`  
`struct FTagEntry`  
_L54-59_
- L56 _public member_ `const TCHAR* Display;`
- L57 _public member_ `const TCHAR* FullPath;`
- L58 _public member_ `TagIdType ParentTag;`

#### class `TraceServices::FShortLivingAllocs`  
`class FShortLivingAllocs`  
_L96-143_
- L106 _private member_ `static constexpr int32 MaxAllocCount = 64;` — max number of short living allocations
- L109 _public prototype_ `FShortLivingAllocs();`
- L110 _public prototype_ `~FShortLivingAllocs();`
- L112 _public prototype_ `void Reset();`
- L114 _public function_ `bool IsFull() const`
- L115 _public function_ `int32 Num() const`
- L119 _public prototype_ `FORCEINLINE FAllocationItem* FindRef(uint64 Address) const;` — Finds the allocation with the specified address. Returns the found allocation or nullptr if not found.
- L123 _public prototype_ `FORCEINLINE FAllocationItem* FindRange(uint64 Address) const;` — Finds an allocation containing the specified address. Returns the found allocation or nullptr if not found.
- L125 _public prototype_ `FORCEINLINE void Enumerate(TFunctionRef<void(const FAllocationItem& Alloc)> Callback) const;`
- L126 _public prototype_ `FORCEINLINE void Enumerate(uint64 StartAddress, uint64 EndAddress, TFunctionRef<void(const FAllocationItem& Alloc)> Callback) const;`
- L131 _public prototype_ `FORCEINLINE FAllocationItem* AddAndRemoveOldest(FAllocationItem* Alloc);` — The collection keeps ownership of FAllocationItem* until Remove is called or until the oldest allocation is removed. Returns the removed oldest allocation if collection is already full; nullptr otherwise. The caller receives ownership of the removed oldest allocation, if a valid pointer is returned.
- L134 _public prototype_ `FORCEINLINE FAllocationItem* Remove(uint64 Address);` — The caller takes ownership of FAllocationItem*. Returns nullptr if Address is not found.
- L138 _private member_ `FNode* AllNodes = nullptr;` — TMap<uint64, FNode*> AddressMap; // map for short living allocations: Address -> FNode* // #if INSIGHTS_SLA_USE_ADDRESS_MAP
- L139 _private member_ `FNode* LastAddedAllocNode = nullptr;` — the last added alloc; double linked list: Prev -> .. -> OldestAlloc
- L140 _private member_ `FNode* OldestAllocNode = nullptr;` — the oldest alloc; double linked list: Next -> .. -> LastAddedAlloc
- L141 _private member_ `FNode* FirstUnusedNode = nullptr;` — simple linked list with unused nodes (uses Next)
- L142 _private member_ `int32 AllocCount = 0;`

#### struct `TraceServices::FShortLivingAllocs::FNode`  
`struct FNode`  
_L99-104_
- L101 _public member_ `FAllocationItem* Alloc;`
- L102 _public member_ `FNode* Next;`
- L103 _public member_ `FNode* Prev;`

#### class `TraceServices::FHeapAllocs`  
`class FHeapAllocs`  
_L147-191_
- L164 _public prototype_ `FHeapAllocs();`
- L165 _public prototype_ `~FHeapAllocs();`
- L167 _public prototype_ `void Reset();`
- L169 _public function_ `int32 Num() const`
- L173 _public prototype_ `FORCEINLINE FAllocationItem* FindRef(uint64 Address) const;` — Finds the last heap allocation with specified address. Returns the found allocation or nullptr if not found.
- L177 _public prototype_ `FORCEINLINE FAllocationItem* FindRange(uint64 Address) const;` — Finds a heap allocation containing the specified address. Returns the found allocation or nullptr if not found.
- L179 _public prototype_ `FORCEINLINE void Enumerate(TFunctionRef<void(const FAllocationItem& Alloc)> Callback) const;`
- L180 _public prototype_ `FORCEINLINE void Enumerate(uint64 StartAddress, uint64 EndAddress, TFunctionRef<void(const FAllocationItem& Alloc)> Callback) const;`
- L183 _public prototype_ `FORCEINLINE void Add(FAllocationItem* Alloc);` — The collection keeps ownership of FAllocationItem* until Remove is called.
- L186 _public prototype_ `FORCEINLINE FAllocationItem* Remove(uint64 Address);` — The caller takes ownership of FAllocationItem*. Returns nullptr if Address is not found.
- L189 _private member_ `TMap<uint64, FList> AddressMap;` — map heap allocs: Address -> list of heap allocs
- L190 _private member_ `int32 AllocCount = 0;`

#### struct `TraceServices::FHeapAllocs::FNode`  
`struct FNode`  
_L150-155_
- L152 _public member_ `FAllocationItem* Alloc;`
- L153 _public member_ `FNode* Next;`
- L154 _public member_ `FNode* Prev;`

#### struct `TraceServices::FHeapAllocs::FList`  
`struct FList`  
_L157-161_
- L159 _public member_ `FNode* First = nullptr;`
- L160 _public member_ `FNode* Last = nullptr;`

#### class `TraceServices::FLiveAllocCollection`  
`class FLiveAllocCollection`  
_L195-281_
- L198 _public prototype_ `FLiveAllocCollection();`
- L199 _public prototype_ `~FLiveAllocCollection();`
- L201 _public function_ `uint32 Num() const`
- L202 _public function_ `uint32 PeakCount() const`
- L206 _public prototype_ `FORCEINLINE FAllocationItem* FindRef(uint64 Address) const;` — Finds the allocation with specified address. Returns the found allocation or nullptr if not found.
- L210 _public prototype_ `FORCEINLINE FAllocationItem* FindHeapRef(uint64 Address) const;` — Finds the heap allocation with specified address. Returns the found allocation or nullptr if not found.
- L214 _public prototype_ `FORCEINLINE FAllocationItem* FindSwapRef(uint64 Address) const;` — Finds the swap allocation with specified address. Returns the found allocation or nullptr if not found.
- L218 _public prototype_ `FORCEINLINE FAllocationItem* FindByAddressRange(uint64 Address) const;` — Finds an allocation containing the address. Returns the found allocation or nullptr if not found.
- L222 _public prototype_ `FORCEINLINE FAllocationItem* FindHeapByAddressRange(uint64 Address) const;` — Finds the heap allocation containing the address. Returns the found allocation or nullptr if not found.
- L225 _public prototype_ `FORCEINLINE void Enumerate(TFunctionRef<void(const FAllocationItem& Alloc)> Callback) const;` — Enumerates all allocations (including heap allocations).
- L228 _public prototype_ `FORCEINLINE void Enumerate(uint64 StartAddress, uint64 EndAddress, TFunctionRef<void(const FAllocationItem& Alloc)> Callback) const;` — Enumerates allocations in a specified address range (including heap allocations).
- L233 _public prototype_ `FORCEINLINE FAllocationItem* AddNew(uint64 Address);` — Adds a new allocation with specified address. The collection keeps ownership of FAllocationItem* until Remove is called. Returns the new added allocation.
- L237 _public prototype_ `FORCEINLINE void Add(FAllocationItem* Alloc);` — Adds a new allocation. The collection keeps ownership of FAllocationItem* until Remove is called.
- L242 _public prototype_ `FORCEINLINE FAllocationItem* AddNewHeap(uint64 Address);` — Adds a new heap allocation with specified address. The collection keeps ownership of FAllocationItem* until RemoveHeap is called. Returns the new added allocation.
- L246 _public prototype_ `FORCEINLINE void AddHeap(FAllocationItem* HeapAlloc);` — Adds a new heap allocation. The collection keeps ownership of FAllocationItem* until RemoveHeap is called.
- L251 _public prototype_ `FORCEINLINE FAllocationItem* Remove(uint64 Address);` — Removes an allocation with specified address. The caller takes ownership of FAllocationItem*. Returns the removed allocation or nullptr if not found.
- L256 _public prototype_ `FORCEINLINE FAllocationItem* RemoveHeap(uint64 Address);` — Removes a heap allocation with specified address. The caller takes ownership of FAllocationItem*. Returns the removed heap allocation or nullptr if not found.
- L261 _public prototype_ `FORCEINLINE FAllocationItem* AddNewSwap(uint64 Address);` — Adds a new swap allocation with specified address (a memory page that was moved to swap). The collection keeps ownership of FAllocationItem* until RemoveSwap is called. Returns the new added allocation.
- L265 _public prototype_ `FORCEINLINE void AddSwap(FAllocationItem* SwapAlloc);` — Adds a new swap allocation. The collection keeps ownership of FAllocationItem* until RemoveSwap is called.
- L270 _public prototype_ `FORCEINLINE FAllocationItem* RemoveSwap(uint64 Address);` — Removes a swap allocation with specified address. The caller takes ownership of FAllocationItem*. Returns the removed swap allocation or nullptr if not found.
- L273 _private member_ `FAllocationItem* LastAlloc = nullptr;` — last allocation
- L274 _private member_ `FShortLivingAllocs ShortLivingAllocs;` — short living allocations
- L275 _private member_ `FAllocMap LongLivingAllocs;` — long living allocations
- L276 _private member_ `FHeapAllocs HeapAllocs;` — heap allocations
- L277 _private member_ `FHeapAllocs SwapAllocs;` — swap allocations (memory pages stored in swap)
- L279 _private member_ `uint32 TotalAllocCount = 0;`
- L280 _private member_ `uint32 MaxAllocCount = 0;` — debug stats

#### class `TraceServices::FAllocationsProvider`  
`class FAllocationsProvider : public IAllocationsProvider , public IEditableProvider`  
_L285-517_
- inherits: `IAllocationsProvider,IEditableProvider`
- L290 _private member_ `static constexpr double DefaultTimelineSampleGranularity = 0.0001;` — 0.1ms
- L293 _private member_ `static constexpr uint32 MaxRootHeaps = 16;` — Number of supported root heaps
- L322 _public prototype_ `explicit FAllocationsProvider(IAnalysisSession& InSession, FMetadataProvider& InMetadataProvider);`
- L323 _public prototype_ `virtual ~FAllocationsProvider();`
- L328 _public function_ `virtual void BeginRead() const override`
- L329 _public function_ `virtual void EndRead() const override`
- L330 _public function_ `virtual void ReadAccessCheck() const override`
- L332 _public function_ `virtual bool IsInitialized() const override`
- L334 _public function_ `virtual bool HasAllocationEvents() const`
- L336 _public function_ `virtual bool HasSwapOpEvents() const`
- L338 _public prototype_ `virtual void EnumerateTags(TFunctionRef<void(const TCHAR*, const TCHAR*, TagIdType, TagIdType)> Callback) const override;`
- L340 _public function_ `virtual const TCHAR* GetTagName(TagIdType Tag) const override`
- L341 _public function_ `virtual const TCHAR* GetTagFullPath(TagIdType Tag) const override`
- L342 _public function_ `bool HasTagFromPtrScope(uint32 ThreadId, uint8 Tracker) const`
- L344 _public prototype_ `virtual void EnumerateRootHeaps(TFunctionRef<void(HeapId Id, const FHeapSpec&)> Callback) const override;`
- L345 _public prototype_ `virtual void EnumerateHeaps(TFunctionRef<void(HeapId Id, const FHeapSpec&)> Callback) const override;`
- L347 _public function_ `virtual int32 GetTimelineNumPoints() const override`
- L348 _public prototype_ `virtual void GetTimelineIndexRange(double StartTime, double EndTime, int32& StartIndex, int32& EndIndex) const override;`
- L350 _public prototype_ `virtual void EnumerateTimeline(ETimelineU64 Timeline, int32 StartIndex, int32 EndIndex, TFunctionRef<void(double Time, double Duration, uint64 Value)> Callback) const override;`
- L351 _public prototype_ `virtual void EnumerateTimeline(ETimelineU32 Timeline, int32 StartIndex, int32 EndIndex, TFunctionRef<void(double Time, double Duration, uint32 Value)> Callback) const override;`
- L353 _public prototype_ `virtual FQueryHandle StartQuery(const FQueryParams& Params) const override;`
- L354 _public prototype_ `virtual void CancelQuery(FQueryHandle Query) const override;`
- L355 _public prototype_ `virtual const FQueryStatus PollQuery(FQueryHandle Query) const override;`
- L357 _public prototype_ `virtual uint64 GetPlatformPageSize() const override;`
- L359 _public function_ `const FSbTree* GetSbTreeUnchecked(HeapId Heap) const`
- L361 _public prototype_ `void EnumerateLiveAllocs(TFunctionRef<void(const FAllocationItem& Alloc)> Callback) const;`
- L362 _public prototype_ `uint32 GetNumLiveAllocs() const;`
- L364 _public prototype_ `void DebugPrint() const;`
- L369 _public function_ `virtual void BeginEdit() const override`
- L370 _public function_ `virtual void EndEdit() const override`
- L371 _public function_ `virtual void EditAccessCheck() const override`
- L373 _public prototype_ `void EditInit(double Time, uint8 MinAlignment, uint64 PlatformPageSize);`
- L375 _public prototype_ `void EditAlloc(uint32 ThreadId, double Time, uint32 CallstackId, uint64 Address, uint64 Size, uint32 Alignment, HeapId RootHeap);`
- L376 _public prototype_ `void EditFree(uint32 ThreadId, double Time, uint32 CallstackId, uint64 Address, HeapId RootHeap);`
- L377 _public prototype_ `void EditUpdateAlloc(uint32 ThreadId, double Time, uint32 CallstackId, uint64 Address, HeapId RootHeap);`
- L378 _public prototype_ `void EditSwapOp(uint32 ThreadId, double Time, uint64 UnmaskedPageAddress, EMemoryTraceSwapOperation SwapOp, uint64 CompressedPageSize, uint32 CallstackId);`
- L380 _public prototype_ `void EditHeapSpec(HeapId Id, HeapId ParentId, const FStringView& Name, EMemoryTraceHeapFlags Flags);`
- L381 _public prototype_ `void EditMarkAllocationAsHeap(uint32 ThreadId, double Time, uint32 CallstackId, uint64 Address, HeapId Heap, EMemoryTraceHeapAllocationFlags Flags);`
- L382 _public prototype_ `void EditUnmarkAllocationAsHeap(uint32 ThreadId, double Time, uint32 CallstackId, uint64 Address, HeapId Heap);`
- L384 _public function_ `void EditAddTagSpec(TagIdType Tag, TagIdType ParentTag, const TCHAR* Display)`
- L385 _public prototype_ `void EditPushTag(uint32 ThreadId, uint8 Tracker, TagIdType Tag);`
- L386 _public prototype_ `void EditPopTag(uint32 ThreadId, uint8 Tracker);`
- L387 _public prototype_ `void EditPushTagFromPtr(uint32 ThreadId, uint8 Tracker, uint64 Ptr, HeapId RootHeapId);`
- L388 _public prototype_ `void EditPopTagFromPtr(uint32 ThreadId, uint8 Tracker);`
- L390 _public prototype_ `void EditOnAnalysisCompleted(double Time);`
- L395 _private prototype_ `void AllocInternal(uint32 ThreadId, double Time, uint32 CallstackId, uint64 Address, uint64 Size, uint32 Alignment, HeapId RootHeap);`
- L396 _private prototype_ `void FreeInternal(uint32 ThreadId, double Time, uint32 CallstackId, uint64 Address, HeapId RootHeap);`
- L398 _private prototype_ `bool ShouldIgnoreEvent(uint32 ThreadId, double Time, uint64 Address, HeapId RootHeapId, uint32 CallstackId);`
- L399 _private prototype_ `void AdvanceTimelines(double Time);`
- L400 _private prototype_ `void AddHeapSpec(HeapId Id, HeapId ParentId, const FStringView& Name, EMemoryTraceHeapFlags Flags);`
- L402 _private function_ `bool IsValidHeap(HeapId HeapId) const`
- L407 _private function_ `FHeapSpec& GetHeapSpecUnchecked(HeapId Id) const`
- L412 _private prototype_ `FHeapSpec& GetOrCreateHeapSpec(HeapId Id);`
- L414 _private function_ `bool IsValidRootHeap(HeapId RootHeapId) const`
- L419 _private function_ `FRootHeap& GetRootHeapUnchecked(HeapId RootHeapId) const`
- L424 _private prototype_ `FRootHeap& FindParentRootHeapUnchecked(HeapId HeapId) const;`
- L425 _private prototype_ `void CreateRootHeap(HeapId Id);`
- L427 _private function_ `void SetSampleU64(ETimelineU64 TimelineIndex, uint64 Value)`
- L432 _private function_ `void SetMinSampleU64(ETimelineU64 TimelineIndex, uint64 Value)`
- L437 _private function_ `void SetMaxSampleU64(ETimelineU64 TimelineIndex, uint64 Value)`
- L442 _private function_ `void SetSampleU32(ETimelineU32 TimelineIndex, uint32 Value)`
- L447 _private function_ `void SetMinSampleU32(ETimelineU32 TimelineIndex, uint32 Value)`
- L452 _private function_ `void SetMaxSampleU32(ETimelineU32 TimelineIndex, uint32 Value)`
- L457 _private function_ `void IncSampleU32(ETimelineU32 TimelineIndex)`
- L464 _private member_ `mutable FProviderLock Lock;`
- L466 _private member_ `IAnalysisSession& Session;`
- L467 _private member_ `FMetadataProvider& MetadataProvider;`
- L469 _private member_ `double InitTime = 0;`
- L470 _private member_ `uint64 PlatformPageSize = 0;`
- L471 _private member_ `uint8 MinAlignment = 0;`
- L472 _private member_ `uint8 SizeShift = 0;`
- L473 _private member_ `uint8 SummarySizeShift = 0;`
- L474 _private member_ `bool bInitialized = false;`
- L476 _private member_ `FTagTracker TagTracker;`
- L478 _private member_ `TArray<FHeapSpec*> HeapSpecs;`
- L479 _private member_ `FRootHeap* RootHeaps[MaxRootHeaps] = { nullptr };`
- L481 _private member_ `uint64 AllocCount = 0;`
- L482 _private member_ `uint64 FreeCount = 0;`
- L483 _private member_ `uint64 HeapCount = 0;`
- L485 _private member_ `uint64 AllocEvents = 0;`
- L486 _private member_ `uint64 FreeEvents = 0;`
- L487 _private member_ `uint64 HeapEvents = 0;`
- L488 _private member_ `uint64 SwapOpEvents = 0;`
- L490 _private member_ `uint64 MiscWarnings = 0;`
- L491 _private member_ `uint64 MiscErrors = 0;`
- L492 _private member_ `uint64 HeapWarnings = 0;`
- L493 _private member_ `uint64 HeapErrors = 0;`
- L494 _private member_ `uint64 AllocWarnings = 0;`
- L495 _private member_ `uint64 AllocErrors = 0;`
- L496 _private member_ `uint64 FreeWarnings = 0;`
- L497 _private member_ `uint64 FreeErrors = 0;`
- L498 _private member_ `uint64 SwapWarnings = 0;`
- L499 _private member_ `uint64 SwapErrors = 0;`
- L501 _private member_ `uint64 TotalAllocatedMemory = 0;`
- L502 _private member_ `uint32 TotalLiveAllocations = 0;`
- L503 _private member_ `uint64 TotalSwapMemory = 0;`
- L504 _private member_ `uint64 TotalCompressedSwapMemory = 0;`
- L506 _private member_ `static constexpr int32 NumTimelinesU64 = int32(IAllocationsProvider::ETimelineU64::Count);`
- L507 _private member_ `static constexpr int32 NumTimelinesU32 = int32(IAllocationsProvider::ETimelineU32::Count);`
- L509 _private member_ `double SampleStartTimestamp = 0.0;`
- L510 _private member_ `double SampleEndTimestamp = 0.0;`
- L511 _private member_ `uint64 SampleValuesU64[NumTimelinesU64];`
- L512 _private member_ `uint32 SampleValuesU32[NumTimelinesU32];`
- L514 _private member_ `TPagedArray<double> Timeline;`
- L515 _private member_ `TPagedArray<uint64>* ValueTimelinesU64[NumTimelinesU64];`
- L516 _private member_ `TPagedArray<uint32>* ValueTimelinesU32[NumTimelinesU32];`

#### struct `TraceServices::FAllocationsProvider::FRootHeap`  
`struct FRootHeap`  
_L295-319_
- L297 _public prototype_ `void UpdateHistogramByAllocSize(uint64 Size);`
- L298 _public prototype_ `void UpdateHistogramByEventDistance(uint32 EventDistance);`
- L300 _public prototype_ `void LogStats();`
- L301 _public prototype_ `void LogAllocSizeHistogram();`
- L302 _public prototype_ `void LogEventDistanceHistogram();`
- L304 _public member_ `FHeapSpec* HeapSpec = nullptr;`
- L306 _public member_ `FLiveAllocCollection* LiveAllocs = nullptr;`
- L308 _public member_ `FSbTree* SbTree = nullptr;`
- L310 _public member_ `uint32 EventIndex = 0;`
- L312 _public member_ `static constexpr uint32 NumAllocSizeHistogramPow2 = 66;`
- L313 _public member_ `uint64 AllocSizeHistogramPow2[NumAllocSizeHistogramPow2] = { 0 };`
- L314 _public member_ `uint64 MaxAllocSize = 0;`
- L316 _public member_ `static constexpr uint32 NumEventDistanceHistogramPow10 = 13;`
- L317 _public member_ `uint32 EventDistanceHistogramPow10[NumEventDistanceHistogramPow10] = { 0 };`
- L318 _public member_ `uint32 MaxEventDistance = 0;`

#### Free symbols / members of external scopes

- L15 _namespace_ `namespace TraceServices`
- L23 _externvar_ `extern thread_local FProviderLock::FThreadLocalState GAllocationsProviderLockState;` (scope `TraceServices`)

### `Source/Developer/TraceServices/Private/Model/AllocationsQuery.h` (Private)


#### struct `TraceServices::FAllocationsImpl`  
`struct FAllocationsImpl`  
_L20-24_
- L22 _public member_ `FAllocationsImpl* Next = nullptr;`
- L23 _public member_ `TArray<const FAllocationItem*> Items;`

#### class `TraceServices::FAllocationsQuery`  
`class FAllocationsQuery`  
_L26-51_
- L31 _public prototype_ `FAllocationsQuery(const FAllocationsProvider& InAllocationsProvider, const IAllocationsProvider::FQueryParams& InParams);`
- L33 _public prototype_ `void Cancel();`
- L34 _public prototype_ `IAllocationsProvider::FQueryStatus Poll();`
- L37 _private prototype_ `void Run();`
- L38 _private prototype_ `void QueryLiveAllocs(TArray<const FAllocationItem*>& OutAllocs) const;`
- L41 _private member_ `const FAllocationsProvider& AllocationsProvider;`
- L43 _private member_ `IAllocationsProvider::FQueryParams Params;`
- L45 _private member_ `TQueue<FAllocationsImpl*> Results;`
- L47 _private member_ `std::atomic<bool> IsWorking;`
- L48 _private member_ `std::atomic<bool> IsCanceling;`
- L50 _private member_ `FGraphEventRef CompletedEvent;`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace TraceServices`

### `Source/Developer/TraceServices/Private/Model/BookmarksPrivate.h` (Private)


#### struct `TraceServices::FBookmarkSpec`  
`struct FBookmarkSpec`  
_L14-19_
- L16 _public member_ `const TCHAR* File = nullptr;`
- L17 _public member_ `const TCHAR* FormatString = nullptr;`
- L18 _public member_ `int32 Line = 0;`

#### struct `TraceServices::FBookmarkInternal`  
`struct FBookmarkInternal`  
_L21-26_
- L23 _public member_ `double Time = 0.0;`
- L24 _public member_ `const TCHAR* Text = nullptr;`
- L25 _public member_ `uint32 CallstackId = 0;`

#### class `TraceServices::FBookmarkProvider`  
`class FBookmarkProvider : public IBookmarkProvider , public IEditableBookmarkProvider`  
_L28-60_
- inherits: `IBookmarkProvider,IEditableBookmarkProvider`
- L33 _public prototype_ `explicit FBookmarkProvider(IAnalysisSession& Session);`
- L34 _public prototype_ `virtual ~FBookmarkProvider() = default;`
- L36 _public prototype_ `FBookmarkSpec& GetSpec(uint64 BookmarkPoint);`
- L37 _public function_ `virtual uint64 GetBookmarkCount() const override`
- L38 _public prototype_ `virtual void EnumerateBookmarks(double IntervalStart, double IntervalEnd, TFunctionRef<void(const FBookmark&)> Callback) const override;`
- L41 _public prototype_ `virtual void UpdateBookmarkSpec(uint64 BookmarkPoint, const TCHAR* FormatString, const TCHAR* File, int32 Line) override;` — implement IEditableBookmarkProvider
- L42 _public prototype_ `virtual void AppendBookmark(uint64 BookmarkPoint, double Time, uint32 CallstackId, const uint8* FormatArgs) override;`
- L43 _public prototype_ `virtual void AppendBookmark(uint64 BookmarkPoint, double Time, uint32 CallstackId, const TCHAR* Text) override;`
- L48 _private prototype_ `void CheckBookmarkForRegion(const TSharedRef<FBookmarkInternal> Shared) const;` — check whether a bookmark is actually a region marker from the deprecated/5.1 regions implementation. will forward to IEditableRegionProvider in this case
- L50 _private member_ `IAnalysisSession& Session;`
- L51 _private member_ `TMap<uint64, TSharedPtr<FBookmarkSpec>> SpecMap;`
- L52 _private member_ `TArray<TSharedRef<FBookmarkInternal>> Bookmarks;`
- L58 _private member_ `TCHAR FormatBuffer[FormatBufferSize];`
- L59 _private member_ `TCHAR TempBuffer[FormatBufferSize];`

#### enum `TraceServices::FBookmarkProvider::(anonymous)`  
``  
_L55-57_

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace TraceServices`
- L56 _enumerator_ `FormatBufferSize = 65536` (scope `TraceServices::FBookmarkProvider::__anona94636910103`)

### `Source/Developer/TraceServices/Private/Model/CallstacksProvider.h` (Private)


#### class `TraceServices::FCallstacksProvider`  
`class FCallstacksProvider : public ICallstacksProvider`  
_L17-44_
- inherits: `ICallstacksProvider`
- L20 _public prototype_ `explicit FCallstacksProvider(IAnalysisSession& Session);`
- L21 _public prototype_ `virtual ~FCallstacksProvider() = default;`
- L23 _public prototype_ `const FCallstack* GetCallstack(uint32 CallstackId) const override;`
- L24 _public prototype_ `void GetCallstacks(const TArrayView<uint32>& CallstackIds, FCallstack const** OutCallstacks) const override;`
- L25 _public prototype_ `void AddCallstack(uint32 CallstackId, const uint64* Frames, uint8 FrameCount);`
- L28 _public prototype_ `uint32 AddCallstackWithHash(uint64 CallstackHash, const uint64* Frames, uint8 FrameCount);` — Backward compatibility with legacy memory trace format (5.0-EA).
- L29 _public prototype_ `uint32 GetCallstackIdForHash(uint64 CallstackHash) const override;`
- L38 _private member_ `mutable FRWLock EntriesLock;`
- L39 _private member_ `IAnalysisSession& Session;`
- L40 _private member_ `mutable IModuleProvider* ModuleProvider;`
- L41 _private member_ `TPagedArray<FCallstack> Callstacks;` — CallstackId is an index in this array; Callstacks[0] is an empty callstack
- L42 _private member_ `TPagedArray<FStackFrame> Frames;`
- L43 _private member_ `TMap<uint64, uint32> CallstackMap;` — (CallstackHash --> CallstackId) map, used for backward compatibility with legacy trace format

#### enum `TraceServices::FCallstacksProvider::(anonymous)`  
``  
_L33-36_

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace TraceServices`
- L34 _enumerator_ `FramesPerPage = 65536` (scope `TraceServices::FCallstacksProvider::__anonfdf3559d0103`) — 16 bytes/entry -> 1 Mb per page
- L35 _enumerator_ `CallstacksPerPage = 65536 * 2` (scope `TraceServices::FCallstacksProvider::__anonfdf3559d0103`) — 8 bytes/callstack -> 1Mb per page

### `Source/Developer/TraceServices/Private/Model/Channel.h` (Private)


#### class `TraceServices::FChannelProvider`  
`class FChannelProvider : public IChannelProvider`  
_L12-29_
- inherits: `IChannelProvider`
- L15 _public prototype_ `FChannelProvider();`
- L16 _public prototype_ `virtual ~FChannelProvider() = default;`
- L18 _public prototype_ `void AnnounceChannel(const TCHAR* ChannelName, uint32 Id, bool bReadOnly);`
- L19 _public prototype_ `void UpdateChannel(uint32 Id, bool bEnabled);`
- L21 _public prototype_ `virtual uint64 GetChannelCount() const override;`
- L22 _public prototype_ `virtual const TArray<FChannelEntry>& GetChannels() const override;`
- L24 _public prototype_ `virtual FDateTime GetTimeStamp() const override;`
- L27 _private member_ `TArray<FChannelEntry> Channels;`
- L28 _private member_ `FDateTime TimeStamp;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace TraceServices`

### `Source/Developer/TraceServices/Private/Model/ContextSwitchesPrivate.h` (Private)


#### class `TraceServices::FContextSwitchesProvider`  
`class FContextSwitchesProvider : public IContextSwitchesProvider , public IEditableProvider`  
_L19-82_
- inherits: `IContextSwitchesProvider,IEditableProvider`
- L24 _public prototype_ `explicit FContextSwitchesProvider(IAnalysisSession& Session);`
- L25 _public prototype_ `virtual ~FContextSwitchesProvider();`
- L30 _public function_ `virtual void BeginRead() const override`
- L31 _public function_ `virtual void EndRead() const override`
- L32 _public function_ `virtual void ReadAccessCheck() const override`
- L34 _public prototype_ `virtual bool HasData() const override;`
- L35 _public prototype_ `virtual bool GetSystemThreadId(uint32 ThreadId, uint32& OutSystemThreadId) const override;`
- L36 _public prototype_ `virtual bool GetThreadId(uint32 SystemThreadId, uint32& OutThreadId) const override;`
- L37 _public prototype_ `virtual bool GetSystemThreadId(uint32 CoreNumber, double Time, uint32& OutSystemThreadId) const override;`
- L38 _public prototype_ `virtual bool GetThreadId(uint32 CoreNumber, double Time, uint32& OutThreadId) const override;`
- L39 _public prototype_ `virtual bool GetCoreNumber(uint32 ThreadId, double Time, uint32& OutCoreNumber) const override;`
- L40 _public function_ `virtual uint64 GetThreadsSerial() const override`
- L41 _public function_ `virtual uint64 GetCpuCoresSerial() const override`
- L42 _public prototype_ `virtual void EnumerateCpuCores(CpuCoreCallback Callback) const override;`
- L43 _public prototype_ `virtual void EnumerateContextSwitches(uint32 ThreadId, double StartTime, double EndTime, ContextSwitchCallback Callback) const override;`
- L44 _public prototype_ `virtual void EnumerateCpuCoreEvents(uint32 CoreNumber, double StartTime, double EndTime, CpuCoreEventCallback Callback) const override;`
- L45 _public prototype_ `virtual void EnumerateCpuCoreEventsBackwards(uint32 CoreNumber, double EndTime, double StartTime, CpuCoreEventCallback Callback) const override;`
- L50 _public function_ `virtual void BeginEdit() const override`
- L51 _public function_ `virtual void EndEdit() const override`
- L52 _public function_ `virtual void EditAccessCheck() const override`
- L54 _public prototype_ `void AddTimingEvent(uint32 SystemThreadId, double StartTime, double EndTime, uint32 CoreNumber);`
- L55 _public prototype_ `void AddThreadInfo(uint32 ThreadId, uint32 SystemThreadId);`
- L56 _public prototype_ `void AddThreadName(uint32 SystemThreadId, uint32 SystemProcessId, FStringView Name);`
- L61 _private function_ `uint32 GetNumCpuCoresWithEvents() const`
- L62 _private function_ `uint32 GetExclusiveMaxCpuCoreNumber() const`
- L63 _private prototype_ `const TPagedArray<FContextSwitch>* GetContextSwitches(uint32 ThreadId) const;`
- L66 _private member_ `mutable FProviderLock Lock;`
- L68 _private member_ `IAnalysisSession& Session;`
- L71 _private member_ `TMap<uint32, uint32> TraceToSystemThreadIdMap;` — (Trace) Thread Id -> System Thread Id
- L74 _private member_ `TMap<uint32, uint32> SystemToTraceThreadIdMap;` — System Thread Id -> (Trace) Thread Id
- L77 _private member_ `TMap<uint32, TPagedArray<FContextSwitch>*> Threads;` — System Thread Id -> PagedArray
- L80 _private member_ `TArray<TPagedArray<FCpuCoreEvent>*> CpuCores;` — [Core Number] -> PagedArray; some can be nullptr
- L81 _private member_ `uint32 NumCpuCores;`

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace TraceServices`
- L17 _externvar_ `extern thread_local FProviderLock::FThreadLocalState GContextSwitchesProviderLockState;` (scope `TraceServices`)

### `Source/Developer/TraceServices/Private/Model/CookProfilerProviderPrivate.h` (Private)


#### struct `TraceServices::FPackageScope`  
`struct FPackageScope`  
_L16-32_
- L18 _public function_ `FPackageScope()`
- L21 _public function_ `FPackageScope(uint64 InPackageId, double InTimestamp, EPackageEventStatType InType, bool InIsEnterScope) : PackageId(InPackageId) , Timestamp(InTimestamp) , Type(InType) , bIsEnterScope(InIsEnterScope)`
- L28 _public member_ `uint64 PackageId;`
- L29 _public member_ `double Timestamp;`
- L30 _public member_ `EPackageEventStatType Type;`
- L31 _public member_ `bool bIsEnterScope;`

#### class `TraceServices::FCookProfilerProvider`  
`class FCookProfilerProvider : public ICookProfilerProvider , public IEditableCookProfilerProvider`  
_L34-79_
- inherits: `ICookProfilerProvider,IEditableCookProfilerProvider`
- L39 _public prototype_ `explicit FCookProfilerProvider(IAnalysisSession& Session);`
- L40 _public prototype_ `virtual ~FCookProfilerProvider() = default;`
- L45 _public function_ `virtual void BeginRead() const override`
- L46 _public function_ `virtual void EndRead() const override`
- L47 _public function_ `virtual void ReadAccessCheck() const override`
- L49 _public prototype_ `virtual uint32 GetNumPackages() const;`
- L50 _public prototype_ `virtual void EnumeratePackages(double StartTime, double EndTime, EnumeratePackagesCallback Callback) const override;`
- L51 _public prototype_ `virtual void CreateAggregation(TArray64<FPackageData>& OutPackages) const override;`
- L56 _public function_ `virtual void BeginEdit() const override`
- L57 _public function_ `virtual void EndEdit() const override`
- L58 _public function_ `virtual void EditAccessCheck() const override`
- L60 _public prototype_ `virtual FPackageData* EditPackage(uint64 Id) override;`
- L62 _public prototype_ `virtual void AddScopeEntry(uint32 ThreadId, uint64 InPackageId, double Timestamp, EPackageEventStatType InType, bool InIsEnterScope);`
- L67 _private prototype_ `uint32 FindOrAddPackage(uint64 Id);`
- L68 _private prototype_ `TPagedArray<FPackageScope>& FindOrAddScopeEntries(uint32 ThreadId);`
- L71 _private member_ `mutable FProviderLock Lock;`
- L73 _private member_ `IAnalysisSession& Session;`
- L75 _private member_ `TMap<uint64, uint32> PackageIdToIndexMap;`
- L76 _private member_ `TArray64<FPackageData> Packages;`
- L78 _private member_ `TMap<uint32, TPagedArray<FPackageScope>*> ScopeEntries;` — The Key is the ThreadId of the scope entries.

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace TraceServices`
- L14 _externvar_ `extern thread_local FProviderLock::FThreadLocalState GCookProviderLockState;` (scope `TraceServices`)

### `Source/Developer/TraceServices/Private/Model/CountersPrivate.h` (Private)


#### class `TraceServices::TCounterDataIterator`  
`template<typename ValueType> class TCounterDataIterator`  
_L27-130_
- L30 _public function_ `TCounterDataIterator(const TCounterData<ValueType>& Outer, const TArray64<double>& FrameStartTimes) : FrameStartTimesIterator(FrameStartTimes.CreateConstIterator()) , TimestampsIterator(Outer.Timestamps.GetIterator()) , OpTypesIterator(Outer.OpTypes.GetIterator()) , OpArgumentsIterator(Outer.OpArguments.GetIterator()) , CurrentTime(0.0) , CurrentOp(ECounterOpType::Set) , CurrentOpArgument(ValueType()) , CurrentValue(ValueType())`
- L43 _public function_ `const ValueType operator*() const`
- L48 _public function_ `const double GetCurrentTime() const`
- L53 _public function_ `const ECounterOpType GetCurrentOp() const`
- L58 _public function_ `const ValueType GetCurrentOpArgument() const`
- L63 _public function_ `const ValueType GetCurrentValue() const`
- L68 _public function_ `explicit operator bool() const`
- L73 _public function_ `TCounterDataIterator& operator++()`
- L82 _public function_ `TCounterDataIterator operator++(int)`
- L90 _private function_ `void UpdateValue()`
- L116 _private member_ `TArray64<double>::TConstIterator FrameStartTimesIterator;`
- L118 _private member_ `TVariablePagedArray<double>::TIterator TimestampsIterator;`
- L119 _private member_ `TVariablePagedArray<ECounterOpType>::TIterator OpTypesIterator;`
- L120 _private member_ `typename TVariablePagedArray<ValueType>::TIterator OpArgumentsIterator;`
- L122 _private member_ `TPagedArray<double>::TIterator TimestampsIterator;`
- L123 _private member_ `TPagedArray<ECounterOpType>::TIterator OpTypesIterator;`
- L124 _private member_ `typename TPagedArray<ValueType>::TIterator OpArgumentsIterator;`
- L126 _private member_ `double CurrentTime;`
- L127 _private member_ `ECounterOpType CurrentOp;`
- L128 _private member_ `ValueType CurrentOpArgument;`
- L129 _private member_ `ValueType CurrentValue;`

#### class `TraceServices::TCounterData`  
`template<typename ValueType> class TCounterData`  
_L133-205_
- L136 _public typedef_ `typedef TCounterDataIterator<ValueType> TIterator;`
- L138 _public function_ `TCounterData(ILinearAllocator& Allocator) : Timestamps(Allocator, 1024) , OpTypes(Allocator, 1024) , OpArguments(Allocator, 1024)`
- L146 _public function_ `void InsertOp(double Timestamp, ECounterOpType OpType, ValueType OpArgument)`
- L179 _public function_ `uint64 Num() const`
- L184 _public function_ `TIterator GetIterator(const TArray64<double>& FrameStartTimes) const`
- L189 _public function_ `double GetFirstTimestamp() const`
- L190 _public function_ `double GetLastTimestamp() const`
- L197 _private member_ `TVariablePagedArray<double> Timestamps;`
- L198 _private member_ `TVariablePagedArray<ECounterOpType> OpTypes;`
- L199 _private member_ `TVariablePagedArray<ValueType> OpArguments;`
- L201 _private member_ `TPagedArray<double> Timestamps;`
- L202 _private member_ `TPagedArray<ECounterOpType> OpTypes;`
- L203 _private member_ `TPagedArray<ValueType> OpArguments;`

#### class `TraceServices::FCounter`  
`class FCounter : public ICounter , public IEditableCounter`  
_L207-248_
- inherits: `ICounter,IEditableCounter`
- L212 _public prototype_ `FCounter(ILinearAllocator& Allocator, const TArray64<double>& FrameStartTimes);`
- L215 _public function_ `virtual const TCHAR* GetName() const override` — ICounter
- L216 _public function_ `virtual const TCHAR* GetGroup() const override`
- L217 _public function_ `virtual const TCHAR* GetDescription() const override`
- L218 _public function_ `virtual bool IsFloatingPoint() const override`
- L219 _public function_ `virtual bool IsResetEveryFrame() const override`
- L220 _public function_ `virtual ECounterDisplayHint GetDisplayHint() const`
- L221 _public prototype_ `virtual void EnumerateValues(double IntervalStart, double IntervalEnd, bool bIncludeExternalBounds, TFunctionRef<void(double, int64)> Callback) const override;`
- L222 _public prototype_ `virtual void EnumerateFloatValues(double IntervalStart, double IntervalEnd, bool bIncludeExternalBounds, TFunctionRef<void(double, double)> Callback) const override;`
- L223 _public prototype_ `virtual void EnumerateOps(double IntervalStart, double IntervalEnd, bool bIncludeExternalBounds, TFunctionRef<void(double, ECounterOpType, int64)> Callback) const override;`
- L224 _public prototype_ `virtual void EnumerateFloatOps(double IntervalStart, double IntervalEnd, bool bIncludeExternalBounds, TFunctionRef<void(double, ECounterOpType, double)> Callback) const override;`
- L227 _public function_ `virtual void SetName(const TCHAR* InName) override` — IEditableCounter
- L228 _public function_ `virtual void SetGroup(const TCHAR* InGroup) override`
- L229 _public function_ `virtual void SetDescription(const TCHAR* InDescription) override`
- L230 _public prototype_ `virtual void SetIsFloatingPoint(bool bInIsFloatingPoint) override;`
- L231 _public prototype_ `virtual void SetIsResetEveryFrame(bool bInIsResetEveryFrame) override;`
- L232 _public function_ `virtual void SetDisplayHint(ECounterDisplayHint InDisplayHint) override`
- L233 _public prototype_ `virtual void AddValue(double Time, int64 Value) override;`
- L234 _public prototype_ `virtual void AddValue(double Time, double Value) override;`
- L235 _public prototype_ `virtual void SetValue(double Time, int64 Value) override;`
- L236 _public prototype_ `virtual void SetValue(double Time, double Value) override;`
- L239 _private member_ `const TArray64<double>& FrameStartTimes;`
- L240 _private member_ `TCounterData<int64> IntCounterData;`
- L241 _private member_ `TCounterData<double> DoubleCounterData;`
- L242 _private member_ `const TCHAR* Name = nullptr;`
- L243 _private member_ `const TCHAR* Group = nullptr;`
- L244 _private member_ `const TCHAR* Description = nullptr;`
- L245 _private member_ `ECounterDisplayHint DisplayHint = CounterDisplayHint_None;`
- L246 _private member_ `bool bIsFloatingPoint = false;`
- L247 _private member_ `bool bIsResetEveryFrame = false;`

#### class `TraceServices::FCounterProvider`  
`class FCounterProvider : public ICounterProvider , public IEditableCounterProvider`  
_L250-278_
- inherits: `ICounterProvider,IEditableCounterProvider`
- L255 _public prototype_ `explicit FCounterProvider(IAnalysisSession& Session, IFrameProvider& FrameProvider);`
- L256 _public prototype_ `virtual ~FCounterProvider();`
- L261 _public function_ `virtual uint64 GetCounterCount() const override`
- L262 _public prototype_ `virtual void EnumerateCounters(TFunctionRef<void(uint32, const ICounter&)> Callback) const override;`
- L263 _public prototype_ `virtual bool ReadCounter(uint32 CounterId, TFunctionRef<void(const ICounter&)> Callback) const override;`
- L268 _public prototype_ `virtual const ICounter* GetCounter(IEditableCounter* EditableCounter) override;`
- L269 _public prototype_ `virtual IEditableCounter* CreateEditableCounter() override;`
- L270 _public prototype_ `virtual void AddCounter(const ICounter* Counter) override;`
- L275 _private member_ `IAnalysisSession& Session;`
- L276 _private member_ `IFrameProvider& FrameProvider;`
- L277 _private member_ `TArray<const ICounter*> Counters;`

#### Free symbols / members of external scopes

- L12 _macro_ `#define USE_VARIABLE_PAGED_ARRAY 1` — We need to test data pattern and measure performance for more trace sessions before completely switching to variable paged array.
- L20 _namespace_ `namespace TraceServices`

### `Source/Developer/TraceServices/Private/Model/CsvProfilerProviderPrivate.h` (Private)


#### enum `TraceServices::ECsvStatSeriesType`  
`enum ECsvStatSeriesType`  
_L12-17_
- L14 _public enumerator_ `CsvStatSeriesType_Timer`
- L15 _public enumerator_ `CsvStatSeriesType_CustomStatInt`
- L16 _public enumerator_ `CsvStatSeriesType_CustomStatFloat`

#### class `TraceServices::FCsvProfilerProvider`  
`class FCsvProfilerProvider : public ICsvProfilerProvider`  
_L19-158_
- inherits: `ICsvProfilerProvider`
- L23 _public prototype_ `explicit FCsvProfilerProvider(IAnalysisSession& InSession);`
- L24 _public prototype_ `virtual ~FCsvProfilerProvider();`
- L25 _public function_ `virtual const IUntypedTable& GetTable(uint32 CaptureIndex) const override`
- L26 _public prototype_ `virtual void EnumerateCaptures(TFunctionRef<void(const FCaptureInfo&)> Callback) const override;`
- L27 _public prototype_ `void StartCapture(const TCHAR* Filename, uint32 FrameNumber);`
- L28 _public prototype_ `void EndCapture(uint32 FrameNumber);`
- L29 _public prototype_ `uint64 AddSeries(const TCHAR* Name, ECsvStatSeriesType Type);`
- L30 _public prototype_ `void SetValue(uint64 SeriesHandle, uint32 FrameNumber, double Value);`
- L31 _public prototype_ `void SetValue(uint64 SeriesHandle, uint32 FrameNumber, int64 Value);`
- L32 _public prototype_ `void AddEvent(uint32 FrameNumber, const TCHAR* Text);`
- L33 _public prototype_ `void SetMetadata(const TCHAR* Key, const TCHAR* Value);`
- L150 _private prototype_ `FStatSeriesValue& GetValueRef(uint64 SeriesHandle, uint32 FrameNumber);`
- L152 _private member_ `IAnalysisSession& Session;`
- L153 _private member_ `TArray<FStatSeries*> StatSeries;`
- L154 _private member_ `TMap<uint32, FEvents*> Events;`
- L155 _private member_ `TMap<const TCHAR*, const TCHAR*, FDefaultSetAllocator, TStringPointerMapKeyFuncs_DEPRECATED<const TCHAR*, const TCHAR*>> Metadata;`
- L156 _private member_ `TArray<FCapture*> Captures;`
- L157 _private member_ `FCapture* CurrentCapture = nullptr;`

#### struct `TraceServices::FCsvProfilerProvider::FStatSeriesValue`  
`struct FStatSeriesValue`  
_L36-44_
- L38 _public function_ `FStatSeriesValue()`
- L43 _public member_ `} Value;`

#### union `TraceServices::FCsvProfilerProvider::FStatSeriesValue::(anonymous)`  
``  
_L40-43_

#### struct `TraceServices::FCsvProfilerProvider::FStatSeries`  
`struct FStatSeries`  
_L46-52_
- L48 _public member_ `TMap<uint32, FStatSeriesValue> Values;`
- L49 _public member_ `TSet<uint32> Captures;`
- L50 _public member_ `const TCHAR* Name = nullptr;`
- L51 _public member_ `ECsvStatSeriesType Type;`

#### struct `TraceServices::FCsvProfilerProvider::FEvents`  
`struct FEvents`  
_L54-58_
- L56 _public member_ `TArray<const TCHAR*> Events;`
- L57 _public member_ `const TCHAR* SemiColonSeparatedEvents = nullptr;`

#### class `TraceServices::FCsvProfilerProvider::FTableLayout`  
`class FTableLayout : public ITableLayout`  
_L62-82_
- inherits: `ITableLayout`
- L66 _public function_ `FTableLayout(const TArray<FStatSeries*>& InStatSeries) : StatSeries(InStatSeries)`
- L72 _public prototype_ `virtual uint64 GetColumnCount() const override;`
- L73 _public prototype_ `virtual const TCHAR* GetColumnName(uint64 ColumnIndex) const override;`
- L74 _public prototype_ `virtual ETableColumnType GetColumnType(uint64 ColumnIndex) const override;`
- L75 _public function_ `virtual uint32 GetColumnDisplayHintFlags(uint64 ColumnIndex) const override`
- L81 _private member_ `const TArray<FStatSeries*>& StatSeries;`

#### class `TraceServices::FCsvProfilerProvider::FTableReader`  
`class FTableReader : public IUntypedTableReader`  
_L84-110_
- inherits: `IUntypedTableReader`
- L88 _public function_ `FTableReader(const FCapture& InCapture, const TMap<uint32, FEvents*>& InEvents) : Capture(InCapture) , Events(InEvents) , CurrentRowIndex(0)`
- L95 _public prototype_ `virtual bool IsValid() const override;`
- L96 _public prototype_ `virtual void NextRow() override;`
- L97 _public prototype_ `virtual void SetRowIndex(uint64 RowIndex) override;`
- L98 _public prototype_ `virtual bool GetValueBool(uint64 ColumnIndex) const override;`
- L99 _public prototype_ `virtual int64 GetValueInt(uint64 ColumnIndex) const override;`
- L100 _public prototype_ `virtual float GetValueFloat(uint64 ColumnIndex) const override;`
- L101 _public prototype_ `virtual double GetValueDouble(uint64 ColumnIndex) const override;`
- L102 _public prototype_ `virtual const TCHAR* GetValueCString(uint64 ColumnIndex) const override;`
- L105 _private prototype_ `const FStatSeriesValue* GetValue(uint64 ColumnIndex) const;`
- L107 _private member_ `const FCapture& Capture;`
- L108 _private member_ `const TMap<uint32, FEvents*>& Events;`
- L109 _private member_ `uint32 CurrentRowIndex;`

#### class `TraceServices::FCsvProfilerProvider::FTable`  
`class FTable : public IUntypedTable`  
_L112-132_
- inherits: `IUntypedTable`
- L116 _public function_ `FTable(const FCapture& InCapture, const TMap<uint32, FEvents*>& InEvents) : Layout(InCapture.StatSeries) , Capture(InCapture) , Events(InEvents)`
- L124 _public function_ `virtual const ITableLayout& GetLayout() const override`
- L125 _public prototype_ `virtual uint64 GetRowCount() const override;`
- L126 _public prototype_ `virtual IUntypedTableReader* CreateReader() const override;`
- L129 _private member_ `FTableLayout Layout;`
- L130 _private member_ `const FCapture& Capture;`
- L131 _private member_ `const TMap<uint32, FEvents*>& Events;`

#### struct `TraceServices::FCsvProfilerProvider::FCapture`  
`struct FCapture`  
_L134-148_
- L136 _public function_ `FCapture(const TMap<uint32, FEvents*>& Events) : Table(*this, Events)`
- L142 _public member_ `FTable Table;`
- L143 _public member_ `const TCHAR* Filename;`
- L144 _public member_ `uint32 StartFrame = 0;`
- L145 _public member_ `uint32 EndFrame = 0;`
- L146 _public member_ `TArray<FStatSeries*> StatSeries;`
- L147 _public member_ `TMap<const TCHAR*, const TCHAR*, FDefaultSetAllocator, TStringPointerMapKeyFuncs_DEPRECATED<const TCHAR*, const TCHAR*>> Metadata;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace TraceServices`
- L41 _member_ `int64 AsInt;` (scope `TraceServices::FCsvProfilerProvider::FStatSeriesValue::__anon5f810a62010a`)
- L42 _member_ `double AsDouble;` (scope `TraceServices::FCsvProfilerProvider::FStatSeriesValue::__anon5f810a62010a`)

### `Source/Developer/TraceServices/Private/Model/DbgHelpResolver.h` (Private)


#### class `TraceServices::FDbgHelpResolver`  
`class FDbgHelpResolver : public FRunnable`  
_L23-97_
- inherits: `FRunnable`
- L26 _public typedef_ `typedef TArray<TTuple<uint64, FResolvedSymbol*>> SymbolArray;`
- L28 _public prototype_ `FDbgHelpResolver(IAnalysisSession& InSession, IResolvedSymbolFilter& InSymbolFilter);`
- L29 _public prototype_ `~FDbgHelpResolver();`
- L31 _public prototype_ `void Start();`
- L32 _public prototype_ `void QueueModuleLoad(const uint8* ImageId, uint32 ImageIdSize, FModule* Module);`
- L33 _public prototype_ `void QueueModuleReload(FModule* Module, const TCHAR* Path, TFunction<void(SymbolArray&)> ResolveOnSuccess);`
- L34 _public prototype_ `void QueueSymbolResolve(uint64 Address, FResolvedSymbol* Symbol);`
- L35 _public prototype_ `void OnAnalysisComplete();`
- L36 _public prototype_ `void GetStats(IModuleProvider::FStats* OutStats) const;`
- L37 _public prototype_ `bool HasFinishedResolving() const;`
- L38 _public prototype_ `void EnumerateSymbolSearchPaths(TFunctionRef<void(FStringView Path)> Callback) const;`
- L64 _private prototype_ `bool SetupSyms();`
- L65 _private prototype_ `void FreeSyms() const;`
- L66 _private prototype_ `virtual uint32 Run() override;`
- L67 _private prototype_ `virtual void Stop() override;`
- L68 _private prototype_ `FModuleEntry* GetModuleEntry(FModule* Module) const;`
- L69 _private prototype_ `FModuleEntry* GetModuleForAddress(uint64 Address) const;`
- L70 _private prototype_ `static void UpdateResolvedSymbol(FResolvedSymbol& Symbol, ESymbolQueryResult Result, const TCHAR* Module, const TCHAR* Name, const TCHAR* File, uint16 Line);`
- L71 _private prototype_ `void ResolveSymbol(uint64 Address, FResolvedSymbol& Target);`
- L72 _private prototype_ `void LoadModuleSymbols(FModule* Module, const TCHAR* Path, const TArrayView<const uint8> ImageId);`
- L74 _private member_ `mutable FRWLock ModulesLock;`
- L75 _private member_ `TPagedArray<FModuleEntry> Modules;`
- L76 _private member_ `TArray<FModuleEntry*> SortedModules;`
- L77 _private member_ `TQueue<FQueuedModule, EQueueMode::Mpsc> LoadSymbolsQueue;`
- L78 _private member_ `TQueue<FQueuedAddress, EQueueMode::Mpsc> ResolveQueue;`
- L80 _private member_ `mutable FRWLock CustomSymbolSearchPathsLock;`
- L81 _private member_ `TArray<FString> CustomSymbolSearchPaths;` — search paths added by user from UI in the current session
- L82 _private member_ `TArray<FString> ConfigSymbolSearchPaths;` — search paths specified in environment variables and config files
- L84 _private member_ `std::atomic<uint32> ModulesDiscovered;`
- L85 _private member_ `std::atomic<uint32> ModulesFailed;`
- L86 _private member_ `std::atomic<uint32> ModulesLoaded;`
- L87 _private member_ `std::atomic<uint32> AlreadyResolvedSymbols;`
- L88 _private member_ `std::atomic<uint32> NoModuleSymbols;`
- L90 _private member_ `IAnalysisSession& Session;`
- L91 _private member_ `IResolvedSymbolFilter& SymbolFilter;`
- L93 _private member_ `bool bRunWorkerThread;`
- L94 _private member_ `bool bDrainThenStop;`
- L95 _private member_ `UPTRINT Handle;`
- L96 _private member_ `FRunnableThread* Thread;`

#### struct `TraceServices::FDbgHelpResolver::FModuleEntry`  
`struct FModuleEntry`  
_L41-45_
- L43 _public member_ `FModule* Module;`
- L44 _public member_ `TArray<uint8> ImageId;`

#### struct `TraceServices::FDbgHelpResolver::FQueuedAddress`  
`struct FQueuedAddress`  
_L47-51_
- L49 _public member_ `uint64 Address;`
- L50 _public member_ `FResolvedSymbol* Target;`

#### struct `TraceServices::FDbgHelpResolver::FQueuedModule`  
`struct FQueuedModule`  
_L53-58_
- L55 _public member_ `FModule* Module;`
- L56 _public member_ `const TCHAR* Path;`
- L57 _public member_ `TArrayView<const uint8> ImageId;`

#### enum `TraceServices::FDbgHelpResolver::(anonymous)`  
`enum : uint32`  
_L60-62_

#### Free symbols / members of external scopes

- L19 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogDbgHelp, Log, All);`
- L19 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogDbgHelp, Log, All);`
- L21 _namespace_ `namespace TraceServices`
- L61 _enumerator_ `MaxNameLen = 512` (scope `TraceServices::FDbgHelpResolver::__anon5fd110750103`)

### `Source/Developer/TraceServices/Private/Model/DefinitionProvider.h` (Private)


#### class `TraceServices::FDefinitionProvider`  
`class FDefinitionProvider : public IDefinitionProvider`  
_L15-42_
- inherits: `IDefinitionProvider`
- L18 _public prototype_ `FDefinitionProvider(IAnalysisSession* InSession);`
- L19 _public prototype_ `virtual ~FDefinitionProvider();`
- L21 _public function_ `virtual void BeginRead() const override`
- L22 _public function_ `virtual void EndRead() const override`
- L23 _public function_ `virtual void ReadAccessCheck() const override`
- L25 _public function_ `virtual void BeginEdit() const override`
- L26 _public function_ `virtual void EndEdit() const override`
- L27 _public function_ `virtual void EditAccessCheck() const override`
- L30 _private prototype_ `virtual void AddEntry(uint64 Hash, const void* Ptr) override;`
- L31 _private prototype_ `virtual const void* FindEntry(uint64 Hash) const override;`
- L32 _private prototype_ `virtual void* Allocate(uint32 Size, uint32 Alignment) override;`
- L35 _private member_ `mutable FRWLock Lock;`
- L37 _private member_ `TArray<uint8*> Pages;`
- L38 _private member_ `static constexpr uint32 PageSize = 1024;`
- L39 _private member_ `uint32 PageRemain;`
- L41 _private member_ `TMap<uint64, const void*> Definitions;`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace TraceServices`

### `Source/Developer/TraceServices/Private/Model/DiagnosticsPrivate.h` (Private)


#### class `TraceServices::FDiagnosticsProvider`  
`class FDiagnosticsProvider : public IDiagnosticsProvider`  
_L10-24_
- inherits: `IDiagnosticsProvider`
- L13 _public prototype_ `explicit FDiagnosticsProvider(IAnalysisSession& Session);`
- L14 _public prototype_ `virtual ~FDiagnosticsProvider() = default;`
- L16 _public prototype_ `virtual bool IsSessionInfoAvailable() const override;`
- L17 _public prototype_ `virtual const FSessionInfo& GetSessionInfo() const override;`
- L18 _public prototype_ `void SetSessionInfo(const FSessionInfo& InSessionInfo);`
- L21 _private member_ `IAnalysisSession& Session;`
- L22 _private member_ `FSessionInfo SessionInfo;`
- L23 _private member_ `bool bIsSessionInfoAvailable = false;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace TraceServices`

### `Source/Developer/TraceServices/Private/Model/FileActivity.h` (Private)


#### class `TraceServices::FFileActivityProvider`  
`class FFileActivityProvider : public IFileActivityProvider`  
_L18-56_
- inherits: `IFileActivityProvider`
- L29 _public typedef_ `typedef TIntervalTimeline<FFileActivity*, FTimelineSettings> TimelineInternal;`
- L31 _public prototype_ `explicit FFileActivityProvider(IAnalysisSession& Session);`
- L32 _public prototype_ `virtual ~FFileActivityProvider() = default;`
- L34 _public prototype_ `virtual void EnumerateFileActivity(TFunctionRef<bool(const FFileInfo&, const Timeline&)> Callback) const override;`
- L35 _public prototype_ `virtual const ITable<FFileActivity>& GetFileActivityTable() const override;`
- L36 _public prototype_ `uint32 GetFileIndex(const TCHAR* Path);`
- L37 _public prototype_ `uint32 GetUnknownFileIndex();`
- L38 _public prototype_ `uint64 BeginActivity(uint32 FileIndex, EFileActivityType Type, uint32 ThreadId, uint64 Offset, uint64 Size, double Time);`
- L39 _public prototype_ `void EndActivity(uint32 FileIndex, uint64 ActivityIndex, uint64 ActualSize, double Time, bool Failed);`
- L40 _public prototype_ `void SetActivityFileHandle(uint32 FileIndex, uint64 ActivityIndex, uint64 FileHandle);`
- L41 _public prototype_ `void SetActivityReadWriteHandle(uint32 FileIndex, uint64 ActivityIndex, uint64 ReadWriteHandle);`
- L42 _public prototype_ `void CheckActivityReadWriteHandle(uint32 FileIndex, uint64 ActivityIndex, uint64 ReadWriteHandle);`
- L43 _public prototype_ `const TCHAR* GetFilePath(uint32 FileIndex) const;`
- L52 _private member_ `IAnalysisSession& Session;`
- L53 _private member_ `TPagedArray<FFileInfoInternal> Files;`
- L54 _private member_ `TPagedArray<FFileActivity> FileActivities;`
- L55 _private member_ `TTableView<FFileActivity> FileActivityTable;`

#### struct `TraceServices::FFileActivityProvider::FTimelineSettings`  
`struct FTimelineSettings`  
_L22-28_

#### enum `TraceServices::FFileActivityProvider::FTimelineSettings::(anonymous)`  
``  
_L25-27_

#### struct `TraceServices::FFileActivityProvider::FFileInfoInternal`  
`struct FFileInfoInternal`  
_L46-50_
- L48 _public member_ `FFileInfo FileInfo;`
- L49 _public member_ `TSharedPtr<TimelineInternal> ActivityTimeline;`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace TraceServices`
- L26 _enumerator_ `EventsPerPage = 128` (scope `TraceServices::FFileActivityProvider::FTimelineSettings::__anon66e38e1a0103`)

### `Source/Developer/TraceServices/Private/Model/FramesPrivate.h` (Private)


#### class `TraceServices::FFrameProvider`  
`class FFrameProvider : public IFrameProvider`  
_L14-44_
- inherits: `IFrameProvider`
- L18 _public prototype_ `explicit FFrameProvider(IAnalysisSession& Session);`
- L19 _public prototype_ `virtual ~FFrameProvider() = default;`
- L24 _public prototype_ `virtual uint64 GetFrameCount(ETraceFrameType FrameType) const override;`
- L25 _public prototype_ `virtual void EnumerateFrames(ETraceFrameType FrameType, uint64 StartIndex, uint64 EndIndex, TFunctionRef<void(const FFrame&)> Callback) const override;`
- L26 _public prototype_ `virtual void EnumerateFrames(ETraceFrameType FrameType, double StartTime, double EndTime, TFunctionRef<void(const FFrame&)> Callback) const override;`
- L27 _public function_ `virtual const TArray64<double>& GetFrameStartTimes(ETraceFrameType FrameType) const override`
- L28 _public prototype_ `virtual bool GetFrameFromTime(ETraceFrameType FrameType, double Time, FFrame& OutFrame) const override;`
- L29 _public prototype_ `virtual const FFrame* GetFrame(ETraceFrameType FrameType, uint64 Index) const override;`
- L30 _public prototype_ `virtual uint32 GetFrameNumberForTimestamp(ETraceFrameType FrameType, double Time) const override;`
- L35 _public prototype_ `void BeginFrame(ETraceFrameType FrameType, double Time);`
- L36 _public prototype_ `void EndFrame(ETraceFrameType FrameType, double Time);`
- L41 _private member_ `IAnalysisSession& Session;`
- L42 _private member_ `TArray<TPagedArray<FFrame>> Frames;`
- L43 _private member_ `TArray64<double> FrameStartTimes[TraceFrameType_Count];`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace TraceServices`

### `Source/Developer/TraceServices/Private/Model/LoadTimeProfilerPrivate.h` (Private)


#### class `TraceServices::FLoadTimeProfilerProvider`  
`class FLoadTimeProfilerProvider : public ILoadTimeProfilerProvider`  
_L18-123_
- inherits: `ILoadTimeProfilerProvider`
- L22 _public typedef_ `typedef TMonotonicTimeline<FLoadTimeProfilerCpuEvent> CpuTimelineInternal;`
- L24 _public prototype_ `explicit FLoadTimeProfilerProvider(IAnalysisSession& Session, IEditableCounterProvider& EditableCounterProvider);`
- L25 _public prototype_ `virtual ~FLoadTimeProfilerProvider() = default;`
- L27 _public function_ `virtual uint32 GetTimelineCount() const override`
- L28 _public prototype_ `virtual bool GetCpuThreadTimelineIndex(uint32 ThreadId, uint32& OutTimelineIndex) const override;`
- L29 _public prototype_ `virtual bool ReadTimeline(uint32 Index, TFunctionRef<void(const CpuTimeline&)> Callback) const override;`
- L30 _public prototype_ `virtual ITable<FLoadTimeProfilerAggregatedStats>* CreateEventAggregation(double IntervalStart, double IntervalEnd) const override;`
- L31 _public prototype_ `virtual ITable<FLoadTimeProfilerAggregatedStats>* CreateObjectTypeAggregation(double IntervalStart, double IntervalEnd) const override;`
- L32 _public prototype_ `virtual ITable<FPackagesTableRow>* CreatePackageDetailsTable(double IntervalStart, double IntervalEnd) const override;`
- L33 _public prototype_ `virtual ITable<FExportsTableRow>* CreateExportDetailsTable(double IntervalStart, double IntervalEnd) const override;`
- L34 _public prototype_ `virtual ITable<FRequestsTableRow>* CreateRequestsTable(double IntervalStart, double IntervalEnd) const override;`
- L35 _public function_ `virtual const ITable<FLoadRequest>& GetRequestsTable() const override`
- L36 _public prototype_ `const FClassInfo& AddClassInfo(const TCHAR* ClassName);`
- L37 _public prototype_ `FLoadRequest& CreateRequest();`
- L38 _public prototype_ `FPackageInfo& CreatePackage();`
- L39 _public prototype_ `FPackageExportInfo& CreateExport();`
- L40 _public prototype_ `CpuTimelineInternal& EditCpuTimeline(uint32 ThreadId);`
- L41 _public prototype_ `uint64 BeginIoDispatcherBatch(uint64 BatchId, double Time);`
- L42 _public prototype_ `void EndIoDispatcherBatch(uint64 BatchHandle, double Time, uint64 TotalSize);`
- L47 _private prototype_ `static uint64 PackageSizeSum(const FLoadRequest& Row);`
- L48 _private prototype_ `void CreateCounters();`
- L49 _private prototype_ `void DistributeBytesAcrossFrames(uint64 ByteCount, double StartTime, double EndTime, uint64 FLoaderFrame::* FrameVariable);`
- L51 _private member_ `static constexpr double LoaderFrameLength = 1.0 / 60.0;`
- L103 _private member_ `IAnalysisSession& Session;`
- L104 _private member_ `IEditableCounterProvider& EditableCounterProvider;`
- L105 _private member_ `TPagedArray<FClassInfo> ClassInfos;`
- L106 _private member_ `TPagedArray<FLoadRequest> Requests;`
- L107 _private member_ `TPagedArray<FPackageInfo> Packages;`
- L108 _private member_ `TPagedArray<FIoDispatcherBatch> IoDispatcherBatches;`
- L109 _private member_ `TPagedArray<FPackageExportInfo> Exports;`
- L110 _private member_ `TArray<TSharedRef<CpuTimelineInternal>> CpuTimelines;`
- L111 _private member_ `TMap<uint32, uint32> CpuTimelinesThreadMap;`
- L112 _private member_ `TTableView<FLoadRequest> RequestsTable;`
- L113 _private member_ `TTableLayout<FLoadTimeProfilerAggregatedStats> AggregatedStatsTableLayout;`
- L114 _private member_ `TTableLayout<FPackagesTableRow> PackagesTableLayout;`
- L115 _private member_ `TTableLayout<FExportsTableRow> ExportsTableLayout;`
- L116 _private member_ `TTableLayout<FRequestsTableRow> RequestsTableLayout;`
- L117 _private member_ `TPagedArray<FLoaderFrame> Frames;`
- L118 _private member_ `bool bHasCreatedCounters = false;`
- L119 _private member_ `IEditableCounter* ActiveIoDispatcherBatchesCounter = nullptr;`
- L120 _private member_ `IEditableCounter* TotalIoDispatcherBytesReadCounter = nullptr;`
- L121 _private member_ `IEditableCounter* LoadingPackagesCounter = nullptr;`
- L122 _private member_ `IEditableCounter* TotalLoaderBytesLoadedCounter = nullptr;`

#### struct `TraceServices::FLoadTimeProfilerProvider::FPackageLoad`  
`struct FPackageLoad`  
_L53-58_
- L55 _public member_ `const FPackageInfo* Package = nullptr;`
- L56 _public member_ `double StartTime = 0.0;`
- L57 _public member_ `double EndTime = 0.0;`

#### struct `TraceServices::FLoadTimeProfilerProvider::FIoDispatcherBatch`  
`struct FIoDispatcherBatch`  
_L60-65_
- L62 _public member_ `double StartTime = 0.0;`
- L63 _public member_ `double EndTime = 0.0;`
- L64 _public member_ `uint64 TotalSize = 0;`

#### struct `TraceServices::FLoadTimeProfilerProvider::FLoaderFrame`  
`struct FLoaderFrame`  
_L67-72_
- L69 _public member_ `uint64 IoDispatcherReadBytes = 0;`
- L70 _public member_ `uint64 HeaderLoadedBytes = 0;`
- L71 _public member_ `uint64 ExportLoadedBytes = 0;`

#### class `TraceServices::FLoadTimeProfilerProvider::FLoaderFrameCounter`  
`class FLoaderFrameCounter : public ICounter`  
_L74-101_
- inherits: `ICounter`
- L85 _public prototype_ `FLoaderFrameCounter(ELoaderFrameCounterType Type, const TPagedArray<FLoaderFrame>& Frames);`
- L86 _public prototype_ `virtual ~FLoaderFrameCounter() = default;`
- L88 _public prototype_ `virtual const TCHAR* GetName() const override;`
- L89 _public prototype_ `virtual const TCHAR* GetGroup() const override;`
- L90 _public prototype_ `virtual const TCHAR* GetDescription() const override;`
- L91 _public prototype_ `virtual bool IsFloatingPoint() const override;`
- L92 _public prototype_ `virtual ECounterDisplayHint GetDisplayHint() const override;`
- L93 _public prototype_ `virtual void EnumerateValues(double IntervalStart, double IntervalEnd, bool bIncludeExternalBounds, TFunctionRef<void(double, int64)> Callback) const override;`
- L94 _public prototype_ `virtual void EnumerateFloatValues(double IntervalStart, double IntervalEnd, bool bIncludeExternalBounds, TFunctionRef<void(double, double)> Callback) const override;`
- L95 _public prototype_ `virtual void EnumerateOps(double IntervalStart, double IntervalEnd, bool bIncludeExternalBounds, TFunctionRef<void(double, ECounterOpType, int64)> Callback) const override;`
- L96 _public prototype_ `virtual void EnumerateFloatOps(double IntervalStart, double IntervalEnd, bool bIncludeExternalBounds, TFunctionRef<void(double, ECounterOpType, double)> Callback) const override;`
- L99 _private member_ `const TPagedArray<FLoaderFrame>& Frames;`
- L100 _private member_ `ELoaderFrameCounterType Type;`

#### enum `TraceServices::FLoadTimeProfilerProvider::FLoaderFrameCounter::ELoaderFrameCounterType`  
`enum ELoaderFrameCounterType`  
_L78-83_
- L80 _public enumerator_ `LoaderFrameCounterType_IoDispatcherThroughput`
- L81 _public enumerator_ `LoaderFrameCounterType_LoaderThroughput`
- L82 _public enumerator_ `LoaderFrameCounterType_Count`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace TraceServices`

### `Source/Developer/TraceServices/Private/Model/LogPrivate.h` (Private)


#### struct `TraceServices::FLogMessageSpec`  
`struct FLogMessageSpec`  
_L21-28_
- L23 _public member_ `FLogCategoryInfo* Category = nullptr;`
- L24 _public member_ `const TCHAR* File = nullptr;`
- L25 _public member_ `const TCHAR* FormatString = nullptr;`
- L26 _public member_ `int32 Line;`
- L27 _public member_ `ELogVerbosity::Type Verbosity;`

#### struct `TraceServices::FLogMessageInternal`  
`struct FLogMessageInternal`  
_L30-35_
- L32 _public member_ `FLogMessageSpec* Spec = nullptr;`
- L33 _public member_ `double Time;`
- L34 _public member_ `const TCHAR* Message = nullptr;`

#### class `TraceServices::FLogProvider`  
`class FLogProvider : public ILogProvider , public IEditableLogProvider`  
_L37-119_
- inherits: `ILogProvider,IEditableLogProvider`
- L42 _public prototype_ `explicit FLogProvider(IAnalysisSession& Session);`
- L43 _public prototype_ `virtual ~FLogProvider();`
- L48 _public function_ `virtual uint64 GetMessageCount() const override`
- L49 _public prototype_ `virtual bool ReadMessage(uint64 Index, TFunctionRef<void(const FLogMessageInfo&)> Callback) const override;`
- L50 _public prototype_ `virtual void EnumerateMessagesByIndex(uint64 StartIndex, uint64 EndIndex, TFunctionRef<void(const FLogMessageInfo&)> Callback) const override;`
- L51 _public prototype_ `virtual void EnumerateMessages(double StartTime, double EndTime, TFunctionRef<void(const FLogMessageInfo&)> Callback) const override;`
- L52 _public prototype_ `virtual void ReverseEnumerateMessages(double StartTime, double EndTime, TFunctionRef<bool(const FLogMessageInfo&)> Callback) const override;`
- L54 _public prototype_ `virtual uint64 LowerBoundByTime(double Time) const override;`
- L55 _public prototype_ `virtual uint64 UpperBoundByTime(double Time) const override;`
- L56 _public prototype_ `virtual uint64 BinarySearchClosestByTime(double Time) const override;`
- L58 _public function_ `virtual uint64 GetMessageSpecCount() const override`
- L60 _public function_ `virtual uint64 GetCategoryCount() const override`
- L61 _public prototype_ `virtual void EnumerateCategories(TFunctionRef<void(const FLogCategoryInfo&)> Callback) const override;`
- L63 _public function_ `virtual const IUntypedTable& GetMessagesTable() const override`
- L65 _public function_ `virtual uint64 GetInsertCount() const override`
- L66 _public function_ `virtual uint64 GetUnknownSpecTotalCount() const override`
- L67 _public function_ `virtual uint64 GetUnresolvedSpecCount() const override`
- L72 _public prototype_ `virtual uint64 RegisterCategory() override;`
- L73 _public prototype_ `virtual FLogCategoryInfo& GetCategory(uint64 CategoryPointer) override;`
- L75 _public prototype_ `FLogMessageSpec& GetMessageSpec(uint64 LogPoint);`
- L76 _public prototype_ `virtual void UpdateMessageCategory(uint64 LogPoint, uint64 InCategoryPointer) override;`
- L77 _public prototype_ `virtual void UpdateMessageFormatString(uint64 LogPoint, const TCHAR* InFormatString) override;`
- L78 _public prototype_ `virtual void UpdateMessageFile(uint64 LogPoint, const TCHAR* InFile, int32 InLine) override;`
- L79 _public prototype_ `virtual void UpdateMessageVerbosity(uint64 LogPoint, ELogVerbosity::Type InVerbosity) override;`
- L80 _public prototype_ `virtual void UpdateMessageSpec(uint64 LogPoint, uint64 InCategoryPointer, const TCHAR* InFormatString, const TCHAR* InFile, int32 InLine, ELogVerbosity::Type InVerbosity) override;`
- L81 _public prototype_ `virtual void UpdateMessageSpec(uint64 LogPoint) override;`
- L83 _public prototype_ `virtual void AppendMessage(uint64 LogPoint, double Time, const uint8* FormatArgs) override;`
- L84 _public prototype_ `virtual void AppendMessage(uint64 LogPoint, double Time, TArrayView<const uint8> FormatArgsView) override;`
- L85 _public prototype_ `virtual void AppendMessage(uint64 LogPoint, double Time, const TCHAR* StoredText) override;`
- L86 _public prototype_ `void AppendMessage(uint64 LogPoint, double Time, const FStringView Message);`
- L91 _private prototype_ `FLogMessageInternal& AppendMessageInternal(double Time, uint64* OutIndex = nullptr);`
- L92 _private prototype_ `void AppendUnknownMessageInternal(uint64 LogPoint, double Time, const FStringView Message);`
- L93 _private prototype_ `bool ConstructMessage(const FLogMessageInternal& InternalMessage, uint64 Index, TFunctionRef<void(const FLogMessageInfo&)> Callback) const;`
- L94 _private prototype_ `bool ConstructMessage(const FLogMessageInternal& InternalMessage, uint64 Index, TFunctionRef<bool(const FLogMessageInfo&)> Callback) const;`
- L107 _private member_ `IAnalysisSession& Session;`
- L108 _private member_ `TMap<uint64, FLogCategoryInfo*> CategoryMap;` — CategoryPointer --> FLogCategoryInfo*
- L109 _private member_ `TMap<uint64, FLogMessageSpec*> SpecMap;` — LogPoint --> FLogMessageSpec*
- L110 _private member_ `TPagedArray<FLogCategoryInfo> Categories;`
- L111 _private member_ `TPagedArray<FLogMessageSpec> MessageSpecs;`
- L112 _private member_ `TPagedArray<FLogMessageInternal> Messages;`
- L113 _private member_ `TCHAR FormatBuffer[FormatBufferSize];`
- L114 _private member_ `TCHAR TempBuffer[FormatBufferSize];`
- L115 _private member_ `TTableView<FLogMessageInternal> MessagesTable;`
- L116 _private member_ `TMultiMap<uint64, FMissingMessage> MissingLogPoints;` — LogPoint --> FMissingMessage[]
- L117 _private member_ `uint64 NumInserts = 0;` — total number of inserts (out of order messages)
- L118 _private member_ `uint64 NumUnknownSpecs = 0;` — total number of log messages received with unknown spec

#### enum `TraceServices::FLogProvider::(anonymous)`  
``  
_L97-99_

#### struct `TraceServices::FLogProvider::FMissingMessage`  
`struct FMissingMessage`  
_L101-105_
- desc: message with missing spec
- L103 _public member_ `uint64 Index = ~0ull;` — index in Messages array
- L104 _public member_ `uint8* FormatArgs = nullptr;`

#### Free symbols / members of external scopes

- L15 _namespace_ `namespace TraceServices`
- L98 _enumerator_ `FormatBufferSize = 65536` (scope `TraceServices::FLogProvider::__anon341ca1ca0103`)

### `Source/Developer/TraceServices/Private/Model/MemoryPrivate.h` (Private)


#### class `TraceServices::FMemoryProvider`  
`class FMemoryProvider : public IMemoryProvider, public IEditableProvider`  
_L16-145_
- inherits: `IMemoryProvider,IEditableProvider`
- L19 _public prototype_ `explicit FMemoryProvider(IAnalysisSession& Session);`
- L20 _public prototype_ `virtual ~FMemoryProvider();`
- L25 _public function_ `virtual void BeginRead() const override`
- L26 _public function_ `virtual void EndRead() const override`
- L27 _public function_ `virtual void ReadAccessCheck() const override`
- L29 _public function_ `virtual bool IsInitialized() const override`
- L30 _public function_ `virtual bool IsCompleted() const override`
- L32 _public prototype_ `virtual uint32 GetTagSerial() const override;`
- L33 _public prototype_ `virtual uint32 GetTagCount() const override;`
- L34 _public prototype_ `virtual const FMemoryTagInfo* GetTag(FMemoryTagId Id) const override;`
- L36 _public prototype_ `virtual void EnumerateTags(TFunctionRef<void(const FMemoryTagInfo&)> Callback) const override;`
- L37 _public prototype_ `virtual void EnumerateTags(FMemoryTagSetId TagSetId, TFunctionRef<void(const FMemoryTagInfo&)> Callback) const override;`
- L39 _public prototype_ `virtual uint32 GetTrackerCount() const override;`
- L40 _public prototype_ `virtual void EnumerateTrackers(TFunctionRef<void(const FMemoryTrackerInfo&)> Callback) const override;`
- L42 _public prototype_ `virtual uint32 GetTagSetCount() const override;`
- L43 _public prototype_ `virtual void EnumerateTagSets(TFunctionRef<void(const FMemoryTagSetInfo&)> Callback) const override;`
- L45 _public prototype_ `virtual uint64 GetTagSampleCount(FMemoryTrackerId Tracker, FMemoryTagId Tag) const override;`
- L46 _public prototype_ `virtual void EnumerateTagSamples( FMemoryTrackerId Tracker, FMemoryTagId Tag, double StartTime, double EnddTime, bool bIncludeRangeNeighbours, TFunctionRef<void(double Time, double Duration, const FMemoryTagSample&)> Callback) const override;`
- L57 _public function_ `virtual void BeginEdit() const override`
- L58 _public function_ `virtual void EndEdit() const override`
- L59 _public function_ `virtual void EditAccessCheck() const override`
- L61 _public prototype_ `void AddTrackerSpec(FMemoryTrackerId TrackerId, const FString& Name);`
- L62 _public prototype_ `void AddTagSetSpec(FMemoryTagSetId TagSetId, const FString& Name);`
- L63 _public prototype_ `void AddTagSpec(FMemoryTagId Tag, const FString& Name, FMemoryTagId ParentTag, FMemoryTagSetId TagSet);`
- L65 _public prototype_ `void AddTagSnapshot(FMemoryTrackerId TrackerId, double Time, const int64* Tags, const FMemoryTagSample* Values, uint32 TagCount);`
- L67 _public prototype_ `void OnAnalysisCompleted();`
- L116 _private prototype_ `void InternalAddTrackerSpec(FMemoryTrackerId TrackerId, const FString& Name);`
- L117 _private prototype_ `void InternalAddTagSetSpec(FMemoryTagSetId TagSetId, const FString& Name);`
- L118 _private prototype_ `void InternalAddTagSpec(FMemoryTagId Tag, const FString& Name, FMemoryTagId ParentTag, FMemoryTagSetId TagSet);`
- L119 _private prototype_ `FTrackerData* GetTracker(FMemoryTrackerId TrackerId) const;`
- L120 _private prototype_ `FTrackerData* GetOrAddTracker(FMemoryTrackerId TrackerId);`
- L121 _private prototype_ `FTagSetData* GetTagSet(FMemoryTagSetId TagSetId) const;`
- L122 _private prototype_ `FTagSetData* GetOrAddTagSet(FMemoryTagSetId TagSetId);`
- L125 _private member_ `mutable FProviderLock Lock;`
- L127 _private member_ `IAnalysisSession& Session;`
- L129 _private member_ `TArray<FTrackerData*> AvailableTrackers;`
- L130 _private member_ `uint32 NumTrackers = 0;`
- L132 _private member_ `TArray<FTagSetData*> AvailableTagSets;`
- L133 _private member_ `uint32 NumTagSets = 0;`
- L135 _private member_ `TArray<FMemoryTagInfo*> AvailableTags;`
- L136 _private member_ `TMap<FMemoryTagId, FMemoryTagInfo*> TagMap;` — tag id --> TagInfo
- L139 _private member_ `TPagedArray<double> SnapshotTimes;` — Timestamps for samples
- L141 _private member_ `uint32 TagsSerial = 0;`
- L143 _private member_ `std::atomic<bool> bIsInitialized = false;`
- L144 _private member_ `std::atomic<bool> bIsCompleted = false;`

#### struct `TraceServices::FMemoryProvider::FTagSampleData`  
`struct FTagSampleData`  
_L72-85_
- L75 _public member_ `TPagedArray<FMemoryTagSample> Values;` — Sample values.
- L77 _public member_ `FMemoryTagInfo* TagInfo = nullptr;`
- L79 _public function_ `FTagSampleData(ILinearAllocator& Allocator) : Values(Allocator, 65536)`
- L82 _public function_ `FTagSampleData(const FTagSampleData& Other) : Values(Other.Values)`

#### struct `TraceServices::FMemoryProvider::FTrackerData`  
`struct FTrackerData`  
_L87-99_
- L90 _public member_ `FMemoryTrackerInfo* Info = nullptr;` — The memory tracker.
- L93 _public member_ `TMap<FMemoryTagId, FTagSampleData*> Samples;` — All tags and samples for this tracker.
- L95 _public function_ `FTrackerData(FMemoryTrackerInfo* InInfo) : Info(InInfo)`
- L98 _private prototype_ `FTrackerData(const FTrackerData&) = delete;`

#### struct `TraceServices::FMemoryProvider::FTagSetData`  
`struct FTagSetData`  
_L101-113_
- L104 _public member_ `FMemoryTagSetInfo* Info = nullptr;` — The memory tag set.
- L107 _public member_ `TMap<FMemoryTagId, FMemoryTagInfo*> Tags;` — All tags for this tag set.
- L109 _public function_ `FTagSetData(FMemoryTagSetInfo* InInfo) : Info(InInfo)`
- L112 _private prototype_ `FTagSetData(const FTagSetData&) = delete;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace TraceServices`
- L14 _externvar_ `extern thread_local FProviderLock::FThreadLocalState GMemoryProviderLockState;` (scope `TraceServices`)

### `Source/Developer/TraceServices/Private/Model/MetadataProvider.h` (Private)


#### class `TraceServices::FMetadataProviderLock`  
`class FMetadataProviderLock`  
_L19-33_
- L22 _public prototype_ `void ReadAccessCheck() const;`
- L23 _public prototype_ `void WriteAccessCheck() const;`
- L25 _public prototype_ `void BeginRead();`
- L26 _public prototype_ `void EndRead();`
- L28 _public prototype_ `void BeginWrite();`
- L29 _public prototype_ `void EndWrite();`
- L32 _private member_ `FRWLock RWLock;`

#### class `TraceServices::FMetadataProvider`  
`class FMetadataProvider : public IMetadataProvider , public IEditableMetadataProvider`  
_L37-175_
- inherits: `IMetadataProvider,IEditableMetadataProvider`
- L42 _public member_ `static constexpr uint32 MaxMetadataSize = 0xFFFF;`
- L43 _public member_ `static constexpr uint32 MaxLogMessagesPerErrorType = 100;`
- L46 _private member_ `static constexpr uint32 MaxInlinedMetadataSize = 12;`
- L47 _private member_ `static constexpr uint32 MaxMetadataTypeId = 0xFFFF;`
- L48 _private member_ `static constexpr int32 MaxMetadataStackSize = 0xFFFF;`
- L49 _private member_ `static constexpr uint32 InvalidMetadataStoreIndex = 0xFFFFFFFF;`
- L97 _public prototype_ `explicit FMetadataProvider(IAnalysisSession& InSession);`
- L98 _public prototype_ `virtual ~FMetadataProvider();`
- L103 _public function_ `virtual void BeginRead() const override`
- L104 _public function_ `virtual void EndRead() const override`
- L105 _public function_ `virtual void ReadAccessCheck() const override`
- L107 _public prototype_ `virtual uint16 GetRegisteredMetadataType(FName InName) const override;`
- L108 _public prototype_ `virtual FName GetRegisteredMetadataName(uint16 InType) const override;`
- L109 _public prototype_ `virtual const FMetadataSchema* GetRegisteredMetadataSchema(uint16) const override;`
- L111 _public prototype_ `virtual uint32 GetMetadataStackSize(uint32 InThreadId, uint32 InMetadataId) const override;`
- L112 _public prototype_ `virtual bool GetMetadata(uint32 InThreadId, uint32 InMetadataId, uint32 InStackDepth, uint16& OutType, const void*& OutData, uint32& OutSize) const override;`
- L113 _public prototype_ `virtual void EnumerateMetadata(uint32 InThreadId, uint32 InMetadataId, TFunctionRef<bool(uint32 StackDepth, uint16 Type, const void* Data, uint32 Size)> Callback) const override;`
- L118 _public function_ `virtual void BeginEdit() const override`
- L119 _public function_ `virtual void EndEdit() const override`
- L120 _public function_ `virtual void EditAccessCheck() const override`
- L122 _public prototype_ `virtual uint16 RegisterMetadataType(const TCHAR* InName, const FMetadataSchema& InSchema) override;`
- L124 _public prototype_ `virtual void PushScopedMetadata(uint32 InThreadId, uint16 InType, const void* InData, uint32 InSize) override;`
- L125 _public prototype_ `virtual void PopScopedMetadata(uint32 InThreadId, uint16 InType) override;`
- L127 _public prototype_ `virtual void BeginClearStackScope(uint32 InThreadId) override;`
- L128 _public prototype_ `virtual void EndClearStackScope(uint32 InThreadId) override;`
- L130 _public prototype_ `virtual void SaveStack(uint32 InThreadId, uint32 InSavedStackId) override;`
- L131 _public prototype_ `virtual void BeginRestoreSavedStackScope(uint32 InThreadId, uint32 InSavedStackId) override;`
- L132 _public prototype_ `virtual void EndRestoreSavedStackScope(uint32 InThreadId) override;`
- L135 _public prototype_ `virtual uint32 PinAndGetId(uint32 InThreadId) override;` — Pins the metadata stack and returns an id for it.
- L137 _public prototype_ `virtual void OnAnalysisCompleted() override;`
- L142 _private prototype_ `FMetadataThread& GetOrAddThread(uint32 InThreadId);`
- L143 _private prototype_ `FMetadataThread* GetThread(uint32 InThreadId);`
- L144 _private prototype_ `const FMetadataThread* GetThread(uint32 InThreadId) const;`
- L145 _private prototype_ `void InternalAllocStoreEntry(FMetadataStoreEntry& InStoreEntry, uint16 InType, const void* InData, uint32 InSize);`
- L146 _private prototype_ `void InternalFreeStoreEntry(const FMetadataStoreEntry& InStoreEntry);`
- L147 _private prototype_ `void InternalPushStackEntry(FMetadataThread& InMetadataThread, uint16 InType, const void* InData, uint32 InSize);`
- L148 _private prototype_ `void InternalPopStackEntry(FMetadataThread& InMetadataThread);`
- L149 _private prototype_ `void InternalClearStack(FMetadataThread& InMetadataThread);`
- L150 _private prototype_ `void InternalPushSavedStack(FMetadataThread& InMetadataThread, FMetadataThread& InSavedMetadataThread, uint32 InSavedMetadataId);`
- L153 _private member_ `mutable FProviderLock Lock;`
- L155 _private member_ `IAnalysisSession& Session;`
- L157 _private member_ `TPagedArray<FMetadataSchema> RegisteredTypes;`
- L158 _private member_ `TMap<FName, uint16> RegisteredTypesMap;`
- L160 _private member_ `TPagedArray<FMetadataStoreEntry> MetadataStore;` — stores individual metadata values
- L162 _private member_ `TMap<uint32, FMetadataThread*> Threads;`
- L164 _private member_ `TMap<uint32, FMetadataSavedStackInfo> SavedStackMap;` — SavedStackId --> (ThreadId, MetadataId)
- L166 _private member_ `uint32 MetaScopeErrors = 0;` — debug
- L167 _private member_ `uint32 ClearScopeErrors = 0;` — debug
- L168 _private member_ `uint32 RestoreScopeErrors = 0;` — debug
- L169 _private member_ `uint32 PushSavedStackErrors = 0;` — debug
- L171 _private member_ `uint64 EventCount = 0;` — debug
- L172 _private member_ `uint64 AllocationEventCount = 0;` — debug
- L173 _private member_ `uint64 AllocationCount = 0;` — debug
- L174 _private member_ `uint64 TotalAllocatedMemory = 0;` — debug

#### struct `TraceServices::FMetadataProvider::FMetadataStoreEntry`  
`struct FMetadataStoreEntry`  
_L51-61_
- L58 _public member_ `uint8 ValueEx[4];`
- L59 _public member_ `uint16 Size;`
- L60 _public member_ `uint16 Type;`

#### union `TraceServices::FMetadataProvider::FMetadataStoreEntry::(anonymous)`  
``  
_L54-57_

#### struct `TraceServices::FMetadataProvider::FMetadataStackEntry`  
`struct FMetadataStackEntry`  
_L64-69_
- L66 _public member_ `FMetadataStoreEntry StoreEntry;`
- L67 _public member_ `uint32 StoreIndex;`
- L68 _public member_ `uint32 PinnedId;`

#### struct `TraceServices::FMetadataProvider::FMetadataEntry`  
`struct FMetadataEntry`  
_L72-77_
- L74 _public member_ `uint32 StoreIndex;`
- L75 _public member_ `uint16 Type;`
- L76 _public member_ `uint16 StackSize;`

#### struct `TraceServices::FMetadataProvider::FMetadataThread`  
`struct FMetadataThread`  
_L80-88_
- L82 _public prototype_ `FMetadataThread(uint32 InThreadId, ILinearAllocator&);`
- L84 _public member_ `uint32 ThreadId;`
- L85 _public member_ `TArray<FMetadataStackEntry> CurrentStack;`
- L86 _public member_ `TPagedArray<FMetadataEntry> Metadata;` — a metadata id is an index in this array
- L87 _public member_ `TArray<uint32> SavedMetadataStack;` — stack of MetadataId values for each saved Clear or Restore scope

#### struct `TraceServices::FMetadataProvider::FMetadataSavedStackInfo`  
`struct FMetadataSavedStackInfo`  
_L90-94_
- L92 _public member_ `uint32 ThreadId;`
- L93 _public member_ `uint32 MetadataId;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace TraceServices`
- L15 _externvar_ `extern thread_local FProviderLock::FThreadLocalState GMetadataProviderLockState;` (scope `TraceServices`)
- L55 _member_ `void* Ptr;` (scope `TraceServices::FMetadataProvider::FMetadataStoreEntry::__anon0bdbe619010a`)
- L56 _member_ `uint8 Value[8];` (scope `TraceServices::FMetadataProvider::FMetadataStoreEntry::__anon0bdbe619010a`)

### `Source/Developer/TraceServices/Private/Model/ModuleProvider.h` (Private)


#### class `TraceServices::IModuleAnalysisProvider`  
`class IModuleAnalysisProvider : public IModuleProvider`  
_L13-19_
- inherits: `IModuleProvider`
- L16 _public prototype_ `virtual void OnModuleLoad(const FStringView& Module, uint64 Base, uint32 Size, const uint8* ImageId, uint32 ImageIdSize) = 0;`
- L17 _public prototype_ `virtual void OnModuleUnload(uint64 Base) = 0;`
- L18 _public prototype_ `virtual void OnAnalysisComplete() = 0;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace TraceServices`
- L22 _prototype_ `TSharedPtr<IModuleAnalysisProvider> CreateModuleProvider(IAnalysisSession& Session, const FAnsiStringView& SymbolFormat);` (scope `TraceServices`) — Create a module provider with the given symbol format.

### `Source/Developer/TraceServices/Private/Model/NetProfilerProvider.h` (Private)


#### struct `TraceServices::FNetProfilerGameInstanceInternal`  
`struct FNetProfilerGameInstanceInternal`  
_L15-27_
- L17 _public member_ `FNetProfilerGameInstance Instance;`
- L19 _public member_ `TPagedArray<FNetProfilerObjectInstance>* Objects;`
- L20 _public member_ `TArray<uint32, TInlineAllocator<128>> Connections;`
- L22 _public member_ `TPagedArray<FNetProfilerFrame>* Frames;`
- L23 _public member_ `TPagedArray<FNetProfilerStats>* FrameStats;`
- L25 _public member_ `uint32 ObjectsChangeCount;`
- L26 _public member_ `uint32 FramesChangeCount;`

#### struct `TraceServices::FNetProfilerConnectionData`  
`struct FNetProfilerConnectionData`  
_L29-47_
- L31 _public function_ `FNetProfilerConnectionData(ILinearAllocator& Allocator) : Packets(Allocator, 1024) , PacketStats(Allocator, 4096) , ContentEvents(Allocator, 8192) , PacketChangeCount(0u) , PacketStatsChangeCount(0u) , ContentEventChangeCount(0u)`
- L40 _public member_ `TPagedArray<FNetProfilerPacket> Packets;`
- L41 _public member_ `TPagedArray<FNetProfilerStats> PacketStats;`
- L42 _public member_ `TPagedArray<FNetProfilerContentEvent> ContentEvents;`
- L44 _public member_ `uint32 PacketChangeCount;`
- L45 _public member_ `uint32 PacketStatsChangeCount;`
- L46 _public member_ `uint32 ContentEventChangeCount;`

#### struct `TraceServices::FNetProfilerConnectionInternal`  
`struct FNetProfilerConnectionInternal`  
_L49-54_
- L51 _public member_ `FNetProfilerConnection Connection;`
- L53 _public member_ `FNetProfilerConnectionData* Data[ENetProfilerConnectionMode::Count];`

#### class `TraceServices::FNetProfilerProvider`  
`class FNetProfilerProvider : public INetProfilerProvider`  
_L56-164_
- inherits: `INetProfilerProvider`
- L60 _public prototype_ `explicit FNetProfilerProvider(IAnalysisSession& InSession);`
- L61 _public prototype_ `virtual ~FNetProfilerProvider();`
- L63 _public prototype_ `void SetNetTraceVersion(uint32 NetTraceVersion);`
- L65 _public prototype_ `FNetProfilerNameIndexType AddNetProfilerName(const TCHAR* Name);`
- L67 _public prototype_ `uint32 AddNetProfilerEventType(uint32 NameIndex, uint32 Level);`
- L69 _public prototype_ `uint32 AddNetProfilerStatsCounterType(uint32 NameIndex, ENetProfilerStatsCounterType Type);`
- L71 _public prototype_ `FNetProfilerGameInstanceInternal& CreateGameInstance();`
- L72 _public prototype_ `FNetProfilerGameInstanceInternal* EditGameInstance(uint32 GameInstanceIndex);`
- L73 _public prototype_ `void MarkGameInstancesDirty();`
- L75 _public prototype_ `FNetProfilerConnectionInternal& CreateConnection(uint32 GameInstanceIndex);`
- L76 _public prototype_ `FNetProfilerConnectionInternal* EditConnection(uint32 ConnectionIndex);`
- L77 _public prototype_ `FNetProfilerConnectionData& EditConnectionData(uint32 ConnectionIndex, ENetProfilerConnectionMode Mode);`
- L79 _public prototype_ `void EditPacketDeliveryStatus(uint32 ConnectionIndex, ENetProfilerConnectionMode Mode, uint32 SequenceNumber, ENetProfilerDeliveryStatus DeliveryStatus);`
- L81 _public prototype_ `FNetProfilerObjectInstance& CreateObject(uint32 GameInstanceIndex);`
- L82 _public prototype_ `FNetProfilerObjectInstance* EditObject(uint32 GameInstanceIndex, uint32 ObjectIndex);`
- L86 _public prototype_ `virtual uint32 GetNetTraceVersion() const override;`
- L89 _public function_ `virtual uint32 GetNameCount() const override` — Access Names
- L90 _public prototype_ `virtual void ReadNames(TFunctionRef<void(const FNetProfilerName*, uint64)> Callback) const override;`
- L91 _public prototype_ `virtual void ReadName(uint32 NameIndex, TFunctionRef<void(const FNetProfilerName&)> Callback) const override;`
- L94 _public function_ `virtual uint32 GetEventTypesCount() const override` — Access EventTypers
- L95 _public prototype_ `virtual void ReadEventTypes(TFunctionRef<void(const FNetProfilerEventType*, uint64)> Callback) const override;`
- L96 _public prototype_ `virtual void ReadEventType(uint32 EventTypeIndex, TFunctionRef<void(const FNetProfilerEventType&)> Callback) const override;`
- L99 _public function_ `virtual uint32 GetGameInstanceCount() const override` — Access GameInstances
- L100 _public prototype_ `virtual void ReadGameInstances(TFunctionRef<void(const FNetProfilerGameInstance&)> Callback) const override;`
- L101 _public function_ `virtual uint32 GetGameInstanceChangeCount() const override`
- L104 _public prototype_ `virtual uint32 GetConnectionCount(uint32 GameInstanceIndex) const override;` — Access Connections
- L105 _public prototype_ `virtual void ReadConnections(uint32 GameInstanceIndex, TFunctionRef<void(const FNetProfilerConnection&)> Callback) const override;`
- L106 _public prototype_ `virtual void ReadConnection(uint32 ConnectionIndex, TFunctionRef<void(const FNetProfilerConnection&)> Callback) const override;`
- L107 _public function_ `virtual uint32 GetConnectionChangeCount() const override`
- L110 _public prototype_ `virtual uint32 GetObjectCount(uint32 GameInstanceIndex) const override;` — Access Object Instances
- L111 _public prototype_ `virtual void ReadObjects(uint32 GameInstanceIndex, TFunctionRef<void(const FNetProfilerObjectInstance&)> Callback) const override;`
- L112 _public prototype_ `virtual void ReadObject(uint32 GameInstanceIndex, uint32 ObjectIndex, TFunctionRef<void(const FNetProfilerObjectInstance&)> Callback) const override;`
- L113 _public prototype_ `virtual uint32 GetObjectsChangeCount(uint32 GameInstanceIndex) const override;`
- L116 _public prototype_ `virtual int32 FindPacketIndexFromPacketSequence(uint32 ConnectionIndex, ENetProfilerConnectionMode Mode, uint32 SequenceNumber) const override;` — Find Packet Index from SequenceNumber
- L119 _public prototype_ `virtual uint32 GetPacketCount(uint32 ConnectionIndex, ENetProfilerConnectionMode Mode) const override;` — Enumerate packets in the provided packet interval
- L120 _public prototype_ `virtual void EnumeratePackets(uint32 ConnectionIndex, ENetProfilerConnectionMode Mode, uint32 PacketIndexIntervalStart, uint32 PacketIndexIntervalEnd, TFunctionRef<void(const FNetProfilerPacket&)> Callback) const override;`
- L121 _public prototype_ `virtual uint32 GetPacketChangeCount(uint32 ConnectionIndex, ENetProfilerConnectionMode Mode) const override;`
- L124 _public prototype_ `virtual void EnumeratePacketContentEventsByIndex(uint32 ConnectionIndex, ENetProfilerConnectionMode Mode, uint32 StartEventIndex, uint32 EndEventIndex, TFunctionRef<void(const FNetProfilerContentEvent&)> Callback) const override;` — Enumerate packet content events by range
- L125 _public prototype_ `virtual void EnumeratePacketContentEventsByPosition(uint32 ConnectionIndex, ENetProfilerConnectionMode Mode, uint32 PacketIndex, uint32 StartPos, uint32 EndPos, TFunctionRef<void(const FNetProfilerContentEvent&)> Callback) const override;`
- L126 _public prototype_ `virtual uint32 GetPacketContentEventChangeCount(uint32 ConnectionIndex, ENetProfilerConnectionMode Mode) const override;`
- L129 _public function_ `virtual uint32 GetNetStatsCounterTypesCount() const override` — Access StatsCounterTypes
- L130 _public prototype_ `virtual void ReadNetStatsCounterTypes(TFunctionRef<void(const FNetProfilerStatsCounterType*, uint64)> Callback) const override;`
- L131 _public prototype_ `virtual void ReadNetStatsCounterType(uint32 TypeIndex, TFunctionRef<void(const FNetProfilerStatsCounterType&)> Callback) const override;`
- L134 _public prototype_ `virtual ITable<FNetProfilerAggregatedStats>* CreateAggregation(uint32 ConnectionIndex, ENetProfilerConnectionMode Mode, uint32 PacketIndexIntervalStart, uint32 PacketIndexIntervalEnd, uint32 StartPosition, uint32 EndPosition) const override;` — Stats queries
- L135 _public prototype_ `virtual ITable<FNetProfilerAggregatedStatsCounterStats>* CreateStatsCountersAggregation(uint32 ConnectionIndex, ENetProfilerConnectionMode Mode, uint32 PacketIndexIntervalStart, uint32 PacketIndexIntervalEnd) const override;`
- L137 _public function_ `const TCHAR* InternalGetNetProfilerName(FNetProfilerNameIndexType NameIndex) const`
- L140 _private prototype_ `const FNetProfilerName* GetNetProfilerName(FNetProfilerNameIndexType ProfilerNameId) const;`
- L141 _private prototype_ `const FNetProfilerEventType* GetNetProfilerEventType(uint32 ProfilerEventTypeId) const;`
- L142 _private prototype_ `const FNetProfilerStatsCounterType* GetNetProfilerStatsCounterType(uint32 ProfilerStatsCounterTypeId) const;`
- L144 _private member_ `IAnalysisSession& Session;`
- L146 _private member_ `TArray<FNetProfilerName> Names;`
- L148 _private member_ `TArray<FNetProfilerEventType> EventTypes;`
- L150 _private member_ `TArray<FNetProfilerStatsCounterType> StatsCounterTypes;`
- L153 _private member_ `TArray<FNetProfilerGameInstanceInternal, TInlineAllocator<4>> GameInstances;` — All GameInstances seen throughout the session
- L156 _private member_ `TPagedArray<FNetProfilerConnectionInternal> Connections;` — All connections we have seen throughout the session
- L158 _private member_ `TTableLayout<FNetProfilerAggregatedStats> AggregatedStatsTableLayout;`
- L159 _private member_ `TTableLayout<FNetProfilerAggregatedStatsCounterStats> AggregatedStatsCounterStatsTableLayout;`
- L161 _private member_ `uint32 NetTraceVersion;`
- L162 _private member_ `uint32 ConnectionChangeCount;`
- L163 _private member_ `uint32 GameInstanceChangeCount;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace TraceServices`

### `Source/Developer/TraceServices/Private/Model/ObjectProviderPrivate.h` (Private)


#### class `TraceServices::FObjectSnapshot`  
`class FObjectSnapshot : public IObjectEditableSnapshot`  
_L17-99_
- inherits: `IObjectEditableSnapshot`
- L22 _public member_ `static constexpr uint32 MaxNumObjects = 1 << 25;` — ~33 million objects
- L23 _public member_ `static constexpr uint32 InvalidObjectId = uint32(-1);`
- L26 _public prototype_ `FObjectSnapshot();`
- L27 _public prototype_ `virtual ~FObjectSnapshot();`
- L29 _public function_ `virtual uint32 GetId() const`
- L31 _public function_ `static inline bool IsValidObjectId(uint32 ObjectId)`
- L35 _public function_ `inline bool IsValidObject(uint32 ObjectId)`
- L40 _public function_ `virtual double GetStartTime() const override`
- L41 _public function_ `virtual double GetEndTime() const override`
- L43 _public function_ `virtual uint32 GetObjectArrayNum() const override`
- L44 _public function_ `virtual uint32 GetObjectCount() const override`
- L45 _public function_ `virtual uint32 GetNumReferences() const override`
- L47 _public function_ `virtual bool HasTotalMemorySizes() const override`
- L48 _public function_ `virtual void EnableTotalMemorySizes() override`
- L50 _public function_ `virtual uint32 GetTracedObjectArrayNum() const override`
- L51 _public function_ `virtual void SetTracedObjectArrayNum(uint32 Count) override`
- L53 _public function_ `virtual uint32 GetTracedObjectArrayNumMinusAvailable() const override`
- L54 _public function_ `virtual void SetTracedObjectArrayNumMinusAvailable(uint32 Count) override`
- L56 _public function_ `virtual uint32 GetTracedObjectArrayNumPermanent() const override`
- L57 _public function_ `virtual void SetTracedObjectArrayNumPermanent(uint32 Count) override`
- L59 _public function_ `virtual const FObjectInfo* GetObject(uint32 ObjectId) const override`
- L63 _public function_ `virtual FObjectInfo* GetEditableObject(uint32 ObjectId) override`
- L68 _public function_ `virtual TConstArrayView<FObjectInfo> GetObjectsArray() const override`
- L69 _public function_ `virtual TConstArrayView<FObjectReferenceInfo> GetReferencesArray() const override`
- L71 _public function_ `inline bool IsEmpty() const`
- L76 _public prototype_ `FObjectInfo& GetOrAddObject(uint32 ObjectId);`
- L77 _public prototype_ `void EnumerateObjects(TFunctionRef<bool(const FObjectInfo&)> Callback) const;`
- L78 _public prototype_ `const FObjectInfo* FindObject(FStringView Name) const;`
- L80 _public prototype_ `void Validate();`
- L82 _public prototype_ `virtual void SaveAs(const TCHAR* CsvFileName) const;`
- L85 _private prototype_ `void ValidateExpectedFlags(FObjectInfo& Obj, EObjectInfoFlags ExpectedFlags);`
- L86 _private prototype_ `uint32 ValidateClassesRec(const TArray<uint32>& Classes, uint32 ClassClassId, uint32 BaseClassId, EObjectInfoFlags ExpectedClassFlags);`
- L89 _private member_ `uint32 Id;` — snapshot's unique id
- L90 _private member_ `double StartTime = 0.0;`
- L91 _private member_ `double EndTime = 0.0;`
- L92 _private member_ `bool bHasTotalMemorySizes = false;`
- L93 _private member_ `uint32 TracedObjectArrayNum = 0;`
- L94 _private member_ `uint32 TracedObjectArrayNumMinusAvailable = 0;`
- L95 _private member_ `uint32 TracedObjectArrayNumPermanent = 0;`
- L96 _private member_ `uint32 ObjectCount = 0;`
- L97 _private member_ `TArray<FObjectInfo> Objects;`
- L98 _private member_ `TArray<FObjectReferenceInfo> References;`

#### class `TraceServices::FObjectProvider`  
`class FObjectProvider : public IObjectProvider, public IEditableObjectProvider`  
_L101-155_
- inherits: `IObjectProvider,IEditableObjectProvider`
- L104 _public prototype_ `explicit FObjectProvider(IAnalysisSession& InSession);`
- L105 _public prototype_ `virtual ~FObjectProvider();`
- L111 _public function_ `virtual void BeginRead() const override` — IProvider
- L112 _public function_ `virtual void EndRead() const override`
- L113 _public function_ `virtual void ReadAccessCheck() const override`
- L116 _public prototype_ `virtual void EnumerateObjects(uint32 SnapshotId, TFunctionRef<bool(const FObjectInfo&)> Callback) const override;` — IObjectProvider
- L117 _public prototype_ `virtual const FObjectInfo* GetObject(uint32 SnapshotId, uint32 ObjectId) const override;`
- L118 _public prototype_ `virtual const FObjectInfo* FindObject(uint32 SnapshotId, FStringView Name) const override;`
- L119 _public prototype_ `virtual uint32 GetCurrentSnapshotObjectCount() const override;`
- L120 _public prototype_ `virtual uint32 GetCurrentSnapshotTotalObjectCount() const override;`
- L121 _public prototype_ `virtual uint32 GetNumSnapshots() const override;`
- L122 _public prototype_ `virtual void EnumerateSnapshots(TFunctionRef<bool(const IObjectSnapshot&)> Callback) const override;`
- L123 _public prototype_ `virtual const IObjectSnapshot* GetSnapshot(uint32 SnapshotId) const override;`
- L124 _public prototype_ `virtual bool IsCurrentSnapshotValid() const override;`
- L125 _public prototype_ `virtual const IObjectSnapshot* GetLowerBoundSnapshot(double Time) const override;`
- L131 _public function_ `virtual void BeginEdit() const override` — IEditableProvider
- L132 _public function_ `virtual void EndEdit() const override`
- L133 _public function_ `virtual void EditAccessCheck() const override`
- L136 _public prototype_ `virtual IObjectEditableSnapshot* GetCurrentSnapshot() override;` — IEditableObjectProvider
- L137 _public prototype_ `virtual IObjectEditableSnapshot* BeginSnapshot(double Time) override;`
- L138 _public prototype_ `virtual IObjectEditableSnapshot* EndSnapshot(double Time) override;`
- L139 _public prototype_ `virtual FObjectInfo* AddObject(uint32 Id, uint32 ClassId, uint32 OuterId, uint32 Flags, const TCHAR* PersistentName) override;`
- L140 _public prototype_ `virtual FObjectInfo* GetEditableObject(uint32 Id) override;`
- L141 _public prototype_ `virtual FObjectReferenceInfo* AddObjectReference(uint32 ReferencerId, uint32 ObjectId) override;`
- L142 _public function_ `virtual const IObjectProvider* GetReadProvider() const override`
- L147 _private prototype_ `void InternalReset();`
- L150 _private member_ `mutable FProviderLock Lock;`
- L151 _private member_ `IAnalysisSession& Session;`
- L153 _private member_ `TArray<FObjectSnapshot*> Snapshots;`
- L154 _private member_ `FObjectSnapshot* CurrentSnapshot = nullptr;`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace TraceServices`
- L15 _externvar_ `extern thread_local FProviderLock::FThreadLocalState GObjectProviderLockState;` (scope `TraceServices`)

### `Source/Developer/TraceServices/Private/Model/PsymResolver.h` (Private)


#### class `TraceServices::FPsymResolver`  
`class FPsymResolver : public FRunnable`  
_L21-127_
- inherits: `FRunnable`
- L24 _public typedef_ `typedef TArray<TTuple<uint64, FResolvedSymbol*>> SymbolArray;`
- L26 _public prototype_ `FPsymResolver(IAnalysisSession& InSession, IResolvedSymbolFilter& InSymbolFilter);`
- L27 _public prototype_ `~FPsymResolver();`
- L29 _public prototype_ `void Start();`
- L30 _public prototype_ `void QueueModuleLoad(const uint8* ImageId, uint32 ImageIdSize, FModule* Module);`
- L31 _public prototype_ `void QueueModuleReload(FModule* Module, const TCHAR* Path, TFunction<void(SymbolArray&)> ResolveOnSuccess);`
- L32 _public prototype_ `void QueueSymbolResolve(uint64 Address, FResolvedSymbol* Symbol);`
- L33 _public prototype_ `void OnAnalysisComplete();`
- L34 _public prototype_ `void GetStats(IModuleProvider::FStats* OutStats) const;`
- L35 _public prototype_ `bool HasFinishedResolving() const;`
- L36 _public prototype_ `void EnumerateSymbolSearchPaths(TFunctionRef<void(FStringView Path)> Callback) const;`
- L66 _private prototype_ `virtual uint32 Run() override;`
- L67 _private prototype_ `virtual void Stop() override;`
- L68 _private prototype_ `static void UpdateResolvedSymbol(FResolvedSymbol& Symbol, ESymbolQueryResult Result, const TCHAR* Module, const TCHAR* Name, const TCHAR* File, uint16 Line);`
- L70 _private prototype_ `void ResolveSymbol(uint64 Address, FResolvedSymbol& Target);`
- L71 _private prototype_ `void LoadModuleSymbols(const FModule* Module, const TCHAR* Path, const TArrayView<const uint8> ImageId);`
- L72 _private prototype_ `const FModuleEntry* GetEntryForModule(const FModule* Module) const;`
- L73 _private prototype_ `const FModuleEntry* GetModuleForAddress(uint64 Address) const;`
- L75 _private member_ `mutable FCriticalSection ModulesCs;`
- L76 _private member_ `TArray<FModuleEntry> LoadedModules;`
- L77 _private member_ `TQueue<FQueuedModule, EQueueMode::Mpsc> LoadSymbolsQueue;`
- L78 _private member_ `TQueue<FQueuedAddress, EQueueMode::Mpsc> ResolveQueue;`
- L80 _private member_ `std::atomic<uint32> ModulesDiscovered;`
- L81 _private member_ `std::atomic<uint32> ModulesFailed;`
- L82 _private member_ `std::atomic<uint32> ModulesLoaded;`
- L83 _private member_ `std::atomic<uint32> AlreadyResolvedSymbols;`
- L84 _private member_ `std::atomic<uint32> NoModuleSymbols;`
- L86 _private member_ `mutable FRWLock CustomSymbolSearchPathsLock;`
- L87 _private member_ `TArray<FString> CustomSymbolSearchPaths;` — search paths added by user from UI in the current session
- L88 _private member_ `TArray<FString> ConfigSymbolSearchPaths;` — search paths specified in environment variables and config files
- L90 _private member_ `bool bRunWorkerThread;`
- L91 _private member_ `bool bDrainThenStop;`
- L92 _private member_ `UPTRINT Handle;`
- L93 _private member_ `IAnalysisSession& Session;`
- L94 _private member_ `IResolvedSymbolFilter& SymbolFilter;`
- L95 _private member_ `FRunnableThread* Thread;`
- L124 _private member_ `TMap<int32, const TCHAR*> PsymSourceFiles;`
- L125 _private member_ `TArray<FPsymSymbol> PsymSymbols;`
- L126 _private member_ `TArray<FPsymLine> PsymSourceLines;`

#### struct `TraceServices::FPsymResolver::FModuleEntry`  
`struct FModuleEntry`  
_L39-47_
- L41 _public member_ `uint64 Base;`
- L42 _public member_ `uint32 Size;`
- L43 _public member_ `const TCHAR* Name;`
- L44 _public member_ `const TCHAR* Path;`
- L45 _public member_ `FModule* Module;`
- L46 _public member_ `TArray<uint8> ImageId;`

#### struct `TraceServices::FPsymResolver::FQueuedAddress`  
`struct FQueuedAddress`  
_L49-53_
- L51 _public member_ `uint64 Address;`
- L52 _public member_ `FResolvedSymbol* Target;`

#### struct `TraceServices::FPsymResolver::FQueuedModule`  
`struct FQueuedModule`  
_L55-60_
- L57 _public member_ `const FModule* Module;`
- L58 _public member_ `const TCHAR* Path;`
- L59 _public member_ `TArrayView<const uint8> ImageId;`

#### enum `TraceServices::FPsymResolver::(anonymous)`  
`enum : uint32`  
_L62-64_

#### struct `TraceServices::FPsymResolver::FPsymSymbol`  
`struct FPsymSymbol`  
_L97-108_
- L99 _public member_ `uint64 Address;`
- L100 _public member_ `uint32 Size;`
- L101 _public member_ `const TCHAR* Name;`
- L103 _public function_ `FPsymSymbol(uint64 InAddress, uint32 InSize, const TCHAR* InName) : Address(InAddress) , Size(InSize) , Name(InName)`

#### struct `TraceServices::FPsymResolver::FPsymLine`  
`struct FPsymLine`  
_L109-122_
- L111 _public member_ `uint64 Address;`
- L112 _public member_ `uint32 Size;`
- L113 _public member_ `int32 LineNumber;`
- L114 _public member_ `int32 FileIndex;`
- L116 _public function_ `FPsymLine(uint64 InAddress, uint32 InSize, int32 InLineNumber, int32 InFileIndex) : Address(InAddress) , Size(InSize) , LineNumber(InLineNumber) , FileIndex(InFileIndex)`

#### Free symbols / members of external scopes

- L15 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogPsymResolver, Log, All);`
- L15 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogPsymResolver, Log, All);`
- L17 _namespace_ `namespace TraceServices`
- L63 _enumerator_ `MaxNameLen = 512` (scope `TraceServices::FPsymResolver::__anon713503080103`)

### `Source/Developer/TraceServices/Private/Model/RegionsPrivate.h` (Private)


#### class `TraceServices::FRegionTimeline`  
`class FRegionTimeline : public IRegionTimeline`  
_L26-103_
- inherits: `IRegionTimeline`
- desc: A View onto a set of Timing Regions, sorted into a stack of individual lanes without overlaps for display, optionally filtered by Category
- L29 _public prototype_ `virtual ~FRegionTimeline() = default;`
- L31 _public function_ `FRegionTimeline(FRegionProvider& InProvider, IAnalysisSession& InSession, const FRegionCategoryImpl* InCategory) : Provider(InProvider) , Session(InSession) , Category(InCategory)`
- L40 _public prototype_ `const TCHAR* GetCategoryName() const override;` — @return the category name of this timeline if filtered or nullptr
- L45 _public prototype_ `const FRegionCategory* GetCategory() const override;` — @return the category of this timeline if filtered or nullptr
- L50 _public prototype_ `int32 GetLaneCount() const override;` — @return the number of lanes
- L57 _public prototype_ `const FRegionLane* GetLane(int32 Index) const override;` — Direct access to a certain lane at a given index/depth. The pointer is valid only in the current read scope. @return a pointer to the lane at the specified depth index or nullptr if Index is invalid
- L65 _public prototype_ `bool EnumerateRegions(double IntervalStart, double IntervalEnd, TFunctionRef<bool(const FTimeRegion& )> Callback) const override;` — Enumerates all regions that overlap a certain time interval. Will enumerate by depth but does not expose lanes. @param Callback a callback called for each region. Return false to abort iteration. @returns true if the enumeration finished, false if it was aborted by the callback returning false
- L73 _public prototype_ `bool EnumerateRegionsBackwards(double IntervalEnd, double IntervalStart, TFunctionRef<bool(const FTimeRegion& )> Callback) const override;` — Enumerates all regions that overlap a certain time interval in reverse. Will enumerate by depth but does not expose lanes. @param Callback a callback called for each region. Return false to abort iteration. @returns true if the enumeration finished, false if it was aborted by the callback returning false
- L78 _public prototype_ `void EnumerateLanes(TFunctionRef<void(const FRegionLane& , const int32 )> Callback) const override;` — Will call Callback(Lane, Depth) for each lane in order.
- L86 _private prototype_ `FTimeRegion* InsertNewRegion(const FRegionTimerImpl& Timer, double BeginTime, uint64 Id);` — Inserts a new Region into the stack, returns the created Region to allow the update of the region end time when it closes.
- L91 _private prototype_ `int32 CalculateRegionDepth(const FTimeRegion& Item) const;` — Update the depth member of a region to allow overlapping regions to be displayed on separate lanes.
- L95 _private member_ `TraceServices::FRegionProvider& Provider;` — The parent provider. Required to engage the ReadAccessLock or WriteAccessLock when a Lane is modified.
- L97 _private member_ `TraceServices::IAnalysisSession& Session;`
- L99 _private member_ `const FRegionCategoryImpl* Category = nullptr;`
- L102 _private member_ `TArray<FRegionLane> Lanes;` — Closed regions

#### struct `TraceServices::FRegionCategoryImpl`  
`struct FRegionCategoryImpl : public FRegionCategory`  
_L105-113_
- inherits: `FRegionCategory`
- L107 _public member_ `FRegionTimeline Timeline;`
- L109 _public function_ `FRegionCategoryImpl(FRegionProvider& InProvider, IAnalysisSession& InSession) : Timeline(InProvider, InSession, this)`

#### struct `TraceServices::FRegionTimerImpl`  
`struct FRegionTimerImpl : public FRegionTimer`  
_L115-117_
- inherits: `FRegionTimer`

#### class `TraceServices::FRegionProvider`  
`class FRegionProvider : public IRegionProvider , public IEditableRegionProvider`  
_L119-222_
- inherits: `IRegionProvider,IEditableRegionProvider`
- L124 _public prototype_ `explicit FRegionProvider(IAnalysisSession& Session);`
- L125 _public prototype_ `virtual ~FRegionProvider() override = default;`
- L130 _public function_ `virtual void BeginRead() const override`
- L131 _public function_ `virtual void EndRead() const override`
- L132 _public function_ `virtual void ReadAccessCheck() const override`
- L134 _public prototype_ `virtual bool EnumerateCategories(TFunctionRef<bool(const FRegionCategory&)> Callback) const override;`
- L135 _public prototype_ `virtual bool EnumerateTimers(TFunctionRef<bool(const FRegionTimer&)> Callback) const override;`
- L137 _public prototype_ `virtual void EnumerateTimelinesByCategory(TFunctionRef<void(const IRegionTimeline& , const TCHAR* )> Callback) const override;`
- L138 _public prototype_ `virtual const IRegionTimeline& GetDefaultTimeline() const override;`
- L139 _public prototype_ `virtual const IRegionTimeline* GetTimelineForCategory(const TCHAR* Category) const override;`
- L140 _public function_ `virtual const TCHAR* GetUncategorizedRegionCategoryName() const override`
- L142 _public prototype_ `virtual uint64 GetRegionCount() const override;`
- L143 _public function_ `virtual int32 GetLaneCount() const override`
- L145 _public prototype_ `virtual const FRegionLane* GetLane(int32 Index) const override;`
- L147 _public prototype_ `virtual bool EnumerateRegions(double IntervalStart, double IntervalEnd, TFunctionRef<bool(const FTimeRegion&)> Callback) const override;`
- L149 _public prototype_ `virtual void EnumerateLanes(TFunctionRef<void(const FRegionLane&, const int32)> Callback) const override;`
- L151 _public function_ `virtual uint64 GetUpdateCounter() const override`
- L156 _public function_ `virtual void BeginEdit() const override`
- L157 _public function_ `virtual void EndEdit() const override`
- L158 _public function_ `virtual void EditAccessCheck() const override`
- L160 _public function_ `virtual const FRegionCategory* RegisterRegionCategory(const TCHAR* Name) override`
- L165 _public function_ `virtual const FRegionTimer* RegisterRegionTimer(const TCHAR* Name, const FRegionCategory* Category = nullptr) override`
- L171 _public prototype_ `virtual void AppendRegionBegin(const TCHAR* Name, double Time, const TCHAR* Category = nullptr) override;`
- L172 _public prototype_ `virtual void AppendRegionBeginWithId(const TCHAR* Name, uint64 Id, double Time, const TCHAR* Category = nullptr) override;`
- L173 _public prototype_ `virtual void AppendRegionEnd(const TCHAR* Name, double Time) override;`
- L174 _public prototype_ `virtual void AppendRegionEndWithId(uint64 Id, double Time) override;`
- L176 _public prototype_ `virtual void OnAnalysisSessionEnded() override;`
- L181 _private prototype_ `FRegionCategoryImpl& GetOrAddRegionCategory(const TCHAR* CategoryName);`
- L182 _private prototype_ `FRegionTimerImpl& GetOrAddRegionTimer(const TCHAR* TimerName, const FRegionCategory* Category = nullptr);`
- L192 _private prototype_ `FOpenRegions AddRegionToTimelines(double BeginTime, const TCHAR* Name, uint64 Id, const TCHAR* Category);` — Adds a new region to the AllRegions timeline and to the category timeline (which can be the uncategorized timeline). @return The two added regions.
- L195 _private member_ `mutable FProviderLock Lock;`
- L197 _private member_ `IAnalysisSession& Session;`
- L199 _private member_ `TPagedArray<FRegionCategoryImpl> Categories;`
- L200 _private member_ `TPagedArray<FRegionTimerImpl> Timers;`
- L202 _private member_ `TMap<FStringView, FRegionCategoryImpl*> CategoriesByName;`
- L203 _private member_ `TMap<FStringView, FRegionTimerImpl*> TimersByName;`
- L206 _private member_ `TMap<FStringView, FOpenRegions> OpenRegionsByName;` — Open regions inside lanes
- L207 _private member_ `TMap<uint64, FOpenRegions> OpenRegionsById;`
- L209 _private member_ `FRegionTimeline AllRegionsTimeline;`
- L212 _private member_ `const TCHAR* UncategorizedName = TEXT("Unc` — String maps don't support nullptr, so use this key internally for all regions where category is nullptr.
- L215 _private member_ `uint64 UpdateCounter = -1;` — Counter incremented each time region data changes during analysis
- L217 _private member_ `static constexpr uint32 MaxWarningMessages = 100;`
- L218 _private member_ `static constexpr uint32 MaxErrorMessages = 100;`
- L220 _private member_ `uint32 NumWarnings = 0;`
- L221 _private member_ `uint32 NumErrors = 0;`

#### struct `TraceServices::FRegionProvider::FOpenRegions`  
`struct FOpenRegions`  
_L184-188_
- L186 _public member_ `FTimeRegion* Region;`
- L187 _public member_ `FTimeRegion* CategoryRegion;`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace TraceServices`
- L20 _externvar_ `extern thread_local FProviderLock::FThreadLocalState GRegionsProviderLockState;` (scope `TraceServices`)

### `Source/Developer/TraceServices/Private/Model/SbTree.h` (Private)


#### class `TraceServices::FSbTreeUtils`  
`class FSbTreeUtils`  
_L16-23_
- L19 _public prototype_ `static uint32 GetMaxDepth(uint32 TotalColumns);`
- L20 _public prototype_ `static uint32 GetCellAtDepth(uint32 Column, uint32 Depth);`
- L21 _public prototype_ `static uint32 GetCommonDepth(uint32 ColumnA, uint32 ColumnB);`
- L22 _public prototype_ `static uint32 GetCellWidth(uint32 CellIndex);`

#### class `TraceServices::FSbTreeCell`  
`class FSbTreeCell`  
_L27-55_
- L30 _public prototype_ `FSbTreeCell(ILinearAllocator& InAllocator);`
- L31 _public prototype_ `~FSbTreeCell();`
- L33 _public function_ `uint32 GetAllocCount() const`
- L35 _public prototype_ `void AddAlloc(const FAllocationItem* Alloc);` — takes ownership of memory allocated by Alloc pointer
- L37 _public function_ `uint32 GetMinStartEventIndex() const`
- L38 _public function_ `uint32 GetMaxEndEventIndex() const`
- L40 _public function_ `double GetMinStartTime() const`
- L41 _public function_ `double GetMaxEndTime() const`
- L43 _public prototype_ `void Query(TArray<const FAllocationItem*>& OutAllocs, const IAllocationsProvider::FQueryParams& Params) const;`
- L46 _private member_ `ILinearAllocator& Allocator;`
- L49 _private member_ `TArray<const FAllocationItem*> Allocs;` — TODO: TPagedArray<FAllocationItem> Allocs;
- L51 _private member_ `uint32 MinStartEventIndex;`
- L52 _private member_ `uint32 MaxEndEventIndex;`
- L53 _private member_ `double MinStartTime;`
- L54 _private member_ `double MaxEndTime;`

#### class `TraceServices::FSbTree`  
`class FSbTree`  
_L59-105_
- L62 _public prototype_ `FSbTree(ILinearAllocator& InAllocator, uint32 InColumnShift);`
- L63 _public prototype_ `~FSbTree();`
- L65 _public prototype_ `void SetTimeForEvent(uint32 EventIndex, double Time);`
- L67 _public prototype_ `void AddAlloc(const FAllocationItem* Alloc);` — takes ownership of memory allocated by Alloc pointer
- L69 _public function_ `uint32 GetColumnWidth() const`
- L70 _public function_ `uint32 GetCurrentColumn() const`
- L72 _public prototype_ `void Query(TArray<const FSbTreeCell*>& OutCells, const IAllocationsProvider::FQueryParams& Params) const;`
- L74 _public prototype_ `void IterateCells(TArray<const FSbTreeCell*>& OutCells, int32 Column) const;`
- L75 _public prototype_ `void IterateCells(TArray<const FSbTreeCell*>& OutCells, int32 StartColumn, int32 EndColumn) const;`
- L77 _public prototype_ `void DebugPrint() const;`
- L78 _public prototype_ `void Validate() const;`
- L81 _private prototype_ `int32 GetColumnsAtTime(double Time, int32* OutStartColumn, int32* OutEndColumn) const;`
- L84 _private member_ `ILinearAllocator& Allocator;`
- L87 _private member_ `TArray<FSbTreeCell*> Cells;` — Normal cells.
- L90 _private member_ `TArray<FSbTreeCell*> OffsettedCells;` — Offsetted cells. Note: Depth 0 doesn't use offsetted cells. Those will always be empty.
- L95 _private member_ `TArray<double> ColumnStartTimes;` — Array with time values of the first event in each column. Because multiple columns can have same time, CST[i] can also be assumed the time of the last event in previous column (i-1). Time range for events in column i is inclusive interval [CST[i], CST[i+1]], with CST[N] = infinity.
- L99 _private member_ `uint32 ColumnShift;` — It defines the width of a column (as number of events). ColumnWidth = 1 << ColumnShift
- L102 _private member_ `uint32 CurrentColumn;` — Index of the current (last) column.
- L104 _private member_ `double LastAllocEndTime = 0.0;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace TraceServices`

### `Source/Developer/TraceServices/Private/Model/ScreenshotProviderPrivate.h` (Private)


#### class `TraceServices::FScreenshotProvider`  
`class FScreenshotProvider : public IScreenshotProvider`  
_L11-25_
- inherits: `IScreenshotProvider`
- L15 _public prototype_ `explicit FScreenshotProvider(IAnalysisSession& Session);`
- L16 _public prototype_ `virtual ~FScreenshotProvider() = default;`
- L18 _public prototype_ `TSharedPtr<FScreenshot> AddScreenshot(uint32 Id);`
- L19 _public prototype_ `void AddScreenshotChunk(uint32 Id, uint32 ChunkNum, uint16 Size, const TArrayView<const uint8>& ChunkData);`
- L20 _public prototype_ `virtual const TSharedPtr<const FScreenshot> GetScreenshot(uint32 Id) const override;`
- L23 _private member_ `TMap<uint32, TSharedPtr<FScreenshot>> Screenshots;`
- L24 _private member_ `IAnalysisSession& Session;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace TraceServices`

### `Source/Developer/TraceServices/Private/Model/StackSamplesPrivate.h` (Private)


#### class `TraceServices::FStackSamplesProviderThread`  
`class FStackSamplesProviderThread`  
_L25-46_
- L30 _public function_ `FStackSamplesProviderThread(uint32 InSystemThreadId) : SystemThreadId(InSystemThreadId)`
- L34 _public prototype_ `~FStackSamplesProviderThread() = default;`
- L36 _public function_ `uint32 GetSystemThreadId() const`
- L37 _public function_ `const TCHAR* GetName() const`
- L38 _public function_ `FStackSamplesTimeline* GetTimeline() const`
- L41 _private member_ `uint32 SystemThreadId = 0;`
- L42 _private member_ `const TCHAR* Name = nullptr;`
- L43 _private member_ `TSharedPtr<FStackSamplesTimeline> Timeline;`
- L44 _private member_ `TArray<uint64> LastSampleStack;`
- L45 _private member_ `double LastSampleTime = 0.0;`

#### class `TraceServices::FStackSamplesProvider`  
`class FStackSamplesProvider : public IStackSamplesProvider , public IEditableProvider`  
_L48-116_
- inherits: `IStackSamplesProvider,IEditableProvider`
- L53 _public prototype_ `explicit FStackSamplesProvider(IAnalysisSession& Session);`
- L54 _public prototype_ `virtual ~FStackSamplesProvider();`
- L59 _public function_ `virtual void BeginRead() const override`
- L60 _public function_ `virtual void EndRead() const override`
- L61 _public function_ `virtual void ReadAccessCheck() const override`
- L63 _public prototype_ `virtual uint32 GetStackFrameCount() const override;`
- L64 _public prototype_ `virtual void EnumerateStackFrames(TFunctionRef<void(const FStackSampleFrame& Frame)> Callback) const override;`
- L66 _public prototype_ `virtual uint32 GetThreadCount() const override;`
- L67 _public prototype_ `virtual void EnumerateThreads(TFunctionRef<void(const FStackSampleThread& Thread)> Callback) const override;`
- L69 _public prototype_ `virtual uint32 GetTimelineCount() const override;`
- L70 _public prototype_ `virtual void EnumerateTimelines(TFunctionRef<void(const FStackSampleTimeline& Timeline, const FStackSampleThread& Thread)> Callback) const override;`
- L71 _public prototype_ `virtual const FStackSampleTimeline* GetTimeline(uint32 SystemThreadId) const override;`
- L76 _public function_ `virtual void BeginEdit() const override`
- L77 _public function_ `virtual void EndEdit() const override`
- L78 _public function_ `virtual void EditAccessCheck() const override`
- L80 _public prototype_ `void SetSamplingInterval(uint32 Microseconds);`
- L81 _public prototype_ `void AddThreadName(uint32 SystemThreadId, uint32 SystemProcessId, FStringView Name);`
- L82 _public prototype_ `void AddStackSample(uint32 SystemThreadId, double Time, uint32 Count, const uint64* Addresses);`
- L83 _public prototype_ `double OnAnalysisEnd();`
- L85 _public prototype_ `bool UpdatePendingTimers();`
- L90 _private prototype_ `FStackSamplesProviderThread& GetOrAddThread(uint32 SystemThreadId);`
- L91 _private prototype_ `FStackSampleFrame& GetOrAddStackFrame(uint64 Address);`
- L92 _private prototype_ `void CreateTimer(FStackSampleFrame& StackFrame);`
- L93 _private prototype_ `bool UpdateTimerName(FStackSampleFrame& StackFrame, bool bFirstTime);`
- L96 _private member_ `mutable FProviderLock Lock;`
- L98 _private member_ `IAnalysisSession& Session;`
- L99 _private member_ `IEditableTimingProfilerProvider* EditableTimingProfilerProvider = nullptr;`
- L100 _private member_ `IModuleProvider* ModuleProvider = nullptr;`
- L102 _private member_ `TPagedArray<FStackSamplesProviderThread> Threads;`
- L103 _private member_ `TArray<FStackSamplesProviderThread*> Timelines;` — the threads with a valid timeline
- L104 _private member_ `TMap<uint32, FStackSamplesProviderThread*> ThreadsBySystemId;` — SystemThreadId --> FThreadSamplingData*
- L105 _private member_ `TPagedArray<FStackSampleFrame> StackFrames;`
- L106 _private member_ `TMap<uint64, FStackSampleFrame*> StackFramesByAddress;` — Address --> FStackSampleFrame*
- L107 _private member_ `TMap<uint32, FStackSampleFrame*> StackFramesByTimerId;` — TimerId --> FStackSampleFrame*
- L108 _private member_ `TArray<FStackSampleFrame*> PendingTimers;`
- L110 _private member_ `double MaxSampleDuration = 0.0;` — [seconds]
- L111 _private member_ `uint32 SamplingIntervalUsec = 0;` — [microseconds]
- L113 _private member_ `int32 MaxStackSize = 0;`
- L114 _private member_ `uint64 TotalNumFrames = 0;`
- L115 _private member_ `uint64 TotalNumSamples = 0;`

#### Free symbols / members of external scopes

- L16 _namespace_ `namespace TraceServices`
- L21 _externvar_ `extern thread_local FProviderLock::FThreadLocalState GStackSamplesProviderLockState;` (scope `TraceServices`)
- L23 _typedef_ `typedef TMonotonicTimeline<FTimingProfilerEvent> FStackSamplesTimeline;` (scope `TraceServices`)

### `Source/Developer/TraceServices/Private/Model/SymslibResolver.h` (Private)


#### class `TraceServices::FSymslibResolver`  
`class FSymslibResolver`  
_L33-140_
- L36 _public typedef_ `typedef TArray<TTuple<uint64, FResolvedSymbol*>> SymbolArray;`
- L38 _public prototype_ `FSymslibResolver(IAnalysisSession& InSession, IResolvedSymbolFilter& InSymbolFilter);`
- L39 _public prototype_ `~FSymslibResolver();`
- L41 _public prototype_ `void QueueModuleLoad(const uint8* ImageId, uint32 ImageIdSize, FModule* Module);`
- L42 _public prototype_ `void QueueModuleReload(FModule* Module, const TCHAR* Path, TFunction<void(SymbolArray&)> ResolveOnSuccess);`
- L43 _public prototype_ `void QueueSymbolResolve(uint64 Address, FResolvedSymbol* Symbol);`
- L44 _public prototype_ `void OnAnalysisComplete();`
- L45 _public prototype_ `void GetStats(IModuleProvider::FStats* OutStats) const;`
- L46 _public prototype_ `bool HasFinishedResolving() const;`
- L47 _public prototype_ `void EnumerateSymbolSearchPaths(TFunctionRef<void(FStringView Path)> Callback) const;`
- L96 _private prototype_ `void MaybeDispatchQueuedAddresses();` — Checks if there are no modules in flight and that the queue has reached the threshold for dispatching. Note that is up to the caller to synchronize.
- L100 _private prototype_ `void DispatchQueuedAddresses();` — Dispatches the currently queued addresses to be resolved. Note that is up to the caller to synchronize.
- L101 _private prototype_ `void ResolveSymbols(TArrayView<FQueuedAddress>& QueuedWork);`
- L102 _private prototype_ `FModuleEntry* GetModuleEntry(FModule* Module) const;`
- L103 _private prototype_ `FModuleEntry* GetModuleForAddress(uint64 Address) const;`
- L104 _private prototype_ `static void UpdateResolvedSymbol(FResolvedSymbol& Symbol, ESymbolQueryResult Result, const TCHAR* Module, const TCHAR* Name, const TCHAR* File, uint16 Line);`
- L105 _private prototype_ `void LoadModuleTracked(FModuleEntry* Entry, FStringView OverrideSearchPath);`
- L106 _private prototype_ `EModuleStatus LoadModule(FModuleEntry* Entry, FStringView SearchPathView, FStringBuilderBase& OutStatusMessage) const;`
- L107 _private prototype_ `void ResolveSymbolTracked(uint64 Address, FResolvedSymbol& Target, class FSymbolStringAllocator& StringAllocator);`
- L108 _private prototype_ `bool ResolveSymbol(uint64 Address, FResolvedSymbol& Target, FSymbolStringAllocator& StringAllocator, FModuleEntry* Entry) const;`
- L109 _private prototype_ `void WaitForTasks();`
- L110 _private prototype_ `void UpdateSessionInfo() const;`
- L112 _private member_ `mutable FRWLock ModulesLock;`
- L113 _private member_ `TPagedArray<FModuleEntry> Modules;`
- L114 _private member_ `TArray<FModuleEntry*> SortedModules;`
- L115 _private member_ `FCriticalSection SymbolsQueueLock;`
- L116 _private member_ `TArray<FQueuedAddress, TInlineAllocator<QueuedAddressLength>> ResolveQueue;`
- L117 _private member_ `std::atomic<uint32> TasksInFlight;`
- L118 _private member_ `FCriticalSection CleanupLock;`
- L119 _private member_ `FGraphEventRef CleanupTask;`
- L120 _private member_ `FGraphEventRef ModuleReloadTask;`
- L121 _private member_ `std::atomic<bool> CancelTasks;`
- L123 _private member_ `mutable FRWLock CustomSymbolSearchPathsLock;`
- L124 _private member_ `TArray<FString> CustomSymbolSearchPaths;` — search paths added by user from UI in the current session
- L125 _private member_ `TArray<FString> ConfigSymbolSearchPaths;` — search paths specified in environment variables and config files
- L127 _private member_ `mutable FString Platform;`
- L128 _private member_ `mutable FString AppName;`
- L130 _private member_ `std::atomic<uint32> ModulesDiscovered;`
- L131 _private member_ `std::atomic<uint32> ModulesFailed;`
- L132 _private member_ `std::atomic<uint32> ModulesLoaded;`
- L133 _private member_ `std::atomic<uint32> AlreadyResolvedSymbols;`
- L134 _private member_ `std::atomic<uint32> NoModuleSymbols;`
- L135 _private member_ `std::atomic<uint64> SymbolBytesAllocated;`
- L136 _private member_ `std::atomic<uint64> SymbolBytesWasted;`
- L138 _private member_ `IAnalysisSession& Session;`
- L139 _private member_ `IResolvedSymbolFilter& SymbolFilter;`

#### struct `TraceServices::FSymslibResolver::FSymsSymbol`  
`struct FSymsSymbol`  
_L50-53_
- L52 _public member_ `const char* Name;`

#### struct `TraceServices::FSymslibResolver::FSymsUnit`  
`struct FSymsUnit`  
_L55-61_
- L57 _public member_ `SYMS_SpatialMap1D ProcMap;`
- L58 _public member_ `SYMS_String8Array FileTable;`
- L59 _public member_ `SYMS_LineTable LineTable;`
- L60 _public member_ `SYMS_SpatialMap1D LineMap;`

#### struct `TraceServices::FSymslibResolver::FSymsInstance`  
`struct FSymsInstance`  
_L63-71_
- L65 _public member_ `TArray<SYMS_Arena*> Arenas;`
- L66 _public member_ `TArray<FSymsUnit> Units;`
- L67 _public member_ `SYMS_SpatialMap1D UnitMap;`
- L68 _public member_ `SYMS_SpatialMap1D StrippedMap;`
- L69 _public member_ `FSymsSymbol* StrippedSymbols;`
- L70 _public member_ `uint64 DefaultBase;`

#### struct `TraceServices::FSymslibResolver::FModuleEntry`  
`struct FModuleEntry`  
_L73-78_
- L75 _public member_ `FModule* Module;`
- L76 _public member_ `TArray<uint8> ImageId;`
- L77 _public member_ `FSymsInstance Instance;`

#### struct `TraceServices::FSymslibResolver::FQueuedAddress`  
`struct FQueuedAddress`  
_L80-84_
- L82 _public member_ `uint64 Address;`
- L83 _public member_ `FResolvedSymbol* Target;`

#### enum `TraceServices::FSymslibResolver::(anonymous)`  
`enum : uint32`  
_L86-90_

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_SYMSLIB_AVAILABLE 1`
- L10 _macro_ `#define UE_SYMSLIB_AVAILABLE 0`
- L28 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogSymslib, Log, All);`
- L28 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogSymslib, Log, All);`
- L30 _namespace_ `namespace TraceServices`
- L87 _enumerator_ `MaxNameLen = 512` (scope `TraceServices::FSymslibResolver::__anon287f37220103`)
- L88 _enumerator_ `QueuedAddressLength = 2048` (scope `TraceServices::FSymslibResolver::__anon287f37220103`)
- L89 _enumerator_ `SymbolTasksInParallel = 8` (scope `TraceServices::FSymslibResolver::__anon287f37220103`)

### `Source/Developer/TraceServices/Private/Model/TableImportTask.h` (Private)


#### class `TraceServices::FImportTableRow`  
`class FImportTableRow`  
_L19-40_
- L22 _public function_ `FColumnValueContainer GetValue(uint64 ColumnIndex) const`
- L28 _public function_ `template<typename T> void SetValue(uint64 ColumnIndex, T Value)`
- L33 _public function_ `void SetNumValues(uint64 NumColumns)`
- L39 _private member_ `TArray<FColumnValueContainer> Values;`

#### class `TraceServices::TImportTable`  
`template<typename RowType> class TImportTable : public TTable<RowType, GImportTableAllocatorSlabSize>`  
_L45-60_
- inherits: `TTable<RowType,GImportTableAllocatorSlabSize>`
- L49 _public function_ `TImportTable() : TTable<RowType, GImportTableAllocatorSlabSize>() , StringStore(TTable<RowType, GImportTableAllocatorSlabSize>::Allocator)`
- L54 _public prototype_ `virtual ~TImportTable() = default;`
- L56 _public function_ `FStringStore& GetStringStore()`
- L59 _private member_ `FStringStore StringStore;`

#### class `TraceServices::FTableImportTask`  
`class FTableImportTask`  
_L62-90_
- L65 _public prototype_ `FTableImportTask(const FString& InFilePath, FName InTableId, FTableImportService::TableImportCallback InCallback);`
- L66 _public prototype_ `~FTableImportTask();`
- L68 _public prototype_ `void operator()();`
- L70 _public prototype_ `bool ParseHeader(const FString& HeaderLine);`
- L71 _public prototype_ `bool CreateLayout(const FString& Line);`
- L72 _public prototype_ `bool ParseData(TArray<FString>& Lines);`
- L75 _private prototype_ `ETableImportResult ImportTable();`
- L77 _private prototype_ `void SplitLineIntoValues(const FString& InLine, TArray<FString>& OutValues);`
- L78 _private prototype_ `bool LoadFileToStringArray(const FString& InFilePath, TArray<FString>& Lines);`
- L80 _private prototype_ `void AddError(const FText& Msg);`
- L82 _private member_ `FTableImportService::TableImportCallback Callback;`
- L83 _private member_ `TSharedPtr<TImportTable<FImportTableRow>> Table;`
- L85 _private member_ `TArray<TSharedRef<FTokenizedMessage>> Messages;`
- L86 _private member_ `TArray<FString> ColumnNames;`
- L87 _private member_ `FString FilePath;`
- L88 _private member_ `FName TableId;`
- L89 _private member_ `FString Separator;`

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace TraceServices`
- L42 _variable_ `constexpr int GImportTableAllocatorSlabSize = 32 << 20;` (scope `TraceServices`)

### `Source/Developer/TraceServices/Private/Model/TableMergeTask.h` (Private)


#### class `TraceServices::FTableMergeTask`  
`class FTableMergeTask`  
_L14-45_
- L17 _public prototype_ `FTableMergeTask(const TSharedPtr<IUntypedTable>& InTableA, const TSharedPtr<IUntypedTable>& InTableB, FTableMergeService::TableDiffCallback InCallback);`
- L19 _public prototype_ `void operator()();`
- L22 _private prototype_ `ETableDiffResult MergeTables();`
- L30 _private prototype_ `bool BuildCLayout(const ITableLayout& LayoutA, const ITableLayout& LayoutB, TTableLayout<FImportTableRow>& LayoutC);`
- L33 _private prototype_ `template<typename Variant, Sign Operation> void FillResultUsing(IUntypedTableReader& SourceTableReader) const;`
- L35 _private prototype_ `void AddError(const FText& Msg);`
- L38 _private member_ `const TSharedPtr<IUntypedTable> TableA;`
- L39 _private member_ `const TSharedPtr<IUntypedTable> TableB;`
- L40 _private member_ `const FTableMergeService::TableDiffCallback Callback;`
- L42 _private member_ `TSharedPtr<TImportTable<FImportTableRow>> TableC;`
- L43 _private member_ `TArray<TSharedRef<FTokenizedMessage>> Messages;`
- L44 _private member_ `TArray<TVariant<FEmptyVariantState, FBoth, FOnlyA, FOnlyB, FMerged>> ColumnsMap;`
- L48 _function_ `template <typename Variant, FTableMergeTask::Sign Operation> void FTableMergeTask::FillResultUsing(IUntypedTableReader& SourceTableReader) const`

#### struct `TraceServices::FTableMergeTask::FBoth`  
`struct FBoth`  
_L24-24_
- L24 _public function_ `struct FBoth`
- L24 _public member_ `struct FBoth { FBoth(uint64 Index) : ColIndex(Index) {} uint64 ColIndex; };`

#### struct `TraceServices::FTableMergeTask::FOnlyA`  
`struct FOnlyA`  
_L25-25_
- L25 _public function_ `struct FOnlyA`
- L25 _public member_ `struct FOnlyA { FOnlyA(uint64 Index) : ColIndex(Index) {} uint64 ColIndex; };`

#### struct `TraceServices::FTableMergeTask::FOnlyB`  
`struct FOnlyB`  
_L26-26_
- L26 _public function_ `struct FOnlyB`
- L26 _public member_ `struct FOnlyB { FOnlyB(uint64 Index) : ColIndex(Index) {} uint64 ColIndex; };`

#### struct `TraceServices::FTableMergeTask::FMerged`  
`struct FMerged`  
_L27-27_
- L27 _public function_ `struct FMerged`
- L27 _public member_ `struct FMerged { FMerged(uint64 Index) : ColIndex(Index) {} uint64 ColIndex; };`

#### enum `TraceServices::FTableMergeTask::Sign`  
`enum class Sign`  
_L28-28_
- L28 _public enumerator_ `enum class Sign { Positive, Negative }; bool BuildCLayout(const ITableLayout& LayoutA, const ITableLayout& LayoutB, TTableLayout<FImportTableRow>& LayoutC); template<typename Variant`
- L28 _public enumerator_ `enum class Sign { Positive, Negative }; bool BuildCLayout(const ITableLayout& LayoutA, const ITableLayout& LayoutB, TTableLayout<FImportTableRow>& LayoutC); template<typename Variant`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace TraceServices`

### `Source/Developer/TraceServices/Private/Model/Tables.h` (Private)


#### struct `TraceServices::FColumnValueContainer`  
`struct FColumnValueContainer`  
_L89-149_
- L91 _public function_ `FColumnValueContainer(bool Value)`
- L96 _public function_ `FColumnValueContainer(int8 Value)`
- L101 _public function_ `FColumnValueContainer(uint8 Value)`
- L106 _public function_ `FColumnValueContainer(int32 Value)`
- L111 _public function_ `FColumnValueContainer(uint32 Value)`
- L116 _public function_ `FColumnValueContainer(int64 Value)`
- L121 _public function_ `FColumnValueContainer(uint64 Value)`
- L126 _public function_ `FColumnValueContainer(float Value)`
- L131 _public function_ `FColumnValueContainer(double Value)`
- L136 _public function_ `FColumnValueContainer(const TCHAR* Value)`

#### union `TraceServices::FColumnValueContainer::(anonymous)`  
``  
_L142-148_

#### class `TraceServices::TTableLayout`  
`template<typename RowType> class TTableLayout : public ITableLayout`  
_L152-252_
- inherits: `ITableLayout`
- L157 _public function_ `template<typename ColumnNativeType> TTableLayout<RowType>& AddColumn(ColumnNativeType RowType::* MemberVariableColumn, const TCHAR* ColumnName, uint32 DisplayHintFlags = 0)`
- L172 _public function_ `template<typename ColumnNativeType> TTableLayout<RowType>& AddColumn(ColumnNativeType(RowType::* MemberFunctionColumn)() const, const TCHAR* ColumnName, uint32 DisplayHintFlags = 0)`
- L187 _public function_ `template<typename ColumnNativeType> TTableLayout<RowType>& AddColumn(ColumnNativeType(*FunctionColumn)(const RowType&), const TCHAR* ColumnName, uint32 DisplayHintFlags = 0)`
- L202 _public function_ `template<typename ColumnNativeType> TTableLayout<RowType>& AddColumn(const TCHAR* ColumnName, TFunction<FColumnValueContainer(const RowType&)> Projector, uint32 DisplayHintFlags = 0)`
- L212 _public function_ `uint64 GetColumnCount() const override`
- L217 _public function_ `const TCHAR* GetColumnName(uint64 ColumnIndex) const override`
- L222 _public function_ `ETableColumnType GetColumnType(uint64 ColumnIndex) const override`
- L227 _public function_ `void SetColumnType(uint64 ColumnIndex, ETableColumnType ColumnType)`
- L232 _public function_ `uint32 GetColumnDisplayHintFlags(uint64 ColumnIndex) const override`
- L237 _public function_ `FColumnValueContainer GetColumnValue(const RowType& Row, uint64 ColumnIndex) const`
- L251 _private member_ `TArray<FColumnDeclaration> Columns;`

#### struct `TraceServices::TTableLayout::FColumnDeclaration`  
`struct FColumnDeclaration`  
_L243-249_
- L245 _public member_ `FString Name;`
- L246 _public member_ `ETableColumnType Type;`
- L247 _public member_ `uint32 DisplayHintFlags;`
- L248 _public member_ `TFunction<FColumnValueContainer(const RowType&)> Projector;`

#### class `TraceServices::TTableReader`  
`template<typename RowType> class TTableReader : public ITableReader<RowType>`  
_L255-389_
- inherits: `ITableReader<RowType>`
- L259 _public function_ `TTableReader(const TTableLayout<RowType>& InLayout, const TPagedArray<RowType>& InRows) : Layout(InLayout) , Iterator(InRows.GetIteratorFromItem(0))`
- L266 _public function_ `virtual bool IsValid() const override`
- L271 _public function_ `virtual void NextRow() override`
- L276 _public function_ `virtual void SetRowIndex(uint64 RowIndex) override`
- L281 _public function_ `virtual const RowType* GetCurrentRow() const override`
- L286 _public function_ `virtual bool GetValueBool(uint64 ColumnIndex) const override`
- L307 _public function_ `virtual int64 GetValueInt(uint64 ColumnIndex) const override`
- L328 _public function_ `virtual float GetValueFloat(uint64 ColumnIndex) const override`
- L349 _public function_ `virtual double GetValueDouble(uint64 ColumnIndex) const override`
- L370 _public function_ `virtual const TCHAR* GetValueCString(uint64 ColumnIndex) const override`
- L386 _private member_ `const TTableLayout<RowType>& Layout;`
- L387 _private member_ `typename TPagedArray<RowType>::TIterator Iterator;`
- L388 _private member_ `const RowType* CurrentRow;`

#### class `TraceServices::TTableBase`  
`template<typename RowType> class TTableBase : public ITable<RowType>`  
_L392-430_
- inherits: `ITable<RowType>`
- L396 _public prototype_ `TTableBase() = default;`
- L398 _public function_ `TTableBase(TTableLayout<RowType> InLayout) : Layout(InLayout)`
- L404 _public prototype_ `virtual ~TTableBase() = default;`
- L406 _public function_ `const ITableLayout& GetLayout() const override`
- L411 _public function_ `uint64 GetRowCount() const override`
- L416 _public function_ `ITableReader<RowType>* CreateReader() const override`
- L421 _public function_ `TTableLayout<RowType>& EditLayout()`
- L427 _private prototype_ `virtual const TPagedArray<RowType>& GetRows() const = 0;`
- L429 _private member_ `TTableLayout<RowType> Layout;`

#### class `TraceServices::TTableView`  
`template<typename RowType> class TTableView : public TTableBase<RowType>`  
_L433-449_
- inherits: `TTableBase<RowType>`
- L437 _public function_ `TTableView(const TPagedArray<RowType>& InRows) : Rows(InRows)`
- L443 _private function_ `virtual const TPagedArray<RowType>& GetRows() const override`
- L448 _private member_ `const TPagedArray<RowType>& Rows;`

#### class `TraceServices::TTable`  
`template<typename RowType, int AllocatorSlabSize = 2 << 20> class TTable : public TTableBase<RowType>`  
_L452-486_
- inherits: `TTableBase<RowType>`
- L456 _public function_ `TTable() : Allocator(AllocatorSlabSize) , Rows(Allocator, 1024)`
- L463 _public function_ `TTable(TTableLayout<RowType> Layout) : TTableBase<RowType>(Layout) , Allocator(AllocatorSlabSize) , Rows(Allocator, 1024)`
- L471 _public function_ `RowType& AddRow()`
- L477 _protected member_ `FSlabAllocator Allocator;`
- L480 _private function_ `virtual const TPagedArray<RowType>& GetRows() const override`
- L485 _private member_ `TPagedArray<RowType> Rows;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace TraceServices`
- L15 _prototype_ `template<typename Type> static constexpr ETableColumnType GetColumnTypeFromNativeType();` (scope `TraceServices`)
- L18 _function_ `template<> constexpr ETableColumnType GetColumnTypeFromNativeType<bool>()` (scope `TraceServices`)
- L24 _function_ `template<> constexpr ETableColumnType GetColumnTypeFromNativeType<int8>()` (scope `TraceServices`)
- L30 _function_ `template<> constexpr ETableColumnType GetColumnTypeFromNativeType<uint8>()` (scope `TraceServices`)
- L36 _function_ `template<> constexpr ETableColumnType GetColumnTypeFromNativeType<int16>()` (scope `TraceServices`)
- L42 _function_ `template<> constexpr ETableColumnType GetColumnTypeFromNativeType<uint16>()` (scope `TraceServices`)
- L48 _function_ `template<> constexpr ETableColumnType GetColumnTypeFromNativeType<int32>()` (scope `TraceServices`)
- L54 _function_ `template<> constexpr ETableColumnType GetColumnTypeFromNativeType<uint32>()` (scope `TraceServices`)
- L60 _function_ `template<> constexpr ETableColumnType GetColumnTypeFromNativeType<int64>()` (scope `TraceServices`)
- L66 _function_ `template<> constexpr ETableColumnType GetColumnTypeFromNativeType<uint64>()` (scope `TraceServices`)
- L72 _function_ `template<> constexpr ETableColumnType GetColumnTypeFromNativeType<float>()` (scope `TraceServices`)
- L78 _function_ `template<> constexpr ETableColumnType GetColumnTypeFromNativeType<double>()` (scope `TraceServices`)
- L84 _function_ `template<> constexpr ETableColumnType GetColumnTypeFromNativeType<const TCHAR*>()` (scope `TraceServices`)
- L143 _member_ `bool BoolValue;` (scope `TraceServices::FColumnValueContainer::__anonba27d428010a`)
- L144 _member_ `int64 IntValue;` (scope `TraceServices::FColumnValueContainer::__anonba27d428010a`)
- L145 _member_ `float FloatValue;` (scope `TraceServices::FColumnValueContainer::__anonba27d428010a`)
- L146 _member_ `double DoubleValue;` (scope `TraceServices::FColumnValueContainer::__anonba27d428010a`)
- L147 _member_ `const TCHAR* StringValue;` (scope `TraceServices::FColumnValueContainer::__anonba27d428010a`)
- L164 _function_ `` (scope `TraceServices::TTableLayout::AddColumn`)

### `Source/Developer/TraceServices/Private/Model/TasksProfilerPrivate.h` (Private)


#### class `TraceServices::FTasksProvider`  
`class FTasksProvider : public ITasksProvider`  
_L16-104_
- inherits: `ITasksProvider`
- desc: tasks database, filled by the analyser and consumed by UI. Creates and fills a number of counters. Unprocessed info can be queried by `ITasksProvider` interface
- L19 _public prototype_ `explicit FTasksProvider(IAnalysisSession& Session);`
- L20 _public prototype_ `virtual ~FTasksProvider() = default;`
- L22 _public prototype_ `void Init(uint32 Version);`
- L25 _public prototype_ `void TaskCreated(TaskTrace::FId TaskId, double Timestamp, uint32 ThreadId, uint64 TaskSize);` — traces consumption
- L26 _public prototype_ `void TaskLaunched(TaskTrace::FId TaskId, const TCHAR* DebugName, bool bTracked, int32 ThreadToExecuteOn, double Timestamp, uint32 ThreadId, uint64 TaskSize);`
- L27 _public prototype_ `void TaskScheduled(TaskTrace::FId TaskId, double Timestamp, uint32 ThreadId);`
- L28 _public prototype_ `void SubsequentAdded(TaskTrace::FId TaskId, TaskTrace::FId SubsequentId, double Timestamp, uint32 ThreadId);`
- L29 _public prototype_ `void TaskStarted(TaskTrace::FId TaskId, double Timestamp, uint32 ThreadId);`
- L30 _public prototype_ `void TaskFinished(TaskTrace::FId TaskId, double Timestamp);`
- L31 _public prototype_ `void TaskCompleted(TaskTrace::FId TaskId, double Timestamp, uint32 ThreadId);`
- L32 _public prototype_ `void TaskDestroyed(TaskTrace::FId TaskId, double Timestamp, uint32 ThreadId);`
- L34 _public prototype_ `void WaitingStarted(TArray<TaskTrace::FId> Tasks, double Timestamp, uint32 ThreadId);`
- L35 _public prototype_ `void WaitingFinished(double Timestamp, uint32 ThreadId);`
- L38 _public prototype_ `virtual const FTaskInfo* TryGetTask(uint32 ThreadId, double Timestamp) const override;` — ITasksProvider impl
- L39 _public prototype_ `virtual const FTaskInfo* TryGetTask(TaskTrace::FId TaskId) const;`
- L40 _public prototype_ `virtual const FWaitingForTasks* TryGetWaiting(const TCHAR* TimerName, uint32 ThreadId, double Timestamp) const override;`
- L41 _public prototype_ `virtual TArray<TaskTrace::FId> TryGetParallelForTasks(const TCHAR* TimerName, uint32 ThreadId, double StartTime, double EndTime) const override;`
- L42 _public prototype_ `virtual int64 GetNumTasks() const override;`
- L43 _public prototype_ `virtual void EnumerateTasks(double StartTime, double EndTime, ETaskEnumerationOption EnumerationOption, TaskCallback Callback) const override;`
- L47 _private prototype_ `void InitTaskIdToIndexConversion(TaskTrace::FId FirstTaskId);` — initializes conversion of task id to its index in the internal container, if it's not initialized already
- L50 _private prototype_ `` — `FistTaskId` must be initialised before the first use
- L52 _private prototype_ `FTaskInfo* TryGetTask(TaskTrace::FId TaskId);`
- L54 _private prototype_ `FTaskInfo* TryGetOrCreateTask(TaskTrace::FId TaskId);` — default-constructs a task if required
- L56 _private prototype_ `static bool IsNamedThread(int32 Thread);`
- L58 _private prototype_ `void CreateCounters();`
- L60 _private prototype_ `void AddRelative(const TCHAR* RelativeType, TaskTrace::FId TaskId, TArray<FTaskInfo::FRelationInfo> FTaskInfo::* RelationsPtr, TaskTrace::FId RelativeId, double Timestamp, uint32 ThreadId);`
- L63 _private member_ `IAnalysisSession& Session;` — for synchronisation with consumers
- L65 _private member_ `uint32 Version = ~(uint32)0;`
- L69 _private member_ `TArray64<FTaskInfo> Tasks;` — task IDs are auto-incremented almost monotonic numbers, they are used as indices into tasks array minus the first task ID "almost monotonic" because a trace with TaskId==N+1 can arrive before all traces with TaskId==N
- L73 _private member_ `TMap<uint32, TArray64<TaskTrace::FId>> ExecutionThreads;` — on execution start, when it becomes known which thread will execute a task, all tasks are grouped by their execution threads, where they are naturally sorted by `StartedTimestamp`
- L75 _private member_ `TMap<uint32, TArray64<FWaitingForTasks>> WaitingThreads;` — ThreadId -> [Waiting]
- L78 _private member_ `TaskTrace::FId FirstTaskId = TaskTrace::InvalidId;` — task ID of the first trace. as traces can race, it's possible some traces of the previous task will be lost, which is not a probem
- L82 _private member_ `int64 WaitingForPrerequisitesTasksNum = 0;` — number of tasks waiting to be scheduled, because they are blocked by dependencies or they will be immediately scheduled and reported by another task trace
- L84 _private member_ `int64 ScheduledTasksNum = 0;` — number of non named threads tasks sheduled for execution
- L86 _private member_ `int64 NamedThreadsScheduledTasksNum = 0;` — number of named threads tasks scheduled for execution
- L88 _private member_ `int64 RunningTasksNum = 0;` — number of tasks being executed
- L90 _private member_ `bool bCountersCreated = false;` — a bool that is set when the counters are created
- L92 _private member_ `int64 AliveTasksNum = 0;` — number of alive tasks
- L93 _private member_ `int64 AliveTasksSize = 0;`
- L95 _private member_ `IEditableCounterProvider& EditableCounterProvider;`
- L96 _private member_ `IEditableCounter* TaskLatencyCounter;`
- L97 _private member_ `IEditableCounter* WaitingForPrerequisitesTasksCounter;`
- L98 _private member_ `IEditableCounter* ScheduledTasksCounter;`
- L99 _private member_ `IEditableCounter* NamedThreadsScheduledTasksCounter;`
- L100 _private member_ `IEditableCounter* RunningTasksCounter;`
- L101 _private member_ `IEditableCounter* ExecutionTimeCounter;`
- L102 _private member_ `IEditableCounter* AliveTasksCounter;`
- L103 _private member_ `IEditableCounter* AliveTasksSizeCounter;`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace TraceServices`

### `Source/Developer/TraceServices/Private/Model/ThreadsPrivate.h` (Private)


#### class `TraceServices::FThreadProvider`  
`class FThreadProvider : public IThreadProvider , public IEditableThreadProvider`  
_L14-56_
- inherits: `IThreadProvider,IEditableThreadProvider`
- L19 _public prototype_ `explicit FThreadProvider(IAnalysisSession& Session);`
- L20 _public prototype_ `virtual ~FThreadProvider();`
- L23 _public prototype_ `virtual void AddThread(uint32 Id, const TCHAR* Name, EThreadPriority Priority) override;` — IEditableThreadProvider
- L24 _public function_ `virtual const IThreadProvider* GetReadProvider() const override`
- L26 _public prototype_ `void AddGameThread(uint32 Id);`
- L27 _public prototype_ `void SetThreadPriority(uint32 Id, EThreadPriority Priority);`
- L28 _public prototype_ `void SetThreadGroup(uint32 Id, const TCHAR* GroupName);`
- L31 _public function_ `virtual uint64 GetModCount() const override` — IThreadProvider
- L32 _public prototype_ `virtual void EnumerateThreads(TFunctionRef<void(const FThreadInfo&)> Callback) const override;`
- L33 _public prototype_ `virtual const TCHAR* GetThreadName(uint32 ThreadId) const override;`
- L48 _private prototype_ `void SortThreads();`
- L49 _private prototype_ `static int32 GetPrioritySortOrder(EThreadPriority ThreadPriority);`
- L50 _private prototype_ `static uint32 GetGroupSortOrder(const TCHAR* GroupName);`
- L52 _private member_ `IAnalysisSession& Session;`
- L53 _private member_ `uint64 ModCount = 0;`
- L54 _private member_ `TMap<uint32, FThreadInfoInternal*> ThreadMap;`
- L55 _private member_ `TArray<FThreadInfoInternal*> SortedThreads;`

#### struct `TraceServices::FThreadProvider::FThreadInfoInternal`  
`struct FThreadInfoInternal`  
_L36-46_
- L38 _public member_ `uint32 Id = 0;`
- L39 _public member_ `const TCHAR* Name = TEXT("Unn`
- L40 _public member_ `uint32 GroupSortOrder = ~0u;`
- L41 _public member_ `int32 PrioritySortOrder = INT_MAX;`
- L42 _public member_ `uint32 FallbackSortOrder = ~0u;`
- L43 _public member_ `const TCHAR* GroupName = nullptr;`
- L45 _public prototype_ `bool operator<(const FThreadInfoInternal& Other) const;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace TraceServices`

### `Source/Developer/TraceServices/Private/Model/TimingProfilerPrivate.h` (Private)


#### struct `TraceServices::FGpuQueueData`  
`struct FGpuQueueData`  
_L16-20_
- L18 _public member_ `TArray<FGpuSignalFence> SignalFenceArray;`
- L19 _public member_ `TArray<FGpuWaitFence> WaitFenceArray;`

#### class `TraceServices::FTimingProfilerProvider`  
`class FTimingProfilerProvider : public ITimingProfilerProvider , public ITimingProfilerTimerReader , public IEditableTimingProfilerProvider`  
_L22-181_
- inherits: `ITimingProfilerProvider,ITimingProfilerTimerReader,IEditableTimingProfilerProvider`
- L28 _public typedef_ `typedef TMonotonicTimeline<FTimingProfilerEvent> TimelineInternal;`
- L30 _public prototype_ `explicit FTimingProfilerProvider(IAnalysisSession& InSession);`
- L31 _public prototype_ `virtual ~FTimingProfilerProvider();`
- L38 _public prototype_ `virtual bool ReadTimeline(uint32 Index, TFunctionRef<void(const Timeline&)> Callback) const override;`
- L39 _public function_ `virtual uint32 GetTimelineCount() const override`
- L40 _public prototype_ `virtual void EnumerateTimelines(TFunctionRef<void(const Timeline&)> Callback) const override;`
- L44 _public prototype_ `virtual void ReadTimers(TFunctionRef<void(const ITimingProfilerTimerReader&)> Callback) const override;`
- L45 _public function_ `virtual const ITimingProfilerTimerReader& GetTimerReader() const override`
- L49 _public prototype_ `virtual uint32 GetOriginalTimerIdFromMetadata(uint32 MetadataTimerId) const override;` — also in ITimingProfilerTimerReader
- L50 _public prototype_ `virtual TArrayView<const uint8> GetMetadata(uint32 MetadataTimerId) const override;` — also in ITimingProfilerTimerReader
- L51 _public prototype_ `virtual const FMetadataSpec* GetMetadataSpec(uint32 MetadataSpecId) const override;`
- L52 _public prototype_ `virtual void MakeTimerDisplayName(const FTimingProfilerTimer& InTimer, TStringBuilder<1024>& InOutDisplayName) const override;`
- L56 _public prototype_ `virtual bool HasGpuTiming() const override;`
- L57 _public prototype_ `virtual bool GetGpuTimelineIndex(uint32& OutTimelineIndex) const override;` — backward compatibility
- L58 _public prototype_ `virtual bool GetGpu2TimelineIndex(uint32& OutTimelineIndex) const override;` — backward compatibility
- L59 _public prototype_ `virtual void EnumerateGpuQueues(TFunctionRef<void(const FGpuQueueInfo&)> Callback) const override;`
- L60 _public prototype_ `virtual bool GetGpuQueueTimelineIndex(uint32 QueueId, uint32& OutTimelineIndex) const override;`
- L61 _public prototype_ `virtual void EnumerateGpuSignalFences(uint32 QueueId, double StartTime, double EndTime, EnumerateGpuSignalFencesCallback Callback) const override;`
- L62 _public prototype_ `virtual void EnumerateGpuWaitFences(uint32 QueueId, double StartTime, double EndTime, EnumerateGpuWaitFencesCallback Callback) const override;`
- L63 _public prototype_ `virtual void EnumerateGpuFences(uint32 QueueId, double StartTime, double EndTime, EnumerateGpuFencesCallback Callback) const override;`
- L64 _public prototype_ `virtual void EnumerateResolvedGpuFences(uint32 QueueId, double StartTime, double EndTime, EnumerateResolvedGpuFencesCallback Callback) const override;`
- L68 _public prototype_ `virtual bool HasVerseTiming() const override;`
- L69 _public prototype_ `virtual bool GetVerseTimelineIndex(uint32& OutTimelineIndex) const override;`
- L73 _public prototype_ `virtual bool HasCpuTiming() const override;`
- L74 _public prototype_ `virtual bool GetCpuThreadTimelineIndex(uint32 ThreadId, uint32& OutTimelineIndex) const override;`
- L78 _public prototype_ `virtual ITable<FTimingProfilerAggregatedStats>* CreateAggregation(const FCreateAggregationParams& Params) const override;`
- L79 _public prototype_ `virtual ITimingProfilerButterfly* CreateButterfly(const FCreateButterflyParams& Params) const override;`
- L83 _public function_ `virtual double GetRatioOfThreadsToUse() const override`
- L88 _public prototype_ `virtual uint32 GetTimerCount() const override;`
- L91 _public prototype_ `virtual const FTimingProfilerTimer* GetTimer(uint32 TimerId) const override;` — The returned FTimingProfilerTimer* is only valid under the current read lock.
- L101 _public prototype_ `virtual uint32 AddTimer(ETimingProfilerTimerType Type) override;`
- L102 _public prototype_ `virtual uint32 AddTimer(ETimingProfilerTimerType Type, FStringView Name) override;`
- L103 _public prototype_ `virtual uint32 AddTimer(ETimingProfilerTimerType Type, FStringView Name, const TCHAR* File, uint32 Line) override;`
- L105 _public prototype_ `virtual void SetTimerName(uint32 TimerId, FStringView Name) override;`
- L106 _public prototype_ `virtual void SetTimerNameAndLocation(uint32 TimerId, FStringView Name, const TCHAR* File, uint32 Line) override;`
- L107 _public prototype_ `virtual void SetTimerLocation(uint32 TimerId, const TCHAR* File, uint32 Line) override;`
- L111 _public prototype_ `virtual uint32 AddMetadata(uint32 OriginalTimerId, TArray<uint8>&& Metadata) override;`
- L112 _public prototype_ `virtual void SetMetadata(uint32 MetadataTimerId, TArray<uint8>&& Metadata) override;`
- L113 _public prototype_ `virtual void SetMetadata(uint32 MetadataTimerId, TArray<uint8>&& Metadata, uint32 NewTimerId) override;`
- L114 _public prototype_ `virtual TArrayView<uint8> GetEditableMetadata(uint32 MetadataTimerId) override;`
- L115 _public prototype_ `virtual uint32 AddMetadataSpec(FMetadataSpec&& Metadata) override;`
- L116 _public prototype_ `virtual void SetMetadataSpec(uint32 TimerId, uint32 MetadataSpecId) override;`
- L120 _public prototype_ `virtual void AddGpuQueue(uint32 QueueId, uint8 GPU, uint8 Index, uint8 Type, const TCHAR* Name) override;`
- L121 _public prototype_ `virtual void AddGpuSignalFence(uint32 QueueId, const FGpuSignalFence& SignalFence) override;`
- L122 _public prototype_ `virtual void AddGpuWaitFence(uint32 QueueId, const FGpuWaitFence& WaitFence) override;`
- L123 _public prototype_ `virtual IEditableTimeline<FTimingProfilerEvent>* GetGpuQueueEditableTimeline(uint32 QueueId) override;`
- L124 _public prototype_ `virtual IEditableTimeline<FTimingProfilerEvent>* GetGpuQueueWorkEditableTimeline(uint32 QueueId) override;`
- L128 _public prototype_ `virtual IEditableTimeline<FTimingProfilerEvent>* GetVerseEditableTimeline() override;`
- L132 _public prototype_ `virtual IEditableTimeline<FTimingProfilerEvent>& GetCpuThreadEditableTimeline(uint32 ThreadId) override;`
- L136 _public function_ `virtual void SetRatioOfThreadsToUse(double InRatioOfThreadsToUse) override`
- L137 _public function_ `virtual const ITimingProfilerProvider* GetReadProvider() const override`
- L141 _public prototype_ `TimelineInternal& EditGpuTimeline();`
- L142 _public prototype_ `TimelineInternal& EditGpu2Timeline();`
- L145 _private prototype_ `FTimingProfilerTimer& AddTimerInternal(ETimingProfilerTimerType TimerType, FStringView Name, const TCHAR* File, uint32 Line);`
- L146 _private prototype_ `ITable<FTimingProfilerAggregatedStats>* CreateAggregationInternal(TArray<const ITimingProfilerTimeline*>& IncludedTimelines, const FCreateAggregationParams& Params) const;`
- L147 _private prototype_ `ITimingProfilerButterfly* CreateButterflyInternal(TArray<const ITimingProfilerTimeline*>& IncludedTimelines, const FCreateButterflyParams& Params) const;`
- L155 _private member_ `IAnalysisSession& Session;`
- L156 _private member_ `TArray<FMetadata> Metadatas;`
- L157 _private member_ `TArray<FMetadataSpec> MetadataSpecs;`
- L158 _private member_ `TMultiMap<uint32, uint32> MetadataSpecMap;` — hash(FMetadataSpec) --> MetadataSpecId (index)
- L159 _private member_ `TArray<FTimingProfilerTimer> Timers;`
- L160 _private member_ `TArray<TSharedRef<TimelineInternal>> Timelines;`
- L161 _private member_ `TTableLayout<FTimingProfilerAggregatedStats> AggregatedStatsTableLayout;`
- L162 _private member_ `double RatioOfThreadsToUse = 0.75;`
- L164 _private member_ `bool bHasData[uint32(ETimingProfilerTimerType::Count)];`
- L168 _private member_ `static const uint32 GpuTimelineIndex = 0;`
- L169 _private member_ `static const uint32 Gpu2TimelineIndex = 1;`
- L170 _private member_ `TArray<FGpuQueueInfo> GpuQueues;`
- L171 _private member_ `TArray<FGpuQueueData> GpuQueueData;`
- L172 _private member_ `TMap<uint32, uint32> GpuQueueIdToQueueIndexMap;` — GPU Queue Id --> queue index, in GpuQueues
- L176 _private member_ `static const uint32 VerseTimelineIndex = 2;`
- L180 _private member_ `TMap<uint32, uint32> CpuThreadTimelineIndexMap;` — CPU Thread Id --> timeline index, in Timelines

#### struct `TraceServices::FTimingProfilerProvider::FMetadata`  
`struct FMetadata`  
_L149-153_
- L151 _public member_ `TArray<uint8> Payload;`
- L152 _public member_ `uint32 TimerId;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace TraceServices`

### `Source/Developer/TraceServices/Private/ModuleServicePrivate.h` (Private)


#### class `TraceServices::FModuleService`  
`class FModuleService : public IModuleService`  
_L16-40_
- inherits: `IModuleService`
- L20 _public prototype_ `FModuleService();`
- L22 _public prototype_ `virtual void GetAvailableModules(TArray<FModuleInfo>& OutModules) override;`
- L23 _public prototype_ `virtual void GetAvailableModulesEx(TArray<FModuleInfoEx>& OutModules) override;`
- L24 _public prototype_ `virtual void GetEnabledModules(TArray<FModuleInfo>& OutModules) override;`
- L25 _public prototype_ `virtual void SetModuleEnabled(const FName& ModuleName, bool bEnabled) override;`
- L26 _public prototype_ `virtual void GenerateReports(const IAnalysisSession& Session, const TCHAR* CmdLine, const TCHAR* OutputDirectory) override;`
- L28 _public prototype_ `void OnAnalysisBegin(IAnalysisSession& Session);`
- L30 _public prototype_ `TArray<const TCHAR*> GetModuleLoggers(const FName& ModuleName);`
- L33 _private prototype_ `void Initialize();`
- L34 _private prototype_ `TSet<FName> GetEnabledModulesFromCommandLine(const TCHAR* CommandLine);`
- L36 _private member_ `mutable FCriticalSection CriticalSection;`
- L37 _private member_ `bool bIsInitialized = false;`
- L38 _private member_ `TSet<IModule*> EnabledModules;`
- L39 _private member_ `TMap<FName, IModule*> ModulesMap;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace TraceServices`

### `Source/Developer/TraceServices/Private/Modules/CookProfilerModule.h` (Private)


#### class `TraceServices::FCookProfilerModule`  
`class FCookProfilerModule : public IModule`  
_L10-20_
- inherits: `IModule`
- L14 _public prototype_ `virtual void GetModuleInfo(FModuleInfo& OutModuleInfo) override;`
- L16 _public function_ `virtual bool ShouldBeEnabledByDefault() const override`
- L18 _public prototype_ `virtual void GetLoggers(TArray<const TCHAR*>& OutLoggers) override;`
- L19 _public prototype_ `virtual void OnAnalysisBegin(IAnalysisSession& Session) override;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace TraceServices`

### `Source/Developer/TraceServices/Private/Modules/CountersModule.h` (Private)


#### class `TraceServices::FCountersModule`  
`class FCountersModule : public IModule`  
_L10-18_
- inherits: `IModule`
- L14 _public prototype_ `virtual void GetModuleInfo(FModuleInfo& OutModuleInfo) override;`
- L15 _public prototype_ `virtual void GetLoggers(TArray<const TCHAR*>& OutLoggers) override;`
- L16 _public prototype_ `virtual void OnAnalysisBegin(IAnalysisSession& Session) override;`
- L17 _public function_ `virtual void GenerateReports(const IAnalysisSession& Session, const TCHAR* CmdLine, const TCHAR* OutputDirectory) override`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace TraceServices`

### `Source/Developer/TraceServices/Private/Modules/CsvProfilerModule.h` (Private)


#### class `TraceServices::FCsvProfilerModule`  
`class FCsvProfilerModule : public IModule`  
_L10-17_
- inherits: `IModule`
- L14 _public prototype_ `virtual void GetModuleInfo(FModuleInfo& OutModuleInfo) override;`
- L15 _public prototype_ `virtual void OnAnalysisBegin(IAnalysisSession& Session) override;`
- L16 _public prototype_ `virtual void GenerateReports(const IAnalysisSession& Session, const TCHAR* CmdLine, const TCHAR* OutputDirectory) override;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace TraceServices`

### `Source/Developer/TraceServices/Private/Modules/DiagnosticsModule.h` (Private)


#### class `TraceServices::FDiagnosticsModule`  
`class FDiagnosticsModule : public IModule`  
_L10-17_
- inherits: `IModule`
- L14 _public prototype_ `virtual void GetModuleInfo(FModuleInfo& OutModuleInfo) override;`
- L15 _public prototype_ `virtual void GetLoggers(TArray<const TCHAR*>& OutLoggers) override;`
- L16 _public prototype_ `virtual void OnAnalysisBegin(IAnalysisSession& Session) override;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace TraceServices`

### `Source/Developer/TraceServices/Private/Modules/LoadTimeProfilerModule.h` (Private)


#### class `TraceServices::FLoadTimeProfilerModule`  
`class FLoadTimeProfilerModule : public IModule`  
_L10-21_
- inherits: `IModule`
- L14 _public prototype_ `virtual void GetModuleInfo(FModuleInfo& OutModuleInfo) override;`
- L16 _public function_ `virtual bool ShouldBeEnabledByDefault() const override`
- L18 _public prototype_ `virtual void GetLoggers(TArray<const TCHAR*>& OutLoggers) override;`
- L19 _public prototype_ `virtual void OnAnalysisBegin(IAnalysisSession& Session) override;`
- L20 _public prototype_ `virtual void GenerateReports(const IAnalysisSession& Session, const TCHAR* CmdLine, const TCHAR* OutputDirectory) override;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace TraceServices`

### `Source/Developer/TraceServices/Private/Modules/MemoryModule.h` (Private)


#### class `TraceServices::FMemoryModule`  
`class FMemoryModule : public IModule`  
_L10-17_
- inherits: `IModule`
- L14 _public prototype_ `virtual void GetModuleInfo(FModuleInfo& OutModuleInfo) override;`
- L15 _public prototype_ `virtual void GetLoggers(TArray<const TCHAR*>& OutLoggers) override;`
- L16 _public prototype_ `virtual void OnAnalysisBegin(IAnalysisSession& Session) override;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace TraceServices`

### `Source/Developer/TraceServices/Private/Modules/NetProfilerModule.h` (Private)


#### class `TraceServices::FNetProfilerModule`  
`class FNetProfilerModule : public IModule`  
_L10-16_
- inherits: `IModule`
- L14 _public prototype_ `virtual void GetModuleInfo(FModuleInfo& OutModuleInfo) override;`
- L15 _public prototype_ `virtual void OnAnalysisBegin(IAnalysisSession& Session) override;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace TraceServices`

### `Source/Developer/TraceServices/Private/Modules/ObjectModule.h` (Private)


#### class `TraceServices::FObjectModule`  
`class FObjectModule : public IModule`  
_L10-15_
- inherits: `IModule`
- L13 _public prototype_ `virtual void GetModuleInfo(FModuleInfo& OutModuleInfo) override;`
- L14 _public prototype_ `virtual void OnAnalysisBegin(IAnalysisSession& Session) override;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace TraceServices`

### `Source/Developer/TraceServices/Private/Modules/PlatformEventsModule.h` (Private)


#### class `TraceServices::FPlatformEventsModule`  
`class FPlatformEventsModule : public IModule`  
_L10-16_
- inherits: `IModule`
- L14 _public prototype_ `virtual void GetModuleInfo(FModuleInfo& OutModuleInfo) override;`
- L15 _public prototype_ `virtual void OnAnalysisBegin(IAnalysisSession& Session) override;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace TraceServices`

### `Source/Developer/TraceServices/Private/Modules/StatsModule.h` (Private)


#### class `TraceServices::FStatsModule`  
`class FStatsModule : public IModule`  
_L10-16_
- inherits: `IModule`
- L14 _public prototype_ `virtual void GetModuleInfo(FModuleInfo& OutModuleInfo) override;`
- L15 _public prototype_ `virtual void OnAnalysisBegin(IAnalysisSession& Session) override;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace TraceServices`

### `Source/Developer/TraceServices/Private/Modules/TasksModule.h` (Private)


#### class `TraceServices::FTasksModule`  
`class FTasksModule : public IModule`  
_L10-19_
- inherits: `IModule`
- L14 _public prototype_ `virtual void GetModuleInfo(FModuleInfo& OutModuleInfo) override;`
- L16 _public function_ `virtual bool ShouldBeEnabledByDefault() const override`
- L18 _public prototype_ `virtual void OnAnalysisBegin(IAnalysisSession& Session) override;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace TraceServices`

### `Source/Developer/TraceServices/Private/Modules/TimingProfilerModule.h` (Private)


#### class `TraceServices::FTimingProfilerModule`  
`class FTimingProfilerModule : public IModule`  
_L10-17_
- inherits: `IModule`
- L14 _public prototype_ `virtual void GetModuleInfo(FModuleInfo& OutModuleInfo) override;`
- L15 _public prototype_ `virtual void GetLoggers(TArray<const TCHAR*>& OutLoggers) override;`
- L16 _public prototype_ `virtual void OnAnalysisBegin(IAnalysisSession& Session) override;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace TraceServices`

### `Source/Developer/TraceServices/Public/Common/CachedPagedArray.h` (Public)


#### class `TraceServices::TCachedPagedArray`  
`template<typename InItemType, unsigned int PageSize> class TCachedPagedArray`  
_L32-151_
- desc: A typed paged array allowing persistent storage of the data. User defines page size (in number of elements) which defines the size of the page. The page is then mapped to a number of cache blocks. The blocks are always loaded into a coherent buffer. +-------------------------------------------------------------------+ |  Page                                                             | +-------------------------------------------------------------------+ |                   |                    |                  | |                   |                    |                  | v                   v                    v                  v +------------------------------------------------------------------------------+ |     Block n       |     Block n+1      |     Block n+2    |     Block n+3    | +------------------------------------------------------------------------------+ Depending on the page size there could be some blocks that are only partially used. The container supports unloading pages for extremely large datasets by defining the number of resident pages. Once the limit is reached pages are unloaded. Pages are lazily loaded on access.
- L35 _public typedef_ `typedef InItemType ItemType;`
- L37 _public function_ `TCachedPagedArray(const TCHAR* InCacheId, IAnalysisCache& InCache, uint32 InResidentPages = ~0) : Cache(InCache) , CacheId(0) , ResidentPageCount(InResidentPages) , ElementCount(nullptr)`
- L61 _public function_ `template <typename... ArgsType> ItemType& EmplaceBack(ArgsType&&... Args)`
- L72 _public function_ `ItemType& operator[](uint64 Index)`
- L85 _public function_ `uint32 NumPages() const`
- L90 _public function_ `uint64 Num() const`
- L96 _private member_ `constexpr static uint32 PageSizeBytes = sizeof(ItemType) * PageSize;`
- L97 _private member_ `constexpr static uint32 BlocksPerPage = (PageSizeBytes + IAnalysisCache::BlockSizeBytes - 1) / IAnalysisCache::BlockSizeBytes;`
- L98 _private member_ `constexpr static uint32 WastePerPage = (BlocksPerPage * IAnalysisCache::BlockSizeBytes) - PageSizeBytes;`
- L100 _private function_ `inline ItemType* GetPageForNextItem()`
- L111 _private function_ `void GetItemsFromPage(uint64 PageIndex, ItemType** OutFirstItem, ItemType** OutLastItem) const`
- L119 _private function_ `ItemType* GetPage(uint32 InPageIndex)`
- L132 _private function_ `void EvictPages()`
- L145 _private member_ `IAnalysisCache& Cache;`
- L146 _private member_ `TArray<ItemType*> Pages;`
- L147 _private member_ `TArray<FSharedBuffer> ResidentPages;`
- L148 _private member_ `uint32 CacheId;`
- L149 _private member_ `uint32 ResidentPageCount;`
- L150 _private member_ `uint64* ElementCount;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace TraceServices`

### `Source/Developer/TraceServices/Public/Common/CachedStringStore.h` (Public)


#### class `TraceServices::TCachedStringStore`  
`template<typename CharType> class TCachedStringStore`  
_L19-228_
- desc: A deduplicating persistent string store. Allows users to store a string in a session and retrieve it at a given offset in consecutive sessions. The store uses analysis cache to store the strings. The store is not thread safe.
- L22 _public typedef_ `typedef TStringView<CharType> StringViewType;`
- L29 _public function_ `TCachedStringStore(const TCHAR* InCacheIdentifier, IAnalysisCache& InCache) : Cache(InCache) , CacheIndex(0)` — Create a persistent string store. @param InCacheIdentifier A unique string identifying this store. @param InCache Cache to use
- L76 _public function_ `~TCachedStringStore()`
- L86 _public function_ `const CharType* GetStringAtOffset(uint64 OffsetBytes) const` — Resolve an offset to a c string. @param OffsetBytes Offset in bytes @return The string at the offset or null if the offset was invalid.
- L103 _public function_ `uint64 GetOffsetOfString(const TCHAR* String) const` — Gets the offset of a string previously stored string. @param String A string that was stored @return Offset in bytes to the string, or ~0 if the string was not found in the store.
- L124 _public function_ `uint64 Store_GetOffset(const CharType* String)` — Store a string, get offset back. @param String String to store @return Offset in bytes
- L134 _public function_ `uint64 Store_GetOffset(const StringViewType String)` — Store a string, get offset back. @param String String to store @return Offset in bytes
- L144 _public function_ `const CharType* Store_GetString(const CharType* String)` — Store a string, get string back. @param String String to store @return Stored string
- L154 _public function_ `const CharType* Store_GetString(const StringViewType String)` — Store a string, get string back. @param String String to store @return Stored string
- L163 _public function_ `uint32 Num() const` — Get the number of unique stored string. @return Number of strings
- L172 _public function_ `uint64 AllocatedSize()` — Get the total number of bytes used. Note that this does ot account for unused block space. @return Number of bytes used to store the strings.
- L179 _private function_ `const TTuple<uint64, const CharType*>& StoreInternal(const StringViewType& String)`
- L220 _private member_ `constexpr static uint32 BlockSize = IAnalysisCache::BlockSizeBytes;`
- L222 _private member_ `IAnalysisCache& Cache;`
- L223 _private member_ `uint32 CacheIndex;`
- L224 _private member_ `TMap<uint32, TTuple<uint64,const CharType*>> StoredStrings;`
- L225 _private member_ `TArray<FSharedBuffer> Blocks;`
- L226 _private member_ `CharType* BufferCursor;`
- L227 _private member_ `FPersistentState* State;`

#### struct `TraceServices::TCachedStringStore::FPersistentState`  
`struct FPersistentState`  
_L214-218_
- L216 _public member_ `uint32 BlockCount;`
- L217 _public member_ `uint32 BufferLeftBytes;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace TraceServices`
- L230 _typedef_ `typedef TCachedStringStore<WIDECHAR> FCachedStringStore;` (scope `TraceServices`)
- L231 _typedef_ `typedef TCachedStringStore<ANSICHAR> FCachedStringStoreAnsi;` (scope `TraceServices`)

### `Source/Developer/TraceServices/Public/Common/PagedArray.h` (Public)


#### struct `TraceServices::TPagedArrayPage`  
`template<typename ItemType> struct TPagedArrayPage`  
_L25-29_
- L27 _public member_ `ItemType* Items = nullptr;`
- L28 _public member_ `uint64 Count = 0;`

#### class `TraceServices::TPagedArrayIterator`  
`template<typename ItemType, typename PageType> class TPagedArrayIterator`  
_L68-381_
- L71 _public function_ `TPagedArrayIterator()`
- L75 _public function_ `TPagedArrayIterator(const TPagedArray<ItemType, PageType>& InOuter, uint64 InItemIndex) : Outer(&InOuter)`
- L90 _public function_ `uint64 GetCurrentPageIndex() const`
- L95 _public function_ `const PageType* GetCurrentPage() const`
- L100 _public function_ `const PageType* SetCurrentPage(uint64 PageIndex)`
- L129 _public function_ `const PageType* PrevPage()`
- L149 _public function_ `const PageType* NextPage()`
- L172 _public function_ `uint64 GetCurrentItemIndex() const`
- L177 _public function_ `const ItemType* GetCurrentItem() const`
- L182 _public function_ `const ItemType* SetPosition(uint64 InItemIndex)`
- L190 _public function_ `const ItemType* PrevItem()`
- L210 _public function_ `const ItemType* NextItem()`
- L233 _public function_ `const ItemType& operator*() const`
- L238 _public function_ `const ItemType* operator->() const`
- L243 _public function_ `explicit operator bool() const`
- L248 _public function_ `TPagedArrayIterator& operator++()`
- L254 _public function_ `TPagedArrayIterator operator++(int)`
- L261 _public function_ `TPagedArrayIterator& operator--()`
- L267 _public function_ `TPagedArrayIterator operator--(int)`
- L275 _private function_ `void OnCurrentPageChanged()`
- L289 _private function_ `void SetPositionInternal(uint64 InItemIndex)`
- L320 _private function_ `void DebugCheckState()`
- L371 _private member_ `const TPagedArray<ItemType, PageType>* Outer = nullptr;`
- L372 _private member_ `uint64 CurrentPageIndex = 0;`
- L373 _private member_ `const ItemType* CurrentPageFirstItem = nullptr;`
- L374 _private member_ `const ItemType* CurrentPageLastItem = nullptr;`
- L375 _private member_ `uint64 CurrentItemIndex = 0;`
- L376 _private member_ `const ItemType* CurrentItem = nullptr;`
- L378 _private member_ `uint64 TotalPageCount = 0;`
- L379 _private member_ `uint64 TotalItemCount = 0;`
- L393 _public function_ `TPagedArrayIterator(const TPagedArray<ItemType, PageType>& InOuter, uint64 InItemIndex) : Outer(&InOuter) , CurrentItemIndex(InItemIndex)`
- L462 _public function_ `const ItemType* SetPosition(uint64 Index)`

#### class `TraceServices::TPagedArrayIterator`  
`template<typename ItemType, typename PageType> class TPagedArrayIterator`  
_L386-548_
- L71 _public function_ `TPagedArrayIterator()`
- L75 _public function_ `TPagedArrayIterator(const TPagedArray<ItemType, PageType>& InOuter, uint64 InItemIndex) : Outer(&InOuter)`
- L90 _public function_ `uint64 GetCurrentPageIndex() const`
- L95 _public function_ `const PageType* GetCurrentPage() const`
- L100 _public function_ `const PageType* SetCurrentPage(uint64 PageIndex)`
- L129 _public function_ `const PageType* PrevPage()`
- L149 _public function_ `const PageType* NextPage()`
- L172 _public function_ `uint64 GetCurrentItemIndex() const`
- L177 _public function_ `const ItemType* GetCurrentItem() const`
- L182 _public function_ `const ItemType* SetPosition(uint64 InItemIndex)`
- L190 _public function_ `const ItemType* PrevItem()`
- L210 _public function_ `const ItemType* NextItem()`
- L233 _public function_ `const ItemType& operator*() const`
- L238 _public function_ `const ItemType* operator->() const`
- L243 _public function_ `explicit operator bool() const`
- L248 _public function_ `TPagedArrayIterator& operator++()`
- L254 _public function_ `TPagedArrayIterator operator++(int)`
- L261 _public function_ `TPagedArrayIterator& operator--()`
- L267 _public function_ `TPagedArrayIterator operator--(int)`
- L275 _private function_ `void OnCurrentPageChanged()`
- L289 _private function_ `void SetPositionInternal(uint64 InItemIndex)`
- L320 _private function_ `void DebugCheckState()`
- L371 _private member_ `const TPagedArray<ItemType, PageType>* Outer = nullptr;`
- L372 _private member_ `uint64 CurrentPageIndex = 0;`
- L373 _private member_ `const ItemType* CurrentPageFirstItem = nullptr;`
- L374 _private member_ `const ItemType* CurrentPageLastItem = nullptr;`
- L375 _private member_ `uint64 CurrentItemIndex = 0;`
- L376 _private member_ `const ItemType* CurrentItem = nullptr;`
- L378 _private member_ `uint64 TotalPageCount = 0;`
- L379 _private member_ `uint64 TotalItemCount = 0;`
- L393 _public function_ `TPagedArrayIterator(const TPagedArray<ItemType, PageType>& InOuter, uint64 InItemIndex) : Outer(&InOuter) , CurrentItemIndex(InItemIndex)`
- L462 _public function_ `const ItemType* SetPosition(uint64 Index)`

#### class `TraceServices::TPagedArray`  
`template<typename InItemType, typename InPageType = TPagedArrayPage<InItemType>> class TPagedArray`  
_L553-751_
- L556 _public typedef_ `typedef InItemType ItemType;`
- L557 _public typedef_ `typedef InPageType PageType;`
- L558 _public typedef_ `typedef TPagedArrayIterator<InItemType, InPageType> TIterator;`
- L560 _public function_ `TPagedArray(ILinearAllocator& InAllocator, uint64 InPageSize) : Allocator(InAllocator) , PageSize(InPageSize)`
- L567 _public function_ `~TPagedArray()`
- L579 _public function_ `uint64 Num() const`
- L584 _public function_ `uint64 GetPageSize() const`
- L589 _public function_ `uint64 NumPages() const`
- L594 _public function_ `ItemType& PushBack()`
- L610 _public function_ `template <typename... ArgsType> ItemType& EmplaceBack(ArgsType&&... Args)`
- L625 _public function_ `ItemType& Insert(uint64 Index)`
- L646 _public function_ `PageType* GetLastPage()`
- L651 _public function_ `const PageType* GetLastPage() const`
- L656 _public function_ `PageType* GetPage(uint64 PageIndex)`
- L661 _public function_ `const PageType* GetPage(uint64 PageIndex) const`
- L666 _public function_ `PageType* GetItemPage(uint64 ItemIndex)`
- L672 _public function_ `const PageType* GetItemPage(uint64 ItemIndex) const`
- L678 _public function_ `TIterator GetIterator() const`
- L683 _public function_ `TIterator GetIteratorFromPage(uint64 PageIndex) const`
- L688 _public function_ `TIterator GetIteratorFromItem(uint64 ItemIndex) const`
- L693 _public function_ `const PageType* GetPages() const`
- L698 _public function_ `ItemType& operator[](uint64 Index)`
- L707 _public function_ `const ItemType& operator[](uint64 Index) const`
- L712 _public function_ `ItemType& First()`
- L718 _public function_ `const ItemType& First() const`
- L724 _public function_ `ItemType& Last()`
- L730 _public function_ `const ItemType& Last() const`
- L736 _public function_ `FORCEINLINE TIterator begin()`
- L737 _public function_ `FORCEINLINE TIterator begin() const`
- L738 _public function_ `FORCEINLINE TIterator end()`
- L739 _public function_ `FORCEINLINE TIterator end() const`
- L745 _private member_ `ILinearAllocator& Allocator;`
- L746 _private member_ `TArray<PageType> PagesArray;`
- L747 _private member_ `PageType* FirstPage = nullptr;`
- L748 _private member_ `PageType* LastPage = nullptr;`
- L749 _private member_ `uint64 PageSize;`
- L750 _private member_ `uint64 TotalItemCount = 0;`

#### Free symbols / members of external scopes

- L15 _macro_ `#define TRACESERVICES_PAGED_ARRAY_ITERATOR_V2 0 // enables a simpler implementation of TPagedArrayIterator, for debug purposes`
- L19 _macro_ `#define TRACESERVICES_PAGED_ARRAY_ITERATOR_DEBUG_ENABLED 0`
- L22 _namespace_ `namespace TraceServices`
- L32 _function_ `template<typename ItemType> inline const ItemType* GetData(const TPagedArrayPage<ItemType>& Page)` (scope `TraceServices`)
- L38 _function_ `template<typename ItemType> inline SIZE_T GetNum(const TPagedArrayPage<ItemType>& Page)` (scope `TraceServices`)
- L44 _function_ `template<typename ItemType> inline const ItemType* GetFirstItem(const TPagedArrayPage<ItemType>& Page)` (scope `TraceServices`)
- L50 _function_ `template<typename ItemType> inline const ItemType* GetLastItem(const TPagedArrayPage<ItemType>& Page)` (scope `TraceServices`)
- L313 _function_ `FORCEINLINE friend bool operator!=(const TPagedArrayIterator& Lhs, const TPagedArrayIterator& Rhs)` (scope `TraceServices`)
- L754 _function_ `template<typename ItemType, typename PageType> inline const PageType* GetData(const TPagedArray<ItemType, PageType>& PagedArray)` (scope `TraceServices`)
- L760 _function_ `template<typename ItemType, typename PageType> inline SIZE_T GetNum(const TPagedArray<ItemType, PageType>& PagedArray)` (scope `TraceServices`)
- L773 _function_ `template<typename ItemType, typename PageType> FInt32Interval GetElementRangeOverlappingGivenRange(const TPagedArray<ItemType, PageType>& PagedArray, double StartTime, double EndTime, TFunctionRef<double(const ItemType&)> ItemStartProjection, TFunctionRef<double(const ItemType&)> ItemEndProjection )` (scope `TraceServices`) — Use binary search to find the first and last element inside a TPagedArray that overlaps a given input interval. This requires the elements in the array to be sorted by the value returned from the Projection. Example usage for Timeline events would require a projection that returns Item.StartTime and the resulting range.Min will point to the last element where Item.End > StartTime and range.Max to the last element where Item.StartTime < EndTime.
- L801 _function_ `int32 StartPageIndex = Algo::UpperBoundBy(Pages, StartTime, [&ItemEndProjection](const PageType& Page) { return ItemEndProjection(Page.Items[0]); });` (scope `TraceServices::GetElementRangeOverlappingGivenRange`) — find the page before the first page that's already inside the range (thus -1)
- L830 _function_ `int32 EndPageIndex = Algo::UpperBoundBy(RemainingPages, EndTime, [&ItemStartProjection](const PageType& Page) { return ItemStartProjection(Page.Items[0]); });` (scope `TraceServices::GetElementRangeOverlappingGivenRange`)
- L859 _namespace_ `namespace PagedArrayAlgoImpl` (scope `TraceServices`)
- L878 _function_ `int32 PageIndex = Algo::LowerBoundBy(Pages, Value, [&Projection](const PageType& Page) { return Invoke(Projection, Page.Items[0]); }, SortPredicate);` (scope `TraceServices::PagedArrayAlgoImpl`) — Find the first page with projected value of the first item >= searched Value.
- L919 _function_ `int32 PageIndex = Algo::UpperBoundBy(Pages, Value, [&Projection](const PageType& Page) { return Invoke(Projection, Page.Items[0]); }, SortPredicate);` (scope `TraceServices::PagedArrayAlgoImpl`) — Find the first page with projected value of the first item > searched Value.
- L965 _function_ `int32 StartPageIndex = Algo::LowerBoundBy(Pages, Value, [&Projection](const PageType& Page) { return Invoke(Projection, Page.Items[0]); }, SortPredicate);` (scope `TraceServices::PagedArrayAlgoImpl`)
- L998 _namespace_ `namespace PagedArrayAlgo` (scope `TraceServices`)
- L1011 _function_ `template <typename ItemType, typename PageType, typename SortPredicateType> FORCEINLINE auto LowerBound(const TPagedArray<ItemType, PageType>& PagedArray, const ItemType& Value, SortPredicateType SortPredicate) -> decltype(GetNum(PagedArray))` (scope `TraceServices::PagedArrayAlgo`) — Performs binary search, resulting in position of the first element >= Value. @param PagedArray The paged array to search through; must be already sorted by SortPredicate. @param Value The value to look for @param SortPredicate Predicate for sort comparison; defaults to <. @returns Position of the first element >= Value; may be == Num.
- L1013 _typedef_ `using SizeType = decltype(GetNum(PagedArray));` (scope `TraceServices::PagedArrayAlgo::LowerBound`)
- L1017 _function_ `template <typename ItemType, typename PageType> FORCEINLINE auto LowerBound(const TPagedArray<ItemType, PageType>& PagedArray, const ItemType& Value) -> decltype(GetNum(PagedArray))` (scope `TraceServices::PagedArrayAlgo`)
- L1034 _function_ `template <typename ItemType, typename PageType, typename ValueType, typename ProjectionType, typename SortPredicateType> FORCEINLINE auto LowerBoundBy(const TPagedArray<ItemType, PageType>& PagedArray, const ValueType& Value, ProjectionType Projection, SortPredicateType SortPredicate) -> decltype(GetNum(PagedArray))` (scope `TraceServices::PagedArrayAlgo`) — Performs binary search, resulting in position of the first element with projected value >= Value. @param PagedArray The paged array to search through, must be already sorted by SortPredicate. @param Value The value to look for @param Projection Functor or data member pointer; called via Invoke to compare to Value. @param SortPredicate Predicate for sort comparison; defaults to <. @returns Position of the first element with projected value >= Value; may be == Num.
- L1036 _typedef_ `using SizeType = decltype(GetNum(PagedArray));` (scope `TraceServices::PagedArrayAlgo::LowerBoundBy`)
- L1040 _function_ `template <typename ItemType, typename PageType, typename ValueType, typename ProjectionType> FORCEINLINE auto LowerBoundBy(const TPagedArray<ItemType, PageType>& PagedArray, const ValueType& Value, ProjectionType Projection) -> decltype(GetNum(PagedArray))` (scope `TraceServices::PagedArrayAlgo`)
- L1056 _function_ `template <typename ItemType, typename PageType, typename SortPredicateType> FORCEINLINE auto UpperBound(const TPagedArray<ItemType, PageType>& PagedArray, const ItemType& Value, SortPredicateType SortPredicate) -> decltype(GetNum(PagedArray))` (scope `TraceServices::PagedArrayAlgo`) — Performs binary search, resulting in position of the first element > Value. @param PagedArray The paged array to search through, must be already sorted by SortPredicate. @param Value The value to look for @param SortPredicate Predicate for sort comparison; defaults to <. @returns Position of the first element > Value; may be == Num.
- L1058 _typedef_ `using SizeType = decltype(GetNum(PagedArray));` (scope `TraceServices::PagedArrayAlgo::UpperBound`)
- L1062 _function_ `template <typename ItemType, typename PageType> FORCEINLINE auto UpperBound(const TPagedArray<ItemType, PageType>& PagedArray, const ItemType& Value) -> decltype(GetNum(PagedArray))` (scope `TraceServices::PagedArrayAlgo`)
- L1079 _function_ `template <typename ItemType, typename PageType, typename ValueType, typename ProjectionType, typename SortPredicateType> FORCEINLINE auto UpperBoundBy(const TPagedArray<ItemType, PageType>& PagedArray, const ValueType& Value, ProjectionType Projection, SortPredicateType SortPredicate) -> decltype(GetNum(PagedArray))` (scope `TraceServices::PagedArrayAlgo`) — Performs binary search, resulting in position of the first element with projected value > Value. @param PagedArray The paged array to search through, must be already sorted by SortPredicate. @param Value The value to look for @param Projection Functor or data member pointer; called via Invoke to compare to Value. @param SortPredicate Predicate for sort comparison; defaults to <. @returns Position of the first element with projected value > Value; may be == Num.
- L1081 _typedef_ `using SizeType = decltype(GetNum(PagedArray));` (scope `TraceServices::PagedArrayAlgo::UpperBoundBy`)
- L1085 _function_ `template <typename ItemType, typename PageType, typename ValueType, typename ProjectionType> FORCEINLINE auto UpperBoundBy(const TPagedArray<ItemType, PageType>& PagedArray, const ValueType& Value, ProjectionType Projection) -> decltype(GetNum(PagedArray))` (scope `TraceServices::PagedArrayAlgo`)
- L1101 _function_ `template <typename ItemType, typename PageType, typename SortPredicateType> FORCEINLINE auto BinarySearchClosest(const TPagedArray<ItemType, PageType>& PagedArray, const ItemType& Value, SortPredicateType SortPredicate) -> decltype(GetNum(PagedArray))` (scope `TraceServices::PagedArrayAlgo`) — Performs binary search, resulting in position of the first element closest to Value. @param PagedArray The paged array to search through; must be already sorted by SortPredicate. @param Value The value to look for @param SortPredicate The predicate for sort comparison; defaults to <. @returns The position of the first element closest to Value; == 0 if Num == 0, otherwise is a value in range [0 .. Num-1].
- L1103 _typedef_ `using SizeType = decltype(GetNum(PagedArray));` (scope `TraceServices::PagedArrayAlgo::BinarySearchClosest`)
- L1107 _function_ `template <typename ItemType, typename PageType> FORCEINLINE auto BinarySearchClosest(const TPagedArray<ItemType, PageType>& PagedArray, const ItemType& Value) -> decltype(GetNum(PagedArray))` (scope `TraceServices::PagedArrayAlgo`)
- L1124 _function_ `template <typename ItemType, typename PageType, typename ValueType, typename ProjectionType, typename SortPredicateType> FORCEINLINE auto BinarySearchClosestBy(const TPagedArray<ItemType, PageType>& PagedArray, const ValueType& Value, ProjectionType Projection, SortPredicateType SortPredicate) -> decltype(GetNum(PagedArray))` (scope `TraceServices::PagedArrayAlgo`) — Performs binary search, resulting in position of the first element with projected value closest to Value. @param PagedArray The paged array to search through; must be already sorted by SortPredicate. @param Value The value to look for @param Projection The functor or data member pointer; called via Invoke to compare to Value. @param SortPredicate The predicate for sort comparison; defaults to <. @returns The position of the first element with projected value closest to Value; == 0 if Num == 0, otherwise is a value in range [0 .. Num-1].
- L1126 _typedef_ `using SizeType = decltype(GetNum(PagedArray));` (scope `TraceServices::PagedArrayAlgo::BinarySearchClosestBy`)
- L1130 _function_ `template <typename ItemType, typename PageType, typename ValueType, typename ProjectionType> FORCEINLINE auto BinarySearchClosestBy(const TPagedArray<ItemType, PageType>& PagedArray, const ValueType& Value, ProjectionType Projection) -> decltype(GetNum(PagedArray))` (scope `TraceServices::PagedArrayAlgo`)

### `Source/Developer/TraceServices/Public/Common/ProviderLock.h` (Public)


#### struct `TraceServices::FProviderEditScopeLock`  
`struct FProviderEditScopeLock`  
_L12-26_
- L14 _public function_ `FProviderEditScopeLock(const IEditableProvider& InProvider) : Provider(InProvider)`
- L20 _public function_ `~FProviderEditScopeLock()`
- L25 _public member_ `const IEditableProvider& Provider;`

#### struct `TraceServices::FProviderReadScopeLock`  
`struct FProviderReadScopeLock`  
_L28-42_
- L30 _public function_ `FProviderReadScopeLock(const IProvider& InProvider) : Provider(InProvider)`
- L36 _public function_ `~FProviderReadScopeLock()`
- L41 _public member_ `const IProvider& Provider;`

#### class `TraceServices::FProviderLock`  
`class FProviderLock`  
_L51-73_
- desc: Utility class to implement the read/write lock for a provider. Example usage: extern thread_local FProviderLock::FThreadLocalState MyProviderLockState; virtual void EditAccessCheck() const override.{ Lock.WriteAccessCheck(MyProviderLockState); } FProviderLock Lock;
- L62 _public prototype_ `void ReadAccessCheck(FThreadLocalState& State) const;`
- L63 _public prototype_ `void WriteAccessCheck(FThreadLocalState& State) const;`
- L65 _public prototype_ `void BeginRead(FThreadLocalState& State);`
- L66 _public prototype_ `void EndRead(FThreadLocalState& State);`
- L68 _public prototype_ `void BeginWrite(FThreadLocalState& State);`
- L69 _public prototype_ `void EndWrite(FThreadLocalState& State);`
- L72 _private member_ `FRWLock RWLock;`

#### struct `TraceServices::FProviderLock::FThreadLocalState`  
`struct FThreadLocalState`  
_L54-59_
- L56 _public member_ `FProviderLock* Lock;`
- L57 _public member_ `int32 ReadLockCount;`
- L58 _public member_ `int32 WriteLockCount;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace TraceServices`

### `Source/Developer/TraceServices/Public/Common/VariablePagedArray.h` (Public)


#### struct `TraceServices::TVariablePagedArrayPage`  
`template<typename ItemType> struct TVariablePagedArrayPage`  
_L60-65_
- L62 _public member_ `ItemType* Items = nullptr;`
- L63 _public member_ `uint64 ItemOffset = 0;`
- L64 _public member_ `uint64 ItemCount = 0;`

#### struct `TraceServices::TVariablePagedArrayPageGroup`  
`template<typename ItemType> struct TVariablePagedArrayPageGroup`  
_L103-109_
- L105 _public member_ `uint64 FirstItemIndex = 0;`
- L106 _public member_ `uint64 ItemCount = 0;`
- L107 _public member_ `uint64 FirstPageIndex = 0;`
- L108 _public member_ `uint64 PageCount = 0;`

#### class `TraceServices::TVariablePagedArrayIterator`  
`template<typename ItemType> class TVariablePagedArrayIterator`  
_L117-334_
- L120 _public typedef_ `typedef TVariablePagedArrayPage<ItemType> PageType;`
- L121 _public typedef_ `typedef TVariablePagedArrayPageGroup<ItemType> PageGroupType;`
- L122 _public typedef_ `typedef TVariablePagedArray<ItemType> ArrayType;`
- L125 _public function_ `TVariablePagedArrayIterator(const ArrayType& InOuter) : Outer(&InOuter)`
- L134 _public function_ `TVariablePagedArrayIterator(const ArrayType& InOuter, const uint64 ItemIndex) : Outer(&InOuter)`
- L157 _public function_ `const PageType* GetCurrentPage()`
- L162 _public function_ `const ItemType* GetCurrentItem()`
- L167 _public function_ `const uint64 GetCurrentItemIndex()`
- L172 _public function_ `const ItemType& operator*() const`
- L177 _public function_ `const ItemType* operator->() const`
- L182 _public function_ `explicit operator bool() const`
- L187 _public function_ `const PageType* PrevPage()`
- L207 _public function_ `const PageType* NextPage()`
- L227 _public function_ `const ItemType* PrevItem()`
- L241 _public function_ `TVariablePagedArrayIterator& operator--()`
- L247 _public function_ `TVariablePagedArrayIterator operator--(int)`
- L254 _public function_ `const ItemType* NextItem()`
- L268 _public function_ `TVariablePagedArrayIterator& operator++()`
- L274 _public function_ `TVariablePagedArrayIterator operator++(int)`
- L281 _public function_ `const ItemType* SetPositionAtFirstItem()`
- L293 _public function_ `const ItemType* SetPositionAtLastItem()`
- L305 _public function_ `const ItemType* SetPosition(uint64 Index)`
- L322 _private function_ `void OnCurrentPageChanged()`
- L328 _private member_ `const ArrayType* Outer = nullptr;`
- L329 _private member_ `const PageType* CurrentPage = nullptr;`
- L330 _private member_ `uint64 CurrentItemIndex = 0;`
- L331 _private member_ `const ItemType* CurrentItem = nullptr;`
- L332 _private member_ `const ItemType* CurrentPageFirstItem = nullptr;`
- L333 _private member_ `const ItemType* CurrentPageLastItem = nullptr;`

#### class `TraceServices::TVariablePagedArray`  
`template<typename InItemType> class TVariablePagedArray`  
_L339-791_
- L342 _public typedef_ `typedef InItemType ItemType;`
- L343 _public typedef_ `typedef TVariablePagedArrayPage<InItemType> PageType;`
- L344 _public typedef_ `typedef TVariablePagedArrayPageGroup<InItemType> PageGroupType;`
- L345 _public typedef_ `typedef TVariablePagedArrayIterator<InItemType> TIterator;`
- L347 _public function_ `TVariablePagedArray(ILinearAllocator& InAllocator, uint64 InPageSize) : Allocator(InAllocator) , Pages() , FirstPage(nullptr) , LastPage(nullptr) , PageGroups() , FirstPageGroup(nullptr) , LastPageGroup(nullptr) , PageSize(InPageSize) , TotalItemCount(0)`
- L360 _public function_ `~TVariablePagedArray()`
- L373 _public function_ `uint64 Num() const`
- L378 _public function_ `uint64 GetPageSize() const`
- L383 _public function_ `uint64 NumPages() const`
- L388 _public function_ `uint64 NumItemsWasted() const`
- L394 _public function_ `double WastedPercent() const`
- L400 _public function_ `ItemType& PushBack()`
- L427 _public function_ `ItemType& Insert(uint64 Index)`
- L560 _public function_ `TIterator GetIterator() const`
- L565 _public function_ `TIterator GetIteratorFromItem(uint64 ItemIndex) const`
- L570 _public function_ `ItemType& operator[](uint64 Index)`
- L579 _public function_ `const ItemType& operator[](uint64 Index) const`
- L584 _public function_ `ItemType& First()`
- L590 _public function_ `const ItemType& First() const`
- L596 _public function_ `ItemType& Last()`
- L602 _public function_ `const ItemType& Last() const`
- L609 _private function_ `void FindItemChecked(const uint64 Index, const PageType*& OutPage, uint64& OutItemIndexInPage) const`
- L640 _private function_ `void CreateInitialPage()`
- L657 _private function_ `ItemType& PushBackItemInPageGroup(const uint64 PageGroupIndex)`
- L681 _private function_ `void OnInsertedPage(const uint64 PageGroupIndex)`
- L699 _private function_ `void OnInsertedItem(const uint64 PageGroupIndex)`
- L715 _private function_ `void CheckIntegrity() const`
- L779 _private member_ `ILinearAllocator& Allocator;`
- L781 _private member_ `TArray<PageType> Pages;`
- L782 _private member_ `PageType* FirstPage;`
- L783 _private member_ `PageType* LastPage;`
- L785 _private member_ `TArray<PageGroupType> PageGroups;`
- L786 _private member_ `PageGroupType* FirstPageGroup;`
- L787 _private member_ `PageGroupType* LastPageGroup;`
- L789 _private member_ `uint64 PageSize;`
- L790 _private member_ `uint64 TotalItemCount;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace TraceServices`
- L47 _macro_ `#define DEBUG_VARIABLE_PAGED_ARRAY 0` — For debugging the TVariablePagedArray implementation.
- L50 _macro_ `#define VARIABLE_PAGED_ARRAY_CHECK(x) check(x)`
- L70 _function_ `template<typename ItemType> inline const ItemType* GetData(const TVariablePagedArrayPage<ItemType>& Page)` (scope `TraceServices`)
- L76 _function_ `template<typename ItemType> inline SIZE_T GetNum(const TVariablePagedArrayPage<ItemType>& Page)` (scope `TraceServices`)
- L82 _function_ `template<typename ItemType> inline const ItemType* GetFirstItem(const TVariablePagedArrayPage<ItemType>& Page)` (scope `TraceServices`)
- L88 _function_ `template<typename ItemType> inline const ItemType* GetLastItem(const TVariablePagedArrayPage<ItemType>& Page)` (scope `TraceServices`)

### `Source/Developer/TraceServices/Public/Model/AsyncEnumerateTask.h` (Public)


#### struct `TraceServices::FAsyncEnumerateTaskData`  
`template<typename InEventType, typename SettingsType> struct FAsyncEnumerateTaskData`  
_L14-27_
- L16 _public member_ `uint32 TaskIndex;`
- L17 _public member_ `uint32 NumTasks;`
- L18 _public member_ `uint64 StartPageIndex;` — Inclusive
- L19 _public member_ `uint64 EndPageIndex;` — Exclusive
- L20 _public member_ `double StartTime;`
- L21 _public member_ `double EndTime;`
- L22 _public member_ `EEventSortOrder SortOrder;`
- L23 _public member_ `const FDetailLevel<InEventType, SettingsType>* DetailLevel;`
- L25 _public member_ `typename ITimeline<InEventType>::AsyncEventRangeCallback EventRangeCallback;`
- L26 _public member_ `typename ITimeline<InEventType>::AsyncEventCallback EventCallback;`

#### class `TraceServices::EnumerateAsyncAlgoritm`  
`template<typename InEventType, typename SettingsType> class EnumerateAsyncAlgoritm`  
_L30-191_
- L39 _public typedef_ `typedef TFunctionRef<void(int32 )> InitialStackCallback;`
- L41 _public function_ `static void EnumerateEventsDownSampled(FAsyncEnumerateTaskData<InEventType, SettingsType>& Data, InitialStackCallback InitCallback, typename ITimeline<InEventType>::EventCallback Callback)`
- L173 _private function_ `static bool ShouldStopSearchingForEndEvents(FAsyncEnumerateTaskData<InEventType, SettingsType>& Data, FEnumerationStackEntry* EventStack, const FEventScopeEntryPage* InitialPage, int32 CurrentStackDepth, const FDetailLevel<InEventType, SettingsType>& DetailLevel)`

#### struct `TraceServices::EnumerateAsyncAlgoritm::FEnumerationStackEntry`  
`struct FEnumerationStackEntry`  
_L33-37_
- L35 _public member_ `double StartTime;`
- L36 _public member_ `InEventType Event;`

#### class `TraceServices::FEnumerateAsyncTask`  
`template<typename InEventType, typename SettingsType> class FEnumerateAsyncTask : public FNonAbandonableTask`  
_L194-355_
- inherits: `FNonAbandonableTask`
- L196 _private typedef_ `using EventType = InEventType;`
- L201 _public function_ `FEnumerateAsyncTask(const FAsyncEnumerateTaskData<InEventType, SettingsType>& InData) : Data(InData)`
- L206 _public function_ `void EnumerateOrderedByStartTime()`
- L281 _public function_ `void EnumerateOrderedByEndTime()`
- L323 _public function_ `void DoWork()`
- L349 _public function_ `FORCEINLINE TStatId GetStatId() const`
- L354 _public member_ `FAsyncEnumerateTaskData<InEventType, SettingsType> Data;`

#### struct `TraceServices::FEnumerateAsyncTask::EnumerateOrderedByStartTime::FStackEntry`  
`struct FStackEntry`  
_L208-211_
- L210 _public member_ `uint64 OutputEventIndex;`

#### struct `TraceServices::FEnumerateAsyncTask::EnumerateOrderedByStartTime::FOutputEvent`  
`struct FOutputEvent`  
_L217-223_
- L219 _public member_ `double StartTime;`
- L220 _public member_ `double EndTime;`
- L221 _public member_ `uint32 Depth;`
- L222 _public member_ `EventType Event;`

#### struct `TraceServices::FEnumerateAsyncTask::EnumerateOrderedByEndTime::FStackEntry`  
`struct FStackEntry`  
_L283-286_
- L285 _public member_ `double StartTime;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace TraceServices`
- L230 _function_ `` (scope `TraceServices::FEnumerateAsyncTask::EnumerateOrderedByStartTime`)
- L294 _function_ `` (scope `TraceServices::FEnumerateAsyncTask::EnumerateOrderedByEndTime`)
- L340 _function_ `` (scope `TraceServices::FEnumerateAsyncTask::DoWork`)

### `Source/Developer/TraceServices/Public/Model/IntervalTimeline.h` (Public)


#### struct `TraceServices::FIntervalTimelineDefaultSettings`  
`struct FIntervalTimelineDefaultSettings`  
_L13-19_

#### enum `TraceServices::FIntervalTimelineDefaultSettings::(anonymous)`  
``  
_L16-18_

#### class `TraceServices::TIntervalTimeline`  
`template<typename EventType, typename SettingsType = FIntervalTimelineDefaultSettings> class TIntervalTimeline : public ITimeline<EventType>`  
_L22-170_
- inherits: `ITimeline<EventType>`
- L26 _public function_ `TIntervalTimeline(ILinearAllocator& Allocator) : Events(Allocator, SettingsType::EventsPerPage)`
- L31 _public prototype_ `virtual ~TIntervalTimeline() = default;`
- L32 _public function_ `virtual uint64 GetModCount() const override`
- L33 _public function_ `virtual uint64 GetEventCount() const override`
- L34 _public function_ `virtual const EventType& GetEvent(uint64 InIndex) const override`
- L35 _public function_ `double GetEventStartTime(uint64 InIndex) const`
- L36 _public function_ `double GetEventEndTime(uint64 InIndex) const`
- L37 _public function_ `virtual double GetStartTime() const override`
- L38 _public function_ `virtual double GetEndTime() const override`
- L39 _public function_ `virtual void EnumerateEventsDownSampled(double IntervalStart, double IntervalEnd, double Resolution, typename ITimeline<EventType>::EventCallback Callback) const override`
- L40 _public function_ `virtual void EnumerateEventsDownSampled(double IntervalStart, double IntervalEnd, double Resolution, typename ITimeline<EventType>::EventRangeCallback Callback) const override`
- L41 _public function_ `virtual void EnumerateEvents(double IntervalStart, double IntervalEnd, typename ITimeline<EventType>::EventCallback Callback) const override`
- L51 _public function_ `virtual void EnumerateEvents(double IntervalStart, double IntervalEnd, typename ITimeline<EventType>::EventRangeCallback Callback) const override`
- L80 _public function_ `uint64 AppendBeginEvent(double StartTime, const EventType& Event)`
- L86 _public function_ `template <typename... ArgsType> uint64 EmplaceBeginEvent(double StartTime, ArgsType&&... Args)`
- L116 _public function_ `EventType& EndEvent(uint64 EventIndex, double EndTime)`
- L133 _public function_ `virtual bool GetEventInfo(double InTime, double DeltaTime, int32 Depth, typename ITimeline<EventType>::FTimelineEventInfo& EventInfo) const override`
- L166 _private member_ `TPagedArray<FEventInternal, FEventPage> Events;`
- L167 _private member_ `FEventPage* CurrentPage = nullptr;`
- L168 _private member_ `double LastTime = 0.0;`
- L169 _private member_ `uint64 ModCount = 0;`

#### struct `TraceServices::TIntervalTimeline::FEventInternal`  
`struct FEventInternal`  
_L141-153_
- L143 _public member_ `double StartTime;`
- L144 _public member_ `double EndTime;`
- L145 _public member_ `EventType Event;`
- L147 _public prototype_ `FEventInternal() = default;`
- L148 _public function_ `FEventInternal(double InStartTime, double InEndTime, EventType InEvent) : StartTime(InStartTime) , EndTime(InEndTime) , Event(MoveTempIfPossible(InEvent))`

#### struct `TraceServices::TIntervalTimeline::FEventPage`  
`struct FEventPage`  
_L155-164_
- L157 _public member_ `double BeginTime = 0.0;`
- L158 _public member_ `double EndTime = 0.0;`
- L159 _public member_ `uint64 BeginEventIndex = 0;`
- L160 _public member_ `uint64 EndEventIndex = 0;`
- L161 _public member_ `FEventInternal* Items = nullptr;`
- L162 _public member_ `uint64 Count = 0;`
- L163 _public member_ `uint64 OpenEvents = 0;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace TraceServices`
- L17 _enumerator_ `EventsPerPage = 65536` (scope `TraceServices::FIntervalTimelineDefaultSettings::__anon0730570d0103`)
- L44 _function_ `` (scope `TraceServices::TIntervalTimeline::EnumerateEvents`)

### `Source/Developer/TraceServices/Public/Model/MonotonicTimeline.h` (Public)


#### struct `TraceServices::FMonotonicTimelineDefaultSettings`  
`struct FMonotonicTimelineDefaultSettings`  
_L16-31_
- L26 _public function_ `constexpr static double DetailLevelResolution(int32 Index)`

#### enum `TraceServices::FMonotonicTimelineDefaultSettings::(anonymous)`  
``  
_L19-24_

#### class `TraceServices::IEditableTimeline`  
`template<typename InEventType> class IEditableTimeline`  
_L37-63_
- desc: An interface that can consume timed serial events (a timeline).
- L40 _public prototype_ `virtual ~IEditableTimeline() = default;`
- L48 _public prototype_ `virtual void AppendBeginEvent(double StartTime, const InEventType& Event) = 0;` — Begin a new timed event. @param StartTime	The starting timestamp of the event in seconds. @param Event		The event information.
- L55 _public prototype_ `virtual void AppendEndEvent(double EndTime) = 0;` — End a new timed event. This ends the event started by the prior call to AppendBeginEvent. @param EndTime	The ending timestamp of the event in seconds.
- L62 _public function_ `virtual double GetLastTimestamp() const` — Gets the last time added to the timeline. @return The last timestamp added to the timeline.

#### class `TraceServices::TMonotonicTimeline`  
`template<typename InEventType, typename SettingsType = FMonotonicTimelineDefaultSettings> class TMonotonicTimeline : public ITimeline<InEventType> , public IEditableTimeline<InEventType>`  
_L66-1496_
- inherits: `ITimeline<InEventType>,IEditableTimeline<InEventType>`
- L72 _private typedef_ `typedef FEventInfoStackEntry<InEventType, SettingsType> FEventInfoStackEntry;`
- L73 _private typedef_ `typedef FDetailLevel<InEventType, SettingsType> FDetailLevel;`
- L74 _private typedef_ `typedef FDetailLevelDepthState<InEventType> FDetailLevelDepthState;`
- L75 _private typedef_ `typedef FEnumerateAsyncTask<InEventType, SettingsType> FEnumerateAsyncTask;`
- L78 _public typedef_ `using EventType = InEventType;`
- L80 _public function_ `TMonotonicTimeline(ILinearAllocator& InAllocator) : Allocator(InAllocator)`
- L90 _public prototype_ `virtual ~TMonotonicTimeline() = default;`
- L92 _public function_ `virtual void AppendBeginEvent(double StartTime, const EventType& Event) override`
- L159 _public function_ `virtual void AppendEndEvent(double EndTime) override`
- L204 _public function_ `virtual uint64 GetModCount() const override`
- L209 _public function_ `virtual uint64 GetEventCount() const override`
- L214 _public function_ `virtual const EventType& GetEvent(uint64 InIndex) const override`
- L219 _public function_ `virtual double GetStartTime() const override`
- L224 _public function_ `virtual double GetEndTime() const override`
- L230 _public function_ `virtual double GetLastTimestamp() const override`
- L235 _public function_ `virtual void EnumerateEventsDownSampled(double IntervalStart, double IntervalEnd, double Resolution, typename ITimeline<EventType>::EventCallback Callback) const override`
- L419 _public function_ `virtual void EnumerateEventsDownSampled(double IntervalStart, double IntervalEnd, double Resolution, typename ITimeline<EventType>::EventRangeCallback Callback) const override`
- L479 _public function_ `virtual void EnumerateEventsBackwardsDownSampled(double IntervalEnd, double IntervalStart, double Resolution, typename ITimeline<EventType>::EventCallback Callback) const override`
- L683 _public function_ `virtual void EnumerateEventsBackwardsDownSampled(double IntervalEnd, double IntervalStart, double Resolution, typename ITimeline<EventType>::EventRangeCallback Callback) const override`
- L718 _public function_ `virtual void EnumerateEventsDownSampledAsync(const typename ITimeline<EventType>::EnumerateAsyncParams& EnumerateAsyncParams) const override`
- L810 _public function_ `virtual void EnumerateEvents(double IntervalStart, double IntervalEnd, typename ITimeline<EventType>::EventCallback Callback) const override`
- L815 _public function_ `virtual void EnumerateEvents(double IntervalStart, double IntervalEnd, typename ITimeline<EventType>::EventRangeCallback Callback) const override`
- L820 _public function_ `virtual void EnumerateEventsBackwards(double IntervalEnd, double IntervalStart, typename ITimeline<EventType>::EventCallback Callback) const override`
- L825 _public function_ `virtual void EnumerateEventsBackwards(double IntervalEnd, double IntervalStart, typename ITimeline<EventType>::EventRangeCallback Callback) const override`
- L830 _public function_ `virtual bool GetEventInfo(double InTime, double DeltaTime, int32 Depth, typename ITimeline<InEventType>::FTimelineEventInfo& EventInfo) const override`
- L1095 _public function_ `virtual int32 GetDepthAt(double Time) const override`
- L1172 _private function_ `void UpdateDominatingEvent(FDetailLevel& DetailLevel, int32 Depth, double CurrentTime)`
- L1193 _private function_ `void AddScopeEntry(FDetailLevel& DetailLevel, double Time, bool IsEnter)`
- L1289 _private function_ `void AddEvent(FDetailLevel& DetailLevel, const EventType& Event)`
- L1298 _private function_ `bool FindEventUsingPageInitialStack(typename TPagedArray<FEventScopeEntry, FEventScopeEntryPage>::TIterator ScopeEntryIterator, double Time, double DeltaTime, int32 Depth, const FDetailLevel& DetailLevel, FEventStackEntry& OutPageStackEntry) const`
- L1353 _private function_ `bool FindBestMatchEvent(const FFindBestMatchEventInParams &InParams, FFindBestMatchEventOutParams &OutParams) const`
- L1492 _private member_ `ILinearAllocator& Allocator;`
- L1493 _private member_ `TArray<FDetailLevel> DetailLevels;`
- L1494 _private member_ `int32 ExtraDepthEvents = 0;` — the number of events virtually pushed on the stack when depth exceeds SettingsType::MaxDepth
- L1495 _private member_ `uint64 ModCount = 0;` — a serial number increased each time the timeline is modified

#### struct `TraceServices::TMonotonicTimeline::EnumerateEventsDownSampled::FEnumerationStackEntry`  
`struct FEnumerationStackEntry`  
_L273-277_
- L275 _public member_ `double StartTime;`
- L276 _public member_ `EventType Event;`

#### struct `TraceServices::TMonotonicTimeline::EnumerateEventsDownSampled::FStackEntry`  
`struct FStackEntry`  
_L421-424_
- L423 _public member_ `uint64 LocalEventIndex;`

#### struct `TraceServices::TMonotonicTimeline::EnumerateEventsDownSampled::FOutputEvent`  
`struct FOutputEvent`  
_L428-434_
- L430 _public member_ `double StartTime;`
- L431 _public member_ `double EndTime;`
- L432 _public member_ `uint32 Depth;`
- L433 _public member_ `EventType Event;`

#### struct `TraceServices::TMonotonicTimeline::EnumerateEventsBackwardsDownSampled::FEnumerationStackEntry`  
`struct FEnumerationStackEntry`  
_L504-508_
- L506 _public member_ `double EndTime;`
- L507 _public member_ `EventType Event;`

#### struct `TraceServices::TMonotonicTimeline::EnumerateEventsBackwardsDownSampled::FStackEntry`  
`struct FStackEntry`  
_L685-689_
- L687 _public member_ `double EndTime;`
- L688 _public member_ `EventType Event;`

#### struct `TraceServices::TMonotonicTimeline::FIterationState`  
`struct FIterationState`  
_L1145-1152_
- L1147 _public member_ `typename TPagedArray<FEventScopeEntry, FEventScopeEntryPage>::TIterator ScopeIterator;`
- L1148 _public member_ `typename TPagedArray<EventType>::TIterator EventsIterator;`
- L1149 _public member_ `FEventInfoStackEntry* EventStack;`
- L1150 _public member_ `int32 StackDepth;`
- L1151 _public member_ `double LastIterationTime;`

#### struct `TraceServices::TMonotonicTimeline::FFindBestMatchEventInParams`  
`struct FFindBestMatchEventInParams`  
_L1154-1161_
- L1156 _public member_ `FIterationState IterationState;`
- L1158 _public member_ `double TargetExactTime;`
- L1159 _public member_ `double TargetEndTime;`
- L1160 _public member_ `int32 TargetDepth;`

#### struct `TraceServices::TMonotonicTimeline::FFindBestMatchEventOutParams`  
`struct FFindBestMatchEventOutParams`  
_L1163-1170_
- L1165 _public member_ `FIterationState IterationState;`
- L1167 _public member_ `FEventInfoStackEntry EventInfo;`
- L1168 _public member_ `bool bHasEndTime;`
- L1169 _public member_ `double EndTime;`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace TraceServices`
- L20 _enumerator_ `MaxDepth = 1024` (scope `TraceServices::FMonotonicTimelineDefaultSettings::__anonbbfa909e0103`)
- L21 _enumerator_ `ScopeEntriesPageSize = 65536` (scope `TraceServices::FMonotonicTimelineDefaultSettings::__anonbbfa909e0103`)
- L22 _enumerator_ `EventsPageSize = 65536` (scope `TraceServices::FMonotonicTimelineDefaultSettings::__anonbbfa909e0103`)
- L23 _enumerator_ `DetailLevelsCount = 6` (scope `TraceServices::FMonotonicTimelineDefaultSettings::__anonbbfa909e0103`)
- L256 _function_ `` (scope `TraceServices::TMonotonicTimeline::EnumerateEventsDownSampled`)
- L500 _function_ `` (scope `TraceServices::TMonotonicTimeline::EnumerateEventsBackwardsDownSampled`)
- L747 _function_ `` (scope `TraceServices::TMonotonicTimeline::EnumerateEventsDownSampledAsync`)
- L852 _function_ `` (scope `TraceServices::TMonotonicTimeline::GetEventInfo`)
- L1107 _function_ `` (scope `TraceServices::TMonotonicTimeline::GetDepthAt`)

### `Source/Developer/TraceServices/Public/Model/MonotonicTimelineData.h` (Public)


#### struct `TraceServices::FEventScopeEntry`  
`struct FEventScopeEntry`  
_L10-13_
- L12 _public member_ `double Time;`

#### struct `TraceServices::FEventStackEntry`  
`struct FEventStackEntry`  
_L15-21_
- L17 _public member_ `uint64 EnterScopeIndex;`
- L18 _public member_ `uint64 EventIndex;`
- L19 _public member_ `double ExclTime = 0.0;`
- L20 _public member_ `double EndTime = -1.0;` — By convention a negative EndTime means the event does not end in the current page

#### struct `TraceServices::FEventScopeEntryPage`  
`struct FEventScopeEntryPage`  
_L23-33_
- L25 _public member_ `FEventScopeEntry* Items = nullptr;`
- L26 _public member_ `uint64 Count = 0;`
- L27 _public member_ `double BeginTime = 0.0;`
- L28 _public member_ `double EndTime = 0.0;`
- L29 _public member_ `uint64 BeginEventIndex = 0;`
- L30 _public member_ `uint64 EndEventIndex = 0;`
- L31 _public member_ `FEventStackEntry* InitialStack = nullptr;`
- L32 _public member_ `uint16 InitialStackCount = 0;`

#### struct `TraceServices::FDetailLevelDepthState`  
`template<typename EventType> struct FDetailLevelDepthState`  
_L36-48_
- L38 _public member_ `int64 PendingScopeEnterIndex = -1;`
- L39 _public member_ `int64 PendingEventIndex = -1;`
- L41 _public member_ `EventType DominatingEvent;`
- L42 _public member_ `double DominatingEventStartTime = 0.0;`
- L43 _public member_ `double DominatingEventEndTime = 0.0;`
- L44 _public member_ `double DominatingEventDuration = 0.0;`
- L46 _public member_ `double EnterTime = 0.0;`
- L47 _public member_ `double ExitTime = 0.0;`

#### struct `TraceServices::FDetailLevelInsertionState`  
`template<typename EventType, typename SettingsType> struct FDetailLevelInsertionState`  
_L51-59_
- L53 _public member_ `double LastTime = -1.0;`
- L54 _public member_ `uint16 CurrentDepth = 0;`
- L55 _public member_ `int32 PendingDepth = -1;`
- L56 _public member_ `FDetailLevelDepthState<EventType> DepthStates[SettingsType::MaxDepth];`
- L57 _public member_ `FEventStackEntry EventStack[SettingsType::MaxDepth];`
- L58 _public member_ `uint64 CurrentScopeEntryPageIndex = (uint64)-1;`

#### struct `TraceServices::FDetailLevel`  
`template<typename EventType, typename SettingsType> struct FDetailLevel`  
_L62-93_
- L64 _public function_ `FDetailLevel(ILinearAllocator& Allocator, double InResolution) : Resolution(InResolution) , ScopeEntries(Allocator, SettingsType::ScopeEntriesPageSize) , Events(Allocator, SettingsType::EventsPageSize)`
- L72 _public function_ `double GetScopeEntryTime(uint64 Index) const`
- L78 _public function_ `void SetEvent(uint64 Index, const EventType& Event)`
- L83 _public function_ `EventType GetEvent(uint64 Index) const`
- L88 _public member_ `double Resolution;`
- L89 _public member_ `TPagedArray<FEventScopeEntry, FEventScopeEntryPage> ScopeEntries;`
- L90 _public member_ `TPagedArray<EventType> Events;`
- L92 _public member_ `FDetailLevelInsertionState<EventType, SettingsType> InsertionState;`

#### struct `TraceServices::FEventInfoStackEntry`  
`template<typename EventType, typename SettingsType> struct FEventInfoStackEntry`  
_L96-109_
- L98 _public prototype_ `FEventInfoStackEntry() = default;`
- L99 _public function_ `FEventInfoStackEntry(const FEventStackEntry& EventStackEntry, const FDetailLevel<EventType, SettingsType>& DetailLevel)`
- L106 _public member_ `EventType Event;`
- L107 _public member_ `double StartTime = 0.0;`
- L108 _public member_ `double ExclTime = 0.0;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace TraceServices`

### `Source/Developer/TraceServices/Public/Model/PointTimeline.h` (Public)


#### struct `TraceServices::FPointTimelineDefaultSettings`  
`struct FPointTimelineDefaultSettings`  
_L13-19_

#### enum `TraceServices::FPointTimelineDefaultSettings::(anonymous)`  
``  
_L16-18_

#### class `TraceServices::TPointTimeline`  
`template<typename EventType, typename SettingsType = FPointTimelineDefaultSettings> class TPointTimeline : public ITimeline<EventType>`  
_L22-175_
- inherits: `ITimeline<EventType>`
- L26 _public function_ `TPointTimeline(ILinearAllocator& Allocator) : Events(Allocator, SettingsType::EventsPerPage)`
- L31 _public prototype_ `virtual ~TPointTimeline() = default;`
- L32 _public function_ `virtual uint64 GetModCount() const override`
- L33 _public function_ `virtual uint64 GetEventCount() const override`
- L34 _public function_ `virtual const EventType& GetEvent(uint64 InIndex) const override`
- L35 _public function_ `virtual double GetStartTime() const override`
- L36 _public function_ `virtual double GetEndTime() const override`
- L37 _public function_ `virtual void EnumerateEventsDownSampled(double IntervalStart, double IntervalEnd, double Resolution, typename ITimeline<EventType>::EventCallback Callback) const override`
- L38 _public function_ `virtual void EnumerateEventsDownSampled(double IntervalStart, double IntervalEnd, double Resolution, typename ITimeline<EventType>::EventRangeCallback Callback) const override`
- L39 _public function_ `virtual void EnumerateEvents(double IntervalStart, double IntervalEnd, typename ITimeline<EventType>::EventCallback Callback) const override`
- L49 _public function_ `virtual void EnumerateEvents(double IntervalStart, double IntervalEnd, typename ITimeline<EventType>::EventRangeCallback Callback) const override`
- L100 _public function_ `uint64 AppendEvent(double Time, const EventType& Event)`
- L106 _public function_ `template <typename... ArgsType> uint64 EmplaceEvent(double Time, ArgsType&&... Args)`
- L135 _public function_ `void SetEnumerateOutsideRange(bool bInEnumerateOutsideRange)` — Set whether we enumerate one event each side of the passed-in time range. This is useful for cases such as drawing where connected events need to be drawn outside of the viewport.
- L140 _public function_ `virtual bool GetEventInfo(double InTime, double DeltaTime, int32 Depth, typename ITimeline<EventType>::FTimelineEventInfo& EventInfo) const override`
- L170 _private member_ `TPagedArray<FEventInternal, FEventPage> Events;`
- L171 _private member_ `FEventPage* CurrentPage = nullptr;`
- L172 _private member_ `double LastTime = 0.0;`
- L173 _private member_ `uint64 ModCount = 0;`
- L174 _private member_ `bool bEnumerateOutsideRange = false;`

#### struct `TraceServices::TPointTimeline::FEventInternal`  
`struct FEventInternal`  
_L148-158_
- L150 _public member_ `double Time;`
- L151 _public member_ `EventType Event;`
- L153 _public prototype_ `FEventInternal() = default;`
- L154 _public function_ `FEventInternal(double InTime, EventType InEvent) : Time(InTime) , Event(MoveTempIfPossible(InEvent))`

#### struct `TraceServices::TPointTimeline::FEventPage`  
`struct FEventPage`  
_L160-168_
- L162 _public member_ `double BeginTime = 0.0;`
- L163 _public member_ `double EndTime = 0.0;`
- L164 _public member_ `uint64 BeginEventIndex = 0;`
- L165 _public member_ `uint64 EndEventIndex = 0;`
- L166 _public member_ `FEventInternal* Items = nullptr;`
- L167 _public member_ `uint64 Count = 0;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace TraceServices`
- L17 _enumerator_ `EventsPerPage = 65536` (scope `TraceServices::FPointTimelineDefaultSettings::__anona8ffb1d20103`)
- L42 _function_ `` (scope `TraceServices::TPointTimeline::EnumerateEvents`)

### `Source/Developer/TraceServices/Public/TraceServices/AnalysisService.h` (Public)


#### class `TraceServices::IAnalysisService`  
`class IAnalysisService`  
_L23-49_
- L32 _public prototype_ `virtual TSharedPtr<const IAnalysisSession> Analyze(const TCHAR* SessionUri) = 0;` — Start analysis from a file and wait for it to finish. @param SessionUri Path to trace file. @return New completed analysis session
- L39 _public prototype_ `virtual TSharedPtr<const IAnalysisSession> StartAnalysis(const TCHAR* SessionUri) = 0;` — Start analysis reading from a file. @param SessionUri Path to trace file @return New analysis session
- L48 _public prototype_ `virtual TSharedPtr<const IAnalysisSession> StartAnalysis(uint32 TraceId, const TCHAR* SessionName, TUniquePtr<UE::Trace::IInDataStream>&& DataStream) = 0;` — Start analysis from a trace which can be identified with a trace id. @param TraceId Unique trace id. If no id is available set ~0. @param SessionName Display name for this session @param DataStream Stream to read from @return New analysis session

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L12 _namespace_ `namespace Trace` (scope `UE`)
- L18 _namespace_ `namespace TraceServices`

### `Source/Developer/TraceServices/Public/TraceServices/AnalyzerFactories.h` (Public)


#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L11 _namespace_ `namespace Trace` (scope `UE`)
- L20 _namespace_ `namespace TraceServices`
- L36 _prototype_ `TSharedPtr<IAnalysisSession> CreateAnalysisSession(uint32 InTraceId, const TCHAR* InSessionName, TUniquePtr<UE::Trace::IInDataStream>&& InDataStream);` (scope `TraceServices`) — Create an IAnalysisSession object for external analysis. @param InTraceId		A user defined identifier for this session. @param InSessionName	A user defined string to present to the user for this session. @param InDataStream	The data stream interface for this analysis session.
- L44 _prototype_ `TSharedPtr<UE::Trace::IAnalyzer> CreateBookmarksAnalyzer(IAnalysisSession& InSession, IEditableBookmarkProvider& InEditableBookmarkProvider);` (scope `TraceServices`) — Create an IAnalyzer object for analyzing bookmark events. @param InSession					The session object to interact with. @param InEditableBookmarkProvider	The bookmark provider interface to receive the event callbacks.
- L52 _prototype_ `TSharedPtr<UE::Trace::IAnalyzer> CreateCountersAnalyzer(IAnalysisSession& InSession, IEditableCounterProvider& InEditableCounterProvider);` (scope `TraceServices`) — Create an IAnalyzer object for analyzing counter events. @param InSession					The session object to interact with. @param InEditableCounterProvider	The counter provider interface to receive the event callbacks.
- L61 _prototype_ `TSharedPtr<UE::Trace::IAnalyzer> CreateCpuProfilerAnalyzer(IAnalysisSession& InSession, IEditableTimingProfilerProvider& InEditableTimingProfilerProvider, IEditableThreadProvider& InEditableThreadProvider);` (scope `TraceServices`) — Create an IAnalyzer object for external analysis. @param InSession							The session object to interact with. @param InEditableTimingProfilerProvider	The timing profiler provider interface to receive the cpu timing event callbacks. @param InEditableThreadProvider			The thread provider interface to receive the thread event callbacks.

### `Source/Developer/TraceServices/Public/TraceServices/Common/CancellationToken.h` (Public)


#### class `TraceServices::FCancellationToken`  
`class FCancellationToken`  
_L10-23_
- L13 _public function_ `FCancellationToken() : bCancel(false)`
- L17 _public function_ `bool ShouldCancel()`
- L18 _public function_ `void Cancel()`
- L19 _public function_ `void Reset()`
- L22 _private member_ `std::atomic<bool> bCancel;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace TraceServices`

### `Source/Developer/TraceServices/Public/TraceServices/Containers/Allocators.h` (Public)


#### class `TraceServices::ILinearAllocator`  
`class ILinearAllocator`  
_L11-16_
- L14 _public prototype_ `virtual ~ILinearAllocator() = default;`
- L15 _public prototype_ `virtual void* Allocate(uint64 Size) = 0;`

#### class `TraceServices::IStringStore`  
`class IStringStore`  
_L18-26_
- L21 _public prototype_ `virtual ~IStringStore() = default;`
- L22 _public prototype_ `virtual const TCHAR* Find(const TCHAR* String) const = 0;`
- L23 _public prototype_ `virtual const TCHAR* Find(const FStringView& String) const = 0;`
- L24 _public prototype_ `virtual const TCHAR* Store(const TCHAR* String) = 0;`
- L25 _public prototype_ `virtual const TCHAR* Store(const FStringView& String) = 0;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace TraceServices`

### `Source/Developer/TraceServices/Public/TraceServices/Containers/SlabAllocator.h` (Public)


#### class `TraceServices::FSlabAllocator`  
`class FSlabAllocator : public ILinearAllocator`  
_L14-79_
- inherits: `ILinearAllocator`
- L18 _public function_ `FSlabAllocator(uint64 InSlabSize) : SlabSize(InSlabSize)`
- L23 _public function_ `~FSlabAllocator()`
- L32 _public function_ `virtual void* Allocate(uint64 Size) override`
- L59 _public function_ `uint64 GetUsedSize() const`
- L65 _public function_ `uint64 GetAllocatedSize() const`
- L72 _private member_ `mutable FCriticalSection Cs;`
- L73 _private member_ `TArray<void*> Slabs;`
- L74 _private member_ `uint8* CurrentSlab = nullptr;`
- L75 _private member_ `const uint64 SlabSize;`
- L76 _private member_ `uint64 CurrentSlabAllocatedSize = 0;`
- L77 _private member_ `uint64 TotalUsedSize = 0;`
- L78 _private member_ `uint64 TotalAllocatedSize = 0;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace TraceServices`

### `Source/Developer/TraceServices/Public/TraceServices/Containers/Tables.h` (Public)


#### enum `TraceServices::ETableColumnType`  
`enum ETableColumnType`  
_L10-18_
- L12 _public enumerator_ `TableColumnType_Invalid`
- L13 _public enumerator_ `TableColumnType_Bool`
- L14 _public enumerator_ `TableColumnType_Int`
- L15 _public enumerator_ `TableColumnType_Float`
- L16 _public enumerator_ `TableColumnType_Double`
- L17 _public enumerator_ `TableColumnType_CString`

#### enum `TraceServices::ETableColumnDisplayHint`  
`enum ETableColumnDisplayHint`  
_L20-25_
- L22 _public enumerator_ `TableColumnDisplayHint_Time = 1 << 0`
- L23 _public enumerator_ `TableColumnDisplayHint_Memory = 1 << 1`
- L24 _public enumerator_ `TableColumnDisplayHint_Summable = 1 << 31`

#### class `TraceServices::ITableLayout`  
`class ITableLayout`  
_L27-35_
- L30 _public prototype_ `virtual ~ITableLayout() = default;`
- L31 _public prototype_ `virtual uint64 GetColumnCount() const = 0;`
- L32 _public prototype_ `virtual const TCHAR* GetColumnName(uint64 ColumnIndex) const = 0;`
- L33 _public prototype_ `virtual ETableColumnType GetColumnType(uint64 ColumnIndex) const = 0;`
- L34 _public prototype_ `virtual uint32 GetColumnDisplayHintFlags(uint64 ColumnIndex) const = 0;`

#### class `TraceServices::IUntypedTableReader`  
`class IUntypedTableReader`  
_L37-49_
- L40 _public prototype_ `virtual ~IUntypedTableReader() = default;`
- L41 _public prototype_ `virtual bool IsValid() const = 0;`
- L42 _public prototype_ `virtual void NextRow() = 0;`
- L43 _public prototype_ `virtual void SetRowIndex(uint64 RowIndex) = 0;`
- L44 _public prototype_ `virtual bool GetValueBool(uint64 ColumnIndex) const = 0;`
- L45 _public prototype_ `virtual int64 GetValueInt(uint64 ColumnIndex) const = 0;`
- L46 _public prototype_ `virtual float GetValueFloat(uint64 ColumnIndex) const = 0;`
- L47 _public prototype_ `virtual double GetValueDouble(uint64 ColumnIndex) const = 0;`
- L48 _public prototype_ `virtual const TCHAR* GetValueCString(uint64 ColumnIndex) const = 0;`

#### class `TraceServices::ITableReader`  
`template<typename RowType> class ITableReader : public IUntypedTableReader`  
_L52-57_
- inherits: `IUntypedTableReader`
- L56 _public prototype_ `virtual const RowType* GetCurrentRow() const = 0;`

#### class `TraceServices::IUntypedTable`  
`class IUntypedTable`  
_L59-66_
- L62 _public prototype_ `virtual ~IUntypedTable() = default;`
- L63 _public prototype_ `virtual const ITableLayout& GetLayout() const = 0;`
- L64 _public prototype_ `virtual uint64 GetRowCount() const = 0;`
- L65 _public prototype_ `virtual IUntypedTableReader* CreateReader() const = 0;`

#### class `TraceServices::ITable`  
`template<typename RowType> class ITable : public IUntypedTable`  
_L69-75_
- inherits: `IUntypedTable`
- L73 _public prototype_ `virtual ~ITable() = default;`
- L74 _public prototype_ `virtual ITableReader<RowType>* CreateReader() const = 0;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace TraceServices`
- L77 _prototype_ `bool Table2Csv(const IUntypedTable& Table, const TCHAR* Filename);` (scope `TraceServices`)

### `Source/Developer/TraceServices/Public/TraceServices/Containers/Timelines.h` (Public)


#### enum `TraceServices::EEventEnumerate`  
`enum class EEventEnumerate`  
_L11-15_
- L13 _public enumerator_ `Continue`
- L14 _public enumerator_ `Stop`

#### enum `TraceServices::EEventSortOrder`  
`enum class EEventSortOrder`  
_L17-21_
- L19 _public enumerator_ `ByStartTime`
- L20 _public enumerator_ `ByEndTime`

#### class `TraceServices::ITimeline`  
`template<typename InEventType> class ITimeline`  
_L24-90_
- L27 _public typedef_ `typedef InEventType EventType;`
- L28 _public typedef_ `typedef TFunctionRef<EEventEnumerate(bool , double , const EventType& )> EventCallback;`
- L29 _public typedef_ `typedef TFunctionRef<EEventEnumerate(double , double , uint32 , const EventType& )> EventRangeCallback;`
- L30 _public typedef_ `typedef TFunction<EEventEnumerate(double , double , uint32 , const EventType& , uint32 )> AsyncEventRangeCallback;`
- L31 _public typedef_ `typedef TFunction<EEventEnumerate(bool , double , const EventType& , uint32 )> AsyncEventCallback;`
- L32 _public typedef_ `typedef TFunction<void(uint32 )> TaskInfoCallback;`
- L56 _public prototype_ `virtual ~ITimeline() = default;`
- L58 _public prototype_ `virtual uint64 GetModCount() const = 0;`
- L60 _public prototype_ `virtual uint64 GetEventCount() const = 0;`
- L61 _public prototype_ `virtual const InEventType& GetEvent(uint64 InIndex) const = 0;`
- L63 _public prototype_ `virtual double GetStartTime() const = 0;`
- L64 _public prototype_ `virtual double GetEndTime() const = 0;`
- L66 _public prototype_ `virtual void EnumerateEventsDownSampled(double IntervalStart, double IntervalEnd, double Resolution, EventCallback Callback) const = 0;`
- L67 _public prototype_ `virtual void EnumerateEventsDownSampled(double IntervalStart, double IntervalEnd, double Resolution, EventRangeCallback Callback) const = 0;`
- L69 _public function_ `virtual void EnumerateEventsBackwardsDownSampled(double IntervalEnd, double IntervalStart, double Resolution, EventCallback Callback) const`
- L70 _public function_ `virtual void EnumerateEventsBackwardsDownSampled(double IntervalEnd, double IntervalStart, double Resolution, EventRangeCallback Callback) const`
- L72 _public function_ `virtual void EnumerateEventsDownSampledAsync(const EnumerateAsyncParams& EnumerateAsyncParams) const`
- L74 _public prototype_ `virtual void EnumerateEvents(double IntervalStart, double IntervalEnd, EventCallback Callback) const = 0;`
- L75 _public prototype_ `virtual void EnumerateEvents(double IntervalStart, double IntervalEnd, EventRangeCallback Callback) const = 0;`
- L77 _public function_ `virtual void EnumerateEventsBackwards(double IntervalEnd, double IntervalStart, EventCallback Callback) const`
- L78 _public function_ `virtual void EnumerateEventsBackwards(double IntervalEnd, double IntervalStart, EventRangeCallback Callback) const`
- L80 _public function_ `virtual int32 GetDepthAt(double Time) const`
- L89 _public prototype_ `virtual bool GetEventInfo(double InTime, double DeltaTime, int32 Depth, FTimelineEventInfo& EventInfo) const = 0;` — Finds event information for the event closest to InTime from the interval [InTime - DeltaTime, InTime + DeltaTime] @param InTime - The time used to query for the event @param DeltaTime - Events from interval [InTime - DeltaTime, InTime + DeltaTime] will be considered. The one closest to InTime will be returned @param Depth - The Depth used to query for the event @return True if an event was found, False if no event was found for the specified input parameters

#### struct `TraceServices::ITimeline::FTimelineEventInfo`  
`struct FTimelineEventInfo`  
_L34-40_
- L36 _public member_ `double StartTime = 0.0;`
- L37 _public member_ `double EndTime = 0.0;`
- L38 _public member_ `double ExclTime = 0.0;`
- L39 _public member_ `EventType Event;`

#### struct `TraceServices::ITimeline::EnumerateAsyncParams`  
`struct EnumerateAsyncParams`  
_L42-54_
- L44 _public member_ `double IntervalStart = 0.0;`
- L45 _public member_ `double IntervalEnd = -1.0;`
- L46 _public member_ `double Resolution = 0.0;`
- L47 _public member_ `double MaxOccupancy = 0.875;` — Leave 1/8 threads free to avoid starvation.
- L48 _public member_ `EEventSortOrder SortOrder = EEventSortOrder::ByEndTime;`
- L49 _public member_ `typename ITimeline<EventType>::TaskInfoCallback SetupCallback;`
- L52 _public member_ `typename ITimeline<EventType>::AsyncEventRangeCallback EventRangeCallback;` — Only one of these 2 callbacks must be set.
- L53 _public member_ `typename ITimeline<EventType>::AsyncEventCallback EventCallback;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace TraceServices`

### `Source/Developer/TraceServices/Public/TraceServices/ITraceServicesModule.h` (Public)


#### class `ITraceServicesModule`  
`class ITraceServicesModule : public IModuleInterface`  
_L16-26_
- inherits: `IModuleInterface`
- L20 _public prototype_ `virtual TSharedPtr<TraceServices::IAnalysisService> GetAnalysisService() = 0;`
- L21 _public prototype_ `virtual TSharedPtr<TraceServices::IModuleService> GetModuleService() = 0;`
- L22 _public prototype_ `virtual TSharedPtr<TraceServices::IAnalysisService> CreateAnalysisService() = 0;`
- L23 _public prototype_ `virtual TSharedPtr<TraceServices::IModuleService> CreateModuleService() = 0;`
- L25 _public prototype_ `virtual ~ITraceServicesModule() = default;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace TraceServices`

### `Source/Developer/TraceServices/Public/TraceServices/Model/AllocationsProvider.h` (Public)


#### class `TraceServices::IAllocationsProvider`  
`class IAllocationsProvider : public IProvider`  
_L22-293_
- inherits: `IProvider`
- L140 _public typedef_ `typedef TUniquePtr<const FAllocations> FQueryResult;`
- L167 _public typedef_ `typedef UPTRINT FQueryHandle;`
- L170 _public prototype_ `virtual ~IAllocationsProvider() = default;`
- L172 _public prototype_ `virtual void BeginRead() const = 0;`
- L173 _public prototype_ `virtual void EndRead() const = 0;`
- L174 _public prototype_ `virtual void ReadAccessCheck() const = 0;`
- L176 _public prototype_ `virtual bool IsInitialized() const = 0;`
- L179 _public prototype_ `virtual bool HasAllocationEvents() const = 0;` — Returns true if provider has processed at least one Alloc, Free or Heap event.
- L182 _public prototype_ `virtual bool HasSwapOpEvents() const = 0;` — Returns true if provider has processed at least one Swap Op event.
- L185 _public prototype_ `virtual void EnumerateTags(TFunctionRef<void(const TCHAR*, const TCHAR*, TagIdType, TagIdType)> Callback) const = 0;` — Enumerates the discovered tags.
- L189 _public prototype_ `virtual const TCHAR* GetTagName(TagIdType Tag) const = 0;` — Returns the display name of the specified LLM tag. Lifetime of returned string matches the session lifetime.
- L190 _public prototype_ `virtual const TCHAR* GetTagFullPath(TagIdType Tag) const = 0;`
- L192 _public prototype_ `virtual void EnumerateRootHeaps(TFunctionRef<void(HeapId Id, const FHeapSpec&)> Callback) const = 0;`
- L193 _public prototype_ `virtual void EnumerateHeaps(TFunctionRef<void(HeapId Id, const FHeapSpec&)> Callback) const = 0;`
- L196 _public prototype_ `virtual int32 GetTimelineNumPoints() const = 0;` — Returns the number of points in each timeline (Min/Max Total Allocated Memory, Min/Max Live Allocations, Total Alloc Events, Total Free Events).
- L200 _public prototype_ `virtual void GetTimelineIndexRange(double StartTime, double EndTime, int32& StartIndex, int32& EndIndex) const = 0;` — Returns the inclusive index range [StartIndex, EndIndex] for a time range [StartTime, EndTime]. Index values are in range { -1, 0, .. , N-1, N }, where N = GetTimelineNumPoints().
- L204 _public function_ `virtual void EnumerateMinTotalAllocatedMemoryTimeline(int32 StartIndex, int32 EndIndex, TFunctionRef<void(double Time, double Duration, uint64 Value)> Callback) const` — `UE_DEPRECATED(5.7, "Use EnumerateTimeline(ETimelineUInt64, ...) instead")`
- L210 _public function_ `virtual void EnumerateMaxTotalAllocatedMemoryTimeline(int32 StartIndex, int32 EndIndex, TFunctionRef<void(double Time, double Duration, uint64 Value)> Callback) const` — `UE_DEPRECATED(5.7, "Use EnumerateTimeline(ETimelineUInt64, ...) instead")`
- L216 _public function_ `virtual void EnumerateMinLiveAllocationsTimeline(int32 StartIndex, int32 EndIndex, TFunctionRef<void(double Time, double Duration, uint32 Value)> Callback) const` — `UE_DEPRECATED(5.7, "Use EnumerateTimeline(ETimelineUInt32, ...) instead")`
- L222 _public function_ `virtual void EnumerateMaxLiveAllocationsTimeline(int32 StartIndex, int32 EndIndex, TFunctionRef<void(double Time, double Duration, uint32 Value)> Callback) const` — `UE_DEPRECATED(5.7, "Use EnumerateTimeline(ETimelineUInt32, ...) instead")`
- L228 _public function_ `virtual void EnumerateMinTotalSwapMemoryTimeline(int32 StartIndex, int32 EndIndex, TFunctionRef<void(double Time, double Duration, uint64 Value)> Callback) const` — `UE_DEPRECATED(5.7, "Use EnumerateTimeline(ETimelineUInt64, ...) instead")`
- L234 _public function_ `virtual void EnumerateMaxTotalSwapMemoryTimeline(int32 StartIndex, int32 EndIndex, TFunctionRef<void(double Time, double Duration, uint64 Value)> Callback) const` — `UE_DEPRECATED(5.7, "Use EnumerateTimeline(ETimelineUInt64, ...) instead")`
- L240 _public function_ `virtual void EnumerateMinTotalCompressedSwapMemoryTimeline(int32 StartIndex, int32 EndIndex, TFunctionRef<void(double Time, double Duration, uint64 Value)> Callback) const` — `UE_DEPRECATED(5.7, "Use EnumerateTimeline(ETimelineUInt64, ...) instead")`
- L246 _public function_ `virtual void EnumerateMaxTotalCompressedSwapMemoryTimeline(int32 StartIndex, int32 EndIndex, TFunctionRef<void(double Time, double Duration, uint64 Value)> Callback) const` — `UE_DEPRECATED(5.7, "Use EnumerateTimeline(ETimelineUInt64, ...) instead")`
- L252 _public function_ `virtual void EnumerateAllocEventsTimeline(int32 StartIndex, int32 EndIndex, TFunctionRef<void(double Time, double Duration, uint32 Value)> Callback) const` — `UE_DEPRECATED(5.7, "Use EnumerateTimeline(ETimelineUInt32, ...) instead")`
- L258 _public function_ `virtual void EnumerateFreeEventsTimeline(int32 StartIndex, int32 EndIndex, TFunctionRef<void(double Time, double Duration, uint32 Value)> Callback) const` — `UE_DEPRECATED(5.7, "Use EnumerateTimeline(ETimelineUInt32, ...) instead")`
- L264 _public function_ `virtual void EnumeratePageInEventsTimeline(int32 StartIndex, int32 EndIndex, TFunctionRef<void(double Time, double Duration, uint32 Value)> Callback) const` — `UE_DEPRECATED(5.7, "Use EnumerateTimeline(ETimelineUInt32, ...) instead")`
- L270 _public function_ `virtual void EnumeratePageOutEventsTimeline(int32 StartIndex, int32 EndIndex, TFunctionRef<void(double Time, double Duration, uint32 Value)> Callback) const` — `UE_DEPRECATED(5.7, "Use EnumerateTimeline(ETimelineUInt32, ...) instead")`
- L276 _public function_ `virtual void EnumerateSwapFreeEventsTimeline(int32 StartIndex, int32 EndIndex, TFunctionRef<void(double Time, double Duration, uint32 Value)> Callback) const` — `UE_DEPRECATED(5.7, "Use EnumerateTimeline(ETimelineUInt32, ...) instead")`
- L283 _public prototype_ `virtual void EnumerateTimeline(ETimelineU64 Timeline, int32 StartIndex, int32 EndIndex, TFunctionRef<void(double Time, double Duration, uint64 Value)> Callback) const = 0;` — Enumerates points (time-value pairs) of a UInt64 timeline, in the inclusive index interval [StartIndex, EndIndex].
- L286 _public prototype_ `virtual void EnumerateTimeline(ETimelineU32 Timeline, int32 StartIndex, int32 EndIndex, TFunctionRef<void(double Time, double Duration, uint32 Value)> Callback) const = 0;` — Enumerates points (time-value pairs) of a UInt32 timeline, in the inclusive index interval [StartIndex, EndIndex].
- L288 _public prototype_ `virtual FQueryHandle StartQuery(const FQueryParams& Params) const = 0;`
- L289 _public prototype_ `virtual void CancelQuery(FQueryHandle Query) const = 0;`
- L290 _public prototype_ `virtual const FQueryStatus PollQuery(FQueryHandle Query) const = 0;`
- L292 _public prototype_ `virtual uint64 GetPlatformPageSize() const = 0;`

#### enum `TraceServices::IAllocationsProvider::EQueryRule`  
`enum class EQueryRule`  
_L31-52_
- desc: Allocation query rules. The enum uses the following naming convention: A, B, C, D = time markers a = time when "alloc" event occurs f = time when "free" event occurs (can be infinite) Ex.: "AaBf" means "all memory allocations allocated between time A and time B and freed after time B".
- L33 _public enumerator_ `aAf` — active allocs at A
- L34 _public enumerator_ `afA` — before
- L35 _public enumerator_ `Aaf` — after
- L36 _public enumerator_ `aAfB` — decline
- L37 _public enumerator_ `AaBf` — growth
- L38 _public enumerator_ `aAfaBf` — decline + growth (used as "growth vs. decline")
- L39 _public enumerator_ `AfB` — free events
- L40 _public enumerator_ `AaB` — alloc events
- L41 _public enumerator_ `AafB` — short living allocs
- L42 _public enumerator_ `aABf` — long living allocs
- L43 _public enumerator_ `AaBCf` — memory leaks
- L44 _public enumerator_ `AaBfC` — limited lifetime
- L45 _public enumerator_ `aABfC` — decline of long living allocs
- L46 _public enumerator_ `AaBCfD` — specific lifetime
- L47 _public enumerator_ `AoB` — all paged out allocs between A and B
- L48 _public enumerator_ `AiB` — all paged in allocs between A and B

#### enum `TraceServices::IAllocationsProvider::ETimelineU64`  
`enum class ETimelineU64`  
_L54-75_
- L57 _public enumerator_ `MinTotalAllocatedMemory` — The Minimum Total Allocated Memory
- L60 _public enumerator_ `MaxTotalAllocatedMemory` — The Maximum Total Allocated Memory
- L63 _public enumerator_ `MinTotalSwapMemory` — The Minimum Total Swap Memory
- L66 _public enumerator_ `MaxTotalSwapMemory` — The Maximum Total Swap Memory
- L69 _public enumerator_ `MinTotalCompressedSwapMemory` — The Minimum Total Compressed Swap Memory
- L72 _public enumerator_ `MaxTotalCompressedSwapMemory` — The Maximum Total Compressed Swap Memory
- L74 _public enumerator_ `Count`

#### enum `TraceServices::IAllocationsProvider::ETimelineU32`  
`enum class ETimelineU32`  
_L77-101_
- L80 _public enumerator_ `MinLiveAllocations` — The Minimum Number of Live Allocations
- L83 _public enumerator_ `MaxLiveAllocations` — The Maximum Number of Live Allocations
- L86 _public enumerator_ `AllocEvents` — The Number of Alloc Events
- L89 _public enumerator_ `FreeEvents` — The Number of Free Events
- L92 _public enumerator_ `PageInEvents` — The Number of Page In Events
- L95 _public enumerator_ `PageOutEvents` — The Number of Page Out Events
- L98 _public enumerator_ `SwapFreeEvents` — The Number of Swap Free Events
- L100 _public enumerator_ `Count`

#### struct `TraceServices::IAllocationsProvider::FQueryParams`  
`struct FQueryParams`  
_L103-110_
- L105 _public member_ `EQueryRule Rule;`
- L106 _public member_ `double TimeA;`
- L107 _public member_ `double TimeB;`
- L108 _public member_ `double TimeC;`
- L109 _public member_ `double TimeD;`

#### struct `TraceServices::IAllocationsProvider::FAllocation`  
`struct FAllocation`  
_L112-130_
- L114 _public prototype_ `uint32 GetStartEventIndex() const;`
- L115 _public prototype_ `uint32 GetEndEventIndex() const;`
- L116 _public prototype_ `double GetStartTime() const;`
- L117 _public prototype_ `double GetEndTime() const;`
- L118 _public prototype_ `uint64 GetAddress() const;`
- L119 _public prototype_ `uint64 GetSize() const;`
- L120 _public prototype_ `uint32 GetAlignment() const;`
- L121 _public prototype_ `uint32 GetAllocThreadId() const;`
- L122 _public prototype_ `uint32 GetFreeThreadId() const;`
- L123 _public prototype_ `uint32 GetAllocCallstackId() const;`
- L124 _public prototype_ `uint32 GetFreeCallstackId() const;`
- L125 _public prototype_ `uint32 GetMetadataId() const;`
- L126 _public prototype_ `TagIdType GetTag() const;`
- L127 _public prototype_ `HeapId GetRootHeap() const;`
- L128 _public prototype_ `bool IsHeap() const;`
- L129 _public prototype_ `bool IsSwap() const;`

#### class `TraceServices::IAllocationsProvider::FAllocations`  
`class FAllocations`  
_L132-138_
- L135 _public prototype_ `void operator delete (void* Address);`
- L136 _public prototype_ `uint32 Num() const;`
- L137 _public prototype_ `const FAllocation* Get(uint32 Index) const;`

#### enum `TraceServices::IAllocationsProvider::EQueryStatus`  
`enum class EQueryStatus`  
_L142-148_
- L144 _public enumerator_ `Unknown`
- L145 _public enumerator_ `Done`
- L146 _public enumerator_ `Working`
- L147 _public enumerator_ `Available`

#### struct `TraceServices::IAllocationsProvider::FQueryStatus`  
`struct FQueryStatus`  
_L150-156_
- L152 _public prototype_ `FQueryResult NextResult() const;`
- L154 _public member_ `EQueryStatus Status;`
- L155 _public member_ `mutable UPTRINT Handle;`

#### struct `TraceServices::IAllocationsProvider::FHeapSpec`  
`struct FHeapSpec`  
_L158-165_
- L160 _public member_ `HeapId Id;`
- L161 _public member_ `FHeapSpec* Parent;`
- L162 _public member_ `TArray<FHeapSpec*> Children;`
- L163 _public member_ `const TCHAR* Name;`
- L164 _public member_ `EMemoryTraceHeapFlags Flags;`

#### Free symbols / members of external scopes

- L14 _macro_ `#define UE_API TRACESERVICES_API`
- L16 _namespace_ `namespace TraceServices`
- L20 _typedef_ `typedef uint32 TagIdType;` (scope `TraceServices`) — Id type for tags
- L295 _prototype_ `FName GetAllocationsProviderName();` (scope `TraceServices`)
- L296 _prototype_ `const IAllocationsProvider* ReadAllocationsProvider(const IAnalysisSession& Session);` (scope `TraceServices`)
- L300 _function_ `inline const TCHAR* LexToString(const TraceServices::IAllocationsProvider::EQueryRule Rule)`
- L302 _typedef_ `using EQueryRule = TraceServices::IAllocationsProvider::EQueryRule;` (scope `LexToString`)

### `Source/Developer/TraceServices/Public/TraceServices/Model/AnalysisCache.h` (Public)


#### enum `TraceServices::ECacheFlags`  
`enum ECacheFlags : uint16`  
_L18-22_
- desc: Flags defining the behaviour of a cache entry
- L21 _public enumerator_ `ECacheFlags_NoGlobalCaching = 1 << 1` — When set blocks are not kept in as part of the global caching.

#### class `TraceServices::IAnalysisCache`  
`class IAnalysisCache`  
_L45-89_
- desc: Analysis cache Allows users of the system to create tracked fixed size blocks associated with a "cache id", created using a string. After creating block(s) users are free to write arbitrary data into them. Once all references to the block has been dropped the buffer is committed to persistent storage (e.g. cache file). On consecutive analysis sessions the blocks can be retrieved using the cache id and the block index. Any block can be requested at any point in the session in any order. Analysis is not thread safe and is designed to be used from the analysis thread only. The container classes \ref TraceServices::TCachedPagedArray or \ref TraceServices::FCachedStringStore are provided as user facing abstractions on top of the cache.
- L48 _public prototype_ `virtual ~IAnalysisCache() = default;`
- L53 _public member_ `constexpr static uint64 BlockSizeBytes = 8 * 1024;` — Block size in bytes
- L61 _public prototype_ `virtual FCacheId GetCacheId(const TCHAR* Name, uint16 Flags = 0) = 0;` — Returns the unique id for a named entry. If the entry does not yet exists and new id is reserved. @param Name String identifier @param Flags Details about the entry from \ref ECacheFlags. @return A valid index for the identifier
- L70 _public prototype_ `virtual FMutableMemoryView GetUserData(FCacheId CacheId) = 0;` — Gets a pointer to the user data a given cache id. The owner of the cache id is able to store arbitrary data which does not fit as block data, for example element counts. The user can write to this memory at any point during the session. The block is stored to disk at the end of the session. @param CacheId Unique cache id @return A valid memory view of the user data block, an empty view if the index was not found.
- L79 _public prototype_ `[[nodiscard]] virtual FSharedBuffer CreateBlocks(FCacheId CacheId, uint32 Count) = 0;` — Create blocks of tracked memory. The requested blocks form a contiguous memory range. The block written to disk when no more references are alive. @param CacheId Unique cache id @param Count Number of blocks to use @return Buffer mapping to the blocks. If the cache id is invalid an empty buffer is returned.
- L88 _public prototype_ `[[nodiscard]] virtual FSharedBuffer GetBlocks(FCacheId CacheId, uint32 BlockIndexStart, uint32 BlockCount = 1) = 0;` — Load blocks into memory. The requested range of blocks will be loaded into a contiguous memory range. @param CacheId Unique cache id @param BlockIndexStart Block index for this cache entry @param BlockCount Consecutive block indices to load @return Buffer mapping to the blocks. If the block range is invalid the buffer is empty.

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace TraceServices`
- L12 _typedef_ `typedef TArrayView<FMemoryView> FSegmentIterator;` (scope `TraceServices`) — An iterator for segments
- L27 _typedef_ `typedef uint32 FCacheId;` (scope `TraceServices`) — A unique id for a named cache entry.

### `Source/Developer/TraceServices/Public/TraceServices/Model/AnalysisSession.h` (Public)


#### class `TraceServices::IProvider`  
`class IProvider`  
_L28-36_
- L31 _public prototype_ `virtual ~IProvider() = default;`
- L33 _public function_ `virtual void BeginRead() const`
- L34 _public function_ `virtual void EndRead() const`
- L35 _public function_ `virtual void ReadAccessCheck() const`

#### class `TraceServices::IEditableProvider`  
`class IEditableProvider`  
_L38-46_
- L41 _public prototype_ `virtual ~IEditableProvider() = default;`
- L43 _public function_ `virtual void BeginEdit() const`
- L44 _public function_ `virtual void EndEdit() const`
- L45 _public function_ `virtual void EditAccessCheck() const`

#### struct `TraceServices::FTraceSessionMetadata`  
`struct FTraceSessionMetadata`  
_L48-65_
- L57 _public member_ `FName Name;`
- L58 _public member_ `EType Type;`
- L64 _public member_ `FString StringValue;`

#### enum `TraceServices::FTraceSessionMetadata::EType`  
`enum class EType`  
_L50-55_
- L52 _public enumerator_ `Int64`
- L53 _public enumerator_ `Double`
- L54 _public enumerator_ `String`

#### union `TraceServices::FTraceSessionMetadata::(anonymous)`  
``  
_L60-63_

#### struct `TraceServices::FAnalysisMessage`  
`struct FAnalysisMessage`  
_L67-71_
- L69 _public member_ `EMessageSeverity::Type Severity;`
- L70 _public member_ `FString Message;`

#### class `TraceServices::IAnalysisSession`  
`class IAnalysisSession`  
_L73-145_
- L76 _public prototype_ `virtual ~IAnalysisSession() = default;`
- L77 _public prototype_ `virtual void Stop(bool bAndWait=false) const = 0;`
- L78 _public prototype_ `virtual void Wait() const = 0;`
- L80 _public prototype_ `virtual const TCHAR* GetName() const = 0;`
- L81 _public prototype_ `virtual uint32 GetTraceId() const = 0;`
- L82 _public prototype_ `virtual bool IsAnalysisComplete() const = 0;`
- L84 _public prototype_ `virtual double GetDurationSeconds() const = 0;`
- L90 _public prototype_ `virtual void UpdateDurationSeconds(double Duration) = 0;` — Update the internal estimation of the session duration with a new timestamp. This function should be called with any timestamps from individual events so the full session duration can be estimated.
- L97 _public prototype_ `virtual double GetBaseDateTime() const = 0;` — Getter for the unix timestamp at the start of all analysis. This function should be used as an offset for any relative (session) timestamps to calculate real UTC timestamps.
- L98 _public prototype_ `virtual void SetBaseDateTime(double InBaseDateTime) = 0;`
- L100 _public prototype_ `virtual uint32 GetMetadataCount() const = 0;`
- L101 _public prototype_ `virtual void EnumerateMetadata(TFunctionRef<void(const FTraceSessionMetadata& Metadata)> Callback) const = 0;`
- L102 _public prototype_ `virtual void AddMetadata(FName InName, int64 InValue) = 0;`
- L103 _public prototype_ `virtual void AddMetadata(FName InName, double InValue) = 0;`
- L104 _public prototype_ `virtual void AddMetadata(FName InName, FString InValue) = 0;`
- L107 _public prototype_ `virtual uint32 GetNumPendingMessages() const = 0;` — Get the number of pending messages. Can be called without lock
- L109 _public prototype_ `virtual TArray<FAnalysisMessage> DrainPendingMessages() = 0;` — Moves pending messages to the return array.
- L111 _public prototype_ `virtual void BeginRead() const = 0;`
- L112 _public prototype_ `virtual void EndRead() const = 0;`
- L113 _public prototype_ `virtual void ReadAccessCheck() const = 0;`
- L115 _public prototype_ `virtual void BeginEdit() = 0;`
- L116 _public prototype_ `virtual void EndEdit() = 0;`
- L117 _public prototype_ `virtual void WriteAccessCheck() = 0;`
- L119 _public prototype_ `virtual ILinearAllocator& GetLinearAllocator() = 0;`
- L120 _public prototype_ `virtual IStringStore& GetStringStore() = 0;`
- L121 _public prototype_ `virtual const TCHAR* StoreString(const TCHAR* String) = 0;`
- L122 _public prototype_ `virtual const TCHAR* StoreString(const FStringView& String) = 0;`
- L124 _public prototype_ `virtual IAnalysisCache& GetCache() = 0;`
- L126 _public prototype_ `virtual void AddAnalyzer(UE::Trace::IAnalyzer* Analyzer) = 0;`
- L127 _public prototype_ `virtual void AddAnalyzer(TSharedRef<UE::Trace::IAnalyzer> Analyzer) = 0;`
- L128 _public prototype_ `virtual void AddProvider(const FName& Name, TSharedPtr<IProvider> Provider, TSharedPtr<IEditableProvider> EditableProvider = nullptr) = 0;`
- L131 _public function_ `template<typename ProviderType> const ProviderType* ReadProvider(const FName& Name) const`
- L137 _public function_ `template<typename ProviderType> ProviderType* EditProvider(const FName& Name)`
- L143 _private prototype_ `virtual const IProvider* ReadProviderPrivate(const FName& Name) const = 0;`
- L144 _private prototype_ `virtual IEditableProvider* EditProviderPrivate(const FName& Name) = 0;`

#### struct `TraceServices::FAnalysisSessionReadScope`  
`struct FAnalysisSessionReadScope`  
_L147-162_
- L149 _public function_ `FAnalysisSessionReadScope(const IAnalysisSession& InAnalysisSession) : AnalysisSession(InAnalysisSession)`
- L155 _public function_ `~FAnalysisSessionReadScope()`
- L161 _private member_ `const IAnalysisSession& AnalysisSession;`

#### struct `TraceServices::FAnalysisSessionEditScope`  
`struct FAnalysisSessionEditScope`  
_L164-178_
- L166 _public function_ `FAnalysisSessionEditScope(IAnalysisSession& InAnalysisSession) : AnalysisSession(InAnalysisSession)`
- L172 _public function_ `~FAnalysisSessionEditScope()`
- L177 _public member_ `IAnalysisSession& AnalysisSession;`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L14 _namespace_ `namespace Trace` (scope `UE`)
- L21 _namespace_ `namespace TraceServices`
- L61 _member_ `int64 Int64Value;` (scope `TraceServices::FTraceSessionMetadata::__anonb4685f9b010a`)
- L62 _member_ `double DoubleValue;` (scope `TraceServices::FTraceSessionMetadata::__anonb4685f9b010a`)

### `Source/Developer/TraceServices/Public/TraceServices/Model/Bookmarks.h` (Public)


#### struct `TraceServices::FBookmark`  
`struct FBookmark`  
_L13-18_
- L15 _public member_ `double Time;`
- L16 _public member_ `const TCHAR* Text;`
- L17 _public member_ `uint32 CallstackId;`

#### class `TraceServices::IBookmarkProvider`  
`class IBookmarkProvider : public IProvider`  
_L20-27_
- inherits: `IProvider`
- L24 _public prototype_ `virtual ~IBookmarkProvider() = default;`
- L25 _public prototype_ `virtual uint64 GetBookmarkCount() const = 0;`
- L26 _public prototype_ `virtual void EnumerateBookmarks(double IntervalStart, double IntervalEnd, TFunctionRef<void(const FBookmark&)> Callback) const = 0;`

#### class `TraceServices::IEditableBookmarkProvider`  
`class IEditableBookmarkProvider : public IEditableProvider`  
_L32-71_
- inherits: `IEditableProvider`
- desc: The interface to a provider that can consume mutations of bookmark events from a session.
- L36 _public prototype_ `virtual ~IEditableBookmarkProvider() = default;`
- L46 _public prototype_ `virtual void UpdateBookmarkSpec(uint64 BookmarkPoint, const TCHAR* FormatString, const TCHAR* File, int32 Line) = 0;` — Update the information in the Bookmark. @param BookmarkPoint	The unique identity (memory address) of the bookmark. @param FormatString	The format string of the bookmark's message. @param File			The source file the bookmark is in. @param Line			The line in the source file the bookmark is on.
- L55 _public prototype_ `virtual void AppendBookmark(uint64 BookmarkPoint, double Time, uint32 CallstackId, const uint8* FormatArgs) = 0;` — Append a new instance of a bookmark from the trace session. @param BookmarkPoint	The unique identity (memory address) of the bookmark. @param Time			The time in seconds of the event. @param FormatArgs		The arguments to use in conjunction with the spec's FormatString.
- L65 _public prototype_ `virtual void AppendBookmark(uint64 BookmarkPoint, double Time, uint32 CallstackId, const TCHAR* Text) = 0;` — Append a new instance of a bookmark from the trace session. @param BookmarkPoint	The unique identity (memory address) of the bookmark. @param Time			The time in seconds of the event. @param Text			The fully formatted bookmark string for this instance. This may vary between instances. This pointer is valid until the IAnalysisSession is deleted.
- L68 _public function_ `void AppendBookmark(uint64 BookmarkPoint, double Time, const uint8* FormatArgs)` — `UE_DEPRECATED(5.6, "Use AppendBookmark that has CallstackId parameter")`
- L70 _public function_ `void AppendBookmark(uint64 BookmarkPoint, double Time, const TCHAR* Text)` — `UE_DEPRECATED(5.6, "Use AppendBookmark that has CallstackId parameter")`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace TraceServices`
- L73 _prototype_ `FName GetBookmarkProviderName();` (scope `TraceServices`)
- L74 _prototype_ `const IBookmarkProvider& ReadBookmarkProvider(const IAnalysisSession& Session);` (scope `TraceServices`)
- L75 _prototype_ `IEditableBookmarkProvider& EditBookmarkProvider(IAnalysisSession& Session);` (scope `TraceServices`)

### `Source/Developer/TraceServices/Public/TraceServices/Model/Callstack.h` (Public)


#### struct `TraceServices::FStackFrame`  
`struct FStackFrame`  
_L17-21_
- L19 _public member_ `uint64 Addr;`
- L20 _public member_ `const FResolvedSymbol* Symbol;`

#### struct `TraceServices::FCallstack`  
`struct FCallstack`  
_L24-67_
- L27 _public prototype_ `FCallstack();` — Creates the default empty callstack (id 0).
- L30 _public prototype_ `FCallstack(uint64 Id);` — Creates an empty callstack but with a non-zero id.
- L33 _public prototype_ `FCallstack(const FStackFrame* FirstEntry, uint8 FrameCount);` — Creates an callstack initialized with a certain number of stack frames.
- L36 _public prototype_ `void Init(const FStackFrame* FirstEntry, uint8 FrameCount);` — Initializes the callstack with a certain number of stack frames.
- L39 _public prototype_ `void InitEmpty(uint64 Id);` — Initializes an empty callstack but with a non-zero id.
- L42 _public prototype_ `uint64 GetEmptyId() const;` — Gets the callstack id of an empty callstack.
- L45 _public prototype_ `bool IsEmpty() const;` — Return true if the number of stack frames is zero.
- L48 _public prototype_ `uint32 Num() const;` — Gets the number of stack frames in callstack.
- L51 _public prototype_ `uint64 Addr(uint8 Depth) const;` — Gets the address at a given stack depth.
- L54 _public prototype_ `const TCHAR* Name(uint8 Depth) const;` — Gets the cached symbol name at a given stack depth.
- L57 _public prototype_ `const FStackFrame* Frame(uint8 Depth) const;` — Gets the entire frame at given depth.
- L66 _private member_ `uint64 CallstackLenIndex;`
- L106 _function_ `inline FCallstack::FCallstack() : CallstackLenIndex(0)`
- L112 _function_ `inline FCallstack::FCallstack(uint64 Id)`
- L118 _function_ `inline FCallstack::FCallstack(const FStackFrame* InFirstFrame, uint8 InFrameCount)`
- L124 _function_ `inline void FCallstack::Init(const FStackFrame* InFirstFrame, uint8 InFrameCount)`
- L131 _function_ `inline void FCallstack::InitEmpty(uint64 Id)`
- L138 _function_ `inline uint64 FCallstack::GetEmptyId() const`
- L144 _function_ `inline bool FCallstack::IsEmpty() const`
- L150 _function_ `inline uint32 FCallstack::Num() const`
- L156 _function_ `inline uint64 FCallstack::Addr(uint8 Depth) const`
- L164 _function_ `inline const TCHAR* FCallstack::Name(uint8 Depth) const`
- L172 _function_ `inline const FStackFrame* FCallstack::Frame(uint8 Depth) const`

#### enum `TraceServices::FCallstack::(anonymous)`  
``  
_L61-64_

#### class `TraceServices::ICallstacksProvider`  
`class ICallstacksProvider : public IProvider`  
_L72-98_
- inherits: `IProvider`
- L76 _public prototype_ `virtual ~ICallstacksProvider() = default;`
- L83 _public prototype_ `virtual const FCallstack* GetCallstack(uint32 CallstackId) const = 0;` — Queries a callstack id. @param CallstackId Callstack id to query. @return Callstack information. If id is not found a special "Unknown" callstack is returned.
- L90 _public prototype_ `virtual void GetCallstacks(const TArrayView<uint32>& CallstackIds, FCallstack const** OutCallstacks) const = 0;` — Queries a set of callstack ids. @param CallstackIds List of callstack ids to query @param OutCallstacks Output list of callstacks. Caller is responsible for allocating space according to CallstackIds length.
- L97 _public prototype_ `virtual uint32 GetCallstackIdForHash(uint64 CallstackHash) const = 0;` — Gets a callstack id for a registered callstack hash. @param CallstackHash The callstack hash. @returns The callstack id.

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API TRACESERVICES_API`
- L13 _namespace_ `namespace TraceServices`
- L62 _enumerator_ `EntryLenShift = 56` (scope `TraceServices::FCallstack::__anonc15c38e50103`)
- L63 _enumerator_ `EntryLenMask = uint64(0xff) << EntryLenShift` (scope `TraceServices::FCallstack::__anonc15c38e50103`)
- L102 _prototype_ `FName GetCallstacksProviderName();` (scope `TraceServices`)
- L103 _prototype_ `const ICallstacksProvider* ReadCallstacksProvider(const IAnalysisSession& Session);` (scope `TraceServices`)

### `Source/Developer/TraceServices/Public/TraceServices/Model/Channel.h` (Public)


#### struct `TraceServices::FChannelEntry`  
`struct FChannelEntry`  
_L14-20_
- L16 _public member_ `uint32 Id;`
- L17 _public member_ `FString Name;`
- L18 _public member_ `bool bIsEnabled;`
- L19 _public member_ `bool bReadOnly;`

#### class `TraceServices::IChannelProvider`  
`class IChannelProvider : public IProvider`  
_L22-30_
- inherits: `IProvider`
- L26 _public prototype_ `virtual ~IChannelProvider() = default;`
- L27 _public prototype_ `virtual uint64 GetChannelCount() const = 0;`
- L28 _public prototype_ `virtual const TArray<FChannelEntry>& GetChannels() const = 0;`
- L29 _public prototype_ `virtual FDateTime GetTimeStamp() const = 0;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace TraceServices`
- L32 _prototype_ `FName GetChannelProviderName();` (scope `TraceServices`)
- L33 _prototype_ `const IChannelProvider* ReadChannelProvider(const IAnalysisSession& Session);` (scope `TraceServices`)

### `Source/Developer/TraceServices/Public/TraceServices/Model/ContextSwitches.h` (Public)


#### struct `TraceServices::FContextSwitch`  
`struct FContextSwitch`  
_L13-18_
- L15 _public member_ `double Start;`
- L16 _public member_ `double End;`
- L17 _public member_ `uint32 CoreNumber;`

#### struct `TraceServices::FCpuCoreInfo`  
`struct FCpuCoreInfo`  
_L20-23_
- L22 _public member_ `uint32 CoreNumber;`

#### struct `TraceServices::FCpuCoreEvent`  
`struct FCpuCoreEvent`  
_L25-30_
- L27 _public member_ `double Start;`
- L28 _public member_ `double End;`
- L29 _public member_ `uint32 SystemThreadId;`

#### enum `TraceServices::EContextSwitchEnumerationResult`  
`enum class EContextSwitchEnumerationResult`  
_L32-36_
- L34 _public enumerator_ `Continue`
- L35 _public enumerator_ `Stop`

#### class `TraceServices::IContextSwitchesProvider`  
`class IContextSwitchesProvider : public IProvider`  
_L38-59_
- inherits: `IProvider`
- L42 _public typedef_ `typedef TFunctionRef<void(const FCpuCoreInfo&)> CpuCoreCallback;`
- L43 _public typedef_ `typedef TFunctionRef<EContextSwitchEnumerationResult(const FCpuCoreEvent&)> CpuCoreEventCallback;`
- L44 _public typedef_ `typedef TFunctionRef<EContextSwitchEnumerationResult(const FContextSwitch&)> ContextSwitchCallback;`
- L46 _public prototype_ `virtual ~IContextSwitchesProvider() = default;`
- L47 _public prototype_ `virtual bool HasData() const = 0;`
- L48 _public prototype_ `virtual bool GetSystemThreadId(uint32 ThreadId, uint32& OutSystemThreadId) const = 0;`
- L49 _public prototype_ `virtual bool GetThreadId(uint32 SystemThreadId, uint32& OutThreadId) const = 0;`
- L50 _public prototype_ `virtual bool GetSystemThreadId(uint32 CoreNumber, double Time, uint32& OutSystemThreadId) const = 0;`
- L51 _public prototype_ `virtual bool GetThreadId(uint32 CoreNumber, double Time, uint32& OutThreadId) const = 0;`
- L52 _public prototype_ `virtual bool GetCoreNumber(uint32 ThreadId, double Time, uint32& OutCoreNumber) const = 0;`
- L53 _public prototype_ `virtual uint64 GetThreadsSerial() const = 0;`
- L54 _public prototype_ `virtual uint64 GetCpuCoresSerial() const = 0;`
- L55 _public prototype_ `virtual void EnumerateCpuCores(CpuCoreCallback Callback) const = 0;`
- L56 _public prototype_ `virtual void EnumerateCpuCoreEvents(uint32 CoreNumber, double StartTime, double EndTime, CpuCoreEventCallback Callback) const = 0;`
- L57 _public prototype_ `virtual void EnumerateCpuCoreEventsBackwards(uint32 CoreNumber, double EndTime, double StartTime, CpuCoreEventCallback Callback) const = 0;`
- L58 _public prototype_ `virtual void EnumerateContextSwitches(uint32 ThreadId, double StartTime, double EndTime, ContextSwitchCallback Callback) const = 0;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace TraceServices`
- L61 _prototype_ `FName GetContextSwitchesProviderName();` (scope `TraceServices`)
- L62 _prototype_ `const IContextSwitchesProvider* ReadContextSwitchesProvider(const IAnalysisSession& Session);` (scope `TraceServices`)

### `Source/Developer/TraceServices/Public/TraceServices/Model/CookProfilerProvider.h` (Public)


#### struct `TraceServices::FPackageData`  
`struct FPackageData`  
_L14-33_
- L16 _public prototype_ `FPackageData(uint64 InId);`
- L17 _public member_ `uint64 Id = -1;`
- L18 _public member_ `const TCHAR* Name;`
- L20 _public member_ `double LoadTimeIncl = 0;`
- L21 _public member_ `double LoadTimeExcl = 0;`
- L23 _public member_ `double SaveTimeIncl = 0;`
- L24 _public member_ `double SaveTimeExcl = 0;`
- L26 _public member_ `double BeginCacheForCookedPlatformDataIncl = 0;` — BeginCacheForCookedPlatformData is the name of the function from the cooker.
- L27 _public member_ `double BeginCacheForCookedPlatformDataExcl = 0;`
- L29 _public member_ `double IsCachedCookedPlatformDataLoadedIncl = 0;` — IsCachedCookedPlatformDataLoaded is the name of the function from the cooker.
- L30 _public member_ `double IsCachedCookedPlatformDataLoadedExcl = 0;`
- L32 _public member_ `const TCHAR* AssetClass;`

#### class `TraceServices::ICookProfilerProvider`  
`class ICookProfilerProvider : public IProvider`  
_L35-50_
- inherits: `IProvider`
- L38 _public typedef_ `typedef TFunctionRef<bool(const FPackageData& )> EnumeratePackagesCallback;`
- L40 _public prototype_ `virtual ~ICookProfilerProvider() = default;`
- L42 _public prototype_ `virtual void BeginRead() const = 0;`
- L43 _public prototype_ `virtual void EndRead() const = 0;`
- L44 _public prototype_ `virtual void ReadAccessCheck() const = 0;`
- L46 _public prototype_ `virtual uint32 GetNumPackages() const = 0;`
- L47 _public prototype_ `virtual void EnumeratePackages(double StartTime, double EndTime, EnumeratePackagesCallback Callback) const = 0;`
- L49 _public prototype_ `virtual void CreateAggregation(TArray64<FPackageData>& OutPackages) const = 0;`

#### class `TraceServices::IEditableCookProfilerProvider`  
`class IEditableCookProfilerProvider : public IEditableProvider`  
_L52-64_
- inherits: `IEditableProvider`
- L55 _public prototype_ `virtual ~IEditableCookProfilerProvider() = default;`
- L57 _public prototype_ `virtual void BeginEdit() const = 0;`
- L58 _public prototype_ `virtual void EndEdit() const = 0;`
- L59 _public prototype_ `virtual void EditAccessCheck() const = 0;`
- L61 _public prototype_ `virtual FPackageData* EditPackage(uint64 Id) = 0;`
- L63 _public prototype_ `virtual void AddScopeEntry(uint32 ThreadId, uint64 InPackageId, double Timestamp, EPackageEventStatType InType, bool InIsEnterScope) = 0;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace TraceServices`
- L66 _prototype_ `FName GetCookProfilerProviderName();` (scope `TraceServices`)
- L67 _prototype_ `const ICookProfilerProvider* ReadCookProfilerProvider(const IAnalysisSession& Session);` (scope `TraceServices`)
- L68 _prototype_ `IEditableCookProfilerProvider* EditCookProfilerProvider(IAnalysisSession& Session);` (scope `TraceServices`)

### `Source/Developer/TraceServices/Public/TraceServices/Model/Counters.h` (Public)


#### enum `TraceServices::ECounterDisplayHint`  
`enum ECounterDisplayHint`  
_L13-19_
- L15 _public enumerator_ `CounterDisplayHint_None`
- L16 _public enumerator_ `CounterDisplayHint_Memory`
- L17 _public enumerator_ `CounterDisplayHint_Bandwidth`
- L18 _public enumerator_ `CounterDisplayHint_Percent`

#### enum `TraceServices::ECounterOpType`  
`enum class ECounterOpType : uint8`  
_L21-25_
- L23 _public enumerator_ `Set = 0`
- L24 _public enumerator_ `Add = 1`

#### class `TraceServices::ICounter`  
`class ICounter`  
_L27-42_
- L30 _public prototype_ `virtual ~ICounter() = default;`
- L32 _public prototype_ `virtual const TCHAR* GetName() const = 0;`
- L33 _public prototype_ `virtual const TCHAR* GetGroup() const = 0;`
- L34 _public prototype_ `virtual const TCHAR* GetDescription() const = 0;`
- L35 _public prototype_ `virtual bool IsFloatingPoint() const = 0;`
- L36 _public function_ `virtual bool IsResetEveryFrame() const`
- L37 _public prototype_ `virtual ECounterDisplayHint GetDisplayHint() const = 0;`
- L38 _public prototype_ `virtual void EnumerateValues(double IntervalStart, double IntervalEnd, bool bIncludeExternalBounds, TFunctionRef<void(double, int64)> Callback) const = 0;`
- L39 _public prototype_ `virtual void EnumerateFloatValues(double IntervalStart, double IntervalEnd, bool bIncludeExternalBounds, TFunctionRef<void(double, double)> Callback) const = 0;`
- L40 _public prototype_ `virtual void EnumerateOps(double IntervalStart, double IntervalEnd, bool bIncludeExternalBounds, TFunctionRef<void(double, ECounterOpType, int64)> Callback) const = 0;`
- L41 _public prototype_ `virtual void EnumerateFloatOps(double IntervalStart, double IntervalEnd, bool bIncludeExternalBounds, TFunctionRef<void(double, ECounterOpType, double)> Callback) const = 0;`

#### class `TraceServices::IEditableCounter`  
`class IEditableCounter`  
_L49-127_
- desc: An interface that can consume mutations of the state of a counter.
- L52 _public prototype_ `virtual ~IEditableCounter() = default;`
- L59 _public prototype_ `virtual void SetName(const TCHAR* Name) = 0;` — Sets the name of the counter. @param Name	The name of the counter.
- L66 _public prototype_ `virtual void SetGroup(const TCHAR* Group) = 0;` — Sets the group of the counter. @param Group	The group name of the counter.
- L73 _public prototype_ `virtual void SetDescription(const TCHAR* Description) = 0;` — Sets the description of the counter. @param Description	The description of the counter.
- L80 _public prototype_ `virtual void SetIsFloatingPoint(bool bIsFloatingPoint) = 0;` — Sets whether the counter is an integral or floating point number. @param bIsFloatingPoint	True if the counter is floating point, false if it is integral.
- L87 _public prototype_ `virtual void SetIsResetEveryFrame(bool bInIsResetEveryFrame) = 0;` — Sets whether the counter value is reset every frame. This can be used for counters polled from stats. @param bInIsResetEveryFrame	True if the counter is reset every frame.
- L94 _public prototype_ `virtual void SetDisplayHint(ECounterDisplayHint DisplayHint) = 0;` — Sets the display hint for this counter. @param DisplayHint	The display hint for this counter.
- L102 _public prototype_ `virtual void AddValue(double Time, int64 Value) = 0;` — Add a value to the value counter. @param Time	The time at which the value was added in seconds. @param Value	The value to add to the current value of the counter.
- L110 _public prototype_ `virtual void AddValue(double Time, double Value) = 0;` — Add a value to the value counter. @param Time	The time at which the value was added in seconds. @param Value	The value to add to the current value of the counter.
- L118 _public prototype_ `virtual void SetValue(double Time, int64 Value) = 0;` — Set the value of the counter. @param Time	The time at which the value was set in seconds. @param Value	The new value for the counter.
- L126 _public prototype_ `virtual void SetValue(double Time, double Value) = 0;` — Set the value of the counter. @param Time	The time at which the value was set in seconds. @param Value	The new value for the counter.

#### class `TraceServices::ICounterProvider`  
`class ICounterProvider : public IProvider`  
_L129-137_
- inherits: `IProvider`
- L133 _public prototype_ `virtual ~ICounterProvider() = default;`
- L134 _public prototype_ `virtual uint64 GetCounterCount() const = 0;`
- L135 _public prototype_ `virtual bool ReadCounter(uint32 CounterId, TFunctionRef<void(const ICounter&)> Callback) const = 0;`
- L136 _public prototype_ `virtual void EnumerateCounters(TFunctionRef<void(uint32, const ICounter&)> Callback) const = 0;`

#### class `TraceServices::IEditableCounterProvider`  
`class IEditableCounterProvider : public IEditableProvider`  
_L142-167_
- inherits: `IEditableProvider`
- desc: The interface to a provider that can consume mutations of counter events from a session.
- L146 _public prototype_ `virtual ~IEditableCounterProvider() = default;`
- L154 _public prototype_ `virtual const ICounter* GetCounter(IEditableCounter* EditableCounter) = 0;` — Retrieve the counter interface to an editable counter. @return The interface the counter. This can be null if the provider doesn't care about deriving new counters from existing editable counters.
- L161 _public prototype_ `virtual IEditableCounter* CreateEditableCounter() = 0;` — Create a new counter mutation interface. @return The interface to mutate the counter.
- L166 _public prototype_ `virtual void AddCounter(const ICounter* Counter) = 0;` — Add a custom counter to the provider.

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace TraceServices`
- L169 _prototype_ `FName GetCounterProviderName();` (scope `TraceServices`)
- L170 _prototype_ `const ICounterProvider& ReadCounterProvider(const IAnalysisSession& Session);` (scope `TraceServices`)
- L171 _prototype_ `IEditableCounterProvider& EditCounterProvider(IAnalysisSession& Session);` (scope `TraceServices`)

### `Source/Developer/TraceServices/Public/TraceServices/Model/CsvProfilerProvider.h` (Public)


#### struct `TraceServices::FCaptureInfo`  
`struct FCaptureInfo`  
_L16-22_
- L18 _public member_ `const TMap<const TCHAR*, const TCHAR*, FDefaultSetAllocator, TStringPointerMapKeyFuncs_DEPRECATED<const TCHAR*, const TCHAR*>>& Metadata;`
- L19 _public member_ `const TCHAR* Filename = nullptr;`
- L20 _public member_ `uint32 Id = uint32(-1);`
- L21 _public member_ `uint32 FrameCount = 0;`

#### class `TraceServices::ICsvProfilerProvider`  
`class ICsvProfilerProvider : public IProvider`  
_L24-31_
- inherits: `IProvider`
- L28 _public prototype_ `virtual ~ICsvProfilerProvider() = default;`
- L29 _public prototype_ `virtual void EnumerateCaptures(TFunctionRef<void(const FCaptureInfo&)> Callback) const = 0;`
- L30 _public prototype_ `virtual const IUntypedTable& GetTable(uint32 CaptureId) const = 0;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace TraceServices`
- L33 _prototype_ `FName GetCsvProfilerProviderName();` (scope `TraceServices`)
- L34 _prototype_ `const ICsvProfilerProvider* ReadCsvProfilerProvider(const IAnalysisSession& Session);` (scope `TraceServices`)

### `Source/Developer/TraceServices/Public/TraceServices/Model/Definitions.h` (Public)


#### class `TraceServices::IDefinitionProvider`  
`class IDefinitionProvider : public IProvider , public IEditableProvider`  
_L35-111_
- inherits: `IProvider,IEditableProvider`
- desc: Allows users to publish "definitions", structs representing a definition event. This data can then be queried when resolving a reference field in another event. \note If your definition type reference other definitions it is encouraged to resolve those during analysis to avoid having to resolve complex chains on every lookup. Example usage: This code creates a definition, initializes the instance, resolves a reference and finally registers it. \code FMyDefinitionClass* Instance = DefinitionProvider->Create<FMyDefinitionClass>(); Instance->SomeValue = EventData.GetValue<uint32>("SomeValue"); const FEventRef Reference = EventData.GetReferenceValue("SomeString"); Instance->SomeString = DefinitionProvider->Get<FStringDefinition>(Reference)->Display; ... const UE::Trace::FEventRef Id(EventData.GetDefinitionId(), EventData.GetTypeInfo().GetId()); DefinitionProvider->Register<FMyDefinitionClass>(Instance, Id); \endcode
- L40 _public prototype_ `virtual ~IDefinitionProvider() = default;`
- L51 _public function_ `template<typename T> T* Create()` — Allocates memory for the definition. The memory is guaranteed to be valid during the lifetime of the analysis session. @return Pointer to zeroed memory enough to hold an instance of T.
- L65 _public function_ `template<typename T, typename DefinitionType> void Register(const T* Instance, const UE::Trace::TEventRef<DefinitionType>& Id)` — Makes the instance of a definition visible to queries. @param Instance Pointer to the instance @param Id Id that should be used to reference the definition.
- L80 _public function_ `template<typename T, typename DefinitionType> const T* Get(const UE::Trace::TEventRef<DefinitionType>& Reference) const` — Attempts to retrieve a previously registered instance of a definition using a reference. @param Reference Id used to uniquely identify the definition. @return Pointer to the definition or null if the id was not found.
- L92 _public function_ `template<typename DefinitionType> FString GetAsString(const UE::Trace::TEventRef<DefinitionType>& Reference) const` — Gets the definition as a owned string. @param Reference Id used to uniquely identify the definition. @return A string describing the referenced value
- L104 _protected prototype_ `virtual void* Allocate(uint32 Size, uint32 Alignment) = 0;`
- L105 _protected prototype_ `virtual void AddEntry(uint64 Hash, const void* Ptr) = 0;`
- L106 _protected prototype_ `virtual const void* FindEntry(uint64 Hash) const = 0;`
- L109 _protected typedef_ `using StringifierFn = TFunction<FString (const void*)>;`
- L110 _protected member_ `TMap<uint32, StringifierFn> Stringifiers;`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace TraceServices`
- L113 _prototype_ `FName GetDefinitionProviderName();` (scope `TraceServices`)
- L114 _prototype_ `const IDefinitionProvider* ReadDefinitionProvider(const IAnalysisSession& Session);` (scope `TraceServices`)
- L115 _prototype_ `IDefinitionProvider* EditDefinitionProvider(IAnalysisSession& Session);` (scope `TraceServices`)

### `Source/Developer/TraceServices/Public/TraceServices/Model/Diagnostics.h` (Public)


#### struct `TraceServices::FSessionInfo`  
`struct FSessionInfo`  
_L14-28_
- L16 _public member_ `FString Platform;`
- L17 _public member_ `FString AppName;`
- L18 _public member_ `FString ProjectName;`
- L19 _public member_ `FString EngineVersion;`
- L20 _public member_ `FString BuildVersion;`
- L21 _public member_ `FString Branch;`
- L22 _public member_ `FString CommandLine;`
- L23 _public member_ `FString VFSPaths;`
- L24 _public member_ `uint32 Changelist = 0;`
- L25 _public member_ `EBuildConfiguration ConfigurationType = EBuildConfiguration::Unknown;`
- L26 _public member_ `EBuildTargetType TargetType = EBuildTargetType::Unknown;`
- L27 _public member_ `FGuid InstanceId;`

#### class `TraceServices::IDiagnosticsProvider`  
`class IDiagnosticsProvider : public IProvider`  
_L30-38_
- inherits: `IProvider`
- L33 _public prototype_ `virtual ~IDiagnosticsProvider() = default;`
- L35 _public prototype_ `virtual bool IsSessionInfoAvailable() const = 0;`
- L37 _public prototype_ `virtual const FSessionInfo& GetSessionInfo() const = 0;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace TraceServices`
- L40 _prototype_ `FName GetDiagnosticsProviderName();` (scope `TraceServices`)
- L41 _prototype_ `const IDiagnosticsProvider* ReadDiagnosticsProvider(const IAnalysisSession& Session);` (scope `TraceServices`)

### `Source/Developer/TraceServices/Public/TraceServices/Model/Frames.h` (Public)


#### struct `TraceServices::FFrame`  
`struct FFrame`  
_L16-22_
- L18 _public member_ `uint64 Index;`
- L19 _public member_ `double StartTime;`
- L20 _public member_ `double EndTime;`
- L21 _public member_ `ETraceFrameType FrameType;`

#### class `TraceServices::IFrameProvider`  
`class IFrameProvider : public IProvider`  
_L24-88_
- inherits: `IProvider`
- L28 _public prototype_ `virtual ~IFrameProvider() = default;`
- L35 _public prototype_ `virtual uint64 GetFrameCount(ETraceFrameType FrameType) const = 0;` — Gets the number of frames, for the specified frame type. @param FrameType - type of frames @returns number of frames
- L44 _public prototype_ `virtual void EnumerateFrames(ETraceFrameType FrameType, uint64 Start, uint64 End, TFunctionRef<void(const FFrame&)> Callback) const = 0;` — Enumerates frames in the [Start, End) index range, for the specified frame type. @param FrameType - type of frames @param Start     - inclusive start index @param End       - exclusive end index @param Callback  - a callback called for each frame
- L53 _public prototype_ `virtual void EnumerateFrames(ETraceFrameType FrameType, double StartTime, double EndTime, TFunctionRef<void(const FFrame&)> Callback) const = 0;` — Enumerate frames whose duration intersects [StartTime, EndTime]. @param FrameType	The frame type to enumerate. @param StartTime	The start timestamp in seconds. @param EndTime	The end timestamp in seconds. @param Callback	The callback to be called for each frame.
- L60 _public prototype_ `virtual const TArray64<double>& GetFrameStartTimes(ETraceFrameType FrameType) const = 0;` — Gets the array of frame start times, for the specified frame type. @param FrameType - type of frames @returns a const reference to array of time values
- L70 _public prototype_ `virtual bool GetFrameFromTime(ETraceFrameType FrameType, double Time, FFrame& OutFrame) const = 0;` — Gets the first frame with start time <= specified time, for the specified frame type. Note: This function does not check the end time of frames. @param FrameType - type of frames @param Time      - time value, in seconds @param OutFrame  - the output frame, if this function returns true @returns true if there is a frame with start time <= time or false otherwise
- L78 _public prototype_ `virtual const FFrame* GetFrame(ETraceFrameType FrameType, uint64 Index) const = 0;` — Gets the frame at the specified index, for the specified frame type. @param FrameType - type of frames @param Index     - frame index @returns a const pointer to the frame or nullptr if index is invalid
- L87 _public prototype_ `virtual uint32 GetFrameNumberForTimestamp(ETraceFrameType FrameType, double Time) const = 0;` — Gets the index of the first frame with start time <= specified time, for the specified frame type. Note: This function does not check the end time of frames. @param FrameType - type of frames @param Time      - time value, in seconds @returns index of the first frame with start time <= time; also returns 0 when time < start time of the first frame or if frame count is zero

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace TraceServices`
- L90 _prototype_ `FName GetFrameProviderName();` (scope `TraceServices`)
- L91 _prototype_ `const IFrameProvider& ReadFrameProvider(const IAnalysisSession& Session);` (scope `TraceServices`)

### `Source/Developer/TraceServices/Public/TraceServices/Model/LoadTimeProfiler.h` (Public)


#### struct `TraceServices::FFileInfo`  
`struct FFileInfo`  
_L19-23_
- L21 _public member_ `uint32 Id = uint32(-1);`
- L22 _public member_ `const TCHAR* Path = nullptr;`

#### enum `TraceServices::EFileActivityType`  
`enum EFileActivityType`  
_L25-35_
- L27 _public enumerator_ `FileActivityType_Open`
- L28 _public enumerator_ `FileActivityType_ReOpen`
- L29 _public enumerator_ `FileActivityType_Close`
- L30 _public enumerator_ `FileActivityType_Read`
- L31 _public enumerator_ `FileActivityType_Write`
- L33 _public enumerator_ `FileActivityType_Count`
- L34 _public enumerator_ `FileActivityType_Invalid = FileActivityType_Count`

#### struct `TraceServices::FFileActivity`  
`struct FFileActivity`  
_L39-52_
- L41 _public member_ `const FFileInfo* File = nullptr;`
- L42 _public member_ `double StartTime = 0.0;`
- L43 _public member_ `double EndTime = 0.0;`
- L44 _public member_ `uint64 Offset = 0;`
- L45 _public member_ `uint64 Size = 0;`
- L46 _public member_ `uint64 ActualSize = 0;`
- L47 _public member_ `uint32 ThreadId = 0;`
- L48 _public member_ `EFileActivityType ActivityType = FileActivityType_Invalid;`
- L49 _public member_ `bool Failed = false;`
- L50 _public member_ `uint64 FileHandle;`
- L51 _public member_ `uint64 ReadWriteHandle;`

#### class `TraceServices::IFileActivityProvider`  
`class IFileActivityProvider : public IProvider`  
_L54-63_
- inherits: `IProvider`
- L58 _public typedef_ `typedef ITimeline<FFileActivity*> Timeline;`
- L60 _public prototype_ `virtual ~IFileActivityProvider() = default;`
- L61 _public prototype_ `virtual void EnumerateFileActivity(TFunctionRef<bool(const FFileInfo&, const Timeline&)> Callback) const = 0;`
- L62 _public prototype_ `virtual const ITable<FFileActivity>& GetFileActivityTable() const = 0;`

#### struct `TraceServices::FPackageSummaryInfo`  
`struct FPackageSummaryInfo`  
_L65-71_
- L67 _public member_ `uint32 TotalHeaderSize = 0;`
- L68 _public member_ `uint32 ImportCount = 0;`
- L69 _public member_ `uint32 ExportCount = 0;`
- L70 _public member_ `int32 Priority = 0;`

#### struct `TraceServices::FClassInfo`  
`struct FClassInfo`  
_L73-76_
- L75 _public member_ `const TCHAR* Name;`

#### struct `TraceServices::FPackageExportInfo`  
`struct FPackageExportInfo`  
_L80-86_
- L82 _public member_ `uint32 Id;`
- L83 _public member_ `const FClassInfo* Class = nullptr;`
- L84 _public member_ `uint64 SerialSize = 0;`
- L85 _public member_ `const FPackageInfo* Package = nullptr;`

#### struct `TraceServices::FPackageInfo`  
`struct FPackageInfo`  
_L88-97_
- L90 _public member_ `uint32 Id;`
- L91 _public member_ `const TCHAR* Name = nullptr;`
- L92 _public member_ `FPackageSummaryInfo Summary;`
- L93 _public member_ `TArray<const FPackageInfo*> ImportedPackages;`
- L94 _public member_ `TArray<const FPackageExportInfo*> Exports;`
- L95 _public member_ `uint64 TotalExportsSerialSize = 0;`
- L96 _public member_ `uint64 RequestId = 0;`

#### struct `TraceServices::FLoadRequest`  
`struct FLoadRequest`  
_L99-107_
- L101 _public member_ `uint64 Id = 0;`
- L102 _public member_ `const TCHAR* Name = nullptr;`
- L103 _public member_ `uint32 ThreadId = uint32(-1);`
- L104 _public member_ `double StartTime = 0.0;`
- L105 _public member_ `double EndTime = 0.0;`
- L106 _public member_ `TArray<const FPackageInfo*> Packages;`

#### enum `TraceServices::ELoadTimeProfilerObjectEventType`  
`enum ELoadTimeProfilerObjectEventType`  
_L109-115_
- L111 _public enumerator_ `LoadTimeProfilerObjectEventType_Create`
- L112 _public enumerator_ `LoadTimeProfilerObjectEventType_Serialize`
- L113 _public enumerator_ `LoadTimeProfilerObjectEventType_PostLoad`
- L114 _public enumerator_ `LoadTimeProfilerObjectEventType_None`

#### struct `TraceServices::FExportsTableRow`  
`struct FExportsTableRow`  
_L117-124_
- L119 _public member_ `const FPackageExportInfo* ExportInfo = nullptr;`
- L120 _public member_ `uint64 SerializedSize = 0;`
- L121 _public member_ `double MainThreadTime = 0.0;`
- L122 _public member_ `double AsyncLoadingThreadTime = 0.0;`
- L123 _public member_ `ELoadTimeProfilerObjectEventType EventType = LoadTimeProfilerObjectEventType_None;`

#### struct `TraceServices::FPackagesTableRow`  
`struct FPackagesTableRow`  
_L126-135_
- L128 _public member_ `const FPackageInfo* PackageInfo = nullptr;`
- L129 _public member_ `uint64 TotalSerializedSize = 0;`
- L130 _public member_ `uint64 SerializedHeaderSize = 0;`
- L131 _public member_ `uint64 SerializedExportsCount = 0;`
- L132 _public member_ `uint64 SerializedExportsSize = 0;`
- L133 _public member_ `double MainThreadTime = 0.0;`
- L134 _public member_ `double AsyncLoadingThreadTime = 0.0;`

#### struct `TraceServices::FRequestsTableRow`  
`struct FRequestsTableRow`  
_L137-144_
- L139 _public member_ `uint64 Id = 0;`
- L140 _public member_ `const TCHAR* Name = nullptr;`
- L141 _public member_ `double StartTime = 0.0;`
- L142 _public member_ `double Duration = 0.0;`
- L143 _public member_ `TArray<const FPackageInfo*> Packages;`

#### struct `TraceServices::FLoadTimeProfilerCpuEvent`  
`struct FLoadTimeProfilerCpuEvent`  
_L146-151_
- L148 _public member_ `const FPackageInfo* Package = nullptr;`
- L149 _public member_ `const FPackageExportInfo* Export = nullptr;`
- L150 _public member_ `ELoadTimeProfilerObjectEventType EventType = LoadTimeProfilerObjectEventType_None;`

#### struct `TraceServices::FLoadTimeProfilerAggregatedStats`  
`struct FLoadTimeProfilerAggregatedStats`  
_L153-162_
- L155 _public member_ `const TCHAR* Name;`
- L156 _public member_ `uint64 Count;`
- L157 _public member_ `double Total;`
- L158 _public member_ `double Min;`
- L159 _public member_ `double Max;`
- L160 _public member_ `double Average;`
- L161 _public member_ `double Median;`

#### class `TraceServices::ILoadTimeProfilerProvider`  
`class ILoadTimeProfilerProvider : public IProvider`  
_L166-182_
- inherits: `IProvider`
- L170 _public typedef_ `typedef ITimeline<FLoadTimeProfilerCpuEvent> CpuTimeline;`
- L172 _public prototype_ `virtual ~ILoadTimeProfilerProvider() = default;`
- L173 _public prototype_ `virtual uint32 GetTimelineCount() const = 0;`
- L174 _public prototype_ `virtual bool GetCpuThreadTimelineIndex(uint32 ThreadId, uint32& OutTimelineIndex) const = 0;`
- L175 _public prototype_ `virtual bool ReadTimeline(uint32 Index, TFunctionRef<void(const CpuTimeline&)> Callback) const = 0;`
- L176 _public prototype_ `virtual ITable<FLoadTimeProfilerAggregatedStats>* CreateEventAggregation(double IntervalStart, double IntervalEnd) const = 0;`
- L177 _public prototype_ `virtual ITable<FLoadTimeProfilerAggregatedStats>* CreateObjectTypeAggregation(double IntervalStart, double IntervalEnd) const = 0;`
- L178 _public prototype_ `virtual ITable<FPackagesTableRow>* CreatePackageDetailsTable(double IntervalStart, double IntervalEnd) const = 0;`
- L179 _public prototype_ `virtual ITable<FExportsTableRow>* CreateExportDetailsTable(double IntervalStart, double IntervalEnd) const = 0;`
- L180 _public prototype_ `virtual ITable<FRequestsTableRow>* CreateRequestsTable(double IntervalStart, double IntervalEnd) const = 0;`
- L181 _public prototype_ `virtual const ITable<FLoadRequest>& GetRequestsTable() const = 0;`

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace TraceServices`
- L37 _prototype_ `const TCHAR* GetFileActivityTypeString(EFileActivityType ActivityType);` (scope `TraceServices`)
- L164 _prototype_ `const TCHAR* GetLoadTimeProfilerObjectEventTypeString(ELoadTimeProfilerObjectEventType EventType);` (scope `TraceServices`)
- L184 _prototype_ `FName GetLoadTimeProfilerProviderName();` (scope `TraceServices`)
- L185 _prototype_ `const ILoadTimeProfilerProvider* ReadLoadTimeProfilerProvider(const IAnalysisSession& Session);` (scope `TraceServices`)
- L187 _prototype_ `FName GetFileActivityProviderName();` (scope `TraceServices`)
- L188 _prototype_ `const IFileActivityProvider* ReadFileActivityProvider(const IAnalysisSession& Session);` (scope `TraceServices`)

### `Source/Developer/TraceServices/Public/TraceServices/Model/Log.h` (Public)


#### struct `TraceServices::FLogCategoryInfo`  
`struct FLogCategoryInfo`  
_L16-20_
- L18 _public member_ `const TCHAR* Name = nullptr;`
- L19 _public member_ `ELogVerbosity::Type DefaultVerbosity;`

#### struct `TraceServices::FLogMessageInfo`  
`struct FLogMessageInfo`  
_L22-31_
- L24 _public member_ `uint64 Index;`
- L25 _public member_ `double Time;`
- L26 _public member_ `const FLogCategoryInfo* Category = nullptr;`
- L27 _public member_ `const TCHAR* File = nullptr;`
- L28 _public member_ `const TCHAR* Message = nullptr;`
- L29 _public member_ `int32 Line;`
- L30 _public member_ `ELogVerbosity::Type Verbosity;`

#### class `TraceServices::ILogProvider`  
`class ILogProvider : public IProvider`  
_L33-172_
- inherits: `IProvider`
- L37 _public prototype_ `virtual ~ILogProvider() = default;`
- L44 _public prototype_ `virtual uint64 GetMessageCount() const = 0;` — Gets the number of log messages. @returns The current number of log messages.
- L55 _public prototype_ `virtual bool ReadMessage(uint64 Index, TFunctionRef<void(const FLogMessageInfo&)> Callback) const = 0;` — Reads information for a single message specified by index. @param Index The index of the message to read. @param Callback The function to be called with the log message's information. @returns Whether Index is valid or not. @note The current number of messages could be different than the value returned by the last call to GetMessageCount().
- L66 _public prototype_ `virtual void EnumerateMessagesByIndex(uint64 StartIndex, uint64 EndIndex, TFunctionRef<void(const FLogMessageInfo&)> Callback) const = 0;` — Enumerates messages in the specified index interval [StartIndex, EndIndex). @param StartIndex The inclusive start index of the interval. @param EndIndex The exclusive end index of the interval. @param Callback The function to be called for each log message with the message's information. @note The current number of messages could be different than the value returned by the last call to GetMessageCount().
- L77 _public prototype_ `virtual void EnumerateMessages(double StartTime, double EndTime, TFunctionRef<void(const FLogMessageInfo&)> Callback) const = 0;` — Enumerates messages with timestamp in the specified time interval [StartTime, EndTime]. @param StartTime The inclusive start time of the interval. @param EndTime The inclusive end time of the interval. @param Callback The function to be called for each log message with the message's information. @note The current number of messages could be different than the value returned by the last call to GetMessageCount().
- L89 _public prototype_ `virtual void ReverseEnumerateMessages(double StartTime, double EndTime, TFunctionRef<bool(const FLogMessageInfo&)> Callback) const = 0;` — Enumerates messages in reverse with timestamp in the specified time interval [EndTime, StartTime] until either it finds the last message or is stopped on callback. @param StartTime The inclusive start time of the interval. @param EndTime The inclusive end time of the interval. @param Callback The function to be called for each log message with the message's information. Return True to signify a stop, False to continue. @note The current number of messages could be different than the value returned by the last call to GetMessageCount().
- L99 _public function_ `virtual uint64 LowerBoundByTime(double Time) const` — Performs binary search, resulting in position of the first log message with time >= provided time value. @param Time The time value, in seconds. @returns The index of the first log message with time >= provided time value; [0, MessageCount]. Returns ~0ull if not implemented. @note The current number of messages (MessageCount) could be different than the value returned by the last call to GetMessageCount().
- L109 _public function_ `virtual uint64 UpperBoundByTime(double Time) const` — Performs binary search, resulting in position of the first log message with time > provided time value. @param Time The time value, in seconds. @returns The index of the first log message with time > provided time value; [0, MessageCount]. Returns ~0ull if not implemented. @note The current number of messages (MessageCount) could be different than the value returned by the last call to GetMessageCount().
- L120 _public function_ `virtual uint64 BinarySearchClosestByTime(double Time) const` — Finds the log message with closest timestamp to the specified time. @param Time The time value, in seconds. @returns The index of the message with the closest timestamp to the specified time. If MessageCount is 0, this function returns 0; otherwise it returns a valid index in range [0, MessageCount-1]. Returns ~0ull if not implemented. @note The current number of messages (MessageCount) could be different than the value returned by the last call to GetMessageCount().
- L127 _public function_ `virtual uint64 GetMessageSpecCount() const` — Gets the number of log message specs. @returns The current number of log message specs.
- L134 _public prototype_ `virtual uint64 GetCategoryCount() const = 0;` — Gets the number of log categories. @returns The current number of log categories.
- L143 _public prototype_ `virtual void EnumerateCategories(TFunctionRef<void(const FLogCategoryInfo&)> Callback) const = 0;` — Enumerates the log categories. @param Callback The function to be called for each log category with the category's information. @note The current number of messages could be different than the value returned by the last call to GetMessageCount().
- L150 _public prototype_ `virtual const IUntypedTable& GetMessagesTable() const = 0;` — Gets the untyped table for log messages. @returns The IUntypedTable reference to the messages table.
- L157 _public function_ `virtual uint64 GetInsertCount() const` — Gets the number of inserts (when a message is inserted before other messages). @returns The number of inserts.
- L164 _public function_ `virtual uint64 GetUnknownSpecTotalCount() const` — Gets the total number of messages received with unknown message spec. @returns The total number of messages received with unknown message spec.
- L171 _public function_ `virtual uint64 GetUnresolvedSpecCount() const` — Gets the number of messages received with unknown message spec and still unresolved. @returns The number of messages received with unknown message spec and still unresolved.

#### class `TraceServices::IEditableLogProvider`  
`class IEditableLogProvider : public IEditableProvider`  
_L174-272_
- inherits: `IEditableProvider`
- L178 _public prototype_ `virtual ~IEditableLogProvider() = default;`
- L185 _public prototype_ `virtual uint64 RegisterCategory() = 0;` — Registers a new log message category. @return The category identity.
- L193 _public prototype_ `virtual FLogCategoryInfo& GetCategory(uint64 CategoryPointer) = 0;` — Fetches the data structure for a log category. @param CategoryPointer The unique identity (memory address) of the category instrumentation. @return A reference to the category structure.
- L201 _public prototype_ `virtual void UpdateMessageCategory(uint64 LogPoint, uint64 InCategoryPointer) = 0;` — Updates the Category information for a log message. @param LogPoint The log message to update. @param InCategoryPointer The category.
- L209 _public prototype_ `virtual void UpdateMessageFormatString(uint64 LogPoint, const TCHAR* InFormatString) = 0;` — Updates the format string for a log message. @param LogPoint The log message to update. @param InFormatString The format string whose memory is stored in the Session.
- L218 _public prototype_ `virtual void UpdateMessageFile(uint64 LogPoint, const TCHAR* InFile, int32 InLine) = 0;` — Updates the file location for a log message. @param LogPoint The log message to update. @param InFile The file path of the message's location. @param InLine The line number of the message's location.
- L226 _public prototype_ `virtual void UpdateMessageVerbosity(uint64 LogPoint, ELogVerbosity::Type InVerbosity) = 0;` — Updates the verbosity for a log message. @param LogPoint The log message to update. @param InVerbosity The verbosity of the message.
- L238 _public prototype_ `virtual void UpdateMessageSpec(uint64 LogPoint, uint64 InCategoryPointer, const TCHAR* InFormatString, const TCHAR* InFile, int32 InLine, ELogVerbosity::Type InVerbosity) = 0;` — Updates information for a log message. @param LogPoint The log message to update. @param InCategoryPointer The category. @param InFormatString The format string whose memory is stored in the Session. @param InFile The file path of the message's location. @param InLine The line number of the message's location. @param InVerbosity The verbosity of the message.
- L243 _public function_ `virtual void UpdateMessageSpec(uint64 LogPoint)` — Updates information for a log message after message spec was updated.
- L253 _public function_ `virtual void AppendMessage(uint64 LogPoint, double Time, const uint8* FormatArgs)` — `UE_DEPRECATED(5.8, "Use AppendMessage(uint64, double, TArrayView<const uint8>) instead.")` — Appends a new instance of a message from the trace session. @param LogPoint The unique identity (memory address) of the message instrumentation. @param Time The time in seconds of the event. @param FormatArgs The arguments to use in conjunction with the spec's FormatString.
- L262 _public function_ `virtual void AppendMessage(uint64 LogPoint, double Time, TArrayView<const uint8> FormatArgsView)` — Appends a new instance of a message from the trace session. @param LogPoint The unique identity (memory address) of the message instrumentation. @param Time The time in seconds of the event. @param FormatArgsView The arguments to use in conjunction with the spec's FormatString.
- L271 _public prototype_ `virtual void AppendMessage(uint64 LogPoint, double Time, const TCHAR* StoredText) = 0;` — Appends a new instance of a message from the trace session. @param LogPoint The unique identity (memory address) of the message instrumentation. @param Time The time in seconds of the event. @param StoredText The persistent message text.

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace TraceServices`
- L274 _prototype_ `FName GetLogProviderName();` (scope `TraceServices`)
- L275 _prototype_ `const ILogProvider& ReadLogProvider(const IAnalysisSession& Session);` (scope `TraceServices`)
- L276 _prototype_ `IEditableLogProvider& EditLogProvider(IAnalysisSession& Session);` (scope `TraceServices`)
- L277 _prototype_ `void FormatString(TCHAR* OutputString, uint32 OutputStringCount, const TCHAR* FormatString, const uint8* FormatArgs);` (scope `TraceServices`)

### `Source/Developer/TraceServices/Public/TraceServices/Model/Memory.h` (Public)


#### struct `TraceServices::FMemoryTrackerInfo`  
`struct FMemoryTrackerInfo`  
_L19-29_
- L21 _public member_ `static constexpr FMemoryTrackerId InvalidTrackerId = -1;`
- L22 _public member_ `static constexpr int32 MaxTrackers = 8;`
- L25 _public member_ `FMemoryTrackerId Id;` — The unique identifier of the memory tracker. Can also be used as an index, limited to [0 .. MaxTrackers-1] range.
- L28 _public member_ `FString Name;` — The name of the memory tracker.

#### struct `TraceServices::FMemoryTagSetInfo`  
`struct FMemoryTagSetInfo`  
_L31-40_
- L33 _public member_ `static constexpr FMemoryTagSetId InvalidTagSetId = -1;`
- L34 _public member_ `static constexpr int32 MaxTagSets = 8;`
- L37 _public member_ `FMemoryTagSetId Id;` — The unique identifier of the memory tag set. Can also be used as an index, limited to [0 .. MaxTagSets-1] range.
- L39 _public member_ `FString Name;`

#### struct `TraceServices::FMemoryTagInfo`  
`struct FMemoryTagInfo`  
_L42-62_
- L44 _public member_ `static constexpr FMemoryTagId InvalidTagId = 0;`
- L47 _public member_ `FMemoryTagId Id;` — The unique identifier of the memory tag.
- L50 _public member_ `FMemoryTagId ParentId;` — The id of the parent tag, 0 if no parent.
- L53 _public member_ `FMemoryTagSetId TagSetId;` — The set id of the memory tag.
- L58 _public member_ `uint64 Trackers;` — Bit flags for trackers using this memory tag. The bit position represents the tracker id; this limits the valid tracker ids to range [0 .. 63]. It can be updated during analysis (as new trackers / snapshots are analyzed).
- L61 _public member_ `FString Name;` — The name of the memory tag.

#### struct `TraceServices::FMemoryTagSample`  
`struct FMemoryTagSample`  
_L64-68_
- L67 _public member_ `int64 Value;` — Value at sample time.

#### class `TraceServices::IMemoryProvider`  
`class IMemoryProvider : public IProvider`  
_L70-162_
- inherits: `IProvider`
- L73 _public prototype_ `virtual ~IMemoryProvider() = default;`
- L75 _public prototype_ `virtual void BeginRead() const = 0;`
- L76 _public prototype_ `virtual void EndRead() const = 0;`
- L77 _public prototype_ `virtual void ReadAccessCheck() const = 0;`
- L82 _public prototype_ `virtual bool IsInitialized() const = 0;` — @returns Whether the provider is initialized or not.
- L88 _public prototype_ `virtual bool IsCompleted() const = 0;` — When this provider is completed it cannot be further modified. @returns Whether this provider is completed or not.
- L94 _public prototype_ `virtual uint32 GetTagSerial() const = 0;` — Unique serial index that changes when new tags are registered or when the Trackers flags is updated for a tag. @return Unique index
- L100 _public prototype_ `virtual uint32 GetTagCount() const = 0;` — Return the number of registered tags. @return Number of registered tags.
- L106 _public prototype_ `virtual void EnumerateTags(TFunctionRef<void(const FMemoryTagInfo&)> Callback) const = 0;` — Enumerate the registered tags. @param Callback Function that will be called for each registered tag.
- L112 _public prototype_ `virtual void EnumerateTags(FMemoryTagSetId TagSetId, TFunctionRef<void(const FMemoryTagInfo&)> Callback) const = 0;` — Enumerate the registered tags for a specified tag set. @param Callback Function that will be called for each registered tag.
- L119 _public prototype_ `virtual const FMemoryTagInfo* GetTag(FMemoryTagId TagId) const = 0;` — Returns the meta data for a memory tag specified by id. @param TagId The id of the memory tag. @return Memory tag information.
- L127 _public prototype_ `virtual uint64 GetTagSampleCount(FMemoryTrackerId Tracker, FMemoryTagId TagId) const = 0;` — Gets the number of samples for a given tag from a given tracker. @param Tracker Tracer index. @param TagId The id of the memory tag. @return Number of samples that has been recorded.
- L133 _public prototype_ `virtual uint32 GetTrackerCount() const = 0;` — Return the number of registered trackers. @return Number of trackers.
- L139 _public prototype_ `virtual void EnumerateTrackers(TFunctionRef<void(const FMemoryTrackerInfo&)> Callback) const = 0;` — Enumerate the registered trackers. @param Callback Function that is called for each registered tracker.
- L145 _public prototype_ `virtual uint32 GetTagSetCount() const = 0;` — Return the number of registered tag sets. @return Number of tag sets.
- L151 _public prototype_ `virtual void EnumerateTagSets(TFunctionRef<void(const FMemoryTagSetInfo&)> Callback) const = 0;` — Enumerate the registered tag sets. @param Callback Function that is called for each registered tag set.
- L161 _public prototype_ `virtual void EnumerateTagSamples(FMemoryTrackerId Tracker, FMemoryTagId TagId, double StartTime, double EndTime, bool bIncludeRangeNeighbors, TFunctionRef<void(double Time, double Duration, const FMemoryTagSample&)> Callback) const = 0;` — Enumerates samples (values) for a specified LLM tag. @param Tracker The tracker index. @param TagId The id of the memory tag. @param StartSample The inclusive start index in the sample array of specified memory tag. @param EndSample The exclusive end index in the sample array of specified memory tag. @param Callback A callback function called for each sample enumerated. @param bIncludeRangeNeighbors Includes the sample immediately before and after the selected range.

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace TraceServices`
- L15 _typedef_ `typedef int32 FMemoryTrackerId;` (scope `TraceServices`)
- L16 _typedef_ `typedef int32 FMemoryTagSetId;` (scope `TraceServices`)
- L17 _typedef_ `typedef int64 FMemoryTagId;` (scope `TraceServices`)
- L164 _prototype_ `FName GetMemoryProviderName();` (scope `TraceServices`)
- L165 _prototype_ `const IMemoryProvider* ReadMemoryProvider(const IAnalysisSession& Session);` (scope `TraceServices`)

### `Source/Developer/TraceServices/Public/TraceServices/Model/MetadataProvider.h` (Public)


#### class `TraceServices::FMetadataSchema`  
`class FMetadataSchema`  
_L15-267_
- L237 _public function_ `explicit FMetadataSchema(uint8 InFieldCount)`
- L242 _public function_ `FMetadataSchema(const FMetadataSchema& InSchema) : Fields(InSchema.Fields)`
- L248 _public function_ `FBuilder Builder()`
- L253 _public function_ `FWriter Writer() const`
- L258 _public function_ `FReader Reader() const`
- L264 _private prototype_ `FMetadataSchema() = delete;`
- L266 _private member_ `TArray<FField> Fields;`

#### enum `TraceServices::FMetadataSchema::EFieldType`  
`enum class EFieldType : uint8`  
_L18-25_
- L20 _public enumerator_ `Integer`
- L21 _public enumerator_ `SignedInteger`
- L22 _public enumerator_ `FloatingPoint`
- L23 _public enumerator_ `WideStringPtr`
- L24 _public enumerator_ `Reference`

#### struct `TraceServices::FMetadataSchema::FField`  
`struct FField`  
_L27-33_
- L29 _public member_ `FName Name;`
- L30 _public member_ `EFieldType Type;`
- L31 _public member_ `uint8 Offset;`
- L32 _public member_ `uint8 Size;`

#### struct `TraceServices::FMetadataSchema::FBuilder`  
`struct FBuilder`  
_L38-67_
- desc: Helper class that assist in defining a schema.
- L40 _public function_ `FBuilder(FField* InBuffer, uint8 InMaxFieldCount) : Buffer(InBuffer), MaxFieldCount(InMaxFieldCount), CurrentFieldCount(0), CurrentOffset(0)`
- L46 _public function_ `template<typename T> FBuilder& AddField(FName FieldName, EFieldType Type)`
- L58 _public function_ `void Finish()`
- L63 _private member_ `FField* Buffer;`
- L64 _private member_ `uint8 MaxFieldCount;`
- L65 _private member_ `uint8 CurrentFieldCount;`
- L66 _private member_ `uint8 CurrentOffset;`

#### struct `TraceServices::FMetadataSchema::FWriter`  
`struct FWriter`  
_L72-95_
- desc: Helper class that helps writing data based on a schema.
- L74 _public function_ `FWriter(const FField* InBuffer, uint8 InFieldCount) : Buffer(InBuffer), FieldCount(InFieldCount), Offset(0)`
- L80 _public function_ `template<typename ArrayType> void WriteField(uint8 Index, const void* Src, uint8 Size, ArrayType& Dst)`
- L92 _private member_ `const FField* Buffer;`
- L93 _private member_ `uint8 FieldCount;`
- L94 _private member_ `uint8 Offset;`

#### struct `TraceServices::FMetadataSchema::FReader`  
`struct FReader`  
_L100-235_
- desc: Helper class that helps reading fields from data based on a schema.
- L102 _public function_ `FReader(const FField* InBuffer, uint8 InFieldCount) : Buffer(InBuffer), FieldCount(InFieldCount)`
- L106 _public function_ `uint8 GetFieldCount() const`
- L107 _public function_ `const FField& GetFieldDesc(uint8 Index) const`
- L109 _public function_ `FString GetString(uint8* MetaData, uint8 Index) const`
- L162 _public function_ `FText GetText(uint8* MetaData, uint8 Index) const`
- L219 _public function_ `template<typename T> const T* GetValueAs(const uint8* Metadata, uint8 Index) const`
- L226 _private function_ `template<typename T> const T* GetValue(const uint8* Metadata, uint8 Index) const`
- L233 _private member_ `const FField* Buffer;`
- L234 _private member_ `uint8 FieldCount;`

#### class `TraceServices::IMetadataProvider`  
`class IMetadataProvider : public IProvider`  
_L269-288_
- inherits: `IProvider`
- L272 _public member_ `static constexpr uint32 InvalidMetadataId = 0xFFFFFFFF;`
- L273 _public member_ `static constexpr uint16 InvalidMetadataType = 0xFF;`
- L275 _public prototype_ `virtual ~IMetadataProvider() = default;`
- L277 _public prototype_ `virtual void BeginRead() const = 0;`
- L278 _public prototype_ `virtual void EndRead() const = 0;`
- L279 _public prototype_ `virtual void ReadAccessCheck() const = 0;`
- L281 _public prototype_ `virtual uint16 GetRegisteredMetadataType(FName Name) const = 0;`
- L282 _public prototype_ `virtual FName GetRegisteredMetadataName(uint16 Type) const = 0;`
- L283 _public prototype_ `virtual const FMetadataSchema* GetRegisteredMetadataSchema(uint16) const = 0 ;`
- L285 _public prototype_ `virtual uint32 GetMetadataStackSize(uint32 InThreadId, uint32 InMetadataId) const = 0;`
- L286 _public prototype_ `virtual bool GetMetadata(uint32 InThreadId, uint32 InMetadataId, uint32 InStackDepth, uint16& OutType, const void*& OutData, uint32& OutSize) const = 0;`
- L287 _public prototype_ `virtual void EnumerateMetadata(uint32 InThreadId, uint32 InMetadataId, TFunctionRef<bool(uint32 StackDepth, uint16 Type, const void* Data, uint32 Size)> Callback) const = 0;`

#### class `TraceServices::IEditableMetadataProvider`  
`class IEditableMetadataProvider : public IEditableProvider`  
_L290-315_
- inherits: `IEditableProvider`
- L293 _public prototype_ `virtual ~IEditableMetadataProvider() = default;`
- L295 _public prototype_ `virtual void BeginEdit() const = 0;`
- L296 _public prototype_ `virtual void EndEdit() const = 0;`
- L297 _public prototype_ `virtual void EditAccessCheck() const = 0;`
- L299 _public prototype_ `virtual uint16 RegisterMetadataType(const TCHAR* InName, const FMetadataSchema& InSchema) = 0;`
- L301 _public prototype_ `virtual void PushScopedMetadata(uint32 InThreadId, uint16 InType, const void* InData, uint32 InSize) = 0;`
- L302 _public prototype_ `virtual void PopScopedMetadata(uint32 InThreadId, uint16 InType) = 0;`
- L304 _public prototype_ `virtual void BeginClearStackScope(uint32 InThreadId) = 0;`
- L305 _public prototype_ `virtual void EndClearStackScope(uint32 InThreadId) = 0;`
- L307 _public prototype_ `virtual void SaveStack(uint32 InThreadId, uint32 InSavedStackId) = 0;`
- L308 _public prototype_ `virtual void BeginRestoreSavedStackScope(uint32 InThreadId, uint32 InSavedStackId) = 0;`
- L309 _public prototype_ `virtual void EndRestoreSavedStackScope(uint32 InThreadId) = 0;`
- L312 _public prototype_ `virtual uint32 PinAndGetId(uint32 InThreadId) = 0;` — Pins the metadata stack and returns an id for it.
- L314 _public function_ `virtual void OnAnalysisCompleted()`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace TraceServices`
- L317 _prototype_ `FName GetMetadataProviderName();` (scope `TraceServices`)
- L318 _prototype_ `const IMetadataProvider* ReadMetadataProvider(const IAnalysisSession& Session);` (scope `TraceServices`)
- L319 _prototype_ `IEditableMetadataProvider* EditMetadataProvider(IAnalysisSession& Session);` (scope `TraceServices`)

### `Source/Developer/TraceServices/Public/TraceServices/Model/Modules.h` (Public)


#### enum `TraceServices::ESymbolQueryResult`  
`enum class ESymbolQueryResult : uint8`  
_L22-30_
- desc: Result of a query. Since symbol resolving can be deferred this signals if a symbol has been resolved, waiting to be resolved or wasn't found at all.
- L24 _public enumerator_ `Pending` — Symbol is pending resolution
- L25 _public enumerator_ `OK` — Symbol has been correctly resolved
- L26 _public enumerator_ `NotLoaded` — Module debug data could not be loaded or found
- L27 _public enumerator_ `Mismatch` — Module debug data could not be loaded because debug data did not match traced binary
- L28 _public enumerator_ `NotFound` — Symbol was not found in module debug data
- L29 _public enumerator_ `StatusNum`

#### enum `TraceServices::EResolvedSymbolFilterStatus`  
`enum class EResolvedSymbolFilterStatus : uint8`  
_L51-56_
- L53 _public enumerator_ `Unknown = 0`
- L54 _public enumerator_ `Filtered`
- L55 _public enumerator_ `NotFiltered`

#### struct `TraceServices::FResolvedSymbol`  
`struct FResolvedSymbol`  
_L64-86_
- desc: Represent a resolved symbol. The resolve status and string values may change over time, but string pointers returned from the methods are guaranteed to live during the entire analysis session.
- L66 _public member_ `const TCHAR* Module;`
- L67 _public member_ `const TCHAR* Name;`
- L68 _public member_ `const TCHAR* File;`
- L69 _public member_ `uint16 Line;`
- L70 _public member_ `std::atomic<ESymbolQueryResult> Result;`
- L71 _public member_ `std::atomic<EResolvedSymbolFilterStatus> FilterStatus;`
- L73 _public function_ `inline ESymbolQueryResult GetResult() const`
- L78 _public function_ `FResolvedSymbol(ESymbolQueryResult InResult, const TCHAR* InModule, const TCHAR* InName, const TCHAR* InFile, uint16 InLine, EResolvedSymbolFilterStatus InFilterStatus) : Module(InModule) , Name(InName) , File(InFile) , Line(InLine) , Result(InResult) , FilterStatus(InFilterStatus)`

#### class `TraceServices::IResolvedSymbolFilter`  
`class IResolvedSymbolFilter`  
_L89-93_
- L92 _public prototype_ `virtual void Update(FResolvedSymbol& InSymbol) const = 0;`

#### enum `TraceServices::EModuleStatus`  
`enum class EModuleStatus : uint8`  
_L96-106_
- L98 _public enumerator_ `Discovered` — Symbols are discovered for this module
- L99 _public enumerator_ `Pending` — Module is pending load
- L100 _public enumerator_ `Loaded` — Module has been successfully loaded
- L101 _public enumerator_ `VersionMismatch` — Debug data was found, but did not match traced version
- L102 _public enumerator_ `NotFound` — Debug data for module was not found
- L103 _public enumerator_ `Failed` — Unable to parse debug information
- L104 _public enumerator_ `StatusNum`
- L105 _public enumerator_ `FailedStatusStart = VersionMismatch`

#### struct `TraceServices::FModule`  
`struct FModule`  
_L128-164_
- desc: Represents information about a module (engine/game/system dll or monolithic binary) and how debug information has been loaded.
- L131 _public member_ `const TCHAR* Name;` — Name of the module.
- L133 _public member_ `const TCHAR* FullName;` — Full name as reported by the event
- L135 _public member_ `uint64 Base;` — Base address
- L137 _public member_ `uint32 Size;` — Size in memory
- L139 _public member_ `std::atomic<bool> bIsUnloaded;` — If the module was unloaded or not
- L141 _public member_ `std::atomic<EModuleStatus> Status;` — Status of loading debug information
- L143 _public member_ `const TCHAR* StatusMessage;` — If status is loaded, contains the path to the debug info. If failure state contains an error message.
- L152 _public member_ `} Stats;`
- L154 _public function_ `FModule(const TCHAR* InName, const TCHAR* InFullName, uint64 InBase, uint32 InSize, EModuleStatus InStatus) : Name(InName) , FullName(InFullName) , Base(InBase) , Size(InSize) , bIsUnloaded(false) , Status(InStatus) , StatusMessage(nullptr)`

#### struct `TraceServices::FModule::SymbolStats`  
`struct SymbolStats`  
_L145-152_
- desc: Statistics about the module
- L147 _public member_ `std::atomic<uint32> Discovered = 0;` — number of symbols discovered in the trace (used symbols)
- L148 _public member_ `std::atomic<uint32> Cached = 0;` — number of symbols loaded from cache
- L149 _public member_ `std::atomic<uint32> Resolved = 0;` — number of symbols successfully resolved from the loaded module
- L150 _public member_ `std::atomic<uint32> Failed = 0;` — number of symbols failed to resolve
- L151 _public member_ `std::atomic<uint32> Available = 0;` — number of symbols available in the loaded module's debug information

#### class `TraceServices::IModuleProvider`  
`class IModuleProvider : public IProvider , public IEditableProvider`  
_L167-225_
- inherits: `IProvider,IEditableProvider`
- L183 _public prototype_ `virtual ~IModuleProvider() = default;`
- L189 _public prototype_ `virtual const FResolvedSymbol* GetSymbol(uint64 Address) = 0;` — Queries the name of the symbol at address. This function returns immediately, but the lookup is async. See \ref FResolvedSymbol for details. It assumed that all calls to this function happens before analysis has ended.
- L195 _public prototype_ `virtual uint32 GetNumModules() const = 0;` — Gets the number of discovered modules. @return Number of modules that were discovered so far.
- L203 _public prototype_ `virtual void EnumerateModules(uint32 Start, TFunctionRef<void(const FModule& Module)> Callback) const = 0;` — Enumerates all detected modules and their state. Modules are listed in the order they were found and is guaranteed to retain it's index in the list and address in memory. @param Start Starting index @param Callback Issued for each module
- L212 _public prototype_ `virtual FGraphEventRef LoadSymbolsForModuleUsingPath(uint64 Base, const TCHAR* Path) = 0;` — Trigger a manual attempt to load symbols for a module given a search path. This operation is asynchronous and if successful resolve symbols that previously failed. @param Base Base address of the module @param Path Path where debug data can be located @return Waitable graph event for the operation
- L218 _public prototype_ `virtual void EnumerateSymbolSearchPaths(TFunctionRef<void(FStringView Path)> Callback) const = 0;` — Gets the search paths used to find debug symbols. @param Callback Called for each search path.
- L221 _public prototype_ `virtual void GetStats(FStats* OutStats) const = 0;` — Gets statistics from provider.
- L224 _public prototype_ `virtual bool HasFinishedResolving() const = 0;` — Checks if all symbols have been resolved in resolver queues. Only useful after analysis has completed (e.g., OnAnalysisComplete).

#### struct `TraceServices::IModuleProvider::FStats`  
`struct FStats`  
_L172-181_
- L174 _public member_ `uint32 ModulesDiscovered;`
- L175 _public member_ `uint32 ModulesLoaded;`
- L176 _public member_ `uint32 ModulesFailed;`
- L177 _public member_ `uint32 SymbolsDiscovered;`
- L178 _public member_ `uint32 SymbolsCached;`
- L179 _public member_ `uint32 SymbolsResolved;`
- L180 _public member_ `uint32 SymbolsFailed;`

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace TraceServices`
- L36 _function_ `inline const TCHAR* QueryResultToString(ESymbolQueryResult Result)` (scope `TraceServices`) — Helper method to get a string representation of the query result.
- L109 _function_ `inline const TCHAR* ModuleStatusToString(EModuleStatus Result)` (scope `TraceServices`)
- L229 _prototype_ `FName GetModuleProviderName();` (scope `TraceServices`)
- L230 _prototype_ `const IModuleProvider* ReadModuleProvider(const IAnalysisSession& Session);` (scope `TraceServices`)

### `Source/Developer/TraceServices/Public/TraceServices/Model/NetProfiler.h` (Public)


#### enum `TraceServices::ENetProfilerAggregationMode`  
`enum class ENetProfilerAggregationMode : uint32`  
_L16-21_
- L18 _public enumerator_ `None`
- L19 _public enumerator_ `Aggregate`
- L20 _public enumerator_ `InstanceMax`

#### enum `TraceServices::ENetProfilerDeliveryStatus`  
`enum class ENetProfilerDeliveryStatus : uint8`  
_L23-28_
- L25 _public enumerator_ `Unknown`
- L26 _public enumerator_ `Delivered`
- L27 _public enumerator_ `Dropped`

#### enum `TraceServices::ENetProfilerConnectionMode`  
`enum ENetProfilerConnectionMode : uint8`  
_L30-35_
- L32 _public enumerator_ `Outgoing = 0`
- L33 _public enumerator_ `Incoming = 1`
- L34 _public enumerator_ `Count`

#### enum `TraceServices::ENetProfilerChannelCloseReason`  
`enum class ENetProfilerChannelCloseReason : uint8`  
_L38-45_
- desc: Mirrored from EChannelCloseReason on the runtime side
- L40 _public enumerator_ `Destroyed = 0`
- L41 _public enumerator_ `Dormancy`
- L42 _public enumerator_ `LevelUnloaded`
- L43 _public enumerator_ `Relevancy`
- L44 _public enumerator_ `TearOff`

#### enum `TraceServices::ENetProfilerConnectionState`  
`enum class ENetProfilerConnectionState : uint8`  
_L48-54_
- desc: Mirrored from EConnectionState on the runtime side
- L50 _public enumerator_ `USOCK_Invalid = 0` — Connection is invalid, possibly uninitialized.
- L51 _public enumerator_ `USOCK_Closed = 1` — Connection permanently closed.
- L52 _public enumerator_ `USOCK_Pending = 2` — Connection is awaiting connection.
- L53 _public enumerator_ `USOCK_Open = 3` — Connection is open.

#### struct `TraceServices::FNetProfilerName`  
`struct FNetProfilerName`  
_L62-66_
- L64 _public member_ `const TCHAR* Name;` — Name
- L65 _public member_ `FNetProfilerNameIndexType NameIndex;` — Index in the type array?

#### struct `TraceServices::FNetProfilerEventType`  
`struct FNetProfilerEventType`  
_L69-75_
- desc: This is our event type separate per level as the same name might be used on different levels
- L71 _public member_ `const TCHAR* Name;`
- L72 _public member_ `uint32 EventTypeIndex;`
- L73 _public member_ `FNetProfilerNameIndexType NameIndex;`
- L74 _public member_ `uint16 Level;`

#### struct `TraceServices::FNetProfilerLifeTime`  
`struct FNetProfilerLifeTime`  
_L79-83_
- L81 _public member_ `FNetProfilerTimeStamp Begin = 0;`
- L82 _public member_ `FNetProfilerTimeStamp End = std::numeric_limits<double>::infinity();`

#### struct `TraceServices::FNetProfilerObjectInstance`  
`struct FNetProfilerObjectInstance`  
_L92-99_
- L94 _public member_ `FNetProfilerLifeTime LifeTime;` — Lifetime of this instance
- L95 _public member_ `uint64 NetObjectId = 0;` — NetHandleIndex or NetGUID
- L96 _public member_ `uint64 TypeId = uint64(0);` — ProtocolIdentifier
- L97 _public member_ `uint32 ObjectIndex = 0U;` — Index in the object array
- L98 _public member_ `FNetProfilerNameIndexType NameIndex = 0U;` — Index in the Name array

#### union `TraceServices::FNetProfilerBunchInfo`  
`union FNetProfilerBunchInfo`  
_L101-128_
- L125 _public member_ `uint64 Value;`
- L127 _public function_ `static FNetProfilerBunchInfo MakeBunchInfo(uint64 InValue)`

#### struct `TraceServices::FNetProfilerBunchInfo::(anonymous)`  
``  
_L104-124_

#### struct `TraceServices::FNetProfilerContentEvent`  
`struct FNetProfilerContentEvent`  
_L132-144_
- L134 _public member_ `uint64 StartPos : 24;` — Inclusive start position in the packet
- L135 _public member_ `uint64 EndPos : 24;` — Exclusive end position in the packet; BitSize = EndPos - StartPos
- L136 _public member_ `uint64 Level : 8;` — Level
- L137 _public member_ `uint64 Padding : 8;` — Padding
- L139 _public member_ `FNetProfilerBunchInfo BunchInfo;`
- L141 _public member_ `uint32 EventTypeIndex;` — Will replace name index
- L142 _public member_ `FNetProfilerNameIndexType NameIndex;` — Identify the name / type, should we store the actual Name as well
- L143 _public member_ `uint32 ObjectInstanceIndex;` — Object instance, Non zero if this is a NetObject, we can then look up data by indexing into ObjectInstances

#### enum `TraceServices::ENetProfilerStatsCounterType`  
`enum class ENetProfilerStatsCounterType : uint8`  
_L147-151_
- desc: This must be kept in sync with ENetTraceStatsCounterType in NetTrace.h
- L149 _public enumerator_ `Packet = 0`
- L150 _public enumerator_ `Frame = 1`

#### struct `TraceServices::FNetProfilerStatsCounterType`  
`struct FNetProfilerStatsCounterType`  
_L153-158_
- L155 _public member_ `uint32 StatsCounterTypeIndex;`
- L156 _public member_ `FNetProfilerNameIndexType NameIndex;`
- L157 _public member_ `ENetProfilerStatsCounterType Type;`

#### struct `TraceServices::FNetProfilerStats`  
`struct FNetProfilerStats`  
_L160-164_
- L162 _public member_ `uint32 StatsCounterTypeIndex;`
- L163 _public member_ `uint32 StatsValue;`

#### struct `TraceServices::FNetProfilerPacket`  
`struct FNetProfilerPacket`  
_L166-185_
- L168 _public member_ `FNetProfilerTimeStamp TimeStamp;`
- L169 _public member_ `uint32 SequenceNumber;`
- L170 _public member_ `uint32 ContentSizeInBits;` — This is the part that is tracked by the PacketContents
- L171 _public member_ `uint32 TotalPacketSizeInBytes;` — This is the actual size of the packet sent on the socket
- L174 _public member_ `uint32 StartEventIndex;` — Index into Events
- L175 _public member_ `uint32 EventCount;`
- L177 _public member_ `uint32 StartStatsIndex;`
- L178 _public member_ `uint32 StatsCount;`
- L181 _public member_ `uint32 NetProfilerFrameIndex;` — Index into network profiler frames
- L183 _public member_ `ENetProfilerDeliveryStatus DeliveryStatus;` — Indicates if the packet was delivered or not, updated as soon as we know
- L184 _public member_ `ENetProfilerConnectionState ConnectionState;`

#### struct `TraceServices::FNetProfilerFrame`  
`struct FNetProfilerFrame`  
_L187-193_
- L189 _public member_ `FNetProfilerTimeStamp TimeStamp;`
- L190 _public member_ `uint64 EngineFrameNumber = 0;`
- L191 _public member_ `uint32 StartStatsIndex = 0;`
- L192 _public member_ `uint32 StatsCount = 0;`

#### struct `TraceServices::FNetProfilerConnection`  
`struct FNetProfilerConnection`  
_L195-205_
- L197 _public member_ `const TCHAR* Name = nullptr;`
- L198 _public member_ `const TCHAR* AddressString = nullptr;`
- L199 _public member_ `FNetProfilerLifeTime LifeTime;`
- L200 _public member_ `uint32 GameInstanceIndex;`
- L201 _public member_ `uint32 ConnectionIndex : 16;`
- L202 _public member_ `uint32 ConnectionId : 14;`
- L203 _public member_ `uint32 bHasIncomingData : 1;`
- L204 _public member_ `uint32 bHasOutgoingData : 1;`

#### struct `TraceServices::FNetProfilerGameInstance`  
`struct FNetProfilerGameInstance`  
_L207-215_
- L209 _public member_ `FNetProfilerLifeTime LifeTime;`
- L210 _public member_ `uint32 GameInstanceIndex;`
- L211 _public member_ `uint32 GameInstanceId;`
- L212 _public member_ `const TCHAR* InstanceName = nullptr;`
- L213 _public member_ `bool bIsUsingIrisReplication = false;`
- L214 _public member_ `bool bIsServer = false;`

#### struct `TraceServices::FNetProfilerAggregatedStats`  
`struct FNetProfilerAggregatedStats`  
_L217-226_
- L219 _public member_ `uint32 EventTypeIndex;`
- L220 _public member_ `uint32 InstanceCount = 0U;`
- L221 _public member_ `uint32 TotalInclusive = 0U;`
- L222 _public member_ `uint32 MaxInclusive = 0U;`
- L223 _public member_ `uint32 AverageInclusive = 0U;`
- L224 _public member_ `uint32 TotalExclusive = 0U;`
- L225 _public member_ `uint32 MaxExclusive = 0U;`

#### struct `TraceServices::FNetProfilerAggregatedStatsCounterStats`  
`struct FNetProfilerAggregatedStatsCounterStats`  
_L228-245_
- L230 _public member_ `uint32 StatsCounterTypeIndex;`
- L231 _public member_ `uint32 Sum;`
- L232 _public member_ `uint32 Min;`
- L233 _public member_ `uint32 Max;`
- L234 _public member_ `uint32 Average;`
- L235 _public member_ `uint32 Count;`
- L237 _public function_ `void Reset()`

#### class `TraceServices::INetProfilerProvider`  
`class INetProfilerProvider : public IProvider`  
_L248-315_
- inherits: `IProvider`
- desc: What queries do we need?
- L251 _public prototype_ `virtual ~INetProfilerProvider() = default;`
- L255 _public prototype_ `virtual uint32 GetNetTraceVersion() const = 0;` — Return the version reported in the trace A return value of 0 indicates no network trace data
- L258 _public prototype_ `virtual uint32 GetNameCount() const = 0;` — Access Names
- L259 _public prototype_ `virtual void ReadNames(TFunctionRef<void(const FNetProfilerName*, uint64)> Callback) const = 0;`
- L260 _public prototype_ `virtual void ReadName(uint32 NameIndex, TFunctionRef<void(const FNetProfilerName&)> Callback) const = 0;`
- L263 _public prototype_ `virtual uint32 GetEventTypesCount() const = 0;` — Access EventTypes
- L264 _public prototype_ `virtual void ReadEventTypes(TFunctionRef<void(const FNetProfilerEventType*, uint64)> Callback) const = 0;`
- L265 _public prototype_ `virtual void ReadEventType(uint32 EventTypeIndex, TFunctionRef<void(const FNetProfilerEventType&)> Callback) const = 0;`
- L268 _public prototype_ `virtual uint32 GetGameInstanceCount() const = 0;` — Access GameInstances
- L269 _public prototype_ `virtual void ReadGameInstances(TFunctionRef<void(const FNetProfilerGameInstance&)> Callback) const = 0;`
- L270 _public prototype_ `virtual uint32 GetGameInstanceChangeCount() const = 0;`
- L273 _public prototype_ `virtual uint32 GetConnectionCount(uint32 GameInstanceIndex) const = 0;` — Access Connections
- L274 _public prototype_ `virtual void ReadConnections(uint32 GameInstanceIndex, TFunctionRef<void(const FNetProfilerConnection&)> Callback) const = 0;`
- L275 _public prototype_ `virtual void ReadConnection(uint32 ConnectionIndex, TFunctionRef<void(const FNetProfilerConnection&)> Callback) const = 0;`
- L276 _public prototype_ `virtual uint32 GetConnectionChangeCount() const = 0;`
- L279 _public prototype_ `virtual uint32 GetObjectCount(uint32 GameInstanceIndex) const = 0;` — Access Object Instances
- L280 _public prototype_ `virtual void ReadObjects(uint32 GameInstanceIndex, TFunctionRef<void(const FNetProfilerObjectInstance&)> Callback) const = 0;`
- L281 _public prototype_ `virtual void ReadObject(uint32 GameInstanceIndex, uint32 ObjectIndex, TFunctionRef<void(const FNetProfilerObjectInstance&)> Callback) const = 0;`
- L282 _public prototype_ `virtual uint32 GetObjectsChangeCount(uint32 GameInstanceIndex) const = 0;`
- L285 _public prototype_ `virtual int32 FindPacketIndexFromPacketSequence(uint32 ConnectionIndex, ENetProfilerConnectionMode Mode, uint32 SequenceNumber) const = 0;` — Find Packet Index from SequenceNumber
- L288 _public prototype_ `virtual uint32 GetPacketCount(uint32 ConnectionIndex, ENetProfilerConnectionMode Mode) const = 0;` — Gets the number of packets for the specified connection and connection mode.
- L291 _public prototype_ `virtual void EnumeratePackets(uint32 ConnectionIndex, ENetProfilerConnectionMode Mode, uint32 PacketIndexIntervalStart, uint32 PacketIndexIntervalEnd, TFunctionRef<void(const FNetProfilerPacket&)> Callback) const = 0;` — Enumerates packets in the provided inclusive packet interval, [PacketIndexIntervalStart, PacketIndexIntervalEnd].
- L293 _public prototype_ `virtual uint32 GetPacketChangeCount(uint32 ConnectionIndex, ENetProfilerConnectionMode Mode) const = 0;` — Returns a change number incremented each time a change occurs in the packets for the specified connection and connection mode.
- L296 _public prototype_ `virtual void EnumeratePacketContentEventsByIndex(uint32 ConnectionIndex, ENetProfilerConnectionMode Mode, uint32 StartEventIndex, uint32 EndEventIndex, TFunctionRef<void(const FNetProfilerContentEvent&)> Callback) const = 0;`
- L298 _public prototype_ `virtual void EnumeratePacketContentEventsByPosition(uint32 ConnectionIndex, ENetProfilerConnectionMode Mode, uint32 PacketIndex, uint32 StartPosition, uint32 EndPosition, TFunctionRef<void(const FNetProfilerContentEvent&)> Callback) const = 0;`
- L300 _public prototype_ `virtual uint32 GetPacketContentEventChangeCount(uint32 ConnectionIndex, ENetProfilerConnectionMode Mode) const = 0;`
- L303 _public prototype_ `virtual uint32 GetNetStatsCounterTypesCount() const = 0;` — Access StatsCounterTypes
- L304 _public prototype_ `virtual void ReadNetStatsCounterTypes(TFunctionRef<void(const FNetProfilerStatsCounterType*, uint64)> Callback) const = 0;`
- L305 _public prototype_ `virtual void ReadNetStatsCounterType(uint32 TypeIndex, TFunctionRef<void(const FNetProfilerStatsCounterType&)> Callback) const = 0;`
- L310 _public prototype_ `virtual ITable<FNetProfilerAggregatedStats>* CreateAggregation(uint32 ConnectionIndex, ENetProfilerConnectionMode Mode, uint32 PacketIndexIntervalStart, uint32 PacketIndexIntervalEnd, uint32 StartPosition, uint32 EndPosition) const = 0;` — Computes aggregated stats for a packet interval or for a range of content events in a single packet. [PacketIndexIntervalStart, PacketIndexIntervalEnd] is the inclusive packet interval. [StartPosition, EndPosition) is the exclusive bit range interval; only used when PacketIndexIntervalStart == PacketIndexIntervalEnd.
- L314 _public prototype_ `virtual ITable<FNetProfilerAggregatedStatsCounterStats>* CreateStatsCountersAggregation(uint32 ConnectionIndex, ENetProfilerConnectionMode Mode, uint32 PacketIndexIntervalStart, uint32 PacketIndexIntervalEnd) const = 0;` — Computes aggregated statscounters for a packet interval [PacketIndexIntervalStart, PacketIndexIntervalEnd] is the inclusive packet interval.

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace TraceServices`
- L56 _prototype_ `const TCHAR* LexToString(const ENetProfilerChannelCloseReason Value);` (scope `TraceServices`)
- L57 _prototype_ `const TCHAR* LexToString(const ENetProfilerConnectionState Value);` (scope `TraceServices`)
- L60 _typedef_ `typedef uint32 FNetProfilerNameIndexType;` (scope `TraceServices`) — Mirror from FNetDebugNameId on the runtime side.
- L77 _typedef_ `typedef double FNetProfilerTimeStamp;` (scope `TraceServices`)
- L106 _member_ `uint64 ChannelIndex : 20;` (scope `TraceServices::FNetProfilerBunchInfo::__anoned3baafd0108`) — Must match FNetTraceBunchInfo in runtime code.
- L107 _member_ `uint64 Seq : 12;` (scope `TraceServices::FNetProfilerBunchInfo::__anoned3baafd0108`)
- L108 _member_ `uint64 ChannelCloseReason : 4;` (scope `TraceServices::FNetProfilerBunchInfo::__anoned3baafd0108`)
- L109 _member_ `uint64 bPartial : 1;` (scope `TraceServices::FNetProfilerBunchInfo::__anoned3baafd0108`)
- L110 _member_ `uint64 bPartialInitial : 1;` (scope `TraceServices::FNetProfilerBunchInfo::__anoned3baafd0108`)
- L111 _member_ `uint64 bPartialCustomExportsFinal : 1;` (scope `TraceServices::FNetProfilerBunchInfo::__anoned3baafd0108`)
- L112 _member_ `uint64 bPartialFinal : 1;` (scope `TraceServices::FNetProfilerBunchInfo::__anoned3baafd0108`)
- L114 _member_ `uint64 bIsReplicationPaused : 1;` (scope `TraceServices::FNetProfilerBunchInfo::__anoned3baafd0108`) — `UE_DEPRECATED(5.3, "Replication pausing is now deprecated.")`
- L115 _member_ `uint64 bOpen : 1;` (scope `TraceServices::FNetProfilerBunchInfo::__anoned3baafd0108`)
- L116 _member_ `uint64 bClose : 1;` (scope `TraceServices::FNetProfilerBunchInfo::__anoned3baafd0108`)
- L117 _member_ `uint64 bReliable : 1;` (scope `TraceServices::FNetProfilerBunchInfo::__anoned3baafd0108`)
- L118 _member_ `uint64 bHasPackageMapExports : 1;` (scope `TraceServices::FNetProfilerBunchInfo::__anoned3baafd0108`)
- L119 _member_ `uint64 bHasMustBeMappedGUIDs : 1;` (scope `TraceServices::FNetProfilerBunchInfo::__anoned3baafd0108`)
- L122 _member_ `uint64 bIsValid : 1;` (scope `TraceServices::FNetProfilerBunchInfo::__anoned3baafd0108`) — Reserved
- L123 _member_ `uint64 Padding : 17;` (scope `TraceServices::FNetProfilerBunchInfo::__anoned3baafd0108`)
- L317 _prototype_ `FName GetNetProfilerProviderName();` (scope `TraceServices`)
- L318 _prototype_ `const INetProfilerProvider* ReadNetProfilerProvider(const IAnalysisSession& Session);` (scope `TraceServices`)

### `Source/Developer/TraceServices/Public/TraceServices/Model/ObjectProvider.h` (Public)


#### enum `TraceServices::EObjectInfoFlags`  
`enum class EObjectInfoFlags : uint32`  
_L18-26_
- L20 _public enumerator_ `None = 0`
- L21 _public enumerator_ `IsField = 1 << 0`
- L22 _public enumerator_ `IsStruct = 1 << 1`
- L23 _public enumerator_ `IsClass = 1 << 2`
- L24 _public enumerator_ `IsFunction = 1 << 3`
- L25 _public enumerator_ `IsPackage = 1 << 4`

#### struct `TraceServices::FObjectInfo`  
`struct FObjectInfo`  
_L29-56_
- L31 _public member_ `uint32 Id = uint32(-1);`
- L32 _public member_ `uint32 ClassId = uint32(-1);`
- L33 _public member_ `uint32 OuterId = uint32(-1);`
- L34 _public member_ `const TCHAR* Name = nullptr;`
- L35 _public member_ `uint32 Flags = 0;`
- L36 _public member_ `EObjectInfoFlags FlagsEx = EObjectInfoFlags::None;`
- L38 _public member_ `const TCHAR* VersePath = nullptr;`
- L40 _public member_ `uint64 SystemMemoryBytes = 0;`
- L41 _public member_ `uint64 VideoMemoryBytes = 0;`
- L42 _public member_ `uint64 TotalSystemMemoryBytes = 0;`
- L43 _public member_ `uint64 TotalVideoMemoryBytes = 0;`
- L45 _public member_ `uint32 SuperId = uint32(-1);`
- L46 _public member_ `uint32 InheritanceSuperId = uint32(-1);`
- L47 _public member_ `int32 StructureSize = 0;`
- L49 _public member_ `uint32 FunctionFlags = 0;`
- L50 _public member_ `uint8 FunctionNumParms = 0;`
- L51 _public member_ `uint16 FunctionParmsSize = 0;`
- L53 _public member_ `uint64 PackageId = 0;`
- L54 _public member_ `const TCHAR* PackagePath = nullptr;`
- L55 _public member_ `const TCHAR* SourcePackageName = nullptr;` — Editor source package name; set when it differs from the runtime Name (e.g. streamed/instanced level packages)

#### struct `TraceServices::FObjectReferenceInfo`  
`struct FObjectReferenceInfo`  
_L58-62_
- L60 _public member_ `uint32 ReferencerId = 0;`
- L61 _public member_ `uint32 ObjectId = 0;`

#### class `TraceServices::IObjectSnapshot`  
`class IObjectSnapshot`  
_L64-82_
- L67 _public prototype_ `virtual ~IObjectSnapshot() = default;`
- L68 _public prototype_ `virtual uint32 GetId() const = 0;`
- L69 _public prototype_ `virtual double GetStartTime() const = 0;`
- L70 _public prototype_ `virtual double GetEndTime() const = 0;`
- L71 _public prototype_ `virtual const FObjectInfo* GetObject(uint32 Id) const = 0;`
- L72 _public prototype_ `virtual uint32 GetObjectArrayNum() const = 0;`
- L73 _public prototype_ `virtual uint32 GetObjectCount() const = 0;`
- L74 _public prototype_ `virtual uint32 GetNumReferences() const = 0;`
- L75 _public prototype_ `virtual uint32 GetTracedObjectArrayNum() const = 0;`
- L76 _public prototype_ `virtual uint32 GetTracedObjectArrayNumMinusAvailable() const = 0;`
- L77 _public prototype_ `virtual uint32 GetTracedObjectArrayNumPermanent() const = 0;`
- L78 _public prototype_ `virtual bool HasTotalMemorySizes() const = 0;`
- L79 _public prototype_ `virtual TConstArrayView<FObjectInfo> GetObjectsArray() const = 0;`
- L80 _public prototype_ `virtual TConstArrayView<FObjectReferenceInfo> GetReferencesArray() const = 0;`
- L81 _public prototype_ `virtual void SaveAs(const TCHAR* CsvFileName) const = 0;`

#### class `TraceServices::IObjectEditableSnapshot`  
`class IObjectEditableSnapshot : public IObjectSnapshot`  
_L84-94_
- inherits: `IObjectSnapshot`
- L87 _public prototype_ `virtual ~IObjectEditableSnapshot() = default;`
- L89 _public prototype_ `virtual FObjectInfo* GetEditableObject(uint32 ObjectId) = 0;`
- L90 _public prototype_ `virtual void EnableTotalMemorySizes() = 0;`
- L91 _public prototype_ `virtual void SetTracedObjectArrayNum(uint32 Count) = 0;`
- L92 _public prototype_ `virtual void SetTracedObjectArrayNumMinusAvailable(uint32 Count) = 0;`
- L93 _public prototype_ `virtual void SetTracedObjectArrayNumPermanent(uint32 Count) = 0;`

#### class `TraceServices::IObjectProvider`  
`class IObjectProvider : public IProvider`  
_L96-160_
- inherits: `IProvider`
- L99 _public prototype_ `virtual ~IObjectProvider() = default;`
- L101 _public prototype_ `virtual void BeginRead() const = 0;`
- L102 _public prototype_ `virtual void EndRead() const = 0;`
- L103 _public prototype_ `virtual void ReadAccessCheck() const = 0;`
- L109 _public prototype_ `virtual void EnumerateObjects(uint32 SnapshotId, TFunctionRef<bool(const FObjectInfo&)> Callback) const = 0;` — Enumerates the available objects. The enumeration stops if the callback returns false.
- L115 _public prototype_ `virtual const FObjectInfo* GetObject(uint32 SnapshotId, uint32 ObjectId) const = 0;` — Gets the object with the specified Id. The resulting pointer is valid only under the current read lock.
- L121 _public prototype_ `virtual const FObjectInfo* FindObject(uint32 SnapshotId, FStringView Name) const = 0;` — Finds the object with the specified name. The resulting pointer is valid only under the current read lock.
- L126 _public prototype_ `virtual uint32 GetCurrentSnapshotObjectCount() const = 0;` — Gets the current number of analyzed objects in the snapshot being currently modified.
- L131 _public prototype_ `virtual uint32 GetCurrentSnapshotTotalObjectCount() const = 0;` — Gets the total number of objects traced in the snapshot being currently modified.
- L136 _public prototype_ `virtual uint32 GetNumSnapshots() const = 0;` — Gets the number of available snapshots.
- L142 _public prototype_ `virtual void EnumerateSnapshots(TFunctionRef<bool(const IObjectSnapshot&)> Callback) const = 0;` — Enumerates the available snapshots. The enumeration stops if the callback returns false.
- L148 _public prototype_ `virtual const IObjectSnapshot* GetSnapshot(uint32 SnapshotId) const = 0;` — Gets the snapshot with the specified Id. The resulting pointer is valid only under the current read lock.
- L153 _public prototype_ `virtual bool IsCurrentSnapshotValid() const = 0;` — Checks the validity of the snapshot being currently modified.
- L159 _public prototype_ `virtual const IObjectSnapshot* GetLowerBoundSnapshot(double Time) const = 0;` — Finds the last snapshot with StartTime <= provided Time. The resulting pointer is valid only under the current read lock.

#### class `TraceServices::IEditableObjectProvider`  
`class IEditableObjectProvider : public IEditableProvider`  
_L162-211_
- inherits: `IEditableProvider`
- L165 _public prototype_ `virtual ~IEditableObjectProvider() = default;`
- L171 _public prototype_ `virtual IObjectEditableSnapshot* GetCurrentSnapshot() = 0;` — Gets the current snapshot. The resulting pointer is valid only under the current edit lock.
- L177 _public prototype_ `virtual IObjectEditableSnapshot* BeginSnapshot(double Time) = 0;` — Begins a new snapshot. The resulting pointer is valid only under the current edit lock.
- L183 _public prototype_ `virtual IObjectEditableSnapshot* EndSnapshot(double Time) = 0;` — Ends the current snapshot. The resulting pointer is valid only under the current edit lock.
- L190 _public prototype_ `virtual FObjectInfo* AddObject(uint32 ObjectId, uint32 ClassId, uint32 OuterId, uint32 Flags, const TCHAR* PersistentName) = 0;` — Adds an object declaration, to the current snapshot. It is only valid to call this between BeginSnapshot() and EndSnapshot() calls. The resulting pointer is valid only under the current edit lock.
- L197 _public prototype_ `virtual FObjectInfo* GetEditableObject(uint32 Id) = 0;` — Gets the object identified by id. It is only valid to call this between BeginSnapshot() and EndSnapshot() calls. The resulting pointer is valid only under the current edit lock.
- L204 _public prototype_ `virtual FObjectReferenceInfo* AddObjectReference(uint32 ReferencerId, uint32 ObjectId) = 0;` — Adds a dependency between objects, to the current snapshot. It is only valid to call this between BeginSnapshot() and EndSnapshot() calls. The resulting pointer is valid only under the current edit lock.
- L210 _public function_ `virtual const IObjectProvider* GetReadProvider() const` — Gets the read provider. @returns The read only provider or nullptr if not available.

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace TraceServices`
- L16 _prototype_ `FUtf8String FunctionFlagsToUtf8String(uint32 Flags);` (scope `TraceServices`)
- L27 _prototype_ `ENUM_CLASS_FLAGS(EObjectInfoFlags);` (scope `TraceServices`)
- L213 _prototype_ `FName GetObjectProviderName();` (scope `TraceServices`)
- L214 _prototype_ `const IObjectProvider* ReadObjectProvider(const IAnalysisSession& Session);` (scope `TraceServices`)
- L215 _prototype_ `IEditableObjectProvider* EditObjectProvider(IAnalysisSession& Session);` (scope `TraceServices`)

### `Source/Developer/TraceServices/Public/TraceServices/Model/Regions.h` (Public)


#### struct `TraceServices::FRegionCategory`  
`struct FRegionCategory`  
_L19-22_
- L21 _public member_ `const TCHAR* Name = nullptr;`

#### struct `TraceServices::FRegionTimer`  
`struct FRegionTimer`  
_L24-28_
- L26 _public member_ `const TCHAR* Name = nullptr;`
- L27 _public member_ `const FRegionCategory* Category = nullptr;`

#### struct `TraceServices::FTimeRegion`  
`struct FTimeRegion`  
_L31-46_
- L33 _public member_ `const FRegionTimer* Timer = nullptr;` — name and category of the region
- L35 _public member_ `double BeginTime = std::numeric_limits<double>::infinity();`
- L36 _public member_ `double EndTime = std::numeric_limits<double>::infinity();`
- L38 _public member_ `uint64 Id = 0;` — 0 if the region is identified by Name only
- L39 _public member_ `int32 Depth = -1;`
- L42 _public member_ `const TCHAR* Text = nullptr;` — `UE_DEPRECATED(5.7, "Use instead Timer->Name")`
- L45 _public member_ `const TCHAR* Category = nullptr;` — `UE_DEPRECATED(5.7, "Use instead Timer->Category->Name")` — this will be nullptr for regions without a Category

#### class `TraceServices::FRegionLane`  
`class FRegionLane`  
_L49-75_
- L55 _public function_ `FRegionLane(ILinearAllocator& InAllocator) : Regions(InAllocator, 512)`
- L57 _public function_ `int32 Num() const`
- L64 _public prototype_ `bool EnumerateRegions(double IntervalStart, double IntervalEnd, TFunctionRef<bool(const FTimeRegion&)> Callback) const;` — Call Callback for every region overlapping the interval defined by IntervalStart and IntervalEnd @param Callback a callback called for each region. Return false to abort iteration. @returns true if the enumeration finished, false if it was aborted by the callback returning false
- L71 _public prototype_ `bool EnumerateRegionsBackwards(double IntervalEnd, double IntervalStart, TFunctionRef<bool(const FTimeRegion&)> Callback) const;` — Call Callback for every region overlapping the interval defined by IntervalEnd and IntervalStart @param Callback a callback called for each region. Return false to abort iteration. @returns true if the enumeration finished, false if it was aborted by the callback returning false
- L74 _private member_ `TPagedArray<FTimeRegion> Regions;`

#### struct `TraceServices::FLaneEnumeration`  
`struct FLaneEnumeration`  
_L77-92_
- L79 _public member_ `const FRegionLane& Lane;`
- L80 _public member_ `int32 IntervalStart;`
- L81 _public member_ `int32 IntervalEnd;`
- L83 _public function_ `bool operator<(const FLaneEnumeration& rhs) const`
- L88 _public function_ `bool operator>(const FLaneEnumeration& rhs) const`

#### class `TraceServices::IRegionTimeline`  
`class IRegionTimeline`  
_L97-141_
- desc: Sorts a set of Timing Regions into a stack of individual lanes without overlaps for display
- L103 _public prototype_ `virtual const TCHAR* GetCategoryName() const = 0;` — @return the category name of this timeline if filtered or nullptr
- L108 _public prototype_ `virtual const FRegionCategory* GetCategory() const = 0;` — @return the category of this timeline if filtered or nullptr
- L113 _public prototype_ `virtual int32 GetLaneCount() const = 0;` — @return the number of lanes
- L120 _public prototype_ `virtual const FRegionLane* GetLane(int32 Index) const = 0;` — Direct access to a certain lane at a given index/depth. The pointer is valid only in the current read scope. @return a pointer to the lane at the specified depth index or nullptr if Index > GetLaneCount()-1
- L128 _public prototype_ `virtual bool EnumerateRegions(double IntervalStart, double IntervalEnd, TFunctionRef<bool(const FTimeRegion&)> Callback) const = 0;` — Enumerates all regions that overlap a certain time interval. Will enumerate by depth but does not expose lanes. @param Callback a callback called for each region. Return false to abort iteration. @returns true if the enumeration finished, false if it was aborted by the callback returning false
- L136 _public prototype_ `virtual bool EnumerateRegionsBackwards(double IntervalEnd, double IntervalStart, TFunctionRef<bool(const FTimeRegion&)> Callback) const = 0;` — Enumerates all regions that overlap a certain time interval in reverse. Will enumerate by depth but does not expose lanes. @param Callback a callback called for each region. Return false to abort iteration. @returns true if the enumeration finished, false if it was aborted by the callback returning false
- L140 _public prototype_ `virtual void EnumerateLanes(TFunctionRef<void(const FRegionLane&, const int32)> Callback) const = 0;` — Will call Callback(Lane, Depth) for each lane in order.

#### class `TraceServices::IRegionProvider`  
`class IRegionProvider : public IProvider`  
_L143-223_
- inherits: `IProvider`
- L147 _public prototype_ `virtual ~IRegionProvider() override = default;`
- L154 _public prototype_ `virtual bool EnumerateCategories(TFunctionRef<bool(const FRegionCategory&)> Callback) const = 0;` — Enumerates all region categories. @param Callback a callback called for each region category. Return false to abort iteration. @returns true if the enumeration finished, false if it was aborted by the callback returning false
- L161 _public prototype_ `virtual bool EnumerateTimers(TFunctionRef<bool(const FRegionTimer&)> Callback) const = 0;` — Enumerates all region timers (unique regions by name). @param Callback a callback called for each region timer. Return false to abort iteration. @returns true if the enumeration finished, false if it was aborted by the callback returning false
- L167 _public prototype_ `virtual void EnumerateTimelinesByCategory(TFunctionRef<void(const IRegionTimeline& , const TCHAR* )> Callback) const = 0;` — Enumerates all timelines, this includes the uncategorized timeline with uncategorized regions and individual timelines for each Category @param Callback a callback called for each timeline. Second parameter contains Category or nullptr for the uncategorized timeline.
- L172 _public prototype_ `virtual const IRegionTimeline& GetDefaultTimeline() const = 0;` — @return the default timeline containing all regions without filtering
- L177 _public prototype_ `virtual const IRegionTimeline* GetTimelineForCategory(const TCHAR* Category) const = 0;` — @return the timeline for a given Category or the timeline with uncategorized regions if Category is nullptr. Returns nullptr if the category was invalid/not found
- L182 _public prototype_ `virtual const TCHAR* GetUncategorizedRegionCategoryName() const = 0;` — @return the string used to store regions with no explicit category set
- L187 _public prototype_ `virtual uint64 GetRegionCount() const = 0;` — @return the amount of currently known regions (including open-ended ones)
- L193 _public prototype_ `virtual int32 GetLaneCount() const = 0;` — `UE_DEPRECATED(5.6, "Use GetDefaultTimeline().GetLaneCount() or EnumerateTimelinesByCategory() to access timelines instead.")` — @return the number of lanes of the default timeline
- L201 _public prototype_ `virtual const FRegionLane* GetLane(int32 Index) const = 0;` — `UE_DEPRECATED(5.6, "Use GetDefaultTimeline().GetLane() or EnumerateTimelinesByCategory() to access timelines instead.")` — Direct access to a certain lane at a given index/depth of the default timeline. The pointer is valid only in the current read scope. @return a pointer to the lane at the specified depth index or nullptr if Index > GetLaneCount()-1
- L210 _public prototype_ `virtual bool EnumerateRegions(double IntervalStart, double IntervalEnd, TFunctionRef<bool(const FTimeRegion& )> Callback) const = 0;` — `UE_DEPRECATED(5.6, "Use GetDefaultTimeline().EnumerateRegions() or EnumerateTimelinesByCategory() to access timelines instead.")` — Enumerates all regions that overlap a certain time interval. Will enumerate by depth but does not expose lanes. @param Callback a callback called for each region. Return false to abort iteration. @returns true if the enumeration finished, false if it was aborted by the callback returning false
- L216 _public prototype_ `virtual void EnumerateLanes(TFunctionRef<void(const FRegionLane& , const int32 )> Callback) const = 0;` — `UE_DEPRECATED(5.6, "Use GetDefaultTimeline().EnumerateLanes() or EnumerateTimelinesByCategory() to access timelines instead.")` — Will call Callback(Lane, Depth) for each lane in order.
- L222 _public prototype_ `virtual uint64 GetUpdateCounter() const = 0;` — @return a monotonically increasing counter that is updated each time new data is added to the provider. This can be used to detect when to update any (UI-)state dependent on the provider during analysis.

#### class `TraceServices::IEditableRegionProvider`  
`class IEditableRegionProvider : public IEditableProvider`  
_L228-280_
- inherits: `IEditableProvider`
- desc: The interface to a provider that can consume mutations of region events from a session.
- L232 _public prototype_ `virtual ~IEditableRegionProvider() override = default;`
- L234 _public prototype_ `virtual const FRegionCategory* RegisterRegionCategory(const TCHAR* Name) = 0;`
- L235 _public prototype_ `virtual const FRegionTimer* RegisterRegionTimer(const TCHAR* Name, const FRegionCategory* Category = nullptr) = 0;`
- L245 _public prototype_ `virtual void AppendRegionBegin(const TCHAR* Name, double Time, const TCHAR* Category = nullptr) = 0;` — Append a new begin event of a region from the trace session. Prefer opening/closing regions with an Id, since string names are not unique. @param Name		The string name of the region. @param Time		The time in seconds of the begin event of this region. @param Category	The category associated with this region, use nullptr if no category has been set
- L256 _public prototype_ `virtual void AppendRegionBeginWithId(const TCHAR* Name, uint64 Id, double Time, const TCHAR* Category = nullptr) = 0;` — Append a new begin event of a region from the trace session. Id will be used to uniquely identify the new region. @param Name		The string name of the region. @param Id		The Id of the region. Used to uniquely identify regions with the same name. @param Time		The time in seconds of the begin event of this region. @param Category	The category associated with this region, use nullptr if no category has been set
- L265 _public prototype_ `virtual void AppendRegionEnd(const TCHAR* Name, double Time) = 0;` — Append a new end event of a region from the trace session. Prefer opening/closing regions with an Id, since string names are not unique. @param Name		The string name of the region. @param Time		The time in seconds of the end event of this region.
- L273 _public prototype_ `virtual void AppendRegionEndWithId(const uint64 Id, double Time) = 0;` — Append a new end event of a region from the trace session. The region is identified by Id. @param Id		The Id of the region. @param Time		The time in seconds of the end event of this region.
- L279 _public prototype_ `virtual void OnAnalysisSessionEnded() = 0;` — Called from the analyzer once all events have been processed. Allows post-processing and error reporting for regions that were never closed.

#### Free symbols / members of external scopes

- L14 _macro_ `#define UE_API TRACESERVICES_API`
- L16 _namespace_ `namespace TraceServices`
- L284 _prototype_ `FName GetRegionProviderName();` (scope `TraceServices`)
- L285 _prototype_ `const IRegionProvider& ReadRegionProvider(const IAnalysisSession& Session);` (scope `TraceServices`)
- L286 _prototype_ `IEditableRegionProvider& EditRegionProvider(IAnalysisSession& Session);` (scope `TraceServices`)

### `Source/Developer/TraceServices/Public/TraceServices/Model/Screenshot.h` (Public)


#### struct `TraceServices::FScreenshot`  
`struct FScreenshot`  
_L13-25_
- L15 _public member_ `uint32 Id;`
- L16 _public member_ `FString Name;`
- L17 _public member_ `double Timestamp;`
- L18 _public member_ `uint32 Width;`
- L19 _public member_ `uint32 Height;`
- L20 _public member_ `uint32 ChunkNum;`
- L21 _public member_ `uint32 Size;`
- L22 _public member_ `TArray<uint8> Data;`
- L24 _public member_ `static const uint32 InvalidScreenshotId = (uint32)-1;`

#### class `TraceServices::IScreenshotProvider`  
`class IScreenshotProvider : public IProvider`  
_L27-34_
- inherits: `IProvider`
- L31 _public prototype_ `virtual ~IScreenshotProvider() = default;`
- L33 _public prototype_ `virtual const TSharedPtr<const FScreenshot> GetScreenshot(uint32 Id) const = 0;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace TraceServices`
- L36 _prototype_ `FName GetScreenshotProviderName();` (scope `TraceServices`)
- L37 _prototype_ `const IScreenshotProvider& ReadScreenshotProvider(const IAnalysisSession& Session);` (scope `TraceServices`)

### `Source/Developer/TraceServices/Public/TraceServices/Model/StackSamples.h` (Public)


#### struct `TraceServices::FStackSampleFrame`  
`struct FStackSampleFrame`  
_L19-24_
- L21 _public member_ `uint64 Address = 0;`
- L22 _public member_ `uint32 TimerId = 0;`
- L23 _public member_ `const FResolvedSymbol* Symbol = nullptr;`

#### struct `TraceServices::FStackSampleThread`  
`struct FStackSampleThread`  
_L28-33_
- L30 _public member_ `uint32 SystemThreadId = 0;`
- L31 _public member_ `const TCHAR* Name = nullptr;`
- L32 _public member_ `const FStackSampleTimeline* Timeline = nullptr;`

#### class `TraceServices::IStackSamplesProvider`  
`class IStackSamplesProvider : public IProvider`  
_L35-50_
- inherits: `IProvider`
- L39 _public prototype_ `virtual ~IStackSamplesProvider() = default;`
- L41 _public prototype_ `virtual uint32 GetStackFrameCount() const = 0;`
- L42 _public prototype_ `virtual void EnumerateStackFrames(TFunctionRef<void(const FStackSampleFrame& Frame)> Callback) const = 0;`
- L44 _public prototype_ `virtual uint32 GetThreadCount() const = 0;`
- L45 _public prototype_ `virtual void EnumerateThreads(TFunctionRef<void(const FStackSampleThread& Thread)> Callback) const = 0;`
- L47 _public prototype_ `virtual uint32 GetTimelineCount() const = 0;`
- L48 _public prototype_ `virtual void EnumerateTimelines(TFunctionRef<void(const FStackSampleTimeline& Timeline, const FStackSampleThread& Thread)> Callback) const = 0;`
- L49 _public prototype_ `virtual const FStackSampleTimeline* GetTimeline(uint32 SystemThreadId) const = 0;`

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace TraceServices`
- L26 _typedef_ `typedef ITimeline<FTimingProfilerEvent> FStackSampleTimeline;` (scope `TraceServices`)
- L52 _prototype_ `FName GetStackSamplesProviderName();` (scope `TraceServices`)
- L53 _prototype_ `const IStackSamplesProvider* ReadStackSamplesProvider(const IAnalysisSession& Session);` (scope `TraceServices`)

### `Source/Developer/TraceServices/Public/TraceServices/Model/Strings.h` (Public)


#### struct `TraceServices::FStringDefinition`  
`struct FStringDefinition`  
_L9-21_
- L14 _public member_ `const TCHAR* Display;` — Display string. The pointer is valid during the analysis session.
- L16 _public function_ `static FString ToString(const void* Data)`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace TraceServices`

### `Source/Developer/TraceServices/Public/TraceServices/Model/TableImport.h` (Public)


#### class `TraceServices::ITableImportData`  
`class ITableImportData`  
_L15-18_
- L17 _private prototype_ `TSharedPtr<ITable<FImportTableRow>> GetTable();`

#### enum `TraceServices::ETableImportResult`  
`enum class ETableImportResult : uint32`  
_L20-24_
- L22 _public enumerator_ `ESuccess = 0`
- L23 _public enumerator_ `EFail = 1`

#### struct `TraceServices::FTableImportCallbackParams`  
`struct FTableImportCallbackParams`  
_L26-32_
- L28 _public member_ `FName TableId;`
- L29 _public member_ `ETableImportResult Result;`
- L30 _public member_ `TSharedPtr<ITable<FImportTableRow>> Table;`
- L31 _public member_ `TArray<TSharedRef<FTokenizedMessage>> Messages;`

#### class `TraceServices::FTableImportService`  
`class FTableImportService`  
_L34-40_
- L37 _public typedef_ `typedef TFunction<void(TSharedPtr<FTableImportCallbackParams>)> TableImportCallback;`
- L39 _public prototype_ `static void ImportTable(const FString& InPath, FName TableId, TableImportCallback InCallback);`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace TraceServices`

### `Source/Developer/TraceServices/Public/TraceServices/Model/TableMerge.h` (Public)


#### enum `TraceServices::ETableDiffResult`  
`enum class ETableDiffResult : uint32`  
_L12-16_
- L14 _public enumerator_ `ESuccess = 0`
- L15 _public enumerator_ `EFail = 1`

#### struct `TraceServices::FTableDiffCallbackParams`  
`struct FTableDiffCallbackParams`  
_L18-23_
- L20 _public member_ `ETableDiffResult Result;`
- L21 _public member_ `TSharedPtr<IUntypedTable> Table;`
- L22 _public member_ `TArray<TSharedRef<FTokenizedMessage>> Messages;`

#### class `TraceServices::FTableMergeService`  
`class FTableMergeService`  
_L25-31_
- L28 _public typedef_ `typedef TFunction<void(TSharedPtr<FTableDiffCallbackParams>)> TableDiffCallback;`
- L30 _public prototype_ `static void MergeTables(const TSharedPtr<IUntypedTable>& TableA, const TSharedPtr<IUntypedTable>& TableB, TableDiffCallback InCallback);`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace TraceServices`

### `Source/Developer/TraceServices/Public/TraceServices/Model/TasksProfiler.h` (Public)


#### struct `TraceServices::FTaskInfo`  
`struct FTaskInfo`  
_L17-80_
- desc: task biography
- L19 _public prototype_ `FTaskInfo() = default;`
- L21 _public member_ `TaskTrace::FId Id = TaskTrace::InvalidId;`
- L24 _public member_ `const TCHAR* DebugName = nullptr;` — this members are filled during task launch
- L25 _public member_ `bool bTracked = false;` — if the task is awaitable, not awaitable tasks will never be "completed", they are done when their execution is finished
- L26 _public member_ `int32 ThreadToExecuteOn = ENamedThreads::AnyThread;` — ENamedThreads::Type - combines the info about thread to execute on (one of named threads or a worker
- L30 _public member_ `static constexpr double InvalidTimestamp = -std::numeric_limits<double>::max();`
- L33 _public member_ `double CreatedTimestamp = InvalidTimestamp;` — some tasks can be created with delayed launch, otherwise "created" and "launched" timestamps and thread IDs are equal
- L35 _public member_ `double LaunchedTimestamp = InvalidTimestamp;` — the moment and the place when the task was launched
- L37 _public member_ `double ScheduledTimestamp = InvalidTimestamp;` — the moment and the place when all task's dependencies are resolved and it's added to the execution queue
- L39 _public member_ `double StartedTimestamp = InvalidTimestamp;` — execution started
- L41 _public member_ `double FinishedTimestamp = InvalidTimestamp;` — execution finished, but the task can be still not completed waiting for all nested tasks to complete
- L43 _public member_ `double CompletedTimestamp = InvalidTimestamp;` — execution done and all nested tasks are completed
- L45 _public member_ `double DestroyedTimestamp = InvalidTimestamp;` — the last reference is released and the task is destroyed
- L47 _public member_ `uint32 CreatedThreadId = 0;`
- L48 _public member_ `uint32 LaunchedThreadId = 0;`
- L49 _public member_ `uint32 ScheduledThreadId = 0;`
- L50 _public member_ `uint32 StartedThreadId = 0;`
- L51 _public member_ `uint32 CompletedThreadId = 0;`
- L52 _public member_ `uint32 DestroyedThreadId = 0;`
- L55 _public member_ `uint64 TaskSize = 0;` — task size including user-provided task body
- L73 _public member_ `TArray<FRelationInfo> Prerequisites;` — other tasks that must complete before this task can be scheduled
- L75 _public member_ `TArray<FRelationInfo> Subsequents;` — other tasks that wait for this task completion before they'll start execution
- L77 _public member_ `TArray<FRelationInfo> ParentTasks;` — other tasks that have this task as a nested
- L79 _public member_ `TArray<FRelationInfo> NestedTasks;` — the task is completed only after all nested tasks are completed

#### struct `TraceServices::FTaskInfo::FRelationInfo`  
`struct FRelationInfo`  
_L58-70_
- desc: relation with another task, when and where it was established
- L60 _public function_ `FRelationInfo(TaskTrace::FId InRelativeId, double InTimestamp, uint32 InThreadId) : RelativeId(InRelativeId) , Timestamp(InTimestamp) , ThreadId(InThreadId)`
- L67 _public member_ `TaskTrace::FId RelativeId;`
- L68 _public member_ `double Timestamp;`
- L69 _public member_ `uint32 ThreadId;`

#### struct `TraceServices::FWaitingForTasks`  
`struct FWaitingForTasks`  
_L82-87_
- L84 _public member_ `TArray<TaskTrace::FId> Tasks;`
- L85 _public member_ `double StartedTimestamp;`
- L86 _public member_ `double FinishedTimestamp = FTaskInfo::InvalidTimestamp;`

#### enum `TraceServices::ETaskEnumerationOption`  
`enum class ETaskEnumerationOption`  
_L89-100_
- L91 _public enumerator_ `Alive`
- L92 _public enumerator_ `Launched`
- L93 _public enumerator_ `Active`
- L94 _public enumerator_ `WaitingForPrerequisites`
- L95 _public enumerator_ `Queued`
- L96 _public enumerator_ `Executing`
- L97 _public enumerator_ `WaitingForNested`
- L98 _public enumerator_ `Completed`
- L99 _public enumerator_ `Count`

#### enum `TraceServices::ETaskEnumerationResult`  
`enum class ETaskEnumerationResult`  
_L102-106_
- L104 _public enumerator_ `Continue`
- L105 _public enumerator_ `Stop`

#### class `TraceServices::ITasksProvider`  
`class ITasksProvider : public IProvider`  
_L109-132_
- inherits: `IProvider`
- desc: query interface to tasks info
- L112 _public typedef_ `typedef TFunctionRef<ETaskEnumerationResult(const FTaskInfo& Task)> TaskCallback;`
- L114 _public prototype_ `virtual ~ITasksProvider() = default;`
- L117 _public prototype_ `virtual const FTaskInfo* TryGetTask(uint32 ThreadId, double Timestamp) const = 0;` — returns a task for given thread and timestamp, if any, otherwise `nullptr`
- L119 _public prototype_ `virtual const FTaskInfo* TryGetTask(TaskTrace::FId TaskId) const = 0;` — returns task info for given task ID
- L122 _public prototype_ `virtual const FWaitingForTasks* TryGetWaiting(const TCHAR* TimerName, uint32 ThreadId, double Timestamp) const = 0;` — returns an info about waiting for tasks completion for given thread and timestamp, if any, otherwise `nullptr`
- L125 _public prototype_ `virtual TArray<TaskTrace::FId> TryGetParallelForTasks(const TCHAR* TimerName, uint32 ThreadId, double StartTime, double EndTime) const = 0;` — returns an info about ParallelFor tasks for given timer
- L128 _public prototype_ `virtual int64 GetNumTasks() const = 0;` — returns the number of tasks stored in the provider
- L131 _public prototype_ `virtual void EnumerateTasks(double StartTime, double EndTime, ETaskEnumerationOption EnumerationOption, TaskCallback Callback) const = 0;` — Calls the callback for each task stored in the provider with CreatedTimestamp <= EndTime and FinishedTimestamp >= StartTime

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace TraceServices`
- L134 _prototype_ `FName GetTaskProviderName();` (scope `TraceServices`)
- L135 _prototype_ `const ITasksProvider* ReadTasksProvider(const IAnalysisSession& Session);` (scope `TraceServices`)

### `Source/Developer/TraceServices/Public/TraceServices/Model/Threads.h` (Public)


#### struct `TraceServices::FThreadInfo`  
`struct FThreadInfo`  
_L14-19_
- L16 _public member_ `uint32 Id;`
- L17 _public member_ `const TCHAR* Name;`
- L18 _public member_ `const TCHAR* GroupName;`

#### class `TraceServices::IThreadProvider`  
`class IThreadProvider : public IProvider`  
_L21-29_
- inherits: `IProvider`
- L25 _public prototype_ `virtual ~IThreadProvider() = default;`
- L26 _public prototype_ `virtual uint64 GetModCount() const = 0;`
- L27 _public prototype_ `virtual void EnumerateThreads(TFunctionRef<void(const FThreadInfo&)> Callback) const = 0;`
- L28 _public prototype_ `virtual const TCHAR* GetThreadName(uint32 ThreadId) const = 0;`

#### class `TraceServices::IEditableThreadProvider`  
`class IEditableThreadProvider : public IEditableProvider`  
_L34-54_
- inherits: `IEditableProvider`
- desc: An interface that can consume thread related events from a session.
- L38 _public prototype_ `virtual ~IEditableThreadProvider() = default;`
- L47 _public prototype_ `virtual void AddThread(uint32 Id, const TCHAR* Name, EThreadPriority Priority) = 0;` — Note the existence of a new thread. @param Id			The thread identity. @param Name		The name the user may know the thread by, if available. @param Priority	The system priority level of the thread, if available.
- L53 _public function_ `virtual const IThreadProvider* GetReadProvider() const` — Gets the read provider. @returns The read only provider or nullptr if not available.

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace TraceServices`
- L56 _prototype_ `FName GetThreadProviderName();` (scope `TraceServices`)
- L57 _prototype_ `const IThreadProvider& ReadThreadProvider(const IAnalysisSession& Session);` (scope `TraceServices`)
- L58 _prototype_ `IEditableThreadProvider& EditThreadProvider(IAnalysisSession& Session);` (scope `TraceServices`)

### `Source/Developer/TraceServices/Public/TraceServices/Model/TimingProfiler.h` (Public)


#### struct `TraceServices::FTimingProfilerEvent`  
`struct FTimingProfilerEvent`  
_L27-30_
- L29 _public member_ `uint32 TimerIndex = uint32(-1);`

#### struct `TraceServices::FMetadataSpec`  
`struct FMetadataSpec`  
_L35-41_
- L37 _public member_ `const TCHAR* Format = nullptr;`
- L38 _public member_ `TArray<const TCHAR*> FieldNames;`
- L40 _public member_ `static const uint32 InvalidMetadataSpecId = (uint32)-1;`

#### enum `TraceServices::ETimingProfilerTimerType`  
`enum class ETimingProfilerTimerType : uint8`  
_L43-55_
- L45 _public enumerator_ `CpuScope`
- L46 _public enumerator_ `CpuSampling`
- L47 _public enumerator_ `GpuScope`
- L48 _public enumerator_ `VerseSampling`
- L50 _public enumerator_ `Count`
- L52 _public enumerator_ `CPU = CpuScope` — temporary backward compatibility
- L53 _public enumerator_ `GPU = GpuScope` — temporary backward compatibility
- L54 _public enumerator_ `Verse = VerseSampling` — temporary backward compatibility

#### struct `TraceServices::FTimingProfilerTimer`  
`struct FTimingProfilerTimer`  
_L57-78_
- L59 _public member_ `const TCHAR* Name = nullptr;`
- L60 _public member_ `const TCHAR* File = nullptr;`
- L61 _public member_ `uint32 MetadataSpecId = FMetadataSpec::InvalidMetadataSpecId;`
- L63 _public member_ `uint32 Id = 0;`
- L74 _public function_ `bool HasValidMetadataSpecId() const`

#### union `TraceServices::FTimingProfilerTimer::(anonymous)`  
``  
_L65-72_

#### struct `TraceServices::FTimingProfilerTimer::__anon4ee8fe1e010a::(anonymous)`  
``  
_L67-70_

#### struct `TraceServices::FTimingProfilerAggregatedStats`  
`struct FTimingProfilerAggregatedStats`  
_L80-95_
- L82 _public member_ `const FTimingProfilerTimer* Timer = nullptr;`
- L83 _public member_ `uint64 InstanceCount = 0;`
- L84 _public member_ `double AverageInstanceCount = 0.0;`
- L85 _public member_ `double TotalInclusiveTime = 0.0;`
- L86 _public member_ `double MinInclusiveTime = DBL_MAX;`
- L87 _public member_ `double MaxInclusiveTime = -DBL_MAX;`
- L88 _public member_ `double AverageInclusiveTime = 0.0;`
- L89 _public member_ `double MedianInclusiveTime = 0.0;`
- L90 _public member_ `double TotalExclusiveTime = 0.0;`
- L91 _public member_ `double MinExclusiveTime = DBL_MAX;`
- L92 _public member_ `double MaxExclusiveTime = -DBL_MAX;`
- L93 _public member_ `double AverageExclusiveTime = 0.0;`
- L94 _public member_ `double MedianExclusiveTime = 0.0;`

#### struct `TraceServices::FTimingProfilerButterflyNode`  
`struct FTimingProfilerButterflyNode`  
_L97-105_
- L99 _public member_ `const FTimingProfilerTimer* Timer = nullptr;`
- L100 _public member_ `uint64 Count = 0;`
- L101 _public member_ `double InclusiveTime = 0.0;`
- L102 _public member_ `double ExclusiveTime = 0.0;`
- L103 _public member_ `const FTimingProfilerButterflyNode* Parent = nullptr;`
- L104 _public member_ `TArray<FTimingProfilerButterflyNode*> Children;`

#### struct `TraceServices::FCreateAggregationParams`  
`struct FCreateAggregationParams`  
_L107-160_
- L124 _public member_ `double IntervalStart = 0.0;` — The start timestamp in seconds.
- L127 _public member_ `double IntervalEnd = 0.0;` — The end timestamp in seconds.
- L130 _public member_ `TFunction<bool(uint32)> GpuQueueFilter;` — A function to filter (by GPU Queue Id) the GPU queues to aggregate.
- L133 _public member_ `bool bIncludeOldGpu1 = false;` — A boolean value to specify if aggregation should include the old GPU timeline.
- L136 _public member_ `bool bIncludeOldGpu2 = false;` — A boolean value to specify if aggregation should include the old GPU timeline.
- L139 _public member_ `bool bIncludeVerseSampling = false;` — A boolean value to specify if aggregation should include the Verse Sampling timeline.
- L142 _public member_ `TFunction<bool(uint32)> CpuThreadFilter;` — A function to filter (by Thread Id) the CPU threads to aggregate.
- L145 _public member_ `TArray<const ITimingProfilerTimeline*> CustomTimelines;` — A list of additional custom timelines to aggregate.
- L148 _public member_ `ESortBy SortBy = ESortBy::DontSort;` — Whether to sort the table by a field.
- L151 _public member_ `ESortOrder SortOrder = ESortOrder::DontSort;` — The sorting order
- L154 _public member_ `int TableEntryLimit = 0;` — Limit the entries in aggregation (e.g. "top 100")
- L157 _public member_ `ETraceFrameType FrameType = ETraceFrameType::TraceFrameType_Count;` — The type of frame to use for frame stats aggregation. ETraceFrameType::TraceFrameType_Count means no frame aggregation.
- L159 _public member_ `TSharedPtr<TraceServices::FCancellationToken> CancellationToken;`

#### enum `TraceServices::FCreateAggregationParams::ESortBy`  
`enum class ESortBy`  
_L110-114_
- desc: whether to sort the created aggregation
- L112 _public enumerator_ `DontSort`
- L113 _public enumerator_ `TotalInclusiveTime`

#### enum `TraceServices::FCreateAggregationParams::ESortOrder`  
`enum class ESortOrder`  
_L116-121_
- L118 _public enumerator_ `DontSort`
- L119 _public enumerator_ `Descending`
- L120 _public enumerator_ `Ascending`

#### struct `TraceServices::FCreateButterflyParams`  
`struct FCreateButterflyParams`  
_L162-187_
- L165 _public member_ `double IntervalStart = 0.0;` — The start timestamp in seconds.
- L168 _public member_ `double IntervalEnd = 0.0;` — The end timestamp in seconds.
- L171 _public member_ `TFunction<bool(uint32)> GpuQueueFilter;` — A function to filter the GPU queues to aggregate.
- L174 _public member_ `bool bIncludeOldGpu1 = false;` — A boolean value to specify if aggregation should include the old GPU timeline.
- L177 _public member_ `bool bIncludeOldGpu2 = false;` — A boolean value to specify if aggregation should include the old GPU timeline.
- L180 _public member_ `bool bIncludeVerseSampling = false;` — A boolean value to specify if aggregation should include the Verse Sampling timeline.
- L183 _public member_ `TFunction<bool(uint32)> CpuThreadFilter;` — A function to filter the CPU threads to aggregate.
- L186 _public member_ `TArray<const ITimingProfilerTimeline*> CustomTimelines;` — A list of additional custom timelines to aggregate.

#### class `TraceServices::ITimingProfilerButterfly`  
`class ITimingProfilerButterfly`  
_L189-195_
- L192 _public prototype_ `virtual ~ITimingProfilerButterfly() = default;`
- L193 _public prototype_ `virtual const FTimingProfilerButterflyNode& GenerateCallersTree(uint32 TimerId) = 0;`
- L194 _public prototype_ `virtual const FTimingProfilerButterflyNode& GenerateCalleesTree(uint32 TimerId) = 0;`

#### class `TraceServices::ITimingProfilerTimerReader`  
`class ITimingProfilerTimerReader`  
_L197-217_
- L204 _public prototype_ `virtual uint32 GetTimerCount() const = 0;` — Gets the number of timers. A valid TimerId is an index in the [0 .. TimerCount-1] range.
- L212 _public prototype_ `virtual const FTimingProfilerTimer* GetTimer(uint32 TimerId) const = 0;` — Gets the timer info. The returned pointer is only valid in the current ITimingProfilerTimerReader lock scope. @param TimerId A valid timer id (index in the [0 .. TimerCount-1] range) or a bit inverted metadata id (index in the metadata table). @return The timer info.
- L214 _public function_ `virtual uint32 GetOriginalTimerIdFromMetadata(uint32 MetadataTimerId) const`
- L216 _public function_ `virtual TArrayView<const uint8> GetMetadata(uint32 MetadataTimerId) const`

#### struct `TraceServices::FGpuSignalFence`  
`struct FGpuSignalFence`  
_L219-223_
- L221 _public member_ `double Timestamp = 0.0f;`
- L222 _public member_ `uint64 Value = 0;`

#### struct `TraceServices::FGpuWaitFence`  
`struct FGpuWaitFence`  
_L225-230_
- L227 _public member_ `double Timestamp = 0.0f;`
- L228 _public member_ `uint64 Value = 0;`
- L229 _public member_ `uint32 QueueToWaitForId = 0;`

#### enum `TraceServices::EGpuFenceType`  
`enum EGpuFenceType : uint8`  
_L232-236_
- L234 _public enumerator_ `SignalFence = 0`
- L235 _public enumerator_ `WaitFence = 1`

#### struct `TraceServices::FGpuFenceWrapper`  
`struct FGpuFenceWrapper`  
_L238-242_
- L240 _public member_ `EGpuFenceType FenceType;`
- L241 _public member_ `TVariant<const FGpuSignalFence*, const FGpuWaitFence*> Fence;`

#### struct `TraceServices::FGpuQueueInfo`  
`struct FGpuQueueInfo`  
_L244-258_
- L246 _public member_ `uint32 Id = 0;`
- L247 _public member_ `uint8 GPU = 0;`
- L248 _public member_ `uint8 Index = 0;`
- L249 _public member_ `uint8 Type = 0;`
- L250 _public member_ `const TCHAR* Name = nullptr;`
- L251 _public member_ `uint32 TimelineIndex = ~0;`
- L252 _public member_ `uint32 WorkTimelineIndex = ~0;`
- L254 _public function_ `FString GetDisplayName() const`

#### enum `TraceServices::EEnumerateResult`  
`enum class EEnumerateResult`  
_L260-264_
- L262 _public enumerator_ `Continue`
- L263 _public enumerator_ `Stop`

#### class `TraceServices::ITimingProfilerProvider`  
`class ITimingProfilerProvider : public IProvider`  
_L266-401_
- inherits: `IProvider`
- L270 _public typedef_ `typedef ITimeline<FTimingProfilerEvent> Timeline;`
- L271 _public typedef_ `typedef TFunctionRef<EEnumerateResult(const FGpuSignalFence&)> EnumerateGpuSignalFencesCallback;`
- L272 _public typedef_ `typedef TFunctionRef<EEnumerateResult(const FGpuWaitFence&)> EnumerateGpuWaitFencesCallback;`
- L273 _public typedef_ `typedef TFunctionRef<EEnumerateResult(const FGpuFenceWrapper&)> EnumerateGpuFencesCallback;`
- L274 _public typedef_ `typedef TFunctionRef<EEnumerateResult(uint32 , const FGpuSignalFence& , uint32 , const FGpuWaitFence& )> EnumerateResolvedGpuFencesCallback;`
- L276 _public prototype_ `virtual ~ITimingProfilerProvider() = default;`
- L281 _public prototype_ `virtual bool ReadTimeline(uint32 Index, TFunctionRef<void(const Timeline&)> Callback) const = 0;`
- L282 _public prototype_ `virtual uint32 GetTimelineCount() const = 0;`
- L283 _public prototype_ `virtual void EnumerateTimelines(TFunctionRef<void(const Timeline&)> Callback) const = 0;`
- L289 _public function_ `virtual void ReadTimers(TFunctionRef<void(const ITimingProfilerTimerReader&)> Callback) const` — `UE_DEPRECATED(5.8, "Use GetTimerReader() instead")`
- L297 _public function_ `virtual const ITimingProfilerTimerReader& GetTimerReader() const` — Gets the TimerReader provider. @return A reference to the ITimingProfilerTimerReader object. The reference is valid for the rest of the session lifetime, but it can be used only under a Session Read Scope.
- L313 _public function_ `virtual uint32 GetOriginalTimerIdFromMetadata(uint32 MetadataTimerId) const` — also in ITimingProfilerTimerReader
- L314 _public function_ `virtual TArrayView<const uint8> GetMetadata(uint32 MetadataTimerId) const` — also in ITimingProfilerTimerReader
- L322 _public function_ `virtual const FMetadataSpec* GetMetadataSpec(uint32 MetadataSpecId) const` — Gets the metadata spec associated with the MetadataSpecId. @param MetadataSpecId The Metadata spec id. @return A pointer to the FMetadataSpec or nullptr if no spec is associated with the provided Id. The pointer is only valid in the same Session Read Scope as the function call.
- L330 _public function_ `virtual void MakeTimerDisplayName(const FTimingProfilerTimer& InTimer, TStringBuilder<1024>& InOutDisplayName) const` — Gets the display name for a timer, combining the static name and the format string if present. @param InTimer The timer to create the display name for. @param InOutDisplayName A TStringBuilder where the display name will be created.
- L335 _public function_ `virtual bool HasGpuTiming() const`
- L338 _public function_ `virtual bool GetGpuTimelineIndex(uint32& OutTimelineIndex) const` — Only used for backward compatibility with old GPU Insights.
- L340 _public function_ `virtual bool GetGpu2TimelineIndex(uint32& OutTimelineIndex) const` — Only used for backward compatibility with old GPU Insights.
- L342 _public function_ `virtual void EnumerateGpuQueues(TFunctionRef<void(const FGpuQueueInfo&)> Callback) const`
- L343 _public function_ `virtual bool GetGpuQueueTimelineIndex(uint32 QueueId, uint32& OutTimelineIndex) const`
- L345 _public function_ `virtual void EnumerateGpuSignalFences(uint32 QueueId, double StartTime, double EndTime, EnumerateGpuSignalFencesCallback Callback) const`
- L346 _public function_ `virtual void EnumerateGpuWaitFences(uint32 QueueId, double StartTime, double EndTime, EnumerateGpuWaitFencesCallback Callback) const`
- L347 _public function_ `virtual void EnumerateGpuFences(uint32 QueueId, double StartTime, double EndTime, EnumerateGpuFencesCallback Callback) const`
- L348 _public function_ `virtual void EnumerateResolvedGpuFences(uint32 QueueId, double StartTime, double EndTime, EnumerateResolvedGpuFencesCallback Callback) const`
- L353 _public function_ `virtual bool HasVerseTiming() const`
- L355 _public function_ `virtual bool GetVerseTimelineIndex(uint32& OutTimelineIndex) const`
- L360 _public function_ `virtual bool HasCpuTiming() const`
- L362 _public prototype_ `virtual bool GetCpuThreadTimelineIndex(uint32 ThreadId, uint32& OutTimelineIndex) const = 0;`
- L372 _public function_ `virtual ITable<FTimingProfilerAggregatedStats>* CreateAggregation(const FCreateAggregationParams& Params) const` — Creates a table of aggregated stats. @param Params	The params for the aggregation.
- L379 _public function_ `virtual ITimingProfilerButterfly* CreateButterfly(const FCreateButterflyParams& Params) const` — Creates a butterfly aggregation. @param Params	The params for the aggregation.
- L382 _public function_ `virtual ITimingProfilerButterfly* CreateButterfly(double IntervalStart, double IntervalEnd, TFunctionRef<bool(uint32)> CpuThreadFilter, bool bIncludeGpu) const` — `UE_DEPRECATED(5.6, "Use FCreateButterflyParams instead.")`
- L400 _public function_ `virtual double GetRatioOfThreadsToUse() const` — Gets the Ratio of Threads to use. @return The ratio scaled between 0-1.

#### class `TraceServices::IEditableTimingProfilerProvider`  
`class IEditableTimingProfilerProvider : public IEditableProvider`  
_L403-669_
- inherits: `IEditableProvider`
- L407 _public prototype_ `virtual ~IEditableTimingProfilerProvider() = default;`
- L418 _public function_ `virtual uint32 AddTimer(ETimingProfilerTimerType Type)` — Adds/registers a new timer. @param Type	The type of the new timer. @return		The identity of the new timer.
- L427 _public function_ `virtual uint32 AddTimer(ETimingProfilerTimerType Type, FStringView Name)` — Adds/registers a new timer. @param Type	The type of the new timer. @param Name	The name attached to the timer. @return		The identity of the new timer.
- L446 _public function_ `virtual uint32 AddTimer(ETimingProfilerTimerType Type, FStringView Name, const TCHAR* File, uint32 Line)` — Adds/registers a new timer. @param Type	The type of the new timer. @param Name	The name attached to the timer. @param File	The source file in which the timer is defined. @param Line	The line number of the source file in which the timer is defined. @return		The identity of the new timer.
- L462 _public prototype_ `virtual void SetTimerName(uint32 TimerId, FStringView Name) = 0;` — Updates an existing timer with information. Some information is unavailable when it's created. @param TimerId	The identity of the timer to update. @param Name		The name attached to the timer.
- L472 _public function_ `virtual void SetTimerNameAndLocation(uint32 TimerId, FStringView Name, const TCHAR* File, uint32 Line)` — Updates an existing timer with information. Some information is unavailable when it's created. @param TimerId	The identity of the timer to update. @param Name		The name attached to the timer. @param File		The source file in which the timer is defined. @param Line		The line number of the source file in which the timer is defined.
- L485 _public function_ `virtual void SetTimerLocation(uint32 TimerId, const TCHAR* File, uint32 Line)` — Updates an existing timer with information. Some information is unavailable when it's created. @param TimerId	The identity of the timer to update. @param File		The source file in which the timer is defined. @param Line		The line number of the source file in which the timer is defined.
- L496 _public function_ `virtual void SetMetadataSpec(uint32 TimerId, uint32 MetadataSpecId)` — Sets the metadata spec for an existing timer. @param TimerId			The identity of the timer to update. @param MetadataSpecId	The metadata spec to associate with the timer.
- L506 _public prototype_ `virtual uint32 AddMetadata(uint32 OriginalTimerId, TArray<uint8>&& Metadata) = 0;` — Adds metadata to a CPU or GPU timer. @param OriginalTimerId	The identity of the timer to add metadata to. @param Metadata			The metadata. @return The identity of the metadata.
- L517 _public function_ `virtual void SetMetadata(uint32 MetadataTimerId, TArray<uint8>&& Metadata)` — Sets metadata for the specified MetadataTimerId. The MetadataTimerId must be a value returned by AddMetadata. The function is meant to be used to replace the metadata at a MetadataTimerId. @param MetadataTimerId	The identity of the metadata to replace. @param Metadata			The metadata.
- L529 _public function_ `virtual void SetMetadata(uint32 MetadataTimerId, TArray<uint8>&& Metadata, uint32 NewTimerId)` — Sets metadata for the specified MetadataTimerId and replaces the OriginalTimerId with a new value. The MetadataTimerId must be a value returned by AddMetadata. The function is meant to be used to replace the metadata at a MetadataTimerId. @param MetadataTimerId	The identity of the metadata to replace. @param Metadata			The metadata. @param NewTimerId		The new TimerId. Represents the identity of the timer the metadata is attached to.
- L538 _public prototype_ `virtual TArrayView<uint8> GetEditableMetadata(uint32 MetadataTimerId) = 0;` — Gets metadata by id. @param MetadataTimerId	The identity of the metadata. @return The metadata.
- L547 _public function_ `virtual uint32 AddMetadataSpec(FMetadataSpec&& Metadata)` — Adds a metadata spec to storage. @param Metadata	The metadata spec to add. @return			The identity of the metadata spec.
- L561 _public function_ `virtual uint32 AddGpuTimer(FStringView Name)` — Adds/registers a new GPU timer. @param Name	The name attached to the timer. @param File	The source file in which the timer is defined. @param Line	The line number of the source file in which the timer is defined. @return The identity of the GPU timer.
- L571 _public function_ `virtual void AddGpuQueue(uint32 QueueId, uint8 GPU, uint8 Index, uint8 Type, const TCHAR* Name)` — Adds a new GPU queue. @param QueueId	The GPU queue for which the events are for.
- L579 _public function_ `virtual void AddGpuSignalFence(uint32 QueueId, const FGpuSignalFence& SignalFence)` — Adds a new GPU signal fence to a queue. @param QueueId		The GPU queue that issues the signal. @param SignalFence	The signal fence.
- L587 _public function_ `virtual void AddGpuWaitFence(uint32 QueueId, const FGpuWaitFence& WaitFence)` — Adds a new GPU wait fence to a queue. @param QueueId		The GPU queue that waits. @param WaitFence		The wait fence.
- L596 _public function_ `virtual IEditableTimeline<FTimingProfilerEvent>* GetGpuQueueEditableTimeline(uint32 QueueId)` — Gets an object to receive ordered GPU timing events for a GPU queue. @param QueueId	The queue for which the events are for. @return The object to receive the serial GPU timing events for the specified queue.
- L605 _public function_ `virtual IEditableTimeline<FTimingProfilerEvent>* GetGpuQueueWorkEditableTimeline(uint32 QueueId)` — Gets an object to receive ordered GPU Work timing events for a GPU queue. @param QueueId	The queue for which the events are for. @return The object to receive the serial GPU Work timing events for the specified queue.
- L617 _public function_ `virtual uint32 AddVerseTimer(FStringView Name)` — Adds/registers a new Verse Sampling timer. @param Name	The name attached to the timer. @return The identity of the CPU timer.
- L627 _public function_ `virtual IEditableTimeline<FTimingProfilerEvent>* GetVerseEditableTimeline()` — Gets an object to receive ordered Verse timing events for the Verse sampling. @return The object to receive the serial Verse timing events for Verse sampling.
- L641 _public function_ `virtual uint32 AddCpuTimer(FStringView Name, const TCHAR* File, uint32 Line)` — Adds/registers a new CPU Scope timer. @param Name	The name attached to the timer. @param File	The source file in which the timer is defined. @param Line	The line number of the source file in which the timer is defined. @return The identity of the CPU timer.
- L653 _public prototype_ `virtual IEditableTimeline<FTimingProfilerEvent>& GetCpuThreadEditableTimeline(uint32 ThreadId) = 0;` — Gets an object to receive ordered CPU timing events for a CPU thread. @param ThreadId	The thread for which the events are for. @return The object to receive the serial CPU timing events for the specified thread.
- L662 _public function_ `virtual void SetRatioOfThreadsToUse(double InRatioOfThreadsToUse)` — Sets the Ratio of Threads to be used. @param InRatioOfThreadsToUse The new ratio of threads to use.
- L668 _public function_ `virtual const ITimingProfilerProvider* GetReadProvider() const` — Gets the read provider. @returns The read only provider or nullptr if not available.

#### Free symbols / members of external scopes

- L20 _namespace_ `namespace TraceServices`
- L32 _typedef_ `typedef ITimeline<FTimingProfilerEvent> ITimingProfilerTimeline;` (scope `TraceServices`)
- L33 _typedef_ `typedef IEditableTimeline<FTimingProfilerEvent> ITimingProfilerEditableTimeline;` (scope `TraceServices`)
- L68 _member_ `uint32 Line : 24;` (scope `TraceServices::FTimingProfilerTimer::__anon4ee8fe1e010a::__anon4ee8fe1e0208`)
- L69 _member_ `ETimingProfilerTimerType Type : 8;` (scope `TraceServices::FTimingProfilerTimer::__anon4ee8fe1e010a::__anon4ee8fe1e0208`)
- L71 _member_ `uint32 LineAndType = 0;` (scope `TraceServices::FTimingProfilerTimer::__anon4ee8fe1e010a`) — used only to default initialize Line and Type with 0
- L304 _function_ `ReadTimers([&TimerReader](const TraceServices::ITimingProfilerTimerReader& Out) { TimerReader = &Out; });` (scope `TraceServices::ITimingProfilerProvider::GetTimerReader`)
- L389 _function_ `Params.CpuThreadFilter = [CpuThreadFilter](uint32 QueueId)` (scope `TraceServices::ITimingProfilerProvider::CreateButterfly`)
- L671 _prototype_ `FName GetTimingProfilerProviderName();` (scope `TraceServices`)
- L672 _prototype_ `const ITimingProfilerProvider* ReadTimingProfilerProvider(const IAnalysisSession& Session);` (scope `TraceServices`)
- L673 _prototype_ `IEditableTimingProfilerProvider* EditTimingProfilerProvider(IAnalysisSession& Session);` (scope `TraceServices`)

### `Source/Developer/TraceServices/Public/TraceServices/ModuleService.h` (Public)


#### struct `TraceServices::FModuleInfo`  
`struct FModuleInfo`  
_L18-22_
- L20 _public member_ `FName Name;`
- L21 _public member_ `const TCHAR* DisplayName = nullptr;`

#### struct `TraceServices::FModuleInfoEx`  
`struct FModuleInfoEx`  
_L24-28_
- L26 _public member_ `FModuleInfo Info;`
- L27 _public member_ `bool bIsEnabled = false;`

#### class `TraceServices::IModule`  
`class IModule : public IModularFeature`  
_L30-40_
- inherits: `IModularFeature`
- L34 _public prototype_ `virtual void GetModuleInfo(FModuleInfo& OutModuleInfo) = 0;`
- L35 _public function_ `virtual bool ShouldBeEnabledByDefault() const`
- L36 _public function_ `virtual void GetLoggers(TArray<const TCHAR*>& OutLoggers)`
- L37 _public function_ `virtual const TCHAR* GetCommandLineArgument()`
- L38 _public prototype_ `virtual void OnAnalysisBegin(IAnalysisSession& Session) = 0;`
- L39 _public function_ `virtual void GenerateReports(const IAnalysisSession& Session, const TCHAR* CmdLine, const TCHAR* OutputDirectory)`

#### class `TraceServices::IModuleService`  
`class IModuleService`  
_L42-51_
- L45 _public prototype_ `virtual ~IModuleService() = default;`
- L46 _public prototype_ `virtual void GetAvailableModules(TArray<FModuleInfo>& OutModules) = 0;`
- L47 _public prototype_ `virtual void GetAvailableModulesEx(TArray<FModuleInfoEx>& OutModules) = 0;`
- L48 _public prototype_ `virtual void GetEnabledModules(TArray<FModuleInfo>& OutModules) = 0;`
- L49 _public prototype_ `virtual void SetModuleEnabled(const FName& ModuleName, bool bEnabled) = 0;`
- L50 _public prototype_ `virtual void GenerateReports(const IAnalysisSession& Session, const TCHAR* CmdLine, const TCHAR* OutputDirectory) = 0;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace TraceServices`
- L16 _externvar_ `extern const FName ModuleFeatureName;` (scope `TraceServices`)

### `Source/Developer/TraceServices/Public/TraceServices/TraceTrimmer.h` (Public)


#### struct `TraceServices::FTrimParameters`  
`struct FTrimParameters`  
_L20-50_
- L26 _public member_ `double StartTime = -std::numeric_limits<double>::infinity();` — The start time filter. The analysis will ignore non-important events with timestamp < StartTime.
- L32 _public member_ `double EndTime = +std::numeric_limits<double>::infinity();` — The end time filter. The analysis will stop when a first non-important event with timestamp > EndTime is detected.
- L41 _public member_ `FAnsiString Include;` — Comma separated list of trace events to include. The events are specified as "logger.event" wildcard patterns. Example: "$trace.*,cpu.*". If specified, only the trace events with name that matches one of the patterns in the Include string will be included. Empty string (default) is equivalent with "*.*" (include all).
- L49 _public member_ `FAnsiString Exclude;` — Comma separated list of trace events to exclude. The events are specified as "logger.event" wildcard patterns. Example: "$trace.*,cpu.*". If specified, the trace events with name that matches one of the pattern in the Exclude string will be excluded.

#### class `TraceServices::ITrimAnalysisProcessor`  
`class ITrimAnalysisProcessor`  
_L52-70_
- L55 _public prototype_ `ITrimAnalysisProcessor() = default;`
- L56 _public prototype_ `virtual ~ITrimAnalysisProcessor() = default;`
- L59 _public prototype_ `virtual bool IsActive() const = 0;` — Checks if this object instance is valid and currently processing
- L62 _public prototype_ `virtual void Stop() = 0;` — End processing a trace stream.
- L65 _public prototype_ `virtual void Wait() = 0;` — Wait for the entire stream to have been processed and analyzed.
- L69 _public prototype_ `virtual void Pause(bool bState) = 0;` — Pause or resume the processing. @param bState Pause if true, resume if false.

#### Free symbols / members of external scopes

- L16 _macro_ `#define UE_API TRACESERVICES_API`
- L18 _namespace_ `namespace TraceServices`
- L83 _prototype_ `TUniquePtr<ITrimAnalysisProcessor> TrimAsync(FTrimParameters& Parameters, UE::Trace::IInDataStream& InputDataStream, UE::Trace::IOutDataStream& OutputDataStream);` (scope `TraceServices`) — Trims a trace stream using the provided parameters. The function starts the trimming process and returns immediately a unique pointer to the trim analysis processor object. The caller is responsible for waiting the processor to complete. @param Parameters The trim process parameters @param InputDataStream The input data stream @param OutputDataStream The output data stream @returns a unique pointer to the trim analysis processor object
- L94 _prototype_ `int32 Trim(FTrimParameters& Parameters, UE::Trace::IInDataStream& InputDataStream, UE::Trace::IOutDataStream& OutputDataStream);` (scope `TraceServices`) — Trims a trace stream using the provided parameters. The function waits for the trimming process to complete, before returning. @param Parameters The trim process parameters @param InputDataStream The input data stream @param OutputDataStream The output data stream @returns 0 if the trim process is completed successfully, non-zero otherwise

### `Source/Developer/TraceServices/Public/TraceServices/Utils.h` (Public)


#### Free symbols / members of external scopes

- L9 _namespace_ `namespace TraceServices`
- L10 _namespace_ `namespace FTraceAnalyzerUtils` (scope `TraceServices`)
- L13 _function_ `template <typename AttachedCharType> inline FString LegacyAttachmentString( const ANSICHAR* FieldName, const UE::Trace::IAnalyzer::FOnEventContext& Context)` (scope `TraceServices::FTraceAnalyzerUtils`)
- L27 _function_ `inline TArrayView<const uint8> LegacyAttachmentArray( const ANSICHAR* FieldName, const UE::Trace::IAnalyzer::FOnEventContext& Context)` (scope `TraceServices::FTraceAnalyzerUtils`)
- L43 _prototype_ `void StringFormat(TCHAR* Out, uint64 MaxOut, TCHAR* Temp, uint64 MaxTemp, const TCHAR* FormatString, const uint8* FormatArgs);` (scope `TraceServices`)
