# Runtime / MetalRHI

- module root: `Source/Runtime/Apple/MetalRHI`
- headers: 53; symbols: 2502
- symbol kinds: class=72, delegate=43, enum=43, enumerator=267, externvar=4, function=294, macro=37, member=767, namespace=7, prototype=800, struct=94, typedef=59, union=2, variable=13
- PrivateDependencyModuleNames: ApplicationCore, Core, Engine, Projects, RHI, RHICore, RenderCore, Slate, SlateCore, TraceLog
- PublicIncludePathModuleNames: MetalCPP

### `Source/Runtime/Apple/MetalRHI/Private/MetalBindlessDescriptors.h` (Private)


#### enum `EMetalDescriptorUpdateType`  
`enum class EMetalDescriptorUpdateType`  
_L18-22_
- L20 _public enumerator_ `Immediate`
- L21 _public enumerator_ `GPU`

#### struct `FMetalPendingDescriptorUpdates`  
`struct FMetalPendingDescriptorUpdates`  
_L24-48_
- L26 _public member_ `TArray<uint32> Indices;`
- L27 _public member_ `TArray<IRDescriptorTableEntry> Descriptors;`
- L29 _public function_ `int32 Num() const`
- L34 _public function_ `void Add(FRHIDescriptorHandle InHandle, const IRDescriptorTableEntry& InDescriptor)`
- L43 _public function_ `void Empty()`

#### struct `FMetalDescriptorHeap`  
`struct FMetalDescriptorHeap`  
_L50-92_
- L52 _public prototype_ `FMetalDescriptorHeap(FMetalDevice& MetalDevice, ERHIDescriptorTypeMask InTypeMask);`
- L53 _public prototype_ `~FMetalDescriptorHeap();`
- L55 _public prototype_ `void Init(FRHICommandListBase& RHICmdList, int32 HeapSize);`
- L57 _public prototype_ `FRHIDescriptorHandle AllocateDescriptor(ERHIDescriptorType DescriptorType);`
- L58 _public prototype_ `FRHIDescriptorHandle AllocateDescriptor(ERHIDescriptorType DescriptorType, IRDescriptorTableEntry DescriptorData);`
- L59 _public prototype_ `void FreeDescriptor(FRHIDescriptorHandle DescriptorHandle);`
- L61 _public prototype_ `void UpdateDescriptorImmediately(FRHIDescriptorHandle DescriptorHandle, IRDescriptorTableEntry DescriptorData);`
- L62 _public prototype_ `void BindToEncoder(FMetalCommandEncoder* Encoder, MTL::FunctionType FunctionType, uint32 BindIndex);`
- L64 _public function_ `ERHIDescriptorTypeMask GetTypeMask() const`
- L69 _public function_ `bool HandlesAllocation(ERHIDescriptorType InType) const`
- L74 _public function_ `FMetalRHIBuffer* GetHeap() const`
- L80 _private function_ `IRDescriptorTableEntry* GetDescriptorMemory()`
- L86 _private member_ `FMetalDevice& Device;`
- L88 _private member_ `FRHIHeapDescriptorAllocator* Manager = nullptr;`
- L89 _private member_ `TRefCountPtr<FMetalRHIBuffer> ResourceHeap;`
- L91 _private member_ `const ERHIDescriptorTypeMask TypeMask;`

#### class `FMetalBindlessDescriptorManager`  
`class FMetalBindlessDescriptorManager`  
_L94-141_
- L97 _public prototype_ `FMetalBindlessDescriptorManager(FMetalDevice& MetalDevice);`
- L98 _public prototype_ `~FMetalBindlessDescriptorManager();`
- L100 _public prototype_ `void Init();`
- L102 _public prototype_ `FRHIDescriptorHandle AllocateDescriptor(ERHIDescriptorType DescriptorType);`
- L103 _public prototype_ `FRHIDescriptorHandle AllocateDescriptor(ERHIDescriptorType DescriptorType, MTL::Texture* Texture);`
- L104 _public prototype_ `FRHIDescriptorHandle AllocateDescriptor(ERHIDescriptorType DescriptorType, FMetalBuffer* Buffer, const uint32_t ExtraOffset = 0);`
- L105 _public prototype_ `FRHIDescriptorHandle AllocateDescriptor(MTL::SamplerState* SamplerState);`
- L107 _public prototype_ `void FreeDescriptor(FRHIDescriptorHandle DescriptorHandle);`
- L109 _public prototype_ `void UpdateDescriptor(FRHICommandListBase& RHICmdList, FRHIDescriptorHandle DescriptorHandle, IRDescriptorTableEntry Descriptor, EMetalDescriptorUpdateType UpdateType);`
- L110 _public prototype_ `void UpdateDescriptor(FRHICommandListBase& RHICmdList, FRHIDescriptorHandle DescriptorHandle, MTL::Texture* Texture, EMetalDescriptorUpdateType UpdateType);`
- L111 _public prototype_ `void UpdateDescriptor(FRHICommandListBase& RHICmdList, FRHIDescriptorHandle DescriptorHandle, FMetalBuffer* Buffer, EMetalDescriptorUpdateType UpdateType);`
- L112 _public prototype_ `void UpdateDescriptor(FMetalRHICommandContext* Context, FRHIDescriptorHandle DescriptorHandle, FMetalResourceViewBase* Resource, EMetalDescriptorUpdateType UpdateType);`
- L114 _public prototype_ `void FlushPendingDescriptorUpdates(FMetalRHICommandContext& Context, const FMetalPendingDescriptorUpdates& PendingDescriptorUpdates);`
- L115 _public prototype_ `void BindDescriptorHeapsToEncoder(FMetalCommandEncoder* Encoder, MTL::FunctionType FunctionType, EMetalShaderStages Frequency);`
- L117 _public function_ `FMetalRHIBuffer* GetStandardResourceHeap()`
- L123 _public function_ `FMetalRHIBuffer* GetSamplerResourceHeap()`
- L129 _public function_ `bool IsSupported() const`
- L135 _private member_ `FMetalDevice& Device;`
- L137 _private member_ `FMetalDescriptorHeap StandardResources;`
- L138 _private member_ `FMetalDescriptorHeap SamplerResources;`
- L140 _private member_ `bool bIsSupported = false;`

### `Source/Runtime/Apple/MetalRHI/Private/MetalBuffer.h` (Private)


#### struct `FMetalPooledBufferArgs`  
`struct FMetalPooledBufferArgs`  
_L16-34_
- L18 _public function_ `FMetalPooledBufferArgs() : Device(nullptr), Size(0), Flags(BUF_None), Storage(MTL::StorageModeShared), CpuCacheMode(MTL::CPUCacheModeDefaultCache)`
- L20 _public function_ `FMetalPooledBufferArgs(FMetalDevice* InDevice, uint32 InSize, EBufferUsageFlags InFlags, MTL::StorageMode InStorage, MTL::CPUCacheMode InCpuCacheMode = MTL::CPUCacheModeDefaultCache) : Device(InDevice) , Size(InSize) , Flags(InFlags) , Storage(InStorage) , CpuCacheMode(InCpuCacheMode)`
- L29 _public member_ `FMetalDevice* Device;`
- L30 _public member_ `uint32 Size;`
- L31 _public member_ `EBufferUsageFlags Flags;`
- L32 _public member_ `MTL::StorageMode Storage;`
- L33 _public member_ `MTL::CPUCacheMode CpuCacheMode;`

#### class `IMetalBufferAllocator`  
`class IMetalBufferAllocator`  
_L36-40_
- L39 _public prototype_ `virtual void ReleaseBuffer(FMetalBuffer* Buffer) = 0;`

#### class `FMetalSubBufferHeap`  
`class FMetalSubBufferHeap : public IMetalBufferAllocator`  
_L42-89_
- inherits: `IMetalBufferAllocator`
- L47 _public prototype_ `FMetalSubBufferHeap(FMetalDevice& MetalDevice, NS::UInteger Size, NS::UInteger Alignment, MTL::ResourceOptions, FCriticalSection& PoolMutex);`
- L48 _public prototype_ `~FMetalSubBufferHeap();`
- L50 _public prototype_ `NS::String* GetLabel() const;`
- L51 _public prototype_ `MTL::Device* GetDevice() const;`
- L52 _public prototype_ `MTL::StorageMode GetStorageMode() const;`
- L53 _public prototype_ `MTL::CPUCacheMode GetCpuCacheMode() const;`
- L54 _public prototype_ `NS::UInteger GetSize() const;`
- L55 _public prototype_ `NS::UInteger GetUsedSize() const;`
- L56 _public prototype_ `NS::UInteger MaxAvailableSize() const;`
- L57 _public prototype_ `int64 NumCurrentAllocations() const;`
- L58 _public prototype_ `bool CanAllocateSize(NS::UInteger Size) const;`
- L60 _public prototype_ `void SetLabel(const NS::String* label);`
- L62 _public prototype_ `FMetalBufferPtr NewBuffer(NS::UInteger length);`
- L63 _public prototype_ `MTL::PurgeableState SetPurgeableState(MTL::PurgeableState state);`
- L64 _public prototype_ `void FreeRange(NS::Range const& Range);`
- L66 _public prototype_ `virtual void ReleaseBuffer(FMetalBuffer* Buffer) override;`
- L68 _public prototype_ `void SetOwner(NS::Range const& Range, FMetalRHIBuffer* Owner, bool bIsSwap);`
- L80 _private member_ `FMetalDevice& Device;`
- L81 _private member_ `FCriticalSection& PoolMutex;`
- L82 _private member_ `int64 volatile OutstandingAllocs;`
- L83 _private member_ `NS::UInteger MinAlign;`
- L84 _private member_ `NS::UInteger UsedSize;`
- L85 _private member_ `MTL::Buffer* ParentBuffer;`
- L86 _private member_ `MTLHeapPtr ParentHeap;`
- L87 _private member_ `TArray<NS::Range> FreeRanges;`
- L88 _private member_ `TArray<Allocation> AllocRanges;`

#### struct `FMetalSubBufferHeap::Allocation`  
`struct Allocation`  
_L71-78_
- L73 _public function_ `Allocation() : Range(0,0)`
- L75 _public member_ `NS::Range Range;`
- L76 _public member_ `MTL::Buffer* Resource;`
- L77 _public member_ `FMetalRHIBuffer* Owner;`

#### class `FMetalSubBufferLinear`  
`class FMetalSubBufferLinear : public IMetalBufferAllocator`  
_L91-121_
- inherits: `IMetalBufferAllocator`
- L94 _public prototype_ `FMetalSubBufferLinear(FMetalDevice& MetalDevice, NS::UInteger Size, NS::UInteger Alignment, MTL::ResourceOptions, FCriticalSection& PoolMutex);`
- L95 _public prototype_ `~FMetalSubBufferLinear();`
- L97 _public prototype_ `NS::String* GetLabel() const;`
- L98 _public prototype_ `MTL::Device* GetDevice() const;`
- L99 _public prototype_ `MTL::StorageMode GetStorageMode() const;`
- L100 _public prototype_ `MTL::CPUCacheMode GetCpuCacheMode() const;`
- L101 _public prototype_ `NS::UInteger GetSize() const;`
- L102 _public prototype_ `NS::UInteger GetUsedSize() const;`
- L103 _public prototype_ `bool CanAllocateSize(NS::UInteger Size) const;`
- L105 _public prototype_ `void SetLabel(const NS::String* label);`
- L107 _public prototype_ `FMetalBufferPtr NewBuffer(NS::UInteger length);`
- L108 _public prototype_ `MTL::PurgeableState SetPurgeableState(MTL::PurgeableState state);`
- L109 _public prototype_ `void FreeRange(NS::Range const& Range);`
- L111 _public prototype_ `virtual void ReleaseBuffer(FMetalBuffer* Buffer) override;`
- L114 _private member_ `FMetalDevice& Device;`
- L115 _private member_ `FCriticalSection& PoolMutex;`
- L116 _private member_ `NS::UInteger MinAlign;`
- L117 _private member_ `NS::UInteger WriteHead;`
- L118 _private member_ `NS::UInteger UsedSize;`
- L119 _private member_ `NS::UInteger FreedSize;`
- L120 _private member_ `MTL::Buffer* ParentBuffer;`

#### class `FMetalSubBufferMagazine`  
`class FMetalSubBufferMagazine : public IMetalBufferAllocator`  
_L123-156_
- inherits: `IMetalBufferAllocator`
- L126 _public prototype_ `FMetalSubBufferMagazine(FMetalDevice& MetalDevice, NS::UInteger Size, NS::UInteger ChunkSize, MTL::ResourceOptions);`
- L127 _public prototype_ `~FMetalSubBufferMagazine();`
- L129 _public prototype_ `NS::String* GetLabel() const;`
- L130 _public prototype_ `MTL::Device* GetDevice() const;`
- L131 _public prototype_ `MTL::StorageMode GetStorageMode() const;`
- L132 _public prototype_ `MTL::CPUCacheMode GetCpuCacheMode() const;`
- L133 _public prototype_ `NS::UInteger GetSize() const;`
- L134 _public prototype_ `NS::UInteger GetUsedSize() const;`
- L135 _public prototype_ `NS::UInteger GetFreeSize() const;`
- L136 _public prototype_ `int64 NumCurrentAllocations() const;`
- L137 _public prototype_ `bool CanAllocateSize(NS::UInteger Size) const;`
- L139 _public prototype_ `void SetLabel(const NS::String* label);`
- L140 _public prototype_ `void FreeRange(NS::Range const& Range);`
- L142 _public prototype_ `virtual void ReleaseBuffer(FMetalBuffer* Buffer) override;`
- L144 _public prototype_ `FMetalBufferPtr NewBuffer();`
- L145 _public prototype_ `MTL::PurgeableState SetPurgeableState(MTL::PurgeableState state);`
- L148 _private member_ `FMetalDevice& Device;`
- L149 _private member_ `NS::UInteger MinAlign;`
- L150 _private member_ `NS::UInteger BlockSize;`
- L151 _private member_ `int64 volatile OutstandingAllocs;`
- L152 _private member_ `int64 volatile UsedSize;`
- L153 _private member_ `MTL::Buffer* ParentBuffer;`
- L154 _private member_ `MTLHeapPtr ParentHeap;`
- L155 _private member_ `TArray<int8> Blocks;`

#### struct `FMetalRingBufferRef`  
`struct FMetalRingBufferRef`  
_L158-178_
- L160 _public prototype_ `FMetalRingBufferRef(FMetalDevice& InDevice, FMetalBufferPtr Buf);`
- L161 _public prototype_ `~FMetalRingBufferRef();`
- L163 _public function_ `void SetLastRead(uint64 Read)`
- L165 _public function_ `FMetalBufferPtr GetBuffer()`
- L170 _public function_ `MTL::Buffer* GetMTLBuffer()`
- L175 _public member_ `FMetalDevice& Device;`
- L176 _public member_ `FMetalBufferPtr Buffer = nullptr;`
- L177 _public member_ `uint64 LastRead;`

#### class `FMetalSubBufferRing`  
`class FMetalSubBufferRing : public IMetalBufferAllocator`  
_L183-222_
- inherits: `IMetalBufferAllocator`
- L186 _public prototype_ `FMetalSubBufferRing(FMetalDevice& MetalDevice, NS::UInteger Size, NS::UInteger Alignment, MTL::ResourceOptions Options);`
- L187 _public prototype_ `~FMetalSubBufferRing();`
- L189 _public prototype_ `MTL::Device* GetDevice() const;`
- L190 _public prototype_ `MTL::StorageMode GetStorageMode() const;`
- L191 _public prototype_ `MTL::CPUCacheMode GetCpuCacheMode() const;`
- L192 _public prototype_ `NS::UInteger GetSize() const;`
- L194 _public prototype_ `FMetalBufferPtr NewBuffer(NS::UInteger Size, uint32 Alignment);`
- L195 _public function_ `virtual void ReleaseBuffer(FMetalBuffer* Buffer) override`
- L199 _public prototype_ `void Shrink();` — Tries to shrink the ring-buffer back toward its initial size, but not smaller.
- L202 _public prototype_ `void Commit(FMetalCommandBuffer* CmdBuffer);` — Commits a completion handler to the cmd-buffer to release the processed range
- L206 _private prototype_ `void Submit();` — Submits all outstanding writes to the GPU, coalescing the updates into a single contiguous range.
- L208 _private member_ `FMetalDevice& Device;`
- L210 _private member_ `NS::UInteger FrameSize[10];`
- L211 _private member_ `NS::UInteger LastFrameChange;`
- L212 _private member_ `NS::UInteger InitialSize;`
- L213 _private member_ `NS::UInteger MinAlign;`
- L214 _private member_ `NS::UInteger CommitHead;`
- L215 _private member_ `NS::UInteger SubmitHead;`
- L216 _private member_ `NS::UInteger WriteHead;`
- L217 _private member_ `NS::UInteger BufferSize;`
- L218 _private member_ `MTL::ResourceOptions Options;`
- L219 _private member_ `MTL::StorageMode Storage;`
- L220 _private member_ `TSharedPtr<FMetalRingBufferRef, ESPMode::ThreadSafe> RingBufferRef;`
- L221 _private member_ `TArray<NS::Range> AllocatedRanges;`

#### class `FMetalBufferPoolPolicyData`  
`class FMetalBufferPoolPolicyData`  
_L224-298_
- L254 _public typedef_ `typedef FMetalPooledBufferArgs CreationArguments;` — Buffers are created with a simple byte size
- L269 _public prototype_ `uint32 GetPoolBucketIndex(CreationArguments Args);` — Get the pool bucket index from the size @param Size the number of bytes for the resource @returns The bucket index.
- L275 _public prototype_ `uint32 GetPoolBucketSize(uint32 Bucket);` — Get the pool bucket size from the index @param Bucket the bucket index @returns The bucket size.
- L281 _public prototype_ `MTL::Buffer* CreateResource(FRHICommandListBase& RHICmdList, CreationArguments Args);` — Creates the resource @param Args The buffer size in bytes. @returns A suitably sized buffer or NULL on failure.
- L287 _public prototype_ `CreationArguments GetCreationArguments(MTL::Buffer* Resource);` — Gets the arguments used to create resource @param Resource The buffer to get data for. @returns The arguments used to create the buffer.
- L292 _public prototype_ `void FreeResource(MTL::Buffer* Resource);` — Frees the resource @param Resource The buffer to prepare for release from the pool permanently.
- L296 _private member_ `static uint32 BucketSizes[NumPoolBucketSizes];` — The bucket sizes
- L297 _private member_ `static TMap<MTL::Buffer*, CreationArguments> CreationArgumentMap;`

#### enum `FMetalBufferPoolPolicyData::BucketSizes`  
`enum BucketSizes`  
_L226-251_
- L229 _public enumerator_ `BucketSize256` — These sizes are required for ring-buffers and esp. Managed Memory which is a Mac-only feature
- L230 _public enumerator_ `BucketSize512`
- L231 _public enumerator_ `BucketSize1k`
- L232 _public enumerator_ `BucketSize2k`
- L233 _public enumerator_ `BucketSize4k`
- L234 _public enumerator_ `BucketSize8k`
- L235 _public enumerator_ `BucketSize16k`
- L236 _public enumerator_ `BucketSize32k`
- L237 _public enumerator_ `BucketSize64k`
- L238 _public enumerator_ `BucketSize128k`
- L239 _public enumerator_ `BucketSize256k`
- L240 _public enumerator_ `BucketSize512k`
- L241 _public enumerator_ `BucketSize1Mb`
- L242 _public enumerator_ `BucketSize2Mb`
- L243 _public enumerator_ `BucketSize4Mb`
- L245 _public enumerator_ `BucketSize8Mb` — These sizes are the ones typically used by buffer allocations
- L246 _public enumerator_ `BucketSize12Mb`
- L247 _public enumerator_ `BucketSize16Mb`
- L248 _public enumerator_ `BucketSize24Mb`
- L249 _public enumerator_ `BucketSize32Mb`
- L250 _public enumerator_ `NumBucketSizes`

#### enum `FMetalBufferPoolPolicyData::(anonymous)`  
``  
_L256-263_

#### class `FMetalBufferPool`  
`class FMetalBufferPool : public TResourcePool<MTL::Buffer*, FMetalBufferPoolPolicyData, FMetalBufferPoolPolicyData::CreationArguments>`  
_L301-306_
- inherits: `TResourcePool<MTL::Buffer*,FMetalBufferPoolPolicyData,FMetalBufferPoolPolicyData::CreationArguments>`
- desc: A pool for metal buffers with consistent usage, bucketed for efficiency.
- L305 _public prototype_ `virtual ~FMetalBufferPool();` — Destructor

#### class `FMetalTexturePool`  
`class FMetalTexturePool`  
_L308-393_
- L318 _public function_ `friend uint32 GetTypeHash(Descriptor const& Other)`
- L382 _public prototype_ `FMetalTexturePool(FCriticalSection& PoolMutex);`
- L383 _public prototype_ `~FMetalTexturePool();`
- L385 _public prototype_ `MTLTexturePtr CreateTexture(FMetalDevice& Device, MTL::TextureDescriptor* Desc);`
- L386 _public prototype_ `void ReleaseTexture(MTLTexturePtr Texture);`
- L388 _public prototype_ `void Drain(bool const bForce);`
- L391 _private member_ `FCriticalSection& PoolMutex;`
- L392 _private member_ `TMap<Descriptor, MTLTexturePtr> Pool;`

#### enum `FMetalTexturePool::(anonymous)`  
``  
_L311-314_

#### struct `FMetalTexturePool::Descriptor`  
`struct Descriptor`  
_L316-380_
- L333 _public function_ `bool operator<(Descriptor const& Other) const`
- L351 _public function_ `bool operator==(Descriptor const& Other) const`
- L369 _public member_ `NS::UInteger textureType;`
- L370 _public member_ `NS::UInteger pixelFormat;`
- L371 _public member_ `NS::UInteger width;`
- L372 _public member_ `NS::UInteger height;`
- L373 _public member_ `NS::UInteger depth;`
- L374 _public member_ `NS::UInteger mipmapLevelCount;`
- L375 _public member_ `NS::UInteger sampleCount;`
- L376 _public member_ `NS::UInteger arrayLength;`
- L377 _public member_ `NS::UInteger resourceOptions;`
- L378 _public member_ `NS::UInteger usage;`
- L379 _public member_ `NS::UInteger freedFrame;`

#### class `FMetalResourceHeap`  
`class FMetalResourceHeap : public IMetalBufferAllocator`  
_L397-543_
- inherits: `IMetalBufferAllocator`
- L460 _public prototype_ `FMetalResourceHeap(FMetalDevice& MetalDevice);`
- L461 _public prototype_ `~FMetalResourceHeap();`
- L463 _public prototype_ `void Init(FMetalCommandQueue& Queue);`
- L465 _public prototype_ `FMetalBufferPtr CreateBuffer(uint32 Size, uint32 Alignment, EBufferUsageFlags Flags, MTL::ResourceOptions Options, bool bForceUnique = false);`
- L466 _public prototype_ `MTLTexturePtr CreateTexture(MTL::TextureDescriptor* Desc, FMetalSurface* Surface);`
- L468 _public prototype_ `virtual void ReleaseBuffer(FMetalBuffer* Buffer) override;`
- L469 _public prototype_ `void ReleaseTexture(FMetalSurface* Surface, MTLTexturePtr Texture);`
- L472 _public prototype_ `FMetalAccelerationStructure* CreateAccelerationStructure(uint32 Size);`
- L473 _public prototype_ `void ReleaseAccelerationStructure(FMetalAccelerationStructure* AccelerationStructure);`
- L476 _public prototype_ `void Compact(bool const bForce);`
- L479 _private prototype_ `uint32 GetMagazineIndex(uint32 Size);`
- L480 _private prototype_ `uint32 GetHeapIndex(uint32 Size);`
- L481 _private prototype_ `TextureHeapSize TextureSizeToIndex(uint32 Size);`
- L483 _private prototype_ `MTLHeapPtr GetTextureHeap(MTL::TextureDescriptor* Desc, MTL::SizeAndAlign Size);`
- L486 _private member_ `static uint32 MagazineSizes[NumMagazineSizes];`
- L487 _private member_ `static uint32 HeapSizes[NumHeapSizes];`
- L488 _private member_ `static uint32 MagazineAllocSizes[NumMagazineSizes];`
- L489 _private member_ `static uint32 HeapAllocSizes[NumHeapSizes];`
- L490 _private member_ `static uint32 HeapTextureHeapSizes[NumTextureHeapSizes];`
- L492 _private member_ `FMetalDevice& Device;`
- L493 _private member_ `FCriticalSection Mutex;`
- L494 _private member_ `FMetalCommandQueue* Queue;`
- L497 _private member_ `TArray<FMetalSubBufferMagazine*> SmallBuffers[NumUsageTypes][NumAllocTypes][NumMagazineSizes];` — Small allocations (<= 4KB) are made from magazine allocators that use sub-ranges of a buffer
- L501 _private member_ `TArray<FMetalSubBufferHeap*> BufferHeaps[NumUsageTypes][NumAllocTypes][NumHeapSizes];` — There are two alignment categories for heaps - 16b for Vertes/Index data and 256b for constant data (macOS-only)
- L504 _private member_ `FMetalBufferPool Buffers[NumAllocTypes];` — Larger buffers (up-to 32MB) that are subject to bucketing & pooling rather than sub-allocation
- L506 _private member_ `FMetalBufferPool ManagedBuffers;`
- L507 _private member_ `TArray<FMetalSubBufferLinear*> ManagedSubHeaps;`
- L512 _private member_ `FMetalTexturePool TexturePool;` — We can reuse texture allocations as well, to minimize their performance impact
- L513 _private member_ `FMetalTexturePool TargetPool;`
- L515 _private member_ `TArray<MTLHeapPtr> TextureHeaps[EMetalHeapTextureUsageNum][NumTextureHeapSizes];`
- L526 _private typedef_ `using FMetalListIterator = TDoubleLinkedList<FMetalResourceHeap::MemoryBlock>::TIterator;`
- L528 _private member_ `TMap<MTL::ResourceOptions, TDoubleLinkedList<MemoryBlock>*> FreeLists;`
- L529 _private member_ `TMap<MTL::ResourceOptions, TDoubleLinkedList<MemoryBlock>*> UsedLists;`
- L531 _private member_ `FCriticalSection FreeListCS;`
- L534 _private member_ `FCriticalSection InUseResourcesCS;` — TODO: AAPL: Figure out how to guarantee index uniqueness without using a set (as iterators cant be hashed)
- L535 _private member_ `TArray<FMetalListIterator> InUseResources;`
- L536 _private member_ `TQueue<uint32> InUseResourcesFreeList;`
- L537 _private member_ `TMap<MTL::Resource*, uint32> AllocationHandlesLUT;`
- L539 _private prototype_ `FMetalListIterator MergeBlocks(TDoubleLinkedList<FMetalResourceHeap::MemoryBlock>& List, FMetalListIterator BlockItA, FMetalListIterator BlockItB);`
- L540 _private prototype_ `void FreeBlock(const uint32 ResourceAllocationHandle);`
- L541 _private prototype_ `FMetalListIterator FindOrAllocateBlock(uint32 Size, uint32 Alignment, MTL::ResourceOptions Options);`
- L542 _private prototype_ `FMetalListIterator SplitBlock(TDoubleLinkedList<FMetalResourceHeap::MemoryBlock>& List, FMetalListIterator BlockIt, const uint64 Offset, const uint32 Size);`

#### enum `FMetalResourceHeap::MagazineSize`  
`enum MagazineSize`  
_L399-412_
- L401 _public enumerator_ `Size16`
- L402 _public enumerator_ `Size32`
- L403 _public enumerator_ `Size64`
- L404 _public enumerator_ `Size128`
- L405 _public enumerator_ `Size256`
- L406 _public enumerator_ `Size512`
- L407 _public enumerator_ `Size1024`
- L408 _public enumerator_ `Size2048`
- L409 _public enumerator_ `Size4096`
- L410 _public enumerator_ `Size8192`
- L411 _public enumerator_ `NumMagazineSizes`

#### enum `FMetalResourceHeap::HeapSize`  
`enum HeapSize`  
_L414-419_
- L416 _public enumerator_ `Size1Mb`
- L417 _public enumerator_ `Size2Mb`
- L418 _public enumerator_ `NumHeapSizes`

#### enum `FMetalResourceHeap::TextureHeapSize`  
`enum TextureHeapSize`  
_L421-433_
- L423 _public enumerator_ `Size4Mb`
- L424 _public enumerator_ `Size8Mb`
- L425 _public enumerator_ `Size16Mb`
- L426 _public enumerator_ `Size32Mb`
- L427 _public enumerator_ `Size64Mb`
- L428 _public enumerator_ `Size128Mb`
- L429 _public enumerator_ `Size256Mb`
- L430 _public enumerator_ `NumTextureHeapSizes`
- L431 _public enumerator_ `MinTexturesPerHeap = 4`
- L432 _public enumerator_ `MaxTextureSize = Size64Mb`

#### enum `FMetalResourceHeap::AllocTypes`  
`enum AllocTypes`  
_L435-440_
- L437 _public enumerator_ `AllocShared`
- L438 _public enumerator_ `AllocPrivate`
- L439 _public enumerator_ `NumAllocTypes = 2`

#### enum `FMetalResourceHeap::EMetalHeapTextureUsage`  
`enum EMetalHeapTextureUsage`  
_L442-450_
- L445 _public enumerator_ `EMetalHeapTextureUsageResource = 0` — Regular texture resource
- L447 _public enumerator_ `EMetalHeapTextureUsageRenderTarget = 1` — Render target or UAV that can be aliased
- L449 _public enumerator_ `EMetalHeapTextureUsageNum = 2` — Number of texture usage types

#### enum `FMetalResourceHeap::UsageTypes`  
`enum UsageTypes`  
_L452-457_
- L454 _public enumerator_ `UsageStatic`
- L455 _public enumerator_ `UsageDynamic`
- L456 _public enumerator_ `NumUsageTypes = 2`

#### struct `FMetalResourceHeap::MemoryBlock`  
`struct MemoryBlock`  
_L517-524_
- L519 _public member_ `MTLHeapPtr Heap;`
- L520 _public member_ `uint64 Offset;`
- L521 _public member_ `uint64 Size;`
- L522 _public member_ `MTL::Resource* Resource;`
- L523 _public member_ `MTL::ResourceOptions Options;`

#### Free symbols / members of external scopes

- L14 _typedef_ `typedef TSharedPtr<FMetalBuffer, ESPMode::ThreadSafe> FMetalBufferPtr;`
- L257 _enumerator_ `NumResourceStorageModes = 4` (scope `FMetalBufferPoolPolicyData::__anon090c533c0103`)
- L258 _enumerator_ `NumSafeFrames = 1` (scope `FMetalBufferPoolPolicyData::__anon090c533c0103`) — NumResourceStorageModes = 4,   Corresponds to MTLStorageMode types: managed, shared, private, memoryless
- L259 _enumerator_ `NumPoolBucketSizes = NumBucketSizes` (scope `FMetalBufferPoolPolicyData::__anon090c533c0103`) — NumSafeFrames = 1,   Number of frames to leave buffers before reclaiming/reusing
- L260 _enumerator_ `NumPoolBuckets = NumPoolBucketSizes * NumResourceStorageModes` (scope `FMetalBufferPoolPolicyData::__anon090c533c0103`) — NumPoolBucketSizes = NumBucketSizes,   Number of pool bucket sizes
- L261 _enumerator_ `NumToDrainPerFrame = 65536` (scope `FMetalBufferPoolPolicyData::__anon090c533c0103`) — NumPoolBuckets = NumPoolBucketSizes * NumResourceStorageModes,   Number of pool bucket sizes - all entries must use consistent ResourceOptions, so the total number of pool buckets is the number of pool bucket sizes x the number of resource storage modes
- L262 _enumerator_ `CullAfterFramesNum = 30` (scope `FMetalBufferPoolPolicyData::__anon090c533c0103`) — NumToDrainPerFrame = 65536,   Max. number of resources to cull in a single frame
- L312 _enumerator_ `PurgeAfterNumFrames = 2` (scope `FMetalTexturePool::__anon090c533c0203`)
- L313 _enumerator_ `CullAfterNumFrames = 3` (scope `FMetalTexturePool::__anon090c533c0203`) — PurgeAfterNumFrames = 2,   Textures must be reused fairly rapidly but after this number of frames we reclaim the memory, even though the object persists
- L395 _typedef_ `typedef NS::SharedPtr<MTL::Heap> MTLHeapPtr;`

### `Source/Runtime/Apple/MetalRHI/Private/MetalCaptureManager.h` (Private)


#### class `FMetalCaptureManager`  
`class FMetalCaptureManager`  
_L9-46_
- L12 _public prototype_ `FMetalCaptureManager(MTL::Device* Device, FMetalCommandQueue& Queue);`
- L13 _public prototype_ `~FMetalCaptureManager();`
- L16 _public prototype_ `void PresentFrame(uint32 FrameNumber);` — Called by the MetalRHI code to trigger the provided capture scopes visible in Xcode.
- L20 _public prototype_ `void BeginCapture(void);` — Programmatic captures without an Xcode capture scope. Use them to instrument the code manually to debug issues.
- L21 _public prototype_ `void EndCapture(void);`
- L24 _private member_ `MTL::Device* Device;`
- L25 _private member_ `FMetalCommandQueue& Queue;`
- L26 _private member_ `bool bSupportsCaptureManager;`
- L45 _private member_ `TArray<FMetalCaptureScope> ActiveScopes;`

#### enum `FMetalCaptureManager::EMetalCaptureType`  
`enum EMetalCaptureType`  
_L29-35_
- L31 _public enumerator_ `EMetalCaptureTypeUnknown`
- L32 _public enumerator_ `EMetalCaptureTypeFrame` — (BeginFrame-EndFrame) * StepCount
- L33 _public enumerator_ `EMetalCaptureTypePresent` — (Present-Present) * StepCount
- L34 _public enumerator_ `EMetalCaptureTypeViewport` — (Present-Present) * Viewports * StepCount

#### struct `FMetalCaptureManager::FMetalCaptureScope`  
`struct FMetalCaptureScope`  
_L37-43_
- L39 _public member_ `EMetalCaptureType Type;`
- L40 _public member_ `uint32 StepCount;`
- L41 _public member_ `uint32 LastTrigger;`
- L42 _public member_ `MTL::CaptureScope* MTLScope;`

### `Source/Runtime/Apple/MetalRHI/Private/MetalCommandBuffer.h` (Private)


#### class `FMetalCommandBuffer`  
`class FMetalCommandBuffer`  
_L12-118_
- L15 _public function_ `FMetalCommandBuffer(MTL::CommandBuffer* InCommandBuffer, FMetalCommandQueue& Queue) : EventStream(Queue.GetProfilerQueue())`
- L22 _public function_ `~FMetalCommandBuffer()`
- L27 _public function_ `FORCEINLINE MTL::CommandBuffer*& GetMTLCmdBuffer()`
- L30 _public function_ `void BeginBreadcrumb(FMetalBreadcrumbInstance* Instance)`
- L39 _public function_ `void EndBreadcrumb(FMetalBreadcrumbInstance* Instance)`
- L49 _public function_ `void AddCounterSample(FMetalCounterSamplePtr CounterSample)`
- L67 _public function_ `void SetBeginWorkTimestamp(uint64_t* Timestamp)`
- L72 _public function_ `void SetEndWorkTimestamp(uint64_t* Timestamp)`
- L78 _public function_ `template <typename TEventType, typename... TArgs> TEventType& EmplaceProfilerEvent(TArgs&&... Args)`
- L92 _public function_ `void FlushProfilerEvents(UE::RHI::GPUProfiler::FEventStream& Destination, uint64 CPUTimestamp)`
- L102 _public member_ `TArray<FMetalRHIRenderQuery*> TimestampQueries;`
- L103 _public member_ `TArray<FMetalRHIRenderQuery*> OcclusionQueries;`
- L104 _public member_ `TArray<FMetalCounterSamplePtr> CounterSamples;`
- L106 _public member_ `UE::RHI::GPUProfiler::FEventStream EventStream;`
- L107 _public member_ `TArray<UE::RHI::GPUProfiler::FEvent::FBeginWork*, TInlineAllocator<8>> BeginEvents;`
- L110 _public member_ `TArray<FMetalBreadcrumbTrackerObject> BreadcrumbTrackerStream;`
- L113 _public member_ `uint64_t* BeginWorkTimestamp;`
- L114 _public member_ `uint64_t* EndWorkTimestamp;`
- L117 _private member_ `MTL::CommandBuffer* CommandBuffer;`

### `Source/Runtime/Apple/MetalRHI/Private/MetalCommandEncoder.h` (Private)


#### struct `FMetalCommandData`  
`struct FMetalCommandData`  
_L21-49_
- L39 _public member_ `Type CommandType;`
- L48 _public prototype_ `FString ToString() const;`

#### enum `FMetalCommandData::Type`  
`enum class Type`  
_L23-33_
- L25 _public enumerator_ `DrawPrimitive`
- L26 _public enumerator_ `DrawPrimitiveIndexed`
- L27 _public enumerator_ `DrawPrimitivePatch`
- L28 _public enumerator_ `DrawPrimitiveIndirect`
- L29 _public enumerator_ `DrawPrimitiveIndexedIndirect`
- L30 _public enumerator_ `Dispatch`
- L31 _public enumerator_ `DispatchIndirect`
- L32 _public enumerator_ `Num`

#### struct `FMetalCommandData::DispatchIndirectArgs`  
`struct DispatchIndirectArgs`  
_L34-38_
- L36 _public member_ `MTL::Buffer* ArgumentBuffer;`
- L37 _public member_ `NS::UInteger ArgumentOffset;`

#### union `FMetalCommandData::(anonymous)`  
``  
_L41-47_

#### struct `FMetalCommandDebug`  
`struct FMetalCommandDebug`  
_L51-59_
- L53 _public member_ `uint32 CmdBufIndex;`
- L54 _public member_ `uint32 Encoder;`
- L55 _public member_ `uint32 Index;`
- L56 _public member_ `FMetalGraphicsPipelineState* PSO;`
- L57 _public member_ `FMetalComputeShader* ComputeShader;`
- L58 _public member_ `FMetalCommandData Data;`

#### enum `EMetalFenceWaitStage::Type`  
`enum Type`  
_L63-68_
- L65 _public enumerator_ `None = 0`
- L66 _public enumerator_ `BeforeVertex = 1 << 0` — Wait fence before VS/CS is executed
- L67 _public enumerator_ `BeforeFragment = 1 << 1` — Wait fence before PS is executed

#### struct `FMetalBarrierScope`  
`struct FMetalBarrierScope`  
_L72-102_
- desc: An emulator of MTLBarrierScope that is supported since IOS 16.0
- L74 _public member_ `EMetalFenceWaitStage::Type BuffersWaitStage;`
- L75 _public member_ `EMetalFenceWaitStage::Type RenderTargetsWaitStage;`
- L76 _public member_ `EMetalFenceWaitStage::Type TexturesWaitStage;`
- L78 _public function_ `FMetalBarrierScope()`
- L83 _public function_ `void Reset()`
- L90 _public function_ `EMetalFenceWaitStage::Type GetFenceWaitStage()`

#### struct `FMetalCommandEncoderFence`  
`struct FMetalCommandEncoderFence`  
_L104-137_
- L107 _public member_ `TSet<MTL::Resource*> FenceResources;` — Resources produced in the prologue pass
- L109 _public member_ `TRefCountPtr<FMetalFence> Fence;` — Fence written by the prologue pass
- L111 _public member_ `FMetalBarrierScope BarrierScope;` — The barrier state for the current pass
- L113 _public prototype_ `FMetalCommandEncoderFence() = default;`
- L115 _public function_ `FMetalCommandEncoderFence(FMetalCommandEncoderFence&& In)`
- L121 _public function_ `FMetalCommandEncoderFence& operator=(FMetalCommandEncoderFence&& lhs)`
- L131 _public function_ `void Reset()`

#### class `FMetalCommandEncoder`  
`class FMetalCommandEncoder`  
_L146-634_
- desc: FMetalCommandEncoder: Wraps the details of switching between different command encoders on the command-buffer, allowing for restoration of the render encoder if needed. UnrealEngine expects the API to serialise commands in-order, but Metal expects applications to work with command-buffers directly so we need to implement the RHI semantics by switching between encoder types. This class hides the ugly details. Eventually it might be possible to move some of the operations into pre- & post- command-buffers so that we avoid encoder switches but that will take changes to the RHI and high-level code too, so it won't happen soon.
- L152 _public prototype_ `FMetalCommandEncoder(FMetalDevice& Device, FMetalCommandQueue& CommandQueue);` — Default constructor
- L155 _public prototype_ `void Release(void);` — Release Function
- L158 _public prototype_ `void Reset(void);` — Reset cached state for reuse
- L161 _public prototype_ `void ResetLive(void);` — Reset cached state for reuse while in rendering
- L169 _public prototype_ `void StartCommandBuffer(void);` — Start encoding to CommandBuffer. It is an error to call this with any outstanding command encoders or current command buffer. Instead call EndEncoding & CommitCommandBuffer before calling this.
- L174 _public prototype_ `void EndCommandBuffer(FMetalRHICommandContext* Context);` — Will deprecate in 5.6, splits the command buffer into chunks, required for profiling until we switch to encoder counter buffers
- L179 _public function_ `FMetalCommandBuffer* GetCommandBuffer()` — @returns the current command buffer
- L182 _public function_ `uint32 GetCommandBufferIndex() const` — @returns the monotonically incremented command buffer index
- L187 _public function_ `inline bool IsParallelRenderCommandEncoderActive(void) const` — @returns True if and only if there is an active parallel render command encoder, otherwise false.
- L193 _public function_ `inline bool IsRenderCommandEncoderActive(void) const` — @returns True if and only if there is an active render command encoder, otherwise false.
- L199 _public function_ `inline bool IsComputeCommandEncoderActive(void) const` — @returns True if and only if there is an active compute command encoder, otherwise false.
- L205 _public function_ `inline bool IsBlitCommandEncoderActive(void) const` — @returns True if and only if there is an active blit command encoder, otherwise false.
- L211 _public function_ `inline bool IsAnyCommandEncoderActive(void) const` — @returns True if any encoder is active, otherwise false.
- L222 _public function_ `inline bool IsParallelEncoding()`
- L229 _public prototype_ `bool IsAccelerationStructureCommandEncoderActive(void) const;` — @returns True if and only if there is an active acceleration structure command encoder, otherwise false.
- L233 _public prototype_ `bool IsRenderPassDescriptorValid(void) const;` — @returns True if and only if there is valid render pass descriptor set on the encoder, otherwise false.
- L236 _public prototype_ `const MTL::RenderPassDescriptor* GetRenderPassDescriptor(void) const;` — @returns The current render pass descriptor.
- L239 _public prototype_ `MTL::RenderCommandEncoder* GetRenderCommandEncoder(void);` — @returns The active render command encoder or nullptr if there isn't one.
- L242 _public prototype_ `MTL::ComputeCommandEncoder* GetComputeCommandEncoder(void);` — @returns The active compute command encoder or nullptr if there isn't one.
- L245 _public prototype_ `MTL::BlitCommandEncoder* GetBlitCommandEncoder(void);` — @returns The active blit command encoder or nullptr if there isn't one.
- L249 _public prototype_ `MTL::AccelerationStructureCommandEncoder* GetAccelerationStructureCommandEncoder(void);` — @returns The active acceleration structure command encoder or nullptr if there isn't one.
- L253 _public prototype_ `TRefCountPtr<FMetalFence> const& GetEncoderFence(void) const;` — @returns The MTLFence for the current encoder or nullptr if there isn't one.
- L256 _public function_ `uint32 NumEncodedPasses(void) const` — @returns The number of encoded passes in the command buffer.
- L263 _public prototype_ `MTLParallelRenderCommandEncoderPtr BeginParallelRenderCommandEncoding(FMetalCounterSampler* Sampler);` — Begins encoding for parallel rendering commands into the current command buffer. No other encoder may be active
- L268 _public prototype_ `void BeginRenderCommandEncoding(FMetalCounterSampler* Sampler);` — Begins encoding rendering commands into the current command buffer. No other encoder may be active
- L273 _public prototype_ `void BeginRenderCommandEncoding(MTL::RenderPassDescriptor* RenderPassDesc, MTLParallelRenderCommandEncoderPtr ParallelEncoder);` — Begins encoding rendering commands into the parallel render encoder (no command buffer required)
- L276 _public prototype_ `void BeginComputeCommandEncoding(MTL::DispatchType Type = MTL::DispatchTypeSerial, FMetalCounterSampler* Sampler = nullptr);` — Begins encoding compute commands into the current command buffer. No other encoder may be active.
- L280 _public prototype_ `void BeginAccelerationStructureCommandEncoding(void);` — Begins encoding acceleration structure commands into the current command buffer. No other encoder may be active.
- L284 _public prototype_ `void BeginBlitCommandEncoding(FMetalCounterSampler* Sampler);` — Begins encoding blit commands into the current command buffer. No other encoder may be active.
- L287 _public prototype_ `TRefCountPtr<FMetalFence> EndEncoding();` — Declare that all command generation from this encoder is complete, and detach from the MTLCommandBuffer if there is an encoder active or does nothing if there isn't.
- L290 _public prototype_ `void UpdateFence(FMetalFence* Fence);` — Update the event to capture all GPU work so far enqueued by this encoder.
- L293 _public prototype_ `void WaitForFence(FMetalFence* Fence);` — Prevent further GPU work until the event is reached.
- L296 _public prototype_ `void SignalEvent(MTLEventPtr Event, uint32_t SignalCount);` — Update the event to capture all GPU work so far enqueued by this encoder.
- L299 _public prototype_ `void WaitForEvent(MTLEventPtr Event, uint32_t SignalCount);` — Prevent further GPU work until the event is reached.
- L302 _public prototype_ `void SignalSharedEvent(MTLSharedEventPtr Event, uint32_t SignalCount);` — Update the event to capture all GPU work so far enqueued by this encoder.
- L305 _public prototype_ `void WaitForSharedEvent(MTLSharedEventPtr Event, uint32_t SignalCount);` — Prevent further GPU work until the event is reached.
- L313 _public prototype_ `void InsertDebugSignpost(NS::String* String);` — Inserts a debug string into the command buffer.  This does not change any API behavior, but can be useful when debugging. @param string The name of the signpost.
- L319 _public prototype_ `void PushDebugGroup(NS::String* String);` — Push a new named string onto a stack of string labels. @param string The name of the debug group.
- L322 _public prototype_ `void PopDebugGroup(void);` — Pop the latest named string off of the stack.
- L330 _public prototype_ `void SetRenderPassDescriptor(MTL::RenderPassDescriptor* RenderPass);` — Set the render pass descriptor - no encoder may be active when this function is called. @param RenderPass The render pass descriptor to set. May be nullptr.
- L338 _public prototype_ `void SetRenderPassStoreActions(MTL::StoreAction const* const ColorStore, MTL::StoreAction const DepthStore, MTL::StoreAction const StencilStore);` — Set the render pass store actions, call after SetRenderPassDescriptor but before EndEncoding. @param ColorStore The store actions for color targets. @param DepthStore The store actions for the depth buffer - use MTL::StoreActionUnknown if no depth-buffer bound. @param StencilStore The store actions for the stencil buffer - use MTL::StoreActionUnknown if no stencil-buffer bound.
- L344 _public prototype_ `void SetRenderPipelineState(FMetalShaderPipeline* const PipelineState);` — Sets the current render pipeline state object. @param PipelineState The pipeline state to set. Must not be null.
- L351 _public prototype_ `void SetViewport(MTL::Viewport const Viewport[], uint32 NumActive);` — Set the viewport, which is used to transform vertexes from normalized device coordinates to window coordinates.  Fragments that lie outside of the viewport are clipped, and optionally clamped for fragments outside of znear/zfar. @param Viewport The array of viewport dimensions to use. @param NumActive The number of active viewport dimensions to use.
- L357 _public prototype_ `void SetFrontFacingWinding(MTL::Winding const FrontFacingWinding);` — The winding order of front-facing primitives. @param FrontFacingWinding The front face winding.
- L363 _public prototype_ `void SetCullMode(MTL::CullMode const CullMode);` — Controls if primitives are culled when front facing, back facing, or not culled at all. @param CullMode The cull mode.
- L371 _public prototype_ `void SetDepthBias(float const DepthBias, float const SlopeScale, float const Clamp);` — Depth Bias. @param DepthBias The depth-bias value. @param SlopeScale The slope-scale to apply. @param Clamp The value to clamp to.
- L378 _public prototype_ `void SetScissorRect(MTL::ScissorRect const Rect[], uint32 NumActive);` — Specifies a rectangle for a fragment scissor test.  All fragments outside of this rectangle are discarded. @param Rect The array of scissor rect dimensions. @param NumActive The number of active scissor rect dimensions.
- L384 _public prototype_ `void SetTriangleFillMode(MTL::TriangleFillMode const FillMode);` — Set how to rasterize triangle and triangle strip primitives. @param FillMode The fill mode.
- L390 _public prototype_ `void SetDepthClipMode(MTL::DepthClipMode DepthClipMode);` — Set wether to clip or clamp triangles based on depth. @param FillMode The fill mode.
- L399 _public prototype_ `void SetBlendColor(float const Red, float const Green, float const Blue, float const Alpha);` — Set the constant blend color used across all blending on all render targets @param Red The value for the red channel in 0-1. @param Green The value for the green channel in 0-1. @param Blue The value for the blue channel in 0-1. @param Alpha The value for the alpha channel in 0-1.
- L405 _public prototype_ `void SetDepthStencilState(MTL::DepthStencilState* DepthStencilState);` — Set the DepthStencil state object. @param DepthStencilState The depth-stencil state, must not be null.
- L411 _public prototype_ `void SetStencilReferenceValue(uint32 const ReferenceValue);` — Set the stencil reference value for both the back and front stencil buffers. @param ReferenceValue The stencil ref value to use.
- L418 _public prototype_ `void SetVisibilityResultMode(MTL::VisibilityResultMode const Mode, NS::UInteger const Offset);` — Monitor if samples pass the depth and stencil tests. @param Mode Controls if the counter is disabled or moniters passing samples. @param Offset The offset relative to the occlusion query buffer provided when the command encoder was created.  offset must be a multiple of 8.
- L428 _public prototype_ `void SetShaderAccelerationStructure(MTL::FunctionType const FunctionType, MTLAccelerationStructurePtr AccelerationStructure, NS::UInteger const Index);` — Set a global acceleration structure for the specified shader frequency at the given bind point index. @param FunctionType The shader function to modify. @param AccelerationStructure The acceleration structure to bind or nullptr to clear. @param Index The index to modify.
- L442 _public prototype_ `void SetShaderBuffer(MTL::FunctionType const FunctionType, FMetalBufferPtr Buffer, NS::UInteger const Offset, NS::UInteger const Length, NS::UInteger const Index, MTL::ResourceUsage const Usage, EPixelFormat const Format = PF_Unknown, NS::UInteger const ElementRowPitch = 0, TArray<TTuple<MTL::Resource*, MTL::ResourceUsage>> ReferencedResources = {});` — Set a global buffer for the specified shader frequency at the given bind point index. @param FunctionType The shader function to modify. @param Buffer The buffer to bind or nullptr to clear. @param Offset The offset in the buffer or 0 when Buffer is nullptr. @param Length The data length - caller is responsible for accounting for non-zero Offset. @param Index The index to modify. @param Usage The resource usage mask. @param Format The Pixel format to reinterpret the resource as. @param ReferencedResources Resources indirectly used by the bound buffer.
- L452 _public prototype_ `void SetShaderData(MTL::FunctionType const FunctionType, FMetalBufferData* Data, NS::UInteger const Offset, NS::UInteger const Index, EPixelFormat const Format = PF_Unknown, NS::UInteger const ElementRowPitch = 0);` — Set an FMetalBufferData to the specified shader frequency at the given bind point index. @param FunctionType The shader function to modify. @param Data The data to bind or nullptr to clear. @param Offset The offset in the buffer or 0 when Buffer is nullptr. @param Index The index to modify. @param Format The pixel format to reinterpret the resource as.
- L461 _public prototype_ `void SetShaderBytes(MTL::FunctionType const FunctionType, uint8 const* Bytes, NS::UInteger const Length, NS::UInteger const Index);` — Set bytes to the specified shader frequency at the given bind point index. @param FunctionType The shader function to modify. @param Bytes The data to bind or nullptr to clear. @param Length The length of the buffer or 0 when Bytes is nullptr. @param Index The index to modify.
- L470 _public prototype_ `void SetShaderTexture(MTL::FunctionType const FunctionType, MTL::Texture* Texture, NS::UInteger const Index, MTL::ResourceUsage const Usage);` — Set a global texture for the specified shader frequency at the given bind point index. @param FunctionType The shader function to modify. @param Texture The texture to bind or nullptr to clear. @param Index The index to modify. @param Usage The resource usage mask.
- L478 _public prototype_ `void SetShaderSamplerState(MTL::FunctionType const FunctionType, MTL::SamplerState* Sampler, NS::UInteger const Index);` — Set a global sampler for the specified shader frequency at the given bind point index. @param FunctionType The shader function to modify. @param Sampler The sampler state to bind or nullptr to clear. @param Index The index to modify.
- L485 _public prototype_ `void SetShaderSideTable(MTL::FunctionType const FunctionType, NS::UInteger const Index);` — Set the shader side-table data for FunctionType at Index. @param FunctionType The shader function to modify. @param Index The index to bind data to.
- L492 _public prototype_ `void UseIndirectArgumentResource(MTL::Texture* Texture, MTL::ResourceUsage const Usage);` — Inform the driver that an indirect argument resource will be used and what the usage mode will be. @param Texture The texture that will be used as an indirect argument. @param Usage The usage mode for the texture.
- L499 _public prototype_ `void UseIndirectArgumentResource(FMetalBufferPtr Buffer, MTL::ResourceUsage const Usage);` — Inform the driver that an indirect argument resource will be used and what the usage mode will be. @param Buffer The buffer that will be used as an indirect argument. @param Usage The usage mode for the texture.
- L505 _public prototype_ `void TransitionResources(MTL::Resource* Resource);` — Transition resource so that we can barrier fragment->vertex stages. @param Resource The resource we are going to make readable having been written.
- L513 _public prototype_ `void SetComputePipelineState(FMetalShaderPipelinePtr State);` — Set the compute pipeline state that will be used. @param State The state to set - must not be nullptr.
- L515 _public prototype_ `void SetComputePipelineState(MTL::ComputePipelineState* State);`
- L522 _public prototype_ `FMetalSubBufferRing& GetRingBuffer(void);` — Get the internal ring-buffer used for temporary allocations. @returns The temporary allocation buffer for this command-encoder.
- L535 _private prototype_ `void SetShaderBufferOffset(MTL::FunctionType const FunctionType, NS::UInteger const Offset, NS::UInteger const Length, NS::UInteger const Index);` — Set the offset for the buffer bound on the specified shader frequency at the given bind point index. @param FunctionType The shader function to modify. @param Offset The offset in the buffer or 0 when Buffer is nullptr. @param Length The data length - caller is responsible for accounting for non-zero Offset. @param Index The index to modify.
- L537 _private prototype_ `void SetShaderBufferInternal(MTL::FunctionType Function, uint32 Index);`
- L539 _private prototype_ `void FenceResource(MTL::Texture* Resource, const MTL::FunctionType Function, bool bIsRenderTarget = false);`
- L540 _private prototype_ `void FenceResource(MTL::Buffer* Resource, const MTL::FunctionType Function);`
- L543 _public prototype_ `void UseResource(MTL::Resource* Resource, MTL::ResourceUsage const Usage);`
- L544 _public prototype_ `void UseResources(TArray<MTL::Resource*> const& Resources, MTL::ResourceUsage const Usage, MTL::RenderStages RenderStages = 0);`
- L545 _public prototype_ `void UseHeaps(TArray<MTL::Heap*> const& Heaps, const MTL::FunctionType Function);`
- L598 _private member_ `FMetalDevice& Device;`
- L599 _private member_ `FMetalCommandQueue& CommandQueue;`
- L601 _private member_ `FMetalBufferBindings ShaderBuffers[int(MTL::FunctionTypeObject)+1];`
- L603 _private member_ `MTL::StoreAction ColorStoreActions[MaxSimultaneousRenderTargets];`
- L604 _private member_ `MTL::StoreAction DepthStoreAction;`
- L605 _private member_ `MTL::StoreAction StencilStoreAction;`
- L607 _private member_ `FMetalSubBufferRing RingBuffer;`
- L609 _private member_ `MTL::RenderPassDescriptor* RenderPassDesc = nullptr;`
- L611 _private member_ `FMetalCommandBuffer* CommandBuffer = nullptr;`
- L613 _private member_ `MTLParallelRenderCommandEncoderPtr ParallelRenderCommandEncoder;`
- L614 _private member_ `MTLRenderCommandEncoderPtr RenderCommandEncoder;`
- L615 _private member_ `MTLComputeCommandEncoderPtr ComputeCommandEncoder;`
- L616 _private member_ `MTLBlitCommandEncoderPtr BlitCommandEncoder;`
- L618 _private member_ `MTLAccelerationStructureCommandEncoderPtr AccelerationStructureCommandEncoder;`
- L621 _private member_ `TRefCountPtr<FMetalFence> EncoderFence;`
- L623 _private member_ `TArray<NS::String*> DebugGroups;`
- L625 _private member_ `TSet<FMetalBufferPtr> ActiveBuffers;`
- L627 _private member_ `TMap<MTL::Resource*, MTL::ResourceUsage> ResourceUsage;`
- L629 _private member_ `TSet<MTL::Resource*> TransitionedResources;`
- L630 _private member_ `FMetalCommandEncoderFence CommandEncoderFence;`
- L631 _private member_ `uint32 EncoderNum;`
- L632 _private member_ `uint32 CmdBufIndex;`
- L633 _private member_ `bool bIsParallelEncoding = false;`

#### struct `FMetalCommandEncoder::FMetalBufferBindings`  
`struct FMetalBufferBindings`  
_L550-595_
- desc: A structure of arrays for the current buffer binding settings.
- L553 _public member_ `FMetalBufferData* SideTable;` — Side-table wrapper object to allow us to use Set*Bytes.
- L555 _public member_ `FMetalBufferPtr Buffers[ML_MaxBuffers];` — The bound buffers or nullptr.
- L556 _public member_ `TArray<TTuple<MTL::Resource*, MTL::ResourceUsage>> ReferencedResources[ML_MaxBuffers];`
- L559 _public member_ `MTLAccelerationStructurePtr AccelerationStructure[ML_MaxBuffers];` — The bound acceleration structure or nullptr.
- L562 _public member_ `FMetalBufferData* Bytes[ML_MaxBuffers];` — The bound buffers or nullptr.
- L564 _public member_ `NS::UInteger Offsets[ML_MaxBuffers];` — The bound buffer offsets or 0.
- L566 _public member_ `MTL::ResourceUsage Usage[ML_MaxBuffers];` — The usage mask for the bound resource or 0
- L578 _public member_ `FSizeConstants Lengths[ML_MaxBuffers + ML_MaxTextures];`
- L580 _public member_ `uint32 Bound;` — A bitmask for which buffers were bound by the application where a bit value of 1 is bound and 0 is unbound.
- L583 _public function_ `void SetBufferMetaData(NS::UInteger Index, NS::UInteger Length, NS::UInteger Format, NS::UInteger ElementRowPitch)`
- L589 _public function_ `void SetTextureSwizzle(NS::UInteger Index, uint8 (&Swizzle)[4])`

#### struct `FMetalCommandEncoder::FMetalBufferBindings::FSizeConstants`  
`struct FSizeConstants`  
_L568-577_
- desc: The bound buffer constants
- L575 _public member_ `uint32 Format;`
- L576 _public member_ `uint32 ElementRowPitch;`

#### union `FMetalCommandEncoder::FMetalBufferBindings::FSizeConstants::(anonymous)`  
``  
_L571-574_

#### Free symbols / members of external scopes

- L17 _typedef_ `typedef TSharedPtr<FMetalShaderPipeline, ESPMode::ThreadSafe> FMetalShaderPipelinePtr;`
- L42 _member_ `MTL::DrawPrimitivesIndirectArguments Draw;` (scope `FMetalCommandData::__anon64fa8ce1010a`)
- L43 _member_ `MTL::DrawIndexedPrimitivesIndirectArguments DrawIndexed;` (scope `FMetalCommandData::__anon64fa8ce1010a`)
- L44 _member_ `MTL::DrawPatchIndirectArguments DrawPatch;` (scope `FMetalCommandData::__anon64fa8ce1010a`)
- L45 _member_ `MTL::DispatchThreadgroupsIndirectArguments Dispatch;` (scope `FMetalCommandData::__anon64fa8ce1010a`)
- L46 _member_ `DispatchIndirectArgs DispatchIndirect;` (scope `FMetalCommandData::__anon64fa8ce1010a`)
- L61 _namespace_ `namespace EMetalFenceWaitStage`
- L572 _member_ `uint32 Length;` (scope `FMetalCommandEncoder::FMetalBufferBindings::FSizeConstants::__anon64fa8ce1020a`)
- L573 _member_ `uint32 Swizzle;` (scope `FMetalCommandEncoder::FMetalBufferBindings::FSizeConstants::__anon64fa8ce1020a`)

### `Source/Runtime/Apple/MetalRHI/Private/MetalCommandQueue.h` (Private)


#### class `FMetalTiming`  
`class FMetalTiming`  
_L15-27_
- L18 _public member_ `FMetalCommandQueue& Queue;`
- L21 _public member_ `uint64 GPUFrequency = 0, GPUTimestamp = 0;` — Timer calibration data
- L21 _public member_ `uint64 GPUFrequency = 0, GPUTimestamp = 0;` — Timer calibration data
- L22 _public member_ `uint64 CPUFrequency = 0, CPUTimestamp = 0;`
- L22 _public member_ `uint64 CPUFrequency = 0, CPUTimestamp = 0;`
- L24 _public member_ `UE::RHI::GPUProfiler::FEventStream EventStream;`
- L26 _public prototype_ `FMetalTiming(FMetalCommandQueue& Queue);`

#### class `FMetalCommandQueue`  
`class FMetalCommandQueue`  
_L32-137_
- desc: FMetalCommandQueue:
- L42 _public prototype_ `FMetalCommandQueue(FMetalDevice& Device, uint32 const MaxNumCommandBuffers = 0);` — Constructor @param Device The Metal device to create on. @param MaxNumCommandBuffers The maximum number of incomplete command-buffers, defaults to 0 which implies the system default.
- L45 _public prototype_ `~FMetalCommandQueue(void);` — Destructor
- L54 _public prototype_ `FMetalCommandBuffer* CreateCommandBuffer(void);` — Start encoding to CommandBuffer. It is an error to call this with any outstanding command encoders or current command buffer. Instead call EndEncoding & CommitCommandBuffer before calling this. @param CommandBuffer The new command buffer to begin encoding to.
- L60 _public prototype_ `void CommitCommandBuffer(FMetalCommandBuffer* CommandBuffer);` — Commit the supplied command buffer immediately. @param CommandBuffer The command buffer to commit, must not be null
- L63 _public prototype_ `FMetalFence* CreateFence(NS::String* Label) const;` — @returns Creates a new MTLFence or nullptr if this is unsupported
- L68 _public prototype_ `FMetalDevice& GetDevice(void);` — @returns The command queue's native device.
- L71 _public function_ `MTL::CommandQueue* GetQueue(void)` — @returns The command queue's native device.
- L74 _public prototype_ `static MTL::ResourceOptions GetCompatibleResourceOptions(MTL::ResourceOptions Options);` — Converts a Metal v1.1+ resource option to something valid on the current version.
- L81 _public function_ `static inline bool SupportsSeparateMSAAAndResolveTarget()` — @param InFeature A specific Metal feature to check for. @returns True if RHISupportsSeparateMSAAAndResolveTextures will be true. Currently Mac only.
- L84 _public function_ `static inline bool IsUMASystem()` — @returns True on UMA system; false otherwise.
- L89 _public prototype_ `void InsertDebugCaptureBoundary(void);` — Inserts a boundary that marks the end of a frame for the debug capture tool.
- L102 _public member_ `} PendingSubmission, PendingInterrupt;`
- L102 _public member_ `} PendingSubmission, PendingInterrupt;`
- L104 _public member_ `FMetalPayload* PayloadToSubmit = nullptr;`
- L106 _public typedef_ `using FPayloadArray = TArray<FMetalPayload*>;`
- L109 _public prototype_ `uint64 FinalizePayload(bool bRequiresSignal, FPayloadArray& PayloadsToHandDown);` — Batches the current payload's command lists, returning the latest fence value signaled for this queue.
- L111 _public function_ `FMetalSignalEvent& GetSignalEvent()`
- L116 _public member_ `TArray<FMetalRHIRenderQuery*> TimestampQueries;`
- L117 _public member_ `TArray<FMetalRHIRenderQuery*> OcclusionQueries;`
- L118 _public member_ `TArray<FMetalCounterSamplePtr> CounterSamples;`
- L120 _public prototype_ `UE::RHI::GPUProfiler::FQueue GetProfilerQueue() const;`
- L121 _public member_ `FMetalTiming* Timing = nullptr;`
- L127 _public prototype_ `static void HandleMetalCommandBufferFailure(MTL::CommandBuffer* CompletedBuffer);` — Command buffer failure reporting function. @param CompletedBuffer The buffer to check for failure.
- L131 _private member_ `FMetalDevice& Device;`
- L132 _private member_ `MTL::CommandQueue* CommandQueue;`
- L133 _private member_ `int32 RuntimeDebuggingLevel;`
- L134 _private member_ `static NS::UInteger PermittedOptions;`
- L136 _private member_ `FMetalSignalEvent SignalEvent;`

#### struct `FMetalCommandQueue::(anonymous)`  
`struct : public TQueue<FMetalPayload*, EQueueMode::Mpsc>`  
_L91-102_
- inherits: `TQueue<FMetalPayload*,EQueueMode::Mpsc>`

#### Free symbols / members of external scopes

- L93 _function_ `FMetalPayload* Peek()` (scope `FMetalCommandQueue::__anon4b37d5a60108`)

### `Source/Runtime/Apple/MetalRHI/Private/MetalCounterSampler.h` (Private)


#### enum `EMetalCounterSampleType`  
`enum class EMetalCounterSampleType`  
_L8-16_
- L10 _public enumerator_ `RenderStage = 0`
- L11 _public enumerator_ `ComputeStage`
- L12 _public enumerator_ `BlitStage`
- L13 _public enumerator_ `DrawBoundary`
- L14 _public enumerator_ `DispatchBoundary`
- L15 _public enumerator_ `BlitBoundary`

#### struct `FMetalCounterSample`  
`struct FMetalCounterSample`  
_L19-60_
- L21 _public function_ `FMetalCounterSample(EMetalCounterSampleType Type, MTL::CounterSampleBuffer* Buffer, uint32_t InOffset) : SampleType(Type) , Offset(InOffset) , SampleBuffer(Buffer)`
- L27 _public function_ `bool IsStageType()`
- L32 _public prototype_ `void ResolveStageCounters(uint64_t& InStartTime, uint64_t& InEndTime);`
- L33 _public prototype_ `void ResolveBoundaryCounter(uint64_t& Time);`
- L35 _public function_ `void* operator new(size_t Size)`
- L48 _public function_ `void operator delete(void* Pointer)`
- L53 _public member_ `static TLockFreePointerListUnordered<void, PLATFORM_CACHE_LINE_SIZE> MemoryPool;`
- L55 _public member_ `EMetalCounterSampleType SampleType;`
- L56 _public member_ `uint32_t Offset = 0;`
- L57 _public member_ `MTL::CounterSampleBuffer* SampleBuffer;`
- L58 _public member_ `bool bResolved = false;`
- L59 _public member_ `uint64_t StartTime, EndTime;`
- L59 _public member_ `uint64_t StartTime, EndTime;`

#### class `FMetalCounterSampler`  
`class FMetalCounterSampler`  
_L64-87_
- L67 _public prototype_ `FMetalCounterSampler(FMetalDevice* InDevice, uint32_t SampleCount);`
- L68 _public prototype_ `~FMetalCounterSampler();`
- L70 _public prototype_ `FMetalCounterSamplePtr SetupStageCounters(MTL::ComputePassDescriptor* ComputePassDesc);`
- L71 _public prototype_ `FMetalCounterSamplePtr SetupStageCounters(MTL::BlitPassDescriptor* BlitPassDesc);`
- L72 _public prototype_ `FMetalCounterSamplePtr SetupStageCounters(MTL::RenderPassDescriptor* InRenderPassDesc);`
- L73 _public prototype_ `FMetalCounterSamplePtr SetupBoundaryCounters(MTL::RenderCommandEncoder* RenderCommandEncoder);`
- L74 _public prototype_ `FMetalCounterSamplePtr SetupBoundaryCounters(MTL::ComputeCommandEncoder* ComputeCommandEncoder);`
- L75 _public prototype_ `FMetalCounterSamplePtr SetupBoundaryCounters(MTL::BlitCommandEncoder* BlitCommandEncoder);`
- L77 _public prototype_ `MTL::CounterSampleBuffer* SwapOrAllocateBuffer(uint32_t SampleSize, uint32_t& OutOffset);`
- L80 _private member_ `FMetalDevice* Device;`
- L81 _private member_ `MTL::CounterSampleBuffer* SampleBuffer = nullptr;`
- L82 _private member_ `TArray<MTL::CounterSampleBuffer*> SampleBufferFreePool;`
- L83 _private member_ `FCriticalSection Mutex;`
- L85 _private member_ `uint32_t Offset = 0;`
- L86 _private member_ `uint32_t Size = 0;`

#### Free symbols / members of external scopes

- L62 _typedef_ `typedef TSharedPtr<FMetalCounterSample> FMetalCounterSamplePtr;`

### `Source/Runtime/Apple/MetalRHI/Private/MetalDevice.h` (Private)


#### enum `EMetalQueueType`  
`enum class EMetalQueueType`  
_L21-25_
- desc: Defines a unique command queue type within a Metal Device (owner by the command list managers). Currently only implements direct
- L23 _public enumerator_ `Direct = 0`
- L24 _public enumerator_ `Count`

#### enum `EMetalDebugLevel`  
`enum EMetalDebugLevel`  
_L76-84_
- desc: EMetalDebugLevel: Level of Metal debug features to be enabled.
- L78 _public enumerator_ `EMetalDebugLevelOff`
- L79 _public enumerator_ `EMetalDebugLevelFastValidation`
- L80 _public enumerator_ `EMetalDebugLevelResetOnBind`
- L81 _public enumerator_ `EMetalDebugLevelConditionalSubmit`
- L82 _public enumerator_ `EMetalDebugLevelValidation`
- L83 _public enumerator_ `EMetalDebugLevelWaitForComplete`

#### enum `EMetalShaderValidationType`  
`enum class EMetalShaderValidationType`  
_L89-95_
- desc: EMetalShaderValidationType: Type of Metal Shader Validation to perform
- L91 _public enumerator_ `All`
- L92 _public enumerator_ `ComputeOnly`
- L93 _public enumerator_ `RenderPipelineOnly`
- L94 _public enumerator_ `ShaderName`

#### class `FMetalDevice`  
`class FMetalDevice`  
_L102-276_
- L105 _public prototype_ `static FMetalDevice* CreateDevice();`
- L106 _public prototype_ `virtual ~FMetalDevice();`
- L108 _public prototype_ `void PostInit();`
- L110 _public prototype_ `void EnumerateFeatureSupport();`
- L111 _public function_ `inline bool SupportsFeature(EMetalFeatures InFeature)`
- L113 _public function_ `inline FMetalResourceHeap& GetResourceHeap(void)`
- L115 _public prototype_ `void EndDrawingViewport(const FRHIPresentArgs& InPresentArgs);`
- L117 _public prototype_ `MTLTexturePtr CreateTexture(FMetalSurface* Surface, MTL::TextureDescriptor* Descriptor);`
- L118 _public prototype_ `FMetalBufferPtr CreatePooledBuffer(FMetalPooledBufferArgs const& Args);`
- L119 _public prototype_ `MTLEventPtr CreateEvent();`
- L120 _public prototype_ `MTLSharedEventPtr CreateSharedEvent();`
- L122 _public prototype_ `void DrainHeap();`
- L123 _public prototype_ `void GarbageCollect();`
- L125 _public function_ `FMetalTempAllocator* GetTransferAllocator()`
- L130 _public function_ `FMetalTempAllocator* GetUniformAllocator()`
- L135 _public function_ `uint32 GetFrameNumberRHIThread()`
- L140 _public function_ `FMetalCommandQueue& GetCommandQueue(EMetalQueueType QueueType)`
- L147 _public function_ `FMetalBindlessDescriptorManager* GetBindlessDescriptorManager()`
- L152 _public function_ `FMetalStaticSamplers* GetStaticSamplers()`
- L159 _public prototype_ `void AddActiveBuffer(MTL::Buffer* Buffer, const NS::Range& Range);`
- L160 _public prototype_ `void RemoveActiveBuffer(MTL::Buffer* Buffer, const NS::Range& Range);`
- L161 _public prototype_ `bool ValidateIsInactiveBuffer(MTL::Buffer* Buffer, const NS::Range& Range);`
- L164 _public function_ `MTL::Device* GetDevice()`
- L169 _public function_ `inline int32 GetRuntimeDebuggingLevel(void) const`
- L174 _public function_ `void IncrementFrameRHIThread()`
- L179 _public function_ `dispatch_semaphore_t& GetFrameSemaphore()`
- L184 _public function_ `FMetalCounterSampler* GetCounterSampler()`
- L189 _public function_ `bool IsShaderValidationEnabled()`
- L194 _public function_ `void ForceHeapSupport()`
- L199 _private prototype_ `FMetalDevice(MTL::Device* MetalDevices);`
- L201 _private prototype_ `void FlushFreeList(bool const bFlushFences = true);`
- L204 _private member_ `MTL::Device* Device;`
- L206 _private member_ `TArray<FMetalCommandQueue*, TInlineAllocator<(uint32)EMetalQueueType::Count>> CommandQueues;`
- L209 _private member_ `dispatch_semaphore_t FrameSemaphore;` — A sempahore used to ensure that wait for previous frames to complete if more are in flight than we permit
- L212 _private member_ `FMetalResourceHeap Heap;` — Dynamic memory heap
- L215 _private member_ `FMetalCaptureManager* CaptureManager;` — GPU Frame Capture Manager
- L217 _private member_ `FMetalTempAllocator* UniformBufferAllocator;`
- L218 _private member_ `FMetalTempAllocator* TransferBufferAllocator;`
- L222 _private member_ `TArray<FMetalFence*> FrameFences;` — The list of fences for the current frame
- L224 _private member_ `FCriticalSection ActiveBuffersMutex;`
- L227 _private member_ `TMap<MTL::Buffer*, TArray<NS::Range>> ActiveBuffers;` — These are the active buffers that cannot be CPU modified
- L231 _private member_ `FCriticalSection FreeListMutex;` — Critical section for FreeList
- L234 _private member_ `FEvent* FrameReadyEvent;` — Event for coordinating pausing of render thread to keep inline with the ios display link.
- L237 _private member_ `uint32 FrameCounter = 0;` — Internal frame counter, used to ensure that we only drain the buffer pool one after each frame within RHIEndFrame.
- L240 _private member_ `uint64 Features = 0;` — Bitfield of supported Metal features with varying availability depending on OS/device
- L243 _private member_ `FMetalPipelineStateCacheManager* PSOManager;` — PSO cache manager
- L246 _private member_ `uint32 FrameNumberRHIThread = 0;` — Thread index owned by the RHI Thread. Monotonically increases every call to EndFrame()
- L248 _private member_ `int32 RuntimeDebuggingLevel = 0;`
- L250 _private member_ `FMetalCounterSampler* CounterSampler = nullptr;`
- L252 _private member_ `bool bShaderValidationEnabled = false;`
- L256 _private member_ `FMetalBindlessDescriptorManager* BindlessDescriptorManager;` — Bindless Descriptor Heaps manager.
- L257 _private member_ `FMetalStaticSamplers* StaticSamplers;`
- L261 _private member_ `FMetalRayTracingCompactionRequestHandler* RayTracingCompactionRequestHandler;`
- L262 _private member_ `FMetalRayTracingPipelineCache* RayTracingPipelineCache;`
- L264 _private prototype_ `void InitializeRayTracing();`
- L265 _private prototype_ `void CleanUpRayTracing();`
- L268 _public prototype_ `void UpdateRayTracing(FMetalRHICommandContext& Context);`
- L270 _public function_ `inline FMetalRayTracingCompactionRequestHandler* GetRayTracingCompactionRequestHandler() const`
- L271 _public function_ `inline FMetalRayTracingPipelineCache* GetRayTracingPipelineCache() const`
- L274 _public member_ `FMetalBufferPtr DummyIndexBuffer;` — Dummy Index buffer used when creating descriptors

#### Free symbols / members of external scopes

- L31 _typedef_ `typedef NS_OPTIONS(uint32, EMetalFeatures) { EMetalFeaturesCountingQueries = 1 << 1, EMetalFeaturesBaseVertexInstance = 1 << 2, EMetalFeaturesIndirectBuffer = 1 << 3, EMetalFeaturesLayeredRendering = 1 << 4, EMetalFeaturesValidation = 1 << 5, EMetalFeaturesHeaps = 1 << 6, EMetalFeaturesFences = 1 << 7, EMetalFeaturesMSAADepthResolve = 1 << 8, EMetalFeaturesMSAAStoreAndResolve = 1 << 9, EMetalFeaturesCubemapArrays = 1 << 10, EMetalFeaturesMultipleViewports = 1 << 11, EMetalFeaturesPresentMinDuration = 1 << 12, EMetalFeaturesEfficientBufferBlits = 1 << 13, EMetalFeaturesBufferSubAllocation = 1 << 14, EMetalFeaturesPrivateBufferSubAllocation = 1 << 15, EMetalFeaturesTileShaders = 1 << 16, EMetalFeaturesStageCounterSampling = 1 << 17, EMetalFeaturesBoundaryCounterSampling = 1 << 18, EMetalFeaturesRayTracing = 1 << 19,` — Enumeration of features which are present only on some OS/device combinations. These have to be checked at runtime as well as compile time to ensure backward compatibility.

### `Source/Runtime/Apple/MetalRHI/Private/MetalDynamicRHI.h` (Private)


#### struct `FMetalDeferredDeleteObject`  
`struct FMetalDeferredDeleteObject`  
_L26-67_
- L38 _public typedef_ `TUniqueFunction<void()>*> TObjectStorage;`
- L40 _public member_ `TObjectStorage Storage;`
- L42 _public function_ `explicit FMetalDeferredDeleteObject(FMetalBufferPtr InBuffer) : Storage(TInPlaceType<FMetalBufferPtr>(), InBuffer)`
- L45 _public function_ `explicit FMetalDeferredDeleteObject(MTLTexturePtr InTexture) : Storage(TInPlaceType<MTLTexturePtr>(), InTexture)`
- L48 _public function_ `explicit FMetalDeferredDeleteObject(NS::Object* InObject) : Storage(TInPlaceType<NS::Object*>(), InObject)`
- L52 _public function_ `explicit FMetalDeferredDeleteObject(FRHIDescriptorHandle InHandle) : Storage(TInPlaceType<FRHIDescriptorHandle>(), InHandle)`
- L56 _public function_ `explicit FMetalDeferredDeleteObject(FMetalFence* InFence) : Storage(TInPlaceType<FMetalFence*>(), InFence)`
- L60 _public function_ `explicit FMetalDeferredDeleteObject(FMetalAccelerationStructure* InAccelerationStructure) : Storage(TInPlaceType<FMetalAccelerationStructure*>(), InAccelerationStructure)`
- L64 _public function_ `explicit FMetalDeferredDeleteObject(TUniqueFunction<void()>&& Func) : Storage(TInPlaceType<TUniqueFunction<void()>*>(), new TUniqueFunction<void()>(MoveTemp(Func)))`

#### struct `FMetalFinalizedCommands`  
`struct FMetalFinalizedCommands final : public IRHIPlatformCommandList, public TArray<FMetalPayload*>`  
_L69-70_
- inherits: `IRHIPlatformCommandList,TArray<FMetalPayload*>`

#### class `FMetalDynamicRHI`  
`class FMetalDynamicRHI : public IMetalDynamicRHI`  
_L73-314_
- inherits: `IMetalDynamicRHI`
- desc: The interface which is implemented by the dynamically bound RHI.
- L75 _private member_ `static inline FMetalDynamicRHI* Singleton = nullptr;`
- L87 _public prototype_ `FRIEND_ENUM_CLASS_FLAGS(EQueueStatus);`
- L94 _public function_ `static inline FMetalDynamicRHI& Get()`
- L97 _public prototype_ `FMetalDynamicRHI(ERHIFeatureLevel::Type RequestedFeatureLevel);` — Initialization constructor.
- L100 _public prototype_ `~FMetalDynamicRHI();` — Destructor
- L103 _public prototype_ `virtual void Init();` — FDynamicRHI interface.
- L104 _public function_ `virtual void Shutdown()`
- L105 _public function_ `virtual const TCHAR* GetName() override`
- L107 _public prototype_ `virtual void RHIEndFrame_RenderThread(FRHICommandListImmediate& RHICmdList) final override;`
- L108 _public prototype_ `virtual void RHIEndFrame(const FRHIEndFrameArgs& Args) final override;`
- L110 _public prototype_ `virtual FRHIShaderLibraryRef RHICreateShaderLibrary(EShaderPlatform Platform, FString const& FilePath, FString const& Name) final override;`
- L111 _public prototype_ `virtual FSamplerStateRHIRef RHICreateSamplerState(const FSamplerStateInitializerRHI& Initializer) final override;`
- L112 _public prototype_ `virtual FRasterizerStateRHIRef RHICreateRasterizerState(const FRasterizerStateInitializerRHI& Initializer) final override;`
- L113 _public prototype_ `virtual FDepthStencilStateRHIRef RHICreateDepthStencilState(const FDepthStencilStateInitializerRHI& Initializer) final override;`
- L114 _public prototype_ `virtual FBlendStateRHIRef RHICreateBlendState(const FBlendStateInitializerRHI& Initializer) final override;`
- L115 _public prototype_ `virtual FVertexDeclarationRHIRef RHICreateVertexDeclaration(const FVertexDeclarationElementList& Elements) final override;`
- L116 _public prototype_ `virtual FPixelShaderRHIRef RHICreatePixelShader(const FRHICreateShaderDesc& CreateShaderDesc) final override;`
- L117 _public prototype_ `virtual FVertexShaderRHIRef RHICreateVertexShader(const FRHICreateShaderDesc& CreateShaderDesc) final override;`
- L118 _public prototype_ `virtual FGeometryShaderRHIRef RHICreateGeometryShader(const FRHICreateShaderDesc& CreateShaderDesc) final override;`
- L119 _public prototype_ `virtual FComputeShaderRHIRef RHICreateComputeShader(const FRHICreateShaderDesc& CreateShaderDesc) final override;`
- L121 _public prototype_ `virtual FMeshShaderRHIRef RHICreateMeshShader(const FRHICreateShaderDesc& CreateShaderDesc) final override;`
- L122 _public prototype_ `virtual FAmplificationShaderRHIRef RHICreateAmplificationShader(const FRHICreateShaderDesc& CreateShaderDesc) final override;`
- L124 _public prototype_ `virtual FBoundShaderStateRHIRef RHICreateBoundShaderState(FRHIVertexDeclaration* VertexDeclaration, FRHIVertexShader* VertexShader, FRHIPixelShader* PixelShader, FRHIGeometryShader* GeometryShader) final override;`
- L125 _public prototype_ `virtual FGraphicsPipelineStateRHIRef RHICreateGraphicsPipelineState(const FGraphicsPipelineStateInitializer& Initializer) final override;`
- L126 _public prototype_ `virtual TRefCountPtr<FRHIComputePipelineState> RHICreateComputePipelineState(const FComputePipelineStateInitializer& Initializer) final override;`
- L127 _public prototype_ `virtual FUniformBufferRHIRef RHICreateUniformBuffer(const void* Contents, const FRHIUniformBufferLayout* Layout, EUniformBufferUsage Usage, EUniformBufferValidation Validation) final override;`
- L129 _public prototype_ `[[nodiscard]] virtual FRHIBufferInitializer RHICreateBufferInitializer(FRHICommandListBase& RHICmdList, const FRHIBufferCreateDesc& CreateDesc) final override;`
- L131 _public prototype_ `virtual void RHIReplaceResources(FRHICommandListBase& RHICmdList, TArray<FRHIResourceReplaceInfo>&& ReplaceInfos) final override;`
- L132 _public prototype_ `virtual void RHIWriteResourceGPUAddresses(FRHICommandListBase& RHICmdList, uint32 GPUIndex, TConstArrayView<FRHIResource*> Resources, uint64* AddressesPtr) final override;`
- L134 _public prototype_ `virtual void * RHILockBuffer(class FRHICommandListBase& RHICmdList, FRHIBuffer* Buffer, uint32 Offset, uint32 SizeRHI, EResourceLockMode LockMode) final override;`
- L135 _public prototype_ `virtual void RHIUnlockBuffer(class FRHICommandListBase& RHICmdList, FRHIBuffer* Buffer) final override;`
- L136 _public prototype_ `virtual void* LockBuffer_BottomOfPipe(FRHICommandListBase& RHICmdList, FRHIBuffer* Buffer, uint32 Offset, uint32 SizeRHI, EResourceLockMode LockMode) final override;`
- L137 _public prototype_ `virtual void UnlockBuffer_BottomOfPipe(FRHICommandListBase& RHICmdList, FRHIBuffer* Buffer) final override;`
- L140 _public prototype_ `virtual void RHIUpdateAllocationTags(FRHICommandListBase& RHICmdList, FRHIBuffer* Buffer) final override;`
- L144 _public prototype_ `virtual FShaderResourceViewRHIRef RHICreateShaderResourceView (class FRHICommandListBase& RHICmdList, FRHIViewableResource* Resource, FRHIViewDesc const& ViewDesc) final override;` — SRV / UAV creation functions
- L145 _public prototype_ `virtual FUnorderedAccessViewRHIRef RHICreateUnorderedAccessView(class FRHICommandListBase& RHICmdList, FRHIViewableResource* Resource, FRHIViewDesc const& ViewDesc) final override;`
- L148 _public prototype_ `virtual FRHIResourceCollectionRef RHICreateResourceCollection(FRHICommandListBase& RHICmdList, TConstArrayView<FRHIResourceCollectionMember> InMembers) final override;`
- L149 _public prototype_ `virtual void RHIUpdateResourceCollection(FRHICommandListBase& RHICmdList, FRHIResourceCollection* InResourceCollection, uint32 InStartIndex, TConstArrayView<FRHIResourceCollectionMember> InMemberUpdates) final override;`
- L152 _public prototype_ `virtual FRHICalcTextureSizeResult RHICalcTexturePlatformSize(FRHITextureDesc const& Desc, uint32 FirstMipIndex) final override;`
- L153 _public prototype_ `virtual uint64 RHIGetMinimumAlignmentForBufferBackedSRV(EPixelFormat Format) final override;`
- L154 _public prototype_ `virtual void RHIGetTextureMemoryStats(FTextureMemoryStats& OutStats) final override;`
- L155 _public prototype_ `virtual bool RHIGetTextureMemoryVisualizeData(FColor* TextureData,int32 SizeX,int32 SizeY,int32 Pitch,int32 PixelSize) final override;`
- L156 _public prototype_ `[[nodiscard]] virtual FRHITextureInitializer RHICreateTextureInitializer(FRHICommandListBase& RHICmdList, const FRHITextureCreateDesc& CreateDesc) final override;`
- L157 _public prototype_ `virtual FTextureRHIRef RHIAsyncCreateTexture2D(uint32 SizeX, uint32 SizeY, uint8 Format, uint32 NumMips, ETextureCreateFlags Flags, ERHIAccess InResourceState, void** InitialMipData, uint32 NumInitialMips, const TCHAR* DebugName, FGraphEventRef& OutCompletionEvent) final override;`
- L158 _public prototype_ `virtual uint32 RHIComputeMemorySize(FRHITexture* TextureRHI) final override;`
- L160 _public prototype_ `virtual FRHILockTextureResult RHILockTexture(FRHICommandListImmediate& RHICmdList, const FRHILockTextureArgs& Arguments) final override;`
- L161 _public prototype_ `virtual void RHIUnlockTexture(FRHICommandListImmediate& RHICmdList, const FRHILockTextureArgs& Arguments) final override;`
- L163 _public prototype_ `virtual void RHIUpdateTexture2D(FRHICommandListBase& RHICmdList, FRHITexture* Texture, uint32 MipIndex, const struct FUpdateTextureRegion2D& UpdateRegion, uint32 SourcePitch, const uint8* SourceData) final override;`
- L164 _public prototype_ `virtual void RHIUpdateTexture3D(FRHICommandListBase& RHICmdList, FRHITexture* Texture, uint32 MipIndex, const struct FUpdateTextureRegion3D& UpdateRegion, uint32 SourceRowPitch, uint32 SourceDepthPitch, const uint8* SourceData) final override;`
- L165 _public prototype_ `virtual void RHIBindDebugLabelName(FRHICommandListBase& RHICmdList, FRHITexture* Texture, const TCHAR* Name) final override;`
- L166 _public prototype_ `virtual void RHIReadSurfaceData(FRHITexture* Texture,FIntRect Rect,TArray<FColor>& OutData,FReadSurfaceDataFlags InFlags) final override;`
- L167 _public prototype_ `virtual void RHIReadSurfaceData(FRHITexture* TextureRHI, FIntRect InRect, TArray<FLinearColor>& OutData, FReadSurfaceDataFlags InFlags) final override;`
- L169 _public prototype_ `virtual bool RHIReadViewportDataDirect(uint32& OutWidth, uint32& OutHeight, TArray<FColor>& OutData) final override;`
- L171 _public prototype_ `virtual void RHIMapStagingSurface(FRHITexture* Texture, FRHIGPUFence* Fence, void*& OutData, int32& OutWidth, int32& OutHeight, uint32 GPUIndex = 0) final override;`
- L172 _public prototype_ `virtual void RHIUnmapStagingSurface(FRHITexture* Texture, uint32 GPUIndex = 0) final override;`
- L173 _public prototype_ `virtual void RHIReadSurfaceFloatData(FRHITexture* Texture,FIntRect Rect,TArray<FFloat16Color>& OutData,ECubeFace CubeFace,int32 ArrayIndex,int32 MipIndex) final override;`
- L174 _public prototype_ `virtual void RHIRead3DSurfaceFloatData(FRHITexture* Texture,FIntRect Rect,FIntPoint ZMinMax,TArray<FFloat16Color>& OutData) final override;`
- L175 _public prototype_ `virtual FRenderQueryRHIRef RHICreateRenderQuery(ERenderQueryType QueryType) final override;`
- L176 _public prototype_ `virtual bool RHIGetRenderQueryResult(FRHIRenderQuery* RenderQuery, uint64& OutResult, bool bWait, uint32 GPUIndex = INDEX_NONE) final override;`
- L177 _public prototype_ `virtual FTextureRHIRef RHIGetViewportBackBuffer(FRHIViewport* Viewport) final override;`
- L178 _public prototype_ `virtual FTextureRHIRef RHIGetViewportBackBufferAtLayerIndex(FRHIViewport* Viewport, uint32 DrawLayerIndex) final override;`
- L179 _public prototype_ `virtual FViewportRHIRef RHICreateViewport(void* WindowHandle, uint32 SizeX, uint32 SizeY, bool bIsFullscreen, EPixelFormat PixelFormat) final override;`
- L180 _public prototype_ `virtual void RHIResizeViewport(FRHIViewport* Viewport, uint32 SizeX, uint32 SizeY, bool bIsFullscreen, EPixelFormat PixelFormat) final override;`
- L181 _public prototype_ `virtual void RHIEndDrawingViewport(FRHICommandListImmediate& RHICmdList, FRHIViewport* Viewport, const FRHIPresentArgs& PresentArgs) final override;`
- L182 _public prototype_ `virtual void RHITick(float DeltaTime) final override;`
- L183 _public prototype_ `virtual void RHIBlockUntilGPUIdle() final override;`
- L184 _public prototype_ `virtual bool RHIGetAvailableResolutions(FScreenResolutionArray& Resolutions, bool bIgnoreRefreshRate) final override;`
- L185 _public prototype_ `virtual void RHIGetSupportedResolution(uint32& Width, uint32& Height) final override;`
- L186 _public prototype_ `virtual MTL::Device* RHIGetDevice() final override;`
- L187 _public prototype_ `virtual void* RHIGetNativeDevice() final override;`
- L188 _public prototype_ `virtual void* RHIGetNativeGraphicsQueue() final override;`
- L189 _public prototype_ `virtual void* RHIGetNativeComputeQueue() final override;`
- L191 _public prototype_ `virtual class IRHICommandContext* RHIGetDefaultContext() final override;`
- L192 _public prototype_ `virtual IRHIUploadContext* RHIGetUploadContext() final override;`
- L194 _public prototype_ `virtual IRHIComputeContext* RHIGetCommandContext(ERHIPipeline Pipeline) final override;`
- L195 _public prototype_ `virtual IRHICommandContext* RHIGetParallelCommandContext(FRHIParallelRenderPassInfo const& ParallelRenderPass) final override;`
- L197 _public prototype_ `virtual FRHIFinalizeContextsResult RHIFinalizeContexts(FRHIFinalizeContextsArgs&& Args) final override;`
- L198 _public prototype_ `virtual void RHISubmitCommandLists(FRHISubmitCommandListsArgs&& Args) final override;`
- L199 _public prototype_ `virtual void RHIProcessDeleteQueue() final override;`
- L201 _public prototype_ `virtual FUpdateTexture3DData RHIBeginUpdateTexture3D(FRHICommandListBase& RHICmdList, FRHITexture* Texture, uint32 MipIndex, const struct FUpdateTextureRegion3D& UpdateRegion) final override;`
- L202 _public prototype_ `virtual void RHIEndUpdateTexture3D(FRHICommandListBase& RHICmdList, FUpdateTexture3DData& UpdateData) final override;`
- L204 _public prototype_ `virtual void RHICreateTransition(FRHITransition* Transition, const FRHITransitionCreateInfo& CreateInfo) final override;`
- L205 _public prototype_ `virtual void RHIReleaseTransition(FRHITransition* Transition) final override;`
- L207 _public prototype_ `virtual FGPUFenceRHIRef RHICreateGPUFence(const FName &Name) final override;`
- L208 _public prototype_ `virtual void RHIWriteGPUFence_TopOfPipe(FRHICommandListBase& RHICmdList, FRHIGPUFence* FenceRHI) final override;`
- L210 _public prototype_ `virtual FStagingBufferRHIRef RHICreateStagingBuffer() final override;`
- L211 _public prototype_ `virtual void* RHILockStagingBuffer(FRHIStagingBuffer* StagingBuffer, FRHIGPUFence* Fence, uint32 Offset, uint32 SizeRHI) final override;`
- L212 _public prototype_ `virtual void RHIUnlockStagingBuffer(FRHIStagingBuffer* StagingBuffer) final override;`
- L214 _public prototype_ `virtual void RHIUpdateUniformBuffer(FRHICommandListBase& RHICmdList, FRHIUniformBuffer* UniformBufferRHI, const void* Contents) final override;`
- L216 _public prototype_ `virtual uint16 RHIGetPlatformTextureMaxSampleCount() override;`
- L219 _public prototype_ `virtual FRayTracingAccelerationStructureSize RHICalcRayTracingSceneSize(const FRayTracingSceneInitializer& Initializer) final override;`
- L220 _public prototype_ `virtual FRayTracingAccelerationStructureSize RHICalcRayTracingGeometrySize(const FRayTracingGeometryInitializer& Initializer) final override;`
- L222 _public prototype_ `virtual FRayTracingGeometryRHIRef RHICreateRayTracingGeometry(FRHICommandListBase& RHICmdList, const FRayTracingGeometryInitializer& Initializer) final override;`
- L223 _public prototype_ `virtual FRayTracingSceneRHIRef RHICreateRayTracingScene(FRayTracingSceneInitializer Initializer) final override;`
- L224 _public prototype_ `virtual FRayTracingShaderRHIRef RHICreateRayTracingShader(const FRHICreateShaderDesc& CreateShaderDesc, EShaderFrequency ShaderFrequency) final override;`
- L225 _public prototype_ `virtual FRayTracingPipelineStateRHIRef RHICreateRayTracingPipelineState(const FRayTracingPipelineStateInitializer& Initializer) final override;`
- L227 _public prototype_ `virtual FShaderBindingTableRHIRef RHICreateShaderBindingTable(FRHICommandListBase& RHICmdList, const FRayTracingShaderBindingTableInitializer& Initializer) final override;`
- L230 _public prototype_ `virtual FTextureReferenceRHIRef RHICreateTextureReference(FRHICommandListBase& RHICmdList, FRHITexture* InReferencedTexture) final override;`
- L231 _public prototype_ `virtual void RHIUpdateTextureReference(FRHICommandListBase& RHICmdList, FRHITextureReference* TextureRef, FRHITexture* NewTexture) final override;`
- L234 _public prototype_ `virtual uint64 RHIComputePrecachePSOHash(const FGraphicsPipelineStateInitializer& Initializer) final override;`
- L235 _public prototype_ `virtual bool RHIMatchPrecachePSOInitializers(const FGraphicsPipelineStateInitializer& LHS, const FGraphicsPipelineStateInitializer& RHS) final override;`
- L237 _public prototype_ `virtual void RHIBeginRenderQuery_TopOfPipe(FRHICommandListBase& RHICmdList, FRHIRenderQuery* RenderQuery) override;`
- L238 _public prototype_ `virtual void RHIEndRenderQuery_TopOfPipe (FRHICommandListBase& RHICmdList, FRHIRenderQuery* RenderQuery) override;`
- L240 _public prototype_ `virtual void RHIBeginRenderQueryBatch_TopOfPipe(FRHICommandListBase& RHICmdList, ERenderQueryType QueryType) final override;`
- L241 _public prototype_ `virtual void RHIEndRenderQueryBatch_TopOfPipe(FRHICommandListBase& RHICmdList, ERenderQueryType QueryType) final override;`
- L243 _public prototype_ `virtual void RHIRunOnQueue(TFunction<void(MTL::CommandQueue*)>&& CodeToRun, bool bWaitForSubmission) final override;`
- L245 _public prototype_ `virtual FTextureRHIRef RHICreateTexture2DFromCVMetalTexture(EPixelFormat Format, ETextureCreateFlags TexCreateFlags, const FClearValueBinding& ClearValueBinding, CVMetalTextureRef Resource) final override;`
- L248 _public function_ `template <typename ...Args> void DeferredDelete(Args&&... InArgs)`
- L255 _public prototype_ `void SubmitCommands(TConstArrayView<struct FMetalFinalizedCommands*> Commands);`
- L256 _public prototype_ `void SubmitPayloads(TArray<FMetalPayload*>&& Payloads);`
- L259 _public prototype_ `void FlushBatchedPayloads(FMetalCommandQueue::FPayloadArray& PayloadsToHandDown);` — Ensures all prior batched command lists have reached the MetalQueue
- L263 _public prototype_ `void ProcessInterruptQueueUntil(FGraphEvent* GraphEvent);` — Processes the interrupt queue on the calling thread, until the specified GraphEvent is signaled. If the GraphEvent is nullptr, processes the queue until no further progress is made.
- L265 _public prototype_ `void ProcessPendingCommandBuffers(TArrayView<FMetalCommandBuffer*> CommandBuffers);`
- L268 _public prototype_ `void ProcessInterruptQueueOnGPUCrash();` — Called when the GPU has crashed. This function will not return.
- L278 _public member_ `FMetalTimingArray CurrentTimingPerQueue;`
- L280 _public prototype_ `void InitializeSubmissionPipe();`
- L281 _public prototype_ `void ShutdownSubmissionPipe();`
- L284 _public prototype_ `void EnqueueEndOfPipeTask(TUniqueFunction<void()> TaskFunc, TUniqueFunction<void(FMetalPayload&)> ModifyPayloadCallback = {});` — Inserts a task graph task which is executed once all previously submitted GPU work has completed (across all queues, device and adapters).
- L285 _public member_ `FGraphEventRef EopTask;`
- L287 _public member_ `FCriticalSection SubmissionCS;`
- L288 _public member_ `FCriticalSection InterruptCS;`
- L290 _public prototype_ `FProcessResult ProcessSubmissionQueue();`
- L291 _public prototype_ `FProcessResult ProcessInterruptQueue();`
- L294 _public prototype_ `void ForEachQueue(TFunctionRef<void(FMetalCommandQueue&)> Callback);` — Enumerates all queues across all devices and active adapters
- L297 _private member_ `FMetalDevice* Device;`
- L298 _private member_ `FTextureMemoryStats MemoryStats;`
- L299 _private member_ `TMap<uint32, FVertexDeclarationRHIRef> VertexDeclarationCache;`
- L300 _private member_ `TLockFreePointerListUnordered<FMetalRHICommandContext, PLATFORM_CACHE_LINE_SIZE> MetalCommandContextPool;`
- L302 _private member_ `FCriticalSection ObjectsToDeleteCS;`
- L303 _private member_ `TArray<FMetalDeferredDeleteObject> ObjectsToDelete;`
- L306 _private member_ `struct IRCompiler* CompilerInstance;`
- L310 _private member_ `class FMetalThread* SubmissionThread = nullptr;`
- L311 _private member_ `class FMetalThread* InterruptThread = nullptr;`
- L313 _private member_ `TQueue<TArray<FMetalPayload*>*, EQueueMode::Mpsc> PendingPayloadsForSubmission;`

#### enum `FMetalDynamicRHI::EQueueStatus`  
`enum class EQueueStatus`  
_L77-86_
- L79 _public enumerator_ `None = 0`
- L82 _public enumerator_ `Processed = 1 << 0` — Work was processed through the queue.
- L85 _public enumerator_ `Pending = 1 << 1` — The queue has further, unprocessed work.

#### struct `FMetalDynamicRHI::FProcessResult`  
`struct FProcessResult`  
_L89-92_
- L91 _public member_ `EQueueStatus Status = EQueueStatus::None;`

#### struct `FMetalDynamicRHI::FMetalTimingArray`  
`struct FMetalTimingArray : public TArray<TUniquePtr<FMetalTiming>, TInlineAllocator<GMetalMaxNumQueues>>`  
_L270-276_
- inherits: `TArray<TUniquePtr<FMetalTiming>,TInlineAllocator<GMetalMaxNumQueues>>`
- L272 _public function_ `FMetalTiming* CreateNew(FMetalCommandQueue& Queue)`

#### Free symbols / members of external scopes

- L316 _prototype_ `ENUM_CLASS_FLAGS(FMetalDynamicRHI::EQueueStatus);`

### `Source/Runtime/Apple/MetalRHI/Private/MetalDynamicRHIModule.h` (Private)


#### class `FMetalDynamicRHIModule`  
`class FMetalDynamicRHIModule : public IDynamicRHIModule`  
_L16-22_
- inherits: `IDynamicRHIModule`
- L19 _public prototype_ `virtual bool IsSupported() override final;`
- L21 _public prototype_ `virtual FDynamicRHI* CreateRHI(ERHIFeatureLevel::Type RequestedFeatureLevel = ERHIFeatureLevel::Num) override final;`

### `Source/Runtime/Apple/MetalRHI/Private/MetalFence.h` (Private)


#### class `FMetalFence`  
`class FMetalFence`  
_L11-91_
- L14 _public function_ `FMetalFence() : NumRefs(0)`
- L20 _public function_ `explicit FMetalFence(FMetalFence const& Other) : NumRefs(0)`
- L26 _public function_ `~FMetalFence()`
- L31 _public function_ `uint32 AddRef() const`
- L35 _public prototype_ `uint32 Release() const;`
- L36 _public function_ `uint32 GetRefCount() const`
- L41 _public function_ `FMetalFence& operator=(FMetalFence const& Other)`
- L50 _public function_ `void Reset(void)`
- L56 _public function_ `void Write()`
- L61 _public function_ `void Wait()`
- L66 _public function_ `int8 NumWrite() const`
- L71 _public function_ `int8 NumWait() const`
- L76 _public function_ `MTL::Fence* Get() const`
- L81 _public function_ `void Set(MTL::Fence* InFence)`
- L87 _private member_ `MTL::Fence* Fence;`
- L88 _private member_ `int8 WriteNum;`
- L89 _private member_ `int8 WaitNum;`
- L90 _private member_ `mutable int32 NumRefs;`

#### class `FMetalFencePool`  
`class FMetalFencePool`  
_L93-125_
- L100 _public function_ `FMetalFencePool()`
- L102 _public function_ `static FMetalFencePool& Get()`
- L108 _public prototype_ `void Initialise(MTL::Device* InDevice);`
- L110 _public prototype_ `FMetalFence* AllocateFence();`
- L111 _public prototype_ `void ReleaseFence(FMetalFence* InFence);`
- L113 _public function_ `int32 Max() const`
- L114 _public function_ `int32 Num() const`
- L117 _private member_ `int32 Count;`
- L118 _private member_ `int32 Allocated;`
- L119 _private member_ `MTL::Device* Device;`
- L121 _private member_ `TSet<FMetalFence*> Fences;`
- L122 _private member_ `FCriticalSection Mutex;`
- L124 _private member_ `TLockFreePointerListFIFO<FMetalFence, PLATFORM_CACHE_LINE_SIZE> Lifo;`

#### enum `FMetalFencePool::(anonymous)`  
``  
_L96-98_

#### Free symbols / members of external scopes

- L97 _enumerator_ `NumFences = 2048` (scope `FMetalFencePool::__anon83c8c7a30103`)

### `Source/Runtime/Apple/MetalRHI/Private/MetalGraphicsPipelineState.h` (Private)


#### class `FMetalGraphicsPipelineState`  
`class FMetalGraphicsPipelineState : public FRHIGraphicsPipelineState`  
_L17-101_
- inherits: `FRHIGraphicsPipelineState`
- L22 _public prototype_ `virtual ~FMetalGraphicsPipelineState();`
- L24 _public function_ `FRHIGraphicsShader* GetShader(EShaderFrequency Frequency) const override`
- L56 _public prototype_ `FMetalShaderPipelinePtr GetPipeline();`
- L59 _public member_ `TRefCountPtr<FMetalVertexDeclaration> VertexDeclaration;` — Cached vertex structure
- L62 _public member_ `TRefCountPtr<FMetalVertexShader> VertexShader;` — Cached shaders
- L63 _public member_ `TRefCountPtr<FMetalPixelShader> PixelShader;`
- L65 _public member_ `TRefCountPtr<FMetalGeometryShader> GeometryShader;`
- L68 _public member_ `TRefCountPtr<FMetalMeshShader> MeshShader;`
- L69 _public member_ `TRefCountPtr<FMetalAmplificationShader> AmplificationShader;`
- L73 _public member_ `TRefCountPtr<FMetalDepthStencilState> DepthStencilState;` — Cached state objects
- L74 _public member_ `TRefCountPtr<FMetalRasterizerState> RasterizerState;`
- L76 _public function_ `EPrimitiveType GetPrimitiveType()`
- L81 _public function_ `bool GetDepthBounds() const`
- L87 _public member_ `TArray<uint8_t> StageInFunctionBytecode;`
- L92 _private prototype_ `FMetalGraphicsPipelineState(const FGraphicsPipelineStateInitializer& Init);` — This can only be created through the RHI to make sure Compile() is called.
- L95 _private prototype_ `bool Compile();` — Compiles the underlying gpu pipeline objects. This must be called before usage.
- L98 _private member_ `FGraphicsPipelineStateInitializer Initializer;` — Needed to runtime refine shaders currently.
- L100 _private member_ `FMetalShaderPipelinePtr PipelineState;`

### `Source/Runtime/Apple/MetalRHI/Private/MetalHashedVertexDescriptor.h` (Private)


#### struct `FMetalHashedVertexDescriptor`  
`struct FMetalHashedVertexDescriptor`  
_L21-45_
- desc: The MTLVertexDescriptor and a pre-calculated hash value used to simplify comparisons (as vendor MTLVertexDescriptor implementations are not all comparable).
- L23 _public member_ `NS::UInteger VertexDescHash;`
- L24 _public member_ `MTLVertexDescriptorPtr VertexDesc;`
- L27 _public prototype_ `FMetalHashedVertexDescriptor(IRVersionedInputLayoutDescriptor& Desc, uint32 Hash);`
- L28 _public member_ `IRVersionedInputLayoutDescriptor IRVertexDesc;`
- L29 _public member_ `bool bUsesIRVertexDesc = false;`
- L32 _public prototype_ `FMetalHashedVertexDescriptor();`
- L34 _public prototype_ `FMetalHashedVertexDescriptor(MTLVertexDescriptorPtr Desc, uint32 Hash);`
- L35 _public prototype_ `FMetalHashedVertexDescriptor(FMetalHashedVertexDescriptor const& Other);`
- L36 _public prototype_ `~FMetalHashedVertexDescriptor();`
- L38 _public prototype_ `FMetalHashedVertexDescriptor& operator=(FMetalHashedVertexDescriptor const& Other);`
- L39 _public prototype_ `bool operator==(FMetalHashedVertexDescriptor const& Other) const;`

#### Free symbols / members of external scopes

- L41 _function_ `friend uint32 GetTypeHash(FMetalHashedVertexDescriptor const& Hash)`

### `Source/Runtime/Apple/MetalRHI/Private/MetalLLM.h` (Private)


#### enum `ELLMTagMetal`  
`enum class ELLMTagMetal : LLM_TAG_TYPE`  
_L27-36_
- L29 _public enumerator_ `Buffers = (LLM_TAG_TYPE)ELLMTagApple::AppleMetalTagsStart`
- L30 _public enumerator_ `Textures`
- L31 _public enumerator_ `Heaps`
- L32 _public enumerator_ `RenderTargets`
- L33 _public enumerator_ `AccelerationStructures`
- L35 _public enumerator_ `Count`

#### Free symbols / members of external scopes

- L12 _typedef_ `typedef TSharedPtr<FMetalBuffer, ESPMode::ThreadSafe> FMetalBufferPtr;`
- L16 _variable_ `dispatch_block_t Block;`
- L24 _macro_ `#define LLM_SCOPE_METAL(Tag) LLM_SCOPE((ELLMTag)Tag)`
- L25 _macro_ `#define LLM_PLATFORM_SCOPE_METAL(Tag) LLM_PLATFORM_SCOPE((ELLMTag)Tag)`
- L40 _namespace_ `namespace MetalLLM`
- L42 _prototype_ `void Initialise();` (scope `MetalLLM`)
- L54 _namespace_ `namespace MetalLLM`
- L56 _prototype_ `void LogAllocTexture(MTL::Texture* Texture);` (scope `MetalLLM`)
- L57 _prototype_ `void LogFreeTexture(MTL::Texture* Texture);` (scope `MetalLLM`)
- L58 _prototype_ `void LogAllocBufferNative(MTL::Buffer* Buffer);` (scope `MetalLLM`)
- L59 _prototype_ `void LogFreeBufferNative(MTL::Buffer* Buffer);` (scope `MetalLLM`)
- L60 _prototype_ `void LogAllocHeap(MTL::Heap* Heap);` (scope `MetalLLM`)
- L62 _prototype_ `void LogAliasTexture(MTL::Texture* Texture);` (scope `MetalLLM`)
- L65 _namespace_ `namespace MetalBufferStats`
- L67 _prototype_ `void UpdateBufferStats(const FRHIBufferDesc& BufferDesc, int64 BufferSize, bool bAllocating);` (scope `MetalBufferStats`)
- L68 _prototype_ `void UpdateUniformBufferStats(int64 BufferSize, bool bAllocating);` (scope `MetalBufferStats`)

### `Source/Runtime/Apple/MetalRHI/Private/MetalPipeline.h` (Private)


#### struct `FMetalShaderResourceMask`  
`struct FMetalShaderResourceMask`  
_L29-34_
- desc: A structure for quick mask-testing of shader-stage resource bindings
- L31 _public member_ `FMetalTextureMask TextureMask;`
- L32 _public member_ `FMetalBufferMask BufferMask;`
- L33 _public member_ `FMetalSamplerMask SamplerMask;`

#### enum `EMetalShaderFrequency`  
`enum EMetalShaderFrequency`  
_L36-43_
- L38 _public enumerator_ `EMetalShaderVertex = 0`
- L39 _public enumerator_ `EMetalShaderFragment = 1`
- L40 _public enumerator_ `EMetalShaderCompute = 2`
- L41 _public enumerator_ `EMetalShaderRenderNum = 2`
- L42 _public enumerator_ `EMetalShaderStagesNum = 3`

#### enum `EMetalLimits`  
`enum EMetalLimits`  
_L45-51_
- L47 _public enumerator_ `ML_MaxSamplers = 16`
- L48 _public enumerator_ `ML_MaxBuffers = METAL_MAX_BUFFERS` — ML_MaxSamplers = 16,   Maximum number of samplers
- L49 _public enumerator_ `ML_MaxTextures = METAL_MAX_TEXTURES` — ML_MaxBuffers = METAL_MAX_BUFFERS,   Maximum number of buffers
- L50 _public enumerator_ `ML_MaxViewports = 16` — ML_MaxTextures = METAL_MAX_TEXTURES,   Maximum number of textures - there are more textures available on Mac than iOS

#### enum `EMetalPipelineHashBits`  
`enum EMetalPipelineHashBits`  
_L53-64_
- L56 _public enumerator_ `NumBits_BlendState = 8` — Blend States
- L59 _public enumerator_ `NumBits_RenderTargetFormat = 6` — Raster States
- L60 _public enumerator_ `NumBits_DepthFormat = 3` — (x1=3),
- L61 _public enumerator_ `NumBits_SampleCount = 3` — (x1=3),
- L62 _public enumerator_ `NumBits_PrimitiveTopology = 2` — (x1=2)
- L63 _public enumerator_ `NumBits_AlphaToCoverage = 1` — (x1=1)

#### enum `EMetalPipelineHashOffsets`  
`enum EMetalPipelineHashOffsets`  
_L66-91_
- L68 _public enumerator_ `Offset_BlendState0 = 0`
- L69 _public enumerator_ `Offset_BlendState1 = Offset_BlendState0 + NumBits_BlendState`
- L70 _public enumerator_ `Offset_BlendState2 = Offset_BlendState1 + NumBits_BlendState`
- L71 _public enumerator_ `Offset_BlendState3 = Offset_BlendState2 + NumBits_BlendState`
- L72 _public enumerator_ `Offset_BlendState4 = Offset_BlendState3 + NumBits_BlendState`
- L73 _public enumerator_ `Offset_BlendState5 = Offset_BlendState4 + NumBits_BlendState`
- L74 _public enumerator_ `Offset_BlendState6 = Offset_BlendState5 + NumBits_BlendState`
- L75 _public enumerator_ `Offset_BlendState7 = Offset_BlendState6 + NumBits_BlendState`
- L76 _public enumerator_ `Offset_BlendStateEnd = Offset_BlendState7 + NumBits_BlendState - 1` — 63
- L78 _public enumerator_ `Offset_RenderTargetFormat0 = 64`
- L79 _public enumerator_ `Offset_RenderTargetFormat1 = Offset_RenderTargetFormat0 + NumBits_RenderTargetFormat`
- L80 _public enumerator_ `Offset_RenderTargetFormat2 = Offset_RenderTargetFormat1 + NumBits_RenderTargetFormat`
- L81 _public enumerator_ `Offset_RenderTargetFormat3 = Offset_RenderTargetFormat2 + NumBits_RenderTargetFormat`
- L82 _public enumerator_ `Offset_RenderTargetFormat4 = Offset_RenderTargetFormat3 + NumBits_RenderTargetFormat`
- L83 _public enumerator_ `Offset_RenderTargetFormat5 = Offset_RenderTargetFormat4 + NumBits_RenderTargetFormat`
- L84 _public enumerator_ `Offset_RenderTargetFormat6 = Offset_RenderTargetFormat5 + NumBits_RenderTargetFormat`
- L85 _public enumerator_ `Offset_RenderTargetFormat7 = Offset_RenderTargetFormat6 + NumBits_RenderTargetFormat`
- L86 _public enumerator_ `Offset_DepthFormat = Offset_RenderTargetFormat7 + NumBits_RenderTargetFormat`
- L87 _public enumerator_ `Offset_SampleCount = Offset_DepthFormat + NumBits_DepthFormat`
- L88 _public enumerator_ `Offset_AlphaToCoverage = Offset_SampleCount + NumBits_SampleCount`
- L89 _public enumerator_ `Offset_PrimitiveTopology = Offset_AlphaToCoverage + NumBits_AlphaToCoverage`
- L90 _public enumerator_ `Offset_End = Offset_PrimitiveTopology + NumBits_PrimitiveTopology`

#### class `FMetalPipelineStateCacheManager`  
`class FMetalPipelineStateCacheManager`  
_L94-111_
- L97 _public prototype_ `FMetalPipelineStateCacheManager(FMetalDevice& Device);`
- L98 _public prototype_ `~FMetalPipelineStateCacheManager();`
- L101 _private member_ `FDelegateHandle ApplicationWillDeactivateDelegateHandle;`
- L102 _private member_ `FDelegateHandle ApplicationHasReactivatedDelegateHandle;`
- L103 _private member_ `FDelegateHandle OnShaderPipelineCachePreOpenDelegate;`
- L104 _private member_ `FDelegateHandle OnShaderPipelineCacheOpenedDelegate;`
- L105 _private member_ `FDelegateHandle OnShaderPipelineCachePrecompilationCompleteDelegate;`
- L108 _private prototype_ `void OnShaderPipelineCachePreOpen(FString const& Name, EShaderPlatform Platform, bool& bReady);` — Delegate handlers to track the ShaderPipelineCache precompile.
- L109 _private prototype_ `void OnShaderPipelineCacheOpened(FString const& Name, EShaderPlatform Platform, uint32 Count, const FGuid& VersionGuid, FShaderPipelineCache::FShaderCachePrecompileContext& ShaderCachePrecompileContext);`
- L110 _private prototype_ `void OnShaderPipelineCachePrecompilationComplete(uint32 Count, double Seconds, const FShaderPipelineCache::FShaderCachePrecompileContext& ShaderCachePrecompileContext);`

#### class `FMetalShaderPipeline`  
`class FMetalShaderPipeline`  
_L113-146_
- L116 _public function_ `FMetalShaderPipeline(FMetalDevice& MetalDevice) : Device(MetalDevice)`
- L118 _public prototype_ `~FMetalShaderPipeline();`
- L120 _public prototype_ `void Init();`
- L121 _public prototype_ `void InitResourceMask(const FGraphicsPipelineStateInitializer& Init);`
- L122 _public prototype_ `void InitResourceMask(const FComputePipelineStateInitializer& Init);`
- L123 _public prototype_ `void InitResourceMask(EMetalShaderFrequency Frequency, uint8 SideTableBinding);`
- L125 _public member_ `FMetalDevice& Device;`
- L126 _public member_ `MTLRenderPipelineStatePtr RenderPipelineState;`
- L127 _public member_ `MTLComputePipelineStatePtr ComputePipelineState;`
- L128 _public member_ `TArray<uint32> BufferDataSizes[EMetalShaderStagesNum];`
- L129 _public member_ `TMap<uint8, uint8> TextureTypes[EMetalShaderStagesNum];`
- L130 _public member_ `FMetalShaderResourceMask ResourceMask[EMetalShaderStagesNum];`
- L131 _public member_ `MTLRenderPipelineReflectionPtr RenderPipelineReflection;`
- L132 _public member_ `MTLComputePipelineReflectionPtr ComputePipelineReflection;`
- L134 _public member_ `NS::String* VertexSource = nullptr;`
- L135 _public member_ `NS::String* FragmentSource = nullptr;`
- L136 _public member_ `NS::String* ComputeSource = nullptr;`
- L138 _public member_ `NS::String* MeshSource = nullptr;`
- L139 _public member_ `NS::String* ObjectSource = nullptr;`
- L141 _public member_ `MTLRenderPipelineDescriptorPtr RenderDesc;`
- L142 _public member_ `MTLMeshRenderPipelineDescriptorPtr MeshRenderDesc;`
- L143 _public member_ `MTLRenderPipelineDescriptorPtr StreamDesc;`
- L144 _public member_ `MTLComputePipelineDescriptorPtr ComputeDesc;`

#### Free symbols / members of external scopes

- L14 _macro_ `#define METAL_MAX_TEXTURES 31`
- L15 _typedef_ `typedef uint32 FMetalTextureMask;`
- L17 _macro_ `#define METAL_MAX_TEXTURES 128`
- L18 _typedef_ `typedef __uint128_t FMetalTextureMask;`
- L23 _macro_ `#define METAL_MAX_BUFFERS 31`
- L25 _typedef_ `typedef uint32 FMetalBufferMask;`
- L26 _typedef_ `typedef uint16 FMetalSamplerMask;`
- L148 _prototype_ `void ShutdownPipelineCache();`
- L150 _typedef_ `typedef TSharedPtr<FMetalShaderPipeline, ESPMode::ThreadSafe> FMetalShaderPipelinePtr;`

### `Source/Runtime/Apple/MetalRHI/Private/MetalProfiler.h` (Private)


#### enum `EMetalBreadcrumbTrackerType`  
`enum class EMetalBreadcrumbTrackerType : uint8`  
_L65-71_
- L67 _public enumerator_ `Invalid = 0` — sentinel: a default-constructed tracker asserts in the resolver
- L68 _public enumerator_ `Begin`
- L69 _public enumerator_ `End`
- L70 _public enumerator_ `Encode`

#### struct `FMetalBreadcrumbInstance`  
`struct FMetalBreadcrumbInstance : public FRefCountedObject`  
_L75-84_
- inherits: `FRefCountedObject`
- L77 _public member_ `FRHIBreadcrumbNode* Node = nullptr;`
- L78 _public member_ `bool bWithinRenderPass = false;`
- L79 _public member_ `bool bTopResolved = false;`
- L80 _public member_ `uint64_t* TimestampTOP = nullptr;`
- L81 _public member_ `uint64_t* TimestampBOP = nullptr;`
- L82 _public member_ `TArray<FMetalCounterSamplePtr> Samples;`
- L83 _public member_ `FMetalCommandBuffer* BeginCmdBuffer = nullptr;`

#### struct `FMetalBreadcrumbTrackerObject`  
`struct FMetalBreadcrumbTrackerObject`  
_L86-92_
- L88 _public member_ `EMetalBreadcrumbTrackerType Type = EMetalBreadcrumbTrackerType::Invalid;`
- L89 _public member_ `FMetalCommandBuffer* CmdBuffer = nullptr;`
- L90 _public member_ `FMetalCounterSamplePtr CounterSample;`
- L91 _public member_ `TRefCountPtr<FMetalBreadcrumbInstance> Instance;` — null for Encode

#### class `FMetalBreadcrumbProfiler`  
`class FMetalBreadcrumbProfiler`  
_L94-216_
- L97 _public function_ `inline static FMetalBreadcrumbProfiler* GetInstance()`
- L106 _public function_ `~FMetalBreadcrumbProfiler()`
- L110 _public function_ `inline TRefCountPtr<FMetalBreadcrumbInstance> GetBreadcrumbEvent(FRHIBreadcrumbNode* Node, bool bWithinRenderPass)`
- L123 _public function_ `inline void AddSample(FMetalCounterSamplePtr Sample)`
- L131 _public function_ `inline void OnBreadcrumbBegin(FMetalBreadcrumbInstance* InInstance)`
- L136 _public function_ `inline void ResolveTopForCmdBuffer(FMetalCommandBuffer* CmdBuffer)`
- L168 _public function_ `inline void OnBreadcrumbEnd(FMetalBreadcrumbInstance* InInstance)`
- L207 _public prototype_ `void ResolveBreadcrumbTrackerStream(FMetalCommandBuffer* CmdBuffer);` — Resolves all the breadcrumbs added to the command buffer
- L210 _private member_ `TArray<TRefCountPtr<FMetalBreadcrumbInstance>> ActiveBreadcrumbs;`
- L212 _private member_ `TMap<FRHIBreadcrumbNode*, TRefCountPtr<FMetalBreadcrumbInstance>> CreatedBreadcrumbs;`
- L214 _private member_ `static FMetalBreadcrumbProfiler* Instance;`
- L215 _private member_ `FCriticalSection Mutex;`

#### Free symbols / members of external scopes

- L11 _delegate_ `DECLARE_DELEGATE_OneParam(FMetalCommandBufferCompletionHandler, MTL::CommandBuffer*);`
- L11 _prototype_ `DECLARE_DELEGATE_OneParam(FMetalCommandBufferCompletionHandler, MTL::CommandBuffer*);`
- L14 _delegate_ `DECLARE_CYCLE_STAT_EXTERN(TEXT("MakeDrawable time"),STAT_MetalMakeDrawableTime,STATG` — Stats
- L15 _delegate_ `DECLARE_CYCLE_STAT_EXTERN(TEXT("Draw call time"),STAT_MetalDrawCallTime,STATGROU`
- L16 _delegate_ `DECLARE_CYCLE_STAT_EXTERN(TEXT("PrepareDraw time"),STAT_MetalPrepareDrawTime,STATGR`
- L17 _delegate_ `DECLARE_CYCLE_STAT_EXTERN(TEXT("SwitchToNone time"),STAT_MetalSwitchToNoneTime,STATG`
- L18 _delegate_ `DECLARE_CYCLE_STAT_EXTERN(TEXT("SwitchToRender time"),STAT_MetalSwitchToRenderTime,STA`
- L19 _delegate_ `DECLARE_CYCLE_STAT_EXTERN(TEXT("SwitchToCompute time"),STAT_MetalSwitchToComputeTime,ST`
- L20 _delegate_ `DECLARE_CYCLE_STAT_EXTERN(TEXT("SwitchToBlit time"),STAT_MetalSwitchToBlitTime,STATG`
- L21 _delegate_ `DECLARE_CYCLE_STAT_EXTERN(TEXT("PrepareToRender time"),STAT_MetalPrepareToRenderTime,ST`
- L22 _delegate_ `DECLARE_CYCLE_STAT_EXTERN(TEXT("PrepareToDispatch time"),STAT_MetalPrepareToDispatchTime,`
- L23 _delegate_ `DECLARE_CYCLE_STAT_EXTERN(TEXT("CommitRenderResourceTables time"),STAT_MetalCommitRenderResourceTa`
- L24 _delegate_ `DECLARE_CYCLE_STAT_EXTERN(TEXT("SetRenderState time"),STAT_MetalSetRenderStateTime,STA`
- L25 _delegate_ `DECLARE_CYCLE_STAT_EXTERN(TEXT("SetRenderPipelineState time"),STAT_MetalSetRenderPipelineState`
- L26 _delegate_ `DECLARE_CYCLE_STAT_EXTERN(TEXT("PipelineState time"),STAT_MetalPipelineStateTime,STAT`
- L27 _delegate_ `DECLARE_CYCLE_STAT_EXTERN(TEXT("Buffer Page-Off time"), STAT_MetalBufferPageOffTime, ST`
- L28 _delegate_ `DECLARE_CYCLE_STAT_EXTERN(TEXT("Texture Page-Off time"), STAT_MetalTexturePageOffTime, S`
- L30 _delegate_ `DECLARE_DWORD_COUNTER_STAT_EXTERN(TEXT("Uniform Memory Allocated Per-Frame"), STAT_MetalUnifo`
- L31 _delegate_ `DECLARE_DWORD_COUNTER_STAT_EXTERN(TEXT("Uniform Memory Freed Per-Frame"), STAT_MetalUniformMe`
- L32 _delegate_ `DECLARE_DWORD_COUNTER_STAT_EXTERN(TEXT("Vertex Memory Allocated Per-Frame"), STAT_MetalVerte`
- L33 _delegate_ `DECLARE_DWORD_COUNTER_STAT_EXTERN(TEXT("Vertex Memory Freed Per-Frame"), STAT_MetalVertexMem`
- L34 _delegate_ `DECLARE_DWORD_COUNTER_STAT_EXTERN(TEXT("Index Memory Allocated Per-Frame"), STAT_MetalIndex`
- L35 _delegate_ `DECLARE_DWORD_COUNTER_STAT_EXTERN(TEXT("Index Memory Freed Per-Frame"), STAT_MetalIndexMemF`
- L36 _delegate_ `DECLARE_DWORD_COUNTER_STAT_EXTERN(TEXT("Texture Memory Updated Per-Frame"), STAT_MetalTextureM`
- L37 _delegate_ `DECLARE_MEMORY_STAT_EXTERN(TEXT("Buffer Memory"), STAT_MetalBufferMemory, STATGROUP`
- L38 _delegate_ `DECLARE_MEMORY_STAT_EXTERN(TEXT("Texture Memory"), STAT_MetalTextureMemory, STATGROU`
- L39 _delegate_ `DECLARE_MEMORY_STAT_EXTERN(TEXT("Heap Memory"), STAT_MetalHeapMemory, STATGROUP_M`
- L40 _delegate_ `DECLARE_MEMORY_STAT_EXTERN(TEXT("Unused Buffer Memory"), STAT_MetalBufferUnusedMemory, ST`
- L41 _delegate_ `DECLARE_MEMORY_STAT_EXTERN(TEXT("Unused Texture Memory"), STAT_MetalTextureUnusedMemory, S`
- L43 _delegate_ `DECLARE_MEMORY_STAT_EXTERN(TEXT("Uniform Memory In Flight"), STAT_MetalUniformMemoryInFlight`
- L44 _delegate_ `DECLARE_MEMORY_STAT_EXTERN(TEXT("Allocated Uniform Pool Memory"), STAT_MetalUniformAllocatedM`
- L45 _delegate_ `DECLARE_MEMORY_STAT_EXTERN(TEXT("Uniform Memory Per Frame"), STAT_MetalUniformBytesPerFrame`
- L47 _delegate_ `DECLARE_MEMORY_STAT_EXTERN(TEXT("Allocated Frame Temp Memory"), STAT_MetalTempAllocatorAllocatedMem`
- L49 _delegate_ `DECLARE_DWORD_ACCUMULATOR_STAT_EXTERN(TEXT("Buffer Count"), STAT_MetalBufferCount, STATGROUP_`
- L50 _delegate_ `DECLARE_DWORD_ACCUMULATOR_STAT_EXTERN(TEXT("Texture Count"), STAT_MetalTextureCount, STATGROUP`
- L51 _delegate_ `DECLARE_DWORD_ACCUMULATOR_STAT_EXTERN(TEXT("Heap Count"), STAT_MetalHeapCount, STATGROUP_Me`
- L52 _delegate_ `DECLARE_DWORD_ACCUMULATOR_STAT_EXTERN(TEXT("Fence Count"), STAT_MetalFenceCount, STATGROUP_M`
- L54 _delegate_ `DECLARE_CYCLE_STAT_EXTERN(TEXT("Texture Page-On time"), STAT_MetalTexturePageOnTime, ST`
- L55 _delegate_ `DECLARE_CYCLE_STAT_EXTERN(TEXT("CustomPresent time"), STAT_MetalCustomPresentTime, STAT`
- L57 _delegate_ `DECLARE_DWORD_COUNTER_STAT_EXTERN(TEXT("Number Command Buffers Created Per-Frame"), STAT_MetalCommandBuffe`
- L58 _delegate_ `DECLARE_DWORD_COUNTER_STAT_EXTERN(TEXT("Number Command Buffers Committed Per-Frame"), STAT_MetalCommandBuffe`

### `Source/Runtime/Apple/MetalRHI/Private/MetalRHIPrivate.h` (Private)


#### enum `EMTLTextureType`  
`enum EMTLTextureType`  
_L88-91_
- desc: Unavailable on iOS, but dealing with this clutters the code.
- L90 _public enumerator_ `EMTLTextureTypeCubeArray = 6`

#### struct `FMetalBufferFormat`  
`struct FMetalBufferFormat`  
_L101-107_
- L104 _public member_ `MTL::PixelFormat LinearTextureFormat;` — Valid linear texture pixel formats - potentially different than the actual texture formats
- L106 _public member_ `uint8 DataFormat;` — Metal buffer data types for manual ALU format conversions

#### struct `TMetalResourceTraits`  
`template<class T> struct TMetalResourceTraits`  
_L195-197_

#### enum `EMetalShaderStages`  
`enum EMetalShaderStages`  
_L225-239_
- desc: Needs to be the same as EShaderFrequency when all stages are supported, but unlike EShaderFrequency you can compile out stages.
- L227 _public enumerator_ `Vertex`
- L228 _public enumerator_ `Pixel`
- L230 _public enumerator_ `Geometry`
- L233 _public enumerator_ `Mesh`
- L234 _public enumerator_ `Amplification`
- L236 _public enumerator_ `Compute`
- L238 _public enumerator_ `Num`

#### Free symbols / members of external scopes

- L18 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogMetal, Display, All);`
- L18 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogMetal, Display, All);`
- L20 _delegate_ `DECLARE_DELEGATE_OneParam(FMetalCommandBufferCompletionHandler, MTL::CommandBuffer*);`
- L20 _prototype_ `DECLARE_DELEGATE_OneParam(FMetalCommandBufferCompletionHandler, MTL::CommandBuffer*);`
- L23 _externvar_ `extern bool GIsMetalInitialized;` — Whether the Metal RHI is initialized sufficiently to handle resources
- L27 _variable_ `const uint32 BufferOffsetAlignment = 256;`
- L28 _variable_ `const uint32 BufferBackedLinearTextureOffsetAlignment = 1024;`
- L30 _variable_ `const uint32 BufferOffsetAlignment = 16;`
- L31 _variable_ `const uint32 BufferBackedLinearTextureOffsetAlignment = 64;`
- L35 _variable_ `const uint32 MetalBufferPageSize = 4096;` — The maximum buffer page size that can be uploaded in a set*Bytes call
- L39 _variable_ `const uint32 MetalBufferBytesSize = BufferOffsetAlignment * 2;`
- L41 _variable_ `const uint32 MetalBufferBytesSize = BufferOffsetAlignment * 32;`
- L45 _macro_ `#define METAL_USE_METAL_SHADER_CONVERTER 0`
- L48 _macro_ `#define METAL_RHI_RAYTRACING (METAL_USE_METAL_SHADER_CONVERTER)`
- L54 _macro_ `#define IR_RUNTIME_METALCPP 1`
- L58 _variable_ `constexpr uint64_t kIRStandardHeapBindPoint = 0;`
- L62 _macro_ `#define BUFFER_CACHE_MODE MTL::ResourceCPUCacheModeDefaultCache`
- L65 _macro_ `#define BUFFER_MANAGED_MEM MTL::ResourceStorageModeManaged`
- L66 _macro_ `#define BUFFER_STORAGE_MODE MTL::StorageModeShared`
- L67 _macro_ `#define BUFFER_RESOURCE_STORAGE_MANAGED MTL::ResourceStorageModeManaged`
- L68 _macro_ `#define BUFFER_DYNAMIC_REALLOC BUF_AnyDynamic`
- L70 _variable_ `const uint32 MaxMetalStreams = 31;` — How many possible vertex streams are allowed
- L72 _macro_ `#define BUFFER_MANAGED_MEM 0`
- L75 _macro_ `#define BUFFER_STORAGE_MODE MTL::StorageModePrivate`
- L76 _macro_ `#define BUFFER_RESOURCE_STORAGE_MANAGED MTL::ResourceStorageModePrivate`
- L79 _macro_ `#define BUFFER_RESOURCE_STORAGE_MANAGED MTL::ResourceStorageModeShared`
- L84 _variable_ `const uint32 MaxMetalStreams = 30;` — How many possible vertex streams are allowed
- L94 _macro_ `#define METAL_SUPPORTS_INDIRECT_ARGUMENT_BUFFERS 1` — This is the right VERSION check, see Availability.h in the SDK
- L95 _macro_ `#define METAL_SUPPORTS_CAPTURE_MANAGER 1`
- L96 _macro_ `#define METAL_SUPPORTS_TILE_SHADERS 1`
- L99 _externvar_ `extern bool GMetalSupportsCaptureManager;` — In addition to compile-time SDK checks we also need a way to check if these are available on runtime
- L109 _externvar_ `extern FMetalBufferFormat GMetalBufferFormats[PF_MAX];`
- L111 _macro_ `#define METAL_DEBUG_OPTIONS !(UE_BUILD_SHIPPING || UE_BUILD_TEST)`
- L113 _macro_ `#define METAL_DEBUG_OPTION(Code) Code`
- L115 _macro_ `#define METAL_DEBUG_OPTION(Code)`
- L118 _externvar_ `extern bool GMetalCommandBufferDebuggingEnabled;`
- L122 _macro_ `#define ENABLE_METAL_GPUEVENTS_IN_TEST 0`
- L124 _macro_ `#define ENABLE_METAL_GPUEVENTS (UE_BUILD_DEBUG || UE_BUILD_DEVELOPMENT || (UE_BUILD_TEST && ENABLE_METAL_GPUEVENTS_IN_TEST))`
- L125 _macro_ `#define ENABLE_METAL_GPUPROFILE (ENABLE_METAL_GPUEVENTS && 1)`
- L127 _macro_ `#define UNREAL_TO_METAL_BUFFER_INDEX(Index) ((MaxMetalStreams - 1) - Index)`
- L128 _macro_ `#define METAL_TO_UNREAL_BUFFER_INDEX(Index) ((MaxMetalStreams - 1) - Index)`
- L130 _macro_ `#define METAL_NEW_NONNULL_DECL (__clang_major__ >= 9)`
- L133 _macro_ `#define METAL_FATAL_ERROR(Format, ...) { UE_LOG(LogMetal, Warning, Format, __VA_ARGS__); FIOSPlatformMisc::MetalAssert(); }`
- L135 _macro_ `#define METAL_FATAL_ERROR(Format, ...) UE_LOG(LogMetal, Fatal, Format, __VA_ARGS__)`
- L137 _macro_ `#define METAL_FATAL_ASSERT(Condition, Format, ...) if (!(Condition)) { METAL_FATAL_ERROR(Format, __VA_ARGS__); }`
- L140 _macro_ `#define METAL_IGNORED(Func)`
- L143 _function_ `FORCEINLINE bool IsMetalBindlessEnabled()`
- L149 _prototype_ `FMetalSurface* GetMetalSurfaceFromRHITexture(FRHITexture* Texture);` — Access the underlying surface object from any kind of texture
- L151 _macro_ `#define NOT_SUPPORTED(Func) UE_LOGF(LogMetal, Fatal, "'%ls' is not supported", TEXT(Func));`
- L153 _function_ `FORCEINLINE bool MetalIsSafeToUseRHIThreadResources()`
- L161 _function_ `FORCEINLINE int32 GetMetalCubeFace(ECubeFace Face)`
- L176 _function_ `FORCEINLINE MTL::LoadAction GetMetalRTLoadAction(ERenderTargetLoadAction LoadAction)`
- L187 _prototype_ `MTL::PrimitiveType TranslatePrimitiveType(uint32 PrimitiveType);`
- L188 _prototype_ `MTL::PrimitiveTopologyClass TranslatePrimitiveTopology(uint32 PrimitiveType);`
- L190 _prototype_ `MTL::PixelFormat UEToMetalFormat(FMetalDevice& Device, EPixelFormat UEFormat, bool bSRGB);`
- L192 _prototype_ `uint8 GetMetalPixelFormatKey(MTL::PixelFormat Format);`
- L200 _function_ `template<typename TRHIType> static FORCEINLINE typename TMetalResourceTraits<TRHIType>::TConcreteType* ResourceCast(TRHIType* Resource)`
- L206 _function_ `template<typename TRHIType> static FORCEINLINE const typename TMetalResourceTraits<TRHIType>::TConcreteType* ResourceCast(const TRHIType* Resource)`
- L211 _function_ `static FORCEINLINE FMetalSurface* ResourceCast(FRHITexture* Texture)`
- L216 _function_ `static FORCEINLINE const FMetalSurface* ResourceCast(const FRHITexture* Texture)`
- L222 _prototype_ `MTL::LanguageVersion ValidateVersion(uint32 Version);`
- L241 _function_ `FORCEINLINE EShaderFrequency GetRHIShaderFrequency(EMetalShaderStages Stage)`
- L266 _function_ `FORCEINLINE EMetalShaderStages GetMetalShaderFrequency(EShaderFrequency Stage)`
- L291 _function_ `FORCEINLINE FString NSStringToFString(NS::String* InputString)`
- L296 _function_ `FORCEINLINE NS::String* FStringToNSString(const FString& InputString)`
- L302 _prototype_ `bool ShouldUseMemoryless(ETextureCreateFlags Flags);` — helper functions to reduce copy and pasted checks all around
- L303 _prototype_ `bool AllowMSAA();`

### `Source/Runtime/Apple/MetalRHI/Private/MetalRHIRenderQuery.h` (Private)


#### class `FMetalQueryBuffer`  
`class FMetalQueryBuffer : public FRefCountedObject`  
_L30-41_
- inherits: `FRefCountedObject`
- L33 _public prototype_ `FMetalQueryBuffer(FMetalQueryBufferPool* Pool, FMetalBufferPtr InBuffer);`
- L34 _public prototype_ `virtual ~FMetalQueryBuffer();`
- L36 _public prototype_ `uint64 GetResult(uint32 Offset);`
- L38 _public member_ `FMetalQueryBufferPool* Pool = nullptr;`
- L39 _public member_ `FMetalBufferPtr Buffer;`
- L40 _public member_ `uint32 WriteOffset;`

#### class `FMetalQueryBufferPool`  
`class FMetalQueryBufferPool`  
_L50-77_
- L60 _public prototype_ `FMetalQueryBufferPool() = delete;` — Disallow a default constructor
- L62 _public prototype_ `FMetalQueryBufferPool(FMetalDevice& InDevice);`
- L63 _public prototype_ `~FMetalQueryBufferPool();`
- L65 _public prototype_ `void Allocate(FMetalQueryResult& NewQuery);`
- L67 _public prototype_ `FMetalQueryBufferRef AcquireQueryBuffer(uint32_t NumOcclusionQueries);`
- L68 _public prototype_ `FMetalQueryBufferRef GetCurrentQueryBuffer();`
- L69 _public prototype_ `void ReleaseCurrentQueryBuffer();`
- L70 _public prototype_ `void ReleaseQueryBuffer(FMetalBufferPtr Buffer);`
- L72 _public member_ `uint32_t BufferSize = 0;`
- L74 _public member_ `FMetalQueryBufferRef CurrentBuffer;`
- L75 _public member_ `TArray<FMetalBufferPtr> Buffers;`
- L76 _public member_ `FMetalDevice& Device;`

#### enum `FMetalQueryBufferPool::(anonymous)`  
``  
_L54-57_

#### class `FMetalQueryResult`  
`class FMetalQueryResult`  
_L85-98_
- L88 _public prototype_ `FMetalQueryResult() = default;`
- L89 _public prototype_ `~FMetalQueryResult() = default;`
- L91 _public prototype_ `void Reset();`
- L92 _public prototype_ `uint64 GetResult();`
- L94 _public member_ `FMetalQueryBufferRef SourceBuffer = nullptr;`
- L95 _public member_ `uint32 Offset = 0;`
- L96 _public member_ `bool bCompleted = false;`
- L97 _public member_ `bool bBatchFence = false;`

#### class `FMetalRHIRenderQuery`  
`class FMetalRHIRenderQuery : public FRHIRenderQuery`  
_L105-155_
- inherits: `FRHIRenderQuery`
- L109 _public prototype_ `FMetalRHIRenderQuery(FMetalDevice& MetalDevice, ERenderQueryType InQueryType);`
- L110 _public prototype_ `virtual ~FMetalRHIRenderQuery();`
- L112 _public prototype_ `void Begin_TopOfPipe();`
- L113 _public prototype_ `void End_TopOfPipe();`
- L118 _public prototype_ `void Begin(FMetalRHICommandContext* Context);` — Kick off an occlusion test
- L123 _public prototype_ `void End(FMetalRHICommandContext* Context);` — Finish up an occlusion test
- L128 _public prototype_ `void SampleOcclusionResult();` — Samples the occlusion result on the submission thread
- L133 _public prototype_ `bool GetResult(uint64& OutNumPixels, bool bWait, uint32 GPUIndex);` — Get the query result
- L136 _private member_ `FMetalDevice& Device;`
- L139 _private member_ `ERenderQueryType Type;` — The type of query
- L142 _private member_ `FMetalQueryResult Buffer;` — Query buffer allocation details as the buffer is already set on the command-encoder
- L145 _private member_ `volatile uint64 Result;` — Query result.
- L148 _private member_ `std::atomic<bool> bAvailable;` — Result availability - if not set the first call to acquire it will read the buffer & cache
- L151 _private member_ `FMetalSyncPointRef SyncPoint;` — Signaled when the result is available. Nullptr if the query has never been used.
- L154 _private member_ `FMetalCommandBuffer* CommandBuffer = nullptr;` — Temporary

#### Free symbols / members of external scopes

- L23 _typedef_ `typedef TSharedPtr<FMetalBuffer, ESPMode::ThreadSafe> FMetalBufferPtr;`
- L43 _typedef_ `typedef TRefCountPtr<FMetalQueryBuffer> FMetalQueryBufferRef;`
- L55 _enumerator_ `EQueryBufferAlignment = 8` (scope `FMetalQueryBufferPool::__anon310adffb0103`)
- L56 _enumerator_ `EQueryResultMaxSize = 8` (scope `FMetalQueryBufferPool::__anon310adffb0103`)

### `Source/Runtime/Apple/MetalRHI/Private/MetalRHIStagingBuffer.h` (Private)


#### class `FMetalRHIStagingBuffer`  
`class FMetalRHIStagingBuffer final : public FRHIStagingBuffer`  
_L15-38_
- inherits: `FRHIStagingBuffer`
- L20 _public prototype_ `FMetalRHIStagingBuffer(FMetalDevice& Device);`
- L21 _public prototype_ `virtual ~FMetalRHIStagingBuffer() final override;`
- L29 _public prototype_ `virtual void* Lock(uint32 Offset, uint32 NumBytes) final override;` — Returns the pointer to read the buffer. There is no actual locking, the buffer is always shared.  If this is not fenced correctly, it will not have the expected data.
- L31 _public prototype_ `virtual void Unlock() final override;`
- L33 _public prototype_ `uint64 GetGPUSizeBytes() const override;`
- L36 _private member_ `FMetalDevice& Device;`
- L37 _private member_ `FMetalBufferPtr ShadowBuffer = nullptr;`

#### Free symbols / members of external scopes

- L13 _typedef_ `typedef TSharedPtr<FMetalBuffer, ESPMode::ThreadSafe> FMetalBufferPtr;`

### `Source/Runtime/Apple/MetalRHI/Private/MetalRayTracing.h` (Private)


#### struct `FMetalHitGroupSystemParameters`  
`struct FMetalHitGroupSystemParameters`  
_L15-21_
- L17 _public member_ `FHitGroupSystemRootConstants RootConstants;`
- L19 _public member_ `uint32 BindlessHitGroupSystemIndexBuffer;`
- L20 _public member_ `uint32 BindlessHitGroupSystemVertexBuffer;`

#### class `FMetalRayTracingGeometry`  
`class FMetalRayTracingGeometry : public FRHIRayTracingGeometry`  
_L23-78_
- inherits: `FRHIRayTracingGeometry`
- L26 _public prototype_ `FMetalRayTracingGeometry(FMetalDevice& InDevice, FRHICommandListBase& RHICmdList, const FRayTracingGeometryInitializer& InInitializer);`
- L27 _public prototype_ `~FMetalRayTracingGeometry();`
- L29 _public prototype_ `void ReleaseUnderlyingResource();`
- L30 _public prototype_ `void ReleaseDescriptors();`
- L32 _public prototype_ `uint64 GetGPUAddress() const;`
- L36 _public function_ `virtual FRayTracingAccelerationStructureAddress GetAccelerationStructureAddress(uint64 GPUIndex) const final override` — FRHIRayTracingGeometry Interface
- L40 _public prototype_ `void Swap(FMetalRayTracingGeometry& Other);`
- L41 _public prototype_ `void RebuildDescriptors();`
- L43 _public prototype_ `void RemoveCompactionRequest();`
- L48 _public member_ `MTL::PrimitiveAccelerationStructureDescriptor* AccelerationStructureDescriptor = nullptr;`
- L50 _public member_ `bool bHasPendingCompactionRequests;`
- L51 _public member_ `uint32 CompactionSizeIndex;`
- L53 _public member_ `static constexpr uint32 IndicesPerPrimitive = 3;` — Triangle geometry only
- L55 _public function_ `inline FMetalAccelerationStructure* GetAccelerationStructure() const`
- L60 _public prototype_ `void SetAccelerationStructure(FMetalAccelerationStructure* InBuffer);`
- L61 _public prototype_ `void SetupHitGroupSystemParameters();`
- L62 _public prototype_ `void ReleaseBindlessHandles();`
- L64 _public member_ `TArray<FMetalHitGroupSystemParameters> HitGroupSystemParameters;`
- L67 _private member_ `FMetalDevice& Device;`
- L69 _private member_ `TArray<MTL::AccelerationStructureTriangleGeometryDescriptor*> GeomArray;`
- L71 _private member_ `uint32 AccelerationStructureIndex;`
- L72 _private member_ `FMetalAccelerationStructure* AccelerationStructure = nullptr;`
- L74 _private member_ `TArray<FRHIDescriptorHandle> HitGroupSystemVertexViews;`
- L75 _private member_ `FRHIDescriptorHandle HitGroupSystemIndexView;`
- L77 _private member_ `NS::Array* GeometryDescriptors = nullptr;`

#### class `FMetalRayTracingScene`  
`class FMetalRayTracingScene : public FRHIRayTracingScene`  
_L80-118_
- inherits: `FRHIRayTracingScene`
- L83 _public prototype_ `FMetalRayTracingScene(FMetalDevice& InDevice, FRayTracingSceneInitializer InInitializer);`
- L84 _public prototype_ `virtual ~FMetalRayTracingScene();`
- L86 _public prototype_ `void BindBuffer(FRHIBuffer* InBuffer, uint32 InBufferOffset);`
- L87 _public prototype_ `void BuildAccelerationStructure( FMetalRHICommandContext& CommandContext, FMetalRHIBuffer* ScratchBuffer, uint32 ScratchOffset, FMetalRHIBuffer* InstanceBuffer, uint32 InstanceOffset, FMetalRHIBuffer* HitGroupContributionsBuffer, uint32 HitGroupContributionsBufferOffset, uint32 NumInstances);`
- L94 _public function_ `inline const FRayTracingSceneInitializer& GetInitializer() const override final`
- L101 _public function_ `FMetalAccelerationStructure* GetAccelerationStructure()`
- L111 _private member_ `FMetalDevice& Device;`
- L114 _private member_ `const FRayTracingSceneInitializer Initializer;` — The initializer provided to build the scene. Contains all the free standing stuff that used to be owned by the RT implementation.
- L117 _private member_ `FMetalRHIBuffer* AccelerationStructureBuffer;` — Acceleration Structure for the whole scene.

### `Source/Runtime/Apple/MetalRHI/Private/MetalResourceCollection.h` (Private)


#### struct `TMetalResourceTraits`  
`template<> struct TMetalResourceTraits<FRHIResourceCollection>`  
_L13-16_
- L15 _public typedef_ `using TConcreteType = FMetalResourceCollection;`

#### Free symbols / members of external scopes

- L10 _typedef_ `using FMetalResourceCollection = UE::RHICore::FGenericResourceCollection;`

### `Source/Runtime/Apple/MetalRHI/Private/MetalShaderTypes.h` (Private)
_(no declarations extracted)_

### `Source/Runtime/Apple/MetalRHI/Private/MetalStateCache.h` (Private)


#### enum `EMetalPipelineFlags`  
`enum EMetalPipelineFlags`  
_L18-25_
- L20 _public enumerator_ `EMetalPipelineFlagPipelineState = 1 << 0`
- L21 _public enumerator_ `EMetalPipelineFlagComputeShader = 1 << 5`
- L22 _public enumerator_ `EMetalPipelineFlagRasterMask = 0xF`
- L23 _public enumerator_ `EMetalPipelineFlagComputeMask = 0x30`
- L24 _public enumerator_ `EMetalPipelineFlagMask = 0x3F`

#### enum `EMetalRenderFlags`  
`enum EMetalRenderFlags`  
_L27-41_
- L29 _public enumerator_ `EMetalRenderFlagViewport = 1 << 0`
- L30 _public enumerator_ `EMetalRenderFlagFrontFacingWinding = 1 << 1`
- L31 _public enumerator_ `EMetalRenderFlagCullMode = 1 << 2`
- L32 _public enumerator_ `EMetalRenderFlagDepthBias = 1 << 3`
- L33 _public enumerator_ `EMetalRenderFlagScissorRect = 1 << 4`
- L34 _public enumerator_ `EMetalRenderFlagTriangleFillMode = 1 << 5`
- L35 _public enumerator_ `EMetalRenderFlagBlendColor = 1 << 6`
- L36 _public enumerator_ `EMetalRenderFlagDepthStencilState = 1 << 7`
- L37 _public enumerator_ `EMetalRenderFlagStencilReferenceValue = 1 << 8`
- L38 _public enumerator_ `EMetalRenderFlagVisibilityResultMode = 1 << 9`
- L39 _public enumerator_ `EMetalRenderFlagDepthClipMode = 1 << 10`
- L40 _public enumerator_ `EMetalRenderFlagMask = 0x3FF`

#### class `FMetalStateCache`  
`class FMetalStateCache`  
_L44-363_
- L47 _public prototype_ `FMetalStateCache(FMetalDevice& Device);`
- L48 _public prototype_ `~FMetalStateCache();`
- L51 _public prototype_ `void Reset();` — Reset cached state for reuse
- L54 _public prototype_ `void ResetBindings();` — Reset bindings between encoders
- L56 _public prototype_ `void SetScissorRect(bool const bEnable, MTL::ScissorRect const& Rect);`
- L57 _public prototype_ `void SetBlendFactor(FLinearColor const& InBlendFactor);`
- L58 _public prototype_ `void SetStencilRef(uint32 const InStencilRef);`
- L59 _public prototype_ `void SetComputeShader(FMetalComputeShader* InComputeShader);`
- L60 _public prototype_ `bool SetRenderPassInfo(FRHIRenderPassInfo const& InRenderTargets, FMetalQueryBufferRef QueryBuffer);`
- L61 _public prototype_ `void InvalidateRenderTargets(void);`
- L62 _public prototype_ `void SetRenderTargetsActive(bool const bActive);`
- L63 _public prototype_ `void SetViewport(const MTL::Viewport& InViewport);`
- L64 _public prototype_ `void SetViewports(const MTL::Viewport InViewport[], uint32 Count);`
- L65 _public prototype_ `void SetVertexStream(uint32 const Index, FMetalBufferPtr Buffer, FMetalBufferData* Bytes, uint32 const Offset, uint32 const Length);`
- L66 _public prototype_ `void SetGraphicsPipelineState(FMetalGraphicsPipelineState* State);`
- L67 _public prototype_ `void BindUniformBuffer(EMetalShaderStages const Freq, uint32 const BufferIndex, FRHIUniformBuffer* BufferRHI);`
- L74 _public prototype_ `void SetVisibilityResultMode(MTL::VisibilityResultMode const Mode, NS::UInteger const Offset);` — Monitor if samples pass the depth and stencil tests. @param Mode Controls if the counter is disabled or moniters passing samples. @param Offset The offset relative to the occlusion query buffer provided when the command encoder was created.  offset must be a multiple of 8.
- L89 _public prototype_ `void SetShaderBuffer( EMetalShaderStages const Frequency , FMetalBufferPtr Buffer , FMetalBufferData* const Bytes , NS::UInteger const Offset , NS::UInteger const Length , NS::UInteger const Index , MTL::ResourceUsage const Usage , EPixelFormat const Format = PF_Unknown , NS::UInteger const ElementRowPitch = 0 , TArray<TTuple<MTL::Resource*, MTL::ResourceUsage>> ReferencedResources = {} );` — Set a global buffer for the specified shader frequency at the given bind point index. @param Frequency The shader frequency to modify. @param Buffer The buffer to bind or nullptr to clear. @param Bytes The FMetalBufferData to bind or nullptr to clear. @param Offset The offset in the buffer or 0 when Buffer is nullptr. @param Offset The length of data (caller accounts for Offset) in the buffer or 0 when Buffer is nullptr. @param Index The index to modify. @param Usage The resource usage flags. @param Format The UAV pixel format. @param ReferencedResources The resources indirectly used by the bound buffer.
- L110 _public prototype_ `void SetShaderBuffer(EMetalShaderStages const Frequency, FMetalAccelerationStructure* AccelerationStructure, NS::UInteger const Index, TArray<TTuple<MTL::Resource*, MTL::ResourceUsage>> BLAS);` — Set a global acceleration structure for the specified shader frequency at the given bind point index. @param Frequency The shader frequency to modify. @param AccelerationStructure The acceleration structure to bind or nullptr to clear. @param Index The index to modify. @param BLAS The resources indirectly used by the bound buffer.
- L114 _public prototype_ `void CacheHeapResidency(MTL::Heap* InHeap, EMetalShaderStages const Frequency);`
- L115 _public prototype_ `void CacheOrSkipResourceResidencyUpdate(MTL::Resource* InResource, EMetalShaderStages const Frequency, bool bReadOnly, bool bForceUseResource = false);`
- L117 _public prototype_ `void IRMakeSRVResident(EMetalShaderStages const Frequency, FMetalShaderResourceView* SRV);`
- L118 _public prototype_ `void IRMakeUAVResident(EMetalShaderStages const Frequency, FMetalUnorderedAccessView* UAV);`
- L119 _public prototype_ `void IRMakeTextureResident(EMetalShaderStages const Frequency, MTL::Texture* Texture);`
- L121 _public prototype_ `void IRBindUniformBuffer(EMetalShaderStages const Frequency, int32 Index, FMetalUniformBuffer* UB);`
- L122 _public prototype_ `void IRBindPackedUniforms(EMetalShaderStages const Frequency, int32 Index, uint8 const* Bytes, const uint32 Size, FMetalBufferPtr& Buffer);`
- L129 _public prototype_ `FMetalBufferPtr IRSideUploadToBuffer(void const* Content, uint64 Size);` — Write GPU data to ring buffer on CPU, returns GPU address of data written @param Content Data to upload @param Size Size in bytes
- L132 _public prototype_ `template<EMetalShaderStages Frequency, MTL::FunctionType FunctionType> void FlushUsedResources(FMetalCommandEncoder* Encoder);`
- L135 _public prototype_ `template<class ShaderType, EMetalShaderStages Frequency, MTL::FunctionType FunctionType> void IRBindResourcesToEncoder(ShaderType Shader, FMetalCommandEncoder* Encoder);`
- L137 _public prototype_ `void IRMapVertexBuffers(MTL::RenderCommandEncoder* Encoder, bool bBindForMeshShaders = false);`
- L147 _public prototype_ `void SetShaderTexture(EMetalShaderStages const Frequency, MTL::Texture* Texture, NS::UInteger const Index, MTL::ResourceUsage const Usage);` — Set a global texture for the specified shader frequency at the given bind point index. @param Frequency The shader frequency to modify. @param Texture The texture to bind or nullptr to clear. @param Index The index to modify. @param Usage The resource usage flags.
- L155 _public prototype_ `void SetShaderSamplerState(EMetalShaderStages const Frequency, FMetalSamplerState* const Sampler, NS::UInteger const Index);` — Set a global sampler for the specified shader frequency at the given bind point index. @param Frequency The shader frequency to modify. @param Sampler The sampler state to bind or nullptr to clear. @param Index The index to modify.
- L157 _public prototype_ `void SetShaderResourceView(EMetalShaderStages ShaderStage, uint32 BindIndex, FMetalShaderResourceView* SRV);`
- L158 _public prototype_ `void SetShaderUnorderedAccessView(EMetalShaderStages ShaderStage, uint32 BindIndex, FMetalUnorderedAccessView* UAV);`
- L159 _public prototype_ `void SetStateDirty(void);`
- L160 _public prototype_ `void SetShaderBufferDirty(EMetalShaderStages const Frequency, NS::UInteger const Index);`
- L161 _public prototype_ `void SetRenderStoreActions(FMetalCommandEncoder& CommandEncoder, bool const bConditionalSwitch = false);`
- L162 _public prototype_ `void SetRenderState(FMetalCommandEncoder& CommandEncoder);`
- L164 _public prototype_ `void CommitRenderResources(FMetalCommandEncoder* Raster);`
- L165 _public prototype_ `void CommitComputeResources(FMetalCommandEncoder* Compute);`
- L167 _public prototype_ `void CommitResourceTable(EMetalShaderStages const Frequency, MTL::FunctionType const Type, FMetalCommandEncoder& CommandEncoder);`
- L168 _public prototype_ `void StartRenderPass(const FRHIRenderPassInfo& Info, FMetalQueryBufferRef QueryBuffer, MTL::RenderPassDescriptor* InDesc, bool bInIsParallelContext);`
- L169 _public prototype_ `void EndRenderPass();`
- L171 _public function_ `FMetalShaderParameterCache& GetShaderParameters(EMetalShaderStages const Stage)`
- L172 _public function_ `FLinearColor const& GetBlendFactor() const`
- L173 _public function_ `uint32 GetStencilRef() const`
- L174 _public function_ `FMetalDepthStencilState* GetDepthStencilState() const`
- L175 _public function_ `FMetalRasterizerState* GetRasterizerState() const`
- L176 _public function_ `FMetalGraphicsPipelineState* GetGraphicsPSO() const`
- L177 _public function_ `FMetalComputeShader* GetComputeShader() const`
- L178 _public function_ `CGSize GetFrameBufferSize() const`
- L179 _public function_ `FRHIRenderPassInfo const& GetRenderPassInfo() const`
- L180 _public function_ `int32 GetNumRenderTargets()`
- L181 _public function_ `bool GetHasValidRenderTarget() const`
- L182 _public function_ `bool GetHasValidColorTarget() const`
- L183 _public function_ `const MTL::Viewport& GetViewport(uint32 const Index) const`
- L184 _public prototype_ `uint32 GetVertexBufferSize(uint32 const Index);`
- L185 _public function_ `uint32 GetRenderTargetArraySize() const`
- L186 _public function_ `FMetalQueryBufferRef GetVisibilityResultsBuffer() const`
- L187 _public prototype_ `bool NeedsToSetRenderTarget(const FRHIRenderPassInfo& RenderPassInfo);`
- L188 _public function_ `bool HasValidDepthStencilSurface() const`
- L190 _public function_ `MTL::RenderPassDescriptor* GetRenderPassDescriptor(void) const`
- L192 _public function_ `uint32 GetSampleCount(void) const`
- L193 _public prototype_ `FMetalShaderPipeline* GetPipelineState() const;`
- L194 _public prototype_ `EPrimitiveType GetPrimitiveType();`
- L195 _public function_ `MTL::VisibilityResultMode GetVisibilityResultMode()`
- L196 _public function_ `uint32 GetVisibilityResultOffset()`
- L198 _public prototype_ `void SetRenderPipelineState(FMetalCommandEncoder& CommandEncoder);`
- L199 _public prototype_ `void SetComputePipelineState(FMetalCommandEncoder& CommandEncoder);`
- L200 _public prototype_ `void FlushVisibilityResults(FMetalCommandEncoder& CommandEncoder);`
- L202 _public prototype_ `void ReleaseDescriptor(MTL::RenderPassDescriptor* Desc);`
- L203 _public prototype_ `void ClearPreviousComputeState();`
- L205 _public member_ `FMetalDescriptorHeap* OverriddenDescriptorHeap = nullptr;`
- L206 _public function_ `void SetOverriddenDescriptorHeap(FMetalDescriptorHeap* InHeap)`
- L211 _public prototype_ `void ConditionalUpdateBackBuffer(FMetalSurface& Surface);`
- L213 _private prototype_ `void SetDepthStencilState(FMetalDepthStencilState* InDepthStencilState);`
- L214 _private prototype_ `void SetRasterizerState(FMetalRasterizerState* InRasterizerState);`
- L217 _private prototype_ `template <class ShaderType> void SetResourcesFromTables(ShaderType Shader, CrossCompiler::EShaderStage ShaderStage);`
- L219 _private prototype_ `void SetViewport(uint32 Index, const MTL::Viewport& InViewport);`
- L220 _private prototype_ `void SetScissorRect(uint32 Index, bool const bEnable, MTL::ScissorRect const& Rect);`
- L222 _private prototype_ `void Validate();`
- L223 _private prototype_ `bool ValidateFunctionBindings(FMetalShaderPipeline* Pipeline, EMetalShaderFrequency Frequency, uint8 SideTableIndex);`
- L227 _private prototype_ `void EnsureTextureAndType(EMetalShaderStages Stage, uint32 Index, const TMap<uint8, uint8>& TexTypes) const;`
- L289 _private prototype_ `void InternalResetStageBindings();`
- L291 _private member_ `FMetalDevice& Device;`
- L293 _private member_ `FMetalShaderParameterCache ShaderParameters[EMetalShaderStages::Num];`
- L295 _private member_ `uint32 SampleCount;`
- L297 _private member_ `TSet<TRefCountPtr<FRHIUniformBuffer>> ActiveUniformBuffers;`
- L298 _private member_ `FRHIUniformBuffer* BoundUniformBuffers[EMetalShaderStages::Num][ML_MaxBuffers];`
- L301 _private member_ `uint32 DirtyUniformBuffers[EMetalShaderStages::Num];` — Bitfield for which uniform buffers are dirty
- L304 _private member_ `FMetalBufferBinding VertexBuffers[MaxVertexElementCount];` — Vertex attribute buffers
- L307 _private member_ `FMetalBufferBindings ShaderBuffers[EMetalShaderStages::Num];` — Bound shader resource tables.
- L308 _private member_ `FMetalTextureBindings ShaderTextures[EMetalShaderStages::Num];`
- L309 _private member_ `FMetalSamplerBindings ShaderSamplers[EMetalShaderStages::Num];`
- L311 _private member_ `MTL::StoreAction ColorStore[MaxSimultaneousRenderTargets];`
- L312 _private member_ `MTL::StoreAction DepthStore;`
- L313 _private member_ `MTL::StoreAction StencilStore;`
- L316 _private member_ `static constexpr uint32 TopLevelABNumEntry = METAL_MAX_BUFFERS + 1;` — One slot per buffer index (0..METAL_MAX_BUFFERS-1) plus one for the static sampler VA
- L317 _private member_ `uint64 CBVTable[EMetalShaderStages::Num][TopLevelABNumEntry];`
- L319 _private member_ `IRRuntimeVertexBuffer VertexBufferVAs[31];`
- L321 _private member_ `TStaticArray<TSet<MTL::Heap*>, EMetalShaderStages::Num> HeapsUsedByStage;`
- L322 _private member_ `TStaticArray<TSet<MTL::Resource*>, EMetalShaderStages::Num> RWResourcesByStage;`
- L323 _private member_ `TStaticArray<TSet<MTL::Resource*>, EMetalShaderStages::Num> ROResourcesByStage;`
- L326 _private member_ `FMetalQueryBufferRef VisibilityResults;`
- L327 _private member_ `MTL::VisibilityResultMode VisibilityMode;`
- L328 _private member_ `NS::UInteger VisibilityOffset;`
- L329 _private member_ `NS::UInteger VisibilityWritten;`
- L331 _private member_ `TRefCountPtr<FMetalDepthStencilState> DepthStencilState;`
- L332 _private member_ `TRefCountPtr<FMetalRasterizerState> RasterizerState;`
- L333 _private member_ `TRefCountPtr<FMetalGraphicsPipelineState> GraphicsPSO;`
- L334 _private member_ `TRefCountPtr<FMetalComputeShader> ComputeShader;`
- L335 _private member_ `TRefCountPtr<FMetalComputeShader> PreviousComputeShader;`
- L337 _private member_ `uint32 StencilRef;`
- L339 _private member_ `FLinearColor BlendFactor;`
- L340 _private member_ `CGSize FrameBufferSize;`
- L342 _private member_ `uint32 RenderTargetArraySize;`
- L344 _private member_ `MTL::Viewport Viewport[ML_MaxViewports];`
- L345 _private member_ `MTL::ScissorRect Scissor[ML_MaxViewports];`
- L347 _private member_ `uint32 ActiveViewports;`
- L348 _private member_ `uint32 ActiveScissors;`
- L350 _private member_ `FRHIRenderPassInfo RenderPassInfo;`
- L351 _private member_ `FTextureRHIRef ColorTargets[MaxSimultaneousRenderTargets];`
- L352 _private member_ `FTextureRHIRef ResolveTargets[MaxSimultaneousRenderTargets];`
- L353 _private member_ `FTextureRHIRef DepthStencilSurface;`
- L354 _private member_ `FTextureRHIRef DepthStencilResolve;`
- L356 _private member_ `MTL::RenderPassDescriptor* RenderPassDesc;`
- L357 _private member_ `uint32 RasterBits;`
- L358 _private member_ `uint8 PipelineBits;`
- L359 _private member_ `bool bIsRenderTargetActive;`
- L360 _private member_ `bool bHasValidRenderTarget;`
- L361 _private member_ `bool bHasValidColorTarget;`
- L362 _private member_ `bool bIsParallelContext = false;`

#### struct `FMetalStateCache::FMetalBufferBinding`  
`struct FMetalBufferBinding`  
_L231-252_
- L233 _public function_ `FMetalBufferBinding() : Bytes(nullptr), Offset(0), Length(0), Usage((MTL::ResourceUsage)0), ReferencedResources`
- L235 _public member_ `FMetalBufferPtr Buffer = nullptr;` — The bound buffers or nullptr.
- L237 _public member_ `FMetalBufferData* Bytes = nullptr;` — Optional bytes buffer used instead of an FMetalBuffer
- L239 _public member_ `NS::UInteger Offset;` — The bound buffer offsets or 0.
- L241 _public member_ `NS::UInteger Length;` — The bound buffer lengths or 0.
- L243 _public member_ `NS::UInteger ElementRowPitch;` — The bound buffer element row pitch or 0
- L245 _public member_ `MTL::ResourceUsage Usage;` — The bound buffer usage or 0
- L248 _public member_ `FMetalAccelerationStructure* AccelerationStructure = nullptr;` — The bound acceleration structure or nullptr.
- L251 _public member_ `TArray<TTuple<MTL::Resource*, MTL::ResourceUsage>> ReferencedResources;` — The resources referenced by this binding (e.g. BLAS referenced by a TLAS)

#### struct `FMetalStateCache::FMetalBufferBindings`  
`struct FMetalBufferBindings`  
_L255-264_
- desc: A structure of arrays for the current buffer binding settings.
- L257 _public function_ `FMetalBufferBindings() : Bound(0)`
- L259 _public member_ `FMetalBufferBinding Buffers[ML_MaxBuffers];` — The bound buffers/bytes or nullptr.
- L261 _public member_ `EPixelFormat Formats[ML_MaxBuffers];` — The pixel formats for buffers bound so that we emulate [RW]Buffer<T> type conversion
- L263 _public member_ `uint32 Bound;` — A bitmask for which buffers were bound by the application where a bit value of 1 is bound and 0 is unbound.

#### struct `FMetalStateCache::FMetalTextureBindings`  
`struct FMetalTextureBindings`  
_L267-276_
- desc: A structure of arrays for the current texture binding settings.
- L269 _public function_ `FMetalTextureBindings() : Bound(0)`
- L271 _public member_ `MTL::Texture* Textures[ML_MaxTextures];` — The bound textures or nullptr.
- L273 _public member_ `MTL::ResourceUsage Usage[ML_MaxTextures];` — The bound texture usage or 0
- L275 _public member_ `FMetalTextureMask Bound;` — A bitmask for which textures were bound by the application where a bit value of 1 is bound and 0 is unbound.

#### struct `FMetalStateCache::FMetalSamplerBindings`  
`struct FMetalSamplerBindings`  
_L279-286_
- desc: A structure of arrays for the current sampler binding settings.
- L281 _public function_ `FMetalSamplerBindings() : Bound(0)`
- L283 _public member_ `MTL::SamplerState* Samplers[ML_MaxSamplers];` — The bound sampler states or nullptr.
- L285 _public member_ `uint16 Bound;` — A bitmask for which samplers were bound by the application where a bit value of 1 is bound and 0 is unbound.

#### class `FMetalRenderPassDescriptorPool`  
`class FMetalRenderPassDescriptorPool`  
_L365-423_
- L368 _public function_ `FMetalRenderPassDescriptorPool()`
- L371 _public function_ `~FMetalRenderPassDescriptorPool()`
- L374 _public function_ `MTL::RenderPassDescriptor* CreateDescriptor()`
- L385 _public function_ `void ReleaseDescriptor(MTL::RenderPassDescriptor* Desc)`
- L415 _public function_ `static FMetalRenderPassDescriptorPool& Get()`
- L422 _private member_ `TLockFreePointerListLIFO<MTL::RenderPassDescriptor> Cache;`

### `Source/Runtime/Apple/MetalRHI/Private/MetalStaticSamplers.h` (Private)


#### class `FMetalStaticSamplers`  
`class FMetalStaticSamplers`  
_L19-35_
- L22 _public prototype_ `FMetalStaticSamplers(FMetalDevice& Device);`
- L23 _public prototype_ `~FMetalStaticSamplers();`
- L25 _public prototype_ `uint64 GetGPUAddress() const;`
- L28 _private member_ `static const uint32 MAX_STATIC_SAMPLERS = 6;`
- L31 _private member_ `MTL::SamplerDescriptor* MetalStaticSamplerDescs[MAX_STATIC_SAMPLERS];` — Static sampler table must match MetalCommon.ush and MetalMSC.cpp
- L33 _private member_ `TArray<MTL::SamplerState*> StaticSamplers;`
- L34 _private member_ `FMetalBufferPtr StaticSamplersTable;`

### `Source/Runtime/Apple/MetalRHI/Private/MetalSubmission.h` (Private)


#### enum `EMetalSyncPointType`  
`enum class EMetalSyncPointType`  
_L23-32_
- L27 _public enumerator_ `GPUOnly` — Sync points of this type do not include an FGraphEvent, so cannot report completion to the CPU (via either IsComplete() or Wait())
- L31 _public enumerator_ `GPUAndCPU` — Sync points of this type include an FGraphEvent. The IsComplete() and Wait() functions can be used to poll for completion from the CPU, or block the CPU, respectively.

#### struct `FMetalSignalEvent`  
`struct FMetalSignalEvent`  
_L35-40_
- desc: Fence type used by the device queues to manage GPU completion
- L37 _public member_ `MTL::Event* MetalEvent;`
- L38 _public member_ `uint64 NextCompletionValue = 0;`
- L39 _public member_ `std::atomic<uint64> LastSignaledValue = 0;`

#### struct `FMetalResolvedFence`  
`struct FMetalResolvedFence`  
_L43-52_
- desc: Used by FMetalSyncPoint and the submission thread to fix up signaled fence values at the end-of-pipe
- L45 _public member_ `FMetalSignalEvent& Fence;`
- L46 _public member_ `uint64 Value = 0;`
- L48 _public function_ `FMetalResolvedFence(FMetalSignalEvent& Fence, uint64 Value) : Fence(Fence) , Value(Value)`

#### class `FMetalSyncPoint`  
`class FMetalSyncPoint final : public FRefCountedObject`  
_L63-121_
- inherits: `FRefCountedObject`
- desc: A sync point is a logical point on a GPU queue's timeline that can be awaited by other queues, or the CPU. These are used throughout the RHI as a way to abstract the underlying Metal fences. The submission thread manages the underlying fences and signaled values, and reports completion to the relevant sync points via an FGraphEvent. Sync points are one-shot, meaning they represent a single timeline point, and are released after use, via ref-counting. Use FMetalSyncPoint::Create() to make a new sync point and hold a reference to it via a FMetalSyncPointRef object.
- L70 _private prototype_ `FMetalSyncPoint(FMetalSyncPoint const&) = delete;` — No copying or moving
- L71 _private prototype_ `FMetalSyncPoint(FMetalSyncPoint&&) = delete;`
- L73 _private member_ `TOptional<FMetalResolvedFence> ResolvedFence;`
- L74 _private member_ `FGraphEventRef GraphEvent;`
- L76 _private function_ `FMetalSyncPoint(EMetalSyncPointType Type)`
- L85 _public function_ `static FMetalSyncPointRef Create(EMetalSyncPointType Type)`
- L91 _public function_ `bool IsComplete() const`
- L97 _public prototype_ `void Wait() const;`
- L99 _public function_ `void OnCompletionCallback(TUniqueFunction<void()>&& Func)`
- L109 _public function_ `FGraphEvent* GetGraphEvent() const`
- L115 _public function_ `EMetalSyncPointType GetType() const`

#### struct `FMetalBatchedPayloadObjects`  
`struct FMetalBatchedPayloadObjects`  
_L125-134_
- L127 _public member_ `TArray<FMetalRHIRenderQuery*> OcclusionQueries;`
- L128 _public member_ `TArray<FMetalRHIRenderQuery*> TimestampQueries;`
- L130 _public function_ `bool IsEmpty() const`

#### struct `FMetalPayloadBaseFixLayout`  
`struct FMetalPayloadBaseFixLayout`  
_L137-140_
- desc: Base class to avoid 8 bytes of padding after the vtable
- L139 _public prototype_ `virtual ~FMetalPayloadBaseFixLayout() = default;`

#### struct `FMetalPayload`  
`struct FMetalPayload : public FMetalPayloadBaseFixLayout`  
_L145-227_
- inherits: `FMetalPayloadBaseFixLayout`
- desc: A single unit of work (specific to a single GPU node and queue type) to be processed by the submission thread.
- L152 _public member_ `FMetalCommandQueue& Queue;` — Constants
- L161 _public member_ `} SyncPointsToWait;`
- L168 _public member_ `TArray<FQueueFence, TInlineAllocator<GMetalMaxNumQueues>> QueueFencesToWait;`
- L170 _public prototype_ `void AddQueueFenceWait(FMetalSignalEvent& Fence, uint64 Value);`
- L173 _public member_ `bool bAlwaysSignal = false;` — Flags.
- L174 _public member_ `std::atomic<bool> bSubmitted { false };`
- L177 _public member_ `TFunction<void(MTL::CommandQueue*)> PreExecuteCallback;` — Used by RHIRunOnQueue
- L180 _public member_ `TArray<FMetalCommandBuffer*> CommandBuffersToExecute;` — Execute
- L181 _public member_ `FMetalCommandBuffer* SignalCommandBuffer = nullptr;`
- L184 _public member_ `TArray<FMetalSyncPointRef> SyncPointsToSignal;` — Signal
- L185 _public member_ `uint64 CompletionFenceValue = 0;`
- L187 _public member_ `FGraphEventRef SubmissionEvent;`
- L188 _public member_ `TOptional<uint64> SubmissionTime;`
- L190 _public member_ `FMetalBatchedPayloadObjects BatchedObjects;`
- L193 _public member_ `FRHIBreadcrumbRange BreadcrumbRange {};`
- L194 _public member_ `TSharedPtr<FRHIBreadcrumbAllocatorArray> BreadcrumbAllocators {};`
- L197 _public member_ `TOptional<FMetalTiming*> Timing;`
- L198 _public member_ `UE::RHI::GPUProfiler::FEventStream EventStream;`
- L199 _public member_ `TOptional<UE::RHI::GPUProfiler::FEvent::FFrameBoundary> EndFrameEvent;`
- L201 _public prototype_ `virtual ~FMetalPayload();`
- L203 _public prototype_ `virtual void PreExecute();`
- L205 _public function_ `virtual bool HasPreExecuteWork() const`
- L210 _public function_ `virtual bool RequiresQueueFenceSignal() const`
- L215 _public function_ `virtual bool HasWaitWork() const`
- L220 _public function_ `virtual bool HasSignalWork() const`
- L226 _protected prototype_ `FMetalPayload(FMetalCommandQueue&);`

#### struct `FMetalPayload::(anonymous)`  
`struct : public TArray<FMetalSyncPointRef>`  
_L155-161_
- inherits: `TArray<FMetalSyncPointRef>`
- desc: Wait

#### struct `FMetalPayload::FQueueFence`  
`struct FQueueFence`  
_L163-167_
- L165 _public member_ `FMetalSignalEvent& Fence;`
- L166 _public member_ `uint64 Value;`

#### Free symbols / members of external scopes

- L13 _variable_ `static constexpr uint32 GMetalMaxNumQueues = 1;`
- L21 _typedef_ `using FMetalSyncPointRef = TRefCountPtr<FMetalSyncPoint>;`
- L104 _function_ `` (scope `FMetalSyncPoint::OnCompletionCallback`)
- L159 _member_ `int32 Index = 0;` (scope `FMetalPayload::__anon8fe7ebae0208`) — Used to pause / resume iteration of the sync point array on the submission thread when we find a sync point that is unresolved.

### `Source/Runtime/Apple/MetalRHI/Private/MetalTransitionData.h` (Private)


#### class `FMetalTransitionData`  
`class FMetalTransitionData`  
_L25-54_
- L28 _public prototype_ `explicit FMetalTransitionData(ERHIPipeline InSrcPipelines, ERHIPipeline InDstPipelines, ERHITransitionCreateFlags InCreateFlags, TArrayView<const FRHITransitionInfo> InInfos);`
- L34 _public prototype_ `~FMetalTransitionData() = default;` — The default destructor is sufficient.
- L37 _public prototype_ `FMetalTransitionData() = delete;` — Disallow default, copy and move constructors.
- L38 _public prototype_ `FMetalTransitionData(const FMetalTransitionData&) = delete;`
- L39 _public prototype_ `FMetalTransitionData(const FMetalTransitionData&&) = delete;`
- L42 _public prototype_ `void BeginResourceTransitions() const;`
- L45 _public prototype_ `void EndResourceTransitions(FMetalCommandEncoder& CurrentEncoder, bool& UAVBarrier) const;`
- L48 _private member_ `ERHIPipeline SrcPipelines = ERHIPipeline::Num;`
- L49 _private member_ `ERHIPipeline DstPipelines = ERHIPipeline::Num;`
- L50 _private member_ `ERHITransitionCreateFlags CreateFlags = ERHITransitionCreateFlags::None;`
- L51 _private member_ `bool bCrossPipeline = false;`
- L52 _private member_ `FMetalTransitionInfoArray Infos = {};`
- L53 _private member_ `TRefCountPtr<FMetalFence> Fence = nullptr;`

#### Free symbols / members of external scopes

- L17 _typedef_ `typedef TArray<FRHITransitionInfo, TInlineAllocator<4> > FMetalTransitionInfoArray;`

### `Source/Runtime/Apple/MetalRHI/Private/MetalVertexDeclaration.h` (Private)


#### class `FMetalVertexDeclaration`  
`class FMetalVertexDeclaration : public FRHIVertexDeclaration`  
_L23-48_
- inherits: `FRHIVertexDeclaration`
- desc: This represents a vertex declaration that hasn't been combined with a specific shader to create a bound shader.
- L27 _public prototype_ `FMetalVertexDeclaration(const FVertexDeclarationElementList& InElements);` — Initialization constructor.
- L28 _public prototype_ `~FMetalVertexDeclaration();`
- L31 _public member_ `IRVersionedInputLayoutDescriptor InputDescriptor;`
- L32 _public member_ `TStaticArray<uint32, MaxVertexElementCount> InputDescriptorBufferStrides;`
- L35 _public member_ `FVertexDeclarationElementList Elements;` — Cached element info array (offset, stream index, etc)
- L38 _public member_ `FMetalHashedVertexDescriptor Layout;` — This is the layout for the vertex elements
- L41 _public member_ `uint32 BaseHash;` — Hash without considering strides which may be overriden
- L43 _public prototype_ `virtual bool GetInitializer(FVertexDeclarationElementList& Init) override final;`
- L44 _public function_ `virtual uint32 GetPrecachePSOHash() const override final`
- L47 _protected prototype_ `void GenerateLayout(const FVertexDeclarationElementList& Elements);`

### `Source/Runtime/Apple/MetalRHI/Private/Shaders/Debugging/MetalShaderDebugCache.h` (Private)


#### struct `FMetalShaderDebugCache`  
`struct FMetalShaderDebugCache`  
_L15-28_
- L17 _public function_ `static FMetalShaderDebugCache& Get()`
- L23 _public prototype_ `class FMetalShaderDebugZipFile* GetDebugFile(FString Path);`
- L24 _public prototype_ `NS::String* GetShaderCode(uint32 ShaderSrcLen, uint32 ShaderSrcCRC);`
- L26 _public member_ `FCriticalSection Mutex;`
- L27 _public member_ `TMap<FString, class FMetalShaderDebugZipFile*> DebugFiles;`

### `Source/Runtime/Apple/MetalRHI/Private/Shaders/Debugging/MetalShaderDebugZipFile.h` (Private)


#### class `FMetalShaderDebugZipFile`  
`class FMetalShaderDebugZipFile`  
_L16-47_
- L38 _public prototype_ `FMetalShaderDebugZipFile(FString LibPath);`
- L39 _public prototype_ `~FMetalShaderDebugZipFile();`
- L41 _public prototype_ `NS::String* GetShaderCode(uint32 ShaderSrcLen, uint32 ShaderSrcCRC);`
- L44 _private member_ `FCriticalSection Mutex;`
- L45 _private member_ `IFileHandle* File;`
- L46 _private member_ `TArray<FFileEntry> Files;`

#### struct `FMetalShaderDebugZipFile::FFileEntry`  
`struct FFileEntry`  
_L18-35_
- L20 _public member_ `FString Filename;`
- L21 _public member_ `uint32 Crc32;`
- L22 _public member_ `uint64 Length;`
- L23 _public member_ `uint64 Offset;`
- L24 _public member_ `uint32 Time;`
- L26 _public function_ `FFileEntry(const FString& InFilename, uint32 InCrc32, uint64 InLength, uint64 InOffset, uint32 InTime) : Filename(InFilename) , Crc32(InCrc32) , Length(InLength) , Offset(InOffset) , Time(InTime)`

### `Source/Runtime/Apple/MetalRHI/Private/Shaders/MetalCompiledShaderCache.h` (Private)


#### struct `FCachedCompiledShader`  
`struct FCachedCompiledShader`  
_L13-17_
- L15 _public member_ `MTLFunctionPtr Function;`
- L16 _public member_ `MTLLibraryPtr Library;`

#### struct `FMetalCompiledShaderCache`  
`struct FMetalCompiledShaderCache`  
_L19-39_
- L22 _public function_ `FCachedCompiledShader Find(FMetalCompiledShaderKey const& Key)`
- L27 _public function_ `void Add(FMetalCompiledShaderKey Key, MTLLibraryPtr Lib, MTLFunctionPtr Function)`
- L32 _public function_ `void Remove(FMetalCompiledShaderKey const& Key)`
- L38 _private member_ `TStripedMap<32, FMetalCompiledShaderKey, FCachedCompiledShader> Cache;`

#### Free symbols / members of external scopes

- L29 _function_ `Cache.FindOrProduce(Key, [&]() { return FCachedCompiledShader{ Function, Lib }; });` (scope `FMetalCompiledShaderCache::Add`)
- L41 _prototype_ `extern FMetalCompiledShaderCache& GetMetalCompiledShaderCache();`

### `Source/Runtime/Apple/MetalRHI/Private/Shaders/MetalCompiledShaderKey.h` (Private)


#### struct `FMetalCompiledShaderKey`  
`struct FMetalCompiledShaderKey`  
_L12-31_
- L14 _public function_ `FMetalCompiledShaderKey(uint32 CodeSize, uint32 CodeCRC, bool bIsExtendedBytecode = false, uint64 InLibrarySeed = 0)`
- L30 _public member_ `uint32 Hash;`

#### Free symbols / members of external scopes

- L20 _function_ `friend bool operator ==(const FMetalCompiledShaderKey& A, const FMetalCompiledShaderKey& B)`
- L25 _function_ `friend uint32 GetTypeHash(const FMetalCompiledShaderKey &Key)`

### `Source/Runtime/Apple/MetalRHI/Private/Shaders/MetalIoStoreShaderCodeArchive.h` (Private)


#### class `FMetalIoStoreShaderCodeArchive`  
`class FMetalIoStoreShaderCodeArchive : public FIoStoreShaderCodeArchive`  
_L14-45_
- inherits: `FIoStoreShaderCodeArchive`
- desc: Metal-specific extension of FIoStoreShaderCodeArchive. Tracks created shaders and releases Metal objects (MTLFunction/MTLLibrary) on Teardown, independently of when FRHIShader objects are destroyed.
- L17 _public prototype_ `FMetalIoStoreShaderCodeArchive(EShaderPlatform InPlatform, const FString& InLibraryName, FIoDispatcher& InIoDispatcher);`
- L19 _public prototype_ `virtual void Teardown() override;`
- L20 _public prototype_ `virtual void OnCloseShaderCode() override;`
- L21 _public prototype_ `virtual TRefCountPtr<FRHIShader> CreateShader(int32 Index, bool bRequired = true) override;`
- L24 _protected prototype_ `virtual void OnShaderGroupDataOwnerCreated() override;`
- L25 _protected prototype_ `virtual void OnShaderGroupDataOwnerReleased() override;`
- L29 _private prototype_ `static void ReleaseMetalObjectsForShader(FRHIShader* Shader);` — Helper function to call ReleaseMetalObjects for all shader types.
- L32 _private prototype_ `void ReleaseMetalObjectsAndWait();` — Releases all Metal objects and waits for pending dispatch_data_t destructors.
- L35 _private prototype_ `void WaitForPendingDispatchDataDestructors();` — Waits for all outstanding dispatch_data_t destructors for this archive to complete.
- L38 _private member_ `std::atomic<int32> PendingDispatchDataDestructorCount{0};` — Counts dispatch_data_t objects with a custom destructor that are still alive for this archive.
- L41 _private member_ `UE::FEventCount DispatchDataDestructorEvent;` — Notified each time a dispatch_data_t destructor completes for this archive.
- L44 _private member_ `TQueue<TRefCountPtr<FRHIShader>, EQueueMode::Mpsc> CreatedShaders;` — All shaders created from this archive. Lock-free MPSC queue since CreateShader can be called from multiple threads.

### `Source/Runtime/Apple/MetalRHI/Private/Shaders/MetalShaderLibrary.h` (Private)


#### class `FMetalShaderLibrary`  
`class FMetalShaderLibrary final : public FRHIShaderLibrary`  
_L20-122_
- inherits: `FRHIShaderLibrary`
- L51 _public typedef_ `using FShaderCodeArrayType = TArray<uint8>;`
- L53 _public typedef_ `using FShaderCodeArrayType = TArrayView<const uint8>;`
- L55 _private member_ `TUniquePtr<FShaderLibDataOwner> MemOwner;`
- L57 _public function_ `FMetalShaderLibrary(FMetalDevice& Device, EShaderPlatform Platform, FString const& Name, const FString& InShaderLibraryFilename, const FMetalShaderLibraryHeader& InHeader, FSerializedShaderArchive&& InSerializedShaders, FShaderCodeArrayType&& InShaderCode, TArray<TUniquePtr<FLazyMetalLib>>&& InLazyLibraries, TUniquePtr<FShaderLibDataOwner>&& InMemOwner) : FMetalShaderLibrary(Device, Platform, Name, InShaderLibraryFilename, InHeader, MoveTemp(InSerializedShaders), MoveTemp(InShaderCode), MoveTemp(InLazyLibraries))`
- L73 _public member_ `static FCriticalSection LoadedShaderLibraryMutex;`
- L74 _public member_ `static TMap<FString, FRHIShaderLibrary*> LoadedShaderLibraryMap;`
- L76 _public prototype_ `FMetalShaderLibrary(FMetalDevice& Device, EShaderPlatform Platform, FString const& Name, const FString& InShaderLibraryFilename, const FMetalShaderLibraryHeader& InHeader, FSerializedShaderArchive&& InSerializedShaders, FShaderCodeArrayType&& InShaderCode, TArray<TUniquePtr<FLazyMetalLib>>&& InLazyLibraries);`
- L85 _public prototype_ `virtual ~FMetalShaderLibrary();`
- L87 _public prototype_ `virtual bool IsNativeLibrary() const override final;`
- L89 _public prototype_ `virtual int32 GetNumShaders() const override;`
- L90 _public prototype_ `virtual int32 GetNumShaderMaps() const override;`
- L91 _public prototype_ `virtual uint32 GetSizeBytes() const override;`
- L92 _public prototype_ `virtual int32 GetNumShadersForShaderMap(int32 ShaderMapIndex) const override;`
- L93 _public prototype_ `virtual int32 GetShaderIndex(int32 ShaderMapIndex, int32 i) const override;`
- L95 _public prototype_ `virtual int32 FindShaderMapIndex(const FShaderHash& Hash) override;`
- L96 _public prototype_ `virtual int32 FindShaderIndex(const FShaderHash& Hash) override;`
- L97 _public function_ `virtual FShaderHash GetShaderHash(int32 ShaderMapIndex, int32 ShaderIndex) override`
- L102 _public function_ `virtual FShaderHash GetShaderMapHash(int32 ShaderMapIndex) const override`
- L107 _public function_ `virtual bool PreloadShader(int32 ShaderIndex, FGraphEventArray& OutCompletionEvents) override`
- L108 _public function_ `virtual bool PreloadShaderMap(int32 ShaderMapIndex, FGraphEventArray& OutCompletionEvents) override`
- L110 _public prototype_ `virtual TRefCountPtr<FRHIShader> CreateShader(int32 Index, bool bRequired = true) override;`
- L113 _private member_ `FMetalDevice& Device;`
- L114 _private member_ `FString ShaderLibraryFilename;`
- L115 _private member_ `FMetalShaderLibraryHeader Header;`
- L116 _private member_ `FSerializedShaderArchive SerializedShaders;`
- L117 _private member_ `FShaderCodeArrayType ShaderCode;`
- L118 _private member_ `TArray<TUniquePtr<FLazyMetalLib>> LazyLibraries;`
- L120 _private member_ `class FMetalShaderDebugZipFile* DebugFile;`

#### struct `FMetalShaderLibrary::FShaderLibDataOwner`  
`struct FShaderLibDataOwner`  
_L24-29_
- L26 _public member_ `TArray<uint8> Mem;`
- L27 _public member_ `TUniquePtr<IMappedFileHandle> MappedCacheFile;`
- L28 _public member_ `TUniquePtr<IMappedFileRegion> MappedRegion;`

#### class `FMetalShaderLibrary::FLazyMetalLib`  
`class FLazyMetalLib`  
_L31-48_
- L34 _public prototype_ `FLazyMetalLib(FString FilePath, TUniquePtr<FShaderLibDataOwner> Data);`
- L35 _public prototype_ `~FLazyMetalLib();`
- L37 _public prototype_ `FLazyMetalLib(FLazyMetalLib&& Other) = delete;`
- L38 _public prototype_ `FLazyMetalLib(FLazyMetalLib const&) = delete;`
- L39 _public prototype_ `FLazyMetalLib& operator=(FLazyMetalLib const&) = delete;`
- L41 _public prototype_ `MTLLibraryPtr EnsureLoaded(FMetalDevice& MetalDevice);`
- L44 _private member_ `TUniquePtr<FShaderLibDataOwner> Data;`
- L45 _private member_ `FString FilePath;`
- L46 _private member_ `UE::FMutex LibraryMutex;`
- L47 _private member_ `std::atomic<MTL::Library*> Library = nullptr;`

### `Source/Runtime/Apple/MetalRHI/Private/Shaders/MetalShaderParameterCache.h` (Private)


#### class `FMetalShaderParameterCache`  
`class FMetalShaderParameterCache`  
_L15-70_
- L19 _public prototype_ `FMetalShaderParameterCache();` — Constructor.
- L22 _public prototype_ `~FMetalShaderParameterCache();` — Destructor.
- L24 _public function_ `inline void PrepareGlobalUniforms(uint32 TypeIndex, uint32 UniformArraySize)`
- L35 _public prototype_ `void Reset();` — Invalidates all existing data.
- L40 _public prototype_ `void MarkAllDirty();` — Marks all uniform arrays as dirty.
- L45 _public prototype_ `void Set(uint32 BufferIndex, uint32 ByteOffset, uint32 NumBytes, const void* NewValues);` — Sets values directly into the packed uniform array
- L50 _public prototype_ `void CommitPackedGlobals(class FMetalStateCache* Cache, class FMetalCommandEncoder* Encoder, uint32 Frequency, const FMetalShaderBindings& Bindings);` — Commit shader parameters to the currently bound program.
- L53 _private member_ `static constexpr uint32 SizeOfFloat = sizeof(float);`
- L56 _private member_ `FMetalBufferData* PackedGlobalUniforms[CrossCompiler::PACKED_TYPEINDEX_MAX];` — CPU memory block for storing uniform values.
- L65 _private member_ `FRange PackedGlobalUniformDirty[CrossCompiler::PACKED_TYPEINDEX_MAX];` — Dirty ranges for each uniform array.
- L67 _private member_ `uint32 PackedGlobalUniformsSizes[CrossCompiler::PACKED_TYPEINDEX_MAX];`
- L69 _private prototype_ `void ResizeGlobalUniforms(uint32 TypeIndex, uint32 UniformArraySize);`

#### struct `FMetalShaderParameterCache::FRange`  
`struct FRange`  
_L58-62_
- L60 _public member_ `uint32 LowVector;`
- L61 _public member_ `uint32 HighVector;`

### `Source/Runtime/Apple/MetalRHI/Private/Shaders/Types/MetalAmplificationShader.h` (Private)


#### class `FMetalAmplificationShader`  
`class FMetalAmplificationShader : public TMetalBaseShader<FRHIAmplificationShader, SF_Amplification>`  
_L18-25_
- inherits: `TMetalBaseShader<FRHIAmplificationShader,SF_Amplification>`
- L21 _public prototype_ `FMetalAmplificationShader(FMetalDevice& Device, const FRHICreateShaderDesc& CreateShaderDesc);`
- L22 _public prototype_ `FMetalAmplificationShader(FMetalDevice& Device, const FRHICreateShaderDesc& CreateShaderDesc, MTLLibraryPtr InLibrary);`
- L24 _public prototype_ `MTLFunctionPtr GetFunction();`

### `Source/Runtime/Apple/MetalRHI/Private/Shaders/Types/MetalComputeShader.h` (Private)


#### class `FMetalComputeShader`  
`class FMetalComputeShader : public TMetalBaseShader<FRHIComputeShader, SF_Compute>`  
_L18-45_
- inherits: `TMetalBaseShader<FRHIComputeShader,SF_Compute>`
- L21 _public prototype_ `FMetalComputeShader(FMetalDevice& Device, const FRHICreateShaderDesc& CreateShaderDesc, MTLLibraryPtr InLibrary);`
- L22 _public prototype_ `virtual ~FMetalComputeShader();`
- L25 _public prototype_ `virtual void ReleaseMetalObjects() override;` — Release the Metal Pipeline.
- L27 _public prototype_ `FMetalShaderPipelinePtr GetPipeline();`
- L28 _public prototype_ `MTLFunctionPtr GetFunction();`
- L31 _public member_ `int32 NumThreadsX;` — thread group counts
- L32 _public member_ `int32 NumThreadsY;`
- L33 _public member_ `int32 NumThreadsZ;`
- L37 _public member_ `FMetalRayTracingHeader RayTracingBindings;` — Meta-data for function table binding indexes (UINT32_MAX if unavailable).
- L42 _private member_ `FMetalShaderPipelinePtr Pipeline;` — the state object for a compute shader
- L44 _private member_ `FCriticalSection PipelineCS;`

### `Source/Runtime/Apple/MetalRHI/Private/Shaders/Types/MetalGeometryShader.h` (Private)


#### class `FMetalGeometryShader`  
`class FMetalGeometryShader : public TMetalBaseShader<FRHIGeometryShader, SF_Geometry>`  
_L18-27_
- inherits: `TMetalBaseShader<FRHIGeometryShader,SF_Geometry>`
- L22 _public prototype_ `FMetalGeometryShader(FMetalDevice& Device, const FRHICreateShaderDesc& CreateShaderDesc);`
- L23 _public prototype_ `FMetalGeometryShader(FMetalDevice& Device, const FRHICreateShaderDesc& CreateShaderDesc, MTLLibraryPtr InLibrary);`
- L25 _public prototype_ `MTLFunctionPtr GetFunction();`

### `Source/Runtime/Apple/MetalRHI/Private/Shaders/Types/MetalMeshShader.h` (Private)


#### class `FMetalMeshShader`  
`class FMetalMeshShader : public TMetalBaseShader<FRHIMeshShader, SF_Mesh>`  
_L19-26_
- inherits: `TMetalBaseShader<FRHIMeshShader,SF_Mesh>`
- L22 _public prototype_ `FMetalMeshShader(FMetalDevice& Device, const FRHICreateShaderDesc& CreateShaderDesc);`
- L23 _public prototype_ `FMetalMeshShader(FMetalDevice& Device, const FRHICreateShaderDesc& CreateShaderDesc, MTLLibraryPtr InLibrary);`
- L25 _public prototype_ `MTLFunctionPtr GetFunction();`

### `Source/Runtime/Apple/MetalRHI/Private/Shaders/Types/MetalPixelShader.h` (Private)


#### class `FMetalPixelShader`  
`class FMetalPixelShader : public TMetalBaseShader<FRHIPixelShader, SF_Pixel>`  
_L18-25_
- inherits: `TMetalBaseShader<FRHIPixelShader,SF_Pixel>`
- L21 _public prototype_ `FMetalPixelShader(FMetalDevice& Device, const FRHICreateShaderDesc& CreateShaderDesc);`
- L22 _public prototype_ `FMetalPixelShader(FMetalDevice& Device, const FRHICreateShaderDesc& CreateShaderDesc, MTLLibraryPtr InLibrary);`
- L24 _public prototype_ `MTLFunctionPtr GetFunction();`

### `Source/Runtime/Apple/MetalRHI/Private/Shaders/Types/MetalRayShader.h` (Private)


#### class `FMetalBaseRayShader`  
`template<typename BaseResourceType, int32 ShaderType> class FMetalBaseRayShader : public TMetalBaseShader<BaseResourceType, ShaderType>`  
_L18-49_
- inherits: `TMetalBaseShader<BaseResourceType,ShaderType>`
- L21 _public function_ `FMetalBaseRayShader(FMetalDevice& MetalDevice, const FRHICreateShaderDesc& CreateShaderDesc, MTLLibraryPtr InLibrary, IRShaderStage InShaderStage, FString& InEntryPoint, bool bInCompileAsBinary, bool bUseExtendedCodeSection = false) : TMetalBaseShader<BaseResourceType, ShaderType>(MetalDevice), bCompileAsBinary(bInCompileAsBinary), ShaderStage(InShaderStage), EntryPoint(InEntryPoint)`
- L31 _public function_ `IRShaderStage GetShaderStage()`
- L36 _public function_ `MTLFunctionPtr GetFunction()`
- L41 _public function_ `virtual FString GetFunctionName() override`
- L46 _public member_ `bool bCompileAsBinary = false;`
- L47 _public member_ `IRShaderStage ShaderStage;`
- L48 _public member_ `FString EntryPoint;`

#### class `FMetalRayShader`  
`class FMetalRayShader : public FRHIRayTracingShader`  
_L51-132_
- inherits: `FRHIRayTracingShader`
- L56 _public prototype_ `FMetalRayShader(FMetalDevice& Device, const FRHICreateShaderDesc& CreateShaderDesc, EShaderFrequency InFrequency, MTLLibraryPtr InLibrary = nullptr);`
- L57 _public prototype_ `virtual ~FMetalRayShader();`
- L60 _public prototype_ `void ReleaseMetalObjects();` — Releases MTLFunction and MTLLibrary references on all sub-shaders.
- L62 _public function_ `inline IRRootSignature *GetGlobalRootSignature() const`
- L63 _public function_ `inline IRRootSignature *GetLocalRootSignature() const`
- L65 _public function_ `const inline TArray<IRRootParameter1>& GetGlobalRootParams() const`
- L66 _public function_ `const inline TArray<IRRootParameter1>& GetLocalRootParams() const`
- L68 _public function_ `inline uint32 GetGlobalRootSignatureSize() const`
- L69 _public function_ `inline uint32 GetLocalRootSignatureSize() const`
- L72 _public member_ `FString EntryPoint;` — These are the original names when the shaders were compiled, not necessarily the final name generated by IRConverter
- L73 _public member_ `FString AnyHitEntryPoint;` — Optional any-hit shader entry point for SF_RayHitGroup.
- L74 _public member_ `FString IntersectionEntryPoint;` — Optional intersection shader entry point for SF_RayHitGroup.
- L77 _public member_ `TArray<FUniformBufferStaticSlot> StaticSlots;` — Uniform buffer static slots
- L79 _public member_ `static constexpr bool bBinaryCompile = true;`
- L81 _public function_ `inline MTLFunctionPtr GetRayGenFunction()`
- L82 _public function_ `inline MTLFunctionPtr GetMissFunction()`
- L83 _public function_ `inline MTLFunctionPtr GetCallableFunction()`
- L84 _public function_ `inline MTLFunctionPtr GetClosestHitFunction()`
- L85 _public function_ `inline MTLFunctionPtr GetAnyHitAndIntersectionFunction()`
- L87 _public function_ `inline MTLFunctionPtr GetEntryPointFunction()`
- L99 _public function_ `inline EShaderFrequency GetShaderFrequency() const`
- L101 _public function_ `inline bool HasVisibleFunctionEntryPoint() const`
- L102 _public function_ `inline bool HasIntersectionFunctionEntryPoint() const`
- L104 _public function_ `inline uint32 GetGlobalRootSignatureStartIdx() const`
- L107 _private prototype_ `static IRRootSignature *CreateRootSignature(const TArray<IRRootParameter1> &RootParams, bool bIsLocal);`
- L108 _private prototype_ `static uint32 CalculateRootSignatureSize(IRRootSignature* RootSignature);`
- L110 _private member_ `IRRootSignature *GlobalRootSignature = nullptr;`
- L111 _private member_ `IRRootSignature *LocalRootSignature = nullptr;`
- L113 _private member_ `uint32 GlobalRootSignatureSize = 0, LocalRootSignatureSize = 0;`
- L113 _private member_ `uint32 GlobalRootSignatureSize = 0, LocalRootSignatureSize = 0;`
- L115 _private member_ `TArray<IRRootParameter1> GlobalRootParams;`
- L116 _private member_ `TArray<IRRootParameter1> LocalRootParams;`
- L118 _private member_ `uint32 GlobalRootSignatureStartIdx = 0;`
- L120 _private member_ `EShaderFrequency Frequency;`
- L122 _private typedef_ `using FMetalRayGenShader = FMetalBaseRayShader<FRHIRayGenShader, SF_RayGen>;`
- L123 _private typedef_ `using FMetalRayMissShader = FMetalBaseRayShader<FRHIRayMissShader, SF_RayMiss>;`
- L124 _private typedef_ `using FMetalRayCallableShader = FMetalBaseRayShader<FRHIRayCallableShader, SF_RayCallable>;`
- L125 _private typedef_ `using FMetalHitGroupShader = FMetalBaseRayShader<FRHIRayHitGroupShader, SF_RayHitGroup>;`
- L127 _private member_ `TRefCountPtr<FMetalRayGenShader> RayGen = nullptr;`
- L128 _private member_ `TRefCountPtr<FMetalRayMissShader> Miss = nullptr;`
- L129 _private member_ `TRefCountPtr<FMetalRayCallableShader> Callable = nullptr;`
- L130 _private member_ `TRefCountPtr<FMetalHitGroupShader> ClosestHit = nullptr;`
- L131 _private member_ `TRefCountPtr<FMetalHitGroupShader> AnyHitAndIntersection = nullptr;`

### `Source/Runtime/Apple/MetalRHI/Private/Shaders/Types/MetalVertexShader.h` (Private)


#### class `FMetalVertexShader`  
`class FMetalVertexShader : public TMetalBaseShader<FRHIVertexShader, SF_Vertex>`  
_L18-28_
- inherits: `TMetalBaseShader<FRHIVertexShader,SF_Vertex>`
- L21 _public prototype_ `FMetalVertexShader(FMetalDevice& Device, const FRHICreateShaderDesc& CreateShaderDesc);`
- L22 _public prototype_ `FMetalVertexShader(FMetalDevice& Device, const FRHICreateShaderDesc& CreateShaderDesc, MTLLibraryPtr InLibrary);`
- L24 _public prototype_ `MTLFunctionPtr GetFunction();`
- L26 _public prototype_ `MTLFunctionPtr GetObjectFunctionForGeometryEmulation();`

### `Source/Runtime/Apple/MetalRHI/Private/Shaders/Types/Templates/MetalBaseShader.h` (Private)


#### struct `FMetalShaderData`  
`struct FMetalShaderData`  
_L46-80_
- L49 _public member_ `FMetalShaderBindings Bindings;` — External bindings for this shader.
- L52 _public member_ `TMap<uint32, MTL::ArgumentEncoder*> ArgumentEncoders;` — Argument encoders for shader IABs
- L55 _public member_ `TMap<uint32, TBitArray<>> ArgumentBitmasks;` — Tier1 Argument buffer bitmasks
- L58 _public member_ `TArray<FUniformBufferStaticSlot> StaticSlots;` — Uniform buffer static slots
- L61 _public member_ `int32 SideTableBinding = -1;` — The binding for the buffer side-table if present
- L64 _public member_ `uint32 SourceLen = 0;` — CRC & Len for name disambiguation
- L65 _public member_ `uint32 SourceCRC = 0;`
- L68 _public member_ `uint64 LibrarySeed = 0;` — Unique identifier for the owning FRHIShaderLibrary, used to scope the compiled shader cache per library. 0 if no library.
- L71 _public member_ `MTLFunctionPtr Function;` — this is the compiler shader
- L73 _public member_ `MTLLibraryPtr Library;` — This is the MTLLibrary for the shader so we can dynamically refine the MTLFunction
- L76 _public member_ `NS::String* MetalCodeNSString = nullptr;` — The debuggable text source
- L79 _public member_ `uint32 LibraryFunctionIndex = -1;` — Index of the function (in the library) pointing to the function requested by the user (when GetCompiledFunction() is called with an explicit index).

#### class `TMetalBaseShader`  
`template<typename BaseResourceType, int32 ShaderType> class TMetalBaseShader : public BaseResourceType, public FMetalShaderData`  
_L83-129_
- inherits: `BaseResourceType,FMetalShaderData`
- L91 _public function_ `TMetalBaseShader(FMetalDevice& MetalDevice) : Device(MetalDevice)`
- L96 _public function_ `virtual ~TMetalBaseShader()`
- L101 _public prototype_ `void Init(const FRHICreateShaderDesc& CreateShaderDesc, FMetalCodeHeader& Header, MTLLibraryPtr InLibrary, bool bBinaryCompiled = false, bool bUseExtendedCodeSection = false);`
- L102 _public prototype_ `void Destroy();`
- L106 _public function_ `virtual void ReleaseMetalObjects()` — Releases MTLFunction and MTLLibrary references. Called during shader library teardown to free Metal objects while the FRHIShader may still be alive (held by materials, PSO cache, etc.).
- L114 _public function_ `virtual FString GetFunctionName()`
- L122 _public prototype_ `NS::String* GetSourceCode();` — Gets the Metal source code as an NSString if available or build a string with the hash & function name inside instead.
- L125 _protected member_ `bool bIsExtendedBytecode = 0;`
- L127 _protected member_ `FMetalDevice& Device;`
- L128 _protected prototype_ `MTLFunctionPtr GetCompiledFunction(bool const bAsync = false, const int32 FunctionIndex = -1, bool bCompileToBinary = false);`
- L138 _function_ `template<typename BaseResourceType, int32 ShaderType> void TMetalBaseShader<BaseResourceType, ShaderType>::Init(const FRHICreateShaderDesc& CreateShaderDesc, FMetalCodeHeader& Header, MTLLibraryPtr InLibrary, bool bBinaryCompiled, bool bUseExtendedCodeSection)`
- L434 _function_ `template<typename BaseResourceType, int32 ShaderType> void TMetalBaseShader<BaseResourceType, ShaderType>::Destroy()`
- L444 _function_ `template<typename BaseResourceType, int32 ShaderType> inline NS::String* TMetalBaseShader<BaseResourceType, ShaderType>::GetSourceCode()`
- L458 _function_ `template<typename BaseResourceType, int32 ShaderType> MTLFunctionPtr TMetalBaseShader<BaseResourceType, ShaderType>::GetCompiledFunction(bool const bAsync, const int32 FunctionIndex, bool bCompileToBinary)`

#### enum `TMetalBaseShader::(anonymous)`  
``  
_L87-89_

#### Free symbols / members of external scopes

- L30 _prototype_ `extern MTL::LanguageVersion ValidateVersion(uint32 Version);`
- L39 _macro_ `#define DEBUG_METAL_SHADERS (UE_BUILD_DEBUG || UE_BUILD_DEVELOPMENT)` — Set to 1 to enable shader debugging (makes the driver save the shader source)
- L88 _enumerator_ `StaticFrequency = ShaderType` (scope `TMetalBaseShader::__anon6d426d2f0103`)
- L506 _function_ `` (scope `TMetalBaseShader::GetCompiledFunction`)

### `Source/Runtime/Apple/MetalRHI/Public/IMetalDynamicRHI.h` (Public)


#### struct `IMetalDynamicRHI`  
`struct IMetalDynamicRHI : public FDynamicRHI`  
_L14-30_
- inherits: `FDynamicRHI`
- L16 _public function_ `virtual ERHIInterfaceType GetInterfaceType() const override final`
- L21 _public prototype_ `virtual MTL::Device* RHIGetDevice() = 0;`
- L23 _public prototype_ `virtual void RHIRunOnQueue(TFunction<void(MTL::CommandQueue*)>&& CodeToRun, bool bWaitForSubmission) = 0;`
- L24 _public prototype_ `virtual FTextureRHIRef RHICreateTexture2DFromCVMetalTexture(EPixelFormat Format, ETextureCreateFlags TexCreateFlags, const FClearValueBinding& ClearValueBinding, CVMetalTextureRef Resource) = 0;`
- L28 _public prototype_ `virtual bool RHIReadViewportDataDirect(uint32& OutWidth, uint32& OutHeight, TArray<FColor>& OutData) = 0;` — Used for getting the last back buffer content after a crash.

#### Free symbols / members of external scopes

- L32 _function_ `inline bool IsRHIMetal()`
- L37 _function_ `inline IMetalDynamicRHI* GetIMetalDynamicRHI()`

### `Source/Runtime/Apple/MetalRHI/Public/MetalRHI.h` (Public)
_(no declarations extracted)_

### `Source/Runtime/Apple/MetalRHI/Public/MetalRHIContext.h` (Public)


#### struct `FMetalParallelRenderPassInfo`  
`struct FMetalParallelRenderPassInfo`  
_L25-29_
- L27 _public member_ `MTLParallelRenderCommandEncoderPtr ParallelEncoder;`
- L28 _public member_ `MTL::RenderPassDescriptor* RenderPassDesc = nullptr;`

#### enum `EMetalFlushFlags`  
`enum class EMetalFlushFlags`  
_L31-40_
- L33 _public enumerator_ `None = 0`
- L36 _public enumerator_ `WaitForSubmission = 1` — Block the calling thread until the submission thread has dispatched all work.
- L39 _public enumerator_ `WaitForCompletion = 2` — Both the calling thread until the GPU has signaled completion of all dispatched work.

#### class `FMetalRHICommandContext`  
`class FMetalRHICommandContext : public IRHICommandContext`  
_L44-373_
- inherits: `IRHICommandContext`
- desc: The interface RHI command context.
- L47 _public prototype_ `FMetalRHICommandContext(FMetalDevice& Device);`
- L48 _public prototype_ `virtual ~FMetalRHICommandContext();`
- L50 _public function_ `static inline FMetalRHICommandContext& Get(FRHICommandListBase& CmdList)`
- L56 _public prototype_ `void ResetContext();`
- L57 _public prototype_ `void BeginComputeEncoder();`
- L58 _public prototype_ `void EndComputeEncoder();`
- L59 _public prototype_ `void BeginBlitEncoder();`
- L60 _public prototype_ `void EndBlitEncoder();`
- L62 _public prototype_ `virtual void RHISetComputePipelineState(FRHIComputePipelineState* ComputePipelineState) override;`
- L64 _public prototype_ `virtual void RHIDispatchComputeShader(uint32 ThreadGroupCountX, uint32 ThreadGroupCountY, uint32 ThreadGroupCountZ) final override;`
- L66 _public prototype_ `virtual void RHIDispatchIndirectComputeShader(FRHIBuffer* ArgumentBuffer, uint32 ArgumentOffset) final override;`
- L71 _public prototype_ `virtual void RHISetMultipleViewports(uint32 Count, const FViewportBounds* Data) final override;` — Useful when used with geometry shader (emit polygons to different viewports), otherwise SetViewPort() is simpler @param Count >0 @param Data must not be 0
- L74 _public prototype_ `virtual void RHIClearUAVFloat(FRHIUnorderedAccessView* UnorderedAccessViewRHI, const FVector4f& Values) final override;` — Clears a UAV to the multi-component value provided.
- L75 _public prototype_ `virtual void RHIClearUAVUint(FRHIUnorderedAccessView* UnorderedAccessViewRHI, const FUintVector4& Values) final override;`
- L77 _public prototype_ `virtual void RHICopyTexture(FRHITexture* SourceTextureRHI, FRHITexture* DestTextureRHI, const FRHICopyTextureInfo& CopyInfo) final override;`
- L78 _public prototype_ `virtual void RHICopyBufferRegion(FRHIBuffer* DstBufferRHI, uint64 DstOffset, FRHIBuffer* SrcBufferRHI, uint64 SrcOffset, uint64 NumBytes) final override;`
- L80 _public prototype_ `virtual void RHIBeginRenderQuery(FRHIRenderQuery* RenderQuery) final override;`
- L81 _public prototype_ `virtual void RHIEndRenderQuery(FRHIRenderQuery* RenderQuery) final override;`
- L83 _public prototype_ `void EndDrawingViewport(FMetalViewport* Viewport, const FRHIPresentArgs& InPresentArgs);`
- L85 _public prototype_ `virtual void RHISetStreamSource(uint32 StreamIndex, FRHIBuffer* VertexBuffer, uint32 Offset) final override;`
- L91 _public prototype_ `virtual void RHISetViewport(float MinX, float MinY, float MinZ, float MaxX, float MaxY, float MaxZ) final override;` — @param MinX including like Win32 RECT @param MinY including like Win32 RECT @param MaxX excluding like Win32 RECT @param MaxY excluding like Win32 RECT
- L93 _public prototype_ `virtual void RHISetStereoViewport(float LeftMinX, float RightMinX, float LeftMinY, float RightMinY, float MinZ, float LeftMaxX, float RightMaxX, float LeftMaxY, float RightMaxY, float MaxZ) final override;`
- L99 _public prototype_ `virtual void RHISetScissorRect(bool bEnable, uint32 MinX, uint32 MinY, uint32 MaxX, uint32 MaxY) final override;` — @param MinX including like Win32 RECT @param MinY including like Win32 RECT @param MaxX excluding like Win32 RECT @param MaxY excluding like Win32 RECT
- L101 _public prototype_ `virtual void RHISetGraphicsPipelineState(FRHIGraphicsPipelineState* GraphicsState, uint32 StencilRef, bool bApplyAdditionalState) final override;`
- L103 _public prototype_ `virtual void RHISetStaticUniformBuffers(const FUniformBufferStaticBindings& InUniformBuffers) final override;`
- L104 _public prototype_ `virtual void RHISetStaticUniformBuffer(FUniformBufferStaticSlot Slot, FRHIUniformBuffer* Buffer) final override;`
- L106 _public prototype_ `virtual void RHISetShaderParameters(FRHIGraphicsShader* Shader, TConstArrayView<uint8> InParametersData, TConstArrayView<FRHIShaderParameter> InParameters, TConstArrayView<FRHIShaderParameterResource> InResourceParameters, TConstArrayView<FRHIShaderParameterResource> InBindlessParameters) final override;`
- L107 _public prototype_ `virtual void RHISetShaderParameters(FRHIComputeShader* Shader, TConstArrayView<uint8> InParametersData, TConstArrayView<FRHIShaderParameter> InParameters, TConstArrayView<FRHIShaderParameterResource> InResourceParameters, TConstArrayView<FRHIShaderParameterResource> InBindlessParameters) final override;`
- L109 _public prototype_ `virtual void RHISetStencilRef(uint32 StencilRef) final override;`
- L111 _public prototype_ `virtual void RHISetBlendFactor(const FLinearColor& BlendFactor) final override;`
- L113 _public prototype_ `void SetRenderTargets(uint32 NumSimultaneousRenderTargets, const FRHIRenderTargetView* NewRenderTargets, const FRHIDepthRenderTargetView* NewDepthStencilTarget);`
- L115 _public prototype_ `void SetRenderTargetsAndClear(const FRHISetRenderTargetsInfo& RenderTargetsInfo);`
- L117 _public prototype_ `virtual void RHIDrawPrimitive(uint32 BaseVertexIndex, uint32 NumPrimitives, uint32 NumInstances) final override;`
- L119 _public prototype_ `virtual void RHIDrawPrimitiveIndirect(FRHIBuffer* ArgumentBuffer, uint32 ArgumentOffset) final override;`
- L122 _public prototype_ `virtual void RHIDrawIndexedPrimitive(FRHIBuffer* IndexBuffer, int32 BaseVertexIndex, uint32 FirstInstance, uint32 NumVertices, uint32 StartIndex, uint32 NumPrimitives, uint32 NumInstances) final override;` — @param NumPrimitives need to be >0
- L124 _public prototype_ `virtual void RHIDrawIndexedPrimitiveIndirect(FRHIBuffer* IndexBuffer, FRHIBuffer* ArgumentBuffer, uint32 ArgumentOffset) final override;`
- L127 _public prototype_ `virtual void RHIDispatchMeshShader(uint32 ThreadGroupCountX, uint32 ThreadGroupCountY, uint32 ThreadGroupCountZ) final override;`
- L128 _public prototype_ `virtual void RHIDispatchIndirectMeshShader(FRHIBuffer* ArgumentBuffer, uint32 ArgumentOffset) final override;`
- L137 _public prototype_ `virtual void RHISetDepthBounds(float MinDepth, float MaxDepth) final override;` — Sets Depth Bounds Testing with the given min/max depth. @param MinDepth	The minimum depth for depth bounds test @param MaxDepth	The maximum depth for depth bounds test. The valid values for fMinDepth and fMaxDepth are such that 0 <= fMinDepth <= fMaxDepth <= 1
- L140 _public prototype_ `virtual void RHIBeginBreadcrumbGPU(FRHIBreadcrumbNode* Breadcrumb) final override;`
- L141 _public prototype_ `virtual void RHIEndBreadcrumbGPU(FRHIBreadcrumbNode* Breadcrumb) final override;`
- L144 _public prototype_ `virtual void RHICopyToStagingBuffer(FRHIBuffer* SourceBufferRHI, FRHIStagingBuffer* DestinationStagingBufferRHI, uint32 Offset, uint32 NumBytes) final override;`
- L145 _public prototype_ `virtual void RHIWriteGPUFence(FRHIGPUFence* FenceRHI) final override;`
- L147 _public prototype_ `virtual void RHIBeginTransitions(TArrayView<const FRHITransition*> Transitions);`
- L148 _public prototype_ `virtual void RHIEndTransitions(TArrayView<const FRHITransition*> Transitions);`
- L150 _public prototype_ `virtual void RHIBeginParallelRenderPass(TSharedPtr<FRHIParallelRenderPassInfo> InInfo, const TCHAR* InName) final override;`
- L151 _public prototype_ `virtual void RHIEndParallelRenderPass() final override;`
- L153 _public prototype_ `virtual void RHIBeginRenderPass(const FRHIRenderPassInfo& InInfo, const TCHAR* InName) final override;`
- L154 _public prototype_ `virtual void RHIEndRenderPass() final override;`
- L156 _public prototype_ `virtual void RHINextSubpass() final override;`
- L159 _public prototype_ `virtual void RHIBindAccelerationStructureMemory(FRHIRayTracingScene* Scene, FRHIBuffer* Buffer, uint32 BufferOffset) final override;`
- L160 _public prototype_ `virtual void RHIBuildAccelerationStructures(TConstArrayView<FRayTracingGeometryBuildParams> Params, const FRHIBufferRange& ScratchBufferRange) final override;`
- L161 _public prototype_ `virtual void RHIBuildAccelerationStructures(TConstArrayView<FRayTracingSceneBuildParams> Params) final override;`
- L162 _public prototype_ `virtual void RHIRayTraceDispatch(FRHIRayTracingPipelineState* RayTracingPipelineState, FRHIRayTracingShader* RayGenShader, FRHIShaderBindingTable* SBT, const FRayTracingShaderBindings& GlobalResourceBindings, uint32 Width, uint32 Height) final override;`
- L166 _public prototype_ `virtual void RHIRayTraceDispatchIndirect(FRHIRayTracingPipelineState* InRayTracingPipelineState, FRHIRayTracingShader* InRayGenShader, FRHIShaderBindingTable* InSBT, const FRayTracingShaderBindings& GlobalResourceBindings, FRHIBuffer* ArgumentBuffer, uint32 ArgumentOffset) final override;`
- L169 _public prototype_ `virtual void RHISetBindingsOnShaderBindingTable( FRHIShaderBindingTable* SBT, FRHIRayTracingPipelineState* Pipeline, uint32 NumBindings, const FRayTracingLocalShaderBindings* Bindings, ERayTracingBindingType BindingType) final override;`
- L174 _public prototype_ `void RHICommitShaderBindingTable(FRHIShaderBindingTable* InSBT, FRHIBuffer* InlineBindingDataBuffer);`
- L176 _public prototype_ `void WriteCompactedAccelerationStructureSize(MTLAccelerationStructurePtr AccelerationStructure, FMetalBufferPtr CompactedStructureSizeBuffer, uint32_t Offset);`
- L177 _public prototype_ `void CopyAndCompactAccelerationStructure(MTLAccelerationStructurePtr AccelerationStructureSrc, MTLAccelerationStructurePtr AccelerationStructureDest);`
- L179 _public prototype_ `void BuildAccelerationStructure(FMetalBufferPtr CurInstanceBuffer, uint32_t InstanceBufferOffset, FMetalBufferPtr ScratchBuffer, uint32_t ScratchBufferOffset, FMetalBufferPtr HitGroupContributionsBuffer, uint32_t HitGroupContributionsBufferOffset, uint32_t MaxNumInstances, FMetalAccelerationStructure* AS);`
- L181 _public prototype_ `void BuildAccelerationStructure(MTLAccelerationStructurePtr AS, MTL::AccelerationStructureDescriptor* Descriptor, FMetalBufferPtr ScratchBuffer, uint32_t ScratchBufferOffset);`
- L184 _public prototype_ `void RefitAccelerationStructure(MTLAccelerationStructurePtr SrcBLAS, MTLAccelerationStructurePtr DstBLAS, MTL::PrimitiveAccelerationStructureDescriptor* Descriptor, MTL::Buffer* ScratchBufferRes, uint32_t ScratchOffset);`
- L187 _public prototype_ `void FillBuffer(MTL::Buffer* Buffer, NS::Range Range, uint8 Value);`
- L188 _public prototype_ `void CopyFromTextureToBuffer(MTL::Texture* Texture, uint32 sourceSlice, uint32 sourceLevel, MTL::Origin sourceOrigin, MTL::Size sourceSize, FMetalBufferPtr toBuffer, uint32 destinationOffset, uint32 destinationBytesPerRow, uint32 destinationBytesPerImage, MTL::BlitOption options);`
- L189 _public prototype_ `void CopyFromBufferToTexture(FMetalBufferPtr Buffer, uint32 sourceOffset, uint32 sourceBytesPerRow, uint32 sourceBytesPerImage, MTL::Size sourceSize, MTL::Texture* toTexture, uint32 destinationSlice, uint32 destinationLevel, MTL::Origin destinationOrigin, MTL::BlitOption options);`
- L190 _public prototype_ `void CopyFromTextureToTexture(MTL::Texture* Texture, uint32 sourceSlice, uint32 sourceLevel, MTL::Origin sourceOrigin, MTL::Size sourceSize, MTL::Texture* toTexture, uint32 destinationSlice, uint32 destinationLevel, MTL::Origin destinationOrigin);`
- L191 _public prototype_ `void CopyFromBufferToBuffer(FMetalBufferPtr SourceBuffer, NS::UInteger SourceOffset, FMetalBufferPtr DestinationBuffer, NS::UInteger DestinationOffset, NS::UInteger Size);`
- L193 _public prototype_ `void CommitRenderResourceTables(void);`
- L194 _public prototype_ `void PrepareToRender(uint32 PrimitiveType);`
- L195 _public prototype_ `bool PrepareToDraw(uint32 PrimitiveType);`
- L196 _public prototype_ `void PrepareToDispatch();`
- L197 _public prototype_ `void SetupParallelContext(const FRHIParallelRenderPassInfo* ParallelRenderPassInfo);`
- L199 _public prototype_ `void Finalize(TArray<FMetalPayload*>& OutPayloads);`
- L202 _public function_ `void EnqueueDescriptorUpdate(FRHIDescriptorHandle InHandle, const IRDescriptorTableEntry& InDescriptor)`
- L208 _public prototype_ `void PushDescriptorUpdates();`
- L209 _public prototype_ `void InsertComputeMemoryBarrier();`
- L216 _public member_ `} CurrentPhase = EPhase::Wait;`
- L218 _public function_ `FMetalPayload* GetPayload(EPhase Phase)`
- L229 _public function_ `void NewPayload()`
- L234 _public function_ `FMetalSyncPoint* GetContextSyncPoint()`
- L251 _public member_ `} BatchedSyncPoints;`
- L254 _public prototype_ `void SignalSyncPoint(FMetalSyncPoint* SyncPoint);` — Inserts a command to signal the specified sync point
- L257 _public prototype_ `void WaitSyncPoint(FMetalSyncPoint* SyncPoint);` — Inserts a command that blocks the GPU queue until the specified sync point is signaled.
- L259 _public prototype_ `void SynchronizeResource(MTL::Resource* Resource);`
- L260 _public prototype_ `void SynchronizeTexture(MTL::Texture* Texture, uint32 Slice, uint32 Level);`
- L263 _public prototype_ `void SignalEvent(MTLEventPtr Event, uint32_t SignalCount);` — Update the event to capture all GPU work so far enqueued by this encoder.
- L266 _public prototype_ `void WaitForEvent(MTLEventPtr Event, uint32_t SignalCount);` — Prevent further GPU work until the event is reached.
- L269 _public prototype_ `void SignalSharedEvent(MTLSharedEventPtr Event, uint32_t SignalCount);` — Update the event to capture all GPU work so far enqueued by this encoder.
- L272 _public prototype_ `void WaitForSharedEvent(MTLSharedEventPtr Event, uint32_t SignalCount);` — Prevent further GPU work until the event is reached.
- L275 _public prototype_ `void BeginRenderingImmersive(const MetalRHIVisionOS::BeginRenderingImmersiveParams& Params);`
- L276 _public member_ `cp_frame_t SwiftFrame = nullptr;`
- L278 _public function_ `void SetCustomPresentViewport(FRHIViewport* Viewport)`
- L279 _public member_ `FRHIViewport* CustomPresentViewport = nullptr;`
- L281 _public prototype_ `FMetalCommandBuffer* GetCurrentCommandBuffer();`
- L283 _public function_ `void BeginRecursiveCommand()`
- L288 _public function_ `inline const TArray<FRHIUniformBuffer*>& GetStaticUniformBuffers() const`
- L293 _public function_ `inline TSharedRef<FMetalQueryBufferPool, ESPMode::ThreadSafe> GetQueryBufferPool()`
- L298 _public function_ `inline FMetalStateCache& GetStateCache()`
- L303 _public function_ `inline FMetalCommandQueue& GetCommandQueue()`
- L308 _public function_ `inline FMetalDevice& GetDevice()`
- L313 _public function_ `inline bool IsInsideRenderPass() const`
- L318 _public function_ `const FRHIShaderBindingLayout& GetShaderBindingLayout() const`
- L324 _public prototype_ `void StartCommandBuffer();`
- L325 _public prototype_ `void EndCommandBuffer();`
- L327 _public prototype_ `void FlushProfilerStats();`
- L329 _public prototype_ `void FlushCommands(EMetalFlushFlags Flags);`
- L332 _protected member_ `FMetalDevice& Device;`
- L335 _protected member_ `FMetalCommandQueue& CommandQueue;` — The wrapper around the device command-queue for creating & committing command buffers to
- L337 _protected member_ `FMetalCommandEncoder CurrentEncoder;`
- L340 _protected member_ `FMetalStateCache StateCache;` — The cache of all tracked & accessible state.
- L343 _protected member_ `TSharedPtr<FMetalQueryBufferPool, ESPMode::ThreadSafe> QueryBuffer;` — A pool of buffers for writing visibility query results.
- L345 _protected member_ `MTL::RenderPassDescriptor* RenderPassDesc = nullptr;`
- L347 _protected member_ `TRefCountPtr<FMetalFence> CurrentEncoderFence;`
- L348 _protected member_ `uint64_t UploadSyncCounter = 0;`
- L350 _protected member_ `bool bWithinRenderPass = false;`
- L351 _protected member_ `bool bIsParallelContext = false;`
- L352 _protected prototype_ `void ResolveTexture(UE::RHICore::FResolveTextureInfo Info);`
- L354 _protected member_ `TArray<FRHIUniformBuffer*> StaticUniformBuffers;`
- L358 _protected member_ `TArray<FMetalPayload*> Payloads;` — The array of recorded payloads the submission thread will process. These are returned when the context is finalized.
- L361 _protected member_ `FMetalSyncPointRef ContextSyncPoint;` — A sync point signaled when all payloads in this context have completed.
- L363 _protected member_ `FMetalParallelRenderPassInfo* ParallelRenderPassInfo;`
- L365 _protected member_ `const FRHIShaderBindingLayout* ShaderBindingLayout = nullptr;`
- L368 _protected member_ `FMetalPendingDescriptorUpdates PendingDescriptorUpdates;`
- L372 _private prototype_ `void RHIClearMRT(bool bClearColor, int32 NumClearColors, const FLinearColor* ColorArray, bool bClearDepth, float Depth, bool bClearStencil, uint32 Stencil);`

#### enum `FMetalRHICommandContext::EPhase`  
`enum class EPhase`  
_L211-216_
- L213 _public enumerator_ `Wait`
- L214 _public enumerator_ `Execute`
- L215 _public enumerator_ `Signal`

#### struct `FMetalRHICommandContext::(anonymous)`  
``  
_L248-251_

#### class `FMetalRHIUploadContext`  
`class FMetalRHIUploadContext : public IRHIUploadContext`  
_L375-393_
- inherits: `IRHIUploadContext`
- L378 _public prototype_ `FMetalRHIUploadContext(FMetalDevice& Device);`
- L379 _public prototype_ `~FMetalRHIUploadContext();`
- L381 _public typedef_ `typedef TFunction<void(FMetalRHICommandContext*)> UploadContextFunction;`
- L383 _public prototype_ `void Finalize(TArray<FMetalPayload*>& OutPayloads);`
- L385 _public function_ `void EnqueueFunction(UploadContextFunction Function)`
- L391 _private member_ `FMetalRHICommandContext* UploadContext;`
- L392 _private member_ `TArray<UploadContextFunction> UploadFunctions;`

#### struct `FMetalContextArray`  
`struct FMetalContextArray : public TRHIPipelineArray<FMetalRHICommandContext*>`  
_L395-398_
- inherits: `TRHIPipelineArray<FMetalRHICommandContext*>`
- L397 _public prototype_ `FMetalContextArray(FRHIContextArray const& Contexts);`

#### Free symbols / members of external scopes

- L18 _namespace_ `namespace MetalRHIVisionOS`
- L249 _member_ `TArray<FMetalSyncPointRef> ToWait;` (scope `FMetalRHICommandContext::__anon2400bdce0108`)
- L250 _member_ `TArray<FMetalSyncPointRef> ToSignal;` (scope `FMetalRHICommandContext::__anon2400bdce0108`)

### `Source/Runtime/Apple/MetalRHI/Public/MetalRHIVisionOSBridge.h` (Public)


#### enum `MetalRHIVisionOS::EPresentChoice`  
`enum class EPresentChoice : uint8`  
_L15-19_
- L17 _public enumerator_ `Present`
- L18 _public enumerator_ `DoNotPresent`

#### struct `MetalRHIVisionOS::PresentImmersiveParams`  
`struct PresentImmersiveParams`  
_L21-30_
- L23 _public member_ `EPresentChoice PresentChoice = EPresentChoice::DoNotPresent;`
- L24 _public member_ `const FTextureRHIRef Texture;`
- L25 _public member_ `const FTextureRHIRef Depth;`
- L26 _public member_ `cp_frame_t SwiftFrame;`
- L27 _public member_ `cp_drawable_t SwiftDrawable;`
- L28 _public member_ `int FrameCounter = -1;`
- L29 _public member_ `class IRHICommandContext* RHICommandContext = nullptr;`

#### Free symbols / members of external scopes

- L11 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogMetalVisionOS, Warning, All);`
- L11 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogMetalVisionOS, Warning, All);`
- L13 _namespace_ `namespace MetalRHIVisionOS`
- L31 _prototype_ `void PresentImmersive(const PresentImmersiveParams& Params);` (scope `MetalRHIVisionOS`)

### `Source/Runtime/Apple/MetalRHI/Public/MetalResources.h` (Public)


#### struct `FMetalRenderPipelineHash`  
`struct FMetalRenderPipelineHash`  
_L24-38_
- L36 _public member_ `uint64 RasterBits;`
- L37 _public member_ `uint64 TargetBits;`

#### class `FMetalBuffer`  
`class FMetalBuffer`  
_L51-113_
- L61 _public prototype_ `FMetalBuffer(MTL::Buffer* Handle, FreePolicy Allocation);`
- L62 _public prototype_ `FMetalBuffer(MTL::Buffer* Handle, NS::Range Range, IMetalBufferAllocator* InAllocator);`
- L64 _public prototype_ `virtual ~FMetalBuffer();`
- L66 _public function_ `uint32 GetOffset()`
- L71 _public function_ `uint32 GetLength()`
- L76 _public function_ `const NS::Range& GetRange()`
- L86 _public function_ `void* Contents()`
- L92 _public function_ `uint64_t GetGPUAddress()`
- L97 _public function_ `MTL::Buffer* GetMTLBuffer()`
- L99 _public function_ `void MarkDeleted()`
- L105 _private prototype_ `void Release();`
- L107 _private member_ `MTL::Buffer* Buffer;`
- L108 _private member_ `IMetalBufferAllocator* Allocator;`
- L110 _private member_ `NS::Range SubRange;`
- L111 _private member_ `FreePolicy OnFreePolicy;`
- L112 _private member_ `bool bMarkedDeleted = false;`

#### enum `FMetalBuffer::FreePolicy`  
`enum class FreePolicy`  
_L54-59_
- L56 _public enumerator_ `Owner` — FMetalBuffer owns releasing memory
- L57 _public enumerator_ `BufferAllocator` — Owned by allocator
- L58 _public enumerator_ `Temporary` — Temporary buffer that does not need a release

#### class `FMetalAccelerationStructure`  
`class FMetalAccelerationStructure`  
_L118-167_
- L121 _public function_ `FMetalAccelerationStructure(MTLAccelerationStructurePtr InAccelerationStructure, uint32_t InSize) : AccelerationStructure(InAccelerationStructure), Size(InSize)`
- L127 _public prototype_ `~FMetalAccelerationStructure();`
- L129 _public function_ `uint32_t GetSize() const`
- L134 _public function_ `void SetLabel(const FString& Label)`
- L140 _public prototype_ `void SetIndirectArgumentBuffer(FMetalBufferPtr IndirectArgs);`
- L141 _public function_ `void SetHitContributionsBuffer(FMetalBufferPtr InHitContributionsBuffer)`
- L146 _public function_ `FMetalBufferPtr GetIndirectArgumentBuffer()`
- L151 _public function_ `MTLAccelerationStructurePtr GetAccelerationStructure()`
- L156 _public function_ `FMetalBufferPtr GetHitContributionsBuffer()`
- L162 _private member_ `MTLAccelerationStructurePtr AccelerationStructure;`
- L163 _private member_ `uint32_t Size;`
- L165 _private member_ `FMetalBufferPtr IndirectArgumentBuffer;`
- L166 _private member_ `FMetalBufferPtr HitContributionsBuffer;`

#### struct `FMetalTextureCreateDesc`  
`struct FMetalTextureCreateDesc : public FRHITextureCreateDesc`  
_L170-180_
- inherits: `FRHITextureCreateDesc`
- L172 _public prototype_ `FMetalTextureCreateDesc(FMetalDevice& Device, FRHITextureCreateDesc const& CreateDesc);`
- L173 _public prototype_ `FMetalTextureCreateDesc(FMetalTextureCreateDesc const& Other);`
- L174 _public prototype_ `FMetalTextureCreateDesc& operator=(const FMetalTextureCreateDesc& Other);`
- L176 _public member_ `MTLTextureDescriptorPtr Desc;`
- L177 _public member_ `MTL::PixelFormat MTLFormat;`
- L178 _public member_ `bool bIsRenderTarget = false;`
- L179 _public member_ `uint8 FormatKey = 0;`

#### class `FMetalViewableResource`  
`class FMetalViewableResource`  
_L186-205_
- L189 _public function_ `~FMetalViewableResource()`
- L194 _public function_ `bool HasLinkedViews() const`
- L199 _public prototype_ `void UpdateLinkedViews(FMetalRHICommandContext* Context);`
- L204 _private member_ `FMetalResourceViewBase* LinkedViews = nullptr;`

#### class `FMetalSurface`  
`class FMetalSurface : public FRHITexture, public FMetalViewableResource`  
_L213-347_
- inherits: `FRHITexture,FMetalViewableResource`
- desc: Metal RHI texture resource
- L219 _public prototype_ `FMetalSurface(FMetalDevice& Device, FMetalTextureCreateDesc const& CreateDesc);` — Constructor that will create Texture and Color/DepthBuffers as needed
- L224 _public prototype_ `virtual ~FMetalSurface();` — Destructor
- L230 _protected function_ `FMetalSurface(FMetalDevice& MetalDevice, MTLTexturePtr InTexture, FRHITextureCreateDesc const& CreateDesc) : FRHITexture (CreateDesc) , Device (MetalDevice) , FormatKey (0) , Texture (InTexture) , Viewport (nullptr) , TotalTextureSize (0)` — Constructor for derived classes
- L241 _public prototype_ `void Initialize(FRHICommandListBase& RHICmdList);`
- L244 _public prototype_ `MTL::Buffer* AllocSurface(const FRHILockTextureArgs& Arguments, uint32 MipBytes, uint32 DestStride);` — @returns A newly allocated buffer object large enough for the surface within the texture specified.
- L249 _public prototype_ `void UpdateSurfaceAndDestroySourceBuffer(FMetalRHICommandContext* Context, MTL::Buffer* SourceBuffer, uint32 MipIndex, uint32 ArrayIndex);` — Apply the data in Buffer to the surface specified. Will also handle destroying SourceBuffer appropriately.
- L256 _public prototype_ `FRHILockTextureResult Lock(const FRHILockTextureArgs& Arguments, bool bSingleLayer);` — Locks one of the texture's mip-maps. @param ArrayIndex Index of the texture array/face in the form Index*6+Face @return A pointer to the specified texture data.
- L261 _public prototype_ `void Unlock(const FRHILockTextureArgs& Arguments);` — Unlocks a previously locked mip-map. @param ArrayIndex Index of the texture array/face in the form Index*6+Face
- L268 _public prototype_ `FRHILockTextureResult AsyncLock(FRHICommandListBase& RHICmdList, const FRHILockTextureArgs& Arguments);` — Locks one of the texture's mip-maps. @param ArrayIndex Index of the texture array/face in the form Index*6+Face @return A pointer to the specified texture data.
- L273 _public prototype_ `uint32 GetMipSize(uint32 MipIndex, uint32* Stride, bool bSingleLayer);` — Returns how much memory a single mip uses, and optionally returns the stride
- L278 _public prototype_ `uint32 GetMemorySize();` — Returns how much memory is used by the surface
- L281 _public prototype_ `uint32 GetNumFaces();` — Returns the number of faces for the texture
- L284 _public prototype_ `MTLTexturePtr GetDrawableTexture();` — Gets the drawable texture if this is a back-buffer surface.
- L285 _public prototype_ `void ReleaseDrawableTexture();`
- L287 _public prototype_ `MTLTexturePtr GetCurrentTexture();`
- L289 _public prototype_ `MTLTexturePtr Reallocate(MTLTexturePtr Texture, MTL::TextureUsage UsageModifier);`
- L290 _public prototype_ `void MakeAliasable(void);`
- L292 _public function_ `virtual void* GetTextureBaseRHI() override final`
- L297 _public function_ `virtual void* GetNativeResource() const override final`
- L303 _public function_ `virtual FRHIDescriptorHandle GetDefaultBindlessHandle() const override final`
- L309 _public member_ `FMetalDevice& Device;`
- L310 _public member_ `uint8 FormatKey;`
- L313 _public member_ `MTLTexturePtr Texture;` — texture used for store actions and binding to shader params
- L315 _public member_ `MTLTexturePtr MSAATexture;` — if surface is MSAA, texture used to bind for RT
- L323 _public member_ `MTLTexturePtr MSAAResolveTexture;` — texture used for a resolve target.  Same as texture on iOS. Dummy target on Mac where RHISupportsSeparateMSAAAndResolveTextures is true.	In this case we don't always want a resolve texture but we have to have one until renderpasses are implemented at a high level. Mac / RHISupportsSeparateMSAAAndResolveTextures == true iOS A9+ where depth resolve is available iOS < A9 where depth resolve is unavailable.
- L326 _public member_ `FMetalBufferPtr BackingBuffer;` — Used for atomics
- L329 _public member_ `class FMetalViewport* Viewport;` — For back-buffers, the owning viewport.
- L335 _private prototype_ `void SafeRelease(MTLTexturePtr Texture);` — Safely releases the texture when not in use @param MTLTexturePtr Texture from surface to be released
- L337 _private member_ `FCriticalSection DrawableMutex;`
- L342 _protected member_ `uint64 TotalTextureSize;` — how much memory is allocated for this texture
- L345 _protected member_ `FRHIDescriptorHandle BindlessHandle;`

#### class `FMetalExternalSurface`  
`class FMetalExternalSurface : public FMetalSurface`  
_L352-360_
- inherits: `FMetalSurface`
- desc: Derived class that can be used for creating surfaces with external textures
- L355 _public prototype_ `FMetalExternalSurface(FMetalDevice& MetalDevice, MTLTexturePtr InTexture, FRHITextureCreateDesc const& CreateDesc, TUniqueFunction<void()>&& InOnDeleteFunction);`
- L356 _public prototype_ `~FMetalExternalSurface();`
- L359 _private member_ `TUniqueFunction<void()> OnDeleteFunction;`

#### class `FMetalBufferData`  
`class FMetalBufferData`  
_L362-370_
- L365 _public prototype_ `~FMetalBufferData();`
- L366 _public prototype_ `void InitWithSize(uint32 Size);`
- L368 _public member_ `uint8* Data = nullptr;`
- L369 _public member_ `uint32 Len = 0;`

#### class `FMetalRHIBuffer`  
`class FMetalRHIBuffer final : public FRHIBuffer, public FMetalViewableResource`  
_L372-463_
- inherits: `FRHIBuffer,FMetalViewableResource`
- L375 _public prototype_ `FMetalRHIBuffer(FRHICommandListBase& RHICmdList, FMetalDevice& MetalDevice, const FRHIBufferCreateDesc& CreateDesc, FResourceArrayUploadInterface* InResourceArray);`
- L376 _public prototype_ `virtual ~FMetalRHIBuffer();`
- L378 _public prototype_ `bool RequiresTransferBuffer();`
- L380 _public prototype_ `void AllocateBuffer();`
- L381 _public prototype_ `void ReleaseBuffer();`
- L382 _public prototype_ `void SwitchBuffer(FRHICommandListBase& RHICmdList);`
- L387 _public prototype_ `void* Lock(FRHICommandListBase& RHICmdList, EResourceLockMode LockMode, uint32 Offset, uint32 Size);` — Prepare a CPU accessible buffer for uploading to GPU memory
- L392 _public prototype_ `void Unlock(FRHICommandListBase& RHICmdList);` — Prepare a CPU accessible buffer for uploading to GPU memory
- L394 _public prototype_ `void UploadTransferBuffer(FRHICommandListBase& RHICmdList, FMetalBufferPtr&& InTransferBuffer, uint32 UploadSize);`
- L397 _public function_ `const FMetalBufferPtr& GetCurrentBuffer()` — We need to allocate here because buffer backed textures can be created without an Allocated buffer
- L406 _public function_ `const FMetalBufferPtr& GetCurrentBufferOrNull() const`
- L412 _public function_ `MTL::IndexType GetIndexType() const` — 16- or 32-bit; used for index buffers only.
- L418 _public function_ `bool IsAccelerationStructure() const`
- L422 _public member_ `FMetalAccelerationStructure* AccelerationStructure = nullptr;`
- L428 _public prototype_ `bool UsePrivateMemory() const;` — Whether to allocate the resource from private memory.
- L430 _public prototype_ `void TakeOwnership(FMetalRHIBuffer& Other);`
- L431 _public prototype_ `void ReleaseOwnership();`
- L433 _public member_ `FMetalDevice& Device;`
- L436 _public member_ `FMetalBufferPtr TransferBuffer;` — A temporary shared/CPU accessible buffer for upload/download
- L437 _public member_ `FMetalBufferPtr CurrentBuffer;`
- L440 _public member_ `uint32 Size;` — Initial buffer size.
- L443 _public member_ `uint32 LockOffset = 0;` — offset into the buffer (for lock usage)
- L446 _public member_ `uint32 LockSize = 0;` — Sizeof outstanding lock.
- L449 _public member_ `MTL::StorageMode Mode;` — Storage mode
- L452 _public member_ `EResourceLockMode CurrentLockMode = RLM_Num;` — Current lock mode. RLM_Num indicates this buffer is not locked.
- L454 _public member_ `bool bIsFirstLock = true;`
- L457 _public prototype_ `void UpdateAllocationTags();`
- L462 _private prototype_ `void AllocTransferBuffer(bool bOnRHIThread, uint32 InSize, EResourceLockMode LockMode);` — Allocate the CPU accessible buffer for data transfer.

#### class `FMetalResourceViewBase`  
`class FMetalResourceViewBase : public TIntrusiveLinkedList<FMetalResourceViewBase>`  
_L465-579_
- inherits: `TIntrusiveLinkedList<FMetalResourceViewBase>`
- L507 _public typedef_ `> TStorage;`
- L521 _protected function_ `FMetalResourceViewBase(FMetalDevice& InDevice) : Device(InDevice)`
- L525 _public prototype_ `virtual ~FMetalResourceViewBase();`
- L527 _public function_ `EMetalType GetMetalType() const`
- L532 _public function_ `const MTLTexturePtr& GetTextureView() const`
- L538 _public function_ `const FBufferView& GetBufferView() const`
- L544 _public function_ `const FTextureBufferBacked& GetTextureBufferBacked() const`
- L551 _public function_ `FMetalAccelerationStructure* const& GetAccelerationStructure() const`
- L559 _public member_ `TArray<TTuple<MTL::Resource*, MTL::ResourceUsage>> ReferencedResources;` — TODO: This is kinda awkward; should probably be refactored at some point.
- L561 _public prototype_ `virtual void UpdateView(FMetalRHICommandContext* Context, const bool bConstructing) = 0;`
- L564 _protected prototype_ `void InitAsTextureView(MTLTexturePtr);`
- L565 _protected prototype_ `void InitAsBufferView(FMetalBufferPtr Buffer, uint32 Offset, uint32 Size);`
- L566 _protected prototype_ `void InitAsTextureBufferBacked(MTLTexturePtr Texture, FMetalBufferPtr Buffer, uint32 Offset, uint32 Size, EPixelFormat Format, bool bIsBuffer);`
- L569 _protected prototype_ `void InitAsAccelerationStructure(FMetalAccelerationStructure* AccelerationStructure);`
- L572 _protected prototype_ `void Invalidate();`
- L574 _protected member_ `FMetalDevice& Device;`
- L575 _protected member_ `bool bOwnsResource = true;`
- L578 _private member_ `TStorage Storage;`

#### struct `FMetalResourceViewBase::FBufferView`  
`struct FBufferView`  
_L468-479_
- L470 _public member_ `FMetalBufferPtr Buffer;`
- L471 _public member_ `uint32 Offset;`
- L472 _public member_ `uint32 Size;`
- L474 _public function_ `FBufferView(FMetalBufferPtr Buffer, uint32 Offset, uint32 Size) : Buffer(Buffer) , Offset(Offset) , Size(Size)`

#### struct `FMetalResourceViewBase::FTextureBufferBacked`  
`struct FTextureBufferBacked`  
_L481-498_
- L483 _public member_ `MTLTexturePtr Texture;`
- L484 _public member_ `FMetalBufferPtr Buffer;`
- L485 _public member_ `uint32 Offset;`
- L486 _public member_ `uint32 Size;`
- L487 _public member_ `EPixelFormat Format;`
- L488 _public member_ `bool bIsBuffer;`
- L490 _public function_ `FTextureBufferBacked(MTLTexturePtr Texture, FMetalBufferPtr Buffer, uint32 Offset, uint32 Size, EPixelFormat Format, bool bIsBuffer) : Texture(Texture) , Buffer(Buffer) , Offset(Offset) , Size(Size) , Format(Format) , bIsBuffer(bIsBuffer)`

#### enum `FMetalResourceViewBase::EMetalType`  
`enum class EMetalType`  
_L509-518_
- L511 _public enumerator_ `Null = TStorage::IndexOfType<FEmptyVariantState>()`
- L512 _public enumerator_ `TextureView = TStorage::IndexOfType<MTLTexturePtr>()`
- L513 _public enumerator_ `BufferView = TStorage::IndexOfType<FBufferView>()`
- L514 _public enumerator_ `TextureBufferBacked = TStorage::IndexOfType<FTextureBufferBacked>()`
- L516 _public enumerator_ `AccelerationStructure = TStorage::IndexOfType<FMetalAccelerationStructure*>() #endif`

#### class `FMetalShaderResourceView`  
`class FMetalShaderResourceView final : public FRHIShaderResourceView, public FMetalResourceViewBase`  
_L581-602_
- inherits: `FRHIShaderResourceView,FMetalResourceViewBase`
- L584 _public prototype_ `FMetalShaderResourceView(FMetalDevice& Device, FRHICommandListBase& RHICmdList, FRHIViewableResource* InResource, FRHIViewDesc const& InViewDesc);`
- L586 _public prototype_ `~FMetalShaderResourceView();`
- L587 _public prototype_ `FMetalViewableResource* GetBaseResource() const;`
- L589 _public prototype_ `virtual void UpdateView(FMetalRHICommandContext* Context, const bool bConstructing) override;`
- L593 _public member_ `FRHIDescriptorHandle BindlessHandle;`
- L595 _public function_ `virtual FRHIDescriptorHandle GetBindlessHandle() const override`
- L600 _public member_ `FMetalSurface* SurfaceOverride;`

#### class `FMetalUnorderedAccessView`  
`class FMetalUnorderedAccessView final : public FRHIUnorderedAccessView, public FMetalResourceViewBase`  
_L604-629_
- inherits: `FRHIUnorderedAccessView,FMetalResourceViewBase`
- L607 _public prototype_ `FMetalUnorderedAccessView(FMetalDevice& Device, FRHICommandListBase& RHICmdList, FRHIViewableResource* InResource, FRHIViewDesc const& InViewDesc);`
- L609 _public prototype_ `~FMetalUnorderedAccessView();`
- L610 _public prototype_ `FMetalViewableResource* GetBaseResource() const;`
- L612 _public prototype_ `virtual void UpdateView(FMetalRHICommandContext* Context, const bool bConstructing) override;`
- L614 _public prototype_ `void ClearUAV(TRHICommandList_RecursiveHazardous<FMetalRHICommandContext>& RHICmdList, const void* ClearValue, bool bFloat);`
- L616 _public prototype_ `void ClearUAVWithBlitEncoder(TRHICommandList_RecursiveHazardous<FMetalRHICommandContext>& RHICmdList, uint32 Pattern);`
- L621 _private member_ `FRHIDescriptorHandle BindlessHandle;`
- L624 _public function_ `virtual FRHIDescriptorHandle GetBindlessHandle() const override`

#### class `FMetalGPUFence`  
`class FMetalGPUFence final : public FRHIGPUFence`  
_L631-647_
- inherits: `FRHIGPUFence`
- L634 _public prototype_ `FMetalGPUFence(FMetalDevice& Device, FName InName);`
- L635 _public prototype_ `~FMetalGPUFence();`
- L637 _public prototype_ `virtual void Clear() override;`
- L638 _public prototype_ `virtual bool Poll() const override;`
- L639 _public prototype_ `virtual void Wait(FRHICommandListImmediate& RHICmdList, FRHIGPUMask GPUMask) const override;`
- L642 _private member_ `FMetalSyncPointRef SyncPoint;`
- L643 _private member_ `MTLSharedEventPtr SharedEvent;`
- L644 _private member_ `FMetalDevice* Device = nullptr;`

#### struct `TMetalResourceTraits`  
`template<> struct TMetalResourceTraits<FRHIShaderLibrary>`  
_L673-676_
- L675 _public typedef_ `typedef FMetalShaderLibrary TConcreteType;`
- L680 _public typedef_ `typedef FMetalVertexDeclaration TConcreteType;`
- L685 _public typedef_ `typedef FMetalVertexShader TConcreteType;`
- L690 _public typedef_ `typedef FMetalGeometryShader TConcreteType;`
- L695 _public typedef_ `typedef FMetalPixelShader TConcreteType;`
- L700 _public typedef_ `typedef FMetalComputeShader TConcreteType;`
- L706 _public typedef_ `typedef FMetalMeshShader TConcreteType;`
- L711 _public typedef_ `typedef FMetalAmplificationShader TConcreteType;`
- L717 _public typedef_ `typedef FMetalRHIRenderQuery TConcreteType;`
- L722 _public typedef_ `typedef FMetalSuballocatedUniformBuffer TConcreteType;`
- L727 _public typedef_ `typedef FMetalRHIBuffer TConcreteType;`
- L732 _public typedef_ `typedef FMetalShaderResourceView TConcreteType;`
- L737 _public typedef_ `typedef FMetalUnorderedAccessView TConcreteType;`
- L743 _public typedef_ `typedef FMetalGraphicsPipelineState TConcreteType;`
- L748 _public typedef_ `typedef FMetalGPUFence TConcreteType;`
- L753 _public typedef_ `typedef FMetalRHIStagingBuffer TConcreteType;`
- L759 _public typedef_ `typedef FMetalRayTracingScene TConcreteType;`
- L764 _public typedef_ `typedef FMetalRayTracingGeometry TConcreteType;`
- L769 _public typedef_ `typedef FMetalRayTracingShaderBindingTable TConcreteType;`
- L774 _public typedef_ `typedef FMetalRayShader TConcreteType;`
- L779 _public typedef_ `typedef FMetalRayTracingPipelineState TConcreteType;`

#### struct `TMetalResourceTraits`  
`template<> struct TMetalResourceTraits<FRHIVertexDeclaration>`  
_L678-681_
- L675 _public typedef_ `typedef FMetalShaderLibrary TConcreteType;`
- L680 _public typedef_ `typedef FMetalVertexDeclaration TConcreteType;`
- L685 _public typedef_ `typedef FMetalVertexShader TConcreteType;`
- L690 _public typedef_ `typedef FMetalGeometryShader TConcreteType;`
- L695 _public typedef_ `typedef FMetalPixelShader TConcreteType;`
- L700 _public typedef_ `typedef FMetalComputeShader TConcreteType;`
- L706 _public typedef_ `typedef FMetalMeshShader TConcreteType;`
- L711 _public typedef_ `typedef FMetalAmplificationShader TConcreteType;`
- L717 _public typedef_ `typedef FMetalRHIRenderQuery TConcreteType;`
- L722 _public typedef_ `typedef FMetalSuballocatedUniformBuffer TConcreteType;`
- L727 _public typedef_ `typedef FMetalRHIBuffer TConcreteType;`
- L732 _public typedef_ `typedef FMetalShaderResourceView TConcreteType;`
- L737 _public typedef_ `typedef FMetalUnorderedAccessView TConcreteType;`
- L743 _public typedef_ `typedef FMetalGraphicsPipelineState TConcreteType;`
- L748 _public typedef_ `typedef FMetalGPUFence TConcreteType;`
- L753 _public typedef_ `typedef FMetalRHIStagingBuffer TConcreteType;`
- L759 _public typedef_ `typedef FMetalRayTracingScene TConcreteType;`
- L764 _public typedef_ `typedef FMetalRayTracingGeometry TConcreteType;`
- L769 _public typedef_ `typedef FMetalRayTracingShaderBindingTable TConcreteType;`
- L774 _public typedef_ `typedef FMetalRayShader TConcreteType;`
- L779 _public typedef_ `typedef FMetalRayTracingPipelineState TConcreteType;`

#### struct `TMetalResourceTraits`  
`template<> struct TMetalResourceTraits<FRHIVertexShader>`  
_L683-686_
- L675 _public typedef_ `typedef FMetalShaderLibrary TConcreteType;`
- L680 _public typedef_ `typedef FMetalVertexDeclaration TConcreteType;`
- L685 _public typedef_ `typedef FMetalVertexShader TConcreteType;`
- L690 _public typedef_ `typedef FMetalGeometryShader TConcreteType;`
- L695 _public typedef_ `typedef FMetalPixelShader TConcreteType;`
- L700 _public typedef_ `typedef FMetalComputeShader TConcreteType;`
- L706 _public typedef_ `typedef FMetalMeshShader TConcreteType;`
- L711 _public typedef_ `typedef FMetalAmplificationShader TConcreteType;`
- L717 _public typedef_ `typedef FMetalRHIRenderQuery TConcreteType;`
- L722 _public typedef_ `typedef FMetalSuballocatedUniformBuffer TConcreteType;`
- L727 _public typedef_ `typedef FMetalRHIBuffer TConcreteType;`
- L732 _public typedef_ `typedef FMetalShaderResourceView TConcreteType;`
- L737 _public typedef_ `typedef FMetalUnorderedAccessView TConcreteType;`
- L743 _public typedef_ `typedef FMetalGraphicsPipelineState TConcreteType;`
- L748 _public typedef_ `typedef FMetalGPUFence TConcreteType;`
- L753 _public typedef_ `typedef FMetalRHIStagingBuffer TConcreteType;`
- L759 _public typedef_ `typedef FMetalRayTracingScene TConcreteType;`
- L764 _public typedef_ `typedef FMetalRayTracingGeometry TConcreteType;`
- L769 _public typedef_ `typedef FMetalRayTracingShaderBindingTable TConcreteType;`
- L774 _public typedef_ `typedef FMetalRayShader TConcreteType;`
- L779 _public typedef_ `typedef FMetalRayTracingPipelineState TConcreteType;`

#### struct `TMetalResourceTraits`  
`template<> struct TMetalResourceTraits<FRHIGeometryShader>`  
_L688-691_
- L675 _public typedef_ `typedef FMetalShaderLibrary TConcreteType;`
- L680 _public typedef_ `typedef FMetalVertexDeclaration TConcreteType;`
- L685 _public typedef_ `typedef FMetalVertexShader TConcreteType;`
- L690 _public typedef_ `typedef FMetalGeometryShader TConcreteType;`
- L695 _public typedef_ `typedef FMetalPixelShader TConcreteType;`
- L700 _public typedef_ `typedef FMetalComputeShader TConcreteType;`
- L706 _public typedef_ `typedef FMetalMeshShader TConcreteType;`
- L711 _public typedef_ `typedef FMetalAmplificationShader TConcreteType;`
- L717 _public typedef_ `typedef FMetalRHIRenderQuery TConcreteType;`
- L722 _public typedef_ `typedef FMetalSuballocatedUniformBuffer TConcreteType;`
- L727 _public typedef_ `typedef FMetalRHIBuffer TConcreteType;`
- L732 _public typedef_ `typedef FMetalShaderResourceView TConcreteType;`
- L737 _public typedef_ `typedef FMetalUnorderedAccessView TConcreteType;`
- L743 _public typedef_ `typedef FMetalGraphicsPipelineState TConcreteType;`
- L748 _public typedef_ `typedef FMetalGPUFence TConcreteType;`
- L753 _public typedef_ `typedef FMetalRHIStagingBuffer TConcreteType;`
- L759 _public typedef_ `typedef FMetalRayTracingScene TConcreteType;`
- L764 _public typedef_ `typedef FMetalRayTracingGeometry TConcreteType;`
- L769 _public typedef_ `typedef FMetalRayTracingShaderBindingTable TConcreteType;`
- L774 _public typedef_ `typedef FMetalRayShader TConcreteType;`
- L779 _public typedef_ `typedef FMetalRayTracingPipelineState TConcreteType;`

#### struct `TMetalResourceTraits`  
`template<> struct TMetalResourceTraits<FRHIPixelShader>`  
_L693-696_
- L675 _public typedef_ `typedef FMetalShaderLibrary TConcreteType;`
- L680 _public typedef_ `typedef FMetalVertexDeclaration TConcreteType;`
- L685 _public typedef_ `typedef FMetalVertexShader TConcreteType;`
- L690 _public typedef_ `typedef FMetalGeometryShader TConcreteType;`
- L695 _public typedef_ `typedef FMetalPixelShader TConcreteType;`
- L700 _public typedef_ `typedef FMetalComputeShader TConcreteType;`
- L706 _public typedef_ `typedef FMetalMeshShader TConcreteType;`
- L711 _public typedef_ `typedef FMetalAmplificationShader TConcreteType;`
- L717 _public typedef_ `typedef FMetalRHIRenderQuery TConcreteType;`
- L722 _public typedef_ `typedef FMetalSuballocatedUniformBuffer TConcreteType;`
- L727 _public typedef_ `typedef FMetalRHIBuffer TConcreteType;`
- L732 _public typedef_ `typedef FMetalShaderResourceView TConcreteType;`
- L737 _public typedef_ `typedef FMetalUnorderedAccessView TConcreteType;`
- L743 _public typedef_ `typedef FMetalGraphicsPipelineState TConcreteType;`
- L748 _public typedef_ `typedef FMetalGPUFence TConcreteType;`
- L753 _public typedef_ `typedef FMetalRHIStagingBuffer TConcreteType;`
- L759 _public typedef_ `typedef FMetalRayTracingScene TConcreteType;`
- L764 _public typedef_ `typedef FMetalRayTracingGeometry TConcreteType;`
- L769 _public typedef_ `typedef FMetalRayTracingShaderBindingTable TConcreteType;`
- L774 _public typedef_ `typedef FMetalRayShader TConcreteType;`
- L779 _public typedef_ `typedef FMetalRayTracingPipelineState TConcreteType;`

#### struct `TMetalResourceTraits`  
`template<> struct TMetalResourceTraits<FRHIComputeShader>`  
_L698-701_
- L675 _public typedef_ `typedef FMetalShaderLibrary TConcreteType;`
- L680 _public typedef_ `typedef FMetalVertexDeclaration TConcreteType;`
- L685 _public typedef_ `typedef FMetalVertexShader TConcreteType;`
- L690 _public typedef_ `typedef FMetalGeometryShader TConcreteType;`
- L695 _public typedef_ `typedef FMetalPixelShader TConcreteType;`
- L700 _public typedef_ `typedef FMetalComputeShader TConcreteType;`
- L706 _public typedef_ `typedef FMetalMeshShader TConcreteType;`
- L711 _public typedef_ `typedef FMetalAmplificationShader TConcreteType;`
- L717 _public typedef_ `typedef FMetalRHIRenderQuery TConcreteType;`
- L722 _public typedef_ `typedef FMetalSuballocatedUniformBuffer TConcreteType;`
- L727 _public typedef_ `typedef FMetalRHIBuffer TConcreteType;`
- L732 _public typedef_ `typedef FMetalShaderResourceView TConcreteType;`
- L737 _public typedef_ `typedef FMetalUnorderedAccessView TConcreteType;`
- L743 _public typedef_ `typedef FMetalGraphicsPipelineState TConcreteType;`
- L748 _public typedef_ `typedef FMetalGPUFence TConcreteType;`
- L753 _public typedef_ `typedef FMetalRHIStagingBuffer TConcreteType;`
- L759 _public typedef_ `typedef FMetalRayTracingScene TConcreteType;`
- L764 _public typedef_ `typedef FMetalRayTracingGeometry TConcreteType;`
- L769 _public typedef_ `typedef FMetalRayTracingShaderBindingTable TConcreteType;`
- L774 _public typedef_ `typedef FMetalRayShader TConcreteType;`
- L779 _public typedef_ `typedef FMetalRayTracingPipelineState TConcreteType;`

#### struct `TMetalResourceTraits`  
`template<> struct TMetalResourceTraits<FRHIMeshShader>`  
_L704-707_
- L675 _public typedef_ `typedef FMetalShaderLibrary TConcreteType;`
- L680 _public typedef_ `typedef FMetalVertexDeclaration TConcreteType;`
- L685 _public typedef_ `typedef FMetalVertexShader TConcreteType;`
- L690 _public typedef_ `typedef FMetalGeometryShader TConcreteType;`
- L695 _public typedef_ `typedef FMetalPixelShader TConcreteType;`
- L700 _public typedef_ `typedef FMetalComputeShader TConcreteType;`
- L706 _public typedef_ `typedef FMetalMeshShader TConcreteType;`
- L711 _public typedef_ `typedef FMetalAmplificationShader TConcreteType;`
- L717 _public typedef_ `typedef FMetalRHIRenderQuery TConcreteType;`
- L722 _public typedef_ `typedef FMetalSuballocatedUniformBuffer TConcreteType;`
- L727 _public typedef_ `typedef FMetalRHIBuffer TConcreteType;`
- L732 _public typedef_ `typedef FMetalShaderResourceView TConcreteType;`
- L737 _public typedef_ `typedef FMetalUnorderedAccessView TConcreteType;`
- L743 _public typedef_ `typedef FMetalGraphicsPipelineState TConcreteType;`
- L748 _public typedef_ `typedef FMetalGPUFence TConcreteType;`
- L753 _public typedef_ `typedef FMetalRHIStagingBuffer TConcreteType;`
- L759 _public typedef_ `typedef FMetalRayTracingScene TConcreteType;`
- L764 _public typedef_ `typedef FMetalRayTracingGeometry TConcreteType;`
- L769 _public typedef_ `typedef FMetalRayTracingShaderBindingTable TConcreteType;`
- L774 _public typedef_ `typedef FMetalRayShader TConcreteType;`
- L779 _public typedef_ `typedef FMetalRayTracingPipelineState TConcreteType;`

#### struct `TMetalResourceTraits`  
`template<> struct TMetalResourceTraits<FRHIAmplificationShader>`  
_L709-712_
- L675 _public typedef_ `typedef FMetalShaderLibrary TConcreteType;`
- L680 _public typedef_ `typedef FMetalVertexDeclaration TConcreteType;`
- L685 _public typedef_ `typedef FMetalVertexShader TConcreteType;`
- L690 _public typedef_ `typedef FMetalGeometryShader TConcreteType;`
- L695 _public typedef_ `typedef FMetalPixelShader TConcreteType;`
- L700 _public typedef_ `typedef FMetalComputeShader TConcreteType;`
- L706 _public typedef_ `typedef FMetalMeshShader TConcreteType;`
- L711 _public typedef_ `typedef FMetalAmplificationShader TConcreteType;`
- L717 _public typedef_ `typedef FMetalRHIRenderQuery TConcreteType;`
- L722 _public typedef_ `typedef FMetalSuballocatedUniformBuffer TConcreteType;`
- L727 _public typedef_ `typedef FMetalRHIBuffer TConcreteType;`
- L732 _public typedef_ `typedef FMetalShaderResourceView TConcreteType;`
- L737 _public typedef_ `typedef FMetalUnorderedAccessView TConcreteType;`
- L743 _public typedef_ `typedef FMetalGraphicsPipelineState TConcreteType;`
- L748 _public typedef_ `typedef FMetalGPUFence TConcreteType;`
- L753 _public typedef_ `typedef FMetalRHIStagingBuffer TConcreteType;`
- L759 _public typedef_ `typedef FMetalRayTracingScene TConcreteType;`
- L764 _public typedef_ `typedef FMetalRayTracingGeometry TConcreteType;`
- L769 _public typedef_ `typedef FMetalRayTracingShaderBindingTable TConcreteType;`
- L774 _public typedef_ `typedef FMetalRayShader TConcreteType;`
- L779 _public typedef_ `typedef FMetalRayTracingPipelineState TConcreteType;`

#### struct `TMetalResourceTraits`  
`template<> struct TMetalResourceTraits<FRHIRenderQuery>`  
_L715-718_
- L675 _public typedef_ `typedef FMetalShaderLibrary TConcreteType;`
- L680 _public typedef_ `typedef FMetalVertexDeclaration TConcreteType;`
- L685 _public typedef_ `typedef FMetalVertexShader TConcreteType;`
- L690 _public typedef_ `typedef FMetalGeometryShader TConcreteType;`
- L695 _public typedef_ `typedef FMetalPixelShader TConcreteType;`
- L700 _public typedef_ `typedef FMetalComputeShader TConcreteType;`
- L706 _public typedef_ `typedef FMetalMeshShader TConcreteType;`
- L711 _public typedef_ `typedef FMetalAmplificationShader TConcreteType;`
- L717 _public typedef_ `typedef FMetalRHIRenderQuery TConcreteType;`
- L722 _public typedef_ `typedef FMetalSuballocatedUniformBuffer TConcreteType;`
- L727 _public typedef_ `typedef FMetalRHIBuffer TConcreteType;`
- L732 _public typedef_ `typedef FMetalShaderResourceView TConcreteType;`
- L737 _public typedef_ `typedef FMetalUnorderedAccessView TConcreteType;`
- L743 _public typedef_ `typedef FMetalGraphicsPipelineState TConcreteType;`
- L748 _public typedef_ `typedef FMetalGPUFence TConcreteType;`
- L753 _public typedef_ `typedef FMetalRHIStagingBuffer TConcreteType;`
- L759 _public typedef_ `typedef FMetalRayTracingScene TConcreteType;`
- L764 _public typedef_ `typedef FMetalRayTracingGeometry TConcreteType;`
- L769 _public typedef_ `typedef FMetalRayTracingShaderBindingTable TConcreteType;`
- L774 _public typedef_ `typedef FMetalRayShader TConcreteType;`
- L779 _public typedef_ `typedef FMetalRayTracingPipelineState TConcreteType;`

#### struct `TMetalResourceTraits`  
`template<> struct TMetalResourceTraits<FRHIUniformBuffer>`  
_L720-723_
- L675 _public typedef_ `typedef FMetalShaderLibrary TConcreteType;`
- L680 _public typedef_ `typedef FMetalVertexDeclaration TConcreteType;`
- L685 _public typedef_ `typedef FMetalVertexShader TConcreteType;`
- L690 _public typedef_ `typedef FMetalGeometryShader TConcreteType;`
- L695 _public typedef_ `typedef FMetalPixelShader TConcreteType;`
- L700 _public typedef_ `typedef FMetalComputeShader TConcreteType;`
- L706 _public typedef_ `typedef FMetalMeshShader TConcreteType;`
- L711 _public typedef_ `typedef FMetalAmplificationShader TConcreteType;`
- L717 _public typedef_ `typedef FMetalRHIRenderQuery TConcreteType;`
- L722 _public typedef_ `typedef FMetalSuballocatedUniformBuffer TConcreteType;`
- L727 _public typedef_ `typedef FMetalRHIBuffer TConcreteType;`
- L732 _public typedef_ `typedef FMetalShaderResourceView TConcreteType;`
- L737 _public typedef_ `typedef FMetalUnorderedAccessView TConcreteType;`
- L743 _public typedef_ `typedef FMetalGraphicsPipelineState TConcreteType;`
- L748 _public typedef_ `typedef FMetalGPUFence TConcreteType;`
- L753 _public typedef_ `typedef FMetalRHIStagingBuffer TConcreteType;`
- L759 _public typedef_ `typedef FMetalRayTracingScene TConcreteType;`
- L764 _public typedef_ `typedef FMetalRayTracingGeometry TConcreteType;`
- L769 _public typedef_ `typedef FMetalRayTracingShaderBindingTable TConcreteType;`
- L774 _public typedef_ `typedef FMetalRayShader TConcreteType;`
- L779 _public typedef_ `typedef FMetalRayTracingPipelineState TConcreteType;`

#### struct `TMetalResourceTraits`  
`template<> struct TMetalResourceTraits<FRHIBuffer>`  
_L725-728_
- L675 _public typedef_ `typedef FMetalShaderLibrary TConcreteType;`
- L680 _public typedef_ `typedef FMetalVertexDeclaration TConcreteType;`
- L685 _public typedef_ `typedef FMetalVertexShader TConcreteType;`
- L690 _public typedef_ `typedef FMetalGeometryShader TConcreteType;`
- L695 _public typedef_ `typedef FMetalPixelShader TConcreteType;`
- L700 _public typedef_ `typedef FMetalComputeShader TConcreteType;`
- L706 _public typedef_ `typedef FMetalMeshShader TConcreteType;`
- L711 _public typedef_ `typedef FMetalAmplificationShader TConcreteType;`
- L717 _public typedef_ `typedef FMetalRHIRenderQuery TConcreteType;`
- L722 _public typedef_ `typedef FMetalSuballocatedUniformBuffer TConcreteType;`
- L727 _public typedef_ `typedef FMetalRHIBuffer TConcreteType;`
- L732 _public typedef_ `typedef FMetalShaderResourceView TConcreteType;`
- L737 _public typedef_ `typedef FMetalUnorderedAccessView TConcreteType;`
- L743 _public typedef_ `typedef FMetalGraphicsPipelineState TConcreteType;`
- L748 _public typedef_ `typedef FMetalGPUFence TConcreteType;`
- L753 _public typedef_ `typedef FMetalRHIStagingBuffer TConcreteType;`
- L759 _public typedef_ `typedef FMetalRayTracingScene TConcreteType;`
- L764 _public typedef_ `typedef FMetalRayTracingGeometry TConcreteType;`
- L769 _public typedef_ `typedef FMetalRayTracingShaderBindingTable TConcreteType;`
- L774 _public typedef_ `typedef FMetalRayShader TConcreteType;`
- L779 _public typedef_ `typedef FMetalRayTracingPipelineState TConcreteType;`

#### struct `TMetalResourceTraits`  
`template<> struct TMetalResourceTraits<FRHIShaderResourceView>`  
_L730-733_
- L675 _public typedef_ `typedef FMetalShaderLibrary TConcreteType;`
- L680 _public typedef_ `typedef FMetalVertexDeclaration TConcreteType;`
- L685 _public typedef_ `typedef FMetalVertexShader TConcreteType;`
- L690 _public typedef_ `typedef FMetalGeometryShader TConcreteType;`
- L695 _public typedef_ `typedef FMetalPixelShader TConcreteType;`
- L700 _public typedef_ `typedef FMetalComputeShader TConcreteType;`
- L706 _public typedef_ `typedef FMetalMeshShader TConcreteType;`
- L711 _public typedef_ `typedef FMetalAmplificationShader TConcreteType;`
- L717 _public typedef_ `typedef FMetalRHIRenderQuery TConcreteType;`
- L722 _public typedef_ `typedef FMetalSuballocatedUniformBuffer TConcreteType;`
- L727 _public typedef_ `typedef FMetalRHIBuffer TConcreteType;`
- L732 _public typedef_ `typedef FMetalShaderResourceView TConcreteType;`
- L737 _public typedef_ `typedef FMetalUnorderedAccessView TConcreteType;`
- L743 _public typedef_ `typedef FMetalGraphicsPipelineState TConcreteType;`
- L748 _public typedef_ `typedef FMetalGPUFence TConcreteType;`
- L753 _public typedef_ `typedef FMetalRHIStagingBuffer TConcreteType;`
- L759 _public typedef_ `typedef FMetalRayTracingScene TConcreteType;`
- L764 _public typedef_ `typedef FMetalRayTracingGeometry TConcreteType;`
- L769 _public typedef_ `typedef FMetalRayTracingShaderBindingTable TConcreteType;`
- L774 _public typedef_ `typedef FMetalRayShader TConcreteType;`
- L779 _public typedef_ `typedef FMetalRayTracingPipelineState TConcreteType;`

#### struct `TMetalResourceTraits`  
`template<> struct TMetalResourceTraits<FRHIUnorderedAccessView>`  
_L735-738_
- L675 _public typedef_ `typedef FMetalShaderLibrary TConcreteType;`
- L680 _public typedef_ `typedef FMetalVertexDeclaration TConcreteType;`
- L685 _public typedef_ `typedef FMetalVertexShader TConcreteType;`
- L690 _public typedef_ `typedef FMetalGeometryShader TConcreteType;`
- L695 _public typedef_ `typedef FMetalPixelShader TConcreteType;`
- L700 _public typedef_ `typedef FMetalComputeShader TConcreteType;`
- L706 _public typedef_ `typedef FMetalMeshShader TConcreteType;`
- L711 _public typedef_ `typedef FMetalAmplificationShader TConcreteType;`
- L717 _public typedef_ `typedef FMetalRHIRenderQuery TConcreteType;`
- L722 _public typedef_ `typedef FMetalSuballocatedUniformBuffer TConcreteType;`
- L727 _public typedef_ `typedef FMetalRHIBuffer TConcreteType;`
- L732 _public typedef_ `typedef FMetalShaderResourceView TConcreteType;`
- L737 _public typedef_ `typedef FMetalUnorderedAccessView TConcreteType;`
- L743 _public typedef_ `typedef FMetalGraphicsPipelineState TConcreteType;`
- L748 _public typedef_ `typedef FMetalGPUFence TConcreteType;`
- L753 _public typedef_ `typedef FMetalRHIStagingBuffer TConcreteType;`
- L759 _public typedef_ `typedef FMetalRayTracingScene TConcreteType;`
- L764 _public typedef_ `typedef FMetalRayTracingGeometry TConcreteType;`
- L769 _public typedef_ `typedef FMetalRayTracingShaderBindingTable TConcreteType;`
- L774 _public typedef_ `typedef FMetalRayShader TConcreteType;`
- L779 _public typedef_ `typedef FMetalRayTracingPipelineState TConcreteType;`

#### struct `TMetalResourceTraits`  
`template<> struct TMetalResourceTraits<FRHIGraphicsPipelineState>`  
_L741-744_
- L675 _public typedef_ `typedef FMetalShaderLibrary TConcreteType;`
- L680 _public typedef_ `typedef FMetalVertexDeclaration TConcreteType;`
- L685 _public typedef_ `typedef FMetalVertexShader TConcreteType;`
- L690 _public typedef_ `typedef FMetalGeometryShader TConcreteType;`
- L695 _public typedef_ `typedef FMetalPixelShader TConcreteType;`
- L700 _public typedef_ `typedef FMetalComputeShader TConcreteType;`
- L706 _public typedef_ `typedef FMetalMeshShader TConcreteType;`
- L711 _public typedef_ `typedef FMetalAmplificationShader TConcreteType;`
- L717 _public typedef_ `typedef FMetalRHIRenderQuery TConcreteType;`
- L722 _public typedef_ `typedef FMetalSuballocatedUniformBuffer TConcreteType;`
- L727 _public typedef_ `typedef FMetalRHIBuffer TConcreteType;`
- L732 _public typedef_ `typedef FMetalShaderResourceView TConcreteType;`
- L737 _public typedef_ `typedef FMetalUnorderedAccessView TConcreteType;`
- L743 _public typedef_ `typedef FMetalGraphicsPipelineState TConcreteType;`
- L748 _public typedef_ `typedef FMetalGPUFence TConcreteType;`
- L753 _public typedef_ `typedef FMetalRHIStagingBuffer TConcreteType;`
- L759 _public typedef_ `typedef FMetalRayTracingScene TConcreteType;`
- L764 _public typedef_ `typedef FMetalRayTracingGeometry TConcreteType;`
- L769 _public typedef_ `typedef FMetalRayTracingShaderBindingTable TConcreteType;`
- L774 _public typedef_ `typedef FMetalRayShader TConcreteType;`
- L779 _public typedef_ `typedef FMetalRayTracingPipelineState TConcreteType;`

#### struct `TMetalResourceTraits`  
`template<> struct TMetalResourceTraits<FRHIGPUFence>`  
_L746-749_
- L675 _public typedef_ `typedef FMetalShaderLibrary TConcreteType;`
- L680 _public typedef_ `typedef FMetalVertexDeclaration TConcreteType;`
- L685 _public typedef_ `typedef FMetalVertexShader TConcreteType;`
- L690 _public typedef_ `typedef FMetalGeometryShader TConcreteType;`
- L695 _public typedef_ `typedef FMetalPixelShader TConcreteType;`
- L700 _public typedef_ `typedef FMetalComputeShader TConcreteType;`
- L706 _public typedef_ `typedef FMetalMeshShader TConcreteType;`
- L711 _public typedef_ `typedef FMetalAmplificationShader TConcreteType;`
- L717 _public typedef_ `typedef FMetalRHIRenderQuery TConcreteType;`
- L722 _public typedef_ `typedef FMetalSuballocatedUniformBuffer TConcreteType;`
- L727 _public typedef_ `typedef FMetalRHIBuffer TConcreteType;`
- L732 _public typedef_ `typedef FMetalShaderResourceView TConcreteType;`
- L737 _public typedef_ `typedef FMetalUnorderedAccessView TConcreteType;`
- L743 _public typedef_ `typedef FMetalGraphicsPipelineState TConcreteType;`
- L748 _public typedef_ `typedef FMetalGPUFence TConcreteType;`
- L753 _public typedef_ `typedef FMetalRHIStagingBuffer TConcreteType;`
- L759 _public typedef_ `typedef FMetalRayTracingScene TConcreteType;`
- L764 _public typedef_ `typedef FMetalRayTracingGeometry TConcreteType;`
- L769 _public typedef_ `typedef FMetalRayTracingShaderBindingTable TConcreteType;`
- L774 _public typedef_ `typedef FMetalRayShader TConcreteType;`
- L779 _public typedef_ `typedef FMetalRayTracingPipelineState TConcreteType;`

#### struct `TMetalResourceTraits`  
`template<> struct TMetalResourceTraits<FRHIStagingBuffer>`  
_L751-754_
- L675 _public typedef_ `typedef FMetalShaderLibrary TConcreteType;`
- L680 _public typedef_ `typedef FMetalVertexDeclaration TConcreteType;`
- L685 _public typedef_ `typedef FMetalVertexShader TConcreteType;`
- L690 _public typedef_ `typedef FMetalGeometryShader TConcreteType;`
- L695 _public typedef_ `typedef FMetalPixelShader TConcreteType;`
- L700 _public typedef_ `typedef FMetalComputeShader TConcreteType;`
- L706 _public typedef_ `typedef FMetalMeshShader TConcreteType;`
- L711 _public typedef_ `typedef FMetalAmplificationShader TConcreteType;`
- L717 _public typedef_ `typedef FMetalRHIRenderQuery TConcreteType;`
- L722 _public typedef_ `typedef FMetalSuballocatedUniformBuffer TConcreteType;`
- L727 _public typedef_ `typedef FMetalRHIBuffer TConcreteType;`
- L732 _public typedef_ `typedef FMetalShaderResourceView TConcreteType;`
- L737 _public typedef_ `typedef FMetalUnorderedAccessView TConcreteType;`
- L743 _public typedef_ `typedef FMetalGraphicsPipelineState TConcreteType;`
- L748 _public typedef_ `typedef FMetalGPUFence TConcreteType;`
- L753 _public typedef_ `typedef FMetalRHIStagingBuffer TConcreteType;`
- L759 _public typedef_ `typedef FMetalRayTracingScene TConcreteType;`
- L764 _public typedef_ `typedef FMetalRayTracingGeometry TConcreteType;`
- L769 _public typedef_ `typedef FMetalRayTracingShaderBindingTable TConcreteType;`
- L774 _public typedef_ `typedef FMetalRayShader TConcreteType;`
- L779 _public typedef_ `typedef FMetalRayTracingPipelineState TConcreteType;`

#### struct `TMetalResourceTraits`  
`template<> struct TMetalResourceTraits<FRHIRayTracingScene>`  
_L757-760_
- L675 _public typedef_ `typedef FMetalShaderLibrary TConcreteType;`
- L680 _public typedef_ `typedef FMetalVertexDeclaration TConcreteType;`
- L685 _public typedef_ `typedef FMetalVertexShader TConcreteType;`
- L690 _public typedef_ `typedef FMetalGeometryShader TConcreteType;`
- L695 _public typedef_ `typedef FMetalPixelShader TConcreteType;`
- L700 _public typedef_ `typedef FMetalComputeShader TConcreteType;`
- L706 _public typedef_ `typedef FMetalMeshShader TConcreteType;`
- L711 _public typedef_ `typedef FMetalAmplificationShader TConcreteType;`
- L717 _public typedef_ `typedef FMetalRHIRenderQuery TConcreteType;`
- L722 _public typedef_ `typedef FMetalSuballocatedUniformBuffer TConcreteType;`
- L727 _public typedef_ `typedef FMetalRHIBuffer TConcreteType;`
- L732 _public typedef_ `typedef FMetalShaderResourceView TConcreteType;`
- L737 _public typedef_ `typedef FMetalUnorderedAccessView TConcreteType;`
- L743 _public typedef_ `typedef FMetalGraphicsPipelineState TConcreteType;`
- L748 _public typedef_ `typedef FMetalGPUFence TConcreteType;`
- L753 _public typedef_ `typedef FMetalRHIStagingBuffer TConcreteType;`
- L759 _public typedef_ `typedef FMetalRayTracingScene TConcreteType;`
- L764 _public typedef_ `typedef FMetalRayTracingGeometry TConcreteType;`
- L769 _public typedef_ `typedef FMetalRayTracingShaderBindingTable TConcreteType;`
- L774 _public typedef_ `typedef FMetalRayShader TConcreteType;`
- L779 _public typedef_ `typedef FMetalRayTracingPipelineState TConcreteType;`

#### struct `TMetalResourceTraits`  
`template<> struct TMetalResourceTraits<FRHIRayTracingGeometry>`  
_L762-765_
- L675 _public typedef_ `typedef FMetalShaderLibrary TConcreteType;`
- L680 _public typedef_ `typedef FMetalVertexDeclaration TConcreteType;`
- L685 _public typedef_ `typedef FMetalVertexShader TConcreteType;`
- L690 _public typedef_ `typedef FMetalGeometryShader TConcreteType;`
- L695 _public typedef_ `typedef FMetalPixelShader TConcreteType;`
- L700 _public typedef_ `typedef FMetalComputeShader TConcreteType;`
- L706 _public typedef_ `typedef FMetalMeshShader TConcreteType;`
- L711 _public typedef_ `typedef FMetalAmplificationShader TConcreteType;`
- L717 _public typedef_ `typedef FMetalRHIRenderQuery TConcreteType;`
- L722 _public typedef_ `typedef FMetalSuballocatedUniformBuffer TConcreteType;`
- L727 _public typedef_ `typedef FMetalRHIBuffer TConcreteType;`
- L732 _public typedef_ `typedef FMetalShaderResourceView TConcreteType;`
- L737 _public typedef_ `typedef FMetalUnorderedAccessView TConcreteType;`
- L743 _public typedef_ `typedef FMetalGraphicsPipelineState TConcreteType;`
- L748 _public typedef_ `typedef FMetalGPUFence TConcreteType;`
- L753 _public typedef_ `typedef FMetalRHIStagingBuffer TConcreteType;`
- L759 _public typedef_ `typedef FMetalRayTracingScene TConcreteType;`
- L764 _public typedef_ `typedef FMetalRayTracingGeometry TConcreteType;`
- L769 _public typedef_ `typedef FMetalRayTracingShaderBindingTable TConcreteType;`
- L774 _public typedef_ `typedef FMetalRayShader TConcreteType;`
- L779 _public typedef_ `typedef FMetalRayTracingPipelineState TConcreteType;`

#### struct `TMetalResourceTraits`  
`template<> struct TMetalResourceTraits<FRHIShaderBindingTable>`  
_L767-770_
- L675 _public typedef_ `typedef FMetalShaderLibrary TConcreteType;`
- L680 _public typedef_ `typedef FMetalVertexDeclaration TConcreteType;`
- L685 _public typedef_ `typedef FMetalVertexShader TConcreteType;`
- L690 _public typedef_ `typedef FMetalGeometryShader TConcreteType;`
- L695 _public typedef_ `typedef FMetalPixelShader TConcreteType;`
- L700 _public typedef_ `typedef FMetalComputeShader TConcreteType;`
- L706 _public typedef_ `typedef FMetalMeshShader TConcreteType;`
- L711 _public typedef_ `typedef FMetalAmplificationShader TConcreteType;`
- L717 _public typedef_ `typedef FMetalRHIRenderQuery TConcreteType;`
- L722 _public typedef_ `typedef FMetalSuballocatedUniformBuffer TConcreteType;`
- L727 _public typedef_ `typedef FMetalRHIBuffer TConcreteType;`
- L732 _public typedef_ `typedef FMetalShaderResourceView TConcreteType;`
- L737 _public typedef_ `typedef FMetalUnorderedAccessView TConcreteType;`
- L743 _public typedef_ `typedef FMetalGraphicsPipelineState TConcreteType;`
- L748 _public typedef_ `typedef FMetalGPUFence TConcreteType;`
- L753 _public typedef_ `typedef FMetalRHIStagingBuffer TConcreteType;`
- L759 _public typedef_ `typedef FMetalRayTracingScene TConcreteType;`
- L764 _public typedef_ `typedef FMetalRayTracingGeometry TConcreteType;`
- L769 _public typedef_ `typedef FMetalRayTracingShaderBindingTable TConcreteType;`
- L774 _public typedef_ `typedef FMetalRayShader TConcreteType;`
- L779 _public typedef_ `typedef FMetalRayTracingPipelineState TConcreteType;`

#### struct `TMetalResourceTraits`  
`template<> struct TMetalResourceTraits<FRHIRayTracingShader>`  
_L772-775_
- L675 _public typedef_ `typedef FMetalShaderLibrary TConcreteType;`
- L680 _public typedef_ `typedef FMetalVertexDeclaration TConcreteType;`
- L685 _public typedef_ `typedef FMetalVertexShader TConcreteType;`
- L690 _public typedef_ `typedef FMetalGeometryShader TConcreteType;`
- L695 _public typedef_ `typedef FMetalPixelShader TConcreteType;`
- L700 _public typedef_ `typedef FMetalComputeShader TConcreteType;`
- L706 _public typedef_ `typedef FMetalMeshShader TConcreteType;`
- L711 _public typedef_ `typedef FMetalAmplificationShader TConcreteType;`
- L717 _public typedef_ `typedef FMetalRHIRenderQuery TConcreteType;`
- L722 _public typedef_ `typedef FMetalSuballocatedUniformBuffer TConcreteType;`
- L727 _public typedef_ `typedef FMetalRHIBuffer TConcreteType;`
- L732 _public typedef_ `typedef FMetalShaderResourceView TConcreteType;`
- L737 _public typedef_ `typedef FMetalUnorderedAccessView TConcreteType;`
- L743 _public typedef_ `typedef FMetalGraphicsPipelineState TConcreteType;`
- L748 _public typedef_ `typedef FMetalGPUFence TConcreteType;`
- L753 _public typedef_ `typedef FMetalRHIStagingBuffer TConcreteType;`
- L759 _public typedef_ `typedef FMetalRayTracingScene TConcreteType;`
- L764 _public typedef_ `typedef FMetalRayTracingGeometry TConcreteType;`
- L769 _public typedef_ `typedef FMetalRayTracingShaderBindingTable TConcreteType;`
- L774 _public typedef_ `typedef FMetalRayShader TConcreteType;`
- L779 _public typedef_ `typedef FMetalRayTracingPipelineState TConcreteType;`

#### struct `TMetalResourceTraits`  
`template<> struct TMetalResourceTraits<FRHIRayTracingPipelineState>`  
_L777-780_
- L675 _public typedef_ `typedef FMetalShaderLibrary TConcreteType;`
- L680 _public typedef_ `typedef FMetalVertexDeclaration TConcreteType;`
- L685 _public typedef_ `typedef FMetalVertexShader TConcreteType;`
- L690 _public typedef_ `typedef FMetalGeometryShader TConcreteType;`
- L695 _public typedef_ `typedef FMetalPixelShader TConcreteType;`
- L700 _public typedef_ `typedef FMetalComputeShader TConcreteType;`
- L706 _public typedef_ `typedef FMetalMeshShader TConcreteType;`
- L711 _public typedef_ `typedef FMetalAmplificationShader TConcreteType;`
- L717 _public typedef_ `typedef FMetalRHIRenderQuery TConcreteType;`
- L722 _public typedef_ `typedef FMetalSuballocatedUniformBuffer TConcreteType;`
- L727 _public typedef_ `typedef FMetalRHIBuffer TConcreteType;`
- L732 _public typedef_ `typedef FMetalShaderResourceView TConcreteType;`
- L737 _public typedef_ `typedef FMetalUnorderedAccessView TConcreteType;`
- L743 _public typedef_ `typedef FMetalGraphicsPipelineState TConcreteType;`
- L748 _public typedef_ `typedef FMetalGPUFence TConcreteType;`
- L753 _public typedef_ `typedef FMetalRHIStagingBuffer TConcreteType;`
- L759 _public typedef_ `typedef FMetalRayTracingScene TConcreteType;`
- L764 _public typedef_ `typedef FMetalRayTracingGeometry TConcreteType;`
- L769 _public typedef_ `typedef FMetalRayTracingShaderBindingTable TConcreteType;`
- L774 _public typedef_ `typedef FMetalRayShader TConcreteType;`
- L779 _public typedef_ `typedef FMetalRayTracingPipelineState TConcreteType;`

#### Free symbols / members of external scopes

- L16 _macro_ `#define UE_METAL_RHI_SUPPORT_CLEAR_UAV_WITH_BLIT_ENCODER 1`
- L26 _function_ `friend uint32 GetTypeHash(FMetalRenderPipelineHash const& Hash)`
- L31 _function_ `friend bool operator==(FMetalRenderPipelineHash const& Left, FMetalRenderPipelineHash const& Right)`
- L45 _function_ `inline uint32 GetTypeHash(const MTL::Buffer* BufferPtr)`
- L81 _function_ `friend uint32 GetTypeHash(FMetalBuffer const& Hash)`
- L115 _typedef_ `typedef TSharedPtr<FMetalBuffer, ESPMode::ThreadSafe> FMetalBufferPtr;`
- L207 _function_ `inline uint32 GetTypeHash(const MTLTexturePtr& TexturePtr)`

### `Source/Runtime/Apple/MetalRHI/Public/MetalShaderResources.h` (Public)


#### enum `EMetalBufferFormat`  
`enum class EMetalBufferFormat : uint8`  
_L20-94_
- desc: Buffer data-types for MetalRHI & MetalSL
- L22 _public enumerator_ `Unknown =0`
- L24 _public enumerator_ `R8Sint =1`
- L25 _public enumerator_ `R8Uint =2`
- L26 _public enumerator_ `R8Snorm =3`
- L27 _public enumerator_ `R8Unorm =4`
- L29 _public enumerator_ `R16Sint =5`
- L30 _public enumerator_ `R16Uint =6`
- L31 _public enumerator_ `R16Snorm =7`
- L32 _public enumerator_ `R16Unorm =8`
- L33 _public enumerator_ `R16Half =9`
- L35 _public enumerator_ `R32Sint =10`
- L36 _public enumerator_ `R32Uint =11`
- L37 _public enumerator_ `R32Float =12`
- L39 _public enumerator_ `RG8Sint =13`
- L40 _public enumerator_ `RG8Uint =14`
- L41 _public enumerator_ `RG8Snorm =15`
- L42 _public enumerator_ `RG8Unorm =16`
- L44 _public enumerator_ `RG16Sint =17`
- L45 _public enumerator_ `RG16Uint =18`
- L46 _public enumerator_ `RG16Snorm =19`
- L47 _public enumerator_ `RG16Unorm =20`
- L48 _public enumerator_ `RG16Half =21`
- L50 _public enumerator_ `RG32Sint =22`
- L51 _public enumerator_ `RG32Uint =23`
- L52 _public enumerator_ `RG32Float =24`
- L54 _public enumerator_ `RGB8Sint =25`
- L55 _public enumerator_ `RGB8Uint =26`
- L56 _public enumerator_ `RGB8Snorm =27`
- L57 _public enumerator_ `RGB8Unorm =28`
- L59 _public enumerator_ `RGB16Sint =29`
- L60 _public enumerator_ `RGB16Uint =30`
- L61 _public enumerator_ `RGB16Snorm =31`
- L62 _public enumerator_ `RGB16Unorm =32`
- L63 _public enumerator_ `RGB16Half =33`
- L65 _public enumerator_ `RGB32Sint =34`
- L66 _public enumerator_ `RGB32Uint =35`
- L67 _public enumerator_ `RGB32Float =36`
- L69 _public enumerator_ `RGBA8Sint =37`
- L70 _public enumerator_ `RGBA8Uint =38`
- L71 _public enumerator_ `RGBA8Snorm =39`
- L72 _public enumerator_ `RGBA8Unorm =40`
- L74 _public enumerator_ `BGRA8Unorm =41`
- L76 _public enumerator_ `RGBA16Sint =42`
- L77 _public enumerator_ `RGBA16Uint =43`
- L78 _public enumerator_ `RGBA16Snorm =44`
- L79 _public enumerator_ `RGBA16Unorm =45`
- L80 _public enumerator_ `RGBA16Half =46`
- L82 _public enumerator_ `RGBA32Sint =47`
- L83 _public enumerator_ `RGBA32Uint =48`
- L84 _public enumerator_ `RGBA32Float =49`
- L86 _public enumerator_ `RGB10A2Unorm =50`
- L88 _public enumerator_ `RG11B10Half =51`
- L90 _public enumerator_ `R5G6B5Unorm =52`
- L91 _public enumerator_ `B5G5R5A1Unorm =53`
- L93 _public enumerator_ `Max =54`

#### enum `EMetalBindingsFlags`  
`enum class EMetalBindingsFlags : uint8`  
_L96-100_
- L98 _public enumerator_ `PixelDiscard = 1 << 0`
- L99 _public enumerator_ `UseMetalShaderConverter = 1 << 1`

#### struct `FMetalShaderBindings`  
`struct FMetalShaderBindings`  
_L134-152_
- L136 _public member_ `TArray<CrossCompiler::FPackedArrayInfo> PackedGlobalArrays;`
- L137 _public member_ `TMap<uint8, TArray<uint8>> ArgumentBufferMasks;`
- L138 _public member_ `CrossCompiler::FShaderBindingInOutMask InOutMask;`
- L139 _public member_ `FString IRConverterReflectionJSON;`
- L140 _public member_ `uint32 RSNumCBVs = 0;`
- L141 _public member_ `uint32 OutputSizeVS = 0;`
- L142 _public member_ `uint32 MaxInputPrimitivesPerMeshThreadgroupGS = 0;`
- L144 _public member_ `uint32 ConstantBuffers = 0;`
- L145 _public member_ `uint32 ArgumentBuffers = 0;`
- L146 _public member_ `uint8 NumSamplers = 0;`
- L147 _public member_ `uint8 NumUniformBuffers = 0;`
- L148 _public member_ `uint8 NumUAVs = 0;`
- L149 _public member_ `EMetalBindingsFlags Flags{};`
- L151 _public prototype_ `inline FArchive& Serialize(FArchive& Ar, FShaderResourceTable& SRT);`
- L154 _function_ `inline FArchive& FMetalShaderBindings::Serialize(FArchive& Ar, FShaderResourceTable& SRT)`

#### enum `EMetalOutputWindingMode`  
`enum class EMetalOutputWindingMode : uint8`  
_L179-183_
- L181 _public enumerator_ `Clockwise = 0`
- L182 _public enumerator_ `CounterClockwise = 1`

#### enum `EMetalPartitionMode`  
`enum class EMetalPartitionMode : uint8`  
_L185-191_
- L187 _public enumerator_ `Pow2 = 0`
- L188 _public enumerator_ `Integer = 1`
- L189 _public enumerator_ `FractionalOdd = 2`
- L190 _public enumerator_ `FractionalEven = 3`

#### enum `EMetalComponentType`  
`enum class EMetalComponentType : uint8`  
_L193-201_
- L195 _public enumerator_ `Uint = 0`
- L196 _public enumerator_ `Int`
- L197 _public enumerator_ `Half`
- L198 _public enumerator_ `Float`
- L199 _public enumerator_ `Bool`
- L200 _public enumerator_ `Max`

#### struct `FMetalRayTracingHeader`  
`struct FMetalRayTracingHeader`  
_L203-253_
- L205 _public member_ `uint32 PayloadType;`
- L206 _public member_ `uint32 PayloadSize;`
- L207 _public member_ `uint32 DefaultBytecodeStage = IRShaderStageInvalid;`
- L208 _public member_ `uint32 ExtendedBytecodeStage = IRShaderStageInvalid;`
- L209 _public member_ `FString EntryPoint;`
- L210 _public member_ `FString AnyHitEntryPoint;`
- L211 _public member_ `FString IntersectionEntryPoint;`
- L212 _public member_ `int32 ExtendedCodeDataOffset;`
- L213 _public member_ `int32 ExtendedCodeDataSize;`
- L215 _public member_ `TArray<IRRootParameter1> GlobalRootParams;`
- L216 _public member_ `TArray<IRRootParameter1> LocalRootParams;`
- L218 _public function_ `bool IsValid() const`
- L226 _public function_ `FMetalRayTracingHeader() : PayloadType(UINT32_MAX) , PayloadSize(UINT32_MAX) , DefaultBytecodeStage(IRShaderStageInvalid) , ExtendedBytecodeStage(IRShaderStageInvalid) , ExtendedCodeDataOffset(-1) , ExtendedCodeDataSize(-1)`

#### struct `FMetalAttribute`  
`struct FMetalAttribute`  
_L255-282_
- L257 _public member_ `uint32 Index;`
- L258 _public member_ `uint32 Components;`
- L259 _public member_ `uint32 Offset;`
- L260 _public member_ `EMetalComponentType Type;`
- L261 _public member_ `uint32 Semantic;`
- L263 _public function_ `FMetalAttribute() : Index(0) , Components(0) , Offset(0) , Type(EMetalComponentType::Uint) , Semantic(0)`

#### struct `FMetalCodeHeader`  
`struct FMetalCodeHeader`  
_L284-314_
- L286 _public member_ `FMetalShaderBindings Bindings;`
- L288 _public member_ `uint32 SourceLen;`
- L289 _public member_ `uint32 SourceCRC;`
- L290 _public member_ `uint32 Version;`
- L291 _public member_ `uint32 NumThreadsX;`
- L292 _public member_ `uint32 NumThreadsY;`
- L293 _public member_ `uint32 NumThreadsZ;`
- L294 _public member_ `uint32 CompileFlags;`
- L295 _public member_ `FMetalRayTracingHeader RayTracing;`
- L296 _public member_ `uint8 Frequency;`
- L297 _public member_ `int8 SideTable;`
- L300 _public function_ `FMetalCodeHeader() : SourceLen(0) , SourceCRC(0) , Version(0) , NumThreadsX(0) , NumThreadsY(0) , NumThreadsZ(0) , CompileFlags(0) , Frequency(0) , SideTable(-1)`
- L313 _public prototype_ `inline FArchive& Serialize(FArchive& Ar, FShaderResourceTable& SRT);`
- L317 _function_ `inline FArchive& FMetalCodeHeader::Serialize(FArchive& Ar, FShaderResourceTable& SRT)`

#### struct `FMetalShaderLibraryHeader`  
`struct FMetalShaderLibraryHeader`  
_L338-348_
- L340 _public member_ `FString Format;`
- L341 _public member_ `uint32 NumLibraries;`
- L342 _public member_ `uint32 NumShadersPerLibrary;`

#### struct `FMetalShaderBytecode`  
`struct FMetalShaderBytecode`  
_L368-379_
- L370 _public member_ `FString NativePath;`
- L371 _public member_ `TArray<uint8> OutputFile;`
- L372 _public member_ `TArray<uint8> ObjectFile;`

#### struct `FMetalBindlessShaderInfo`  
`struct FMetalBindlessShaderInfo`  
_L381-416_
- L383 _public member_ `FString RayEntryPoint;`
- L384 _public member_ `FString RayAnyHitEntryPoint;`
- L385 _public member_ `FString RayIntersectionEntryPoint;`
- L386 _public member_ `FString UniqueEntryPointName;`
- L387 _public member_ `FString UniqueRayAnyHitEntryPoint;`
- L388 _public member_ `FString UniqueRayIntersectionEntryPoint;`
- L390 _public member_ `uint32_t NumInstructions = 0;`
- L391 _public member_ `uint32_t NumCBVs = 0;`
- L393 _public member_ `uint32 CRCLen = 0;`
- L394 _public member_ `uint32 CRC = 0;`
- L395 _public member_ `uint32 SourceLen = 0;`
- L396 _public member_ `bool bUsesDualSourceBlending = false;`
- L398 _public member_ `TArray<IRRootParameter1> GlobalRootParams;`
- L399 _public member_ `TArray<IRRootParameter1> UnsortedLocalRootParams;`
- L400 _public member_ `TArray<IRRootParameter1> LocalRootParams;`
- L402 _public member_ `static constexpr uint32 NumShaderSpaces = (UE_HLSL_SPACE_STATIC_SHADER_BINDINGS + 1);`
- L405 _public member_ `TMap<uint32, FString> RootParamsCache[NumShaderSpaces];` — Temporary cache to remove dupes when processing a shader library. Key is the register index; Value is the binding name (for sanity check at compile time).
- L408 _public member_ `FMetalShaderBytecode MetalBytecode;` — Main entry point
- L409 _public member_ `IRShaderStage DefaultBytecodeShaderStage;`
- L412 _public member_ `FMetalShaderBytecode MetalBytecodeExtended;` — Extended entry point (only used by RayTracing IS/AHS)
- L413 _public member_ `IRShaderStage ExtendedBytecodeShaderStage = IRShaderStageInvalid;`
- L415 _public member_ `bool bIsProcedural = false;`

#### Free symbols / members of external scopes

- L102 _function_ `static constexpr IRStaticSamplerDescriptor MakeStaticSampler(const IRFilter Filter, const IRTextureAddressMode WrapMode, const uint32 Register, const uint32 Space)`
- L124 _variable_ `static IRStaticSamplerDescriptor StaticSamplerDescs[] = { MakeStaticSampler(IRFilterMinMagMipPoint, IRTextureAddressModeWrap, 0, 1000), MakeStaticSampler(IRFilterMinMagMipPoint, IRTextureAddressModeClamp, 1, 1000), MakeStaticSampler(IRFilterMinMagLinearMipPoint, IRTextureAddressModeWrap, 2, 1000), MakeStaticSampler(IRFilterMinMagLinearMipPoint, IRTextureAddressModeClamp, 3, 1000), MakeStaticSampler(IRFilterMinMagMipLinear, IRTextureAddressModeWrap, 4, 1000), MakeStaticSampler(IRFilterMinMagMipLinear, IRTextureAddressModeClamp, 5, 1000), };` — Static sampler table must match MetalCommon.ush
- L237 _function_ `friend FArchive& operator<<(FArchive& Ar, FMetalRayTracingHeader& Header)`
- L273 _function_ `friend FArchive& operator<<(FArchive& Ar, FMetalAttribute& Attr)`
- L344 _function_ `friend FArchive& operator<<(FArchive& Ar, FMetalShaderLibraryHeader& Header)`
- L350 _function_ `inline FArchive& operator<<(FArchive &Ar, IRRootDescriptor1 &RootDescriptor)`
- L359 _function_ `inline FArchive& operator<<(FArchive &Ar, IRRootParameter1 &RootParameter)`
- L374 _function_ `friend FArchive& operator<<( FArchive& Ar, FMetalShaderBytecode& Info )`

### `Source/Runtime/Apple/MetalRHI/Public/MetalState.h` (Public)


#### class `FMetalSamplerState`  
`class FMetalSamplerState : public FRHISamplerState`  
_L13-35_
- inherits: `FRHISamplerState`
- L20 _public prototype_ `FMetalSamplerState(class FMetalDevice& Device, const FSamplerStateInitializerRHI& Initializer);` — Constructor/destructor
- L21 _public prototype_ `~FMetalSamplerState();`
- L23 _public member_ `MTL::SamplerState* State;`
- L25 _public member_ `MTL::SamplerState* NoAnisoState;`
- L28 _public member_ `FRHIDescriptorHandle BindlessHandle;`
- L31 _public function_ `virtual FRHIDescriptorHandle GetBindlessHandle() const override final` — TODO: Do we need to support NoAnisoState too? (or is it some leftover we don't care about anymore?)
- L34 _public member_ `FMetalDevice& Device;`

#### class `FMetalRasterizerState`  
`class FMetalRasterizerState : public FRHIRasterizerState`  
_L37-50_
- inherits: `FRHIRasterizerState`
- L44 _public prototype_ `FMetalRasterizerState(const FRasterizerStateInitializerRHI& Initializer);` — Constructor/destructor
- L45 _public prototype_ `~FMetalRasterizerState();`
- L47 _public prototype_ `virtual bool GetInitializer(FRasterizerStateInitializerRHI& Init) override final;`
- L49 _public member_ `FRasterizerStateInitializerRHI State;`

#### class `FMetalDepthStencilState`  
`class FMetalDepthStencilState : public FRHIDepthStencilState`  
_L52-68_
- inherits: `FRHIDepthStencilState`
- L59 _public prototype_ `FMetalDepthStencilState(MTL::Device* Device, const FDepthStencilStateInitializerRHI& Initializer);` — Constructor/destructor
- L60 _public prototype_ `~FMetalDepthStencilState();`
- L62 _public prototype_ `virtual bool GetInitializer(FDepthStencilStateInitializerRHI& Init) override final;`
- L64 _public member_ `FDepthStencilStateInitializerRHI Initializer;`
- L65 _public member_ `MTL::DepthStencilState* State;`
- L66 _public member_ `bool bIsDepthWriteEnabled;`
- L67 _public member_ `bool bIsStencilWriteEnabled;`

#### class `FMetalBlendState`  
`class FMetalBlendState : public FRHIBlendState`  
_L70-96_
- inherits: `FRHIBlendState`
- L77 _public prototype_ `FMetalBlendState(const FBlendStateInitializerRHI& Initializer);` — Constructor/destructor
- L78 _public prototype_ `~FMetalBlendState();`
- L80 _public prototype_ `virtual bool GetInitializer(FBlendStateInitializerRHI& Init) override final;`
- L87 _public member_ `FBlendPerMRT RenderTargetStates[MaxSimultaneousRenderTargets];`
- L88 _public member_ `bool bUseIndependentRenderTargetBlendStates;`
- L89 _public member_ `bool bUseAlphaToCoverage;`
- L93 _private member_ `static TMap<uint32, uint8> BlendSettingsToUniqueKeyMap;` — this tracks blend settings (in a bit flag) into a unique key that uses few bits, for PipelineState MRT setup
- L94 _private member_ `static uint8 NextKey;`
- L95 _private member_ `static FCriticalSection Mutex;`

#### struct `FMetalBlendState::FBlendPerMRT`  
`struct FBlendPerMRT`  
_L82-86_
- L84 _public member_ `MTL::RenderPipelineColorAttachmentDescriptor* BlendState;`
- L85 _public member_ `uint8 BlendStateKey;`

#### struct `TMetalResourceTraits`  
`template<> struct TMetalResourceTraits<FRHISamplerState>`  
_L99-102_
- L101 _public typedef_ `typedef FMetalSamplerState TConcreteType;`
- L106 _public typedef_ `typedef FMetalRasterizerState TConcreteType;`
- L111 _public typedef_ `typedef FMetalDepthStencilState TConcreteType;`
- L116 _public typedef_ `typedef FMetalBlendState TConcreteType;`

#### struct `TMetalResourceTraits`  
`template<> struct TMetalResourceTraits<FRHIRasterizerState>`  
_L104-107_
- L101 _public typedef_ `typedef FMetalSamplerState TConcreteType;`
- L106 _public typedef_ `typedef FMetalRasterizerState TConcreteType;`
- L111 _public typedef_ `typedef FMetalDepthStencilState TConcreteType;`
- L116 _public typedef_ `typedef FMetalBlendState TConcreteType;`

#### struct `TMetalResourceTraits`  
`template<> struct TMetalResourceTraits<FRHIDepthStencilState>`  
_L109-112_
- L101 _public typedef_ `typedef FMetalSamplerState TConcreteType;`
- L106 _public typedef_ `typedef FMetalRasterizerState TConcreteType;`
- L111 _public typedef_ `typedef FMetalDepthStencilState TConcreteType;`
- L116 _public typedef_ `typedef FMetalBlendState TConcreteType;`

#### struct `TMetalResourceTraits`  
`template<> struct TMetalResourceTraits<FRHIBlendState>`  
_L114-117_
- L101 _public typedef_ `typedef FMetalSamplerState TConcreteType;`
- L106 _public typedef_ `typedef FMetalRasterizerState TConcreteType;`
- L111 _public typedef_ `typedef FMetalDepthStencilState TConcreteType;`
- L116 _public typedef_ `typedef FMetalBlendState TConcreteType;`

### `Source/Runtime/Apple/MetalRHI/Public/MetalTempAllocator.h` (Public)


#### class `FMetalTempAllocator`  
`class FMetalTempAllocator : public IMetalBufferAllocator`  
_L15-44_
- inherits: `IMetalBufferAllocator`
- desc: Simple Temporary allocator that allocates from heaps
- L18 _public prototype_ `FMetalTempAllocator(FMetalDevice& InDevice, uint32_t InMinAllocationSize, uint32_t InTargetAllocationLimit, uint32_t InAlignment);`
- L20 _public prototype_ `FMetalBufferPtr Allocate(const uint32_t Size);`
- L21 _public prototype_ `void Cleanup();`
- L23 _public function_ `virtual void ReleaseBuffer(FMetalBuffer*) override`
- L33 _private member_ `FMetalDevice& Device;`
- L34 _private member_ `TArray<FTempBufferInfo> Buffers;`
- L36 _private member_ `FCriticalSection AllocatorLock;`
- L38 _private member_ `TStatId TotalAllocationStat;`
- L40 _private member_ `uint32_t TotalAllocated = 0;`
- L41 _private member_ `uint32_t MinAllocationSize = 0;`
- L42 _private member_ `uint32_t TargetAllocationLimit = 0;`
- L43 _private member_ `uint32_t Alignment;`

#### struct `FMetalTempAllocator::FTempBufferInfo`  
`struct FTempBufferInfo`  
_L26-31_
- L28 _public member_ `MTL::Buffer* Buffer;`
- L29 _public member_ `uint32_t Offset;`
- L30 _public member_ `uint32_t Size;`

### `Source/Runtime/Apple/MetalRHI/Public/MetalThirdParty.h` (Public)
_(no declarations extracted)_

### `Source/Runtime/Apple/MetalRHI/Public/MetalUniformBuffer.h` (Public)


#### class `FMetalSuballocatedUniformBuffer`  
`class FMetalSuballocatedUniformBuffer : public FRHIUniformBuffer`  
_L18-65_
- inherits: `FRHIUniformBuffer`
- L23 _public member_ `uint32 LastFrameUpdated;` — The last render thread frame this uniform buffer updated or pushed contents to the GPU backing
- L25 _public member_ `FMetalBufferPtr BackingBuffer;`
- L29 _public member_ `void* Shadow;` — CPU side shadow memory to hold updates for single-draw or multi-frame buffers. This allows you to upload on a frame but actually use this UB later on
- L32 _public member_ `FRHIDescriptorHandle BindlessHandle;`
- L36 _private member_ `FMetalDevice& Device;`
- L38 _private member_ `EUniformBufferValidation Validation;`
- L44 _public prototype_ `FMetalSuballocatedUniformBuffer(FMetalDevice& Device, const void* Contents, const FRHIUniformBufferLayout* Layout, EUniformBufferUsage Usage, EUniformBufferValidation Validation);` — Creates a uniform buffer. If Usage is SingleDraw or MultiFrame we will keep a copy of the data
- L46 _public prototype_ `~FMetalSuballocatedUniformBuffer();`
- L49 _public prototype_ `virtual FRHIDescriptorHandle GetBindlessHandle() const;`
- L52 _public prototype_ `void Update(FRHICommandListBase& RHICmdList, const void* Contents);`
- L56 _private prototype_ `void CopyResourceTable(const void* Contents, TArray<TRefCountPtr<FRHIResource> >& OutResourceTable) const;` — Copies the RDG resources to a resource table for a deferred update on the RHI thread.
- L64 _private prototype_ `void PushToGPUBacking(const void* Contents);` — Pushes the data in Contents to the gpu. Updates the frame counter to FrameNumber. (this is to support the case where we create buffer and reuse it many frames later). This acquires a region in the current frame's transient uniform buffer and copies Contents into that backing. The amount of data is determined by the Layout

#### Free symbols / members of external scopes

- L13 _macro_ `#define METAL_UNIFORM_BUFFER_VALIDATION !UE_BUILD_SHIPPING`
- L67 _typedef_ `typedef FMetalSuballocatedUniformBuffer FMetalUniformBuffer;`

### `Source/Runtime/Apple/MetalRHI/Public/MetalViewport.h` (Public)


#### enum `EMetalViewportAccessFlag`  
`enum EMetalViewportAccessFlag`  
_L46-52_
- L48 _public enumerator_ `EMetalViewportAccessRHI`
- L49 _public enumerator_ `EMetalViewportAccessRenderer`
- L50 _public enumerator_ `EMetalViewportAccessGame`
- L51 _public enumerator_ `EMetalViewportAccessDisplayLink`

#### class `FMetalViewport`  
`class FMetalViewport : public FRHIViewport`  
_L66-212_
- inherits: `FRHIViewport`
- L69 _public member_ `static FCriticalSection ViewportsMutex;`
- L70 _public member_ `static TSet<FMetalViewport*> Viewports;`
- L72 _public prototype_ `FMetalViewport(FMetalDevice& InDevice, void* WindowHandle, uint32 InSizeX, uint32 InSizeY, bool bInIsFullscreen,EPixelFormat InFormat);`
- L73 _public prototype_ `~FMetalViewport();`
- L75 _public prototype_ `void Resize(uint32 InSizeX, uint32 InSizeY, bool bInIsFullscreen,EPixelFormat Format,bool bWaitForRenderingThread = true);`
- L77 _public prototype_ `TRefCountPtr<FMetalSurface> GetBackBuffer(EMetalViewportAccessFlag Accessor, TOptional<int32> DrawLayerIndex = TOptional<int32>()) const;`
- L80 _public prototype_ `CA::MetalDrawable* GetDrawable(EMetalViewportAccessFlag Accessor, TOptional<int32> DrawLayerIndex = TOptional<int32>());`
- L81 _public prototype_ `MTL::Texture* GetDrawableTexture(EMetalViewportAccessFlag Accessor, TOptional<int32> DrawLayerIndex = TOptional<int32>());`
- L82 _public prototype_ `MTL::Texture* GetDrawableTexture(EMetalViewportAccessFlag Accessor, FMetalSurface* SurfaceWithDrawLayer);`
- L83 _public prototype_ `MTL::Texture* GetCurrentTexture(EMetalViewportAccessFlag Accessor);`
- L85 _public prototype_ `void ReleaseDrawable(void);`
- L86 _public prototype_ `void ReleaseDrawable(int32 DrawLayerKey);`
- L89 _public prototype_ `virtual void CreateNativeLayer(int32 NewNativeLayer, void* NativeViewHandle, const TArray<TInterval<int32>>& LayerRanges) override;`
- L90 _public prototype_ `virtual void DeleteNativeLayer(int32 OldNativeLayer) override;`
- L91 _public prototype_ `virtual void SetDefaultNativeLayer(int32 NativeLayer) override;`
- L95 _public function_ `virtual void* GetNativeBackBufferTexture() const override` — supports pulling the raw MTLTexture
- L96 _public function_ `virtual void* GetNativeBackBufferRT() const override`
- L99 _public prototype_ `NSWindow* GetWindow() const;`
- L103 _public function_ `virtual void SetCustomPresent(FRHICustomPresent* InCustomPresent) override`
- L108 _public function_ `virtual FRHICustomPresent* GetCustomPresent() const override`
- L111 _public prototype_ `void Present(FMetalCommandBuffer* CommandBuffer, bool bLockToVsync);`
- L114 _public prototype_ `void GetDrawableImmersiveTextures(EMetalViewportAccessFlag Accessor, cp_drawable_t SwiftDrawable, MTL::Texture*& OutColorTexture, MTL::Texture*& OutDepthTexture );`
- L115 _public prototype_ `void PresentImmersive(const MetalRHIVisionOS::PresentImmersiveParams& Params);`
- L119 _public prototype_ `TSharedPtr<SWindow> GetBackingSlateWindow();`
- L124 _private prototype_ `FMetalView* CreateNewMetalView(bool bIsContentView, NSWindowOrderingMode ViewOrder, NSView* ViewRelativeTo, TInterval<int32> LayerRange);`
- L127 _private prototype_ `uint32 GetViewportIndex(EMetalViewportAccessFlag Accessor) const;`
- L128 _private prototype_ `void PresentDrawLayers(FMetalCommandBuffer* CommandBuffer);`
- L130 _private prototype_ `CA::MetalDrawable* GetDrawableInternal(EMetalViewportAccessFlag Accessor, TOptional<int32> DrawLayerIndex, bool bLockAlreadyAquired);`
- L155 _private prototype_ `CommittedDrawable GetCommittedDrawableToPresent(int32 DrawLayer, FMetalCommandBuffer* CommandBuffer, bool& bLayersToDraw, FMetalView** TheView);`
- L158 _private prototype_ `CommittedDrawable GetCommittedDrawableToPresent(int32 DrawLayer, FMetalCommandBuffer* CommandBuffer, bool& bLayersToDraw);`
- L162 _private prototype_ `void ResizeBackBuffer(int32 DrawLayerKey, uint32 Index, uint32 InSizeX, uint32 InSizeY, EPixelFormat InFormat);`
- L165 _private member_ `CP_OBJECT_cp_layer_renderer* SwiftLayer = nullptr;`
- L168 _private member_ `FMetalDevice& Device;`
- L169 _private member_ `mutable FCriticalSection Mutex;`
- L171 _private member_ `uint32 DisplayID;`
- L172 _private member_ `FMetalViewportPresentHandler Block;`
- L173 _private member_ `volatile int32 FrameAvailable;`
- L174 _private member_ `bool bIsFullScreen;`
- L178 _private member_ `uint32 SizeX;`
- L179 _private member_ `uint32 SizeY;`
- L180 _private member_ `EPixelFormat Format;`
- L183 _private member_ `UIInterfaceOrientationMask OrientationMask;`
- L184 _private member_ `UIInterfaceOrientationMask OldOrientationMask;`
- L185 _private member_ `FDelegateHandle OrientationChangedHandle;`
- L188 _private member_ `int32 DefaultNativeLayer;`
- L191 _private member_ `FCocoaWindow* WindowHandle;`
- L196 _private member_ `TMap<int32, DrawLayer> DrawLayers;` — all views with slate layers >= the key get drawn in the value metal view
- L197 _private member_ `TArray<NSView*> ViewsAdded;`
- L199 _private member_ `CA::MetalDrawable* Drawable;`
- L200 _private member_ `TRefCountPtr<FMetalSurface> BackBuffer[2];`
- L202 _private member_ `FMetalView* View;`
- L205 _private member_ `MTL::Texture* DrawableTextures[2];`
- L208 _private member_ `FCustomPresentRHIRef CustomPresent;`
- L211 _private member_ `TWeakPtr<SWindow> BackingSlateWindow;`

#### struct `FMetalViewport::DrawLayer`  
`struct DrawLayer`  
_L135-144_
- L137 _public member_ `TRefCountPtr<FMetalSurface> BackBuffer[2];`
- L138 _public member_ `CA::MetalDrawable* Drawable;`
- L140 _public member_ `FMetalView* View;`

#### struct `FMetalViewport::CommittedDrawable`  
`struct CommittedDrawable`  
_L147-152_
- L149 _public member_ `CA::MetalDrawable* Drawable;`
- L150 _public member_ `MTL::Texture* Texture;`
- L151 _public member_ `int32 Key;`

#### struct `TMetalResourceTraits`  
`template<> struct TMetalResourceTraits<FRHIViewport>`  
_L215-218_
- L217 _public typedef_ `typedef FMetalViewport TConcreteType;`

#### Free symbols / members of external scopes

- L57 _namespace_ `namespace MetalRHIVisionOS`
- L64 _typedef_ `typedef void (^FMetalViewportPresentHandler)(uint32 CGDirectDisplayID, double OutputSeconds, double OutputDuration);`
