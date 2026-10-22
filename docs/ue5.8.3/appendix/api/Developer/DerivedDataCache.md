# Developer / DerivedDataCache

- module root: `Source/Developer/DerivedDataCache`
- headers: 58; symbols: 2393
- symbol kinds: class=103, delegate=11, enum=18, enumerator=93, function=443, macro=20, member=398, namespace=514, prototype=668, struct=72, typedef=50, variable=3
- PrivateDependencyModuleNames: Core, DevHttp, Json, SSL, Zen
- PrivateIncludePathModuleNames: Analytics, DesktopPlatform

### `Source/Developer/DerivedDataCache/Internal/Containers/ConcurrentChunkedSparseArray.h` (Internal)


#### class `UE::TConcurrentChunkedSparseArray`  
`template <typename ElementType, uint32 ElementsPerChunk> class TConcurrentChunkedSparseArray`  
_L24-314_
- desc: A concurrent chunked sparse array that maintains every index at a consistent address once allocated. It is safe to add, remove, and access elements from multiple threads concurrently. Callers are responsible for ensuring multiple threads are not mutating the same element concurrently. Iteration is not provided because it is not safe in the presence of concurrent add and remove operations.
- L33 _private prototype_ `TConcurrentChunkedSparseArray(const TConcurrentChunkedSparseArray&) = delete;` — Not implemented but can be if necessary.
- L34 _private prototype_ `TConcurrentChunkedSparseArray& operator=(const TConcurrentChunkedSparseArray&) = delete;`
- L37 _public prototype_ `constexpr TConcurrentChunkedSparseArray() = default;`
- L39 _public function_ `~TConcurrentChunkedSparseArray()`
- L98 _public function_ `[[nodiscard]] inline ElementType& operator[](const uint32 ElementIndex) UE_LIFETIMEBOUND`
- L110 _public function_ `[[nodiscard]] UE_REWRITE const ElementType& operator[](const uint32 ElementIndex) const UE_LIFETIMEBOUND`
- L116 _public function_ `template <typename... ArgTypes> [[nodiscard]] inline uint32 Emplace(ArgTypes&&... Args)`
- L125 _public function_ `[[nodiscard]] UE_REWRITE uint32 AddUninitialized()`
- L131 _public function_ `[[nodiscard]] inline uint32 AddUninitialized(const uint32 ElementCount)`
- L154 _public function_ `inline void RemoveAt(uint32 ElementIndex)`
- L196 _private function_ `[[nodiscard]] inline uint32 PrivateAddUninitialized(FChunk*& OutChunk)`
- L205 _private function_ `FORCEINLINE uint32 AcquireElementIndex()`
- L232 _private function_ `FORCEINLINE FChunkArray* GetOrGrowChunkArray(const uint32 ElementIndex)`
- L242 _private function_ `FORCENOINLINE FChunkArray* GrowChunkArray(const uint32 ElementIndex, FChunkArray* Array)`
- L270 _private function_ `FORCEINLINE static FChunk* GetOrCreateChunk(FChunkArray* Array, uint32 ChunkIndex)`
- L279 _private function_ `FORCENOINLINE static FChunk* CreateChunk(FChunkArray* Array, uint32 ChunkIndex)`
- L304 _private member_ `inline static FChunkArray EmptyChunkArray;` — A shared empty chunk array that avoids requiring null checks to handle empty arrays.
- L307 _private member_ `std::atomic<FChunkArray*> ChunkArray = &EmptyChunkArray;` — Pointer to the current chunk array.
- L310 _private member_ `std::atomic<uint64> FreeElementIndexAndCounter = uint64(MAX_uint32) << 32;` — Index of the first free element (or MAX_uint32) in the high 32 bits. Counter to avoid the ABA problem in the low 32 bits.
- L313 _private member_ `std::atomic<uint32> NextElementIndex = 0;` — Index of the next element allocated at the end of the array. Used when there are no free elements or when allocating multiple elements at once.

#### struct `UE::TConcurrentChunkedSparseArray::FChunk`  
`struct FChunk`  
_L181-184_
- L183 _public member_ `TTypeCompatibleBytes<ElementType> Elements[ElementsPerChunk];`

#### struct `UE::TConcurrentChunkedSparseArray::FChunkArray`  
`struct FChunkArray`  
_L186-194_
- L188 _public member_ `uint32 ChunkCount = 0;`
- L189 _public member_ `uint32 Padding = 0;`
- L191 _public member_ `FChunkArray* Prev = nullptr;` — Pointer to the previous chunk array, to be deleted upon destruction of the container.
- L193 _public member_ `std::atomic<FChunk*> Chunks[0];` — Array of ChunkCount chunks that are allocated on demand.

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L27 _prototype_ `static_assert(FMath::IsPowerOfTwo(ElementsPerChunk), "Ele` (scope `UE::TConcurrentChunkedSparseArray::FMath`)

### `Source/Developer/DerivedDataCache/Internal/Containers/ProbingHashTable.h` (Internal)


#### class `UE::FProbingHashTable`  
`class FProbingHashTable`  
_L31-390_
- desc: A linear-probing hash table that can be used to index another data structure. The least significant bits of the hash are used to pick a bucket and the most significant bits of the hash are used to quickly match slots within a bucket. For the best performance, hashes must have good distribution across their whole range, not only in the lower bits. Example: uint32 Index; uint32 Hash = GetTypeHash(ID); for (FProbingHashTable::FSlotId SlotId = HashTable.FindFirst(Hash, Index); SlotId; SlotId = HashTable.FindNext(SlotId, Hash, Index)) { if (Array[Index].ID == ID) { return Array[Index]; } }
- L33 _private member_ `inline constexpr static uint32 MaxLoadFactorNum = 7;`
- L34 _private member_ `inline constexpr static uint32 MaxLoadFactorDen = 8;`
- L37 _private member_ `inline constexpr static uint32 SlotsPerBlock = 7;`
- L61 _private prototype_ `FProbingHashTable(const FProbingHashTable&) = delete;` — Not implemented but can be if necessary.
- L62 _private prototype_ `FProbingHashTable& operator=(const FProbingHashTable&) = delete;`
- L65 _public prototype_ `constexpr FProbingHashTable() = default;`
- L67 _public function_ `inline FProbingHashTable(FProbingHashTable&& Other) : Blocks(Other.Blocks) , BlockCountMinusOne(Other.BlockCountMinusOne) , FreeSlotCount(Other.FreeSlotCount)`
- L77 _public function_ `inline FProbingHashTable& operator=(FProbingHashTable&& Other)`
- L92 _public function_ `inline ~FProbingHashTable()`
- L98 _public function_ `UE_REWRITE void Empty()` — Remove everything from the hash table and release its memory.
- L132 _public function_ `FSlotId Add(uint32 Hash, uint32 Index)` — Add the pair of Hash and Index. Does not check for duplicates. @return The ID of the slot containing the pair. Valid until the next call to Add.
- L159 _public function_ `inline void Remove(FSlotId Id)` — Remove the pair of hash and index in the slot referenced by ID. The ID remains valid for subsequent calls to FindNext.
- L174 _public function_ `[[nodiscard]] inline FSlotId FindFirst(uint32 Hash, uint32& OutIndex) const` — Find the first slot that matches Hash and assign its index to OutIndex. @return The ID of the matching slot, or an invalid ID. Valid until the next call to Add.
- L189 _public function_ `[[nodiscard]] FSlotId FindNext(FSlotId Id, uint32 Hash, uint32& OutIndex) const` — Find the next slot after Id that matches Hash and assign its index to OutIndex. @return The ID of the matching slot, or an invalid ID. Valid until the next call to Add.
- L259 _public function_ `[[nodiscard]] inline uint32& operator[](FSlotId Id)` — Access the index in the slot referenced by ID.
- L273 _public function_ `inline void EnsureAdditionalCapacity(uint32 Capacity)` — Resize if needed to ensure that Capacity additional elements can be added without rehashing. Like Reserve() on other containers but takes *additional* capacity since neither Num() or Max() are provided by this container.
- L347 _public function_ `[[nodiscard]] UE_REWRITE FConstIterator CreateConstIterator() const`
- L354 _private function_ `FORCENOINLINE void ExpandCapacity(const uint32 SlotCount)` — Expand capacity by at least SlotCount free slots, ignoring existing free slots.
- L377 _private function_ `constexpr static uint32 CalculateCapacity(uint32 BlockCount)` — Calculate the effective capacity from BlockCount, accounting for the max load factor.
- L387 _private member_ `FBlock* Blocks = nullptr;`
- L388 _private member_ `uint32 BlockCountMinusOne = MAX_uint32;`
- L389 _private member_ `uint32 FreeSlotCount = 0;`

#### struct `UE::FProbingHashTable::FSlot`  
`struct FSlot`  
_L39-43_
- L41 _public member_ `uint32 Hash = 0;`
- L42 _public member_ `uint32 Index = 0;`

#### struct `UE::FProbingHashTable::FBlock`  
`struct alignas(64) FBlock`  
_L45-56_
- L50 _public member_ `uint64 MaskAndHashes = 0;` — Byte 0:0 is set when probing must consider the next block if a match is not found in this block. Byte 0:1-7 are a mask of which slots are occupied in this block. Bytes 1-7 are the most significant byte of the hash of the element in the corresponding slot.
- L51 _public member_ `FSlot Slots[SlotsPerBlock];`
- L53 _public member_ `inline constexpr static uint64 ProbeMask = 0x01;`
- L54 _public member_ `inline constexpr static uint64 SlotMask = 0xfe;`
- L55 _public member_ `inline constexpr static uint64 HashMask = 0xffff'ffff'ffff'ff00;`

#### struct `UE::FProbingHashTable::FSlotId`  
`struct FSlotId`  
_L104-125_
- desc: A reference to a slot within the hash table.
- L106 _public function_ `[[nodiscard]] inline explicit operator bool() const`
- L112 _private function_ `[[nodiscard]] inline static FSlotId Create(uint32 InBlockIndex, uint32 InSlotIndexPlusOne)`
- L120 _private member_ `uint32 BlockIndex : 29 = 0;`
- L121 _private member_ `uint32 SlotIndexPlusOne : 3 = 0;`

#### class `UE::FProbingHashTable::FConstIterator`  
`class FConstIterator`  
_L281-345_
- L284 _public prototype_ `constexpr FConstIterator() = default;`
- L286 _public function_ `inline explicit FConstIterator(const FProbingHashTable& HashTable) : Block(HashTable.Blocks) , BlockCount(HashTable.BlockCountMinusOne + 1) , SlotMask(BlockCount ? (Block->MaskAndHashes & FBlock::SlotMask) : 0)`
- L294 _public function_ `inline FConstIterator& operator++()`
- L315 _public function_ `[[nodiscard]] inline explicit operator bool() const`
- L320 _public function_ `[[nodiscard]] inline bool operator==(const FConstIterator& Other) const`
- L325 _public function_ `[[nodiscard]] UE_REWRITE uint32 operator*() const`
- L330 _public function_ `[[nodiscard]] inline uint32 GetHash() const`
- L335 _public function_ `[[nodiscard]] inline uint32 GetIndex() const`
- L341 _private member_ `const FBlock* Block = nullptr;`
- L342 _private member_ `uint32 BlockCount = 0;`
- L343 _private member_ `uint8 SlotIndex = 0;`
- L344 _private member_ `uint8 SlotMask = 0;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L384 _function_ `[[nodiscard]] UE_REWRITE friend FConstIterator begin(const FProbingHashTable& HashTable)` (scope `UE`)
- L385 _function_ `[[nodiscard]] constexpr friend FConstIterator end(const FProbingHashTable& HashTable)` (scope `UE`)

### `Source/Developer/DerivedDataCache/Internal/DerivedDataCacheKeyFilter.h` (Internal)


#### class `UE::DerivedData::FCacheKeyFilter`  
`class FCacheKeyFilter`  
_L17-62_
- desc: A type that filters cache keys by their bucket/type and at a configurable match rate.
- L42 _public prototype_ `static FCacheKeyFilter Parse(const TCHAR* Config, const TCHAR* BucketPrefix, const TCHAR* KeyPrefix, float DefaultRate = 0.0f);` — Parses a filter from a configuration string. Example: - Config = "-DDC-Verify=Texture@2.5+StaticMesh -Unused -DDC-Verify=Audio@75" - BucketPrefix = "-DDC-Verify=" - DefaultRate = 50.0f - Filter matches Texture at a rate of 2.5%, StaticMesh at a rate of 100%, Audio at a rate of 75%, and everything else at a rate of 50%. - Config = "-DDC-All-MissTypes=StaticMesh@50 -DDC-All-MissKeys=Texture/0123456789abcdef0123456789abcdef01234567" - BucketPrefix = "-DDC-All-MissTypes=" - KeyPrefix = "-DDC-All-MissKeys=" - Filter matches StaticMesh at 50%, the single Texture key specified, and everything else at a rate of 0%. Multiple buckets or keys in one argument are delimited by '+' or ','. @param Config         The configuration in the form of command line parameters. @param BucketPrefix   The prefix of the parameter to parse the bucket filter from. Disabled if null. @param KeyPrefix      The prefix of the parameter to parse the key filter from. Disabled if null. @param DefaultRate    The default rate at which to apply the filter. [0, 100]
- L50 _public prototype_ `void SetSalt(uint32 Salt);` — Accesses the salt that is combined with the cache key for filtering. The filter will always produce the same output for a fixed pair of salt and key. To change the behavior of the filter between sessions, the salt is assigned randomly by default.
- L51 _public prototype_ `uint32 GetSalt() const;`
- L52 _public prototype_ `bool RequiresSalt() const;`
- L55 _public prototype_ `bool IsMatch(const FCacheKey& Key) const;` — Returns true if the filter matches the key. The output is the same until the salt changes.
- L58 _public function_ `inline explicit operator bool() const` — Returns true if this filter can ever match a cache key.
- L61 _private member_ `TPimplPtr<Private::FCacheKeyFilterState, EPimplPtrMode::DeepCopy> State;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API DERIVEDDATACACHE_API`
- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace DerivedData` (scope `UE`)
- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace DerivedData` (scope `UE`)
- L11 _namespace_ `namespace Private` (scope `UE::DerivedData`)
- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace DerivedData` (scope `UE`)

### `Source/Developer/DerivedDataCache/Internal/DerivedDataCacheMethod.h` (Internal)


#### enum `UE::DerivedData::ECacheMethod`  
`enum class ECacheMethod : uint8`  
_L13-20_
- L15 _public enumerator_ `Put`
- L16 _public enumerator_ `Get`
- L17 _public enumerator_ `PutValue`
- L18 _public enumerator_ `GetValue`
- L19 _public enumerator_ `GetChunks`

#### class `UE::DerivedData::FCacheMethodFilter`  
`class FCacheMethodFilter`  
_L29-42_
- L33 _public prototype_ `static FCacheMethodFilter Parse(FStringView MethodNames);` — Parse from method names delimited by ',' or '+'.
- L35 _public function_ `inline bool IsMatch(ECacheMethod Method) const`
- L41 _private member_ `uint32 MethodMask = 0;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API DERIVEDDATACACHE_API`
- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace DerivedData` (scope `UE`)
- L22 _prototype_ `FAnsiStringBuilderBase& operator<<(FAnsiStringBuilderBase& Builder, ECacheMethod Method);` (scope `UE::DerivedData`)
- L23 _prototype_ `FWideStringBuilderBase& operator<<(FWideStringBuilderBase& Builder, ECacheMethod Method);` (scope `UE::DerivedData`)
- L24 _prototype_ `FUtf8StringBuilderBase& operator<<(FUtf8StringBuilderBase& Builder, ECacheMethod Method);` (scope `UE::DerivedData`)
- L26 _prototype_ `bool TryLexFromString(ECacheMethod& OutMethod, FUtf8StringView String);` (scope `UE::DerivedData`)
- L27 _prototype_ `bool TryLexFromString(ECacheMethod& OutMethod, FWideStringView String);` (scope `UE::DerivedData`)

### `Source/Developer/DerivedDataCache/Internal/DerivedDataCacheReplay.h` (Internal)


#### class `UE::DerivedData::ICacheReplayWriter`  
`class ICacheReplayWriter`  
_L28-41_
- L31 _public prototype_ `void Write(TConstArrayView<FCachePutRequest> Requests, TConstArrayView<FCachePutResponse> Responses, EPriority Priority);`
- L32 _public prototype_ `void Write(TConstArrayView<FCacheGetRequest> Requests, TConstArrayView<FCacheGetResponse> Responses, EPriority Priority);`
- L33 _public prototype_ `void Write(TConstArrayView<FCachePutValueRequest> Requests, TConstArrayView<FCachePutValueResponse> Responses, EPriority Priority);`
- L34 _public prototype_ `void Write(TConstArrayView<FCacheGetValueRequest> Requests, TConstArrayView<FCacheGetValueResponse> Responses, EPriority Priority);`
- L35 _public prototype_ `void Write(TConstArrayView<FCacheGetChunkRequest> Requests, TConstArrayView<FCacheGetChunkResponse> Responses, EPriority Priority);`
- L37 _public prototype_ `virtual ~ICacheReplayWriter() = default;`
- L40 _public prototype_ `virtual void SerializeBatch(const FCbWriter& Batch) = 0;` — Do not call directly unless forwarding from another ICacheReplayWriter.

#### class `UE::DerivedData::ICacheReplayReader`  
`class ICacheReplayReader`  
_L43-56_
- L46 _public prototype_ `virtual void Read(TConstArrayView<FCachePutRequest> Requests, TConstArrayView<FCachePutResponse> Responses, EPriority Priority) = 0;`
- L47 _public prototype_ `virtual void Read(TConstArrayView<FCacheGetRequest> Requests, TConstArrayView<FCacheGetResponse> Responses, EPriority Priority) = 0;`
- L48 _public prototype_ `virtual void Read(TConstArrayView<FCachePutValueRequest> Requests, TConstArrayView<FCachePutValueResponse> Responses, EPriority Priority) = 0;`
- L49 _public prototype_ `virtual void Read(TConstArrayView<FCacheGetValueRequest> Requests, TConstArrayView<FCacheGetValueResponse> Responses, EPriority Priority) = 0;`
- L50 _public prototype_ `virtual void Read(TConstArrayView<FCacheGetChunkRequest> Requests, TConstArrayView<FCacheGetChunkResponse> Responses, EPriority Priority) = 0;`
- L52 _public prototype_ `virtual ~ICacheReplayReader() = default;`
- L55 _public prototype_ `virtual bool SerializeBatch(FCbObjectView Batch);` — Do not call directly unless forwarding from another ICacheReplayReader.

#### class `UE::DerivedData::FCacheReplayForwardingReader`  
`class FCacheReplayForwardingReader final : public ICacheReplayReader`  
_L77-112_
- inherits: `ICacheReplayReader`
- desc: A replay reader that forwards every batch to a writer.
- L80 _public function_ `inline explicit FCacheReplayForwardingReader(ICacheReplayWriter& TargetWriter) : Writer(TargetWriter)`
- L85 _public function_ `void Read(TConstArrayView<FCachePutRequest> Requests, TConstArrayView<FCachePutResponse> Responses, EPriority Priority) final`
- L90 _public function_ `void Read(TConstArrayView<FCacheGetRequest> Requests, TConstArrayView<FCacheGetResponse> Responses, EPriority Priority) final`
- L95 _public function_ `void Read(TConstArrayView<FCachePutValueRequest> Requests, TConstArrayView<FCachePutValueResponse> Responses, EPriority Priority) final`
- L100 _public function_ `void Read(TConstArrayView<FCacheGetValueRequest> Requests, TConstArrayView<FCacheGetValueResponse> Responses, EPriority Priority) final`
- L105 _public function_ `void Read(TConstArrayView<FCacheGetChunkRequest> Requests, TConstArrayView<FCacheGetChunkResponse> Responses, EPriority Priority) final`
- L111 _private member_ `ICacheReplayWriter& Writer;`

#### class `UE::DerivedData::FCacheReplayReader`  
`class FCacheReplayReader`  
_L114-136_
- L117 _public member_ `static constexpr uint64 DefaultScratchSize = 1024;`
- L119 _public prototype_ `explicit FCacheReplayReader(ILegacyCacheStore* TargetCache);`
- L121 _public prototype_ `void SetKeyFilter(FCacheKeyFilter KeyFilter);`
- L122 _public prototype_ `void SetMethodFilter(FCacheMethodFilter MethodFilter);`
- L123 _public prototype_ `void SetPolicyTransform(ECachePolicy AddFlags, ECachePolicy RemoveFlags);`
- L124 _public prototype_ `void SetPriorityOverride(EPriority Priority);`
- L126 _public prototype_ `void ReadFromFileAsync(const TCHAR* ReplayPath, ICacheStoreOwner& Owner, uint64 ScratchSize = DefaultScratchSize);`
- L127 _public prototype_ `bool ReadFromFile(const TCHAR* ReplayPath, uint64 ScratchSize = DefaultScratchSize);`
- L128 _public prototype_ `bool ReadFromArchive(FArchive& ReplayAr, uint64 ScratchSize = DefaultScratchSize);`
- L129 _public prototype_ `bool ReadFromObject(FCbObjectView Object);`
- L131 _public prototype_ `void WaitForAsyncReads();`
- L135 _private member_ `TPimplPtr<FState> State;`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API DERIVEDDATACACHE_API`
- L18 _namespace_ `namespace UE`
- L18 _namespace_ `namespace DerivedData` (scope `UE`)
- L19 _namespace_ `namespace UE`
- L19 _namespace_ `namespace DerivedData` (scope `UE`)
- L20 _namespace_ `namespace UE`
- L20 _namespace_ `namespace DerivedData` (scope `UE`)
- L21 _namespace_ `namespace UE`
- L21 _namespace_ `namespace DerivedData` (scope `UE`)
- L22 _namespace_ `namespace UE`
- L22 _namespace_ `namespace DerivedData` (scope `UE`)
- L23 _namespace_ `namespace UE`
- L23 _namespace_ `namespace DerivedData` (scope `UE`)
- L25 _namespace_ `namespace UE`
- L25 _namespace_ `namespace DerivedData` (scope `UE`)
- L64 _prototype_ `TUniquePtr<ICacheReplayWriter> CreateReplayArchiveWriter(TNotNull<TUniquePtr<FArchive>> Ar, uint64 CompressionBlockSize = 256 * 1024);` (scope `UE::DerivedData`) — Create a cache replay writer that serializes into an archive. @param Ar   Archive to serialize to, and delete when the writer is deleted. @param CompressionBlockSize   Power-of-two block size or zero to disable compression.
- L71 _prototype_ `bool ReadReplayFromArchive(ICacheReplayReader& Reader, FArchive& Ar);` (scope `UE::DerivedData`) — Reads a replay from an archive that was created by CreateReplayArchiveWriter. @return True if the replay was serialized successfully, otherwise false.
- L72 _prototype_ `bool ReadReplayFromFile(ICacheReplayReader& Reader, const TCHAR* Path);` (scope `UE::DerivedData`)

### `Source/Developer/DerivedDataCache/Internal/DerivedDataCacheTraits.h` (Internal)


#### struct `UE::DerivedData::Private::TCacheRequestResponseTraits`  
`template <> struct TCacheRequestResponseTraits<FCachePutRequest>`  
_L15-23_
- L17 _public typedef_ `using FRequest = FCachePutRequest;`
- L18 _public typedef_ `using FResponse = FCachePutResponse;`
- L19 _public typedef_ `using FOnComplete = FOnCachePutComplete;`
- L20 _public member_ `constexpr static ECacheMethod Method = ECacheMethod::Put;`
- L21 _public member_ `constexpr static void (ICache::*Function)(TConstArrayView<FRequest>, IRequestOwner&, FOnComplete&&) = &ICache::Put;`
- L22 _public function_ `static const FCacheKey& GetKey(const FCachePutRequest& Request)`
- L28 _public typedef_ `using FRequest = FCacheGetRequest;`
- L29 _public typedef_ `using FResponse = FCacheGetResponse;`
- L30 _public typedef_ `using FOnComplete = FOnCacheGetComplete;`
- L31 _public member_ `constexpr static ECacheMethod Method = ECacheMethod::Get;`
- L32 _public member_ `constexpr static void (ICache::*Function)(TConstArrayView<FRequest>, IRequestOwner&, FOnComplete&&) = &ICache::Get;`
- L33 _public function_ `static const FCacheKey& GetKey(const FCacheGetRequest& Request)`
- L39 _public typedef_ `using FRequest = FCachePutValueRequest;`
- L40 _public typedef_ `using FResponse = FCachePutValueResponse;`
- L41 _public typedef_ `using FOnComplete = FOnCachePutValueComplete;`
- L42 _public member_ `constexpr static ECacheMethod Method = ECacheMethod::PutValue;`
- L43 _public member_ `constexpr static void (ICache::*Function)(TConstArrayView<FRequest>, IRequestOwner&, FOnComplete&&) = &ICache::PutValue;`
- L44 _public function_ `static const FCacheKey& GetKey(const FCachePutValueRequest& Request)`
- L50 _public typedef_ `using FRequest = FCacheGetValueRequest;`
- L51 _public typedef_ `using FResponse = FCacheGetValueResponse;`
- L52 _public typedef_ `using FOnComplete = FOnCacheGetValueComplete;`
- L53 _public member_ `constexpr static ECacheMethod Method = ECacheMethod::GetValue;`
- L54 _public member_ `constexpr static void (ICache::*Function)(TConstArrayView<FRequest>, IRequestOwner&, FOnComplete&&) = &ICache::GetValue;`
- L55 _public function_ `static const FCacheKey& GetKey(const FCacheGetValueRequest& Request)`
- L61 _public typedef_ `using FRequest = FCacheGetChunkRequest;`
- L62 _public typedef_ `using FResponse = FCacheGetChunkResponse;`
- L63 _public typedef_ `using FOnComplete = FOnCacheGetChunkComplete;`
- L64 _public member_ `constexpr static ECacheMethod Method = ECacheMethod::GetChunks;`
- L65 _public member_ `constexpr static void (ICache::*Function)(TConstArrayView<FRequest>, IRequestOwner&, FOnComplete&&) = &ICache::GetChunks;`
- L66 _public function_ `static const FCacheKey& GetKey(const FCacheGetChunkRequest& Request)`
- L77 _public function_ `static const FCacheKey& GetKey(const FCachePutResponse& Response)`
- L88 _public function_ `static const FCacheKey& GetKey(const FCacheGetResponse& Response)`
- L99 _public function_ `static const FCacheKey& GetKey(const FCachePutValueResponse& Response)`
- L110 _public function_ `static const FCacheKey& GetKey(const FCacheGetValueResponse& Response)`
- L121 _public function_ `static const FCacheKey& GetKey(const FCacheGetChunkResponse& Response)`

#### struct `UE::DerivedData::Private::TCacheRequestResponseTraits`  
`template <> struct TCacheRequestResponseTraits<FCacheGetRequest>`  
_L26-34_
- L17 _public typedef_ `using FRequest = FCachePutRequest;`
- L18 _public typedef_ `using FResponse = FCachePutResponse;`
- L19 _public typedef_ `using FOnComplete = FOnCachePutComplete;`
- L20 _public member_ `constexpr static ECacheMethod Method = ECacheMethod::Put;`
- L21 _public member_ `constexpr static void (ICache::*Function)(TConstArrayView<FRequest>, IRequestOwner&, FOnComplete&&) = &ICache::Put;`
- L22 _public function_ `static const FCacheKey& GetKey(const FCachePutRequest& Request)`
- L28 _public typedef_ `using FRequest = FCacheGetRequest;`
- L29 _public typedef_ `using FResponse = FCacheGetResponse;`
- L30 _public typedef_ `using FOnComplete = FOnCacheGetComplete;`
- L31 _public member_ `constexpr static ECacheMethod Method = ECacheMethod::Get;`
- L32 _public member_ `constexpr static void (ICache::*Function)(TConstArrayView<FRequest>, IRequestOwner&, FOnComplete&&) = &ICache::Get;`
- L33 _public function_ `static const FCacheKey& GetKey(const FCacheGetRequest& Request)`
- L39 _public typedef_ `using FRequest = FCachePutValueRequest;`
- L40 _public typedef_ `using FResponse = FCachePutValueResponse;`
- L41 _public typedef_ `using FOnComplete = FOnCachePutValueComplete;`
- L42 _public member_ `constexpr static ECacheMethod Method = ECacheMethod::PutValue;`
- L43 _public member_ `constexpr static void (ICache::*Function)(TConstArrayView<FRequest>, IRequestOwner&, FOnComplete&&) = &ICache::PutValue;`
- L44 _public function_ `static const FCacheKey& GetKey(const FCachePutValueRequest& Request)`
- L50 _public typedef_ `using FRequest = FCacheGetValueRequest;`
- L51 _public typedef_ `using FResponse = FCacheGetValueResponse;`
- L52 _public typedef_ `using FOnComplete = FOnCacheGetValueComplete;`
- L53 _public member_ `constexpr static ECacheMethod Method = ECacheMethod::GetValue;`
- L54 _public member_ `constexpr static void (ICache::*Function)(TConstArrayView<FRequest>, IRequestOwner&, FOnComplete&&) = &ICache::GetValue;`
- L55 _public function_ `static const FCacheKey& GetKey(const FCacheGetValueRequest& Request)`
- L61 _public typedef_ `using FRequest = FCacheGetChunkRequest;`
- L62 _public typedef_ `using FResponse = FCacheGetChunkResponse;`
- L63 _public typedef_ `using FOnComplete = FOnCacheGetChunkComplete;`
- L64 _public member_ `constexpr static ECacheMethod Method = ECacheMethod::GetChunks;`
- L65 _public member_ `constexpr static void (ICache::*Function)(TConstArrayView<FRequest>, IRequestOwner&, FOnComplete&&) = &ICache::GetChunks;`
- L66 _public function_ `static const FCacheKey& GetKey(const FCacheGetChunkRequest& Request)`
- L77 _public function_ `static const FCacheKey& GetKey(const FCachePutResponse& Response)`
- L88 _public function_ `static const FCacheKey& GetKey(const FCacheGetResponse& Response)`
- L99 _public function_ `static const FCacheKey& GetKey(const FCachePutValueResponse& Response)`
- L110 _public function_ `static const FCacheKey& GetKey(const FCacheGetValueResponse& Response)`
- L121 _public function_ `static const FCacheKey& GetKey(const FCacheGetChunkResponse& Response)`

#### struct `UE::DerivedData::Private::TCacheRequestResponseTraits`  
`template <> struct TCacheRequestResponseTraits<FCachePutValueRequest>`  
_L37-45_
- L17 _public typedef_ `using FRequest = FCachePutRequest;`
- L18 _public typedef_ `using FResponse = FCachePutResponse;`
- L19 _public typedef_ `using FOnComplete = FOnCachePutComplete;`
- L20 _public member_ `constexpr static ECacheMethod Method = ECacheMethod::Put;`
- L21 _public member_ `constexpr static void (ICache::*Function)(TConstArrayView<FRequest>, IRequestOwner&, FOnComplete&&) = &ICache::Put;`
- L22 _public function_ `static const FCacheKey& GetKey(const FCachePutRequest& Request)`
- L28 _public typedef_ `using FRequest = FCacheGetRequest;`
- L29 _public typedef_ `using FResponse = FCacheGetResponse;`
- L30 _public typedef_ `using FOnComplete = FOnCacheGetComplete;`
- L31 _public member_ `constexpr static ECacheMethod Method = ECacheMethod::Get;`
- L32 _public member_ `constexpr static void (ICache::*Function)(TConstArrayView<FRequest>, IRequestOwner&, FOnComplete&&) = &ICache::Get;`
- L33 _public function_ `static const FCacheKey& GetKey(const FCacheGetRequest& Request)`
- L39 _public typedef_ `using FRequest = FCachePutValueRequest;`
- L40 _public typedef_ `using FResponse = FCachePutValueResponse;`
- L41 _public typedef_ `using FOnComplete = FOnCachePutValueComplete;`
- L42 _public member_ `constexpr static ECacheMethod Method = ECacheMethod::PutValue;`
- L43 _public member_ `constexpr static void (ICache::*Function)(TConstArrayView<FRequest>, IRequestOwner&, FOnComplete&&) = &ICache::PutValue;`
- L44 _public function_ `static const FCacheKey& GetKey(const FCachePutValueRequest& Request)`
- L50 _public typedef_ `using FRequest = FCacheGetValueRequest;`
- L51 _public typedef_ `using FResponse = FCacheGetValueResponse;`
- L52 _public typedef_ `using FOnComplete = FOnCacheGetValueComplete;`
- L53 _public member_ `constexpr static ECacheMethod Method = ECacheMethod::GetValue;`
- L54 _public member_ `constexpr static void (ICache::*Function)(TConstArrayView<FRequest>, IRequestOwner&, FOnComplete&&) = &ICache::GetValue;`
- L55 _public function_ `static const FCacheKey& GetKey(const FCacheGetValueRequest& Request)`
- L61 _public typedef_ `using FRequest = FCacheGetChunkRequest;`
- L62 _public typedef_ `using FResponse = FCacheGetChunkResponse;`
- L63 _public typedef_ `using FOnComplete = FOnCacheGetChunkComplete;`
- L64 _public member_ `constexpr static ECacheMethod Method = ECacheMethod::GetChunks;`
- L65 _public member_ `constexpr static void (ICache::*Function)(TConstArrayView<FRequest>, IRequestOwner&, FOnComplete&&) = &ICache::GetChunks;`
- L66 _public function_ `static const FCacheKey& GetKey(const FCacheGetChunkRequest& Request)`
- L77 _public function_ `static const FCacheKey& GetKey(const FCachePutResponse& Response)`
- L88 _public function_ `static const FCacheKey& GetKey(const FCacheGetResponse& Response)`
- L99 _public function_ `static const FCacheKey& GetKey(const FCachePutValueResponse& Response)`
- L110 _public function_ `static const FCacheKey& GetKey(const FCacheGetValueResponse& Response)`
- L121 _public function_ `static const FCacheKey& GetKey(const FCacheGetChunkResponse& Response)`

#### struct `UE::DerivedData::Private::TCacheRequestResponseTraits`  
`template <> struct TCacheRequestResponseTraits<FCacheGetValueRequest>`  
_L48-56_
- L17 _public typedef_ `using FRequest = FCachePutRequest;`
- L18 _public typedef_ `using FResponse = FCachePutResponse;`
- L19 _public typedef_ `using FOnComplete = FOnCachePutComplete;`
- L20 _public member_ `constexpr static ECacheMethod Method = ECacheMethod::Put;`
- L21 _public member_ `constexpr static void (ICache::*Function)(TConstArrayView<FRequest>, IRequestOwner&, FOnComplete&&) = &ICache::Put;`
- L22 _public function_ `static const FCacheKey& GetKey(const FCachePutRequest& Request)`
- L28 _public typedef_ `using FRequest = FCacheGetRequest;`
- L29 _public typedef_ `using FResponse = FCacheGetResponse;`
- L30 _public typedef_ `using FOnComplete = FOnCacheGetComplete;`
- L31 _public member_ `constexpr static ECacheMethod Method = ECacheMethod::Get;`
- L32 _public member_ `constexpr static void (ICache::*Function)(TConstArrayView<FRequest>, IRequestOwner&, FOnComplete&&) = &ICache::Get;`
- L33 _public function_ `static const FCacheKey& GetKey(const FCacheGetRequest& Request)`
- L39 _public typedef_ `using FRequest = FCachePutValueRequest;`
- L40 _public typedef_ `using FResponse = FCachePutValueResponse;`
- L41 _public typedef_ `using FOnComplete = FOnCachePutValueComplete;`
- L42 _public member_ `constexpr static ECacheMethod Method = ECacheMethod::PutValue;`
- L43 _public member_ `constexpr static void (ICache::*Function)(TConstArrayView<FRequest>, IRequestOwner&, FOnComplete&&) = &ICache::PutValue;`
- L44 _public function_ `static const FCacheKey& GetKey(const FCachePutValueRequest& Request)`
- L50 _public typedef_ `using FRequest = FCacheGetValueRequest;`
- L51 _public typedef_ `using FResponse = FCacheGetValueResponse;`
- L52 _public typedef_ `using FOnComplete = FOnCacheGetValueComplete;`
- L53 _public member_ `constexpr static ECacheMethod Method = ECacheMethod::GetValue;`
- L54 _public member_ `constexpr static void (ICache::*Function)(TConstArrayView<FRequest>, IRequestOwner&, FOnComplete&&) = &ICache::GetValue;`
- L55 _public function_ `static const FCacheKey& GetKey(const FCacheGetValueRequest& Request)`
- L61 _public typedef_ `using FRequest = FCacheGetChunkRequest;`
- L62 _public typedef_ `using FResponse = FCacheGetChunkResponse;`
- L63 _public typedef_ `using FOnComplete = FOnCacheGetChunkComplete;`
- L64 _public member_ `constexpr static ECacheMethod Method = ECacheMethod::GetChunks;`
- L65 _public member_ `constexpr static void (ICache::*Function)(TConstArrayView<FRequest>, IRequestOwner&, FOnComplete&&) = &ICache::GetChunks;`
- L66 _public function_ `static const FCacheKey& GetKey(const FCacheGetChunkRequest& Request)`
- L77 _public function_ `static const FCacheKey& GetKey(const FCachePutResponse& Response)`
- L88 _public function_ `static const FCacheKey& GetKey(const FCacheGetResponse& Response)`
- L99 _public function_ `static const FCacheKey& GetKey(const FCachePutValueResponse& Response)`
- L110 _public function_ `static const FCacheKey& GetKey(const FCacheGetValueResponse& Response)`
- L121 _public function_ `static const FCacheKey& GetKey(const FCacheGetChunkResponse& Response)`

#### struct `UE::DerivedData::Private::TCacheRequestResponseTraits`  
`template <> struct TCacheRequestResponseTraits<FCacheGetChunkRequest>`  
_L59-67_
- L17 _public typedef_ `using FRequest = FCachePutRequest;`
- L18 _public typedef_ `using FResponse = FCachePutResponse;`
- L19 _public typedef_ `using FOnComplete = FOnCachePutComplete;`
- L20 _public member_ `constexpr static ECacheMethod Method = ECacheMethod::Put;`
- L21 _public member_ `constexpr static void (ICache::*Function)(TConstArrayView<FRequest>, IRequestOwner&, FOnComplete&&) = &ICache::Put;`
- L22 _public function_ `static const FCacheKey& GetKey(const FCachePutRequest& Request)`
- L28 _public typedef_ `using FRequest = FCacheGetRequest;`
- L29 _public typedef_ `using FResponse = FCacheGetResponse;`
- L30 _public typedef_ `using FOnComplete = FOnCacheGetComplete;`
- L31 _public member_ `constexpr static ECacheMethod Method = ECacheMethod::Get;`
- L32 _public member_ `constexpr static void (ICache::*Function)(TConstArrayView<FRequest>, IRequestOwner&, FOnComplete&&) = &ICache::Get;`
- L33 _public function_ `static const FCacheKey& GetKey(const FCacheGetRequest& Request)`
- L39 _public typedef_ `using FRequest = FCachePutValueRequest;`
- L40 _public typedef_ `using FResponse = FCachePutValueResponse;`
- L41 _public typedef_ `using FOnComplete = FOnCachePutValueComplete;`
- L42 _public member_ `constexpr static ECacheMethod Method = ECacheMethod::PutValue;`
- L43 _public member_ `constexpr static void (ICache::*Function)(TConstArrayView<FRequest>, IRequestOwner&, FOnComplete&&) = &ICache::PutValue;`
- L44 _public function_ `static const FCacheKey& GetKey(const FCachePutValueRequest& Request)`
- L50 _public typedef_ `using FRequest = FCacheGetValueRequest;`
- L51 _public typedef_ `using FResponse = FCacheGetValueResponse;`
- L52 _public typedef_ `using FOnComplete = FOnCacheGetValueComplete;`
- L53 _public member_ `constexpr static ECacheMethod Method = ECacheMethod::GetValue;`
- L54 _public member_ `constexpr static void (ICache::*Function)(TConstArrayView<FRequest>, IRequestOwner&, FOnComplete&&) = &ICache::GetValue;`
- L55 _public function_ `static const FCacheKey& GetKey(const FCacheGetValueRequest& Request)`
- L61 _public typedef_ `using FRequest = FCacheGetChunkRequest;`
- L62 _public typedef_ `using FResponse = FCacheGetChunkResponse;`
- L63 _public typedef_ `using FOnComplete = FOnCacheGetChunkComplete;`
- L64 _public member_ `constexpr static ECacheMethod Method = ECacheMethod::GetChunks;`
- L65 _public member_ `constexpr static void (ICache::*Function)(TConstArrayView<FRequest>, IRequestOwner&, FOnComplete&&) = &ICache::GetChunks;`
- L66 _public function_ `static const FCacheKey& GetKey(const FCacheGetChunkRequest& Request)`
- L77 _public function_ `static const FCacheKey& GetKey(const FCachePutResponse& Response)`
- L88 _public function_ `static const FCacheKey& GetKey(const FCacheGetResponse& Response)`
- L99 _public function_ `static const FCacheKey& GetKey(const FCachePutValueResponse& Response)`
- L110 _public function_ `static const FCacheKey& GetKey(const FCacheGetValueResponse& Response)`
- L121 _public function_ `static const FCacheKey& GetKey(const FCacheGetChunkResponse& Response)`

#### struct `UE::DerivedData::Private::TCacheRequestResponseTraits`  
`template <> struct TCacheRequestResponseTraits<FCachePutResponse>`  
_L70-78_
- L17 _public typedef_ `using FRequest = FCachePutRequest;`
- L18 _public typedef_ `using FResponse = FCachePutResponse;`
- L19 _public typedef_ `using FOnComplete = FOnCachePutComplete;`
- L20 _public member_ `constexpr static ECacheMethod Method = ECacheMethod::Put;`
- L21 _public member_ `constexpr static void (ICache::*Function)(TConstArrayView<FRequest>, IRequestOwner&, FOnComplete&&) = &ICache::Put;`
- L22 _public function_ `static const FCacheKey& GetKey(const FCachePutRequest& Request)`
- L28 _public typedef_ `using FRequest = FCacheGetRequest;`
- L29 _public typedef_ `using FResponse = FCacheGetResponse;`
- L30 _public typedef_ `using FOnComplete = FOnCacheGetComplete;`
- L31 _public member_ `constexpr static ECacheMethod Method = ECacheMethod::Get;`
- L32 _public member_ `constexpr static void (ICache::*Function)(TConstArrayView<FRequest>, IRequestOwner&, FOnComplete&&) = &ICache::Get;`
- L33 _public function_ `static const FCacheKey& GetKey(const FCacheGetRequest& Request)`
- L39 _public typedef_ `using FRequest = FCachePutValueRequest;`
- L40 _public typedef_ `using FResponse = FCachePutValueResponse;`
- L41 _public typedef_ `using FOnComplete = FOnCachePutValueComplete;`
- L42 _public member_ `constexpr static ECacheMethod Method = ECacheMethod::PutValue;`
- L43 _public member_ `constexpr static void (ICache::*Function)(TConstArrayView<FRequest>, IRequestOwner&, FOnComplete&&) = &ICache::PutValue;`
- L44 _public function_ `static const FCacheKey& GetKey(const FCachePutValueRequest& Request)`
- L50 _public typedef_ `using FRequest = FCacheGetValueRequest;`
- L51 _public typedef_ `using FResponse = FCacheGetValueResponse;`
- L52 _public typedef_ `using FOnComplete = FOnCacheGetValueComplete;`
- L53 _public member_ `constexpr static ECacheMethod Method = ECacheMethod::GetValue;`
- L54 _public member_ `constexpr static void (ICache::*Function)(TConstArrayView<FRequest>, IRequestOwner&, FOnComplete&&) = &ICache::GetValue;`
- L55 _public function_ `static const FCacheKey& GetKey(const FCacheGetValueRequest& Request)`
- L61 _public typedef_ `using FRequest = FCacheGetChunkRequest;`
- L62 _public typedef_ `using FResponse = FCacheGetChunkResponse;`
- L63 _public typedef_ `using FOnComplete = FOnCacheGetChunkComplete;`
- L64 _public member_ `constexpr static ECacheMethod Method = ECacheMethod::GetChunks;`
- L65 _public member_ `constexpr static void (ICache::*Function)(TConstArrayView<FRequest>, IRequestOwner&, FOnComplete&&) = &ICache::GetChunks;`
- L66 _public function_ `static const FCacheKey& GetKey(const FCacheGetChunkRequest& Request)`
- L77 _public function_ `static const FCacheKey& GetKey(const FCachePutResponse& Response)`
- L88 _public function_ `static const FCacheKey& GetKey(const FCacheGetResponse& Response)`
- L99 _public function_ `static const FCacheKey& GetKey(const FCachePutValueResponse& Response)`
- L110 _public function_ `static const FCacheKey& GetKey(const FCacheGetValueResponse& Response)`
- L121 _public function_ `static const FCacheKey& GetKey(const FCacheGetChunkResponse& Response)`

#### struct `UE::DerivedData::Private::TCacheRequestResponseTraits`  
`template <> struct TCacheRequestResponseTraits<FCacheGetResponse>`  
_L81-89_
- L17 _public typedef_ `using FRequest = FCachePutRequest;`
- L18 _public typedef_ `using FResponse = FCachePutResponse;`
- L19 _public typedef_ `using FOnComplete = FOnCachePutComplete;`
- L20 _public member_ `constexpr static ECacheMethod Method = ECacheMethod::Put;`
- L21 _public member_ `constexpr static void (ICache::*Function)(TConstArrayView<FRequest>, IRequestOwner&, FOnComplete&&) = &ICache::Put;`
- L22 _public function_ `static const FCacheKey& GetKey(const FCachePutRequest& Request)`
- L28 _public typedef_ `using FRequest = FCacheGetRequest;`
- L29 _public typedef_ `using FResponse = FCacheGetResponse;`
- L30 _public typedef_ `using FOnComplete = FOnCacheGetComplete;`
- L31 _public member_ `constexpr static ECacheMethod Method = ECacheMethod::Get;`
- L32 _public member_ `constexpr static void (ICache::*Function)(TConstArrayView<FRequest>, IRequestOwner&, FOnComplete&&) = &ICache::Get;`
- L33 _public function_ `static const FCacheKey& GetKey(const FCacheGetRequest& Request)`
- L39 _public typedef_ `using FRequest = FCachePutValueRequest;`
- L40 _public typedef_ `using FResponse = FCachePutValueResponse;`
- L41 _public typedef_ `using FOnComplete = FOnCachePutValueComplete;`
- L42 _public member_ `constexpr static ECacheMethod Method = ECacheMethod::PutValue;`
- L43 _public member_ `constexpr static void (ICache::*Function)(TConstArrayView<FRequest>, IRequestOwner&, FOnComplete&&) = &ICache::PutValue;`
- L44 _public function_ `static const FCacheKey& GetKey(const FCachePutValueRequest& Request)`
- L50 _public typedef_ `using FRequest = FCacheGetValueRequest;`
- L51 _public typedef_ `using FResponse = FCacheGetValueResponse;`
- L52 _public typedef_ `using FOnComplete = FOnCacheGetValueComplete;`
- L53 _public member_ `constexpr static ECacheMethod Method = ECacheMethod::GetValue;`
- L54 _public member_ `constexpr static void (ICache::*Function)(TConstArrayView<FRequest>, IRequestOwner&, FOnComplete&&) = &ICache::GetValue;`
- L55 _public function_ `static const FCacheKey& GetKey(const FCacheGetValueRequest& Request)`
- L61 _public typedef_ `using FRequest = FCacheGetChunkRequest;`
- L62 _public typedef_ `using FResponse = FCacheGetChunkResponse;`
- L63 _public typedef_ `using FOnComplete = FOnCacheGetChunkComplete;`
- L64 _public member_ `constexpr static ECacheMethod Method = ECacheMethod::GetChunks;`
- L65 _public member_ `constexpr static void (ICache::*Function)(TConstArrayView<FRequest>, IRequestOwner&, FOnComplete&&) = &ICache::GetChunks;`
- L66 _public function_ `static const FCacheKey& GetKey(const FCacheGetChunkRequest& Request)`
- L77 _public function_ `static const FCacheKey& GetKey(const FCachePutResponse& Response)`
- L88 _public function_ `static const FCacheKey& GetKey(const FCacheGetResponse& Response)`
- L99 _public function_ `static const FCacheKey& GetKey(const FCachePutValueResponse& Response)`
- L110 _public function_ `static const FCacheKey& GetKey(const FCacheGetValueResponse& Response)`
- L121 _public function_ `static const FCacheKey& GetKey(const FCacheGetChunkResponse& Response)`

#### struct `UE::DerivedData::Private::TCacheRequestResponseTraits`  
`template <> struct TCacheRequestResponseTraits<FCachePutValueResponse>`  
_L92-100_
- L17 _public typedef_ `using FRequest = FCachePutRequest;`
- L18 _public typedef_ `using FResponse = FCachePutResponse;`
- L19 _public typedef_ `using FOnComplete = FOnCachePutComplete;`
- L20 _public member_ `constexpr static ECacheMethod Method = ECacheMethod::Put;`
- L21 _public member_ `constexpr static void (ICache::*Function)(TConstArrayView<FRequest>, IRequestOwner&, FOnComplete&&) = &ICache::Put;`
- L22 _public function_ `static const FCacheKey& GetKey(const FCachePutRequest& Request)`
- L28 _public typedef_ `using FRequest = FCacheGetRequest;`
- L29 _public typedef_ `using FResponse = FCacheGetResponse;`
- L30 _public typedef_ `using FOnComplete = FOnCacheGetComplete;`
- L31 _public member_ `constexpr static ECacheMethod Method = ECacheMethod::Get;`
- L32 _public member_ `constexpr static void (ICache::*Function)(TConstArrayView<FRequest>, IRequestOwner&, FOnComplete&&) = &ICache::Get;`
- L33 _public function_ `static const FCacheKey& GetKey(const FCacheGetRequest& Request)`
- L39 _public typedef_ `using FRequest = FCachePutValueRequest;`
- L40 _public typedef_ `using FResponse = FCachePutValueResponse;`
- L41 _public typedef_ `using FOnComplete = FOnCachePutValueComplete;`
- L42 _public member_ `constexpr static ECacheMethod Method = ECacheMethod::PutValue;`
- L43 _public member_ `constexpr static void (ICache::*Function)(TConstArrayView<FRequest>, IRequestOwner&, FOnComplete&&) = &ICache::PutValue;`
- L44 _public function_ `static const FCacheKey& GetKey(const FCachePutValueRequest& Request)`
- L50 _public typedef_ `using FRequest = FCacheGetValueRequest;`
- L51 _public typedef_ `using FResponse = FCacheGetValueResponse;`
- L52 _public typedef_ `using FOnComplete = FOnCacheGetValueComplete;`
- L53 _public member_ `constexpr static ECacheMethod Method = ECacheMethod::GetValue;`
- L54 _public member_ `constexpr static void (ICache::*Function)(TConstArrayView<FRequest>, IRequestOwner&, FOnComplete&&) = &ICache::GetValue;`
- L55 _public function_ `static const FCacheKey& GetKey(const FCacheGetValueRequest& Request)`
- L61 _public typedef_ `using FRequest = FCacheGetChunkRequest;`
- L62 _public typedef_ `using FResponse = FCacheGetChunkResponse;`
- L63 _public typedef_ `using FOnComplete = FOnCacheGetChunkComplete;`
- L64 _public member_ `constexpr static ECacheMethod Method = ECacheMethod::GetChunks;`
- L65 _public member_ `constexpr static void (ICache::*Function)(TConstArrayView<FRequest>, IRequestOwner&, FOnComplete&&) = &ICache::GetChunks;`
- L66 _public function_ `static const FCacheKey& GetKey(const FCacheGetChunkRequest& Request)`
- L77 _public function_ `static const FCacheKey& GetKey(const FCachePutResponse& Response)`
- L88 _public function_ `static const FCacheKey& GetKey(const FCacheGetResponse& Response)`
- L99 _public function_ `static const FCacheKey& GetKey(const FCachePutValueResponse& Response)`
- L110 _public function_ `static const FCacheKey& GetKey(const FCacheGetValueResponse& Response)`
- L121 _public function_ `static const FCacheKey& GetKey(const FCacheGetChunkResponse& Response)`

#### struct `UE::DerivedData::Private::TCacheRequestResponseTraits`  
`template <> struct TCacheRequestResponseTraits<FCacheGetValueResponse>`  
_L103-111_
- L17 _public typedef_ `using FRequest = FCachePutRequest;`
- L18 _public typedef_ `using FResponse = FCachePutResponse;`
- L19 _public typedef_ `using FOnComplete = FOnCachePutComplete;`
- L20 _public member_ `constexpr static ECacheMethod Method = ECacheMethod::Put;`
- L21 _public member_ `constexpr static void (ICache::*Function)(TConstArrayView<FRequest>, IRequestOwner&, FOnComplete&&) = &ICache::Put;`
- L22 _public function_ `static const FCacheKey& GetKey(const FCachePutRequest& Request)`
- L28 _public typedef_ `using FRequest = FCacheGetRequest;`
- L29 _public typedef_ `using FResponse = FCacheGetResponse;`
- L30 _public typedef_ `using FOnComplete = FOnCacheGetComplete;`
- L31 _public member_ `constexpr static ECacheMethod Method = ECacheMethod::Get;`
- L32 _public member_ `constexpr static void (ICache::*Function)(TConstArrayView<FRequest>, IRequestOwner&, FOnComplete&&) = &ICache::Get;`
- L33 _public function_ `static const FCacheKey& GetKey(const FCacheGetRequest& Request)`
- L39 _public typedef_ `using FRequest = FCachePutValueRequest;`
- L40 _public typedef_ `using FResponse = FCachePutValueResponse;`
- L41 _public typedef_ `using FOnComplete = FOnCachePutValueComplete;`
- L42 _public member_ `constexpr static ECacheMethod Method = ECacheMethod::PutValue;`
- L43 _public member_ `constexpr static void (ICache::*Function)(TConstArrayView<FRequest>, IRequestOwner&, FOnComplete&&) = &ICache::PutValue;`
- L44 _public function_ `static const FCacheKey& GetKey(const FCachePutValueRequest& Request)`
- L50 _public typedef_ `using FRequest = FCacheGetValueRequest;`
- L51 _public typedef_ `using FResponse = FCacheGetValueResponse;`
- L52 _public typedef_ `using FOnComplete = FOnCacheGetValueComplete;`
- L53 _public member_ `constexpr static ECacheMethod Method = ECacheMethod::GetValue;`
- L54 _public member_ `constexpr static void (ICache::*Function)(TConstArrayView<FRequest>, IRequestOwner&, FOnComplete&&) = &ICache::GetValue;`
- L55 _public function_ `static const FCacheKey& GetKey(const FCacheGetValueRequest& Request)`
- L61 _public typedef_ `using FRequest = FCacheGetChunkRequest;`
- L62 _public typedef_ `using FResponse = FCacheGetChunkResponse;`
- L63 _public typedef_ `using FOnComplete = FOnCacheGetChunkComplete;`
- L64 _public member_ `constexpr static ECacheMethod Method = ECacheMethod::GetChunks;`
- L65 _public member_ `constexpr static void (ICache::*Function)(TConstArrayView<FRequest>, IRequestOwner&, FOnComplete&&) = &ICache::GetChunks;`
- L66 _public function_ `static const FCacheKey& GetKey(const FCacheGetChunkRequest& Request)`
- L77 _public function_ `static const FCacheKey& GetKey(const FCachePutResponse& Response)`
- L88 _public function_ `static const FCacheKey& GetKey(const FCacheGetResponse& Response)`
- L99 _public function_ `static const FCacheKey& GetKey(const FCachePutValueResponse& Response)`
- L110 _public function_ `static const FCacheKey& GetKey(const FCacheGetValueResponse& Response)`
- L121 _public function_ `static const FCacheKey& GetKey(const FCacheGetChunkResponse& Response)`

#### struct `UE::DerivedData::Private::TCacheRequestResponseTraits`  
`template <> struct TCacheRequestResponseTraits<FCacheGetChunkResponse>`  
_L114-122_
- L17 _public typedef_ `using FRequest = FCachePutRequest;`
- L18 _public typedef_ `using FResponse = FCachePutResponse;`
- L19 _public typedef_ `using FOnComplete = FOnCachePutComplete;`
- L20 _public member_ `constexpr static ECacheMethod Method = ECacheMethod::Put;`
- L21 _public member_ `constexpr static void (ICache::*Function)(TConstArrayView<FRequest>, IRequestOwner&, FOnComplete&&) = &ICache::Put;`
- L22 _public function_ `static const FCacheKey& GetKey(const FCachePutRequest& Request)`
- L28 _public typedef_ `using FRequest = FCacheGetRequest;`
- L29 _public typedef_ `using FResponse = FCacheGetResponse;`
- L30 _public typedef_ `using FOnComplete = FOnCacheGetComplete;`
- L31 _public member_ `constexpr static ECacheMethod Method = ECacheMethod::Get;`
- L32 _public member_ `constexpr static void (ICache::*Function)(TConstArrayView<FRequest>, IRequestOwner&, FOnComplete&&) = &ICache::Get;`
- L33 _public function_ `static const FCacheKey& GetKey(const FCacheGetRequest& Request)`
- L39 _public typedef_ `using FRequest = FCachePutValueRequest;`
- L40 _public typedef_ `using FResponse = FCachePutValueResponse;`
- L41 _public typedef_ `using FOnComplete = FOnCachePutValueComplete;`
- L42 _public member_ `constexpr static ECacheMethod Method = ECacheMethod::PutValue;`
- L43 _public member_ `constexpr static void (ICache::*Function)(TConstArrayView<FRequest>, IRequestOwner&, FOnComplete&&) = &ICache::PutValue;`
- L44 _public function_ `static const FCacheKey& GetKey(const FCachePutValueRequest& Request)`
- L50 _public typedef_ `using FRequest = FCacheGetValueRequest;`
- L51 _public typedef_ `using FResponse = FCacheGetValueResponse;`
- L52 _public typedef_ `using FOnComplete = FOnCacheGetValueComplete;`
- L53 _public member_ `constexpr static ECacheMethod Method = ECacheMethod::GetValue;`
- L54 _public member_ `constexpr static void (ICache::*Function)(TConstArrayView<FRequest>, IRequestOwner&, FOnComplete&&) = &ICache::GetValue;`
- L55 _public function_ `static const FCacheKey& GetKey(const FCacheGetValueRequest& Request)`
- L61 _public typedef_ `using FRequest = FCacheGetChunkRequest;`
- L62 _public typedef_ `using FResponse = FCacheGetChunkResponse;`
- L63 _public typedef_ `using FOnComplete = FOnCacheGetChunkComplete;`
- L64 _public member_ `constexpr static ECacheMethod Method = ECacheMethod::GetChunks;`
- L65 _public member_ `constexpr static void (ICache::*Function)(TConstArrayView<FRequest>, IRequestOwner&, FOnComplete&&) = &ICache::GetChunks;`
- L66 _public function_ `static const FCacheKey& GetKey(const FCacheGetChunkRequest& Request)`
- L77 _public function_ `static const FCacheKey& GetKey(const FCachePutResponse& Response)`
- L88 _public function_ `static const FCacheKey& GetKey(const FCacheGetResponse& Response)`
- L99 _public function_ `static const FCacheKey& GetKey(const FCachePutValueResponse& Response)`
- L110 _public function_ `static const FCacheKey& GetKey(const FCacheGetValueResponse& Response)`
- L121 _public function_ `static const FCacheKey& GetKey(const FCacheGetChunkResponse& Response)`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace DerivedData` (scope `UE`)
- L8 _namespace_ `namespace Private` (scope `UE::DerivedData`)
- L126 _namespace_ `namespace UE`
- L126 _namespace_ `namespace DerivedData` (scope `UE`)
- L130 _typedef_ `template <typename RequestOrResponseType> using TCacheRequestFor = typename Private::TCacheRequestResponseTraits<RequestOrResponseType>::FRequest;` (scope `UE::DerivedData`) — Alias for the request type corresponding to the request/response type.
- L133 _typedef_ `template <typename RequestOrResponseType> using TCacheResponseFor = typename Private::TCacheRequestResponseTraits<RequestOrResponseType>::FResponse;` (scope `UE::DerivedData`) — Alias for the response type corresponding to the request/response type.
- L136 _typedef_ `template <typename RequestOrResponseType> using TCacheOnCompleteFor = typename Private::TCacheRequestResponseTraits<RequestOrResponseType>::FOnComplete;` (scope `UE::DerivedData`) — Alias for the completion callback type corresponding to the request/response type.
- L139 _variable_ `template <typename RequestOrResponseType> inline constexpr auto CacheMethodFor = Private::TCacheRequestResponseTraits<RequestOrResponseType>::Method;` (scope `UE::DerivedData`) — Alias for the cache method corresponding to the request/response type.
- L142 _variable_ `template <typename RequestOrResponseType> inline constexpr auto CacheFunctionFor = Private::TCacheRequestResponseTraits<RequestOrResponseType>::Function;` (scope `UE::DerivedData`) — Alias for the cache function corresponding to the request/response type.
- L145 _function_ `template <typename RequestOrResponseType> inline auto GetCacheKey(const RequestOrResponseType& Request) -> decltype(Private::TCacheRequestResponseTraits<RequestOrResponseType>::GetKey(Request))` (scope `UE::DerivedData`)

### `Source/Developer/DerivedDataCache/Internal/DerivedDataConfig.h` (Internal)


#### class `UE::DerivedData::Config::FConfigIterator`  
`class FConfigIterator`  
_L22-41_
- desc: Iterates fields of a config string in the form (Name1=Value1, Name2=Value2, Name3=(X=1, Y=2, Z=3), ValueOnly). Names must contain only [A-Za-z0-9_]. Strings with spaces or quotes must be quoted and escaped: (Description="A \"real\" description...") Values that are a name and config are explicitly supported: (Node=Point(X=1, Y=2, Z=3), ValueOnly(Name="Test"))
- L25 _public prototype_ `explicit FConfigIterator(FStringView Config);`
- L27 _public prototype_ `FConfigIterator& operator++();`
- L29 _public function_ `inline bool HasError() const`
- L30 _public function_ `inline explicit operator bool() const`
- L31 _public function_ `inline const FStringView& GetName() const`
- L32 _public function_ `inline const FStringView& GetValue() const`
- L35 _private member_ `FStringView Tail;`
- L36 _private member_ `FStringView Name;`
- L37 _private member_ `FStringView Value;`
- L38 _private member_ `bool bAtEnd = false;`
- L39 _private member_ `bool bError = false;`
- L40 _private member_ `bool bLastField = false;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API DERIVEDDATACACHE_API`
- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace DerivedData` (scope `UE`)
- L12 _namespace_ `namespace Config` (scope `UE::DerivedData`)
- L50 _prototype_ `[[nodiscard]] FStringView ParseQuotedString(FStringView String, FStringBuilderBase& OutScratch);` (scope `UE::DerivedData::Config`) — Returns the possibly-quoted string, with quotes removed and escapes processed. @param String       View of a string that may be surrounded by quotes and may contain escaped characters. @param OutScratch   Builder to use as scratch space when processing escape sequences. @return A view into String if there are no escapes, and a view into OutScratch otherwise.
- L53 _prototype_ `[[nodiscard]] bool FindFirstFieldValue(FStringView Config, FStringView Name, FStringView& OutValue);` (scope `UE::DerivedData::Config`) — Finds the first field in Config matching Name case-insensitively.
- L56 _prototype_ `[[nodiscard]] bool VisitFieldValues(FStringView Config, FStringView Name, TFunctionWithContext<void (FStringView)> OnValue);` (scope `UE::DerivedData::Config`) — Visits every field in Config matching Name case-insensitively.
- L59 _prototype_ `[[nodiscard]] bool TrySplitNameAndConfig(FStringView Value, FStringView& OutName, FStringView& OutConfig);` (scope `UE::DerivedData::Config`) — Splits "Name(Config)" to ("Name", "(Config)"), "Name" to ("Name", ""), "(Config)" to ("", "(Config)").
- L62 _prototype_ `void AppendConfig(FStringBuilderBase& OutConfig, FStringView Name, FStringView Value);` (scope `UE::DerivedData::Config`) — Appends "Name=Value", or "Name" if Value is empty, with extra whitespace removed from any valid nested objects.
- L66 _namespace_ `namespace UE`
- L66 _namespace_ `namespace DerivedData` (scope `UE`)
- L80 _prototype_ `bool TryFindCacheGraphConfig(FStringView GraphNameOrConfig, FStringBuilderBase& OutConfig);` (scope `UE::DerivedData`) — Finds the configuration for a cache graph. Written in the normalized format "(StoreName1, StoreName2, StoreName3)". Store remapping and inline configuration is stripped from the output. Example: "(StoreName1=OtherName(Key=Value))" outputs "(StoreName1)". @param GraphNameOrConfig   Name of the cache graph, which is compared case-insensitively, or a graph configuration. @param OutConfig           Appended with the configuration for the cache graph if it is found. @return True if the configuration was found, otherwise false.
- L98 _prototype_ `bool TryFindCacheStoreConfig(FStringView StoreName, FStringView GraphNameOrConfig, FStringBuilderBase& OutConfig);` (scope `UE::DerivedData`) — Finds the configuration for a cache store, optionally within a specific cache graph. The optional cache graph may contain configuration overrides for the cache store. The configuration is appended to OutConfig from most-derived to least-derived, such that FParse::Value() will see override values before base values. Written in the normalized format "(Type=Value, Key1=Value1, Key2=Value2, Value3)". Store inheritance is stripped from the output. Example: "(Base=OtherStore, Key1 = Value1, Value2)" outputs "(Key1=Value1, Value2, KeyFromOtherStore=OtherValue)". @param StoreName           Name of the cache store, which is compared case-insensitively. @param GraphNameOrConfig   Name of the cache graph, which is compared case-insensitively, or a graph configuration. @param OutConfig           Appended with the configuration for the cache store if it is found. @return True if the configuration was found, otherwise false.

### `Source/Developer/DerivedDataCache/Private/BatchView.h` (Private)


#### enum `EBatchView`  
`enum class EBatchView`  
_L10-16_
- L13 _public enumerator_ `Continue` — Add the item to the previous batch. If no previous batch, treated the same as NewBatch.
- L15 _public enumerator_ `NewBatch` — End the previous batch (if it exists), start a new batch, add the item to the new batch.

#### class `TBatchView`  
`template <typename T> class TBatchView`  
_L23-90_
- desc: Takes a list of items and a ShouldAddToBatch function and provides a ranged-for over the set of batches created from the list.
- L26 _public prototype_ `TBatchView() = default;`
- L35 _public function_ `template <typename ShouldAddToBatchFunc> TBatchView(TArrayView<T> InItems, ShouldAddToBatchFunc&& ShouldAddToBatch) : Items(InItems)` — Constructor from list of elements and a function that is called on each element to decide whether to add the element to the current batch. EBatchView ShouldAddToBatch(const T& Item);
- L78 _public function_ `TIterator begin() const`
- L82 _public function_ `TIterator end() const`
- L88 _private member_ `TArrayView<T> Items;`
- L89 _private member_ `TArray<int32> BatchStarts;`

#### struct `TBatchView::TIterator`  
`struct TIterator`  
_L53-77_
- L55 _public function_ `TIterator(const TBatchView& InBatchList, bool bEnd) : BatchList(InBatchList) , BatchIndex(bEnd ? BatchList.BatchStarts.Num() : 0)`
- L60 _public function_ `TIterator& operator++()`
- L65 _public function_ `TArrayView<T> operator*() const`
- L71 _public function_ `bool operator!=(TIterator& Other) const`
- L75 _public member_ `const TBatchView& BatchList;`
- L76 _public member_ `int32 BatchIndex;`

### `Source/Developer/DerivedDataCache/Private/DerivedDataBackendInterface.h` (Private)


#### enum `UE::DerivedData::EBackendSpeedClass`  
`enum class EBackendSpeedClass`  
_L39-46_
- desc: Speed classes. Higher values are faster so > / < comparisons make sense.
- L41 _public enumerator_ `Unknown`
- L42 _public enumerator_ `Slow` — Unknown,		  Don't know yet
- L43 _public enumerator_ `Ok` — Slow,			  Slow, likely a remote drive. Some benefit but handle with care
- L44 _public enumerator_ `Fast` — Ok,				  Ok but not great.
- L45 _public enumerator_ `Local` — Fast,			  Fast but seek times still have an impact

#### class `UE::DerivedData::FDerivedDataBackend`  
`class FDerivedDataBackend : public ICache`  
_L48-102_
- inherits: `ICache`
- L51 _public prototype_ `static FDerivedDataBackend* CreateStatic();`
- L58 _public prototype_ `static FDerivedDataBackend& GetStatic();` — Singleton to retrieve the GLOBAL backend @return Reference to the global cache backend
- L60 _public prototype_ `virtual ~FDerivedDataBackend() = default;`
- L66 _public prototype_ `virtual ILegacyCacheStore& GetRoot() = 0;` — Singleton to retrieve the root cache @return Reference to the global cache root
- L72 _public prototype_ `virtual void AddToAsyncCompletionCounter(int32 Addend) = 0;`
- L73 _public prototype_ `virtual bool AnyAsyncRequestsRemaining() = 0;`
- L74 _public prototype_ `virtual bool IsShuttingDown() = 0;`
- L75 _public prototype_ `virtual void WaitForQuiescence(bool bShutdown = false) = 0;`
- L76 _public prototype_ `virtual bool GetUsingSharedDDC() const = 0;`
- L77 _public prototype_ `virtual const TCHAR* GetGraphName() const = 0;`
- L78 _public prototype_ `virtual const TCHAR* GetDefaultGraphName() const = 0;`
- L85 _public prototype_ `virtual ILegacyCacheStore* MountPakFile(const TCHAR* PakFilename) = 0;` — Mounts a read-only pak file. @param PakFilename Pak filename
- L92 _public prototype_ `virtual bool UnmountPakFile(const TCHAR* PakFilename) = 0;` — Unmounts a read-only pak file. @param PakFilename Pak filename
- L97 _public prototype_ `virtual TSharedRef<FDerivedDataCacheStatsNode> GatherUsageStats() const = 0;` — Gather the usage of the DDC hierarchically.
- L99 _public prototype_ `virtual void GatherResourceStats(TArray<FDerivedDataCacheResourceStat>& DDCResourceStats) const = 0;`
- L101 _public prototype_ `virtual void GatherVerificationStats(FDerivedDataCacheVerificationStats& OutStats) const = 0;`

#### Free symbols / members of external scopes

- L17 _delegate_ `DECLARE_DWORD_ACCUMULATOR_STAT_EXTERN(TEXT("Num Gets"),STAT_DDC_NumGets,STATGROUP`
- L18 _delegate_ `DECLARE_DWORD_ACCUMULATOR_STAT_EXTERN(TEXT("Num Puts"),STAT_DDC_NumPuts,STATGROUP`
- L19 _delegate_ `DECLARE_DWORD_ACCUMULATOR_STAT_EXTERN(TEXT("Num Build"),STAT_DDC_NumBuilds,STATGROU`
- L20 _delegate_ `DECLARE_DWORD_ACCUMULATOR_STAT_EXTERN(TEXT("Num Exists"),STAT_DDC_NumExist,STATGRO`
- L21 _delegate_ `DECLARE_FLOAT_ACCUMULATOR_STAT_EXTERN(TEXT("Sync Get Time"),STAT_DDC_SyncGetTime,STAT`
- L22 _delegate_ `DECLARE_FLOAT_ACCUMULATOR_STAT_EXTERN(TEXT("ASync Wait Time"),STAT_DDC_ASyncWaitTime,ST`
- L23 _delegate_ `DECLARE_FLOAT_ACCUMULATOR_STAT_EXTERN(TEXT("Sync Put Time"),STAT_DDC_PutTime,STAT`
- L24 _delegate_ `DECLARE_FLOAT_ACCUMULATOR_STAT_EXTERN(TEXT("Sync Build Time"),STAT_DDC_SyncBuildTime,ST`
- L25 _delegate_ `DECLARE_FLOAT_ACCUMULATOR_STAT_EXTERN(TEXT("Exists Time"),STAT_DDC_ExistTime,STATGR`
- L33 _namespace_ `namespace UE`
- L33 _namespace_ `namespace DerivedData` (scope `UE`)
- L106 _function_ `inline const TCHAR* LexToString(EBackendSpeedClass SpeedClass)` (scope `UE::DerivedData`)
- L126 _function_ `inline void LexFromString(EBackendSpeedClass& OutValue, const TCHAR* Buffer)` (scope `UE::DerivedData`)

### `Source/Developer/DerivedDataCache/Private/DerivedDataBuildJobContext.h` (Private)


#### class `UE::DerivedData::Private::FBuildJobContext`  
`class FBuildJobContext final : public FBuildContext, public FBuildConfigContext, public FRequestBase`  
_L27-102_
- inherits: `FBuildContext,FBuildConfigContext,FRequestBase`
- L30 _public prototype_ `FBuildJobContext( IBuildJob& Job, const FCacheKey& CacheKey, const IBuildFunction& Function, FBuildOutputBuilder& OutputBuilder);`
- L36 _public prototype_ `void BeginBuild(IRequestOwner& Owner, TUniqueFunction<void ()>&& OnEndBuild);`
- L38 _public prototype_ `const FSharedString& GetName() const final;`
- L40 _public function_ `inline const FUtf8SharedString& GetTypeName() const`
- L42 _public function_ `inline const FCacheKey& GetCacheKey() const`
- L44 _public function_ `inline ECachePolicy GetCachePolicyMask() const final`
- L45 _public function_ `inline EBuildPolicy GetBuildPolicyMask() const final`
- L46 _public function_ `inline uint64 GetRequiredMemory() const final`
- L47 _public function_ `inline bool ShouldCheckDeterministicOutput() const`
- L49 _public prototype_ `void AddConstant(FUtf8StringView Key, FCbObject&& Value);`
- L50 _public prototype_ `void AddInput(FUtf8StringView Key, const FCompressedBuffer& Value);`
- L52 _public prototype_ `void AddError(FStringView Message) final;`
- L53 _public prototype_ `void AddWarning(FStringView Message) final;`
- L54 _public prototype_ `void AddMessage(FStringView Message) final;`
- L56 _public prototype_ `void ResetInputs();`
- L59 _private prototype_ `FCbObject FindConstant(FUtf8StringView Key) const final;`
- L60 _private prototype_ `FSharedBuffer FindInput(FUtf8StringView Key) const final;`
- L62 _private prototype_ `void AddMeta(FUtf8StringView Key, const FCbField& Meta) final;`
- L64 _private prototype_ `void AddValue(const FValueId& Id, const FValue& Value) final;`
- L65 _private prototype_ `void AddValue(const FValueId& Id, const FCompressedBuffer& Buffer) final;`
- L66 _private prototype_ `void AddValue(const FValueId& Id, const FCompositeBuffer& Buffer, uint64 BlockSize) final;`
- L67 _private prototype_ `void AddValue(const FValueId& Id, const FSharedBuffer& Buffer, uint64 BlockSize) final;`
- L68 _private prototype_ `void AddValue(const FValueId& Id, const FCbObject& Object) final;`
- L70 _private prototype_ `void EndBuild();`
- L71 _private prototype_ `void BeginAsyncBuild() final;`
- L72 _private prototype_ `void EndAsyncBuild() final;`
- L74 _private prototype_ `void SetTypeName(const FUtf8SharedString& TypeName) final;`
- L75 _private prototype_ `void SetCacheBucket(FCacheBucket Bucket) final;`
- L76 _private prototype_ `void SetCachePolicyMask(ECachePolicy Policy) final;`
- L77 _private prototype_ `void SetBuildPolicyMask(EBuildPolicy Policy) final;`
- L78 _private function_ `void SetRequiredMemory(uint64 InRequiredMemory) final`
- L79 _private function_ `void SkipDeterministicOutputCheck() final`
- L81 _private prototype_ `void SetPriority(EPriority Priority) final;`
- L82 _private prototype_ `void Cancel() final;`
- L83 _private prototype_ `void Wait() final;`
- L86 _private member_ `IBuildJob& Job;`
- L87 _private member_ `FCacheKey CacheKey;`
- L88 _private member_ `FUtf8SharedString TypeName;`
- L89 _private member_ `const IBuildFunction& Function;`
- L90 _private member_ `FBuildOutputBuilder& OutputBuilder;`
- L91 _private member_ `TMap<FUtf8SharedString, FCbObject> Constants;`
- L92 _private member_ `TMap<FUtf8SharedString, FCompressedBuffer> Inputs;`
- L93 _private member_ `TUniqueFunction<void ()> OnEndBuild;`
- L94 _private member_ `IRequestOwner* Owner{};`
- L95 _private member_ `uint64 RequiredMemory{};`
- L96 _private member_ `ECachePolicy CachePolicyMask;`
- L97 _private member_ `EBuildPolicy BuildPolicyMask;`
- L98 _private member_ `FManualResetEvent BuildCompleteEvent;`
- L99 _private member_ `bool bIsAsyncBuild{false};`
- L100 _private member_ `bool bIsAsyncBuildComplete{false};`
- L101 _private member_ `bool bDeterministicOutputCheck{true};`

#### Free symbols / members of external scopes

- L17 _namespace_ `namespace UE`
- L17 _namespace_ `namespace DerivedData` (scope `UE`)
- L18 _namespace_ `namespace UE`
- L18 _namespace_ `namespace DerivedData` (scope `UE`)
- L19 _namespace_ `namespace UE`
- L19 _namespace_ `namespace DerivedData` (scope `UE`)
- L20 _namespace_ `namespace UE`
- L20 _namespace_ `namespace DerivedData` (scope `UE`)
- L21 _namespace_ `namespace UE`
- L21 _namespace_ `namespace DerivedData` (scope `UE`)
- L22 _namespace_ `namespace UE`
- L22 _namespace_ `namespace DerivedData` (scope `UE`)
- L24 _namespace_ `namespace UE`
- L24 _namespace_ `namespace DerivedData` (scope `UE`)
- L24 _namespace_ `namespace Private` (scope `UE::DerivedData`)

### `Source/Developer/DerivedDataCache/Private/DerivedDataBuildPrivate.h` (Private)


#### struct `UE::DerivedData::Private::FBuildJobCreateParams`  
`struct FBuildJobCreateParams`  
_L78-85_
- desc: Implemented in DerivedDataBuildJob.cpp
- L80 _public member_ `ICache* Cache{};`
- L81 _public member_ `IBuild& BuildSystem;`
- L82 _public member_ `IBuildScheduler& Scheduler;`
- L83 _public member_ `IBuildInputResolver* InputResolver{};`
- L84 _public member_ `IRequestOwner& Owner;`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace DerivedData` (scope `UE`)
- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace DerivedData` (scope `UE`)
- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace DerivedData` (scope `UE`)
- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace DerivedData` (scope `UE`)
- L17 _namespace_ `namespace UE`
- L17 _namespace_ `namespace DerivedData` (scope `UE`)
- L18 _namespace_ `namespace UE`
- L18 _namespace_ `namespace DerivedData` (scope `UE`)
- L19 _namespace_ `namespace UE`
- L19 _namespace_ `namespace DerivedData` (scope `UE`)
- L20 _namespace_ `namespace UE`
- L20 _namespace_ `namespace DerivedData` (scope `UE`)
- L21 _namespace_ `namespace UE`
- L21 _namespace_ `namespace DerivedData` (scope `UE`)
- L22 _namespace_ `namespace UE`
- L22 _namespace_ `namespace DerivedData` (scope `UE`)
- L23 _namespace_ `namespace UE`
- L23 _namespace_ `namespace DerivedData` (scope `UE`)
- L24 _namespace_ `namespace UE`
- L24 _namespace_ `namespace DerivedData` (scope `UE`)
- L25 _namespace_ `namespace UE`
- L25 _namespace_ `namespace DerivedData` (scope `UE`)
- L26 _namespace_ `namespace UE`
- L26 _namespace_ `namespace DerivedData` (scope `UE`)
- L27 _namespace_ `namespace UE`
- L27 _namespace_ `namespace DerivedData` (scope `UE`)
- L28 _namespace_ `namespace UE`
- L28 _namespace_ `namespace DerivedData` (scope `UE`)
- L29 _namespace_ `namespace UE`
- L29 _namespace_ `namespace DerivedData` (scope `UE`)
- L30 _namespace_ `namespace UE`
- L30 _namespace_ `namespace DerivedData` (scope `UE`)
- L32 _namespace_ `namespace UE`
- L32 _namespace_ `namespace DerivedData` (scope `UE`)
- L35 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogDerivedDataBuild, Log, All);`
- L35 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogDerivedDataBuild, Log, All);` (scope `UE::DerivedData`)
- L39 _namespace_ `namespace UE`
- L39 _namespace_ `namespace DerivedData` (scope `UE`)
- L39 _namespace_ `namespace Private` (scope `UE::DerivedData`)
- L43 _prototype_ `IBuild* CreateBuild(ICache* Cache);` (scope `UE::DerivedData::Private`) — Implemented in DerivedDataBuild.cpp
- L46 _prototype_ `IBuildFunctionRegistry* CreateBuildFunctionRegistry();` (scope `UE::DerivedData::Private`) — Implemented in DerivedDataBuildFunctionRegistry.cpp
- L47 _prototype_ `bool IsValidBuildFunctionName(FUtf8StringView Function);` (scope `UE::DerivedData::Private`)
- L48 _prototype_ `void AssertValidBuildFunctionName(FUtf8StringView Function, FStringView Name);` (scope `UE::DerivedData::Private`)
- L51 _prototype_ `IBuildWorkerRegistry* CreateBuildWorkerRegistry();` (scope `UE::DerivedData::Private`) — Implemented in DerivedDataBuildWorkerRegistry.cpp
- L54 _prototype_ `IBuildScheduler* CreateBuildScheduler();` (scope `UE::DerivedData::Private`) — Implemented in DerivedDataBuildScheduler.cpp
- L57 _prototype_ `FBuildDefinitionBuilder CreateBuildDefinition(const FSharedString& Name, const FUtf8SharedString& Function);` (scope `UE::DerivedData::Private`) — Implemented in DerivedDataBuildDefinition.cpp
- L60 _prototype_ `FBuildActionBuilder CreateBuildAction(const FSharedString& Name, const FUtf8SharedString& Function, const FGuid& FunctionVersion, const FGuid& BuildSystemVersion);` (scope `UE::DerivedData::Private`) — Implemented in DerivedDataBuildAction.cpp
- L63 _prototype_ `FBuildInputsBuilder CreateBuildInputs(const FSharedString& Name);` (scope `UE::DerivedData::Private`) — Implemented in DerivedDataBuildInput.cpp
- L66 _prototype_ `FBuildOutputBuilder CreateBuildOutput(const FSharedString& Name, const FUtf8SharedString& Function);` (scope `UE::DerivedData::Private`) — Implemented in DerivedDataBuildOutput.cpp
- L67 _prototype_ `FValueId GetBuildOutputValueId();` (scope `UE::DerivedData::Private`)
- L70 _prototype_ `FBuildSession CreateBuildSession( const FSharedString& Name, ICache* Cache, IBuild& BuildSystem, IBuildScheduler& Scheduler, IBuildInputResolver* InputResolver);` (scope `UE::DerivedData::Private`) — Implemented in DerivedDataBuildSession.cpp
- L86 _prototype_ `void CreateBuildJob( const FBuildJobCreateParams& Params, const FBuildKey& Key, const FBuildPolicy& Policy, FOnBuildComplete&& OnComplete);` (scope `UE::DerivedData::Private`)
- L91 _prototype_ `void CreateBuildJob( const FBuildJobCreateParams& Params, const FBuildDefinition& Definition, const FOptionalBuildInputs& Inputs, const FBuildPolicy& Policy, FOnBuildComplete&& OnComplete);` (scope `UE::DerivedData::Private`)
- L97 _prototype_ `void CreateBuildJob( const FBuildJobCreateParams& Params, const FBuildAction& Action, const FOptionalBuildInputs& Inputs, const FBuildPolicy& Policy, FOnBuildComplete&& OnComplete);` (scope `UE::DerivedData::Private`)

### `Source/Developer/DerivedDataCache/Private/DerivedDataCachePrivate.h` (Private)


#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace DerivedData` (scope `UE`)
- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace DerivedData` (scope `UE`)
- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace DerivedData` (scope `UE`)
- L12 _namespace_ `namespace Private` (scope `UE::DerivedData`)
- L16 _prototype_ `void LaunchTaskInCacheThreadPool(IRequestOwner& Owner, TUniqueFunction<void ()>&& TaskBody);` (scope `UE::DerivedData::Private`) — Implemented in DerivedDataCacheModule.cpp
- L19 _prototype_ `uint64 GetCacheRecordCompressedSize(const FCacheRecord& Record);` (scope `UE::DerivedData::Private`) — Implemented in DerivedDataCacheRecord.cpp
- L20 _prototype_ `uint64 GetCacheRecordTotalRawSize(const FCacheRecord& Record);` (scope `UE::DerivedData::Private`)
- L21 _prototype_ `uint64 GetCacheRecordRawSize(const FCacheRecord& Record);` (scope `UE::DerivedData::Private`)

### `Source/Developer/DerivedDataCache/Private/DerivedDataCacheStats.h` (Private)


#### class `UE::DerivedData::FRequestCounter`  
`class FRequestCounter`  
_L19-52_
- L27 _private typedef_ `using ERequestOp = ECacheStoreRequestOp;`
- L28 _private typedef_ `using ERequestType = ECacheStoreRequestType;`
- L31 _public prototype_ `void AddRequest(ERequestType Type, ERequestOp Op, EStatus Status);`
- L33 _public function_ `constexpr uint64 Puts() const`
- L34 _public function_ `constexpr uint64 PutHits() const`
- L35 _public function_ `constexpr uint64 PutMisses() const`
- L37 _public function_ `constexpr uint64 Gets() const`
- L38 _public function_ `constexpr uint64 GetHits() const`
- L39 _public function_ `constexpr uint64 GetMisses() const`
- L41 _public function_ `constexpr uint64 Total() const`
- L42 _public function_ `constexpr uint64 TotalHits() const`
- L43 _public function_ `constexpr uint64 TotalMisses() const`
- L46 _private member_ `FCounter PutRecord;`
- L47 _private member_ `FCounter PutValue;`
- L48 _private member_ `FCounter GetRecord;`
- L49 _private member_ `FCounter GetValue;`
- L50 _private member_ `FCounter GetRecordChunk;`
- L51 _private member_ `FCounter GetValueChunk;`

#### struct `UE::DerivedData::FRequestCounter::FCounter`  
`struct FCounter`  
_L21-25_
- L23 _public member_ `uint64 Hits = 0;`
- L24 _public member_ `uint64 Misses = 0;`

#### class `UE::DerivedData::FTimeAveragedStat`  
`class FTimeAveragedStat`  
_L54-104_
- L57 _public function_ `void SetPeriod(FMonotonicTimeSpan NewPeriod)`
- L59 _public prototype_ `void Add(FMonotonicTimePoint StartTime, FMonotonicTimePoint EndTime, double Value);`
- L62 _public prototype_ `double GetRate(FMonotonicTimePoint Time);` — Calculate and return the average rate at the time. Time must be monotonically increasing.
- L65 _public prototype_ `double GetValue(FMonotonicTimePoint Time);` — Calculate and return the average value at the time. Time must be monotonically increasing.
- L68 _private prototype_ `void Update(FMonotonicTimePoint Time);`
- L83 _private member_ `FMonotonicTimeSpan Period;` — Period of time that this stat is averaged over.
- L85 _private member_ `FMonotonicTimePoint LastTime;` — Time at which the most recent update occurred.
- L87 _private member_ `TArray<FRange> ActiveRanges;` — Ranges of time that have values.
- L89 _private member_ `TArray<FValue> StartValues;` — Values that start later than the most recent update time.
- L91 _private member_ `TArray<FValue> EndValues;` — Values that end later than the most recent update time.
- L93 _private member_ `double AverageRate = 0.0;` — Average rate from the last update that had values, or 0.
- L95 _private member_ `double AverageValue = 0.0;` — Average value from the last update that had values, or 0.
- L97 _private member_ `double AccumulatedValue = 0.0;` — Sum of values in the period up to the most recent update time.
- L99 _private member_ `int32 AccumulatedValueCount = 0;` — Number of values within the period at the most recent update time.
- L101 _private member_ `bool bUpdatePending = false;` — Whether values have been added since the last update.
- L103 _private member_ `FMutex Mutex;` — Mutex that can be used to synchronize access to the stat from multiple threads.

#### struct `UE::DerivedData::FTimeAveragedStat::FRange`  
`struct FRange`  
_L70-74_
- L72 _public member_ `FMonotonicTimePoint StartTime;`
- L73 _public member_ `FMonotonicTimePoint EndTime;`

#### struct `UE::DerivedData::FTimeAveragedStat::FValue`  
`struct FValue`  
_L76-80_
- L78 _public member_ `FMonotonicTimePoint Time;`
- L79 _public member_ `double Value = 0.0;`

#### class `UE::DerivedData::FCacheBucketStats`  
`class FCacheBucketStats final`  
_L108-134_
- L112 _public member_ `FCacheBucket Bucket;` — Name of the cache bucket.
- L114 _public member_ `uint64 LogicalReadSize = 0;` — Size of the raw data and metadata that was read from the cache bucket.
- L116 _public member_ `uint64 LogicalWriteSize = 0;` — Size of the raw data and metadata that was written to the cache bucket.
- L118 _public member_ `uint64 PhysicalReadSize = 0;` — Size of the compressed data and anything else that was read from the cache bucket.
- L120 _public member_ `uint64 PhysicalWriteSize = 0;` — Size of the compressed data and anything else that was written to the cache bucket.
- L122 _public member_ `FMonotonicTimeSpan MainThreadTime;` — Approximate CPU time on the main thread that was needed to satisfy requests in the cache bucket.
- L124 _public member_ `FMonotonicTimeSpan OtherThreadTime;` — Approximate CPU time off the main thread that was needed to satisfy requests in the cache bucket.
- L126 _public member_ `FRequestCounter RequestCount;` — Count of requests that accessed the cache bucket.
- L128 _public member_ `mutable FMutex Mutex;` — Mutex that can be used to synchronize access to the cache buckets stats from multiple threads.
- L131 _public member_ `FCookStats::CallStats GetStats;`
- L132 _public member_ `FCookStats::CallStats PutStats;`

#### class `UE::DerivedData::FCacheStoreStats`  
`class FCacheStoreStats final : public ICacheStoreStats`  
_L136-190_
- inherits: `ICacheStoreStats`
- L139 _public prototype_ `FCacheStoreStats(FCacheStats& CacheStats, ECacheStoreFlags Flags, FStringView Type, FStringView Name, FStringView Path);`
- L141 _public member_ `FString Type;`
- L142 _public member_ `FString Name;`
- L143 _public member_ `FString Path;`
- L144 _public member_ `FText Status;`
- L145 _public member_ `ECacheStoreFlags Flags = ECacheStoreFlags::None;`
- L146 _public member_ `ECacheStoreStatusCode StatusCode = ECacheStoreStatusCode::None;`
- L147 _public member_ `mutable FMutex Mutex;`
- L149 _public member_ `TMap<FString, FString> Attributes;`
- L151 _public member_ `FCacheStats& CacheStats;`
- L154 _public member_ `uint64 LogicalReadSize = 0;` — Size of the raw data and metadata that was read from the cache store.
- L156 _public member_ `uint64 LogicalWriteSize = 0;` — Size of the raw data and metadata that was written to the cache store.
- L158 _public member_ `uint64 PhysicalReadSize = 0;` — Size of the compressed data and anything else that was read from the cache store.
- L160 _public member_ `uint64 PhysicalWriteSize = 0;` — Size of the compressed data and anything else that was written to the cache store.
- L162 _public member_ `FMonotonicTimeSpan MainThreadTime;` — Approximate CPU time on the main thread that was needed.
- L164 _public member_ `FMonotonicTimeSpan OtherThreadTime;` — Approximate CPU time off the main thread that was needed.
- L166 _public member_ `FRequestCounter RequestCount;` — Count of requests that accessed the cache store.
- L168 _public member_ `uint64 TotalPhysicalSize = ~0ull;` — Total size of the data in the cache store, ~0ull indicate that the information is not available
- L170 _public member_ `FTimeAveragedStat AverageLatency;`
- L171 _public member_ `FTimeAveragedStat AveragePhysicalReadSize;`
- L172 _public member_ `FTimeAveragedStat AveragePhysicalWriteSize;`
- L175 _public member_ `FCookStats::CallStats GetStats;`
- L176 _public member_ `FCookStats::CallStats PutStats;`
- L180 _private function_ `FStringView GetType() const final`
- L181 _private function_ `FStringView GetName() const final`
- L182 _private function_ `FStringView GetPath() const final`
- L183 _private prototype_ `void SetFlags(ECacheStoreFlags Flags) final;`
- L184 _private prototype_ `void SetStatus(ECacheStoreStatusCode StatusCode, const FText& Status) final;`
- L185 _private prototype_ `void SetAttribute(FStringView Key, FStringView Value) final;`
- L186 _private prototype_ `void AddRequest(const FCacheStoreRequestStats& Stats) final;`
- L187 _private prototype_ `void AddLatency(FMonotonicTimePoint StartTime, FMonotonicTimePoint EndTime, FMonotonicTimeSpan Latency) final;`
- L188 _private prototype_ `double GetAverageLatency() final;`
- L189 _private prototype_ `void SetTotalPhysicalSize(uint64 TotalPhysicalSize) final;`

#### class `UE::DerivedData::FCacheStats`  
`class FCacheStats final`  
_L192-200_
- L195 _public member_ `TArray<TUniquePtr<FCacheBucketStats>> BucketStats;`
- L196 _public member_ `TArray<TUniquePtr<FCacheStoreStats>> StoreStats;`
- L197 _public member_ `mutable FMutex Mutex;`
- L199 _public prototype_ `FCacheBucketStats& GetBucket(FCacheBucket Bucket);`

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace DerivedData` (scope `UE`)
- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace DerivedData` (scope `UE`)

### `Source/Developer/DerivedDataCache/Private/DerivedDataCacheStore.h` (Private)


#### class `UE::DerivedData::ICacheStore`  
`class ICacheStore`  
_L34-114_
- desc: Interface to a store of cache records and cache values. Functions on this interface may be called from any thread.
- L37 _public prototype_ `virtual ~ICacheStore() = default;`
- L51 _public prototype_ `virtual void Put( TConstArrayView<FCachePutRequest> Requests, IRequestOwner& Owner, FOnCachePutComplete&& OnComplete) = 0;` — Asynchronous request to put records in the cache. Behavior must match the cache record policy in each request. A few of those requirements: - Store with Query is expected *not* to overwrite an existing record. - Store without Query is permitted to overwrite an existing record. - Response must be Error if any value has unrecoverable missing data, unless the policy has PartialRecord. @param Requests     Requests with the cache records to store. Records must have a key. @param Owner        The owner to execute the request within. See IRequestOwner. @param OnComplete   A callback invoked for every request as it completes or is canceled.
- L69 _public prototype_ `virtual void Get( TConstArrayView<FCacheGetRequest> Requests, IRequestOwner& Owner, FOnCacheGetComplete&& OnComplete) = 0;` — Asynchronous request to get records from the cache. Behavior must match the cache record policy in each request. A few of those requirements: - Data is required if the value policy has Query. - Data must not be in the response if the value policy has SkipData. - Response must contain values and available data if the record policy has PartialRecord. - Response must be Error if any required data is missing, even if the record policy has PartialRecord. @param Requests     Requests with the keys of the cache records to fetch. @param Owner        The owner to execute the request within. See IRequestOwner. @param OnComplete   A callback invoked for every request as it completes or is canceled.
- L81 _public prototype_ `virtual void PutValue( TConstArrayView<FCachePutValueRequest> Requests, IRequestOwner& Owner, FOnCachePutValueComplete&& OnComplete) = 0;` — Asynchronous request to put values in the cache. @param Requests     Requests with the cache values to store. Requests must have a key. @param Owner        The owner to execute the request within. See IRequestOwner. @param OnComplete   A callback invoked for every request as it completes or is canceled.
- L93 _public prototype_ `virtual void GetValue( TConstArrayView<FCacheGetValueRequest> Requests, IRequestOwner& Owner, FOnCacheGetValueComplete&& OnComplete) = 0;` — Asynchronous request to get values from the cache. @param Requests     Requests with the keys of the cache values to fetch. @param Owner        The owner to execute the request within. See IRequestOwner. @param OnComplete   A callback invoked for every request as it completes or is canceled.
- L105 _public prototype_ `virtual void GetChunks( TConstArrayView<FCacheGetChunkRequest> Requests, IRequestOwner& Owner, FOnCacheGetChunkComplete&& OnComplete) = 0;` — Asynchronous request to get chunks, which are subsets of values, from records or values. @param Requests     Requests with the key, ID, offset, and size of each chunk to fetch. @param Owner        The owner to execute the request within. See IRequestOwner. @param OnComplete   A callback invoked for every request as it completes or is canceled.
- L110 _public typedef_ `using ERequestOp = ECacheStoreRequestOp;`
- L111 _public typedef_ `using ERequestType = ECacheStoreRequestType;`
- L112 _public typedef_ `using FRequestStats = FCacheStoreRequestStats;`
- L113 _public typedef_ `using FRequestTimer = FCacheStoreRequestTimer;`

#### enum `UE::DerivedData::ECacheStoreRequestType`  
`enum class ECacheStoreRequestType : uint8`  
_L119-124_
- desc: The type of data accessed by a request.
- L121 _public enumerator_ `None = 0`
- L122 _public enumerator_ `Record`
- L123 _public enumerator_ `Value`

#### enum `UE::DerivedData::ECacheStoreRequestOp`  
`enum class ECacheStoreRequestOp : uint8`  
_L145-151_
- desc: The operation performed by the request.
- L147 _public enumerator_ `None = 0`
- L148 _public enumerator_ `Put`
- L149 _public enumerator_ `Get`
- L150 _public enumerator_ `GetChunk`

#### enum `UE::DerivedData::ECacheStoreFlags`  
`enum class ECacheStoreFlags : uint32`  
_L171-194_
- L173 _public enumerator_ `None = 0`
- L176 _public enumerator_ `Local = 1 << 0` — Accepts requests with a policy of QueryLocal or StoreLocal. Needs matching Query/Store flag.
- L178 _public enumerator_ `Remote = 1 << 1` — Accepts requests with a policy of QueryRemote or StoreRemote. Needs matching Query/Store flag.
- L181 _public enumerator_ `Query = 1 << 2` — Accepts requests with a policy of QueryLocal or QueryRemote. Needs matching Local/Remote flag.
- L183 _public enumerator_ `Store = 1 << 3` — Accepts requests with a policy of StoreLocal or StoreRemote. Needs matching Local/Remote flag.
- L186 _public enumerator_ `StopPutStore = 1 << 4` — A put of a record or value contained by this cache store will not store to later cache stores.
- L188 _public enumerator_ `StopGetStore = 1 << 5` — A get of a record or value contained by this cache store will not store to later cache stores.
- L190 _public enumerator_ `StopStore = StopPutStore | StopGetStore` — A record or value contained by this cache store will not store to later cache stores.
- L193 _public enumerator_ `NativeAsync = 1 << 6` — Async operation is natively provided by this cache store for requests of non-blocking priority.

#### class `UE::DerivedData::ICacheStoreOwner`  
`class ICacheStoreOwner`  
_L198-223_
- L201 _public prototype_ `virtual ~ICacheStoreOwner() = default;`
- L203 _public prototype_ `virtual void Add(const FSharedString& Name, ILegacyCacheStore* CacheStore, ECacheStoreFlags Flags) = 0;`
- L204 _public prototype_ `virtual void SetFlags(ILegacyCacheStore* CacheStore, ECacheStoreFlags Flags) = 0;`
- L205 _public prototype_ `virtual void RemoveNotSafe(ILegacyCacheStore* CacheStore) = 0;`
- L208 _public prototype_ `virtual bool HasAllFlags(ECacheStoreFlags Flags) const = 0;` — Returns true if the combined flags of the owned cache stores contain all of these flags.
- L210 _public prototype_ `virtual void AddMaintainer(ICacheStoreMaintainer* Maintainer) = 0;`
- L211 _public prototype_ `virtual void RemoveMaintainer(ICacheStoreMaintainer* Maintainer) = 0;`
- L213 _public prototype_ `virtual int32 AddToAsyncTaskCounter(int32 Value) = 0;`
- L215 _public prototype_ `virtual ICacheStoreStats* CreateStats(ILegacyCacheStore* CacheStore, ECacheStoreFlags Flags, FStringView Type, FStringView Name, FStringView Path = {}) = 0;`
- L216 _public prototype_ `virtual void DestroyStats(ICacheStoreStats* Stats) = 0;`
- L218 _public prototype_ `virtual void LegacyResourceStats(TArray<FDerivedDataCacheResourceStat>& OutStats) const = 0;`
- L220 _public prototype_ `virtual void SetShuttingDown() = 0;`
- L221 _public prototype_ `virtual bool IsShuttingDown() const = 0;`
- L222 _public prototype_ `virtual void WaitForIdle() const = 0;`

#### enum `UE::DerivedData::ECacheStoreStatusCode`  
`enum class ECacheStoreStatusCode : uint8`  
_L225-230_
- L227 _public enumerator_ `None = 0`
- L228 _public enumerator_ `Warning`
- L229 _public enumerator_ `Error`

#### struct `UE::DerivedData::FCacheStoreRequestStats`  
`struct FCacheStoreRequestStats final`  
_L235-276_
- desc: Stats that represent how one cache store processed one request.
- L238 _public member_ `FSharedString Name;` — A name to identify this request for logging and profiling. An object path is typically sufficient.
- L240 _public member_ `FCacheBucket Bucket;` — Bucket that contains the data being accessed by this request.
- L242 _public member_ `uint64 LogicalReadSize = 0;` — Size of the raw data and metadata that was read from the cache store.
- L244 _public member_ `uint64 LogicalWriteSize = 0;` — Size of the raw data and metadata that was written to the cache store.
- L246 _public member_ `uint64 PhysicalReadSize = 0;` — Size of the compressed data and anything else that was read from the cache store to satisfy this request.
- L248 _public member_ `uint64 PhysicalWriteSize = 0;` — Size of the compressed data and anything else that was written to the cache store to satisfy this request.
- L250 _public member_ `FMonotonicTimeSpan Latency = FMonotonicTimeSpan::Infinity();` — Minimum latency to the cache store of any of the individual accesses needed to satisfy this request.
- L252 _public member_ `FMonotonicTimeSpan MainThreadTime;` — Approximate CPU time on the main thread that was needed to satisfy this request.
- L254 _public member_ `FMonotonicTimeSpan OtherThreadTime;` — Approximate CPU time off the main thread that was needed to satisfy this request.
- L256 _public member_ `FMonotonicTimePoint StartTime = FMonotonicTimePoint::Infinity();` — Wall time at which this the cache store started processing of this request.
- L258 _public member_ `FMonotonicTimePoint EndTime = FMonotonicTimePoint() - FMonotonicTimeSpan::Infinity();` — Wall time at which this the cache store ended processing of this request.
- L260 _public member_ `ECacheStoreRequestType Type = ECacheStoreRequestType::None;` — The type of data that was accessed by this request.
- L262 _public member_ `ECacheStoreRequestOp Op = ECacheStoreRequestOp::None;` — The operation that was performed by this request.
- L264 _public member_ `EStatus Status = EStatus::Ok;` — The status with which this request completed.
- L266 _public member_ `mutable TDontCopy<FMutex> Mutex;` — Mutex that can be used by cache stores that process a request on multiple threads.
- L268 _public prototype_ `void AddLatency(FMonotonicTimeSpan Latency);`
- L271 _public prototype_ `void AddLogicalRead(const FCacheRecord& Record);` — Record a logical read of the metadata and values in the record.
- L273 _public prototype_ `void AddLogicalRead(const FValue& Value);` — Record a logical read of the value. Recorded as 0 if the value has no data.
- L275 _public prototype_ `void AddLogicalWrite(const FValue& Value);` — Record a logical write of the value. Recorded as 0 if the value has no data.

#### class `UE::DerivedData::FCacheStoreRequestTimer`  
`class FCacheStoreRequestTimer final`  
_L279-293_
- desc: Updates StartTime, EndTime, MainThreadTime, OtherThreadTime based on its lifetime.
- L282 _public prototype_ `explicit FCacheStoreRequestTimer(FCacheStoreRequestStats& Stats);`
- L283 _public function_ `inline ~FCacheStoreRequestTimer()`
- L285 _public prototype_ `void Stop();`
- L287 _public prototype_ `FCacheStoreRequestTimer(const FCacheStoreRequestTimer&) = delete;`
- L288 _public prototype_ `FCacheStoreRequestTimer& operator=(const FCacheStoreRequestTimer&) = delete;`
- L291 _private member_ `FCacheStoreRequestStats& Stats;`
- L292 _private member_ `FMonotonicTimePoint StartTime;`

#### class `UE::DerivedData::ICacheStoreStats`  
`class ICacheStoreStats`  
_L298-327_
- desc: Interface to report the status of a cache store and stats for each request that it processes.
- L301 _public prototype_ `virtual ~ICacheStoreStats() = default;`
- L304 _public prototype_ `virtual FStringView GetType() const = 0;` — Returns the type name of the associated cache store.
- L306 _public prototype_ `virtual FStringView GetName() const = 0;` — Returns the name of the associated cache store in the hierarchy.
- L308 _public prototype_ `virtual FStringView GetPath() const = 0;` — Returns the path to the associated cache store where applicable.
- L311 _public prototype_ `virtual void SetFlags(ECacheStoreFlags Flags) = 0;` — Sets the flags detailing how the associated cache store operates.
- L313 _public prototype_ `virtual void SetStatus(ECacheStoreStatusCode StatusCode, const FText& Status) = 0;` — Sets the status of the associated cache store. Persists until the next call.
- L315 _public prototype_ `virtual void SetAttribute(FStringView Key, FStringView Value) = 0;` — Sets a named attribute on the associated cache store. Persists until the next call.
- L318 _public prototype_ `virtual void AddRequest(const FCacheStoreRequestStats& Stats) = 0;` — Adds stats for a single request that was processed by the associated cache store.
- L321 _public prototype_ `virtual void AddLatency(FMonotonicTimePoint StartTime, FMonotonicTimePoint EndTime, FMonotonicTimeSpan Latency) = 0;` — Adds stats for latency for a measurement that was done for the associated cache store.
- L324 _public prototype_ `virtual double GetAverageLatency() = 0;` — Gets the average latency value for the current time in seconds.
- L326 _public prototype_ `virtual void SetTotalPhysicalSize(uint64 TotalPhysicalSize) = 0;`

#### struct `UE::DerivedData::Private::TCacheStoreFunctionFor`  
`template <> struct TCacheStoreFunctionFor<FCachePutRequest>`  
_L345-348_
- L347 _public member_ `constexpr static void (ICacheStore::*Function)(TConstArrayView<FCachePutRequest>, IRequestOwner&, TCacheOnCompleteFor<FCachePutRequest>&&) = &ICacheStore::Put;`
- L353 _public member_ `constexpr static void (ICacheStore::*Function)(TConstArrayView<FCacheGetRequest>, IRequestOwner&, TCacheOnCompleteFor<FCacheGetRequest>&&) = &ICacheStore::Get;`
- L359 _public member_ `constexpr static void (ICacheStore::*Function)(TConstArrayView<FCachePutValueRequest>, IRequestOwner&, TCacheOnCompleteFor<FCachePutValueRequest>&&) = &ICacheStore::PutValue;`
- L365 _public member_ `constexpr static void (ICacheStore::*Function)(TConstArrayView<FCacheGetValueRequest>, IRequestOwner&, TCacheOnCompleteFor<FCacheGetValueRequest>&&) = &ICacheStore::GetValue;`
- L371 _public member_ `constexpr static void (ICacheStore::*Function)(TConstArrayView<FCacheGetChunkRequest>, IRequestOwner&, TCacheOnCompleteFor<FCacheGetChunkRequest>&&) = &ICacheStore::GetChunks;`

#### struct `UE::DerivedData::Private::TCacheStoreFunctionFor`  
`template <> struct TCacheStoreFunctionFor<FCacheGetRequest>`  
_L351-354_
- L347 _public member_ `constexpr static void (ICacheStore::*Function)(TConstArrayView<FCachePutRequest>, IRequestOwner&, TCacheOnCompleteFor<FCachePutRequest>&&) = &ICacheStore::Put;`
- L353 _public member_ `constexpr static void (ICacheStore::*Function)(TConstArrayView<FCacheGetRequest>, IRequestOwner&, TCacheOnCompleteFor<FCacheGetRequest>&&) = &ICacheStore::Get;`
- L359 _public member_ `constexpr static void (ICacheStore::*Function)(TConstArrayView<FCachePutValueRequest>, IRequestOwner&, TCacheOnCompleteFor<FCachePutValueRequest>&&) = &ICacheStore::PutValue;`
- L365 _public member_ `constexpr static void (ICacheStore::*Function)(TConstArrayView<FCacheGetValueRequest>, IRequestOwner&, TCacheOnCompleteFor<FCacheGetValueRequest>&&) = &ICacheStore::GetValue;`
- L371 _public member_ `constexpr static void (ICacheStore::*Function)(TConstArrayView<FCacheGetChunkRequest>, IRequestOwner&, TCacheOnCompleteFor<FCacheGetChunkRequest>&&) = &ICacheStore::GetChunks;`

#### struct `UE::DerivedData::Private::TCacheStoreFunctionFor`  
`template <> struct TCacheStoreFunctionFor<FCachePutValueRequest>`  
_L357-360_
- L347 _public member_ `constexpr static void (ICacheStore::*Function)(TConstArrayView<FCachePutRequest>, IRequestOwner&, TCacheOnCompleteFor<FCachePutRequest>&&) = &ICacheStore::Put;`
- L353 _public member_ `constexpr static void (ICacheStore::*Function)(TConstArrayView<FCacheGetRequest>, IRequestOwner&, TCacheOnCompleteFor<FCacheGetRequest>&&) = &ICacheStore::Get;`
- L359 _public member_ `constexpr static void (ICacheStore::*Function)(TConstArrayView<FCachePutValueRequest>, IRequestOwner&, TCacheOnCompleteFor<FCachePutValueRequest>&&) = &ICacheStore::PutValue;`
- L365 _public member_ `constexpr static void (ICacheStore::*Function)(TConstArrayView<FCacheGetValueRequest>, IRequestOwner&, TCacheOnCompleteFor<FCacheGetValueRequest>&&) = &ICacheStore::GetValue;`
- L371 _public member_ `constexpr static void (ICacheStore::*Function)(TConstArrayView<FCacheGetChunkRequest>, IRequestOwner&, TCacheOnCompleteFor<FCacheGetChunkRequest>&&) = &ICacheStore::GetChunks;`

#### struct `UE::DerivedData::Private::TCacheStoreFunctionFor`  
`template <> struct TCacheStoreFunctionFor<FCacheGetValueRequest>`  
_L363-366_
- L347 _public member_ `constexpr static void (ICacheStore::*Function)(TConstArrayView<FCachePutRequest>, IRequestOwner&, TCacheOnCompleteFor<FCachePutRequest>&&) = &ICacheStore::Put;`
- L353 _public member_ `constexpr static void (ICacheStore::*Function)(TConstArrayView<FCacheGetRequest>, IRequestOwner&, TCacheOnCompleteFor<FCacheGetRequest>&&) = &ICacheStore::Get;`
- L359 _public member_ `constexpr static void (ICacheStore::*Function)(TConstArrayView<FCachePutValueRequest>, IRequestOwner&, TCacheOnCompleteFor<FCachePutValueRequest>&&) = &ICacheStore::PutValue;`
- L365 _public member_ `constexpr static void (ICacheStore::*Function)(TConstArrayView<FCacheGetValueRequest>, IRequestOwner&, TCacheOnCompleteFor<FCacheGetValueRequest>&&) = &ICacheStore::GetValue;`
- L371 _public member_ `constexpr static void (ICacheStore::*Function)(TConstArrayView<FCacheGetChunkRequest>, IRequestOwner&, TCacheOnCompleteFor<FCacheGetChunkRequest>&&) = &ICacheStore::GetChunks;`

#### struct `UE::DerivedData::Private::TCacheStoreFunctionFor`  
`template <> struct TCacheStoreFunctionFor<FCacheGetChunkRequest>`  
_L369-372_
- L347 _public member_ `constexpr static void (ICacheStore::*Function)(TConstArrayView<FCachePutRequest>, IRequestOwner&, TCacheOnCompleteFor<FCachePutRequest>&&) = &ICacheStore::Put;`
- L353 _public member_ `constexpr static void (ICacheStore::*Function)(TConstArrayView<FCacheGetRequest>, IRequestOwner&, TCacheOnCompleteFor<FCacheGetRequest>&&) = &ICacheStore::Get;`
- L359 _public member_ `constexpr static void (ICacheStore::*Function)(TConstArrayView<FCachePutValueRequest>, IRequestOwner&, TCacheOnCompleteFor<FCachePutValueRequest>&&) = &ICacheStore::PutValue;`
- L365 _public member_ `constexpr static void (ICacheStore::*Function)(TConstArrayView<FCacheGetValueRequest>, IRequestOwner&, TCacheOnCompleteFor<FCacheGetValueRequest>&&) = &ICacheStore::GetValue;`
- L371 _public member_ `constexpr static void (ICacheStore::*Function)(TConstArrayView<FCacheGetChunkRequest>, IRequestOwner&, TCacheOnCompleteFor<FCacheGetChunkRequest>&&) = &ICacheStore::GetChunks;`

#### Free symbols / members of external scopes

- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace DerivedData` (scope `UE`)
- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace DerivedData` (scope `UE`)
- L17 _namespace_ `namespace UE`
- L17 _namespace_ `namespace DerivedData` (scope `UE`)
- L18 _namespace_ `namespace UE`
- L18 _namespace_ `namespace DerivedData` (scope `UE`)
- L19 _namespace_ `namespace UE`
- L19 _namespace_ `namespace DerivedData` (scope `UE`)
- L20 _namespace_ `namespace UE`
- L20 _namespace_ `namespace DerivedData` (scope `UE`)
- L21 _namespace_ `namespace UE`
- L21 _namespace_ `namespace DerivedData` (scope `UE`)
- L22 _namespace_ `namespace UE`
- L22 _namespace_ `namespace DerivedData` (scope `UE`)
- L23 _namespace_ `namespace UE`
- L23 _namespace_ `namespace DerivedData` (scope `UE`)
- L24 _namespace_ `namespace UE`
- L24 _namespace_ `namespace DerivedData` (scope `UE`)
- L26 _namespace_ `namespace UE`
- L26 _namespace_ `namespace DerivedData` (scope `UE`)
- L126 _function_ `inline const TCHAR* LexToString(ECacheStoreRequestType CacheStoreRequestType)` (scope `UE::DerivedData`)
- L153 _function_ `inline const TCHAR* LexToString(ECacheStoreRequestOp CacheStoreRequestOp)` (scope `UE::DerivedData`)
- L196 _prototype_ `ENUM_CLASS_FLAGS(ECacheStoreFlags);` (scope `UE::DerivedData`)
- L330 _function_ `template <typename RequestRangeType, typename OnCompleteType> inline void CompleteWithStatus(RequestRangeType&& Requests, OnCompleteType&& OnComplete, EStatus Status)` (scope `UE::DerivedData`)
- L338 _namespace_ `namespace Private` (scope `UE::DerivedData`)
- L377 _variable_ `template <typename RequestType> inline constexpr auto CacheStoreFunctionFor = Private::TCacheStoreFunctionFor<RequestType>::Function;` (scope `UE::DerivedData`) — Alias for the cache store function corresponding to the request type.

### `Source/Developer/DerivedDataCache/Private/DerivedDataCacheStoreProxy.h` (Private)


#### class `UE::DerivedData::FCacheStoreProxy`  
`class FCacheStoreProxy : public ILegacyCacheStore, public ICacheStoreOwner`  
_L18-122_
- inherits: `ILegacyCacheStore,ICacheStoreOwner`
- desc: Base class for cache store proxies. A cache store proxy is a cache store that modifies the behavior of another cache store. Use a derived class as the owner when constructing the inner cache store.
- L21 _public function_ `explicit FCacheStoreProxy(ICacheStoreOwner& InOuterOwner) : OuterOwner(InOuterOwner)`
- L26 _public function_ `void Add(const FSharedString& Name, ILegacyCacheStore* CacheStore, ECacheStoreFlags Flags) override`
- L34 _public function_ `void SetFlags(ILegacyCacheStore* CacheStore, ECacheStoreFlags Flags) override`
- L40 _public function_ `void RemoveNotSafe(ILegacyCacheStore* CacheStore) override`
- L48 _public function_ `bool HasAllFlags(ECacheStoreFlags Flags) const override`
- L53 _public function_ `void AddMaintainer(ICacheStoreMaintainer* Maintainer) override`
- L58 _public function_ `void RemoveMaintainer(ICacheStoreMaintainer* Maintainer) override`
- L63 _public function_ `int32 AddToAsyncTaskCounter(int32 Value) override`
- L68 _public function_ `ICacheStoreStats* CreateStats(ILegacyCacheStore* CacheStore, ECacheStoreFlags Flags, FStringView Type, FStringView Name, FStringView Path) override`
- L74 _public function_ `void DestroyStats(ICacheStoreStats* Stats) override`
- L79 _public function_ `void LegacyResourceStats(TArray<FDerivedDataCacheResourceStat>& OutStats) const override`
- L84 _public function_ `void SetShuttingDown() override`
- L89 _public function_ `bool IsShuttingDown() const override`
- L94 _public function_ `void WaitForIdle() const override`
- L100 _protected function_ `ILegacyCacheStore* GetInnerStore() const`
- L106 _protected function_ `const FSharedString& GetInnerStoreName() const`
- L112 _protected function_ `void DestroyInnerStore()`
- L119 _private member_ `ICacheStoreOwner& OuterOwner;`
- L120 _private member_ `TUniquePtr<ILegacyCacheStore> InnerStore;`
- L121 _private member_ `FSharedString InnerStoreName;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace DerivedData` (scope `UE`)

### `Source/Developer/DerivedDataCache/Private/DerivedDataHttpRequestQueue.h` (Private)


#### class `UE::DerivedData::FHttpRequestQueue`  
`class FHttpRequestQueue`  
_L15-31_
- L18 _public typedef_ `using FOnRequest = TUniqueFunction<void(THttpUniquePtr<IHttpRequest>&& Request)>;`
- L20 _public prototype_ `void Initialize(IHttpConnectionPool& ConnectionPool, const FHttpClientParams& ClientParams);`
- L22 _public prototype_ `void CreateRequestAsync(IRequestOwner& Owner, const FHttpRequestParams& Params, FOnRequest&& OnRequest);`
- L25 _private prototype_ `bool TryGiveRequestToQueue(THttpUniquePtr<IHttpRequest>&& Request);`
- L29 _private member_ `THttpUniquePtr<IHttpClient> Client;`
- L30 _private member_ `TLockFreePointerListFIFO<FQueueRequest, 0> Queue;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace DerivedData` (scope `UE`)
- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace DerivedData` (scope `UE`)

### `Source/Developer/DerivedDataCache/Private/DerivedDataLegacyCacheStore.h` (Private)


#### class `UE::DerivedData::ILegacyCacheStore`  
`class ILegacyCacheStore : public ICacheStore`  
_L30-51_
- inherits: `ICacheStore`
- L33 _public prototype_ `void LegacyPut( TConstArrayView<FLegacyCachePutRequest> Requests, IRequestOwner& Owner, FOnLegacyCachePutComplete&& OnComplete);`
- L38 _public prototype_ `void LegacyGet( TConstArrayView<FLegacyCacheGetRequest> Requests, IRequestOwner& Owner, FOnLegacyCacheGetComplete&& OnComplete);`
- L43 _public prototype_ `void LegacyDelete( TConstArrayView<FLegacyCacheDeleteRequest> Requests, IRequestOwner& Owner, FOnLegacyCacheDeleteComplete&& OnComplete);`
- L48 _public prototype_ `virtual void LegacyStats(FDerivedDataCacheStatsNode& OutNode) = 0;`
- L50 _public function_ `virtual void GatherVerificationStats(FDerivedDataCacheVerificationStats& OutStats) const`

#### class `UE::DerivedData::FLegacyCacheKey`  
`class FLegacyCacheKey`  
_L53-65_
- L56 _public prototype_ `FLegacyCacheKey() = default;`
- L57 _public prototype_ `explicit FLegacyCacheKey(FStringView FullKey);`
- L59 _public function_ `[[nodiscard]] inline const FCacheKey& GetKey() const`
- L60 _public function_ `[[nodiscard]] inline const FSharedString& GetFullKey() const`
- L63 _private member_ `FCacheKey Key;`
- L64 _private member_ `FSharedString FullKey;`

#### class `UE::DerivedData::Private::FLegacyCacheValueShared`  
`class Private::FLegacyCacheValueShared final`  
_L67-100_
- L70 _public prototype_ `explicit FLegacyCacheValueShared(const FValue& Value);`
- L71 _public prototype_ `explicit FLegacyCacheValueShared(const FCompositeBuffer& RawData);`
- L73 _public prototype_ `FLegacyCacheValueShared(const FLegacyCacheValueShared&) = delete;`
- L74 _public prototype_ `FLegacyCacheValueShared& operator=(const FLegacyCacheValueShared&) = delete;`
- L76 _public function_ `inline bool HasData() const`
- L77 _public prototype_ `const FValue& GetValue();`
- L78 _public prototype_ `const FCompositeBuffer& GetRawData();`
- L79 _public prototype_ `FIoHash GetRawHash() const;`
- L80 _public prototype_ `uint64 GetRawSize() const;`
- L82 _public function_ `inline void AddRef()`
- L87 _public function_ `inline void Release()`
- L96 _private member_ `FValue Value;`
- L97 _private member_ `FCompositeBuffer RawData;`
- L98 _private member_ `std::atomic<uint32> ReferenceCount{0};`
- L99 _private member_ `FMutex Mutex;`

#### class `UE::DerivedData::FLegacyCacheValue`  
`class FLegacyCacheValue`  
_L102-122_
- L105 _public prototype_ `FLegacyCacheValue() = default;`
- L106 _public prototype_ `explicit FLegacyCacheValue(const FValue& Value);`
- L107 _public prototype_ `explicit FLegacyCacheValue(const FCompositeBuffer& RawData);`
- L109 _public function_ `inline void Reset()`
- L111 _public function_ `[[nodiscard]] inline explicit operator bool() const`
- L112 _public function_ `[[nodiscard]] inline bool IsNull() const`
- L114 _public function_ `[[nodiscard]] inline bool HasData() const`
- L115 _public function_ `[[nodiscard]] inline const FValue& GetValue() const`
- L116 _public function_ `[[nodiscard]] inline const FCompositeBuffer& GetRawData() const`
- L117 _public function_ `[[nodiscard]] inline FIoHash GetRawHash() const`
- L118 _public function_ `[[nodiscard]] inline uint64 GetRawSize() const`
- L121 _private member_ `TRefCountPtr<Private::FLegacyCacheValueShared> Shared;`

#### struct `UE::DerivedData::FLegacyCachePutRequest`  
`struct FLegacyCachePutRequest`  
_L124-133_
- L126 _public member_ `FSharedString Name;`
- L127 _public member_ `FLegacyCacheKey Key;`
- L128 _public member_ `FLegacyCacheValue Value;`
- L129 _public member_ `ECachePolicy Policy = ECachePolicy::Default;`
- L130 _public member_ `uint64 UserData = 0;`
- L132 _public prototype_ `FLegacyCachePutResponse MakeResponse(EStatus Status) const;`

#### struct `UE::DerivedData::FLegacyCachePutResponse`  
`struct FLegacyCachePutResponse`  
_L135-141_
- L137 _public member_ `FSharedString Name;`
- L138 _public member_ `FLegacyCacheKey Key;`
- L139 _public member_ `uint64 UserData = 0;`
- L140 _public member_ `EStatus Status = EStatus::Error;`

#### struct `UE::DerivedData::FLegacyCacheGetRequest`  
`struct FLegacyCacheGetRequest`  
_L143-151_
- L145 _public member_ `FSharedString Name;`
- L146 _public member_ `FLegacyCacheKey Key;`
- L147 _public member_ `ECachePolicy Policy = ECachePolicy::Default;`
- L148 _public member_ `uint64 UserData = 0;`
- L150 _public prototype_ `FLegacyCacheGetResponse MakeResponse(EStatus Status) const;`

#### struct `UE::DerivedData::FLegacyCacheGetResponse`  
`struct FLegacyCacheGetResponse`  
_L153-160_
- L155 _public member_ `FSharedString Name;`
- L156 _public member_ `FLegacyCacheKey Key;`
- L157 _public member_ `FLegacyCacheValue Value;`
- L158 _public member_ `uint64 UserData = 0;`
- L159 _public member_ `EStatus Status = EStatus::Error;`

#### struct `UE::DerivedData::FLegacyCacheDeleteRequest`  
`struct FLegacyCacheDeleteRequest`  
_L162-171_
- L164 _public member_ `FSharedString Name;`
- L165 _public member_ `FLegacyCacheKey Key;`
- L166 _public member_ `ECachePolicy Policy = ECachePolicy::Default;`
- L167 _public member_ `bool bTransient = false;`
- L168 _public member_ `uint64 UserData = 0;`
- L170 _public prototype_ `FLegacyCacheDeleteResponse MakeResponse(EStatus Status) const;`

#### struct `UE::DerivedData::FLegacyCacheDeleteResponse`  
`struct FLegacyCacheDeleteResponse`  
_L173-179_
- L175 _public member_ `FSharedString Name;`
- L176 _public member_ `FLegacyCacheKey Key;`
- L177 _public member_ `uint64 UserData = 0;`
- L178 _public member_ `EStatus Status = EStatus::Error;`

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace DerivedData` (scope `UE`)
- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace DerivedData` (scope `UE`)
- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace DerivedData` (scope `UE`)
- L17 _namespace_ `namespace UE`
- L17 _namespace_ `namespace DerivedData` (scope `UE`)
- L18 _namespace_ `namespace UE`
- L18 _namespace_ `namespace DerivedData` (scope `UE`)
- L19 _namespace_ `namespace UE`
- L19 _namespace_ `namespace DerivedData` (scope `UE`)
- L20 _namespace_ `namespace UE`
- L20 _namespace_ `namespace DerivedData` (scope `UE`)
- L21 _namespace_ `namespace UE`
- L21 _namespace_ `namespace DerivedData` (scope `UE`)
- L21 _namespace_ `namespace Private` (scope `UE::DerivedData`)
- L23 _namespace_ `namespace UE`
- L23 _namespace_ `namespace DerivedData` (scope `UE`)
- L26 _typedef_ `using FOnLegacyCachePutComplete = TUniqueFunction<void (FLegacyCachePutResponse&& Response)>;` (scope `UE::DerivedData`)
- L27 _typedef_ `using FOnLegacyCacheGetComplete = TUniqueFunction<void (FLegacyCacheGetResponse&& Response)>;` (scope `UE::DerivedData`)
- L28 _typedef_ `using FOnLegacyCacheDeleteComplete = TUniqueFunction<void (FLegacyCacheDeleteResponse&& Response)>;` (scope `UE::DerivedData`)

### `Source/Developer/DerivedDataCache/Private/DerivedDataPrivate.h` (Private)


#### Free symbols / members of external scopes

- L8 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogDerivedDataCache, Log, All);`
- L8 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogDerivedDataCache, Log, All);`
- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace DerivedData` (scope `UE`)
- L13 _prototype_ `LLM_DECLARE_TAG(DerivedData);` (scope `UE::DerivedData`)
- L14 _prototype_ `LLM_DECLARE_TAG(DerivedDataBuild);` (scope `UE::DerivedData`)
- L15 _prototype_ `LLM_DECLARE_TAG(DerivedDataCache);` (scope `UE::DerivedData`)

### `Source/Developer/DerivedDataCache/Private/HashingArchiveProxy.h` (Private)
_(no declarations extracted)_

### `Source/Developer/DerivedDataCache/Private/MemoryCacheStore.h` (Private)


#### class `UE::DerivedData::IMemoryCacheStore`  
`class IMemoryCacheStore : public ILegacyCacheStore`  
_L10-17_
- inherits: `ILegacyCacheStore`
- L13 _public prototype_ `virtual void Delete(const FCacheKey& Key, const FSharedString& Name) = 0;`
- L14 _public prototype_ `virtual void DeleteValue(const FCacheKey& Key, const FSharedString& Name) = 0;`
- L16 _public prototype_ `virtual void Disable() = 0;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace DerivedData` (scope `UE`)

### `Source/Developer/DerivedDataCache/Private/PakFileCacheStore.h` (Private)


#### class `UE::DerivedData::IPakFileCacheStore`  
`class IPakFileCacheStore : public ILegacyCacheStore`  
_L11-22_
- inherits: `ILegacyCacheStore`
- L14 _public prototype_ `virtual void Close() = 0;`
- L15 _public prototype_ `virtual bool IsWritable() const = 0;`
- L16 _public prototype_ `virtual bool SaveCache() = 0;`
- L17 _public prototype_ `virtual bool LoadCache(const TCHAR* InFilename) = 0;`
- L18 _public prototype_ `virtual void MergeCache(IPakFileCacheStore* OtherPak) = 0;`
- L19 _public prototype_ `virtual const FString& GetFilename() const = 0;`
- L21 _public prototype_ `static bool SortAndCopy(const FString& InputFilename, const FString& OutputFilename);`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace DerivedData` (scope `UE`)

### `Source/Developer/DerivedDataCache/Public/DDCCleanup.h` (Public)


#### class `IDDCCleanup`  
`class IDDCCleanup`  
_L5-11_
- L8 _public prototype_ `virtual ~IDDCCleanup() = default;`
- L9 _public prototype_ `virtual bool IsFinished() const = 0;`
- L10 _public prototype_ `virtual void WaitBetweenDeletes(bool bWait) = 0;`

### `Source/Developer/DerivedDataCache/Public/DerivedDataBuild.h` (Public)


#### class `UE::DerivedData::IBuild`  
`class IBuild`  
_L44-115_
- desc: Interface to the build system. Executing a build typically requires a definition, input resolver, session, and function. Use IBuild::CreateDefinition() to make a new build definition, or use IBuild::LoadDefinition() to load a build definition that was previously saved. This references the function to execute, and the inputs needed by the function. Use IBuild::CreateSession() to make a new build session with a build input resolver to resolve input references into the referenced data. Use FBuildSession::Build() to schedule a definition to build, along with any of its transitive build dependencies. Implement a IBuildFunction, with a unique name and version, to add values to the build context based on constants and inputs in the context. Use TBuildFunctionFactory to add the function to the registry at IBuild::GetFunctionRegistry() to allow the build job to find it.
- L47 _public prototype_ `virtual ~IBuild() = default;`
- L55 _public prototype_ `virtual FBuildDefinitionBuilder CreateDefinition(const FSharedString& Name, const FUtf8SharedString& Function) = 0;` — Create a build definition builder. @param Name       The name by which to identify this definition for logging and profiling. @param Function   The name of the build function with which to build this definition.
- L63 _public prototype_ `virtual FBuildActionBuilder CreateAction(const FSharedString& Name, const FUtf8SharedString& Function) = 0;` — Create a build action builder. @param Name       The name by which to identify this action for logging and profiling. @param Function   The name of the build function that produced this action.
- L70 _public prototype_ `virtual FBuildInputsBuilder CreateInputs(const FSharedString& Name) = 0;` — Create a build inputs builder. @param Name   The name by which to identify the inputs for logging and profiling.
- L78 _public prototype_ `virtual FBuildOutputBuilder CreateOutput(const FSharedString& Name, const FUtf8SharedString& Function) = 0;` — Create a build output builder. @param Name       The name by which to identify this output for logging and profiling. @param Function   The name of the build function that produced this output.
- L92 _public prototype_ `virtual FBuildSession CreateSession( const FSharedString& Name, IBuildInputResolver* InputResolver = nullptr, IBuildScheduler* Scheduler = nullptr) = 0;` — Create a build session. An input resolver is required for the session to perform builds with unresolved inputs, or to resolve build value keys. A default scheduler is used if one is not provided. Using the default is recommended. @param Name            The name by which to identify this session for logging and profiling. @param InputResolver   The input resolver to resolve inputs for requested builds. Optional. @param Scheduler       The scheduler for builds created through the session. Optional.
- L104 _public prototype_ `virtual const FGuid& GetVersion() const = 0;` — Returns the version of the build system. This version is expected to change very infrequently, only when formats and protocols used by the build system are changed in a way that breaks compatibility. This version is incorporated into build actions to keep the build output separate for different build versions.
- L109 _public prototype_ `virtual IBuildFunctionRegistry& GetFunctionRegistry() const = 0;` — Returns the build function registry used by the build system.
- L114 _public prototype_ `virtual IBuildWorkerRegistry& GetWorkerRegistry() const = 0;` — Returns the build worker registry used by the build system.

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API DERIVEDDATACACHE_API`
- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace DerivedData` (scope `UE`)
- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace DerivedData` (scope `UE`)
- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace DerivedData` (scope `UE`)
- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace DerivedData` (scope `UE`)
- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace DerivedData` (scope `UE`)
- L17 _namespace_ `namespace UE`
- L17 _namespace_ `namespace DerivedData` (scope `UE`)
- L18 _namespace_ `namespace UE`
- L18 _namespace_ `namespace DerivedData` (scope `UE`)
- L19 _namespace_ `namespace UE`
- L19 _namespace_ `namespace DerivedData` (scope `UE`)
- L20 _namespace_ `namespace UE`
- L20 _namespace_ `namespace DerivedData` (scope `UE`)
- L22 _namespace_ `namespace UE`
- L22 _namespace_ `namespace DerivedData` (scope `UE`)
- L24 _namespace_ `namespace UE`
- L24 _namespace_ `namespace DerivedData` (scope `UE`)
- L118 _prototype_ `IBuild& GetBuild();` (scope `UE::DerivedData`) — Returns a reference to the build system. Asserts if not available.

### `Source/Developer/DerivedDataCache/Public/DerivedDataBuildAction.h` (Public)


#### class `UE::DerivedData::Private::IBuildActionInternal`  
`class IBuildActionInternal`  
_L29-45_
- L32 _public prototype_ `virtual ~IBuildActionInternal() = default;`
- L33 _public prototype_ `virtual const FBuildActionKey& GetKey() const = 0;`
- L34 _public prototype_ `virtual const FSharedString& GetName() const = 0;`
- L35 _public prototype_ `virtual const FUtf8SharedString& GetFunction() const = 0;`
- L36 _public prototype_ `virtual const FGuid& GetFunctionVersion() const = 0;`
- L37 _public prototype_ `virtual const FGuid& GetBuildSystemVersion() const = 0;`
- L38 _public prototype_ `virtual bool HasConstants() const = 0;`
- L39 _public prototype_ `virtual bool HasInputs() const = 0;`
- L40 _public prototype_ `virtual void IterateConstants(TFunctionRef<void (FUtf8StringView Key, FCbObject&& Value)> Visitor) const = 0;`
- L41 _public prototype_ `virtual void IterateInputs(TFunctionRef<void (FUtf8StringView Key, const FIoHash& RawHash, uint64 RawSize)> Visitor) const = 0;`
- L42 _public prototype_ `virtual void Save(FCbWriter& Writer) const = 0;`
- L43 _public prototype_ `virtual void AddRef() const = 0;`
- L44 _public prototype_ `virtual void Release() const = 0;`

#### class `UE::DerivedData::Private::IBuildActionBuilderInternal`  
`class IBuildActionBuilderInternal`  
_L49-56_
- L52 _public prototype_ `virtual ~IBuildActionBuilderInternal() = default;`
- L53 _public prototype_ `virtual void AddConstant(FUtf8StringView Key, const FCbObject& Value) = 0;`
- L54 _public prototype_ `virtual void AddInput(FUtf8StringView Key, const FIoHash& RawHash, uint64 RawSize) = 0;`
- L55 _public prototype_ `virtual FBuildAction Build() = 0;`

#### class `UE::DerivedData::FBuildAction`  
`class FBuildAction`  
_L79-141_
- desc: A build action is an immutable reference to a build function and its inputs. The purpose of an action is to capture everything required to execute a derived data build for a fixed version of the build function and its constants and inputs. The key for the action uniquely identifies the action and is derived by hashing the serialized compact binary representation of the action. The keys for constants and inputs are names that are unique within the build action. @see FBuildDefinition @see FBuildSession
- L83 _public function_ `inline const FBuildActionKey& GetKey() const` — Returns the key that uniquely identifies this build action.
- L86 _public function_ `inline const FSharedString& GetName() const` — Returns the name by which to identify this action for logging and profiling.
- L89 _public function_ `inline const FUtf8SharedString& GetFunction() const` — Returns the name of the build function with which to build this action.
- L92 _public function_ `inline bool HasConstants() const` — Returns whether the action has any constants.
- L95 _public function_ `inline bool HasInputs() const` — Returns whether the action has any inputs.
- L98 _public function_ `inline const FGuid& GetFunctionVersion() const` — Returns the version of the build function with which to build this action.
- L101 _public function_ `inline const FGuid& GetBuildSystemVersion() const` — Returns the version of the build system required to build this action.
- L104 _public function_ `inline void IterateConstants(TFunctionRef<void (FUtf8StringView Key, FCbObject&& Value)> Visitor) const` — Visits every constant in order by key. The key view is valid for the lifetime of the action.
- L110 _public function_ `inline void IterateInputs(TFunctionRef<void (FUtf8StringView Key, const FIoHash& RawHash, uint64 RawSize)> Visitor) const` — Visits every input in order by key. The key view is valid for the lifetime of the action.
- L116 _public function_ `inline void Save(FCbWriter& Writer) const` — Saves the build action to a compact binary object. Calls BeginObject and EndObject.
- L128 _public prototype_ `static FOptionalBuildAction Load(const FSharedString& Name, FCbObject&& Action);` — Load a build action from compact binary. @param Name     The name by which to identify this action for logging and profiling. @param Action   The saved action to load. @return A valid build action, or null on error.
- L135 _private function_ `inline explicit FBuildAction(Private::IBuildActionInternal* InAction) : Action(InAction)` — Construct a build action. Use Build() on a builder from IBuild::CreateAction().
- L140 _private member_ `TRefCountPtr<Private::IBuildActionInternal> Action;`

#### class `UE::DerivedData::FBuildActionBuilder`  
`class FBuildActionBuilder`  
_L150-182_
- desc: A build action builder is used to construct a build action. Create using IBuild::CreateAction() which must be given a build function name. @see FBuildAction
- L154 _public function_ `inline void AddConstant(FUtf8StringView Key, const FCbObject& Value)` — Add a constant object with a key that is unique within this action.
- L160 _public function_ `inline void AddInput(FUtf8StringView Key, const FIoHash& RawHash, uint64 RawSize)` — Add an input with a key that is unique within this action.
- L166 _public function_ `inline FBuildAction Build()` — Build a build action, which makes this builder subsequently unusable.
- L176 _private function_ `inline explicit FBuildActionBuilder(Private::IBuildActionBuilderInternal* InActionBuilder) : ActionBuilder(InActionBuilder)` — Construct a build action builder. Use IBuild::CreateAction().
- L181 _private member_ `TUniquePtr<Private::IBuildActionBuilderInternal> ActionBuilder;`

#### class `UE::DerivedData::FOptionalBuildAction`  
`class FOptionalBuildAction : private FBuildAction`  
_L189-208_
- inherits: `FBuildAction`
- desc: A build action that can be null. @see FBuildAction
- L192 _public function_ `inline FOptionalBuildAction() : FBuildAction(nullptr)`
- L194 _public function_ `inline FOptionalBuildAction(FBuildAction&& InAction) : FBuildAction(MoveTemp(InAction))`
- L195 _public function_ `inline FOptionalBuildAction(const FBuildAction& InAction) : FBuildAction(InAction)`
- L196 _public function_ `inline FOptionalBuildAction& operator=(FBuildAction&& InAction)`
- L197 _public function_ `inline FOptionalBuildAction& operator=(const FBuildAction& InAction)`
- L200 _public function_ `inline const FBuildAction& Get() const &` — Returns the build action. The caller must check for null before using this accessor.
- L201 _public function_ `inline FBuildAction Get() &&`
- L203 _public function_ `inline bool IsNull() const`
- L204 _public function_ `inline bool IsValid() const`
- L205 _public function_ `inline explicit operator bool() const`
- L207 _public function_ `inline void Reset()`

#### Free symbols / members of external scopes

- L14 _macro_ `#define UE_API DERIVEDDATACACHE_API`
- L21 _namespace_ `namespace UE`
- L21 _namespace_ `namespace DerivedData` (scope `UE`)
- L22 _namespace_ `namespace UE`
- L22 _namespace_ `namespace DerivedData` (scope `UE`)
- L23 _namespace_ `namespace UE`
- L23 _namespace_ `namespace DerivedData` (scope `UE`)
- L24 _namespace_ `namespace UE`
- L24 _namespace_ `namespace DerivedData` (scope `UE`)
- L26 _namespace_ `namespace UE`
- L26 _namespace_ `namespace DerivedData` (scope `UE`)
- L26 _namespace_ `namespace Private` (scope `UE::DerivedData`)
- L47 _prototype_ `FBuildAction CreateBuildAction(IBuildActionInternal* Action);` (scope `UE::DerivedData::Private`)
- L58 _prototype_ `FBuildActionBuilder CreateBuildActionBuilder(IBuildActionBuilderInternal* ActionBuilder);` (scope `UE::DerivedData::Private`)
- L62 _namespace_ `namespace UE`
- L62 _namespace_ `namespace DerivedData` (scope `UE`)

### `Source/Developer/DerivedDataCache/Public/DerivedDataBuildDefinition.h` (Public)


#### class `UE::DerivedData::Private::IBuildDefinitionInternal`  
`class IBuildDefinitionInternal`  
_L30-47_
- L33 _public prototype_ `virtual ~IBuildDefinitionInternal() = default;`
- L34 _public prototype_ `virtual const FBuildKey& GetKey() const = 0;`
- L35 _public prototype_ `virtual const FSharedString& GetName() const = 0;`
- L36 _public prototype_ `virtual const FUtf8SharedString& GetFunction() const = 0;`
- L37 _public prototype_ `virtual bool HasConstants() const = 0;`
- L38 _public prototype_ `virtual bool HasInputs() const = 0;`
- L39 _public prototype_ `virtual void IterateConstants(TFunctionRef<void (FUtf8StringView Key, FCbObject&& Value)> Visitor) const = 0;`
- L40 _public prototype_ `virtual void IterateInputBuilds(TFunctionRef<void (FUtf8StringView Key, const FBuildValueKey& ValueKey)> Visitor) const = 0;`
- L41 _public prototype_ `virtual void IterateInputBulkData(TFunctionRef<void (FUtf8StringView Key, const FGuid& BulkDataId)> Visitor) const = 0;`
- L42 _public prototype_ `virtual void IterateInputFiles(TFunctionRef<void (FUtf8StringView Key, FUtf8StringView Path)> Visitor) const = 0;`
- L43 _public prototype_ `virtual void IterateInputHashes(TFunctionRef<void (FUtf8StringView Key, const FIoHash& RawHash)> Visitor) const = 0;`
- L44 _public prototype_ `virtual void Save(FCbWriter& Writer) const = 0;`
- L45 _public prototype_ `virtual void AddRef() const = 0;`
- L46 _public prototype_ `virtual void Release() const = 0;`

#### class `UE::DerivedData::Private::IBuildDefinitionBuilderInternal`  
`class IBuildDefinitionBuilderInternal`  
_L51-61_
- L54 _public prototype_ `virtual ~IBuildDefinitionBuilderInternal() = default;`
- L55 _public prototype_ `virtual void AddConstant(FUtf8StringView Key, const FCbObject& Value) = 0;`
- L56 _public prototype_ `virtual void AddInputBuild(FUtf8StringView Key, const FBuildValueKey& ValueKey) = 0;`
- L57 _public prototype_ `virtual void AddInputBulkData(FUtf8StringView Key, const FGuid& BulkDataId) = 0;`
- L58 _public prototype_ `virtual void AddInputFile(FUtf8StringView Key, FUtf8StringView Path) = 0;`
- L59 _public prototype_ `virtual void AddInputHash(FUtf8StringView Key, const FIoHash& RawHash) = 0;`
- L60 _public prototype_ `virtual FBuildDefinition Build() = 0;`

#### class `UE::DerivedData::FBuildDefinition`  
`class FBuildDefinition`  
_L89-163_
- desc: A build definition is an immutable reference to a build function and its inputs. The purpose of a definition is to capture everything required to execute a derived data build. The definition is partly fixed (function name, constants, input hashes) and is partly variable (function version, build dependencies, bulk data, files), and the variable components mean the output from building the definition can vary depending on the versions of those components. The key for the definition uniquely identifies the definition using the hash of the serialized compact binary representation of the definition. The keys for constants and inputs are names that are unique within the build definition. To build a definition against a specific version of the function and inputs, queue it to build on a build session, which uses its build input provider to convert it to a build action. @see FBuildDefinitionBuilder @see FBuildSession
- L93 _public function_ `inline const FBuildKey& GetKey() const` — Returns the key that uniquely identifies this build definition.
- L96 _public function_ `inline const FSharedString& GetName() const` — Returns the name by which to identify this definition for logging and profiling.
- L99 _public function_ `inline const FUtf8SharedString& GetFunction() const` — Returns the name of the build function with which to build this definition.
- L102 _public function_ `inline bool HasConstants() const` — Returns whether the definition has any constants.
- L105 _public function_ `inline bool HasInputs() const` — Returns whether the definition has any inputs.
- L108 _public function_ `inline void IterateConstants(TFunctionRef<void (FUtf8StringView Key, FCbObject&& Value)> Visitor) const` — Visits every constant in order by key. The key view is valid for the lifetime of the definition.
- L114 _public function_ `inline void IterateInputBuilds(TFunctionRef<void (FUtf8StringView Key, const FBuildValueKey& ValueKey)> Visitor) const` — Visits every input build value in order by key. The key view is valid for the lifetime of the definition.
- L120 _public function_ `inline void IterateInputBulkData(TFunctionRef<void (FUtf8StringView Key, const FGuid& BulkDataId)> Visitor) const` — Visits every input bulk data in order by key. The key view is valid for the lifetime of the definition.
- L126 _public function_ `inline void IterateInputFiles(TFunctionRef<void (FUtf8StringView Key, FUtf8StringView Path)> Visitor) const` — Visits every input file in order by key. The key and path views are valid for the lifetime of the definition.
- L132 _public function_ `inline void IterateInputHashes(TFunctionRef<void (FUtf8StringView Key, const FIoHash& RawHash)> Visitor) const` — Visits every input hash in order by key. The key view is valid for the lifetime of the definition.
- L138 _public function_ `inline void Save(FCbWriter& Writer) const` — Saves the build definition to a compact binary object. Calls BeginObject and EndObject.
- L150 _public prototype_ `static FOptionalBuildDefinition Load(const FSharedString& Name, FCbObject&& Definition);` — Load a build definition from compact binary. @param Name         The name by which to identify this definition for logging and profiling. @param Definition   An object saved from a build definition. Holds a reference and is cloned if not owned. @return A valid build definition, or null on error.
- L157 _private function_ `inline explicit FBuildDefinition(Private::IBuildDefinitionInternal* InDefinition) : Definition(InDefinition)` — Construct a build definition. Use Build() on a builder from IBuild::CreateDefinition().
- L162 _private member_ `TRefCountPtr<Private::IBuildDefinitionInternal> Definition;`

#### class `UE::DerivedData::FBuildDefinitionBuilder`  
`class FBuildDefinitionBuilder`  
_L172-236_
- desc: A build definition builder is used to construct a build definition. Create using IBuild::CreateDefinition() which must be given a build function name. @see FBuildDefinition
- L176 _public function_ `inline void AddConstant(FUtf8StringView Key, const FCbObject& Value)` — Add a constant object with a key that is unique within this definition.
- L182 _public function_ `inline void AddInputBuild(FUtf8StringView Key, const FBuildValueKey& ValueKey)` — Add a value from another build with a key that is unique within this definition.
- L192 _public function_ `inline void AddInputBulkData(FUtf8StringView Key, const FGuid& BulkDataId)` — Add a bulk data input with a key that is unique within this definition. @param BulkDataId   Identifier that uniquely identifies this data in the IBuildInputResolver.
- L202 _public function_ `inline void AddInputFile(FUtf8StringView Key, FUtf8StringView Path)` — Add a file input with a key that is unique within this definition. @param Path   Path to the file relative to a mounted content root.
- L212 _public function_ `inline void AddInputHash(FUtf8StringView Key, const FIoHash& RawHash)` — Add a hash input with a key that is unique within this definition. @param RawHash   Hash of the raw data that will resolve it in the IBuildInputResolver.
- L220 _public function_ `inline FBuildDefinition Build()` — Build a build definition, which makes this builder subsequently unusable.
- L230 _private function_ `inline explicit FBuildDefinitionBuilder(Private::IBuildDefinitionBuilderInternal* InDefinitionBuilder) : DefinitionBuilder(InDefinitionBuilder)` — Construct a build definition builder. Use IBuild::CreateDefinition().
- L235 _private member_ `TUniquePtr<Private::IBuildDefinitionBuilderInternal> DefinitionBuilder;`

#### class `UE::DerivedData::FOptionalBuildDefinition`  
`class FOptionalBuildDefinition : private FBuildDefinition`  
_L243-262_
- inherits: `FBuildDefinition`
- desc: A build definition that can be null. @see FBuildDefinition
- L246 _public function_ `inline FOptionalBuildDefinition() : FBuildDefinition(nullptr)`
- L248 _public function_ `inline FOptionalBuildDefinition(FBuildDefinition&& InDefinition) : FBuildDefinition(MoveTemp(InDefinition))`
- L249 _public function_ `inline FOptionalBuildDefinition(const FBuildDefinition& InDefinition) : FBuildDefinition(InDefinition)`
- L250 _public function_ `inline FOptionalBuildDefinition& operator=(FBuildDefinition&& InDefinition)`
- L251 _public function_ `inline FOptionalBuildDefinition& operator=(const FBuildDefinition& InDefinition)`
- L254 _public function_ `inline const FBuildDefinition& Get() const &` — Returns the build definition. The caller must check for null before using this accessor.
- L255 _public function_ `inline FBuildDefinition Get() &&`
- L257 _public function_ `inline bool IsNull() const`
- L258 _public function_ `inline bool IsValid() const`
- L259 _public function_ `inline explicit operator bool() const`
- L261 _public function_ `inline void Reset()`

#### Free symbols / members of external scopes

- L14 _macro_ `#define UE_API DERIVEDDATACACHE_API`
- L21 _namespace_ `namespace UE`
- L21 _namespace_ `namespace DerivedData` (scope `UE`)
- L22 _namespace_ `namespace UE`
- L22 _namespace_ `namespace DerivedData` (scope `UE`)
- L23 _namespace_ `namespace UE`
- L23 _namespace_ `namespace DerivedData` (scope `UE`)
- L24 _namespace_ `namespace UE`
- L24 _namespace_ `namespace DerivedData` (scope `UE`)
- L25 _namespace_ `namespace UE`
- L25 _namespace_ `namespace DerivedData` (scope `UE`)
- L27 _namespace_ `namespace UE`
- L27 _namespace_ `namespace DerivedData` (scope `UE`)
- L27 _namespace_ `namespace Private` (scope `UE::DerivedData`)
- L49 _prototype_ `FBuildDefinition CreateBuildDefinition(IBuildDefinitionInternal* Definition);` (scope `UE::DerivedData::Private`)
- L63 _prototype_ `FBuildDefinitionBuilder CreateBuildDefinitionBuilder(IBuildDefinitionBuilderInternal* DefinitionBuilder);` (scope `UE::DerivedData::Private`)
- L67 _namespace_ `namespace UE`
- L67 _namespace_ `namespace DerivedData` (scope `UE`)

### `Source/Developer/DerivedDataCache/Public/DerivedDataBuildFunction.h` (Public)


#### class `UE::DerivedData::IBuildFunction`  
`class IBuildFunction`  
_L40-78_
- desc: A build function is referenced by a build definition as the way to build its inputs. Functions are expected to be pure and maintain no state. Inputs are provided through the build context, and outputs are saved through the build context. Functions have a version which is used as a proxy for their code. Any code changes that affect the behavior of a function must have a corresponding change in the function version. Functions must be registered by a build function factory to be available to the build system. @see FBuildContext @see FBuildConfigContext @see TBuildFunctionFactory
- L43 _public prototype_ `virtual ~IBuildFunction() = default;`
- L46 _public prototype_ `virtual const FUtf8SharedString& GetName() const = 0;` — Returns the name of the build function, which identifies it in a build definition.
- L49 _public prototype_ `virtual FGuid GetVersion() const = 0;` — Returns the version of the build function, which must change when the function changes.
- L59 _public prototype_ `virtual void Build(FBuildContext& Context) const = 0;` — Build the output for the input in the build context. The build is complete when the function returns, unless BeginAsyncBuild has been called on the context, in which case a call to EndAsyncBuild from any thread marks the end. The build is considered to be successful unless an error was logged during its execution.
- L67 _public function_ `virtual void Configure(FBuildConfigContext& Context) const` — Configure the build based on its constants. The default configuration is to use the function name as the cache bucket, use the default cache policy, use the default build policy, and enable non-deterministic output checks.
- L77 _public function_ `virtual void CancelAsyncBuild(FBuildContext& Context) const` — Cancel an asynchronous build. This function is only called when canceling a build that has called BeginAsyncBuild, which requires this to be implemented to return only after EndAsyncBuild has been called exactly once on the given context. Due to timing, this can be called after EndAsyncBuild, and must handle that case, but will never be called unless BeginAsyncBuild has been called.

#### class `UE::DerivedData::FBuildContext`  
`class FBuildContext`  
_L81-144_
- desc: A build context provides the inputs for a build function and saves its outputs.
- L84 _public prototype_ `virtual ~FBuildContext() = default;`
- L87 _public prototype_ `virtual const FSharedString& GetName() const = 0;` — Returns the name by which to identify this build for logging and profiling.
- L90 _public prototype_ `virtual FCbObject FindConstant(FUtf8StringView Key) const = 0;` — Returns the constant with the matching key, or an object with no fields if not found.
- L93 _public prototype_ `virtual FSharedBuffer FindInput(FUtf8StringView Key) const = 0;` — Returns the input with the matching key, or a null buffer if not found.
- L100 _public prototype_ `virtual void AddMeta(FUtf8StringView Key, const FCbField& Meta) = 0;` — Adds metadata to the build output. Must have a unique non-empty alphanumeric key. Metadata is not required to be deterministic or based only on inputs.
- L103 _public prototype_ `virtual void AddValue(const FValueId& Id, const FValue& Value) = 0;` — Adds a value to the build output. Must have a non-null buffer and a unique ID.
- L104 _public prototype_ `virtual void AddValue(const FValueId& Id, const FCompressedBuffer& Buffer) = 0;`
- L105 _public prototype_ `virtual void AddValue(const FValueId& Id, const FCompositeBuffer& Buffer, uint64 BlockSize = 0) = 0;`
- L106 _public prototype_ `virtual void AddValue(const FValueId& Id, const FSharedBuffer& Buffer, uint64 BlockSize = 0) = 0;`
- L107 _public prototype_ `virtual void AddValue(const FValueId& Id, const FCbObject& Object) = 0;`
- L110 _public prototype_ `virtual void AddError(FStringView Message) = 0;` — Adds the error to the build output. Must be deterministic and based only on inputs.
- L113 _public prototype_ `virtual void AddWarning(FStringView Message) = 0;` — Adds the warning to the build output. Must be deterministic and based only on inputs.
- L116 _public prototype_ `virtual void AddMessage(FStringView Message) = 0;` — Adds the message to the build output. Must be deterministic and based only on inputs.
- L119 _public prototype_ `virtual void SetCachePolicyMask(ECachePolicy Policy) = 0;` — Overrides the cache policy mask used when writing this build in the cache.
- L122 _public prototype_ `virtual uint64 GetRequiredMemory() const = 0;` — Returns the estimated peak memory required to execute the build, excluding input size. Defaults to 0.
- L136 _public prototype_ `virtual void BeginAsyncBuild() = 0;` — Make this an asynchronous build by making the caller responsible for completing the build. This is an advanced feature that bypasses many of the safety checks for synchronous builds that validate that the build function only accesses inputs through the context. Take extra care to only consume inputs available in the build context and avoid reading global state. This may be called at most once on a build context. A function that uses this must support async cancellation by implementing CancelAsyncBuild. Once this has been called, the caller is responsible for calling EndAsyncBuild to finish this build. An async build may end from any thread, but the context is only safe to use from one thread at a time.
- L143 _public prototype_ `virtual void EndAsyncBuild() = 0;` — Mark the end of an asynchronous build. It is invalid to call any other function on the build context after calling this.

#### class `UE::DerivedData::FBuildConfigContext`  
`class FBuildConfigContext`  
_L147-202_
- desc: A build config context allows cache and build behavior to be modified based on constant inputs.
- L150 _public prototype_ `virtual ~FBuildConfigContext() = default;`
- L153 _public prototype_ `virtual const FSharedString& GetName() const = 0;` — Returns the name by which to identify this build for logging and profiling.
- L156 _public prototype_ `virtual FCbObject FindConstant(FUtf8StringView Key) const = 0;` — Returns the constant with the matching key, or an object with no fields if not found.
- L159 _public prototype_ `virtual void AddError(FStringView Message) = 0;` — Adds the error to the build output. Must be deterministic and based only on inputs.
- L162 _public prototype_ `virtual void AddWarning(FStringView Message) = 0;` — Adds the warning to the build output. Must be deterministic and based only on inputs.
- L165 _public prototype_ `virtual void AddMessage(FStringView Message) = 0;` — Adds the message to the build output. Must be deterministic and based only on inputs.
- L168 _public prototype_ `virtual void SetTypeName(const FUtf8SharedString& TypeName) = 0;` — Overrides the name of the type for the build. Defaults to the function name.
- L171 _public prototype_ `virtual void SetCacheBucket(FCacheBucket Bucket) = 0;` — Overrides the cache bucket used when reading or writing this build in the cache.
- L174 _public prototype_ `virtual ECachePolicy GetCachePolicyMask() const = 0;` — Returns the cache policy mask used when reading or writing this build in the cache.
- L183 _public prototype_ `virtual void SetCachePolicyMask(ECachePolicy Policy) = 0;` — Overrides the cache policy mask used when reading or writing this build in the cache. Allows Query and Store flags to be cleared for this build by removing them from the mask. Set the mask to the bitwise complement of the flags to be cleared: ~ECachePolicy::Remote.
- L186 _public prototype_ `virtual EBuildPolicy GetBuildPolicyMask() const = 0;` — Returns the build policy mask used when executing this build.
- L195 _public prototype_ `virtual void SetBuildPolicyMask(EBuildPolicy Policy) = 0;` — Overrides the build policy mask used when executing this build. Allows Build flags to be cleared for this build by removing them from the mask. Set the mask to the bitwise complement of the flags to be cleared: ~EBuildPolicy::BuildRemote.
- L198 _public prototype_ `virtual void SetRequiredMemory(uint64 RequiredMemory) = 0;` — Sets the estimated peak memory required to execute the build, excluding input size.
- L201 _public prototype_ `virtual void SkipDeterministicOutputCheck() = 0;` — Skips verification that this function has deterministic output.

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace DerivedData` (scope `UE`)
- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace DerivedData` (scope `UE`)
- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace DerivedData` (scope `UE`)
- L17 _namespace_ `namespace UE`
- L17 _namespace_ `namespace DerivedData` (scope `UE`)
- L18 _namespace_ `namespace UE`
- L18 _namespace_ `namespace DerivedData` (scope `UE`)
- L19 _namespace_ `namespace UE`
- L19 _namespace_ `namespace DerivedData` (scope `UE`)
- L20 _namespace_ `namespace UE`
- L20 _namespace_ `namespace DerivedData` (scope `UE`)
- L22 _namespace_ `namespace UE`
- L22 _namespace_ `namespace DerivedData` (scope `UE`)

### `Source/Developer/DerivedDataCache/Public/DerivedDataBuildFunctionFactory.h` (Public)


#### class `UE::DerivedData::IBuildFunctionFactory`  
`class IBuildFunctionFactory : public IModularFeature`  
_L13-20_
- inherits: `IModularFeature`
- desc: DO NOT USE DIRECTLY. Base for the build function factory. Use TBuildFunctionFactory.
- L16 _public member_ `static inline const FLazyName FeatureName{"Bui`
- L19 _public prototype_ `virtual const IBuildFunction& GetFunction() const = 0;` — Returns the build function associated with this factory.

#### class `UE::DerivedData::TBuildFunctionFactory`  
`template <typename FunctionType> class TBuildFunctionFactory final : public IBuildFunctionFactory`  
_L33-57_
- inherits: `IBuildFunctionFactory`
- desc: Factory that creates and registers a build function. A build function must be registered by a build function factory before it can execute a build. Register a function in the source file that implements it or in the corresponding module. Examples: static const TBuildFunctionFactory<FExampleFunction> ExampleFunctionFactory; static const TBuildFunctionFactory<TExampleFunction<FType>> ExampleFunctionFactory(Name, Version);
- L39 _public function_ `template <typename... ArgTypes> explicit TBuildFunctionFactory(ArgTypes&&... Args) : Function(Forward<ArgTypes>(Args)...)`
- L45 _public function_ `~TBuildFunctionFactory()`
- L50 _public function_ `const IBuildFunction& GetFunction() const final`
- L56 _private member_ `const FunctionType Function;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace DerivedData` (scope `UE`)

### `Source/Developer/DerivedDataCache/Public/DerivedDataBuildFunctionRegistry.h` (Public)


#### class `UE::DerivedData::IBuildFunctionRegistry`  
`class IBuildFunctionRegistry`  
_L18-29_
- desc: A build function registry maintains a collection of build functions.
- L21 _public prototype_ `virtual ~IBuildFunctionRegistry() = default;`
- L24 _public prototype_ `virtual const IBuildFunction* FindFunction(FUtf8StringView Function) const = 0;` — Find a function by name. Returns null if not found. Safe to call from a scheduled job or the main thread.
- L26 _public prototype_ `virtual FGuid FindFunctionVersion(FUtf8StringView Function) const = 0;` — Find a function version by name. Returns zero if not found. Safe to call from any thread.
- L28 _public prototype_ `virtual void IterateFunctionVersions(TFunctionRef<void(FUtf8StringView Name, const FGuid& Version)> Visitor) const = 0;` — Iterate the complete list of build function versions. Safe to call from any thread.

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace DerivedData` (scope `UE`)
- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace DerivedData` (scope `UE`)

### `Source/Developer/DerivedDataCache/Public/DerivedDataBuildInputResolver.h` (Public)


#### struct `UE::DerivedData::FBuildInputMetaByKey`  
`struct FBuildInputMetaByKey`  
_L31-39_
- desc: Metadata for build inputs with the input key.
- L34 _public member_ `FUtf8StringView Key;` — Key used to identify this input.
- L36 _public member_ `FIoHash RawHash;` — Hash of the raw (uncompressed) input.
- L38 _public member_ `uint64 RawSize = 0;` — Size of the raw (uncompressed) input in bytes.

#### struct `UE::DerivedData::FBuildInputDataByKey`  
`struct FBuildInputDataByKey`  
_L42-48_
- desc: Data for build inputs with the input key.
- L45 _public member_ `FUtf8StringView Key;` — Key used to identify this input.
- L47 _public member_ `FCompressedBuffer Data;` — Data for the input.

#### struct `UE::DerivedData::FBuildKeyResolvedParams`  
`struct FBuildKeyResolvedParams`  
_L51-61_
- desc: Parameters for the resolved callback for build definition requests.
- L54 _public member_ `FBuildKey Key;` — Key for the build definition request that resolved or was canceled.
- L60 _public member_ `EStatus Status = EStatus::Error;` — Status of the input request.

#### struct `UE::DerivedData::FBuildInputMetaResolvedParams`  
`struct FBuildInputMetaResolvedParams`  
_L64-71_
- desc: Parameters for the resolved callback for build input metadata requests.
- L67 _public member_ `TConstArrayView<FBuildInputMetaByKey> Inputs;` — All of the requested inputs sorted by key. Only available when Status is Ok.
- L70 _public member_ `EStatus Status = EStatus::Error;` — Status of the input request.

#### struct `UE::DerivedData::FBuildInputDataResolvedParams`  
`struct FBuildInputDataResolvedParams`  
_L74-81_
- desc: Parameters for the resolved callback for build input data requests.
- L77 _public member_ `TConstArrayView<FBuildInputDataByKey> Inputs;` — All of the requested inputs sorted by raw hash. Only available when Status is Ok.
- L80 _public member_ `EStatus Status = EStatus::Error;` — Status of the input request.

#### class `UE::DerivedData::IBuildInputResolver`  
`class IBuildInputResolver`  
_L84-152_
- desc: Interface to resolve references to build inputs.
- L87 _public prototype_ `virtual ~IBuildInputResolver() = default;`
- L96 _public function_ `virtual void ResolveKey( const FBuildKey& Key, IRequestOwner& Owner, FOnBuildKeyResolved&& OnResolved)` — Asynchronous request to resolve a definition from a key. @param Key          The key of the definition to resolve. @param Owner        The owner to execute the resolve request within. @param OnResolved   A required callback invoked when resolving completes or is canceled.
- L111 _public function_ `virtual void ResolveInputMeta( const FBuildDefinition& Definition, IRequestOwner& Owner, FOnBuildInputMetaResolved&& OnResolved)` — Asynchronous request to resolve metadata for the inputs from the definition. @param Definition   The definition to resolve input metadata for. @param Owner        The owner to execute the resolve request within. @param OnResolved   A required callback invoked when resolving completes or is canceled.
- L127 _public function_ `virtual void ResolveInputData( const FBuildDefinition& Definition, IRequestOwner& Owner, FOnBuildInputDataResolved&& OnResolved, FBuildInputFilter&& Filter = FBuildInputFilter())` — Asynchronous request to resolve data for the inputs from the definition. @param Definition   The definition to resolve input data for. @param Owner        The owner to execute the resolve request within. @param OnResolved   A required callback invoked when resolving completes or is canceled. @param Filter       An optional predicate to filter which input keys have data resolved.
- L144 _public function_ `virtual void ResolveInputData( const FBuildAction& Action, IRequestOwner& Owner, FOnBuildInputDataResolved&& OnResolved, FBuildInputFilter&& Filter = FBuildInputFilter())` — Asynchronous request to resolve data for the inputs from the action. @param Action       The action to resolve input data for. @param Owner        The owner to execute the resolve request within. @param OnResolved   A required callback invoked when resolving completes or is canceled. @param Filter       An optional predicate to filter which input keys have data resolved.

#### Free symbols / members of external scopes

- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace DerivedData` (scope `UE`)
- L17 _namespace_ `namespace UE`
- L17 _namespace_ `namespace DerivedData` (scope `UE`)
- L18 _namespace_ `namespace UE`
- L18 _namespace_ `namespace DerivedData` (scope `UE`)
- L19 _namespace_ `namespace UE`
- L19 _namespace_ `namespace DerivedData` (scope `UE`)
- L20 _namespace_ `namespace UE`
- L20 _namespace_ `namespace DerivedData` (scope `UE`)
- L22 _namespace_ `namespace UE`
- L22 _namespace_ `namespace DerivedData` (scope `UE`)
- L25 _typedef_ `using FBuildInputFilter = TUniqueFunction<bool (FUtf8StringView Key)>;` (scope `UE::DerivedData`)
- L26 _typedef_ `using FOnBuildInputDataResolved = TUniqueFunction<void (FBuildInputDataResolvedParams&& Params)>;` (scope `UE::DerivedData`)
- L27 _typedef_ `using FOnBuildInputMetaResolved = TUniqueFunction<void (FBuildInputMetaResolvedParams&& Params)>;` (scope `UE::DerivedData`)
- L28 _typedef_ `using FOnBuildKeyResolved = TUniqueFunction<void (FBuildKeyResolvedParams&& Params)>;` (scope `UE::DerivedData`)

### `Source/Developer/DerivedDataCache/Public/DerivedDataBuildInputs.h` (Public)


#### class `UE::DerivedData::Private::IBuildInputsInternal`  
`class IBuildInputsInternal`  
_L22-31_
- L25 _public prototype_ `virtual ~IBuildInputsInternal() = default;`
- L26 _public prototype_ `virtual const FSharedString& GetName() const = 0;`
- L27 _public prototype_ `virtual const FCompressedBuffer& FindInput(FUtf8StringView Key) const = 0;`
- L28 _public prototype_ `virtual void IterateInputs(TFunctionRef<void (FUtf8StringView Key, const FCompressedBuffer& Buffer)> Visitor) const = 0;`
- L29 _public prototype_ `virtual void AddRef() const = 0;`
- L30 _public prototype_ `virtual void Release() const = 0;`

#### class `UE::DerivedData::Private::IBuildInputsBuilderInternal`  
`class IBuildInputsBuilderInternal`  
_L35-41_
- L38 _public prototype_ `virtual ~IBuildInputsBuilderInternal() = default;`
- L39 _public prototype_ `virtual void AddInput(FUtf8StringView Key, const FCompressedBuffer& Buffer) = 0;`
- L40 _public prototype_ `virtual FBuildInputs Build() = 0;`

#### class `UE::DerivedData::FBuildInputs`  
`class FBuildInputs`  
_L57-83_
- desc: Build inputs are an immutable container of key/value pairs for the inputs to a build function. The keys for inputs are names that are unique within the build inputs. @see FBuildAction
- L61 _public function_ `inline const FSharedString& GetName() const` — Returns the name by which to identify the inputs for logging and profiling.
- L64 _public function_ `inline const FCompressedBuffer& FindInput(FUtf8StringView Key) const` — Finds an input by key, or a null buffer if not found.
- L67 _public function_ `inline void IterateInputs(TFunctionRef<void (FUtf8StringView Key, const FCompressedBuffer& Buffer)> Visitor) const` — Visits every input in order by key. The key view is valid for the lifetime of the inputs.
- L77 _private function_ `inline explicit FBuildInputs(Private::IBuildInputsInternal* InInputs) : Inputs(InInputs)` — Construct build inputs. Use Build() on a builder from IBuild::CreateInputs().
- L82 _private member_ `TRefCountPtr<Private::IBuildInputsInternal> Inputs;`

#### class `UE::DerivedData::FBuildInputsBuilder`  
`class FBuildInputsBuilder`  
_L92-118_
- desc: A build inputs builder is used to construct build inputs. Create using IBuild::CreateInputs(). @see FBuildInputs
- L96 _public function_ `inline void AddInput(FUtf8StringView Key, const FCompressedBuffer& Buffer)` — Add an input with a key that is unique within this input.
- L102 _public function_ `inline FBuildInputs Build()` — Build build inputs, which makes this builder subsequently unusable.
- L112 _private function_ `inline explicit FBuildInputsBuilder(Private::IBuildInputsBuilderInternal* InInputsBuilder) : InputsBuilder(InInputsBuilder)` — Construct a build inputs builder. Use IBuild::CreateInputs().
- L117 _private member_ `TUniquePtr<Private::IBuildInputsBuilderInternal> InputsBuilder;`

#### class `UE::DerivedData::FOptionalBuildInputs`  
`class FOptionalBuildInputs : private FBuildInputs`  
_L125-144_
- inherits: `FBuildInputs`
- desc: Build inputs that can be null. @see FBuildInputs
- L128 _public function_ `inline FOptionalBuildInputs() : FBuildInputs(nullptr)`
- L130 _public function_ `inline FOptionalBuildInputs(FBuildInputs&& InInputs) : FBuildInputs(MoveTemp(InInputs))`
- L131 _public function_ `inline FOptionalBuildInputs(const FBuildInputs& InInputs) : FBuildInputs(InInputs)`
- L132 _public function_ `inline FOptionalBuildInputs& operator=(FBuildInputs&& InInputs)`
- L133 _public function_ `inline FOptionalBuildInputs& operator=(const FBuildInputs& InInputs)`
- L136 _public function_ `inline const FBuildInputs& Get() const &` — Returns the build inputs. The caller must check for null before using this accessor.
- L137 _public function_ `inline FBuildInputs Get() &&`
- L139 _public function_ `inline bool IsNull() const`
- L140 _public function_ `inline bool IsValid() const`
- L141 _public function_ `inline explicit operator bool() const`
- L143 _public function_ `inline void Reset()`

#### Free symbols / members of external scopes

- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace DerivedData` (scope `UE`)
- L17 _namespace_ `namespace UE`
- L17 _namespace_ `namespace DerivedData` (scope `UE`)
- L19 _namespace_ `namespace UE`
- L19 _namespace_ `namespace DerivedData` (scope `UE`)
- L19 _namespace_ `namespace Private` (scope `UE::DerivedData`)
- L33 _prototype_ `FBuildInputs CreateBuildInputs(IBuildInputsInternal* Input);` (scope `UE::DerivedData::Private`)
- L43 _prototype_ `FBuildInputsBuilder CreateBuildInputsBuilder(IBuildInputsBuilderInternal* InputsBuilder);` (scope `UE::DerivedData::Private`)
- L47 _namespace_ `namespace UE`
- L47 _namespace_ `namespace DerivedData` (scope `UE`)

### `Source/Developer/DerivedDataCache/Public/DerivedDataBuildJob.h` (Public)


#### class `UE::DerivedData::IBuildJob`  
`class IBuildJob`  
_L33-54_
- desc: A build job is responsible for the execution of one build. Jobs typically proceed through each one of a sequence of states, though a state may be skipped if the action was found in the cache or if the scheduler finds duplicate jobs for a definition or an action. The job depends on the build scheduler to move it through its states. That relationship allows the scheduler more control over resources such as: memory, compute, storage, network.
- L37 _public prototype_ `virtual const FSharedString& GetName() const = 0;` — Returns the name by which to identify this job for logging and profiling.
- L39 _public prototype_ `virtual const FUtf8SharedString& GetFunction() const = 0;` — Returns the name of the function to build with, or "Unknown" if not resolved yet.
- L42 _public prototype_ `virtual ICache* GetCache() const = 0;` — Returns the cache associated with this job.
- L44 _public prototype_ `virtual IBuild& GetBuild() const = 0;` — Returns the build system associated with this job.
- L47 _public prototype_ `virtual void StepExecution() = 0;` — Called by the scheduler to continue this job on the calling thread.
- L50 _public prototype_ `virtual void SkipExecuteRemote() = 0;` — Called by the scheduler to skip remote execution and fall back to local execution if permitted.
- L53 _public prototype_ `virtual void SetOutput(const FBuildOutput& Output) = 0;` — Called by the scheduler if it has cached output compatible with the build policy.

#### struct `UE::DerivedData::FBuildJobCompleteParams`  
`struct FBuildJobCompleteParams`  
_L57-69_
- desc: Parameters for the completion callback for build jobs.
- L60 _public member_ `const IBuildJob& Job;` — Job that is complete.
- L62 _public member_ `const FCacheKey& CacheKey;` — Key for the job in the cache. Empty if the build completes before the key is assigned.
- L66 _public member_ `EBuildStatus BuildStatus{};` — Detailed status of the job.
- L68 _public member_ `EStatus Status = EStatus::Error;` — Basic status of the job.

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace DerivedData` (scope `UE`)
- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace DerivedData` (scope `UE`)
- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace DerivedData` (scope `UE`)
- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace DerivedData` (scope `UE`)
- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace DerivedData` (scope `UE`)
- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace DerivedData` (scope `UE`)
- L18 _namespace_ `namespace UE`
- L18 _namespace_ `namespace DerivedData` (scope `UE`)
- L21 _typedef_ `using FOnBuildJobComplete = TUniqueFunction<void (FBuildJobCompleteParams&& Params)>;` (scope `UE::DerivedData`)

### `Source/Developer/DerivedDataCache/Public/DerivedDataBuildKey.h` (Public)


#### struct `UE::DerivedData::FBuildKey`  
`struct FBuildKey`  
_L15-21_
- desc: A key that uniquely identifies a build definition.
- L17 _public member_ `FIoHash Hash;`
- L20 _public member_ `static const FBuildKey Empty;` — A key with a zero hash.
- L23 _member_ `inline const FBuildKey FBuildKey::Empty;`

#### struct `UE::DerivedData::FBuildActionKey`  
`struct FBuildActionKey`  
_L26-32_
- desc: A key that uniquely identifies a build action.
- L28 _public member_ `FIoHash Hash;`
- L31 _public member_ `static const FBuildActionKey Empty;` — A key with a zero hash.
- L34 _member_ `inline const FBuildActionKey FBuildActionKey::Empty;`

#### struct `UE::DerivedData::FBuildValueKey`  
`struct FBuildValueKey`  
_L37-44_
- desc: A key that uniquely identifies a value within a build output.
- L39 _public member_ `FBuildKey BuildKey;`
- L40 _public member_ `FValueId Id;`
- L43 _public member_ `static const FBuildValueKey Empty;` — A value key with an empty build key and a null value identifier.
- L46 _member_ `inline const FBuildValueKey FBuildValueKey::Empty;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace DerivedData` (scope `UE`)
- L50 _function_ `inline bool operator==(const FBuildKey& A, const FBuildKey& B)` (scope `UE::DerivedData`)
- L55 _function_ `inline bool operator!=(const FBuildKey& A, const FBuildKey& B)` (scope `UE::DerivedData`)
- L60 _function_ `inline bool operator<(const FBuildKey& A, const FBuildKey& B)` (scope `UE::DerivedData`)
- L65 _function_ `inline uint32 GetTypeHash(const FBuildKey& Key)` (scope `UE::DerivedData`)
- L71 _function_ `template <typename CharType> inline TStringBuilderBase<CharType>& operator<<(TStringBuilderBase<CharType>& Builder, const FBuildKey& Key)` (scope `UE::DerivedData`)
- L78 _function_ `inline bool operator==(const FBuildActionKey& A, const FBuildActionKey& B)` (scope `UE::DerivedData`)
- L83 _function_ `inline bool operator!=(const FBuildActionKey& A, const FBuildActionKey& B)` (scope `UE::DerivedData`)
- L88 _function_ `inline bool operator<(const FBuildActionKey& A, const FBuildActionKey& B)` (scope `UE::DerivedData`)
- L93 _function_ `inline uint32 GetTypeHash(const FBuildActionKey& Key)` (scope `UE::DerivedData`)
- L99 _function_ `template <typename CharType> inline TStringBuilderBase<CharType>& operator<<(TStringBuilderBase<CharType>& Builder, const FBuildActionKey& Key)` (scope `UE::DerivedData`)
- L106 _function_ `inline bool operator==(const FBuildValueKey& A, const FBuildValueKey& B)` (scope `UE::DerivedData`)
- L111 _function_ `inline bool operator!=(const FBuildValueKey& A, const FBuildValueKey& B)` (scope `UE::DerivedData`)
- L116 _function_ `inline bool operator<(const FBuildValueKey& A, const FBuildValueKey& B)` (scope `UE::DerivedData`)
- L123 _function_ `inline uint32 GetTypeHash(const FBuildValueKey& Key)` (scope `UE::DerivedData`)
- L129 _function_ `template <typename CharType> inline TStringBuilderBase<CharType>& operator<<(TStringBuilderBase<CharType>& Builder, const FBuildValueKey& Key)` (scope `UE::DerivedData`)

### `Source/Developer/DerivedDataCache/Public/DerivedDataBuildOutput.h` (Public)


#### class `UE::DerivedData::Private::IBuildOutputInternal`  
`class IBuildOutputInternal`  
_L35-53_
- L38 _public prototype_ `virtual ~IBuildOutputInternal() = default;`
- L39 _public prototype_ `virtual const FSharedString& GetName() const = 0;`
- L40 _public prototype_ `virtual const FUtf8SharedString& GetFunction() const = 0;`
- L41 _public prototype_ `virtual const FCbObject& GetMeta() const = 0;`
- L42 _public prototype_ `virtual bool FindMeta(FUtf8StringView Key, FCbField& OutMeta) const = 0;`
- L43 _public prototype_ `virtual const FValueWithId& GetValue(const FValueId& Id) const = 0;`
- L44 _public prototype_ `virtual TConstArrayView<FValueWithId> GetValues() const = 0;`
- L45 _public prototype_ `virtual TConstArrayView<FBuildOutputMessage> GetMessages() const = 0;`
- L46 _public prototype_ `virtual TConstArrayView<FBuildOutputLog> GetLogs() const = 0;`
- L47 _public prototype_ `virtual bool HasLogs() const = 0;`
- L48 _public prototype_ `virtual bool HasError() const = 0;`
- L49 _public prototype_ `virtual void Save(FCbWriter& Writer) const = 0;`
- L50 _public prototype_ `virtual void Save(FCacheRecordBuilder& RecordBuilder) const = 0;`
- L51 _public prototype_ `virtual void AddRef() const = 0;`
- L52 _public prototype_ `virtual void Release() const = 0;`

#### class `UE::DerivedData::Private::IBuildOutputBuilderInternal`  
`class IBuildOutputBuilderInternal`  
_L57-67_
- L60 _public prototype_ `virtual ~IBuildOutputBuilderInternal() = default;`
- L61 _public prototype_ `virtual void AddMeta(FUtf8StringView Key, const FCbField& Meta) = 0;`
- L62 _public prototype_ `virtual void AddValue(const FValueId& Id, const FValue& Value) = 0;`
- L63 _public prototype_ `virtual void AddMessage(const FBuildOutputMessage& Message) = 0;`
- L64 _public prototype_ `virtual void AddLog(const FBuildOutputLog& Log) = 0;`
- L65 _public prototype_ `virtual bool HasError() const = 0;`
- L66 _public prototype_ `virtual FBuildOutput Build() = 0;`

#### enum `UE::DerivedData::EBuildOutputMessageLevel`  
`enum class EBuildOutputMessageLevel : uint8`  
_L76-81_
- L78 _public enumerator_ `Error`
- L79 _public enumerator_ `Warning`
- L80 _public enumerator_ `Display`

#### struct `UE::DerivedData::FBuildOutputMessage`  
`struct FBuildOutputMessage`  
_L86-90_
- desc: A build output message is diagnostic output from a build function and must be deterministic.
- L88 _public member_ `FUtf8StringView Message;`
- L89 _public member_ `EBuildOutputMessageLevel Level;`

#### enum `UE::DerivedData::EBuildOutputLogLevel`  
`enum class EBuildOutputLogLevel : uint8`  
_L92-96_
- L94 _public enumerator_ `Error`
- L95 _public enumerator_ `Warning`

#### struct `UE::DerivedData::FBuildOutputLog`  
`struct FBuildOutputLog`  
_L108-113_
- desc: A build output log is a log message captured from a build function. The build function may capture every log above a certain level of verbosity, which means these have no guarantee of being deterministic. The presence of any output logs will disable caching of the build output. To allow caching of build output with warnings or errors, replace the log statements with build messages that are added to the build context.
- L110 _public member_ `FUtf8StringView Category;`
- L111 _public member_ `FUtf8StringView Message;`
- L112 _public member_ `EBuildOutputLogLevel Level;`

#### class `UE::DerivedData::FBuildOutput`  
`class FBuildOutput`  
_L122-188_
- desc: A build output is an immutable container of values, messages, and logs produced by a build. The output will not contain any values if it has any errors. The output can be requested without data, which means that the values will have null data.
- L126 _public function_ `inline const FSharedString& GetName() const` — Returns the name by which to identify this output for logging and profiling.
- L129 _public function_ `inline const FUtf8SharedString& GetFunction() const` — Returns the name of the build function that produced this output.
- L132 _public function_ `inline const FCbObject& GetMeta() const` — Returns the optional metadata.
- L135 _public function_ `inline bool FindMeta(FUtf8StringView Key, FCbField& OutMeta) const` — Finds the metadata matching the key. Returns true if found.
- L138 _public function_ `inline const FValueWithId& GetValue(const FValueId& Id) const` — Returns the value matching the ID. Null if no match. Buffer is null if skipped.
- L141 _public function_ `inline TConstArrayView<FValueWithId> GetValues() const` — Returns the values in the output in order by ID.
- L144 _public function_ `inline TConstArrayView<FBuildOutputMessage> GetMessages() const` — Returns the messages in the order that they were recorded.
- L147 _public function_ `inline TConstArrayView<FBuildOutputLog> GetLogs() const` — Returns the logs in the order that they were recorded.
- L150 _public function_ `inline bool HasLogs() const` — Returns whether the output has any logs.
- L153 _public function_ `inline bool HasError() const` — Returns whether the output has any errors.
- L156 _public function_ `void Save(FCbWriter& Writer) const` — Saves the build output to a compact binary object with values as attachments.
- L162 _public function_ `void Save(FCacheRecordBuilder& RecordBuilder) const` — Saves the build output to a cache record.
- L175 _public prototype_ `static FOptionalBuildOutput Load(const FSharedString& Name, const FUtf8SharedString& Function, const FCbObject& Output);` — Load a build output. @param Name       The name by which to identify this output for logging and profiling. @param Function   The name of the build function that produced this output. @param Output     The saved output to load. @return A valid build output, or null on error.
- L176 _public prototype_ `static FOptionalBuildOutput Load(const FSharedString& Name, const FUtf8SharedString& Function, const FCacheRecord& Output);`
- L182 _private function_ `inline explicit FBuildOutput(Private::IBuildOutputInternal* InOutput) : Output(InOutput)`
- L187 _private member_ `TRefCountPtr<Private::IBuildOutputInternal> Output;`

#### class `UE::DerivedData::FBuildOutputBuilder`  
`class FBuildOutputBuilder`  
_L197-247_
- desc: A build output builder is used to construct a build output. Create using IBuild::CreateOutput(). @see FBuildOutput
- L201 _public function_ `inline void AddMeta(FUtf8StringView Key, const FCbField& Meta)` — Add metadata to the output. The key must be unique in this output.
- L207 _public function_ `inline void AddValue(const FValueId& Id, const FValue& Value)` — Add a value to the output. The ID must be unique in this output.
- L213 _public function_ `inline void AddMessage(const FBuildOutputMessage& Message)` — Add a message to the output.
- L219 _public function_ `inline void AddLog(const FBuildOutputLog& Log)` — Add a log to the output.
- L225 _public function_ `inline bool HasError() const` — Returns whether the output has any errors.
- L231 _public function_ `inline FBuildOutput Build()` — Build a build output, which makes this builder subsequently unusable.
- L241 _private function_ `inline explicit FBuildOutputBuilder(Private::IBuildOutputBuilderInternal* InOutputBuilder) : OutputBuilder(InOutputBuilder)` — Construct a build output builder. Use IBuild::CreateOutput().
- L246 _private member_ `TUniquePtr<Private::IBuildOutputBuilderInternal> OutputBuilder;`

#### class `UE::DerivedData::FOptionalBuildOutput`  
`class FOptionalBuildOutput : private FBuildOutput`  
_L254-273_
- inherits: `FBuildOutput`
- desc: A build output that can be null. @see FBuildOutput
- L257 _public function_ `inline FOptionalBuildOutput() : FBuildOutput(nullptr)`
- L259 _public function_ `inline FOptionalBuildOutput(FBuildOutput&& InOutput) : FBuildOutput(MoveTemp(InOutput))`
- L260 _public function_ `inline FOptionalBuildOutput(const FBuildOutput& InOutput) : FBuildOutput(InOutput)`
- L261 _public function_ `inline FOptionalBuildOutput& operator=(FBuildOutput&& InOutput)`
- L262 _public function_ `inline FOptionalBuildOutput& operator=(const FBuildOutput& InOutput)`
- L265 _public function_ `inline const FBuildOutput& Get() const &` — Returns the build output. The caller must check for null before using this accessor.
- L266 _public function_ `inline FBuildOutput Get() &&`
- L268 _public function_ `inline bool IsNull() const`
- L269 _public function_ `inline bool IsValid() const`
- L270 _public function_ `inline explicit operator bool() const`
- L272 _public function_ `inline void Reset()`

#### Free symbols / members of external scopes

- L15 _macro_ `#define UE_API DERIVEDDATACACHE_API`
- L21 _namespace_ `namespace UE`
- L21 _namespace_ `namespace DerivedData` (scope `UE`)
- L22 _namespace_ `namespace UE`
- L22 _namespace_ `namespace DerivedData` (scope `UE`)
- L23 _namespace_ `namespace UE`
- L23 _namespace_ `namespace DerivedData` (scope `UE`)
- L24 _namespace_ `namespace UE`
- L24 _namespace_ `namespace DerivedData` (scope `UE`)
- L25 _namespace_ `namespace UE`
- L25 _namespace_ `namespace DerivedData` (scope `UE`)
- L26 _namespace_ `namespace UE`
- L26 _namespace_ `namespace DerivedData` (scope `UE`)
- L27 _namespace_ `namespace UE`
- L27 _namespace_ `namespace DerivedData` (scope `UE`)
- L28 _namespace_ `namespace UE`
- L28 _namespace_ `namespace DerivedData` (scope `UE`)
- L29 _namespace_ `namespace UE`
- L29 _namespace_ `namespace DerivedData` (scope `UE`)
- L30 _namespace_ `namespace UE`
- L30 _namespace_ `namespace DerivedData` (scope `UE`)
- L32 _namespace_ `namespace UE`
- L32 _namespace_ `namespace DerivedData` (scope `UE`)
- L32 _namespace_ `namespace Private` (scope `UE::DerivedData`)
- L55 _prototype_ `FBuildOutput CreateBuildOutput(IBuildOutputInternal* Output);` (scope `UE::DerivedData::Private`)
- L69 _prototype_ `FBuildOutputBuilder CreateBuildOutputBuilder(IBuildOutputBuilderInternal* OutputBuilder);` (scope `UE::DerivedData::Private`)
- L73 _namespace_ `namespace UE`
- L73 _namespace_ `namespace DerivedData` (scope `UE`)
- L83 _prototype_ `FUtf8StringBuilderBase& operator<<(FUtf8StringBuilderBase& Builder, EBuildOutputMessageLevel Level);` (scope `UE::DerivedData`)
- L98 _prototype_ `FUtf8StringBuilderBase& operator<<(FUtf8StringBuilderBase& Builder, EBuildOutputLogLevel Level);` (scope `UE::DerivedData`)

### `Source/Developer/DerivedDataCache/Public/DerivedDataBuildScheduler.h` (Public)


#### class `UE::DerivedData::IBuildScheduler`  
`class IBuildScheduler`  
_L28-35_
- desc: A build scheduler is responsible for deciding when and where a job executes in certain states. Jobs dispatch themselves to their scheduler when they are prepared to access limited resources such as: memory, compute, storage, network. A scheduler may allow a job to execute immediately or may queue it to execute later. A scheduler that uses a job queue is expected to execute the jobs in priority order, respecting updates to priority.
- L31 _public prototype_ `virtual ~IBuildScheduler() = default;`
- L34 _public prototype_ `virtual TUniquePtr<IBuildJobSchedule> BeginJob(IBuildJob& Job, IRequestOwner& Owner) = 0;` — Begin processing of the job by this scheduler. Always paired with IBuildJobSchedule::EndJob.

#### struct `UE::DerivedData::FBuildSchedulerParams`  
`struct FBuildSchedulerParams`  
_L38-58_
- desc: Parameters that describe a build job to the build scheduler.
- L41 _public member_ `FUtf8SharedString TypeName;` — Type name from the build function for the job. Available from the CacheQuery state onward.
- L44 _public member_ `FBuildActionKey Key;` — Available from the CacheQuery state onward.
- L47 _public member_ `uint64 TotalInputsSize = 0;` — Total size of constants and inputs, whether resolved or not.
- L49 _public member_ `uint64 ResolvedInputsSize = 0;` — Total size of constants and resolved inputs that are in memory now.
- L52 _public member_ `uint64 MissingLocalInputsSize = 0;` — Total size of inputs that need to be resolved for local execution. Available in ResolveInputData.
- L54 _public member_ `uint64 MissingRemoteInputsSize = 0;` — Total size of inputs that need to be resolved for remote execution. Available in ResolveInputData.
- L57 _public member_ `uint64 TotalRequiredMemory = 0;` — Estimate of the peak memory required to execute the build, including constants and inputs.

#### class `UE::DerivedData::IBuildJobSchedule`  
`class IBuildJobSchedule`  
_L61-89_
- desc: Scheduling interface and context for a build job.
- L64 _public prototype_ `virtual ~IBuildJobSchedule() = default;`
- L66 _public prototype_ `virtual FBuildSchedulerParams& EditParameters() = 0;`
- L69 _public prototype_ `virtual void ScheduleCacheQuery() = 0;` — Calls StepExecution() now or later.
- L71 _public prototype_ `virtual void ScheduleCacheStore() = 0;` — Calls StepExecution() now or later.
- L73 _public prototype_ `virtual void ScheduleResolveKey() = 0;` — Calls StepExecution() now or later.
- L75 _public prototype_ `virtual void ScheduleResolveInputMeta() = 0;` — Calls StepExecution() now or later.
- L81 _public prototype_ `virtual void ScheduleResolveInputData() = 0;` — Calls StepExecution() or SkipExecuteRemote() now or later. SkipExecuteRemote() won't be called unless MissingRemoteInputsSize is non-zero.
- L83 _public prototype_ `virtual void ScheduleExecuteRemote() = 0;` — Calls StepExecution() or SkipExecuteRemote() now or later.
- L85 _public prototype_ `virtual void ScheduleExecuteLocal() = 0;` — Calls StepExecution() now or later.
- L88 _public prototype_ `virtual void EndJob() = 0;` — End processing of the job by this scheduler. Always paired with IBuildScheduler::BeginJob.

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace DerivedData` (scope `UE`)
- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace DerivedData` (scope `UE`)
- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace DerivedData` (scope `UE`)
- L17 _namespace_ `namespace UE`
- L17 _namespace_ `namespace DerivedData` (scope `UE`)

### `Source/Developer/DerivedDataCache/Public/DerivedDataBuildSchedulerQueue.h` (Public)


#### class `UE::DerivedData::IBuildSchedulerTypeQueue`  
`class IBuildSchedulerTypeQueue : public IModularFeature`  
_L23-34_
- inherits: `IModularFeature`
- desc: Allows execution of a build to be queued in a type-specific way. At most one instance of this feature may be registered for each type name. Builds are queued before they query the cache, or equivalent if the cache query is skipped. The completion callback will capture the FExecutionResourceContext until the end of the build.
- L26 _public member_ `static inline const FLazyName FeatureName{"Bui`
- L28 _public prototype_ `virtual ~IBuildSchedulerTypeQueue() = default;`
- L31 _public prototype_ `virtual const FUtf8SharedString& GetTypeName() const = 0;` — Returns the type name that this provider corresponds to.
- L33 _public prototype_ `virtual void Queue(IRequestOwner& Owner, TUniqueFunction<void ()>&& OnComplete) = 0;`

#### class `UE::DerivedData::IBuildSchedulerMemoryQueue`  
`class IBuildSchedulerMemoryQueue : public IModularFeature`  
_L43-51_
- inherits: `IModularFeature`
- desc: Allows execution of a build to be queued until there is sufficient memory available. At most one instance of this feature may be registered. Builds are queued before they load input data for local execution of the build. The completion callback will capture the FExecutionResourceContext until the end of the build.
- L46 _public member_ `static inline const FLazyName FeatureName{"Bui`
- L48 _public prototype_ `virtual ~IBuildSchedulerMemoryQueue() = default;`
- L50 _public prototype_ `virtual void Reserve(uint64 Memory, IRequestOwner& Owner, TUniqueFunction<void ()>&& OnComplete) = 0;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace DerivedData` (scope `UE`)
- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace DerivedData` (scope `UE`)

### `Source/Developer/DerivedDataCache/Public/DerivedDataBuildSession.h` (Public)


#### class `UE::DerivedData::Private::IBuildSessionInternal`  
`class IBuildSessionInternal`  
_L22-44_
- L25 _public prototype_ `virtual ~IBuildSessionInternal() = default;`
- L26 _public prototype_ `virtual const FSharedString& GetName() const = 0;`
- L27 _public prototype_ `virtual void Build( const FBuildKey& Key, const FBuildPolicy& Policy, IRequestOwner& Owner, FOnBuildComplete&& OnComplete) = 0;`
- L32 _public prototype_ `virtual void Build( const FBuildDefinition& Definition, const FOptionalBuildInputs& Inputs, const FBuildPolicy& Policy, IRequestOwner& Owner, FOnBuildComplete&& OnComplete) = 0;`
- L38 _public prototype_ `virtual void Build( const FBuildAction& Action, const FOptionalBuildInputs& Inputs, const FBuildPolicy& Policy, IRequestOwner& Owner, FOnBuildComplete&& OnComplete) = 0;`

#### class `UE::DerivedData::FBuildSession`  
`class FBuildSession`  
_L60-141_
- desc: A build session is the main point to the build scheduler. The purpose of a session is to group together related builds that use the same input resolver, such as grouping builds by target platform. A request to build one definition can lead to more builds being scheduled if the definition references values from other builds as inputs.
- L64 _public function_ `inline const FSharedString& GetName() const` — Returns the name by which to identify this session for logging and profiling.
- L79 _public function_ `inline void Build( const FBuildKey& Key, const FBuildPolicy& Policy, IRequestOwner& Owner, FOnBuildComplete&& OnComplete)` — Asynchronous request to execute a build according to the policy. The callback will always be called, and may be called from an arbitrary thread. @param Key          The key of the build definition to resolve and build. @param Policy       Flags to control the behavior of the request. See FBuildPolicy. @param Owner        The owner to execute the build within. @param OnComplete   A callback invoked when the build completes or is canceled.
- L99 _public function_ `inline void Build( const FBuildDefinition& Definition, const FOptionalBuildInputs& Inputs, const FBuildPolicy& Policy, IRequestOwner& Owner, FOnBuildComplete&& OnComplete)` — Asynchronous request to execute a build according to the policy. The callback will always be called, and may be called from an arbitrary thread. @param Definition   The build function to execute and references to its inputs. @param Inputs       The build inputs referenced by the definition, if it has any. Optional. @param Policy       Flags to control the behavior of the request. See FBuildPolicy. @param Owner        The owner to execute the build within. @param OnComplete   A callback invoked when the build completes or is canceled.
- L120 _public function_ `inline void Build( const FBuildAction& Action, const FOptionalBuildInputs& Inputs, const FBuildPolicy& Policy, IRequestOwner& Owner, FOnBuildComplete&& OnComplete)` — Asynchronous request to execute a build according to the policy. The callback will always be called, and may be called from an arbitrary thread. @param Action       The build function to execute and references to its inputs. @param Inputs       The build inputs referenced by the action, if it has any. Optional. @param Policy       Flags to control the behavior of the request. See FBuildPolicy. @param Owner        The owner to execute the build within. @param OnComplete   A callback invoked when the build completes or is canceled.
- L135 _private function_ `inline explicit FBuildSession(Private::IBuildSessionInternal* InSession) : Session(InSession)` — Construct a build session. Use IBuild::CreateSession().
- L140 _private member_ `TUniquePtr<Private::IBuildSessionInternal> Session;`

#### class `UE::DerivedData::FOptionalBuildSession`  
`class FOptionalBuildSession : private FBuildSession`  
_L148-168_
- inherits: `FBuildSession`
- desc: A build session that can be null. @see FBuildSession
- L151 _public function_ `inline FOptionalBuildSession() : FBuildSession(nullptr)`
- L153 _public function_ `inline FOptionalBuildSession(FBuildSession&& InSession) : FBuildSession(MoveTemp(InSession))`
- L154 _public function_ `inline FOptionalBuildSession& operator=(FBuildSession&& InSession)`
- L156 _public prototype_ `inline FOptionalBuildSession(const FBuildSession& InSession) = delete;`
- L157 _public prototype_ `inline FOptionalBuildSession& operator=(const FBuildSession& InSession) = delete;`
- L160 _public function_ `inline FBuildSession& Get() &` — Returns the build session. The caller must check for null before using this accessor.
- L161 _public function_ `inline FBuildSession Get() &&`
- L163 _public function_ `inline bool IsNull() const`
- L164 _public function_ `inline bool IsValid() const`
- L165 _public function_ `inline explicit operator bool() const`
- L167 _public function_ `inline void Reset()`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace DerivedData` (scope `UE`)
- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace DerivedData` (scope `UE`)
- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace DerivedData` (scope `UE`)
- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace DerivedData` (scope `UE`)
- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace DerivedData` (scope `UE`)
- L17 _namespace_ `namespace UE`
- L17 _namespace_ `namespace DerivedData` (scope `UE`)
- L19 _namespace_ `namespace UE`
- L19 _namespace_ `namespace DerivedData` (scope `UE`)
- L19 _namespace_ `namespace Private` (scope `UE::DerivedData`)
- L46 _prototype_ `FBuildSession CreateBuildSession(IBuildSessionInternal* Session);` (scope `UE::DerivedData::Private`)
- L50 _namespace_ `namespace UE`
- L50 _namespace_ `namespace DerivedData` (scope `UE`)

### `Source/Developer/DerivedDataCache/Public/DerivedDataBuildTypes.h` (Public)


#### enum `UE::DerivedData::EBuildPolicy`  
`enum class EBuildPolicy : uint32`  
_L39-70_
- desc: Flags to control the behavior of build requests. The build policy flags can be combined to support a variety of usage patterns. Examples: Build(Default): allow cache get; build if missing; return every value. Build(Build | CacheStore): never query the cache; always build; return every value. Build(Cache | CacheSkipData): allow cache get; never build; skip every value. BuildValue(Default): allow cache get; build if missing; return one value. BuildValue(Build | CacheStore): never get from the cache; always build; return one value. BuildValue(Cache | CacheSkipData): allow cache get; never build; skip every value.
- L42 _public enumerator_ `None = 0` — A value without any flags set.
- L45 _public enumerator_ `BuildLocal = 1 << 0` — Allow local execution of the build function.
- L47 _public enumerator_ `BuildRemote = 1 << 1` — Allow remote execution of the build function if it has a registered build worker.
- L49 _public enumerator_ `Build = BuildLocal | BuildRemote` — Allow local and remote execution of the build function.
- L52 _public enumerator_ `CacheQuery = 1 << 2` — Allow a cache query to avoid having to build.
- L54 _public enumerator_ `CacheStoreOnQuery = 1 << 3` — Allow a cache store to persist the build output when another cache store contains it.
- L56 _public enumerator_ `CacheStoreOnBuild = 1 << 4` — Allow a cache store to persist the build output when the build function executes.
- L58 _public enumerator_ `CacheStore = CacheStoreOnQuery | CacheStoreOnBuild` — Allow a cache store to persist the build output.
- L60 _public enumerator_ `Cache = CacheQuery | CacheStore` — Allow a cache query and a cache store for the build.
- L63 _public enumerator_ `CacheKeepAlive = 1 << 5` — Keep records in the cache for at least the duration of the session.
- L66 _public enumerator_ `SkipData = 1 << 6` — Skip fetching or returning data for the values.
- L69 _public enumerator_ `Default = Build | Cache` — Allow cache query+store, allow local+remote build when missed or skipped, and fetch the value(s).

#### struct `UE::DerivedData::FBuildValuePolicy`  
`struct FBuildValuePolicy`  
_L75-79_
- desc: A value ID and the build policy to use for that value.
- L77 _public member_ `FValueId Id;`
- L78 _public member_ `EBuildPolicy Policy = EBuildPolicy::Default;`

#### class `UE::DerivedData::Private::IBuildPolicyShared`  
`class Private::IBuildPolicyShared`  
_L82-90_
- desc: Interface for the private implementation of the build policy.
- L85 _public prototype_ `virtual ~IBuildPolicyShared() = default;`
- L86 _public prototype_ `virtual void AddRef() const = 0;`
- L87 _public prototype_ `virtual void Release() const = 0;`
- L88 _public prototype_ `virtual TConstArrayView<FBuildValuePolicy> GetValuePolicies() const = 0;`
- L89 _public prototype_ `virtual void AddValuePolicy(const FBuildValuePolicy& Policy) = 0;`

#### class `UE::DerivedData::FBuildPolicy`  
`class FBuildPolicy`  
_L93-133_
- desc: Flags to control the behavior of build requests, with optional overrides by value.
- L97 _public prototype_ `FBuildPolicy() = default;` — Construct a build policy that uses the default policy.
- L100 _public function_ `inline FBuildPolicy(EBuildPolicy Policy) : CombinedPolicy(Policy) , DefaultPolicy(Policy)` — Construct a build policy with a single policy for every value.
- L107 _public function_ `inline bool IsUniform() const` — Returns true if every value uses the same build policy.
- L110 _public function_ `inline EBuildPolicy GetCombinedPolicy() const` — Returns the build policy combined from the value policies.
- L113 _public function_ `inline EBuildPolicy GetDefaultPolicy() const` — Returns the build policy to use for values with no override.
- L116 _public prototype_ `EBuildPolicy GetValuePolicy(const FValueId& Id) const;` — Returns the build policy to use for the value.
- L119 _public function_ `inline TConstArrayView<FBuildValuePolicy> GetValuePolicies() const` — Returns the array of build policy overrides for values, sorted by ID.
- L125 _public prototype_ `FBuildPolicy Transform(TFunctionRef<EBuildPolicy (EBuildPolicy)> Op) const;` — Returns a copy of this policy transformed by an operation.
- L130 _private member_ `EBuildPolicy CombinedPolicy = EBuildPolicy::Default;`
- L131 _private member_ `EBuildPolicy DefaultPolicy = EBuildPolicy::Default;`
- L132 _private member_ `TRefCountPtr<const Private::IBuildPolicyShared> Shared;`

#### class `UE::DerivedData::FBuildPolicyBuilder`  
`class FBuildPolicyBuilder`  
_L136-158_
- desc: A build policy builder is used to construct a build policy.
- L140 _public prototype_ `FBuildPolicyBuilder() = default;` — Construct a policy builder that uses the default policy.
- L143 _public function_ `inline explicit FBuildPolicyBuilder(EBuildPolicy Policy) : BasePolicy(Policy)` — Construct a policy builder that uses the provided policy for values with no override.
- L149 _public prototype_ `void AddValuePolicy(const FBuildValuePolicy& Value);` — Adds a build policy override for a value.
- L150 _public function_ `inline void AddValuePolicy(const FValueId& Id, EBuildPolicy Policy)`
- L153 _public prototype_ `FBuildPolicy Build();` — Build a build policy, which makes this builder subsequently unusable.
- L156 _private member_ `EBuildPolicy BasePolicy = EBuildPolicy::Default;`
- L157 _private member_ `TRefCountPtr<Private::IBuildPolicyShared> Shared;`

#### enum `UE::DerivedData::EBuildStatus`  
`enum class EBuildStatus : uint32`  
_L161-190_
- desc: Flags for build request completion callbacks.
- L164 _public enumerator_ `None = 0` — A value without any flags set.
- L167 _public enumerator_ `BuildLocal = 1 << 0` — The build function was executed locally.
- L169 _public enumerator_ `BuildRemote = 1 << 1` — The build function was executed remotely.
- L171 _public enumerator_ `BuildExport = 1 << 2` — The build action and inputs were exported.
- L174 _public enumerator_ `BuildTryRemote = 1 << 3` — An attempt was made to execute the build function remotely.
- L176 _public enumerator_ `BuildTryExport = 1 << 4` — An attempt was made to export the build action and inputs.
- L179 _public enumerator_ `CacheQuery = 1 << 5` — The build made a cache query request.
- L181 _public enumerator_ `CacheQueryHit = 1 << 6` — Valid build output was found in the cache.
- L184 _public enumerator_ `CacheStore = 1 << 7` — The build made a cache store request.
- L186 _public enumerator_ `CacheStoreHit = 1 << 8` — Valid build output was stored in the cache.
- L189 _public enumerator_ `CacheKey = 1 << 9` — The cache key was calculated.

#### struct `UE::DerivedData::FBuildCompleteParams`  
`struct FBuildCompleteParams`  
_L195-214_
- desc: Parameters for the completion callback for build requests.
- L198 _public member_ `const FCacheKey& CacheKey;` — Key for the build in the cache. Empty if the build completes before the key is assigned.
- L210 _public member_ `EBuildStatus BuildStatus = EBuildStatus::None;` — Detailed status of the build request.
- L213 _public member_ `EStatus Status = EStatus::Error;` — Basic status of the build request.

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API DERIVEDDATACACHE_API`
- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace DerivedData` (scope `UE`)
- L17 _namespace_ `namespace UE`
- L17 _namespace_ `namespace DerivedData` (scope `UE`)
- L18 _namespace_ `namespace UE`
- L18 _namespace_ `namespace DerivedData` (scope `UE`)
- L19 _namespace_ `namespace UE`
- L19 _namespace_ `namespace DerivedData` (scope `UE`)
- L19 _namespace_ `namespace Private` (scope `UE::DerivedData`)
- L21 _namespace_ `namespace UE`
- L21 _namespace_ `namespace DerivedData` (scope `UE`)
- L24 _typedef_ `using FOnBuildComplete = TUniqueFunction<void (FBuildCompleteParams&& Params)>;` (scope `UE::DerivedData`)
- L72 _prototype_ `ENUM_CLASS_FLAGS(EBuildPolicy);` (scope `UE::DerivedData`)
- L192 _prototype_ `ENUM_CLASS_FLAGS(EBuildStatus);` (scope `UE::DerivedData`)

### `Source/Developer/DerivedDataCache/Public/DerivedDataBuildVersion.h` (Public)


#### class `UE::DerivedData::FBuildVersionBuilder`  
`class FBuildVersionBuilder final : public FArchive`  
_L26-50_
- inherits: `FArchive`
- desc: A type that builds a build version from arbitrary values serialized to it. FGuid GetVersion() const final { FBuildVersionBuilder Builder; Builder << FGuid(TEXT("a3ae79ff-6a89-4124-afd6-dc095e000488")); Builder << ThirdPartyLibraryVersion; return Builder.Build(); }
- L29 _public prototype_ `inline FBuildVersionBuilder();`
- L31 _public prototype_ `inline FGuid Build() const;`
- L33 _public function_ `inline FString GetArchiveName() const final`
- L35 _public prototype_ `inline void Serialize(void* Data, int64 Num) final;`
- L38 _public prototype_ `FArchive& operator<<(FName& Name) final;`
- L41 _public function_ `template <typename ArgType> inline FBuildVersionBuilder& operator<<(ArgType&& Arg)`
- L49 _private member_ `FXxHash128Builder HashBuilder;`
- L52 _function_ `inline FBuildVersionBuilder::FBuildVersionBuilder()`
- L62 _function_ `inline FGuid FBuildVersionBuilder::Build() const`
- L76 _function_ `inline void FBuildVersionBuilder::Serialize(void* Data, int64 Num)`
- L81 _function_ `inline FArchive& FBuildVersionBuilder::operator<<(FName& Name)`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace DerivedData` (scope `UE`)

### `Source/Developer/DerivedDataCache/Public/DerivedDataBuildWorker.h` (Public)


#### class `UE::DerivedData::Private::IBuildWorkerBuilderInternal`  
`class IBuildWorkerBuilderInternal`  
_L42-56_
- L45 _public prototype_ `virtual ~IBuildWorkerBuilderInternal() = default;`
- L46 _public prototype_ `virtual void SetName(FUtf8StringView Name) = 0;`
- L47 _public prototype_ `virtual void SetPath(FUtf8StringView Path) = 0;`
- L48 _public prototype_ `virtual void SetHostPlatform(FUtf8StringView Name) = 0;`
- L49 _public prototype_ `virtual void SetBuildSystemVersion(const FGuid& Version) = 0;`
- L50 _public prototype_ `virtual void AddFunction(FUtf8StringView Name, const FGuid& Version) = 0;`
- L51 _public prototype_ `virtual void AddDirectory(FUtf8StringView Path) = 0;`
- L52 _public prototype_ `virtual void AddFile(FUtf8StringView Path, const FCompressedBuffer& Data) = 0;`
- L53 _public prototype_ `virtual void AddExecutable(FUtf8StringView Path, const FCompressedBuffer& Data) = 0;`
- L54 _public prototype_ `virtual void SetEnvironment(FUtf8StringView Name, FUtf8StringView Value) = 0;`
- L55 _public prototype_ `virtual FBuildWorker Build(FStringView PackagePath) = 0;`

#### struct `UE::DerivedData::FBuildWorkerKey`  
`struct FBuildWorkerKey final`  
_L67-91_
- desc: A key that uniquely identifies a build worker.
- L69 _public member_ `FIoHash Hash;`

#### class `UE::DerivedData::FBuildWorker`  
`class FBuildWorker final`  
_L104-160_
- desc: A build worker is a reference to an immutable build worker program and its dependencies. The purpose of a build worker is to capture which build functions a program contains and refer to everything required to execute the program, including files and environment. The key for the worker uniquely identifies the worker using a hash of the serialized compact binary representation of the worker. A build worker resolver is used to resolve file hashes to the referenced file data.
- L107 _public function_ `[[nodiscard]] inline FBuildWorkerKey GetKey() const`
- L112 _public prototype_ `[[nodiscard]] FUtf8StringView GetName() const;`
- L113 _public prototype_ `[[nodiscard]] FUtf8StringView GetPath() const;`
- L114 _public prototype_ `[[nodiscard]] FUtf8StringView GetHostPlatform() const;`
- L115 _public prototype_ `[[nodiscard]] FGuid GetBuildSystemVersion() const;`
- L117 _public prototype_ `void IterateFunctions(TFunctionRef<void (FUtf8StringView Name, const FGuid& Version)> Visitor) const;`
- L118 _public prototype_ `void IterateDirectories(TFunctionRef<void (FUtf8StringView Path)> Visitor) const;`
- L119 _public prototype_ `void IterateFiles(TFunctionRef<void (FUtf8StringView Path, const FIoHash& RawHash, uint64 RawSize)> Visitor) const;`
- L120 _public prototype_ `void IterateExecutables(TFunctionRef<void (FUtf8StringView Path, const FIoHash& RawHash, uint64 RawSize)> Visitor) const;`
- L121 _public prototype_ `void IterateEnvironment(TFunctionRef<void (FUtf8StringView Name, FUtf8StringView Value)> Visitor) const;`
- L124 _public prototype_ `void Resolve(TConstArrayView<FIoHash> RawHashes, IRequestOwner& Owner, FOnBuildWorkerResolved&& OnResolved) const;` — Resolves files and executables referenced by this build worker, by raw hash.
- L127 _public prototype_ `bool Extract(FStringView OutputPath) const;` — Extracts the build worker into a directory, which must be empty.
- L130 _public function_ `[[nodiscard]] inline const FCbObject& Save() const` — Saves the build worker to a compact binary object, excluding file data.
- L136 _public prototype_ `[[nodiscard]] FStringView GetPackagePath() const;` — Path to the package that this worker was loaded from. Empty when not loaded from a package.
- L139 _public prototype_ `[[nodiscard]] static TOptional<FBuildWorker> Load(FStringView PackagePath);` — Loads a build worker from a package created by FBuildWorkerBuilder::Build.
- L147 _public prototype_ `[[nodiscard]] static FBuildWorker Load(FCbObject Object, TNotNull<TUniquePtr<IBuildWorkerResolver>> Resolver);` — Loads a build worker from a compact binary object. @param Object     An object saved from a build worker. Holds a reference and is cloned if not owned. @param Resolver   A resolver used to find file data referenced by the build worker.
- L149 _public member_ `constexpr static bool bHasIntrusiveUnsetOptionalState = true;`
- L150 _public typedef_ `using IntrusiveUnsetOptionalStateType = FBuildWorker;`
- L151 _public function_ `[[nodiscard]] inline explicit FBuildWorker(FIntrusiveUnsetOptionalState)`
- L152 _public function_ `[[nodiscard]] inline bool operator==(FIntrusiveUnsetOptionalState) const`
- L155 _private prototype_ `FBuildWorker() = default;`
- L157 _private member_ `FCbObject Object;`
- L158 _private member_ `TUniquePtr<IBuildWorkerResolver> Resolver;`
- L159 _private member_ `FBuildWorkerKey Key;`

#### class `UE::DerivedData::FBuildWorkerBuilder`  
`class FBuildWorkerBuilder final`  
_L163-220_
- desc: A builder to construct a build worker.
- L166 _public prototype_ `[[nodiscard]] FBuildWorkerBuilder();`
- L168 _public function_ `inline void SetName(FUtf8StringView Name)`
- L173 _public function_ `inline void SetPath(FUtf8StringView Path)`
- L178 _public function_ `inline void SetHostPlatform(FUtf8StringView Name)`
- L183 _public function_ `inline void SetBuildSystemVersion(const FGuid& Version)`
- L188 _public function_ `inline void AddFunction(FUtf8StringView Name, const FGuid& Version)`
- L193 _public function_ `inline void AddDirectory(FUtf8StringView Path)`
- L198 _public function_ `inline void AddFile(FUtf8StringView Path, const FCompressedBuffer& Data)`
- L203 _public function_ `inline void AddExecutable(FUtf8StringView Path, const FCompressedBuffer& Data)`
- L208 _public function_ `inline void SetEnvironment(FUtf8StringView Name, FUtf8StringView Value)`
- L213 _public function_ `[[nodiscard]] inline FBuildWorker Build(FStringView PackagePath)`
- L219 _private member_ `TUniquePtr<Private::IBuildWorkerBuilderInternal> Builder;`

#### class `UE::DerivedData::IBuildWorkerResolver`  
`class IBuildWorkerResolver`  
_L223-239_
- desc: Interface to resolve file data for a build worker.
- L226 _public prototype_ `virtual ~IBuildWorkerResolver() = default;`
- L235 _public prototype_ `virtual void Resolve(TConstArrayView<FIoHash> RawHashes, IRequestOwner& Owner, FOnBuildWorkerResolved&& OnResolved) = 0;` — Resolve the compressed data for the raw hashes. @param RawHashes   The raw hashes of the data to resolve. @param Owner   Owner provides priority and manages requests when resolving is asynchronous. @param OnResolved   Called exactly once when data is resolved. May return partial results if Status is Error.
- L238 _public prototype_ `[[nodiscard]] virtual FStringView GetPackagePath() const = 0;` — Returns the path to the package that this is resolving from, or empty if not backed by a package.

#### class `UE::DerivedData::IBuildWorkerFactory`  
`class IBuildWorkerFactory : public IModularFeature`  
_L242-262_
- inherits: `IModularFeature`
- desc: Interface to create and register build workers with the build worker registry.
- L245 _public member_ `static inline const FLazyName FeatureName{"Bui`
- L247 _public prototype_ `virtual ~IBuildWorkerFactory() = default;`
- L254 _public prototype_ `virtual void CreateWorkers(IBuildWorkerRegistry& WorkerRegistry) = 0;` — Called by the build system when it is created, or when the factory is registered later. Async worker creation is allowed and must be finished before AbortCreateWorkers() returns.
- L261 _public prototype_ `virtual void AbortCreateWorkers() = 0;` — Called by the build system when it is about to be destroyed. Any async worker creation must be completed or aborted before returning from this function.

#### class `UE::DerivedData::IBuildWorkerExecutor`  
`class IBuildWorkerExecutor : public IModularFeature`  
_L265-282_
- inherits: `IModularFeature`
- desc: Interface to execute a build action using a build worker.
- L268 _public member_ `static inline const FLazyName FeatureName{"Bui`
- L270 _public prototype_ `virtual ~IBuildWorkerExecutor() = default;`
- L272 _public prototype_ `virtual void Build( const FBuildAction& Action, const FOptionalBuildInputs& Inputs, const FBuildPolicy& Policy, const FBuildWorker& Worker, IBuild& BuildSystem, IRequestOwner& Owner, FOnBuildWorkerActionComplete&& OnComplete) = 0;`
- L281 _public prototype_ `virtual TConstArrayView<FUtf8StringView> GetHostPlatforms() const = 0;`

#### struct `UE::DerivedData::FBuildWorkerActionCompleteParams`  
`struct FBuildWorkerActionCompleteParams final`  
_L284-290_
- L286 _public member_ `FBuildActionKey Key;`
- L288 _public member_ `TConstArrayView<FUtf8StringView> MissingInputs;`
- L289 _public member_ `EStatus Status = EStatus::Error;`

#### struct `UE::DerivedData::FBuildWorkerResolvedParams`  
`struct FBuildWorkerResolvedParams final`  
_L292-296_
- L294 _public member_ `TConstArrayView<FCompressedBuffer> Files;`
- L295 _public member_ `EStatus Status = EStatus::Error;`

#### Free symbols / members of external scopes

- L18 _macro_ `#define UE_API DERIVEDDATACACHE_API`
- L26 _namespace_ `namespace UE`
- L26 _namespace_ `namespace DerivedData` (scope `UE`)
- L27 _namespace_ `namespace UE`
- L27 _namespace_ `namespace DerivedData` (scope `UE`)
- L28 _namespace_ `namespace UE`
- L28 _namespace_ `namespace DerivedData` (scope `UE`)
- L29 _namespace_ `namespace UE`
- L29 _namespace_ `namespace DerivedData` (scope `UE`)
- L30 _namespace_ `namespace UE`
- L30 _namespace_ `namespace DerivedData` (scope `UE`)
- L31 _namespace_ `namespace UE`
- L31 _namespace_ `namespace DerivedData` (scope `UE`)
- L32 _namespace_ `namespace UE`
- L32 _namespace_ `namespace DerivedData` (scope `UE`)
- L33 _namespace_ `namespace UE`
- L33 _namespace_ `namespace DerivedData` (scope `UE`)
- L34 _namespace_ `namespace UE`
- L34 _namespace_ `namespace DerivedData` (scope `UE`)
- L35 _namespace_ `namespace UE`
- L35 _namespace_ `namespace DerivedData` (scope `UE`)
- L36 _namespace_ `namespace UE`
- L36 _namespace_ `namespace DerivedData` (scope `UE`)
- L37 _namespace_ `namespace UE`
- L37 _namespace_ `namespace DerivedData` (scope `UE`)
- L37 _namespace_ `namespace Private` (scope `UE::DerivedData`)
- L39 _namespace_ `namespace UE`
- L39 _namespace_ `namespace DerivedData` (scope `UE`)
- L39 _namespace_ `namespace Private` (scope `UE::DerivedData`)
- L60 _namespace_ `namespace UE`
- L60 _namespace_ `namespace DerivedData` (scope `UE`)
- L63 _typedef_ `using FOnBuildWorkerActionComplete = TUniqueFunction<void (FBuildWorkerActionCompleteParams&& Params)>;` (scope `UE::DerivedData`)
- L64 _typedef_ `using FOnBuildWorkerResolved = TUniqueFunction<void (FBuildWorkerResolvedParams&& Params)>;` (scope `UE::DerivedData`)
- L71 _function_ `friend inline bool operator==(const FBuildWorkerKey& A, const FBuildWorkerKey& B)` (scope `UE::DerivedData`)
- L76 _function_ `friend inline bool operator<(const FBuildWorkerKey& A, const FBuildWorkerKey& B)` (scope `UE::DerivedData`)
- L81 _function_ `friend inline uint32 GetTypeHash(const FBuildWorkerKey& Key)` (scope `UE::DerivedData`)
- L87 _function_ `template <typename CharType> friend inline TStringBuilderBase<CharType>& operator<<(TStringBuilderBase<CharType>& Builder, const FBuildWorkerKey& Key)` (scope `UE::DerivedData`)

### `Source/Developer/DerivedDataCache/Public/DerivedDataBuildWorkerRegistry.h` (Public)


#### class `UE::DerivedData::IBuildWorkerRegistry`  
`class IBuildWorkerRegistry`  
_L24-52_
- desc: A build worker registry maintains a collection of build workers.
- L27 _public prototype_ `virtual ~IBuildWorkerRegistry() = default;`
- L30 _public prototype_ `virtual void RegisterWorker(FBuildWorker&& Worker, TNotNull<IBuildWorkerFactory*> Factory) = 0;` — Registers a build worker and takes ownership of it.
- L41 _public prototype_ `virtual FBuildWorker* FindWorker( const FUtf8SharedString& Function, const FGuid& FunctionVersion, const FGuid& BuildSystemVersion, IBuildWorkerExecutor*& OutWorkerExecutor) const = 0;` — Finds a build worker that can execute the function at the version. @param Function            The function to find a worker for. @param FunctionVersion     The version required for the function. @param BuildSystemVersion  The version required for the build system. @param OutWorkerExecutor   The executor to use to execute the worker. @return A build worker and executor if a compatible pair was found, or null for both.
- L48 _public prototype_ `virtual FBuildWorkerBuilder CreateWorker() const = 0;` — Creates a builder to create a build worker. Load with LoadWorker.
- L51 _public prototype_ `virtual TOptional<FBuildWorker> LoadWorker(FStringView PackagePath) const = 0;` — Loads a build worker as created through CreateWorker.

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace DerivedData` (scope `UE`)
- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace DerivedData` (scope `UE`)
- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace DerivedData` (scope `UE`)
- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace DerivedData` (scope `UE`)
- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace DerivedData` (scope `UE`)
- L18 _namespace_ `namespace UE`
- L18 _namespace_ `namespace DerivedData` (scope `UE`)

### `Source/Developer/DerivedDataCache/Public/DerivedDataCache.h` (Public)


#### class `UE::DerivedData::ICache`  
`class ICache`  
_L56-133_
- desc: Interface to the cache. Functions on this interface may be called from any thread. Requests may complete out of order relative to the order that they were requested. Callbacks may be called from any thread, including the calling thread, may be called from more than one thread concurrently, and may be called before returning from the request function.
- L59 _public prototype_ `virtual ~ICache() = default;`
- L70 _public prototype_ `virtual void Put( TConstArrayView<FCachePutRequest> Requests, IRequestOwner& Owner, FOnCachePutComplete&& OnComplete = {}) = 0;` — Asynchronous request to put records in the cache. @see FCachePutRequest @param Requests     Requests with the cache records to store. Records must have a key. @param Owner        The owner to execute the request within. See IRequestOwner. @param OnComplete   A callback invoked for every request as it completes or is canceled.
- L84 _public prototype_ `virtual void Get( TConstArrayView<FCacheGetRequest> Requests, IRequestOwner& Owner, FOnCacheGetComplete&& OnComplete) = 0;` — Asynchronous request to get records from the cache. @see FCacheGetRequest @param Requests     Requests with the keys of the cache records to fetch. @param Owner        The owner to execute the request within. See IRequestOwner. @param OnComplete   A callback invoked for every request as it completes or is canceled.
- L98 _public prototype_ `virtual void PutValue( TConstArrayView<FCachePutValueRequest> Requests, IRequestOwner& Owner, FOnCachePutValueComplete&& OnComplete = {}) = 0;` — Asynchronous request to put values in the cache. @see FCachePutValueRequest @param Requests     Requests with the cache values to store. Requests must have a key. @param Owner        The owner to execute the request within. See IRequestOwner. @param OnComplete   A callback invoked for every request as it completes or is canceled.
- L112 _public prototype_ `virtual void GetValue( TConstArrayView<FCacheGetValueRequest> Requests, IRequestOwner& Owner, FOnCacheGetValueComplete&& OnComplete) = 0;` — Asynchronous request to get values from the cache. @see FCacheGetValueRequest @param Requests     Requests with the keys of the cache values to fetch. @param Owner        The owner to execute the request within. See IRequestOwner. @param OnComplete   A callback invoked for every request as it completes or is canceled.
- L126 _public prototype_ `virtual void GetChunks( TConstArrayView<FCacheGetChunkRequest> Requests, IRequestOwner& Owner, FOnCacheGetChunkComplete&& OnComplete) = 0;` — Asynchronous request to get chunks, which are subsets of values, from records or values. @see FCacheGetChunkRequest @param Requests     Requests with the key, ID, offset, and size of each chunk to fetch. @param Owner        The owner to execute the request within. See IRequestOwner. @param OnComplete   A callback invoked for every request as it completes or is canceled.
- L132 _public prototype_ `virtual ICacheStoreMaintainer& GetMaintainer() = 0;` — Returns the interface to the background cache store maintenance.

#### struct `UE::DerivedData::FCachePutRequest`  
`struct FCachePutRequest`  
_L138-154_
- desc: Parameters to request to put a cache record.
- L141 _public member_ `FSharedString Name;` — A name to identify this request for logging and profiling. An object path is typically sufficient.
- L144 _public member_ `FCacheRecord Record;` — A record to store.
- L147 _public member_ `FCacheRecordPolicy Policy = ECachePolicy::Default | ECachePolicy::SkipData;` — Flags to control the behavior of the request. See FCacheRecordPolicy.
- L150 _public member_ `uint64 UserData = 0;` — A value that will be returned in the completion callback.
- L153 _public prototype_ `FCachePutResponse MakeResponse(EStatus Status) const;` — Make a default response for this request, with the provided status.

#### struct `UE::DerivedData::FCachePutResponse`  
`struct FCachePutResponse`  
_L158-180_
- desc: Parameters for the completion callback for cache put requests.
- L161 _public member_ `FSharedString Name;` — A copy of the name from the request.
- L165 _public member_ `FCacheKey Key;` — `UE_DEPRECATED(5.8, "Access the key through Record.GetKey().")` — A copy of the key from the request.
- L173 _public member_ `FCacheRecord Record;` — A copy of the record from the request, or the conflicting record if there is one. A conflicting record is returned when the cache contains a record with the requested key that differs from the record in the request, and the request policy disallows overwrite.
- L176 _public member_ `uint64 UserData = 0;` — A copy of the value from the request.
- L179 _public member_ `EStatus Status = EStatus::Error;` — The status of the request.

#### struct `UE::DerivedData::FCacheGetRequest`  
`struct FCacheGetRequest`  
_L184-200_
- desc: Parameters to request to get a cache record.
- L187 _public member_ `FSharedString Name;` — A name to identify this request for logging and profiling. An object path is typically sufficient.
- L190 _public member_ `FCacheKey Key;` — A key identifying the record to fetch.
- L193 _public member_ `FCacheRecordPolicy Policy;` — Flags to control the behavior of the request. See FCacheRecordPolicy.
- L196 _public member_ `uint64 UserData = 0;` — A value that will be returned in the completion callback.
- L199 _public prototype_ `FCacheGetResponse MakeResponse(EStatus Status) const;` — Make a default response for this request, with the provided status.

#### struct `UE::DerivedData::FCacheGetResponse`  
`struct FCacheGetResponse`  
_L203-223_
- desc: Parameters for the completion callback for cache get requests.
- L206 _public member_ `FSharedString Name;` — A copy of the name from the request.
- L216 _public member_ `FCacheRecord Record;` — Record for the request that completed or was canceled. The key is always populated. The remainder of the record is populated when Status is Ok. The metadata or the data for values may be skipped based on cache policy flags. Values for which data has been skipped will have a hash and size but null data.
- L219 _public member_ `uint64 UserData = 0;` — A copy of the value from the request.
- L222 _public member_ `EStatus Status = EStatus::Error;` — The status of the request.

#### struct `UE::DerivedData::FCachePutValueRequest`  
`struct FCachePutValueRequest`  
_L226-245_
- desc: Parameters to request to put a cache value.
- L229 _public member_ `FSharedString Name;` — A name to identify this request for logging and profiling. An object path is typically sufficient.
- L232 _public member_ `FCacheKey Key;` — A key that will uniquely identify the value in the cache.
- L235 _public member_ `FValue Value;` — A value to store.
- L238 _public member_ `ECachePolicy Policy = ECachePolicy::Default | ECachePolicy::SkipData;` — Flags to control the behavior of the request. See ECachePolicy.
- L241 _public member_ `uint64 UserData = 0;` — A value that will be returned in the completion callback.
- L244 _public prototype_ `FCachePutValueResponse MakeResponse(EStatus Status) const;` — Make a default response for this request, with the provided status.

#### struct `UE::DerivedData::FCachePutValueResponse`  
`struct FCachePutValueResponse`  
_L248-269_
- desc: Parameters for the completion callback for cache value put requests.
- L251 _public member_ `FSharedString Name;` — A copy of the name from the request.
- L254 _public member_ `FCacheKey Key;` — A copy of the key from the request.
- L262 _public member_ `FValue Value;` — A copy of the value from the request, or the conflicting value if there is one. A conflicting value is returned when the cache contains a value with the requested key that differs from the value in the request, and the request policy disallows overwrite.
- L265 _public member_ `uint64 UserData = 0;` — A copy of the value from the request.
- L268 _public member_ `EStatus Status = EStatus::Error;` — The status of the request.

#### struct `UE::DerivedData::FCacheGetValueRequest`  
`struct FCacheGetValueRequest`  
_L272-288_
- desc: Parameters to request to get a cache value.
- L275 _public member_ `FSharedString Name;` — A name to identify this request for logging and profiling. An object path is typically sufficient.
- L278 _public member_ `FCacheKey Key;` — A key identifying the value to fetch.
- L281 _public member_ `ECachePolicy Policy = ECachePolicy::Default;` — Flags to control the behavior of the request. See ECachePolicy.
- L284 _public member_ `uint64 UserData = 0;` — A value that will be returned in the completion callback.
- L287 _public prototype_ `FCacheGetValueResponse MakeResponse(EStatus Status) const;` — Make a default response for this request, with the provided status.

#### struct `UE::DerivedData::FCacheGetValueResponse`  
`struct FCacheGetValueResponse`  
_L291-312_
- desc: Parameters for the completion callback for cache value get requests.
- L294 _public member_ `FSharedString Name;` — A copy of the name from the request.
- L297 _public member_ `FCacheKey Key;` — A copy of the key from the request.
- L305 _public member_ `FValue Value;` — Value for the request that completed or was canceled. The data may be skipped based on cache policy flags. A value for which data has been skipped will have a hash and size but null data.
- L308 _public member_ `uint64 UserData = 0;` — A copy of the value from the request.
- L311 _public member_ `EStatus Status = EStatus::Error;` — The status of the request.

#### struct `UE::DerivedData::FCacheGetChunkRequest`  
`struct FCacheGetChunkRequest`  
_L315-343_
- desc: Parameters to request a chunk, which is a subset of a value, from a cache record or cache value.
- L318 _public member_ `FSharedString Name;` — A name to identify this request for logging and profiling. An object path is typically sufficient.
- L321 _public member_ `FCacheKey Key;` — A key identifying the record or value to fetch the chunk from.
- L324 _public member_ `FValueId Id;` — An ID identifying the value to fetch, if fetching from a record, otherwise null.
- L327 _public member_ `uint64 RawOffset = 0;` — The offset into the raw bytes of the value at which to start fetching.
- L330 _public member_ `uint64 RawSize = MAX_uint64;` — The maximum number of raw bytes of the value to fetch, starting from the offset.
- L333 _public member_ `FIoHash RawHash;` — The raw hash of the entire value to fetch, if available, otherwise zero.
- L336 _public member_ `ECachePolicy Policy = ECachePolicy::Default;` — Flags to control the behavior of the request. See ECachePolicy.
- L339 _public member_ `uint64 UserData = 0;` — A value that will be returned in the completion callback.
- L342 _public prototype_ `FCacheGetChunkResponse MakeResponse(EStatus Status) const;` — Make a default response for this request, with the provided status.

#### struct `UE::DerivedData::FCacheGetChunkResponse`  
`struct FCacheGetChunkResponse`  
_L346-374_
- desc: Parameters for the completion callback for cache chunk requests.
- L349 _public member_ `FSharedString Name;` — A copy of the name from the request.
- L352 _public member_ `FCacheKey Key;` — A copy of the key from the request.
- L355 _public member_ `FValueId Id;` — A copy of the ID from the request.
- L358 _public member_ `uint64 RawOffset = 0;` — A copy of the offset from the request.
- L361 _public member_ `uint64 RawSize = 0;` — The size, in bytes, of the subset of the value that was fetched, if any.
- L364 _public member_ `FIoHash RawHash;` — The hash of the entire value, even if only a subset was fetched.
- L367 _public member_ `FSharedBuffer RawData;` — Data for the subset of the value that was fetched when Status is Ok, otherwise null.
- L370 _public member_ `uint64 UserData = 0;` — A copy of the value from the request.
- L373 _public member_ `EStatus Status = EStatus::Error;` — The status of the request.

#### Free symbols / members of external scopes

- L20 _macro_ `#define UE_API DERIVEDDATACACHE_API`
- L22 _namespace_ `namespace UE`
- L22 _namespace_ `namespace DerivedData` (scope `UE`)
- L23 _namespace_ `namespace UE`
- L23 _namespace_ `namespace DerivedData` (scope `UE`)
- L24 _namespace_ `namespace UE`
- L24 _namespace_ `namespace DerivedData` (scope `UE`)
- L25 _namespace_ `namespace UE`
- L25 _namespace_ `namespace DerivedData` (scope `UE`)
- L26 _namespace_ `namespace UE`
- L26 _namespace_ `namespace DerivedData` (scope `UE`)
- L27 _namespace_ `namespace UE`
- L27 _namespace_ `namespace DerivedData` (scope `UE`)
- L28 _namespace_ `namespace UE`
- L28 _namespace_ `namespace DerivedData` (scope `UE`)
- L29 _namespace_ `namespace UE`
- L29 _namespace_ `namespace DerivedData` (scope `UE`)
- L30 _namespace_ `namespace UE`
- L30 _namespace_ `namespace DerivedData` (scope `UE`)
- L31 _namespace_ `namespace UE`
- L31 _namespace_ `namespace DerivedData` (scope `UE`)
- L32 _namespace_ `namespace UE`
- L32 _namespace_ `namespace DerivedData` (scope `UE`)
- L33 _namespace_ `namespace UE`
- L33 _namespace_ `namespace DerivedData` (scope `UE`)
- L35 _namespace_ `namespace UE`
- L35 _namespace_ `namespace DerivedData` (scope `UE`)
- L38 _typedef_ `using FOnCachePutComplete = TUniqueFunction<void (FCachePutResponse&& Response)>;` (scope `UE::DerivedData`)
- L39 _typedef_ `using FOnCacheGetComplete = TUniqueFunction<void (FCacheGetResponse&& Response)>;` (scope `UE::DerivedData`)
- L40 _typedef_ `using FOnCachePutValueComplete = TUniqueFunction<void (FCachePutValueResponse&& Response)>;` (scope `UE::DerivedData`)
- L41 _typedef_ `using FOnCacheGetValueComplete = TUniqueFunction<void (FCacheGetValueResponse&& Response)>;` (scope `UE::DerivedData`)
- L42 _typedef_ `using FOnCacheGetChunkComplete = TUniqueFunction<void (FCacheGetChunkResponse&& Response)>;` (scope `UE::DerivedData`)
- L379 _prototype_ `ICache& GetCache();` (scope `UE::DerivedData`) — Returns a reference to the cache. Asserts if not available.
- L382 _prototype_ `ICache* TryGetCache();` (scope `UE::DerivedData`) — Returns a pointer to the cache. Null if not available or not created.
- L393 _prototype_ `UE_INTERNAL ICache* CreateCache(FStringView GraphNameOrConfig);` (scope `UE::DerivedData`) — Creates a cache from a graph name or graph config. Must be called from the main thread. Destroy the cache with operator delete. Consider using TUniquePtr. @param GraphNameOrConfig   Name of the graph in [DerivedDataCacheGraphs] or a graph config. @return A pointer to the new cache, or null if it failed to create.

### `Source/Developer/DerivedDataCache/Public/DerivedDataCacheInterface.h` (Public)


#### class `FDerivedDataCacheInterface`  
`class FDerivedDataCacheInterface`  
_L24-297_
- desc: Interface for the derived data cache This API is fully threadsafe (with the possible exception of the system interface: NotfiyBootComplete, etc).
- L27 _public prototype_ `virtual ~FDerivedDataCacheInterface() = default;`
- L39 _public prototype_ `virtual bool GetSynchronous(class FDerivedDataPluginInterface* DataDeriver, TArray<uint8>& OutData, bool* bDataWasBuilt = nullptr) = 0;` — Synchronously checks the cache and if the item is present, it returns the cached results, otherwise tells the deriver to build the data and then updates the cache @param	DataDeriver	plugin to produce cache key and in the event of a miss, return the data. @param	bDataWasBuilt if non-null, set to true if the data returned had to be built instead of retrieved from the DDC. Used for stat tracking. @return	true if the data was retrieved from the cache or the deriver built the data sucessfully. false can only occur if the plugin returns false.
- L47 _public prototype_ `virtual uint32 GetAsynchronous(class FDerivedDataPluginInterface* DataDeriver) = 0;` — Starts the async process of checking the cache and if the item is present, retrieving the cached results, otherwise telling the deriver to build the data and then updating the cache If the plugin does not support threading, all of the above will be completed before the call returns. @param	DataDeriver	plugin to produce cache key and in the event of a miss, return the data. @return	a handle that can be used for PollAsynchronousCompletion, WaitAsynchronousCompletion and GetAsynchronousResults
- L53 _public prototype_ `virtual bool PollAsynchronousCompletion(uint32 Handle) = 0;` — Polls a previous GetAsynchronous get for completion. @param	Handle	Handle returned from GetAsynchronous. @return			true if the build / retrieve is complete and the results can be obtained.
- L58 _public prototype_ `virtual void WaitAsynchronousCompletion(uint32 Handle) = 0;` — Blocks the current thread until an previous GetAsynchronous request is ready @param	Handle	Handle returned from GetAsynchronous.
- L66 _public prototype_ `virtual bool GetAsynchronousResults(uint32 Handle, TArray<uint8>& OutData, bool* bDataWasBuilt = nullptr) = 0;` — Retrieves the results from an async lookup / build. MUST only be called after the results are known to be ready by one of the aforementioned calls. @param	Handle	Handle returned from GetAsynchronous. @param	OutData	Array to receive the output results. @param	bDataWasBuilt if non-null, set to true if the data returned had to be built instead of retrieved from the DDC. Used for stat tracking. @return			true if the data was retrieved from the cache or the deriver built the data successfully. false can only occur if the plugin returns false.
- L67 _public prototype_ `virtual bool GetAsynchronousResults(uint32 Handle, TArray64<uint8>& OutData, bool* bDataWasBuilt = nullptr) = 0;`
- L74 _private member_ `static inline constexpr FAsciiSet ValidCacheKeyChars = "AB`
- L76 _private function_ `static void AppendSanitized(FString& Out, FStringView In)`
- L98 _public function_ `static bool IsValidCacheChar(const TCHAR C)` — Returns true if character is valid in a DDC cache key without escaping
- L108 _public function_ `static FString SanitizeCacheKey(const TCHAR* CacheKey)` — Static function to make sure a cache key contains only legal characters by using an escape @param CacheKey							Cache key to sanitize @return									Sanitized cache key
- L122 _public function_ `static FString BuildCacheKey(const TCHAR* PluginName, const TCHAR* VersionString, const TCHAR* PluginSpecificCacheKeySuffix)` — Static function to build a cache key out of the plugin name, versions and plugin specific info @param PluginName						Name of the derived data type @param VersionString						Version string of the derived data @param PluginSpecificCacheKeySuffix		GUIDS and / or Hashes, etc to uniquely identify the specific cache entry @return									Assembled cache key
- L127 _public function_ `static FString BuildCacheKey(FStringView PluginName, FStringView VersionString, FStringView PluginSpecificCacheKeySuffix)`
- L152 _public prototype_ `virtual bool GetSynchronous(const TCHAR* CacheKey, TArray<uint8>& OutData, FStringView DebugContext) = 0;` — Synchronously checks the cache and if the item is present, it returns the cached results, otherwise it returns false. Prefer to use a FDerivedDataPluginInterface instead of generating the key directly. @param	CacheKey		Key to identify the data. @param	DebugContext	A string used to describe the data being generated. Typically the path to the object that it is generated from is sufficient. @return	true if the data was retrieved from the cache.
- L153 _public prototype_ `virtual bool GetSynchronous(const TCHAR* CacheKey, TArray64<uint8>& OutData, FStringView DebugContext) = 0;`
- L164 _public prototype_ `virtual uint32 GetAsynchronous(const TCHAR* CacheKey, FStringView DebugContext) = 0;` — Starts the async process of checking the cache and if the item is present, retrieving the cached results. Prefer to use a FDerivedDataPluginInterface instead of generating the key directly. @param	CacheKey		Key to identify the data. @param	DebugContext	A string used to describe the data being generated. Typically the path to the object that it is generated from is sufficient. @return	A handle that can be used for PollAsynchronousCompletion, WaitAsynchronousCompletion, and GetAsynchronousResults.
- L175 _public prototype_ `virtual void Put(const TCHAR* CacheKey, TArrayView64<const uint8> Data, FStringView DataContext, bool bPutEvenIfExists = false) = 0;` — Puts data into the cache. This is fire-and-forget and typically asynchronous. Prefer to use a FDerivedDataPluginInterface instead of generating the key directly. @param	CacheKey	Key to identify the data @param	Data		Data to put in the cache under this key @param	DataContext	A string used to describe the data being generated. Typically the path to the object that it is generated from is sufficient.
- L181 _public prototype_ `virtual void MarkTransient(const TCHAR* CacheKey) = 0;` — Hint that the data associated with the key is transient and may be optionally purged from the cache. @param	CacheKey	Key that is associated with transient data.
- L188 _public prototype_ `virtual bool CachedDataProbablyExists(const TCHAR* CacheKey) = 0;` — Returns true if the data associated with the key is likely to exist in the cache. Even if this function returns true, a get for this key may still fail! @param	CacheKey	Key to see if data probably exists.
- L196 _public prototype_ `virtual TBitArray<> CachedDataProbablyExistsBatch(TConstArrayView<FString> CacheKeys) = 0;` — Returns whether the data associated with each key is likely to exist in the cache. Even if this function returns true, a get for one of the keys may still fail! @param	CacheKeys	Keys to see if data probably exists. @return				A bit array with bits indicating whether the data for the corresponding key will probably be found
- L203 _public prototype_ `virtual bool AllCachedDataProbablyExists(TConstArrayView<FString> CacheKeys) = 0;` — Returns true if the data associated with each key is likely to exist in the cache. Even if this function returns true, a get for one of the keys may still fail! @param	CacheKeys	Keys to see if data probably exists.
- L212 _public prototype_ `virtual bool TryToPrefetch(TConstArrayView<FString> CacheKeys, FStringView DebugContext) = 0;` — Synchronous attempt to make sure the cached data will be available as optimally as possible. @param	CacheKeys		Keys to identify the data. @param	DebugContext	A string used to describe the data being generated. Typically the path to the object that it is generated from is sufficient. @return					true if the data will probably be found in a fast backend on a future request.
- L219 _public function_ `void NotifyBootComplete()` — `UE_DEPRECATED(5.8, "The cache no longer uses this internally.")`
- L222 _public prototype_ `virtual void AddToAsyncCompletionCounter(int32 Addend) = 0;` — `UE_DEPRECATED(5.8, "The cache tracks its async operations internally. External modifications are no longer supported.")`
- L227 _public prototype_ `virtual bool AnyAsyncRequestsRemaining() const = 0;` — Are there any async DDC requests in progress?
- L232 _public prototype_ `virtual void WaitForQuiescence(bool bShutdown = false) = 0;` — Wait for all outstanding async DDC operations to complete.
- L235 _public function_ `void GetDirectories(TArray<FString>& OutResults)` — `UE_DEPRECATED(5.8, "Querying cache directories is no longer supported.")`
- L238 _public prototype_ `virtual bool GetUsingSharedDDC() const = 0;` — `UE_DEPRECATED(5.8, "Querying whether a shared cache is being used is no longer supported.")`
- L243 _public prototype_ `virtual const TCHAR* GetGraphName() const = 0;` — Retrieve the name of the graph used when configuring DDC
- L248 _public prototype_ `virtual const TCHAR* GetDefaultGraphName() const = 0;` — Retrieve the name of the 'default' graph, which may or may not be the active graph currently.
- L253 _public function_ `bool IsDefaultGraph() const` — Are we currently using the default graph configuration?
- L262 _public prototype_ `virtual void GatherUsageStats(TMap<FString, FDerivedDataCacheUsageStats>& UsageStats) = 0;` — Retrieve usage stats by the DDC
- L268 _public prototype_ `virtual TSharedRef<FDerivedDataCacheStatsNode> GatherUsageStats() const = 0;` — `UE_DEPRECATED(4.27, "This overload of GatherUsageStats is temporary. Please use other overload.")` — Retrieve usage stats by the DDC
- L270 _public prototype_ `virtual void GatherResourceStats(TArray<FDerivedDataCacheResourceStat>& DDCResourceStats) const = 0;`
- L272 _public prototype_ `virtual void GatherSummaryStats(FDerivedDataCacheSummaryStats& DDCSummaryStats) const = 0;`
- L277 _public prototype_ `UE_INTERNAL virtual void GatherVerificationStats(FDerivedDataCacheVerificationStats& OutStats) const = 0;` — Retrieve stats about the integrity of DDC data vs generated data
- L291 _public typedef_ `using FOnDDCNotification UE_DEPRECATED(5.8, "Notifications from the cache are no longer suppor`
- L294 _public prototype_ `virtual FOnDDCNotification& GetDDCNotificationEvent() = 0;` — `UE_DEPRECATED(5.8, "Notifications from the cache are no longer supported.")`

#### enum `FDerivedDataCacheInterface::EDDCNotification`  
`enum UE_DEPRECATED(5.8, "Notifications from the cache are no longer supported.") EDDCNotification`  
_L285-289_
- L288 _public enumerator_ `SharedDDCPerformanceNotification` — DDC performance notification generated when not using a shared cache

### `Source/Developer/DerivedDataCache/Public/DerivedDataCacheKey.h` (Public)


#### class `UE::DerivedData::FCacheBucket`  
`class FCacheBucket`  
_L27-87_
- desc: An alphanumeric identifier that groups related cache records. A cache bucket name must be alphanumeric, non-empty, and contain fewer than 64 code units.
- L31 _public member_ `static constexpr int32 MaxNameLen = 63;` — Maximum number of code units in a valid cache bucket name.
- L35 _public function_ `template <typename CharType> static inline bool IsValidName(TStringView<CharType> Name)` — Returns true if the name is a valid cache bucket name.
- L42 _public prototype_ `FCacheBucket() = default;` — Construct a null cache bucket.
- L45 _public prototype_ `explicit FCacheBucket(FUtf8StringView Name);` — Create a cache bucket from a name.
- L46 _public prototype_ `explicit FCacheBucket(FWideStringView Name);`
- L49 _public prototype_ `FCacheBucket(FUtf8StringView Name, FStringView DisplayName);` — Create a cache bucket from a name and a display name.
- L50 _public prototype_ `FCacheBucket(FWideStringView Name, FStringView DisplayName);`
- L53 _public prototype_ `void ToDisplayName(FStringBuilderBase& OutDisplayName) const;` — Append the display name if available or the bucket name if not.
- L56 _public function_ `inline bool IsNull() const` — Whether this is null.
- L58 _public function_ `inline bool IsValid() const` — Whether this is not null.
- L61 _public function_ `inline void Reset()` — Reset this to null.
- L63 _public function_ `inline bool operator==(FCacheBucket Other) const`
- L64 _public function_ `inline bool operator!=(FCacheBucket Other) const`
- L66 _public function_ `inline bool operator<(FCacheBucket Other) const`
- L77 _public prototype_ `inline FAnsiStringView ToString() const;` — Get the name of the cache bucket as a string.
- L80 _public function_ `inline const ANSICHAR* ToCString() const` — Get the name of the cache bucket as a null-terminated string.
- L83 _protected member_ `static constexpr int32 LengthOffset = -1;`
- L86 _protected member_ `const ANSICHAR* Name = nullptr;` — Name stored as a null-terminated string preceded by one byte containing its length.
- L127 _function_ `inline FAnsiStringView FCacheBucket::ToString() const`

#### struct `UE::DerivedData::FCacheKey`  
`struct FCacheKey`  
_L92-121_
- desc: A key that uniquely identifies a cache record.
- L94 _public member_ `FCacheBucket Bucket;`
- L95 _public member_ `FIoHash Hash;`
- L98 _public member_ `static const FCacheKey Empty;` — A key with a null bucket and a zero hash.
- L123 _member_ `inline const FCacheKey FCacheKey::Empty;`

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API DERIVEDDATACACHE_API`
- L17 _namespace_ `namespace UE`
- L17 _namespace_ `namespace DerivedData` (scope `UE`)
- L71 _function_ `friend inline uint32 GetTypeHash(FCacheBucket Bucket)` (scope `UE::DerivedData`)
- L100 _function_ `friend inline bool operator==(const FCacheKey& A, const FCacheKey& B)` (scope `UE::DerivedData`)
- L105 _function_ `friend inline bool operator!=(const FCacheKey& A, const FCacheKey& B)` (scope `UE::DerivedData`)
- L110 _function_ `friend inline bool operator<(const FCacheKey& A, const FCacheKey& B)` (scope `UE::DerivedData`)
- L117 _function_ `friend inline uint32 GetTypeHash(const FCacheKey& Key)` (scope `UE::DerivedData`)
- L133 _function_ `template <typename CharType> inline TStringBuilderBase<CharType>& operator<<(TStringBuilderBase<CharType>& Builder, const FCacheBucket& Bucket)` (scope `UE::DerivedData`)
- L139 _function_ `template <typename CharType> inline bool TryLexFromString(FCacheBucket& OutBucket, TStringView<CharType> String)` (scope `UE::DerivedData`)
- L152 _function_ `template <typename CharType> inline TStringBuilderBase<CharType>& operator<<(TStringBuilderBase<CharType>& Builder, const FCacheKey& Key)` (scope `UE::DerivedData`)
- L157 _prototype_ `bool TryLexFromString(FCacheKey& OutKey, FAnsiStringView String);` (scope `UE::DerivedData`)
- L158 _prototype_ `bool TryLexFromString(FCacheKey& OutKey, FWideStringView String);` (scope `UE::DerivedData`)
- L160 _prototype_ `void SerializeForLog(FCbWriter& Writer, const FCacheKey& Key);` (scope `UE::DerivedData`)
- L171 _prototype_ `FCacheKey ConvertLegacyCacheKey(FStringView Key);` (scope `UE::DerivedData`) — Constructs a cache key from a legacy cache key. Keys converted with this function are the same keys used internally by the legacy cache API. Legacy keys are typically of the form DATATYPENAME_VersionGuid_TypeSpecificSuffix.
- L178 _prototype_ `FCacheKey BuildLegacyCacheKey(FStringView PluginName, FStringView VersionString, FStringView PluginSpecificCacheKeySuffix);` (scope `UE::DerivedData`) — Builds a cache key from the same components as the legacy BuildCacheKey API. Equivalent to ConvertLegacyCacheKey(FDerivedDataCacheInterface::BuildCacheKey(PluginName, VersionString, PluginSpecificCacheKeySuffix)).

### `Source/Developer/DerivedDataCache/Public/DerivedDataCacheKeyBuilder.h` (Public)


#### class `UE::DerivedData::FCacheKeyBuilder`  
`class FCacheKeyBuilder final : public FArchive`  
_L27-51_
- inherits: `FArchive`
- desc: A type that builds a cache key from arbitrary values serialized to it. FCacheKey GetKey(UAsset* Asset) { FCacheKeyBuilder Builder; Builder << FGuid(TEXT("a3ae79ff-6a89-4124-afd6-dc095e000488")); Builder << ThirdPartyLibraryVersion; Builder << Asset->GetBulkData().GetPayloadId(); static const FCacheBucket Bucket(ANSITEXTVIEW("")); return Builder.Build(Bucket); }
- L30 _public prototype_ `inline FCacheKeyBuilder();`
- L32 _public prototype_ `inline FCacheKey Build(FCacheBucket Bucket) const;`
- L34 _public function_ `inline FString GetArchiveName() const final`
- L36 _public prototype_ `inline void Serialize(void* Data, int64 Num) final;`
- L39 _public prototype_ `FArchive& operator<<(FName& Name) final;`
- L42 _public function_ `template <typename ArgType> inline FCacheKeyBuilder& operator<<(ArgType&& Arg)`
- L50 _private member_ `FIoHashBuilder HashBuilder;`
- L53 _function_ `inline FCacheKeyBuilder::FCacheKeyBuilder()`
- L63 _function_ `inline FCacheKey FCacheKeyBuilder::Build(FCacheBucket Bucket) const`
- L68 _function_ `inline void FCacheKeyBuilder::Serialize(void* Data, int64 Num)`
- L73 _function_ `inline FArchive& FCacheKeyBuilder::operator<<(FName& Name)`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace DerivedData` (scope `UE`)

### `Source/Developer/DerivedDataCache/Public/DerivedDataCacheMaintainer.h` (Public)


#### class `UE::DerivedData::ICacheStoreMaintainer`  
`class ICacheStoreMaintainer`  
_L19-38_
- desc: A cache store may register an instance of this interface to take part in cache maintenance. As an example, a filesystem cache might register a maintainer that scans for and deletes stale files within its cache directory. Boosting the priority removes any sleep between file scans. An example consumer is the DDCCleanup commandlet which uses this to boost priority and wait on the completion of maintenance by cache stores.
- L27 _public prototype_ `virtual bool IsIdle() const = 0;` — True when maintenance is not active. This must return true eventually because it is called to wait for maintenance.
- L35 _public function_ `virtual void BoostPriority()` — Boost the priority of the active maintenance operation. This is expected to remove any delays, or otherwise allow the active maintenance operation to complete more quickly. This is called before waiting for maintenance to be idle.

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace DerivedData` (scope `UE`)

### `Source/Developer/DerivedDataCache/Public/DerivedDataCacheModule.h` (Public)


#### class `IDerivedDataCacheModule`  
`class IDerivedDataCacheModule : public IModuleInterface`  
_L13-33_
- inherits: `IModuleInterface`
- desc: Module for the Derived Data Cache and Derived Data Build.
- L23 _public prototype_ `virtual FDerivedDataCacheInterface* const* CreateOrGetCache() = 0;` — Returns the cache, which is created by the first call to this function. This always returns a pointer to a valid cache, but that pointer becomes null when the module shuts down and destroys the cache. This extra level of indirection allows a caller to observe the destruction of the cache without polling this function or monitoring the module lifetime.
- L32 _public prototype_ `virtual FDerivedDataCacheInterface* const* GetCache() = 0;` — Returns a pointer to the cache, which may be null. This returns a non-null pointer to a cache which may be null and becomes null when the module shuts down and destroys the cache. This extra level of indirection allows a caller to observe the destruction of the cache without polling this function or monitoring the module lifetime.

### `Source/Developer/DerivedDataCache/Public/DerivedDataCachePolicy.h` (Public)


#### enum `UE::DerivedData::ECachePolicy`  
`enum class ECachePolicy : uint32`  
_L47-114_
- desc: Flags to control the behavior of cache requests. Flags can be combined to cover a variety of requirements. Examples: Get(Default): Fetch from any cache. Store the response to any caches if missing. Get(Local): Fetch from any local cache. Store the response to any local caches if missing. Get(Query | StoreLocal): Fetch from any cache. Store response to any local caches if missing. Get(Query | SkipData): Check for existence in any cache. Do not store to any caches if missing. Get(Default | SkipData): Check for existence in any cache. Store the response to any caches if missing. Get(Default | PartialRecord): Fetch from any cache, and return a partial record if values are missing data. Put(Default | SkipData): Store to every cache, do not overwrite existing valid records or values, and skip fetching values from conflicting existing records for the record returned in the response. Put(Default): Store to every cache, and do not overwrite existing valid records or values, and fetch values from conflicting existing records for the record returned in the response. Put(Store): Store to every cache, and overwrite existing records or values. Put(Local): Store to every local cache, skipping remote caches. Put(Default | PartialRecord): Store to every cache, even if the record has missing data for its values.
- L50 _public enumerator_ `None = 0` — A value with no flags. Disables access to the cache unless combined with other flags.
- L53 _public enumerator_ `QueryLocal = 1 << 0` — Allow a cache request to query local caches.
- L55 _public enumerator_ `QueryRemote = 1 << 1` — Allow a cache request to query remote caches.
- L57 _public enumerator_ `Query = QueryLocal | QueryRemote` — Allow a cache request to query any caches.
- L60 _public enumerator_ `StoreLocal = 1 << 2` — Allow cache records and values to be stored in local caches.
- L62 _public enumerator_ `StoreRemote = 1 << 3` — Allow cache records and values to be stored in remote caches.
- L64 _public enumerator_ `Store = StoreLocal | StoreRemote` — Allow cache records and values to be stored in any caches.
- L67 _public enumerator_ `Local = QueryLocal | StoreLocal` — Allow cache requests to query and store records and values in local caches.
- L69 _public enumerator_ `Remote = QueryRemote | StoreRemote` — Allow cache requests to query and store records and values in remote caches.
- L72 _public enumerator_ `Default = Query | Store` — Allow cache requests to query and store records and values in any caches.
- L75 _public enumerator_ `SkipData = 1 << 4` — Skip fetching the data for values.
- L78 _public enumerator_ `SkipMeta = 1 << 5` — Skip fetching the metadata for record requests.
- L91 _public enumerator_ `PartialRecord = 1 << 6` — Partial output will be provided with the error status when a required value is missing. This is meant for cases when the missing values can be individually recovered, or rebuilt, without rebuilding the whole record. The cache automatically adds this flag when there are other cache stores that it may be able to recover missing values from. Missing values will be returned in the records, but with only the hash and size. Applying this flag for a put of a record allows a partial record to be stored.
- L102 _public enumerator_ `KeepAlive = 1 << 7` — Keep records and values in the cache for at least the duration of the session. This flag hints that the records and values that it is applied to may be accessed again in this session. The cache will make an effort to prevent eviction of the records and values, though an absolute guarantee is impossible. This flag is meant to be used when subsequent accesses will not tolerate a cache miss.
- L113 _public enumerator_ `NonDeterministic = 1 << 8` — Values associated with this policy are known to be non-deterministic. This is meant to be applied to values that are expected to differ between builds. Disables reporting of non-determinism in put requests and disables verification of determinism for associated values when running in verify mode. DO NOT APPLY THIS FLAG TO VALUES THAT ARE WRITTEN TO COOKED PACKAGES.

#### struct `UE::DerivedData::FCacheValuePolicy`  
`struct FCacheValuePolicy`  
_L138-145_
- desc: A value ID and the cache policy to use for that value.
- L140 _public member_ `FValueId Id;`
- L141 _public member_ `ECachePolicy Policy = ECachePolicy::Default;`
- L144 _public member_ `static constexpr ECachePolicy PolicyMask = ECachePolicy::Default | ECachePolicy::SkipData | ECachePolicy::NonDeterministic;` — Flags that are valid on a value policy.

#### class `UE::DerivedData::Private::ICacheRecordPolicyShared`  
`class Private::ICacheRecordPolicyShared`  
_L148-156_
- desc: Interface for the private implementation of the cache record policy.
- L151 _public prototype_ `virtual ~ICacheRecordPolicyShared() = default;`
- L152 _public prototype_ `virtual void AddRef() const = 0;`
- L153 _public prototype_ `virtual void Release() const = 0;`
- L154 _public prototype_ `virtual void AddValuePolicy(const FCacheValuePolicy& Policy) = 0;`
- L155 _public prototype_ `virtual TConstArrayView<FCacheValuePolicy> GetValuePolicies() const = 0;`

#### class `UE::DerivedData::FCacheRecordPolicy`  
`class FCacheRecordPolicy`  
_L167-214_
- desc: Flags to control the behavior of cache record requests, with optional overrides by value. Examples: - A base policy of None with value policy overrides of Default will fetch those values if they exist in the record, and skip data for any other values. - A base policy of Default, with value policy overrides of (Query | SkipData), will skip those values, but still check if they exist, and will load any other values.
- L171 _public prototype_ `FCacheRecordPolicy() = default;` — Construct a cache record policy that uses the default policy.
- L174 _public function_ `inline FCacheRecordPolicy(ECachePolicy BasePolicy) : RecordPolicy(BasePolicy) , DefaultValuePolicy(BasePolicy & FCacheValuePolicy::PolicyMask)` — Construct a cache record policy with a uniform policy for the record and every value.
- L181 _public function_ `inline bool IsDefault() const` — Returns true if this is the default cache policy with no overrides for values.
- L184 _public function_ `inline bool IsUniform() const` — Returns true if the record and every value use the same cache policy.
- L187 _public function_ `inline ECachePolicy GetRecordPolicy() const` — Returns the cache policy to use for the record.
- L190 _public function_ `inline ECachePolicy GetBasePolicy() const` — Returns the base cache policy that this was constructed from.
- L196 _public prototype_ `ECachePolicy GetValuePolicy(const FValueId& Id) const;` — Returns the cache policy to use for the value.
- L199 _public function_ `inline TConstArrayView<FCacheValuePolicy> GetValuePolicies() const` — Returns the array of cache policy overrides for values, sorted by ID.
- L205 _public prototype_ `FCacheRecordPolicy Transform(TFunctionRef<ECachePolicy (ECachePolicy)> Op) const;` — Returns a copy of this policy transformed by an operation.
- L211 _private member_ `ECachePolicy RecordPolicy = ECachePolicy::Default;`
- L212 _private member_ `ECachePolicy DefaultValuePolicy = ECachePolicy::Default;`
- L213 _private member_ `TRefCountPtr<const Private::ICacheRecordPolicyShared> Shared;`

#### class `UE::DerivedData::FCacheRecordPolicyBuilder`  
`class FCacheRecordPolicyBuilder`  
_L217-239_
- desc: A cache record policy builder is used to construct a cache record policy.
- L221 _public prototype_ `FCacheRecordPolicyBuilder() = default;` — Construct a policy builder that uses the default policy as its base policy.
- L224 _public function_ `inline explicit FCacheRecordPolicyBuilder(ECachePolicy Policy) : BasePolicy(Policy)` — Construct a policy builder that uses the provided policy for the record and values with no override.
- L230 _public prototype_ `void AddValuePolicy(const FCacheValuePolicy& Value);` — Adds a cache policy override for a value. Must contain only flags in FCacheRecordValue::PolicyMask.
- L231 _public function_ `inline void AddValuePolicy(const FValueId& Id, ECachePolicy Policy)`
- L234 _public prototype_ `FCacheRecordPolicy Build();` — Build a cache record policy, which makes this builder subsequently unusable.
- L237 _private member_ `ECachePolicy BasePolicy = ECachePolicy::Default;`
- L238 _private member_ `TRefCountPtr<Private::ICacheRecordPolicyShared> Shared;`

#### class `UE::DerivedData::FOptionalCacheRecordPolicy`  
`class FOptionalCacheRecordPolicy : private FCacheRecordPolicy`  
_L246-265_
- inherits: `FCacheRecordPolicy`
- desc: A cache record policy that can be null. @see FCacheRecordPolicy
- L249 _public function_ `inline FOptionalCacheRecordPolicy() : FCacheRecordPolicy(~ECachePolicy::None)`
- L251 _public function_ `inline FOptionalCacheRecordPolicy(FCacheRecordPolicy&& InOutput) : FCacheRecordPolicy(MoveTemp(InOutput))`
- L252 _public function_ `inline FOptionalCacheRecordPolicy(const FCacheRecordPolicy& InOutput) : FCacheRecordPolicy(InOutput)`
- L253 _public function_ `inline FOptionalCacheRecordPolicy& operator=(FCacheRecordPolicy&& InOutput)`
- L254 _public function_ `inline FOptionalCacheRecordPolicy& operator=(const FCacheRecordPolicy& InOutput)`
- L257 _public function_ `inline const FCacheRecordPolicy& Get() const &` — Returns the cache record policy. The caller must check for null before using this accessor.
- L258 _public function_ `inline FCacheRecordPolicy Get() &&`
- L260 _public function_ `inline bool IsNull() const`
- L261 _public function_ `inline bool IsValid() const`
- L262 _public function_ `inline explicit operator bool() const`
- L264 _public function_ `inline void Reset()`

#### Free symbols / members of external scopes

- L14 _macro_ `#define UE_API DERIVEDDATACACHE_API`
- L18 _namespace_ `namespace UE`
- L18 _namespace_ `namespace DerivedData` (scope `UE`)
- L19 _namespace_ `namespace UE`
- L19 _namespace_ `namespace DerivedData` (scope `UE`)
- L20 _namespace_ `namespace UE`
- L20 _namespace_ `namespace DerivedData` (scope `UE`)
- L21 _namespace_ `namespace UE`
- L21 _namespace_ `namespace DerivedData` (scope `UE`)
- L22 _namespace_ `namespace UE`
- L22 _namespace_ `namespace DerivedData` (scope `UE`)
- L22 _namespace_ `namespace Private` (scope `UE::DerivedData`)
- L24 _namespace_ `namespace UE`
- L24 _namespace_ `namespace DerivedData` (scope `UE`)
- L116 _prototype_ `ENUM_CLASS_FLAGS(ECachePolicy);` (scope `UE::DerivedData`)
- L126 _prototype_ `ECachePolicy CombineCachePolicy(ECachePolicy A, ECachePolicy B);` (scope `UE::DerivedData`) — Returns a cache policy that encompasses the operations requested by the both arguments. Examples: - (Local, Remote | SkipData) -> Default - (Default, Local | SkipMeta) -> Default - (Query, StoreRemote) -> Query | StoreRemote
- L129 _prototype_ `FAnsiStringBuilderBase& operator<<(FAnsiStringBuilderBase& Builder, ECachePolicy Policy);` (scope `UE::DerivedData`) — Append a non-empty text version of the policy to the builder.
- L130 _prototype_ `FWideStringBuilderBase& operator<<(FWideStringBuilderBase& Builder, ECachePolicy Policy);` (scope `UE::DerivedData`)
- L131 _prototype_ `FUtf8StringBuilderBase& operator<<(FUtf8StringBuilderBase& Builder, ECachePolicy Policy);` (scope `UE::DerivedData`)
- L134 _prototype_ `bool TryLexFromString(ECachePolicy& OutPolicy, FUtf8StringView String);` (scope `UE::DerivedData`) — Try to parse a policy from text written by operator<<.
- L135 _prototype_ `bool TryLexFromString(ECachePolicy& OutPolicy, FWideStringView String);` (scope `UE::DerivedData`)
- L268 _prototype_ `FValue ApplySkipPolicy(const FValue& Value, ECachePolicy Policy);` (scope `UE::DerivedData`) — Apply the policy to the value by removing data if SkipData is present.
- L270 _prototype_ `FValueWithId ApplySkipPolicy(const FValueWithId& Value, ECachePolicy Policy);` (scope `UE::DerivedData`) — Apply the policy to the value by removing data if SkipData is present.
- L272 _prototype_ `FCacheRecord ApplySkipPolicy(const FCacheRecord& Record, const FCacheRecordPolicy& Policy);` (scope `UE::DerivedData`) — Apply the policy to the record by removing data if SkipData is present and metadata if SkipMeta is present.

### `Source/Developer/DerivedDataCache/Public/DerivedDataCacheRecord.h` (Public)


#### class `UE::DerivedData::Private::ICacheRecordInternal`  
`class ICacheRecordInternal`  
_L34-44_
- L37 _public prototype_ `virtual ~ICacheRecordInternal() = default;`
- L38 _public prototype_ `virtual const FCacheKey& GetKey() const = 0;`
- L39 _public prototype_ `virtual const FCbObject& GetMeta() const = 0;`
- L40 _public prototype_ `virtual const FValueWithId& GetValue(const FValueId& Id) const = 0;`
- L41 _public prototype_ `virtual TConstArrayView<FValueWithId> GetValues() const = 0;`
- L42 _public prototype_ `virtual void AddRef() const = 0;`
- L43 _public prototype_ `virtual void Release() const = 0;`

#### class `UE::DerivedData::Private::ICacheRecordBuilderInternal`  
`class ICacheRecordBuilderInternal`  
_L48-56_
- L51 _public prototype_ `virtual ~ICacheRecordBuilderInternal() = default;`
- L52 _public prototype_ `virtual void SetMeta(FCbObject&& Meta) = 0;`
- L53 _public prototype_ `virtual void AddValue(const FValueId& Id, const FValue& Value) = 0;`
- L54 _public prototype_ `virtual FCacheRecord Build() = 0;`
- L55 _public prototype_ `virtual void BuildAsync(IRequestOwner& Owner, FOnCacheRecordComplete&& OnComplete) = 0;`

#### class `UE::DerivedData::FCacheRecord`  
`class FCacheRecord`  
_L72-113_
- desc: A cache record is a key, an array of values, and metadata. The key must uniquely correspond to its values. The key must never be reused for other values. The metadata does not have this requirement and may be used to persist details that vary, such as the time to generate the values or the machine that generated them.
- L76 _public prototype_ `explicit FCacheRecord(const FCacheKey& Key);` — Construct a cache record for the key with no metadata or values.
- L79 _public function_ `inline const FCacheKey& GetKey() const` — Returns the key that identifies this record in the cache.
- L82 _public function_ `inline const FCbObject& GetMeta() const` — Returns the metadata. Null when requested with ECachePolicy::SkipMeta.
- L85 _public function_ `inline const FValueWithId& GetValue(const FValueId& Id) const` — Returns the value matching the ID. Null if no match. Data is null if skipped.
- L88 _public function_ `inline TConstArrayView<FValueWithId> GetValues() const` — Returns a view of the values ordered by ID. Data is null if skipped.
- L91 _public prototype_ `FCbPackage Save() const;` — Save the cache record to a compact binary package.
- L93 _public prototype_ `void Save(FCbPackage& Attachments, FCbWriter& Writer) const;` — Append the cache record to an existing package and writer, as an object, for e.g. a batch of records.
- L96 _public prototype_ `static FOptionalCacheRecord Load(const FCbPackage& Package);` — Load a cache record from a compact binary package. Null on error.
- L97 _public prototype_ `static FOptionalCacheRecord Load(const FCbPackage& Attachments, const FCbObject& Object);`
- L100 _public prototype_ `UE_INTERNAL static FCacheRecord CreateByMove(const FCacheKey& Key, FCbObject&& Meta, TArray<FValueWithId>&& Values);` — Internal. Create a record from a key, optional metadata, and sorted values. Moves metadata and values.
- L107 _private function_ `inline explicit FCacheRecord(Private::ICacheRecordInternal* InRecord) : Record(InRecord)` — Construct a cache record. Use Build() or BuildAsync() on FCacheRecordBuilder.
- L112 _private member_ `TRefCountPtr<Private::ICacheRecordInternal> Record;`

#### class `UE::DerivedData::FCacheRecordBuilder`  
`class FCacheRecordBuilder`  
_L123-193_
- desc: A cache record builder is used to construct a cache record. Create using a key that uniquely corresponds to the values for the cache record. The metadata may vary between records with the same key. @see FCacheRecord
- L129 _public prototype_ `explicit FCacheRecordBuilder(const FCacheKey& Key);` — Create a cache record builder from a cache key.
- L136 _public function_ `inline void SetMeta(FCbObject&& Meta)` — Set the metadata for the cache record. @param Meta   The metadata, which is cloned if not owned.
- L148 _public prototype_ `void AddValue(const FValueId& Id, const FCompositeBuffer& Buffer, uint64 BlockSize = 0);` — Add a value to the cache record. @param Id          An ID for the value that is unique within this cache record. @param Buffer      The value, which is compressed by the builder, and cloned if not owned. @param BlockSize   The power-of-two block size to encode raw data in. 0 is default.
- L149 _public prototype_ `void AddValue(const FValueId& Id, const FSharedBuffer& Buffer, uint64 BlockSize = 0);`
- L156 _public prototype_ `void AddValue(const FValueWithId& Value);` — Add a value to the cache record. @note The ID for the value must be unique within this cache record.
- L163 _public function_ `inline void AddValue(const FValueId& Id, const FValue& Value)` — Add a value to the cache record. @param Id   An ID for the value that is unique within this cache record.
- L174 _public function_ `inline FCacheRecord Build()` — Build a cache record, which makes this builder subsequently unusable. Prefer BuildAsync() when the values are added from raw buffers, which requires compressing those buffers before constructing the cache record.
- L186 _public function_ `inline void BuildAsync(IRequestOwner& Owner, FOnCacheRecordComplete&& OnComplete)` — Build a cache record asynchronously, which makes this builder subsequently unusable. Prefer Build() when the values are added from compressed buffers as compression is already complete and BuildAsync() will complete immediately in that case.
- L192 _private member_ `TUniquePtr<Private::ICacheRecordBuilderInternal> RecordBuilder;`

#### class `UE::DerivedData::FOptionalCacheRecord`  
`class FOptionalCacheRecord : private FCacheRecord`  
_L200-219_
- inherits: `FCacheRecord`
- desc: A cache record that can be null. @see FCacheRecord
- L203 _public function_ `inline FOptionalCacheRecord() : FCacheRecord(nullptr)`
- L205 _public function_ `inline FOptionalCacheRecord(FCacheRecord&& InRecord) : FCacheRecord(MoveTemp(InRecord))`
- L206 _public function_ `inline FOptionalCacheRecord(const FCacheRecord& InRecord) : FCacheRecord(InRecord)`
- L207 _public function_ `inline FOptionalCacheRecord& operator=(FCacheRecord&& InRecord)`
- L208 _public function_ `inline FOptionalCacheRecord& operator=(const FCacheRecord& InRecord)`
- L211 _public function_ `inline const FCacheRecord& Get() const &` — Returns the cache record. The caller must check for null before using this accessor.
- L212 _public function_ `inline FCacheRecord Get() &&`
- L214 _public function_ `inline bool IsNull() const`
- L215 _public function_ `inline bool IsValid() const`
- L216 _public function_ `inline explicit operator bool() const`
- L218 _public function_ `inline void Reset()`

#### struct `UE::DerivedData::FCacheRecordKeyFuncs`  
`struct FCacheRecordKeyFuncs`  
_L229-240_
- desc: An implementation of KeyFuncs to compare FCacheRecord by its FCacheKey.
- L231 _public typedef_ `using KeyType = FCacheKey;`
- L232 _public typedef_ `using KeyInitType = const FCacheKey&;`
- L233 _public typedef_ `using ElementInitType = const FCacheRecord&;`
- L235 _public member_ `static constexpr bool bAllowDuplicateKeys = false;`
- L237 _public function_ `static inline KeyInitType GetSetKey(ElementInitType Record)`
- L238 _public function_ `static inline uint32 GetKeyHash(KeyInitType Key)`
- L239 _public function_ `static inline bool Matches(KeyInitType A, KeyInitType B)`

#### Free symbols / members of external scopes

- L15 _macro_ `#define UE_API DERIVEDDATACACHE_API`
- L21 _namespace_ `namespace UE`
- L21 _namespace_ `namespace DerivedData` (scope `UE`)
- L22 _namespace_ `namespace UE`
- L22 _namespace_ `namespace DerivedData` (scope `UE`)
- L23 _namespace_ `namespace UE`
- L23 _namespace_ `namespace DerivedData` (scope `UE`)
- L24 _namespace_ `namespace UE`
- L24 _namespace_ `namespace DerivedData` (scope `UE`)
- L25 _namespace_ `namespace UE`
- L25 _namespace_ `namespace DerivedData` (scope `UE`)
- L26 _namespace_ `namespace UE`
- L26 _namespace_ `namespace DerivedData` (scope `UE`)
- L27 _namespace_ `namespace UE`
- L27 _namespace_ `namespace DerivedData` (scope `UE`)
- L27 _typedef_ `namespace UE::DerivedData { using FOnCacheRecordComplete = TUniqueFunction<void (FCacheRecord&& Record)>; }` (scope `UE::DerivedData`)
- L31 _namespace_ `namespace UE`
- L31 _namespace_ `namespace DerivedData` (scope `UE`)
- L31 _namespace_ `namespace Private` (scope `UE::DerivedData`)
- L46 _prototype_ `FCacheRecord CreateCacheRecord(ICacheRecordInternal* Record);` (scope `UE::DerivedData::Private`)
- L62 _namespace_ `namespace UE`
- L62 _namespace_ `namespace DerivedData` (scope `UE`)
- L225 _namespace_ `namespace UE`
- L225 _namespace_ `namespace DerivedData` (scope `UE`)

### `Source/Developer/DerivedDataCache/Public/DerivedDataCacheUsageStats.h` (Public)


#### class `FDerivedDataCacheUsageStats`  
`class FDerivedDataCacheUsageStats`  
_L60-111_
- desc: Usage stats for the derived data cache nodes. At the end of the app or commandlet, the DDC can be asked to gather usage stats for each of the nodes in the DDC graph, which are accumulated into a TMap of Name->Stats. The Stats portion is this class. The class exposes various high-level routines to time important aspects of the DDC, mostly focusing on performance of GetCachedData, PutCachedData, and CachedDataProbablyExists. This class will track time taken, calls made, hits, misses, bytes processed, and do it for two buckets: 1) the main thread and 2) all other threads.  The reason is because any time spent in the DDC on the main thread is considered meaningful, as DDC access is generally expected to be async from helper threads. The class goes through a bit of trouble to use thread-safe access calls for task-thread usage, and simple, fast accumulators for game-thread usage, since it's guaranteed to not be written to concurrently. The class also limits itself to checking the thread once at construction. Usage would be something like this in a concrete FDerivedDataBackendInterface implementation: class MyBackend : public FDerivedDataBackendInterface { FDerivedDataCacheUsageStats UsageStats; public: <override CachedDataProbablyExists> { auto Timer = UsageStats.TimeExists(); ... } <override GetCachedData> { auto Timer = UsageStats.TimeGet(); ... <if it's a cache hit> Timer.AddHit(DataSize); // Misses are automatically tracked } <override PutCachedData> { auto Timer = UsageStats.T
- L66 _public function_ `FCookStats::FScopedStatsCounter TimeProbablyExists()` — Call this at the top of the CachedDataProbablyExists override. auto Timer = TimeProbablyExists();
- L72 _public function_ `FCookStats::FScopedStatsCounter TimeGet()` — Call this at the top of the GetCachedData override. auto Timer = TimeGet(); Use AddHit on the returned type to track a cache hit.
- L78 _public function_ `FCookStats::FScopedStatsCounter TimePut()` — Call this at the top of the PutCachedData override. auto Timer = TimePut(); Use AddHit on the returned type to track a cache hit.
- L84 _public function_ `FCookStats::FScopedStatsCounter TimePrefetch()` — Call this at the top of the PutCachedData override. auto Timer = TimePut(); Use AddHit on the returned type to track a cache hit.
- L89 _public function_ `void LogStats(FCookStatsManager::AddStatFuncRef AddStat, const FString& StatName, const FString& NodeName) const`
- L97 _public function_ `void Combine(const FDerivedDataCacheUsageStats& Other)`
- L106 _public member_ `FCookStats::CallStats GetStats;` — expose these publicly for low level access. These should really never be accessed directly except when finished accumulating them.
- L107 _public member_ `FCookStats::CallStats PutStats;`
- L108 _public member_ `FCookStats::CallStats ExistsStats;`
- L109 _public member_ `FCookStats::CallStats PrefetchStats;`

#### struct `FDerivedDataCacheSpeedStats`  
`struct FDerivedDataCacheSpeedStats`  
_L114-119_
- desc: Performance stats for this backend
- L116 _public member_ `double ReadSpeedMBs = 0.0;`
- L117 _public member_ `double WriteSpeedMBs = 0.0;`
- L118 _public member_ `double LatencyMS = 0.0;`

#### enum `EDerivedDataCacheStatus`  
`enum class EDerivedDataCacheStatus`  
_L121-128_
- L123 _public enumerator_ `None = 0`
- L124 _public enumerator_ `Information`
- L125 _public enumerator_ `Warning`
- L126 _public enumerator_ `Error`
- L127 _public enumerator_ `Deactivation`

#### struct `FDerivedDataCacheSummaryStats`  
`struct FDerivedDataCacheSummaryStats`  
_L132-135_
- L134 _public prototype_ `COOK_STAT(TArray<FDerivedDataCacheSummaryStat> Stats);`

#### class `FDerivedDataCacheStatsNode`  
`class FDerivedDataCacheStatsNode : public TSharedFromThis<FDerivedDataCacheStatsNode>`  
_L140-222_
- inherits: `TSharedFromThis<FDerivedDataCacheStatsNode>`
- desc: Hierarchical usage stats for the DDC nodes.
- L143 _public prototype_ `FDerivedDataCacheStatsNode() = default;`
- L145 _public function_ `FDerivedDataCacheStatsNode(const FString& InCacheType, const FString& InCacheName, bool bInIsLocal, EDerivedDataCacheStatus InCacheStatus = EDerivedDataCacheStatus::None, const TCHAR* InCacheStatusText = nullptr) : CacheType(InCacheType) , CacheName(InCacheName) , CacheStatusText(InCacheStatusText) , CacheStatus(InCacheStatus) , bIsLocal(bInIsLocal)`
- L154 _public function_ `const FString& GetCacheType() const`
- L156 _public function_ `const FString& GetCacheName() const`
- L158 _public function_ `const EDerivedDataCacheStatus GetCacheStatus() const`
- L160 _public function_ `const FString& GetCacheStatusText() const`
- L162 _public function_ `bool IsLocal() const`
- L164 _public function_ `TMap<FString, FDerivedDataCacheUsageStats> ToLegacyUsageMap() const`
- L171 _public function_ `void ForEachDescendant(TFunctionRef<void(TSharedRef<const FDerivedDataCacheStatsNode>)> Predicate) const`
- L181 _public function_ `uint64 GetTotalPhysicalSize() const`
- L182 _public function_ `void SetTotalPhysicalSize(uint64 InTotalPhysicalSize)`
- L185 _public function_ `void GatherLegacyUsageStats(TMap<FString, FDerivedDataCacheUsageStats>& UsageStatsMap, FString&& GraphPath) const`
- L209 _public member_ `TMap<FString, FDerivedDataCacheUsageStats> UsageStats;`
- L210 _public member_ `FDerivedDataCacheSpeedStats SpeedStats;`
- L211 _public prototype_ `COOK_STAT(TArray<FCookStatsManager::StringKeyValue> CustomStats);`
- L213 _public member_ `TArray<TSharedRef<FDerivedDataCacheStatsNode>> Children;`
- L216 _protected member_ `FString CacheType;`
- L217 _protected member_ `FString CacheName;`
- L218 _protected member_ `FString CacheStatusText;`
- L219 _protected member_ `uint64 TotalPhysicalSize = ~0ull;`
- L220 _protected member_ `EDerivedDataCacheStatus CacheStatus;`
- L221 _protected member_ `bool bIsLocal;`

#### struct `FDerivedDataCacheResourceStat`  
`struct FDerivedDataCacheResourceStat`  
_L224-303_
- L227 _public function_ `FDerivedDataCacheResourceStat(FString InAssetType = TEXT("None"), bool bIsGameThreadTime = false, double InLoadTimeSec = 0.0, double InLoadSizeMB = 0.0, int64 InAssetsLoaded = 0, double InBuildTimeSec = 0.0, double InBuildSizeMB = 0.0, int64 InAssetsBuilt = 0) : AssetType(MoveTemp(InAssetType)), LoadTimeSec(InLoadTimeSec), LoadSizeMB(InLoadSizeMB), LoadCount(InAssetsLoaded), BuildTimeSec(InBuildTimeSec), BuildSizeMB(InBuildSizeMB), BuildCount(InAssetsBuilt), GameThreadTimeSec(bIsGameThreadTime ? InLoadTimeSec + InBuildTimeSec : 0.0)`
- L241 _public function_ `const FDerivedDataCacheResourceStat& operator+(const FDerivedDataCacheResourceStat& OtherStat)`
- L259 _public function_ `const FDerivedDataCacheResourceStat& operator-(const FDerivedDataCacheResourceStat& OtherStat)`
- L277 _public function_ `const FDerivedDataCacheResourceStat& operator+=(const FDerivedDataCacheResourceStat& OtherStat)`
- L283 _public function_ `const FDerivedDataCacheResourceStat& operator-=(const FDerivedDataCacheResourceStat& OtherStat)`
- L289 _public member_ `FString AssetType;`
- L291 _public member_ `double LoadTimeSec = 0;`
- L292 _public member_ `double LoadSizeMB = 0;`
- L293 _public member_ `int64 LoadCount = 0;`
- L295 _public member_ `double BuildTimeSec = 0;`
- L296 _public member_ `double BuildSizeMB = 0;`
- L297 _public member_ `int64 BuildCount = 0;`
- L299 _public member_ `int64 TotalCount = 0;`
- L300 _public member_ `double Efficiency = 0;`
- L302 _public member_ `double GameThreadTimeSec = 0;`

#### struct `FDerivedDataCacheResourceStatKeyFuncs`  
`struct FDerivedDataCacheResourceStatKeyFuncs : BaseKeyFuncs<FDerivedDataCacheResourceStat, FString, false>`  
_L305-310_
- inherits: `BaseKeyFuncs<FDerivedDataCacheResourceStat,FString,false>`
- L307 _public function_ `static const FString& GetSetKey(const FDerivedDataCacheResourceStat& Element)`
- L308 _public function_ `static bool Matches(const FString& A, const FString& B)`
- L309 _public function_ `static uint32 GetKeyHash(const FString& Key)`

#### struct `FDerivedDataCacheVerificationStat`  
`struct FDerivedDataCacheVerificationStat`  
_L314-348_
- desc: DDC-Verify collects data about a subset of newly generated derived data, and whether it matches existing cached values This object is used to track statistics about verification results and is collected per DDC bucket
- L316 _public member_ `FString BucketName;` — name of the bucket
- L317 _public member_ `uint32 RecordsTested = 0;` — num records that were tested against the cache
- L318 _public member_ `uint32 RecordsMatchedCache = 0;` — num records that match existing cache data
- L319 _public member_ `uint32 RecordsNotInCache = 0;` — records that have no existing data in the cache
- L320 _public member_ `uint32 ValuesTested = 0;` — multiple values per record
- L321 _public member_ `uint64 ValuesTestedBytes = 0;` — total size of values tested
- L322 _public member_ `uint32 ValuesMatchedCache = 0;` — num values that match existing cache data
- L323 _public member_ `uint64 ValuesMatchedCacheBytes = 0;` — total size of matching data
- L324 _public member_ `uint32 ValuesNotInCache = 0;` — num values that have no existing data in the cache
- L325 _public member_ `uint64 ValuesNotInCacheBytes = 0;` — num bytes of new values written to the cache
- L326 _public member_ `uint32 ValuesChanged = 0;` — num values existing in the cache that don't match the new data
- L327 _public member_ `uint64 ValuesChangedBytes = 0;` — num bytes of changed values detected (note this tracks the entire value, not the individual changes)
- L328 _public member_ `uint32 ValuesNotInRequest = 0;` — num values that were in the cache before, but not in the new data
- L329 _public member_ `uint64 ValuesNotInRequestBytes = 0;` — num bytes of data we are no longer writing in values
- L331 _public function_ `const FDerivedDataCacheVerificationStat& operator+=(const FDerivedDataCacheVerificationStat& OtherStat)`

#### struct `FDerivedDataCacheVerificationStats`  
`struct FDerivedDataCacheVerificationStats`  
_L350-353_
- L352 _public member_ `TArray<FDerivedDataCacheVerificationStat> Entries;`

#### Free symbols / members of external scopes

- L130 _prototype_ `COOK_STAT(using FDerivedDataCacheSummaryStat = FCookStatsManager::StringKeyValue);`
- L355 _prototype_ `void GatherDerivedDataCacheResourceStats(TArray<FDerivedDataCacheResourceStat>& DDCResourceStats);`
- L356 _prototype_ `void GatherDerivedDataCacheSummaryStats(FDerivedDataCacheSummaryStats& DDCSummaryStats);`

### `Source/Developer/DerivedDataCache/Public/DerivedDataChunk.h` (Public)


#### struct `UE::DerivedData::TChunkEqual`  
`struct TChunkEqual`  
_L11-18_
- desc: Binary predicate that compares chunks by key, then value ID, then raw offset.
- L14 _public function_ `template <typename ChunkTypeA, typename ChunkTypeB> inline bool operator()(ChunkTypeA&& A, ChunkTypeB&& B) const`

#### struct `UE::DerivedData::TChunkLess`  
`struct TChunkLess`  
_L20-43_
- desc: Binary predicate that compares chunks by key, then value ID, then raw offset.
- L23 _public function_ `template <typename ChunkTypeA, typename ChunkTypeB> inline bool operator()(ChunkTypeA&& A, ChunkTypeB&& B) const`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace DerivedData` (scope `UE`)

### `Source/Developer/DerivedDataCache/Public/DerivedDataPluginInterface.h` (Public)


#### class `FDerivedDataPluginInterface`  
`class FDerivedDataPluginInterface`  
_L12-57_
- desc: Interface for data deriving backends This API will not be called concurrently, except that Build might be called on different instances if IsBuildThreadsafe.
- L15 _public prototype_ `virtual ~FDerivedDataPluginInterface() = default;`
- L20 _public prototype_ `virtual const TCHAR* GetPluginName() const = 0;` — Get the plugin name, this is used as the first part of the cache key @return	Name of the plugin
- L26 _public prototype_ `virtual const TCHAR* GetVersionString() const = 0;` — Get the version of the plugin, this is used as part of the cache key. This is supposed to be a guid string ( ex. "69C8C8A6-A9F8-4EFC-875C-CFBB72E66486" ) @return	Version string of the plugin
- L32 _public prototype_ `virtual FString GetPluginSpecificCacheKeySuffix() const = 0;` — Returns the largest and plugin specific part of the cache key. This must be a alphanumeric+underscore @return	Version number of the plugin, for licensees.
- L37 _public prototype_ `virtual bool IsBuildThreadsafe() const = 0;` — Indicates that this plugin is threadsafe. Note, the system itself will not call it concurrently if this false, however, then you are responsible for not calling the system itself concurrently. @return	true if this plugin is threadsafe
- L43 _public function_ `virtual FQueuedThreadPool* GetCustomThreadPool() const` — `UE_DEPRECATED(5.5, "GetCustomThreadPool() is no longer supported.")` — If IsBuildThreadsafe() returns true, then this is the thread pool that is used to run the background task. @return	The threadpool to run the task with
- L46 _public function_ `virtual bool IsDeterministic() const` — Indicated that this plugin generates deterministic data. This is used for DDC verification
- L49 _public function_ `virtual FString GetDebugContextString() const` — A string used to describe the data being generated. Typically the path to the object that it is generated from is sufficient.
- L56 _public prototype_ `virtual bool Build(TArray<uint8>& OutData) = 0;` — Does the work of deriving the data. @param	OutData	Array of bytes to fill in with the result data @return	true if successful, in the event of failure the cache is not updated and failure is propagated to the original caller.

### `Source/Developer/DerivedDataCache/Public/DerivedDataRequest.h` (Public)


#### class `UE::DerivedData::IRequest`  
`class IRequest`  
_L26-59_
- desc: Interface to an asynchronous request that can be prioritized or canceled. Use IRequestOwner, typically FRequestOwner, to reference requests between its Begin and End. Requests typically invoke a callback on completion, and must not return from Cancel or Wait on any thread until any associated callbacks have finished executing. This property is crucial to allowing requests to be chained or nested by creating new requests from within callbacks. @see FRequestBase @see FRequestOwner @see IRequestOwner
- L29 _public prototype_ `virtual ~IRequest() = default;`
- L36 _public prototype_ `virtual void SetPriority(EPriority Priority) = 0;` — Set the priority of the request. @param Priority   The priority, which may be higher or lower than the existing priority.
- L44 _public prototype_ `virtual void Cancel() = 0;` — Cancel the request and invoke any associated callback. Must not return until any callback for the request has finished executing, and the request has been removed from its owner by calling IRequestOwner::End.
- L52 _public prototype_ `virtual void Wait() = 0;` — Block the calling thread until the request is complete. Must not return until any callback for the request has finished executing, and the request has been removed from its owner by calling IRequestOwner::End.
- L55 _public prototype_ `virtual void AddRef() const = 0;` — Add a reference to the request.
- L58 _public prototype_ `virtual void Release() const = 0;` — Release a reference. The request is deleted when the last reference is released.

#### class `UE::DerivedData::FRequestBase`  
`class FRequestBase : public IRequest`  
_L62-85_
- inherits: `IRequest`
- desc: An asynchronous request base type that provides reference counting.
- L65 _public prototype_ `FRequestBase() = default;`
- L66 _public prototype_ `~FRequestBase() override = default;`
- L67 _public prototype_ `FRequestBase(const FRequestBase&) = delete;`
- L68 _public prototype_ `FRequestBase& operator=(const FRequestBase&) = delete;`
- L70 _public function_ `inline void AddRef() const final`
- L75 _public function_ `inline void Release() const final`
- L84 _private member_ `mutable std::atomic<uint32> ReferenceCount{0};`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace DerivedData` (scope `UE`)
- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace DerivedData` (scope `UE`)

### `Source/Developer/DerivedDataCache/Public/DerivedDataRequestOwner.h` (Public)


#### enum `UE::DerivedData::ERequestBarrierFlags`  
`enum class ERequestBarrierFlags : uint32`  
_L24-30_
- desc: Flags to control the behavior of request barriers.
- L27 _public enumerator_ `None = 0` — A value without any flags set.
- L29 _public enumerator_ `Priority = 1 << 0` — Within the barrier, calls to SetPriority are replayed to requests in calls to Begin.

#### class `UE::DerivedData::IRequestOwner`  
`class IRequestOwner`  
_L47-96_
- desc: A request owner manages requests throughout their execution. Requests are expected to call Begin when created, and End when finished, with their completion callback and arguments passed to End when possible. If a request needs to invoke more than one callback, have a request barrier in scope when executing callbacks to ensure that new requests are prioritized properly when the priority is being changed from another thread. The owner is responsible for keeping itself alive while it has active requests or barriers. @see FRequestBarrier @see FRequestOwner
- L56 _public prototype_ `virtual void Begin(IRequest* Request) = 0;` — Begin tracking for the request. The owner will hold a reference to the request until End is called, and forward any cancel operation or priority change to the request. Begin must return before End is called.
- L65 _public prototype_ `virtual TRefCountPtr<IRequest> End(IRequest* Request) = 0;` — End tracking for the request. Requests with a single completion callback should use the callback overload of End. @return The reference to the request that was held by the owner.
- L76 _public prototype_ `template <typename CallbackType, typename... CallbackArgTypes> inline TRefCountPtr<IRequest> End(IRequest* Request, CallbackType&& Callback, CallbackArgTypes&&... CallbackArgs);` — End tracking of the request. Begins a barrier, ends the request, invokes the callback, then ends the barrier. Keeps its reference to the request until the callback has returned. @return The reference to the request that was held by the owner.
- L79 _public prototype_ `UE_INTERNAL virtual void BeginBarrier(const FRequestBarrier& Barrier) = 0;` — See FRequestBarrier.
- L80 _public prototype_ `UE_INTERNAL virtual void EndBarrier(const FRequestBarrier& Barrier) = 0;`
- L83 _public prototype_ `virtual EPriority GetPriority() const = 0;` — Returns the priority that new requests are expected to inherit.
- L85 _public prototype_ `virtual bool IsCanceled() const = 0;` — Returns whether the owner has been canceled, which new requests are expected to check.
- L95 _public prototype_ `void LaunchTask(const TCHAR* DebugName, TUniqueFunction<void ()>&& TaskBody);` — Launches a task that executes the task body when scheduled. The task inherits the current priority of this request owner. The task is launched as a new request within this request owner. @note The debug name is not copied and must remain valid for the duration of the task.
- L182 _function_ `template <typename CallbackType, typename... CallbackArgTypes> TRefCountPtr<IRequest> IRequestOwner::End(IRequest* Request, CallbackType&& Callback, CallbackArgTypes&&... CallbackArgs)`

#### class `UE::DerivedData::FRequestOwner`  
`class FRequestOwner`  
_L106-151_
- desc: A concrete request owner that also presents as a request. Request owners may be moved but not copied, and cancel any outstanding requests on destruction unless KeepAlive has been called. @see IRequestOwner
- L110 _public prototype_ `explicit FRequestOwner(EPriority Priority);` — Construct a request owner with the given priority.
- L112 _public prototype_ `FRequestOwner(FRequestOwner&&) = default;`
- L113 _public prototype_ `FRequestOwner& operator=(FRequestOwner&&) = default;`
- L115 _public prototype_ `FRequestOwner(const FRequestOwner&) = delete;`
- L116 _public prototype_ `FRequestOwner& operator=(const FRequestOwner&) = delete;`
- L119 _public prototype_ `void KeepAlive();` — Keep requests in the owner alive until complete, even after destruction of the owner.
- L122 _public prototype_ `EPriority GetPriority() const;` — Returns the priority that new requests are expected to inherit.
- L124 _public prototype_ `void SetPriority(EPriority Priority);` — Set the priority of active and future requests in the owner.
- L126 _public prototype_ `void Cancel();` — Cancel any active and future requests in the owner.
- L128 _public prototype_ `void Wait();` — Wait for any active and future requests or barriers in the owner.
- L130 _public prototype_ `bool Poll() const;` — Poll the owner for active requests or barriers, returning false if it has either and true otherwise.
- L133 _public function_ `inline bool IsCanceled() const` — Returns whether the owner has been canceled, which new requests are expected to check.
- L136 _public function_ `inline void LaunchTask(const TCHAR* DebugName, TUniqueFunction<void ()>&& TaskBody)` — Launches a task that executes the task body when scheduled. See IRequestOwner::LaunchTask.
- L142 _public function_ `inline operator IRequestOwner&()` — Access as a request owner.
- L144 _public prototype_ `operator IRequest*();` — Access as a request.
- L147 _private prototype_ `static void Destroy(IRequestOwner& SharedOwner);`
- L150 _private member_ `TUniquePtr<IRequestOwner, FDeleteOwner> Owner;`

#### struct `UE::DerivedData::FRequestOwner::FDeleteOwner`  
`struct FDeleteOwner`  
_L149-149_
- L149 _public function_ `struct FDeleteOwner`

#### class `UE::DerivedData::FRequestBarrier`  
`class FRequestBarrier`  
_L160-179_
- desc: A request barrier is expected to be used when an owner may have new requests added to it. An owner may not consider its execution to be complete in the presence of a barrier, and needs to take note of priority changes that occur while within a barrier, since newly-added requests may have been created with the previous priority value.
- L163 _public prototype_ `explicit FRequestBarrier(IRequestOwner& Owner, ERequestBarrierFlags Flags = ERequestBarrierFlags::None);`
- L164 _public prototype_ `~FRequestBarrier();`
- L166 _public prototype_ `FRequestBarrier(const FRequestBarrier&) = delete;`
- L167 _public prototype_ `FRequestBarrier& operator=(const FRequestBarrier&) = delete;`
- L169 _public function_ `UE_INTERNAL inline ERequestBarrierFlags GetFlags() const`
- L172 _public prototype_ `UE_INTERNAL static bool HasBarrierForOwnerOnCallingThread(IRequestOwner& QueryOwner);` — Returns true if the calling thread has an active barrier for the owner.
- L176 _private member_ `IRequestOwner& Owner;`
- L177 _private member_ `FRequestBarrier* NextOnThread;`
- L178 _private member_ `ERequestBarrierFlags Flags;`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API DERIVEDDATACACHE_API`
- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace DerivedData` (scope `UE`)
- L17 _namespace_ `namespace UE`
- L17 _namespace_ `namespace DerivedData` (scope `UE`)
- L18 _namespace_ `namespace UE`
- L18 _namespace_ `namespace DerivedData` (scope `UE`)
- L20 _namespace_ `namespace UE`
- L20 _namespace_ `namespace DerivedData` (scope `UE`)
- L32 _prototype_ `ENUM_CLASS_FLAGS(ERequestBarrierFlags);` (scope `UE::DerivedData`)

### `Source/Developer/DerivedDataCache/Public/DerivedDataRequestTypes.h` (Public)


#### enum `UE::DerivedData::EPriority`  
`enum class EPriority : uint8`  
_L16-49_
- desc: Priority for scheduling a request.
- L22 _public enumerator_ `Lowest` — Lowest is the minimum priority for asynchronous requests, and primarily for requests that are speculative in nature, while minimizing impact on other requests.
- L27 _public enumerator_ `Low` — Low is intended for requests that are below the default priority, but are used for operations that the program will execute now rather than at an unknown time in the future.
- L31 _public enumerator_ `Normal` — Normal is intended as the default request priority.
- L36 _public enumerator_ `High` — High is intended for requests that are on the critical path, but are not required to maintain interactivity of the program.
- L41 _public enumerator_ `Highest` — Highest is the maximum priority for asynchronous requests, and intended for requests that are required to maintain interactivity of the program.
- L48 _public enumerator_ `Blocking` — Blocking is to be used only when the thread making the request will wait on completion of the request before doing any other work. Requests at this priority level will be processed before any request at a lower priority level. This priority permits a request to be processed on the thread making the request. Waiting on a request may increase its priority to this level.

#### enum `UE::DerivedData::EStatus`  
`enum class EStatus : uint8`  
_L66-74_
- desc: Status of a request that has completed.
- L69 _public enumerator_ `Ok` — The request completed successfully. Any requested data is available.
- L71 _public enumerator_ `Error` — The request completed unsuccessfully. Any requested data is not available.
- L73 _public enumerator_ `Canceled` — The request was canceled before it completed. Any requested data is not available.

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API DERIVEDDATACACHE_API`
- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace DerivedData` (scope `UE`)
- L52 _prototype_ `FAnsiStringBuilderBase& operator<<(FAnsiStringBuilderBase& Builder, EPriority Priority);` (scope `UE::DerivedData`) — Append a non-empty text version of the priority to the builder.
- L53 _prototype_ `FWideStringBuilderBase& operator<<(FWideStringBuilderBase& Builder, EPriority Priority);` (scope `UE::DerivedData`)
- L54 _prototype_ `FUtf8StringBuilderBase& operator<<(FUtf8StringBuilderBase& Builder, EPriority Priority);` (scope `UE::DerivedData`)
- L57 _prototype_ `bool TryLexFromString(EPriority& OutPriority, FUtf8StringView String);` (scope `UE::DerivedData`) — Try to parse a priority from text written by operator<<.
- L58 _prototype_ `bool TryLexFromString(EPriority& OutPriority, FWideStringView String);` (scope `UE::DerivedData`)
- L61 _prototype_ `EQueuedWorkPriority ConvertToQueuedWorkPriority(EPriority Priority);` (scope `UE::DerivedData`) — Converts to a queued work priority. Asserts on invalid priority values.
- L63 _prototype_ `EPriority ConvertFromQueuedWorkPriority(EQueuedWorkPriority Priority);` (scope `UE::DerivedData`) — Converts from a queued work priority. Asserts on invalid priority values.
- L77 _prototype_ `FAnsiStringBuilderBase& operator<<(FAnsiStringBuilderBase& Builder, EStatus Status);` (scope `UE::DerivedData`) — Append a non-empty text version of the status to the builder.
- L78 _prototype_ `FWideStringBuilderBase& operator<<(FWideStringBuilderBase& Builder, EStatus Status);` (scope `UE::DerivedData`)
- L79 _prototype_ `FUtf8StringBuilderBase& operator<<(FUtf8StringBuilderBase& Builder, EStatus Status);` (scope `UE::DerivedData`)
- L82 _prototype_ `bool TryLexFromString(EStatus& OutStatus, FUtf8StringView String);` (scope `UE::DerivedData`) — Try to parse a status from text written by operator<<.
- L83 _prototype_ `bool TryLexFromString(EStatus& OutStatus, FWideStringView String);` (scope `UE::DerivedData`)

### `Source/Developer/DerivedDataCache/Public/DerivedDataSerialization.h` (Public)


#### enum `UE::DerivedData::EMetaSaveFormat`  
`enum class EMetaSaveFormat`  
_L48-54_
- desc: Format in which to save metadata.
- L51 _public enumerator_ `Object` — Save metadata as an object field.
- L53 _public enumerator_ `Attachment` — Save metadata as an attachment referenced by its hash and size.

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API DERIVEDDATACACHE_API`
- L17 _namespace_ `namespace UE`
- L17 _namespace_ `namespace DerivedData` (scope `UE`)
- L18 _namespace_ `namespace UE`
- L18 _namespace_ `namespace DerivedData` (scope `UE`)
- L19 _namespace_ `namespace UE`
- L19 _namespace_ `namespace DerivedData` (scope `UE`)
- L20 _namespace_ `namespace UE`
- L20 _namespace_ `namespace DerivedData` (scope `UE`)
- L21 _namespace_ `namespace UE`
- L21 _namespace_ `namespace DerivedData` (scope `UE`)
- L22 _namespace_ `namespace UE`
- L22 _namespace_ `namespace DerivedData` (scope `UE`)
- L23 _namespace_ `namespace UE`
- L23 _namespace_ `namespace DerivedData` (scope `UE`)
- L24 _namespace_ `namespace UE`
- L24 _namespace_ `namespace DerivedData` (scope `UE`)
- L25 _namespace_ `namespace UE`
- L25 _namespace_ `namespace DerivedData` (scope `UE`)
- L26 _namespace_ `namespace UE`
- L26 _namespace_ `namespace DerivedData` (scope `UE`)
- L27 _namespace_ `namespace UE`
- L27 _namespace_ `namespace DerivedData` (scope `UE`)
- L28 _namespace_ `namespace UE`
- L28 _namespace_ `namespace DerivedData` (scope `UE`)
- L29 _namespace_ `namespace UE`
- L29 _namespace_ `namespace DerivedData` (scope `UE`)
- L30 _namespace_ `namespace UE`
- L30 _namespace_ `namespace DerivedData` (scope `UE`)
- L31 _namespace_ `namespace UE`
- L31 _namespace_ `namespace DerivedData` (scope `UE`)
- L32 _namespace_ `namespace UE`
- L32 _namespace_ `namespace DerivedData` (scope `UE`)
- L33 _namespace_ `namespace UE`
- L33 _namespace_ `namespace DerivedData` (scope `UE`)
- L34 _namespace_ `namespace UE`
- L34 _namespace_ `namespace DerivedData` (scope `UE`)
- L35 _namespace_ `namespace UE`
- L35 _namespace_ `namespace DerivedData` (scope `UE`)
- L36 _namespace_ `namespace UE`
- L36 _namespace_ `namespace DerivedData` (scope `UE`)
- L37 _namespace_ `namespace UE`
- L37 _namespace_ `namespace DerivedData` (scope `UE`)
- L38 _namespace_ `namespace UE`
- L38 _namespace_ `namespace DerivedData` (scope `UE`)
- L39 _namespace_ `namespace UE`
- L39 _namespace_ `namespace DerivedData` (scope `UE`)
- L41 _namespace_ `namespace UE`
- L41 _namespace_ `namespace DerivedData` (scope `UE`)
- L44 _typedef_ `using FSaveAttachmentFn = TFunctionWithContext<void (FCbAttachment&& Attachment)>;` (scope `UE::DerivedData`)
- L45 _typedef_ `using FLoadAttachmentFn = TFunctionWithContext<FCbAttachment (const FIoHash& Hash)>;` (scope `UE::DerivedData`)
- L57 _prototype_ `void SaveMetaToCompactBinary(FCbWriter& Writer, const FCbObject& Meta, EMetaSaveFormat MetaFormat, FSaveAttachmentFn SaveAttachment = nullptr);` (scope `UE::DerivedData`) — Save metadata to a stream of named fields. Caller must call BeginObject/EndObject to save this into an object.
- L58 _prototype_ `bool LoadMetaFromCompactBinary(FCbFieldView Field, FCbObject& OutMeta, FLoadAttachmentFn LoadAttachment = nullptr);` (scope `UE::DerivedData`)
- L63 _prototype_ `FCbWriter& operator<<(FCbWriter& Writer, const FCacheGetRequest& Request);` (scope `UE::DerivedData`) — `UE_DEPRECATED(5.8, "Call SaveToCompactBinary(Writer, Request).")`
- L65 _prototype_ `FCbWriter& operator<<(FCbWriter& Writer, const FCacheGetValueRequest& Request);` (scope `UE::DerivedData`) — `UE_DEPRECATED(5.8, "Call SaveToCompactBinary(Writer, Request).")`
- L67 _prototype_ `FCbWriter& operator<<(FCbWriter& Writer, const FCacheGetChunkRequest& Request);` (scope `UE::DerivedData`) — `UE_DEPRECATED(5.8, "Call SaveToCompactBinary(Writer, Request).")`
- L69 _prototype_ `void SaveToCompactBinary(FCbWriter& Writer, const FCachePutRequest& Request, const FCachePutResponse* Response = nullptr, FSaveAttachmentFn SaveAttachment = nullptr);` (scope `UE::DerivedData`)
- L70 _prototype_ `bool LoadFromCompactBinary(FCbFieldView Field, TOptional<FCachePutRequest>& OutRequest, TOptional<FCachePutResponse>* OutResponse = nullptr, FLoadAttachmentFn LoadAttachment = nullptr);` (scope `UE::DerivedData`)
- L72 _prototype_ `void SaveToCompactBinary(FCbWriter& Writer, const FCacheGetRequest& Request, const FCacheGetResponse* Response = nullptr, FSaveAttachmentFn SaveAttachment = nullptr);` (scope `UE::DerivedData`)
- L73 _prototype_ `bool LoadFromCompactBinary(FCbFieldView Field, FCacheGetRequest& OutRequest, TOptional<FCacheGetResponse>* OutResponse = nullptr, FLoadAttachmentFn LoadAttachment = nullptr);` (scope `UE::DerivedData`)
- L75 _prototype_ `void SaveToCompactBinary(FCbWriter& Writer, const FCachePutValueRequest& Request, const FCachePutValueResponse* Response = nullptr, FSaveAttachmentFn SaveAttachment = nullptr);` (scope `UE::DerivedData`)
- L76 _prototype_ `bool LoadFromCompactBinary(FCbFieldView Field, FCachePutValueRequest& OutRequest, FCachePutValueResponse* OutResponse = nullptr, FLoadAttachmentFn LoadAttachment = nullptr);` (scope `UE::DerivedData`)
- L78 _prototype_ `void SaveToCompactBinary(FCbWriter& Writer, const FCacheGetValueRequest& Request, const FCacheGetValueResponse* Response = nullptr, FSaveAttachmentFn SaveAttachment = nullptr);` (scope `UE::DerivedData`)
- L79 _prototype_ `bool LoadFromCompactBinary(FCbFieldView Field, FCacheGetValueRequest& OutRequest, FCacheGetValueResponse* OutResponse = nullptr, FLoadAttachmentFn LoadAttachment = nullptr);` (scope `UE::DerivedData`)
- L81 _prototype_ `void SaveToCompactBinary(FCbWriter& Writer, const FCacheGetChunkRequest& Request, const FCacheGetChunkResponse* Response = nullptr, FSaveAttachmentFn SaveAttachment = nullptr);` (scope `UE::DerivedData`)
- L82 _prototype_ `bool LoadFromCompactBinary(FCbFieldView Field, FCacheGetChunkRequest& OutRequest, FCacheGetChunkResponse* OutResponse = nullptr, FLoadAttachmentFn LoadAttachment = nullptr);` (scope `UE::DerivedData`)
- L86 _prototype_ `FCbWriter& operator<<(FCbWriter& Writer, ECachePolicy Policy);` (scope `UE::DerivedData`)
- L87 _prototype_ `bool LoadFromCompactBinary(FCbFieldView Field, ECachePolicy& OutPolicy, ECachePolicy Default);` (scope `UE::DerivedData`)
- L89 _prototype_ `bool LoadFromCompactBinary(FCbFieldView Field, ECachePolicy& OutPolicy);` (scope `UE::DerivedData`) — `UE_DEPRECATED(5.8, "Call the overload with an explicit default of ECachePolicy::Default.")`
- L91 _prototype_ `FCbWriter& operator<<(FCbWriter& Writer, FCacheBucket Bucket);` (scope `UE::DerivedData`)
- L92 _prototype_ `bool LoadFromCompactBinary(FCbFieldView Field, FCacheBucket& OutBucket);` (scope `UE::DerivedData`)
- L94 _prototype_ `FCbWriter& operator<<(FCbWriter& Writer, const FCacheKey& Key);` (scope `UE::DerivedData`)
- L95 _prototype_ `bool LoadFromCompactBinary(FCbFieldView Field, FCacheKey& OutKey);` (scope `UE::DerivedData`)
- L99 _prototype_ `FCbWriter& operator<<(FCbWriter& Writer, ECacheMethod Method);` (scope `UE::DerivedData`)
- L100 _prototype_ `bool LoadFromCompactBinary(FCbFieldView Field, ECacheMethod& OutMethod);` (scope `UE::DerivedData`)
- L104 _prototype_ `FCbWriter& operator<<(FCbWriter& Writer, const FCacheValuePolicy& Policy);` (scope `UE::DerivedData`)
- L105 _prototype_ `bool LoadFromCompactBinary(FCbFieldView Field, FCacheValuePolicy& OutPolicy);` (scope `UE::DerivedData`)
- L107 _prototype_ `FCbWriter& operator<<(FCbWriter& Writer, const FCacheRecordPolicy& Policy);` (scope `UE::DerivedData`)
- L108 _prototype_ `bool LoadFromCompactBinary(FCbFieldView Field, FCacheRecordPolicy& OutPolicy);` (scope `UE::DerivedData`)
- L118 _prototype_ `void SaveToCompactBinary(FCbWriter& Writer, const FCacheRecord& Record, EMetaSaveFormat MetaFormat, FSaveAttachmentFn SaveAttachment = nullptr);` (scope `UE::DerivedData`) — Save a cache record as a stream of named fields. Attachments optionally saved to a callback. It is the responsibility of the caller to call BeginObject/EndObject to save this into an object. When SaveAttachment is provided, it is called for each attachment referenced by the saved record.
- L126 _prototype_ `bool LoadFromCompactBinary(FCbFieldView Field, FOptionalCacheRecord& OutRecord, FLoadAttachmentFn LoadAttachment = nullptr);` (scope `UE::DerivedData`) — Load a cache record from an object. Attachments optionally loaded from a callback. When LoadAttachment is provided, it is called for each attachment referenced by the loaded object. An attachment that cannot be loaded will be omitted from the returned record without failing the load.
- L130 _prototype_ `FCbWriter& operator<<(FCbWriter& Writer, EPriority Priority);` (scope `UE::DerivedData`)
- L131 _prototype_ `bool LoadFromCompactBinary(FCbFieldView Field, EPriority& OutPriority, EPriority Default);` (scope `UE::DerivedData`)
- L133 _prototype_ `bool LoadFromCompactBinary(FCbFieldView Field, EPriority& OutPriority);` (scope `UE::DerivedData`) — `UE_DEPRECATED(5.8, "Call the overload with an explicit default of EPriority::Normal.")`
- L135 _prototype_ `FCbWriter& operator<<(FCbWriter& Writer, EStatus Status);` (scope `UE::DerivedData`)
- L136 _prototype_ `bool LoadFromCompactBinary(FCbFieldView Field, EStatus& OutStatus, EStatus Default);` (scope `UE::DerivedData`)
- L138 _prototype_ `bool LoadFromCompactBinary(FCbFieldView Field, EStatus& OutStatus);` (scope `UE::DerivedData`) — `UE_DEPRECATED(5.8, "Call the overload with an explicit default of EStatus::Ok.")`
- L142 _prototype_ `FCbWriter& operator<<(FCbWriter& Writer, const FValue& Value);` (scope `UE::DerivedData`)
- L143 _prototype_ `FCbWriter& operator<<(FCbWriter& Writer, const FValueWithId& Value);` (scope `UE::DerivedData`)
- L145 _prototype_ `void SaveToCompactBinary(FCbWriter& Writer, const FValue& Value, FSaveAttachmentFn SaveAttachment = nullptr);` (scope `UE::DerivedData`)
- L146 _prototype_ `void SaveToCompactBinary(FCbWriter& Writer, const FValueWithId& Value, FSaveAttachmentFn SaveAttachment = nullptr);` (scope `UE::DerivedData`)
- L148 _prototype_ `bool LoadFromCompactBinary(FCbFieldView Field, FValue& OutValue, FLoadAttachmentFn LoadAttachment = nullptr);` (scope `UE::DerivedData`)
- L149 _prototype_ `bool LoadFromCompactBinary(FCbFieldView Field, FValueWithId& OutValue, FLoadAttachmentFn LoadAttachment = nullptr);` (scope `UE::DerivedData`)
- L153 _prototype_ `FCbWriter& operator<<(FCbWriter& Writer, const FValueId& Id);` (scope `UE::DerivedData`)
- L154 _prototype_ `bool LoadFromCompactBinary(FCbFieldView Field, FValueId& OutId);` (scope `UE::DerivedData`)

### `Source/Developer/DerivedDataCache/Public/DerivedDataThreadPoolTask.h` (Public)


#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API DERIVEDDATACACHE_API`
- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace DerivedData` (scope `UE`)
- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace DerivedData` (scope `UE`)
- L35 _prototype_ `void LaunchTaskInThreadPool( uint64 MemoryEstimate, const TCHAR* DebugName, IRequestOwner& Owner, FQueuedThreadPool* ThreadPool, TUniqueFunction<void ()>&& TaskBody);` (scope `UE::DerivedData`) — Launches a task in the thread pool that tracks the priority of the request owner. Waiting on or canceling the task before it has started executing in the thread pool will cause it to be retracted and executed on the thread that asked to wait or cancel. Passing a null thread pool will execute the task immediately on the calling thread. TaskBody is guaranteed to return before the request is considered complete. TaskBody is responsible for checking for cancellation by checking Owner.IsCanceled(). @param MemoryEstimate   The estimated peak memory required to execute TaskBody. @param DebugName        The name of the job, for debugging/logging purposes only. @param Owner            The owner of the request that will execute TaskBody. @param ThreadPool       The thread pool within which to execute the task, if not retracted. @param TaskBody         The task body that will be unconditionally executed exactly once.
- L44 _prototype_ `void LaunchTaskInThreadPool( IRequestOwner& Owner, FQueuedThreadPool* ThreadPool, TUniqueFunction<void ()>&& TaskBody);` (scope `UE::DerivedData`) — `UE_DEPRECATED(5.8, "Use LaunchTaskInThreadPool with DebugName and MemoryEstimate = 0.")` — with no MemoryEstimate arg, assumes 0 (none) not -1 (unknown/max)

### `Source/Developer/DerivedDataCache/Public/DerivedDataValue.h` (Public)


#### class `UE::DerivedData::FValue`  
`class FValue`  
_L23-70_
- desc: A value is a compressed buffer identified by its raw hash and raw size. A value without data may be used as a reference to the value.
- L32 _public prototype_ `static FValue Compress(const FCompositeBuffer& RawData, uint64 BlockSize = 0);` — Compress the buffer to a value using default derived data compression parameters. @param RawData     The raw data to be compressed. @param BlockSize   The power-of-two block size to encode raw data in. 0 is default.
- L33 _public prototype_ `static FValue Compress(const FSharedBuffer& RawData, uint64 BlockSize = 0);`
- L36 _public prototype_ `FValue() = default;` — Construct a null value, which is a hash and size of zero with no data.
- L39 _public prototype_ `inline FValue(const FIoHash& RawHash, uint64 RawSize);` — Construct a value reference from the hash and size of its data.
- L42 _public prototype_ `inline explicit FValue(const FCompressedBuffer& Data);` — Construct a value from a compressed buffer, which is cloned if not owned.
- L43 _public prototype_ `inline explicit FValue(FCompressedBuffer&& Data);`
- L46 _public function_ `inline const FIoHash& GetRawHash() const` — Returns the hash of the raw buffer (uncompressed) for the value.
- L49 _public function_ `inline uint64 GetRawSize() const` — Returns the size of the raw buffer (uncompressed) for the value.
- L52 _public function_ `inline const FCompressedBuffer& GetData() const` — Returns the compressed buffer for the value. May be null.
- L55 _public function_ `inline bool HasData() const` — Whether the compressed buffer for the value is available.
- L58 _public function_ `[[nodiscard]] inline FValue RemoveData() const` — Create a copy of the value with the data removed.
- L61 _public function_ `inline void Reset()` — Reset this to null.
- L64 _public member_ `static const FValue Null;` — A null value.
- L67 _private member_ `FIoHash RawHash;`
- L68 _private member_ `uint64 RawSize = 0;`
- L69 _private member_ `FCompressedBuffer Data;`
- L110 _member_ `inline const FValue FValue::Null;`
- L113 _function_ `inline FValue::FValue(const FIoHash& InRawHash, const uint64 InRawSize) : RawHash(InRawHash) , RawSize(InRawSize)`
- L119 _function_ `inline FValue::FValue(const FCompressedBuffer& InData) : RawHash(InData.GetRawHash()) , RawSize(InData.GetRawSize()) , Data(InData.MakeOwned())`
- L126 _function_ `inline FValue::FValue(FCompressedBuffer&& InData) : RawHash(InData.GetRawHash()) , RawSize(InData.GetRawSize()) , Data(MoveTemp(InData).MakeOwned())`

#### class `UE::DerivedData::FValueWithId`  
`class FValueWithId : public FValue`  
_L77-108_
- inherits: `FValue`
- desc: A value with an ID. Null if both ID and value are null. May have a null value with a non-null ID. A non-null value must have a non-null ID.
- L81 _public prototype_ `FValueWithId() = default;` — Construct a null value.
- L85 _public prototype_ `template <typename... ArgTypes> inline explicit FValueWithId(const FValueId& Id, ArgTypes&&... Args);` — Construct a value with a non-null ID and forward the other args to FValue().
- L88 _public function_ `inline const FValueId& GetId() const` — Returns the ID for the value.
- L91 _public function_ `[[nodiscard]] inline FValueWithId RemoveData() const` — Create a copy of the value with the data removed.
- L94 _public function_ `inline bool IsNull() const` — Whether this is null.
- L96 _public function_ `inline bool IsValid() const` — Whether this is not null.
- L98 _public function_ `inline explicit operator bool() const` — Whether this is not null.
- L101 _public function_ `inline void Reset()` — Reset this to null.
- L104 _public member_ `static const FValueWithId Null;` — A null value with a null ID.
- L107 _private member_ `FValueId Id;`
- L111 _member_ `inline const FValueWithId FValueWithId::Null;`
- L134 _function_ `template <typename... ArgTypes> inline FValueWithId::FValueWithId(const FValueId& InId, ArgTypes&&... InArgs) : FValue(Forward<ArgTypes>(InArgs)...) , Id(InId)`

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API DERIVEDDATACACHE_API`
- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace DerivedData` (scope `UE`)
- L142 _function_ `inline bool operator==(const FValue& A, const FValue& B)` (scope `UE::DerivedData`) — Compare values by the hash and size of their raw buffer.
- L148 _function_ `inline bool operator==(const FValueWithId& A, const FValueWithId& B)` (scope `UE::DerivedData`) — Compare values by their ID and the hash and size of their raw buffer.
- L156 _function_ `inline bool operator<(const FValue& A, const FValue& B)` (scope `UE::DerivedData`) — Compare values by the hash and size of their raw buffer.
- L164 _function_ `inline bool operator<(const FValueWithId& A, const FValueWithId& B)` (scope `UE::DerivedData`) — Compare values by their ID and the hash and size of their raw buffer.

### `Source/Developer/DerivedDataCache/Public/DerivedDataValueId.h` (Public)


#### struct `UE::DerivedData::FValueId`  
`struct FValueId`  
_L19-68_
- desc: A 12-byte value that uniquely identifies a value in the context that it was created.
- L22 _public typedef_ `using ByteArray = uint8[12];`
- L25 _public prototype_ `FValueId() = default;` — Construct a null ID.
- L28 _public prototype_ `inline explicit FValueId(const ByteArray& Id);` — Construct an ID from an array of 12 bytes.
- L31 _public prototype_ `explicit FValueId(FMemoryView Id);` — Construct an ID from a view of 12 bytes.
- L34 _public prototype_ `FValueId(const FCbObjectId& Id);` — Construct an ID from a Compact Binary Object ID.
- L37 _public prototype_ `operator FCbObjectId() const;` — Returns the ID as a Compact Binary Object ID.
- L40 _public prototype_ `[[nodiscard]] static FValueId FromHash(const FIoHash& Hash);` — Construct an ID from a non-zero hash.
- L43 _public prototype_ `[[nodiscard]] static FValueId FromName(FUtf8StringView Name);` — Construct an ID from a non-empty name.
- L44 _public prototype_ `[[nodiscard]] static FValueId FromName(FWideStringView Name);`
- L47 _public prototype_ `[[nodiscard]] FValueId MakeIndexed(int32 Index) const;` — Returns a copy of this ID with the last 4 bytes replaced by the index. Use for arrays of values.
- L50 _public function_ `inline const ByteArray& GetBytes() const` — Returns a reference to the raw byte array for the ID.
- L53 _public function_ `inline FMemoryView GetView() const` — Returns a view of the raw byte array for the ID.
- L56 _public prototype_ `inline bool IsNull() const;` — Whether this is null.
- L58 _public function_ `inline bool IsValid() const` — Whether this is not null.
- L61 _public function_ `inline void Reset()` — Reset this to null.
- L64 _public member_ `static const FValueId Null;` — A null ID.
- L67 _private member_ `alignas(uint32) ByteArray Bytes{};`
- L70 _member_ `inline const FValueId FValueId::Null;`
- L72 _function_ `inline FValueId::FValueId(const ByteArray& Id)`
- L105 _function_ `inline bool FValueId::IsNull() const`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API DERIVEDDATACACHE_API`
- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace DerivedData` (scope `UE`)
- L77 _function_ `inline bool operator==(const FValueId& A, const FValueId& B)` (scope `UE::DerivedData`)
- L82 _function_ `inline bool operator!=(const FValueId& A, const FValueId& B)` (scope `UE::DerivedData`)
- L87 _function_ `inline bool operator<(const FValueId& A, const FValueId& B)` (scope `UE::DerivedData`)
- L92 _function_ `inline uint32 GetTypeHash(const FValueId& Id)` (scope `UE::DerivedData`)
- L99 _function_ `template <typename CharType> inline TStringBuilderBase<CharType>& operator<<(TStringBuilderBase<CharType>& Builder, const FValueId& Id)` (scope `UE::DerivedData`) — Convert the ID to a 24-character hex string.
