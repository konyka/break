# Runtime / StorageServerClient

- module root: `Source/Runtime/StorageServerClient`
- headers: 21; symbols: 683
- symbol kinds: class=35, delegate=1, enum=3, enumerator=10, function=83, macro=6, member=235, namespace=10, prototype=275, struct=22, typedef=3
- PrivateDependencyModuleNames: CookOnTheFly, Core, CoreUObject, DeveloperSettings, Json, Sockets

### `Source/Runtime/StorageServerClient/Internal/IStorageServerPlatformFile.h` (Internal)


#### class `IStorageServerPlatformFile`  
`class IStorageServerPlatformFile : public IPlatformFile`  
_L8-24_
- inherits: `IPlatformFile`
- L20 _public prototype_ `virtual FStringView GetHostAddr() const = 0;`
- L22 _public prototype_ `virtual void GetAndResetConnectionStats(FConnectionStats& OutStats) = 0;`
- L23 _public prototype_ `virtual void UpdateFileList() = 0;`

#### struct `IStorageServerPlatformFile::FConnectionStats`  
`struct FConnectionStats`  
_L12-18_
- L14 _public member_ `uint64 AccumulatedBytes = 0;`
- L15 _public member_ `uint32 RequestCount = 0;`
- L16 _public member_ `double MinRequestThroughput = 0.0;`
- L17 _public member_ `double MaxRequestThroughput = 0.0;`

### `Source/Runtime/StorageServerClient/Internal/StorageServerClientModule.h` (Internal)


#### class `IStorageServerClientModule`  
`class IStorageServerClientModule : public IPlatformFileModule`  
_L16-39_
- inherits: `IPlatformFileModule`
- L19 _public function_ `static FORCEINLINE IStorageServerClientModule& Get()`
- L23 _public function_ `static FORCEINLINE IStorageServerPlatformFile* FindStorageServerPlatformFile()`
- L28 _public prototype_ `virtual IStorageServerPlatformFile* TryCreateCustomPlatformFile(FStringView StoreDirectory, IPlatformFile* Inner) = 0;`
- L38 _public prototype_ `virtual bool CreateDetachedPlatformFile(FString Host, uint16 Port, FString Project, FString Platform, FDetachedPlatformFileResult& OutResult) = 0;`

#### struct `IStorageServerClientModule::FDetachedPlatformFileResult`  
`struct FDetachedPlatformFileResult`  
_L32-37_
- desc: Creates a platform file, package store and io dispatcher backends, without mounting them in FPackageStore and FIoDispatcher.
- L34 _public member_ `TUniquePtr<IStorageServerPlatformFile> PlatformFile;`
- L35 _public member_ `TSharedPtr<IPackageStoreBackend> PackageStoreBackend;`
- L36 _public member_ `TSharedPtr<IIoDispatcherBackend> IoDispatcherBackend;`

### `Source/Runtime/StorageServerClient/Private/BuiltInHttpClient/BuiltInHttpClient.h` (Private)


#### class `IBuiltInHttpClientSocket`  
`class IBuiltInHttpClientSocket`  
_L10-24_
- L13 _public prototype_ `virtual ~IBuiltInHttpClientSocket() = default;`
- L15 _public prototype_ `virtual bool Send(const uint8* Data, const uint64 DataSize) = 0;`
- L16 _public prototype_ `virtual bool Recv(uint8* Data, const uint64 DataSize, uint64& BytesRead, ESocketReceiveFlags::Type ReceiveFlags) = 0;`
- L17 _public prototype_ `virtual bool HasPendingData(uint64& PendingDataSize) const = 0;`
- L18 _public prototype_ `virtual void Close() = 0;`
- L23 _public prototype_ `virtual bool IsAlive() const = 0;` — Probe whether a pooled socket is still usable. Returns true only when the connection is open and idle (no buffered data, no peer-closed state). A busy server can reap idle keep-alive connections, so pools must check before reusing.

#### class `IBuiltInHttpClientSocketPool`  
`class IBuiltInHttpClientSocketPool`  
_L26-33_
- L29 _public prototype_ `virtual ~IBuiltInHttpClientSocketPool() = default;`
- L31 _public prototype_ `virtual IBuiltInHttpClientSocket* AcquireSocket(float TimeoutSeconds = -1.f) = 0;`
- L32 _public prototype_ `virtual void ReleaseSocket(IBuiltInHttpClientSocket* Socket, bool bKeepAlive) = 0;`

#### class `FBuiltInHttpClient`  
`class FBuiltInHttpClient : public IStorageServerHttpClient`  
_L35-73_
- inherits: `IStorageServerHttpClient`
- L38 _public prototype_ `FBuiltInHttpClient(TUniquePtr<IBuiltInHttpClientSocketPool> InSocketPool, FString InHostname);`
- L39 _public prototype_ `virtual ~FBuiltInHttpClient() override = default;`
- L41 _public prototype_ `virtual void SetPersistentHeaders(TArrayView<const FAnsiString> InHeaders) override;`
- L43 _public prototype_ `virtual FResult RequestSync( FAnsiStringView Url, EStorageServerContentType Accept, FAnsiStringView Verb, TOptional<FIoBuffer> OptPayload, EStorageServerContentType PayloadContentType, TOptional<FIoBuffer> OptDestination, float TimeoutSeconds, const bool bReportErrors ) override;`
- L54 _public function_ `virtual void RequestAsync( FResultCallback&& Callback, FAnsiStringView Url, EStorageServerContentType Accept, FAnsiStringView Verb, TOptional<FIoBuffer> OptPayload, EStorageServerContentType PayloadContentType, TOptional<FIoBuffer> OptDestination, float TimeoutSeconds, const bool bReportErrors ) override`
- L70 _private member_ `TUniquePtr<IBuiltInHttpClientSocketPool> SocketPool;`
- L71 _private member_ `FString Hostname;`
- L72 _private member_ `TArray<FAnsiString> PersistentHeaders;`

### `Source/Runtime/StorageServerClient/Private/BuiltInHttpClient/BuiltInHttpClientFSocket.h` (Private)


#### class `FBuiltInHttpClientFSocket`  
`class FBuiltInHttpClientFSocket : public IBuiltInHttpClientSocket`  
_L12-26_
- inherits: `IBuiltInHttpClientSocket`
- L15 _public prototype_ `FBuiltInHttpClientFSocket(FSocket* InSocket);`
- L18 _public prototype_ `virtual bool Send(const uint8* Data, const uint64 DataSize) override;`
- L19 _public prototype_ `virtual bool Recv(uint8* Data, const uint64 DataSize, uint64& BytesRead, ESocketReceiveFlags::Type ReceiveFlags) override;`
- L20 _public prototype_ `virtual bool HasPendingData(uint64& PendingDataSize) const override;`
- L21 _public prototype_ `virtual void Close() override;`
- L22 _public prototype_ `virtual bool IsAlive() const override;`
- L25 _private member_ `FSocket* Socket;`

#### class `FBuiltInHttpClientFSocketPool`  
`class FBuiltInHttpClientFSocketPool : public IBuiltInHttpClientSocketPool`  
_L28-41_
- inherits: `IBuiltInHttpClientSocketPool`
- L31 _public prototype_ `FBuiltInHttpClientFSocketPool(TSharedPtr<FInternetAddr> InServerAddr, ISocketSubsystem& InSocketSubsystem);`
- L34 _public prototype_ `virtual IBuiltInHttpClientSocket* AcquireSocket(float TimeoutSeconds = -1.f) override;`
- L35 _public prototype_ `virtual void ReleaseSocket(IBuiltInHttpClientSocket* Socket, bool bKeepAlive) override;`
- L38 _private member_ `TSharedPtr<FInternetAddr> ServerAddr;`
- L39 _private member_ `ISocketSubsystem& SocketSubsystem;`
- L40 _private member_ `TLockFreePointerListUnordered<IBuiltInHttpClientSocket, PLATFORM_CACHE_LINE_SIZE> SocketPool;`

### `Source/Runtime/StorageServerClient/Private/BuiltInHttpClient/BuiltInHttpClientPlatformSocket.h` (Private)


#### class `FConnectionCircularBuffer`  
`class FConnectionCircularBuffer`  
_L13-129_
- L16 _public function_ `explicit FConnectionCircularBuffer(uint64 InCapacity) : CapacityMask(FMath::RoundUpToPowerOfTwo(InCapacity) - 1)`
- L22 _public function_ `~FConnectionCircularBuffer()`
- L27 _public function_ `uint8 operator[](uint64 Index) const`
- L32 _public function_ `uint8& operator[](uint64 Index)`
- L39 _public function_ `uint64 GetSize() const`
- L44 _public function_ `uint64 GetCapacity() const`
- L49 _public function_ `bool IsEmpty() const`
- L54 _public function_ `void Clear()`
- L61 _public function_ `uint64 SpaceLeft() const`
- L66 _public function_ `void Peek(uint8* Data, const uint64 DataSize, uint64& OutSize)`
- L83 _public function_ `void Consume(uint8* Data, const uint64 DataSize, uint64& OutSize)`
- L97 _public function_ `bool Put(uint8* Data, uint64 DataSize)`
- L124 _private member_ `uint8* Allocation{ nullptr };`
- L125 _private member_ `uint64 CapacityMask{ 0 };`
- L126 _private member_ `uint64 Size{ 0 };`
- L127 _private member_ `uint64 Head{ 0 };`
- L128 _private member_ `uint64 Tail{ 0 };`

#### class `FBuiltInHttpClientPlatformSocket`  
`class FBuiltInHttpClientPlatformSocket : public IBuiltInHttpClientSocket`  
_L131-150_
- inherits: `IBuiltInHttpClientSocket`
- L134 _public prototype_ `FBuiltInHttpClientPlatformSocket(IPlatformHostCommunication* InCommunication, IPlatformHostSocketPtr InSocket, int32 InProtocolNumber);`
- L137 _public prototype_ `virtual bool Send(const uint8* Data, const uint64 DataSize) override;`
- L138 _public prototype_ `virtual bool Recv(uint8* Data, const uint64 DataSize, uint64& BytesRead, ESocketReceiveFlags::Type ReceiveFlags) override;`
- L139 _public prototype_ `virtual bool HasPendingData(uint64& PendingDataSize) const override;`
- L140 _public prototype_ `virtual void Close() override;`
- L141 _public prototype_ `virtual bool IsAlive() const override;`
- L143 _public function_ `int32 GetProtocolNumber() const`
- L146 _private member_ `IPlatformHostCommunication* Communication;`
- L147 _private member_ `IPlatformHostSocketPtr Socket;`
- L148 _private member_ `FConnectionCircularBuffer ConnectionBuffer;`
- L149 _private member_ `const int32 ProtocolNumber;`

#### class `FBuiltInHttpClientPlatformSocketPool`  
`class FBuiltInHttpClientPlatformSocketPool : public IBuiltInHttpClientSocketPool`  
_L152-170_
- inherits: `IBuiltInHttpClientSocketPool`
- L155 _public prototype_ `FBuiltInHttpClientPlatformSocketPool(const FString InAddress);`
- L158 _public prototype_ `virtual IBuiltInHttpClientSocket* AcquireSocket(float TimeoutSeconds = -1.f) override;`
- L159 _public prototype_ `virtual void ReleaseSocket(IBuiltInHttpClientSocket* Socket, bool bKeepAlive) override;`
- L162 _private member_ `const FString Address;`
- L163 _private member_ `IPlatformHostCommunication* Communication = nullptr;`
- L165 _private member_ `TLockFreePointerListUnordered<IBuiltInHttpClientSocket, PLATFORM_CACHE_LINE_SIZE> SocketPool;`
- L167 _private member_ `FCriticalSection UsedSocketsCS;`
- L168 _private member_ `UE::FConditionVariable UsedSocketsCV;`
- L169 _private member_ `TBitArray<> UsedSockets;` — bitset to keep track of used sockets in the pool

### `Source/Runtime/StorageServerClient/Private/BuiltInHttpClient/BuiltInHttpClientUDSSocket.h` (Private)


#### class `FBuiltInHttpClientUDSSocket`  
`class FBuiltInHttpClientUDSSocket : public IBuiltInHttpClientSocket`  
_L10-35_
- inherits: `IBuiltInHttpClientSocket`
- L13 _public prototype_ `FBuiltInHttpClientUDSSocket(uint64 InSocket);`
- L16 _public prototype_ `virtual bool Send( const uint8* Data, const uint64 DataSize) override;`
- L20 _public prototype_ `virtual bool Recv( uint8* Data, const uint64 DataSize, uint64& BytesRead, ESocketReceiveFlags::Type ReceiveFlags) override;`
- L26 _public prototype_ `virtual bool HasPendingData( uint64& PendingDataSize) const override;`
- L29 _public prototype_ `virtual void Close() override;`
- L31 _public prototype_ `virtual bool IsAlive() const override;`
- L34 _private member_ `uint64 Socket;`

#### class `FBuiltInHttpClientUDSSocketPool`  
`class FBuiltInHttpClientUDSSocketPool : public IBuiltInHttpClientSocketPool`  
_L37-53_
- inherits: `IBuiltInHttpClientSocketPool`
- L40 _public prototype_ `FBuiltInHttpClientUDSSocketPool(FString InServerAddr);`
- L43 _public prototype_ `virtual IBuiltInHttpClientSocket* AcquireSocket( float TimeoutSeconds = -1.f) override;`
- L46 _public prototype_ `virtual void ReleaseSocket( IBuiltInHttpClientSocket* Socket, bool bKeepAlive) override;`
- L51 _private member_ `const FString Address;`
- L52 _private member_ `TLockFreePointerListUnordered<IBuiltInHttpClientSocket, PLATFORM_CACHE_LINE_SIZE> SocketPool;`

### `Source/Runtime/StorageServerClient/Private/Cache/CacheJournal.h` (Private)


#### struct `StorageServer::FCacheChunkInfo`  
`struct FCacheChunkInfo`  
_L16-60_
- L18 _public member_ `TOptional<uint64> ModTag;` — content modification tag
- L19 _public member_ `TOptional<int64> RawSize;` — size of complete chunk
- L20 _public member_ `TOptional<int32> RawBlockSize;` — size of block in a chunk if any, e.g. 256kb, can be 0
- L22 _public function_ `bool SetChunkInfo( const TOptional<uint64>& OptModTag, const TOptional<int64>& OptRawSize, const TOptional<int32>& OptRawBlockSize )`
- L45 _public function_ `FCacheChunkInfo& operator=(const FCacheChunkInfo& Other)`

#### struct `StorageServer::FCacheEntry`  
`struct FCacheEntry`  
_L62-86_
- L64 _public member_ `uint64 ChunkOffset;` — uncompressed offset in a chunk
- L65 _public member_ `uint64 ChunkSize;` — uncompressed size in a chunk
- L66 _public member_ `uint64 StorageOffset;` — offset in cache storage
- L67 _public member_ `uint64 StorageSize;` — size in cache storage
- L68 _public member_ `FIoHash StorageHash;` — hash of data in cache storage, needed to validate after reading from storage as we might lose data
- L69 _public member_ `EStorageServerContentType StorageContentType;` — content type in storage
- L71 _public function_ `TInterval<uint64> GetChunkInterval() const`

#### class `StorageServer::ICacheJournal`  
`class ICacheJournal`  
_L90-155_
- desc: Generic journal for storage server caching. Transactions are thread safe, atomic, saved at best effort. Cache journal focuses on avoiding data corruption when saving to disk, unlike cache storage which doesn't provide any guarantees for data consistency.
- L93 _public prototype_ `virtual ~ICacheJournal() = default;`
- L96 _public prototype_ `virtual void Flush(bool bImmediate) = 0;` — Flushes data to backing storage
- L99 _public prototype_ `virtual void InvalidateAll() = 0;` — Invalidates all data in journal
- L102 _public prototype_ `virtual void Invalidate(const FIoChunkId& ChunkId) = 0;` — Invalidates data for a specific chunk.
- L109 _public prototype_ `virtual bool SetChunkInfo( const FIoChunkId& ChunkId, const TOptional<uint64>& OptModTag, const TOptional<int64>& OptRawSize, const TOptional<int32>& OptRawBlockSize ) = 0;` — Updates chunk info. All fields are optional. If OptModTag is passed will compare it to existing ModTag and asks you to invalidate all data for this chunk id if they don't match. OptRawSize, OptRawBlockSize will simply be updated if passed. Returns true if either new ChunkId info is created or ModTag matches previous existing entry for this ChunkId. Returns false if ModHash doesn't match and cached data for this entry needs to be invalidated.
- L117 _public prototype_ `virtual bool TryGetChunkInfo( const FIoChunkId& ChunkId, FCacheChunkInfo& OutChunkInfo ) = 0;` — Return chunk info if present, returns true if chunk info is present.
- L124 _public prototype_ `virtual bool AddEntry( const FIoChunkId& ChunkId, const FCacheEntry& Entry ) = 0;` — Adds a new cache entry for chunk. Returns true if new entry was added, false if there is an entry for (ChunkId / ChunkOffset / ChunkSize).
- L130 _public prototype_ `virtual bool TryGetEntry( const FIoChunkId& ChunkId, const uint64 ChunkOffset, const uint64 ChunkSize, FCacheEntry& OutEntry ) = 0;` — Tries to find an entry for specified chunk offset and size, returns true if entry is present.
- L139 _public prototype_ `virtual void IterateChunkIds( TFunctionRef<void(const FIoChunkId& ChunkId, const FCacheChunkInfo& ChunkInfo)> Callback ) = 0;` — Iterate chunk id in journal that contain at least one entry. Not safe to invoke other journal methods from the callback.
- L145 _public prototype_ `virtual void IterateCacheEntriesForChunkId( const FIoChunkId& ChunkId, TFunctionRef<void(const FCacheEntry& Entry)> Callback ) = 0;` — Iterate entries for a chunk id in journal. Not safe to invoke other journal methods from the callback.
- L152 _public prototype_ `virtual void IterateCacheEntries( TFunctionRef<void(const FIoChunkId& ChunkId, const FCacheEntry& Entry)> Callback ) = 0;` — Iterate all entries in journal. Not safe to invoke other journal methods from the callback.

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace StorageServer`
- L53 _function_ `friend FArchive& operator << (FArchive& Ar, FCacheChunkInfo& Info)` (scope `StorageServer`)
- L76 _function_ `friend FArchive& operator << (FArchive& Ar, FCacheEntry& Entry)` (scope `StorageServer`)

### `Source/Runtime/StorageServerClient/Private/Cache/CacheJournalSectioned.h` (Private)


#### enum `StorageServer::EPageType`  
`enum class EPageType : uint8`  
_L15-19_
- L17 _public enumerator_ `Chunk = 1`
- L18 _public enumerator_ `ChunkInfo = 2`

#### struct `StorageServer::FJournalStoreEntry`  
`struct FJournalStoreEntry`  
_L21-39_
- L23 _public member_ `FIoChunkId ChunkId;`
- L24 _public member_ `FCacheEntry Entry;`
- L25 _public member_ `bool bValid;`
- L27 _public function_ `bool operator<(const FJournalStoreEntry& Other) const`

#### enum `StorageServer::EJournalPageResult`  
`enum class EJournalPageResult`  
_L41-47_
- L43 _public enumerator_ `Ok`
- L44 _public enumerator_ `EntryAlreadyExists`
- L45 _public enumerator_ `PageFull`
- L46 _public enumerator_ `EntryNotFound`

#### struct `StorageServer::FJournalHeader`  
`struct FJournalHeader`  
_L49-64_
- L51 _public member_ `uint32 Magic;`
- L52 _public member_ `uint32 Version;`
- L53 _public member_ `uint32 PageCount;`
- L55 _public member_ `static constexpr int32 SerializedSize = 32;` — actual size is 12 bytes, but we reserve some for future use

#### struct `StorageServer::FJournalPageHeader`  
`struct FJournalPageHeader`  
_L66-85_
- L68 _public member_ `uint32 Magic;`
- L69 _public member_ `uint32 PageSize;` — total size of page in bytes, should be used to calculate offset of next page
- L70 _public member_ `uint32 DataSize;` — size of data in current page minus header, can be less than page size if page is not full
- L71 _public member_ `FIoHash DataHash;` — hash of data in current page
- L72 _public member_ `EPageType Type;`
- L74 _public member_ `static constexpr int32 SerializedSize = 64;` — actual size is 33 bytes, but we reserve some for future use

#### class `StorageServer::FJournalPageBase`  
`class FJournalPageBase`  
_L87-132_
- L90 _public function_ `FJournalPageBase(EPageType InPageType, int64 InPageSize) : FilePos(-1) , PageSize(InPageSize) , PageType(InPageType)`
- L97 _public prototype_ `virtual ~FJournalPageBase() = default;`
- L99 _public prototype_ `[[nodiscard]] virtual bool Contains(const FIoChunkId&) const = 0;`
- L100 _public prototype_ `[[nodiscard]] virtual bool IsFull() const = 0;`
- L102 _public function_ `void SetFilePos(int64 FileCursor)`
- L107 _public function_ `int64 GetFilePos() const`
- L112 _public function_ `int64 GetPageSize() const`
- L117 _public prototype_ `bool Flush(IFileHandle* JournalFile, TArray<uint8>& SerializationBuffer);`
- L126 _protected member_ `int64 FilePos;`
- L127 _protected member_ `const int64 PageSize;`
- L128 _protected member_ `const EPageType PageType;`
- L129 _protected member_ `bool bDirty = false;`
- L131 _protected prototype_ `virtual void Serialize(FArchive& Ar) = 0;`

#### class `StorageServer::FJournalChunkInfoPage`  
`class FJournalChunkInfoPage : public FJournalPageBase`  
_L134-166_
- inherits: `FJournalPageBase`
- L137 _public prototype_ `FJournalChunkInfoPage(int64 InPageSize, int32 InMaxEntries);`
- L139 _public prototype_ `EJournalPageResult Add(const FIoChunkId& ChunkId, const FCacheChunkInfo& Entry);`
- L140 _public prototype_ `bool GetEntry(const FIoChunkId& ChunkId, FCacheChunkInfo& Info);`
- L141 _public prototype_ `virtual bool Contains(const FIoChunkId& ChunkId) const override;`
- L142 _public function_ `virtual bool IsFull() const override`
- L146 _public function_ `int32 GetEntryCount() const`
- L151 _public prototype_ `void Invalidate(const FIoChunkId& ChunkId);`
- L152 _public prototype_ `void InvalidateAll();`
- L154 _public prototype_ `void IterateChunkIds(TFunctionRef<void(const FIoChunkId& ChunkId, const FCacheChunkInfo& ChunkInfo)> Callback);`
- L159 _private member_ `int32 MaxEntryCount;`
- L160 _private member_ `TMap<FIoChunkId, FCacheChunkInfo> Entries;`
- L162 _private function_ `virtual void Serialize(FArchive& Ar) override`

#### class `StorageServer::FJournalChunkPage`  
`class FJournalChunkPage : public FJournalPageBase`  
_L168-207_
- inherits: `FJournalPageBase`
- L171 _public prototype_ `FJournalChunkPage(int64 InPageSize, int32 InMaxEntries);`
- L173 _public prototype_ `EJournalPageResult Add(const FIoChunkId& ChunkId, const FCacheEntry& Entry);`
- L174 _public prototype_ `bool GetEntry(const FIoChunkId& ChunkId, const uint64 ChunkOffset, const uint64 ChunkSize, FCacheEntry& OutEntry);`
- L175 _public function_ `virtual bool Contains(const FIoChunkId& ChunkId) const override`
- L180 _public prototype_ `void IterateCacheEntriesForChunkId(const FIoChunkId& ChunkId, TFunctionRef<void(const FCacheEntry& Entry)> Callback);`
- L181 _public prototype_ `void IterateCacheEntries(TFunctionRef<void(const FIoChunkId& ChunkId, const FCacheEntry& Entry)> Callback);`
- L182 _public function_ `virtual bool IsFull() const override`
- L186 _public function_ `int32 GetEntryCount() const`
- L191 _public prototype_ `void Invalidate(const FIoChunkId& ChunkId);`
- L192 _public prototype_ `void InvalidateAll();`
- L197 _private typedef_ `using FIntervalMap = TMap<TInterval<uint64>, int32>;`
- L198 _private member_ `TMap<FIoChunkId, FIntervalMap> ChunkMap;`
- L199 _private member_ `TArray<FJournalStoreEntry> Entries;`
- L200 _private member_ `int32 MaxEntryCount;`
- L201 _private member_ `bool bContainsInvalidEntries = false;`
- L203 _private function_ `virtual void Serialize(FArchive& Ar) override`

#### class `StorageServer::FCacheJournalSectioned`  
`class FCacheJournalSectioned : public ICacheJournal`  
_L209-267_
- inherits: `ICacheJournal`
- L213 _public prototype_ `FCacheJournalSectioned(FStringView JournalPath);`
- L214 _public prototype_ `virtual ~FCacheJournalSectioned() override = default;`
- L216 _public prototype_ `virtual void Flush(bool bImmediate) override;`
- L217 _public prototype_ `virtual void InvalidateAll() override;`
- L218 _public prototype_ `virtual void Invalidate(const FIoChunkId& ChunkId) override;`
- L220 _public prototype_ `virtual bool SetChunkInfo(const FIoChunkId& ChunkId, const TOptional<uint64>& OptModHash, const TOptional<int64>& OptRawSize, const TOptional<int32>& OptRawBlockSize) override;`
- L221 _public prototype_ `virtual bool TryGetChunkInfo(const FIoChunkId& ChunkId, FCacheChunkInfo& OutChunkInfo) override;`
- L223 _public prototype_ `virtual bool AddEntry(const FIoChunkId& ChunkId, const FCacheEntry& Entry) override;`
- L224 _public prototype_ `virtual bool TryGetEntry(const FIoChunkId& ChunkId, const uint64 ChunkOffset, const uint64 ChunkSize, FCacheEntry& OutEntry) override;`
- L226 _public prototype_ `virtual void IterateChunkIds(TFunctionRef<void(const FIoChunkId& ChunkId, const FCacheChunkInfo& ChunkInfo)> Callback) override;`
- L227 _public prototype_ `virtual void IterateCacheEntriesForChunkId(const FIoChunkId& ChunkId, TFunctionRef<void(const FCacheEntry& Entry)> Callback) override;`
- L228 _public prototype_ `virtual void IterateCacheEntries(TFunctionRef<void(const FIoChunkId& ChunkId, const FCacheEntry& Entry)> Callback) override;`
- L231 _private prototype_ `bool LoadCacheJournal();`
- L232 _private prototype_ `void ValidateJournal();`
- L234 _private prototype_ `FJournalChunkInfoPage* FindOrAddChunkInfoPage(const FIoChunkId& ChunkId);`
- L235 _private prototype_ `FJournalChunkPage* FindOrAddChunkPage(const FIoChunkId& ChunkId);`
- L237 _private prototype_ `FJournalChunkInfoPage* AddChunkInfoPage();`
- L238 _private prototype_ `FJournalChunkPage* AddChunkPage();`
- L240 _private function_ `int32 AllocateJournalFilePos(int32 PageSize)`
- L247 _private function_ `void ResetJournalFilePos()`
- L253 _private member_ `FString JournalFilePath;`
- L254 _private member_ `TUniquePtr<IFileHandle> JournalFileHandle;`
- L255 _private member_ `uint32 NextAvailableJournalPos = FJournalHeader::SerializedSize;`
- L256 _private member_ `UE::Tasks::TTask<void> FlushTask;`
- L258 _private member_ `bool bPagesModified = false;`
- L260 _private member_ `TArray<FJournalChunkPage> ChunkPages;`
- L261 _private member_ `TArray<FJournalChunkInfoPage> ChunkInfoPages;`
- L262 _private member_ `FJournalChunkPage* CurrentChunkPage = nullptr;`
- L264 _private member_ `FCriticalSection CriticalSection;`
- L266 _private prototype_ `void FlushImmediate();`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace StorageServer`
- L32 _function_ `friend FArchive& operator<<(FArchive& Ar, FJournalStoreEntry& StoreEntry)` (scope `StorageServer`)
- L57 _function_ `friend FArchive& operator << (FArchive& Ar, FJournalHeader& Header)` (scope `StorageServer`)
- L76 _function_ `friend FArchive& operator << (FArchive& Ar, FJournalPageHeader& Desc)` (scope `StorageServer`)
- L119 _function_ `friend FArchive& operator<<(FArchive& Ar, FJournalPageBase& Page)` (scope `StorageServer`)

### `Source/Runtime/StorageServerClient/Private/Cache/CacheJournalSimple.h` (Private)


#### class `StorageServer::FCacheJournalSimple`  
`class FCacheJournalSimple : public ICacheJournal`  
_L16-73_
- inherits: `ICacheJournal`
- desc: Cross-platform cache journal implementation, baseline for platforms where platform specific implementation is not available.
- L19 _public prototype_ `FCacheJournalSimple(const TCHAR* FileName, const uint64 FlushAtWriteCount);`
- L22 _public prototype_ `virtual void Flush(bool bImmediate) override;`
- L24 _public prototype_ `virtual void InvalidateAll() override;`
- L25 _public prototype_ `virtual void Invalidate(const FIoChunkId& ChunkId) override;`
- L27 _public prototype_ `virtual bool SetChunkInfo( const FIoChunkId& ChunkId, const TOptional<uint64>& OptModTag, const TOptional<int64>& OptRawSize, const TOptional<int32>& OptRawBlockSize ) override;`
- L33 _public prototype_ `virtual bool TryGetChunkInfo( const FIoChunkId& ChunkId, FCacheChunkInfo& OutChunkInfo ) override;`
- L38 _public prototype_ `virtual bool AddEntry( const FIoChunkId& ChunkId, const FCacheEntry& Entry ) override;`
- L42 _public prototype_ `virtual bool TryGetEntry( const FIoChunkId& ChunkId, const uint64 ChunkOffset, const uint64 ChunkSize, FCacheEntry& OutEntry ) override;`
- L49 _public prototype_ `virtual void IterateChunkIds( TFunctionRef<void(const FIoChunkId& ChunkId, const FCacheChunkInfo& ChunkInfo)> Callback ) override;`
- L52 _public prototype_ `virtual void IterateCacheEntriesForChunkId( const FIoChunkId& ChunkId, TFunctionRef<void(const FCacheEntry& Entry)> Callback ) override;`
- L56 _public prototype_ `virtual void IterateCacheEntries( TFunctionRef<void(const FIoChunkId& ChunkId, const FCacheEntry& Entry)> Callback ) override;`
- L61 _private member_ `FCriticalSection DataLock, FlushTaskLock;`
- L61 _private member_ `FCriticalSection DataLock, FlushTaskLock;`
- L62 _private member_ `FString FileName;`
- L63 _private member_ `UE::Tasks::TTask<void> FlushTask;`
- L64 _private member_ `uint64 FlushAtWriteCount;`
- L65 _private member_ `uint64 CurrentWriteCount;`
- L66 _private member_ `std::atomic<bool> bDirty;`
- L68 _private typedef_ `typedef TMap<TInterval<uint64>, FCacheEntry> FPerChunkCacheEntries;`
- L69 _private member_ `TMap<FIoChunkId, FCacheChunkInfo> ChunkInfos;`
- L70 _private member_ `TMap<FIoChunkId, FPerChunkCacheEntries> ChunkCacheEntries;`
- L72 _private prototype_ `void FlushImmediate();`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace StorageServer`

### `Source/Runtime/StorageServerClient/Private/Cache/CacheStorage.h` (Private)


#### class `StorageServer::ICacheStorage`  
`class ICacheStorage`  
_L17-102_
- desc: Bulk storage for caching, transactions are async, non-atomic, best effort, data might be corrupted.
- L20 _public prototype_ `virtual ~ICacheStorage() = default;`
- L23 _public function_ `virtual bool IsNewlyCreatedStorage()` — returns true if cache was created/truncated this session and all data should be assumed lost
- L28 _public prototype_ `virtual void Flush() = 0;`
- L30 _public prototype_ `virtual uint64 GetSize() const = 0;`
- L32 _public prototype_ `virtual void Invalidate(const uint64 Offset, const uint64 Size) = 0;`
- L34 _public prototype_ `virtual FIoBuffer Read( const uint64 Offset, const uint64 ReadSize, TOptional<FIoBuffer> OptDestination ) = 0;`
- L40 _public prototype_ `virtual void WriteAsync( const uint64 Offset, const void* Buffer, const uint64 WriteSize ) = 0;`
- L47 _protected member_ `bool bNewlyCreatedStorage = false;`
- L50 _protected member_ `static constexpr uint64 MaxCacheFileSize = 2ull * 1024 * 1024 * 1024;` — Limit cache file size to 2GB to stay below file system limitations
- L53 _protected function_ `static TArray<TTuple<FString, uint64>> GetBackingFileNames(const TCHAR* FileNamePrefix, const uint64 FileSizeTmp)` — Generate a list of filenames and sizes to be used for backing storage
- L72 _protected function_ `static bool GetBackingIntervals(const uint64 Offset, const uint64 Size, uint32& IndexA, uint64& OffsetA, uint64& SizeA, uint32& IndexB, uint64& OffsetB, uint64& SizeB)`

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace StorageServer`

### `Source/Runtime/StorageServerClient/Private/Cache/CacheStorageBlocking.h` (Private)


#### class `StorageServer::FCacheStorageBlocking`  
`class FCacheStorageBlocking : public ICacheStorage`  
_L13-106_
- inherits: `ICacheStorage`
- desc: Cache storage implemented via blocking file operations
- L16 _public prototype_ `FCacheStorageBlocking(const TCHAR* FileName, const uint64 FileSize);`
- L19 _public prototype_ `virtual void Flush() override;`
- L21 _public prototype_ `virtual uint64 GetSize() const override;`
- L23 _public function_ `virtual void Invalidate(const uint64 Offset, const uint64 Size) override` — no-op
- L25 _public prototype_ `virtual FIoBuffer Read( const uint64 Offset, const uint64 ReadSize, TOptional<FIoBuffer> OptDestination ) override;`
- L31 _public prototype_ `virtual void WriteAsync( const uint64 Offset, const void* Buffer, const uint64 WriteSize ) override;`
- L97 _private member_ `UE::Tasks::TTask<void> FlushTask;`
- L98 _private member_ `TArray<TUniquePtr<IFileHandle>> BackingFiles;`
- L99 _private member_ `FDoubleBuffer Buffers;`
- L100 _private member_ `FCriticalSection FrontLock, BackLock, FileWriteLock;`
- L100 _private member_ `FCriticalSection FrontLock, BackLock, FileWriteLock;`
- L100 _private member_ `FCriticalSection FrontLock, BackLock, FileWriteLock;`
- L101 _private member_ `uint64 FileSize;`
- L103 _private prototype_ `void Flush(bool bLazy);`
- L104 _private prototype_ `void BackingReadAt(const uint64 Offset, void* Buffer, const uint64 Size);`
- L105 _private prototype_ `void BackingWriteAt(const uint64 Offset, const void* Buffer, const uint64 Size);`

#### struct `StorageServer::FCacheStorageBlocking::FWriteOp`  
`struct FWriteOp`  
_L38-43_
- L40 _public member_ `uint64 OffsetInFile;`
- L41 _public member_ `uint64 Size;`
- L42 _public member_ `uint8* Data;`

#### struct `StorageServer::FCacheStorageBlocking::FWriteQueue`  
`struct FWriteQueue`  
_L45-63_
- L47 _public member_ `static constexpr uint32 MaxOpCount = 1 * 1024;`
- L48 _public member_ `static constexpr uint32 MaxDataSize = 16 * 1024 * 1024;`
- L50 _public member_ `TArray<FWriteOp, TInlineAllocator<MaxOpCount * sizeof(FWriteOp)>> Operations;`
- L51 _public member_ `TArray<uint8, TInlineAllocator<MaxDataSize>> Data;`
- L53 _public function_ `bool CanStore(const uint64 Size) const`
- L57 _public prototype_ `bool Write(const uint64 OffsetInFile, const void* Buffer, const uint64 Size);`
- L58 _public function_ `void Empty()`

#### class `StorageServer::FCacheStorageBlocking::FDoubleBuffer`  
`class FDoubleBuffer`  
_L65-95_
- L68 _public function_ `FDoubleBuffer() : Front(&Queue1) , Back(&Queue2)`
- L73 _public function_ `FWriteQueue* GetFront() const`
- L74 _public function_ `FWriteQueue* GetBack() const`
- L76 _public function_ `void Flip()`
- L91 _private member_ `FWriteQueue Queue1;`
- L92 _private member_ `FWriteQueue Queue2;`
- L93 _private member_ `FWriteQueue* Front;`
- L94 _private member_ `FWriteQueue* Back;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace StorageServer`

### `Source/Runtime/StorageServerClient/Private/Cache/CacheStorageMmap.h` (Private)


#### class `StorageServer::FCacheStorageMmap`  
`class FCacheStorageMmap : public ICacheStorage`  
_L14-67_
- inherits: `ICacheStorage`
- desc: Cache storage implemented via mmap-ing a file on platforms that support mmap
- L17 _public prototype_ `FCacheStorageMmap(const TCHAR* FileNamePrefix, const uint64 FileSize);`
- L20 _public prototype_ `virtual void Flush() override;`
- L22 _public function_ `virtual uint64 GetSize() const override`
- L24 _public prototype_ `virtual void Invalidate(const uint64 Offset, const uint64 Size) override;`
- L26 _public prototype_ `virtual FIoBuffer Read( const uint64 Offset, const uint64 ReadSize, TOptional<FIoBuffer> OptDestination ) override;`
- L32 _public prototype_ `virtual void WriteAsync( const uint64 Offset, const void* Buffer, const uint64 WriteSize ) override;`
- L60 _private member_ `TArray<FBackingFile> BackingFiles;`
- L61 _private member_ `uint64 TotalSize;`
- L63 _private function_ `bool IsValidRange(const uint64 Offset, const uint64 Size) const`

#### struct `StorageServer::FCacheStorageMmap::FBackingFile`  
`struct FBackingFile`  
_L39-58_
- L41 _public member_ `TUniquePtr<IMappedFileHandle> FileHandle;`
- L42 _public member_ `TUniquePtr<IMappedFileRegion> FileRegion;`
- L43 _public member_ `uint8* MapPtr;`
- L44 _public member_ `uint64 MapSize;`
- L46 _public prototype_ `FBackingFile() = default;`
- L47 _public prototype_ `FBackingFile(FBackingFile&&) = default;`
- L48 _public prototype_ `FBackingFile(const FBackingFile&) = delete;`
- L49 _public prototype_ `FBackingFile& operator=(const FBackingFile&) = delete;`
- L50 _public function_ `~FBackingFile()`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace StorageServer`

### `Source/Runtime/StorageServerClient/Private/Cache/CacheStrategy.h` (Private)


#### class `StorageServer::ICacheStrategy`  
`class ICacheStrategy`  
_L14-116_
- L17 _public function_ `ICacheStrategy(TUniquePtr<ICacheJournal>&& InJournal, TUniquePtr<ICacheStorage>&& InStorage, const float FlushInterval) : Journal(MoveTemp(InJournal)) , Storage(MoveTemp(InStorage))`
- L34 _public function_ `virtual ~ICacheStrategy()`
- L43 _public prototype_ `virtual void Invalidate(const FIoChunkId& ChunkId) = 0;`
- L45 _public function_ `virtual void CacheChunkSize(const FIoChunkId& ChunkId, const int64 RawSize)`
- L50 _public function_ `virtual bool TryGetChunkSize(const FIoChunkId& ChunkId, int64& OutRawSize)`
- L71 _public prototype_ `virtual bool ReadChunk( const FIoChunkId& RequestChunkId, const uint64 RequestOffset, const uint64 RequestSize, TOptional<FIoBuffer> OptDestination, FIoBuffer& OutBuffer, EStorageServerContentType& OutContentType ) = 0;`
- L86 _public prototype_ `virtual void CacheChunk( const FIoChunkId& RequestChunkId, const uint64 RequestRawOffset, const uint64 RequestRawSize, const FIoBuffer& ResultBuffer, const EStorageServerContentType ResultContentType, const uint64 ResultModTag ) = 0;` — TODO cache individual chunk blocks. In case if ResultContentType is CompressedBinary the ResultBuffer will contain 1 or more chunk blocks, we can cache them individually with corresponding block offset and block size, such as if a follow-up ReadChunk request comes in that maps to the same block (but not same offset/size that was used in first request), it would still be fulfilled from cache. This requires unpacking of CompressedBinary and reconstructing its header for each individual chunk block.
- L95 _public function_ `virtual void Flush()`
- L101 _public function_ `virtual void IterateChunkIds(TFunctionRef<void(const FIoChunkId& ChunkId, const FCacheChunkInfo& ChunkInfo)> Callback)`
- L107 _protected member_ `TUniquePtr<ICacheJournal> Journal;`
- L108 _protected member_ `TUniquePtr<ICacheStorage> Storage;`
- L109 _protected member_ `FTSTicker::FDelegateHandle FlushTicker;`
- L111 _protected function_ `bool FlushTick(float DeltaTime)`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace StorageServer`

### `Source/Runtime/StorageServerClient/Private/Cache/CacheStrategyLinear.h` (Private)


#### class `StorageServer::FCacheStrategyLinear`  
`class FCacheStrategyLinear : public ICacheStrategy`  
_L13-38_
- inherits: `ICacheStrategy`
- desc: Use cache storage as arena allocator and store all chunks as they come in. No eviction.
- L16 _public prototype_ `FCacheStrategyLinear(TUniquePtr<ICacheJournal>&& InJournal, TUniquePtr<ICacheStorage>&& InStorage, const uint64 AbandonAtInvalidSize, const float FlushInterval, const bool bInvalidate);`
- L19 _public prototype_ `void InvalidateAll();`
- L20 _public function_ `virtual void Invalidate(const FIoChunkId& ChunkId) override`
- L25 _public prototype_ `virtual bool ReadChunk(const FIoChunkId& RequestChunkId, const uint64 RequestOffset, const uint64 RequestSize, TOptional<FIoBuffer> OptDestination, FIoBuffer& OutBuffer, EStorageServerContentType& ContentType) override;`
- L27 _public prototype_ `virtual void CacheChunk(const FIoChunkId& RequestChunkId, const uint64 RequestOffset, const uint64 RequestSize, const FIoBuffer& Buffer, const EStorageServerContentType ContentType, const uint64 ResultModTag) override;`
- L31 _private member_ `std::atomic<uint64> CurrentSize;` — Linear cache is implemented as arena allocator
- L32 _private member_ `uint64 CurrentInvalidSize;` — Amount of bytes with-in arena allocator that are stale
- L33 _private member_ `uint64 AbandonAtInvalidSize;` — Consider cache to be a lost cause at this amount of stale data
- L34 _private member_ `FCriticalSection JournalLock;`
- L36 _private prototype_ `void Invalidate(const FIoChunkId& ChunkId, bool bShouldLockJournal);`
- L37 _private prototype_ `void SetCounters();`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace StorageServer`

### `Source/Runtime/StorageServerClient/Private/CookOnTheFlyPackageStore.h` (Private)


#### class `FCookOnTheFlyPackageStoreBackend`  
`class FCookOnTheFlyPackageStoreBackend final : public IPackageStoreBackend`  
_L14-83_
- inherits: `IPackageStoreBackend`
- L30 _public prototype_ `FCookOnTheFlyPackageStoreBackend(UE::Cook::ICookOnTheFlyServerConnection& InCookOnTheFlyServerConnection);`
- L32 _public function_ `virtual void OnMounted(TSharedRef<const FPackageStoreBackendContext> InContext) override`
- L37 _public prototype_ `virtual void BeginRead() override;`
- L39 _public prototype_ `virtual void EndRead() override;`
- L45 _public prototype_ `bool DoesPackageExist(FPackageId PackageId);` — Returns true if a cooked or uncooked package exists on-disk on the COTF server Note this may not be accurate for generated packages
- L46 _public prototype_ `virtual EPackageStoreEntryStatus GetPackageStoreEntry(FPackageId PackageId, FName PackageName, FPackageStoreEntry& OutPackageStoreEntry) override;`
- L49 _public function_ `virtual bool GetPackageRedirectInfo(FPackageId PackageId, FName& OutSourcePackageName, FPackageId& OutRedirectedToPackageId) override`
- L55 _private prototype_ `void GetCookedPackagesFromServer();`
- L56 _private prototype_ `void GetAllAvailablePackagesFromServer();`
- L57 _private prototype_ `void SendCookRequest(TArray<TPair<FPackageId, FName>> PackageIds);`
- L58 _private prototype_ `EPackageStoreEntryStatus CreatePackageStoreEntry(const FEntryInfo& EntryInfo, FPackageStoreEntry& OutPackageStoreEntry);`
- L59 _private prototype_ `void AddPackages(TArray<FPackageStoreEntryResource> Entries, TArray<FPackageId> FailedPackageIds, TArray<TPair<FPackageId, FName>> PackageIdsAndNames);`
- L61 _private prototype_ `void AddOnDiskPackages(const TArray<FPackageId>& Packages);`
- L62 _private prototype_ `void OnCookOnTheFlyMessage(const UE::Cook::FCookOnTheFlyMessage& Message);`
- L63 _private prototype_ `void CheckActivity();`
- L65 _private member_ `UE::Cook::ICookOnTheFlyServerConnection& CookOnTheFlyServerConnection;`
- L66 _private member_ `TSharedPtr<const FPackageStoreBackendContext> Context;`
- L67 _private member_ `FRWLock EntriesLock;`
- L68 _private member_ `TMap<FPackageId, FEntryInfo> PackageIdToEntryInfo;`
- L69 _private member_ `TChunkedArray<FPackageStoreEntryResource> PackageEntries;`
- L70 _private member_ `TArray<TPair<FPackageId, FName>> RequestedPackageIds;`
- L75 _private member_ `TSet<FPackageId> AllServerOnDiskPackages;` — All packages available on-disk on the COTF server. Populated from server asset registry when connection is established. These may be cooked or uncooked
- L76 _private member_ `FPackageStats PackageStats;`
- L78 _private member_ `const double MaxInactivityTime = 20;`
- L79 _private member_ `const double TimeBetweenWarning = 10;`
- L80 _private member_ `double LastClientActivtyTime = 0;`
- L81 _private member_ `double LastServerActivtyTime = 0;`
- L82 _private member_ `double LastWarningTime = 0;`

#### struct `FCookOnTheFlyPackageStoreBackend::FEntryInfo`  
`struct FEntryInfo`  
_L18-22_
- L20 _public member_ `EPackageStoreEntryStatus Status = EPackageStoreEntryStatus::None;`
- L21 _public member_ `int32 EntryIndex = INDEX_NONE;`

#### struct `FCookOnTheFlyPackageStoreBackend::FPackageStats`  
`struct FPackageStats`  
_L24-28_
- L26 _public member_ `TAtomic<uint32> Cooked{ 0 };`
- L27 _public member_ `TAtomic<uint32> Failed{ 0 };`

### `Source/Runtime/StorageServerClient/Private/StorageServerConnection.h` (Private)


#### class `FStorageServerConnection`  
`class FStorageServerConnection`  
_L46-205_
- L49 _public prototype_ `FStorageServerConnection() = default;`
- L50 _public prototype_ `~FStorageServerConnection() = default;`
- L52 _public prototype_ `bool Initialize(TArrayView<const FString> HostAddresses, const int32 Port, const FAnsiStringView& InBaseURI, TArrayView<const FAnsiString> InPersistentHeaders = {});`
- L74 _public prototype_ `TIoStatusOr<Workspaces> GetWorkspaces();`
- L75 _public prototype_ `TIoStatusOr<FString> CreateShare(const FString& WorkspaceId, const FString& SharePath, const FString& Alias);`
- L76 _public function_ `bool IsConnectedToWorkspace() const`
- L81 _public prototype_ `void PackageStoreRequest(TFunctionRef<void(FPackageStoreEntryResource&&)> Callback);`
- L82 _public prototype_ `void FileManifestRequest(TFunctionRef<void(FIoChunkId Id, FStringView Path, int64 RawSize)> Callback);`
- L83 _public prototype_ `void ChunkInfosRequest(TFunctionRef<void(FIoChunkId Id, FIoHash RawHash, int64 RawSize)> Callback);`
- L84 _public prototype_ `int64 ChunkSizeRequest(const FIoChunkId& ChunkId);`
- L85 _public prototype_ `TIoStatusOr<FIoBuffer> ReadChunkRequest( const FIoChunkId& ChunkId, const uint64 Offset, const uint64 Size, const TOptional<FIoBuffer> OptDestination, const bool bHardwareTargetBuffer );`
- L93 _public prototype_ `void ReadChunkRequestAsync( const FIoChunkId& ChunkId, const uint64 Offset, const uint64 Size, const TOptional<FIoBuffer> OptDestination, const bool bHardwareTargetBuffer, TFunctionRef<void(TIoStatusOr<FIoBuffer> Data)> OnResponse );`
- L122 _public prototype_ `FIoStatus ReadChunkBatchRequest( const TArray<FChunkBatchRequestEntry>& Chunks, TFunctionRef<void(FIoChunkId Id, EStorageServerContentType MimeType, FIoBuffer Data, const TOptional<uint64>& ModTag)> OnResponse, bool bSkipData = false`
- L129 _public function_ `FStringView GetHostAddr() const`
- L134 _public prototype_ `void GetAndResetStats(IStorageServerPlatformFile::FConnectionStats& OutStats);`
- L137 _private member_ `TUniquePtr<IStorageServerHttpClient> HttpClient;`
- L138 _private member_ `TUniquePtr<StorageServer::ICacheStrategy> CacheStrategy;`
- L139 _private member_ `FAnsiString BaseURI;`
- L140 _private member_ `FString CurrentHostAddr;`
- L141 _private member_ `TArray<FAnsiString> PersistentHeaders;`
- L142 _private member_ `bool bIsUsingZenWorkspace = false;` — is the connection to the /ws/ endpoint
- L145 _private member_ `std::atomic<uint64> AccumulatedBytes = 0;` — Stats
- L146 _private member_ `std::atomic<uint32> RequestCount = 0;`
- L147 _private member_ `std::atomic<double> MinRequestThroughput = DBL_MAX;`
- L148 _private member_ `std::atomic<double> MaxRequestThroughput = -DBL_MAX;`
- L150 _private prototype_ `TArray<FString> SortHostAddressesByLocalSubnet(TArrayView<const FString> HostAddresses, const int32 Port);`
- L151 _private prototype_ `static bool IsPlatformSocketAddress(const FString Address);`
- L152 _private prototype_ `static bool IsUDSSocketAddress(const FString Address);`
- L153 _private prototype_ `static bool IsHostnameAddress(const FString Address);`
- L154 _private prototype_ `TUniquePtr<IStorageServerHttpClient> CreateHttpClient(const FString Address, const int32 Port);`
- L155 _private prototype_ `TSharedPtr<FInternetAddr> StringToInternetAddr(const FString Address, const int32 Port);`
- L156 _private prototype_ `bool HandshakeRequest();`
- L173 _private prototype_ `static bool ShouldRetryRequest(const IStorageServerHttpClient::FResult& Result);` — Returns true if the given request result represents a transient failure that is worth retrying. The intent is to retry transport-level failures and 5xx server responses while leaving 4xx alone (they encode deterministic client-side errors like "Not Found" or "Bad Request" that an identical retry would only repeat).
- L175 _private prototype_ `void GetDefaultCacheConfiguration(FCacheConfiguration& OutConfiguration);`
- L176 _private prototype_ `void SetupCacheStrategy();`
- L177 _private prototype_ `bool FinalizeSetupCacheStrategy();`
- L178 _private prototype_ `void BuildReadChunkRequestUrl(FAnsiStringBuilderBase& Builder, const FIoChunkId& ChunkId, const uint64 Offset, const uint64 Size);`
- L179 _private prototype_ `static TIoStatusOr<FIoBuffer> ReadChunkRequestProcessHttpResult( IStorageServerHttpClient::FResult ResultTuple, const uint64 Offset, const uint64 Size, const TOptional<FIoBuffer> OptDestination, const bool bHardwareTargetBuffer );`
- L186 _private prototype_ `static uint64 GetCompressedOffset(const FCompressedBuffer& Buffer, uint64 RawOffset);`
- L187 _private prototype_ `void AddTimingInstance(const double Duration, const uint64 Bytes);`
- L204 _private member_ `TSharedPtr<FAsyncQueryLatestServerChunkInfo, ESPMode::ThreadSafe> AsyncQueryLatestServerChunkInfo;`

#### struct `FStorageServerConnection::Workspaces`  
`struct Workspaces`  
_L54-72_
- L71 _public member_ `TArray<Workspace> Workspaces;`

#### struct `FStorageServerConnection::Workspaces::Share`  
`struct Share`  
_L56-61_
- L58 _public member_ `FString Id;`
- L59 _public member_ `FString Path;`
- L60 _public member_ `FString Alias;`

#### struct `FStorageServerConnection::Workspaces::Workspace`  
`struct Workspace`  
_L63-70_
- L65 _public member_ `FString Id;`
- L66 _public member_ `FString Root;`
- L67 _public member_ `bool AllowShareCreationFromHttp = false;`
- L69 _public member_ `TArray<Share> Shares;`

#### struct `FStorageServerConnection::FChunkBatchRequestEntry`  
`struct FChunkBatchRequestEntry`  
_L104-120_
- desc: Matches input parameters for ProjectStore::GetChunks in zen server
- L105 _public member_ `FIoChunkId ChunkId;`
- L106 _public member_ `uint64 Offset;`
- L107 _public member_ `uint64 Size;`
- L108 _public member_ `TOptional<uint64> ModTag;`
- L110 _public function_ `static FChunkBatchRequestEntry DataRequest(const FIoChunkId& ChunkId, const uint64 Offset, const uint64 Size)`
- L116 _public function_ `static FChunkBatchRequestEntry VerifyModTagRequest(const FIoChunkId& ChunkId, const uint64 ModTag)`

#### struct `FStorageServerConnection::FCacheConfiguration`  
`struct FCacheConfiguration`  
_L158-168_
- L160 _public member_ `bool bEnable = false;` — set to true to enable cache
- L161 _public member_ `bool bForceInvalidate = false;` — invalidate cache if set to true
- L162 _public member_ `int32 CacheSizeKB = 0;` — total size of cache in kb
- L163 _public member_ `float FlushInterval = 0.f;` — interval at which to flush cache in seconds
- L164 _public member_ `int32 FlushEveryNEntries = 0;` — set to >0 to flush journal every N new entries
- L165 _public member_ `int32 AbandonSizeKB = 0;` — set to >0 to abandon cache if amount of invalid data goes over threshold
- L166 _public member_ `bool bUseSectionedJournal = false;` — use the sectioned journal instead of the simple TMap variant
- L167 _public member_ `bool bUseMemoryMappedStorage = false;` — use mmapped cache storage backend

#### class `FStorageServerConnection::FAsyncQueryLatestServerChunkInfo`  
`class FAsyncQueryLatestServerChunkInfo : public FRunnable`  
_L189-202_
- inherits: `FRunnable`
- L192 _public prototype_ `FAsyncQueryLatestServerChunkInfo(FStorageServerConnection& InOwner);`
- L193 _public prototype_ `virtual ~FAsyncQueryLatestServerChunkInfo();`
- L195 _public prototype_ `bool IsFinished() const;`
- L196 _public prototype_ `void Wait();`
- L198 _private prototype_ `virtual uint32 Run() override;`
- L200 _private member_ `FStorageServerConnection& Owner;`
- L201 _private member_ `class FEvent* IsCompleted;`

#### Free symbols / members of external scopes

- L21 _macro_ `#define PLATFORM_SUPPORTS_STORAGE_SERVER_CACHE (PLATFORM_WINDOWS || PLATFORM_ANDROID || PLATFORM_IOS)`
- L25 _macro_ `#define PLATFORM_ENABLES_STORAGE_SERVER_CACHE_BY_DEFAULT 1`
- L29 _macro_ `#define PLATFORM_ENABLES_STORAGE_SERVER_CACHE_BY_DEFAULT 0`
- L33 _macro_ `#define PLATFORM_HAS_CUSTOM_STORAGE_SERVER_CACHE_STRATEGY 0`
- L37 _macro_ `#define HAS_STORAGE_SERVER_RPC_GETCHUNKS_API 1`
- L42 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogStorageServerConnection, Log, All);`
- L42 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogStorageServerConnection, Log, All);`

### `Source/Runtime/StorageServerClient/Private/StorageServerHttpClient.h` (Private)


#### enum `EStorageServerContentType`  
`enum class EStorageServerContentType : uint8`  
_L12-18_
- L14 _public enumerator_ `Unknown = 0`
- L15 _public enumerator_ `CbObject`
- L16 _public enumerator_ `Binary`
- L17 _public enumerator_ `CompressedBinary`

#### class `IStorageServerHttpClient`  
`class IStorageServerHttpClient`  
_L20-70_
- L41 _public typedef_ `using FResultCallback = TFunction<void(FResult)>;`
- L43 _public prototype_ `virtual ~IStorageServerHttpClient() = default;`
- L46 _public prototype_ `virtual void SetPersistentHeaders(TArrayView<const FAnsiString> InHeaders) = 0;` — Set headers that will be included with every request. Each entry should be a complete header line (e.g. "Authorization: Basic dWU6cGFzcw==").
- L48 _public prototype_ `virtual FResult RequestSync( FAnsiStringView Url, EStorageServerContentType Accept = EStorageServerContentType::Unknown, FAnsiStringView Verb = "GET", TOptional<FIoBuffer> OptPayload = TOptional<FIoBuffer>(), EStorageServerContentType PayloadContentType = EStorageServerContentType::Unknown, TOptional<FIoBuffer> OptDestination = TOptional<FIoBuffer>(), float TimeoutSeconds = -1.f, const bool bReportErrors = true ) = 0;`
- L59 _public prototype_ `virtual void RequestAsync( FResultCallback&& Callback, FAnsiStringView Url, EStorageServerContentType Accept = EStorageServerContentType::Unknown, FAnsiStringView Verb = "GET", TOptional<FIoBuffer> OptPayload = TOptional<FIoBuffer>(), EStorageServerContentType PayloadContentType = EStorageServerContentType::Unknown, TOptional<FIoBuffer> OptDestination = TOptional<FIoBuffer>(), float TimeoutSeconds = -1.f, const bool bReportErrors = true ) = 0;`

#### struct `IStorageServerHttpClient::FResult`  
`struct FResult`  
_L24-39_
- desc: Result of an HTTP request.
- L29 _public member_ `TIoStatusOr<FIoBuffer> IoStatus;` — IO status (and on success the response body) for the request. Callers should inspect .IsOk() before dereferencing. Named IoStatus rather than Status to avoid confusion with the HTTP-level HttpStatusCode field below.
- L33 _public member_ `EStorageServerContentType ContentType = EStorageServerContentType::Unknown;` — Content-Type reported by the server (Unknown when no response was received or the server omitted the header).
- L38 _public member_ `int32 HttpStatusCode = 0;` — Raw HTTP response status code (e.g. 200, 404, 503). Zero when no HTTP response was actually received - e.g. the request failed before reaching the server, or the result was synthesized from a local cache hit.

### `Source/Runtime/StorageServerClient/Private/StorageServerIoDispatcherBackend.h` (Private)


#### class `FStorageServerIoDispatcherBackend`  
`class FStorageServerIoDispatcherBackend final : public FRunnable , public IIoDispatcherBackend`  
_L14-101_
- inherits: `FRunnable,IIoDispatcherBackend`
- L19 _public prototype_ `FStorageServerIoDispatcherBackend(FStorageServerConnection& Connection);`
- L20 _public prototype_ `~FStorageServerIoDispatcherBackend();`
- L22 _public prototype_ `void Initialize(TSharedRef<const FIoDispatcherBackendContext> Context) override;`
- L23 _public prototype_ `void Shutdown() override;`
- L24 _public prototype_ `void ResolveIoRequests(FIoRequestList Requests, FIoRequestList& OutUnresolved) override;`
- L25 _public function_ `void CancelIoRequest(FIoRequestImpl* Request) override`
- L26 _public function_ `void UpdatePriorityForIoRequest(FIoRequestImpl* Request) override`
- L27 _public prototype_ `bool DoesChunkExist(const FIoChunkId& ChunkId) const override;`
- L28 _public prototype_ `TIoStatusOr<uint64> GetSizeForChunk(const FIoChunkId& ChunkId) const override;`
- L29 _public prototype_ `FIoRequestImpl* GetCompletedIoRequests() override;`
- L30 _public function_ `TIoStatusOr<FIoMappedRegion> OpenMapped(const FIoChunkId& ChunkId, const FIoReadOptions& Options) override`
- L34 _public prototype_ `const TCHAR* GetName() const override;`
- L36 _public function_ `virtual bool Init() override`
- L40 _public prototype_ `virtual uint32 Run() override;`
- L41 _public prototype_ `virtual void Stop() override;`
- L82 _private prototype_ `bool Resolve(FIoRequestImpl* Request);`
- L83 _private prototype_ `void SubmitBatch(FBatch* Batch);`
- L84 _private prototype_ `void OnBatchCompleted(FBatch* Batch);`
- L85 _private prototype_ `bool WaitForBatchToComplete(uint32 WaitTime = MAX_uint32);`
- L87 _private member_ `FStorageServerConnection& Connection;`
- L88 _private member_ `TSharedPtr<const FIoDispatcherBackendContext> BackendContext;`
- L89 _private member_ `FRunnableThread* Thread = nullptr;`
- L90 _private member_ `FEvent* NewRequestEvent;`
- L91 _private member_ `FRequestQueue RequestQueue;`
- L92 _private member_ `FBatch* FirstAvailableBatch = nullptr;`
- L93 _private member_ `int32 SubmittedBatchesCount = 0;`
- L94 _private member_ `FCriticalSection CompletedBatchesCritical;`
- L95 _private member_ `FBatch* FirstCompletedBatch = nullptr;`
- L96 _private member_ `FEvent* BatchCompletedEvent;`
- L97 _private member_ `FCriticalSection CompletedRequestsCritical;`
- L98 _private member_ `FIoRequestImpl* CompletedRequestsHead = nullptr;`
- L99 _private member_ `FIoRequestImpl* CompletedRequestsTail = nullptr;`
- L100 _private member_ `TAtomic<bool> bStopRequested{ false };`

#### class `FStorageServerIoDispatcherBackend::FRequestQueue`  
`class FRequestQueue`  
_L44-65_
- L47 _public prototype_ `FIoRequestImpl* Pop();`
- L48 _public prototype_ `void Push(FIoRequestImpl& Request);`
- L49 _public prototype_ `void UpdateOrder();`
- L52 _private function_ `static bool QueueSortFunc(const FIoRequestImpl& A, const FIoRequestImpl& B)`
- L63 _private member_ `TArray<FIoRequestImpl*> Heap;`
- L64 _private member_ `FCriticalSection CriticalSection;`

#### struct `FStorageServerIoDispatcherBackend::FBatch`  
`struct FBatch : public IQueuedWork`  
_L67-80_
- inherits: `IQueuedWork`
- L70 _public prototype_ `FBatch(FStorageServerIoDispatcherBackend& InOwner);`
- L72 _public prototype_ `virtual void DoThreadedWork() override;`
- L73 _public function_ `virtual void Abandon() override`
- L75 _public member_ `FStorageServerIoDispatcherBackend& Owner;`
- L76 _public member_ `FBatch* Next = nullptr;`
- L77 _public member_ `FIoRequestImpl* RequestsHead = nullptr;`
- L78 _public member_ `FIoRequestImpl* RequestsTail = nullptr;`
- L79 _public member_ `uint64 RequestsCount = 0;`

### `Source/Runtime/StorageServerClient/Private/StorageServerPackageStore.h` (Private)


#### class `FStorageServerPackageStoreBackend`  
`class FStorageServerPackageStoreBackend : public IPackageStoreBackend`  
_L14-68_
- inherits: `IPackageStoreBackend`
- L18 _public prototype_ `FStorageServerPackageStoreBackend(FStorageServerConnection& Connection);`
- L19 _public prototype_ `virtual ~FStorageServerPackageStoreBackend() = default;`
- L21 _public function_ `virtual void OnMounted(TSharedRef<const FPackageStoreBackendContext> Context) override`
- L25 _public function_ `virtual void BeginRead() override`
- L29 _public function_ `virtual void EndRead() override`
- L33 _public prototype_ `virtual EPackageStoreEntryStatus GetPackageStoreEntry(FPackageId PackageIde, FName PackageName, FPackageStoreEntry& OutPackageStoreEntry) override;`
- L36 _public function_ `virtual bool GetPackageRedirectInfo(FPackageId PackageId, FName& OutSourcePackageName, FPackageId& OutRedirectedToPackageId) override`
- L51 _private member_ `TMap<FPackageId, FStoreEntry> StoreEntriesMap;`
- L67 _private member_ `TSharedPtr<FAsyncInitRunnable, ESPMode::ThreadSafe> AsyncInit;`

#### struct `FStorageServerPackageStoreBackend::FStoreEntry`  
`struct FStoreEntry`  
_L42-50_
- L44 _public member_ `TArray<FPackageId> ImportedPackages;`
- L45 _public member_ `TArray<FShaderHash> ShaderMapHashes;`
- L47 _public member_ `EPackageStoreEntryFlags Flags;`
- L48 _public member_ `TArray<FPackageId> OptionalSegmentImportedPackageIds;`

#### class `FStorageServerPackageStoreBackend::FAsyncInitRunnable`  
`class FAsyncInitRunnable : public FRunnable`  
_L53-66_
- inherits: `FRunnable`
- L56 _public prototype_ `FAsyncInitRunnable(FStorageServerPackageStoreBackend& InOwner, FStorageServerConnection& InConnection);`
- L57 _public prototype_ `virtual ~FAsyncInitRunnable();`
- L58 _public prototype_ `void WaitForCompletion() const;`
- L61 _private prototype_ `virtual uint32 Run() override;`
- L63 _private member_ `FStorageServerPackageStoreBackend& Owner;`
- L64 _private member_ `FStorageServerConnection& Connection;`
- L65 _private member_ `class FEvent* IsCompleted;`

### `Source/Runtime/StorageServerClient/Private/StorageServerPlatformFile.h` (Private)


#### class `FStorageServerFileSystemTOC`  
`class FStorageServerFileSystemTOC`  
_L31-66_
- L34 _public prototype_ `~FStorageServerFileSystemTOC();`
- L35 _public prototype_ `void AddFile(const FIoChunkId& FileChunkId, FStringView Path, int64 RawSize);`
- L36 _public prototype_ `void Clear();`
- L37 _public prototype_ `bool FileExists(const FString& Path);`
- L38 _public prototype_ `bool DirectoryExists(const FString& Path);`
- L39 _public prototype_ `const FIoChunkId* GetFileChunkId(const FString& Path);`
- L40 _public prototype_ `int64 GetFileSize(const FString& Path);`
- L41 _public prototype_ `bool GetFileData(const FString& Path, FIoChunkId& OutChunkId, int64& OutRawSize);`
- L42 _public prototype_ `bool IterateDirectory(const FString& Path, TFunctionRef<bool(const FIoChunkId&, const TCHAR*, int64)> Callback);`
- L43 _public prototype_ `bool IterateDirectoryRecursively(const FString& Path, TFunctionRef<bool(const FIoChunkId&, const TCHAR*, int64)> Callback);`
- L59 _private prototype_ `FDirectory* AddDirectoriesRecursive(const FString& DirectoryPath);`
- L61 _private member_ `FDirectory Root;`
- L62 _private member_ `TMap<FString, FDirectory*> Directories;`
- L63 _private member_ `TMap<FString, int32> FilePathToIndexMap;`
- L64 _private member_ `TArray<FFile> Files;`
- L65 _private member_ `FRWLock TocLock;`

#### struct `FStorageServerFileSystemTOC::FDirectory`  
`struct FDirectory`  
_L46-50_
- L48 _public member_ `TArray<FString> Directories;`
- L49 _public member_ `TArray<int32> Files;`

#### struct `FStorageServerFileSystemTOC::FFile`  
`struct FFile`  
_L52-57_
- L54 _public member_ `FIoChunkId FileChunkId;`
- L55 _public member_ `FString FilePath;`
- L56 _public member_ `int64 RawSize;`

#### class `FStorageServerPlatformFile`  
`class FStorageServerPlatformFile : public IStorageServerPlatformFile`  
_L68-189_
- inherits: `IStorageServerPlatformFile`
- L72 _public prototype_ `FStorageServerPlatformFile();`
- L73 _public prototype_ `virtual ~FStorageServerPlatformFile();`
- L74 _public prototype_ `virtual bool ShouldBeUsed(IPlatformFile* Inner, const TCHAR* CmdLine) const override;`
- L75 _public prototype_ `virtual bool Initialize(IPlatformFile* Inner, const TCHAR* CmdLine) override;`
- L76 _public prototype_ `virtual void InitializeAfterProjectFilePath() override;`
- L78 _public function_ `virtual IPlatformFile* GetLowerLevel() override`
- L83 _public function_ `virtual void SetLowerLevel(IPlatformFile* NewLowerLevel) override`
- L88 _public function_ `virtual const TCHAR* GetName() const override`
- L93 _public prototype_ `virtual bool FileExists(const TCHAR* Filename) override;`
- L94 _public prototype_ `virtual int64 FileSize(const TCHAR* Filename) override;`
- L95 _public prototype_ `virtual bool IsReadOnly(const TCHAR* Filename) override;`
- L96 _public prototype_ `virtual FDateTime GetTimeStamp(const TCHAR* Filename) override;`
- L97 _public prototype_ `virtual FDateTime GetAccessTimeStamp(const TCHAR* Filename) override;`
- L98 _public prototype_ `virtual IFileHandle* OpenRead(const TCHAR* Filename, bool bAllowWrite = false) override;`
- L99 _public prototype_ `virtual bool DirectoryExists(const TCHAR* Directory) override;`
- L100 _public prototype_ `virtual FFileStatData GetStatData(const TCHAR* FilenameOrDirectory) override;`
- L101 _public prototype_ `virtual bool IterateDirectory(const TCHAR* Directory, FDirectoryVisitor& Visitor) override;`
- L102 _public prototype_ `virtual bool IterateDirectoryRecursively(const TCHAR* Directory, FDirectoryVisitor& Visitor) override;`
- L103 _public prototype_ `virtual bool IterateDirectoryStat(const TCHAR* Directory, FDirectoryStatVisitor& Visitor) override;`
- L104 _public prototype_ `virtual FOpenMappedResult OpenMappedEx(const TCHAR* Filename, EOpenReadFlags OpenOptions = EOpenReadFlags::None, int64 MaximumSize = 0) override;`
- L105 _public prototype_ `virtual FOpenMappedResult OpenMappedEx2(const TCHAR* Filename, EOpenMappedFlags OpenOptions = EOpenMappedFlags::None, int64 MaximumSize = 0) override;`
- L106 _public prototype_ `virtual FString GetFilenameOnDisk(const TCHAR* Filename) override;`
- L107 _public prototype_ `virtual bool DeleteFile(const TCHAR* Filename) override;`
- L108 _public prototype_ `virtual bool MoveFile(const TCHAR* To, const TCHAR* From) override;`
- L109 _public prototype_ `virtual bool SetReadOnly(const TCHAR* Filename, bool bNewReadOnlyValue) override;`
- L110 _public prototype_ `virtual void SetTimeStamp(const TCHAR* Filename, FDateTime DateTime) override;`
- L111 _public prototype_ `virtual IFileHandle* OpenWrite(const TCHAR* Filename, bool bAppend = false, bool bAllowRead = false) override;`
- L112 _public prototype_ `virtual bool CreateDirectory(const TCHAR* Directory) override;`
- L113 _public prototype_ `virtual bool DeleteDirectory(const TCHAR* Directory) override;`
- L114 _public prototype_ `virtual FString ConvertToAbsolutePathForExternalAppForRead(const TCHAR* Filename) override;`
- L115 _public prototype_ `virtual FString ConvertToAbsolutePathForExternalAppForWrite(const TCHAR* Filename) override;`
- L116 _public prototype_ `virtual bool SendMessageToServer(const TCHAR* Message, IPlatformFile::IFileServerMessageHandler* Handler) override;`
- L118 _public prototype_ `FStringView GetHostAddr() const override;`
- L119 _public prototype_ `void GetAndResetConnectionStats(FConnectionStats& OutStats) override;`
- L121 _public function_ `void SetAllowPackageIo(bool bInAllowPackageIo)`
- L125 _public function_ `void SetAbortOnConnectionFailure(bool bInAbortOnConnectionFailure)`
- L129 _public function_ `void SetCustomProjectStorePath(FStringView InProjectStorePath)`
- L134 _public prototype_ `void UpdateFileList() override;`
- L136 _public function_ `bool IsConnectionValid() const`
- L141 _public prototype_ `TSharedPtr<IPackageStoreBackend> CreatePackageStoreBackend() const;`
- L142 _public prototype_ `TSharedPtr<IIoDispatcherBackend> CreateIoDispatcherBackend() const;`
- L149 _private prototype_ `void InitializeConnection();`
- L150 _private prototype_ `bool IsNonServerFilenameAllowed(FStringView InFilename);`
- L151 _private prototype_ `bool IsAssumedImmutableTimeStampFilename(FStringView InFilename) const;`
- L152 _private prototype_ `bool IsEngineStartupPrecachableFilename(FStringView InFilename) const;`
- L153 _private prototype_ `bool MakeStorageServerPath(const TCHAR* LocalFilenameOrDirectory, FStringBuilderBase& OutPath) const;`
- L154 _private prototype_ `bool MakeLocalPath(const TCHAR* ServerFilenameOrDirectory, FStringBuilderBase& OutPath) const;`
- L155 _private prototype_ `IFileHandle* InternalOpenFile(const FIoChunkId& FileChunkId, int64 RawSize, const TCHAR* LocalFilename);`
- L156 _private prototype_ `bool SendGetFileListMessage();`
- L157 _private prototype_ `FFileStatData SendGetStatDataMessage(const FIoChunkId& FileChunkId);`
- L158 _private prototype_ `int64 SendReadMessage(uint8* Destination, const FIoChunkId& FileChunkId, int64 Offset, int64 BytesToRead);`
- L160 _private prototype_ `void OnCookOnTheFlyMessage(const UE::Cook::FCookOnTheFlyMessage& Message);`
- L162 _private prototype_ `TUniquePtr<FArchive> TryFindProjectStoreMarkerFile(IPlatformFile* Inner) const;`
- L163 _private prototype_ `FAnsiString MakeBaseURI();`
- L165 _private member_ `FString CustomProjectStorePath;`
- L166 _private member_ `TSet<FName> ExcludedNonServerExtensions;`
- L167 _private member_ `TSet<FName> AssumedImmutableTimeStampExtensions;`
- L168 _private member_ `TSet<FName> EngineStartupPrecacheExtensions;`
- L169 _private member_ `IPlatformFile* LowerLevel = nullptr;`
- L170 _private member_ `FStringView ServerEngineDirView = FStringView(TEXT("/{en`
- L171 _private member_ `FStringView ServerProjectDirView = FStringView(TEXT("/{pr`
- L172 _private member_ `TUniquePtr<FStorageServerConnection> Connection;`
- L174 _private member_ `TSharedPtr<UE::Cook::ICookOnTheFlyServerConnection> CookOnTheFlyServerConnection;`
- L176 _private member_ `FStorageServerFileSystemTOC ServerToc;`
- L177 _private member_ `FString ServerProject;`
- L178 _private member_ `FString ServerPlatform;`
- L179 _private member_ `FString BaseURI;`
- L180 _private member_ `FString AbsProjectDir;`
- L181 _private member_ `FString AbsEngineDir;`
- L182 _private member_ `FString WorkspaceSharePath;`
- L183 _private member_ `TDirectoryTree<FString> RemapDirectoriesTree;`
- L184 _private member_ `mutable TArray<FString> HostAddrs;`
- L185 _private member_ `mutable uint16 HostPort = 8558;`
- L186 _private member_ `TArray<FAnsiString> AuthHeaders;`
- L187 _private member_ `bool bAllowPackageIo = true;`
- L188 _private member_ `bool bAbortOnConnectionFailure = true;`

#### Free symbols / members of external scopes

- L22 _namespace_ `namespace UE`
- L22 _namespace_ `namespace Cook` (scope `UE`)
- L29 _macro_ `#define STORAGE_SERVER_FILE_UNKOWN_SIZE (-1)`

### `Source/Runtime/StorageServerClient/Private/ZenStreamingSettings.h` (Private)


#### class `UZenStreamingSettings`  
`class UZenStreamingSettings : public UDeveloperSettings`  
_L11-36_
- reflection: `UCLASS(MinimalAPI, config=Game, defaultconfig, meta=(DisplayName="Zen Streaming"))`
- inherits: `UDeveloperSettings`
- L20 _public member_ `bool bShowZenBadge = true;` — `UPROPERTY(config, EditAnywhere, Category = ZenStreaming, meta=(DisplayName="Show Zen streaming badge", ConsoleVariable="zen.indicator.show"))` — Show an in-game badge to indicate if the client is streaming from Zen
- L23 _public member_ `float BadgePositionX = 0.05f;` — `UPROPERTY(config, EditAnywhere, Category = ZenStreaming, meta=(ClampMin=0, ClampMax=1.0, ConsoleVariable="zen.indicator.x"))`
- L26 _public member_ `float BadgePositionY = 0.8f;` — `UPROPERTY(config, EditAnywhere, Category = ZenStreaming, meta=(ClampMin=0, ClampMax=1.0, ConsoleVariable="zen.indicator.y"))`
- L32 _public member_ `float BadgeFadeTime = -1;` — `UPROPERTY(config, EditAnywhere, Category = ZenStreaming, meta=(ClampMin=-1, ConsoleVariable="zen.indicator.fadetime"))` — For how long (in seconds) should the badge stay on screen. < 0 will make the badge persistent
- L35 _public member_ `float BadgeAlpha = 0.5;` — `UPROPERTY(config, EditAnywhere, Category = ZenStreaming, meta=(ClampMin=0, ClampMax=1.0, ConsoleVariable="zen.indicator.alpha"))`
