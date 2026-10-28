# Runtime / AutoRTFM

- module root: `Source/Runtime/AutoRTFM`
- headers: 47; symbols: 1496
- symbol kinds: class=19, enum=22, enumerator=109, externvar=8, function=469, macro=185, member=265, namespace=54, prototype=242, struct=53, typedef=52, union=1, variable=17
- PrivateIncludePathModuleNames: Core

### `Source/Runtime/AutoRTFM/Private/Allocator.h` (Private)


#### struct `AutoRTFM::FAllocator`  
`struct AUTORTFM_INTERNAL FAllocator`  
_L52-77_
- desc: The AutoRTFM default Allocator that wraps the external API's memory allocation functions.
- L54 _public function_ `static inline void* Allocate(size_t Size, size_t Alignment)`
- L60 _public function_ `static inline void* Reallocate(void* Pointer, size_t Size, size_t Alignment, size_t PreviousSize)`
- L66 _public function_ `static inline void* AllocateZeroed(size_t Size, size_t Alignment)`
- L72 _public function_ `static inline void Free(void* Pointer, size_t AllocationSize)`

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace AutoRTFM`
- L83 _function_ `template <typename Allocator, typename T, typename... ARGS> static inline T* New(ARGS&&... Args)` (scope `AutoRTFM`) — Constructs a new T with the given arguments, using Allocator.
- L91 _function_ `template <typename Allocator, typename T, typename... ARGS> static inline void Delete(T* Ptr)` (scope `AutoRTFM`) — Destructs and frees a T* allocated with New<Allocator, T>(...). Ptr should be immediately set to null after calling.

### `Source/Runtime/AutoRTFM/Private/BlockAllocator.h` (Private)


#### class `AutoRTFM::TBlockAllocator`  
`template <size_t InlineBlockDataSize = 256, size_t DataAlignment = 16, size_t GrowthPercentage = 200> class AUTORTFM_INTERNAL TBlockAllocator`  
_L25-125_
- desc: A single-threaded, bump memory allocator that sub-allocates out of blocks of inline memory and once that's exhausted, from heap allocated memory. All allocated memory is freed when the TBlockAllocator is destructed. There is no way to free individual allocations. Template parameters: InlineBlockDataSize - The size of the data section of the inline block. DataAlignment - The maximum supported alignment of data from this allocator. GrowthPercentage - The percentage to grow the block size each reallocation.
- L29 _public prototype_ `TBlockAllocator() = default;` — Constructor
- L32 _public function_ `~TBlockAllocator()` — Destructor - frees all the memory allocated by the allocator.
- L38 _public function_ `void FreeAll()` — Frees all allocations made by the allocator.
- L52 _public function_ `inline void* Allocate(size_t Size, size_t Alignment)` — Allocates memory from the block allocator. Alignment must be a power of two and no larger than DataAlignment.
- L72 _private prototype_ `TBlockAllocator(TBlockAllocator&&) = delete;`
- L73 _private prototype_ `TBlockAllocator(const TBlockAllocator&) = delete;`
- L74 _private prototype_ `TBlockAllocator& operator=(const TBlockAllocator&) = delete;`
- L75 _private prototype_ `TBlockAllocator& operator=(TBlockAllocator&&) = delete;`
- L77 _private member_ `static constexpr size_t BlockAlignment = std::max<size_t>(DataAlignment, 8);`
- L121 _private member_ `size_t NextBlockSize = InlineBlockDataSize * GrowthPercentage / 100;`
- L122 _private member_ `FBlockHeader* Tail = &InlineBlock;`
- L123 _private member_ `FBlockHeader InlineBlock{ nullptr, InlineBlockDataSize};`
- L124 _private member_ `alignas(BlockAlignment) std::byte Data[InlineBlockDataSize];`

#### struct `AutoRTFM::TBlockAllocator::FBlockHeader`  
`struct alignas(BlockAlignment) FBlockHeader`  
_L79-117_
- L82 _public member_ `FBlockHeader* const Prev = nullptr;` — The previous FBlock in the singly linked-list
- L84 _public member_ `size_t const BlockDataSize;` — The size of the block's data
- L86 _public member_ `std::byte* NextAllocation = reinterpret_cast<std::byte*>(this) + sizeof(FBlockHeader);` — Pointer to the next sub-allocation.
- L90 _public function_ `static FBlockHeader* New(FBlockHeader* Prev, size_t BlockDataSize)` — Allocates, constructs and returns a new block from the heap-allocated memory.
- L97 _public function_ `inline size_t TotalSize() const` — Returns the total size in bytes of this block.
- L104 _public function_ `inline void* TryAllocate(size_t Size, size_t Alignment)` — Attempts to sub-allocate with out of this block. Returns a pointer to the sub-allocated memory on success, or nullptr on failure.

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace AutoRTFM`

### `Source/Runtime/AutoRTFM/Private/BuildMacros.h` (Private)


#### Free symbols / members of external scopes

- L7 _macro_ `#define AUTORTFM_BUILD_DEBUG 1`
- L9 _macro_ `#define AUTORTFM_BUILD_DEBUG 0`
- L15 _macro_ `#define AUTORTFM_BUILD_DEVELOPMENT 1`
- L17 _macro_ `#define AUTORTFM_BUILD_DEVELOPMENT 0`
- L23 _macro_ `#define AUTORTFM_BUILD_TEST 1`
- L25 _macro_ `#define AUTORTFM_BUILD_TEST 0`
- L31 _macro_ `#define AUTORTFM_BUILD_SHIPPING 1`
- L33 _macro_ `#define AUTORTFM_BUILD_SHIPPING 0`
- L41 _macro_ `#define AUTORTFM_PLATFORM_WINDOWS 1`
- L43 _macro_ `#define AUTORTFM_PLATFORM_WINDOWS 0`
- L49 _macro_ `#define AUTORTFM_PLATFORM_MAC 1`
- L51 _macro_ `#define AUTORTFM_PLATFORM_MAC 0`
- L57 _macro_ `#define AUTORTFM_PLATFORM_LINUX 1`
- L59 _macro_ `#define AUTORTFM_PLATFORM_LINUX 0`
- L64 _macro_ `#define AUTORTFM_ARCHITECTURE_X64 1`
- L66 _macro_ `#define AUTORTFM_ARCHITECTURE_X64 0`
- L71 _macro_ `#define AUTORTFM_EXCEPTIONS_ENABLED 1`
- L75 _macro_ `#define AUTORTFM_EXCEPTIONS_ENABLED 0`

### `Source/Runtime/AutoRTFM/Private/CallNest.h` (Private)


#### class `AutoRTFM::FCallNest`  
`class AUTORTFM_DISABLE FCallNest final`  
_L15-28_
- L18 _public function_ `FCallNest(FCallNest* Parent, TransactionID Transaction) : Parent(Parent), Transaction(Transaction)`
- L20 _public member_ `FCallNest* const Parent;`
- L21 _public member_ `TransactionID const Transaction;`
- L22 _public member_ `FLongJump AbortJump;`
- L23 _public member_ `ETransactionStatus Status = ETransactionStatus::Executing;`
- L27 _public prototype_ `template <typename TTryFunctor> ETransactionStatus Try(const TTryFunctor& TryFunctor);` — Whether this succeeded or not is reflected in Context::GetStatus().

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace AutoRTFM`

### `Source/Runtime/AutoRTFM/Private/CallNestInlines.h` (Private)


#### Free symbols / members of external scopes

- L9 _namespace_ `namespace AutoRTFM`
- L13 _function_ `template <typename TTryFunctor> ETransactionStatus FCallNest::Try(const TTryFunctor& TryFunctor)` (scope `AutoRTFM::FCallNest`)
- L17 _function_ `` (scope `AutoRTFM::FCallNest::Try`)
- L21 _function_ `}, [&]()` (scope `AutoRTFM::FCallNest::Try`)

### `Source/Runtime/AutoRTFM/Private/CallstackTree.h` (Private)


#### class `AutoRTFM::TCallstackTree`  
`template <Allocator Allocator = FAllocator> class AUTORTFM_INTERNAL TCallstackTree final`  
_L22-121_
- desc: FCallstackTree is a store for callstacks that internally holds a DAG of frames which reduces memory consumption by de-duplicating common base frames.
- L25 _public typedef_ `using FHandle = uint32_t;`
- L26 _public typedef_ `using FCallstack = TStack<autortfm_callstack_frame, 8, Allocator>;`
- L27 _public member_ `static constexpr FHandle InvalidHandle = 0;`
- L28 _public member_ `static constexpr FHandle MaxHandle = ~InvalidHandle;`
- L33 _public function_ `FHandle Add(size_t NumFrames, autortfm_callstack_frame const* Frames)` — Adds a callstack consisting of NumFrames frames at Frames. Frames starts with the most deeply-nested frame pointer. Returns a handle that can be passed to Get() to retrieve the callstack.
- L59 _public function_ `FCallstack Get(FHandle Handle) const` — Retrieves a callstack previously added with Add().
- L80 _private typedef_ `using FEntryList = TStack<FEntry, 32, Allocator>;`
- L115 _private member_ `FEntryList Entries;`
- L116 _private member_ `std::unordered_set<FHandle, FHasher, FEquality, StlAllocator<FHandle, Allocator>> Lookup{ 32, FHasher{Entries}, FEquality{Entries}, };`

#### struct `AutoRTFM::TCallstackTree::FEntry`  
`struct FEntry`  
_L72-78_
- L74 _public member_ `FHandle Parent;`
- L75 _public member_ `autortfm_callstack_frame Frame;`
- L77 _public prototype_ `bool operator==(const FEntry&) const = default;`

#### struct `AutoRTFM::TCallstackTree::FHasher`  
`struct FHasher`  
_L82-95_
- L84 _public typedef_ `using is_transparent = void;`
- L85 _public member_ `const FEntryList& Entries;`
- L86 _public function_ `size_t operator()(const FEntry& Entry) const`
- L90 _public function_ `size_t operator()(FHandle Handle) const`

#### struct `AutoRTFM::TCallstackTree::FEquality`  
`struct FEquality`  
_L97-113_
- L99 _public typedef_ `using is_transparent = void;`
- L100 _public member_ `const FEntryList& Entries;`
- L101 _public function_ `size_t operator()(const FEntry& Entry, FHandle Handle) const`
- L105 _public function_ `size_t operator()(FHandle Handle, const FEntry& Entry) const`
- L109 _public function_ `size_t operator()(FHandle A, FHandle B) const`

#### Free symbols / members of external scopes

- L16 _namespace_ `namespace AutoRTFM`

### `Source/Runtime/AutoRTFM/Private/ContainerValidation.h` (Private)


#### enum `AutoRTFM::EContainerValidation`  
`enum class EContainerValidation`  
_L12-16_
- desc: Enumerator used to control validity assertions for containers (bounds checking, etc).
- L14 _public enumerator_ `Enabled`
- L15 _public enumerator_ `Disabled`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace AutoRTFM`

### `Source/Runtime/AutoRTFM/Private/Context.h` (Private)


#### class `AutoRTFM::FContext`  
`class AUTORTFM_INTERNAL FContext final`  
_L21-236_
- L23 _private typedef_ `using FTaskPool = typename TTaskArray<TTask<void()>>::FEntryPool;`
- L24 _private typedef_ `using FTransactionPool = TIntrusivePool<FTransaction, 16>;`
- L25 _private typedef_ `using FCallNestPool = TPool<FCallNest, 16>;`
- L28 _public prototype_ `static FContext* Create();`
- L29 _public prototype_ `static FContext* Get();`
- L30 _public prototype_ `static void Destroy();`
- L33 _public prototype_ `ETransactionResult Transact(void (*UninstrumentedFunction)(void*), void (*InstrumentedFunction)(void*), void* Arg);` — This is public API
- L35 _public prototype_ `ETransactionStatus CallClosedNest(void (*ClosedFunction)(void* Arg), void* Arg);`
- L45 _public prototype_ `void StartTransaction();` — Begins an unscoped transaction. It is common for a transaction to be started and then immediately aborted without actually being used. As a performance optimization, StartTransaction() increments NumDeferredTransactions, which represents the number of "deferred" transactions at the top of the transaction stack. Deferred transactions will be lazily backed by an FTransaction on the first call to MaterializeDeferredTransactions() or GetCurrentTransaction().
- L52 _public prototype_ `void AbortTransaction(ETransactionStatus Reason);` — Ends a scoped or unscoped transaction, undoing all writes recorded by the transaction and calling all registered on-abort handlers. If the current transaction is materialized, then the FTransaction is popped from the transaction stack, otherwise NumDeferredTransactions is decremented.
- L55 _public prototype_ `void AbortTransactionAndThrow(ETransactionStatus Reason);` — Convenience function for calling AbortTransaction() followed by Throw().
- L62 _public prototype_ `void CommitTransaction();` — Ends a scoped or unscoped transaction, calling all registered on-commit handlers. If the current transaction is materialized, then the FTransaction is popped from the transaction stack, otherwise NumDeferredTransactions is decremented.
- L66 _public prototype_ `void MaybeThrow();` — Throws if the current (most-nested) FCallNest has a status that is not ETransactionStatus::Executing.
- L69 _public prototype_ `void RecordWrite(void* LogicalAddress, size_t Size);` — Record that a write is about to occur at the given LogicalAddress of Size bytes.
- L71 _public prototype_ `template <unsigned SIZE> void RecordWrite(void* LogicalAddress);`
- L73 _public prototype_ `template <unsigned SIZE> void RecordWriteSlow(void* LogicalAddress);`
- L75 _public prototype_ `void DidAllocate(void* LogicalAddress, size_t Size);`
- L76 _public prototype_ `void DidFree(void* LogicalAddress);`
- L78 _public prototype_ `inline void DeferUntilComplete(TTask<void()>&& Callback);`
- L79 _public prototype_ `inline void DeferUntilRetry(TTask<void()>&& Callback);`
- L83 _public function_ `inline uint64_t GetNumDeferredTransactions() const` — The number of deferred transactions that have yet to be materialized into a FTransaction.
- L91 _public function_ `inline bool MustMaterializeDeferredTransactions() const` — Returns true if the current (most-nested) transaction is deferred. For more information about deferred transactions, see StartTransaction() and AbortTransaction().
- L100 _public function_ `inline FTransaction* GetCurrentTransaction()` — Returns the current (most-nested) transaction, materializing the transaction stack if one or more transactions are deferred. For more information about deferred transactions, see StartTransaction() and AbortTransaction().
- L112 _public function_ `inline FTransaction* GetMaterializedTransaction()` — Returns the most-nested materialized transaction. For more information about deferred transactions, see StartTransaction() and AbortTransaction().
- L119 _public function_ `AUTORTFM_ENABLE inline bool IsContextThread() const` — Returns true if the caller's thread is the same as the thread associated with the transaction stack.
- L124 _public function_ `AUTORTFM_ENABLE inline EContextStatus GetStatus() const`
- L129 _public function_ `AUTORTFM_ENABLE inline bool IsTransactional() const`
- L134 _public function_ `inline void EnteringStaticLocalInitializer()`
- L153 _public function_ `inline void LeavingStaticLocalInitializer()`
- L173 _public function_ `inline FTaskPool& GetTaskPool()`
- L178 _public function_ `inline FTransactionPool& GetTransactionPool()`
- L184 _public prototype_ `static FStackRange GetThreadStackRange();` — Returns the stack address limits for the caller thread.
- L189 _private member_ `static FContext* Instance;`
- L191 _private function_ `FContext()`
- L195 _private prototype_ `FContext(const FContext&) = delete;`
- L196 _private prototype_ `~FContext();`
- L198 _private prototype_ `void MaterializeDeferredTransactions();`
- L200 _private prototype_ `void PushCallNest();`
- L201 _private prototype_ `void PopCallNest();`
- L203 _private prototype_ `FTransaction* PushTransaction(FStackRange);`
- L204 _private prototype_ `void PopTransaction();`
- L206 _private prototype_ `[[noreturn]] void Throw();`
- L208 _private prototype_ `void EndScopedTransaction();`
- L209 _private prototype_ `void CallCompletionTasks();`
- L212 _private prototype_ `void SetCallNestTransactionCascadingStatus(ETransactionStatus Status);` — Set the status of all the call nests with the given transaction status.
- L216 _private prototype_ `void SetCallNestTransactionNonCascadingStatus(ETransactionStatus Status);` — Set the status of all the call nests associated with the transaction with the given transaction status.
- L218 _private prototype_ `void Reset();`
- L222 _private member_ `uint64_t NumDeferredTransactions{0};` — We defer allocating FTransactions at the top of the transaction stack. This allows us to make starting a transaction in the open a load, some math, and a store.
- L223 _private member_ `FTransaction* CurrentMaterializedTransaction{nullptr};`
- L224 _private member_ `FCallNest* CurrentNest{nullptr};`
- L226 _private member_ `FStackRange Stack;`
- L227 _private member_ `EContextStatus Status{EContextStatus::Idle};`
- L228 _private member_ `FThreadID CurrentThreadId;`
- L229 _private member_ `uint32_t StackLocalInitializerDepth = 0;`
- L230 _private member_ `FTaskPool TaskPool;`
- L231 _private member_ `FTransactionPool TransactionPool;`
- L232 _private member_ `FCallNestPool CallNestPool;`

#### Free symbols / members of external scopes

- L18 _namespace_ `namespace AutoRTFM`

### `Source/Runtime/AutoRTFM/Private/ContextInlines.h` (Private)


#### Free symbols / members of external scopes

- L11 _namespace_ `namespace AutoRTFM`
- L14 _function_ `UE_AUTORTFM_FORCEINLINE FContext* FContext::Get()` (scope `AutoRTFM::FContext`)
- L19 _function_ `AUTORTFM_NO_ASAN UE_AUTORTFM_FORCEINLINE void FContext::RecordWrite(void* LogicalAddress, size_t Size)` (scope `AutoRTFM::FContext`)
- L25 _function_ `template <unsigned SIZE> AUTORTFM_NO_ASAN UE_AUTORTFM_FORCEINLINE void FContext::RecordWrite(void* LogicalAddress)` (scope `AutoRTFM::FContext`)
- L38 _function_ `template <unsigned SIZE> AUTORTFM_NO_ASAN UE_AUTORTFM_FORCENOINLINE void FContext::RecordWriteSlow(void* LogicalAddress)` (scope `AutoRTFM::FContext`)
- L45 _function_ `UE_AUTORTFM_FORCEINLINE void FContext::DidAllocate(void* LogicalAddress, size_t Size)` (scope `AutoRTFM::FContext`)
- L50 _function_ `UE_AUTORTFM_FORCEINLINE void FContext::DidFree(void* LogicalAddress)` (scope `AutoRTFM::FContext`)
- L61 _function_ `UE_AUTORTFM_FORCEINLINE void FContext::DeferUntilComplete(TTask<void()>&& Callback)` (scope `AutoRTFM::FContext`)
- L72 _function_ `UE_AUTORTFM_FORCEINLINE void FContext::DeferUntilRetry(TTask<void()>&& Callback)` (scope `AutoRTFM::FContext`)

### `Source/Runtime/AutoRTFM/Private/ExternAPI.h` (Private)


#### Free symbols / members of external scopes

- L9 _namespace_ `namespace AutoRTFM`
- L12 _externvar_ `extern autortfm_extern_api GExternAPI;` (scope `AutoRTFM`)

### `Source/Runtime/AutoRTFM/Private/FunctionMap.h` (Private)


#### Free symbols / members of external scopes

- L9 _namespace_ `namespace AutoRTFM`
- L13 _prototype_ `AUTORTFM_INTERNAL void FunctionMapDumpStats();` (scope `AutoRTFM`) — Dumps statistics about the function map to LOG_INFO.
- L16 _prototype_ `AUTORTFM_INTERNAL void FunctionMapAdd(autortfm_open_to_closed_table* Tables);` (scope `AutoRTFM`) — Adds all the open to closed function mappings from the linked list of tables to the function map.
- L20 _prototype_ `AUTORTFM_INTERNAL void* FunctionMapLookupExhaustive(void* OpenFn, const char* Where);` (scope `AutoRTFM`) — Looks up the closed function from the open function using the function map, following dynamic library thunk redirections.
- L23 _function_ `template <typename ReturnType, typename... ParameterTypes> AUTORTFM_INTERNAL auto FunctionMapLookupExhaustive(ReturnType (*Function)(ParameterTypes...), const char* Where) -> ReturnType (*)(ParameterTypes...)` (scope `AutoRTFM`)

### `Source/Runtime/AutoRTFM/Private/FunctionMapInlines.h` (Private)


#### Free symbols / members of external scopes

- L12 _namespace_ `namespace AutoRTFM`
- L15 _function_ `AUTORTFM_INTERNAL UE_AUTORTFM_FORCEINLINE void* FunctionMapLookupUsingMagicPrefix(void* OpenFn)` (scope `AutoRTFM`)
- L79 _function_ `AUTORTFM_INTERNAL inline void* FunctionMapLookup(void* OpenFn, const char* Where)` (scope `AutoRTFM`)
- L90 _function_ `template <typename TReturnType, typename... TParameterTypes> AUTORTFM_INTERNAL auto FunctionMapLookup(TReturnType (*OpenFn)(TParameterTypes...), const char* Where) -> TReturnType (*)(TParameterTypes...)` (scope `AutoRTFM`)

### `Source/Runtime/AutoRTFM/Private/HashMap.h` (Private)


#### struct `AutoRTFM::TKeyAndValue`  
`template <typename KeyType, typename ValueType> struct TKeyAndValue`  
_L19-23_
- desc: A simple structure holding a templated key and value pair.
- L21 _public member_ `KeyType Key;`
- L22 _public member_ `ValueType Value;`

#### class `AutoRTFM::THashMap`  
`class AUTORTFM_DISABLE THashMap`  
_L30-213_
- L32 _private typedef_ `using FInnerMap = std::unordered_map<KeyType, ValueType, Hash, Equal, StlAllocator<std::pair<const KeyType, ValueType>, Allocator>>;`
- L93 _public typedef_ `using Key = KeyType;`
- L94 _public typedef_ `using Value = ValueType;`
- L95 _public typedef_ `using Iterator = TIterator< false>;`
- L96 _public typedef_ `using ConstIterator = TIterator< true>;`
- L99 _public prototype_ `THashMap() = default;` — Constructor
- L101 _public prototype_ `~THashMap() = default;` — Destructor
- L103 _public prototype_ `THashMap(const THashMap& Other) = default;` — Copy constructor
- L105 _public function_ `THashMap(THashMap&& Other) : Map` — Move constructor
- L113 _public prototype_ `THashMap& operator=(const THashMap& Other) = default;` — Copy assignment operator
- L115 _public function_ `THashMap& operator=(THashMap&& Other)` — Move assignment operator
- L128 _public function_ `template <typename K, typename V> void Add(K&& Key, V&& Value)` — Set the value associated with a key, replacing any existing entry with the given key.
- L138 _public function_ `template <typename K> ValueType* Find(K&& Key)` — Looks up the value with the given key, returning a pointer to the value if found or nullptr if not found. Warning: The returned pointer will become invalid if the hash map is modified.
- L150 _public function_ `template <typename K> ValueType& FindOrAdd(K&& Key)` — Looks up the value with the given key, returning a reference to the existing value if found or a reference to a newly added, zero-initialized value if not found. Warning: The returned reference will become invalid if the hash map is modified.
- L157 _public function_ `void Remove(const KeyType& Key)` — Removes the entry with the given key. This is a no-op if the hash map does not contain an entry with the given key.
- L163 _public function_ `bool Contains(const KeyType& Key)` — Returns true if the hash map contains an entry with the given key.
- L169 _public function_ `void Empty()` — Removes all entries from the hash map, freeing all allocations.
- L176 _public function_ `void Reset()` — Removes all entries from the hash map. TODO(SOL-7652): Preserve any heap allocations made by the hash map.
- L182 _public function_ `size_t Num() const` — Returns the number of entries held by the hash map.
- L188 _public function_ `bool IsEmpty() const` — Returns true if the hash map holds no entries.
- L194 _public function_ `ConstIterator begin() const` — Iterator methods
- L198 _public function_ `ConstIterator end() const`
- L202 _public function_ `Iterator begin()`
- L206 _public function_ `Iterator end()`
- L212 _private member_ `FInnerMap Map;`

#### class `AutoRTFM::THashMap::TIterator`  
`template <bool bConst> class TIterator`  
_L36-90_
- L38 _private typedef_ `using FInnerIterator = std::conditional_t<bConst, typename FInnerMap::const_iterator, typename FInnerMap::iterator>;`
- L39 _private typedef_ `using FKeyAndValue = std::conditional_t<bConst, const TKeyAndValue<const KeyType, ValueType>, TKeyAndValue<const KeyType, ValueType>>;`
- L44 _public function_ `TIterator(FInnerIterator InnerIterator) : InnerIterator` — Constructor wrapping inner-iterator
- L46 _public prototype_ `TIterator(const TIterator&) = default;` — Copy constructor
- L48 _public prototype_ `TIterator(TIterator&&) = default;` — Move constructor
- L50 _public prototype_ `TIterator& operator=(const TIterator& Other) = default;` — Copy assignment operator
- L52 _public prototype_ `TIterator& operator=(TIterator&& Other) = default;` — Move assignment operator
- L54 _public function_ `FKeyAndValue& operator*() const`
- L72 _public function_ `TIterator& operator++()`
- L78 _public function_ `bool operator==(const TIterator& Other) const`
- L83 _public function_ `bool operator!=(const TIterator& Other) const`
- L89 _private member_ `FInnerIterator InnerIterator;`

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace AutoRTFM`
- L60 _typedef_ `using FPair = std::conditional_t<bConst, const std::pair<const KeyType, ValueType>, std::pair<const KeyType, ValueType>>;` (scope `AutoRTFM::THashMap::TIterator::operator *`) — Super hacky: Reinterpret a std::pair to a TKeyAndValue so that THashMap's iterator has the interface of a TMap instead of a std::unordered_map. TODO(SOL-7652): Remove this filth when THashMap is reimplemented.

### `Source/Runtime/AutoRTFM/Private/HitSet.h` (Private)


#### struct `AutoRTFM::FHitSetEntry`  
`struct FHitSetEntry`  
_L14-34_
- L16 _public member_ `static constexpr size_t AddressBits = 48;`
- L17 _public member_ `static constexpr size_t SizeBits = 12;`
- L18 _public member_ `static constexpr size_t FlagsBits = 4;`
- L21 _public member_ `uintptr_t Address : AddressBits;` — The address of the write.
- L23 _public member_ `uintptr_t Size : SizeBits;` — Size of the write.
- L25 _public member_ `uintptr_t Flags : FlagsBits;` — Flags applied to the write.
- L27 _public function_ `UE_AUTORTFM_FORCEINLINE uintptr_t Payload() const`

#### class `AutoRTFM::FHitSet`  
`class AUTORTFM_DISABLE FHitSet final`  
_L38-403_
- L47 _public member_ `static constexpr size_t MaxSize = 16;` — Maximum size in bytes for a hit-set write record. The cutoff here is arbitrarily any number less than UINT16_MAX, but its a weigh up what a good size is. Because the hitset doesn't detect when you are trying to write to a subregion of a previous hit (like memset something, then write to an individual element), we've got to balance the cost of recording meaningless hits, against the potential to hit again.
- L50 _public member_ `static constexpr uint64_t MaxCapacity = static_cast<uint64_t>(128 * 1024 * 1024) / sizeof(FHitSetEntry);` — TODO: Revisit a good max capacity for the hitset.
- L53 _private member_ `static constexpr uint8_t LinearProbeDepth = 32;`
- L54 _private member_ `static constexpr uint8_t LogInitialCapacity = 6;`
- L55 _private member_ `static constexpr uint64_t InitialCapacity = static_cast<uint64_t>(1) << LogInitialCapacity;`
- L60 _public function_ `~FHitSet()`
- L74 _public function_ `UE_AUTORTFM_FORCEINLINE EInsertResult FindOrTryInsertNoResize(FHitSetEntry Entry)` — Insert something in the HitSet, returning whether the key already exists, it was inserted, or not.
- L82 _public function_ `UE_AUTORTFM_FORCEINLINE bool FindOrTryInsert(FHitSetEntry Entry)` — Insert something in the HitSet, returning true if we found the key. If false is returned, we could have inserted or not - depending on whether the HitSet has reached its max capacity.
- L105 _public function_ `UE_AUTORTFM_FORCEINLINE bool Contains(FHitSetEntry Entry) const` — Returns true if the HitSet contains the given entry, without mutation.
- L153 _public function_ `UE_AUTORTFM_FORCEINLINE bool IsEmpty() const`
- L159 _public function_ `void Reset()` — Clear out the data stored in the set, but does not reduce the capacity.
- L175 _public function_ `uint64_t GetCapacity() const`
- L180 _public function_ `uint64_t GetCount() const`
- L234 _public function_ `FIterator begin() const`
- L238 _public function_ `FIterator end() const`
- L244 _private member_ `uintptr_t SmallPayload[InitialCapacity]{};`
- L245 _private member_ `uintptr_t* Payload = SmallPayload;`
- L246 _private member_ `uint64_t Count = 0;`
- L247 _private member_ `uint32_t SixtyFourMinusLogCapacity = 64 - LogInitialCapacity;`
- L249 _private function_ `UE_AUTORTFM_FORCEINLINE uint64_t Capacity() const`
- L255 _private function_ `UE_AUTORTFM_FORCEINLINE void IncreaseCapacity()`
- L265 _private function_ `bool Resize()`
- L331 _private function_ `UE_AUTORTFM_FORCEINLINE uintptr_t FibonacciHash(const uintptr_t Hashee) const`
- L337 _private function_ `UE_AUTORTFM_FORCEINLINE EInsertResult TryInsertAtIndex(const uintptr_t Raw, const uintptr_t I)`
- L358 _private function_ `UE_AUTORTFM_FORCEINLINE EInsertResult InsertNoResize(const uintptr_t Raw)` — Insert something in the HitSet, returning true if the insert succeeded (EG. the key was not already in the set).

#### enum `AutoRTFM::FHitSet::EInsertResult`  
`enum class EInsertResult : uint8_t`  
_L65-70_
- L67 _public enumerator_ `Exists`
- L68 _public enumerator_ `Inserted`
- L69 _public enumerator_ `NotInserted`

#### struct `AutoRTFM::FHitSet::FIterator`  
`struct FIterator`  
_L185-232_
- L187 _public function_ `FIterator(uintptr_t const* Ptr, size_t EntriesRemaining) : Ptr`
- L192 _public function_ `FHitSetEntry operator*() const`
- L199 _public function_ `FIterator& operator++()`
- L210 _public function_ `bool operator==(FIterator Other) const`
- L215 _public function_ `bool operator!=(FIterator Other) const`
- L221 _private function_ `void SkipEmpty()`
- L230 _private member_ `const uintptr_t* Ptr;`
- L231 _private member_ `size_t EntriesRemaining;`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace AutoRTFM`

### `Source/Runtime/AutoRTFM/Private/Interval.h` (Private)


#### struct `AutoRTFM::FInterval`  
`struct FInterval final`  
_L14-43_
- desc: A half-open address interval [Start, End).
- L17 _public prototype_ `FInterval() = default;` — Default constructor - leaves Start and End uninitialized.
- L20 _public function_ `constexpr FInterval(uintptr_t Start, uintptr_t End) : Start` — Constructs an interval with explicit start and end addresses.
- L23 _public function_ `FInterval(const void* const Address, const size_t Size) : Start(reinterpret_cast<uintptr_t>(Address)) , End(reinterpret_cast<uintptr_t>(Address) + Size)` — Constructs an interval from a base address and byte size.
- L30 _public function_ `size_t Size() const` — Returns the number of bytes in the interval.
- L36 _public function_ `bool operator<(const FInterval& Other) const` — Orders intervals by start address, for use in sorted containers.
- L41 _public member_ `uintptr_t Start;`
- L42 _public member_ `uintptr_t End;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace AutoRTFM`

### `Source/Runtime/AutoRTFM/Private/IntervalTree.h` (Private)


#### struct `AutoRTFM::TIntervalTree`  
`template <typename DataTypeIn, Allocator Allocator = FAllocator> requires std::equality_comparable<DataTypeIn> struct AUTORTFM_INTERNAL TIntervalTree final`  
_L25-1097_
- desc: TIntervalTree tracks a set of non-overlapping memory intervals, each associated with a data value of type DataTypeIn, using a red-black tree. Intervals are stored as [Start, End). On insert, the new interval takes ownership of its address range: - Overlapping or adjacent intervals with the same data are merged. - Overlapping intervals with different data are trimmed, split, or deleted.
- L28 _private typedef_ `using NodeIndex = uint32_t;`
- L29 _private typedef_ `using DataType = DataTypeIn;`
- L30 _private member_ `static constexpr NodeIndex InvalidNode = UINT32_MAX;`
- L33 _public prototype_ `TIntervalTree() = default;`
- L35 _public prototype_ `TIntervalTree(const TIntervalTree&) = delete;`
- L36 _public prototype_ `TIntervalTree& operator=(const TIntervalTree&) = delete;`
- L42 _public function_ `void Insert(const void* const Address, const size_t Size, DataType&& Data)` — Inserts the interval [Address, Address+Size) with the given data into the tree. The new interval takes ownership of its address range: - Overlapping or adjacent same-data intervals are merged into one. - Overlapping different-data intervals are trimmed, split, or deleted to make room.
- L51 _public function_ `void Insert(const void* const Address, const size_t Size, const DataType& Data)` — Inserts the interval [Address, Address+Size) with the given data into the tree. The new interval takes ownership of its address range: - Overlapping or adjacent same-data intervals are merged into one. - Overlapping different-data intervals are trimmed, split, or deleted to make room.
- L57 _public function_ `bool IsEmpty() const` — Returns true if no intervals are stored.
- L63 _public function_ `void Reset()` — Removes all stored intervals.
- L72 _public function_ `void Merge(const TIntervalTree& Other)` — Inserts all intervals from Other into this tree, applying the same ownership semantics as Insert: overlapping/adjacent same-data intervals merge, and overlapping different-data intervals are trimmed, split, or deleted.
- L139 _public function_ `FIterator begin() const` — Returns an iterator to the first interval in the tree
- L145 _public function_ `FIterator end() const` — Returns an end iterator for the tree
- L168 _public function_ `UE_AUTORTFM_FORCENOINLINE bool Overlaps(const void* const Address, const size_t Size) const` — Returns true if any stored interval overlaps [Address, Address+Size). Faster than Get() when you only need an existence check: single tree traversal, no iterator construction, no end-node lookup.
- L211 _public function_ `UE_AUTORTFM_FORCENOINLINE FOverlapRange Get(const void* const Address, const size_t Size) const` — Returns all stored intervals overlapping [Address, Address+Size), in ascending order of start address.
- L268 _private typedef_ `using ColorWord = uint64_t;`
- L471 _private member_ `NodeIndex Root = InvalidNode;`
- L472 _private member_ `FNodes Nodes;`
- L475 _private function_ `NodeIndex Next(NodeIndex Node) const` — Returns the index of the next sequential node after Node.
- L498 _private function_ `NodeIndex LeftMostDescendant(NodeIndex Node) const` — Returns the left-most leaf descendant of Node.
- L508 _private function_ `NodeIndex Predecessor(uintptr_t SearchStart) const` — Returns the rightmost node whose Start < SearchStart, or InvalidNode.
- L528 _private function_ `NodeIndex LowerBound(uintptr_t SearchStart) const` — Returns the leftmost node whose Start >= SearchStart, or InvalidNode.
- L548 _private function_ `void RotateLeft(NodeIndex X)` — Left-rotates around X:  X's right child Y takes X's place.
- L578 _private function_ `void RotateRight(NodeIndex X)` — Right-rotates around X:  X's left child Y takes X's place.
- L609 _private function_ `UE_AUTORTFM_FORCENOINLINE void Remove(NodeIndex Z)` — Removes node Z from the red-black tree. The node's slot in the SoA array is left as a dead entry (not reclaimed).
- L763 _private function_ `UE_AUTORTFM_FORCENOINLINE void Insert(FInterval NewInterval, DataType NewData)` — Inserts NewInterval with NewData into the tree, applying the ownership semantics: Phase A — extend MergedStart left by consuming adjacent/overlapping same-data predecessors; trim or split a different-data predecessor that overlaps. Phase B — scan forward from MergedStart: consume same-data nodes (extending MergedEnd), delete fully-covered different-data nodes, trim a right-partial overlap. Phase C — SimpleInsert the effective [MergedStart, MergedEnd) interval. Phase D — re-insert any deferred right-remainder created by a split or right trim.
- L897 _private function_ `UE_AUTORTFM_FORCEINLINE NodeIndex AddNode(FInterval NewInterval, DataType&& Data, NodeIndex Parent = InvalidNode)`
- L909 _private function_ `UE_AUTORTFM_FORCENOINLINE void SimpleInsert(FInterval NewInterval, DataType Data)` — Fast-path insert: assumes [NewInterval] has no overlapping or adjacent intervals already in the tree.  Called by Insert() after it has cleared the way.

#### struct `AutoRTFM::TIntervalTree::FIntervalAndData`  
`struct FIntervalAndData`  
_L106-110_
- desc: A single entry yielded by the iterator: the stored interval and a reference to its data.
- L108 _public member_ `FInterval Interval;`
- L109 _public member_ `const DataType& Data;`

#### struct `AutoRTFM::TIntervalTree::FIterator`  
`struct FIterator`  
_L113-136_
- desc: A forward iterator that yields intervals in ascending order of start address.
- L115 _public prototype_ `FIterator(const FIterator&) = default;`
- L116 _public prototype_ `FIterator& operator=(const FIterator&) = default;`
- L118 _public function_ `FIntervalAndData operator*() const`
- L123 _public function_ `FIterator& operator++()`
- L129 _public prototype_ `bool operator==(const FIterator& Other) const = default;`
- L133 _private function_ `FIterator(TIntervalTree const* Tree, NodeIndex Node) : Tree`
- L134 _private member_ `TIntervalTree const* Tree = nullptr;`
- L135 _private member_ `NodeIndex Node = InvalidNode;`

#### struct `AutoRTFM::TIntervalTree::FOverlapRange`  
`struct FOverlapRange`  
_L151-163_
- desc: A lightweight range representing all stored intervals that overlap a query.
- L153 _public member_ `FIterator Begin;`
- L154 _public member_ `FIterator End;`
- L155 _public function_ `FIterator begin() const`
- L159 _public function_ `FIterator end() const`

#### enum `AutoRTFM::TIntervalTree::EColor`  
`enum EColor : bool`  
_L262-266_
- L264 _public enumerator_ `Red = false`
- L265 _public enumerator_ `Black = true`

#### struct `AutoRTFM::TIntervalTree::FNode`  
`struct FNode final`  
_L270-278_
- L272 _public member_ `FInterval Interval;`
- L273 _public member_ `NodeIndex Left = InvalidNode;`
- L274 _public member_ `NodeIndex Right = InvalidNode;`
- L275 _public member_ `NodeIndex Parent = InvalidNode;`
- L276 _public member_ `EColor Color;`
- L277 _public member_ `DataType Data;`

#### struct `AutoRTFM::TIntervalTree::FNodePtrs`  
`struct FNodePtrs final`  
_L280-288_
- L282 _public member_ `FInterval* Interval = nullptr;`
- L283 _public member_ `NodeIndex* Left = nullptr;`
- L284 _public member_ `NodeIndex* Right = nullptr;`
- L285 _public member_ `NodeIndex* Parent = nullptr;`
- L286 _public member_ `ColorWord* Color = nullptr;`
- L287 _public member_ `DataType* Data = nullptr;`

#### struct `AutoRTFM::TIntervalTree::FNodes`  
`struct FNodes final`  
_L291-469_
- desc: A list of FNodes, stored as a structure-of-arrays.
- L293 _public member_ `static constexpr size_t NumColorWordBits = sizeof(ColorWord) * 8;`
- L294 _public member_ `static constexpr NodeIndex InitialCapacity = 32;`
- L296 _public member_ `FNodePtrs Ptrs;`
- L297 _public member_ `NodeIndex Count = 0;`
- L298 _public member_ `NodeIndex Capacity = 0;`
- L300 _public prototype_ `FNodes() = default;`
- L302 _public function_ `~FNodes()`
- L308 _public function_ `void Reset()` — Clears the node list to an empty state.
- L326 _public function_ `NodeIndex Push(FNode Node)` — Pushes a new node to the end of the list. Returns the node index.
- L343 _public function_ `FInterval& Interval(NodeIndex Index)`
- L347 _public function_ `const FInterval& Interval(NodeIndex Index) const`
- L351 _public function_ `NodeIndex& Left(NodeIndex Index)`
- L355 _public function_ `const NodeIndex& Left(NodeIndex Index) const`
- L359 _public function_ `NodeIndex& Right(NodeIndex Index)`
- L363 _public function_ `const NodeIndex& Right(NodeIndex Index) const`
- L367 _public function_ `NodeIndex& Parent(NodeIndex Index)`
- L371 _public function_ `const NodeIndex& Parent(NodeIndex Index) const`
- L375 _public function_ `DataType& Data(NodeIndex Index)`
- L379 _public function_ `const DataType& Data(NodeIndex Index) const`
- L384 _public function_ `void SetColor(NodeIndex Index, EColor Color)`
- L398 _public function_ `EColor Color(NodeIndex Index) const`
- L406 _private member_ `std::byte* Memory = nullptr;`
- L407 _private member_ `size_t MemorySizeInBytes = 0;`
- L409 _private prototype_ `FNodes(const FNodes&) = delete;`
- L410 _private prototype_ `FNodes& operator=(const FNodes&) = delete;`
- L412 _private function_ `void Resize(NodeIndex NewCapacity)`
- L458 _private function_ `template <typename T> static size_t SubAllocate(size_t& Offset, size_t Count)`
- L465 _private function_ `static constexpr size_t NumColorWords(size_t Count)`

#### Free symbols / members of external scopes

- L15 _namespace_ `namespace AutoRTFM`
- L774 _function_ `` (scope `AutoRTFM::TIntervalTree::Insert`)
- L955 _function_ `` (scope `AutoRTFM::TIntervalTree::SimpleInsert`)

### `Source/Runtime/AutoRTFM/Private/IntrusivePool.h` (Private)


#### class `AutoRTFM::TIntrusivePool`  
`template <typename ItemType, size_t InlineCapacity> class AUTORTFM_INTERNAL TIntrusivePool final`  
_L17-96_
- L20 _public typedef_ `using FItem = ItemType;`
- L22 _public prototype_ `TIntrusivePool() = default;`
- L24 _public function_ `~TIntrusivePool()`
- L38 _public function_ `template <typename... ArgumentTypes> FItem* Take(ArgumentTypes&&... Arguments)` — Acquires a new Item from the pool. If the item was previously returned to the pool, we'll call `Resurrect` on it with `Arguments`. Otherwise create a new item with `Arguments`.
- L66 _public function_ `void Return(FItem* const Item)` — Calls `Suppress` on `Item` and returns it to the pool to be reused.
- L80 _private member_ `static constexpr size_t EntrySize = sizeof(FItem);`
- L81 _private member_ `static constexpr size_t EntryAlignment = alignof(FItem);`
- L84 _private member_ `TBlockAllocator<InlineCapacity * EntrySize, EntryAlignment> Allocator;` — The underlying allocator for the pool.
- L86 _private member_ `FItem* FreeList = nullptr;` — Free list.
- L88 _private member_ `size_t NumAllocated = 0;` — Number of entries allocated.
- L90 _private member_ `size_t NumInUse = 0;` — Number of entries currently in use.
- L92 _private prototype_ `TIntrusivePool(TIntrusivePool&&) = delete;`
- L93 _private prototype_ `TIntrusivePool(const TIntrusivePool&) = delete;`
- L94 _private prototype_ `TIntrusivePool& operator=(const TIntrusivePool&) = delete;`
- L95 _private prototype_ `TIntrusivePool& operator=(TIntrusivePool&&) = delete;`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace AutoRTFM`

### `Source/Runtime/AutoRTFM/Private/LongJump.h` (Private)


#### class `AutoRTFM::FLongJump`  
`class AUTORTFM_DISABLE FLongJump`  
_L24-48_
- desc: setjmp/longjmp that doesn't do any unwinding (no C++ destructor calls, no messing with OS signal states - just saving/restoring CPU state). Although it's the setjmp/longjmp everyone knows and loves, it's exposed as a try/catch/throw API to make it less error-prone.
- L27 _public function_ `FLongJump()`
- L33 _public prototype_ `template <typename TTryFunctor, typename TCatchFunctor> void TryCatch(const TTryFunctor& TryFunctor, const TCatchFunctor& CatchFunctor);`
- L35 _public prototype_ `[[noreturn]] void Throw();`
- L39 _private prototype_ `static bool SaveContext(void* Buffer);`
- L40 _private prototype_ `[[noreturn]] static void RestoreContext(void* Context);`
- L41 _private member_ `static constexpr size_t ContextSize = 256;`
- L42 _private member_ `static constexpr size_t ContextAlignment = 16;`
- L43 _private member_ `alignas(ContextAlignment) std::byte Context[ContextSize];`
- L47 _private member_ `bool bIsSet;`
- L51 _function_ `template <typename TTryFunctor, typename TCatchFunctor> void FLongJump::TryCatch(const TTryFunctor& TryFunctor, const TCatchFunctor& CatchFunctor)`
- L74 _function_ `inline void FLongJump::Throw()`

#### Free symbols / members of external scopes

- L13 _macro_ `#define AUTORTFM_USE_SAVE_RESTORE_CONTEXT 1`
- L15 _macro_ `#define AUTORTFM_USE_SAVE_RESTORE_CONTEXT 0`
- L18 _namespace_ `namespace AutoRTFM`

### `Source/Runtime/AutoRTFM/Private/Memcpy.h` (Private)


#### Free symbols / members of external scopes

- L11 _namespace_ `namespace AutoRTFM`
- L16 _prototype_ `AUTORTFM_INTERNAL void* MemcpyToNew(void* Dst, const void* Src, size_t Size, FContext* Context);` (scope `AutoRTFM`)
- L17 _prototype_ `AUTORTFM_INTERNAL void* Memcpy(void* Dst, const void* Src, size_t Size, FContext* Context);` (scope `AutoRTFM`)
- L18 _prototype_ `AUTORTFM_INTERNAL void* Memmove(void* Dst, const void* Src, size_t Size, FContext* Context);` (scope `AutoRTFM`)
- L19 _prototype_ `AUTORTFM_INTERNAL void* Memset(void* Dst, int Value, size_t Size, FContext* Context);` (scope `AutoRTFM`)

### `Source/Runtime/AutoRTFM/Private/MemoryStats.h` (Private)


#### struct `AutoRTFM::FMemoryStats`  
`struct FMemoryStats`  
_L20-52_
- L25 _public member_ `static constexpr size_t UnderflowMask = ((~static_cast<size_t>(0)) >> 1) + 1;` — size_t constant with only the most-significant-bit set. Used to quickly check for underflow/overflow, as we don't expect over nine quintillion bytes of heap memory to be allocated.
- L28 _public function_ `static inline void UpdateBytesAllocated(ptrdiff_t Delta)` — Adjusts the total number of bytes allocated by Delta.
- L41 _public function_ `static inline size_t GetTotalBytesAllocated()` — Returns the total number of heap bytes allocated by AutoRTFM.
- L48 _private prototype_ `static void FatalErrorBytesAllocatedUnderflow();` — Not inline to break circular header dependencies.
- L51 _private member_ `static std::atomic<size_t> BytesAllocated;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace AutoRTFM`
- L15 _macro_ `#define AUTORTFM_CHECK_FOR_ALLOCATION_UNDERFLOW 0`

### `Source/Runtime/AutoRTFM/Private/MemoryTracker.h` (Private)


#### struct `AutoRTFM::FMemoryTracker`  
`struct AUTORTFM_INTERNAL FMemoryTracker final`  
_L25-661_
- desc: FMemoryTracker tracks a set of non-overlapping memory intervals using a red-black tree. Each interval is stored as [Start, End) and intervals that touch at their endpoints are merged into a single interval automatically on insert. Assumes that queries never partially overlap a stored interval — a query either falls entirely within an interval or entirely outside it. This assumption enables a simplified BST traversal in Contains() that avoids examining both subtrees.
- L28 _private typedef_ `using NodeIndex = uint32_t;`
- L29 _private member_ `static constexpr NodeIndex InvalidNode = UINT32_MAX;`
- L32 _public prototype_ `FMemoryTracker() = default;`
- L34 _public prototype_ `FMemoryTracker(const FMemoryTracker&) = delete;`
- L35 _public prototype_ `FMemoryTracker& operator=(const FMemoryTracker&) = delete;`
- L40 _public function_ `bool Insert(const void* const Address, const size_t Size)` — Inserts the interval [Address, Address+Size) into the tracker. If the new interval is adjacent to an existing interval, the two are merged. Returns false if the interval overlaps (but is not adjacent to) an existing interval.
- L46 _public function_ `bool Contains(const void* const Address, const size_t Size) const` — Returns true if the interval [Address, Address+Size) overlaps any stored interval.
- L52 _public function_ `bool IsEmpty() const` — Returns true if no intervals are stored.
- L58 _public function_ `void Reset()` — Removes all stored intervals.
- L65 _public function_ `void Merge(const FMemoryTracker& Other)` — Inserts all intervals from Other into this tracker.
- L126 _public function_ `FIterator begin() const` — Returns an iterator to the first interval in the tree
- L132 _public function_ `FIterator end() const` — Returns an end iterator for the tree
- L146 _private typedef_ `using ColorWord = uint64_t;`
- L324 _private member_ `NodeIndex Root = InvalidNode;`
- L325 _private member_ `FNodes Nodes;`
- L327 _private member_ `static constexpr bool bExtraDebugging = false;`
- L330 _private function_ `NodeIndex Next(NodeIndex Node) const` — Returns the index of the next sequential node after Node.
- L353 _private function_ `NodeIndex LeftMostDescendant(NodeIndex Node) const` — Returns the left-most leaf descendant of Node.
- L362 _private function_ `UE_AUTORTFM_FORCEINLINE NodeIndex AddNode(FInterval Interval, NodeIndex Parent = InvalidNode)`
- L371 _private function_ `UE_AUTORTFM_FORCENOINLINE bool Insert(FInterval NewInterval)`
- L583 _private function_ `UE_AUTORTFM_FORCENOINLINE bool Query(const void* const Address, const size_t Size) const`
- L613 _private function_ `UE_AUTORTFM_FORCEINLINE void AssertStructureIsOk() const`
- L624 _private function_ `UE_AUTORTFM_FORCENOINLINE void AssertNodeIsOk(NodeIndex Index) const`

#### struct `AutoRTFM::FMemoryTracker::FIterator`  
`struct FIterator`  
_L99-123_
- desc: A forward iterator of the FMemoryTracker
- L101 _public prototype_ `FIterator(const FIterator&) = default;`
- L102 _public prototype_ `FIterator& operator=(const FIterator&) = default;`
- L104 _public function_ `FInterval operator*() const`
- L109 _public function_ `FIterator& operator++()`
- L115 _public prototype_ `bool operator==(const FIterator& Other) const = default;`
- L116 _public prototype_ `bool operator!=(const FIterator& Other) const = default;`
- L120 _private function_ `FIterator(FMemoryTracker const* Tree, NodeIndex Node) : Tree`
- L121 _private member_ `FMemoryTracker const* Tree = nullptr;`
- L122 _private member_ `NodeIndex Node = InvalidNode;`

#### enum `AutoRTFM::FMemoryTracker::EColor`  
`enum EColor : bool`  
_L140-144_
- L142 _public enumerator_ `Red = false`
- L143 _public enumerator_ `Black = true`

#### struct `AutoRTFM::FMemoryTracker::FNode`  
`struct FNode final`  
_L148-155_
- L150 _public member_ `FInterval Interval;`
- L151 _public member_ `NodeIndex Left = InvalidNode;`
- L152 _public member_ `NodeIndex Right = InvalidNode;`
- L153 _public member_ `NodeIndex Parent = InvalidNode;`
- L154 _public member_ `EColor Color;`

#### struct `AutoRTFM::FMemoryTracker::FNodePtrs`  
`struct FNodePtrs final`  
_L157-164_
- L159 _public member_ `FInterval* Interval = nullptr;`
- L160 _public member_ `NodeIndex* Left = nullptr;`
- L161 _public member_ `NodeIndex* Right = nullptr;`
- L162 _public member_ `NodeIndex* Parent = nullptr;`
- L163 _public member_ `ColorWord* Color = nullptr;`

#### struct `AutoRTFM::FMemoryTracker::FNodes`  
`struct FNodes final`  
_L167-322_
- desc: A list of FNodes, stored as a structure-of-arrays.
- L169 _public member_ `static constexpr size_t NumColorWordBits = sizeof(ColorWord) * 8;`
- L170 _public member_ `static constexpr NodeIndex InitialCapacity = 32;`
- L172 _public member_ `FNodePtrs Ptrs;`
- L173 _public member_ `NodeIndex Count = 0;`
- L174 _public member_ `NodeIndex Capacity = 0;`
- L176 _public prototype_ `FNodes() = default;`
- L178 _public function_ `~FNodes()`
- L184 _public function_ `void Reset()` — Clears the node list to an empty state.
- L197 _public function_ `NodeIndex Push(FNode Node)` — Pushes a new node to the end of the list. Returns the node index.
- L213 _public function_ `FInterval& Interval(NodeIndex Index)`
- L217 _public function_ `const FInterval& Interval(NodeIndex Index) const`
- L221 _public function_ `NodeIndex& Left(NodeIndex Index)`
- L225 _public function_ `const NodeIndex& Left(NodeIndex Index) const`
- L229 _public function_ `NodeIndex& Right(NodeIndex Index)`
- L233 _public function_ `const NodeIndex& Right(NodeIndex Index) const`
- L237 _public function_ `NodeIndex& Parent(NodeIndex Index)`
- L241 _public function_ `const NodeIndex& Parent(NodeIndex Index) const`
- L246 _public function_ `void SetColor(NodeIndex Index, EColor Color)`
- L260 _public function_ `EColor Color(size_t Index) const`
- L268 _private member_ `std::byte* Memory = nullptr;`
- L269 _private member_ `size_t MemorySizeInBytes = 0;`
- L271 _private prototype_ `FNodes(const FNodes&) = delete;`
- L272 _private prototype_ `FNodes& operator=(const FNodes&) = delete;`
- L274 _private function_ `void Resize(NodeIndex NewCapacity)`
- L311 _private function_ `template <typename T> static size_t SubAllocate(size_t& Offset, size_t Count)`
- L318 _private function_ `static constexpr size_t NumColorWords(size_t Count)`

#### Free symbols / members of external scopes

- L15 _namespace_ `namespace AutoRTFM`
- L436 _function_ `` (scope `AutoRTFM::FMemoryTracker::Insert`)

### `Source/Runtime/AutoRTFM/Private/MetricsPriv.h` (Private)


#### Free symbols / members of external scopes

- L11 _namespace_ `namespace AutoRTFM`
- L15 _prototype_ `bool ConvertMetricsToCSV(const FAutoRTFMMetrics& Metrics, char* Buffer, int BufferLength);` (scope `AutoRTFM`) — Converts an AutoRTFM metrics struct into CSV-formatted text.
- L18 _function_ `inline void IncrementNumTransactionsStartedMetric(size_t Amount = 1)` (scope `AutoRTFM`) — Increments counter for number of transactions started.
- L20 _externvar_ `extern AutoRTFM::FAutoRTFMMetrics GAutoRTFMMetrics;` (scope `AutoRTFM::IncrementNumTransactionsStartedMetric`)
- L25 _function_ `inline void IncrementNumTransactionsCommittedMetric(size_t Amount = 1)` (scope `AutoRTFM`) — Increments counter for number of transactions committed.
- L27 _externvar_ `extern AutoRTFM::FAutoRTFMMetrics GAutoRTFMMetrics;` (scope `AutoRTFM::IncrementNumTransactionsCommittedMetric`)
- L32 _function_ `inline void IncrementNumTransactionsAbortedMetric(size_t Amount = 1)` (scope `AutoRTFM`) — Increments counter for number of transactions aborted.
- L34 _externvar_ `extern AutoRTFM::FAutoRTFMMetrics GAutoRTFMMetrics;` (scope `AutoRTFM::IncrementNumTransactionsAbortedMetric`)
- L39 _function_ `inline void IncrementNumRequestedAbortsMetric(size_t Amount = 1)` (scope `AutoRTFM`) — Increments counter for number of calls to AbortTransaction.
- L41 _externvar_ `extern AutoRTFM::FAutoRTFMMetrics GAutoRTFMMetrics;` (scope `AutoRTFM::IncrementNumRequestedAbortsMetric`)
- L46 _function_ `inline void IncrementNumRequestedCascadingAbortsMetric(size_t Amount = 1)` (scope `AutoRTFM`) — Increments counter for number of CascadingAbortTransaction calls.
- L48 _externvar_ `extern AutoRTFM::FAutoRTFMMetrics GAutoRTFMMetrics;` (scope `AutoRTFM::IncrementNumRequestedCascadingAbortsMetric`)
- L53 _function_ `inline void IncrementNumRequestedCascadingRetriesMetric(size_t Amount = 1)` (scope `AutoRTFM`) — Increments counter for number of CascadingRetryTransaction calls.
- L55 _externvar_ `extern AutoRTFM::FAutoRTFMMetrics GAutoRTFMMetrics;` (scope `AutoRTFM::IncrementNumRequestedCascadingRetriesMetric`)
- L60 _function_ `inline void IncrementNumTransactionalViolationsMetric(size_t Amount = 1)` (scope `AutoRTFM`) — Increments counter for number of transactional aborts caused by violating transactionality (unsupported calls or API misuse).
- L62 _externvar_ `extern AutoRTFM::FAutoRTFMMetrics GAutoRTFMMetrics;` (scope `AutoRTFM::IncrementNumTransactionalViolationsMetric`)
- L67 _prototype_ `void UpdatePeakMemoryUsageMetrics(size_t MemoryUsed = FMemoryStats::GetTotalBytesAllocated());` (scope `AutoRTFM`) — Updates the peak memory usage metrics with the passed-in value, if it's higher than the current peak value.
- L70 _prototype_ `void UpdateMemoryUsageHistogram();` (scope `AutoRTFM`) — Updates the memory histogram metric, and resets the current-transaction peak memory usage metric.

### `Source/Runtime/AutoRTFM/Private/Pool.h` (Private)


#### class `AutoRTFM::TPool`  
`template <typename ItemType, size_t InlineCapacity> class AUTORTFM_INTERNAL TPool`  
_L26-122_
- desc: An allocator of objects of a single type, backed by a TBlockAllocator with and internal linked list for free items. Items can be constructed and returned from the pool with Take(). The memory of items returned to the pool with Return() will be reused for the next calls to Take() in a LIFO order. Template parameters: ItemType - the pooled item type. InlineCapacity - the number of items that can be held before spilling to the heap.
- L29 _public typedef_ `using FItem = ItemType;`
- L32 _public prototype_ `TPool() = default;` — Constructor
- L36 _public function_ `template <typename... ArgumentTypes> FItem* Take(ArgumentTypes&&... Arguments)` — Acquires a new Item from the pool, forward-constructing the item with Arguments.
- L60 _public function_ `void Return(FItem* Item)` — Destructs the item and returns it back to the pool so the memory can be reused.
- L76 _public function_ `void Reset(bool bIgnoreNonReturned = false)` — Frees the memory allocated for the item list. No items can be in use when calling.
- L86 _public function_ `size_t GetNumAllocated() const` — Returns the number of items allocated.
- L92 _public function_ `size_t GetNumInUse() const` — Returns the number of items currently in use (not returned).
- L106 _private member_ `static constexpr size_t EntrySize = std::max<size_t>(sizeof(FItem), sizeof(TFreeEntry));` — The memory of each entry is used for both an Item (when in use) and a TFreeEntry (when in the pool), so the size and alignment needs to be the max of both.
- L107 _private member_ `static constexpr size_t EntryAlignment = std::max<size_t>(alignof(FItem), alignof(TFreeEntry));`
- L109 _private prototype_ `TPool(TPool&&) = delete;`
- L110 _private prototype_ `TPool(const TPool&) = delete;`
- L111 _private prototype_ `TPool& operator=(const TPool&) = delete;`
- L112 _private prototype_ `TPool& operator=(TPool&&) = delete;`
- L115 _private member_ `TBlockAllocator<InlineCapacity * EntrySize, EntryAlignment> Allocator;` — The underlying allocator for the pool.
- L117 _private member_ `TFreeEntry* FreeList = nullptr;` — Free list.
- L119 _private member_ `size_t NumAllocated = 0;` — Number of entries allocated.
- L121 _private member_ `size_t NumInUse = 0;` — Number of entries currently in use.

#### struct `AutoRTFM::TPool::TFreeEntry`  
`struct TFreeEntry`  
_L98-101_
- L100 _public member_ `TFreeEntry* Next;`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace AutoRTFM`

### `Source/Runtime/AutoRTFM/Private/Sanitizer.h` (Private)


#### Free symbols / members of external scopes

- L11 _namespace_ `namespace AutoRTFM`
- L11 _namespace_ `namespace Sanitizer` (scope `AutoRTFM`)
- L14 _macro_ `#define AUTORTFM_SANITIZER_INTERNAL [[clang::autortfm(autortfm_mode_internal)]]`
- L16 _prototype_ `AUTORTFM_SANITIZER_INTERNAL void Initialize();` (scope `AutoRTFM::Sanitizer`)
- L17 _prototype_ `AUTORTFM_SANITIZER_INTERNAL void Shutdown();` (scope `AutoRTFM::Sanitizer`)
- L19 _prototype_ `AUTORTFM_SANITIZER_INTERNAL size_t NumberOfIssuesFound();` (scope `AutoRTFM::Sanitizer`)
- L21 _prototype_ `AUTORTFM_SANITIZER_INTERNAL void StartTransaction(TransactionID ID, FStackRange StackRange);` (scope `AutoRTFM::Sanitizer`)
- L22 _prototype_ `AUTORTFM_SANITIZER_INTERNAL void CommitTransaction(TransactionID ID);` (scope `AutoRTFM::Sanitizer`)
- L23 _prototype_ `AUTORTFM_SANITIZER_INTERNAL void AbortTransaction(TransactionID ID);` (scope `AutoRTFM::Sanitizer`)
- L25 _prototype_ `AUTORTFM_SANITIZER_INTERNAL void ClosedWrite(TransactionID ID, void* Ptr, size_t Size, void* ProgramCounter);` (scope `AutoRTFM::Sanitizer`)

### `Source/Runtime/AutoRTFM/Private/ScopedGuard.h` (Private)


#### class `AutoRTFM::TScopedGuard`  
`template <typename T> class AUTORTFM_INTERNAL TScopedGuard`  
_L13-29_
- L16 _public function_ `TScopedGuard(T& Ref, const T& Value) : OldValue(Ref), Ref(Ref)`
- L21 _public function_ `~TScopedGuard()`
- L27 _private member_ `T OldValue;`
- L28 _private member_ `T& Ref;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace AutoRTFM`

### `Source/Runtime/AutoRTFM/Private/Stack.h` (Private)


#### class `AutoRTFM::TStack`  
`class AUTORTFM_INTERNAL TStack`  
_L35-370_
- L38 _public typedef_ `using ElementType = T;`
- L41 _public prototype_ `TStack() = default;` — Constructor.
- L44 _public function_ `TStack(std::initializer_list<T> List)` — Constructor from initializer list.
- L54 _public function_ `TStack(const TStack& Other)` — Copy constructor.
- L60 _public function_ `TStack(TStack&& Other)` — Move constructor.
- L67 _public function_ `~TStack()` — Destructor. Frees all the memory allocated by the allocator.
- L73 _public function_ `TStack& operator=(const TStack& Other)` — Copy assignment operator
- L84 _public function_ `TStack& operator=(TStack&& Other)` — Move assignment operator
- L95 _public function_ `void Clear()` — Clears all the items from the stack, preserving the capacity.
- L106 _public function_ `void Reset()` — Clears all the items from the stack, freeing all heap allocations and resetting the capacity to InlineCapacity
- L118 _public function_ `inline void Push(const T& Item)` — Pushes a new item on to the stack.
- L131 _public function_ `inline void PushAll(TStack&& Other)` — Moves all the items from Other to this stack. Other will hold no elements after calling.
- L160 _public function_ `inline void Pop()` — Removes the last item on the stack.
- L168 _public function_ `inline void Reserve(size_t NewCapacity)` — Reserves memory for at NewCapacity items.
- L207 _public function_ `inline size_t Num() const`
- L212 _public function_ `inline bool IsEmpty() const`
- L217 _public function_ `T& operator[](size_t Index)`
- L223 _public function_ `const T& operator[](size_t Index) const`
- L229 _public function_ `T& Front()`
- L235 _public function_ `const T& Front() const`
- L241 _public function_ `T& Back()`
- L247 _public function_ `const T& Back() const`
- L253 _public function_ `T* begin()`
- L257 _public function_ `const T* begin() const`
- L261 _public function_ `T* end()`
- L265 _public function_ `const T* end() const`
- L272 _public function_ `template <typename OtherT, size_t OtherInlineCapacity, typename OtherAllocator> bool operator==(const TStack<OtherT, OtherInlineCapacity, OtherAllocator>& Other) const` — Equality operator
- L291 _private function_ `void Free()` — Frees the heap allocation for this TStack. Note: Does not null Data or reset Capacity.
- L300 _private function_ `void CopyFrom(const TStack& Other)` — Copies the data from Other to this stack. This stack must be empty before calling.
- L320 _private function_ `void MoveFrom(TStack&& Other)` — Moves the data from Other to this stack. This stack must be empty before calling.
- L350 _private function_ `void SetToInitialState()` — Sets Data, Capacity and Count to the initially default-constructed values. Warning: This does not free or destruct any elements held by this stack.
- L357 _private function_ `T* InlineData()`
- L361 _private function_ `const T* InlineData() const`
- L366 _private member_ `alignas(T) std::byte InlineDataBuffer[sizeof(T) * InlineCapacity];`
- L367 _private member_ `T* Data = reinterpret_cast<T*>(InlineDataBuffer);`
- L368 _private member_ `size_t Capacity = InlineCapacity;`
- L369 _private member_ `size_t Count = 0;`

#### Free symbols / members of external scopes

- L15 _namespace_ `namespace AutoRTFM`

### `Source/Runtime/AutoRTFM/Private/StackRange.h` (Private)


#### struct `AutoRTFM::FStackRange`  
`struct FStackRange`  
_L12-33_
- desc: FStackRange represents a stack memory range. It is assumed the stack grows downwards.
- L14 _public member_ `void* Low = nullptr;` — One byte past the end of the stack range.
- L15 _public member_ `void* High = nullptr;` — The first byte of the stack range.
- L18 _public function_ `bool Contains(const void* Address) const` — Returns true if the stack range contains Address
- L24 _public function_ `bool operator==(const FStackRange& Other) const` — Equality operator
- L29 _public function_ `bool operator!=(const FStackRange& Other) const` — In-equality operator

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace AutoRTFM`

### `Source/Runtime/AutoRTFM/Private/StlAllocator.h` (Private)


#### class `AutoRTFM::StlAllocator`  
`template <typename T, Allocator Allocator = FAllocator> class [[clang::autortfm(autortfm_mode_internal)]] StlAllocator`  
_L19-38_
- desc: A stl-compatible allocator which wraps an AutoRTFM allocator. TODO(SOL-7652): Remove this once HashMap has been replaced with a bespoke hashmap implementation.
- L22 _public typedef_ `using value_type = T;`
- L24 _public prototype_ `StlAllocator() = default;`
- L27 _public function_ `template <typename U, typename A> StlAllocator(const StlAllocator<U, A>&)`
- L29 _public function_ `T* allocate(size_t Count)`
- L34 _public function_ `void deallocate(T* Pointer, size_t Count)`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace AutoRTFM`
- L41 _function_ `template <typename T, typename U, typename A> bool operator==(const StlAllocator<T, A>&, const StlAllocator<U, A>&)` (scope `AutoRTFM`)
- L47 _function_ `template <typename T, typename U, typename A> bool operator!=(const StlAllocator<T, A>&, const StlAllocator<U, A>&)` (scope `AutoRTFM`)

### `Source/Runtime/AutoRTFM/Private/TaskArray.h` (Private)


#### class `AutoRTFM::TTaskArray`  
`template <typename TaskType, typename KeyType = const void*> class AUTORTFM_DISABLE TTaskArray`  
_L27-280_
- desc: A sequential linked-list of tasks, with the ability to tag some tasks with a key. Those tagged with a key can be removed from the list in LIFO order (stack-like). Tasks can be traversed bi-directionally. Template parameters: Task            - the task data type Key             - the data type used as a key for push / pop. InlineTaskCount - the number of tasks that can be allocated before a performing heap allocations.
- L87 _public typedef_ `using FEntryPool = TPool<FEntry, 256>;` — The shared pool type for task arrays.
- L92 _public function_ `TTaskArray(FEntryPool& TaskEntryPool) : EntryPool` — Constructor. TaskEntryPool is used to allocate new task entries and can be shared between task arrays.
- L95 _public function_ `~TTaskArray()` — Destructor. Returns all allocated tasks to the pool.
- L101 _public function_ `void Reset()` — Clears the array and returns all allocated tasks to the pool.
- L115 _public function_ `template <typename TaskParamType> void Add(TaskParamType&& Task)` — Adds the unkeyed task to the end of the array.
- L124 _public function_ `template <typename TaskParamType> void AddKeyed(KeyType Key, TaskParamType&& Task)` — Adds the keyed task to the end of the array.
- L132 _public function_ `void AddAll(TTaskArray&& OtherArray)` — Moves all the tasks from OtherArray to the end of this array, clearing OtherArray.
- L173 _public function_ `bool DeleteKey(KeyType Key)` — Removes the last added task with the given key. Returns true if the task with the given key was removed, or false if there are no remaining tasks with the given key.
- L192 _public function_ `bool DeleteAllMatchingKeys(KeyType Key)` — Removes all the tasks with the given key. Returns true if a task with the given key was removed, or false if there are no remaining tasks with the given key.
- L212 _public function_ `template <typename CallbackType> void RemoveEachForward(CallbackType&& Callback)` — Traverses the tasks from least recently added to most recently added, calling Callback with each task, and removing each from the array. Callback is a function-like type with the signature: void(TASK_TYPE&)
- L230 _public function_ `template <typename CallbackType> void RemoveEachBackward(CallbackType&& Callback)` — Traverses the tasks from most recently added to least recently added, calling Callback with each task, and removing each from the array. Callback is a function-like type with the signature: void(TASK_TYPE&)
- L244 _public function_ `size_t Num() const` — Returns the total number of tasks held by the array.
- L250 _public function_ `bool IsEmpty() const` — Returns true if there are no tasks held by the array.
- L257 _private typedef_ `using TEntryStack = TStack<FEntry*, 8>;` — An stack of pointers to entries in the linked list.
- L261 _private function_ `void Release(FEntry* Entry)` — Unlinks Entry and releases it back to the pool. Also decrements the count.
- L269 _private member_ `FEntryPool& EntryPool;` — The entry pool. Holds the underlying allocator.
- L272 _private member_ `FEntry* Head = nullptr;` — The doubly-linked list of tasks held by this array.
- L273 _private member_ `FEntry* Tail = nullptr;`
- L276 _private member_ `THashMap<KeyType, TEntryStack> Keyed;` — A map of keyed tasks keys to their ordered task entries in the linked list.
- L279 _private member_ `size_t Count = 0;` — Total number of tasks held by this array.

#### struct `AutoRTFM::TTaskArray::FEntry`  
`struct FEntry`  
_L29-83_
- L32 _public member_ `TaskType Task;` — The task function.
- L34 _public member_ `FEntry* Next = nullptr;` — The next sequential task.
- L36 _public member_ `FEntry* Prev = nullptr;` — The previous sequential task.
- L39 _public function_ `FEntry(const TaskType& Task) : Task` — Constructor using copied Task
- L41 _public function_ `FEntry(TaskType&& Task) : Task` — Constructor using moved Task
- L45 _public function_ `void Unlink(FEntry*& ListHead, FEntry*& ListTail)` — Unlinks this entry from the doubly-linked list, updating the provided head and tail pointers as necessary.
- L69 _public function_ `void Link(FEntry*& ListHead, FEntry*& ListTail)` — Links this entry to the doubly-linked list's tail pointer. This entry must be unlinked before calling.

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace AutoRTFM`

### `Source/Runtime/AutoRTFM/Private/ThreadID.h` (Private)


#### struct `AutoRTFM::FThreadID`  
`struct AUTORTFM_OPEN FThreadID`  
_L22-47_
- desc: A unique identifier for a thread of execution. Constructed as FThreadID::Invalid.
- L25 _public member_ `static const FThreadID Invalid;` — An invalid thread identifier.
- L28 _public prototype_ `static FThreadID GetCurrent();` — Returns the currently executing thread's unique identifier.
- L31 _public function_ `inline bool operator==(const FThreadID& Other) const` — Equality operator
- L37 _public function_ `inline bool operator!=(const FThreadID& Other) const` — Inequality operator
- L43 _public member_ `uint32_t Value = 0;`
- L45 _public member_ `std::thread::id Value;`

#### Free symbols / members of external scopes

- L17 _namespace_ `namespace AutoRTFM`

### `Source/Runtime/AutoRTFM/Private/ToString.h` (Private)


#### Free symbols / members of external scopes

- L9 _namespace_ `namespace AutoRTFM`
- L12 _function_ `inline const char* ToString(EContextStatus Status)` (scope `AutoRTFM`)
- L35 _function_ `inline const char* ToString(ETransactionStatus Status)` (scope `AutoRTFM`)
- L54 _function_ `inline const char* ToString(ETransactionResult Result)` (scope `AutoRTFM`)

### `Source/Runtime/AutoRTFM/Private/Toggles.h` (Private)


#### Free symbols / members of external scopes

- L9 _namespace_ `namespace AutoRTFM`
- L13 _variable_ `static constexpr bool bCollectStats = false;` (scope `AutoRTFM`) — Should we collect stats on the AutoRTFM runtime or not.
- L17 _variable_ `static constexpr bool bTrackAllocationLocations = false;` (scope `AutoRTFM`)
- L19 _variable_ `static constexpr bool bTrackAllocationLocations = true;` (scope `AutoRTFM`)

### `Source/Runtime/AutoRTFM/Private/Transaction.h` (Private)


#### class `AutoRTFM::FTransaction`  
`class AUTORTFM_INTERNAL FTransaction final`  
_L20-139_
- L24 _private prototype_ `void Resurrect(FContext* const InContext);`
- L25 _private prototype_ `void Suppress();`
- L26 _private prototype_ `FTransaction** GetIntrusiveAddress();`
- L29 _private prototype_ `FTransaction(FContext* const Context);` — Constructor.
- L32 _public prototype_ `void Initialize(FTransaction* InParent, FStackRange InStackRange);`
- L34 _public function_ `FTransaction* GetParent() const`
- L39 _public prototype_ `void DeferUntilCommit(TTask<void()>&&);`
- L40 _public prototype_ `void DeferUntilPreAbort(TTask<void()>&&);`
- L41 _public prototype_ `void DeferUntilAbort(TTask<void()>&&);`
- L42 _public prototype_ `void DeferUntilRetry(TTask<void()>&&);`
- L43 _public prototype_ `void PushDeferUntilCommitHandler(const void* Key, TTask<void()>&&);`
- L44 _public prototype_ `void PopDeferUntilCommitHandler(const void* Key);`
- L45 _public prototype_ `void PopAllDeferUntilCommitHandlers(const void* Key);`
- L46 _public prototype_ `void PushDeferUntilAbortHandler(const void* Key, TTask<void()>&&);`
- L47 _public prototype_ `void PopDeferUntilAbortHandler(const void* Key);`
- L48 _public prototype_ `void PopAllDeferUntilAbortHandlers(const void* Key);`
- L50 _public prototype_ `void Abort();`
- L51 _public prototype_ `void Commit();`
- L54 _public prototype_ `void RecordWrite(void* LogicalAddress, size_t Size, EWriteFlags Flags = EWriteFlags::Default);` — Record that a write is about to occur at the given LogicalAddress of Size bytes.
- L56 _public prototype_ `template <unsigned SIZE> void RecordWrite(void* LogicalAddress);`
- L58 _public prototype_ `template <unsigned SIZE> void RecordWriteInsertedSlow(void* LogicalAddress);`
- L60 _public prototype_ `template <unsigned SIZE> void RecordWriteNotInsertedSlow(void* LogicalAddress);`
- L62 _public prototype_ `void DidAllocate(void* LogicalAddress, size_t Size);`
- L63 _public prototype_ `void DidFree(void* LogicalAddress);`
- L66 _public prototype_ `bool IsFresh() const;` — Returns true if the transaction is in its initial state.
- L69 _public function_ `inline bool IsActive() const` — Return true if this transaction is currently active.
- L74 _public function_ `inline TransactionID Identifier() const`
- L80 _public function_ `inline FStackRange GetStackRange() const` — The stack range represents all stack memory inside the transaction scope
- L86 _public prototype_ `inline bool IsOnStack(const void* LogicalAddress) const;` — Returns true if the LogicalAddress is within the stack of the transaction.
- L89 _private typedef_ `using FTaskArray = TTaskArray<TTask<void()>>;`
- L91 _private prototype_ `void Undo();`
- L93 _private prototype_ `void CommitNested();`
- L94 _private prototype_ `void CommitOuterNest();`
- L96 _private prototype_ `bool ShouldRecordWrite(void* LogicalAddress) const;`
- L98 _private member_ `FContext* Context = nullptr;` — null indicates the transaction is not active
- L106 _private member_ `FTransaction* Parent = nullptr;` — This field is used for two purposes: - When the transaction is active, the Parent field is used to support transaction nesting. This field points to our immediate outer nest; it's null when this is the top level. - When the transaction is "freed"--sitting in the FTransactionPool free list--this field is used to point to the next free item, forming a linked list of reusable FTransactions. (See GetIntrusiveAddress.)
- L109 _private member_ `FTaskArray CommitTasks;` — Commit tasks run on commit in forward order.
- L112 _private member_ `FTaskArray PreAbortTasks;` — Abort tasks run on abort (pre memory rollback) in reverse order.
- L115 _private member_ `FTaskArray AbortTasks;` — Abort tasks run on abort (post memory rollback) in reverse order.
- L119 _private member_ `TStack<const void*, 8> DeferredPopOnCommitHandlers;` — If a call to `PopOnCommitHandler` could not find a commit to pop, it is deferred and tried again on the parent transaction.
- L123 _private member_ `TStack<const void*, 8> DeferredPopOnAbortHandlers;` — If a call to `PopOnAbortHandler` could not find an abort to pop, it is deferred and tried again on the parent transaction.
- L127 _private member_ `TStack<const void*, 1> DeferredPopAllOnCommitHandlers;` — If a call to `PopAllOnCommitHandlers` was used and our transaction successfully commits, we need to propagate this to the parent too.
- L131 _private member_ `TStack<const void*, 1> DeferredPopAllOnAbortHandlers;` — If a call to `PopAllOnAbortHandlers` was used and our transaction successfully commits, we need to propagate this to the parent too.
- L133 _private member_ `FHitSet HitSet;`
- L134 _private member_ `FMemoryTracker NewMemoryTracker;`
- L135 _private member_ `FWriteLog WriteLog;`
- L136 _private member_ `FStackRange StackRange;`
- L137 _private member_ `TransactionID ID = 0;`
- L138 _private member_ `bool bIsInAllocateFn = false;`

#### Free symbols / members of external scopes

- L16 _namespace_ `namespace AutoRTFM`

### `Source/Runtime/AutoRTFM/Private/TransactionInlines.h` (Private)


#### Free symbols / members of external scopes

- L22 _macro_ `#define AUTORTFM_CHECK_ASAN_FAKE_STACKS 1`
- L31 _macro_ `#define AUTORTFM_CHECK_ASAN_FAKE_STACKS 0`
- L34 _namespace_ `namespace AutoRTFM`
- L37 _function_ `UE_AUTORTFM_FORCEINLINE bool FTransaction::IsOnStack(const void* LogicalAddress) const` (scope `AutoRTFM::FTransaction`)
- L57 _function_ `UE_AUTORTFM_FORCEINLINE bool FTransaction::ShouldRecordWrite(void* LogicalAddress) const` (scope `AutoRTFM::FTransaction`)
- L66 _function_ `AUTORTFM_NO_ASAN UE_AUTORTFM_FORCEINLINE void FTransaction::RecordWrite( void* LogicalAddress, size_t Size, EWriteFlags Flags )` (scope `AutoRTFM::FTransaction`)
- L129 _function_ `template <unsigned SIZE> AUTORTFM_NO_ASAN UE_AUTORTFM_FORCEINLINE void FTransaction::RecordWrite(void* LogicalAddress)` (scope `AutoRTFM::FTransaction`)
- L153 _function_ `template <unsigned SIZE> AUTORTFM_NO_ASAN UE_AUTORTFM_FORCENOINLINE void FTransaction::RecordWriteNotInsertedSlow(void* LogicalAddress)` (scope `AutoRTFM::FTransaction`)
- L168 _function_ `template <unsigned SIZE> AUTORTFM_NO_ASAN UE_AUTORTFM_FORCENOINLINE void FTransaction::RecordWriteInsertedSlow(void* LogicalAddress)` (scope `AutoRTFM::FTransaction`)
- L182 _function_ `UE_AUTORTFM_FORCEINLINE void FTransaction::DidAllocate(void* LogicalAddress, const size_t Size)` (scope `AutoRTFM::FTransaction`)
- L194 _function_ `UE_AUTORTFM_FORCEINLINE void FTransaction::DidFree(void* LogicalAddress)` (scope `AutoRTFM::FTransaction`)
- L211 _function_ `UE_AUTORTFM_FORCEINLINE void FTransaction::DeferUntilCommit(TTask<void()>&& Callback)` (scope `AutoRTFM::FTransaction`)
- L220 _function_ `UE_AUTORTFM_FORCEINLINE void FTransaction::DeferUntilPreAbort(TTask<void()>&& Callback)` (scope `AutoRTFM::FTransaction`)
- L229 _function_ `UE_AUTORTFM_FORCEINLINE void FTransaction::DeferUntilAbort(TTask<void()>&& Callback)` (scope `AutoRTFM::FTransaction`)
- L238 _function_ `UE_AUTORTFM_FORCEINLINE void FTransaction::PushDeferUntilCommitHandler(const void* Key, TTask<void()>&& Callback)` (scope `AutoRTFM::FTransaction`)
- L247 _function_ `UE_AUTORTFM_FORCEINLINE void FTransaction::PopDeferUntilCommitHandler(const void* Key)` (scope `AutoRTFM::FTransaction`)
- L257 _function_ `UE_AUTORTFM_FORCEINLINE void FTransaction::PopAllDeferUntilCommitHandlers(const void* Key)` (scope `AutoRTFM::FTransaction`)
- L265 _function_ `UE_AUTORTFM_FORCEINLINE void FTransaction::PushDeferUntilAbortHandler(const void* Key, TTask<void()>&& Callback)` (scope `AutoRTFM::FTransaction`)
- L274 _function_ `UE_AUTORTFM_FORCEINLINE void FTransaction::PopDeferUntilAbortHandler(const void* Key)` (scope `AutoRTFM::FTransaction`)
- L284 _function_ `UE_AUTORTFM_FORCEINLINE void FTransaction::PopAllDeferUntilAbortHandlers(const void* Key)` (scope `AutoRTFM::FTransaction`)

### `Source/Runtime/AutoRTFM/Private/Utils.h` (Private)


#### struct `AutoRTFM::TScopedAssignment`  
`template <typename T> struct TScopedAssignment`  
_L179-198_
- desc: RAII helper to assign a value to a variable for the lifetime of the FScopedAssignment, restoring the original value when the FScopedAssignment is destructed.
- L181 _public function_ `inline TScopedAssignment(T& Variable, T NewValue) : Variable(Variable), OldValue(Variable)`
- L186 _public function_ `inline ~TScopedAssignment()`
- L192 _private prototype_ `TScopedAssignment(const TScopedAssignment&) = delete;`
- L193 _private prototype_ `TScopedAssignment(TScopedAssignment&&) = delete;`
- L194 _private prototype_ `TScopedAssignment& operator=(const TScopedAssignment&) = delete;`
- L195 _private prototype_ `TScopedAssignment& operator=(TScopedAssignment&&) = delete;`
- L196 _private member_ `T& Variable;`
- L197 _private member_ `T OldValue;`

#### Free symbols / members of external scopes

- L16 _macro_ `#define AUTORTFM_VERBOSE_ENABLED 0` — If 0 then verbose logging is compiled-out.
- L27 _macro_ `#define AUTORTFM_INTERNAL [[clang::autortfm(autortfm_mode_internal)]]` — AutoRTFM internal-runtime-only attribute that can be applied to classes, methods or functions to prevent AutoRTFM closed function(s) from being generated. Applying the annotation to a class is equivalent to applying the annotation to each method of the class. When annotating a function, the attribute must be placed on a the function declaration (usually in the header) and not a function implementation. Annotated functions are callable from both the open and closed, without trampolines, and the function is always uninstrumented. Note: This annotation will prevent inlining of annotated functions.
- L29 _namespace_ `namespace AutoRTFM`
- L36 _prototype_ `AUTORTFM_DISABLE __attribute__((__format__(__printf__, 4, 5))) void ReportError( const char* File, int Line, void* ProgramCounter, const char* Format, ...);` (scope `AutoRTFM`) — Reports an internal AutoRTFM issue. The behavior of this function will vary based on ForTheRuntime::GetInternalAbortAction() and ForTheRuntime::GetEnsureOnInternalAbort(). If ProgramCounter is null, then the return address of the call will be used.
- L39 _prototype_ `[[noreturn]] inline void InternalUnreachable();` (scope `AutoRTFM`)
- L41 _prototype_ `std::string GetFunctionDescription(void* FunctionPtr);` (scope `AutoRTFM`)
- L44 _function_ `template <typename TReturnType, typename... TParameterTypes> std::string GetFunctionDescription(TReturnType (*FunctionPtr)(TParameterTypes...))` (scope `AutoRTFM`)
- L53 _prototype_ `[[clang::preserve_most, noreturn]] UE_AUTORTFM_FORCENOINLINE void DoAssert(void (*Logger)());` (scope `AutoRTFM`) — We use a special calling convention for this call to minimize the cost of calling this function (which is super unlikely to be called because it is the asserting true codepath, EG. only fatal process destroying explosions happen here).
- L59 _prototype_ `[[clang::preserve_most]] UE_AUTORTFM_FORCENOINLINE void DoExpect(void (*Logger)());` (scope `AutoRTFM`) — We use a special calling convention for this call to minimize the cost of calling this function (which is super unlikely to be called because it is the expecting true codepath, EG. only things we don't expect to happen get here).
- L62 _function_ `inline void LogV(const char* File, int Line, void* ProgramCounter, autortfm_log_severity Severity, const char* Format, va_list Args)` (scope `AutoRTFM`) — Logs a message using a printf-style format string and va_list arguments.
- L73 _function_ `__attribute__((__format__(__printf__, 5, 6))) inline void Log( const char* File, int Line, void* ProgramCounter, autortfm_log_severity Severity, const char* Format, ...)` (scope `AutoRTFM`) — Logs a message using a printf-style format string and variadic arguments.
- L88 _function_ `inline void LogWithCallstackV(autortfm_log_severity Severity, const char* Format, va_list Args)` (scope `AutoRTFM`) — Logs a message with a callstack using a printf-style format string and va_list arguments.
- L94 _function_ `__attribute__((__format__(__printf__, 2, 3))) inline void LogWithCallstack(autortfm_log_severity Severity, const char* Format, ...)` (scope `AutoRTFM`) — Logs a message with a callstack using a printf-style format string and variadic arguments.
- L104 _function_ `inline void EnsureFailureV(const char* File, int Line, void* ProgramCounter, const char* Condition, const char* Format, va_list Args)` (scope `AutoRTFM`) — Reports an ensure failure using a printf-style format string and va_list arguments. If ProgramCounter is null, then the return address of the call will be used.
- L116 _function_ `__attribute__((__format__(__printf__, 5, 6))) inline void EnsureFailure( const char* File, int Line, void* ProgramCounter, const char* Condition, const char* Format, ...)` (scope `AutoRTFM`) — Reports an ensure failure using a printf-style format string and variadic arguments. If ProgramCounter is null, then the return address of the call will be used.
- L133 _function_ `template <typename T> inline constexpr T AlignDown(T Value, T Alignment)` (scope `AutoRTFM`) — Rounds Value down to the next multiple of Alignment. Alignment must be a power of two.
- L142 _function_ `template <typename T> inline constexpr T AlignUp(T Value, T Alignment)` (scope `AutoRTFM`) — Rounds Value up to the next multiple of Alignment. Alignment must be a power of two.
- L151 _function_ `template <typename T> inline constexpr T RoundDown(T Value, T Multiple)` (scope `AutoRTFM`) — Rounds Value down to the next multiple of Multiple. Unlike AlignDown(), Multiple does not need to be a power of two.
- L160 _function_ `template <typename T> inline constexpr T RoundUp(T Value, T Multiple)` (scope `AutoRTFM`) — Rounds Value up to the next multiple of Multiple. Unlike AlignUp(), Multiple does not need to be a power of two.
- L169 _function_ `template <typename T> requires(std::is_integral_v<T> && std::is_unsigned_v<T>) inline constexpr T Log2(T Value)` (scope `AutoRTFM`) — Returns the log2 of Value
- L202 _macro_ `#define AUTORTFM_SCOPED_ASSIGNMENT(Variable, Value) \` — Assigns Value to Variable, and restores the original value of Variable at the end of the current scope.
- L207 _macro_ `#define AUTORTFM_REQUIRE_SEMICOLON static_assert(true)`
- L209 _macro_ `#define AUTORTFM_REPORT_ERROR(Format, ...) \`
- L212 _macro_ `#define AUTORTFM_LOG_AT_SEVERITY(Severity, Format, ...) \`
- L215 _macro_ `#define AUTORTFM_VERBOSE(Format, ...) AUTORTFM_LOG_AT_SEVERITY(autortfm_log_verbose, Format, ##__VA_ARGS__)`
- L216 _macro_ `#define AUTORTFM_LOG(Format, ...) AUTORTFM_LOG_AT_SEVERITY(autortfm_log_info, Format, ##__VA_ARGS__)`
- L217 _macro_ `#define AUTORTFM_WARN(Format, ...) AUTORTFM_LOG_AT_SEVERITY(autortfm_log_warn, Format, ##__VA_ARGS__)`
- L218 _macro_ `#define AUTORTFM_ERROR(Format, ...) AUTORTFM_LOG_AT_SEVERITY(autortfm_log_error, Format, ##__VA_ARGS__)`
- L219 _macro_ `#define AUTORTFM_FATAL(Format, ...) AUTORTFM_LOG_AT_SEVERITY(autortfm_log_fatal, Format, ##__VA_ARGS__)`
- L221 _macro_ `#define AUTORTFM_VERBOSE_V(Format, Args) \`
- L223 _macro_ `#define AUTORTFM_LOG_V(Format, Args) \`
- L225 _macro_ `#define AUTORTFM_WARN_V(Format, Args) \`
- L227 _macro_ `#define AUTORTFM_ERROR_V(Format, Args) \`
- L229 _macro_ `#define AUTORTFM_FATAL_V(Format, Args) \`
- L232 _macro_ `#define AUTORTFM_VERBOSE_IF(Condition, Format, ...) \`
- L240 _macro_ `#define AUTORTFM_LOG_IF(Condition, Format, ...) \`
- L248 _macro_ `#define AUTORTFM_WARN_IF(Condition, Format, ...) \`
- L256 _macro_ `#define AUTORTFM_ERROR_IF(Condition, Format, ...) \`
- L264 _macro_ `#define AUTORTFM_FATAL_IF(Condition, Format, ...) \`
- L279 _macro_ `#define AUTORTFM_VERBOSE(...) AUTORTFM_REQUIRE_SEMICOLON`
- L280 _macro_ `#define AUTORTFM_VERBOSE_V(...) AUTORTFM_REQUIRE_SEMICOLON`
- L281 _macro_ `#define AUTORTFM_VERBOSE_IF(...) AUTORTFM_REQUIRE_SEMICOLON`
- L284 _macro_ `#define AUTORTFM_ENSURE(Condition) \`
- L297 _macro_ `#define AUTORTFM_ENSURE_MSG(Condition, Format, ...) \`
- L310 _macro_ `#define AUTORTFM_ENSURE_MSG_V(Condition, Format, Args) \`
- L323 _macro_ `#define AUTORTFM_DUMP_STACKTRACE(Message, ...) ::AutoRTFM::LogWithCallstack(autortfm_log_error, Message, ##__VA_ARGS__)`
- L337 _macro_ `#define AUTORTFM_ASSERT(exp) \` — This is all a bit funky - but for good reason! We want `AUTORTFM_ASSERT` to be as close to *zero* cost if the assert wouldn't trigger. We will always pay the cost of the unlikely branch, but we need to make the body of taking the assert happen in another function so as not to affect codegen, register allocation, and stack reservation. But we also want the `AUTORTFM_ASSERT` to give us accurate `__FILE__` and `__LINE__` information for the line that it was triggered on. So what we do is have a lambda at the line that actually does the assert (but crucially gets the correct file and line numbers), but then pass this to another function `DoAssert` which has a special calling convention that makes the caller as optimal as possible (at the expense of the callee).
- L352 _macro_ `#define AUTORTFM_ASSERT_DEBUG(exp) ((void)AUTORTFM_LIKELY(static_cast<bool>(exp)))`
- L354 _macro_ `#define AUTORTFM_ASSERT_DEBUG(exp) \`
- L367 _macro_ `#define AUTORTFM_EXPECT(exp) \` — Same funkiness as AUTORTFM_ASSERT, except that it doesn't cause a fatal error. TODO: Maybe upgrade the Info -> Warning?
- L379 _macro_ `#define AUTORTFM_NO_ASAN [[clang::no_sanitize("address")]]`
- L384 _macro_ `#define AUTORTFM_NO_ASAN`
- L388 _macro_ `#define AUTORTFM_MUST_TAIL [[clang::musttail]]`
- L392 _macro_ `#define AUTORTFM_MUST_TAIL`
- L396 _macro_ `#define CA_SUPPRESS(WarningNumber)`
- L399 _function_ `[[noreturn]] inline void AutoRTFM::InternalUnreachable()` (scope `AutoRTFM`)

### `Source/Runtime/AutoRTFM/Private/WindowsHeader.h` (Private)


#### Free symbols / members of external scopes

- L8 _macro_ `#define WIN32_LEAN_AND_MEAN`
- L9 _macro_ `#define NOMINMAX`

### `Source/Runtime/AutoRTFM/Private/WriteLog.h` (Private)


#### struct `AutoRTFM::FWriteLogEntry`  
`struct AUTORTFM_INTERNAL FWriteLogEntry final`  
_L20-46_
- L23 _public member_ `std::byte* LogicalAddress = nullptr;` — The address of the write.
- L26 _public member_ `std::byte* Data = nullptr;` — A pointer to the original data before the write occurred.
- L29 _public member_ `size_t Size = 0;` — The size of the write in bytes.
- L32 _public member_ `EWriteFlags Flags = EWriteFlags::Default;` — Flags on the write.
- L37 _public function_ `[[nodiscard]] FWriteLogEntry Advance(size_t NumBytes) const` — Returns a new FWriteLogEntry with the logical address and data pointers increased by NumBytes, the size decreased by NumBytes, and the same flags.

#### class `AutoRTFM::FWriteLog`  
`class AUTORTFM_INTERNAL FWriteLog final`  
_L51-700_
- desc: FWriteLog holds an ordered list of write records which can be iterated forwards and backwards. Ensure changes to this class are kept in sync with AutoRTFM.natvis.
- L125 _public typedef_ `using FRegularRecordLayout = FRecordLayout< 14, 2, 48>;` — 64           50 48                                              0 ┌─────────────┬─┬───────────────────────────────────────────────┐ │    Size     │F│                    Address                    │ └─────────────┴─┴───────────────────────────────────────────────┘
- L131 _public typedef_ `using FCustomRollbackRecordLayout = FRecordLayout< 12, 4, 48>;` — 64         52   48                                              0 ┌───────────┬───┬───────────────────────────────────────────────┐ │   Size    │ F │                    Address                    │ └───────────┴───┴───────────────────────────────────────────────┘
- L382 _public function_ `FWriteLog()` — Constructor
- L388 _public function_ `~FWriteLog()` — Destructor
- L395 _public function_ `void Push(FWriteLogEntry Entry)` — Adds the write log entry to the log. The log will make a copy of the FWriteLogEntry's data.
- L410 _public function_ `template <unsigned int Size> void PushSmall(std::byte* LogicalAddress, std::byte* Data, EWriteFlags Flags = EWriteFlags::Default)` — Adds the write log entry to the log; assumes a payload small enough that splitting is not beneficial. If you have large sizes, you should use `Push` instead so that splitting can occur.
- L530 _public typedef_ `using Iterator = TIterator< true>;`
- L531 _public typedef_ `using ReverseIterator = TIterator< false>;`
- L533 _public function_ `Iterator begin() const`
- L537 _public function_ `ReverseIterator rbegin() const`
- L541 _public function_ `Iterator end() const`
- L545 _public function_ `ReverseIterator rend() const`
- L551 _public function_ `void Reset()` — Resets the write log to its initial state, freeing any allocated memory.
- L570 _public function_ `UE_AUTORTFM_FORCEINLINE bool IsEmpty() const` — Returns true if the log holds no entries.
- L576 _public function_ `UE_AUTORTFM_FORCEINLINE size_t Num() const` — Return the number of entries in the log.
- L582 _public function_ `UE_AUTORTFM_FORCEINLINE size_t TotalSize() const` — Return the total size in bytes for all entries in the log.
- L589 _private function_ `template <typename Layout> void Push(FWriteLogEntry Entry)`
- L648 _private function_ `template <size_t Size, typename Layout> void PushSmall(std::byte* LogicalAddress, std::byte* Data, EWriteFlags Flags)`
- L668 _private function_ `UE_AUTORTFM_FORCEINLINE void AllocateNewBlock(size_t Size)`
- L680 _private member_ `template <size_t SIZE> static constexpr bool IsAlignedForFRecord = (SIZE & (alignof(FRecord) - 1)) == 0;`
- L684 _private member_ `static constexpr size_t HeadBlockSize = 256;` — The size of the inline block, which is declared as a byte array (`HeadBlockMemory`) inside the write log.
- L687 _private member_ `static constexpr size_t MaxBlockDataSize = 1024 * 1024 * 16;` — The upper bound on heap-allocated block size.
- L688 _private member_ `static constexpr size_t MaxBlockSize = AlignUp(sizeof(FBlock) + sizeof(FRecord) + MaxBlockDataSize, alignof(FRecord));`
- L694 _private member_ `FBlock* HeadBlock = reinterpret_cast<FBlock*>(HeadBlockMemory);`
- L695 _private member_ `FBlock* TailBlock = reinterpret_cast<FBlock*>(HeadBlockMemory);`
- L696 _private member_ `size_t NumEntries = 0;`
- L697 _private member_ `size_t TotalSizeBytes = 0;`
- L698 _private member_ `size_t NextBlockSize = FBlock::DefaultSize;`
- L699 _private member_ `alignas(alignof(FBlock)) std::byte HeadBlockMemory[HeadBlockSize];`

#### enum `AutoRTFM::FWriteLog::EAppendMode`  
`enum EAppendMode`  
_L53-57_
- L55 _public enumerator_ `Partial`
- L56 _public enumerator_ `Whole`

#### struct `AutoRTFM::FWriteLog::FRecordLayout`  
`template <size_t SizeBits, size_t FlagBits, size_t AddressBits> struct FRecordLayout`  
_L61-119_
- L64 _public member_ `static constexpr size_t NumAddressBits = AddressBits;` — Number of bits used by the FRecord to represent a write's address.
- L67 _public member_ `static constexpr size_t NumFlagsBits = FlagBits;` — Number of bits used by the FRecord to represent a write's flags.
- L71 _public member_ `static constexpr size_t NumSizeBits = SizeBits;` — Number of bits used by the FRecord to represent a write's size. Note a record size must be greater than one byte, so is stored as Size-1.
- L75 _public member_ `static constexpr size_t AddressShift = 0;`
- L76 _public member_ `static constexpr size_t AddressMask = (static_cast<size_t>(1) << NumAddressBits) - 1;`
- L77 _public member_ `static constexpr size_t FlagsShift = NumAddressBits;`
- L78 _public member_ `static constexpr size_t FlagsMask = (static_cast<size_t>(1) << NumFlagsBits) - 1;`
- L79 _public member_ `static constexpr size_t SizeShift = NumAddressBits + NumFlagsBits;`
- L80 _public member_ `static constexpr size_t SizeMask = (static_cast<size_t>(1) << NumSizeBits) - 1;`
- L82 _public member_ `static constexpr size_t MaxAddress = AddressMask;`
- L83 _public member_ `static constexpr size_t MaxSize = SizeMask + 1;`
- L85 _public function_ `[[nodiscard]] static uint64_t Pack(std::byte* Address, EWriteFlags Flags, size_t Size)`
- L96 _public function_ `[[nodiscard]] static uint64_t ReplaceSize(uint64_t Packed, size_t NewSize)`
- L104 _public function_ `[[nodiscard]] static std::byte* UnpackAddress(uint64_t Packed)`
- L109 _public function_ `[[nodiscard]] static EWriteFlags UnpackFlags(uint64_t Packed)`
- L114 _public function_ `[[nodiscard]] static size_t UnpackSize(uint64_t Packed)`

#### struct `AutoRTFM::FWriteLog::FRecord`  
`struct FRecord`  
_L134-186_
- L138 _public function_ `bool UsesCustomRollback() const` — Returns true if the record has the EWriteFlags::CustomRollback flag set. This alters the bit packing layout of the record.
- L145 _public function_ `template <typename Layout> void Set(std::byte* Address, EWriteFlags Flags, size_t Size)` — Packs the address, flags and size into the record using the provided bit packing layout.
- L153 _public function_ `template <typename Layout> void SetSize(size_t NewSize)` — Replaces the size field of the record using the provided bit packing layout.
- L160 _public function_ `std::byte* Address() const` — Returns the unpacked address from the record.
- L167 _public function_ `EWriteFlags Flags() const` — Returns the unpacked flags from the record.
- L173 _public function_ `size_t Size() const` — Returns the unpacked size from the record.
- L180 _public function_ `template <typename Layout> size_t Size() const` — Returns the unpacked size from the record, using the bit packing layout.
- L185 _public member_ `uint64_t Bits;`

#### struct `AutoRTFM::FWriteLog::FBlock`  
`struct FBlock final`  
_L192-378_
- desc: Ensure changes to this structure are kept in sync with Unreal.natvis.
- L203 _public member_ `static constexpr size_t DefaultSize = 2048;` — Starting size of a heap-allocated block, including the FBlock struct header.
- L208 _public function_ `explicit FBlock(size_t TotalSize)` — Constructor TotalSize is the total size of the allocated memory for the block including the FBlock header.
- L222 _public function_ `static FBlock* Allocate(size_t TotalSize)` — Allocate performs a heap allocation of a new block. TotalSize is the total size of the allocated memory for the block including the FBlock header.
- L233 _public function_ `void Free()` — Free releases the heap-allocated memory for this block. Note: This block must have been allocated with a call to Allocate().
- L241 _public function_ `std::byte* DataStart()` — Returns a pointer to the data for the first entry
- L247 _public function_ `std::byte* LastData()` — Returns a pointer to the data for the last entry
- L253 _public function_ `bool IsEmpty() const` — Returns true if the block holds no entries.
- L260 _public function_ `UE_AUTORTFM_FORCEINLINE size_t SpaceRemaining() const` — Returns the number of unused bytes in the block between the last record and end of the data.
- L281 _public function_ `template <EAppendMode AppendMode, typename Layout> UE_AUTORTFM_FORCEINLINE size_t AppendWithNewRecord( std::byte* LogicalAddress, std::byte* DataIn, size_t NumBytes, EWriteFlags Flags)` — Appends a new record to the block, returning the number of bytes copied to the new record from the front of DataIn. If AppendMode is Partial, then AppendWithNewRecord() will append as many bytes that will fit in the remaining available space of the block, which may be fewer than NumBytes. In this mode NumBytes may be 0, in which case the function does nothing and returns 0. If AppendMode is Whole, then it is the caller's responsibility to ensure that there is enough space in the block to hold an additional NumBytes of data plus the size of an FRecord. In this mode NumBytes must be greater than zero. Layout is the bit-packing layout of a record with the given flags.
- L328 _public function_ `template <EAppendMode AppendMode, typename Layout> UE_AUTORTFM_FORCEINLINE size_t AppendToLastRecord( std::byte* LogicalAddress, std::byte* DataIn, size_t NumBytes, EWriteFlags Flags)` — Appends additional data to the tail record, returning the number of bytes copied to the end of the record from the front of DataIn. Regardless of AppendMode, if the last record cannot be appended to, either because the logical address does not start at the end of the last record's logical address or the flags are incompatible, then the function returns 0. If AppendMode is Partial, then AppendWithNewRecord() will append as many bytes that will fit in the remaining available space of the block, which may be fewer than NumBytes. If AppendMode is Whole, then AppendWithNewRecord() will only append the full NumBytes if they fit, otherwise the function will do nothing and return 0. Layout is the bit-packing layout of a record with the given flags.
- L366 _public member_ `FBlock* NextBlock = nullptr;` — The next block in the linked list.
- L368 _public member_ `FBlock* PrevBlock = nullptr;` — The previous block in the linked list.
- L370 _public member_ `FRecord* FirstRecord = nullptr;` — The pointer to the first entry's record
- L372 _public member_ `FRecord* LastRecord = nullptr;` — The pointer to the last entry's record
- L374 _public member_ `std::byte* DataEnd = nullptr;` — One byte beyond the end of the last entry's data
- L377 _private prototype_ `~FBlock() = delete;`

#### struct `AutoRTFM::FWriteLog::TIterator`  
`template <bool IS_FORWARD> struct TIterator final`  
_L424-528_
- desc: Iterator for enumerating the writes of the log.
- L426 _public prototype_ `TIterator() = default;`
- L428 _public function_ `TIterator(FBlock* StartBlock) : Block(StartBlock)`
- L444 _public function_ `FWriteLogEntry operator*() const` — Returns the entry at the current iterator's position.
- L455 _public function_ `void operator++()` — Progresses the iterator to the next entry
- L492 _public function_ `bool operator!=(const TIterator& Other) const` — Inequality operator
- L499 _private function_ `UE_AUTORTFM_FORCEINLINE void Reset()` — Resets the iterator (compares equal to the write log's end())
- L509 _private function_ `UE_AUTORTFM_FORCEINLINE bool AdvanceBlock()` — Moves from this block to the next (if IS_FORWARD) or previous (if not IS_FORWARD), skipping any empty blocks. Returns true on success. If no more blocks exist, resets the iterator and returns false.
- L525 _private member_ `FBlock* Block = nullptr;`
- L526 _private member_ `std::byte* Data = nullptr;`
- L527 _private member_ `FRecord* Record = nullptr;`

#### Free symbols / members of external scopes

- L18 _namespace_ `namespace AutoRTFM`

### `Source/Runtime/AutoRTFM/Public/AutoRTFM.h` (Public)


#### enum `AutoRTFM::EWriteFlags`  
`enum class EWriteFlags`  
_L30-43_
- L33 _public enumerator_ `Default = autortfm_write_default` — No flags applied to the write.
- L35 _public enumerator_ `NoSanitize = autortfm_write_no_sanitize` — The write should not be considered by the AutoRTFM sanitizer.
- L38 _public enumerator_ `CustomRollback = autortfm_write_custom_rollback` — The autortfm_extern_api::RollbackWrite will be called to perform the rollback for this write if the transaction is aborted.
- L41 _public enumerator_ `CustomFlag0 = autortfm_write_custom_flag_0` — Custom flag bits which can be used by the custom abort callbacks. Requires CustomRollback for usage.
- L42 _public enumerator_ `CustomFlag1 = autortfm_write_custom_flag_1`

#### enum `AutoRTFM::ETransactionResult`  
`enum class ETransactionResult`  
_L74-108_
- desc: The transaction result provides information on how a transaction completed.
- L78 _public enumerator_ `Committed = autortfm_transaction_committed` — The transaction committed successfully. For a nested transaction this does not mean that the transaction effects cannot be undone later if the parent transaction is aborted for any reason.
- L81 _public enumerator_ `AbortedByRequest = autortfm_transaction_aborted_by_request` — The transaction aborted because of an explicit call to AbortTransaction.
- L84 _public enumerator_ `AbortedByLanguage = autortfm_transaction_aborted_by_language` — The transaction aborted because of unhandled constructs in the code (atomics, unhandled function calls, etc).
- L87 _public enumerator_ `AbortedByCascadingAbort = autortfm_transaction_aborted_by_cascading_abort` — The transaction aborted because of an explicit call to CascadingAbortTransaction.
- L91 _public enumerator_ `RejectedTransactDuringUnwind = autortfm_transaction_rejected_during_unwind` — A transaction was rejected because a new transaction nest was attempted after a cascading abort or cascading retry.
- L95 _public enumerator_ `RejectedTransactDuringCommit = autortfm_transaction_rejected_during_commit` — A transaction was rejected because a new transaction nest was attempted (via OnCommit) while the current transaction was being committed.
- L99 _public enumerator_ `RejectedTransactDuringAbort = autortfm_transaction_rejected_during_abort` — A transaction was rejected because a new transaction nest was attempted (via OnAbort) while the current transaction was being aborted.
- L103 _public enumerator_ `RejectedTransactDuringRetry = autortfm_transaction_rejected_during_retry` — A transaction was rejected because a new transaction nest was attempted (via OnRetry) while the current transaction was being retried.
- L107 _public enumerator_ `RejectedTransactDuringCompletion = autortfm_transaction_rejected_during_complete` — A transaction was rejected because a new transaction nest was attempted (via OnComplete) while the current transaction was being retried.

#### enum `AutoRTFM::ETransactionStatus`  
`enum class ETransactionStatus`  
_L134-154_
- desc: The transaction status provides information on how a transaction is currently executing or completed.
- L137 _public enumerator_ `Executing = autortfm_transaction_executing` — The transaction aborted because of an explicit call to AbortTransaction.
- L141 _public enumerator_ `Committed = autortfm_transaction_committed` — The transaction committed successfully. For a nested transaction this does not mean that the transaction effects cannot be undone later if the parent transaction is aborted for any reason.
- L144 _public enumerator_ `AbortedByRequest = autortfm_transaction_aborted_by_request` — The transaction aborted because of an explicit call to AbortTransaction.
- L147 _public enumerator_ `AbortedByLanguage = autortfm_transaction_aborted_by_language` — The transaction aborted because of unhandled constructs in the code (atomics, unhandled function calls, etc).
- L150 _public enumerator_ `AbortedByCascadingAbort = autortfm_transaction_aborted_by_cascading_abort` — The transaction aborted because of an explicit call to CascadingAbortTransaction.
- L153 _public enumerator_ `AbortedByCascadingRetry = autortfm_transaction_aborted_by_cascading_retry` — The transaction aborted because of an explicit call to CascadingRetryTransaction.

#### enum `AutoRTFM::EContextStatus`  
`enum class EContextStatus : uint8_t`  
_L195-223_
- desc: The context status shows what state the AutoRTFM context is currently in.
- L199 _public enumerator_ `Idle = autortfm_status_idle` — An Idle status means we are not in transactional code - i.e. the transaction stack is empty, or queried on a non-transactional thread.
- L202 _public enumerator_ `OnTrack = autortfm_status_on_track` — An OnTrack status means we are in transactional code.
- L206 _public enumerator_ `Unwinding = autortfm_status_unwinding` — An Unwinding status means we've performed a cascading abort / retry and are now in the process of unwinding the stack to the outermost Transact()
- L209 _public enumerator_ `Committing = autortfm_status_committing` — We are currently running the on-commit handlers for a transaction.
- L212 _public enumerator_ `Aborting = autortfm_status_aborting` — We are currently running the on-abort handlers for a transaction.
- L215 _public enumerator_ `Retrying = autortfm_status_retrying` — We are currently running the on-retry handlers for a transaction stack.
- L218 _public enumerator_ `Completing = autortfm_status_completing` — We are currently running the on-complete handlers for a transaction stack.
- L222 _public enumerator_ `InStaticLocalInitializer = autortfm_status_in_static_local_initializer` — Means we are in a static local initializer which always run in the open. `IsTransactional()` will return `false` when in this state.

#### enum `AutoRTFM::Sanitizer::EMode`  
`enum class EMode : uint8_t`  
_L239-249_
- desc: An enumerator of AutoRTFM sanitizer levels. The AutoRTFM sanitizer is used to detect modification by open-code to memory that was written by a transaction. In this situation, aborting the transaction can corrupt memory as the undo will overwrite the writes made in the open-code.
- L242 _public enumerator_ `Disabled = autortfm_sanitizer_disabled` — AutoRTFM sanitizer is disabled.
- L245 _public enumerator_ `Warn = autortfm_sanitizer_warn` — AutoRTFM sanitizer is enabled and failures are treated as warnings.
- L248 _public enumerator_ `Error = autortfm_sanitizer_error` — AutoRTFM sanitizer is enabled and failures are treated as errors.

#### class `AutoRTFM::Sanitizer::FDisableScope`  
`class FDisableScope`  
_L286-299_
- desc: A helper class that temporarily disables the AutoRTFM sanitizer for the lifetime of the object.
- L289 _public function_ `UE_AUTORTFM_FORCEINLINE FDisableScope() : Handle`
- L290 _public function_ `UE_AUTORTFM_FORCEINLINE ~FDisableScope()`
- L296 _private prototype_ `FDisableScope(const FDisableScope&) = delete;`
- L297 _private prototype_ `FDisableScope& operator=(const FDisableScope&) = delete;`
- L298 _private member_ `FDisableHandle const Handle;`

#### enum `AutoRTFM::EOpenFlags`  
`enum class EOpenFlags`  
_L571-577_
- desc: Optional flags that can be passed as the first template argument to Open().
- L574 _public enumerator_ `Default` — Default open behavior.
- L576 _public enumerator_ `NoSanitize` — The AutoRTFM sanitizer will be disabled for the scope of this open.

#### struct `AutoRTFM::Open::FArgs`  
`struct FArgs`  
_L627-631_
- desc: Call Functor in the open, and in-place construct the return value into OpenReturnValue.
- L629 _public member_ `const FunctorType& Functor;`
- L630 _public member_ `void* OpenReturnValueMemory;`
- L681 _public member_ `ReturnType ReturnValue;`

#### struct `AutoRTFM::Open::FArgs`  
`struct FArgs`  
_L678-682_
- L629 _public member_ `const FunctorType& Functor;`
- L630 _public member_ `void* OpenReturnValueMemory;`
- L681 _public member_ `ReturnType ReturnValue;`

#### struct `AutoRTFM::FHeapRedirectCallbacks`  
`struct FHeapRedirectCallbacks`  
_L961-974_
- L963 _public member_ `uint32_t AddressSpace;`
- L964 _public member_ `void (*RedirectedLoad)(void* DestPointer, uint64_t Size, uint64_t SourceAddress, bool bWillWriteHint);`
- L965 _public member_ `void (*RedirectedLoad8)(void* DestPointer, uint64_t SourceAddress, bool bWillWriteHint);`
- L966 _public member_ `void (*RedirectedLoad4)(void* DestPointer, uint64_t SourceAddress, bool bWillWriteHint);`
- L967 _public member_ `void (*RedirectedLoad2)(void* DestPointer, uint64_t SourceAddress, bool bWillWriteHint);`
- L968 _public member_ `void (*RedirectedLoad1)(void* DestPointer, uint64_t SourceAddress, bool bWillWriteHint);`
- L969 _public member_ `void (*RedirectedStore)(uint64_t DestAddress, uint64_t Size, const void* SourcePointer);`
- L970 _public member_ `void (*RedirectedStore8)(uint64_t DestAddress, const void* SourcePointer);`
- L971 _public member_ `void (*RedirectedStore4)(uint64_t DestAddress, const void* SourcePointer);`
- L972 _public member_ `void (*RedirectedStore2)(uint64_t DestAddress, const void* SourcePointer);`
- L973 _public member_ `void (*RedirectedStore1)(uint64_t DestAddress, const void* SourcePointer);`

#### struct `AutoRTFM::TScopedAssign`  
`template <typename DataType> struct AUTORTFM_DISABLE_NO_SANITIZE TScopedAssign`  
_L1044-1060_
- desc: A RAII helper to call AutoRTFM::Assign(Variable, NewValue) on construction and again on destruction with the old value of Variable.
- L1046 _public function_ `TScopedAssign(DataType& Variable, DataType NewValue) : Variable`
- L1050 _public function_ `~TScopedAssign()`
- L1056 _private prototype_ `TScopedAssign(DataType& Variable) = delete;`
- L1057 _private prototype_ `const TScopedAssign& operator=(DataType& Variable) = delete;`
- L1058 _private member_ `DataType& Variable;`
- L1059 _private member_ `DataType OldValue;`

#### enum `AutoRTFM::ForTheRuntime::EAutoRTFMEnabledState`  
`enum EAutoRTFMEnabledState`  
_L1113-1138_
- desc: An enum to represent the various ways we want to enable/disable the AutoRTFM runtime. This enum has effective groups of functionality such that if a higher priority group has enabled or disabled the runtime, a lower priority group cannot then override that. We have from higher to lower priority: - Forced Enabled/Disabled - used by CVars when force enabling/disabling AutoRTFM. - Override Enabled/Disabled - override any setting of enabled/disabled as was set by a CVar. - Enabled/Disabled - used by CVars when enabling/disabling AutoRTFM. - Default Enabled/Disabled - whether we should be enabled or disabled by default (used for different backend executables). For example the following would be valid: - At compile time the state is compiled in as default disabled. - The CVar is set to enabled, so we switch the state to enabled. - At runtime we detect a mode where we want AutoRTFM and try to switch the default to enabled, but the CVar already enabled it so this is ignored. - Then for a given codepath we override AutoRTFM to disabled so we switch the state to disabled.
- L1116 _public enumerator_ `AutoRTFM_Disabled = 0` — Disable AutoRTFM.
- L1119 _public enumerator_ `AutoRTFM_Enabled` — Enable AutoRTFM.
- L1122 _public enumerator_ `AutoRTFM_ForcedDisabled` — Force disable AutoRTFM.
- L1125 _public enumerator_ `AutoRTFM_ForcedEnabled` — Force enable AutoRTFM.
- L1128 _public enumerator_ `AutoRTFM_DisabledByDefault` — Whether our default is to be disabled.
- L1131 _public enumerator_ `AutoRTFM_EnabledByDefault` — Whether our default is to be enabled.
- L1134 _public enumerator_ `AutoRTFM_OverriddenDisabled` — Whether we've overridden and AutoRTFM is disabled.
- L1137 _public enumerator_ `AutoRTFM_OverriddenEnabled` — Whether we've overridden and AutoRTFM is enabled.

#### enum `AutoRTFM::ForTheRuntime::EAutoRTFMRetryTransactionState`  
`enum EAutoRTFMRetryTransactionState`  
_L1141-1154_
- desc: An enum to represent whether we should abort and retry transactions (for testing purposes).
- L1144 _public enumerator_ `NoRetry = 0` — Do not abort and retry transactions (the default).
- L1147 _public enumerator_ `RetryNonNested` — Abort and retry non-nested transactions (EG. only abort the parent transactional nest).
- L1153 _public enumerator_ `RetryNestedToo` — Abort and retry nested-transactions too. Will be slower as each nested-transaction will be aborted and retried at least *twice* (once when the non-nested transaction runs the first time, and a second time when the non-nested transaction is doing its retry after aborting).

#### enum `AutoRTFM::ForTheRuntime::EAutoRTFMInternalAbortActionState`  
`enum EAutoRTFMInternalAbortActionState`  
_L1156-1163_
- L1159 _public enumerator_ `Crash = 0` — Crash the process if we hit an internal AutoRTFM abort.
- L1162 _public enumerator_ `Abort` — Just do a normal transaction abort and let the runtime recover (used to test aborting codepaths).

#### struct `AutoRTFM::Private::FOpenHelper`  
`struct FOpenHelper`  
_L1253-1260_
- L1256 _public function_ `template <typename FunctorType> UE_AUTORTFM_FORCEINLINE void operator+(FunctorType&& F)`

#### struct `AutoRTFM::Private::FOpenNoSanitizeHelper`  
`struct FOpenNoSanitizeHelper`  
_L1261-1268_
- L1264 _public function_ `template <typename FunctorType> UE_AUTORTFM_FORCEINLINE void operator+(FunctorType&& F)`

#### struct `AutoRTFM::Private::FCloseHelper`  
`struct FCloseHelper`  
_L1269-1276_
- L1272 _public function_ `template <typename FunctorType> [[nodiscard]] EContextStatus operator+(FunctorType F)`

#### struct `AutoRTFM::Private::FOnPreAbortHelper`  
`struct FOnPreAbortHelper`  
_L1277-1284_
- L1280 _public function_ `template <typename FunctorType> UE_AUTORTFM_FORCEINLINE void operator+(FunctorType&& F)`

#### struct `AutoRTFM::Private::FOnAbortHelper`  
`struct FOnAbortHelper`  
_L1285-1292_
- L1288 _public function_ `template <typename FunctorType> UE_AUTORTFM_FORCEINLINE void operator+(FunctorType&& F)`

#### struct `AutoRTFM::Private::FOnCommitHelper`  
`struct FOnCommitHelper`  
_L1293-1300_
- L1296 _public function_ `template <typename FunctorType> UE_AUTORTFM_FORCEINLINE void operator+(FunctorType&& F)`

#### struct `AutoRTFM::Private::FTransactHelper`  
`struct FTransactHelper`  
_L1301-1308_
- L1304 _public function_ `template <typename FunctorType> UE_AUTORTFM_FORCEINLINE void operator+(FunctorType&& F)`

#### struct `AutoRTFM::Private::__anon97b52c400111::FThreadLocalHelper`  
`struct FThreadLocalHelper`  
_L1311-1319_
- L1314 _public function_ `template <typename Type, int Unique> UE_AUTORTFM_ALWAYS_OPEN static Type& Get()`

#### Free symbols / members of external scopes

- L27 _namespace_ `namespace AutoRTFM`
- L46 _function_ `inline constexpr EWriteFlags operator|(EWriteFlags LHS, EWriteFlags RHS)` (scope `AutoRTFM`) — Bitwise operator | for EWriteFlags
- L51 _function_ `inline constexpr EWriteFlags operator&(EWriteFlags LHS, EWriteFlags RHS)` (scope `AutoRTFM`) — Bitwise operator & for EWriteFlags
- L60 _variable_ `template <typename FuncType, typename... ArgTypes> static constexpr autortfm_mode CallMode = AUTORTFM_MODE_OF_CALL(std::declval<FuncType>()(std::declval<ArgTypes>()...));` (scope `AutoRTFM`) — Evaluates to the AutoRTFM mode of the function overload which would be called when calling FuncType with the arguments of type ArgTypes. Warning: This is an experimental API and may be removed in the future.
- L65 _variable_ `template <typename Type> static constexpr autortfm_mode DestructorMode = AUTORTFM_MODE_OF_CALL(std::declval<Type>().~Type());` (scope `AutoRTFM`) — Evaluates to the AutoRTFM mode of the destructor function of the type Type. Warning: This is an experimental API and may be removed in the future.
- L71 _variable_ `template <typename Type, typename... ArgTypes> static constexpr autortfm_mode ConstructorMode = AUTORTFM_MODE_OF_CALL(::new Type(std::declval<ArgTypes>()...));` (scope `AutoRTFM`) — Evaluates to the AutoRTFM mode of the constructor function of the type Type when called with the arguments of type ArgTypes. Warning: This is an experimental API and may be removed in the future.
- L112 _function_ `inline bool HasAborted(ETransactionResult State)` (scope `AutoRTFM`) — Returns true if the given ETransactionResult represents a transaction that has aborted.
- L157 _function_ `inline bool HasAborted(ETransactionStatus State)` (scope `AutoRTFM`) — Returns true if the given ETransactionStatus represents a transaction that has aborted.
- L176 _function_ `inline bool IsCascading(ETransactionStatus Status)` (scope `AutoRTFM`) — Returns true if Status is AbortedByCascadingAbort or AbortedByCascadingRetry.
- L226 _typedef_ `using TransactionID = autortfm_transaction_id;` (scope `AutoRTFM`) — An opaque unique identifier for a transaction.
- L230 _macro_ `#define AUTORTFM_SANITIZER_INTERNAL [[clang::autortfm(autortfm_mode_internal)]]`
- L233 _namespace_ `namespace Sanitizer` (scope `AutoRTFM`)
- L252 _prototype_ `AUTORTFM_SANITIZER_INTERNAL EMode GetMode();` (scope `AutoRTFM::Sanitizer`) — Returns the global AutoRTFM sanitizer mode currently in use.
- L255 _prototype_ `AUTORTFM_SANITIZER_INTERNAL void SetMode(EMode Mode);` (scope `AutoRTFM::Sanitizer`) — Sets the global AutoRTFM sanitizer mode.
- L258 _prototype_ `AUTORTFM_SANITIZER_INTERNAL bool RecordClosedWriteCallstacks();` (scope `AutoRTFM::Sanitizer`) — Returns true if the AutoRTFM sanitizer records the callstack of closed writes.
- L261 _prototype_ `AUTORTFM_SANITIZER_INTERNAL void SetRecordClosedWriteCallstacks(bool bEnable);` (scope `AutoRTFM::Sanitizer`) — Sets whether the AutoRTFM sanitizer records the callstack of closed writes.
- L264 _typedef_ `using FDisableHandle = void*;` (scope `AutoRTFM::Sanitizer`) — Opaque handle returned by BeginDisable()
- L272 _prototype_ `AUTORTFM_SANITIZER_INTERNAL FDisableHandle BeginDisable();` (scope `AutoRTFM::Sanitizer`) — Temporarily disables the AutoRTFM sanitizer for the current transaction and any child transactions. Must be paired with a call to EndDisable(). Calls to BeginDisable() are internally counted and may be nested within other BeginDisable() / EndDisable() calls. This call is a no-op when called outside of a transaction.
- L277 _prototype_ `AUTORTFM_SANITIZER_INTERNAL void EndDisable(FDisableHandle);` (scope `AutoRTFM::Sanitizer`) — Ends temporarily disabling the AutoRTFM sanitizer. DisableHandle must be a handle returned by BeginDisable(). See BeginDisable().
- L282 _prototype_ `AUTORTFM_SANITIZER_INTERNAL bool AnyTransactionsInFlight();` (scope `AutoRTFM::Sanitizer`) — Returns true if there are any AutoRTFM transactions in flight. Can be safely called from any thread, although the result will be non-deterministic without synchronization between threads.
- L304 _macro_ `#define AUTORTFM_SANITIZER_DISABLE_SCOPE() \`
- L309 _macro_ `#define AUTORTFM_SANITIZER_DISABLE_SCOPE() static_assert(true) /* require semicolon */`
- L314 _namespace_ `namespace ForTheRuntime` (scope `AutoRTFM`)
- L316 _prototype_ `void OnCommitInternal(TTask<void()>&& Work);` (scope `AutoRTFM::ForTheRuntime`)
- L317 _prototype_ `void OnPreAbortInternal(TTask<void()>&& Work);` (scope `AutoRTFM::ForTheRuntime`)
- L318 _prototype_ `void OnAbortInternal(TTask<void()>&& Work);` (scope `AutoRTFM::ForTheRuntime`)
- L319 _prototype_ `void OnCompleteInternal(TTask<void()>&& Work);` (scope `AutoRTFM::ForTheRuntime`)
- L320 _prototype_ `void OnRetryInternal(TTask<void()>&& Work);` (scope `AutoRTFM::ForTheRuntime`)
- L321 _prototype_ `void PushOnCommitHandlerInternal(const void* Key, TTask<void()>&& Work);` (scope `AutoRTFM::ForTheRuntime`)
- L322 _prototype_ `void PopOnCommitHandlerInternal(const void* Key);` (scope `AutoRTFM::ForTheRuntime`)
- L323 _prototype_ `void PopAllOnCommitHandlersInternal(const void* Key);` (scope `AutoRTFM::ForTheRuntime`)
- L324 _prototype_ `void PushOnAbortHandlerInternal(const void* Key, TTask<void()>&& Work);` (scope `AutoRTFM::ForTheRuntime`)
- L325 _prototype_ `void PopOnAbortHandlerInternal(const void* Key);` (scope `AutoRTFM::ForTheRuntime`)
- L326 _prototype_ `void PopAllOnAbortHandlersInternal(const void* Key);` (scope `AutoRTFM::ForTheRuntime`)
- L327 _prototype_ `void RegisterOnCommitFromTheOpen(TTask<void()>&& Work);` (scope `AutoRTFM::ForTheRuntime`)
- L328 _prototype_ `void RegisterOnAbortFromTheOpen(TTask<void()>&& Work);` (scope `AutoRTFM::ForTheRuntime`)
- L329 _prototype_ `void RedirectedLoad( uint32_t AddressSpace, void* DestPointer, uint64_t Size, uint64_t SourceAddress, bool bWillWriteHint);` (scope `AutoRTFM::ForTheRuntime`)
- L331 _prototype_ `void RedirectedLoad8(uint32_t AddressSpace, void* DestPointer, uint64_t SourceAddress, bool bWillWriteHint);` (scope `AutoRTFM::ForTheRuntime`)
- L332 _prototype_ `void RedirectedLoad4(uint32_t AddressSpace, void* DestPointer, uint64_t SourceAddress, bool bWillWriteHint);` (scope `AutoRTFM::ForTheRuntime`)
- L333 _prototype_ `void RedirectedLoad2(uint32_t AddressSpace, void* DestPointer, uint64_t SourceAddress, bool bWillWriteHint);` (scope `AutoRTFM::ForTheRuntime`)
- L334 _prototype_ `void RedirectedLoad1(uint32_t AddressSpace, void* DestPointer, uint64_t SourceAddress, bool bWillWriteHint);` (scope `AutoRTFM::ForTheRuntime`)
- L335 _prototype_ `void RedirectedStore(uint32_t AddressSpace, uint64_t DestAddress, uint64_t Size, const void* SourcePointer);` (scope `AutoRTFM::ForTheRuntime`)
- L336 _prototype_ `void RedirectedStore8(uint32_t AddressSpace, uint64_t DestAddress, const void* SourcePointer);` (scope `AutoRTFM::ForTheRuntime`)
- L337 _prototype_ `void RedirectedStore4(uint32_t AddressSpace, uint64_t DestAddress, const void* SourcePointer);` (scope `AutoRTFM::ForTheRuntime`)
- L338 _prototype_ `void RedirectedStore2(uint32_t AddressSpace, uint64_t DestAddress, const void* SourcePointer);` (scope `AutoRTFM::ForTheRuntime`)
- L339 _prototype_ `void RedirectedStore1(uint32_t AddressSpace, uint64_t DestAddress, const void* SourcePointer);` (scope `AutoRTFM::ForTheRuntime`)
- L344 _function_ `template <typename FunctorType> void AutoRTFMFunctorInvoker(void* Arg)` (scope `AutoRTFM`)
- L351 _function_ `template <typename FunctorType> auto AutoRTFMLookupInstrumentedFunctorInvoker(const FunctorType& Functor) -> void (*)(void*)` (scope `AutoRTFM`)
- L369 _typedef_ `using FExternAPI = autortfm_extern_api;` (scope `AutoRTFM`)
- L374 _prototype_ `void Initialize(const FExternAPI& ExternAPI);` (scope `AutoRTFM`)
- L376 _function_ `UE_AUTORTFM_CRITICAL_INLINE void Initialize(const FExternAPI& ExternAPI)` (scope `AutoRTFM`)
- L385 _prototype_ `void Shutdown();` (scope `AutoRTFM`)
- L387 _function_ `UE_AUTORTFM_CRITICAL_INLINE void Shutdown()` (scope `AutoRTFM`)
- L394 _function_ `UE_AUTORTFM_CRITICAL_INLINE_ALWAYS bool IsClosed()` (scope `AutoRTFM`) — Tells if we are currently running in the closed nest of a transaction. By default, transactional code is in a closed nest; the only way to be in an open nest is to request it via `Open`. This function is handled specially in the compiler and will be constant folded as true in closed code, and false in open code.
- L402 _function_ `UE_AUTORTFM_CRITICAL_INLINE EContextStatus ContextStatus()` (scope `AutoRTFM`) — Returns the current AutoRTFM context status. Note: autortfm_get_context_status() is handled specially in the compiler and will be constant folded as EContextStatus::OnTrack when called in the closed.
- L410 _function_ `UE_AUTORTFM_CRITICAL_INLINE_ALWAYS bool IsTransactional()` (scope `AutoRTFM`) — Returns true if we are currently running in a transaction, and outside of an on-commit, on-abort, on-retry or on-complete handler. This will constant folded by the compiler to true when called in the closed.
- L417 _function_ `UE_AUTORTFM_CRITICAL_INLINE_ALWAYS bool IsIdle()` (scope `AutoRTFM`) — Returns true if we are currently outside of transactional code - i.e. the transaction stack is empty, or called from a non-transactional thread.
- L424 _function_ `UE_AUTORTFM_CRITICAL_INLINE_ALWAYS bool IsCommitting()` (scope `AutoRTFM`) — Returns true if we are currently committing a transaction. This will return true when inside an on-commit handler.
- L431 _function_ `UE_AUTORTFM_CRITICAL_INLINE_ALWAYS bool IsAborting()` (scope `AutoRTFM`) — Returns true if we are currently aborting a transaction. This will return true when inside an on-abort handler.
- L438 _function_ `UE_AUTORTFM_CRITICAL_INLINE_ALWAYS bool IsRetrying()` (scope `AutoRTFM`) — Returns true if we are currently retrying a transaction. This will return true when inside an on-retry handler.
- L446 _function_ `UE_AUTORTFM_CRITICAL_INLINE_ALWAYS bool IsCommittingOrAborting()` (scope `AutoRTFM`) — Returns true when inside an on-abort, on-commit, on-complete, on-retry handler, unwinding from a cascading abort / cascading retry, or inside a static initializer. TODO(SOL-8967): This function name is misleading. Rename to something sensible.
- L467 _function_ `UE_AUTORTFM_CRITICAL_INLINE bool IsOnCurrentTransactionStack(void* Ptr)` (scope `AutoRTFM`) — Returns true if the passed-in pointer is on the stack of the currently-executing transaction. This is occasionally necessary when writing OnAbort handlers for objects on the stack, since we don't want to scribble on stack memory that might have been reused.
- L473 _function_ `UE_AUTORTFM_CRITICAL_INLINE TransactionID CurrentTransactionID()` (scope `AutoRTFM`) — Returns an opaque identifier for the current transaction.
- L487 _function_ `template <typename FunctorType> UE_AUTORTFM_CRITICAL_INLINE ETransactionResult Transact(AUTORTFM_IMPLICIT_ENABLE const FunctorType& Functor)` (scope `AutoRTFM`) — Run the functor in a transaction. Memory writes and other side effects get instrumented and will be reversed if the transaction aborts. If this begins a nested transaction, the instrumented effects are logged onto the root transaction, so the effects can be reversed later if the root transaction aborts, even if this nested transaction succeeds. If AutoRTFM is disabled, the code will be ran non-transactionally.
- L505 _function_ `template <typename FunctorType> UE_AUTORTFM_CRITICAL_INLINE ETransactionResult TransactThenOpen(const FunctorType& Functor)` (scope `AutoRTFM`) — This is just like calling Transact([&] { Open([&] { Functor(); }); }); The reason we expose it is that it allows the caller's module to not be compiled with the AutoRTFM instrumentation of functions if the only thing that's being invoked is a function in the open.
- L519 _function_ `UE_AUTORTFM_CRITICAL_INLINE void AbortTransaction()` (scope `AutoRTFM`) — Immediately aborts and pop the top-most transaction, discarding all effects. When called from the closed, control will jump to end of the next outer Transact() or Close(). When called from the open, execution will continue until the next open -> closed transition, upon which, control will immediately jump to end of the next outer Transact() or Close().
- L532 _function_ `UE_AUTORTFM_CRITICAL_INLINE void CascadingAbortTransaction()` (scope `AutoRTFM`) — Immediately aborts and pops all transactions, discarding all effects. When called from the closed, control will jump to end of the next outer Transact() or Close(). When called from the open, execution will continue until the next open -> closed transition, upon which, control will immediately jump to end of the next outer Transact() or Close(). This process will repeat until the the outermost transaction is reached, upon which all registered on-complete callbacks will be invoked.
- L547 _function_ `UE_AUTORTFM_CRITICAL_INLINE void CascadingRetryTransaction()` (scope `AutoRTFM`) — Immediately aborts and pops all transactions, discarding all effects, then retries the outermost transaction. When called from the closed, control will jump to end of the next outer Transact() or Close(). When called from the open, execution will continue until the next open -> closed transition, upon which, control will immediately jump to end of the next outer Transact() or Close(). This process will repeat until the the outermost transaction is reached, upon which all registered on-retry callbacks will be invoked, then the outermost transaction will be restarted.
- L556 _function_ `AUTORTFM_DISABLE UE_AUTORTFM_CRITICAL_INLINE void StartTransaction()` (scope `AutoRTFM`) — Manually create a new transaction from open code and push it as a transaction nest. Can only be called within an already active parent transaction (EG. this cannot start a transaction nest itself). Can only be called from the open.
- L565 _function_ `AUTORTFM_DISABLE UE_AUTORTFM_CRITICAL_INLINE void CommitTransaction()` (scope `AutoRTFM`) — Manually commit the top transaction nest, popping it from the execution scope. Can only be called within an already active parent transaction (EG. this cannot end a transaction nest itself). Can only be called from the open.
- L585 _function_ `UE_AUTORTFM_CRITICAL_INLINE ReturnType Open(const FunctorType& Functor)` (scope `AutoRTFM`)
- L595 _macro_ `#define AUTORTFM_INTERNAL_CALL_IN_OPEN(Arg, Function) \` — Macro filth to either call autortfm_open() or autortfm_open_no_sanitize() depending on Flags. Cannot be done as a lambda or inner class method as any call indirection will break compiler optimizations.
- L713 _function_ `template <typename FunctorType> [[nodiscard]] UE_AUTORTFM_CRITICAL_INLINE ETransactionStatus Close(AUTORTFM_IMPLICIT_ENABLE const FunctorType& Functor)` (scope `AutoRTFM`) — Always executes the given code transactionally when called from a transaction nest (whether we are in open or closed code). Will crash if called outside of a transaction nest. If Close() returns an aborting status (see IsStatusAborting()), then attempting to use the transaction is undefined behaviour. The caller should return to the closed as quickly as possible to avoid the risk of the transaction being used in its rolled-back state.
- L728 _function_ `template <typename FunctorType> [[nodiscard]] UE_AUTORTFM_CRITICAL_INLINE ETransactionStatus CloseIfTransactional(AUTORTFM_IMPLICIT_ENABLE FunctorType&& Functor)` (scope `AutoRTFM`) — Similar to Close(), but can be called from outside of a transaction. If called from outside a transaction then CloseIfTransactional() will call Functor and always return ETransactionStatus::Executing.
- L753 _function_ `template <typename FunctorType> UE_AUTORTFM_CRITICAL_INLINE void OnCommit(AUTORTFM_IMPLICIT_DISABLE FunctorType&& Work)` (scope `AutoRTFM`) — Have some work happen when this transaction commits. In a nested transaction, the work is deferred until the outermost nest is committed; at that point, the worklist is run in FIFO order. If this is called outside a transaction or from an open nest, then the work happens immediately.
- L766 _function_ `template <typename FunctorType> UE_AUTORTFM_CRITICAL_INLINE void OnCommit(FunctorType&& Work)` (scope `AutoRTFM`)
- L777 _function_ `template <typename FunctorType> UE_AUTORTFM_CRITICAL_INLINE void OnPreAbort(AUTORTFM_IMPLICIT_DISABLE FunctorType&& Work)` (scope `AutoRTFM`) — Have some work happen when this transaction aborts (before memory rollback). If an abort occurs, the work list is run in LIFO order. If this is called outside a transaction or from an open nest then the work is ignored.
- L786 _function_ `template <typename FunctorType> UE_AUTORTFM_CRITICAL_INLINE void OnPreAbort(FunctorType&&)` (scope `AutoRTFM`)
- L796 _function_ `template <typename FunctorType> UE_AUTORTFM_CRITICAL_INLINE void OnAbort(AUTORTFM_IMPLICIT_DISABLE FunctorType&& Work)` (scope `AutoRTFM`) — Have some work happen when this transaction aborts (after memory rollback). If an abort occurs, the work list is run in LIFO order. If this is called outside a transaction or from an open nest then the work is ignored.
- L805 _function_ `template <typename FunctorType> UE_AUTORTFM_CRITICAL_INLINE void OnAbort(FunctorType&&)` (scope `AutoRTFM`)
- L817 _function_ `template <typename FunctorType> UE_AUTORTFM_CRITICAL_INLINE void OnComplete(AUTORTFM_IMPLICIT_DISABLE FunctorType&& Work)` (scope `AutoRTFM`) — Enqueues a task to run after the outermost transaction commits or aborts, after all other OnCommit() or OnAbort() tasks are run, and after any retries of the outermost transaction. The worklist is run in FIFO order. If this is called outside a transaction or from an open nest, then the work is ignored.
- L826 _function_ `template <typename FunctorType> UE_AUTORTFM_CRITICAL_INLINE void OnComplete(FunctorType&&)` (scope `AutoRTFM`)
- L837 _function_ `template <typename FunctorType> UE_AUTORTFM_CRITICAL_INLINE void OnRetry(AUTORTFM_IMPLICIT_DISABLE FunctorType&& Work)` (scope `AutoRTFM`) — Enqueues a task to run after the outermost transaction retries due to CascadingRetryTransaction(), after all other OnAbort() tasks are run. The worklist is run in FIFO order. If this is called outside a transaction or from an open nest, then the work is ignored.
- L846 _function_ `template <typename FunctorType> UE_AUTORTFM_CRITICAL_INLINE void OnRetry(FunctorType&&)` (scope `AutoRTFM`)
- L857 _function_ `template <typename FunctorType> UE_AUTORTFM_CRITICAL_INLINE void PushOnCommitHandler(const void* Key, AUTORTFM_IMPLICIT_DISABLE FunctorType&& Work)` (scope `AutoRTFM`) — Register a handler for transaction commit. Takes a key parameter so that the handler can be unregistered (see `PopOnCommitHandler`). This is useful for scoped mutations that need an abort handler present unless execution reaches the end of the relevant scope.
- L870 _function_ `template <typename FunctorType> UE_AUTORTFM_CRITICAL_INLINE void PushOnCommitHandler(const void*, AUTORTFM_IMPLICIT_DISABLE FunctorType&&)` (scope `AutoRTFM`) — Register a handler for transaction commit. Takes a key parameter so that the handler can be unregistered (see `PopOnCommitHandler`). This is useful for scoped mutations that need an abort handler present unless execution reaches the end of the relevant scope.
- L877 _function_ `UE_AUTORTFM_CRITICAL_INLINE void PopOnCommitHandler(const void* Key)` (scope `AutoRTFM`) — Unregister the most recently pushed handler (via `PushOnCommitHandler`) for the given key.
- L886 _function_ `UE_AUTORTFM_CRITICAL_INLINE void PopOnCommitHandler(const void*)` (scope `AutoRTFM`) — Unregister the most recently pushed handler (via `PushOnCommitHandler`) for the given key.
- L891 _function_ `UE_AUTORTFM_CRITICAL_INLINE void PopAllOnCommitHandlers(const void* Key)` (scope `AutoRTFM`) — Unregister all pushed handlers (via `PushOnCommitHandler`) for the given key.
- L900 _function_ `UE_AUTORTFM_CRITICAL_INLINE void PopAllOnCommitHandlers(const void*)` (scope `AutoRTFM`) — Unregister all pushed handlers (via `PushOnCommitHandler`) for the given key.
- L909 _function_ `template <typename FunctorType> UE_AUTORTFM_CRITICAL_INLINE void PushOnAbortHandler(const void* Key, AUTORTFM_IMPLICIT_DISABLE FunctorType&& Work)` (scope `AutoRTFM`) — Register a handler for transaction abort. Takes a key parameter so that the handler can be unregistered (see `PopOnAbortHandler`). This is useful for scoped mutations that need an abort handler present unless execution reaches the end of the relevant scope.
- L922 _function_ `template <typename FunctorType> UE_AUTORTFM_CRITICAL_INLINE void PushOnAbortHandler(const void* Key, FunctorType&&)` (scope `AutoRTFM`) — Register a handler for transaction abort. Takes a key parameter so that the handler can be unregistered (see `PopOnAbortHandler`). This is useful for scoped mutations that need an abort handler present unless execution reaches the end of the relevant scope.
- L929 _function_ `UE_AUTORTFM_CRITICAL_INLINE void PopOnAbortHandler(const void* Key)` (scope `AutoRTFM`) — Unregister the most recently pushed handler (via `PushOnAbortHandler`) for the given key.
- L946 _function_ `UE_AUTORTFM_CRITICAL_INLINE void PopAllOnAbortHandlers(const void* Key)` (scope `AutoRTFM`) — Unregister all pushed handlers (via `PushOnAbortHandler`) for the given key.
- L977 _prototype_ `void RegisterHeapRedirectCallbacks(FHeapRedirectCallbacks Callbacks);` (scope `AutoRTFM`)
- L979 _function_ `UE_AUTORTFM_CRITICAL_INLINE void RegisterHeapRedirectCallbacks(FHeapRedirectCallbacks )` (scope `AutoRTFM`)
- L988 _function_ `UE_AUTORTFM_CRITICAL_INLINE void* DidAllocate(void* Ptr, size_t Size)` (scope `AutoRTFM`) — Inform the runtime that we have performed a new object allocation. It's only necessary to call this inside of custom malloc implementations. As an optimization, you can choose to then only have your malloc return the pointer returned by this function. It's guaranteed to be equal to the pointer you passed, but it's blessed specially from the compiler's perspective, leading to some nice optimizations. This does nothing when called from open code.
- L994 _function_ `UE_AUTORTFM_CRITICAL_INLINE void DidFree(void* Ptr)` (scope `AutoRTFM`) — Inform the runtime that we have free'd a given memory location.
- L1004 _function_ `UE_AUTORTFM_CRITICAL_INLINE void RecordOpenWrite(void* Ptr, size_t Size, EWriteFlags Flags = EWriteFlags::Default)` (scope `AutoRTFM`) — Informs the runtime that a block of memory is about to be overwritten in the open. During a transaction, this allows the runtime to copy the data in preparation for a possible abort. Normally, tracking memory overwrites should be automatically handled by AutoRTFM, but manual overwrite tracking may be required for third-party libraries or outside compilers (such as ISPC).
- L1015 _function_ `template <typename Type> UE_AUTORTFM_CRITICAL_INLINE void RecordOpenWrite(Type* Ptr, EWriteFlags Flags = EWriteFlags::Default)` (scope `AutoRTFM`) — Informs the runtime that a block of memory is about to be overwritten in the open. During a transaction, this allows the runtime to copy the data in preparation for a possible abort. Normally, tracking memory overwrites should be automatically handled by AutoRTFM, but manual overwrite tracking may be required for third-party libraries or outside compilers (such as ISPC).
- L1024 _function_ `template <typename RefType, typename ValueType> AUTORTFM_OPEN_NO_SANITIZE void Assign(RefType& Ref, ValueType&& NewValue, EWriteFlags Flags = EWriteFlags::Default)` (scope `AutoRTFM`)
- L1034 _function_ `template <typename RefType, typename ValueType> UE_AUTORTFM_CRITICAL_INLINE void Assign(RefType& Ref, ValueType&& NewValue, EWriteFlags Flags = EWriteFlags::Default)` (scope `AutoRTFM`)
- L1065 _function_ `[[noreturn]] UE_AUTORTFM_CRITICAL_INLINE_ALWAYS void Unreachable(const char* Message = nullptr)` (scope `AutoRTFM`)
- L1070 _function_ `UE_AUTORTFM_CRITICAL_INLINE void Unreachable(const char* Message = nullptr)` (scope `AutoRTFM`)
- L1077 _function_ `UE_AUTORTFM_CRITICAL_INLINE_ALWAYS void UnreachableIfTransactional(const char* Message = nullptr)` (scope `AutoRTFM`) — If we are running within a transaction, call `AutoRTFM::Unreachable`.
- L1086 _function_ `UE_AUTORTFM_CRITICAL_INLINE_ALWAYS void UnreachableIfClosed(const char* Message = nullptr)` (scope `AutoRTFM`) — If we are running within a closed transaction, call `AutoRTFM::Unreachable`.
- L1095 _namespace_ `namespace ForTheRuntime` (scope `AutoRTFM`)
- L1167 _prototype_ `bool SetAutoRTFMRuntime(EAutoRTFMEnabledState State);` (scope `AutoRTFM::ForTheRuntime`) — Set whether the AutoRTFM runtime is enabled or disabled. Returns true when the state was changed successfully.
- L1169 _prototype_ `bool IsAutoRTFMRuntimeEnabledInternal();` (scope `AutoRTFM::ForTheRuntime`)
- L1172 _function_ `UE_AUTORTFM_CRITICAL_INLINE bool IsAutoRTFMRuntimeEnabled()` (scope `AutoRTFM::ForTheRuntime`) — Query whether the AutoRTFM runtime is enabled.
- L1186 _prototype_ `void SetAutoRTFMEnabledProbability(float Chance);` (scope `AutoRTFM::ForTheRuntime`) — Set the percentage [0..100] chance that a call to `CoinTossDisable` will end up disabling AutoRTFM. 100% means never disable via coin-toss, 0% means always disable. So passing `0.1` means disable all but 1/1000's calls via `CoinTossDisable`.
- L1189 _prototype_ `float GetAutoRTFMEnabledProbability();` (scope `AutoRTFM::ForTheRuntime`) — Get the enabled probability set via `SetAutoRTFMEnabledProbability`.
- L1193 _prototype_ `bool CoinTossDisable();` (scope `AutoRTFM::ForTheRuntime`) — Call to randomly disable AutoRTFM with a probability set with `SetAutoRTFMEnabledProbability`. Returns true if AutoRTFM was disabled by this call.
- L1195 _prototype_ `void SetInternalAbortAction(EAutoRTFMInternalAbortActionState State);` (scope `AutoRTFM::ForTheRuntime`)
- L1197 _prototype_ `EAutoRTFMInternalAbortActionState GetInternalAbortAction();` (scope `AutoRTFM::ForTheRuntime`)
- L1199 _prototype_ `bool GetEnsureOnInternalAbort();` (scope `AutoRTFM::ForTheRuntime`)
- L1200 _prototype_ `void SetEnsureOnInternalAbort(bool bEnabled);` (scope `AutoRTFM::ForTheRuntime`)
- L1202 _prototype_ `autortfm_log_severity GetAutoRTFMHazardLogSeverity();` (scope `AutoRTFM::ForTheRuntime`)
- L1203 _prototype_ `void SetAutoRTFMHazardLogSeverity(autortfm_log_severity Severity);` (scope `AutoRTFM::ForTheRuntime`)
- L1206 _function_ `[[deprecated("Use 'SetEnsureOnInternalAbort' instead!")]] inline void SetEnsureOnAbortByLanguage(bool bEnabled)` (scope `AutoRTFM::ForTheRuntime`) — Set whether we should trigger an ensure on an abort-by-language.
- L1212 _function_ `[[deprecated("Use 'GetEnsureOnInternalAbort' instead!")]] inline bool IsEnsureOnAbortByLanguageEnabled()` (scope `AutoRTFM::ForTheRuntime`) — Returns whether the runtime will trigger an ensure on an abort-by-language, or not.
- L1218 _function_ `[[deprecated("Use 'GetInternalAbortAction' instead!")]] inline bool IsAutoRTFMAssertOnError()` (scope `AutoRTFM::ForTheRuntime`) — Returns whether we want to assert or ensure on a Language Error
- L1224 _prototype_ `void SetRetryTransaction(EAutoRTFMRetryTransactionState State);` (scope `AutoRTFM::ForTheRuntime`) — Set whether we should retry transactions.
- L1227 _prototype_ `EAutoRTFMRetryTransactionState GetRetryTransaction();` (scope `AutoRTFM::ForTheRuntime`) — Returns whether we should retry transactions.
- L1230 _prototype_ `bool ShouldRetryNonNestedTransactions();` (scope `AutoRTFM::ForTheRuntime`) — Returns true if we should retry non-nested transactions.
- L1233 _prototype_ `bool ShouldRetryNestedTransactionsToo();` (scope `AutoRTFM::ForTheRuntime`) — Returns true if we should also retry nested transactions.
- L1236 _function_ `UE_AUTORTFM_CRITICAL_INLINE void RecordOpenRead(void const*, size_t)` (scope `AutoRTFM::ForTheRuntime`) — Reserved for future.
- L1240 _function_ `template <typename Type> UE_AUTORTFM_CRITICAL_INLINE void RecordOpenRead(Type*)` (scope `AutoRTFM::ForTheRuntime`) — Reserved for future.
- L1251 _namespace_ `namespace AutoRTFM`
- L1251 _namespace_ `namespace Private` (scope `AutoRTFM`)
- L1310 _namespace_ `namespace (anonymous)` (scope `AutoRTFM::Private`)
- L1323 _macro_ `#define UE_AUTORTFM_DECLARE_THREAD_LOCAL_VAR_IMPL(Type, Name) \`
- L1326 _macro_ `#define UE_AUTORTFM_OPEN_IMPL ::AutoRTFM::Private::FOpenHelper{} + [&] AUTORTFM_DISABLE()`
- L1327 _macro_ `#define UE_AUTORTFM_OPEN_NO_SANITIZE_IMPL ::AutoRTFM::Private::FOpenNoSanitizeHelper{} + [&] AUTORTFM_DISABLE_NO_SANITIZE()`
- L1328 _macro_ `#define UE_AUTORTFM_CLOSE_IMPL ::AutoRTFM::Private::FCloseHelper{} + [&] AUTORTFM_ENABLE()`
- L1329 _macro_ `#define UE_AUTORTFM_ONPREABORT_IMPL(...) ::AutoRTFM::Private::FOnPreAbortHelper{} + [__VA_ARGS__] AUTORTFM_DISABLE() mutable`
- L1330 _macro_ `#define UE_AUTORTFM_ONABORT_IMPL(...) ::AutoRTFM::Private::FOnAbortHelper{} + [__VA_ARGS__] AUTORTFM_DISABLE() mutable`
- L1331 _macro_ `#define UE_AUTORTFM_ONCOMMIT_IMPL(...) ::AutoRTFM::Private::FOnCommitHelper{} + [__VA_ARGS__] AUTORTFM_DISABLE() mutable`
- L1332 _macro_ `#define UE_AUTORTFM_TRANSACT_IMPL ::AutoRTFM::Private::FTransactHelper{} + [&] AUTORTFM_ENABLE()`
- L1336 _macro_ `#define UE_AUTORTFM_DECLARE_THREAD_LOCAL_VAR_IMPL(Type, Name) thread_local Type Name` — Do nothing, these should be followed by blocks that should be either executed or not executed
- L1337 _macro_ `#define UE_AUTORTFM_OPEN_IMPL`
- L1338 _macro_ `#define UE_AUTORTFM_OPEN_NO_SANITIZE_IMPL`
- L1339 _macro_ `#define UE_AUTORTFM_CLOSE_IMPL`
- L1340 _macro_ `#define UE_AUTORTFM_ONPREABORT_IMPL(...) (void)[__VA_ARGS__]() mutable`
- L1341 _macro_ `#define UE_AUTORTFM_ONABORT_IMPL(...) (void)[__VA_ARGS__]() mutable`
- L1342 _macro_ `#define UE_AUTORTFM_ONCOMMIT_IMPL(...)`
- L1343 _macro_ `#define UE_AUTORTFM_TRANSACT_IMPL`
- L1350 _macro_ `#define UE_AUTORTFM_DECLARE_THREAD_LOCAL_VAR(Type, Name) UE_AUTORTFM_DECLARE_THREAD_LOCAL_VAR_IMPL(Type, Name)` — Declares an AutoRTFM-aware thread local variable. `thread_local` variables are not yet natively supported (#jira SOL-7684) This macro must be used inside a function, and will not work properly at global scope. Calls should be written like this: UE_AUTORTFM_DECLARE_THREAD_LOCAL_VAR(FString, MyThreadLocalString); MyThreadLocalString = TEXT("Hello");
- L1354 _macro_ `#define UE_AUTORTFM_OPEN UE_AUTORTFM_OPEN_IMPL` — Runs a block of code in the open, non-transactionally. Anything performed in the open will not be undone if a transaction fails. Calls should be written like this: UE_AUTORTFM_OPEN { ... code ... };
- L1357 _macro_ `#define UE_AUTORTFM_OPEN_NO_VALIDATION UE_AUTORTFM_OPEN_NO_SANITIZE_IMPL` — Deprecated: Use UE_AUTORTFM_OPEN_NO_SANITIZE
- L1361 _macro_ `#define UE_AUTORTFM_OPEN_NO_SANITIZE UE_AUTORTFM_OPEN_NO_SANITIZE_IMPL` — Similar to UE_AUTORTFM_OPEN, but the AutoRTFM sanitizer will be disabled for the scope of the call.
- L1365 _macro_ `#define UE_AUTORTFM_CLOSE UE_AUTORTFM_CLOSE_IMPL` — Runs a block of code in the closed, transactionally. Anything performed in the closed will be undone if a transaction fails. Calls should be written like this: UE_AUTORTFM_CLOSE { ... code ... };
- L1371 _macro_ `#define UE_AUTORTFM_ONPREABORT(...) UE_AUTORTFM_ONPREABORT_IMPL(__VA_ARGS__)` — Runs a block of code if a transaction aborts (before memory rollback). In non-transactional code paths the block of code will not be executed at all. The macro arguments are the capture specification for the lambda. Calls should be written like this: UE_AUTORTFM_ONPREABORT(=) { ... code ... };
- L1377 _macro_ `#define UE_AUTORTFM_ONABORT(...) UE_AUTORTFM_ONABORT_IMPL(__VA_ARGS__)` — Runs a block of code if a transaction aborts (after memory rollback). In non-transactional code paths the block of code will not be executed at all. The macro arguments are the capture specification for the lambda. Calls should be written like this: UE_AUTORTFM_ONABORT(=) { ... code ... };
- L1383 _macro_ `#define UE_AUTORTFM_ONCOMMIT(...) UE_AUTORTFM_ONCOMMIT_IMPL(__VA_ARGS__)` — Runs a block of code if a transaction commits successfully. In non-transactional code paths the block of code will be executed immediately. The macro arguments are the capture specification for the lambda. Calls should be written like this: UE_AUTORTFM_ONCOMMIT(=) { ... code ... };
- L1387 _macro_ `#define UE_AUTORTFM_TRANSACT UE_AUTORTFM_TRANSACT_IMPL` — Runs a block of code in the closed, transactionally, within a new transaction. Calls should be written like this: UE_AUTORTFM_TRANSACT { ... code ... };
- L1390 _macro_ `#define UE_AUTORTFM_REGISTER_OPEN_TO_CLOSED_FUNCTIONS(...) \`
- L1394 _macro_ `#define UE_AUTORTFM_REGISTER_OPEN_TO_CLOSED_FUNCTIONS(...)`

### `Source/Runtime/AutoRTFM/Public/AutoRTFM/CAPI.h` (Public)


#### enum `(anonymous)`  
``  
_L47-59_

#### enum `(anonymous)`  
``  
_L63-69_

#### enum `(anonymous)`  
``  
_L73-85_

#### struct `(anonymous)`  
``  
_L95-179_

#### struct `autortfm_open_to_closed_mapping`  
`struct autortfm_open_to_closed_mapping`  
_L375-379_
- desc: autortfm_open_to_closed_mapping maps an open function to its closed variant.
- L377 _public member_ `void* Open;`
- L378 _public member_ `void* Closed;`

#### struct `autortfm_open_to_closed_table`  
`struct autortfm_open_to_closed_table`  
_L384-394_
- desc: autortfm_open_to_closed_table holds a pointer to a null-terminated list of autortfm_open_to_closed_mapping, and an intrusive linked-list pointer to the previous and next registered autortfm_open_to_closed_table.
- L387 _public member_ `const struct autortfm_open_to_closed_mapping* Mappings;` — Null-terminated open function to closed function mapping table.
- L390 _public member_ `struct autortfm_open_to_closed_table* Prev;` — An intrusive linked-list pointer to the previous autortfm_open_to_closed_table. Used by autortfm_register_open_to_closed_functions().
- L393 _public member_ `struct autortfm_open_to_closed_table* Next;` — An intrusive linked-list pointer to the next autortfm_open_to_closed_table. Used by autortfm_register_open_to_closed_functions().

#### Free symbols / members of external scopes

- L18 _macro_ `#define UE_AUTORTFM_API AUTORTFM_API`
- L21 _macro_ `#define UE_AUTORTFM_API`
- L48 _enumerator_ `autortfm_transaction_executing = 0` (scope `__anone48b85ac0103`)
- L49 _enumerator_ `autortfm_transaction_committed` (scope `__anone48b85ac0103`)
- L50 _enumerator_ `autortfm_transaction_aborted_by_request` (scope `__anone48b85ac0103`)
- L51 _enumerator_ `autortfm_transaction_aborted_by_language` (scope `__anone48b85ac0103`)
- L52 _enumerator_ `autortfm_transaction_rejected_during_unwind` (scope `__anone48b85ac0103`)
- L53 _enumerator_ `autortfm_transaction_rejected_during_commit` (scope `__anone48b85ac0103`)
- L54 _enumerator_ `autortfm_transaction_rejected_during_abort` (scope `__anone48b85ac0103`)
- L55 _enumerator_ `autortfm_transaction_rejected_during_retry` (scope `__anone48b85ac0103`)
- L56 _enumerator_ `autortfm_transaction_rejected_during_complete` (scope `__anone48b85ac0103`)
- L57 _enumerator_ `autortfm_transaction_aborted_by_cascading_abort` (scope `__anone48b85ac0103`)
- L58 _enumerator_ `autortfm_transaction_aborted_by_cascading_retry` (scope `__anone48b85ac0103`)
- L59 _typedef_ `autortfm_transaction_rejected_during_complete, autortfm_transaction_aborted_by_cascading_abort, autortfm_transaction_aborted_by_cascading_retry, } autortfm_transaction_status;`
- L64 _enumerator_ `autortfm_log_verbose = 0` (scope `__anone48b85ac0203`)
- L65 _enumerator_ `autortfm_log_info` (scope `__anone48b85ac0203`)
- L66 _enumerator_ `autortfm_log_warn` (scope `__anone48b85ac0203`)
- L67 _enumerator_ `autortfm_log_error` (scope `__anone48b85ac0203`)
- L68 _enumerator_ `autortfm_log_fatal` (scope `__anone48b85ac0203`)
- L69 _typedef_ `autortfm_log_warn, autortfm_log_error, autortfm_log_fatal, } autortfm_log_severity;`
- L75 _enumerator_ `autortfm_write_default = 0x0` (scope `__anone48b85ac0303`) — No flags applied to the write.
- L77 _enumerator_ `autortfm_write_no_sanitize = 0x1` (scope `__anone48b85ac0303`) — The write should not be considered by the AutoRTFM sanitizer.
- L80 _enumerator_ `autortfm_write_custom_rollback = 0x2` (scope `__anone48b85ac0303`) — The autortfm_extern_api::RollbackWrite will be called to perform the rollback for this write if the transaction is aborted.
- L83 _enumerator_ `autortfm_write_custom_flag_0 = 0x4` (scope `__anone48b85ac0303`) — Custom flag bits which can be used by the custom abort callbacks. Requires autortfm_write_custom_rollback for usage.
- L84 _enumerator_ `autortfm_write_custom_flag_1 = 0x8` (scope `__anone48b85ac0303`)
- L85 _typedef_ `autortfm_write_custom_flag_0 = 0x4, autortfm_write_custom_flag_1 = 0x8, } autortfm_write_flags;` — Custom flag bits which can be used by the custom abort callbacks. Requires autortfm_write_custom_rollback for usage.
- L88 _typedef_ `typedef uint64_t autortfm_transaction_id;` — An opaque unique identifier for a transaction.
- L91 _typedef_ `typedef unsigned long long autortfm_callstack_frame;` — A single frame of a callstack capture.
- L98 _member_ `void* (*Allocate)(size_t Size, size_t Alignment);` (scope `__anone48b85ac0408`) — The function used to allocate memory from the heap. Must not be null. This API should never return null; if the allocator cannot satisfy the request, it must abort the program.
- L102 _member_ `void* (*Reallocate)(void* Pointer, size_t Size, size_t Alignment, size_t PreviousSize);` (scope `__anone48b85ac0408`) — The function used to reallocate memory from the heap. Must not be null. This API should never return null; if the allocator cannot satisfy the request, it must abort the program.
- L106 _member_ `void* (*AllocateZeroed)(size_t Size, size_t Alignment);` (scope `__anone48b85ac0408`) — The function used to allocate zeroed memory from the heap. Must not be null. This API should never return null; if the allocator cannot satisfy the request, it must abort the program.
- L110 _member_ `void (*Free)(void* Pointer, size_t AllocationSize);` (scope `__anone48b85ac0408`) — The function used to free memory allocated by Allocate(), Reallocate() or AllocateZeroed(). Must not be null.
- L115 _member_ `void (*Log)( const char* File, int Line, void* ProgramCounter, autortfm_log_severity Severity, const char* Format, va_list Args);` (scope `__anone48b85ac0408`) — Function used to log messages using a printf-style format string and va_list arguments. Strings use UTF-8 encoding. Must not be null.
- L121 _member_ `void (*LogWithCallstack)(void* ProgramCounter, autortfm_log_severity Severity, const char* Format, va_list Args);` (scope `__anone48b85ac0408`) — Function used to log messages with a callstack using a printf-style format string and va_list arguments. Strings use UTF-8 encoding. Must not be null.
- L126 _member_ `void (*EnsureFailure)( const char* File, int Line, void* ProgramCounter, const char* Condition, const char* Format, va_list Args);` (scope `__anone48b85ac0408`) — Function used to report an ensure failure using a printf-style format string and va_list arguments. Strings use UTF-8 encoding. Must not be null.
- L131 _member_ `bool (*IsLogActive)(autortfm_log_severity Severity);` (scope `__anone48b85ac0408`) — Function used to query whether a log severity is active. Must not be null.
- L137 _member_ `size_t (*CaptureCallstack)(size_t MaxFrames, autortfm_callstack_frame* StackOut);` (scope `__anone48b85ac0408`) — Performs a capture of the currently executing callstack, writing at most MaxFrames frame addresses to StackOut, starting with with the most deeply nested frame. Returns the number of frame addresses actually written. Must not be null.
- L142 _member_ `void (*LogCallstack)(autortfm_log_severity Severity, size_t Count, autortfm_callstack_frame const* Stack);` (scope `__anone48b85ac0408`) — Prints a callstack captured with CaptureCallstack to the log with the given severity. Must not be null.
- L147 _member_ `void (*OnRuntimeEnabledChanged)();` (scope `__anone48b85ac0408`) — Optional callback to be informed when the value returned by ForTheRuntime::IsAutoRTFMRuntimeEnabled() changes. Can be null.
- L152 _member_ `void (*OnRetryTransactionsChanged)();` (scope `__anone48b85ac0408`) — Optional callback to be informed when the value returned by ForTheRuntime::GetRetryTransaction() changes. Can be null.
- L158 _member_ `void (*OnSanitizerModeChanged)();` (scope `__anone48b85ac0408`) — Optional callback to be informed when the value returned by ForTheRuntime::GetSanitizerMode() changes. Can be null.
- L163 _member_ `void (*OnSanitizerRecordClosedWriteCallstacksChanged)();` (scope `__anone48b85ac0408`) — Optional callback to be informed when the value returned by ForTheRuntime::SanitizerRecordClosedWriteCallstacks() changes. Can be null.
- L178 _member_ `void (*RollbackWrite)(void* Address, const void* Value, size_t Size, autortfm_write_flags Flags);` (scope `__anone48b85ac0408`) — Custom abort handler for writes that that were added with the autortfm_write_custom_rollback flag. It is the responsibility of this function to perform the rollback (copy of Size bytes from Value to Address). RollbackWrite may contain multiple writes condensed into a single contigious block of memory, and the writes may be split into multiple calls with no defined size or alignment granularity. Calls are ordered starting with the most recently recorded writes. Address / Value pointers are ordered starting with the least recently recorded writes. Split writes are guaranteed to be "completed" with the next immediate call(s).
- L179 _typedef_ `} autortfm_extern_api;`
- L187 _prototype_ `void autortfm_initialize(const autortfm_extern_api* ExternAPI) AUTORTFM_NOEXCEPT;` — Initialize the AutoRTFM library. Must only be called once for the lifetime of the application. Parameters: ExternAPI - Function pointers used by AutoRTFM for heap allocations, etc. Must be non-null.
- L189 _function_ `UE_AUTORTFM_CRITICAL_INLINE void autortfm_initialize(const autortfm_extern_api* ExternAPI) AUTORTFM_NOEXCEPT`
- L198 _prototype_ `void autortfm_shutdown() AUTORTFM_NOEXCEPT;` — Shutdown the AutoRTFM library. Must only be called once for the lifetime of the application, after autortfm_initialize().
- L200 _function_ `UE_AUTORTFM_CRITICAL_INLINE void autortfm_shutdown() AUTORTFM_NOEXCEPT`
- L206 _prototype_ `bool autortfm_is_closed(void) AUTORTFM_NOEXCEPT;` — Note: There is no implementation of this function. The AutoRTFM compiler will replace all calls to this function with a constant boolean value.
- L208 _function_ `UE_AUTORTFM_CRITICAL_INLINE bool autortfm_is_closed(void) AUTORTFM_NOEXCEPT`
- L219 _prototype_ `void autortfm_debug_dump_ir(void) AUTORTFM_NOEXCEPT;`
- L221 _function_ `UE_AUTORTFM_CRITICAL_INLINE void autortfm_debug_dump_ir(void) AUTORTFM_NOEXCEPT`
- L229 _prototype_ `autortfm_context_status autortfm_get_context_status(void) AUTORTFM_NOEXCEPT;` — Returns the current AutoRTFM context status. This function is handled specially in the compiler and will be constant folded as autortfm_status_on_track in closed code, or preserved as a function call in open code.
- L231 _function_ `UE_AUTORTFM_CRITICAL_INLINE autortfm_context_status autortfm_get_context_status(void) AUTORTFM_NOEXCEPT`
- L243 _prototype_ `bool autortfm_is_context_status(autortfm_context_status Status) AUTORTFM_NOEXCEPT;` — Returns true if the AutoRTFM context status is equal to Status. This is equivallent to (autortfm_get_context_status() == Status) and exists as a constant-folding optimization for non-optimized builds. This function is handled specially in the compiler and will be constant folded if possible.
- L245 _function_ `UE_AUTORTFM_CRITICAL_INLINE bool autortfm_is_context_status(autortfm_context_status Status) AUTORTFM_NOEXCEPT`
- L252 _prototype_ `autortfm_transaction_status autortfm_transact( void (*UninstrumentedWork)(void*), void (*InstrumentedWork)(void*), void* Arg) AUTORTFM_EXCEPT;`
- L255 _function_ `UE_AUTORTFM_CRITICAL_INLINE autortfm_transaction_status autortfm_transact( void (*UninstrumentedWork)(void*), void (*InstrumentedWork)(void*), void* Arg) AUTORTFM_EXCEPT`
- L265 _prototype_ `autortfm_transaction_status autortfm_transact_then_open( void (*UninstrumentedWork)(void*), void* Arg) AUTORTFM_EXCEPT;`
- L268 _function_ `UE_AUTORTFM_CRITICAL_INLINE autortfm_transaction_status autortfm_transact_then_open( void (*UninstrumentedWork)(void*), void* Arg) AUTORTFM_EXCEPT`
- L277 _prototype_ `UE_AUTORTFM_FORCENOINLINE void autortfm_abort_transaction() AUTORTFM_NOEXCEPT;`
- L279 _function_ `UE_AUTORTFM_CRITICAL_INLINE void autortfm_abort_transaction() AUTORTFM_NOEXCEPT`
- L283 _prototype_ `UE_AUTORTFM_FORCENOINLINE void autortfm_cascading_abort_transaction() AUTORTFM_NOEXCEPT;`
- L285 _function_ `UE_AUTORTFM_CRITICAL_INLINE void autortfm_cascading_abort_transaction() AUTORTFM_NOEXCEPT`
- L289 _prototype_ `UE_AUTORTFM_FORCENOINLINE void autortfm_cascading_retry_transaction() AUTORTFM_NOEXCEPT;`
- L291 _function_ `UE_AUTORTFM_CRITICAL_INLINE void autortfm_cascading_retry_transaction() AUTORTFM_NOEXCEPT`
- L295 _prototype_ `AUTORTFM_DISABLE void autortfm_start_transaction() AUTORTFM_NOEXCEPT;`
- L297 _function_ `UE_AUTORTFM_CRITICAL_INLINE void autortfm_start_transaction() AUTORTFM_NOEXCEPT`
- L301 _prototype_ `AUTORTFM_DISABLE void autortfm_commit_transaction() AUTORTFM_NOEXCEPT;`
- L303 _function_ `UE_AUTORTFM_CRITICAL_INLINE void autortfm_commit_transaction() AUTORTFM_NOEXCEPT`
- L307 _prototype_ `AUTORTFM_OPEN autortfm_transaction_id autortfm_current_transaction_id() AUTORTFM_NOEXCEPT;`
- L309 _function_ `UE_AUTORTFM_CRITICAL_INLINE autortfm_transaction_id autortfm_current_transaction_id() AUTORTFM_NOEXCEPT`
- L316 _prototype_ `UE_AUTORTFM_FORCENOINLINE void autortfm_open(void (*work)(void* arg), void* arg);`
- L318 _function_ `UE_AUTORTFM_CRITICAL_INLINE void autortfm_open(void (*work)(void* arg), void* arg)`
- L325 _prototype_ `UE_AUTORTFM_FORCENOINLINE void autortfm_open_no_sanitize(void (*work)(void* arg), void* arg);`
- L327 _function_ `UE_AUTORTFM_CRITICAL_INLINE void autortfm_open_no_sanitize(void (*work)(void* arg), void* arg)`
- L334 _prototype_ `[[nodiscard]] autortfm_transaction_status autortfm_close( void (*UninstrumentedWork)(void*), void (*InstrumentedWork)(void*), void* Arg);`
- L338 _function_ `[[nodiscard]] UE_AUTORTFM_CRITICAL_INLINE autortfm_transaction_status autortfm_close( void (*UninstrumentedWork)(void*), void (*InstrumentedWork)(void*), void* Arg)`
- L353 _prototype_ `void autortfm_record_open_write(void* Ptr, size_t Size) AUTORTFM_NOEXCEPT;`
- L363 _prototype_ `void autortfm_record_open_write_with_flags(void* Ptr, size_t Size, autortfm_write_flags Flags) AUTORTFM_NOEXCEPT;`
- L365 _function_ `UE_AUTORTFM_CRITICAL_INLINE void autortfm_record_open_write_with_flags( void* Ptr, size_t Size, autortfm_write_flags Flags) AUTORTFM_NOEXCEPT`
- L397 _prototype_ `void autortfm_register_open_to_closed_functions(struct autortfm_open_to_closed_table* Table) AUTORTFM_NOEXCEPT;`
- L398 _prototype_ `void autortfm_unregister_open_to_closed_functions(struct autortfm_open_to_closed_table* Table) AUTORTFM_NOEXCEPT;`
- L400 _function_ `UE_AUTORTFM_CRITICAL_INLINE void autortfm_register_open_to_closed_functions(autortfm_open_to_closed_table* Table) AUTORTFM_NOEXCEPT`
- L404 _function_ `UE_AUTORTFM_CRITICAL_INLINE void autortfm_unregister_open_to_closed_functions(autortfm_open_to_closed_table* Table) AUTORTFM_NOEXCEPT`
- L411 _prototype_ `bool autortfm_is_on_current_transaction_stack(void* Ptr) AUTORTFM_NOEXCEPT;`
- L413 _function_ `UE_AUTORTFM_CRITICAL_INLINE bool autortfm_is_on_current_transaction_stack(void* Ptr) AUTORTFM_NOEXCEPT`
- L421 _prototype_ `void autortfm_on_commit(void (*work)(void* arg), void* arg);`
- L423 _function_ `UE_AUTORTFM_CRITICAL_INLINE void autortfm_on_commit(void (*work)(void* arg), void* arg)`
- L430 _prototype_ `void autortfm_on_pre_abort(void (*work)(void* arg), void* arg) AUTORTFM_NOEXCEPT;`
- L432 _function_ `UE_AUTORTFM_CRITICAL_INLINE void autortfm_on_pre_abort(void (*work)(void* arg), void* arg) AUTORTFM_NOEXCEPT`
- L440 _prototype_ `void autortfm_on_abort(void (*work)(void* arg), void* arg) AUTORTFM_NOEXCEPT;`
- L442 _function_ `UE_AUTORTFM_CRITICAL_INLINE void autortfm_on_abort(void (*work)(void* arg), void* arg) AUTORTFM_NOEXCEPT`
- L450 _prototype_ `void autortfm_push_on_abort_handler(const void* key, void (*work)(void* arg), void* arg) AUTORTFM_NOEXCEPT;`
- L451 _prototype_ `void autortfm_pop_on_abort_handler(const void* key) AUTORTFM_NOEXCEPT;`
- L453 _function_ `UE_AUTORTFM_CRITICAL_INLINE void autortfm_push_on_abort_handler( const void* key, void (*work)(void* arg), void* arg) AUTORTFM_NOEXCEPT`
- L461 _function_ `UE_AUTORTFM_CRITICAL_INLINE void autortfm_pop_on_abort_handler(const void* key) AUTORTFM_NOEXCEPT`
- L468 _prototype_ `void* autortfm_did_allocate(void* ptr, size_t size) AUTORTFM_NOEXCEPT;`
- L470 _function_ `UE_AUTORTFM_CRITICAL_INLINE void* autortfm_did_allocate(void* ptr, size_t size) AUTORTFM_NOEXCEPT`
- L478 _prototype_ `void autortfm_did_free(void* ptr) AUTORTFM_NOEXCEPT;`
- L480 _function_ `UE_AUTORTFM_CRITICAL_INLINE void autortfm_did_free(void* ptr) AUTORTFM_NOEXCEPT`
- L493 _prototype_ `void autortfm_check_abi(void* ptr, size_t size) AUTORTFM_NOEXCEPT;`
- L495 _function_ `UE_AUTORTFM_CRITICAL_INLINE void autortfm_check_abi(void* ptr, size_t size) AUTORTFM_NOEXCEPT`
- L506 _prototype_ `[[noreturn]] AUTORTFM_OPEN void autortfm_unreachable(const char* Message) AUTORTFM_NOEXCEPT;` — Called when execution unexpectedly reaches a code path that was considered unreachable. Either aborts execution of the program or aborts the current transaction, depending on the current 'InternalAbortAction' state.
- L508 _function_ `UE_AUTORTFM_CRITICAL_INLINE void autortfm_unreachable(const char* Message) AUTORTFM_NOEXCEPT`
- L516 _prototype_ `extern "C" UE_AUTORTFM_FORCENOINLINE void* autortfm_lookup_function( void* OriginalFunction, const char* Where) AUTORTFM_NOEXCEPT;` — Given an open function pointer, returns the equivalent closed function pointer.
- L519 _function_ `UE_AUTORTFM_CRITICAL_INLINE void* autortfm_lookup_function(void* OriginalFunction, const char* Where) AUTORTFM_NOEXCEPT`

### `Source/Runtime/AutoRTFM/Public/AutoRTFM/Constants.h` (Public)


#### enum `(anonymous)`  
``  
_L16-25_

#### enum `(anonymous)`  
``  
_L32-43_

#### enum `(anonymous)`  
``  
_L47-94_

#### Free symbols / members of external scopes

- L17 _enumerator_ `autortfm_status_idle = 0` (scope `__anon6a26c36c0103`)
- L18 _enumerator_ `autortfm_status_on_track` (scope `__anon6a26c36c0103`)
- L19 _enumerator_ `autortfm_status_unwinding` (scope `__anon6a26c36c0103`)
- L20 _enumerator_ `autortfm_status_committing` (scope `__anon6a26c36c0103`)
- L21 _enumerator_ `autortfm_status_aborting` (scope `__anon6a26c36c0103`)
- L22 _enumerator_ `autortfm_status_retrying` (scope `__anon6a26c36c0103`)
- L23 _enumerator_ `autortfm_status_completing` (scope `__anon6a26c36c0103`)
- L24 _enumerator_ `autortfm_status_in_static_local_initializer` (scope `__anon6a26c36c0103`)
- L25 _typedef_ `autortfm_status_retrying, autortfm_status_completing, autortfm_status_in_static_local_initializer, } autortfm_context_status;`
- L34 _enumerator_ `autortfm_sanitizer_disabled` (scope `__anon6a26c36c0203`) — Disable AutoRTFM sanitizer.
- L38 _enumerator_ `autortfm_sanitizer_warn` (scope `__anon6a26c36c0203`) — Enable AutoRTFM sanitizer. AutoRTFM sanitizer failures are treated as warnings.
- L42 _enumerator_ `autortfm_sanitizer_error` (scope `__anon6a26c36c0203`) — Enable AutoRTFM sanitizer. AutoRTFM sanitizer failures are treated as fatal.
- L43 _typedef_ `autortfm_sanitizer_error, } autortfm_sanitizer_mode;` — Enable AutoRTFM sanitizer. AutoRTFM sanitizer failures are treated as fatal.
- L50 _enumerator_ `autortfm_mode_enable = 0` (scope `__anon6a26c36c0303`) — [[clang::autortfm(enable)]] / default Generate AutoRTFM instrumentation for the function.
- L58 _enumerator_ `autortfm_mode_disable = 1` (scope `__anon6a26c36c0303`) — [[clang::autortfm(disable)]] Do not generate AutoRTFM instrumentation for the function. Calls to the function from AutoRTFM-enabled functions is a compile-time error. WARNING: If you change this constant, then make sure to also update UEBuildModule.AddModuleToCompileEnvironment() in Engine\Source\Programs\UnrealBuildTool\Configuration\UEBuildModule.cs
- L64 _enumerator_ `autortfm_mode_disable_no_sanitize = 2` (scope `__anon6a26c36c0303`) — [[clang::autortfm(disable_no_sanitize)]] Same as autortfm_mode_disable, but the function will be ignored by the AutoRTFM sanitizer. Note that the sanitizer will still be active for function calls made by this function.
- L68 _enumerator_ `autortfm_mode_infer = 3` (scope `__anon6a26c36c0303`) — [[clang::autortfm(infer)]] AutoRTFM instrumentation mode is determined by the calls made by the function.
- L73 _enumerator_ `autortfm_mode_open = 4` (scope `__anon6a26c36c0303`) — [[clang::autortfm(open)]] / [[clang::autortfm_always_open]] Do not generate AutoRTFM instrumentation for the function. Calling the function from the closed will call the uninstrumented variant.
- L77 _enumerator_ `autortfm_mode_open_no_sanitize = 5` (scope `__anon6a26c36c0303`) — [[clang::autortfm(open_no_sanitize)]] / [[clang::autortfm_always_open_no_sanitize]] Same as autortfm_mode_open, but the AutoRTFM sanitizer will not instrument the function.
- L88 _enumerator_ `autortfm_mode_internal = 6` (scope `__anon6a26c36c0303`) — [[clang::autortfm(autortfm_mode_internal)]] Do not generate AutoRTFM instrumentation for the function. Calls to the function from AutoRTFM-enabled functions will directly call the open function without any pre / post callbacks or trampolines. The AutoRTFM sanitizer ignore these functions - no calls to autortfm_disable_sanitizer() or autortfm_enable_sanitizer() will be emitted, nor will any calls to autortfm_sanitizer_open_write() be emitted for writes, however calls to any open functions made by an internal function may call autortfm_sanitizer_open_write().
- L93 _enumerator_ `autortfm_mode_no_autortfm = 7` (scope `__anon6a26c36c0303`) — [[clang::noautortfm]] DEPRECATED - similar to Disable but does not cause a compile-time error if called from an AutoRTFM-enabled function.
- L94 _typedef_ `autortfm_mode_no_autortfm = 7, } autortfm_mode;` — [[clang::noautortfm]] DEPRECATED - similar to Disable but does not cause a compile-time error if called from an AutoRTFM-enabled function.
- L97 _variable_ `static const autortfm_mode autortfm_last_mode = autortfm_mode_no_autortfm;` — The last mode declared in autortfm_mode. Used for range checking.
- L100 _function_ `inline const char* autortfm_mode_to_string(autortfm_mode Mode)` — Returns the AutoRTFM mode as a string
- L129 _namespace_ `namespace AutoRTFM`
- L133 _function_ `constexpr inline bool IsDisabled(autortfm_mode Mode)` (scope `AutoRTFM`) — Returns true if mode is autortfm_mode_disable or autortfm_mode_disable_no_sanitize
- L139 _function_ `constexpr inline bool IsOpen(autortfm_mode Mode)` (scope `AutoRTFM`) — Returns true if mode is autortfm_mode_open or autortfm_mode_open_no_sanitize
- L145 _function_ `constexpr inline bool IsNoSanitize(autortfm_mode Mode)` (scope `AutoRTFM`) — Returns true if mode suspends the AutoRTFM sanitizer (open_no_sanitize or disable_no_sanitize)
- L152 _namespace_ `namespace AutoRTFM`
- L152 _namespace_ `namespace Constants` (scope `AutoRTFM`)
- L154 _variable_ `inline constexpr uint32_t Major = 0;` (scope `AutoRTFM::Constants`)
- L155 _variable_ `inline constexpr uint32_t Minor = 3;` (scope `AutoRTFM::Constants`)
- L156 _variable_ `inline constexpr uint32_t Patch = 0;` (scope `AutoRTFM::Constants`)
- L164 _variable_ `inline constexpr uint64_t MagicPrefix = 0xa273'0000'0000'0000;` (scope `AutoRTFM::Constants`) — The Magic Prefix constant - an arbitrarily chosen address prefix, shared between the AutoRTFM compiler and runtime. We add this prefix value to open function pointer addresses in our custom LLVM pass. At runtime, if we detect the Magic Prefix in the the top 16 bits of an open function pointer address, we assume that we can find a closed variant pointer residing 8 bytes before the function address.
- L168 _variable_ `inline constexpr uint64_t PosOffsetMagicPrefix = 0xa272'0000'0000'0000;` (scope `AutoRTFM::Constants`) — Similar to the above, but these constants indicate that the low 48 bits provide a relative addresses from the open function to the closed function.
- L169 _variable_ `inline constexpr uint64_t NegOffsetMagicPrefix = 0xa271'0000'0000'0000;` (scope `AutoRTFM::Constants`)

### `Source/Runtime/AutoRTFM/Public/AutoRTFM/Defines.h` (Public)


#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_AUTORTFM 1 // Compiler is 'verse-clang'`
- L10 _macro_ `#define UE_AUTORTFM 0`
- L14 _macro_ `#define UE_AUTORTFM_ENABLED 1 // Compiled with '-fautortfm'`
- L16 _macro_ `#define UE_AUTORTFM_ENABLED 0`
- L20 _macro_ `#define UE_AUTORTFM_ENABLED_RUNTIME_BY_DEFAULT 1`
- L24 _macro_ `#define UE_AUTORTFM_STATIC_VERIFIER 0`
- L31 _macro_ `#define UE_AUTORTFM_NOAUTORTFM [[clang::noautortfm]]` — The annotated function will have no AutoRTFM closed variant generated, and cannot be called from another closed function. This attribute will eventually be deprecated and replaced with AUTORTFM_DISABLE.
- L37 _macro_ `#define UE_AUTORTFM_ALWAYS_OPEN [[clang::autortfm_always_open]]` — Omits AutoRTFM instrumentation from the function. Calling this annotated function from the closed will automatically enter the open for the duration of the call and will return back to the closed. Deprecated: Use AUTORTFM_OPEN
- L42 _macro_ `#define UE_AUTORTFM_ALWAYS_OPEN_NO_MEMORY_VALIDATION [[clang::autortfm_always_open_no_sanitize]]` — The same as UE_AUTORTFM_ALWAYS_OPEN, but disables the AutoRTFM sanitizer for the duration of this call. Deprecated: Use AUTORTFM_OPEN_NO_SANITIZE
- L47 _macro_ `#define UE_AUTORTFM_ALWAYS_OPEN_NO_SANITIZER [[clang::autortfm_always_open_no_sanitize]]` — The same as UE_AUTORTFM_ALWAYS_OPEN, but disables the AutoRTFM sanitizer for the duration of this call. Deprecated: Use AUTORTFM_OPEN_NO_SANITIZE
- L57 _macro_ `#define AUTORTFM_DISABLE [[clang::autortfm(autortfm_mode_disable)]]` — Annotation that can be applied to classes, methods or functions to prevent AutoRTFM closed function(s) from being generated. Applying the annotation to a class is equivalent to applying the annotation to each method of the class. When annotating a function, the attribute must be placed on a the function declaration (usually in the header) and not a function implementation. Annotated functions cannot be called from another closed function and attempting to do so will result in a runtime failure.
- L60 _macro_ `#define AUTORTFM_DISABLE_IF(...) [[clang::autortfm(autortfm_mode_disable, __VA_ARGS__)]]` — Applies the AUTORTFM_DISABLE annotation if the condition argument evaluates to true.
- L64 _macro_ `#define AUTORTFM_DISABLE_NO_SANITIZE [[clang::autortfm(autortfm_mode_disable_no_sanitize)]]` — Same as AUTORTFM_DISABLE, but the functions will be ignored by the AutoRTFM sanitizer.
- L69 _macro_ `#define AUTORTFM_DISABLE_BEGIN _Pragma("clang attribute AutoRTFM_Disable.push (AUTORTFM_DISABLE, apply_to = any(function, record))")` — Begins a range where all classes and functions will be automatically annotated with AUTORTFM_DISABLE. Must be ended with AUTORTFM_DISABLE_END before the end of the file.
- L72 _macro_ `#define AUTORTFM_DISABLE_END _Pragma("clang attribute AutoRTFM_Disable.pop")` — Ends a range started with AUTORTFM_DISABLE_BEGIN
- L78 _macro_ `#define AUTORTFM_ENABLE [[clang::autortfm(autortfm_mode_enable)]]` — Annotation that can be applied to classes, methods or functions to re-enable AutoRTFM instrumentation which would otherwise be disabled by AUTORTFM_DISABLE. Useful for selectively enabling AutoRTFM on methods when a class is annotated AUTORTFM_DISABLE.
- L81 _macro_ `#define AUTORTFM_ENABLE_IF(...) [[clang::autortfm(autortfm_mode_enable, __VA_ARGS__)]]` — Applies the AUTORTFM_ENABLE annotation if the condition argument evaluates to true.
- L93 _macro_ `#define AUTORTFM_INFER [[clang::autortfm(autortfm_mode_infer)]]` — Annotation that can be applied to classes, methods or functions to infer whether AutoRTFM instrumentation should be enabled for each individual function based on the AutoRTFM-enabled state of each callee made by the function. If the function calls any AutoRTFM-disabled function, then the function will also be AutoRTFM-disabled, otherwise the function is AutoRTFM-enabled. Applying the annotation to a class is equivalent to applying the annotation to each method of the class. When annotating a function, the attribute must be placed on a the function declaration (usually in the header) and not a function implementation.
- L103 _macro_ `#define AUTORTFM_OPEN [[clang::autortfm(autortfm_mode_open)]]` — Annotation that can be applied to classes, methods or functions to prevent AutoRTFM closed function(s) from being generated. Unlike AUTORTFM_DISABLE annotated functions can be called from closed functions, which will call the uninstrumented function. Applying the annotation to a class is equivalent to applying the annotation to each method of the class. When annotating a function, the attribute must be placed on a the function declaration (usually in the header) and not a function implementation.
- L107 _macro_ `#define AUTORTFM_OPEN_NO_VALIDATION [[clang::autortfm(autortfm_mode_open_no_sanitize)]]` — Similar to AUTORTFM_OPEN, but disables the AutoRTFM sanitizer on the call. Deprecated: Use AUTORTFM_OPEN_NO_SANITIZE
- L110 _macro_ `#define AUTORTFM_OPEN_NO_SANITIZE [[clang::autortfm(autortfm_mode_open_no_sanitize)]]` — Similar to AUTORTFM_OPEN, but disables AutoRTFM sanitizer on the call.
- L115 _macro_ `#define AUTORTFM_IMPLICIT_ENABLE [[clang::autortfm_implicit_mode(autortfm_mode_enable)]]` — Annotation that can be applied to function parameters to implicitly set the AutoRTFM mode of "naked" lambda arguments to AutoRTFM-enabled, regardless of the AutoRTFM mode of the caller function.
- L120 _macro_ `#define AUTORTFM_IMPLICIT_DISABLE [[clang::autortfm_implicit_mode(autortfm_mode_disable)]]` — Annotation that can be applied to function parameters to implicitly set the AutoRTFM mode of "naked" lambda arguments to AutoRTFM-disable, regardless of the AutoRTFM mode of the caller function.
- L123 _macro_ `#define AUTORTFM_MODE_OF(EXPR_OR_TYPE) static_cast<autortfm_mode>(__autortfm_get_mode(EXPR_OR_TYPE))` — Evaluates to the AutoRTFM mode of function, method, type or class.
- L126 _macro_ `#define AUTORTFM_MODE_OF_CALL(CALL_EXPR) AUTORTFM_MODE_OF(__autortfm_declcall(CALL_EXPR))` — Evaluates to the AutoRTFM mode of function, method, type or class.
- L129 _macro_ `#define UE_AUTORTFM_CALLSITE_FORCEINLINE [[clang::always_inline]]` — Force the call statement to be inlined.
- L132 _macro_ `#define AUTORTFM_SANITIZER (__has_feature(autortfm_sanitizer))` — Evaluates to true iff the AutoRTFM sanitizer is enabled.
- L135 _macro_ `#define AUTORTFM_LIKELY(x) __builtin_expect(!!(x), 1)` — Provides a hint to the compiler that the expression is likely to be true
- L138 _macro_ `#define AUTORTFM_UNLIKELY(x) __builtin_expect(!!(x), 0)` — Provides a hint to the compiler that the expression is unlikely to be true
- L141 _macro_ `#define AUTORTFM_SANITIZER_ONLY(...) __VA_ARGS__`
- L143 _macro_ `#define AUTORTFM_SANITIZER_ONLY(...)`
- L148 _macro_ `#define UE_AUTORTFM_NOAUTORTFM`
- L149 _macro_ `#define UE_AUTORTFM_ALWAYS_OPEN`
- L150 _macro_ `#define UE_AUTORTFM_ALWAYS_OPEN_NO_MEMORY_VALIDATION`
- L151 _macro_ `#define UE_AUTORTFM_ALWAYS_OPEN_NO_SANITIZER`
- L152 _macro_ `#define AUTORTFM_DISABLE`
- L153 _macro_ `#define AUTORTFM_DISABLE_IF(CONDITION)`
- L154 _macro_ `#define AUTORTFM_DISABLE_NO_SANITIZE`
- L155 _macro_ `#define AUTORTFM_DISABLE_BEGIN`
- L156 _macro_ `#define AUTORTFM_DISABLE_END`
- L157 _macro_ `#define AUTORTFM_ENABLE`
- L158 _macro_ `#define AUTORTFM_INFER`
- L159 _macro_ `#define AUTORTFM_OPEN`
- L160 _macro_ `#define AUTORTFM_OPEN_NO_VALIDATION`
- L161 _macro_ `#define AUTORTFM_OPEN_NO_SANITIZE`
- L162 _macro_ `#define AUTORTFM_IMPLICIT_ENABLE`
- L163 _macro_ `#define AUTORTFM_IMPLICIT_DISABLE`
- L164 _macro_ `#define AUTORTFM_MODE_OF(EXPR_OR_TYPE) autortfm_mode_disable`
- L165 _macro_ `#define AUTORTFM_MODE_OF_CALL(EXPR_OR_TYPE) autortfm_mode_disable`
- L166 _macro_ `#define UE_AUTORTFM_CALLSITE_FORCEINLINE`
- L167 _macro_ `#define AUTORTFM_SANITIZER (false)`
- L168 _macro_ `#define AUTORTFM_LIKELY(x) (!!(x))`
- L169 _macro_ `#define AUTORTFM_UNLIKELY(x) (!!(x))`
- L174 _macro_ `#define AUTORTFM_NOEXCEPT noexcept`
- L175 _macro_ `#define AUTORTFM_EXCEPT noexcept(false)`
- L177 _macro_ `#define AUTORTFM_NOEXCEPT`
- L178 _macro_ `#define AUTORTFM_EXCEPT`
- L182 _macro_ `#define UE_AUTORTFM_ENSURE_SAFE [[clang::autortfm_ensure_safe]]`
- L183 _macro_ `#define UE_AUTORTFM_ASSUME_SAFE [[clang::autortfm_assume_safe]]`
- L185 _macro_ `#define UE_AUTORTFM_ENSURE_SAFE`
- L186 _macro_ `#define UE_AUTORTFM_ASSUME_SAFE`
- L189 _macro_ `#define UE_AUTORTFM_CONCAT_IMPL(A, B) A##B`
- L190 _macro_ `#define UE_AUTORTFM_CONCAT(A, B) UE_AUTORTFM_CONCAT_IMPL(A, B)`
- L193 _macro_ `#define UE_AUTORTFM_FORCEINLINE __forceinline`
- L194 _macro_ `#define UE_AUTORTFM_FORCEINLINE_ALWAYS __forceinline`
- L195 _macro_ `#define UE_AUTORTFM_FORCENOINLINE __declspec(noinline)`
- L196 _macro_ `#define UE_AUTORTFM_ASSUME(x) __assume(x)`
- L198 _macro_ `#define UE_AUTORTFM_FORCEINLINE __attribute__((always_inline)) inline`
- L199 _macro_ `#define UE_AUTORTFM_FORCEINLINE_ALWAYS __attribute__((always_inline)) inline`
- L200 _macro_ `#define UE_AUTORTFM_FORCENOINLINE __attribute__((noinline))`
- L201 _macro_ `#define UE_AUTORTFM_ASSUME(x) __builtin_assume(x)`
- L203 _macro_ `#define UE_AUTORTFM_FORCEINLINE inline`
- L204 _macro_ `#define UE_AUTORTFM_FORCEINLINE_ALWAYS inline`
- L205 _macro_ `#define UE_AUTORTFM_FORCENOINLINE`
- L206 _macro_ `#define UE_AUTORTFM_ASSUME(x)`
- L218 _macro_ `#define AUTORTFM_DISABLE_UNREACHABLE_CODE_WARNINGS __pragma(warning(push)) __pragma(warning(disable : 4702)) /* unreachable code */`
- L219 _macro_ `#define AUTORTFM_RESTORE_UNREACHABLE_CODE_WARNINGS __pragma(warning(pop))` — #define AUTORTFM_DISABLE_UNREACHABLE_CODE_WARNINGS __pragma(warning(push)) __pragma(warning(disable : 4702))   unreachable code
- L221 _macro_ `#define AUTORTFM_DISABLE_UNREACHABLE_CODE_WARNINGS`
- L222 _macro_ `#define AUTORTFM_RESTORE_UNREACHABLE_CODE_WARNINGS`
- L225 _macro_ `#define UE_AUTORTFM_UNUSED(UNUSEDVAR) (void)UNUSEDVAR`
- L230 _macro_ `#define UE_AUTORTFM_CRITICAL_INLINE static UE_AUTORTFM_FORCEINLINE`
- L231 _macro_ `#define UE_AUTORTFM_CRITICAL_INLINE_ALWAYS static UE_AUTORTFM_FORCEINLINE_ALWAYS`
- L233 _macro_ `#define UE_AUTORTFM_CRITICAL_INLINE \`
- L235 _macro_ `#define UE_AUTORTFM_CRITICAL_INLINE_ALWAYS \`

### `Source/Runtime/AutoRTFM/Public/AutoRTFM/Metrics.h` (Public)


#### struct `AutoRTFM::FAutoRTFMMetrics`  
`struct FAutoRTFMMetrics`  
_L12-48_
- L14 _public member_ `uint64_t NumTopLevelTransactionsCompleted;` — Tracks the number of top-level transactions that have been completed
- L15 _public member_ `uint64_t NumTransactionsStarted;` — Tracks the number of transactions (at any depth) that have been started
- L16 _public member_ `uint64_t NumTransactionsCommitted;` — Tracks the number of transactions (at any depth) that have been committed
- L17 _public member_ `uint64_t NumTransactionsAborted;` — Tracks the number of transactions (at any depth) that have been aborted
- L18 _public member_ `uint64_t NumRequestedAborts;` — Tracks the number of calls to AbortTransaction()
- L19 _public member_ `uint64_t NumRequestedCascadingAborts;` — Tracks the number of calls to CascadingAbortTransaction()
- L20 _public member_ `uint64_t NumRequestedCascadingRetries;` — Tracks the number of calls to CascadingRetryTransaction()
- L21 _public member_ `uint64_t NumTransactionalViolations;` — Tracks the number of AutoRTFM aborts caused by violating transactional rules
- L23 _public member_ `uint64_t OverallPeakMemoryUsage;` — Tracks the peak memory usage across all transactions, in bytes
- L24 _public member_ `uint64_t ActiveTransactionPeakMemoryUsage;` — Tracks the peak memory usage within this transaction, in bytes
- L34 _public typedef_ `using HistogramBucketArray = uint32_t[64];` — A log2-histogram of transaction memory usage, in bytes. We do not distinguish between committed or aborted transactions in the histogram. [0] indicates the number of finished transactions using between 0 and 1 bytes of memory. [1] indicates the number of finished transactions using between 2 and 3 bytes of memory. [2] indicates the number of finished transactions using between 4 and 7 bytes of memory. [3] indicates the number of finished transactions using between 8 and 15 bytes of memory. [4] indicates the number of finished transactions using between 16 and 31 bytes of memory. and so on.
- L35 _public member_ `HistogramBucketArray MemoryUsageHistogram;`
- L37 _public member_ `static constexpr char CSVHeader[] = "NumTopLevelTransactionsCompleted,NumTransactionsStarted,NumTransactionsCommitted," "NumTransactionsAborted,NumRequestedAborts,NumRequestedCascadingAborts,NumRequestedCascadingRetries," "NumTransactionalViolations,OverallPeakMemoryUsage,ActiveTransactionPeakMemoryUsage," "0b+,2b+,4b+,8b+,16b+,32b+,64b+,128b+,256b+,512b+,"`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace AutoRTFM`
- L51 _prototype_ `void ResetAutoRTFMMetrics();` (scope `AutoRTFM`) — Reset the internal metrics tracking back to zero.
- L54 _prototype_ `FAutoRTFMMetrics GetAutoRTFMMetrics();` (scope `AutoRTFM`) — Get a snapshot of the current internal metrics.

### `Source/Runtime/AutoRTFM/Public/AutoRTFM/OpenWrapper.h` (Public)


#### class `AutoRTFM::TOpenWrapper`  
`template <typename ObjectType> class AUTORTFM_OPEN TOpenWrapper final`  
_L27-39_
- desc: An object wrapper that will ensure the copy constructor, move constructor, copy assignment, move assignment and destructor are all called in the open. This can be used to wrap a lambda capture if it is known that it safe and more optimal to copy, move & destruct the object in the open. For example - it may be safe to wrap a shared pointer with a TOpenWrapper when capturing for use by AutoRTFM::OnCommit() or AutoRTFM::OnAbort(), as the AutoRTFM::TTask destructor will be called regardless of a transactional failure or commit. This may be preferable to capturing the unwrapped shared pointer as we can avoid costly closed transactional logic to ensure the count is restored on failure: AutoRTFM::OnCommit([WrappedSharedPtr = AutoRTFM::TOpenWrapper{MySharedPtr}] { WrappedSharedPtr.Object->DoSomething(); });
- L30 _public member_ `ObjectType Object;`
- L32 _public prototype_ `TOpenWrapper(const TOpenWrapper&) = default;`
- L33 _public prototype_ `TOpenWrapper(TOpenWrapper&&) = default;`
- L34 _public prototype_ `TOpenWrapper& operator=(const TOpenWrapper&) = default;`
- L35 _public prototype_ `TOpenWrapper& operator=(TOpenWrapper&&) = default;`
- L36 _public function_ `TOpenWrapper(const ObjectType& Value) : Object`
- L37 _public function_ `TOpenWrapper(ObjectType&& Value) : Object`
- L38 _public prototype_ `~TOpenWrapper() = default;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace AutoRTFM`

### `Source/Runtime/AutoRTFM/Public/AutoRTFM/ReportHazard.h` (Public)


#### enum `AutoRTFM::ForTheRuntime::EHazardType`  
`enum class EHazardType`  
_L13-23_
- L15 _public enumerator_ `CriticalSection`
- L16 _public enumerator_ `RWLock`
- L17 _public enumerator_ `Mutex`
- L18 _public enumerator_ `RecursiveMutex`
- L19 _public enumerator_ `SharedMutex`
- L20 _public enumerator_ `OpenFree`
- L21 _public enumerator_ `SpscQueue`
- L22 _public enumerator_ `MpscQueue`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace AutoRTFM`
- L10 _namespace_ `namespace ForTheRuntime` (scope `AutoRTFM`)
- L29 _prototype_ `AUTORTFM_OPEN void ReportAutoRTFMHazard(EHazardType HazardType);` (scope `AutoRTFM::ForTheRuntime`) — Prints an AutoRTFM Hazard banner, with descriptive text based on the hazard type, and a callstack. Concludes with AutoRTFM::ReportError, which will terminate the process under normal circumstances.
- L37 _macro_ `#define UE_AUTORTFM_REPORT_HAZARD_IF_CLOSED(InHazardType) \` — Reports an AutoRTFM hazard if this block of code is reached from the closed. `autortfm_is_closed` is optimized away at compile time, so this compiles away to nothing in an open function.
- L44 _macro_ `#define UE_AUTORTFM_REPORT_HAZARD_IF_CLOSED(InHazardType) ((void)0)` — Our macro compiles away to nothing on compilers which do not support AutoRTFM.

### `Source/Runtime/AutoRTFM/Public/AutoRTFM/ReturnFromOpenMode.h` (Public)


#### enum `AutoRTFM::EReturnFromOpenMode`  
`enum class EReturnFromOpenMode`  
_L19-33_
- desc: An enumerator of modes used to control the behaviour of values passed across the open -> closed boundary. For more information see the following declarations: * AutoRTFM::Open() * AutoRTFM::ReturnFromOpenModeFor * AutoRTFM::CHasAssignFromOpenToClosedMethod * AutoRTFM::CHasReturnFromOpenModeField
- L22 _public enumerator_ `Unsupported` — The type does not support cross open -> closed boundaries.
- L25 _public enumerator_ `CopyConstructInClosed` — The type can be copy-constructed in the closed from a value constructed in the open.
- L28 _public enumerator_ `MoveConstructInClosed` — The type can be move-constructed in the closed from a value constructed in the open.
- L32 _public enumerator_ `CustomMethod` — The type has a custom method that will be called to handle passing a value of the type across a open -> closed boundary. See AutoRTFM::CHasAssignFromOpenToClosedMethod.

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace AutoRTFM`
- L56 _variable_ `template <typename T> static constexpr EReturnFromOpenMode ReturnFromOpenModeFor = EReturnFromOpenMode::Unsupported;` (scope `AutoRTFM`) — Evaluates to the EReturnFromOpenMode for the given type. Evaluates to EReturnFromOpenMode::Unsupported, unless specialized.
- L63 _variable_ `template <CHasReturnFromOpenModeField T> static constexpr EReturnFromOpenMode ReturnFromOpenModeFor<T> = T::AutoRTFMReturnFromOpenMode;` (scope `AutoRTFM`) — Specialization of ReturnFromOpenModeFor for types that have a static field with the signature: static constexpr AutoRTFM::EReturnFromOpenMode AutoRTFMReturnFromOpenMode = <mode>; Evaluates to the field's mode. See CHasReturnFromOpenModeField.
- L71 _variable_ `template <CHasAssignFromOpenToClosedMethod T> static constexpr EReturnFromOpenMode ReturnFromOpenModeFor<T> = EReturnFromOpenMode::CustomMethod;` (scope `AutoRTFM`) — Specialization of ReturnFromOpenModeFor for types that have a static mode with the signature: static void AutoRTFMAssignFromOpenToClosed(T& Closed, U Open) Where `U` is `T`, `const T&` or `T&&` Evaluates to EReturnFromOpenMode::CustomMethod. See CHasAssignFromOpenToClosedMethod.
- L82 _variable_ `template <typename T> static constexpr EReturnFromOpenMode ReturnFromOpenModeFor<T*> = EReturnFromOpenMode::CopyConstructInClosed;` (scope `AutoRTFM`) — Specialization of ReturnFromOpenModeFor for raw pointer types. Evaluates to EReturnFromOpenMode::CopyConstructInClosed.

### `Source/Runtime/AutoRTFM/Public/AutoRTFM/Task.h` (Public)


#### class `AutoRTFM::TTask`  
`template <typename ReturnType, typename... ParameterTypes> class TTask<ReturnType(ParameterTypes...)>`  
_L29-276_
- L32 _public member_ `static constexpr size_t InlineDataSize = 16;`
- L33 _public member_ `static constexpr size_t InlineDataAlignment = 8;`
- L160 _public prototype_ `TTask() = default;` — Constructor. The TTask is constructed in a non-set state.
- L163 _public function_ `~TTask()` — Destructor.
- L169 _public function_ `TTask(const TTask& Other)` — Copy constructor
- L179 _public function_ `TTask(TTask&& Other)` — Move constructor
- L195 _public function_ `TTask(FunctorType&& Functor)`
- L213 _public function_ `TTask& operator=(const TTask& Other)` — Copy assignment operator
- L228 _public function_ `TTask& operator=(TTask&& Other)` — Move assignment operator
- L245 _public function_ `template <typename... ArgumentTypes> AUTORTFM_DISABLE ReturnType operator()(ArgumentTypes&&... Arguments) const` — Call operator. Cannot be called from the closed.
- L251 _public function_ `void Reset()` — Reset the task to an unset state.
- L261 _public function_ `bool IsSet() const` — Returns true if the task holds a functor.
- L267 _public function_ `void* FunctionAddress() const` — Returns the address of the functor.
- L274 _private member_ `alignas(InlineDataAlignment) mutable FPayload Payload;` — mutable as the functor might be mutable.
- L275 _private member_ `FPayloadMethods const* PayloadMethods = nullptr;`

#### union `AutoRTFM::TTask::FPayload`  
`union FPayload`  
_L38-42_
- desc: The payload holds either the inline function data, or a pointer to the data in a heap allocation.
- L40 _public member_ `std::byte Inline[InlineDataSize];`
- L41 _public member_ `void* External;`

#### struct `AutoRTFM::TTask::FPayloadMethods`  
`struct FPayloadMethods`  
_L45-56_
- desc: Holds the function pointers for operating on the payload.
- L47 _public typedef_ `using CallFn = ReturnType(FPayload& Payload, ParameterTypes...);`
- L48 _public typedef_ `using CopyFn = void(FPayload& Dst, const FPayload& Src);`
- L49 _public typedef_ `using MoveFn = void(FPayload& Dst, FPayload& Src);`
- L50 _public typedef_ `using DestructFn = void(FPayload& Payload);`
- L52 _public member_ `CallFn* Call = nullptr;` — Calls the function held by the payload.
- L53 _public member_ `CopyFn* Copy = nullptr;` — Copies the payload.
- L54 _public member_ `MoveFn* Move = nullptr;` — Moves the payload.
- L55 _public member_ `DestructFn* Destruct = nullptr;` — Destructs the payload.

#### struct `AutoRTFM::TTask::TTraits`  
`template <typename T> struct TTraits`  
_L60-155_
- desc: Traits helper for a functor (T).
- L64 _public member_ `static constexpr bool bCanUseInline = sizeof(T) <= InlineDataSize && alignof(T) <= InlineDataAlignment;` — True iff T can fit within the inline payload, and does not require courser alignment than provided by the inline payload.
- L67 _public member_ `static constexpr bool bCopyDisabled = AutoRTFM::IsDisabled(AUTORTFM_MODE_OF_CALL(::new T(std::declval<const T&>())));` — True iff the copy constructor of the functor T is AutoRTFM-disabled.
- L70 _public member_ `static constexpr bool bMoveDisabled = AutoRTFM::IsDisabled(AUTORTFM_MODE_OF_CALL(::new T(std::declval<T&&>())));` — True iff the move constructor of the functor T is AutoRTFM-disabled.
- L73 _public member_ `static constexpr bool bDestructorDisabled = AutoRTFM::IsDisabled(AUTORTFM_MODE_OF_CALL(std::declval<T>().~T()));` — True iff the destructor of the functor T is AutoRTFM-disabled.
- L76 _public function_ `static T* FunctionFrom(FPayload& Payload)` — Returns the functor from the payload.
- L82 _public function_ `static const T* FunctionFrom(const FPayload& Payload)` — Returns the functor from the payload.
- L88 _public function_ `AUTORTFM_DISABLE static ReturnType Call(FPayload& Payload, ParameterTypes... Arguments)` — Calls the function held by the payload. Cannot be called from the closed.
- L94 _public function_ `static void Copy(FPayload& Dst, const FPayload& Src)` — Copies the payload.
- L114 _public function_ `static void Move(FPayload& Dst, FPayload& Src)` — Moves the payload.
- L134 _public function_ `static void Destruct(FPayload& Payload)` — Destructs the payload.
- L154 _public member_ `static constexpr FPayloadMethods PayloadMethods{&Call, &Copy, &Move, &Destruct};` — The methods to operate on a payload for a functor of type T.

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace AutoRTFM`
- L197 _typedef_ `using Decayed = std::decay_t<FunctorType>;` (scope `AutoRTFM::TTask::TTask`)
- L198 _typedef_ `using Traits = TTraits<Decayed>;` (scope `AutoRTFM::TTask::TTask`)

### `Source/Runtime/AutoRTFM/Public/AutoRTFM/Testing.h` (Public)


#### struct `AutoRTFM::Testing::FEnabledStateResetterScoped`  
`struct FEnabledStateResetterScoped final`  
_L51-61_
- L53 _public function_ `FEnabledStateResetterScoped(ForTheRuntime::EAutoRTFMEnabledState State) : Original(ForceSetAutoRTFMRuntime(State))`
- L54 _public function_ `~FEnabledStateResetterScoped()`
- L60 _private member_ `const ForTheRuntime::EAutoRTFMEnabledState Original;`

#### struct `AutoRTFM::Testing::FTrackingAllocator`  
`struct AUTORTFM_DISABLE FTrackingAllocator`  
_L67-97_
- desc: A utility for ensuring that allocations made by AutoRTFM are not leaked and free / reallocations pass the same size as the allocation.
- L69 _public typedef_ `using OnFailureFn = void (*)(const char* Error);`
- L74 _public prototype_ `FTrackingAllocator(OnFailureFn OnFailure);` — Constructor. OnFailure is a callback function called to report an allocation error. Only a single FTrackingAllocator can be alive at any given time.
- L78 _public prototype_ `~FTrackingAllocator();` — Destructor. Must only be called after AutoRTFM has been shutdown.
- L85 _public prototype_ `void Install(autortfm_extern_api& API, bool bRecordAllocationStackTraces = false);` — Replaces the allocator external API functions of API to install the tracking allocator. If bRecordAllocationStackTraces is true, then the stacktrace of each heap allocation will be recorded, so that allocation failures and leaks can be easily identified.
- L88 _public prototype_ `size_t TotalBytesAllocated() const;` — Returns the total number of bytes allocated by AutoRTFM.
- L92 _public prototype_ `void PrintAllocationCallstacks(size_t MaxCount = 5) const;` — Prints callstack of active allocations. Requires FTrackingAllocator to be constructed with bRecordAllocationStackTraces enabled.
- L96 _private member_ `FState* State = nullptr;`

#### struct `AutoRTFM::Testing::FCrashInfo`  
`struct FCrashInfo`  
_L103-111_
- L106 _public member_ `const char* Kind = nullptr;` — A description of the cause of the crash
- L108 _public member_ `void* ProgramCounter = nullptr;` — The program counter at the point of the crash. May be null.
- L110 _public member_ `void* Address = nullptr;` — The memory address that caused the crash. May be null.

#### Free symbols / members of external scopes

- L9 _macro_ `#define AUTORTFM_ENABLE_TEST_UTILS 0`
- L11 _macro_ `#define AUTORTFM_ENABLE_TEST_UTILS 1`
- L14 _namespace_ `namespace AutoRTFM`
- L14 _namespace_ `namespace Testing` (scope `AutoRTFM`)
- L18 _prototype_ `void AssertionFailure(const char* Expression, const char* File, int Line);` (scope `AutoRTFM::Testing`) — Implemented by the test framework, and called when AUTORTFM_TESTING_ASSERT() fails.
- L20 _macro_ `#define AUTORTFM_TESTING_ASSERT(Condition) \`
- L33 _function_ `template <typename TFunctor> static UE_AUTORTFM_FORCEINLINE void Commit(AUTORTFM_IMPLICIT_ENABLE const TFunctor& Functor)` (scope `AutoRTFM::Testing`) — Run the callback in a transaction like Transact, but abort program execution if the result is anything other than autortfm_committed. Useful for testing.
- L42 _function_ `template <typename TFunctor> static UE_AUTORTFM_FORCEINLINE void Abort(AUTORTFM_IMPLICIT_ENABLE const TFunctor& Functor)` (scope `AutoRTFM::Testing`) — Run the callback in a transaction like Transact, but abort program execution if the result is anything other than abort.
- L49 _prototype_ `ForTheRuntime::EAutoRTFMEnabledState ForceSetAutoRTFMRuntime(ForTheRuntime::EAutoRTFMEnabledState State);` (scope `AutoRTFM::Testing`) — Force set the AutoRTFM runtime state. Used in testing. Returns the old value.
- L115 _prototype_ `AUTORTFM_DISABLE void OnCrash(TTask<void(const FCrashInfo&)> Callback);` (scope `AutoRTFM::Testing`) — Sets up a exception / signal handler to call Callback on uncaught exception / fault. Can only be called once for the lifetime of the process.
