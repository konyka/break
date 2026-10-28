# Runtime / PakFile

- module root: `Source/Runtime/PakFile`
- headers: 11; symbols: 1235
- symbol kinds: class=34, delegate=7, enum=11, enumerator=41, externvar=2, function=281, macro=10, member=403, namespace=13, prototype=374, struct=38, typedef=18, union=1, variable=2
- PrivateDependencyModuleNames: Core, CoreUObject, TraceLog
- PublicDependencyModuleNames: RSA

### `Source/Runtime/PakFile/Internal/IoDispatcherFileBackendTypes.h` (Internal)


#### struct `FFileIoStoreContainerFilePartition`  
`struct FFileIoStoreContainerFilePartition`  
_L27-50_
- L29 _public prototype_ `FFileIoStoreContainerFilePartition() = default;`
- L30 _public prototype_ `FFileIoStoreContainerFilePartition(FFileIoStoreContainerFilePartition&&) = delete;`
- L31 _public prototype_ `FFileIoStoreContainerFilePartition(const FFileIoStoreContainerFilePartition&) = delete;`
- L32 _public prototype_ `~FFileIoStoreContainerFilePartition();`
- L34 _public prototype_ `FFileIoStoreContainerFilePartition& operator=(FFileIoStoreContainerFilePartition&&) = delete;`
- L35 _public prototype_ `FFileIoStoreContainerFilePartition& operator=(const FFileIoStoreContainerFilePartition&) = delete;`
- L39 _public prototype_ `IMappedFileHandle* BorrowMappedFileHandle();` — This will lazily map the file, if needed. It is thread-safe to borrow handles, but their lifetimes are tied to this partition.
- L41 _public member_ `FString FilePath;`
- L42 _public member_ `uint64 FileHandle = 0;`
- L43 _public member_ `uint64 FileSize = 0;`
- L44 _public member_ `uint32 ContainerFileIndex = 0;`
- L45 _public member_ `std::atomic<int32> StartedReadRequestsCount = 0;`
- L48 _private member_ `std::atomic<IMappedFileHandle*> MappedFileHandle = nullptr;`
- L49 _private member_ `UE::FMutex MappedFileHandleMutex;`

#### struct `FFileIoStoreContainerFile`  
`struct FFileIoStoreContainerFile`  
_L52-91_
- L54 _public prototype_ `FFileIoStoreContainerFile() = default;`
- L57 _public member_ `uint64 PartitionSize = 0;`
- L58 _public member_ `uint64 CompressionBlockSize = 0;`
- L59 _public member_ `TArray<FName> CompressionMethods;`
- L60 _public member_ `TConstArrayView<FIoStoreTocCompressedBlockEntry> CompressionBlocks;`
- L61 _public member_ `FString FilePath;`
- L62 _public member_ `FGuid EncryptionKeyGuid;`
- L63 _public member_ `FAES::FAESKey EncryptionKey;`
- L64 _public member_ `EIoContainerFlags ContainerFlags;`
- L65 _public member_ `TConstArrayView<FSHAHash> BlockSignatureTable;`
- L66 _public member_ `TArray<FFileIoStoreContainerFilePartition> Partitions;`
- L67 _public member_ `uint32 ContainerInstanceId = 0;`
- L68 _public member_ `std::atomic_int32_t RefCount{0};`
- L70 _public function_ `void GetPartitionAndOffset(uint64 TocOffset, FFileIoStoreContainerFilePartition*& OutPartition, uint64& OutOffset)`
- L77 _public function_ `void Empty()`

#### struct `FFileIoStoreBuffer`  
`struct FFileIoStoreBuffer`  
_L93-97_
- L95 _public member_ `FFileIoStoreBuffer* Next = nullptr;`
- L96 _public member_ `uint8* Memory = nullptr;`

#### struct `FFileIoStoreBlockKey`  
`struct FFileIoStoreBlockKey`  
_L99-121_

#### union `FFileIoStoreBlockKey::(anonymous)`  
``  
_L102-109_

#### struct `FFileIoStoreBlockKey::__anonef406ad2010a::(anonymous)`  
``  
_L104-107_

#### struct `FFileIoStoreBlockScatter`  
`struct FFileIoStoreBlockScatter`  
_L123-129_
- L125 _public member_ `struct FFileIoStoreResolvedRequest* Request = nullptr;`
- L126 _public member_ `uint64 DstOffset = 0;`
- L127 _public member_ `uint64 SrcOffset = 0;`
- L128 _public member_ `uint64 Size = 0;`

#### struct `FFileIoStoreCompressedBlock`  
`struct FFileIoStoreCompressedBlock`  
_L131-151_
- L133 _public member_ `FFileIoStoreCompressedBlock* Next = nullptr;`
- L134 _public member_ `FFileIoStoreBlockKey Key;`
- L135 _public member_ `FName CompressionMethod;`
- L136 _public member_ `uint64 RawOffset = uint64(-1);`
- L137 _public member_ `uint32 UncompressedSize = uint32(-1);`
- L138 _public member_ `uint32 CompressedSize = uint32(-1);`
- L139 _public member_ `uint32 RawSize = uint32(-1);`
- L140 _public member_ `uint32 RefCount = 0;`
- L141 _public member_ `uint32 UnfinishedRawBlocksCount = 0;`
- L142 _public member_ `TArray<struct FFileIoStoreReadRequest*, TInlineAllocator<2>> RawBlocks;`
- L143 _public member_ `TArray<FFileIoStoreBlockScatter, TInlineAllocator<2>> ScatterList;`
- L144 _public member_ `FFileIoStoreCompressionContext* CompressionContext = nullptr;`
- L145 _public member_ `uint8* CompressedDataBuffer = nullptr;`
- L146 _public member_ `FAES::FAESKey EncryptionKey;`
- L147 _public member_ `TConstArrayView<FSHAHash> BlockSignatureTable;`
- L148 _public member_ `const FSHAHash* SignatureHash = nullptr;`
- L149 _public member_ `bool bFailed = false;`
- L150 _public member_ `bool bCancelled = false;`

#### struct `FFileIoStoreReadRequest`  
`struct FFileIoStoreReadRequest`  
_L153-195_
- L163 _public function_ `FFileIoStoreReadRequest() : Sequence(NextSequence++) , CreationTime(FPlatformTime::Cycles64())`
- L168 _public member_ `FFileIoStoreReadRequest* Next = nullptr;`
- L169 _public member_ `FFileIoStoreReadRequest* Previous = nullptr;`
- L170 _public member_ `FFileIoStoreContainerFilePartition* ContainerFilePartition = nullptr;`
- L171 _public member_ `uint64 Offset = uint64(-1);`
- L172 _public member_ `uint64 Size = uint64(-1);`
- L173 _public member_ `FFileIoStoreBlockKey Key;`
- L174 _public member_ `FFileIoStoreBuffer* Buffer = nullptr;`
- L175 _public member_ `uint32 RefCount = 0;`
- L176 _public member_ `uint32 BufferRefCount = 0;`
- L177 _public member_ `TArray<FFileIoStoreCompressedBlock*, TInlineAllocator<8>> CompressedBlocks;`
- L178 _public member_ `const uint32 Sequence;`
- L179 _public member_ `int32 Priority = 0;`
- L180 _public member_ `uint64 CreationTime;` — Potentially used to circuit break request ordering optimizations when outstanding requests have been delayed too long
- L181 _public member_ `FFileIoStoreBlockScatter ImmediateScatter;`
- L182 _public member_ `uint32 BytesUsed = 0;`
- L183 _public member_ `bool bIsCustomRequest = false;`
- L184 _public member_ `bool bFailed = false;`
- L185 _public member_ `bool bCancelled = false;`
- L186 _public member_ `EQueueStatus QueueStatus = QueueStatus_NotInQueue;`
- L190 _public member_ `uint32 ListCookie = 0;` — For debug checks that we are in the correct owning list for our intrusive next/previous pointers
- L194 _private member_ `static uint32 NextSequence;`

#### enum `FFileIoStoreReadRequest::EQueueStatus`  
`enum EQueueStatus`  
_L155-161_
- L157 _public enumerator_ `QueueStatus_NotInQueue`
- L158 _public enumerator_ `QueueStatus_InQueue`
- L159 _public enumerator_ `QueueStatus_Started`
- L160 _public enumerator_ `QueueStatus_Completed`

#### class `FFileIoStoreReadRequestListStealingIterator`  
`class FFileIoStoreReadRequestListStealingIterator`  
_L199-276_
- desc: Iterator class for traversing and emptying a list FFileIoStoreReadRequestList at the same time
- L202 _public prototype_ `FFileIoStoreReadRequestListStealingIterator(const FFileIoStoreReadRequestListStealingIterator&) = delete;`
- L203 _public prototype_ `FFileIoStoreReadRequestListStealingIterator& operator=(const FFileIoStoreReadRequestListStealingIterator&) = delete;`
- L205 _public function_ `FFileIoStoreReadRequestListStealingIterator(FFileIoStoreReadRequestListStealingIterator&& Other)`
- L213 _public function_ `FFileIoStoreReadRequestListStealingIterator& operator=(FFileIoStoreReadRequestListStealingIterator&& Other)`
- L223 _public function_ `void operator++()`
- L228 _public function_ `FFileIoStoreReadRequest* operator*()`
- L233 _public function_ `FFileIoStoreReadRequest* operator->()`
- L238 _public function_ `explicit operator bool() const`
- L246 _private function_ `FFileIoStoreReadRequestListStealingIterator(FFileIoStoreReadRequest* InHead)`
- L259 _private function_ `void AdvanceTo(FFileIoStoreReadRequest* NewCurrent)`
- L274 _private member_ `FFileIoStoreReadRequest* Current = nullptr;`
- L275 _private member_ `FFileIoStoreReadRequest* Next = nullptr;`

#### class `FFileIoStoreReadRequestListIterator`  
`class FFileIoStoreReadRequestListIterator`  
_L278-335_
- L281 _public prototype_ `FFileIoStoreReadRequestListIterator(const FFileIoStoreReadRequestListIterator&) = default;`
- L282 _public prototype_ `FFileIoStoreReadRequestListIterator& operator=(const FFileIoStoreReadRequestListIterator&) = default;`
- L284 _public function_ `void operator++()`
- L290 _public function_ `FFileIoStoreReadRequest* operator*()`
- L295 _public function_ `FFileIoStoreReadRequest* operator->()`
- L300 _public function_ `explicit operator bool() const`
- L305 _public function_ `bool operator!=(const FFileIoStoreReadRequestListIterator& Other) const`
- L313 _private function_ `FFileIoStoreReadRequestListIterator(FFileIoStoreReadRequest* InHead)`
- L318 _private function_ `void AdvanceTo(FFileIoStoreReadRequest* NewCurrent)`
- L333 _private member_ `FFileIoStoreReadRequest* Current = nullptr;`
- L334 _private member_ `FFileIoStoreReadRequest* Next = nullptr;`

#### class `FFileIoStoreReadRequestList`  
`class FFileIoStoreReadRequestList`  
_L340-560_
- L343 _public function_ `FFileIoStoreReadRequestList() #if CHECK_IO_STORE_READ_REQUEST_LIST_MEMBERSHIP : ListCookie(++NextListCookie) #endif`
- L351 _public prototype_ `FFileIoStoreReadRequestList(const FFileIoStoreReadRequestList& Other) = delete;` — Owns the Next/Previous pointers of the FFileIoStoreReadRequests it contains so it can't be copied
- L352 _public prototype_ `FFileIoStoreReadRequestList& operator=(const FFileIoStoreReadRequestList& Other) = delete;`
- L354 _public function_ `FFileIoStoreReadRequestList(FFileIoStoreReadRequestList&& Other)`
- L368 _public function_ `FFileIoStoreReadRequestList& operator=(FFileIoStoreReadRequestList&& Other)`
- L387 _public function_ `~FFileIoStoreReadRequestList()`
- L397 _public function_ `bool IsEmpty() const`
- L403 _public function_ `FFileIoStoreReadRequestListStealingIterator Steal()` — Steal the whole list for iteration and moving the contents to other lists
- L418 _public function_ `FFileIoStoreReadRequestListIterator CreateIterator() const` — Non-stealing iterator
- L423 _public function_ `FFileIoStoreReadRequestListIterator begin() const`
- L426 _public function_ `FFileIoStoreReadRequestListIterator end() const`
- L430 _public function_ `FFileIoStoreReadRequest* PeekHead() const`
- L435 _public function_ `void Add(FFileIoStoreReadRequest* Request)`
- L458 _public function_ `void AppendSteal(FFileIoStoreReadRequestList& List)` — Remove all FFileIoStoreReadRequests from List and add them to this list
- L468 _public function_ `void Remove(FFileIoStoreReadRequest* Request)`
- L510 _public function_ `void Clear()`
- L523 _private member_ `FFileIoStoreReadRequest* Head = nullptr;`
- L524 _private member_ `FFileIoStoreReadRequest* Tail = nullptr;`
- L527 _private member_ `uint32 ListCookie;`
- L528 _private member_ `static uint32 NextListCookie;`
- L531 _private function_ `void AppendSteal(FFileIoStoreReadRequest* ListHead, FFileIoStoreReadRequest* ListTail)`

#### class `FFileIoStoreBufferAllocator`  
`class FFileIoStoreBufferAllocator`  
_L564-583_
- L567 _public function_ `FFileIoStoreBufferAllocator(FFileIoStoreStats& InStats) : Stats(InStats)`
- L572 _public prototype_ `void Initialize(uint64 MemorySize, uint64 BufferSize, uint32 BufferAlignment);`
- L573 _public prototype_ `FFileIoStoreBuffer* AllocBuffer();`
- L574 _public prototype_ `void FreeBuffer(FFileIoStoreBuffer* Buffer);`
- L575 _public function_ `uint64 GetBufferSize() const`
- L578 _private member_ `FFileIoStoreStats& Stats;`
- L579 _private member_ `uint64 BufferSize = 0;`
- L580 _private member_ `uint8* BufferMemory = nullptr;`
- L581 _private member_ `FCriticalSection BuffersCritical;`
- L582 _private member_ `FFileIoStoreBuffer* FirstFreeBuffer = nullptr;`

#### class `FFileIoStoreBlockCache`  
`class FFileIoStoreBlockCache`  
_L585-610_
- L588 _public prototype_ `FFileIoStoreBlockCache(FFileIoStoreStats& Stats);`
- L589 _public prototype_ `~FFileIoStoreBlockCache();`
- L591 _public prototype_ `void Initialize(uint64 CacheMemorySize, uint64 ReadBufferSize);`
- L592 _public prototype_ `bool Read(FFileIoStoreReadRequest* Block);`
- L593 _public prototype_ `void Store(const FFileIoStoreReadRequest* Block);`
- L604 _private member_ `FFileIoStoreStats& Stats;`
- L605 _private member_ `uint8* CacheMemory = nullptr;`
- L606 _private member_ `TMap<uint64, FCachedBlock*> CachedBlocks;`
- L607 _private member_ `FCachedBlock CacheLruHead;`
- L608 _private member_ `FCachedBlock CacheLruTail;`
- L609 _private member_ `uint64 ReadBufferSize = 0;`

#### struct `FFileIoStoreBlockCache::FCachedBlock`  
`struct FCachedBlock`  
_L596-602_
- L598 _public member_ `FCachedBlock* LruPrev = nullptr;`
- L599 _public member_ `FCachedBlock* LruNext = nullptr;`
- L600 _public member_ `uint64 Key = 0;`
- L601 _public member_ `uint8* Buffer = nullptr;`

#### struct `FFileIoStoreReadRequestSortKey`  
`struct FFileIoStoreReadRequestSortKey`  
_L612-623_
- L614 _public member_ `uint64 Offset = 0;`
- L615 _public member_ `uint64 Handle = 0;`
- L616 _public member_ `int32 Priority = 0;`
- L618 _public function_ `FFileIoStoreReadRequestSortKey()`
- L619 _public function_ `FFileIoStoreReadRequestSortKey(FFileIoStoreReadRequest* Request) : Offset(Request->Offset), Handle(Request->ContainerFilePartition->FileHandle), Priority(Request->Priority)`

#### class `FFileIoStoreOffsetSortedRequestQueue`  
`class FFileIoStoreOffsetSortedRequestQueue`  
_L626-663_
- desc: Stores FFileIoStoreReadRequest sorted by file handle & offset with a parallel list sorted by insertion order
- L629 _public prototype_ `FFileIoStoreOffsetSortedRequestQueue(int32 InPriority);`
- L630 _public prototype_ `FFileIoStoreOffsetSortedRequestQueue(const FFileIoStoreOffsetSortedRequestQueue&) = delete;`
- L631 _public prototype_ `FFileIoStoreOffsetSortedRequestQueue(FFileIoStoreOffsetSortedRequestQueue&&) = default;`
- L632 _public prototype_ `FFileIoStoreOffsetSortedRequestQueue& operator=(const FFileIoStoreOffsetSortedRequestQueue&) = delete;`
- L633 _public prototype_ `FFileIoStoreOffsetSortedRequestQueue& operator=(FFileIoStoreOffsetSortedRequestQueue&&) = default;`
- L635 _public function_ `int32 GetPriority() const`
- L636 _public function_ `bool IsEmpty() const`
- L639 _public prototype_ `TArray<FFileIoStoreReadRequest*> StealRequests();` — Remove all requests from this container and return them, for switching to a different queue scheme
- L641 _public prototype_ `TArray<FFileIoStoreReadRequest*> RemoveMisprioritizedRequests();` — Remove all requests whose priority has been changed to something other than the Priority of this queue
- L642 _public prototype_ `void RemoveCancelledRequests(TArray<FFileIoStoreReadRequest*>& OutCancelled);`
- L644 _public prototype_ `FFileIoStoreReadRequest* Pop(FFileIoStoreReadRequestSortKey LastSortKey);`
- L645 _public prototype_ `void Push(FFileIoStoreReadRequest* Request);`
- L646 _public prototype_ `int32 HandleContainerUnmounted(const FFileIoStoreContainerFile& ContainerFile);`
- L649 _private member_ `int32 Priority;`
- L650 _private member_ `int32 PeekRequestIndex = INDEX_NONE;`
- L653 _private member_ `TArray<FFileIoStoreReadRequest*> Requests;` — Requests sorted by file handle & offset
- L657 _private member_ `FFileIoStoreReadRequestList RequestsBySequence;` — Requests sorted by insertion order We store this on the heap in case we get moved, FFileIoStoreReadRequest keeps pointers to FFileIoStoreReadRequestList for debugging
- L659 _private prototype_ `FFileIoStoreReadRequest* GetNextInternal(FFileIoStoreReadRequestSortKey LastSortKey, bool bPop);`
- L661 _private function_ `static FFileIoStoreReadRequestSortKey RequestSortProjection(FFileIoStoreReadRequest* Request)`
- L662 _private prototype_ `static bool RequestSortPredicate(const FFileIoStoreReadRequestSortKey& A, const FFileIoStoreReadRequestSortKey& B);`

#### class `FFileIoStoreRequestQueue`  
`class FFileIoStoreRequestQueue`  
_L665-704_
- L668 _public prototype_ `FFileIoStoreReadRequest* Pop();`
- L669 _public prototype_ `void PopCancelled(TArray<FFileIoStoreReadRequest*>& OutCancelled);`
- L670 _public prototype_ `void Push(FFileIoStoreReadRequest& Request);` — Takes ownership of Request and rewrites its intrustive linked list pointers
- L671 _public prototype_ `void Push(FFileIoStoreReadRequestList& Requests);` — Consumes the request list and overwrites all intrustive linked list pointers
- L672 _public prototype_ `void UpdateOrder();`
- L673 _public prototype_ `void Lock();`
- L674 _public prototype_ `void Unlock();`
- L675 _public prototype_ `int32 HandleContainerUnmounted(const FFileIoStoreContainerFile& ContainerFile);`
- L678 _private function_ `static bool QueueSortFunc(const FFileIoStoreReadRequest& A, const FFileIoStoreReadRequest& B)`
- L686 _private prototype_ `void UpdateSortRequestsByOffset();` — Check if we need to switch sorting schemes based on the CVar
- L687 _private prototype_ `void PushToPriorityQueues(FFileIoStoreReadRequest* Request);`
- L688 _private function_ `static int32 QueuePriorityProjection(const FFileIoStoreOffsetSortedRequestQueue& A)`
- L690 _private member_ `bool bSortRequestsByOffset = false;` — Cached value of CVar controlling whether we use Heap or SortedPriorityQueues
- L693 _private member_ `TArray<FFileIoStoreReadRequest*> Heap;` — Heap sorted by request order
- L694 _private member_ `FCriticalSection CriticalSection;`
- L697 _private member_ `TArray<FFileIoStoreOffsetSortedRequestQueue> SortedPriorityQueues;` — Queues sorted by increasing priority
- L699 _private member_ `FFileIoStoreReadRequestSortKey LastSortKey;` — The last offset, file handle and priority we popped so that we can pop the closest forward read for the next IO operation
- L702 _private member_ `TMap<int32, uint32> RequestPriorityCounts;`

#### struct `FFileIoStoreReadRequestLink`  
`struct FFileIoStoreReadRequestLink`  
_L709-718_
- L711 _public function_ `FFileIoStoreReadRequestLink(FFileIoStoreReadRequest& InReadRequest) : ReadRequest(InReadRequest)`
- L716 _public member_ `FFileIoStoreReadRequestLink* Next = nullptr;`
- L717 _public member_ `FFileIoStoreReadRequest& ReadRequest;`

#### class `FFileIoStoreRequestAllocator`  
`class FFileIoStoreRequestAllocator`  
_L720-792_
- L723 _public function_ `int64 GetLiveReadRequestsCount() const`
- L729 _public function_ `FFileIoStoreResolvedRequest* AllocResolvedRequest( FIoRequestImpl& InDispatcherRequest, FFileIoStoreContainerFile* InContainerFile, uint64 InResolvedOffset, uint64 InResolvedSize, int32 InPriority)`
- L744 _public function_ `void Free(FFileIoStoreResolvedRequest* ResolvedRequest)`
- L749 _public function_ `FFileIoStoreReadRequest* AllocReadRequest()`
- L756 _public function_ `void Free(FFileIoStoreReadRequest* ReadRequest)`
- L763 _public function_ `FFileIoStoreCompressedBlock* AllocCompressedBlock()`
- L769 _public function_ `void Free(FFileIoStoreCompressedBlock* CompressedBlock)`
- L775 _public function_ `FFileIoStoreReadRequestLink* AllocRequestLink(FFileIoStoreReadRequest* ReadRequest)`
- L781 _public function_ `void Free(FFileIoStoreReadRequestLink* RequestLink)`
- L787 _private member_ `TIoDispatcherSingleThreadedSlabAllocator<FFileIoStoreResolvedRequest> ResolvedRequestAllocator;`
- L788 _private member_ `TIoDispatcherSingleThreadedSlabAllocator<FFileIoStoreReadRequest> ReadRequestAllocator;`
- L789 _private member_ `TIoDispatcherSingleThreadedSlabAllocator<FFileIoStoreCompressedBlock> CompressedBlockAllocator;`
- L790 _private member_ `TIoDispatcherSingleThreadedSlabAllocator<FFileIoStoreReadRequestLink> RequestLinkAllocator;`
- L791 _private member_ `int64 LiveReadRequestsCount = 0;`

#### struct `FFileIoStoreResolvedRequest`  
`struct FFileIoStoreResolvedRequest`  
_L794-863_
- L797 _public prototype_ `FFileIoStoreResolvedRequest( FIoRequestImpl& InDispatcherRequest, FFileIoStoreContainerFile* InContainerFile, uint64 InResolvedOffset, uint64 InResolvedSize, int32 InPriority);`
- L804 _public function_ `const FFileIoStoreContainerFile* GetContainerFile() const`
- L809 _public function_ `FFileIoStoreContainerFile* GetContainerFile()`
- L814 _public function_ `uint64 GetResolvedOffset() const`
- L819 _public function_ `uint64 GetResolvedSize() const`
- L824 _public function_ `int32 GetPriority() const`
- L829 _public function_ `bool HasBuffer() const`
- L835 _public function_ `void CreateBuffer(uint64 Size)`
- L841 _public function_ `FIoBuffer& GetBuffer()`
- L847 _public prototype_ `void AddReadRequestLink(FFileIoStoreReadRequestLink* ReadRequestLink);`
- L850 _private member_ `FIoRequestImpl* DispatcherRequest = nullptr;`
- L851 _private member_ `FFileIoStoreContainerFile* ContainerFile;`
- L852 _private member_ `FFileIoStoreReadRequestLink* ReadRequestsHead = nullptr;`
- L853 _private member_ `FFileIoStoreReadRequestLink* ReadRequestsTail = nullptr;`
- L854 _private member_ `const uint64 ResolvedOffset;`
- L855 _private member_ `const uint64 ResolvedSize;`
- L856 _private member_ `int32 Priority = 0;`
- L857 _private member_ `uint32 UnfinishedReadsCount = 0;`
- L858 _private member_ `bool bFailed = false;`
- L859 _private member_ `bool bCancelled = false;`

#### class `FFileIoStoreStats`  
`class FFileIoStoreStats`  
_L868-913_
- L871 _public prototype_ `FFileIoStoreStats();`
- L872 _public prototype_ `~FFileIoStoreStats();`
- L875 _public prototype_ `void OnFilesystemReadStarted(const FFileIoStoreReadRequest* Request);` — Called by the backend when underlying file system reads start
- L876 _public prototype_ `void OnFilesystemReadsStarted(const FFileIoStoreReadRequestList& Requests);`
- L878 _public prototype_ `void OnFilesystemReadCompleted(const FFileIoStoreReadRequest* Request);` — Called by the backend when underlying filesystem reads complete, possibly already decompressed on some systems
- L879 _public prototype_ `void OnFilesystemReadsCompleted(const FFileIoStoreReadRequestList& CompletedRequests);`
- L887 _private prototype_ `void OnReadRequestsQueued(const FFileIoStoreReadRequestList& Requests);`
- L888 _private prototype_ `void OnReadRequestsCompleted(const FFileIoStoreReadRequestList& Requests);`
- L889 _private prototype_ `void OnDecompressQueued(const FFileIoStoreCompressedBlock* CompressedBlock);`
- L890 _private prototype_ `void OnDecompressComplete(const FFileIoStoreCompressedBlock* CompressedBlock);`
- L893 _private prototype_ `void OnBytesScattered(int64 BytesScattered);` — Bytes were copied into the buffer provided to users of the io system
- L895 _private prototype_ `void OnBlockCacheStore(uint64 NumBytes);` — Record stats for block cache hit/miss rate & data throughput
- L896 _private prototype_ `void OnBlockCacheHit(uint64 NumBytes);`
- L897 _private prototype_ `void OnBlockCacheMiss(uint64 NumBytes);`
- L900 _private prototype_ `void OnSequentialRead();` — A read was started without seeking
- L902 _private prototype_ `void OnSeek(uint64 LastOffset, uint64 NewOffset);` — A read was started and was either a forward or reverse seek
- L904 _private prototype_ `void OnHandleChangeSeek();` — A read was started from a different file handle from the last one we used
- L906 _private prototype_ `void OnTocMounted(uint64 AllocatedSize);`
- L907 _private prototype_ `void OnTocUnmounted(uint64 AllocatedSize);`
- L909 _private prototype_ `void OnBufferReleased();`
- L910 _private prototype_ `void OnBufferAllocated();`
- L912 _private member_ `UE::FIoDispatcherFilesystemStats Stats;`
- L918 _public function_ `void OnFilesystemReadStarted(const FFileIoStoreReadRequest* Request)`
- L919 _public function_ `void OnFilesystemReadsStarted(const FFileIoStoreReadRequestList& Requests)`
- L920 _public function_ `void OnFilesystemReadCompleted(const FFileIoStoreReadRequest* Request)`
- L921 _public function_ `void OnFilesystemReadsCompleted(const FFileIoStoreReadRequestList& CompletedRequests)`
- L929 _private function_ `void OnReadRequestsQueued(const FFileIoStoreReadRequestList& Requests)`
- L930 _private function_ `void OnReadRequestsCompleted(const FFileIoStoreReadRequestList& Requests)`
- L931 _private function_ `void OnDecompressQueued(const FFileIoStoreCompressedBlock* CompressedBlock)`
- L932 _private function_ `void OnDecompressComplete(const FFileIoStoreCompressedBlock* CompressedBlock)`
- L933 _private function_ `void OnBytesScattered(int64 BytesScattered)`
- L934 _private function_ `void OnBlockCacheStore(uint64 NumBytes)`
- L935 _private function_ `void OnBlockCacheHit(uint64 NumBytes)`
- L936 _private function_ `void OnBlockCacheMiss(uint64 NumBytes)`
- L937 _private function_ `void OnTocMounted(uint64 AllocatedSize)`
- L938 _private function_ `void OnTocUnmounted(uint64 AllocatedSize)`
- L939 _private function_ `void OnBufferReleased()`
- L940 _private function_ `void OnBufferAllocated()`

#### class `FFileIoStoreStats`  
`class FFileIoStoreStats`  
_L915-941_
- L871 _public prototype_ `FFileIoStoreStats();`
- L872 _public prototype_ `~FFileIoStoreStats();`
- L875 _public prototype_ `void OnFilesystemReadStarted(const FFileIoStoreReadRequest* Request);` — Called by the backend when underlying file system reads start
- L876 _public prototype_ `void OnFilesystemReadsStarted(const FFileIoStoreReadRequestList& Requests);`
- L878 _public prototype_ `void OnFilesystemReadCompleted(const FFileIoStoreReadRequest* Request);` — Called by the backend when underlying filesystem reads complete, possibly already decompressed on some systems
- L879 _public prototype_ `void OnFilesystemReadsCompleted(const FFileIoStoreReadRequestList& CompletedRequests);`
- L887 _private prototype_ `void OnReadRequestsQueued(const FFileIoStoreReadRequestList& Requests);`
- L888 _private prototype_ `void OnReadRequestsCompleted(const FFileIoStoreReadRequestList& Requests);`
- L889 _private prototype_ `void OnDecompressQueued(const FFileIoStoreCompressedBlock* CompressedBlock);`
- L890 _private prototype_ `void OnDecompressComplete(const FFileIoStoreCompressedBlock* CompressedBlock);`
- L893 _private prototype_ `void OnBytesScattered(int64 BytesScattered);` — Bytes were copied into the buffer provided to users of the io system
- L895 _private prototype_ `void OnBlockCacheStore(uint64 NumBytes);` — Record stats for block cache hit/miss rate & data throughput
- L896 _private prototype_ `void OnBlockCacheHit(uint64 NumBytes);`
- L897 _private prototype_ `void OnBlockCacheMiss(uint64 NumBytes);`
- L900 _private prototype_ `void OnSequentialRead();` — A read was started without seeking
- L902 _private prototype_ `void OnSeek(uint64 LastOffset, uint64 NewOffset);` — A read was started and was either a forward or reverse seek
- L904 _private prototype_ `void OnHandleChangeSeek();` — A read was started from a different file handle from the last one we used
- L906 _private prototype_ `void OnTocMounted(uint64 AllocatedSize);`
- L907 _private prototype_ `void OnTocUnmounted(uint64 AllocatedSize);`
- L909 _private prototype_ `void OnBufferReleased();`
- L910 _private prototype_ `void OnBufferAllocated();`
- L912 _private member_ `UE::FIoDispatcherFilesystemStats Stats;`
- L918 _public function_ `void OnFilesystemReadStarted(const FFileIoStoreReadRequest* Request)`
- L919 _public function_ `void OnFilesystemReadsStarted(const FFileIoStoreReadRequestList& Requests)`
- L920 _public function_ `void OnFilesystemReadCompleted(const FFileIoStoreReadRequest* Request)`
- L921 _public function_ `void OnFilesystemReadsCompleted(const FFileIoStoreReadRequestList& CompletedRequests)`
- L929 _private function_ `void OnReadRequestsQueued(const FFileIoStoreReadRequestList& Requests)`
- L930 _private function_ `void OnReadRequestsCompleted(const FFileIoStoreReadRequestList& Requests)`
- L931 _private function_ `void OnDecompressQueued(const FFileIoStoreCompressedBlock* CompressedBlock)`
- L932 _private function_ `void OnDecompressComplete(const FFileIoStoreCompressedBlock* CompressedBlock)`
- L933 _private function_ `void OnBytesScattered(int64 BytesScattered)`
- L934 _private function_ `void OnBlockCacheStore(uint64 NumBytes)`
- L935 _private function_ `void OnBlockCacheHit(uint64 NumBytes)`
- L936 _private function_ `void OnBlockCacheMiss(uint64 NumBytes)`
- L937 _private function_ `void OnTocMounted(uint64 AllocatedSize)`
- L938 _private function_ `void OnTocUnmounted(uint64 AllocatedSize)`
- L939 _private function_ `void OnBufferReleased()`
- L940 _private function_ `void OnBufferAllocated()`

#### struct `FInitializePlatformFileIoStoreParams`  
`struct FInitializePlatformFileIoStoreParams`  
_L944-951_
- L946 _public member_ `const FWakeUpIoDispatcherThreadDelegate* WakeUpDispatcherThreadDelegate = nullptr;`
- L947 _public member_ `FFileIoStoreRequestAllocator* RequestAllocator = nullptr;`
- L948 _public member_ `FFileIoStoreBufferAllocator* BufferAllocator = nullptr;`
- L949 _public member_ `FFileIoStoreBlockCache* BlockCache = nullptr;`
- L950 _public member_ `FFileIoStoreStats* Stats = nullptr;`

#### class `IPlatformFileIoStore`  
`class IPlatformFileIoStore`  
_L953-968_
- L956 _public prototype_ `virtual ~IPlatformFileIoStore() = default;`
- L957 _public prototype_ `virtual void Initialize(const FInitializePlatformFileIoStoreParams& Params) = 0;`
- L959 _public prototype_ `virtual bool OpenContainer(const TCHAR* ContainerFilePath, uint64& ContainerFileHandle, uint64& ContainerFileSize) = 0;`
- L960 _public prototype_ `virtual void CloseContainer(uint64 ContainerFileHandle) = 0;`
- L962 _public prototype_ `virtual bool CreateCustomRequests(FFileIoStoreResolvedRequest& ResolvedRequest, FFileIoStoreReadRequestList& OutRequests) = 0;`
- L963 _public prototype_ `virtual bool StartRequests(FFileIoStoreRequestQueue& RequestQueue) = 0;`
- L964 _public prototype_ `virtual void GetCompletedRequests(FFileIoStoreReadRequestList& OutRequests) = 0;`
- L966 _public prototype_ `virtual void ServiceNotify() = 0;`
- L967 _public prototype_ `virtual void ServiceWait() = 0;`

#### class `IPlatformFileIoStoreModule`  
`class IPlatformFileIoStoreModule : public IModuleInterface`  
_L970-974_
- inherits: `IModuleInterface`
- L973 _public prototype_ `virtual TUniquePtr<IPlatformFileIoStore> CreatePlatformFileIoStore() = 0;`

#### Free symbols / members of external scopes

- L16 _macro_ `#define PLATFORM_IMPLEMENTS_IO 0`
- L20 _macro_ `#define PLATFORM_IODISPATCHER_MODULE UE_STRINGIZE(UE_JOIN(PLATFORM_HEADER_NAME, PlatformIoDispatcher))`
- L23 _macro_ `#define UE_FILEIOSTORE_STATS_ENABLED (COUNTERSTRACE_ENABLED || CSV_PROFILER_STATS)`
- L105 _member_ `uint32 FileIndex;` (scope `FFileIoStoreBlockKey::__anonef406ad2010a::__anonef406ad20208`)
- L106 _member_ `uint32 BlockIndex;` (scope `FFileIoStoreBlockKey::__anonef406ad2010a::__anonef406ad20208`)
- L108 _member_ `uint64 Hash;` (scope `FFileIoStoreBlockKey::__anonef406ad2010a`)
- L112 _function_ `friend bool operator==(const FFileIoStoreBlockKey& A, const FFileIoStoreBlockKey& B)`
- L117 _function_ `friend uint32 GetTypeHash(const FFileIoStoreBlockKey& Key)`
- L197 _macro_ `#define CHECK_IO_STORE_READ_REQUEST_LIST_MEMBERSHIP (DO_CHECK && 0)`
- L707 _typedef_ `template <typename T, uint16 SlabSize = 4096> using TIoDispatcherSingleThreadedSlabAllocator = TSingleThreadedSlabAllocator<T, SlabSize>;`
- L977 _prototype_ `TUniquePtr<IPlatformFileIoStore> CreatePlatformFileIoStore();`

### `Source/Runtime/PakFile/Private/FileIoDispatcherBackend.h` (Private)


#### enum `UE::IoStore::ETocMountOptions`  
`enum class ETocMountOptions`  
_L15-21_
- L17 _public enumerator_ `None = 0`
- L19 _public enumerator_ `WithSoftReferences = 1 << 0` — Make soft references available
- L20 _public enumerator_ `Last = WithSoftReferences`

#### class `UE::IoStore::IFileIoDispatcherBackend`  
`class IFileIoDispatcherBackend : public IIoDispatcherBackend`  
_L24-38_
- inherits: `IIoDispatcherBackend`
- L28 _public prototype_ `virtual ~IFileIoDispatcherBackend() = default;`
- L30 _public prototype_ `virtual TIoStatusOr<FIoContainerHeader> Mount( const TCHAR* TocPath, int32 Order, const FGuid& EncryptionKeyGuid, const FAES::FAESKey& EncryptionKey, ETocMountOptions Options = ETocMountOptions::None) = 0;`
- L36 _public prototype_ `virtual bool Unmount(const TCHAR* TocPath) = 0;`
- L37 _public prototype_ `virtual void ReopenAllFileHandles() = 0;`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace IoStore` (scope `UE`)
- L22 _prototype_ `ENUM_CLASS_FLAGS(ETocMountOptions);` (scope `UE::IoStore`)
- L40 _prototype_ `TSharedPtr<IFileIoDispatcherBackend> MakeFileIoDispatcherBackend();` (scope `UE::IoStore`)
- L44 _function_ `inline const TCHAR* LexToString(UE::IoStore::ETocMountOptions MountOptions)`

### `Source/Runtime/PakFile/Private/FilePackageStore.h` (Private)


#### struct `UE::FilePackageStorePrivate::FMountedDataRange`  
`struct FMountedDataRange`  
_L17-23_
- L19 _public function_ `bool Contains(uint32 Offset) const`
- L21 _public member_ `uint32 Begin = 0;`
- L22 _public member_ `uint32 End = 0;`

#### struct `UE::FilePackageStorePrivate::FMountedContainer`  
`struct FMountedContainer`  
_L25-32_
- L27 _public member_ `FIoContainerHeader* ContainerHeader;`
- L28 _public member_ `uint32 Order;`
- L29 _public member_ `uint32 Sequence;`
- L30 _public member_ `uint32 NumMountedPackages = 0;`
- L31 _public member_ `FMountedDataRange EntryDataRange;`

#### struct `UE::FilePackageStorePrivate::FEntryHandle`  
`struct FEntryHandle`  
_L34-47_
- L36 _public member_ `static constexpr uint32 OffsetBits = 29;`
- L38 _public member_ `uint32 Offset : OffsetBits;`
- L39 _public member_ `uint32 HasPackageIds : 1;`
- L40 _public member_ `uint32 HasShaderMaps : 1;`
- L41 _public member_ `uint32 HasSoftRefs : 1;`
- L43 _public function_ `FEntryHandle()`

#### class `UE::FilePackageStorePrivate::FPackageIdMap`  
`class FPackageIdMap`  
_L50-75_
- desc: Memory-optimized immutable FPackageId -> FEntryHandle hash map
- L53 _public prototype_ `FPackageIdMap() = default;`
- L54 _public prototype_ `explicit FPackageIdMap(TArray<TPair<FPackageId, FEntryHandle>>&& Pairs);`
- L55 _public function_ `FPackageIdMap(FPackageIdMap&& O)`
- L56 _public prototype_ `FPackageIdMap& operator=(FPackageIdMap&& O);`
- L57 _public function_ `~FPackageIdMap()`
- L59 _public prototype_ `void Empty();`
- L60 _public prototype_ `const FEntryHandle* Find(FPackageId Key) const;`
- L61 _public function_ `uint32 GetCapacity() const`
- L62 _public prototype_ `uint64 GetAllocatedSize() const;`
- L66 _private member_ `uint32 MaxValues = 0;`
- L67 _private member_ `uint32 SlotBits = 0;`
- L68 _private member_ `uint32* Slots = nullptr;`
- L69 _private member_ `uint16* Values = nullptr;`
- L71 _private function_ `uint32 NumSlots() const`

#### struct `UE::FilePackageStorePrivate::FUncookedPackage`  
`struct FUncookedPackage`  
_L77-81_
- L79 _public member_ `FName PackageName;`
- L80 _public member_ `EPackageExtension HeaderExtension;`

#### class `FFilePackageStoreBackend`  
`class FFilePackageStoreBackend final : public IPackageStoreBackend`  
_L88-139_
- inherits: `IPackageStoreBackend`
- desc: File/container based package store.
- L91 _public function_ `virtual void OnMounted(TSharedRef<const FPackageStoreBackendContext>) override`
- L92 _public prototype_ `virtual void BeginRead() override;`
- L93 _public prototype_ `virtual void EndRead() override;`
- L94 _public prototype_ `virtual EPackageStoreEntryStatus GetPackageStoreEntry(FPackageId PackageId, FName PackageName, FPackageStoreEntry& OutPackageStoreEntry) override;`
- L95 _public prototype_ `virtual bool GetPackageRedirectInfo(FPackageId PackageId, FName& OutSourcePackageName, FPackageId& OutRedirectedToPackageId) override;`
- L96 _public prototype_ `virtual TConstArrayView<uint32> GetSoftReferences(FPackageId PackageId, TConstArrayView<FPackageId>& OutPackageIds) override;`
- L98 _public prototype_ `void Mount(FIoContainerHeader* ContainerHeader, uint32 Order);`
- L99 _public prototype_ `void Unmount(const FIoContainerHeader* ContainerHeader);`
- L102 _private typedef_ `using FMountedDataRange = UE::FilePackageStorePrivate::FMountedDataRange;`
- L103 _private typedef_ `using FMountedContainer = UE::FilePackageStorePrivate::FMountedContainer;`
- L104 _private typedef_ `using FEntryHandle = UE::FilePackageStorePrivate::FEntryHandle;`
- L105 _private typedef_ `using FPackageIdMap = UE::FilePackageStorePrivate::FPackageIdMap;`
- L106 _private typedef_ `using FUncookedPackage = UE::FilePackageStorePrivate::FUncookedPackage;`
- L108 _private member_ `FRWLock EntriesLock;`
- L109 _private member_ `FCriticalSection UpdateLock;`
- L110 _private member_ `TArray<FMountedContainer> MountedContainers;`
- L111 _private member_ `TAtomic<uint32> NextSequence{ 0 };`
- L113 _private member_ `FPackageIdMap PackageEntries;`
- L114 _private member_ `TArray<uint32> EntryData;`
- L115 _private member_ `TMap<FPackageId, TTuple<FName, FPackageId>> RedirectsPackageMap;`
- L116 _private member_ `TMap<FPackageId, FName> LocalizedPackages;`
- L117 _private member_ `bool bNeedsContainerUpdate = false;`
- L120 _private member_ `FDelegateHandle OnContentPathMountedDelegateHandle;`
- L121 _private member_ `FDelegateHandle OnContentPathDismountedDelegateHandle;`
- L122 _private member_ `FCriticalSection UncookedPackageRootsLock;`
- L123 _private member_ `TSet<FString> PendingAddUncookedPackageRoots;`
- L124 _private member_ `TSet<FString> PendingRemoveUncookedPackageRoots;`
- L125 _private member_ `TMap<FPackageId, FUncookedPackage> UncookedPackagesMap;`
- L126 _private member_ `TMap<FPackageId, const FFilePackageStoreEntry*> OptionalSegmentStoreEntriesMap;`
- L127 _private member_ `bool bNeedsUncookedPackagesUpdate = false;`
- L129 _private prototype_ `uint64 AddUncookedPackagesFromRoot(const FString& RootPath);`
- L130 _private prototype_ `uint64 RemoveUncookedPackagesFromRoot(const TSet<FString>& RootPath);`
- L133 _private prototype_ `void Update();`
- L134 _private prototype_ `FEntryHandle AddNewEntryData(const FFilePackageStoreEntry& Entry, const FFilePackageStoreEntrySoftReferences* SoftReferences);`
- L135 _private prototype_ `FEntryHandle AddOldEntryData(FEntryHandle OldHandle, TConstArrayView<uint32> OldEntryData);`
- L136 _private prototype_ `TConstArrayView<FPackageId> GetImportedPackages(FEntryHandle Handle);`
- L137 _private prototype_ `TConstArrayView<FShaderHash> GetShaderHashes(FEntryHandle Handle);`
- L138 _private prototype_ `TConstArrayView<uint32> GetSoftReferenceIndices(FEntryHandle Handle);`

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace FilePackageStorePrivate` (scope `UE`)

### `Source/Runtime/PakFile/Private/GenericPlatformIoDispatcher.h` (Private)


#### class `FGenericFileIoStoreEventQueue`  
`class FGenericFileIoStoreEventQueue`  
_L14-24_
- L17 _public prototype_ `FGenericFileIoStoreEventQueue();`
- L18 _public prototype_ `~FGenericFileIoStoreEventQueue();`
- L19 _public prototype_ `void ServiceNotify();`
- L20 _public prototype_ `void ServiceWait();`
- L23 _private member_ `FEvent* ServiceEvent = nullptr;`

#### class `FGenericFileIoStoreImpl`  
`class FGenericFileIoStoreImpl : public IPlatformFileIoStore`  
_L26-68_
- inherits: `IPlatformFileIoStore`
- L29 _public prototype_ `FGenericFileIoStoreImpl();`
- L30 _public prototype_ `~FGenericFileIoStoreImpl();`
- L31 _public function_ `void Initialize(const FInitializePlatformFileIoStoreParams& Params) override`
- L38 _public prototype_ `bool OpenContainer(const TCHAR* ContainerFilePath, uint64& ContainerFileHandle, uint64& ContainerFileSize) override;`
- L39 _public prototype_ `void CloseContainer(uint64 ContainerFileHandle) override;`
- L40 _public function_ `bool CreateCustomRequests(FFileIoStoreResolvedRequest& ResolvedRequest, FFileIoStoreReadRequestList& OutRequests) override`
- L44 _public prototype_ `bool StartRequests(FFileIoStoreRequestQueue& RequestQueue) override;`
- L45 _public prototype_ `void GetCompletedRequests(FFileIoStoreReadRequestList& OutRequests) override;`
- L47 _public function_ `virtual void ServiceNotify() override`
- L51 _public function_ `virtual void ServiceWait() override`
- L56 _private member_ `const FWakeUpIoDispatcherThreadDelegate* WakeUpDispatcherThreadDelegate = nullptr;`
- L57 _private member_ `FGenericFileIoStoreEventQueue EventQueue;`
- L58 _private member_ `FFileIoStoreBufferAllocator* BufferAllocator = nullptr;`
- L59 _private member_ `FFileIoStoreBlockCache* BlockCache = nullptr;`
- L60 _private member_ `FFileIoStoreStats* Stats = nullptr;`
- L61 _private member_ `FFileIoStoreBuffer* AcquiredBuffer = nullptr;`
- L63 _private member_ `FCriticalSection CompletedRequestsCritical;`
- L64 _private member_ `FFileIoStoreReadRequestList CompletedRequests;`
- L66 _private member_ `uint64 PreviousFileHandle = 0;`

### `Source/Runtime/PakFile/Private/IoDispatcherFileBackend.h` (Private)


#### struct `FFileIoStoreCompressionContext`  
`struct FFileIoStoreCompressionContext`  
_L25-30_
- L27 _public member_ `FFileIoStoreCompressionContext* Next = nullptr;`
- L28 _public member_ `uint64 UncompressedBufferSize = 0;`
- L29 _public member_ `uint8* UncompressedBuffer = nullptr;`

#### class `FFileIoStoreReader`  
`class FFileIoStoreReader`  
_L32-84_
- L35 _public prototype_ `FFileIoStoreReader(IPlatformFileIoStore& InPlatformImpl, FFileIoStoreStats& InStats);`
- L36 _public prototype_ `~FFileIoStoreReader();`
- L37 _public prototype_ `FIoStatus Initialize(const TCHAR* InTocFilePath, int32 Order);`
- L38 _public function_ `uint32 GetContainerInstanceId() const`
- L42 _public prototype_ `FIoStatus Close();`
- L43 _public prototype_ `bool DoesChunkExist(const FIoChunkId& ChunkId) const;`
- L44 _public prototype_ `TIoStatusOr<uint64> GetSizeForChunk(const FIoChunkId& ChunkId) const;`
- L45 _public prototype_ `const FIoOffsetAndLength* Resolve(const FIoChunkId& ChunkId) const;`
- L46 _public function_ `FFileIoStoreContainerFile* GetContainerFile()`
- L47 _public function_ `const FFileIoStoreContainerFile* GetContainerFile() const`
- L48 _public prototype_ `TUniquePtr<IMappedFileHandle> GetMappedContainerFileHandle(uint64 TocOffset);`
- L49 _public function_ `const FIoContainerId& GetContainerId() const`
- L50 _public function_ `int32 GetOrder() const`
- L51 _public function_ `bool IsEncrypted() const`
- L52 _public function_ `bool IsSigned() const`
- L53 _public function_ `const FGuid& GetEncryptionKeyGuid() const`
- L54 _public function_ `void SetEncryptionKey(const FAES::FAESKey& Key)`
- L55 _public function_ `const FAES::FAESKey& GetEncryptionKey() const`
- L56 _public prototype_ `TIoStatusOr<FIoContainerHeader> ReadContainerHeader(bool bReadSoftRefs) const;`
- L57 _public prototype_ `void ReopenAllFileHandles();`
- L60 _private prototype_ `const FIoOffsetAndLength* FindChunkInternal(const FIoChunkId& ChunkId) const;`
- L61 _private prototype_ `uint64 GetTocAllocatedSize() const;`
- L63 _private member_ `IPlatformFileIoStore& PlatformImpl;`
- L64 _private member_ `FFileIoStoreStats& Stats;`
- L72 _private member_ `FPerfectHashMap PerfectHashMap;`
- L73 _private member_ `TMap<FIoChunkId, FIoOffsetAndLength> TocImperfectHashMapFallback;`
- L74 _private member_ `FFileIoStoreContainerFile ContainerFile;`
- L75 _private member_ `FIoContainerId ContainerId;`
- L77 _private member_ `FIoStoreTocResourceStorage DataContainer;` — Owns the data for ArrayViews in ContainerFile and in PerfectHash map
- L78 _private member_ `int32 Order;`
- L79 _private member_ `bool bClosed = false;`
- L80 _private member_ `bool bHasPerfectHashMap = false;`
- L82 _private member_ `static TAtomic<uint32> GlobalPartitionIndex;`
- L83 _private member_ `static TAtomic<uint32> GlobalContainerInstanceId;`

#### struct `FFileIoStoreReader::FPerfectHashMap`  
`struct FPerfectHashMap`  
_L66-71_
- L68 _public member_ `TConstArrayView<int32> TocChunkHashSeeds;`
- L69 _public member_ `TConstArrayView<FIoChunkId> TocChunkIds;`
- L70 _public member_ `TConstArrayView<FIoOffsetAndLength> TocOffsetAndLengths;`

#### class `FFileIoStoreRequestTracker`  
`class FFileIoStoreRequestTracker`  
_L86-108_
- L89 _public prototype_ `FFileIoStoreRequestTracker(FFileIoStoreRequestAllocator& RequestAllocator, FFileIoStoreRequestQueue& RequestQueue);`
- L90 _public prototype_ `~FFileIoStoreRequestTracker();`
- L92 _public prototype_ `FFileIoStoreCompressedBlock* FindOrAddCompressedBlock(FFileIoStoreBlockKey Key, bool& bOutWasAdded);`
- L93 _public prototype_ `void RemoveCompressedBlock(const FFileIoStoreCompressedBlock* CompressedBlock, bool bRemoveFromCancel = false);`
- L94 _public prototype_ `FFileIoStoreReadRequest* FindOrAddRawBlock(FFileIoStoreBlockKey Key, bool& bOutWasAdded);`
- L95 _public prototype_ `void RemoveRawBlock(const FFileIoStoreReadRequest* RawBlock, bool bRemoveFromCancel = false);`
- L96 _public prototype_ `void AddReadRequestsToResolvedRequest(FFileIoStoreCompressedBlock* CompressedBlock, FFileIoStoreResolvedRequest& ResolvedRequest);`
- L97 _public prototype_ `void AddReadRequestsToResolvedRequest(const FFileIoStoreReadRequestList& Requests, FFileIoStoreResolvedRequest& ResolvedRequest);`
- L98 _public prototype_ `bool CancelIoRequest(FFileIoStoreResolvedRequest& ResolvedRequest);`
- L99 _public prototype_ `void UpdatePriorityForIoRequest(FFileIoStoreResolvedRequest& ResolvedRequest);`
- L100 _public prototype_ `void ReleaseIoRequestReferences(FFileIoStoreResolvedRequest& ResolvedRequest);`
- L101 _public prototype_ `int64 GetLiveReadRequestsCount() const;`
- L104 _private member_ `FFileIoStoreRequestAllocator& RequestAllocator;`
- L105 _private member_ `FFileIoStoreRequestQueue& RequestQueue;`
- L106 _private member_ `TMap<FFileIoStoreBlockKey, FFileIoStoreCompressedBlock*> CompressedBlocksMap;`
- L107 _private member_ `TMap<FFileIoStoreBlockKey, FFileIoStoreReadRequest*> RawBlocksMap;`

#### class `FFileIoStoreReadersToUnload`  
`class FFileIoStoreReadersToUnload`  
_L110-121_
- L113 _public prototype_ `FFileIoStoreReadersToUnload() = default;`
- L114 _public prototype_ `~FFileIoStoreReadersToUnload();`
- L115 _public prototype_ `void Add(TUniquePtr<FFileIoStoreReader>&& Reader);`
- L116 _public prototype_ `void TryUnload();`
- L119 _private member_ `TArray<TUniquePtr<FFileIoStoreReader>> Readers;`
- L120 _private member_ `UE::FMutex Mutex;`

#### class `FFileIoStore`  
`class FFileIoStore final : public FRunnable , public UE::IoStore::IFileIoDispatcherBackend`  
_L123-193_
- inherits: `FRunnable,UE::IoStore::IFileIoDispatcherBackend`
- L128 _public prototype_ `FFileIoStore(TUniquePtr<IPlatformFileIoStore>&& PlatformImpl);`
- L129 _public prototype_ `~FFileIoStore();`
- L130 _public prototype_ `void Initialize(TSharedRef<const FIoDispatcherBackendContext> Context) override;`
- L131 _public prototype_ `void Shutdown() override;`
- L132 _public prototype_ `virtual TIoStatusOr<FIoContainerHeader> Mount( const TCHAR* InTocPath, int32 Order, const FGuid& EncryptionKeyGuid, const FAES::FAESKey& EncryptionKey, UE::IoStore::ETocMountOptions Options) override;`
- L138 _public prototype_ `virtual bool Unmount(const TCHAR* InTocPath) override;`
- L139 _public prototype_ `void ResolveIoRequests(FIoRequestList Requests, FIoRequestList& OutUnresolved) override;`
- L140 _public prototype_ `void CancelIoRequest(FIoRequestImpl* Request) override;`
- L141 _public prototype_ `void UpdatePriorityForIoRequest(FIoRequestImpl* Request) override;`
- L142 _public prototype_ `bool DoesChunkExist(const FIoChunkId& ChunkId) const override;`
- L143 _public prototype_ `TIoStatusOr<uint64> GetSizeForChunk(const FIoChunkId& ChunkId) const;`
- L144 _public prototype_ `FIoRequestImpl* GetCompletedIoRequests() override;`
- L145 _public prototype_ `TIoStatusOr<FIoMappedRegion> OpenMapped(const FIoChunkId& ChunkId, const FIoReadOptions& Options) override;`
- L146 _public prototype_ `const TCHAR* GetName() const override;`
- L147 _public prototype_ `virtual void ReopenAllFileHandles() override;`
- L149 _public prototype_ `virtual bool Init() override;`
- L150 _public prototype_ `virtual uint32 Run() override;`
- L151 _public prototype_ `virtual void Stop() override;`
- L153 _public prototype_ `uint32 GetThreadId() const;`
- L157 _private prototype_ `bool Resolve(FIoRequestImpl* Request);`
- L158 _private prototype_ `void OnNewPendingRequestsAdded();`
- L159 _private prototype_ `void ReadBlocks(FFileIoStoreResolvedRequest& ResolvedRequest);`
- L160 _private prototype_ `void FreeBuffer(FFileIoStoreBuffer& Buffer);`
- L161 _private prototype_ `FFileIoStoreCompressionContext* AllocCompressionContext();`
- L162 _private prototype_ `void FreeCompressionContext(FFileIoStoreCompressionContext* CompressionContext);`
- L163 _private prototype_ `void ScatterBlock(FFileIoStoreCompressedBlock* CompressedBlock, bool bIsAsync);`
- L164 _private prototype_ `void CompleteDispatcherRequest(FFileIoStoreResolvedRequest* ResolvedRequest);`
- L165 _private prototype_ `void FinalizeCompressedBlock(FFileIoStoreCompressedBlock* CompressedBlock);`
- L166 _private prototype_ `void StopThread();`
- L168 _private member_ `uint64 ReadBufferSize = 0;`
- L169 _private member_ `TSharedPtr<const FIoDispatcherBackendContext> BackendContext;`
- L170 _private member_ `FFileIoStoreStats Stats;`
- L171 _private member_ `FFileIoStoreBlockCache BlockCache;`
- L172 _private member_ `FFileIoStoreBufferAllocator BufferAllocator;`
- L173 _private member_ `FFileIoStoreRequestAllocator RequestAllocator;`
- L174 _private member_ `FFileIoStoreRequestQueue RequestQueue;`
- L175 _private member_ `FFileIoStoreRequestTracker RequestTracker;`
- L176 _private member_ `TUniquePtr<IPlatformFileIoStore> PlatformImpl;`
- L177 _private member_ `FFileIoStoreReadersToUnload IoStoreReadersToUnload;`
- L178 _private member_ `FRunnableThread* Thread = nullptr;`
- L179 _private member_ `bool bIsMultithreaded;`
- L180 _private member_ `TAtomic<bool> bStopRequested{ false };`
- L181 _private member_ `mutable FRWLock IoStoreReadersLock;`
- L182 _private member_ `TArray<TUniquePtr<FFileIoStoreReader>> IoStoreReaders;`
- L183 _private member_ `TArray<TUniquePtr<FFileIoStoreCompressionContext>> CompressionContexts;`
- L184 _private member_ `TSpscQueue<UE::Tasks::FTask> DecompressionTasks;`
- L185 _private member_ `FFileIoStoreCompressionContext* FirstFreeCompressionContext = nullptr;`
- L186 _private member_ `FFileIoStoreCompressedBlock* ReadyForDecompressionHead = nullptr;`
- L187 _private member_ `FFileIoStoreCompressedBlock* ReadyForDecompressionTail = nullptr;`
- L188 _private member_ `FCriticalSection DecompressedBlocksCritical;`
- L189 _private member_ `FFileIoStoreCompressedBlock* FirstDecompressedBlock = nullptr;`
- L190 _private member_ `FIoRequestImpl* CompletedRequestsHead = nullptr;`
- L191 _private member_ `FIoRequestImpl* CompletedRequestsTail = nullptr;`
- L192 _private member_ `FDelegateHandle OversubscriptionLimitReached;`

#### Free symbols / members of external scopes

- L195 _prototype_ `TSharedRef<FFileIoStore> CreateIoDispatcherFileBackend();`

### `Source/Runtime/PakFile/Private/PakFile.h` (Private)


#### Free symbols / members of external scopes

- L9 _externvar_ `extern bool GPak_ValidateDirectoryTreeSearchConsistency;`
- L11 _externvar_ `extern bool GPak_UseDirectoryTreeForPakSearch;`

### `Source/Runtime/PakFile/Private/PakFile.inl` (Private)


#### Free symbols / members of external scopes

- L11 _function_ `template <typename ShouldVisitFunc, class ContainerType> void FPakFile::FindFilesAtPathInIndex(const FDirectoryIndex& TargetIndex, const FDirectoryTreeIndex& TargetTreeIndex, ContainerType& OutFiles, const FString& FullSearchPath, const FVisitFilter<ShouldVisitFunc>& VisitFilter) const` (scope `FPakFile`) — Search the given FDirectoryIndex for all files under the given Directory.  Helper for FindFilesAtPath, called separately on the DirectoryIndex or Pruned DirectoryIndex. Does not use FScopedPakDirectoryIndexAccess internally; caller is responsible for calling from within a lock. Returned paths are full paths (include the mount point)
- L68 _function_ `template <typename ShouldVisitFunc, class ContainerType> void FPakFile::FindFilesAtPathInTreeIndexInternal(FStringView RelSearchPath, const FDirectoryTreeIndex& TargetTreeIndex, ContainerType& OutFiles, TArray<FString>& OutDirectories, const FString& FullSearchPath, const FVisitFilter<ShouldVisitFunc>& VisitFilter) const` (scope `FPakFile`)
- L112 _function_ `template <class ContainerType> bool FPakFile::ValidateDirectoryTreeSearchConsistency(const ContainerType& FilesTree, const TArray<FString>& DirectoriesInPakTree, const ContainerType& FilesIndexed, const TArray<FString>& DirectoriesInPakIndexed) const` (scope `FPakFile`)
- L151 _function_ `template <typename ShouldVisitFunc, class ContainerType> void FPakFile::FindFilesAtPathInIndexInternal(const FStringView& RelSearchPath, const FDirectoryIndex& TargetIndex, ContainerType& OutFiles, TArray<FString>& OutDirectories, const FString& FullSearchPath, const FVisitFilter<ShouldVisitFunc>& VisitFilter) const` (scope `FPakFile`)
- L167 _function_ `template <typename ShouldVisitFunc, class ContainerType> void FPakFile::FindFilesAtPathInPakDirectoryInternal(const FString& MountPoint, FStringView RelPathInIndex, const FPakDirectory& PakDirectory, ContainerType& OutFiles, TArray<FString>& OutDirectoriesInPak, const FString& FullSearchPath, const FVisitFilter<ShouldVisitFunc>& VisitFilter)` (scope `FPakFile`)
- L233 _function_ `template <typename ShouldVisitFunc> FPakFile::FVisitFilter<ShouldVisitFunc>::FVisitFilter(const ShouldVisitFunc& InShouldVisit, bool bInIncludeFiles, bool bInIncludeDirectories, bool bInRecursive) : ShouldVisit(InShouldVisit) , bIncludeFiles(bInIncludeFiles) , bIncludeDirectories(bInIncludeDirectories) , bRecursive(bInRecursive)` (scope `FPakFile::FVisitFilter`)
- L243 _function_ `template <typename ShouldVisitFunc, class ContainerType> void FPakFile::FindPrunedFilesAtPathInternal(const TCHAR* InPath, ContainerType& OutFiles, const FVisitFilter<ShouldVisitFunc>& VisitFilter) const` (scope `FPakFile`)

### `Source/Runtime/PakFile/Private/PakIntervalTree.inl` (Private)


#### enum `(anonymous)`  
``  
_L6-8_

#### class `TIntervalTreeAllocator`  
`template<class TItem> class TIntervalTreeAllocator`  
_L34-96_
- desc: This is like TSparseArray, only a bit safer and I needed some restrictions on resizing.
- L36 _private member_ `TArray<TItem> Items;`
- L37 _private member_ `TArray<int32> FreeItems;` — @todo make this into a linked list through the existing items
- L38 _private member_ `uint32 Salt;`
- L39 _private member_ `uint32 SaltMask;`
- L41 _public function_ `TIntervalTreeAllocator()`
- L48 _public function_ `inline TIntervalTreeIndex Alloc()`
- L64 _public function_ `void EnsureNoRealloc(int32 NeededNewNum)`
- L71 _public function_ `FORCEINLINE TItem& Get(TIntervalTreeIndex InIndex)`
- L77 _public function_ `FORCEINLINE void Free(TIntervalTreeIndex InIndex)`
- L91 _public function_ `FORCEINLINE void CheckIndex(TIntervalTreeIndex InIndex)`

#### class `FIntervalTreeNode`  
`class FIntervalTreeNode`  
_L98-115_
- L101 _public member_ `TIntervalTreeIndex LeftChildOrRootOfLeftList;`
- L102 _public member_ `TIntervalTreeIndex RootOfOnList;`
- L103 _public member_ `TIntervalTreeIndex RightChildOrRootOfRightList;`
- L105 _public function_ `FIntervalTreeNode() : LeftChildOrRootOfLeftList(IntervalTreeInvalidIndex) , RootOfOnList(IntervalTreeInvalidIndex) , RightChildOrRootOfRightList(IntervalTreeInvalidIndex)`
- L111 _public function_ `~FIntervalTreeNode()`

#### Free symbols / members of external scopes

- L7 _enumerator_ `IntervalTreeInvalidIndex = 0` (scope `__anon9736c2600103`)
- L10 _typedef_ `typedef uint32 TIntervalTreeIndex;` — this is the arg type of TSparseArray::operator[]
- L12 _typedef_ `typedef uint64 FJoinedOffsetAndPakIndex;`
- L14 _function_ `static FORCEINLINE uint16 GetRequestPakIndexLow(FJoinedOffsetAndPakIndex Joined)`
- L19 _function_ `static FORCEINLINE int64 GetRequestOffset(FJoinedOffsetAndPakIndex Joined)`
- L24 _function_ `static FORCEINLINE FJoinedOffsetAndPakIndex MakeJoinedRequest(uint16 PakIndex, int64 Offset)`
- L30 _variable_ `static uint32 GNextSalt = 1;`
- L117 _variable_ `static TIntervalTreeAllocator<FIntervalTreeNode> GIntervalTreeNodeNodeAllocator;`
- L119 _function_ `static FORCEINLINE uint64 HighBit(uint64 x)`
- L124 _function_ `static FORCEINLINE bool IntervalsIntersect(uint64 Min1, uint64 Max1, uint64 Min2, uint64 Max2)`
- L131 _function_ `static void AddToIntervalTree_Dangerous( TIntervalTreeIndex* RootNode, TIntervalTreeAllocator<TItem>& Allocator, TIntervalTreeIndex Index, uint64 MinInterval, uint64 MaxInterval, uint32 CurrentShift, uint32 MaxShift )` — this routine assume that the pointers remain valid even though we are reallocating
- L184 _function_ `template<typename TItem> static void AddToIntervalTree( TIntervalTreeIndex* RootNode, TIntervalTreeAllocator<TItem>& Allocator, TIntervalTreeIndex Index, uint32 StartShift, uint32 MaxShift )`
- L202 _function_ `template<typename TItem> static FORCEINLINE bool ScanNodeListForRemoval( TIntervalTreeIndex* Iter, TIntervalTreeAllocator<TItem>& Allocator, TIntervalTreeIndex Index, uint64 MinInterval, uint64 MaxInterval )`
- L226 _function_ `template<typename TItem> static bool RemoveFromIntervalTree( TIntervalTreeIndex* RootNode, TIntervalTreeAllocator<TItem>& Allocator, TIntervalTreeIndex Index, uint64 MinInterval, uint64 MaxInterval, uint32 CurrentShift, uint32 MaxShift )`
- L283 _function_ `template<typename TItem> static bool RemoveFromIntervalTree( TIntervalTreeIndex* RootNode, TIntervalTreeAllocator<TItem>& Allocator, TIntervalTreeIndex Index, uint32 StartShift, uint32 MaxShift )`
- L298 _function_ `template<typename TItem> static FORCEINLINE void ScanNodeListForRemovalFunc( TIntervalTreeIndex* Iter, TIntervalTreeAllocator<TItem>& Allocator, uint64 MinInterval, uint64 MaxInterval, TFunctionRef<bool(TIntervalTreeIndex)> Func )`
- L326 _function_ `template<typename TItem> static void MaybeRemoveOverlappingNodesInIntervalTree( TIntervalTreeIndex* RootNode, TIntervalTreeAllocator<TItem>& Allocator, uint64 MinInterval, uint64 MaxInterval, uint64 MinNode, uint64 MaxNode, uint32 CurrentShift, uint32 MaxShift, TFunctionRef<bool(TIntervalTreeIndex)> Func )`
- L392 _function_ `template<typename TItem> static FORCEINLINE bool ScanNodeList( TIntervalTreeIndex Iter, TIntervalTreeAllocator<TItem>& Allocator, uint64 MinInterval, uint64 MaxInterval, TFunctionRef<bool(TIntervalTreeIndex)> Func )`
- L418 _function_ `template<typename TItem> static bool OverlappingNodesInIntervalTree( TIntervalTreeIndex RootNode, TIntervalTreeAllocator<TItem>& Allocator, uint64 MinInterval, uint64 MaxInterval, uint64 MinNode, uint64 MaxNode, uint32 CurrentShift, uint32 MaxShift, TFunctionRef<bool(TIntervalTreeIndex)> Func )`
- L480 _function_ `template<typename TItem> static bool ScanNodeListWithShrinkingInterval( TIntervalTreeIndex Iter, TIntervalTreeAllocator<TItem>& Allocator, uint64 MinInterval, uint64& MaxInterval, TFunctionRef<bool(TIntervalTreeIndex)> Func )`
- L508 _function_ `template<typename TItem> static bool OverlappingNodesInIntervalTreeWithShrinkingInterval( TIntervalTreeIndex RootNode, TIntervalTreeAllocator<TItem>& Allocator, uint64 MinInterval, uint64& MaxInterval, uint64 MinNode, uint64 MaxNode, uint32 CurrentShift, uint32 MaxShift, TFunctionRef<bool(TIntervalTreeIndex)> Func )`
- L573 _function_ `template<typename TItem> static void MaskInterval( TIntervalTreeIndex Index, TIntervalTreeAllocator<TItem>& Allocator, uint64 MinInterval, uint64 MaxInterval, uint32 BytesToBitsShift, uint64* Bits )`
- L614 _function_ `template<typename TItem> static void OverlappingNodesInIntervalTreeMask( TIntervalTreeIndex RootNode, TIntervalTreeAllocator<TItem>& Allocator, uint64 MinInterval, uint64 MaxInterval, uint64 MinNode, uint64 MaxNode, uint32 CurrentShift, uint32 MaxShift, uint32 BytesToBitsShift, uint64* Bits )`
- L637 _function_ `` (scope `OverlappingNodesInIntervalTreeMask`)

### `Source/Runtime/PakFile/Private/SignedArchiveReader.h` (Private)


#### struct `FChunkBuffer`  
`struct FChunkBuffer`  
_L17-42_
- desc: Chunk buffer. Buffers are locked and released only on the worker thread.
- L20 _public member_ `uint8* Data;` — Chunk data
- L22 _public member_ `int32 LockCount;` — Number of locks on this buffer
- L24 _public member_ `int32 ChunkIndex;` — Index of the chunk
- L26 _public member_ `double LastAccessTime;` — Last time this buffer has been accessed
- L28 _public function_ `FChunkBuffer() : Data(NULL) , LockCount(0) , ChunkIndex(INDEX_NONE) , LastAccessTime(0.0)`
- L37 _public function_ `~FChunkBuffer()`

#### struct `FChunkRequest`  
`struct FChunkRequest`  
_L48-95_
- desc: Request to load a chunk. This is how the archive reader and the worker thread communicate. Requests can be locked by both threads.
- L51 _public member_ `int32 Index;` — Chunk index
- L53 _public member_ `int64 Offset;` — Chunk offset
- L55 _public member_ `int64 Size;` — Chunk size
- L57 _public member_ `FChunkBuffer* Buffer;` — Buffer where the data is cached
- L59 _public member_ `FThreadSafeCounter IsTrusted;` — Flag to indicate if the chunk has been verified
- L61 _public member_ `FThreadSafeCounter RefCount;` — Reference count
- L63 _public member_ `FEvent* Event;` — Optional pointer to an FEvent that can be used to signal that the request is ready for use
- L68 _public function_ `FChunkRequest() : Index(INDEX_NONE) , Offset(0) , Size(0) , Buffer(nullptr) , IsTrusted(0) , RefCount(0) , Event(nullptr)` — Constructor
- L81 _public function_ `FORCEINLINE void WaitUntilReady() const` — Waits until this chunk has been verified
- L91 _public function_ `FORCEINLINE bool IsReady() const` — Checks if this chunk has been verified.

#### class `FChunkCacheWorker`  
`class FChunkCacheWorker : public FRunnable`  
_L102-214_
- inherits: `FRunnable`
- desc: Thread that loads and verifies signed chunks. One per pak file but can serve multiple FSignedArchiveReaders from multiple threads! Can process multiple chunks using a limited number of buffers.
- L111 _private member_ `TSharedPtr<const FPakSignatureFile, ESPMode::ThreadSafe> Signatures;` — Reference hashes
- L113 _private member_ `TPakChunkHash OriginalSignatureFileHash;` — Hash of the sig file data. Used to check that nothing was corrupted when a signature check fails
- L115 _private member_ `FRunnableThread* Thread;` — Thread to run the worker FRunnable on
- L117 _private member_ `TUniquePtr<FArchive> Reader;` — Archive reader
- L119 _private member_ `FChunkBuffer CachedChunks[MaxCachedChunks];` — Cached and verified chunks.
- L121 _private member_ `TArray<FChunkRequest*> RequestQueue;` — Queue of chunks to cache
- L123 _private member_ `FCriticalSection QueueLock;` — Lock for manipulating the queue
- L125 _private member_ `FThreadSafeCounter PendingQueueCounter;` — Counter indicating how many pending queued request exist
- L127 _private member_ `FEvent* QueuedRequestsEvent;` — Event used to signal there's work to be done
- L129 _private member_ `TArray<FChunkRequest*> ActiveRequests;` — List of active chunk requests
- L131 _private member_ `FThreadSafeCounter StopTaskCounter;` — Stops this thread
- L133 _private member_ `TLockFreePointerListUnordered<FChunkRequest, PLATFORM_CACHE_LINE_SIZE> FreeChunkRequests;` — Available chunk requests
- L135 _private member_ `TLockFreePointerListUnordered<FEvent,PLATFORM_CACHE_LINE_SIZE> EventsToRelease;` — List of FEvents to be released on the worker thread
- L142 _private prototype_ `int32 ProcessQueue();` — Process requested chunks @return Number of chunks processed this loop.
- L146 _private prototype_ `bool CheckSignature(const FChunkRequest& ChunkInfo);` — Verifies chunk signature [*]
- L150 _private prototype_ `FChunkBuffer* GetCachedChunkBuffer(int32 ChunkIndex);` — Tries to get a pre-cached chunk buffer
- L154 _private prototype_ `FChunkBuffer* GetFreeBuffer();` — Tries to get the least recent free buffer
- L158 _private prototype_ `void ReleaseBuffer(int32 ChunkIndex);` — Decrements a ref count on a buffer for the specified chunk
- L162 _private function_ `FORCEINLINE bool IsMultithreaded() const` — Is this chunk cache worker running in a thread?
- L169 _private prototype_ `FEvent* AcquireNotificationEvent() const;` — Returns a FEvent that can later be released via ReleaseNotificationEvent
- L173 _private prototype_ `void ReleaseNotificationEvent(FEvent* Event);` — Queues the event to be released safely on the FChunkCacheWorker thread
- L177 _public prototype_ `FChunkCacheWorker(TUniquePtr<FArchive> InReader, const TCHAR* Filename);`
- L178 _public prototype_ `virtual ~FChunkCacheWorker();`
- L181 _public prototype_ `virtual bool Init();`
- L182 _public prototype_ `virtual uint32 Run();`
- L183 _public prototype_ `virtual void Stop();`
- L186 _public function_ `TSharedPtr<const FPakSignatureFile, ESPMode::ThreadSafe> GetSignatures() const`
- L200 _public prototype_ `FChunkRequest& RequestChunk(int32 ChunkIndex, int64 StartOffset, int64 ChunkSize, FEvent* Event);` — Requests a chunk to be loaded and verified @param ChunkIndex Index of a chunk to load @param StartOffset Offset to the beginning of the chunk @param ChunkSize Chunk size @param Event Optional FEvent that will signal when the request is ready, nullptr is valid if the calling code does not want this signal @return Handle to the request.
- L204 _public prototype_ `void ReleaseChunk(FChunkRequest& Chunk);` — Releases the requested chunk buffer
- L211 _public prototype_ `bool IsValid() const;` — Indicates that this chunk worker is valid. If the signature file couldn't be loaded or if it failed the principal table check, this will be false

#### enum `FChunkCacheWorker::(anonymous)`  
``  
_L105-108_

#### class `FSignedArchiveReader`  
`class FSignedArchiveReader : public FArchive`  
_L221-311_
- inherits: `FArchive`
- desc: FSignedArchiveReader - reads data from pre-cached and verified chunks.
- L233 _private member_ `int64 ChunkCount;` — Number of chunks in the archive
- L235 _private member_ `FArchive* PakReader;` — Reader archive
- L237 _private member_ `int64 SizeOnDisk;` — Size of the archive on disk
- L239 _private member_ `int64 PakSize;` — Size of actual data (excluding signatures)
- L241 _private member_ `int64 PakOffset;` — Current offet into data
- L243 _private member_ `FChunkCacheWorker* SignatureChecker;` — Worker thread - reads chunks from disk and verifies their signatures
- L245 _private member_ `FChunkBuffer LastCachedChunk;` — Last pre-cached buffer
- L250 _private function_ `FORCEINLINE int64 CalculateChunkIndex(int64 ReadOffset) const` — Calculate index of a chunk that contains the specified offset
- L258 _private function_ `FORCEINLINE int64 CalculateChunkOffsetFromIndex(int64 BufferIndex) const` — Calculate offset of a chunk in the archive
- L270 _private function_ `FORCEINLINE int64 CalculateChunkOffset(int64 ReadOffset, int64& OutDataOffset) const` — Calculate offset of a chunk in the archive and the offset to read from the archive @param ReadOffset Read request offset @param OutDataOffset Actuall offset to read from in the archive @return Offset where the chunk begins in the archive (signature offset)
- L280 _private prototype_ `int64 CalculateChunkSize(int64 ChunkIndex) const;` — Calculates chunk size based on its index (most chunks have the same size, except the last one
- L289 _private prototype_ `int64 PrecacheChunks(TArray<FReadInfo>& Chunks, int64 Length, FEvent* Event);` — Queues chunks on the worker thread @param Chunks This array will contain info about each chunk created by the call. @param Length The length of data to precache @param Event Optional FEvent that will signal as each request becomes ready, nullptr is valid if the calling code does not want this signal @return Number of chunks in the output array which are actually required for the requested length. The rest are precache chunks
- L293 _public prototype_ `FSignedArchiveReader(FArchive* InPakReader, FChunkCacheWorker* InSignatureChecker);`
- L294 _public prototype_ `virtual ~FSignedArchiveReader();`
- L297 _public prototype_ `virtual void Serialize(void* Data, int64 Length) override;`
- L298 _public function_ `virtual int64 Tell() override`
- L302 _public function_ `virtual int64 TotalSize() override`
- L306 _public function_ `virtual void Seek(int64 InPos) override`

#### struct `FSignedArchiveReader::FReadInfo`  
`struct FReadInfo`  
_L223-230_
- L225 _public member_ `FChunkRequest* Request;`
- L226 _public member_ `FChunkBuffer* PreCachedChunk;`
- L227 _public member_ `int64 SourceOffset;`
- L228 _public member_ `int64 DestOffset;`
- L229 _public member_ `int64 Size;`

#### Free symbols / members of external scopes

- L107 _enumerator_ `MaxCachedChunks = 8` (scope `FChunkCacheWorker::__anonc66217630103`) — Buffer size

### `Source/Runtime/PakFile/Public/IPlatformFilePak.h` (Public)


#### struct `FPakChunkSignatureCheckFailedData`  
`struct FPakChunkSignatureCheckFailedData`  
_L118-133_
- L120 _public function_ `FPakChunkSignatureCheckFailedData(const FString& InPakFilename, const TPakChunkHash& InExpectedHash, const TPakChunkHash& InReceivedHash, int32 InChunkIndex) : PakFilename(InPakFilename) , ChunkIndex(InChunkIndex) , ExpectedHash(InExpectedHash) , ReceivedHash(InReceivedHash)`
- L127 _public member_ `FString PakFilename;`
- L128 _public member_ `int32 ChunkIndex;`
- L129 _public member_ `TPakChunkHash ExpectedHash;`
- L130 _public member_ `TPakChunkHash ReceivedHash;`
- L132 _public function_ `FPakChunkSignatureCheckFailedData() : ChunkIndex(0)`

#### struct `FPakInfo`  
`struct FPakInfo`  
_L147-363_
- desc: Struct which holds pak file info (version, index offset, hash value).
- L184 _public member_ `uint32 Magic;` — Pak file magic value.
- L186 _public member_ `int32 Version;` — Pak file version.
- L188 _public member_ `int64 IndexOffset;` — Offset to pak file index.
- L190 _public member_ `int64 IndexSize;` — Size (in bytes) of pak file index.
- L192 _public member_ `FSHAHash IndexHash;` — SHA1 of the bytes in the index, used to check for data corruption when loading the index.
- L194 _public member_ `uint8 bEncryptedIndex;` — Flag indicating if the pak index has been encrypted.
- L196 _public member_ `FGuid EncryptionKeyGuid;` — Encryption key guid. Empty if we should use the embedded key.
- L198 _public member_ `TArray<FName> CompressionMethods;` — Compression methods used in this pak file (FNames, saved as FStrings)
- L203 _public function_ `FPakInfo() : Magic(PakFile_Magic) , Version(PakFile_Version_Latest) , IndexOffset(-1) , IndexSize(0) , bEncryptedIndex(0)` — Constructor.
- L219 _public function_ `int64 GetSerializedSize(int32 InVersion = PakFile_Version_Latest) const` — Gets the size of data serialized by this struct. @return Serialized data size.
- L231 _public function_ `int64 HasRelativeCompressedChunkOffsets() const`
- L241 _public function_ `void Serialize(FArchive& Ar, int32 InVersion)` — Serializes this struct. @param Ar Archive to serialize data with.
- L331 _public function_ `int32 GetCompressionMethodIndex(FName CompressionMethod)`
- L350 _public function_ `FName GetCompressionMethod(uint32 Index) const`
- L355 _public function_ `TOptional<FName> TryGetCompressionMethod(uint32 Index) const`

#### enum `FPakInfo::(anonymous)`  
``  
_L150-159_

#### enum `FPakInfo::(anonymous)`  
``  
_L163-181_

#### struct `FPakCompressedBlock`  
`struct FPakCompressedBlock`  
_L368-384_
- desc: Struct storing offsets and sizes of a compressed block.
- L371 _public member_ `int64 CompressedStart;` — Offset of the start of a compression block. Offset is relative to the start of the compressed chunk data
- L373 _public member_ `int64 CompressedEnd;` — Offset of the end of a compression block. This may not align completely with the start of the next block. Offset is relative to the start of the compressed chunk data.
- L375 _public function_ `bool operator == (const FPakCompressedBlock& B) const`
- L380 _public function_ `bool operator != (const FPakCompressedBlock& B) const`

#### struct `FPakEntry`  
`struct FPakEntry`  
_L405-603_
- desc: Struct holding info about a single file stored in pak file. CHANGE THIS FILE RARELY AND WITH GREAT CARE. MODIFICATIONS WILL RESULT IN EVERY PAK ENTRY IN AN EXISTING INSTALL HAVING TO TO BE PATCHED. On Fortnite that would be 15GB of data (250k pak entries * 64kb patch block) just to add/change/remove a field.
- L407 _public member_ `static const uint8 Flag_None = 0x00;`
- L408 _public member_ `static const uint8 Flag_Encrypted = 0x01;`
- L409 _public member_ `static const uint8 Flag_Deleted = 0x02;`
- L412 _public member_ `int64 Offset;` — Offset into pak file where the file is stored.
- L414 _public member_ `int64 Size;` — Serialized file size.
- L416 _public member_ `int64 UncompressedSize;` — Uncompressed file size.
- L418 _public member_ `uint8 Hash[20];` — File SHA1 value.
- L420 _public member_ `TArray<FPakCompressedBlock> CompressionBlocks;` — Array of compression blocks that describe how to decompress this pak entry.
- L422 _public member_ `uint32 CompressionBlockSize;` — Size of a compressed block in the file.
- L424 _public member_ `uint32 CompressionMethodIndex;` — Index into the compression methods in this pakfile.
- L426 _public member_ `uint8 Flags;` — Pak entry flags.
- L428 _public member_ `mutable bool Verified;` — Flag is set to true when FileHeader has been checked against PakHeader. It is not serialized.
- L433 _public function_ `FPakEntry()` — Constructor.
- L443 _public function_ `int64 GetSerializedSize(int32 Version) const` — Gets the size of data serialized by this struct. @return Serialized data size.
- L475 _public function_ `bool operator == (const FPakEntry& B) const` — Compares two FPakEntry structs.
- L484 _public function_ `bool operator != (const FPakEntry& B) const` — Compares two FPakEntry structs.
- L489 _public function_ `bool IndexDataEquals(const FPakEntry& B) const`
- L502 _public function_ `void Reset()`
- L521 _public function_ `void Serialize(FArchive& Ar, int32 Version)` — Serializes FPakEntry struct. @param Ar Archive to serialize data with. @param Entry Data to serialize.
- L572 _public function_ `inline void SetFlag( uint8 InFlag, bool bValue )`
- L584 _public function_ `inline bool GetFlag( uint8 InFlag ) const`
- L589 _public function_ `inline bool IsEncrypted() const`
- L590 _public function_ `inline void SetEncrypted( bool bEncrypted )`
- L592 _public function_ `inline bool IsDeleteRecord() const`
- L593 _public function_ `inline void SetDeleteRecord( bool bDeleteRecord )`
- L602 _public prototype_ `static bool VerifyPakEntriesMatch(const FPakEntry& FileEntryA, const FPakEntry& FileEntryB);` — Verifies two entries match to check for corruption. @param FileEntryA Entry 1. @param FileEntryB Entry 2.

#### struct `FPakEntryLocation`  
`struct FPakEntryLocation`  
_L609-697_
- desc: An identifier for the location of an FPakEntry in an FDirectoryIndex or an FPathHashIndex. Contains a byte offset into the encoded array of FPakEntry data, an index into the list of unencodable FPakEntries, or a marker indicating invalidity
- L618 _public member_ `static const int32 Invalid = MIN_int32;` — 0x00000000 - 0x7ffffffe: EncodedOffset from 0 to MaxIndex 0x7fffffff: Unused, interpreted as Invalid 0x80000000: Invalid 0x80000001 - 0xffffffff: FileIndex from MaxIndex to 0
- L619 _public member_ `static const int32 MaxIndex = MAX_int32 - 1;`
- L621 _public function_ `FPakEntryLocation() : Index(Invalid)`
- L624 _public prototype_ `FPakEntryLocation(const FPakEntryLocation& Other) = default;`
- L625 _public prototype_ `FPakEntryLocation& operator=(const FPakEntryLocation& other) = default;`
- L627 _public function_ `static FPakEntryLocation CreateInvalid()`
- L632 _public function_ `static FPakEntryLocation CreateFromOffsetIntoEncoded(int32 Offset)`
- L638 _public function_ `static FPakEntryLocation CreateFromListIndex(int32 ListIndex)`
- L644 _public function_ `bool IsInvalid() const`
- L649 _public function_ `bool IsOffsetIntoEncoded() const`
- L654 _public function_ `bool IsListIndex() const`
- L659 _public function_ `int32 GetAsOffsetIntoEncoded() const`
- L670 _public function_ `int32 GetAsListIndex() const`
- L682 _public function_ `void Serialize(FArchive& Ar)`
- L687 _public function_ `bool operator==(const FPakEntryLocation& Other) const`
- L692 _private function_ `explicit FPakEntryLocation(int32 InIndex) : Index(InIndex)`
- L696 _private member_ `int32 Index;`

#### class `FSharedPakReader`  
`class FSharedPakReader final`  
_L708-734_
- desc: Wrapper for a pointer to a shared pak reader archive that has been temporarily acquired.
- L712 _private member_ `FArchive* Archive = nullptr;`
- L713 _private member_ `FPakFile* PakFile = nullptr;` — Pak file to return ownership to on destruction
- L715 _private prototype_ `FSharedPakReader(FArchive* InArchive, FPakFile* InPakFile);`
- L718 _public prototype_ `~FSharedPakReader();`
- L720 _public prototype_ `FSharedPakReader(const FSharedPakReader& Other) = delete;`
- L721 _public prototype_ `FSharedPakReader& operator=(const FSharedPakReader& Other) = delete;`
- L722 _public prototype_ `FSharedPakReader(FSharedPakReader&& Other);`
- L723 _public prototype_ `FSharedPakReader& operator=(FSharedPakReader&& Other);`
- L725 _public function_ `explicit operator bool() const`
- L726 _public function_ `bool operator==(TYPE_OF_NULLPTR)`
- L727 _public function_ `bool operator!=(TYPE_OF_NULLPTR)`
- L728 _public function_ `FArchive* operator->()`
- L732 _public function_ `FArchive& GetArchive()` — USE WITH CARE, the FSharedPakReader must live longer than this reference to prevent the archive being used by another thread. Do not call on a temporary return value!

#### struct `FPakEntryPair`  
`struct FPakEntryPair`  
_L752-756_
- desc: Convenience struct for building FPakFile indexes from an enumeration of (Filename,FPakEntry) pairs
- L754 _public member_ `FString Filename;`
- L755 _public member_ `FPakEntry Info;`

#### class `FPakFile`  
`class FPakFile : FNoncopyable, public FRefCountedObject, public IPakFile`  
_L761-1665_
- inherits: `FNoncopyable,FRefCountedObject,IPakFile`
- desc: Pak file.
- L765 _public typedef_ `typedef TMap<uint64, FPakEntryLocation> FPathHashIndex;` — Index data that provides a map from the hash of a Filename to an FPakEntryLocation
- L767 _public typedef_ `typedef TMap<FString, FPakDirectory> FDirectoryIndex;` — Index data that keeps an in-memory directoryname/filename tree to map a Filename to an FPakEntryLocation
- L806 _public prototype_ `bool RecreatePakReaders(IPlatformFile* LowerLevel);` — Recreates the pak reader for each thread
- L821 _private member_ `FString PakFilename;` — Pak filename.
- L822 _private member_ `FName PakFilenameName;`
- L824 _private member_ `TUniquePtr<class FChunkCacheWorker> Decryptor;` — Archive to serialize the pak file from.
- L826 _private member_ `TArray<FArchiveAndLastAccessTime> Readers;` — List of readers and when they were last used.
- L828 _private member_ `std::atomic<int32> CurrentlyUsedReaders = 0;` — How many readers have been loaned out and not yet returned. If this is >0 we should not destroy the decryptor.
- L830 _private member_ `FCriticalSection ReadersCriticalSection;` — Critical section for accessing Readers.
- L832 _private member_ `FPakInfo Info;` — Pak file info (trailer).
- L834 _private member_ `FString MountPoint;` — Mount point.
- L836 _private member_ `TArray<FPakEntry> Files;` — Info on all files stored in pak.
- L838 _private member_ `FDirectoryIndex DirectoryIndex;` — Pak Index organized as a map of directories to support searches by path.  This Index is pruned at runtime of all FileNames and Paths that are not allowed by DirectoryIndexKeepFiles
- L840 _private typedef_ `using FDirectoryTreeIndex = UE::PakFile::Private::FDirectoryTreeIndex;`
- L842 _private member_ `FDirectoryTreeIndex DirectoryTreeIndex;`
- L846 _private member_ `FDirectoryIndex PrunedDirectoryIndex;` — Temporary-lifetime copy of the Pruned DirectoryIndex; all Pruned files have been removed form this copy.  This copy is used for validation that no queries are missing during runtime, and will be swapped into the DirectoryIndex when Pak Mounting is complete
- L847 _private member_ `FDirectoryTreeIndex PrunedDirectoryTreeIndex;`
- L849 _private member_ `mutable FRWLock DirectoryIndexLock;` — ReaderWriter lock to guard DirectoryIndex iteration from being interrupted by the swap of PrunedDirectoryIndex
- L853 _private member_ `FPathHashIndex PathHashIndex;` — Index data that provides a map from the hash of a Filename to an FPakEntryLocation
- L855 _private member_ `TArray<uint8> EncodedPakEntries;` — FPakEntries that have been serialized into a compacted format in an array of bytes.
- L857 _private member_ `uint64 PathHashSeed;` — The seed passed to the hash function for hashing filenames in this pak.  Differs per pack so that the same filename in different paks has different hashes
- L860 _private member_ `int32 NumEntries;` — The number of file entries in the pak file
- L862 _private member_ `FDateTime Timestamp;` — Timestamp of this pak file.
- L864 _private member_ `int64 CachedTotalSize;` — TotalSize of the pak file
- L866 _private member_ `bool bSigned;` — True if this is a signed pak file.
- L868 _private member_ `bool bIsValid;` — True if this pak file is valid and usable.
- L870 _private member_ `bool bHasPathHashIndex;` — True if the PathHashIndex has been populated for this PakFile
- L872 _private member_ `bool bHasFullDirectoryIndex;` — True if the DirectoryIndex has not been pruned and still contains a Filename for every FPakEntry in this PakFile
- L875 _private member_ `bool bWillPruneDirectoryIndex;` — True if we have a FullDirectoryIndex that we will modify in OptimizeMemoryUsageForMountedPaks and therefore need to guard access with DirectoryIndexLock
- L877 _private member_ `bool bNeedsLegacyPruning;` — True if the Index of this PakFile was a legacy index that did not have the precomputed Pruned DirectoryIndex and we need to compute it before swapping the Pruned DirectoryIndex
- L880 _private member_ `bool bUseDirectoryTree;`
- L883 _private member_ `int32 PakchunkIndex;` — ID for the chunk this pakfile is part of. INDEX_NONE if this isn't a pak chunk (derived from filename)
- L885 _private member_ `TSharedPtr<IMappedFileHandle> MappedFileHandle;`
- L886 _private member_ `FCriticalSection MappedFileHandleCriticalSection;`
- L889 _private member_ `ECacheType CacheType;` — The type of cache this pak file should have
- L891 _private member_ `int32 CacheIndex;` — The index of this pak file into the cache array, -1 = not initialized
- L893 _private member_ `bool UnderlyingCacheTrimDisabled;` — Allow the cache of a pak file to never shrink, should be used with caution, it will burn memory
- L895 _private member_ `bool bIsMounted;` — Record of whether the pak file is still mounted, so PakPrecacher can reject requests to register it.
- L897 _private member_ `TUniquePtr<FIoContainerHeader> IoContainerHeader;`
- L899 _private member_ `TUniquePtr<FIoContainerHeader> OptionalSegmentIoContainerHeader;`
- L902 _private function_ `static inline int32 CDECL CompareFilenameHashes(const void* Left, const void* Right)`
- L917 _private prototype_ `FArchive* CreatePakReader(IPlatformFile* LowerLevel, const TCHAR* Filename);`
- L918 _private prototype_ `FArchive* SetupSignedPakReader(FArchive* Reader, const TCHAR* Filename);`
- L923 _public function_ `virtual const FString& PakGetPakFilename() const override` — IPakFile interface, for users of PakFiles that cannot have a dependency on this header
- L928 _public function_ `virtual bool PakContains(const FString& FullPath) const override`
- L933 _public function_ `virtual int32 PakGetPakchunkIndex() const override`
- L938 _public function_ `virtual void PakVisitPrunedFilenames(IPlatformFile::FDirectoryVisitor& Visitor) const override`
- L946 _public function_ `virtual const FString& PakGetMountPoint() const override`
- L952 _public function_ `void SetUnderlyingCacheTrimDisabled(bool InUnderlyingCacheTrimDisabled)`
- L953 _public function_ `bool GetUnderlyingCacheTrimDisabled(void)`
- L955 _public function_ `void SetCacheType(ECacheType InCacheType)`
- L956 _public function_ `ECacheType GetCacheType(void)`
- L957 _public function_ `void SetCacheIndex(int32 InCacheIndex)`
- L958 _public function_ `int32 GetCacheIndex(void)`
- L959 _public function_ `void SetIsMounted(bool bInIsMounted)`
- L960 _public function_ `bool GetIsMounted() const`
- L968 _public prototype_ `FPakFile(const TCHAR* Filename, bool bIsSigned);` — Opens a pak file given its filename. @param Filename Pak filename. @param bIsSigned true if the pak is signed
- L978 _public prototype_ `FPakFile(IPlatformFile* LowerLevel, const TCHAR* Filename, bool bIsSigned, bool bLoadIndex = true);` — Creates a pak file using the supplied file handle. @param LowerLevel Lower level platform file. @param Filename Filename. @param bIsSigned = true if the pak is signed.
- L986 _public prototype_ `FPakFile(FArchive* Archive);`
- L991 _private prototype_ `virtual ~FPakFile();` — Private destructor, use AddRef/Release instead
- L1001 _public function_ `bool IsValid() const` — Checks if the pak file is valid. @return true if this pak file is valid, false otherwise.
- L1011 _public prototype_ `bool PassedSignatureChecks() const;` — Checks if the pak has valid chunk signature checking data, and that the data passed the initial signing check @return true if this pak file has passed the initial signature checking phase
- L1018 _public function_ `const FString& GetFilename() const` — Gets pak filename. @return Pak filename.
- L1022 _public function_ `FName GetFilenameName() const`
- L1027 _public function_ `int64 TotalSize() const`
- L1035 _public function_ `virtual int32 GetNumFiles() const override` — Gets the number of files in this pak.
- L1041 _public prototype_ `void GetPrunedFilenames(TArray<FString>& OutFileList) const;` — Returns the FullPath (includes Mount) Filename found in Pruned DirectoryIndex
- L1044 _public prototype_ `void GetPrunedFilenamesInChunk(const TArray<int32>& InChunkIDs, TArray<FString>& OutFileList) const;` — Returns the RelativePathFromMount Filename for every Filename found in the Pruned DirectoryIndex that points to a PakEntry in the given Chunk
- L1051 _public prototype_ `FSharedPakReader GetSharedReader(IPlatformFile* LowerLevel);` — Gets shared pak file archive for given thread. @return Pointer to pak file archive used to read data from pak.
- L1054 _public prototype_ `void ReturnSharedReader(FArchive* SharedReader);` — Return a shared pak reader. Should only be called from the FSharedPakReader's destructor.
- L1057 _public prototype_ `void ReleaseOldReaders(double MaxAgeSeconds);` — Delete all readers that haven't been used in MaxAgeSeconds.
- L1072 _public prototype_ `EFindResult Find(const FString& FullPath, FPakEntry* OutEntry) const;`
- L1079 _public function_ `void SetMountPoint(const TCHAR* Path)` — Sets the pak file mount point. @param Path New mount point path.
- L1090 _public function_ `const FString& GetMountPoint() const` — Gets pak file mount point. @return Mount point path.
- L1097 _public function_ `void FindPrunedFilesAtPath(ContainerType& OutFiles, const TCHAR* InPath, bool bIncludeFiles = true, bool bIncludeDirectories = false, bool bRecursive = false) const` — `UE_DEPRECATED(5.4, "Use version that takes a TArray<FString>& instead.")`
- L1120 _public prototype_ `void FindPrunedFilesAtPath(const TCHAR* InPath, TArray<FString>& OutFiles, bool bIncludeFiles = true, bool bIncludeDirectories = false, bool bRecursive = false) const;` — Looks for files or directories within the Pruned DirectoryIndex of the pak file. The Pruned DirectoryIndex does not have entries for most Files in the pak; they were removed to save memory. A project can specify which FileNames and DirectoryNames can be marked to keep in the DirectoryIndex; see FPakFile::FIndexSettings and FPakFile::PruneDirectoryIndex Returned paths are full paths (include the mount point) @param InPath Path to look for files or folder at. @param OutFiles List of files or folder matching search criteria. @param bIncludeFiles If true OutFiles will include matching files. @param bIncludeDirectories If true OutFiles will include matching folders. @param bRecursive If true, sub-folders will also be checked.
- L1129 _public function_ `const FPakDirectory* FindPrunedDirectory(const TCHAR* InPath) const` — Finds a directory in pak file. @param InPath Directory path. @return Pointer to a map with directory contents if the directory was found, NULL otherwise.
- L1147 _public function_ `bool DirectoryExistsInPruned(const TCHAR* InPath) const` — Checks if a directory exists in pak file. @param InPath Directory path. @return true if the given path exists in pak file, false otherwise.
- L1164 _public prototype_ `bool Check();` — Checks the validity of the pak data by reading out the data for every file in the pak @return true if the pak file is valid
- L1314 _public function_ `const FPakInfo& GetInfo() const` — Gets this pak file info. @return Info about this pak file.
- L1324 _public function_ `const FDateTime& GetTimestamp() const` — Gets this pak file's tiemstamp. @return Timestamp.
- L1334 _public function_ `bool HasFilenames() const` — Returns whether filenames currently exist in the DirectoryIndex for all files in the Pak. @return true if filenames are present for all FPakEntry, false otherwise.
- L1347 _public function_ `void ReadHashFromPayload(const FPakEntry& PakEntry, uint8* OutBuffer)` — Given a FPakEntry from the index, seek to the payload and read the hash of the payload out of the payload entry Warning: Slow function, do not use in performance critical operations @param PakEntry the FPakEntry from the index, which has the Offset to read to @param OutBuffer a buffer at least sizeof(FPakEntry::Hash) in size, into which the hash will be copied
- L1364 _public prototype_ `static uint64 HashPath(const TCHAR* RelativePathFromMount, uint64 Seed, int32 PakFileVersion);` — Hash the given full-path filename using the hash function used by FPakFiles, with the given FPakFile-specific seed, with version provided for legacy pak files that used different hash function
- L1385 _public typedef_ `typedef TFunction<FPakEntryPair & ()> ReadNextEntryFunction;` — Read a list of (Filename, FPakEntry) pairs from a provided enumeration, attempt to encode each one, store each one in the appropriate given encoded and/or unencoded array, and populate the given Directories to map each filename to the location for the FPakEntry @param InNumEntries How many entries will be read from ReadNextEntryFunction @param ReadNextEntryFunction Callback called repeatedly to enumerate the (Filename,FPakEntry) pairs to be encoded @param InPakFilename Filename for the pak containing the files, used to create the hashseed for the given pak @param InPakInfo PakInfo for the given pak, used for serialization flags @param MountPoint Directory into which the pak will be mounted, used to create the Directory and PathHash indexes @param OutNumEncodedEntries How many entries were written to the bytes in OutEncodedPakEntries @param OutNumDeletedEntries How many entries were skipped and not stored because the input FPakEntry was a Delete record @param OutPathHashSeed optional out param to get a copy of the pakfile-specific hashseed @param OutDirectoryIndex optional output FDirectoryIndex @param OutPathHashIndex optional output FPathHashIndex @param OutEncodedPakEntries array of bytes into which the encoded FPakEntries are stored.  Values in OutDirectoryIndex and OutPathHashIndex can be offsets into this array indicated the start point for the encoding of the given FPakEntry @param OutNonEncodableEntries A list of all the FPakEntries that could not be encoded.  Values i
- L1386 _public prototype_ `static void EncodePakEntriesIntoIndex(int32 InNumEntries, const ReadNextEntryFunction& InReadNextEntry, const TCHAR* InPakFilename, const FPakInfo& InPakInfo, const FString& MountPoint, int32& OutNumEncodedEntries, int32& OutNumDeletedEntries, uint64* OutPathHashSeed, FDirectoryIndex* OutDirectoryIndex, FPathHashIndex* OutPathHashIndex, TArray<uint8>& OutEncodedPakEntries, TArray<FPakEntry>& OutNonEncodableEntries, TMap<uint64, FString>* InOutCollisionDetection, int32 PakFileVersion);`
- L1392 _public prototype_ `static const FPakEntryLocation* FindLocationFromIndex(const FString& FullPath, const FString& MountPoint, const FPathHashIndex& PathHashIndex, uint64 PathHashSeed, int32 PakFileVersion);` — Lookup the FPakEntryLocation stored in the given PathHashIndex, return nullptr if not found
- L1395 _public prototype_ `static const FPakEntryLocation* FindLocationFromIndex(const FString& FullPath, const FString& MountPoint, const FDirectoryIndex& DirectoryIndex);` — Lookup the FPakEntryLocation stored in the given DirectoryIndex, return nullptr if not found
- L1403 _public prototype_ `static EFindResult GetPakEntry(const FPakEntryLocation& FPakEntryLocation, FPakEntry* OutEntry, const TArray<uint8>& EncodedPakEntries, const TArray<FPakEntry>& Files, const FPakInfo& Info);` — Returns the FPakEntry pointed to by the given FPakEntryLocation inside the given EncodedPakEntries or Files Can return Found or Deleted; if the FPakEntryLocation is invalid this function assumes the FPakEntry exists in this pack but as a deleted file If OutEntry is non-null, populates it with a copy of the FPakEntry found, or sets it to an FPakEntry with SetDeleteRecord(true) if not found
- L1412 _public prototype_ `static void PruneDirectoryIndex(FDirectoryIndex& InOutDirectoryIndex, FDirectoryIndex* PrunedDirectoryIndex, const FString& MountPoint);` — Given a directory index, remove entries from it that are directed by ini to not have filenames kept at runtime. InOutDirectoryIndex - The full index from which to potentially remove entries OutDirectoryIndex - If null, InOutDirectoryIndex will have pruned entries removed.  If non-null, InOutDirectoryIndex will not be modified, and PrunedDirectoryIndex will have kept values added. MountPoint The mount point for the pak containing the index, used to provide the fullpath for filenames in the DirectoryIndex for comparison against paths in ini
- L1415 _public function_ `static void MakeDirectoryFromPath(FString& Path)` — Helper function to modify the given string to append '/' at the end of path to normalize directory names for hash and string compares
- L1423 _public function_ `static bool IsPathInDirectoryFormat(const FString& Path)` — Helper function to check that the given string is in our directory format (ends with '/')
- L1429 _public prototype_ `static FString PakPathCombine(FStringView Parent, FStringView Child);` — Helper function to join two path strings that are in the PakPath format
- L1430 _public prototype_ `static FString PakPathCombine(FStringView Parent, FUtf8StringView Child);`
- L1433 _public prototype_ `static bool SplitPathInline(FStringView& InOutPath, FStringView& OutFilename);` — Helper function to split a PakDirectoryIndex-Formatted PathName into its PakDirectoryIndex-Formatted parent directory and the CleanFileName
- L1435 _public function_ `static bool SplitPathInline(FString& InOutPath, FString& OutFilename)`
- L1449 _public function_ `static bool GetRelativePathFromMountInline(FString& Child, const FString& MountPoint)` — Helper function to return Child's relative path from the mount point.  Returns false if Child is not equal to MountPoint and is not a child path under MountPoint, else returns true. Edits Child only if returning true, setting it to the relative path. If child equals MountPoint, returns true and sets Child to the relative path to the MountPoint, which is "/"
- L1469 _public function_ `static const TCHAR* GetRelativeFilePathFromMountPointer(const FString& Child, const FString& MountPoint)` — Helper function to return Filename's relative path from the mount point. Returns null if Child is not equal to MountPoint and is not a child path under MountPoint, else returns pointer to the offset within Child after the MountPoint. If child equals MountPoint, returns null; The MountPoint itself is not a valid Filename, since Filenames must have non-zero length and are added on to the MountPoint.
- L1485 _public prototype_ `static bool IsPakKeepFullDirectory();` — Returns the global,const flag for whether the current process is allowing PakFiles to keep their entire DirectoryIndex (if it exists in the PakFile on disk) rather than pruning it
- L1488 _public prototype_ `static bool IsPakWritePathHashIndex();` — Returns the global,const flag for whether UnrealPak should write a copy of the full PathHashIndex and Pruned DirectoryIndex to the PakFile
- L1491 _public prototype_ `static bool IsPakWriteFullDirectoryIndex();` — Returns the global,const flag for whether UnrealPak should write a copy of the full DirectoryIndex to the PakFile
- L1498 _private prototype_ `void Initialize(FArchive& Reader, bool bLoadIndex = true);` — Initializes the pak file.
- L1503 _private prototype_ `void LoadIndex(FArchive& Reader);` — Loads and initializes pak file index.
- L1508 _private prototype_ `EFindResult GetPakEntry(const FPakEntryLocation& FPakEntryLocation, FPakEntry* OutEntry) const;` — Returns the FPakEntry pointed to by the given FPakEntryLocation, forwards to the static GetPakEntry with data from *this
- L1513 _private prototype_ `static FIndexSettings& GetIndexSettings();`
- L1520 _private prototype_ `static bool IsPakValidatePruning();` — Returns the global,const flag for whether the current process should run directory queries on both the DirectoryIndex and the Pruned DirectoryIndex and log an error if they don't match. Validation only occurs until the first call to OptimizeMemoryUsageForMountedPaks, after which the Full DirectoryIndex is dropped and there is nothing left to Validate Has the same effect as IsPakDelayPruning, plus the addition of the error for any mismatches.
- L1526 _private prototype_ `static bool IsPakDelayPruning();` — Returns the global,const flag for whether the current process should keep a copy of the Full DirectoryIndex around until OptimizeMemoryUsageForMountedPaks is called, so that systems can run directory queries against the full index until then. Note that validation will still occur if IsPakValidatePruning is true.
- L1530 _private member_ `static bool bSomePakNeedsPruning;` — Global flag for whether a Pak has indicated it needs Pruning
- L1537 _private prototype_ `bool RequiresDirectoryIndexLock() const;` — Returns whether read accesses against the DirectoryIndex need to be guarded using this->DirectoryIndexLock. Locking is not required if the pak is not going to be pruned or already has been; the DirectoryIndex is immutable after that point, and we can get a performance benefit by skipping the lock.
- L1542 _private prototype_ `bool ShouldValidatePrunedDirectory() const;` — Returns whether the current Process IsPakValidatePruning and this PakFile has a Full DirectoryIndex and Pruned DirectoryIndex to validate.
- L1548 _private prototype_ `bool ShouldUseDirectoryTree() const;` — Returns whether the current PakFile is using a TDirectoryTree for storage of its DirectoryTreeIndex rather than a TMap. Returns false if !ENABLE_PAKFILE_USE_DIRECTORY_TREE or if PakFile TDirectoryTrees are disabled.
- L1563 _private prototype_ `static void AddEntryToIndex(const FString& Filename, const FPakEntryLocation& EntryLocation, const FString& MountPoint, uint64 PathHashSeed, FDirectoryIndex* DirectoryIndex, FDirectoryTreeIndex* DirectoryTreeIndex, FPathHashIndex* PathHashIndex, TMap<uint64, FString>* CollisionDetection, int32 PakFileVersion);` — Add the given (Filename,FPakEntryLocation) value into the provided indexes @param Filename The filename to add @param EntryLocation The FPakEntryLocation to add @param MountPoint The mount point of the pakfile containing the FPakEntryLocation, used to create the filename in the DirectoryIndex @param PathHashSeed the pakfile-specific seed for the hash of the path in the PathHasIndex @param DirectoryIndex Optional FDirectoryIndex into which to insert the (Filename, FPakEntryLocation) @param DirectoryTreeIndex Optional FDirectoryTreeIndex into which to insert the (Filename, FPakEntryLocation) @param PathHashIndex Optional FPathHashIndex into which to insert the (Filename, FPakEntryLocation) @param InOutCollisionDetection Optional parameter to detect hash collisions.  If present, the hashed filename will be check()'d for a collision against a different filename in InOutCollisionDetection, and will be added into InOutCollisionDetection @param PakFileVersion Version of the pakfile containing the index, to support legacy formats
- L1569 _private prototype_ `static bool EncodePakEntry(FArchive& Ar, const FPakEntry& InPakEntry, const FPakInfo& InInfo);` — Encodes a pak entry as an array of bytes into the given archive.  Returns true if encoding succeeded.  If encoding did not succeed, caller will need to store the InPakEntry in an unencoded list
- L1572 _private prototype_ `static void DecodePakEntry(const uint8* SourcePtr, FPakEntry& OutEntry, const FPakInfo& InInfo);` — Decodes a bit-encoded pak entry from a pointer to the start of its encoded bytes into the given OutEntry
- L1575 _private prototype_ `bool LoadIndexInternal(FArchive& Reader, FDirectoryIndex& OutDirectoryTMap, FDirectoryTreeIndex& OutDirectoryTree, FDirectoryIndex& OutPrunedDirectoryTMap, FDirectoryTreeIndex& OutPrunedDirectoryTree, bool bStoreDirectoryTMap, bool bStoreDirectoryTree);` — Internal index loading function that returns false if index loading fails due to an intermittent IO error. Allows LoadIndex to retry or throw a fatal as required
- L1578 _private prototype_ `void LoadIndexInternal_DirectoryIndex(FArchive& Ar, FDirectoryIndex& OutDirectoryTMap, FDirectoryTreeIndex& OutDirectoryTree, bool bLoadIntoDirectoryTMap, bool bLoadIntoDirectoryTree);`
- L1582 _public prototype_ `static void SaveIndexInternal_DirectoryIndex(FArchive& Ar, const FDirectoryIndex& DirectoryTMap);`
- L1586 _private prototype_ `bool LoadLegacyIndex(FArchive& Reader, FDirectoryIndex& OutDirectoryTMap);` — Legacy index loading function for PakFiles saved before FPakInfo::PakFile_Version_PathHashIndex
- L1589 _private prototype_ `bool DecryptAndValidateIndex(FArchive& Reader, TArray<uint8>& IndexData, FSHAHash& InExpectedHash, FSHAHash& OutActualHash);` — Helper function for LoadIndexInternal; each array of Index bytes read from the file needs to be independently decrypted and checked for corruption
- L1592 _private prototype_ `void AddSpecialFile(const FPakEntry& Entry, const FString& Filename);` — Manually add a file to a pak file
- L1594 _private prototype_ `static void PruneDirectoryIndexInternal(FDirectoryIndex* InOutDirectoryIndex, FDirectoryTreeIndex* InOutDirectoryTreeIndex, FDirectoryIndex* PrunedDirectoryIndex, FDirectoryTreeIndex* PrunedDirectoryTreeIndex, const FString& MountPoint);`
- L1609 _private prototype_ `template <typename ShouldVisitFunc, class ContainerType> void FindPrunedFilesAtPathInternal(const TCHAR* InPath, ContainerType& OutFiles, const FVisitFilter<ShouldVisitFunc>& VisitFilter) const;`
- L1615 _private prototype_ `const FPakEntryLocation* FindLocationFromIndex(const FString& FullPath, const FDirectoryIndex& InDirectoryIndex, const FDirectoryTreeIndex& InDirectoryTreeIndex) const;` — Lookup the FPakEntryLocation stored in the given DirectoryIndex or DirectoryTreeIndex, return nullptr if not found
- L1624 _private prototype_ `template <typename ShouldVisitFunc, class ContainerType> void FindFilesAtPathInIndex(const FDirectoryIndex& TargetIndex, const FDirectoryTreeIndex& TargetTreeIndex, ContainerType& OutFiles, const FString& FullSearchPath, const FVisitFilter<ShouldVisitFunc>& VisitFilter) const;` — Search the given FDirectoryIndex for all files under the given Directory.  Helper for FindFilesAtPath, called separately on the DirectoryIndex or Pruned DirectoryIndex. Does not use FScopedPakDirectoryIndexAccess internally; caller is responsible for calling from within a lock. Returned paths are full paths (include the mount point)
- L1630 _private prototype_ `template <typename ShouldVisitFunc, class ContainerType> void FindFilesAtPathInTreeIndexInternal(FStringView RelSearchPath, const FDirectoryTreeIndex& TargetTreeIndex, ContainerType& OutFiles, TArray<FString>& OutDirectories, const FString& FullSearchPath, const FVisitFilter<ShouldVisitFunc>& VisitFilter) const;`
- L1636 _private prototype_ `template <class ContainerType> bool ValidateDirectoryTreeSearchConsistency(const ContainerType& FilesTree, const TArray<FString>& DirectoriesInPakTree, const ContainerType& FilesIndexed, const TArray<FString>& DirectoriesInPakIndexed) const;`
- L1641 _private prototype_ `template <typename ShouldVisitFunc, class ContainerType> void FindFilesAtPathInIndexInternal(const FStringView& RelSearchPath, const FDirectoryIndex& TargetIndex, ContainerType& OutFiles, TArray<FString>& OutDirectories, const FString& FullSearchPath, const FVisitFilter<ShouldVisitFunc>& VisitFilter) const;`
- L1646 _private prototype_ `template <typename ShouldVisitFunc, class ContainerType> static void FindFilesAtPathInPakDirectoryInternal(const FString& MountPoint, FStringView RelPathInIndex, const FPakDirectory& PakDirectory, ContainerType& OutFiles, TArray<FString>& OutDirectoriesInPak, const FString& FullSearchPath, const FVisitFilter<ShouldVisitFunc>& VisitFilter);`
- L1651 _private prototype_ `bool NormalizeDirectoryQuery(const TCHAR* InPath, FString& OutRelativePathFromMount) const;` — Converts the path to a RelativePathFromMount and normalizes it to the expected format for Pak Directories.  Returns false if Path is not under the MountDir and hence can not be in this PakFile.
- L1657 _private prototype_ `const FPakDirectory* FindPrunedDirectoryInternal(const FString& RelativePathFromMount) const;` — Looks up the given Normalized RelativePath in the Pruned DirectoryIndex and returns the directory if found. Validates the result if IsPakValidatePruning. Does not use a critical section; caller is responsible for calling from within an FScopedPakDirectoryIndexAccess
- L1658 _private prototype_ `const FPakDirectory* FindPrunedDirectoryInIndexInternal(const FString& RelativePathFromMount, const FDirectoryIndex& InDirectoryIndex, const FDirectoryTreeIndex& InTreeIndex) const;`
- L1663 _private prototype_ `void ValidateDirectorySearch(const TSet<FString>& FoundFullFiles, const TSet<FString>& PrunedFoundFiles, const TCHAR* InPath) const;` — Logs an error if the two sets are not identical after removing all config-specified ignore paths

#### enum `FPakFile::ECacheType`  
`enum class ECacheType : uint8`  
_L770-774_
- desc: Pak files can share a cache or have their own
- L772 _public enumerator_ `Shared`
- L773 _public enumerator_ `Individual`

#### struct `FPakFile::FScopedPakDirectoryIndexAccess`  
`struct FScopedPakDirectoryIndexAccess`  
_L777-803_
- desc: A ReadLock wrapper that must be used to prevent threading errors around any call to FindPrunedDirectory or internal uses of DirectoryIndex
- L779 _public function_ `FScopedPakDirectoryIndexAccess(const FPakFile& InPakFile) #if ENABLE_PAKFILE_RUNTIME_PRUNING : PakFile(InPakFile) , bRequiresDirectoryIndexLock(PakFile.RequiresDirectoryIndexLock()) #endif`
- L793 _public function_ `~FScopedPakDirectoryIndexAccess()`
- L800 _public member_ `const FPakFile& PakFile;`
- L801 _public member_ `bool bRequiresDirectoryIndexLock;`

#### struct `FPakFile::FArchiveAndLastAccessTime`  
`struct FArchiveAndLastAccessTime`  
_L808-812_
- L810 _public member_ `TUniquePtr<FArchive> Archive;`
- L811 _public member_ `double LastAccessTime;`

#### enum `FPakFile::EFindResult`  
`enum class EFindResult : uint8`  
_L1066-1071_
- desc: Finds an entry in the pak file matching the given filename. @param Filename File to find. @param OutEntry The optional address of an FPakEntry instance where the found file information should be stored. Pass NULL to only check for file existence. @return Returns true if the file was found, false otherwise.
- L1068 _public enumerator_ `NotFound`
- L1069 _public enumerator_ `Found`
- L1070 _public enumerator_ `FoundDeleted`

#### enum `FPakFile::EIteratorType`  
`enum class EIteratorType : uint8`  
_L1167-1172_
- desc: Internal IteratorType used by an FBaseIterator.
- L1169 _public enumerator_ `PathHash`
- L1170 _public enumerator_ `DirectoryIndex`
- L1171 _public enumerator_ `DirectoryTree`

#### class `FPakFile::FBaseIterator`  
`class FBaseIterator`  
_L1174-1268_
- desc: Base functionality for iterating over the DirectoryIndex.
- L1178 _private member_ `const FPakFile* PakFile;` — Owner pak file.
- L1180 _private member_ `TOptional<FDirectoryIndex::TConstIterator> DirectoryIndexIt;` — Outer iterator over Directories when using the FDirectoryIndex.
- L1187 _private member_ `TUniquePtr<FDirectoryTreeIndex::FConstIterator> TreeIt;` — Outer iterator over Directories when using the FDirectoryTreeIndex. A TDirectoryTree::FConstIterator has a large struct size. Store it as a TUniquePtr rather than a TOptional so that the struct size of our struct can remain small.
- L1190 _private member_ `TOptional<FPakDirectory::TConstIterator> FileIt;` — Inner iterator over Files when using the FDirectoryIndex or FDirectoryTreeIndex.
- L1192 _private member_ `TOptional<FPathHashIndex::TConstIterator> PathHashIt;` — Iterator when using the FPathHashIndex.
- L1194 _private member_ `mutable FString CachedFilename;` — The cached filename for return in Filename().
- L1196 _private member_ `mutable FPakEntry PakEntry;` — The PakEntry for return in Info
- L1198 _private member_ `EIteratorType IteratorType;` — Which type of internal iterator this iterator and its pakfile are using.
- L1200 _private member_ `bool bIncludeDeleted;` — Whether to include delete records in the iteration.
- L1203 _private member_ `bool bRequiresDirectoryIndexLock;` — Whether this iterator needs to ReadLock and ReadUnlock due to use of the DirectoryIndex
- L1207 _public prototype_ `FBaseIterator(FBaseIterator&&) = default;`
- L1208 _public prototype_ `FBaseIterator& operator=(FBaseIterator&&) = default;`
- L1210 _public prototype_ `FBaseIterator(const FBaseIterator&) = delete;` — PakFile iterators can be large, because they have to walk a tree, so do not copy them, move construct only.
- L1211 _public prototype_ `FBaseIterator& operator=(const FBaseIterator&) = delete;`
- L1213 _public prototype_ `FBaseIterator& operator++();`
- L1216 _public prototype_ `explicit operator bool() const;` — conversion to "bool" returning true if the iterator is valid.
- L1219 _public prototype_ `bool operator !() const;` — inverse of the "bool" operator
- L1222 _public prototype_ `const FPakEntry& Info() const;` — Return the FPakEntry. Invalid to call unless the iterator is currently valid.
- L1224 _public prototype_ `bool HasFilename() const;`
- L1227 _protected prototype_ `FBaseIterator(const FPakFile& InPakFile, bool bInIncludeDeleted, bool bUsePathHash);`
- L1230 _protected prototype_ `~FBaseIterator();`
- L1234 _protected prototype_ `const FString& Filename() const;` — Return the current filename, as the RelativePath from the MountPoint.  Only available when using the FDirectoryIndex, otherwise always returns empty string. Invalid to call unless the iterator is currently valid.
- L1237 _protected prototype_ `FPakEntryLocation GetPakEntryIndex() const;` — Return the arbitrary index of the iteration. Invalid to call unless the iterator is currently valid.
- L1242 _private prototype_ `void AdvanceToValid();` — Skips over deleted records and moves to the next Directory in the DirectoryIndex when necessary.
- L1245 _private prototype_ `FPathHashIndex::TConstIterator& GetPathHashIt();` — With EIteratorType::PathHash, we have only a single iterator.
- L1246 _private prototype_ `const FPathHashIndex::TConstIterator& GetPathHashIt() const;`
- L1252 _private prototype_ `bool IsDirectoryItValid() const;` — With EIteratorType::DirectoryIndex or EIteratorType::DirectoryTree, we have an outer iterator that traverses directories in the tree, and an inner iterator that traverses files in the directory.
- L1253 _private prototype_ `void IncrementDirectoryIt();`
- L1254 _private prototype_ `FStringView GetDirectoryItKey() const;`
- L1255 _private prototype_ `const FPakDirectory& GetDirectoryItValue() const;`
- L1256 _private prototype_ `FPakDirectory::TConstIterator& GetFileIt();`
- L1257 _private prototype_ `const FPakDirectory::TConstIterator& GetFileIt() const;`
- L1260 _private prototype_ `FDirectoryIndex::TConstIterator& GetDirectoryIndexIt();` — With EIteratorType::DirectoryIndex, GetDirectoryIndexIt is the outer iterator of directories.
- L1261 _private prototype_ `const FDirectoryIndex::TConstIterator& GetDirectoryIndexIt() const;`
- L1265 _private prototype_ `FDirectoryTreeIndex::FConstIterator& GetTreeIt();` — With EIteratorType::DirectoryTree, GetTreeIt is the outer iterator of directories.
- L1266 _private prototype_ `const FDirectoryTreeIndex::FConstIterator& GetTreeIt() const;`

#### class `FPakFile::FPakEntryIterator`  
`class FPakEntryIterator : public FBaseIterator`  
_L1271-1290_
- inherits: `FBaseIterator`
- desc: Iterator class for every FPakEntry in the FPakFile, but does not provide filenames unless the PakFile has an unpruned DirectoryIndex.
- L1274 _public function_ `FPakEntryIterator(const FPakFile& InPakFile, bool bInIncludeDeleted = false) : FBaseIterator(InPakFile, bInIncludeDeleted, !InPakFile.bHasFullDirectoryIndex )`
- L1279 _public function_ `const FString* TryGetFilename() const`

#### class `FPakFile::FFilenameIterator`  
`class FFilenameIterator : public FBaseIterator`  
_L1293-1307_
- inherits: `FBaseIterator`
- desc: Iterator class used to iterate over just the files in the pak for which we have filenames.
- L1301 _public function_ `FFilenameIterator(const FPakFile& InPakFile, bool bInIncludeDeleted = false) : FBaseIterator(InPakFile, bInIncludeDeleted, false )` — Constructor. @param InPakFile Pak file to iterate.

#### struct `FPakFile::FVisitFilter`  
`template <typename ShouldVisitFunc> struct FVisitFilter`  
_L1599-1606_
- L1601 _public prototype_ `FVisitFilter(const ShouldVisitFunc& InShouldVisit, bool bInIncludeFiles, bool bInIncludeDirectories, bool bInRecursive);`
- L1602 _public member_ `const ShouldVisitFunc& ShouldVisit;`
- L1603 _public member_ `bool bIncludeFiles = true;`
- L1604 _public member_ `bool bIncludeDirectories = false;`
- L1605 _public member_ `bool bRecursive = false;`

#### class `FPakNoEncryption`  
`class FPakNoEncryption`  
_L1670-1687_
- desc: Placeholder Class
- L1678 _public function_ `static inline int64 AlignReadRequest(int64 Size)`
- L1683 _public function_ `static inline void DecryptBlock(void* Data, int64 Size, const FGuid& EncryptionKeyGuid)`

#### enum `FPakNoEncryption::(anonymous)`  
``  
_L1674-1676_

#### class `FPakReaderPolicy`  
`template< typename EncryptionPolicy = FPakNoEncryption > class FPakReaderPolicy`  
_L1695-1759_
- L1699 _public member_ `const FPakFile& PakFile;` — Pak file that own this file data
- L1701 _public member_ `FPakEntry PakEntry;` — Pak file entry for this file.
- L1703 _public member_ `TAcquirePakReaderFunction AcquirePakReader;` — Pak file archive to read the data from.
- L1705 _public member_ `int64 OffsetToFile;` — Offset to the file in pak (including the file header).
- L1707 _public function_ `FPakReaderPolicy(const FPakFile& InPakFile,const FPakEntry& InPakEntry, TAcquirePakReaderFunction& InAcquirePakReader) : PakFile(InPakFile) , PakEntry(InPakEntry) , AcquirePakReader(InAcquirePakReader)`
- L1715 _public function_ `inline int64 FileSize() const`
- L1720 _public function_ `void Serialize(int64 DesiredPosition, void* V, int64 Length) const`

#### class `FPakFileHandle`  
`template< typename ReaderPolicy = FPakReaderPolicy<> > class FPakFileHandle : public IFileHandle`  
_L1765-1904_
- inherits: `IFileHandle`
- desc: File handle to read from pak file.
- L1768 _private member_ `int64 ReadPos;` — Current read position.
- L1770 _private member_ `ReaderPolicy Reader;` — Class that controls reading from pak file
- L1772 _private member_ `TRefCountPtr<const FPakFile> PakFile;` — Reference to keep the PakFile referenced until we are destroyed
- L1783 _public function_ `FPakFileHandle(const TRefCountPtr<const FPakFile>& InPakFile, const FPakEntry& InPakEntry, TAcquirePakReaderFunction& InAcquirePakReaderFunction) : ReadPos(0) , Reader(*InPakFile, InPakEntry, InAcquirePakReaderFunction) , PakFile(InPakFile)` — Constructs pak file handle to read from pak. @param InFilename Filename @param InPakEntry Entry in the pak file. @param InAcquirePakReaderFunction Function that returns the archive to use for serialization. The result of this should not be cached, but reacquired on each serialization operation
- L1798 _public function_ `FPakFileHandle(const TRefCountPtr<const FPakFile>& InPakFile, const FPakEntry& InPakEntry, FArchive* InPakReader) : ReadPos(0) , Reader(*InPakFile, InPakEntry, InPakReader) , PakFile(InPakFile)` — Constructs pak file handle to read from pak. @param InFilename Filename @param InPakEntry Entry in the pak file. @param InPakFile Pak file.
- L1809 _public function_ `virtual ~FPakFileHandle()` — Destructor. Cleans up the reader archive if necessary.
- L1815 _public function_ `virtual int64 Tell() override`
- L1819 _public function_ `virtual bool Seek(int64 NewPosition) override`
- L1828 _public function_ `virtual bool SeekFromEnd(int64 NewPositionRelativeToEnd) override`
- L1832 _public function_ `virtual bool Read(uint8* Destination, int64 BytesToRead) override`
- L1844 _public function_ `virtual bool ReadAt(uint8* Destination, int64 BytesToRead, int64 Offset) override`
- L1853 _public function_ `virtual bool Write(const uint8* Source, int64 BytesToWrite) override`
- L1858 _public function_ `virtual int64 Size() override`
- L1862 _public function_ `virtual bool Flush(const bool bFullFlush = false) override`
- L1867 _public function_ `virtual bool Truncate(int64 NewSize) override`
- L1874 _private function_ `bool ReadInternal(uint8* Destination, int64 BytesToRead, int64 Offset)`

#### struct `FPakMountArgs`  
`struct FPakMountArgs`  
_L1909-1921_
- desc: Args for pak mounting
- L1912 _public member_ `const TCHAR* PakFilename = nullptr;` — Pak filename
- L1914 _public member_ `uint32 PakOrder = 0;` — Search order
- L1916 _public member_ `const TCHAR* Path = nullptr;` — Path to mount the pak at
- L1918 _public member_ `FPakMountOptions MountOptions;` — Mount options
- L1920 _public member_ `bool bLoadIndex = true;` — Flag to load Index

#### class `FPakPlatformFile`  
`class FPakPlatformFile : public IPlatformFile`  
_L1926-2680_
- inherits: `IPlatformFile`
- desc: Platform file wrapper to be able to use pak files.
- L1959 _private member_ `IPlatformFile* LowerLevel;` — Wrapped file
- L1961 _private member_ `TArray<FPakListEntry> PakFiles;` — List of all available pak files.
- L1963 _private member_ `TArray<FPakListDeferredEntry> PendingEncryptedPakFiles;` — List of all pak filenames with dynamic encryption where we don't have the key yet
- L1965 _private member_ `bool bSigned;` — True if this we're using signed content.
- L1967 _private member_ `mutable FTransactionallySafeCriticalSection PakListCritical;` — Synchronization object for accessing the list of currently mounted pak files.
- L1970 _private member_ `TSet<FName> ExcludedNonPakExtensions;` — Cache of extensions that we automatically reject if not found in pak file.
- L1973 _private member_ `FString IniFileExtension;` — The extension used for ini files, used for excluding ini files
- L1975 _private member_ `FString GameUserSettingsIniFilename;` — The filename for the gameusersettings ini file, used for excluding ini files, but not gameusersettings
- L1976 _private member_ `TSharedPtr<UE::IoStore::IFileIoDispatcherBackend> IoDispatcherFileBackend;`
- L1977 _private member_ `TSharedPtr<FFilePackageStoreBackend> PackageStoreBackend;`
- L1979 _private member_ `FTSTicker::FDelegateHandle RetireReadersHandle;`
- L1984 _private member_ `bool bLookLooseFirst = false;` — if true (via -lookloosefirst) then loose/non-ufs files will be looked for before looking in the .pak file this respects IsNonPakFilenameAllowed()
- L1985 _private member_ `std::atomic<bool> bProcessHasEverMountedAPakFile{ false };`
- L1991 _private function_ `inline void GetMountedPaks(TArray<FPakListEntry>& Paks)` — Gets mounted pak files
- L2003 _private prototype_ `bool DirectoryExistsInPrunedPakFiles(const TCHAR* Directory);` — Checks if a directory exists in one of the available pak files. @param Directory Directory to look for. @return true if the directory exists, false otherwise.
- L2015 _private prototype_ `bool BufferedCopyFile(IFileHandle& Dest, IFileHandle& Source, const int64 FileSize, uint8* Buffer, const int64 BufferSize) const;` — Helper function to copy a file from one handle to another usuing the supplied buffer. @param Dest Destination file handle. @param Source file handle. @param FileSize size of the source file. @param Buffer Pointer to the buffer used to copy data. @param BufferSize Sizeof of the buffer. @return true if the operation was successfull, false otherwise.
- L2025 _private prototype_ `IFileHandle* CreatePakFileHandle(const TCHAR* Filename, const TRefCountPtr<FPakFile>& PakFile, const FPakEntry* FileEntry);` — Creates file handle to read from Pak file. @param Filename Filename to create the handle for. @param PakFile Pak file to read from. @param FileEntry File entry to create the handle for. @return Pointer to the new handle.
- L2031 _private prototype_ `static int32 GetPakOrderFromPakFilePath(const FStringView PakFilePath);` — Hardcode default load ordering of game main pak -> game content -> engine content -> saved dir would be better to make this config but not even the config system is initialized here so we can't do that
- L2036 _private prototype_ `IPakFile* HandleMountPakDelegate(const FString& PakFilePath, int32 PakOrder);` — Handler for device delegate to prompt us to load a new pak.
- L2046 _private prototype_ `bool HandleUnmountPakDelegate(const FString& PakFilePath);` — Handler for device delegate to prompt us to unload a pak.
- L2054 _private prototype_ `static void FindPakFilesInDirectory(IPlatformFile* LowLevelFile, const TCHAR* Directory, const FString& WildCard, TArray<FString>& OutPakFiles);` — Finds all pak files in the given directory. @param Directory Directory to (recursively) look for pak files in @param OutPakFiles List of pak files
- L2061 _private prototype_ `static void FindAllPakFiles(IPlatformFile* LowLevelFile, const TArray<FString>& PakFolders, const FString& WildCard, TArray<FString>& OutPakFiles);` — Finds all pak files in the known pak folders @param OutPakFiles List of all found pak files
- L2069 _private prototype_ `bool IsNonPakFilenameAllowed(const FString& InFilename);` — When security is enabled, determine if this filename can be looked for in the lower level file system @param InFilename			Filename to check @param bAllowDirectories		Consider directories as valid filepaths?
- L2077 _private prototype_ `void RegisterEncryptionKey(const FGuid& InEncryptionKeyGuid, const FAES::FAESKey& InKey);` — Registers a new AES key with the given guid. Triggers the mounting of any pak files that we encountered that use that key @param InEncryptionKeyGuid	Guid for this encryption key @param InKey					Encryption key
- L2085 _private prototype_ `static bool IsPakFileInstalled(const FString& InFilename);` — Checks with any current chunk installation system if the given pak file is installed @param InFilename  the pak filename to check @return whether the pak file is installed
- L2089 _public member_ `static bool bMountFailOnMissingUtoc;`
- L2100 _public function_ `static const TCHAR* GetTypeName()` — Get the unique name for the pak platform file layer
- L2108 _public prototype_ `static const TCHAR* GetMountStartupPaksWildCard();` — Get the wild card pattern used to identify paks to load on startup
- L2113 _public prototype_ `static void SetMountStartupPaksWildCard(const FString& WildCard);` — Overrides the wildcard used for searching paks. Call before initialization
- L2118 _public prototype_ `EChunkLocation::Type GetPakChunkLocation(int32 InPakchunkIndex) const;` — Determine location information for a given pakchunk index. Will be DoesNotExist if the pak file wasn't detected, NotAvailable if it exists but hasn't been mounted due to a missing encryption key, or LocalFast if it exists and has been mounted
- L2123 _public prototype_ `bool AnyChunksAvailable() const;` — Returns true if any of the mounted or pending pak files are chunks (filenames starting pakchunkN)
- L2128 _public function_ `inline void GetMountedPakFilenames(TArray<FString>& PakFilenames)` — Get a list of all pak files which have been successfully mounted
- L2141 _public function_ `inline void GetMountedPakFilenames(TSet<FString>& PakFilenames)` — Get a list of all pak files which have been successfully mounted
- L2154 _public function_ `inline void GetMountedChunkIds(TSet<int32>& OutChunkIds)` — Gets a set of the mounted chunk Ids.
- L2167 _public prototype_ `static bool CheckIfPakFilesExist(IPlatformFile* LowLevelFile, const TArray<FString>& PakFolders);` — Checks if pak files exist in any of the known pak file locations.
- L2172 _public prototype_ `static void GetPakFolders(const TCHAR* CmdLine, TArray<FString>& OutPakFolders);` — Gets all pak file locations.
- L2177 _public prototype_ `static void GetPakEncryptionKey(FAES::FAESKey& OutKey, const FGuid& InEncryptionKeyGuid);` — Helper function for accessing pak encryption key
- L2184 _public prototype_ `static TSharedPtr<const struct FPakSignatureFile, ESPMode::ThreadSafe> GetPakSignatureFile(const TCHAR* InFilename);` — Load a pak signature file. Validates the contents by comparing a SHA hash of the chunk table against and encrypted version that is stored within the file. Returns nullptr if the data is missing or fails the signature check. This function also calls the generic pak signature failure delegates if anything is wrong.
- L2189 _public prototype_ `static void RemoveCachedPakSignaturesFile(const TCHAR* InFilename);` — Remove the intenrally cached pointer to the signature file for the specified pak
- L2196 _public prototype_ `FPakPlatformFile();` — Constructor. @param InLowerLevel Wrapper platform file.
- L2201 _public prototype_ `virtual ~FPakPlatformFile();` — Destructor.
- L2203 _public prototype_ `virtual bool ShouldBeUsed(IPlatformFile* Inner, const TCHAR* CmdLine) const override;`
- L2204 _public prototype_ `virtual bool Initialize(IPlatformFile* Inner, const TCHAR* CommandLineParam) override;`
- L2205 _public prototype_ `virtual void InitializeNewAsyncIO() override;`
- L2207 _public prototype_ `void OptimizeMemoryUsageForMountedPaks();`
- L2209 _public function_ `virtual IPlatformFile* GetLowerLevel() override`
- L2213 _public function_ `virtual void SetLowerLevel(IPlatformFile* NewLowerLevel) override`
- L2218 _public function_ `virtual const TCHAR* GetName() const override`
- L2223 _public prototype_ `void Tick() override;`
- L2235 _public prototype_ `bool Mount(const TCHAR* InPakFilename, uint32 PakOrder, const TCHAR* InPath = nullptr, bool bLoadIndex = true, FPakListEntry* OutPakListEntry = nullptr);` — Mounts a pak file at the specified path. In most cases, this should not be called directly. Instead use the mounting delegates in FCoreDelegates @param InPakFilename Pak filename. @param InPath Path to mount the pak at. @param OutPakListEntry for internal use @param OutIoMountStatus Status of the pak or associated iostore mount
- L2246 _public prototype_ `bool Mount(const FPakMountArgs& MountArgs, FIoStatus* OutIoMountStatus = nullptr, FPakListEntry* OutPakListEntry = nullptr);` — Mounts a pak file at the specified path. In most cases, this should not be called directly. Instead use the mounting delegates in FCoreDelegates @param MountArgs mount arguments @param OutIoMountStatus Status of the pak or associated iostore mount @param OutPakListEntry for internal use
- L2248 _public prototype_ `bool Unmount(const TCHAR* InPakFilename);`
- L2250 _public prototype_ `int32 MountAllPakFiles(const TArray<FString>& PakFolders);`
- L2251 _public prototype_ `int32 MountAllPakFiles(const TArray<FString>& PakFolders, const FString& WildCard);`
- L2256 _public prototype_ `bool ReloadPakReaders();` — Re-creates all the pak readers
- L2261 _public prototype_ `virtual void MakeUniquePakFilesForTheseFiles(const TArray<TArray<FString>>& InFiles);` — Make unique in memory pak files from a list of named files
- L2271 _public prototype_ `static bool FindFileInPakFiles(TArray<FPakListEntry>& Paks, const TCHAR* Filename, TRefCountPtr<FPakFile>* OutPakFile, FPakEntry* OutEntry = nullptr);` — Finds a file in the specified pak files. @param Paks Pak files to find the file in. @param Filename File to find in pak files. @param OutPakFile Optional pointer to a pak file where the filename was found. @return true if the file was found, false otherwise.
- L2281 _public prototype_ `bool FindFileInPakFiles(const TCHAR* Filename, TRefCountPtr<FPakFile>* OutPakFile = nullptr, FPakEntry* OutEntry = nullptr);` — Finds a file in all available pak files. @param Filename File to find in pak files. @param OutPakFile Optional pointer to a pak file where the filename was found. @return true if the file was found, false otherwise.
- L2285 _public function_ `virtual bool FileExists(const TCHAR* Filename) override`
- L2301 _public function_ `virtual int64 FileSize(const TCHAR* Filename) override`
- L2318 _public function_ `virtual bool DeleteFile(const TCHAR* Filename) override`
- L2334 _public function_ `virtual bool IsReadOnly(const TCHAR* Filename) override`
- L2350 _public function_ `virtual bool MoveFile(const TCHAR* To, const TCHAR* From) override`
- L2366 _public function_ `virtual bool SetReadOnly(const TCHAR* Filename, bool bNewReadOnlyValue) override`
- L2383 _public function_ `virtual FDateTime GetTimeStamp(const TCHAR* Filename) override`
- L2402 _public function_ `virtual void GetTimeStampPair(const TCHAR* FilenameA, const TCHAR* FilenameB, FDateTime& OutTimeStampA, FDateTime& OutTimeStampB) override`
- L2431 _public function_ `virtual void SetTimeStamp(const TCHAR* Filename, FDateTime DateTime) override`
- L2443 _public function_ `virtual FDateTime GetAccessTimeStamp(const TCHAR* Filename) override`
- L2460 _public function_ `virtual FString GetFilenameOnDisk(const TCHAR* Filename) override`
- L2508 _public function_ `virtual ESymlinkResult IsSymlink(const TCHAR* Filename) override`
- L2513 _public prototype_ `virtual IFileHandle* OpenRead(const TCHAR* Filename, bool bAllowWrite = false) override;`
- L2514 _public prototype_ `virtual IFileHandle* OpenWrite(const TCHAR* Filename, bool bAppend = false, bool bAllowRead = false) override;`
- L2517 _public prototype_ `virtual bool DirectoryExists(const TCHAR* Directory) override;`
- L2518 _public prototype_ `virtual bool CreateDirectory(const TCHAR* Directory) override;`
- L2519 _public prototype_ `virtual bool DeleteDirectory(const TCHAR* Directory) override;`
- L2520 _public prototype_ `virtual FFileStatData GetStatData(const TCHAR* FilenameOrDirectory) override;`
- L2521 _public prototype_ `virtual bool IterateDirectory(const TCHAR* Directory, IPlatformFile::FDirectoryVisitor& Visitor) override;`
- L2523 _public prototype_ `virtual bool IterateDirectoryRecursively(const TCHAR* Directory, IPlatformFile::FDirectoryVisitor& Visitor) override;`
- L2525 _public prototype_ `virtual bool IterateDirectoryStat(const TCHAR* Directory, IPlatformFile::FDirectoryStatVisitor& Visitor) override;`
- L2527 _public prototype_ `virtual bool IterateDirectoryStatRecursively(const TCHAR* Directory, IPlatformFile::FDirectoryStatVisitor& Visitor) override;`
- L2529 _public prototype_ `virtual void FindFiles(TArray<FString>& FoundFiles, const TCHAR* Directory, const TCHAR* FileExtension) override;`
- L2531 _public prototype_ `virtual void FindFilesRecursively(TArray<FString>& FoundFiles, const TCHAR* Directory, const TCHAR* FileExtension) override;`
- L2533 _public prototype_ `virtual bool DeleteDirectoryRecursively(const TCHAR* Directory) override;`
- L2534 _public prototype_ `virtual bool CreateDirectoryTree(const TCHAR* Directory) override;`
- L2536 _public prototype_ `virtual bool CopyFile(const TCHAR* To, const TCHAR* From, EPlatformFileRead ReadFlags = EPlatformFileRead::None, EPlatformFileWrite WriteFlags = EPlatformFileWrite::None) override;`
- L2538 _public prototype_ `virtual IAsyncReadFileHandle* OpenAsyncRead(const TCHAR* Filename, bool bAllowWrite = false) override;`
- L2539 _public prototype_ `virtual void SetAsyncMinimumPriority(EAsyncIOPriorityAndFlags Priority) override;`
- L2541 _public prototype_ `virtual FOpenMappedResult OpenMappedEx(const TCHAR* Filename, EOpenReadFlags OpenOptions = EOpenReadFlags::None, int64 MaximumSize = 0) override;`
- L2542 _public prototype_ `virtual FOpenMappedResult OpenMappedEx2(const TCHAR* Filename, EOpenMappedFlags OpenOptions = EOpenMappedFlags::None, int64 MaximumSize = 0) override;`
- L2554 _public function_ `FString ConvertToPakRelativePath(const TCHAR* Filename, const FPakFile* Pak)` — Converts a filename to a path inside pak file. @param Filename Filename to convert. @param Pak Pak to convert the filename realative to. @param Relative filename.
- L2560 _public function_ `FString ConvertToAbsolutePathForExternalAppForRead(const TCHAR* Filename) override`
- L2574 _public function_ `FString ConvertToAbsolutePathForExternalAppForWrite(const TCHAR* Filename) override`
- L2593 _public prototype_ `void RefreshPakChunkIndicies();` — Requests that all the known paks re-evaluate and set their PakchunkIndex value. Used to allow the AssetManager inform the pak file system about potential name pak chunk overrides.
- L2596 _public prototype_ `static FFilenameSecurityDelegate& GetFilenameSecurityDelegate();` — Access static delegate for loose file security
- L2599 _public prototype_ `static FPakCustomEncryptionDelegate& GetPakCustomEncryptionDelegate();` — Access static delegate for custom encryption
- L2620 _public prototype_ `static FPakSigningFailureHandlerData& GetPakSigningFailureHandlerData();` — Access static delegate for handling a Pak signature check failure
- L2623 _public prototype_ `static void BroadcastPakChunkSignatureCheckFailure(const FPakChunkSignatureCheckFailedData& InData);` — Broadcast a signature check failure through any registered delegates in a thread safe way
- L2626 _public prototype_ `static void BroadcastPakPrincipalSignatureTableCheckFailure(const FString& InFilename);` — Broadcast a principal signature table failure through any registered delegates in a thread safe way
- L2629 _public prototype_ `static void BroadcastPakMasterSignatureTableCheckFailure(const FString& InFilename);` — `UE_DEPRECATED("5.1", "Use BroadcastPakPrincipalSignatureTableCheckFailure instead")`
- L2632 _public prototype_ `static FPakSetIndexSettings& GetPakSetIndexSettingsDelegate();` — Access static delegate for setting PakIndex settings.
- L2635 _public prototype_ `void GetPrunedFilenamesInChunk(const FString& InPakFilename, const TArray<int32>& InChunkIDs, TArray<FString>& OutFileList);` — Get a list of RelativePathFromMount for every file in the given Pak that lives in any of the given chunks.  Only searches the Pruned DirectoryIndex
- L2638 _public prototype_ `void GetPrunedFilenamesInPakFile(const FString& InPakFilename, TArray<FString>& OutFileList);` — Gets a list of FullPaths (includes Mount directory) for every File in the given Pak's Pruned DirectoryIndex
- L2641 _public prototype_ `static void GetFilenamesFromIostoreContainer(const FString& InContainerName, TArray<FString>& OutFileList);` — Returns the RelativePathFromMount Filename for every file found in the given Iostore Container
- L2644 _public prototype_ `static void GetFilenamesFromIostoreByBlockIndex(const FString& InContainerName, const TArray<int32>& InBlockIndex, TArray<FString>& OutFileList);` — Returns the RelativePathFromMount Filename for every Filename found in the Iostore Container that relates to the provided block indexes
- L2647 _public prototype_ `static void ForeachPackageInIostoreWhile(TFunctionRef<bool(FName)> Predicate);` — Iterates Iostore Container while Predicate returns true
- L2649 _public prototype_ `void ReleaseOldReaders();`
- L2653 _public prototype_ `void HandlePakListCommand(const TCHAR* Cmd, FOutputDevice& Ar);`
- L2654 _public prototype_ `void HandleMountCommand(const TCHAR* Cmd, FOutputDevice& Ar);`
- L2655 _public prototype_ `void HandleUnmountCommand(const TCHAR* Cmd, FOutputDevice& Ar);`
- L2656 _public prototype_ `void HandlePakCorruptCommand(const TCHAR* Cmd, FOutputDevice& Ar);`
- L2657 _public prototype_ `void HandleReloadPakReadersCommand(const TCHAR* Cmd, FOutputDevice& Ar);`
- L2662 _public member_ `static TMap<FString, int32> GPakSizeMap;`
- L2663 _public prototype_ `static void TrackPak(const TCHAR* Filename, const FPakEntry* PakEntry);`
- L2664 _public function_ `static TMap<FString, int32>& GetPakMap()`
- L2668 _public member_ `static TMap<FName, TSharedPtr<const struct FPakSignatureFile, ESPMode::ThreadSafe>> PakSignatureFileCache;` — Internal cache of pak signature files
- L2669 _public member_ `static FCriticalSection PakSignatureFileCacheLock;`
- L2672 _private prototype_ `bool IterateDirectoryInternal(const TCHAR* Directory, IPlatformFile::FDirectoryVisitor& Visitor, bool bRecursive);`
- L2673 _private prototype_ `bool IterateDirectoryInPakFiles(const TCHAR* Directory, UE::PakFile::Private::FPakFileDirectoryVisitorBase& Visitor, bool bRecursive, TSet<FString>& FilesVisitedInPak);`
- L2676 _private prototype_ `bool IterateDirectoryStatInternal(const TCHAR* Directory, IPlatformFile::FDirectoryStatVisitor& Visitor, bool bRecursive);`
- L2678 _private prototype_ `void FindFilesInternal(TArray<FString>& FoundFiles, const TCHAR* Directory, const TCHAR* FileExtension, bool bRecursive);`

#### struct `FPakPlatformFile::FPakListEntry`  
`struct FPakListEntry`  
_L1928-1942_
- L1930 _public function_ `FPakListEntry() : ReadOrder(0) , PakFile(nullptr)`
- L1935 _public member_ `uint32 ReadOrder;`
- L1936 _public member_ `TRefCountPtr<FPakFile> PakFile;`
- L1938 _public function_ `inline bool operator < (const FPakListEntry& RHS) const`

#### struct `FPakPlatformFile::FPakListDeferredEntry`  
`struct FPakListDeferredEntry`  
_L1947-1956_
- L1949 _public member_ `FString Filename;`
- L1950 _public member_ `FString Path;`
- L1951 _public member_ `uint32 ReadOrder;`
- L1952 _public member_ `FGuid EncryptionKeyGuid;`
- L1953 _public member_ `int32 PakchunkIndex;`
- L1954 _public member_ `FPakMountOptions MountOptions;`
- L1955 _public member_ `bool bLoadIndex = true;`

#### struct `FPakPlatformFile::FPakSigningFailureHandlerData`  
`struct FPakSigningFailureHandlerData`  
_L2601-2617_
- L2604 _public function_ `FCriticalSection& GetLock()`
- L2605 _public function_ `FPakChunkSignatureCheckFailedHandler& GetPakChunkSignatureCheckFailedDelegate()`
- L2606 _public function_ `FPakPrincipalSignatureTableCheckFailureHandler& GetPrincipalSignatureTableCheckFailedDelegate()`
- L2610 _public member_ `FCriticalSection Lock;` — `UE_DEPRECATED("5.1", "Use GetLock instead")`
- L2613 _public member_ `FPakChunkSignatureCheckFailedHandler ChunkSignatureCheckFailedDelegate;` — `UE_DEPRECATED("5.1", "Use GetPakChunkSignatureCheckFailedDelegate instead")`
- L2616 _public member_ `FPakPrincipalSignatureTableCheckFailureHandler MasterSignatureTableCheckFailedDelegate;` — `UE_DEPRECATED("5.1", "Use GetPrincipalSignatureTableCheckFailureDelegate instead")`

#### struct `FPakSignatureFile`  
`struct FPakSignatureFile`  
_L2685-2802_
- desc: Structure which describes the content of the pak .sig files
- L2688 _public member_ `static const uint32 Magic = 0x73832DAA;` — Magic number that tells us we're dealing with the new format sig files
- L2700 _public member_ `EVersion Version = EVersion::Latest;` — Sig file version. Set to Legacy if the sig file is of an old version
- L2703 _public member_ `TArray<uint8> EncryptedHash;` — RSA encrypted hash
- L2706 _public member_ `FSHAHash DecryptedHash;` — SHA1 hash of the chunk CRC data. Only valid after calling DecryptSignatureAndValidate
- L2709 _public member_ `TArray<uint8> SignatureData;` — The actual array of data that was encrypted in the RSA block. Contains the chunk table hash and also other custom data related to the pak file
- L2712 _public member_ `TArray<TPakChunkHash> ChunkHashes;` — CRCs of each contiguous 64kb block of the pak file
- L2717 _public function_ `void SetChunkHashesAndSign(const TArray<TPakChunkHash>& InChunkHashes, const TArrayView<uint8>& InSignatureData, const FRSAKeyHandle InKey)` — Initialize and hash the CRC list then use the provided private key to encrypt the hash
- L2732 _public function_ `void Serialize(FArchive& Ar)` — Serialize/deserialize this object to/from an FArchive
- L2753 _public function_ `bool DecryptSignatureAndValidate(const FRSAKeyHandle InKey, const FString& InFilename)` — Decrypt the chunk CRCs hash and validate that it matches the current one
- L2790 _public function_ `FSHAHash ComputeCurrentPrincipalHash() const` — Helper function for computing the SHA1 hash of the current chunk CRC array
- L2798 _public function_ `FSHAHash ComputeCurrentMasterHash() const` — `UE_DEPRECATED("5.1", "Use ComputeCurrentPrincipalHash instead")`

#### enum `FPakSignatureFile::EVersion`  
`enum class EVersion`  
_L2690-2697_
- L2692 _public enumerator_ `Invalid`
- L2693 _public enumerator_ `First`
- L2695 _public enumerator_ `Last`
- L2696 _public enumerator_ `Latest = Last - 1`

#### Free symbols / members of external scopes

- L57 _macro_ `#define ENABLE_PAKFILE_USE_DIRECTORY_TREE 1`
- L65 _macro_ `#define EXCLUDE_NONPAK_UE_EXTENSIONS (!WITH_EDITOR)` — By default EXCLUDE_NONPAK_UE_EXTENSIONS is defined in runtime game and not defined in editor. Use .Build.cs file to define it to 0 if the game relies on accessing loose files. This functionality is not needed in Editor configurations using pak files, because Editor always includes the possibility of any type being uncooked on disk and not in pak.
- L75 _namespace_ `namespace UE`
- L75 _namespace_ `namespace PakFile` (scope `UE`)
- L75 _namespace_ `namespace Private` (scope `UE::PakFile`)
- L83 _namespace_ `namespace UE`
- L83 _namespace_ `namespace IoStore` (scope `UE`)
- L86 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogPakFile, Log, All);`
- L87 _delegate_ `DECLARE_FLOAT_ACCUMULATOR_STAT_EXTERN(TEXT("Total pak file read time"), STAT_PakFile_Read, STATGROU`
- L89 _delegate_ `DECLARE_DWORD_ACCUMULATOR_STAT_EXTERN(TEXT("Num open pak file handles"), STAT_PakFile_NumOpenHandles, STATGRO`
- L91 _macro_ `#define PAK_TRACKER 0`
- L96 _macro_ `#define ENABLE_PAKFILE_RUNTIME_PRUNING 1`
- L98 _macro_ `#define ENABLE_PAKFILE_RUNTIME_PRUNING_VALIDATE ENABLE_PAKFILE_RUNTIME_PRUNING && !UE_BUILD_SHIPPING`
- L101 _macro_ `#define PAKHASH_USE_CRC 1` — Define the type of a chunk hash. Currently selectable between SHA1 and CRC32.
- L103 _typedef_ `typedef uint32 TPakChunkHash;`
- L105 _typedef_ `typedef FSHAHash TPakChunkHash;`
- L108 _prototype_ `TPakChunkHash ComputePakChunkHash(const void* InData, int64 InDataSizeInBytes);`
- L109 _function_ `inline FString ChunkHashToString(const TPakChunkHash& InHash)`
- L135 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FFilenameSecurityDelegate, const TCHAR* );` — Delegate for allowing a game to restrict the accessing of non-pak files
- L135 _prototype_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FFilenameSecurityDelegate, const TCHAR* );` — Delegate for allowing a game to restrict the accessing of non-pak files
- L136 _delegate_ `DECLARE_DELEGATE_ThreeParams(FPakCustomEncryptionDelegate, uint8* , uint32 , FGuid );`
- L136 _prototype_ `DECLARE_DELEGATE_ThreeParams(FPakCustomEncryptionDelegate, uint8* , uint32 , FGuid );`
- L137 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FPakChunkSignatureCheckFailedHandler, const FPakChunkSignatureCheckFailedData&);`
- L137 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FPakChunkSignatureCheckFailedHandler, const FPakChunkSignatureCheckFailedData&);`
- L138 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FPakPrincipalSignatureTableCheckFailureHandler, const FString&);`
- L138 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FPakPrincipalSignatureTableCheckFailureHandler, const FString&);`
- L140 _delegate_ `DECLARE_DELEGATE_ThreeParams(FPakSetIndexSettings, bool& , bool& , bool& );` — Delegate which allows a project to configure Index Pruning.  This is a delegate instead of a config file because config files are loaded after the first PakFiles
- L140 _prototype_ `DECLARE_DELEGATE_ThreeParams(FPakSetIndexSettings, bool& , bool& , bool& );` — Delegate which allows a project to configure Index Pruning.  This is a delegate instead of a config file because config files are loaded after the first PakFiles
- L143 _typedef_ `typedef FPakPrincipalSignatureTableCheckFailureHandler FPakMasterSignatureTableCheckFailureHandler;` — `UE_DEPRECATED("5.1", "Use FPakPrincipalSignatureTableCheckFailureHandler instead")`
- L152 _enumerator_ `PakFile_Magic = 0x5A6F12E1` (scope `FPakInfo::__anonb5d7e7e20103`) — Magic number to use in header
- L154 _enumerator_ `MaxChunkDataSize = 64*1024` (scope `FPakInfo::__anonb5d7e7e20103`) — Size of cached data.
- L156 _enumerator_ `CompressionMethodNameLen = 32` (scope `FPakInfo::__anonb5d7e7e20103`) — Length of a compression format name
- L158 _enumerator_ `MaxNumCompressionMethods=5` (scope `FPakInfo::__anonb5d7e7e20103`) — Number of allowed different methods
- L164 _enumerator_ `PakFile_Version_Initial = 1` (scope `FPakInfo::__anonb5d7e7e20203`)
- L165 _enumerator_ `PakFile_Version_NoTimestamps = 2` (scope `FPakInfo::__anonb5d7e7e20203`)
- L166 _enumerator_ `PakFile_Version_CompressionEncryption = 3` (scope `FPakInfo::__anonb5d7e7e20203`)
- L167 _enumerator_ `PakFile_Version_IndexEncryption = 4` (scope `FPakInfo::__anonb5d7e7e20203`)
- L168 _enumerator_ `PakFile_Version_RelativeChunkOffsets = 5` (scope `FPakInfo::__anonb5d7e7e20203`)
- L169 _enumerator_ `PakFile_Version_DeleteRecords = 6` (scope `FPakInfo::__anonb5d7e7e20203`)
- L170 _enumerator_ `PakFile_Version_EncryptionKeyGuid = 7` (scope `FPakInfo::__anonb5d7e7e20203`)
- L171 _enumerator_ `PakFile_Version_FNameBasedCompressionMethod = 8` (scope `FPakInfo::__anonb5d7e7e20203`)
- L172 _enumerator_ `PakFile_Version_FrozenIndex = 9` (scope `FPakInfo::__anonb5d7e7e20203`)
- L173 _enumerator_ `PakFile_Version_PathHashIndex = 10` (scope `FPakInfo::__anonb5d7e7e20203`)
- L174 _enumerator_ `PakFile_Version_Fnv64BugFix = 11` (scope `FPakInfo::__anonb5d7e7e20203`)
- L175 _enumerator_ `PakFile_Version_Utf8PakDirectory = 12` (scope `FPakInfo::__anonb5d7e7e20203`)
- L178 _enumerator_ `PakFile_Version_Last` (scope `FPakInfo::__anonb5d7e7e20203`)
- L179 _enumerator_ `PakFile_Version_Invalid` (scope `FPakInfo::__anonb5d7e7e20203`)
- L180 _enumerator_ `PakFile_Version_Latest = PakFile_Version_Last - 1` (scope `FPakInfo::__anonb5d7e7e20203`)
- L386 _function_ `inline FArchive& operator<<(FArchive& Ar, FPakCompressedBlock& Block)`
- L698 _function_ `inline FArchive& operator<<(FArchive& Ar, FPakEntryLocation& PakEntryLocation)`
- L737 _typedef_ `typedef TMap<FUtf8String, FPakEntryLocation> FPakDirectory;` — Pak directory type mapping a filename to an FPakEntryLocation.
- L739 _namespace_ `namespace UE`
- L739 _namespace_ `namespace PakFile` (scope `UE`)
- L739 _namespace_ `namespace Private` (scope `UE::PakFile`)
- L742 _typedef_ `typedef TDirectoryTree<FPakDirectory> FDirectoryTreeIndex;` (scope `UE::PakFile::Private`)
- L1675 _enumerator_ `Alignment = 1` (scope `FPakNoEncryption::__anonb5d7e7e20303`)
- L1692 _typedef_ `typedef TFunction<FSharedPakReader()> TAcquirePakReaderFunction;` — Typedef for a function that returns an archive to use for accessing an underlying pak file

### `Source/Runtime/PakFile/Public/MountPaksExArgs.h` (Public)


#### struct `UE::FMountPaksExArgs`  
`struct FMountPaksExArgs`  
_L11-23_
- L19 _public member_ `const TCHAR* PakFilePath = nullptr;`
- L20 _public member_ `int32 Order = INDEX_NONE;`
- L21 _public member_ `FPakMountOptions MountOptions;`
- L22 _public member_ `TValueOrError<FMountResult, UE::UnifiedError::FError> Result = MakeValue();`

#### struct `UE::FMountPaksExArgs::FMountResult`  
`struct FMountResult`  
_L13-17_
- L16 _public member_ `IPakFile* PakFile = nullptr;` — Any pak file that was mounted, may be null on success if an encryption key is pending

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
